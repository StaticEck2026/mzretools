// Decompiled by Ghidra from hockey.elf (via ledisasm ELF export)
// This is machine generated pseudo-C meant as a reference for porting, it does not compile as is.
#include "prototypes.h"

// ================================================================================================
// exh_hub_playoff_tree @ 0x20171 [__watcall]
// ================================================================================================

undefined8 __watcall exh_hub_playoff_tree(undefined4 param_1,undefined4 unaff_EDX)

{
  undefined *puVar1;
  undefined auStack_324 [768];
  undefined auStack_24 [16];
  
  __CHK(0x334);
  dword_dd120 = auStack_324;
  dword_dc738 = 1;
  dword_c65b8 = stats_table;
  dword_c6a60 = 1;
  dword_c65b0 = param_1;
  getpalette(0,0x100,auStack_324);
  fade_palette(1,auStack_324,0x10);
  setdefaultscreen();
  hub_build_remap(1);
  stats_table(param_1);
  draw_menu_items(&unk_cf80f,4,0x40,0x41,0x42);
  puVar1 = install_path;
  if (byte_ed85a != '\x01') {
    puVar1 = (undefined *)0x0;
  }
  make_path(auStack_24,puVar1,aEmbpal,0);
  dword_dd104 = loadshapes(auStack_24,0);
  dword_dd100 = locateshape(dword_dd104,&aPal_c0c3b);
  memcpy(auStack_324,(void *)(dword_dd100 + 0x10),0x300);
  freemem(dword_dd104);
  fade_palette(0,auStack_324,0x10);
  dword_c6a60 = 0;
  dword_dd120 = (undefined *)0x0;
  run_menu(&unk_cf80f,4,0x40,0x41,0x42);
  getpalette(0,0x100,auStack_324);
  fade_palette(1,auStack_324,0x10);
  dword_dc738 = 0;
  dword_c65b8 = (code *)0x0;
  return CONCAT44(unaff_EDX,2);
}


// ================================================================================================
// exh_hub_league_calendar @ 0x202e5 [__watcall]
// ================================================================================================

undefined8 __watcall exh_hub_league_calendar(undefined4 param_1,undefined4 unaff_EDX)

{
  undefined *puVar1;
  undefined auStack_320 [768];
  undefined auStack_20 [16];
  
  __CHK(0x330);
  dword_dc738 = 1;
  dword_c65b8 = stats_table;
  dword_c65b0 = param_1;
  getpalette(0,0x100,auStack_320);
  fade_palette(1,auStack_320,0x10);
  hub_build_remap(1);
  stats_table(param_1);
  draw_menu_items(&unk_cf88f,4,0x40,0x41,0x42);
  puVar1 = install_path;
  if (byte_ed85a != '\x01') {
    puVar1 = (undefined *)0x0;
  }
  make_path(auStack_20,puVar1,aEmbpal,0);
  dword_dd104 = loadshapes(auStack_20,0);
  dword_dd100 = locateshape(dword_dd104,&aPal_c0c3b);
  memcpy(auStack_320,(void *)(dword_dd100 + 0x10),0x300);
  freemem(dword_dd104);
  fade_palette(0,auStack_320,0x10);
  run_menu(&unk_cf88f,4,0x40,0x41,0x42);
  getpalette(0,0x100,auStack_320);
  fade_palette(1,auStack_320,0x10);
  dword_dc738 = 0;
  dword_c65b8 = (code *)0x0;
  return CONCAT44(unaff_EDX,2);
}


// ================================================================================================
// exh_hub_standings @ 0x203fa [__watcall]
// ================================================================================================

longlong __watcall exh_hub_standings(undefined4 param_1,uint unaff_EDX)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined auStack_1c [16];
  
  __CHK(0x28);
  if (dword_c6956 == 0) {
    stats_free_buffers();
    setdefaultscreen();
    draw_menu_items(&unk_cf54f,4,0x40,0x41,0x42);
    standings_table(dword_dd10c,&unk_dc640);
  }
  else {
    if (dword_c65a8 == 0) {
      dword_c65a8 = loadfile(aEASNVfn,0);
    }
    if (dword_c65ac == 0) {
      puVar1 = install_path;
      if (dword_c6956 == 0) {
        puVar2 = off_c68e4;
        if (byte_ed858 != '\x01') {
          puVar1 = (undefined *)0x0;
        }
      }
      else {
        puVar2 = (&off_c68e4)[dword_c6956];
        if (byte_ed859 != '\x01') {
          puVar1 = (undefined *)0x0;
        }
      }
      make_path(auStack_1c,puVar1,puVar2);
      dword_c65ac = loadshapes(auStack_1c,0);
    }
    standings_playoffs_view(dword_dd10c,&unk_dc640);
    draw_menu_items(&unk_cf54f,4,0x40,0x41,0x42);
  }
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// exh_hub_stats @ 0x2051a [__watcall]
// ================================================================================================

undefined8 __watcall exh_hub_stats(undefined4 param_1,undefined4 unaff_EDX)

{
  undefined *puVar1;
  undefined auStack_328 [768];
  undefined auStack_28 [16];
  
  __CHK(0x338);
  dword_dc738 = 1;
  dword_c65b8 = dword_c65cc;
  dword_c65b4 = 0;
  dword_c65b0 = 0;
  byte_dc836 = 0;
  getpalette(0,0x100,auStack_328);
  fade_palette(1,auStack_328,0x10);
  setdefaultscreen();
  clearclip(0);
  dword_c6d26 = 0;
  hub_build_remap(1);
  dword_dd10c = allocmem(aTstat,0x2a4,0x20);
  dword_dd11c = allocmem(&aKeys,0x5b0,0x20);
  dword_dd110 = allocmem(aPstat,0x497,0x20);
  dword_dd114 = allocmem(aGstat,0x10e,0x20);
  (*dword_c65cc)();
  draw_menu_items(&unk_cf54f,4,0x40,0x41,0x42);
  dword_c65b0 = 0;
  dword_c65b4 = 0;
  puVar1 = install_path;
  if (byte_ed85a != '\x01') {
    puVar1 = (undefined *)0x0;
  }
  make_path(auStack_28,puVar1,aEmbpal,0);
  dword_dd104 = loadshapes(auStack_28,0);
  dword_dd100 = locateshape(dword_dd104,&aPal_c0c3b);
  setpalette(0,0x100,dword_dd100 + 0x10);
  freemem(dword_dd104);
  menu_page_a(&unk_cf54f,4,0x40,0x41,0x42);
  stats_free_buffers();
  while (dword_c65bc != 1) {
    switch(dword_c65bc) {
    case 2:
      dword_c65b8 = dword_c65cc;
      (*dword_c65cc)();
      draw_menu_items(&unk_cf54f,4,0x40,0x41,0x42);
      menu_page_a(&unk_cf54f,4,0x40,0x41,0x42);
      if (dword_c6956 != 0) {
        stats_free_buffers();
      }
      dword_c6d26 = 0;
      break;
    case 3:
      dword_dc734 = 0;
      dword_c65b8 = player_stats_screen;
      player_stats_screen(dword_c65b0);
      draw_menu_items(&unk_cf6af,4,0x40,0x41,0x42);
      menu_page_b(&unk_cf6af,4,0x40,0x41,0x42);
      break;
    case 4:
      dword_c65b8 = goalie_card_screen;
      dword_dc6b4 = 0;
      goalie_card_screen(&unk_dc834);
      draw_menu_items(&unk_cf74f,2,0x40,0x41,0x42);
      run_menu(&unk_cf74f,2,0x40,0x41,0x42);
      break;
    case 5:
      dword_c65b8 = player_card_screen;
      dword_dc6b4 = 0;
      player_card_screen(&unk_dc834,dword_c65bc,0x40);
      draw_menu_items(&unk_cf74f,2,0x40,0x41,0x42);
      run_menu(&unk_cf74f,2,0x40,0x41,0x42);
      dword_c6d26 = 1;
    }
  }
  dword_c6d26 = 0;
  getpalette(0,0x100,auStack_328);
  fade_palette(1,auStack_328,0x10);
  stats_free_buffers();
  freemem(dword_dd10c);
  freemem(dword_dd114);
  freemem(dword_dd110);
  freemem(dword_dd11c);
  dword_dd11c = 0;
  dword_dd10c = 0;
  dword_dd114 = 0;
  dword_dd110 = 0;
  dword_dc738 = 0;
  dword_c65b8 = (code *)0x0;
  return CONCAT44(unaff_EDX,2);
}


// ================================================================================================
// hub_sports_central @ 0x208ef [__watcall]
// ================================================================================================

undefined8 __watcall hub_sports_central(undefined4 param_1,undefined4 unaff_EDX)

{
  undefined *puVar1;
  undefined auStack_324 [768];
  undefined auStack_24 [16];
  
  __CHK(0x334);
  getpalette(0,0x100,auStack_324);
  dword_c7219 = 1;
  dword_dc738 = 1;
  dword_c65b8 = team_stats_screen;
  dword_c65b0 = param_1;
  setdefaultscreen();
  hub_build_remap(1);
  fade_palette(1,auStack_324,0x10);
  team_stats_screen(param_1);
  draw_menu_items(&unk_cf78f,4,0x40,0x41,0x42);
  puVar1 = install_path;
  if (byte_ed85a != '\x01') {
    puVar1 = (undefined *)0x0;
  }
  make_path(auStack_24,puVar1,aEmbpal_c0c58,0);
  dword_dd104 = loadshapes(auStack_24,0);
  dword_dd100 = locateshape(dword_dd104,&aPal_c0c5f);
  fade_palette(0,dword_dd100 + 0x10,0x10);
  freemem(dword_dd104);
  run_menu(&unk_cf78f,4,0x40,0x41,0x42);
  getpalette(0,0x100,auStack_324);
  fade_palette(1,auStack_324,0x10);
  dword_dc738 = 0;
  dword_c65b8 = (code *)0x0;
  return CONCAT44(unaff_EDX,2);
}


// ================================================================================================
// hub_playoff_tree @ 0x20a46 [__watcall]
// ================================================================================================

undefined8 __watcall hub_playoff_tree(undefined4 param_1,undefined4 unaff_EDX)

{
  int iVar1;
  undefined *puVar2;
  char *pcVar3;
  undefined auStack_324 [768];
  undefined auStack_24 [16];
  
  __CHK(0x334);
  dword_c7219 = 1;
  getpalette(0,0x100,auStack_324);
  dword_dc738 = 1;
  dword_c65b8 = stats_table;
  dword_c65b0 = param_1;
  setdefaultscreen();
  hub_build_remap(1);
  fade_palette(1,auStack_324,0x10);
  stats_table(param_1);
  draw_menu_items(&unk_cf80f,4,0x40,0x41,0x42);
  puVar2 = install_path;
  if (byte_ed85a != '\x01') {
    puVar2 = (undefined *)0x0;
  }
  make_path(auStack_24,puVar2,aEmbpal_c0c58,0);
  dword_dd104 = loadshapes(auStack_24,0);
  dword_dd100 = locateshape(dword_dd104,&aPal_c0c5f);
  fade_palette(0,dword_dd100 + 0x10,0x10);
  freemem(dword_dd104);
  run_menu(&unk_cf80f,4,0x40,0x41,0x42);
  getpalette(0,0x100,auStack_324);
  puVar2 = install_path;
  if (dword_c53fb == 1) {
    pcVar3 = aEmbpal_c0c58;
    if (byte_ed85a != '\x01') {
      puVar2 = (undefined *)0x0;
    }
  }
  else {
    pcVar3 = aEasndesk;
    if (byte_ed836 != '\x01') {
      puVar2 = (undefined *)0x0;
    }
  }
  make_path(auStack_24,puVar2,pcVar3,0);
  dword_dd104 = loadshapes(auStack_24,0);
  iVar1 = locateshape(dword_dd104,&aPal_c0c5f);
  dword_dd100 = iVar1 + 0x10;
  fade_palette(1,auStack_324,0x10);
  freemem(dword_dd104);
  dword_dc738 = 0;
  dword_c65b8 = (code *)0x0;
  return CONCAT44(unaff_EDX,2);
}


// ================================================================================================
// hub_league_calendar @ 0x20bbd [__watcall]
// ================================================================================================

undefined8 __watcall hub_league_calendar(undefined4 param_1,undefined4 unaff_EDX)

{
  char cVar1;
  int iVar2;
  undefined *puVar3;
  char *pcVar4;
  undefined auStack_324 [768];
  undefined auStack_24 [16];
  
  __CHK(0x334);
  dword_c7219 = 1;
  getpalette(0,0x100,auStack_324);
  dword_dc738 = 1;
  dword_c65b8 = stats_table;
  dword_c65b0 = param_1;
  setdefaultscreen();
  hub_build_remap(1);
  fade_palette(1,auStack_324,0x10);
  stats_table(param_1);
  draw_menu_items(&unk_cf88f,4,0x40,0x41,0x42);
  puVar3 = install_path;
  if (byte_ed85a != '\x01') {
    puVar3 = (undefined *)0x0;
  }
  make_path(auStack_24,puVar3,aEmbpal_c0c58,0);
  dword_dd104 = loadshapes(auStack_24,0);
  dword_dd100 = locateshape(dword_dd104,&aPal_c0c5f);
  fade_palette(0,dword_dd100 + 0x10,0x10);
  freemem(dword_dd104);
  run_menu(&unk_cf88f,4,0x40,0x41,0x42);
  getpalette(0,0x100,auStack_324);
  if (dword_c53fb == 1) {
    pcVar4 = aEmbpal_c0c58;
    cVar1 = byte_ed85a;
  }
  else {
    pcVar4 = aEasndesk;
    cVar1 = byte_ed836;
  }
  puVar3 = install_path;
  if (cVar1 != '\x01') {
    puVar3 = (undefined *)0x0;
  }
  make_path(auStack_24,puVar3,pcVar4,0);
  dword_dd104 = loadshapes(auStack_24,0);
  iVar2 = locateshape(dword_dd104,&aPal_c0c5f);
  dword_dd100 = iVar2 + 0x10;
  fade_palette(1,auStack_324,0x10);
  freemem(dword_dd104);
  dword_dc738 = 0;
  dword_c65b8 = (code *)0x0;
  return CONCAT44(unaff_EDX,2);
}


// ================================================================================================
// hub_standings @ 0x20d97 [__watcall]
// ================================================================================================

longlong __watcall hub_standings(undefined4 param_1,uint unaff_EDX)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined auStack_1c [16];
  
  __CHK(0x28);
  if (dword_c6956 == 0) {
    stats_free_buffers();
    setdefaultscreen();
    draw_menu_items(&unk_cf54f,4,0x40,0x41,0x42);
    standings_table(dword_dd10c,&unk_dc640);
  }
  else {
    if (dword_c65a8 == 0) {
      dword_c65a8 = loadfile(aEASNVfn,0);
    }
    if (dword_c65ac == 0) {
      puVar1 = install_path;
      if (dword_c6956 == 0) {
        puVar2 = off_c68e4;
        if (byte_ed858 != '\x01') {
          puVar1 = (undefined *)0x0;
        }
      }
      else {
        puVar2 = (&off_c68e4)[dword_c6956];
        if (byte_ed859 != '\x01') {
          puVar1 = (undefined *)0x0;
        }
      }
      make_path(auStack_1c,puVar1,puVar2);
      dword_c65ac = loadshapes(auStack_1c,0);
    }
    standings_playoffs_view(dword_dd10c,&unk_dc640);
    draw_menu_items(&unk_cf54f,4,0x40,0x41,0x42);
  }
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// hub_stats @ 0x20eb7 [__watcall]
// ================================================================================================

undefined8 __watcall hub_stats(undefined4 param_1,undefined4 unaff_EDX)

{
  int iVar1;
  undefined *puVar2;
  undefined auStack_3a4 [768];
  undefined4 local_a4 [31];
  undefined auStack_28 [16];
  
  __CHK(0x3b4);
  iVar1 = 0;
  do {
    local_a4[iVar1] = (&dword_dc7b8)[iVar1];
    iVar1 = iVar1 + 1;
  } while (iVar1 < 0x1f);
  dword_dc738 = 1;
  dword_c65b8 = dword_c65cc;
  dword_c65b4 = 0;
  dword_c65b0 = 0;
  dword_c6d26 = 0;
  dword_c7219 = 1;
  byte_dc836 = 0;
  getpalette(0,0x100,auStack_3a4);
  fade_palette(1,auStack_3a4,0x10);
  hub_build_remap(1);
  dword_dd10c = allocmem(aTstat_c0c6d,0x2a4,0x20);
  dword_dd11c = allocmem(&aKeys_c0c73,0x5b0,0x20);
  dword_dd110 = allocmem(aPstat_c0c78,0x497,0x20);
  dword_dd114 = allocmem(aGstat_c0c7e,0x10e,0x20);
  (*dword_c65cc)();
  draw_menu_items(&unk_cf54f,4,0x40,0x41,0x42);
  dword_c65b0 = 0;
  dword_c65b4 = 0;
  puVar2 = install_path;
  if (byte_ed85a != '\x01') {
    puVar2 = (undefined *)0x0;
  }
  make_path(auStack_28,puVar2,aEmbpal_c0c58,0);
  dword_dd104 = loadshapes(auStack_28,0);
  dword_dd100 = locateshape(dword_dd104,&aPal_c0c5f);
  fade_palette(0,dword_dd100 + 0x10,0x10);
  freemem(dword_dd104);
  menu_page_a(&unk_cf54f,4,0x40,0x41,0x42);
  stats_free_buffers();
  setdefaultscreen();
  while (dword_c65bc != 1) {
    switch(dword_c65bc) {
    case 2:
      dword_c65b8 = dword_c65cc;
      (*dword_c65cc)();
      draw_menu_items(&unk_cf54f,4,0x40,0x41,0x42);
      menu_page_a(&unk_cf54f,4,0x40,0x41,0x42);
      if (dword_c6956 != 0) {
        stats_free_buffers();
        setdefaultscreen();
      }
      dword_c6d26 = 0;
      break;
    case 3:
      dword_dc734 = 0;
      dword_c65b8 = player_stats_screen;
      player_stats_screen(dword_c65b0);
      draw_menu_items(&unk_cf6af,4,0x40,0x41,0x42);
      menu_page_b(&unk_cf6af,4,0x40,0x41,0x42);
      break;
    case 4:
      dword_c65b8 = goalie_card_screen;
      dword_dc6b4 = 0;
      goalie_card_screen(&unk_dc834);
      draw_menu_items(&unk_cf74f,2,0x40,0x41,0x42);
      run_menu(&unk_cf74f,2,0x40,0x41,0x42);
      break;
    case 5:
      dword_c65b8 = player_card_screen;
      dword_dc6b4 = 0;
      dword_c6a60 = 0;
      dword_dd120 = 0;
      player_card_screen(&unk_dc834);
      draw_menu_items(&unk_cf74f,2,0x40,0x41,0x42);
      run_menu(&unk_cf74f,2,0x40,0x41,0x42);
      dword_c6d26 = 1;
    }
  }
  dword_c6d26 = 0;
  stats_free_buffers();
  freemem(dword_dd10c);
  freemem(dword_dd114);
  freemem(dword_dd110);
  freemem(dword_dd11c);
  dword_dd11c = 0;
  dword_dd10c = 0;
  dword_dd114 = 0;
  dword_dd110 = 0;
  getpalette(0,0x100,auStack_3a4);
  fade_palette(1,auStack_3a4,0x10);
  dword_dc738 = 0;
  dword_c65b8 = (code *)0x0;
  iVar1 = 0;
  do {
    (&dword_dc7b8)[iVar1] = local_a4[iVar1];
    iVar1 = iVar1 + 1;
  } while (iVar1 < 0x1f);
  return CONCAT44(unaff_EDX,2);
}


// ================================================================================================
// calendar_free_if_low_mem @ 0x212c6 [__watcall]
// ================================================================================================

void __watcall
calendar_free_if_low_mem(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  int iVar1;
  
  __CHK(0x14);
  iVar1 = largest_free_locked();
  if (iVar1 < 0x4b709) {
    if (dword_c8992 != 0) {
      freemem(dword_c8992,unaff_EDX,unaff_ECX,unaff_EBX);
    }
    dword_c8992 = 0;
  }
  return;
}


// ================================================================================================
// calendar_load_shapes @ 0x212fe [__watcall]
// ================================================================================================

void __watcall calendar_load_shapes(void)

{
  undefined *puVar1;
  undefined auStack_2c [32];
  
  __CHK(0x38);
  if (dword_c8992 == 0) {
    puVar1 = (undefined *)0x0;
    if (byte_ed98d == '\x01') {
      puVar1 = install_path;
    }
    make_path(auStack_2c,puVar1,aCalendar,0);
    dword_c8992 = loadshapes(auStack_2c,0x20);
  }
  return;
}


// ================================================================================================
// cal_hub_a @ 0x21350 [__watcall]
// ================================================================================================

longlong __watcall cal_hub_a(undefined4 param_1,uint unaff_EDX)

{
  undefined *puVar1;
  undefined auStack_324 [768];
  undefined auStack_24 [16];
  
  __CHK(0x334);
  getpalette(0,0x100,auStack_324);
  dword_dc738 = 1;
  dword_c65b8 = team_stats_screen;
  dword_c65b0 = param_1;
  setdefaultscreen();
  hub_build_remap(1);
  fade_palette(1,auStack_324,0x10);
  calendar_free_if_low_mem();
  team_stats_screen(param_1);
  draw_menu_items(&unk_cf78f,4,0x40,0x41,0x42);
  puVar1 = install_path;
  if (byte_ed85a != '\x01') {
    puVar1 = (undefined *)0x0;
  }
  make_path(auStack_24,puVar1,aEmbpal_c0c8d,0);
  dword_dd104 = loadshapes(auStack_24,0);
  dword_dd100 = locateshape(dword_dd104,&aPal_c0c94);
  fade_palette(0,dword_dd100 + 0x10,0x10);
  freemem(dword_dd104);
  run_menu(&unk_cf78f,4,0x40,0x41,0x42);
  getpalette(0,0x100,auStack_324);
  fade_palette(1,auStack_324,0x10);
  dword_ddd2c = 0xffffffff;
  calendar_load_shapes();
  dword_dc738 = 0;
  dword_c65b8 = (code *)0x0;
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// cal_hub_b @ 0x214b1 [__watcall]
// ================================================================================================

longlong __watcall cal_hub_b(undefined4 param_1,uint unaff_EDX)

{
  undefined *puVar1;
  undefined auStack_324 [768];
  undefined auStack_24 [16];
  
  __CHK(0x334);
  getpalette(0,0x100,auStack_324);
  dword_dc738 = 1;
  dword_c65b8 = stats_table;
  dword_c65b0 = param_1;
  setdefaultscreen();
  hub_build_remap(1);
  fade_palette(1,auStack_324,0x10);
  calendar_free_if_low_mem();
  stats_table(param_1);
  draw_menu_items(&unk_cf80f,4,0x40,0x41,0x42);
  puVar1 = install_path;
  if (byte_ed85a != '\x01') {
    puVar1 = (undefined *)0x0;
  }
  make_path(auStack_24,puVar1,aEmbpal_c0c8d,0);
  dword_dd104 = loadshapes(auStack_24,0);
  dword_dd100 = locateshape(dword_dd104,&aPal_c0c94);
  fade_palette(0,dword_dd100 + 0x10,0x10);
  freemem(dword_dd104);
  run_menu(&unk_cf80f,4,0x40,0x41,0x42);
  getpalette(0,0x100,auStack_324);
  fade_palette(1,auStack_324,0x10);
  dword_ddd2c = 0xffffffff;
  calendar_load_shapes();
  dword_dc738 = 0;
  dword_c65b8 = (code *)0x0;
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// cal_hub_c @ 0x215c4 [__watcall]
// ================================================================================================

longlong __watcall cal_hub_c(undefined4 param_1,uint unaff_EDX)

{
  undefined *puVar1;
  undefined auStack_324 [768];
  undefined auStack_24 [16];
  
  __CHK(0x334);
  getpalette(0,0x100,auStack_324);
  dword_dc738 = 1;
  dword_c65b8 = stats_table;
  dword_c65b0 = param_1;
  setdefaultscreen();
  hub_build_remap(1);
  fade_palette(1,auStack_324,0x10);
  calendar_free_if_low_mem();
  stats_table(param_1);
  draw_menu_items(&unk_cf88f,4,0x40,0x41,0x42);
  puVar1 = install_path;
  if (byte_ed85a != '\x01') {
    puVar1 = (undefined *)0x0;
  }
  make_path(auStack_24,puVar1,aEmbpal_c0c8d,0);
  dword_dd104 = loadshapes(auStack_24,0);
  dword_dd100 = locateshape(dword_dd104,&aPal_c0c94);
  fade_palette(0,dword_dd100 + 0x10,0x10);
  freemem(dword_dd104);
  run_menu(&unk_cf88f,4,0x40,0x41,0x42);
  getpalette(0,0x100,auStack_324);
  fade_palette(1,auStack_324,0x10);
  dword_ddd2c = 0xffffffff;
  calendar_load_shapes();
  dword_dc738 = 0;
  dword_c65b8 = (code *)0x0;
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// cal_hub_standings @ 0x216d7 [__watcall]
// ================================================================================================

longlong __watcall cal_hub_standings(undefined4 param_1,uint unaff_EDX)

{
  undefined *puVar1;
  undefined *puVar2;
  undefined auStack_1c [16];
  
  __CHK(0x28);
  calendar_free_if_low_mem();
  if (dword_c6956 == 0) {
    stats_free_buffers();
    setdefaultscreen();
    draw_menu_items(&unk_cf54f,4,0x40,0x41,0x42);
    standings_table(dword_dd10c,&unk_dc640);
  }
  else {
    if (dword_c65a8 == 0) {
      dword_c65a8 = loadfile(aEASNVfn,0);
    }
    if (dword_c65ac == 0) {
      puVar1 = install_path;
      if (dword_c6956 == 0) {
        puVar2 = off_c68e4;
        if (byte_ed858 != '\x01') {
          puVar1 = (undefined *)0x0;
        }
      }
      else {
        puVar2 = (&off_c68e4)[dword_c6956];
        if (byte_ed859 != '\x01') {
          puVar1 = (undefined *)0x0;
        }
      }
      make_path(auStack_1c,puVar1,puVar2);
      dword_c65ac = loadshapes(auStack_1c,0);
    }
    standings_playoffs_view(dword_dd10c,&unk_dc640);
    draw_menu_items(&unk_cf54f,4,0x40,0x41,0x42);
  }
  calendar_load_shapes();
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// cal_hub_stats @ 0x217fe [__watcall]
// ================================================================================================

longlong __watcall cal_hub_stats(undefined4 param_1,uint unaff_EDX)

{
  int iVar1;
  undefined *puVar2;
  undefined auStack_3a4 [768];
  undefined4 local_a4 [31];
  undefined auStack_28 [16];
  
  __CHK(0x3b4);
  iVar1 = 0;
  do {
    local_a4[iVar1] = (&dword_dc7b8)[iVar1];
    iVar1 = iVar1 + 1;
  } while (iVar1 < 0x1f);
  dword_dc738 = 1;
  dword_c65b8 = dword_c65cc;
  dword_c65b4 = 0;
  dword_c65b0 = 0;
  byte_dc836 = 0;
  getpalette(0,0x100,auStack_3a4);
  fade_palette(1,auStack_3a4,0x10);
  calendar_free_if_low_mem();
  dword_c6d26 = 0;
  hub_build_remap(1);
  dword_dd10c = allocmem(aTstat_c0c99,0x2a4,0x20);
  dword_dd11c = allocmem(&aKeys_c0c9f,0x5b0,0x20);
  dword_dd110 = allocmem(aPstat_c0ca4,0x497,0x20);
  dword_dd114 = allocmem(aGstat_c0caa,0x10e,0x20);
  (*dword_c65cc)();
  draw_menu_items(&unk_cf54f,4,0x40,0x41,0x42);
  dword_c65b0 = 0;
  dword_c65b4 = 0;
  puVar2 = install_path;
  if (byte_ed85a != '\x01') {
    puVar2 = (undefined *)0x0;
  }
  make_path(auStack_28,puVar2,aEmbpal_c0c8d,0);
  dword_dd104 = loadshapes(auStack_28,0);
  dword_dd100 = locateshape(dword_dd104,&aPal_c0c94);
  fade_palette(0,dword_dd100 + 0x10,0x10);
  freemem(dword_dd104);
  menu_page_a(&unk_cf54f,4,0x40,0x41,0x42);
  stats_free_buffers();
  setdefaultscreen();
  while (dword_c65bc != 1) {
    switch(dword_c65bc) {
    case 2:
      dword_c65b8 = dword_c65cc;
      (*dword_c65cc)();
      draw_menu_items(&unk_cf54f,4,0x40,0x41,0x42);
      menu_page_a(&unk_cf54f,4,0x40,0x41,0x42);
      if (dword_c6956 != 0) {
        stats_free_buffers();
        setdefaultscreen();
      }
      dword_c6d26 = 0;
      break;
    case 3:
      dword_dc734 = 0;
      dword_c65b8 = player_stats_screen;
      player_stats_screen(dword_c65b0);
      draw_menu_items(&unk_cf6af,4,0x40,0x41,0x42);
      menu_page_b(&unk_cf6af,4,0x40,0x41,0x42);
      break;
    case 4:
      dword_c65b8 = goalie_card_screen;
      dword_dc6b4 = 0;
      goalie_card_screen(&unk_dc834);
      draw_menu_items(&unk_cf74f,2,0x40,0x41,0x42);
      run_menu(&unk_cf74f,2,0x40,0x41,0x42);
      break;
    case 5:
      dword_c65b8 = player_card_screen;
      dword_dc6b4 = 0;
      player_card_screen(&unk_dc834);
      draw_menu_items(&unk_cf74f,2,0x40,0x41,0x42);
      run_menu(&unk_cf74f,2,0x40,0x41,0x42);
      dword_c6d26 = 1;
    }
  }
  dword_c6d26 = 0;
  stats_free_buffers();
  freemem(dword_dd10c);
  freemem(dword_dd114);
  freemem(dword_dd110);
  freemem(dword_dd11c);
  iVar1 = 0;
  dword_dd11c = 0;
  dword_dd10c = 0;
  dword_dd114 = 0;
  dword_dd110 = 0;
  dword_dc738 = 0;
  dword_c65b8 = (code *)0x0;
  do {
    (&dword_dc7b8)[iVar1] = local_a4[iVar1];
    iVar1 = iVar1 + 1;
  } while (iVar1 < 0x1f);
  getpalette(0,0x100,auStack_3a4);
  fade_palette(1,auStack_3a4,0x10);
  dword_ddd2c = 0xffffffff;
  calendar_load_shapes();
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// player_card_draw_photo @ 0x21c04 [__watcall]
// ================================================================================================

void __watcall
player_card_draw_photo(undefined *param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  undefined *puVar1;
  int iVar2;
  undefined auStack_310 [204];
  undefined auStack_244 [384];
  undefined auStack_c4 [180];
  
  __CHK(800);
  if (dword_c6a60 == 0) {
    getpalette(0,0x100,auStack_310);
  }
  else {
    memcpy(auStack_310,dword_dd120,0x300);
  }
  puVar1 = auStack_244;
  for (iVar2 = 0; iVar2 < 0xb4; iVar2 = iVar2 + 1) {
    *puVar1 = *param_1;
    param_1 = param_1 + 1;
    puVar1 = puVar1 + 1;
  }
  puVar1 = auStack_c4;
  for (iVar2 = 0; iVar2 < 0xa5; iVar2 = iVar2 + 1) {
    *puVar1 = *param_1;
    param_1 = param_1 + 1;
    puVar1 = puVar1 + 1;
  }
  setremaptable(&unk_c6960);
  if (dword_c6a60 == 0) {
    setpalette(0,0x100,auStack_310);
  }
  else {
    memcpy(dword_dd120,auStack_310,0x300);
  }
  drawshape_trans(unaff_EDX,unaff_EBX,unaff_ECX);
  return;
}


// ================================================================================================
// player_card_screen @ 0x21cde [__watcall]
// ================================================================================================

undefined8 __watcall player_card_screen(undefined4 param_1,undefined4 unaff_EDX)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  __off_t __offset;
  undefined *puVar5;
  char *__src;
  undefined4 *puVar6;
  int *piVar7;
  int iVar8;
  byte bVar9;
  undefined5 *puVar10;
  char local_124 [4];
  undefined local_120;
  undefined auStack_11f [3];
  undefined uStack_11c;
  undefined auStack_d4 [64];
  int local_94 [4];
  int aiStack_82 [5];
  undefined auStack_6c [32];
  char acStack_4c [20];
  undefined local_38 [6];
  undefined2 uStack_32;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  char *pcStack_20;
  undefined4 uStack_1c;
  
  bVar9 = 0;
  __CHK(0x138);
  local_28 = 0;
  local_2c = font_main;
  local_24 = font_kaufm;
  make_path(auStack_6c,&unk_c65d4,(&off_c68ec)[dword_c695a],0);
  iVar1 = c_open(auStack_6c,0x200);
  __offset = dword_dc85c;
  if (dword_c695a != 0) {
    __offset = CONCAT13(dword_dc860._3_1_,CONCAT12(dword_dc860._2_1_,(undefined2)dword_dc860));
  }
  lseek(iVar1,__offset,0);
  read(iVar1,local_94,0x28);
  _close(iVar1);
  make_path(auStack_6c,&unk_c65d4,aAttDb,0);
  iVar1 = c_open(auStack_6c,0x200);
  lseek(iVar1,DAT_000dc858,0);
  read(iVar1,acStack_4c,0x14);
  _close(iVar1);
  make_path(auStack_6c,&unk_c65d4,off_c68f4,0);
  iVar1 = c_open(auStack_6c,0x200);
  lseek(iVar1,(uint)unk_dc834 * 0x4c,0);
  read(iVar1,local_38,5);
  _close(iVar1);
  setdefaultscreen();
  sprintf((char *)&unk_dd0d8,aEmbS_c6935,local_38);
  puVar5 = install_path;
  if ((&byte_ed83c)[unk_dc834] != '\x01') {
    puVar5 = (undefined *)0x0;
  }
  make_path(auStack_6c,puVar5,&unk_dd0d8,0);
  dword_dd104 = loadshapes(auStack_6c,0);
  dword_dd100 = locateshape(dword_dd104,&aBkgd_c693b);
  setclip(0,0x280,0x13,0x1e0);
  drawshape_remap_home(dword_dd100);
  setclip(0,0x280,0,0x1e0);
  freemem(dword_dd104);
  if (DAT_000dc864 == '\0') {
    puVar5 = install_path;
    if (byte_ed908 != '\x01') {
      puVar5 = (undefined *)0x0;
    }
    make_path(auStack_6c,puVar5,aPstatbar,0);
    dword_dd104 = loadshapes(auStack_6c,0);
    dword_dd100 = locateshape(dword_dd104,&aPst2);
    drawshape_remap_home(dword_dd100);
  }
  else {
    local_124[0] = aPORTR[0];
    local_124[1] = aPORTR[1];
    local_124[2] = aPORTR[2];
    local_124[3] = aPORTR[3];
    *(undefined2 *)(&local_120 + (uint)bVar9 * -8) = *(undefined2 *)(aPORTR + (uint)bVar9 * -8 + 4);
    memcpy(auStack_11f,&DAT_000dc864,4);
    uStack_11c = 0;
    puVar5 = install_path;
    if (*(char *)((cRam000dc865 + -0x30) * 10 + cRam000dc866 + 0xed8d9) != '\x01') {
      puVar5 = (undefined *)0x0;
    }
    make_path(auStack_6c,puVar5,local_124,0);
    uVar2 = loadshapes(auStack_6c,0);
    memcpy(local_124,&DAT_000dc864,4);
    local_120 = 0;
    iVar1 = locateshape_fast(uVar2,local_124);
    if (iVar1 == 0) {
      freemem(uVar2);
      puVar5 = install_path;
      if (byte_ed908 != '\x01') {
        puVar5 = (undefined *)0x0;
      }
      make_path(auStack_6c,puVar5,aPstatbar,0);
      dword_dd104 = loadshapes(auStack_6c,0);
      puVar10 = &aPst2;
    }
    else {
      local_124[0] = '!';
      iVar3 = locateshape_fast(uVar2,local_124);
      player_card_draw_photo(iVar3 + 0x10,iVar1,0x21,0x26);
      freemem(uVar2);
      puVar5 = install_path;
      if (byte_ed908 != '\x01') {
        puVar5 = (undefined *)0x0;
      }
      make_path(auStack_6c,puVar5,aPstatbar,0);
      dword_dd104 = loadshapes(auStack_6c,0);
      puVar10 = &aPst1;
    }
    dword_dd100 = locateshape(dword_dd104,puVar10);
    drawshape_remap_home(dword_dd100);
  }
  freemem(dword_dd104);
  getfontstate(auStack_d4);
  setfont(local_24);
  set_text_colors(0x40,0x43);
  unk_dd0d8._0_1_ = aPlayerStats[0];
  unk_dd0d8._1_1_ = aPlayerStats[1];
  unk_dd0d8._2_1_ = aPlayerStats[2];
  unk_dd0d8._3_1_ = aPlayerStats[3];
  (&DAT_000dd0dc)[(uint)bVar9 * -2] = *(undefined4 *)(aPlayerStats + (uint)bVar9 * -8 + 4);
  (&DAT_000dd0e0)[(uint)bVar9 * -2 + (uint)bVar9 * -2] =
       *(undefined4 *)(aPlayerStats + (uint)bVar9 * -8 + (uint)bVar9 * -8 + 8);
  *(char *)(&DAT_000dd0e0 + (uint)bVar9 * -2 + (uint)bVar9 * -2 + (uint)bVar9 * -2 + 1) =
       (aPlayerStats + (uint)bVar9 * -8 + (uint)bVar9 * -8 + 8)[((uint)bVar9 * -2 + 1) * 4];
  iVar1 = textwidth(&unk_dd0d8);
  print_outlined(0x140 - (iVar1 >> 1),0x52,&unk_dd0d8);
  text_capture_begin();
  set_text_colors(0x40,0x43);
  sprintf((char *)&unk_dd0d8,aSS_c0d78,&unk_dc837,&unk_dc847);
  print_centered_shadow(0x98,&unk_dd0d8);
  sprintf((char *)&unk_dd0d8,(char *)&aD_c0d7e,(uint)DAT_000dc835);
  if (byte_dc836 < 0x44) {
    if (byte_dc836 != 0x43) goto LAB_000221df;
    __src = aCenter;
  }
  else if (byte_dc836 < 0x45) {
    __src = aDefense;
  }
  else {
    if (byte_dc836 < 0x4c) goto LAB_000221df;
    if (byte_dc836 < 0x4d) {
      __src = aLeftWing;
    }
    else {
      if (byte_dc836 != 0x52) goto LAB_000221df;
      __src = aRightWing;
    }
  }
  strcat((char *)&unk_dd0d8,__src);
LAB_000221df:
  print_centered_shadow(0xb2,&unk_dd0d8);
  setfont(local_2c);
  local_30._0_2_ = 0xf3;
  local_30._2_2_ = 0;
  iVar1 = CONCAT22(0xf3,uStack_32) >> 0x10;
  print_text_at(0x82,iVar1,&aGP_c0da6);
  print_text_at(0xaa,iVar1,&aG_c0da9);
  print_text_at(0xd2,iVar1,&aA_c0dad);
  print_text_at(0xfa,iVar1,&aPt_c0db1);
  print_text_at(0x122,iVar1,&aPIM_c0db5);
  print_text_at(0x14a,iVar1,&unk_c0db9);
  print_text_at(0x186,iVar1,&aPPG_c0dbe);
  print_text_at(0x1ae,iVar1,&aSHG_c0dc2);
  print_text_at(0x1d6,iVar1,aShots_c0dc6);
  print_text_at(0x212,iVar1,aPct_c0dcc);
  piVar7 = local_94;
  iVar3 = 0;
  local_30 = 0x103;
  do {
    iVar8 = (int)(short)local_30;
    print_text_at(0x32,iVar8,(&off_c68cc)[iVar3],iVar1);
    print_textf(0x82,iVar8,&a2d,(int)*(short *)piVar7);
    print_textf(0xaa,iVar8,&a3d,*piVar7 >> 0x10);
    print_textf(0xd2,iVar8,&a3d,*(int *)((int)piVar7 + 2) >> 0x10);
    print_textf(0xfa,iVar8,&a3d,piVar7[1] >> 0x10);
    print_textf(0x122,iVar8,&a3d,*(int *)((int)piVar7 + 10) >> 0x10);
    print_textf(0x14a,iVar8,&a4d,*(int *)((int)piVar7 + 0xe) >> 0x10);
    print_textf(0x186,iVar8,&a3d,*(int *)((int)piVar7 + 6) >> 0x10);
    print_textf(0x1ae,iVar8,&a3d,piVar7[2] >> 0x10);
    print_textf(0x1d6,iVar8,&a5d,piVar7[3] >> 0x10);
    if (*(short *)((int)piVar7 + 0xe) == 0) {
      uVar4 = 0;
    }
    else {
      uVar4 = ((uint)*(ushort *)((int)piVar7 + 2) * 1000 + *(ushort *)((int)piVar7 + 0xe) / 2) /
              (uint)*(ushort *)((int)piVar7 + 0xe);
    }
    iVar1 = (int)(short)((ulonglong)(longlong)(int)uVar4 / 10);
    print_textf2(0x212,(int)(short)local_30,a3d1d,iVar1,(short)((ulonglong)(longlong)(int)uVar4 % 10));
    piVar7 = aiStack_82;
    local_30 = local_30 + 0xd;
    iVar3 = iVar3 + 1;
  } while (iVar3 < 2);
  local_30._0_2_ = 0x131;
  local_30._2_2_ = 0;
  print_centered_shadow(CONCAT22(0x131,uStack_32) >> 0x10,aRatings);
  pcStack_20 = acStack_4c;
  local_30._0_2_ = 0x143;
  local_30._2_2_ = 0;
  iVar1 = CONCAT22(0x143,uStack_32) >> 0x10;
  print_text_at(0x1e,iVar1,aShoots);
  if (acStack_4c[0] == '\0') {
    puVar6 = &aR;
  }
  else {
    puVar6 = &aL_c0de2;
  }
  print_text_at(0x10e,iVar1,puVar6);
  uStack_1c = 0;
  iVar3 = 0;
  local_30 = CONCAT22(local_30._2_2_,(short)local_30) + 0xd;
  do {
    if (iVar3 == 7) {
      uStack_1c = 0x136;
      local_30 = local_30 + -0x68;
    }
    iVar8 = (int)(short)local_30;
    print_text_at((int)(short)((short)uStack_1c + 0x1e),iVar8,(&off_c6a64)[iVar3],iVar1);
    iVar1 = (int)(short)(((byte)pcStack_20[*(int *)((int)&unk_c6a99 + iVar3) >> 0x18] + 5) * 5);
    print_textf((int)(short)((short)uStack_1c + 0x10e),iVar8,&a3d);
    local_30 = local_30 + 0xd;
    iVar3 = iVar3 + 1;
  } while (iVar3 < 0xe);
  setfontstate(auStack_d4);
  text_capture_stop();
  return CONCAT44(unaff_EDX,local_28);
}


// ================================================================================================
// goalie_card_screen @ 0x22581 [__watcall]
// ================================================================================================

void __watcall goalie_card_screen(void)

{
  ushort uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  __off_t __offset;
  undefined *puVar5;
  undefined4 *puVar6;
  int *piVar7;
  short sVar8;
  int iVar9;
  byte bVar10;
  undefined5 *puVar11;
  char local_128 [4];
  undefined local_124;
  undefined auStack_123 [3];
  undefined uStack_120;
  undefined auStack_d8 [64];
  int local_98 [5];
  int aiStack_82 [8];
  undefined auStack_60 [32];
  char acStack_40 [16];
  undefined local_30 [6];
  undefined2 uStack_2a;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 uStack_20;
  char *pcStack_1c;
  
  bVar10 = 0;
  __CHK(0x13c);
  local_24 = font_main;
  uStack_20 = font_kaufm;
  make_path(auStack_60,&unk_c65d4,(&off_c68ec)[dword_c695a],0);
  iVar2 = c_open(auStack_60,0x200);
  __offset = dword_dc85c;
  if (dword_c695a != 0) {
    __offset = CONCAT13(dword_dc860._3_1_,CONCAT12(dword_dc860._2_1_,(undefined2)dword_dc860));
  }
  lseek(iVar2,__offset,0);
  read(iVar2,local_98,0x36);
  _close(iVar2);
  make_path(auStack_60,&unk_c65d4,aAttDb,0);
  iVar2 = c_open(auStack_60,0x200);
  lseek(iVar2,DAT_000dc858,0);
  read(iVar2,acStack_40,0x10);
  _close(iVar2);
  make_path(auStack_60,&unk_c65d4,off_c68f4,0);
  iVar2 = c_open(auStack_60,0x200);
  lseek(iVar2,(uint)unk_dc834 * 0x4c,0);
  read(iVar2,local_30,5);
  _close(iVar2);
  setdefaultscreen();
  sprintf((char *)&unk_dd0d8,aEmbS_c6935,local_30);
  puVar5 = install_path;
  if ((&byte_ed83c)[unk_dc834] != '\x01') {
    puVar5 = (undefined *)0x0;
  }
  make_path(auStack_60,puVar5,&unk_dd0d8,0);
  dword_dd104 = loadshapes(auStack_60,0);
  dword_dd100 = locateshape(dword_dd104,&aBkgd_c693b);
  setclip(0,0x280,0x13,0x1e0);
  drawshape_remap_home(dword_dd100);
  setclip(0,0x280,0,0x1e0);
  freemem(dword_dd104);
  if (DAT_000dc864 == '\0') {
    puVar5 = install_path;
    if (byte_ed908 != '\x01') {
      puVar5 = (undefined *)0x0;
    }
    make_path(auStack_60,puVar5,aPstatbar_c0e6a,0);
    dword_dd104 = loadshapes(auStack_60,0);
    dword_dd100 = locateshape(dword_dd104,&aPst2_c0e78);
    drawshape_remap_home(dword_dd100);
  }
  else {
    local_128[0] = aPORTR_c0e64[0];
    local_128[1] = aPORTR_c0e64[1];
    local_128[2] = aPORTR_c0e64[2];
    local_128[3] = aPORTR_c0e64[3];
    *(undefined2 *)(&local_124 + (uint)bVar10 * -8) =
         *(undefined2 *)(aPORTR_c0e64 + (uint)bVar10 * -8 + 4);
    memcpy(auStack_123,&DAT_000dc864,4);
    uStack_120 = 0;
    puVar5 = install_path;
    if (*(char *)(cRam000dc866 + 0xed8d9 + (cRam000dc865 + -0x30) * 10) != '\x01') {
      puVar5 = (undefined *)0x0;
    }
    make_path(auStack_60,puVar5,local_128,0);
    uVar3 = loadshapes(auStack_60,0);
    memcpy(local_128,&DAT_000dc864,4);
    local_124 = 0;
    iVar2 = locateshape_fast(uVar3,local_128);
    if (iVar2 == 0) {
      freemem(uVar3);
      puVar5 = install_path;
      if (byte_ed908 != '\x01') {
        puVar5 = (undefined *)0x0;
      }
      make_path(auStack_60,puVar5,aPstatbar_c0e6a,0);
      dword_dd104 = loadshapes(auStack_60,0);
      puVar11 = &aPst2_c0e78;
    }
    else {
      local_128[0] = '!';
      iVar4 = locateshape_fast(uVar3,local_128);
      player_card_draw_photo(iVar4 + 0x10,iVar2,0x21,0x26);
      freemem(uVar3);
      puVar5 = install_path;
      if (byte_ed908 != '\x01') {
        puVar5 = (undefined *)0x0;
      }
      make_path(auStack_60,puVar5,aPstatbar_c0e6a,0);
      dword_dd104 = loadshapes(auStack_60,0);
      puVar11 = &aPst1_c0e73;
    }
    dword_dd100 = locateshape(dword_dd104,puVar11);
    drawshape_remap_home(dword_dd100);
  }
  freemem(dword_dd104);
  text_capture_begin();
  getfontstate(auStack_d8);
  setfont(uStack_20);
  set_text_colors(0x40,0x43);
  unk_dd0d8._0_1_ = aPlayerStats_c0e7d[0];
  unk_dd0d8._1_1_ = aPlayerStats_c0e7d[1];
  unk_dd0d8._2_1_ = aPlayerStats_c0e7d[2];
  unk_dd0d8._3_1_ = aPlayerStats_c0e7d[3];
  (&DAT_000dd0dc)[(uint)bVar10 * -2] = *(undefined4 *)(aPlayerStats_c0e7d + (uint)bVar10 * -8 + 4);
  (&DAT_000dd0e0)[(uint)bVar10 * -2 + (uint)bVar10 * -2] =
       *(undefined4 *)(aPlayerStats_c0e7d + (uint)bVar10 * -8 + (uint)bVar10 * -8 + 8);
  *(char *)(&DAT_000dd0e0 + (uint)bVar10 * -2 + (uint)bVar10 * -2 + (uint)bVar10 * -2 + 1) =
       (aPlayerStats_c0e7d + (uint)bVar10 * -8 + (uint)bVar10 * -8 + 8)[((uint)bVar10 * -2 + 1) * 4]
  ;
  iVar2 = textwidth(&unk_dd0d8);
  print_outlined(0x140 - (iVar2 >> 1),0x52,&unk_dd0d8);
  set_text_colors(0x40,0x43);
  sprintf((char *)&unk_dd0d8,aSS_c0e8a,&unk_dc837,&unk_dc847);
  print_centered_shadow(0x98,&unk_dd0d8);
  sprintf((char *)&unk_dd0d8,aDGoalie,(uint)DAT_000dc835);
  print_centered_shadow(0xb2,&unk_dd0d8);
  setfont(local_24);
  local_28._0_2_ = 0xf3;
  local_28._2_2_ = 0;
  iVar2 = CONCAT22(0xf3,uStack_2a) >> 0x10;
  print_text_at(0x82,iVar2,&aGP_c0e9a);
  print_text_at(0xaa,iVar2,&aMin_c0e9d);
  print_text_at(0xd2,iVar2,aGAA_c0ea2);
  print_text_at(0x10e,iVar2,&aW_c0ea8);
  print_text_at(0x136,iVar2,&aL_c0eab);
  print_text_at(0x15e,iVar2,&aT_c0eae);
  print_text_at(0x186,iVar2,&aSO_c0eb1);
  print_text_at(0x1ae,iVar2,&aEN_c0eb4);
  print_text_at(0x1d6,iVar2,aSA);
  print_text_at(0x212,iVar2,aPct_c0ebd);
  piVar7 = local_98;
  iVar4 = 0;
  local_28 = 0x103;
  do {
    iVar9 = (int)(short)local_28;
    print_text_at(0x32,iVar9,(&off_c68cc)[iVar4],iVar2);
    print_textf(0x82,iVar9,&a2d,(int)*(short *)piVar7);
    print_textf(0xaa,iVar9,&a4d,*(int *)((int)piVar7 + 10) >> 0x10);
    print_textf2(0xd2,iVar9,a2d22d,
              (short)((ulonglong)(longlong)(int)(uint)*(ushort *)(piVar7 + 4) / 100),
              (short)((ulonglong)(longlong)(int)(uint)*(ushort *)(piVar7 + 4) % 100));
    print_textf(0x10e,iVar9,&a2d,*piVar7 >> 0x10);
    print_textf(0x136,iVar9,&a2d,*(int *)((int)piVar7 + 2) >> 0x10);
    print_textf(0x15e,iVar9,&a2d,piVar7[1] >> 0x10);
    print_textf(0x186,iVar9,&a2d,*(int *)((int)piVar7 + 6) >> 0x10);
    print_textf(0x1ae,iVar9,&a2d,piVar7[2] >> 0x10);
    print_textf(0x1d6,iVar9,&a5d,piVar7[4] >> 0x10);
    uVar1 = *(ushort *)(piVar7 + 5);
    if (uVar1 < 1000) {
      iVar2 = (int)(short)(*(ushort *)(piVar7 + 5) % 1000);
      print_textf(0x212,iVar9,a03d);
    }
    else {
      iVar2 = (int)(short)((ulonglong)(uint)uVar1 / 1000);
      print_textf2(0x212,iVar9,a1d03d,iVar2,(short)((ulonglong)(uint)uVar1 % 1000));
    }
    piVar7 = aiStack_82;
    local_28 = local_28 + 0xd;
    iVar4 = iVar4 + 1;
  } while (iVar4 < 2);
  local_28._0_2_ = 0x131;
  local_28._2_2_ = 0;
  print_centered_shadow(CONCAT22(0x131,uStack_2a) >> 0x10,aRatings_c0ec3);
  pcStack_1c = acStack_40;
  local_28._0_2_ = 0x143;
  local_28._2_2_ = 0;
  iVar2 = CONCAT22(0x143,uStack_2a) >> 0x10;
  print_text_at(0x14,iVar2,aGloveHand);
  if (acStack_40[0] == '\0') {
    puVar6 = &aR_c0edb;
  }
  else {
    puVar6 = &aL_c0ed7;
  }
  print_text_at(0x104,iVar2,puVar6);
  sVar8 = 0;
  iVar4 = 0;
  local_28 = CONCAT22(local_28._2_2_,(short)local_28) + 0xd;
  do {
    if (iVar4 == 5) {
      sVar8 = sVar8 + 0x140;
      local_28 = local_28 + -0x4e;
    }
    iVar9 = (int)(short)local_28;
    print_text_at((int)(short)(sVar8 + 0x14),iVar9,(&off_c6aac)[iVar4],iVar2);
    iVar2 = (int)(short)(((byte)pcStack_1c[*(int *)((int)&unk_c6ad1 + iVar4) >> 0x18] + 5) * 5);
    print_textf((int)(short)(sVar8 + 0x104),iVar9,&a3d);
    local_28 = local_28 + 0xd;
    iVar4 = iVar4 + 1;
  } while (iVar4 < 10);
  setfontstate(auStack_d8);
  text_capture_stop();
  return;
}


// ================================================================================================
// cmp_team_standings @ 0x22dde [__watcall]
// ================================================================================================

int __watcall cmp_team_standings(int *param_1,int *unaff_EDX)

{
  byte *pbVar1;
  byte *pbVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  
  __CHK(0x24);
  if (dword_c6956 == 0) {
    pbVar1 = (byte *)(*param_1 * 0x4c + dword_dd108 + 0x28);
    pbVar2 = (byte *)(*unaff_EDX * 0x4c + dword_dd108 + 0x28);
  }
  else {
    pbVar1 = (byte *)(*param_1 * 0x4c + dword_dd108 + 0x3a);
    pbVar2 = (byte *)(dword_dd108 + *unaff_EDX * 0x4c + 0x3a);
  }
  iVar5 = (uint)pbVar2[1] * 2 + (uint)pbVar2[3];
  iVar6 = (uint)pbVar1[3] + (uint)pbVar1[1] * 2;
  if (iVar6 != iVar5) {
    return iVar5 - iVar6;
  }
  if (*pbVar2 == *pbVar1) {
    if (pbVar2[1] != pbVar1[1]) {
      return (uint)pbVar2[1] - (uint)pbVar1[1];
    }
    if (*(ushort *)(pbVar2 + 4) != *(ushort *)(pbVar1 + 4)) {
      return (uint)*(ushort *)(pbVar2 + 4) - (uint)*(ushort *)(pbVar1 + 4);
    }
    if (*(ushort *)(pbVar2 + 6) == *(ushort *)(pbVar1 + 6)) {
      return *param_1 - *unaff_EDX;
    }
    uVar4 = (uint)*(ushort *)(pbVar1 + 6);
    uVar3 = (uint)*(ushort *)(pbVar2 + 6);
  }
  else {
    uVar4 = (uint)*pbVar1;
    uVar3 = (uint)*pbVar2;
  }
  return uVar4 - uVar3;
}


// ================================================================================================
// cmp_team_scoring @ 0x22f2e [__watcall]
// ================================================================================================

int __watcall cmp_team_scoring(int *param_1,int *unaff_EDX)

{
  byte *pbVar1;
  byte *pbVar2;
  int iVar3;
  int iVar4;
  
  __CHK(0x20);
  if (dword_c6956 == 0) {
    pbVar1 = (byte *)(*param_1 * 0x4c + dword_dd108 + 0x28);
    pbVar2 = (byte *)(*unaff_EDX * 0x4c + dword_dd108 + 0x28);
  }
  else {
    pbVar1 = (byte *)(*param_1 * 0x4c + dword_dd108 + 0x3a);
    pbVar2 = (byte *)(*unaff_EDX * 0x4c + dword_dd108 + 0x3a);
  }
  if (*(ushort *)(pbVar2 + 4) == *(ushort *)(pbVar1 + 4)) {
    if (*pbVar2 == *pbVar1) {
      iVar3 = (uint)pbVar2[1] * 2 + (uint)pbVar2[3];
      iVar4 = (uint)pbVar1[3] + (uint)pbVar1[1] * 2;
      if (iVar4 == iVar3) {
        if (pbVar2[1] == pbVar1[1]) {
          iVar3 = *param_1 - *unaff_EDX;
        }
        else {
          iVar3 = (uint)pbVar2[1] - (uint)pbVar1[1];
        }
      }
      else {
        iVar3 = iVar3 - iVar4;
      }
    }
    else {
      iVar3 = (uint)*pbVar1 - (uint)*pbVar2;
    }
  }
  else {
    iVar3 = (uint)*(ushort *)(pbVar2 + 4) - (uint)*(ushort *)(pbVar1 + 4);
  }
  return iVar3;
}


// ================================================================================================
// cmp_team_defense @ 0x23051 [__watcall]
// ================================================================================================

int __watcall cmp_team_defense(int *param_1,int *unaff_EDX)

{
  byte *pbVar1;
  byte *pbVar2;
  int iVar3;
  int iVar4;
  
  __CHK(0x20);
  if (dword_c6956 == 0) {
    pbVar1 = (byte *)(*param_1 * 0x4c + dword_dd108 + 0x28);
    pbVar2 = (byte *)(*unaff_EDX * 0x4c + dword_dd108 + 0x28);
  }
  else {
    pbVar1 = (byte *)(*param_1 * 0x4c + dword_dd108 + 0x3a);
    pbVar2 = (byte *)(*unaff_EDX * 0x4c + dword_dd108 + 0x3a);
  }
  if (*(ushort *)(pbVar2 + 6) == *(ushort *)(pbVar1 + 6)) {
    if (*pbVar2 == *pbVar1) {
      iVar3 = (uint)pbVar2[1] * 2 + (uint)pbVar2[3];
      iVar4 = (uint)pbVar1[3] + (uint)pbVar1[1] * 2;
      if (iVar4 == iVar3) {
        if (pbVar2[1] == pbVar1[1]) {
          iVar3 = *param_1 - *unaff_EDX;
        }
        else {
          iVar3 = (uint)pbVar2[1] - (uint)pbVar1[1];
        }
      }
      else {
        iVar3 = iVar3 - iVar4;
      }
    }
    else {
      iVar3 = (uint)*pbVar2 - (uint)*pbVar1;
    }
  }
  else {
    iVar3 = (uint)*(ushort *)(pbVar1 + 6) - (uint)*(ushort *)(pbVar2 + 6);
  }
  return iVar3;
}


// ================================================================================================
// cmp_team_power_play @ 0x2312d [__watcall]
// ================================================================================================

uint __watcall cmp_team_power_play(int *param_1,int *unaff_EDX)

{
  ushort uVar1;
  byte *pbVar2;
  byte *pbVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  
  __CHK(0x28);
  uVar6 = *(uint *)(*unaff_EDX * 4 + dword_dd118);
  uVar7 = *(uint *)(dword_dd118 + *param_1 * 4);
  if (uVar6 == uVar7) {
    if (dword_c6956 == 0) {
      pbVar2 = (byte *)(*param_1 * 0x4c + dword_dd108 + 0x28);
      pbVar3 = (byte *)(*unaff_EDX * 0x4c + dword_dd108 + 0x28);
    }
    else {
      pbVar2 = (byte *)(*param_1 * 0x4c + dword_dd108 + 0x3a);
      pbVar3 = (byte *)(dword_dd108 + *unaff_EDX * 0x4c + 0x3a);
    }
    iVar4 = (uint)*(ushort *)(pbVar3 + 8) * (uint)*(ushort *)(pbVar2 + 10);
    uVar1 = *(ushort *)(pbVar3 + 10);
    iVar5 = (uint)*(ushort *)(pbVar2 + 8) * (uint)uVar1;
    if (iVar4 != iVar5) {
      return (uint)(iVar4 != iVar5 && -1 < iVar4 - iVar5);
    }
    if (uVar1 != *(ushort *)(pbVar2 + 10)) {
      return (uint)uVar1 - (uint)*(ushort *)(pbVar2 + 10);
    }
    if (*pbVar3 != *pbVar2) {
      return (uint)*pbVar3 - (uint)*pbVar2;
    }
    uVar6 = (uint)pbVar3[1];
    iVar5 = uVar6 * 2 + (uint)pbVar3[3];
    uVar7 = (uint)pbVar2[1];
    iVar4 = uVar7 * 2 + (uint)pbVar2[3];
    if (iVar5 != iVar4) {
      return iVar5 - iVar4;
    }
    if (pbVar3[1] == pbVar2[1]) {
      return *param_1 - *unaff_EDX;
    }
  }
  return uVar6 - uVar7;
}


// ================================================================================================
// cmp_team_penalty_killing @ 0x232b7 [__watcall]
// ================================================================================================

uint __watcall cmp_team_penalty_killing(int *param_1,int *unaff_EDX)

{
  ushort uVar1;
  byte *pbVar2;
  byte *pbVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  
  __CHK(0x28);
  uVar6 = *(uint *)(*unaff_EDX * 4 + dword_dd118);
  uVar7 = *(uint *)(dword_dd118 + *param_1 * 4);
  if (uVar6 == uVar7) {
    if (dword_c6956 == 0) {
      pbVar2 = (byte *)(*param_1 * 0x4c + dword_dd108 + 0x28);
      pbVar3 = (byte *)(*unaff_EDX * 0x4c + dword_dd108 + 0x28);
    }
    else {
      pbVar2 = (byte *)(*param_1 * 0x4c + dword_dd108 + 0x3a);
      pbVar3 = (byte *)(dword_dd108 + *unaff_EDX * 0x4c + 0x3a);
    }
    iVar4 = (uint)*(ushort *)(pbVar3 + 0xc) * (uint)*(ushort *)(pbVar2 + 0xe);
    uVar1 = *(ushort *)(pbVar3 + 0xe);
    iVar5 = (uint)*(ushort *)(pbVar2 + 0xc) * (uint)uVar1;
    if (iVar4 != iVar5) {
      return (uint)(iVar4 - iVar5 < 0);
    }
    if (uVar1 != *(ushort *)(pbVar2 + 0xe)) {
      return (uint)uVar1 - (uint)*(ushort *)(pbVar2 + 0xe);
    }
    if (*pbVar3 != *pbVar2) {
      return (uint)*pbVar3 - (uint)*pbVar2;
    }
    uVar6 = (uint)pbVar3[1];
    iVar5 = uVar6 * 2 + (uint)pbVar3[3];
    uVar7 = (uint)pbVar2[1];
    iVar4 = uVar7 * 2 + (uint)pbVar2[3];
    if (iVar5 != iVar4) {
      return iVar5 - iVar4;
    }
    if (pbVar3[1] == pbVar2[1]) {
      return *param_1 - *unaff_EDX;
    }
  }
  return uVar6 - uVar7;
}


// ================================================================================================
// cmp_team_penalties @ 0x23437 [__watcall]
// ================================================================================================

int __watcall cmp_team_penalties(int *param_1,int *unaff_EDX)

{
  int iVar1;
  byte *pbVar2;
  byte *pbVar3;
  int iVar4;
  
  __CHK(0x28);
  iVar4 = *(int *)(*unaff_EDX * 4 + dword_dd118);
  iVar1 = *(int *)(dword_dd118 + *param_1 * 4);
  if (iVar4 == iVar1) {
    if (dword_c6956 == 0) {
      pbVar2 = (byte *)(dword_dd108 + *param_1 * 0x4c + 0x28);
      pbVar3 = (byte *)(*unaff_EDX * 0x4c + dword_dd108 + 0x28);
    }
    else {
      pbVar2 = (byte *)(dword_dd108 + *param_1 * 0x4c + 0x3a);
      pbVar3 = (byte *)(*unaff_EDX * 0x4c + dword_dd108 + 0x3a);
    }
    if (*pbVar3 == *pbVar2) {
      if (*(ushort *)(pbVar3 + 0x10) == *(ushort *)(pbVar2 + 0x10)) {
        iVar1 = (uint)pbVar3[1] * 2 + (uint)pbVar3[3];
        iVar4 = (uint)pbVar2[1] * 2 + (uint)pbVar2[3];
        if (iVar1 == iVar4) {
          if (pbVar3[1] == pbVar2[1]) {
            iVar1 = *param_1 - *unaff_EDX;
          }
          else {
            iVar1 = (uint)pbVar3[1] - (uint)pbVar2[1];
          }
        }
        else {
          iVar1 = iVar1 - iVar4;
        }
      }
      else {
        iVar1 = (uint)*(ushort *)(pbVar2 + 0x10) - (uint)*(ushort *)(pbVar3 + 0x10);
      }
    }
    else {
      iVar1 = (uint)*pbVar3 - (uint)*pbVar2;
    }
  }
  else {
    iVar1 = iVar1 - iVar4;
  }
  return iVar1;
}


// ================================================================================================
// team_stats_screen @ 0x235be [__watcall]
// ================================================================================================

longlong __watcall team_stats_screen(uint param_1,uint unaff_EDX)

{
  undefined4 uVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  byte *pbVar6;
  int iVar7;
  ushort uVar8;
  short sVar9;
  undefined *puVar10;
  undefined *puVar11;
  char *pcVar12;
  undefined4 *puVar13;
  uint uVar14;
  int iVar15;
  undefined4 *puVar16;
  byte bVar17;
  uint local_280 [14];
  uint local_248 [15];
  uint local_20c [26];
  uint auStack_1a4 [26];
  undefined auStack_13c [84];
  undefined4 uStack_e8;
  char acStack_e3 [34];
  byte bStack_c1;
  byte abStack_c0 [36];
  undefined auStack_9c [64];
  undefined auStack_5c [32];
  int local_3c [3];
  int local_30;
  int local_2c;
  undefined2 local_28;
  undefined2 uStack_26;
  undefined4 local_24;
  undefined4 local_20;
  uint uStack_1c;
  
  bVar17 = 0;
  __CHK(0x294);
  local_280[0] = param_1;
  dword_dd108 = allocmem(aTeams_c0fa6,0x7b8,0x20);
  if (1 < (int)local_280[0]) {
    dword_dd118 = allocmem(aAddsort,0x68,0x20);
  }
  make_path(auStack_5c,&unk_c65d4,(&off_c68f4)[dword_c695a],0);
  local_2c = c_open(auStack_5c,0x200);
  if (dword_c695a == 0) {
    local_30 = 0x4c;
  }
  else {
    local_30 = 0x2e8;
  }
  if (dword_c6956 == 0) {
    uVar14 = 0;
    do {
      local_20c[uVar14] = uVar14;
      uVar14 = uVar14 + 1;
    } while ((int)uVar14 < 0x1a);
    local_28 = 0x1a;
    uStack_26 = 0;
  }
  else {
    load_lssched_db(local_3c);
    iVar4 = local_3c[0];
    iVar15 = local_3c[0] + 0x199a;
    local_3c[0] = local_3c[0] + 2;
    iVar7 = 0;
    do {
      local_20c[iVar7 * 2] = (uint)*(byte *)(iVar15 + 2);
      local_20c[iVar7 * 2 + 1] = (uint)*(byte *)(iVar15 + 3);
      iVar7 = iVar7 + 1;
      iVar15 = iVar15 + 0x2a;
    } while (iVar7 < 8);
    if (local_20c[0] == 0xff) {
      local_28 = 0;
    }
    else {
      local_28 = 0x10;
    }
    uStack_26 = 0;
    freemem(iVar4);
  }
  if (CONCAT22(uStack_26,local_28) != 0) {
    for (uVar14 = 0; (int)uVar14 < CONCAT22(uStack_26,local_28); uVar14 = uVar14 + 1) {
      auStack_1a4[uVar14] = uVar14;
      lseek(local_2c,local_30 * local_20c[uVar14],0);
      read(local_2c,&uStack_e8,0x4c);
      puVar13 = &uStack_e8;
      puVar16 = (undefined4 *)(dword_dd108 + uVar14 * 0x4c);
      for (iVar4 = 0x13; iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar16 = *puVar13;
        puVar13 = puVar13 + (uint)bVar17 * -2 + 1;
        puVar16 = puVar16 + (uint)bVar17 * -2 + 1;
      }
      if (dword_c6956 == 0) {
        pbVar6 = abStack_c0;
      }
      else {
        pbVar6 = abStack_c0 + 0x12;
      }
      switch(local_280[0]) {
      case 2:
        if (*(ushort *)(pbVar6 + 0xe) < *(ushort *)(pbVar6 + 0xc)) {
          *(ushort *)(pbVar6 + 0xe) = *(ushort *)(pbVar6 + 0xc);
        }
        uVar3 = (uint)*(ushort *)(pbVar6 + 0xe);
        uStack_1c = uVar3;
        if (uVar3 != 0) {
          uVar3 = 1000 - ((uint)*(ushort *)(pbVar6 + 0xc) * 1000 + uVar3 / 2) / uVar3;
        }
        *(uint *)(dword_dd118 + uVar14 * 4) = uVar3;
        break;
      case 3:
        if (*(ushort *)(pbVar6 + 10) < *(ushort *)(pbVar6 + 8)) {
          *(ushort *)(pbVar6 + 10) = *(ushort *)(pbVar6 + 8);
        }
        uVar3 = (uint)*(ushort *)(pbVar6 + 10);
        uStack_1c = uVar3;
        if (uVar3 != 0) {
          iVar4 = (uint)*(ushort *)(pbVar6 + 8) * 1000;
LAB_00023871:
          uVar3 = (iVar4 + uStack_1c / 2) / uStack_1c;
        }
        goto LAB_0002388d;
      case 4:
        uStack_1c = (uint)*pbVar6;
        if (uStack_1c != 0) {
          iVar4 = (uint)*(ushort *)(pbVar6 + 0x10) * 10;
          goto LAB_00023871;
        }
        uVar3 = 0;
LAB_0002388d:
        *(uint *)(dword_dd118 + uVar14 * 4) = uVar3;
        break;
      case 5:
        *(uint *)(dword_dd118 + uVar14 * 4) = (uint)bStack_c1;
      }
    }
    if (local_280[0] == 5) {
      if (dword_c6956 == 0) {
        if (dword_c695a == 0) {
          local_28 = 0xe;
          uStack_26 = 0;
          iVar4 = 0;
          do {
            local_280[iVar4 + 1] = *(uint *)(&unk_c6af8 + iVar4 * 4);
            local_248[iVar4 + 1] = *(uint *)(&unk_c6b30 + iVar4 * 4);
            iVar4 = iVar4 + 1;
          } while (iVar4 < 0xe);
        }
        else {
          qsort(auStack_1a4,CONCAT22(uStack_26,local_28));
          iVar15 = 0;
          iVar4 = 0;
          for (iVar7 = 0; iVar7 < CONCAT22(uStack_26,local_28); iVar7 = iVar7 + 1) {
            if (*(int *)(&unk_c5581 + local_20c[auStack_1a4[iVar7]] * 4) == 3) {
              local_280[iVar4 + 1] = auStack_1a4[iVar7];
              iVar4 = iVar4 + 1;
            }
            else {
              local_248[iVar15 + 1] = auStack_1a4[iVar7];
              iVar15 = iVar15 + 1;
            }
          }
          if ((*(uint *)(&unk_c5519 + local_280[1] * 4) | *(uint *)(&unk_c5519 + local_280[2] * 4))
              != 3) {
            iVar4 = 2;
            do {
              if ((*(uint *)(&unk_c5519 + local_280[1] * 4) |
                  *(uint *)(&unk_c5519 + local_280[iVar4 + 1] * 4)) == 3) break;
              iVar4 = iVar4 + 1;
            } while (iVar4 < 0xc);
            local_280[2] = local_280[iVar4 + 1];
            for (; 1 < iVar4; iVar4 = iVar4 + -1) {
              local_280[iVar4 + 1] = local_280[iVar4];
            }
          }
          if ((*(uint *)(&unk_c5519 + local_248[1] * 4) | *(uint *)(&unk_c5519 + local_248[2] * 4))
              != 0xc) {
            iVar4 = 2;
            do {
              if ((*(uint *)(&unk_c5519 + local_248[1] * 4) |
                  *(uint *)(&unk_c5519 + local_248[iVar4 + 1] * 4)) == 0xc) break;
              iVar4 = iVar4 + 1;
            } while (iVar4 < 0xc);
            local_248[2] = local_248[iVar4 + 1];
            for (; 1 < iVar4; iVar4 = iVar4 + -1) {
              local_248[iVar4 + 1] = local_248[iVar4];
            }
          }
          local_28 = 0xe;
          uStack_26 = 0;
        }
      }
      else {
        qsort(auStack_1a4,CONCAT22(uStack_26,local_28));
        iVar15 = 0;
        iVar4 = 0;
        for (iVar7 = 0; iVar7 < 0x10; iVar7 = iVar7 + 1) {
          if (*(int *)(&unk_c5581 + local_20c[auStack_1a4[iVar7]] * 4) == 3) {
            local_280[iVar4 + 1] = auStack_1a4[iVar7];
            iVar4 = iVar4 + 1;
          }
          else {
            local_248[iVar15 + 1] = auStack_1a4[iVar7];
            iVar15 = iVar15 + 1;
          }
        }
        local_28 = 8;
        uStack_26 = 0;
      }
    }
    else {
      qsort(auStack_1a4,CONCAT22(uStack_26,local_28),4);
    }
  }
  _close(local_2c);
  uVar1 = font_main;
  uVar5 = font_kaufm;
  setdefaultscreen();
  puVar10 = install_path;
  if (dword_c6956 == 0) {
    puVar11 = off_c68e4;
    if (byte_ed858 != '\x01') {
      puVar10 = (undefined *)0x0;
    }
  }
  else {
    puVar11 = (&off_c68e4)[dword_c6956];
    if (byte_ed859 != '\x01') {
      puVar10 = (undefined *)0x0;
    }
  }
  make_path(auStack_5c,puVar10,puVar11,0);
  dword_dd104 = loadshapes(auStack_5c,0);
  dword_dd100 = locateshape(dword_dd104,&aBkgd_c693b);
  setclip(0,0x280,0x13,0x1e0);
  drawshape_remap_home(dword_dd100);
  setclip(0,0x280,0,0x1e0);
  freemem(dword_dd104);
  puVar10 = install_path;
  if (byte_ed908 != '\x01') {
    puVar10 = (undefined *)0x0;
  }
  make_path(auStack_5c,puVar10,aPstatbar_c0fb4,0);
  dword_dd104 = loadshapes(auStack_5c,0);
  dword_dd100 = locateshape(dword_dd104,&aPst2_c0fbd);
  drawshape_remap(dword_dd100,0,0x1c);
  freemem(dword_dd104);
  getfontstate(auStack_9c);
  setfont(uVar5);
  text_capture_begin();
  set_text_colors(0x40,0x43);
  stats_source_title(auStack_13c,(&off_c6b70)[local_280[0]]);
  iVar4 = textwidth(auStack_13c);
  print_outlined(300 - (iVar4 >> 1),0x31,auStack_13c);
  if (CONCAT22(uStack_26,local_28) == 0) {
    setfont(uVar5);
    print_centered_shadow(0xeb,aStatsUnavailable);
    setfont(uVar1);
    iVar4 = CONCAT22(local_20._2_2_,(short)local_20);
  }
  else {
    setfont(uVar1);
    uVar14 = local_280[0];
    puVar10 = off_c6b68;
    local_20._0_2_ = 0x5c;
    local_20._2_2_ = 0;
    if (local_280[0] == 5) {
      iVar15 = CONCAT22(0x5c,local_24._2_2_) >> 0x10;
      iVar4 = textwidth(off_c6b68);
      print_text_at((int)(short)(0xa0 - (short)(iVar4 >> 1)),iVar15,puVar10);
      puVar10 = off_c6b6c;
      iVar4 = textwidth(off_c6b6c);
      print_text_at((int)(short)(0x1e0 - (short)(iVar4 >> 1)),iVar15,puVar10);
      local_20._0_2_ = 0x73;
      local_20._2_2_ = 0;
      iVar4 = CONCAT22(0x73,local_24._2_2_) >> 0x10;
      print_text_at(0xec,iVar4,&aGP_c0fd4);
      print_text_at(0x21c,iVar4,&aGP_c0fd4);
      print_text_at(0x114,(int)(short)local_20,
                    (&off_c6b88)[(uint)(dword_c6956 != 0) + local_280[0] * 4]);
      puVar10 = (&off_c6b88)[local_280[0] * 4 + (uint)(dword_c6956 != 0)];
      iVar4 = CONCAT22((short)local_20,local_24._2_2_);
      uVar5 = 0x244;
    }
    else {
      iVar4 = CONCAT22(0x5c,local_24._2_2_) >> 0x10;
      print_text_at(0x154,iVar4,&aGP_c0fd4);
      print_text_at(0x186,iVar4,(&off_c6b88)[uVar14 * 4]);
      print_text_at(0x1b8,iVar4,(&off_c6b8c)[uVar14 * 4]);
      if ((dword_c6956 == 0) || ((uVar14 != 1 && (uVar14 != 0)))) {
        print_text_at(0x1ea,(int)(short)local_20,(&off_c6b90)[local_280[0] * 4]);
      }
      puVar10 = (&off_c6b94)[local_280[0] * 4];
      iVar4 = CONCAT22((short)local_20,local_24._2_2_);
      uVar5 = 0x21c;
    }
    print_text_at(uVar5,iVar4 >> 0x10,puVar10);
    local_24._0_2_ = 1;
    local_24._2_2_ = 0;
    local_24 = 1;
    iVar4 = CONCAT22(local_20._2_2_,(short)local_20) + 0x10;
    local_20._0_2_ = (short)iVar4;
    local_20._2_2_ = (undefined2)((uint)iVar4 >> 0x10);
    if (local_280[0] == 5) {
      for (iVar15 = 0; iVar15 < CONCAT22(uStack_26,local_28); iVar15 = iVar15 + 1) {
        local_3c[1] = 0;
        local_20 = iVar4;
        if (iVar15 < 0xc) {
          uStack_1c = local_280[iVar15 + 1];
          iVar7 = 0x13;
          puVar13 = (undefined4 *)(dword_dd108 + local_280[iVar15 + 1] * 0x4c);
          puVar16 = &uStack_e8;
          while( true ) {
            local_20._0_2_ = (short)iVar4;
            local_20 = iVar4;
            if (iVar7 == 0) break;
            iVar7 = iVar7 + -1;
            *puVar16 = *puVar13;
            puVar13 = puVar13 + (uint)bVar17 * -2 + 1;
            puVar16 = puVar16 + (uint)bVar17 * -2 + 1;
            iVar4 = local_20;
          }
          if (dword_c6956 == 0) {
            pbVar6 = abStack_c0;
          }
          else {
            pbVar6 = abStack_c0 + 0x12;
          }
          if ((dword_c695a != 0) || (*pbVar6 != 0)) {
            iVar7 = (int)(short)local_20;
            print_textf((int)(short)((short)local_3c[1] + 0x1e),iVar7,&a2d,(int)(short)local_24);
            iVar4 = strnicmp_ascii(&uStack_e8,&aANA_c0fd7,3);
            if (iVar4 == 0) {
              pcVar12 = aMightyDucksOfAnaheim;
            }
            else {
              pcVar12 = acStack_e3;
            }
            print_text_at((int)(short)((short)local_3c[1] + 0x3c),iVar7,pcVar12);
            iVar4 = (int)(short)local_20;
            print_textf((int)(short)((short)local_3c[1] + 0xec),iVar4,&a2d,*pbVar6);
            if (dword_c6956 == 0) {
              uVar8 = (ushort)pbVar6[3] + (ushort)pbVar6[1] * 2;
              puVar13 = &a3d;
            }
            else {
              uVar8 = (ushort)pbVar6[1];
              puVar13 = &a2d;
            }
            print_textf((int)(short)((short)local_3c[1] + 0x114),iVar4,puVar13,uVar8);
            goto LAB_00023fa4;
          }
        }
        else {
LAB_00023fa4:
          local_3c[1] = 0x140;
          uStack_1c = local_248[iVar15 + 1];
          iVar7 = 0x13;
          puVar13 = (undefined4 *)(dword_dd108 + local_248[iVar15 + 1] * 0x4c);
          puVar16 = &uStack_e8;
          iVar4 = local_20;
          while( true ) {
            local_20._0_2_ = (short)iVar4;
            local_20 = iVar4;
            if (iVar7 == 0) break;
            iVar7 = iVar7 + -1;
            *puVar16 = *puVar13;
            puVar13 = puVar13 + (uint)bVar17 * -2 + 1;
            puVar16 = puVar16 + (uint)bVar17 * -2 + 1;
            iVar4 = local_20;
          }
          if (dword_c6956 == 0) {
            pbVar6 = abStack_c0;
          }
          else {
            pbVar6 = abStack_c0 + 0x12;
          }
          if ((dword_c695a != 0) || (*pbVar6 != 0)) {
            iVar7 = (int)(short)local_20;
            print_textf((int)(short)((short)local_3c[1] + 0x1e),iVar7,&a2d,(int)(short)local_24);
            iVar4 = strnicmp_ascii(&uStack_e8,&aANA_c0fd7,3);
            if (iVar4 == 0) {
              pcVar12 = aMightyDucksOfAnaheim;
            }
            else {
              pcVar12 = acStack_e3;
            }
            print_text_at((int)(short)((short)local_3c[1] + 0x3c),iVar7,pcVar12);
            iVar4 = (int)(short)local_20;
            print_textf((int)(short)((short)local_3c[1] + 0xdc),iVar4,&a2d,*pbVar6);
            if (dword_c6956 == 0) {
              uVar8 = (ushort)pbVar6[1] * 2 + (ushort)pbVar6[3];
              puVar13 = &a3d;
            }
            else {
              uVar8 = (ushort)pbVar6[1];
              puVar13 = &a2d;
            }
            print_textf((int)(short)((short)local_3c[1] + 0x104),iVar4,puVar13,uVar8);
            iVar4 = local_24 + 1;
            local_24._0_2_ = (short)iVar4;
            local_24._2_2_ = (undefined2)((uint)iVar4 >> 0x10);
            local_24 = iVar4;
            if ((iVar4 == 9) && (dword_c6956 == 0)) {
              local_20 = local_20 + 0xd;
              iVar4 = (int)(short)local_20;
              print_text_at(0x1e,iVar4,unk_c0ff3);
              print_text_at(0x15e,iVar4,unk_c101b);
            }
            iVar4 = local_20 + 0xd;
            local_20._0_2_ = (short)iVar4;
            local_20._2_2_ = (undefined2)((uint)iVar4 >> 0x10);
          }
        }
      }
    }
    else {
      for (iVar15 = 0; iVar15 < CONCAT22(uStack_26,local_28); iVar15 = iVar15 + 1) {
        uStack_1c = auStack_1a4[iVar15];
        iVar7 = 0x13;
        puVar13 = (undefined4 *)(dword_dd108 + auStack_1a4[iVar15] * 0x4c);
        puVar16 = &uStack_e8;
        while( true ) {
          local_20._0_2_ = (short)iVar4;
          local_20 = iVar4;
          if (iVar7 == 0) break;
          iVar7 = iVar7 + -1;
          *puVar16 = *puVar13;
          puVar13 = puVar13 + (uint)bVar17 * -2 + 1;
          puVar16 = puVar16 + (uint)bVar17 * -2 + 1;
          iVar4 = local_20;
        }
        if (dword_c6956 == 0) {
          pbVar6 = abStack_c0;
        }
        else {
          pbVar6 = abStack_c0 + 0x12;
        }
        if ((dword_c695a == 0) && (*pbVar6 == 0)) goto LAB_000243fd;
        iVar4 = (int)(short)local_24;
        iVar7 = (int)(short)local_20;
        local_24 = local_24 + 1;
        print_textf(0x50,iVar7,&a2d,iVar4);
        iVar4 = strnicmp_ascii(&uStack_e8,&aANA_c0fd7,3);
        if (iVar4 == 0) {
          pcVar12 = aMightyDucksOfAnaheim;
        }
        else {
          pcVar12 = acStack_e3;
        }
        print_text_at(0x6e,iVar7,pcVar12);
        iVar7 = (int)(short)local_20;
        print_textf(0x154,iVar7,&a2d,*pbVar6);
        iVar4 = local_3c[2];
        local_3c[2] = uStack_1c << 2;
        switch(local_280[0]) {
        case 0:
          print_textf(0x186,iVar7,&a2d,pbVar6[1]);
          print_textf(0x1b8,iVar7,&a2d,pbVar6[2]);
          if (dword_c6956 == 0) {
            print_textf(0x1ea,iVar7,&a2d,pbVar6[3]);
          }
          iVar4 = *(int *)(pbVar6 + 2);
          break;
        case 1:
          print_textf(0x186,iVar7,&a2d,pbVar6[1]);
          print_textf(0x1b8,iVar7,&a2d,pbVar6[2]);
          if (dword_c6956 == 0) {
            print_textf(0x1ea,iVar7,&a2d,pbVar6[3]);
          }
          iVar4 = *(int *)(pbVar6 + 4);
          break;
        case 2:
          print_textf(0x186,iVar7,&a3d,*(int *)(pbVar6 + 0xc) >> 0x10);
          iVar4 = *(int *)(pbVar6 + 10);
          puVar13 = &a4d;
          goto LAB_00024339;
        case 3:
          print_textf(0x186,iVar7,&a3d,*(int *)(pbVar6 + 8) >> 0x10);
          iVar4 = *(int *)(pbVar6 + 6);
          puVar13 = &a3d;
LAB_00024339:
          print_textf(0x1b8,iVar7,puVar13,iVar4 >> 0x10);
          sVar9 = (short)((longlong)*(int *)(dword_dd118 + local_3c[2]) % 10);
          sVar2 = (short)((longlong)*(int *)(dword_dd118 + local_3c[2]) / 10);
          uVar5 = 0x1ea;
LAB_000243f0:
          print_textf2(uVar5,iVar7,a3d1d,(int)sVar2,(int)sVar9);
          iVar4 = local_3c[2];
          goto LAB_000243f5;
        case 4:
          print_textf(0x186,iVar7,&a3d,*(int *)(pbVar6 + 0xe) >> 0x10);
          sVar9 = (short)((longlong)*(int *)(dword_dd118 + local_3c[2]) % 10);
          sVar2 = (short)((longlong)*(int *)(dword_dd118 + local_3c[2]) / 10);
          uVar5 = 0x1b8;
          goto LAB_000243f0;
        default:
          goto LAB_000243f5;
        }
        print_textf(0x21c,(int)(short)local_20,&a3d,iVar4 >> 0x10);
        iVar4 = local_3c[2];
LAB_000243f5:
        local_3c[2] = iVar4;
        iVar4 = local_20 + 0xd;
        local_20._0_2_ = (short)iVar4;
        local_20._2_2_ = (undefined2)((uint)iVar4 >> 0x10);
LAB_000243fd:
      }
    }
  }
  local_20 = iVar4;
  text_capture_stop();
  setfontstate(auStack_9c);
  if (1 < (int)local_280[0]) {
    freemem(dword_dd118);
  }
  freemem(dword_dd108);
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// stats_row_at @ 0x24453 [__watcall]
// ================================================================================================

undefined4 __watcall stats_row_at(undefined4 param_1,int unaff_EDX,int *unaff_EBX)

{
  int iVar1;
  
  __CHK(8);
  *unaff_EBX = 0;
  if (unaff_EDX < 0x40) {
    return 0;
  }
  if (unaff_EDX < dword_dc750 * 0xd + 0x40) {
    iVar1 = (unaff_EDX + -0x40) / 0xd;
  }
  else {
    if (unaff_EDX < 0x1a5) {
      return 0;
    }
    if (dword_dc6b8 * 0xd + 0x1a5 <= unaff_EDX) {
      return 0;
    }
    iVar1 = dword_dc750 + (unaff_EDX + -0x1a5) / 0xd;
  }
  *unaff_EBX = iVar1;
  return 1;
}


// ================================================================================================
// player_stats_screen @ 0x244e2 [__watcall]
// ================================================================================================

longlong __watcall player_stats_screen(int param_1,uint unaff_EDX)

{
  ushort uVar1;
  int iVar2;
  undefined4 uVar3;
  __off_t _Var4;
  undefined *puVar5;
  undefined4 uVar6;
  int iVar7;
  undefined4 *puVar8;
  int *piVar9;
  undefined4 *puVar10;
  byte bVar11;
  undefined5 *puVar12;
  undefined auStack_424 [5];
  undefined auStack_41f [71];
  int aiStack_3d8 [25];
  int aiStack_374 [142];
  undefined auStack_13c [64];
  undefined4 auStack_fc [13];
  undefined local_c5 [2];
  byte bStack_c3;
  undefined auStack_c1 [16];
  undefined auStack_b1 [21];
  __off_t local_9c;
  __off_t _Stack_98;
  undefined4 auStack_90 [12];
  undefined auStack_60 [32];
  int local_40;
  int local_3c;
  int local_38;
  int local_34;
  undefined4 local_30;
  undefined4 local_2c;
  int *local_28;
  int local_24;
  undefined4 local_20;
  undefined4 uStack_1c;
  
  bVar11 = 0;
  __CHK(0x43c);
  local_2c = font_main;
  local_30 = font_kaufm;
  make_path(auStack_60,&unk_c65d4,off_c68f8,0);
  iVar2 = c_open(auStack_60,0x200);
  local_34 = iVar2;
  lseek(iVar2,param_1 * 0x2e8,0);
  read(iVar2,auStack_424,0x2e8);
  make_path(auStack_60,&unk_c65d4,aKeyDb,0);
  local_40 = c_open(auStack_60,0x200);
  make_path(auStack_60,&unk_c65d4,(&off_c68ec)[dword_c695a],0);
  local_3c = c_open(auStack_60,0x200);
  local_38 = 0;
  for (iVar2 = 0; iVar2 < 0x19; iVar2 = iVar2 + 1) {
    if (aiStack_3d8[iVar2] != -1) {
      lseek(local_40,aiStack_3d8[iVar2],0);
      read(local_40,local_c5 + 1,0x34);
      puVar8 = (undefined4 *)(local_c5 + 1);
      puVar10 = (undefined4 *)(dword_dd11c + iVar2 * 0x34);
      for (iVar7 = 0xd; iVar7 != 0; iVar7 = iVar7 + -1) {
        *puVar10 = *puVar8;
        puVar8 = puVar8 + (uint)bVar11 * -2 + 1;
        puVar10 = puVar10 + (uint)bVar11 * -2 + 1;
      }
      _Var4 = _Stack_98;
      if (dword_c695a == 0) {
        _Var4 = local_9c;
      }
      lseek(local_3c,_Var4,0);
      read(local_3c,auStack_90,0x2f);
      puVar8 = auStack_90;
      puVar10 = (undefined4 *)(dword_dd110 + local_38 * 0x2f);
      for (iVar7 = 0xb; iVar7 != 0; iVar7 = iVar7 + -1) {
        *puVar10 = *puVar8;
        puVar8 = puVar8 + (uint)bVar11 * -2 + 1;
        puVar10 = puVar10 + (uint)bVar11 * -2 + 1;
      }
      *(undefined2 *)puVar10 = *(undefined2 *)puVar8;
      *(undefined *)((int)puVar10 + (uint)bVar11 * -4 + 2) =
           *(undefined *)((int)puVar8 + (uint)bVar11 * -4 + 2);
      *(int *)(&unk_dc754 + local_38 * 4) = iVar2;
      (&unk_dc6bc)[local_38] = local_38;
      local_38 = local_38 + 1;
    }
  }
  local_20._0_2_ = 0;
  local_20._2_2_ = 0;
  iVar2 = 0;
  for (iVar7 = 0; local_20 = iVar2, iVar7 < 3; iVar7 = iVar7 + 1) {
    if (aiStack_374[iVar7] != -1) {
      lseek(local_40,aiStack_374[iVar7],0);
      read(local_40,local_c5 + 1,0x34);
      puVar8 = (undefined4 *)(local_c5 + 1);
      puVar10 = (undefined4 *)(dword_dd11c + (iVar7 + 0x19) * 0x34);
      for (iVar2 = 0xd; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar10 = *puVar8;
        puVar8 = puVar8 + (uint)bVar11 * -2 + 1;
        puVar10 = puVar10 + (uint)bVar11 * -2 + 1;
      }
      _Var4 = _Stack_98;
      if (dword_c695a == 0) {
        _Var4 = local_9c;
      }
      lseek(local_3c,_Var4,0);
      read(local_3c,auStack_fc,0x36);
      puVar8 = auStack_fc;
      puVar10 = (undefined4 *)(dword_dd114 + local_20 * 0x36);
      for (iVar2 = 0xd; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar10 = *puVar8;
        puVar8 = puVar8 + (uint)bVar11 * -2 + 1;
        puVar10 = puVar10 + (uint)bVar11 * -2 + 1;
      }
      *(undefined2 *)puVar10 = *(undefined2 *)puVar8;
      *(int *)(&unk_dc73c + local_20 * 4) = iVar7 + 0x19;
      (&unk_dc720)[local_20] = local_20;
      iVar2 = local_20 + 1;
      local_20._0_2_ = (undefined2)iVar2;
      local_20._2_2_ = (undefined2)((uint)iVar2 >> 0x10);
    }
  }
  _close(local_34);
  _close(local_40);
  _close(local_3c);
  qsort(&unk_dc6bc,local_38,4,cmp_leaders_points);
  qsort(&unk_dc720,local_20,4,cmp_leaders_gaa);
  setdefaultscreen();
  sprintf((char *)&unk_dd0d8,aEmbS_c6935,auStack_424);
  puVar5 = install_path;
  if ((&byte_ed83c)[param_1] != '\x01') {
    puVar5 = (undefined *)0x0;
  }
  make_path(auStack_60,puVar5,&unk_dd0d8,0);
  dword_dd104 = loadshapes(auStack_60,0);
  dword_dd100 = locateshape(dword_dd104,&aBkgd_c693b);
  setclip(0,0x280,0x13,0x1e0);
  drawshape_remap_home(dword_dd100);
  setclip(0,0x280,0,0x1e0);
  freemem(dword_dd104);
  puVar5 = install_path;
  if (byte_ed908 != '\x01') {
    puVar5 = (undefined *)0x0;
  }
  make_path(auStack_60,puVar5,aPstatbar_c1047,0);
  dword_dd104 = loadshapes(auStack_60,0);
  dword_dd100 = locateshape(dword_dd104,&aPst2_c1050);
  drawshape_remap(dword_dd100,0,6);
  getfontstate(auStack_13c);
  setfont(local_2c);
  text_capture_begin();
  if (dword_dc734 == 0) {
    uVar6 = 0x43;
    uVar3 = 0x40;
  }
  else {
    uVar6 = 0xc3;
    uVar3 = 0xc0;
  }
  set_text_colors(uVar3,uVar6);
  setfont(local_30);
  set_text_colors(0x40,0x43);
  uStack_1c._0_2_ = 0x1b;
  uStack_1c._2_2_ = 0;
  if (param_1 == 0x18) {
    sprintf((char *)&unk_dd0d8,aMightyDucksOfAnaheim_c1062);
    iVar2 = textwidth(&unk_dd0d8);
    print_outlined(300 - (iVar2 >> 1),0x1b,&unk_dd0d8);
    dword_dd100 = locateshape(dword_dd104,&aTrad);
    iVar2 = 0x1b;
    iVar7 = 0x12a;
  }
  else {
    sprintf((char *)&unk_dd0d8,(char *)&aS,auStack_41f);
    iVar2 = textwidth(&unk_dd0d8);
    print_outlined(300 - (iVar2 >> 1),0x1b,&unk_dd0d8);
    if (((param_1 == 2) || (param_1 == 0x18)) || (param_1 == 0x19)) {
      puVar12 = &aTrad;
    }
    else {
      puVar12 = &aRegi;
    }
    dword_dd100 = locateshape(dword_dd104,puVar12);
    iVar2 = CONCAT22(uStack_1c._2_2_,(short)uStack_1c) + 6;
    iVar7 = textwidth(&unk_dd0d8,iVar2);
    iVar7 = (iVar7 >> 1) + 300;
  }
  drawshape_remap(dword_dd100,iVar7,iVar2);
  freemem(dword_dd104);
  setfont(local_2c);
  set_text_colors(0x40,0x43);
  uStack_1c._0_2_ = 0x30;
  uStack_1c._2_2_ = 0;
  iVar2 = CONCAT22(0x30,local_20._2_2_) >> 0x10;
  print_text_at(0x14,iVar2,&aPos);
  print_text_at(0x42,iVar2,&aNo);
  print_text_at(0x60,iVar2,&aName);
  print_text_at(0x10e,iVar2,&aGP_c1087);
  print_text_at(0x136,iVar2,&aG_c108a);
  print_text_at(0x15e,iVar2,&aA_c108e);
  print_text_at(0x186,iVar2,&aPT);
  print_text_at(0x1ae,iVar2,aShots_c1096);
  print_text_at(0x1e8,iVar2,&aPIM_c109c);
  print_text_at(0x210,iVar2,&unk_c10a0);
  uStack_1c = 0x40;
  iVar2 = local_20;
  for (iVar7 = 0; local_20._2_2_ = (undefined2)((uint)iVar2 >> 0x10), local_20 = iVar2,
      iVar7 < local_38; iVar7 = iVar7 + 1) {
    local_24 = (&unk_dc6bc)[iVar7];
    puVar8 = (undefined4 *)(dword_dd11c + *(int *)(&unk_dc754 + local_24 * 4) * 0x34);
    puVar10 = (undefined4 *)(local_c5 + 1);
    for (iVar2 = 0xd; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar10 = *puVar8;
      puVar8 = puVar8 + (uint)bVar11 * -2 + 1;
      puVar10 = puVar10 + (uint)bVar11 * -2 + 1;
    }
    sprintf((char *)&unk_dd0d8,(char *)&aC_c10a5,_local_c5 >> 0x18);
    iVar2 = (int)(short)uStack_1c;
    print_text_at(0x14,iVar2,&unk_dd0d8);
    if (bStack_c3 < 100) {
      print_textf(0x42,iVar2,&a2d,bStack_c3);
    }
    format_team_name(&unk_dd0d8,auStack_c1,auStack_b1,0xa6);
    print_text_at(0x60,(int)(short)uStack_1c,&unk_dd0d8);
    if (dword_c6956 == 0) {
      piVar9 = (int *)(local_24 * 0x2f + dword_dd110);
    }
    else {
      piVar9 = (int *)(local_24 * 0x2f + dword_dd110 + 0x12);
    }
    iVar2 = (int)(short)uStack_1c;
    print_textf(0x10e,iVar2,&a2d,(int)*(short *)piVar9);
    print_textf(0x136,iVar2,&a3d,*piVar9 >> 0x10);
    print_textf(0x15e,iVar2,&a3d,*(int *)((int)piVar9 + 2) >> 0x10);
    print_textf(0x186,iVar2,&a3d,piVar9[1] >> 0x10);
    print_textf(0x1ae,iVar2,&a5d,piVar9[3] >> 0x10);
    print_textf(0x1e8,iVar2,&a3d,*(int *)((int)piVar9 + 10) >> 0x10);
    print_textf(0x210,iVar2,&a4d,*(int *)((int)piVar9 + 0xe) >> 0x10);
    uStack_1c = uStack_1c + 0xd;
    iVar2 = local_20;
  }
  uStack_1c._0_2_ = 0x195;
  uStack_1c._2_2_ = 0;
  iVar2 = CONCAT22(0x195,local_20._2_2_) >> 0x10;
  print_text_at(0x14,iVar2,&aPos);
  print_text_at(0x42,iVar2,&aNo);
  print_text_at(0x60,iVar2,&aName);
  print_text_at(0x10e,iVar2,&aGP_c1087);
  print_text_at(0x136,iVar2,&aMin_c10a8);
  print_text_at(0x15e,iVar2,aGAA_c10ad);
  print_text_at(400,iVar2,&aW_c10b3);
  print_text_at(0x1ae,iVar2,&aL_c10b6);
  if (dword_c6956 == 0) {
    print_text_at(0x1cc,iVar2,&aT_c10b9);
  }
  iVar2 = (int)(short)uStack_1c;
  print_text_at(0x1ea,iVar2,&aGA_c10bc);
  print_text_at(0x20e,iVar2,&aSA_c10c0);
  print_text_at(0x240,iVar2,aPCT_c10c5);
  uStack_1c = CONCAT22(uStack_1c._2_2_,(short)uStack_1c) + 0x10;
  for (iVar2 = 0; iVar2 < local_20; iVar2 = iVar2 + 1) {
    local_24 = (&unk_dc720)[iVar2];
    puVar8 = (undefined4 *)(*(int *)(&unk_dc73c + local_24 * 4) * 0x34 + dword_dd11c);
    puVar10 = (undefined4 *)(local_c5 + 1);
    for (iVar7 = 0xd; iVar7 != 0; iVar7 = iVar7 + -1) {
      *puVar10 = *puVar8;
      puVar8 = puVar8 + (uint)bVar11 * -2 + 1;
      puVar10 = puVar10 + (uint)bVar11 * -2 + 1;
    }
    sprintf((char *)&unk_dd0d8,(char *)&aC_c10a5,_local_c5 >> 0x18);
    iVar7 = (int)(short)uStack_1c;
    print_text_at(0x14,iVar7);
    if (bStack_c3 < 100) {
      print_textf(0x42,iVar7,&a2d,bStack_c3);
    }
    format_team_name(&unk_dd0d8,auStack_c1,auStack_b1,0xa6);
    print_text_at(0x60,(int)(short)uStack_1c,&unk_dd0d8);
    if (dword_c6956 == 0) {
      piVar9 = (int *)(local_24 * 0x36 + dword_dd114);
    }
    else {
      piVar9 = (int *)(local_24 * 0x36 + dword_dd114 + 0x16);
    }
    iVar7 = (int)(short)uStack_1c;
    local_28 = piVar9;
    print_textf(0x10e,iVar7,&a2d,(int)*(short *)piVar9);
    print_textf(0x136,iVar7,&a4d,*(int *)((int)piVar9 + 10) >> 0x10);
    print_textf2(0x15e,iVar7,a2d22d,
              (short)((ulonglong)(longlong)(int)(uint)*(ushort *)(piVar9 + 4) / 100),
              (short)((ulonglong)(longlong)(int)(uint)*(ushort *)(piVar9 + 4) % 100));
    print_textf(400,iVar7,&a2d,*piVar9 >> 0x10);
    print_textf(0x1ae,iVar7,&a2d,*(int *)((int)piVar9 + 2) >> 0x10);
    if (dword_c6956 == 0) {
      print_textf(0x1cc,iVar7,&a2d,piVar9[1] >> 0x10);
    }
    iVar7 = (int)(short)uStack_1c;
    print_textf(0x1ea,iVar7,&a3d,local_28[3] >> 0x10);
    print_textf(0x20e,iVar7,&a4d,local_28[4] >> 0x10);
    uVar1 = *(ushort *)(local_28 + 5);
    if (uVar1 < 1000) {
      print_textf(0x240,iVar7,a03d,*(ushort *)(local_28 + 5) % 1000);
    }
    else {
      print_textf2(0x240,iVar7,a1d03d,(short)((ulonglong)(longlong)(int)(uint)uVar1 / 1000),
                (short)((ulonglong)(longlong)(int)(uint)uVar1 % 1000));
    }
    uStack_1c = uStack_1c + 0xd;
  }
  text_capture_stop();
  setfontstate(auStack_13c);
  dword_dc750 = local_38;
  dword_dc6b8 = local_20;
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// cmp_leaders_goals @ 0x25144 [__watcall]
// ================================================================================================

int __watcall cmp_leaders_goals(int *param_1,int *unaff_EDX)

{
  ushort uVar1;
  ushort *puVar2;
  ushort *puVar3;
  uint uVar4;
  ushort uVar5;
  uint uVar6;
  
  __CHK(0x14);
  if (dword_c6956 == 0) {
    puVar2 = (ushort *)(*param_1 * 0x2f + dword_dd110);
    puVar3 = (ushort *)(*unaff_EDX * 0x2f + dword_dd110);
  }
  else {
    puVar2 = (ushort *)(*param_1 * 0x2f + dword_dd110 + 0x12);
    puVar3 = (ushort *)(dword_dd110 + *unaff_EDX * 0x2f + 0x12);
  }
  uVar1 = puVar3[1];
  uVar5 = puVar2[1];
  if (uVar1 == uVar5) {
    if (*puVar3 != *puVar2) {
      return (uint)*puVar2 - (uint)*puVar3;
    }
    uVar1 = puVar3[3];
    uVar5 = puVar2[3];
    if (uVar1 == uVar5) {
      uVar4 = *(int *)(puVar3 + 7) >> 0x10;
      uVar6 = *(int *)(puVar2 + 7) >> 0x10;
      goto LAB_00025230;
    }
  }
  uVar4 = (uint)uVar1;
  uVar6 = (uint)uVar5;
LAB_00025230:
  return uVar4 - uVar6;
}


// ================================================================================================
// cmp_leaders_assists @ 0x25237 [__watcall]
// ================================================================================================

int __watcall cmp_leaders_assists(int *param_1,int *unaff_EDX)

{
  ushort uVar1;
  ushort *puVar2;
  ushort *puVar3;
  uint uVar4;
  ushort uVar5;
  uint uVar6;
  
  __CHK(0x14);
  if (dword_c6956 == 0) {
    puVar2 = (ushort *)(*param_1 * 0x2f + dword_dd110);
    puVar3 = (ushort *)(*unaff_EDX * 0x2f + dword_dd110);
  }
  else {
    puVar2 = (ushort *)(*param_1 * 0x2f + dword_dd110 + 0x12);
    puVar3 = (ushort *)(dword_dd110 + *unaff_EDX * 0x2f + 0x12);
  }
  uVar1 = puVar3[2];
  uVar5 = puVar2[2];
  if (uVar1 == uVar5) {
    if (*puVar3 != *puVar2) {
      return (uint)*puVar3 - (uint)*puVar2;
    }
    uVar1 = puVar3[3];
    uVar5 = puVar2[3];
    if (uVar1 == uVar5) {
      uVar4 = *(int *)(puVar3 + 7) >> 0x10;
      uVar6 = *(int *)(puVar2 + 7) >> 0x10;
      goto LAB_0002531e;
    }
  }
  uVar4 = (uint)uVar1;
  uVar6 = (uint)uVar5;
LAB_0002531e:
  return uVar4 - uVar6;
}


// ================================================================================================
// cmp_leaders_pp_goals @ 0x25325 [__watcall]
// ================================================================================================

int __watcall cmp_leaders_pp_goals(int *param_1,int *unaff_EDX)

{
  ushort uVar1;
  ushort *puVar2;
  ushort *puVar3;
  uint uVar4;
  ushort uVar5;
  uint uVar6;
  
  __CHK(0x14);
  if (dword_c6956 == 0) {
    puVar2 = (ushort *)(*param_1 * 0x2f + dword_dd110);
    puVar3 = (ushort *)(*unaff_EDX * 0x2f + dword_dd110);
  }
  else {
    puVar2 = (ushort *)(*param_1 * 0x2f + dword_dd110 + 0x12);
    puVar3 = (ushort *)(*unaff_EDX * 0x2f + dword_dd110 + 0x12);
  }
  if (puVar3[4] != puVar2[4]) {
    uVar6 = (uint)puVar3[4];
    uVar4 = (uint)puVar2[4];
LAB_0002542f:
    return uVar6 - uVar4;
  }
  if (*puVar3 != *puVar2) {
    return (uint)*puVar2 - (uint)*puVar3;
  }
  uVar1 = puVar3[3];
  uVar5 = puVar2[3];
  if (uVar1 == uVar5) {
    uVar1 = puVar3[1];
    uVar5 = puVar2[1];
    if (uVar1 == uVar5) {
      uVar6 = *(int *)(puVar3 + 7) >> 0x10;
      uVar4 = *(int *)(puVar2 + 7) >> 0x10;
      goto LAB_0002542f;
    }
  }
  return (uint)uVar1 - (uint)uVar5;
}


// ================================================================================================
// cmp_leaders_sh_goals @ 0x25438 [__watcall]
// ================================================================================================

int __watcall cmp_leaders_sh_goals(int *param_1,int *unaff_EDX)

{
  ushort uVar1;
  ushort *puVar2;
  ushort *puVar3;
  uint uVar4;
  ushort uVar5;
  uint uVar6;
  
  __CHK(0x14);
  if (dword_c6956 == 0) {
    puVar2 = (ushort *)(*param_1 * 0x2f + dword_dd110);
    puVar3 = (ushort *)(*unaff_EDX * 0x2f + dword_dd110);
  }
  else {
    puVar2 = (ushort *)(*param_1 * 0x2f + dword_dd110 + 0x12);
    puVar3 = (ushort *)(*unaff_EDX * 0x2f + dword_dd110 + 0x12);
  }
  if (puVar3[5] != puVar2[5]) {
    uVar6 = (uint)puVar3[5];
    uVar4 = (uint)puVar2[5];
LAB_00025542:
    return uVar6 - uVar4;
  }
  if (*puVar3 != *puVar2) {
    return (uint)*puVar2 - (uint)*puVar3;
  }
  uVar1 = puVar3[3];
  uVar5 = puVar2[3];
  if (uVar1 == uVar5) {
    uVar1 = puVar3[1];
    uVar5 = puVar2[1];
    if (uVar1 == uVar5) {
      uVar6 = *(int *)(puVar3 + 7) >> 0x10;
      uVar4 = *(int *)(puVar2 + 7) >> 0x10;
      goto LAB_00025542;
    }
  }
  return (uint)uVar1 - (uint)uVar5;
}


// ================================================================================================
// cmp_leaders_plus_minus @ 0x2554b [__watcall]
// ================================================================================================

int __watcall cmp_leaders_plus_minus(int *param_1,int *unaff_EDX)

{
  ushort *puVar1;
  ushort *puVar2;
  uint uVar3;
  uint uVar4;
  
  __CHK(0x10);
  if (dword_c6956 == 0) {
    puVar1 = (ushort *)(*param_1 * 0x2f + dword_dd110);
    puVar2 = (ushort *)(*unaff_EDX * 0x2f + dword_dd110);
  }
  else {
    puVar1 = (ushort *)(*param_1 * 0x2f + dword_dd110 + 0x12);
    puVar2 = (ushort *)(dword_dd110 + *unaff_EDX * 0x2f + 0x12);
  }
  if (puVar2[8] == puVar1[8]) {
    if (*puVar2 != *puVar1) {
      return (uint)*puVar1 - (uint)*puVar2;
    }
    if (puVar2[3] == puVar1[3]) {
      uVar3 = (uint)puVar2[1];
      uVar4 = (uint)puVar1[1];
    }
    else {
      uVar3 = (uint)puVar2[3];
      uVar4 = (uint)puVar1[3];
    }
  }
  else {
    uVar3 = *(int *)(puVar2 + 7) >> 0x10;
    uVar4 = *(int *)(puVar1 + 7) >> 0x10;
  }
  return uVar3 - uVar4;
}


// ================================================================================================
// cmp_leaders_penalty_minutes @ 0x25642 [__watcall]
// ================================================================================================

int __watcall cmp_leaders_penalty_minutes(int *param_1,int *unaff_EDX)

{
  ushort uVar1;
  ushort *puVar2;
  ushort *puVar3;
  uint uVar4;
  ushort uVar5;
  uint uVar6;
  
  __CHK(0x14);
  if (dword_c6956 == 0) {
    puVar2 = (ushort *)(*param_1 * 0x2f + dword_dd110);
    puVar3 = (ushort *)(*unaff_EDX * 0x2f + dword_dd110);
  }
  else {
    puVar2 = (ushort *)(*param_1 * 0x2f + dword_dd110 + 0x12);
    puVar3 = (ushort *)(*unaff_EDX * 0x2f + dword_dd110 + 0x12);
  }
  if (puVar3[6] != puVar2[6]) {
    uVar6 = (uint)puVar3[6];
    uVar4 = (uint)puVar2[6];
LAB_0002574c:
    return uVar6 - uVar4;
  }
  if (*puVar3 != *puVar2) {
    return (uint)*puVar2 - (uint)*puVar3;
  }
  uVar1 = puVar3[3];
  uVar5 = puVar2[3];
  if (uVar1 == uVar5) {
    uVar1 = puVar3[1];
    uVar5 = puVar2[1];
    if (uVar1 == uVar5) {
      uVar6 = *(int *)(puVar3 + 7) >> 0x10;
      uVar4 = *(int *)(puVar2 + 7) >> 0x10;
      goto LAB_0002574c;
    }
  }
  return (uint)uVar1 - (uint)uVar5;
}


// ================================================================================================
// cmp_leaders_shooting_pct @ 0x25755 [__watcall]
// ================================================================================================

int __watcall cmp_leaders_shooting_pct(int *param_1,int *unaff_EDX)

{
  int iVar1;
  int iVar2;
  ushort *puVar3;
  ushort *puVar4;
  uint uVar5;
  uint uVar6;
  
  __CHK(0x14);
  iVar1 = *(int *)(*unaff_EDX * 4 + dword_dd118);
  iVar2 = *(int *)(dword_dd118 + *param_1 * 4);
  if (iVar1 != iVar2) {
    return iVar1 - iVar2;
  }
  if (dword_c6956 == 0) {
    puVar3 = (ushort *)(*param_1 * 0x2f + dword_dd110);
    puVar4 = (ushort *)(*unaff_EDX * 0x2f + dword_dd110);
  }
  else {
    puVar3 = (ushort *)(dword_dd110 + *param_1 * 0x2f + 0x12);
    puVar4 = (ushort *)(*unaff_EDX * 0x2f + dword_dd110 + 0x12);
  }
  if (*puVar4 == *puVar3) {
    if (puVar4[3] != puVar3[3]) {
      return (uint)puVar4[3] - (uint)puVar3[3];
    }
    if (puVar4[1] == puVar3[1]) {
      uVar6 = *(int *)(puVar4 + 7) >> 0x10;
      uVar5 = *(int *)(puVar3 + 7) >> 0x10;
    }
    else {
      uVar6 = (uint)puVar4[1];
      uVar5 = (uint)puVar3[1];
    }
  }
  else {
    uVar6 = (uint)*puVar4;
    uVar5 = (uint)*puVar3;
  }
  return uVar6 - uVar5;
}


// ================================================================================================
// cmp_leaders_wins @ 0x2586a [__watcall]
// ================================================================================================

int __watcall cmp_leaders_wins(int *param_1,int *unaff_EDX)

{
  ushort uVar1;
  ushort uVar2;
  ushort *puVar3;
  uint uVar4;
  ushort *puVar5;
  
  __CHK(0x14);
  if (dword_c6956 == 0) {
    puVar3 = (ushort *)(dword_dd114 + *param_1 * 0x36);
    puVar5 = (ushort *)(dword_dd114 + *unaff_EDX * 0x36);
  }
  else {
    puVar3 = (ushort *)(*param_1 * 0x36 + dword_dd114 + 0x16);
    puVar5 = (ushort *)(dword_dd114 + *unaff_EDX * 0x36 + 0x16);
  }
  uVar2 = puVar3[1];
  if (puVar5[1] != uVar2) {
    uVar4 = (uint)puVar5[1];
    goto LAB_000259b2;
  }
  if (dword_c6956 == 0) {
    uVar1 = puVar5[3];
    uVar2 = puVar3[3];
    if (uVar1 == uVar2) goto LAB_00025931;
  }
  else {
LAB_00025931:
    uVar2 = puVar3[2];
    if (puVar5[2] != uVar2) {
      uVar1 = puVar5[2];
LAB_00025949:
      return (uint)uVar2 - (uint)uVar1;
    }
    if (*puVar5 != *puVar3) {
      return (uint)*puVar3 - (uint)*puVar5;
    }
    uVar1 = puVar5[6];
    uVar2 = puVar3[6];
    if (uVar1 == uVar2) {
      uVar2 = puVar3[8];
      if (puVar5[8] != uVar2) {
        uVar1 = puVar5[8];
        goto LAB_00025949;
      }
      uVar4 = (uint)puVar5[10];
      uVar2 = puVar3[10];
      goto LAB_000259b2;
    }
  }
  uVar4 = (uint)uVar1;
LAB_000259b2:
  return uVar4 - uVar2;
}


// ================================================================================================
// cmp_leaders_save_pct @ 0x259c0 [__watcall]
// ================================================================================================

int __watcall cmp_leaders_save_pct(int *param_1,int *unaff_EDX)

{
  ushort uVar1;
  ushort *puVar2;
  ushort *puVar3;
  ushort uVar4;
  
  __CHK(0x14);
  if (dword_c6956 == 0) {
    puVar2 = (ushort *)(*param_1 * 0x36 + dword_dd114);
    puVar3 = (ushort *)(*unaff_EDX * 0x36 + dword_dd114);
  }
  else {
    puVar2 = (ushort *)(*param_1 * 0x36 + dword_dd114 + 0x16);
    puVar3 = (ushort *)(*unaff_EDX * 0x36 + dword_dd114 + 0x16);
  }
  uVar1 = puVar2[10];
  if (puVar3[10] != uVar1) {
    uVar4 = puVar3[10];
LAB_00025a66:
    return (uint)uVar4 - (uint)uVar1;
  }
  uVar1 = puVar3[6];
  uVar4 = puVar2[6];
  if (uVar1 == uVar4) {
    uVar1 = *puVar2;
    if (*puVar3 != uVar1) {
      uVar4 = *puVar3;
      goto LAB_00025a66;
    }
    uVar1 = puVar3[1];
    uVar4 = puVar2[1];
    if (uVar1 == uVar4) {
      uVar1 = puVar3[2];
      uVar4 = puVar2[2];
      if (uVar1 == uVar4) {
        uVar4 = puVar2[8];
        uVar1 = puVar3[8];
      }
      return (uint)uVar4 - (uint)uVar1;
    }
  }
  return (uint)uVar1 - (uint)uVar4;
}


// ================================================================================================
// stats_table @ 0x25b24 [__watcall]
// ================================================================================================

/* WARNING: Type propagation algorithm not settling */

longlong __watcall stats_table(int param_1,uint unaff_EDX)

{
  ushort uVar1;
  undefined4 uVar2;
  byte bVar3;
  short sVar4;
  int iVar5;
  undefined4 uVar6;
  ssize_t sVar7;
  uint uVar8;
  int iVar9;
  __off_t _Var10;
  undefined *puVar11;
  undefined4 *puVar12;
  char *pcVar13;
  undefined1 *puVar14;
  int *unaff_EBP;
  int *piVar15;
  undefined4 *puVar16;
  byte bVar17;
  uint auStack_288 [26];
  undefined auStack_220 [80];
  uint local_1d0;
  uint auStack_1cc [20];
  undefined auStack_17c [26];
  undefined auStack_162 [14];
  byte bStack_154;
  byte bStack_142;
  undefined auStack_130 [64];
  undefined4 uStack_f0;
  undefined2 uStack_da;
  short sStack_d8;
  undefined local_b9 [2];
  byte bStack_b7;
  char cStack_b6;
  undefined auStack_b5 [16];
  undefined auStack_a5 [21];
  __off_t local_90;
  __off_t _Stack_8c;
  undefined4 uStack_84;
  uint uStack_76;
  undefined2 uStack_72;
  ushort uStack_70;
  uint uStack_64;
  undefined auStack_54 [32];
  int local_34;
  int local_30;
  undefined2 local_2c;
  undefined2 uStack_2a;
  undefined4 local_28;
  int *local_24;
  uint local_20;
  uint uStack_1c;
  
  bVar17 = 0;
  __CHK(0x2a0);
  local_34 = 0;
  dword_dd11c = allocmem(&aKeys_c1211,0x444,0x20);
  if (param_1 < 8) {
    dword_dd110 = allocmem(aPstat_c1216,0x3db,0x20);
  }
  else {
    dword_dd114 = allocmem(aGstat_c121c,0x46e,0x20);
  }
  if (param_1 == 7) {
    dword_dd118 = allocmem(aAddsort_c1222,0x54,0x20);
  }
  if ((((param_1 == 8) || (param_1 == 10)) || (param_1 == 5)) || (param_1 == 7)) {
    make_path(auStack_54,&unk_c65d4,(&off_c68f4)[dword_c695a],0);
    iVar5 = c_open(auStack_54,0x200);
    if (dword_c695a == 0) {
      iVar9 = 0x4c;
    }
    else {
      iVar9 = 0x2e8;
    }
    local_20 = 0;
    do {
      lseek(iVar5,local_20 * iVar9,0);
      read(iVar5,auStack_17c,0x4c);
      uVar8 = local_20;
      bVar3 = bStack_142;
      if (dword_c6956 == 0) {
        bVar3 = bStack_154;
      }
      auStack_288[local_20] = (uint)bVar3;
      if (((dword_c695a == 0) && (dword_c6956 == 0)) && (auStack_288[uVar8] == 0)) {
        auStack_288[uVar8] = 0;
      }
      local_20 = local_20 + 1;
    } while ((int)local_20 < 0x1a);
    _close(iVar5);
  }
  make_path(auStack_54,&unk_c65d4,aKeyDb_c122a,0);
  uVar6 = c_open(auStack_54,0x200);
  local_2c = (undefined2)uVar6;
  uStack_2a = (undefined2)((uint)uVar6 >> 0x10);
  make_path(auStack_54,&unk_c65d4,(&off_c68ec)[dword_c695a],0);
  local_30 = c_open(auStack_54,0x200);
LAB_00025f08:
  do {
    sVar7 = read(CONCAT22(uStack_2a,local_2c),local_b9 + 1,0x34);
    if (sVar7 != 0x34) break;
    if (local_b9[1] < 0x1a) {
      if (cStack_b6 == 'G') {
        if (param_1 < 8) goto LAB_00025f08;
        _Var10 = _Stack_8c;
        if (dword_c695a == 0) {
          _Var10 = local_90;
        }
        lseek(local_30,_Var10,0);
        read(local_30,&uStack_f0,0x36);
        if (dword_c6956 == 0) {
          uVar8 = CONCAT22(uStack_f0._2_2_,(undefined2)uStack_f0);
        }
        else {
          uVar8 = CONCAT22(sStack_d8,uStack_da);
        }
        if ((uVar8 & 0xffff) == 0) goto LAB_00025f08;
        if ((param_1 == 8) || (param_1 == 10)) {
          if ((auStack_288[_local_b9 >> 8 & 0xff] == 0) ||
             ((int)((uVar8 & 0xffff) * 100) / (int)auStack_288[_local_b9 >> 8 & 0xff] < 0x1e))
          goto LAB_00025f08;
        }
        else if (param_1 == 9) {
          sVar4 = sStack_d8;
          if (dword_c6956 == 0) {
            sVar4 = uStack_f0._2_2_;
          }
          if (sVar4 == 0) goto LAB_00025f08;
        }
        puVar12 = &uStack_f0;
        puVar16 = (undefined4 *)(dword_dd114 + local_34 * 0x36);
        for (iVar5 = 0xd; iVar5 != 0; iVar5 = iVar5 + -1) {
          *puVar16 = *puVar12;
          puVar12 = puVar12 + (uint)bVar17 * -2 + 1;
          puVar16 = puVar16 + (uint)bVar17 * -2 + 1;
        }
        *(undefined2 *)puVar16 = *(undefined2 *)puVar12;
        if ((0x13 < local_34) && (iVar5 = (*(code *)(&funcptr_c6be8)[param_1])(), -1 < iVar5))
        goto LAB_00025f08;
        if (local_34 < 0x14) {
          puVar12 = (undefined4 *)(local_b9 + 1);
          puVar16 = (undefined4 *)(dword_dd11c + local_34 * 0x34);
          for (iVar5 = 0xd; iVar5 != 0; iVar5 = iVar5 + -1) {
            *puVar16 = *puVar12;
            puVar12 = puVar12 + (uint)bVar17 * -2 + 1;
            puVar16 = puVar16 + (uint)bVar17 * -2 + 1;
          }
          auStack_1cc[local_34] = local_34;
          local_34 = local_34 + 1;
        }
        else {
          uStack_1c = (&local_1d0)[local_34];
          puVar12 = (undefined4 *)(local_b9 + 1);
          puVar16 = (undefined4 *)(dword_dd11c + uStack_1c * 0x34);
          for (iVar5 = 0xd; iVar5 != 0; iVar5 = iVar5 + -1) {
            *puVar16 = *puVar12;
            puVar12 = puVar12 + (uint)bVar17 * -2 + 1;
            puVar16 = puVar16 + (uint)bVar17 * -2 + 1;
          }
          puVar12 = &uStack_f0;
          puVar16 = (undefined4 *)(dword_dd114 + uStack_1c * 0x36);
          for (iVar5 = 0xd; iVar5 != 0; iVar5 = iVar5 + -1) {
            *puVar16 = *puVar12;
            puVar12 = puVar12 + (uint)bVar17 * -2 + 1;
            puVar16 = puVar16 + (uint)bVar17 * -2 + 1;
          }
          *(undefined2 *)puVar16 = *(undefined2 *)puVar12;
        }
      }
      else {
        if (7 < param_1) goto LAB_00025f08;
        _Var10 = _Stack_8c;
        if (dword_c695a == 0) {
          _Var10 = local_90;
        }
        lseek(local_30,_Var10,0);
        read(local_30,&uStack_84,0x2f);
        if (dword_c6956 == 0) {
          uVar8 = CONCAT22(uStack_84._2_2_,(undefined2)uStack_84);
        }
        else {
          uVar8 = CONCAT22(uStack_70,uStack_72);
        }
        if (((uVar8 & 0xffff) == 0) ||
           (((param_1 == 5 || (param_1 == 7)) &&
            ((auStack_288[_local_b9 >> 8 & 0xff] == 0 ||
             ((int)((uVar8 & 0xffff) * 100) / (int)auStack_288[_local_b9 >> 8 & 0xff] < 0x50))))))
        goto LAB_00025f08;
        puVar12 = &uStack_84;
        puVar16 = (undefined4 *)(dword_dd110 + local_34 * 0x2f);
        for (iVar5 = 0xb; iVar5 != 0; iVar5 = iVar5 + -1) {
          *puVar16 = *puVar12;
          puVar12 = puVar12 + (uint)bVar17 * -2 + 1;
          puVar16 = puVar16 + (uint)bVar17 * -2 + 1;
        }
        *(undefined2 *)puVar16 = *(undefined2 *)puVar12;
        *(undefined *)((int)puVar16 + (uint)bVar17 * -4 + 2) =
             *(undefined *)((int)puVar12 + (uint)bVar17 * -4 + 2);
        if (param_1 == 7) {
          uStack_1c = uStack_64;
          if (dword_c6956 == 0) {
            uStack_1c = uStack_76;
          }
          uStack_1c = uStack_1c & 0xffff;
          if (uStack_1c == 0) {
            *(undefined4 *)(dword_dd118 + local_34 * 4) = 0;
          }
          else {
            uVar1 = uStack_70;
            if (dword_c6956 == 0) {
              uVar1 = uStack_84._2_2_;
            }
            local_20 = (uint)uVar1;
            *(uint *)(dword_dd118 + local_34 * 4) = ((uint)uVar1 * 1000 + uStack_1c / 2) / uStack_1c
            ;
          }
        }
        if ((0x13 < local_34) && (iVar5 = (*(code *)(&funcptr_c6be8)[param_1])(), -1 < iVar5))
        goto LAB_00025f08;
        if (local_34 < 0x14) {
          puVar12 = (undefined4 *)(local_b9 + 1);
          puVar16 = (undefined4 *)(dword_dd11c + local_34 * 0x34);
          for (iVar5 = 0xd; iVar5 != 0; iVar5 = iVar5 + -1) {
            *puVar16 = *puVar12;
            puVar12 = puVar12 + (uint)bVar17 * -2 + 1;
            puVar16 = puVar16 + (uint)bVar17 * -2 + 1;
          }
          auStack_1cc[local_34] = local_34;
          local_34 = local_34 + 1;
        }
        else {
          uStack_1c = (&local_1d0)[local_34];
          puVar12 = (undefined4 *)(local_b9 + 1);
          puVar16 = (undefined4 *)(dword_dd11c + uStack_1c * 0x34);
          for (iVar5 = 0xd; iVar5 != 0; iVar5 = iVar5 + -1) {
            *puVar16 = *puVar12;
            puVar12 = puVar12 + (uint)bVar17 * -2 + 1;
            puVar16 = puVar16 + (uint)bVar17 * -2 + 1;
          }
          puVar12 = &uStack_84;
          puVar16 = (undefined4 *)(dword_dd110 + uStack_1c * 0x2f);
          for (iVar5 = 0xb; iVar5 != 0; iVar5 = iVar5 + -1) {
            *puVar16 = *puVar12;
            puVar12 = puVar12 + (uint)bVar17 * -2 + 1;
            puVar16 = puVar16 + (uint)bVar17 * -2 + 1;
          }
          *(undefined2 *)puVar16 = *(undefined2 *)puVar12;
          *(undefined *)((int)puVar16 + (uint)bVar17 * -4 + 2) =
               *(undefined *)((int)puVar12 + (uint)bVar17 * -4 + 2);
          if (param_1 == 7) {
            *(undefined4 *)(dword_dd118 + uStack_1c * 4) =
                 *(undefined4 *)(dword_dd118 + local_34 * 4);
          }
        }
      }
      qsort(auStack_1cc,local_34,4);
    }
  } while( true );
  _close(local_30);
  _close(CONCAT22(uStack_2a,local_2c));
  uVar2 = font_main;
  uVar6 = font_kaufm;
  setdefaultscreen();
  puVar11 = install_path;
  if (byte_ed858 != '\x01') {
    puVar11 = (undefined *)0x0;
  }
  make_path(auStack_54,puVar11,(&off_c68e4)[dword_c6956],0);
  dword_dd104 = loadshapes(auStack_54,0);
  dword_dd100 = locateshape(dword_dd104,&aBkgd_c693b);
  setclip(0,0x280,0x13,0x1e0);
  drawshape_remap_home(dword_dd100);
  setclip(0,0x280,0,0x1e0);
  freemem(dword_dd104);
  puVar11 = install_path;
  if (byte_ed908 != '\x01') {
    puVar11 = (undefined *)0x0;
  }
  make_path(auStack_54,puVar11,aPstatbar_c1231,0);
  dword_dd104 = loadshapes(auStack_54,0);
  dword_dd100 = locateshape(dword_dd104,&aPst2_c123a);
  drawshape_remap(dword_dd100,0,0x1c);
  freemem(dword_dd104);
  getfontstate(auStack_130);
  setfont(uVar6);
  text_capture_begin();
  set_text_colors(0x40,0x43);
  stats_source_title(auStack_220,(&off_c6c14)[param_1]);
  iVar5 = textwidth(auStack_220);
  print_outlined(300 - (iVar5 >> 1),0x31,auStack_220);
  setfont(uVar2);
  if (local_34 == 0) {
    setfont(uVar6);
    print_centered_shadow(0xeb,aStatsUnavailable_c123f);
    setfont(uVar2);
    iVar5 = CONCAT22(local_28._2_2_,(short)local_28);
  }
  else {
    local_28._0_2_ = 0x5c;
    local_28._2_2_ = 0;
    iVar5 = CONCAT22(0x5c,uStack_2a) >> 0x10;
    print_text_at(10,iVar5,&aPOS);
    print_text_at(0x32,iVar5,&aNO);
    print_text_at(0x50,iVar5,aPLAYER);
    print_text_at(0xfa,iVar5,&aTEAM);
    print_text_at(0x172,iVar5,&aGP_c1264);
    print_text_at(0x19a,iVar5,(&off_c6c40)[param_1 * 5]);
    print_text_at(0x1cc,iVar5,(&off_c6c44)[param_1 * 5]);
    print_text_at(500,iVar5,(&off_c6c48)[param_1 * 5]);
    if ((param_1 != 9) || (dword_c6956 != 1)) {
      print_text_at(0x21c,(int)(short)local_28,(&off_c6c4c)[param_1 * 5]);
    }
    print_text_at(0x24e,(int)(short)local_28,(&off_c6c50)[param_1 * 5]);
    iVar5 = CONCAT22(local_28._2_2_,(short)local_28) + 0x10;
    local_28._0_2_ = (short)iVar5;
    local_28._2_2_ = (undefined2)((uint)iVar5 >> 0x10);
    for (local_20 = 0; (int)local_20 < local_34; local_20 = local_20 + 1) {
      uStack_1c = auStack_1cc[local_20];
      puVar12 = (undefined4 *)(dword_dd11c + uStack_1c * 0x34);
      puVar16 = (undefined4 *)(local_b9 + 1);
      local_28 = iVar5;
      for (iVar9 = 0xd; iVar9 != 0; iVar9 = iVar9 + -1) {
        *puVar16 = *puVar12;
        puVar12 = puVar12 + (uint)bVar17 * -2 + 1;
        puVar16 = puVar16 + (uint)bVar17 * -2 + 1;
      }
      sprintf((char *)&unk_dd0d8,(char *)&aC_c1267,(int)_local_b9 >> 0x18);
      iVar5 = (int)(short)local_28;
      print_text_at(10,iVar5);
      if (bStack_b7 < 100) {
        print_textf(0x32,iVar5,&a2d,bStack_b7);
      }
      format_team_name(&unk_dd0d8,auStack_b5,auStack_a5);
      iVar9 = (int)(short)local_28;
      print_text_at(0x50,iVar9,&unk_dd0d8);
      make_path(auStack_54,&unk_c65d4,off_c68f4,0);
      iVar5 = c_open(auStack_54,0x200);
      lseek(iVar5,(_local_b9 >> 8 & 0xff) * 0x4c,0);
      read(iVar5,auStack_17c,0x27);
      _close(iVar5);
      print_text_at(0xfa,iVar9,auStack_162);
      sVar4 = (short)local_28;
      if (param_1 < 8) {
        if (dword_c6956 == 0) {
          piVar15 = (int *)(dword_dd110 + uStack_1c * 0x2f);
        }
        else {
          piVar15 = (int *)(uStack_1c * 0x2f + dword_dd110 + 0x12);
        }
        iVar5 = (int)(short)local_28;
        local_24 = piVar15;
        print_textf(0x172,iVar5,&a2d,(int)*(short *)piVar15);
        print_textf(0x19a,iVar5,&a3d,*piVar15 >> 0x10);
        print_textf(0x1cc,iVar5,&a3d,*(int *)((int)piVar15 + 2) >> 0x10);
        iVar5 = piVar15[1];
        puVar12 = &a3d;
        uVar6 = 500;
      }
      else {
        if (dword_c6956 == 0) {
          unaff_EBP = (int *)(dword_dd114 + uStack_1c * 0x36);
        }
        else {
          unaff_EBP = (int *)(uStack_1c * 0x36 + dword_dd114 + 0x16);
        }
        print_textf(0x172,(int)(short)local_28,&a2d,(int)*(short *)unaff_EBP);
        iVar5 = *(int *)((int)unaff_EBP + 10);
        puVar12 = &a4d;
        uVar6 = 0x19a;
      }
      print_textf(uVar6,(int)sVar4,puVar12,iVar5 >> 0x10);
      sVar4 = (short)local_28;
      switch(param_1) {
      default:
        goto switchD_00026732_caseD_0;
      case 3:
        iVar5 = *(int *)((int)local_24 + 6) >> 0x10;
        pcVar13 = (char *)&a2d;
        break;
      case 4:
        iVar5 = local_24[2];
        goto LAB_00026765;
      case 5:
        iVar5 = *(int *)((int)local_24 + 0xe) >> 0x10;
        pcVar13 = (char *)&a4d;
        break;
      case 6:
        iVar5 = *(int *)((int)local_24 + 10);
LAB_00026765:
        iVar5 = iVar5 >> 0x10;
        pcVar13 = (char *)&a3d;
        break;
      case 7:
        print_textf(0x21c,(int)(short)local_28,&a5d,local_24[3] >> 0x10);
        piVar15 = (int *)(uStack_1c * 4 + dword_dd118);
        iVar5 = (int)(short)((longlong)*piVar15 % 10);
        iVar9 = (int)(short)((longlong)*piVar15 / 10);
        uVar6 = 0x24e;
        puVar14 = a3d1d;
        goto LAB_0002680c;
      case 8:
        print_textf(0x1cc,(int)(short)local_28,&a3d,unaff_EBP[3] >> 0x10);
        iVar5 = (int)(short)((ulonglong)(longlong)(int)(uint)*(ushort *)(unaff_EBP + 4) % 100);
        iVar9 = (int)(short)((ulonglong)(longlong)(int)(uint)*(ushort *)(unaff_EBP + 4) / 100);
        puVar14 = a2d22d;
        uVar6 = 500;
LAB_0002680c:
        print_textf2(uVar6,(int)sVar4,puVar14,iVar9,iVar5);
        goto switchD_00026732_caseD_0;
      case 9:
        iVar5 = (int)(short)local_28;
        print_textf(0x1cc,iVar5,&a2d,*unaff_EBP >> 0x10);
        print_textf(500,iVar5,&a2d,*(int *)((int)unaff_EBP + 2) >> 0x10);
        if (dword_c6956 == 0) {
          iVar5 = unaff_EBP[1] >> 0x10;
          pcVar13 = (char *)&a2d;
          break;
        }
        goto switchD_00026732_caseD_0;
      case 10:
        iVar5 = (int)(short)local_28;
        print_textf(0x1cc,iVar5,&a3d,unaff_EBP[3] >> 0x10);
        print_textf(500,iVar5,&a4d,unaff_EBP[4] >> 0x10);
        uVar1 = *(ushort *)(unaff_EBP + 5);
        if (999 < uVar1) {
          iVar5 = (int)(short)((ulonglong)(longlong)(int)(uint)uVar1 % 1000);
          iVar9 = (int)(short)((ulonglong)(longlong)(int)(uint)uVar1 / 1000);
          puVar14 = a1d03d;
          uVar6 = 0x21c;
          goto LAB_0002680c;
        }
        iVar5 = (int)(short)(*(ushort *)(unaff_EBP + 5) % 1000);
        pcVar13 = a03d;
      }
      print_textf(0x21c,(int)sVar4,pcVar13,iVar5);
switchD_00026732_caseD_0:
      iVar5 = local_28 + 0xd;
      local_28._0_2_ = (short)iVar5;
      local_28._2_2_ = (undefined2)((uint)iVar5 >> 0x10);
    }
  }
  local_28 = iVar5;
  text_capture_stop();
  setfontstate(auStack_130);
  if (param_1 == 7) {
    freemem(dword_dd118);
  }
  iVar5 = dword_dd114;
  if (param_1 < 8) {
    iVar5 = dword_dd110;
  }
  freemem(iVar5);
  freemem(dword_dd11c);
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// cmp_standings @ 0x269fe [__watcall]
// ================================================================================================

int __watcall cmp_standings(int *param_1,int *unaff_EDX)

{
  int iVar1;
  int iVar2;
  undefined4 local_20;
  
  __CHK(0x2c);
  iVar1 = dword_dd10c + *param_1 * 0x1a;
  iVar2 = dword_dd10c + *unaff_EDX * 0x1a;
  if (*(char *)(iVar2 + 0xd) == *(char *)(iVar1 + 0xd)) {
    if (*(short *)(iVar2 + 0x16) == *(short *)(iVar1 + 0x16)) {
      if (*(char *)(iVar2 + 0xe) == *(char *)(iVar1 + 0xe)) {
        if (*(char *)(iVar2 + 0xf) == *(char *)(iVar1 + 0xf)) {
          if (*(short *)(iVar2 + 0x12) == *(short *)(iVar1 + 0x12)) {
            if (*(short *)(iVar2 + 0x14) == *(short *)(iVar1 + 0x14)) {
              local_20 = *param_1 - *unaff_EDX;
            }
            else {
              local_20 = (uint)*(ushort *)(iVar1 + 0x14) - (uint)*(ushort *)(iVar2 + 0x14);
            }
          }
          else {
            local_20 = (uint)*(ushort *)(iVar2 + 0x12) - (uint)*(ushort *)(iVar1 + 0x12);
          }
        }
        else {
          local_20 = (uint)*(byte *)(iVar2 + 0xf) - (uint)*(byte *)(iVar1 + 0xf);
        }
      }
      else {
        local_20 = (uint)*(byte *)(iVar1 + 0xe) - (uint)*(byte *)(iVar2 + 0xe);
      }
    }
    else {
      local_20 = (uint)*(ushort *)(iVar2 + 0x16) - (uint)*(ushort *)(iVar1 + 0x16);
    }
  }
  else {
    local_20 = (uint)*(byte *)(iVar1 + 0xd) - (uint)*(byte *)(iVar2 + 0xd);
  }
  return local_20;
}


// ================================================================================================
// menu_page_c @ 0x26b5a [__watcall]
// ================================================================================================

undefined4 __watcall menu_page_c(int param_1,int unaff_EDX,uint *unaff_EBX)

{
  undefined4 uStackY_2c;
  short sStackY_1c;
  
  __CHK(0x3c);
  param_1 = param_1 + 4;
  if (dword_c6956 == 0) {
    *unaff_EBX = 0;
    if (unaff_EDX < 0xa5) {
      uStackY_2c = 0;
    }
    else {
      if (param_1 < 0x140) {
        if (unaff_EDX < 0xf3) {
          *unaff_EBX = (unaff_EDX + -0xa5) / 0xd;
          return 1;
        }
        if (unaff_EDX < 0x14a) {
          return 0;
        }
        if (unaff_EDX < 0x198) {
          *unaff_EBX = (unaff_EDX + -0x14a) / 0xd + 6;
          return 1;
        }
      }
      else {
        if (unaff_EDX < 0x100) {
          *unaff_EBX = (unaff_EDX + -0xa5) / 0xd + 0xc;
          return 1;
        }
        if (unaff_EDX < 0x14a) {
          return 0;
        }
        if (unaff_EDX < 0x1a5) {
          *unaff_EBX = (unaff_EDX + -0x14a) / 0xd + 0x13;
          return 1;
        }
      }
      uStackY_2c = 0;
    }
  }
  else {
    *unaff_EBX = 0;
    if ((unaff_EDX < 0x4b) || (0x68 < unaff_EDX)) {
      if ((unaff_EDX < 0x9a) || (0xb8 < unaff_EDX)) {
        if ((unaff_EDX < 0xe6) || (0x103 < unaff_EDX)) {
          if ((unaff_EDX < 0x134) || (0x151 < unaff_EDX)) {
            if ((unaff_EDX < 0x181) || (0x19e < unaff_EDX)) {
              uStackY_2c = 0;
            }
            else {
              for (sStackY_1c = 0; sStackY_1c < 4; sStackY_1c = sStackY_1c + 1) {
                if ((*(int *)(&unk_c6e22 + sStackY_1c * 2) <= param_1) &&
                   (param_1 <= *(int *)(&unk_c6e22 + sStackY_1c * 2) + 100)) {
                  if (unaff_EDX < 400) {
                    *unaff_EBX = (uint)(byte)(&unk_c6db2)[sStackY_1c * 2];
                  }
                  else {
                    *unaff_EBX = (uint)(byte)(&unk_c6db3)[sStackY_1c * 2];
                  }
                  return 1;
                }
              }
              uStackY_2c = 0;
            }
          }
          else {
            for (sStackY_1c = 0; sStackY_1c < 2; sStackY_1c = sStackY_1c + 1) {
              if ((0x280 - (*(int *)(&unk_c6e32 + (1 - sStackY_1c) * 2) + 100) <= param_1) &&
                 (param_1 <= 0x280 - *(int *)(&unk_c6e32 + (1 - sStackY_1c) * 2))) {
                if (unaff_EDX < 0x143) {
                  *unaff_EBX = (uint)(byte)(&byte_c6daa)[sStackY_1c * 2];
                }
                else {
                  *unaff_EBX = (uint)(byte)(&byte_c6dab)[sStackY_1c * 2];
                }
                return 1;
              }
            }
            uStackY_2c = 0;
          }
        }
        else if ((param_1 < 0x48) || (0xac < param_1)) {
          if ((param_1 < 0x10c) || (0x170 < param_1)) {
            if ((param_1 < 0x1cd) || (0x231 < param_1)) {
              uStackY_2c = 0;
            }
            else {
              if (unaff_EDX < 0xf5) {
                *unaff_EBX = (uint)byte_c6da2;
              }
              else {
                *unaff_EBX = (uint)byte_c6da3;
              }
              uStackY_2c = 1;
            }
          }
          else {
            if (unaff_EDX < 0xf2) {
              *unaff_EBX = (uint)byte_c6d8a;
            }
            else {
              *unaff_EBX = (uint)byte_c6d9a;
            }
            uStackY_2c = 1;
          }
        }
        else {
          if (unaff_EDX < 0xf5) {
            *unaff_EBX = (uint)byte_c6d82;
          }
          else {
            *unaff_EBX = (uint)byte_c6d83;
          }
          uStackY_2c = 1;
        }
      }
      else {
        for (sStackY_1c = 0; sStackY_1c < 2; sStackY_1c = sStackY_1c + 1) {
          if ((*(int *)(&unk_c6e32 + sStackY_1c * 2) <= param_1) &&
             (param_1 <= *(int *)(&unk_c6e32 + sStackY_1c * 2) + 100)) {
            if (unaff_EDX < 0xa9) {
              *unaff_EBX = (uint)(byte)(&byte_c6d7a)[sStackY_1c * 2];
            }
            else {
              *unaff_EBX = (uint)(byte)(&byte_c6d7b)[sStackY_1c * 2];
            }
            return 1;
          }
        }
        uStackY_2c = 0;
      }
    }
    else {
      for (sStackY_1c = 0; sStackY_1c < 4; sStackY_1c = sStackY_1c + 1) {
        if ((*(int *)(&unk_c6e22 + sStackY_1c * 2) <= param_1) &&
           (param_1 <= *(int *)(&unk_c6e22 + sStackY_1c * 2) + 100)) {
          if (unaff_EDX < 0x5a) {
            *unaff_EBX = (uint)(byte)(&byte_c6d72)[sStackY_1c * 2];
          }
          else {
            *unaff_EBX = (uint)(byte)(&unk_c6d73)[sStackY_1c * 2];
          }
          return 1;
        }
      }
      uStackY_2c = 0;
    }
  }
  return uStackY_2c;
}


// ================================================================================================
// standings_table @ 0x27080 [__watcall]
// ================================================================================================

undefined4 __watcall standings_table(int param_1,int unaff_EDX)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  uint uVar6;
  undefined4 *puVar7;
  byte bVar8;
  undefined *local_454;
  undefined *local_448;
  int iStack_43c;
  undefined auStack_150 [84];
  undefined auStack_fc [64];
  undefined auStack_bc [26];
  undefined4 auStack_a2 [3];
  byte bStack_94;
  byte bStack_93;
  undefined local_92;
  byte bStack_91;
  short sStack_90;
  short local_8e;
  ushort local_8c;
  ushort uStack_8a;
  undefined auStack_88 [32];
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined2 local_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined2 local_54;
  undefined2 uStack_3a;
  short local_38;
  short local_34;
  int iStack_2c;
  
  bVar8 = 0;
  __CHK(0x468);
  uVar2 = font_main;
  uVar1 = font_kaufm;
  uStack_68 = 0x150014;
  uStack_64 = 0x170016;
  local_60 = 0x18;
  uStack_5c = 0x310032;
  uStack_58 = 0x2f0030;
  local_54 = 0x2e;
  funcptr_cf6a3 = menu_show_team_roster;
  make_path(auStack_88,&unk_c65d4,(&off_c68f4)[dword_c695a],0);
  iVar3 = c_open(auStack_88,0x200);
  if (dword_c695a == 0) {
    iStack_43c = 0x4c;
  }
  else {
    iStack_43c = 0x2e8;
  }
  for (iStack_2c = 0; iStack_2c < 0x1a; iStack_2c = iStack_2c + 1) {
    lseek(iVar3,iStack_43c * iStack_2c,0);
    read(iVar3,auStack_bc,0x34);
    local_8c = (ushort)bStack_93 * 2 + (ushort)bStack_91;
    if (bStack_94 == 0) {
      uStack_8a = 0;
    }
    else {
      uStack_8a = (ushort)(((uint)bStack_94 + (uint)local_8c * 1000) / ((uint)bStack_94 * 2));
    }
    puVar5 = auStack_a2;
    puVar7 = (undefined4 *)(param_1 + iStack_2c * 0x1a);
    for (iVar4 = 6; iVar4 != 0; iVar4 = iVar4 + -1) {
      *puVar7 = *puVar5;
      puVar5 = puVar5 + (uint)bVar8 * -2 + 1;
      puVar7 = puVar7 + (uint)bVar8 * -2 + 1;
    }
    *(undefined2 *)puVar7 = *(undefined2 *)puVar5;
    *(int *)(iStack_2c * 4 + unaff_EDX) = iStack_2c;
  }
  _close(iVar3);
  qsort(unaff_EDX,0x1a,4,cmp_standings);
  setdefaultscreen();
  if (byte_ed858 == '\x01') {
    local_448 = install_path;
  }
  else {
    local_448 = (undefined *)0x0;
  }
  make_path(auStack_88,local_448,(&off_c68e4)[dword_c6956],0);
  dword_dd104 = loadshapes(auStack_88,0);
  dword_dd100 = locateshape(dword_dd104,&aBkgd_c693b);
  setclip(0,0x280,0x13,0x1e0);
  drawshape_remap_home(dword_dd100);
  setclip(0,0x280,0,0x1e0);
  freemem(dword_dd104);
  if (byte_ed908 == '\x01') {
    local_454 = install_path;
  }
  else {
    local_454 = (undefined *)0x0;
  }
  make_path(auStack_88,local_454,aPstatbar_c1282,0);
  dword_dd104 = loadshapes(auStack_88,0);
  dword_dd100 = locateshape(dword_dd104,&aPst2_c128b);
  drawshape_remap(dword_dd100,0,0x1c);
  freemem(dword_dd104);
  text_capture_begin();
  getfontstate(auStack_fc);
  setfont(uVar1);
  set_text_colors(0x40,0x43);
  stats_source_title(auStack_150,aStandings);
  iVar3 = textwidth(auStack_150);
  print_outlined(300 - (iVar3 >> 1),0x31,auStack_150);
  iVar3 = textwidth(aWestern);
  print_text_at((int)(short)(0xa0 - (short)(iVar3 >> 1)),CONCAT22(0x50,uStack_3a) >> 0x10,aWestern);
  iVar3 = textwidth(aConference);
  print_text_at((int)(short)(0xa0 - (short)(iVar3 >> 1)),0x60,aConference);
  iVar3 = textwidth(aEastern);
  print_text_at((int)(short)(0x1e0 - (short)(iVar3 >> 1)),CONCAT22(0x50,uStack_3a) >> 0x10,aEastern)
  ;
  iVar3 = textwidth(aConference);
  print_text_at((int)(short)(0x1e0 - (short)(iVar3 >> 1)),0x60,aConference);
  setfont(uVar2);
  set_text_colors(0x40,0x43);
  iVar3 = 0xa7;
  uVar6 = 0xffffffff;
  for (iStack_2c = 0; iStack_2c < 0x1a; iStack_2c = iStack_2c + 1) {
    puVar5 = (undefined4 *)(param_1 + *(int *)(iStack_2c * 4 + unaff_EDX) * 0x1a);
    if (*(byte *)((int)puVar5 + 0xd) != uVar6) {
      uVar6 = (uint)*(byte *)((int)puVar5 + 0xd) % 4;
      local_34 = (short)*(undefined4 *)(&unk_c6e3a + uVar6 * 4);
      iVar3 = *(int *)(&unk_c6e4a + uVar6 * 4);
      local_38 = (short)iVar3;
      print_text_at((int)local_34,(int)local_38,(&off_c68bc)[uVar6]);
      local_38 = (short)(iVar3 + 0x12);
      print_text_at((int)local_34,(int)local_38,&aTeam);
      print_text_at((int)(short)(local_34 + 100),(int)local_38,&aGP_c12bb);
      print_text_at((int)(short)(local_34 + 0x78),(int)local_38,&aW_c12be);
      print_text_at((int)(short)(local_34 + 0x8c),(int)local_38,&aL_c12c1);
      print_text_at((int)(short)(local_34 + 0xa0),(int)local_38,&aT_c12c4);
      print_text_at((int)(short)(local_34 + 0xb4),(int)local_38,&aGF_c12c7);
      print_text_at((int)(short)(local_34 + 0xd2),(int)local_38,&aGA_c12cb);
      print_text_at((int)(short)(local_34 + 0xf0),(int)local_38,&aP_c12cf);
      print_text_at((int)(short)(local_34 + 0x10e),(int)local_38,aPct_c12d3);
      iVar3 = iVar3 + 0x25;
    }
    local_38 = (short)iVar3;
    if ((dword_c695a != 0) || (*(char *)((int)puVar5 + 0xe) != '\0')) {
      puVar7 = auStack_a2;
      for (iVar4 = 6; iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar7 = *puVar5;
        puVar5 = puVar5 + (uint)bVar8 * -2 + 1;
        puVar7 = puVar7 + (uint)bVar8 * -2 + 1;
      }
      *(undefined2 *)puVar7 = *(undefined2 *)puVar5;
      print_text_at((int)local_34,(int)local_38,auStack_a2);
      print_textf((int)(short)(local_34 + 100),(int)local_38,&a2d,bStack_94);
      print_textf((int)(short)(local_34 + 0x78),(int)local_38,&a2d,bStack_93);
      print_textf((int)(short)(local_34 + 0x8c),(int)local_38,&a2d,local_92);
      print_textf((int)(short)(local_34 + 0xa0),(int)local_38,&a2d,bStack_91);
      print_textf((int)(short)(local_34 + 0xb4),(int)local_38,&a3d,(int)sStack_90);
      print_textf((int)(short)(local_34 + 0xd2),(int)local_38,&a3d,(int)local_8e);
      print_textf((int)(short)(local_34 + 0xf0),(int)local_38,&a3d,(int)(short)local_8c);
      if (uStack_8a < 1000) {
        print_textf((int)(short)(local_34 + 0x10e),(int)local_38,a03d,
                  (short)((ulonglong)(longlong)(int)(uint)uStack_8a % 1000));
      }
      else {
        print_textf2((int)(short)(local_34 + 0x10e),(int)local_38,a1d03d,
                  (short)((ulonglong)(longlong)(int)(uint)uStack_8a / 1000),
                  (short)((ulonglong)(longlong)(int)(uint)uStack_8a % 1000));
      }
      iVar3 = iVar3 + 0xd;
    }
  }
  text_capture_stop();
  setfontstate(auStack_fc);
  return 0;
}


// ================================================================================================
// standings_highlight_row @ 0x2785f [__watcall]
// ================================================================================================

void __watcall standings_highlight_row(uint *param_1)

{
  ushort uVar1;
  short sVar2;
  int iVar3;
  undefined2 local_32;
  undefined4 local_2e;
  undefined2 uStack_28;
  undefined2 uStack_22;
  byte bStack_20;
  undefined uStack_1f;
  
  __CHK(0x4c);
  local_32 = (undefined2)((uint)param_1 >> 0x10);
  bStack_20 = 0;
  uStack_1f = 0;
  while( true ) {
    if (7 < CONCAT11(uStack_1f,bStack_20)) {
      uVar1 = 0;
      while( true ) {
        uStack_1f = (undefined)(uVar1 >> 8);
        bStack_20 = (byte)uVar1;
        if (3 < (short)uVar1) {
          sVar2 = 0;
          while( true ) {
            uStack_1f = (undefined)((ushort)sVar2 >> 8);
            bStack_20 = (byte)sVar2;
            if (1 < sVar2) {
              if ((uint)byte_c6d8a == *param_1) {
                fillrect2_clipped(0x10a,0xe2,0x5c,0xd,0x80);
              }
              else if ((uint)byte_c6d9a == *param_1) {
                fillrect2_clipped(0x10a,0xf2,0x5c,0xd,0x80);
              }
              return;
            }
            if ((uint)(byte)(&byte_c6d82)[CONCAT13(uStack_1f,CONCAT12(bStack_20,uStack_22)) >> 0x10]
                == *param_1) break;
            if ((uint)(byte)(&byte_c6da2)[CONCAT13(uStack_1f,CONCAT12(bStack_20,uStack_22)) >> 0x10]
                == *param_1) {
              if (sVar2 == 0) {
                uStack_28 = 0xe6;
              }
              else {
                uStack_28 = 0xf6;
              }
              fillrect2_clipped(0x1c5,uStack_28,100,0xd,0x80);
              return;
            }
            sVar2 = sVar2 + 1;
          }
          if (sVar2 == 0) {
            uStack_28 = 0xe6;
          }
          else {
            uStack_28 = 0xf6;
          }
          fillrect2_clipped(0x47,uStack_28,100,0xd,0x80);
          return;
        }
        if ((uint)(byte)(&byte_c6d7a)[CONCAT13(uStack_1f,CONCAT12(bStack_20,uStack_22)) >> 0x10] ==
            *param_1) {
          if ((uVar1 & 1) == 0) {
            uStack_28 = 0x99;
          }
          else {
            uStack_28 = 0xa9;
          }
          local_2e = CONCAT22(100,(undefined2)local_2e);
          fillrect2_clipped((int)(short)((&unk_c6e32)
                                 [(CONCAT13(uStack_1f,CONCAT12(bStack_20,uStack_22)) >> 0x11) * 2] +
                                -1),uStack_28,local_2e >> 0x10,CONCAT22(0xd,local_32) >> 0x10,0x80);
          return;
        }
        if ((uint)(byte)(&byte_c6daa)[CONCAT13(uStack_1f,CONCAT12(bStack_20,uStack_22)) >> 0x10] ==
            *param_1) break;
        uVar1 = uVar1 + 1;
      }
      if ((uVar1 & 1) == 0) {
        uStack_28 = 0x133;
      }
      else {
        uStack_28 = 0x143;
      }
      local_2e = CONCAT22(100,(undefined2)local_2e);
      fillrect2_clipped((int)(short)(0x27f - ((&unk_c6e32)
                                      [(1 - (CONCAT13(uStack_1f,CONCAT12(bStack_20,uStack_22)) >>
                                            0x11)) * 2] + 100)),uStack_28,local_2e >> 0x10,
                CONCAT22(0xd,local_32) >> 0x10,0x80);
      return;
    }
    if ((uint)(byte)(&byte_c6d72)[CONCAT13(uStack_1f,CONCAT12(bStack_20,uStack_22)) >> 0x10] ==
        *param_1) {
      if ((bStack_20 & 1) == 0) {
        uStack_28 = 0x4a;
      }
      else {
        uStack_28 = 0x5a;
      }
      local_2e = CONCAT22(100,(undefined2)local_2e);
      fillrect2_clipped((int)(short)((&unk_c6e22)
                             [(CONCAT13(uStack_1f,CONCAT12(bStack_20,uStack_22)) >> 0x11) * 2] + -1)
                ,uStack_28,local_2e >> 0x10,CONCAT22(0xd,local_32) >> 0x10,0x80);
      return;
    }
    if ((uint)(byte)(&unk_c6db2)[CONCAT13(uStack_1f,CONCAT12(bStack_20,uStack_22)) >> 0x10] ==
        *param_1) break;
    iVar3 = CONCAT11(uStack_1f,bStack_20) + 1;
    bStack_20 = (byte)iVar3;
    uStack_1f = (undefined)((uint)iVar3 >> 8);
  }
  if ((bStack_20 & 1) == 0) {
    uStack_28 = 0x180;
  }
  else {
    uStack_28 = 400;
  }
  local_2e = CONCAT22(100,(undefined2)local_2e);
  fillrect2_clipped((int)(short)((&unk_c6e22)
                         [(CONCAT13(uStack_1f,CONCAT12(bStack_20,uStack_22)) >> 0x11) * 2] + -1),
            uStack_28,local_2e >> 0x10,CONCAT22(0xd,local_32) >> 0x10,0x80);
  return;
}


// ================================================================================================
// standings_move_highlight @ 0x27bc3 [__watcall]
// ================================================================================================

void __watcall standings_move_highlight(int *param_1,int *unaff_EDX)

{
  __CHK(0x20);
  if ((((param_1 != (int *)0x0) && ((int)(&dword_dc7b8)[*param_1] < 0x1a)) &&
      (standings_highlight_row(param_1), unaff_EDX != (int *)0x0)) && ((int)(&dword_dc7b8)[*unaff_EDX] < 0x1a)) {
    standings_highlight_row(unaff_EDX);
    *param_1 = *unaff_EDX;
  }
  return;
}


// ================================================================================================
// playoff_bracket_build @ 0x27c34 [__watcall]
// ================================================================================================

void __watcall playoff_bracket_build(int param_1,int unaff_EDX,int unaff_EBX)

{
  int iVar1;
  byte abStack_4c [32];
  int iStack_20;
  int local_18;
  int iStack_14;
  
  __CHK(0x54);
  if (unaff_EBX == 0) {
    load_lssched_db(&local_18);
  }
  else {
    load_schedule_file(&local_18);
  }
  iVar1 = local_18;
  iStack_14 = local_18 + 0x199a;
  for (iStack_20 = 0; iStack_20 < 0x1c; iStack_20 = iStack_20 + 1) {
    abStack_4c[iStack_20] = 0;
  }
  for (iStack_20 = 0; iStack_20 < 0x38; iStack_20 = iStack_20 + 1) {
    if ((((*(char *)(iStack_14 + 2) != -1) && (*(char *)(iStack_14 + 3) != -1)) &&
        (*(char *)(iStack_14 + 4) != -1)) && (*(char *)(iStack_14 + 5) != -1)) {
      if (*(byte *)(iStack_14 + 5) < *(byte *)(iStack_14 + 4)) {
        abStack_4c[*(byte *)(iStack_14 + 2)] = abStack_4c[*(byte *)(iStack_14 + 2)] + 1;
      }
      else {
        abStack_4c[*(byte *)(iStack_14 + 3)] = abStack_4c[*(byte *)(iStack_14 + 3)] + 1;
      }
    }
    iStack_14 = iStack_14 + 6;
  }
  for (iStack_20 = 0; iStack_20 < 0x10; iStack_20 = iStack_20 + 1) {
    *(uint *)(iStack_20 * 4 + unaff_EDX) = (uint)abStack_4c[*(int *)(iStack_20 * 4 + param_1)];
  }
  for (iStack_20 = 0; iStack_20 < 0x1a; iStack_20 = iStack_20 + 1) {
    abStack_4c[iStack_20] = 0;
  }
  for (iStack_20 = 0; iStack_20 < 0x1c; iStack_20 = iStack_20 + 1) {
    if (((*(char *)(iStack_14 + 2) != -1) && (*(char *)(iStack_14 + 3) != -1)) &&
       ((*(char *)(iStack_14 + 4) != -1 && (*(char *)(iStack_14 + 5) != -1)))) {
      if (*(byte *)(iStack_14 + 5) < *(byte *)(iStack_14 + 4)) {
        abStack_4c[*(byte *)(iStack_14 + 2)] = abStack_4c[*(byte *)(iStack_14 + 2)] + 1;
      }
      else {
        abStack_4c[*(byte *)(iStack_14 + 3)] = abStack_4c[*(byte *)(iStack_14 + 3)] + 1;
      }
    }
    iStack_14 = iStack_14 + 6;
  }
  for (iStack_20 = 0x10; iStack_20 < 0x18; iStack_20 = iStack_20 + 1) {
    *(uint *)(iStack_20 * 4 + unaff_EDX) = (uint)abStack_4c[*(int *)(iStack_20 * 4 + param_1)];
  }
  for (iStack_20 = 0; iStack_20 < 0x1a; iStack_20 = iStack_20 + 1) {
    abStack_4c[iStack_20] = 0;
  }
  for (iStack_20 = 0; iStack_20 < 0xe; iStack_20 = iStack_20 + 1) {
    if (((*(char *)(iStack_14 + 2) != -1) && (*(char *)(iStack_14 + 3) != -1)) &&
       ((*(char *)(iStack_14 + 4) != -1 && (*(char *)(iStack_14 + 5) != -1)))) {
      if (*(byte *)(iStack_14 + 5) < *(byte *)(iStack_14 + 4)) {
        abStack_4c[*(byte *)(iStack_14 + 2)] = abStack_4c[*(byte *)(iStack_14 + 2)] + 1;
      }
      else {
        abStack_4c[*(byte *)(iStack_14 + 3)] = abStack_4c[*(byte *)(iStack_14 + 3)] + 1;
      }
    }
    iStack_14 = iStack_14 + 6;
  }
  for (iStack_20 = 0x18; iStack_20 < 0x1c; iStack_20 = iStack_20 + 1) {
    *(uint *)(iStack_20 * 4 + unaff_EDX) = (uint)abStack_4c[*(int *)(iStack_20 * 4 + param_1)];
  }
  for (iStack_20 = 0; iStack_20 < 0x1a; iStack_20 = iStack_20 + 1) {
    abStack_4c[iStack_20] = 0;
  }
  for (iStack_20 = 0; iStack_20 < 7; iStack_20 = iStack_20 + 1) {
    if ((((*(char *)(iStack_14 + 2) != -1) && (*(char *)(iStack_14 + 3) != -1)) &&
        (*(char *)(iStack_14 + 4) != -1)) && (*(char *)(iStack_14 + 5) != -1)) {
      if (*(byte *)(iStack_14 + 5) < *(byte *)(iStack_14 + 4)) {
        abStack_4c[*(byte *)(iStack_14 + 2)] = abStack_4c[*(byte *)(iStack_14 + 2)] + 1;
      }
      else {
        abStack_4c[*(byte *)(iStack_14 + 3)] = abStack_4c[*(byte *)(iStack_14 + 3)] + 1;
      }
    }
    iStack_14 = iStack_14 + 6;
  }
  for (iStack_20 = 0x1c; iStack_20 < 0x1e; iStack_20 = iStack_20 + 1) {
    *(uint *)(iStack_20 * 4 + unaff_EDX) = (uint)abStack_4c[*(int *)(iStack_20 * 4 + param_1)];
  }
  local_18 = local_18 + 2;
  freemem(iVar1);
  return;
}


// ================================================================================================
// standings_screen @ 0x27f9c [__watcall]
// ================================================================================================

/* WARNING: Type propagation algorithm not settling */

void __watcall standings_screen(void)

{
  undefined uVar1;
  byte bVar2;
  int iVar3;
  char *pcVar4;
  char *pcVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  byte bVar8;
  char acStackY_24d2 [1018];
  undefined2 auStackY_20d8 [1018];
  char *apcStackY_18e4 [1457];
  undefined *local_210;
  char *local_20c;
  undefined4 local_208;
  undefined *local_204;
  char *local_200;
  undefined4 local_1fc;
  undefined *local_1f8;
  char *local_1f4;
  undefined4 local_1f0;
  undefined *local_1ec;
  undefined *local_1e8;
  undefined4 local_1e4;
  undefined4 auStack_1e0 [54];
  undefined4 uStack_108;
  undefined4 uStack_104;
  char acStack_fe [74];
  undefined auStack_b4 [64];
  undefined auStack_74 [32];
  undefined4 local_54;
  undefined2 local_50;
  undefined2 uStack_4e;
  int iStack_4c;
  undefined4 uStack_44;
  undefined4 uStack_3c;
  undefined4 local_30;
  short sStack_2c;
  undefined2 uStack_2a;
  undefined2 uStack_22;
  ushort uStack_20;
  undefined2 uStack_1e;
  
  bVar8 = 0;
  __CHK(0x224);
  local_50 = 0;
  uStack_4e = 0;
  uStack_44 = font_main;
  local_54 = font_kaufm;
  if (dword_dc7b8 == 0x1a) {
    funcptr_cf6a3 = (undefined *)0x0;
  }
  else {
    funcptr_cf6a3 = menu_show_team_roster;
  }
  setdefaultscreen();
  if (dword_c65ac == 0) {
    local_1e4 = 0;
    local_1e8 = (&off_c68e4)[dword_c6956];
    if (byte_ed859 == '\x01') {
      local_1ec = install_path;
    }
    else {
      local_1ec = (undefined *)0x0;
    }
    make_path(auStack_74,local_1ec,local_1e8,0);
    dword_dd104 = loadshapes(auStack_74,0);
    dword_dd100 = locateshape(dword_dd104,&aBkgd_c693b);
    setclip(0,0x280,0x13,0x1e0);
    drawshape_remap_home(dword_dd100);
    setclip(0,0x280,0,0x1e0);
    freemem(dword_dd104);
  }
  else {
    dword_dd100 = locateshape(dword_c65ac,&aBkgd_c693b);
    setclip(0,0x280,0x13,0x1e0);
    drawshape_remap_home(dword_dd100);
    setclip(0,0x280,0,0x1e0);
  }
  if (dword_c6d26 == 1) {
    local_1f0 = 0;
    local_1f4 = aEmbpal_c12d9;
    if (byte_ed85a == '\x01') {
      local_1f8 = install_path;
    }
    else {
      local_1f8 = (undefined *)0x0;
    }
    make_path(auStack_74,local_1f8,aEmbpal_c12d9,0);
    dword_dd104 = loadshapes(auStack_74,0);
    dword_dd100 = locateshape(dword_dd104,&aPal_c12e0);
    if (dword_c6a60 == 1) {
      memcpy(dword_dd120,(void *)(dword_dd100 + 0x10),0x300);
    }
    else {
      setpalette(0,0x100,dword_dd100 + 0x10);
    }
    freemem(dword_dd104);
    dword_c6d26 = 0;
  }
  playoff_bracket_build(&dword_dc7b8,auStack_1e0,0);
  set_text_colors(0x40,0x43);
  if ((&dword_dc7b8)[byte_c6d72] < 0x1a) {
    local_1fc = 0;
    local_200 = aPstatbar_c1282;
    if (byte_ed908 == '\x01') {
      local_204 = install_path;
    }
    else {
      local_204 = (undefined *)0x0;
    }
    make_path(auStack_74,local_204,aPstatbar_c1282,0);
    dword_dd104 = loadshapes(auStack_74,0);
    dword_dd100 = locateshape(dword_dd104,&aRst1);
    drawshape_remap(dword_dd100,0,0x1a);
    dword_dd100 = locateshape(dword_dd104,&aRst2);
    drawshape_remap(dword_dd100,0xf,0x192);
    freemem(dword_dd104);
    local_208 = 0;
    local_20c = aScuparrw;
    if (byte_ed93a == '\x01') {
      local_210 = install_path;
    }
    else {
      local_210 = (undefined *)0x0;
    }
    make_path(auStack_74,local_210,aScuparrw,0);
    dword_dd104 = loadshapes(auStack_74,0);
    text_capture_begin();
    getfontstate(auStack_b4);
    setfont(uStack_44);
    stats_source_title(&uStack_108,aStandings);
    print_centered_shadow(0x16,&uStack_108);
    setfont(local_54);
    uStack_108._0_1_ = aWesternConference_c131a[0];
    uStack_108._1_1_ = aWesternConference_c131a[1];
    uStack_108._2_1_ = aWesternConference_c131a[2];
    uStack_108._3_1_ = aWesternConference_c131a[3];
    puVar6 = (undefined4 *)(&stack0xffffff00 + (uint)bVar8 * -8 + (uint)bVar8 * -8);
    pcVar4 = aWesternConference_c131a + (uint)bVar8 * -8 + (uint)bVar8 * -8 + 8;
    (&uStack_104)[(uint)bVar8 * -2] =
         *(undefined4 *)(aWesternConference_c131a + (uint)bVar8 * -8 + 4);
    puVar7 = puVar6 + (uint)bVar8 * -2 + 1;
    pcVar5 = pcVar4 + ((uint)bVar8 * -2 + 1) * 4;
    *puVar6 = *(undefined4 *)pcVar4;
    *puVar7 = *(undefined4 *)pcVar5;
    *(undefined2 *)(puVar7 + (uint)bVar8 * -2 + 1) =
         *(undefined2 *)(pcVar5 + ((uint)bVar8 * -2 + 1) * 4);
    *(char *)((int)(puVar7 + (uint)bVar8 * -2 + 1) + (uint)bVar8 * -4 + 2) =
         (pcVar5 + ((uint)bVar8 * -2 + 1) * 4)[(uint)bVar8 * -4 + 2];
    iVar3 = textwidth(&uStack_108);
    print_outlined(0x140 - (iVar3 >> 1),0x2f,&uStack_108);
    uStack_108._0_1_ = aEasternConference_c132d[0];
    uStack_108._1_1_ = aEasternConference_c132d[1];
    uStack_108._2_1_ = aEasternConference_c132d[2];
    uStack_108._3_1_ = aEasternConference_c132d[3];
    puVar6 = (undefined4 *)(&stack0xffffff00 + (uint)bVar8 * -8 + (uint)bVar8 * -8);
    pcVar4 = aEasternConference_c132d + (uint)bVar8 * -8 + (uint)bVar8 * -8 + 8;
    (&uStack_104)[(uint)bVar8 * -2] =
         *(undefined4 *)(aEasternConference_c132d + (uint)bVar8 * -8 + 4);
    puVar7 = puVar6 + (uint)bVar8 * -2 + 1;
    pcVar5 = pcVar4 + ((uint)bVar8 * -2 + 1) * 4;
    *puVar6 = *(undefined4 *)pcVar4;
    *puVar7 = *(undefined4 *)pcVar5;
    *(undefined2 *)(puVar7 + (uint)bVar8 * -2 + 1) =
         *(undefined2 *)(pcVar5 + ((uint)bVar8 * -2 + 1) * 4);
    *(char *)((int)(puVar7 + (uint)bVar8 * -2 + 1) + (uint)bVar8 * -4 + 2) =
         (pcVar5 + ((uint)bVar8 * -2 + 1) * 4)[(uint)bVar8 * -4 + 2];
    iVar3 = textwidth(&uStack_108);
    print_outlined(0x140 - (iVar3 >> 1),0x1a7,&uStack_108);
    setfont(uStack_44);
    iVar3 = 0;
    while( true ) {
      uStack_2a = (undefined2)((uint)iVar3 >> 0x10);
      sStack_2c = (short)iVar3;
      if (7 < sStack_2c) break;
      if (sStack_2c < 4) {
        uVar1 = (&byte_c6d72)[sStack_2c * 2];
      }
      else {
        uVar1 = *(undefined *)(0xc6d79 - (sStack_2c * 2 + -8));
      }
      uStack_1e = 0;
      *(int *)(&unk_c6dba + (&dword_dc7b8)[(int)(uint)CONCAT12(uVar1,uStack_22) >> 0x10] * 4) =
           (int)sStack_2c;
      if (sStack_2c < 4) {
        bVar2 = (&unk_c6db2)[sStack_2c * 2];
        local_30 = iVar3;
      }
      else {
        local_30 = 7 - iVar3;
        bVar2 = *(byte *)(0xc6db9 - (sStack_2c * 2 + -8));
      }
      uStack_20 = (ushort)bVar2;
      *(int *)(&unk_c6dba + (&dword_dc7b8)[(short)uStack_20] * 4) = (int)sStack_2c;
      iVar3 = iVar3 + 1;
    }
    iVar3 = 0x48;
    for (sStack_2c = 0; sStack_2c < 8; sStack_2c = sStack_2c + 1) {
      if (sStack_2c < 4) {
        local_30 = CONCAT22(uStack_2a,sStack_2c);
        bVar2 = (&byte_c6d72)[sStack_2c * 2];
      }
      else {
        local_30 = 7 - CONCAT22(uStack_2a,sStack_2c);
        bVar2 = *(byte *)(0xc6d79 - (sStack_2c * 2 + -8));
      }
      uStack_20 = (ushort)bVar2;
      iStack_4c = iVar3;
      set_text_colors(0x40,0x43,&uStack_108);
      sprintf((char *)&uStack_108,(char *)&aC_c1340,
              *(int *)(&unk_c6dba + (&dword_dc7b8)[(short)uStack_20] * 4) + 0x91);
      strcat((char *)&uStack_108,&unk_ddac4 + (&dword_dc7b8)[(short)uStack_20] * 0x15);
      print_text_at(*(int *)(&unk_c6e20 + (short)local_30 * 4) >> 0x10,(int)(short)iStack_4c,
                    &uStack_108);
      uStack_3c = CONCAT22((short)((uint)((short)local_30 * 4) >> 0x10),
                           (&unk_c6e22)[(short)local_30 * 2]) + 0x6a;
      if (((((&dword_dc7b8)[byte_c6d7a] == (&dword_dc7b8)[(short)uStack_20]) ||
           ((&dword_dc7b8)[byte_c6d7b] == (&dword_dc7b8)[(short)uStack_20])) ||
          ((&dword_dc7b8)[byte_c6d7c] == (&dword_dc7b8)[(short)uStack_20])) ||
         ((&dword_dc7b8)[byte_c6d7d] == (&dword_dc7b8)[(short)uStack_20])) {
        set_text_colors(0x44,0x43);
      }
      else {
        set_text_colors(0x40,0x43);
      }
      sprintf((char *)&uStack_108,(char *)&aD_c1344,
              *(undefined4 *)((int)auStack_1e0 + (short)uStack_20 * 4));
      print_text_at((int)(short)uStack_3c,(int)(short)iStack_4c);
      if (sStack_2c == 3) {
        iStack_4c = iStack_4c + 0x10;
      }
      iVar3 = iStack_4c;
    }
    iStack_4c = iVar3 + 0x3f;
    if ((((&dword_dc7b8)[byte_c6d7a] < 0x1a) && ((&dword_dc7b8)[byte_c6d7b] < 0x1a)) &&
       (((&dword_dc7b8)[byte_c6d7c] < 0x1a && ((&dword_dc7b8)[byte_c6d7d] < 0x1a)))) {
      dword_dd100 = locateshape(dword_dd104,&aAup1);
      drawshape_remap_home(dword_dd100);
      sStack_2c = 0;
      iVar3 = local_30;
      while( true ) {
        local_30._2_2_ = (undefined2)((uint)iVar3 >> 0x10);
        if (3 < sStack_2c) break;
        if (sStack_2c < 2) {
          local_30._0_2_ = sStack_2c + 4;
          bVar2 = (&byte_c6d7a)[sStack_2c * 2];
        }
        else {
          local_30._0_2_ = 7 - sStack_2c;
          bVar2 = (&byte_c6d7d)[-(sStack_2c * 2 + -4)];
        }
        uStack_20 = (ushort)bVar2;
        set_text_colors(0x40,0x43,&uStack_108);
        sprintf((char *)&uStack_108,(char *)&aC_c1340,
                *(int *)(&unk_c6dba + (&dword_dc7b8)[(short)uStack_20] * 4) + 0x91);
        strcat((char *)&uStack_108,&unk_ddac4 + (&dword_dc7b8)[(short)uStack_20] * 0x15);
        print_text_at(*(int *)(&unk_c6e20 + (short)local_30 * 4) >> 0x10,(int)(short)iStack_4c,
                      &uStack_108);
        uStack_3c._0_2_ = (&unk_c6e22)[(short)local_30 * 2] + 0x6a;
        if (((&dword_dc7b8)[byte_c6d82] == (&dword_dc7b8)[(short)uStack_20]) ||
           ((&dword_dc7b8)[byte_c6d83] == (&dword_dc7b8)[(short)uStack_20])) {
          set_text_colors(0x44,0x43);
        }
        else {
          set_text_colors(0x40,0x43);
        }
        sprintf((char *)&uStack_108,(char *)&aD_c1344,
                *(undefined4 *)((int)auStack_1e0 + (short)uStack_20 * 4));
        print_text_at((int)(short)uStack_3c,(int)(short)iStack_4c);
        iVar3 = CONCAT22(local_30._2_2_,(short)local_30);
        if (sStack_2c == 1) {
          iStack_4c = iStack_4c + 0x10;
        }
        sStack_2c = sStack_2c + 1;
      }
      iStack_4c = iStack_4c + 0x3d;
      if (((&dword_dc7b8)[byte_c6d82] < 0x1a) && ((&dword_dc7b8)[byte_c6d83] < 0x1a)) {
        local_30 = iVar3;
        dword_dd100 = locateshape(dword_dd104,&aAup2);
        drawshape_remap_home(dword_dd100);
        uStack_20 = (ushort)byte_c6d82;
        set_text_colors(0x40,0x43,&uStack_108);
        sprintf((char *)&uStack_108,(char *)&aC_c1340,
                *(int *)(&unk_c6dba + (&dword_dc7b8)[(short)uStack_20] * 4) + 0x91);
        strcat((char *)&uStack_108,&unk_ddac4 + (&dword_dc7b8)[(short)uStack_20] * 0x15);
        print_text_at(0x48,(int)(short)((short)iStack_4c + -1),&uStack_108);
        if (((&dword_dc7b8)[byte_c6d8a] == (&dword_dc7b8)[(short)uStack_20]) ||
           ((&dword_dc7b8)[byte_c6d9a] == (&dword_dc7b8)[(short)uStack_20])) {
          set_text_colors(0x44,0x43);
        }
        else {
          set_text_colors(0x40,0x43);
        }
        sprintf((char *)&uStack_108,(char *)&aD_c1344,
                *(undefined4 *)((int)auStack_1e0 + (short)uStack_20 * 4));
        print_text_at(0xb2,(int)(short)((short)iStack_4c + -1),&uStack_108);
        iStack_4c = iStack_4c + 0x10;
        uStack_20 = (ushort)byte_c6d83;
        set_text_colors(0x40,0x43);
        sprintf((char *)&uStack_108,(char *)&aC_c1340,
                *(int *)(&unk_c6dba + (&dword_dc7b8)[(short)uStack_20] * 4) + 0x91);
        strcat((char *)&uStack_108,&unk_ddac4 + (&dword_dc7b8)[(short)uStack_20] * 0x15);
        print_text_at(0x48,(int)(short)((short)iStack_4c + -1),&uStack_108);
        if (((&dword_dc7b8)[byte_c6d8a] == (&dword_dc7b8)[(short)uStack_20]) ||
           ((&dword_dc7b8)[byte_c6d9a] == (&dword_dc7b8)[(short)uStack_20])) {
          set_text_colors(0x44,0x43);
        }
        else {
          set_text_colors(0x40,0x43);
        }
        sprintf((char *)&uStack_108,(char *)&aD_c1344,
                *(undefined4 *)((int)auStack_1e0 + (short)uStack_20 * 4));
        print_text_at(0xb2,(int)(short)((short)iStack_4c + -1),&uStack_108);
        iStack_4c = iStack_4c + -0x10;
        iVar3 = local_30;
      }
    }
    else {
      iStack_4c = iVar3 + 0x8c;
      iVar3 = local_30;
    }
    local_30 = iVar3;
    if ((&dword_dc7b8)[byte_c6d8a] < 0x1a) {
      dword_dd100 = locateshape(dword_dd104,&aAup3);
      drawshape_remap_home(dword_dd100);
      local_50 = 1;
      uStack_4e = 0;
      dword_dd100 = locateshape(dword_dd104,&aMidl);
      drawshape_remap_home(dword_dd100);
      set_text_colors(0x40,0x43,&uStack_108);
      uStack_108._0_2_ = asc;
      *(undefined1 *)((int)&uStack_108 + (uint)bVar8 * -4 + 2) = (&DAT_000c135d)[(uint)bVar8 * -4];
      uStack_20 = (ushort)byte_c6d8a;
      strcat((char *)&uStack_108,
             &unk_ddac4 + (&dword_dc7b8)[(int)(uint)CONCAT12(byte_c6d8a,uStack_22) >> 0x10] * 0x15);
      print_text_at(0x102,(int)(short)((short)iStack_4c + -4),&uStack_108);
      sprintf((char *)&uStack_108,(char *)&aD_c1344,
              *(undefined4 *)((int)auStack_1e0 + (short)uStack_20 * 4));
      if ((&dword_dc7b8)[byte_c6d92] == (&dword_dc7b8)[(short)uStack_20]) {
        if (*(int *)(&unk_c5581 + (short)uStack_20 * 4) == 3) {
          set_text_colors(0x44,0x43);
        }
        else {
          set_text_colors(0xc4,0x43);
        }
      }
      else {
        set_text_colors(0x40,0x43);
      }
      print_text_at(0x16c,(int)(short)((short)iStack_4c + -4),&uStack_108);
    }
    if ((&dword_dc7b8)[byte_c6d9a] < 0x1a) {
      dword_dd100 = locateshape(dword_dd104,&aAdn3);
      drawshape_remap_home(dword_dd100);
      if (CONCAT22(uStack_4e,local_50) == 0) {
        dword_dd100 = locateshape(dword_dd104,&aMidl);
        drawshape_remap_home(dword_dd100);
      }
      iStack_4c = iStack_4c + 0x10;
      set_text_colors(0x40,0x43,&uStack_108);
      uStack_108._0_2_ = asc;
      *(undefined1 *)((int)&uStack_108 + (uint)bVar8 * -4 + 2) = (&DAT_000c135d)[(uint)bVar8 * -4];
      uStack_20 = (ushort)byte_c6d9a;
      strcat((char *)&uStack_108,
             &unk_ddac4 + (&dword_dc7b8)[(int)(uint)CONCAT12(byte_c6d9a,uStack_22) >> 0x10] * 0x15);
      print_text_at(0x102,(int)(short)((short)iStack_4c + -4),&uStack_108);
      sprintf((char *)&uStack_108,(char *)&aD_c1344,
              *(undefined4 *)((int)auStack_1e0 + (short)uStack_20 * 4));
      if ((&dword_dc7b8)[byte_c6d92] == (&dword_dc7b8)[(short)uStack_20]) {
        if (*(int *)(&unk_c5581 + (short)uStack_20 * 4) == 3) {
          set_text_colors(0x44,0x43);
        }
        else {
          set_text_colors(0xc4,0x43);
        }
      }
      else {
        set_text_colors(0x40,0x43);
      }
      print_text_at(0x16c,(int)(short)((short)iStack_4c + -4),&uStack_108);
      iStack_4c = iStack_4c + -0x10;
    }
    if (((&dword_dc7b8)[byte_c6da2] < 0x1a) && ((&dword_dc7b8)[byte_c6da3] < 0x1a)) {
      uStack_20 = (ushort)byte_c6da2;
      set_text_colors(0x40,0x43,&uStack_108);
      sprintf((char *)&uStack_108,(char *)&aC_c1340,
              *(int *)(&unk_c6dba + (&dword_dc7b8)[(short)uStack_20] * 4) + 0x91);
      strcat((char *)&uStack_108,&unk_ddac4 + (&dword_dc7b8)[(short)uStack_20] * 0x15);
      print_text_at(0x1c6,(int)(short)((short)iStack_4c + -1),&uStack_108);
      if (((&dword_dc7b8)[byte_c6d8a] == (&dword_dc7b8)[(short)uStack_20]) ||
         ((&dword_dc7b8)[byte_c6d9a] == (&dword_dc7b8)[(short)uStack_20])) {
        set_text_colors(0xc4,0x43);
      }
      else {
        set_text_colors(0x40,0x43);
      }
      sprintf((char *)&uStack_108,(char *)&aD_c1344,
              *(undefined4 *)((int)auStack_1e0 + (short)uStack_20 * 4));
      print_text_at(0x230,(int)(short)((short)iStack_4c + -1),&uStack_108);
      iStack_4c = iStack_4c + 0x10;
      uStack_20 = (ushort)byte_c6da3;
      set_text_colors(0x40,0x43);
      sprintf((char *)&uStack_108,(char *)&aC_c1340,
              *(int *)(&unk_c6dba + (&dword_dc7b8)[(short)uStack_20] * 4) + 0x91);
      strcat((char *)&uStack_108,&unk_ddac4 + (&dword_dc7b8)[(short)uStack_20] * 0x15);
      print_text_at(0x1c6,(int)(short)((short)iStack_4c + -1),&uStack_108);
      if (((&dword_dc7b8)[byte_c6d8a] == (&dword_dc7b8)[(short)uStack_20]) ||
         ((&dword_dc7b8)[byte_c6d9a] == (&dword_dc7b8)[(short)uStack_20])) {
        set_text_colors(0xc4,0x43);
      }
      else {
        set_text_colors(0x40,0x43);
      }
      sprintf((char *)&uStack_108,(char *)&aD_c1344,
              *(undefined4 *)((int)auStack_1e0 + (short)uStack_20 * 4));
      print_text_at(0x230,(int)(short)((short)iStack_4c + -1),&uStack_108);
      iStack_4c = iStack_4c + 0x3d;
      dword_dd100 = locateshape(dword_dd104,&aAdn2);
      drawshape_remap_home(dword_dd100);
    }
    else {
      iStack_4c = iStack_4c + 0x4d;
    }
    if (((((&dword_dc7b8)[byte_c6daa] < 0x1a) && ((&dword_dc7b8)[byte_c6dab] < 0x1a)) &&
        ((&dword_dc7b8)[byte_c6dac] < 0x1a)) && ((&dword_dc7b8)[byte_c6dad] < 0x1a)) {
      sStack_2c = 0;
      iVar3 = local_30;
      while( true ) {
        local_30._2_2_ = (undefined2)((uint)iVar3 >> 0x10);
        if (3 < sStack_2c) break;
        if (sStack_2c < 2) {
          bVar8 = (&byte_c6daa)[sStack_2c * 2];
          local_30._0_2_ = sStack_2c;
        }
        else {
          local_30._0_2_ = 3 - sStack_2c;
          bVar8 = (&byte_c6dad)[-(sStack_2c * 2 + -4)];
        }
        uStack_20 = (ushort)bVar8;
        set_text_colors(0x40,0x43,&uStack_108);
        sprintf((char *)&uStack_108,(char *)&aC_c1340,
                *(int *)(&unk_c6dba + (&dword_dc7b8)[(short)uStack_20] * 4) + 0x91);
        strcat((char *)&uStack_108,&unk_ddac4 + (&dword_dc7b8)[(short)uStack_20] * 0x15);
        print_text_at((int)(short)(0x280 - ((&unk_c6e22)[(5 - (short)local_30) * 2] + 100)),
                      (int)(short)iStack_4c,&uStack_108);
        uStack_3c._0_2_ = 0x286 - (&unk_c6e22)[(5 - (short)local_30) * 2];
        if (((&dword_dc7b8)[byte_c6da2] == (&dword_dc7b8)[(short)uStack_20]) ||
           ((&dword_dc7b8)[byte_c6da3] == (&dword_dc7b8)[(short)uStack_20])) {
          set_text_colors(0xc4,0x43);
        }
        else {
          set_text_colors(0x40,0x43);
        }
        sprintf((char *)&uStack_108,(char *)&aD_c1344,
                *(undefined4 *)((int)auStack_1e0 + (short)uStack_20 * 4));
        print_text_at((int)(short)uStack_3c,(int)(short)iStack_4c);
        iVar3 = CONCAT22(local_30._2_2_,(short)local_30);
        if (sStack_2c == 1) {
          iStack_4c = iStack_4c + 0x10;
        }
        sStack_2c = sStack_2c + 1;
      }
      iStack_4c = iStack_4c + 0x3d;
      local_30 = iVar3;
      dword_dd100 = locateshape(dword_dd104,&aAdn1);
      drawshape_remap_home(dword_dd100);
    }
    else {
      iStack_4c = iStack_4c + 0x4d;
    }
    sStack_2c = 0;
    iVar3 = local_30;
    while( true ) {
      local_30._2_2_ = (undefined2)((uint)iVar3 >> 0x10);
      if (7 < sStack_2c) break;
      if (sStack_2c < 4) {
        local_30._0_2_ = sStack_2c;
        bVar8 = (&unk_c6db2)[sStack_2c * 2];
      }
      else {
        local_30._0_2_ = 7 - sStack_2c;
        bVar8 = *(byte *)(0xc6db9 - (sStack_2c * 2 + -8));
      }
      uStack_20 = (ushort)bVar8;
      set_text_colors(0x40,0x43,&uStack_108);
      sprintf((char *)&uStack_108,(char *)&aC_c1340,
              *(int *)(&unk_c6dba + (&dword_dc7b8)[(short)uStack_20] * 4) + 0x91);
      strcat((char *)&uStack_108,&unk_ddac4 + (&dword_dc7b8)[(short)uStack_20] * 0x15);
      print_text_at(*(int *)(&unk_c6e20 + (short)local_30 * 4) >> 0x10,(int)(short)iStack_4c,
                    &uStack_108);
      uStack_3c._0_2_ = (&unk_c6e22)[(short)local_30 * 2] + 0x6a;
      if ((((&dword_dc7b8)[byte_c6daa] == (&dword_dc7b8)[(short)uStack_20]) ||
          ((&dword_dc7b8)[byte_c6dab] == (&dword_dc7b8)[(short)uStack_20])) ||
         (((&dword_dc7b8)[byte_c6dac] == (&dword_dc7b8)[(short)uStack_20] ||
          ((&dword_dc7b8)[byte_c6dad] == (&dword_dc7b8)[(short)uStack_20])))) {
        set_text_colors(0xc4,0x43);
      }
      else {
        set_text_colors(0x40,0x43);
      }
      sprintf((char *)&uStack_108,(char *)&aD_c1344,
              *(undefined4 *)((int)auStack_1e0 + (short)uStack_20 * 4));
      print_text_at((int)(short)uStack_3c,(int)(short)iStack_4c);
      iVar3 = CONCAT22(local_30._2_2_,(short)local_30);
      if (sStack_2c == 3) {
        iStack_4c = iStack_4c + 0x10;
      }
      sStack_2c = sStack_2c + 1;
    }
    local_30 = iVar3;
    text_capture_stop();
    freemem(dword_dd104);
    setfontstate(auStack_b4);
  }
  else {
    setfont(local_54);
    pcVar4 = aPlayoffsHaveNotBeenSeede;
    puVar6 = &uStack_108;
    for (iVar3 = 8; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar6 = *(undefined4 *)pcVar4;
      pcVar4 = pcVar4 + ((uint)bVar8 * -2 + 1) * 4;
      puVar6 = puVar6 + (uint)bVar8 * -2 + 1;
    }
    *(undefined2 *)puVar6 = *(undefined2 *)pcVar4;
    iVar3 = textwidth(&uStack_108);
    print_outlined(0x140 - (iVar3 >> 1),0xf0,&uStack_108);
    setfont(uStack_44);
  }
  return;
}


