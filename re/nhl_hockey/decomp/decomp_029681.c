// Decompiled by Ghidra from hockey.elf (via ledisasm ELF export)
// This is machine generated pseudo-C meant as a reference for porting, it does not compile as is.
#include "prototypes.h"

// ================================================================================================
// sub_29681 @ 0x29681 [__watcall]
// ================================================================================================

undefined4 __watcall sub_29681(void)

{
  __CHK(0x28);
  return 0;
}


// ================================================================================================
// sub_296ba @ 0x296ba [__watcall]
// ================================================================================================

undefined4 __watcall sub_296ba(undefined4 param_1,undefined4 unaff_EDX)

{
  __CHK(0x24);
  if (dword_c695a == 0) {
    playoff_series_status(param_1,unaff_EDX);
  }
  else {
    playoff_round_screen(param_1,unaff_EDX);
  }
  return 0;
}


// ================================================================================================
// playoff_series_status @ 0x2970a [__watcall]
// ================================================================================================

undefined4 __watcall playoff_series_status(undefined4 param_1)

{
  short sVar1;
  short sVar2;
  short sVar3;
  undefined auStackY_6c [32];
  undefined local_4c [2];
  byte bStackY_4a;
  byte bStackY_49;
  byte local_48;
  byte bStackY_47;
  undefined4 local_44;
  ushort local_30;
  short local_28;
  short local_24;
  short local_1c [2];
  uint uStackY_18;
  
  __CHK(0xb0);
  local_1c[0] = -1;
  local_1c[1] = 0xffff;
  local_44 = param_1;
  make_path(auStackY_6c,&unk_c65d4,off_c80e7,&aDB);
  sVar3 = db_open_check(auStackY_6c,&unk_ddac4,0);
  if (sVar3 == 0) {
    make_path(auStackY_6c,0,aLSSCHED,&aDB);
    sVar3 = file_open_read(auStackY_6c,local_1c);
  }
  local_28 = 0;
  sVar1 = 0;
  while ((sVar1 < 0x69 && (sVar3 == 0))) {
    sVar3 = db_read_record2((int)local_1c[0],local_4c,sVar1 + 0x444);
    (&dword_dc7b8)[local_28] = (uint)bStackY_4a;
    (&dword_dc7b8)[(short)(local_28 + 1)] = (uint)bStackY_49;
    local_28 = local_28 + 2;
    sVar1 = sVar1 + 7;
  }
  sVar1 = 0;
  sVar2 = 0;
  local_24 = 0;
  while ((local_24 < 7 && (sVar3 == 0))) {
    sVar3 = db_read_record2((int)local_1c[0],local_4c,local_24 + 0x4a6);
    if (local_24 == 0) {
      uStackY_18 = (uint)bStackY_4a;
      local_30 = (ushort)bStackY_49;
    }
    if (((bStackY_47 < local_48) && (bStackY_4a == (ushort)uStackY_18)) ||
       ((local_48 < bStackY_47 && (bStackY_49 == (ushort)uStackY_18)))) {
      sVar1 = sVar1 + 1;
    }
    else {
      sVar2 = sVar2 + 1;
    }
    if (((sVar1 == 4) && (bStackY_4a == (ushort)uStackY_18)) ||
       ((sVar2 == 4 && (bStackY_4a == local_30)))) {
      dword_dc830 = (uint)bStackY_4a;
      local_24 = 7;
    }
    if (((sVar2 == 4) && (bStackY_49 == local_30)) ||
       ((sVar1 == 4 && (bStackY_49 == (ushort)uStackY_18)))) {
      dword_dc830 = (uint)bStackY_49;
      local_24 = 7;
    }
    local_24 = local_24 + 1;
  }
  file_close(local_1c);
  if (sVar3 == 0) {
    standings_screen();
  }
  return 0;
}


// ================================================================================================
// sub_2991c @ 0x2991c [__watcall]
// ================================================================================================

uint __watcall sub_2991c(char *param_1,uint unaff_EDX,int unaff_EBX)

{
  uint uVar1;
  uint uVar2;
  uint local_34;
  uint local_30;
  char *local_24;
  int local_18;
  uint uStackY_14;
  
  __CHK(0x38);
  uVar1 = (uint)(byte)param_1[2];
  uStackY_14 = (uint)(byte)param_1[3];
  local_24 = param_1;
  if (unaff_EBX == 0) {
    if (param_1[4] == -1) {
      return 0xffffffff;
    }
    local_30 = 0;
    local_34 = 0;
    for (local_18 = 0; (*local_24 != -1 && (local_18 < 7)); local_18 = local_18 + 1) {
      if (local_24[4] == -1) {
        return 0xffffffff;
      }
      if ((byte)local_24[2] == uVar1) {
        if ((byte)local_24[5] < (byte)local_24[4]) {
          local_34 = local_34 + 1;
        }
        else {
          local_30 = local_30 + 1;
        }
      }
      else if ((byte)local_24[5] < (byte)local_24[4]) {
        local_30 = local_30 + 1;
      }
      else {
        local_34 = local_34 + 1;
      }
      local_24 = local_24 + 6;
    }
  }
  else {
    uVar2 = (unaff_EDX >> 1) + 1;
    local_30 = 0;
    local_34 = 0;
    while ((local_34 < uVar2 && (local_30 < uVar2))) {
      if (local_24[4] == -1) {
        return 0xffffffff;
      }
      if ((byte)local_24[2] == uVar1) {
        if ((byte)local_24[5] < (byte)local_24[4]) {
          local_34 = local_34 + 1;
        }
        else {
          local_30 = local_30 + 1;
        }
      }
      else if ((byte)local_24[5] < (byte)local_24[4]) {
        local_30 = local_30 + 1;
      }
      else {
        local_34 = local_34 + 1;
      }
      local_24 = local_24 + 6;
    }
  }
  if ((int)local_30 < (int)local_34) {
    uStackY_14 = uVar1;
  }
  return uStackY_14;
}


// ================================================================================================
// sub_29a97 @ 0x29a97 [__watcall]
// ================================================================================================

void __watcall sub_29a97(undefined4 *param_1)

{
  undefined4 uVar1;
  undefined auStack_3c [32];
  undefined4 *puStack_1c;
  
  __CHK(0x48);
  puStack_1c = param_1;
  if (dword_c695a == 0) {
    make_path(auStack_3c,0,aLSSCHED,&aDB);
  }
  else {
    make_path(auStack_3c,&unk_c65d4,off_c80ef,&aDB);
  }
  uVar1 = loadfile(auStack_3c,0x20);
  *puStack_1c = uVar1;
  return;
}


// ================================================================================================
// playoff_round_screen @ 0x29b07 [__watcall]
// ================================================================================================

undefined4 __watcall playoff_round_screen(void)

{
  undefined4 *puVar1;
  int iVar2;
  int local_34;
  int local_30;
  int iStack_2c;
  int iStack_18;
  
  __CHK(0x5c);
  iStack_2c = strcmp(&unk_c65d4,&byte_c5386);
  for (iStack_18 = 0; iStack_18 < 0x1a; iStack_18 = iStack_18 + 1) {
    strcpy(&unk_ddac4 + iStack_18 * 0x15,(&off_c54a9)[iStack_18]);
  }
  strcpy(&unk_ddce6,(char *)&asc_c136d);
  sub_29a97(&local_30);
  local_34 = local_30 + 0x199a;
  for (iStack_18 = 0; iStack_18 < 0x1e; iStack_18 = iStack_18 + 2) {
    (&dword_dc7b8)[iStack_18] = (uint)*(byte *)(local_34 + 2);
    (&unk_dc7bc)[iStack_18] = (uint)*(byte *)(local_34 + 3);
    if ((&dword_dc7b8)[iStack_18] == 0xff) {
      (&dword_dc7b8)[iStack_18] = 0x1a;
    }
    if ((&unk_dc7bc)[iStack_18] == 0xff) {
      (&unk_dc7bc)[iStack_18] = 0x1a;
    }
    local_34 = local_34 + 0x2a;
  }
  iVar2 = local_30 + 0x1be6;
  puVar1 = (undefined4 *)(local_30 + 0x8a);
  local_30 = local_30 + 2;
  dword_dc830 = sub_2991c(iVar2,*puVar1,iStack_2c);
  if (dword_dc830 == -1) {
    dword_dc830 = 0x1a;
  }
  freemem(local_30 + -2);
  standings_screen();
  return 0;
}


// ================================================================================================
// sub_29c75 @ 0x29c75 [__watcall]
// ================================================================================================

void __watcall sub_29c75(char *param_1,char *unaff_EDX,char *unaff_EBX,int unaff_ECX)

{
  int iVar1;
  size_t sVar2;
  
  __CHK(0x18);
  if (unaff_EDX == (char *)0x0) {
    strcpy(param_1,unaff_EBX);
  }
  else {
    strcpy(param_1,unaff_EDX);
    strcat(param_1,&asc_c8111);
    strcat(param_1,unaff_EBX);
    iVar1 = textwidth(param_1);
    if (unaff_ECX < iVar1) {
      *param_1 = *unaff_EDX;
      param_1[1] = '.';
      param_1[2] = ' ';
      param_1[3] = '\0';
      strcat(param_1,unaff_EBX);
    }
  }
  while( true ) {
    iVar1 = textwidth(param_1);
    if (iVar1 <= unaff_ECX) break;
    sVar2 = strlen(param_1);
    param_1[sVar2 - 1] = '\0';
  }
  return;
}


// ================================================================================================
// sub_29d00 @ 0x29d00 [__watcall]
// ================================================================================================

void __watcall sub_29d00(int param_1,int unaff_EDX,int unaff_EBX,int unaff_ECX,int param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  __CHK(0x38);
  fillrect(param_1,unaff_EDX,(unaff_EBX - param_1) + 1,(unaff_ECX - unaff_EDX) + 1,dword_c71cc);
  sub_b4fac(param_1,unaff_EDX,unaff_EBX,unaff_EDX,dword_c71d0);
  sub_b4fac(param_1,unaff_EDX,param_1,unaff_ECX,dword_c71d0);
  sub_b4fac(unaff_EBX,unaff_EDX,unaff_EBX,unaff_ECX,dword_c71d4);
  sub_b4fac(param_1,unaff_ECX,unaff_EBX,unaff_ECX,dword_c71d4);
  if (param_5 != 0) {
    iVar1 = unaff_EDX + 2;
    iVar2 = param_1 + 2;
    putpixel(iVar2,iVar1,dword_c71d0,iVar1,iVar2);
    unaff_EDX = unaff_EDX + 3;
    param_1 = param_1 + 3;
    putpixel(param_1,unaff_EDX,dword_c71d0);
    putpixel(param_1,iVar1,dword_c71d4);
    putpixel(iVar2,unaff_EDX,dword_c71d4);
    iVar3 = unaff_ECX + -2;
    putpixel(iVar2,iVar3,dword_c71d4,iVar1,iVar2,iVar3);
    unaff_ECX = unaff_ECX + -3;
    putpixel(param_1,unaff_ECX,dword_c71d4);
    putpixel(param_1,iVar3,dword_c71d0);
    putpixel(iVar2,unaff_ECX,dword_c71d0);
    iVar2 = unaff_EBX + -3;
    putpixel(iVar2,iVar1,dword_c71d0);
    unaff_EBX = unaff_EBX + -2;
    putpixel(unaff_EBX,unaff_EDX,dword_c71d0);
    putpixel(unaff_EBX,iVar1,dword_c71d4);
    putpixel(iVar2,unaff_EDX,dword_c71d4);
    putpixel(iVar2,iVar3,dword_c71d4);
    putpixel(unaff_EBX,unaff_ECX,dword_c71d4);
    putpixel(unaff_EBX,iVar3,dword_c71d0);
    putpixel(iVar2,unaff_ECX,dword_c71d0);
  }
  return;
}


// ================================================================================================
// team_select_screen @ 0x29f28 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __watcall team_select_screen(byte param_1,byte unaff_DL)

{
  byte bVar1;
  undefined *puVar2;
  int iVar3;
  int *piVar4;
  int *piVar5;
  int *piVar6;
  undefined4 uVar7;
  int iVar8;
  byte bVar9;
  undefined4 extraout_ECX;
  int extraout_ECX_00;
  undefined *puVar10;
  undefined4 *puVar11;
  int **ppiVar12;
  undefined4 uVar13;
  int **ppiVar14;
  int iVar15;
  undefined4 *puVar16;
  byte bVar17;
  undefined8 uVar18;
  int *piStack_68c;
  undefined auStack_688 [26];
  int aiStack_66e [176];
  undefined auStack_3ac [38];
  undefined auStack_386 [706];
  undefined local_c4 [12];
  int aiStack_b8 [16];
  int aiStack_78 [8];
  undefined5 **local_58;
  int *local_54;
  undefined4 local_50;
  undefined4 *local_4c;
  undefined4 local_48;
  void *local_44;
  int *local_40;
  int *local_3c;
  undefined4 local_38;
  undefined2 *local_34;
  undefined *local_30;
  undefined *puStack_2c;
  undefined4 *local_28;
  int local_24;
  byte local_20 [4];
  byte local_1c;
  byte bStack_18;
  
  bVar17 = 0;
  __CHK(0x6a0);
  local_50 = 0xffffffff;
  piStack_68c = (int *)0x29f5b;
  local_1c = unaff_DL;
  bStack_18 = param_1;
  speech_stop();
  piStack_68c = (int *)0xf7;
  set_dialog_colors(0xf9,0xfa,0xf8);
  piStack_68c = (int *)0x29f85;
  set_text_colors(0xfa,0xf7);
  piStack_68c = (int *)0x20;
  local_44 = (void *)allocmem(&aApal,0x300);
  local_20[0] = bStack_18;
  local_20[1] = local_1c;
  piStack_68c = (int *)0x29fd8;
  make_path(aiStack_78,&league_dir,off_c80e7);
  piStack_68c = (int *)0x29feb;
  iVar3 = file_open_read(aiStack_78,&local_50);
  bVar9 = 0;
  while ((bVar9 < 2 && (iVar3 == 0))) {
    piStack_68c = (int *)0x2a01d;
    iVar3 = db_read_record(local_50,auStack_688 + (uint)bVar9 * 0x2e8,local_20[bVar9]);
    bVar9 = bVar9 + 1;
  }
  piStack_68c = (int *)0x2a034;
  file_close(&local_50);
  piStack_68c = (int *)0x2a039;
  setdefaultscreen();
  piStack_68c = (int *)0x20;
  piVar4 = (int *)allocmem(&aPal_c1375,0x300);
  if ((sound_enabled != '\0') && (dword_c721d != (int *)0x0)) {
    piStack_68c = (int *)0x2a075;
    sound_fade(dword_d2431,3,100);
  }
  piStack_68c = piVar4;
  getpalette(0,0x100);
  piStack_68c = (int *)0x2a096;
  fade_palette(1,piVar4,0x10);
  piStack_68c = piVar4;
  freemem();
  if ((sound_enabled != '\0') && (dword_c721d != (int *)0x0)) {
    do {
      piStack_68c = (int *)0x2a0c3;
      iVar3 = sound_channel_status(ram0x000d242c >> 0x18,3);
    } while (iVar3 == 0);
    piStack_68c = dword_c721d;
    releasememblock();
    dword_c721d = (int *)0x0;
  }
  piVar4 = font_kaufm;
  local_40 = font_main;
  piStack_68c = aiStack_b8;
  getfontstate();
  piStack_68c = local_40;
  setfont();
  puVar10 = install_path;
  if (byte_ed7f3 != '\x01') {
    puVar10 = (undefined *)0x0;
  }
  piStack_68c = (int *)0x2a136;
  make_path(aiStack_78,puVar10,aArena,0);
  piStack_68c = (int *)0x0;
  piVar5 = (int *)loadshapes(aiStack_78);
  piStack_68c = (int *)&aPal_c137f;
  iVar3 = locateshape(piVar5);
  piStack_68c = (int *)0x2a16c;
  memcpy(local_44,(void *)(iVar3 + 0x10),0x300);
  piStack_68c = (int *)&aRink;
  piVar6 = (int *)locateshape(piVar5);
  piStack_68c = (int *)0x1e0;
  setclip(0,0x280,0);
  piStack_68c = piVar6;
  drawshape_home();
  piStack_68c = piVar5;
  freemem();
  puVar10 = install_path;
  if (byte_ed9e5 != '\x01') {
    puVar10 = (undefined *)0x0;
  }
  piStack_68c = (int *)0x2a1ca;
  make_path(aiStack_78,puVar10,aSrlogo,0);
  piStack_68c = (int *)0x0;
  piVar5 = (int *)loadshapes(aiStack_78);
  piStack_68c = (int *)(&off_c57cc)[local_1c];
  uVar7 = locateshape(piVar5);
  piStack_68c = (int *)0x6d;
  drawshape_remap(uVar7,0x3c);
  piStack_68c = (int *)(&off_c57cc)[bStack_18];
  uVar7 = locateshape(piVar5);
  piStack_68c = (int *)0x6d;
  drawshape_remap(uVar7,0x1e5);
  piStack_68c = piVar5;
  freemem();
  piStack_68c = piVar4;
  setfont();
  piStack_68c = aiStack_66e;
  sprintf((char *)aiStack_78,aSAtS,auStack_386);
  piStack_68c = aiStack_78;
  iVar3 = textwidth();
  piStack_68c = (int *)0x2a294;
  sub_17636((0x280 - iVar3) / 2,0x93,aiStack_78);
  piStack_68c = dword_c71cc;
  fillrect(0x6e,0xcf,0x1ae,5);
  piStack_68c = dword_c71d0;
  sub_b4fac(0x6e,0xcf,0x21c,0xcf);
  piStack_68c = dword_c71d4;
  sub_b4fac(0x6e,0xd3,0x21c,0xd3);
  iVar3 = 0;
  do {
    iVar8 = (byte_d42c3 + 3) * iVar3;
    iVar15 = iVar8 + 0xda;
    if (iVar3 == 8) {
      piStack_68c = dword_c71cc;
      iVar15 = iVar8 + 0xdf;
      fillrect(0x6e,iVar15,0x1ae,5);
      piStack_68c = dword_c71d0;
      local_4c = (undefined4 *)(iVar8 + 0xe3);
      sub_b4fac(0x6e,iVar15,0x21c,iVar15);
      piStack_68c = dword_c71d4;
      iVar15 = iVar8 + 0xe8;
      sub_b4fac(0x6e,local_4c,0x21c,local_4c);
    }
    piVar4 = (int *)(&off_c6f48)[iVar3];
    piStack_68c = piVar4;
    iVar8 = textwidth();
    piStack_68c = (int *)0x2a393;
    sub_17636((0x280 - iVar8) / 2,iVar15,piVar4);
    iVar3 = iVar3 + 1;
  } while (iVar3 < 9);
  puStack_2c = local_c4;
  local_30 = auStack_3ac;
  iVar3 = 0;
  do {
    uVar13 = 0xfa;
    uVar7 = 0xfa;
    bVar9 = puStack_2c[(byte)(&unk_c6f6c)[iVar3]];
    bVar1 = local_30[(byte)(&unk_c6f6c)[iVar3]];
    if (bVar1 < bVar9) {
      uVar13 = 0xfd;
    }
    else if (bVar9 < bVar1) {
      uVar7 = 0xfd;
    }
    iVar15 = (byte_d42c3 + 3) * iVar3;
    iVar8 = iVar15 + 0xda;
    if (iVar3 == 8) {
      iVar8 = iVar15 + 0xe6;
    }
    piStack_68c = (int *)0x2a417;
    set_text_colors(uVar13,0xf7,CONCAT22((short)((uint)piVar4 >> 0x10),CONCAT11(bVar1,bVar9)),uVar7)
    ;
    piStack_68c = (int *)(uint)(byte)puStack_2c[(byte)(&unk_c6f6c)[iVar3]];
    sprintf((char *)aiStack_78,(char *)&aD_c139d);
    piStack_68c = (int *)0x2a456;
    sub_17636(0x6e,iVar8,aiStack_78);
    piStack_68c = (int *)0x2a462;
    set_text_colors(extraout_ECX,0xf7);
    piStack_68c = (int *)(uint)(byte)local_30[(byte)(&unk_c6f6c)[iVar3]];
    sprintf((char *)aiStack_78,(char *)&aD_c139d);
    piVar4 = aiStack_78;
    piStack_68c = (int *)0x2a4a1;
    sub_17636(0x212,iVar8,piVar4);
    iVar3 = iVar3 + 1;
  } while (iVar3 < 9);
  piStack_68c = (int *)0x2a4ba;
  set_text_colors(0xfa,0xf7);
  piStack_68c = local_40;
  setfont();
  if ((funcptr_cef43 == (undefined *)0x0) && (funcptr_cef63 == (undefined *)0x0)) {
    local_38 = 2;
LAB_0002a4e7:
    local_34 = (undefined2 *)&unk_c6e9a;
  }
  else {
    if (funcptr_cef43 == (undefined *)0x0) {
      local_38 = 3;
    }
    else {
      if (funcptr_cef63 == (undefined *)0x0) {
        local_38 = 3;
        goto LAB_0002a4e7;
      }
      local_38 = 4;
    }
    local_34 = &a0;
  }
  piStack_68c = (int *)0x1;
  sub_29d00(0,0x1ae,0x26b,0x1df);
  piStack_68c = (int *)0x2a561;
  sub_30ae2(local_34,local_38);
  piStack_68c = (int *)0x20;
  local_4c = (undefined4 *)
             allocmem(aPointer_c13a0,
                      (((int)pointer_shapes[1] >> 0x10) + 1) *
                      ((*(int *)((int)pointer_shapes + 2) >> 0x10) + 1) + 0x11);
  puVar11 = local_4c + (uint)bVar17 * -2 + 1;
  ppiVar14 = pointer_shapes + (uint)bVar17 * -2 + 1;
  *local_4c = *pointer_shapes;
  puVar16 = puVar11 + (uint)bVar17 * -2 + 1;
  ppiVar12 = ppiVar14 + (uint)bVar17 * -2 + 1;
  *puVar11 = *ppiVar14;
  *puVar16 = *ppiVar12;
  puVar16[(uint)bVar17 * -2 + 1] = ppiVar12[(uint)bVar17 * -2 + 1];
  *(undefined *)(puVar16 + (uint)bVar17 * -2 + 1 + (uint)bVar17 * -2 + 1) =
       *(undefined *)(ppiVar12 + (uint)bVar17 * -2 + 1 + (uint)bVar17 * -2 + 1);
  *(short *)(local_4c + 1) = *(short *)(pointer_shapes + 1) + 1;
  *(short *)((int)local_4c + 6) = *(short *)((int)pointer_shapes + 6) + 1;
  ppiVar14 = (int **)0x0;
  local_58 = (undefined5 **)0x0;
  piVar4 = (int *)0x0;
  local_54 = (int *)0x0;
  piStack_68c = (int *)0x1e0;
  local_28 = local_4c;
  setmouselimits(0,0,0x280);
  piStack_68c = local_54;
  setmousepos(local_58);
  piStack_68c = (int *)0x0;
  grabshape(local_4c,0);
  piStack_68c = (int *)0x0;
  drawshape_remap(pointer_shapes,0);
  piStack_68c = (int *)0x2a62e;
  event_queue_reset();
  if ((sound_enabled != '\0') && (dword_c721d == (int *)0x0)) {
    puVar10 = install_path;
    if (byte_ed9af != '\x01') {
      puVar10 = (undefined *)0x0;
    }
    piStack_68c = (int *)0x2a669;
    make_path(aiStack_78,puVar10,aScouting,&aIff_c13a8);
    piStack_68c = (int *)0x2a675;
    dword_c721d = (int *)loadsound(aiStack_78);
    if ((dword_c721d != (int *)0x0) && (((byte)option_flags & 0x40) != 0)) {
      piStack_68c = (int *)0x2a69c;
      playsample(dword_c721d,dword_d2431,3,0x4c);
    }
  }
  piStack_68c = (int *)0x2a6af;
  fade_palette(0,local_44);
  if (dword_dc234 < 0x444) {
    piStack_68c = (int *)0x2a6d2;
    uVar18 = say_game_intro_wrapper(bStack_18,local_1c);
  }
  else {
    if (*(uint *)(&unk_c5581 + (uint)bStack_18 * 4) == *(uint *)(&unk_c5581 + (uint)local_1c * 4)) {
      iVar3 = (int)(*(uint *)(&unk_c5581 + (uint)bStack_18 * 4) |
                   *(uint *)(&unk_c5581 + (uint)local_1c * 4)) % 2 + 1;
    }
    else {
      iVar3 = 3;
    }
    piStack_68c = (int *)0x1;
    if (0x47b < dword_dc234) {
      piStack_68c = (int *)0x2;
    }
    if (0x497 < dword_dc234) {
      piStack_68c = (int *)0x3;
    }
    uVar18 = say_playoff_intro_wrapper(bStack_18,local_1c,(dword_dc234 + -0x444) % 7 + 1,iVar3);
  }
  ppiVar12 = (int **)0x0;
  local_24 = 0;
  local_48 = 0;
  do {
    local_3c = (int *)0x0;
    do {
      piStack_68c = (int *)0x2a795;
      uVar18 = event_queue_pop((int)uVar18,(int)((ulonglong)uVar18 >> 0x20),ppiVar12);
      iVar3 = (int)uVar18;
      if (iVar3 != 0) {
        ppiVar12 = &local_54;
        piStack_68c = (int *)0x2a7af;
        uVar18 = (*ui_poll_callback)();
        local_3c = (int *)uVar18;
        iVar3 = extraout_ECX_00;
      }
    } while ((iVar3 != 0) && (((uint)local_3c & 6) == 0));
    piStack_68c = piVar4;
    if (local_3c == (int *)0x0) {
      if ((ppiVar14 != (int **)local_58) || (piVar4 != local_54)) {
        drawshape(local_28,ppiVar14);
        piStack_68c = local_54;
        grabshape(local_28,local_58);
        ppiVar14 = pointer_shapes;
LAB_0002aa81:
        piStack_68c = local_54;
        uVar18 = drawshape_remap(pointer_shapes,local_58);
        ppiVar12 = ppiVar14;
        ppiVar14 = (int **)local_58;
        piVar4 = local_54;
      }
    }
    else if (((uint)local_3c & 4) == 0) {
      drawshape(local_28,ppiVar14);
      ppiVar12 = (int **)local_58;
      piStack_68c = local_3c;
      iVar3 = sub_30a39(local_34,local_38,local_58,local_54);
      if (-1 < iVar3) {
        if (funcptr_cef63 == (undefined *)0x0) {
          iVar3 = iVar3 + 1;
        }
        switch(iVar3) {
        case 0:
          if ((_away_team_id == dword_c5403) || (_away_team_id == dword_c5407)) {
            piStack_68c = (int *)0x20;
            piVar4 = (int *)allocmem(aScreen,0x4b011);
            piVar5 = piVar4 + (uint)bVar17 * -2 + 1;
            ppiVar14 = pointer_shapes + (uint)bVar17 * -2 + 1;
            *piVar4 = (int)*pointer_shapes;
            piVar6 = piVar5 + (uint)bVar17 * -2 + 1;
            ppiVar12 = ppiVar14 + (uint)bVar17 * -2 + 1;
            *piVar5 = (int)*ppiVar14;
            *piVar6 = (int)*ppiVar12;
            piVar6[(uint)bVar17 * -2 + 1] = (int)ppiVar12[(uint)bVar17 * -2 + 1];
            *(undefined *)(piVar6 + (uint)bVar17 * -2 + 1 + (uint)bVar17 * -2 + 1) =
                 *(undefined *)(ppiVar12 + (uint)bVar17 * -2 + 1 + (uint)bVar17 * -2 + 1);
            *(undefined2 *)(piVar4 + 1) = 0x280;
            *(undefined2 *)((int)piVar4 + 6) = 0x1e0;
            piStack_68c = (int *)0x0;
            grabshape(piVar4,0);
            puVar11 = (undefined4 *)&unk_dabf0;
            uVar7 = 1;
LAB_0002a9be:
            piStack_68c = (int *)0x2a9c3;
            edit_lines_screen_b(uVar7,puVar11,&unk_cf1af,3);
            piStack_68c = (int *)0x20;
            piVar5 = (int *)allocmem(&aPal_c1375,0x300);
            piStack_68c = piVar5;
            getpalette(0,0x100);
            piStack_68c = (int *)0x2a9fa;
            fade_palette(1,piVar5,0x10);
            piStack_68c = piVar5;
            freemem();
            piStack_68c = (int *)0x0;
            drawshape(piVar4,0);
            piStack_68c = piVar4;
            freemem();
            ppiVar12 = (int **)0x10;
            piStack_68c = (int *)0x2aa2c;
            fade_palette(0,local_44);
            piStack_68c = (int *)0x2aa3b;
            set_text_colors(0xfa,0xf7);
          }
          break;
        case 1:
          local_24 = -1;
          break;
        case 2:
          local_24 = -1;
          local_48 = 3;
          break;
        case 3:
          if ((user2_team._2_2_ == dword_c5403) || (user2_team._2_2_ == dword_c5407)) {
            piStack_68c = (int *)0x20;
            piVar4 = (int *)allocmem(aScreen,0x4b011);
            piVar5 = piVar4 + (uint)bVar17 * -2 + 1;
            ppiVar14 = pointer_shapes + (uint)bVar17 * -2 + 1;
            *piVar4 = (int)*pointer_shapes;
            piVar6 = piVar5 + (uint)bVar17 * -2 + 1;
            ppiVar12 = ppiVar14 + (uint)bVar17 * -2 + 1;
            *piVar5 = (int)*ppiVar14;
            *piVar6 = (int)*ppiVar12;
            piVar6[(uint)bVar17 * -2 + 1] = (int)ppiVar12[(uint)bVar17 * -2 + 1];
            *(undefined *)(piVar6 + (uint)bVar17 * -2 + 1 + (uint)bVar17 * -2 + 1) =
                 *(undefined *)(ppiVar12 + (uint)bVar17 * -2 + 1 + (uint)bVar17 * -2 + 1);
            *(undefined2 *)(piVar4 + 1) = 0x280;
            *(undefined2 *)((int)piVar4 + 6) = 0x1e0;
            piStack_68c = (int *)0x0;
            grabshape(piVar4,0);
            puVar11 = &unk_dc200;
            uVar7 = 0;
            goto LAB_0002a9be;
          }
        }
        piStack_68c = (int *)0x2aa40;
        setdefaultscreen();
      }
      piStack_68c = local_54;
      uVar18 = grabshape(local_28,local_58);
      ppiVar14 = (int **)local_58;
      piVar4 = local_54;
      if (local_24 == 0) goto LAB_0002aa81;
    }
    else {
      local_24 = -1;
      local_48 = 3;
    }
    if (local_24 != 0) {
      if ((sound_enabled != '\0') && (dword_c721d != (int *)0x0)) {
        piStack_68c = (int *)0x2aacb;
        sound_fade(dword_d2431,3,100);
      }
      piStack_68c = (int *)0x2aae1;
      fade_palette(1,local_44,0x10);
      if ((sound_enabled != '\0') && (dword_c721d != (int *)0x0)) {
        do {
          piStack_68c = (int *)0x2ab05;
          iVar3 = sound_channel_status(ram0x000d242c >> 0x18,3);
        } while (iVar3 == 0);
        piStack_68c = dword_c721d;
        releasememblock();
        dword_c721d = (int *)0x0;
      }
      ppiVar14 = (int **)auStack_688;
      if ((sound_enabled != '\0') && (ppiVar14 = (int **)auStack_688, (option_flags._1_1_ & 1) != 0)
         ) {
        ppiVar14 = &piStack_68c;
        piStack_68c = (int *)0x2ab36;
        sub_8373e();
        do {
          *(undefined4 *)((int)ppiVar14 + -4) = 0x2ab3b;
          iVar3 = sub_836e4();
        } while (iVar3 != 0);
      }
      *(undefined **)((int)ppiVar14 + -4) = (undefined *)((int)ppiVar14 + 0x5d0);
      *(undefined4 *)((int)ppiVar14 + -8) = 0x2ab4c;
      setfontstate();
      *(undefined4 *)((int)ppiVar14 + -4) = *(undefined4 *)((int)ppiVar14 + 0x644);
      *(undefined4 *)((int)ppiVar14 + -8) = 0x2ab5c;
      freemem();
      *(undefined4 *)((int)ppiVar14 + -4) = *(undefined4 *)((int)ppiVar14 + 0x660);
      *(undefined4 *)((int)ppiVar14 + -8) = 0x2ab6c;
      freemem();
      if (*(int *)((int)ppiVar14 + 0x640) < 2) {
        bVar9 = *(byte *)((int)ppiVar14 + 0x66c);
        bVar17 = *(byte *)((int)ppiVar14 + 0x670);
        *(undefined4 *)((int)ppiVar14 + -4) = 0x2ab94;
        uVar7 = draw_team_logos((uint)bVar17,(uint)bVar9);
        *(undefined4 *)((int)ppiVar14 + 0x640) = uVar7;
        puVar10 = (&team_abbrev)[bVar9];
        puVar2 = (&team_abbrev)[bVar17];
        *(undefined4 *)((int)ppiVar14 + -4) = 0x2abae;
        preload_speech_wrapper(puVar2,puVar10);
      }
      *(undefined4 *)((int)ppiVar14 + 0x664) = 0;
      if (*(int *)((int)ppiVar14 + 0x640) == 3) {
        *(undefined4 *)((int)ppiVar14 + 0x664) = 4;
      }
      return *(undefined4 *)((int)ppiVar14 + 0x664);
    }
  } while( true );
}


// ================================================================================================
// draw_team_logos @ 0x2abdf [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __watcall draw_team_logos(void)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined *puVar5;
  char *pcVar6;
  char *pcVar7;
  char *pcVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  int iVar11;
  undefined4 *puVar12;
  undefined4 *puVar13;
  byte bVar14;
  undefined8 uVar15;
  undefined auStack_134 [84];
  undefined auStack_e0 [64];
  undefined4 local_a0;
  undefined4 uStack_9c;
  undefined4 uStack_84;
  undefined4 local_7c;
  undefined4 uStack_78;
  undefined auStack_6c [16];
  undefined4 *local_5c;
  undefined1 *local_58;
  undefined4 *local_54;
  undefined4 *local_50;
  undefined4 local_4c;
  undefined4 *local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  int local_2c;
  int local_28;
  int local_24;
  undefined4 uStack_20;
  
  bVar14 = 0;
  __CHK(0x148);
  pcVar8 = auStack_134;
  local_4c = 0xffffffff;
  event_queue_reset();
  setdefaultscreen();
  clearclip(0);
  puVar5 = install_path;
  if (byte_ed825 != '\x01') {
    puVar5 = (undefined *)0x0;
  }
  make_path(auStack_6c,puVar5,aCtlogo,0);
  local_38 = loadshapes(auStack_6c,0);
  local_48 = (undefined4 *)locateshape(local_38,(&off_c57cc)[user2_team._2_2_]);
  local_24 = (*(int *)((int)local_48 + 2) >> 0x10) * ((int)local_48[1] >> 0x10) + 0x11;
  local_54 = (undefined4 *)allocmem(aLogohome,local_24,0x20);
  puVar12 = local_54 + (uint)bVar14 * -2 + 1;
  puVar9 = local_48 + (uint)bVar14 * -2 + 1;
  *local_54 = *local_48;
  puVar13 = puVar12 + (uint)bVar14 * -2 + 1;
  puVar10 = puVar9 + (uint)bVar14 * -2 + 1;
  *puVar12 = *puVar9;
  *puVar13 = *puVar10;
  puVar13[(uint)bVar14 * -2 + 1] = puVar10[(uint)bVar14 * -2 + 1];
  *(undefined *)(puVar13 + (uint)bVar14 * -2 + 1 + (uint)bVar14 * -2 + 1) =
       *(undefined *)(puVar10 + (uint)bVar14 * -2 + 1 + (uint)bVar14 * -2 + 1);
  drawshape(local_48,0,0);
  grabshape(local_54,0,0);
  local_48 = (undefined4 *)locateshape(local_38,(&off_c57cc)[_away_team_id]);
  local_24 = ((int)local_48[1] >> 0x10) * (*(int *)((int)local_48 + 2) >> 0x10) + 0x11;
  local_50 = (undefined4 *)allocmem(aLogoaway,local_24,0x20);
  puVar12 = local_50 + (uint)bVar14 * -2 + 1;
  puVar9 = local_48 + (uint)bVar14 * -2 + 1;
  *local_50 = *local_48;
  puVar13 = puVar12 + (uint)bVar14 * -2 + 1;
  puVar10 = puVar9 + (uint)bVar14 * -2 + 1;
  *puVar12 = *puVar9;
  *puVar13 = *puVar10;
  puVar13[(uint)bVar14 * -2 + 1] = puVar10[(uint)bVar14 * -2 + 1];
  *(undefined *)(puVar13 + (uint)bVar14 * -2 + 1 + (uint)bVar14 * -2 + 1) =
       *(undefined *)(puVar10 + (uint)bVar14 * -2 + 1 + (uint)bVar14 * -2 + 1);
  drawshape(local_48,0,0);
  grabshape(local_50,0,0);
  freemem(local_38);
  puVar5 = install_path;
  if (byte_ed824 != '\x01') {
    puVar5 = (undefined *)0x0;
  }
  make_path(auStack_6c,puVar5,aCtbkgd,0);
  uVar1 = loadshapes(auStack_6c,0);
  local_44 = uVar1;
  local_34 = locateshape(uVar1,&aBkgd_c13e0);
  local_2c = locateshape(uVar1,&aPal_c13e5);
  local_2c = local_2c + 0x10;
  puVar5 = install_path;
  if (byte_ed826 != '\x01') {
    puVar5 = (undefined *)0x0;
  }
  make_path(auStack_6c,puVar5,aCttitle1,0);
  uVar1 = loadshapes(auStack_6c,0);
  local_3c = uVar1;
  local_a0 = locateshape(uVar1,&aDef);
  uStack_9c = locateshape(uVar1,&aFowa);
  uStack_84 = locateshape(uVar1,&aScra);
  local_7c = locateshape(uVar1,&aTlu);
  uStack_78 = locateshape(uVar1,&aTop);
  getfontstate(auStack_e0);
  puVar5 = install_path;
  if (byte_ed9e6 != '\x01') {
    puVar5 = (undefined *)0x0;
  }
  make_path(auStack_134,puVar5,aIndus030,&aVFN);
  local_40 = loadfile(auStack_134,0x20);
  setfont(local_40);
  set_text_colors(0x40,0);
  pcVar6 = off_c80d7;
  make_path(auStack_134,&league_dir,off_c80d7,&aDB);
  iVar2 = file_open_read(auStack_134,&local_4c);
  if (iVar2 == 0) {
    local_28 = allocmem(&aGIPK,0xb60,0x20);
    iVar2 = 0;
    local_24 = 0;
    while ((local_24 < 2 && (iVar2 == 0))) {
      iVar11 = 0;
      while ((iVar11 < 0x1c && (iVar2 == 0))) {
        pcVar6 = *(char **)(&unk_dbc7c + iVar11 * 4 + local_24 * 0x2e8);
        if (pcVar6 != (char *)0xffffffff) {
          iVar2 = sub_1463d(local_4c,local_28 + (local_24 * 0x1c + iVar11) * 0x34);
        }
        iVar11 = iVar11 + 1;
      }
      local_24 = local_24 + 1;
    }
  }
  iVar2 = file_close(&local_4c);
  local_5c = &unk_dc200;
  local_58 = &unk_dabf0;
  local_30 = 0;
  if ((sound_enabled != '\0') && (dword_c721d == 0)) {
    pcVar6 = aTonights;
    puVar5 = install_path;
    if (byte_ed9ab != '\x01') {
      puVar5 = (undefined *)0x0;
    }
    make_path(auStack_6c,puVar5,aTonights,&aIff_c141a);
    iVar2 = loadsound(auStack_6c);
    dword_c721d = iVar2;
    if ((iVar2 != 0) && (((byte)option_flags & 0x40) != 0)) {
      pcVar6 = (char *)0x3;
      iVar2 = playsample(iVar2,dword_d2431,3,0x4c);
    }
  }
  uVar15 = 0;
  uStack_20 = 0;
  while( true ) {
    iVar11 = (int)uVar15;
    if ((1 < *(int *)(pcVar8 + 0x114)) || (1 < iVar11)) break;
    pcVar8[-0xffffffff00000004] = -0x79;
    pcVar8[-0xffffffff00000003] = -0x50;
    pcVar8[-0xffffffff00000002] = '\x02';
    pcVar8[-0xffffffff00000001] = '\0';
    setdefaultscreen(iVar2,(int)((ulonglong)uVar15 >> 0x20),pcVar6);
    if (*(int *)(pcVar8 + 0x114) == 0) {
      pcVar8[-0xffffffff00000004] = -0x20;
      pcVar8[-0xffffffff00000003] = '\x01';
      pcVar8[-0xffffffff00000002] = '\0';
      pcVar8[-0xffffffff00000001] = '\0';
      pcVar8[-0xffffffff00000008] = '\0';
      pcVar8[-0xffffffff00000007] = '\0';
      pcVar8[-0xffffffff00000006] = '\0';
      pcVar8[-0xffffffff00000005] = '\0';
      pcVar8[-0xffffffff0000000c] = -0x80;
      pcVar8[-0xffffffff0000000b] = '\x02';
      pcVar8[-0xffffffff0000000a] = '\0';
      pcVar8[-0xffffffff00000009] = '\0';
      pcVar8[-0xffffffff00000010] = '\0';
      pcVar8[-0xffffffff0000000f] = '\0';
      pcVar8[-0xffffffff0000000e] = '\0';
      pcVar8[-0xffffffff0000000d] = '\0';
      pcVar8[-0xffffffff00000014] = '\b';
      pcVar8[-0xffffffff00000013] = -0x4f;
      pcVar8[-0xffffffff00000012] = '\x02';
      pcVar8[-0xffffffff00000011] = '\0';
      setclip();
      *(undefined4 *)(pcVar8 + -4) = *(undefined4 *)(pcVar8 + 0x100);
      pcVar8[-0xffffffff00000008] = '\x18';
      pcVar8[-0xffffffff00000007] = -0x4f;
      pcVar8[-0xffffffff00000006] = '\x02';
      pcVar8[-0xffffffff00000005] = '\0';
      drawshape_home();
    }
    else {
      pcVar8[-0xffffffff00000004] = -0x20;
      pcVar8[-0xffffffff00000003] = '\x01';
      pcVar8[-0xffffffff00000002] = '\0';
      pcVar8[-0xffffffff00000001] = '\0';
      pcVar8[-0xffffffff00000008] = -0x74;
      pcVar8[-0xffffffff00000007] = '\0';
      pcVar8[-0xffffffff00000006] = '\0';
      pcVar8[-0xffffffff00000005] = '\0';
      pcVar8[-0xffffffff0000000c] = -0x80;
      pcVar8[-0xffffffff0000000b] = '\x02';
      pcVar8[-0xffffffff0000000a] = '\0';
      pcVar8[-0xffffffff00000009] = '\0';
      pcVar8[-0xffffffff00000010] = -0x80;
      pcVar8[-0xffffffff0000000f] = '\0';
      pcVar8[-0xffffffff0000000e] = '\0';
      pcVar8[-0xffffffff0000000d] = '\0';
      pcVar8[-0xffffffff00000014] = -0x56;
      pcVar8[-0xffffffff00000013] = -0x50;
      pcVar8[-0xffffffff00000012] = '\x02';
      pcVar8[-0xffffffff00000011] = '\0';
      setclip();
      *(undefined4 *)(pcVar8 + -4) = *(undefined4 *)(pcVar8 + 0x100);
      pcVar8[-0xffffffff00000008] = -0x46;
      pcVar8[-0xffffffff00000007] = -0x50;
      pcVar8[-0xffffffff00000006] = '\x02';
      pcVar8[-0xffffffff00000005] = '\0';
      drawshape_home();
      pcVar8[-0xffffffff00000004] = -0x74;
      pcVar8[-0xffffffff00000003] = '\0';
      pcVar8[-0xffffffff00000002] = '\0';
      pcVar8[-0xffffffff00000001] = '\0';
      pcVar8[-0xffffffff00000008] = '\0';
      pcVar8[-0xffffffff00000007] = '\0';
      pcVar8[-0xffffffff00000006] = '\0';
      pcVar8[-0xffffffff00000005] = '\0';
      pcVar8[-0xffffffff0000000c] = -0x80;
      pcVar8[-0xffffffff0000000b] = '\0';
      pcVar8[-0xffffffff0000000a] = '\0';
      pcVar8[-0xffffffff00000009] = '\0';
      pcVar8[-0xffffffff00000010] = '\0';
      pcVar8[-0xffffffff0000000f] = '\0';
      pcVar8[-0xffffffff0000000e] = '\0';
      pcVar8[-0xffffffff0000000d] = '\0';
      pcVar8[-0xffffffff00000014] = -0x32;
      pcVar8[-0xffffffff00000013] = -0x50;
      pcVar8[-0xffffffff00000012] = '\x02';
      pcVar8[-0xffffffff00000011] = '\0';
      setclip();
      *(undefined4 *)(pcVar8 + -4) = *(undefined4 *)(pcVar8 + 0x100);
      pcVar8[-0xffffffff00000008] = -0x22;
      pcVar8[-0xffffffff00000007] = -0x50;
      pcVar8[-0xffffffff00000006] = '\x02';
      pcVar8[-0xffffffff00000005] = '\0';
      drawshape_home();
      pcVar8[-0xffffffff00000004] = -0x20;
      pcVar8[-0xffffffff00000003] = '\x01';
      pcVar8[-0xffffffff00000002] = '\0';
      pcVar8[-0xffffffff00000001] = '\0';
      pcVar8[-0xffffffff00000008] = '\0';
      pcVar8[-0xffffffff00000007] = '\0';
      pcVar8[-0xffffffff00000006] = '\0';
      pcVar8[-0xffffffff00000005] = '\0';
      pcVar8[-0xffffffff0000000c] = -0x80;
      pcVar8[-0xffffffff0000000b] = '\0';
      pcVar8[-0xffffffff0000000a] = '\0';
      pcVar8[-0xffffffff00000009] = '\0';
      pcVar8[-0xffffffff00000010] = '\0';
      pcVar8[-0xffffffff0000000f] = '\0';
      pcVar8[-0xffffffff0000000e] = '\0';
      pcVar8[-0xffffffff0000000d] = '\0';
      pcVar8[-0xffffffff00000014] = -0xe;
      pcVar8[-0xffffffff00000013] = -0x50;
      pcVar8[-0xffffffff00000012] = '\x02';
      pcVar8[-0xffffffff00000011] = '\0';
      setclip();
    }
    *(char **)(pcVar8 + -4) = pcVar8 + 0x11c;
    pcVar8[-0xffffffff00000008] = '\0';
    pcVar8[-0xffffffff00000007] = '\0';
    pcVar8[-0xffffffff00000006] = '\0';
    pcVar8[-0xffffffff00000005] = '\0';
    pcVar6 = *(char **)(pcVar8 + 0x108);
    pcVar8[-0xffffffff0000000c] = '?';
    pcVar8[-0xffffffff0000000b] = -0x4f;
    pcVar8[-0xffffffff0000000a] = '\x02';
    pcVar8[-0xffffffff00000009] = '\0';
    sub_7df4e(8,0,pcVar6,pcVar8 + 0x94);
    pcVar8[-0xffffffff00000004] = -0x20;
    pcVar8[-0xffffffff00000003] = '\x01';
    pcVar8[-0xffffffff00000002] = '\0';
    pcVar8[-0xffffffff00000001] = '\0';
    pcVar8[-0xffffffff00000008] = '\0';
    pcVar8[-0xffffffff00000007] = '\0';
    pcVar8[-0xffffffff00000006] = '\0';
    pcVar8[-0xffffffff00000005] = '\0';
    pcVar8[-0xffffffff0000000c] = -0x80;
    pcVar8[-0xffffffff0000000b] = '\x02';
    pcVar8[-0xffffffff0000000a] = '\0';
    pcVar8[-0xffffffff00000009] = '\0';
    pcVar8[-0xffffffff00000010] = '\0';
    pcVar8[-0xffffffff0000000f] = '\0';
    pcVar8[-0xffffffff0000000e] = '\0';
    pcVar8[-0xffffffff0000000d] = '\0';
    pcVar8[-0xffffffff00000014] = 'R';
    pcVar8[-0xffffffff00000013] = -0x4f;
    pcVar8[-0xffffffff00000012] = '\x02';
    pcVar8[-0xffffffff00000011] = '\0';
    setclip();
    pcVar8[-0xffffffff00000004] = 'P';
    pcVar8[-0xffffffff00000003] = '\0';
    pcVar8[-0xffffffff00000002] = '\0';
    pcVar8[-0xffffffff00000001] = '\0';
    pcVar8[-0xffffffff00000008] = '=';
    pcVar8[-0xffffffff00000007] = '\0';
    pcVar8[-0xffffffff00000006] = '\0';
    pcVar8[-0xffffffff00000005] = '\0';
    *(undefined4 *)(pcVar8 + -0xc) = *(undefined4 *)(pcVar8 + *(int *)(pcVar8 + 0x114) * 4 + 0xe0);
    pcVar8[-0xffffffff00000010] = 'm';
    pcVar8[-0xffffffff0000000f] = -0x4f;
    pcVar8[-0xffffffff0000000e] = '\x02';
    pcVar8[-0xffffffff0000000d] = '\0';
    drawshape_remap_centered();
    pcVar8[-0xffffffff00000004] = '|';
    pcVar8[-0xffffffff00000003] = -0x4f;
    pcVar8[-0xffffffff00000002] = '\x02';
    pcVar8[-0xffffffff00000001] = '\0';
    set_text_colors(0x40,0);
    pcVar8[-0xffffffff00000004] = 'T';
    pcVar8[-0xffffffff00000003] = '\x01';
    pcVar8[-0xffffffff00000002] = '\0';
    pcVar8[-0xffffffff00000001] = '\0';
    pcVar8[-0xffffffff00000008] = '\0';
    pcVar8[-0xffffffff00000007] = '\0';
    pcVar8[-0xffffffff00000006] = '\0';
    pcVar8[-0xffffffff00000005] = '\0';
    pcVar8[-0xffffffff0000000c] = -0x80;
    pcVar8[-0xffffffff0000000b] = '\x02';
    pcVar8[-0xffffffff0000000a] = '\0';
    pcVar8[-0xffffffff00000009] = '\0';
    pcVar8[-0xffffffff00000010] = '\0';
    pcVar8[-0xffffffff0000000f] = '\0';
    pcVar8[-0xffffffff0000000e] = '\0';
    pcVar8[-0xffffffff0000000d] = '\0';
    pcVar8[-0xffffffff00000014] = -0x71;
    pcVar8[-0xffffffff00000013] = -0x4f;
    pcVar8[-0xffffffff00000012] = '\x02';
    pcVar8[-0xffffffff00000011] = '\0';
    setclip();
    iVar2 = byte_d42c3 + 0xa6;
    pcVar8[0x110] = '\0';
    pcVar8[0x111] = '\0';
    pcVar8[0x112] = '\0';
    pcVar8[0x113] = '\0';
    while (*(int *)(pcVar8 + 0x110) < 4) {
      for (iVar11 = 0; iVar11 < 3; iVar11 = iVar11 + 1) {
        *(uint *)(pcVar8 + 0x118) =
             (uint)*(byte *)(iVar11 + *(int *)(pcVar8 + *(int *)(pcVar8 + 0x114) * 4 + 0xd8) +
                                      *(int *)(pcVar8 + 0x110) * 3);
        pcVar8[-0xffffffff00000004] = '#';
        pcVar8[-0xffffffff00000003] = -0x4e;
        pcVar8[-0xffffffff00000002] = '\x02';
        pcVar8[-0xffffffff00000001] = '\0';
        sub_29c75(pcVar8,0,*(int *)(pcVar8 + 0x10c) +
                           (*(int *)(pcVar8 + 0x118) + *(int *)(pcVar8 + 0x114) * 0x1c) * 0x34 +
                           0x13,200);
        *(char **)(pcVar8 + -4) = pcVar8;
        pcVar8[-0xffffffff00000008] = '+';
        pcVar8[-0xffffffff00000007] = -0x4e;
        pcVar8[-0xffffffff00000006] = '\x02';
        pcVar8[-0xffffffff00000005] = '\0';
        iVar3 = textwidth();
        pcVar8[-0xffffffff00000004] = '`';
        pcVar8[-0xffffffff00000003] = -0x4e;
        pcVar8[-0xffffffff00000002] = '\x02';
        pcVar8[-0xffffffff00000001] = '\0';
        print_text_at(iVar11 * 0x96 + 0x91 + (0x96 - iVar3) / 2,iVar2);
        pcVar6 = pcVar8;
      }
      iVar2 = iVar2 + byte_d42c3 + 0xe;
      *(int *)(pcVar8 + 0x110) = *(int *)(pcVar8 + 0x110) + 1;
    }
    if (*(int *)(pcVar8 + 0x104) == 0) {
      pcVar6 = (char *)0x10;
      pcVar8[-0xffffffff00000004] = -0x50;
      pcVar8[-0xffffffff00000003] = -0x4e;
      pcVar8[-0xffffffff00000002] = '\x02';
      pcVar8[-0xffffffff00000001] = '\0';
      fade_palette(0,*(undefined4 *)(pcVar8 + 0x108));
      pcVar7 = pcVar8;
      if (*(int *)(pcVar8 + 0x114) == 0) {
        pcVar7 = pcVar8 + -4;
        pcVar8[-0xffffffff00000004] = -0x41;
        pcVar8[-0xffffffff00000003] = -0x4e;
        pcVar8[-0xffffffff00000002] = '\x02';
        pcVar8[-0xffffffff00000001] = '\0';
        say_lineups();
      }
      *(undefined4 *)(pcVar7 + 0x104) = 0xffffffff;
      pcVar8 = pcVar7;
    }
    builtin_strncpy(pcVar8 + 0xfffffffffffffffc,"Բ\x02",4);
    uVar15 = sub_33e6a(1000);
    if ((int)uVar15 < 2) {
      pcVar8[-0xffffffff00000004] = -0x1c;
      pcVar8[-0xffffffff00000003] = -0x4e;
      pcVar8[-0xffffffff00000002] = '\x02';
      pcVar8[-0xffffffff00000001] = '\0';
      setdefaultscreen((int)uVar15,(int)((ulonglong)uVar15 >> 0x20),pcVar6);
      pcVar8[-0xffffffff00000004] = -0x20;
      pcVar8[-0xffffffff00000003] = '\x01';
      pcVar8[-0xffffffff00000002] = '\0';
      pcVar8[-0xffffffff00000001] = '\0';
      pcVar8[-0xffffffff00000008] = -0x74;
      pcVar8[-0xffffffff00000007] = '\0';
      pcVar8[-0xffffffff00000006] = '\0';
      pcVar8[-0xffffffff00000005] = '\0';
      pcVar8[-0xffffffff0000000c] = -0x80;
      pcVar8[-0xffffffff0000000b] = '\x02';
      pcVar8[-0xffffffff0000000a] = '\0';
      pcVar8[-0xffffffff00000009] = '\0';
      pcVar8[-0xffffffff00000010] = -0x80;
      pcVar8[-0xffffffff0000000f] = '\0';
      pcVar8[-0xffffffff0000000e] = '\0';
      pcVar8[-0xffffffff0000000d] = '\0';
      pcVar8[-0xffffffff00000014] = -3;
      pcVar8[-0xffffffff00000013] = -0x4e;
      pcVar8[-0xffffffff00000012] = '\x02';
      pcVar8[-0xffffffff00000011] = '\0';
      setclip();
      *(undefined4 *)(pcVar8 + -4) = *(undefined4 *)(pcVar8 + 0x100);
      pcVar8[-0xffffffff00000008] = '\r';
      pcVar8[-0xffffffff00000007] = -0x4d;
      pcVar8[-0xffffffff00000006] = '\x02';
      pcVar8[-0xffffffff00000005] = '\0';
      drawshape_home();
      pcVar8[-0xffffffff00000004] = -0x20;
      pcVar8[-0xffffffff00000003] = '\x01';
      pcVar8[-0xffffffff00000002] = '\0';
      pcVar8[-0xffffffff00000001] = '\0';
      pcVar8[-0xffffffff00000008] = -0x74;
      pcVar8[-0xffffffff00000007] = '\0';
      pcVar8[-0xffffffff00000006] = '\0';
      pcVar8[-0xffffffff00000005] = '\0';
      pcVar8[-0xffffffff0000000c] = -0x80;
      pcVar8[-0xffffffff0000000b] = '\0';
      pcVar8[-0xffffffff0000000a] = '\0';
      pcVar8[-0xffffffff00000009] = '\0';
      pcVar8[-0xffffffff00000010] = '\0';
      pcVar8[-0xffffffff0000000f] = '\0';
      pcVar8[-0xffffffff0000000e] = '\0';
      pcVar8[-0xffffffff0000000d] = '\0';
      pcVar8[-0xffffffff00000014] = '&';
      pcVar8[-0xffffffff00000013] = -0x4d;
      pcVar8[-0xffffffff00000012] = '\x02';
      pcVar8[-0xffffffff00000011] = '\0';
      setclip();
      *(char **)(pcVar8 + -4) = pcVar8 + 0x11c;
      pcVar8[-0xffffffff00000008] = '\0';
      pcVar8[-0xffffffff00000007] = '\0';
      pcVar8[-0xffffffff00000006] = '\0';
      pcVar8[-0xffffffff00000005] = '\0';
      pcVar8[-0xffffffff0000000c] = 'M';
      pcVar8[-0xffffffff0000000b] = -0x4d;
      pcVar8[-0xffffffff0000000a] = '\x02';
      pcVar8[-0xffffffff00000009] = '\0';
      sub_7df4e(0x10,0,*(undefined4 *)(pcVar8 + 0x108),pcVar8 + 0x94);
      pcVar8[-0xffffffff00000004] = 'P';
      pcVar8[-0xffffffff00000003] = '\0';
      pcVar8[-0xffffffff00000002] = '\0';
      pcVar8[-0xffffffff00000001] = '\0';
      pcVar8[-0xffffffff00000008] = '=';
      pcVar8[-0xffffffff00000007] = '\0';
      pcVar8[-0xffffffff00000006] = '\0';
      pcVar8[-0xffffffff00000005] = '\0';
      pcVar6 = *(char **)(pcVar8 + *(int *)(pcVar8 + 0x114) * 4 + 0xe0);
      *(char **)(pcVar8 + -0xc) = pcVar6;
      pcVar8[-0xffffffff00000010] = 'e';
      pcVar8[-0xffffffff0000000f] = -0x4d;
      pcVar8[-0xffffffff0000000e] = '\x02';
      pcVar8[-0xffffffff0000000d] = '\0';
      drawshape_remap_centered();
      pcVar8[-0xffffffff00000004] = -0x20;
      pcVar8[-0xffffffff00000003] = '\x01';
      pcVar8[-0xffffffff00000002] = '\0';
      pcVar8[-0xffffffff00000001] = '\0';
      pcVar8[-0xffffffff00000008] = '\0';
      pcVar8[-0xffffffff00000007] = '\0';
      pcVar8[-0xffffffff00000006] = '\0';
      pcVar8[-0xffffffff00000005] = '\0';
      pcVar8[-0xffffffff0000000c] = -0x80;
      pcVar8[-0xffffffff0000000b] = '\x02';
      pcVar8[-0xffffffff0000000a] = '\0';
      pcVar8[-0xffffffff00000009] = '\0';
      pcVar8[-0xffffffff00000010] = '\0';
      pcVar8[-0xffffffff0000000f] = '\0';
      pcVar8[-0xffffffff0000000e] = '\0';
      pcVar8[-0xffffffff0000000d] = '\0';
      pcVar8[-0xffffffff00000014] = '{';
      pcVar8[-0xffffffff00000013] = -0x4d;
      pcVar8[-0xffffffff00000012] = '\x02';
      pcVar8[-0xffffffff00000011] = '\0';
      setclip();
      iVar2 = byte_d42c3 + 0xa6;
      pcVar8[0x110] = '\0';
      pcVar8[0x111] = '\0';
      pcVar8[0x112] = '\0';
      pcVar8[0x113] = '\0';
      while (*(int *)(pcVar8 + 0x110) < 3) {
        for (iVar11 = 0; iVar11 < 2; iVar11 = iVar11 + 1) {
          *(uint *)(pcVar8 + 0x118) =
               (uint)*(byte *)(iVar11 + 0xc +
                              *(int *)(pcVar8 + 0x110) * 2 +
                              *(int *)(pcVar8 + *(int *)(pcVar8 + 0x114) * 4 + 0xd8));
          pcVar8[-0xffffffff00000004] = '\x10';
          pcVar8[-0xffffffff00000003] = -0x4c;
          pcVar8[-0xffffffff00000002] = '\x02';
          pcVar8[-0xffffffff00000001] = '\0';
          sub_29c75(pcVar8,0,*(int *)(pcVar8 + 0x10c) +
                             (*(int *)(pcVar8 + 0x118) + *(int *)(pcVar8 + 0x114) * 0x1c) * 0x34 +
                             0x13,200);
          *(char **)(pcVar8 + -4) = pcVar8;
          pcVar8[-0xffffffff00000008] = '\x18';
          pcVar8[-0xffffffff00000007] = -0x4c;
          pcVar8[-0xffffffff00000006] = '\x02';
          pcVar8[-0xffffffff00000005] = '\0';
          iVar3 = textwidth();
          pcVar8[-0xffffffff00000004] = 'G';
          pcVar8[-0xffffffff00000003] = -0x4c;
          pcVar8[-0xffffffff00000002] = '\x02';
          pcVar8[-0xffffffff00000001] = '\0';
          print_text_at(iVar11 * 0xf0 + 0x91 + (0xf0 - iVar3) / 2,iVar2);
          pcVar6 = pcVar8;
        }
        iVar2 = iVar2 + byte_d42c3 + 0xe;
        *(int *)(pcVar8 + 0x110) = *(int *)(pcVar8 + 0x110) + 1;
      }
      if (*(int *)(pcVar8 + 0x104) == 0) {
        pcVar6 = (char *)0x10;
        pcVar8[-0xffffffff00000004] = -0x69;
        pcVar8[-0xffffffff00000003] = -0x4c;
        pcVar8[-0xffffffff00000002] = '\x02';
        pcVar8[-0xffffffff00000001] = '\0';
        fade_palette(0,*(undefined4 *)(pcVar8 + 0x108));
        pcVar8[0x104] = -1;
        pcVar8[0x105] = -1;
        pcVar8[0x106] = -1;
        pcVar8[0x107] = -1;
      }
      pcVar8[-0xffffffff00000004] = -0x54;
      pcVar8[-0xffffffff00000003] = -0x4c;
      pcVar8[-0xffffffff00000002] = '\x02';
      pcVar8[-0xffffffff00000001] = '\0';
      uVar15 = sub_33e6a(1000);
    }
    if ((int)uVar15 < 2) {
      pcVar8[-0xffffffff00000004] = -0x44;
      pcVar8[-0xffffffff00000003] = -0x4c;
      pcVar8[-0xffffffff00000002] = '\x02';
      pcVar8[-0xffffffff00000001] = '\0';
      setdefaultscreen((int)uVar15,(int)((ulonglong)uVar15 >> 0x20),pcVar6);
      pcVar8[-0xffffffff00000004] = -0x20;
      pcVar8[-0xffffffff00000003] = '\x01';
      pcVar8[-0xffffffff00000002] = '\0';
      pcVar8[-0xffffffff00000001] = '\0';
      pcVar8[-0xffffffff00000008] = -0x74;
      pcVar8[-0xffffffff00000007] = '\0';
      pcVar8[-0xffffffff00000006] = '\0';
      pcVar8[-0xffffffff00000005] = '\0';
      pcVar8[-0xffffffff0000000c] = -0x80;
      pcVar8[-0xffffffff0000000b] = '\x02';
      pcVar8[-0xffffffff0000000a] = '\0';
      pcVar8[-0xffffffff00000009] = '\0';
      pcVar8[-0xffffffff00000010] = -0x80;
      pcVar8[-0xffffffff0000000f] = '\0';
      pcVar8[-0xffffffff0000000e] = '\0';
      pcVar8[-0xffffffff0000000d] = '\0';
      pcVar8[-0xffffffff00000014] = -0x2b;
      pcVar8[-0xffffffff00000013] = -0x4c;
      pcVar8[-0xffffffff00000012] = '\x02';
      pcVar8[-0xffffffff00000011] = '\0';
      setclip();
      *(undefined4 *)(pcVar8 + -4) = *(undefined4 *)(pcVar8 + 0x100);
      pcVar8[-0xffffffff00000008] = -0x1b;
      pcVar8[-0xffffffff00000007] = -0x4c;
      pcVar8[-0xffffffff00000006] = '\x02';
      pcVar8[-0xffffffff00000005] = '\0';
      drawshape_home();
      pcVar8[-0xffffffff00000004] = -0x20;
      pcVar8[-0xffffffff00000003] = '\x01';
      pcVar8[-0xffffffff00000002] = '\0';
      pcVar8[-0xffffffff00000001] = '\0';
      pcVar8[-0xffffffff00000008] = -0x74;
      pcVar8[-0xffffffff00000007] = '\0';
      pcVar8[-0xffffffff00000006] = '\0';
      pcVar8[-0xffffffff00000005] = '\0';
      pcVar8[-0xffffffff0000000c] = -0x80;
      pcVar8[-0xffffffff0000000b] = '\0';
      pcVar8[-0xffffffff0000000a] = '\0';
      pcVar8[-0xffffffff00000009] = '\0';
      pcVar8[-0xffffffff00000010] = '\0';
      pcVar8[-0xffffffff0000000f] = '\0';
      pcVar8[-0xffffffff0000000e] = '\0';
      pcVar8[-0xffffffff0000000d] = '\0';
      pcVar8[-0xffffffff00000014] = -2;
      pcVar8[-0xffffffff00000013] = -0x4c;
      pcVar8[-0xffffffff00000012] = '\x02';
      pcVar8[-0xffffffff00000011] = '\0';
      setclip();
      *(char **)(pcVar8 + -4) = pcVar8 + 0x11c;
      pcVar8[-0xffffffff00000008] = '\0';
      pcVar8[-0xffffffff00000007] = '\0';
      pcVar8[-0xffffffff00000006] = '\0';
      pcVar8[-0xffffffff00000005] = '\0';
      pcVar6 = *(char **)(pcVar8 + 0x108);
      pcVar8[-0xffffffff0000000c] = '%';
      pcVar8[-0xffffffff0000000b] = -0x4b;
      pcVar8[-0xffffffff0000000a] = '\x02';
      pcVar8[-0xffffffff00000009] = '\0';
      sub_7df4e(4,0,pcVar6,pcVar8 + 0x94);
      pcVar8[-0xffffffff00000004] = 'P';
      pcVar8[-0xffffffff00000003] = '\0';
      pcVar8[-0xffffffff00000002] = '\0';
      pcVar8[-0xffffffff00000001] = '\0';
      pcVar8[-0xffffffff00000008] = '=';
      pcVar8[-0xffffffff00000007] = '\0';
      pcVar8[-0xffffffff00000006] = '\0';
      pcVar8[-0xffffffff00000005] = '\0';
      *(undefined4 *)(pcVar8 + -0xc) = *(undefined4 *)(pcVar8 + *(int *)(pcVar8 + 0x114) * 4 + 0xe0)
      ;
      pcVar8[-0xffffffff00000010] = '=';
      pcVar8[-0xffffffff0000000f] = -0x4b;
      pcVar8[-0xffffffff0000000e] = '\x02';
      pcVar8[-0xffffffff0000000d] = '\0';
      drawshape_remap_centered();
      pcVar8[-0xffffffff00000004] = -0x20;
      pcVar8[-0xffffffff00000003] = '\x01';
      pcVar8[-0xffffffff00000002] = '\0';
      pcVar8[-0xffffffff00000001] = '\0';
      pcVar8[-0xffffffff00000008] = '\0';
      pcVar8[-0xffffffff00000007] = '\0';
      pcVar8[-0xffffffff00000006] = '\0';
      pcVar8[-0xffffffff00000005] = '\0';
      pcVar8[-0xffffffff0000000c] = -0x80;
      pcVar8[-0xffffffff0000000b] = '\x02';
      pcVar8[-0xffffffff0000000a] = '\0';
      pcVar8[-0xffffffff00000009] = '\0';
      pcVar8[-0xffffffff00000010] = '\0';
      pcVar8[-0xffffffff0000000f] = '\0';
      pcVar8[-0xffffffff0000000e] = '\0';
      pcVar8[-0xffffffff0000000d] = '\0';
      pcVar8[-0xffffffff00000014] = 'S';
      pcVar8[-0xffffffff00000013] = -0x4b;
      pcVar8[-0xffffffff00000012] = '\x02';
      pcVar8[-0xffffffff00000011] = '\0';
      setclip();
      iVar2 = byte_d42c3 + 0x7e;
      pcVar8[0x110] = '\0';
      pcVar8[0x111] = '\0';
      pcVar8[0x112] = '\0';
      pcVar8[0x113] = '\0';
      while (*(int *)(pcVar8 + 0x110) < 8) {
        uVar4 = (uint)*(byte *)(*(int *)(pcVar8 + *(int *)(pcVar8 + 0x114) * 4 + 0xd8) +
                                *(int *)(pcVar8 + 0x110) + 0x28);
        *(uint *)(pcVar8 + 0x118) = uVar4;
        if (uVar4 < 100) {
          builtin_strncpy(pcVar8 + 0xfffffffffffffffc,"ݵ\x02",4);
          sub_29c75(pcVar8,0,*(int *)(pcVar8 + 0x10c) +
                             (*(int *)(pcVar8 + 0x118) + *(int *)(pcVar8 + 0x114) * 0x1c) * 0x34 +
                             0x13,200);
          pcVar8[-0xffffffff00000004] = -0x15;
          pcVar8[-0xffffffff00000003] = -0x4b;
          pcVar8[-0xffffffff00000002] = '\x02';
          pcVar8[-0xffffffff00000001] = '\0';
          print_text_at(0xb4,iVar2,pcVar8);
          pcVar6 = (char *)(*(int *)(pcVar8 + 0x114) * 0x444);
          if (pcVar6[(int)(&rosters + *(int *)(pcVar8 + 0x118) * 0x27)] == '\x01') {
            pcVar6 = aInjured;
            pcVar8[-0xffffffff00000004] = '/';
            pcVar8[-0xffffffff00000003] = -0x4a;
            pcVar8[-0xffffffff00000002] = '\x02';
            pcVar8[-0xffffffff00000001] = '\0';
            print_text_at(0x226,iVar2);
          }
          iVar2 = iVar2 + byte_d42c3 + 0xe;
        }
        *(int *)(pcVar8 + 0x110) = *(int *)(pcVar8 + 0x110) + 1;
      }
      if (*(int *)(pcVar8 + 0x104) == 0) {
        pcVar6 = (char *)0x10;
        pcVar8[-0xffffffff00000004] = 's';
        pcVar8[-0xffffffff00000003] = -0x4a;
        pcVar8[-0xffffffff00000002] = '\x02';
        pcVar8[-0xffffffff00000001] = '\0';
        fade_palette(0,*(undefined4 *)(pcVar8 + 0x108));
        pcVar8[0x104] = -1;
        pcVar8[0x105] = -1;
        pcVar8[0x106] = -1;
        pcVar8[0x107] = -1;
      }
      pcVar8[-0xffffffff00000004] = -0x78;
      pcVar8[-0xffffffff00000003] = -0x4a;
      pcVar8[-0xffffffff00000002] = '\x02';
      pcVar8[-0xffffffff00000001] = '\0';
      uVar15 = sub_33e6a(1000);
    }
    iVar2 = (int)uVar15;
    *(int *)(pcVar8 + 0x114) = *(int *)(pcVar8 + 0x114) + 1;
  }
  *(undefined4 *)(pcVar8 + -4) = *(undefined4 *)(pcVar8 + 0x10c);
  pcVar8[-0xffffffff00000008] = -0x4b;
  pcVar8[-0xffffffff00000007] = -0x4a;
  pcVar8[-0xffffffff00000006] = '\x02';
  pcVar8[-0xffffffff00000005] = '\0';
  freemem();
  if ((sound_enabled != '\0') && (dword_c721d != 0)) {
    builtin_strncpy(pcVar8 + 0xfffffffffffffffc,"޶\x02",4);
    sound_fade(dword_d2431,3,100);
  }
  pcVar8[-0xffffffff00000004] = -0xc;
  pcVar8[-0xffffffff00000003] = -0x4a;
  pcVar8[-0xffffffff00000002] = '\x02';
  pcVar8[-0xffffffff00000001] = '\0';
  fade_palette(1,*(undefined4 *)(pcVar8 + 0x108));
  pcVar8[-0xffffffff00000004] = -7;
  pcVar8[-0xffffffff00000003] = -0x4a;
  pcVar8[-0xffffffff00000002] = '\x02';
  pcVar8[-0xffffffff00000001] = '\0';
  setdefaultscreen();
  pcVar8[-0xffffffff00000004] = '\0';
  pcVar8[-0xffffffff00000003] = '\0';
  pcVar8[-0xffffffff00000002] = '\0';
  pcVar8[-0xffffffff00000001] = '\0';
  pcVar8[-0xffffffff00000008] = '\0';
  pcVar8[-0xffffffff00000007] = -0x49;
  pcVar8[-0xffffffff00000006] = '\x02';
  pcVar8[-0xffffffff00000005] = '\0';
  clearclip();
  if ((sound_enabled != '\0') && (dword_c721d != 0)) {
    do {
      pcVar8[-0xffffffff00000004] = '\'';
      pcVar8[-0xffffffff00000003] = -0x49;
      pcVar8[-0xffffffff00000002] = '\x02';
      pcVar8[-0xffffffff00000001] = '\0';
      iVar2 = sound_channel_status(ram0x000d242c >> 0x18,3);
    } while (iVar2 == 0);
    *(int *)(pcVar8 + -4) = dword_c721d;
    pcVar8[-0xffffffff00000008] = '7';
    pcVar8[-0xffffffff00000007] = -0x49;
    pcVar8[-0xffffffff00000006] = '\x02';
    pcVar8[-0xffffffff00000005] = '\0';
    releasememblock();
    dword_c721d = 0;
  }
  if (iVar11 < 3) {
    pcVar8[-0xffffffff00000004] = 'L';
    pcVar8[-0xffffffff00000003] = -0x49;
    pcVar8[-0xffffffff00000002] = '\x02';
    pcVar8[-0xffffffff00000001] = '\0';
    loading_screen();
  }
  *(char **)(pcVar8 + -4) = pcVar8 + 0x54;
  pcVar8[-0xffffffff00000008] = 'V';
  pcVar8[-0xffffffff00000007] = -0x49;
  pcVar8[-0xffffffff00000006] = '\x02';
  pcVar8[-0xffffffff00000005] = '\0';
  setfontstate();
  *(undefined4 *)(pcVar8 + -4) = *(undefined4 *)(pcVar8 + 0xf4);
  pcVar8[-0xffffffff00000008] = 'f';
  pcVar8[-0xffffffff00000007] = -0x49;
  pcVar8[-0xffffffff00000006] = '\x02';
  pcVar8[-0xffffffff00000005] = '\0';
  freemem();
  *(undefined4 *)(pcVar8 + -4) = *(undefined4 *)(pcVar8 + 0xf8);
  pcVar8[-0xffffffff00000008] = 'v';
  pcVar8[-0xffffffff00000007] = -0x49;
  pcVar8[-0xffffffff00000006] = '\x02';
  pcVar8[-0xffffffff00000005] = '\0';
  freemem();
  *(undefined4 *)(pcVar8 + -4) = *(undefined4 *)(pcVar8 + 0xf0);
  pcVar8[-0xffffffff00000008] = -0x7a;
  pcVar8[-0xffffffff00000007] = -0x49;
  pcVar8[-0xffffffff00000006] = '\x02';
  pcVar8[-0xffffffff00000005] = '\0';
  freemem();
  *(undefined4 *)(pcVar8 + -4) = *(undefined4 *)(pcVar8 + 0xe0);
  pcVar8[-0xffffffff00000008] = -0x6a;
  pcVar8[-0xffffffff00000007] = -0x49;
  pcVar8[-0xffffffff00000006] = '\x02';
  pcVar8[-0xffffffff00000005] = '\0';
  freemem();
  *(undefined4 *)(pcVar8 + -4) = *(undefined4 *)(pcVar8 + 0xe4);
  pcVar8[-0xffffffff00000008] = -0x5a;
  pcVar8[-0xffffffff00000007] = -0x49;
  pcVar8[-0xffffffff00000006] = '\x02';
  pcVar8[-0xffffffff00000005] = '\0';
  freemem();
  return iVar11;
}


// ================================================================================================
// league_select_buttons @ 0x2b7c3 [__watcall]
// ================================================================================================

void __watcall league_select_buttons(void)

{
  undefined *puVar1;
  undefined auStack_38 [32];
  
  __CHK(0x44);
  if (dword_c6f78 == 0) {
    puVar1 = (undefined *)0x0;
    if (byte_ed992 == '\x01') {
      puVar1 = install_path;
    }
    make_path(auStack_38,puVar1,aOpenBut,0);
    dword_c6f78 = loadshapes(auStack_38,0);
    dword_dd638 = locateshape(dword_c6f78,&aNone);
    dword_dd644 = locateshape(dword_c6f78,&aDel);
    dword_dd640 = locateshape(dword_c6f78,&aOpen);
    dword_dd64c = locateshape(dword_c6f78,&aCan);
    dword_dd664 = locateshape(dword_c6f78,&aNoar);
    dword_dd648 = locateshape(dword_c6f78,&aUp);
    dword_dd654 = locateshape(dword_c6f78,&aDown);
    dword_dd65c = locateshape(dword_c6f78,&aArro);
    dword_dd650 = locateshape(dword_c6f78,&aGtno);
    dword_dd634 = locateshape(dword_c6f78,&aGtex);
    dword_dd660 = locateshape(dword_c6f78,&aGtlp);
    dword_dd63c = locateshape(dword_c6f78,&aGtpo);
  }
  return;
}


// ================================================================================================
// league_select_screen @ 0x2b944 [__watcall]
// ================================================================================================

undefined4 __watcall league_select_screen(void)

{
  char *pcVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 extraout_EDX;
  char *__dest;
  undefined4 *puVar6;
  undefined4 *puVar7;
  int iVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  byte bVar11;
  undefined4 auStack_4c [14];
  
  bVar11 = 0;
  __CHK(0x58);
  auStack_4c[0] = 0x2b95b;
  scan_league_dirs();
  auStack_4c[0] = 0x20;
  puVar2 = (undefined4 *)allocmem(&aBuf,0xb825);
  puVar9 = puVar2 + (uint)bVar11 * -2 + 1;
  puVar6 = pointer_shapes + (uint)bVar11 * -2 + 1;
  *puVar2 = *pointer_shapes;
  puVar10 = puVar9 + (uint)bVar11 * -2 + 1;
  puVar7 = puVar6 + (uint)bVar11 * -2 + 1;
  *puVar9 = *puVar6;
  *puVar10 = *puVar7;
  puVar10[(uint)bVar11 * -2 + 1] = puVar7[(uint)bVar11 * -2 + 1];
  *(undefined *)(puVar10 + (uint)bVar11 * -2 + 1 + (uint)bVar11 * -2 + 1) =
       *(undefined *)(puVar7 + (uint)bVar11 * -2 + 1 + (uint)bVar11 * -2 + 1);
  *(undefined2 *)(puVar2 + 1) = 0xee;
  *(undefined2 *)((int)puVar2 + 6) = 0xc6;
  auStack_4c[0] = 0x13;
  grabshape(puVar2,10);
  auStack_4c[0] = 0x2b99c;
  league_select_buttons();
  __dest = (char *)auStack_4c;
  auStack_4c[0] = 0x2b9a1;
  league_dialog_box();
  __dest[-0xffffffff00000004] = -0x5a;
  __dest[-0xffffffff00000003] = -0x47;
  __dest[-0xffffffff00000002] = '\x02';
  __dest[-0xffffffff00000001] = '\0';
  league_type_menu();
  __dest[-0xffffffff00000004] = -0x55;
  __dest[-0xffffffff00000003] = -0x47;
  __dest[-0xffffffff00000002] = '\x02';
  __dest[-0xffffffff00000001] = '\0';
  iVar3 = league_name_entry();
  __dest[-0xffffffff00000004] = '\x13';
  __dest[-0xffffffff00000003] = '\0';
  __dest[-0xffffffff00000002] = '\0';
  __dest[-0xffffffff00000001] = '\0';
  __dest[-0xffffffff00000008] = '\n';
  __dest[-0xffffffff00000007] = '\0';
  __dest[-0xffffffff00000006] = '\0';
  __dest[-0xffffffff00000005] = '\0';
  *(undefined4 **)(__dest + -0xc) = puVar2;
  __dest[-0xffffffff00000010] = -0x49;
  __dest[-0xffffffff0000000f] = -0x47;
  __dest[-0xffffffff0000000e] = '\x02';
  __dest[-0xffffffff0000000d] = '\0';
  drawshape2();
  *(undefined4 **)(__dest + -4) = puVar2;
  __dest[-0xffffffff00000008] = -0x40;
  __dest[-0xffffffff00000007] = -0x47;
  __dest[-0xffffffff00000006] = '\x02';
  __dest[-0xffffffff00000005] = '\0';
  freemem();
  *(undefined4 *)(__dest + -4) = dword_c6f78;
  __dest[-0xffffffff00000008] = -0x31;
  __dest[-0xffffffff00000007] = -0x47;
  __dest[-0xffffffff00000006] = '\x02';
  __dest[-0xffffffff00000005] = '\0';
  freemem();
  dword_c6f78 = 0;
  __dest[-0xffffffff00000004] = -0x21;
  __dest[-0xffffffff00000003] = -0x47;
  __dest[-0xffffffff00000002] = '\x02';
  __dest[-0xffffffff00000001] = '\0';
  sub_1d518();
  __dest[-0xffffffff00000004] = -0x1a;
  __dest[-0xffffffff00000003] = -0x47;
  __dest[-0xffffffff00000002] = '\x02';
  __dest[-0xffffffff00000001] = '\0';
  set_menu_mode(0);
  if (iVar3 == 0) {
LAB_0002bd0b:
    uVar5 = 0;
  }
  else {
    if (dword_dd658 == 0) {
      __dest[-0xffffffff00000004] = '\x1e';
      __dest[-0xffffffff00000003] = -0x46;
      __dest[-0xffffffff00000002] = '\x02';
      __dest[-0xffffffff00000001] = '\0';
      set_menu_mode(1);
      pcVar1 = (char *)(&unk_dd254)[dword_dd248];
      __dest[-0xffffffff00000004] = '1';
      __dest[-0xffffffff00000003] = -0x46;
      __dest[-0xffffffff00000002] = '\x02';
      __dest[-0xffffffff00000001] = '\0';
      strcpy(__dest,pcVar1);
      __dest[-0xffffffff00000004] = '=';
      __dest[-0xffffffff00000003] = -0x46;
      __dest[-0xffffffff00000002] = '\x02';
      __dest[-0xffffffff00000001] = '\0';
      strcat(__dest,(char *)&aNhl);
      __dest[-0xffffffff00000004] = 'H';
      __dest[-0xffffffff00000003] = -0x46;
      __dest[-0xffffffff00000002] = '\x02';
      __dest[-0xffffffff00000001] = '\0';
      iVar3 = file_open_read(__dest,__dest + 0x30);
      if (iVar3 != 0) {
        *(undefined3 **)(__dest + -4) = &aK1;
        __dest[-0xffffffff00000008] = 'V';
        __dest[-0xffffffff00000007] = -0x46;
        __dest[-0xffffffff00000006] = '\x02';
        __dest[-0xffffffff00000005] = '\0';
        fatalerror();
      }
      __dest[-0xffffffff00000004] = 'g';
      __dest[-0xffffffff00000003] = -0x46;
      __dest[-0xffffffff00000002] = '\x02';
      __dest[-0xffffffff00000001] = '\0';
      iVar3 = sub_14566(aGsummaryDb_c148e,__dest + 0x2c);
      if (iVar3 != 0) {
        *(undefined3 **)(__dest + -4) = &aK2;
        __dest[-0xffffffff00000008] = 'u';
        __dest[-0xffffffff00000007] = -0x46;
        __dest[-0xffffffff00000006] = '\x02';
        __dest[-0xffffffff00000005] = '\0';
        fatalerror();
      }
      __dest[-0xffffffff00000004] = -0x71;
      __dest[-0xffffffff00000003] = -0x46;
      __dest[-0xffffffff00000002] = '\x02';
      __dest[-0xffffffff00000001] = '\0';
      iVar3 = file_read(*(undefined4 *)(__dest + 0x30),__dest + 0x20,0x75,0xb);
      if (iVar3 != 0) {
        *(undefined3 **)(__dest + -4) = &aK3;
        __dest[-0xffffffff00000008] = -99;
        __dest[-0xffffffff00000007] = -0x46;
        __dest[-0xffffffff00000006] = '\x02';
        __dest[-0xffffffff00000005] = '\0';
        fatalerror();
      }
      __dest[-0xffffffff00000004] = -0x49;
      __dest[-0xffffffff00000003] = -0x46;
      __dest[-0xffffffff00000002] = '\x02';
      __dest[-0xffffffff00000001] = '\0';
      iVar3 = file_write(*(undefined4 *)(__dest + 0x2c),__dest + 0x20,0xffffffff,0xb);
      if (iVar3 != 0) {
        *(undefined3 **)(__dest + -4) = &aK4;
        __dest[-0xffffffff00000008] = -0x3b;
        __dest[-0xffffffff00000007] = -0x46;
        __dest[-0xffffffff00000006] = '\x02';
        __dest[-0xffffffff00000005] = '\0';
        fatalerror();
      }
      iVar3 = *(int *)(__dest + 0x23);
      for (iVar8 = 0; iVar8 < iVar3 >> 0x10; iVar8 = iVar8 + 1) {
        __dest[-0xffffffff00000004] = -0x16;
        __dest[-0xffffffff00000003] = -0x46;
        __dest[-0xffffffff00000002] = '\x02';
        __dest[-0xffffffff00000001] = '\0';
        iVar4 = file_read(*(undefined4 *)(__dest + 0x30),__dest + 0x20,0xffffffff,0xb);
        if (iVar4 != 0) {
          *(undefined3 **)(__dest + -4) = &aK5;
          __dest[-0xffffffff00000008] = -8;
          __dest[-0xffffffff00000007] = -0x46;
          __dest[-0xffffffff00000006] = '\x02';
          __dest[-0xffffffff00000005] = '\0';
          fatalerror();
        }
        __dest[-0xffffffff00000004] = '\x12';
        __dest[-0xffffffff00000003] = -0x45;
        __dest[-0xffffffff00000002] = '\x02';
        __dest[-0xffffffff00000001] = '\0';
        iVar4 = file_write(*(undefined4 *)(__dest + 0x2c),__dest + 0x20,0xffffffff,0xb);
        if (iVar4 != 0) {
          *(undefined3 **)(__dest + -4) = &aK6;
          __dest[-0xffffffff00000008] = ' ';
          __dest[-0xffffffff00000007] = -0x45;
          __dest[-0xffffffff00000006] = '\x02';
          __dest[-0xffffffff00000005] = '\0';
          fatalerror();
        }
      }
      __dest[-0xffffffff00000004] = '1';
      __dest[-0xffffffff00000003] = -0x45;
      __dest[-0xffffffff00000002] = '\x02';
      __dest[-0xffffffff00000001] = '\0';
      file_close(__dest + 0x2c);
      __dest[-0xffffffff00000004] = 'I';
      __dest[-0xffffffff00000003] = -0x45;
      __dest[-0xffffffff00000002] = '\x02';
      __dest[-0xffffffff00000001] = '\0';
      iVar3 = file_read(*(undefined4 *)(__dest + 0x30),&unk_dd774,0xffffffff,0xc);
      if (iVar3 != 0) {
        *(undefined3 **)(__dest + -4) = &aK7;
        __dest[-0xffffffff00000008] = 'W';
        __dest[-0xffffffff00000007] = -0x45;
        __dest[-0xffffffff00000006] = '\x02';
        __dest[-0xffffffff00000005] = '\0';
        fatalerror();
      }
      __dest[-0xffffffff00000004] = 'r';
      __dest[-0xffffffff00000003] = -0x45;
      __dest[-0xffffffff00000002] = '\x02';
      __dest[-0xffffffff00000001] = '\0';
      iVar3 = file_read(*(undefined4 *)(__dest + 0x30),&unk_dd788,0xffffffff,0xc);
      if (iVar3 != 0) {
        *(undefined3 **)(__dest + -4) = &aK8;
        __dest[-0xffffffff00000008] = -0x80;
        __dest[-0xffffffff00000007] = -0x45;
        __dest[-0xffffffff00000006] = '\x02';
        __dest[-0xffffffff00000005] = '\0';
        fatalerror();
      }
      __dest[-0xffffffff00000004] = -0x65;
      __dest[-0xffffffff00000003] = -0x45;
      __dest[-0xffffffff00000002] = '\x02';
      __dest[-0xffffffff00000001] = '\0';
      iVar3 = file_read(*(undefined4 *)(__dest + 0x30),&unk_dd730,0xffffffff,0x18);
      if (iVar3 != 0) {
        *(undefined3 **)(__dest + -4) = &aH7;
        __dest[-0xffffffff00000008] = -0x57;
        __dest[-0xffffffff00000007] = -0x45;
        __dest[-0xffffffff00000006] = '\x02';
        __dest[-0xffffffff00000005] = '\0';
        fatalerror();
      }
      byte_c52f2 = byte_c52f2 & 0x7f;
      __dest[-0xffffffff00000004] = -0x44;
      __dest[-0xffffffff00000003] = -0x45;
      __dest[-0xffffffff00000002] = '\x02';
      __dest[-0xffffffff00000001] = '\0';
      uVar5 = exhibition_mode(__dest + 0x30);
      builtin_strncpy(__dest + 0xfffffffffffffffc,"Ż\x02",4);
      set_menu_mode(0,uVar5);
      return extraout_EDX;
    }
    if (dword_dd658 < 2) {
      *(undefined1 **)(__dest + -4) = &byte_c5311;
      __dest[-0xffffffff00000008] = -0x16;
      __dest[-0xffffffff00000007] = -0x45;
      __dest[-0xffffffff00000006] = '\x02';
      __dest[-0xffffffff00000005] = '\0';
      iVar3 = sub_1466b(aGsummary,&aSav,&aDb,&byte_c5311);
      if (iVar3 != 0) {
        *(undefined3 **)(__dest + -4) = &aA1;
        __dest[-0xffffffff00000008] = -8;
        __dest[-0xffffffff00000007] = -0x45;
        __dest[-0xffffffff00000006] = '\x02';
        __dest[-0xffffffff00000005] = '\0';
        fatalerror();
      }
      __dest[-0xffffffff00000004] = '\x05';
      __dest[-0xffffffff00000003] = -0x44;
      __dest[-0xffffffff00000002] = '\x02';
      __dest[-0xffffffff00000001] = '\0';
      set_menu_mode(2);
      pcVar1 = (char *)(&unk_dd1c4)[dword_dd1b8];
      __dest[-0xffffffff00000004] = '\x18';
      __dest[-0xffffffff00000003] = -0x44;
      __dest[-0xffffffff00000002] = '\x02';
      __dest[-0xffffffff00000001] = '\0';
      strcpy(__dest,pcVar1);
      __dest[-0xffffffff00000004] = '$';
      __dest[-0xffffffff00000003] = -0x44;
      __dest[-0xffffffff00000002] = '\x02';
      __dest[-0xffffffff00000001] = '\0';
      strcat(__dest,aPoGameSav);
      __dest[-0xffffffff00000004] = '/';
      __dest[-0xffffffff00000003] = -0x44;
      __dest[-0xffffffff00000002] = '\x02';
      __dest[-0xffffffff00000001] = '\0';
      iVar3 = file_open_read(__dest,__dest + 0x30);
      if (iVar3 != 0) {
        *(undefined3 **)(__dest + -4) = &aL1;
        __dest[-0xffffffff00000008] = '=';
        __dest[-0xffffffff00000007] = -0x44;
        __dest[-0xffffffff00000006] = '\x02';
        __dest[-0xffffffff00000005] = '\0';
        fatalerror();
      }
      word_c5366._1_1_ = word_c5366._1_1_ & 0x7f;
      __dest[-0xffffffff00000004] = 'P';
      __dest[-0xffffffff00000003] = -0x44;
      __dest[-0xffffffff00000002] = '\x02';
      __dest[-0xffffffff00000001] = '\0';
      uVar5 = playoff_tree_screen(__dest + 0x30);
      bVar11 = word_c5366._1_1_;
    }
    else {
      if (dword_dd658 != 2) goto LAB_0002bd0b;
      *(undefined1 **)(__dest + -4) = &byte_c5386;
      __dest[-0xffffffff00000008] = -0x69;
      __dest[-0xffffffff00000007] = -0x44;
      __dest[-0xffffffff00000006] = '\x02';
      __dest[-0xffffffff00000005] = '\0';
      iVar3 = sub_1466b(aGsummary,&aSav,&aDb,&byte_c5386);
      if (iVar3 != 0) {
        *(undefined3 **)(__dest + -4) = &aA2;
        __dest[-0xffffffff00000008] = -0x5b;
        __dest[-0xffffffff00000007] = -0x44;
        __dest[-0xffffffff00000006] = '\x02';
        __dest[-0xffffffff00000005] = '\0';
        fatalerror();
      }
      __dest[-0xffffffff00000004] = -0x4e;
      __dest[-0xffffffff00000003] = -0x44;
      __dest[-0xffffffff00000002] = '\x02';
      __dest[-0xffffffff00000001] = '\0';
      set_menu_mode(3);
      puVar2 = &unk_dd134 + dword_dd128;
      builtin_strncpy(__dest + 0xfffffffffffffffc,"ż\x02",4);
      strcpy(__dest,(char *)*puVar2);
      builtin_strncpy(__dest + 0xfffffffffffffffc,"Ѽ\x02",4);
      strcat(__dest,aLpGameSav);
      builtin_strncpy(__dest + 0xfffffffffffffffc,"ܼ\x02",4);
      iVar3 = file_open_read(__dest,__dest + 0x30);
      if (iVar3 != 0) {
        *(undefined3 **)(__dest + -4) = &aL2;
        __dest[-0xffffffff00000008] = -0x16;
        __dest[-0xffffffff00000007] = -0x44;
        __dest[-0xffffffff00000006] = '\x02';
        __dest[-0xffffffff00000005] = '\0';
        fatalerror();
      }
      word_c53db._1_1_ = word_c53db._1_1_ & 0x7f;
      __dest[-0xffffffff00000004] = -3;
      __dest[-0xffffffff00000003] = -0x44;
      __dest[-0xffffffff00000002] = '\x02';
      __dest[-0xffffffff00000001] = '\0';
      uVar5 = league_calendar_screen(__dest + 0x30);
      bVar11 = word_c53db._1_1_;
    }
    if (((bVar11 & 0x80) == 0) && (dword_c53f7 == 1)) {
      __dest[-0xffffffff00000004] = 'k';
      __dest[-0xffffffff00000003] = -0x44;
      __dest[-0xffffffff00000002] = '\x02';
      __dest[-0xffffffff00000001] = '\0';
      sub_903e8(__dest);
    }
    __dest[-0xffffffff00000004] = 'r';
    __dest[-0xffffffff00000003] = -0x44;
    __dest[-0xffffffff00000002] = '\x02';
    __dest[-0xffffffff00000001] = '\0';
    set_menu_mode(0);
  }
  return uVar5;
}


// ================================================================================================
// league_type_menu @ 0x2bd16 [__watcall]
// ================================================================================================

void __watcall league_type_menu(void)

{
  undefined4 uVar1;
  
  __CHK(0x28);
  settextpos(0xf8,0xff);
  if ((int)dword_dd658 < 0) {
    printstr_at(&aOpen_c14ea,0x2a,0xc0);
    printstr_at(aDelete,0x6b,0xc0);
    settextpos(0xfa,0xff);
    printstr_at(&aDone,0xb8,0xc0);
    settextpos(0xf8,0xff);
    printstr_at(aExhibition,0xa7,0x4c);
    printstr_at(aPlayoffs,0xab,100);
    printstr_at(aLeague,0xb0,0x7c);
    drawshape_remap(dword_dd664,0x18,0x46);
    uVar1 = dword_dd650;
  }
  else {
    if (((byte)dword_dd668 & 0x80) == 0) {
      printstr_at(aLeague,0xb0,0x7c);
    }
    if (((byte)dword_dd668 & 0x40) == 0) {
      printstr_at(aPlayoffs,0xab,100);
    }
    if (((byte)dword_dd668 & 0x20) == 0) {
      printstr2_at(aExhibition,0xa7,0x4c);
    }
    uVar1 = dword_dd65c;
    if (*(int *)(&off_c6f7c)[dword_dd658] < 7) {
      uVar1 = dword_dd664;
    }
    drawshape_remap(uVar1,0x18,0x46);
    uVar1 = dword_dd634;
    if (((dword_dd658 != 0) && (uVar1 = dword_dd63c, 1 < dword_dd658)) &&
       (uVar1 = dword_dd660, dword_dd658 != 2)) {
      return;
    }
  }
  drawshape_remap(uVar1,0xa3,0x4b);
  return;
}


// ================================================================================================
// sub_2beea @ 0x2beea [__watcall]
// ================================================================================================

void __watcall sub_2beea(undefined4 *param_1,undefined4 *unaff_EDX)

{
  __CHK(4);
  strcmp((char *)*param_1,(char *)*unaff_EDX);
  return;
}


// ================================================================================================
// scan_league_dirs @ 0x2befd [__watcall]
// ================================================================================================

void __watcall scan_league_dirs(void)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined auStackY_44 [30];
  char acStackY_26 [14];
  
  __CHK(0x48);
  iVar3 = 0;
  dword_dd124 = 0;
  iVar2 = _dos_findfirst(&aLp,0x10);
  if (iVar2 == 0) {
    do {
      (&unk_dd134)[dword_dd124] = (int)&unk_dd2d4 + iVar3;
      iVar2 = 0;
      do {
        cVar1 = acStackY_26[iVar2];
        if ((cVar1 == '\0') || (cVar1 == '.')) break;
        *(char *)((int)&unk_dd2d4 + iVar3) = cVar1;
        iVar2 = iVar2 + 1;
        iVar3 = iVar3 + 1;
      } while (iVar2 < 8);
      *(undefined *)((int)&unk_dd2d4 + iVar3) = 0;
      iVar3 = iVar3 + 1;
      dword_dd124 = dword_dd124 + 1;
    } while ((dword_dd124 < 0x20) && (iVar2 = _dos_findnext(auStackY_44), iVar2 == 0));
    sub_9244c(&unk_dd134,dword_dd124,4);
    dword_dd12c = 0;
    dword_dd128 = 0;
    if (dword_dd124 < 6) {
      dword_dd130 = dword_dd124 + -1;
    }
    else {
      dword_dd130 = 5;
    }
  }
  dword_dd1b4 = 0;
  iVar2 = _dos_findfirst(&aPo,0x10);
  if (iVar2 == 0) {
    do {
      (&unk_dd1c4)[dword_dd1b4] = (int)&unk_dd2d4 + iVar3;
      iVar2 = 0;
      do {
        cVar1 = acStackY_26[iVar2];
        if ((cVar1 == '\0') || (cVar1 == '.')) break;
        *(char *)((int)&unk_dd2d4 + iVar3) = cVar1;
        iVar2 = iVar2 + 1;
        iVar3 = iVar3 + 1;
      } while (iVar2 < 8);
      *(undefined *)((int)&unk_dd2d4 + iVar3) = 0;
      iVar3 = iVar3 + 1;
      dword_dd1b4 = dword_dd1b4 + 1;
    } while ((dword_dd1b4 < 0x20) && (iVar2 = _dos_findnext(auStackY_44), iVar2 == 0));
    sub_9244c(&unk_dd1c4,dword_dd1b4,4,sub_2beea);
    dword_dd1bc = 0;
    dword_dd1b8 = 0;
    if (dword_dd1b4 < 6) {
      dword_dd1c0 = dword_dd1b4 + -1;
    }
    else {
      dword_dd1c0 = 5;
    }
  }
  dword_dd244 = 0;
  iVar2 = _dos_findfirst(aNhl_c1520);
  if (iVar2 == 0) {
    do {
      (&unk_dd254)[dword_dd244] = (int)&unk_dd2d4 + iVar3;
      iVar2 = 0;
      do {
        cVar1 = acStackY_26[iVar2];
        if ((cVar1 == '\0') || (cVar1 == '.')) break;
        *(char *)((int)&unk_dd2d4 + iVar3) = cVar1;
        iVar2 = iVar2 + 1;
        iVar3 = iVar3 + 1;
      } while (iVar2 < 8);
      *(undefined *)((int)&unk_dd2d4 + iVar3) = 0;
      iVar3 = iVar3 + 1;
      dword_dd244 = dword_dd244 + 1;
    } while ((dword_dd244 < 0x20) && (iVar2 = _dos_findnext(auStackY_44), iVar2 == 0));
    sub_9244c(&unk_dd254,dword_dd244,4,sub_2beea);
    dword_dd24c = 0;
    dword_dd248 = 0;
    if (dword_dd244 < 6) {
      dword_dd250 = dword_dd244 + -1;
    }
    else {
      dword_dd250 = 5;
    }
  }
  return;
}


// ================================================================================================
// sub_2c135 @ 0x2c135 [__watcall]
// ================================================================================================

void __watcall sub_2c135(int param_1,undefined4 unaff_EDX,undefined4 unaff_EBX)

{
  int iVar1;
  char acStack_48 [64];
  
  __CHK(0x58);
  for (iVar1 = 0; *(char *)(param_1 + iVar1) != '\0'; iVar1 = iVar1 + 1) {
    acStack_48[iVar1] = *(char *)(param_1 + iVar1);
  }
  acStack_48[iVar1] = '\0';
  printstr_at(acStack_48,unaff_EDX,unaff_EBX);
  return;
}


// ================================================================================================
// league_dialog_box @ 0x2c18f [__watcall]
// ================================================================================================

void __watcall league_dialog_box(void)

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
  if (byte_ed82f != '\x01') {
    puVar6 = (undefined *)0x0;
  }
  make_path(auStack_3c,puVar6,aDialogbx,0);
  uVar4 = loadshapes(auStack_3c,0);
  uVar5 = locateshape(uVar4,&aDbox,10,0x13);
  drawshape2_remap(uVar5);
  freemem(uVar4);
  dword_dd668 = 0x10;
  dword_dd658 = -1;
  if (dword_dd124 != 0) {
    dword_dd668 = 0x90;
    dword_dd658 = 2;
  }
  if (dword_dd1b4 != 0) {
    dword_dd668 = dword_dd668 | 0x40;
    dword_dd658 = 1;
  }
  if (dword_dd244 != 0) {
    dword_dd668 = dword_dd668 | 0x20;
    dword_dd658 = 0;
  }
  if (-1 < dword_dd658) {
    dword_dd668 = dword_dd668 | 0x20c;
    settextpos(0xfa,0xff);
    piVar1 = (int *)(&off_c6f7c)[dword_dd658];
    sub_2c135(piVar1[piVar1[1] + 4],dword_c7018 + 0xd,dword_c701c + 0x13);
    fillrect(dword_c7028 + 10,dword_c702c + 0x13,(dword_c7030 - dword_c7028) + 1,
             (dword_c7034 - dword_c702c) + 1,0xf8);
    iVar8 = 10;
    for (iVar7 = piVar1[2]; iVar3 = dword_c700c, iVar2 = dword_c7008, iVar7 <= piVar1[3];
        iVar7 = iVar7 + 1) {
      sub_2c135(piVar1[iVar7 + 4],(&unk_c6f88)[iVar8 * 4] + 10,(&unk_c6f8c)[iVar8 * 4] + 0x10);
      iVar8 = iVar8 + 1;
    }
    if (6 < *piVar1) {
      dword_dd668 = dword_dd668 | 0xff03;
      iVar7 = dword_c7008 + 10;
      iVar9 = dword_c700c + 0x13;
      iStack_1c = dword_c7010 + 10;
      iVar8 = dword_c700c + 0x11 + (int)(0x1e0 / (longlong)*piVar1);
      sub_b4fac(iVar7,iVar9,dword_c7010 + 9,iVar9,0xfa);
      sub_b4fac(iVar7,iVar9,iVar7,iVar8 + -1,0xfa);
      iVar7 = iStack_1c;
      sub_b4fac(iStack_1c,iVar3 + 0x12,iStack_1c,iVar8,0xf8);
      sub_b4fac(iVar2 + 9,iVar8,iVar7,iVar8,0xf8);
      FUN_0002c3f7();
      return;
    }
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
  return;
}


// ================================================================================================
// FUN_0002c3f7 @ 0x2c3f7
// ================================================================================================

void FUN_0002c3f7(void)

{
  return;
}


// ================================================================================================
// sub_2c3ff @ 0x2c3ff [__watcall]
// ================================================================================================

undefined4 __watcall sub_2c3ff(int param_1,int unaff_EDX,int *unaff_EBX)

{
  int iVar1;
  
  __CHK(0xc);
  iVar1 = 0;
  while ((((param_1 + -6 < (int)(&unk_c6f88)[iVar1 * 4] ||
           ((int)(&unk_c6f90)[iVar1 * 4] < param_1 + -6)) ||
          (unaff_EDX + -0x13 < (int)(&unk_c6f8c)[iVar1 * 4])) ||
         ((int)(&unk_c6f94)[iVar1 * 4] < unaff_EDX + -0x13))) {
    iVar1 = iVar1 + 1;
    if (0xf < iVar1) {
      return 0;
    }
  }
  *unaff_EBX = iVar1;
  return 1;
}


// ================================================================================================
// sub_2c46b @ 0x2c46b [__watcall]
// ================================================================================================

undefined8 __watcall sub_2c46b(int *param_1,undefined4 unaff_EDX)

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
  iVar3 = 0;
  do {
    fillrect((&dword_c7028)[iVar3 * 4] + 10,(&dword_c702c)[iVar3 * 4] + 0x13,
             ((&dword_c7030)[iVar3 * 4] - (&dword_c7028)[iVar3 * 4]) + 1,
             ((&dword_c7034)[iVar3 * 4] - (&dword_c702c)[iVar3 * 4]) + 1,0xf9);
    iVar3 = iVar3 + 1;
  } while (iVar3 < 6);
  if (param_1 == (int *)0x0) {
    fillrect(dword_c7018 + 0xd,dword_c701c + 0x16,(dword_c7020 - dword_c7018) + -5,
             (dword_c7024 - dword_c701c) + -5,0xf8);
    uStack_1c = 0;
  }
  else {
    if (*param_1 < 7) {
      for (iVar3 = 0; iVar3 < *param_1; iVar3 = iVar3 + 1) {
        sub_2c135(param_1[iVar3 + 4],(&dword_c7028)[iVar3 * 4] + 10,(&dword_c702c)[iVar3 * 4] + 0x10
                 );
      }
    }
    else {
      iVar3 = 0;
      do {
        sub_2c135(param_1[param_1[2] + iVar3 + 4],(&dword_c7028)[iVar3 * 4] + 10,
                  (&dword_c702c)[iVar3 * 4] + 0x10);
        iVar3 = iVar3 + 1;
      } while (iVar3 < 6);
    }
    if (0 < *param_1) {
      fillrect(dword_c7018 + 0xd,dword_c701c + 0x16,(dword_c7020 - dword_c7018) + -5,
               (dword_c7024 - dword_c701c) + -5,0xf8);
      sub_2c135(param_1[param_1[1] + 4],dword_c7018 + 0xd,dword_c701c + 0x13);
    }
    iVar3 = param_1[1];
    if ((param_1[2] <= iVar3) && (iVar3 <= param_1[3])) {
      iVar3 = iVar3 - param_1[2];
      fillrect((&dword_c7028)[iVar3 * 4] + 10,(&dword_c702c)[iVar3 * 4] + 0x13,
               (&dword_c7030)[iVar3 * 4] - (&dword_c7028)[iVar3 * 4],
               (&dword_c7034)[iVar3 * 4] - (&dword_c702c)[iVar3 * 4],0xf8);
      sub_2c135(param_1[param_1[2] + iVar3 + 4],(&dword_c7028)[iVar3 * 4] + 10,
                (&dword_c702c)[iVar3 * 4] + 0x10);
    }
    fillrect(dword_c7008 + 10,dword_c700c + 0x13,(dword_c7010 - dword_c7008) + 1,
             (dword_c7014 - dword_c700c) + 1,0xf9);
    iVar3 = dword_c7008;
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
      iVar4 = dword_c7008 + 10;
      iVar2 = dword_c700c + 0x13 + (param_1[2] * 0x50) / *param_1;
      iVar1 = dword_c7010 + 10;
      iVar5 = dword_c700c + 0x12 + ((param_1[3] + 1) * 0x50) / *param_1;
      sub_b4fac(iVar4,iVar2,dword_c7010 + 9,iVar2,0xfa,iVar1);
      sub_b4fac(iVar4,iVar2,iVar4,iVar5 + -1,0xfa);
      sub_b4fac(iVar1,iVar2 + 1,iVar1,iVar5,0xf8);
      sub_b4fac(iVar3 + 0xb,iVar5,iVar1,iVar5,0xf8);
    }
    uVar6 = dword_dd65c;
    if (*(int *)(&off_c6f7c)[dword_dd658] < 7) {
      uVar6 = dword_dd664;
    }
    drawshape_remap(uVar6,0x18,0x46);
    uVar6 = dword_dd634;
    if (((dword_dd658 == 0) || (uVar6 = dword_dd63c, dword_dd658 < 2)) ||
       (uVar6 = dword_dd660, dword_dd658 == 2)) {
      drawshape_remap(uVar6,0xa3,0x4b);
    }
  }
  return CONCAT44(unaff_EDX,uStack_1c);
}


// ================================================================================================
// league_name_entry @ 0x2c801 [__watcall]
// ================================================================================================

void __watcall league_name_entry(void)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  undefined4 ****ppppuVar4;
  undefined4 extraout_EDX;
  undefined4 ****ppppuVar5;
  undefined4 ****ppppuVar6;
  int *piVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  byte bVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  uint local_3c;
  undefined4 *local_38;
  undefined4 ***local_34;
  int local_30;
  undefined4 ***local_2c;
  int local_28;
  int local_24;
  undefined4 *local_20;
  undefined4 ***pppuStack_1c;
  
  bVar10 = 0;
  __CHK(0x4c);
  local_24 = 0;
  bVar1 = false;
  getmouse(&local_38,&local_28,&local_2c);
  local_30 = local_28;
  local_34 = local_2c;
  setdefaultscreen();
  local_20 = (undefined4 *)
             allocmem(aPointer_c1534,
                      (((int)pointer_shapes[1] >> 0x10) + 1) *
                      ((*(int *)((int)pointer_shapes + 2) >> 0x10) + 1) + 0x11,0x20);
  ppppuVar4 = (undefined4 ****)local_34;
  puVar8 = local_20 + (uint)bVar10 * -2 + 1;
  ppppuVar5 = pointer_shapes + (uint)bVar10 * -2 + 1;
  *local_20 = *pointer_shapes;
  puVar9 = puVar8 + (uint)bVar10 * -2 + 1;
  ppppuVar6 = ppppuVar5 + (uint)bVar10 * -2 + 1;
  *puVar8 = *ppppuVar5;
  *puVar9 = *ppppuVar6;
  puVar9[(uint)bVar10 * -2 + 1] = ppppuVar6[(uint)bVar10 * -2 + 1];
  *(undefined *)(puVar9 + (uint)bVar10 * -2 + 1 + (uint)bVar10 * -2 + 1) =
       *(undefined *)(ppppuVar6 + (uint)bVar10 * -2 + 1 + (uint)bVar10 * -2 + 1);
  *(short *)(local_20 + 1) = *(short *)(pointer_shapes + 1) + 1;
  *(short *)((int)local_20 + 6) = *(short *)((int)pointer_shapes + 6) + 1;
  grabshape(local_20,local_30 + -4,local_34);
  drawshape_remap(pointer_shapes,local_30 + -4,local_34);
  piVar7 = (int *)(&off_c6f7c)[dword_dd658];
  uVar11 = event_queue_reset();
LAB_0002c8e4:
  local_38 = (undefined4 *)0x0;
  do {
    uVar12 = event_queue_pop((int)uVar11,(int)((ulonglong)uVar11 >> 0x20),ppppuVar4);
    uVar11 = CONCAT44((int)((ulonglong)uVar12 >> 0x20),local_38);
    if ((int)uVar12 == 0) break;
    ppppuVar4 = &local_34;
    uVar11 = (*ui_poll_callback)();
    local_38 = (undefined4 *)uVar11;
  } while (local_38 == (undefined4 *)0x0);
  local_38 = (undefined4 *)uVar11;
  uVar11 = CONCAT44((int)((ulonglong)uVar11 >> 0x20),local_34);
  if (local_38 == (undefined4 *)0x0) goto code_r0x0002c914;
  drawshape2(local_20,local_28 + -4,local_2c);
  if ((((uint)local_38 & 1) == 0) || ((dword_dd668 & 0x100) == 0)) {
    if (((uint)local_38 & 2) == 0) {
      if (((uint)local_38 & 4) != 0) goto LAB_0002cc4a;
    }
    else {
      bVar1 = false;
      local_24 = 0;
      iVar2 = sub_2c3ff(local_30,local_34,&local_3c);
      if (iVar2 != 0) {
        local_3c = 1 << ((byte)local_3c & 0x1f);
        if ((dword_dd668 & local_3c) != 0) {
          if (local_3c < 0x10) {
            if (local_3c < 2) {
              if (local_3c != 1) goto LAB_0002cdeb;
              drawshape_remap(dword_dd648,0x18,0x46);
              if (piVar7[2] != 0) {
                piVar7[2] = piVar7[2] + -1;
                piVar7[3] = piVar7[3] + -1;
                goto LAB_0002ccef;
              }
            }
            else {
              if (2 < local_3c) {
                if (3 < local_3c) {
                  if (local_3c < 5) {
                    drawshape_remap(dword_dd640,0x20,0xbf);
                    freemem(local_20);
                    enter_league();
                    FUN_0002c3f7();
                    return;
                  }
                  if (local_3c == 8) {
                    drawshape_remap(dword_dd644,0x20,0xbf);
                    league_name_prompt((&off_c6f7c)[dword_dd658]);
                    setmousepos(local_30,local_34);
                    if (dword_dd658 < 0) {
                      piVar7 = (int *)0x0;
                    }
                    else {
                      piVar7 = (int *)(&off_c6f7c)[dword_dd658];
                    }
                    sub_2c46b(piVar7);
                    drawshape_remap(dword_dd638,0x20,0xbf);
                    goto LAB_0002cb46;
                  }
                }
LAB_0002cdeb:
                sub_2c3ff(local_30,local_34,&local_3c);
                if (9 < (int)local_3c) {
                  piVar7[1] = piVar7[2] + local_3c + -10;
                }
                goto LAB_0002ccef;
              }
              drawshape_remap(dword_dd654,0x18,0x46);
              if (piVar7[3] + 1 < *piVar7) {
                piVar7[2] = piVar7[2] + 1;
                piVar7[3] = piVar7[3] + 1;
                goto LAB_0002ccef;
              }
            }
          }
          else {
            if (local_3c < 0x11) {
              drawshape_remap(dword_dd64c,0x20,0xbf);
LAB_0002cc4a:
              freemem(local_20);
              FUN_0002c3f7();
              return;
            }
            if (local_3c < 0x40) {
              if (local_3c != 0x20) goto LAB_0002cdeb;
              dword_dd658 = 0;
              piVar7 = (int *)off_c6f7c;
            }
            else if (local_3c < 0x41) {
              dword_dd658 = 1;
              piVar7 = (int *)off_c6f80;
            }
            else {
              if (local_3c < 0x80) goto LAB_0002cdeb;
              if (local_3c < 0x81) {
                dword_dd658 = 2;
                piVar7 = (int *)off_c6f84;
              }
              else {
                if (local_3c != 0x100) goto LAB_0002cdeb;
                iVar2 = (((int)local_34 + (-0x13 - dword_c700c)) * *piVar7) / 0x50;
                if (iVar2 < piVar7[2]) {
                  if (iVar2 < 3) {
                    piVar7[2] = 0;
                    piVar7[3] = 5;
                  }
                  else {
LAB_0002cce1:
                    piVar7[2] = iVar2 + -3;
                    piVar7[3] = iVar2 + 2;
                  }
                }
                else {
                  if (iVar2 <= piVar7[3]) goto LAB_0002cb46;
                  if (iVar2 + 3 <= *piVar7) goto LAB_0002cce1;
                  piVar7[2] = *piVar7 + -6;
                  piVar7[3] = *piVar7 + -1;
                }
              }
            }
LAB_0002ccef:
            sub_2c46b(piVar7);
          }
        }
      }
    }
  }
  else if ((local_28 != local_30) || (local_2c != local_34)) {
    iVar2 = sub_2c3ff(local_30,local_34,&local_3c);
    if ((iVar2 == 0) || (local_3c != 8)) {
      local_24 = 0;
    }
    else if (local_24 == 0) {
      local_24 = 1;
    }
    else {
      iVar3 = (*piVar7 * ((int)local_2c + (-0x13 - dword_c700c))) / 0x50;
      iVar2 = piVar7[3];
      if (((local_2c != local_34) && (piVar7[2] <= iVar3)) && (iVar3 <= iVar2)) {
        ppppuVar4 = (undefined4 ****)local_2c;
        if (bVar1) {
          ppppuVar4 = (undefined4 ****)pppuStack_1c;
        }
        if ((int)ppppuVar4 < (int)local_34) {
          ppppuVar4 = (undefined4 ****)local_2c;
          if (bVar1) {
            ppppuVar4 = (undefined4 ****)pppuStack_1c;
          }
          iVar3 = (((int)local_34 - (int)ppppuVar4) * *piVar7) / 0x50;
          if (iVar3 == 0) {
            if (!bVar1) {
              pppuStack_1c = local_2c;
            }
            bVar1 = true;
          }
          else {
            bVar1 = false;
          }
          if (piVar7[3] + iVar3 < *piVar7) {
            piVar7[2] = piVar7[2] + iVar3;
            piVar7[3] = piVar7[3] + iVar3;
          }
          else {
            piVar7[3] = *piVar7 + -1;
            piVar7[2] = *piVar7 + -6;
          }
        }
        else {
          ppppuVar4 = (undefined4 ****)local_2c;
          if (bVar1) {
            ppppuVar4 = (undefined4 ****)pppuStack_1c;
          }
          if ((int)local_34 < (int)ppppuVar4) {
            ppppuVar4 = (undefined4 ****)local_2c;
            if (bVar1) {
              ppppuVar4 = (undefined4 ****)pppuStack_1c;
            }
            iVar3 = (*piVar7 * ((int)ppppuVar4 - (int)local_34)) / 0x50;
            if (iVar3 == 0) {
              if (!bVar1) {
                pppuStack_1c = local_2c;
              }
              bVar1 = true;
            }
            else {
              bVar1 = false;
            }
            if (piVar7[2] - iVar3 < 0) {
              piVar7[2] = 0;
              piVar7[3] = 5;
            }
            else {
              piVar7[2] = piVar7[2] - iVar3;
              piVar7[3] = piVar7[3] - iVar3;
            }
          }
        }
        if (iVar2 != piVar7[3]) goto LAB_0002ccef;
      }
    }
  }
LAB_0002cb46:
  grabshape(local_20,local_30 + -4,local_34);
  ppppuVar4 = (undefined4 ****)local_34;
  goto LAB_0002c975;
code_r0x0002c914:
  if ((local_30 != local_28) || (local_34 != local_2c)) {
    setdefaultscreen();
    drawshape(local_20,local_28 + -4,local_2c);
    grabshape(local_20,local_30 + -4,local_34);
    ppppuVar4 = pointer_shapes;
LAB_0002c975:
    drawshape_remap(pointer_shapes,local_30 + -4,local_34);
    uVar11 = CONCAT44(extraout_EDX,local_34);
    local_28 = local_30;
    local_2c = local_34;
  }
  goto LAB_0002c8e4;
}


// ================================================================================================
// league_name_prompt @ 0x2ce29 [__watcall]
// ================================================================================================

/* WARNING: Removing unreachable block (ram,0x0002d014) */

undefined8 __watcall league_name_prompt(int *param_1,undefined4 unaff_EDX)

{
  int iVar1;
  int iVar2;
  undefined auStack_6c [21];
  byte bStack_57;
  char acStack_4e [14];
  char acStack_40 [16];
  undefined4 *apuStack_30 [6];
  
  __CHK(0x84);
  apuStack_30[0] = (undefined4 *)&aNHL;
  apuStack_30[1] = &aPO;
  apuStack_30[2] = &aLP;
  apuStack_30[4] = (undefined4 *)0x140;
  apuStack_30[3] = (undefined4 *)0xf0;
  if (dword_dd658 == 0) {
    dword_c70e3 = aExhibitionGameCalled;
  }
  else if (dword_dd658 == 1) {
    dword_c70e3 = aPlayOffSeriesCalled;
  }
  else {
    dword_c70e3 = aLeagueCalled;
  }
  dword_c70e7 = param_1[param_1[1] + 4];
  set_dialog_colors(0xf9,0xfa,0xf8,0xfa,0);
  iVar2 = message_dialog(0xffffffff,0xffffffff,&off_c70df,3,&unk_d2b38,2,apuStack_30 + 4,
                         apuStack_30 + 3,0xffffffff);
  if (iVar2 == 1) {
    strcpy(acStack_40,(char *)param_1[param_1[1] + 4]);
    strcat(acStack_40,(char *)apuStack_30[dword_dd658]);
    iVar2 = _dos_findfirst(acStack_40,0x10,auStack_6c);
    if (iVar2 == 0) {
      if ((bStack_57 & 0x10) == 0) {
        iVar2 = remove(acStack_4e);
        if (iVar2 != 0) {
          fatalerror(&aC6);
        }
      }
      else {
        iVar2 = stricmp(acStack_40,&byte_c5386);
        if (iVar2 == 0) {
          byte_c5386 = 0;
          dword_ce4e3 = 0;
          dword_ce503 = 0;
          dword_ce527 = 0;
        }
        else {
          iVar2 = stricmp(acStack_40,&byte_c5311);
          if (iVar2 == 0) {
            byte_c5311 = 0;
            dword_ce583 = 0;
            dword_ce5a3 = 0;
            dword_ce5c3 = 0;
          }
        }
        sub_14442(acStack_4e);
      }
      iVar2 = *param_1;
      *param_1 = iVar2 + -1;
      if (iVar2 + -1 == 0) {
        if (dword_dd658 == 0) {
          dword_dd668 = dword_dd668 & 0xffdf;
        }
        else if (dword_dd658 < 2) {
          dword_dd668 = dword_dd668 & 0xffbf;
        }
        else if (dword_dd658 == 2) {
          dword_dd668 = dword_dd668 & 0xff7f;
        }
        if (dword_dd244 == 0) {
          if (dword_dd1b4 == 0) {
            if (dword_dd124 == 0) {
              dword_dd658 = 0xffffffff;
              dword_dd668 = 0x10;
            }
            else {
              dword_dd658 = 2;
            }
          }
          else {
            dword_dd658 = 1;
          }
        }
        else {
          dword_dd658 = 0;
        }
        league_type_menu();
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
    else {
      apuStack_30[5] = (undefined4 *)0x0;
    }
  }
  else {
    apuStack_30[5] = (undefined4 *)0x0;
  }
  return CONCAT44(unaff_EDX,apuStack_30[5]);
}


// ================================================================================================
// enter_league @ 0x2d099 [__watcall]
// ================================================================================================

undefined8 __watcall enter_league(undefined4 param_1,undefined4 unaff_EDX)

{
  int iVar1;
  char *pcVar2;
  undefined auStack_40 [32];
  char acStack_20 [16];
  
  __CHK(0x4c);
  if (dword_dd658 == 0) {
    strcpy(acStack_20,(char *)(&unk_dd254)[dword_dd248]);
    strcat(acStack_20,(char *)&aNhl);
    load_league_settings(&settings_exhibition,acStack_20,1);
    apply_settings(&settings_exhibition);
    if (dword_c52e9 < 0x18) {
      pcVar2 = (&team_abbrev)[dword_c52e9];
    }
    else {
      pcVar2 = (char *)(&off_c5441)[dword_c52e9];
    }
    strncpy(aGameLAAtMTL + 6,pcVar2,3);
    if (dword_c52ed < 0x18) {
      pcVar2 = (&team_abbrev)[dword_c52ed];
    }
    else {
      pcVar2 = (char *)(&off_c5441)[dword_c52ed];
    }
    strncpy(aGameLAAtMTL + 0xd,pcVar2,3);
    param_1 = 1;
  }
  else if (dword_dd658 < 2) {
    strcpy(acStack_20,(char *)(&unk_dd1c4)[dword_dd1b8]);
    strcat(acStack_20,(char *)&aPo_c153f);
    param_1 = load_league_settings(&settings_playoff,acStack_20,0);
    dword_ce583 = playoff_tree_screen;
    dword_ce5a3 = sub_7a29c;
    dword_ce5c3 = sub_86647;
    make_path(auStack_40,acStack_20,aScheduleDb,0);
    iVar1 = loadfile(auStack_40,0);
    dword_d29fb = *(int *)(iVar1 + 0x42) % 7;
    freemem(iVar1);
  }
  else if (dword_dd658 == 2) {
    strcpy(acStack_20,(char *)(&unk_dd134)[dword_dd128]);
    strcat(acStack_20,(char *)&aLp_c154f);
    param_1 = load_league_settings(&settings_league,acStack_20,0);
    dword_ce4e3 = sub_336e6;
    dword_ce503 = league_calendar_screen;
    dword_ce527 = &unk_ce64f;
  }
  return CONCAT44(unaff_EDX,param_1);
}


// ================================================================================================
// load_league_settings @ 0x2d260 [__watcall]
// ================================================================================================

undefined4 __watcall load_league_settings(int param_1,int unaff_EDX,int unaff_EBX)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined auStack_54 [64];
  undefined4 uStack_14;
  
  __CHK(0x5c);
  if (unaff_EBX == 0) {
    make_path(auStack_54,unaff_EDX,aGameSet_c1553,0);
    iVar1 = file_open_read(auStack_54,&uStack_14);
    if (iVar1 == 0) goto LAB_0002d2bb;
    puVar3 = (undefined4 *)&aD2;
  }
  else {
    iVar1 = file_open_read(unaff_EDX,&uStack_14);
    if (iVar1 == 0) goto LAB_0002d2bb;
    puVar3 = &aDd2;
  }
  fatalerror(puVar3);
LAB_0002d2bb:
  iVar1 = file_read(uStack_14,param_1,0xffffffff);
  if (iVar1 != 0) {
    fatalerror(&aD3_c1563);
  }
  iVar1 = file_close(&uStack_14);
  if (iVar1 != 0) {
    fatalerror(&aD4_c1566);
  }
  if (unaff_EBX == 0) {
    make_path(auStack_54,unaff_EDX,aGameSav_c1569,0);
    unaff_EDX = sub_b3cc8(auStack_54);
  }
  if (unaff_EDX == 0) {
    uVar2 = 0;
  }
  else {
    if (sound_enabled == '\0') {
      *(byte *)(param_1 + 0x5a) = *(byte *)(param_1 + 0x5a) & 0xfe;
    }
    uVar2 = 1;
  }
  return uVar2;
}


// ================================================================================================
// boxscore_screen @ 0x2d35a [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __watcall boxscore_screen(uint param_1,undefined unaff_DL,undefined unaff_BL)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined *puVar5;
  byte bVar6;
  uint *puVar7;
  uint *puVar9;
  char *pcVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  byte *pbVar14;
  byte *pbVar15;
  int *piVar16;
  uint uVar17;
  uint local_800;
  undefined auStack_7fc [744];
  undefined auStack_514 [744];
  char acStack_22c [84];
  undefined auStack_1d8 [64];
  undefined4 local_198;
  undefined4 local_194;
  undefined4 local_190;
  undefined4 local_18c;
  undefined4 local_188;
  undefined4 local_184;
  undefined4 local_180;
  undefined4 local_17c;
  undefined4 local_178;
  undefined4 local_174;
  undefined4 local_170;
  undefined4 uStack_16c;
  undefined auStack_164 [19];
  undefined auStack_151 [33];
  undefined auStack_130 [100];
  char acStack_cc [16];
  undefined auStack_bc [3];
  undefined4 uStack_b9;
  undefined1 *local_b0 [8];
  int local_90;
  int local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  int local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_64;
  undefined4 local_5c;
  int local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_40;
  uint local_3c;
  undefined local_38 [4];
  undefined local_34 [4];
  undefined local_30 [4];
  undefined local_2c;
  undefined local_28;
  undefined local_24;
  undefined local_20;
  undefined uStack_1c;
  undefined uStack_10;
  undefined4 *puVar8;
  
  __CHK(0x818);
  puVar7 = &local_800;
  puVar9 = &local_800;
  local_b0[6] = (undefined1 *)0xffffffff;
  local_b0[5] = (undefined1 *)0xffffffff;
  local_b0[2] = (undefined1 *)0xffffffff;
  local_b0[3] = (undefined1 *)0xffffffff;
  local_b0[4] = (undefined1 *)0xffffffff;
  local_800 = param_1;
  local_24 = unaff_BL;
  local_20 = unaff_DL;
  sub_1baf3(700000);
  if ((sound_enabled != '\0') && (dword_c721d != 0)) {
    sound_fade(dword_d2431,3);
    do {
      iVar3 = sound_channel_status(ram0x000d242c >> 0x18,3);
    } while (iVar3 == 0);
    releasememblock(dword_c721d);
    dword_c721d = 0;
  }
  event_queue_reset();
  local_88 = 0;
  do {
    iVar3 = 0;
    do {
      auStack_130[local_88 * 0x19 + iVar3] = 0;
      iVar3 = iVar3 + 1;
    } while (iVar3 < 0x19);
    local_88 = local_88 + 1;
  } while (local_88 < 2);
  local_54 = 0;
  local_40 = 0;
  speech_stop();
  local_70 = 0;
  local_4c = 0;
  local_50 = 0;
  local_48 = 0;
  local_80 = 0;
  local_5c = 0xffffffff;
  local_28 = local_20;
  uStack_10 = 0;
  local_88 = 0;
  do {
    local_38[local_88] = 0;
    local_30[local_88] = 0;
    local_88 = local_88 + 1;
  } while (local_88 < 2);
  setdefaultscreen();
  getfontstate(auStack_1d8);
  puVar5 = install_path;
  if (byte_ed9e6 != '\x01') {
    puVar5 = (undefined *)0x0;
  }
  make_path(acStack_22c,puVar5,aIndus030_c1574,&aVFN);
  local_84 = loadfile(acStack_22c,0x20);
  setfont(local_84);
  puVar5 = install_path;
  if (byte_ed825 != '\x01') {
    puVar5 = (undefined *)0x0;
  }
  make_path(acStack_cc,puVar5,aCtlogo_c157d,0);
  uVar4 = loadshapes(acStack_cc,0);
  iVar3 = locateshape(uVar4,(&off_c57cc)[user2_team._2_2_]);
  dword_dd66c = windowdefp(*(int *)(iVar3 + 2) >> 0x10,*(int *)(iVar3 + 4) >> 0x10,0x20);
  setscreen(dword_dd66c);
  drawshape(iVar3,0,0);
  *(undefined2 *)(*(int *)(dword_dd66c + 0x2c) + 8) = *(undefined2 *)(iVar3 + 8);
  *(undefined2 *)(*(int *)(dword_dd66c + 0x2c) + 10) = *(undefined2 *)(iVar3 + 10);
  iVar3 = locateshape(uVar4,(&off_c57cc)[_away_team_id]);
  dword_dd670 = windowdefp(*(int *)(iVar3 + 2) >> 0x10,*(int *)(iVar3 + 4) >> 0x10,0x20);
  setscreen(dword_dd670);
  drawshape(iVar3,0,0);
  *(undefined2 *)(*(int *)(dword_dd670 + 0x2c) + 8) = *(undefined2 *)(iVar3 + 8);
  *(undefined2 *)(*(int *)(dword_dd670 + 0x2c) + 10) = *(undefined2 *)(iVar3 + 10);
  setdefaultscreen();
  freemem(uVar4);
  puVar5 = install_path;
  if (byte_ed824 != '\x01') {
    puVar5 = (undefined *)0x0;
  }
  make_path(acStack_cc,puVar5,aCtbkgd_c1584,0);
  uVar4 = loadshapes(acStack_cc,0);
  local_7c = uVar4;
  local_64 = locateshape(uVar4,&aBkgd_c158b);
  local_58 = locateshape(uVar4,&aPal_c1590);
  local_58 = local_58 + 0x10;
  if ((local_800 & 3) == 0) {
    if ((local_800 & 0x1c) != 0) {
      puVar5 = install_path;
      if (byte_ed826 != '\x01') {
        puVar5 = (undefined *)0x0;
      }
      make_path(acStack_cc,puVar5,aCttitle1_c15bc,0);
      uVar4 = loadshapes(acStack_cc,0);
      local_74 = uVar4;
      local_198 = locateshape(uVar4,&aDef_c15c5);
      local_194 = locateshape(uVar4,&aFowa_c15ca);
      local_17c = locateshape(uVar4,&aScra_c15cf);
      local_174 = locateshape(uVar4,&aTlu_c15d4);
      goto LAB_0002d781;
    }
    if ((local_800 & 0x20) != 0) {
      puVar5 = install_path;
      if (byte_ed828 != '\x01') {
        puVar5 = (undefined *)0x0;
      }
      make_path(acStack_cc,puVar5,aCttitle3,0);
      uVar4 = loadshapes(acStack_cc,0);
      local_74 = uVar4;
      local_18c = locateshape(uVar4,&aOts);
      uStack_16c = locateshape(uVar4,&aColm);
    }
  }
  else {
    puVar5 = install_path;
    if (byte_ed827 != '\x01') {
      puVar5 = (undefined *)0x0;
    }
    make_path(acStack_cc,puVar5,aCttitle2,0);
    uVar4 = loadshapes(acStack_cc,0);
    local_74 = uVar4;
    local_178 = locateshape(uVar4,&aSumm_c159e);
    local_190 = locateshape(uVar4,&aOt);
    local_188 = locateshape(uVar4,&aPer1);
    local_184 = locateshape(uVar4,&aPer2);
    local_180 = locateshape(uVar4,&aPer3);
LAB_0002d781:
    local_170 = locateshape(uVar4,&aTop_c15b7);
  }
  set_text_colors(0x40,0);
  make_path(acStack_22c,&league_dir);
  local_78 = file_open_read(acStack_22c,local_b0 + 4);
  if (local_78 == 0) {
    local_78 = sub_147ff(local_b0[4],auStack_bc,0);
  }
  if ((local_800 & 0x20) == 0) {
    if (local_78 == 0) {
      local_90 = uStack_b9 >> 0x10;
      local_2c = (undefined)uStack_b9;
      uStack_1c = uStack_b9._1_1_;
      make_path(acStack_22c,&league_dir,off_c80e7);
      local_78 = file_open_read(acStack_22c,local_b0 + 6);
    }
    if (local_78 == 0) {
      local_78 = db_read_record(local_b0[6],auStack_7fc,local_2c);
    }
    if (local_78 == 0) {
      local_78 = db_read_record(local_b0[6],auStack_514,uStack_1c);
    }
    file_close(local_b0 + 6);
  }
  if (local_78 == 0) {
    make_path(acStack_22c,&league_dir,off_c80d7);
    local_78 = file_open_read(acStack_22c,local_b0 + 5);
  }
  if (local_78 == 0) {
    strcpy(acStack_cc,off_c80eb);
    sprintf(acStack_22c,&byte_dd750,acStack_cc);
    local_78 = file_open_rw(acStack_22c,local_b0 + 2);
  }
  if (local_78 == 0) {
    strcpy(acStack_cc,off_c80eb);
    sprintf(acStack_22c,&byte_dd710,acStack_cc);
    local_78 = file_open_rw(acStack_22c,local_b0 + 3);
  }
  iVar3 = 0xa0;
  local_b0[7] = (undefined1 *)0x0;
  if ((local_800 & 0x20) == 0) {
    wait_sprite_fade();
    if ((sound_enabled == '\0') || (dword_c721d != 0)) {
      puVar5 = install_path;
      if (dword_c541f == 8) {
        pcVar10 = aMtsum;
        if (byte_ed8ce != '\x01') {
          puVar5 = (undefined *)0x0;
        }
      }
      else {
        pcVar10 = aAdsum;
        if (byte_ed7ed != '\x01') {
          puVar5 = (undefined *)0x0;
        }
      }
      make_path(acStack_22c,puVar5,pcVar10,0);
      dword_ccc94 = 0x20;
      local_b0[7] = (undefined1 *)sub_8f13b(acStack_22c);
      dword_ccc94 = 0;
      play_sample_by_ptr();
    }
    else {
      puVar5 = install_path;
      if (byte_ed9b0 != '\x01') {
        puVar5 = (undefined *)0x0;
      }
      make_path(acStack_22c,puVar5,aGamesum,&aIff_c15f5);
      dword_c721d = loadsound(acStack_22c);
      if ((dword_c721d != 0) && (((byte)option_flags & 0x40) != 0)) {
        playsample(dword_c721d,dword_d2431,3,0x4c);
      }
    }
  }
  event_queue_reset();
  flush_key_events();
  local_b0[0] = (undefined1 *)&unk_dc200;
  local_b0[1] = &unk_dabf0;
  if ((local_800 & 0x24) == 0) {
    drawshape_remap_home(local_64);
    if ((local_800 & 3) == 0) {
      sub_7df4e(local_800,local_20,local_58,&local_198,0,local_34);
      puVar9 = &local_800;
    }
    else {
      sub_7df4e(local_800,local_20,local_58,&local_198,0,local_34);
      drawshape_remap_centered(*(undefined4 *)(dword_dd66c + 0x2c),0x3d,0x50);
      drawshape_remap_centered(*(undefined4 *)(dword_dd670 + 0x2c),0x221,0x50);
      puVar9 = &local_800;
    }
  }
  else {
    if ((local_800 & 0x20) == 0) {
      if ((local_800 & 4) == 0) goto LAB_0002e1be;
      iVar13 = 0;
      do {
        if (iVar13 != 0) {
          fade_palette(1,local_58,0x10);
        }
        clearclip(0);
        drawshape_remap_home(local_64);
        sub_7df4e(local_800,local_20,local_58,&local_198,0,local_34);
        drawshape_remap_centered(*(undefined4 *)((&dword_dd66c)[iVar13] + 0x2c),0x3d,0x50);
        iVar3 = byte_d42c3 + 0x78;
        local_88 = 0;
        while ((local_88 < 8 && (local_78 == 0))) {
          local_3c = (uint)(byte)local_b0[iVar13][local_88 + 0x28];
          if (local_3c < 100) {
            local_78 = sub_1463d(local_b0[5],auStack_164,
                                 *(undefined4 *)(&unk_dbc7c + local_3c * 4 + iVar13 * 0x2e8));
            if (local_78 == 0) {
              sub_29c75(acStack_22c,0,auStack_151,200);
              print_text_at(0xb4,iVar3,acStack_22c);
              if ((&rosters)[iVar13 * 0x444 + local_3c * 0x27] == '\x01') {
                print_text_at(0x226,iVar3,aInjured_c1639);
              }
            }
            iVar3 = iVar3 + byte_d42c3 + 0xe;
          }
          local_88 = local_88 + 1;
        }
        fade_palette(0,local_58);
        local_4c = sub_33e6a(1000);
        iVar13 = iVar13 + 1;
        puVar7 = &local_800;
      } while (iVar13 < 2);
    }
    else {
      local_88 = 0;
      while (((iVar13 = puVar7[0x1de], iVar13 < 6 && ((int)puVar7[0x1ed] < 2)) &&
             (puVar7[0x1e2] == 0))) {
        *(undefined1 *)(puVar7 + 0x1f5) = (&unk_dd774)[iVar13 * 2];
        *(undefined1 *)(puVar7 + 0x1f9) = (&unk_dd775)[iVar13 * 2];
        *(undefined *)(puVar7 + 0x1f6) = *(undefined *)(&unk_dd730 + iVar13);
        *(undefined1 *)(puVar7 + 500) = (&unk_dd788)[iVar13 * 2];
        *(undefined1 *)((int)puVar7 + 0x7d1) = (&unk_dd789)[iVar13 * 2];
        if (puVar7[0x1e2] == 0) {
          puVar7[-1] = 0x2dd28;
          make_path(puVar7 + 0x175,&league_dir,off_c80e7,&aDB);
          puVar7[-1] = 0x2dd3b;
          uVar4 = file_open_read(puVar7 + 0x175,puVar7 + 0x1da);
          puVar7[0x1e2] = uVar4;
        }
        if (puVar7[0x1e2] == 0) {
          puVar7[-1] = 0x2dd64;
          uVar4 = db_read_record(puVar7[0x1da],puVar7 + 1);
          puVar7[0x1e2] = uVar4;
        }
        if (puVar7[0x1e2] == 0) {
          puVar7[-1] = 0x2dd91;
          uVar4 = db_read_record(puVar7[0x1da],puVar7 + 0xbb);
          puVar7[0x1e2] = uVar4;
        }
        puVar7[-1] = 0x2dda4;
        file_close(puVar7 + 0x1da);
        if (puVar7[0x1e2] == 0) {
          if (puVar7[0x1de] == 0) {
            puVar7[-1] = 0x1e0;
            puVar7[-2] = 0;
            puVar7[-3] = 0x280;
            puVar7[-4] = 0;
          }
          else {
            puVar7[-1] = 0x1e0;
            puVar7[-2] = 0x8c;
            puVar7[-3] = 0x280;
            puVar7[-4] = 0x72;
          }
          puVar7[-5] = 0x2dde1;
          setclip();
          puVar7[-1] = 0x2dde9;
          wait_sprite_fade();
          puVar7[-1] = puVar7[0x1e7];
          puVar7[-2] = 0x2ddf6;
          drawshape_remap_home();
          puVar7[-1] = (uint)(puVar7 + 499);
          puVar7[-2] = 0;
          puVar7[-3] = 0x2de23;
          sub_7df4e(*puVar7,*(undefined *)(puVar7 + 0x1f8),puVar7[0x1ea],puVar7 + 0x19a);
          puVar7[-1] = 0x1e0;
          puVar7[-2] = 0;
          puVar7[-3] = 0x280;
          puVar7[-4] = 0;
          puVar7[-5] = 0x2de36;
          setclip();
          puVar7[-1] = 0x2de4c;
          strcpy((char *)(puVar7 + 0x175),(char *)((int)puVar7 + 0x306));
          puVar7[-1] = 0x2de62;
          print_text_at(0x74,0xd2,puVar7 + 0x175);
          puVar7[-1] = (uint)*(byte *)((int)puVar7 + 0x7d1);
          puVar7[-2] = (uint)&aD_c160e;
          puVar7[-3] = (uint)(puVar7 + 0x175);
          puVar7[-4] = 0x2de7e;
          sprintf((char *)puVar7[-3],(char *)puVar7[-2]);
          puVar7[-1] = 0x2de97;
          print_text_at(0x118,0xd2,puVar7 + 0x175);
          puVar7[-1] = 0x2dea7;
          strcpy((char *)(puVar7 + 0x175),(char *)((int)puVar7 + 0x1e));
          puVar7[-1] = 0x2debd;
          print_text_at(0x74,0x114,puVar7 + 0x175);
          puVar7[-1] = (uint)*(byte *)(puVar7 + 500);
          puVar7[-2] = (uint)&aD_c160e;
          puVar7[-3] = (uint)(puVar7 + 0x175);
          puVar7[-4] = 0x2ded9;
          sprintf((char *)puVar7[-3],(char *)puVar7[-2]);
          puVar7[-1] = 0x2def2;
          print_text_at(0x118,0x114,puVar7 + 0x175);
          iVar3 = 0xf3;
          switch(*(undefined *)(puVar7 + 0x1f6)) {
          case 1:
            puVar7[-1] = (uint)&a1st;
            break;
          case 2:
            puVar7[-1] = (uint)&a2nd;
            break;
          case 3:
            puVar7[-1] = (uint)&a3rd;
            break;
          case 4:
            puVar7[-1] = (uint)&aOT_c161d;
            break;
          case 5:
            puVar7[-1] = (uint)aFinalOT;
            break;
          default:
            puVar7[-1] = (uint)aFinal;
          }
          puVar7[-2] = (uint)(puVar7 + 0x175);
          puVar7[-3] = 0x2df46;
          sprintf((char *)puVar7[-2],(char *)puVar7[-1]);
          if (*(byte *)(puVar7 + 0x1f6) < 4) {
            puVar7[-1] = 0x2df64;
            strcat((char *)(puVar7 + 0x175),aPeriod);
          }
          puVar7[-1] = 0x2df77;
          print_text_at(400,0xf3);
          if (puVar7[0x1e9] != 0) {
            puVar8 = puVar7 + -1;
            puVar7 = puVar7 + -1;
            *puVar8 = 0x2df86;
            say_elsenhl();
            *(undefined4 *)((int)puVar7 + 0x7a4) = 0;
          }
          if (*(int *)((int)puVar7 + 0x778) == 0) {
            *(undefined4 *)((int)puVar7 + -4) = 0x2dfac;
            fade_palette(0,*(undefined4 *)((int)puVar7 + 0x7a8));
          }
          *(undefined4 *)((int)puVar7 + -4) = 0x2dfb6;
          uVar4 = sub_33e6a(1000);
          *(undefined4 *)((int)puVar7 + 0x7b4) = uVar4;
        }
        *(int *)((int)puVar7 + 0x778) = *(int *)((int)puVar7 + 0x778) + 1;
      }
    }
    *(undefined4 *)((int)puVar7 + 0x780) = 0xffffffff;
    puVar9 = puVar7;
  }
LAB_0002e1be:
  if (*(int *)((int)puVar9 + 0x780) != -1) {
    *(byte *)((int)puVar9 + -0xffffffff00000004) = 0x20;
    *(byte *)((int)puVar9 + -0xffffffff00000003) = 0;
    *(byte *)((int)puVar9 + -0xffffffff00000002) = 0;
    *(byte *)((int)puVar9 + -0xffffffff00000001) = 0;
    *(int *)((int)puVar9 + -8) =
         ((*(int *)((int)puVar9 + 0x770) * 0x10 + *(int *)((int)puVar9 + 0x770) * -4) -
         *(int *)((int)puVar9 + 0x770)) + 1;
    *(undefined5 **)((int)puVar9 + -0xc) = &aEVNT;
    *(byte *)((int)puVar9 + -0xffffffff00000010) = 0xf2;
    *(byte *)((int)puVar9 + -0xffffffff0000000f) = 0xe1;
    *(byte *)((int)puVar9 + -0xffffffff0000000e) = 2;
    *(byte *)((int)puVar9 + -0xffffffff0000000d) = 0;
    uVar4 = allocmem();
    *(undefined4 *)((int)puVar9 + 0x7c0) = uVar4;
    *(byte *)((int)puVar9 + 0x7bc) = 0;
    *(byte *)((int)puVar9 + 0x7bd) = 0;
    *(byte *)((int)puVar9 + 0x7be) = 0;
    *(byte *)((int)puVar9 + 0x7bf) = 0;
    *(byte *)((int)puVar9 + 0x778) = 0;
    *(byte *)((int)puVar9 + 0x779) = 0;
    *(byte *)((int)puVar9 + 0x77a) = 0;
    *(byte *)((int)puVar9 + 0x77b) = 0;
    *(byte *)((int)puVar9 + 0x7a0) = 0;
    *(byte *)((int)puVar9 + 0x7a1) = 0;
    *(byte *)((int)puVar9 + 0x7a2) = 0;
    *(byte *)((int)puVar9 + 0x7a3) = 0;
    *(byte *)((int)puVar9 + 0x7cc) = 0;
    *(byte *)((int)puVar9 + 0x7cd) = 0;
    do {
      pcVar10 = (char *)(*(int *)((int)puVar9 + 0x7c0) +
                        ((*(int *)((int)puVar9 + 0x7bc) * 0x10 + *(int *)((int)puVar9 + 0x7bc) * -4)
                        - *(int *)((int)puVar9 + 0x7bc)));
      *(byte *)((int)puVar9 + -0xffffffff00000004) = 0x59;
      *(byte *)((int)puVar9 + -0xffffffff00000003) = 0xe2;
      *(byte *)((int)puVar9 + -0xffffffff00000002) = 2;
      *(byte *)((int)puVar9 + -0xffffffff00000001) = 0;
      uVar4 = sub_147ff(*(undefined4 *)((int)puVar9 + 0x760),pcVar10);
      *(undefined4 *)((int)puVar9 + 0x788) = uVar4;
      if ((((*pcVar10 == '\x01') && ((*(byte *)puVar9 & 1) != 0)) ||
          ((*(char *)(((*(int *)((int)puVar9 + 0x7bc) * 0x10 + *(int *)((int)puVar9 + 0x7bc) * -4) -
                      *(int *)((int)puVar9 + 0x7bc)) + *(int *)((int)puVar9 + 0x7c0)) == '\x02' &&
           ((*(byte *)puVar9 & 2) != 0)))) ||
         ((*(char *)(((*(int *)((int)puVar9 + 0x7bc) * 0x10 + *(int *)((int)puVar9 + 0x7bc) * -4) -
                     *(int *)((int)puVar9 + 0x7bc)) + *(int *)((int)puVar9 + 0x7c0)) == '\x04' &&
          ((*(byte *)puVar9 & 3) != 0)))) {
        if (*(char *)(((*(int *)((int)puVar9 + 0x7bc) * 0x10 + *(int *)((int)puVar9 + 0x7bc) * -4) -
                      *(int *)((int)puVar9 + 0x7bc)) + *(int *)((int)puVar9 + 0x7c0)) == '\x04') {
          *(int *)((int)puVar9 + 0x7a0) = *(int *)((int)puVar9 + 0x7a0) + 1;
        }
        pcVar10 = (char *)(((*(int *)((int)puVar9 + 0x7bc) * 0x10 +
                            *(int *)((int)puVar9 + 0x7bc) * -4) - *(int *)((int)puVar9 + 0x7bc)) +
                          *(int *)((int)puVar9 + 0x7c0));
        if (*pcVar10 == '\x01') {
          *(byte *)((int)puVar9 + (byte)pcVar10[1] + 0x7cc) =
               *(byte *)((int)puVar9 + (byte)pcVar10[1] + 0x7cc) + 1;
        }
        *(int *)((int)puVar9 + 0x7bc) = *(int *)((int)puVar9 + 0x7bc) + 1;
      }
      iVar13 = *(int *)((int)puVar9 + 0x778);
      *(int *)((int)puVar9 + 0x778) = iVar13 + 1;
    } while ((*(int *)((int)puVar9 + 0x788) == 0) && (iVar13 + 1 <= *(int *)((int)puVar9 + 0x770)));
    *(byte *)((int)puVar9 + -0xffffffff00000004) = 0x20;
    *(byte *)((int)puVar9 + -0xffffffff00000003) = 0;
    *(byte *)((int)puVar9 + -0xffffffff00000002) = 0;
    *(byte *)((int)puVar9 + -0xffffffff00000001) = 0;
    *(int *)((int)puVar9 + -8) = *(int *)((int)puVar9 + 0x7a0) * 4 + 1;
    *(undefined5 **)((int)puVar9 + -0xc) = &aPRDS;
    *(byte *)((int)puVar9 + -0xffffffff00000010) = 0x66;
    *(byte *)((int)puVar9 + -0xffffffff0000000f) = 0xe3;
    *(byte *)((int)puVar9 + -0xffffffff0000000e) = 2;
    *(byte *)((int)puVar9 + -0xffffffff0000000d) = 0;
    uVar4 = allocmem();
    *(undefined4 *)((int)puVar9 + 0x7ac) = uVar4;
    *(byte *)((int)puVar9 + 0x794) = 1;
    *(byte *)((int)puVar9 + 0x795) = 0;
    *(byte *)((int)puVar9 + 0x796) = 0;
    *(byte *)((int)puVar9 + 0x797) = 0;
    *(byte *)((int)puVar9 + 0x778) = 0;
    *(byte *)((int)puVar9 + 0x779) = 0;
    *(byte *)((int)puVar9 + 0x77a) = 0;
    *(byte *)((int)puVar9 + 0x77b) = 0;
    iVar11 = 0;
    *(byte *)((int)puVar9 + 0x798) = 1;
    *(byte *)((int)puVar9 + 0x799) = 0;
    *(byte *)((int)puVar9 + 0x79a) = 0;
    *(byte *)((int)puVar9 + 0x79b) = 0;
    *(byte *)((int)puVar9 + 0x774) = 0;
    *(byte *)((int)puVar9 + 0x775) = 0;
    *(byte *)((int)puVar9 + 0x776) = 0;
    *(byte *)((int)puVar9 + 0x777) = 0;
    iVar13 = *(int *)((int)puVar9 + 0x7a0);
    iVar12 = *(int *)((int)puVar9 + 0x7ac);
    do {
      pcVar10 = (char *)(((*(int *)((int)puVar9 + 0x778) * 0x10 + *(int *)((int)puVar9 + 0x778) * -4
                          ) - *(int *)((int)puVar9 + 0x778)) + *(int *)((int)puVar9 + 0x7c0));
      if (*pcVar10 == '\x04') {
        *(char **)(iVar11 * 4 + iVar12) = pcVar10 + 1;
        iVar11 = iVar11 + 1;
      }
      iVar2 = *(int *)((int)puVar9 + 0x778);
      *(int *)((int)puVar9 + 0x778) = iVar2 + 1;
    } while ((iVar2 + 1 <= *(int *)((int)puVar9 + 0x770)) && (iVar11 < iVar13));
    if ((*(byte *)puVar9 & 0x24) == 0) {
      if ((*(byte *)puVar9 & 3) == 0) {
        *(byte **)((int)puVar9 + -4) = (byte *)((int)puVar9 + 0x7cc);
        *(undefined4 *)((int)puVar9 + -8) = *(undefined4 *)((int)puVar9 + 0x7a0);
        *(byte *)((int)puVar9 + -0xffffffff0000000c) = 0x8c;
        *(byte *)((int)puVar9 + -0xffffffff0000000b) = 0xe4;
        *(byte *)((int)puVar9 + -0xffffffff0000000a) = 2;
        *(byte *)((int)puVar9 + -0xffffffff00000009) = 0;
        sub_7df4e(*puVar9,*(byte *)((int)puVar9 + 0x7e0),*(undefined4 *)((int)puVar9 + 0x7a8),
                  (byte *)((int)puVar9 + 0x668));
      }
      else {
        *(byte **)((int)puVar9 + -4) = (byte *)((int)puVar9 + 0x7cc);
        *(undefined4 *)((int)puVar9 + -8) = *(undefined4 *)((int)puVar9 + 0x7a0);
        *(byte *)((int)puVar9 + -0xffffffff0000000c) = 0x2d;
        *(byte *)((int)puVar9 + -0xffffffff0000000b) = 0xe4;
        *(byte *)((int)puVar9 + -0xffffffff0000000a) = 2;
        *(byte *)((int)puVar9 + -0xffffffff00000009) = 0;
        sub_7df4e(*puVar9,*(byte *)((int)puVar9 + 0x7e0),*(undefined4 *)((int)puVar9 + 0x7a8),
                  (byte *)((int)puVar9 + 0x668));
        *(byte *)((int)puVar9 + -0xffffffff00000004) = 0x50;
        *(byte *)((int)puVar9 + -0xffffffff00000003) = 0;
        *(byte *)((int)puVar9 + -0xffffffff00000002) = 0;
        *(byte *)((int)puVar9 + -0xffffffff00000001) = 0;
        *(byte *)((int)puVar9 + -0xffffffff00000008) = 0x3d;
        *(byte *)((int)puVar9 + -0xffffffff00000007) = 0;
        *(byte *)((int)puVar9 + -0xffffffff00000006) = 0;
        *(byte *)((int)puVar9 + -0xffffffff00000005) = 0;
        *(undefined4 *)((int)puVar9 + -0xc) = *(undefined4 *)(dword_dd66c + 0x2c);
        *(byte *)((int)puVar9 + -0xffffffff00000010) = 0x3f;
        *(byte *)((int)puVar9 + -0xffffffff0000000f) = 0xe4;
        *(byte *)((int)puVar9 + -0xffffffff0000000e) = 2;
        *(byte *)((int)puVar9 + -0xffffffff0000000d) = 0;
        drawshape_remap_centered();
        *(byte *)((int)puVar9 + -0xffffffff00000004) = 0x50;
        *(byte *)((int)puVar9 + -0xffffffff00000003) = 0;
        *(byte *)((int)puVar9 + -0xffffffff00000002) = 0;
        *(byte *)((int)puVar9 + -0xffffffff00000001) = 0;
        *(byte *)((int)puVar9 + -0xffffffff00000008) = 0x21;
        *(byte *)((int)puVar9 + -0xffffffff00000007) = 2;
        *(byte *)((int)puVar9 + -0xffffffff00000006) = 0;
        *(byte *)((int)puVar9 + -0xffffffff00000005) = 0;
        *(undefined4 *)((int)puVar9 + -0xc) = *(undefined4 *)(dword_dd670 + 0x2c);
        *(byte *)((int)puVar9 + -0xffffffff00000010) = 0x57;
        *(byte *)((int)puVar9 + -0xffffffff0000000f) = 0xe4;
        *(byte *)((int)puVar9 + -0xffffffff0000000e) = 2;
        *(byte *)((int)puVar9 + -0xffffffff0000000d) = 0;
        drawshape_remap_centered();
      }
    }
    *(byte *)((int)puVar9 + 0x778) = 0;
    *(byte *)((int)puVar9 + 0x779) = 0;
    *(byte *)((int)puVar9 + 0x77a) = 0;
    *(byte *)((int)puVar9 + 0x77b) = 0;
    *(byte *)((int)puVar9 + 0x7ec) = 0;
    *(byte *)((int)puVar9 + 0x7e8) = 0;
    while ((((*(int *)((int)puVar9 + 0x788) == 0 && (*(int *)((int)puVar9 + 0x780) == 0)) &&
            (*(int *)((int)puVar9 + 0x778) < *(int *)((int)puVar9 + 0x7bc))) &&
           (*(int *)((int)puVar9 + 0x7b4) < 2))) {
      *(byte *)((int)puVar9 + -0xffffffff00000004) = 0xe0;
      *(byte *)((int)puVar9 + -0xffffffff00000003) = 1;
      *(byte *)((int)puVar9 + -0xffffffff00000002) = 0;
      *(byte *)((int)puVar9 + -0xffffffff00000001) = 0;
      *(byte *)((int)puVar9 + -0xffffffff00000008) = 0;
      *(byte *)((int)puVar9 + -0xffffffff00000007) = 0;
      *(byte *)((int)puVar9 + -0xffffffff00000006) = 0;
      *(byte *)((int)puVar9 + -0xffffffff00000005) = 0;
      *(byte *)((int)puVar9 + -0xffffffff0000000c) = 0x80;
      *(byte *)((int)puVar9 + -0xffffffff0000000b) = 2;
      *(byte *)((int)puVar9 + -0xffffffff0000000a) = 0;
      *(byte *)((int)puVar9 + -0xffffffff00000009) = 0;
      *(byte *)((int)puVar9 + -0xffffffff00000010) = 0;
      *(byte *)((int)puVar9 + -0xffffffff0000000f) = 0;
      *(byte *)((int)puVar9 + -0xffffffff0000000e) = 0;
      *(byte *)((int)puVar9 + -0xffffffff0000000d) = 0;
      *(byte *)((int)puVar9 + -0xffffffff00000014) = 0xa6;
      *(byte *)((int)puVar9 + -0xffffffff00000013) = 0xf0;
      *(byte *)((int)puVar9 + -0xffffffff00000012) = 2;
      *(byte *)((int)puVar9 + -0xffffffff00000011) = 0;
      setclip();
      pbVar14 = (byte *)(*(int *)((int)puVar9 + 0x7c0) +
                        ((*(int *)((int)puVar9 + 0x778) * 0x10 + *(int *)((int)puVar9 + 0x778) * -4)
                        - *(int *)((int)puVar9 + 0x778)));
      bVar6 = *pbVar14;
      pbVar15 = pbVar14 + 1;
      if (bVar6 < 2) {
        if (bVar6 == 1) {
          *(byte *)((int)puVar9 + (uint)*pbVar15 * 0x19 + (uint)pbVar14[2] + 0x6d0) =
               *(byte *)((int)puVar9 + (uint)*pbVar15 * 0x19 + (uint)pbVar14[2] + 0x6d0) + 1;
          if (((*(byte *)((int)puVar9 + 0x7e0) <= pbVar14[6]) &&
              (pbVar14[6] <= *(byte *)((int)puVar9 + 0x7dc))) && ((*(byte *)puVar9 & 1) != 0)) {
            *(uint *)((int)puVar9 + 0x7c4) = (uint)pbVar14[2];
            *(byte *)((int)puVar9 + -0xffffffff00000004) = 0x3f;
            *(byte *)((int)puVar9 + -0xffffffff00000003) = 0xe5;
            *(byte *)((int)puVar9 + -0xffffffff00000002) = 2;
            *(byte *)((int)puVar9 + -0xffffffff00000001) = 0;
            iVar13 = sub_1463d(*(undefined4 *)((int)puVar9 + 0x764),(byte *)((int)puVar9 + 0x69c));
            *(int *)((int)puVar9 + 0x788) = iVar13;
            if (iVar13 == 0) {
              *(byte **)((int)puVar9 + -4) = (byte *)((int)puVar9 + (uint)*pbVar15 * 0x2e8 + 4);
              *(undefined3 **)((int)puVar9 + -8) = &aS_c164b;
              *(byte **)((int)puVar9 + -0xc) = (byte *)((int)puVar9 + 0x5d4);
              *(byte *)((int)puVar9 + -0xffffffff00000010) = 0x7c;
              *(byte *)((int)puVar9 + -0xffffffff0000000f) = 0xe5;
              *(byte *)((int)puVar9 + -0xffffffff0000000e) = 2;
              *(byte *)((int)puVar9 + -0xffffffff0000000d) = 0;
              sprintf(*(char **)((int)puVar9 + -0xc),*(char **)((int)puVar9 + -8));
              *(byte *)((int)puVar9 + -0xffffffff00000004) = 0x92;
              *(byte *)((int)puVar9 + -0xffffffff00000003) = 0xe5;
              *(byte *)((int)puVar9 + -0xffffffff00000002) = 2;
              *(byte *)((int)puVar9 + -0xffffffff00000001) = 0;
              print_text_at(0x96,iVar3,(byte *)((int)puVar9 + 0x5d4));
              *(byte *)((int)puVar9 + -0xffffffff00000004) = 0xac;
              *(byte *)((int)puVar9 + -0xffffffff00000003) = 0xe5;
              *(byte *)((int)puVar9 + -0xffffffff00000002) = 2;
              *(byte *)((int)puVar9 + -0xffffffff00000001) = 0;
              sub_29c75((byte *)((int)puVar9 + 0x5d4),0,(byte *)((int)puVar9 + 0x6af));
              uVar4 = *(undefined4 *)((int)puVar9 + (uint)*pbVar15 * 4 + 0x758);
              *(byte *)((int)puVar9 + -0xffffffff00000004) = 0xca;
              *(byte *)((int)puVar9 + -0xffffffff00000003) = 0xe5;
              *(byte *)((int)puVar9 + -0xffffffff00000002) = 2;
              *(byte *)((int)puVar9 + -0xffffffff00000001) = 0;
              uVar4 = sub_1478b(uVar4,(byte *)((int)puVar9 + 0x704));
              *(undefined4 *)((int)puVar9 + 0x788) = uVar4;
            }
            if (*(int *)((int)puVar9 + 0x788) == 0) {
              if ((option_flags._1_1_ & 2) == 0) {
                uVar1 = *(ushort *)((int)puVar9 + 0x718);
              }
              else {
                uVar1 = *(ushort *)((int)puVar9 + 0x706);
              }
              iVar12 = (*(int *)((int)puVar9 +
                                (uint)*pbVar15 * 0x19 + *(int *)((int)puVar9 + 0x7c4) + 0x6cd) >>
                       0x18) + (uint)uVar1;
              *(int *)((int)puVar9 + -4) = iVar12;
              *(undefined5 **)((int)puVar9 + -8) = &aD_c164e;
              *(byte **)((int)puVar9 + -0xc) = (byte *)((int)puVar9 + 0x734);
              *(byte *)((int)puVar9 + -0xffffffff00000010) = 0x35;
              *(byte *)((int)puVar9 + -0xffffffff0000000f) = 0xe6;
              *(byte *)((int)puVar9 + -0xffffffff0000000e) = 2;
              *(byte *)((int)puVar9 + -0xffffffff0000000d) = 0;
              sprintf(*(char **)((int)puVar9 + -0xc),*(char **)((int)puVar9 + -8));
              *(byte *)((int)puVar9 + -0xffffffff00000004) = 0x4b;
              *(byte *)((int)puVar9 + -0xffffffff00000003) = 0xe6;
              *(byte *)((int)puVar9 + -0xffffffff00000002) = 2;
              *(byte *)((int)puVar9 + -0xffffffff00000001) = 0;
              strcat((char *)((int)puVar9 + 0x5d4),(char *)((int)puVar9 + 0x734));
              iVar13 = iVar12 % 10;
              iVar12 = iVar12 % 100;
              if ((iVar13 == 1) && (iVar12 != 0xb)) {
                pcVar10 = (char *)&aSt;
              }
              else if ((iVar13 == 2) && (iVar12 != 0xc)) {
                pcVar10 = (char *)&aNd;
              }
              else if ((iVar13 == 3) && (iVar12 != 0xd)) {
                pcVar10 = (char *)&aRd;
              }
              else {
                pcVar10 = (char *)&aTh;
              }
              *(byte *)((int)puVar9 + -0xffffffff00000004) = 0xad;
              *(byte *)((int)puVar9 + -0xffffffff00000003) = 0xe6;
              *(byte *)((int)puVar9 + -0xffffffff00000002) = 2;
              *(byte *)((int)puVar9 + -0xffffffff00000001) = 0;
              strcat((char *)((int)puVar9 + 0x5d4),pcVar10);
              if ((pbVar14[5] & 2) == 0) {
                if ((pbVar14[5] & 4) != 0) {
                  pcVar10 = (char *)&aPP_c1667;
                  goto LAB_0002e6c6;
                }
              }
              else {
                pcVar10 = (char *)&aSH;
LAB_0002e6c6:
                *(byte *)((int)puVar9 + -0xffffffff00000004) = 0xd2;
                *(byte *)((int)puVar9 + -0xffffffff00000003) = 0xe6;
                *(byte *)((int)puVar9 + -0xffffffff00000002) = 2;
                *(byte *)((int)puVar9 + -0xffffffff00000001) = 0;
                strcat((char *)((int)puVar9 + 0x5d4),pcVar10);
              }
              *(byte *)((int)puVar9 + -0xffffffff00000004) = 0xe5;
              *(byte *)((int)puVar9 + -0xffffffff00000003) = 0xe6;
              *(byte *)((int)puVar9 + -0xffffffff00000002) = 2;
              *(byte *)((int)puVar9 + -0xffffffff00000001) = 0;
              print_text_at(0xe6,iVar3,(byte *)((int)puVar9 + 0x5d4));
              *(byte *)((int)puVar9 + 0x7ec) = 0xff;
              *(uint *)((int)puVar9 + -4) = (uint)pbVar14[8];
              *(uint *)((int)puVar9 + -8) = (uint)pbVar14[7];
              *(undefined1 **)((int)puVar9 + -0xc) = a02d02d;
              *(byte **)((int)puVar9 + -0x10) = (byte *)((int)puVar9 + 0x5d4);
              *(byte *)((int)puVar9 + -0xffffffff00000014) = 0xb;
              *(byte *)((int)puVar9 + -0xffffffff00000013) = 0xe7;
              *(byte *)((int)puVar9 + -0xffffffff00000012) = 2;
              *(byte *)((int)puVar9 + -0xffffffff00000011) = 0;
              sprintf(*(char **)((int)puVar9 + -0x10),*(char **)((int)puVar9 + -0xc));
              *(byte *)((int)puVar9 + -0xffffffff00000004) = 0x21;
              *(byte *)((int)puVar9 + -0xffffffff00000003) = 0xe7;
              *(byte *)((int)puVar9 + -0xffffffff00000002) = 2;
              *(byte *)((int)puVar9 + -0xffffffff00000001) = 0;
              print_text_at(0x20d,iVar3);
              uVar17 = (uint)byte_d42c3;
              if (pbVar14[3] != 0xff) {
                *(uint *)((int)puVar9 + 0x7c4) = (uint)pbVar14[3];
                *(byte *)((int)puVar9 + -0xffffffff00000004) = 0x7a;
                *(byte *)((int)puVar9 + -0xffffffff00000003) = 0xe7;
                *(byte *)((int)puVar9 + -0xffffffff00000002) = 2;
                *(byte *)((int)puVar9 + -0xffffffff00000001) = 0;
                iVar13 = sub_1463d(*(undefined4 *)((int)puVar9 + 0x764),
                                   (byte *)((int)puVar9 + 0x69c));
                *(int *)((int)puVar9 + 0x788) = iVar13;
                if (iVar13 == 0) {
                  *(byte *)((int)puVar9 + -0xffffffff00000004) = 0x9f;
                  *(byte *)((int)puVar9 + -0xffffffff00000003) = 0xe7;
                  *(byte *)((int)puVar9 + -0xffffffff00000002) = 2;
                  *(byte *)((int)puVar9 + -0xffffffff00000001) = 0;
                  sub_29c75((byte *)((int)puVar9 + 0x734),0,(byte *)((int)puVar9 + 0x6af),200);
                  *(byte **)((int)puVar9 + -4) = (byte *)((int)puVar9 + 0x734);
                  *(undefined **)((int)puVar9 + -8) = &unk_c1675;
                  *(byte **)((int)puVar9 + -0xc) = (byte *)((int)puVar9 + 0x5d4);
                  *(byte *)((int)puVar9 + -0xffffffff00000010) = 0xb9;
                  *(byte *)((int)puVar9 + -0xffffffff0000000f) = 0xe7;
                  *(byte *)((int)puVar9 + -0xffffffff0000000e) = 2;
                  *(byte *)((int)puVar9 + -0xffffffff0000000d) = 0;
                  sprintf(*(char **)((int)puVar9 + -0xc),*(char **)((int)puVar9 + -8));
                }
                if (pbVar14[4] != 0xff) {
                  *(uint *)((int)puVar9 + 0x7c4) = (uint)pbVar14[4];
                  *(byte *)((int)puVar9 + -0xffffffff00000004) = 0xc;
                  *(byte *)((int)puVar9 + -0xffffffff00000003) = 0xe8;
                  *(byte *)((int)puVar9 + -0xffffffff00000002) = 2;
                  *(byte *)((int)puVar9 + -0xffffffff00000001) = 0;
                  iVar13 = sub_1463d(*(undefined4 *)((int)puVar9 + 0x764),
                                     (byte *)((int)puVar9 + 0x69c));
                  *(int *)((int)puVar9 + 0x788) = iVar13;
                  if (iVar13 == 0) {
                    *(byte *)((int)puVar9 + -0xffffffff00000004) = 0x31;
                    *(byte *)((int)puVar9 + -0xffffffff00000003) = 0xe8;
                    *(byte *)((int)puVar9 + -0xffffffff00000002) = 2;
                    *(byte *)((int)puVar9 + -0xffffffff00000001) = 0;
                    sub_29c75((byte *)((int)puVar9 + 0x734),0);
                    *(byte *)((int)puVar9 + -0xffffffff00000004) = 0x42;
                    *(byte *)((int)puVar9 + -0xffffffff00000003) = 0xe8;
                    *(byte *)((int)puVar9 + -0xffffffff00000002) = 2;
                    *(byte *)((int)puVar9 + -0xffffffff00000001) = 0;
                    strcat((char *)((int)puVar9 + 0x5d4),(char *)&asc_c1679);
                    *(byte *)((int)puVar9 + -0xffffffff00000004) = 0x55;
                    *(byte *)((int)puVar9 + -0xffffffff00000003) = 0xe8;
                    *(byte *)((int)puVar9 + -0xffffffff00000002) = 2;
                    *(byte *)((int)puVar9 + -0xffffffff00000001) = 0;
                    strcat((char *)((int)puVar9 + 0x5d4),(char *)((int)puVar9 + 0x734));
                  }
                }
                if (*(int *)((int)puVar9 + 0x788) == 0) {
                  *(byte *)((int)puVar9 + -0xffffffff00000004) = 0x70;
                  *(byte *)((int)puVar9 + -0xffffffff00000003) = 0xe8;
                  *(byte *)((int)puVar9 + -0xffffffff00000002) = 2;
                  *(byte *)((int)puVar9 + -0xffffffff00000001) = 0;
                  strcat((char *)((int)puVar9 + 0x5d4),&unk_c167c);
                  *(byte *)((int)puVar9 + -0xffffffff00000004) = 0x83;
                  *(byte *)((int)puVar9 + -0xffffffff00000003) = 0xe8;
                  *(byte *)((int)puVar9 + -0xffffffff00000002) = 2;
                  *(byte *)((int)puVar9 + -0xffffffff00000001) = 0;
                  print_text_at(0xe6,iVar3 + uVar17);
                }
              }
              iVar3 = iVar3 + uVar17 + (uint)byte_d42c3;
            }
          }
        }
      }
      else if (bVar6 < 3) {
        if ((((*(byte *)puVar9 & 2) != 0) && (*(byte *)((int)puVar9 + 0x7e0) <= pbVar14[5])) &&
           (pbVar14[5] <= *(byte *)((int)puVar9 + 0x7dc))) {
          *(byte **)((int)puVar9 + -4) = (byte *)((int)puVar9 + (uint)*pbVar15 * 0x2e8 + 4);
          *(undefined3 **)((int)puVar9 + -8) = &aS_c164b;
          *(byte **)((int)puVar9 + -0xc) = (byte *)((int)puVar9 + 0x5d4);
          *(byte *)((int)puVar9 + -0xffffffff00000010) = 0xe6;
          *(byte *)((int)puVar9 + -0xffffffff0000000f) = 0xe8;
          *(byte *)((int)puVar9 + -0xffffffff0000000e) = 2;
          *(byte *)((int)puVar9 + -0xffffffff0000000d) = 0;
          sprintf(*(char **)((int)puVar9 + -0xc),*(char **)((int)puVar9 + -8));
          *(byte *)((int)puVar9 + -0xffffffff00000004) = 0xfc;
          *(byte *)((int)puVar9 + -0xffffffff00000003) = 0xe8;
          *(byte *)((int)puVar9 + -0xffffffff00000002) = 2;
          *(byte *)((int)puVar9 + -0xffffffff00000001) = 0;
          print_text_at(0x91,iVar3,(byte *)((int)puVar9 + 0x5d4));
          *(uint *)((int)puVar9 + 0x7c4) = (uint)pbVar14[2];
          *(byte *)((int)puVar9 + -0xffffffff00000004) = 0x40;
          *(byte *)((int)puVar9 + -0xffffffff00000003) = 0xe9;
          *(byte *)((int)puVar9 + -0xffffffff00000002) = 2;
          *(byte *)((int)puVar9 + -0xffffffff00000001) = 0;
          iVar13 = sub_1463d(*(undefined4 *)((int)puVar9 + 0x764),(byte *)((int)puVar9 + 0x69c));
          *(int *)((int)puVar9 + 0x788) = iVar13;
          if (iVar13 == 0) {
            *(byte *)((int)puVar9 + -0xffffffff00000004) = 0x62;
            *(byte *)((int)puVar9 + -0xffffffff00000003) = 0xe9;
            *(byte *)((int)puVar9 + -0xffffffff00000002) = 2;
            *(byte *)((int)puVar9 + -0xffffffff00000001) = 0;
            print_text_at(0xdc,iVar3,(byte *)((int)puVar9 + 0x6af));
            *(uint *)((int)puVar9 + -4) = (uint)pbVar14[7];
            *(uint *)((int)puVar9 + -8) = (uint)pbVar14[6];
            *(undefined1 **)((int)puVar9 + -0xc) = a02d02d;
            *(byte **)((int)puVar9 + -0x10) = (byte *)((int)puVar9 + 0x5d4);
            *(byte *)((int)puVar9 + -0xffffffff00000014) = 0x80;
            *(byte *)((int)puVar9 + -0xffffffff00000013) = 0xe9;
            *(byte *)((int)puVar9 + -0xffffffff00000012) = 2;
            *(byte *)((int)puVar9 + -0xffffffff00000011) = 0;
            sprintf(*(char **)((int)puVar9 + -0x10),*(char **)((int)puVar9 + -0xc));
            *(byte *)((int)puVar9 + -0xffffffff00000004) = 0x96;
            *(byte *)((int)puVar9 + -0xffffffff00000003) = 0xe9;
            *(byte *)((int)puVar9 + -0xffffffff00000002) = 2;
            *(byte *)((int)puVar9 + -0xffffffff00000001) = 0;
            print_text_at(0x229,iVar3,(byte *)((int)puVar9 + 0x5d4));
            uVar17 = (uint)byte_d42c3;
            bVar6 = pbVar14[4];
            if (bVar6 == 0xff) {
              *(undefined **)((int)puVar9 + -4) = (&off_cd304)[pbVar14[3]];
              *(char **)((int)puVar9 + -8) = aSS_c167e;
              *(byte **)((int)puVar9 + -0xc) = (byte *)((int)puVar9 + 0x5d4);
              *(byte *)((int)puVar9 + -0xffffffff00000010) = 0xc6;
              *(byte *)((int)puVar9 + -0xffffffff0000000f) = 0xe9;
              *(byte *)((int)puVar9 + -0xffffffff0000000e) = 2;
              *(byte *)((int)puVar9 + -0xffffffff0000000d) = 0;
              sprintf(*(char **)((int)puVar9 + -0xc),*(char **)((int)puVar9 + -8));
            }
            else {
              *(undefined **)((int)puVar9 + -4) = (&off_cd304)[pbVar14[3]];
              *(uint *)((int)puVar9 + -8) = (uint)bVar6;
              *(char **)((int)puVar9 + -0xc) = aDMinS;
              *(byte **)((int)puVar9 + -0x10) = (byte *)((int)puVar9 + 0x5d4);
              *(byte *)((int)puVar9 + -0xffffffff00000014) = 0xef;
              *(byte *)((int)puVar9 + -0xffffffff00000013) = 0xe9;
              *(byte *)((int)puVar9 + -0xffffffff00000012) = 2;
              *(byte *)((int)puVar9 + -0xffffffff00000011) = 0;
              sprintf(*(char **)((int)puVar9 + -0x10),*(char **)((int)puVar9 + -0xc));
            }
            *(byte *)((int)puVar9 + -0xffffffff00000004) = 5;
            *(byte *)((int)puVar9 + -0xffffffff00000003) = 0xea;
            *(byte *)((int)puVar9 + -0xffffffff00000002) = 2;
            *(byte *)((int)puVar9 + -0xffffffff00000001) = 0;
            print_text_at(0xdc,iVar3 + uVar17);
            iVar3 = iVar3 + uVar17 + (uint)byte_d42c3;
            *(byte *)((int)puVar9 + 0x7e8) = 0xff;
          }
        }
      }
      else if (bVar6 == 4) {
        bVar6 = *(byte *)((int)puVar9 + 0x7f0) + 1;
        *(byte *)((int)puVar9 + 0x7f0) = bVar6;
        if ((*(byte *)((int)puVar9 + 0x7e0) <= bVar6) && (bVar6 <= *(byte *)((int)puVar9 + 0x7dc)))
        {
          iVar3 = 0x177;
          *(byte *)((int)puVar9 + 0x7b8) = 0xff;
          *(byte *)((int)puVar9 + 0x7b9) = 0xff;
          *(byte *)((int)puVar9 + 0x7ba) = 0xff;
          *(byte *)((int)puVar9 + 0x7bb) = 0xff;
          *(byte *)((int)puVar9 + 0x7b0) = 0xff;
          *(byte *)((int)puVar9 + 0x7b1) = 0xff;
          *(byte *)((int)puVar9 + 0x7b2) = 0xff;
          *(byte *)((int)puVar9 + 0x7b3) = 0xff;
        }
      }
      *(int *)((int)puVar9 + 0x778) = *(int *)((int)puVar9 + 0x778) + 1;
      if ((((int)(0x177 - (uint)byte_d42c3) <= iVar3) || (*(int *)((int)puVar9 + 0x7b8) != 0)) ||
         ((*(int *)((int)puVar9 + 0x780) != 0 || (*(int *)((int)puVar9 + 0x788) != 0)))) {
        if ((*(byte *)puVar9 & 1) != 0) {
          *(byte *)((int)puVar9 + 2000) = 0;
          *(byte *)((int)puVar9 + 0x7d1) = 0;
          *(byte *)((int)puVar9 + 0x7c8) = 0;
          *(byte *)((int)puVar9 + 0x7c9) = 0;
          for (iVar3 = 0; bVar6 = *(byte *)((int)puVar9 + 0x7d8), iVar3 < (int)(uint)bVar6;
              iVar3 = iVar3 + 1) {
            piVar16 = (int *)(iVar3 * 4 + *(int *)((int)puVar9 + 0x7ac));
            *(byte *)((int)puVar9 + 2000) = *(byte *)((int)puVar9 + 2000) + *(char *)*piVar16;
            *(byte *)((int)puVar9 + 0x7d1) =
                 *(byte *)((int)puVar9 + 0x7d1) + *(char *)(*piVar16 + 2);
            *(byte *)((int)puVar9 + 0x7c8) =
                 *(byte *)((int)puVar9 + 0x7c8) + *(char *)(*piVar16 + 1);
            *(byte *)((int)puVar9 + 0x7c9) =
                 *(byte *)((int)puVar9 + 0x7c9) + *(char *)(*piVar16 + 3);
          }
          *(char **)((int)puVar9 + -4) = aShotsOnGoal;
          *(byte **)((int)puVar9 + -8) = (byte *)((int)puVar9 + 0x5d4);
          *(byte *)((int)puVar9 + -0xffffffff0000000c) = 0x13;
          *(byte *)((int)puVar9 + -0xffffffff0000000b) = 0xeb;
          *(byte *)((int)puVar9 + -0xffffffff0000000a) = 2;
          *(byte *)((int)puVar9 + -0xffffffff00000009) = 0;
          sprintf(*(char **)((int)puVar9 + -8),*(char **)((int)puVar9 + -4));
          *(byte **)((int)puVar9 + -4) = (byte *)((int)puVar9 + 0x5d4);
          *(byte *)((int)puVar9 + -0xffffffff00000008) = 0x23;
          *(byte *)((int)puVar9 + -0xffffffff00000007) = 0xeb;
          *(byte *)((int)puVar9 + -0xffffffff00000006) = 2;
          *(byte *)((int)puVar9 + -0xffffffff00000005) = 0;
          iVar3 = textwidth();
          *(byte *)((int)puVar9 + -0xffffffff00000004) = 0x4c;
          *(byte *)((int)puVar9 + -0xffffffff00000003) = 0xeb;
          *(byte *)((int)puVar9 + -0xffffffff00000002) = 2;
          *(byte *)((int)puVar9 + -0xffffffff00000001) = 0;
          print_text_at((500 - iVar3) / 2 + 0x86,400,(byte *)((int)puVar9 + 0x5d4));
          uVar17 = (uint)byte_d42c3;
          *(uint *)((int)puVar9 + -4) = (uint)*(byte *)((int)puVar9 + 0x7c8);
          iVar13 = (uint)bVar6 * 4 + *(int *)((int)puVar9 + 0x7ac);
          *(uint *)((int)puVar9 + -8) = (uint)*(byte *)(*(int *)(iVar13 + -4) + 1);
          *(byte **)((int)puVar9 + -0xc) = (byte *)((int)puVar9 + 0x1e);
          *(char **)((int)puVar9 + -0x10) = aSDD;
          *(byte **)((int)puVar9 + -0x14) = (byte *)((int)puVar9 + 0x5d4);
          *(byte *)((int)puVar9 + -0xffffffff00000018) = 0x92;
          *(byte *)((int)puVar9 + -0xffffffff00000017) = 0xeb;
          *(byte *)((int)puVar9 + -0xffffffff00000016) = 2;
          *(byte *)((int)puVar9 + -0xffffffff00000015) = 0;
          sprintf(*(char **)((int)puVar9 + -0x14),*(char **)((int)puVar9 + -0x10));
          *(byte **)((int)puVar9 + -4) = (byte *)((int)puVar9 + 0x5d4);
          *(byte *)((int)puVar9 + -0xffffffff00000008) = 0xa2;
          *(byte *)((int)puVar9 + -0xffffffff00000007) = 0xeb;
          *(byte *)((int)puVar9 + -0xffffffff00000006) = 2;
          *(byte *)((int)puVar9 + -0xffffffff00000005) = 0;
          iVar3 = textwidth();
          *(byte *)((int)puVar9 + -0xffffffff00000004) = 0xbd;
          *(byte *)((int)puVar9 + -0xffffffff00000003) = 0xeb;
          *(byte *)((int)puVar9 + -0xffffffff00000002) = 2;
          *(byte *)((int)puVar9 + -0xffffffff00000001) = 0;
          print_text_at(0x161 - iVar3,uVar17 + 400,(byte *)((int)puVar9 + 0x5d4));
          *(uint *)((int)puVar9 + -4) = (uint)*(byte *)((int)puVar9 + 0x7c9);
          *(uint *)((int)puVar9 + -8) = (uint)*(byte *)(*(int *)(iVar13 + -4) + 3);
          *(byte **)((int)puVar9 + -0xc) = (byte *)((int)puVar9 + 0x306);
          *(char **)((int)puVar9 + -0x10) = aSDD;
          *(byte **)((int)puVar9 + -0x14) = (byte *)((int)puVar9 + 0x5d4);
          *(byte *)((int)puVar9 + -0xffffffff00000018) = 0xed;
          *(byte *)((int)puVar9 + -0xffffffff00000017) = 0xeb;
          *(byte *)((int)puVar9 + -0xffffffff00000016) = 2;
          *(byte *)((int)puVar9 + -0xffffffff00000015) = 0;
          sprintf(*(char **)((int)puVar9 + -0x14),*(char **)((int)puVar9 + -0x10));
          *(byte *)((int)puVar9 + -0xffffffff00000004) = 3;
          *(byte *)((int)puVar9 + -0xffffffff00000003) = 0xec;
          *(byte *)((int)puVar9 + -0xffffffff00000002) = 2;
          *(byte *)((int)puVar9 + -0xffffffff00000001) = 0;
          print_text_at(0x1a5,uVar17 + 400);
        }
        pbVar14 = (byte *)puVar9;
        if ((*(int *)((int)puVar9 + 0x790) == 0) && ((*(byte *)puVar9 & 0x24) == 0)) {
          if (((*(byte *)puVar9 & 1) != 0) && (*(int *)((int)puVar9 + 0x794) != 0)) {
            *(byte *)((int)puVar9 + 0x7a4) = 0;
            *(byte *)((int)puVar9 + 0x7a5) = 0;
            *(byte *)((int)puVar9 + 0x7a6) = 0;
            *(byte *)((int)puVar9 + 0x7a7) = 0;
            *(byte *)((int)puVar9 + 0x794) = 0;
            *(byte *)((int)puVar9 + 0x795) = 0;
            *(byte *)((int)puVar9 + 0x796) = 0;
            *(byte *)((int)puVar9 + 0x797) = 0;
            if ((dword_c53f7 == 1) ||
               (*(byte *)((int)puVar9 + 0x7e0) != *(byte *)((int)puVar9 + 0x7dc))) {
              uVar4 = 0;
              uVar17 = 0;
            }
            else {
              bVar6 = *(byte *)((int)puVar9 + 0x7d8);
              if (bVar6 < 4) {
                uVar17 = (uint)bVar6;
                uVar4 = 0;
              }
              else if (((bVar6 < 7) &&
                       (*(byte *)((int)puVar9 + 0x7cc) == *(byte *)((int)puVar9 + 0x7cd))) &&
                      (0x443 < dword_dc234)) {
                uVar17 = bVar6 - 3;
                uVar4 = 0xffffffff;
              }
              else {
                uVar4 = 0xffffffff;
                uVar17 = 0;
              }
            }
            pbVar14 = (byte *)((int)puVar9 + -4);
            *(byte *)((int)puVar9 + -0xffffffff00000004) = 0xb9;
            *(byte *)((int)puVar9 + -0xffffffff00000003) = 0xec;
            *(byte *)((int)puVar9 + -0xffffffff00000002) = 2;
            *(byte *)((int)puVar9 + -0xffffffff00000001) = 0;
            say_period_score(uVar17,uVar4);
          }
          *(undefined4 *)(pbVar14 + 0x790) = 1;
        }
        if (*(int *)(pbVar14 + 0x7b0) == 0) {
          for (iVar3 = *(int *)(pbVar14 + 0x778);
              *(char *)(iVar3 * 0xb + *(int *)(pbVar14 + 0x7c0)) != '\x04'; iVar3 = iVar3 + 1) {
            if (((*(char *)(iVar3 * 0xb + *(int *)(pbVar14 + 0x7c0)) == '\x01') &&
                ((*pbVar14 & 1) != 0)) ||
               ((*(char *)(iVar3 * 0xb + *(int *)(pbVar14 + 0x7c0)) == '\x02' &&
                ((*pbVar14 & 2) != 0)))) {
              iVar3 = *(int *)(pbVar14 + 0x778);
              break;
            }
          }
          *(int *)(pbVar14 + 0x778) = iVar3;
          if (*(char *)(iVar3 * 0xb + *(int *)(pbVar14 + 0x7c0)) == '\x04') {
            pbVar14[0x7b0] = 0xff;
            pbVar14[0x7b1] = 0xff;
            pbVar14[0x7b2] = 0xff;
            pbVar14[0x7b3] = 0xff;
            *(int *)(pbVar14 + 0x778) = iVar3 + 1;
          }
        }
        if ((pbVar14[0x7ec] == 0) && ((*pbVar14 & 1) != 0)) {
          *(char **)(pbVar14 + -4) = aNoScoring;
          pbVar14[-0xffffffff00000008] = 0x76;
          pbVar14[-0xffffffff00000007] = 0xed;
          pbVar14[-0xffffffff00000006] = 2;
          pbVar14[-0xffffffff00000005] = 0;
          iVar3 = textwidth();
          pbVar14[-0xffffffff00000004] = 0x9d;
          pbVar14[-0xffffffff00000003] = 0xed;
          pbVar14[-0xffffffff00000002] = 2;
          pbVar14[-0xffffffff00000001] = 0;
          print_text_at((500 - iVar3) / 2 + 0x8c,0x10b);
        }
        if ((pbVar14[0x7e8] == 0) && ((*pbVar14 & 2) != 0)) {
          *(char **)(pbVar14 + -4) = aNoPenalties;
          pbVar14[-0xffffffff00000008] = 0xb7;
          pbVar14[-0xffffffff00000007] = 0xed;
          pbVar14[-0xffffffff00000006] = 2;
          pbVar14[-0xffffffff00000005] = 0;
          iVar3 = textwidth();
          pbVar14[-0xffffffff00000004] = 0xde;
          pbVar14[-0xffffffff00000003] = 0xed;
          pbVar14[-0xffffffff00000002] = 2;
          pbVar14[-0xffffffff00000001] = 0;
          print_text_at((500 - iVar3) / 2 + 0x8c,0x10b);
        }
        if ((pbVar14[0x7d8] == pbVar14[0x7dc]) &&
           ((*(int *)(pbVar14 + 0x778) == *(int *)(pbVar14 + 0x7bc) ||
            (*(char *)(((*(int *)(pbVar14 + 0x778) * 0x10 + *(int *)(pbVar14 + 0x778) * -4) -
                       *(int *)(pbVar14 + 0x778)) + *(int *)(pbVar14 + 0x7c0)) == '\x04')))) {
          pbVar14[0x780] = 0xff;
          pbVar14[0x781] = 0xff;
          pbVar14[0x782] = 0xff;
          pbVar14[0x783] = 0xff;
        }
        if (*(int *)(pbVar14 + 0x7b0) != 0) {
          if (pbVar14[0x7d8] < 5) {
            pbVar14[0x7a4] = 0xff;
            pbVar14[0x7a5] = 0xff;
            pbVar14[0x7a6] = 0xff;
            pbVar14[0x7a7] = 0xff;
          }
          pbVar14[0x774] = 1;
          pbVar14[0x775] = 0;
          pbVar14[0x776] = 0;
          pbVar14[0x777] = 0;
          pbVar14[0x7d8] = pbVar14[0x7d8] + 1;
        }
        pbVar14[0x7b0] = 0;
        pbVar14[0x7b1] = 0;
        pbVar14[0x7b2] = 0;
        pbVar14[0x7b3] = 0;
        pbVar14[0x7ec] = 0;
        pbVar14[0x7e8] = 0;
        if (*(int *)(pbVar14 + 0x798) != 0) {
          pbVar14[-0xffffffff00000004] = 0x8f;
          pbVar14[-0xffffffff00000003] = 0xee;
          pbVar14[-0xffffffff00000002] = 2;
          pbVar14[-0xffffffff00000001] = 0;
          fade_palette(0,*(undefined4 *)(pbVar14 + 0x7a8));
          pbVar14[0x798] = 0;
          pbVar14[0x799] = 0;
          pbVar14[0x79a] = 0;
          pbVar14[0x79b] = 0;
        }
        pbVar14[-0xffffffff00000004] = 0xb3;
        pbVar14[-0xffffffff00000003] = 0xee;
        pbVar14[-0xffffffff00000002] = 2;
        pbVar14[-0xffffffff00000001] = 0;
        iVar13 = sub_33e6a(1000);
        *(int *)(pbVar14 + 0x7b4) = iVar13;
        pbVar14[0x7b8] = 0;
        pbVar14[0x7b9] = 0;
        pbVar14[0x7ba] = 0;
        pbVar14[0x7bb] = 0;
        iVar3 = 0xa0;
        puVar9 = (uint *)pbVar14;
        if ((((*(int *)(pbVar14 + 0x780) == 0) && (*(int *)(pbVar14 + 0x788) == 0)) && (iVar13 < 2))
           && (*(int *)(pbVar14 + 0x778) < *(int *)(pbVar14 + 0x7bc))) {
          if (*(int *)(pbVar14 + 0x774) == 0) {
            pbVar14[-0xffffffff00000004] = 0xe0;
            pbVar14[-0xffffffff00000003] = 1;
            pbVar14[-0xffffffff00000002] = 0;
            pbVar14[-0xffffffff00000001] = 0;
            pbVar14[-0xffffffff00000008] = 0x8c;
            pbVar14[-0xffffffff00000007] = 0;
            pbVar14[-0xffffffff00000006] = 0;
            pbVar14[-0xffffffff00000005] = 0;
            pbVar14[-0xffffffff0000000c] = 0x80;
            pbVar14[-0xffffffff0000000b] = 2;
            pbVar14[-0xffffffff0000000a] = 0;
            pbVar14[-0xffffffff00000009] = 0;
            pbVar14[-0xffffffff00000010] = 0x80;
            pbVar14[-0xffffffff0000000f] = 0;
            pbVar14[-0xffffffff0000000e] = 0;
            pbVar14[-0xffffffff0000000d] = 0;
          }
          else {
            pbVar14[-0xffffffff00000004] = 0x22;
            pbVar14[-0xffffffff00000003] = 0xef;
            pbVar14[-0xffffffff00000002] = 2;
            pbVar14[-0xffffffff00000001] = 0;
            fade_palette_to(1,*(undefined4 *)(pbVar14 + 0x7a8),0x10);
            pbVar14[0x798] = 1;
            pbVar14[0x799] = 0;
            pbVar14[0x79a] = 0;
            pbVar14[0x79b] = 0;
            pbVar14[0x774] = 0;
            pbVar14[0x775] = 0;
            pbVar14[0x776] = 0;
            pbVar14[0x777] = 0;
            pbVar14[-0xffffffff00000004] = 0xe0;
            pbVar14[-0xffffffff00000003] = 1;
            pbVar14[-0xffffffff00000002] = 0;
            pbVar14[-0xffffffff00000001] = 0;
            pbVar14[-0xffffffff00000008] = 0x8c;
            pbVar14[-0xffffffff00000007] = 0;
            pbVar14[-0xffffffff00000006] = 0;
            pbVar14[-0xffffffff00000005] = 0;
            pbVar14[-0xffffffff0000000c] = 0x80;
            pbVar14[-0xffffffff0000000b] = 2;
            pbVar14[-0xffffffff0000000a] = 0;
            pbVar14[-0xffffffff00000009] = 0;
            pbVar14[-0xffffffff00000010] = 0;
            pbVar14[-0xffffffff0000000f] = 0;
            pbVar14[-0xffffffff0000000e] = 0;
            pbVar14[-0xffffffff0000000d] = 0;
          }
          pbVar14[-0xffffffff00000014] = 0x5f;
          pbVar14[-0xffffffff00000013] = 0xef;
          pbVar14[-0xffffffff00000012] = 2;
          pbVar14[-0xffffffff00000011] = 0;
          setclip();
          *(undefined4 *)(pbVar14 + -4) = *(undefined4 *)(pbVar14 + 0x79c);
          pbVar14[-0xffffffff00000008] = 0x6f;
          pbVar14[-0xffffffff00000007] = 0xef;
          pbVar14[-0xffffffff00000006] = 2;
          pbVar14[-0xffffffff00000005] = 0;
          drawshape_remap_home();
          if ((*pbVar14 & 3) == 0) {
            *(byte **)(pbVar14 + -4) = pbVar14 + 0x7cc;
            *(undefined4 *)(pbVar14 + -8) = *(undefined4 *)(pbVar14 + 0x7a0);
            pbVar14[-0xffffffff0000000c] = 7;
            pbVar14[-0xffffffff0000000b] = 0xf0;
            pbVar14[-0xffffffff0000000a] = 2;
            pbVar14[-0xffffffff00000009] = 0;
            sub_7df4e(*(undefined4 *)pbVar14,pbVar14[0x7d8],*(undefined4 *)(pbVar14 + 0x7a8),
                      pbVar14 + 0x668);
          }
          else {
            *(byte **)(pbVar14 + -4) = pbVar14 + 0x7cc;
            *(undefined4 *)(pbVar14 + -8) = *(undefined4 *)(pbVar14 + 0x7a0);
            pbVar14[-0xffffffff0000000c] = 0xa8;
            pbVar14[-0xffffffff0000000b] = 0xef;
            pbVar14[-0xffffffff0000000a] = 2;
            pbVar14[-0xffffffff00000009] = 0;
            sub_7df4e(*(undefined4 *)pbVar14,pbVar14[0x7d8],*(undefined4 *)(pbVar14 + 0x7a8),
                      pbVar14 + 0x668);
            pbVar14[-0xffffffff00000004] = 0x50;
            pbVar14[-0xffffffff00000003] = 0;
            pbVar14[-0xffffffff00000002] = 0;
            pbVar14[-0xffffffff00000001] = 0;
            pbVar14[-0xffffffff00000008] = 0x3d;
            pbVar14[-0xffffffff00000007] = 0;
            pbVar14[-0xffffffff00000006] = 0;
            pbVar14[-0xffffffff00000005] = 0;
            *(undefined4 *)(pbVar14 + -0xc) = *(undefined4 *)(dword_dd66c + 0x2c);
            pbVar14[-0xffffffff00000010] = 0xba;
            pbVar14[-0xffffffff0000000f] = 0xef;
            pbVar14[-0xffffffff0000000e] = 2;
            pbVar14[-0xffffffff0000000d] = 0;
            drawshape_remap_centered();
            pbVar14[-0xffffffff00000004] = 0x50;
            pbVar14[-0xffffffff00000003] = 0;
            pbVar14[-0xffffffff00000002] = 0;
            pbVar14[-0xffffffff00000001] = 0;
            pbVar14[-0xffffffff00000008] = 0x21;
            pbVar14[-0xffffffff00000007] = 2;
            pbVar14[-0xffffffff00000006] = 0;
            pbVar14[-0xffffffff00000005] = 0;
            *(undefined4 *)(pbVar14 + -0xc) = *(undefined4 *)(dword_dd670 + 0x2c);
            pbVar14[-0xffffffff00000010] = 0xd2;
            pbVar14[-0xffffffff0000000f] = 0xef;
            pbVar14[-0xffffffff0000000e] = 2;
            pbVar14[-0xffffffff0000000d] = 0;
            drawshape_remap_centered();
          }
          if ((((*pbVar14 & 1) != 0) && (*(int *)(pbVar14 + 0x7a4) != 0)) &&
             ((pbVar14[0x7a4] = 0, pbVar14[0x7a5] = 0, pbVar14[0x7a6] = 0, pbVar14[0x7a7] = 0,
              dword_c53f7 != 1 && (pbVar14[0x7e0] == pbVar14[0x7dc])))) {
            bVar6 = pbVar14[0x7d8];
            if (bVar6 < 4) {
              uVar17 = (uint)bVar6;
              uVar4 = 0;
            }
            else if (((bVar6 < 7) && (pbVar14[0x7cc] == pbVar14[0x7cd])) && (0x443 < dword_dc234)) {
              uVar17 = bVar6 - 3;
              uVar4 = 0xffffffff;
            }
            else {
              uVar4 = 0xffffffff;
              uVar17 = 0;
            }
            puVar9 = (uint *)(pbVar14 + -4);
            pbVar14[-0xffffffff00000004] = 0x56;
            pbVar14[-0xffffffff00000003] = 0xf0;
            pbVar14[-0xffffffff00000002] = 2;
            pbVar14[-0xffffffff00000001] = 0;
            say_period_score(uVar17,uVar4);
          }
        }
      }
    }
  }
  if ((sound_enabled != '\0') && (dword_c721d != 0)) {
    *(undefined4 *)((int)puVar9 + -4) = 0x2f150;
    sound_fade(dword_d2431,3,100);
  }
  *(undefined4 *)((int)puVar9 + -4) = 0x2f166;
  fade_palette(1,*(undefined4 *)((int)puVar9 + 0x7a8),0x10);
  if ((sound_enabled == '\0') || (dword_c721d == 0)) {
    *(undefined4 *)((int)puVar9 + -4) = 0x2f1ac;
    stop_crowd_loop();
  }
  else {
    do {
      *(undefined4 *)((int)puVar9 + -4) = 0x2f18a;
      iVar3 = sound_channel_status(ram0x000d242c >> 0x18,3);
    } while (iVar3 == 0);
    *(int *)((int)puVar9 + -4) = dword_c721d;
    *(undefined4 *)((int)puVar9 + -8) = 0x2f19a;
    releasememblock();
    dword_c721d = 0;
  }
  *(undefined4 *)((int)puVar9 + -4) = 0x2f1b1;
  setdefaultscreen();
  *(undefined4 *)((int)puVar9 + -4) = 0;
  *(undefined4 *)((int)puVar9 + -8) = 0x2f1b8;
  clearclip();
  if (*(int *)((int)puVar9 + 0x7ac) != 0) {
    *(int *)((int)puVar9 + -4) = *(int *)((int)puVar9 + 0x7ac);
    *(undefined4 *)((int)puVar9 + -8) = 0x2f1cc;
    freemem();
  }
  if (*(int *)((int)puVar9 + 0x7c0) != 0) {
    *(int *)((int)puVar9 + -4) = *(int *)((int)puVar9 + 0x7c0);
    *(undefined4 *)((int)puVar9 + -8) = 0x2f1e0;
    freemem();
  }
  *(undefined4 *)((int)puVar9 + -4) = 0x2f1ef;
  file_close((undefined *)((int)puVar9 + 0x75c));
  *(undefined4 *)((int)puVar9 + -4) = 0x2f1fb;
  file_close((undefined *)((int)puVar9 + 0x758));
  *(undefined4 *)((int)puVar9 + -4) = 0x2f207;
  file_close((undefined *)((int)puVar9 + 0x764));
  *(undefined4 *)((int)puVar9 + -4) = 0x2f213;
  file_close((undefined *)((int)puVar9 + 0x760));
  *(undefined **)((int)puVar9 + -4) = (undefined *)((int)puVar9 + 0x628);
  *(undefined4 *)((int)puVar9 + -8) = 0x2f220;
  setfontstate();
  *(undefined4 *)((int)puVar9 + -4) = *(undefined4 *)((int)puVar9 + 0x77c);
  *(undefined4 *)((int)puVar9 + -8) = 0x2f230;
  freemem();
  *(undefined4 *)((int)puVar9 + -4) = *(undefined4 *)((int)puVar9 + 0x78c);
  *(undefined4 *)((int)puVar9 + -8) = 0x2f240;
  freemem();
  *(undefined4 *)((int)puVar9 + -4) = *(undefined4 *)((int)puVar9 + 0x784);
  *(undefined4 *)((int)puVar9 + -8) = 0x2f250;
  freemem();
  *(int *)((int)puVar9 + -4) = dword_dd66c;
  *(undefined4 *)((int)puVar9 + -8) = 0x2f25e;
  freemem();
  *(int *)((int)puVar9 + -4) = dword_dd670;
  *(undefined4 *)((int)puVar9 + -8) = 0x2f26d;
  freemem();
  if (*(int *)((int)puVar9 + 0x76c) != 0) {
    *(undefined4 *)((int)puVar9 + -4) = 0x2f282;
    sub_8f1fe(*(int *)((int)puVar9 + 0x76c));
  }
  *(undefined4 *)((int)puVar9 + 0x780) = 0;
  if (*(int *)((int)puVar9 + 0x7b4) == 3) {
    *(undefined4 *)((int)puVar9 + 0x780) = 4;
  }
  return *(undefined4 *)((int)puVar9 + 0x780);
}


// ================================================================================================
// sub_2f2b1 @ 0x2f2b1 [__watcall]
// ================================================================================================

void __watcall sub_2f2b1(byte param_1,byte unaff_DL)

{
  byte bVar1;
  int iVar2;
  byte bVar3;
  int iVar4;
  int iVar5;
  
  __CHK(0x1c);
  bVar1 = (&unk_c8922)[param_1];
  iVar5 = 0;
  do {
    (&unk_dd730)[iVar5] = 0;
    (&unk_dd788)[iVar5 * 2] = 0;
    (&unk_dd789)[iVar5 * 2] = 0;
    do {
      iVar4 = 0;
      iVar2 = rand();
      bVar3 = (byte)((longlong)iVar2 % 0x1a);
      (&unk_dd774)[iVar5 * 2] = bVar3;
      if (((param_1 == bVar3) || (bVar3 == unaff_DL)) || (bVar1 < (byte)(&unk_c8922)[bVar3])) {
        iVar4 = -1;
      }
      iVar2 = 0;
      while ((iVar2 < iVar5 && (iVar4 == 0))) {
        if (((&unk_dd774)[iVar5 * 2] == (&unk_dd774)[iVar2 * 2]) ||
           ((&unk_dd774)[iVar5 * 2] == (&unk_dd775)[iVar2 * 2])) {
          iVar4 = -1;
        }
        iVar2 = iVar2 + 1;
      }
    } while (iVar4 != 0);
    do {
      iVar4 = 0;
      iVar2 = rand();
      bVar3 = (byte)((longlong)iVar2 % 0x1a);
      (&unk_dd775)[iVar5 * 2] = bVar3;
      if (((bVar3 == (&unk_dd774)[iVar5 * 2]) || (param_1 == bVar3)) || (bVar3 == unaff_DL)) {
        iVar4 = -1;
      }
      iVar2 = 0;
      while ((iVar2 < iVar5 && (iVar4 == 0))) {
        if (((&unk_dd775)[iVar5 * 2] == (&unk_dd774)[iVar2 * 2]) ||
           ((&unk_dd775)[iVar5 * 2] == (&unk_dd775)[iVar2 * 2])) {
          iVar4 = -1;
        }
        iVar2 = iVar2 + 1;
      }
    } while (iVar4 != 0);
    iVar5 = iVar5 + 1;
  } while (iVar5 < 6);
  return;
}


// ================================================================================================
// sub_2f3d7 @ 0x2f3d7 [__watcall]
// ================================================================================================

undefined8 __watcall sub_2f3d7(int param_1,undefined4 unaff_EDX)

{
  ulonglong uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  __CHK(0x24);
  iVar7 = 0;
  do {
    iVar5 = ((uint)(byte)(&unk_c8922)[user2_team >> 0x10] -
            (uint)(byte)(&unk_c8922)[(byte)(&unk_dd774)[iVar7 * 2]]) + param_1;
    iVar6 = (&unk_dd730)[iVar7];
    iVar4 = param_1;
    if (iVar6 <= iVar5) {
      for (; iVar6 <= iVar5; iVar6 = iVar6 + 1) {
        if (iVar6 == 4) {
          iVar2 = iVar7 * 2;
          iVar4 = CONCAT31((int3)((uint)iVar4 >> 8),(&unk_dd788)[iVar2]);
          if ((&unk_dd788)[iVar2] == (&unk_dd789)[iVar2]) {
            (&unk_dd730)[iVar7] = 4;
            uVar3 = rand();
            iVar4 = (int)(((ulonglong)uVar3 & 0xffffffff00007fff) / 100);
            if ((uint)(((ulonglong)uVar3 & 0xffffffff00007fff) % 100) < 0x47) {
              uVar3 = rand();
              iVar4 = (int)(((ulonglong)uVar3 & 0xffffffff00007fff) / 100);
              if (0x46 < (uint)(((ulonglong)uVar3 & 0xffffffff00007fff) % 100)) {
                (&unk_dd730)[iVar7] = 5;
                (&unk_dd789)[iVar2] = (&unk_dd789)[iVar2] + '\x01';
              }
            }
            else {
              (&unk_dd730)[iVar7] = 5;
              (&unk_dd788)[iVar2] = (&unk_dd788)[iVar2] + '\x01';
            }
          }
          else {
            (&unk_dd730)[iVar7] = 6;
          }
        }
        else if ((iVar6 == 5) && ((&unk_dd730)[iVar7] == 4)) {
          (&unk_dd730)[iVar7] = 5;
        }
        else {
          iVar4 = (&unk_dd730)[iVar7];
          if ((iVar4 < 3) && (iVar6 != iVar4)) {
            (&unk_dd730)[iVar7] = iVar6;
            uVar3 = rand();
            (&unk_dd788)[iVar7 * 2] =
                 (&unk_dd788)[iVar7 * 2] + (char)(((ulonglong)uVar3 & 0xffffffff00007fff) % 3);
            uVar3 = rand();
            uVar1 = ((ulonglong)uVar3 & 0xffffffff00007fff) % 3;
            iVar4 = (int)uVar1;
            (&unk_dd789)[iVar7 * 2] = (&unk_dd789)[iVar7 * 2] + (char)uVar1;
          }
        }
      }
    }
    iVar7 = iVar7 + 1;
  } while (iVar7 < 6);
  return CONCAT44(unaff_EDX,iVar4);
}


// ================================================================================================
// sub_2f580 @ 0x2f580 [__watcall]
// ================================================================================================

void __watcall sub_2f580(int param_1,undefined4 unaff_EDX,undefined4 unaff_EBX)

{
  int iVar1;
  
  __CHK(0x18);
  iVar1 = textwidth(unaff_EBX);
  if ((param_1 < 0x140) || (param_1 + iVar1 < 0x281)) {
    if ((param_1 < 0x140) && ((0xf0 < param_1 + iVar1 && (param_1 = 0xf0 - iVar1, param_1 < 8)))) {
      param_1 = 8;
    }
  }
  else {
    param_1 = 0x280 - iVar1;
  }
  print_text_at(param_1,unaff_EDX,unaff_EBX);
  return;
}


// ================================================================================================
// team_select_screen2 @ 0x2f5ee [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall team_select_screen2(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined *puVar4;
  char *pcVar5;
  int iVar6;
  int iVar7;
  undefined auStack_38c [768];
  undefined auStack_8c [64];
  char acStack_4c [20];
  int local_38 [4];
  undefined4 local_28;
  int local_24;
  int local_20;
  undefined4 uStack_1c;
  
  __CHK(0x3a4);
  local_38[0] = (int)user2_team._2_2_;
  local_38[1] = (int)_away_team_id;
  event_queue_reset();
  setdefaultscreen();
  clearclip(0);
  acStack_4c[0] = '\0';
  acStack_4c[1] = 0;
  acStack_4c[2] = 0;
  iVar7 = 0;
  do {
    setpalette(iVar7,1,acStack_4c);
    iVar7 = iVar7 + 1;
  } while (iVar7 < 0x100);
  puVar4 = install_path;
  if (byte_ed824 != '\x01') {
    puVar4 = (undefined *)0x0;
  }
  make_path(acStack_4c,puVar4,aCtbkgd_c16ac,0);
  uVar1 = loadshapes(acStack_4c,0);
  iVar7 = locateshape(uVar1,&aPal_c16b3);
  memcpy(auStack_38c,(void *)(iVar7 + 0x10),0x300);
  uVar2 = locateshape(uVar1,&aBkgd_c16b8);
  drawshape_remap_home(uVar2);
  freemem(uVar1);
  puVar4 = install_path;
  if (byte_ed828 != '\x01') {
    puVar4 = (undefined *)0x0;
  }
  make_path(acStack_4c,puVar4,aCttitle3_c16bd,0);
  uVar1 = loadshapes(acStack_4c,0);
  uVar2 = locateshape(uVar1,&aColm_c16c6);
  drawshape_remap_home(uVar2);
  uVar2 = locateshape(uVar1,&aGsta);
  drawshape_remap_home(uVar2);
  freemem(uVar1);
  puVar4 = install_path;
  if (byte_ed825 != '\x01') {
    puVar4 = (undefined *)0x0;
  }
  make_path(acStack_4c,puVar4,aCtlogo_c16d0,0);
  local_28 = loadshapes(acStack_4c,0);
  getfontstate(auStack_8c);
  setfont(font_kaufm);
  set_text_colors(0x40,0);
  local_24 = 0xb0;
  iVar7 = 0;
  do {
    iVar3 = textwidth((&off_c719c)[iVar7]);
    print_text_at((0x26c - iVar3) / 2,local_24,(&off_c719c)[iVar7]);
    local_24 = local_24 + 0x18;
    iVar7 = iVar7 + 1;
  } while (iVar7 < 0xc);
  iVar7 = 0;
  do {
    uVar1 = locateshape(local_28,(&off_c57cc)[local_38[iVar7]]);
    if (iVar7 == 0) {
      uVar2 = 0x40;
    }
    else {
      uVar2 = 0x212;
    }
    drawshape_remap_centered(uVar1,uVar2,0x4e);
    local_38[2] = iVar7 * 0x1c7;
    iVar3 = textwidth(&DAT_000dbc4a + iVar7 * 0x2e8);
    local_20 = local_38[2] + 0x49;
    print_text_at(local_20 - (iVar3 >> 1),0x8a,&DAT_000dbc4a + iVar7 * 0x2e8);
    iVar6 = iVar7 * 0x100;
    sprintf(acStack_4c,(char *)&aD_c16d7,(int)(&dword_df622)[iVar7 * 0x40] >> 0x10);
    iVar3 = textwidth(acStack_4c);
    sub_2f580(local_20 - (iVar3 >> 1),0xb0,acStack_4c);
    sprintf(acStack_4c,(char *)&aD_c16d7,(int)(&dword_df612)[iVar7 * 0x40] >> 0x10);
    iVar3 = textwidth(acStack_4c);
    sub_2f580(local_20 - (iVar3 >> 1),200,acStack_4c);
    sprintf(acStack_4c,(char *)&aD_c16d7,(int)(&unk_df62a)[iVar7 * 0x40] >> 0x10);
    iVar3 = textwidth(acStack_4c);
    sub_2f580(local_20 - (iVar3 >> 1),0xe0,acStack_4c);
    sprintf(acStack_4c,unk_c16da,*(int *)((int)&dword_df612 + iVar6 + 2) >> 0x10,
            (int)(&dword_df616)[iVar7 * 0x40] >> 0x10);
    iVar3 = textwidth(acStack_4c);
    sub_2f580(local_20 - (iVar3 >> 1),0xf8,acStack_4c);
    uStack_1c = 0x3c;
    sprintf(acStack_4c,aD02d,((int)(&unk_df61a)[iVar7 * 0x40] >> 0x10) / 0x3c,
            ((int)(&unk_df61a)[iVar7 * 0x40] >> 0x10) % 0x3c);
    iVar3 = textwidth(acStack_4c);
    sub_2f580(local_20 - (iVar3 >> 1),0x110,acStack_4c);
    sprintf(acStack_4c,(char *)&aD_c16d7,*(int *)((int)&dword_df616 + iVar6 + 2) >> 0x10);
    iVar3 = textwidth(acStack_4c);
    sub_2f580(local_20 - (iVar3 >> 1),0x128,acStack_4c);
    sprintf(acStack_4c,unk_c16da,*(int *)((int)&unk_df61a + iVar6 + 2) >> 0x10,
            (int)(&dword_df61e)[iVar7 * 0x40] >> 0x10);
    iVar3 = textwidth(acStack_4c);
    sub_2f580(local_20 - (iVar3 >> 1),0x140,acStack_4c);
    sprintf(acStack_4c,(char *)&aD_c16d7,*(int *)((int)&dword_df622 + iVar6 + 2) >> 0x10);
    iVar3 = textwidth(acStack_4c);
    sub_2f580(local_20 - (iVar3 >> 1),0x158,acStack_4c);
    sprintf(acStack_4c,(char *)&aD_c16d7,(int)(&unk_df626)[iVar7 * 0x40] >> 0x10);
    iVar3 = textwidth(acStack_4c);
    sub_2f580(local_20 - (iVar3 >> 1),0x170,acStack_4c);
    sprintf(acStack_4c,(char *)&aD_c16d7,(int)(&unk_df636)[iVar7 * 0x40] >> 0x10);
    iVar3 = textwidth(acStack_4c);
    sub_2f580(local_20 - (iVar3 >> 1),0x188,acStack_4c);
    iVar3 = *(int *)((int)&dword_df61e + iVar6 + 2) >> 0x10;
    uStack_1c = 0x3c;
    sprintf(acStack_4c,aD02d,iVar3 / 0x3c,iVar3 % 0x3c);
    iVar3 = textwidth(acStack_4c);
    sub_2f580(local_20 - (iVar3 >> 1),0x1a0);
    iVar3 = 0;
    local_24 = 0x1b8;
    if (*(short *)(&dword_df63a + iVar7 * 0x40) != 0) {
      iVar3 = (((int)(&dword_df63a)[iVar7 * 0x40] >> 0x10) * 100) /
              (*(int *)((int)&unk_df636 + iVar6 + 2) >> 0x10);
    }
    sprintf(acStack_4c,unk_c16e8,(int)(&dword_df63a)[iVar7 * 0x40] >> 0x10,
            *(int *)((int)&unk_df636 + iVar7 * 0x100 + 2) >> 0x10,iVar3);
    iVar3 = textwidth(acStack_4c);
    sub_2f580((iVar7 * 0x1c7 + 0x49) - (iVar3 >> 1),local_24,acStack_4c);
    iVar7 = iVar7 + 1;
  } while (iVar7 < 2);
  if (sound_enabled == '\0') {
    puVar4 = install_path;
    if (dword_c541f == 8) {
      pcVar5 = aMtsum_c1703;
      if (byte_ed8ce != '\x01') {
        puVar4 = (undefined *)0x0;
      }
    }
    else {
      pcVar5 = aAdsum_c1709;
      if (byte_ed7ed != '\x01') {
        puVar4 = (undefined *)0x0;
      }
    }
    make_path(acStack_4c,puVar4,pcVar5);
    dword_ccc94 = 0x20;
    local_38[3] = sub_8f13b(acStack_4c);
    dword_ccc94 = 0;
    play_sample_by_ptr();
  }
  else {
    if (dword_c721d != 0) {
      sound_fade(dword_d2431,3,0x28);
      settimeout(0x28);
      waittimeout();
      releasememblock(dword_c721d);
      dword_c721d = 0;
    }
    sub_8378c();
    puVar4 = install_path;
    if (byte_ed9ac != '\x01') {
      puVar4 = (undefined *)0x0;
    }
    make_path(acStack_4c,puVar4,aLeaguetm,&aIff_c16f5);
    dword_c721d = loadsound(acStack_4c);
    if ((dword_c721d != 0) && (((byte)option_flags & 0x40) != 0)) {
      playsample(dword_c721d,dword_d2431,3,0x7f);
    }
  }
  fade_palette(0,auStack_38c,0x10);
  sub_33e6a(2000);
  if ((sound_enabled != '\0') && (dword_c721d != 0)) {
    sound_fade(dword_d2431,3,100);
  }
  fade_palette(1,auStack_38c,0x10);
  if (sound_enabled == '\0') {
    stop_crowd_loop();
    sub_8f1fe(local_38[3]);
  }
  else if (dword_c721d != 0) {
    do {
      iVar7 = sound_channel_status(ram0x000d242c >> 0x18,3);
    } while (iVar7 == 0);
    releasememblock(dword_c721d);
    dword_c721d = 0;
  }
  setfontstate(auStack_8c);
  freemem(local_28);
  return;
}


// ================================================================================================
// sub_2fdd1 @ 0x2fdd1 [__watcall]
// ================================================================================================

undefined8 __watcall sub_2fdd1(undefined4 param_1,undefined4 unaff_EDX)

{
  int iVar1;
  undefined local_18 [4];
  undefined local_14 [4];
  undefined auStack_10 [4];
  
  __CHK(0x30);
  getmouse(auStack_10,local_14,local_18);
  iVar1 = message_dialog(0xffffffff,0xffffffff,&off_c74ab,3,&unk_c74b7,2,local_14,local_18,
                         0xffffffff);
  if (iVar1 == 1) {
    dword_dd770 = &aORG;
  }
  else {
    dword_dd770 = (undefined5 *)&aDB;
  }
  return CONCAT44(unaff_EDX,iVar1);
}


// ================================================================================================
// draw_dialog_frame @ 0x2fe49 [__watcall]
// ================================================================================================

void __watcall
draw_dialog_frame(int param_1,int param_2,int unaff_EBX,int unaff_ECX,undefined4 param_5,
                 undefined4 param_6,undefined4 param_7)

{
  int iVar1;
  int iVar2;
  
  __CHK(0x28);
  iVar2 = param_1 + -1 + unaff_EBX;
  iVar1 = param_2 + -1 + unaff_ECX;
  fillrect(param_1,param_2,unaff_EBX,unaff_ECX,param_5,iVar2);
  sub_b4fac(param_1,param_2,param_1,iVar1,param_6);
  sub_b4fac(param_1,param_2,iVar2,param_2,param_6);
  sub_b4fac(param_1,iVar1,iVar2,iVar1,param_7);
  sub_b4fac(iVar2,param_2,iVar2,iVar1,param_7);
  return;
}


// ================================================================================================
// sub_2fed2 @ 0x2fed2 [__watcall]
// ================================================================================================

undefined4 __watcall sub_2fed2(void)

{
  __CHK(4);
  return 0;
}


// ================================================================================================
// sub_2fedf @ 0x2fedf [__watcall]
// ================================================================================================

int __watcall
sub_2fedf(undefined4 param_1,char *unaff_EDX,int unaff_EBX,int unaff_ECX,int param_5,int param_6,
         int param_7,int param_8,undefined4 param_9)

{
  char cVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined8 uVar7;
  undefined auStack_120 [256];
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  
  __CHK(0x138);
  ui_shutdown();
  setdefaultscreen();
  for (iVar5 = 0; iVar5 < unaff_EBX; iVar5 = iVar5 + 1) {
    auStack_120[iVar5] = 0x4d;
  }
  auStack_120[unaff_EBX] = 0;
  iVar5 = textwidth(auStack_120);
  if (iVar5 < unaff_ECX) {
    iVar5 = unaff_ECX;
  }
  iVar5 = iVar5 + 0xc;
  iVar3 = textwidth(param_1);
  iVar3 = iVar3 + 0x10;
  if (iVar3 < iVar5) {
    iVar3 = iVar5 + 0x10;
  }
  local_20 = (uint)byte_d42c3 * 2 + 0x20;
  local_14 = (0x280 - iVar3) / 2;
  local_18 = (0x1e0 - local_20) / 2;
  save_dialog_background(local_14,local_18,iVar3,local_20);
  set_text_colors(dword_c71d8,dword_c71dc);
  draw_dialog_frame(local_14,local_18,iVar3,local_20,dword_c71cc,dword_c71d0,dword_c71d4);
  settextpos(dword_c71d8,dword_c71dc);
  local_1c = local_18 + 7;
  iVar4 = textwidth(param_1);
  iVar6 = local_14;
  print_text_at((iVar3 - iVar4) / 2 + local_14,local_1c,param_1);
  local_14 = iVar6 + (iVar3 - iVar5) / 2;
  draw_dialog_frame(local_14,local_18 + 0x1f,iVar5,0x12,dword_c71dc,dword_c71d4,dword_c71d0);
  settextpos(dword_c71d8,dword_c71dc);
  do {
    do {
      iVar3 = sub_b2cbe(1);
    } while (iVar3 != 0);
    iVar3 = sub_b2cbe(0x1c);
  } while (iVar3 != 0);
  event_queue_reset();
  if (param_5 == 0) {
    do {
      *unaff_EDX = '\0';
      iVar3 = sub_3170d(unaff_EDX,unaff_EBX,iVar5 + -8,local_14 + 6,local_18 + 0x20,sub_2fed2,0,
                        param_9);
      bVar2 = true;
      if (((param_8 != 0) && (*unaff_EDX == '\0')) && (iVar3 != 0x1b)) {
        bVar2 = false;
      }
    } while (!bVar2);
  }
  else {
    do {
      *unaff_EDX = '\0';
      sub_3170d(unaff_EDX,unaff_EBX,iVar5 + -8,local_14 + 6,local_18 + 0x20,sub_2fed2,0,param_9);
      iVar3 = 0;
      iVar6 = 0;
      while ((iVar6 < unaff_EBX &&
             (((((&unk_c4b6c)[(byte)(unaff_EDX[iVar6] + 1)] & 0x20) != 0 ||
               (cVar1 = *unaff_EDX, cVar1 == ' ')) || ((cVar1 == '\0' || (cVar1 == '-'))))))) {
        uVar7 = sub_92d7c(unaff_EDX);
        iVar3 = (int)uVar7;
        iVar6 = (int)((ulonglong)uVar7 >> 0x20) + 1;
      }
    } while ((iVar3 < param_6) || (param_7 < iVar3));
  }
  do {
    do {
      iVar5 = sub_b2cbe(1);
    } while (iVar5 != 0);
    iVar5 = sub_b2cbe(0x1c);
  } while (iVar5 != 0);
  event_queue_reset();
  sub_30f12();
  ui_init();
  return iVar3;
}


// ================================================================================================
// sub_30209 @ 0x30209 [__watcall]
// ================================================================================================

void __watcall sub_30209(int param_1,int unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  __CHK(0x14);
  uVar1 = dword_c71dc;
  uVar2 = dword_c71d8;
  if (unaff_EDX == param_1) {
    uVar1 = dword_c71d8;
    uVar2 = dword_c71dc;
  }
  settextpos(uVar2,uVar1,unaff_ECX,unaff_EBX);
  return;
}


// ================================================================================================
// sub_3023e @ 0x3023e [__watcall]
// ================================================================================================

int __watcall
sub_3023e(int param_1,int unaff_EDX,int unaff_EBX,int unaff_ECX,int param_5,int param_6)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  __CHK(0x18);
  iVar2 = -1;
  iVar1 = 0;
  while ((iVar1 < param_6 && (iVar2 < 0))) {
    iVar3 = (byte_d42c3 + 2) * iVar1 + unaff_ECX + 2;
    if ((unaff_EBX + 2 <= param_1) &&
       (((param_1 <= unaff_EBX + 2 + param_5 + -4 && (iVar3 <= unaff_EDX)) &&
        (unaff_EDX <= (int)((uint)byte_d42c3 + iVar3 + 2))))) {
      iVar2 = iVar1;
    }
    iVar1 = iVar1 + 1;
  }
  return iVar2;
}


// ================================================================================================
// sub_302b9 @ 0x302b9 [__watcall]
// ================================================================================================

void __watcall
sub_302b9(undefined4 param_1,int param_2,int param_3,int param_4,int param_5,int param_6,int param_7
         ,uint param_8,int param_9,int param_10)

{
  int iVar1;
  undefined4 uVar2;
  
  __CHK(0x28);
  param_3 = param_3 + (param_6 - param_5) * (byte_d42c3 + 2) + 2;
  param_2 = param_2 + 2;
  param_4 = param_4 + -4;
  if (((param_9 == 0) || (uVar2 = dword_c71cc, *(char *)(param_10 + param_6) == '\0')) &&
     (uVar2 = dword_c71dc, param_7 == param_6)) {
    uVar2 = dword_c71d8;
  }
  fillrect(param_2,param_3,param_4,byte_d42c3 + 2,uVar2);
  sub_30209(param_6,param_7);
  if (param_8 != 0) {
    if (param_8 < 2) {
      iVar1 = textwidth(param_1);
      iVar1 = (param_4 - iVar1) + -4;
    }
    else {
      if (param_8 != 2) goto LAB_00030386;
      iVar1 = textwidth(param_1);
      iVar1 = (param_4 - iVar1) / 2;
    }
    param_2 = param_2 + iVar1;
  }
LAB_00030386:
  draw_item_text(param_2,param_3 + 1,param_1);
  return;
}


// ================================================================================================
// sub_3039c @ 0x3039c [__watcall]
// ================================================================================================

void __watcall
sub_3039c(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,int param_5,
         undefined4 param_6,int param_7,undefined4 param_8,undefined4 param_9,undefined4 param_10)

{
  int iVar1;
  
  __CHK(0x30);
  for (iVar1 = 0; iVar1 < param_7; iVar1 = iVar1 + 1) {
    sub_302b9(*(undefined4 *)((param_5 + iVar1) * 4 + param_1),param_2,param_3,param_4,param_5,
              param_5 + iVar1,param_6,param_8,param_9,param_10);
  }
  return;
}


// ================================================================================================
// sub_303fb @ 0x303fb [__watcall]
// ================================================================================================

int __watcall
sub_303fb(int param_1,int unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX,int param_5,
         int param_6)

{
  bool bVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined4 ***pppuVar8;
  undefined4 *puVar9;
  int extraout_ECX;
  undefined4 extraout_EDX;
  undefined4 uVar10;
  undefined4 ***pppuVar11;
  int iVar12;
  undefined4 *puVar13;
  undefined4 *puVar14;
  int unaff_EDI;
  undefined4 *puVar15;
  undefined4 *puVar16;
  byte bVar17;
  undefined8 uVar18;
  undefined4 **local_64;
  undefined4 **local_60;
  undefined4 **local_5c;
  undefined4 **local_58;
  int local_54;
  undefined4 *local_50;
  int local_38;
  int local_34;
  int iVar19;
  int local_20;
  int iStack_1c;
  int local_18;
  int local_14;
  uint uStack_10;
  
  bVar17 = 0;
  __CHK(0x84);
  setdefaultscreen();
  local_34 = 0;
  local_14 = 0;
  iVar12 = 0;
  if (param_5 != 0) {
    iVar12 = -1;
  }
  iVar19 = unaff_EDX;
  if (0x14 < unaff_EDX) {
    iVar19 = 0x14;
  }
  iStack_1c = textwidth(unaff_EBX);
  for (local_54 = 0; local_54 < unaff_EDX; local_54 = local_54 + 1) {
    if (param_5 != 0) {
      *(undefined *)(param_6 + local_54) = 0;
    }
    unaff_EDI = textwidth(*(undefined4 *)(local_54 * 4 + param_1));
    if (iStack_1c < unaff_EDI) {
      iStack_1c = unaff_EDI;
    }
  }
  iStack_1c = iStack_1c + 9;
  if (iStack_1c < unaff_EDI) {
    iStack_1c = unaff_EDI;
  }
  iVar3 = textwidth(unaff_EBX);
  iVar4 = (byte_d42c3 + 2) * iVar19;
  iVar5 = iVar4 + 4;
  local_38 = (0x270 - iStack_1c) / 2;
  iVar6 = (0x1c0 - iVar5) / 2;
  iVar7 = iStack_1c + 0x10;
  iVar4 = iVar4 + 0x24;
  local_20 = local_38 + 8;
  pppuVar8 = (undefined4 ***)(iVar6 + 0x18);
  if (iVar19 < unaff_EDX) {
    local_34 = -1;
    local_20 = local_38 + -2;
    local_38 = local_38 + -10;
    dword_c71e8 = local_38 + iVar7;
    dword_c71f0 = 10;
    dword_c71ec = iVar6;
    dword_c71f4 = iVar4;
    sub_30bf3(&dword_c71e8,iVar19,unaff_EDX);
    dword_c7208 = 0;
    dword_c71fc = 0;
    save_dialog_background(local_38,iVar6,iStack_1c + 0x1a,iVar4);
    sub_30c3d(&dword_c71e8);
  }
  else {
    save_dialog_background(local_38,iVar6,iVar7,iVar4);
  }
  draw_dialog_frame(local_38,iVar6,iVar7,iVar4,dword_c71cc,dword_c71d0,dword_c71d4);
  set_text_colors(dword_c71d8,dword_c71dc);
  print_text_at((iVar7 - iVar3) / 2 + local_38,iVar6 + 6,unaff_EBX);
  draw_dialog_frame(local_20,pppuVar8,iStack_1c,iVar5,dword_c71dc,dword_c71d4,dword_c71d0);
  sub_3039c(param_1,local_20,pppuVar8,iStack_1c,0,iVar12,iVar19,unaff_ECX,param_5,param_6);
  puVar9 = (undefined4 *)
           allocmem(aPointer_c1710,
                    (((int)pointer_shapes[1] >> 0x10) + 1) *
                    ((*(int *)((int)pointer_shapes + 2) >> 0x10) * 4 + 4) + 0x11,0x20);
  puVar15 = puVar9 + (uint)bVar17 * -2 + 1;
  puVar13 = pointer_shapes + (uint)bVar17 * -2 + 1;
  *puVar9 = *pointer_shapes;
  puVar16 = puVar15 + (uint)bVar17 * -2 + 1;
  puVar14 = puVar13 + (uint)bVar17 * -2 + 1;
  *puVar15 = *puVar13;
  *puVar16 = *puVar14;
  puVar16[(uint)bVar17 * -2 + 1] = puVar14[(uint)bVar17 * -2 + 1];
  *(undefined *)(puVar16 + (uint)bVar17 * -2 + 1 + (uint)bVar17 * -2 + 1) =
       *(undefined *)(puVar14 + (uint)bVar17 * -2 + 1 + (uint)bVar17 * -2 + 1);
  *(short *)(puVar9 + 1) = *(short *)(pointer_shapes + 1) + 1;
  *(short *)((int)puVar9 + 6) = *(short *)((int)pointer_shapes + 6) + 1;
  local_50 = puVar9;
  getmouse(&local_54,&local_58,&local_5c);
  local_60 = local_58;
  local_64 = local_5c;
  grabshape(local_50,local_58,local_5c);
  drawshape_remap(pointer_shapes,local_58,local_5c);
  uVar18 = event_queue_reset();
  bVar2 = false;
  pppuVar11 = pppuVar8;
  do {
    uStack_10 = 0;
    do {
      uVar18 = event_queue_pop((int)uVar18,(int)((ulonglong)uVar18 >> 0x20),pppuVar11);
      iVar4 = (int)uVar18;
      if (iVar4 != 0) {
        pppuVar11 = &local_64;
        uVar18 = (*ui_poll_callback)();
        uStack_10 = (uint)uVar18;
        iVar4 = extraout_ECX;
      }
      uVar10 = (undefined4)((ulonglong)uVar18 >> 0x20);
    } while ((iVar4 != 0) && ((uStack_10 & 2) == 0));
    iVar4 = iVar12;
    if (uStack_10 == 0) {
      if ((local_60 != local_58) || (local_64 != local_5c)) {
        drawshape(puVar9,local_58,local_5c);
        pppuVar11 = (undefined4 ***)local_60;
        grabshape(puVar9,local_60,local_64);
        goto LAB_00030994;
      }
    }
    else {
      drawshape(puVar9,local_58,local_5c);
      if ((uStack_10 & 2) != 0) {
        local_54 = sub_3023e(local_60,local_64,local_20,pppuVar8,iStack_1c,iVar19);
        if (-1 < local_54) {
          iVar4 = local_14 + local_54;
          if ((param_5 != 0) && ((iVar4 != iVar12 || (*(char *)(param_6 + iVar4) == '\0')))) {
            *(byte *)(param_6 + iVar4) = ~*(byte *)(param_6 + iVar4);
          }
          if (((-1 < iVar12) && (local_14 <= iVar12)) && (iVar12 < local_14 + iVar19)) {
            sub_302b9(*(undefined4 *)(iVar12 * 4 + param_1),local_20,pppuVar8,iStack_1c,local_14,
                      iVar12,iVar4,unaff_ECX,param_5,param_6);
          }
          sub_302b9(*(undefined4 *)(iVar4 * 4 + param_1),local_20,pppuVar8,iStack_1c,local_14,iVar4,
                    iVar4,unaff_ECX,param_5,param_6);
          local_18 = iVar12;
        }
        if (iVar4 == local_18) {
          if ((param_5 == 0) || (*(char *)(param_6 + iVar4) != '\0')) {
            bVar1 = true;
          }
          else {
            bVar1 = false;
          }
          if (bVar1) {
            bVar2 = true;
          }
        }
      }
      if (local_34 != 0) {
        iVar12 = sub_30d0e(&dword_c71e8,1,local_60,local_64,uStack_10);
        if ((-1 < iVar12) && (local_14 != dword_c7208)) {
          local_14 = dword_c7208;
          sub_3039c(param_1,local_20,pppuVar8,iStack_1c,dword_c7208,iVar4,iVar19,unaff_ECX,param_5,
                    param_6);
        }
      }
      grabshape(puVar9,local_60,local_64);
      pppuVar11 = (undefined4 ***)local_64;
LAB_00030994:
      drawshape_remap(pointer_shapes,local_60,local_64);
      local_58 = local_60;
      local_5c = local_64;
      uVar10 = extraout_EDX;
    }
    uVar18 = CONCAT44(uVar10,local_64);
    iVar12 = iVar4;
    if (bVar2) {
      drawshape(puVar9,local_58,local_5c);
      freemem(puVar9);
      sub_30f12();
      return iVar4;
    }
  } while( true );
}


// ================================================================================================
// sub_309e4 @ 0x309e4 [__watcall]
// ================================================================================================

void __watcall sub_309e4(undefined4 param_1,int *unaff_EDX,int *unaff_EBX,int unaff_ECX)

{
  int iVar1;
  
  __CHK(0x14);
  iVar1 = textwidth(param_1);
  if (*unaff_EDX < iVar1) {
    *unaff_EDX = iVar1;
  }
  *unaff_EBX = *unaff_EBX + unaff_ECX;
  return;
}


// ================================================================================================
// set_dialog_colors @ 0x30a0c [__watcall]
// ================================================================================================

void __watcall
set_dialog_colors(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX,
                 undefined4 param_5)

{
  __CHK(4);
  dword_c71cc = param_1;
  dword_c71d0 = unaff_EDX;
  dword_c71d4 = unaff_EBX;
  dword_c71d8 = unaff_ECX;
  dword_c71dc = param_5;
  return;
}


// ================================================================================================
// sub_30a39 @ 0x30a39 [__watcall]
// ================================================================================================

int __watcall sub_30a39(int param_1,int unaff_EDX,int unaff_EBX,int unaff_ECX,byte param_5)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int extraout_EDX;
  int extraout_EDX_00;
  int iVar4;
  
  __CHK(0x14);
  iVar4 = -1;
  iVar3 = 0;
  do {
    if (unaff_EDX <= iVar3) {
      return iVar4;
    }
    piVar1 = (int *)(iVar3 * 0x1c + param_1);
    if ((((unaff_EBX < *piVar1) || (*piVar1 + piVar1[2] <= unaff_EBX)) || (unaff_ECX < piVar1[1]))
       || (piVar1[1] + piVar1[3] <= unaff_ECX)) {
      iVar2 = iVar3 * 0x1c + param_1;
      if (*(int *)(iVar2 + 0x10) != 0) goto LAB_00030ac5;
    }
    else {
      if ((piVar1[4] == 0) && ((param_5 & 1) != 0)) {
        piVar1[4] = -1;
        sub_30b16();
        iVar3 = extraout_EDX;
      }
      if ((param_5 & 2) != 0) {
        iVar2 = iVar3 * 0x1c + param_1;
        iVar4 = iVar3;
LAB_00030ac5:
        *(undefined4 *)(iVar2 + 0x10) = 0;
        sub_30b16();
        iVar3 = extraout_EDX_00;
      }
    }
    iVar3 = iVar3 + 1;
  } while( true );
}


// ================================================================================================
// sub_30ae2 @ 0x30ae2 [__watcall]
// ================================================================================================

void __watcall sub_30ae2(int param_1,int unaff_EDX)

{
  int iVar1;
  int extraout_EDX;
  
  __CHK(0xc);
  iVar1 = 0;
  while (iVar1 < unaff_EDX) {
    *(undefined4 *)(iVar1 * 0x1c + param_1 + 0x10) = 0;
    sub_30b16();
    iVar1 = extraout_EDX + 1;
  }
  return;
}


// ================================================================================================
// sub_30b16 @ 0x30b16 [__watcall]
// ================================================================================================

void __watcall sub_30b16(int *param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  
  __CHK(0x28);
  uVar4 = dword_c71d4;
  if (param_1[4] != 0) {
    dword_c71d4 = dword_c71d0;
    dword_c71d0 = uVar4;
  }
  draw_dialog_frame(*param_1,param_1[1],param_1[2],param_1[3],dword_c71cc,dword_c71d0,dword_c71d4);
  uVar4 = dword_c71d4;
  if (param_1[4] != 0) {
    dword_c71d4 = dword_c71d0;
    dword_c71d0 = uVar4;
  }
  iVar1 = param_1[6];
  if (iVar1 != 0) {
    uVar6 = (uint)byte_d42c3;
    iVar2 = param_1[3];
    iVar3 = param_1[1];
    iVar5 = textwidth(iVar1);
    print_text_at((param_1[2] - iVar5) / 2 + *param_1,iVar3 + (int)(iVar2 - uVar6) / 2,iVar1);
  }
  return;
}


// ================================================================================================
// sub_30bf3 @ 0x30bf3 [__watcall]
// ================================================================================================

void __watcall sub_30bf3(int param_1,undefined4 unaff_EDX,undefined4 unaff_EBX)

{
  __CHK(8);
  *(undefined4 *)(param_1 + 0x28) = unaff_EBX;
  *(undefined4 *)(param_1 + 0x24) = unaff_EDX;
  *(undefined4 *)(param_1 + 0x20) = 0;
  *(undefined4 *)(param_1 + 0x10) = 0;
  *(undefined4 *)(param_1 + 0x14) = 0;
  *(int *)(param_1 + 0x18) = *(int *)(param_1 + 8) + -4;
  *(int *)(param_1 + 0x1c) =
       ((*(int *)(param_1 + 0xc) + -4) * *(int *)(param_1 + 0x24)) / *(int *)(param_1 + 0x28);
  return;
}


// ================================================================================================
// sub_30c3d @ 0x30c3d [__watcall]
// ================================================================================================

void __watcall sub_30c3d(int *param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  __CHK(0x28);
  iVar1 = *param_1;
  iVar2 = param_1[1];
  draw_dialog_frame(iVar1,iVar2,param_1[2],param_1[3],dword_c71cc,dword_c71d0,dword_c71d4);
  uVar3 = dword_c71d4;
  if (param_1[0xb] != 0) {
    dword_c71d4 = dword_c71d0;
    dword_c71d0 = uVar3;
  }
  draw_dialog_frame(iVar1 + param_1[4] + 2,iVar2 + param_1[5] + 2,param_1[6],param_1[7],dword_c71cc,
                    dword_c71d0,dword_c71d4);
  if (param_1[0xb] != 0) {
    uVar3 = dword_c71d4;
    dword_c71d4 = dword_c71d0;
    dword_c71d0 = uVar3;
  }
  return;
}


// ================================================================================================
// sub_30d0e @ 0x30d0e [__watcall]
// ================================================================================================

int __watcall sub_30d0e(int param_1,int unaff_EDX,int unaff_EBX,int unaff_ECX,byte param_5)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int local_14;
  
  __CHK(0x20);
  local_14 = -1;
  iVar3 = 0;
  do {
    if (unaff_EDX <= iVar3) {
      return local_14;
    }
    piVar1 = (int *)(iVar3 * 0x30 + param_1);
    iVar4 = unaff_EBX;
    if ((((unaff_EBX < *piVar1) || (iVar4 = *piVar1 + piVar1[2], iVar4 <= unaff_EBX)) ||
        (iVar4 = piVar1[1], unaff_ECX < iVar4)) || (iVar4 = iVar4 + piVar1[3], iVar4 <= unaff_ECX))
    {
      iVar5 = iVar3 * 0x30 + param_1;
      if (*(int *)(iVar5 + 0x2c) != 0) {
        *(undefined4 *)(iVar5 + 0x2c) = 0;
        goto LAB_00030e4a;
      }
    }
    else {
      iVar7 = piVar1[5];
      if (((param_5 & 1) != 0) && (piVar1[0xb] == 0)) {
        piVar1[0xb] = -1;
        iVar7 = -1;
      }
      if ((param_5 & 2) != 0) {
        *(undefined4 *)(param_1 + 0x2c + iVar3 * 0x30) = 0;
        iVar7 = -1;
      }
      iVar4 = param_1 + iVar3 * 0x30;
      iVar5 = (unaff_ECX - *(int *)(iVar4 + 4)) - *(int *)(iVar4 + 0x1c) / 2;
      *(int *)(iVar4 + 0x14) = iVar5;
      if (iVar5 < 0) {
        *(undefined4 *)(iVar4 + 0x14) = 0;
      }
      else {
        iVar5 = (*(int *)(iVar4 + 0xc) - *(int *)(iVar4 + 0x1c)) + -4;
        if (iVar5 < *(int *)(iVar4 + 0x14)) {
          *(int *)(iVar4 + 0x14) = iVar5;
        }
      }
      iVar5 = param_1 + iVar3 * 0x30;
      iVar6 = *(int *)(iVar5 + 0x14) * *(int *)(iVar5 + 0x28);
      iVar2 = *(int *)(iVar5 + 0xc) + -4;
      iVar4 = iVar6 % iVar2;
      *(int *)(iVar5 + 0x20) = iVar6 / iVar2;
      local_14 = iVar3;
      if (iVar7 != *(int *)(iVar5 + 0x14)) {
LAB_00030e4a:
        sub_30c3d(iVar5,iVar4);
      }
    }
    iVar3 = iVar3 + 1;
  } while( true );
}


// ================================================================================================
// save_dialog_background @ 0x30e66 [__watcall]
// ================================================================================================

void __watcall save_dialog_background(int param_1,undefined4 unaff_EDX,int unaff_EBX,int unaff_ECX)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  byte bVar5;
  
  bVar5 = 0;
  __CHK(0x28);
  dword_c71e4 = (undefined4 *)allocmem(&aDBOX,(unaff_ECX + 4) * (unaff_EBX + 8) + 0x11,0x20);
  if (dword_c71e4 != (undefined4 *)0x0) {
    puVar3 = dword_c71e4 + (uint)bVar5 * -2 + 1;
    puVar1 = pointer_shapes + (uint)bVar5 * -2 + 1;
    *dword_c71e4 = *pointer_shapes;
    puVar4 = puVar3 + (uint)bVar5 * -2 + 1;
    puVar2 = puVar1 + (uint)bVar5 * -2 + 1;
    *puVar3 = *puVar1;
    *puVar4 = *puVar2;
    puVar4[(uint)bVar5 * -2 + 1] = puVar2[(uint)bVar5 * -2 + 1];
    *(undefined *)(puVar4 + (uint)bVar5 * -2 + 1 + (uint)bVar5 * -2 + 1) =
         *(undefined *)(puVar2 + (uint)bVar5 * -2 + 1 + (uint)bVar5 * -2 + 1);
    *(short *)(dword_c71e4 + 1) = (short)unaff_EBX + 7;
    *(short *)((int)dword_c71e4 + 6) = (short)unaff_ECX + 4;
    dword_dd678 = ((int)((param_1 + (param_1 >> 0x1f) * -4) - (uint)((param_1 >> 0x1f) << 1 < 0)) >>
                  2) << 2;
    dword_dd688 = unaff_EDX;
    grabshape(dword_c71e4,dword_dd678,unaff_EDX);
  }
  return;
}


// ================================================================================================
// sub_30f12 @ 0x30f12 [__watcall]
// ================================================================================================

void __watcall sub_30f12(void)

{
  __CHK(0x24);
  if (dword_c71e4 != 0) {
    drawshape(dword_c71e4,dword_dd678,dword_dd688);
    freemem(dword_c71e4);
    dword_c71e4 = 0;
  }
  return;
}


// ================================================================================================
// sub_30f5f @ 0x30f5f [__watcall]
// ================================================================================================

void __watcall sub_30f5f(int *param_1,int *unaff_EDX,int *unaff_EBX)

{
  int iVar1;
  
  __CHK(8);
  if ((*(byte *)(param_1 + 5) & 1) == 0) {
    iVar1 = (param_1[2] - *param_1) + 8;
    if (iVar1 <= *unaff_EDX) goto LAB_00030f8c;
  }
  else {
    iVar1 = *param_1 + param_1[2] + 8;
    if (iVar1 <= *unaff_EDX) goto LAB_00030f8c;
  }
  *unaff_EDX = iVar1;
LAB_00030f8c:
  if ((*(byte *)(param_1 + 5) & 4) == 0) {
    iVar1 = (param_1[3] - param_1[1]) + 8;
    if (*unaff_EBX < iVar1) {
      *unaff_EBX = iVar1;
    }
  }
  else {
    iVar1 = param_1[1] + param_1[3] + 8;
    if (*unaff_EBX < iVar1) {
      *unaff_EBX = iVar1;
      return;
    }
  }
  return;
}


// ================================================================================================
// sub_30fb4 @ 0x30fb4 [__watcall]
// ================================================================================================

void __watcall sub_30fb4(int *param_1,int unaff_EDX,int *unaff_EBX,int *unaff_ECX)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  __CHK(0x10);
  iVar1 = 0;
  iVar3 = 0;
  do {
    if (unaff_EDX <= iVar3) {
      return;
    }
    if ((*(byte *)(param_1 + 5) & 1) == 0) {
      iVar2 = param_1[2] - *param_1;
    }
    else {
      iVar2 = *param_1 + param_1[2];
    }
    iVar1 = iVar1 + iVar2 + 8;
    if (*unaff_EBX < iVar1) {
      *unaff_EBX = iVar1;
    }
    if ((*(byte *)(param_1 + 5) & 4) == 0) {
      iVar2 = (param_1[3] - param_1[1]) + 8;
      if (*unaff_ECX < iVar2) goto LAB_00031008;
    }
    else {
      iVar2 = param_1[1] + param_1[3] + 8;
      if (*unaff_ECX < iVar2) {
LAB_00031008:
        *unaff_ECX = iVar2;
      }
    }
    iVar3 = iVar3 + 1;
  } while( true );
}


// ================================================================================================
// message_dialog @ 0x31013 [__watcall]
// ================================================================================================

undefined4 __watcall
message_dialog(int param_1,int unaff_EDX,int unaff_EBX,int unaff_ECX,int param_5,int param_6,
              undefined4 param_7,undefined4 param_8,int param_9)

{
  uint uVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  undefined4 *puVar5;
  int iVar6;
  int local_2c;
  int local_28;
  undefined4 local_24;
  int local_14;
  
  __CHK(0x3c);
  setdefaultscreen();
  sub_30f12();
  local_28 = 0;
  local_2c = 0;
  uVar1 = (uint)byte_d42c3;
  for (iVar6 = 0; iVar6 < unaff_ECX; iVar6 = iVar6 + 1) {
    sub_309e4(*(undefined4 *)(iVar6 * 4 + unaff_EBX),&local_28,&local_2c,uVar1 + 2);
  }
  local_28 = local_28 + 0x10;
  local_2c = local_2c + 0x10;
  sub_30fb4(param_5,param_6,&local_28,&local_2c);
  if (param_1 < 0) {
    param_1 = (0x280 - local_28) / 2;
  }
  if (unaff_EDX < 0) {
    unaff_EDX = (0x1e0 - local_2c) / 2;
  }
  save_dialog_background(param_1,unaff_EDX,local_28,local_2c);
  draw_dialog_frame(param_1,unaff_EDX,local_28,local_2c,dword_c71cc,dword_c71d0,dword_c71d4);
  local_14 = unaff_EDX + 8;
  set_text_colors(dword_c71d8,dword_c71dc);
  for (iVar6 = 0; iVar6 < unaff_ECX; iVar6 = iVar6 + 1) {
    puVar5 = (undefined4 *)(iVar6 * 4 + unaff_EBX);
    iVar2 = textwidth(*puVar5);
    print_text_at((local_28 - iVar2) / 2 + param_1,local_14,*puVar5);
    local_14 = local_14 + uVar1 + 2;
  }
  for (iVar6 = 0; iVar6 < param_6; iVar6 = iVar6 + 1) {
    piVar3 = (int *)(iVar6 * 0x1c + param_5);
    if ((*(byte *)(piVar3 + 5) & 1) == 0) {
      *piVar3 = *piVar3 + ((local_28 + param_1) - piVar3[2]);
    }
    else {
      *piVar3 = *piVar3 + param_1;
    }
    iVar4 = iVar6 * 0x1c + param_5;
    iVar2 = unaff_EDX;
    if ((*(byte *)(iVar4 + 0x14) & 4) == 0) {
      iVar2 = (unaff_EDX + local_2c) - *(int *)(iVar4 + 0xc);
    }
    *(int *)(iVar4 + 4) = *(int *)(iVar4 + 4) + iVar2;
  }
  sub_30ae2(param_5,param_6);
  event_queue_reset();
  if (param_9 != 0) {
    local_24 = sub_31250(param_7,param_8,param_5,param_6);
    sub_30f12();
  }
  for (iVar6 = 0; iVar6 < param_6; iVar6 = iVar6 + 1) {
    piVar3 = (int *)(iVar6 * 0x1c + param_5);
    if ((*(byte *)(piVar3 + 5) & 1) == 0) {
      *piVar3 = *piVar3 - ((local_28 + param_1) - piVar3[2]);
    }
    else {
      *piVar3 = *piVar3 - param_1;
    }
    iVar4 = iVar6 * 0x1c + param_5;
    iVar2 = unaff_EDX;
    if ((*(byte *)(iVar4 + 0x14) & 4) == 0) {
      iVar2 = (unaff_EDX + local_2c) - *(int *)(iVar4 + 0xc);
    }
    *(int *)(iVar4 + 4) = *(int *)(iVar4 + 4) - iVar2;
  }
  return local_24;
}


// ================================================================================================
// sub_31250 @ 0x31250 [__watcall]
// ================================================================================================

int __watcall sub_31250(int *param_1,int *unaff_EDX,undefined4 unaff_EBX,int unaff_ECX)

{
  undefined4 **ppuVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 ***pppuVar4;
  undefined4 ***pppuVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  undefined4 ***pppuVar8;
  byte bVar9;
  ulonglong uVar10;
  undefined4 **local_20;
  undefined4 **local_1c;
  int local_18;
  undefined4 *local_14;
  uint uStack_10;
  
  bVar9 = 0;
  __CHK(0x40);
  puVar2 = (undefined4 *)
           allocmem(aPointer_c1710,
                    (((int)pointer_shapes[1] >> 0x10) + 1) *
                    ((*(int *)((int)pointer_shapes + 2) >> 0x10) * 4 + 4) + 0x11,0x20);
  puVar6 = puVar2 + (uint)bVar9 * -2 + 1;
  pppuVar4 = pointer_shapes + (uint)bVar9 * -2 + 1;
  *puVar2 = *pointer_shapes;
  puVar7 = puVar6 + (uint)bVar9 * -2 + 1;
  pppuVar5 = pppuVar4 + (uint)bVar9 * -2 + 1;
  *puVar6 = *pppuVar4;
  *puVar7 = *pppuVar5;
  puVar7[(uint)bVar9 * -2 + 1] = pppuVar5[(uint)bVar9 * -2 + 1];
  *(undefined *)(puVar7 + (uint)bVar9 * -2 + 1 + (uint)bVar9 * -2 + 1) =
       *(undefined *)(pppuVar5 + (uint)bVar9 * -2 + 1 + (uint)bVar9 * -2 + 1);
  *(short *)(puVar2 + 1) = *(short *)(pointer_shapes + 1) + 1;
  *(short *)((int)puVar2 + 6) = *(short *)((int)pointer_shapes + 6) + 1;
  local_18 = 0;
  pppuVar5 = (undefined4 ***)*param_1;
  pppuVar8 = (undefined4 ***)*unaff_EDX;
  local_20 = pppuVar8;
  local_1c = pppuVar5;
  local_14 = puVar2;
  setmousepos(pppuVar5,pppuVar8);
  grabshape(puVar2,pppuVar5,pppuVar8);
  pppuVar4 = pointer_shapes;
  drawshape_remap(pointer_shapes,pppuVar5,pppuVar8);
  do {
    do {
      iVar3 = sub_b2cbe(1);
    } while (iVar3 != 0);
    iVar3 = sub_b2cbe(0x1c);
  } while (iVar3 != 0);
  uVar10 = event_queue_reset();
  iVar3 = 0;
  do {
    uVar10 = event_queue_pop((int)uVar10,(int)(uVar10 >> 0x20),pppuVar4);
    if ((int)uVar10 != 0) {
      pppuVar4 = &local_20;
      uVar10 = (*ui_poll_callback)();
      uStack_10 = (uint)uVar10;
      if ((uVar10 & 0x2f) != 0) {
        drawshape(local_14,pppuVar5,pppuVar8);
        ppuVar1 = local_1c;
        if (unaff_ECX < 1) {
          if ((uStack_10 & 4) == 0) {
            if ((uStack_10 & 0x2a) == 0) goto LAB_000313b7;
          }
          else {
            local_18 = 4;
          }
LAB_000313b2:
          iVar3 = -1;
        }
        else if ((uStack_10 & 4) == 0) {
          local_18 = sub_30a39(unaff_EBX,unaff_ECX,local_1c,local_20,uStack_10);
          pppuVar4 = (undefined4 ***)ppuVar1;
          if (-1 < local_18) goto LAB_000313b2;
        }
        else {
          local_18 = -1;
          iVar3 = -1;
        }
LAB_000313b7:
        grabshape(local_14,pppuVar5,pppuVar8);
        uVar10 = drawshape_remap(pointer_shapes,pppuVar5,pppuVar8);
      }
      puVar2 = local_14;
      if ((pppuVar5 != (undefined4 ***)local_1c) || (pppuVar8 != (undefined4 ***)local_20)) {
        drawshape(local_14,pppuVar5,pppuVar8);
        grabshape(puVar2,local_1c,local_20);
        pppuVar4 = (undefined4 ***)local_20;
        uVar10 = drawshape_remap(pointer_shapes,local_1c,local_20);
        pppuVar5 = (undefined4 ***)local_1c;
        pppuVar8 = (undefined4 ***)local_20;
      }
    }
    if (iVar3 != 0) {
      do {
        do {
          iVar3 = sub_b2cbe(1);
        } while (iVar3 != 0);
        iVar3 = sub_b2cbe(0x1c);
      } while (iVar3 != 0);
      event_queue_reset();
      puVar2 = local_14;
      drawshape(local_14,pppuVar5,pppuVar8);
      event_queue_reset();
      setmousepos(local_1c,local_20);
      *param_1 = (int)local_1c;
      *unaff_EDX = (int)local_20;
      freemem(puVar2);
      return local_18;
    }
  } while( true );
}


// ================================================================================================
// sub_3149d @ 0x3149d [__watcall]
// ================================================================================================

undefined4 __watcall sub_3149d(void)

{
  __CHK(4);
  dword_dd7a4 = 0xffffffff;
  return 0;
}


// ================================================================================================
// sub_314b4 @ 0x314b4 [__watcall]
// ================================================================================================

void __watcall sub_314b4(uint param_1)

{
  int iVar1;
  size_t sVar2;
  int iVar3;
  
  __CHK(0x34);
  iVar1 = textwidth(&unk_c1720);
  if (dword_dd69c != 0) {
    sVar2 = strlen(dword_dd698);
    if ((int)sVar2 < (int)dword_dd690) {
      dword_dd690 = strlen(dword_dd698);
    }
    if (dword_dd698[dword_dd690] == '\0') {
      iVar3 = textwidth(&asc_c1722);
    }
    else {
      iVar3 = iVar1;
      if ((param_1 & 2) == 0) {
        iVar3 = textwidthn(dword_dd698 + dword_dd690,1);
      }
    }
    if ((param_1 & 2) == 0) {
      iVar1 = textwidthn(dword_dd698,dword_dd690);
    }
    else {
      iVar1 = dword_dd690 * iVar1;
    }
    sub_91044(iVar1 + dword_dd6a4,(((uint)byte_d42c5 + dword_dd6a0) - dword_dd68c) + -2,iVar3,
              dword_dd68c,dword_d42a8);
  }
  return;
}


// ================================================================================================
// sub_31599 @ 0x31599 [__watcall]
// ================================================================================================

void __watcall sub_31599(uint param_1)

{
  int iVar1;
  size_t sVar2;
  int iVar3;
  
  __CHK(0x34);
  iVar1 = textwidth(&unk_c1720);
  if (dword_dd694 != 0) {
    if ((param_1 & 2) == 0) {
      while ((iVar3 = textwidth(dword_dd698), dword_dd694 < iVar3 &&
             (sVar2 = strlen(dword_dd698), sVar2 != 0))) {
        sVar2 = strlen(dword_dd698);
        dword_dd698[sVar2 - 1] = '\0';
      }
    }
    else {
      while ((sVar2 = strlen(dword_dd698),
             sVar2 * iVar1 - dword_dd694 != 0 && dword_dd694 <= (int)(sVar2 * iVar1) &&
             (sVar2 = strlen(dword_dd698), sVar2 != 0))) {
        sVar2 = strlen(dword_dd698);
        dword_dd698[sVar2 - 1] = '\0';
      }
    }
  }
  sVar2 = strlen(dword_dd698);
  if ((int)sVar2 < (int)dword_dd690) {
    dword_dd690 = sVar2;
  }
  if ((param_1 & 2) == 0) {
    printstr2_at(dword_dd698,dword_dd6a4,dword_dd6a0);
  }
  else {
    for (iVar3 = 0; iVar3 < (int)sVar2; iVar3 = iVar3 + 1) {
      printstr2_at(&unk_c1720,iVar1 * iVar3 + dword_dd6a4,dword_dd6a0);
    }
  }
  if (dword_dd694 != 0) {
    if ((param_1 & 2) == 0) {
      iVar1 = textwidth(dword_dd698);
    }
    else {
      iVar1 = sVar2 * iVar1;
    }
    if (0 < dword_dd694 - iVar1) {
      sub_90ec0(iVar1 + dword_dd6a4,dword_dd6a0,dword_dd694 - iVar1,byte_d42c5 - 2,dword_d42ac);
    }
  }
  return;
}


