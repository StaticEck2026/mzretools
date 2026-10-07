// Decompiled by Ghidra from hockey.elf (via ledisasm ELF export)
// This is machine generated pseudo-C meant as a reference for porting, it does not compile as is.
#include "prototypes.h"

// ================================================================================================
// debug_clear @ 0x938c8 [__watcall]
// ================================================================================================

void __watcall debug_clear(void)

{
  int iVar1;
  
  if (1 < dword_d4534) {
    iVar1 = 0;
    do {
      *(undefined4 *)(dword_d453c + iVar1) = 0;
      iVar1 = iVar1 + 4;
    } while (iVar1 < 4000);
  }
  return;
}


// ================================================================================================
// debug_set_top_row @ 0x938f4 [__cdecl]
// ================================================================================================

void debug_set_top_row(int param_1)

{
  if ((-1 < param_1) && (param_1 < 0x19)) {
    byte_d4544 = (undefined)param_1;
  }
  return;
}


// ================================================================================================
// debug_set_attr @ 0x93908 [__cdecl]
// ================================================================================================

void debug_set_attr(undefined param_1)

{
  byte_d4545 = param_1;
  return;
}


// ================================================================================================
// debug_set_tab @ 0x93914 [__cdecl]
// ================================================================================================

void debug_set_tab(int param_1)

{
  if (0 < param_1) {
    byte_d4546 = (undefined)param_1;
  }
  return;
}


// ================================================================================================
// debug_set_textbuf @ 0x93924 [__cdecl]
// ================================================================================================

void debug_set_textbuf(int param_1)

{
  dword_d453c = param_1 * 0x8000 + 0xb0000;
  return;
}


// ================================================================================================
// debug_openlog @ 0x93938 [__watcall]
// ================================================================================================

void __watcall debug_openlog(char *param_1)

{
  char cVar1;
  short sVar2;
  int iVar3;
  char *pcVar4;
  char *pcVar5;
  char *pcVar6;
  char local_c4 [136];
  undefined local_3c [20];
  undefined local_28 [20];
  
  pcVar5 = local_c4;
  if (dword_d4548 == (FILE *)0x0) {
    do {
      cVar1 = *param_1;
      *pcVar5 = cVar1;
      if (cVar1 == '\0') break;
      cVar1 = param_1[1];
      param_1 = param_1 + 2;
      pcVar5[1] = cVar1;
      pcVar5 = pcVar5 + 2;
    } while (cVar1 != '\0');
    iVar3 = -1;
    pcVar5 = local_c4;
    do {
      if (iVar3 == 0) break;
      iVar3 = iVar3 + -1;
      cVar1 = *pcVar5;
      pcVar5 = pcVar5 + 1;
    } while (cVar1 != '\0');
    sVar2 = ~(ushort)iVar3 - 1;
    if (0 < sVar2) {
      if ((local_c4[sVar2 + -1] != '\\') && (local_c4[sVar2 + -1] != ':')) {
        local_c4[sVar2] = '\\';
        local_c4[sVar2 + 1] = '\0';
      }
    }
    pcVar4 = &aDBUGTXT;
    iVar3 = -1;
    pcVar5 = local_c4;
    do {
      pcVar6 = pcVar5;
      if (iVar3 == 0) break;
      iVar3 = iVar3 + -1;
      pcVar6 = pcVar5 + 1;
      cVar1 = *pcVar5;
      pcVar5 = pcVar6;
    } while (cVar1 != '\0');
    pcVar6 = pcVar6 + -1;
    do {
      cVar1 = *pcVar4;
      *pcVar6 = cVar1;
      if (cVar1 == '\0') break;
      cVar1 = pcVar4[1];
      pcVar4 = pcVar4 + 2;
      pcVar6[1] = cVar1;
      pcVar6 = pcVar6 + 2;
    } while (cVar1 != '\0');
    debug_unique_logname(local_c4);
    dword_d4548 = fopen(local_c4,(char *)&aWt_c4040);
    if (dword_d4548 == (FILE *)0x0) {
      fclose((FILE *)0x0);
    }
    else {
      date_time_strings(local_3c,local_28);
      debug_logf(s_FILE___s_000c4043 + 1,local_c4);
      debug_logf(s_DATE___s_000c404e + 2,local_3c);
      debug_logf(s_mTIME___s_000c405a + 2,local_28);
    }
  }
  return;
}


// ================================================================================================
// debug_closelog @ 0x93a40 [__watcall]
// ================================================================================================

void __watcall debug_closelog(void)

{
  undefined auStack_34 [20];
  undefined local_20 [20];
  
  if (dword_d4548 != (FILE *)0x0) {
    date_time_strings(local_20,auStack_34);
    debug_logf(s_V_CLOSED_000c4067 + 1);
    debug_logf(s_DATE___s_000c404e + 2,local_20);
    debug_logf(s_i__TIME___s_000c4071 + 3,auStack_34);
    fclose(dword_d4548);
    dword_d4548 = (FILE *)0x0;
  }
  return;
}


// ================================================================================================
// debug_logf @ 0x93aa4 [__cdecl]
// ================================================================================================

void debug_logf(char *param_1)

{
  undefined *local_4;
  
  if ((1 < dword_d4534) && (dword_d4548 != (FILE *)0x0)) {
    local_4 = &stack0x00000008;
    vfprintf_alt(dword_d4548,param_1,&local_4);
  }
  return;
}


// ================================================================================================
// debug_printf_log @ 0x93ad8 [__watcall]
// ================================================================================================

void __watcall debug_printf_log(void)

{
  char *in_stack_00000004;
  char acStack_104 [256];
  undefined *local_4;
  
  if (1 < dword_d4534) {
    local_4 = &stack0x00000008;
    vsprintf(acStack_104,in_stack_00000004,&local_4);
    local_4 = (undefined *)0x0;
    if (dword_d4548 != (FILE *)0x0) {
      fputs(acStack_104,dword_d4548);
    }
    debug_puts();
  }
  return;
}


// ================================================================================================
// debug_unique_logname @ 0x93b34 [__watcall]
// ================================================================================================

undefined8 __watcall debug_unique_logname(char *param_1,undefined4 unaff_EDX)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  char *pcVar4;
  int iVar5;
  int iVar6;
  
  iVar6 = 0;
  cVar1 = *param_1;
  pcVar4 = param_1;
  while ((cVar1 != '?' && (*pcVar4 != '\0'))) {
    pcVar4 = pcVar4 + 1;
    iVar6 = iVar6 + 1;
    cVar1 = *pcVar4;
  }
  pcVar4 = param_1 + iVar6;
  if ((*pcVar4 == '\0') || (pcVar4[1] != '?')) {
    uVar2 = 0;
  }
  else {
    iVar5 = 0;
    do {
      *pcVar4 = (char)((longlong)iVar5 / 10) + '0';
      pcVar4[1] = (char)((longlong)iVar5 % 10) + '0';
      iVar3 = dos_findfirst_dta(param_1);
      if (iVar3 == 0) break;
      iVar5 = iVar5 + 1;
    } while (iVar5 < 100);
    if (99 < iVar5) {
      param_1 = param_1 + iVar6;
      param_1[1] = 'x';
      *param_1 = param_1[1];
      return CONCAT44(unaff_EDX,2);
    }
    uVar2 = 1;
  }
  return CONCAT44(unaff_EDX,uVar2);
}


// ================================================================================================
// date_time_strings @ 0x93bd4 [__watcall]
// ================================================================================================

void __watcall date_time_strings(char *param_1,undefined4 unaff_EDX)

{
  char *__s;
  byte local_18;
  byte local_17;
  ushort local_16;
  byte local_10;
  byte local_f;
  byte local_e;
  
  _dos_getdate(&local_18,unaff_EDX,param_1,unaff_EDX);
  _dos_gettime(&local_10);
  sprintf(param_1,a02d3s02d,(uint)local_18,(&dword_d4548)[local_17],(uint)local_16 % 100);
  sprintf(__s,a2d02d02d,(uint)local_10,(uint)local_f,(uint)local_e);
  return;
}


// ================================================================================================
// getkey_upper @ 0x93c88 [__watcall]
// ================================================================================================

void __watcall
getkey_upper(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  undefined4 uVar1;
  
  uVar1 = key_poll_translate();
  toupper_ascii(uVar1,unaff_EDX,unaff_ECX,unaff_EBX);
  return;
}


// ================================================================================================
// clearclip_reset @ 0x93ca0 [__watcall]
// ================================================================================================

void __watcall
clearclip_reset(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  clearclip(param_1,unaff_EDX,unaff_ECX,unaff_EBX);
  return_zero_9c5a8();
  return;
}


// ================================================================================================
// debug_monitor @ 0x93cb8 [__watcall]
// ================================================================================================

void __watcall debug_monitor(void)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined8 uVar7;
  undefined auStack_dc [96];
  undefined local_7c [64];
  char acStack_3c [12];
  undefined uStack_30;
  uint local_2c;
  int local_28;
  uint local_24;
  int local_20;
  undefined local_1c;
  
  local_24 = dword_d4594;
  save_screen_state(auStack_dc);
  getfontstate(local_7c);
  setfont(&unk_d45d8);
  local_1c = byte_d4544;
  debug_set_top_row(0);
  if (dword_d3024 == 0) {
    local_24 = 1;
  }
  dword_d457c = palette_closest(0);
  dword_d4580 = palette_closest(0xfcfcfc);
  dword_d4584 = palette_closest(0xfcfc54);
  dword_d4588 = palette_closest(0x80a8);
  dword_d458c = palette_closest(0xa80000);
  local_2c = (uint)(local_24 == 0);
  local_20 = 0;
  iVar4 = dword_d459c;
  iVar5 = dword_d45a0;
  do {
    if ((dword_d4594 != local_24) &&
       (dword_d4594 = local_24, dword_d459c = iVar4, dword_d45a0 = iVar5, local_2c == 0)) {
      local_2c = (uint)(local_24 == 0);
    }
    uVar1 = debug_memblock_count();
    local_28 = debug_memlist(iVar5,iVar4,uVar1);
    uVar7 = CONCAT44(iVar4 + 0x14,local_28);
    if (local_28 < iVar4 + 0x14) {
      uVar7 = CONCAT44(local_28,local_28);
    }
    do {
      uVar7 = getkey_upper((int)uVar7,(int)((ulonglong)uVar7 >> 0x20));
      iVar3 = (int)((ulonglong)uVar7 >> 0x20);
      iVar2 = (int)uVar7;
    } while (iVar2 == 0);
    iVar6 = iVar5;
    if (((iVar2 == 0x4900) && (iVar6 = iVar4, iVar5 == iVar4)) && (0 < iVar4)) {
      iVar4 = iVar4 + -0x15;
      iVar6 = iVar4;
    }
    iVar5 = iVar6;
    if (((iVar2 == 0x5100) && (iVar5 = iVar3, iVar6 == iVar3)) && (iVar5 = iVar6, iVar3 < local_28))
    {
      iVar4 = iVar4 + 0x15;
      iVar5 = iVar3 + 0x15;
    }
    if (((iVar2 == 0x4800) && (0 < iVar5)) && (iVar5 = iVar5 + -1, iVar5 < iVar4)) {
      iVar4 = iVar4 + -1;
    }
    if (((iVar2 == 0x5000) && (iVar5 < local_28)) && (iVar5 = iVar5 + 1, iVar3 < iVar5)) {
      iVar4 = iVar4 + 1;
    }
    iVar6 = iVar5;
    if ((iVar2 == 0x4700) && (iVar6 = iVar4, iVar5 == iVar4)) {
      iVar4 = 0;
      iVar6 = iVar4;
    }
    iVar5 = iVar6;
    if (((iVar2 == 0x4f00) && (iVar6 != local_28)) && (iVar5 = iVar3, iVar6 == iVar3)) {
      iVar4 = local_28 + -0x14;
      iVar5 = local_28;
    }
    if (iVar2 == 0x1b) {
      local_20 = 1;
    }
    if (iVar2 == 0xd) {
      debug_hexdump(dword_ede68,dword_ede84,local_24);
    }
    if (iVar2 == 0x43) {
      setdefaultscreen();
      clearclip_reset(dword_d457c);
    }
    if (iVar2 == 0x46) {
      dword_edab4 = 0;
    }
    if (iVar2 == 0x44) {
      dword_d4590._0_1_ = (byte)dword_d4590 ^ 1;
    }
    if (iVar2 == 0x42) {
      debug_memblock_window(dword_ede7c,dword_ede78,local_24);
    }
    if (iVar2 == 0x4d) {
      debug_clear();
    }
    if ((iVar2 == 0x50) || (iVar2 == 0x20)) {
      debug_memmap();
    }
    if (((((iVar2 == 0x53) || (iVar2 == 0x5b)) || (iVar2 == 0x5d)) ||
        ((iVar2 == 0x4b00 || (iVar2 == 0x4d00)))) && ((dword_ede7c & 0x8000) == 0)) {
      debug_shapes(dword_ede68,dword_ede84,local_24);
    }
    if (iVar2 == 0x56) {
      debug_screenshot();
    }
    if (iVar2 == 0x54) {
      debug_palette(local_24);
    }
    if (iVar2 == 0x57) {
      debug_shape_view(dword_ede68,local_24);
    }
    if (iVar2 == 0x41) {
      local_24 = local_24 ^ 1;
    }
    if (iVar2 == 9) {
      local_24 = local_24 ^ 1;
    }
    if ((iVar2 == 0x5300) && ((dword_ede7c & 0x8000) == 0)) {
      releasememblock(dword_ede80);
    }
    if ((iVar2 == 0x5200) && ((dword_ede7c & 0x8000) == 0)) {
      strncpy(acStack_3c,dword_ede64,0xc);
      uStack_30 = 0;
      setpurgeable(dword_ede80);
    }
    if (local_28 < iVar4) {
      iVar4 = iVar4 + -0x15;
      iVar5 = local_28;
    }
    else if (iVar4 < 0) {
      iVar4 = 0;
      iVar5 = 0;
    }
    if (local_28 < iVar5) {
      iVar5 = local_28;
    }
  } while (local_20 == 0);
  dword_d459c = iVar4;
  dword_d45a0 = iVar5;
  flushkeys_wrap();
  if (local_2c != 0) {
    setdefaultscreen();
    clearclip_reset(dword_d457c);
  }
  debug_set_top_row(local_1c);
  setfontstate(local_7c);
  restore_screen_state(auStack_dc);
  return;
}


// ================================================================================================
// debug_monitor_enter @ 0x93e38 [__watcall]
// ================================================================================================

void __watcall debug_monitor_enter(void)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined8 uVar7;
  undefined auStack_dc [96];
  undefined auStack_7c [64];
  char acStack_3c [12];
  undefined uStack_30;
  uint uStack_2c;
  int iStack_28;
  uint uStack_24;
  int iStack_20;
  undefined uStack_1c;
  
  dword_d4594 = 1;
  uStack_24 = 1;
  save_screen_state(auStack_dc);
  getfontstate(auStack_7c);
  setfont(&unk_d45d8);
  uStack_1c = byte_d4544;
  debug_set_top_row(0);
  if (dword_d3024 == 0) {
    uStack_24 = 1;
  }
  dword_d457c = palette_closest(0);
  dword_d4580 = palette_closest(0xfcfcfc);
  dword_d4584 = palette_closest(0xfcfc54);
  dword_d4588 = palette_closest(0x80a8);
  dword_d458c = palette_closest(0xa80000);
  uStack_2c = (uint)(uStack_24 == 0);
  iStack_20 = 0;
  iVar4 = dword_d459c;
  iVar5 = dword_d45a0;
  do {
    if ((dword_d4594 != uStack_24) &&
       (dword_d4594 = uStack_24, dword_d459c = iVar4, dword_d45a0 = iVar5, uStack_2c == 0)) {
      uStack_2c = (uint)(uStack_24 == 0);
    }
    uVar1 = debug_memblock_count();
    iStack_28 = debug_memlist(iVar5,iVar4,uVar1);
    uVar7 = CONCAT44(iVar4 + 0x14,iStack_28);
    if (iStack_28 < iVar4 + 0x14) {
      uVar7 = CONCAT44(iStack_28,iStack_28);
    }
    do {
      uVar7 = getkey_upper((int)uVar7,(int)((ulonglong)uVar7 >> 0x20));
      iVar3 = (int)((ulonglong)uVar7 >> 0x20);
      iVar2 = (int)uVar7;
    } while (iVar2 == 0);
    iVar6 = iVar5;
    if (((iVar2 == 0x4900) && (iVar6 = iVar4, iVar5 == iVar4)) && (0 < iVar4)) {
      iVar4 = iVar4 + -0x15;
      iVar6 = iVar4;
    }
    iVar5 = iVar6;
    if (((iVar2 == 0x5100) && (iVar5 = iVar3, iVar6 == iVar3)) && (iVar5 = iVar6, iVar3 < iStack_28)
       ) {
      iVar4 = iVar4 + 0x15;
      iVar5 = iVar3 + 0x15;
    }
    if (((iVar2 == 0x4800) && (0 < iVar5)) && (iVar5 = iVar5 + -1, iVar5 < iVar4)) {
      iVar4 = iVar4 + -1;
    }
    if (((iVar2 == 0x5000) && (iVar5 < iStack_28)) && (iVar5 = iVar5 + 1, iVar3 < iVar5)) {
      iVar4 = iVar4 + 1;
    }
    iVar6 = iVar5;
    if ((iVar2 == 0x4700) && (iVar6 = iVar4, iVar5 == iVar4)) {
      iVar4 = 0;
      iVar6 = iVar4;
    }
    iVar5 = iVar6;
    if (((iVar2 == 0x4f00) && (iVar6 != iStack_28)) && (iVar5 = iVar3, iVar6 == iVar3)) {
      iVar4 = iStack_28 + -0x14;
      iVar5 = iStack_28;
    }
    if (iVar2 == 0x1b) {
      iStack_20 = 1;
    }
    if (iVar2 == 0xd) {
      debug_hexdump(dword_ede68,dword_ede84,uStack_24);
    }
    if (iVar2 == 0x43) {
      setdefaultscreen();
      clearclip_reset(dword_d457c);
    }
    if (iVar2 == 0x46) {
      dword_edab4 = 0;
    }
    if (iVar2 == 0x44) {
      dword_d4590._0_1_ = (byte)dword_d4590 ^ 1;
    }
    if (iVar2 == 0x42) {
      debug_memblock_window(dword_ede7c,dword_ede78,uStack_24);
    }
    if (iVar2 == 0x4d) {
      debug_clear();
    }
    if ((iVar2 == 0x50) || (iVar2 == 0x20)) {
      debug_memmap();
    }
    if (((((iVar2 == 0x53) || (iVar2 == 0x5b)) || (iVar2 == 0x5d)) ||
        ((iVar2 == 0x4b00 || (iVar2 == 0x4d00)))) && ((dword_ede7c & 0x8000) == 0)) {
      debug_shapes(dword_ede68,dword_ede84,uStack_24);
    }
    if (iVar2 == 0x56) {
      debug_screenshot();
    }
    if (iVar2 == 0x54) {
      debug_palette(uStack_24);
    }
    if (iVar2 == 0x57) {
      debug_shape_view(dword_ede68,uStack_24);
    }
    if (iVar2 == 0x41) {
      uStack_24 = uStack_24 ^ 1;
    }
    if (iVar2 == 9) {
      uStack_24 = uStack_24 ^ 1;
    }
    if ((iVar2 == 0x5300) && ((dword_ede7c & 0x8000) == 0)) {
      releasememblock(dword_ede80);
    }
    if ((iVar2 == 0x5200) && ((dword_ede7c & 0x8000) == 0)) {
      strncpy(acStack_3c,dword_ede64,0xc);
      uStack_30 = 0;
      setpurgeable(dword_ede80);
    }
    if (iStack_28 < iVar4) {
      iVar4 = iVar4 + -0x15;
      iVar5 = iStack_28;
    }
    else if (iVar4 < 0) {
      iVar4 = 0;
      iVar5 = 0;
    }
    if (iStack_28 < iVar5) {
      iVar5 = iStack_28;
    }
  } while (iStack_20 == 0);
  dword_d459c = iVar4;
  dword_d45a0 = iVar5;
  flushkeys_wrap();
  if (uStack_2c != 0) {
    setdefaultscreen();
    clearclip_reset(dword_d457c);
  }
  debug_set_top_row(uStack_1c);
  setfontstate(auStack_7c);
  restore_screen_state(auStack_dc);
  return;
}


// ================================================================================================
// debug_memclass_bound @ 0x93e4c [__watcall]
// ================================================================================================

undefined8 __watcall debug_memclass_bound(int param_1,undefined4 unaff_EDX)

{
  if (param_1 == 1) {
    return CONCAT44(unaff_EDX,(&dword_eda08)[dword_d4598 * 5]);
  }
  return CONCAT44(unaff_EDX,(&dword_eda0c)[dword_d4598 * 5]);
}


// ================================================================================================
// debug_monitor_loop @ 0x93e79 [__watcall]
// ================================================================================================

void __watcall debug_monitor_loop(undefined4 param_1,undefined4 unaff_EDX)

{
  undefined4 uVar1;
  int iVar2;
  int unaff_EBP;
  undefined4 unaff_ESI;
  int iVar3;
  int unaff_EDI;
  int iVar4;
  int iVar5;
  undefined8 uVar6;
  undefined param_13;
  uint param_14;
  int param_15;
  uint param_16;
  int param_17;
  undefined param_18;
  
  uVar6 = CONCAT44(unaff_EDX,unaff_ESI);
  do {
    iVar2 = (int)((ulonglong)uVar6 >> 0x20);
    iVar4 = unaff_EDI;
    if (iVar2 < param_15) {
      unaff_EBP = unaff_EBP + 0x15;
      iVar4 = iVar2 + 0x15;
    }
    do {
      iVar2 = (int)((ulonglong)uVar6 >> 0x20);
      iVar3 = (int)uVar6;
      if (((iVar3 == 0x4800) && (0 < iVar4)) && (iVar4 = iVar4 + -1, iVar4 < unaff_EBP)) {
        unaff_EBP = unaff_EBP + -1;
      }
      if (((iVar3 == 0x5000) && (iVar4 < param_15)) && (iVar4 = iVar4 + 1, iVar2 < iVar4)) {
        unaff_EBP = unaff_EBP + 1;
      }
      iVar5 = iVar4;
      if ((iVar3 == 0x4700) && (iVar5 = unaff_EBP, iVar4 == unaff_EBP)) {
        unaff_EBP = 0;
        iVar5 = unaff_EBP;
      }
      iVar4 = iVar5;
      if (((iVar3 == 0x4f00) && (iVar5 != param_15)) && (iVar4 = iVar2, iVar5 == iVar2)) {
        unaff_EBP = param_15 + -0x14;
        iVar4 = param_15;
      }
      if (iVar3 == 0x1b) {
        param_17 = 1;
      }
      if (iVar3 == 0xd) {
        debug_hexdump(dword_ede68,dword_ede84,param_16);
      }
      if (iVar3 == 0x43) {
        setdefaultscreen();
        clearclip_reset(dword_d457c);
      }
      if (iVar3 == 0x46) {
        dword_edab4 = 0;
      }
      if (iVar3 == 0x44) {
        dword_d4590._0_1_ = (byte)dword_d4590 ^ 1;
      }
      if (iVar3 == 0x42) {
        debug_memblock_window(dword_ede7c,dword_ede78,param_16);
      }
      if (iVar3 == 0x4d) {
        debug_clear();
      }
      if ((iVar3 == 0x50) || (iVar3 == 0x20)) {
        debug_memmap();
      }
      if (((((iVar3 == 0x53) || (iVar3 == 0x5b)) || (iVar3 == 0x5d)) ||
          ((iVar3 == 0x4b00 || (iVar3 == 0x4d00)))) && ((dword_ede7c & 0x8000) == 0)) {
        debug_shapes(dword_ede68,dword_ede84,param_16);
      }
      if (iVar3 == 0x56) {
        debug_screenshot();
      }
      if (iVar3 == 0x54) {
        debug_palette(param_16);
      }
      if (iVar3 == 0x57) {
        debug_shape_view(dword_ede68,param_16);
      }
      if (iVar3 == 0x41) {
        param_16 = param_16 ^ 1;
      }
      if (iVar3 == 9) {
        param_16 = param_16 ^ 1;
      }
      if ((iVar3 == 0x5300) && ((dword_ede7c & 0x8000) == 0)) {
        releasememblock(dword_ede80);
      }
      if ((iVar3 == 0x5200) && ((dword_ede7c & 0x8000) == 0)) {
        strncpy(&stack0x000000a0,dword_ede64,0xc);
        param_13 = 0;
        setpurgeable(dword_ede80);
      }
      if (param_15 < unaff_EBP) {
        unaff_EBP = unaff_EBP + -0x15;
        iVar4 = param_15;
      }
      else if (unaff_EBP < 0) {
        unaff_EBP = 0;
        iVar4 = 0;
      }
      if (param_15 < iVar4) {
        iVar4 = param_15;
      }
      if (param_17 != 0) {
        dword_d459c = unaff_EBP;
        dword_d45a0 = iVar4;
        flushkeys_wrap();
        if (param_14 != 0) {
          setdefaultscreen();
          clearclip_reset(dword_d457c);
        }
        debug_set_top_row(param_18);
        setfontstate(&stack0x00000060);
        restore_screen_state(&stack0x00000000);
        return;
      }
      if ((dword_d4594 != param_16) &&
         (dword_d4594 = param_16, dword_d459c = unaff_EBP, dword_d45a0 = iVar4, param_14 == 0)) {
        param_14 = (uint)(param_16 == 0);
      }
      uVar1 = debug_memblock_count();
      param_15 = debug_memlist(iVar4,unaff_EBP,uVar1);
      uVar6 = CONCAT44(unaff_EBP + 0x14,param_15);
      if (param_15 < unaff_EBP + 0x14) {
        uVar6 = CONCAT44(param_15,param_15);
      }
      do {
        uVar6 = getkey_upper((int)uVar6,(int)((ulonglong)uVar6 >> 0x20));
        iVar3 = (int)((ulonglong)uVar6 >> 0x20);
        iVar2 = (int)uVar6;
      } while (iVar2 == 0);
      unaff_EDI = iVar4;
      if (((iVar2 == 0x4900) && (unaff_EDI = unaff_EBP, iVar4 == unaff_EBP)) && (0 < unaff_EBP)) {
        unaff_EBP = unaff_EBP + -0x15;
        unaff_EDI = unaff_EBP;
      }
      iVar4 = unaff_EDI;
    } while ((iVar2 != 0x5100) || (iVar4 = iVar3, unaff_EDI != iVar3));
  } while( true );
}


// ================================================================================================
// debug_memblock_count @ 0x940f4 [__watcall]
// ================================================================================================

undefined8 __watcall debug_memblock_count(undefined4 param_1,undefined4 unaff_EDX)

{
  int iVar1;
  undefined8 uVar2;
  
  for (uVar2 = debug_memclass_bound(1,0); iVar1 = (int)((ulonglong)uVar2 >> 0x20), (int)uVar2 != 0;
      uVar2 = CONCAT44(iVar1 + 1,*(undefined4 *)((int)uVar2 + 0x20))) {
  }
  return CONCAT44(unaff_EDX,iVar1 + 1);
}


// ================================================================================================
// debug_memlist_highlight @ 0x94114 [__watcall]
// ================================================================================================

undefined4 __watcall
debug_memlist_highlight
          (int param_1,int param_2,int param_3,int param_4,undefined4 param_5,undefined4 param_6,
          undefined4 param_7,undefined4 param_8)

{
  if (param_2 != 2) {
    if ((param_1 < param_3) || (param_3 + 0x15 <= param_1)) {
      return 1;
    }
    if (param_1 == param_4) {
      dword_ede70 = dword_d4580;
      dword_ede60 = 0x70;
      dword_ede68 = param_5;
      dword_ede84 = param_6;
      dword_ede7c = param_7;
      dword_ede78 = param_8;
      return 0;
    }
    dword_ede70 = dword_d457c;
    dword_ede60 = 7;
  }
  return 0;
}


// ================================================================================================
// debug_memlist @ 0x94188 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __watcall debug_memlist(int param_1,int unaff_EDX,int unaff_EBX,int unaff_ECX)

{
  char *pcVar1;
  int iVar2;
  undefined1 *__format;
  int iVar3;
  undefined4 *puVar4;
  int iVar5;
  byte bVar6;
  undefined4 local_164 [21];
  char local_110 [84];
  char local_bc [84];
  undefined local_68 [12];
  undefined local_5c [12];
  int local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  int local_40;
  undefined4 local_3c;
  int local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  int local_24;
  
  bVar6 = 0;
  debug_mem_totals(&local_30,&local_28,&local_2c,&local_34);
  if (dword_d4590 == 0) {
    pcVar1 = s_r_fCS__4_4x_DS__4_4x_HW___7u_Poo_000c4129 + 3;
  }
  else {
    pcVar1 = aCS44xDS44xHW66xPool66x;
  }
  sprintf(local_bc,pcVar1,CONCAT22(dword_d2f78._2_2_,(undefined2)dword_d2f78),
          CONCAT22(_dword_d2f7c,dword_d2f78._2_2_),dword_edab4,local_30);
  if (dword_d4590 == 0) {
    pcVar1 = s___Used___7u_Free___7u_Largst___7_000c417a + 2;
  }
  else {
    pcVar1 = aUsed66xFree66xLargst66x;
  }
  sprintf(local_110,pcVar1,local_28,local_2c,local_34);
  if (unaff_ECX == 0) {
    pcVar1 = aNAMESIZEADREND;
    puVar4 = local_164;
    for (iVar3 = 10; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar4 = *(undefined4 *)pcVar1;
      pcVar1 = pcVar1 + ((uint)bVar6 * -2 + 1) * 4;
      puVar4 = puVar4 + (uint)bVar6 * -2 + 1;
    }
    setdefaultscreen();
    settextpos(dword_d4584,dword_d457c);
    fillrect(0,0,dword_d3044,0,dword_d457c);
    printstr2_at(local_bc,0,0);
    return_zero_9c5a8();
    fillrect(0,8,dword_d3044,1,dword_d457c);
    printstr2_at(local_110,0,9);
    return_zero_9c5a8();
    fillrect(0,0x11,dword_d3044,1,dword_d457c);
    printstr2_at(local_164,0,0x12);
    return_zero_9c5a8();
    fillrect(0,0x1a,dword_d3044,2,dword_d457c);
    return_zero_9c5a8();
  }
  else {
    pcVar1 = aIDXNAMESIZEADRENDFLAG;
    puVar4 = local_164;
    for (iVar3 = 0xb; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar4 = *(undefined4 *)pcVar1;
      pcVar1 = pcVar1 + ((uint)bVar6 * -2 + 1) * 4;
      puVar4 = puVar4 + (uint)bVar6 * -2 + 1;
    }
    if (unaff_ECX == 1) {
      debug_printf(&aC_c41f0,0xb);
      debug_printf_at(0,0,a80s,local_bc);
      debug_printf_at(0,1,a80s,local_110);
      debug_printf_at(0,2,a80s,local_164);
      debug_printf_at(0,3,a80s,&unk_c41fc);
    }
    else if (unaff_ECX == 2) {
      fprintf(dword_ede74,&unk_c4200,local_bc);
      fprintf(dword_ede74,&unk_c4200,local_110);
      fprintf(dword_ede74,&unk_c4204,local_164);
    }
  }
  iVar3 = 0;
  iVar5 = 0;
  if (0 < unaff_EBX) {
    do {
      debug_memblock_info(iVar5,&local_3c,&local_50,&local_40,&local_44,&local_48,&local_4c,
                          &local_38);
      if (local_50 != local_38) {
        iVar2 = debug_memlist_highlight
                          (iVar3,unaff_ECX,unaff_EDX,param_1,local_38,local_50 - local_38,0xa000,0);
        if (iVar2 == 0) {
          sprint_hex(local_38,local_5c);
          sprint_hex(local_50,local_68);
          if (unaff_ECX == 0) {
            if (dword_d4590 == 0) {
              pcVar1 = s____SPACE__9d__8s__8s_000c4226 + 2;
            }
            else {
              pcVar1 = s_x_SPACE__9x__8s__8s_000c4209 + 3;
            }
            sprintf(local_bc,pcVar1,local_50 - local_38,local_5c,local_68);
            settextpos(dword_ede70,dword_d458c);
            printstr2_at(local_bc,0,(iVar3 - unaff_EDX) * 8 + 0x1c);
            return_zero_9c5a8();
          }
          else {
            if (dword_d4590 == 0) {
              pcVar1 = aSPACE7d66s66s;
            }
            else {
              pcVar1 = s_t___SPACE__6_6x__6_6s__6_6s_000c4241 + 3;
            }
            sprintf(local_bc,pcVar1,local_50 - local_38,local_5c,local_68);
            if (unaff_ECX == 1) {
              debug_set_attr(dword_ede60);
              debug_printf_at(0,(iVar3 - unaff_EDX) + 4,a80s,local_bc);
            }
            else if (unaff_ECX == 2) {
              fprintf(dword_ede74,&unk_c4200,local_bc);
            }
          }
        }
        iVar3 = iVar3 + 1;
      }
      iVar2 = debug_memlist_highlight
                        (iVar3,unaff_ECX,unaff_EDX,param_1,local_50,local_44,local_48,local_4c);
      if (iVar2 == 0) {
        if (iVar3 == param_1) {
          dword_ede80 = *(int *)(dword_ede6c + 0x24);
          dword_ede64 = dword_ede80 + 4;
        }
        sprint_hex(local_50,local_5c);
        sprint_hex(local_50 + local_40,local_68);
        if (unaff_ECX == 0) {
          if (dword_d4590 == 0) {
            __format = a1212s9d8s8s;
          }
          else {
            __format = a1212s9x8s8s;
          }
          sprintf(local_110,__format,local_3c,local_44,local_5c,local_68);
          settextpos(dword_d4588,dword_ede70);
          printstr2_at(local_110,0,(iVar3 - unaff_EDX) * 8 + 0x1c);
          return_zero_9c5a8();
        }
        else {
          if (dword_d4590 == 0) {
            pcVar1 = a33d1212s7d66s66s44x;
          }
          else {
            pcVar1 = a33d1212s66x66s66s44x;
          }
          sprintf(local_110,pcVar1,iVar5,local_3c,local_44,local_5c,local_68,local_48);
          if (unaff_ECX == 1) {
            debug_set_attr(dword_ede60);
            debug_printf_at(0,(iVar3 - unaff_EDX) + 4,a80s,local_110);
            debug_set_attr(7);
          }
          else if (unaff_ECX == 2) {
            fprintf(dword_ede74,&unk_c4200,local_110);
          }
        }
      }
      iVar3 = iVar3 + 1;
      iVar5 = iVar5 + 1;
    } while (iVar5 < unaff_EBX);
  }
  local_24 = unaff_EDX + 0x15;
  if (unaff_ECX == 0) {
    if (iVar3 < local_24) {
      iVar5 = (iVar3 - unaff_EDX) * 8 + 0x1c;
    }
    else {
      iVar5 = 0xc4;
    }
    setclip(0,dword_d3044,iVar5,dword_d3048);
    clearclip_reset(dword_d457c);
    setdefaultscreen();
  }
  else if (unaff_ECX == 1) {
    debug_set_attr(7);
    iVar2 = local_24 + 4;
    for (iVar5 = iVar3 + 4 + -unaff_EDX; iVar5 < -unaff_EDX + iVar2; iVar5 = iVar5 + 1) {
      debug_printf_at(0,iVar5,a80s,&unk_c41fc);
    }
  }
  return iVar3 + -1;
}


// ================================================================================================
// debug_mem_totals @ 0x9477c [__watcall]
// ================================================================================================

void __watcall debug_mem_totals(uint *param_1,uint *unaff_EDX,uint *unaff_EBX,uint *unaff_ECX)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  uint uVar4;
  
  piVar3 = (int *)debug_memclass_bound(1);
  piVar1 = (int *)piVar3[8];
  *unaff_ECX = 0;
  uVar4 = *unaff_ECX;
  *unaff_EBX = uVar4;
  *unaff_EDX = uVar4;
  *param_1 = uVar4;
  while (piVar2 = piVar1, piVar2 != (int *)0x0) {
    uVar4 = (*piVar2 - *piVar3) - piVar3[4];
    if ((*(byte *)((int)piVar2 + 0x19) & 0x80) == 0) {
      *unaff_EDX = *unaff_EDX + piVar2[4];
    }
    *unaff_EBX = *unaff_EBX + uVar4;
    if (*unaff_ECX < uVar4) {
      *unaff_ECX = uVar4;
    }
    piVar3 = piVar2;
    piVar1 = (int *)piVar2[8];
  }
  *param_1 = *unaff_EDX + *unaff_EBX;
  return;
}


// ================================================================================================
// debug_memblock_info @ 0x947d8 [__watcall]
// ================================================================================================

void __watcall
debug_memblock_info(int param_1,int *param_2,int *param_3,int *param_4,int *param_5,
                   undefined4 *param_6,undefined4 *param_7,int *param_8)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  
  puVar1 = dword_ede6c;
  if (param_1 == 0) {
    *param_2 = (int)(s_ACEMEM_MANAGER_000c4309 + 3);
    iVar2 = identity_8e3cc(dword_d2f80);
    *param_3 = iVar2;
    iVar3 = identity_8e3cc(*(undefined4 *)(&dword_eda08)[dword_d4598 * 5]);
    iVar2 = *param_3;
    *param_4 = iVar3 - iVar2;
    *param_5 = iVar3 - iVar2;
    *param_6 = 0x8000;
    *param_7 = 0;
    *param_8 = *param_3;
    dword_ede6c = (undefined4 *)(&dword_eda08)[dword_d4598 * 5];
  }
  else {
    *param_2 = (int)(dword_ede6c + 1);
    iVar2 = identity_8e3cc(*puVar1);
    *param_3 = iVar2;
    puVar1 = dword_ede6c;
    *param_4 = dword_ede6c[4];
    *param_5 = puVar1[5];
    *param_6 = puVar1[6];
    *param_7 = 0;
    if (param_1 < 2) {
      iVar2 = *param_3;
    }
    else {
      puVar1 = (undefined4 *)puVar1[9];
      iVar2 = identity_8e3cc(*puVar1);
      iVar2 = iVar2 + puVar1[4];
    }
    *param_8 = iVar2;
    dword_ede6c = (undefined4 *)dword_ede6c[8];
  }
  return;
}


// ================================================================================================
// sprint_hex @ 0x948d4 [__watcall]
// ================================================================================================

void __watcall sprint_hex(undefined4 param_1,char *unaff_EDX)

{
  sprintf(unaff_EDX,(char *)&aX_c4318,param_1);
  return;
}


// ================================================================================================
// debug_memblock_window @ 0x948e4 [__watcall]
// ================================================================================================

void __watcall debug_memblock_window(uint param_1,undefined4 unaff_EDX,int unaff_EBX)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  
  setdefaultscreen();
  fillbox_corners(0x2e,0x37,0x111,0xa4,dword_d4580);
  fillbox_corners(0x2f,0x38,0x110,0xa3,dword_d458c);
  fillrect(0x30,0x39,0xe0,0x6a,dword_d457c);
  settextpos(dword_d4584,dword_d457c);
  printf_at(0x38,0x3d,s_6_04_4X__0000_0000_0000_0000__000c431b + 1,param_1);
  return_zero_9c5a8();
  iVar2 = 0;
  uVar1 = param_1;
  iVar3 = 0xf8;
  do {
    if ((uVar1 & 1) != 0) {
      printstr2_at(&a1_c433c,iVar3,0x3d);
      return_zero_9c5a8();
    }
    uVar1 = (int)uVar1 >> 1;
    iVar4 = iVar3 + -8;
    if (iVar2 % 4 == 3) {
      iVar4 = iVar3 + -0x10;
    }
    iVar2 = iVar2 + 1;
    iVar3 = iVar4;
  } while (iVar2 < 0x10);
  settextpos(dword_d457c,dword_d458c);
  iVar3 = 0x4d;
  if ((param_1 & 0x8000) != 0) {
    drawline(0x50,0x4c,0x8f,0x4c,dword_d458c);
    printstr2_at(s___SYSTEM_000c433e + 2,0x50,0x4d);
    return_zero_9c5a8();
    iVar3 = 0x55;
  }
  if ((param_1 & 0x2000) != 0) {
    drawline(0x50,iVar3 + -1,0x87,iVar3 + -1,dword_d458c);
    printstr2_at(s__12_SPACE_000c4349 + 3,0x50,iVar3);
    return_zero_9c5a8();
    iVar3 = iVar3 + 8;
  }
  if ((param_1 & 0xa000) != 0) {
    iVar3 = iVar3 + 8;
  }
  settextpos(dword_d4580,dword_d457c);
  if ((param_1 & 0x20) == 0) {
    pcVar5 = aLOWMemoryBlock;
  }
  else {
    pcVar5 = aHIGHMemoryBlock;
  }
  printstr2_at(pcVar5,0x50,iVar3);
  return_zero_9c5a8();
  printstr2_at(s_6_6Conventional_memory_000c4379 + 3,0x50,iVar3 + 10);
  return_zero_9c5a8();
  iVar2 = iVar3 + 0x1e;
  if ((param_1 & 0x10) == 0) {
    pcVar5 = s__Non_Relocatable_block_000c43a2 + 2;
  }
  else {
    pcVar5 = aRelocatableBlock;
  }
  printstr2_at(pcVar5,0x50,iVar3 + 0x14);
  return_zero_9c5a8();
  if ((param_1 & 0x40) != 0) {
    printstr2_at(s_M_ALIGN_flag_is_set_000c43ba + 2,0x50,iVar2);
    return_zero_9c5a8();
    iVar2 = iVar3 + 0x28;
  }
  if ((param_1 & 0xf) != 0) {
    printf_at(0x50,iVar2,s__PRIORITY___1d_000c43ce + 2,param_1 & 7);
    return_zero_9c5a8();
    iVar2 = iVar2 + 10;
  }
  printf_at(0x50,iVar2,s_0Sequence___d_000c43de + 2,unaff_EDX);
  return_zero_9c5a8();
  if ((param_1 & 8) != 0) {
    printstr2_at(s_SYSBlock_is_PURGABLE_000c43ed + 3,0x50,iVar2 + 10);
    return_zero_9c5a8();
  }
  if (unaff_EBX == 0) {
    debug_pause_key();
  }
  return;
}


// ================================================================================================
// debug_hexdump @ 0x94b6c [__watcall]
// ================================================================================================

void __watcall debug_hexdump(int param_1,uint unaff_EDX)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  int iVar4;
  int iVar5;
  byte *pbVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  uint uVar11;
  uint uVar12;
  int iVar13;
  int iVar14;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 uStack_14;
  
  if (unaff_EDX == 0) {
    debug_clear();
  }
  else {
    local_20 = unaff_EDX >> 4;
    if ((unaff_EDX & 0xf) != 0) {
      local_20 = local_20 + 1;
    }
    iVar13 = 0;
    local_1c = 0;
    bVar2 = false;
    bVar3 = false;
    iVar9 = 0;
    uVar11 = 0;
    do {
      local_18 = local_20 - uVar11;
      if (0x19 < local_18) {
        local_18 = 0x19;
      }
      iVar14 = iVar13;
      if (local_18 <= iVar13) {
        iVar14 = local_18 + -1;
      }
      iVar4 = identity_8e3d4(uVar11 * 0x10 + param_1);
      debug_hexdump_rows(local_18,uVar11,iVar4,iVar9,iVar14,local_1c);
      return_zero_9c5a8();
      do {
        uStack_14 = key_poll();
        iVar5 = toupper_ascii(uStack_14);
      } while (iVar5 == 0);
      bVar1 = false;
      if (iVar5 == 0x1b) {
        if (local_1c == 0) {
          bVar3 = true;
        }
        else {
          local_1c = 0;
        }
      }
      uVar12 = uVar11;
      iVar13 = iVar14;
      if (iVar5 == 0x4900) {
        if (iVar14 == 0) {
          if (uVar11 != 0) {
            if (uVar11 < 0x1a) {
              uVar12 = 0;
            }
            else {
              uVar12 = uVar11 - 0x19;
            }
          }
        }
        else {
          iVar13 = 0;
        }
      }
      if (iVar5 == 0x5100) {
        if (iVar13 == local_18 + -1) {
          if (uVar12 + 0x19 < local_20) {
            uVar12 = uVar12 + 0x19;
          }
        }
        else {
          iVar13 = 0x18;
        }
      }
      if ((iVar5 == 0x4800) || (iVar8 = 0, iVar5 == 0x5000)) {
        iVar8 = iVar5;
      }
      if (iVar5 == 8) {
        iVar8 = 0x4b00;
      }
      iVar10 = iVar9;
      if (iVar5 == 0x4700) {
        if (iVar9 == 0) {
          if (iVar13 == 0) {
            if (uVar12 != 0) {
              uVar12 = 0;
            }
          }
          else {
            iVar13 = 0;
          }
        }
        else {
          iVar10 = 0;
        }
      }
      if (iVar5 == 0x4f00) {
        if (iVar10 == 0xf) {
          if (iVar13 == local_18 + -1) {
            if (uVar12 + 0x18 < local_20) {
              uVar12 = local_20 - 0x19;
            }
          }
          else {
            iVar13 = 0x18;
          }
        }
        else {
          iVar10 = 0xf;
        }
      }
      if (local_1c == 1) {
        *(char *)(iVar13 * 0x10 + iVar4 + iVar10) = (char)uStack_14;
        iVar8 = 0x4d00;
      }
      if (iVar5 == 0x4d) {
        local_1c = 1;
      }
      if ((0x2f < iVar5) && (iVar5 < 0x3a)) {
        uStack_14 = iVar5 + -0x30;
        bVar1 = true;
      }
      if ((0x40 < iVar5) && (iVar5 < 0x47)) {
        uStack_14._0_1_ = (char)iVar5 + -0x37;
        bVar1 = true;
      }
      if (bVar1) {
        pbVar6 = (byte *)(iVar4 + iVar10 + iVar13 * 0x10);
        if (bVar2) {
          if (bVar2) {
            *pbVar6 = (char)uStack_14 + (*pbVar6 & 0xf0);
            iVar8 = 0x4d00;
          }
        }
        else {
          uVar7 = CONCAT11(*pbVar6,(char)uStack_14) & 0xffff0fff;
          *pbVar6 = (char)(uVar7 >> 8) + (char)uVar7 * '\x10';
          bVar2 = true;
        }
      }
      if (iVar8 == 0x4b00) {
        iVar10 = iVar10 + -1;
        if (iVar10 < 0) {
          iVar10 = 0xf;
          iVar8 = 0x4800;
        }
      }
      else if ((iVar8 == 0x4d00) && (iVar10 = iVar10 + 1, 0xf < iVar10)) {
        iVar10 = 0;
        iVar8 = 0x5000;
      }
      if (iVar8 == 0x4800) {
        if (iVar13 < 1) {
          if (uVar12 != 0) {
            uVar12 = uVar12 - 1;
          }
        }
        else {
          iVar13 = iVar13 + -1;
        }
      }
      else if (iVar8 == 0x5000) {
        if (iVar13 < 0x18) {
          iVar13 = iVar13 + 1;
        }
        else if (uVar12 + 0x19 < local_20) {
          uVar12 = uVar12 + 1;
        }
      }
      if (((iVar10 != iVar9) || (iVar13 != iVar14)) || (uVar12 != uVar11)) {
        bVar2 = false;
      }
      iVar9 = iVar10;
      uVar11 = uVar12;
    } while (!bVar3);
  }
  return;
}


// ================================================================================================
// debug_hexdump_rows @ 0x94e34 [__watcall]
// ================================================================================================

void __watcall
debug_hexdump_rows(int param_1,int param_2,byte *unaff_EBX,uint unaff_ECX,int param_5,int param_6)

{
  int iVar1;
  byte *pbVar2;
  uint uVar3;
  int iVar4;
  int local_14;
  byte local_10;
  
  debug_printf(&aC_c41f0,0xb);
  local_14 = param_2 << 4;
  iVar1 = 0;
  if (0 < param_1) {
    do {
      debug_printf(a04x_c4404,local_14);
      uVar3 = 0;
      do {
        pbVar2 = unaff_EBX;
        if ((uVar3 == unaff_ECX) && (iVar1 == param_5)) {
          debug_set_attr(0x70);
        }
        debug_printf(&a02x,*pbVar2);
        if (((uVar3 == unaff_ECX) && (iVar1 == param_5)) && (param_6 != 0)) {
          debug_printf(&unk_c4414);
          debug_set_attr(7);
        }
        else {
          debug_set_attr(7);
          debug_printf(&asc_c4418);
        }
        if ((uVar3 & 3) == 3) {
          debug_printf(&asc_c4418);
        }
        uVar3 = uVar3 + 1;
        unaff_EBX = pbVar2 + 1;
      } while ((int)uVar3 < 0x10);
      debug_printf(&asc_c4418);
      iVar4 = 0;
      unaff_EBX = pbVar2 + -0xf;
      do {
        local_10 = *unaff_EBX & 0x7f;
        dword_ede60 = 7;
        if (local_10 < 0x20) {
          local_10 = 0x2e;
        }
        if ((*unaff_EBX & 0x80) != 0) {
          dword_ede60 = 0x70;
        }
        debug_set_attr(dword_ede60);
        debug_printf(&aC_c41f0,local_10);
        unaff_EBX = unaff_EBX + 1;
        iVar4 = iVar4 + 1;
      } while (iVar4 < 0x10);
      debug_set_attr(7);
      debug_printf(&asc_c441c);
      local_14 = local_14 + 0x10;
      iVar1 = iVar1 + 1;
    } while (iVar1 < param_1);
  }
  for (; iVar1 < 0x19; iVar1 = iVar1 + 1) {
    debug_printf(a80s,&unk_c41fc);
  }
  return;
}


// ================================================================================================
// debug_memlist_file @ 0x94fbc [__cdecl]
// ================================================================================================

undefined4 debug_memlist_file(FILE *param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined3 *puVar2;
  undefined auStack_34 [20];
  undefined local_20 [20];
  
  uVar1 = 0;
  if (param_1 != (FILE *)0x0) {
    dword_ede74 = param_1;
    date_time_strings2(local_20,auStack_34);
    fprintf(dword_ede74,&unk_c4200,unk_c40a0);
    fprintf(dword_ede74,s_ock__FILE___s_000c4421 + 3,param_2);
    fprintf(dword_ede74,aDATES_c4430,local_20);
    fprintf(dword_ede74,aTIMES_c443c,auStack_34);
    fprintf(dword_ede74,&unk_c4200,unk_c40a0);
    if (dword_d4590 == 0) {
      puVar2 = &aFF;
    }
    else {
      puVar2 = (undefined3 *)&aN_c4448;
    }
    fprintf(dword_ede74,s__hexmemdsp___O_s_000c444f + 1,puVar2);
    uVar1 = debug_memblock_count();
    debug_memlist(0,0,uVar1,2);
    uVar1 = 1;
  }
  return uVar1;
}


// ================================================================================================
// debug_memmap @ 0x950ac [__watcall]
// ================================================================================================

void __watcall debug_memmap(void)

{
  undefined4 uVar1;
  undefined2 local_54;
  undefined2 uStack_52;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined uStack_48;
  
  uStack_50 = DAT_000c4468;
  uStack_4c = DAT_000c446c;
  uStack_48 = DAT_000c4470;
  _local_54 = CONCAT22((short)((uint)aXxMMAPTXT >> 0x10),0x454d);
  debug_unique_filename(&local_54);
  uVar1 = dword_edab4;
  if (dword_d3024 != 0) {
    msgbox(&local_54,0x14);
  }
  dword_ede74 = fopen((char *)&local_54,(char *)&aW_c4474);
  if (dword_ede74 == (FILE *)0x0) {
    if (dword_d3024 != 0) {
      msgbox(s_seError_Dumping_Memory_Map_000c4476 + 2,0x14);
    }
  }
  else {
    dword_edab4 = uVar1;
    debug_memlist_file(dword_ede74,&local_54);
    fclose(dword_ede74);
    uVar1 = dword_edab4;
  }
  dword_edab4 = uVar1;
  return;
}


// ================================================================================================
// locateshape_wrap @ 0x95148 [__watcall]
// ================================================================================================

void __watcall
locateshape_wrap(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  locateshape(param_1,unaff_EDX,unaff_ECX,unaff_EBX);
  return;
}


// ================================================================================================
// debug_shapes @ 0x95158 [__watcall]
// ================================================================================================

void __watcall debug_shapes(int param_1,undefined4 param_2,undefined4 param_3,int unaff_ECX)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  char local_4c [4];
  undefined uStack_48;
  int iStack_44;
  int iStack_40;
  undefined local_3c [4];
  undefined local_38 [4];
  undefined local_34 [4];
  int *local_30;
  int *local_2c;
  undefined4 local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  uint uStack_14;
  int iStack_10;
  
  local_18 = param_1;
  shpi_header_fields(param_1,&local_28,&local_2c,&local_30,local_34,local_38,local_3c);
  local_1c = shapecount(local_28);
  uStack_48 = 0;
  if ((*local_2c < 0) || (*local_30 < 0)) {
    setdefaultscreen();
    clearclip_reset(dword_d457c);
    settextpos(dword_d4584,dword_d457c);
    return_zero_9c5a8();
    printstr2_centered(s_nceShape_file_is_invalid__Work_w_000c4491 + 3,0x60);
    return_zero_9c5a8();
    iVar1 = debug_pause_key();
    if (iVar1 != 0x59) {
      return;
    }
  }
  iVar3 = 0;
  iStack_44 = 0;
  local_20 = 0;
  iVar1 = 0;
  if (0 < local_1c) {
    do {
      shape_offset(local_28,iVar1,local_4c);
      if (local_4c[0] == '!') {
        iVar3 = iVar3 + 1;
      }
      puVar2 = (undefined4 *)locateshape_wrap(local_28,local_4c);
      if (((int)(char)*puVar2 & 0x80U) == 0) {
        local_20 = local_20 + 1;
      }
      else {
        iStack_44 = iStack_44 + 1;
      }
      iVar1 = iVar1 + 1;
    } while (iVar1 < local_1c);
  }
  debug_clear();
  debug_printf(s_2xNum____d____packed____d____not_000c44ba + 2,local_1c,iStack_44,local_20,iVar3);
  if (iVar3 == local_1c) {
    debug_printf(s_TIMThere_are_no_shapes_that_can_b_000c44f9 + 3);
  }
  else {
    if ((unaff_ECX == 0x5b) || (unaff_ECX == 0x4b00)) {
      iVar1 = local_1c + -1;
    }
    else {
      iVar1 = 0;
      unaff_ECX = 0x5d;
    }
    local_24 = 0;
    iStack_40 = local_1c + -1;
    do {
      do {
        shape_offset(local_28,iVar1,local_4c);
        puVar2 = (undefined4 *)getshape(local_28,iVar1);
        iVar3 = identity_8e3cc(puVar2);
        debug_printf(a44s05x,local_4c,iVar3 - local_18);
        settextpos(dword_d4584,dword_d457c);
        iVar3 = identity_8e3cc(puVar2);
        printf_at(0,0xc0,a44s05x,local_4c,iVar3 - local_18);
        return_zero_9c5a8();
        if (local_4c[0] == '!') {
          debug_printf(s_umcx_cy____3d__3d___000c453a + 2,*(int *)((int)puVar2 + 6) >> 0x10,
                       (int)puVar2[2] >> 0x10);
          debug_printf(s_SNot_drawn__000c454f + 1);
          if ((unaff_ECX == 0x5b) || (unaff_ECX == 0x4b00)) {
            iVar1 = iVar1 + -1;
            if (iVar1 < 0) {
              iVar1 = iStack_40;
            }
          }
          else if ((((unaff_ECX == 0x5d) || (unaff_ECX == 0x53)) || (unaff_ECX == 0x4d00)) &&
                  (iVar1 = iVar1 + 1, local_1c <= iVar1)) {
            iVar1 = 0;
          }
        }
        else {
          iStack_10 = debug_shape_info(puVar2);
          if (iStack_10 == 0) {
            debug_printf(aBad);
            clearclip_reset(dword_d457c);
          }
          else {
            uStack_14 = (int)(char)*puVar2 & 0x80;
            setdefaultscreen();
            if (iStack_10 == 2) {
              if (uStack_14 == 0) {
                drawshape(puVar2,0,0);
              }
              else {
                drawshapex_xor(puVar2,0,0);
              }
            }
            else if (uStack_14 == 0) {
              drawshape_home(puVar2);
            }
            else {
              drawshapex_xor_home();
            }
            return_zero_9c5a8();
          }
        }
      } while (local_4c[0] == '!');
      return_zero_9c5a8();
      do {
        unaff_ECX = getkey_upper();
      } while (unaff_ECX == 0);
      if (unaff_ECX == 0x1b) {
        local_24 = 1;
      }
      if (((unaff_ECX == 0x5b) || (unaff_ECX == 0x4b00)) && (iVar1 = iVar1 + -1, iVar1 < 0)) {
        iVar1 = iStack_40;
      }
      if ((((unaff_ECX == 0x5d) || (unaff_ECX == 0x53)) || (unaff_ECX == 0x4d00)) &&
         (iVar1 = iVar1 + 1, local_1c <= iVar1)) {
        iVar1 = 0;
      }
      if (unaff_ECX == 0x43) {
        setdefaultscreen();
        clearclip_reset(dword_d457c);
      }
      if (unaff_ECX == 0x4d) {
        debug_clear();
      }
      if (unaff_ECX == 0x50) {
        debug_memshapes(local_18);
      }
      if (unaff_ECX == 0x56) {
        debug_screenshot();
      }
    } while (local_24 == 0);
  }
  return;
}


// ================================================================================================
// shpi_header_fields @ 0x954c8 [__watcall]
// ================================================================================================

void __watcall
shpi_header_fields(undefined4 param_1,undefined4 *param_2,int *param_3,int *unaff_ECX,int *param_5,
                  int *param_6,undefined4 *param_7)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = identity_8e3d4(param_1);
  *param_2 = uVar1;
  iVar2 = identity_8e3c4(uVar1);
  *param_3 = iVar2;
  iVar2 = identity_8e3c4(iVar2 + 4);
  *unaff_ECX = iVar2;
  iVar2 = identity_8e3c4(iVar2 + 4);
  *param_5 = iVar2;
  iVar2 = identity_8e3c4(*param_5 + *(int *)*unaff_ECX * 4);
  *param_6 = iVar2;
  uVar1 = identity_8e3c4(*(int *)*unaff_ECX * 4 + *param_6);
  *param_7 = uVar1;
  return;
}


// ================================================================================================
// debug_shape_info @ 0x95548 [__watcall]
// ================================================================================================

undefined8 __watcall debug_shape_info(undefined4 *param_1,undefined4 unaff_EDX)

{
  undefined3 *puVar1;
  char *pcVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  
  debug_printf(aBytes3dRows3dXY3d3dCxCy3,*(int *)((int)param_1 + 2) >> 0x10,(int)param_1[1] >> 0x10,
               *(int *)((int)param_1 + 10) >> 0x10,(int)param_1[3] >> 0x10,
               *(int *)((int)param_1 + 6) >> 0x10,(int)param_1[2] >> 0x10);
  if (((int)(char)*param_1 & 0x80U) == 0) {
    puVar1 = &aUn;
  }
  else {
    puVar1 = (undefined3 *)&unk_c41fc;
  }
  debug_printf(s_a__spacked_000c4597 + 1,puVar1);
  if (((int)(char)*param_1 & 0x80U) == 0) {
    pcVar2 = s___unpacked_000c45ad + 3;
  }
  else {
    pcVar2 = s__packed_000c45a3 + 1;
  }
  printf_at(0x70,0xc0,s_ere_3d__3d___3d__3d___s_000c45b9 + 3,*(int *)((int)param_1 + 2) >> 0x10,
            (int)param_1[1] >> 0x10,*(int *)((int)param_1 + 10) >> 0x10,(int)param_1[3] >> 0x10,
            pcVar2);
  return_zero_9c5a8();
  if (((((-1 < *(short *)(param_1 + 1)) &&
        (iVar4 = *(int *)((int)param_1 + 2) >> 0x10, iVar4 <= dword_d3044)) &&
       (-1 < *(short *)((int)param_1 + 6))) &&
      (((int)param_1[1] >> 0x10 <= dword_d3048 && (-1 < *(short *)(param_1 + 3))))) &&
     ((iVar5 = *(int *)((int)param_1 + 10) >> 0x10, iVar5 <= dword_d3044 &&
      (-1 < *(short *)((int)param_1 + 0xe))))) {
    if ((((int)param_1[3] >> 0x10 <= dword_d3048) && (iVar4 + iVar5 <= dword_d3044)) &&
       (((int)param_1[1] >> 0x10) + ((int)param_1[3] >> 0x10) <= dword_d3048)) {
      uVar3 = 1;
      goto LAB_000956b8;
    }
  }
  setdefaultscreen();
  clearclip_reset(dword_d457c);
  settextpos(dword_d4580,dword_d457c);
  printstr2_centered(s_an_Shape_is_invalid__Draw_it_any_000c45d1 + 3,0x60);
  return_zero_9c5a8();
  iVar4 = debug_pause_key();
  if (iVar4 == 0x59) {
    uVar3 = 2;
  }
  else {
    uVar3 = 0;
  }
LAB_000956b8:
  return CONCAT44(unaff_EDX,uVar3);
}


// ================================================================================================
// debug_memshapes @ 0x956c0 [__watcall]
// ================================================================================================

void __watcall debug_memshapes(undefined4 param_1)

{
  undefined4 uVar1;
  undefined3 *puVar2;
  int extraout_EDX;
  int extraout_EDX_00;
  undefined4 *extraout_EDX_01;
  int iVar3;
  int iVar4;
  undefined4 uStack_a4;
  undefined4 uStack_a0;
  undefined4 uStack_9c;
  undefined uStack_98;
  undefined auStack_64 [20];
  undefined auStack_50 [20];
  undefined local_3c [4];
  undefined uStack_38;
  undefined local_34 [4];
  int local_30;
  undefined local_2c [4];
  int *local_28;
  undefined4 *local_24;
  undefined4 local_20;
  int iStack_1c;
  
  shpi_header_fields(param_1,&local_20,&local_24,&local_28,local_2c,&local_30,local_34);
  iStack_1c = *local_28;
  uStack_38 = 0;
  uStack_a4 = aMEMSHPTXT;
  uStack_a0 = DAT_000c45fc;
  uStack_9c = DAT_000c4600;
  uStack_98 = DAT_000c4604;
  debug_unique_filename(&uStack_a4);
  uVar1 = dword_edab4;
  msgbox(&uStack_a4,0x14);
  return_zero_9c5a8();
  dword_ede74 = fopen((char *)&uStack_a4,(char *)&aW_c4474);
  if (dword_ede74 == (FILE *)0x0) {
    msgbox(s_d__Error_Dumping_Shapes_List_000c4605 + 3,0x14);
    return_zero_9c5a8();
    dword_edab4 = uVar1;
  }
  else {
    dword_edab4 = uVar1;
    date_time_strings2(auStack_50,auStack_64);
    fprintf(dword_ede74,&unk_c4200,unk_c40a0);
    fprintf(dword_ede74,s_ock__FILE___s_000c4421 + 3,&uStack_a4);
    fprintf(dword_ede74,aDATES_c4430,auStack_50);
    fprintf(dword_ede74,aTIMES_c443c,auStack_64);
    fprintf(dword_ede74,&unk_c4200,unk_c40a0);
    fprintf(dword_ede74,s___Shape_file_name___0_12s_000c4622 + 2,dword_ede64);
    fprintf(dword_ede74,aShapeFileSizeLd,*local_24);
    iVar4 = iStack_1c;
    fprintf(dword_ede74,s_d_Number_of_shapes___d_000c4656 + 2,iStack_1c);
    iVar3 = 0;
    if (0 < iVar4) {
      iVar4 = 0;
      do {
        shape_offset(local_20,iVar3,local_3c);
        uVar1 = *(undefined4 *)(iVar4 + local_30);
        getshape(local_20,iVar3);
        fprintf(dword_ede74,a44s66ld,local_3c,uVar1);
        fprintf(dword_ede74,aBytes3dRows3d,*(int *)(extraout_EDX + 2) >> 0x10,
                *(int *)(extraout_EDX + 4) >> 0x10);
        fprintf(dword_ede74,s_rax_y____3d__3d__cx_cy____3d__3d_000c469e + 2,
                *(int *)(extraout_EDX_00 + 10) >> 0x10,*(int *)(extraout_EDX_00 + 0xc) >> 0x10,
                *(int *)(extraout_EDX_00 + 6) >> 0x10,*(int *)(extraout_EDX_00 + 8) >> 0x10);
        if (((int)(char)*extraout_EDX_01 & 0x80U) == 0) {
          puVar2 = &aUn;
        }
        else {
          puVar2 = (undefined3 *)&unk_c41fc;
        }
        fprintf(dword_ede74,s_a__spacked_000c4597 + 1,puVar2);
        iVar4 = iVar4 + 4;
        iVar3 = iVar3 + 1;
      } while (iVar3 < iStack_1c);
    }
    if (iStack_1c != 0) {
      fprintf(dword_ede74,&unk_c46c0);
    }
    fclose(dword_ede74);
  }
  return;
}


// ================================================================================================
// debug_palette @ 0x9596c [__watcall]
// ================================================================================================

void __watcall debug_palette(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  byte local_348 [768];
  int local_48;
  int local_44;
  int local_40;
  int local_3c;
  int local_38;
  int local_34;
  int local_30;
  uint local_2c;
  int local_28;
  uint local_24;
  uint local_20;
  uint local_1c;
  
  getpalette(0,0x100,local_348);
  setdefaultscreen();
  clearclip_reset(dword_d457c);
  debug_palette_labels(0);
  fillrect(0x18,0x16,0x120,0xa3,0xff);
  return_zero_9c5a8();
  local_40 = 0x19;
  local_38 = 0;
  do {
    iVar4 = local_40;
    iVar2 = 0x1d;
    iVar3 = local_38;
    do {
      fillrect(iVar2,iVar4,8,7,iVar3);
      iVar2 = iVar2 + 0x12;
      iVar3 = iVar3 + 1;
    } while (iVar2 != 0x13d);
    local_40 = local_40 + 10;
    local_38 = local_38 + 0x10;
  } while (local_38 != 0x100);
  return_zero_9c5a8();
  iVar3 = 0;
  iVar4 = 0;
  local_2c = 0;
  local_34 = 0x1b;
  local_3c = 0x17;
  xorbox(0x1b,0x17,0x26,0x21,dword_d45a4);
  return_zero_9c5a8();
  local_30 = 0;
  local_1c = (uint)local_348[0];
  local_20 = (uint)local_348[1];
  local_24 = (uint)local_348[2];
  do {
    settimeout(10);
    local_48 = local_34;
    local_44 = local_3c;
    local_28 = 0;
    iVar2 = key_poll();
    if (iVar2 == 0x30) {
      debug_palette_labels(0);
    }
    if (iVar2 == 0x31) {
      debug_palette_labels(1);
    }
    if (iVar2 == 0x52) {
      local_1c = local_1c + 1;
      if (0x3f < (int)local_1c) {
        local_1c = 0x3f;
      }
      local_28 = 1;
    }
    if (iVar2 == 0x47) {
      local_20 = local_20 + 1;
      if (0x3f < (int)local_20) {
        local_20 = 0x3f;
      }
      local_28 = 1;
    }
    if (iVar2 == 0x42) {
      local_24 = local_24 + 1;
      if (0x3f < (int)local_24) {
        local_24 = 0x3f;
      }
      local_28 = 1;
    }
    if (iVar2 == 0x72) {
      local_1c = local_1c - 1;
      if ((int)local_1c < 0) {
        local_1c = 0;
      }
      local_28 = 1;
    }
    if (iVar2 == 0x67) {
      local_20 = local_20 - 1;
      if ((int)local_20 < 0) {
        local_20 = 0;
      }
      local_28 = 1;
    }
    if (iVar2 == 0x62) {
      local_24 = local_24 - 1;
      if ((int)local_24 < 0) {
        local_24 = 0;
      }
      local_28 = 1;
    }
    if ((iVar2 == 0x56) || (iVar2 == 0x76)) {
      debug_screenshot();
    }
    if (iVar2 == 0x4700) {
      if (iVar3 == 0) {
        iVar4 = 0;
      }
      else {
        iVar3 = 0;
      }
    }
    if (iVar2 == 0x4f00) {
      if (iVar3 == 0xf) {
        iVar4 = 0xf;
      }
      else {
        iVar3 = 0xf;
      }
    }
    if ((iVar2 == 0x4800) && (iVar4 = iVar4 + -1, iVar4 < 0)) {
      iVar4 = 0xf;
      iVar3 = iVar3 + -1;
    }
    if ((iVar2 == 0x5000) && (iVar4 = iVar4 + 1, 0xf < iVar4)) {
      iVar4 = 0;
      iVar3 = iVar3 + 1;
    }
    if ((iVar2 == 0x4b00) && (iVar3 = iVar3 + -1, iVar3 < 0)) {
      iVar3 = 0xf;
      iVar4 = iVar4 + -1;
    }
    if ((iVar2 == 0x4d00) && (iVar3 = iVar3 + 1, 0xf < iVar3)) {
      iVar3 = 0;
      iVar4 = iVar4 + 1;
    }
    if (iVar3 < 0) {
      iVar3 = 0xf;
    }
    else if (0xf < iVar3) {
      iVar3 = 0;
    }
    if (iVar4 < 0) {
      iVar4 = 0xf;
    }
    else if (0xf < iVar4) {
      iVar4 = 0;
    }
    if (local_28 != 0) {
      iVar1 = local_30 * 3;
      local_348[iVar1] = (byte)local_1c;
      local_348[iVar1 + 1] = (byte)local_20;
      local_348[iVar1 + 2] = (byte)local_24;
      setpalette(0,0x100,local_348);
    }
    local_34 = iVar3 * 0x12 + 0x1b;
    local_3c = iVar4 * 10 + 0x17;
    xorbox(local_48,local_44,local_48 + 0xb,local_44 + 10,(&dword_d45a4)[local_2c]);
    local_2c = local_2c + 1;
    if (2 < local_2c) {
      local_2c = 0;
    }
    xorbox(local_34,local_3c,local_34 + 0xb,local_3c + 10,(&dword_d45a4)[local_2c]);
    return_zero_9c5a8();
    local_30 = iVar4 * 0x10 + iVar3;
    iVar1 = local_30 * 3;
    local_1c = (uint)local_348[iVar1];
    local_20 = (uint)local_348[iVar1 + 1];
    local_24 = (uint)local_348[iVar1 + 2];
    settextpos(dword_d4584,dword_d457c);
    printf_at(0x44,0xc0,a033d022X,local_30,local_30);
    return_zero_9c5a8();
    settextpos(4,dword_d457c);
    printf_at(0x8c,0xc0,aR022d,local_1c);
    return_zero_9c5a8();
    settextpos(2,dword_d457c);
    printf_at(0xb4,0xc0,aG022d,local_20);
    return_zero_9c5a8();
    settextpos(1,dword_d457c);
    printf_at(0xdc,0xc0,aB022d,local_24);
    return_zero_9c5a8();
    waittimeout();
  } while (iVar2 != 0x1b);
  return;
}


// ================================================================================================
// debug_palette_labels @ 0x95ecc [__watcall]
// ================================================================================================

void __watcall debug_palette_labels(int param_1)

{
  int iVar1;
  int iVar2;
  
  settextpos(dword_d4584,dword_d457c);
  iVar1 = 0x19;
  iVar2 = 0x19;
  do {
    printf_at(iVar2,0xd,&a02d_c46f8,param_1);
    printf_at(7,iVar1,&a02d_c46f8,param_1);
    return_zero_9c5a8();
    iVar1 = iVar1 + 10;
    iVar2 = iVar2 + 0x12;
    param_1 = param_1 + 1;
  } while (iVar2 != 0x139);
  return;
}


// ================================================================================================
// debug_screenshot @ 0x95f30 [__watcall]
// ================================================================================================

void __watcall debug_screenshot(void)

{
  undefined4 uVar1;
  char local_4c [4];
  char acStack_48 [4];
  ushort local_44;
  char cStack_42;
  
  uVar1 = dword_edab4;
  local_4c = (char  [4])s__ldSCREEN_____000c46fd._3_4_;
  acStack_48 = (char  [4])s__ldSCREEN_____000c46fd._7_4_;
  local_44 = s__ldSCREEN_____000c46fd._11_2_;
  cStack_42 = s__ldSCREEN_____000c46fd[0xd];
  debug_unique_filename(local_4c);
  local_44 = local_44 & 0xff00;
  msgbox(local_4c,0x14);
  return_zero_9c5a8();
  save_screen_shape(local_4c);
  dword_edab4 = uVar1;
  return;
}


// ================================================================================================
// debug_shape_view @ 0x95f84 [__watcall]
// ================================================================================================

void __watcall debug_shape_view(void)

{
  undefined4 *puVar1;
  int iVar2;
  uint uVar3;
  
  debug_clear();
  setdefaultscreen();
  clearclip_reset(dword_d457c);
  iVar2 = window_select(dword_ede80);
  puVar1 = *(undefined4 **)(iVar2 + 0x2c);
  setdefaultscreen();
  iVar2 = debug_shape_info(puVar1);
  if (iVar2 != 0) {
    uVar3 = (int)(char)*puVar1 & 0x80;
    if (iVar2 == 2) {
      if (uVar3 == 0) {
        drawshape(puVar1,0,0);
      }
      else {
        drawshapex_xor(puVar1,0,0);
      }
    }
    else if (uVar3 == 0) {
      drawshape_home(puVar1);
    }
    else {
      drawshapex_xor_home();
    }
    return_zero_9c5a8();
    while (iVar2 = debug_pause_key(), iVar2 == 0x56) {
      debug_screenshot();
    }
  }
  return;
}


// ================================================================================================
// date_time_strings2 @ 0x96030 [__watcall]
// ================================================================================================

void __watcall date_time_strings2(char *param_1,undefined4 unaff_EDX)

{
  char *__s;
  byte local_18;
  byte local_17;
  ushort local_16;
  byte local_10;
  byte local_f;
  byte local_e;
  
  _dos_getdate(&local_18,unaff_EDX,param_1,unaff_EDX);
  _dos_gettime(&local_10);
  sprintf(param_1,a02d3s02d_c470c,(uint)local_18,(&off_93c54)[local_17],(uint)local_16 % 100);
  sprintf(__s,a2d02d02d_c471c,(uint)local_10,(uint)local_f,(uint)local_e);
  return;
}


// ================================================================================================
// debug_unique_filename @ 0x960ac [__watcall]
// ================================================================================================

undefined8 __watcall debug_unique_filename(char *param_1,undefined4 unaff_EDX)

{
  char cVar1;
  char *pcVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar5 = 0;
  cVar1 = *param_1;
  pcVar2 = param_1;
  while (cVar1 != '?') {
    pcVar2 = pcVar2 + 1;
    iVar5 = iVar5 + 1;
    cVar1 = *pcVar2;
  }
  iVar4 = 0;
  do {
    *pcVar2 = (char)((longlong)iVar4 / 10) + '0';
    pcVar2[1] = (char)((longlong)iVar4 % 10) + '0';
    iVar3 = dos_findfirst_dta(param_1);
    if (iVar3 == 0) break;
    iVar4 = iVar4 + 1;
  } while (iVar4 < 100);
  if (99 < iVar4) {
    param_1 = param_1 + iVar5;
    param_1[1] = 'x';
    *param_1 = param_1[1];
  }
  return CONCAT44(unaff_EDX,1);
}


// ================================================================================================
// debug_wait_key @ 0x9612c [__watcall]
// ================================================================================================

void __watcall debug_wait_key(void)

{
  return_zero_9c5a8();
  dword_d45b0 = getkey_upper();
  return;
}


// ================================================================================================
// debug_pause_key @ 0x96144 [__watcall]
// ================================================================================================

void __watcall
debug_pause_key(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  undefined4 uVar1;
  
  return_zero_9c5a8();
  flushkeys_wrap();
  uVar1 = debug_wait_key_loop();
  toupper_ascii(uVar1,unaff_EDX,unaff_ECX,unaff_EBX);
  return;
}


// ================================================================================================
// flushkeys_wrap @ 0x96164 [__watcall]
// ================================================================================================

void __watcall flushkeys_wrap(void)

{
  flushkeys();
  return;
}


// ================================================================================================
// debug_wait_key_loop @ 0x96170 [__watcall]
// ================================================================================================

void __watcall debug_wait_key_loop(void)

{
  int iVar1;
  
  flushkeys();
  do {
    iVar1 = debug_wait_key();
  } while (iVar1 == 0);
  return;
}


// ================================================================================================
// fprintf @ 0x96185 [__cdecl]
// ================================================================================================

int fprintf(FILE *__stream,char *__format,...)

{
  int iVar1;
  undefined *local_c [2];
  
  local_c[0] = &stack0x0000000c;
  iVar1 = vfprintf(__stream,__format,local_c);
  return iVar1;
}


// ================================================================================================
// strupr @ 0x961b0 [__watcall]
// ================================================================================================

undefined8 __watcall strupr(char *param_1,undefined4 unaff_EDX)

{
  char cVar1;
  char *pcVar2;
  
  for (pcVar2 = param_1; cVar1 = *pcVar2, cVar1 != '\0'; pcVar2 = pcVar2 + 1) {
    if ((byte)(cVar1 + 0x9fU) < 0x1a) {
      *pcVar2 = cVar1 + -0x20;
    }
  }
  return CONCAT44(unaff_EDX,param_1);
}


// ================================================================================================
// fround @ 0x961d0 [__watcall]
// ================================================================================================

longdouble __watcall fround(void)

{
  longdouble in_ST0;
  
  return ROUND(in_ST0);
}


// ================================================================================================
// unk_961ee @ 0x961ee
// ================================================================================================

/* WARNING: Removing unreachable block (ram,0x0009d332) */

longdouble unk_961ee(void)

{
  int unaff_EBP;
  
  if (unaff_EBP != 0) {
    FUN_0009d352();
  }
  return (longdouble)0;
}


// ================================================================================================
// unk_961f3 @ 0x961f3
// ================================================================================================

void __watcall
unk_961f3(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  code *pcVar1;
  char cVar2;
  
  if (byte_d51dc != '\x01') {
    return;
  }
  if (byte_d4d08 == '\0') {
    if (byte_d4d06 == '\t') {
      (**(code **)(dword_d41f4 + 0x30))();
    }
    else if (byte_d4d06 == '\0') {
      pcVar1 = (code *)swi(0x21);
      (*pcVar1)();
    }
    else if (byte_d4d06 == '\x01') {
      __dpmi_fini_hooks(0,word_d41f8,unaff_EBX,unaff_ECX,unaff_EDX,unaff_EBX,unaff_ECX);
    }
    else {
      cVar2 = __dpmi_fini_hooks(byte_d4d06,0,unaff_EBX,unaff_ECX,unaff_EDX,unaff_EBX,unaff_ECX);
      if (cVar2 != '\x01') {
        unhook_pharlap();
      }
    }
  }
  else {
    _reset_EM_MP_bits();
  }
  byte_d51dc = 0;
  return;
}


// ================================================================================================
// strlwr @ 0x961f8 [__watcall]
// ================================================================================================

undefined8 __watcall strlwr(char *param_1,undefined4 unaff_EDX)

{
  char cVar1;
  char *pcVar2;
  
  for (pcVar2 = param_1; cVar1 = *pcVar2, cVar1 != '\0'; pcVar2 = pcVar2 + 1) {
    if ((byte)(cVar1 + 0xbfU) < 0x1a) {
      *pcVar2 = cVar1 + ' ';
    }
  }
  return CONCAT44(unaff_EDX,param_1);
}


// ================================================================================================
// delay_ms @ 0x96218 [__watcall]
// ================================================================================================

void __watcall delay_ms(int param_1)

{
  code *pcVar1;
  uint uVar2;
  
  if (param_1 != 0) {
    uVar2 = (param_1 * dword_f24cc + 500U) / 1000;
    if (uVar2 == 0) {
      uVar2 = 1;
    }
    do {
      pcVar1 = (code *)swi(0x21);
      (*pcVar1)();
      uVar2 = uVar2 - 1;
    } while (uVar2 != 0);
  }
  return;
}


// ================================================================================================
// perror @ 0x9621d [__watcall]
// ================================================================================================

void __watcall perror(char *__s)

{
  int *piVar1;
  char *__s_00;
  
  if ((__s != (char *)0x0) && (*__s != '\0')) {
    fputs(__s,(FILE *)&unk_d4d4c);
    fputs((char *)&asc_c472c,(FILE *)&unk_d4d4c);
  }
  piVar1 = (int *)__get_errno_ptr();
  __s_00 = strerror(*piVar1);
  fputs(__s_00,(FILE *)&unk_d4d4c);
  fputc(10,(FILE *)&unk_d4d4c);
  return;
}


// ================================================================================================
// write @ 0x96267 [__watcall]
// ================================================================================================

ssize_t __watcall write(int __fd,void *__buf,size_t __n)

{
  code *pcVar1;
  bool bVar2;
  uint uVar3;
  undefined4 uVar4;
  ssize_t sVar5;
  int iVar6;
  uint uVar7;
  ssize_t extraout_EDX;
  int extraout_EDX_00;
  char *pcVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  undefined4 *puVar11;
  undefined4 *puVar12;
  undefined4 *puVar13;
  uint uVar14;
  byte bVar15;
  undefined8 uVar16;
  undefined6 uVar17;
  uint local_24;
  uint local_20;
  char *local_1c;
  uint local_14;
  
  puVar10 = (undefined4 *)&stack0xffffffcc;
  uVar3 = __GetIOMode();
  if (uVar3 == 0) {
    uVar4 = 4;
LAB_00096286:
    __set_errno(uVar4);
    return -1;
  }
  if ((uVar3 & 2) == 0) {
    uVar4 = 6;
    goto LAB_00096286;
  }
  uVar14 = uVar3;
  uVar7 = uVar3;
  if ((uVar3 & 0x80) != 0) {
    bVar15 = 0;
    pcVar1 = (code *)swi(0x21);
    uVar17 = (*pcVar1)();
    uVar14 = (uint)uVar17;
    puVar9 = (undefined4 *)&stack0xffffffd0;
    puVar10 = (undefined4 *)&stack0xffffffd0;
    bVar2 = (bVar15 & 1) != 0;
    uVar7 = CONCAT22((ushort)((short)((uint6)uVar17 >> 0x20) << 1 | (ushort)bVar15) >> 1 |
                     (ushort)bVar2 << 0xf,(short)uVar17);
    local_20 = uVar7;
    if (bVar2) goto LAB_000962c7;
  }
  bVar15 = 0;
  if ((uVar3 & 0x40) == 0) {
    puVar10[-1] = 0x96317;
    uVar3 = stackavail(uVar14,uVar7);
    if (uVar3 < 0xb0) {
                    /* WARNING: Subroutine does not return */
      puVar10[-1] = 0x96325;
      __STKOVERFLOW();
    }
    uVar14 = 0x200;
    if (uVar3 < 0x230) {
      uVar14 = 0x80;
    }
    uVar3 = 0;
    iVar6 = -uVar14;
    local_14 = 0;
    local_24 = 0;
    puVar11 = (undefined4 *)((int)puVar10 + iVar6);
    local_1c = (char *)__buf;
    while (local_14 < __n) {
      puVar13 = puVar11;
      if (*local_1c == '\n') {
        *(undefined *)((int)puVar10 + uVar3 + iVar6) = 0xd;
        uVar3 = uVar3 + 1;
        bVar15 = uVar3 < uVar14;
        if (uVar3 == uVar14) {
          pcVar1 = (code *)swi(0x21);
          uVar16 = (*pcVar1)();
          uVar7 = (uint)((ulonglong)uVar16 >> 0x20);
          puVar9 = puVar11 + 1;
          puVar13 = puVar11 + 1;
          bVar2 = (bVar15 & 1) != 0;
          local_20 = ((int)uVar16 << 1 | (uint)bVar15) >> 1 | (uint)bVar2 << 0x1f;
          if (bVar2) goto LAB_000962c7;
          puVar12 = puVar11;
          if (local_20 != uVar14) goto LAB_00096391;
          uVar3 = local_20 ^ uVar14;
          local_24 = local_14;
        }
      }
      pcVar8 = local_1c + 1;
      local_14 = local_14 + 1;
      *(char *)((int)puVar10 + uVar3 + iVar6) = *local_1c;
      uVar3 = uVar3 + 1;
      bVar15 = uVar3 < uVar14;
      puVar11 = puVar13;
      local_1c = pcVar8;
      if (uVar3 == uVar14) {
        pcVar1 = (code *)swi(0x21);
        uVar16 = (*pcVar1)();
        uVar7 = (uint)((ulonglong)uVar16 >> 0x20);
        puVar9 = (undefined4 *)((int)puVar13 + 4);
        puVar11 = (undefined4 *)((int)puVar13 + 4);
        bVar2 = (bVar15 & 1) != 0;
        local_20 = ((int)uVar16 << 1 | (uint)bVar15) >> 1 | (uint)bVar2 << 0x1f;
        if (bVar2) goto LAB_000962c7;
        puVar12 = puVar13;
        if (local_20 != uVar14) {
LAB_00096391:
          *puVar12 = 0x9639b;
          __set_errno(0xc,uVar7,__fd);
          return local_24 + local_20;
        }
        uVar3 = local_20 ^ uVar14;
        local_24 = local_14;
      }
    }
    bVar15 = 0;
    if (uVar3 == 0) {
      return __n;
    }
    pcVar1 = (code *)swi(0x21);
    iVar6 = (*pcVar1)();
    puVar9 = puVar11 + 1;
    bVar2 = (bVar15 & 1) != 0;
    uVar7 = (iVar6 << 1 | (uint)bVar15) >> 1 | (uint)bVar2 << 0x1f;
    local_20 = uVar7;
    if (!bVar2) {
      if (uVar7 == uVar3) {
        return __n;
      }
      *puVar11 = 0x96427;
      __set_errno(0xc,uVar7,__fd);
      return local_24 + extraout_EDX_00;
    }
  }
  else {
    pcVar1 = (code *)swi(0x21);
    iVar6 = (*pcVar1)();
    puVar9 = puVar10 + 1;
    bVar2 = (bVar15 & 1) != 0;
    uVar7 = (iVar6 << 1 | (uint)bVar15) >> 1 | (uint)bVar2 << 0x1f;
    local_20 = uVar7;
    if (!bVar2) {
      if (uVar7 == __n) {
        return __n;
      }
      *puVar10 = 0x9630a;
      __set_errno(0xc,uVar7,__fd);
      return extraout_EDX;
    }
  }
LAB_000962c7:
  *(undefined4 *)((int)puVar9 + -4) = 0x962d2;
  sVar5 = __set_errno_dos(local_20 & 0xffff,uVar7,__fd);
  return sVar5;
}


// ================================================================================================
// drawshape_clip_save @ 0x96440 [__cdecl]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void drawshape_clip_save(int param_1,int param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  int local_1c;
  int local_18;
  uint local_10;
  
  if (dword_d30c8 == 0) {
    vesa_drawshape_clip_save(param_1,param_2,param_3);
  }
  else {
    *(short *)(param_1 + 0xc) = (short)param_2;
    *(short *)(param_1 + 0xe) = (short)param_3;
    iVar5 = param_1 + 0x10;
    local_18 = *(int *)(param_1 + 2) >> 0x10;
    local_1c = *(int *)(param_1 + 4) >> 0x10;
    iVar3 = dword_d30b0 - param_3;
    if (0 < iVar3) {
      iVar5 = iVar5 + local_18 * iVar3;
      local_1c = local_1c - iVar3;
      param_3 = param_3 + iVar3;
    }
    iVar3 = (param_3 + local_1c) - dword_d30b8;
    if (0 < iVar3) {
      local_1c = local_1c - iVar3;
    }
    iVar4 = dword_d30ac - param_2;
    iVar3 = 0;
    if (0 < iVar4) {
      iVar5 = iVar5 + iVar4;
      local_18 = local_18 - iVar4;
      param_2 = param_2 + iVar4;
      iVar3 = iVar4;
    }
    iVar4 = (local_18 + param_2) - _dword_d30b4;
    if (0 < iVar4) {
      iVar3 = iVar3 + iVar4;
      local_18 = local_18 - iVar4;
    }
    iVar4 = (&unk_d3104)[param_3];
    iVar1 = dword_d30a4 - local_18;
    local_10 = (uint)(param_2 + iVar4) >> 0x10;
    iVar7 = dword_d30d0;
    vesa_set_bank(local_10,iVar1,iVar3,dword_d30d0);
    uVar6 = param_2 + iVar4 & 0xffff;
    if (0 < local_18) {
      for (; 0 < local_1c; local_1c = local_1c + -1) {
        uVar2 = local_18 + uVar6;
        if ((uVar2 & 0x10000) == 0) {
          memmove_dwords(iVar7 + uVar6,iVar5,local_18);
          iVar5 = iVar5 + local_18;
        }
        else {
          memmove_dwords(iVar7 + uVar6,iVar5,0x10000 - uVar6);
          iVar5 = iVar5 + (0x10000 - uVar6);
          uVar2 = uVar2 & 0xffff;
          local_10 = local_10 + 1;
          vesa_set_bank(local_10);
          memmove_dwords(iVar7,iVar5,uVar2);
          iVar5 = iVar5 + uVar2;
        }
        uVar6 = uVar2 + iVar1;
        iVar5 = iVar5 + iVar3;
        if ((uVar6 & 0x10000) != 0) {
          uVar6 = uVar6 & 0xffff;
          local_10 = local_10 + 1;
          vesa_set_bank(local_10);
        }
      }
    }
  }
  return;
}


// ================================================================================================
// drawshape_clip_save_home @ 0x965dc [__cdecl]
// ================================================================================================

void drawshape_clip_save_home(int param_1)

{
  drawshape_clip_save(param_1,*(int *)(param_1 + 10) >> 0x10,*(int *)(param_1 + 0xc) >> 0x10);
  return;
}


// ================================================================================================
// drawshape_clip_save_centered @ 0x965f8 [__cdecl]
// ================================================================================================

void drawshape_clip_save_centered(int param_1,int param_2,int param_3)

{
  drawshape_clip_save(param_1,param_2 - (*(int *)(param_1 + 6) >> 0x10),
                      param_3 - (*(int *)(param_1 + 8) >> 0x10));
  return;
}


// ================================================================================================
// drawshape_clip_save_window @ 0x96620 [__watcall]
// ================================================================================================

void __watcall drawshape_clip_save_window(void)

{
  undefined4 uVar1;
  int param_5;
  int param_6;
  int in_stack_0000000c;
  int in_stack_00000010;
  int in_stack_00000014;
  int in_stack_00000018;
  undefined auStack_6c [96];
  
  save_screen_state(auStack_6c);
  uVar1 = dword_d30d0;
  setdefaultscreen();
  setclip(param_5,in_stack_00000014 + param_5,param_6,in_stack_00000018 + param_6);
  drawshape_clip_save(uVar1,param_5 - in_stack_0000000c,param_6 - in_stack_00000010);
  restore_screen_state(auStack_6c);
  return;
}


// ================================================================================================
// mvi_print_info @ 0x96690 [__watcall]
// ================================================================================================

void __watcall mvi_print_info(undefined4 *param_1)

{
  debug_printf(aFrameRate3dFrames3dBlock,param_1[2],*param_1,param_1[8]);
  debug_printf(s_me_Width___3d_Height___3d_000c475d + 3,param_1[3],param_1[4]);
  debug_printf(s_cdeColours___3d_1st_Colour___3d_000c477d + 3,param_1[6],param_1[5]);
  return;
}


// ================================================================================================
// mvi_open_windows @ 0x966e4 [__watcall]
// ================================================================================================

void __watcall mvi_open_windows(int *param_1,int unaff_EDX)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  byte bVar7;
  byte bVar8;
  byte bVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  byte *pbVar15;
  
  bVar1 = *(byte *)(unaff_EDX + 2);
  bVar2 = *(byte *)(unaff_EDX + 3);
  iVar14 = (uint)*(byte *)(unaff_EDX + 4) + (uint)*(byte *)(unaff_EDX + 5) * 0x100;
  iVar12 = (uint)*(byte *)(unaff_EDX + 6) + (uint)*(byte *)(unaff_EDX + 7) * 0x100;
  bVar3 = *(byte *)(unaff_EDX + 8);
  bVar4 = *(byte *)(unaff_EDX + 9);
  bVar5 = *(byte *)(unaff_EDX + 10);
  bVar6 = *(byte *)(unaff_EDX + 0xb);
  bVar7 = *(byte *)(unaff_EDX + 0xc);
  bVar8 = *(byte *)(unaff_EDX + 0xd);
  pbVar15 = (byte *)(unaff_EDX + 0x10);
  iVar13 = (uint)*(byte *)(unaff_EDX + 0xe) + (uint)*(byte *)(unaff_EDX + 0xf) * 0x100;
  iVar11 = iVar13 * 3;
  iVar10 = allocmem(s_firmvipal_000c47a1 + 3,iVar11,0);
  param_1[7] = iVar10;
  iVar10 = 0;
  if (iVar11 != 0) {
    do {
      bVar9 = *pbVar15;
      pbVar15 = pbVar15 + 1;
      *(char *)(param_1[7] + iVar10) = (char)((int)(uint)bVar9 >> 2);
      iVar10 = iVar10 + 1;
    } while (iVar10 < iVar11);
  }
  param_1[5] = (uint)bVar7 + (uint)bVar8 * 0x100;
  param_1[6] = iVar13;
  *param_1 = (uint)bVar1 + (uint)bVar2 * 0x100;
  param_1[1] = 1;
  param_1[8] = (uint)bVar3 + (uint)bVar4 * 0x100;
  param_1[3] = iVar14;
  param_1[4] = iVar12;
  param_1[10] = iVar11 + 0x10;
  param_1[0xb] = iVar11 + 0x10;
  param_1[2] = (uint)bVar5 + (uint)bVar6 * 0x100;
  iVar11 = windowdefp(iVar14,iVar12,0);
  param_1[0xd] = iVar11;
  iVar11 = windowdefp(iVar14,iVar12,0);
  param_1[0xe] = iVar11;
  iVar12 = windowdefp(iVar14,iVar12,0);
  param_1[0xf] = iVar12;
  return;
}


// ================================================================================================
// mvi_open @ 0x96844 [__watcall]
// ================================================================================================

int __watcall mvi_open(void)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 in_stack_00000004;
  int in_stack_00000008;
  undefined local_328 [784];
  undefined local_18 [4];
  int local_14;
  int local_10;
  
  iVar1 = allocmem_try();
  if (iVar1 != 0) {
    if ((in_stack_00000008 == 1) || (in_stack_00000008 == 0)) {
      iVar2 = loadfile_fatal();
      if (iVar2 == 0) {
        if (in_stack_00000008 != 0) {
          freemem(iVar1);
          iVar1 = 0;
        }
      }
      else {
        uVar3 = memblock_ptr(iVar2);
        uVar3 = identity_972f0(uVar3);
        mvi_open_windows(iVar1,uVar3);
        *(int *)(iVar1 + 0x30) = iVar2;
        *(undefined4 *)(iVar1 + 0x24) = 0;
      }
    }
    else {
      dos_open_fatal(in_stack_00000004,&local_10,&local_14,local_18);
      if (local_10 == 0) {
        freemem(iVar1);
        return 0;
      }
      dos_read_blocks(local_10,local_328,0x310);
      mvi_open_windows(iVar1,local_328);
      *(int *)(iVar1 + 0x24) = local_10;
      *(int *)(iVar1 + 0x28) = *(int *)(iVar1 + 0x28) + local_14;
      iVar2 = reservemem_fatal(s_DATABUFFER_000c47ab + 1,
                               *(int *)(iVar1 + 0xc) * *(int *)(iVar1 + 0x10),0x40);
      *(int *)(iVar1 + 0x30) = iVar2;
      if (iVar2 == 0) {
        closehandle(local_10);
        freemem(iVar1);
        return 0;
      }
      seekhandle(local_10,*(undefined4 *)(iVar1 + 0x28));
    }
  }
  return iVar1;
}


// ================================================================================================
// mvi_close @ 0x969a8 [__watcall]
// ================================================================================================

void __watcall mvi_close(void)

{
  int in_stack_00000004;
  
  if (in_stack_00000004 != 0) {
    if (*(int *)(in_stack_00000004 + 0x24) != 0) {
      closehandle(*(int *)(in_stack_00000004 + 0x24));
    }
    if (*(int *)(in_stack_00000004 + 0x30) != 0) {
      releasememblock(*(int *)(in_stack_00000004 + 0x30));
    }
    removewindow_free(*(undefined4 *)(in_stack_00000004 + 0x34));
    removewindow_free(*(undefined4 *)(in_stack_00000004 + 0x38));
    removewindow_free(*(undefined4 *)(in_stack_00000004 + 0x3c));
    freemem(*(undefined4 *)(in_stack_00000004 + 0x1c));
    freemem(in_stack_00000004);
  }
  return;
}


// ================================================================================================
// mvi_rewind @ 0x96a10 [__cdecl]
// ================================================================================================

void mvi_rewind(int param_1)

{
  *(undefined4 *)(param_1 + 4) = 1;
  if (*(int *)(param_1 + 0x24) == 0) {
    *(undefined4 *)(param_1 + 0x2c) = *(undefined4 *)(param_1 + 0x28);
    return;
  }
  seekhandle(*(int *)(param_1 + 0x24),*(undefined4 *)(param_1 + 0x28));
  return;
}


// ================================================================================================
// mvi_get_size @ 0x96a38 [__cdecl]
// ================================================================================================

void mvi_get_size(int param_1,undefined4 *param_2,undefined4 *param_3,undefined4 *param_4)

{
  *param_2 = *(undefined4 *)(param_1 + 0x14);
  *param_3 = *(undefined4 *)(param_1 + 0x18);
  *param_4 = *(undefined4 *)(param_1 + 0x1c);
  return;
}


// ================================================================================================
// mvi_current_frame @ 0x96a58 [__cdecl]
// ================================================================================================

undefined4 mvi_current_frame(int param_1)

{
  return *(undefined4 *)(param_1 + 4);
}


// ================================================================================================
// mvi_width @ 0x96a60 [__cdecl]
// ================================================================================================

undefined4 mvi_width(int param_1)

{
  return *(undefined4 *)(param_1 + 0xc);
}


// ================================================================================================
// mvi_height @ 0x96a68 [__cdecl]
// ================================================================================================

undefined4 mvi_height(int param_1)

{
  return *(undefined4 *)(param_1 + 0x10);
}


// ================================================================================================
// mvi_handle_field0 @ 0x96a70 [__cdecl]
// ================================================================================================

undefined4 mvi_handle_field0(undefined4 *param_1)

{
  return *param_1;
}


// ================================================================================================
// mvi_frame_count @ 0x96a78 [__cdecl]
// ================================================================================================

undefined4 mvi_frame_count(int param_1)

{
  return *(undefined4 *)(param_1 + 8);
}


// ================================================================================================
// mvi_has_more @ 0x96a80 [__cdecl]
// ================================================================================================

bool mvi_has_more(int *param_1)

{
  return *param_1 < param_1[1];
}


// ================================================================================================
// mvi_seek @ 0x96a94 [__watcall]
// ================================================================================================

void __watcall mvi_seek(void)

{
  int iVar1;
  int in_stack_00000004;
  int in_stack_00000008;
  
  if (in_stack_00000008 < 0) {
    in_stack_00000008 = 0;
  }
  mvi_rewind(in_stack_00000004);
  iVar1 = *(int *)(in_stack_00000004 + 4);
  while (iVar1 < in_stack_00000008) {
    mvi_next_frame(in_stack_00000004);
    iVar1 = *(int *)(in_stack_00000004 + 4);
  }
  return;
}


// ================================================================================================
// mvi_decode_blocks @ 0x96ac4 [__watcall]
// ================================================================================================

void __watcall mvi_decode_blocks(int param_1,byte *unaff_EDX,byte *unaff_EBX)

{
  byte bVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined4 *puVar8;
  int *piVar9;
  undefined4 *puVar10;
  int iVar11;
  int local_3c;
  int local_20;
  int local_18;
  int local_14;
  
  iVar3 = *(int *)(param_1 + 0xc);
  iVar4 = *(int *)(*(int *)(param_1 + 0x34) + 0x2c);
  iVar5 = *(int *)(*(int *)(param_1 + 0x38) + 0x2c);
  iVar6 = *(int *)(*(int *)(param_1 + 0x3c) + 0x2c);
  iVar7 = *(int *)(*(int *)(param_1 + 0x34) + 0x28);
  local_20 = 0;
  if (0 < *(int *)(param_1 + 0x10)) {
    do {
      local_14 = 0;
      if (0 < iVar3) {
        piVar9 = (int *)(iVar7 + local_20 * 4);
        iVar11 = iVar4;
        do {
          if ((*unaff_EDX == 0xff) && (*unaff_EBX == 0xff)) {
            puVar8 = (undefined4 *)(*piVar9 + iVar11);
            *puVar8 = *(undefined4 *)(unaff_EBX + 1);
            puVar8 = (undefined4 *)((int)puVar8 + iVar3);
            *puVar8 = *(undefined4 *)(unaff_EBX + 5);
            puVar8 = (undefined4 *)((int)puVar8 + iVar3);
            *puVar8 = *(undefined4 *)(unaff_EBX + 9);
            *(undefined4 *)(iVar3 + (int)puVar8) = *(undefined4 *)(unaff_EBX + 0xd);
            unaff_EBX = unaff_EBX + 0x11;
          }
          else {
            bVar1 = *unaff_EDX;
            if (bVar1 == 0xff) {
              bVar1 = *unaff_EBX;
              bVar2 = *unaff_EBX;
              unaff_EBX = unaff_EBX + 1;
              local_3c = iVar6;
            }
            else {
              bVar2 = *unaff_EDX;
              local_3c = iVar5;
            }
            local_18 = ((int)(uint)bVar2 >> 4) + -7;
            puVar10 = (undefined4 *)(*piVar9 + iVar11);
            puVar8 = (undefined4 *)
                     (local_3c + local_14 + ((bVar1 & 0xf) - 7) +
                     *(int *)(iVar7 + (local_20 + local_18) * 4));
            *puVar10 = *puVar8;
            puVar10 = (undefined4 *)((int)puVar10 + iVar3);
            puVar8 = (undefined4 *)((int)puVar8 + iVar3);
            *puVar10 = *puVar8;
            puVar10 = (undefined4 *)((int)puVar10 + iVar3);
            puVar8 = (undefined4 *)((int)puVar8 + iVar3);
            *puVar10 = *puVar8;
            *(undefined4 *)(iVar3 + (int)puVar10) = *(undefined4 *)(iVar3 + (int)puVar8);
          }
          unaff_EDX = unaff_EDX + 1;
          iVar11 = iVar11 + 4;
          local_14 = local_14 + 4;
        } while (local_14 < iVar3);
      }
      local_20 = local_20 + 4;
    } while (local_20 < *(int *)(param_1 + 0x10));
  }
  return;
}


// ================================================================================================
// mvi_decode_blocks_delta @ 0x96c4c [__watcall]
// ================================================================================================

void __watcall mvi_decode_blocks_delta(int param_1,byte *unaff_EDX,byte *unaff_EBX)

{
  byte bVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  byte *pbVar10;
  int iVar11;
  int iVar12;
  byte *pbVar13;
  int local_60;
  int local_5c;
  int local_40;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  
  iVar3 = *(int *)(param_1 + 0xc);
  iVar4 = *(int *)(param_1 + 0x10);
  iVar5 = *(int *)(param_1 + 0x20);
  iVar9 = *(int *)(*(int *)(param_1 + 0x34) + 0x2c) + 0x10;
  iVar6 = *(int *)(*(int *)(param_1 + 0x38) + 0x2c);
  iVar7 = *(int *)(*(int *)(param_1 + 0x3c) + 0x2c);
  local_40 = 0;
  if (0 < iVar4) {
    do {
      local_60 = 0;
      if (0 < iVar3) {
        do {
          if ((*unaff_EDX == 0xff) && (*unaff_EBX == 0xff)) {
            local_2c = local_40;
            unaff_EBX = unaff_EBX + 1;
            if (local_40 < local_40 + iVar5) {
              iVar11 = local_40 * iVar3;
              do {
                if (local_60 < local_60 + iVar5) {
                  pbVar10 = (byte *)(local_60 + iVar11 + iVar9);
                  iVar8 = local_60;
                  pbVar13 = unaff_EBX;
                  do {
                    unaff_EBX = pbVar13 + 1;
                    *pbVar10 = *pbVar13;
                    pbVar10 = pbVar10 + 1;
                    iVar8 = iVar8 + 1;
                    pbVar13 = unaff_EBX;
                  } while (iVar8 < local_60 + iVar5);
                }
                iVar11 = iVar11 + iVar3;
                local_2c = local_2c + 1;
              } while (local_2c < local_40 + iVar5);
            }
          }
          else {
            bVar1 = *unaff_EDX;
            if (bVar1 == 0xff) {
              bVar1 = *unaff_EBX;
              bVar2 = *unaff_EBX;
              unaff_EBX = unaff_EBX + 1;
              local_24 = iVar7;
            }
            else {
              bVar2 = *unaff_EDX;
              local_24 = iVar6;
            }
            local_20 = (bVar1 & 0xf) - 7;
            local_24 = local_24 + 0x10;
            local_5c = ((int)(uint)bVar2 >> 4) + -7;
            if (0 < iVar5) {
              local_28 = local_40;
              do {
                if (0 < iVar5) {
                  iVar11 = local_60;
                  do {
                    if ((local_28 < iVar4) && (iVar11 < iVar3)) {
                      iVar8 = local_20 + iVar11;
                      iVar12 = local_5c + local_28;
                      if ((iVar12 < 0) || (((iVar4 <= iVar12 || (iVar8 < 0)) || (iVar3 <= iVar8))))
                      {
                        *(undefined *)(local_28 * iVar3 + iVar9 + iVar11) = 0;
                      }
                      else {
                        *(undefined *)(local_28 * iVar3 + iVar9 + iVar11) =
                             *(undefined *)(iVar12 * iVar3 + local_24 + iVar8);
                      }
                    }
                    iVar11 = iVar11 + 1;
                  } while (iVar11 < local_60 + iVar5);
                }
                local_28 = local_28 + 1;
              } while (local_28 < iVar5 + local_40);
            }
          }
          unaff_EDX = unaff_EDX + 1;
          local_60 = local_60 + iVar5;
        } while (local_60 < iVar3);
      }
      local_40 = local_40 + iVar5;
    } while (local_40 < iVar4);
  }
  return;
}


// ================================================================================================
// mvi_next_frame @ 0x96e7c [__cdecl]
// ================================================================================================

undefined4 mvi_next_frame(int param_1)

{
  int iVar1;
  char *pcVar2;
  undefined4 uVar3;
  int iVar4;
  byte local_24;
  byte local_23;
  byte local_22;
  byte local_21;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  char *local_10;
  
  local_14 = *(int *)(param_1 + 0x20);
  local_20 = *(int *)(param_1 + 0xc);
  local_1c = *(int *)(param_1 + 0x10);
  local_18 = ((local_20 + local_14 + -1) / local_14) * ((local_1c + local_14 + -1) / local_14);
  iVar1 = memblock_ptr(*(undefined4 *)(param_1 + 0x30));
  pcVar2 = (char *)identity_972f0(iVar1 + *(int *)(param_1 + 0x2c));
  local_10 = pcVar2 + local_18;
  iVar1 = mvi_has_more(param_1);
  if (iVar1 == 0) {
    uVar3 = *(undefined4 *)(param_1 + 0x3c);
    *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(param_1 + 0x38);
    *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(param_1 + 0x34);
    *(undefined4 *)(param_1 + 0x34) = uVar3;
    if (*(int *)(param_1 + 0x24) != 0) {
      uVar3 = memblock_ptr(*(undefined4 *)(param_1 + 0x30));
      pcVar2 = (char *)identity_972f0(uVar3);
      dos_read_blocks(*(undefined4 *)(param_1 + 0x24),pcVar2,2);
    }
    if ((*pcVar2 == '\0') && (pcVar2[1] == '\0')) {
      iVar4 = local_20 * local_1c;
      iVar1 = iVar4 + 2;
      if (*(int *)(param_1 + 0x24) == 0) {
        memmove_dwords(pcVar2 + 2,*(int *)(*(int *)(param_1 + 0x34) + 0x2c) + 0x10,iVar4);
      }
      else {
        dos_read_blocks(*(int *)(param_1 + 0x24),*(int *)(*(int *)(param_1 + 0x34) + 0x2c) + 0x10,
                        iVar4);
      }
    }
    else {
      if (*(int *)(param_1 + 0x24) == 0) {
        iVar1 = (uint)(byte)pcVar2[2] + (uint)(byte)pcVar2[3] * 0x100 +
                (uint)(byte)pcVar2[4] * 0x10000 + (uint)(byte)pcVar2[5] * 0x1000000;
        pcVar2 = pcVar2 + 6;
        local_10 = local_10 + 6;
      }
      else {
        dos_read_blocks(*(int *)(param_1 + 0x24),&local_24,4);
        iVar1 = (uint)local_24 + (uint)local_23 * 0x100 + (uint)local_22 * 0x10000 +
                (uint)local_21 * 0x1000000;
        uVar3 = memblock_ptr(*(undefined4 *)(param_1 + 0x30));
        pcVar2 = (char *)identity_972f0(uVar3);
        dos_read_blocks(*(undefined4 *)(param_1 + 0x24),pcVar2,iVar1);
        local_10 = pcVar2 + local_18;
      }
      iVar1 = iVar1 + 6;
      if (local_14 == 4) {
        mvi_decode_blocks(param_1,pcVar2,local_10);
        *(int *)(param_1 + 4) = *(int *)(param_1 + 4) + 1;
        *(int *)(param_1 + 0x2c) = *(int *)(param_1 + 0x2c) + iVar1;
        return *(undefined4 *)(*(int *)(param_1 + 0x34) + 0x2c);
      }
      mvi_decode_blocks_delta(param_1,pcVar2,local_10);
    }
    *(int *)(param_1 + 4) = *(int *)(param_1 + 4) + 1;
    *(int *)(param_1 + 0x2c) = *(int *)(param_1 + 0x2c) + iVar1;
    iVar1 = *(int *)(param_1 + 0x34);
  }
  else {
    iVar1 = *(int *)(param_1 + 0x34);
  }
  return *(undefined4 *)(iVar1 + 0x2c);
}


// ================================================================================================
// drv_open @ 0x97079 [__watcall]
// ================================================================================================

undefined8 __watcall drv_open(int param_1,undefined4 unaff_EDX)

{
  short sVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  undefined **ppuVar6;
  undefined4 *puVar7;
  
  if ((-1 < param_1) && (param_1 < 7)) {
    for (uVar2 = 0; (int)uVar2 < (int)dword_d4f64; uVar2 = uVar2 + 1) {
      if (param_1 == (&unk_edeb0)[uVar2 * 0xb]) goto LAB_0009715c;
    }
    if (dword_d4f64 == 0) {
      for (uVar2 = 0; uVar2 < 7; uVar2 = uVar2 + 1) {
        (&unk_d4bc8)[uVar2 * 0xb] = 0xffffffff;
      }
    }
    uVar2 = dword_d4f64;
    (&unk_d4bc8)[param_1 * 0xb] = dword_d4f64;
    ppuVar6 = &funcptr_d4ba0 + param_1 * 0xb;
    puVar7 = (undefined4 *)(&unk_ede88 + uVar2 * 0x2c);
    for (iVar4 = 0xb; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar7 = *ppuVar6;
      ppuVar6 = ppuVar6 + 1;
      puVar7 = puVar7 + 1;
    }
    (&unk_edeb0)[uVar2 * 0xb] = param_1;
    uVar5 = uVar2 & 0xff;
    uVar3 = drv_call_init(uVar5);
    sVar1 = drv_call_detect(uVar5,uVar3);
    if (sVar1 != 0) {
      drv_call_setup(uVar5,uVar3);
      (&unk_f243e)[uVar2] = (&unk_edeac)[uVar2 * 0x2c];
      iVar4 = drv_control(uVar5,7);
      if ((0 < iVar4) && (iVar4 < 100)) {
        dword_d4f96 = uVar2;
      }
      dword_d4f64 = dword_d4f64 + 1;
      goto LAB_0009715c;
    }
  }
  uVar2 = 0xffffffff;
LAB_0009715c:
  return CONCAT44(unaff_EDX,uVar2);
}


// ================================================================================================
// drv_index @ 0x97166 [__watcall]
// ================================================================================================

undefined4 __watcall drv_index(int param_1)

{
  if (dword_d4f64 < 1) {
    return 0xffffffff;
  }
  return (&unk_d4bc8)[param_1 * 0xb];
}


// ================================================================================================
// drv_call_init @ 0x9717f [__watcall]
// ================================================================================================

void __watcall
drv_call_init(uint param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  (**(code **)(&unk_ede88 + (param_1 & 0xff) * 0x2c))(unaff_EDX,unaff_ECX,unaff_EBX);
  return;
}


// ================================================================================================
// drv_call_detect @ 0x97194 [__watcall]
// ================================================================================================

void __watcall
drv_call_detect(uint param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  (**(code **)(&unk_ede8c + (param_1 & 0xff) * 0x2c))(unaff_EDX,unaff_ECX,unaff_EBX);
  return;
}


// ================================================================================================
// drv_call_setup @ 0x971ab [__watcall]
// ================================================================================================

void __watcall
drv_call_setup(uint param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  (**(code **)(&unk_ede90 + (param_1 & 0xff) * 0x2c))(unaff_EDX,unaff_ECX,unaff_EBX);
  return;
}


// ================================================================================================
// drv_reset @ 0x971be [__watcall]
// ================================================================================================

void __watcall
drv_reset(uint param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  if ((int)(param_1 & 0xff) < dword_d4f64) {
    (**(code **)(&unk_ede94 + (param_1 & 0xff) * 0x2c))(unaff_EDX,unaff_ECX,unaff_EBX);
  }
  return;
}


// ================================================================================================
// drv_tick @ 0x971db [__watcall]
// ================================================================================================

void __watcall drv_tick(uint param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  if ((int)(param_1 & 0xff) < dword_d4f64) {
    (**(code **)(&unk_ede98 + (param_1 & 0xff) * 0x2c))(unaff_EDX,unaff_ECX,unaff_EBX);
  }
  return;
}


// ================================================================================================
// drv_control @ 0x971f8 [__watcall]
// ================================================================================================

void __watcall
drv_control(uint param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  (**(code **)(&unk_ede9c + (param_1 & 0xff) * 0x2c))(unaff_EDX,unaff_ECX,unaff_EBX);
  return;
}


// ================================================================================================
// drv_channel_config @ 0x9720b [__watcall]
// ================================================================================================

void __watcall
drv_channel_config(uint param_1,undefined2 unaff_DX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  if ((int)(param_1 & 0xff) < dword_d4f64) {
    (**(code **)(&unk_edea0 + (param_1 & 0xff) * 0x2c))(unaff_DX,unaff_EBX,unaff_ECX);
  }
  return;
}


// ================================================================================================
// drv_send_midi @ 0x9722e [__watcall]
// ================================================================================================

void __watcall
drv_send_midi(byte param_1,undefined2 unaff_DX,undefined *unaff_EBX,undefined4 unaff_ECX)

{
  ushort uVar1;
  char cVar2;
  
  if ((int)(uint)param_1 < dword_d4f64) {
    uVar1 = CONCAT11(*unaff_EBX,param_1) & 0xf0ff;
    cVar2 = (char)(uVar1 >> 8);
    if ((cVar2 == -0x80) || (cVar2 == -0x70)) {
      unaff_EBX[1] = unaff_EBX[1] + '\x18';
    }
    (**(code **)(&unk_edea4 + (uVar1 & 0xff) * 0x2c))(unaff_DX,unaff_EBX,unaff_ECX);
  }
  return;
}


// ================================================================================================
// drv_play_sample @ 0x97268 [__watcall]
// ================================================================================================

void __watcall
drv_play_sample(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
               undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,
               undefined4 param_9,undefined4 param_10)

{
  if ((int)(param_1 & 0xff) < dword_d4f64) {
    (**(code **)(&unk_edea8 + (param_1 & 0xff) * 0x2c))
              (param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10);
  }
  return;
}


// ================================================================================================
// nulldrv_ret1 @ 0x972ab [__watcall]
// ================================================================================================

undefined4 __watcall nulldrv_ret1(void)

{
  empty_func_902a0();
  return 1;
}


// ================================================================================================
// nulldrv_nop1 @ 0x972b8 [__watcall]
// ================================================================================================

void __watcall nulldrv_nop1(void)

{
  empty_func_902a0();
  return;
}


// ================================================================================================
// nulldrv_nop2 @ 0x972c0 [__watcall]
// ================================================================================================

void __watcall nulldrv_nop2(void)

{
  empty_func_902a0();
  return;
}


// ================================================================================================
// nulldrv_retm1 @ 0x972c8 [__watcall]
// ================================================================================================

undefined4 __watcall nulldrv_retm1(void)

{
  empty_func_902a0();
  return 0xffffffff;
}


// ================================================================================================
// nulldrv_nop3 @ 0x972d5 [__watcall]
// ================================================================================================

void __watcall nulldrv_nop3(void)

{
  empty_func_902a0();
  return;
}


// ================================================================================================
// nulldrv_nop4 @ 0x972dd [__watcall]
// ================================================================================================

void __watcall nulldrv_nop4(void)

{
  empty_func_902a0();
  return;
}


// ================================================================================================
// nulldrv_nop5 @ 0x972e5 [__watcall]
// ================================================================================================

void __watcall nulldrv_nop5(void)

{
  empty_func_902a0();
  return;
}


// ================================================================================================
// identity_972f0 @ 0x972f0 [__cdecl]
// ================================================================================================

undefined4 identity_972f0(undefined4 param_1)

{
  return param_1;
}


// ================================================================================================
// return_zero_972f5 @ 0x972f5 [__watcall]
// ================================================================================================

undefined4 __watcall return_zero_972f5(void)

{
  return 0;
}


// ================================================================================================
// skip_copyright @ 0x97300 [__watcall]
// ================================================================================================

undefined8 __watcall skip_copyright(char *param_1,undefined4 unaff_EDX)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  char *pcVar4;
  
  iVar2 = strncmp(param_1,aCopyright,9);
  if (iVar2 == 0) {
    uVar3 = 0xffffffff;
    pcVar4 = param_1;
    do {
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      cVar1 = *pcVar4;
      pcVar4 = pcVar4 + 1;
    } while (cVar1 != '\0');
    param_1 = param_1 + ~uVar3;
  }
  return CONCAT44(unaff_EDX,param_1);
}


// ================================================================================================
// read_be_n @ 0x97334 [__watcall]
// ================================================================================================

int __watcall read_be_n(byte *param_1,int unaff_EDX)

{
  byte bVar1;
  int iVar2;
  
  iVar2 = 0;
  while (unaff_EDX = unaff_EDX + -1, unaff_EDX != -1) {
    bVar1 = *param_1;
    param_1 = param_1 + 1;
    iVar2 = iVar2 * 0x100 + (uint)bVar1;
  }
  return iVar2;
}


// ================================================================================================
// pack_type @ 0x97350 [__watcall]
// ================================================================================================

/* WARNING: Removing unreachable block (ram,0x0009752a) */
/* WARNING: Removing unreachable block (ram,0x000975b3) */

undefined8 __watcall
pack_type(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  byte bVar1;
  byte *pbVar2;
  undefined4 uVar3;
  
  pbVar2 = (byte *)skip_copyright(param_1,unaff_EDX,param_1,unaff_ECX,unaff_EDX,unaff_ECX,unaff_EBX)
  ;
  if (pbVar2[1] != 0xfb) {
    if ((((uint)*pbVar2 * 0x100 + (uint)pbVar2[1]) * 0x100 + (uint)pbVar2[2]) * 0x100 +
        (uint)pbVar2[3] == 0x3f3) {
      return CONCAT44(unaff_EDX,0x21);
    }
    uVar3 = 0;
    goto LAB_00097623;
  }
  bVar1 = *pbVar2 & 0xfe;
  if (bVar1 < 0x44) {
    if (bVar1 < 0x2c) {
      if (0x25 < bVar1) {
        if (0x26 < bVar1) {
          if (bVar1 < 0x28) goto LAB_000975e3;
          if (bVar1 < 0x29) goto LAB_00097578;
          if (bVar1 != 0x2a) {
            return CONCAT44(unaff_EDX,0x12);
          }
        }
        return CONCAT44(unaff_EDX,0x18);
      }
      if (bVar1 == 0x10) {
LAB_000974b8:
        return CONCAT44(unaff_EDX,0xc);
      }
    }
    else {
      if (bVar1 < 0x2d) {
        return CONCAT44(unaff_EDX,0x19);
      }
      if (bVar1 < 0x32) {
        if (0x2d < bVar1) {
          if (0x2e < bVar1) {
            if (bVar1 != 0x30) {
              return CONCAT44(unaff_EDX,0x12);
            }
            return CONCAT44(unaff_EDX,7);
          }
LAB_00097578:
          return CONCAT44(unaff_EDX,0x1a);
        }
      }
      else {
        if (bVar1 < 0x33) {
          return CONCAT44(unaff_EDX,9);
        }
        if (0x33 < bVar1) {
          if (bVar1 < 0x35) {
            return CONCAT44(unaff_EDX,10);
          }
          if (bVar1 != 0x42) {
            return CONCAT44(unaff_EDX,0x12);
          }
          goto LAB_0009758e;
        }
      }
    }
  }
  else {
    if (bVar1 < 0x45) {
LAB_0009758e:
      return CONCAT44(unaff_EDX,0x17);
    }
    if (bVar1 < 0x72) {
      if (bVar1 < 0x6a) {
        if (0x45 < bVar1) {
          if (bVar1 < 0x47) {
            return CONCAT44(unaff_EDX,5);
          }
          if (bVar1 != 0x66) {
            return CONCAT44(unaff_EDX,0x12);
          }
          return CONCAT44(unaff_EDX,0x1b);
        }
      }
      else {
        if (bVar1 < 0x6b) {
LAB_00097562:
          return CONCAT44(unaff_EDX,0x1f);
        }
        if (0x6d < bVar1) {
          if (bVar1 < 0x6f) {
            return CONCAT44(unaff_EDX,1);
          }
          if (bVar1 == 0x70) {
            return CONCAT44(unaff_EDX,0x11);
          }
          uVar3 = 0x12;
          goto LAB_00097623;
        }
      }
    }
    else {
      if (bVar1 < 0x73) {
        return CONCAT44(unaff_EDX,0xb);
      }
      if (bVar1 < 0x78) {
        if (0x73 < bVar1) {
          if (bVar1 < 0x75) {
            return CONCAT44(unaff_EDX,0x10);
          }
          if (bVar1 == 0x76) {
            uVar3 = 0x14;
            if ((pbVar2[5] == 1) && (pbVar2[6] == 1)) {
              uVar3 = 0x15;
            }
            if ((pbVar2[5] == 2) && (pbVar2[6] == 1)) {
              return CONCAT44(unaff_EDX,0x16);
            }
LAB_00097623:
            return CONCAT44(unaff_EDX,uVar3);
          }
        }
      }
      else {
        if (bVar1 < 0x79) goto LAB_000974b8;
        if (0x79 < bVar1) {
          if (bVar1 < 0x7b) {
            uVar3 = 2;
            if ((pbVar2[5] == 1) && (pbVar2[6] == 1)) {
              uVar3 = 3;
            }
            if ((pbVar2[5] == 2) && (pbVar2[6] == 1)) {
              return CONCAT44(unaff_EDX,4);
            }
            goto LAB_00097623;
          }
          if (bVar1 == 0xc0) goto LAB_00097562;
        }
      }
    }
  }
LAB_000975e3:
  return CONCAT44(unaff_EDX,0x12);
}


// ================================================================================================
// unpacked_size @ 0x9762c [__watcall]
// ================================================================================================

int __watcall unpacked_size(void)

{
  int iVar1;
  int iVar2;
  undefined8 uVar3;
  int in_stack_00000004;
  int in_stack_00000008;
  
  iVar1 = in_stack_00000008;
  if ((2 < in_stack_00000008) &&
     (iVar1 = (*(code *)funcptr_d3088)(in_stack_00000004,in_stack_00000008), iVar1 == 0)) {
    iVar2 = skip_copyright(in_stack_00000004);
    iVar1 = in_stack_00000008 - (iVar2 - in_stack_00000004);
    uVar3 = pack_type(iVar2);
    if ((0 < (int)uVar3) && ((int)uVar3 < 0x1f)) {
      iVar1 = read_be_n((int)((ulonglong)uVar3 >> 0x20) + 2,3);
      return iVar1;
    }
  }
  return iVar1;
}


// ================================================================================================
// bitlz_getbits @ 0x9767c [__watcall]
// ================================================================================================

undefined8 __watcall bitlz_getbits(int param_1,undefined4 unaff_EDX)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  undefined8 uVar4;
  
  if (param_1 < 0x11) {
    uVar3 = dword_edee4 >> (0x20 - (byte)param_1 & 0x1f);
    dword_edee4 = dword_edee4 << ((byte)param_1 & 0x1f);
    dword_edee0 = dword_edee0 - param_1;
    if (dword_edee0 < 0x10) {
      iVar2 = 0x18 - dword_edee0;
      do {
        bVar1 = *dword_edef0;
        dword_edef0 = dword_edef0 + 1;
        dword_edee4 = dword_edee4 | (uint)bVar1 << ((byte)iVar2 & 0x1f);
        iVar2 = iVar2 + -8;
        dword_edee0 = dword_edee0 + 8;
      } while (8 < iVar2);
    }
  }
  else {
    iVar2 = bitlz_getbits(param_1 + -0x10);
    uVar4 = bitlz_getbits(0x10,iVar2 << 0x10);
    uVar3 = (uint)uVar4 | (uint)((ulonglong)uVar4 >> 0x20);
  }
  return CONCAT44(unaff_EDX,uVar3);
}


// ================================================================================================
// bitlz_getgamma @ 0x97714 [__watcall]
// ================================================================================================

undefined8 __watcall bitlz_getgamma(undefined4 param_1,undefined4 unaff_EDX)

{
  int iVar1;
  int iVar2;
  undefined8 uVar3;
  
  iVar2 = 2;
  iVar1 = 1;
  do {
    iVar2 = iVar2 * 2;
    uVar3 = bitlz_getbits(1,iVar1 + 1);
    iVar1 = (int)((ulonglong)uVar3 >> 0x20);
  } while ((int)uVar3 == 0);
  iVar1 = bitlz_getbits(iVar1);
  return CONCAT44(unaff_EDX,iVar1 + iVar2 + -4);
}


// ================================================================================================
// bitlz_decode @ 0x97740 [__watcall]
// ================================================================================================

int __watcall bitlz_decode(byte *param_1,char *unaff_EDX,int unaff_EBX)

{
  char cVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  char *pcVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  undefined8 uVar12;
  char acStack_2e8 [256];
  char acStack_1e8 [256];
  int aiStack_e8 [16];
  int aiStack_a8 [16];
  uint auStack_68 [16];
  int local_28;
  int local_24;
  uint local_1c;
  
  local_24 = 0;
  dword_edee8 = unaff_EDX;
  dword_edef0 = param_1;
  if (param_1 != (byte *)0x0) {
    dword_edef0 = param_1 + 2;
    local_1c = (uint)*param_1 * 0x100 + (uint)param_1[1];
    if ((local_1c & 0x100) != 0) {
      dword_edef0 = param_1 + 5;
    }
    local_1c = local_1c & 0xfffffeff;
    iVar10 = 0;
    dword_edee0 = 0;
    dword_edee4 = 0;
    bitlz_getbits(0);
    local_24 = bitlz_getbits(0x18);
    if (unaff_EBX != 0) {
      cVar1 = bitlz_getbits(8);
      iVar7 = 0;
      local_28 = 0xf;
      iVar8 = 4;
      iVar9 = 1;
      do {
        iVar11 = iVar9;
        *(int *)((int)aiStack_a8 + iVar8) = iVar7 * 2 - iVar10;
        uVar12 = bitlz_getgamma();
        iVar3 = (int)uVar12;
        *(int *)((int)aiStack_e8 + iVar8) = iVar3;
        iVar10 = iVar10 + iVar3;
        iVar7 = (int)((ulonglong)uVar12 >> 0x20) + iVar3;
        uVar6 = 0;
        if (iVar3 != 0) {
          uVar6 = iVar7 << ((byte)local_28 & 0x1f) & 0xffff;
        }
        *(uint *)((int)auStack_68 + iVar8) = uVar6;
        local_28 = local_28 + -1;
        iVar8 = iVar8 + 4;
        iVar9 = iVar11 + 1;
      } while ((iVar3 == 0) || (uVar6 != 0));
      uVar4 = _memset_fill(acStack_2e8,0,iVar8,0x100);
      uVar6 = 0xffffffff;
      iVar9 = 0;
      if (0 < iVar10) {
        do {
          uVar12 = bitlz_getgamma(uVar4,uVar6);
          uVar6 = (uint)((ulonglong)uVar12 >> 0x20);
          iVar7 = (int)uVar12 + 1;
          while (iVar7 != 0) {
            uVar6 = uVar6 + 1 & 0xff;
            if (acStack_2e8[uVar6] == '\0') {
              iVar7 = iVar7 + -1;
            }
          }
          acStack_2e8[uVar6] = '\x01';
          acStack_1e8[iVar9] = (char)uVar6;
          iVar9 = iVar9 + 1;
          uVar4 = 0;
        } while (iVar9 < iVar10);
      }
      while( true ) {
        while( true ) {
          while( true ) {
            iVar10 = 1;
            uVar6 = auStack_68[1];
            for (iVar9 = 4;
                (uVar6 <= dword_edee4 >> 0x10 &&
                (SBORROW4(iVar9,iVar11 * 4) != iVar9 + iVar11 * -4 < 0)); iVar9 = iVar9 + 4) {
              iVar10 = iVar10 + 1;
              uVar6 = *(uint *)((int)auStack_68 + iVar9 + 4);
            }
            uVar12 = bitlz_getbits(iVar10);
            if (acStack_1e8[(int)uVar12 - aiStack_a8[(int)((ulonglong)uVar12 >> 0x20)]] == cVar1)
            break;
            *dword_edee8 = acStack_1e8[(int)uVar12 - aiStack_a8[(int)((ulonglong)uVar12 >> 0x20)]];
            dword_edee8 = dword_edee8 + 1;
          }
          iVar10 = bitlz_getgamma();
          if (iVar10 == 0) break;
          cVar2 = dword_edee8[-1];
          while (iVar10 = iVar10 + -1, iVar10 != -1) {
            *dword_edee8 = cVar2;
            dword_edee8 = dword_edee8 + 1;
          }
        }
        iVar10 = bitlz_getbits(1);
        if (iVar10 != 0) break;
        cVar2 = bitlz_getbits(8);
        *dword_edee8 = cVar2;
        dword_edee8 = dword_edee8 + 1;
      }
      pcVar5 = unaff_EDX + local_24;
      if (local_1c == 0x32fb) {
        cVar1 = '\0';
        dword_edee8 = unaff_EDX;
        if (unaff_EDX < pcVar5) {
          do {
            cVar1 = cVar1 + *dword_edee8;
            *dword_edee8 = cVar1;
            dword_edee8 = dword_edee8 + 1;
          } while (dword_edee8 < pcVar5);
        }
      }
      else if (local_1c == 0x34fb) {
        cVar2 = '\0';
        cVar1 = '\0';
        dword_edee8 = unaff_EDX;
        if (unaff_EDX < pcVar5) {
          do {
            cVar2 = cVar2 + *dword_edee8;
            cVar1 = cVar1 + cVar2;
            *dword_edee8 = cVar1;
            dword_edee8 = dword_edee8 + 1;
          } while (dword_edee8 < pcVar5);
        }
      }
    }
  }
  return local_24;
}


// ================================================================================================
// bytepair_expand @ 0x979f8 [__watcall]
// ================================================================================================

void __watcall bytepair_expand(byte param_1)

{
  int extraout_EDX;
  
  while( true ) {
    if (*(char *)((uint)param_1 + dword_edef8) == '\0') break;
    bytepair_expand(*(undefined *)((uint)param_1 + dword_edeec));
    param_1 = *(byte *)(extraout_EDX + dword_edef4);
  }
  *dword_edee8 = param_1;
  dword_edee8 = dword_edee8 + 1;
  return;
}


// ================================================================================================
// bytepair_decode @ 0x97a38 [__watcall]
// ================================================================================================

int __watcall bytepair_decode(byte *param_1,byte *unaff_EDX)

{
  byte bVar1;
  byte bVar2;
  undefined *puVar3;
  int iVar4;
  int extraout_EDX;
  byte *pbVar5;
  undefined auStack_318 [256];
  undefined local_218 [256];
  undefined local_118 [256];
  int local_18;
  
  dword_edef4 = auStack_318;
  local_18 = 0;
  dword_edef8 = local_118;
  dword_edeec = local_218;
  dword_edee8 = unaff_EDX;
  if (param_1 != (byte *)0x0) {
    pbVar5 = param_1 + 2;
    if ((uint)*param_1 * 0x100 + (uint)param_1[1] == 0x47fb) {
      pbVar5 = param_1 + 5;
    }
    local_18 = ((uint)*pbVar5 * 0x100 + (uint)pbVar5[1]) * 0x100 + (uint)pbVar5[2];
    iVar4 = 0;
    dword_edef4 = auStack_318;
    do {
      puVar3 = dword_edef8;
      dword_edef8[iVar4] = 0;
      iVar4 = iVar4 + 1;
    } while (iVar4 < 0x100);
    puVar3[pbVar5[3]] = 1;
    bVar2 = pbVar5[4];
    iVar4 = 0;
    dword_edef0 = pbVar5 + 5;
    if (bVar2 != 0) {
      do {
        bVar1 = *dword_edef0;
        pbVar5 = dword_edef0 + 2;
        dword_edeec[bVar1] = dword_edef0[1];
        dword_edef0 = dword_edef0 + 3;
        dword_edef4[bVar1] = *pbVar5;
        dword_edef8[bVar1] = 0xff;
        iVar4 = iVar4 + 1;
      } while (iVar4 < (int)(uint)bVar2);
    }
    while( true ) {
      while( true ) {
        while( true ) {
          bVar2 = *dword_edef0;
          pbVar5 = dword_edef0 + 1;
          if (dword_edef8[bVar2] != '\0') break;
          *dword_edee8 = bVar2;
          dword_edee8 = dword_edee8 + 1;
          dword_edef0 = pbVar5;
        }
        if (-1 < (char)dword_edef8[bVar2]) break;
        dword_edef0 = pbVar5;
        bytepair_expand(dword_edeec[bVar2]);
        bytepair_expand(dword_edef4[extraout_EDX]);
      }
      param_1 = dword_edef0 + 2;
      if (*pbVar5 == 0) break;
      *dword_edee8 = *pbVar5;
      dword_edee8 = dword_edee8 + 1;
      dword_edef0 = param_1;
    }
  }
  dword_edef0 = param_1;
  return local_18;
}


// ================================================================================================
// delta_decode @ 0x97bb8 [__watcall]
// ================================================================================================

int __watcall delta_decode(byte *param_1,char *unaff_EDX)

{
  char *pcVar1;
  byte bVar2;
  byte *pbVar3;
  byte *pbVar4;
  char cVar5;
  int iVar6;
  
  iVar6 = 0;
  if (param_1 != (byte *)0x0) {
    pbVar3 = param_1 + 2;
    iVar6 = (uint)*param_1 * 0x100 + (uint)param_1[1];
    if (iVar6 == 0x62fb) {
      pbVar3 = param_1 + 5;
    }
    else if (iVar6 == 0x66fb) {
      pbVar3 = param_1 + 6;
    }
    pbVar4 = pbVar3 + 3;
    iVar6 = ((uint)*pbVar3 * 0x100 + (uint)pbVar3[1]) * 0x100 + (uint)pbVar3[2];
    pcVar1 = unaff_EDX + iVar6;
    cVar5 = '\0';
    if (unaff_EDX < pcVar1) {
      do {
        bVar2 = *pbVar4;
        pbVar4 = pbVar4 + 1;
        cVar5 = cVar5 + bVar2;
        *unaff_EDX = cVar5;
        unaff_EDX = unaff_EDX + 1;
      } while (unaff_EDX < pcVar1);
    }
  }
  return iVar6;
}


// ================================================================================================
// pack7a_decode @ 0x97c2c [__watcall]
// ================================================================================================

int __watcall pack7a_decode(byte *param_1,byte *unaff_EDX)

{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  int local_1c;
  
  local_1c = 0;
  if (param_1 != (byte *)0x0) {
    pbVar2 = param_1 + 2;
    if ((uint)*param_1 * 0x100 + (uint)param_1[1] == 0x7bfb) {
      pbVar2 = param_1 + 5;
    }
    local_1c = ((uint)*pbVar2 * 0x100 + (uint)pbVar2[1]) * 0x100 + (uint)pbVar2[2];
    uVar5 = (uint)pbVar2[3];
    bVar1 = pbVar2[4];
    pbVar2 = pbVar2 + 5;
    do {
      iVar6 = (int)(char)*pbVar2;
      uVar4 = (uint)bVar1;
      while( true ) {
        uVar4 = uVar4 - 1;
        pbVar2 = pbVar2 + 1;
        if (uVar4 == 0) break;
        iVar6 = iVar6 * 0x100 + (uint)*pbVar2;
      }
      if (iVar6 < 0) {
        iVar3 = -iVar6 * uVar5;
        do {
          *unaff_EDX = *pbVar2;
          pbVar2 = pbVar2 + 1;
          unaff_EDX = unaff_EDX + 1;
          iVar3 = iVar3 + -1;
        } while (iVar3 != 0);
      }
      else if (iVar6 != 0) {
        iVar3 = iVar6 + 1;
        uVar4 = uVar5;
        do {
          do {
            *unaff_EDX = *pbVar2;
            pbVar2 = pbVar2 + 1;
            unaff_EDX = unaff_EDX + 1;
            uVar4 = uVar4 - 1;
          } while (uVar4 != 0);
          pbVar2 = pbVar2 + -uVar5;
          iVar3 = iVar3 + -1;
          uVar4 = uVar5;
        } while (iVar3 != 0);
        pbVar2 = pbVar2 + uVar5;
      }
    } while (iVar6 != 0);
  }
  return local_1c;
}


// ================================================================================================
// refpack_decode @ 0x97ce0 [__watcall]
// ================================================================================================

int __watcall refpack_decode(byte *param_1,byte *unaff_EDX,int unaff_EBX)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  uint uVar5;
  byte *pbVar6;
  byte *pbVar7;
  uint uVar8;
  int iVar9;
  int local_1c;
  
  local_1c = 0;
  if (param_1 != (byte *)0x0) {
    pbVar6 = param_1 + 2;
    if (((uint)*param_1 * 0x100 + (uint)param_1[1] & 0x100) != 0) {
      pbVar6 = param_1 + 5;
    }
    pbVar7 = pbVar6 + 3;
    local_1c = ((uint)*pbVar6 * 0x100 + (uint)pbVar6[1]) * 0x100 + (uint)pbVar6[2];
    if (unaff_EBX != 0) {
      while( true ) {
        while( true ) {
          while( true ) {
            while( true ) {
              bVar2 = *pbVar7;
              uVar8 = (uint)bVar2;
              pbVar6 = pbVar7 + 1;
              uVar5 = uVar8 & 3;
              if ((bVar2 & 0x80) != 0) break;
              bVar3 = *pbVar6;
              pbVar7 = pbVar7 + 2;
              if ((bVar2 & 3) != 0) {
                do {
                  *unaff_EDX = *pbVar7;
                  pbVar7 = pbVar7 + 1;
                  unaff_EDX = unaff_EDX + 1;
                  uVar5 = uVar5 - 1;
                } while (uVar5 != 0);
              }
              pbVar6 = unaff_EDX + -((uVar8 & 0x60) * 8 + (uint)bVar3 + 1);
              iVar9 = ((uVar8 & 0x1c) >> 2) + 1;
              *unaff_EDX = *pbVar6;
              unaff_EDX[1] = pbVar6[1];
              pbVar6 = pbVar6 + 2;
              unaff_EDX = unaff_EDX + 2;
              do {
                *unaff_EDX = *pbVar6;
                pbVar6 = pbVar6 + 1;
                unaff_EDX = unaff_EDX + 1;
                iVar9 = iVar9 + -1;
              } while (iVar9 != 0);
            }
            if ((bVar2 & 0x40) != 0) break;
            bVar2 = *pbVar6;
            bVar3 = pbVar7[2];
            pbVar7 = pbVar7 + 3;
            for (uVar5 = (uint)(bVar2 >> 6); uVar5 != 0; uVar5 = uVar5 - 1) {
              *unaff_EDX = *pbVar7;
              pbVar7 = pbVar7 + 1;
              unaff_EDX = unaff_EDX + 1;
            }
            pbVar6 = unaff_EDX + -((bVar2 & 0x3f) * 0x100 + (uint)bVar3 + 1);
            iVar9 = (uVar8 & 0x3f) + 1;
            *unaff_EDX = *pbVar6;
            unaff_EDX[1] = pbVar6[1];
            unaff_EDX[2] = pbVar6[2];
            pbVar6 = pbVar6 + 3;
            unaff_EDX = unaff_EDX + 3;
            do {
              *unaff_EDX = *pbVar6;
              pbVar6 = pbVar6 + 1;
              unaff_EDX = unaff_EDX + 1;
              iVar9 = iVar9 + -1;
            } while (iVar9 != 0);
          }
          if ((bVar2 & 0x20) != 0) break;
          bVar3 = *pbVar6;
          bVar1 = pbVar7[2];
          bVar4 = pbVar7[3];
          pbVar7 = pbVar7 + 4;
          if ((bVar2 & 3) != 0) {
            do {
              *unaff_EDX = *pbVar7;
              pbVar7 = pbVar7 + 1;
              unaff_EDX = unaff_EDX + 1;
              uVar5 = uVar5 - 1;
            } while (uVar5 != 0);
          }
          pbVar6 = unaff_EDX +
                   -(((uVar8 & 0x10) >> 4) * 0x10000 + (uint)bVar3 * 0x100 + (uint)bVar1 + 1);
          iVar9 = ((uVar8 & 0xc) >> 2) * 0x100 + (uint)bVar4 + 1;
          *unaff_EDX = *pbVar6;
          unaff_EDX[1] = pbVar6[1];
          unaff_EDX[2] = pbVar6[2];
          unaff_EDX[3] = pbVar6[3];
          pbVar6 = pbVar6 + 4;
          unaff_EDX = unaff_EDX + 4;
          do {
            *unaff_EDX = *pbVar6;
            pbVar6 = pbVar6 + 1;
            unaff_EDX = unaff_EDX + 1;
            iVar9 = iVar9 + -1;
          } while (iVar9 != 0);
        }
        if (0xfb < uVar8) break;
        iVar9 = (uVar8 & 0x1f) + 1;
        pbVar7 = pbVar6;
        do {
          *unaff_EDX = *pbVar7;
          unaff_EDX[1] = pbVar7[1];
          unaff_EDX[2] = pbVar7[2];
          unaff_EDX[3] = pbVar7[3];
          pbVar7 = pbVar7 + 4;
          unaff_EDX = unaff_EDX + 4;
          iVar9 = iVar9 + -1;
        } while (iVar9 != 0);
      }
      if ((bVar2 & 3) != 0) {
        do {
          *unaff_EDX = *pbVar6;
          pbVar6 = pbVar6 + 1;
          unaff_EDX = unaff_EDX + 1;
          uVar5 = uVar5 - 1;
        } while (uVar5 != 0);
      }
    }
  }
  return local_1c;
}


// ================================================================================================
// unpack @ 0x97eb8 [__cdecl]
// ================================================================================================

int unpack(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  byte bVar1;
  int iVar2;
  byte *pbVar3;
  int local_10;
  
  iVar2 = (*(code *)funcptr_d308c)(param_1,param_2,param_3);
  if (iVar2 != 0) {
    return iVar2;
  }
  local_10 = unpacked_size();
  pbVar3 = (byte *)skip_copyright(param_1);
  iVar2 = 0;
  if (pbVar3[1] != 0xfb) goto LAB_00098009;
  bVar1 = *pbVar3 & 0xfe;
  if (0x5f < bVar1) {
    if (0x60 < bVar1) {
      if (0x69 < bVar1) {
        if (bVar1 < 0x6b) {
LAB_00097fcb:
          memmove_dwords(pbVar3 + 5,param_2,local_10);
          iVar2 = local_10;
          goto LAB_00098009;
        }
        if (bVar1 < 0x72) {
          if (bVar1 == 0x6e) goto LAB_00097fcb;
        }
        else {
          if (bVar1 < 0x73) goto LAB_00097fbe;
          if ((0x79 < bVar1) && (bVar1 < 0x7c)) {
            local_10 = pack7a_decode(pbVar3,param_2);
            goto LAB_00098009;
          }
        }
        goto LAB_00097fef;
      }
      if ((bVar1 < 0x62) || ((0x62 < bVar1 && (bVar1 != 0x66)))) goto LAB_00097fef;
    }
LAB_00097fbe:
    iVar2 = delta_decode(pbVar3,param_2);
    goto LAB_00098009;
  }
  if (bVar1 < 0x32) {
    if (0xf < bVar1) {
      if (bVar1 < 0x11) {
        iVar2 = refpack_decode(pbVar3,param_2,1);
        goto LAB_00098009;
      }
      if (bVar1 == 0x30) goto LAB_00097f9f;
    }
  }
  else {
    if (bVar1 < 0x33) {
LAB_00097f9f:
      iVar2 = bitlz_decode(pbVar3,param_2,1);
      goto LAB_00098009;
    }
    if (0x33 < bVar1) {
      if (bVar1 < 0x35) goto LAB_00097f9f;
      if (bVar1 == 0x46) {
        iVar2 = bytepair_decode(pbVar3,param_2);
        goto LAB_00098009;
      }
    }
  }
LAB_00097fef:
  if (param_4 != 0) {
    fatalerror(s_funpack___INVALID_PACK_CODE___x__000c47c2 + 2,*pbVar3);
  }
LAB_00098009:
  if (iVar2 == 0) {
    memmove_dwords(pbVar3,param_2,local_10);
    iVar2 = local_10;
  }
  return iVar2;
}


// ================================================================================================
// unpack_fatal @ 0x98028 [__cdecl]
// ================================================================================================

void unpack_fatal(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  unpack(param_1,param_2,param_3,1);
  return;
}


// ================================================================================================
// unpack_try @ 0x98044 [__watcall]
// ================================================================================================

void __watcall unpack_try(void)

{
  undefined4 in_stack_00000004;
  undefined4 in_stack_00000008;
  undefined4 in_stack_0000000c;
  
  unpack(in_stack_00000004,in_stack_00000008,in_stack_0000000c,0);
  return;
}


// ================================================================================================
// memmove_fs @ 0x9805e [__watcall]
// ================================================================================================

undefined8 __watcall
memmove_fs(undefined2 *param_1,undefined4 unaff_EDX,undefined2 *unaff_EBX,short unaff_CX,
          uint param_5)

{
  undefined2 *puVar1;
  uint uVar2;
  int in_FS_OFFSET;
  
  if ((unaff_EBX != param_1) || (unaff_CX != (short)unaff_EDX)) {
    if ((unaff_EBX < param_1) &&
       (puVar1 = (undefined2 *)((int)unaff_EBX + param_5), param_1 < puVar1)) {
      param_1 = (undefined2 *)((int)param_1 + param_5);
      for (; param_5 != 0; param_5 = param_5 - 1) {
        puVar1 = (undefined2 *)((int)puVar1 - 1);
        param_1 = (undefined2 *)((int)param_1 + -1);
        *(undefined *)(in_FS_OFFSET + (int)param_1) = *(undefined *)puVar1;
      }
    }
    else {
      puVar1 = param_1;
      for (uVar2 = param_5 >> 1; uVar2 != 0; uVar2 = uVar2 - 1) {
        *puVar1 = *unaff_EBX;
        unaff_EBX = unaff_EBX + 1;
        puVar1 = puVar1 + 1;
      }
      for (uVar2 = (uint)((param_5 & 1) != 0); uVar2 != 0; uVar2 = uVar2 - 1) {
        *(undefined *)puVar1 = *(undefined *)unaff_EBX;
        unaff_EBX = (undefined2 *)((int)unaff_EBX + 1);
        puVar1 = (undefined2 *)((int)puVar1 + 1);
      }
    }
  }
  return CONCAT44(unaff_EDX,param_1);
}


// ================================================================================================
// utoa @ 0x980e5 [__watcall]
// ================================================================================================

char * __watcall utoa(uint param_1,char *unaff_EDX,uint unaff_EBX)

{
  char cVar1;
  uint uVar2;
  char *pcVar3;
  char *pcVar4;
  char local_37 [35];
  
  pcVar3 = local_37;
  do {
    uVar2 = param_1 / unaff_EBX;
    *pcVar3 = "0123456789abcdefghijklmnopqrstuvwxyz"[param_1 % unaff_EBX];
    pcVar3 = pcVar3 + 1;
    param_1 = uVar2;
    pcVar4 = unaff_EDX;
  } while (uVar2 != 0);
  do {
    pcVar3 = pcVar3 + -1;
    cVar1 = *pcVar3;
    *pcVar4 = cVar1;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  return unaff_EDX;
}


// ================================================================================================
// itoa @ 0x9812f [__watcall]
// ================================================================================================

undefined * __watcall itoa(int param_1,undefined *unaff_EDX,int unaff_EBX)

{
  if ((unaff_EBX == 10) && (param_1 < 0)) {
    param_1 = -param_1;
    *unaff_EDX = 0x2d;
  }
  utoa(param_1);
  return unaff_EDX;
}


// ================================================================================================
// fgets @ 0x9814a [__watcall]
// ================================================================================================

char * __watcall fgets(char *__s,int __n,FILE *__stream)

{
  char *pcVar1;
  char *pcVar2;
  int local_14;
  
  pcVar1 = __stream->_IO_read_base;
  *(byte *)&__stream->_IO_read_base = *(byte *)&__stream->_IO_read_base & 0xcf;
  pcVar2 = __s;
  do {
    __n = __n + -1;
    if (__n < 1) break;
    local_14 = fgetc(__stream);
    if (local_14 == -1) break;
    *pcVar2 = (char)local_14;
    pcVar2 = pcVar2 + 1;
  } while ((char)local_14 != '\n');
  if ((local_14 == -1) && ((pcVar2 == __s || ((*(byte *)&__stream->_IO_read_base & 0x20) != 0)))) {
    __s = (char *)0x0;
  }
  else {
    *pcVar2 = '\0';
  }
  __stream->_IO_read_base = (char *)((uint)__stream->_IO_read_base | (uint)pcVar1 & 0x30);
  return __s;
}


// ================================================================================================
// empty_func_981ad @ 0x981ad [__watcall]
// ================================================================================================

void __watcall empty_func_981ad(void)

{
  return;
}


// ================================================================================================
// msgbox_save_background @ 0x981b0 [__watcall]
// ================================================================================================

void __watcall msgbox_save_background(int param_1,undefined4 unaff_EDX,undefined4 unaff_EBX)

{
  setdefaultscreen();
  grabshape(*(undefined4 *)(param_1 + 0x2c),unaff_EDX,unaff_EBX);
  return;
}


// ================================================================================================
// msgbox_restore_background @ 0x981d4 [__watcall]
// ================================================================================================

void __watcall msgbox_restore_background(int param_1,undefined4 unaff_EDX,undefined4 unaff_EBX)

{
  setdefaultscreen();
  drawshape2(*(undefined4 *)(param_1 + 0x2c),unaff_EDX,unaff_EBX);
  return;
}


// ================================================================================================
// msgbox_yesno @ 0x981f8 [__watcall]
// ================================================================================================

uint __watcall
msgbox_yesno(undefined4 param_1,int param_2,int unaff_EBX,int unaff_ECX,int param_5,uint param_6)

{
  undefined4 uVar1;
  uint uVar2;
  uint uVar3;
  undefined auStack_cc [96];
  undefined local_6c [64];
  int local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  
  dword_d2fd8 = 1;
  local_28 = param_1;
  (*(code *)funcptr_d45b4)();
  local_24 = return_zero_9c5a8();
  return_zero_9c5a8();
  uVar1 = windowdefp(unaff_ECX,param_5,0);
  local_20 = uVar1;
  save_screen_state(auStack_cc);
  getfontstate(local_6c);
  setfont(&unk_d45d8);
  local_2c = param_2 + unaff_ECX;
  window_setclip(&dword_d30d4,param_2,local_2c,unaff_EBX,unaff_EBX + param_5);
  (*(code *)funcptr_d3070)();
  setscreen(uVar1);
  msgbox_save_background(uVar1,param_2,unaff_EBX);
  setdefaultscreen();
  uVar1 = palette_closest(0);
  fillrect(param_2,unaff_EBX,unaff_ECX,param_5,uVar1);
  uVar1 = palette_closest(0xa80000);
  fillbox_corners(param_2 + 4,unaff_EBX + 4,local_2c + -5,unaff_EBX + param_5 + -4,uVar1);
  uVar1 = palette_closest(0xfcfcfc,0);
  settextpos(uVar1);
  printstr_centered(local_28,unaff_EBX + 9);
  (*(code *)funcptr_d3074)();
  window_clip_full(&dword_d30d4);
  do {
    uVar2 = (*(code *)mouse_update_callback)();
  } while ((uVar2 & param_6) != 0);
  do {
    uVar2 = key_poll();
    uVar3 = (*(code *)mouse_update_callback)();
    if (uVar2 != 0) break;
  } while ((uVar3 & param_6) == 0);
  uVar3 = uVar3 & param_6 & 1;
  if ((uVar2 | 0x20) == 0x79) {
    uVar3 = 1;
  }
  window_setclip(&dword_d30d4,param_2,param_2 + unaff_ECX,unaff_EBX,unaff_EBX + param_5);
  (*(code *)funcptr_d306c)();
  msgbox_restore_background(local_20,param_2,unaff_EBX);
  (*(code *)funcptr_d3074)();
  setfontstate(local_6c);
  restore_screen_state(auStack_cc);
  removewindow_free(local_20);
  return_zero_9c5a8();
  (*(code *)funcptr_d45b8)();
  dword_d2fd8 = 0;
  return uVar3;
}


// ================================================================================================
// exit_to_dos_prompt @ 0x984a8 [__watcall]
// ================================================================================================

void __watcall exit_to_dos_prompt(void)

{
  int iVar1;
  
  iVar1 = msgbox_yesno(aEXITTODOSYN,0x50,0x58,0xa0,0x18,7);
  if (iVar1 != 0) {
    (*(code *)funcptr_d41f0)();
  }
  return;
}


// ================================================================================================
// msgbox @ 0x984d0 [__cdecl]
// ================================================================================================

void msgbox(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined auStack_a8 [96];
  undefined local_48 [64];
  
  dword_d2fd8 = 1;
  return_zero_9c5a8();
  return_zero_9c5a8();
  uVar1 = windowdefp(0x140,10,0);
  save_screen_state(auStack_a8);
  getfontstate(local_48);
  setfont(&unk_d45d8);
  setscreen(uVar1);
  window_setclip(&dword_d30d4,0,0x140,0xbe,200);
  (*(code *)funcptr_d3070)();
  msgbox_save_background(uVar1,0,0xbe);
  setdefaultscreen();
  uVar2 = palette_closest(0);
  fillrect(0,0xbe,0x140,10,uVar2);
  uVar2 = palette_closest(0xfcfcfc,0);
  settextpos(uVar2);
  printstr_centered(param_1,0xbf);
  (*(code *)funcptr_d3074)();
  spin_wait_b(param_2);
  (*(code *)funcptr_d306c)();
  msgbox_restore_background(uVar1,0,0xbe);
  (*(code *)funcptr_d3074)();
  setfontstate(local_48);
  restore_screen_state(auStack_a8);
  removewindow_free(uVar1);
  return_zero_9c5a8();
  dword_d2fd8 = 0;
  return;
}


// ================================================================================================
// debug_pause @ 0x9862c [__watcall]
// ================================================================================================

void __watcall debug_pause(void)

{
  msgbox_yesno(s_izPAUSE___PRESS_ANY_KEY_TO_RESUM_000c47fa + 2,0x10,0x58,0x120,0x18,1);
  return;
}


// ================================================================================================
// dos_getvect @ 0x9864c [__watcall]
// ================================================================================================

undefined6 __watcall dos_getvect(undefined4 param_1,undefined4 param_2,undefined4 unaff_EBX)

{
  code *pcVar1;
  undefined2 in_ES;
  
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  return CONCAT24(in_ES,unaff_EBX);
}


// ================================================================================================
// dos_setvect @ 0x98664 [__watcall]
// ================================================================================================

undefined8 __watcall dos_setvect(undefined4 param_1)

{
  code *pcVar1;
  undefined4 unaff_EBP;
  
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  return CONCAT44(param_1,unaff_EBP);
}


// ================================================================================================
// __fatal_runtime_error @ 0x98683 [__watcall]
// ================================================================================================

void __watcall __fatal_runtime_error(undefined4 param_1,undefined4 unaff_EDX)

{
  int iVar1;
  undefined4 *puVar2;
  undefined2 in_DS;
  undefined4 uStack_c;
  
  puVar2 = &uStack_c;
  uStack_c = 0x98690;
  iVar1 = debug_break(param_1,in_DS);
  if (iVar1 == 0) {
                    /* WARNING: Subroutine does not return */
    *(undefined4 *)((int)puVar2 + -4) = 0x9869d;
    __do_exit_with_msg(param_1,unaff_EDX);
  }
  return;
}


// ================================================================================================
// unk_986a0 @ 0x986a0
// ================================================================================================

void unk_986a0(void)

{
  return;
}


// ================================================================================================
// memman_lock_init @ 0x986b0 [__watcall]
// ================================================================================================

undefined4 * __watcall memman_lock_init(void)

{
  dword_edefc = 0;
  return &dword_edefc;
}


// ================================================================================================
// memman_lock @ 0x986c0 [__cdecl]
// ================================================================================================

void memman_lock(undefined4 *param_1)

{
  *param_1 = 1;
  return;
}


// ================================================================================================
// lock_try @ 0x986cc [__cdecl]
// ================================================================================================

undefined4 lock_try(int *param_1)

{
  if (*param_1 != 0) {
    return 0;
  }
  *param_1 = 1;
  return 1;
}


// ================================================================================================
// memman_unlock @ 0x986e4 [__cdecl]
// ================================================================================================

void memman_unlock(undefined4 *param_1)

{
  *param_1 = 0;
  return;
}


// ================================================================================================
// vfprintf_putc @ 0x986ef [__watcall]
// ================================================================================================

void __watcall vfprintf_putc(undefined4 *param_1,int unaff_EDX)

{
  fputc(unaff_EDX,(FILE *)*param_1);
  param_1[4] = param_1[4] + 1;
  return;
}


// ================================================================================================
// vfprintf @ 0x98700 [__cdecl]
// ================================================================================================

int __watcall vfprintf(FILE *__s,char *__format,__gnuc_va_list __arg)

{
  char *pcVar1;
  int iVar2;
  byte bVar3;
  int extraout_EDX;
  bool bVar4;
  
  pcVar1 = __s->_IO_read_base;
  *(byte *)&__s->_IO_read_base = *(byte *)&__s->_IO_read_base & 0xcf;
  if (__s->_IO_read_end == (char *)0x0) {
    __ioalloc(__s);
  }
  bVar3 = *(byte *)((int)&__s->_IO_read_base + 1);
  bVar4 = (bVar3 & 4) != 0;
  if (bVar4) {
    bVar3 = bVar3 & 0xfa;
    *(byte *)((int)&__s->_IO_read_base + 1) = bVar3;
    *(byte *)((int)&__s->_IO_read_base + 1) = bVar3 | 1;
  }
  iVar2 = __prtf(__s);
  if (bVar4) {
    bVar3 = *(byte *)((int)&__s->_IO_read_base + 1);
    *(byte *)((int)&__s->_IO_read_base + 1) = bVar3 & 0xfa;
    *(byte *)((int)&__s->_IO_read_base + 1) = bVar3 & 0xfa | 4;
    __flush(__s);
    iVar2 = extraout_EDX;
  }
  if ((*(byte *)&__s->_IO_read_base & 0x20) != 0) {
    iVar2 = -1;
  }
  __s->_IO_read_base = (char *)((uint)__s->_IO_read_base | (uint)pcVar1 & 0x30);
  return iVar2;
}


// ================================================================================================
// __set_errno @ 0x9878a [__watcall]
// ================================================================================================

void __watcall
__set_errno(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  undefined8 uVar1;
  
  uVar1 = __get_errno_ptr(param_1,param_1,unaff_EBX,unaff_ECX,unaff_EDX);
  *(undefined4 *)uVar1 = (int)((ulonglong)uVar1 >> 0x20);
  return;
}


// ================================================================================================
// __set_ERANGE @ 0x98796 [__watcall]
// ================================================================================================

void __watcall __set_ERANGE(void)

{
  __set_errno(0xe);
  return;
}


// ================================================================================================
// __set_EINVAL @ 0x9879d [__watcall]
// ================================================================================================

undefined4 __watcall __set_EINVAL(void)

{
  __set_errno(9);
  return 0xffffffff;
}


// ================================================================================================
// __set_doserrno @ 0x987ad [__watcall]
// ================================================================================================

void __watcall
__set_doserrno(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  undefined8 uVar1;
  
  uVar1 = __get_doserrno_ptr(param_1,param_1,unaff_EBX,unaff_ECX,unaff_EDX);
  *(undefined4 *)uVar1 = (int)((ulonglong)uVar1 >> 0x20);
  return;
}


// ================================================================================================
// call_funcptr_d4d11 @ 0x987b9 [__watcall]
// ================================================================================================

void __watcall call_funcptr_d4d11(void)

{
  (*(code *)funcptr_d4d11)();
  return;
}


// ================================================================================================
// segread @ 0x987c0 [__watcall]
// ================================================================================================

void __watcall segread(undefined2 *param_1)

{
  undefined2 in_ES;
  undefined2 in_CS;
  undefined2 in_SS;
  undefined2 in_DS;
  undefined2 in_FS;
  undefined2 in_GS;
  
  param_1[1] = in_CS;
  param_1[3] = in_DS;
  *param_1 = in_ES;
  param_1[2] = in_SS;
  param_1[4] = in_FS;
  param_1[5] = in_GS;
  return;
}


// ================================================================================================
// int386x @ 0x987e8 [__watcall]
// ================================================================================================

undefined4 __watcall
int386x(undefined4 param_1,undefined4 param_2,undefined4 *unaff_EBX,undefined4 unaff_ECX)

{
  __int386x(param_1,unaff_EBX,unaff_ECX);
  return *unaff_EBX;
}


// ================================================================================================
// _expand @ 0x98801 [__watcall]
// ================================================================================================

undefined4 __watcall _expand(undefined4 param_1,undefined4 unaff_EDX)

{
  bool bVar1;
  byte bVar2;
  int iVar3;
  undefined2 in_DS;
  undefined4 uStack_18;
  byte local_14;
  
  local_14 = local_14 & 0xfe;
  while( true ) {
    iVar3 = __expand_block(in_DS,param_1,unaff_EDX,&uStack_18);
    bVar2 = local_14;
    if (iVar3 == 0) {
      return param_1;
    }
    if (iVar3 == 1) break;
    if (((byte_d4d06 == '\x01') && (byte_d4d07 == '\0')) || (byte_d4d06 == '\t')) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
    }
    if (!bVar1) {
      return 0;
    }
    if (iVar3 == 2) {
      if (((local_14 & 1) != 0) || (iVar3 = __ExpandDGROUP(uStack_18), iVar3 == 0)) {
        return 0;
      }
      local_14 = bVar2 | 1;
    }
  }
  return 0;
}


// ================================================================================================
// __expand_block @ 0x98839 [__watcall]
// ================================================================================================

undefined4 __watcall __expand_block(short param_1,uint unaff_EDX,uint unaff_EBX,uint *unaff_ECX)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint *puVar6;
  undefined4 uVar7;
  uint unaff_ESI;
  short in_DS;
  
  uVar3 = unaff_EBX + 7 & 0xfffffffc;
  if (uVar3 < unaff_EBX) {
    uVar3 = 0xffffffff;
  }
  if (uVar3 < 0xc) {
    uVar3 = 0xc;
  }
  puVar1 = (uint *)(unaff_EDX - 4);
  uVar5 = *puVar1 & 0xfffffffe;
  if (uVar5 < uVar3) {
    uVar3 = uVar3 - uVar5;
    puVar6 = (uint *)((int)puVar1 + uVar5);
    while( true ) {
      *unaff_ECX = uVar3;
      uVar5 = *puVar6;
      if (uVar5 == 0xffffffff) break;
      if ((uVar5 & 1) != 0) {
        return 1;
      }
      uVar3 = puVar6[2];
      uVar2 = puVar6[1];
      uVar4 = dword_d43e8;
      if (in_DS == param_1) {
        for (; (unaff_ESI = uVar4, *(uint *)(uVar4 + 8) != 0 &&
               ((unaff_EDX < uVar4 || (*(uint *)(uVar4 + 8) <= unaff_EDX))));
            uVar4 = *(uint *)(uVar4 + 8)) {
        }
      }
      if (puVar6 == *(uint **)(unaff_ESI + 0xc)) {
        *(uint *)(unaff_ESI + 0xc) = (*(uint **)(unaff_ESI + 0xc))[1];
      }
      if (*unaff_ECX <= uVar5) {
        uVar4 = uVar5 - *unaff_ECX;
        if (0xb < uVar4) {
          puVar6 = (uint *)((int)puVar6 + *unaff_ECX);
          *puVar6 = uVar4;
          puVar6[1] = uVar2;
          puVar6[2] = uVar3;
          *(uint **)(uVar2 + 8) = puVar6;
          *(uint **)(uVar3 + 4) = puVar6;
          *puVar1 = *puVar1 + *unaff_ECX;
          byte_f24c4 = 0;
          return 0;
        }
      }
      *(uint *)(uVar2 + 8) = uVar3;
      *(uint *)(uVar3 + 4) = uVar2;
      *puVar1 = *puVar1 + uVar5;
      *(int *)(unaff_ESI + 0x1c) = *(int *)(unaff_ESI + 0x1c) + -1;
      byte_f24c4 = 0;
      if (*unaff_ECX <= uVar5) goto LAB_000989bd;
      uVar3 = *unaff_ECX - uVar5;
      puVar6 = (uint *)((int)puVar6 + uVar5);
    }
    uVar7 = 2;
  }
  else {
    if (0xb < uVar5 - uVar3) {
      *puVar1 = uVar3 | 1;
      *(uint *)((int)puVar1 + uVar3) = uVar5 - uVar3 | 1;
      uVar5 = dword_d43e8;
      if (in_DS == param_1) {
        for (; (unaff_ESI = uVar5, *(uint *)(uVar5 + 8) != 0 &&
               ((unaff_EDX < uVar5 || (*(uint *)(uVar5 + 8) <= unaff_EDX))));
            uVar5 = *(uint *)(uVar5 + 8)) {
        }
      }
      *(int *)(unaff_ESI + 0x18) = *(int *)(unaff_ESI + 0x18) + 1;
      free((uint *)((int)puVar1 + uVar3) + 1);
    }
LAB_000989bd:
    uVar7 = 0;
  }
  return uVar7;
}


// ================================================================================================
// __heap_grow_loop @ 0x989c8 [__watcall]
// ================================================================================================

void __watcall __heap_grow_loop(int param_1)

{
  bool bVar1;
  int iVar2;
  undefined2 in_DS;
  undefined4 unaff_retaddr;
  byte in_stack_00000004;
  
  do {
    if (param_1 == 1) {
      return;
    }
    if (((byte_d4d06 == '\x01') && (byte_d4d07 == '\0')) || (byte_d4d06 == '\t')) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
    }
    if (!bVar1) {
      return;
    }
    if (param_1 == 2) {
      if ((in_stack_00000004 & 1) != 0) {
        return;
      }
      iVar2 = __ExpandDGROUP(unaff_retaddr);
      if (iVar2 == 0) {
        return;
      }
      in_stack_00000004 = in_stack_00000004 | 1;
    }
    param_1 = __expand_block(in_DS);
    if (param_1 == 0) {
      return;
    }
  } while( true );
}


// ================================================================================================
// _msize @ 0x98a2b [__watcall]
// ================================================================================================

int __watcall _msize(int param_1)

{
  return (*(uint *)(param_1 + -4) & 0xfffffffe) - 4;
}


// ================================================================================================
// file_exists @ 0x98a40 [__cdecl]
// ================================================================================================

int file_exists(undefined4 param_1)

{
  undefined auStack_c [4];
  undefined local_8 [4];
  int local_4;
  
  dos_open_try(param_1,&local_4,local_8,auStack_c);
  closehandle(local_4);
  if (local_4 != 0) {
    local_4 = 1;
  }
  return local_4;
}


// ================================================================================================
// spawnl @ 0x98a81 [__cdecl]
// ================================================================================================

void spawnl(undefined4 param_1,undefined4 param_2)

{
  spawnve(param_1,param_2,&stack0x0000000c,dword_d5444);
  return;
}


// ================================================================================================
// strncmp @ 0x98a9f [__watcall]
// ================================================================================================

int __watcall strncmp(char *__s1,char *__s2,size_t __n)

{
  while( true ) {
    if (__n == 0) {
      return 0;
    }
    if (*__s1 != *__s2) break;
    if (*__s1 == 0) {
      return 0;
    }
    __s1 = (char *)((byte *)__s1 + 1);
    __s2 = (char *)((byte *)__s2 + 1);
    __n = __n - 1;
  }
  return (uint)(byte)*__s1 - (uint)(byte)*__s2;
}


// ================================================================================================
// _dos_setvect @ 0x98ac8 [__watcall]
// ================================================================================================

void __watcall _dos_setvect(undefined4 param_1,undefined4 unaff_EDX)

{
  code *pcVar1;
  
  if ((1 < byte_d4d06) && (byte_d4d06 < 9)) {
    pcVar1 = (code *)swi(0x21);
    (*pcVar1)();
    return;
  }
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)(unaff_EDX);
  return;
}


// ================================================================================================
// _dos_getvect @ 0x98af3 [__watcall]
// ================================================================================================

undefined6 __watcall
_dos_getvect(undefined4 param_1,undefined4 param_2,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  code *pcVar1;
  undefined2 in_ES;
  
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)(unaff_ECX,unaff_EBX);
  return CONCAT24(in_ES,param_1);
}


// ================================================================================================
// draw_quad_clipped @ 0x98b30 [__cdecl]
// ================================================================================================

void draw_quad_clipped(undefined4 param_1,undefined4 *param_2)

{
  int iVar1;
  int iVar2;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  
  iVar1 = shape_width();
  iVar2 = shape_height();
  local_28 = 1;
  local_24 = 1;
  local_20 = iVar1 + -3;
  local_1c = 1;
  iVar2 = iVar2 + -3;
  local_18 = local_20;
  local_14 = iVar2;
  local_10 = local_20;
  draw_textured_triangle(param_1,&local_28,param_2);
  local_28 = local_10;
  local_20 = 1;
  local_18 = 1;
  local_14 = 1;
  local_40 = param_2[4];
  local_3c = param_2[5];
  local_38 = param_2[6];
  local_34 = param_2[7];
  local_30 = *param_2;
  local_2c = param_2[1];
  local_24 = iVar2;
  local_1c = iVar2;
  draw_textured_triangle(param_1,&local_28,&local_40);
  return;
}


// ================================================================================================
// draw_poly_indexed @ 0x98bec [__watcall]
// ================================================================================================

void __watcall draw_poly_indexed(void)

{
  int iVar1;
  undefined4 in_stack_00000004;
  int in_stack_00000008;
  int *in_stack_0000000c;
  int local_40;
  int local_3c;
  int local_38;
  int local_34;
  int local_30;
  int local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  int local_10;
  
  local_10 = shape_width();
  iVar1 = shape_height();
  local_40 = 1;
  local_3c = 1;
  local_38 = local_10 + -2;
  local_34 = 1;
  iVar1 = iVar1 + -2;
  local_28 = *(undefined4 *)(in_stack_00000008 + *in_stack_0000000c * 8);
  local_24 = *(undefined4 *)(in_stack_00000008 + 4 + *in_stack_0000000c * 8);
  local_20 = *(undefined4 *)(in_stack_00000008 + in_stack_0000000c[1] * 8);
  local_1c = *(undefined4 *)(in_stack_00000008 + 4 + in_stack_0000000c[1] * 8);
  local_18 = *(undefined4 *)(in_stack_00000008 + in_stack_0000000c[2] * 8);
  local_14 = *(undefined4 *)(in_stack_00000008 + 4 + in_stack_0000000c[2] * 8);
  local_30 = local_38;
  local_2c = iVar1;
  local_10 = local_38;
  draw_textured_triangle(in_stack_00000004,&local_40,&local_28);
  local_40 = local_10;
  local_38 = 1;
  local_30 = 1;
  local_2c = 1;
  local_28 = *(undefined4 *)(in_stack_00000008 + in_stack_0000000c[2] * 8);
  local_24 = *(undefined4 *)(in_stack_00000008 + 4 + in_stack_0000000c[2] * 8);
  local_20 = *(undefined4 *)(in_stack_00000008 + in_stack_0000000c[3] * 8);
  local_1c = *(undefined4 *)(in_stack_00000008 + 4 + in_stack_0000000c[3] * 8);
  local_18 = *(undefined4 *)(in_stack_00000008 + *in_stack_0000000c * 8);
  local_14 = *(undefined4 *)(in_stack_00000008 + 4 + *in_stack_0000000c * 8);
  local_3c = iVar1;
  local_34 = iVar1;
  draw_textured_triangle(in_stack_00000004,&local_40,&local_28);
  return;
}


// ================================================================================================
// window_alloc_slot @ 0x98d20 [__watcall]
// ================================================================================================

int * __watcall window_alloc_slot(int param_1,int unaff_EDX,int unaff_EBX)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  
  piVar3 = (int *)0x0;
  if (dword_d2f60 < dword_edaa8) {
    piVar1 = dword_d2f60;
    do {
      if (unaff_EBX <= *piVar1) {
        if (piVar1[1] == 0) {
          if (piVar3 == (int *)0x0) {
            piVar3 = piVar1;
          }
        }
        else if ((param_1 == piVar1[2]) && (piVar1[3] == param_1 + unaff_EDX)) {
          piVar1[1] = piVar1[1] + 1;
          return piVar1 + 2;
        }
      }
      piVar1 = piVar1 + *piVar1 + 2;
    } while (piVar1 < dword_edaa8);
  }
  if (piVar3 == (int *)0x0) {
    return (int *)0x0;
  }
  iVar4 = *piVar3;
  if (unaff_EBX + 8 <= iVar4) {
    piVar3[unaff_EBX + 2] = (iVar4 - unaff_EBX) + -2;
    piVar3[unaff_EBX + 3] = 0;
    iVar4 = unaff_EBX;
  }
  *piVar3 = iVar4;
  piVar3[1] = 1;
  iVar2 = 0;
  piVar1 = piVar3 + 2;
  if (0 < iVar4) {
    do {
      *piVar1 = param_1;
      param_1 = param_1 + unaff_EDX;
      iVar2 = iVar2 + 1;
      piVar1 = piVar1 + 1;
    } while (iVar2 < iVar4);
  }
  return piVar3 + 2;
}


// ================================================================================================
// removewindow @ 0x98dd8 [__watcall]
// ================================================================================================

void __watcall removewindow(int *param_1)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  int *piVar4;
  
  iVar1 = param_1[1];
  param_1[1] = iVar1 + -1;
  if (iVar1 + -1 == 0) {
    piVar2 = (int *)0x0;
    for (piVar3 = dword_d2f60; piVar3 < param_1; piVar3 = piVar3 + *piVar3 + 2) {
      piVar2 = piVar3;
    }
    if (piVar3 != param_1) {
      fatalerror(aRemovewindowROWSPACECORR);
    }
    piVar4 = piVar3 + *piVar3 + 2;
    if ((piVar4 < dword_edaa8) && (piVar4[1] == 0)) {
      *piVar3 = *piVar3 + *piVar4 + 2;
    }
    if ((piVar2 != (int *)0x0) && (piVar2[1] == 0)) {
      *piVar2 = *piVar2 + *piVar3 + 2;
    }
  }
  return;
}


// ================================================================================================
// loadfile_auto @ 0x98e50 [__cdecl]
// ================================================================================================

undefined4 * loadfile_auto(undefined4 param_1,uint param_2,undefined4 param_3)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined local_70 [100];
  
  uVar1 = find_file_ext();
  puVar2 = (undefined4 *)find_loaded_file(local_70);
  if (puVar2 == (undefined4 *)0x0) {
    iVar3 = stricmp(uVar1,&aVsh);
    if ((iVar3 != 0) && (iVar3 = stricmp(uVar1,&aQvs), iVar3 != 0)) {
      puVar2 = (undefined4 *)loadfile_packed(local_70,param_2,param_3);
      return puVar2;
    }
    puVar4 = (undefined4 *)loadfile_packed(local_70,param_2 ^ 0x20,param_3);
    puVar2 = puVar4;
    if (puVar4 != (undefined4 *)0x0) {
      uVar1 = packed_size(*puVar4);
      puVar2 = (undefined4 *)reservemem_locked(local_70,uVar1,param_2,param_3);
      shpi_from_compressed(*puVar4,*puVar2);
      releasememblock(puVar4);
    }
  }
  return puVar2;
}


// ================================================================================================
// sound_timer @ 0x98f11 [__watcall]
// ================================================================================================

void __watcall sound_timer(void)

{
  if (((byte_d4f5e == '\0') && (word_d4f88 == 0)) && (dword_d4f64 != 0)) {
    byte_d4f5e = '\x01';
    sound_timer_tick();
    byte_d4f5e = byte_d4f5e + -1;
  }
  return;
}


// ================================================================================================
// sound_timer_tick @ 0x98f46 [__watcall]
// ================================================================================================

void __watcall sound_timer_tick(void)

{
  byte bVar1;
  char cVar2;
  ushort uVar3;
  int iVar4;
  uint uVar5;
  int *piVar6;
  undefined1 *puVar7;
  undefined4 *puVar8;
  int iVar9;
  int iVar10;
  
  iVar4 = 0;
  byte_d4f5d = byte_d4f5d + '\x01';
  do {
    piVar6 = &unk_f22fc + iVar4 * 5;
    if (*piVar6 != 0) {
      iVar9 = (&unk_f2300)[iVar4 * 5];
      (&unk_f2300)[iVar4 * 5] = iVar9 - (&unk_f2304)[iVar4 * 5];
      iVar9 = iVar9 - (&unk_f2304)[iVar4 * 5] >> 0x18;
      if (iVar9 != *piVar6) {
        drv_control((&unk_f230c)[iVar4 * 0x14],iVar9 * 0x10000 + iVar4 * 0x1000000 + 0x32);
        if (iVar9 < 1) {
          sound_channel_stop((&unk_f2308)[iVar4 * 5],iVar4);
          iVar9 = 0;
        }
        *piVar6 = iVar9;
      }
    }
    iVar4 = iVar4 + 1;
  } while (iVar4 < 4);
  if (-1 < (int)dword_d4f96) {
    iVar4 = drv_control(dword_d4f96 & 0xff,8);
    if (iVar4 != 0) {
      drv_tick(dword_d4f96 & 0xff);
    }
  }
  for (uVar5 = 0; (int)uVar5 < dword_d4f64; uVar5 = uVar5 + 1) {
    if (uVar5 != dword_d4f96) {
      drv_tick(uVar5 & 0xff);
    }
  }
  snd_flush_messages();
  if (dword_d4f8a == 0) {
    puVar7 = &unk_f1a1c;
    iVar4 = 0;
    do {
      bVar1 = puVar7[1];
      uVar5 = (uint)bVar1;
      if (bVar1 != 0) {
        if ((bVar1 & 8) != 0) {
          cVar2 = *(char *)(*(int *)(puVar7 + 6) + 0x15);
          uVar5 = (uint)CONCAT11(byte_d4f5d,cVar2);
          if (cVar2 != byte_d4f5d) {
            *(char *)(*(int *)(puVar7 + 6) + 0x15) = byte_d4f5d;
            iVar9 = *(int *)(puVar7 + 6);
            uVar3 = *(ushort *)(iVar9 + 0xe);
            uVar5 = (uint)uVar3;
            if (uVar3 != 0) {
              bVar1 = *(byte *)(iVar9 + 0x10);
              *(ushort *)(iVar9 + 0xe) = uVar3 - 1;
              iVar9 = abs((int)(short)uVar3);
              iVar9 = (uint)bVar1 * iVar9;
              iVar10 = (int)*(short *)(*(int *)(puVar7 + 6) + 0xc);
              uVar5 = iVar9 % iVar10;
              *(char *)(*(int *)(puVar7 + 6) + 0x11) = (char)(iVar9 / iVar10);
            }
          }
        }
        kms_track_tick(puVar7,uVar5);
      }
      puVar7 = puVar7 + 0x54;
      iVar4 = iVar4 + 1;
    } while (iVar4 < 0x18);
    puVar8 = &unk_f189c;
    iVar4 = 0;
    do {
      if ((*(char *)((int)puVar8 + 5) == -1) &&
         (iVar9 = puVar8[2], puVar8[2] = iVar9 + -1, iVar9 + -1 == 0)) {
        snd_note_off(puVar8);
      }
      puVar8 = puVar8 + 3;
      iVar4 = iVar4 + 1;
    } while (iVar4 < 0x20);
  }
  if (-1 < (int)dword_d4f96) {
    iVar4 = drv_control(dword_d4f96 & 0xff,8);
    if (iVar4 != 0) {
      drv_tick(dword_d4f96 & 0xff);
    }
  }
  return;
}


// ================================================================================================
// kms_track_tick @ 0x990cb [__watcall]
// ================================================================================================

void __watcall kms_track_tick(char *param_1)

{
  char cVar1;
  short sVar2;
  int iVar3;
  short sVar4;
  int iVar5;
  uint uVar6;
  int *piVar7;
  int *extraout_EDX;
  undefined4 *puVar8;
  undefined4 *extraout_EDX_00;
  byte *pbVar9;
  byte *pbVar10;
  byte local_1c;
  
  iVar3 = dword_d4f9a;
  if (*(int *)(param_1 + 10) == 0) {
    return;
  }
  pbVar10 = &unk_f21fc + dword_d4f9a;
  dword_d4f9a = dword_d4f9a + 4;
  *pbVar10 = 0x80;
  if ((param_1[1] & 8U) != 0) {
    iVar5 = *(int *)(param_1 + 6);
    if (*(short *)(iVar5 + 0xe) == 0) {
      piVar7 = &unk_f189c;
      for (sVar4 = 0; sVar4 < 0x20; sVar4 = sVar4 + 1) {
        if ((*piVar7 == *(int *)(param_1 + 2)) && (*(char *)((int)piVar7 + 5) == *param_1)) {
          snd_note_off(piVar7);
          piVar7 = extraout_EDX;
        }
        piVar7 = piVar7 + 3;
      }
      *pbVar10 = param_1[0x50] | 0xb0;
      (&DAT_000f21fd)[iVar3] = 0x7b;
      (&DAT_000f21fe)[iVar3] = 0;
      snd_queue_message(param_1[0x51],3,pbVar10);
      param_1[10] = '\0';
      param_1[0xb] = '\0';
      param_1[0xc] = '\0';
      param_1[0xd] = '\0';
      param_1[1] = '\0';
      goto LAB_00099513;
    }
    sVar4 = *(short *)(iVar5 + 0xc);
    iVar5 = abs((int)*(short *)(iVar5 + 0xe));
    if (iVar5 == sVar4) {
      *(undefined *)(*(int *)(param_1 + 6) + 0x11) = *(undefined *)(*(int *)(param_1 + 6) + 0x10);
      param_1[1] = param_1[1] & 0xf7;
    }
    else {
      sVar4 = *(short *)(*(int *)(param_1 + 6) + 0xe);
      if ((sVar4 != 0) &&
         (sVar2 = *(short *)(*(int *)(param_1 + 6) + 0xc), iVar5 = abs((int)sVar4), iVar5 != sVar2))
      {
        kms_controller(param_1,7);
      }
    }
  }
  *(short *)(param_1 + 0x4a) = *(short *)(param_1 + 0x4a) + 0x80;
  while ((*(short *)(param_1 + 0x4c) <= *(short *)(param_1 + 0x4a) && (*(int *)(param_1 + 10) != 0))
        ) {
    puVar8 = &unk_f189c;
    for (sVar4 = 0; sVar4 < 0x20; sVar4 = sVar4 + 1) {
      if ((*(char *)((int)puVar8 + 5) == *param_1) &&
         (iVar5 = puVar8[2], puVar8[2] = iVar5 + -1, iVar5 + -1 == 0)) {
        snd_note_off(puVar8);
        puVar8 = extraout_EDX_00;
      }
      puVar8 = puVar8 + 3;
    }
    if (*(int *)(param_1 + 0xe) == 0) {
      if (*(int *)(param_1 + 10) != 0) {
        while ((*(int *)(param_1 + 0xe) == 0 && (*(int *)(param_1 + 10) != 0))) {
          kms_read_event(&unk_f1884,*(int *)(param_1 + 10));
          uVar6 = (uint)byte_f188e;
          iVar5 = *(int *)(param_1 + 10);
          *(uint *)(param_1 + 10) = iVar5 + uVar6;
          cVar1 = byte_f188d;
          if (byte_f188c < 0xd9) {
            if (byte_f188c < 0x80) {
              byte_f188d = param_1[0x52];
            }
            byte_f188c = byte_f188c & 0x7f;
            if (param_1[0x50] != '\t') {
              byte_f188c = byte_f188c + *(char *)(*(int *)(param_1 + 6) + 0x13);
            }
            if (dword_d4f92 != 0) {
              local_1c = param_1[0x51];
              if ((param_1[0x50] == '\t') &&
                 (iVar5 = snd_patch_record(byte_f188c + 0x5c), iVar5 != 0)) {
                local_1c = *(byte *)(iVar5 + 0xf) & 0x7f;
              }
              snd_note_on(byte_f188c,byte_f188d,dword_f1888,param_1[0x50],local_1c,*param_1,
                          *(undefined4 *)(param_1 + 2));
            }
          }
          else if (byte_f188c < 0xe2) {
            if (byte_f188c < 0xdc) {
              if (0xd8 < byte_f188c) {
                if (byte_f188c < 0xdb) {
                  if (param_1[0x31] == 0) {
                    param_1[10] = '\0';
                    param_1[0xb] = '\0';
                    param_1[0xc] = '\0';
                    param_1[0xd] = '\0';
                    param_1[2] = '\0';
                    param_1[3] = '\0';
                    param_1[4] = '\0';
                    param_1[5] = '\0';
                    param_1[1] = '\0';
                  }
                  else {
                    *(undefined4 *)(param_1 + 10) =
                         *(undefined4 *)(param_1 + (uint)(byte)param_1[0x31] * 4 + 0x32);
                    param_1[0x31] = param_1[0x31] + -1;
                  }
                }
                else {
                  param_1[0x31] = '\0';
                  param_1[0x30] = '\0';
                  iVar5 = *(int *)(param_1 + 0x32);
LAB_00099329:
                  *(int *)(param_1 + 10) = iVar5;
                }
              }
            }
            else if (byte_f188c < 0xdd) {
              param_1[0x4f] = byte_f188d;
              *pbVar10 = param_1[0x50] | 0xc0;
              (&DAT_000f21fd)[iVar3] = cVar1;
              iVar5 = snd_patch_record(cVar1);
              if (iVar5 != 0) {
                if ((*(byte *)(iVar5 + 0xf) & 0x80) == 0) {
                  param_1[0x51] = '\x7f';
                }
                else {
                  param_1[0x51] = *(byte *)(iVar5 + 0xf) & 0x7f;
                }
              }
              cVar1 = param_1[0x51];
              sVar4 = 2;
              pbVar9 = pbVar10;
LAB_000993c5:
              drv_send_midi(cVar1,sVar4,pbVar9);
            }
            else if (byte_f188c < 0xde) {
              kms_set_tempo(*(undefined4 *)(param_1 + 2),byte_f188d);
            }
            else if ((byte_f188c == 0xdf) && ((param_1[1] & 8U) == 0)) {
              kms_controller(param_1,byte_f188d,dword_f1888 & 0xff);
            }
          }
          else if (byte_f188c < 0xe3) {
            *(uint *)(param_1 + (uint)(byte)param_1[0x30] * 4 + 0x18) = iVar5 + uVar6;
            param_1[(byte)param_1[0x30] + 0x12] = cVar1 + -1;
            param_1[0x30] = param_1[0x30] + '\x01';
          }
          else if (byte_f188c < 0xe5) {
            if (byte_f188c < 0xe4) {
              if (param_1[0x30] != 0) {
                *(undefined4 *)(param_1 + 10) =
                     *(undefined4 *)(param_1 + (uint)(byte)param_1[0x30] * 4 + 0x14);
                cVar1 = param_1[(byte)param_1[0x30] + 0x11];
                param_1[(byte)param_1[0x30] + 0x11] = cVar1 + -1;
                if (cVar1 == '\0') {
                  param_1[0x30] = param_1[0x30] + -1;
                }
              }
            }
            else {
              param_1[0x52] = byte_f188d;
            }
          }
          else if (byte_f188c < 0xe6) {
            kms_pitch_bend(param_1,(int)(short)dword_f1888);
          }
          else if (byte_f188c < 0xe8) {
            if (byte_f188c == 0xe6) {
              cVar1 = param_1[0x31];
              param_1[0x31] = cVar1 + 1U;
              *(undefined4 *)(param_1 + (uint)(byte)(cVar1 + 1U) * 4 + 0x32) =
                   *(undefined4 *)(param_1 + 10);
              iVar5 = dword_f1888 + 4;
              goto LAB_00099329;
            }
          }
          else {
            if (byte_f188c < 0xe9) {
              sVar4 = byte_f188e - 4;
              cVar1 = param_1[0x51];
              pbVar9 = &unk_f1784;
              goto LAB_000993c5;
            }
            if (byte_f188c == 0xea) {
              param_1[0x4e] = byte_f188d;
            }
          }
          if (*(int *)(param_1 + 10) != 0) {
            kms_read_event(&dword_f1890,*(int *)(param_1 + 10));
            *(undefined4 *)(param_1 + 0xe) = dword_f1890;
          }
        }
        *(int *)(param_1 + 0xe) = *(int *)(param_1 + 0xe) + -1;
      }
    }
    else {
      *(int *)(param_1 + 0xe) = *(int *)(param_1 + 0xe) + -1;
    }
    *(short *)(param_1 + 0x4a) = *(short *)(param_1 + 0x4a) - *(short *)(param_1 + 0x4c);
  }
LAB_00099513:
  dword_d4f9a = dword_d4f9a + -4;
  return;
}


// ================================================================================================
// kms_controller @ 0x99522 [__watcall]
// ================================================================================================

void __watcall kms_controller(int param_1,byte unaff_DL,byte unaff_BL)

{
  byte bVar1;
  int iVar2;
  byte *pbVar3;
  
  iVar2 = dword_d4f9a;
  pbVar3 = &unk_f21fc + dword_d4f9a;
  dword_d4f9a = dword_d4f9a + 4;
  *pbVar3 = *(byte *)(param_1 + 0x50) | 0xb0;
  (&DAT_000f21fd)[iVar2] = unaff_DL;
  if (6 < unaff_DL) {
    if (unaff_DL < 8) {
      (&unk_f234d)[(uint)*(byte *)(param_1 + 0x50) * 7] = unaff_BL;
      unaff_BL = (byte)(((uint)*(byte *)(*(int *)(param_1 + 6) + 0x11) * (uint)unaff_BL) / 0x7f);
      if (0x7f < unaff_BL) {
        unaff_BL = 0x7f;
      }
    }
    else if (unaff_DL == 10) {
      (&unk_f234e)[(uint)*(byte *)(param_1 + 0x50) * 7] = unaff_BL;
      bVar1 = *(byte *)(*(int *)(param_1 + 6) + 0x12);
      if (bVar1 < 0x40) {
        unaff_BL = unaff_BL -
                   (char)((int)((0x3f - (uint)*(byte *)(*(int *)(param_1 + 6) + 0x12)) *
                               (uint)unaff_BL) / 0x3f);
      }
      else {
        unaff_BL = unaff_BL + (char)((int)((0x7f - (uint)unaff_BL) * (bVar1 - 0x3f)) / 0x3f);
      }
    }
  }
  (&DAT_000f21fe)[iVar2] = unaff_BL;
  drv_send_midi(*(undefined *)(param_1 + 0x51),3,pbVar3);
  dword_d4f9a = dword_d4f9a + -4;
  return;
}


// ================================================================================================
// snd_note_off @ 0x99620 [__watcall]
// ================================================================================================

void __watcall snd_note_off(undefined4 *param_1)

{
  int iVar1;
  byte *pbVar2;
  
  iVar1 = dword_d4f9a;
  pbVar2 = &unk_f21fc + dword_d4f9a;
  dword_d4f9a = dword_d4f9a + 4;
  *pbVar2 = *(byte *)((int)param_1 + 6) | 0x80;
  (&DAT_000f21fd)[iVar1] = *(undefined *)(param_1 + 1);
  (&DAT_000f21fe)[iVar1] = 0;
  drv_send_midi(*(undefined *)((int)param_1 + 7),3);
  *param_1 = 0;
  dword_d4f9a = dword_d4f9a + -4;
  return;
}


// ================================================================================================
// kms_set_tempo @ 0x9966e [__watcall]
// ================================================================================================

undefined4 __watcall kms_set_tempo(int param_1,byte unaff_DL)

{
  short sVar1;
  undefined1 *puVar2;
  
  puVar2 = &unk_f1a1c;
  for (sVar1 = 0; sVar1 < 0x18; sVar1 = sVar1 + 1) {
    if (param_1 == *(int *)(puVar2 + 2)) {
      *(short *)(puVar2 + 0x4c) = (short)(32000 / (ulonglong)(longlong)(int)(uint)unaff_DL);
    }
    puVar2 = puVar2 + 0x54;
  }
  return 0;
}


// ================================================================================================
// kms_pitch_bend @ 0x996b0 [__watcall]
// ================================================================================================

void __watcall kms_pitch_bend(int param_1,undefined4 unaff_EDX)

{
  int iVar1;
  byte *pbVar2;
  
  iVar1 = dword_d4f9a;
  pbVar2 = &unk_f21fc + dword_d4f9a;
  dword_d4f9a = dword_d4f9a + 4;
  *pbVar2 = *(byte *)(param_1 + 0x50) | 0xe0;
  (&DAT_000f21fd)[iVar1] = 0;
  (&DAT_000f21fe)[iVar1] = (byte)((uint)unaff_EDX >> 8) & 0x7f;
  drv_send_midi(*(undefined *)(param_1 + 0x51),3);
  dword_d4f9a = dword_d4f9a + -4;
  return;
}


// ================================================================================================
// snd_note_on @ 0x99700 [__watcall]
// ================================================================================================

int __watcall
snd_note_on(undefined param_1,undefined param_2,int param_3,byte unaff_CL,undefined param_5,
           char param_6,int param_7)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  byte *pbVar4;
  
  iVar1 = dword_d4f9a;
  pbVar4 = &unk_f21fc + dword_d4f9a;
  piVar2 = &unk_f189c;
  iVar3 = 0;
  dword_d4f9a = dword_d4f9a + 4;
  do {
    if (*piVar2 == 0) {
      *piVar2 = param_7;
      *(undefined *)(piVar2 + 1) = param_1;
      *(char *)((int)piVar2 + 5) = param_6;
      *(byte *)((int)piVar2 + 6) = unaff_CL;
      *(undefined *)((int)piVar2 + 7) = param_5;
      if (param_3 == 0) {
        piVar2[2] = 1;
      }
      else {
        piVar2[2] = param_3;
      }
      *pbVar4 = unaff_CL | 0x90;
      (&DAT_000f21fd)[iVar1] = param_1;
      (&DAT_000f21fe)[iVar1] = param_2;
      if (param_6 == -1) {
        snd_queue_message(param_5,3);
      }
      else {
        drv_send_midi(param_5,3);
      }
      goto LAB_000997a6;
    }
    piVar2 = piVar2 + 3;
    iVar3 = iVar3 + 1;
  } while (iVar3 < 0x20);
  iVar3 = -1;
LAB_000997a6:
  dword_d4f9a = dword_d4f9a + -4;
  return iVar3;
}


// ================================================================================================
// snd_queue_message @ 0x997b7 [__watcall]
// ================================================================================================

void __watcall snd_queue_message(undefined param_1,short unaff_DX,undefined *unaff_EBX)

{
  undefined1 *puVar1;
  
  if ((byte_d4f5c == '\0') && (unaff_DX + dword_d4f58 < 0x80)) {
    (&unk_f1704)[dword_d4f58] = param_1;
    word_d4f88 = word_d4f88 + 1;
    byte_d4f5c = byte_d4f5c + '\x01';
    dword_d4f58 = dword_d4f58 + 1;
    for (; unaff_DX != 0; unaff_DX = unaff_DX + -1) {
      puVar1 = &unk_f1704 + dword_d4f58;
      dword_d4f58 = dword_d4f58 + 1;
      *puVar1 = *unaff_EBX;
      unaff_EBX = unaff_EBX + 1;
    }
    byte_d4f5c = byte_d4f5c + -1;
    word_d4f88 = word_d4f88 + -1;
  }
  return;
}


// ================================================================================================
// snd_flush_messages @ 0x99822 [__watcall]
// ================================================================================================

void __watcall snd_flush_messages(void)

{
  short sVar1;
  short sVar2;
  
  if ((dword_d4f58 != 0) && (byte_d4f5c == '\0')) {
    sVar1 = 0;
    byte_d4f5c = '\x01';
    do {
      sVar2 = 3;
      if (((&unk_f1705)[sVar1] & 0xf0) == 0xc0) {
        sVar2 = 2;
      }
      drv_send_midi((&unk_f1704)[sVar1],sVar2,&unk_f1705 + sVar1);
      sVar1 = sVar1 + sVar2 + 1;
    } while (sVar1 < dword_d4f58);
    dword_d4f58 = 0;
    byte_d4f5c = byte_d4f5c + -1;
  }
  return;
}


// ================================================================================================
// snd_program_change @ 0x998a0 [__watcall]
// ================================================================================================

void __watcall snd_program_change(undefined param_1,byte unaff_DL,undefined unaff_BL)

{
  int iVar1;
  byte *pbVar2;
  
  iVar1 = dword_d4f9a;
  pbVar2 = &unk_f21fc + dword_d4f9a;
  dword_d4f9a = dword_d4f9a + 4;
  *pbVar2 = unaff_DL | 0xc0;
  (&DAT_000f21fd)[iVar1] = unaff_BL;
  drv_send_midi(param_1,2);
  dword_d4f9a = dword_d4f9a + -4;
  return;
}


// ================================================================================================
// kms_read_event @ 0x99925 [__watcall]
// ================================================================================================

void __watcall kms_read_event(int *param_1,byte *unaff_EDX)

{
  byte bVar1;
  int iVar2;
  byte *pbVar3;
  byte *pbVar4;
  undefined8 uVar5;
  
  *param_1 = 0;
  pbVar3 = unaff_EDX;
  do {
    pbVar4 = pbVar3;
    *param_1 = *param_1 * 0x80 + (uint)(*pbVar4 & 0x7f);
    pbVar3 = pbVar4 + 1;
  } while ((*pbVar4 & 0x80) != 0);
  bVar1 = pbVar4[1];
  *(byte *)(param_1 + 2) = bVar1;
  pbVar3 = pbVar4 + 2;
  if (0x11 < (byte)(bVar1 + 0x27)) goto switchD_0009996a_caseD_d9;
  switch(bVar1) {
  case 0xd9:
  case 0xda:
  case 0xdb:
  case 0xe3:
    break;
  default:
    *(byte *)((int)param_1 + 9) = *pbVar3;
    goto LAB_0009998e;
  case 0xdf:
    *(byte *)((int)param_1 + 9) = *pbVar3;
    param_1[1] = (uint)pbVar4[3];
    pbVar3 = pbVar4 + 4;
    break;
  case 0xe5:
    uVar5 = read_u16(pbVar3);
    param_1[1] = (uint)uVar5 & 0xffff;
    pbVar3 = (byte *)((int)((ulonglong)uVar5 >> 0x20) + 2);
    break;
  case 0xe6:
    *(byte *)((int)param_1 + 9) = *pbVar3;
    iVar2 = read_u32(pbVar4 + 3);
    param_1[1] = iVar2;
    pbVar3 = pbVar4 + 7;
    break;
  case 0xe8:
    for (iVar2 = 0; iVar2 < (int)(uint)*pbVar3; iVar2 = iVar2 + 1) {
      (&unk_f1784)[iVar2] = pbVar4[iVar2 + 3];
    }
  case 0xe7:
    pbVar3 = pbVar3 + *pbVar3;
LAB_0009998e:
    pbVar3 = pbVar3 + 1;
  }
switchD_0009996a_caseD_d9:
  if (bVar1 < 0xd9) {
    *(byte *)((int)param_1 + 9) = *pbVar3;
    param_1[1] = 0;
    pbVar4 = pbVar3 + 1;
    do {
      param_1[1] = param_1[1] * 0x80 + (uint)(*pbVar4 & 0x7f);
      pbVar3 = pbVar4 + 1;
      bVar1 = *pbVar4;
      pbVar4 = pbVar3;
    } while ((bVar1 & 0x80) != 0);
  }
  *(char *)((int)param_1 + 10) = (char)pbVar3 - (char)unaff_EDX;
  return;
}


// ================================================================================================
// read_u32 @ 0x99a0b [__watcall]
// ================================================================================================

undefined4 __watcall read_u32(undefined4 *param_1)

{
  return *param_1;
}


// ================================================================================================
// read_u16 @ 0x99a0e [__watcall]
// ================================================================================================

undefined2 __watcall read_u16(undefined2 *param_1)

{
  return *param_1;
}


// ================================================================================================
// __copypart @ 0x99a12 [__watcall]
// ================================================================================================

void __watcall __copypart(undefined4 *param_1,undefined4 *unaff_EDX,uint unaff_EBX,uint unaff_ECX)

{
  uint uVar1;
  undefined4 *puVar2;
  
  if (param_1 != (undefined4 *)0x0) {
    if ((int)unaff_ECX < (int)unaff_EBX) {
      unaff_EBX = unaff_ECX;
    }
    puVar2 = param_1;
    for (uVar1 = unaff_EBX >> 2; uVar1 != 0; uVar1 = uVar1 - 1) {
      *puVar2 = *unaff_EDX;
      unaff_EDX = unaff_EDX + 1;
      puVar2 = puVar2 + 1;
    }
    for (uVar1 = unaff_EBX & 3; uVar1 != 0; uVar1 = uVar1 - 1) {
      *(undefined *)puVar2 = *(undefined *)unaff_EDX;
      unaff_EDX = (undefined4 *)((int)unaff_EDX + 1);
      puVar2 = (undefined4 *)((int)puVar2 + 1);
    }
    *(undefined *)(unaff_EBX + (int)param_1) = 0;
  }
  return;
}


// ================================================================================================
// _splitpath @ 0x99a45 [__watcall]
// ================================================================================================

void __watcall
_splitpath(char *param_1,char *unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX,
          undefined4 param_5)

{
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  char *pcVar4;
  char *pcVar5;
  
  if ((*param_1 == '\0') || (param_1[1] != ':')) {
    pcVar4 = param_1;
    if (unaff_EDX != (char *)0x0) {
      *unaff_EDX = '\0';
    }
  }
  else {
    if (unaff_EDX != (char *)0x0) {
      cVar1 = *param_1;
      unaff_EDX[2] = '\0';
      *unaff_EDX = cVar1;
      unaff_EDX[1] = ':';
    }
    param_1 = param_1 + 2;
    pcVar4 = param_1;
  }
  do {
    pcVar2 = pcVar4;
    pcVar4 = pcVar2;
    pcVar5 = (char *)0x0;
    do {
      while( true ) {
        pcVar3 = pcVar4;
        cVar1 = *pcVar3;
        if (cVar1 == '\0') {
          __copypart(unaff_EBX,param_1,(int)pcVar2 - (int)param_1,0x81);
          if (pcVar5 == (char *)0x0) {
            pcVar5 = pcVar3;
          }
          __copypart(unaff_ECX,pcVar2,(int)pcVar5 - (int)pcVar2,8);
          __copypart(param_5,pcVar5,(int)pcVar3 - (int)pcVar5,4);
          return;
        }
        if (cVar1 != '.') break;
        pcVar4 = pcVar3 + 1;
        pcVar5 = pcVar3;
      }
      pcVar4 = pcVar3 + 1;
    } while ((cVar1 != '\\') && (cVar1 != '/'));
  } while( true );
}


// ================================================================================================
// __pathsep @ 0x99ae2 [__watcall]
// ================================================================================================

char __watcall __pathsep(char param_1,char *unaff_EDX)

{
  if ((param_1 == '\\') || (param_1 == '/')) {
    if (*unaff_EDX == '\0') {
      *unaff_EDX = param_1;
    }
    param_1 = *unaff_EDX;
  }
  return param_1;
}


// ================================================================================================
// _makepath @ 0x99af4 [__watcall]
// ================================================================================================

void __watcall
_makepath(char *param_1,char *unaff_EDX,char *unaff_EBX,char *unaff_ECX,char *param_5)

{
  char cVar1;
  char *pcVar2;
  char local_c [4];
  
  local_c[0] = '\0';
  if ((unaff_EDX != (char *)0x0) && (*unaff_EDX != '\0')) {
    *param_1 = *unaff_EDX;
    param_1[1] = ':';
    param_1 = param_1 + 2;
  }
  *param_1 = '\0';
  if ((unaff_EBX != (char *)0x0) && (pcVar2 = param_1, *unaff_EBX != '\0')) {
    do {
      param_1 = pcVar2;
      cVar1 = *unaff_EBX;
      unaff_EBX = unaff_EBX + 1;
      cVar1 = __pathsep(cVar1,local_c);
      *param_1 = cVar1;
      pcVar2 = param_1 + 1;
    } while (*unaff_EBX != '\0');
    if (local_c[0] == '\0') {
      local_c[0] = '\\';
    }
    if (local_c[0] != *param_1) {
      *pcVar2 = local_c[0];
      param_1 = pcVar2;
    }
  }
  if (local_c[0] == '\0') {
    local_c[0] = '\\';
  }
  if (unaff_ECX == (char *)0x0) {
    if (local_c[0] == *param_1) {
      param_1 = param_1 + 1;
    }
  }
  else {
    cVar1 = __pathsep(*unaff_ECX,local_c);
    if ((cVar1 != local_c[0]) && (local_c[0] == *param_1)) {
      param_1 = param_1 + 1;
    }
    for (; *unaff_ECX != '\0'; unaff_ECX = unaff_ECX + 1) {
      cVar1 = __pathsep(*unaff_ECX,local_c);
      *param_1 = cVar1;
      param_1 = param_1 + 1;
    }
  }
  if ((param_5 != (char *)0x0) && (*param_5 != '\0')) {
    if (*param_5 == '.') goto LAB_00099ba9;
    *param_1 = '.';
    while( true ) {
      param_1 = param_1 + 1;
LAB_00099ba9:
      cVar1 = *param_5;
      if (cVar1 == '\0') break;
      param_5 = param_5 + 1;
      *param_1 = cVar1;
    }
  }
  *param_1 = '\0';
  return;
}


// ================================================================================================
// __run_atexit @ 0x99bbf [__watcall]
// ================================================================================================

void __watcall __run_atexit(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX)

{
  int iVar1;
  int extraout_EDX;
  
  iVar1 = dword_f24c0;
  dword_f24c0 = 0x20;
  iVar1 = iVar1 << 2;
  while (iVar1 != 0) {
    (**(code **)(&unk_f243c + iVar1))(*(code **)(&unk_f243c + iVar1),unaff_EDX,unaff_EBX);
    iVar1 = extraout_EDX;
  }
  return;
}


// ================================================================================================
// atexit @ 0x99bf6 [__watcall]
// ================================================================================================

int __watcall atexit(__func *__func)

{
  funcptr_d2f68 = __run_atexit;
  if (dword_f24c0 < 0x20) {
    *(__func **)(&unk_f2440 + dword_f24c0 * 4) = __func;
    dword_f24c0 = dword_f24c0 + 1;
    return 0;
  }
  return -1;
}


// ================================================================================================
// __CMain @ 0x99c32 [__watcall] noreturn
// ================================================================================================

void __watcall __CMain(undefined4 param_1)

{
  undefined *puVar1;
  int iVar2;
  uint uVar3;
  undefined *puVar4;
  undefined8 uVar5;
  
  puVar4 = &stack0xfffffff8;
  uVar5 = stackavail(param_1,dword_d4cf0 + 3U & 0xfffffffc);
  uVar3 = (uint)((ulonglong)uVar5 >> 0x20);
  if (uVar3 < (uint)uVar5) {
    iVar2 = -uVar3;
    puVar4 = &stack0xfffffff8 + iVar2;
    puVar1 = &stack0xfffffff8 + iVar2;
  }
  else {
    puVar1 = (undefined *)0x0;
  }
  dword_d4cf4 = puVar1 + dword_d4cf0;
  *(undefined4 *)(puVar4 + -4) = 0x99c67;
  __init_amblksiz();
  *(undefined4 *)(puVar4 + -4) = 0x99c77;
  iVar2 = main(dword_f58d8,dword_f58dc);
                    /* WARNING: Subroutine does not return */
  *(code **)(puVar4 + -4) = empty_func_99c7c;
  exit(iVar2);
}


// ================================================================================================
// empty_func_99c7c @ 0x99c7c [__watcall]
// ================================================================================================

void __watcall empty_func_99c7c(void)

{
  return;
}


// ================================================================================================
// __InitRtns @ 0x99c82 [__watcall]
// ================================================================================================

void __watcall __InitRtns(byte param_1)

{
  byte bVar1;
  char *pcVar2;
  char *pcVar3;
  
  while( true ) {
    pcVar2 = &unk_d8b3e;
    bVar1 = param_1;
    for (pcVar3 = &unk_d8b14; pcVar3 < &unk_d8b3e; pcVar3 = pcVar3 + 6) {
      if ((*pcVar3 != '\x02') && ((byte)pcVar3[1] <= bVar1)) {
        bVar1 = pcVar3[1];
        pcVar2 = pcVar3;
      }
    }
    if (pcVar2 == &unk_d8b3e) break;
    if (*(code **)(pcVar2 + 2) != (code *)0x0) {
      (**(code **)(pcVar2 + 2))();
    }
    *pcVar2 = '\x02';
  }
  return;
}


// ================================================================================================
// __FiniRtns @ 0x99ccd [__watcall]
// ================================================================================================

void __watcall __FiniRtns(byte param_1,byte unaff_DL)

{
  byte bVar1;
  char *pcVar2;
  char *pcVar3;
  
  while( true ) {
    pcVar2 = &unk_d8b4a;
    bVar1 = param_1;
    for (pcVar3 = &unk_d8b3e; pcVar3 < &unk_d8b4a; pcVar3 = pcVar3 + 6) {
      if ((*pcVar3 != '\x02') && (bVar1 <= (byte)pcVar3[1])) {
        bVar1 = pcVar3[1];
        pcVar2 = pcVar3;
      }
    }
    if (pcVar2 == &unk_d8b4a) break;
    if ((bVar1 <= unaff_DL) && (*(code **)(pcVar2 + 2) != (code *)0x0)) {
      (**(code **)(pcVar2 + 2))();
    }
    *pcVar2 = '\x02';
  }
  return;
}


// ================================================================================================
// __prtf @ 0x99d1c [__watcall]
// ================================================================================================

undefined4 __watcall __prtf(undefined4 param_1,char *unaff_EDX,int *unaff_EBX,code *unaff_ECX)

{
  int iVar1;
  char cVar2;
  undefined6 *puVar3;
  char *pcVar4;
  char *extraout_ECX;
  undefined4 *puVar5;
  undefined2 *puVar6;
  bool bVar7;
  undefined auStack_5c [40];
  undefined4 local_34;
  int local_30;
  int local_2c;
  int local_28;
  undefined4 local_24;
  byte local_20;
  char local_1f;
  char local_1e;
  char local_1d [5];
  undefined local_14 [4];
  
  local_14[0] = 0;
  local_20 = 0;
  local_24 = 0;
  local_34 = param_1;
  do {
    while( true ) {
      while( true ) {
        while( true ) {
          cVar2 = *unaff_EDX;
          if (cVar2 == '\0') {
            return local_24;
          }
          unaff_EDX = unaff_EDX + 1;
          if (cVar2 == '%') break;
          (*unaff_ECX)();
        }
        unaff_EDX = (char *)__prtf_getspec(unaff_EDX,unaff_EBX,&local_34);
        local_1f = *unaff_EDX;
        unaff_EDX = unaff_EDX + 1;
        if (local_1f == '\0') {
          return local_24;
        }
        if (local_1f == 'n') break;
        __prtf_convert(auStack_5c,unaff_EBX,&local_34,local_14);
        if (((local_20 & 8) == 0) && (local_1e == ' ')) {
          while (local_30 = local_30 + -1, -1 < local_30) {
            (*unaff_ECX)();
          }
        }
        pcVar4 = local_1d;
        while (*pcVar4 != '\0') {
          (*unaff_ECX)();
          pcVar4 = extraout_ECX;
        }
        while (iVar1 = local_28 + -1, local_28 != 0) {
          local_28 = iVar1;
          (*unaff_ECX)();
        }
        local_28 = iVar1;
        if (((local_20 & 8) == 0) && (local_1e != ' ')) {
          while (local_30 = local_30 + -1, -1 < local_30) {
            (*unaff_ECX)();
          }
        }
        if ((local_1f == 's') || (local_1f == 'S')) {
          if ((local_20 & 0x20) == 0) {
            while (iVar1 = local_2c + -1, bVar7 = local_2c != 0, local_2c = iVar1, bVar7) {
              (*unaff_ECX)();
            }
          }
          else {
            while (iVar1 = local_2c + -1, bVar7 = local_2c != 0, local_2c = iVar1, bVar7) {
              (*unaff_ECX)();
            }
          }
        }
        else {
          while (iVar1 = local_2c + -1, bVar7 = local_2c != 0, local_2c = iVar1, bVar7) {
            (*unaff_ECX)();
          }
        }
        if (((local_20 & 8) != 0) && (0 < local_30)) {
          while (iVar1 = local_30 + -1, bVar7 = local_30 != 0, local_30 = iVar1, bVar7) {
            (*unaff_ECX)();
          }
        }
      }
      if ((local_20 & 0x20) == 0) break;
      if ((local_20 & 0x80) == 0) {
        if ((local_20 & 0x40) == 0) {
          puVar5 = (undefined4 *)*unaff_EBX;
          *unaff_EBX = (int)(puVar5 + 1);
          puVar5 = (undefined4 *)*puVar5;
        }
        else {
          puVar5 = (undefined4 *)*unaff_EBX;
          *unaff_EBX = (int)(puVar5 + 1);
          puVar5 = (undefined4 *)*puVar5;
        }
LAB_00099d99:
        *puVar5 = local_24;
      }
      else {
        puVar3 = (undefined6 *)*unaff_EBX;
        *unaff_EBX = (int)(puVar3 + 1);
        puVar5 = (undefined4 *)*puVar3;
LAB_00099d82:
        *puVar5 = local_24;
      }
    }
    if ((local_20 & 0x10) == 0) {
      if ((local_20 & 0x80) == 0) {
        if ((local_20 & 0x40) == 0) {
          puVar5 = (undefined4 *)*unaff_EBX;
          *unaff_EBX = (int)(puVar5 + 1);
          puVar5 = (undefined4 *)*puVar5;
        }
        else {
          puVar5 = (undefined4 *)*unaff_EBX;
          *unaff_EBX = (int)(puVar5 + 1);
          puVar5 = (undefined4 *)*puVar5;
        }
        goto LAB_00099d99;
      }
      puVar3 = (undefined6 *)*unaff_EBX;
      *unaff_EBX = (int)(puVar3 + 1);
      puVar5 = (undefined4 *)*puVar3;
      goto LAB_00099d82;
    }
    if ((local_20 & 0x80) == 0) {
      if ((local_20 & 0x40) == 0) {
        puVar5 = (undefined4 *)*unaff_EBX;
        *unaff_EBX = (int)(puVar5 + 1);
        puVar6 = (undefined2 *)*puVar5;
      }
      else {
        puVar5 = (undefined4 *)*unaff_EBX;
        *unaff_EBX = (int)(puVar5 + 1);
        puVar6 = (undefined2 *)*puVar5;
      }
      *puVar6 = (short)local_24;
    }
    else {
      puVar3 = (undefined6 *)*unaff_EBX;
      *unaff_EBX = (int)(puVar3 + 1);
      *(undefined2 *)*puVar3 = (short)local_24;
    }
  } while( true );
}


// ================================================================================================
// __prtf_getspec @ 0x99f9d [__watcall]
// ================================================================================================

byte * __watcall __prtf_getspec(undefined4 param_1,int *unaff_EDX,int unaff_EBX)

{
  byte bVar1;
  int *piVar2;
  int iVar3;
  byte *pbVar4;
  byte *pbVar5;
  
  *(undefined *)(unaff_EBX + 0x17) = 0;
  *(undefined *)(unaff_EBX + 0x16) = 0x20;
  pbVar4 = (byte *)__prtf_evalflags(param_1,unaff_EBX);
  *(undefined4 *)(unaff_EBX + 4) = 0;
  if ((*pbVar4 < 0x30) || (0x39 < *pbVar4)) {
    if (*pbVar4 == 0x2a) {
      piVar2 = (int *)*unaff_EDX;
      *unaff_EDX = (int)(piVar2 + 1);
      iVar3 = *piVar2;
      *(int *)(unaff_EBX + 4) = iVar3;
      if (iVar3 < 0) {
        *(int *)(unaff_EBX + 4) = -iVar3;
        *(byte *)(unaff_EBX + 0x14) = *(byte *)(unaff_EBX + 0x14) | 8;
      }
      pbVar4 = pbVar4 + 1;
    }
  }
  else {
    do {
      bVar1 = *pbVar4;
      pbVar4 = pbVar4 + 1;
      *(uint *)(unaff_EBX + 4) = *(int *)(unaff_EBX + 4) * 10 + (bVar1 - 0x30);
      if (*pbVar4 < 0x30) break;
    } while (*pbVar4 < 0x3a);
  }
  *(undefined4 *)(unaff_EBX + 8) = 0xffffffff;
  pbVar5 = pbVar4;
  if (*pbVar4 == 0x2e) {
    pbVar5 = pbVar4 + 1;
    *(undefined4 *)(unaff_EBX + 8) = 0;
    if (*pbVar5 == 0x2a) {
      piVar2 = (int *)*unaff_EDX;
      *unaff_EDX = (int)(piVar2 + 1);
      iVar3 = *piVar2;
      *(int *)(unaff_EBX + 8) = iVar3;
      if (iVar3 < 0) {
        *(undefined4 *)(unaff_EBX + 8) = 0xffffffff;
      }
      pbVar5 = pbVar4 + 2;
    }
    else {
      for (; (0x2f < *pbVar5 && (*pbVar5 < 0x3a)); pbVar5 = pbVar5 + 1) {
        *(uint *)(unaff_EBX + 8) = *(int *)(unaff_EBX + 8) * 10 + (*pbVar5 - 0x30);
      }
    }
  }
  bVar1 = *pbVar5;
  pbVar4 = pbVar5 + 1;
  if (bVar1 < 0x4e) {
    if (0x45 < bVar1) {
      if (bVar1 < 0x47) {
        *(byte *)(unaff_EBX + 0x14) = *(byte *)(unaff_EBX + 0x14) | 0x80;
      }
      else {
        if (bVar1 != 0x4c) {
          return pbVar5;
        }
        *(byte *)(unaff_EBX + 0x14) = *(byte *)(unaff_EBX + 0x14) | 0x40;
      }
      return pbVar4;
    }
  }
  else {
    if (0x4e < bVar1) {
      if (bVar1 < 0x6c) {
        if (bVar1 == 0x68) {
          *(byte *)(unaff_EBX + 0x14) = *(byte *)(unaff_EBX + 0x14) | 0x10;
          return pbVar4;
        }
        return pbVar5;
      }
      if ((0x6c < bVar1) && (bVar1 != 0x77)) {
        return pbVar5;
      }
      *(byte *)(unaff_EBX + 0x14) = *(byte *)(unaff_EBX + 0x14) | 0x20;
      return pbVar5 + 1;
    }
    *(byte *)(unaff_EBX + 0x14) = *(byte *)(unaff_EBX + 0x14) | 0x40;
    pbVar5 = pbVar4;
  }
  return pbVar5;
}


// ================================================================================================
// __prtf_evalflags @ 0x9a0d0 [__watcall]
// ================================================================================================

void __watcall __prtf_evalflags(char *param_1,int unaff_EDX)

{
  char cVar1;
  byte bVar2;
  
  *(undefined *)(unaff_EDX + 0x14) = 0;
  do {
    cVar1 = *param_1;
    if (cVar1 == '-') {
      *(byte *)(unaff_EDX + 0x14) = *(byte *)(unaff_EDX + 0x14) | 8;
    }
    else if (cVar1 == '#') {
      *(byte *)(unaff_EDX + 0x14) = *(byte *)(unaff_EDX + 0x14) | 1;
    }
    else if (cVar1 == '+') {
      bVar2 = *(byte *)(unaff_EDX + 0x14);
      *(byte *)(unaff_EDX + 0x14) = bVar2 | 4;
      *(byte *)(unaff_EDX + 0x14) = bVar2 & 0xfd | 4;
    }
    else if (cVar1 == ' ') {
      if ((*(byte *)(unaff_EDX + 0x14) & 4) == 0) {
        *(byte *)(unaff_EDX + 0x14) = *(byte *)(unaff_EDX + 0x14) | 2;
      }
    }
    else {
      if (cVar1 != '0') {
        return;
      }
      *(undefined *)(unaff_EDX + 0x16) = 0x30;
    }
    param_1 = param_1 + 1;
  } while( true );
}


// ================================================================================================
// __prtf_strnlen @ 0x9a12b [__watcall]
// ================================================================================================

void __watcall __prtf_strnlen(char *param_1,undefined4 param_2,int unaff_EBX)

{
  char cVar1;
  int iVar2;
  
  for (iVar2 = 0; (cVar1 = *param_1, param_1 = param_1 + 1, cVar1 != '\0' && (iVar2 != unaff_EBX));
      iVar2 = iVar2 + 1) {
  }
  return;
}


// ================================================================================================
// __prtf_wstrnlen @ 0x9a14f [__watcall]
// ================================================================================================

void __watcall __prtf_wstrnlen(short *param_1,undefined4 param_2,int unaff_EBX)

{
  short sVar1;
  int iVar2;
  
  for (iVar2 = 0; (sVar1 = *param_1, param_1 = param_1 + 1, sVar1 != 0 && (iVar2 != unaff_EBX));
      iVar2 = iVar2 + 1) {
  }
  return;
}


// ================================================================================================
// __prtf_fmt4hex @ 0x9a172 [__watcall]
// ================================================================================================

void __watcall __prtf_fmt4hex(undefined4 param_1,char *unaff_EDX,int unaff_EBX)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  char *pcVar4;
  char *pcVar5;
  
  itoa(param_1,unaff_EDX,0x10);
  uVar3 = 0xffffffff;
  pcVar4 = unaff_EDX;
  do {
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    cVar1 = *pcVar4;
    pcVar4 = pcVar4 + 1;
  } while (cVar1 != '\0');
  iVar2 = unaff_EBX + -1;
  pcVar4 = unaff_EDX + (~uVar3 - 1);
  pcVar5 = unaff_EDX + iVar2;
  while (pcVar4 != unaff_EDX) {
    pcVar4 = pcVar4 + -1;
    iVar2 = iVar2 + -1;
    *pcVar5 = *pcVar4;
    pcVar5 = pcVar5 + -1;
  }
  pcVar4 = unaff_EDX + iVar2;
  for (; -1 < iVar2; iVar2 = iVar2 + -1) {
    *pcVar4 = '0';
    pcVar4 = pcVar4 + -1;
  }
  unaff_EDX[unaff_EBX] = '\0';
  return;
}


// ================================================================================================
// __prtf_fixed @ 0x9a1d3 [__watcall]
// ================================================================================================

void __watcall __prtf_fixed(char *param_1,uint unaff_EDX,int unaff_EBX)

{
  int iVar1;
  char *pcVar2;
  char *pcVar3;
  char *pcVar4;
  
  pcVar2 = param_1;
  if ((int)unaff_EDX < 0) {
    unaff_EDX = -unaff_EDX;
    pcVar2 = param_1 + 1;
    *param_1 = '-';
  }
  if (*(int *)(unaff_EBX + 8) == -1) {
    *(undefined4 *)(unaff_EBX + 8) = 4;
  }
  itoa(unaff_EDX >> 0x10,pcVar2,10);
  pcVar4 = pcVar2;
  do {
    pcVar3 = pcVar4;
    pcVar4 = pcVar3 + 1;
  } while (*pcVar3 != '\0');
  if (*(int *)(unaff_EBX + 8) != 0) {
    *pcVar3 = '.';
    for (iVar1 = 0; iVar1 < *(int *)(unaff_EBX + 8); iVar1 = iVar1 + 1) {
      unaff_EDX = (unaff_EDX & 0xffff) * 10;
      *pcVar4 = (char)(unaff_EDX >> 0x10) + '0';
      pcVar4 = pcVar4 + 1;
    }
    *pcVar4 = '\0';
    pcVar3 = pcVar4;
  }
  if ((unaff_EDX & 0x8000) != 0) {
    while (pcVar3 != pcVar2) {
      pcVar4 = pcVar3 + -1;
      if (*pcVar4 == '.') {
        pcVar4 = pcVar3 + -2;
      }
      if (*pcVar4 != '9') {
        *pcVar4 = *pcVar4 + '\x01';
        return;
      }
      *pcVar4 = '0';
      pcVar3 = pcVar4;
    }
    *pcVar2 = '1';
    pcVar2 = pcVar2 + 1;
    do {
      pcVar4 = pcVar2;
      pcVar2 = pcVar4 + 1;
    } while (*pcVar4 == '0');
    if (*pcVar4 == '.') {
      *pcVar4 = '0';
      pcVar4[1] = '.';
      for (pcVar4 = pcVar4 + 2; *pcVar4 == '0'; pcVar4 = pcVar4 + 1) {
      }
    }
    *pcVar4 = '0';
    pcVar4[1] = '\0';
  }
  return;
}


// ================================================================================================
// __prtf_float_hook @ 0x9a2ae [__watcall]
// ================================================================================================

void __watcall __prtf_float_hook(void)

{
  (*(code *)funcptr_d5668)();
  return;
}


// ================================================================================================
// __prtf_convert @ 0x9a2b5 [__watcall]
// ================================================================================================

undefined8 __watcall __prtf_convert(ushort *param_1,int *unaff_EDX,int unaff_EBX,ushort *unaff_ECX)

{
  byte bVar1;
  uint *puVar2;
  int *piVar3;
  short *psVar4;
  undefined4 *puVar5;
  byte *pbVar6;
  bool bVar7;
  uint uVar8;
  int iVar9;
  ushort uVar10;
  undefined4 uVar11;
  uint unaff_EBP;
  ushort *puVar12;
  ushort in_DS;
  ushort uVar13;
  bool bVar14;
  undefined8 uVar15;
  
  bVar7 = true;
  bVar1 = *(byte *)(unaff_EBX + 0x15);
  *(undefined4 *)(unaff_EBX + 0xc) = 0;
  if (bVar1 < 0x69) {
    if (0x57 < bVar1) {
      if (bVar1 < 0x59) goto LAB_0009a302;
      if (bVar1 == 100) goto LAB_0009a336;
    }
  }
  else {
    if (0x69 < bVar1) {
      if (bVar1 < 0x75) {
        bVar14 = bVar1 == 0x6f;
      }
      else {
        if (bVar1 < 0x76) goto LAB_0009a302;
        bVar14 = bVar1 == 0x78;
      }
      if (!bVar14) goto LAB_0009a340;
LAB_0009a302:
      if ((*(byte *)(unaff_EBX + 0x14) & 0x20) == 0) {
        if ((*(byte *)(unaff_EBX + 0x14) & 0x10) == 0) {
          puVar2 = (uint *)*unaff_EDX;
          *unaff_EDX = (int)(puVar2 + 1);
          unaff_EBP = *puVar2;
        }
        else {
          puVar12 = (ushort *)*unaff_EDX;
          *unaff_EDX = (int)(puVar12 + 2);
          unaff_EBP = (uint)*puVar12;
        }
      }
      else {
        puVar2 = (uint *)*unaff_EDX;
        *unaff_EDX = (int)(puVar2 + 1);
        unaff_EBP = *puVar2;
      }
      *(byte *)(unaff_EBX + 0x14) = *(byte *)(unaff_EBX + 0x14) & 0xf9;
    }
LAB_0009a336:
    if (*(int *)(unaff_EBX + 8) != -1) {
      *(undefined *)(unaff_EBX + 0x16) = 0x20;
    }
  }
LAB_0009a340:
  bVar1 = *(byte *)(unaff_EBX + 0x15);
  uVar11 = 10;
  puVar12 = param_1;
  uVar10 = in_DS;
  uVar13 = in_DS;
  if (bVar1 < 0x65) {
    if (bVar1 < 0x50) {
      if (bVar1 < 0x46) {
        bVar14 = bVar1 == 0x45;
      }
      else {
        if (bVar1 < 0x47) goto LAB_0009a3ec;
        bVar14 = bVar1 == 0x47;
      }
      if (!bVar14) goto LAB_0009a639;
      goto LAB_0009a416;
    }
    if (0x50 < bVar1) {
      if (bVar1 < 0x58) {
        if (bVar1 != 0x53) goto LAB_0009a639;
LAB_0009a4a5:
        param_1 = unaff_ECX;
        if ((*(byte *)(unaff_EBX + 0x14) & 0x80) == 0) {
          if ((*(byte *)(unaff_EBX + 0x14) & 0x40) == 0) {
            puVar5 = (undefined4 *)*unaff_EDX;
            *unaff_EDX = (int)(puVar5 + 1);
            puVar12 = (ushort *)*puVar5;
          }
          else {
            puVar5 = (undefined4 *)*unaff_EDX;
            *unaff_EDX = (int)(puVar5 + 1);
            puVar12 = (ushort *)*puVar5;
          }
          if (puVar12 != (ushort *)0x0) {
            param_1 = puVar12;
          }
        }
        else {
          puVar5 = (undefined4 *)*unaff_EDX;
          *unaff_EDX = (int)(puVar5 + 2);
          if (((ushort *)*puVar5 != (ushort *)0x0) || (*(ushort *)(puVar5 + 1) != 0)) {
            param_1 = (ushort *)*puVar5;
            uVar10 = *(ushort *)(puVar5 + 1);
          }
        }
        bVar1 = *(byte *)(unaff_EBX + 0x14);
        bVar7 = false;
        *(byte *)(unaff_EBX + 0x14) = bVar1 & 0xf9;
        if (*(char *)(unaff_EBX + 0x15) == 'S') {
          if ((bVar1 & 0x20) == 0) {
            uVar8 = (uint)*(byte *)param_1;
            param_1 = (ushort *)((int)param_1 + 1);
          }
          else {
            uVar8 = (uint)*param_1;
            param_1 = param_1 + 1;
          }
        }
        else {
          if ((bVar1 & 0x20) == 0) {
            uVar8 = (uint)uVar10;
            uVar11 = *(undefined4 *)(unaff_EBX + 8);
            goto LAB_0009a45b;
          }
          uVar8 = __prtf_wstrnlen(param_1,uVar10,*(undefined4 *)(unaff_EBX + 8));
        }
      }
      else {
        if (bVar1 < 0x59) {
LAB_0009a551:
          if (((*(byte *)(unaff_EBX + 0x14) & 1) != 0) && (unaff_EBP != 0)) {
            *(undefined *)(unaff_EBX + 0x17) = 0x30;
            *(undefined *)(unaff_EBX + 0x19) = 0;
            *(undefined *)(unaff_EBX + 0x18) = *(undefined *)(unaff_EBX + 0x15);
          }
          uVar11 = 0x10;
LAB_0009a56e:
          ultoa(unaff_EBP,param_1,uVar11);
          if (*(char *)(unaff_EBX + 0x15) == 'X') {
            __prtf_upper(param_1);
          }
          goto LAB_0009a443;
        }
        if (bVar1 < 99) goto LAB_0009a639;
        if (99 < bVar1) goto LAB_0009a465;
        pbVar6 = (byte *)*unaff_EDX;
        *unaff_EDX = (int)(pbVar6 + 4);
        bVar1 = *pbVar6;
        *(byte *)((int)param_1 + 1) = 0;
        *(byte *)param_1 = bVar1;
        *(undefined4 *)(unaff_EBX + 8) = 1;
        uVar8 = 1;
        bVar7 = false;
        *(byte *)(unaff_EBX + 0x14) = *(byte *)(unaff_EBX + 0x14) & 0xf9;
      }
      goto LAB_0009a663;
    }
LAB_0009a58d:
    if (*(int *)(unaff_EBX + 4) == 0) {
      if ((*(byte *)(unaff_EBX + 0x14) & 0x80) == 0) {
        *(undefined4 *)(unaff_EBX + 4) = 8;
      }
      else {
        *(undefined4 *)(unaff_EBX + 4) = 0xd;
      }
    }
    *(byte *)(unaff_EBX + 0x14) = *(byte *)(unaff_EBX + 0x14) & 0xf9;
    puVar5 = (undefined4 *)*unaff_EDX;
    *unaff_EDX = (int)(puVar5 + 1);
    uVar11 = *puVar5;
    if ((*(byte *)(unaff_EBX + 0x14) & 0x80) != 0) {
      *unaff_EDX = (int)(puVar5 + 2);
      __prtf_fmt4hex(puVar5[1] & 0xffff,param_1,4);
      *(byte *)(param_1 + 2) = 0x3a;
      puVar12 = (ushort *)((int)param_1 + 5);
    }
    __prtf_fmt4hex(uVar11,puVar12,8);
    if (*(char *)(unaff_EBX + 0x15) == 'P') {
      __prtf_upper(param_1);
    }
LAB_0009a452:
    uVar11 = 0xffffffff;
    uVar8 = (uint)in_DS;
    uVar10 = in_DS;
    in_DS = uVar13;
LAB_0009a45b:
    uVar8 = __prtf_strnlen(param_1,uVar8,uVar11);
  }
  else {
    if (bVar1 < 0x66) {
LAB_0009a416:
      uVar15 = __prtf_float_hook(param_1,unaff_EDX,unaff_EBX);
      uVar8 = (uint)((ulonglong)uVar15 >> 0x20);
      param_1 = (ushort *)uVar15;
      uVar11 = 0xffffffff;
      uVar10 = (ushort)((ulonglong)uVar15 >> 0x20);
      goto LAB_0009a45b;
    }
    if (bVar1 < 0x6f) {
      if (bVar1 < 0x67) {
LAB_0009a3ec:
        if ((*(byte *)(unaff_EBX + 0x14) & 0x10) != 0) {
          puVar5 = (undefined4 *)*unaff_EDX;
          *unaff_EDX = (int)(puVar5 + 1);
          __prtf_fixed(param_1,*puVar5,unaff_EBX);
          uVar11 = 0xffffffff;
          uVar8 = (uint)uVar10;
          in_DS = uVar10;
          goto LAB_0009a45b;
        }
      }
      else if (0x67 < bVar1) {
        if (bVar1 == 0x69) {
LAB_0009a465:
          if ((*(byte *)(unaff_EBX + 0x14) & 0x20) == 0) {
            if ((*(byte *)(unaff_EBX + 0x14) & 0x10) == 0) {
              puVar5 = (undefined4 *)*unaff_EDX;
              *unaff_EDX = (int)(puVar5 + 1);
              itoa(*puVar5,param_1);
              goto LAB_0009a443;
            }
            psVar4 = (short *)*unaff_EDX;
            *unaff_EDX = (int)(psVar4 + 2);
            iVar9 = (int)*psVar4;
          }
          else {
            piVar3 = (int *)*unaff_EDX;
            *unaff_EDX = (int)(piVar3 + 1);
            iVar9 = *piVar3;
          }
          ltoa(iVar9,param_1);
          goto LAB_0009a443;
        }
        goto LAB_0009a639;
      }
      goto LAB_0009a416;
    }
    if (bVar1 < 0x70) {
      if ((*(byte *)(unaff_EBX + 0x14) & 1) != 0) {
        *(byte *)param_1 = 0x30;
        puVar12 = (ushort *)((int)param_1 + 1);
      }
      ltoa(unaff_EBP,puVar12,8);
LAB_0009a443:
      if ((*(int *)(unaff_EBX + 8) == 0) && (*(byte *)puVar12 == 0x30)) {
        *(byte *)param_1 = 0;
      }
      goto LAB_0009a452;
    }
    if (bVar1 < 0x73) {
      if (bVar1 == 0x70) goto LAB_0009a58d;
    }
    else {
      if (bVar1 < 0x74) goto LAB_0009a4a5;
      if (0x74 < bVar1) {
        if (bVar1 < 0x76) goto LAB_0009a56e;
        if (bVar1 == 0x78) goto LAB_0009a551;
      }
    }
LAB_0009a639:
    *(undefined4 *)(unaff_EBX + 4) = 0;
    bVar1 = *(byte *)(unaff_EBX + 0x15);
    *(byte *)((int)param_1 + 1) = 0;
    *(byte *)param_1 = bVar1;
    *(undefined4 *)(unaff_EBX + 8) = 1;
    bVar7 = false;
    *(byte *)(unaff_EBX + 0x14) = *(byte *)(unaff_EBX + 0x14) & 0xf9;
    uVar8 = 1;
  }
LAB_0009a663:
  if (!bVar7) goto LAB_0009a6a9;
  if (*(byte *)param_1 == 0x2d) {
    param_1 = (ushort *)((int)param_1 + 1);
    *(undefined *)(unaff_EBX + 0x18) = 0;
    uVar8 = uVar8 - 1;
    *(undefined *)(unaff_EBX + 0x17) = 0x2d;
  }
  else {
    if ((*(byte *)(unaff_EBX + 0x14) & 2) == 0) {
      if ((*(byte *)(unaff_EBX + 0x14) & 4) == 0) goto LAB_0009a698;
      *(undefined *)(unaff_EBX + 0x17) = 0x2b;
    }
    else {
      *(undefined *)(unaff_EBX + 0x17) = 0x20;
    }
    *(undefined *)(unaff_EBX + 0x18) = 0;
  }
LAB_0009a698:
  if (*(int *)(unaff_EBX + 8) < (int)uVar8) {
    *(uint *)(unaff_EBX + 8) = uVar8;
  }
  else {
    *(uint *)(unaff_EBX + 0xc) = *(int *)(unaff_EBX + 8) - uVar8;
  }
LAB_0009a6a9:
  if (*(char *)(unaff_EBX + 0x16) == '*') {
    *(undefined *)(unaff_EBX + 0x17) = 0;
    *(byte *)(unaff_EBX + 0x14) = *(byte *)(unaff_EBX + 0x14) & 0xf9;
  }
  if (((*(int *)(unaff_EBX + 8) == -1) || ((int)uVar8 < *(int *)(unaff_EBX + 8))) &&
     (*(char *)(unaff_EBX + 0x15) != 'c')) {
    *(uint *)(unaff_EBX + 8) = uVar8;
  }
  iVar9 = __prtf_strnlen(unaff_EBX + 0x17,in_DS,0xffffffff);
  *(int *)(unaff_EBX + 4) =
       *(int *)(unaff_EBX + 4) - (iVar9 + *(int *)(unaff_EBX + 8) + *(int *)(unaff_EBX + 0xc));
  return CONCAT44(CONCAT22((short)((uint)*(int *)(unaff_EBX + 0xc) >> 0x10),uVar10),param_1);
}


// ================================================================================================
// __prtf_upper @ 0x9a6fe [__watcall]
// ================================================================================================

void __watcall __prtf_upper(byte *param_1)

{
  int iVar1;
  
  for (; *param_1 != 0; param_1 = param_1 + 1) {
    iVar1 = toupper((uint)*param_1);
    *param_1 = (byte)iVar1;
  }
  return;
}


// ================================================================================================
// __doserror @ 0x9a716 [__watcall]
// ================================================================================================

undefined2 __watcall __doserror(undefined2 param_1)

{
  bool in_CF;
  
  if (in_CF) {
    __set_errno_dos();
  }
  else {
    param_1 = 0;
  }
  return param_1;
}


// ================================================================================================
// __doserror_ret @ 0x9a729 [__watcall]
// ================================================================================================

ulonglong __watcall __doserror_ret(uint param_1,int unaff_EDX)

{
  uint uVar1;
  byte bVar2;
  uint extraout_EDX;
  
  if (unaff_EDX == 0) {
    return 0;
  }
  if (unaff_EDX == 0) {
    return (ulonglong)param_1;
  }
  uVar1 = param_1 & 0xff;
  __set_doserrno(param_1 & 0xff);
  if (extraout_EDX < 0x100) {
    if (2 < byte_d4d0f) {
      bVar2 = (byte)extraout_EDX;
      if (bVar2 == 0x50) {
        uVar1 = 0xe;
      }
      else if (bVar2 < 0x22) {
        if (0x1f < bVar2) {
          uVar1 = 5;
        }
      }
      else {
        uVar1 = 0x13;
      }
    }
    if (0x13 < (byte)uVar1) {
      uVar1 = 0x13;
    }
    uVar1 = *(int *)(&unk_d4ff1 + uVar1) >> 0x18;
  }
  else {
    uVar1 = extraout_EDX >> 8 & 0xff;
  }
  __set_errno(uVar1);
  return CONCAT44(unaff_EDX,0xffffffff);
}


// ================================================================================================
// __set_errno_dos_entry @ 0x9a730 [__watcall]
// ================================================================================================

ulonglong __watcall __set_errno_dos_entry(uint param_1,int unaff_EDX)

{
  uint uVar1;
  byte bVar2;
  uint extraout_EDX;
  
  if (unaff_EDX == 0) {
    return (ulonglong)param_1;
  }
  uVar1 = param_1 & 0xff;
  __set_doserrno(param_1 & 0xff);
  if (extraout_EDX < 0x100) {
    if (2 < byte_d4d0f) {
      bVar2 = (byte)extraout_EDX;
      if (bVar2 == 0x50) {
        uVar1 = 0xe;
      }
      else if (bVar2 < 0x22) {
        if (0x1f < bVar2) {
          uVar1 = 5;
        }
      }
      else {
        uVar1 = 0x13;
      }
    }
    if (0x13 < (byte)uVar1) {
      uVar1 = 0x13;
    }
    uVar1 = *(int *)(&unk_d4ff1 + uVar1) >> 0x18;
  }
  else {
    uVar1 = extraout_EDX >> 8 & 0xff;
  }
  __set_errno(uVar1);
  return CONCAT44(unaff_EDX,0xffffffff);
}


// ================================================================================================
// __set_errno_dos @ 0x9a735 [__watcall]
// ================================================================================================

undefined8 __watcall __set_errno_dos(byte param_1,undefined4 unaff_EDX)

{
  uint uVar1;
  byte bVar2;
  uint extraout_EDX;
  
  uVar1 = (uint)param_1;
  __set_doserrno(param_1);
  if (extraout_EDX < 0x100) {
    if (2 < byte_d4d0f) {
      bVar2 = (byte)extraout_EDX;
      if (bVar2 == 0x50) {
        uVar1 = 0xe;
      }
      else if (bVar2 < 0x22) {
        if (0x1f < bVar2) {
          uVar1 = 5;
        }
      }
      else {
        uVar1 = 0x13;
      }
    }
    if (0x13 < (byte)uVar1) {
      uVar1 = 0x13;
    }
    uVar1 = *(int *)(&unk_d4ff1 + uVar1) >> 0x18;
  }
  else {
    uVar1 = extraout_EDX >> 8 & 0xff;
  }
  __set_errno(uVar1);
  return CONCAT44(unaff_EDX,0xffffffff);
}


// ================================================================================================
// windowdef @ 0x9a7a0 [__cdecl]
// ================================================================================================

int * windowdef(int param_1,int param_2,undefined4 param_3)

{
  int *piVar1;
  int *piVar2;
  byte *pbVar3;
  int iVar4;
  
  piVar2 = (int *)reservemem_fatal(aMCGAWINDOW,param_1 * param_2 + 0x40,param_3);
  if (piVar2 == (int *)0x0) {
    fatalerror(aWindowdefOUTOFMEMORY);
  }
  piVar1 = (int *)*piVar2;
  if (piVar1 == (int *)0x0) {
    fatalerror(s__windowdef___BAD_BLOCK_000c48af + 1);
  }
  pbVar3 = (byte *)identity_8e3c4(piVar1 + 0xc);
  memzero(piVar1,0x40);
  *(short *)(pbVar3 + 4) = (short)param_1;
  *(short *)(pbVar3 + 6) = (short)param_2;
  pbVar3[0] = 0;
  pbVar3[1] = 0;
  pbVar3[2] = 0;
  pbVar3[3] = 0;
  *pbVar3 = *pbVar3 | 1;
  *piVar1 = param_1;
  piVar1[8] = param_1;
  piVar1[4] = param_1;
  piVar1[7] = param_1;
  piVar1[1] = param_2;
  piVar1[5] = param_2;
  piVar1[0xb] = (int)pbVar3;
  iVar4 = window_alloc_slot(0x10,param_1,param_2);
  piVar1[10] = iVar4;
  if (iVar4 == 0) {
    fatalerror(s_gwindowdefadr___OUT_OF_ROW_SPACE_000c48c7 + 1,param_1,param_2);
  }
  return piVar2;
}


// ================================================================================================
// __MemAllocator @ 0x9a874 [__watcall]
// ================================================================================================

uint * __watcall __MemAllocator(uint param_1,undefined4 param_2,int unaff_EBX)

{
  uint uVar1;
  uint uVar2;
  uint *puVar3;
  uint uVar4;
  uint *puVar5;
  
  if (((param_1 != 0) && (param_1 < 0xfffffff9)) &&
     (uVar2 = param_1 + 7 & 0xfffffffc, uVar2 = (uVar2 - 0xc & -(uint)(0xb < uVar2)) + 0xc,
     uVar2 <= *(uint *)(unaff_EBX + 0x14))) {
    puVar3 = *(uint **)(unaff_EBX + 0xc);
    uVar4 = *(uint *)(unaff_EBX + 0x10);
    if (uVar2 <= uVar4) {
      puVar3 = *(uint **)(unaff_EBX + 0x28);
      uVar4 = 0;
    }
    do {
      uVar1 = *puVar3;
      if (uVar2 <= uVar1) {
        *(uint *)(unaff_EBX + 0x10) = uVar4;
        *(int *)(unaff_EBX + 0x18) = *(int *)(unaff_EBX + 0x18) + 1;
        uVar4 = puVar3[2];
        if (uVar1 - uVar2 < 0xc) {
          *(int *)(unaff_EBX + 0x1c) = *(int *)(unaff_EBX + 0x1c) + -1;
          uVar2 = puVar3[1];
          *(uint *)(uVar2 + 8) = uVar4;
          *(uint *)(uVar4 + 4) = uVar2;
          *(uint *)(unaff_EBX + 0xc) = uVar2;
        }
        else {
          puVar5 = (uint *)((int)puVar3 + uVar2);
          *(uint **)(unaff_EBX + 0xc) = puVar5;
          *puVar5 = uVar1 - uVar2;
          *puVar3 = uVar2;
          uVar2 = puVar3[1];
          puVar5[1] = uVar2;
          puVar5[2] = uVar4;
          *(uint **)(uVar2 + 8) = puVar5;
          *(uint **)(uVar4 + 4) = puVar5;
        }
        *puVar3 = *puVar3 | 1;
        return puVar3 + 1;
      }
      uVar4 = (uVar4 - uVar1 & -(uint)(uVar1 <= uVar4)) + uVar1;
      puVar3 = (uint *)puVar3[2];
    } while (puVar3 != (uint *)(unaff_EBX + 0x20U));
    *(uint *)(unaff_EBX + 0x14) = uVar4;
  }
  return (uint *)0x0;
}


// ================================================================================================
// empty_func_9a917 @ 0x9a917 [__watcall]
// ================================================================================================

void __watcall empty_func_9a917(void)

{
  return;
}


// ================================================================================================
// __MemFree @ 0x9a91c [__watcall]
// ================================================================================================

void __watcall __MemFree(undefined4 *param_1,undefined4 param_2,int unaff_EBX)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint *puVar4;
  uint *puVar5;
  uint *puVar6;
  
  if (param_1 == (undefined4 *)0x0) {
    return;
  }
  puVar4 = param_1 + -1;
  if ((*puVar4 & 1) == 0) {
    return;
  }
  uVar3 = *puVar4 & 0xfffffffe;
  puVar6 = (uint *)((int)puVar4 + uVar3);
  if ((*puVar6 & 1) == 0) {
    if (puVar6 == *(uint **)(unaff_EBX + 0xc)) {
      *(uint **)(unaff_EBX + 0xc) = puVar4;
    }
    *puVar4 = uVar3 + *puVar6;
    uVar3 = puVar6[1];
    puVar6 = (uint *)puVar6[2];
    *(uint **)(uVar3 + 8) = puVar6;
    puVar6[1] = uVar3;
    *(int *)(unaff_EBX + 0x1c) = *(int *)(unaff_EBX + 0x1c) + -1;
  }
  else {
    *puVar4 = uVar3;
    puVar6 = *(uint **)(unaff_EBX + 0xc);
    if (puVar4 < puVar6) {
      if (((uint *)puVar6[1] < puVar4) || (puVar6 = *(uint **)(unaff_EBX + 0x28), puVar4 < puVar6))
      goto LAB_0009a9da;
    }
    else {
      puVar6 = (uint *)puVar6[2];
      if ((puVar4 < puVar6) ||
         (puVar6 = (uint *)(unaff_EBX + 0x20), *(uint **)(unaff_EBX + 0x24) < puVar4))
      goto LAB_0009a9da;
    }
    uVar3 = *(uint *)(unaff_EBX + 0x1c);
    uVar1 = *(uint *)(unaff_EBX + 0x18) / (uVar3 + 1);
    if (uVar1 < uVar3) {
      iVar2 = uVar1 * 2;
      if (*(int *)(unaff_EBX + 0x18) - uVar3 <= uVar3) {
        iVar2 = 0;
      }
      puVar6 = (uint *)((int)puVar4 + *puVar4);
      do {
        uVar3 = *puVar6;
        if ((uVar3 & 1) == 0) goto LAB_0009a9da;
        if (uVar3 == 0xffffffff) break;
        puVar6 = (uint *)((int)puVar6 + (uVar3 & 0xfffffffe));
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
    }
    puVar6 = *(uint **)(unaff_EBX + 0xc);
    if (puVar4 < puVar6) {
      puVar6 = *(uint **)(unaff_EBX + 0x28);
    }
    while (((puVar6 <= puVar4 && (puVar6 = (uint *)puVar6[2], puVar6 <= puVar4)) &&
           (puVar6 = (uint *)puVar6[2], puVar6 <= puVar4))) {
      puVar6 = (uint *)puVar6[2];
    }
  }
LAB_0009a9da:
  puVar5 = (uint *)puVar6[1];
  uVar3 = *puVar4;
  if ((uint *)((int)puVar5 + *puVar5) == puVar4) {
    uVar3 = uVar3 + *puVar5;
    *puVar5 = uVar3;
    if (puVar4 == *(uint **)(unaff_EBX + 0xc)) {
      *(uint **)(unaff_EBX + 0xc) = puVar5;
    }
  }
  else {
    *(int *)(unaff_EBX + 0x1c) = *(int *)(unaff_EBX + 0x1c) + 1;
    param_1[1] = puVar6;
    *param_1 = puVar5;
    puVar5[2] = (uint)puVar4;
    puVar6[1] = (uint)puVar4;
    puVar5 = puVar4;
  }
  *(int *)(unaff_EBX + 0x18) = *(int *)(unaff_EBX + 0x18) + -1;
  if ((puVar5 < *(uint **)(unaff_EBX + 0xc)) && (*(uint *)(unaff_EBX + 0x10) < uVar3)) {
    *(uint *)(unaff_EBX + 0x10) = uVar3;
  }
  if (*(uint *)(unaff_EBX + 0x14) < uVar3) {
    *(uint *)(unaff_EBX + 0x14) = uVar3;
  }
  return;
}


// ================================================================================================
// FUN_0009aa22 @ 0x9aa22
// ================================================================================================

void __watcall FUN_0009aa22(void)

{
  return;
}


// ================================================================================================
// __unlink_heap @ 0x9aa27 [__watcall]
// ================================================================================================

void __watcall __unlink_heap(int param_1)

{
  int iVar1;
  int iVar2;
  
  if (param_1 == dword_d43ec) {
    dword_d43ec = *(int *)(dword_d43ec + 8);
  }
  if (param_1 == dword_d43e8) {
    dword_d43e8 = *(int *)(dword_d43e8 + 8);
  }
  iVar1 = *(int *)(param_1 + 4);
  iVar2 = *(int *)(param_1 + 8);
  if (iVar1 != 0) {
    *(int *)(iVar1 + 8) = iVar2;
  }
  if (iVar2 != 0) {
    *(int *)(iVar2 + 4) = iVar1;
  }
  return;
}


// ================================================================================================
// __ReleaseUnusedHeap @ 0x9aa66 [__watcall]
// ================================================================================================

undefined8 __watcall __ReleaseUnusedHeap(undefined4 param_1)

{
  int iVar1;
  code *pcVar2;
  int *piVar3;
  undefined2 *puVar4;
  undefined2 in_ES;
  byte bVar5;
  undefined8 uVar6;
  undefined4 uStack_18;
  
  uVar6 = CONCAT44(dword_d43e8,param_1);
  puVar4 = (undefined2 *)&stack0xffffffec;
  while (piVar3 = (int *)((ulonglong)uVar6 >> 0x20), piVar3 != (int *)0x0) {
    if (*(int *)piVar3[9] + 0x2c == *piVar3) {
      iVar1 = piVar3[2];
      *(undefined4 *)(puVar4 + -2) = 0x9aa94;
      __unlink_heap(piVar3,piVar3,piVar3 + -2,iVar1);
      bVar5 = 0;
      if (piVar3[-1] == 0) {
        pcVar2 = (code *)swi(0x31);
        uVar6 = (*pcVar2)();
        puVar4 = puVar4 + 2;
      }
      else {
        puVar4[-2] = in_ES;
        pcVar2 = (code *)swi(0x21);
        uVar6 = (*pcVar2)();
        uVar6 = CONCAT44((int)((ulonglong)uVar6 >> 0x20),
                         ((int)uVar6 << 1 | (uint)bVar5) >> 1 | (uint)((bVar5 & 1) != 0) << 0x1f);
        in_ES = *puVar4;
        puVar4 = puVar4 + 2;
      }
    }
    else {
      uVar6 = CONCAT44(piVar3[2],*(int *)piVar3[9] + 0x2c);
    }
  }
  return CONCAT44(*(undefined4 *)(puVar4 + 4),(int)uVar6);
}


// ================================================================================================
// _heapshrink_seg @ 0x9aac4 [__watcall]
// ================================================================================================

uint * __watcall _heapshrink_seg(int *param_1,uint unaff_EDX)

{
  undefined2 uVar1;
  undefined2 uVar2;
  uint uVar3;
  code *pcVar4;
  undefined2 *puVar5;
  uint *puVar6;
  uint *puVar7;
  undefined2 extraout_CX;
  int *extraout_EDX;
  uint3 uVar9;
  int extraout_EDX_00;
  int *piVar8;
  byte bVar10;
  
  __ReleaseUnusedHeap();
  piVar8 = dword_d43e8;
  while( true ) {
    if (piVar8 == (int *)0x0) {
      return (uint *)0x0;
    }
    if (param_1 < piVar8) {
      return (uint *)0x0;
    }
    if (piVar8 + 0xb == param_1) break;
    piVar8 = (int *)piVar8[2];
  }
  __unlink_heap(piVar8);
  if (extraout_EDX[-1] != 0) {
    return (uint *)0x0;
  }
  uVar9 = (uint3)(*extraout_EDX + (unaff_EDX - *param_1) + 0x100b >> 8) & 0xfffff0;
  bVar10 = (((uint)uVar9 << 8) >> 0xf & 1) != 0;
  uVar1 = *(undefined2 *)(extraout_EDX + -2);
  uVar2 = *(undefined2 *)((int)extraout_EDX + -6);
  pcVar4 = (code *)swi(0x31);
  (*pcVar4)();
  puVar5 = (undefined2 *)(1 - (uint)bVar10);
  if (puVar5 != (undefined2 *)0x0) {
    puVar5 = (undefined2 *)CONCAT22((short)(uVar9 >> 8),extraout_CX);
    *puVar5 = uVar1;
    puVar5[1] = uVar2;
  }
  if (puVar5 != (undefined2 *)0x0) {
    *(undefined4 *)(puVar5 + 2) = 0;
    *(int *)(puVar5 + 4) = extraout_EDX_00 + -0xc;
    puVar6 = (uint *)__LinkUpNewMHeap(puVar5 + 4);
    *(undefined4 *)(puVar5 + 0x10) = 1;
    uVar3 = *puVar6;
    if (0xb < uVar3 - unaff_EDX) {
      *puVar6 = unaff_EDX | 1;
      puVar7 = (uint *)((int)puVar6 + (unaff_EDX | 1) & 0xfffffffe);
      *puVar7 = uVar3 - unaff_EDX | 1;
      *(undefined4 *)(puVar5 + 0xe) = 0xffffffff;
      *(int *)(puVar5 + 0x10) = *(int *)(puVar5 + 0x10) + 1;
      free(puVar7 + 1);
      return puVar6;
    }
    return puVar6;
  }
  return (uint *)0x0;
}


// ================================================================================================
// __LinkUpNewMHeap @ 0x9abae [__watcall]
// ================================================================================================

undefined8 __watcall __LinkUpNewMHeap(int *param_1,undefined4 unaff_EDX)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  
  piVar1 = dword_d43e8;
  piVar3 = (int *)0x0;
  while ((piVar2 = piVar1, piVar2 != (int *)0x0 && (piVar2 <= param_1))) {
    piVar3 = piVar2;
    piVar1 = (int *)piVar2[2];
  }
  param_1[1] = (int)piVar3;
  param_1[2] = (int)piVar2;
  piVar1 = param_1;
  if (piVar3 != (int *)0x0) {
    piVar3[2] = (int)param_1;
    piVar1 = dword_d43e8;
  }
  dword_d43e8 = piVar1;
  if (piVar2 != (int *)0x0) {
    piVar2[1] = (int)param_1;
  }
  piVar1 = param_1 + 8;
  piVar3 = param_1 + 0xb;
  param_1[8] = 0;
  param_1[4] = 0;
  param_1[6] = 0;
  param_1[7] = 0;
  param_1[9] = (int)piVar1;
  param_1[10] = (int)piVar1;
  param_1[3] = (int)piVar1;
  *piVar3 = *param_1 + -0x2c;
  *(undefined4 *)((int)piVar3 + *param_1 + -0x2c) = 0xffffffff;
  return CONCAT44(unaff_EDX,piVar3);
}


// ================================================================================================
// __LastFree @ 0x9ac22 [__watcall]
// ================================================================================================

longlong __watcall __LastFree(undefined4 param_1,uint unaff_EDX)

{
  int *piVar1;
  undefined3 uVar2;
  ushort in_DS;
  
  if (dword_d43e8 != 0) {
    piVar1 = *(int **)(dword_d43e8 + 0x24);
    if (((1 < byte_d4d06) && (byte_d4d06 < 9)) && (byte_d4d08 == '\0')) {
      uVar2 = SegmentLimit((uint)in_DS);
      dword_d4cd8 = (ushort)uVar2 + 1;
    }
    if ((int)piVar1 + *piVar1 + 4 == dword_d4cd8) {
      return CONCAT44(unaff_EDX,*piVar1);
    }
  }
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// __RationalAlloc_dpmi @ 0x9ac70 [__watcall]
// ================================================================================================

undefined8 __watcall __RationalAlloc_dpmi(uint param_1,undefined4 param_2,int unaff_EBX)

{
  code *pcVar1;
  bool bVar2;
  undefined2 *puVar3;
  int iVar4;
  int *piVar5;
  undefined2 extraout_CX;
  undefined2 extraout_CX_00;
  undefined2 extraout_DX;
  undefined *puVar6;
  uint unaff_ESI;
  undefined *unaff_EDI;
  byte bVar7;
  
  __ReleaseUnusedHeap();
  bVar7 = (param_1 >> 0xf & 1) != 0;
  pcVar1 = (code *)swi(0x31);
  (*pcVar1)();
  puVar6 = &stack0xffffffec;
  puVar3 = (undefined2 *)(1 - (uint)bVar7);
  if (puVar3 != (undefined2 *)0x0) {
    puVar3 = (undefined2 *)CONCAT22((short)(param_1 >> 0x10),extraout_CX);
    *puVar3 = (short)unaff_EDI;
    puVar3[1] = (short)unaff_ESI;
  }
  if (puVar3 == (undefined2 *)0x0) {
    if ((dword_f58e0 & 0xfff00000) != 0) {
      dword_f58e0 = 0xfffff;
    }
    puVar6 = &stack0xffffffec;
    if (unaff_EDI < &UNK_00010001) {
      bVar7 = 0;
      pcVar1 = (code *)swi(0x21);
      (*pcVar1)();
      puVar6 = &stack0xfffffff0;
      if ((bVar7 & 1) == 0) {
        bVar7 = (unaff_ESI >> 3 & 1) != 0;
        pcVar1 = (code *)swi(0x21);
        iVar4 = (*pcVar1)();
        bVar2 = (bVar7 & 1) != 0;
        pcVar1 = (code *)swi(0x21);
        (*pcVar1)();
        puVar6 = &stack0xfffffff8;
        if (!bVar2) {
          pcVar1 = (code *)swi(0x31);
          (*pcVar1)();
          puVar6 = &stack0xfffffffc;
          piVar5 = (int *)(CONCAT22(extraout_CX_00,extraout_DX) + 8);
          *(uint *)(CONCAT22(extraout_CX_00,extraout_DX) + 4) =
               (iVar4 << 1 | (uint)bVar7) >> 1 | (uint)bVar2 << 0x1f;
          *piVar5 = unaff_EBX + -8;
          goto LAB_0009ad3a;
        }
      }
    }
    piVar5 = (int *)0x0;
  }
  else {
    piVar5 = (int *)(puVar3 + 4);
    *piVar5 = (int)(unaff_EDI + -8);
    *(undefined4 *)(puVar3 + 2) = 0;
  }
LAB_0009ad3a:
  return CONCAT44(*(undefined4 *)(puVar6 + 0xc),piVar5);
}


// ================================================================================================
// __CreateNewNHeap @ 0x9ad43 [__watcall]
// ================================================================================================

undefined8 __watcall __CreateNewNHeap(uint param_1)

{
  code *pcVar1;
  int iVar2;
  uint *puVar3;
  uint uVar4;
  uint *puVar5;
  uint *puVar6;
  uint *puVar7;
  byte bVar8;
  undefined8 uVar9;
  uint local_18;
  
  puVar7 = &local_18;
  local_18 = param_1;
  puVar5 = &local_18;
  if ((dword_d5670 != 0) && (puVar5 = &local_18, dword_d4cd8 != -2)) {
    iVar2 = __AdjustAmount(&local_18);
    if (iVar2 == 0) goto LAB_0009ad3a;
    bVar8 = byte_d4d06 == '\0';
    if (byte_d4d06 == '\x01') {
      puVar3 = (uint *)__RationalAlloc_dpmi(local_18);
      puVar6 = puVar3;
      puVar7 = &local_18;
      if (puVar3 != (uint *)0x0) {
        local_18 = *puVar3;
        puVar7 = &local_18;
      }
    }
    else {
      pcVar1 = (code *)swi(0x21);
      uVar4 = (*pcVar1)();
      puVar7 = (uint *)&stack0xffffffec;
      puVar6 = (uint *)~-(uint)bVar8;
      puVar3 = (uint *)(uVar4 & (uint)puVar6);
    }
    puVar5 = puVar7;
    if (((puVar3 != (uint *)0x0) && (uVar4 = *puVar7 - 4, uVar4 <= *puVar7)) &&
       (*puVar7 = uVar4, 0x37 < uVar4)) {
      *puVar3 = uVar4;
      puVar7[-1] = 0x9adc7;
      uVar9 = __LinkUpNewMHeap(puVar3,puVar3,puVar6);
      iVar2 = (int)((ulonglong)uVar9 >> 0x20);
      puVar5 = (uint *)uVar9;
      uVar4 = *puVar5;
      *puVar7 = uVar4;
      *puVar5 = uVar4 | 1;
      *(undefined4 *)(iVar2 + 0x14) = 0xffffffff;
      *(int *)(iVar2 + 0x18) = *(int *)(iVar2 + 0x18) + 1;
      puVar7[-1] = 0x9ade8;
      free(puVar5 + 1);
      iVar2 = 1;
      goto LAB_0009ad3a;
    }
  }
  puVar7 = puVar5;
  iVar2 = 0;
LAB_0009ad3a:
  return CONCAT44(*(undefined4 *)((int)puVar7 + 0xc),iVar2);
}


// ================================================================================================
// __ExpandDGROUP @ 0x9adf2 [__watcall]
// ================================================================================================

undefined8 __watcall __ExpandDGROUP(uint param_1,undefined4 unaff_EDX)

{
  int *piVar1;
  undefined3 uVar2;
  int iVar3;
  uint *puVar4;
  uint *puVar5;
  uint uVar6;
  uint *puVar7;
  ushort in_DS;
  undefined8 uVar8;
  uint local_18;
  
  local_18 = param_1;
  if (((byte_d4d06 == 1) && (byte_d4d07 == '\0')) || (byte_d4d06 == 9)) {
    iVar3 = __CreateNewNHeap(param_1);
    goto LAB_0009af2d;
  }
  if ((dword_d5670 == 0) || (dword_d4cd8 == 0xfffffffe)) goto LAB_0009ae29;
  iVar3 = __AdjustAmount(&local_18);
  if (iVar3 == 0) goto LAB_0009af2d;
  if (((1 < byte_d4d06) && (byte_d4d06 < 9)) && (byte_d4d08 == '\0')) {
    uVar2 = SegmentLimit((uint)in_DS);
    dword_d4cd8 = (ushort)uVar2 + 1;
  }
  uVar6 = local_18 + dword_d4cd8;
  if (uVar6 < dword_d4cd8) {
    uVar6 = 0xfffffffe;
  }
  uVar8 = __brk(uVar6);
  puVar7 = (uint *)((ulonglong)uVar8 >> 0x20);
  puVar4 = (uint *)uVar8;
  if (((puVar4 != (uint *)0xffffffff) && (puVar4 < (uint *)0xfffffff9)) && (puVar4 < puVar7)) {
    uVar6 = (int)puVar7 - (int)puVar4;
    local_18 = uVar6 - 4;
    puVar7 = dword_d43e8;
    if (local_18 <= uVar6) {
      for (; ((puVar7 != (uint *)0x0 && ((uint *)puVar7[2] != (uint *)0x0)) &&
             ((puVar4 < puVar7 || ((uint *)puVar7[2] <= puVar4)))); puVar7 = (uint *)puVar7[2]) {
      }
      if (puVar7 == (uint *)0x0) {
LAB_0009aef0:
        if (local_18 < 0x38) goto LAB_0009ae29;
        *puVar4 = local_18;
        uVar8 = __LinkUpNewMHeap(puVar4,puVar4);
        local_18 = *(uint *)uVar8;
      }
      else {
        puVar5 = (uint *)(*puVar7 + (int)puVar7);
        uVar8 = CONCAT44(puVar7,puVar5);
        if (puVar4 + -1 != puVar5) goto LAB_0009aef0;
        *puVar7 = *puVar7 + uVar6;
        *(undefined4 *)((int)puVar5 + uVar6) = 0xffffffff;
        local_18 = uVar6;
      }
      iVar3 = (int)((ulonglong)uVar8 >> 0x20);
      *(uint *)uVar8 = local_18 | 1;
      piVar1 = (int *)(iVar3 + 0x18);
      *piVar1 = *piVar1 + 1;
      *(undefined4 *)(iVar3 + 0x14) = 0xffffffff;
      free((uint *)uVar8 + 1);
      iVar3 = 1;
      goto LAB_0009af2d;
    }
  }
LAB_0009ae29:
  iVar3 = 0;
LAB_0009af2d:
  return CONCAT44(unaff_EDX,iVar3);
}


// ================================================================================================
// __AdjustAmount @ 0x9af36 [__watcall]
// ================================================================================================

longlong __watcall __AdjustAmount(uint *param_1,uint unaff_EDX)

{
  uint uVar1;
  undefined8 uVar2;
  
  uVar1 = *param_1 + 3 & 0xfffffffc;
  if (uVar1 != 0) {
    if (((byte_d4d06 == '\x01') && (byte_d4d07 == '\0')) || (byte_d4d06 == '\t')) {
      uVar1 = uVar1 + 8;
    }
    else {
      uVar2 = __LastFree();
      uVar1 = (int)((ulonglong)uVar2 >> 0x20) - (int)uVar2;
    }
    *param_1 = uVar1;
    uVar1 = uVar1 + 0x3c;
    if (*param_1 <= uVar1) {
      if (uVar1 < dword_d5674) {
        uVar1 = dword_d5674 & 0xfffffffe;
      }
      *param_1 = uVar1;
      uVar1 = uVar1 + 0xfff;
      if (*param_1 <= uVar1) {
        *param_1 = (uint)((uint3)(uVar1 >> 8) & 0xfffff0) << 8;
        return CONCAT44(unaff_EDX,(uint)((uVar1 & 0xfffff000) != 0));
      }
    }
  }
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// return_zero_9afad @ 0x9afad [__watcall]
// ================================================================================================

undefined4 __watcall return_zero_9afad(void)

{
  return 0;
}


// ================================================================================================
// tolower @ 0x9afb0 [__watcall]
// ================================================================================================

int __watcall tolower(int __c)

{
  if ((0x40 < __c) && (__c < 0x5b)) {
    __c = __c + 0x20;
  }
  return __c;
}


// ================================================================================================
// __allocfp @ 0x9afbe [__watcall]
// ================================================================================================

undefined8 __watcall __allocfp(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX)

{
  undefined4 *puVar1;
  undefined4 *__s;
  uint uVar2;
  
  if (dword_edf00 == (undefined4 *)0x0) {
    for (__s = (undefined4 *)&unk_d4d18; __s < &aA_d4f20; __s = (undefined4 *)((int)__s + 0x1a)) {
      if ((*(byte *)(__s + 3) & 3) == 0) {
        puVar1 = (undefined4 *)malloc(8);
        if (puVar1 == (undefined4 *)0x0) goto LAB_0009b054;
        uVar2 = 3;
        goto LAB_0009b02f;
      }
    }
    uVar2 = 0x4003;
    puVar1 = (undefined4 *)malloc(0x22);
    __s = puVar1;
    if (puVar1 == (undefined4 *)0x0) {
LAB_0009b054:
      __set_errno(5,unaff_EDX,unaff_EBX,__s);
      __s = (undefined4 *)0x0;
      goto LAB_0009b060;
    }
    __s = puVar1 + 2;
  }
  else {
    __s = (undefined4 *)dword_edf00[1];
    uVar2 = (uint)((ushort)__s[3] & 0x4003 | 3);
    puVar1 = dword_edf00;
    dword_edf00 = (undefined4 *)*dword_edf00;
  }
LAB_0009b02f:
  memset(__s,0,0x1a);
  __s[3] = uVar2;
  puVar1[1] = __s;
  *puVar1 = dword_f24c8;
  dword_f24c8 = puVar1;
LAB_0009b060:
  return CONCAT44(unaff_EDX,__s);
}


// ================================================================================================
// __freefp @ 0x9b066 [__watcall]
// ================================================================================================

void __watcall __freefp(int param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  puVar1 = &dword_f24c8;
  do {
    puVar2 = puVar1;
    puVar1 = (undefined4 *)*puVar2;
    if (puVar1 == (undefined4 *)0x0) {
      return;
    }
  } while (param_1 != puVar1[1]);
  *(byte *)(param_1 + 0xc) = *(byte *)(puVar1[1] + 0xc) | 3;
  *puVar2 = *puVar1;
  *puVar1 = dword_edf00;
  dword_edf00 = puVar1;
  return;
}


// ================================================================================================
// __purgefp @ 0x9b09f [__watcall]
// ================================================================================================

void __watcall __purgefp(void)

{
  undefined4 *puVar1;
  
  while (dword_edf00 != (undefined4 *)0x0) {
    puVar1 = (undefined4 *)*dword_edf00;
    free(dword_edf00);
    dword_edf00 = puVar1;
  }
  return;
}


// ================================================================================================
// __fseek_in_buffer @ 0x9b0bd [__watcall]
// ================================================================================================

undefined4 __watcall __fseek_in_buffer(int param_1,int *unaff_EDX)

{
  *(byte *)(unaff_EDX + 3) = *(byte *)(unaff_EDX + 3) & 0xef;
  if ((param_1 <= unaff_EDX[1]) && (unaff_EDX[2] - *unaff_EDX <= param_1)) {
    *unaff_EDX = *unaff_EDX + param_1;
    unaff_EDX[1] = unaff_EDX[1] - param_1;
    return 0;
  }
  unaff_EDX[1] = 0;
  *unaff_EDX = unaff_EDX[2];
  return 1;
}


// ================================================================================================
// fseek @ 0x9b0ff [__watcall]
// ================================================================================================

/* WARNING: Removing unreachable block (ram,0x0009b179) */

int __watcall fseek(FILE *__stream,long __off,int __whence)

{
  char *pcVar1;
  int iVar2;
  __off_t _Var3;
  
  if ((*(byte *)&__stream->_IO_read_base & 6) == 0) {
    if (__whence == 0) {
      iVar2 = tell(__stream->_IO_write_base);
      iVar2 = __fseek_in_buffer(__off - (iVar2 - (int)__stream->_IO_read_ptr),__stream);
      if ((iVar2 != 0) && (_Var3 = lseek((int)__stream->_IO_write_base,__off,0), _Var3 == -1)) {
        return -1;
      }
    }
    else if ((uint)__whence < 2) {
      pcVar1 = __stream->_IO_read_ptr;
      iVar2 = __fseek_in_buffer(__off,__stream);
      if ((iVar2 != 0) &&
         (_Var3 = lseek((int)__stream->_IO_write_base,__off - (int)pcVar1,__whence), _Var3 == -1)) {
        return -1;
      }
    }
    else {
      if (__whence != 2) goto LAB_0009b125;
      __stream->_flags = (int)__stream->_IO_read_end;
      *(byte *)&__stream->_IO_read_base = *(byte *)&__stream->_IO_read_base & 0xef;
      __stream->_IO_read_ptr = (char *)0x0;
      _Var3 = lseek((int)__stream->_IO_write_base,__off,2);
      if (_Var3 == -1) {
        return -1;
      }
    }
  }
  else {
    if ((*(byte *)((int)&__stream->_IO_read_base + 1) & 0x10) == 0) {
      if (__whence == 1) {
        __off = __off - (int)__stream->_IO_read_ptr;
      }
      __stream->_IO_read_ptr = (char *)0x0;
      __stream->_flags = (int)__stream->_IO_read_end;
    }
    else {
      iVar2 = __flush(__stream);
      if (iVar2 != 0) {
        if (__whence != 0) {
          return -1;
        }
        if (-1 < __off) {
          return -1;
        }
LAB_0009b125:
        __set_errno(9);
        return -1;
      }
    }
    *(byte *)&__stream->_IO_read_base = *(byte *)&__stream->_IO_read_base & 0xeb;
    _Var3 = lseek((int)__stream->_IO_write_base,__off,__whence);
    if (_Var3 == -1) {
      return -1;
    }
  }
  return 0;
}


// ================================================================================================
// __chktty @ 0x9b1fb [__watcall]
// ================================================================================================

void __watcall __chktty(int param_1)

{
  byte bVar1;
  int iVar2;
  
  if ((*(byte *)(param_1 + 0xd) & 0x20) == 0) {
    iVar2 = isatty(*(int *)(param_1 + 0x10));
    if (iVar2 != 0) {
      bVar1 = *(byte *)(param_1 + 0xd);
      *(byte *)(param_1 + 0xd) = bVar1 | 0x20;
      if ((bVar1 & 7) == 0) {
        *(byte *)(param_1 + 0xd) = bVar1 | 0x22;
      }
    }
  }
  return;
}


// ================================================================================================
// __get_tmpfile_seed @ 0x9b22c [__watcall]
// ================================================================================================

undefined4 __watcall __get_tmpfile_seed(void)

{
  return dword_d4ce4;
}


// ================================================================================================
// __flush @ 0x9b232 [__watcall]
// ================================================================================================

undefined8 __watcall __flush(undefined4 *param_1,undefined4 unaff_EDX)

{
  ushort uVar1;
  int iVar2;
  undefined4 uVar3;
  
  uVar3 = 0;
  if ((*(byte *)((int)param_1 + 0xd) & 0x10) == 0) {
    if ((param_1[2] != 0) &&
       (uVar1 = *(ushort *)(param_1 + 3), *(byte *)(param_1 + 3) = *(byte *)(param_1 + 3) & 0xef,
       (uVar1 & 0x2000) == 0)) {
      iVar2 = param_1[1];
      if (iVar2 != 0) {
        iVar2 = lseek(param_1[4],-iVar2,1);
      }
      if (iVar2 == -1) {
        *(byte *)(param_1 + 3) = *(byte *)(param_1 + 3) | 0x20;
        uVar3 = 0xffffffff;
      }
    }
  }
  else {
    *(byte *)((int)param_1 + 0xd) = *(byte *)((int)param_1 + 0xd) & 0xef;
    if (((*(byte *)(param_1 + 3) & 2) != 0) && (param_1[2] != 0)) {
      iVar2 = __qwrite(param_1[4],param_1[2],param_1[1]);
      if (iVar2 == -1) {
        *(byte *)(param_1 + 3) = *(byte *)(param_1 + 3) | 0x20;
        uVar3 = 0xffffffff;
      }
      else if (iVar2 != param_1[1]) {
        __set_errno(0xc);
        uVar3 = 0xffffffff;
        *(byte *)(param_1 + 3) = *(byte *)(param_1 + 3) | 0x20;
      }
    }
  }
  param_1[1] = 0;
  *param_1 = param_1[2];
  return CONCAT44(unaff_EDX,uVar3);
}


// ================================================================================================
// ftell @ 0x9b2f1 [__watcall]
// ================================================================================================

long __watcall ftell(FILE *__stream)

{
  int iVar1;
  long lVar2;
  int iVar3;
  undefined8 uVar4;
  
  uVar4 = tell(__stream->_IO_write_base,__stream);
  iVar3 = (int)((ulonglong)uVar4 >> 0x20);
  lVar2 = (long)uVar4;
  if ((lVar2 != -1) && (iVar1 = *(int *)(iVar3 + 4), iVar1 != 0)) {
    if ((*(byte *)(iVar3 + 0xd) & 0x10) != 0) {
      return iVar1 + lVar2;
    }
    lVar2 = lVar2 - iVar1;
  }
  return lVar2;
}


// ================================================================================================
// __close_stream_handle @ 0x9b321 [__watcall]
// ================================================================================================

longlong __watcall __close_stream_handle(undefined4 param_1,undefined4 param_2,uint unaff_EBX)

{
  code *pcVar1;
  undefined4 extraout_EDX;
  byte in_CF;
  
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  if ((in_CF & 1) == 0) {
    __SetIOMode(extraout_EDX,0);
    return (ulonglong)unaff_EBX << 0x20;
  }
  __set_errno(4,extraout_EDX,param_1);
  return CONCAT44(unaff_EBX,0xffffffff);
}


// ================================================================================================
// __ioalloc @ 0x9b353 [__watcall]
// ================================================================================================

void __watcall
__ioalloc(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  void *pvVar1;
  byte bVar2;
  undefined4 *extraout_EDX;
  
  __chktty(param_1,param_1,unaff_EBX,unaff_ECX,unaff_EDX,unaff_ECX);
  if (extraout_EDX[5] == 0) {
    if ((*(byte *)((int)extraout_EDX + 0xd) & 2) == 0) {
      if ((*(byte *)((int)extraout_EDX + 0xd) & 4) == 0) {
        extraout_EDX[5] = 0x1000;
      }
      else {
        extraout_EDX[5] = 1;
      }
    }
    else {
      extraout_EDX[5] = 0x86;
    }
  }
  pvVar1 = malloc(extraout_EDX[5]);
  extraout_EDX[2] = pvVar1;
  if (pvVar1 == (void *)0x0) {
    extraout_EDX[5] = 1;
    bVar2 = *(byte *)((int)extraout_EDX + 0xd) & 0xf8;
    extraout_EDX[2] = extraout_EDX + 6;
    *(byte *)((int)extraout_EDX + 0xd) = bVar2;
    *(byte *)((int)extraout_EDX + 0xd) = bVar2 | 4;
  }
  else {
    *(byte *)(extraout_EDX + 3) = *(byte *)(extraout_EDX + 3) | 8;
  }
  extraout_EDX[1] = 0;
  *extraout_EDX = extraout_EDX[2];
  return;
}


// ================================================================================================
// fputc @ 0x9b3ca [__watcall]
// ================================================================================================

int __watcall fputc(int __c,FILE *__stream)

{
  byte *pbVar1;
  char *pcVar2;
  uint uVar3;
  int iVar4;
  int extraout_EDX;
  FILE *extraout_EDX_00;
  undefined8 uVar5;
  
  if ((*(byte *)&__stream->_IO_read_base & 2) == 0) {
    __set_errno(4);
    *(byte *)(extraout_EDX + 0xc) = *(byte *)(extraout_EDX + 0xc) | 0x20;
LAB_0009b3e5:
    uVar3 = 0xffffffff;
  }
  else {
    if (__stream->_IO_read_end == (char *)0x0) {
      __ioalloc(__stream);
      __stream = extraout_EDX_00;
    }
    uVar3 = 0x400;
    if ((__c == 10) && (uVar3 = 0x600, (*(byte *)&__stream->_IO_read_base & 0x40) == 0)) {
      pbVar1 = (byte *)((int)&__stream->_IO_read_base + 1);
      *pbVar1 = *pbVar1 | 0x10;
      *(undefined *)__stream->_flags = 0xd;
      pcVar2 = __stream->_IO_read_ptr;
      __stream->_flags = __stream->_flags + 1;
      __stream->_IO_read_ptr = pcVar2 + 1;
      if (pcVar2 + 1 == __stream->_IO_write_ptr) {
        uVar5 = __flush(__stream);
        __stream = (FILE *)((ulonglong)uVar5 >> 0x20);
        if ((int)uVar5 != 0) goto LAB_0009b3e5;
      }
    }
    pbVar1 = (byte *)((int)&__stream->_IO_read_base + 1);
    *pbVar1 = *pbVar1 | 0x10;
    *(char *)__stream->_flags = (char)__c;
    pcVar2 = __stream->_IO_read_ptr;
    __stream->_flags = __stream->_flags + 1;
    __stream->_IO_read_ptr = pcVar2 + 1;
    if (((uVar3 & (uint)__stream->_IO_read_base) != 0) || (pcVar2 + 1 == __stream->_IO_write_ptr)) {
      iVar4 = __flush(__stream);
      if (iVar4 != 0) goto LAB_0009b3e5;
    }
    uVar3 = __c & 0xff;
  }
  return uVar3;
}


// ================================================================================================
// draw_line_aa @ 0x9b498 [__cdecl]
// ================================================================================================

void draw_line_aa(int *param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  bool bVar8;
  int local_20;
  int local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  if (dword_d30c8 == 0) {
    draw_line_octant(param_1);
  }
  else {
    uVar3 = param_1[1] * 0x10000 + (*param_1 >> 0x10 & 0xffffU) + 0x8000;
    local_14 = param_1[3] * 0x10000 + (param_1[2] >> 0x10 & 0xffffU) + 0x8000;
    uVar7 = (int)uVar3 >> 0x10 & 0xffff;
    uVar4 = (int)local_14 >> 0x10 & 0xffff;
    iVar2 = param_1[7];
    iVar6 = param_1[6];
    if (*(byte *)(param_1 + 0xd) < 10) {
      uVar3 = uVar3 & 0xffff;
      local_14 = local_14 & 0xffff;
      switch(*(byte *)(param_1 + 0xd)) {
      default:
        if (iVar6 != 0) {
          fillrect(uVar7,uVar4,iVar6,1,iVar2);
          return;
        }
        break;
      case 2:
        if (iVar6 != 0) {
          fillrect(uVar7,param_1[3],1,iVar6,iVar2);
          return;
        }
        break;
      case 3:
        iVar5 = param_1[3];
        while (iVar6 = iVar6 + -1, iVar6 != -1) {
          putpixel(uVar7,iVar5,iVar2);
          iVar5 = iVar5 + 1;
          uVar7 = uVar7 - 1;
        }
        break;
      case 4:
        iVar5 = param_1[3];
        while (iVar6 = iVar6 + -1, iVar6 != -1) {
          putpixel(uVar7,iVar5,iVar2);
          iVar5 = iVar5 + 1;
          uVar7 = uVar7 + 1;
        }
        break;
      case 5:
        uVar4 = param_1[0xc];
        local_20 = param_1[3];
        while (iVar6 = iVar6 + -1, iVar6 != -1) {
          iVar5 = local_20 + 1;
          putpixel(uVar7,local_20,iVar2);
          uVar3 = uVar3 + (uVar4 >> 0x10);
          local_20 = iVar5;
          if ((uVar3 & 0xffff0000) != 0) {
            uVar3 = uVar3 & 0xffff;
            uVar7 = uVar7 - 1;
          }
        }
        break;
      case 6:
        uVar4 = param_1[0xc];
        local_1c = param_1[3];
        while (iVar6 = iVar6 + -1, iVar6 != -1) {
          iVar5 = local_1c + 1;
          putpixel(uVar7,local_1c,iVar2);
          uVar3 = uVar3 + (uVar4 >> 0x10);
          local_1c = iVar5;
          if ((uVar3 & 0xffff0000) != 0) {
            uVar3 = uVar3 & 0xffff;
            uVar7 = uVar7 + 1;
          }
        }
        break;
      case 7:
        uVar3 = param_1[0xc];
        local_18 = local_14;
        while (iVar6 = iVar6 + -1, iVar6 != -1) {
          putpixel(uVar7,uVar4,iVar2);
          uVar7 = uVar7 - 1;
          uVar1 = local_18 + (uVar3 >> 0x10);
          local_18._2_2_ = (short)(uVar1 >> 0x10);
          bVar8 = local_18._2_2_ != 0;
          local_18 = uVar1;
          if (bVar8) {
            local_18 = uVar1 & 0xffff;
            uVar4 = uVar4 + 1;
          }
        }
        break;
      case 8:
        uVar3 = param_1[0xc];
        while (iVar6 = iVar6 + -1, iVar6 != -1) {
          putpixel(uVar7,uVar4,iVar2);
          uVar7 = uVar7 + 1;
          uVar1 = local_14 + (uVar3 >> 0x10);
          local_14._2_2_ = (short)(uVar1 >> 0x10);
          bVar8 = local_14._2_2_ != 0;
          local_14 = uVar1;
          if (bVar8) {
            local_14 = uVar1 & 0xffff;
            uVar4 = uVar4 + 1;
          }
        }
        break;
      case 9:
        putpixel(uVar7,uVar4,iVar2);
      }
    }
  }
  return;
}


// ================================================================================================
// isatty @ 0x9b710 [__watcall]
// ================================================================================================

int __watcall isatty(int __fd)

{
  code *pcVar1;
  uint extraout_EDX;
  
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  return (uint)((extraout_EDX & 0x80) != 0);
}


// ================================================================================================
// __GetIOMode @ 0x9b72e [__watcall]
// ================================================================================================

longlong __watcall __GetIOMode(uint param_1,uint unaff_EDX)

{
  int iVar1;
  int iVar2;
  
  if (dword_d500c <= param_1) {
    return (ulonglong)unaff_EDX << 0x20;
  }
  if ((int)param_1 < 6) {
    iVar2 = param_1 * 4;
    if ((off_d5060[iVar2 + 1] & 0x40) == 0) {
      off_d5060[iVar2 + 1] = off_d5060[iVar2 + 1] | 0x40;
      iVar1 = isatty(param_1);
      if (iVar1 != 0) {
        off_d5060[iVar2 + 1] = off_d5060[iVar2 + 1] | 0x20;
      }
    }
  }
  return CONCAT44(unaff_EDX,*(undefined4 *)(off_d5060 + param_1 * 4));
}


// ================================================================================================
// __SetIOMode @ 0x9b783 [__watcall]
// ================================================================================================

void __watcall __SetIOMode(int param_1,uint unaff_EDX)

{
  *(uint *)(off_d5060 + param_1 * 4) = unaff_EDX | 0x4000;
  return;
}


// ================================================================================================
// __fsetbits @ 0x9b798 [__watcall]
// ================================================================================================

void __watcall __fsetbits(undefined2 *param_1,undefined4 param_2,byte *unaff_EBX)

{
  byte bVar1;
  int iVar2;
  undefined2 *puVar3;
  int in_FS_OFFSET;
  
  puVar3 = param_1;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + 1;
  }
  for (iVar2 = 0; iVar2 != 0; iVar2 = iVar2 + -1) {
    *(undefined *)puVar3 = 0;
    puVar3 = (undefined2 *)((int)puVar3 + 1);
  }
  for (; bVar1 = *unaff_EBX, bVar1 != 0; unaff_EBX = unaff_EBX + 1) {
    *(byte *)((int)param_1 + in_FS_OFFSET + ((int)(uint)bVar1 >> 3)) =
         *(byte *)((int)param_1 + in_FS_OFFSET + ((int)(uint)bVar1 >> 3)) | (&unk_c4c70)[bVar1 & 7];
  }
  return;
}


// ================================================================================================
// __setbits @ 0x9b7f5 [__watcall]
// ================================================================================================

void __watcall __setbits(void *param_1,byte *unaff_EDX)

{
  byte bVar1;
  
  memset(param_1,0,0x20);
  for (; bVar1 = *unaff_EDX, bVar1 != 0; unaff_EDX = unaff_EDX + 1) {
    *(byte *)((int)param_1 + ((int)(uint)bVar1 >> 3)) =
         *(byte *)((int)param_1 + ((int)(uint)bVar1 >> 3)) | (&unk_c4c70)[bVar1 & 7];
  }
  return;
}


// ================================================================================================
// fgetc @ 0x9b833 [__watcall]
// ================================================================================================

int __watcall fgetc(FILE *__stream)

{
  char *pcVar1;
  uint uVar2;
  FILE *extraout_EDX;
  int iVar3;
  undefined8 uVar4;
  
  if ((*(byte *)&__stream->_IO_read_base & 1) == 0) {
    __set_errno(4);
    uVar2 = 0xffffffff;
    *(byte *)&extraout_EDX->_IO_read_base = *(byte *)&extraout_EDX->_IO_read_base | 0x20;
    __stream = extraout_EDX;
  }
  else {
    pcVar1 = __stream->_IO_read_ptr;
    __stream->_IO_read_ptr = pcVar1 + -1;
    if ((int)(pcVar1 + -1) < 0) {
      uVar4 = __filbuf(__stream);
      __stream = (FILE *)((ulonglong)uVar4 >> 0x20);
      uVar2 = (uint)uVar4;
    }
    else {
      uVar2 = (uint)*(byte *)__stream->_flags;
      __stream->_flags = (int)((byte *)__stream->_flags + 1);
    }
  }
  uVar4 = CONCAT44(__stream,uVar2);
  if ((*(byte *)&__stream->_IO_read_base & 0x40) == 0) {
    if (uVar2 == 0xd) {
      pcVar1 = __stream->_IO_read_ptr;
      __stream->_IO_read_ptr = pcVar1 + -1;
      if ((int)(pcVar1 + -1) < 0) {
        uVar4 = __filbuf(__stream);
      }
      else {
        uVar4 = CONCAT44(__stream,(uint)*(byte *)__stream->_flags);
        __stream->_flags = (int)((byte *)__stream->_flags + 1);
      }
    }
    iVar3 = (int)((ulonglong)uVar4 >> 0x20);
    uVar2 = (uint)uVar4;
    if (uVar2 == 0x1a) {
      uVar2 = 0xffffffff;
      *(byte *)(iVar3 + 0xc) = *(byte *)(iVar3 + 0xc) | 0x10;
    }
  }
  return uVar2;
}


// ================================================================================================
// __filbuf @ 0x9b8bc [__watcall]
// ================================================================================================

undefined8 __watcall __filbuf(undefined4 param_1,undefined4 unaff_EDX)

{
  byte *pbVar1;
  undefined4 *puVar2;
  undefined8 uVar3;
  
  uVar3 = __fill_buffer(param_1,param_1);
  puVar2 = (undefined4 *)((ulonglong)uVar3 >> 0x20);
  if ((int)uVar3 == 0) {
    return CONCAT44(unaff_EDX,0xffffffff);
  }
  pbVar1 = (byte *)*puVar2;
  puVar2[1] = puVar2[1] + -1;
  *puVar2 = pbVar1 + 1;
  return CONCAT44(unaff_EDX,(uint)*pbVar1);
}


