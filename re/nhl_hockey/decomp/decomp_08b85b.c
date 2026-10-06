// Decompiled by Ghidra from hockey.elf (via ledisasm ELF export)
// This is machine generated pseudo-C meant as a reference for porting, it does not compile as is.
#include "prototypes.h"

// ================================================================================================
// sub_8b85b @ 0x8b85b [__watcall]
// ================================================================================================

void __watcall sub_8b85b(void)

{
  __CHK(0x10);
  if (dword_c5413 == dword_c5417) {
    if (dword_c5413 == (undefined *)0x0) {
      funcptr_cef43 = sub_1a8aa;
      funcptr_cef63 = dword_c5413;
      off_cede7 = &unk_cee4f;
      off_cee07 = (undefined *)0x0;
      return;
    }
    funcptr_cef43 = (undefined *)0x0;
    off_cede7 = (undefined *)0x0;
  }
  else {
    if ((dword_c5403 == -1) || (dword_c5407 == -1)) {
      funcptr_cef43 = (undefined *)0x0;
      off_cede7 = (undefined *)0x0;
    }
    else {
      funcptr_cef43 = sub_1a8aa;
      off_cede7 = &unk_cee4f;
    }
    if ((dword_c5403 == -2) || (dword_c5407 == -2)) {
      funcptr_cef63 = (undefined *)0x0;
      off_cee07 = (undefined *)0x0;
      return;
    }
  }
  funcptr_cef63 = sub_1a922;
  off_cee07 = &unk_ceeaf;
  return;
}


// ================================================================================================
// sub_8b92f @ 0x8b92f [__watcall]
// ================================================================================================

void __watcall sub_8b92f(void)

{
  __CHK(4);
  if (dword_c53fb == 0) {
    load_game_set(&settings_exhibition);
    return;
  }
  if (1 < dword_c53fb) {
    if (dword_c53fb != 2) {
      return;
    }
    load_game_set(&settings_league);
    return;
  }
  load_game_set(&settings_playoff);
  return;
}


// ================================================================================================
// sub_8b96d @ 0x8b96d [__watcall]
// ================================================================================================

void __watcall sub_8b96d(char param_1,int unaff_EDX)

{
  char *pcVar1;
  int iVar2;
  int iVar3;
  
  __CHK(0xc);
  iVar3 = 0;
  do {
    pcVar1 = (char *)(iVar3 * 3 + unaff_EDX);
    if (param_1 == *pcVar1) {
      *pcVar1 = 'd';
    }
    else if (param_1 == pcVar1[1]) {
      pcVar1[1] = 'd';
    }
    else if (param_1 == pcVar1[2]) {
      pcVar1[2] = 'd';
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 < 4);
  iVar3 = 0;
  do {
    iVar2 = iVar3 * 2 + unaff_EDX;
    if (param_1 == *(char *)(iVar2 + 0xc)) {
      *(undefined *)(iVar2 + 0xc) = 100;
    }
    else if (param_1 == *(char *)(iVar2 + 0xd)) {
      *(undefined *)(iVar2 + 0xd) = 100;
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 < 3);
  if (param_1 == *(char *)(unaff_EDX + 0x12)) {
    *(undefined *)(unaff_EDX + 0x12) = 100;
  }
  else if (param_1 == *(char *)(unaff_EDX + 0x13)) {
    *(undefined *)(unaff_EDX + 0x13) = 100;
  }
  else if (param_1 == *(char *)(unaff_EDX + 0x14)) {
    *(undefined *)(unaff_EDX + 0x14) = 100;
  }
  else if (param_1 == *(char *)(unaff_EDX + 0x15)) {
    *(undefined *)(unaff_EDX + 0x15) = 100;
  }
  else if (param_1 == *(char *)(unaff_EDX + 0x16)) {
    *(undefined *)(unaff_EDX + 0x16) = 100;
  }
  if (param_1 == *(char *)(unaff_EDX + 0x17)) {
    *(undefined *)(unaff_EDX + 0x17) = 100;
  }
  else if (param_1 == *(char *)(unaff_EDX + 0x18)) {
    *(undefined *)(unaff_EDX + 0x18) = 100;
  }
  else if (param_1 == *(char *)(unaff_EDX + 0x19)) {
    *(undefined *)(unaff_EDX + 0x19) = 100;
  }
  else if (param_1 == *(char *)(unaff_EDX + 0x1a)) {
    *(undefined *)(unaff_EDX + 0x1a) = 100;
  }
  else if (param_1 == *(char *)(unaff_EDX + 0x1b)) {
    *(undefined *)(unaff_EDX + 0x1b) = 100;
  }
  if (param_1 == *(char *)(unaff_EDX + 0x1c)) {
    *(undefined *)(unaff_EDX + 0x1c) = 100;
  }
  else if (param_1 == *(char *)(unaff_EDX + 0x1d)) {
    *(undefined *)(unaff_EDX + 0x1d) = 100;
  }
  else if (param_1 == *(char *)(unaff_EDX + 0x1e)) {
    *(undefined *)(unaff_EDX + 0x1e) = 100;
  }
  else if (param_1 == *(char *)(unaff_EDX + 0x1f)) {
    *(undefined *)(unaff_EDX + 0x1f) = 100;
  }
  if (param_1 == *(char *)(unaff_EDX + 0x20)) {
    *(undefined *)(unaff_EDX + 0x20) = 100;
  }
  else if (param_1 == *(char *)(unaff_EDX + 0x21)) {
    *(undefined *)(unaff_EDX + 0x21) = 100;
  }
  else if (param_1 == *(char *)(unaff_EDX + 0x22)) {
    *(undefined *)(unaff_EDX + 0x22) = 100;
  }
  else if (param_1 == *(char *)(unaff_EDX + 0x23)) {
    *(undefined *)(unaff_EDX + 0x23) = 100;
  }
  if (param_1 == *(char *)(unaff_EDX + 0x24)) {
    *(undefined *)(unaff_EDX + 0x24) = 100;
  }
  if (param_1 == *(char *)(unaff_EDX + 0x25)) {
    *(undefined *)(unaff_EDX + 0x25) = 100;
  }
  if (param_1 == *(char *)(unaff_EDX + 0x26)) {
    *(undefined *)(unaff_EDX + 0x26) = 100;
  }
  if (param_1 == *(char *)(unaff_EDX + 0x27)) {
    *(undefined *)(unaff_EDX + 0x27) = 100;
  }
  return;
}


// ================================================================================================
// load_nhl_cfg @ 0x8baaf [__watcall]
// ================================================================================================

void __watcall load_nhl_cfg(void)

{
  FILE *__stream;
  FILE *__stream_00;
  int iVar1;
  int iVar2;
  int iVar3;
  undefined auStack_22a0 [8784];
  char acStack_50 [60];
  
  __CHK(0x22b0);
  __stream = fopen(aNhlCfg,(char *)&aR_c3b0c);
  if (__stream == (FILE *)0x0) {
    fatalerror(aCannotOpenNhlCfg_c3b16);
  }
  sub_9814a(acStack_50,0x10,__stream);
  sub_9814a(acStack_50,0x10);
  aA_d2c68._0_1_ = acStack_50[0];
  acStack_50[1] = 0;
  strcat(acStack_50,aALLFILESTXT);
  __stream_00 = fopen(acStack_50,(char *)&aR_c3b0c);
  if (__stream_00 == (FILE *)0x0) {
    __stream_00 = fopen(aALLFILESTXT_c3b38,(char *)&aR_c3b0c);
    if (__stream_00 == (FILE *)0x0) {
      fclose(__stream);
      fatalerror(aCouldNotOpenALLFILESTXTF);
    }
  }
  iVar3 = 0;
  iVar2 = 0;
  while ((iVar3 < 0x225 && (iVar2 != -1))) {
    (&file_on_disk)[iVar3] = 1;
    iVar2 = fscanf(__stream_00,&unk_c3b67,auStack_22a0 + iVar3 * 0x10);
    iVar3 = iVar3 + 1;
  }
  fclose(__stream_00);
  iVar2 = 0;
  while (iVar2 != -1) {
    iVar2 = fscanf(__stream,&unk_c3b67,acStack_50);
    iVar3 = 0;
    while (iVar3 < 0x225) {
      iVar1 = stricmp(acStack_50,auStack_22a0 + iVar3 * 0x10);
      if (iVar1 == 0) {
        (&file_on_disk)[iVar3] = 0;
        iVar3 = 0x226;
      }
      else {
        iVar3 = iVar3 + 1;
      }
    }
  }
  fclose(__stream);
  return;
}


// ================================================================================================
// coach_clip_player @ 0x8bc15 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 __watcall coach_clip_player(void)

{
  bool bVar1;
  undefined5 *puVar2;
  int iVar3;
  int iVar4;
  int extraout_EDX;
  undefined *puVar5;
  undefined5 **ppuVar6;
  undefined5 *puStack_34c;
  undefined5 auStack_348 [96];
  undefined auStack_48 [32];
  char acStack_28 [16];
  
  __CHK(0x358);
  puStack_34c = (undefined5 *)0x8bc30;
  wait_sprite_fade();
  puStack_34c = (undefined5 *)0x8bc35;
  ui_init();
  puVar5 = install_path;
  if (byte_ed9b2 != '\x01') {
    puVar5 = (undefined *)0x0;
  }
  puStack_34c = (undefined5 *)0x8bc5b;
  make_path(auStack_48,puVar5,aCoachcut,0);
  puStack_34c = (undefined5 *)0x0;
  puVar2 = (undefined5 *)loadshapes(auStack_48);
  puStack_34c = auStack_348;
  getpalette(0,0x100);
  puStack_34c = (undefined5 *)0x8bc92;
  fade_palette_to(1,auStack_348,0x10);
  puStack_34c = (undefined5 *)0x8bc97;
  setdefaultscreen();
  puStack_34c = &aScrn_c3b75;
  puStack_34c = (undefined5 *)locateshape(puVar2);
  drawshape_home();
  puStack_34c = &aPal_c3b7a;
  iVar3 = locateshape(puVar2);
  puStack_34c = (undefined5 *)0x8bccb;
  memcpy(auStack_348,(void *)(iVar3 + 0x10),0x300);
  puStack_34c = puVar2;
  freemem();
  if ((sound_enabled != '\0') && (dword_c721d == (undefined5 *)0x0)) {
    puVar5 = install_path;
    if (byte_ed9eb != '\x01') {
      puVar5 = (undefined *)0x0;
    }
    puStack_34c = (undefined5 *)0x8bd0f;
    make_path(auStack_48,puVar5,aCoach,&aIff_c3b7f);
    puStack_34c = (undefined5 *)0x8bd1b;
    dword_c721d = (undefined5 *)loadsound(auStack_48);
  }
  if ((sound_enabled == '\0') || ((option_flags._1_1_ & 1) == 0)) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
    puStack_34c = (undefined5 *)0x8bd3c;
    sub_8473a();
  }
  puStack_34c = (undefined5 *)0x8bd4e;
  fade_palette_to(0,auStack_348,0x10);
  puStack_34c = (undefined5 *)0x8bd58;
  iVar3 = sub_33e6a(10);
  if (iVar3 == 0) {
    puStack_34c = (undefined5 *)0x8bd67;
    iVar3 = rand();
    puStack_34c = (undefined5 *)(iVar3 % 0x32 + 1);
    sprintf(acStack_28,aClip04d);
    puVar5 = install_path;
    if ((&unk_ed9b3)[extraout_EDX] != '\x01') {
      puVar5 = (undefined *)0x0;
    }
    puStack_34c = (undefined5 *)0x8bdb7;
    make_path(auStack_48,puVar5,acStack_28,&aCmv_c3b93);
    if ((sound_enabled != '\0') && ((option_flags._1_1_ & 1) != 0)) {
      do {
        puStack_34c = (undefined5 *)0x8bdce;
        iVar3 = sub_836e4();
      } while (iVar3 != 0);
    }
    puStack_34c = (undefined5 *)0x8bde8;
    iVar3 = cmv_play(auStack_48,0x161,0x54);
    puStack_34c = auStack_348;
    getpalette(0,0x100);
    puStack_34c = (undefined5 *)0x8be0d;
    fade_palette_to(1,auStack_348);
    ppuVar6 = (undefined5 **)auStack_348;
    if ((sound_enabled != '\0') &&
       (ppuVar6 = (undefined5 **)auStack_348, (option_flags._1_1_ & 1) != 0)) {
      ppuVar6 = &puStack_34c;
      puStack_34c = (undefined5 *)0x8be24;
      sub_8373e();
      do {
        *(undefined4 *)((int)ppuVar6 + -4) = 0x8be29;
        iVar4 = sub_836e4();
      } while (iVar4 != 0);
    }
    puVar2 = (undefined5 *)ppuVar6;
    if ((sound_enabled != '\0') && (dword_c721d != (undefined5 *)0x0)) {
      do {
        *(undefined4 *)((int)ppuVar6 + -4) = 0x8be59;
        iVar4 = sound_channel_status(ram0x000d242c >> 0x18,3);
      } while (iVar4 == 0);
      *(undefined5 **)((int)ppuVar6 + -4) = dword_c721d;
      *(undefined4 *)((int)ppuVar6 + -8) = 0x8be69;
      releasememblock();
      dword_c721d = (undefined5 *)0x0;
    }
  }
  else {
    puStack_34c = auStack_348;
    getpalette(0,0x100);
    puStack_34c = (undefined5 *)0x8be99;
    fade_palette_to(1,auStack_348,0x10);
    puVar2 = auStack_348;
    if ((sound_enabled != '\0') && (puVar2 = auStack_348, dword_c721d != (undefined5 *)0x0)) {
      puStack_34c = dword_c721d;
      releasememblock();
      dword_c721d = (undefined5 *)0x0;
      puVar2 = auStack_348;
    }
  }
  if (bVar1) {
    *(undefined4 *)((int)puVar2 + -4) = 0x8bec7;
    sub_8474e();
  }
  *(undefined4 *)((int)puVar2 + -4) = 0x8becc;
  ui_shutdown();
  return CONCAT44(*(undefined4 *)((int)puVar2 + 0x33c),iVar3);
}


// ================================================================================================
// cmv_play @ 0x8bedb [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __watcall cmv_play(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX)

{
  bool bVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  int iVar10;
  int iVar11;
  undefined8 uVar12;
  int local_34;
  int local_30;
  int local_1c;
  int local_18;
  int iStack_14;
  
  __CHK(0x58);
  event_queue_reset();
  setdefaultscreen();
  uVar2 = sub_1b0f3(300000,0x2000,0x20);
  sub_1b1c2(uVar2,param_1);
  uVar3 = sub_1ac25();
  settimeout(0x96);
  while (iVar4 = sub_b39a7(), iVar4 == 0) {
    iff_parse();
  }
  local_34 = 10;
  iVar11 = 0;
  local_30 = 0;
  getticks();
  iVar4 = 0;
  bVar1 = false;
  iStack_14 = 0;
  local_1c = getticks();
  local_18 = 0;
  uVar12 = iff_parse();
  do {
    iVar5 = sub_1b8ac((int)uVar12,(int)((ulonglong)uVar12 >> 0x20));
    if (iVar5 == -1) {
      uVar12 = 0xffffffffffffffff;
      iVar4 = -1;
    }
    else if (iVar5 == 0) {
      uVar12 = iff_parse();
    }
    else {
      uVar6 = sub_16072();
      if (uVar6 < 0x4d564966) {
        if (uVar6 == 0x4d564965) {
          local_18 = local_18 + 1;
        }
        else {
LAB_0008c0c8:
          bVar1 = true;
        }
      }
      else if (uVar6 < 0x4d564967) {
        if (1 < iVar11) {
          iStack_14 = iStack_14 + local_34;
          uVar7 = sub_1b002(uVar3);
          iVar10 = getticks();
          if (iVar10 - local_1c < iStack_14) {
            drawshape2(uVar7,unaff_EDX,unaff_EBX);
          }
          if ((local_18 == 0) && (iVar11 == local_30)) {
            if ((sound_enabled != '\0') && (dword_c721d != 0)) {
              playsample(dword_c721d,dword_d2431,3,0x7f);
            }
            local_1c = getticks();
          }
          iVar11 = iVar11 + -1;
        }
      }
      else {
        if (uVar6 != 0x4d564968) goto LAB_0008c0c8;
        cmv_load_palette(uVar3);
        iVar11 = sub_1b092(uVar3);
        fillrect(unaff_EDX,unaff_EBX,0xe4,0xb0,0);
        uVar7 = sub_1b0e5(uVar3);
        uVar8 = sub_1b0d7(uVar3);
        uVar9 = sub_1b0c9(uVar3);
        setpalette(uVar9,uVar8,uVar7);
        iVar10 = sub_1b0bb(uVar3);
        local_34 = (int)(100 / (longlong)iVar10);
        local_30 = iVar11;
      }
      sub_1b92e(uVar2,iVar5);
      uVar12 = iff_parse();
      if (uVar6 == 0x4d564966) {
        uVar12 = getticks();
        iVar5 = (int)uVar12 - local_1c;
        uVar12 = CONCAT44((int)((ulonglong)uVar12 >> 0x20),iVar5);
        if (iVar5 < iStack_14) {
          settimeout(iStack_14 - iVar5);
          while ((uVar12 = sub_b39a7(), (int)uVar12 == 0 && (iVar4 == 0))) {
            iVar4 = sub_1600c();
          }
        }
      }
    }
    if (iVar4 == 0) {
      uVar12 = sub_1600c();
      iVar4 = (int)uVar12;
    }
    if (((iVar4 != 0) || (bVar1)) || (local_18 == 3)) {
      sub_1acf1(uVar3);
      sub_1b18b(uVar2);
      if ((sound_enabled != '\0') && (dword_c721d != 0)) {
        while ((iVar4 == 0 && (iVar11 = sound_channel_status(ram0x000d242c >> 0x18,3), iVar11 == 0))
              ) {
          iVar4 = sub_33e6a(10);
        }
        sound_fade(dword_d2431,3,0x50);
      }
      return iVar4;
    }
  } while( true );
}


// ================================================================================================
// sub_8c1b7 @ 0x8c1b7 [__watcall]
// ================================================================================================

void __watcall sub_8c1b7(void)

{
  __CHK(4);
  return;
}


// ================================================================================================
// select_game_surface @ 0x8c1c2 [__watcall]
// ================================================================================================

void __watcall
select_game_surface(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,
                   undefined4 unaff_ECX)

{
  __CHK(0x14);
  setscreen(hud_window,unaff_EDX,unaff_ECX,unaff_EBX);
  return;
}


// ================================================================================================
// sub_8c1e2 @ 0x8c1e2 [__watcall]
// ================================================================================================

void __watcall
sub_8c1e2(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  __CHK(0x14);
  setscreen(dword_c73d4,unaff_EDX,unaff_ECX,unaff_EBX);
  return;
}


// ================================================================================================
// sub_8c1f7 @ 0x8c1f7 [__watcall]
// ================================================================================================

void __watcall sub_8c1f7(void)

{
  __CHK(4);
  return;
}


// ================================================================================================
// sub_8c202 @ 0x8c202 [__watcall]
// ================================================================================================

void __watcall sub_8c202(void)

{
  __CHK(4);
  return;
}


// ================================================================================================
// sub_8c20d @ 0x8c20d [__watcall]
// ================================================================================================

void __watcall sub_8c20d(void)

{
  __CHK(4);
  return;
}


// ================================================================================================
// sub_8c218 @ 0x8c218 [__cdecl]
// ================================================================================================

void sub_8c218(void)

{
  __CHK(4);
  return;
}


// ================================================================================================
// sub_8c223 @ 0x8c223 [__watcall]
// ================================================================================================

void __watcall sub_8c223(void)

{
  __CHK(4);
  return;
}


// ================================================================================================
// randomrange @ 0x8c230 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined2 __watcall randomrange(void)

{
  ushort *puVar1;
  ushort uVar2;
  short sVar3;
  undefined2 in_SS;
  undefined auStack_12 [2];
  
  uVar2 = (ushort)((uint)dword_c9100 * 0xe62d);
  sVar3 = uVar2 + 1;
  _word_c9102 = (short)((uint)dword_c9100 * 0xe62d >> 0x10) +
                _word_c9102 * -0x19d3 + dword_c9100 * -0x44c0 + (ushort)(0xfffe < uVar2);
  dword_c9100 = sVar3;
  puVar1 = (ushort *)segment(in_SS,(short)auStack_12);
  return (short)((uint)CONCAT11((char)_word_c9102,(char)((ushort)sVar3 >> 8)) * (uint)*puVar1 >>
                0x10);
}


// ================================================================================================
// sub_8c290 @ 0x8c290 [__watcall]
// ================================================================================================

undefined2 __watcall sub_8c290(void)

{
  short *psVar1;
  undefined2 *puVar2;
  byte bVar3;
  uint unaff_ECX;
  int iVar4;
  ushort uVar5;
  short sVar6;
  short sVar7;
  undefined4 unaff_EBP;
  int iVar8;
  undefined4 unaff_ESI;
  undefined *puVar9;
  undefined4 unaff_EDI;
  undefined *puVar10;
  undefined2 in_SS;
  undefined auStack_e [12];
  undefined auStack_2 [2];
  
  iVar8 = CONCAT22((short)((uint)unaff_EBP >> 0x10),(short)auStack_2);
  out(0x3ce,5);
  bVar3 = in(0x3cf);
  out(0x3cf,(bVar3 & 0xfc) + 1);
  out(0x3c4,2);
  bVar3 = in(0x3c5);
  out(0x3c5,(bVar3 & 0xf0) + 0xf);
  puVar10 = (undefined *)
            CONCAT22((short)((uint)unaff_EDI >> 0x10),
                     *(short *)(iVar8 + 6) + dword_c7290 * *(short *)(iVar8 + 10) +
                     *(short *)(iVar8 + 8));
  uVar5 = *(short *)(iVar8 + 10) + word_dd70c * 8;
  if (0xaf < uVar5) {
    uVar5 = uVar5 - 0xb0;
  }
  puVar9 = (undefined *)
           CONCAT22((short)((uint)unaff_ESI >> 0x10),
                    uVar5 * 0x60 + -0x7960 + *(short *)(iVar8 + 8) + word_dd6b2 * 2);
  sVar7 = *(short *)(iVar8 + 0xc);
  sVar6 = dword_c7290 - sVar7;
  unaff_ECX = unaff_ECX & 0xffff0000;
  do {
    for (iVar4 = CONCAT22((short)(unaff_ECX >> 0x10),sVar7); iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar10 = *puVar9;
      puVar9 = puVar9 + 1;
      puVar10 = puVar10 + 1;
    }
    puVar10 = (undefined *)CONCAT22((short)((uint)puVar10 >> 0x10),(short)puVar10 + sVar6);
    uVar5 = (short)puVar9 + (0x60 - sVar7);
    if (0xc89f < uVar5) {
      uVar5 = uVar5 + 0xbe00;
    }
    puVar9 = (undefined *)CONCAT22((short)((uint)puVar9 >> 0x10),uVar5);
    psVar1 = (short *)(iVar8 + 0xe);
    *psVar1 = *psVar1 + -1;
    unaff_ECX = 0;
  } while (*psVar1 != 0);
  sVar7 = (short)auStack_e;
  puVar2 = (undefined2 *)segment(in_SS,sVar7);
  out(0x3c5,(char)*puVar2);
  puVar2 = (undefined2 *)segment(in_SS,sVar7 + 2);
  out(0x3cf,(char)*puVar2);
  segment(in_SS,sVar7 + 4);
  segment(in_SS,sVar7 + 6);
  segment(in_SS,sVar7 + 0xc);
  return *puVar2;
}


// ================================================================================================
// sub_8c36f @ 0x8c36f [__watcall]
// ================================================================================================

undefined2 __watcall sub_8c36f(void)

{
  undefined2 uVar1;
  undefined2 *puVar2;
  byte bVar3;
  short sVar4;
  undefined4 unaff_ECX;
  int iVar5;
  short sVar6;
  undefined4 unaff_EBP;
  undefined4 unaff_ESI;
  undefined *puVar7;
  undefined4 unaff_EDI;
  undefined *puVar8;
  undefined2 in_SS;
  undefined auStack_e [12];
  undefined auStack_2 [2];
  
  iVar5 = CONCAT22((short)((uint)unaff_EBP >> 0x10),(short)auStack_2);
  out(0x3ce,5);
  bVar3 = in(0x3cf);
  out(0x3cf,(bVar3 & 0xfc) + 1);
  out(0x3c4,2);
  bVar3 = in(0x3c5);
  out(0x3c5,(bVar3 & 0xf0) + 0xf);
  sVar6 = dword_c7290 - *(short *)(iVar5 + 10);
  puVar7 = (undefined *)CONCAT22((short)((uint)unaff_ESI >> 0x10),*(undefined2 *)(iVar5 + 6));
  puVar8 = (undefined *)CONCAT22((short)((uint)unaff_EDI >> 0x10),*(undefined2 *)(iVar5 + 8));
  sVar4 = *(short *)(iVar5 + 0xc);
  uVar1 = *(undefined2 *)(iVar5 + 10);
  do {
    for (iVar5 = CONCAT22((short)((uint)unaff_ECX >> 0x10),uVar1); iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar8 = *puVar7;
      puVar7 = puVar7 + 1;
      puVar8 = puVar8 + 1;
    }
    puVar8 = (undefined *)CONCAT22((short)((uint)puVar8 >> 0x10),(short)puVar8 + sVar6);
    sVar4 = sVar4 + -1;
    unaff_ECX = 0;
  } while (sVar4 != 0);
  sVar4 = (short)auStack_e;
  puVar2 = (undefined2 *)segment(in_SS,sVar4);
  out(0x3c5,(char)*puVar2);
  puVar2 = (undefined2 *)segment(in_SS,sVar4 + 2);
  out(0x3cf,(char)*puVar2);
  segment(in_SS,sVar4 + 4);
  segment(in_SS,sVar4 + 6);
  segment(in_SS,sVar4 + 0xc);
  return *puVar2;
}


// ================================================================================================
// sub_8c3e9 @ 0x8c3e9 [__watcall]
// ================================================================================================

undefined2 __watcall sub_8c3e9(void)

{
  undefined2 uVar1;
  undefined2 *puVar2;
  byte bVar3;
  short sVar4;
  undefined4 unaff_ECX;
  int iVar5;
  short sVar6;
  undefined4 unaff_EBP;
  undefined4 unaff_ESI;
  undefined *puVar7;
  undefined4 unaff_EDI;
  undefined *puVar8;
  undefined2 in_SS;
  undefined auStack_e [12];
  undefined auStack_2 [2];
  
  iVar5 = CONCAT22((short)((uint)unaff_EBP >> 0x10),(short)auStack_2);
  out(0x3ce,5);
  bVar3 = in(0x3cf);
  out(0x3cf,(bVar3 & 0xfc) + 1);
  out(0x3c4,2);
  bVar3 = in(0x3c5);
  out(0x3c5,(bVar3 & 0xf0) + 0xf);
  sVar6 = dword_c7290 - *(short *)(iVar5 + 10);
  puVar7 = (undefined *)CONCAT22((short)((uint)unaff_ESI >> 0x10),*(undefined2 *)(iVar5 + 6));
  puVar8 = (undefined *)CONCAT22((short)((uint)unaff_EDI >> 0x10),*(undefined2 *)(iVar5 + 8));
  sVar4 = *(short *)(iVar5 + 0xc);
  uVar1 = *(undefined2 *)(iVar5 + 10);
  do {
    for (iVar5 = CONCAT22((short)((uint)unaff_ECX >> 0x10),uVar1); iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar8 = *puVar7;
      puVar7 = puVar7 + 1;
      puVar8 = puVar8 + 1;
    }
    puVar7 = (undefined *)CONCAT22((short)((uint)puVar7 >> 0x10),(short)puVar7 + sVar6);
    sVar4 = sVar4 + -1;
    unaff_ECX = 0;
  } while (sVar4 != 0);
  sVar4 = (short)auStack_e;
  puVar2 = (undefined2 *)segment(in_SS,sVar4);
  out(0x3c5,(char)*puVar2);
  puVar2 = (undefined2 *)segment(in_SS,sVar4 + 2);
  out(0x3cf,(char)*puVar2);
  segment(in_SS,sVar4 + 4);
  segment(in_SS,sVar4 + 6);
  segment(in_SS,sVar4 + 0xc);
  return *puVar2;
}


// ================================================================================================
// sub_8c463 @ 0x8c463 [__watcall]
// ================================================================================================

ushort __watcall sub_8c463(void)

{
  undefined *puVar1;
  short *psVar2;
  undefined2 *puVar3;
  ushort *puVar4;
  byte bVar5;
  undefined uVar6;
  char cVar7;
  ushort uVar8;
  undefined4 unaff_ECX;
  undefined2 uVar11;
  int iVar9;
  int iVar10;
  short sVar12;
  short sVar13;
  int iVar14;
  undefined *puVar15;
  undefined4 unaff_EBP;
  undefined4 unaff_ESI;
  undefined *puVar16;
  short sVar17;
  undefined4 unaff_EDI;
  undefined *puVar18;
  undefined2 in_SS;
  undefined auStack_e [4];
  undefined auStack_a [8];
  undefined auStack_2 [2];
  
  iVar10 = CONCAT22((short)((uint)unaff_EBP >> 0x10),(short)auStack_2);
  sVar13 = (short)auStack_a;
  sVar12 = 0x60;
  puVar16 = (undefined *)CONCAT22((short)((uint)unaff_ESI >> 0x10),*(undefined2 *)(iVar10 + 6));
  sVar17 = *(short *)(iVar10 + 8);
  uVar11 = (undefined2)((uint)unaff_ECX >> 0x10);
  if ((*(ushort *)(iVar10 + 10) & 0x800) == 0) {
    out(0x3ce,5);
    bVar5 = in(0x3cf);
    out(0x3cf,(bVar5 & 0xfc) + 1);
    out(0x3c4,2);
    bVar5 = in(0x3c5);
    out(0x3c5,(bVar5 & 0xf0) + 0xf);
    iVar9 = CONCAT22(uVar11,8);
    uVar8 = *(ushort *)(iVar10 + 10);
    if ((uVar8 & 0x1000) != 0) {
      sVar17 = sVar17 + 0x2a0;
      sVar12 = -0x60;
    }
    puVar18 = (undefined *)CONCAT22((short)((uint)unaff_EDI >> 0x10),sVar17);
    do {
      puVar1 = puVar16 + 1;
      *puVar18 = *puVar16;
      puVar16 = puVar16 + 2;
      puVar18[1] = *puVar1;
      puVar18 = (undefined *)
                CONCAT22((short)((uint)(puVar18 + 2) >> 0x10),(short)(puVar18 + 2) + sVar12 + -2);
      iVar9 = iVar9 + -1;
    } while (iVar9 != 0);
  }
  else {
    out(0x3ce,5);
    bVar5 = in(0x3cf);
    out(0x3cf,bVar5 & 0xfc);
    out(0x3ce,4);
    bVar5 = in(0x3cf);
    out(0x3cf,bVar5 & 0xfc);
    out(0x3c4,2);
    bVar5 = in(0x3c5);
    out(0x3c5,(bVar5 & 0xf0) + 8);
    bVar5 = 8;
    if ((*(ushort *)(iVar10 + 10) & 0x1000) != 0) {
      sVar12 = -0x60;
    }
    puVar15 = auStack_e;
    iVar10 = CONCAT22(uVar11,4);
    do {
      sVar13 = (short)puVar15;
      psVar2 = (short *)segment(in_SS,sVar13);
      sVar17 = *psVar2;
      puVar3 = (undefined2 *)segment(in_SS,sVar13 + 2);
      iVar14 = CONCAT22((short)((uint)puVar15 >> 0x10),sVar13 + 4);
      puVar16 = (undefined *)CONCAT22((short)((uint)puVar16 >> 0x10),*puVar3);
      *(undefined2 *)(iVar14 + -2) = *puVar3;
      *(short *)(iVar14 + -4) = sVar17;
      *(short *)(iVar14 + -6) = (short)iVar10;
      iVar10 = CONCAT22((short)((uint)iVar10 >> 0x10),8);
      do {
        puVar18 = (undefined *)segment(0xa000,sVar17 + 1);
        *puVar18 = *puVar16;
        puVar18 = (undefined *)segment(0xa000,sVar17);
        *puVar18 = puVar16[1];
        sVar17 = sVar17 + sVar12;
        puVar16 = (undefined *)CONCAT22((short)((uint)puVar16 >> 0x10),(short)puVar16 + 2);
        iVar10 = iVar10 + -1;
      } while (iVar10 != 0);
      out(0x3c4,2);
      uVar6 = in(0x3c5);
      uVar8 = CONCAT11(bVar5,uVar6) & 0xfff0;
      bVar5 = (byte)(uVar8 >> 9);
      out(0x3c5,(char)uVar8 + bVar5);
      out(0x3ce,4);
      cVar7 = in(0x3cf);
      out(0x3cf,cVar7 + '\x01');
      sVar13 = (short)(iVar14 + -6);
      puVar4 = (ushort *)segment(in_SS,sVar13);
      puVar15 = (undefined *)CONCAT22((short)((uint)(iVar14 + -6) >> 0x10),sVar13 + 2);
      iVar10 = *puVar4 - 1;
    } while (iVar10 != 0);
    cVar7 = in(0x3cf);
    uVar8 = CONCAT11(bVar5,cVar7 + -1);
    out(0x3cf,cVar7 + -1);
    segment(in_SS,sVar13 + 2);
    segment(in_SS,sVar13 + 4);
    sVar13 = sVar13 + 6;
  }
  segment(in_SS,sVar13);
  segment(in_SS,sVar13 + 2);
  segment(in_SS,sVar13 + 8);
  return uVar8;
}


// ================================================================================================
// sub_8c58c @ 0x8c58c [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined2 __watcall sub_8c58c(void)

{
  undefined2 *puVar1;
  byte bVar2;
  short sVar3;
  undefined2 in_SS;
  undefined auStack_c [12];
  
  dword_eda04._0_2_ = (ushort)dword_eda04 & 1 ^ 1;
  if ((ushort)dword_eda04 == 1) {
    sVar3 = 0x4400;
  }
  else {
    sVar3 = 0xb00;
  }
  sVar3 = ((ushort)dword_dd6ac >> 2) + dword_c7290 * _dword_dd6aa + sVar3;
  do {
    do {
      bVar2 = in(0x3da);
    } while ((bVar2 & 8) != 0);
  } while ((bVar2 & 1) == 0);
  out(0x3d4,CONCAT11((char)((ushort)sVar3 >> 8),0xc));
  out(0x3d4,CONCAT11((char)sVar3,0xd));
  do {
    bVar2 = in(0x3da);
  } while ((bVar2 & 8) != 0);
  do {
    bVar2 = in(0x3da);
  } while ((bVar2 & 8) == 0);
  out(0x3c0,0x33);
  out(0x3c0,(char)(((ushort)dword_dd6ac & 3) << 1));
  do {
    bVar2 = in(0x3da);
  } while ((bVar2 & 8) != 0);
  sVar3 = (short)auStack_c;
  segment(in_SS,sVar3);
  segment(in_SS,sVar3 + 2);
  segment(in_SS,sVar3 + 4);
  puVar1 = (undefined2 *)segment(in_SS,sVar3 + 6);
  segment(in_SS,sVar3 + 8);
  segment(in_SS,sVar3 + 10);
  return *puVar1;
}


// ================================================================================================
// sub_8c637 @ 0x8c637 [__watcall]
// ================================================================================================

undefined2 __watcall sub_8c637(void)

{
  ushort uVar1;
  ushort *puVar2;
  undefined2 *puVar3;
  byte bVar4;
  char cVar5;
  undefined4 unaff_ECX;
  int iVar6;
  short sVar7;
  undefined2 *puVar8;
  undefined4 unaff_EBP;
  int iVar9;
  undefined4 unaff_ESI;
  undefined2 uVar11;
  undefined *puVar10;
  undefined *unaff_EDI;
  undefined2 in_SS;
  undefined auStack_12 [16];
  undefined auStack_2 [2];
  
  iVar9 = CONCAT22((short)((uint)unaff_EBP >> 0x10),(short)auStack_2);
  out(0x3ce,5);
  bVar4 = in(0x3cf);
  out(0x3cf,bVar4 & 0xfc);
  out(0x3c4,2);
  bVar4 = in(0x3c5);
  bVar4 = bVar4 & 0xf0;
  cVar5 = '\x01';
  uVar11 = (undefined2)((uint)unaff_ESI >> 0x10);
  uVar1 = *(ushort *)CONCAT22(uVar11,*(undefined2 *)(iVar9 + 8));
  puVar8 = (undefined2 *)auStack_12;
  puVar10 = (undefined *)
            CONCAT22(uVar11,(short)*(undefined4 *)CONCAT22(uVar11,*(undefined2 *)(iVar9 + 6)));
  iVar6 = CONCAT22((short)((uint)unaff_ECX >> 0x10),4);
  do {
    out(0x3c5,bVar4 + cVar5);
    bVar4 = (bVar4 + cVar5) - cVar5;
    cVar5 = cVar5 << 1;
    *(short *)((int)puVar8 + -2) = (short)iVar6;
    unaff_EDI = (undefined *)CONCAT22((short)((uint)unaff_EDI >> 0x10),0xda78);
    for (iVar6 = CONCAT22((short)((uint)iVar6 >> 0x10),uVar1 >> 2); iVar6 != 0; iVar6 = iVar6 + -1)
    {
      *unaff_EDI = *puVar10;
      puVar10 = puVar10 + 1;
      unaff_EDI = unaff_EDI + 1;
    }
    puVar2 = (ushort *)segment(in_SS,(short)(undefined *)((int)puVar8 + -2));
    puVar8 = (undefined2 *)
             CONCAT22((short)((uint)((int)puVar8 + -2) >> 0x10),
                      (short)(undefined *)((int)puVar8 + -2) + 2);
    iVar6 = *puVar2 - 1;
  } while (iVar6 != 0);
  *puVar8 = *puVar8;
  uVar11 = (undefined2)((uint)puVar10 >> 0x10);
  uVar1 = *(ushort *)(CONCAT22(uVar11,*(undefined2 *)(iVar9 + 8)) + 2);
  puVar10 = (undefined *)
            CONCAT22(uVar11,(short)*(undefined4 *)(CONCAT22(uVar11,*(undefined2 *)(iVar9 + 6)) + 4))
  ;
  iVar6 = 4;
  cVar5 = '\x01';
  do {
    *(short *)((int)puVar8 + -2) = (short)unaff_EDI;
    *(short *)((int)puVar8 + -4) = (short)iVar6;
    out(0x3c5,bVar4 + cVar5);
    bVar4 = (bVar4 + cVar5) - cVar5;
    cVar5 = cVar5 << 1;
    for (iVar6 = CONCAT22((short)((uint)iVar6 >> 0x10),uVar1 >> 2); iVar6 != 0; iVar6 = iVar6 + -1)
    {
      *unaff_EDI = *puVar10;
      puVar10 = puVar10 + 1;
      unaff_EDI = unaff_EDI + 1;
    }
    sVar7 = (short)(undefined *)((int)puVar8 + -4);
    puVar2 = (ushort *)segment(in_SS,sVar7);
    puVar3 = (undefined2 *)segment(in_SS,sVar7 + 2);
    puVar8 = (undefined2 *)CONCAT22((short)((uint)((int)puVar8 + -4) >> 0x10),sVar7 + 4);
    unaff_EDI = (undefined *)CONCAT22((short)((uint)unaff_EDI >> 0x10),*puVar3);
    iVar6 = *puVar2 - 1;
  } while (iVar6 != 0);
  out(0x3c4,2);
  sVar7 = (short)(undefined *)((int)puVar8 + 4);
  puVar3 = (undefined2 *)segment(in_SS,sVar7);
  out(0x3c5,(char)*puVar3);
  out(0x3ce,5);
  puVar3 = (undefined2 *)segment(in_SS,sVar7 + 2);
  out(0x3cf,(char)*puVar3);
  segment(in_SS,sVar7 + 4);
  segment(in_SS,sVar7 + 6);
  segment(in_SS,sVar7 + 0xc);
  return *puVar3;
}


// ================================================================================================
// sub_8c6f0 @ 0x8c6f0 [__watcall]
// ================================================================================================

undefined2 __watcall sub_8c6f0(void)

{
  undefined2 *puVar1;
  byte bVar2;
  short sVar3;
  uint unaff_ECX;
  int iVar4;
  undefined4 unaff_EBP;
  ushort uVar5;
  undefined4 unaff_ESI;
  undefined *puVar6;
  undefined4 unaff_EDI;
  undefined *puVar7;
  undefined2 in_SS;
  undefined auStack_e [12];
  undefined auStack_2 [2];
  
  out(0x3ce,5);
  bVar2 = in(0x3cf);
  out(0x3cf,(bVar2 & 0xfc) + 1);
  out(0x3c4,2);
  bVar2 = in(0x3c5);
  out(0x3c5,(bVar2 & 0xf0) + 0xf);
  puVar6 = (undefined *)
           CONCAT22((short)((uint)unaff_ESI >> 0x10),word_dd70c * 0x300 + -0x7960 + word_dd6b2 * 2);
  puVar7 = (undefined *)
           CONCAT22((short)((uint)unaff_EDI >> 0x10),
                    *(undefined2 *)(CONCAT22((short)((uint)unaff_EBP >> 0x10),(short)auStack_2) + 6)
                   );
  sVar3 = 0xb0;
  unaff_ECX = unaff_ECX & 0xffff0000;
  do {
    for (iVar4 = CONCAT22((short)(unaff_ECX >> 0x10),0x52); iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar7 = *puVar6;
      puVar6 = puVar6 + 1;
      puVar7 = puVar7 + 1;
    }
    uVar5 = (short)puVar6 + 0xe;
    if (0xc89f < uVar5) {
      uVar5 = (short)puVar6 + 0xbe0e;
    }
    puVar6 = (undefined *)CONCAT22((short)((uint)puVar6 >> 0x10),uVar5);
    sVar3 = sVar3 + -1;
    unaff_ECX = 0;
  } while (sVar3 != 0);
  out(0x3c4,2);
  sVar3 = (short)auStack_e;
  puVar1 = (undefined2 *)segment(in_SS,sVar3);
  out(0x3c5,(char)*puVar1);
  out(0x3ce,5);
  puVar1 = (undefined2 *)segment(in_SS,sVar3 + 2);
  out(0x3cf,(char)*puVar1);
  segment(in_SS,sVar3 + 4);
  segment(in_SS,sVar3 + 6);
  segment(in_SS,sVar3 + 0xc);
  return *puVar1;
}


// ================================================================================================
// sub_8c798 @ 0x8c798 [__watcall]
// ================================================================================================

undefined2 __watcall sub_8c798(void)

{
  undefined2 *puVar1;
  byte bVar2;
  undefined4 unaff_ECX;
  int iVar3;
  short sVar4;
  undefined4 unaff_EBP;
  int iVar5;
  undefined4 unaff_ESI;
  undefined *puVar6;
  undefined4 unaff_EDI;
  undefined *puVar7;
  undefined2 in_SS;
  undefined auStack_e [12];
  undefined auStack_2 [2];
  
  iVar5 = CONCAT22((short)((uint)unaff_EBP >> 0x10),(short)auStack_2);
  out(0x3ce,5);
  bVar2 = in(0x3cf);
  out(0x3cf,(bVar2 & 0xfc) + 1);
  out(0x3c4,2);
  bVar2 = in(0x3c5);
  out(0x3c5,(bVar2 & 0xf0) + 0xf);
  puVar6 = (undefined *)CONCAT22((short)((uint)unaff_ESI >> 0x10),*(undefined2 *)(iVar5 + 6));
  puVar7 = (undefined *)CONCAT22((short)((uint)unaff_EDI >> 0x10),*(undefined2 *)(iVar5 + 8));
  for (iVar3 = CONCAT22((short)((uint)unaff_ECX >> 0x10),0xa40); iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar7 = *puVar6;
    puVar6 = puVar6 + 1;
    puVar7 = puVar7 + 1;
  }
  sVar4 = (short)auStack_e;
  puVar1 = (undefined2 *)segment(in_SS,sVar4);
  out(0x3c5,(char)*puVar1);
  puVar1 = (undefined2 *)segment(in_SS,sVar4 + 2);
  out(0x3cf,(char)*puVar1);
  segment(in_SS,sVar4 + 4);
  segment(in_SS,sVar4 + 6);
  segment(in_SS,sVar4 + 0xc);
  return *puVar1;
}


// ================================================================================================
// sub_8c7f5 @ 0x8c7f5 [__watcall]
// ================================================================================================

undefined2 __watcall sub_8c7f5(void)

{
  undefined2 *puVar1;
  byte bVar2;
  undefined4 unaff_ECX;
  int iVar3;
  short sVar4;
  undefined4 unaff_EBP;
  int iVar5;
  undefined4 unaff_ESI;
  undefined *puVar6;
  undefined4 unaff_EDI;
  undefined *puVar7;
  undefined2 in_SS;
  undefined auStack_e [12];
  undefined auStack_2 [2];
  
  iVar5 = CONCAT22((short)((uint)unaff_EBP >> 0x10),(short)auStack_2);
  out(0x3ce,5);
  bVar2 = in(0x3cf);
  out(0x3cf,(bVar2 & 0xfc) + 1);
  out(0x3c4,2);
  bVar2 = in(0x3c5);
  out(0x3c5,(bVar2 & 0xf0) + 0xf);
  puVar6 = (undefined *)CONCAT22((short)((uint)unaff_ESI >> 0x10),*(undefined2 *)(iVar5 + 6));
  puVar7 = (undefined *)CONCAT22((short)((uint)unaff_EDI >> 0x10),*(undefined2 *)(iVar5 + 8));
  for (iVar3 = CONCAT22((short)((uint)unaff_ECX >> 0x10),*(undefined2 *)(iVar5 + 10)); iVar3 != 0;
      iVar3 = iVar3 + -1) {
    *puVar7 = *puVar6;
    puVar6 = puVar6 + 1;
    puVar7 = puVar7 + 1;
  }
  sVar4 = (short)auStack_e;
  puVar1 = (undefined2 *)segment(in_SS,sVar4);
  out(0x3c5,(char)*puVar1);
  puVar1 = (undefined2 *)segment(in_SS,sVar4 + 2);
  out(0x3cf,(char)*puVar1);
  segment(in_SS,sVar4 + 4);
  segment(in_SS,sVar4 + 6);
  segment(in_SS,sVar4 + 0xc);
  return *puVar1;
}


// ================================================================================================
// sub_8c852 @ 0x8c852 [__watcall]
// ================================================================================================

undefined2 __watcall sub_8c852(void)

{
  short *psVar1;
  undefined2 *puVar2;
  byte bVar3;
  uint unaff_ECX;
  int iVar4;
  short sVar5;
  undefined4 unaff_EBP;
  int iVar6;
  undefined4 unaff_ESI;
  undefined *puVar7;
  short sVar8;
  undefined4 unaff_EDI;
  undefined *puVar9;
  undefined2 in_SS;
  undefined auStack_e [12];
  undefined auStack_2 [2];
  
  iVar6 = CONCAT22((short)((uint)unaff_EBP >> 0x10),(short)auStack_2);
  out(0x3ce,5);
  bVar3 = in(0x3cf);
  out(0x3cf,(bVar3 & 0xfc) + 1);
  out(0x3c4,2);
  bVar3 = in(0x3c5);
  out(0x3c5,(bVar3 & 0xf0) + 0xf);
  sVar8 = dword_c7290 * *(short *)(iVar6 + 0xc) + *(short *)(iVar6 + 10);
  puVar9 = (undefined *)CONCAT22((short)((uint)unaff_EDI >> 0x10),sVar8 + *(short *)(iVar6 + 8));
  puVar7 = (undefined *)CONCAT22((short)((uint)unaff_ESI >> 0x10),sVar8 + *(short *)(iVar6 + 6));
  sVar8 = *(short *)(iVar6 + 0xe);
  sVar5 = dword_c7290 - sVar8;
  unaff_ECX = unaff_ECX & 0xffff0000;
  do {
    for (iVar4 = CONCAT22((short)(unaff_ECX >> 0x10),sVar8); iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar9 = *puVar7;
      puVar7 = puVar7 + 1;
      puVar9 = puVar9 + 1;
    }
    puVar9 = (undefined *)CONCAT22((short)((uint)puVar9 >> 0x10),(short)puVar9 + sVar5);
    puVar7 = (undefined *)CONCAT22((short)((uint)puVar7 >> 0x10),(short)puVar7 + sVar5);
    psVar1 = (short *)(iVar6 + 0x10);
    *psVar1 = *psVar1 + -1;
    unaff_ECX = 0;
  } while (*psVar1 != 0);
  sVar8 = (short)auStack_e;
  puVar2 = (undefined2 *)segment(in_SS,sVar8);
  out(0x3c5,(char)*puVar2);
  puVar2 = (undefined2 *)segment(in_SS,sVar8 + 2);
  out(0x3cf,(char)*puVar2);
  segment(in_SS,sVar8 + 4);
  segment(in_SS,sVar8 + 6);
  segment(in_SS,sVar8 + 0xc);
  return *puVar2;
}


// ================================================================================================
// direction8 @ 0x8c8e8 [__watcall]
// ================================================================================================

short __watcall direction8(ushort param_1,ushort unaff_DX)

{
  uint uVar1;
  bool bVar2;
  
  if (param_1 == 0 && unaff_DX == 0) {
    return 8;
  }
  bVar2 = (short)param_1 < 0;
  if (bVar2) {
    param_1 = -param_1;
  }
  uVar1 = (uint)bVar2;
  if ((short)unaff_DX < 0) {
    unaff_DX = -unaff_DX;
    uVar1 = uVar1 | 2;
  }
  if (param_1 <= (ushort)(unaff_DX << 1)) {
    uVar1 = uVar1 | 4;
  }
  if (unaff_DX <= (ushort)(param_1 << 1)) {
    uVar1 = uVar1 | 8;
  }
  return (short)(char)(&unk_d2c74)[uVar1];
}


// ================================================================================================
// sub_8c944 @ 0x8c944 [__watcall]
// ================================================================================================

void __watcall sub_8c944(void)

{
  undefined2 in_SS;
  
  word_d2f44 = in_SS;
  return;
}


// ================================================================================================
// __CHK @ 0x8c94c [__regsafe]
// ================================================================================================

/* WARNING: Variable defined which should be unmapped: param_1 */

void __regsafe __CHK(undefined4 param_1)

{
  LOCK();
  UNLOCK();
  __STKCHK(param_1);
  return;
}


// ================================================================================================
// __STKCHK @ 0x8c95f [__watcall]
// ================================================================================================

uint * __watcall __STKCHK(undefined *param_1)

{
  uint *puVar1;
  char *pcVar2;
  uint uVar3;
  uint *puVar4;
  int iVar5;
  ushort in_SS;
  uint in_stack_00000004;
  int in_stack_00000008;
  uint in_stack_0000000c;
  int in_stack_00000010;
  int in_stack_00000014;
  undefined4 in_stack_00000018;
  
  if ((param_1 < &stack0x00000000) &&
     (puVar1 = (uint *)-((int)param_1 - (int)&stack0x00000000),
     dword_d4ce8 <= puVar1 && -(int)dword_d4ce8 != (int)param_1 - (int)&stack0x00000000)) {
    return puVar1;
  }
  if (in_SS != word_d2f44) {
    return (uint *)(uint)in_SS;
  }
  pcVar2 = (char *)sub_98683(aStackOverflow,1);
  *pcVar2 = *pcVar2 + (char)pcVar2;
  *pcVar2 = *pcVar2 + (char)pcVar2;
  iVar5 = (int)(in_stack_00000004 & 0x700) >> 8;
  puVar4 = &dword_eda08 + iVar5 * 5;
  uVar3 = in_stack_00000010 - 1;
  *(uint *)(&DAT_000eda10 + iVar5 * 0x14) = uVar3;
  *(int *)(&DAT_000eda14 + iVar5 * 0x14) = in_stack_00000014 + -1;
  (&DAT_000eda18)[iVar5 * 5] = in_stack_00000018;
  puVar1 = (uint *)getmemblock();
  sub_8e3e4(puVar1 + 1,aLOWMEM,0xc);
  *puVar1 = in_stack_00000008 + uVar3 & ~uVar3;
  puVar1[5] = 0;
  puVar1[4] = 0;
  puVar1[9] = 0;
  puVar1[6] = in_stack_00000004 | 0x8000;
  *puVar4 = (uint)puVar1;
  puVar1 = (uint *)getmemblock();
  sub_8e3e4(puVar1 + 1,aHIGHMEM,0xc);
  *puVar1 = in_stack_0000000c & ~uVar3;
  puVar1[5] = 0;
  puVar1[4] = 0;
  puVar1[8] = 0;
  puVar1[6] = in_stack_00000004 | 0x8020;
  (&dword_eda0c)[iVar5 * 5] = puVar1;
  *(uint **)(*puVar4 + 0x20) = puVar1;
  puVar1[9] = *puVar4;
  return puVar4;
}


// ================================================================================================
// __STKOVERFLOW @ 0x8c97d [__watcall] noreturn
// ================================================================================================

uint * __watcall __STKOVERFLOW(void)

{
  char *pcVar1;
  uint uVar2;
  uint *puVar3;
  uint *puVar4;
  int iVar5;
  uint in_stack_00000004;
  int in_stack_00000008;
  uint in_stack_0000000c;
  int in_stack_00000010;
  int in_stack_00000014;
  undefined4 in_stack_00000018;
  
  pcVar1 = (char *)sub_98683(aStackOverflow,1);
  *pcVar1 = *pcVar1 + (char)pcVar1;
  *pcVar1 = *pcVar1 + (char)pcVar1;
  iVar5 = (int)(in_stack_00000004 & 0x700) >> 8;
  puVar4 = &dword_eda08 + iVar5 * 5;
  uVar2 = in_stack_00000010 - 1;
  *(uint *)(&DAT_000eda10 + iVar5 * 0x14) = uVar2;
  *(int *)(&DAT_000eda14 + iVar5 * 0x14) = in_stack_00000014 + -1;
  (&DAT_000eda18)[iVar5 * 5] = in_stack_00000018;
  puVar3 = (uint *)getmemblock();
  sub_8e3e4(puVar3 + 1,aLOWMEM,0xc);
  *puVar3 = in_stack_00000008 + uVar2 & ~uVar2;
  puVar3[5] = 0;
  puVar3[4] = 0;
  puVar3[9] = 0;
  puVar3[6] = in_stack_00000004 | 0x8000;
  *puVar4 = (uint)puVar3;
  puVar3 = (uint *)getmemblock();
  sub_8e3e4(puVar3 + 1,aHIGHMEM,0xc);
  *puVar3 = in_stack_0000000c & ~uVar2;
  puVar3[5] = 0;
  puVar3[4] = 0;
  puVar3[8] = 0;
  puVar3[6] = in_stack_00000004 | 0x8020;
  (&dword_eda0c)[iVar5 * 5] = puVar3;
  *(uint **)(*puVar4 + 0x20) = puVar3;
  puVar3[9] = *puVar4;
  return puVar4;
}


// ================================================================================================
// sub_8c990 @ 0x8c990 [__cdecl]
// ================================================================================================

uint * sub_8c990(uint param_1,int param_2,uint param_3,int param_4,int param_5,undefined4 param_6)

{
  uint uVar1;
  uint *puVar2;
  uint *puVar3;
  int iVar4;
  
  iVar4 = (int)(param_1 & 0x700) >> 8;
  puVar3 = &dword_eda08 + iVar4 * 5;
  uVar1 = param_4 - 1;
  *(uint *)(&DAT_000eda10 + iVar4 * 0x14) = uVar1;
  *(int *)(&DAT_000eda14 + iVar4 * 0x14) = param_5 + -1;
  (&DAT_000eda18)[iVar4 * 5] = param_6;
  puVar2 = (uint *)getmemblock();
  sub_8e3e4(puVar2 + 1,aLOWMEM,0xc);
  *puVar2 = param_2 + uVar1 & ~uVar1;
  puVar2[5] = 0;
  puVar2[4] = 0;
  puVar2[9] = 0;
  puVar2[6] = param_1 | 0x8000;
  *puVar3 = (uint)puVar2;
  puVar2 = (uint *)getmemblock();
  sub_8e3e4(puVar2 + 1,aHIGHMEM,0xc);
  *puVar2 = param_3 & ~uVar1;
  puVar2[5] = 0;
  puVar2[4] = 0;
  puVar2[8] = 0;
  puVar2[6] = param_1 | 0x8020;
  (&dword_eda0c)[iVar4 * 5] = puVar2;
  *(uint **)(*puVar3 + 0x20) = puVar2;
  puVar2[9] = *puVar3;
  return puVar3;
}


// ================================================================================================
// sub_8ca6c @ 0x8ca6c [__watcall]
// ================================================================================================

int * __watcall sub_8ca6c(void)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  int iVar4;
  uint param_5;
  undefined4 param_6;
  undefined4 param_7;
  undefined4 in_stack_00000010;
  undefined4 in_stack_00000014;
  undefined4 in_stack_00000018;
  undefined4 in_stack_0000001c;
  
  iVar4 = (int)(param_5 & 0x700) >> 8;
  piVar3 = (int *)sub_8c990(param_6,param_7,in_stack_00000010,in_stack_00000014,in_stack_00000018,
                            in_stack_0000001c);
  if (*(int *)(&dword_eda08)[iVar4 * 5] == *(int *)(&dword_eda0c)[iVar4 * 5]) {
    (&dword_eda08)[iVar4 * 5] = *piVar3;
  }
  else {
    iVar1 = *piVar3;
    ((int *)(&dword_eda0c)[iVar4 * 5])[8] = iVar1;
    piVar2 = (int *)(&dword_eda0c)[iVar4 * 5];
    *(int **)(iVar1 + 0x24) = piVar2;
    iVar1 = *(int *)*piVar3;
    piVar2[4] = iVar1 - *piVar2;
    *(int *)((&dword_eda0c)[iVar4 * 5] + 0x14) = iVar1 - *piVar2;
  }
  (&dword_eda0c)[iVar4 * 5] = piVar3[1];
  return piVar3;
}


// ================================================================================================
// sub_8caf4 @ 0x8caf4 [__cdecl]
// ================================================================================================

void sub_8caf4(uint param_1,int param_2,uint param_3)

{
  uint uVar1;
  int *piVar2;
  int iVar3;
  uint uVar4;
  uint *puVar5;
  int iVar6;
  
  iVar3 = (int)(param_1 & 0x700) >> 8;
  uVar1 = *(uint *)(&DAT_000eda10 + iVar3 * 0x14);
  uVar4 = ~uVar1;
  puVar5 = (uint *)getmemblock();
  sub_8e3e4(puVar5 + 1,aHIGHMEM,0xc);
  *puVar5 = param_3 & uVar4;
  puVar5[5] = 0;
  puVar5[4] = 0;
  puVar5[8] = 0;
  puVar5[6] = param_1 | 0x8020;
  sub_8e3e4((&dword_eda0c)[iVar3 * 5] + 4,&aGAP,0xc);
  *(uint **)((&dword_eda0c)[iVar3 * 5] + 0x20) = puVar5;
  piVar2 = (int *)(&dword_eda0c)[iVar3 * 5];
  puVar5[9] = (uint)piVar2;
  iVar6 = (param_2 + uVar1 & uVar4) - *piVar2;
  piVar2[4] = iVar6;
  *(int *)(puVar5[9] + 0x14) = iVar6;
  (&dword_eda0c)[iVar3 * 5] = puVar5;
  return;
}


// ================================================================================================
// sub_8cba4 @ 0x8cba4 [__watcall]
// ================================================================================================

int __watcall sub_8cba4(void)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  uint in_stack_00000004;
  int in_stack_00000008;
  
  iVar6 = (int)(in_stack_00000004 & 0x700) >> 8;
  piVar7 = (int *)(&dword_eda08)[iVar6 * 5];
  if (piVar7 != (int *)(&dword_eda0c)[iVar6 * 5]) {
    do {
      if (in_stack_00000008 == *piVar7 + piVar7[4]) break;
      piVar7 = (int *)piVar7[8];
    } while (piVar7 != (int *)(&dword_eda0c)[iVar6 * 5]);
  }
  if (piVar7 == (int *)(&dword_eda0c)[iVar6 * 5]) {
    fatalerror(aReleaseMemoryNotFound);
  }
  piVar1 = (int *)piVar7[8];
  iVar2 = *piVar1;
  iVar3 = *piVar7;
  iVar4 = piVar7[4];
  if (piVar1 == (int *)(&dword_eda0c)[iVar6 * 5]) {
    piVar7[4] = 0;
    piVar7[5] = piVar7[4];
    piVar7[8] = 0;
    (&dword_eda0c)[iVar6 * 5] = piVar7;
  }
  else {
    iVar5 = (piVar1[4] + *piVar1) - *piVar7;
    piVar7[4] = iVar5;
    piVar7[5] = iVar5;
    piVar7[8] = piVar1[8];
    piVar1[9] = (int)piVar7;
  }
  sub_8db78(piVar1);
  piVar1 = (int *)(&dword_eda08)[iVar6 * 5];
  if (piVar7 == piVar1) {
    piVar1[4] = 0;
    piVar1[5] = piVar1[4];
  }
  return (iVar2 - iVar3) - iVar4;
}


// ================================================================================================
// sub_8cc5c @ 0x8cc5c [__cdecl]
// ================================================================================================

void sub_8cc5c(undefined4 param_1,undefined4 param_2)

{
  dword_d2f60 = param_1;
  dword_d2f5c = param_2;
  return;
}


// ================================================================================================
// sub_8cc70 @ 0x8cc70 [__cdecl]
// ================================================================================================

void sub_8cc70(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  reservemem_locked(param_1,param_2,param_3,1);
  return;
}


// ================================================================================================
// sub_8cc8c @ 0x8cc8c [__cdecl]
// ================================================================================================

void sub_8cc8c(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  reservemem_locked(param_1,param_2,param_3,0);
  return;
}


// ================================================================================================
// allocmem @ 0x8cca8 [__cdecl]
// ================================================================================================

undefined4 allocmem(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)reservemem_locked(param_1,param_2,param_3,1);
  return *puVar1;
}


// ================================================================================================
// sub_8ccc4 @ 0x8ccc4 [__watcall]
// ================================================================================================

undefined4 __watcall sub_8ccc4(void)

{
  undefined4 *puVar1;
  undefined4 in_stack_00000004;
  undefined4 in_stack_00000008;
  undefined4 in_stack_0000000c;
  
  puVar1 = (undefined4 *)reservemem_locked(in_stack_00000004,in_stack_00000008,in_stack_0000000c,0);
  return *puVar1;
}


// ================================================================================================
// sub_8cce0 @ 0x8cce0 [__watcall]
// ================================================================================================

undefined4 __watcall sub_8cce0(void)

{
  undefined4 *puVar1;
  undefined4 in_stack_00000004;
  undefined4 in_stack_00000008;
  undefined4 in_stack_0000000c;
  undefined4 in_stack_00000010;
  
  puVar1 = (undefined4 *)
           reservemem_locked(in_stack_00000004,in_stack_00000008,in_stack_0000000c,in_stack_00000010
                            );
  return *puVar1;
}


// ================================================================================================
// reservemem_locked @ 0x8cd04 [__cdecl]
// ================================================================================================

undefined4 reservemem_locked(void)

{
  undefined4 uVar1;
  
  memman_lock(dword_edab0);
  uVar1 = reservemem();
  memman_unlock(dword_edab0);
  return uVar1;
}


// ================================================================================================
// reservemem @ 0x8cd4c [__watcall]
// ================================================================================================

uint * __watcall reservemem(void)

{
  undefined4 uVar1;
  int iVar2;
  uint *puVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  uint *puVar8;
  undefined4 in_stack_00000004;
  uint in_stack_00000008;
  uint in_stack_0000000c;
  int in_stack_00000010;
  char *pcVar9;
  uint local_10;
  
  if ((int)in_stack_00000008 < 0) {
    if (in_stack_00000010 == 0) {
      return (uint *)0x0;
    }
    memman_unlock(dword_edab0);
    uVar1 = sub_8dab8();
    fatalerror(s_e_reservemem___INVALID_SIZE_REQU_000c3bca + 2,in_stack_00000008,uVar1);
    return (uint *)0x0;
  }
  iVar5 = (int)(in_stack_0000000c & 0x700) >> 8;
  iVar2 = iVar5 * 0x14;
  puVar3 = &dword_eda08 + iVar5 * 5;
  uVar1 = sub_8e424(in_stack_00000004);
  if ((in_stack_0000000c & 0x40) == 0) {
    local_10 = in_stack_00000008 + *(uint *)(&DAT_000eda10 + iVar2) &
               ~*(uint *)(&DAT_000eda10 + iVar2);
  }
  else {
    local_10 = in_stack_00000008 + *(uint *)(&DAT_000eda14 + iVar2) &
               ~*(uint *)(&DAT_000eda14 + iVar2);
  }
  uVar7 = *puVar3;
  if (uVar7 == 0) goto LAB_0008d097;
  if ((in_stack_0000000c & 0x20) != 0) {
    if ((in_stack_0000000c & 0x10) == 0) {
      sub_8d990(uVar7,(&dword_eda0c)[iVar5 * 5]);
    }
LAB_0008cf66:
    puVar8 = (uint *)((uint *)(&dword_eda0c)[iVar5 * 5])[9];
    uVar7 = *(uint *)(&dword_eda0c)[iVar5 * 5];
    if ((in_stack_0000000c & 0x40) != 0) {
      uVar7 = uVar7 & ~*(uint *)(&DAT_000eda14 + iVar2);
    }
    do {
      iVar6 = 0;
      while( true ) {
        uVar4 = *puVar8 + puVar8[4];
        if ((in_stack_0000000c & 0x40) != 0) {
          uVar4 = ~*(uint *)(&DAT_000eda14 + iVar2) & *(int *)(&DAT_000eda14 + iVar2) + uVar4;
        }
        if (uVar4 < uVar7) break;
        uVar7 = *puVar8;
        if ((in_stack_0000000c & 0x40) != 0) {
          uVar7 = uVar7 & ~*(uint *)(&DAT_000eda14 + iVar2);
        }
        if (puVar8 == (uint *)*puVar3) goto LAB_0008cfbd;
        puVar8 = (uint *)puVar8[9];
      }
      iVar6 = uVar7 - uVar4;
LAB_0008cfbd:
      if ((int)local_10 <= iVar6) {
        puVar3 = (uint *)getmemblock();
        puVar3[6] = in_stack_0000000c;
        puVar3[7] = dword_d2f64;
        puVar3[5] = in_stack_00000008;
        puVar3[4] = local_10;
        dword_d2f64 = dword_d2f64 + 1;
        sub_8e3e4(puVar3 + 1,uVar1,0xc);
        *puVar3 = uVar7 - local_10;
        puVar3[9] = (uint)puVar8;
        uVar7 = puVar8[8];
        puVar3[8] = uVar7;
        *(uint **)(uVar7 + 0x24) = puVar3;
        puVar8[8] = (uint)puVar3;
        sub_8da98();
        return puVar3;
      }
      if (puVar8 == (uint *)*puVar3) goto LAB_0008d03d;
      uVar7 = *puVar8;
      if ((in_stack_0000000c & 0x40) != 0) {
        uVar7 = uVar7 & ~*(uint *)(&DAT_000eda14 + iVar2);
      }
      puVar8 = (uint *)puVar8[9];
    } while( true );
  }
  if ((in_stack_0000000c & 0x10) == 0) {
    sub_8d844((&dword_eda0c)[iVar5 * 5],uVar7);
  }
  do {
    puVar8 = (uint *)((uint *)*puVar3)[8];
    uVar7 = *(uint *)*puVar3;
    if ((in_stack_0000000c & 0x40) != 0) {
      uVar7 = ~*(uint *)(&DAT_000eda14 + iVar2) & *(int *)(&DAT_000eda14 + iVar2) + uVar7;
    }
    if (*puVar8 <= uVar7) goto LAB_0008ce43;
LAB_0008ce3d:
    iVar6 = *puVar8 - uVar7;
    while( true ) {
      if ((int)local_10 <= iVar6) {
        puVar3 = (uint *)getmemblock();
        puVar3[6] = in_stack_0000000c;
        puVar3[7] = dword_d2f64;
        puVar3[5] = in_stack_00000008;
        puVar3[4] = local_10;
        dword_d2f64 = dword_d2f64 + 1;
        sub_8e3e4(puVar3 + 1,uVar1,0xc);
        *puVar3 = uVar7;
        puVar3[9] = puVar8[9];
        puVar3[8] = (uint)puVar8;
        *(uint **)(puVar8[9] + 0x20) = puVar3;
        puVar8[9] = (uint)puVar3;
        sub_8da98();
        return puVar3;
      }
      if (puVar8 == (uint *)(&dword_eda0c)[iVar5 * 5]) break;
      uVar7 = *puVar8 + puVar8[4];
      if ((in_stack_0000000c & 0x40) != 0) {
        uVar7 = uVar7 + *(uint *)(&DAT_000eda14 + iVar2) & ~*(uint *)(&DAT_000eda14 + iVar2);
      }
      puVar8 = (uint *)puVar8[8];
      if (uVar7 < *puVar8) {
        iVar6 = *puVar8 - uVar7;
      }
      else {
LAB_0008ce43:
        while( true ) {
          iVar6 = 0;
          uVar7 = *puVar8 + puVar8[4];
          if ((in_stack_0000000c & 0x40) != 0) {
            uVar7 = ~*(uint *)(&DAT_000eda14 + iVar2) & *(int *)(&DAT_000eda14 + iVar2) + uVar7;
          }
          if (puVar8 == (uint *)(&dword_eda0c)[iVar5 * 5]) break;
          puVar8 = (uint *)puVar8[8];
          if (uVar7 < *puVar8) goto LAB_0008ce3d;
        }
      }
    }
    iVar6 = sub_8d604(in_stack_0000000c);
  } while ((iVar6 != 0) || (iVar6 = sub_8d844((&dword_eda0c)[iVar5 * 5],*puVar3), iVar6 != 0));
  if (in_stack_00000010 == 0) goto LAB_0008d097;
  memman_unlock(dword_edab0);
  uVar1 = sub_8dab8();
  pcVar9 = s_rreservemem___OUT_OF_MEMORY_requ_000c3c0f + 1;
  goto LAB_0008d08f;
LAB_0008d03d:
  iVar6 = sub_8d604(in_stack_0000000c);
  if ((iVar6 != 0) || (iVar6 = sub_8d990(*puVar3,(&dword_eda0c)[iVar5 * 5]), iVar6 != 0))
  goto LAB_0008cf66;
  if (in_stack_00000010 == 0) goto LAB_0008d097;
  memman_unlock(dword_edab0);
  uVar1 = sub_8dab8();
  pcVar9 = aReservememOUTOFMEMORYReq_c3c4c;
LAB_0008d08f:
  fatalerror(pcVar9,in_stack_00000008,uVar1);
LAB_0008d097:
  if (in_stack_00000010 != 0) {
    memman_unlock(dword_edab0);
    fatalerror(s_emreservemem___INVALID_TYPE_FLAG_000c3c86 + 2,in_stack_0000000c);
  }
  return (uint *)0x0;
}


// ================================================================================================
// sub_8d0c8 @ 0x8d0c8 [__cdecl]
// ================================================================================================

void sub_8d0c8(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  
  uVar1 = findmemblock(param_1,param_2,param_3);
  resizemem(uVar1);
  return;
}


// ================================================================================================
// sub_8d0ec @ 0x8d0ec [__watcall]
// ================================================================================================

void __watcall sub_8d0ec(void)

{
  undefined4 uVar1;
  undefined4 in_stack_00000004;
  undefined4 in_stack_00000008;
  
  uVar1 = findmemblock(in_stack_00000004,in_stack_00000008,1);
  resizemem(uVar1);
  return;
}


// ================================================================================================
// sub_8d10c @ 0x8d10c [__watcall]
// ================================================================================================

void __watcall sub_8d10c(void)

{
  undefined4 uVar1;
  undefined4 in_stack_00000004;
  undefined4 in_stack_00000008;
  
  uVar1 = findmemblock(in_stack_00000004,in_stack_00000008,0);
  resizemem(uVar1);
  return;
}


// ================================================================================================
// sub_8d12c @ 0x8d12c [__watcall]
// ================================================================================================

void __watcall sub_8d12c(void)

{
  undefined4 in_stack_00000004;
  undefined4 in_stack_00000008;
  
  resizemem(in_stack_00000004,in_stack_00000008,1);
  return;
}


// ================================================================================================
// sub_8d144 @ 0x8d144 [__cdecl]
// ================================================================================================

void sub_8d144(undefined4 param_1,undefined4 param_2)

{
  resizemem(param_1,param_2,0);
  return;
}


// ================================================================================================
// resizemem @ 0x8d15c [__cdecl]
// ================================================================================================

int resizemem(int *param_1,int param_2,int param_3)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  
  uVar4 = (param_1[6] & 0x700U) >> 8;
  memman_lock(dword_edab0);
  iVar5 = *(int *)param_1[8] - *param_1;
  uVar1 = param_2 + *(uint *)(&DAT_000eda10 + uVar4 * 0x14) &
          ~*(uint *)(&DAT_000eda10 + uVar4 * 0x14);
  if (param_2 < 0) {
    memman_unlock(dword_edab0);
    if (param_2 == -1) {
      return iVar5;
    }
    if (param_3 != 0) {
      memman_unlock(dword_edab0);
      uVar2 = sub_8dab8();
      fatalerror(aResizememINVALIDSIZEREQU,param_2,uVar2);
    }
  }
  else {
    while( true ) {
      if ((int)uVar1 < iVar5) {
        param_1[5] = param_2;
        param_1[4] = uVar1;
        memman_unlock(dword_edab0);
        return param_2;
      }
      if ((*(byte *)(param_1[8] + 0x18) & 0x18) == 0) break;
      iVar3 = sub_8d844((&dword_eda0c)[uVar4 * 5],param_1[8]);
      if (iVar3 == 0) break;
LAB_0008d257:
      iVar5 = *(int *)param_1[8] - *param_1;
      uVar1 = ~*(uint *)(&DAT_000eda10 + uVar4 * 0x14) &
              param_2 + *(uint *)(&DAT_000eda10 + uVar4 * 0x14);
    }
    if ((*(byte *)(param_1 + 6) & 0x18) != 0) {
      iVar3 = sub_8d990((&dword_eda08)[uVar4 * 5],param_1);
      if (iVar3 != 0) goto LAB_0008d257;
    }
    memman_unlock(dword_edab0);
    if (param_3 != 0) {
      fatalerror(s_laresizememblock___NO_ROOM_TO_RE_000c3cf2 + 2,param_2,iVar5);
    }
  }
  return 0;
}


// ================================================================================================
// findmemblock @ 0x8d2a0 [__cdecl]
// ================================================================================================

int * findmemblock(int param_1)

{
  int *piVar1;
  
  piVar1 = *(int **)(*(int *)off_d2f58 + 0x20);
  while ((param_1 != *piVar1 || ((*(byte *)((int)piVar1 + 0x19) & 0x80) != 0))) {
    piVar1 = (int *)piVar1[8];
    if (piVar1 == *(int **)(off_d2f58 + 4)) {
      fatalerror(s_abfindmemblock___BLOCK_NOT_FOUND_000c3d36 + 2,param_1);
      return (int *)0x0;
    }
  }
  return piVar1;
}


// ================================================================================================
// freemem @ 0x8d2d8 [__cdecl]
// ================================================================================================

void freemem(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = findmemblock(param_1);
  releasememblock(uVar1);
  return;
}


// ================================================================================================
// releasememblock @ 0x8d2f0 [__cdecl]
// ================================================================================================

void releasememblock(undefined4 param_1)

{
  memman_lock(dword_edab0);
  releasemem(param_1);
  memman_unlock(dword_edab0);
  return;
}


// ================================================================================================
// releasemem @ 0x8d31c [__cdecl]
// ================================================================================================

void releasemem(int param_1)

{
  int iVar1;
  
  if ((*(byte *)(param_1 + 0x19) & 0x80) == 0) {
    iVar1 = *(int *)(param_1 + 0x20);
    *(int *)(*(int *)(param_1 + 0x24) + 0x20) = iVar1;
    *(undefined4 *)(iVar1 + 0x24) = *(undefined4 *)(param_1 + 0x24);
    sub_8db78(param_1);
  }
  return;
}


// ================================================================================================
// sub_8d344 @ 0x8d344 [__cdecl]
// ================================================================================================

void sub_8d344(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = findmemblock(param_1);
  sub_8d35c(uVar1);
  return;
}


// ================================================================================================
// sub_8d35c @ 0x8d35c [__cdecl]
// ================================================================================================

void sub_8d35c(int param_1)

{
  byte bVar1;
  int iVar2;
  
  memman_lock(dword_edab0);
  iVar2 = *(int *)(param_1 + 0x20);
  bVar1 = *(byte *)(iVar2 + 0x18);
  while ((bVar1 & 0x20) == 0) {
    iVar2 = *(int *)(iVar2 + 0x20);
    releasemem(*(undefined4 *)(iVar2 + 0x24));
    bVar1 = *(byte *)(iVar2 + 0x18);
  }
  memman_unlock(dword_edab0);
  return;
}


// ================================================================================================
// sub_8d3a0 @ 0x8d3a0 [__watcall]
// ================================================================================================

undefined4 __watcall sub_8d3a0(void)

{
  undefined4 uVar1;
  
  memman_lock(dword_edab0);
  uVar1 = sub_8d3d4();
  memman_unlock(dword_edab0);
  return uVar1;
}


// ================================================================================================
// sub_8d3d4 @ 0x8d3d4 [__watcall]
// ================================================================================================

uint __watcall sub_8d3d4(void)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint in_stack_00000004;
  
  iVar3 = (int)(in_stack_00000004 & 0x700) >> 8;
  in_stack_00000004 = in_stack_00000004 & 7;
  uVar5 = 0;
  iVar2 = 0;
  uVar1 = *(uint *)((&dword_eda08)[iVar3 * 5] + 0x20);
  do {
    if (((*(byte *)(uVar1 + 0x18) & 8) != 0) &&
       ((uVar4 = *(uint *)(uVar1 + 0x18) & 7, in_stack_00000004 < uVar4 ||
        ((uVar4 == in_stack_00000004 && (iVar2 <= dword_d2f64 - *(int *)(uVar1 + 0x1c))))))) {
      in_stack_00000004 = *(uint *)(uVar1 + 0x18) & 7;
      iVar2 = dword_d2f64 - *(int *)(uVar1 + 0x1c);
      uVar5 = uVar1;
    }
    uVar1 = *(uint *)(uVar1 + 0x20);
  } while (uVar1 != (&dword_eda0c)[iVar3 * 5]);
  if (uVar5 == 0) {
    uVar1 = uVar1 ^ (&dword_eda0c)[iVar3 * 5];
  }
  else {
    releasemem(uVar5);
    uVar1 = 1;
  }
  return uVar1;
}


// ================================================================================================
// sub_8d468 @ 0x8d468 [__watcall]
// ================================================================================================

void __watcall sub_8d468(void)

{
  undefined4 uVar1;
  undefined4 in_stack_00000004;
  
  uVar1 = findmemblock(in_stack_00000004,1);
  sub_8d4b0(uVar1);
  return;
}


// ================================================================================================
// sub_8d484 @ 0x8d484 [__cdecl]
// ================================================================================================

void sub_8d484(undefined4 param_1)

{
  sub_8d4b0(param_1,1);
  return;
}


// ================================================================================================
// sub_8d494 @ 0x8d494 [__cdecl]
// ================================================================================================

void sub_8d494(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  uVar1 = findmemblock(param_1,param_2);
  sub_8d4b0(uVar1);
  return;
}


// ================================================================================================
// sub_8d4b0 @ 0x8d4b0 [__cdecl]
// ================================================================================================

int sub_8d4b0(int param_1,uint param_2)

{
  memman_lock(dword_edab0);
  *(uint *)(param_1 + 0x18) = param_2 | *(uint *)(param_1 + 0x18) & 0xfffffff0 | 8;
  memman_unlock(dword_edab0);
  return param_1;
}


// ================================================================================================
// sub_8d4e8 @ 0x8d4e8 [__cdecl]
// ================================================================================================

int sub_8d4e8(undefined4 param_1,uint param_2)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = (int)(param_2 & 0x700) >> 8;
  uVar1 = sub_8e44c(param_1);
  iVar4 = (&dword_eda08)[iVar3 * 5];
  if (iVar4 != (&dword_eda0c)[iVar3 * 5]) {
    do {
      iVar2 = sub_8e3f8(uVar1,iVar4 + 4,0xc);
      if (iVar2 == 0) {
        return iVar4;
      }
      iVar4 = *(int *)(iVar4 + 0x20);
    } while (iVar4 != (&dword_eda0c)[iVar3 * 5]);
  }
  return 0;
}


// ================================================================================================
// sub_8d548 @ 0x8d548 [__watcall]
// ================================================================================================

void __watcall sub_8d548(void)

{
  undefined4 in_stack_00000004;
  
  sub_8d4e8(in_stack_00000004,0);
  return;
}


// ================================================================================================
// sub_8d558 @ 0x8d558 [__watcall]
// ================================================================================================

int __watcall sub_8d558(void)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 in_stack_00000004;
  uint in_stack_00000008;
  
  iVar3 = (int)(in_stack_00000008 & 0x700) >> 8;
  uVar1 = sub_8e44c(in_stack_00000004);
  iVar4 = (&dword_eda08)[iVar3 * 5];
  if (iVar4 != (&dword_eda0c)[iVar3 * 5]) {
    do {
      iVar2 = sub_8e3f8(uVar1,iVar4 + 4,0xc);
      if ((iVar2 == 0) && ((*(byte *)(iVar4 + 0x18) & 8) != 0)) {
        return iVar4;
      }
      iVar4 = *(int *)(iVar4 + 0x20);
    } while (iVar4 != (&dword_eda0c)[iVar3 * 5]);
  }
  return 0;
}


// ================================================================================================
// sub_8d5c0 @ 0x8d5c0 [__watcall]
// ================================================================================================

void __watcall sub_8d5c0(void)

{
  sub_8d558();
  return;
}


// ================================================================================================
// sub_8d5d0 @ 0x8d5d0 [__watcall]
// ================================================================================================

undefined4 __watcall sub_8d5d0(void)

{
  undefined4 uVar1;
  undefined4 in_stack_00000004;
  
  memman_lock(dword_edab0);
  uVar1 = sub_8d604(in_stack_00000004);
  memman_unlock(dword_edab0);
  return uVar1;
}


// ================================================================================================
// sub_8d604 @ 0x8d604 [__cdecl]
// ================================================================================================

undefined4 sub_8d604(uint param_1)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined local_20 [12];
  undefined local_14;
  undefined4 *local_10;
  
  iVar2 = (int)(param_1 & 0x700) >> 8;
  if ((&DAT_000eda18)[iVar2 * 5] == 0) {
    uVar1 = sub_8d3d4();
  }
  else {
    param_1 = param_1 & 7;
    puVar5 = (undefined4 *)0x0;
    iVar3 = 0;
    puVar4 = *(undefined4 **)((&dword_eda08)[iVar2 * 5] + 0x20);
    do {
      if ((*(byte *)(puVar4 + 6) & 8) != 0) {
        if ((param_1 < (puVar4[6] & 7)) ||
           (((puVar4[6] & 7) == param_1 && (iVar3 <= dword_d2f64 - puVar4[7])))) {
          param_1 = puVar4[6] & 7;
          iVar3 = dword_d2f64 - puVar4[7];
          puVar5 = puVar4;
        }
      }
      puVar4 = (undefined4 *)puVar4[8];
    } while (puVar4 != (undefined4 *)(&dword_eda0c)[iVar2 * 5]);
    if (puVar5 != (undefined4 *)0x0) {
      iVar2 = 0;
      do {
        local_20[iVar2] = *(undefined *)(puVar4 + 1);
        puVar4 = (undefined4 *)((int)puVar4 + 1);
        iVar2 = iVar2 + 1;
      } while (iVar2 < 0xc);
      local_14 = 0;
      do {
        local_10 = (undefined4 *)reservemem();
        if (local_10 != (undefined4 *)0x0) break;
        iVar2 = sub_8d604(param_1);
      } while (iVar2 != 0);
      if (local_10 != (undefined4 *)0x0) {
        sub_b3abc(*puVar5,*local_10,puVar5[5]);
        releasemem(puVar5);
        return 1;
      }
    }
    uVar1 = 0;
  }
  return uVar1;
}


// ================================================================================================
// sub_8d714 @ 0x8d714 [__watcall]
// ================================================================================================

undefined4 * __watcall sub_8d714(void)

{
  undefined4 *puVar1;
  undefined4 in_stack_00000004;
  
  puVar1 = (undefined4 *)find_loaded_file(in_stack_00000004);
  if (puVar1 != (undefined4 *)0x0) {
    puVar1 = (undefined4 *)*puVar1;
  }
  return puVar1;
}


// ================================================================================================
// find_loaded_file @ 0x8d728 [__cdecl]
// ================================================================================================

undefined4 * find_loaded_file(void)

{
  byte bVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  uint uVar5;
  
  puVar3 = (undefined4 *)sub_8d5c0();
  uVar2 = uRam00000018;
  if (puVar3 == (undefined4 *)0x0) {
    uVar5 = *(uint *)(off_d2f58 + 0x10);
    do {
      puVar3 = (undefined4 *)sub_8d558();
      if (puVar3 != (undefined4 *)0x0) {
        *(byte *)(puVar3 + 6) = *(byte *)(puVar3 + 6) & 0xf7;
        puVar4 = (undefined4 *)reservemem();
        puVar3[6] = uVar2;
        sub_b3abc(*puVar3,*puVar4,puVar3[5]);
        return puVar4;
      }
      uVar5 = (&DAT_000eda18)[((int)(uVar5 & 0x700) >> 8) * 5];
      puVar3 = (undefined4 *)0x0;
    } while (uVar5 != 0);
  }
  else {
    bVar1 = *(byte *)(puVar3 + 6);
    *(byte *)(puVar3 + 6) = bVar1 & 0xf7;
    if ((bVar1 & 0x10) == 0) {
      puVar4 = (undefined4 *)reservemem();
      if (puVar4 != (undefined4 *)0x0) {
        sub_b3abc(*puVar3,*puVar4,puVar3[5]);
        releasememblock(puVar3);
        puVar3 = puVar4;
      }
    }
  }
  return puVar3;
}


// ================================================================================================
// sub_8d80c @ 0x8d80c [__watcall]
// ================================================================================================

void __watcall sub_8d80c(void)

{
  memman_lock(dword_edab0);
  sub_8d844(*(undefined4 *)(off_d2f58 + 4),*(undefined4 *)off_d2f58);
  memman_unlock(dword_edab0);
  return;
}


// ================================================================================================
// sub_8d844 @ 0x8d844 [__cdecl]
// ================================================================================================

undefined4 sub_8d844(uint *param_1,uint *param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint *puVar5;
  uint *puVar6;
  undefined4 local_14;
  
  local_14 = 0;
  uVar2 = *param_1;
  puVar5 = (uint *)param_1[9];
  puVar6 = puVar5;
  do {
    iVar3 = 0;
    while( true ) {
      uVar1 = *puVar6;
      uVar4 = puVar6[4] + uVar1;
      if (uVar4 < uVar2) break;
      if (puVar6 == param_2) goto LAB_0008d87f;
      puVar6 = (uint *)puVar6[9];
      uVar2 = uVar1;
    }
    iVar3 = uVar2 - uVar4;
    uVar2 = uVar4;
LAB_0008d87f:
    if (iVar3 == 0) {
      return local_14;
    }
    for (; ((*(byte *)(puVar5 + 6) & 0x18) == 0 || (uVar1 = *puVar5, uVar2 < uVar1));
        puVar5 = (uint *)puVar5[9]) {
      if (puVar5 == param_2) {
        return local_14;
      }
    }
    if (uVar2 == puVar5[4] + uVar1) {
      uVar2 = (uVar2 + iVar3) - puVar5[4];
      sub_b3abc(uVar1,uVar2,puVar5[4]);
      *puVar5 = uVar2;
      local_14 = 1;
    }
    else if (iVar3 < (int)puVar5[4]) {
      uVar2 = *puVar6;
    }
    else {
      uVar2 = (uVar2 + iVar3) - puVar5[4];
      sub_b3abc(uVar1,uVar2,puVar5[4]);
      *puVar5 = uVar2;
      uVar2 = puVar5[8];
      *(uint *)(puVar5[9] + 0x20) = uVar2;
      *(uint *)(uVar2 + 0x24) = puVar5[9];
      puVar5[8] = puVar6[8];
      puVar5[9] = (uint)puVar6;
      *(uint **)(puVar6[8] + 0x24) = puVar5;
      puVar6[8] = (uint)puVar5;
      uVar2 = *puVar5;
      local_14 = 1;
    }
  } while( true );
}


// ================================================================================================
// sub_8d958 @ 0x8d958 [__watcall]
// ================================================================================================

void __watcall sub_8d958(void)

{
  memman_lock(dword_edab0);
  sub_8d990(*(undefined4 *)off_d2f58,*(undefined4 *)(off_d2f58 + 4));
  memman_unlock(dword_edab0);
  return;
}


// ================================================================================================
// sub_8d990 @ 0x8d990 [__cdecl]
// ================================================================================================

undefined4 sub_8d990(uint *param_1,uint *param_2)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  uint *puVar5;
  uint *puVar6;
  
  uVar3 = 0;
  uVar4 = *param_1;
  puVar5 = (uint *)param_1[8];
  puVar6 = puVar5;
  if (*puVar5 <= uVar4) goto LAB_0008d9ac;
LAB_0008d9a6:
  iVar2 = *puVar5 - uVar4;
LAB_0008d9c0:
  if (iVar2 == 0) {
    return uVar3;
  }
  while( true ) {
    while( true ) {
      while( true ) {
        for (; ((*(byte *)(puVar6 + 6) & 0x18) == 0 || (uVar1 = *puVar6, uVar1 < uVar4));
            puVar6 = (uint *)puVar6[8]) {
          if (puVar6 == param_2) {
            return uVar3;
          }
        }
        if (puVar6 != puVar5) break;
        sub_b3abc(uVar1,uVar4,puVar5[4]);
        *puVar5 = uVar4;
        uVar4 = uVar4 + puVar5[4];
        uVar3 = 1;
        if (*puVar5 <= uVar4) goto LAB_0008d9ac;
        iVar2 = *puVar5 - uVar4;
        if (iVar2 == 0) {
          return 1;
        }
      }
      if ((int)puVar6[4] <= iVar2) break;
      uVar4 = *puVar5 + puVar5[4];
      if (*puVar5 <= uVar4) goto LAB_0008d9ac;
      iVar2 = *puVar5 - uVar4;
      if (iVar2 == 0) {
        return uVar3;
      }
    }
    sub_b3abc(uVar1,uVar4,puVar6[4]);
    *puVar6 = uVar4;
    uVar1 = puVar6[8];
    *(uint *)(puVar6[9] + 0x20) = uVar1;
    *(uint *)(uVar1 + 0x24) = puVar6[9];
    puVar6[8] = (uint)puVar5;
    uVar1 = puVar5[9];
    puVar6[9] = uVar1;
    *(uint **)(uVar1 + 0x20) = puVar6;
    puVar5[9] = (uint)puVar6;
    uVar4 = uVar4 + puVar6[4];
    uVar3 = 1;
    if (*puVar5 <= uVar4) break;
    iVar2 = *puVar5 - uVar4;
    if (iVar2 == 0) {
      return 1;
    }
  }
LAB_0008d9ac:
  do {
    iVar2 = 0;
    if (puVar5 == param_2) goto LAB_0008d9c0;
    uVar4 = *puVar5 + puVar5[4];
    puVar5 = (uint *)puVar5[8];
    if (uVar4 < *puVar5) goto LAB_0008d9a6;
  } while( true );
}


// ================================================================================================
// sub_8da98 @ 0x8da98 [__watcall]
// ================================================================================================

undefined8 __watcall sub_8da98(undefined4 param_1,undefined4 unaff_EDX)

{
  int iVar1;
  
  iVar1 = sub_8dae4();
  if (iVar1 < dword_edab4) {
    dword_edab4 = iVar1;
  }
  return CONCAT44(unaff_EDX,dword_edab4);
}


// ================================================================================================
// sub_8dab8 @ 0x8dab8 [__watcall]
// ================================================================================================

undefined4 __watcall sub_8dab8(void)

{
  undefined4 uVar1;
  
  memman_lock(dword_edab0);
  uVar1 = sub_8dae4();
  memman_unlock(dword_edab0);
  return uVar1;
}


// ================================================================================================
// sub_8dae4 @ 0x8dae4 [__watcall]
// ================================================================================================

int __watcall sub_8dae4(void)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  
  sub_8d844(*(undefined4 *)(off_d2f58 + 4),*(undefined4 *)off_d2f58);
  iVar3 = 0;
  piVar1 = (int *)(*(int **)off_d2f58)[8];
  piVar5 = *(int **)off_d2f58;
  do {
    piVar2 = piVar1;
    iVar4 = (*piVar2 - *piVar5) - piVar5[4];
    if (iVar3 < iVar4) {
      iVar3 = iVar4;
    }
    piVar1 = (int *)piVar2[8];
    piVar5 = piVar2;
  } while ((int *)piVar2[8] != (int *)0x0);
  return iVar3;
}


// ================================================================================================
// sub_8db20 @ 0x8db20 [__watcall]
// ================================================================================================

int __watcall sub_8db20(void)

{
  int iVar1;
  
  iVar1 = sub_8dab8();
  return iVar1 >> 4;
}


// ================================================================================================
// sub_8db2c @ 0x8db2c [__watcall]
// ================================================================================================

int __watcall sub_8db2c(void)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  for (iVar1 = *(int *)off_d2f58; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x20)) {
    if ((*(byte *)(iVar1 + 0x18) & 0x18) == 0) {
      iVar2 = iVar2 + *(int *)(iVar1 + 0x10);
    }
  }
  return iVar2;
}


// ================================================================================================
// sub_8db4c @ 0x8db4c [__cdecl]
// ================================================================================================

void sub_8db4c(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  dword_edaac = param_1;
  iVar2 = 0;
  iVar1 = param_1;
  if (0 < param_2 + -1) {
    do {
      param_1 = iVar1 + 0x28;
      *(int *)(iVar1 + 0x20) = param_1;
      iVar2 = iVar2 + 1;
      iVar1 = param_1;
    } while (iVar2 < param_2 + -1);
  }
  *(undefined4 *)(param_1 + 0x20) = 0;
  return;
}


// ================================================================================================
// sub_8db78 @ 0x8db78 [__cdecl]
// ================================================================================================

void sub_8db78(int param_1)

{
  *(int *)(param_1 + 0x20) = dword_edaac;
  dword_edaac = param_1;
  return;
}


// ================================================================================================
// getmemblock @ 0x8db8c [__watcall]
// ================================================================================================

void __watcall getmemblock(void)

{
  if (dword_edaac == 0) {
    memman_unlock(dword_edab0);
    fatalerror(s_FLAgetmemblock___NO_MEMORY_BLOCK_000c3d5d + 3);
  }
  dword_edaac = *(undefined4 *)(dword_edaac + 0x20);
  return;
}


// ================================================================================================
// sub_8dbc0 @ 0x8dbc0 [__cdecl]
// ================================================================================================

undefined4 sub_8dbc0(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = findmemblock(param_1);
  return *(undefined4 *)(iVar1 + 0x14);
}


// ================================================================================================
// sub_8dbd4 @ 0x8dbd4 [__cdecl]
// ================================================================================================

undefined4 sub_8dbd4(undefined4 *param_1)

{
  return *param_1;
}


// ================================================================================================
// sub_8dbdc @ 0x8dbdc [__cdecl]
// ================================================================================================

undefined4 sub_8dbdc(int param_1)

{
  return *(undefined4 *)(param_1 + 0x14);
}


// ================================================================================================
// sub_8dbe4 @ 0x8dbe4 [__cdecl]
// ================================================================================================

int sub_8dbe4(int param_1)

{
  return param_1 + 4;
}


// ================================================================================================
// sub_8dbec @ 0x8dbec [__cdecl]
// ================================================================================================

undefined4 sub_8dbec(int param_1)

{
  return *(undefined4 *)(param_1 + 0x18);
}


// ================================================================================================
// _dos_getdrive @ 0x8dbf4 [__watcall]
// ================================================================================================

int __watcall _dos_getdrive(uint *param_1)

{
  code *pcVar1;
  undefined4 uVar2;
  ushort uVar3;
  
  pcVar1 = (code *)swi(0x21);
  uVar2 = (*pcVar1)();
  uVar3 = (ushort)((uint)uVar2 >> 0x10);
  *param_1 = CONCAT22(uVar3,(short)uVar2 + 1) & 0xffff00ff;
  return (uint)uVar3 << 0x10;
}


// ================================================================================================
// _dos_setdrive @ 0x8dc08 [__watcall]
// ================================================================================================

undefined4 __watcall _dos_setdrive(undefined4 param_1,undefined4 *unaff_EDX)

{
  code *pcVar1;
  undefined4 uVar2;
  
  pcVar1 = (code *)swi(0x21);
  uVar2 = (*pcVar1)();
  *unaff_EDX = CONCAT22((short)((uint)uVar2 >> 0x10),(ushort)(byte)uVar2);
  return 0;
}


// ================================================================================================
// printf @ 0x8dc1c [__cdecl]
// ================================================================================================

int printf(char *__format,...)

{
  int iVar1;
  undefined *local_c [2];
  
  local_c[0] = &stack0x00000008;
  iVar1 = vfprintf((FILE *)&unk_d4d32,__format,local_c);
  return iVar1;
}


// ================================================================================================
// unk_8dc3e @ 0x8dc3e
// ================================================================================================

void unk_8dc3e(void)

{
  return;
}


// ================================================================================================
// exit @ 0x8dc3f [__watcall] noreturn
// ================================================================================================

void __watcall exit(int __status)

{
  int __status_00;
  
  (*(code *)funcptr_d2f68)();
  (*(code *)funcptr_d2f6c)();
                    /* WARNING: Subroutine does not return */
  _exit(__status_00);
}


// ================================================================================================
// sub_8dc55 @ 0x8dc55 [__watcall]
// ================================================================================================

void __watcall sub_8dc55(void)

{
  return;
}


// ================================================================================================
// _exit @ 0x8dc57 [__watcall] noreturn
// ================================================================================================

void __watcall _exit(int __status)

{
  undefined4 extraout_EDX;
  
  (*(code *)funcptr_d2f6c)();
  (*(code *)funcptr_d2f70)();
                    /* WARNING: Subroutine does not return */
  sub_90265(extraout_EDX);
}


// ================================================================================================
// _dos_getdiskfree @ 0x8dc6e [__watcall]
// ================================================================================================

undefined4 __watcall
_dos_getdiskfree(undefined4 param_1,undefined2 *unaff_EDX,undefined2 unaff_BX,undefined4 unaff_ECX)

{
  code *pcVar1;
  short sVar2;
  undefined4 uVar3;
  undefined2 extraout_CX;
  undefined2 extraout_DX;
  
  pcVar1 = (code *)swi(0x21);
  sVar2 = (*pcVar1)(unaff_ECX);
  if (sVar2 == -1) {
    uVar3 = sub_9879d();
  }
  else {
    *unaff_EDX = extraout_DX;
    unaff_EDX[1] = unaff_BX;
    unaff_EDX[2] = sVar2;
    unaff_EDX[3] = extraout_CX;
    uVar3 = 0;
  }
  return uVar3;
}


// ================================================================================================
// int386 @ 0x8dc9c [__watcall]
// ================================================================================================

void __watcall int386(undefined4 param_1,undefined4 param_2,undefined4 unaff_EBX)

{
  undefined4 extraout_EDX;
  undefined auStack_10 [12];
  
  segread(auStack_10);
  int386x(param_1,extraout_EDX,unaff_EBX,auStack_10);
  return;
}


// ================================================================================================
// sub_8dcc0 @ 0x8dcc0 [__watcall]
// ================================================================================================

undefined4 __watcall sub_8dcc0(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 extraout_EDX;
  undefined8 uVar3;
  
  iVar2 = 0x4000000;
  while( true ) {
    uVar3 = sub_91984(iVar2);
    iVar2 = (int)uVar3;
    if (iVar2 != 0) break;
    iVar2 = (int)((longlong)uVar3 >> 0x21);
  }
  if (iVar2 == 0) {
    return 0;
  }
  sub_98801(iVar2,0x4000000);
  uVar1 = sub_98a2b(iVar2);
  sub_91a67(iVar2,uVar1);
  return extraout_EDX;
}


// ================================================================================================
// initmemman @ 0x8dcf8 [__cdecl]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void initmemman(int param_1,uint param_2,int param_3)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  int unaff_EBP;
  int iVar4;
  undefined8 uVar5;
  ushort local_4c [2];
  uint local_48;
  ushort local_40;
  undefined2 local_30 [2];
  ushort local_2c;
  undefined2 local_24;
  uint local_14;
  int local_10;
  
  dword_edab0 = sub_986b0();
  memman_lock(dword_edab0);
  sub_b3f50();
  uVar2 = sub_8dcc0();
  if ((0 < (int)param_2) && ((int)param_2 < (int)uVar2)) {
    uVar2 = param_2;
  }
  uVar5 = sub_91984(uVar2 & 0xfffffff0);
  dword_d2f80 = (int)uVar5;
  _dword_d2f7c = dword_d2f80 + (int)((ulonglong)uVar5 >> 0x20);
  if (dword_d2f60 == (int *)0x0) {
    dword_d2f60 = &unk_edf04;
  }
  if (dword_d2f5c < 0xcc) {
    fatalerror(aInitmemmanINSUFFICIENTRO);
  }
  piVar1 = dword_d2f60;
  dword_edaa8 = dword_d2f60 + dword_d2f5c;
  *dword_d2f60 = dword_d2f5c + -2;
  piVar1[1] = 0;
  local_10 = param_1 * 0x28;
  sub_8db4c(dword_d2f80,param_1);
  sub_8c990(0,dword_d2f80 + local_10,_dword_d2f7c,8,8,0);
  if (param_2 == 0) {
    if (param_3 < 16000) {
      param_3 = 16000;
    }
    local_30[0] = 0x100;
    local_2c = 0xa000;
    int386(0x31,local_30,local_4c);
    local_30[0] = 0x100;
    iVar4 = (local_48 & 0xffff) * 0x10 - param_3;
    if (0 < iVar4) {
      local_2c = (ushort)local_48 - (short)(param_3 + 0xf >> 4);
      int386(0x31,local_30,local_4c);
      unaff_EBP = (uint)local_4c[0] << 4;
      iVar4 = (uint)local_2c << 4;
      if (param_3 != 0) {
        local_30[0] = 0x100;
        local_2c = 0xa000;
        int386(0x31,local_30,local_4c);
        local_30[0] = 0x100;
        local_2c = (ushort)local_48;
        int386(0x31,local_30,local_4c);
        local_14 = (uint)local_40;
      }
    }
    while( true ) {
      iVar3 = sub_8dcc0();
      if (iVar3 < 10000) break;
      uVar5 = sub_91984(iVar3,iVar3);
      sub_8caf4(0,(int)uVar5,(int)((ulonglong)uVar5 >> 0x20) + (int)uVar5);
    }
    if (0 < iVar4) {
      sub_8caf4(0,unaff_EBP,iVar4 + unaff_EBP);
      if (param_3 != 0) {
        local_30[0] = 0x101;
        local_24 = (undefined2)local_14;
        int386(0x31,local_30,local_4c);
      }
    }
  }
  memman_unlock(dword_edab0);
  dword_edab4 = sub_8dab8();
  return;
}


// ================================================================================================
// sub_8df28 @ 0x8df28 [__watcall]
// ================================================================================================

void __watcall sub_8df28(void)

{
  undefined4 in_stack_00000004;
  
  initmemman(in_stack_00000004,0,0);
  return;
}


// ================================================================================================
// sub_8df3c @ 0x8df3c [__watcall]
// ================================================================================================

void __watcall sub_8df3c(void)

{
  undefined4 in_stack_00000004;
  undefined4 in_stack_00000008;
  
  initmemman(in_stack_00000004,in_stack_00000008,0);
  return;
}


// ================================================================================================
// initmem @ 0x8df54 [__cdecl]
// ================================================================================================

void initmem(undefined4 param_1,undefined4 param_2)

{
  initmemman(param_1,0,param_2);
  return;
}


// ================================================================================================
// load_eavesa @ 0x8df70 [__watcall]
// ================================================================================================

undefined8 __watcall load_eavesa(undefined4 param_1,undefined4 unaff_EDX)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  
  pcVar3 = aEavesaCom;
  iVar1 = sub_98a40(aEavesaCom);
  if (iVar1 == 0) {
    pcVar3 = s_Mc__util_eavesa_com_000c3dbf + 1;
  }
  dword_edcb8 = sub_98a81(0,pcVar3,pcVar3,0);
  if (dword_edcb8 == -1) {
    fatalerror(s_linitgraphics___EAVESA_COM_REQUI_000c3dd3 + 1);
  }
  iVar1 = loadfile(aCEavesaDat,0);
  remove(aCEavesaDat);
  iVar2 = sub_8dbc0(iVar1);
  if (iVar2 != 0x41c) {
    fatalerror(s_t_initgraphics___NEW_VERSION_OF_E_000c3e36 + 2);
  }
  dword_edcb8 = 0;
  iVar2 = sub_98a9f(iVar1,&aVESA,4);
  if (iVar2 == 0) {
    dword_edcb8 = 1;
  }
  sub_b3abc(iVar1,&unk_edbb8,0x100);
  sub_b3abc(iVar1 + 0x100,&unk_edab8,0x100);
  sub_b3abc(iVar1 + 0x400,&byte_edcc0,0x1b);
  if (word_edbca < 5) {
    sub_b3fc2(&byte_edcc1,0x1a);
  }
  freemem(iVar1);
  return CONCAT44(unaff_EDX,dword_edcb8);
}


// ================================================================================================
// initgraphics @ 0x8e080 [__cdecl]
// ================================================================================================

void initgraphics(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int unaff_ESI;
  int iVar5;
  short unaff_DI;
  char local_14 [8];
  
  if (dword_d2f80 == 0) {
    fatalerror(s_cs_initgraphics___INITMEMMAN_REQ_000c3e99 + 3);
  }
  if (dword_d3024 == 0) {
    sub_b3e98();
  }
  if (dword_d2f88 == 0) {
    load_eavesa();
    dword_d2f88 = 1;
  }
  if (param_1 == 0) {
    param_1 = 0x280;
  }
  if (param_2 == 0) {
    param_2 = 0x1e0;
  }
  if ((param_1 == 0x140) && (param_2 == 200)) {
    unaff_ESI = -1;
  }
  else if ((param_1 == 0x280) && (param_2 == 400)) {
    unaff_ESI = 0;
  }
  else if ((param_1 == 0x280) && (param_2 == 0x1e0)) {
    unaff_ESI = 1;
  }
  else if ((param_1 == 800) && (param_2 == 600)) {
    unaff_ESI = 3;
  }
  else if ((param_1 == 0x400) && (param_2 == 0x300)) {
    unaff_ESI = 5;
  }
  else if ((param_1 == 0x500) && (param_2 == 0x400)) {
    unaff_ESI = 7;
  }
  else if ((param_1 == -1) && (param_2 == -1)) {
    unaff_ESI = 5;
  }
  else {
    fatalerror(aInitgraphicsINVALIDSCREE,param_1,param_2);
  }
  if (-1 < unaff_ESI) {
    if (dword_edcb8 == 0) {
      fatalerror(aVESAVideoBiosDriverRequi);
    }
    dword_d4f50 = 0;
    iVar3 = (int)dword_edaba >> 0x10;
    if (iVar3 != 0) {
      for (; iVar3 < 0x40; iVar3 = iVar3 * 2) {
        dword_d4f50 = dword_d4f50 + 1;
      }
    }
    dword_d4f4c = (uint)((dword_edaba & 0x100) != 0);
    _memset_fill(local_14,0,iVar3,8);
    local_14[0] = byte_edcc0;
    local_14[1] = byte_edcc1;
    local_14[3] = byte_edcc3;
    local_14[5] = byte_edcc5;
    local_14[7] = byte_edcc7;
    do {
      unaff_DI = 0;
      if (local_14[unaff_ESI] != '\0') {
        unaff_DI = sub_b5ea7();
      }
      if (unaff_DI != 0x4f) {
        local_14[unaff_ESI] = '\0';
        if (unaff_ESI == 1) {
          unaff_ESI = 0;
        }
        for (; (unaff_ESI < 8 && (local_14[unaff_ESI] == '\0')); unaff_ESI = unaff_ESI + 1) {
        }
        if (7 < unaff_ESI) {
          unaff_ESI = 7;
          do {
            if (local_14[unaff_ESI] != '\0') break;
            unaff_ESI = unaff_ESI + -1;
          } while (-1 < unaff_ESI);
        }
      }
    } while ((-1 < unaff_ESI) && (unaff_DI != 0x4f));
  }
  if ((unaff_ESI < 0) || (unaff_DI != 0x4f)) {
    if (dword_d3024 == 8) {
      sub_b5e00(0);
    }
    unaff_ESI = 0x13;
    sub_b5eb8(0x13);
    iVar3 = 0x140;
    dword_d3048 = 200;
    dword_d3024 = 5;
  }
  else {
    iVar3 = *(int *)(&unk_d2f8c + unaff_ESI * 8);
    dword_d3048 = *(int *)(&unk_d2f90 + unaff_ESI * 8);
    dword_d3024 = 8;
  }
  dword_d3054 = iVar3 - dword_d304c;
  dword_d3058 = dword_d3048 - dword_d3050;
  dword_d30dc = 0;
  dword_d30e0 = 0;
  dword_d30ec = 0;
  dword_d30f8 = (uint)(unaff_ESI != 0x13);
  iVar4 = 0;
  dword_d3044 = iVar3;
  dword_d30d4 = iVar3;
  dword_d30d8 = dword_d3048;
  dword_d30e4 = iVar3;
  dword_d30e8 = dword_d3048;
  dword_d30f0 = iVar3;
  dword_d30f4 = iVar3;
  if (0 < dword_d3048) {
    iVar5 = 0;
    iVar1 = dword_d3048 * 4;
    do {
      *(int *)((int)&unk_d3104 + iVar5) = iVar4;
      iVar4 = iVar4 + iVar3;
      iVar5 = iVar5 + 4;
    } while (iVar5 < iVar1);
  }
  iVar4 = 0;
  iVar1 = 0x10000;
  do {
    iVar5 = iVar1 / iVar3;
    iVar2 = iVar1 % iVar3;
    *(int *)((int)&unk_d4108 + iVar4) = iVar5;
    iVar4 = iVar4 + 4;
    iVar1 = iVar1 + 0x10000;
  } while (iVar4 != 0x50);
  setdefaultscreen(iVar5,iVar2);
  dword_edcbc = &dword_d30a4;
  return;
}


// ================================================================================================
// sub_8e3c0 @ 0x8e3c0 [__watcall]
// ================================================================================================

void __watcall sub_8e3c0(void)

{
  return;
}


// ================================================================================================
// sub_8e3c4 @ 0x8e3c4 [__cdecl]
// ================================================================================================

undefined4 sub_8e3c4(undefined4 param_1)

{
  return param_1;
}


// ================================================================================================
// sub_8e3cc @ 0x8e3cc [__cdecl]
// ================================================================================================

undefined4 sub_8e3cc(undefined4 param_1)

{
  return param_1;
}


// ================================================================================================
// sub_8e3d4 @ 0x8e3d4 [__cdecl]
// ================================================================================================

undefined4 sub_8e3d4(undefined4 param_1)

{
  return param_1;
}


// ================================================================================================
// sub_8e3dc @ 0x8e3dc [__cdecl]
// ================================================================================================

undefined4 sub_8e3dc(undefined4 param_1)

{
  return param_1;
}


// ================================================================================================
// sub_8e3e4 @ 0x8e3e4 [__cdecl]
// ================================================================================================

void sub_8e3e4(char *param_1,char *param_2,size_t param_3)

{
  strncpy(param_1,param_2,param_3);
  return;
}


// ================================================================================================
// sub_8e3f8 @ 0x8e3f8 [__cdecl]
// ================================================================================================

void sub_8e3f8(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  sub_98a9f(param_1,param_2,param_3);
  return;
}


// ================================================================================================
// sub_8e40c @ 0x8e40c [__cdecl]
// ================================================================================================

void sub_8e40c(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  sub_b3abc(param_2,param_1,param_3);
  return;
}


// ================================================================================================
// sub_8e424 @ 0x8e424 [__cdecl]
// ================================================================================================

char * sub_8e424(char *param_1)

{
  char cVar1;
  char *pcVar2;
  
  cVar1 = *param_1;
  pcVar2 = param_1;
  while (cVar1 != '\0') {
    cVar1 = *param_1;
    if (((cVar1 == '\\') || (cVar1 == ':')) || (cVar1 == '/')) {
      pcVar2 = param_1 + 1;
    }
    param_1 = param_1 + 1;
    cVar1 = *param_1;
  }
  return pcVar2;
}


// ================================================================================================
// sub_8e44c @ 0x8e44c [__cdecl]
// ================================================================================================

void sub_8e44c(undefined4 param_1)

{
  sub_8e424(param_1);
  return;
}


// ================================================================================================
// sub_8e45c @ 0x8e45c [__watcall]
// ================================================================================================

undefined8 __watcall sub_8e45c(void)

{
  int iVar1;
  int extraout_EDX;
  undefined *puVar2;
  byte in_AF;
  byte in_TF;
  byte in_IF;
  byte bVar3;
  bool bVar4;
  byte in_NT;
  byte in_AC;
  byte in_VIF;
  byte in_VIP;
  byte in_ID;
  undefined auStack_38 [4];
  uint uStack_34;
  undefined auStack_30 [16];
  
  puVar2 = auStack_30;
  bVar3 = 0;
  uStack_34 = 0x8e46b;
  sub_902a0();
  dword_d2fdc = dword_d2fdc + 1;
  iVar1 = 0;
  do {
    if (*(int *)((int)&dword_edcdc + iVar1) != 0) {
      uStack_34 = 0x8e484;
      (**(code **)((int)&dword_edcdc + iVar1))();
      iVar1 = extraout_EDX;
    }
    iVar1 = iVar1 + 4;
  } while (iVar1 != 0x20);
  if (dword_d2fdc % 5 == 0) {
    bVar4 = SCARRY4(dword_d2fe0,1);
    dword_d2fe0 = dword_d2fe0 + 1;
    uStack_34 = (uint)(in_NT & 1) * 0x4000 | (uint)bVar4 * 0x800 | (uint)(bVar3 & 1) * 0x400 |
                (uint)(in_IF & 1) * 0x200 | (uint)(in_TF & 1) * 0x100 |
                (uint)((int)dword_d2fe0 < 0) * 0x80 | (uint)(dword_d2fe0 == 0) * 0x40 |
                (uint)(in_AF & 1) * 0x10 | (uint)((POPCOUNT(dword_d2fe0 & 0xff) & 1U) == 0) * 4 |
                (uint)(in_ID & 1) * 0x200000 | (uint)(in_VIP & 1) * 0x100000 |
                (uint)(in_VIF & 1) * 0x80000 | (uint)(in_AC & 1) * 0x40000;
    puVar2 = auStack_38;
    (*(code *)&dword_d2fe4)();
  }
  else {
    out(0x20,0x20);
  }
  return CONCAT44(*(undefined4 *)(puVar2 + 0x24),*(undefined4 *)(puVar2 + 0x2c));
}


// ================================================================================================
// addtimer @ 0x8e4c0 [__cdecl]
// ================================================================================================

void addtimer(undefined4 param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = 0;
  iVar3 = iVar2;
  if (dword_edcdc != 0) {
    do {
      iVar2 = iVar3 + 4;
      if (0x1f < iVar2) {
        fatalerror(aAddtimerLISTFULL);
        return;
      }
      piVar1 = (int *)((int)&DAT_000edce0 + iVar3);
      iVar3 = iVar2;
    } while (*piVar1 != 0);
  }
  *(undefined4 *)((int)&dword_edcdc + iVar2) = param_1;
  return;
}


// ================================================================================================
// removetimer @ 0x8e4f8 [__cdecl]
// ================================================================================================

void removetimer(int param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = 0;
  iVar3 = iVar2;
  if (param_1 != dword_edcdc) {
    do {
      iVar2 = iVar3 + 4;
      if (0x1f < iVar2) {
        return;
      }
      piVar1 = (int *)((int)&DAT_000edce0 + iVar3);
      iVar3 = iVar2;
    } while (param_1 != *piVar1);
  }
  *(undefined4 *)((int)&dword_edcdc + iVar2) = 0;
  return;
}


// ================================================================================================
// sub_8e528 @ 0x8e528 [__watcall]
// ================================================================================================

int __watcall sub_8e528(void)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  iVar1 = 0;
  do {
    if (*(int *)((int)&dword_edcdc + iVar1) != 0) {
      iVar2 = iVar2 + 1;
    }
    iVar1 = iVar1 + 4;
  } while (iVar1 != 0x20);
  return iVar2;
}


// ================================================================================================
// sub_8e544 @ 0x8e544 [__watcall]
// ================================================================================================

ulonglong __watcall sub_8e544(undefined4 param_1,undefined4 unaff_EDX)

{
  byte bVar1;
  
  bVar1 = in(0x21);
  out(0x21,bVar1 | 3);
  return CONCAT44(unaff_EDX,(uint)bVar1) | 3;
}


// ================================================================================================
// sub_8e554 @ 0x8e554 [__watcall]
// ================================================================================================

void __watcall
sub_8e554(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  uint uVar1;
  undefined4 extraout_EDX;
  
  if ((dword_d2fe4 != 0) || (word_d2fe8 != 0)) {
    sub_8e544();
    uVar1 = sub_98ac8(8,extraout_EDX,dword_d2fe4,word_d2fe8,unaff_EDX,unaff_ECX,unaff_EBX);
    out(0x40,0);
    out(0x40,0);
    word_d2fe8 = 0;
    dword_d2fe4 = 0;
    sub_8e614(uVar1 & 0xffffff00,0x40);
  }
  return;
}


// ================================================================================================
// inittimer @ 0x8e5ac [__watcall]
// ================================================================================================

ulonglong __watcall inittimer(undefined4 param_1,undefined4 param_2,undefined4 unaff_EBX)

{
  byte bVar1;
  undefined4 extraout_EDX;
  undefined2 in_CS;
  ulonglong uVar2;
  undefined6 uVar3;
  
  uVar2 = _memset_dwords(&dword_edcdc,0,unaff_EBX,8);
  if ((dword_d2fe4 == 0) && (word_d2fe8 == 0)) {
    sub_8e544();
    uVar3 = sub_98af3(8);
    word_d2fe8 = (short)((uint6)uVar3 >> 0x20);
    dword_d2fe4 = (int)uVar3;
    out(0x40,0x9c);
    out(0x40,0x2e);
    sub_98ac8(8,0x40,sub_8e45c,in_CS);
    sub_b3454(sub_8e554);
    bVar1 = in(0x21);
    out(0x21,bVar1 & 0xfc);
    return CONCAT44(extraout_EDX,(uint)bVar1) & 0xfffffffffffffffc;
  }
  return uVar2;
}


// ================================================================================================
// sub_8e614 @ 0x8e614 [__watcall]
// ================================================================================================

ulonglong __watcall sub_8e614(undefined4 param_1,undefined4 unaff_EDX)

{
  byte bVar1;
  
  bVar1 = in(0x21);
  out(0x21,bVar1 & 0xfc);
  return CONCAT44(unaff_EDX,(uint)bVar1) & 0xfffffffffffffffc;
}


// ================================================================================================
// sub_8e624 @ 0x8e624 [__cdecl]
// ================================================================================================

void sub_8e624(undefined4 param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  
  iVar1 = sub_91fa4(param_1,*(int *)(param_2 + 2) >> 0x10);
  local_18 = sub_91fa4(param_1,*(int *)(param_2 + 4) >> 0x10);
  local_2c = param_3;
  local_28 = param_4;
  local_24 = param_3 + iVar1;
  local_20 = param_4;
  local_18 = param_4 + local_18;
  local_14 = param_3;
  local_1c = local_24;
  local_10 = local_18;
  sub_98b30(param_2,&local_2c);
  return;
}


// ================================================================================================
// sub_8e6a8 @ 0x8e6a8 [__cdecl]
// ================================================================================================

void sub_8e6a8(undefined4 param_1,int param_2)

{
  sub_8e624(param_1,param_2,*(int *)(param_2 + 10) >> 0x10,*(int *)(param_2 + 0xc) >> 0x10);
  return;
}


// ================================================================================================
// sub_8e6cc @ 0x8e6cc [__watcall]
// ================================================================================================

void __watcall sub_8e6cc(void)

{
  int iVar1;
  undefined4 in_stack_00000004;
  int in_stack_00000008;
  int in_stack_0000000c;
  int in_stack_00000010;
  
  iVar1 = sub_91fa4(in_stack_00000004,*(int *)(in_stack_00000008 + 6) >> 0x10);
  iVar1 = sub_91fa4(in_stack_00000004,*(int *)(in_stack_00000008 + 6) >> 0x10,
                    in_stack_00000010 - iVar1);
  sub_8e624(in_stack_00000004,in_stack_00000008,in_stack_0000000c - iVar1);
  return;
}


// ================================================================================================
// sub_8e714 @ 0x8e714 [__cdecl]
// ================================================================================================

void sub_8e714(undefined4 param_1,int param_2)

{
  sub_8e624(param_1,param_2,*(int *)(param_2 + 10) >> 0x10,*(int *)(param_2 + 0xc) >> 0x10);
  return;
}


// ================================================================================================
// sub_8e738 @ 0x8e738 [__watcall]
// ================================================================================================

void __watcall sub_8e738(void)

{
  int iVar1;
  undefined4 in_stack_00000004;
  int in_stack_00000008;
  int in_stack_0000000c;
  int in_stack_00000010;
  
  iVar1 = sub_91fa4(in_stack_00000004,*(int *)(in_stack_00000008 + 6) >> 0x10);
  iVar1 = sub_91fa4(in_stack_00000004,*(int *)(in_stack_00000008 + 6) >> 0x10,
                    in_stack_00000010 - iVar1);
  sub_8e624(in_stack_00000004,in_stack_00000008,in_stack_0000000c - iVar1);
  return;
}


// ================================================================================================
// sub_8e780 @ 0x8e780 [__watcall]
// ================================================================================================

void __watcall sub_8e780(void)

{
  undefined4 in_stack_00000004;
  undefined4 in_stack_00000008;
  undefined4 in_stack_0000000c;
  undefined4 in_stack_00000010;
  
  sub_8e624(in_stack_00000004,in_stack_00000008,in_stack_0000000c,in_stack_00000010);
  return;
}


// ================================================================================================
// subwindowdefadr @ 0x8e7a0 [__cdecl]
// ================================================================================================

undefined4 *
subwindowdefadr(undefined4 *param_1,int param_2,int param_3,undefined4 param_4,undefined4 param_5)

{
  undefined4 *puVar1;
  int iVar2;
  
  puVar1 = (undefined4 *)allocmem(aSUBWINDOW,0x30,0);
  sub_b3fc2(puVar1,0x30);
  puVar1[8] = param_4;
  puVar1[4] = param_4;
  puVar1[7] = param_4;
  puVar1[1] = param_5;
  puVar1[5] = param_5;
  *puVar1 = *param_1;
  puVar1[0xb] = param_1[0xb];
  iVar2 = sub_98d20(*(int *)(param_1[10] + param_3 * 4) + param_2,*puVar1,param_5);
  puVar1[10] = iVar2;
  if (iVar2 == 0) {
    fatalerror(s_d_subwindowdefadr___OUT_OF_ROW_S_000c3f7e + 2);
  }
  return puVar1;
}


// ================================================================================================
// sub_8e81c @ 0x8e81c [__watcall]
// ================================================================================================

void __watcall sub_8e81c(void)

{
  undefined4 in_stack_00000004;
  undefined4 in_stack_00000008;
  
  loadfile_auto(in_stack_00000004,in_stack_00000008,0);
  return;
}


// ================================================================================================
// sub_8e823 @ 0x8e823 [__watcall]
// ================================================================================================

void __watcall sub_8e823(void)

{
  undefined4 in_stack_00000004;
  undefined4 in_stack_00000008;
  
  loadfile_auto(in_stack_00000004,in_stack_00000008,1);
  return;
}


// ================================================================================================
// loadshapes @ 0x8e83c [__cdecl]
// ================================================================================================

undefined4 * loadshapes(undefined4 param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)loadfile_auto(param_1,param_2,1);
  if (puVar1 != (undefined4 *)0x0) {
    puVar1 = (undefined4 *)*puVar1;
  }
  return puVar1;
}


// ================================================================================================
// sub_8e846 @ 0x8e846 [__watcall]
// ================================================================================================

undefined4 * __watcall sub_8e846(void)

{
  undefined4 *puVar1;
  undefined4 in_stack_00000004;
  undefined4 in_stack_00000008;
  
  puVar1 = (undefined4 *)loadfile_auto(in_stack_00000004,in_stack_00000008,0);
  if (puVar1 != (undefined4 *)0x0) {
    puVar1 = (undefined4 *)*puVar1;
  }
  return puVar1;
}


// ================================================================================================
// sub_8e84d @ 0x8e84d [__watcall]
// ================================================================================================

undefined4 * __watcall sub_8e84d(void)

{
  undefined4 *puVar1;
  undefined4 in_stack_00000004;
  undefined4 in_stack_00000008;
  undefined4 in_stack_0000000c;
  
  puVar1 = (undefined4 *)loadfile_auto(in_stack_00000004,in_stack_00000008,in_stack_0000000c);
  if (puVar1 != (undefined4 *)0x0) {
    puVar1 = (undefined4 *)*puVar1;
  }
  return puVar1;
}


// ================================================================================================
// loadfile @ 0x8e8a0 [__cdecl]
// ================================================================================================

void loadfile(undefined4 param_1,undefined4 param_2)

{
  loadfile_handle(param_1,param_2,1);
  return;
}


// ================================================================================================
// sub_8e8b8 @ 0x8e8b8 [__cdecl]
// ================================================================================================

void sub_8e8b8(undefined4 param_1,undefined4 param_2)

{
  loadfile_handle(param_1,param_2,0);
  return;
}


// ================================================================================================
// loadfile_handle @ 0x8e8d0 [__cdecl]
// ================================================================================================

undefined4 * loadfile_handle(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)sub_8e920(param_1,param_2,param_3);
  if (puVar1 != (undefined4 *)0x0) {
    puVar1 = (undefined4 *)*puVar1;
  }
  return puVar1;
}


// ================================================================================================
// sub_8e8f0 @ 0x8e8f0 [__watcall]
// ================================================================================================

void __watcall sub_8e8f0(void)

{
  undefined4 in_stack_00000004;
  undefined4 in_stack_00000008;
  
  sub_8e920(in_stack_00000004,in_stack_00000008,1);
  return;
}


// ================================================================================================
// sub_8e908 @ 0x8e908 [__watcall]
// ================================================================================================

void __watcall sub_8e908(void)

{
  undefined4 in_stack_00000004;
  undefined4 in_stack_00000008;
  
  sub_8e920(in_stack_00000004,in_stack_00000008,0);
  return;
}


// ================================================================================================
// sub_8e920 @ 0x8e920 [__cdecl]
// ================================================================================================

undefined4 * sub_8e920(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  undefined4 local_14;
  undefined local_10 [4];
  int local_c;
  
  puVar1 = (undefined4 *)find_loaded_file(param_1);
  if (puVar1 == (undefined4 *)0x0) {
    openhandle(param_1,&local_14,local_10,&local_c,param_3);
    if (local_c == 0) {
      puVar1 = (undefined4 *)0x0;
    }
    else {
      puVar1 = (undefined4 *)reservemem_locked(param_1,local_c,param_2,param_3);
      if (puVar1 == (undefined4 *)0x0) {
        closehandle(local_14);
        return (undefined4 *)0x0;
      }
      sub_b3c74(local_14,*puVar1,local_c);
      closehandle(local_14);
    }
  }
  return puVar1;
}


// ================================================================================================
// settextpos @ 0x8e9c0 [__cdecl]
// ================================================================================================

void settextpos(undefined4 param_1,undefined4 param_2)

{
  dword_d42a8 = param_1;
  dword_d42ac = param_2;
  return;
}


// ================================================================================================
// settextxy @ 0x8e9d4 [__cdecl]
// ================================================================================================

void settextxy(undefined4 param_1,undefined4 param_2)

{
  dword_d42b0 = param_1;
  dword_d42b4 = param_2;
  return;
}


// ================================================================================================
// getfontstate @ 0x8e9e8 [__cdecl]
// ================================================================================================

void getfontstate(undefined4 *param_1)

{
  int iVar1;
  undefined **ppuVar2;
  
  ppuVar2 = &off_d42a4;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *param_1 = *ppuVar2;
    ppuVar2 = ppuVar2 + 1;
    param_1 = param_1 + 1;
  }
  return;
}


// ================================================================================================
// setfontstate @ 0x8ea00 [__cdecl]
// ================================================================================================

void setfontstate(undefined4 *param_1)

{
  int iVar1;
  undefined **ppuVar2;
  
  ppuVar2 = &off_d42a4;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *ppuVar2 = (undefined *)*param_1;
    param_1 = param_1 + 1;
    ppuVar2 = ppuVar2 + 1;
  }
  return;
}


// ================================================================================================
// setfont @ 0x8ea18 [__cdecl]
// ================================================================================================

void setfont(undefined4 *param_1)

{
  off_d42a4 = (undefined *)param_1;
  dword_d42bc = *param_1;
  byte_d42c0 = *(undefined *)(param_1 + 1);
  byte_d42c1 = *(undefined *)((int)param_1 + 5);
  byte_d42c2 = *(undefined *)((int)param_1 + 6);
  byte_d42c3 = *(undefined *)((int)param_1 + 7);
  byte_d42c4 = *(undefined *)(param_1 + 2);
  byte_d42c5 = *(undefined *)((int)param_1 + 9);
  byte_d42c6 = *(undefined *)((int)param_1 + 10);
  dword_d42b8 = 0;
  if ((int)param_1[4] >> 0x10 == 0) {
    off_d42c8 = (undefined *)0x0;
  }
  else {
    off_d42c8 = (undefined *)((int)param_1 + ((int)param_1[4] >> 0x10));
  }
  dword_d42cc = (int)(short)param_1[5];
  if (dword_d42cc != 0) {
    dword_d42cc = dword_d42cc + (int)param_1;
  }
  dword_d42d0 = (int)param_1[5] >> 0x10;
  if (dword_d42d0 != 0) {
    dword_d42d0 = dword_d42d0 + (int)param_1;
  }
  dword_d42d4 = (int)(short)param_1[6];
  if (dword_d42d4 != 0) {
    dword_d42d4 = dword_d42d4 + (int)param_1;
  }
  dword_d42d8 = (int)param_1[6] >> 0x10;
  if (dword_d42d8 != 0) {
    dword_d42d8 = dword_d42d8 + (int)param_1;
  }
  dword_d42dc = (int)param_1 + param_1[7];
  off_d42e0 = (undefined *)(param_1 + 8);
  return;
}


// ================================================================================================
// sub_8eaec @ 0x8eaec [__watcall]
// ================================================================================================

longlong __watcall
sub_8eaec(undefined *param_1,undefined4 unaff_EDX,undefined4 param_3,undefined4 unaff_ECX)

{
  code *pcVar1;
  undefined uVar2;
  undefined2 extraout_CX;
  undefined2 extraout_DX;
  uint unaff_retaddr;
  
  pcVar1 = (code *)swi(0x21);
  uVar2 = (*pcVar1)(unaff_ECX,unaff_EDX);
  *(undefined2 *)(param_1 + 2) = extraout_CX;
  param_1[1] = (char)((ushort)extraout_DX >> 8);
  *param_1 = (char)extraout_DX;
  param_1[4] = uVar2;
  return (ulonglong)unaff_retaddr << 0x20;
}


// ================================================================================================
// _dos_gettime @ 0x8eb07 [__watcall]
// ================================================================================================

longlong __watcall
_dos_gettime(undefined *param_1,undefined4 unaff_EDX,undefined4 param_3,undefined4 unaff_ECX)

{
  code *pcVar1;
  undefined2 extraout_CX;
  undefined2 extraout_DX;
  uint unaff_retaddr;
  
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)(unaff_ECX,unaff_EDX);
  *param_1 = (char)((ushort)extraout_CX >> 8);
  param_1[1] = (char)extraout_CX;
  param_1[2] = (char)((ushort)extraout_DX >> 8);
  param_1[3] = (char)extraout_DX;
  return (ulonglong)unaff_retaddr << 0x20;
}


// ================================================================================================
// sub_8eb21 @ 0x8eb21 [__watcall]
// ================================================================================================

undefined * __watcall sub_8eb21(void)

{
  return &unk_d41c8;
}


// ================================================================================================
// rand @ 0x8eb27 [__watcall]
// ================================================================================================

int __watcall rand(void)

{
  uint *puVar1;
  uint uVar2;
  
  puVar1 = (uint *)sub_8eb21();
  if (puVar1 != (uint *)0x0) {
    uVar2 = *puVar1 * 0x41c64e6d + 0x3039;
    *puVar1 = uVar2;
    puVar1 = (uint *)(uVar2 >> 0x10 & 0x7fff);
  }
  return (int)puVar1;
}


// ================================================================================================
// srand @ 0x8eb4b [__watcall]
// ================================================================================================

void __watcall srand(uint __seed)

{
  undefined8 uVar1;
  
  uVar1 = sub_8eb21(__seed,__seed);
  if ((undefined4 *)uVar1 != (undefined4 *)0x0) {
    *(undefined4 *)uVar1 = (int)((ulonglong)uVar1 >> 0x20);
  }
  return;
}


// ================================================================================================
// sound_timer_install @ 0x8eb5b [__watcall]
// ================================================================================================

longlong __watcall
sound_timer_install(undefined4 param_1,uint unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  sound_shutdown();
  addtimer(sound_timer,unaff_EDX,unaff_ECX,unaff_EBX);
  if (byte_d41cc == '\0') {
    sub_b3454(sound_shutdown);
    byte_d41cc = '\x01';
  }
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// sound_shutdown @ 0x8eb93 [__watcall]
// ================================================================================================

void __watcall
sound_shutdown(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  int extraout_EDX;
  int iVar1;
  int extraout_EDX_00;
  
  removetimer(sound_timer,unaff_EDX,unaff_ECX,unaff_EBX);
  iVar1 = dword_d4f64;
  while (-1 < (int)(iVar1 - 1U)) {
    sub_971be(iVar1 - 1U & 0xff);
    iVar1 = extraout_EDX;
  }
  iVar1 = 0;
  do {
    kms_unload((&unk_edcfc)[iVar1 * 6]);
    iVar1 = extraout_EDX_00 + 1;
  } while (iVar1 < 0xd);
  unload_patches();
  sub_8ebe2();
  return;
}


// ================================================================================================
// sub_8ebe2 @ 0x8ebe2 [__watcall]
// ================================================================================================

void __watcall sub_8ebe2(void)

{
  short sVar1;
  int iVar2;
  
  for (sVar1 = 0; sVar1 < 0x18; sVar1 = sVar1 + 1) {
    iVar2 = sVar1 * 0x54;
    (&unk_f1a1c)[iVar2] = (char)sVar1;
    (&unk_f1a1d)[iVar2] = 0;
    (&unk_f1a1e)[sVar1 * 0x15] = 0;
  }
  for (sVar1 = 0; sVar1 < 0x20; sVar1 = sVar1 + 1) {
    (&unk_f189c)[sVar1 * 3] = 0;
  }
  for (sVar1 = 0; sVar1 < 10; sVar1 = sVar1 + 1) {
    (&unk_ede34)[sVar1] = 0;
  }
  for (sVar1 = 0; sVar1 < 0x10; sVar1 = sVar1 + 1) {
    (&unk_f23bc)[sVar1] = 0;
  }
  for (sVar1 = 0; sVar1 < 0xd; sVar1 = sVar1 + 1) {
    iVar2 = (int)sVar1;
    (&unk_edcfc)[iVar2 * 6] = 0;
    (&unk_edd00)[iVar2 * 6] = 0;
    (&unk_edd04)[iVar2 * 6] = 0;
  }
  for (sVar1 = 0; sVar1 < 4; sVar1 = sVar1 + 1) {
    (&unk_f22fc)[sVar1 * 5] = 0;
  }
  snd_patch_bank = 0;
  dword_d4f64 = 0;
  dword_d4f96 = 0xffffffff;
  return;
}


// ================================================================================================
// loadpatches @ 0x8ecc0 [__watcall]
// ================================================================================================

undefined4 __watcall loadpatches(char *param_1,undefined4 unaff_EDX)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  char local_20 [16];
  int local_10;
  
  unload_patches();
  if (*param_1 == '\0') {
    uVar1 = 0xfffffffb;
  }
  else {
    sub_8fed2(param_1,&aSCN);
    local_10 = sub_594b2(1,local_20);
    if (local_10 == 0) {
      uVar1 = 0xffffffff;
    }
    else {
      uVar1 = sub_8dbdc(local_10);
      uVar1 = sub_8dbd4(local_10,&byte_f23cc,uVar1);
      sub_b3abc(uVar1);
      sub_8ff3e(&local_10);
      sprintf(local_20,a03sFF03dPAT,unaff_EDX,(uint)byte_f23cd);
      dword_f23ea = load_patch_file(local_20);
      if (dword_f23ea == 0) {
        unload_patches();
        uVar1 = 0xfffffffe;
      }
      else {
        for (iVar3 = 0; iVar3 < (int)(uint)byte_f23cf; iVar3 = iVar3 + 1) {
          sprintf(local_20,a03sFF03dTIM,unaff_EDX,(uint)(byte)(&unk_f23e0)[iVar3]);
          iVar2 = load_timbre_file(local_20,&unk_f2416 + iVar3);
          (&unk_f23ee)[iVar3] = iVar2;
          if (iVar2 == 0) {
            unload_patches();
            return 0xfffffffd;
          }
        }
        bind_patch_timbres();
        uVar1 = 0;
      }
    }
  }
  return uVar1;
}


// ================================================================================================
// unload_patches @ 0x8edd2 [__watcall]
// ================================================================================================

void __watcall unload_patches(void)

{
  int iVar1;
  
  if (byte_f23cc == '\x04') {
    for (iVar1 = 0; iVar1 < (int)(uint)byte_f23cf; iVar1 = iVar1 + 1) {
      sub_8ef76((&unk_f23ee)[iVar1],(&unk_f2416)[iVar1]);
      (&unk_f23ee)[iVar1] = 0;
      (&unk_f2416)[iVar1] = 0;
    }
    sub_8ee43(dword_f23ea);
    dword_f23ea = 0;
    byte_f23cc = '\0';
  }
  return;
}


// ================================================================================================
// load_patch_file @ 0x8ee2f [__watcall]
// ================================================================================================

void __watcall
load_patch_file(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  snd_patch_bank = sub_59493(2,param_1,unaff_EBX,unaff_ECX,unaff_EDX);
  return;
}


// ================================================================================================
// sub_8ee43 @ 0x8ee43 [__watcall]
// ================================================================================================

void __watcall sub_8ee43(undefined4 param_1)

{
  undefined4 uStack_4;
  
  uStack_4 = param_1;
  sub_8ff1e(&uStack_4);
  return;
}


// ================================================================================================
// load_timbre_file @ 0x8ee4f [__watcall]
// ================================================================================================

int __watcall load_timbre_file(undefined4 param_1,int *unaff_EDX)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 *puVar7;
  int local_1c;
  
  *unaff_EDX = 0;
  iVar2 = sub_59493(3,param_1);
  if (iVar2 != 0) {
    timbre_bank_add();
    if (byte_d41cd == '\0') {
      uVar6 = 0x2e646967;
    }
    else {
      uVar6 = 0x6769642e;
    }
    iVar3 = sub_8fe89(iVar2,uVar6);
    if (iVar3 != 0) {
      iVar3 = sub_594b2(4,iVar3);
      *unaff_EDX = iVar3;
      if (iVar3 != 0) {
        uVar1 = *(ushort *)(iVar2 + 4);
        puVar7 = (undefined4 *)(iVar2 + 6);
        for (local_1c = 0; local_1c < (int)(uint)uVar1; local_1c = local_1c + 1) {
          pcVar4 = (char *)sub_8fe89(iVar2,*puVar7);
          if (*pcVar4 == '\x06') {
            if (byte_d41cd == '\0') {
              uVar6 = sub_8ff7c(*(undefined4 *)(pcVar4 + 2));
            }
            else {
              uVar6 = *(undefined4 *)(pcVar4 + 2);
            }
            uVar5 = sub_8dbd4(*unaff_EDX);
            iVar3 = sub_8fe89(uVar5,uVar6);
            if (iVar3 != 0) {
              pcVar4[10] = '\0';
              pcVar4[0xb] = '\0';
              *(int *)(pcVar4 + 0xc) = iVar3;
              pcVar4[0x10] = '\0';
              pcVar4[0x11] = '\0';
              pcVar4[0x12] = '\x11';
              pcVar4[0x13] = '+';
            }
          }
          puVar7 = puVar7 + 1;
        }
      }
    }
  }
  return iVar2;
}


// ================================================================================================
// timbre_bank_add @ 0x8ef50 [__watcall]
// ================================================================================================

void __watcall timbre_bank_add(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = 0;
  do {
    if ((&unk_ede34)[iVar1] == 0) {
      (&unk_ede34)[iVar1] = param_1;
      return;
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 < 10);
  return;
}


// ================================================================================================
// sub_8ef76 @ 0x8ef76 [__watcall]
// ================================================================================================

void __watcall sub_8ef76(undefined4 param_1)

{
  undefined4 local_4;
  
  local_4 = param_1;
  timbre_bank_remove();
  sub_8ff1e(&local_4);
  sub_8ff3e(&stack0xfffffff8);
  return;
}


// ================================================================================================
// timbre_bank_remove @ 0x8ef91 [__watcall]
// ================================================================================================

void __watcall timbre_bank_remove(int param_1)

{
  int iVar1;
  
  iVar1 = 0;
  do {
    if (param_1 == (&unk_ede34)[iVar1]) {
      (&unk_ede34)[iVar1] = 0;
      return;
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 < 10);
  return;
}


// ================================================================================================
// bind_patch_timbres @ 0x8efbb [__watcall]
// ================================================================================================

void __watcall bind_patch_timbres(void)

{
  undefined *puVar1;
  int iVar2;
  int iVar3;
  uint local_18;
  undefined local_14 [3];
  undefined uStack_11;
  
  if (snd_patch_bank == 0) {
    return;
  }
  local_18 = 0;
  word_d4f88 = word_d4f88 + 1;
LAB_0008efdb:
  puVar1 = (undefined *)snd_patch_record(local_18 & 0xff);
  if ((puVar1 != (undefined *)0x0) && ((puVar1[0xf] & 0x80) == 0)) {
    if (puVar1[0xf] == 3) {
      for (iVar2 = 0; iVar2 < dword_d4f64; iVar2 = iVar2 + 1) {
        if ((&unk_f243e)[iVar2] == '\x03') goto LAB_0008f011;
      }
    }
    else {
      iVar2 = 0;
      do {
        if ((&unk_ede34)[iVar2] != 0) {
          if (byte_d41cd == '\0') {
            _local_14 = (uint)CONCAT11(0x80,*puVar1) << 0x10;
            _local_14 = CONCAT31(stack0xffffffed,puVar1[1]);
          }
          else {
            _local_14 = CONCAT13(puVar1[1],CONCAT12(0,CONCAT11(*puVar1,0x80)));
          }
          iVar3 = sub_8fe89((&unk_ede34)[iVar2],_local_14);
          *(int *)(puVar1 + 0x10) = iVar3;
          if (iVar3 != 0) {
            iVar2 = 0;
            goto LAB_0008f0a5;
          }
        }
        iVar2 = iVar2 + 1;
      } while (iVar2 < 10);
    }
  }
  goto LAB_0008f0b5;
LAB_0008f0a5:
  if (dword_d4f64 <= iVar2) goto LAB_0008f0b5;
  if (puVar1[0xf] == (&unk_f243e)[iVar2]) goto LAB_0008f011;
  iVar2 = iVar2 + 1;
  goto LAB_0008f0a5;
LAB_0008f011:
  puVar1[0xf] = (byte)iVar2 | 0x80;
LAB_0008f0b5:
  local_18 = local_18 + 1;
  if (0xff < (int)local_18) {
    word_d4f88 = word_d4f88 + -1;
    return;
  }
  goto LAB_0008efdb;
}


// ================================================================================================
// snd_patch_record @ 0x8f0d7 [__cdecl]
// ================================================================================================

int snd_patch_record(byte param_1)

{
  sub_902a0();
  if ((snd_patch_bank != 0) && (*(char *)((uint)param_1 + snd_patch_bank + 2) != '\0')) {
    return (uint)*(byte *)((uint)param_1 + snd_patch_bank + 2) * 0x14 + snd_patch_bank + 0x102;
  }
  return 0;
}


// ================================================================================================
// snd_patch_timbre @ 0x8f114 [__watcall]
// ================================================================================================

undefined4 __watcall snd_patch_timbre(void)

{
  int iVar1;
  undefined in_stack_00000004;
  
  sub_902a0();
  if (snd_patch_bank == 0) {
    return 0;
  }
  iVar1 = snd_patch_record(in_stack_00000004);
  return *(undefined4 *)(iVar1 + 0x10);
}


// ================================================================================================
// music_load_kms @ 0x8f13b [__watcall]
// ================================================================================================

undefined8 __watcall music_load_kms(undefined4 param_1,undefined4 unaff_EDX)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined auStack_28 [16];
  
  iVar1 = kms_find_song(0);
  if (-1 < iVar1) {
    puVar4 = &unk_d41d2;
    puVar5 = &unk_edcfc + iVar1 * 6;
    for (iVar3 = 6; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar5 = *puVar4;
      puVar4 = puVar4 + 1;
      puVar5 = puVar5 + 1;
    }
    dword_d41ce = dword_d41ce + 1;
    if (dword_d41ce < 0x201) {
      dword_d41ce = 0x200;
    }
    (&unk_edcfc)[iVar1 * 6] = dword_d41ce;
    sub_8fed2(param_1,&aKMS,auStack_28);
    uVar2 = sub_59493(5,auStack_28);
    (&unk_edd00)[iVar1 * 6] = uVar2;
    if (uVar2 == 0) goto LAB_0008f1f4;
    sub_8fed2(param_1,&aCFG,auStack_28);
    iVar3 = sub_59493(6,auStack_28);
    (&unk_edd04)[iVar1 * 6] = iVar3;
    if (iVar3 != 0) {
      uVar2 = (&unk_edcfc)[iVar1 * 6];
      goto LAB_0008f1f4;
    }
    sub_8ff1e(&unk_edd00 + iVar1 * 6);
  }
  uVar2 = 0;
LAB_0008f1f4:
  return CONCAT44(unaff_EDX,uVar2);
}


// ================================================================================================
// kms_unload @ 0x8f1fe [__watcall]
// ================================================================================================

void __watcall
kms_unload(uint param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  int iVar1;
  undefined4 extraout_EDX;
  int extraout_EDX_00;
  
  if (0x1ff < param_1) {
    snd_stop_handle(param_1,param_1,unaff_EBX,unaff_ECX,unaff_EDX,unaff_EBX);
    iVar1 = kms_find_song(extraout_EDX);
    if (-1 < iVar1) {
      sub_8ff1e(&unk_edd00 + iVar1 * 6);
      sub_8ff1e(&unk_edd04 + iVar1 * 6);
      *(undefined4 *)((int)&unk_edcfc + extraout_EDX_00) = 0;
    }
  }
  return;
}


// ================================================================================================
// kms_find_song @ 0x8f247 [__watcall]
// ================================================================================================

undefined8 __watcall kms_find_song(int param_1,undefined4 unaff_EDX)

{
  int iVar1;
  
  iVar1 = 0;
  do {
    if (param_1 == (&unk_edcfc)[iVar1 * 6]) {
      return CONCAT44(unaff_EDX,iVar1);
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 < 0xd);
  return CONCAT44(unaff_EDX,0xffffffff);
}


// ================================================================================================
// kms_play @ 0x8f270 [__watcall]
// ================================================================================================

void __watcall
kms_play(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  kms_start(param_1,unaff_EDX,0,unaff_ECX,unaff_EBX);
  return;
}


// ================================================================================================
// sub_8f27a @ 0x8f27a [__watcall]
// ================================================================================================

undefined4 __watcall
sub_8f27a(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  ulonglong uVar4;
  undefined uVar5;
  undefined *puVar6;
  undefined2 *puVar7;
  int iVar8;
  undefined4 *puVar9;
  uint uVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  int unaff_retaddr;
  undefined4 *param_8;
  undefined param_10;
  byte bStack00000020;
  byte bStack00000028;
  
  puVar9 = &unk_edcfc + param_1 * 6;
  param_8 = puVar9;
  uVar11 = drv_index(param_2);
  if ((int)(uint)uVar11 < 0) {
    param_5 = 0;
  }
  else {
    iVar2 = (&unk_edd00)[param_1 * 6];
    iVar3 = (&unk_edd04)[param_1 * 6];
    bVar1 = *(byte *)(iVar2 + 1);
    bStack00000020 = *(byte *)(iVar2 + 6);
    uVar12 = CONCAT44((int)((ulonglong)uVar11 >> 0x20),
                      CONCAT22((short)((uint)iVar2 >> 0x10),(ushort)bStack00000020));
    bStack00000028 = 0;
    word_d4f88 = word_d4f88 + 1;
    for (; bStack00000020 != 0; bStack00000020 = bStack00000020 - 1) {
      puVar6 = (undefined *)kms_alloc_track((int)uVar12,(int)((ulonglong)uVar12 >> 0x20),puVar9);
      if (puVar6 == (undefined *)0x0) {
        param_5 = 0;
        break;
      }
      uVar5 = *puVar6;
      sub_b3fb0(puVar6,0x54,0);
      *puVar6 = uVar5;
      *(undefined4 *)(puVar6 + 2) = param_5;
      *(undefined4 **)(puVar6 + 6) = param_8;
      puVar9 = (undefined4 *)(uint)bStack00000028;
      iVar8 = iVar2 + (uint)*(ushort *)((int)puVar9 * 2 + iVar2 + 8);
      *(int *)(puVar6 + 10) = iVar8;
      *(int *)(puVar6 + 0x32) = iVar8;
      uVar4 = 32000 / (ulonglong)(longlong)(int)(uint)bVar1;
      uVar12 = CONCAT44((int)(32000 % (ulonglong)(longlong)(int)(uint)bVar1),(int)uVar4);
      *(short *)(puVar6 + 0x4c) = (short)uVar4;
      if (iVar3 != 0) {
        puVar7 = (undefined2 *)(iVar3 + 8 + (int)puVar9 * 0x10);
        uVar5 = kms_track_channel(*puVar7);
        puVar6[0x50] = uVar5;
        if ((byte)puVar6[0x50] == 0xffffffff) {
          param_5 = 0;
          break;
        }
        param_10 = (undefined)uVar11;
        puVar6[0x51] = param_10;
        uVar10 = (uint)uVar11 & 0xff;
        drv_channel_config(uVar10,puVar6[0x50],*(undefined4 *)(puVar7 + 1));
        snd_program_change(uVar10,puVar6[0x50]);
        kms_controller(puVar6,1,0);
        kms_controller(puVar6,7,*(undefined *)(puVar7 + 3));
        puVar9 = (undefined4 *)(uint)*(byte *)((int)puVar7 + 7);
        kms_controller(puVar6,10);
        uVar12 = kms_pitch_bend(puVar6,0x4000);
      }
      puVar6[1] = 1;
      if (0 < unaff_retaddr) {
        puVar6[1] = puVar6[1] | 8;
        iVar8 = *(int *)(puVar6 + 6);
        *(undefined2 *)(iVar8 + 0xe) = 0xffff;
        uVar5 = *(undefined *)(*(int *)(puVar6 + 6) + 0x11);
        uVar12 = CONCAT44(iVar8,CONCAT31((int3)((ulonglong)uVar12 >> 8),uVar5));
        *(undefined *)(*(int *)(puVar6 + 6) + 0x10) = uVar5;
      }
      bStack00000028 = bStack00000028 + 1;
    }
    word_d4f88 = word_d4f88 + -1;
  }
  return param_5;
}


// ================================================================================================
// kms_alloc_track @ 0x8f433 [__watcall]
// ================================================================================================

undefined8 __watcall kms_alloc_track(undefined4 param_1,undefined4 unaff_EDX)

{
  undefined1 *puVar1;
  short sVar2;
  
  puVar1 = &unk_f1a1c;
  for (sVar2 = 0; sVar2 < 0x18; sVar2 = sVar2 + 1) {
    if (puVar1[1] == '\0') goto LAB_0008f44f;
    puVar1 = puVar1 + 0x54;
  }
  puVar1 = (undefined1 *)0x0;
LAB_0008f44f:
  return CONCAT44(unaff_EDX,puVar1);
}


// ================================================================================================
// kms_track_channel @ 0x8f451 [__watcall]
// ================================================================================================

undefined8 __watcall kms_track_channel(ushort param_1,undefined4 unaff_EDX)

{
  short sVar1;
  int iVar2;
  
  for (iVar2 = 0; sVar1 = (short)iVar2, sVar1 < 0x10; iVar2 = iVar2 + 1) {
    if (((param_1 & (&unk_d4f68)[sVar1]) != 0) && ((&unk_f23bc)[sVar1] == '\0')) goto LAB_0008f48a;
  }
  iVar2 = -1;
LAB_0008f48a:
  return CONCAT44(unaff_EDX,iVar2);
}


// ================================================================================================
// kms_load_start @ 0x8f48f [__watcall]
// ================================================================================================

void __watcall
kms_load_start(undefined4 param_1,undefined4 param_2,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  undefined8 uVar1;
  
  uVar1 = music_load_kms();
  if ((int)uVar1 != 0) {
    kms_start((int)uVar1,(int)((ulonglong)uVar1 >> 0x20),0,unaff_ECX,unaff_EBX);
  }
  return;
}


// ================================================================================================
// kms_start @ 0x8f4a7 [__watcall]
// ================================================================================================

undefined4 __watcall kms_start(undefined4 param_1,undefined4 param_2,int unaff_EBX)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  ulonglong uVar4;
  undefined uVar5;
  undefined *puVar6;
  int iVar7;
  undefined2 *puVar8;
  int iVar9;
  undefined4 *puVar10;
  uint uVar11;
  undefined8 uVar12;
  undefined8 uVar13;
  undefined4 uStack_38;
  undefined uStack_24;
  byte bStack_1c;
  byte bStack_14;
  
  uVar13 = kms_find_song();
  iVar7 = (int)uVar13;
  if (-1 < iVar7) {
    uVar13 = drv_index((int)((ulonglong)uVar13 >> 0x20));
    if (-1 < (int)(uint)uVar13) {
      iVar2 = (&unk_edd00)[iVar7 * 6];
      iVar3 = (&unk_edd04)[iVar7 * 6];
      bVar1 = *(byte *)(iVar2 + 1);
      bStack_1c = *(byte *)(iVar2 + 6);
      uVar12 = CONCAT44((int)((ulonglong)uVar13 >> 0x20),
                        CONCAT22((short)((uint)iVar2 >> 0x10),(ushort)bStack_1c));
      bStack_14 = 0;
      word_d4f88 = word_d4f88 + 1;
      puVar10 = &unk_edcfc + iVar7 * 6;
      do {
        uStack_38 = param_1;
        if (bStack_1c == 0) {
LAB_0008f420:
          word_d4f88 = word_d4f88 + -1;
          return uStack_38;
        }
        puVar6 = (undefined *)kms_alloc_track((int)uVar12,(int)((ulonglong)uVar12 >> 0x20),puVar10);
        if (puVar6 == (undefined *)0x0) {
          uStack_38 = 0;
          goto LAB_0008f420;
        }
        uVar5 = *puVar6;
        sub_b3fb0(puVar6,0x54,0);
        *puVar6 = uVar5;
        *(undefined4 *)(puVar6 + 2) = param_1;
        *(undefined4 **)(puVar6 + 6) = &unk_edcfc + iVar7 * 6;
        puVar10 = (undefined4 *)(uint)bStack_14;
        iVar9 = iVar2 + (uint)*(ushort *)((int)puVar10 * 2 + iVar2 + 8);
        *(int *)(puVar6 + 10) = iVar9;
        *(int *)(puVar6 + 0x32) = iVar9;
        uVar4 = 32000 / (ulonglong)(longlong)(int)(uint)bVar1;
        uVar12 = CONCAT44((int)(32000 % (ulonglong)(longlong)(int)(uint)bVar1),(int)uVar4);
        *(short *)(puVar6 + 0x4c) = (short)uVar4;
        if (iVar3 != 0) {
          puVar8 = (undefined2 *)(iVar3 + 8 + (int)puVar10 * 0x10);
          uVar5 = kms_track_channel(*puVar8);
          puVar6[0x50] = uVar5;
          if ((byte)puVar6[0x50] == 0xffffffff) {
            uStack_38 = 0;
            goto LAB_0008f420;
          }
          uStack_24 = (undefined)uVar13;
          puVar6[0x51] = uStack_24;
          uVar11 = (uint)uVar13 & 0xff;
          drv_channel_config(uVar11,puVar6[0x50],*(undefined4 *)(puVar8 + 1));
          snd_program_change(uVar11,puVar6[0x50]);
          kms_controller(puVar6,1,0);
          kms_controller(puVar6,7,*(undefined *)(puVar8 + 3));
          puVar10 = (undefined4 *)(uint)*(byte *)((int)puVar8 + 7);
          kms_controller(puVar6,10);
          uVar12 = kms_pitch_bend(puVar6,0x4000);
        }
        puVar6[1] = 1;
        if (0 < unaff_EBX) {
          puVar6[1] = puVar6[1] | 8;
          iVar9 = *(int *)(puVar6 + 6);
          *(undefined2 *)(iVar9 + 0xe) = 0xffff;
          uVar5 = *(undefined *)(*(int *)(puVar6 + 6) + 0x11);
          uVar12 = CONCAT44(iVar9,CONCAT31((int3)((ulonglong)uVar12 >> 8),uVar5));
          *(undefined *)(*(int *)(puVar6 + 6) + 0x10) = uVar5;
        }
        bStack_1c = bStack_1c - 1;
        bStack_14 = bStack_14 + 1;
      } while( true );
    }
  }
  return 0;
}


// ================================================================================================
// snd_play_patch @ 0x8f4c4 [__watcall]
// ================================================================================================

int __watcall snd_play_patch(ushort param_1,int unaff_EDX,undefined unaff_BL)

{
  byte bVar1;
  int iVar2;
  ushort uVar3;
  short sVar4;
  int iVar5;
  byte *pbVar6;
  uint uVar7;
  undefined local_18;
  byte local_14;
  
  if (param_1 < 0x100) {
    if (dword_d4f8e == 0) {
      return 0;
    }
    local_18 = (undefined)param_1;
    iVar5 = snd_patch_record(param_1 & 0xff);
    iVar2 = dword_d4f9a;
    if (iVar5 != 0) {
      bVar1 = *(byte *)(iVar5 + 0xf);
      if (unaff_EDX == 0) {
        if (*(byte *)(iVar5 + 0xe) == 0) {
          unaff_EDX = 0xa0;
        }
        else {
          unaff_EDX = (uint)*(byte *)(iVar5 + 0xe) * 6;
        }
      }
      pbVar6 = &unk_f21fc + dword_d4f9a;
      dword_d4f9a = dword_d4f9a + 4;
      if (param_1 < 0x80) {
        uVar7 = dword_d41ea + 0xc;
        dword_d41ea = dword_d41ea + 1 & 3;
        local_14 = (byte)uVar7;
        *pbVar6 = local_14 | 0xc0;
        (&DAT_000f21fd)[iVar2] = local_18;
        snd_queue_message(bVar1 & 0x7f,2,pbVar6);
        *pbVar6 = local_14 | 0xb0;
        (&DAT_000f21fd)[iVar2] = 7;
        (&DAT_000f21fe)[iVar2] = unaff_BL;
        snd_queue_message(bVar1 & 0x7f,3,pbVar6);
        uVar7 = uVar7 & 0xff;
        uVar3 = 0x24;
      }
      else {
        *pbVar6 = 0xb9;
        (&DAT_000f21fd)[iVar2] = 7;
        (&DAT_000f21fe)[iVar2] = unaff_BL;
        snd_queue_message(bVar1 & 0x7f,3,pbVar6);
        uVar3 = param_1 - 0x74 & 0xff;
        uVar7 = 9;
      }
      sVar4 = snd_note_on(uVar3,0x7f,unaff_EDX,uVar7,bVar1 & 0x7f,0xff,0xff);
      dword_d4f9a = dword_d4f9a + -4;
      return (int)sVar4;
    }
  }
  return -1;
}


// ================================================================================================
// snd_play_sfx @ 0x8f61d [__watcall]
// ================================================================================================

void __watcall
snd_play_sfx(undefined2 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  snd_play_patch(param_1,0,0x7f,unaff_ECX,unaff_EDX,unaff_EBX);
  return;
}


// ================================================================================================
// sound_stopall @ 0x8f633 [__watcall]
// ================================================================================================

void __watcall sound_stopall(void)

{
  short sVar1;
  
  if (dword_d4f8e != 0) {
    word_d4f88 = word_d4f88 + 1;
    for (sVar1 = 0; sVar1 < 0x20; sVar1 = sVar1 + 1) {
      if ((&unk_f189c)[sVar1 * 3] != 0) {
        (&unk_f18a4)[sVar1 * 3] = 1;
      }
    }
    word_d4f88 = word_d4f88 + -1;
  }
  return;
}


// ================================================================================================
// snd_stop_handle @ 0x8f67d [__watcall]
// ================================================================================================

undefined8 __watcall snd_stop_handle(uint param_1,undefined4 unaff_EDX)

{
  int iVar1;
  undefined4 uVar2;
  uint *puVar3;
  byte *pbVar4;
  undefined1 *puVar5;
  short sVar6;
  
  if (param_1 == 0xffffffff) {
    uVar2 = 0xffffffff;
  }
  else {
    word_d4f88 = word_d4f88 + 1;
    if (param_1 < 0x100) {
      if (dword_d4f8e == 0) {
        uVar2 = 0;
        goto LAB_0008f1f7;
      }
      if ((&unk_f18a4)[param_1 * 3] != 0) {
        (&unk_f18a4)[param_1 * 3] = 1;
      }
    }
    else {
      puVar3 = &unk_f189c;
      puVar5 = &unk_f1a1c;
      for (sVar6 = 0; iVar1 = dword_d4f9a, sVar6 < 0x20; sVar6 = sVar6 + 1) {
        if (param_1 == *puVar3) {
          snd_note_off(puVar3);
        }
        puVar3 = puVar3 + 3;
      }
      pbVar4 = &unk_f21fc + dword_d4f9a;
      dword_d4f9a = dword_d4f9a + 4;
      for (sVar6 = 0; sVar6 < 0x18; sVar6 = sVar6 + 1) {
        if (param_1 == *(uint *)(puVar5 + 2)) {
          *pbVar4 = puVar5[0x50] | 0xb0;
          (&DAT_000f21fd)[iVar1] = 0x7b;
          (&DAT_000f21fe)[iVar1] = 0;
          snd_queue_message(puVar5[0x51] & 0x7f,3,pbVar4);
          *pbVar4 = puVar5[0x50] | 0xb0;
          (&DAT_000f21fd)[iVar1] = 7;
          (&DAT_000f21fe)[iVar1] = 0;
          snd_queue_message(puVar5[0x51] & 0x7f,3,pbVar4);
          puVar5[1] = 0;
          *(undefined4 *)(puVar5 + 2) = 0;
        }
        puVar5 = puVar5 + 0x54;
      }
      *pbVar4 = 0xb9;
      (&DAT_000f21fd)[iVar1] = 7;
      (&DAT_000f21fe)[iVar1] = 0x7f;
      snd_queue_message(byte_f1d61 & 0x7f,3,pbVar4);
      sound_timer_tick();
      dword_d4f9a = dword_d4f9a + -4;
    }
    uVar2 = 0;
    word_d4f88 = word_d4f88 + -1;
  }
LAB_0008f1f7:
  return CONCAT44(unaff_EDX,uVar2);
}


// ================================================================================================
// kms_fade_out @ 0x8f7ae [__watcall]
// ================================================================================================

undefined4 __watcall kms_fade_out(int param_1,undefined2 unaff_DX)

{
  undefined1 *puVar1;
  short sVar2;
  
  puVar1 = &unk_f1a1c;
  word_d4f88 = word_d4f88 + 1;
  for (sVar2 = 0; sVar2 < 0x18; sVar2 = sVar2 + 1) {
    if ((param_1 == *(int *)(puVar1 + 2)) && (puVar1[1] != 0)) {
      puVar1[1] = puVar1[1] | 8;
      *(undefined2 *)(*(int *)(puVar1 + 6) + 0xc) = unaff_DX;
      *(short *)(*(int *)(puVar1 + 6) + 0xe) = *(short *)(*(int *)(puVar1 + 6) + 0xc) + -1;
      *(undefined *)(*(int *)(puVar1 + 6) + 0x10) = *(undefined *)(*(int *)(puVar1 + 6) + 0x11);
    }
    puVar1 = puVar1 + 0x54;
  }
  word_d4f88 = word_d4f88 + -1;
  return 0;
}


// ================================================================================================
// kms_finished @ 0x8f80e [__watcall]
// ================================================================================================

longlong __watcall kms_finished(int param_1,uint unaff_EDX)

{
  undefined1 *puVar1;
  short sVar2;
  
  if (dword_d4f64 != 0) {
    puVar1 = &unk_f1a1c;
    for (sVar2 = 0; sVar2 < 0x18; sVar2 = sVar2 + 1) {
      if ((param_1 == *(int *)(puVar1 + 2)) && (puVar1[1] != '\0')) {
        return (ulonglong)unaff_EDX << 0x20;
      }
      puVar1 = puVar1 + 0x54;
    }
  }
  return CONCAT44(unaff_EDX,1);
}


// ================================================================================================
// kms_fade_done @ 0x8f846 [__watcall]
// ================================================================================================

longlong __watcall kms_fade_done(int param_1,uint unaff_EDX)

{
  undefined1 *puVar1;
  short sVar2;
  
  if (dword_d4f64 != 0) {
    puVar1 = &unk_f1a1c;
    for (sVar2 = 0; sVar2 < 0x18; sVar2 = sVar2 + 1) {
      if ((param_1 == *(int *)(puVar1 + 2)) && ((puVar1[1] & 8) != 0)) {
        return (ulonglong)unaff_EDX << 0x20;
      }
      puVar1 = puVar1 + 0x54;
    }
  }
  return CONCAT44(unaff_EDX,1);
}


// ================================================================================================
// kms_track_marker @ 0x8f87e [__watcall]
// ================================================================================================

undefined4 __watcall kms_track_marker(int param_1,char unaff_DL)

{
  undefined1 *puVar1;
  short sVar2;
  
  puVar1 = &unk_f1a1c;
  sVar2 = 0;
  while( true ) {
    if (0x17 < sVar2) {
      return 0xffffffff;
    }
    if ((param_1 == *(int *)(puVar1 + 2)) && (unaff_DL == puVar1[0x50])) break;
    puVar1 = puVar1 + 0x54;
    sVar2 = sVar2 + 1;
  }
  return CONCAT22((short)((uint)puVar1 >> 0x10),(ushort)(byte)puVar1[0x4e]);
}


// ================================================================================================
// music_mute @ 0x8f8b7 [__watcall]
// ================================================================================================

void __watcall music_mute(void)

{
  int iVar1;
  byte *pbVar2;
  short sVar3;
  
  iVar1 = dword_d4f9a;
  pbVar2 = &unk_f21fc + dword_d4f9a;
  dword_d4f8a = 1;
  dword_d4f9a = dword_d4f9a + 4;
  for (sVar3 = 0; sVar3 < 0x18; sVar3 = sVar3 + 1) {
    if (unk_f1a1d != '\0') {
      *pbVar2 = DAT_000f1a6c | 0xb0;
      (&DAT_000f21fd)[iVar1] = 7;
      (&DAT_000f21fe)[iVar1] = 0;
      snd_queue_message(0,3,pbVar2);
    }
  }
  dword_d4f9a = dword_d4f9a + -4;
  return;
}


// ================================================================================================
// music_unmute @ 0x8f91c [__watcall]
// ================================================================================================

void __watcall music_unmute(void)

{
  short sVar1;
  
  for (sVar1 = 0; sVar1 < 0x18; sVar1 = sVar1 + 1) {
    if (unk_f1a1d != '\0') {
      kms_controller(&unk_f1a1c,7,(&unk_f234d)[(uint)DAT_000f1a6c * 7]);
    }
  }
  dword_d4f8a = 0;
  return;
}


// ================================================================================================
// sfx_enable @ 0x8f963 [__watcall]
// ================================================================================================

void __watcall sfx_enable(void)

{
  dword_d4f8e = 1;
  return;
}


// ================================================================================================
// sfx_disable @ 0x8f96e [__watcall]
// ================================================================================================

void __watcall sfx_disable(void)

{
  dword_d4f8e = 0;
  return;
}


// ================================================================================================
// music_enable @ 0x8f979 [__watcall]
// ================================================================================================

void __watcall music_enable(void)

{
  dword_d4f92 = 1;
  return;
}


// ================================================================================================
// music_disable @ 0x8f984 [__watcall]
// ================================================================================================

void __watcall music_disable(void)

{
  dword_d4f92 = 0;
  return;
}


// ================================================================================================
// loadsound @ 0x8f98f [__watcall]
// ================================================================================================

undefined8 __watcall loadsound(undefined4 param_1,undefined4 unaff_EDX)

{
  undefined2 uVar1;
  uint *puVar2;
  int iVar3;
  uint *puVar4;
  uint uVar5;
  int iVar6;
  uint *puVar7;
  byte bVar8;
  undefined8 uVar9;
  uint auStackY_180c [1507];
  undefined local_74 [24];
  undefined2 local_5c;
  uint local_4c;
  undefined local_48 [4];
  undefined4 local_44;
  undefined4 local_40;
  undefined2 local_38;
  undefined4 local_30;
  uint local_2c [4];
  byte local_1c;
  
  bVar8 = 0;
  local_2c[3] = sub_594b2(7,param_1);
  if (local_2c[3] != 0) {
    puVar2 = (uint *)sub_8dbd4(local_2c[3]);
    local_30 = local_30 & 0xffff0000;
    iVar6 = 0;
    if (*puVar2 == 0x4d524f46) {
      iVar6 = sub_8faf2(puVar2 + 1,&aVHDR);
      if (iVar6 < 0) {
        sub_8ff3e(local_2c + 3);
        local_2c[3] = 0;
        goto LAB_0008faea;
      }
      sub_b3abc(iVar6 + (int)(puVar2 + 1),local_48,0x18);
      iVar6 = iVar6 + 0x24;
      uVar1 = sub_8ff5e(local_38);
      local_30 = CONCAT22(uVar1,(undefined2)local_30);
      local_2c[1] = sub_8ff7c(local_44);
      uVar9 = sub_8ff7c(local_40,local_2c[1]);
      local_2c[2] = (uint)uVar9;
      local_2c[0] = (int)((ulonglong)uVar9 >> 0x20) + local_2c[2];
      local_1c = 0;
    }
    else if (*puVar2 == 0x46464952) {
      sub_b3abc(puVar2,local_74,0x2c);
      iVar6 = 0x2c;
      local_30 = CONCAT22(local_5c,(undefined2)local_30);
      local_2c[0] = local_4c;
      local_2c[1] = 0;
      local_2c[2] = 0;
      local_1c = 0x80;
    }
    iVar3 = sub_8dbdc(local_2c[3]);
    puVar4 = puVar2 + 4;
    sub_b3abc((int)puVar2 + iVar6,puVar4,iVar3 - iVar6);
    iVar3 = sub_8dbdc(local_2c[3]);
    sub_8d144(local_2c[3],(iVar3 - iVar6) + 0x10);
    puVar7 = puVar2 + (uint)bVar8 * -2 + 1;
    *puVar2 = local_30;
    *puVar7 = local_2c[(uint)bVar8 * -2];
    puVar7[(uint)bVar8 * -2 + 1] = local_2c[(uint)bVar8 * -2 + (uint)bVar8 * -2 + 1];
    (puVar7 + (uint)bVar8 * -2 + 1)[(uint)bVar8 * -2 + 1] =
         (local_2c + (uint)bVar8 * -2 + (uint)bVar8 * -2 + 1)[(uint)bVar8 * -2 + 1];
    if (local_1c != 0) {
      for (uVar5 = 0; uVar5 < local_2c[0]; uVar5 = uVar5 + 1) {
        *(byte *)puVar4 = *(byte *)puVar4 ^ local_1c;
        puVar4 = (uint *)((int)puVar4 + 1);
      }
    }
  }
LAB_0008faea:
  return CONCAT44(unaff_EDX,local_2c[3]);
}


// ================================================================================================
// sub_8faf2 @ 0x8faf2 [__watcall]
// ================================================================================================

int __watcall sub_8faf2(char *param_1,char *unaff_EDX)

{
  size_t sVar1;
  size_t sVar2;
  int iVar3;
  
  sVar1 = strlen(unaff_EDX);
  sVar2 = 0;
  iVar3 = 0;
  do {
    if (*param_1 == unaff_EDX[sVar2]) {
      sVar2 = sVar2 + 1;
      if (sVar2 == sVar1) {
        return iVar3 + 1;
      }
    }
    else {
      sVar2 = 0;
    }
    param_1 = param_1 + 1;
    iVar3 = iVar3 + 1;
  } while( true );
}


// ================================================================================================
// sub_8fb24 @ 0x8fb24 [__watcall]
// ================================================================================================

void __watcall sub_8fb24(int param_1,undefined4 unaff_EDX,int unaff_EBX,undefined4 unaff_ECX)

{
  uint uVar1;
  int iVar2;
  
  if (param_1 != 0) {
    uVar1 = drv_index(unaff_EDX);
    if (-1 < (int)uVar1) {
      iVar2 = sub_8dbd4(param_1);
      (&unk_f22fc)[unaff_EBX * 5] = 0;
      drv_play_sample(uVar1 & 0xff,unaff_EBX,iVar2,0x10,*(undefined4 *)(iVar2 + 4),
                *(undefined4 *)(iVar2 + 8),*(undefined4 *)(iVar2 + 0xc),*(undefined2 *)(iVar2 + 2),
                unaff_ECX,0);
    }
  }
  return;
}


// ================================================================================================
// playsample @ 0x8fb8e [__watcall]
// ================================================================================================

void __watcall playsample(int param_1,undefined4 unaff_EDX,int unaff_EBX,undefined4 unaff_ECX)

{
  uint uVar1;
  int iVar2;
  
  if (param_1 != 0) {
    uVar1 = drv_index(unaff_EDX);
    if (-1 < (int)uVar1) {
      iVar2 = sub_8dbd4(param_1);
      (&unk_f22fc)[unaff_EBX * 5] = 0;
      drv_play_sample(uVar1 & 0xff,unaff_EBX,iVar2,0x10,*(uint *)(iVar2 + 4) >> 1,
                *(uint *)(iVar2 + 8) >> 1,*(uint *)(iVar2 + 0xc) >> 1,*(undefined2 *)(iVar2 + 2),
                unaff_ECX,1);
    }
  }
  return;
}


// ================================================================================================
// sub_8fbe5 @ 0x8fbe5 [__watcall]
// ================================================================================================

void __watcall
sub_8fbe5(int param_1,undefined4 param_2,int unaff_EBX,undefined4 unaff_ECX,undefined4 param_5,
         undefined4 param_6)

{
  undefined8 uVar1;
  
  if (param_1 != 0) {
    uVar1 = drv_index(param_2,unaff_EBX);
    if (-1 < (int)(uint)uVar1) {
      (&unk_f22fc)[unaff_EBX * 5] = 0;
      drv_play_sample((uint)uVar1 & 0xff,(int)((ulonglong)uVar1 >> 0x20),param_1,0,unaff_ECX,0,0,param_5,
                param_6,0);
    }
  }
  return;
}


// ================================================================================================
// sub_8fc37 @ 0x8fc37 [__watcall]
// ================================================================================================

void __watcall
sub_8fc37(int param_1,undefined4 param_2,int unaff_EBX,undefined4 unaff_ECX,undefined4 param_5,
         undefined4 param_6)

{
  undefined8 uVar1;
  
  if (param_1 != 0) {
    uVar1 = drv_index(param_2,unaff_ECX);
    if (-1 < (int)(uint)uVar1) {
      (&unk_f22fc)[unaff_EBX * 5] = 0;
      drv_play_sample((uint)uVar1 & 0xff,unaff_EBX,param_1,0,(int)((ulonglong)uVar1 >> 0x20) / 2,0,0,
                param_5,param_6,1);
    }
  }
  return;
}


// ================================================================================================
// sound_channel_status @ 0x8fc8a [__watcall]
// ================================================================================================

undefined4 __watcall sound_channel_status(uint param_1,int unaff_EDX)

{
  undefined4 uVar1;
  
  if (((int)param_1 < dword_d4f64) && (-1 < (int)param_1)) {
    uVar1 = sub_971f8(param_1 & 0xff,unaff_EDX * 0x10000 + 9);
    return uVar1;
  }
  return 0xffffffff;
}


// ================================================================================================
// sound_channel_stop @ 0x8fcac [__watcall]
// ================================================================================================

void __watcall sound_channel_stop(void)

{
  int iVar1;
  undefined8 uVar2;
  
  uVar2 = drv_index();
  iVar1 = (int)((ulonglong)uVar2 >> 0x20);
  if (-1 < (int)(uint)uVar2) {
    drv_play_sample((uint)uVar2 & 0xff,iVar1,(iVar1 + 1) * 0x1000 + 0xff,0,0,0,0,0,0,0);
  }
  return;
}


// ================================================================================================
// sound_fade @ 0x8fcdf [__watcall]
// ================================================================================================

void __watcall sound_fade(undefined4 param_1,int unaff_EDX,int unaff_EBX)

{
  uint uVar1;
  int iVar2;
  undefined8 uVar3;
  
  if (unaff_EBX == 0) {
    sound_channel_stop();
  }
  else {
    uVar3 = drv_index();
    uVar1 = (uint)uVar3;
    if (-1 < (int)uVar1) {
      iVar2 = sub_971f8(uVar1 & 0xff,(int)((ulonglong)uVar3 >> 0x20) * 0x10000 + 10);
      (&unk_f2300)[unaff_EDX * 5] = iVar2 << 0x18;
      (&unk_f2304)[unaff_EDX * 5] = (iVar2 * 0x1020408) / unaff_EBX;
      (&unk_f22fc)[unaff_EDX * 5] = iVar2;
      (&unk_f2308)[unaff_EDX * 5] = param_1;
      *(uint *)(&unk_f230c + unaff_EDX * 0x14) = uVar1;
    }
  }
  return;
}


// ================================================================================================
// sub_8fd67 @ 0x8fd67 [__watcall]
// ================================================================================================

void __watcall
sub_8fd67(undefined4 param_1,undefined4 param_2,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  uint uVar1;
  undefined8 uVar2;
  
  uVar2 = drv_index();
  uVar1 = (uint)uVar2;
  if (-1 < (int)uVar1) {
    sub_971f8(uVar1 & 0xff,(int)((ulonglong)uVar2 >> 0x20) * 0x10000 + 0x33,uVar1,unaff_ECX,
              unaff_EBX);
  }
  return;
}


// ================================================================================================
// sub_8fd84 @ 0x8fd84 [__watcall]
// ================================================================================================

void __watcall sub_8fd84(uint param_1,byte unaff_DL,undefined unaff_BL)

{
  byte local_4;
  undefined local_3;
  
  if (((int)param_1 < dword_d4f64) && (-1 < (int)param_1)) {
    local_4 = unaff_DL | 0xc0;
    local_3 = unaff_BL;
    snd_queue_message(param_1 & 0xff,2,&local_4);
  }
  return;
}


// ================================================================================================
// sub_8fdb2 @ 0x8fdb2 [__watcall]
// ================================================================================================

void __watcall sub_8fdb2(uint param_1,byte unaff_DL,undefined unaff_BL)

{
  byte local_4 [4];
  
  if (((int)param_1 < dword_d4f64) && (-1 < (int)param_1)) {
    local_4[0] = unaff_DL | 0xb0;
    local_4[1] = 7;
    local_4[2] = unaff_BL;
    snd_queue_message(param_1 & 0xff,3,local_4);
  }
  return;
}


// ================================================================================================
// sub_8fde5 @ 0x8fde5 [__watcall]
// ================================================================================================

void __watcall sub_8fde5(uint param_1,byte unaff_DL,byte unaff_BL)

{
  byte local_4 [4];
  
  if (((int)param_1 < dword_d4f64) && (-1 < (int)param_1)) {
    local_4[0] = unaff_DL | 0xe0;
    local_4[1] = 0;
    local_4[2] = unaff_BL & 0x7f;
    snd_queue_message(param_1 & 0xff,3,local_4);
  }
  return;
}


// ================================================================================================
// sub_8fe1c @ 0x8fe1c [__watcall]
// ================================================================================================

void __watcall sub_8fe1c(uint param_1,byte unaff_DL,undefined unaff_BL)

{
  byte local_4;
  undefined local_3;
  undefined local_2;
  
  if (((int)param_1 < dword_d4f64) && (-1 < (int)param_1)) {
    local_4 = unaff_DL | 0x90;
    local_2 = 0x7f;
    local_3 = unaff_BL;
    snd_queue_message(param_1 & 0xff,3,&local_4);
  }
  return;
}


// ================================================================================================
// sub_8fe4f @ 0x8fe4f [__watcall]
// ================================================================================================

void __watcall sub_8fe4f(uint param_1,byte unaff_DL,undefined unaff_BL)

{
  byte local_4;
  undefined local_3;
  undefined local_2;
  
  if (((int)param_1 < dword_d4f64) && (-1 < (int)param_1)) {
    local_4 = unaff_DL | 0x80;
    local_2 = 0;
    local_3 = unaff_BL;
    snd_queue_message(param_1 & 0xff,3,&local_4);
  }
  return;
}


// ================================================================================================
// sub_8fe83 @ 0x8fe83 [__watcall]
// ================================================================================================

void __watcall sub_8fe83(undefined param_1)

{
  byte_d41cd = param_1;
  return;
}


// ================================================================================================
// sub_8fe89 @ 0x8fe89 [__watcall]
// ================================================================================================

int __watcall sub_8fe89(int param_1,int unaff_EDX)

{
  int *piVar1;
  int *piVar2;
  uint uVar3;
  int iVar4;
  
  piVar1 = (int *)(param_1 + 6);
  uVar3 = (uint)*(ushort *)(param_1 + 4);
  iVar4 = 0;
  piVar2 = piVar1;
  while( true ) {
    if ((int)(uint)*(ushort *)(param_1 + 4) <= iVar4) {
      return 0;
    }
    if (unaff_EDX == *piVar2) break;
    iVar4 = iVar4 + 1;
    piVar2 = piVar2 + 1;
  }
  return (int)piVar1 + piVar1[uVar3 + iVar4] + uVar3 * 8;
}


// ================================================================================================
// sub_8fed2 @ 0x8fed2 [__watcall]
// ================================================================================================

void __watcall sub_8fed2(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX)

{
  undefined local_bc [136];
  undefined local_34 [16];
  undefined local_24 [12];
  undefined local_18 [12];
  
  sub_99a45(param_1,local_18,local_bc,local_34,local_24);
  sub_99af4(unaff_EBX,&unk_c3fd5,&unk_c3fd5,local_34,unaff_EDX);
  return;
}


// ================================================================================================
// sub_8ff1e @ 0x8ff1e [__watcall]
// ================================================================================================

void __watcall sub_8ff1e(int *param_1)

{
  if (*param_1 != 0) {
    freemem(*param_1);
    *param_1 = 0;
  }
  return;
}


// ================================================================================================
// sub_8ff3e @ 0x8ff3e [__watcall]
// ================================================================================================

void __watcall sub_8ff3e(int *param_1)

{
  if (*param_1 != 0) {
    releasememblock(*param_1);
    *param_1 = 0;
  }
  return;
}


// ================================================================================================
// sub_8ff5e @ 0x8ff5e [__watcall]
// ================================================================================================

undefined8 __watcall sub_8ff5e(uint param_1,undefined4 unaff_EDX)

{
  return CONCAT44(unaff_EDX,(param_1 & 0xff) * 0x100 + ((int)((param_1 >> 8 & 0xff) << 8) >> 8));
}


// ================================================================================================
// sub_8ff7c @ 0x8ff7c [__watcall]
// ================================================================================================

undefined8 __watcall sub_8ff7c(uint param_1,undefined4 unaff_EDX)

{
  return CONCAT44(unaff_EDX,
                  (param_1 >> 0x18) +
                  (param_1 & 0xff00) * 0x100 + param_1 * 0x1000000 + ((param_1 & 0xff0000) >> 8));
}


// ================================================================================================
// getpalette @ 0x8ffb0 [__cdecl]
// ================================================================================================

void getpalette(undefined param_1,int param_2,undefined *param_3)

{
  undefined uVar1;
  
  out(0x3c7,param_1);
  param_2 = param_2 * 3;
  do {
    uVar1 = in(0x3c9);
    *param_3 = uVar1;
    param_2 = param_2 + -1;
    param_3 = param_3 + 1;
  } while (param_2 != 0);
  return;
}


// ================================================================================================
// _cstart_ @ 0x8ffd4 [__watcall] noreturn
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall _cstart_(void)

{
  code *pcVar1;
  char cVar2;
  short sVar3;
  short extraout_CX;
  uint uVar4;
  int iVar5;
  short extraout_DX;
  char *pcVar6;
  undefined *puVar7;
  int iVar8;
  uint *puVar9;
  uint *puVar10;
  char *pcVar11;
  char *pcVar12;
  undefined4 *puVar13;
  undefined2 in_ES;
  undefined2 in_DS;
  short in_GS;
  bool bVar14;
  undefined8 uVar15;
  undefined2 in_stack_00000004;
  
  dword_d4ce4._0_2_ = 0x24;
  pcVar1 = (code *)swi(0x21);
  dword_d4cd8 = (undefined *)register0x00000010;
  dword_d4cec = (undefined *)register0x00000010;
  uVar15 = (*pcVar1)();
  iVar5 = (int)((ulonglong)uVar15 >> 0x20);
  byte_d4d0f = (undefined)uVar15;
  byte_d4d10 = (undefined)((ulonglong)uVar15 >> 8);
  iVar8 = 0;
  pcVar11 = (char *)0x81;
  sVar3 = (short)((ulonglong)uVar15 >> 0x10);
  if (sVar3 == 0x4458) {
    dword_d4cd8 = (undefined *)(_DAT_0000005c + 0xfffU & 0xfffff000);
    pcVar1 = (code *)swi(0x21);
    (*pcVar1)();
    word_d4d0d = 0x2c;
  }
  else {
    if (sVar3 != 0x4243) {
      pcVar1 = (code *)swi(0x21);
      cVar2 = (*pcVar1)();
      if (cVar2 == '\0') {
        word_d4d0d = 0x2c;
        in_stack_00000004 = 0;
        puVar7 = &stack0x00000008;
      }
      else {
        if (in_GS != 0) {
          word_d41f8 = in_GS;
        }
        pcVar1 = (code *)swi(0x31);
        (*pcVar1)();
        in_stack_00000004 = 1;
        puVar7 = &stack0x0000000c;
        dword_d4ce4._0_2_ = in_ES;
        word_d4d0d = _DAT_0000002c;
        if (extraout_DX != 0 || extraout_CX != 0) {
          in_stack_00000004 = 0x101;
          puVar7 = &stack0x0000000c;
        }
      }
      goto LAB_00090163;
    }
    pcVar1 = (code *)swi(0x21);
    dword_d41f4 = iVar5;
    (*pcVar1)();
    iVar5 = *(int *)(iVar5 + 0x10);
    pcVar11 = (char *)(iVar5 + 0x81);
    iVar8 = (uint)*(ushort *)(iVar5 + 0x2c) << 4;
    in_stack_00000004 = 9;
    dword_d4ce4._0_2_ = in_DS;
    word_d4d0d = in_DS;
  }
  puVar7 = &stack0x00000008;
LAB_00090163:
  byte_d4d06 = (char)in_stack_00000004;
  byte_d4d07 = (undefined)((ushort)in_stack_00000004 >> 8);
  *(int *)(puVar7 + -4) = iVar8;
  pcVar6 = &DAT_000f7b90;
  bVar14 = true;
  uVar4 = (uint)(byte)pcVar11[-1];
  do {
    pcVar12 = pcVar11;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar12 = pcVar11 + 1;
    bVar14 = *pcVar11 == ' ';
    pcVar11 = pcVar12;
  } while (bVar14);
  word_90048 = in_DS;
  dword_d4d09 = iVar8;
  if (!bVar14) {
    pcVar11 = pcVar12 + -1;
    for (iVar5 = uVar4 + 1; iVar5 != 0; iVar5 = iVar5 + -1) {
      *pcVar6 = *pcVar11;
      pcVar11 = pcVar11 + 1;
      pcVar6 = pcVar6 + 1;
    }
  }
  *pcVar6 = '\0';
  pcVar6[1] = '\0';
  puVar10 = *(uint **)(puVar7 + -4);
  *(char **)(puVar7 + -4) = pcVar6 + 1;
  *(uint *)(puVar7 + -8) = CONCAT22(0xf,in_DS);
  _word_d4d04 = 0;
  do {
    if (((*puVar10 | 0x20202020) == 0x37386f6e) && (*(char *)(puVar10 + 1) == '=')) {
      _word_d4d04 = _word_d4d04 + 1;
    }
    do {
      puVar9 = puVar10;
      puVar10 = (uint *)((int)puVar9 + 1);
    } while (*(char *)puVar9 != '\0');
  } while (*(char *)puVar10 != '\0');
  puVar10 = puVar9 + 1;
  pcVar11 = pcVar6 + 1;
  do {
    cVar2 = *(char *)puVar10;
    dword_d4ce8 = pcVar11 + 1;
    *pcVar11 = *(char *)puVar10;
    puVar10 = (uint *)((int)puVar10 + 1);
    pcVar11 = dword_d4ce8;
  } while (cVar2 != '\0');
  dword_d4ce0 = *(undefined4 *)(puVar7 + -4);
  uVar4 = 0x1f020;
  if (byte_d4d06 == '\x01') {
    uVar4 = 0x1000;
  }
  puVar13 = &font_kaufm;
  dword_d4cd4 = puVar7;
  for (uVar4 = uVar4 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *puVar13 = 0;
    puVar13 = puVar13 + 1;
  }
  for (iVar5 = 0; iVar5 != 0; iVar5 = iVar5 + -1) {
    *(undefined *)puVar13 = 0;
    puVar13 = (undefined4 *)((int)puVar13 + 1);
  }
  dword_d4cdc = &DAT_000f7b90;
  *(undefined4 *)(puVar7 + -4) = 0x9025e;
  sub_99c82(0xff);
                    /* WARNING: Subroutine does not return */
  *(code **)(puVar7 + -4) = sub_90265;
  __CMain();
}


// ================================================================================================
// FUN_0009004e @ 0x9004e noreturn
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall FUN_0009004e(void)

{
  code *pcVar1;
  char cVar2;
  short sVar3;
  short extraout_CX;
  uint uVar4;
  int iVar5;
  short extraout_DX;
  char *pcVar6;
  undefined *puVar7;
  int iVar8;
  uint *puVar9;
  uint *puVar10;
  char *pcVar11;
  char *pcVar12;
  undefined4 *puVar13;
  undefined2 in_ES;
  undefined2 in_DS;
  short in_GS;
  bool bVar14;
  undefined8 uVar15;
  undefined2 in_stack_00000004;
  
  dword_d4ce4._0_2_ = 0x24;
  pcVar1 = (code *)swi(0x21);
  dword_d4cd8 = (undefined *)register0x00000010;
  dword_d4cec = (undefined *)register0x00000010;
  uVar15 = (*pcVar1)();
  iVar5 = (int)((ulonglong)uVar15 >> 0x20);
  byte_d4d0f = (undefined)uVar15;
  byte_d4d10 = (undefined)((ulonglong)uVar15 >> 8);
  iVar8 = 0;
  pcVar11 = (char *)0x81;
  sVar3 = (short)((ulonglong)uVar15 >> 0x10);
  if (sVar3 == 0x4458) {
    dword_d4cd8 = (undefined *)(_DAT_0000005c + 0xfffU & 0xfffff000);
    pcVar1 = (code *)swi(0x21);
    (*pcVar1)();
    word_d4d0d = 0x2c;
  }
  else {
    if (sVar3 != 0x4243) {
      pcVar1 = (code *)swi(0x21);
      cVar2 = (*pcVar1)();
      if (cVar2 == '\0') {
        word_d4d0d = 0x2c;
        in_stack_00000004 = 0;
        puVar7 = &stack0x00000008;
      }
      else {
        if (in_GS != 0) {
          word_d41f8 = in_GS;
        }
        pcVar1 = (code *)swi(0x31);
        (*pcVar1)();
        in_stack_00000004 = 1;
        puVar7 = &stack0x0000000c;
        dword_d4ce4._0_2_ = in_ES;
        word_d4d0d = _DAT_0000002c;
        if (extraout_DX != 0 || extraout_CX != 0) {
          in_stack_00000004 = 0x101;
          puVar7 = &stack0x0000000c;
        }
      }
      goto LAB_00090163;
    }
    pcVar1 = (code *)swi(0x21);
    dword_d41f4 = iVar5;
    (*pcVar1)();
    iVar5 = *(int *)(iVar5 + 0x10);
    pcVar11 = (char *)(iVar5 + 0x81);
    iVar8 = (uint)*(ushort *)(iVar5 + 0x2c) << 4;
    in_stack_00000004 = 9;
    dword_d4ce4._0_2_ = in_DS;
    word_d4d0d = in_DS;
  }
  puVar7 = &stack0x00000008;
LAB_00090163:
  byte_d4d06 = (char)in_stack_00000004;
  byte_d4d07 = (undefined)((ushort)in_stack_00000004 >> 8);
  *(int *)(puVar7 + -4) = iVar8;
  pcVar6 = &DAT_000f7b90;
  bVar14 = true;
  uVar4 = (uint)(byte)pcVar11[-1];
  do {
    pcVar12 = pcVar11;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar12 = pcVar11 + 1;
    bVar14 = *pcVar11 == ' ';
    pcVar11 = pcVar12;
  } while (bVar14);
  word_90048 = in_DS;
  dword_d4d09 = iVar8;
  if (!bVar14) {
    pcVar11 = pcVar12 + -1;
    for (iVar5 = uVar4 + 1; iVar5 != 0; iVar5 = iVar5 + -1) {
      *pcVar6 = *pcVar11;
      pcVar11 = pcVar11 + 1;
      pcVar6 = pcVar6 + 1;
    }
  }
  *pcVar6 = '\0';
  pcVar6[1] = '\0';
  puVar10 = *(uint **)(puVar7 + -4);
  *(char **)(puVar7 + -4) = pcVar6 + 1;
  *(uint *)(puVar7 + -8) = CONCAT22(0xf,in_DS);
  _word_d4d04 = 0;
  do {
    if (((*puVar10 | 0x20202020) == 0x37386f6e) && (*(char *)(puVar10 + 1) == '=')) {
      _word_d4d04 = _word_d4d04 + 1;
    }
    do {
      puVar9 = puVar10;
      puVar10 = (uint *)((int)puVar9 + 1);
    } while (*(char *)puVar9 != '\0');
  } while (*(char *)puVar10 != '\0');
  puVar10 = puVar9 + 1;
  pcVar11 = pcVar6 + 1;
  do {
    cVar2 = *(char *)puVar10;
    dword_d4ce8 = pcVar11 + 1;
    *pcVar11 = *(char *)puVar10;
    puVar10 = (uint *)((int)puVar10 + 1);
    pcVar11 = dword_d4ce8;
  } while (cVar2 != '\0');
  dword_d4ce0 = *(undefined4 *)(puVar7 + -4);
  uVar4 = 0x1f020;
  if (byte_d4d06 == '\x01') {
    uVar4 = 0x1000;
  }
  puVar13 = &font_kaufm;
  dword_d4cd4 = puVar7;
  for (uVar4 = uVar4 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *puVar13 = 0;
    puVar13 = puVar13 + 1;
  }
  for (iVar5 = 0; iVar5 != 0; iVar5 = iVar5 + -1) {
    *(undefined *)puVar13 = 0;
    puVar13 = (undefined4 *)((int)puVar13 + 1);
  }
  dword_d4cdc = &DAT_000f7b90;
  *(undefined4 *)(puVar7 + -4) = 0x9025e;
  sub_99c82(0xff);
                    /* WARNING: Subroutine does not return */
  *(code **)(puVar7 + -4) = sub_90265;
  __CMain();
}


// ================================================================================================
// sub_90265 @ 0x90265 [__watcall] noreturn
// ================================================================================================

void __watcall
sub_90265(undefined4 param_1,undefined4 param_2,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  code *pcVar1;
  
  sub_99ccd(0,0xff,unaff_EBX,unaff_ECX,param_1);
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  return;
}


// ================================================================================================
// sub_90267 @ 0x90267 [__watcall] noreturn
// ================================================================================================

void __watcall sub_90267(undefined4 param_1,char *unaff_EDX)

{
  char cVar1;
  code *pcVar2;
  undefined2 uVar3;
  
  pcVar2 = (code *)swi(0x21);
  uVar3 = (*pcVar2)();
  do {
    cVar1 = *unaff_EDX;
    unaff_EDX = unaff_EDX + 1;
  } while (cVar1 != '\0');
  pcVar2 = (code *)swi(0x21);
  (*pcVar2)();
  sub_99ccd(0,0xff,uVar3);
  pcVar2 = (code *)swi(0x21);
  (*pcVar2)();
  return;
}


// ================================================================================================
// sub_902a0 @ 0x902a0 [__watcall]
// ================================================================================================

void __watcall sub_902a0(void)

{
  return;
}


// ================================================================================================
// _memset_fill @ 0x902b0 [__watcall]
// ================================================================================================

void __watcall _memset_fill(undefined *param_1,uint unaff_EDX,undefined4 param_3,uint unaff_ECX)

{
  undefined *puVar1;
  undefined uVar2;
  undefined6 uVar3;
  
  if (unaff_ECX != 0) {
    do {
      if (((uint)param_1 & 3) == 0) break;
      *param_1 = (char)unaff_EDX;
      param_1 = param_1 + 1;
      unaff_EDX = unaff_EDX >> 8 | unaff_EDX << 0x18;
      unaff_ECX = unaff_ECX - 1;
    } while (unaff_ECX != 0);
    uVar3 = _memset_dwords();
    puVar1 = (undefined *)uVar3;
    unaff_ECX = unaff_ECX & 3;
    if (unaff_ECX != 0) {
      uVar2 = (undefined)((uint6)uVar3 >> 0x20);
      *puVar1 = uVar2;
      if ((unaff_ECX != 1) && (puVar1[1] = (char)((uint6)uVar3 >> 0x28), unaff_ECX != 2)) {
        puVar1[2] = uVar2;
      }
    }
  }
  return;
}


// ================================================================================================
// _memset_dwords @ 0x902e7 [__watcall]
// ================================================================================================

undefined4 * __watcall
_memset_dwords(undefined4 *param_1,undefined4 unaff_EDX,undefined4 param_3,uint unaff_ECX)

{
  undefined4 *puVar1;
  int iVar2;
  
  puVar1 = param_1;
  if (unaff_ECX != 0) {
    do {
      if (((uint)param_1 & 0x1f) == 0) break;
      *param_1 = unaff_EDX;
      param_1 = param_1 + 1;
      unaff_ECX = unaff_ECX - 1;
    } while (unaff_ECX != 0);
    if (unaff_ECX >> 2 != 0) {
      iVar2 = (unaff_ECX >> 2) - 1;
      if (iVar2 != 0) {
        do {
          puVar1 = param_1;
          *puVar1 = unaff_EDX;
          puVar1[1] = unaff_EDX;
          puVar1[2] = unaff_EDX;
          puVar1[3] = unaff_EDX;
          if (iVar2 == 1) goto LAB_00090326;
          puVar1[4] = unaff_EDX;
          puVar1[5] = unaff_EDX;
          iVar2 = iVar2 + -2;
          puVar1[6] = unaff_EDX;
          puVar1[7] = unaff_EDX;
          param_1 = puVar1 + 8;
        } while (iVar2 != 0);
        puVar1 = puVar1 + 4;
LAB_00090326:
        param_1 = puVar1 + 4;
      }
      *param_1 = unaff_EDX;
      param_1[1] = unaff_EDX;
      param_1[2] = unaff_EDX;
      param_1[3] = unaff_EDX;
      param_1 = param_1 + 4;
    }
    unaff_ECX = unaff_ECX & 3;
    puVar1 = param_1;
    if (unaff_ECX != 0) {
      *param_1 = unaff_EDX;
      puVar1 = param_1 + 1;
      if (unaff_ECX != 1) {
        *puVar1 = unaff_EDX;
        puVar1 = param_1 + 2;
        if (unaff_ECX != 2) {
          *puVar1 = unaff_EDX;
          puVar1 = param_1 + 3;
        }
      }
    }
  }
  return puVar1;
}


// ================================================================================================
// shapecount @ 0x90354 [__cdecl]
// ================================================================================================

undefined4 shapecount(int param_1)

{
  return *(undefined4 *)(param_1 + 8);
}


// ================================================================================================
// getshape @ 0x9035c [__cdecl]
// ================================================================================================

int getshape(int param_1,uint param_2)

{
  if (param_2 < *(uint *)(param_1 + 8)) {
    return param_1 + *(int *)(param_1 + 0x14 + param_2 * 8);
  }
  return 0;
}


// ================================================================================================
// sub_90373 @ 0x90373 [__cdecl]
// ================================================================================================

void sub_90373(int param_1,uint param_2,undefined4 *param_3)

{
  if (param_2 < *(uint *)(param_1 + 8)) {
    *param_3 = *(undefined4 *)(param_1 + 0x10 + param_2 * 8);
    return;
  }
  *param_3 = 0;
  return;
}


// ================================================================================================
// strcpy @ 0x90392 [__watcall]
// ================================================================================================

char * __watcall strcpy(char *__dest,char *__src)

{
  char cVar1;
  char *pcVar2;
  
  pcVar2 = __dest;
  do {
    cVar1 = *__src;
    *pcVar2 = cVar1;
    if (cVar1 == '\0') {
      return __dest;
    }
    cVar1 = __src[1];
    __src = __src + 2;
    pcVar2[1] = cVar1;
    pcVar2 = pcVar2 + 2;
  } while (cVar1 != '\0');
  return __dest;
}


// ================================================================================================
// strcat @ 0x903b1 [__watcall]
// ================================================================================================

char * __watcall strcat(char *__dest,char *__src)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  char *pcVar4;
  
  iVar2 = -1;
  pcVar3 = __dest;
  do {
    pcVar4 = pcVar3;
    if (iVar2 == 0) break;
    iVar2 = iVar2 + -1;
    pcVar4 = pcVar3 + 1;
    cVar1 = *pcVar3;
    pcVar3 = pcVar4;
  } while (cVar1 != '\0');
  pcVar4 = pcVar4 + -1;
  do {
    cVar1 = *__src;
    *pcVar4 = cVar1;
    if (cVar1 == '\0') {
      return __dest;
    }
    cVar1 = __src[1];
    __src = __src + 2;
    pcVar4[1] = cVar1;
    pcVar4 = pcVar4 + 2;
  } while (cVar1 != '\0');
  return __dest;
}


// ================================================================================================
// sub_903e8 @ 0x903e8 [__watcall]
// ================================================================================================

int __watcall sub_903e8(char *__filename)

{
  code *pcVar1;
  int iVar2;
  byte in_CF;
  
  pcVar1 = (code *)swi(0x21);
  iVar2 = (*pcVar1)();
  if ((in_CF & 1) != 0) {
    iVar2 = sub_9a735((iVar2 << 1 | (uint)in_CF) >> 1 & 0xffff);
    return iVar2;
  }
  return 0;
}


// ================================================================================================
// drawshape @ 0x903f0 [__cdecl]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void drawshape(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  int local_24;
  uint local_20;
  int local_10;
  
  iVar2 = dword_d30d0;
  if (dword_d30c8 == 0) {
    sub_b5f0f(param_1,param_2,param_3);
  }
  else {
    iVar9 = param_1 + 0x10;
    local_10 = *(int *)(param_1 + 2) >> 0x10;
    local_24 = *(int *)(param_1 + 4) >> 0x10;
    iVar3 = dword_d30b0 - param_3;
    if (0 < iVar3) {
      iVar9 = iVar9 + local_10 * iVar3;
      local_24 = local_24 - iVar3;
      param_3 = param_3 + iVar3;
    }
    iVar3 = (param_3 + local_24) - dword_d30b8;
    if (0 < iVar3) {
      local_24 = local_24 - iVar3;
    }
    iVar4 = dword_d30ac - param_2;
    iVar3 = 0;
    if (0 < iVar4) {
      iVar9 = iVar9 + iVar4;
      local_10 = local_10 - iVar4;
      param_2 = param_2 + iVar4;
      iVar3 = iVar4;
    }
    iVar4 = (local_10 + param_2) - _dword_d30b4;
    if (0 < iVar4) {
      iVar3 = iVar3 + iVar4;
      local_10 = local_10 - iVar4;
    }
    iVar4 = (&unk_d3104)[param_3];
    iVar5 = dword_d30a4 - local_10;
    local_20 = (uint)(param_2 + iVar4) >> 0x10;
    sub_b5e00(local_20,iVar5,iVar3);
    uVar8 = param_2 + iVar4 & 0xffff;
    if (0 < local_10) {
      iVar4 = local_10 + iVar5;
      iVar1 = local_10 + iVar3;
      while (0 < local_24) {
        iVar7 = (&unk_d4108)[local_20] - param_3;
        if (local_24 < (&unk_d4108)[local_20] - param_3) {
          iVar7 = local_24;
        }
        if (iVar7 != 0) {
          param_3 = param_3 + iVar7;
          local_24 = local_24 - iVar7;
          do {
            (*(code *)funcptr_d43e4)(iVar9,iVar2 + uVar8,local_10);
            uVar8 = uVar8 + iVar4;
            iVar9 = iVar9 + iVar1;
            iVar7 = iVar7 + -1;
          } while (iVar7 != 0);
        }
        if (local_24 != 0) {
          if ((uVar8 & 0x10000) != 0) {
            uVar8 = uVar8 & 0xffff;
            local_20 = local_20 + 1;
            sub_b5e00(local_20);
          }
          uVar6 = local_10 + uVar8;
          if ((uVar6 - 1 & 0x10000) == 0) {
            (*(code *)funcptr_d43e4)(iVar9,iVar2 + uVar8,local_10);
            iVar9 = iVar9 + local_10;
          }
          else {
            (*(code *)funcptr_d43e4)(iVar9,iVar2 + uVar8,0x10000 - uVar8);
            iVar9 = iVar9 + (0x10000 - uVar8);
            uVar6 = uVar6 & 0xffff;
            local_20 = local_20 + 1;
            sub_b5e00(local_20);
            (*(code *)funcptr_d43e4)(iVar9,iVar2,uVar6);
            iVar9 = iVar9 + uVar6;
          }
          uVar8 = uVar6 + iVar5;
          iVar9 = iVar9 + iVar3;
          if ((uVar8 & 0x10000) != 0) {
            uVar8 = uVar8 & 0xffff;
            local_20 = local_20 + 1;
            sub_b5e00(local_20);
          }
          local_24 = local_24 + -1;
          param_3 = param_3 + 1;
        }
      }
    }
  }
  return;
}


// ================================================================================================
// drawshape_home @ 0x9061c [__cdecl]
// ================================================================================================

void drawshape_home(int param_1)

{
  drawshape(param_1,*(int *)(param_1 + 10) >> 0x10,*(int *)(param_1 + 0xc) >> 0x10);
  return;
}


// ================================================================================================
// sub_90638 @ 0x90638 [__cdecl]
// ================================================================================================

void sub_90638(int param_1,int param_2,int param_3)

{
  drawshape(param_1,param_2 - (*(int *)(param_1 + 6) >> 0x10),
            param_3 - (*(int *)(param_1 + 8) >> 0x10));
  return;
}


// ================================================================================================
// sub_90660 @ 0x90660 [__cdecl]
// ================================================================================================

void sub_90660(uint *param_1,uint *param_2,uint param_3)

{
  int iVar1;
  
  iVar1 = (int)param_3 >> 2;
  while (iVar1 = iVar1 + -1, iVar1 != -1) {
    *param_2 = *param_2 ^ *param_1;
    param_2 = param_2 + 1;
    param_1 = param_1 + 1;
  }
  param_3 = param_3 & 3;
  while (param_3 = param_3 - 1, param_3 != 0xffffffff) {
    *(byte *)param_2 = *(byte *)param_2 ^ *(byte *)param_1;
    param_2 = (uint *)((int)param_2 + 1);
    param_1 = (uint *)((int)param_1 + 1);
  }
  return;
}


// ================================================================================================
// sub_90698 @ 0x90698 [__cdecl]
// ================================================================================================

void sub_90698(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  if (dword_d30c8 == 0) {
    sub_b608b(param_1,param_2,param_3);
    return;
  }
  funcptr_d43e4 = sub_90660;
  drawshape(param_1,param_2,param_3);
  funcptr_d43e4 = sub_b3abc;
  return;
}


// ================================================================================================
// sub_906dc @ 0x906dc [__cdecl]
// ================================================================================================

void sub_906dc(int param_1)

{
  sub_90698(param_1,*(int *)(param_1 + 10) >> 0x10,*(int *)(param_1 + 0xc) >> 0x10);
  return;
}


// ================================================================================================
// sub_906f8 @ 0x906f8 [__cdecl]
// ================================================================================================

void sub_906f8(int param_1,int param_2,int param_3)

{
  sub_90698(param_1,param_2 - (*(int *)(param_1 + 6) >> 0x10),
            param_3 - (*(int *)(param_1 + 8) >> 0x10));
  return;
}


// ================================================================================================
// sub_90720 @ 0x90720 [__cdecl]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_90720(int param_1,int param_2,int param_3)

{
  undefined uVar1;
  int iVar2;
  undefined *puVar3;
  int iVar4;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  
  if (dword_d30c8 == 0) {
    sub_b6217(param_1,param_2,param_3);
  }
  else {
    puVar3 = (undefined *)(param_1 + 0x10);
    local_14 = *(int *)(param_1 + 2) >> 0x10;
    local_10 = *(int *)(param_1 + 4) >> 0x10;
    local_1c = param_2;
    local_18 = 0;
    iVar2 = dword_d30b0 - param_3;
    if (0 < iVar2) {
      puVar3 = puVar3 + local_14 * iVar2;
      local_10 = local_10 - iVar2;
      param_3 = param_3 + iVar2;
    }
    iVar2 = (param_3 + local_10) - dword_d30b8;
    if (0 < iVar2) {
      local_10 = local_10 - iVar2;
    }
    iVar2 = dword_d30ac - param_2;
    if (0 < iVar2) {
      puVar3 = puVar3 + iVar2;
      local_14 = local_14 - iVar2;
      local_1c = param_2 + iVar2;
      local_18 = iVar2;
    }
    iVar2 = (local_1c + local_14) - _dword_d30b4;
    if (0 < iVar2) {
      local_18 = local_18 + iVar2;
      local_14 = local_14 - iVar2;
    }
    if ((0 < local_14) && (0 < local_10)) {
      while (local_10 = local_10 + -1, iVar2 = local_1c, iVar4 = local_14, local_10 != -1) {
        while (iVar4 + -1 != -1) {
          uVar1 = *puVar3;
          puVar3 = puVar3 + 1;
          sub_b63ac(iVar2,param_3,uVar1);
          iVar2 = iVar2 + 1;
          iVar4 = iVar4 + -1;
        }
        param_3 = param_3 + 1;
        puVar3 = puVar3 + local_18;
      }
    }
  }
  return;
}


// ================================================================================================
// sub_90838 @ 0x90838 [__cdecl]
// ================================================================================================

void sub_90838(int param_1)

{
  sub_90720(param_1,*(int *)(param_1 + 10) >> 0x10,*(int *)(param_1 + 0xc) >> 0x10);
  return;
}


// ================================================================================================
// sub_90854 @ 0x90854 [__cdecl]
// ================================================================================================

void sub_90854(int param_1,int param_2,int param_3)

{
  sub_90720(param_1,param_2 - (*(int *)(param_1 + 6) >> 0x10),
            param_3 - (*(int *)(param_1 + 8) >> 0x10));
  return;
}


// ================================================================================================
// sub_9087c @ 0x9087c [__cdecl]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_9087c(int param_1,int param_2,int param_3)

{
  undefined uVar1;
  int iVar2;
  undefined *puVar3;
  int iVar4;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  
  if (dword_d30c8 != 0) {
    puVar3 = (undefined *)(param_1 + 0x10);
    local_14 = *(int *)(param_1 + 2) >> 0x10;
    local_10 = *(int *)(param_1 + 4) >> 0x10;
    local_1c = param_2;
    local_18 = 0;
    iVar2 = dword_d30b0 - param_3;
    if (0 < iVar2) {
      puVar3 = puVar3 + local_14 * iVar2;
      local_10 = local_10 - iVar2;
      param_3 = param_3 + iVar2;
    }
    iVar2 = (param_3 + local_10) - dword_d30b8;
    if (0 < iVar2) {
      local_10 = local_10 - iVar2;
    }
    iVar2 = dword_d30ac - param_2;
    if (0 < iVar2) {
      puVar3 = puVar3 + iVar2;
      local_14 = local_14 - iVar2;
      local_1c = param_2 + iVar2;
      local_18 = iVar2;
    }
    iVar2 = (local_1c + local_14) - _dword_d30b4;
    if (0 < iVar2) {
      local_18 = local_18 + iVar2;
      local_14 = local_14 - iVar2;
    }
    if ((0 < local_14) && (0 < local_10)) {
      while (local_10 = local_10 + -1, iVar2 = local_1c, iVar4 = local_14, local_10 != -1) {
        while (iVar4 + -1 != -1) {
          uVar1 = *puVar3;
          puVar3 = puVar3 + 1;
          sub_b65b8(iVar2,param_3,uVar1);
          iVar2 = iVar2 + 1;
          iVar4 = iVar4 + -1;
        }
        param_3 = param_3 + 1;
        puVar3 = puVar3 + local_18;
      }
    }
    return;
  }
  sub_b6423(param_1,param_2,param_3);
  return;
}


// ================================================================================================
// sub_9099c @ 0x9099c [__cdecl]
// ================================================================================================

void sub_9099c(int param_1)

{
  sub_9087c(param_1,*(int *)(param_1 + 10) >> 0x10,*(int *)(param_1 + 0xc) >> 0x10);
  return;
}


// ================================================================================================
// sub_909b8 @ 0x909b8 [__cdecl]
// ================================================================================================

void sub_909b8(int param_1,int param_2,int param_3)

{
  sub_9087c(param_1,param_2 - (*(int *)(param_1 + 6) >> 0x10),
            param_3 - (*(int *)(param_1 + 8) >> 0x10));
  return;
}


// ================================================================================================
// sub_909e0 @ 0x909e0 [__watcall]
// ================================================================================================

int __watcall sub_909e0(byte *param_1,byte *unaff_EDX,int unaff_EBX)

{
  byte bVar1;
  byte local_8;
  
  while( true ) {
    if (unaff_EBX == 0) {
      return 0;
    }
    local_8 = *unaff_EDX;
    bVar1 = *param_1;
    if ((0x40 < bVar1) && (bVar1 < 0x5b)) {
      bVar1 = bVar1 + 0x20;
    }
    if ((0x40 < local_8) && (local_8 < 0x5b)) {
      local_8 = local_8 + 0x20;
    }
    if (bVar1 != local_8) break;
    if (local_8 == 0) {
      return 0;
    }
    param_1 = param_1 + 1;
    unaff_EDX = unaff_EDX + 1;
    unaff_EBX = unaff_EBX + -1;
  }
  return (uint)bVar1 - (uint)local_8;
}


// ================================================================================================
// textwidthn @ 0x90a40 [__cdecl]
// ================================================================================================

int textwidthn(char *param_1,int param_2)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = 0;
  cVar1 = *param_1;
  for (; (cVar1 != '\0' && (param_2 != 0)); param_2 = param_2 + -1) {
    uVar3 = (uint)(byte)(*param_1 - byte_d42c0);
    if ((int)uVar3 < (int)(((uint)byte_d42c1 - (uint)byte_d42c0) + 1)) {
      if (dword_d42d0 == 0) {
        if (off_d42c8 == (undefined *)0x0) {
          uVar3 = (uint)byte_d42c2;
        }
        else {
          uVar3 = (uint)(byte)off_d42c8[uVar3];
        }
        uVar3 = byte_d42c4 + uVar3;
      }
      else {
        uVar3 = (uint)*(byte *)(dword_d42d0 + uVar3);
      }
      iVar2 = iVar2 + uVar3;
    }
    param_1 = param_1 + 1;
    cVar1 = *param_1;
  }
  return iVar2;
}


// ================================================================================================
// textwidth @ 0x90ac4 [__cdecl]
// ================================================================================================

void textwidth(undefined4 param_1)

{
  textwidthn(param_1,0x200);
  return;
}


// ================================================================================================
// sub_90ad7 @ 0x90ad7 [__watcall]
// ================================================================================================

void __watcall sub_90ad7(int *param_1,undefined unaff_DL)

{
  undefined *puVar1;
  
  puVar1 = (undefined *)*param_1;
  *param_1 = (int)(puVar1 + 1);
  *puVar1 = unaff_DL;
  param_1[4] = param_1[4] + 1;
  return;
}


// ================================================================================================
// sprintf @ 0x90aea [__cdecl]
// ================================================================================================

int sprintf(char *__s,char *__format,...)

{
  int iVar1;
  undefined *local_10 [3];
  
  local_10[0] = &stack0x0000000c;
  iVar1 = __prtf(__s,__format,local_10,sub_90ad7);
  __s[iVar1] = '\0';
  return iVar1;
}


// ================================================================================================
// memcpy @ 0x90b20 [__watcall]
// ================================================================================================

void * __watcall memcpy(void *__dest,void *__src,size_t __n)

{
  uint uVar1;
  undefined4 *puVar2;
  
  puVar2 = (undefined4 *)__dest;
                    /* WARNING: Load size is inaccurate */
  for (uVar1 = __n >> 2; uVar1 != 0; uVar1 = uVar1 - 1) {
    *puVar2 = *__src;
    __src = (undefined4 *)((int)__src + 4);
    puVar2 = puVar2 + 1;
  }
                    /* WARNING: Load size is inaccurate */
  for (uVar1 = __n & 3; uVar1 != 0; uVar1 = uVar1 - 1) {
    *(undefined *)puVar2 = *__src;
    __src = (undefined4 *)((int)__src + 1);
    puVar2 = (undefined4 *)((int)puVar2 + 1);
  }
  return __dest;
}


// ================================================================================================
// sub_90b50 @ 0x90b50 [__watcall]
// ================================================================================================

void __watcall sub_90b50(void)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 in_stack_00000004;
  char *in_stack_00000008;
  undefined4 *in_stack_0000000c;
  
  cVar1 = *in_stack_00000008;
  while (cVar1 != '\0') {
    uVar2 = locateshape_fast(in_stack_00000004,in_stack_00000008);
    *in_stack_0000000c = uVar2;
    in_stack_0000000c = in_stack_0000000c + 1;
    in_stack_00000008 = in_stack_00000008 + 4;
    cVar1 = *in_stack_00000008;
  }
  return;
}


// ================================================================================================
// locateshapes @ 0x90b80 [__cdecl]
// ================================================================================================

void locateshapes(undefined4 param_1,char *param_2,undefined4 *param_3)

{
  char cVar1;
  undefined4 uVar2;
  
  cVar1 = *param_2;
  while (cVar1 != '\0') {
    uVar2 = locateshape(param_1,param_2);
    *param_3 = uVar2;
    param_3 = param_3 + 1;
    param_2 = param_2 + 4;
    cVar1 = *param_2;
  }
  return;
}


// ================================================================================================
// _dos_findfirst @ 0x90bb0 [__watcall]
// ================================================================================================

void __watcall
_dos_findfirst(undefined4 param_1,undefined4 param_2,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  code *pcVar1;
  undefined4 uVar2;
  
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)(param_1,unaff_ECX);
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  uVar2 = sub_9a716();
  sub_90bec(uVar2,unaff_EBX);
  return;
}


// ================================================================================================
// _dos_findnext @ 0x90bcd [__watcall]
// ================================================================================================

void __watcall _dos_findnext(void)

{
  code *pcVar1;
  
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  sub_90c0f();
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  sub_9a716();
  sub_90bec();
  return;
}


// ================================================================================================
// sub_90be9 @ 0x90be9 [__watcall]
// ================================================================================================

undefined4 __watcall sub_90be9(void)

{
  return 0;
}


// ================================================================================================
// sub_90bec @ 0x90bec [__watcall]
// ================================================================================================

undefined4 __watcall sub_90bec(undefined4 param_1,undefined4 param_2,undefined *unaff_EBX)

{
  code *pcVar1;
  int iVar2;
  undefined *extraout_EDX;
  undefined *puVar3;
  byte bVar4;
  undefined4 unaff_retaddr;
  
  bVar4 = 0;
  if (byte_d4d06 == '\t') {
    pcVar1 = (code *)swi(0x21);
    (*pcVar1)();
    puVar3 = extraout_EDX;
    for (iVar2 = 0x2b; param_1 = unaff_retaddr, iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = *unaff_EBX;
      unaff_EBX = unaff_EBX + (uint)bVar4 * -2 + 1;
      puVar3 = puVar3 + (uint)bVar4 * -2 + 1;
    }
  }
  return param_1;
}


// ================================================================================================
// sub_90c0f @ 0x90c0f [__watcall]
// ================================================================================================

undefined4 __watcall sub_90c0f(undefined4 param_1,undefined4 param_2,undefined *unaff_EBX)

{
  code *pcVar1;
  int iVar2;
  undefined *extraout_EDX;
  undefined *puVar3;
  byte bVar4;
  undefined4 unaff_retaddr;
  
  bVar4 = 0;
  if (byte_d4d06 == '\t') {
    pcVar1 = (code *)swi(0x21);
    (*pcVar1)();
    puVar3 = extraout_EDX;
    for (iVar2 = 0x2b; param_1 = unaff_retaddr, iVar2 != 0; iVar2 = iVar2 + -1) {
      *unaff_EBX = *puVar3;
      puVar3 = puVar3 + (uint)bVar4 * -2 + 1;
      unaff_EBX = unaff_EBX + (uint)bVar4 * -2 + 1;
    }
  }
  return param_1;
}


// ================================================================================================
// rmdir @ 0x90c32 [__watcall]
// ================================================================================================

int __watcall rmdir(char *__path)

{
  code *pcVar1;
  int iVar2;
  byte in_CF;
  
  pcVar1 = (code *)swi(0x21);
  iVar2 = (*pcVar1)();
  if ((in_CF & 1) != 0) {
    iVar2 = sub_9a735((iVar2 << 1 | (uint)in_CF) >> 1 & 0xffff);
    return iVar2;
  }
  return 0;
}


// ================================================================================================
// close @ 0x90c52 [__watcall]
// ================================================================================================

int __watcall close(int __fd)

{
  code *pcVar1;
  int iVar2;
  undefined8 uVar3;
  
  pcVar1 = (code *)swi(0x21);
  uVar3 = (*pcVar1)();
  iVar2 = sub_9a716((int)uVar3,(int)((ulonglong)uVar3 >> 0x20),__fd & 0xffff);
  return iVar2;
}


// ================================================================================================
// sub_90c61 @ 0x90c61 [__watcall]
// ================================================================================================

void __watcall sub_90c61(undefined2 param_1)

{
  code *pcVar1;
  undefined2 uVar2;
  undefined4 extraout_EDX;
  
  pcVar1 = (code *)swi(0x21);
  uVar2 = (*pcVar1)();
  sub_9a716(uVar2,extraout_EDX,param_1);
  return;
}


// ================================================================================================
// open @ 0x90c71 [__watcall]
// ================================================================================================

int __watcall open(char *__file,int __oflag,...)

{
  code *pcVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 *unaff_EBX;
  undefined in_CF;
  
  pcVar1 = (code *)swi(0x21);
  uVar2 = (*pcVar1)();
  if (!(bool)in_CF) {
    *unaff_EBX = uVar2;
  }
  iVar3 = sub_9a716();
  return iVar3;
}


// ================================================================================================
// creat @ 0x90c80 [__watcall]
// ================================================================================================

int __watcall creat(char *__file,__mode_t __mode)

{
  code *pcVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 *unaff_EBX;
  undefined in_CF;
  
  pcVar1 = (code *)swi(0x21);
  uVar2 = (*pcVar1)();
  if (!(bool)in_CF) {
    *unaff_EBX = uVar2;
  }
  iVar3 = sub_9a716();
  return iVar3;
}


// ================================================================================================
// sub_90c94 @ 0x90c94 [__watcall]
// ================================================================================================

void __watcall sub_90c94(undefined4 param_1,undefined4 param_2,undefined4 *unaff_EBX)

{
  code *pcVar1;
  undefined4 uVar2;
  undefined in_CF;
  
  pcVar1 = (code *)swi(0x21);
  uVar2 = (*pcVar1)();
  if (!(bool)in_CF) {
    *unaff_EBX = uVar2;
  }
  sub_9a716();
  return;
}


// ================================================================================================
// lseek @ 0x90ca8 [__watcall]
// ================================================================================================

__off_t __watcall lseek(int __fd,__off_t __offset,int __whence)

{
  code *pcVar1;
  __off_t unaff_EDI;
  byte bVar2;
  undefined8 uVar3;
  
  bVar2 = ((uint)__offset >> 0xf & 1) != 0;
  pcVar1 = (code *)swi(0x21);
  uVar3 = (*pcVar1)();
  if ((bVar2 & 1) != 0) {
    sub_9a735(((int)uVar3 << 1 | (uint)bVar2) >> 1 & 0xffff,(int)((ulonglong)uVar3 >> 0x20),__fd);
    unaff_EDI = -1;
  }
  return unaff_EDI;
}


// ================================================================================================
// read_bytes @ 0x90cea [__watcall]
// ================================================================================================

void __watcall read_bytes(undefined4 *param_1)

{
  code *pcVar1;
  undefined in_CF;
  undefined8 uVar2;
  undefined4 *in_stack_00000008;
  
  pcVar1 = (code *)swi(0x21);
  uVar2 = (*pcVar1)(0x3f00);
  if (!(bool)in_CF) {
    *in_stack_00000008 = (int)uVar2;
    param_1 = in_stack_00000008;
  }
  sub_9a716((int)uVar2,(int)((ulonglong)uVar2 >> 0x20),param_1);
  return;
}


// ================================================================================================
// sub_90d14 @ 0x90d14 [__watcall]
// ================================================================================================

void __watcall sub_90d14(undefined4 *param_1)

{
  code *pcVar1;
  undefined in_CF;
  undefined8 uVar2;
  undefined4 *in_stack_00000008;
  
  pcVar1 = (code *)swi(0x21);
  uVar2 = (*pcVar1)(0x4000);
  if (!(bool)in_CF) {
    *in_stack_00000008 = (int)uVar2;
    param_1 = in_stack_00000008;
  }
  sub_9a716((int)uVar2,(int)((ulonglong)uVar2 >> 0x20),param_1);
  return;
}


// ================================================================================================
// fillrect @ 0x90d20 [__cdecl]
// ================================================================================================

void fillrect(int param_1,int param_2,int param_3,int param_4,undefined4 param_5)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  int local_1c;
  uint local_18;
  
  iVar1 = dword_d30d0;
  if ((0 < param_3) && (0 < param_4)) {
    if (dword_d30c8 == 0) {
      sub_b6665(param_1,param_2,param_3,param_4,param_5);
    }
    else {
      iVar4 = (&unk_d3104)[param_2];
      iVar2 = dword_d30a4 - param_3;
      local_18 = (uint)(param_1 + iVar4) >> 0x10;
      sub_b5e00(local_18);
      uVar3 = param_1 + iVar4 & 0xffff;
      local_1c = param_4;
      if (0 < param_4) {
        do {
          iVar4 = (&unk_d4108)[local_18] - param_2;
          if (local_1c < (&unk_d4108)[local_18] - param_2) {
            iVar4 = local_1c;
          }
          if (iVar4 != 0) {
            param_2 = param_2 + iVar4;
            local_1c = local_1c - iVar4;
            do {
              sub_b3fb0(iVar1 + uVar3,param_3,param_5);
              uVar3 = uVar3 + param_3 + iVar2;
              iVar4 = iVar4 + -1;
            } while (iVar4 != 0);
          }
          if (local_1c != 0) {
            if ((uVar3 & 0x10000) != 0) {
              uVar3 = uVar3 & 0xffff;
              local_18 = local_18 + 1;
              sub_b5e00(local_18);
            }
            uVar5 = param_3 + uVar3;
            if ((uVar5 & 0x10000) == 0) {
              sub_b3fb0(iVar1 + uVar3,param_3,param_5);
            }
            else {
              sub_b3fb0(iVar1 + uVar3,0x10000 - uVar3,param_5);
              uVar5 = uVar5 & 0xffff;
              local_18 = local_18 + 1;
              sub_b5e00(local_18);
              sub_b3fb0(iVar1,uVar5,param_5);
            }
            uVar3 = uVar5 + iVar2;
            if ((uVar3 & 0x10000) != 0) {
              uVar3 = uVar3 & 0xffff;
              local_18 = local_18 + 1;
              sub_b5e00(local_18);
            }
            local_1c = local_1c + -1;
            param_2 = param_2 + 1;
          }
        } while (0 < local_1c);
      }
    }
  }
  return;
}


// ================================================================================================
// sub_90ec0 @ 0x90ec0 [__cdecl]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_90ec0(int param_1,int param_2,int param_3,int param_4,undefined4 param_5)

{
  int iVar1;
  
  iVar1 = dword_d30b0 - param_2;
  if (0 < iVar1) {
    param_4 = param_4 - iVar1;
    param_2 = param_2 + iVar1;
  }
  iVar1 = (param_2 + param_4) - dword_d30b8;
  if (0 < iVar1) {
    param_4 = param_4 - iVar1;
  }
  iVar1 = dword_d30ac - param_1;
  if (0 < iVar1) {
    param_3 = param_3 - iVar1;
    param_1 = param_1 + iVar1;
  }
  iVar1 = (param_1 + param_3) - _dword_d30b4;
  if (0 < iVar1) {
    param_3 = param_3 - iVar1;
  }
  if ((0 < param_3) && (0 < param_4)) {
    fillrect(param_1,param_2,param_3,param_4,param_5);
  }
  return;
}


// ================================================================================================
// sub_90f2c @ 0x90f2c [__watcall]
// ================================================================================================

void __watcall sub_90f2c(byte *param_1,int unaff_EDX,byte unaff_BL)

{
  while (unaff_EDX = unaff_EDX + -1, unaff_EDX != -1) {
    *param_1 = *param_1 ^ unaff_BL;
    param_1 = param_1 + 1;
  }
  return;
}


// ================================================================================================
// fillrect2 @ 0x90f38 [__cdecl]
// ================================================================================================

void fillrect2(int param_1,int param_2,int param_3,int param_4,uint param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  undefined4 local_10;
  
  iVar1 = dword_d30d0;
  if ((0 < param_3) && (0 < param_4)) {
    if (dword_d30c8 == 0) {
      sub_b677d(param_1,param_2,param_3,param_4,param_5);
    }
    else {
      uVar5 = dword_d30a4 * param_2 + param_1;
      iVar2 = dword_d30a4 - param_3;
      uVar6 = uVar5 >> 0x10;
      sub_b5e00(uVar6);
      uVar5 = uVar5 & 0xffff;
      local_10 = param_4;
      if (0 < param_4) {
        do {
          uVar4 = param_3 + uVar5;
          iVar3 = iVar1 + uVar5;
          if ((uVar4 & 0x10000) == 0) {
            sub_90f2c(iVar3,param_3,param_5 & 0xff);
          }
          else {
            sub_90f2c(iVar3,0x10000 - uVar5,param_5 & 0xff);
            uVar4 = uVar4 & 0xffff;
            uVar6 = uVar6 + 1;
            sub_b5e00(uVar6);
            sub_90f2c(iVar1,uVar4,param_5 & 0xff);
          }
          uVar5 = uVar4 + iVar2;
          if ((uVar5 & 0x10000) != 0) {
            uVar5 = uVar5 & 0xffff;
            uVar6 = uVar6 + 1;
            sub_b5e00(uVar6);
          }
          local_10 = local_10 + -1;
        } while (0 < local_10);
      }
    }
  }
  return;
}


// ================================================================================================
// sub_91044 @ 0x91044 [__cdecl]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_91044(int param_1,int param_2,int param_3,int param_4,undefined4 param_5)

{
  int iVar1;
  
  iVar1 = dword_d30b0 - param_2;
  if (0 < iVar1) {
    param_4 = param_4 - iVar1;
    param_2 = param_2 + iVar1;
  }
  iVar1 = (param_2 + param_4) - dword_d30b8;
  if (0 < iVar1) {
    param_4 = param_4 - iVar1;
  }
  iVar1 = dword_d30ac - param_1;
  if (0 < iVar1) {
    param_3 = param_3 - iVar1;
    param_1 = param_1 + iVar1;
  }
  iVar1 = (param_1 + param_3) - _dword_d30b4;
  if (0 < iVar1) {
    param_3 = param_3 - iVar1;
  }
  if ((0 < param_3) && (0 < param_4)) {
    fillrect2(param_1,param_2,param_3,param_4,param_5);
  }
  return;
}


// ================================================================================================
// sub_910b0 @ 0x910b0 [__cdecl]
// ================================================================================================

void sub_910b0(undefined4 param_1)

{
  undefined auStack_60 [96];
  
  sub_b3a88(auStack_60);
  setdefaultscreen();
  clearclip(param_1);
  sub_b3aa1(auStack_60);
  return;
}


// ================================================================================================
// drawshape2 @ 0x910e0 [__cdecl]
// ================================================================================================

void drawshape2(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  int local_1c;
  uint local_10;
  
  if (dword_d30c8 == 0) {
    sub_b6887(param_1,param_2,param_3);
  }
  else {
    iVar6 = param_1 + 0x10;
    local_1c = *(int *)(param_1 + 4) >> 0x10;
    iVar2 = *(int *)(param_1 + 2) >> 0x10;
    iVar1 = (&unk_d3104)[param_3];
    iVar3 = dword_d30a4 - iVar2;
    local_10 = (uint)(iVar1 + param_2) >> 0x10;
    iVar7 = dword_d30d0;
    sub_b5e00(local_10,iVar3,dword_d30d0);
    uVar5 = iVar1 + param_2 & 0xffff;
    if (0 < iVar2) {
      for (; 0 < local_1c; local_1c = local_1c + -1) {
        uVar4 = iVar2 + uVar5;
        if ((uVar4 & 0x10000) == 0) {
          (*(code *)funcptr_d43e4)(iVar6,iVar7 + uVar5,iVar2);
          iVar6 = iVar6 + iVar2;
        }
        else {
          (*(code *)funcptr_d43e4)(iVar6,iVar7 + uVar5,0x10000 - uVar5);
          iVar6 = iVar6 + (0x10000 - uVar5);
          uVar4 = uVar4 & 0xffff;
          local_10 = local_10 + 1;
          sub_b5e00(local_10);
          (*(code *)funcptr_d43e4)(iVar6,iVar7,uVar4);
          iVar6 = iVar6 + uVar4;
        }
        uVar5 = uVar4 + iVar3;
        if ((uVar5 & 0x10000) != 0) {
          uVar5 = uVar5 & 0xffff;
          local_10 = local_10 + 1;
          sub_b5e00(local_10);
        }
      }
    }
  }
  return;
}


// ================================================================================================
// drawshape2_home @ 0x9121c [__cdecl]
// ================================================================================================

void drawshape2_home(int param_1)

{
  drawshape2(param_1,*(int *)(param_1 + 10) >> 0x10,*(int *)(param_1 + 0xc) >> 0x10);
  return;
}


// ================================================================================================
// sub_91238 @ 0x91238 [__cdecl]
// ================================================================================================

void sub_91238(int param_1,int param_2,int param_3)

{
  drawshape2(param_1,param_2 - (*(int *)(param_1 + 6) >> 0x10),
             param_3 - (*(int *)(param_1 + 8) >> 0x10));
  return;
}


// ================================================================================================
// sub_91260 @ 0x91260 [__cdecl]
// ================================================================================================

void sub_91260(char *param_1,char *param_2,int param_3)

{
  char cVar1;
  char *pcVar2;
  
  if (param_3 != 0) {
    pcVar2 = param_2 + param_3;
    do {
      cVar1 = *param_1;
      param_1 = param_1 + 1;
      if (cVar1 != -1) {
        *param_2 = cVar1;
      }
      param_2 = param_2 + 1;
    } while (param_2 < pcVar2);
  }
  return;
}


// ================================================================================================
// drawshape2_remap @ 0x91284 [__cdecl]
// ================================================================================================

void drawshape2_remap(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  if (dword_d30c8 == 0) {
    sub_b693c(param_1,param_2,param_3);
    return;
  }
  funcptr_d43e4 = sub_91260;
  drawshape2(param_1,param_2,param_3);
  funcptr_d43e4 = sub_b3abc;
  return;
}


// ================================================================================================
// sub_912c8 @ 0x912c8 [__cdecl]
// ================================================================================================

void sub_912c8(int param_1)

{
  drawshape2_remap(param_1,*(int *)(param_1 + 10) >> 0x10,*(int *)(param_1 + 0xc) >> 0x10);
  return;
}


// ================================================================================================
// sub_912e4 @ 0x912e4 [__cdecl]
// ================================================================================================

void sub_912e4(int param_1,int param_2,int param_3)

{
  drawshape2_remap(param_1,param_2 - (*(int *)(param_1 + 6) >> 0x10),
                   param_3 - (*(int *)(param_1 + 8) >> 0x10));
  return;
}


// ================================================================================================
// sub_91310 @ 0x91310 [__cdecl]
// ================================================================================================

void sub_91310(int *param_1)

{
  undefined4 extraout_EDX;
  
  removewindow(*(int *)(*param_1 + 0x28) + -8);
  releasememblock(extraout_EDX);
  return;
}


// ================================================================================================
// sub_9132c @ 0x9132c [__cdecl]
// ================================================================================================

void sub_9132c(int param_1)

{
  undefined4 extraout_EDX;
  
  removewindow(*(int *)(param_1 + 0x28) + -8);
  freemem(extraout_EDX);
  return;
}


// ================================================================================================
// memset @ 0x91350 [__watcall]
// ================================================================================================

void * __watcall memset(void *__s,int __c,size_t __n)

{
  undefined uVar1;
  
  uVar1 = (undefined)__c;
  _memset_fill(__s,CONCAT31(CONCAT21(CONCAT11(uVar1,uVar1),uVar1),uVar1),__n,__n);
  return __s;
}


// ================================================================================================
// drawshape_remap @ 0x91370 [__cdecl]
// ================================================================================================

void drawshape_remap(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  if (dword_d30c8 == 0) {
    sub_b69e4(param_1,param_2,param_3);
    return;
  }
  funcptr_d43e4 = sub_91260;
  drawshape(param_1,param_2,param_3);
  funcptr_d43e4 = sub_b3abc;
  return;
}


// ================================================================================================
// drawshape_remap_home @ 0x913b4 [__cdecl]
// ================================================================================================

void drawshape_remap_home(int param_1)

{
  drawshape_remap(param_1,*(int *)(param_1 + 10) >> 0x10,*(int *)(param_1 + 0xc) >> 0x10);
  return;
}


// ================================================================================================
// drawshape_remap_centered @ 0x913d0 [__cdecl]
// ================================================================================================

void drawshape_remap_centered(int param_1,int param_2,int param_3)

{
  drawshape_remap(param_1,param_2 - (*(int *)(param_1 + 6) >> 0x10),
                  param_3 - (*(int *)(param_1 + 8) >> 0x10));
  return;
}


// ================================================================================================
// grabshape @ 0x91400 [__cdecl]
// ================================================================================================

void grabshape(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  uint local_10;
  
  if (dword_d30c8 == 0) {
    sub_b6b3f(param_1,param_2,param_3);
  }
  else {
    *(short *)(param_1 + 0xc) = (short)param_2;
    *(short *)(param_1 + 0xe) = (short)param_3;
    iVar7 = param_1 + 0x10;
    iVar5 = *(int *)(param_1 + 4);
    iVar2 = *(int *)(param_1 + 2) >> 0x10;
    iVar1 = (&unk_d3104)[param_3];
    iVar3 = dword_d30a4 - iVar2;
    local_10 = (uint)(iVar1 + param_2) >> 0x10;
    iVar8 = dword_d30d0;
    sub_b5e00(local_10,iVar3,dword_d30d0);
    uVar6 = iVar1 + param_2 & 0xffff;
    for (iVar5 = iVar5 >> 0x10; 0 < iVar5; iVar5 = iVar5 + -1) {
      uVar4 = iVar2 + uVar6;
      if ((uVar4 & 0x10000) == 0) {
        sub_b3abc(iVar8 + uVar6,iVar7,iVar2);
        iVar7 = iVar7 + iVar2;
      }
      else {
        sub_b3abc(iVar8 + uVar6,iVar7,0x10000 - uVar6);
        iVar7 = iVar7 + (0x10000 - uVar6);
        uVar4 = uVar4 & 0xffff;
        local_10 = local_10 + 1;
        sub_b5e00(local_10);
        sub_b3abc(iVar8,iVar7,uVar4);
        iVar7 = iVar7 + uVar4;
      }
      uVar6 = uVar4 + iVar3;
      if ((uVar6 & 0x10000) != 0) {
        uVar6 = uVar6 & 0xffff;
        local_10 = local_10 + 1;
        sub_b5e00(local_10);
      }
    }
  }
  return;
}


// ================================================================================================
// sub_91538 @ 0x91538 [__cdecl]
// ================================================================================================

void sub_91538(int param_1)

{
  grabshape(param_1,*(int *)(param_1 + 10) >> 0x10,*(int *)(param_1 + 0xc) >> 0x10);
  return;
}


// ================================================================================================
// sub_91554 @ 0x91554 [__cdecl]
// ================================================================================================

void sub_91554(int param_1,int param_2,int param_3)

{
  grabshape(param_1,param_2 - (*(int *)(param_1 + 6) >> 0x10),
            param_3 - (*(int *)(param_1 + 8) >> 0x10));
  return;
}


// ================================================================================================
// printstr @ 0x91580 [__cdecl]
// ================================================================================================

void printstr(char *param_1)

{
  char cVar1;
  uint uVar2;
  byte bVar3;
  byte bVar4;
  undefined *puVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  byte bVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  int iVar12;
  int iVar13;
  uint uVar14;
  int iVar15;
  uint uVar16;
  uint uVar17;
  byte *pbVar18;
  bool bVar19;
  uint local_30;
  uint local_28;
  int local_24;
  uint local_14;
  
  uVar7 = dword_d42dc;
  uVar6 = dword_d42a8;
  puVar5 = off_d42a4;
  uVar9 = (uint)byte_d42c1;
  uVar14 = (uint)byte_d42c0;
  uVar10 = (byte)off_d42a4[3] - 0x30;
  bVar19 = dword_d42bc == 0x464e544d;
  cVar1 = *param_1;
  while (cVar1 != '\0') {
    bVar8 = *param_1 - byte_d42c0;
    if ((int)(uint)bVar8 < (int)((uVar9 - uVar14) + 1)) {
      bVar4 = byte_d42c2;
      if (off_d42c8 != (undefined *)0x0) {
        bVar4 = off_d42c8[bVar8];
      }
      uVar2 = (uint)bVar4;
      bVar3 = byte_d42c3;
      if (dword_d42cc != 0) {
        bVar3 = *(byte *)(dword_d42cc + (CONCAT11(bVar4,bVar8) & 0xff));
      }
      uVar11 = (uint)CONCAT11(bVar3,bVar8);
      local_14 = (uint)bVar3;
      if (dword_d42d0 == 0) {
        uVar16 = byte_d42c4 + uVar2;
      }
      else {
        uVar16 = (uint)*(byte *)((uVar11 & 0xff) + dword_d42d0);
      }
      if (dword_d42d4 == 0) {
        uVar17 = 0;
      }
      else {
        uVar17 = (uint)*(byte *)((uVar11 & 0xff) + dword_d42d4);
      }
      iVar12 = dword_d42b0 + uVar17;
      if (dword_d42d8 == 0) {
        uVar17 = 0;
      }
      else {
        uVar17 = (uint)*(byte *)((uVar11 & 0xff) + dword_d42d8);
      }
      iVar13 = uVar17 + dword_d42b4;
      iVar15 = *(int *)(off_d42e0 + (uVar11 & 0xff) * 4);
      if (bVar19) {
        if ((uVar2 != 0) && (bVar3 != 0)) {
          setclip(iVar12,iVar12 + uVar2,iVar13,local_14 + iVar13);
          drawshape_remap(uVar7,iVar12 - iVar15,iVar13);
          setclip(0,dword_d30a4,0,dword_d30a8);
        }
      }
      else if (iVar15 != 0) {
        pbVar18 = puVar5 + iVar15;
        if (uVar10 < 4) {
          if (uVar10 == 1) {
            while (local_14 = local_14 - 1, local_14 != 0xffffffff) {
              if ((iVar13 < dword_d30b0) || (dword_d30b8 <= iVar13)) {
                pbVar18 = pbVar18 + ((int)(uVar2 + 7) >> 3);
              }
              else {
                iVar15 = iVar12;
                local_30 = uVar2;
                if (uVar2 != 0) {
                  do {
                    if ((*pbVar18 & 0x80) != 0) {
                      sub_b5d80(iVar15,iVar13,uVar6);
                    }
                    if ((*pbVar18 & 0x40) != 0) {
                      sub_b5d80(iVar15 + 1,iVar13,uVar6);
                    }
                    if ((*pbVar18 & 0x20) != 0) {
                      sub_b5d80(iVar15 + 2,iVar13,uVar6);
                    }
                    if ((*pbVar18 & 0x10) != 0) {
                      sub_b5d80(iVar15 + 3,iVar13,uVar6);
                    }
                    if ((*pbVar18 & 8) != 0) {
                      sub_b5d80(iVar15 + 4,iVar13,uVar6);
                    }
                    if ((*pbVar18 & 4) != 0) {
                      sub_b5d80(iVar15 + 5,iVar13,uVar6);
                    }
                    if ((*pbVar18 & 2) != 0) {
                      sub_b5d80(iVar15 + 6,iVar13,uVar6);
                    }
                    if ((*pbVar18 & 1) != 0) {
                      sub_b5d80(iVar15 + 7,iVar13,uVar6);
                    }
                    iVar15 = iVar15 + 8;
                    local_30 = local_30 - 8;
                    pbVar18 = pbVar18 + 1;
                  } while (0 < (int)local_30);
                }
              }
              iVar13 = iVar13 + 1;
            }
          }
        }
        else if (uVar10 < 5) {
          while (local_14 = local_14 - 1, local_14 != 0xffffffff) {
            if ((iVar13 < dword_d30b0) || (dword_d30b8 <= iVar13)) {
              pbVar18 = pbVar18 + ((int)(uVar2 + 1) >> 1);
            }
            else {
              iVar15 = iVar12;
              local_28 = uVar2;
              if (uVar2 != 0) {
                do {
                  if ((int)(uint)*pbVar18 >> 4 != 0) {
                    sub_b5d80(iVar15,iVar13,(int)(uint)*pbVar18 >> 4);
                  }
                  if ((*pbVar18 & 0xf) != 0) {
                    sub_b5d80(iVar15 + 1,iVar13,*pbVar18 & 0xf);
                  }
                  iVar15 = iVar15 + 2;
                  local_28 = local_28 - 2;
                  pbVar18 = pbVar18 + 1;
                } while (0 < (int)local_28);
              }
            }
            iVar13 = iVar13 + 1;
          }
        }
        else if (uVar10 == 8) {
          while (local_14 = local_14 - 1, local_14 != 0xffffffff) {
            if ((iVar13 < dword_d30b0) || (uVar11 = uVar2, local_24 = iVar12, dword_d30b8 <= iVar13)
               ) {
              pbVar18 = pbVar18 + uVar2;
            }
            else {
              while (uVar11 - 1 != 0xffffffff) {
                if (*pbVar18 != 0) {
                  sub_b5d80(local_24,iVar13,*pbVar18);
                }
                pbVar18 = pbVar18 + 1;
                uVar11 = uVar11 - 1;
                local_24 = local_24 + 1;
              }
            }
            iVar13 = iVar13 + 1;
          }
        }
      }
      dword_d42b0 = dword_d42b0 + uVar16;
    }
    cVar1 = param_1[1];
    param_1 = param_1 + 1;
  }
  return;
}


// ================================================================================================
// printstr_at @ 0x91964 [__cdecl]
// ================================================================================================

void printstr_at(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  settextxy(param_2,param_3);
  printstr(param_1);
  return;
}


// ================================================================================================
// sub_91984 @ 0x91984 [__watcall]
// ================================================================================================

undefined8 __watcall sub_91984(uint param_1,undefined4 unaff_EDX)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  undefined2 in_DS;
  
  if ((param_1 != 0) && (param_1 < 0xffffffd5)) {
    iVar2 = 0;
    bVar1 = false;
    uVar6 = param_1 + 3 & 0xfffffffc;
LAB_000919b7:
    do {
      uVar3 = uVar6;
      if (uVar6 < 0xc) {
        uVar3 = 0xc;
      }
      if (dword_d43f0 < uVar3) {
        uVar5 = dword_d43ec;
        uVar3 = dword_d43ec;
        if (dword_d43ec == 0) goto LAB_000919d5;
      }
      else {
        uVar3 = 0;
LAB_000919d5:
        uVar5 = dword_d43e8;
        dword_d43f0 = uVar3;
      }
      for (; uVar5 != 0; uVar5 = *(uint *)(uVar5 + 8)) {
        dword_d43ec = uVar5;
        iVar2 = sub_9a874(param_1,in_DS,uVar5);
        if (iVar2 != 0) goto LAB_00091a4e;
        if (dword_d43f0 < *(uint *)(uVar5 + 0x14)) {
          dword_d43f0 = *(uint *)(uVar5 + 0x14);
        }
      }
      if (bVar1) {
LAB_00091a30:
        iVar4 = sub_9afad(param_1);
        if (iVar4 == 0) goto LAB_00091a4e;
        bVar1 = false;
        goto LAB_000919b7;
      }
      iVar4 = sub_9adf2(param_1);
      if (iVar4 == 0) goto LAB_00091a30;
      bVar1 = true;
    } while( true );
  }
  iVar2 = 0;
LAB_00091a58:
  return CONCAT44(unaff_EDX,iVar2);
LAB_00091a4e:
  byte_f24c5 = 0;
  goto LAB_00091a58;
}


// ================================================================================================
// sub_91a67 @ 0x91a67 [__watcall]
// ================================================================================================

void __watcall sub_91a67(uint param_1)

{
  uint uVar1;
  undefined2 in_DS;
  
  for (uVar1 = dword_d43e8;
      (*(uint *)(uVar1 + 8) != 0 && ((param_1 < uVar1 || (*(uint *)(uVar1 + 8) <= param_1))));
      uVar1 = *(uint *)(uVar1 + 8)) {
  }
  sub_9a91c(param_1,in_DS,uVar1);
  if ((uVar1 != dword_d43ec) && (dword_d43f0 < *(uint *)(uVar1 + 0x14))) {
    dword_d43f0 = *(uint *)(uVar1 + 0x14);
  }
  byte_f24c5 = 0;
  return;
}


// ================================================================================================
// strlen @ 0x91ac5 [__watcall]
// ================================================================================================

size_t __watcall strlen(char *__s)

{
  char cVar1;
  uint uVar2;
  
  uVar2 = 0xffffffff;
  do {
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    cVar1 = *__s;
    __s = __s + 1;
  } while (cVar1 != '\0');
  return ~uVar2 - 1;
}


// ================================================================================================
// sub_91ade @ 0x91ade [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 __watcall sub_91ade(undefined *param_1,undefined4 unaff_EDX)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  int extraout_EDX;
  uint uVar4;
  bool bVar5;
  
  uVar4 = 0;
  cVar1 = sub_9afb0(*param_1);
  if (((cVar1 != 'r') && (cVar1 != 'w')) && (cVar1 != 'a')) {
    sub_9878a(9);
    uVar4 = 0;
    goto LAB_00091b8b;
  }
  uVar2 = 3;
  if (*(char *)(extraout_EDX + 1) == '+') {
    uVar3 = 0x43;
    if (*(char *)(extraout_EDX + 2) == 'b') {
LAB_00091b3a:
      uVar4 = uVar3;
    }
    else {
      uVar4 = uVar2;
      if (*(char *)(extraout_EDX + 2) != 't') {
        bVar5 = ram0x000d4f21 == 0x200;
LAB_00091b38:
        if (bVar5) goto LAB_00091b3a;
      }
    }
  }
  else {
    uVar3 = 0x40;
    if (*(char *)(extraout_EDX + 1) == 'b') {
      uVar4 = uVar3;
      if (*(char *)(extraout_EDX + 2) == '+') {
        uVar3 = 0x43;
LAB_00091b6f:
        uVar4 = uVar3;
      }
    }
    else {
      if (*(char *)(extraout_EDX + 1) == 't') {
        bVar5 = *(char *)(extraout_EDX + 2) == '+';
        uVar3 = uVar2;
        goto LAB_00091b38;
      }
      if (ram0x000d4f21 == 0x200) goto LAB_00091b6f;
    }
  }
  if (cVar1 == 'w') {
    uVar4 = uVar4 | 2;
  }
  else if (cVar1 == 'a') {
    uVar4 = uVar4 | 0x82;
  }
  else {
    uVar4 = uVar4 | 1;
  }
LAB_00091b8b:
  return CONCAT44(unaff_EDX,uVar4);
}


// ================================================================================================
// sub_91b92 @ 0x91b92 [__watcall]
// ================================================================================================

int __watcall sub_91b92(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,int unaff_ECX)

{
  char cVar1;
  byte bVar2;
  ushort uVar3;
  int extraout_ECX;
  char extraout_DL;
  undefined8 uVar4;
  undefined4 uVar5;
  
  *(byte *)(unaff_ECX + 0xc) = *(byte *)(unaff_ECX + 0xc) & 0xfc;
  uVar4 = sub_91ade(unaff_EDX);
  *(uint *)(unaff_ECX + 0xc) = *(uint *)(unaff_ECX + 0xc) | (uint)uVar4;
  cVar1 = sub_9afb0(*(undefined *)((ulonglong)uVar4 >> 0x20));
  if (cVar1 == 'r') {
    uVar3 = 0;
    if ((*(byte *)(unaff_ECX + 0xc) & 2) != 0) {
      uVar3 = 2;
    }
    if ((*(byte *)(unaff_ECX + 0xc) & 0x40) == 0) {
      uVar3 = uVar3 | 0x100;
    }
    else {
      uVar3 = uVar3 | 0x200;
    }
    uVar5 = 0;
  }
  else {
    bVar2 = ((*(byte *)(unaff_ECX + 0xc) & 1) != 0) + 0x21;
    if (cVar1 == 'a') {
      bVar2 = bVar2 | 0x10;
    }
    else {
      bVar2 = bVar2 | 0x40;
    }
    if ((*(byte *)(unaff_ECX + 0xc) & 0x40) == 0) {
      uVar3 = CONCAT11(1,bVar2);
    }
    else {
      uVar3 = CONCAT11(2,bVar2);
    }
    uVar5 = 0x180;
  }
  uVar5 = sub_9208c(param_1,uVar3,unaff_EBX,uVar5);
  *(undefined4 *)(extraout_ECX + 0x10) = uVar5;
  if (*(int *)(extraout_ECX + 0x10) == -1) {
    sub_9b066(extraout_ECX);
    return 0;
  }
  *(undefined4 *)(extraout_ECX + 4) = 0;
  *(undefined4 *)(extraout_ECX + 8) = 0;
  *(undefined4 *)(extraout_ECX + 0x14) = 0;
  if (extraout_DL == 'a') {
    sub_9b0ff(extraout_ECX,0,2);
  }
  sub_9b1fb(extraout_ECX);
  return extraout_ECX;
}


// ================================================================================================
// sub_91c5a @ 0x91c5a [__watcall]
// ================================================================================================

void __watcall sub_91c5a(undefined4 param_1,undefined4 param_2,undefined4 unaff_EBX)

{
  undefined8 uVar1;
  
  uVar1 = sub_9afbe(0);
  if ((int)uVar1 != 0) {
    sub_91b92(param_1,(int)((ulonglong)uVar1 >> 0x20),unaff_EBX,(int)uVar1);
  }
  return;
}


// ================================================================================================
// fopen @ 0x91c75 [__watcall]
// ================================================================================================

FILE * __watcall fopen(char *__filename,char *__modes)

{
  FILE *pFVar1;
  
  pFVar1 = (FILE *)sub_91c5a(__filename,__modes,0);
  return pFVar1;
}


// ================================================================================================
// sub_91c7f @ 0x91c7f [__watcall]
// ================================================================================================

longlong __watcall sub_91c7f(int param_1,uint unaff_EDX)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  puVar2 = dword_f24c8;
  do {
    if (puVar2 == (undefined4 *)0x0) {
      puVar2 = &dword_edf00;
      do {
        puVar3 = puVar2;
        puVar2 = (undefined4 *)*puVar3;
        if (puVar2 == (undefined4 *)0x0) {
          sub_9878a(4);
          return (ulonglong)unaff_EDX << 0x20;
        }
      } while (param_1 != puVar2[1]);
      *puVar3 = *puVar2;
      *puVar2 = dword_f24c8;
      dword_f24c8 = puVar2;
LAB_00091ca6:
      return CONCAT44(unaff_EDX,param_1);
    }
    iVar1 = puVar2[1];
    if (param_1 == iVar1) {
      if ((*(byte *)(iVar1 + 0xc) & 3) != 0) {
        sub_91dc4(iVar1,1);
      }
      goto LAB_00091ca6;
    }
    puVar2 = (undefined4 *)*puVar2;
  } while( true );
}


// ================================================================================================
// sub_91ce7 @ 0x91ce7 [__watcall]
// ================================================================================================

void __watcall sub_91ce7(undefined4 param_1,undefined4 param_2,undefined4 unaff_EBX)

{
  int iVar1;
  undefined8 uVar2;
  
  uVar2 = sub_91c7f(unaff_EBX);
  iVar1 = (int)uVar2;
  if (iVar1 != 0) {
    *(uint *)(iVar1 + 0xc) = *(uint *)(iVar1 + 0xc) & 0x4000;
    sub_91b92(param_1,(int)((ulonglong)uVar2 >> 0x20),0,iVar1);
  }
  return;
}


// ================================================================================================
// fclose @ 0x91d0b [__watcall]
// ================================================================================================

int __watcall fclose(FILE *__stream)

{
  undefined4 *puVar1;
  int iVar2;
  
  puVar1 = dword_f24c8;
  while( true ) {
    if (puVar1 == (undefined4 *)0x0) {
      return -1;
    }
    if (__stream == (FILE *)puVar1[1]) break;
    puVar1 = (undefined4 *)*puVar1;
  }
  iVar2 = sub_91d3a((FILE *)puVar1[1],1);
  return iVar2;
}


// ================================================================================================
// sub_91d3a @ 0x91d3a [__watcall]
// ================================================================================================

undefined4 __watcall
sub_91d3a(undefined4 param_1,undefined4 param_2,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  undefined4 uVar1;
  undefined4 extraout_EDX;
  
  uVar1 = sub_91dc4();
  sub_9b066(param_1,uVar1,param_1,unaff_ECX,unaff_EBX);
  return extraout_EDX;
}


// ================================================================================================
// sub_91d4f @ 0x91d4f [__watcall]
// ================================================================================================

int __watcall sub_91d4f(int param_1)

{
  int iVar1;
  
  iVar1 = param_1 + 0x30;
  if (0x39 < iVar1) {
    iVar1 = param_1 + 0x57;
  }
  return iVar1;
}


// ================================================================================================
// sub_91d5b @ 0x91d5b [__watcall]
// ================================================================================================

void __watcall sub_91d5b(undefined *param_1,uint unaff_EDX)

{
  undefined uVar1;
  uint uVar2;
  undefined *puVar3;
  undefined *extraout_EDX;
  
  uVar2 = sub_9b22c();
  *param_1 = 0x74;
  puVar3 = param_1 + 4;
  do {
    uVar1 = sub_91d4f(uVar2 & 0xf,puVar3);
    *extraout_EDX = uVar1;
    puVar3 = extraout_EDX + -1;
    uVar2 = uVar2 >> 4;
  } while (puVar3 != param_1);
  param_1[5] = 0x5f;
  uVar1 = sub_91d4f((int)unaff_EDX >> 4 & 0xf);
  param_1[6] = uVar1;
  uVar1 = sub_91d4f(unaff_EDX & 0xf);
  param_1[8] = 0x2e;
  param_1[9] = 0x74;
  param_1[10] = 0x6d;
  param_1[0xb] = 0x70;
  param_1[0xc] = 0;
  param_1[7] = uVar1;
  return;
}


// ================================================================================================
// sub_91dc4 @ 0x91dc4 [__watcall]
// ================================================================================================

uint __watcall sub_91dc4(int param_1,int unaff_EDX)

{
  int __offset;
  uint uVar1;
  uint uVar2;
  char acStack_20 [16];
  
  if (*(int *)(param_1 + 0xc) == 0) {
    uVar2 = 0xffffffff;
  }
  else {
    uVar2 = 0;
    if ((*(byte *)(param_1 + 0xd) & 0x10) != 0) {
      uVar2 = sub_9b232(param_1);
    }
    __offset = sub_9b2f1(param_1);
    if (__offset != -1) {
      lseek(*(int *)(param_1 + 0x10),__offset,0);
    }
    if (unaff_EDX != 0) {
      uVar1 = sub_9b321(*(undefined4 *)(param_1 + 0x10));
      uVar2 = uVar2 | uVar1;
    }
    if ((*(byte *)(param_1 + 0xc) & 8) != 0) {
      sub_91a67(*(undefined4 *)(param_1 + 8));
      *(undefined4 *)(param_1 + 8) = 0;
    }
    if ((*(byte *)(param_1 + 0xd) & 8) != 0) {
      sub_91d5b(acStack_20,*(undefined *)(param_1 + 0x19));
      sub_903e8(acStack_20);
    }
  }
  return uVar2;
}


// ================================================================================================
// strncpy @ 0x91e4d [__watcall]
// ================================================================================================

char * __watcall strncpy(char *__dest,char *__src,size_t __n)

{
  char *pcVar1;
  
  pcVar1 = __dest;
  for (; (__n != 0 && (*__src != '\0')); __src = __src + 1) {
    __n = __n - 1;
    *pcVar1 = *__src;
    pcVar1 = pcVar1 + 1;
  }
  for (; __n != 0; __n = __n - 1) {
    *pcVar1 = '\0';
    pcVar1 = pcVar1 + 1;
  }
  return __dest;
}


// ================================================================================================
// sub_91e72 @ 0x91e72 [__watcall]
// ================================================================================================

int __watcall sub_91e72(char *param_1,int unaff_EDX)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  byte bVar4;
  int iVar5;
  bool bVar6;
  
  if (*(int *)(unaff_EDX + 8) == 0) {
    sub_9b353(unaff_EDX);
  }
  bVar6 = (*(byte *)(unaff_EDX + 0xd) & 4) != 0;
  if (bVar6) {
    bVar4 = *(byte *)(unaff_EDX + 0xd) & 0xf9;
    *(byte *)(unaff_EDX + 0xd) = bVar4;
    *(byte *)(unaff_EDX + 0xd) = bVar4 | 2;
  }
  iVar5 = 0;
  pcVar3 = param_1;
  do {
    cVar1 = *pcVar3;
    if (cVar1 == '\0') goto LAB_00091ec2;
    pcVar3 = pcVar3 + 1;
    iVar2 = sub_9b3ca(cVar1,unaff_EDX);
  } while (iVar2 != -1);
  iVar5 = -1;
LAB_00091ec2:
  if (bVar6) {
    bVar4 = *(byte *)(unaff_EDX + 0xd) & 0xf9;
    *(byte *)(unaff_EDX + 0xd) = bVar4;
    *(byte *)(unaff_EDX + 0xd) = bVar4 | 4;
    if (iVar5 == 0) {
      iVar5 = sub_9b232(unaff_EDX);
    }
  }
  if (iVar5 == 0) {
    iVar5 = (int)pcVar3 - (int)param_1;
  }
  return iVar5;
}


// ================================================================================================
// strcmp @ 0x91f00 [__watcall]
// ================================================================================================

int __watcall strcmp(char *__s1,char *__s2)

{
  byte bVar1;
  byte bVar3;
  uint uVar4;
  bool bVar5;
  uint uVar2;
  
  if (__s1 != __s2) {
    do {
      uVar2 = *(uint *)__s1;
      uVar4 = *(uint *)__s2;
      if (uVar4 != uVar2) {
LAB_00091f79:
        bVar1 = (byte)uVar2;
        bVar5 = bVar1 < (byte)uVar4;
        if (bVar1 == (byte)uVar4) {
          if (bVar1 == 0) {
            return 0;
          }
          bVar1 = (byte)(uVar2 >> 8);
          bVar3 = (byte)(uVar4 >> 8);
          bVar5 = bVar1 < bVar3;
          if (bVar1 == bVar3) {
            if (bVar1 == 0) {
              return 0;
            }
            bVar1 = (byte)(uVar2 >> 0x10);
            bVar3 = (byte)(uVar4 >> 0x10);
            bVar5 = bVar1 < bVar3;
            if (bVar1 == bVar3) {
              if (bVar1 == 0) {
                return 0;
              }
              bVar5 = (byte)(uVar2 >> 0x18) < (byte)(uVar4 >> 0x18);
            }
          }
        }
        return -(uint)bVar5 | 1;
      }
      if ((uVar2 + 0xfefefeff & ~uVar4 & 0x80808080) != 0) {
        return 0;
      }
      uVar2 = *(uint *)((int)__s1 + 4);
      uVar4 = *(uint *)((int)__s2 + 4);
      if (uVar4 != uVar2) goto LAB_00091f79;
      if ((uVar2 + 0xfefefeff & ~uVar4 & 0x80808080) != 0) {
        return 0;
      }
      uVar2 = *(uint *)((int)__s1 + 8);
      uVar4 = *(uint *)((int)__s2 + 8);
      if (uVar4 != uVar2) goto LAB_00091f79;
      if ((uVar2 + 0xfefefeff & ~uVar4 & 0x80808080) != 0) {
        return 0;
      }
      uVar2 = *(uint *)((int)__s1 + 0xc);
      uVar4 = *(uint *)((int)__s2 + 0xc);
      if (uVar4 != uVar2) goto LAB_00091f79;
      __s1 = (char *)((int)__s1 + 0x10);
      __s2 = (char *)((int)__s2 + 0x10);
    } while ((uVar2 + 0xfefefeff & ~uVar4 & 0x80808080) == 0);
  }
  return 0;
}


// ================================================================================================
// sub_91fa4 @ 0x91fa4 [__cdecl]
// ================================================================================================

uint sub_91fa4(int param_1,int param_2)

{
  longlong lVar1;
  
  lVar1 = (longlong)param_1 * (longlong)param_2 + 0x7fff;
  return (uint)lVar1 >> 0x10 | (int)((ulonglong)lVar1 >> 0x20) << 0x10;
}


// ================================================================================================
// sub_91fbc @ 0x91fbc [__watcall]
// ================================================================================================

int __watcall sub_91fbc(byte *param_1,byte *unaff_EDX,int unaff_EBX)

{
  int iVar1;
  bool bVar2;
  bool bVar3;
  
  bVar2 = false;
  iVar1 = 0;
  bVar3 = true;
  do {
    if (unaff_EBX == 0) break;
    unaff_EBX = unaff_EBX + -1;
    bVar2 = *param_1 < *unaff_EDX;
    bVar3 = *param_1 == *unaff_EDX;
    param_1 = param_1 + 1;
    unaff_EDX = unaff_EDX + 1;
  } while (bVar3);
  if (!bVar3) {
    iVar1 = (1 - (uint)bVar2) - (uint)(bVar2 != 0);
  }
  return iVar1;
}


// ================================================================================================
// drawshape_trans @ 0x91fe0 [__cdecl]
// ================================================================================================

void drawshape_trans(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  if (dword_d30c8 == 0) {
    sub_b6be5(param_1,param_2,param_3);
    return;
  }
  funcptr_d43e4 = sub_931d0;
  drawshape(param_1,param_2,param_3);
  funcptr_d43e4 = sub_b3abc;
  return;
}


// ================================================================================================
// sub_92024 @ 0x92024 [__cdecl]
// ================================================================================================

void sub_92024(int param_1)

{
  drawshape_trans(param_1,*(int *)(param_1 + 10) >> 0x10,*(int *)(param_1 + 0xc) >> 0x10);
  return;
}


// ================================================================================================
// sub_92040 @ 0x92040 [__cdecl]
// ================================================================================================

void sub_92040(int param_1,int param_2,int param_3)

{
  drawshape_trans(param_1,param_2 - (*(int *)(param_1 + 6) >> 0x10),
                  param_3 - (*(int *)(param_1 + 8) >> 0x10));
  return;
}


// ================================================================================================
// sub_92068 @ 0x92068 [__cdecl]
// ================================================================================================

void sub_92068(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  sub_9208c(param_1,param_2,0,param_3);
  return;
}


// ================================================================================================
// sub_9208c @ 0x9208c [__cdecl]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 sub_9208c(char *param_1,undefined4 param_2,uint param_3)

{
  code *pcVar1;
  bool bVar2;
  int iVar3;
  uint uVar4;
  undefined4 extraout_EDX;
  uint *puVar5;
  uint *puVar6;
  uint uVar7;
  byte bVar8;
  ulonglong uVar9;
  undefined8 uVar10;
  undefined4 local_20;
  byte abStack_1c [4];
  uint local_18;
  
  for (; *param_1 == ' '; param_1 = param_1 + 1) {
  }
  bVar8 = 0;
  uVar7 = 0xffffffff;
  pcVar1 = (code *)swi(0x21);
  iVar3 = (*pcVar1)();
  bVar2 = (bVar8 & 1) != 0;
  uVar4 = (iVar3 << 1 | (uint)bVar8) >> 1;
  local_18 = uVar4 | (uint)bVar2 << 0x1f;
  if (!bVar2) {
    uVar7 = uVar4 & 0xffff;
  }
  puVar5 = (uint *)abStack_1c;
  if ((((param_3 & 3) == 0) || (puVar5 = (uint *)abStack_1c, uVar7 == 0xffffffff)) ||
     (uVar9 = sub_9b710(uVar7), puVar5 = (uint *)abStack_1c, (int)uVar9 != 0)) goto LAB_0009214d;
  if ((param_3 & 0x400) != 0) {
    pcVar1 = (code *)swi(0x21);
    (*pcVar1)();
    puVar6 = &local_18;
    abStack_1c[0] = 0xb;
    abStack_1c[1] = 0x21;
    abStack_1c[2] = 9;
    abStack_1c[3] = 0;
    sub_9878a(7,extraout_EDX,uVar7);
    uVar7 = 0xffffffff;
    goto LAB_00092248;
  }
  puVar5 = (uint *)abStack_1c;
  if ((uVar9 & 0x400000000000) == 0) {
LAB_0009214d:
    puVar6 = puVar5;
    if (uVar7 != 0xffffffff) {
LAB_000921db:
      *(byte *)((int)puVar6 + -0xffffffff00000004) = 0xe2;
      *(byte *)((int)puVar6 + -0xffffffff00000003) = 0x21;
      *(byte *)((int)puVar6 + -0xffffffff00000002) = 9;
      *(byte *)((int)puVar6 + -0xffffffff00000001) = 0;
      uVar4 = sub_9b72e(uVar7);
      *(byte *)((int)puVar6 + -0xffffffff00000004) = 0xed;
      *(byte *)((int)puVar6 + -0xffffffff00000003) = 0x21;
      *(byte *)((int)puVar6 + -0xffffffff00000002) = 9;
      *(byte *)((int)puVar6 + -0xffffffff00000001) = 0;
      uVar10 = sub_9b710(uVar7,uVar4 & 0xffffff3c);
      uVar4 = (uint)((ulonglong)uVar10 >> 0x20);
      if ((int)uVar10 != 0) {
        uVar4 = uVar4 | 0x2000;
      }
      *(byte *)puVar6 = *(byte *)puVar6 & 0x7f;
      if (*puVar6 == 2) {
        uVar4 = uVar4 | 3;
      }
      if (*puVar6 == 0) {
        uVar4 = uVar4 | 1;
      }
      if (*puVar6 == 1) {
        uVar4 = uVar4 | 2;
      }
      if ((*(byte *)((int)puVar6 + 0x28) & 0x10) != 0) {
        uVar4 = uVar4 | 0x80;
      }
      if ((*(byte *)((int)puVar6 + 0x29) & 3) == 0) {
        if (ram0x000d4f21 == 0x200) goto LAB_0009223d;
      }
      else if ((*(byte *)((int)puVar6 + 0x29) & 2) != 0) {
LAB_0009223d:
        uVar4 = uVar4 | 0x40;
      }
      *(byte *)((int)puVar6 + -0xffffffff00000004) = 0x46;
      *(byte *)((int)puVar6 + -0xffffffff00000003) = 0x22;
      *(byte *)((int)puVar6 + -0xffffffff00000002) = 9;
      *(byte *)((int)puVar6 + -0xffffffff00000001) = 0;
      sub_9b783(uVar7,uVar4);
      goto LAB_00092248;
    }
    if (((*(byte *)((int)puVar5 + 0x28) & 0x20) != 0) && (*(short *)((int)puVar5 + 4) == 2)) {
      bVar8 = 0;
      pcVar1 = (code *)swi(0x21);
      iVar3 = (*pcVar1)();
      puVar6 = (uint *)((int)puVar5 + 4);
      bVar2 = (bVar8 & 1) != 0;
      *(uint *)((int)puVar5 + 8) = (iVar3 << 1 | (uint)bVar8) >> 1 | (uint)bVar2 << 0x1f;
      bVar8 = 0;
      if (!bVar2) {
        pcVar1 = (code *)swi(0x21);
        iVar3 = (*pcVar1)();
        puVar6 = (uint *)((int)puVar5 + 8);
        bVar2 = (bVar8 & 1) != 0;
        *(uint *)((int)puVar5 + 0xc) = (iVar3 << 1 | (uint)bVar8) >> 1 | (uint)bVar2 << 0x1f;
        if (!bVar2) {
          bVar8 = 0;
          pcVar1 = (code *)swi(0x21);
          iVar3 = (*pcVar1)();
          puVar6 = (uint *)((int)puVar5 + 0xc);
          bVar2 = (bVar8 & 1) != 0;
          *(uint *)((int)puVar5 + 0x10) = (iVar3 << 1 | (uint)bVar8) >> 1 | (uint)bVar2 << 0x1f;
          if (!bVar2) {
            uVar7 = (uint)*(ushort *)((int)puVar5 + 0x10);
            puVar6 = (uint *)((int)puVar5 + 0xc);
            goto LAB_000921db;
          }
        }
      }
    }
  }
  else {
    bVar8 = 0;
    pcVar1 = (code *)swi(0x21);
    (*pcVar1)();
    puVar5 = &local_18;
    if ((bVar8 & 1) == 0) goto LAB_0009214d;
    pcVar1 = (code *)swi(0x21);
    (*pcVar1)();
    puVar6 = (uint *)&stack0xffffffec;
  }
  *(undefined4 *)((int)puVar6 + -4) = 0x92148;
  uVar7 = sub_9a735(*(undefined2 *)((int)puVar6 + 4));
LAB_00092248:
  return CONCAT44(*(undefined4 *)((int)puVar6 + 0x14),uVar7);
}


// ================================================================================================
// sub_92251 @ 0x92251 [__watcall]
// ================================================================================================

undefined8 __watcall sub_92251(undefined4 param_1)

{
  code *pcVar1;
  bool bVar2;
  uint uVar3;
  undefined4 uVar4;
  int extraout_EDX;
  int extraout_EDX_00;
  undefined2 *puVar5;
  undefined2 *puVar6;
  byte bVar7;
  undefined auStack_14 [4];
  
  puVar6 = (undefined2 *)auStack_14;
  uVar3 = sub_9b72e();
  sub_9b783(param_1,uVar3 | 0x40);
  bVar7 = 0;
  if ((uVar3 & 0x2000) == 0) {
LAB_000922ac:
    uVar4 = 0;
  }
  else {
    pcVar1 = (code *)swi(0x21);
    (*pcVar1)();
    puVar5 = (undefined2 *)&stack0xfffffff0;
    bVar2 = (bVar7 & 1) != 0;
    uVar3 = (extraout_EDX << 1 | (uint)bVar7) >> 1 | (uint)bVar2 << 0x1f;
    if (!bVar2) {
      bVar7 = 0;
      pcVar1 = (code *)swi(0x21);
      (*pcVar1)();
      puVar6 = (undefined2 *)&stack0xfffffff4;
      puVar5 = (undefined2 *)&stack0xfffffff4;
      bVar2 = (bVar7 & 1) != 0;
      uVar3 = (extraout_EDX_00 << 1 | (uint)bVar7) >> 1 | (uint)bVar2 << 0x1f;
      if (!bVar2) goto LAB_000922ac;
    }
    *(undefined4 *)(puVar5 + -2) = 0x9228f;
    uVar4 = sub_9a735(*puVar5,uVar3,param_1);
    puVar6 = puVar5;
  }
  return CONCAT44(*(undefined4 *)((int)puVar6 + 8),uVar4);
}


// ================================================================================================
// read @ 0x922b6 [__watcall]
// ================================================================================================

ssize_t __watcall read(int __fd,void *__buf,size_t __nbytes)

{
  code *pcVar1;
  uint uVar2;
  bool bVar3;
  undefined4 uVar4;
  ssize_t sVar5;
  uint uVar6;
  char *pcVar7;
  int iVar8;
  int iVar9;
  undefined4 *puVar10;
  uint *puVar11;
  undefined4 *puVar12;
  int iVar13;
  int iVar14;
  byte bVar15;
  undefined8 uVar16;
  uint local_28;
  undefined4 local_20;
  uint local_1c;
  byte local_17 [3];
  uint local_14;
  
  local_28 = __fd;
  local_1c = sub_9b72e();
  uVar6 = local_28;
  if (local_1c == 0) {
    uVar4 = 4;
  }
  else {
    if ((local_1c & 1) != 0) {
      bVar15 = 0;
      if ((local_1c & 0x40) == 0) {
        local_20 = 0;
        puVar11 = &local_28;
        while( true ) {
          bVar15 = 0;
          pcVar1 = (code *)swi(0x21);
          uVar16 = (*pcVar1)();
          uVar4 = (undefined4)((ulonglong)uVar16 >> 0x20);
          puVar10 = puVar11 + 1;
          bVar3 = (bVar15 & 1) != 0;
          uVar2 = ((int)uVar16 << 1 | (uint)bVar15) >> 1;
          uVar6 = uVar2 | (uint)bVar3 << 0x1f;
          puVar11[5] = uVar6;
          if (bVar3) goto LAB_00092314;
          puVar12 = puVar11 + 1;
          if (uVar6 == 0) break;
          iVar13 = puVar11[3];
          iVar14 = 0;
          puVar11[6] = (uint)((int)__buf + uVar6);
          iVar9 = 0;
          for (pcVar7 = (char *)__buf; pcVar7 < (char *)puVar11[6]; pcVar7 = pcVar7 + 1) {
            if (*pcVar7 == '\x1a') {
              *puVar11 = 0x92382;
              lseek(puVar11[1],(iVar14 - puVar11[5]) + 1,1);
              return iVar13;
            }
            iVar8 = iVar9;
            if (*pcVar7 != '\r') {
              iVar13 = iVar13 + 1;
              iVar8 = iVar9 + 1;
              *(char *)((int)__buf + iVar9) = *pcVar7;
            }
            iVar14 = iVar14 + 1;
            iVar9 = iVar8;
          }
          iVar14 = puVar11[2];
          puVar11[3] = iVar13;
          __buf = (void *)((int)__buf + iVar9);
          puVar11[2] = iVar14 - iVar9;
          puVar12 = puVar11 + 1;
          if (((*(byte *)((int)puVar11 + 0x11) & 0x20) != 0) ||
             (puVar12 = puVar11 + 1, puVar11 = puVar11 + 1, iVar14 - iVar9 == 0)) break;
        }
      }
      else {
        pcVar1 = (code *)swi(0x21);
        uVar16 = (*pcVar1)();
        uVar4 = (undefined4)((ulonglong)uVar16 >> 0x20);
        puVar10 = (undefined4 *)&stack0xffffffdc;
        bVar3 = (bVar15 & 1) != 0;
        uVar2 = ((int)uVar16 << 1 | (uint)bVar15) >> 1;
        local_1c = uVar2 | (uint)bVar3 << 0x1f;
        puVar12 = (undefined4 *)&stack0xffffffdc;
        if (bVar3) {
LAB_00092314:
          *(undefined4 *)((int)puVar10 + -4) = 0x92319;
          sVar5 = sub_9a735(uVar2 & 0xffff,uVar4,uVar6);
          return sVar5;
        }
      }
      return *(ssize_t *)((int)puVar12 + 8);
    }
    uVar4 = 6;
  }
  sub_9878a(uVar4);
  return -1;
}


// ================================================================================================
// sub_923c9 @ 0x923c9 [__watcall]
// ================================================================================================

longlong __watcall sub_923c9(undefined4 param_1,undefined4 param_2,uint unaff_EBX)

{
  code *pcVar1;
  undefined4 extraout_EDX;
  byte in_CF;
  
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  if ((in_CF & 1) == 0) {
    sub_9b783(extraout_EDX,0);
    return (ulonglong)unaff_EBX << 0x20;
  }
  sub_9878a(4,extraout_EDX,param_1);
  return CONCAT44(unaff_EBX,0xffffffff);
}


// ================================================================================================
// sub_923ce @ 0x923ce [__watcall]
// ================================================================================================

void __watcall sub_923ce(void)

{
  undefined uVar1;
  undefined4 uVar2;
  uint uVar3;
  uint unaff_ECX;
  uint uVar4;
  undefined4 *unaff_ESI;
  undefined4 *unaff_EDI;
  
  for (uVar4 = unaff_ECX >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    LOCK();
    uVar2 = *unaff_ESI;
    *unaff_ESI = *unaff_EDI;
    UNLOCK();
    *unaff_EDI = uVar2;
    unaff_ESI = unaff_ESI + 1;
    unaff_EDI = unaff_EDI + 1;
  }
  uVar4 = (uint)((byte)unaff_ECX & 3);
  uVar3 = unaff_ECX & 3;
  while (uVar3 != 0) {
    LOCK();
    uVar1 = *(undefined *)unaff_ESI;
    *(undefined *)unaff_ESI = *(undefined *)unaff_EDI;
    UNLOCK();
    *(undefined *)unaff_EDI = uVar1;
    unaff_ESI = (undefined4 *)((int)unaff_ESI + 1);
    uVar4 = uVar4 - 1;
    unaff_EDI = (undefined4 *)((int)unaff_EDI + 1);
    uVar3 = uVar4;
  }
  return;
}


// ================================================================================================
// sub_923f4 @ 0x923f4 [__watcall]
// ================================================================================================

undefined4 __watcall
sub_923f4(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,code *unaff_ECX)

{
  int iVar1;
  
  iVar1 = (*unaff_ECX)();
  if (iVar1 < 1) {
    iVar1 = (*unaff_ECX)();
    if (-1 < iVar1) {
      return param_1;
    }
    iVar1 = (*unaff_ECX)();
    if (iVar1 < 1) {
      return unaff_EDX;
    }
  }
  else {
    iVar1 = (*unaff_ECX)();
    if (iVar1 < 1) {
      return param_1;
    }
    iVar1 = (*unaff_ECX)();
    if (0 < iVar1) {
      return unaff_EDX;
    }
  }
  return unaff_EBX;
}


// ================================================================================================
// sub_9244c @ 0x9244c [__watcall]
// ================================================================================================

void __watcall sub_9244c(undefined4 *param_1,uint unaff_EDX,uint unaff_EBX,code *unaff_ECX)

{
  undefined uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined *puVar4;
  uint uVar5;
  undefined *puVar6;
  uint uVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  byte bVar11;
  undefined4 *local_160;
  undefined4 auStack_15c [32];
  uint auStack_dc [32];
  undefined4 local_5c;
  int local_58;
  undefined4 *local_54;
  int local_50;
  int local_4c;
  undefined4 *local_48;
  undefined4 *local_44;
  undefined4 *local_40;
  undefined4 *local_3c;
  int local_38;
  uint local_34;
  int local_30;
  int local_28;
  undefined4 *local_24;
  undefined4 *local_20;
  undefined4 *local_1c;
  
  bVar11 = 0;
  if ((((uint)param_1 | unaff_EBX) & 3) == 0) {
    local_34 = (uint)(4 < unaff_EBX);
  }
  else {
    local_34 = 2;
  }
  local_50 = unaff_EBX * 3;
  local_28 = 0;
  local_4c = unaff_EBX * 2;
  local_160 = param_1;
LAB_00092492:
  do {
    if (1 < unaff_EDX) {
      if (0xf < unaff_EDX) {
        puVar10 = (undefined4 *)((unaff_EDX >> 1) * unaff_EBX + (int)local_160);
        if (0x1d < unaff_EDX) {
          local_48 = local_160;
          puVar9 = (undefined4 *)((int)local_160 + (unaff_EDX - 1) * unaff_EBX);
          if (0x2a < unaff_EDX) {
            local_38 = unaff_EBX * (unaff_EDX >> 3);
            local_58 = local_38 * 2;
            local_48 = (undefined4 *)
                       sub_923f4(local_160,(undefined4 *)((int)local_160 + local_38),
                                 (undefined *)((int)local_160 + local_58),unaff_ECX);
            puVar10 = (undefined4 *)
                      sub_923f4((int)puVar10 - local_38,puVar10,
                                (undefined *)(local_38 + (int)puVar10),unaff_ECX);
            puVar9 = (undefined4 *)
                     sub_923f4((int)puVar9 - local_58,(int)puVar9 - local_38,puVar9,unaff_ECX);
          }
          puVar10 = (undefined4 *)sub_923f4(local_48,puVar10,puVar9,unaff_ECX);
        }
        if (local_34 == 0) {
          local_44 = &local_5c;
          local_5c = *puVar10;
        }
        else {
          local_44 = local_160;
          if (local_34 == 0) {
            uVar2 = *local_160;
            *local_160 = *puVar10;
            *puVar10 = uVar2;
          }
          else {
            sub_923ce();
          }
        }
        local_20 = (undefined4 *)((int)local_160 + (unaff_EDX - 1) * unaff_EBX);
        local_24 = local_160;
        puVar10 = local_160;
        local_1c = local_20;
LAB_0009267e:
        for (; puVar10 <= local_1c; puVar10 = (undefined4 *)((int)puVar10 + unaff_EBX)) {
          iVar3 = (*unaff_ECX)();
          if (0 < iVar3) break;
          if (iVar3 == 0) {
            if (local_34 == 0) {
              uVar2 = *local_24;
              *local_24 = *puVar10;
              *puVar10 = uVar2;
            }
            else {
              sub_923ce();
            }
            local_24 = (undefined4 *)((int)local_24 + unaff_EBX);
          }
        }
        for (; puVar10 <= local_1c; local_1c = (undefined4 *)((int)local_1c - unaff_EBX)) {
          iVar3 = (*unaff_ECX)();
          if (iVar3 < 0) break;
          if (iVar3 == 0) {
            if (local_34 == 0) {
              uVar2 = *local_1c;
              *local_1c = *local_20;
              *local_20 = uVar2;
            }
            else {
              sub_923ce();
            }
            local_20 = (undefined4 *)((int)local_20 - unaff_EBX);
          }
        }
        if (puVar10 <= local_1c) {
          if (local_34 == 0) {
            uVar2 = *puVar10;
            *puVar10 = *local_1c;
            *local_1c = uVar2;
          }
          else {
            sub_923ce();
          }
          puVar10 = (undefined4 *)((int)puVar10 + unaff_EBX);
          local_1c = (undefined4 *)((int)local_1c - unaff_EBX);
          goto LAB_0009267e;
        }
        local_40 = (undefined4 *)((int)local_160 + unaff_EDX * unaff_EBX);
        uVar7 = (int)puVar10 - (int)local_24;
        if ((int)local_24 - (int)local_160 < (int)puVar10 - (int)local_24) {
          uVar7 = (int)local_24 - (int)local_160;
        }
        if (uVar7 != 0) {
          puVar9 = (undefined4 *)((int)puVar10 - uVar7);
          puVar8 = local_160;
          for (uVar5 = uVar7 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
            LOCK();
            uVar2 = *puVar8;
            *puVar8 = *puVar9;
            UNLOCK();
            *puVar9 = uVar2;
            puVar8 = puVar8 + 1;
            puVar9 = puVar9 + (uint)bVar11 * -2 + 1;
          }
          uVar5 = (uint)((byte)uVar7 & 3);
          uVar7 = uVar7 & 3;
          while (uVar7 != 0) {
            LOCK();
            uVar1 = *(undefined *)puVar8;
            *(undefined *)puVar8 = *(undefined *)puVar9;
            UNLOCK();
            *(undefined *)puVar9 = uVar1;
            puVar8 = (undefined4 *)((int)puVar8 + 1);
            uVar5 = uVar5 - 1;
            puVar9 = (undefined4 *)((int)puVar9 + (uint)bVar11 * -2 + 1);
            uVar7 = uVar5;
          }
        }
        puVar4 = (undefined *)((int)local_40 + (-unaff_EBX - (int)local_20));
        puVar6 = (undefined *)((int)local_20 - (int)local_1c);
        if (puVar4 <= (undefined *)((int)local_20 - (int)local_1c)) {
          puVar6 = puVar4;
        }
        if (puVar6 != (undefined *)0x0) {
          puVar9 = (undefined4 *)((int)local_40 - (int)puVar6);
          puVar8 = puVar10;
          for (uVar7 = (uint)puVar6 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
            LOCK();
            uVar2 = *puVar8;
            *puVar8 = *puVar9;
            UNLOCK();
            *puVar9 = uVar2;
            puVar8 = puVar8 + 1;
            puVar9 = puVar9 + (uint)bVar11 * -2 + 1;
          }
          uVar7 = (uint)((byte)puVar6 & 3);
          uVar5 = (uint)puVar6 & 3;
          while (uVar5 != 0) {
            LOCK();
            uVar1 = *(undefined *)puVar8;
            *(undefined *)puVar8 = *(undefined *)puVar9;
            UNLOCK();
            *(undefined *)puVar9 = uVar1;
            puVar8 = (undefined4 *)((int)puVar8 + 1);
            uVar7 = uVar7 - 1;
            puVar9 = (undefined4 *)((int)puVar9 + (uint)bVar11 * -2 + 1);
            uVar5 = uVar7;
          }
        }
        uVar7 = (int)puVar10 - (int)local_24;
        unaff_EDX = (int)local_20 - (int)local_1c;
        if (unaff_EDX < uVar7) {
          if (uVar7 <= unaff_EBX) goto LAB_00092530;
          auStack_15c[local_28] = local_160;
          auStack_dc[local_28] = uVar7 / unaff_EBX;
          local_160 = (undefined4 *)((int)local_40 - unaff_EDX);
        }
        else {
          auStack_dc[local_28] = unaff_EDX / unaff_EBX;
          auStack_15c[local_28] = (undefined4 *)((int)local_40 - unaff_EDX);
          unaff_EDX = uVar7;
        }
        unaff_EDX = unaff_EDX / unaff_EBX;
        local_28 = local_28 + 1;
        goto LAB_00092492;
      }
      local_54 = (undefined4 *)((int)local_160 + unaff_EDX * unaff_EBX);
      for (local_30 = local_50; 0 < local_30; local_30 = local_30 - local_4c) {
        for (local_3c = (undefined4 *)((int)local_160 + local_30); puVar10 = local_3c,
            local_3c < local_54; local_3c = (undefined4 *)((int)local_3c + local_30)) {
          for (; local_160 < puVar10; puVar10 = (undefined4 *)((int)puVar10 - local_30)) {
            puVar9 = (undefined4 *)((int)puVar10 - local_30);
            iVar3 = (*unaff_ECX)();
            if (iVar3 < 1) break;
            if (local_34 == 0) {
              uVar2 = *puVar10;
              *puVar10 = *puVar9;
              *puVar9 = uVar2;
            }
            else {
              sub_923ce();
            }
          }
        }
      }
    }
LAB_00092530:
    if (local_28 == 0) {
      return;
    }
    local_28 = local_28 + -1;
    local_160 = (undefined4 *)auStack_15c[local_28];
    unaff_EDX = auStack_dc[local_28];
  } while( true );
}


// ================================================================================================
// printstr2 @ 0x92890 [__cdecl]
// ================================================================================================

void printstr2(char *param_1)

{
  char cVar1;
  uint uVar2;
  byte bVar3;
  byte bVar4;
  undefined *puVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  byte bVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  int iVar12;
  int iVar13;
  uint uVar14;
  int iVar15;
  uint uVar16;
  uint uVar17;
  byte *pbVar18;
  bool bVar19;
  undefined4 uVar20;
  uint local_2c;
  uint local_28;
  int local_24;
  uint local_1c;
  
  uVar7 = dword_d42ac;
  uVar6 = dword_d42a8;
  puVar5 = off_d42a4;
  uVar9 = (uint)byte_d42c1;
  uVar14 = (uint)byte_d42c0;
  uVar10 = (byte)off_d42a4[3] - 0x30;
  bVar19 = dword_d42bc == 0x464e544d;
  cVar1 = *param_1;
  uVar20 = dword_d42dc;
  while (cVar1 != '\0') {
    bVar8 = *param_1 - byte_d42c0;
    if ((int)(uint)bVar8 < (int)((uVar9 - uVar14) + 1)) {
      bVar4 = byte_d42c2;
      if (off_d42c8 != (undefined *)0x0) {
        bVar4 = off_d42c8[bVar8];
      }
      uVar2 = (uint)bVar4;
      bVar3 = byte_d42c3;
      if (dword_d42cc != 0) {
        bVar3 = *(byte *)(dword_d42cc + (CONCAT11(bVar4,bVar8) & 0xff));
      }
      uVar11 = (uint)CONCAT11(bVar3,bVar8);
      local_2c = (uint)bVar3;
      if (dword_d42d0 == 0) {
        uVar16 = byte_d42c4 + uVar2;
      }
      else {
        uVar16 = (uint)*(byte *)((uVar11 & 0xff) + dword_d42d0);
      }
      if (dword_d42d4 == 0) {
        uVar17 = 0;
      }
      else {
        uVar17 = (uint)*(byte *)((uVar11 & 0xff) + dword_d42d4);
      }
      iVar12 = dword_d42b0 + uVar17;
      if (dword_d42d8 == 0) {
        uVar17 = 0;
      }
      else {
        uVar17 = (uint)*(byte *)((uVar11 & 0xff) + dword_d42d8);
      }
      iVar13 = uVar17 + dword_d42b4;
      iVar15 = *(int *)(off_d42e0 + (uVar11 & 0xff) * 4);
      if (bVar19) {
        if ((uVar2 != 0) && (bVar3 != 0)) {
          setclip(iVar12,iVar12 + uVar2,iVar13,local_2c + iVar13);
          drawshape(uVar20,iVar12 - iVar15,iVar13);
          setclip(0,dword_d30a4,0,dword_d30a8);
        }
      }
      else if (iVar15 != 0) {
        pbVar18 = puVar5 + iVar15;
        if (uVar10 < 4) {
          if (uVar10 == 1) {
            sub_90ec0(iVar12,iVar13,uVar2,local_2c,uVar7,uVar20);
            while (local_2c = local_2c - 1, local_2c != 0xffffffff) {
              if ((iVar13 < dword_d30b0) || (dword_d30b8 <= iVar13)) {
                pbVar18 = pbVar18 + ((int)(uVar2 + 7) >> 3);
              }
              else {
                iVar15 = iVar12;
                local_1c = uVar2;
                if (uVar2 != 0) {
                  do {
                    if ((*pbVar18 & 0x80) != 0) {
                      sub_b5d80(iVar15,iVar13,uVar6);
                    }
                    if ((*pbVar18 & 0x40) != 0) {
                      sub_b5d80(iVar15 + 1,iVar13,uVar6);
                    }
                    if ((*pbVar18 & 0x20) != 0) {
                      sub_b5d80(iVar15 + 2,iVar13,uVar6);
                    }
                    if ((*pbVar18 & 0x10) != 0) {
                      sub_b5d80(iVar15 + 3,iVar13,uVar6);
                    }
                    if ((*pbVar18 & 8) != 0) {
                      sub_b5d80(iVar15 + 4,iVar13,uVar6);
                    }
                    if ((*pbVar18 & 4) != 0) {
                      sub_b5d80(iVar15 + 5,iVar13,uVar6);
                    }
                    if ((*pbVar18 & 2) != 0) {
                      sub_b5d80(iVar15 + 6,iVar13,uVar6);
                    }
                    if ((*pbVar18 & 1) != 0) {
                      sub_b5d80(iVar15 + 7,iVar13,uVar6);
                    }
                    iVar15 = iVar15 + 8;
                    local_1c = local_1c - 8;
                    pbVar18 = pbVar18 + 1;
                  } while (0 < (int)local_1c);
                }
              }
              iVar13 = iVar13 + 1;
            }
          }
        }
        else if (uVar10 < 5) {
          sub_90ec0(iVar12,iVar13,uVar2,local_2c,uVar7,uVar20);
          while (local_2c = local_2c - 1, local_2c != 0xffffffff) {
            if ((iVar13 < dword_d30b0) || (dword_d30b8 <= iVar13)) {
              pbVar18 = pbVar18 + ((int)(uVar2 + 1) >> 1);
            }
            else {
              iVar15 = iVar12;
              local_28 = uVar2;
              if (uVar2 != 0) {
                do {
                  if ((int)(uint)*pbVar18 >> 4 != 0) {
                    sub_b5d80(iVar15,iVar13,(int)(uint)*pbVar18 >> 4);
                  }
                  if ((*pbVar18 & 0xf) != 0) {
                    sub_b5d80(iVar15 + 1,iVar13,*pbVar18 & 0xf);
                  }
                  iVar15 = iVar15 + 2;
                  local_28 = local_28 - 2;
                  pbVar18 = pbVar18 + 1;
                } while (0 < (int)local_28);
              }
            }
            iVar13 = iVar13 + 1;
          }
        }
        else if (uVar10 == 8) {
          sub_90ec0(iVar12,iVar13,uVar2,local_2c,uVar7,uVar20);
          while (local_2c = local_2c - 1, local_2c != 0xffffffff) {
            if ((iVar13 < dword_d30b0) || (uVar11 = uVar2, local_24 = iVar12, dword_d30b8 <= iVar13)
               ) {
              pbVar18 = pbVar18 + uVar2;
            }
            else {
              while (uVar11 - 1 != 0xffffffff) {
                if (*pbVar18 != 0) {
                  sub_b5d80(local_24,iVar13,*pbVar18);
                }
                pbVar18 = pbVar18 + 1;
                uVar11 = uVar11 - 1;
                local_24 = local_24 + 1;
              }
            }
            iVar13 = iVar13 + 1;
          }
        }
      }
      dword_d42b0 = dword_d42b0 + uVar16;
    }
    cVar1 = param_1[1];
    param_1 = param_1 + 1;
  }
  return;
}


// ================================================================================================
// printstr2_at @ 0x92cd0 [__cdecl]
// ================================================================================================

void printstr2_at(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  settextxy(param_2,param_3);
  printstr2(param_1);
  return;
}


// ================================================================================================
// sub_92cf0 @ 0x92cf0 [__watcall]
// ================================================================================================

void __watcall sub_92cf0(void)

{
  undefined in_stack_00000004;
  undefined4 in_stack_00000008;
  undefined4 in_stack_0000000c;
  undefined local_4;
  undefined local_3;
  
  settextxy(in_stack_00000008,in_stack_0000000c);
  local_4 = in_stack_00000004;
  local_3 = 0;
  printstr2(&local_4);
  return;
}


// ================================================================================================
// stricmp @ 0x92d21 [__watcall]
// ================================================================================================

int __watcall stricmp(byte *param_1,byte *unaff_EDX)

{
  byte bVar1;
  byte bVar2;
  
  while( true ) {
    bVar1 = *param_1;
    bVar2 = *unaff_EDX;
    if ((0x40 < bVar1) && (bVar1 < 0x5b)) {
      bVar1 = bVar1 + 0x20;
    }
    if ((0x40 < bVar2) && (bVar2 < 0x5b)) {
      bVar2 = bVar2 + 0x20;
    }
    if ((bVar1 != bVar2) || (bVar2 == 0)) break;
    param_1 = param_1 + 1;
    unaff_EDX = unaff_EDX + 1;
  }
  return (uint)bVar1 - (uint)bVar2;
}


// ================================================================================================
// remove @ 0x92d5a [__watcall]
// ================================================================================================

int __watcall remove(char *__filename)

{
  code *pcVar1;
  int iVar2;
  byte in_CF;
  
  pcVar1 = (code *)swi(0x21);
  iVar2 = (*pcVar1)();
  if ((in_CF & 1) != 0) {
    iVar2 = sub_9a735((iVar2 << 1 | (uint)in_CF) >> 1 & 0xffff);
    return iVar2;
  }
  return 0;
}


// ================================================================================================
// sub_92d7c @ 0x92d7c [__watcall]
// ================================================================================================

undefined8 __watcall sub_92d7c(byte *param_1,undefined4 unaff_EDX)

{
  byte bVar1;
  byte bVar2;
  int iVar3;
  
  while (((&unk_c4b6c)[(byte)(*param_1 + 1)] & 2) != 0) {
    param_1 = param_1 + 1;
  }
  bVar1 = *param_1;
  if ((bVar1 == 0x2b) || (bVar1 == 0x2d)) {
    param_1 = param_1 + 1;
  }
  iVar3 = 0;
  while (((&unk_c4b6c)[(byte)(*param_1 + 1)] & 0x20) != 0) {
    bVar2 = *param_1;
    param_1 = param_1 + 1;
    iVar3 = iVar3 * 10 + (uint)bVar2 + -0x30;
  }
  if (bVar1 == 0x2d) {
    iVar3 = -iVar3;
  }
  return CONCAT44(unaff_EDX,iVar3);
}


// ================================================================================================
// filesize @ 0x92de0 [__cdecl]
// ================================================================================================

void filesize(undefined4 param_1)

{
  filesize_handle(param_1,1);
  return;
}


// ================================================================================================
// sub_92df0 @ 0x92df0 [__watcall]
// ================================================================================================

void __watcall sub_92df0(void)

{
  undefined4 in_stack_00000004;
  
  filesize_handle(in_stack_00000004,0);
  return;
}


// ================================================================================================
// filesize_handle @ 0x92e00 [__cdecl]
// ================================================================================================

undefined4 filesize_handle(undefined4 param_1,undefined4 param_2)

{
  undefined4 local_c;
  undefined local_8 [4];
  undefined4 local_4;
  
  openhandle(param_1,&local_4,local_8,&local_c,param_2);
  closehandle(local_4);
  return local_c;
}


// ================================================================================================
// sub_92e40 @ 0x92e40 [__cdecl]
// ================================================================================================

int sub_92e40(undefined4 param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_14;
  undefined local_10 [4];
  int local_c;
  
  iVar1 = sub_8d714();
  if (iVar1 == 0) {
    openhandle(param_1,&local_14,local_10,&local_c,param_3);
    if (local_c != 0) {
      sub_b3c74(local_14,param_2,local_c);
      closehandle(local_14);
      local_c = param_2;
    }
  }
  else {
    uVar2 = sub_8dbc0(iVar1);
    sub_b3abc(iVar1,param_2,uVar2);
    freemem(iVar1);
    local_c = iVar1;
  }
  return local_c;
}


// ================================================================================================
// sub_92ecc @ 0x92ecc [__watcall]
// ================================================================================================

void __watcall sub_92ecc(void)

{
  undefined4 in_stack_00000004;
  undefined4 in_stack_00000008;
  
  sub_92e40(in_stack_00000004,in_stack_00000008,1);
  return;
}


// ================================================================================================
// sub_92ee4 @ 0x92ee4 [__cdecl]
// ================================================================================================

void sub_92ee4(undefined4 param_1,undefined4 param_2)

{
  sub_92e40(param_1,param_2,0);
  return;
}


// ================================================================================================
// strcspn @ 0x92ef9 [__watcall]
// ================================================================================================

size_t __watcall strcspn(char *__s,char *__reject)

{
  byte bVar1;
  size_t sVar2;
  undefined2 in_DS;
  byte abStack_28 [36];
  
  sub_9b798(abStack_28,in_DS);
  sVar2 = 0;
  while ((bVar1 = *__s, bVar1 != 0 && ((abStack_28[bVar1 >> 3] & (&unk_c4c70)[bVar1 & 7]) == 0))) {
    sVar2 = sVar2 + 1;
    __s = (char *)((byte *)__s + 1);
  }
  return sVar2;
}


// ================================================================================================
// sub_92f50 @ 0x92f50 [__cdecl]
// ================================================================================================

void sub_92f50(int param_1,int param_2,int param_3,int param_4,undefined4 param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = param_4;
  iVar3 = param_3;
  if (param_3 < param_1) {
    iVar3 = param_1;
    param_1 = param_3;
  }
  iVar1 = (iVar3 - param_1) + 1;
  if (param_4 < param_2) {
    param_4 = param_2;
    param_2 = iVar2;
  }
  iVar2 = (param_4 - param_2) + -1;
  sub_91044(param_1,param_2,iVar1,1,param_5,iVar2);
  sub_91044(iVar3,param_2 + 1,1,iVar2,param_5);
  sub_91044(param_1,param_2 + 1,1,iVar2,param_5);
  sub_91044(param_1,param_4,iVar1,1,param_5);
  return;
}


// ================================================================================================
// sub_93000 @ 0x93000 [__cdecl]
// ================================================================================================

void sub_93000(int param_1,int param_2,int param_3,int param_4,undefined4 param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = param_4;
  iVar3 = param_3;
  if (param_3 < param_1) {
    iVar3 = param_1;
    param_1 = param_3;
  }
  iVar1 = (iVar3 - param_1) + 1;
  if (param_4 < param_2) {
    param_4 = param_2;
    param_2 = iVar2;
  }
  iVar2 = (param_4 - param_2) + -1;
  sub_90ec0(param_1,param_2,iVar1,1,param_5,iVar2);
  sub_90ec0(iVar3,param_2 + 1,1,iVar2,param_5);
  sub_90ec0(param_1,param_2 + 1,1,iVar2,param_5);
  sub_90ec0(param_1,param_4,iVar1,1,param_5);
  return;
}


// ================================================================================================
// mkdir @ 0x930a7 [__watcall]
// ================================================================================================

int __watcall mkdir(char *__path,__mode_t __mode)

{
  code *pcVar1;
  int iVar2;
  byte in_CF;
  
  pcVar1 = (code *)swi(0x21);
  iVar2 = (*pcVar1)();
  if ((in_CF & 1) != 0) {
    iVar2 = sub_9a735((iVar2 << 1 | (uint)in_CF) >> 1 & 0xffff);
    return iVar2;
  }
  return 0;
}


// ================================================================================================
// sub_930c6 @ 0x930c6 [__watcall]
// ================================================================================================

undefined8 __watcall sub_930c6(int param_1,undefined4 unaff_EDX)

{
  undefined4 *puVar1;
  byte *pbVar2;
  uint uVar3;
  undefined8 uVar4;
  
  puVar1 = *(undefined4 **)(param_1 + 8);
  if (((((int)puVar1[1] < 1) || ((*(byte *)(puVar1 + 3) & 4) != 0)) || (*(char *)*puVar1 == '\r'))
     || (*(char *)*puVar1 == '\x1a')) {
    uVar4 = sub_9b833(*(undefined4 *)(param_1 + 8));
    param_1 = (int)((ulonglong)uVar4 >> 0x20);
    uVar3 = (uint)uVar4;
  }
  else {
    puVar1[1] = puVar1[1] + -1;
    pbVar2 = (byte *)**(int **)(param_1 + 8);
    **(int **)(param_1 + 8) = (int)(pbVar2 + 1);
    uVar3 = (uint)*pbVar2;
  }
  if (uVar3 == 0xffffffff) {
    *(byte *)(param_1 + 0x10) = *(byte *)(param_1 + 0x10) | 2;
  }
  return CONCAT44(unaff_EDX,uVar3);
}


// ================================================================================================
// sub_93114 @ 0x93114 [__watcall]
// ================================================================================================

void __watcall sub_93114(undefined4 param_1,int unaff_EDX)

{
  sub_9b996(param_1,*(undefined4 *)(unaff_EDX + 8));
  return;
}


// ================================================================================================
// sub_9311c @ 0x9311c [__cdecl]
// ================================================================================================

void sub_9311c(void)

{
  sub_9ba18(sub_930c6,sub_93114);
  return;
}


// ================================================================================================
// fscanf @ 0x93143 [__cdecl]
// ================================================================================================

int fscanf(FILE *__stream,char *__format,...)

{
  int iVar1;
  
  iVar1 = sub_9311c(&stack0x0000000c);
  return iVar1;
}


// ================================================================================================
// printf_at @ 0x93170 [__cdecl]
// ================================================================================================

void printf_at(undefined4 param_1,undefined4 param_2,char *param_3)

{
  char local_104 [256];
  undefined *local_4;
  
  local_4 = &stack0x00000010;
  vsprintf(local_104,param_3,&local_4);
  printstr2_at(local_104,param_1,param_2);
  return;
}


// ================================================================================================
// sub_931d0 @ 0x931d0 [__cdecl]
// ================================================================================================

void sub_931d0(byte *param_1,char *param_2,int param_3)

{
  byte bVar1;
  char *pcVar2;
  
  if (param_3 != 0) {
    pcVar2 = param_2 + param_3;
    do {
      bVar1 = *param_1;
      param_1 = param_1 + 1;
      if (*(char *)((int)&unk_d42e4 + (uint)bVar1) != -1) {
        *param_2 = *(char *)((int)&unk_d42e4 + (uint)bVar1);
      }
      param_2 = param_2 + 1;
    } while (param_2 < pcVar2);
  }
  return;
}


// ================================================================================================
// drawshape2_trans @ 0x931fc [__cdecl]
// ================================================================================================

void drawshape2_trans(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  if (dword_d30c8 == 0) {
    sub_b6d47(param_1,param_2,param_3);
    return;
  }
  funcptr_d43e4 = sub_931d0;
  drawshape2(param_1,param_2,param_3);
  funcptr_d43e4 = sub_b3abc;
  return;
}


// ================================================================================================
// sub_93240 @ 0x93240 [__cdecl]
// ================================================================================================

void sub_93240(int param_1)

{
  drawshape2_trans(param_1,*(int *)(param_1 + 10) >> 0x10,*(int *)(param_1 + 0xc) >> 0x10);
  return;
}


// ================================================================================================
// sub_9325c @ 0x9325c [__cdecl]
// ================================================================================================

void sub_9325c(int param_1,int param_2,int param_3)

{
  drawshape2_trans(param_1,param_2 - (*(int *)(param_1 + 6) >> 0x10),
                   param_3 - (*(int *)(param_1 + 8) >> 0x10));
  return;
}


// ================================================================================================
// sub_93284 @ 0x93284 [__watcall]
// ================================================================================================

int __watcall sub_93284(byte *param_1)

{
  byte bVar1;
  int iVar2;
  byte abStack_28 [32];
  
  sub_9b7f5(abStack_28);
  iVar2 = 0;
  while ((bVar1 = *param_1, bVar1 != 0 && ((abStack_28[bVar1 >> 3] & (&unk_c4c70)[bVar1 & 7]) == 0))
        ) {
    iVar2 = iVar2 + 1;
    param_1 = param_1 + 1;
  }
  return iVar2;
}


// ================================================================================================
// savefile @ 0x932d0 [__cdecl]
// ================================================================================================

void savefile(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  savefileblock(param_1,param_2,param_3,1);
  return;
}


// ================================================================================================
// sub_932ec @ 0x932ec [__cdecl]
// ================================================================================================

void sub_932ec(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  savefileblock(param_1,param_2,param_3,0);
  return;
}


// ================================================================================================
// savefileblock @ 0x93308 [__cdecl]
// ================================================================================================

void savefileblock(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 local_28 [5];
  undefined4 local_14;
  undefined4 local_10;
  
  local_28[0] = param_2;
  local_14 = param_3;
  local_10 = 0;
  savefileblocka(param_1,local_28,param_4);
  return;
}


// ================================================================================================
// sub_9333c @ 0x9333c [__watcall]
// ================================================================================================

void __watcall sub_9333c(void)

{
  undefined4 in_stack_00000004;
  undefined4 in_stack_00000008;
  
  savefileblocka(in_stack_00000004,in_stack_00000008,1);
  return;
}


// ================================================================================================
// sub_93354 @ 0x93354 [__watcall]
// ================================================================================================

void __watcall sub_93354(void)

{
  undefined4 in_stack_00000004;
  undefined4 in_stack_00000008;
  
  savefileblocka(in_stack_00000004,in_stack_00000008,0);
  return;
}


// ================================================================================================
// savefileblocka @ 0x9336c [__cdecl]
// ================================================================================================

undefined4 savefileblocka(undefined4 param_1,undefined4 param_2,int param_3)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined auStack_18 [4];
  undefined local_14 [4];
  int local_10;
  
  uVar1 = sub_8dbdc(param_2);
  uVar2 = sub_8dbd4(param_2);
  sub_b3b44(param_1,&local_10,local_14,auStack_18);
  if (local_10 == 0) {
    if (param_3 != 0) {
      fatalerror(aSavefileblockaOPENFAILED,param_1);
    }
    uVar1 = 0;
  }
  else {
    sub_b3c70(local_10,uVar2,uVar1);
    closehandle(local_10);
    uVar1 = 1;
  }
  return uVar1;
}


// ================================================================================================
// imul32 @ 0x933f0 [__cdecl]
// ================================================================================================

longlong imul32(int param_1,int param_2)

{
  return (longlong)param_1 * (longlong)param_2;
}


// ================================================================================================
// sub_933fb @ 0x933fb [__cdecl]
// ================================================================================================

longlong sub_933fb(uint param_1,uint param_2)

{
  return (ulonglong)param_1 * (ulonglong)param_2;
}


// ================================================================================================
// sub_93406 @ 0x93406 [__cdecl]
// ================================================================================================

int sub_93406(int param_1,int param_2)

{
  return param_1 / param_2;
}


// ================================================================================================
// sub_93412 @ 0x93412 [__cdecl]
// ================================================================================================

uint sub_93412(uint param_1,uint param_2)

{
  return param_1 / param_2;
}


// ================================================================================================
// sub_9341f @ 0x9341f [__cdecl]
// ================================================================================================

int sub_9341f(int param_1,int param_2)

{
  return param_1 / param_2;
}


// ================================================================================================
// sub_9342b @ 0x9342b [__cdecl]
// ================================================================================================

uint sub_9342b(uint param_1,uint param_2)

{
  return (uint)(((ulonglong)param_1 << 0x20) / (ulonglong)param_2) >> 0xc;
}


// ================================================================================================
// sub_9343b @ 0x9343b [__cdecl]
// ================================================================================================

undefined4 sub_9343b(int param_1,int param_2,int param_3)

{
  return (int)(((longlong)param_1 * (longlong)param_2) / (longlong)param_3);
}


// ================================================================================================
// sub_9344c @ 0x9344c [__cdecl]
// ================================================================================================

undefined4 sub_9344c(ulonglong param_1,uint param_3)

{
  return (int)(param_1 / param_3);
}


// ================================================================================================
// sub_9345b @ 0x9345b [__cdecl]
// ================================================================================================

undefined4 sub_9345b(int param_1)

{
  return (int)(0x100000000 / (longlong)param_1);
}


// ================================================================================================
// isqrt32 @ 0x93470 [__cdecl]
// ================================================================================================

uint isqrt32(uint param_1)

{
  byte bVar1;
  ushort uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  byte bVar7;
  ushort uVar8;
  
  if (0xffff < param_1) {
    uVar6 = param_1 >> 0x10;
    uVar2 = CONCAT11((char)(param_1 >> 0x18) + '\b',(char)(param_1 >> 0x10));
    uVar2 = (ushort)(uVar2 + (short)((uVar6 << 0x10 | param_1 & 0xffff) / (uint)uVar2)) >> 1;
    uVar2 = (ushort)(uVar2 + (short)((uVar6 << 0x10 | param_1 & 0xffff) / (uint)uVar2)) >> 1;
    uVar2 = (ushort)(uVar2 + (short)((uVar6 << 0x10 | param_1 & 0xffff) / (uint)uVar2)) >> 1;
    return (uint)((ushort)((short)((uVar6 << 0x10 | param_1 & 0xffff) / (uint)uVar2) + uVar2) >> 1);
  }
  if (0x930 < param_1) {
    bVar1 = (byte)(param_1 >> 8);
    bVar7 = bVar1 + 0x30;
    if (bVar1 < 0xd0) {
      bVar1 = (byte)((ushort)param_1 / (ushort)bVar7);
      bVar7 = (byte)(bVar7 + bVar1) >> 1 | CARRY1(bVar7,bVar1) << 7;
      bVar1 = (byte)((ushort)param_1 / (ushort)bVar7);
      return (uint)(byte)((byte)(bVar1 + bVar7) >> 1 | CARRY1(bVar1,bVar7) << 7);
    }
    uVar8 = (short)(param_1 >> 9) + 0x80;
    uVar2 = (ushort)((param_1 & 0xffff) / (uint)uVar8);
    return (uint)(ushort)((ushort)(uVar2 + uVar8) >> 1 | (ushort)CARRY2(uVar2,uVar8) << 0xf);
  }
  uVar6 = param_1 >> 1;
  if (uVar6 != 0) {
    iVar3 = -6;
    do {
      uVar6 = uVar6 - (iVar3 + 0x10);
      iVar4 = iVar3 + 0x10;
      if ((int)uVar6 < 0) break;
      uVar6 = uVar6 - (iVar3 + 0x20);
      iVar4 = iVar3 + 0x20;
      if ((int)uVar6 < 0) break;
      uVar6 = uVar6 - (iVar3 + 0x30);
      iVar4 = iVar3 + 0x30;
      if ((int)uVar6 < 0) break;
      iVar3 = iVar3 + 0x40;
      uVar6 = uVar6 - iVar3;
      iVar4 = iVar3;
    } while (-1 < (int)uVar6);
    uVar5 = iVar4 - 6U >> 2;
    iVar3 = (uVar6 + iVar4) - uVar5;
    param_1 = uVar5;
    if (-1 < iVar3) {
      param_1 = uVar5 + 1;
      iVar3 = iVar3 - param_1;
      if ((-1 < iVar3) && (param_1 = uVar5 + 2, -1 < (int)(iVar3 - param_1))) {
        param_1 = uVar5 + 3;
      }
    }
  }
  return param_1;
}


// ================================================================================================
// sub_93540 @ 0x93540 [__cdecl]
// ================================================================================================

void sub_93540(int param_1,int param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  int *piVar7;
  undefined4 *puVar8;
  int iVar9;
  
  iVar4 = param_1 >> 1;
  do {
    iVar3 = iVar4;
    if (iVar4 < 1) {
      return;
    }
    for (; iVar3 < param_1; iVar3 = iVar3 + 1) {
      for (iVar5 = iVar3 - iVar4; -1 < iVar5; iVar5 = iVar5 - iVar4) {
        iVar9 = (iVar4 + iVar5) * 4;
        piVar7 = (int *)(param_2 + iVar9);
        piVar6 = (int *)(param_2 + iVar5 * 4);
        if (*piVar7 <= *piVar6) break;
        iVar1 = *piVar6;
        *piVar6 = *piVar7;
        *piVar7 = iVar1;
        puVar8 = (undefined4 *)(iVar5 * 4 + param_3);
        uVar2 = *puVar8;
        *puVar8 = *(undefined4 *)(param_3 + iVar9);
        *(undefined4 *)(param_3 + iVar9) = uVar2;
      }
    }
    iVar4 = iVar4 >> 1;
  } while( true );
}


// ================================================================================================
// sub_935e0 @ 0x935e0 [__cdecl]
// ================================================================================================

void sub_935e0(char *param_1)

{
  char acStack_104 [256];
  undefined *local_4;
  
  if (1 < dword_d4534) {
    local_4 = &stack0x00000008;
    vsprintf(acStack_104,param_1,&local_4);
    local_4 = (undefined *)0x0;
    sub_936c0();
  }
  return;
}


// ================================================================================================
// sub_9362c @ 0x9362c [__cdecl]
// ================================================================================================

void sub_9362c(int param_1,int param_2,char *param_3)

{
  char acStack_108 [256];
  undefined *local_8;
  
  if (1 < dword_d4534) {
    if ((((-1 < param_1) && (param_1 < 0x50)) && (-1 < param_2)) && (param_2 < 0x19)) {
      dword_d4540 = (param_2 * 0x50 + param_1) * 2;
    }
    local_8 = &stack0x00000010;
    vsprintf(acStack_108,param_3,&local_8);
    local_8 = (undefined *)0x0;
    sub_936c0();
  }
  return;
}


// ================================================================================================
// sub_936c0 @ 0x936c0 [__cdecl]
// ================================================================================================

void sub_936c0(void)

{
  byte bVar1;
  byte *in_EAX;
  int iVar2;
  uint uVar3;
  int iVar4;
  byte *pbVar5;
  int iVar6;
  byte local_1c;
  
  uVar3 = 0xffffffff;
  pbVar5 = in_EAX;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    bVar1 = *pbVar5;
    pbVar5 = pbVar5 + 1;
  } while (bVar1 != 0);
  iVar4 = ~uVar3 - 1;
  local_1c = 0;
  iVar6 = 0;
  if (iVar4 < 1) {
    return;
  }
LAB_000936e8:
  while( true ) {
    if (local_1c == 0xe) {
      sub_93908(*in_EAX);
      local_1c = 0;
      goto LAB_0009382f;
    }
    local_1c = *in_EAX;
    if (local_1c < 0x20) break;
    sub_93844();
    *(ushort *)(dword_d453c + dword_d4540) = (ushort)byte_d4545 * 0x100 + (ushort)local_1c;
    dword_d4540 = dword_d4540 + 2;
    in_EAX = in_EAX + 1;
    iVar6 = iVar6 + 1;
    if (iVar4 <= iVar6) {
      return;
    }
  }
  if (4 < (byte)(local_1c - 8)) goto LAB_0009382f;
  iVar2 = dword_d4540 / 0xa0;
  switch(local_1c) {
  case 8:
    if (1 < dword_d4540) {
      dword_d4540 = dword_d4540 + -2;
      in_EAX = in_EAX + 1;
      iVar6 = iVar6 + 1;
      if (iVar4 <= iVar6) {
        return;
      }
      goto LAB_000936e8;
    }
    break;
  case 9:
    if (1 < byte_d4546) {
      dword_d4540 = (((dword_d4540 % 0xa0) / 2) / (int)(uint)byte_d4546 + 1) * (uint)byte_d4546 * 2
                    + iVar2 * 0xa0;
    }
    break;
  case 10:
    goto switchD_00093775_caseD_a;
  case 0xb:
    dword_d4540 = (uint)byte_d4544 * 0xa0;
    break;
  case 0xc:
    sub_938c8(iVar2,dword_d4540 % 0xa0);
    dword_d4540 = (uint)byte_d4544 * 0xa0;
  }
LAB_0009382f:
  in_EAX = in_EAX + 1;
  iVar6 = iVar6 + 1;
  if (iVar4 <= iVar6) {
    return;
  }
  goto LAB_000936e8;
switchD_00093775_caseD_a:
  dword_d4540 = (iVar2 + 1) * 0xa0;
  sub_93844();
  in_EAX = in_EAX + 1;
  iVar6 = iVar6 + 1;
  if (iVar4 <= iVar6) {
    return;
  }
  goto LAB_000936e8;
}


// ================================================================================================
// sub_93844 @ 0x93844 [__watcall]
// ================================================================================================

void __watcall
sub_93844(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  uint uVar1;
  
  if (3999 < dword_d4540) {
    uVar1 = (uint)byte_d4544;
    sub_b3abc((uVar1 + 1) * 0xa0 + dword_d453c,uVar1 * 0xa0 + dword_d453c,(0x18 - uVar1) * 0xa0,
              unaff_EDX,unaff_ECX,unaff_EBX);
    sub_b3fc2(dword_d453c + 0xf00,0xa0);
    dword_d4540 = 0xf00;
  }
  return;
}


