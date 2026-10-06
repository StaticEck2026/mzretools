// Decompiled by Ghidra from hockey.elf (via ledisasm ELF export)
// This is machine generated pseudo-C meant as a reference for porting, it does not compile as is.
#include "prototypes.h"

// ================================================================================================
// sub_7aaaa @ 0x7aaaa [__watcall]
// ================================================================================================

void __watcall sub_7aaaa(void)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int *piVar5;
  undefined4 uVar6;
  int iStack_1c;
  
  __CHK(0x2c);
  piVar4 = &asc_d14f0;
  iStack_1c = 0;
  do {
    piVar5 = piVar4;
    if (iStack_1c == 5) {
      iStack_1c = 6;
      piVar5 = piVar4 + 8;
    }
    if ((dword_ed360 & 1 << ((byte)iStack_1c & 0x1f)) == 0) {
      iVar2 = piVar5[1];
      iVar3 = *piVar5;
      uVar6 = dword_ed780;
    }
    else {
      iVar2 = piVar5[1];
      iVar3 = *piVar5;
      uVar6 = dword_ed788;
    }
    drawshape_trans(uVar6,iVar3 + 10,iVar2 + 0x13);
    iStack_1c = iStack_1c + 1;
    piVar4 = piVar5 + 8;
  } while (iStack_1c < 9);
  uVar1 = dword_ed360 & 0xe00;
  if (uVar1 < 0x400) {
    if (uVar1 != 0x200) goto LAB_0007ab95;
    iVar2 = piVar5[9] + 0x13;
    iVar3 = *piVar4 + 10;
    uVar6 = dword_ed75c;
  }
  else if (uVar1 < 0x401) {
    iVar2 = piVar5[9] + 0x13;
    iVar3 = *piVar4 + 10;
    uVar6 = dword_ed764;
  }
  else {
    if (uVar1 != 0x800) goto LAB_0007ab95;
    iVar2 = piVar5[9] + 0x13;
    iVar3 = *piVar4 + 10;
    uVar6 = dword_ed760;
  }
  drawshape_trans(uVar6,iVar3,iVar2);
LAB_0007ab95:
  uVar1 = dword_ed360 & 0xf000;
  piVar4 = piVar5 + 0x14;
  if (uVar1 < 0x2000) {
    if (uVar1 != 0x1000) {
      return;
    }
    iVar2 = piVar5[0x15] + 0x13;
    iVar3 = *piVar4 + 10;
    uVar6 = dword_ed770;
  }
  else if (uVar1 < 0x2001) {
    iVar2 = piVar5[0x15] + 0x13;
    iVar3 = *piVar4 + 10;
    uVar6 = dword_ed77c;
  }
  else {
    if (uVar1 < 0x4000) {
      return;
    }
    if (uVar1 < 0x4001) {
      iVar2 = piVar5[0x15] + 0x13;
      iVar3 = *piVar4 + 10;
      uVar6 = dword_ed784;
    }
    else {
      if (uVar1 != 0x8000) {
        return;
      }
      iVar2 = piVar5[0x15] + 0x13;
      iVar3 = *piVar4 + 10;
      uVar6 = dword_ed768;
    }
  }
  drawshape_trans(uVar6,iVar3,iVar2);
  return;
}


// ================================================================================================
// sub_7ac31 @ 0x7ac31 [__watcall]
// ================================================================================================

longlong __watcall sub_7ac31(undefined4 param_1,uint unaff_EDX)

{
  undefined4 *puVar1;
  undefined4 extraout_EDX;
  undefined4 ***pppuVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  byte bVar7;
  ulonglong uVar8;
  undefined8 uVar9;
  undefined4 *local_2c;
  undefined4 **local_28;
  int local_24;
  undefined4 **local_20;
  int iStack_1c;
  
  bVar7 = 0;
  __CHK(0x3c);
  setpalette(0xf7,4,&unk_d16a0);
  getmouse(&local_2c,&iStack_1c,&local_20);
  local_24 = iStack_1c;
  local_28 = local_20;
  setdefaultscreen();
  puVar1 = (undefined4 *)
           allocmem(aPointer_c32f5,
                    (((int)pointer_shapes[1] >> 0x10) + 1) *
                    ((*(int *)((int)pointer_shapes + 2) >> 0x10) + 1) + 0x11,0x20);
  puVar5 = puVar1 + (uint)bVar7 * -2 + 1;
  puVar3 = pointer_shapes + (uint)bVar7 * -2 + 1;
  *puVar1 = *pointer_shapes;
  puVar6 = puVar5 + (uint)bVar7 * -2 + 1;
  puVar4 = puVar3 + (uint)bVar7 * -2 + 1;
  *puVar5 = *puVar3;
  *puVar6 = *puVar4;
  puVar6[(uint)bVar7 * -2 + 1] = puVar4[(uint)bVar7 * -2 + 1];
  *(undefined *)(puVar6 + (uint)bVar7 * -2 + 1 + (uint)bVar7 * -2 + 1) =
       *(undefined *)(puVar4 + (uint)bVar7 * -2 + 1 + (uint)bVar7 * -2 + 1);
  *(short *)(puVar1 + 1) = *(short *)(pointer_shapes + 1) + 1;
  *(short *)((int)puVar1 + 6) = *(short *)((int)pointer_shapes + 6) + 1;
  grabshape(puVar1,local_24 + -4,local_28);
  pppuVar2 = (undefined4 ***)local_28;
  drawshape_remap(pointer_shapes,local_24 + -4,local_28);
  uVar8 = event_queue_reset();
  do {
    local_2c = (undefined4 *)0x0;
    do {
      uVar9 = event_queue_pop((int)uVar8,(int)(uVar8 >> 0x20),pppuVar2);
      uVar8 = CONCAT44((int)((ulonglong)uVar9 >> 0x20),local_2c);
      if ((int)uVar9 == 0) break;
      pppuVar2 = &local_28;
      uVar8 = (*ui_poll_callback)();
      local_2c = (undefined4 *)uVar8;
    } while ((uVar8 & 6) == 0);
    local_2c = (undefined4 *)uVar8;
    uVar8 = CONCAT44((int)(uVar8 >> 0x20),local_28);
    if (local_2c != (undefined4 *)0x0) {
      drawshape(puVar1,iStack_1c + -4,local_20);
      freemem(puVar1);
      return (ulonglong)unaff_EDX << 0x20;
    }
    if ((local_24 != iStack_1c) || (local_28 != local_20)) {
      drawshape(puVar1,iStack_1c + -4,local_20);
      grabshape(puVar1,local_24 + -4,local_28);
      drawshape_remap(pointer_shapes,local_24 + -4,local_28);
      uVar8 = CONCAT44(extraout_EDX,local_28);
      iStack_1c = local_24;
      local_20 = local_28;
    }
  } while( true );
}


// ================================================================================================
// settings_menu @ 0x7add3 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

longlong __watcall settings_menu(int param_1,uint unaff_EDX)

{
  ulonglong uVar1;
  undefined4 ***pppuVar2;
  undefined4 *puVar3;
  int iVar4;
  uint uVar5;
  undefined4 extraout_EDX;
  uint uVar6;
  undefined4 ****ppppuVar7;
  undefined4 ****ppppuVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  byte bVar11;
  ulonglong uVar12;
  undefined8 uVar13;
  int local_34;
  undefined4 *local_30;
  undefined4 ***local_2c;
  int local_28;
  undefined4 ***local_24;
  int local_20;
  uint uStack_1c;
  
  bVar11 = 0;
  __CHK(0x44);
  if (param_1 != 0) {
    setpalette(0xf7,4,&unk_d16a0);
  }
  getmouse(&local_30,&local_20,&local_24);
  local_28 = local_20;
  local_2c = local_24;
  uStack_1c = (option_flags << 0x19) >> 0x1f;
  setdefaultscreen();
  puVar3 = (undefined4 *)
           allocmem(aPointer_c32f5,
                    (((int)pointer_shapes[1] >> 0x10) + 1) *
                    ((*(int *)((int)pointer_shapes + 2) >> 0x10) + 1) + 0x11,0x20);
  puVar9 = puVar3 + (uint)bVar11 * -2 + 1;
  ppppuVar7 = pointer_shapes + (uint)bVar11 * -2 + 1;
  *puVar3 = *pointer_shapes;
  puVar10 = puVar9 + (uint)bVar11 * -2 + 1;
  ppppuVar8 = ppppuVar7 + (uint)bVar11 * -2 + 1;
  *puVar9 = *ppppuVar7;
  *puVar10 = *ppppuVar8;
  puVar10[(uint)bVar11 * -2 + 1] = ppppuVar8[(uint)bVar11 * -2 + 1];
  *(undefined *)(puVar10 + (uint)bVar11 * -2 + 1 + (uint)bVar11 * -2 + 1) =
       *(undefined *)(ppppuVar8 + (uint)bVar11 * -2 + 1 + (uint)bVar11 * -2 + 1);
  *(short *)(puVar3 + 1) = *(short *)(pointer_shapes + 1) + 1;
  *(short *)((int)puVar3 + 6) = *(short *)((int)pointer_shapes + 6) + 1;
  grabshape(puVar3,local_28 + -4,local_2c);
  ppppuVar7 = (undefined4 ****)local_2c;
  drawshape_remap(pointer_shapes,local_28 + -4,local_2c);
  uVar12 = event_queue_reset();
LAB_0007aec6:
  local_30 = (undefined4 *)0x0;
  do {
    uVar13 = event_queue_pop((int)uVar12,(int)(uVar12 >> 0x20),ppppuVar7);
    uVar1 = CONCAT44((int)((ulonglong)uVar13 >> 0x20),local_30);
    if ((int)uVar13 == 0) break;
    ppppuVar7 = &local_2c;
    uVar12 = (*ui_poll_callback)();
    local_30 = (undefined4 *)uVar12;
    uVar1 = uVar12;
  } while ((uVar12 & 6) == 0);
  pppuVar2 = local_24;
  local_30 = (undefined4 *)uVar1;
  uVar12 = CONCAT44((int)(uVar1 >> 0x20),local_2c);
  if ((uVar1 & 6) == 0) goto code_r0x0007aef2;
  iVar4 = local_20 + -4;
  if ((uVar1 & 2) == 0) {
    if ((uVar1 & 4) == 0) {
      drawshape(puVar3,iVar4,local_24);
      grabshape(puVar3,local_28 + -4,local_2c);
      iVar4 = local_28 + -4;
      ppppuVar7 = pointer_shapes;
      goto LAB_0007af46;
    }
    drawshape(puVar3,iVar4,local_24);
LAB_0007a1f5:
    freemem(puVar3);
    return (ulonglong)unaff_EDX << 0x20;
  }
  drawshape(puVar3,iVar4,local_24);
  iVar4 = sub_7a9c8(local_28,local_2c,&local_34);
  if (iVar4 != 0) {
    if (local_34 < 0x12) {
      uVar5 = local_34 / 2;
      if (local_34 % 2 == 0) {
        if ((sound_enabled != '\0') || (local_34 != 0x10)) {
          local_34 = local_34 / 2;
          uVar5 = 1 << ((byte)local_34 & 0x1f);
          dword_ed360 = dword_ed360 | uVar5;
        }
      }
      else if ((sound_enabled != '\0') || (local_34 != 0x11)) {
        local_34 = local_34 / 2;
        uVar5 = ~(1 << ((byte)local_34 & 0x1f));
        dword_ed360 = dword_ed360 & uVar5;
      }
    }
    else {
      if (local_34 < 0x15) {
        uVar5 = dword_ed360 & 0xf1ff;
      }
      else {
        if (0x18 < local_34) {
          if (local_34 == 0x19) {
            drawshape_trans(dword_ed774,0x3f,0x148);
            option_flags = option_flags & 0xfffffffe;
            uVar5 = option_flags;
            option_flags._0_1_ = (byte)option_flags | (dword_ed360 & 1) != 0;
            option_flags._1_3_ = SUB43(uVar5,1);
            option_flags = CONCAT31(option_flags._1_3_,(byte)option_flags) & 0xfffffffd;
            uVar5 = option_flags;
            option_flags._0_1_ = (byte)option_flags | ((dword_ed360 & 2) != 0) * '\x02';
            option_flags._1_3_ = SUB43(uVar5,1);
            option_flags = CONCAT31(option_flags._1_3_,(byte)option_flags) & 0xfffffffb;
            uVar5 = option_flags;
            option_flags._0_1_ = (byte)option_flags | ((dword_ed360 & 4) != 0) << 2;
            uVar6 = (dword_ed360 & 0xff) << 8;
            option_flags._1_3_ = SUB43(uVar5,1);
            option_flags = CONCAT31(option_flags._1_3_,(byte)option_flags) & 0xfffffff7;
            uVar5 = option_flags;
            option_flags._0_1_ = (byte)option_flags | ((uVar6 & 0x800) != 0) << 3;
            option_flags._1_3_ = SUB43(uVar5,1);
            option_flags = CONCAT31(option_flags._1_3_,(byte)option_flags) & 0xffffffef;
            uVar5 = option_flags;
            option_flags._0_1_ = (byte)option_flags | ((dword_ed360 & 0x10) != 0) << 4;
            option_flags._1_3_ = SUB43(uVar5,1);
            option_flags = CONCAT31(option_flags._1_3_,(byte)option_flags) & 0xffffffdf;
            uVar5 = option_flags;
            option_flags = option_flags | (uint)((uVar6 & 0x2000) != 0) << 5;
            if (dword_c541f != 0x10) {
              option_flags._1_3_ = SUB43(uVar5,1);
              option_flags = CONCAT31(option_flags._1_3_,(byte)option_flags) & 0xffffffbf;
              uVar5 = option_flags;
              option_flags._0_1_ = (byte)option_flags | ((dword_ed360 & 0x40) != 0) << 6;
              option_flags._1_3_ = SUB43(uVar5,1);
              option_flags = CONCAT31(option_flags._1_3_,(byte)option_flags) & 0xffffff7f;
              option_flags = option_flags | (uint)((dword_ed360 & 0x80) != 0) << 7;
            }
            if ((dword_c541f & 0x22) != 0) {
              option_flags = option_flags & 0xfffffeff;
              option_flags = option_flags | (uint)((dword_ed360 & 0x100) != 0) << 8;
            }
            uVar6 = dword_ed360 & 0xe00;
            uVar5 = option_flags & 0xfffff3ff;
            if (uVar6 < 0x400) {
              if (uVar6 == 0x200) {
                uVar5 = uVar5 | 0x800;
                goto LAB_0007b1b9;
              }
            }
            else {
              if (uVar6 < 0x401) {
                uVar5 = uVar5 | 0x400;
              }
              else if (uVar6 != 0x800) goto LAB_0007b1be;
LAB_0007b1b9:
              option_flags = uVar5;
            }
LAB_0007b1be:
            uVar5 = dword_ed360 & 0xf000;
            uVar6 = option_flags & 0xffff8fff;
            if (uVar5 < 0x2000) {
              if (uVar5 == 0x1000) {
                option_flags = uVar6 | 0x1000;
              }
            }
            else if (uVar5 < 0x2001) {
              option_flags = uVar6 | 0x3000;
            }
            else if (0x3fff < uVar5) {
              if (uVar5 < 0x4001) {
                option_flags = uVar6 | 0x5000;
              }
              else if (uVar5 == 0x8000) {
                option_flags = option_flags | 0x7000;
              }
            }
            if ((option_flags & 0x40) == 0) {
              if (((sound_enabled != '\0') && (dword_c721d != 0)) &&
                 (iVar4 = sound_channel_status(ram0x000d242c >> 0x18,3), iVar4 == 0)) {
                sound_fade(dword_d2431,3,100);
              }
              music_disable();
            }
            else {
              if (((sound_enabled != '\0') && (dword_c721d != 0)) &&
                 ((uStack_1c == 0 &&
                  (iVar4 = sound_channel_status(ram0x000d242c >> 0x18,3), iVar4 != 0)))) {
                playsample(dword_c721d,dword_d2431,3,0x7f);
              }
              music_enable();
            }
            if ((option_flags & 0x80) == 0) {
              sfx_disable();
            }
            else {
              sfx_enable();
            }
            sub_8b92f();
          }
          else {
            drawshape_trans(dword_dd64c,0x89,0x148);
          }
          goto LAB_0007a1f5;
        }
        uVar5 = dword_ed360 & 0xfff;
      }
      uVar5 = uVar5 | 1 << ((byte)(local_34 + -9) & 0x1f);
      dword_ed360 = uVar5;
      local_34 = local_34 + -9;
    }
    sub_7aaaa(uVar5);
  }
  ppppuVar7 = (undefined4 ****)local_2c;
  sub_96440(puVar3,local_28 + -4,local_2c);
  iVar4 = local_28 + -4;
  goto LAB_0007af46;
code_r0x0007aef2:
  if ((local_28 == local_20) && (local_2c == local_24)) goto LAB_0007aec6;
  drawshape(puVar3,local_20 + -4,local_24);
  grabshape(puVar3,local_28 + -4,local_2c);
  iVar4 = local_28 + -4;
  ppppuVar7 = (undefined4 ****)pppuVar2;
LAB_0007af46:
  drawshape_remap(pointer_shapes,iVar4,local_2c);
  uVar12 = CONCAT44(extraout_EDX,local_2c);
  local_20 = local_28;
  local_24 = local_2c;
  goto LAB_0007aec6;
}


// ================================================================================================
// sub_7b39c @ 0x7b39c [__watcall]
// ================================================================================================

void __watcall sub_7b39c(void)

{
  __CHK(4);
  return;
}


// ================================================================================================
// game_settings_screen @ 0x7b3a7 [__watcall]
// ================================================================================================

longlong __watcall game_settings_screen(undefined4 param_1,uint unaff_EDX)

{
  short sVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  byte bVar7;
  
  bVar7 = 0;
  __CHK(0x28);
  setdefaultscreen();
  settings_toggles();
  puVar2 = (undefined4 *)allocmem(&aBKGD_c3300,0xe935,0x20);
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
  *(undefined2 *)(puVar2 + 1) = 0xd6;
  *(undefined2 *)((int)puVar2 + 6) = 0x101;
  grabshape(puVar2,10,0x13);
  game_settings_dialog();
  sound_settings_dialog();
  if (dword_c53fb == 2) {
    sub_7b846();
  }
  else {
    game_settings_menu();
  }
  drawshape(puVar2,10,0x13);
  if (((byte)option_flags & 4) == 0) {
    word_cbc58 = 0;
    word_cbc56 = 0;
    word_cbc6c = 0;
    word_cbc6a = 0;
    for (sVar1 = 0; sVar1 < 0xc; sVar1 = sVar1 + 1) {
      (&unk_df861)[sVar1 * 0x80] = (&unk_df861)[sVar1 * 0x80] & 0xf7;
    }
    byte_df658 = byte_df658 & 0xfd;
    byte_df758 = byte_df758 & 0xfd;
    for (sVar1 = 0; sVar1 < 0x1c; sVar1 = sVar1 + 1) {
      (&unk_df75a)[sVar1] = 0x1000;
      (&unk_df65a)[sVar1] = 0x1000;
    }
  }
  if (((byte)option_flags & 0x40) == 0) {
    music_disable();
  }
  else {
    music_enable();
  }
  if (((byte)option_flags & 0x80) == 0) {
    sfx_disable();
  }
  else {
    sfx_enable();
  }
  freemem(puVar2);
  freemem(dword_d20a8);
  dword_d20a8 = 0;
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// game_settings_dialog @ 0x7b4ec [__watcall]
// ================================================================================================

void __watcall game_settings_dialog(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined *puVar3;
  char *pcVar4;
  undefined auStack_30 [32];
  
  __CHK(0x40);
  puVar3 = install_path;
  if (dword_c53fb == 2) {
    pcVar4 = aSetting7;
    if (byte_ed943 != '\x01') {
      puVar3 = (undefined *)0x0;
    }
  }
  else {
    pcVar4 = aSetting4;
    if (byte_ed940 != '\x01') {
      puVar3 = (undefined *)0x0;
    }
  }
  make_path(auStack_30,puVar3,pcVar4,0);
  uVar1 = loadshapes(auStack_30,0);
  uVar2 = locateshape(uVar1,&aDbox_c3317,10,0x13);
  drawshape2_remap(uVar2);
  freemem(uVar1);
  settextpos(0xf8,0xff);
  if (dword_c541f == 0x10) {
    printstr_at(aMusic_c331c,0x60,0xaa);
    printstr_at(aSound_c3322,0x60,0xc0);
  }
  if (sound_enabled == '\0') {
    printstr_at(aDigitizedSpeech_c3328,0x60,0xd6);
  }
  setdefaultscreen();
  sub_8050f(10,0x13,4,dword_c53fb,0xfa);
  return;
}


// ================================================================================================
// sound_settings_dialog @ 0x7b604 [__watcall]
// ================================================================================================

void __watcall
sound_settings_dialog
          (undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  __CHK(0x1c);
  if ((dword_c541f & 0x10) == 0) {
    uVar1 = ((option_flags << 0x19) >> 0x1f) << 6;
  }
  else {
    uVar1 = 0;
  }
  if ((dword_c541f & 0x10) == 0) {
    uVar2 = ((option_flags << 0x18) >> 0x1f) << 7;
  }
  else {
    uVar2 = 0;
  }
  if ((dword_c541f & 0x22) == 0) {
    uVar3 = 0;
  }
  else {
    uVar3 = ((option_flags << 0x17) >> 0x1f) << 8;
  }
  dword_ed360 = option_flags & 1 | ((int)(option_flags << 0x1e) >> 0x1f) * -2 |
                ((option_flags << 0x1d) >> 0x1f) << 2 | ((option_flags << 0x1c) >> 0x1f) << 3 |
                ((option_flags << 0x1b) >> 0x1f) << 4 | ((option_flags << 0x1a) >> 0x1f) << 5 |
                uVar1 | uVar2 | uVar3;
  sub_7b7be();
  settextpos(0xf8,0xff,unaff_EDX,unaff_ECX,unaff_EBX);
  if (dword_c541f == 0x10) {
    printstr_at(aMusic_c331c,0x60,0xaa);
    printstr_at(aSound_c3322,0x60,0xc0);
  }
  if (sound_enabled == '\0') {
    printstr_at(aDigitizedSpeech_c3328,0x60,0xd6);
  }
  setdefaultscreen();
  return;
}


// ================================================================================================
// sub_7b734 @ 0x7b734 [__watcall]
// ================================================================================================

undefined4 __watcall sub_7b734(int param_1,int unaff_EDX,int *unaff_EBX)

{
  int iVar1;
  
  __CHK(0xc);
  iVar1 = 0;
  while ((((param_1 + -6 < (int)(&unk_d16ac)[iVar1 * 4] ||
           ((int)(&unk_d16b4)[iVar1 * 4] < param_1 + -6)) ||
          (unaff_EDX + -0x13 < (int)(&unk_d16b0)[iVar1 * 4])) ||
         ((int)(&unk_d16b8)[iVar1 * 4] < unaff_EDX + -0x13))) {
    iVar1 = iVar1 + 1;
    if (0x13 < iVar1) {
      return 0;
    }
  }
  if (iVar1 == 10) {
    return 0;
  }
  if (iVar1 == 0xb) {
    return 0;
  }
  if (((0xb < iVar1) && (iVar1 < 0x10)) && (dword_c541f == 0x10)) {
    return 0;
  }
  if (((iVar1 == 0x10) || (iVar1 == 0x11)) && (sound_enabled == '\0')) {
    return 0;
  }
  *unaff_EBX = iVar1;
  return 1;
}


// ================================================================================================
// sub_7b7be @ 0x7b7be [__watcall]
// ================================================================================================

void __watcall sub_7b7be(void)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  undefined4 uVar4;
  int iStack_18;
  
  __CHK(0x28);
  piVar3 = &unk_d16ac;
  iStack_18 = 0;
  do {
    if (iStack_18 == 5) {
      iStack_18 = 6;
      piVar3 = piVar3 + 8;
    }
    if ((dword_ed360 & 1 << ((byte)iStack_18 & 0x1f)) == 0) {
      iVar1 = piVar3[1];
      iVar2 = *piVar3;
      uVar4 = dword_ed780;
    }
    else {
      iVar1 = piVar3[1];
      iVar2 = *piVar3;
      uVar4 = dword_ed788;
    }
    drawshape(uVar4,iVar2 + 10,iVar1 + 0x13);
    iStack_18 = iStack_18 + 1;
    piVar3 = piVar3 + 8;
  } while (iStack_18 < 9);
  return;
}


// ================================================================================================
// sub_7b846 @ 0x7b846 [__watcall]
// ================================================================================================

longlong __watcall sub_7b846(undefined4 param_1,uint unaff_EDX)

{
  undefined4 *puVar1;
  undefined4 extraout_EDX;
  undefined4 ***pppuVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  byte bVar7;
  ulonglong uVar8;
  undefined8 uVar9;
  undefined4 *local_2c;
  undefined4 **local_28;
  int local_24;
  undefined4 **local_20;
  int iStack_1c;
  
  bVar7 = 0;
  __CHK(0x3c);
  setpalette(0xf7,4,&unk_d16a0);
  getmouse(&local_2c,&iStack_1c,&local_20);
  local_24 = iStack_1c;
  local_28 = local_20;
  setdefaultscreen();
  puVar1 = (undefined4 *)
           allocmem(aPointer_c3339,
                    (((int)pointer_shapes[1] >> 0x10) + 1) *
                    ((*(int *)((int)pointer_shapes + 2) >> 0x10) + 1) + 0x11,0x20);
  puVar5 = puVar1 + (uint)bVar7 * -2 + 1;
  puVar3 = pointer_shapes + (uint)bVar7 * -2 + 1;
  *puVar1 = *pointer_shapes;
  puVar6 = puVar5 + (uint)bVar7 * -2 + 1;
  puVar4 = puVar3 + (uint)bVar7 * -2 + 1;
  *puVar5 = *puVar3;
  *puVar6 = *puVar4;
  puVar6[(uint)bVar7 * -2 + 1] = puVar4[(uint)bVar7 * -2 + 1];
  *(undefined *)(puVar6 + (uint)bVar7 * -2 + 1 + (uint)bVar7 * -2 + 1) =
       *(undefined *)(puVar4 + (uint)bVar7 * -2 + 1 + (uint)bVar7 * -2 + 1);
  *(short *)(puVar1 + 1) = *(short *)(pointer_shapes + 1) + 1;
  *(short *)((int)puVar1 + 6) = *(short *)((int)pointer_shapes + 6) + 1;
  grabshape(puVar1,local_24 + -4,local_28);
  pppuVar2 = (undefined4 ***)local_28;
  drawshape_remap(pointer_shapes,local_24 + -4,local_28);
  uVar8 = event_queue_reset();
  do {
    local_2c = (undefined4 *)0x0;
    do {
      uVar9 = event_queue_pop((int)uVar8,(int)(uVar8 >> 0x20),pppuVar2);
      uVar8 = CONCAT44((int)((ulonglong)uVar9 >> 0x20),local_2c);
      if ((int)uVar9 == 0) break;
      pppuVar2 = &local_28;
      uVar8 = (*ui_poll_callback)();
      local_2c = (undefined4 *)uVar8;
    } while ((uVar8 & 6) == 0);
    local_2c = (undefined4 *)uVar8;
    uVar8 = CONCAT44((int)(uVar8 >> 0x20),local_28);
    if (local_2c != (undefined4 *)0x0) {
      drawshape(puVar1,iStack_1c + -4,local_20);
      freemem(puVar1);
      return (ulonglong)unaff_EDX << 0x20;
    }
    if ((local_24 != iStack_1c) || (local_28 != local_20)) {
      drawshape(puVar1,iStack_1c + -4,local_20);
      grabshape(puVar1,local_24 + -4,local_28);
      drawshape_remap(pointer_shapes,local_24 + -4,local_28);
      uVar8 = CONCAT44(extraout_EDX,local_28);
      iStack_1c = local_24;
      local_20 = local_28;
    }
  } while( true );
}


// ================================================================================================
// game_settings_menu @ 0x7b9e8 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

longlong __watcall game_settings_menu(undefined4 param_1,uint unaff_EDX)

{
  ulonglong uVar1;
  undefined4 *puVar2;
  int iVar3;
  uint uVar4;
  undefined4 extraout_EDX;
  uint extraout_EDX_00;
  undefined4 ****ppppuVar5;
  undefined4 ****ppppuVar6;
  undefined4 *puVar7;
  byte bVar8;
  ulonglong uVar9;
  undefined8 uVar10;
  undefined4 *puVar11;
  int local_34;
  undefined4 *local_30;
  undefined4 ***local_2c;
  int local_28;
  undefined4 ***local_24;
  int local_20;
  uint uStack_1c;
  
  bVar8 = 0;
  __CHK(0x44);
  setpalette(0xf7,4,&unk_d16a0);
  getmouse(&local_30,&local_20,&local_24);
  local_28 = local_20;
  local_2c = local_24;
  setdefaultscreen();
  uStack_1c = (option_flags << 0x19) >> 0x1f;
  puVar2 = (undefined4 *)
           allocmem(aPointer_c3339,
                    (((int)pointer_shapes[1] >> 0x10) + 1) *
                    ((*(int *)((int)pointer_shapes + 2) >> 0x10) + 1) + 0x11,0x20);
  puVar11 = puVar2 + (uint)bVar8 * -2 + 1;
  ppppuVar5 = pointer_shapes + (uint)bVar8 * -2 + 1;
  *puVar2 = *pointer_shapes;
  puVar7 = puVar11 + (uint)bVar8 * -2 + 1;
  ppppuVar6 = ppppuVar5 + (uint)bVar8 * -2 + 1;
  *puVar11 = *ppppuVar5;
  *puVar7 = *ppppuVar6;
  puVar7[(uint)bVar8 * -2 + 1] = ppppuVar6[(uint)bVar8 * -2 + 1];
  *(undefined *)(puVar7 + (uint)bVar8 * -2 + 1 + (uint)bVar8 * -2 + 1) =
       *(undefined *)(ppppuVar6 + (uint)bVar8 * -2 + 1 + (uint)bVar8 * -2 + 1);
  *(short *)(puVar2 + 1) = *(short *)(pointer_shapes + 1) + 1;
  *(short *)((int)puVar2 + 6) = *(short *)((int)pointer_shapes + 6) + 1;
  grabshape(puVar2,local_28 + -4,local_2c);
  ppppuVar5 = (undefined4 ****)local_2c;
  drawshape_remap(pointer_shapes,local_28 + -4,local_2c);
  uVar9 = event_queue_reset();
LAB_0007bad7:
  local_30 = (undefined4 *)0x0;
  do {
    uVar10 = event_queue_pop((int)uVar9,(int)(uVar9 >> 0x20),ppppuVar5);
    uVar1 = CONCAT44((int)((ulonglong)uVar10 >> 0x20),local_30);
    if ((int)uVar10 == 0) break;
    ppppuVar5 = &local_2c;
    uVar9 = (*ui_poll_callback)();
    local_30 = (undefined4 *)uVar9;
    uVar1 = uVar9;
  } while ((uVar9 & 6) == 0);
  local_30 = (undefined4 *)uVar1;
  uVar9 = CONCAT44((int)(uVar1 >> 0x20),local_2c);
  if ((uVar1 & 6) == 0) goto code_r0x0007bb03;
  iVar3 = local_20 + -4;
  if ((uVar1 & 2) == 0) {
    puVar11 = puVar2;
    ppppuVar5 = (undefined4 ****)local_24;
    if ((uVar1 & 4) == 0) goto LAB_0007bb23;
    goto LAB_0007be88;
  }
  drawshape(puVar2,iVar3,local_24);
  iVar3 = sub_7b734(local_28,local_2c,&local_34);
  if (iVar3 == 0) goto LAB_0007bb2d;
  if (0x11 < local_34) {
    if (local_34 == 0x12) {
      drawshape(dword_ed774,0x37,0xf8);
      option_flags = option_flags & 0xfffffffe;
      uVar4 = option_flags;
      option_flags._0_1_ = (byte)option_flags | (dword_ed360 & 1) != 0;
      option_flags._1_3_ = SUB43(uVar4,1);
      option_flags = CONCAT31(option_flags._1_3_,(byte)option_flags) & 0xfffffffd;
      uVar4 = option_flags;
      option_flags._0_1_ = (byte)option_flags | ((dword_ed360 & 2) != 0) * '\x02';
      option_flags._1_3_ = SUB43(uVar4,1);
      option_flags = CONCAT31(option_flags._1_3_,(byte)option_flags) & 0xfffffffb;
      uVar4 = option_flags;
      option_flags._0_1_ = (byte)option_flags | ((dword_ed360 & 4) != 0) << 2;
      option_flags._1_3_ = SUB43(uVar4,1);
      option_flags = CONCAT31(option_flags._1_3_,(byte)option_flags) & 0xfffffff7;
      uVar4 = option_flags;
      option_flags._0_1_ = (byte)option_flags | ((dword_ed360 & 8) != 0) << 3;
      option_flags._1_3_ = SUB43(uVar4,1);
      option_flags = CONCAT31(option_flags._1_3_,(byte)option_flags) & 0xffffffef;
      uVar4 = option_flags;
      option_flags._0_1_ = (byte)option_flags | ((dword_ed360 & 0x10) != 0) << 4;
      option_flags._1_3_ = SUB43(uVar4,1);
      option_flags = CONCAT31(option_flags._1_3_,(byte)option_flags) & 0xffffffdf;
      uVar4 = option_flags;
      option_flags = option_flags | (uint)((dword_ed360 & 0x20) != 0) << 5;
      if (dword_c541f != 0x10) {
        option_flags._1_3_ = SUB43(uVar4,1);
        option_flags = CONCAT31(option_flags._1_3_,(byte)option_flags) & 0xffffffbf;
        uVar4 = option_flags;
        option_flags._0_1_ = (byte)option_flags | ((dword_ed360 & 0x40) != 0) << 6;
        option_flags._1_3_ = SUB43(uVar4,1);
        option_flags = CONCAT31(option_flags._1_3_,(byte)option_flags) & 0xffffff7f;
        option_flags = option_flags | (uint)((dword_ed360 & 0x80) != 0) << 7;
      }
      uVar4 = (uint)((dword_ed360 & 0x80) != 0);
      if (((option_flags & 0x80) != 0) && (uVar4 == 0)) {
        sound_pause_all();
        uVar4 = extraout_EDX_00;
      }
      if (((option_flags & 0x80) == 0) && (uVar4 != 0)) {
        option_flags = option_flags & 0xffffff7f;
        option_flags = option_flags | (uVar4 & 1) << 7;
        sound_resume_all();
      }
      else {
        option_flags = option_flags & 0xffffff7f;
        option_flags = option_flags | (uVar4 & 1) << 7;
      }
      if (sound_enabled != '\0') {
        option_flags = option_flags & 0xfffffeff;
        option_flags = option_flags | (uint)((dword_ed360 & 0x100) != 0) << 8;
      }
      if ((option_flags & 0x40) == 0) {
        if (((sound_enabled != '\0') && (dword_c721d != 0)) &&
           (iVar3 = sound_channel_status(ram0x000d242c >> 0x18,3), iVar3 == 0)) {
          sound_fade(dword_d2431,3,100);
        }
        music_disable();
      }
      else {
        if (((sound_enabled != '\0') && (dword_c721d != 0)) &&
           ((uStack_1c == 0 && (iVar3 = sound_channel_status(ram0x000d242c >> 0x18,3), iVar3 != 0)))
           ) {
          playsample(dword_c721d,dword_d2431,3,0x7f);
        }
        music_enable();
      }
      if ((option_flags & 0x80) == 0) {
        sfx_disable();
      }
      else {
        sfx_enable();
      }
      sub_8b92f();
      goto LAB_0007b4e5;
    }
    iVar3 = 0x81;
    puVar11 = dword_dd64c;
    ppppuVar5 = (undefined4 ****)0xf8;
LAB_0007be88:
    drawshape(puVar11,iVar3,ppppuVar5);
LAB_0007b4e5:
    freemem(puVar2);
    return (ulonglong)unaff_EDX << 0x20;
  }
  uVar4 = local_34 / 2;
  if (local_34 % 2 == 0) {
    if ((sound_enabled != '\0') || (local_34 != 0x10)) {
      local_34 = local_34 / 2;
      uVar4 = 1 << ((byte)local_34 & 0x1f);
      dword_ed360 = dword_ed360 | uVar4;
    }
  }
  else if ((sound_enabled != '\0') || (local_34 != 0x11)) {
    local_34 = local_34 / 2;
    uVar4 = ~(1 << ((byte)local_34 & 0x1f));
    dword_ed360 = dword_ed360 & uVar4;
  }
  sub_7b7be(uVar4);
  goto LAB_0007bb2d;
code_r0x0007bb03:
  if ((local_28 == local_20) && (local_2c == local_24)) goto LAB_0007bad7;
LAB_0007bb23:
  drawshape(puVar2,local_20 + -4,local_24);
LAB_0007bb2d:
  grabshape(puVar2,local_28 + -4,local_2c);
  ppppuVar5 = pointer_shapes;
  drawshape_remap(pointer_shapes,local_28 + -4,local_2c);
  uVar9 = CONCAT44(extraout_EDX,local_2c);
  local_20 = local_28;
  local_24 = local_2c;
  goto LAB_0007bad7;
}


// ================================================================================================
// sub_7bebb @ 0x7bebb [__watcall]
// ================================================================================================

longlong __watcall sub_7bebb(undefined4 param_1,uint unaff_EDX)

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
  puVar1 = (undefined4 *)allocmem(&aBKGD_c3344,0x10aa5,0x20);
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
  *(undefined2 *)(puVar1 + 1) = 0xd6;
  *(undefined2 *)((int)puVar1 + 6) = 0x129;
  grabshape(puVar1,10,0x13);
  setdefaultscreen();
  sub_7c1ac();
  sound_toggle_dialog();
  sound_settings_menu();
  drawshape(puVar1,10,0x13);
  freemem(puVar1);
  freemem(dword_d20a8);
  dword_d20a8 = 0;
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// sound_toggle_dialog @ 0x7bf56 [__watcall]
// ================================================================================================

/* WARNING: Removing unreachable block (ram,0x0007c035) */

void __watcall
sound_toggle_dialog(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,
                   undefined4 unaff_ECX)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  __CHK(0x1c);
  if ((dword_c541f & 0x10) == 0) {
    uVar1 = ((option_flags << 0x19) >> 0x1f) << 6;
  }
  else {
    uVar1 = 0;
  }
  if ((dword_c541f & 0x10) == 0) {
    uVar2 = ((option_flags << 0x18) >> 0x1f) << 7;
  }
  else {
    uVar2 = 0;
  }
  if ((dword_c541f & 0x22) == 0) {
    uVar3 = 0;
  }
  else {
    uVar3 = ((option_flags << 0x17) >> 0x1f) << 8;
  }
  dword_ed360 = option_flags & 1 | ((int)(option_flags << 0x1e) >> 0x1f) * -2 |
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
  sub_7c0b9();
  settextpos(0xf8,0xff,unaff_EDX,unaff_ECX,unaff_EBX);
  if (sound_enabled == '\0') {
    printstr_at(aDigitizedSpeech_c3349,0x60,0xd6);
  }
  if (dword_c541f == 0x10) {
    printstr_at(aMusic_c335a,0x60,0xaa);
    printstr_at(aSound_c3360,0x60,0xc0);
  }
  return;
}


// ================================================================================================
// sub_7c0b9 @ 0x7c0b9 [__watcall]
// ================================================================================================

void __watcall sub_7c0b9(void)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int *piVar5;
  undefined4 uVar6;
  int iStack_1c;
  
  __CHK(0x2c);
  piVar4 = &unk_d17ec;
  iStack_1c = 0;
  do {
    piVar5 = piVar4;
    if (iStack_1c == 5) {
      iStack_1c = 6;
      piVar5 = piVar4 + 8;
    }
    if ((dword_ed360 & 1 << ((byte)iStack_1c & 0x1f)) == 0) {
      iVar2 = piVar5[1];
      iVar3 = *piVar5;
      uVar6 = dword_ed780;
    }
    else {
      iVar2 = piVar5[1];
      iVar3 = *piVar5;
      uVar6 = dword_ed788;
    }
    drawshape(uVar6,iVar3 + 10,iVar2 + 0x13);
    iStack_1c = iStack_1c + 1;
    piVar4 = piVar5 + 8;
  } while (iStack_1c < 9);
  uVar1 = dword_ed360 & 0xe00;
  if (uVar1 < 0x400) {
    if (uVar1 != 0x200) {
      return;
    }
    iVar2 = piVar5[9] + 0x13;
    iVar3 = *piVar4 + 10;
    uVar6 = dword_ed75c;
  }
  else if (uVar1 < 0x401) {
    iVar2 = piVar5[9] + 0x13;
    iVar3 = *piVar4 + 10;
    uVar6 = dword_ed764;
  }
  else {
    if (uVar1 != 0x800) {
      return;
    }
    iVar2 = piVar5[9] + 0x13;
    iVar3 = *piVar4 + 10;
    uVar6 = dword_ed760;
  }
  drawshape(uVar6,iVar3,iVar2);
  return;
}


// ================================================================================================
// sub_7c1ac @ 0x7c1ac [__watcall]
// ================================================================================================

void __watcall sub_7c1ac(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined *puVar3;
  undefined auStack_30 [32];
  
  __CHK(0x40);
  setdefaultscreen();
  puVar3 = install_path;
  if (byte_ed942 != '\x01') {
    puVar3 = (undefined *)0x0;
  }
  make_path(auStack_30,puVar3,aSetting6,0);
  uVar1 = loadshapes(auStack_30,0);
  uVar2 = locateshape(uVar1,&aDbox_c336f,10,0x13);
  drawshape2_remap(uVar2);
  freemem(uVar1);
  if (dword_c541f == 0x10) {
    printstr_at(aMusic_c335a,0x60,0xaa);
    printstr_at(aSound_c3360,0x60,0xc0);
  }
  if (sound_enabled == '\0') {
    printstr_at(aDigitizedSpeech_c3349,0x60,0xd6);
  }
  sub_8050f(10,0x13,6,dword_c53fb,0xfa);
  return;
}


// ================================================================================================
// sub_7c28d @ 0x7c28d [__watcall]
// ================================================================================================

undefined4 __watcall sub_7c28d(int param_1,int unaff_EDX,int *unaff_EBX)

{
  int iVar1;
  
  __CHK(0xc);
  iVar1 = 0;
  while ((((param_1 + -6 < (int)(&unk_d17ec)[iVar1 * 4] ||
           ((int)(&unk_d17f4)[iVar1 * 4] < param_1 + -6)) ||
          (unaff_EDX + -0x13 < (int)(&unk_d17f0)[iVar1 * 4])) ||
         ((int)(&unk_d17f8)[iVar1 * 4] < unaff_EDX + -0x13))) {
    iVar1 = iVar1 + 1;
    if (0x16 < iVar1) {
      return 0;
    }
  }
  if (iVar1 == 10) {
    return 0;
  }
  if (iVar1 == 0xb) {
    return 0;
  }
  if (((0xb < iVar1) && (iVar1 < 0x10)) && (dword_c541f == 0x10)) {
    return 0;
  }
  if (((iVar1 == 0x10) || (iVar1 == 0x11)) && (sound_enabled == '\0')) {
    return 0;
  }
  *unaff_EBX = iVar1;
  return 1;
}


// ================================================================================================
// sound_settings_menu @ 0x7c317 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

longlong __watcall sound_settings_menu(undefined4 param_1,uint unaff_EDX)

{
  ulonglong uVar1;
  undefined4 *puVar2;
  int iVar3;
  uint uVar4;
  undefined4 extraout_EDX;
  uint uVar5;
  undefined4 ****ppppuVar6;
  undefined4 ****ppppuVar7;
  int iVar8;
  undefined4 *puVar9;
  byte bVar10;
  ulonglong uVar11;
  undefined8 uVar12;
  undefined4 *puVar13;
  int local_30;
  undefined4 *local_2c;
  undefined4 ***local_28;
  int local_24;
  undefined4 ***local_20;
  int iStack_1c;
  
  bVar10 = 0;
  __CHK(0x40);
  setpalette(0xf7,4,&unk_d16a0);
  getmouse(&local_2c,&iStack_1c,&local_20);
  local_24 = iStack_1c;
  local_28 = local_20;
  setdefaultscreen();
  puVar2 = (undefined4 *)
           allocmem(aPointer_c3374,
                    (((int)pointer_shapes[1] >> 0x10) + 1) *
                    ((*(int *)((int)pointer_shapes + 2) >> 0x10) + 1) + 0x11,0x20);
  puVar13 = puVar2 + (uint)bVar10 * -2 + 1;
  ppppuVar6 = pointer_shapes + (uint)bVar10 * -2 + 1;
  *puVar2 = *pointer_shapes;
  puVar9 = puVar13 + (uint)bVar10 * -2 + 1;
  ppppuVar7 = ppppuVar6 + (uint)bVar10 * -2 + 1;
  *puVar13 = *ppppuVar6;
  *puVar9 = *ppppuVar7;
  puVar9[(uint)bVar10 * -2 + 1] = ppppuVar7[(uint)bVar10 * -2 + 1];
  *(undefined *)(puVar9 + (uint)bVar10 * -2 + 1 + (uint)bVar10 * -2 + 1) =
       *(undefined *)(ppppuVar7 + (uint)bVar10 * -2 + 1 + (uint)bVar10 * -2 + 1);
  *(short *)(puVar2 + 1) = *(short *)(pointer_shapes + 1) + 1;
  *(short *)((int)puVar2 + 6) = *(short *)((int)pointer_shapes + 6) + 1;
  grabshape(puVar2,local_24 + -4,local_28);
  ppppuVar6 = (undefined4 ****)local_28;
  drawshape_remap(pointer_shapes,local_24 + -4,local_28);
  iVar8 = option_flags << 0x19;
  uVar11 = event_queue_reset();
LAB_0007c403:
  local_2c = (undefined4 *)0x0;
  do {
    uVar12 = event_queue_pop((int)uVar11,(int)(uVar11 >> 0x20),ppppuVar6);
    uVar1 = CONCAT44((int)((ulonglong)uVar12 >> 0x20),local_2c);
    if ((int)uVar12 == 0) break;
    ppppuVar6 = &local_28;
    uVar11 = (*ui_poll_callback)();
    local_2c = (undefined4 *)uVar11;
    uVar1 = uVar11;
  } while ((uVar11 & 6) == 0);
  local_2c = (undefined4 *)uVar1;
  uVar11 = CONCAT44((int)(uVar1 >> 0x20),local_28);
  if ((uVar1 & 6) == 0) goto code_r0x0007c42f;
  iVar3 = iStack_1c + -4;
  if ((uVar1 & 2) == 0) {
    puVar13 = puVar2;
    ppppuVar6 = (undefined4 ****)local_20;
    if ((uVar1 & 4) == 0) {
      drawshape(puVar2,iVar3,local_20);
      ppppuVar6 = (undefined4 ****)local_28;
      grabshape(puVar2,local_24 + -4,local_28);
      iVar3 = local_24 + -4;
      goto LAB_0007c483;
    }
    goto LAB_0007c796;
  }
  drawshape(puVar2,iVar3,local_20);
  iVar3 = sub_7c28d(local_24,local_28,&local_30);
  if (iVar3 != 0) {
    if (local_30 < 0x12) {
      uVar4 = local_30 / 2;
      if (local_30 % 2 == 0) {
        if ((sound_enabled != '\0') || (local_30 != 0x10)) {
          local_30 = local_30 / 2;
          uVar4 = 1 << ((byte)local_30 & 0x1f);
          dword_ed360 = dword_ed360 | uVar4;
        }
      }
      else if ((sound_enabled != '\0') || (local_30 != 0x11)) {
        local_30 = local_30 / 2;
        uVar4 = ~(1 << ((byte)local_30 & 0x1f));
        dword_ed360 = dword_ed360 & uVar4;
      }
    }
    else {
      if (0x14 < local_30) {
        if (local_30 == 0x15) {
          drawshape(dword_ed774,0x37,0x120);
          option_flags = option_flags & 0xfffffffe;
          uVar4 = option_flags;
          option_flags._0_1_ = (byte)option_flags | (dword_ed360 & 1) != 0;
          option_flags._1_3_ = SUB43(uVar4,1);
          option_flags = CONCAT31(option_flags._1_3_,(byte)option_flags) & 0xfffffffd;
          uVar4 = option_flags;
          option_flags._0_1_ = (byte)option_flags | ((dword_ed360 & 2) != 0) * '\x02';
          option_flags._1_3_ = SUB43(uVar4,1);
          option_flags = CONCAT31(option_flags._1_3_,(byte)option_flags) & 0xfffffffb;
          uVar4 = option_flags;
          option_flags._0_1_ = (byte)option_flags | ((dword_ed360 & 4) != 0) << 2;
          option_flags._1_3_ = SUB43(uVar4,1);
          option_flags = CONCAT31(option_flags._1_3_,(byte)option_flags) & 0xfffffff7;
          uVar4 = option_flags;
          option_flags._0_1_ = (byte)option_flags | ((dword_ed360 & 8) != 0) << 3;
          option_flags._1_3_ = SUB43(uVar4,1);
          option_flags = CONCAT31(option_flags._1_3_,(byte)option_flags) & 0xffffffef;
          uVar4 = option_flags;
          option_flags._0_1_ = (byte)option_flags | ((dword_ed360 & 0x10) != 0) << 4;
          option_flags._1_3_ = SUB43(uVar4,1);
          option_flags = CONCAT31(option_flags._1_3_,(byte)option_flags) & 0xffffffdf;
          uVar4 = option_flags;
          option_flags = option_flags | (uint)((dword_ed360 & 0x20) != 0) << 5;
          if (dword_c541f != 0x10) {
            option_flags._1_3_ = SUB43(uVar4,1);
            option_flags = CONCAT31(option_flags._1_3_,(byte)option_flags) & 0xffffffbf;
            uVar4 = option_flags;
            option_flags._0_1_ = (byte)option_flags | ((dword_ed360 & 0x40) != 0) << 6;
            option_flags._1_3_ = SUB43(uVar4,1);
            option_flags = CONCAT31(option_flags._1_3_,(byte)option_flags) & 0xffffff7f;
            option_flags = option_flags | (uint)((dword_ed360 & 0x80) != 0) << 7;
          }
          if ((dword_c541f & 0x22) != 0) {
            option_flags = option_flags & 0xfffffeff;
            option_flags = option_flags | (uint)((dword_ed360 & 0x100) != 0) << 8;
          }
          uVar5 = dword_ed360 & 0xe00;
          uVar4 = option_flags & 0xfffff3ff;
          if (uVar5 < 0x400) {
            if (uVar5 == 0x200) {
              uVar4 = uVar4 | 0x800;
              goto LAB_0007c6cd;
            }
          }
          else {
            if (uVar5 < 0x401) {
              uVar4 = uVar4 | 0x400;
            }
            else if (uVar5 != 0x800) goto LAB_0007c6d2;
LAB_0007c6cd:
            option_flags = uVar4;
          }
LAB_0007c6d2:
          if ((option_flags & 0x40) == 0) {
            if (((sound_enabled != '\0') && (dword_c721d != 0)) &&
               (iVar8 = sound_channel_status(ram0x000d242c >> 0x18,3), iVar8 == 0)) {
              sound_fade(dword_d2431,3,0x28);
            }
            music_disable();
          }
          else {
            if (((sound_enabled != '\0') && (dword_c721d != 0)) &&
               ((-1 < iVar8 && (iVar8 = sound_channel_status(ram0x000d242c >> 0x18,3), iVar8 != 0)))
               ) {
              playsample(dword_c721d,dword_d2431,3,0x7f);
            }
            music_enable();
          }
          if ((option_flags & 0x80) == 0) {
            sfx_disable();
          }
          else {
            sfx_enable();
          }
          sub_8b92f();
          goto LAB_0007bf4f;
        }
        iVar3 = 0x81;
        puVar13 = dword_dd64c;
        ppppuVar6 = (undefined4 ****)0x120;
LAB_0007c796:
        drawshape(puVar13,iVar3,ppppuVar6);
LAB_0007bf4f:
        freemem(puVar2);
        return (ulonglong)unaff_EDX << 0x20;
      }
      local_30 = local_30 + -9;
      uVar4 = dword_ed360 & 0xf1ff | 1 << ((byte)local_30 & 0x1f);
      dword_ed360 = uVar4;
    }
    sub_7c0b9(uVar4);
  }
  sub_96440(puVar2,local_24 + -4,local_28);
  iVar3 = local_24 + -4;
  ppppuVar6 = pointer_shapes;
  goto LAB_0007c483;
code_r0x0007c42f:
  if ((local_24 == iStack_1c) && (local_28 == local_20)) goto LAB_0007c403;
  drawshape(puVar2,iStack_1c + -4,local_20);
  grabshape(puVar2,local_24 + -4,local_28);
  iVar3 = local_24 + -4;
  ppppuVar6 = (undefined4 ****)local_28;
LAB_0007c483:
  drawshape_remap(pointer_shapes,iVar3,local_28);
  uVar11 = CONCAT44(extraout_EDX,local_28);
  iStack_1c = local_24;
  local_20 = local_28;
  goto LAB_0007c403;
}


// ================================================================================================
// sub_7c852 @ 0x7c852 [__watcall]
// ================================================================================================

void __watcall sub_7c852(int *param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  __CHK(0x30);
  if (dword_d19ec == 0) {
    uVar2 = 0xfa;
    uVar1 = 0xf8;
  }
  else {
    uVar2 = 0x40;
    uVar1 = 0x42;
  }
  sub_b4fac(*param_1 + 10,param_1[3] + 0x12,*param_1 + 10,param_1[1] + 0x13,uVar1);
  sub_b4fac(*param_1 + 10,param_1[1] + 0x13,param_1[2] + 9,param_1[1] + 0x13,uVar1);
  sub_b4fac(param_1[2] + 10,param_1[1] + 0x14,param_1[2] + 10,param_1[3] + 0x13,uVar2);
  sub_b4fac(param_1[2] + 10,param_1[3] + 0x13,*param_1 + 0xb,param_1[3] + 0x13,uVar2);
  return;
}


// ================================================================================================
// sub_7c901 @ 0x7c901 [__watcall]
// ================================================================================================

void __watcall sub_7c901(int *param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  __CHK(0x30);
  if (dword_d19ec == 0) {
    uVar2 = 0xfa;
    uVar1 = 0xf8;
  }
  else {
    uVar2 = 0x40;
    uVar1 = 0x42;
  }
  sub_b4fac(*param_1 + 10,param_1[3] + 0x12,*param_1 + 10,param_1[1] + 0x13,uVar2);
  sub_b4fac(*param_1 + 10,param_1[1] + 0x13,param_1[2] + 9,param_1[1] + 0x13,uVar2);
  sub_b4fac(param_1[2] + 10,param_1[1] + 0x14,param_1[2] + 10,param_1[3] + 0x13,uVar1);
  sub_b4fac(param_1[2] + 10,param_1[3] + 0x13,*param_1 + 0xb,param_1[3] + 0x13,uVar1);
  return;
}


// ================================================================================================
// sub_7c993 @ 0x7c993 [__watcall]
// ================================================================================================

longlong __watcall sub_7c993(undefined4 param_1,uint unaff_EDX)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  byte bVar6;
  
  bVar6 = 0;
  __CHK(4);
  __CHK(0x2c);
  puVar1 = (undefined4 *)allocmem(&aBKGD_c337c,0x8c31,0x20);
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
  *(undefined2 *)(puVar1 + 1) = 0x98;
  *(undefined2 *)((int)puVar1 + 6) = 0xec;
  grabshape(puVar1,10,0x13,puVar1);
  controller_dialog(dword_c53fb == 2);
  controller_select_dialog(0);
  controller_menu(0);
  drawshape(puVar1,10,0x13);
  freemem(puVar1);
  dword_d19ec = 0;
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// sub_7c9a1 @ 0x7c9a1 [__watcall]
// ================================================================================================

longlong __watcall sub_7c9a1(undefined4 param_1,uint unaff_EDX)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  byte bVar6;
  
  bVar6 = 0;
  __CHK(4);
  __CHK(0x2c);
  puVar1 = (undefined4 *)allocmem(&aBKGD_c337c,0x8c31,0x20);
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
  *(undefined2 *)(puVar1 + 1) = 0x98;
  *(undefined2 *)((int)puVar1 + 6) = 0xec;
  grabshape(puVar1,10,0x13,puVar1);
  controller_dialog(dword_c53fb == 2);
  controller_select_dialog(1);
  controller_menu(1);
  drawshape(puVar1,10,0x13);
  freemem(puVar1);
  dword_d19ec = 0;
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// sub_7ca53 @ 0x7ca53 [__watcall]
// ================================================================================================

longlong __watcall sub_7ca53(undefined4 param_1,uint unaff_EDX)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  byte bVar6;
  
  bVar6 = 0;
  __CHK(4);
  __CHK(0x2c);
  puVar1 = (undefined4 *)allocmem(&aBKGD_c337c,0x8c31,0x20);
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
  *(undefined2 *)(puVar1 + 1) = 0x98;
  *(undefined2 *)((int)puVar1 + 6) = 0xec;
  grabshape(puVar1,10,0x13);
  controller_dialog(0);
  controller_select_dialog(0);
  controller_menu(0);
  drawshape(puVar1,10,0x13);
  freemem(puVar1);
  dword_d19ec = 0;
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// sub_7ca61 @ 0x7ca61 [__watcall]
// ================================================================================================

longlong __watcall sub_7ca61(undefined4 param_1,uint unaff_EDX)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  byte bVar6;
  
  bVar6 = 0;
  __CHK(4);
  __CHK(0x2c);
  puVar1 = (undefined4 *)allocmem(&aBKGD_c337c,0x8c31,0x20);
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
  *(undefined2 *)(puVar1 + 1) = 0x98;
  *(undefined2 *)((int)puVar1 + 6) = 0xec;
  grabshape(puVar1,10,0x13);
  controller_dialog(0);
  controller_select_dialog(1);
  controller_menu(1);
  drawshape(puVar1,10,0x13);
  freemem(puVar1);
  dword_d19ec = 0;
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// sub_7caf7 @ 0x7caf7 [__watcall]
// ================================================================================================

/* WARNING: Removing unreachable block (ram,0x0007cfe4) */

undefined8 __watcall sub_7caf7(undefined4 param_1,undefined4 unaff_EDX)

{
  undefined4 *puVar1;
  int iVar2;
  short sVar3;
  int extraout_EDX;
  int iVar4;
  int extraout_EDX_00;
  int extraout_EDX_01;
  int iVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  byte bVar9;
  undefined4 uVar10;
  undefined4 *puVar11;
  
  bVar9 = 0;
  __CHK(4);
  __CHK(0x34);
  uVar10 = 0;
  puVar1 = (undefined4 *)allocmem(&aBKGD_c337c,0x8c31,0x20);
  puVar7 = puVar1 + (uint)bVar9 * -2 + 1;
  puVar11 = pointer_shapes + (uint)bVar9 * -2 + 1;
  *puVar1 = *pointer_shapes;
  puVar8 = puVar7 + (uint)bVar9 * -2 + 1;
  puVar6 = puVar11 + (uint)bVar9 * -2 + 1;
  *puVar7 = *puVar11;
  *puVar8 = *puVar6;
  puVar8[(uint)bVar9 * -2 + 1] = puVar6[(uint)bVar9 * -2 + 1];
  *(undefined *)(puVar8 + (uint)bVar9 * -2 + 1 + (uint)bVar9 * -2 + 1) =
       *(undefined *)(puVar6 + (uint)bVar9 * -2 + 1 + (uint)bVar9 * -2 + 1);
  *(undefined2 *)(puVar1 + 1) = 0x98;
  *(undefined2 *)((int)puVar1 + 6) = 0xec;
  puVar11 = puVar1;
  grabshape(puVar1,10,0x13,puVar1,uVar10,puVar1);
  controller_dialog(0);
  controller_select_dialog(0);
  controller_menu(0);
  drawshape(puVar1,10,0x13);
  if (dword_c5403 < 0) {
    sVar3 = 0;
  }
  else if (dword_c5413 == 0) {
    sVar3 = 1;
  }
  else {
    sVar3 = 2;
  }
  iVar2 = (int)user1_team;
  iVar5 = (int)(short)user2_team;
  if (((dword_c5403 < 0) || (dword_c5407 < 0)) || (dword_c5413 != dword_c5417)) {
    dword_c4e0c = 0;
  }
  else {
    dword_c4e0c = 1;
  }
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
  user1_team = sVar3;
  ensure_user_slot(0);
  sub_7cea1();
  if ((((&unk_dff3a)[dword_dff36 >> 0x10] == '\x1b') && (extraout_EDX == 1)) &&
     ((iVar2 != 1 && (iVar5 != 1)))) {
    faceoff_timer = 0;
  }
  iVar4 = 1;
  do {
    if (((iVar2 == iVar4) || (iVar5 == iVar4)) &&
       ((user1_team != iVar4 && ((short)user2_team != iVar4)))) {
      sub_7cbb3(iVar4 == 2);
      iVar4 = extraout_EDX_00;
    }
    else if (((iVar2 != iVar4) && (iVar5 != iVar4)) &&
            ((user1_team == iVar4 || ((short)user2_team == iVar4)))) {
      sub_7cc8a(iVar4 == 2);
      iVar4 = extraout_EDX_01;
    }
    iVar4 = iVar4 + 1;
  } while (iVar4 < 3);
  freemem(puVar11);
  return CONCAT44(unaff_EDX,uVar10);
}


// ================================================================================================
// sub_7cb9f @ 0x7cb9f [__watcall]
// ================================================================================================

/* WARNING: Removing unreachable block (ram,0x0007cfed) */

undefined8 __watcall sub_7cb9f(undefined4 param_1,undefined4 unaff_EDX)

{
  undefined4 *puVar1;
  int iVar2;
  short sVar3;
  int extraout_EDX;
  int iVar4;
  int extraout_EDX_00;
  int extraout_EDX_01;
  int iVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  byte bVar9;
  undefined4 uVar10;
  undefined4 *puVar11;
  
  bVar9 = 0;
  __CHK(4);
  __CHK(0x34);
  uVar10 = 0;
  puVar1 = (undefined4 *)allocmem(&aBKGD_c337c,0x8c31,0x20);
  puVar7 = puVar1 + (uint)bVar9 * -2 + 1;
  puVar11 = pointer_shapes + (uint)bVar9 * -2 + 1;
  *puVar1 = *pointer_shapes;
  puVar8 = puVar7 + (uint)bVar9 * -2 + 1;
  puVar6 = puVar11 + (uint)bVar9 * -2 + 1;
  *puVar7 = *puVar11;
  *puVar8 = *puVar6;
  puVar8[(uint)bVar9 * -2 + 1] = puVar6[(uint)bVar9 * -2 + 1];
  *(undefined *)(puVar8 + (uint)bVar9 * -2 + 1 + (uint)bVar9 * -2 + 1) =
       *(undefined *)(puVar6 + (uint)bVar9 * -2 + 1 + (uint)bVar9 * -2 + 1);
  *(undefined2 *)(puVar1 + 1) = 0x98;
  *(undefined2 *)((int)puVar1 + 6) = 0xec;
  puVar11 = puVar1;
  grabshape(puVar1,10,0x13,puVar1,uVar10,puVar1);
  controller_dialog(0);
  controller_select_dialog(1);
  controller_menu(1);
  drawshape(puVar1,10,0x13);
  if (dword_c5407 < 0) {
    sVar3 = 0;
  }
  else if (dword_c5417 == 0) {
    sVar3 = 1;
  }
  else {
    sVar3 = 2;
  }
  iVar2 = (int)user1_team;
  iVar5 = (int)(short)user2_team;
  if (((dword_c5403 < 0) || (dword_c5407 < 0)) || (dword_c5413 != dword_c5417)) {
    dword_c4e0c = 0;
  }
  else {
    dword_c4e0c = 1;
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
  user2_team._0_2_ = sVar3;
  ensure_user_slot(1);
  sub_7cea1();
  if ((((&unk_dff3a)[dword_dff36 >> 0x10] == '\x1b') && (extraout_EDX == 1)) &&
     ((iVar2 != 1 && (iVar5 != 1)))) {
    faceoff_timer = 0;
  }
  iVar4 = 1;
  do {
    if (((iVar2 == iVar4) || (iVar5 == iVar4)) &&
       ((user1_team != iVar4 && ((short)user2_team != iVar4)))) {
      sub_7cbb3(iVar4 == 2);
      iVar4 = extraout_EDX_00;
    }
    else if (((iVar2 != iVar4) && (iVar5 != iVar4)) &&
            ((user1_team == iVar4 || ((short)user2_team == iVar4)))) {
      sub_7cc8a(iVar4 == 2);
      iVar4 = extraout_EDX_01;
    }
    iVar4 = iVar4 + 1;
  } while (iVar4 < 3);
  freemem(puVar11);
  return CONCAT44(unaff_EDX,uVar10);
}


// ================================================================================================
// sub_7cbb3 @ 0x7cbb3 [__watcall]
// ================================================================================================

void __watcall sub_7cbb3(uint param_1)

{
  int iVar1;
  
  __CHK(0x10);
  if (((short)(&word_df64c)[param_1 * 0x80] < 0) &&
     ((*(byte *)(&word_df64c + param_1 * 0x80) & 0xf0) != 0)) {
    *(byte *)(&word_df64c + param_1 * 0x80) = *(byte *)(&word_df64c + param_1 * 0x80) & 0xf;
    iVar1 = ((int)(&dword_df622)[(uint)(param_1 == 0) * 0x40] >> 0x10) -
            ((int)(&dword_df622)[param_1 * 0x40] >> 0x10);
    if ((iVar1 < 1) || (((2 < iVar1 || (period_idx != 2)) || (0x3c < clock_seconds)))) {
      if (((((game_flags & 1) == 0) && (-1 < *p_puck_carrier)) &&
          (*p_puck_carrier < '\x06' != param_1)) && ((game_flags & 8) != 0)) {
        return;
      }
      *(undefined *)((int)&word_df64c + param_1 * 0x100 + 1) = 0;
      *(&off_cd4a0)[param_1 * 3] = 2;
      *(&off_cd498)[(int)(short)((&word_df64c)[param_1 * 0x80] & 0xf) + param_1 * 3] = 1;
      apply_line_change();
    }
  }
  return;
}


// ================================================================================================
// sub_7cc8a @ 0x7cc8a [__watcall]
// ================================================================================================

void __watcall sub_7cc8a(uint param_1)

{
  __CHK(0x10);
  if ((((short)(&word_df64c)[param_1 * 0x80] < 0) &&
      ((*(byte *)(&word_df64c + param_1 * 0x80) & 0xf0) == 0)) &&
     (((game_flags & 1) != 0 ||
      (((*p_puck_carrier < '\0' || (param_1 == *p_puck_carrier < '\x06')) || ((game_flags & 8) == 0)
       ))))) {
    (&word_df64c)[param_1 * 0x80] = (&word_df64c)[param_1 * 0x80] | 0xfff0;
  }
  return;
}


// ================================================================================================
// ensure_user_slot @ 0x7cce5 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall ensure_user_slot(int param_1)

{
  short *psVar1;
  int *piVar2;
  int iVar3;
  short *psVar4;
  short sVar5;
  short sVar6;
  int iVar7;
  int iVar8;
  short local_1c;
  
  __CHK(0x28);
  if (param_1 == 0) {
    psVar4 = &user1_team;
    psVar1 = (short *)&user1_slot;
  }
  else {
    psVar4 = (short *)&user2_team;
    psVar1 = &user2_slot;
  }
  if (*psVar4 == 0) {
    if (*psVar1 == -1) {
      return;
    }
    local_1c = -1;
  }
  else {
    if (((*psVar4 == 1) && (-1 < *psVar1)) && (*psVar1 < 6)) {
      return;
    }
    if (((*psVar4 == 2) && (5 < *psVar1)) && (*psVar1 < 0xc)) {
      return;
    }
    iVar8 = 0x10000000;
    if (*psVar4 == 1) {
      piVar2 = &entities;
    }
    else {
      piVar2 = &unk_dfb1c;
    }
    sVar5 = 6;
    do {
      if (((-1 < *(short *)((int)piVar2 + 0x1a)) && ((*(byte *)((int)piVar2 + 0x45) & 4) == 0)) &&
         ((*(byte *)(piVar2 + 0x11) & 0x20) == 0)) {
        iVar3 = (int)(short)((short)(char)((ushort)*(undefined2 *)p_puck_vx >> 8) + *p_puck_x) -
                (*piVar2 >> 0x10);
        iVar7 = (int)(short)(*p_puck_y + (short)(char)((ushort)*(undefined2 *)p_puck_vy >> 8)) -
                (piVar2[1] >> 0x10);
        iVar3 = iVar7 * iVar7 + iVar3 * iVar3;
        if ((short)*p_puck_carrier == *(short *)((int)piVar2 + 0x6a)) {
          iVar3 = -1;
        }
        if (iVar3 <= iVar8) {
          sVar6 = user2_slot;
          if (param_1 != 0) {
            sVar6 = _user1_slot;
          }
          if (*(short *)((int)piVar2 + 0x6a) != sVar6) {
            iVar8 = iVar3;
            local_1c = *(short *)((int)piVar2 + 0x6a);
          }
        }
      }
      piVar2 = piVar2 + 0x20;
      sVar5 = sVar5 + -1;
    } while (sVar5 != 0);
  }
  if (param_1 == 0) {
    if (local_1c != _user1_slot) {
      _user1_slot = find_switch_target((int)local_1c,(int)_user1_slot);
    }
  }
  else if (local_1c != user2_slot) {
    user2_slot = find_switch_target((int)local_1c,(int)user2_slot);
  }
  return;
}


// ================================================================================================
// sub_7cea1 @ 0x7cea1 [__watcall]
// ================================================================================================

void __watcall sub_7cea1(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  __CHK(0x18);
  iVar5 = 0;
  do {
    iVar2 = (iVar5 != 0) + 1;
    if ((user1_team != iVar2) && ((short)user2_team != iVar2)) {
      (&word_cbc56)[iVar5] = 0;
      (&word_cbc6a)[iVar5] = 0;
      if (iVar5 == 0) {
        iVar2 = 0;
        do {
          (&unk_df861)[iVar2 * 0x80] = (&unk_df861)[iVar2 * 0x80] & 0xf7;
          iVar2 = iVar2 + 1;
        } while (iVar2 < 6);
      }
      else {
        iVar2 = 6;
        do {
          (&unk_df861)[iVar2 * 0x80] = (&unk_df861)[iVar2 * 0x80] & 0xf7;
          iVar2 = iVar2 + 1;
        } while (iVar2 < 0xc);
      }
      (&byte_df658)[iVar5 * 0x100] = (&byte_df658)[iVar5 * 0x100] & 0xfd;
      iVar2 = (&dword_df648)[(uint)(iVar5 == 0) * 0x40];
      iVar1 = (&dword_df648)[iVar5 * 0x40];
      iVar3 = (iVar2 >> 0x10) - (iVar1 >> 0x10);
      iVar4 = *(int *)((int)&dword_df63a + iVar5 * 0x100 + 2) >> 0x10;
      if ((0 < iVar3) && (iVar4 < 6)) {
        *(undefined2 *)(&word_df63e + iVar5 * 0x100) = 6;
      }
      if ((iVar3 < 0) && ((5 < iVar4 || (iVar4 < 4)))) {
        *(undefined2 *)(&word_df63e + iVar5 * 0x100) = 4;
      }
      if ((iVar2 >> 0x10 == iVar1 >> 0x10) && (2 < iVar4)) {
        *(undefined2 *)(&word_df63e + iVar5 * 0x100) = 0;
      }
    }
    iVar5 = iVar5 + 1;
  } while (iVar5 < 2);
  return;
}


// ================================================================================================
// sub_7cfb9 @ 0x7cfb9 [__watcall]
// ================================================================================================

undefined8 __watcall sub_7cfb9(int param_1)

{
  uint uVar1;
  short sVar2;
  int iVar3;
  short sVar4;
  int extraout_EDX;
  int iVar5;
  int extraout_EDX_00;
  int extraout_EDX_01;
  int iVar6;
  int unaff_EBP;
  undefined4 in_stack_00000004;
  undefined4 in_stack_00000008;
  undefined4 in_stack_00000018;
  
  if (*(int *)((int)&dword_c5413 + param_1) == 0) {
    sVar4 = 1;
  }
  else {
    sVar4 = 2;
  }
  iVar3 = (int)user1_team;
  iVar6 = (int)(short)user2_team;
  sVar2 = sVar4;
  if (unaff_EBP != 0) {
    sVar2 = user1_team;
    user2_team._0_2_ = sVar4;
  }
  user1_team = sVar2;
  if (((dword_c5403 < 0) || (dword_c5407 < 0)) || (dword_c5413 != dword_c5417)) {
    dword_c4e0c = 0;
  }
  else {
    dword_c4e0c = 1;
  }
  uVar1 = (&dword_c540b)[unaff_EBP];
  if (uVar1 < 4) {
    if (uVar1 != 0) {
      if (uVar1 < 2) {
        (&controller_type)[unaff_EBP] = 1;
      }
      else if (uVar1 == 2) {
        (&controller_type)[unaff_EBP] = 2;
      }
    }
  }
  else if (uVar1 < 5) {
    (&controller_type)[unaff_EBP] = 4;
  }
  else if (7 < uVar1) {
    if (uVar1 < 9) {
      (&controller_type)[unaff_EBP] = 8;
    }
    else if (uVar1 == 0x10) {
      (&controller_type)[unaff_EBP] = 0;
    }
  }
  ensure_user_slot();
  sub_7cea1();
  if ((((&unk_dff3a)[dword_dff36 >> 0x10] == '\x1b') && (extraout_EDX == 1)) &&
     ((iVar3 != 1 && (iVar6 != 1)))) {
    faceoff_timer = 0;
  }
  iVar5 = 1;
  do {
    if (((iVar3 == iVar5) || (iVar6 == iVar5)) &&
       ((user1_team != iVar5 && ((short)user2_team != iVar5)))) {
      sub_7cbb3(iVar5 == 2);
      iVar5 = extraout_EDX_00;
    }
    else if (((iVar3 != iVar5) && (iVar6 != iVar5)) &&
            ((user1_team == iVar5 || ((short)user2_team == iVar5)))) {
      sub_7cc8a(iVar5 == 2);
      iVar5 = extraout_EDX_01;
    }
    iVar5 = iVar5 + 1;
  } while (iVar5 < 3);
  freemem(in_stack_00000008);
  return CONCAT44(in_stack_00000018,in_stack_00000004);
}


// ================================================================================================
// sub_7d137 @ 0x7d137 [__watcall]
// ================================================================================================

longlong __watcall sub_7d137(undefined4 param_1,uint unaff_EDX)

{
  undefined2 uVar1;
  undefined2 uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  byte bVar7;
  int iVar8;
  undefined4 *puVar9;
  
  bVar7 = 0;
  __CHK(4);
  __CHK(0x30);
  iVar8 = 0;
  puVar3 = (undefined4 *)allocmem(&aBKGD_c337c,0x8c31,0x20);
  puVar5 = puVar3 + (uint)bVar7 * -2 + 1;
  puVar9 = pointer_shapes + (uint)bVar7 * -2 + 1;
  *puVar3 = *pointer_shapes;
  puVar6 = puVar5 + (uint)bVar7 * -2 + 1;
  puVar4 = puVar9 + (uint)bVar7 * -2 + 1;
  *puVar5 = *puVar9;
  *puVar6 = *puVar4;
  puVar6[(uint)bVar7 * -2 + 1] = puVar4[(uint)bVar7 * -2 + 1];
  *(undefined *)(puVar6 + (uint)bVar7 * -2 + 1 + (uint)bVar7 * -2 + 1) =
       *(undefined *)(puVar4 + (uint)bVar7 * -2 + 1 + (uint)bVar7 * -2 + 1);
  *(undefined2 *)(puVar3 + 1) = 0x98;
  *(undefined2 *)((int)puVar3 + 6) = 0xec;
  puVar9 = puVar3;
  grabshape(puVar3,10,0x13,iVar8,puVar3);
  controller_dialog(1);
  controller_select_dialog(iVar8);
  controller_menu(iVar8);
  drawshape(puVar3,10,0x13);
  if ((&dword_c5403)[iVar8] < 0) {
    uVar2 = 0;
  }
  else if ((&dword_c5413)[iVar8] == 0) {
    uVar2 = 1;
  }
  else {
    uVar2 = 2;
  }
  uVar1 = uVar2;
  if (iVar8 != 0) {
    uVar1 = user1_team;
    user2_team._0_2_ = uVar2;
  }
  user1_team = uVar1;
  if (((dword_c5403 < 0) || (dword_c5407 < 0)) || (dword_c5413 != dword_c5417)) {
    dword_c4e0c = 0;
  }
  else {
    dword_c4e0c = 1;
  }
  freemem(puVar9);
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// sub_7d145 @ 0x7d145 [__watcall]
// ================================================================================================

longlong __watcall sub_7d145(undefined4 param_1,uint unaff_EDX)

{
  undefined2 uVar1;
  undefined2 uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  byte bVar7;
  int iVar8;
  undefined4 *puVar9;
  
  bVar7 = 0;
  __CHK(4);
  __CHK(0x30);
  iVar8 = 1;
  puVar3 = (undefined4 *)allocmem(&aBKGD_c337c,0x8c31,0x20);
  puVar5 = puVar3 + (uint)bVar7 * -2 + 1;
  puVar9 = pointer_shapes + (uint)bVar7 * -2 + 1;
  *puVar3 = *pointer_shapes;
  puVar6 = puVar5 + (uint)bVar7 * -2 + 1;
  puVar4 = puVar9 + (uint)bVar7 * -2 + 1;
  *puVar5 = *puVar9;
  *puVar6 = *puVar4;
  puVar6[(uint)bVar7 * -2 + 1] = puVar4[(uint)bVar7 * -2 + 1];
  *(undefined *)(puVar6 + (uint)bVar7 * -2 + 1 + (uint)bVar7 * -2 + 1) =
       *(undefined *)(puVar4 + (uint)bVar7 * -2 + 1 + (uint)bVar7 * -2 + 1);
  *(undefined2 *)(puVar3 + 1) = 0x98;
  *(undefined2 *)((int)puVar3 + 6) = 0xec;
  puVar9 = puVar3;
  grabshape(puVar3,10,0x13,iVar8,puVar3);
  controller_dialog(1);
  controller_select_dialog(iVar8);
  controller_menu(iVar8);
  drawshape(puVar3,10,0x13);
  if ((&dword_c5403)[iVar8] < 0) {
    uVar2 = 0;
  }
  else if ((&dword_c5413)[iVar8] == 0) {
    uVar2 = 1;
  }
  else {
    uVar2 = 2;
  }
  uVar1 = uVar2;
  if (iVar8 != 0) {
    uVar1 = user1_team;
    user2_team._0_2_ = uVar2;
  }
  user1_team = uVar1;
  if (((dword_c5403 < 0) || (dword_c5407 < 0)) || (dword_c5413 != dword_c5417)) {
    dword_c4e0c = 0;
  }
  else {
    dword_c4e0c = 1;
  }
  freemem(puVar9);
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// controller_dialog @ 0x7d254 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall controller_dialog(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined *puVar4;
  int iVar5;
  undefined auStack_134 [246];
  undefined4 local_3e;
  undefined uStack_3a;
  undefined auStack_34 [32];
  
  __CHK(0x14c);
  setdefaultscreen();
  iVar1 = 0;
  do {
    auStack_134[iVar1] = (char)iVar1;
    iVar1 = iVar1 + 1;
  } while (iVar1 < 0x100);
  if (param_1 != 0) {
    uStack_3a = 0x40;
    local_3e = CONCAT22(0x4142,CONCAT11(0x43,(undefined)local_3e));
  }
  dword_d19ec = param_1;
  setremaptable(auStack_134);
  puVar4 = install_path;
  if (byte_ed904 != '\x01') {
    puVar4 = (undefined *)0x0;
  }
  make_path(auStack_34,puVar4,aPlayer_c3381,0);
  uVar2 = loadshapes(auStack_34,0);
  uVar3 = locateshape(uVar2,&aDbox_c3388,10,0x13);
  drawshape2_trans(uVar3);
  freemem(uVar2);
  if (param_1 == 0) {
    uVar2 = 0xfa;
  }
  else {
    uVar2 = 0x40;
  }
  settextpos(uVar2,0xff);
  iVar1 = dword_d195c;
  iVar5 = dword_d1960 + 0x14;
  fillrect(dword_d195c + 0xb,iVar5,(dword_d1964 + 10) - (dword_d195c + 0xb),
           (dword_d1968 + 0x13) - iVar5,local_3e >> 0x18);
  printstr_at((&off_c54a9)[user2_team._2_2_],iVar1 + 0xe,iVar5);
  iVar1 = dword_d196c;
  iVar5 = dword_d1970 + 0x14;
  fillrect(dword_d196c + 0xb,iVar5,(dword_d1974 + 10) - (dword_d196c + 0xb),
           (dword_d1978 + 0x13) - iVar5,local_3e >> 0x18);
  printstr_at((&off_c54a9)[_away_team_id],iVar1 + 0xe,iVar5);
  return;
}


// ================================================================================================
// controller_select_dialog @ 0x7d3f0 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall controller_select_dialog(int param_1)

{
  int iVar1;
  int extraout_EDX;
  int extraout_EDX_00;
  char *pcVar2;
  undefined4 uVar3;
  
  __CHK(0x28);
  if (dword_d19ec == 0) {
    uVar3 = 0xfa;
  }
  else {
    uVar3 = 0x40;
  }
  settextpos(uVar3,0xff);
  if (param_1 == 0) {
    pcVar2 = aOneS;
  }
  else {
    pcVar2 = aTwoS;
  }
  printstr_at(pcVar2,0x4a,0x20);
  dword_ed360 = 0;
  dword_ed364 = ((_input_devices << 0x1e) >> 0x1f) << 3 | (_input_devices & 1) << 2 | 0x1c3 |
                ((_input_devices << 0x1d) >> 0x1f) << 4 | ((_input_devices << 0x1c) >> 0x1f) << 5;
  if ((&dword_c540b)[param_1 == 0] != 0x10) {
    dword_ed364 = dword_ed364 & ~((&dword_c540b)[param_1 == 0] << 2);
  }
  iVar1 = (&dword_c5403)[param_1];
  if (iVar1 < 0) {
    if (iVar1 == -1) {
      dword_ed360 = 0x41;
    }
    else if (iVar1 == -2) {
      dword_ed360 = 0x42;
    }
  }
  else {
    dword_ed360 = ((&dword_c5413)[param_1] != 0) + 1;
    if ((dword_ed364 & (&dword_c540b)[param_1] << 2) != 0) {
      dword_ed360 = dword_ed360 | (&dword_c540b)[param_1] << 2;
    }
  }
  iVar1 = 0;
  do {
    if ((dword_ed360 & 1 << ((byte)iVar1 & 0x1f)) == 0) {
      sub_7c901(&dword_d195c + iVar1 * 4);
      iVar1 = extraout_EDX_00;
    }
    else {
      sub_7c852();
      iVar1 = extraout_EDX;
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 < 9);
  if (dword_d19ec == 0) {
    uVar3 = 0xf8;
  }
  else {
    uVar3 = 0x42;
  }
  settextpos(uVar3,0xff);
  if ((dword_ed364 & 4) == 0) {
    printstr_at(aTheMouse,dword_d197c + 0x19,dword_d1980 + 0x14);
  }
  if ((dword_ed364 & 8) == 0) {
    printstr_at(aJoystickOne,dword_d198c + 0x12,dword_d1990 + 0x14);
  }
  if ((dword_ed364 & 0x10) == 0) {
    printstr_at(aJoystickTwo,dword_d199c + 0x11,dword_d19a0 + 0x14);
  }
  if ((dword_ed364 & 0x20) == 0) {
    printstr_at(aTheKeyboard,dword_d19ac + 0xf,dword_d19b0 + 0x14);
  }
  return;
}


// ================================================================================================
// sub_7d61f @ 0x7d61f [__watcall]
// ================================================================================================

undefined4 __watcall sub_7d61f(int param_1,int unaff_EDX,int *unaff_EBX)

{
  int iVar1;
  
  __CHK(0xc);
  iVar1 = 0;
  while ((((param_1 + -6 < (int)(&dword_d195c)[iVar1 * 4] ||
           ((int)(&dword_d1964)[iVar1 * 4] < param_1 + -6)) ||
          (unaff_EDX + -0x13 < (int)(&dword_d1960)[iVar1 * 4])) ||
         ((int)(&dword_d1968)[iVar1 * 4] < unaff_EDX + -0x13))) {
    iVar1 = iVar1 + 1;
    if (8 < iVar1) {
      return 0;
    }
  }
  *unaff_EBX = iVar1;
  return 1;
}


// ================================================================================================
// sub_7d671 @ 0x7d671 [__watcall]
// ================================================================================================

void __watcall sub_7d671(void)

{
  int iVar1;
  int extraout_EDX;
  int extraout_EDX_00;
  
  __CHK(0x10);
  iVar1 = 0;
  do {
    if ((dword_ed360 & 1 << ((byte)iVar1 & 0x1f)) == 0) {
      sub_7c901(&dword_d195c + iVar1 * 4);
      iVar1 = extraout_EDX_00;
    }
    else {
      sub_7c852();
      iVar1 = extraout_EDX;
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 < 9);
  return;
}


// ================================================================================================
// controller_menu @ 0x7d6b1 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

longlong __watcall controller_menu(int param_1,uint unaff_EDX)

{
  ulonglong uVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 extraout_EDX;
  undefined4 ****ppppuVar4;
  undefined4 ****ppppuVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  byte bVar8;
  ulonglong uVar9;
  undefined8 uVar10;
  uint local_30;
  undefined4 *local_2c;
  undefined4 ***local_28;
  int local_24;
  undefined4 ***local_20;
  int iStack_1c;
  
  bVar8 = 0;
  __CHK(0x44);
  getmouse(&local_2c,&iStack_1c,&local_20);
  local_24 = iStack_1c;
  local_28 = local_20;
  puVar2 = (undefined4 *)
           allocmem(aPointer_c33ca,
                    (((int)pointer_shapes[1] >> 0x10) + 1) *
                    ((*(int *)((int)pointer_shapes + 2) >> 0x10) + 1) + 0x11,0x20);
  puVar6 = puVar2 + (uint)bVar8 * -2 + 1;
  ppppuVar4 = pointer_shapes + (uint)bVar8 * -2 + 1;
  *puVar2 = *pointer_shapes;
  puVar7 = puVar6 + (uint)bVar8 * -2 + 1;
  ppppuVar5 = ppppuVar4 + (uint)bVar8 * -2 + 1;
  *puVar6 = *ppppuVar4;
  *puVar7 = *ppppuVar5;
  puVar7[(uint)bVar8 * -2 + 1] = ppppuVar5[(uint)bVar8 * -2 + 1];
  *(undefined *)(puVar7 + (uint)bVar8 * -2 + 1 + (uint)bVar8 * -2 + 1) =
       *(undefined *)(ppppuVar5 + (uint)bVar8 * -2 + 1 + (uint)bVar8 * -2 + 1);
  *(short *)(puVar2 + 1) = *(short *)(pointer_shapes + 1) + 1;
  *(short *)((int)puVar2 + 6) = *(short *)((int)pointer_shapes + 6) + 1;
  grabshape(puVar2,local_24 + -4,local_28);
  ppppuVar4 = (undefined4 ****)local_28;
  drawshape_remap(pointer_shapes,local_24 + -4,local_28);
  uVar9 = event_queue_reset();
LAB_0007d779:
  local_2c = (undefined4 *)0x0;
  do {
    uVar10 = event_queue_pop((int)uVar9,(int)(uVar9 >> 0x20),ppppuVar4);
    uVar1 = CONCAT44((int)((ulonglong)uVar10 >> 0x20),local_2c);
    if ((int)uVar10 == 0) break;
    ppppuVar4 = &local_28;
    uVar9 = (*ui_poll_callback)();
    local_2c = (undefined4 *)uVar9;
    uVar1 = uVar9;
  } while ((uVar9 & 6) == 0);
  local_2c = (undefined4 *)uVar1;
  uVar9 = CONCAT44((int)(uVar1 >> 0x20),local_28);
  if (((uVar1 & 2) == 0) && ((uVar1 & 4) == 0)) goto code_r0x0007d7b0;
  if ((uVar1 & 2) == 0) {
    if ((uVar1 & 4) == 0) goto LAB_0007d7d0;
    drawshape(puVar2,iStack_1c + -4,local_20);
LAB_0007d130:
    freemem(puVar2);
    return (ulonglong)unaff_EDX << 0x20;
  }
  drawshape(puVar2,iStack_1c + -4,local_20);
  iVar3 = sub_7d61f(local_24,local_28);
  if (iVar3 == 0) goto LAB_0007d7da;
  local_30 = 1 << ((byte)local_30 & 0x1f);
  if (((local_30 & dword_ed360) == 0) && ((dword_ed364 & local_30) != 0)) {
    if (local_30 < 0x10) {
      if (local_30 < 2) {
        if (local_30 == 1) {
          dword_ed360 = dword_ed360 & 0xfffffffc | 1;
        }
      }
      else if (local_30 < 3) {
        dword_ed360 = dword_ed360 & 0xfffffffc | 2;
      }
      else if (3 < local_30) {
        if (local_30 < 5) {
          dword_ed360 = dword_ed360 & 0xffffff83 | 4;
        }
        else if (local_30 == 8) {
          dword_ed360 = dword_ed360 & 0xffffff83 | 8;
        }
      }
    }
    else if (local_30 < 0x11) {
      dword_ed360 = dword_ed360 & 0xffffff83 | 0x10;
    }
    else if (local_30 < 0x40) {
      if (local_30 == 0x20) {
        dword_ed360 = dword_ed360 & 0xffffff83 | 0x20;
      }
    }
    else if (local_30 < 0x41) {
      dword_ed360 = dword_ed360 & 0xffffff83 | 0x40;
    }
    else if (0x7f < local_30) {
      if (local_30 < 0x81) {
        sub_7c852(&unk_d19cc);
        (&dword_c540b)[param_1] = (int)dword_ed360 >> 2;
        if (dword_ed360 == 0x41) {
          (&dword_c5403)[param_1] = 0xffffffff;
          (&dword_c5413)[param_1] = 0;
          if ((&dword_c5403)[param_1 == 0] == -1) {
            (&dword_c5403)[param_1 == 0] = 0xfffffffe;
          }
          else {
            if ((&dword_c5413)[param_1 == 0] != 0) goto LAB_0007db2b;
            (&dword_c5403)[param_1 == 0] = (int)_away_team_id;
          }
LAB_0007d9b3:
          (&dword_c5413)[param_1 == 0] = 1;
        }
        else if (dword_ed360 == 0x42) {
          (&dword_c5403)[param_1] = 0xfffffffe;
          (&dword_c5413)[param_1] = 1;
          if ((&dword_c5403)[param_1 == 0] == -2) {
LAB_0007db03:
            (&dword_c5403)[param_1 == 0] = 0xffffffff;
            (&dword_c5413)[param_1 == 0] = 0;
          }
          else if ((&dword_c5413)[param_1 == 0] == 1) {
            (&dword_c5403)[param_1 == 0] = (int)user2_team._2_2_;
            (&dword_c5413)[param_1 == 0] = 0;
          }
        }
        else if ((dword_ed360 & 1) == 0) {
          (&dword_c5403)[param_1] = (int)_away_team_id;
          (&dword_c5413)[param_1] = 1;
          if ((&dword_c5403)[param_1 == 0] == -2) goto LAB_0007db03;
        }
        else {
          (&dword_c5403)[param_1] = (int)user2_team._2_2_;
          (&dword_c5413)[param_1] = 0;
          if ((&dword_c5403)[param_1 == 0] == -1) {
            (&dword_c5403)[param_1 == 0] = 0xfffffffe;
            goto LAB_0007d9b3;
          }
        }
LAB_0007db2b:
        sub_8b85b();
        sub_8b92f();
        goto LAB_0007d130;
      }
      if (local_30 == 0x100) {
        sub_7c852(&aX_d19dc);
        goto LAB_0007d130;
      }
    }
    sub_7d671();
  }
  goto LAB_0007d7da;
code_r0x0007d7b0:
  if ((local_24 == iStack_1c) && (local_28 == local_20)) goto LAB_0007d779;
LAB_0007d7d0:
  drawshape(puVar2,iStack_1c + -4,local_20);
LAB_0007d7da:
  grabshape(puVar2,local_24 + -4,local_28);
  ppppuVar4 = pointer_shapes;
  drawshape_remap(pointer_shapes,local_24 + -4,local_28);
  uVar9 = CONCAT44(extraout_EDX,local_28);
  iStack_1c = local_24;
  local_20 = local_28;
  goto LAB_0007d779;
}


// ================================================================================================
// sub_7db67 @ 0x7db67 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall sub_7db67(int param_1,int unaff_EDX,int unaff_EBX,undefined2 unaff_CX)

{
  __CHK(8);
  user2_team._2_2_ = (undefined2)unaff_EBX;
  dword_c5403 = param_1;
  if (param_1 == unaff_EBX) {
    if (dword_c540b == 0x10) {
      dword_c5403 = -1;
    }
    dword_c5413 = 0;
  }
  else {
    if (dword_c540b == 0x10) {
      dword_c5403 = -2;
    }
    dword_c5413 = 1;
  }
  if (unaff_EDX < 0) {
    dword_c5417 = (uint)(dword_c5413 == 0);
    dword_c5407 = (param_1 != unaff_EBX) - 2;
    dword_c540f = 0x10;
  }
  else {
    dword_c5417 = (uint)(unaff_EDX != unaff_EBX);
    dword_c5407 = unaff_EDX;
    if (dword_c540f == 0x10) {
      if (((input_devices & 2) == 0) || (dword_c540b == 2)) {
        if (((input_devices & 4) == 0) || (dword_c540b == 4)) {
          if (((input_devices & 8) == 0) || (dword_c540b == 8)) {
            dword_c540f = 1;
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
  }
  _away_team_id = unaff_CX;
  sub_8b85b();
  return;
}


// ================================================================================================
// load_music_banks @ 0x7dc8b [__watcall]
// ================================================================================================

void __watcall load_music_banks(void)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  undefined *puVar6;
  int iVar7;
  char *pcVar8;
  int iVar9;
  undefined auStackY_34 [16];
  int aiStackY_24 [4];
  
  __CHK(0x38);
  dword_ccc94 = 0x20;
  aiStackY_24[3] = user2_team >> 0x10;
  if (0x19 < aiStackY_24[3]) {
    aiStackY_24[3] = 0xd;
  }
  iVar9 = 0;
  do {
    iVar2 = *(int *)(&unk_d1be0 + aiStackY_24[3] * 6 + iVar9) >> 0x18;
    if (iVar2 < 0) {
      (&unk_ed368)[iVar9] = 0;
    }
    else {
      puVar6 = install_path;
      if ((&file_on_disk)[*(int *)(&unk_d1cee + iVar2 * 4)] != '\x01') {
        puVar6 = (undefined *)0x0;
      }
      make_path(auStackY_34,puVar6,(&off_d1b0b)[iVar2],0);
      uVar3 = music_load_kms(auStackY_34);
      (&unk_ed368)[iVar9] = uVar3;
    }
    iVar9 = iVar9 + 1;
  } while (iVar9 < 6);
  iVar9 = 0;
  do {
    do {
      iVar7 = -1;
      uVar4 = rand();
      iVar5 = (int)(((ulonglong)uVar4 & 0xffffffff00007fff) % 0x12);
      iVar2 = 0;
      while ((iVar2 < 6 && (iVar7 != 0))) {
        if (*(int *)(&unk_d1be0 + aiStackY_24[3] * 6 + iVar2) >> 0x18 ==
            *(int *)(&unk_d1c8b + iVar5 * 4)) {
          iVar7 = 0;
        }
        iVar2 = iVar2 + 1;
      }
      iVar2 = 0;
      while ((iVar2 < iVar9 && (iVar7 != 0))) {
        if (*(int *)(&unk_d1c8b + iVar5 * 4) == aiStackY_24[iVar2]) {
          iVar7 = 0;
        }
        iVar2 = iVar2 + 1;
      }
    } while (iVar7 == 0);
    iVar2 = *(int *)(&unk_d1c8b + iVar5 * 4);
    aiStackY_24[iVar9] = iVar2;
    puVar6 = install_path;
    if ((&file_on_disk)[*(int *)(&unk_d1cee + iVar2 * 4)] != '\x01') {
      puVar6 = (undefined *)0x0;
    }
    make_path(auStackY_34,puVar6,(&off_d1b0b)[iVar2]);
    uVar3 = music_load_kms(auStackY_34);
    (&unk_ed38c)[iVar9] = uVar3;
    iVar9 = iVar9 + 1;
  } while (iVar9 < 3);
  puVar6 = install_path;
  if (dword_c541f == 8) {
    pcVar8 = aMTROCKU;
    cVar1 = byte_ed8cc;
  }
  else {
    if (sound_enabled == '\0') {
      pcVar8 = aADROCKU;
      if (byte_ed7eb != '\x01') {
        puVar6 = (undefined *)0x0;
      }
      goto LAB_0007de31;
    }
    pcVar8 = aSBROCKU;
    cVar1 = byte_ed932;
  }
  if (cVar1 != '\x01') {
    puVar6 = (undefined *)0x0;
  }
LAB_0007de31:
  make_path(auStackY_34,puVar6,pcVar8);
  dword_ed380 = music_load_kms(auStackY_34);
  puVar6 = install_path;
  if ((&file_on_disk)
      [*(int *)(&unk_d1ce6 + (*(int *)(&unk_cc9ad + (user2_team >> 0x10)) >> 0x18) * 4)] != '\x01')
  {
    puVar6 = (undefined *)0x0;
  }
  make_path(auStackY_34,puVar6,(&off_d1cde)[*(int *)(&unk_cc9ad + (user2_team >> 0x10)) >> 0x18]);
  dword_ed384 = music_load_kms(auStackY_34);
  puVar6 = install_path;
  if (byte_ed92d != '\x01') {
    puVar6 = (undefined *)0x0;
  }
  make_path(auStackY_34,puVar6,aROCKDITI,0);
  dword_ed388 = music_load_kms(auStackY_34);
  dword_ccc94 = 0;
  return;
}


// ================================================================================================
// sub_7dec8 @ 0x7dec8 [__watcall]
// ================================================================================================

void __watcall sub_7dec8(void)

{
  int iVar1;
  int extraout_EDX;
  int extraout_EDX_00;
  int extraout_EDX_01;
  
  __CHK(0x1c);
  iVar1 = 0;
  do {
    if ((&unk_ed368)[iVar1] != 0) {
      kms_unload((&unk_ed368)[iVar1]);
      (&unk_ed368)[iVar1] = 0;
      iVar1 = extraout_EDX;
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 < 6);
  iVar1 = 0;
  do {
    if ((&unk_ed38c)[iVar1] != 0) {
      kms_unload((&unk_ed38c)[iVar1]);
      (&unk_ed38c)[iVar1] = 0;
      iVar1 = extraout_EDX_00;
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 < 3);
  iVar1 = 0;
  do {
    if ((&dword_ed380)[iVar1] != 0) {
      kms_unload();
      (&dword_ed380)[iVar1] = 0;
      iVar1 = extraout_EDX_01;
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 < 3);
  return;
}


// ================================================================================================
// sub_7df4e @ 0x7df4e [__watcall]
// ================================================================================================

void __watcall sub_7df4e(uint param_1,byte unaff_DL,undefined4 param_3,undefined4 *unaff_ECX)

{
  int iVar1;
  undefined4 uVar2;
  
  __CHK(0x18);
  if (param_1 < 8) {
    if (param_1 == 4) {
      drawshape_remap_home(unaff_ECX[10]);
      drawshape_remap_home(unaff_ECX[9]);
      uVar2 = unaff_ECX[7];
      goto LAB_0007e021;
    }
  }
  else {
    if (param_1 < 9) {
      drawshape_remap_home(unaff_ECX[10]);
      drawshape_remap_home(unaff_ECX[9]);
      uVar2 = unaff_ECX[1];
      goto LAB_0007e021;
    }
    if (0xf < param_1) {
      if (param_1 < 0x11) {
        drawshape_remap_home(unaff_ECX[10]);
        drawshape_remap_home(unaff_ECX[9]);
        uVar2 = *unaff_ECX;
        goto LAB_0007e021;
      }
      if (param_1 == 0x20) {
        drawshape_remap_home(unaff_ECX[0xb]);
        uVar2 = unaff_ECX[3];
        goto LAB_0007e021;
      }
    }
  }
  drawshape_remap_home(unaff_ECX[10]);
  drawshape_remap_home(unaff_ECX[8]);
  if (unaff_DL < 4) {
    iVar1 = unaff_DL + 3;
  }
  else {
    iVar1 = 2;
  }
  uVar2 = unaff_ECX[iVar1];
LAB_0007e021:
  drawshape_remap_home(uVar2);
  return;
}


// ================================================================================================
// sub_7e032 @ 0x7e032 [__watcall]
// ================================================================================================

undefined4 __watcall sub_7e032(void)

{
  __CHK(4);
  return 0;
}


// ================================================================================================
// sub_7e03f @ 0x7e03f [__watcall]
// ================================================================================================

void __watcall
sub_7e03f(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  __CHK(0x14);
  sub_96a78(dword_ed6d0,unaff_EDX,unaff_ECX,unaff_EBX);
  return;
}


// ================================================================================================
// replay_draw_button @ 0x7e067 [__watcall]
// ================================================================================================

void __watcall replay_draw_button(int param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  
  __CHK(0x34);
  uVar1 = (&unk_d1dc8)[param_1 * 7];
  iVar4 = (&unk_d1dcc)[param_1 * 7] + -0xa8;
  uVar2 = (&unk_d1dd0)[param_1 * 7];
  iVar3 = (&unk_d1dd4)[param_1 * 7] + -0xa8;
  sub_b4fac(uVar1,iVar4,uVar2,iVar4,0x10);
  sub_b4fac(uVar1,iVar4,uVar1,iVar3,0x10);
  sub_b4fac(uVar2,iVar4,uVar2,iVar3,0x15);
  sub_b4fac(uVar1,iVar3,uVar2,iVar3,0x15);
  return;
}


// ================================================================================================
// instant_replay @ 0x7e0fa [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall instant_replay(int param_1)

{
  short sVar1;
  short sVar2;
  short sVar3;
  undefined2 extraout_var;
  int iVar4;
  undefined4 uVar5;
  undefined *puVar6;
  char *pcVar7;
  undefined8 uVar8;
  undefined auStack_38 [16];
  undefined4 local_28;
  short local_24;
  undefined4 local_20;
  undefined4 uStack_1c;
  
  __CHK(0x50);
  if ((dword_c53fb == 0) || ((dword_c5403 < 0 && (dword_c5407 < 0)))) {
    dword_ed6f8 = 1;
  }
  else {
    dword_ed6f8 = 0;
  }
  dword_ed754._0_2_ = 0x44;
  dword_ed754._2_2_ = 0;
  dword_ed750 = 8;
  dword_ed6e0 = 0x100;
  dword_ed6dc = 0xbc;
  setmouselimits(0,0,0x140,0xc1);
  setmousepos(dword_ed6e0,dword_ed6dc);
  select_game_surface();
  setclip(0,0x140,0,0x20);
  puVar6 = install_path;
  if (dword_ed6f8 == 0) {
    pcVar7 = aGadget5;
    if (byte_ed862 != '\x01') {
      puVar6 = (undefined *)0x0;
    }
  }
  else {
    pcVar7 = aGadget6;
    if (byte_ed9ef != '\x01') {
      puVar6 = (undefined *)0x0;
    }
  }
  make_path(auStack_38,puVar6,pcVar7,&aPPV);
  dword_ed6d8 = loadfile(auStack_38,0);
  dword_ed6e4 = locateshape(dword_ed6d8,&aGad1);
  blit_rle_frame(dword_ed6e4,0,0);
  replay_draw_button(6);
  replay_draw_button(2);
  drawshape_remap(pointer_shapes,dword_ed6e0,dword_ed6dc + -0xa8);
  sVar2 = (short)dword_d8c7c;
  dword_c66d4 = 1;
  dword_c66d0 = 1;
  local_20 = CONCAT22(extraout_var,(short)camera);
  uStack_1c = CONCAT22(extraout_var,camera._2_2_);
  local_24 = (short)dword_d8c74;
  sVar1 = crowd_noise._2_2_;
  dword_ed70c = 0;
  dword_cd4fa = CONCAT22(0xffff,(undefined2)dword_cd4fa);
  dword_ed74c = -1;
  dword_ed6ec = -1;
  dword_ed6fc = 0;
  word_ed758 = 0;
  dword_c7444 = dword_c7444 + 1000;
  dword_c7448 = dword_c7448 + 1000;
  dword_e03a4 = replay_oldest_frame(CONCAT22(extraout_var,(short)dword_d8c74),0);
  local_28._0_2_ = 0;
  local_28._2_2_ = 0;
  replay_seek_frames(0);
  dword_ccc88 = crowd_noise >> 0x10;
  dword_d8c7c = (short)camera + 0x20;
  if (0x40 < dword_d8c7c) {
    dword_d8c7c = 0x40;
  }
  if (dword_d8c7c < 0) {
    dword_d8c7c = 0;
  }
  dword_d8c74 = 0xec - camera._2_2_;
  if (0x1a8 < dword_d8c74) {
    dword_d8c74 = 0x1a8;
  }
  if (dword_d8c74 < 0) {
    dword_d8c74 = 0;
  }
  sub_8c1e2();
  set_camera_offset(0,0);
  begin_frame();
  draw_rink(dword_d8c7c,dword_d8c74);
  iVar4 = word_dd6b2 * 8 + (int)(short)dword_dd6ac;
  set_view_rect(iVar4,(int)_dword_dd6aa + _dword_dd6b0 * 8,iVar4 + 0x140);
  dword_d8c40 = 0;
  replay_draw_frame((int)(short)dword_d8c7c,(int)(short)dword_d8c74);
  set_camera_offset(-(word_dd6b2 * 8 + (int)(short)dword_dd6ac),
                    -((int)_dword_dd6aa + _dword_dd6b0 * 8));
  present_frame();
  fade_palette_to(0,&unk_df314);
  uVar8 = ticks_elapsed();
  event_queue_reset((int)uVar8,(int)((ulonglong)uVar8 >> 0x20),0x10);
  local_28._0_2_ = 0;
  local_28._2_2_ = 0;
  while( true ) {
    select_game_surface();
    iVar4 = replay_control_loop(&local_28);
    if (iVar4 == 0) break;
    word_ed758 = word_ed758 + (short)local_28 * 6;
    local_28 = (int)word_ed758 / 0x14;
    word_ed758 = (short)((longlong)(int)word_ed758 % 0x14);
    sVar3 = replay_seek_frames((int)(short)local_28,((ushort)dword_ed754 & 0x3f) == 0x10);
    local_28._2_2_ = sVar3 >> 0xf;
    local_28._0_2_ = sVar3;
    sub_8c1e2();
    if (dword_ed70c == 0) {
      if (-1 < dword_cd4fa) {
        camera._0_2_ = *(short *)(&unk_e9f18 + (dword_cd4fa >> 0x10) * 2);
        camera._2_2_ = *(short *)(&unk_e9f3a + (dword_cd4fa >> 0x10) * 2);
        if ((short)camera < 0x21) {
          if ((short)camera < -0x20) {
            camera._0_2_ = -0x20;
          }
        }
        else {
          camera._0_2_ = 0x20;
        }
        if (camera._2_2_ < 0xed) {
          if (camera._2_2_ < -0xbc) {
            camera._2_2_ = -0xbc;
          }
        }
        else {
          camera._2_2_ = 0xec;
        }
      }
    }
    else {
      camera._0_2_ = dword_ed6f0;
      camera._2_2_ = dword_ed6f4;
      if (dword_ed6f0 < 0x21) {
        if (dword_ed6f0 < -0x20) {
          camera._0_2_ = -0x20;
        }
      }
      else {
        camera._0_2_ = 0x20;
      }
      if (dword_ed6f4 < 0xed) {
        if (dword_ed6f4 < -0xbc) {
          camera._2_2_ = -0xbc;
        }
      }
      else {
        camera._2_2_ = 0xec;
      }
      _dword_ed6f0 = (int)(short)camera;
      _dword_ed6f4 = (int)camera._2_2_;
    }
    dword_d8c7c = (short)camera + 0x20;
    if (0x40 < dword_d8c7c) {
      dword_d8c7c = 0x40;
    }
    if (dword_d8c7c < 0) {
      dword_d8c7c = 0;
    }
    dword_d8c74 = 0xec - camera._2_2_;
    if (0x1a8 < dword_d8c74) {
      dword_d8c74 = 0x1a8;
    }
    if (dword_d8c74 < 0) {
      dword_d8c74 = 0;
    }
    set_camera_offset(0,0);
    begin_frame();
    draw_rink(dword_d8c7c,dword_d8c74);
    iVar4 = (int)(short)dword_dd6ac + word_dd6b2 * 8;
    set_view_rect(iVar4,(int)_dword_dd6aa + _dword_dd6b0 * 8,iVar4 + 0x140);
    dword_d8c40 = 0;
    replay_draw_frame((int)(short)dword_d8c7c,(int)(short)dword_d8c74);
    if (dword_ed6dc < 0xa8) {
      if (dword_ed74c == -1) {
        dword_ed6ec = dword_ed74c;
        _dword_ed704 = (short)camera + dword_ed6e0 + -0xa0;
        _dword_ed708 = (camera._2_2_ - dword_ed6dc) + 0x54;
        draw_sprite_world(0x188,(int)(short)(dword_ed704 + 1),(int)(short)(dword_ed708 + 1),0,0);
      }
      else {
        draw_sprite_world(0x188,(int)(short)(*(short *)(&unk_e9f18 + dword_ed74c * 2) + 1),
                          (int)(short)(*(short *)(&unk_e9f3a + dword_ed74c * 2) + 1),0,1);
        if (dword_ed6ec != dword_ed74c) {
          dword_ed6e0 = ((*(int *)((int)&word_e9f14 + dword_ed74c * 2 + 2) >> 0x10) -
                        (int)(short)camera) + 0xa0;
          dword_ed6dc = ((int)camera._2_2_ -
                        (*(int *)((int)&word_e9f36 + dword_ed74c * 2 + 2) >> 0x10)) + 0x54;
          if (0xa7 < dword_ed6dc) {
            dword_ed6dc = 0xa7;
          }
          setmousepos(dword_ed6e0,dword_ed6dc);
          dword_ed6ec = dword_ed74c;
        }
      }
    }
    set_camera_offset(-(word_dd6b2 * 8 + (int)(short)dword_dd6ac),
                      -((int)_dword_dd6aa + _dword_dd6b0 * 8));
    present_frame();
    uVar5 = ticks_elapsed();
    local_28._0_2_ = (short)uVar5;
    local_28._2_2_ = (short)((uint)uVar5 >> 0x10);
  }
  sound_pause_all();
  _word_cd500 = 0xffff;
  camera._0_2_ = (short)local_20;
  camera._2_2_ = (short)uStack_1c;
  dword_d8c7c._2_2_ = sVar2 >> 0xf;
  dword_d8c74._0_2_ = local_24;
  dword_d8c74._2_2_ = local_24 >> 0xf;
  crowd_noise = CONCAT22(sVar1,0xffff);
  dword_ccc88 = (int)sVar1;
  dword_c66d4 = 1;
  dword_c66d0 = 1;
  dword_d8c7c._0_2_ = sVar2;
  getpalette(0,0x100,&palette_save);
  fade_palette_to(1,&palette_save,0x10);
  freemem(dword_ed6d8);
  setdefaultscreen();
  if (param_1 == 0) {
    set_video_mode(0x280,0x1e0);
  }
  return;
}


// ================================================================================================
// replay_button_at @ 0x7e8e5 [__watcall]
// ================================================================================================

undefined4 __watcall replay_button_at(int param_1,int unaff_EDX,int *unaff_EBX)

{
  int iVar1;
  
  __CHK(0x10);
  iVar1 = 0;
  while ((((param_1 + 5 < (int)(&unk_d1dc8)[iVar1 * 7] ||
           ((int)(&unk_d1dd0)[iVar1 * 7] < param_1 + 5)) ||
          (unaff_EDX < (int)(&unk_d1dcc)[iVar1 * 7])) || ((int)(&unk_d1dd4)[iVar1 * 7] < unaff_EDX))
        ) {
    iVar1 = iVar1 + 1;
    if (9 < iVar1) {
      return 0;
    }
  }
  *unaff_EBX = iVar1;
  return 1;
}


// ================================================================================================
// replay_sprite_at @ 0x7e93e [__watcall]
// ================================================================================================

int __watcall replay_sprite_at(int param_1,int unaff_EDX)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  __CHK(0x1c);
  iVar5 = -1;
  iVar2 = 10000;
  iVar1 = 0;
  do {
    if ((((iVar1 < 0xc) || (0xf < iVar1)) &&
        (iVar4 = (*(int *)((int)&word_e9f14 + iVar1 * 2 + 2) >> 0x10) - param_1,
        iVar3 = (*(int *)((int)&word_e9f36 + iVar1 * 2 + 2) >> 0x10) - unaff_EDX,
        iVar3 = iVar3 * iVar3 + iVar4 * iVar4, iVar3 < 0x65)) && (iVar3 < iVar2)) {
      iVar2 = iVar3;
      iVar5 = iVar1;
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 < 0x11);
  return iVar5;
}


// ================================================================================================
// replay_control_loop @ 0x7e9ac [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 __watcall replay_control_loop(int *param_1,undefined4 unaff_EDX)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  int extraout_ECX;
  int iVar5;
  int iVar6;
  int iVar7;
  uint local_28;
  uint local_24;
  int local_20;
  uint uStack_1c;
  
  __CHK(0x3c);
  iVar6 = dword_ed6dc;
  iVar7 = 0;
  local_24 = dword_ed754;
  local_20 = dword_ed6e0;
  uStack_1c = 0;
  do {
    iVar2 = event_queue_pop();
    if (iVar2 == 0) break;
    uStack_1c = (*ui_poll_callback)();
    if (0x13f < dword_ed6e0) {
      dword_ed6e0 = extraout_ECX;
    }
    if (199 < dword_ed6dc) {
      dword_ed6dc = 199;
    }
  } while ((uStack_1c & 2) == 0);
  if ((uStack_1c & 1) == 0) {
    if ((uStack_1c & 2) != 0) {
      dword_ed6fc = 0;
    }
  }
  else {
    dword_ed6fc = 1;
  }
  uVar3 = dword_ed6fc;
  if (dword_ed6fc != 0) {
    iVar2 = replay_button_at(dword_ed6e0,dword_ed6dc,&local_28);
    if ((iVar2 == 0) || ((dword_ed6f8 != 0 && (local_28 == 7)))) {
      uVar3 = 0;
    }
    else {
      uVar3 = 1 << ((byte)local_28 & 0x1f);
    }
  }
  if (dword_ed6dc < 0xa8) {
    _dword_ed704 = (short)camera + dword_ed6e0 + -0xa0;
    _dword_ed708 = (camera._2_2_ - dword_ed6dc) + 0x54;
  }
  local_28 = uVar3;
  if (uVar3 < 0x10) {
    if (uVar3 < 2) {
      if (uVar3 == 1) {
        dword_ed754 = dword_ed754 & 0x54 | 1;
        iVar7 = *param_1 * -4;
        goto LAB_0007eec9;
      }
      goto LAB_0007eca1;
    }
    if (uVar3 < 3) {
      if ((dword_ed754 & 2) == 0) {
        dword_ed6e8 = 0;
        iVar7 = -1;
        word_ed758 = 0xfff2;
      }
      else {
        dword_ed6e8 = dword_ed6e8 + *param_1;
        if (dword_ed6e8 < 5) {
          iVar7 = 0;
        }
        else {
          iVar7 = -1;
          dword_ed6e8 = dword_ed6e8 + -5;
        }
      }
      bVar1 = (byte)dword_ed754 & 0x40 | 6;
LAB_0007ec02:
      dword_ed754 = (uint)bVar1;
      goto LAB_0007eec9;
    }
    if (uVar3 < 4) {
LAB_0007eca1:
      if ((dword_ed6dc < 0xa8) &&
         (dword_ed74c = replay_sprite_at(_dword_ed704,_dword_ed708), (uStack_1c & 2) != 0)) {
        if (dword_ed74c == -1) {
          dword_ed70c = 1;
          dword_cd4fa._2_2_ = 0xffff;
          _dword_ed6f0 = _dword_ed704;
          _dword_ed6f4 = _dword_ed708;
          dword_ed6e0 = _dword_ed704;
          dword_ed6dc = _dword_ed708;
          if (_dword_ed704 < 0x21) {
            if (_dword_ed704 < -0x20) {
              dword_ed6e0 = -0x20;
            }
          }
          else {
            dword_ed6e0 = 0x20;
          }
          if (_dword_ed708 < 0xed) {
            if (_dword_ed708 < -0xbc) {
              dword_ed6dc = -0xbc;
            }
          }
          else {
            dword_ed6dc = 0xec;
          }
          dword_ed6e0 = (_dword_ed704 - dword_ed6e0) + 0xa0;
          dword_ed6dc = (dword_ed6dc - _dword_ed708) + 0x54;
          if (0xa7 < dword_ed6dc) {
            dword_ed6dc = 0xa7;
          }
          dword_ed6ec = dword_ed74c;
          setmousepos(dword_ed6e0,dword_ed6dc);
        }
        else {
          dword_ed70c = 0;
          dword_cd4fa._2_2_ = (undefined2)dword_ed74c;
          dword_ed6e0 = *(int *)((int)&word_e9f14 + dword_ed74c * 2 + 2) >> 0x10;
          dword_ed6dc = *(int *)((int)&word_e9f36 + dword_ed74c * 2 + 2) >> 0x10;
          if (dword_ed6e0 < 0x21) {
            if (dword_ed6e0 < -0x20) {
              dword_ed6e0 = -0x20;
            }
          }
          else {
            dword_ed6e0 = 0x20;
          }
          if (dword_ed6dc < 0xed) {
            if (dword_ed6dc < -0xbc) {
              dword_ed6dc = -0xbc;
            }
          }
          else {
            dword_ed6dc = 0xec;
          }
          dword_ed6e0 = ((*(int *)((int)&word_e9f14 + dword_ed74c * 2 + 2) >> 0x10) - dword_ed6e0) +
                        0xa0;
          dword_ed6dc = (dword_ed6dc - (*(int *)((int)&word_e9f36 + dword_ed74c * 2 + 2) >> 0x10)) +
                        0x54;
          if (0xa7 < dword_ed6dc) {
            dword_ed6dc = 0xa7;
          }
          setmousepos(dword_ed6e0,dword_ed6dc);
          dword_ed6ec = dword_ed74c;
        }
        dword_ed754 = dword_ed754 & 0x14;
      }
      uVar3 = dword_ed754;
      dword_ed754 = dword_ed754 & 0x54;
      if ((uVar3 & 0x10) != 0) goto LAB_0007eb85;
    }
    else {
      if (4 < uVar3) {
        if (uVar3 == 8) {
          if ((dword_ed754 & 8) == 0) {
            dword_ed6e8 = 0;
            iVar7 = 1;
            word_ed758 = 0xe;
          }
          else {
            dword_ed6e8 = dword_ed6e8 + *param_1;
            if (dword_ed6e8 < 5) {
              iVar7 = 0;
            }
            else {
              iVar7 = 1;
              dword_ed6e8 = dword_ed6e8 + -5;
            }
          }
          bVar1 = (byte)dword_ed754 & 0x40 | 0xc;
          goto LAB_0007ec02;
        }
        goto LAB_0007eca1;
      }
      dword_ed754 = dword_ed754 & 0x40 | 4;
    }
    iVar7 = 0;
  }
  else if (uVar3 < 0x11) {
    if ((dword_ed754 & 0x3f) != 0x10) {
      word_ed758 = 0;
    }
    dword_ed754 = (uint)((byte)dword_ed754 & 0x40 | 0x10);
LAB_0007eb85:
    iVar7 = *param_1;
  }
  else if (uVar3 < 0x40) {
    if (uVar3 != 0x20) goto LAB_0007eca1;
    dword_ed754 = dword_ed754 & 0x54 | 0x20;
    iVar7 = *param_1 << 2;
  }
  else {
    if (0x40 < uVar3) {
      if (0x7f < uVar3) {
        if (uVar3 < 0x81) {
          dword_ed754 = dword_ed754 & 0x40 | 0x84;
          goto LAB_0007eec9;
        }
        if (uVar3 == 0x100) {
          uVar4 = 0;
          goto LAB_0007e0f3;
        }
      }
      goto LAB_0007eca1;
    }
    dword_ed754 = dword_ed754 | 0x40;
    iVar7 = 0;
    dword_ed70c = 0;
    dword_ed74c = -1;
    dword_ed6ec = -1;
    dword_cd4fa._2_2_ = 0xffff;
  }
LAB_0007eec9:
  if (((local_20 != dword_ed6e0) || (iVar6 != dword_ed6dc)) || (local_24 != dword_ed754)) {
    if (local_24 == dword_ed754) {
      iVar2 = (*(int *)(pointer_shapes + 2) >> 0x10) + local_20;
      iVar6 = iVar6 + -0xa8;
      iVar5 = (*(int *)(pointer_shapes + 4) >> 0x10) + iVar6;
      if (local_20 < 0) {
        local_20 = 0;
      }
      else if (0x140 < local_20) {
        local_20 = 0x140;
      }
      if (iVar6 < 0) {
        iVar6 = 0;
      }
      else if (0x20 < iVar6) {
        iVar6 = 0x20;
      }
      if (iVar2 < 0) {
        iVar2 = 0;
      }
      else if (0x140 < iVar2) {
        iVar2 = 0x140;
      }
      if (iVar5 < 0) {
        iVar5 = 0;
      }
      else if (0x20 < iVar5) {
        iVar5 = 0x20;
      }
      setclip(local_20,iVar2,iVar6,iVar5);
    }
    sub_b500c(dword_ed6e4,0,0);
    if (local_24 == dword_ed754) {
      setclip(0,0x140,0,0x20);
    }
    local_28 = 0;
    do {
      if ((dword_ed754 & 1 << ((byte)local_28 & 0x1f)) != 0) {
        replay_draw_button(local_28);
      }
      local_28 = local_28 + 1;
    } while ((int)local_28 < 9);
    if (0xa7 < dword_ed6dc) {
      drawshape_remap(pointer_shapes,dword_ed6e0,dword_ed6dc + -0xa8);
    }
  }
  if ((dword_ed754 & 0x80) != 0) {
    dword_ed6fc = 0;
    replay_menu(0,dword_ed6e0,dword_ed6dc);
    event_queue_reset();
    dword_ed754 = 4;
    select_game_surface();
    setclip(0,0x140,0,0x20);
    blit_rle_frame(dword_ed6e4,0,0);
    replay_draw_button(2);
    drawshape_remap(pointer_shapes,dword_ed6e0,dword_ed6dc + -0xa8);
  }
  *param_1 = iVar7;
  uVar4 = 1;
LAB_0007e0f3:
  return CONCAT44(unaff_EDX,uVar4);
}


// ================================================================================================
// replay_menu @ 0x7f0af [__watcall]
// ================================================================================================

void __watcall replay_menu(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX)

{
  uint uVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 extraout_ECX;
  undefined *puVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  byte bVar11;
  undefined auStack_74 [64];
  undefined auStack_34 [32];
  uint uStack_14;
  
  bVar11 = 0;
  __CHK(0x94);
  setdefaultscreen();
  if ((((int)dword_c5403 < 0) || ((int)dword_c5407 < 0)) || (dword_c5403 == dword_c5407)) {
    settimeout(100);
    uVar1 = user2_team >> 0x10;
    if ((int)dword_c5403 < 0) {
      if (uVar1 == dword_c5407) {
        uVar1 = uVar1 ^ dword_c5407;
      }
      else {
        uVar1 = 1;
      }
    }
    else if (uVar1 == dword_c5403) {
      uVar1 = uVar1 ^ dword_c5403;
    }
    else {
      uVar1 = 1;
    }
    uStack_14 = replay_save_highlight(uVar1);
    if (uStack_14 != 0) {
      getfontstate(auStack_74);
      setfont(font_main);
      settimeout(500);
      set_dialog_colors(0x14,0x59,0x11,0x59,0);
      message_dialog(0,0,&off_d1f25,3,0,0,0,0,0);
      setfontstate(auStack_74);
      freemem(dword_ed6d8);
      puVar6 = install_path;
      if (byte_ed9ef != '\x01') {
        puVar6 = (undefined *)0x0;
      }
      make_path(auStack_34,puVar6,aGadget6,&aPPV);
      dword_ed6d8 = loadfile(auStack_34,0);
      dword_ed6e4 = locateshape(dword_ed6d8,&aGad1);
      waittimeout();
      sub_30f12();
      return;
    }
    waittimeout();
    return;
  }
  select_game_surface();
  setclip(0xc2,0xf0,0,0x20);
  sub_b500c(dword_ed6e4,0,0);
  replay_draw_button(7);
  setdefaultscreen();
  setclip(0,0x140,0,200);
  puVar2 = (undefined4 *)
           allocmem(aPointer_c3426,
                    (*(int *)((int)pointer_shapes + 2) >> 0x10) * ((int)pointer_shapes[1] >> 0x10) +
                    0x11,0x20);
  puVar9 = puVar2 + (uint)bVar11 * -2 + 1;
  puVar7 = pointer_shapes + (uint)bVar11 * -2 + 1;
  *puVar2 = *pointer_shapes;
  puVar10 = puVar9 + (uint)bVar11 * -2 + 1;
  puVar8 = puVar7 + (uint)bVar11 * -2 + 1;
  *puVar9 = *puVar7;
  *puVar10 = *puVar8;
  puVar10[(uint)bVar11 * -2 + 1] = puVar8[(uint)bVar11 * -2 + 1];
  *(undefined *)(puVar10 + (uint)bVar11 * -2 + 1 + (uint)bVar11 * -2 + 1) =
       *(undefined *)(puVar8 + (uint)bVar11 * -2 + 1 + (uint)bVar11 * -2 + 1);
  *(undefined2 *)(puVar2 + 1) = *(undefined2 *)(pointer_shapes + 1);
  *(undefined2 *)((int)puVar2 + 6) = *(undefined2 *)((int)pointer_shapes + 6);
  replay_save_dialog();
  dword_ed6d4 = 3;
  dword_ed6e0 = 0xee;
  dword_ed6dc = 0x8a;
  setmouselimits(0,0x4b,0x136,0x96);
  setmousepos(0xee,0x8a);
  grabshape(puVar2,0xee,0x8a);
  drawshape_remap(pointer_shapes,0xee,0x8a);
  event_queue_reset();
  uStack_14 = 0;
  while ((uStack_14 & 2) == 0) {
    do {
      iVar3 = event_queue_pop();
      iVar4 = dword_ed6dc;
    } while (iVar3 == 0);
    uStack_14 = (*ui_poll_callback)();
    if ((uStack_14 & 2) != 0) {
      if ((dword_ed6e0 < 0x4e) || (0xd8 < dword_ed6e0)) {
        uStack_14 = 0;
      }
      else if ((dword_ed6dc < 0x50) || (0x5e < dword_ed6dc)) {
        if ((dword_ed6dc < 0x61) || (0x6f < dword_ed6dc)) {
          if ((dword_ed6dc < 0x72) || (0x80 < dword_ed6dc)) {
            if ((dword_ed6dc < 0x83) || (0x91 < dword_ed6dc)) {
              uStack_14 = 0;
            }
            else {
              dword_ed6d4 = 3;
            }
          }
          else {
            dword_ed6d4 = 2;
          }
        }
        else {
          dword_ed6d4 = 1;
        }
      }
      else {
        dword_ed6d4 = 0;
      }
    }
    drawshape_remap(puVar2,extraout_ECX,iVar4);
    grabshape(puVar2,dword_ed6e0,dword_ed6dc);
    drawshape_remap(pointer_shapes,dword_ed6e0,dword_ed6dc);
  }
  settimeout(100);
  setclip(0,0x140,0,200);
  sub_b4fac(0x4e,dword_ed6d4 * 0x11 + 0x50,0x4e,dword_ed6d4 * 0x11 + 0x5e,0x10);
  iVar4 = dword_ed6d4 * 0x11 + 0x50;
  sub_b4fac(0x4e,iVar4,0xd8,iVar4,0x10);
  iVar4 = dword_ed6d4 * 0x11 + 0x5e;
  sub_b4fac(0x4f,iVar4,0xd8,iVar4,0x59);
  sub_b4fac(0xd8,dword_ed6d4 * 0x11 + 0x51,0xd8,dword_ed6d4 * 0x11 + 0x5e,0x59);
  putpixel(0xd8,dword_ed6d4 * 0x11 + 0x50,0x13);
  putpixel(0x4e,dword_ed6d4 * 0x11 + 0x5e,0x13);
  drawshape_remap(pointer_shapes,dword_ed6e0,dword_ed6dc);
  switch(dword_ed6d4) {
  case 0:
    uVar5 = 0;
    goto LAB_0007f59d;
  case 2:
    uStack_14 = replay_save_highlight(0);
    if (uStack_14 != 0) break;
  case 1:
    uVar5 = 1;
LAB_0007f59d:
    uStack_14 = replay_save_highlight(uVar5);
    break;
  case 3:
    uStack_14 = 0;
  }
  if (uStack_14 == 0) {
    waittimeout();
  }
  else {
    settimeout(500);
    set_dialog_colors(0x14,0x59,0x11,0x59,0);
    message_dialog(0,0,&off_d1f25,3,0,0,0,0,0);
    freemem(dword_ed6d8);
    puVar6 = install_path;
    if (byte_ed9ef != '\x01') {
      puVar6 = (undefined *)0x0;
    }
    make_path(auStack_34,puVar6,aGadget6,&aPPV);
    dword_ed6d8 = loadfile(auStack_34,0);
    dword_ed6e4 = locateshape(dword_ed6d8,&aGad1);
    waittimeout();
    sub_30f12();
  }
  sub_7fc12();
  dword_ed6e0 = unaff_EDX;
  dword_ed6dc = unaff_EBX;
  setmousepos(dword_ed6e0,dword_ed6dc);
  if (uStack_14 != 0) {
    settimeout(500);
    set_dialog_colors(0x14,0x59,0x11,0x59,0);
    setdefaultscreen();
    message_dialog(0xffffffff,0xffffffff,&off_d1f25,3,0,0,0,0,0);
    waittimeout();
    sub_30f12();
  }
  setclip(0,0x140,0,200);
  freemem(puVar2);
  setmouselimits(0,0,0x140,0xc1);
  return;
}


// ================================================================================================
// replay_save_dialog @ 0x7f724 [__watcall]
// ================================================================================================

void __watcall replay_save_dialog(void)

{
  int iVar1;
  char *pcVar2;
  int iVar3;
  undefined auStack_68 [64];
  char *local_28;
  char *local_24;
  undefined4 local_20;
  int iStack_1c;
  
  __CHK(0x80);
  local_28 = aBothTeams;
  local_24 = aNeitherTeams;
  getfontstate(auStack_68);
  setfont(dword_ed700);
  fillrect(0,0x4b,0x140,0x4c,0x14);
  sub_93000(1,0x4c,0x13e,0x95,9);
  sub_93000(2,0x4d,0x13d,0x96,0x10);
  iVar3 = 0x50;
  for (iStack_1c = 0; iStack_1c < 4; iStack_1c = iStack_1c + 1) {
    iVar1 = iVar3 + 0xe;
    sub_b4fac(0x4e,iVar3,0x4e,iVar1,0x59);
    local_20 = 0xd8;
    sub_b4fac(0x4e,iVar3,0xd8,iVar3,0x59);
    sub_b4fac(0x4f,iVar1,local_20,iVar1,0x10);
    sub_b4fac(local_20,iVar3 + 1,local_20,iVar1,0x10);
    putpixel(local_20,iVar3,0x13);
    putpixel(0x4e,iVar1,0x13);
    iVar3 = iVar3 + 0x11;
  }
  dword_d42a8 = 0x10;
  printstr_at(aSaveTo,0xe,0x6d);
  printstr_at(aHilightsReel,0xdf,0x6d);
  iVar3 = textwidth(&unk_dbc35,0x54);
  printstr_at(&unk_dbc35,(0x85 - iVar3) / 2 + 0x52);
  iVar3 = textwidth(&unk_dbf1d,0x65);
  printstr_at(&unk_dbf1d,(0x85 - iVar3) / 2 + 0x52);
  pcVar2 = local_28;
  iVar3 = textwidth(local_28,0x76);
  printstr_at(pcVar2,(0x85 - iVar3) / 2 + 0x52);
  iVar3 = textwidth(local_24,0x87);
  printstr_at(local_24,(0x85 - iVar3) / 2 + 0x52);
  dword_d42a8 = 0x59;
  printstr_at(aSaveTo,0xd,0x6c);
  printstr_at(aHilightsReel,0xde,0x6c);
  iVar3 = textwidth(&unk_dbc35,0x53);
  printstr_at(&unk_dbc35,(0x85 - iVar3) / 2 + 0x51);
  iVar3 = textwidth(&unk_dbf1d,100);
  printstr_at(&unk_dbf1d,(0x85 - iVar3) / 2 + 0x51);
  iVar3 = textwidth(pcVar2,0x75);
  printstr_at(pcVar2,(0x85 - iVar3) / 2 + 0x51);
  iVar3 = textwidth(local_24,0x86);
  printstr_at(local_24,(0x85 - iVar3) / 2 + 0x51);
  return;
}


// ================================================================================================
// replay_save_highlight @ 0x7fa10 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 __watcall replay_save_highlight(int param_1,undefined4 unaff_EDX)

{
  int iVar1;
  undefined4 uVar2;
  undefined auStack_68 [44];
  char acStack_3c [32];
  undefined local_1c [2];
  ushort local_1a;
  ushort local_18;
  ushort uStack_16;
  int iStack_14;
  
  __CHK(0x74);
  iVar1 = _dos_getdiskfree(0,local_1c);
  if (iVar1 != 0) {
    fatalerror(&aK1_c3444);
  }
  if ((uint)local_1a <
      (uint)((0x9652 / (ulonglong)uStack_16) / (ulonglong)(longlong)(int)(uint)local_18)) {
    dword_ed6f8 = 1;
    uVar2 = 1;
  }
  else {
    byte_e03c4 = byte_dc268;
    byte_e03c5 = byte_dc267;
    byte_e03c6 = user2_team._2_1_;
    byte_e03e3 = away_team_id;
    dword_e0400 = _period_num;
    dword_e0404 = hud_clock_min;
    dword_e0408 = hud_clock_sec;
    dword_e040c = hud_clock_tenths;
    word_e0410 = _action_flags;
    dword_e0412 = replay_write_ptr - (int)replay_buffer;
    iVar1 = 0;
    do {
      (&unk_e03c7)[iVar1] = (&unk_db3ad)[iVar1 * 0x27];
      (&unk_e03e4)[iVar1] = (&unk_db7f1)[iVar1 * 0x27];
      iVar1 = iVar1 + 1;
    } while (iVar1 < 0x1c);
    strcpy(acStack_3c,&league_dir);
    strcat(acStack_3c,&unk_c3447);
    strcat(acStack_3c,(char *)(&team_names + param_1 * 0xba));
    strcat(acStack_3c,(char *)&aHI);
    iVar1 = _dos_findfirst(acStack_3c,0,auStack_68);
    if (iVar1 == 0) {
      iVar1 = sub_1453e(acStack_3c,&iStack_14);
      if (iVar1 != 0) {
        fatalerror(aCanNotOpenSFile,acStack_3c);
      }
    }
    else {
      iVar1 = sub_14566(acStack_3c,&iStack_14);
      if (iVar1 != 0) {
        fatalerror(&aF1);
      }
    }
    lseek(iStack_14,0,2);
    iVar1 = file_write(iStack_14,&byte_e03c4,0xffffffff,0x9652);
    if (iVar1 != 0) {
      fatalerror(&aF3);
    }
    iVar1 = file_close(&iStack_14);
    if (iVar1 != 0) {
      fatalerror(&aF4);
    }
    uVar2 = 0;
  }
  return CONCAT44(unaff_EDX,uVar2);
}


// ================================================================================================
// sub_7fc12 @ 0x7fc12 [__watcall]
// ================================================================================================

void __watcall sub_7fc12(void)

{
  __CHK(4);
  dword_c7444 = dword_c7444 + 1000;
  dword_c7448 = dword_c7448 + 1000;
  return;
}


// ================================================================================================
// sub_7fc31 @ 0x7fc31 [__watcall]
// ================================================================================================

undefined4 __watcall sub_7fc31(int *param_1,int *unaff_EDX)

{
  undefined4 uVar1;
  
  __CHK(0x10);
  uVar1 = 0;
  if (*unaff_EDX < *param_1) {
    uVar1 = 1;
  }
  else if (*param_1 < *unaff_EDX) {
    uVar1 = 0xffffffff;
  }
  return uVar1;
}


// ================================================================================================
// sub_7fc5c @ 0x7fc5c [__watcall]
// ================================================================================================

undefined8 __watcall sub_7fc5c(int param_1,undefined4 unaff_EDX)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  __CHK(0x14);
  iVar3 = -1;
  iVar1 = sub_93284(param_1,&unk_c3470);
  *(undefined *)(param_1 + iVar1) = 0;
  iVar1 = 0;
  do {
    iVar2 = stricmp(param_1,(&team_abbrev)[iVar1]);
    if (iVar2 == 0) {
      iVar3 = iVar1;
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 < 0x1a);
  return CONCAT44(unaff_EDX,iVar3);
}


// ================================================================================================
// format_save_description @ 0x7fca2 [__watcall]
// ================================================================================================

void __watcall format_save_description(char *param_1,byte *unaff_EDX)

{
  __CHK(0x3c);
  sprintf(param_1,aDDSVsSPeriodDTime02d02d,(uint)*unaff_EDX,(uint)unaff_EDX[1],
          (&off_c54a9)[unaff_EDX[2]],(&off_c54a9)[unaff_EDX[0x1f]],*(undefined4 *)(unaff_EDX + 0x3c)
          ,*(undefined4 *)(unaff_EDX + 0x40),*(undefined4 *)(unaff_EDX + 0x44));
  return;
}


// ================================================================================================
// highlights_screen @ 0x7fcf8 [__watcall]
// ================================================================================================

int __watcall
highlights_screen(undefined4 param_1,int *unaff_EDX,undefined4 unaff_EBX,int unaff_ECX,int *param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined *apuStack_1dc [26];
  int local_174 [26];
  char acStack_10c [84];
  undefined auStack_b8 [76];
  undefined auStack_6c [30];
  undefined auStack_4e [14];
  undefined auStack_40 [28];
  undefined4 local_24;
  undefined local_20 [4];
  undefined local_1c [4];
  int iStack_18;
  int iStack_14;
  int iStack_10;
  
  __CHK(0x204);
  local_24 = 0xffffffff;
  iVar3 = 0;
  make_path(acStack_10c,unaff_EBX,&unk_c8113,&aHI_c812d);
  iVar1 = _dos_findfirst(acStack_10c,0,auStack_6c);
  if (iVar1 == 0) {
    local_174[0] = sub_7fc5c(auStack_4e);
    apuStack_1dc[0] = (&off_c54a9)[local_174[0]];
    iVar3 = 1;
    while (iVar1 = _dos_findnext(auStack_6c), iVar1 == 0) {
      iVar1 = sub_7fc5c(auStack_4e);
      local_174[iVar3] = iVar1;
      iVar3 = iVar3 + 1;
    }
  }
  if (iVar3 == 0) {
    getmouse(&iStack_18,local_1c,local_20);
    message_dialog(0xffffffff,0xffffffff,&off_d1f4b,1,0,0,local_1c,local_20,0xffffffff);
  }
  else {
    sub_9244c(local_174,iVar3,4,sub_7fc31);
    for (iStack_18 = 0; iStack_18 < iVar3; iStack_18 = iStack_18 + 1) {
      apuStack_1dc[iStack_18] = (&off_c54a9)[local_174[iStack_18]];
    }
    iVar1 = sub_303fb(apuStack_1dc,iVar3,aSelectATeam,2,0,auStack_40);
    if (-1 < iVar1) {
      make_path(param_1,0,(&team_abbrev)[local_174[iVar1]],&aHI_c812d);
      make_path(acStack_10c,unaff_EBX,param_1,0);
      iVar3 = filesize(acStack_10c);
      iVar1 = file_open_read(acStack_10c,&local_24);
      if (iVar1 == 0) {
        iVar3 = iVar3 / 0x9652;
        iStack_14 = allocmem(&aHLTL,iVar3 << 2,0x20);
        iStack_10 = allocmem(&aHLT,iVar3 * 0x51,0x20);
        if (unaff_ECX != 0) {
          iVar2 = allocmem(&aHLTS,iVar3,0x20);
          *param_5 = iVar2;
          for (iStack_18 = 0; iStack_18 < iVar3; iStack_18 = iStack_18 + 1) {
            *(undefined *)(*param_5 + iStack_18) = 0;
          }
        }
        iStack_18 = 0;
        while ((iStack_18 < iVar3 && (iVar1 == 0))) {
          iVar1 = file_read(local_24,auStack_b8,iStack_18 * 0x9652,0x4c);
          *(int *)(iStack_18 * 4 + iStack_14) = iStack_10 + iStack_18 * 0x51;
          format_save_description(acStack_10c,auStack_b8);
          strcpy((char *)(iStack_18 * 0x51 + iStack_10),acStack_10c);
          iStack_18 = iStack_18 + 1;
        }
        if (iVar1 == 0) {
          iVar2 = sub_303fb(iStack_14,iVar3,aSelectAHilight,2,unaff_ECX,*param_5);
          *unaff_EDX = iVar2;
          if (iVar2 < 0) {
            iVar1 = -1;
          }
          if (unaff_ECX != 0) {
            *unaff_EDX = iVar3;
          }
        }
        freemem(iStack_10);
        freemem(iStack_14);
      }
      file_close(&local_24);
      return iVar1;
    }
  }
  return -1;
}


// ================================================================================================
// sub_80075 @ 0x80075 [__watcall]
// ================================================================================================

undefined8 __watcall sub_80075(undefined4 param_1,undefined4 unaff_EDX)

{
  int iVar1;
  int extraout_EDX;
  int extraout_EDX_00;
  undefined auStack_44 [32];
  undefined auStack_24 [16];
  int local_14;
  undefined4 uStack_10;
  
  __CHK(0x4c);
  uStack_10 = 0xffffffff;
  set_dialog_colors(0xf9,0xfa,0xf8,0xfa,0);
  iVar1 = highlights_screen(auStack_24,&local_14,&league_dir,0,0);
  if (iVar1 == 0) {
    make_path(auStack_44,&league_dir,auStack_24,0);
    iVar1 = file_open_read(auStack_44,&uStack_10);
  }
  if (iVar1 == 0) {
    iVar1 = file_read(uStack_10,&byte_e03c4,local_14 * 0x9652,0x9652);
  }
  file_close(&uStack_10,iVar1);
  iVar1 = extraout_EDX;
  if (extraout_EDX == 0) {
    highlights_play();
    iVar1 = extraout_EDX_00;
  }
  return CONCAT44(unaff_EDX,iVar1);
}


// ================================================================================================
// highlights_play @ 0x8011c [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall highlights_play(void)

{
  int iVar1;
  undefined auStack_318 [768];
  
  __CHK(0x328);
  byte_dc268 = byte_e03c4;
  byte_dc267 = byte_e03c5;
  user2_team._2_2_ = (ushort)byte_e03c6;
  _away_team_id = (ushort)byte_e03e3;
  _period_num = dword_e0400;
  hud_clock_min = dword_e0404;
  hud_clock_sec = dword_e0408;
  hud_clock_tenths = dword_e040c;
  _action_flags = word_e0410;
  replay_write_ptr = replay_buffer + dword_e0412;
  iVar1 = 0;
  do {
    (&unk_db3ad)[iVar1 * 0x27] = (&unk_e03c7)[iVar1];
    (&unk_db7f1)[iVar1 * 0x27] = (&unk_e03e4)[iVar1];
    iVar1 = iVar1 + 1;
  } while (iVar1 < 0x1c);
  if ((sound_enabled != '\0') && (dword_c721d != 0)) {
    sound_fade(dword_d2431,3,100);
  }
  getpalette(0,0x100,auStack_318);
  fade_palette(1,auStack_318,0x10);
  if ((sound_enabled != '\0') && (dword_c721d != 0)) {
    do {
      iVar1 = sound_channel_status(ram0x000d242c >> 0x18,3);
    } while (iVar1 == 0);
    releasememblock(dword_c721d);
    dword_c721d = 0;
  }
  loading_screen();
  load_team_palettes((int)(short)user2_team._2_2_,(int)(short)_away_team_id,&unk_df314);
  load_music_banks();
  load_player_graphics();
  wait_sprite_fade();
  set_video_mode(0x140,200);
  if ((short)user2_team._2_2_ < 0x1a) {
    iVar1 = (int)(short)user2_team._2_2_;
  }
  else {
    iVar1 = 0xc;
  }
  load_rink(iVar1);
  instant_replay(0);
  getpalette(0,0x100,auStack_318);
  fade_palette(1,auStack_318,0x10);
  setfont(font_current_default);
  sub_1bab1();
  freemem(rinkend_bank);
  freemem(scoreboard_bank);
  freemem(numshp_bank);
  freemem(dword_ed700);
  sub_7dec8();
  sub_33727();
  event_queue_reset();
  return;
}


// ================================================================================================
// settings_toggles @ 0x8034b [__watcall]
// ================================================================================================

void __watcall settings_toggles(void)

{
  undefined *puVar1;
  undefined auStack_38 [32];
  
  __CHK(0x44);
  if (dword_d20a8 == 0) {
    puVar1 = (undefined *)0x0;
    if (byte_ed991 == '\x01') {
      puVar1 = install_path;
    }
    make_path(auStack_38,puVar1,aSettings,0);
    dword_d20a8 = loadshapes(auStack_38,0);
    dword_ed788 = locateshape(dword_d20a8,&aOn);
    dword_ed780 = locateshape(dword_d20a8,&aOff);
    dword_ed774 = locateshape(dword_d20a8,&aAcpt);
    dword_dd64c = locateshape(dword_d20a8,&aCanc);
    dword_ed78c = locateshape(dword_d20a8,&aNa01);
    dword_ed778 = locateshape(dword_d20a8,&aNa03);
    dword_ed76c = locateshape(dword_d20a8,&aNa05);
    dword_ed770 = locateshape(dword_d20a8,&aPg01);
    dword_ed77c = locateshape(dword_d20a8,&aPg03);
    dword_ed784 = locateshape(dword_d20a8,&aPg05);
    dword_ed768 = locateshape(dword_d20a8,&aPg07);
    dword_ed760 = locateshape(dword_d20a8,&aPl05);
    dword_ed764 = locateshape(dword_d20a8,&aPl10);
    dword_ed75c = locateshape(dword_d20a8,&aPl20);
  }
  return;
}


// ================================================================================================
// sub_8050f @ 0x8050f [__watcall]
// ================================================================================================

void __watcall
sub_8050f(int param_1,int unaff_EDX,undefined4 unaff_EBX,uint unaff_ECX,undefined4 param_5)

{
  char *pcVar1;
  undefined auStack_50 [64];
  
  __CHK(0x60);
  getfontstate(auStack_50);
  setfont(font_current_default);
  settextpos(param_5,0xff);
  switch(unaff_EBX) {
  case 3:
  case 5:
    param_1 = param_1 + 0x59;
    break;
  case 4:
  case 6:
    param_1 = param_1 + 0x51;
  }
  if (unaff_ECX == 0) {
    param_1 = param_1 + -0x41;
    pcVar1 = aExhibition_d20ac;
  }
  else if (unaff_ECX < 2) {
    param_1 = param_1 + -0x32;
    pcVar1 = aPlayoff_d20b7;
  }
  else {
    if (unaff_ECX != 2) goto LAB_000805b0;
    param_1 = param_1 + -0x2f;
    pcVar1 = aLeague_d20bf;
  }
  printstr_at(pcVar1,param_1,unaff_EDX + 0x16);
LAB_000805b0:
  setfontstate(auStack_50);
  return;
}


// ================================================================================================
// sub_805c4 @ 0x805c4 [__watcall]
// ================================================================================================

void __watcall sub_805c4(uint param_1)

{
  __CHK(0x10);
  if (param_1 == 0) {
    strcpy(aXxxxxxxxxxxSettings,aExhibition_d20ac);
    strcpy(aXxxxxxxxxxxSettings + 10,aSettings_d20d2);
    off_cecff = aSportsCentral;
    off_ced3f = aSportsCentral;
    return;
  }
  if (1 < param_1) {
    if (param_1 == 2) {
      strcpy(aXxxxxxxxxxxSettings,aShowLeague);
      strcpy(aXxxxxxxxxxxSettings + 0xb,aSettings_d20d2);
      off_ced3f = aReturn;
      off_cecff = aReturn;
      return;
    }
    return;
  }
  strcpy(aXxxxxxxxxxxSettings,aPlayoff_d20b7);
  strcpy(aXxxxxxxxxxxSettings + 7,aSettings_d20d2);
  off_cecff = aPlayoffTree;
  off_ced3f = aPlayoffTree;
  return;
}


// ================================================================================================
// sub_80682 @ 0x80682 [__watcall]
// ================================================================================================

void __watcall sub_80682(int param_1,int unaff_EDX,int unaff_EBX,int unaff_ECX,int param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  __CHK(0x38);
  fillrect(param_1,unaff_EDX,(unaff_EBX - param_1) + 1,(unaff_ECX - unaff_EDX) + 1,0x70);
  sub_b4fac(param_1,unaff_EDX,unaff_EBX,unaff_EDX,0x77);
  sub_b4fac(param_1,unaff_EDX,param_1,unaff_ECX,0x77);
  sub_b4fac(unaff_EBX,unaff_EDX,unaff_EBX,unaff_ECX,0x62);
  sub_b4fac(param_1,unaff_ECX,unaff_EBX,unaff_ECX,0x62);
  if (param_5 != 0) {
    iVar1 = unaff_EDX + 2;
    iVar2 = param_1 + 2;
    putpixel(iVar2,iVar1,0x77,iVar1,iVar2);
    unaff_EDX = unaff_EDX + 3;
    param_1 = param_1 + 3;
    putpixel(param_1,unaff_EDX,0x77);
    putpixel(param_1,iVar1,0x62);
    putpixel(iVar2,unaff_EDX,0x62);
    iVar3 = unaff_ECX + -2;
    putpixel(iVar2,iVar3,0x62,iVar1,iVar2,iVar3);
    unaff_ECX = unaff_ECX + -3;
    putpixel(param_1,unaff_ECX,0x62);
    putpixel(param_1,iVar3,0x77);
    putpixel(iVar2,unaff_ECX,0x77);
    iVar2 = unaff_EBX + -3;
    putpixel(iVar2,iVar1,0x77);
    unaff_EBX = unaff_EBX + -2;
    putpixel(unaff_EBX,unaff_EDX,0x77);
    putpixel(unaff_EBX,iVar1,0x62);
    putpixel(iVar2,unaff_EDX,0x62);
    putpixel(iVar2,iVar3,0x62);
    putpixel(unaff_EBX,unaff_ECX,0x62);
    putpixel(unaff_EBX,iVar3,0x77);
    putpixel(iVar2,unaff_ECX,0x77);
  }
  return;
}


// ================================================================================================
// locker_room_hub @ 0x80830 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 __watcall locker_room_hub(undefined4 param_1,undefined4 unaff_EDX)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  byte bVar7;
  undefined auStack_358 [768];
  undefined auStack_58 [64];
  
  bVar7 = 0;
  __CHK(0x368);
  if ((sound_enabled != '\0') && (dword_c721d != 0)) {
    sound_fade(dword_d2431,3,100);
  }
  getpalette(0,0x100,auStack_358);
  fade_palette(1,auStack_358,0x10);
  if ((sound_enabled != '\0') && (dword_c721d != 0)) {
    do {
      iVar1 = sound_channel_status(ram0x000d242c >> 0x18,3);
    } while (iVar1 == 0);
    releasememblock(dword_c721d);
    dword_c721d = 0;
  }
  loading_screen();
  getfontstate(auStack_58);
  dword_ed794 = (undefined4 *)allocmem(aHomeBck,0x1b811,0x20);
  dword_ed79c = (undefined4 *)allocmem(aVisBck,0x1a6f9,0x20);
  puVar5 = dword_ed794 + (uint)bVar7 * -2 + 1;
  puVar3 = pointer_shapes + (uint)bVar7 * -2 + 1;
  *dword_ed794 = *pointer_shapes;
  puVar6 = puVar5 + (uint)bVar7 * -2 + 1;
  puVar4 = puVar3 + (uint)bVar7 * -2 + 1;
  *puVar5 = *puVar3;
  *puVar6 = *puVar4;
  puVar6[(uint)bVar7 * -2 + 1] = puVar4[(uint)bVar7 * -2 + 1];
  *(undefined *)(puVar6 + (uint)bVar7 * -2 + 1 + (uint)bVar7 * -2 + 1) =
       *(undefined *)(puVar4 + (uint)bVar7 * -2 + 1 + (uint)bVar7 * -2 + 1);
  puVar5 = dword_ed79c + (uint)bVar7 * -2 + 1;
  puVar3 = pointer_shapes + (uint)bVar7 * -2 + 1;
  *dword_ed79c = *pointer_shapes;
  puVar6 = puVar5 + (uint)bVar7 * -2 + 1;
  puVar4 = puVar3 + (uint)bVar7 * -2 + 1;
  *puVar5 = *puVar3;
  *puVar6 = *puVar4;
  puVar6[(uint)bVar7 * -2 + 1] = puVar4[(uint)bVar7 * -2 + 1];
  *(undefined *)(puVar6 + (uint)bVar7 * -2 + 1 + (uint)bVar7 * -2 + 1) =
       *(undefined *)(puVar4 + (uint)bVar7 * -2 + 1 + (uint)bVar7 * -2 + 1);
  *(undefined2 *)(dword_ed794 + 1) = 0x140;
  *(undefined2 *)(dword_ed79c + 1) = 0x138;
  *(undefined2 *)((int)dword_ed794 + 6) = 0x160;
  *(undefined2 *)((int)dword_ed79c + 6) = 0x15b;
  dword_ed798 = (undefined4 *)allocmem(aHomeNameBck,0xa07,0x20);
  dword_ed7a0 = (undefined4 *)allocmem(aVisNameBck,0xa07,0x20);
  puVar5 = dword_ed798 + (uint)bVar7 * -2 + 1;
  puVar3 = pointer_shapes + (uint)bVar7 * -2 + 1;
  *dword_ed798 = *pointer_shapes;
  puVar6 = puVar5 + (uint)bVar7 * -2 + 1;
  puVar4 = puVar3 + (uint)bVar7 * -2 + 1;
  *puVar5 = *puVar3;
  *puVar6 = *puVar4;
  puVar6[(uint)bVar7 * -2 + 1] = puVar4[(uint)bVar7 * -2 + 1];
  *(undefined *)(puVar6 + (uint)bVar7 * -2 + 1 + (uint)bVar7 * -2 + 1) =
       *(undefined *)(puVar4 + (uint)bVar7 * -2 + 1 + (uint)bVar7 * -2 + 1);
  puVar5 = dword_ed7a0 + (uint)bVar7 * -2 + 1;
  puVar3 = pointer_shapes + (uint)bVar7 * -2 + 1;
  *dword_ed7a0 = *pointer_shapes;
  puVar6 = puVar5 + (uint)bVar7 * -2 + 1;
  puVar4 = puVar3 + (uint)bVar7 * -2 + 1;
  *puVar5 = *puVar3;
  *puVar6 = *puVar4;
  puVar6[(uint)bVar7 * -2 + 1] = puVar4[(uint)bVar7 * -2 + 1];
  *(undefined *)(puVar6 + (uint)bVar7 * -2 + 1 + (uint)bVar7 * -2 + 1) =
       *(undefined *)(puVar4 + (uint)bVar7 * -2 + 1 + (uint)bVar7 * -2 + 1);
  *(undefined2 *)(dword_ed798 + 1) = 0xaa;
  *(undefined2 *)(dword_ed7a0 + 1) = 0xaa;
  *(undefined2 *)((int)dword_ed798 + 6) = 0xf;
  *(undefined2 *)((int)dword_ed7a0 + 6) = 0xf;
  dword_ed790 = (undefined4 *)allocmem(aTitleBck,0x35c7,0x20);
  puVar5 = dword_ed790 + (uint)bVar7 * -2 + 1;
  puVar3 = pointer_shapes + (uint)bVar7 * -2 + 1;
  *dword_ed790 = *pointer_shapes;
  puVar6 = puVar5 + (uint)bVar7 * -2 + 1;
  puVar4 = puVar3 + (uint)bVar7 * -2 + 1;
  *puVar5 = *puVar3;
  *puVar6 = *puVar4;
  puVar6[(uint)bVar7 * -2 + 1] = puVar4[(uint)bVar7 * -2 + 1];
  *(undefined *)(puVar6 + (uint)bVar7 * -2 + 1 + (uint)bVar7 * -2 + 1) =
       *(undefined *)(puVar4 + (uint)bVar7 * -2 + 1 + (uint)bVar7 * -2 + 1);
  *(undefined2 *)(dword_ed790 + 1) = 0x226;
  *(undefined2 *)((int)dword_ed790 + 6) = 0x19;
  locker_room_screen();
  uVar2 = locker_room_menu();
  freemem(dword_ed790);
  freemem(dword_ed798);
  freemem(dword_ed7a0);
  freemem(dword_ed794);
  freemem(dword_ed79c);
  setfontstate(auStack_58);
  if (dword_c53fb == 0) {
    uVar2 = 2;
  }
  return CONCAT44(unaff_EDX,uVar2);
}


// ================================================================================================
// locker_room_screen @ 0x80aa4 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall locker_room_screen(void)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  char *pcVar4;
  undefined4 uVar5;
  int iVar6;
  undefined *puVar7;
  int iVar8;
  char acStack_36c [384];
  char acStack_1ec [192];
  char acStack_12c [192];
  undefined auStack_6c [64];
  char acStack_2c [16];
  uint uStack_1c;
  
  __CHK(900);
  setdefaultscreen();
  puVar7 = install_path;
  if (byte_ed8b5 != '\x01') {
    puVar7 = (undefined *)0x0;
  }
  make_path(auStack_6c,puVar7,aLockroom,0);
  uVar2 = loadshapes(auStack_6c,0);
  iVar3 = locateshape(uVar2,&aP01);
  uStack_1c = 0;
  do {
    pcVar4 = (char *)(uStack_1c + iVar3 + 0x10);
    if ((int)uStack_1c < 0x168) {
      cVar1 = *pcVar4;
      if (cVar1 < ';') {
        cVar1 = cVar1 + '\x05';
        goto LAB_00080b41;
      }
      acStack_36c[uStack_1c] = '?';
    }
    else {
      cVar1 = *pcVar4;
LAB_00080b41:
      acStack_36c[uStack_1c] = cVar1;
    }
    uStack_1c = uStack_1c + 1;
  } while ((int)uStack_1c < 0x180);
  wait_sprite_fade();
  uVar5 = locateshape(uVar2,&aRoom);
  sub_912c8(uVar5);
  freemem(uVar2);
  sub_80682(0,0x1a7,0x27f,0x1e0,1);
  uStack_1c = 2;
  do {
    sub_80682((&unk_d227c)[uStack_1c * 4],(&unk_d2280)[uStack_1c * 4],(&unk_d2284)[uStack_1c * 4],
              (&unk_d2288)[uStack_1c * 4],0);
    uStack_1c = uStack_1c + 1;
  } while ((int)uStack_1c < 8);
  grabshape(dword_ed790,0x2d,0x11);
  grabshape(dword_ed794,10,0x45);
  grabshape(dword_ed79c,0x146,0x4a);
  grabshape(dword_ed798,0x85,0x2c);
  grabshape(dword_ed7a0,0x152,0x2c);
  sprintf(acStack_2c,aJERSH,(&off_d21c0)[*(int *)(&unk_d20e0 + user2_team._2_2_ * 4)]);
  uStack_1c = user2_team._2_2_ * 2 + 0xa3;
  puVar7 = install_path;
  if (*(char *)(user2_team._2_2_ * 2 + 0xed86f) != '\x01') {
    puVar7 = (undefined *)0x0;
  }
  make_path(auStack_6c,puVar7,acStack_2c,0);
  uVar2 = loadshapes(auStack_6c,0);
  iVar3 = locateshape(uVar2,&aP01);
  uStack_1c = 0x240;
  do {
    cVar1 = *(char *)(uStack_1c + iVar3 + 0x10);
    if (cVar1 < ';') {
      acStack_36c[uStack_1c] = cVar1 + '\x05';
    }
    else {
      acStack_36c[uStack_1c] = '?';
    }
    uStack_1c = uStack_1c + 1;
  } while ((int)uStack_1c < 0x300);
  uVar5 = locateshape(uVar2,&a0000_c35dd);
  sub_912c8(uVar5);
  freemem(uVar2);
  sprintf(acStack_2c,aJERSV,(&off_d21c0)[*(int *)(&unk_d20e0 + _away_team_id * 4)]);
  uStack_1c = _away_team_id * 2 + 0xa4;
  puVar7 = install_path;
  if (*(char *)(_away_team_id * 2 + 0xed870) != '\x01') {
    puVar7 = (undefined *)0x0;
  }
  make_path(auStack_6c,puVar7,acStack_2c,0);
  uVar2 = loadshapes(auStack_6c,0);
  iVar3 = locateshape(uVar2,&aP01);
  uStack_1c = 0x180;
  do {
    cVar1 = *(char *)(uStack_1c + iVar3 + 0x10);
    if (cVar1 < ';') {
      acStack_36c[uStack_1c] = cVar1 + '\x05';
    }
    else {
      acStack_36c[uStack_1c] = '?';
    }
    uStack_1c = uStack_1c + 1;
  } while ((int)uStack_1c < 0x240);
  uVar5 = locateshape(uVar2,&a0000_c35dd);
  sub_912c8(uVar5);
  freemem(uVar2);
  set_text_colors(0x77,0x62);
  uStack_1c = 2;
  do {
    fillrect((&unk_d227c)[uStack_1c * 4] + 1,(&unk_d2280)[uStack_1c * 4] + 1,
             ((&unk_d2284)[uStack_1c * 4] - (&unk_d227c)[uStack_1c * 4]) + -1,
             ((&unk_d2288)[uStack_1c * 4] - (&unk_d2280)[uStack_1c * 4]) + -1,0x70);
    uStack_1c = uStack_1c + 1;
  } while ((int)uStack_1c < 6);
  setfont(font_main);
  settextpos(0x77,0xff);
  if (dword_c53fb == 0) {
    iVar3 = 0x1c;
    uStack_1c = (*(int *)(&unk_d20e0 + user2_team._2_2_ * 4) + 0x1b) % 0x1c;
    if ((0x19 < (int)uStack_1c) && (uStack_1c == *(int *)(&unk_d20e0 + _away_team_id * 4))) {
      iVar6 = uStack_1c + 0x1b;
LAB_00080f57:
      uStack_1c = iVar6 % iVar3;
    }
  }
  else {
    iVar3 = 0x1a;
    uStack_1c = (*(int *)(&unk_d20e0 + user2_team._2_2_ * 4) + 0x19) % 0x1a;
    if (uStack_1c == *(int *)(&unk_d20e0 + _away_team_id * 4)) {
      iVar6 = uStack_1c + 0x19;
      goto LAB_00080f57;
    }
  }
  puVar7 = (&off_d21c0)[uStack_1c];
  iVar8 = dword_d22a0 + 3;
  iVar6 = dword_d229c + dword_d22a4;
  iVar3 = textwidth(puVar7);
  print_text_at(((iVar6 >> 1) - (iVar3 >> 1)) + 2,iVar8,puVar7);
  if (dword_c53fb == 0) {
    iVar6 = 0x1c;
    iVar3 = (*(int *)(&unk_d20e0 + user2_team._2_2_ * 4) + 1) % 0x1c;
    uStack_1c = iVar3;
    if ((0x19 < iVar3) && (iVar3 == *(int *)(&unk_d20e0 + _away_team_id * 4))) {
LAB_0008102c:
      uStack_1c = (iVar3 + 1) % iVar6;
    }
  }
  else {
    iVar3 = (int)user2_team._2_2_;
    uStack_1c = (*(int *)(&unk_d20e0 + iVar3 * 4) + 1) % 0x1a;
    if (uStack_1c == *(int *)(&unk_d20e0 + _away_team_id * 4)) {
      iVar6 = 0x1a;
      goto LAB_0008102c;
    }
  }
  puVar7 = (&off_d21c0)[uStack_1c];
  iVar8 = dword_d22b0 + 3;
  iVar6 = dword_d22b4 + dword_d22ac;
  iVar3 = textwidth(puVar7);
  print_text_at(((iVar6 >> 1) - (iVar3 >> 1)) + 2,iVar8,puVar7);
  if (dword_c53fb == 0) {
    iVar6 = 0x1c;
    uStack_1c = (*(int *)(&unk_d20e0 + _away_team_id * 4) + 0x1b) % 0x1c;
    if ((0x19 < (int)uStack_1c) && (uStack_1c == *(int *)(&unk_d20e0 + user2_team._2_2_ * 4))) {
      iVar3 = uStack_1c + 0x1b;
LAB_0008110e:
      uStack_1c = iVar3 % iVar6;
    }
  }
  else {
    uStack_1c = (*(int *)(&unk_d20e0 + _away_team_id * 4) + 0x19) % 0x1a;
    if (uStack_1c == *(int *)(&unk_d20e0 + user2_team._2_2_ * 4)) {
      iVar3 = uStack_1c + 0x19;
      iVar6 = 0x1a;
      goto LAB_0008110e;
    }
  }
  puVar7 = (&off_d21c0)[uStack_1c];
  iVar8 = dword_d22c0 + 3;
  iVar6 = dword_d22c4 + dword_d22bc;
  iVar3 = textwidth(puVar7);
  print_text_at(((iVar6 >> 1) - (iVar3 >> 1)) + 2,iVar8,puVar7);
  if (dword_c53fb == 0) {
    iVar3 = 0x1c;
    uStack_1c = (*(int *)(&unk_d20e0 + _away_team_id * 4) + 1) % 0x1c;
    if (((int)uStack_1c < 0x1a) || (uStack_1c != *(int *)(&unk_d20e0 + user2_team._2_2_ * 4)))
    goto LAB_000811f6;
  }
  else {
    uStack_1c = (*(int *)(&unk_d20e0 + _away_team_id * 4) + 1) % 0x1a;
    if (uStack_1c != *(int *)(&unk_d20e0 + user2_team._2_2_ * 4)) goto LAB_000811f6;
    iVar3 = 0x1a;
  }
  uStack_1c = (int)(uStack_1c + 1) % iVar3;
LAB_000811f6:
  puVar7 = (&off_d21c0)[uStack_1c];
  iVar8 = dword_d22d0 + 3;
  iVar6 = dword_d22d4 + dword_d22cc;
  iVar3 = textwidth(puVar7);
  print_text_at(((iVar6 >> 1) - (iVar3 >> 1)) + 2,iVar8,puVar7);
  iVar3 = textwidth((&off_c54a9)[user2_team._2_2_]);
  uStack_1c = 0x12d - iVar3;
  sub_17636(uStack_1c,0x2c,(&off_c54a9)[user2_team._2_2_]);
  sub_17636(0x13a,0x2c,&aVs);
  sub_17636(0x154,0x2c,(&off_c54a9)[_away_team_id]);
  print_text_at(dword_d22dc + 0x12,dword_d22e0 + 3,aAccept);
  print_text_at(dword_d22ec + 0x12,dword_d22f0 + 3,aCancel_c35f3);
  iVar6 = dword_d22a8 + 5;
  iVar8 = dword_d229c + dword_d22b4;
  iVar3 = textwidth(aHomeTeam);
  print_text_at(((iVar8 >> 1) - (iVar3 >> 1)) + 2,iVar6,aHomeTeam);
  iVar6 = dword_d22c8 + 5;
  iVar8 = dword_d22bc + dword_d22d4;
  iVar3 = textwidth(aVisitingTeam);
  print_text_at(((iVar8 >> 1) - (iVar3 >> 1)) + 2,iVar6,aVisitingTeam);
  setfont(font_kaufm);
  if (dword_c53fb == 1) {
    uStack_1c = *(uint *)(&unk_c5519 + _away_team_id * 4) |
                *(uint *)(&unk_c5519 + user2_team._2_2_ * 4);
    pcVar4 = (&off_d2230)[*(int *)(&unk_d223c + uStack_1c * 4)];
    iVar3 = textwidth(pcVar4);
  }
  else {
    iVar3 = textwidth(aExhibitionGame);
    pcVar4 = aExhibitionGame;
  }
  sub_17636((0x280 - iVar3) / 2,0x12,pcVar4);
  setfont(font_main);
  if ((sound_enabled != '\0') && (dword_c721d == 0)) {
    puVar7 = (undefined *)0x0;
    if (byte_ed9a9 == '\x01') {
      puVar7 = install_path;
    }
    make_path(auStack_6c,puVar7,aJersey,&aIff_c3622);
    dword_c721d = loadsound(auStack_6c);
    if ((dword_c721d != 0) && (((byte)option_flags & 0x40) != 0)) {
      playsample(dword_c721d,dword_d2431,3,0x4c);
    }
  }
  fade_palette(0,acStack_36c);
  uStack_1c = 0;
  do {
    (&remap_home)[uStack_1c] = (undefined)uStack_1c;
    uStack_1c = uStack_1c + 1;
  } while ((int)uStack_1c < 0x100);
  byte_dc9e8 = 0x2c;
  byte_dc9e9 = 1;
  byte_dc9df = 0x2f;
  byte_dc9eb = 0x32;
  byte_dc9ec = 0x3a;
  byte_dca29 = 0x6d;
  byte_dca28 = 0x6e;
  byte_dca21 = 0x19;
  byte_dc9ee = 0x51;
  byte_dca38 = 0x18;
  byte_dc9dd = 0x7f;
  byte_dcad3 = 0x7c;
  byte_dcad4 = 0x7d;
  byte_dcad5 = 0x7e;
  byte_dcad6 = 0x7f;
  setremaptable(&remap_home);
  return;
}


// ================================================================================================
// sub_81520 @ 0x81520 [__watcall]
// ================================================================================================

undefined4 __watcall sub_81520(int param_1,int unaff_EDX,int *unaff_EBX)

{
  int iVar1;
  
  __CHK(0xc);
  iVar1 = 0;
  while ((((param_1 + 4 < (int)(&unk_d227c)[iVar1 * 4] ||
           ((int)(&unk_d2284)[iVar1 * 4] < param_1 + 4)) ||
          (unaff_EDX < (int)(&unk_d2280)[iVar1 * 4])) || ((int)(&unk_d2288)[iVar1 * 4] < unaff_EDX))
        ) {
    iVar1 = iVar1 + 1;
    if (7 < iVar1) {
      return 0;
    }
  }
  *unaff_EBX = iVar1;
  return 1;
}


// ================================================================================================
// draw_jerseys @ 0x8156f [__watcall]
// ================================================================================================

void __watcall draw_jerseys(int param_1,int unaff_EDX,int unaff_EBX,int unaff_ECX,int param_5)

{
  char cVar1;
  char *__format;
  undefined4 uVar2;
  int iVar3;
  undefined *puVar4;
  int iVar5;
  undefined4 uVar6;
  char acStack_12c [192];
  undefined auStack_6c [64];
  char acStack_2c [16];
  int local_1c;
  int local_18;
  
  __CHK(0x148);
  setdefaultscreen();
  if (param_1 == 0) {
    __format = aJERSH;
  }
  else {
    __format = aJERSV;
  }
  sprintf(acStack_2c,__format,(&off_d21c0)[unaff_EDX]);
  puVar4 = install_path;
  if (*(char *)((param_1 != 0) + 0xed86f + *(int *)(&unk_d20e0 + unaff_EDX * 4) * 2) != '\x01') {
    puVar4 = (undefined *)0x0;
  }
  make_path(auStack_6c,puVar4,acStack_2c,0);
  uVar2 = loadshapes(auStack_6c,0);
  iVar3 = locateshape(uVar2,&aP01);
  if (param_1 == 0) {
    iVar5 = 0;
    do {
      cVar1 = *(char *)(iVar3 + 0x10 + iVar5 + 0x240);
      if (cVar1 < ';') {
        acStack_12c[iVar5] = cVar1 + '\x05';
      }
      else {
        acStack_12c[iVar5] = '?';
      }
      iVar5 = iVar5 + 1;
    } while (iVar5 < 0xc0);
  }
  else {
    iVar5 = 0;
    do {
      cVar1 = *(char *)(iVar3 + 0x10 + iVar5 + 0x180);
      if (cVar1 < ';') {
        acStack_12c[iVar5] = cVar1 + '\x05';
      }
      else {
        acStack_12c[iVar5] = '?';
      }
      iVar5 = iVar5 + 1;
    } while (iVar5 < 0xc0);
  }
  if (param_1 == 0) {
    drawshape2(dword_ed794,10,0x45);
    drawshape2(dword_ed798,0x85,0x2c);
    uVar6 = 0xc0;
  }
  else {
    drawshape2(dword_ed79c,0x146,0x4a);
    drawshape2(dword_ed7a0,0x152,0x2c);
    uVar6 = 0x80;
  }
  setpalette(uVar6,0x40,acStack_12c);
  uVar6 = locateshape(uVar2,&a0000_c35dd);
  sub_912c8(uVar6);
  freemem(uVar2);
  settextpos(0x77,0xff);
  set_text_colors(0x77,0x62);
  if (dword_c53fb == 1) {
    drawshape2(dword_ed790,0x2d,0x11);
    setfont(font_kaufm);
    puVar4 = (&off_d2230)[*(int *)(&unk_d223c + unaff_EBX * 4)];
    iVar3 = textwidth(puVar4);
    sub_17636((0x280 - iVar3) / 2,0x12,puVar4);
    setfont(font_main);
  }
  if (dword_c53fb == 0) {
    iVar3 = 2;
    do {
      fillrect((&unk_d227c)[iVar3 * 4] + 1,(&unk_d2280)[iVar3 * 4] + 1,
               ((&unk_d2284)[iVar3 * 4] - (&unk_d227c)[iVar3 * 4]) + -1,
               ((&unk_d2288)[iVar3 * 4] - (&unk_d2280)[iVar3 * 4]) + -1,0x70);
      iVar3 = iVar3 + 1;
    } while (iVar3 < 6);
    iVar3 = (param_5 + 0x1b) % 0x1c;
    if ((0x19 < iVar3) && (iVar3 == unaff_ECX)) {
      iVar3 = (unaff_ECX + 0x1b) % 0x1c;
    }
    puVar4 = (&off_d21c0)[iVar3];
    local_1c = dword_d22c0 + 3;
    local_18 = dword_d22bc + dword_d22c4 >> 1;
    iVar3 = textwidth(puVar4);
    print_text_at((local_18 - (iVar3 >> 1)) + 2,local_1c,puVar4);
    iVar3 = (param_5 + 1) % 0x1c;
    if ((0x19 < iVar3) && (iVar3 == unaff_ECX)) {
      iVar3 = (unaff_ECX + 1) % 0x1c;
    }
    puVar4 = (&off_d21c0)[iVar3];
    local_1c = dword_d22d0 + 3;
    local_18 = dword_d22cc + dword_d22d4 >> 1;
    iVar3 = textwidth(puVar4);
    print_text_at((local_18 - (iVar3 >> 1)) + 2,local_1c,puVar4);
    sub_17636(0x154,0x2c,(&off_c54a9)[*(int *)(&unk_d2150 + param_5 * 4)]);
    iVar3 = (unaff_ECX + 0x1b) % 0x1c;
    if ((0x19 < iVar3) && (iVar3 == param_5)) {
      iVar3 = (param_5 + 0x1b) % 0x1c;
    }
    puVar4 = (&off_d21c0)[iVar3];
    local_1c = dword_d22a0 + 3;
    local_18 = dword_d229c + dword_d22a4 >> 1;
    iVar3 = textwidth(puVar4);
    print_text_at((local_18 - (iVar3 >> 1)) + 2,local_1c,puVar4);
    iVar3 = (unaff_ECX + 1) % 0x1c;
    if ((0x19 < iVar3) && (iVar3 == param_5)) {
      iVar3 = (param_5 + 1) % 0x1c;
    }
    puVar4 = (&off_d21c0)[iVar3];
    local_1c = dword_d22b0 + 3;
    local_18 = dword_d22ac + dword_d22b4 >> 1;
    iVar3 = textwidth(puVar4);
    print_text_at((local_18 - (iVar3 >> 1)) + 2,local_1c,puVar4);
    iVar3 = textwidth((&off_c54a9)[*(int *)(&unk_d2150 + unaff_ECX * 4)]);
    puVar4 = (&off_c54a9)[*(int *)(&unk_d2150 + unaff_ECX * 4)];
  }
  else {
    iVar3 = 2;
    do {
      fillrect((&unk_d227c)[iVar3 * 4] + 1,(&unk_d2280)[iVar3 * 4] + 1,
               ((&unk_d2284)[iVar3 * 4] - (&unk_d227c)[iVar3 * 4]) + -1,
               ((&unk_d2288)[iVar3 * 4] - (&unk_d2280)[iVar3 * 4]) + -1,0x70);
      iVar3 = iVar3 + 1;
    } while (iVar3 < 6);
    iVar3 = (param_5 + 0x19) % 0x1a;
    if (iVar3 == unaff_ECX) {
      iVar3 = (unaff_ECX + 0x19) % 0x1a;
    }
    puVar4 = (&off_d21c0)[iVar3];
    local_1c = dword_d22c0 + 3;
    local_18 = dword_d22bc + dword_d22c4 >> 1;
    iVar3 = textwidth(puVar4);
    print_text_at((local_18 - (iVar3 >> 1)) + 2,local_1c,puVar4);
    iVar3 = (param_5 + 1) % 0x1a;
    if (iVar3 == unaff_ECX) {
      iVar3 = (unaff_ECX + 1) % 0x1a;
    }
    puVar4 = (&off_d21c0)[iVar3];
    local_1c = dword_d22d0 + 3;
    local_18 = dword_d22cc + dword_d22d4 >> 1;
    iVar3 = textwidth(puVar4);
    print_text_at((local_18 - (iVar3 >> 1)) + 2,local_1c,puVar4);
    sub_17636(0x154,0x2c,(&off_c54a9)[*(int *)(&unk_d2150 + param_5 * 4)]);
    iVar3 = (unaff_ECX + 0x19) % 0x1a;
    if (iVar3 == param_5) {
      iVar3 = (param_5 + 0x19) % 0x1a;
    }
    puVar4 = (&off_d21c0)[iVar3];
    local_1c = dword_d22a0 + 3;
    local_18 = dword_d229c + dword_d22a4 >> 1;
    iVar3 = textwidth(puVar4);
    print_text_at((local_18 - (iVar3 >> 1)) + 2,local_1c,puVar4);
    iVar3 = (unaff_ECX + 1) % 0x1a;
    if (iVar3 == param_5) {
      iVar3 = (param_5 + 1) % 0x1a;
    }
    puVar4 = (&off_d21c0)[iVar3];
    local_18 = dword_d22b0 + 3;
    local_1c = dword_d22ac + dword_d22b4 >> 1;
    iVar3 = textwidth(puVar4);
    print_text_at((local_1c - (iVar3 >> 1)) + 2,local_18,puVar4);
    iVar3 = textwidth((&off_c54a9)[*(int *)(&unk_d2150 + unaff_ECX * 4)]);
    puVar4 = (&off_c54a9)[*(int *)(&unk_d2150 + unaff_ECX * 4)];
  }
  sub_17636(0x12d - iVar3,0x2c,puVar4);
  return;
}


// ================================================================================================
// locker_room_menu @ 0x81c4e [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 __watcall locker_room_menu(undefined4 param_1,undefined4 unaff_EDX)

{
  char *pcVar1;
  ulonglong uVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 extraout_EDX;
  undefined4 ******ppppppuVar6;
  int iVar7;
  uint uVar8;
  undefined4 ******ppppppuVar9;
  undefined4 ******ppppppuVar10;
  undefined4 ******ppppppuVar11;
  byte bVar12;
  ulonglong uVar13;
  undefined8 uVar14;
  undefined auStack_338 [768];
  undefined4 local_38;
  undefined4 *local_34;
  undefined4 *****local_30;
  int local_2c;
  undefined4 *****local_28;
  int local_24;
  undefined4 *****local_20;
  int iStack_1c;
  
  bVar12 = 0;
  __CHK(0x348);
  iVar5 = *(int *)(&unk_d20e0 + user2_team._2_2_ * 4);
  iStack_1c = *(int *)(&unk_d20e0 + _away_team_id * 4);
  getmouse(&local_34,&local_24,&local_28);
  local_2c = local_24;
  local_30 = local_28;
  setdefaultscreen();
  local_20 = (undefined4 *****)
             allocmem(aPointer_c362e,
                      (((int)pointer_shapes[1] >> 0x10) + 1) *
                      ((*(int *)((int)pointer_shapes + 2) >> 0x10) + 1) + 0x11,0x20);
  ppppppuVar10 = (undefined4 ******)local_20 + (uint)bVar12 * -2 + 1;
  ppppppuVar6 = pointer_shapes + (uint)bVar12 * -2 + 1;
  *local_20 = *pointer_shapes;
  ppppppuVar11 = ppppppuVar10 + (uint)bVar12 * -2 + 1;
  ppppppuVar9 = ppppppuVar6 + (uint)bVar12 * -2 + 1;
  *ppppppuVar10 = *ppppppuVar6;
  *ppppppuVar11 = *ppppppuVar9;
  ppppppuVar11[(uint)bVar12 * -2 + 1] = ppppppuVar9[(uint)bVar12 * -2 + 1];
  *(undefined *)(ppppppuVar11 + (uint)bVar12 * -2 + 1 + (uint)bVar12 * -2 + 1) =
       *(undefined *)(ppppppuVar9 + (uint)bVar12 * -2 + 1 + (uint)bVar12 * -2 + 1);
  *(short *)((undefined4 ******)local_20 + 1) = *(short *)(pointer_shapes + 1) + 1;
  *(short *)((int)local_20 + 6) = *(short *)((int)pointer_shapes + 6) + 1;
  grabshape(local_20,local_2c + -4,local_30);
  ppppppuVar6 = (undefined4 ******)local_30;
  drawshape_trans(pointer_shapes,local_2c + -4,local_30);
  uVar13 = event_queue_reset();
LAB_00081d69:
  local_34 = (undefined4 *)0x0;
  do {
    uVar14 = event_queue_pop((int)uVar13,(int)(uVar13 >> 0x20),ppppppuVar6);
    uVar2 = CONCAT44((int)((ulonglong)uVar14 >> 0x20),local_34);
    if ((int)uVar14 == 0) break;
    ppppppuVar6 = &local_30;
    uVar13 = (*ui_poll_callback)();
    local_34 = (undefined4 *)uVar13;
    uVar2 = uVar13;
  } while ((uVar13 & 6) == 0);
  local_34 = (undefined4 *)uVar2;
  uVar13 = CONCAT44((int)(uVar2 >> 0x20),local_30);
  if (((uVar2 & 2) == 0) && ((uVar2 & 4) == 0)) goto code_r0x00081db3;
  if ((uVar2 & 2) != 0) {
    drawshape(local_20,local_24 + -4,local_28);
    iVar3 = sub_81520(local_2c,local_30,&local_38);
    if (iVar3 == 0) goto switchD_00081ec1_caseD_8;
    switch(local_38) {
    case 0:
    case 3:
      if (dword_c53fb == 0) {
        iVar7 = 0x1c;
        iVar3 = (iVar5 + 1) % 0x1c;
        if (0x19 < iVar3) goto joined_r0x00081faf;
      }
      else {
        iVar7 = 0x1a;
        iVar3 = (iVar5 + 1) % 0x1a;
joined_r0x00081faf:
        if (iVar3 == iStack_1c) {
          iVar3 = (iStack_1c + 1) % iVar7;
        }
      }
      uVar8 = *(uint *)(&unk_c5519 + *(int *)(&unk_d2150 + iVar3 * 4) * 4) |
              *(uint *)(&unk_c5519 + *(int *)(&unk_d2150 + iStack_1c * 4) * 4);
      uVar4 = 0;
      iVar5 = iVar3;
      goto LAB_00081fe9;
    case 1:
    case 5:
      if (dword_c53fb == 0) {
        iVar3 = 0x1c;
        iStack_1c = (iStack_1c + 1) % 0x1c;
        if (0x19 < iStack_1c) goto joined_r0x0008212b;
      }
      else {
        iVar3 = 0x1a;
        iStack_1c = (iStack_1c + 1) % 0x1a;
joined_r0x0008212b:
        if (iVar5 == iStack_1c) {
          iStack_1c = (iStack_1c + 1) % iVar3;
        }
      }
      draw_jerseys(1,iStack_1c,
                   *(uint *)(&unk_c5519 + *(int *)(&unk_d2150 + iStack_1c * 4) * 4) |
                   *(uint *)(&unk_c5519 + *(int *)(&unk_d2150 + iVar5 * 4) * 4),iVar5,iStack_1c);
      event_queue_reset();
      break;
    case 2:
      if (dword_c53fb == 0) {
        iVar3 = 0x1c;
        iVar5 = (iVar5 + 0x1b) % 0x1c;
        if ((0x19 < iVar5) && (iVar5 == iStack_1c)) {
          iVar5 = iStack_1c + 0x1b;
LAB_00081f17:
          iVar5 = iVar5 % iVar3;
        }
      }
      else {
        iVar3 = 0x1a;
        iVar5 = (iVar5 + 0x19) % 0x1a;
        if (iVar5 == iStack_1c) {
          iVar5 = iStack_1c + 0x19;
          goto LAB_00081f17;
        }
      }
      draw_jerseys(0,iVar5,*(uint *)(&unk_c5519 + *(int *)(&unk_d2150 + iStack_1c * 4) * 4) |
                           *(uint *)(&unk_c5519 + *(int *)(&unk_d2150 + iVar5 * 4) * 4),iVar5,
                   iStack_1c);
      event_queue_reset();
      break;
    case 4:
      if (dword_c53fb == 0) {
        iVar3 = 0x1c;
        iStack_1c = (iStack_1c + 0x1b) % 0x1c;
        if ((0x19 < iStack_1c) && (iVar5 == iStack_1c)) {
          iStack_1c = iStack_1c + 0x1b;
LAB_000820a5:
          iStack_1c = iStack_1c % iVar3;
        }
      }
      else {
        iVar3 = 0x1a;
        iStack_1c = (iStack_1c + 0x19) % 0x1a;
        if (iVar5 == iStack_1c) {
          iStack_1c = iStack_1c + 0x19;
          goto LAB_000820a5;
        }
      }
      uVar8 = *(uint *)(&unk_c5519 + *(int *)(&unk_d2150 + iVar5 * 4) * 4) |
              *(uint *)(&unk_c5519 + *(int *)(&unk_d2150 + iStack_1c * 4) * 4);
      uVar4 = 1;
      iVar3 = iStack_1c;
LAB_00081fe9:
      draw_jerseys(uVar4,iVar3,uVar8,iVar5,iStack_1c);
      event_queue_reset();
      break;
    case 6:
      goto switchD_00081ec1_caseD_6;
    case 7:
      if ((sound_enabled != '\0') && (dword_c721d != 0)) {
        sound_fade(dword_d2431,3,100);
      }
      getpalette(0,0x100,auStack_338);
      fade_palette(1,auStack_338,0x10);
      freemem(local_20);
      if ((sound_enabled != '\0') && (dword_c721d != 0)) {
        do {
          iVar5 = sound_channel_status(ram0x000d242c >> 0x18,3);
        } while (iVar5 == 0);
        releasememblock(dword_c721d);
        dword_c721d = 0;
      }
      goto LAB_000823b3;
    default:
      goto switchD_00081ec1_caseD_8;
    }
    setmousepos(local_2c,local_30);
switchD_00081ec1_caseD_8:
    grabshape(local_20,local_2c + -4,local_30);
    ppppppuVar6 = pointer_shapes;
    goto LAB_00081e33;
  }
  if ((sound_enabled != '\0') && (dword_c721d != 0)) {
    sound_fade(dword_d2431,3,100);
  }
  getpalette(0,0x100,auStack_338);
  fade_palette(1,auStack_338,0x10);
  freemem(local_20);
  if ((sound_enabled != '\0') && (dword_c721d != 0)) {
    do {
      iVar5 = sound_channel_status(ram0x000d242c >> 0x18,3);
    } while (iVar5 == 0);
    releasememblock(dword_c721d);
    dword_c721d = 0;
  }
LAB_000823b3:
  uVar4 = 3;
LAB_00080a9d:
  return CONCAT44(unaff_EDX,uVar4);
code_r0x00081db3:
  if ((local_2c != local_24) || (local_30 != local_28)) {
    drawshape(local_20,local_24 + -4,local_28);
    ppppppuVar6 = (undefined4 ******)local_20;
    grabshape(local_20,local_2c + -4,local_30);
LAB_00081e33:
    drawshape_trans(pointer_shapes,local_2c + -4,local_30);
    uVar13 = CONCAT44(extraout_EDX,local_30);
    local_24 = local_2c;
    local_28 = local_30;
  }
  goto LAB_00081d69;
switchD_00081ec1_caseD_6:
  user2_team._2_2_ = *(short *)(&unk_d2150 + iVar5 * 4);
  _away_team_id = *(short *)(&unk_d2150 + iStack_1c * 4);
  if (dword_c53fb == 0) {
    pcVar1 = (&off_d21c0)[iVar5];
    if (pcVar1[2] == '\0') {
      strncpy(aGameLAAtMTL + 0xd,pcVar1,2);
      aGameLAAtMTL[0xf] = ' ';
    }
    else {
      strncpy(aGameLAAtMTL + 0xd,pcVar1,3);
    }
    pcVar1 = (&off_d21c0)[iStack_1c];
    if (pcVar1[2] == '\0') {
      strncpy(aGameLAAtMTL + 6,pcVar1,2);
      aGameLAAtMTL[8] = ' ';
    }
    else {
      strncpy(aGameLAAtMTL + 6,pcVar1,3);
    }
  }
  if (-1 < dword_c5403) {
    if (dword_c5413 == 0) {
      iVar5 = CONCAT22(user2_team._2_2_,(undefined2)user2_team);
    }
    else {
      iVar5 = CONCAT22(_away_team_id,user2_team._2_2_);
    }
    dword_c5403 = iVar5 >> 0x10;
  }
  if (-1 < dword_c5407) {
    if (dword_c5417 == 0) {
      iVar5 = CONCAT22(user2_team._2_2_,(undefined2)user2_team);
    }
    else {
      iVar5 = CONCAT22(_away_team_id,user2_team._2_2_);
    }
    dword_c5407 = iVar5 >> 0x10;
  }
  sub_8b92f();
  if ((sound_enabled != '\0') && (dword_c721d != 0)) {
    sound_fade(dword_d2431,3,100);
  }
  getpalette(0,0x100,auStack_338);
  fade_palette(1,auStack_338,0x10);
  freemem(local_20);
  if ((sound_enabled != '\0') && (dword_c721d != 0)) {
    do {
      iVar5 = sound_channel_status(ram0x000d242c >> 0x18,3);
    } while (iVar5 == 0);
    releasememblock(dword_c721d);
    dword_c721d = 0;
  }
  uVar4 = 0;
  goto LAB_00080a9d;
}


// ================================================================================================
// sub_8245a @ 0x8245a [__watcall]
// ================================================================================================

void __watcall sub_8245a(int *param_1)

{
  __CHK(0x28);
  sub_b4fac(*param_1 + 10,param_1[3] + 0x12,*param_1 + 10,param_1[1] + 0x13,0xf8);
  sub_b4fac(*param_1 + 10,param_1[1] + 0x13,param_1[2] + 9,param_1[1] + 0x13,0xf8);
  sub_b4fac(param_1[2] + 10,param_1[1] + 0x14,param_1[2] + 10,param_1[3] + 0x13,0xfa);
  sub_b4fac(param_1[2] + 10,param_1[3] + 0x13,*param_1 + 0xb,param_1[3] + 0x13,0xfa);
  return;
}


// ================================================================================================
// sub_824f8 @ 0x824f8 [__watcall]
// ================================================================================================

void __watcall sub_824f8(int *param_1)

{
  __CHK(0x28);
  sub_b4fac(*param_1 + 10,param_1[3] + 0x12,*param_1 + 10,param_1[1] + 0x13,0xfa);
  sub_b4fac(*param_1 + 10,param_1[1] + 0x13,param_1[2] + 9,param_1[1] + 0x13,0xfa);
  sub_b4fac(param_1[2] + 10,param_1[1] + 0x14,param_1[2] + 10,param_1[3] + 0x13,0xf8);
  sub_b4fac(param_1[2] + 10,param_1[3] + 0x13,*param_1 + 0xb,param_1[3] + 0x13,0xf8);
  return;
}


// ================================================================================================
// sub_82579 @ 0x82579 [__watcall]
// ================================================================================================

undefined4 __watcall sub_82579(void)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  byte bVar6;
  
  bVar6 = 0;
  __CHK(0x24);
  if ((sound_enabled == '\0') || (dword_c721d == 0)) {
    dword_d2435 = allocmem(&aTemp_c3638,320000,0);
  }
  puVar1 = (undefined4 *)allocmem(aBuffer,0x5f11,0);
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
  *(undefined2 *)(puVar1 + 1) = 0x80;
  *(undefined2 *)((int)puVar1 + 6) = 0xbe;
  grabshape(puVar1,10,0x13);
  sub_8261c();
  sound_card_menu_a();
  sound_setup_screen();
  drawshape(puVar1,10,0x13);
  freemem(puVar1);
  return 0;
}


// ================================================================================================
// sub_8261c @ 0x8261c [__watcall]
// ================================================================================================

void __watcall sub_8261c(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined *puVar3;
  undefined auStack_30 [32];
  
  __CHK(0x40);
  setdefaultscreen();
  puVar3 = install_path;
  if (byte_ed95d != '\x01') {
    puVar3 = (undefined *)0x0;
  }
  make_path(auStack_30,puVar3,aSound_c3644,0);
  uVar1 = loadshapes(auStack_30,0);
  uVar2 = locateshape(uVar1,&aDbx2,10,0x13);
  drawshape2_remap(uVar2);
  freemem(uVar1);
  return;
}


// ================================================================================================
// sound_card_menu_a @ 0x82690 [__watcall]
// ================================================================================================

void __watcall sound_card_menu_a(void)

{
  int iVar1;
  int extraout_EDX;
  int extraout_EDX_00;
  
  __CHK(0x20);
  dword_ed360 = dword_c541f;
  iVar1 = 0;
  do {
    if ((dword_ed360 & 1 << ((byte)iVar1 & 0x1f)) == 0) {
      sub_824f8(&dword_d23a3 + iVar1 * 4);
      iVar1 = extraout_EDX_00;
    }
    else {
      sub_8245a();
      iVar1 = extraout_EDX;
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 < 8);
  settextpos(0xf8,0xff);
  if (((byte)dword_c541b & 1) == 0) {
    printstr_at(aPCSpeaker,dword_d23a3 + 0x18,dword_d23a7 + 0x13);
  }
  if (((byte)dword_c541b & 2) == 0) {
    printstr_at(aSoundBlaster,DAT_000d23b3 + 0xe,DAT_000d23b7 + 0x13);
  }
  if (((byte)dword_c541b & 4) == 0) {
    printstr_at(aADLib,DAT_000d23c3 + 0x29,DAT_000d23c7 + 0x13);
  }
  if (((byte)dword_c541b & 8) == 0) {
    printstr_at(aMT32,DAT_000d23d3 + 0x28,DAT_000d23d7 + 0x13);
  }
  if (((byte)dword_c541b & 0x20) == 0) {
    printstr_at(aUltraSound,DAT_000d23f3 + 0x18,DAT_000d23f7 + 0x13);
  }
  return;
}


// ================================================================================================
// sub_827b3 @ 0x827b3 [__watcall]
// ================================================================================================

undefined4 __watcall sub_827b3(int param_1,int unaff_EDX,int *unaff_EBX)

{
  int iVar1;
  
  __CHK(0xc);
  iVar1 = 0;
  while ((((param_1 + -6 < (int)(&dword_d23a3)[iVar1 * 4] ||
           ((int)(&unk_d23ab)[iVar1 * 4] < param_1 + -6)) ||
          (unaff_EDX + -0x13 < (int)(&dword_d23a7)[iVar1 * 4])) ||
         ((int)(&unk_d23af)[iVar1 * 4] < unaff_EDX + -0x13))) {
    iVar1 = iVar1 + 1;
    if (7 < iVar1) {
      return 0;
    }
  }
  *unaff_EBX = iVar1;
  return 1;
}


// ================================================================================================
// sound_card_menu_b @ 0x82805 [__watcall]
// ================================================================================================

void __watcall sound_card_menu_b(void)

{
  int iVar1;
  int extraout_EDX;
  int extraout_EDX_00;
  
  __CHK(0x20);
  iVar1 = 0;
  do {
    if ((dword_ed360 & 1 << ((byte)iVar1 & 0x1f)) == 0) {
      sub_824f8(&dword_d23a3 + iVar1 * 4);
      iVar1 = extraout_EDX_00;
    }
    else {
      sub_8245a();
      iVar1 = extraout_EDX;
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 < 8);
  settextpos(0xf8,0xff);
  if (((byte)dword_c541b & 1) == 0) {
    printstr_at(aPCSpeaker,dword_d23a3 + 0x18,dword_d23a7 + 0x13);
  }
  if (((byte)dword_c541b & 2) == 0) {
    printstr_at(aSoundBlaster,DAT_000d23b3 + 0xe,DAT_000d23b7 + 0x13);
  }
  if (((byte)dword_c541b & 4) == 0) {
    printstr_at(aADLib,DAT_000d23c3 + 0x29,DAT_000d23c7 + 0x13);
  }
  if (((byte)dword_c541b & 8) == 0) {
    printstr_at(aMT32,DAT_000d23d3 + 0x28,DAT_000d23d7 + 0x13);
  }
  if (((byte)dword_c541b & 0x20) == 0) {
    printstr_at(aUltraSound,DAT_000d23f3 + 0x18,DAT_000d23f7 + 0x13);
  }
  return;
}


// ================================================================================================
// sound_setup_screen @ 0x8291e [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

longlong __watcall sound_setup_screen(undefined4 param_1,uint unaff_EDX)

{
  undefined4 *puVar1;
  int iVar2;
  undefined *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  bool bVar8;
  byte bVar9;
  undefined auStack_50 [32];
  uint local_30;
  uint local_2c;
  int local_28;
  int local_24;
  int local_20;
  int iStack_1c;
  
  bVar9 = 0;
  __CHK(0x60);
  puVar1 = (undefined4 *)
           allocmem(aPointer_c3680,
                    ((*(int *)((int)pointer_shapes + 2) >> 0x10) + 1) *
                    (((int)pointer_shapes[1] >> 0x10) + 1) + 0x11,0);
  puVar6 = puVar1 + (uint)bVar9 * -2 + 1;
  puVar4 = pointer_shapes + (uint)bVar9 * -2 + 1;
  *puVar1 = *pointer_shapes;
  puVar7 = puVar6 + (uint)bVar9 * -2 + 1;
  puVar5 = puVar4 + (uint)bVar9 * -2 + 1;
  *puVar6 = *puVar4;
  *puVar7 = *puVar5;
  puVar7[(uint)bVar9 * -2 + 1] = puVar5[(uint)bVar9 * -2 + 1];
  *(undefined *)(puVar7 + (uint)bVar9 * -2 + 1 + (uint)bVar9 * -2 + 1) =
       *(undefined *)(puVar5 + (uint)bVar9 * -2 + 1 + (uint)bVar9 * -2 + 1);
  *(short *)(puVar1 + 1) = *(short *)(pointer_shapes + 1) + 1;
  *(short *)((int)puVar1 + 6) = *(short *)((int)pointer_shapes + 6) + 1;
  if (dword_d2435 != 0) {
    freemem(dword_d2435);
    dword_d2435 = 0;
  }
  getmouse(&local_2c,&iStack_1c,&local_20);
  local_24 = iStack_1c;
  local_28 = local_20;
  setdefaultscreen();
  grabshape(puVar1,local_24 + -4,local_28);
  drawshape_remap(pointer_shapes,local_24 + -4,local_28);
  event_queue_reset();
LAB_00082a04:
  local_2c = 0;
  do {
    iVar2 = event_queue_pop();
    if (iVar2 == 0) break;
    local_2c = (*ui_poll_callback)();
  } while ((local_2c & 6) == 0);
  if (((local_2c & 2) == 0) && ((local_2c & 4) == 0)) goto code_r0x00082a3b;
  if ((local_2c & 2) == 0) {
    if ((local_2c & 4) == 0) goto LAB_00082a5b;
    drawshape(puVar1,iStack_1c + -4,local_20);
LAB_00082d45:
    freemem(puVar1);
LAB_00082d4e:
    return (ulonglong)unaff_EDX << 0x20;
  }
  drawshape(puVar1,iStack_1c + -4,local_20);
  iVar2 = sub_827b3(local_24,local_28,&local_30);
  if (iVar2 != 0) {
    local_30 = 1 << ((byte)local_30 & 0x1f);
    if (((dword_ed360 & local_30) == 0) && ((dword_c541b & local_30) != 0)) {
      if (local_30 < 0x10) {
        if (local_30 < 4) {
          if ((local_30 == 0) || (2 < local_30)) goto LAB_00082d07;
        }
        else if (4 < local_30) {
          bVar8 = local_30 == 8;
          goto LAB_00082b30;
        }
LAB_00082b55:
        dword_ed360 = local_30;
      }
      else {
        if (local_30 < 0x11) goto LAB_00082b55;
        if (local_30 < 0x40) {
          bVar8 = local_30 == 0x20;
LAB_00082b30:
          if (bVar8) goto LAB_00082b55;
        }
        else if (local_30 < 0x41) {
          sub_8245a(&unk_d2403);
          set_dialog_colors(0xf9,0xfa,0xf8,0xfa,0xf7);
          if ((sound_enabled != '\0') && (dword_c721d != 0)) {
            sound_fade(dword_d2431,3,100);
            do {
              iVar2 = sound_channel_status(ram0x000d242c >> 0x18,3);
            } while (iVar2 == 0);
            releasememblock(dword_c721d);
            dword_c721d = 0;
          }
          iVar2 = load_sound_config(dword_ed360);
          if (iVar2 != 0) {
            dword_c541f = dword_ed360;
            freemem(puVar1);
            if ((sound_enabled != '\0') && (dword_c721d == 0)) {
              puVar3 = install_path;
              if (byte_ed9a7 != '\x01') {
                puVar3 = (undefined *)0x0;
              }
              make_path(auStack_50,puVar3,aMaindesk_c368d,&aIff_c3688);
              dword_c721d = loadsound(auStack_50);
              if ((dword_c721d != 0) && (((byte)option_flags & 0x40) != 0)) {
                playsample(dword_c721d,dword_d2431,3,0x4c);
              }
            }
            if (sound_enabled == '\0') {
              option_flags._1_1_ = option_flags._1_1_ & 0xfe;
            }
            else {
              option_flags._1_1_ = option_flags._1_1_ | 1;
            }
            goto LAB_00082d4e;
          }
          dword_c541b = dword_c541b ^ dword_ed360;
          dword_ed360 = dword_c541f;
          if ((sound_enabled != '\0') && (dword_c721d == 0)) {
            puVar3 = install_path;
            if (byte_ed9a7 != '\x01') {
              puVar3 = (undefined *)0x0;
            }
            make_path(auStack_50,puVar3,aMaindesk_c368d,&aIff_c3688);
            dword_c721d = loadsound(auStack_50);
            if ((dword_c721d != 0) && (((byte)option_flags & 0x40) != 0)) {
              playsample(dword_c721d,dword_d2431,3,0x4c);
            }
          }
          sub_824f8(&unk_d2403);
        }
        else if (local_30 == 0x80) {
          sub_8245a(&aE_d2413);
          goto LAB_00082d45;
        }
      }
LAB_00082d07:
      sound_card_menu_b();
    }
  }
  grabshape(puVar1,local_24 + -4,local_28);
  goto LAB_00082a8f;
code_r0x00082a3b:
  if ((local_24 != iStack_1c) || (local_28 != local_20)) {
LAB_00082a5b:
    drawshape(puVar1,iStack_1c + -4,local_20);
    grabshape(puVar1,local_24 + -4,local_28);
LAB_00082a8f:
    drawshape_remap(pointer_shapes,local_24 + -4,local_28);
    iStack_1c = local_24;
    local_20 = local_28;
  }
  goto LAB_00082a04;
}


