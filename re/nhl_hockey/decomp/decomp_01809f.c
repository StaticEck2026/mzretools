// Decompiled by Ghidra from hockey.elf (via ledisasm ELF export)
// This is machine generated pseudo-C meant as a reference for porting, it does not compile as is.
#include "prototypes.h"

// ================================================================================================
// team_stats_penalty_killing @ 0x1809f [__watcall]
// ================================================================================================

undefined8 __watcall team_stats_penalty_killing(undefined4 param_1,undefined4 unaff_EDX)

{
  undefined4 uVar1;
  
  __CHK(0x20);
  stats_current_arg = 2;
  if (stats_hub_active != 0) {
    dword_dc6b0 = allocmem(aSfPal1,0x300,0x20);
    getpalette(0,0x100,dword_dc6b0);
    dword_dc6ac = allocmem(aSfPal2,0x300,0x20);
    getpalette(0,0x100,dword_dc6ac);
    fade_palette(1,dword_dc6b0,0x10);
    freemem(dword_dc6b0);
    dword_dc6a8 = team_stats_screen(2);
    fade_palette(0,dword_dc6ac,0x10);
    freemem(dword_dc6ac);
    return CONCAT44(unaff_EDX,dword_dc6a8);
  }
  uVar1 = (*dword_c65c0)();
  return CONCAT44(unaff_EDX,uVar1);
}


// ================================================================================================
// team_stats_power_play @ 0x18182 [__watcall]
// ================================================================================================

undefined8 __watcall team_stats_power_play(undefined4 param_1,undefined4 unaff_EDX)

{
  undefined4 uVar1;
  
  __CHK(0x20);
  stats_current_arg = 3;
  if (stats_hub_active != 0) {
    dword_dc6b0 = allocmem(aSfPal1,0x300,0x20);
    getpalette(0,0x100,dword_dc6b0);
    dword_dc6ac = allocmem(aSfPal2,0x300,0x20);
    getpalette(0,0x100,dword_dc6ac);
    fade_palette(1,dword_dc6b0,0x10);
    freemem(dword_dc6b0);
    dword_dc6a8 = team_stats_screen(3);
    fade_palette(0,dword_dc6ac,0x10);
    freemem(dword_dc6ac);
    return CONCAT44(unaff_EDX,dword_dc6a8);
  }
  uVar1 = (*dword_c65c0)();
  return CONCAT44(unaff_EDX,uVar1);
}


// ================================================================================================
// team_stats_penalties @ 0x18265 [__watcall]
// ================================================================================================

undefined8 __watcall team_stats_penalties(undefined4 param_1,undefined4 unaff_EDX)

{
  undefined4 uVar1;
  
  __CHK(0x20);
  stats_current_arg = 4;
  if (stats_hub_active != 0) {
    dword_dc6b0 = allocmem(aSfPal1,0x300,0x20);
    getpalette(0,0x100,dword_dc6b0);
    dword_dc6ac = allocmem(aSfPal2,0x300,0x20);
    getpalette(0,0x100,dword_dc6ac);
    fade_palette(1,dword_dc6b0,0x10);
    freemem(dword_dc6b0);
    dword_dc6a8 = team_stats_screen(4);
    fade_palette(0,dword_dc6ac,0x10);
    freemem(dword_dc6ac);
    return CONCAT44(unaff_EDX,dword_dc6a8);
  }
  uVar1 = (*dword_c65c0)();
  return CONCAT44(unaff_EDX,uVar1);
}


// ================================================================================================
// leaders_points @ 0x18348 [__watcall]
// ================================================================================================

undefined8 __watcall leaders_points(undefined4 param_1,undefined4 unaff_EDX)

{
  undefined4 uVar1;
  
  __CHK(0x20);
  stats_current_arg = 0;
  if (stats_hub_active != 0) {
    dword_dc6b0 = allocmem(aSfPal1,0x300,0x20);
    getpalette(0,0x100,dword_dc6b0);
    dword_dc6ac = allocmem(aSfPal2,0x300,0x20);
    getpalette(0,0x100,dword_dc6ac);
    fade_palette(1,dword_dc6b0,0x10);
    freemem(dword_dc6b0);
    dword_dc6a8 = stats_table(0);
    fade_palette(0,dword_dc6ac,0x10);
    freemem(dword_dc6ac);
    return CONCAT44(unaff_EDX,dword_dc6a8);
  }
  uVar1 = (*dword_c65c4)();
  return CONCAT44(unaff_EDX,uVar1);
}


// ================================================================================================
// leaders_goals @ 0x18425 [__watcall]
// ================================================================================================

undefined8 __watcall leaders_goals(undefined4 param_1,undefined4 unaff_EDX)

{
  undefined4 uVar1;
  
  __CHK(0x20);
  stats_current_arg = 1;
  if (stats_hub_active != 0) {
    dword_dc6b0 = allocmem(aSfPal1,0x300,0x20);
    getpalette(0,0x100,dword_dc6b0);
    dword_dc6ac = allocmem(aSfPal2,0x300,0x20);
    getpalette(0,0x100,dword_dc6ac);
    fade_palette(1,dword_dc6b0,0x10);
    freemem(dword_dc6b0);
    dword_dc6a8 = stats_table(1);
    fade_palette(0,dword_dc6ac,0x10);
    freemem(dword_dc6ac);
    return CONCAT44(unaff_EDX,dword_dc6a8);
  }
  uVar1 = (*dword_c65c4)();
  return CONCAT44(unaff_EDX,uVar1);
}


// ================================================================================================
// leaders_assists @ 0x18508 [__watcall]
// ================================================================================================

undefined8 __watcall leaders_assists(undefined4 param_1,undefined4 unaff_EDX)

{
  undefined4 uVar1;
  
  __CHK(0x20);
  stats_current_arg = 2;
  if (stats_hub_active != 0) {
    dword_dc6b0 = allocmem(aSfPal1,0x300,0x20);
    getpalette(0,0x100,dword_dc6b0);
    dword_dc6ac = allocmem(aSfPal2,0x300,0x20);
    getpalette(0,0x100,dword_dc6ac);
    fade_palette(1,dword_dc6b0,0x10);
    freemem(dword_dc6b0);
    dword_dc6a8 = stats_table(2);
    fade_palette(0,dword_dc6ac,0x10);
    freemem(dword_dc6ac);
    return CONCAT44(unaff_EDX,dword_dc6a8);
  }
  uVar1 = (*dword_c65c4)();
  return CONCAT44(unaff_EDX,uVar1);
}


// ================================================================================================
// leaders_pp_goals @ 0x185eb [__watcall]
// ================================================================================================

undefined8 __watcall leaders_pp_goals(undefined4 param_1,undefined4 unaff_EDX)

{
  undefined4 uVar1;
  
  __CHK(0x20);
  stats_current_arg = 3;
  if (stats_hub_active != 0) {
    dword_dc6b0 = allocmem(aSfPal1,0x300,0x20);
    getpalette(0,0x100,dword_dc6b0);
    dword_dc6ac = allocmem(aSfPal2,0x300,0x20);
    getpalette(0,0x100,dword_dc6ac);
    fade_palette(1,dword_dc6b0,0x10);
    freemem(dword_dc6b0);
    dword_dc6a8 = stats_table(3);
    fade_palette(0,dword_dc6ac,0x10);
    freemem(dword_dc6ac);
    return CONCAT44(unaff_EDX,dword_dc6a8);
  }
  uVar1 = (*dword_c65c4)();
  return CONCAT44(unaff_EDX,uVar1);
}


// ================================================================================================
// leaders_sh_goals @ 0x186ce [__watcall]
// ================================================================================================

undefined8 __watcall leaders_sh_goals(undefined4 param_1,undefined4 unaff_EDX)

{
  undefined4 uVar1;
  
  __CHK(0x20);
  stats_current_arg = 4;
  if (stats_hub_active != 0) {
    dword_dc6b0 = allocmem(aSfPal1,0x300,0x20);
    getpalette(0,0x100,dword_dc6b0);
    dword_dc6ac = allocmem(aSfPal2,0x300,0x20);
    getpalette(0,0x100,dword_dc6ac);
    fade_palette(1,dword_dc6b0,0x10);
    freemem(dword_dc6b0);
    dword_dc6a8 = stats_table(4);
    fade_palette(0,dword_dc6ac,0x10);
    freemem(dword_dc6ac);
    return CONCAT44(unaff_EDX,dword_dc6a8);
  }
  uVar1 = (*dword_c65c4)();
  return CONCAT44(unaff_EDX,uVar1);
}


// ================================================================================================
// leaders_plus_minus @ 0x187b1 [__watcall]
// ================================================================================================

undefined8 __watcall leaders_plus_minus(undefined4 param_1,undefined4 unaff_EDX)

{
  undefined4 uVar1;
  
  __CHK(0x20);
  stats_current_arg = 5;
  if (stats_hub_active != 0) {
    dword_dc6b0 = allocmem(aSfPal1,0x300,0x20);
    getpalette(0,0x100,dword_dc6b0);
    dword_dc6ac = allocmem(aSfPal2,0x300,0x20);
    getpalette(0,0x100,dword_dc6ac);
    fade_palette(1,dword_dc6b0,0x10);
    freemem(dword_dc6b0);
    dword_dc6a8 = stats_table(5);
    fade_palette(0,dword_dc6ac,0x10);
    freemem(dword_dc6ac);
    return CONCAT44(unaff_EDX,dword_dc6a8);
  }
  uVar1 = (*dword_c65c4)();
  return CONCAT44(unaff_EDX,uVar1);
}


// ================================================================================================
// leaders_penalty_minutes @ 0x18894 [__watcall]
// ================================================================================================

undefined8 __watcall leaders_penalty_minutes(undefined4 param_1,undefined4 unaff_EDX)

{
  undefined4 uVar1;
  
  __CHK(0x20);
  stats_current_arg = 6;
  if (stats_hub_active != 0) {
    dword_dc6b0 = allocmem(aSfPal1,0x300,0x20);
    getpalette(0,0x100,dword_dc6b0);
    dword_dc6ac = allocmem(aSfPal2,0x300,0x20);
    getpalette(0,0x100,dword_dc6ac);
    fade_palette(1,dword_dc6b0,0x10);
    freemem(dword_dc6b0);
    dword_dc6a8 = stats_table(6);
    fade_palette(0,dword_dc6ac,0x10);
    freemem(dword_dc6ac);
    return CONCAT44(unaff_EDX,dword_dc6a8);
  }
  uVar1 = (*dword_c65c4)();
  return CONCAT44(unaff_EDX,uVar1);
}


// ================================================================================================
// leaders_shooting_pct @ 0x18977 [__watcall]
// ================================================================================================

undefined8 __watcall leaders_shooting_pct(undefined4 param_1,undefined4 unaff_EDX)

{
  undefined4 uVar1;
  
  __CHK(0x20);
  stats_current_arg = 7;
  if (stats_hub_active != 0) {
    dword_dc6b0 = allocmem(aSfPal1,0x300,0x20);
    getpalette(0,0x100,dword_dc6b0);
    dword_dc6ac = allocmem(aSfPal2,0x300,0x20);
    getpalette(0,0x100,dword_dc6ac);
    fade_palette(1,dword_dc6b0,0x10);
    freemem(dword_dc6b0);
    dword_dc6a8 = stats_table(7);
    fade_palette(0,dword_dc6ac,0x10);
    freemem(dword_dc6ac);
    return CONCAT44(unaff_EDX,dword_dc6a8);
  }
  uVar1 = (*dword_c65c4)();
  return CONCAT44(unaff_EDX,uVar1);
}


// ================================================================================================
// leaders_gaa @ 0x18a5a [__watcall]
// ================================================================================================

undefined8 __watcall leaders_gaa(undefined4 param_1,undefined4 unaff_EDX)

{
  undefined4 uVar1;
  
  __CHK(0x20);
  stats_current_arg = 8;
  if (stats_hub_active != 0) {
    dword_dc6b0 = allocmem(aSfPal1,0x300,0x20);
    getpalette(0,0x100,dword_dc6b0);
    dword_dc6ac = allocmem(aSfPal2,0x300,0x20);
    getpalette(0,0x100,dword_dc6ac);
    fade_palette(1,dword_dc6b0,0x10);
    freemem(dword_dc6b0);
    dword_dc6a8 = stats_table(8);
    fade_palette(0,dword_dc6ac,0x10);
    freemem(dword_dc6ac);
    return CONCAT44(unaff_EDX,dword_dc6a8);
  }
  uVar1 = (*dword_c65c8)();
  return CONCAT44(unaff_EDX,uVar1);
}


// ================================================================================================
// leaders_wins @ 0x18b3d [__watcall]
// ================================================================================================

undefined8 __watcall leaders_wins(undefined4 param_1,undefined4 unaff_EDX)

{
  undefined4 uVar1;
  
  __CHK(0x20);
  stats_current_arg = 9;
  if (stats_hub_active != 0) {
    dword_dc6b0 = allocmem(aSfPal1,0x300,0x20);
    getpalette(0,0x100,dword_dc6b0);
    dword_dc6ac = allocmem(aSfPal2,0x300,0x20);
    getpalette(0,0x100,dword_dc6ac);
    fade_palette(1,dword_dc6b0,0x10);
    freemem(dword_dc6b0);
    dword_dc6a8 = stats_table(9);
    fade_palette(0,dword_dc6ac,0x10);
    freemem(dword_dc6ac);
    return CONCAT44(unaff_EDX,dword_dc6a8);
  }
  uVar1 = (*dword_c65c8)();
  return CONCAT44(unaff_EDX,uVar1);
}


// ================================================================================================
// leaders_save_pct @ 0x18c20 [__watcall]
// ================================================================================================

undefined8 __watcall leaders_save_pct(undefined4 param_1,undefined4 unaff_EDX)

{
  undefined4 uVar1;
  
  __CHK(0x20);
  stats_current_arg = 10;
  if (stats_hub_active != 0) {
    dword_dc6b0 = allocmem(aSfPal1,0x300,0x20);
    getpalette(0,0x100,dword_dc6b0);
    dword_dc6ac = allocmem(aSfPal2,0x300,0x20);
    getpalette(0,0x100,dword_dc6ac);
    fade_palette(1,dword_dc6b0,0x10);
    freemem(dword_dc6b0);
    dword_dc6a8 = stats_table(10);
    fade_palette(0,dword_dc6ac,0x10);
    freemem(dword_dc6ac);
    return CONCAT44(unaff_EDX,dword_dc6a8);
  }
  uVar1 = (*dword_c65c8)();
  return CONCAT44(unaff_EDX,uVar1);
}


// ================================================================================================
// menu_show_team_roster @ 0x18d03 [__watcall]
// ================================================================================================

void __watcall menu_show_team_roster(void)

{
  hub_team_roster();
  return;
}


// ================================================================================================
// menu_show_player_stats @ 0x18d0d [__watcall]
// ================================================================================================

undefined4 __watcall menu_show_player_stats(void)

{
  __CHK(4);
  stats_next_screen = (byte_dc836 != 'G') + 4;
  return 1;
}


// ================================================================================================
// stats_free_buffers @ 0x18d33 [__watcall]
// ================================================================================================

longlong __watcall stats_free_buffers(undefined4 param_1,uint unaff_EDX)

{
  __CHK(0x1c);
  if (dword_c65ac != 0) {
    freemem(dword_c65ac);
    dword_c65ac = 0;
  }
  if (dword_c65a8 != 0) {
    freemem(dword_c65a8);
    dword_c65a8 = 0;
  }
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// menu_output_current_data @ 0x18d7f [__watcall]
// ================================================================================================

longlong __watcall menu_output_current_data(undefined4 param_1,uint unaff_EDX)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  char acStack_2c [12];
  undefined4 local_20;
  undefined4 uStack_1c;
  
  __CHK(0x44);
  uVar3 = dword_c71dc;
  uVar2 = dword_c71d8;
  uVar1 = dword_c71d4;
  uStack_1c = dword_c71cc;
  local_20 = dword_c71d0;
  dword_c71cc = 0x41;
  dword_c71d0 = 0x40;
  dword_c71d4 = 0x42;
  dword_c71d8 = 0x40;
  dword_c71dc = 0;
  iVar4 = text_entry_dialog(aPleaseEnterOutputFileNam,acStack_2c,8,0x22,0,0,0,0,5);
  if ((iVar4 != 0x1b) && (acStack_2c[0] != '\0')) {
    export_stats_dialog(acStack_2c);
  }
  dword_c71cc = uStack_1c;
  dword_c71d0 = local_20;
  dword_c71d4 = uVar1;
  dword_c71d8 = uVar2;
  dword_c71dc = uVar3;
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// draw_box_frame @ 0x18e43 [__watcall]
// ================================================================================================

void __watcall
draw_box_frame(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  __CHK(0x24);
  drawline(0xe,0x21,0xaf,0x21,0x22,unaff_EDX,unaff_ECX,unaff_EBX);
  drawline(0xaf,0x21,0xaf,0x86,0x22);
  drawline(0xe,0x86,0xaf,0x86,0x22);
  drawline(0xe,0x86,0xe,0x21,0x22);
  drawline(0xd,0x20,0xb0,0x20,0x21);
  drawline(0xb0,0x20,0xb0,0x87,0x21);
  drawline(0xd,0x87,0xb0,0x87,0x21);
  drawline(0xd,0x87,0xd,0x20,0x21);
  drawline(0xc,0x1f,0xb1,0x1f,0x20);
  drawline(0xb1,0x1f,0xb1,0x88,0x20);
  drawline(0xc,0x88,0xb1,0x88,0x20);
  drawline(0xc,0x88,0xc,0x1f,0x20);
  return;
}


// ================================================================================================
// return_one_18f74 @ 0x18f74 [__watcall]
// ================================================================================================

undefined4 __watcall return_one_18f74(void)

{
  __CHK(4);
  return 1;
}


// ================================================================================================
// return_one_18f86 @ 0x18f86 [__watcall]
// ================================================================================================

undefined4 __watcall return_one_18f86(void)

{
  __CHK(4);
  return 1;
}


// ================================================================================================
// simulate_pending_games @ 0x18f8d [__watcall]
// ================================================================================================

undefined8 __watcall simulate_pending_games(undefined4 param_1,undefined4 unaff_EDX)

{
  short sVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  uint local_24;
  uint local_20;
  int iStack_1c;
  
  __CHK(0x2c);
  iVar2 = 0;
  do {
    if ((4 < (int)(&unk_dd730)[iVar2]) && ((&unk_dd730)[iVar2] != (&league_status_shown)[iVar2])) {
      league_done_mask = league_done_mask | 1 << ((byte)iVar2 & 0x1f);
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 < 6);
  if (league_done_mask == 0x3f) {
    uVar3 = 0;
  }
  else {
    do {
      sVar1 = randomrange(6);
      iVar2 = (int)sVar1;
      iStack_1c._0_1_ = (byte)sVar1;
      uVar4 = 1 << ((byte)iStack_1c & 0x1f);
      iStack_1c = iVar2;
    } while ((uVar4 & league_done_mask) != 0);
    league_done_mask = league_done_mask | uVar4;
    local_24 = (uint)(byte)(&unk_dd788)[iVar2 * 2];
    local_20 = (uint)(byte)(&unk_dd789)[iVar2 * 2];
    iVar5 = (&unk_dd730)[iVar2];
    if (4 < iVar5) {
      iVar5 = 3;
      local_24 = local_24 - 1;
      local_20 = local_20 - 1;
    }
    iVar2 = iVar2 * 2;
    uVar3 = league_highlight_game
                      ((&calendar_games)[iVar2],(&unk_dd775)[iVar2],&local_24,&local_20,iVar5);
    iVar5 = (&unk_dd730)[iStack_1c];
    if (iVar5 < 5) {
      (&unk_dd788)[iVar2] = (undefined)local_24;
      (&unk_dd789)[iVar2] = (undefined)local_20;
      if (iVar5 == 4) {
        (&unk_dd730)[iStack_1c] = 5;
      }
    }
    iVar2 = 0;
    do {
      (&league_status_shown)[iVar2] = (&unk_dd730)[iVar2];
      iVar2 = iVar2 + 1;
    } while (iVar2 < 6);
  }
  return CONCAT44(unaff_EDX,uVar3);
}


// ================================================================================================
// end_match_from_period @ 0x190be [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall end_match_from_period(void)

{
  uint uVar1;
  int iVar2;
  
  __CHK(0x14);
  if (_penalty_box_mode >> 0x10 == -1) {
    wait_sprite_fade();
  }
  else {
    loading_screen();
    gsummary_flush();
    gsummary_seek_last();
    ui_init();
    uVar1 = boxscore_screen(1,_period_num,_period_num,0);
    ui_shutdown();
    if (dword_c53fb == 0) {
      if ((((user2_team._2_2_ != 0x1a) && (user2_team._2_2_ != 0x1b)) && (_away_team_id != 0x1a)) &&
         (_away_team_id != 0x1b)) {
        if (_period_num == 1) {
          league_done_mask = 0;
          league_scores_init((int)user2_team._2_2_,(int)_away_team_id);
          iVar2 = 0;
          do {
            (&league_status_shown)[iVar2] = (&unk_dd730)[iVar2];
            iVar2 = iVar2 + 1;
          } while (iVar2 < 6);
        }
        if ((uVar1 & 4) == 0) {
          league_scores_advance(_period_num);
          iVar2 = simulate_pending_games();
          if (-1 < iVar2) {
            ui_init();
            boxscore_screen(0x20,_period_num,0,0);
            ui_shutdown();
          }
        }
      }
    }
  }
  _penalty_box_mode = CONCAT22(0xffff,penalty_box_mode);
  pause_menu(1);
  byte_c542f = 0;
  byte_c5430 = 0;
  byte_c5431 = 0;
  byte_c5432 = 0;
  gsummary_write_final();
  set_video_mode(0x140,200);
  return;
}


// ================================================================================================
// end_match_from_loop @ 0x1920f [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall
end_match_from_loop(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,
                   undefined4 unaff_ECX)

{
  undefined4 uVar1;
  int iVar2;
  uint extraout_EDX;
  
  __CHK(0x1c);
  getpalette(0,0x100,&palette_save,unaff_EDX,unaff_ECX,unaff_EBX);
  fade_palette(1,&palette_save,0x10);
  set_video_mode(0x280,0x1e0);
  ensure_free_memory(140000);
  loading_screen();
  gsummary_flush();
  gsummary_seek_last();
  gsummary_write_header();
  ui_init();
  uVar1 = boxscore_screen(1,1,_period_num,0);
  ui_shutdown(uVar1,uVar1);
  if ((dword_c53fb == 0) && ((extraout_EDX & 4) == 0)) {
    if ((user2_team._2_2_ != 0x1a) && (user2_team._2_2_ != 0x1b)) {
      if ((_away_team_id != 0x1a) && (_away_team_id != 0x1b)) {
        league_scores_advance(_period_num);
        simulate_pending_games();
        set_video_mode(0x280,0x1e0);
        free_match_resources();
        iVar2 = coach_clip_player();
        if (iVar2 != 0) {
          iVar2 = wait_ticks_or_input(10);
        }
        if (iVar2 == 0) {
          loading_screen();
          ui_init();
          boxscore_screen(0x20,_period_num,0,0);
          ui_shutdown();
        }
      }
    }
  }
  pause_menu(2);
  dword_c53f7 = 1;
  set_video_mode(0x140,200);
  return;
}


// ================================================================================================
// pause_menu @ 0x1935d [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

longlong __watcall pause_menu(int param_1,uint unaff_EDX)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  undefined4 *puVar7;
  int *piVar8;
  undefined4 extraout_EDX;
  undefined *puVar9;
  int iVar10;
  undefined4 *puVar11;
  undefined4 *puVar12;
  undefined4 *puVar13;
  undefined4 *puVar14;
  byte bVar15;
  undefined8 uVar16;
  ulonglong uVar17;
  undefined auStack_41c [768];
  undefined auStack_11c [64];
  undefined auStack_dc [24];
  int aiStack_c4 [10];
  int local_9c [12];
  int *local_6c [4];
  int local_5c;
  int local_58;
  int local_54;
  int local_50;
  undefined4 local_4c;
  undefined4 local_48;
  uint local_44;
  int local_40;
  int *local_3c;
  int *local_38;
  int local_34;
  int local_30;
  int local_2c;
  undefined4 *local_28;
  int iStack_24;
  int *local_20;
  int iStack_1c;
  
  bVar15 = 0;
  __CHK(0x434);
  iStack_1c = 0;
  local_2c = 0;
  local_30 = 0x5dc;
  set_pause_menu_labels(dword_c53fb);
  set_hub_title(param_1 + 3);
  uVar16 = replay_buffer_empty();
  funcptr_cef23 = (undefined *)((ulonglong)uVar16 >> 0x20);
  if ((int)uVar16 == 0) {
    funcptr_cef23 = menu_go_to_replay;
  }
  getmouse(&local_44,&local_48,&local_4c);
  pause_requested = 0;
  _input_enabled = 0;
  if (param_1 == 0) {
    ensure_free_memory(700000);
    getpalette(0,0x100,auStack_41c);
    fade_palette(1,auStack_41c,0x10);
  }
  setdefaultscreen();
  sprintf(&unk_dc890,aEadesk1d,param_1);
  puVar9 = install_path;
  if ((&unk_ed830)[param_1] != '\x01') {
    puVar9 = (undefined *)0x0;
  }
  make_path(auStack_dc,puVar9,&unk_dc890,0);
  uVar4 = loadshapes(auStack_dc,0);
  uVar5 = locateshape(uVar4,&aDesk);
  drawshape_home(uVar5);
  iVar6 = locateshape(uVar4,&aPal_c097f);
  iVar10 = 0;
  do {
    auStack_41c[iVar10] = *(undefined *)(iVar6 + 0x10 + iVar10);
    iVar10 = iVar10 + 1;
  } while (iVar10 < 0x300);
  freemem(uVar4);
  getfontstate(auStack_11c);
  setfont(font_current_default);
  if (param_1 == 2) {
    if (0x443 < league_game_number) {
      speech_stop();
    }
    local_6c[0] = (int *)&unk_cec4f;
    local_9c[8] = 3;
  }
  else {
    local_6c[0] = (int *)&unk_ceb8f;
    local_9c[8] = 6;
  }
  local_6c[3] = (int *)0x0;
  local_6c[2] = (int *)0x0;
  local_6c[1] = (int *)0x0;
  local_9c[3] = 0;
  local_9c[2] = 0;
  local_9c[1] = 0;
  local_9c[0] = 0;
  local_9c[7] = 0;
  local_9c[6] = 0;
  local_9c[5] = 0;
  local_9c[4] = 0;
  aiStack_c4[3] = 0;
  aiStack_c4[2] = 0;
  puVar7 = (undefined4 *)
           allocmem(aPointer,((*(int *)((int)pointer_shapes + 2) >> 0x10) + 1) *
                             (((int)pointer_shapes[1] >> 0x10) + 1) + 0x11,0x20);
  puVar13 = puVar7 + (uint)bVar15 * -2 + 1;
  puVar11 = pointer_shapes + (uint)bVar15 * -2 + 1;
  *puVar7 = *pointer_shapes;
  puVar14 = puVar13 + (uint)bVar15 * -2 + 1;
  puVar12 = puVar11 + (uint)bVar15 * -2 + 1;
  *puVar13 = *puVar11;
  *puVar14 = *puVar12;
  puVar14[(uint)bVar15 * -2 + 1] = puVar12[(uint)bVar15 * -2 + 1];
  *(undefined *)(puVar14 + (uint)bVar15 * -2 + 1 + (uint)bVar15 * -2 + 1) =
       *(undefined *)(puVar12 + (uint)bVar15 * -2 + 1 + (uint)bVar15 * -2 + 1);
  *(short *)(puVar7 + 1) = *(short *)(pointer_shapes + 1) + 1;
  *(short *)((int)puVar7 + 6) = *(short *)((int)pointer_shapes + 6) + 1;
  local_28 = puVar7;
  draw_menu_items(local_6c[0],local_9c[8],0xfa,0xf9,0xf8);
  ui_init();
  piVar8 = (int *)((*local_6c[0] + local_6c[0][2]) / 2);
  iVar6 = (local_6c[0][1] + local_6c[0][3]) / 2;
  local_40 = iVar6;
  local_3c = piVar8;
  local_34 = iVar6;
  local_20 = piVar8;
  grabshape(puVar7,piVar8,iVar6);
  drawshape_remap(pointer_shapes,piVar8,iVar6);
  if ((sound_enabled != '\0') && (dword_c721d == 0)) {
    puVar9 = install_path;
    if (byte_ed9e8 != '\x01') {
      puVar9 = (undefined *)0x0;
    }
    make_path(auStack_dc,puVar9,aPause,&aIff_c098c);
    dword_c721d = loadsound(auStack_dc);
    if ((dword_c721d != 0) && (((byte)option_flags & 0x40) != 0)) {
      playsample(dword_c721d,dword_d2431,3,0x4c);
    }
  }
  piVar8 = (int *)0x10;
  fade_palette(0,auStack_41c,0x10);
  setmouselimits(0,0,0x280,0x1e0);
  setmousepos(local_20,local_34);
  (*(code *)mouse_update_callback)();
  event_queue_reset();
  if (((param_1 == 1) && (dword_c5403 < 0)) && (dword_c5407 < 0)) {
    local_2c = 1;
  }
  uVar16 = ticks_elapsed();
  if ((param_1 == 2) && (0x443 < league_game_number)) {
    if (dword_df722._2_2_ < dword_df622._2_2_) {
      iVar6 = CONCAT22(user2_team._2_2_,(undefined2)user2_team);
    }
    else {
      iVar6 = CONCAT22(_away_team_id,user2_team._2_2_);
    }
    uVar4 = 0;
    if (3 < _period_num) {
      uVar4 = 0xffffffff;
    }
    if (*(uint *)(&unk_c5581 + user2_team._2_2_ * 4) == *(uint *)(&unk_c5581 + _away_team_id * 4)) {
      piVar8 = (int *)((int)(*(uint *)(&unk_c5581 + user2_team._2_2_ * 4) |
                            *(uint *)(&unk_c5581 + _away_team_id * 4)) % 2 + 1);
    }
    else {
      piVar8 = (int *)0x3;
    }
    uVar5 = 1;
    if (0x47b < league_game_number) {
      uVar5 = 2;
    }
    if (0x497 < league_game_number) {
      uVar5 = 3;
    }
    uVar16 = say_series_result_wrapper
                       (iVar6 >> 0x10,(league_game_number + -0x444) % 7 + 1,piVar8,uVar5,uVar4,
                        (int)ram0x000ccc9d >> 0x18);
    uVar16 = CONCAT44(CONCAT22((short)((ulonglong)uVar16 >> 0x30),
                               (ushort)(byte)((ulonglong)uVar16 >> 0x20)),(int)uVar16);
    ram0x000ccc9d = ram0x000ccc9d & 0xffffff;
  }
  local_38 = (int *)0xb4;
LAB_00019af6:
  piVar2 = local_38;
  if (sound_enabled != '\0') {
    if (local_38 < (int *)0xb396f) {
      if (0 < (int)local_38) {
        local_38 = (int *)0x0;
      }
    }
    else {
      uVar16 = ticks_elapsed();
      local_38 = (int *)((int)local_38 - (int)uVar16);
    }
    piVar8 = piVar2;
    if (((local_38 == (int *)0x0) && (param_1 == 0)) &&
       ((dword_c53f7 == 0 && ((option_flags._1_1_ & 1) != 0)))) {
      local_38 = (int *)0xffffffff;
      speech_stop_channels();
      uVar16 = say_backmomt_int();
    }
  }
  if (local_2c != 0) {
    iVar6 = ticks_elapsed((int)uVar16,(int)((ulonglong)uVar16 >> 0x20),piVar8);
    local_30 = local_30 - iVar6;
    if (local_30 < 0) {
      if ((sound_enabled != '\0') && (dword_c721d != 0)) {
        sound_fade(dword_d2431,3,100);
      }
      dword_c66d4 = 1;
      dword_c66d0 = 1;
      event_queue_reset();
      ui_shutdown();
      setfontstate(auStack_11c);
      _dword_dd6aa = setmouselimits(0,0,0x280,0x1e0);
      dword_c5840 = 0;
      dword_dd6ac._0_2_ = _dword_dd6aa;
      setmousepos(local_48,local_4c);
      getpalette(0,0x100,auStack_41c);
      fade_palette(1,auStack_41c);
      set_hub_title(dword_c53fb);
      freemem(local_28);
      if ((sound_enabled != '\0') && (dword_c721d != 0)) {
        do {
          iVar6 = sound_channel_status(ram0x000d242c >> 0x18,3);
        } while (iVar6 == 0);
        releasememblock(dword_c721d);
        dword_c721d = 0;
      }
      reload_match_graphics();
      if (((sound_enabled != '\0') && (dword_c53f7 == 0)) && ((option_flags._1_1_ & 1) != 0)) {
        speech_stop_channels();
        release_backmomt_int();
      }
      goto LAB_00019a00;
    }
  }
  local_44 = 0;
  do {
    uVar16 = event_queue_pop();
    uVar17 = CONCAT44((int)((ulonglong)uVar16 >> 0x20),local_44);
    if ((int)uVar16 == 0) break;
    piVar8 = &local_40;
    uVar17 = (*ui_poll_callback)();
    local_44 = (uint)uVar17;
  } while ((uVar17 & 2) == 0);
  local_44 = (uint)uVar17;
  uVar16 = CONCAT44((int)(uVar17 >> 0x20),local_40);
  if ((uVar17 & 2) == 0) goto code_r0x00019a4e;
  local_2c = 0;
  iVar6 = hit_test_menus(local_3c,local_40,local_6c,iStack_1c,local_9c + 8,aiStack_c4 + 2,&local_50,
                         &local_54);
  if (iVar6 == 0) {
    drawshape(local_28,local_20,local_34);
    for (iVar6 = iStack_1c; 0 < iVar6; iVar6 = iVar6 + -1) {
      local_9c[iVar6 + 4] = 0;
      if (local_9c[iVar6] != 0) {
        drawshape(local_9c[iVar6],aiStack_c4[iVar6 * 2 + 2],aiStack_c4[iVar6 * 2 + 3]);
        aiStack_c4[iVar6 * 2 + 3] = 0;
        aiStack_c4[iVar6 * 2 + 2] = 0;
        freemem(local_9c[iVar6]);
      }
    }
    iStack_1c = 0;
    local_6c[3] = (int *)0x0;
    local_6c[2] = (int *)0x0;
    local_6c[1] = (int *)0x0;
    local_9c[3] = 0;
    local_9c[2] = 0;
    local_9c[1] = 0;
    local_9c[0] = 0;
    local_9c[7] = 0;
    local_9c[6] = 0;
    local_9c[5] = 0;
    local_9c[0xb] = 0;
    local_9c[10] = 0;
    local_9c[9] = 0;
  }
  else if (local_6c[local_50][local_54 * 8 + 5] == 0) {
    if (local_6c[local_50][local_54 * 8 + 6] != 0) {
      drawshape(local_28,local_20,local_34);
      iVar6 = iStack_1c;
      if (iStack_1c != local_50) {
        for (; local_50 < iVar6; iVar6 = iVar6 + -1) {
          local_9c[iVar6 + 4] = 0;
          if (local_9c[iVar6] != 0) {
            drawshape(local_9c[iVar6],aiStack_c4[iVar6 * 2 + 2],aiStack_c4[iVar6 * 2 + 3]);
            aiStack_c4[iVar6 * 2 + 3] = 0;
            aiStack_c4[iVar6 * 2 + 2] = 0;
            freemem(local_9c[iVar6]);
            local_9c[iVar6] = 0;
            local_6c[iVar6] = (int *)0x0;
            local_9c[iVar6 + 8] = 0;
          }
        }
        iStack_1c = local_50;
      }
      iVar3 = iStack_1c;
      menu_item_draw_normal
                (local_6c[iStack_1c] + local_9c[iStack_1c + 4] * 8,aiStack_c4[iStack_1c * 2 + 2],
                 aiStack_c4[iStack_1c * 2 + 3],0xfa,0xf9,0xf8);
      iVar6 = local_54;
      local_9c[iVar3 + 4] = local_54;
      menu_item_draw_selected
                (local_6c[iVar3] + iVar6 * 8,aiStack_c4[iVar3 * 2 + 2],aiStack_c4[iVar3 * 2 + 3],
                 0xfa,0xf9,0xf8);
      iVar1 = local_50;
      iVar10 = local_54;
      iVar6 = iVar3 + 1;
      iStack_1c = iVar6;
      local_6c[iVar6] = (int *)local_6c[local_50][local_54 * 8 + 6];
      piVar8 = local_6c[iVar1] + iVar10 * 8;
      local_9c[iVar3 + 9] = piVar8[7];
      if (iVar6 == 1) {
        iVar6 = *piVar8;
      }
      else {
        iVar6 = piVar8[2];
      }
      aiStack_c4[iStack_1c * 2 + 2] = iVar6 + aiStack_c4[iStack_1c * 2];
      if (iStack_1c == 1) {
        iVar6 = local_6c[local_50][local_54 * 8 + 3];
      }
      else {
        iVar6 = local_6c[local_50][local_54 * 8 + 1];
      }
      iStack_24 = iStack_1c * 8;
      aiStack_c4[iStack_1c * 2 + 3] = iVar6 + aiStack_c4[iStack_1c * 2 + 1];
      iVar1 = iStack_1c;
      piVar8 = local_6c[iStack_1c];
      local_5c = (piVar8[local_9c[iStack_1c + 8] * 8 + -6] - *piVar8) + 1;
      local_58 = (piVar8[local_9c[iStack_1c + 8] * 8 + -5] - piVar8[1]) + 1;
      puVar7 = (undefined4 *)allocmem(aMenubuff,local_5c * local_58 + 0x11,0x20);
      local_9c[iVar1] = (int)puVar7;
      puVar12 = puVar7 + (uint)bVar15 * -2 + 1;
      puVar11 = pointer_shapes + (uint)bVar15 * -2 + 1;
      *puVar7 = *pointer_shapes;
      puVar13 = puVar12 + (uint)bVar15 * -2 + 1;
      puVar7 = puVar11 + (uint)bVar15 * -2 + 1;
      *puVar12 = *puVar11;
      *puVar13 = *puVar7;
      puVar13[(uint)bVar15 * -2 + 1] = puVar7[(uint)bVar15 * -2 + 1];
      *(undefined *)(puVar13 + (uint)bVar15 * -2 + 1 + (uint)bVar15 * -2 + 1) =
           *(undefined *)(puVar7 + (uint)bVar15 * -2 + 1 + (uint)bVar15 * -2 + 1);
      *(short *)(local_9c[iVar1] + 4) = (short)local_5c;
      *(short *)(local_9c[iVar1] + 6) = (short)local_58;
      grabshape(local_9c[iVar1],*(undefined4 *)((int)aiStack_c4 + iStack_24 + 8),
                *(undefined4 *)((int)aiStack_c4 + iStack_24 + 0xc));
      draw_menu(local_6c[iVar1],local_9c[iVar1 + 8],*(undefined4 *)((int)aiStack_c4 + iStack_24 + 8)
                ,*(undefined4 *)((int)aiStack_c4 + iStack_24 + 0xc),0xfa,0xf9,0xf8);
      local_9c[iVar1 + 4] = 0;
      iVar6 = *(int *)((int)aiStack_c4 + iStack_24 + 0xc);
      iVar10 = *(int *)((int)aiStack_c4 + iStack_24 + 8);
      piVar8 = local_6c[iVar1];
      goto LAB_0001a0c7;
    }
    drawshape(local_28,local_20,local_34);
  }
  else if (local_54 == local_9c[local_50 + 4]) {
    drawshape(local_28,local_20,local_34);
    for (iVar6 = iStack_1c; 0 < iVar6; iVar6 = iVar6 + -1) {
      local_9c[iVar6 + 4] = 0;
      if (local_9c[iVar6] != 0) {
        drawshape(local_9c[iVar6],aiStack_c4[iVar6 * 2 + 2],aiStack_c4[iVar6 * 2 + 3]);
        aiStack_c4[iVar6 * 2 + 3] = 0;
        aiStack_c4[iVar6 * 2 + 2] = 0;
        freemem(local_9c[iVar6]);
      }
    }
    iStack_1c = 0;
    dword_dc88c = local_3c;
    dword_dc888 = local_40;
    local_44 = (*(code *)local_6c[local_50][local_54 * 8 + 5])();
    local_3c = dword_dc88c;
    local_40 = dword_dc888;
    local_6c[3] = (int *)0x0;
    local_6c[2] = (int *)0x0;
    local_6c[1] = (int *)0x0;
    local_9c[3] = 0;
    local_9c[2] = 0;
    local_9c[1] = 0;
    local_9c[0] = 0;
    local_9c[7] = 0;
    local_9c[6] = 0;
    local_9c[5] = 0;
    local_9c[0xb] = 0;
    local_9c[10] = 0;
    local_9c[9] = 0;
    if ((local_44 == 1) || (local_44 == 5)) {
      event_queue_reset();
      ui_shutdown();
      setfontstate(auStack_11c);
      setmouselimits(0,0,0x280,0x1e0);
      dword_c5840 = 0;
      setmousepos(local_48,local_4c);
      getpalette(0,0x100,auStack_41c);
      if ((sound_enabled != '\0') && (dword_c721d != 0)) {
        sound_fade(dword_d2431,3,100);
      }
      if (((local_44 == 1) && (sound_enabled != '\0')) && ((option_flags._1_1_ & 1) != 0)) {
        speech_stop_channels();
        say_nowback_int();
      }
      fade_palette(1,auStack_41c,0x14);
      if (local_44 != 1) {
        dword_c53f7 = 2;
      }
      set_hub_title(dword_c53fb);
      if (local_28 != (undefined4 *)0x0) {
        freemem(local_28);
      }
      if ((sound_enabled != '\0') && (dword_c721d != 0)) {
        do {
          iVar6 = sound_channel_status(ram0x000d242c >> 0x18,3);
        } while (iVar6 == 0);
        releasememblock(dword_c721d);
        dword_c721d = 0;
      }
      if (local_44 == 1) {
        reload_match_graphics();
      }
      if (((local_44 == 1) && (sound_enabled != '\0')) && ((option_flags._1_1_ & 1) != 0)) {
        do {
          iVar6 = speech_clip_pending();
        } while (iVar6 != 0);
        release_nowback_int();
      }
LAB_00019a00:
      return (ulonglong)unaff_EDX << 0x20;
    }
    if (local_44 == 2) {
      getpalette(0,0x100,auStack_41c);
      fade_palette(1,auStack_41c,0x10);
      ensure_free_memory(700000);
      puVar9 = install_path;
      if ((&unk_ed830)[param_1] != '\x01') {
        puVar9 = (undefined *)0x0;
      }
      make_path(auStack_dc,puVar9,&unk_dc890,0);
      uVar4 = loadshapes(auStack_dc,0);
      uVar5 = locateshape(uVar4,&aDesk);
      drawshape_home(uVar5);
      iVar6 = locateshape(uVar4,&aPal_c097f);
      iVar10 = 0;
      do {
        auStack_41c[iVar10] = *(undefined *)(iVar6 + 0x10 + iVar10);
        iVar10 = iVar10 + 1;
      } while (iVar10 < 0x300);
      freemem(uVar4);
      draw_menu_items(local_6c[0],local_9c[8],0xfa,0xf9,0xf8);
      fade_palette(0,auStack_41c,0x10);
    }
    setmousepos(local_20,local_34);
    event_queue_reset();
  }
  else {
    drawshape(local_28,local_20,local_34);
    iVar6 = iStack_1c;
    if (iStack_1c != local_50) {
      for (; local_50 < iVar6; iVar6 = iVar6 + -1) {
        local_9c[iVar6 + 4] = 0;
        if (local_9c[iVar6] != 0) {
          drawshape(local_9c[iVar6],aiStack_c4[iVar6 * 2 + 2],aiStack_c4[iVar6 * 2 + 3]);
          aiStack_c4[iVar6 * 2 + 3] = 0;
          aiStack_c4[iVar6 * 2 + 2] = 0;
          freemem(local_9c[iVar6]);
          local_9c[iVar6] = 0;
          local_6c[iVar6] = (int *)0x0;
          local_9c[iVar6 + 8] = 0;
        }
      }
      iStack_1c = local_50;
    }
    menu_item_draw_normal
              (local_6c[local_50] + local_9c[local_50 + 4] * 8,aiStack_c4[local_50 * 2 + 2],
               aiStack_c4[local_50 * 2 + 3],0xfa,0xf9,0xf8);
    iVar1 = local_50;
    local_9c[local_50 + 4] = local_54;
    iVar6 = aiStack_c4[iVar1 * 2 + 3];
    iVar10 = aiStack_c4[iVar1 * 2 + 2];
    piVar8 = local_6c[iVar1] + local_9c[iVar1 + 4] * 8;
LAB_0001a0c7:
    menu_item_draw_selected(piVar8,iVar10,iVar6,0xfa,0xf9,0xf8);
  }
  grabshape(local_28,local_3c,local_40);
  piVar8 = local_3c;
  goto LAB_00019ad2;
code_r0x00019a4e:
  if ((local_3c != local_20) || (local_40 != local_34)) {
    local_2c = 0;
    drawshape(local_28,local_20,local_34);
    piVar8 = local_3c;
    grabshape(local_28,local_3c,local_40);
LAB_00019ad2:
    drawshape_remap(pointer_shapes,local_3c,local_40);
    uVar16 = CONCAT44(extraout_EDX,local_40);
    local_20 = local_3c;
    local_34 = local_40;
  }
  goto LAB_00019af6;
}


// ================================================================================================
// reload_match_graphics @ 0x1a534 [__watcall]
// ================================================================================================

void __watcall
reload_match_graphics
          (undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  int iVar1;
  
  __CHK(0x1c);
  if (user2_team._2_2_ < 0x1a) {
    iVar1 = user2_team >> 0x10;
  }
  else {
    iVar1 = 0xc;
  }
  load_rink(iVar1);
  load_sprite_banks();
  getpalette(0,0x100,&palette_save,unaff_EDX,unaff_ECX,unaff_EBX);
  fade_palette(1,&palette_save,0x10);
  dword_c66d4 = 1;
  dword_c66d0 = 1;
  return;
}


// ================================================================================================
// menu_back_to_game @ 0x1a5a1 [__watcall]
// ================================================================================================

undefined4 __watcall menu_back_to_game(void)

{
  __CHK(4);
  return 1;
}


// ================================================================================================
// pause_sports_desk @ 0x1a5b1 [__watcall]
// ================================================================================================

undefined8 __watcall pause_sports_desk(undefined4 param_1,undefined4 unaff_EDX)

{
  __CHK(8);
  dword_c66d4 = 1;
  dword_c66d0 = 1;
  return CONCAT44(unaff_EDX,5);
}


// ================================================================================================
// pause_sports_desk_confirm @ 0x1a5d4 [__watcall]
// ================================================================================================

undefined8 __watcall pause_sports_desk_confirm(undefined4 param_1,undefined4 unaff_EDX)

{
  int iVar1;
  undefined4 uVar2;
  undefined local_1c [4];
  undefined local_18 [4];
  undefined auStack_14 [4];
  
  __CHK(0x34);
  getmouse(auStack_14,local_18,local_1c);
  if (dword_c53fb == 0) {
    dword_c66a4 = aReturningToSportsCentral;
  }
  else if (dword_c53fb < 2) {
    dword_c66a4 = aReturningToThePlayoffTre;
  }
  else if (dword_c53fb == 2) {
    dword_c66a4 = aReturningOutOfTheGame;
  }
  dword_c66ac = aDoYouWishToReturn;
  set_dialog_colors(0xf9,0xfa,0xf8,0xfa,0);
  iVar1 = message_dialog(0xffffffff,0xffffffff,&dword_c66a4,3,&unk_d2b38,2,auStack_14,local_18,
                         0xffffffff);
  if (iVar1 < 1) {
    uVar2 = 0;
  }
  else {
    dword_c66d4 = 1;
    dword_c66d0 = 1;
    uVar2 = 5;
  }
  return CONCAT44(unaff_EDX,uVar2);
}


// ================================================================================================
// exit_game_dialog @ 0x1a6a7 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

longlong __watcall exit_game_dialog(undefined4 param_1,uint unaff_EDX)

{
  int iVar1;
  int local_20;
  undefined local_1c [4];
  undefined auStack_18 [4];
  
  __CHK(0x38);
  if ((sound_enabled != '\0') && (dword_c721d != 0)) {
    sound_fade(dword_d2431,3,100);
  }
  getmouse(auStack_18,local_1c,&local_20);
  dword_c66a4 = aExitingTheGame;
  dword_c66ac = aDoYouWishToExit;
  set_dialog_colors(0xf9,0xfa,0xf8,0xfa,0);
  local_20 = message_dialog(0xffffffff,0xffffffff,&dword_c66a4,3,&unk_d2b38,2,auStack_18,local_1c,
                            0xffffffff);
  if (0 < local_20) {
    getpalette(0,0x100,&palette_save);
    fade_palette(1,&palette_save,0x10);
    setdefaultscreen();
    clearclip(0);
    if ((sound_enabled != '\0') && (dword_c721d != 0)) {
      do {
        iVar1 = sound_channel_status(ram0x000d242c >> 0x18,3);
      } while (iVar1 == 0);
      releasememblock(dword_c721d);
      dword_c721d = 0;
    }
    loading_screen();
    free_match_resources();
    credits_screen();
    getpalette(0,0x100,&palette_save);
    fade_palette(1,&palette_save,0x10);
    settextmode();
    (*(code *)funcptr_d41f0)();
  }
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// menu_go_to_replay @ 0x1a817 [__watcall]
// ================================================================================================

undefined8 __watcall
menu_go_to_replay(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  int iVar1;
  
  __CHK(0x1c);
  if (user2_team._2_2_ < 0x1a) {
    iVar1 = user2_team >> 0x10;
  }
  else {
    iVar1 = 0xc;
  }
  load_rink(iVar1);
  load_sprite_banks();
  getpalette(0,0x100,&palette_save,unaff_EDX,unaff_ECX,unaff_EBX);
  fade_palette_to(1,&palette_save,0x10);
  set_video_mode(0x140,200);
  instant_replay(0);
  setfont(font_current_default);
  dword_c66d4 = 1;
  dword_c66d0 = 1;
  return CONCAT44(unaff_EDX,2);
}


// ================================================================================================
// menu_edit_lines_home @ 0x1a8aa [__watcall]
// ================================================================================================

undefined8 __watcall
menu_edit_lines_home
          (undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  __CHK(0x1c);
  getpalette(0,0x100,&palette_save,unaff_EDX,unaff_ECX,unaff_EBX);
  fade_palette(1,&palette_save,0x10);
  edit_lines_screen_b(0,&unk_dc200,&unk_cf2ef,2);
  getpalette(0,0x100,&palette_save);
  fade_palette(1,&palette_save,0x10);
  return CONCAT44(unaff_EDX,2);
}


// ================================================================================================
// menu_edit_lines_away @ 0x1a922 [__watcall]
// ================================================================================================

undefined8 __watcall
menu_edit_lines_away
          (undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  __CHK(0x1c);
  getpalette(0,0x100,&palette_save,unaff_EDX,unaff_ECX,unaff_EBX);
  fade_palette(1,&palette_save,0x10);
  edit_lines_screen_b(1,&unk_dabf0,&unk_cf2ef,2);
  getpalette(0,0x100,&palette_save);
  fade_palette(1,&palette_save,0x10);
  return CONCAT44(unaff_EDX,2);
}


// ================================================================================================
// menu_game_statistics @ 0x1a96d [__watcall]
// ================================================================================================

undefined8 __watcall
menu_game_statistics
          (undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  __CHK(0x1c);
  getpalette(0,0x100,&palette_save,unaff_EDX,unaff_ECX,unaff_EBX);
  fade_palette(1,&palette_save,0x10);
  game_statistics_screen();
  return CONCAT44(unaff_EDX,2);
}


// ================================================================================================
// menu_penalty_summary @ 0x1a9ac [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 __watcall menu_penalty_summary(undefined4 param_1,undefined4 unaff_EDX)

{
  int iVar1;
  
  __CHK(0x20);
  getpalette(0,0x100,&palette_save);
  if ((sound_enabled != '\0') && (dword_c721d != 0)) {
    sound_fade(dword_d2431,3,100);
  }
  fade_palette(1,&palette_save,0x10);
  if ((sound_enabled != '\0') && (dword_c721d != 0)) {
    do {
      iVar1 = sound_channel_status(ram0x000d242c >> 0x18,3);
    } while (iVar1 == 0);
    releasememblock(dword_c721d);
    dword_c721d = 0;
  }
  loading_screen();
  boxscore_screen(2,1,_period_num,0);
  return CONCAT44(unaff_EDX,2);
}


// ================================================================================================
// menu_scoring_summary @ 0x1aa6d [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 __watcall
menu_scoring_summary
          (undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  __CHK(0x1c);
  getpalette(0,0x100,&palette_save,unaff_EDX,unaff_ECX,unaff_EBX);
  fade_palette(1,&palette_save,0x10);
  loading_screen();
  boxscore_screen(1,1,_period_num,0);
  return CONCAT44(unaff_EDX,2);
}


// ================================================================================================
// menu_team_scratches @ 0x1aac4 [__watcall]
// ================================================================================================

undefined8 __watcall
menu_team_scratches(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,
                   undefined4 unaff_ECX)

{
  __CHK(0x1c);
  getpalette(0,0x100,&palette_save,unaff_EDX,unaff_ECX,unaff_EBX);
  fade_palette(1,&palette_save);
  loading_screen();
  boxscore_screen(4,0,0,0);
  return CONCAT44(unaff_EDX,2);
}


// ================================================================================================
// menu_home_goalie1 @ 0x1ab0b [__watcall]
// ================================================================================================

longlong __watcall menu_home_goalie1(undefined4 param_1,uint unaff_EDX)

{
  __CHK(8);
  choose_goalie(0,0);
  *off_cee5f = 1;
  *off_cee7f = 2;
  *off_cee9f = 2;
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// menu_home_goalie2 @ 0x1ab39 [__watcall]
// ================================================================================================

longlong __watcall menu_home_goalie2(undefined4 param_1,uint unaff_EDX)

{
  __CHK(8);
  choose_goalie(0,1);
  *off_cee5f = 2;
  *off_cee7f = 1;
  *off_cee9f = 2;
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// menu_home_no_goalie @ 0x1ab62 [__watcall]
// ================================================================================================

longlong __watcall menu_home_no_goalie(undefined4 param_1,uint unaff_EDX)

{
  __CHK(8);
  choose_goalie(0,0xffffffff);
  *off_cee5f = 2;
  *off_cee7f = 2;
  *off_cee9f = 1;
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// menu_away_goalie1 @ 0x1ab95 [__watcall]
// ================================================================================================

longlong __watcall menu_away_goalie1(undefined4 param_1,uint unaff_EDX)

{
  __CHK(8);
  choose_goalie(1,0);
  *off_ceebf = 1;
  *off_ceedf = 2;
  *off_ceeff = 2;
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// menu_away_goalie2 @ 0x1abc8 [__watcall]
// ================================================================================================

longlong __watcall menu_away_goalie2(undefined4 param_1,uint unaff_EDX)

{
  __CHK(8);
  choose_goalie(1);
  *off_ceebf = 2;
  *off_ceedf = 1;
  *off_ceeff = 2;
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// menu_away_no_goalie @ 0x1abf1 [__watcall]
// ================================================================================================

longlong __watcall menu_away_no_goalie(undefined4 param_1,uint unaff_EDX)

{
  __CHK(8);
  choose_goalie(1,0xffffffff);
  *off_ceebf = 2;
  *off_ceedf = 2;
  *off_ceeff = 1;
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// cmv_alloc @ 0x1ac25 [__watcall]
// ================================================================================================

void __watcall cmv_alloc(void)

{
  undefined4 *puVar1;
  
  __CHK(0x1c);
  puVar1 = (undefined4 *)allocmem_try();
  if (puVar1 != (undefined4 *)0x0) {
    *puVar1 = 0;
    puVar1[1] = 0;
    puVar1[2] = 0;
    puVar1[3] = 0;
    puVar1[4] = 0;
    puVar1[5] = 0;
    puVar1[6] = 0;
    puVar1[7] = 0;
    puVar1[8] = 0;
    puVar1[9] = 0;
    puVar1[10] = 0;
  }
  return;
}


// ================================================================================================
// cmv_free_buffers @ 0x1ac9a [__watcall]
// ================================================================================================

void __watcall cmv_free_buffers(int param_1)

{
  __CHK(0x1c);
  if (*(int *)(param_1 + 0x1c) != 0) {
    freemem(*(int *)(param_1 + 0x1c));
  }
  if (*(int *)(param_1 + 0x20) != 0) {
    removewindow_free(*(int *)(param_1 + 0x20));
  }
  if (*(int *)(param_1 + 0x24) != 0) {
    removewindow_free(*(int *)(param_1 + 0x24));
  }
  if (*(int *)(param_1 + 0x28) != 0) {
    removewindow_free(*(int *)(param_1 + 0x28));
  }
  return;
}


// ================================================================================================
// cmv_free @ 0x1acf1 [__watcall]
// ================================================================================================

void __watcall cmv_free(int param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  undefined4 extraout_EDX;
  
  __CHK(0x14);
  if (param_1 != 0) {
    cmv_free_buffers(param_1,param_1,unaff_EBX,unaff_ECX,unaff_EDX,unaff_ECX,unaff_EBX);
    freemem(extraout_EDX);
  }
  return;
}


// ================================================================================================
// cmv_load_palette @ 0x1ad16 [__watcall]
// ================================================================================================

void __watcall cmv_load_palette(uint *param_1,int unaff_EDX)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  byte *pbVar5;
  
  __CHK(0x28);
  cmv_free_buffers();
  *param_1 = (uint)*(byte *)(unaff_EDX + 10);
  *param_1 = *param_1 + (uint)*(byte *)(unaff_EDX + 0xb) * 0x100;
  param_1[1] = (uint)*(byte *)(unaff_EDX + 0xc);
  param_1[1] = param_1[1] + (uint)*(byte *)(unaff_EDX + 0xd) * 0x100;
  param_1[2] = (uint)*(byte *)(unaff_EDX + 0xe);
  param_1[2] = param_1[2] + (uint)*(byte *)(unaff_EDX + 0xf) * 0x100;
  param_1[4] = (uint)*(byte *)(unaff_EDX + 0x10);
  param_1[4] = param_1[4] + (uint)*(byte *)(unaff_EDX + 0x11) * 0x100;
  param_1[3] = (uint)*(byte *)(unaff_EDX + 0x12);
  param_1[3] = param_1[3] + (uint)*(byte *)(unaff_EDX + 0x13) * 0x100;
  param_1[5] = (uint)*(byte *)(unaff_EDX + 0x14);
  param_1[5] = param_1[5] + (uint)*(byte *)(unaff_EDX + 0x15) * 0x100;
  param_1[6] = (uint)*(byte *)(unaff_EDX + 0x16);
  pbVar5 = (byte *)(unaff_EDX + 0x18);
  uVar4 = param_1[6] + (uint)*(byte *)(unaff_EDX + 0x17) * 0x100;
  param_1[6] = uVar4;
  iVar2 = uVar4 * 3;
  uVar4 = allocmem(aCmvPalette,iVar2,0);
  param_1[7] = uVar4;
  for (iVar3 = 0; iVar3 < iVar2; iVar3 = iVar3 + 1) {
    bVar1 = *pbVar5;
    pbVar5 = pbVar5 + 1;
    *(char *)(param_1[7] + iVar3) = (char)((int)(uint)bVar1 >> 2);
  }
  uVar4 = windowdefp(param_1[1],param_1[2],0);
  param_1[8] = uVar4;
  uVar4 = windowdefp(param_1[1],param_1[2],0);
  param_1[9] = uVar4;
  uVar4 = windowdefp(param_1[1],param_1[2],0);
  param_1[10] = uVar4;
  iVar2 = *(int *)(param_1[8] + 0x20);
  uVar4 = 0;
  do {
    param_1[uVar4 + 0xb] = ((uVar4 & 0xf) - 7) + (((int)uVar4 >> 4 & 0xfU) - 7) * iVar2;
    uVar4 = uVar4 + 1;
  } while ((int)uVar4 < 0x100);
  return;
}


// ================================================================================================
// cmv_decode_frame @ 0x1ae6b [__watcall]
// ================================================================================================

void __watcall cmv_decode_frame(int param_1,byte *unaff_EDX,byte *unaff_EBX)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  byte *pbVar11;
  undefined4 *puVar12;
  undefined4 *puVar13;
  undefined4 *puVar14;
  int local_3c;
  int local_1c;
  
  __CHK(0x4c);
  iVar1 = *(int *)(param_1 + 0x20);
  iVar2 = *(int *)(iVar1 + 0x2c);
  iVar3 = *(int *)(*(int *)(param_1 + 0x24) + 0x2c);
  iVar4 = *(int *)(*(int *)(param_1 + 0x28) + 0x2c);
  iVar5 = *(int *)(iVar1 + 0x20);
  iVar6 = *(int *)(param_1 + 4);
  iVar7 = iVar6 * 2;
  iVar8 = iVar6 * 3;
  puVar9 = (undefined4 *)(iVar2 + **(int **)(iVar1 + 0x28));
  for (local_3c = *(int *)(param_1 + 8); local_1c = iVar6, 0 < local_3c; local_3c = local_3c + -4) {
    for (; 0 < local_1c; local_1c = local_1c + -4) {
      puVar12 = (undefined4 *)(iVar8 + (int)puVar9);
      puVar14 = (undefined4 *)(iVar7 + (int)puVar9);
      puVar13 = (undefined4 *)(iVar6 + (int)puVar9);
      if (*unaff_EDX == 0xff) {
        pbVar11 = unaff_EBX + 1;
        if (*unaff_EBX == 0xff) {
          *puVar9 = *(undefined4 *)pbVar11;
          *puVar13 = *(undefined4 *)(unaff_EBX + 5);
          *puVar14 = *(undefined4 *)(unaff_EBX + 9);
          *puVar12 = *(undefined4 *)(unaff_EBX + 0xd);
          pbVar11 = unaff_EBX + 0x11;
        }
        else {
          puVar10 = (undefined4 *)
                    ((int)puVar9 + *(int *)((uint)*unaff_EBX * 4 + param_1 + 0x2c) + (iVar4 - iVar2)
                    );
          *puVar9 = *puVar10;
          *puVar13 = *(undefined4 *)((int)puVar10 + iVar6);
          *puVar14 = *(undefined4 *)((int)puVar10 + iVar7);
          *puVar12 = *(undefined4 *)((int)puVar10 + iVar8);
        }
      }
      else {
        puVar10 = (undefined4 *)
                  ((int)puVar9 + *(int *)(param_1 + 0x2c + (uint)*unaff_EDX * 4) + (iVar3 - iVar2));
        *puVar9 = *puVar10;
        *puVar13 = *(undefined4 *)((int)puVar10 + iVar6);
        *puVar14 = *(undefined4 *)((int)puVar10 + iVar7);
        *puVar12 = *(undefined4 *)((int)puVar10 + iVar8);
        pbVar11 = unaff_EBX;
      }
      puVar9 = puVar9 + 1;
      unaff_EDX = unaff_EDX + 1;
      unaff_EBX = pbVar11;
    }
    puVar9 = (undefined4 *)((int)puVar9 + iVar5 * 3);
  }
  return;
}


// ================================================================================================
// cmv_next_frame @ 0x1b002 [__watcall]
// ================================================================================================

undefined4 __watcall cmv_next_frame(int param_1,int unaff_EDX)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  __CHK(0x24);
  iVar4 = *(int *)(param_1 + 4);
  iVar2 = *(int *)(param_1 + 8);
  if (unaff_EDX == 0) {
    iVar4 = *(int *)(param_1 + 0x20);
  }
  else {
    iVar3 = *(int *)(param_1 + 0x28);
    *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x24);
    *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x20);
    *(int *)(param_1 + 0x20) = iVar3;
    iVar1 = unaff_EDX + 10;
    if (*(short *)(unaff_EDX + 8) == 0) {
      memmove_dwords(iVar1,*(int *)(iVar3 + 0x2c) + 0x10,iVar4 * iVar2);
    }
    else {
      cmv_decode_frame(param_1,iVar1,
                       iVar1 + ((int)((iVar2 + (iVar2 >> 0x1f) * -4) -
                                     (uint)((iVar2 >> 0x1f) << 1 < 0)) >> 2) *
                               ((int)((iVar4 + (iVar4 >> 0x1f) * -4) -
                                     (uint)((iVar4 >> 0x1f) << 1 < 0)) >> 2));
    }
    iVar4 = *(int *)(param_1 + 0x20);
  }
  return *(undefined4 *)(iVar4 + 0x2c);
}


// ================================================================================================
// cmv_field_00 @ 0x1b092 [__watcall]
// ================================================================================================

undefined4 __watcall cmv_field_00(undefined4 *param_1)

{
  __CHK(4);
  return *param_1;
}


// ================================================================================================
// cmv_field_04 @ 0x1b09f [__watcall]
// ================================================================================================

undefined4 __watcall cmv_field_04(int param_1)

{
  __CHK(4);
  return *(undefined4 *)(param_1 + 4);
}


// ================================================================================================
// cmv_field_08 @ 0x1b0ad [__watcall]
// ================================================================================================

undefined4 __watcall cmv_field_08(int param_1)

{
  __CHK(4);
  return *(undefined4 *)(param_1 + 8);
}


// ================================================================================================
// cmv_field_0c @ 0x1b0bb [__watcall]
// ================================================================================================

undefined4 __watcall cmv_field_0c(int param_1)

{
  __CHK(4);
  return *(undefined4 *)(param_1 + 0xc);
}


// ================================================================================================
// cmv_field_14 @ 0x1b0c9 [__watcall]
// ================================================================================================

undefined4 __watcall cmv_field_14(int param_1)

{
  __CHK(4);
  return *(undefined4 *)(param_1 + 0x14);
}


// ================================================================================================
// cmv_field_18 @ 0x1b0d7 [__watcall]
// ================================================================================================

undefined4 __watcall cmv_field_18(int param_1)

{
  __CHK(4);
  return *(undefined4 *)(param_1 + 0x18);
}


// ================================================================================================
// cmv_field_1c @ 0x1b0e5 [__watcall]
// ================================================================================================

undefined4 __watcall cmv_field_1c(int param_1)

{
  __CHK(4);
  return *(undefined4 *)(param_1 + 0x1c);
}


// ================================================================================================
// cdstream_open @ 0x1b0f3 [__cdecl]
// ================================================================================================

undefined4 * cdstream_open(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  
  __CHK(0x14);
  puVar1 = (undefined4 *)allocmem(aCDSTREAM,param_1 + 0x54,param_3);
  puVar1[8] = param_1;
  *puVar1 = puVar1 + 0x15;
  puVar1[1] = param_1 + (int)(puVar1 + 0x15);
  uVar2 = *puVar1;
  puVar1[5] = uVar2;
  puVar1[4] = uVar2;
  puVar1[2] = uVar2;
  puVar1[3] = uVar2;
  puVar1[9] = param_2;
  puVar1[6] = 0;
  dword_dc8a0 = puVar1;
  dword_dc8c8 = puVar1;
  puVar1[7] = 7;
  uVar2 = fixmul16(param_2,dword_c66b0);
  puVar1[0x14] = uVar2;
  puVar1[0x13] = 0;
  addtimer(cdstream_timer);
  return puVar1;
}


// ================================================================================================
// cdstream_close @ 0x1b18b [__cdecl]
// ================================================================================================

void cdstream_close(int param_1)

{
  __CHK(0xc);
  removetimer(cdstream_timer);
  if (*(int *)(param_1 + 0x18) != 0) {
    closehandle(*(int *)(param_1 + 0x18));
  }
  freemem(param_1);
  return;
}


// ================================================================================================
// cdstream_set_handler @ 0x1b1c2 [__cdecl]
// ================================================================================================

void cdstream_set_handler(int param_1,undefined4 param_2)

{
  __CHK(4);
  *(undefined4 *)(param_1 + 0x48) = param_2;
  *(undefined4 *)(param_1 + 0x1c) = 1;
  return;
}


// ================================================================================================
// cdstream_stub @ 0x1b1df [__watcall]
// ================================================================================================

void __watcall cdstream_stub(void)

{
  int in_stack_00000004;
  int in_stack_00000008;
  
  __CHK(4);
  *(int *)(in_stack_00000004 + 0x44) = *(int *)(in_stack_00000004 + 0x34) + in_stack_00000008;
  *(undefined4 *)(in_stack_00000004 + 0x1c) = 2;
  return;
}


// ================================================================================================
// cdstream_open_secondary @ 0x1b201 [__watcall]
// ================================================================================================

void __watcall cdstream_open_secondary(void)

{
  int iVar1;
  int *piVar2;
  int in_stack_00000004;
  int in_stack_00000008;
  undefined4 in_stack_0000000c;
  
  __CHK(0x10);
  if ((in_stack_00000004 < 0) || (9 < in_stack_00000004)) {
    fatalerror(aIllegalSecondaryStreamNu);
  }
  piVar2 = (int *)allocmem(aSECCDSTREAM,in_stack_00000008 + 0x54,in_stack_0000000c);
  piVar2[8] = in_stack_00000008;
  *piVar2 = (int)(piVar2 + 0x15);
  piVar2[1] = in_stack_00000008 + (int)(piVar2 + 0x15);
  iVar1 = *piVar2;
  piVar2[5] = iVar1;
  piVar2[4] = iVar1;
  piVar2[2] = iVar1;
  piVar2[3] = iVar1;
  piVar2[9] = 0;
  piVar2[0x10] = 0;
  piVar2[0xe] = 1;
  (&dword_dc8a0)[in_stack_00000004] = piVar2;
  return;
}


// ================================================================================================
// iff_parse @ 0x1b2a7 [__watcall]
// ================================================================================================

void __watcall iff_parse(void)

{
  int *piVar1;
  int iVar2;
  undefined8 uVar3;
  
  __CHK(0x20);
  do {
    if (0 < dword_dc8a0[0x13]) {
      return;
    }
    switch(dword_dc8a0[7]) {
    case 1:
      if (dword_dc8a0[6] != 0) {
        closehandle(dword_dc8a0[6]);
      }
      dos_open_fatal(dword_dc8a0[0x12],dword_dc8a0 + 6,dword_dc8a0 + 0xd,dword_dc8a0 + 0xf);
      dword_dc8a0[0x11] = dword_dc8a0[0xd];
      dword_dc8a0[0xe] = dword_dc8a0[0xd] + dword_dc8a0[0xf];
      dword_dc8a0[7] = 2;
switchD_0001b2cd_caseD_2:
      uVar3 = iff_buffer_fill(dword_dc8a0);
      if ((int)uVar3 < *(int *)((int)((ulonglong)uVar3 >> 0x20) + 0x24)) {
        return;
      }
      dword_dc8a0[7] = 3;
      dword_dc8a0[2] = dword_dc8a0[3];
      dword_dc8a0[0x10] = dword_dc8a0[0x11];
      seekhandle(dword_dc8a0[6],dword_dc8a0[0x10]);
      dword_dc8a0[0xc] = 0;
      iVar2 = fixmul16(dword_dc8a0[9],dword_c66b0);
      dword_dc8a0[0x13] = iVar2;
      return;
    case 2:
      goto switchD_0001b2cd_caseD_2;
    case 3:
      if ((uint)dword_dc8a0[0xc] < 8) {
        uVar3 = iff_buffer_fill(dword_dc8a0);
        if ((int)uVar3 < *(int *)((int)((ulonglong)uVar3 >> 0x20) + 0x24)) {
          return;
        }
        iVar2 = dword_dc8a0[0x13];
        dos_read_blocks(dword_dc8a0[6],dword_dc8a0[2],dword_dc8a0[9]);
        dword_dc8a0[0x13] = iVar2;
        iVar2 = fixmul16(dword_dc8a0[9],dword_c66b0);
        dword_dc8a0[0x13] = iVar2;
        dword_dc8a0[2] = dword_dc8a0[2] + dword_dc8a0[9];
        dword_dc8a0[0x10] = dword_dc8a0[0x10] + dword_dc8a0[9];
        dword_dc8a0[0xc] = dword_dc8a0[0xc] + dword_dc8a0[9];
      }
      dword_dc8a0[0xb] = *(int *)(dword_dc8a0[3] + 4);
      dword_dc8a0[10] = dword_dc8a0[0xb] - dword_dc8a0[0xc];
      iVar2 = *(char *)dword_dc8a0[3] + -0x30;
      dword_dc8c8 = dword_dc8a0;
      if ((0 < iVar2) && (iVar2 < 9)) {
        dword_dc8c8 = (&dword_dc8a0)[iVar2];
      }
      if (dword_dc8c8 == (int *)0x0) {
        dword_dc8c8 = dword_dc8a0;
      }
      if (((uint)dword_dc8a0[0xb] < 8) || (dword_dc8c8[8] < dword_dc8a0[0xb])) {
        fatalerror(aIllegalChunkSizeDBuffers,dword_dc8a0[0xb],dword_dc8c8[8]);
      }
    case 4:
      if (dword_dc8c8 != dword_dc8a0) {
        dword_dc8a0[7] = 4;
        uVar3 = iff_buffer_fill(dword_dc8c8,dword_dc8a0[9] + 8);
        if ((uint)uVar3 < (uint)((ulonglong)uVar3 >> 0x20)) {
          return;
        }
        uVar3 = iff_buffer_skip(dword_dc8c8,dword_dc8a0[0xb] + dword_dc8a0[9]);
        if ((uint)uVar3 < (int)((ulonglong)uVar3 >> 0x20) + 8U) {
          *(undefined4 *)dword_dc8c8[3] = 0xffffffff;
          iVar2 = *dword_dc8c8;
          dword_dc8c8[3] = iVar2;
          dword_dc8c8[2] = iVar2;
          break;
        }
        if (dword_dc8a0[10] < 0) {
          memmove_dwords(dword_dc8a0[3],dword_dc8c8[3],dword_dc8a0[0xb]);
          dword_dc8c8[2] = dword_dc8c8[3] + dword_dc8a0[0xb];
          dword_dc8a0[0xc] = -dword_dc8a0[10];
          memmove_dwords(dword_dc8a0[0xb] + dword_dc8a0[3],dword_dc8a0[3],dword_dc8a0[0xc]);
          dword_dc8a0[2] = dword_dc8a0[2] - dword_dc8a0[0xb];
        }
        else {
          memmove_dwords(dword_dc8a0[3],dword_dc8c8[3],dword_dc8a0[0xc]);
          dword_dc8c8[2] = dword_dc8c8[3] + dword_dc8a0[0xc];
          dword_dc8a0[2] = dword_dc8a0[3];
          dword_dc8a0[0xc] = 0;
        }
      }
switchD_0001b2cd_caseD_5:
      if ((0 < dword_dc8a0[10]) &&
         (uVar3 = iff_buffer_skip(dword_dc8c8,dword_dc8a0[10] + dword_dc8a0[9]),
         (uint)uVar3 < (int)((ulonglong)uVar3 >> 0x20) + 8U)) {
        dword_dc8a0[7] = 5;
        uVar3 = iff_buffer_avail(dword_dc8c8,dword_dc8a0);
        if ((int)uVar3 < *(int *)((int)((ulonglong)uVar3 >> 0x20) + 0x30)) {
          return;
        }
        memmove_dwords(dword_dc8c8[3],*dword_dc8c8,dword_dc8a0[0xc]);
        *(undefined4 *)dword_dc8c8[3] = 0xffffffff;
        dword_dc8c8[2] = *dword_dc8c8 + dword_dc8a0[0xc];
        dword_dc8c8[3] = *dword_dc8c8;
      }
switchD_0001b2cd_caseD_6:
      dword_dc8a0[7] = 6;
      if (0 < dword_dc8a0[10]) {
        uVar3 = iff_buffer_fill(dword_dc8c8);
        if ((int)uVar3 < *(int *)((int)((ulonglong)uVar3 >> 0x20) + 0x24)) {
          return;
        }
        iVar2 = dword_dc8a0[0x13];
        dos_read_blocks(dword_dc8a0[6],dword_dc8c8[2],dword_dc8a0[9]);
        dword_dc8a0[0x13] = iVar2;
        piVar1 = dword_dc8a0;
        iVar2 = fixmul16(dword_dc8a0[9],dword_c66b0);
        piVar1[0x13] = piVar1[0x13] + iVar2;
        dword_dc8a0[0x10] = dword_dc8a0[0x10] + dword_dc8a0[9];
        dword_dc8c8[2] = dword_dc8c8[2] + dword_dc8a0[9];
        dword_dc8a0[10] = dword_dc8a0[10] - dword_dc8a0[9];
        return;
      }
      dword_dc8c8[3] = dword_dc8c8[3] + dword_dc8a0[0xb];
      if (dword_dc8c8 == dword_dc8a0) {
        dword_dc8a0[0xc] = dword_dc8c8[2] - dword_dc8c8[3];
      }
      else if (dword_dc8a0[0xc] == 0) {
        dword_dc8a0[0xc] = dword_dc8c8[2] - dword_dc8c8[3];
        memmove_dwords(dword_dc8c8[3],dword_dc8a0[3],dword_dc8a0[0xc]);
        dword_dc8c8[2] = dword_dc8c8[3];
        dword_dc8a0[2] = dword_dc8a0[3] + dword_dc8a0[0xc];
      }
switchD_0001b2cd_caseD_9:
      if (dword_dc8a0[0x10] - dword_dc8a0[0xc] < dword_dc8a0[0xe]) {
        dword_dc8a0[7] = 3;
      }
      else {
        dword_dc8a0[7] = 9;
        uVar3 = iff_buffer_fill(dword_dc8a0);
        if ((uint)((int)uVar3 + *(int *)((int)((ulonglong)uVar3 >> 0x20) + 0x30)) < 8) {
          return;
        }
        *(undefined4 *)dword_dc8a0[3] = 0xfffffffd;
        *(undefined4 *)(dword_dc8a0[3] + 4) = 8;
        dword_dc8a0[3] = dword_dc8a0[3] + 8;
        dword_dc8a0[2] = dword_dc8a0[3];
        dword_dc8a0[7] = 7;
      }
      break;
    case 5:
      goto switchD_0001b2cd_caseD_5;
    case 6:
      goto switchD_0001b2cd_caseD_6;
    case 7:
      dword_dc8a0[0x13] = 0;
      return;
    case 9:
      goto switchD_0001b2cd_caseD_9;
    }
  } while( true );
}


// ================================================================================================
// cdstream_timer @ 0x1b818 [__watcall]
// ================================================================================================

void __watcall cdstream_timer(void)

{
  __CHK(4);
  *(int *)(dword_dc8a0 + 0x4c) = *(int *)(dword_dc8a0 + 0x4c) + -1;
  return;
}


// ================================================================================================
// iff_buffer_fill @ 0x1b82b [__watcall]
// ================================================================================================

undefined8 __watcall iff_buffer_fill(int *param_1,undefined4 unaff_EDX)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  
  __CHK(0x14);
  piVar1 = (int *)param_1[5];
  if (piVar1 != (int *)param_1[4]) {
    if (*piVar1 == -2) {
      iVar3 = (int)piVar1 + piVar1[1];
    }
    else {
      if (*piVar1 != -1) goto LAB_0001b859;
      iVar3 = *param_1;
    }
    param_1[5] = iVar3;
  }
LAB_0001b859:
  uVar2 = param_1[5];
  if (uVar2 <= (uint)param_1[2]) {
    uVar2 = param_1[1];
  }
  return CONCAT44(unaff_EDX,uVar2 - param_1[2]);
}


// ================================================================================================
// iff_buffer_skip @ 0x1b871 [__watcall]
// ================================================================================================

undefined8 __watcall iff_buffer_skip(int param_1,undefined4 unaff_EDX)

{
  __CHK(0xc);
  return CONCAT44(unaff_EDX,*(int *)(param_1 + 4) - *(int *)(param_1 + 8));
}


// ================================================================================================
// iff_buffer_avail @ 0x1b88a [__watcall]
// ================================================================================================

longlong __watcall iff_buffer_avail(int *param_1,uint unaff_EDX)

{
  __CHK(0xc);
  if ((uint)param_1[5] <= (uint)param_1[2]) {
    return CONCAT44(unaff_EDX,param_1[5] - *param_1);
  }
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// iff_buffer_next_chunk @ 0x1b8ac [__watcall]
// ================================================================================================

int * __watcall iff_buffer_next_chunk(void)

{
  int iVar1;
  uint uVar2;
  int *piVar3;
  uint uVar4;
  undefined4 *in_stack_00000004;
  
  __CHK(0xc);
  iff_parse();
  piVar3 = (int *)in_stack_00000004[4];
  if ((int *)in_stack_00000004[3] == piVar3) {
    return (int *)((uint)in_stack_00000004[3] ^ (uint)piVar3);
  }
  if (*piVar3 == -1) {
    in_stack_00000004[4] = *in_stack_00000004;
    if (in_stack_00000004[3] == in_stack_00000004[4]) {
      return (int *)(in_stack_00000004[3] ^ in_stack_00000004[4]);
    }
  }
  uVar2 = in_stack_00000004[4];
  uVar4 = in_stack_00000004[3];
  if (uVar4 < uVar2) {
    uVar4 = in_stack_00000004[1];
  }
  if (*(int *)(uVar2 + 4) <= (int)(uVar4 - uVar2)) {
    piVar3 = (int *)in_stack_00000004[4];
    iVar1 = (int)piVar3 + *(int *)(uVar2 + 4);
    in_stack_00000004[4] = iVar1;
    if (*piVar3 == -3) {
      if (piVar3 == (int *)in_stack_00000004[5]) {
        in_stack_00000004[5] = iVar1;
      }
      else {
        *piVar3 = -2;
      }
      piVar3 = (int *)0xffffffff;
    }
    return piVar3;
  }
  return (int *)0x0;
}


// ================================================================================================
// iff_buffer_release_chunk @ 0x1b92e [__cdecl]
// ================================================================================================

void iff_buffer_release_chunk(undefined4 *param_1,int *param_2)

{
  __CHK(8);
  *param_2 = -2;
  if (param_2 == (int *)param_1[5]) {
    while (param_1[5] != param_1[3]) {
      if (*param_2 == -2) {
        param_1[5] = param_1[5] + param_2[1];
      }
      else {
        if (*param_2 != -1) {
          return;
        }
        if (param_1[5] == param_1[4]) {
          param_1[4] = *param_1;
        }
        param_1[5] = *param_1;
      }
      if (param_2[1] == 0) {
        return;
      }
      param_2 = (int *)param_1[5];
    }
  }
  return;
}


// ================================================================================================
// free_match_resources @ 0x1b982 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall free_match_resources(void)

{
  __CHK(0x20);
  sound_pause_all();
  set_game_over();
  if ((panel_clip >> 0x10 != -1) && (dword_e0244 != 0)) {
    freemem(dword_e0244);
    dword_e0244 = 0;
  }
  free_sprite_banks();
  if (rinkend_bank != 0) {
    freemem(rinkend_bank);
    rinkend_bank = 0;
  }
  if (numshp_bank != 0) {
    freemem(numshp_bank);
    numshp_bank = 0;
  }
  if (scoreboard_bank != 0) {
    freemem(scoreboard_bank);
    scoreboard_bank = 0;
  }
  if (dword_ed700 != 0) {
    freemem(dword_ed700);
    dword_ed700 = 0;
  }
  free_music_banks();
  if (dword_dc338 != 0) {
    freemem(dword_dc338);
    dword_dc338 = 0;
  }
  _input_enabled = 0;
  flush_key_events();
  setfont(font_current_default);
  dword_c7290 = 0x50;
  free_hilight_buffers();
  return;
}


// ================================================================================================
// free_effect_bank @ 0x1ba85 [__watcall]
// ================================================================================================

void __watcall
free_effect_bank(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  __CHK(0x14);
  if (effect_bank != 0) {
    freemem(effect_bank,unaff_EDX,unaff_ECX,unaff_EBX);
  }
  effect_bank = 0;
  return;
}


// ================================================================================================
// free_sprite_banks @ 0x1bab1 [__watcall]
// ================================================================================================

void __watcall free_sprite_banks(void)

{
  int iVar1;
  
  __CHK(0x1c);
  free_effect_bank();
  for (iVar1 = 0x16; -1 < iVar1; iVar1 = iVar1 + -1) {
    if ((&sprite_banks)[iVar1] != 0) {
      freemem((&sprite_banks)[iVar1]);
      (&sprite_banks)[iVar1] = 0;
    }
  }
  return;
}


// ================================================================================================
// ensure_free_memory @ 0x1baf3 [__watcall]
// ================================================================================================

undefined8 __watcall ensure_free_memory(int param_1,undefined4 unaff_EDX)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  __CHK(0x20);
  iVar1 = largest_free_locked();
  if (iVar1 < param_1) {
    if (dword_c73d4 != 0) {
      freemem(dword_c73d4);
      dword_c73d4 = 0;
    }
    iVar1 = largest_free_locked();
    if (iVar1 < param_1) {
      free_hilight_buffers();
      iVar1 = largest_free_locked();
      if (iVar1 < param_1) {
        if ((panel_clip >> 0x10 != -1) && (dword_e0244 != 0)) {
          freemem(dword_e0244);
          dword_e0244 = 0;
        }
        iVar1 = largest_free_locked();
        if (iVar1 < param_1) {
          free_effect_bank();
          for (iVar1 = 0x16; -1 < iVar1; iVar1 = iVar1 + -1) {
            iVar3 = largest_free_locked();
            if (param_1 <= iVar3) goto LAB_0001bb0e;
            if ((&sprite_banks)[iVar1] != 0) {
              freemem((&sprite_banks)[iVar1]);
              (&sprite_banks)[iVar1] = 0;
            }
          }
          iVar1 = largest_free_locked();
          if (iVar1 < param_1) {
            uVar2 = 0;
            goto LAB_0001ba7e;
          }
        }
      }
    }
  }
LAB_0001bb0e:
  uVar2 = 1;
LAB_0001ba7e:
  return CONCAT44(unaff_EDX,uVar2);
}


// ================================================================================================
// load_team_databases @ 0x1bbcc [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall load_team_databases(uint param_1)

{
  int iVar1;
  __off_t _Var2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  byte bVar5;
  char local_48 [32];
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  int iStack_18;
  
  bVar5 = 0;
  __CHK(0x88);
  sprintf(local_48,&byte_dd750,aTeams);
  iVar1 = _dos_findfirst(local_48,0);
  if (iVar1 != 0) {
    fatalerror(&a1);
  }
  iVar1 = file_open_read(local_48,&iStack_18);
  if (iVar1 != 0) {
    fatalerror(&a2_c0a20);
  }
  _Var2 = lseek(iStack_18,0,0);
  if (_Var2 != 0) {
    fatalerror(&a3);
  }
  _Var2 = lseek(iStack_18,user2_team._2_2_ * 0x2e8,0);
  if (_Var2 < 0) {
    fatalerror(&a4);
  }
  iVar1 = file_read(iStack_18,&team_names,0xffffffff,0x2e8);
  if (iVar1 != 0) {
    fatalerror(&a5);
  }
  file_close(&iStack_18);
  sprintf(local_48,&byte_dd710,aTeams);
  iVar1 = _dos_findfirst(local_48,0);
  if (iVar1 != 0) {
    fatalerror(&a1);
  }
  iVar1 = file_open_read(local_48,&iStack_18);
  if (iVar1 != 0) {
    fatalerror(&a2_c0a20);
  }
  _Var2 = lseek(iStack_18,0,0);
  if (_Var2 != 0) {
    fatalerror(&a3);
  }
  _Var2 = lseek(iStack_18,_away_team_id * 0x2e8,0);
  if (_Var2 < 0) {
    fatalerror(&a7);
  }
  iVar1 = file_read(iStack_18,&unk_dbf18,0xffffffff,0x2e8);
  if (iVar1 != 0) {
    fatalerror(&a8);
  }
  file_close(&iStack_18);
  db_open_files(param_1,&iStack_18,&local_1c,&local_20,&local_24,&byte_dd750,&local_28);
  db_load_team_roster(param_1,iStack_18,local_1c,local_20,local_24,local_28,0);
  file_close(&iStack_18);
  file_close(&local_1c);
  file_close(&local_20);
  if ((param_1 & 6) == 0) {
    file_close(&local_24);
  }
  db_open_files(param_1,&iStack_18,&local_1c,&local_20,&local_24,&byte_dd710,&local_28);
  db_load_team_roster(param_1,iStack_18,local_1c,local_20,local_24,local_28,1);
  file_close(&iStack_18);
  file_close(&local_1c);
  file_close(&local_20);
  if ((param_1 & 6) == 0) {
    file_close(&local_24);
  }
  if ((param_1 == 0) || (param_1 == 2)) {
    puVar3 = &unk_dbcec;
    puVar4 = &unk_dc200;
    for (iVar1 = 0xc; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar4 = *puVar3;
      puVar3 = puVar3 + (uint)bVar5 * -2 + 1;
      puVar4 = puVar4 + (uint)bVar5 * -2 + 1;
    }
    puVar3 = &unk_dbfd4;
    puVar4 = (undefined4 *)&unk_dabf0;
    for (iVar1 = 0xc; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar4 = *puVar3;
      puVar3 = puVar3 + (uint)bVar5 * -2 + 1;
      puVar4 = puVar4 + (uint)bVar5 * -2 + 1;
    }
  }
  iVar1 = 0;
  do {
    if ((&unk_dc228)[iVar1] != 100) {
      (&rosters)[(uint)(byte)(&unk_dc228)[iVar1] * 0x27] = 2;
    }
    if ((&unk_dac18)[iVar1] != 'd') {
      (&unk_db7ec)[(uint)(byte)(&unk_dac18)[iVar1] * 0x27] = 2;
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 < 8);
  return;
}


// ================================================================================================
// begin_game_session @ 0x1befd [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall begin_game_session(undefined param_1,undefined unaff_DL)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  byte bVar5;
  undefined4 uStack_14;
  
  bVar5 = 0;
  __CHK(0x1c);
  _period_num = 0xffffffff;
  byte_c5426 = user2_team._2_1_;
  byte_c5427 = away_team_id;
  word_c5428 = 1;
  byte_c542f = 0;
  byte_c5430 = 0;
  byte_c5431 = 0;
  byte_c5432 = 0;
  byte_c5424 = param_1;
  byte_c5425 = unaff_DL;
  byte_dc267 = unaff_DL;
  byte_dc268 = param_1;
  if ((option_flags._1_1_ & 2) == 0) {
    alloc_cup_banner();
  }
  gsummary_path();
  iVar2 = file_create(&byte_dac20,&uStack_14);
  if (iVar2 != 0) {
    fatalerror(&aB1);
  }
  iVar2 = file_write(uStack_14,&unk_c5423,0xffffffff,0xb);
  if (iVar2 != 0) {
    fatalerror(&aB5);
  }
  iVar2 = file_write(uStack_14,&unk_c542e);
  if (iVar2 != 0) {
    fatalerror(&aB8);
  }
  file_close(&uStack_14);
  load_team_databases(0);
  word_db094._2_2_ = 0;
  word_db094._0_2_ = 0;
  word_db090._2_2_ = 0;
  word_db090._0_2_ = 0;
  word_db08c._2_2_ = 0;
  word_db08c._0_2_ = 0;
  word_db088 = 0;
  iVar2 = 0;
  do {
    iVar3 = 0;
    do {
      puVar1 = &word_db088 + iVar3 * 4 + iVar2 * 100;
      puVar4 = puVar1 + (uint)bVar5 * -2 + 1;
      *puVar1 = word_db088;
      *puVar4 = (&word_db08c)[(uint)bVar5 * -2];
      puVar4[(uint)bVar5 * -2 + 1] = (&word_db090)[(uint)bVar5 * -2 + (uint)bVar5 * -2];
      (puVar4 + (uint)bVar5 * -2 + 1)[(uint)bVar5 * -2 + 1] =
           (&word_db090 + (uint)bVar5 * -2 + (uint)bVar5 * -2)[(uint)bVar5 * -2 + 1];
      iVar3 = iVar3 + 1;
    } while (iVar3 < 0x19);
    iVar2 = iVar2 + 1;
  } while (iVar2 < 2);
  word_dc244 = 0;
  word_dc240 = 0;
  iVar2 = 0;
  do {
    iVar3 = 0;
    do {
      puVar1 = (undefined4 *)((int)&word_dc240 + iVar3 * 6 + iVar2 * 0x12);
      *puVar1 = word_dc240;
      *(undefined2 *)(puVar1 + (uint)bVar5 * -2 + 1) = (&word_dc244)[(uint)bVar5 * -4];
      iVar3 = iVar3 + 1;
    } while (iVar3 < 3);
    iVar2 = iVar2 + 1;
  } while (iVar2 < 2);
  return;
}


// ================================================================================================
// db_read_player @ 0x1c0af [__watcall]
// ================================================================================================

int __watcall
db_read_player(int param_1,int param_2,int param_3,int param_4,__off_t param_5,int param_6,
              undefined4 param_7,undefined4 param_8,undefined4 param_9,undefined4 param_10,
              undefined4 param_11,int param_12)

{
  __off_t _Var1;
  int iVar2;
  int local_14;
  
  __CHK(0x1c);
  _Var1 = lseek(param_1,0,0);
  if (_Var1 != 0) {
    fatalerror(&aD);
  }
  _Var1 = lseek(param_1,param_5,0);
  if (_Var1 < 0) {
    fatalerror(&aE);
  }
  iVar2 = file_read(param_1,param_6,0xffffffff,0x34);
  if (iVar2 != 0) {
    fatalerror(&aF);
  }
  _Var1 = lseek(param_2,0,0);
  if (_Var1 != 0) {
    fatalerror(&aG_c0a3b);
  }
  _Var1 = lseek(param_2,*(__off_t *)(param_6 + 0x24),0);
  if (_Var1 < 0) {
    fatalerror(&aH);
  }
  iVar2 = file_read(param_2,param_7,0xffffffff,param_8);
  if (iVar2 != 0) {
    fatalerror(&aI);
  }
  _Var1 = lseek(param_3,0,0);
  if (_Var1 != 0) {
    fatalerror(&aL_c0a41);
  }
  _Var1 = lseek(param_3,*(__off_t *)(param_6 + 0x2c),0);
  if (_Var1 < 0) {
    fatalerror(&aM);
  }
  iVar2 = file_read(param_3,param_9,0xffffffff,param_10);
  if (iVar2 != 0) {
    fatalerror(&aN);
  }
  if (param_12 == 0) {
    local_14 = param_12;
  }
  else {
    _Var1 = lseek(param_4,0,0);
    if (_Var1 != 0) {
      fatalerror(&aO);
    }
    _Var1 = lseek(param_4,*(__off_t *)(param_6 + 0x28),0);
    if (_Var1 < 0) {
      fatalerror(&aP);
    }
    iVar2 = file_read(param_4,param_11,0xffffffff,param_12);
    if (iVar2 != 0) {
      fatalerror(&aQ);
    }
  }
  return local_14;
}


// ================================================================================================
// db_open_files @ 0x1c26c [__watcall]
// ================================================================================================

void __watcall
db_open_files(uint param_1,undefined4 param_2,undefined4 unaff_EBX,undefined4 unaff_ECX,
             undefined4 param_5,char *param_6,undefined4 *param_7)

{
  int iVar1;
  undefined auStack_58 [44];
  char acStack_2c [32];
  
  __CHK(0x6c);
  sprintf(acStack_2c,param_6,&aKey);
  iVar1 = _dos_findfirst(acStack_2c,0,auStack_58);
  if (iVar1 != 0) {
    fatalerror(&a9);
  }
  iVar1 = file_open_read(acStack_2c,param_2);
  if (iVar1 != 0) {
    fatalerror(&aA_c0a53);
  }
  sprintf(acStack_2c,param_6,&aAtt);
  iVar1 = _dos_findfirst(acStack_2c,0,auStack_58);
  if (iVar1 != 0) {
    fatalerror(&aB);
  }
  iVar1 = file_open_read(acStack_2c,unaff_EBX);
  if (iVar1 != 0) {
    fatalerror(&aC);
  }
  sprintf(acStack_2c,param_6,aSeason_c0a5d);
  iVar1 = _dos_findfirst(acStack_2c,0,auStack_58);
  if (iVar1 != 0) {
    fatalerror(&aJ);
  }
  iVar1 = file_open_read(acStack_2c,unaff_ECX);
  if (iVar1 != 0) {
    fatalerror(&aK);
  }
  if ((param_1 & 6) == 0) {
    sprintf(acStack_2c,param_6,aCareer);
    iVar1 = _dos_findfirst(acStack_2c,0,auStack_58);
    if (iVar1 != 0) {
      fatalerror(&aL_c0a41);
    }
    iVar1 = file_open_read(acStack_2c,param_5);
    if (iVar1 != 0) {
      fatalerror(&aM);
    }
    *param_7 = 0x28;
  }
  else {
    *param_7 = 0;
  }
  return;
}


// ================================================================================================
// db_load_team_roster @ 0x1c3f6 [__watcall]
// ================================================================================================

void __watcall
db_load_team_roster(uint param_1,undefined4 param_2,undefined4 unaff_EBX,undefined4 unaff_ECX,
                   undefined4 param_5,undefined4 param_6,int param_7)

{
  undefined4 *puVar1;
  ushort uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined auStack_fc [46];
  byte bStack_ce;
  byte bStack_cd;
  undefined uStack_c4;
  undefined uStack_c3;
  undefined uStack_c2;
  char acStack_c1 [16];
  char acStack_b1 [33];
  undefined auStack_90 [2];
  ushort local_8e;
  ushort uStack_8c;
  ushort uStack_7c;
  ushort uStack_7a;
  byte bStack_6a;
  byte bStack_69;
  undefined local_60 [36];
  ushort local_3c;
  ushort uStack_3a;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 local_18;
  int local_14;
  int iStack_10;
  
  __CHK(0x130);
  iVar6 = 0;
  do {
    iStack_10 = iVar6 * 0x27;
    iVar7 = iStack_10 + param_7 * 0x444;
    if (*(int *)(&unk_dbc7c + iVar6 * 4 + param_7 * 0x2e8) < 0) {
      (&rosters)[iVar7] = 0;
    }
    else {
      db_read_player(param_2,unaff_EBX,unaff_ECX,param_5,
                     *(int *)(&unk_dbc7c + iVar6 * 4 + param_7 * 0x2e8),&uStack_c4,&local_38,0x14,
                     auStack_90,0x2f,local_60,param_6);
      (&unk_db3ad)[iVar7] = uStack_c3;
      (&unk_db3ae)[iVar7] = uStack_c2;
      iVar3 = iStack_10 + param_7 * 0x444;
      strcpy(&rosters + iVar3 + 7,acStack_c1);
      strcpy(&rosters + iVar3 + 0x17,acStack_b1);
      if ((param_1 == 0) || (param_1 == 2)) {
        iVar7 = iVar6 * 0x27 + param_7 * 0x444;
        if ((byte_dc268 < bStack_6a) || ((byte_dc268 <= bStack_6a && (byte_dc267 < bStack_69)))) {
          (&rosters)[iVar7] = 1;
        }
        else {
          (&rosters)[iVar7] = 3;
        }
      }
      else if (*(int *)(&unk_df690 + param_7 * 0x80 + iVar6) >> 0x10 < 1) {
        (&rosters)[iVar7] =
             (&unk_c66b4)[(*(int *)(&unk_df690 + param_7 * 0x80 + iVar6) >> 0x10) * -2];
      }
      else {
        (&rosters)[iVar7] = 5;
      }
      puVar1 = (undefined4 *)(&player_ratings + iVar6 * 0x14 + param_7 * 500);
      *puVar1 = local_38;
      puVar1[1] = local_34;
      puVar1[2] = uStack_30;
      puVar1[3] = uStack_2c;
      puVar1[4] = uStack_28;
      if ((param_1 & 6) == 0) {
        iVar7 = param_7 * 400 + iVar6 * 0x10;
        if ((option_flags._1_1_ & 2) == 0) {
          *(undefined4 *)(&unk_deb74 + iVar7) = 0;
          *(undefined4 *)(&unk_deb78 + iVar7) = 0;
          uVar4 = (uint)uStack_7c;
          *(uint *)(&unk_deb7c + iVar7) = uVar4;
          uVar2 = uStack_7a;
        }
        else {
          *(uint *)(&unk_deb74 + iVar7) = (uint)local_3c;
          *(uint *)(&unk_deb78 + iVar7) = (uint)uStack_3a + (uint)local_3c;
          uVar4 = (uint)local_8e;
          *(uint *)(&unk_deb7c + iVar7) = uVar4;
          uVar2 = uStack_8c;
        }
        *(uint *)(&unk_deb80 + iVar7) = uVar2 + uVar4;
      }
    }
    iVar6 = iVar6 + 1;
  } while (iVar6 < 0x19);
  iVar6 = 0;
  do {
    iVar5 = iVar6 * 4 + param_7 * 0x2e8;
    local_14 = param_7 * 0x444;
    iVar3 = (iVar6 + 0x19) * 0x27;
    iVar7 = local_14 + iVar3;
    if (*(int *)(&unk_dbce0 + iVar5) < 0) {
      (&rosters)[iVar7] = 0;
    }
    else {
      db_read_player(param_2,unaff_EBX,unaff_ECX,0,*(undefined4 *)(&unk_dbce0 + iVar5),&uStack_c4,
                     &uStack_24,0x10,auStack_fc,0x36,0,0);
      (&unk_db3ad)[iVar7] = uStack_c3;
      (&unk_db3ae)[iVar7] = uStack_c2;
      iVar3 = iVar3 + local_14;
      strcpy(&rosters + iVar3 + 7,acStack_c1);
      strcpy(&rosters + iVar3 + 0x17,acStack_b1);
      if ((param_1 == 0) || (param_1 == 2)) {
        iVar7 = param_7 * 0x444 + (iVar6 + 0x19) * 0x27;
        if ((byte_dc268 < bStack_ce) || ((byte_dc268 <= bStack_ce && (byte_dc267 < bStack_cd)))) {
          (&rosters)[iVar7] = 1;
        }
        else {
          (&rosters)[iVar7] = 3;
        }
      }
      else if (*(int *)(&unk_df6c2 + iVar6 * 2 + param_7 * 0x100) >> 0x10 < 1) {
        (&rosters)[iVar7] =
             (&unk_c66b4)[(*(int *)(&unk_df6c2 + iVar6 * 2 + param_7 * 0x100) >> 0x10) * -2];
      }
      else {
        (&rosters)[iVar7] = 5;
      }
      puVar1 = (undefined4 *)(&unk_dac40 + param_7 * 0x30 + iVar6 * 0x10);
      *puVar1 = uStack_24;
      puVar1[1] = uStack_20;
      puVar1[2] = uStack_1c;
      puVar1[3] = local_18;
    }
    iVar6 = iVar6 + 1;
  } while (iVar6 < 3);
  return;
}


// ================================================================================================
// gsummary_path @ 0x1c807 [__watcall]
// ================================================================================================

void __watcall gsummary_path(void)

{
  __CHK(8);
  byte_dac20 = 0;
  if (league_dir != '\0') {
    strcpy(&byte_dac20,&league_dir);
    strcat(&byte_dac20,&unk_c0a6f);
  }
  strcat(&byte_dac20,aGsummaryDb_c0a71);
  return;
}


// ================================================================================================
// set_goalie_menu_labels @ 0x1c852 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall set_goalie_menu_labels(void)

{
  int iVar1;
  undefined *puVar2;
  char cStack_30;
  char local_2f;
  char cStack_2e;
  char cStack_2d;
  undefined uStack_2b;
  char acStack_28 [24];
  
  __CHK(0x38);
  iVar1 = (uint)byte_dc224 * 0x27;
  strcpy(&cStack_30,off_cee5f);
  if ((byte)(&unk_db3ad)[iVar1] < 10) {
    cStack_2e = local_2f;
  }
  else {
    cStack_2e = cStack_2e + (byte)(&unk_db3ad)[iVar1] / 10;
  }
  cStack_2d = cStack_2d + (byte)(&unk_db3ad)[iVar1] % 10;
  uStack_2b = (&DAT_000db3af)[iVar1];
  strncpy(acStack_28,(char *)(iVar1 + 0xdb3bf),0x10);
  iVar1 = textwidth(&cStack_30);
  DAT_000cee57 = iVar1 + 5;
  strcpy(off_cee5f,&cStack_30);
  iVar1 = (uint)byte_dc225 * 0x27;
  strcpy(&cStack_30,off_cee7f);
  if ((byte)(&unk_db3ad)[iVar1] < 10) {
    cStack_2e = local_2f;
  }
  else {
    cStack_2e = cStack_2e + (byte)(&unk_db3ad)[iVar1] / 10;
  }
  cStack_2d = cStack_2d + (byte)(&unk_db3ad)[iVar1] % 10;
  uStack_2b = (&DAT_000db3af)[iVar1];
  strncpy(acStack_28,(char *)(iVar1 + 0xdb3bf),0x10);
  iVar1 = textwidth(&cStack_30);
  DAT_000cee77 = iVar1 + 5;
  strcpy(off_cee7f,&cStack_30);
  if (DAT_000cee77 < DAT_000cee57) {
    DAT_000cee97 = DAT_000cee57;
  }
  else {
    DAT_000cee97 = DAT_000cee77;
  }
  puVar2 = off_cee9f;
  if (-1 < ram0x000df64a) {
    puVar2 = (&off_cee5f)[(ram0x000df64a >> 0x10) * 8];
  }
  DAT_000cee57 = DAT_000cee97;
  DAT_000cee77 = DAT_000cee97;
  *puVar2 = 1;
  iVar1 = (uint)DAT_000dac13._1_1_ * 0x27;
  strcpy(&cStack_30,off_ceebf);
  if ((byte)(&unk_db7f1)[iVar1] < 10) {
    cStack_2e = local_2f;
  }
  else {
    cStack_2e = cStack_2e + (byte)(&unk_db7f1)[iVar1] / 10;
  }
  cStack_2d = cStack_2d + (byte)(&unk_db7f1)[iVar1] % 10;
  uStack_2b = (&DAT_000db7f3)[iVar1];
  strncpy(acStack_28,(char *)(iVar1 + 0xdb803),0x10);
  iVar1 = textwidth(&cStack_30);
  DAT_000ceeb7 = iVar1 + 5;
  strcpy(off_ceebf,&cStack_30);
  iVar1 = (uint)DAT_000dac13._2_1_ * 0x27;
  strcpy(&cStack_30,off_ceedf);
  if ((byte)(&unk_db7f1)[iVar1] < 10) {
    cStack_2e = local_2f;
  }
  else {
    cStack_2e = cStack_2e + (byte)(&unk_db7f1)[iVar1] / 10;
  }
  cStack_2d = cStack_2d + (byte)(&unk_db7f1)[iVar1] % 10;
  uStack_2b = (&DAT_000db7f3)[iVar1];
  strncpy(acStack_28,(char *)(iVar1 + 0xdb803),0x10);
  iVar1 = textwidth(&cStack_30);
  DAT_000ceed7 = iVar1 + 5;
  strcpy(off_ceedf,&cStack_30);
  if (DAT_000ceed7 < DAT_000ceeb7) {
    DAT_000ceef7 = DAT_000ceeb7;
  }
  else {
    DAT_000ceef7 = DAT_000ceed7;
  }
  puVar2 = off_ceeff;
  if (-1 < ram0x000df74a) {
    puVar2 = (&off_ceebf)[(ram0x000df74a >> 0x10) * 8];
  }
  DAT_000ceeb7 = DAT_000ceef7;
  DAT_000ceed7 = DAT_000ceef7;
  *puVar2 = 1;
  return;
}


// ================================================================================================
// clear_goalie_menu_labels @ 0x1cb7f [__watcall]
// ================================================================================================

void __watcall clear_goalie_menu_labels(void)

{
  __CHK(8);
  strcpy(off_cee5f,&unk_cdcd0);
  strcpy(off_cee7f,&unk_cdcd0);
  *off_cee9f = 2;
  strcpy(off_ceebf,&unk_cdcd0);
  strcpy(off_ceedf,&unk_cdcd0);
  *off_ceeff = 2;
  return;
}


// ================================================================================================
// penalty_lists_reset @ 0x1cbd8 [__watcall]
// ================================================================================================

void __watcall penalty_lists_reset(void)

{
  int iVar1;
  
  __CHK(0x10);
  iVar1 = 0;
  do {
    (&word_c575c)[iVar1 * 4] = 0xffff;
    (&word_c571c)[iVar1 * 4] = 0xffff;
    (&unk_c5762)[iVar1 * 4] = 0;
    (&unk_c5722)[iVar1 * 4] = 0;
    (&unk_c5760)[iVar1 * 4] = 0;
    (&unk_c5720)[iVar1 * 4] = 0;
    (&unk_c575e)[iVar1 * 4] = 0;
    (&unk_c571e)[iVar1 * 4] = 0;
    iVar1 = iVar1 + 1;
  } while (iVar1 < 8);
  load_scoreboard_shapes();
  return;
}


// ================================================================================================
// load_scoreboard_shapes @ 0x1cc3d [__watcall]
// ================================================================================================

void __watcall load_scoreboard_shapes(void)

{
  undefined *puVar1;
  undefined auStack_28 [16];
  
  __CHK(0x38);
  puVar1 = install_path;
  if (byte_ed938 != '\x01') {
    puVar1 = (undefined *)0x0;
  }
  make_path(auStack_28,puVar1,aScrbrd1,&aPPV);
  scoreboard_bank = loadfile(auStack_28,0x20);
  locateshapes(scoreboard_bank,a000000010002000300040005,&score_digit_shapes);
  locateshapes(scoreboard_bank,a100010011002100310041005,&hud_digit_shapes);
  locateshapes(scoreboard_bank,a200020012002200320042005,&small_digit_shapes);
  locateshapes(scoreboard_bank,aVlinvppVpk,&shapes_vlin);
  locateshapes(scoreboard_bank,aHlinhppHpk,&shapes_hlin);
  shape_visp = locateshape(scoreboard_bank,&aVisp);
  shape_homp = locateshape(scoreboard_bank,&aHomp);
  locateshapes(scoreboard_bank,aLin1lin2lin3lin4PP1PP2PK,&shapes_lines);
  return;
}


// ================================================================================================
// blit_sprite @ 0x1cd73 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall
blit_sprite(undefined4 *param_1,short unaff_DX,short unaff_BX,short unaff_CX,short param_5)

{
  undefined uVar1;
  undefined uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined1 *puVar6;
  short local_1c;
  short local_18;
  
  __CHK(0x3c);
  local_1c = 0;
  if (unaff_CX == 0) {
    local_18 = unaff_DX - *(short *)(param_1 + 2);
  }
  else {
    local_18 = (unaff_DX - *(short *)(param_1 + 1)) + *(short *)(param_1 + 2) + 1;
  }
  unaff_BX = unaff_BX - *(short *)((int)param_1 + 10);
  if ((((local_18 < _dword_d30b4) &&
       (iVar3 = (int)(short)(local_18 + *(short *)(param_1 + 1) + -1), dword_d30ac <= iVar3)) &&
      (iVar4 = (int)unaff_BX, iVar4 < dword_d30b8)) &&
     (iVar5 = (int)(short)(unaff_BX + *(short *)((int)param_1 + 6)), dword_d30b0 < iVar5)) {
    if (((local_18 < dword_d30ac) || (_dword_d30b4 <= iVar3)) ||
       ((iVar4 < dword_d30b0 || (dword_d30b8 <= iVar5)))) {
      local_1c = 1;
    }
    if (unaff_CX != 0) {
      local_1c = local_1c + 4;
    }
    if (-1 < param_5) {
      iVar3 = (int)param_5 + unaff_CX * 2;
      if (iVar3 != dword_c6718) {
        if (unaff_CX != 0) {
          if (param_5 == 0) {
            puVar6 = &unk_dca98;
          }
          else {
            puVar6 = &unk_dc998;
          }
          iVar5 = 0;
          do {
            uVar1 = puVar6[iVar5 + 1];
            uVar2 = puVar6[iVar5];
            puVar6[iVar5] = puVar6[iVar5 + 4];
            puVar6[iVar5 + 1] = puVar6[iVar5 + 3];
            puVar6[iVar5 + 3] = uVar1;
            puVar6[iVar5 + 4] = uVar2;
            iVar5 = iVar5 + 0x10;
          } while (iVar5 < 0x40);
        }
        if (param_5 == 0) {
          puVar6 = &remap_home;
        }
        else {
          puVar6 = &remap_away;
        }
        setremaptable(puVar6);
        dword_c6718 = iVar3;
        if (unaff_CX != 0) {
          if (param_5 == 0) {
            puVar6 = &unk_dca98;
          }
          else {
            puVar6 = &unk_dc998;
          }
          iVar3 = 0;
          do {
            uVar1 = puVar6[iVar3 + 1];
            uVar2 = puVar6[iVar3];
            puVar6[iVar3] = puVar6[iVar3 + 4];
            puVar6[iVar3 + 1] = puVar6[iVar3 + 3];
            puVar6[iVar3 + 3] = uVar1;
            puVar6[iVar3 + 4] = uVar2;
            iVar3 = iVar3 + 0x10;
          } while (iVar3 < 0x40);
        }
      }
      local_1c = local_1c + 2;
    }
    iVar3 = dword_d8c40;
    if ((char)*param_1 != '\0') {
      local_1c = local_1c + 8;
    }
    iVar5 = (int)local_18;
    dword_d8c40 = dword_d8c40 + 1;
    zm_zone_set_rect(iVar3,iVar5,iVar4,(*(int *)((int)param_1 + 2) >> 0x10) + iVar5,
                     ((int)param_1[1] >> 0x10) + iVar4);
    switch(local_1c) {
    case 8:
      blit_rle_frame(param_1,iVar5,iVar4);
      break;
    case 9:
      blit_rle_clip(param_1,iVar5,iVar4);
      break;
    case 10:
      blit_rle_remap(param_1,iVar5,iVar4);
      break;
    case 0xb:
      blit_rle_remap_clip();
      break;
    case 0xc:
      blit_rle_flip();
      break;
    case 0xd:
      blit_rle_flip_clip();
      break;
    case 0xe:
      blit_rle_flip_remap();
      break;
    case 0xf:
      blit_rle_flip_remap_clip();
    }
  }
  return;
}


// ================================================================================================
// menu_nop @ 0x1d019 [__watcall]
// ================================================================================================

void __watcall menu_nop(void)

{
  __CHK(4);
  return;
}


// ================================================================================================
// empty_func_1d024 @ 0x1d024 [__watcall]
// ================================================================================================

void __watcall empty_func_1d024(void)

{
  __CHK(4);
  return;
}


// ================================================================================================
// dirty_rect_add @ 0x1d02f [__watcall]
// ================================================================================================

void __watcall dirty_rect_add(short param_1,short unaff_DX,short unaff_BX,short unaff_CX)

{
  int iVar1;
  
  __CHK(0xc);
  *(uint *)(*(int *)(&unk_dc8d0 + (uint)(dword_eda04 == 0) * 4) + 8) =
       (((uint)((int)unaff_BX + (int)param_1) >> 2) - ((uint)(int)param_1 >> 2)) + 1;
  *(int *)(*(int *)(&unk_dc8d0 + (uint)(dword_eda04 == 0) * 4) + 0xc) = (int)unaff_CX;
  **(uint **)(&unk_dc8d0 + (uint)(dword_eda04 == 0) * 4) = (uint)(int)param_1 >> 2;
  *(int *)(*(int *)(&unk_dc8d0 + (uint)(dword_eda04 == 0) * 4) + 4) = (int)unaff_DX;
  iVar1 = dword_eda04;
  *(int *)(&unk_c66c8 + (uint)(dword_eda04 == 0) * 4) =
       *(int *)(&unk_c66c8 + (uint)(dword_eda04 == 0) * 4) + 1;
  *(int *)(&unk_dc8d0 + (uint)(iVar1 == 0) * 4) =
       *(int *)(&unk_dc8d0 + (uint)(iVar1 == 0) * 4) + 0x10;
  return;
}


// ================================================================================================
// set_menu_mode @ 0x1d100 [__watcall]
// ================================================================================================

void __watcall set_menu_mode(int param_1,undefined4 param_2,undefined4 param_3,int unaff_ECX)

{
  char cVar1;
  char *__src;
  int iVar2;
  int iVar3;
  
  __CHK(0x1c);
  cVar1 = byte_c671c;
  if ((param_1 == 0) && ((byte_c5311 == '\0' || (byte_c5386 == '\0')))) {
    if (byte_c5311 == '\0') {
      if (byte_c5386 == '\0') {
        param_1 = 1;
      }
      else {
        param_1 = 3;
      }
    }
    else {
      param_1 = 2;
    }
  }
  switch(param_1) {
  case 0:
    funcptr_c6825 = stats_source_league_season;
    funcptr_c6845 = stats_source_league_season_playoffs;
    funcptr_c6885 = stats_source_league_playoffs;
    off_c6821 = &byte_c6745;
    off_c6841 = &byte_c6759;
    off_c6881 = &byte_c6777;
    if (byte_c6745 == '\x01') {
      byte_c6759 = '\x02';
      if (stats_playoffs != 0) {
        stats_selected_team = 0;
      }
      stats_playoffs = 0;
LAB_0001d3c0:
      byte_c6777 = '\x02';
      __src = &byte_c5386;
LAB_0001d469:
      stats_league = 1;
      byte_c672f = '\x02';
      byte_c671c = '\x02';
      strncpy(&unk_c65d4,__src,0x1f);
    }
    else {
      if (byte_c6759 == '\x01') {
        byte_c6745 = '\x02';
        if (stats_playoffs == 0) {
          stats_selected_team = stats_playoffs;
        }
        stats_playoffs = 1;
        goto LAB_0001d3c0;
      }
      if (byte_c6777 == '\x01') {
        byte_c6759 = '\x02';
        byte_c6745 = '\x02';
        if (stats_playoffs == 0) {
          stats_selected_team = stats_playoffs;
        }
        stats_playoffs = 1;
        __src = &byte_c5311;
        goto LAB_0001d469;
      }
    }
    unaff_ECX = 7;
    break;
  case 1:
    if ((byte_c671c == '\x02') && (byte_c672f == '\x02')) {
      byte_c671c = '\x01';
      byte_c6777 = cVar1;
      byte_c6759 = cVar1;
      byte_c6745 = cVar1;
      byte_c672f = cVar1;
      stats_league = 0;
      if (stats_playoffs != 0) {
        stats_selected_team = 0;
      }
      stats_playoffs = 0;
      strncpy(&unk_c65d4,&unk_c529c,0x1f);
    }
    unaff_ECX = 2;
    break;
  case 2:
    funcptr_c6825 = stats_source_league_playoffs;
    off_c6821 = &byte_c6777;
    if (((byte_c6745 == '\x01') || (byte_c6759 == '\x01')) || (byte_c6777 == '\x01')) {
      byte_c6777 = '\x01';
      byte_c6759 = '\x02';
      byte_c6745 = '\x02';
      byte_c672f = '\x02';
      byte_c671c = '\x02';
      stats_league = 1;
      if (stats_playoffs == 0) {
        stats_selected_team = stats_playoffs;
      }
      stats_playoffs = 1;
      strncpy(&unk_c65d4,&byte_c5311,0x1f);
    }
    unaff_ECX = 4;
    break;
  case 3:
    funcptr_c6825 = stats_source_league_season;
    funcptr_c6845 = stats_source_league_season_playoffs;
    off_c6821 = &byte_c6745;
    off_c6841 = &byte_c6759;
    if ((byte_c6777 == '\x01') || (byte_c6745 == '\x01')) {
      byte_c6745 = '\x01';
      byte_c6759 = '\x02';
      if (stats_playoffs != 0) {
        stats_selected_team = 0;
      }
      stats_playoffs = 0;
LAB_0001d223:
      stats_league = 1;
      byte_c6777 = '\x02';
      byte_c672f = '\x02';
      byte_c671c = '\x02';
      strncpy(&unk_c65d4,&byte_c5386,0x1f);
    }
    else if (byte_c6759 == '\x01') {
      byte_c6745 = '\x02';
      if (stats_playoffs == 0) {
        stats_selected_team = stats_playoffs;
      }
      stats_playoffs = 1;
      goto LAB_0001d223;
    }
    unaff_ECX = 5;
  }
  if (unaff_ECX == 4) {
    dword_c67b9 = 0xc5;
    unk_c678e[0x1b] = '\0';
  }
  else {
    dword_c67b9 = 0xf7;
    unk_c678e[0x1b] = '-';
  }
  iVar3 = 0x11;
  for (iVar2 = 0; iVar2 < unaff_ECX; iVar2 = iVar2 + 1) {
    (&unk_c67bd)[iVar2 * 8] = iVar3;
    (&dword_c67b9)[iVar2 * 8] = dword_c67b9;
    iVar3 = iVar3 + 0x12;
  }
  dword_c891e = unaff_ECX;
  dword_ce8eb = unaff_ECX;
  dword_cf00b = unaff_ECX;
  dword_cf4cb = unaff_ECX;
  dword_cf5ab = unaff_ECX;
  dword_cf70b = unaff_ECX;
  dword_cf7cb = unaff_ECX;
  dword_cf84b = unaff_ECX;
  dword_cf8cb = unaff_ECX;
  dword_cfa4b = unaff_ECX;
  *(int *)(unk_c678e + unaff_ECX * 0x20 + 0xf) = *(int *)(unk_c678e + unaff_ECX * 0x20 + 0xf) + 1;
  return;
}


// ================================================================================================
// set_league_menu_titles @ 0x1d518 [__watcall]
// ================================================================================================

void __watcall set_league_menu_titles(void)

{
  int iVar1;
  
  __CHK(0x10);
  if (byte_c5311 != '\0') {
    iVar1 = strlen_to_dot(&byte_c5311);
    (&byte_c5311)[iVar1] = 0;
    strcpy(s__WWWWWWWW__Play_Offs_000c6778 + 2,&byte_c5311);
    strcpy(s__WWWWWWWW__Play_Offs_000c6778 + iVar1 + 2,aPlayOffs);
    (&byte_c5311)[iVar1] = 0x2e;
  }
  if (byte_c5386 != '\0') {
    iVar1 = strlen_to_dot(&byte_c5386);
    (&byte_c5386)[iVar1] = 0;
    strcpy(s__WWWWWWWW__Season_000c6746 + 2,&byte_c5386);
    strcpy(s__WWWWWWWW__Season_Play_Offs_000c675a + 2,&byte_c5386);
    strcpy(s__WWWWWWWW__Season_000c6746 + iVar1 + 2,aSeason_c6891);
    strcpy(s__WWWWWWWW__Season_Play_Offs_000c675a + iVar1 + 2,aSeasonPlayOffs);
    (&byte_c5386)[iVar1] = 0x2e;
  }
  return;
}


// ================================================================================================
// strlen_to_dot @ 0x1d5d5 [__watcall]
// ================================================================================================

undefined8 __watcall strlen_to_dot(char *param_1,undefined4 unaff_EDX)

{
  int iVar1;
  
  __CHK(0xc);
  iVar1 = 0;
  for (; (*param_1 != '\0' && (*param_1 != '.')); param_1 = param_1 + 1) {
    iVar1 = iVar1 + 1;
  }
  return CONCAT44(unaff_EDX,iVar1);
}


// ================================================================================================
// set_hub_title @ 0x1d610 [__watcall]
// ================================================================================================

void __watcall set_hub_title(undefined4 param_1,int unaff_EDX,char *unaff_EBX)

{
  __CHK(0xc);
  switch(param_1) {
  case 0:
    unaff_EBX = aSportsCentral_ce20b;
    unaff_EDX = 0x67;
    break;
  case 1:
    unaff_EBX = aPlayoffTree_ce22a;
    unaff_EDX = 0x59;
    break;
  case 2:
    unaff_EBX = aLeagueCalendar;
    unaff_EDX = 0x76;
    break;
  case 3:
    unaff_EBX = aBroadcastBooth;
    unaff_EDX = 0x73;
    break;
  case 4:
    unaff_EBX = aIntermissionDesk;
    unaff_EDX = 0x7e;
    break;
  case 5:
    unaff_EBX = aRinkSide;
    unaff_EDX = 0x41;
  }
  off_cf67f = unaff_EBX;
  off_cf61f = unaff_EBX;
  off_cf5df = unaff_EBX;
  off_cf51f = unaff_EBX;
  dword_cf5d7 = unaff_EDX;
  dword_cf517 = unaff_EDX;
  if (unaff_EDX < 0x7e) {
    unaff_EDX = 0x7d;
  }
  dword_cf677 = unaff_EDX;
  dword_cf657 = unaff_EDX;
  dword_cf637 = unaff_EDX;
  dword_cf617 = unaff_EDX;
  dword_cf5f7 = unaff_EDX;
  return;
}


// ================================================================================================
// str_prefix_differs @ 0x1d6be [__watcall]
// ================================================================================================

undefined4 __watcall str_prefix_differs(char *param_1,char *unaff_EDX)

{
  __CHK(8);
  for (; (*param_1 != '\0' && (*unaff_EDX != '\0')); unaff_EDX = unaff_EDX + 1) {
    if (*param_1 != *unaff_EDX) {
      return 1;
    }
    param_1 = param_1 + 1;
  }
  return 0;
}


// ================================================================================================
// run_menu @ 0x1d6e8 [__watcall]
// ================================================================================================

undefined4 __watcall
run_menu(int *param_1,undefined4 param_2,undefined4 unaff_EBX,undefined4 unaff_ECX,
        undefined4 param_5)

{
  ulonglong uVar1;
  int iVar2;
  undefined4 ****ppppuVar3;
  int iVar4;
  undefined4 *****pppppuVar5;
  undefined4 *puVar6;
  int *piVar7;
  undefined4 uVar8;
  undefined4 extraout_EDX;
  int iVar9;
  undefined4 *****pppppuVar10;
  int iVar11;
  undefined4 *****pppppuVar12;
  undefined4 *****pppppuVar13;
  undefined4 *puVar14;
  byte bVar15;
  ulonglong uVar16;
  undefined8 uVar17;
  int local_98 [8];
  int local_78 [4];
  int *local_68 [4];
  int local_58 [4];
  int local_38;
  int local_34;
  undefined4 ****local_30;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  undefined4 ****local_1c;
  int local_18;
  undefined4 ****local_14;
  int local_10;
  
  bVar15 = 0;
  __CHK(0xb4);
  local_10 = 0;
  local_68[3] = (int *)0x0;
  local_68[2] = (int *)0x0;
  local_68[1] = (int *)0x0;
  local_58[3] = 0;
  local_58[2] = 0;
  local_58[1] = 0;
  local_58[0] = 0;
  local_78[3] = 0;
  local_78[2] = 0;
  local_78[1] = 0;
  local_78[0] = 0;
  local_98[1] = 0;
  local_98[0] = 0;
  local_68[0] = param_1;
  local_1c = (undefined4 ****)
             allocmem(aPointer_c0b54,
                      ((*(int *)((int)pointer_shapes + 2) >> 0x10) + 1) *
                      (((int)pointer_shapes[1] >> 0x10) + 1) + 0x11,0x20);
  pppppuVar12 = (undefined4 *****)local_1c + (uint)bVar15 * -2 + 1;
  pppppuVar10 = pointer_shapes + (uint)bVar15 * -2 + 1;
  *local_1c = *pointer_shapes;
  pppppuVar13 = pppppuVar12 + (uint)bVar15 * -2 + 1;
  pppppuVar5 = pppppuVar10 + (uint)bVar15 * -2 + 1;
  *pppppuVar12 = *pppppuVar10;
  *pppppuVar13 = *pppppuVar5;
  pppppuVar13[(uint)bVar15 * -2 + 1] = pppppuVar5[(uint)bVar15 * -2 + 1];
  *(undefined *)(pppppuVar13 + (uint)bVar15 * -2 + 1 + (uint)bVar15 * -2 + 1) =
       *(undefined *)(pppppuVar5 + (uint)bVar15 * -2 + 1 + (uint)bVar15 * -2 + 1);
  *(short *)((undefined4 *****)local_1c + 1) = *(short *)(pointer_shapes + 1) + 1;
  *(short *)((int)local_1c + 6) = *(short *)((int)pointer_shapes + 6) + 1;
  iVar4 = (*local_68[0] + local_68[0][2]) / 2;
  pppppuVar5 = (undefined4 *****)((local_68[0][1] + local_68[0][3]) / 2);
  local_30 = pppppuVar5;
  local_2c = iVar4;
  local_18 = iVar4;
  local_14 = pppppuVar5;
  grabshape(local_1c,iVar4,pppppuVar5);
  pppppuVar10 = pointer_shapes;
  drawshape_remap(pointer_shapes,iVar4,pppppuVar5);
  setmouselimits(0,0,0x280,0x1e0);
  setmousepos(iVar4,pppppuVar5);
  (*(code *)mouse_update_callback)();
  uVar16 = event_queue_reset();
LAB_0001d83a:
  uVar8 = 0;
  do {
    uVar17 = event_queue_pop((int)uVar16,(int)(uVar16 >> 0x20),pppppuVar10);
    uVar1 = CONCAT44((int)((ulonglong)uVar17 >> 0x20),uVar8);
    if ((int)uVar17 == 0) break;
    pppppuVar10 = &local_30;
    uVar16 = (*ui_poll_callback)();
    uVar8 = (undefined4)uVar16;
    uVar1 = uVar16;
  } while ((uVar16 & 2) == 0);
  ppppuVar3 = local_1c;
  uVar16 = CONCAT44((int)(uVar1 >> 0x20),local_30);
  if ((uVar1 & 2) == 0) goto code_r0x0001d862;
  iVar4 = hit_test_menus(local_2c,local_30,local_68,local_10,&stack0xffffffb8,local_98,&local_34,
                         &local_38);
  if (iVar4 == 0) {
    drawshape(local_1c,local_18,local_14);
    for (iVar4 = 3; -1 < iVar4; iVar4 = iVar4 + -1) {
      if (local_58[iVar4] != 0) {
        drawshape(local_58[iVar4],local_98[iVar4 * 2],local_98[iVar4 * 2 + 1]);
        local_98[iVar4 * 2 + 1] = 0;
        local_98[iVar4 * 2] = 0;
        freemem(local_58[iVar4]);
      }
    }
    local_10 = 0;
    local_68[3] = (int *)0x0;
    local_68[2] = (int *)0x0;
    local_68[1] = (int *)0x0;
    local_58[3] = 0;
    local_58[2] = 0;
    local_58[1] = 0;
    local_58[0] = 0;
    local_78[3] = 0;
    local_78[2] = 0;
    local_78[1] = 0;
  }
  else {
    if (local_68[local_34][local_38 * 8 + 5] == 0) {
      if (local_68[local_34][local_38 * 8 + 6] == 0) {
        drawshape(local_1c,local_18,local_14);
        menu_item_draw_normal
                  (local_68[local_34] + local_78[local_34] * 8,local_98[local_34 * 2],
                   local_98[local_34 * 2 + 1],unaff_EBX,unaff_ECX,param_5);
        iVar2 = local_34;
        iVar11 = local_38;
        local_78[local_34] = local_38;
        iVar4 = local_98[iVar2 * 2 + 1];
        iVar9 = local_98[iVar2 * 2];
        piVar7 = local_68[iVar2] + iVar11 * 8;
      }
      else {
        drawshape(local_1c,local_18,local_14);
        iVar4 = local_10;
        if (local_10 != local_34) {
          for (; local_34 < iVar4; iVar4 = iVar4 + -1) {
            local_78[iVar4] = 0;
            if (local_58[iVar4] != 0) {
              drawshape(local_58[iVar4],local_98[iVar4 * 2],local_98[iVar4 * 2 + 1]);
              local_98[iVar4 * 2 + 1] = 0;
              local_98[iVar4 * 2] = 0;
              freemem(local_58[iVar4]);
              local_58[iVar4] = 0;
              local_68[iVar4] = (int *)0x0;
              *(undefined4 *)(&stack0xffffffb8 + iVar4 * 4) = 0;
            }
          }
          local_10 = local_34;
        }
        iVar11 = local_10;
        menu_item_draw_normal
                  (local_68[local_10] + local_78[local_10] * 8,local_98[local_10 * 2],
                   local_98[local_10 * 2 + 1],unaff_EBX,unaff_ECX,param_5);
        iVar4 = local_38;
        local_78[iVar11] = local_38;
        menu_item_draw_selected
                  (local_68[iVar11] + iVar4 * 8,local_98[iVar11 * 2],local_98[iVar11 * 2 + 1],
                   unaff_EBX,unaff_ECX,param_5);
        iVar9 = local_34;
        iVar4 = local_38;
        iVar11 = iVar11 + 1;
        local_10 = iVar11;
        local_68[iVar11] = (int *)local_68[local_34][local_38 * 8 + 6];
        piVar7 = local_68[iVar9] + iVar4 * 8;
        *(int *)(&stack0xffffffb8 + iVar11 * 4) = piVar7[7];
        if (iVar11 == 1) {
          iVar4 = *piVar7;
        }
        else {
          iVar4 = piVar7[2];
        }
        local_98[local_10 * 2] = iVar4 + local_98[local_10 * 2 + -2];
        if (local_10 == 1) {
          iVar4 = local_68[local_34][local_38 * 8 + 3];
        }
        else {
          iVar4 = local_68[local_34][local_38 * 8 + 1];
        }
        local_20 = local_10 * 8;
        local_98[local_10 * 2 + 1] = iVar4 + local_98[local_10 * 2 + -1];
        iVar11 = local_10;
        piVar7 = local_68[local_10];
        local_24 = (piVar7[*(int *)(&stack0xffffffb8 + local_10 * 4) * 8 + -6] - *piVar7) + 1;
        local_28 = (piVar7[*(int *)(&stack0xffffffb8 + local_10 * 4) * 8 + -5] - piVar7[1]) + 1;
        puVar6 = (undefined4 *)allocmem(aMenubuff_c0b5c,local_24 * local_28 + 0x11,0x20);
        local_58[iVar11] = (int)puVar6;
        puVar14 = puVar6 + (uint)bVar15 * -2 + 1;
        pppppuVar10 = pointer_shapes + (uint)bVar15 * -2 + 1;
        *puVar6 = *pointer_shapes;
        puVar6 = puVar14 + (uint)bVar15 * -2 + 1;
        pppppuVar5 = pppppuVar10 + (uint)bVar15 * -2 + 1;
        *puVar14 = *pppppuVar10;
        *puVar6 = *pppppuVar5;
        puVar6[(uint)bVar15 * -2 + 1] = pppppuVar5[(uint)bVar15 * -2 + 1];
        *(undefined *)(puVar6 + (uint)bVar15 * -2 + 1 + (uint)bVar15 * -2 + 1) =
             *(undefined *)(pppppuVar5 + (uint)bVar15 * -2 + 1 + (uint)bVar15 * -2 + 1);
        *(short *)(local_58[iVar11] + 4) = (short)local_24;
        *(short *)(local_58[iVar11] + 6) = (short)local_28;
        grabshape(local_58[iVar11],*(undefined4 *)((int)local_98 + local_20),
                  *(undefined4 *)((int)local_98 + local_20 + 4));
        draw_menu(local_68[iVar11],*(undefined4 *)(&stack0xffffffb8 + iVar11 * 4),
                  *(undefined4 *)((int)local_98 + local_20),
                  *(undefined4 *)((int)local_98 + local_20 + 4),unaff_EBX,unaff_ECX,param_5);
        local_78[iVar11] = 0;
        iVar4 = *(int *)((int)local_98 + local_20 + 4);
        iVar9 = *(int *)((int)local_98 + local_20);
        piVar7 = local_68[iVar11];
      }
    }
    else {
      if (local_38 == local_78[local_34]) {
        drawshape(local_1c,local_18,local_14);
        for (iVar4 = 3; -1 < iVar4; iVar4 = iVar4 + -1) {
          if (local_58[iVar4] != 0) {
            drawshape(local_58[iVar4],local_98[iVar4 * 2],local_98[iVar4 * 2 + 1]);
            local_98[iVar4 * 2 + 1] = 0;
            local_98[iVar4 * 2] = 0;
            freemem(local_58[iVar4]);
          }
        }
        local_10 = 0;
        iVar4 = (*(code *)local_68[local_34][local_38 * 8 + 5])();
        local_68[3] = (int *)0x0;
        local_68[2] = (int *)0x0;
        local_68[1] = (int *)0x0;
        local_58[3] = 0;
        local_58[2] = 0;
        local_58[1] = 0;
        local_58[0] = 0;
        local_78[3] = 0;
        local_78[2] = 0;
        local_78[1] = 0;
        if (iVar4 == 1) {
          freemem(local_1c);
          return 0;
        }
        setmousepos(local_18,local_14);
        local_2c = local_18;
        local_30 = local_14;
        event_queue_reset();
        goto LAB_0001de8d;
      }
      drawshape(local_1c,local_18,local_14);
      menu_item_draw_normal
                (local_68[local_34] + local_78[local_34] * 8,local_98[local_34 * 2],
                 local_98[local_34 * 2 + 1],unaff_EBX,unaff_ECX,param_5);
      iVar11 = local_34;
      local_78[local_34] = local_38;
      iVar4 = local_98[iVar11 * 2 + 1];
      iVar9 = local_98[iVar11 * 2];
      piVar7 = local_68[iVar11] + local_78[iVar11] * 8;
    }
    menu_item_draw_selected(piVar7,iVar9,iVar4,unaff_EBX,unaff_ECX,param_5);
  }
LAB_0001de8d:
  grabshape(local_1c,local_18,local_14);
  pppppuVar10 = (undefined4 *****)local_1c;
  drawshape(local_1c,local_18,local_14);
  grabshape(local_1c,local_2c,local_30);
  goto LAB_0001d8c0;
code_r0x0001d862:
  if ((local_2c != local_18) || (local_30 != local_14)) {
    drawshape(local_1c,local_18,local_14);
    grabshape(ppppuVar3,local_2c,local_30);
    pppppuVar10 = (undefined4 *****)local_30;
LAB_0001d8c0:
    drawshape_remap(pointer_shapes,local_2c,local_30);
    uVar16 = CONCAT44(extraout_EDX,local_30);
    local_18 = local_2c;
    local_14 = local_30;
  }
  goto LAB_0001d83a;
}


// ================================================================================================
// menu_page_a @ 0x1df03 [__watcall]
// ================================================================================================

undefined4 __watcall
menu_page_a(int *param_1,undefined4 param_2,undefined4 unaff_EBX,undefined4 unaff_ECX,
           undefined4 param_5)

{
  undefined4 ****ppppuVar1;
  undefined4 ****ppppuVar2;
  int iVar3;
  int *piVar4;
  undefined4 *puVar5;
  int iVar6;
  uint uVar7;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 uVar8;
  undefined4 *****pppppuVar9;
  int iVar10;
  undefined4 *****pppppuVar11;
  undefined4 *****pppppuVar12;
  undefined4 *puVar13;
  byte bVar14;
  ulonglong uVar15;
  undefined8 uVar16;
  undefined4 *****pppppuVar17;
  int local_a4 [8];
  int local_74 [8];
  int *local_54 [4];
  int local_44;
  undefined4 ****local_40;
  int local_3c;
  int local_38;
  undefined4 ****local_34;
  int local_30;
  int local_2c;
  int local_28;
  int local_24;
  undefined4 ****local_20;
  int local_1c;
  undefined4 ****local_18;
  undefined4 ****local_14;
  undefined4 local_10;
  
  bVar14 = 0;
  __CHK(0xc4);
  local_38 = 0;
  local_3c = 0;
  local_14 = (undefined4 *****)0x0;
  local_54[3] = (int *)0x0;
  local_54[2] = (int *)0x0;
  local_54[1] = (int *)0x0;
  local_74[7] = 0;
  local_74[6] = 0;
  local_74[5] = 0;
  local_74[4] = 0;
  local_74[3] = 0;
  local_74[2] = 0;
  local_74[1] = 0;
  local_74[0] = 0;
  local_a4[1] = 0;
  local_a4[0] = 0;
  local_54[0] = param_1;
  local_20 = (undefined4 ****)
             allocmem(aPointer_c0b54,
                      (((int)pointer_shapes[1] >> 0x10) + 1) *
                      ((*(int *)((int)pointer_shapes + 2) >> 0x10) + 1) + 0x11,0x20);
  pppppuVar11 = (undefined4 *****)local_20 + (uint)bVar14 * -2 + 1;
  pppppuVar9 = pointer_shapes + (uint)bVar14 * -2 + 1;
  *local_20 = *pointer_shapes;
  pppppuVar12 = pppppuVar11 + (uint)bVar14 * -2 + 1;
  pppppuVar17 = pppppuVar9 + (uint)bVar14 * -2 + 1;
  *pppppuVar11 = *pppppuVar9;
  *pppppuVar12 = *pppppuVar17;
  pppppuVar12[(uint)bVar14 * -2 + 1] = pppppuVar17[(uint)bVar14 * -2 + 1];
  *(undefined *)(pppppuVar12 + (uint)bVar14 * -2 + 1 + (uint)bVar14 * -2 + 1) =
       *(undefined *)(pppppuVar17 + (uint)bVar14 * -2 + 1 + (uint)bVar14 * -2 + 1);
  *(short *)((undefined4 *****)local_20 + 1) = *(short *)(pointer_shapes + 1) + 1;
  *(short *)((int)local_20 + 6) = *(short *)((int)pointer_shapes + 6) + 1;
  local_30 = (*local_54[0] + local_54[0][2]) / 2;
  local_34 = (undefined4 ****)((local_54[0][1] + local_54[0][3]) / 2);
  local_1c = local_30;
  local_18 = local_34;
  if (stats_playoffs == 0) {
    iVar10 = 0;
    do {
      if (stats_selected_team == (&standings_order)[iVar10]) {
        local_3c = iVar10;
      }
      iVar10 = iVar10 + 1;
    } while (iVar10 < 0x1a);
    if ((uint)*(byte *)(standings_rows + 0xd + (&standings_order)[local_3c] * 0x1a) % 2 == 0) {
      iVar10 = 0xa5;
    }
    else {
      iVar10 = 0x14a;
    }
    if (*(byte *)(standings_rows + 0xd + (&standings_order)[local_3c] * 0x1a) < 2) {
      uVar8 = 0;
    }
    else {
      uVar8 = 0x140;
    }
    if (local_3c < 0xc) {
      iVar6 = 6;
      iVar3 = local_3c;
    }
    else {
      iVar3 = local_3c + -0xc;
      iVar6 = 7;
    }
    fillrect2(uVar8,iVar10 + (iVar3 % iVar6) * 0xd,0x140,0xd,0x80);
  }
  else {
    local_3c = stats_selected_team;
    if ((&dword_dc7b8)[stats_selected_team] != 0x1a) {
      standings_move_highlight(&local_3c,0);
    }
  }
  ppppuVar1 = local_18;
  iVar10 = local_1c;
  grabshape(local_20,local_1c,local_18);
  pppppuVar9 = pointer_shapes;
  drawshape_remap(pointer_shapes,iVar10,ppppuVar1);
  setmouselimits(0,0,0x280,0x1e0);
  setmousepos(iVar10,ppppuVar1);
  (*(code *)mouse_update_callback)();
  uVar15 = event_queue_reset();
LAB_0001e287:
  uVar7 = 0;
  do {
    iVar10 = event_queue_pop((int)uVar15,(int)(uVar15 >> 0x20),pppppuVar9);
    if (iVar10 == 0) break;
    pppppuVar9 = &local_34;
    uVar15 = (*ui_poll_callback)();
    uVar7 = (uint)uVar15;
  } while ((uVar15 & 2) == 0);
  ppppuVar1 = local_20;
  if ((uVar7 & 2) == 0) goto code_r0x0001e2ab;
  iVar3 = hit_test_menus(local_30,local_34,local_54,local_14,&stack0xffffff7c,local_a4,&local_40,
                         &local_44);
  ppppuVar1 = local_18;
  iVar10 = local_1c;
  if (iVar3 != 0) {
    if (local_54[(int)local_40][local_44 * 8 + 5] == 0) {
      if (local_54[(int)local_40][local_44 * 8 + 6] == 0) {
        drawshape(local_20,local_1c,local_18);
        menu_item_draw_normal
                  (local_54[(int)local_40] + local_74[(int)local_40] * 8,local_a4[(int)local_40 * 2]
                   ,local_a4[(int)local_40 * 2 + 1],unaff_EBX,unaff_ECX,param_5);
        ppppuVar1 = local_40;
        iVar6 = local_44;
        local_74[(int)local_40] = local_44;
        iVar10 = local_a4[(int)ppppuVar1 * 2 + 1];
        iVar3 = local_a4[(int)ppppuVar1 * 2];
        piVar4 = local_54[(int)ppppuVar1] + iVar6 * 8;
        uVar8 = unaff_ECX;
      }
      else {
        drawshape(local_20,local_1c,local_18);
        pppppuVar9 = (undefined4 *****)local_14;
        if (local_14 != local_40) {
          for (; (int)local_40 < (int)pppppuVar9;
              pppppuVar9 = (undefined4 *****)((int)pppppuVar9 + -1)) {
            local_74[(int)pppppuVar9] = 0;
            if (local_74[(int)(pppppuVar9 + 1)] != 0) {
              drawshape(local_74[(int)(pppppuVar9 + 1)],local_a4[(int)pppppuVar9 * 2],
                        local_a4[(int)pppppuVar9 * 2 + 1]);
              local_a4[(int)pppppuVar9 * 2 + 1] = 0;
              local_a4[(int)pppppuVar9 * 2] = 0;
              freemem(local_74[(int)(pppppuVar9 + 1)]);
              local_74[(int)(pppppuVar9 + 1)] = 0;
              local_54[(int)pppppuVar9] = (int *)0x0;
              local_74[(int)(pppppuVar9 + -1)] = 0;
            }
          }
          local_14 = local_40;
        }
        ppppuVar2 = local_14;
        menu_item_draw_normal
                  (local_54[(int)local_14] + local_74[(int)local_14] * 8,local_a4[(int)local_14 * 2]
                   ,local_a4[(int)local_14 * 2 + 1],unaff_EBX,unaff_ECX,param_5);
        iVar10 = local_44;
        local_74[(int)ppppuVar2] = local_44;
        menu_item_draw_selected
                  (local_54[(int)ppppuVar2] + iVar10 * 8,local_a4[(int)ppppuVar2 * 2],
                   local_a4[(int)ppppuVar2 * 2 + 1],unaff_EBX,unaff_ECX,param_5);
        ppppuVar1 = local_40;
        iVar10 = local_44;
        pppppuVar9 = (undefined4 *****)((int)ppppuVar2 + 1);
        local_14 = pppppuVar9;
        local_54[(int)pppppuVar9] = (int *)local_54[(int)local_40][local_44 * 8 + 6];
        piVar4 = local_54[(int)ppppuVar1] + iVar10 * 8;
        local_74[(int)(pppppuVar9 + -1)] = piVar4[7];
        if (pppppuVar9 == (undefined4 *****)0x1) {
          iVar10 = *piVar4;
        }
        else {
          iVar10 = piVar4[2];
        }
        local_a4[(int)local_14 * 2] = iVar10 + local_a4[(int)local_14 * 2 + -2];
        if ((undefined4 *****)local_14 == (undefined4 *****)0x1) {
          iVar10 = local_54[(int)local_40][local_44 * 8 + 3];
        }
        else {
          iVar10 = local_54[(int)local_40][local_44 * 8 + 1];
        }
        local_24 = (int)local_14 * 8;
        local_a4[(int)local_14 * 2 + 1] = iVar10 + local_a4[(int)local_14 * 2 + -1];
        ppppuVar1 = local_14;
        piVar4 = local_54[(int)local_14];
        local_28 = (piVar4[local_74[(int)(local_14 + -1)] * 8 + -6] - *piVar4) + 1;
        local_2c = (piVar4[local_74[(int)(local_14 + -1)] * 8 + -5] - piVar4[1]) + 1;
        puVar5 = (undefined4 *)allocmem(aMenubuff_c0b5c,local_28 * local_2c + 0x11,0x20);
        local_74[(int)(ppppuVar1 + 1)] = (int)puVar5;
        puVar13 = puVar5 + (uint)bVar14 * -2 + 1;
        pppppuVar9 = pointer_shapes + (uint)bVar14 * -2 + 1;
        *puVar5 = *pointer_shapes;
        puVar5 = puVar13 + (uint)bVar14 * -2 + 1;
        pppppuVar17 = pppppuVar9 + (uint)bVar14 * -2 + 1;
        *puVar13 = *pppppuVar9;
        *puVar5 = *pppppuVar17;
        puVar5[(uint)bVar14 * -2 + 1] = pppppuVar17[(uint)bVar14 * -2 + 1];
        *(undefined *)(puVar5 + (uint)bVar14 * -2 + 1 + (uint)bVar14 * -2 + 1) =
             *(undefined *)(pppppuVar17 + (uint)bVar14 * -2 + 1 + (uint)bVar14 * -2 + 1);
        *(short *)(local_74[(int)(ppppuVar1 + 1)] + 4) = (short)local_28;
        *(short *)(local_74[(int)(ppppuVar1 + 1)] + 6) = (short)local_2c;
        grabshape(local_74[(int)(ppppuVar1 + 1)],*(undefined4 *)((int)local_a4 + local_24),
                  *(undefined4 *)((int)local_a4 + local_24 + 4));
        uVar8 = unaff_ECX;
        draw_menu(local_54[(int)ppppuVar1],local_74[(int)(ppppuVar1 + -1)],
                  *(undefined4 *)((int)local_a4 + local_24),
                  *(undefined4 *)((int)local_a4 + local_24 + 4),unaff_EBX,unaff_ECX,param_5);
        local_74[(int)ppppuVar1] = 0;
        iVar10 = *(int *)((int)local_a4 + local_24 + 4);
        iVar3 = *(int *)((int)local_a4 + local_24);
        piVar4 = local_54[(int)ppppuVar1];
      }
    }
    else {
      if (local_44 == local_74[(int)local_40]) {
        drawshape(local_20,local_1c,local_18);
        for (iVar10 = 3; -1 < iVar10; iVar10 = iVar10 + -1) {
          if (local_74[iVar10 + 4] != 0) {
            drawshape(local_74[iVar10 + 4],local_a4[iVar10 * 2],local_a4[iVar10 * 2 + 1]);
            local_a4[iVar10 * 2 + 1] = 0;
            local_a4[iVar10 * 2] = 0;
            freemem(local_74[iVar10 + 4]);
          }
        }
        local_14 = (undefined4 *****)0x0;
        if (stats_playoffs == 0) {
          stats_current_arg = (&standings_order)[local_3c];
          local_38 = stats_current_arg;
          if ((uint)*(byte *)(standings_rows + 0xd + (&standings_order)[local_3c] * 0x1a) % 2 == 0)
          {
            iVar10 = 0xa5;
          }
          else {
            iVar10 = 0x14a;
          }
          if (*(byte *)(standings_rows + 0xd + (&standings_order)[local_3c] * 0x1a) < 2) {
            uVar8 = 0;
          }
          else {
            uVar8 = 0x140;
          }
          if (local_3c < 0xc) {
            iVar6 = 6;
            iVar3 = local_3c;
          }
          else {
            iVar3 = local_3c + -0xc;
            iVar6 = 7;
          }
          stats_selected_team = stats_current_arg;
          fillrect2(uVar8,iVar10 + (iVar3 % iVar6) * 0xd,0x140,0xd,0x80);
        }
        else {
          stats_current_arg = (&dword_dc7b8)[local_3c];
          stats_selected_team = local_3c;
          if ((&dword_dc7b8)[local_3c] != 0x1a) {
            standings_move_highlight(&local_3c,0);
          }
        }
        iVar10 = (*(code *)local_54[(int)local_40][local_44 * 8 + 5])();
        local_54[3] = (int *)0x0;
        local_54[2] = (int *)0x0;
        local_54[1] = (int *)0x0;
        local_74[6] = 0;
        local_74[5] = 0;
        local_74[4] = 0;
        local_74[3] = 0;
        local_74[2] = 0;
        local_74[1] = 0;
        if (iVar10 != 1) {
          if (stats_playoffs == 0) {
            iVar10 = 0;
            do {
              if (local_38 == (&standings_order)[iVar10]) {
                local_3c = iVar10;
              }
              iVar10 = iVar10 + 1;
            } while (iVar10 < 0x1a);
            if ((uint)*(byte *)(standings_rows + 0xd + (&standings_order)[local_3c] * 0x1a) % 2 == 0
               ) {
              iVar10 = 0xa5;
            }
            else {
              iVar10 = 0x14a;
            }
            if (*(byte *)((&standings_order)[local_3c] * 0x1a + 0xd + standings_rows) < 2) {
              uVar8 = 0;
            }
            else {
              uVar8 = 0x140;
            }
            if (local_3c < 0xc) {
              iVar6 = 6;
              iVar3 = local_3c;
            }
            else {
              iVar3 = local_3c + -0xc;
              iVar6 = 7;
            }
            fillrect2(uVar8,iVar10 + (iVar3 % iVar6) * 0xd,0x140,0xd,0x80);
          }
          else {
            local_3c = stats_selected_team;
            if ((&dword_dc7b8)[stats_selected_team] != 0x1a) {
              standings_move_highlight(&local_3c,0);
            }
          }
          ppppuVar1 = local_18;
          iVar10 = local_1c;
          setmousepos(local_1c,local_18);
          local_30 = iVar10;
          local_34 = ppppuVar1;
          event_queue_reset();
          pppppuVar17 = (undefined4 *****)local_20;
          goto LAB_0001e24d;
        }
        goto LAB_0001defd;
      }
      drawshape(local_20,local_1c,local_18);
      menu_item_draw_normal
                (local_54[(int)local_40] + local_74[(int)local_40] * 8,local_a4[(int)local_40 * 2],
                 local_a4[(int)local_40 * 2 + 1],unaff_EBX,unaff_ECX,param_5);
      ppppuVar1 = local_40;
      local_74[(int)local_40] = local_44;
      iVar10 = local_a4[(int)ppppuVar1 * 2 + 1];
      iVar3 = local_a4[(int)ppppuVar1 * 2];
      piVar4 = local_54[(int)ppppuVar1] + local_74[(int)ppppuVar1] * 8;
      uVar8 = unaff_ECX;
    }
    menu_item_draw_selected(piVar4,iVar3,iVar10,unaff_EBX,unaff_ECX,param_5);
    pppppuVar17 = (undefined4 *****)local_20;
    unaff_ECX = uVar8;
    goto LAB_0001e24d;
  }
  drawshape(local_20,local_1c,local_18);
  iVar3 = menu_page_c(local_30,local_34,&local_38);
  if (iVar3 == 0) {
    drawshape(local_20,iVar10,ppppuVar1);
    for (iVar10 = 3; -1 < iVar10; iVar10 = iVar10 + -1) {
      if (local_74[iVar10 + 4] != 0) {
        drawshape(local_74[iVar10 + 4],local_a4[iVar10 * 2],local_a4[iVar10 * 2 + 1]);
        local_a4[iVar10 * 2 + 1] = 0;
        local_a4[iVar10 * 2] = 0;
        freemem(local_74[iVar10 + 4]);
      }
    }
    local_14 = (undefined4 *****)0x0;
    local_54[3] = (int *)0x0;
    local_54[2] = (int *)0x0;
    local_54[1] = (int *)0x0;
    local_74[6] = 0;
    local_74[5] = 0;
    local_74[4] = 0;
    local_74[3] = 0;
    local_74[2] = 0;
    local_74[1] = 0;
    pppppuVar17 = (undefined4 *****)local_20;
  }
  else {
    pppppuVar17 = (undefined4 *****)local_20;
    if (local_3c == local_38) {
      if ((stats_playoffs == 0) || ((&dword_dc7b8)[local_3c] != 0x1a)) {
        for (iVar10 = 3; -1 < iVar10; iVar10 = iVar10 + -1) {
          if (local_74[iVar10 + 4] != 0) {
            drawshape(local_74[iVar10 + 4],local_a4[iVar10 * 2],local_a4[iVar10 * 2 + 1]);
            local_a4[iVar10 * 2 + 1] = 0;
            local_a4[iVar10 * 2] = 0;
            freemem(local_74[iVar10 + 4]);
          }
        }
        if (stats_playoffs == 0) {
          stats_current_arg = (&standings_order)[local_3c];
          stats_selected_team = stats_current_arg;
          local_38 = stats_current_arg;
        }
        else {
          stats_current_arg = (&dword_dc7b8)[local_3c];
          stats_selected_team = local_3c;
        }
        menu_show_team_roster();
        local_74[7] = 0;
LAB_0001defd:
        local_54[3] = (int *)0x0;
        local_54[2] = (int *)0x0;
        local_54[1] = (int *)0x0;
        local_74[6] = 0;
        local_74[5] = 0;
        local_74[4] = 0;
        local_74[3] = 0;
        local_74[2] = 0;
        local_74[1] = 0;
        freemem(local_20);
        return 0;
      }
    }
    else if (stats_playoffs == 0) {
      if ((uint)*(byte *)(standings_rows + 0xd + (&standings_order)[local_3c] * 0x1a) % 2 == 0) {
        iVar10 = 0xa5;
      }
      else {
        iVar10 = 0x14a;
      }
      if (*(byte *)((&standings_order)[local_3c] * 0x1a + 0xd + standings_rows) < 2) {
        uVar8 = 0;
      }
      else {
        uVar8 = 0x140;
      }
      if (local_3c < 0xc) {
        iVar6 = 6;
        iVar3 = local_3c;
      }
      else {
        iVar3 = local_3c + -0xc;
        iVar6 = 7;
      }
      fillrect2(uVar8,iVar10 + (iVar3 % iVar6) * 0xd,0x140,0xd,0x80);
      local_3c = local_38;
      if ((uint)*(byte *)(standings_rows + 0xd + (&standings_order)[local_38] * 0x1a) % 2 == 0) {
        iVar10 = 0xa5;
      }
      else {
        iVar10 = 0x14a;
      }
      if (*(byte *)(standings_rows + 0xd + (&standings_order)[local_38] * 0x1a) < 2) {
        uVar8 = 0;
      }
      else {
        uVar8 = 0x140;
      }
      if (local_38 < 0xc) {
        iVar6 = 6;
        iVar3 = local_38;
      }
      else {
        iVar3 = local_38 + -0xc;
        iVar6 = 7;
      }
      fillrect2(uVar8,iVar10 + (iVar3 % iVar6) * 0xd,0x140,0xd,0x80);
      pppppuVar17 = (undefined4 *****)local_20;
    }
    else if (((&dword_dc7b8)[local_38] != 0x1a) && ((&dword_dc7b8)[local_3c] != 0x1a)) {
      standings_move_highlight(&local_3c,&local_38);
      pppppuVar17 = (undefined4 *****)local_20;
    }
  }
  goto LAB_0001e24d;
code_r0x0001e2ab:
  uVar8 = 0;
  local_10 = 0;
  if (stats_playoffs == 1) {
    uVar16 = standings_menu_stub(local_30,&local_3c,local_20,local_1c,local_18);
    ppppuVar2 = local_14;
    uVar8 = (undefined4)((ulonglong)uVar16 >> 0x20);
    local_10 = (int)uVar16;
    pppppuVar9 = (undefined4 *****)ppppuVar1;
    if ((short)uVar16 != 0) {
      pppppuVar9 = (undefined4 *****)local_14;
      if ((undefined4 *****)local_14 != (undefined4 *****)0x0) {
        for (; -1 < (int)pppppuVar9; pppppuVar9 = (undefined4 *****)((int)pppppuVar9 + -1)) {
          if (local_74[(int)(pppppuVar9 + 1)] != 0) {
            drawshape(local_74[(int)(pppppuVar9 + 1)],local_a4[(int)pppppuVar9 * 2],
                      local_a4[(int)pppppuVar9 * 2 + 1]);
            local_a4[(int)pppppuVar9 * 2 + 1] = 0;
            local_a4[(int)pppppuVar9 * 2] = 0;
            freemem(local_74[(int)(pppppuVar9 + 1)]);
            local_74[(int)(pppppuVar9 + 1)] = 0;
            local_54[(int)pppppuVar9] = (int *)0x0;
            local_74[(int)(pppppuVar9 + -1)] = 0;
          }
        }
        local_14 = (undefined4 *****)0x0;
      }
      standings_screen();
      if ((&dword_dc7b8)[local_3c] != 0x1a) {
        standings_move_highlight(&local_3c,0);
      }
      grabshape(local_20,local_1c,local_18);
      uVar8 = extraout_EDX;
      pppppuVar9 = (undefined4 *****)ppppuVar2;
    }
  }
  pppppuVar17 = (undefined4 *****)local_20;
  uVar15 = CONCAT44(uVar8,local_34);
  if (((local_30 == local_1c) && (local_34 == local_18)) && ((short)local_10 == 0))
  goto LAB_0001e287;
  drawshape(local_20,local_1c,local_18);
LAB_0001e24d:
  grabshape(pppppuVar17,local_30,local_34);
  pppppuVar9 = (undefined4 *****)local_34;
  drawshape_remap(pointer_shapes,local_30,local_34);
  uVar15 = CONCAT44(extraout_EDX_00,local_34);
  local_1c = local_30;
  local_18 = local_34;
  goto LAB_0001e287;
}


// ================================================================================================
// menu_page_b @ 0x1ed96 [__watcall]
// ================================================================================================

undefined4 __watcall
menu_page_b(int *param_1,undefined4 param_2,undefined4 unaff_EBX,undefined4 unaff_ECX,
           undefined4 param_5)

{
  ulonglong uVar1;
  undefined4 ****ppppuVar2;
  undefined4 ****ppppuVar3;
  int iVar4;
  int *piVar5;
  undefined4 *puVar6;
  undefined4 uVar7;
  int iVar8;
  undefined4 extraout_EDX;
  int extraout_EDX_00;
  undefined4 *****pppppuVar9;
  int iVar10;
  undefined4 *puVar11;
  undefined4 *puVar12;
  undefined4 *puVar13;
  byte bVar14;
  ulonglong uVar15;
  undefined8 uVar16;
  int local_a0 [8];
  int *local_80;
  int local_7c;
  int local_78;
  int local_74;
  int local_60 [9];
  int local_3c;
  int local_38;
  undefined4 ****local_34;
  undefined4 ****local_30;
  int local_2c;
  int local_28;
  int local_24;
  undefined4 *local_20;
  undefined4 ****local_1c;
  undefined4 ****local_18;
  int local_14;
  int local_10;
  
  bVar14 = 0;
  __CHK(0xc0);
  local_38 = 0;
  local_14 = 0;
  local_10 = 0;
  local_74 = 0;
  local_78 = 0;
  local_7c = 0;
  local_60[3] = 0;
  local_60[2] = 0;
  local_60[1] = 0;
  local_60[0] = 0;
  local_60[7] = 0;
  local_60[6] = 0;
  local_60[5] = 0;
  local_60[4] = 0;
  local_a0[1] = 0;
  local_a0[0] = 0;
  pppppuVar9 = (undefined4 *****)(*(int *)((int)pointer_shapes + 2) >> 0x10);
  local_80 = param_1;
  local_20 = (undefined4 *)
             allocmem(aPointer_c0b54,
                      ((int)pppppuVar9 + 1) * (((int)pointer_shapes[1] >> 0x10) + 1) + 0x11,0x20);
  puVar11 = local_20 + (uint)bVar14 * -2 + 1;
  puVar6 = pointer_shapes + (uint)bVar14 * -2 + 1;
  *local_20 = *pointer_shapes;
  puVar12 = puVar11 + (uint)bVar14 * -2 + 1;
  puVar13 = puVar6 + (uint)bVar14 * -2 + 1;
  *puVar11 = *puVar6;
  *puVar12 = *puVar13;
  puVar12[(uint)bVar14 * -2 + 1] = puVar13[(uint)bVar14 * -2 + 1];
  *(undefined *)(puVar12 + (uint)bVar14 * -2 + 1 + (uint)bVar14 * -2 + 1) =
       *(undefined *)(puVar13 + (uint)bVar14 * -2 + 1 + (uint)bVar14 * -2 + 1);
  *(short *)(local_20 + 1) = *(short *)(pointer_shapes + 1) + 1;
  *(short *)((int)local_20 + 6) = *(short *)((int)pointer_shapes + 6) + 1;
  local_30 = (undefined4 ****)((*local_80 + local_80[2]) / 2);
  local_34 = (undefined4 ****)((local_80[1] + local_80[3]) / 2);
  local_1c = local_30;
  local_18 = local_34;
  if ((byte_dc836 == 'G') || (byte_dc836 == 'g')) {
    for (iVar10 = 0; iVar8 = local_14, iVar10 < dword_dc6b8; iVar10 = iVar10 + 1) {
      pppppuVar9 = (undefined4 *****)
                   (*(int *)(&unk_dc73c + (&roster_goalie_order)[iVar10] * 4) * 0x34);
      iVar8 = str_prefix_differs(&unk_dc837,(int)pppppuVar9 + dword_dd11c + 3);
      if ((iVar8 == 0) &&
         (iVar8 = str_prefix_differs(&unk_dc847,(int)pppppuVar9 + dword_dd11c + 0x13), iVar8 == 0))
      {
        iVar8 = dword_dc750 + iVar10;
        break;
      }
    }
  }
  else {
    iVar8 = local_14;
    if (byte_dc836 != '\0') {
      for (iVar10 = 0; iVar8 = local_14, iVar10 < dword_dc750; iVar10 = iVar10 + 1) {
        pppppuVar9 = (undefined4 *****)
                     (*(int *)(&unk_dc754 + (&roster_skater_order)[iVar10] * 4) * 0x34);
        iVar8 = str_prefix_differs(&unk_dc837,(int)pppppuVar9 + dword_dd11c + 3);
        if ((iVar8 == 0) &&
           (iVar4 = str_prefix_differs(&unk_dc847,(int)pppppuVar9 + dword_dd11c + 0x13),
           iVar8 = iVar10, iVar4 == 0)) break;
      }
    }
  }
  local_14 = iVar8;
  if (local_14 < dword_dc750) {
    iVar10 = local_14 * 0xd + 0x43;
  }
  else {
    iVar10 = (local_14 - dword_dc750) * 0xd + 0x1a8;
  }
  fillrect2(0,iVar10,0x280,0xd,0x80);
  ppppuVar2 = local_1c;
  grabshape(local_20,local_1c,local_18);
  ppppuVar3 = local_18;
  drawshape_remap(pointer_shapes,ppppuVar2,local_18);
  setmouselimits(0,0,0x280,0x1e0);
  setmousepos(ppppuVar2,ppppuVar3);
  (*(code *)mouse_update_callback)();
  uVar15 = event_queue_reset();
LAB_0001f03d:
  uVar7 = 0;
  do {
    uVar16 = event_queue_pop((int)uVar15,(int)(uVar15 >> 0x20),pppppuVar9);
    uVar1 = CONCAT44((int)((ulonglong)uVar16 >> 0x20),uVar7);
    if ((int)uVar16 == 0) break;
    pppppuVar9 = &local_34;
    uVar15 = (*ui_poll_callback)();
    uVar7 = (undefined4)uVar15;
    uVar1 = uVar15;
  } while ((uVar15 & 2) == 0);
  puVar6 = local_20;
  uVar15 = CONCAT44((int)(uVar1 >> 0x20),local_34);
  if ((uVar1 & 2) == 0) goto code_r0x0001f065;
  iVar10 = hit_test_menus(local_30,local_34,&local_80,local_10,&stack0xffffff90,local_a0,&local_3c,
                          local_60 + 8);
  ppppuVar3 = local_18;
  ppppuVar2 = local_1c;
  puVar6 = local_20;
  if (iVar10 == 0) {
    drawshape(local_20,local_1c,local_18);
    iVar10 = stats_row_at(local_30,local_34,&local_38);
    if (iVar10 == 0) {
      drawshape(puVar6,ppppuVar2,ppppuVar3);
      for (iVar10 = 3; -1 < iVar10; iVar10 = iVar10 + -1) {
        if (local_60[iVar10] != 0) {
          drawshape(local_60[iVar10],local_a0[iVar10 * 2],local_a0[iVar10 * 2 + 1]);
          local_a0[iVar10 * 2 + 1] = 0;
          local_a0[iVar10 * 2] = 0;
          freemem(local_60[iVar10]);
        }
      }
      local_10 = 0;
      local_74 = 0;
      local_78 = 0;
      local_7c = 0;
      local_60[3] = 0;
      local_60[2] = 0;
      local_60[1] = 0;
      local_60[0] = 0;
      local_60[7] = 0;
      local_60[6] = 0;
      local_60[5] = 0;
    }
    else {
      for (iVar10 = 3; -1 < iVar10; iVar10 = iVar10 + -1) {
        if (local_60[iVar10] != 0) {
          drawshape(local_60[iVar10],local_a0[iVar10 * 2],local_a0[iVar10 * 2 + 1]);
          local_a0[iVar10 * 2 + 1] = 0;
          local_a0[iVar10 * 2] = 0;
          freemem(local_60[iVar10]);
        }
      }
      local_10 = 0;
      local_74 = 0;
      local_78 = 0;
      local_7c = 0;
      local_60[3] = 0;
      local_60[2] = 0;
      local_60[1] = 0;
      local_60[0] = 0;
      local_60[7] = 0;
      local_60[6] = 0;
      local_60[5] = 0;
      if (local_14 == local_38) {
        for (iVar10 = 3; -1 < iVar10; iVar10 = iVar10 + -1) {
          if (local_60[iVar10] != 0) {
            drawshape(local_60[iVar10],local_a0[iVar10 * 2],local_a0[iVar10 * 2 + 1]);
            local_a0[iVar10 * 2 + 1] = 0;
            local_a0[iVar10 * 2] = 0;
            freemem(local_60[iVar10]);
          }
        }
        if (local_38 < dword_dc750) {
          iVar10 = *(int *)(&unk_dc754 + (&roster_skater_order)[local_38] * 4);
        }
        else {
          iVar10 = *(int *)(&unk_dc73c + (&roster_goalie_order)[local_38 - dword_dc750] * 4);
        }
        puVar6 = (undefined4 *)(dword_dd11c + iVar10 * 0x34);
        puVar13 = (undefined4 *)&card_player_record;
        for (iVar8 = 0xd; iVar8 != 0; iVar8 = iVar8 + -1) {
          *puVar13 = *puVar6;
          puVar6 = puVar6 + (uint)bVar14 * -2 + 1;
          puVar13 = puVar13 + (uint)bVar14 * -2 + 1;
        }
        dword_c6a60 = 0;
        dword_dd120 = 0;
        menu_show_player_stats();
        local_60[7] = extraout_EDX_00;
LAB_0001defd:
        local_7c = local_60[7];
        local_78 = local_60[7];
        local_74 = local_60[7];
        local_60[0] = local_60[7];
        local_60[1] = local_60[7];
        local_60[2] = local_60[7];
        local_60[3] = local_60[7];
        local_60[5] = local_60[7];
        local_60[6] = local_60[7];
        freemem(local_20);
        return 0;
      }
      if (local_14 < dword_dc750) {
        iVar10 = local_14 * 0xd + 0x43;
      }
      else {
        iVar10 = (local_14 - dword_dc750) * 0xd + 0x1a8;
      }
      fillrect2(0,iVar10,0x280,0xd,0x80);
      local_14 = local_38;
      if (local_38 < dword_dc750) {
        iVar10 = local_38 * 0xd + 0x43;
      }
      else {
        iVar10 = (local_38 - dword_dc750) * 0xd + 0x1a8;
      }
      fillrect2(0,iVar10,0x280,0xd,0x80);
    }
  }
  else {
    if ((&local_80)[local_3c][local_60[8] * 8 + 5] == 0) {
      if ((&local_80)[local_3c][local_60[8] * 8 + 6] == 0) {
        drawshape(local_20,local_1c,local_18);
        menu_item_draw_normal
                  ((&local_80)[local_3c] + local_60[local_3c + 4] * 8,local_a0[local_3c * 2],
                   local_a0[local_3c * 2 + 1],unaff_EBX,unaff_ECX,param_5);
        iVar10 = local_3c;
        local_60[local_3c + 4] = local_60[8];
        uVar7 = unaff_ECX;
        goto LAB_0001f482;
      }
      drawshape(local_20,local_1c,local_18);
      iVar10 = local_10;
      uVar7 = unaff_ECX;
      if (local_10 != local_3c) {
        for (; local_3c < iVar10; iVar10 = iVar10 + -1) {
          local_60[iVar10 + 4] = 0;
          if (local_60[iVar10] != 0) {
            drawshape(local_60[iVar10],local_a0[iVar10 * 2],local_a0[iVar10 * 2 + 1]);
            local_a0[iVar10 * 2 + 1] = 0;
            local_a0[iVar10 * 2] = 0;
            freemem(local_60[iVar10]);
            local_60[iVar10] = 0;
            (&local_80)[iVar10] = (int *)0x0;
            *(undefined4 *)(&stack0xffffff90 + iVar10 * 4) = 0;
          }
        }
        local_10 = local_3c;
        uVar7 = unaff_ECX;
      }
      iVar10 = local_10;
      menu_item_draw_normal
                ((&local_80)[local_10] + local_60[local_10 + 4] * 8,local_a0[local_10 * 2],
                 local_a0[local_10 * 2 + 1],unaff_EBX,uVar7,param_5);
      iVar8 = local_60[8];
      local_60[iVar10 + 4] = local_60[8];
      menu_item_draw_selected
                ((&local_80)[iVar10] + iVar8 * 8,local_a0[iVar10 * 2],local_a0[iVar10 * 2 + 1],
                 unaff_EBX,uVar7,param_5);
      iVar4 = local_3c;
      iVar8 = local_60[8];
      iVar10 = iVar10 + 1;
      local_10 = iVar10;
      (&local_80)[iVar10] = (int *)(&local_80)[local_3c][local_60[8] * 8 + 6];
      piVar5 = (&local_80)[iVar4] + iVar8 * 8;
      *(int *)(&stack0xffffff90 + iVar10 * 4) = piVar5[7];
      if (iVar10 == 1) {
        iVar10 = *piVar5;
      }
      else {
        iVar10 = piVar5[2];
      }
      local_a0[local_10 * 2] = iVar10 + local_a0[local_10 * 2 + -2];
      if (local_10 == 1) {
        iVar10 = (&local_80)[local_3c][local_60[8] * 8 + 3];
      }
      else {
        iVar10 = (&local_80)[local_3c][local_60[8] * 8 + 1];
      }
      local_24 = local_10 * 8;
      local_a0[local_10 * 2 + 1] = iVar10 + local_a0[local_10 * 2 + -1];
      iVar10 = local_10;
      piVar5 = (&local_80)[local_10];
      local_28 = (piVar5[*(int *)(&stack0xffffff90 + local_10 * 4) * 8 + -6] - *piVar5) + 1;
      local_2c = (piVar5[*(int *)(&stack0xffffff90 + local_10 * 4) * 8 + -5] - piVar5[1]) + 1;
      puVar6 = (undefined4 *)allocmem(aMenubuff_c0b5c,local_28 * local_2c + 0x11,0x20);
      local_60[iVar10] = (int)puVar6;
      puVar11 = puVar6 + (uint)bVar14 * -2 + 1;
      puVar13 = pointer_shapes + (uint)bVar14 * -2 + 1;
      *puVar6 = *pointer_shapes;
      puVar12 = puVar11 + (uint)bVar14 * -2 + 1;
      puVar6 = puVar13 + (uint)bVar14 * -2 + 1;
      *puVar11 = *puVar13;
      *puVar12 = *puVar6;
      puVar12[(uint)bVar14 * -2 + 1] = puVar6[(uint)bVar14 * -2 + 1];
      *(undefined *)(puVar12 + (uint)bVar14 * -2 + 1 + (uint)bVar14 * -2 + 1) =
           *(undefined *)(puVar6 + (uint)bVar14 * -2 + 1 + (uint)bVar14 * -2 + 1);
      *(short *)(local_60[iVar10] + 4) = (short)local_28;
      *(short *)(local_60[iVar10] + 6) = (short)local_2c;
      grabshape(local_60[iVar10],*(undefined4 *)((int)local_a0 + local_24),
                *(undefined4 *)((int)local_a0 + local_24 + 4));
      unaff_ECX = uVar7;
      draw_menu((&local_80)[iVar10],*(undefined4 *)(&stack0xffffff90 + iVar10 * 4),
                *(undefined4 *)((int)local_a0 + local_24),
                *(undefined4 *)((int)local_a0 + local_24 + 4),unaff_EBX,uVar7,param_5);
      local_60[iVar10 + 4] = 0;
      iVar8 = *(int *)((int)local_a0 + local_24 + 4);
      iVar4 = *(int *)((int)local_a0 + local_24);
      piVar5 = (&local_80)[iVar10];
    }
    else {
      if (local_60[8] == local_60[local_3c + 4]) {
        drawshape(local_20,local_1c,local_18);
        for (iVar10 = 3; -1 < iVar10; iVar10 = iVar10 + -1) {
          if (local_60[iVar10] != 0) {
            drawshape(local_60[iVar10],local_a0[iVar10 * 2],local_a0[iVar10 * 2 + 1]);
            local_a0[iVar10 * 2 + 1] = 0;
            local_a0[iVar10 * 2] = 0;
            freemem(local_60[iVar10]);
          }
        }
        local_10 = 0;
        if (local_38 < dword_dc750) {
          iVar10 = *(int *)(&unk_dc754 + (&roster_skater_order)[local_38] * 4);
        }
        else {
          iVar10 = *(int *)(&unk_dc73c + (&roster_goalie_order)[local_38 - dword_dc750] * 4);
        }
        puVar6 = (undefined4 *)(dword_dd11c + iVar10 * 0x34);
        puVar13 = (undefined4 *)&card_player_record;
        for (iVar8 = 0xd; iVar8 != 0; iVar8 = iVar8 + -1) {
          *puVar13 = *puVar6;
          puVar6 = puVar6 + (uint)bVar14 * -2 + 1;
          puVar13 = puVar13 + (uint)bVar14 * -2 + 1;
        }
        if (local_14 < dword_dc750) {
          iVar10 = local_14 * 0xd + 0x43;
        }
        else {
          iVar10 = (local_14 - dword_dc750) * 0xd + 0x1a8;
        }
        fillrect2(0,iVar10,0x280,0xd,0x80);
        iVar10 = (*(code *)(&local_80)[local_3c][local_60[8] * 8 + 5])();
        local_74 = 0;
        local_78 = 0;
        local_7c = 0;
        local_60[3] = 0;
        local_60[2] = 0;
        local_60[1] = 0;
        local_60[0] = 0;
        local_60[7] = 0;
        local_60[6] = 0;
        local_60[5] = 0;
        if (iVar10 != 1) {
          if (byte_dc836 == 'G') {
            for (iVar8 = 0; iVar10 = local_14, iVar8 < dword_dc6b8; iVar8 = iVar8 + 1) {
              iVar10 = *(int *)(&unk_dc73c + (&roster_goalie_order)[iVar8] * 4);
              iVar4 = str_prefix_differs(&unk_dc837,dword_dd11c + iVar10 * 0x34 + 3);
              if ((iVar4 == 0) &&
                 (iVar10 = str_prefix_differs(&unk_dc847,dword_dd11c + iVar10 * 0x34 + 0x13),
                 iVar10 == 0)) {
                iVar10 = dword_dc750 + iVar8;
                break;
              }
            }
          }
          else {
            iVar10 = local_14;
            if (byte_dc836 != '\0') {
              for (iVar8 = 0; iVar10 = local_14, iVar8 < dword_dc750; iVar8 = iVar8 + 1) {
                iVar10 = *(int *)(&unk_dc754 + (&roster_skater_order)[iVar8] * 4);
                iVar4 = str_prefix_differs(&unk_dc837,dword_dd11c + iVar10 * 0x34 + 3);
                if ((iVar4 == 0) &&
                   (iVar4 = str_prefix_differs(&unk_dc847,dword_dd11c + iVar10 * 0x34 + 0x13),
                   iVar10 = iVar8, iVar4 == 0)) break;
              }
            }
          }
          local_14 = iVar10;
          if (local_14 < dword_dc750) {
            iVar10 = local_14 * 0xd + 0x43;
          }
          else {
            iVar10 = (local_14 - dword_dc750) * 0xd + 0x1a8;
          }
          fillrect2(0,iVar10,0x280,0xd,0x80);
          ppppuVar2 = local_1c;
          setmousepos(local_1c,local_18);
          local_30 = ppppuVar2;
          local_34 = local_18;
          event_queue_reset();
          goto LAB_0001fa6c;
        }
        goto LAB_0001defd;
      }
      drawshape(local_20,local_1c,local_18);
      menu_item_draw_normal
                ((&local_80)[local_3c] + local_60[local_3c + 4] * 8,local_a0[local_3c * 2],
                 local_a0[local_3c * 2 + 1],unaff_EBX,unaff_ECX,param_5);
      iVar10 = local_3c;
      local_60[local_3c + 4] = local_60[8];
      uVar7 = unaff_ECX;
LAB_0001f482:
      iVar8 = local_a0[iVar10 * 2 + 1];
      iVar4 = local_a0[iVar10 * 2];
      piVar5 = (&local_80)[iVar10] + local_60[iVar10 + 4] * 8;
      unaff_ECX = uVar7;
    }
    menu_item_draw_selected(piVar5,iVar4,iVar8,unaff_EBX,uVar7,param_5);
  }
LAB_0001fa6c:
  grabshape(local_20,local_30,local_34);
  pppppuVar9 = (undefined4 *****)local_30;
  goto LAB_0001f0c3;
code_r0x0001f065:
  if ((local_30 != local_1c) || (local_34 != local_18)) {
    drawshape(local_20,local_1c,local_18);
    grabshape(puVar6,local_30,local_34);
    pppppuVar9 = (undefined4 *****)local_34;
LAB_0001f0c3:
    drawshape_remap(pointer_shapes,local_30,local_34);
    uVar15 = CONCAT44(extraout_EDX,local_34);
    local_1c = local_30;
    local_18 = local_34;
  }
  goto LAB_0001f03d;
}


// ================================================================================================
// hub_build_remap @ 0x1faa7 [__watcall]
// ================================================================================================

void __watcall
hub_build_remap(int param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  int iVar1;
  
  __CHK(0x14);
  if (param_1 == 0) {
    _memset_fill(&unk_dcfd8,0,unaff_EBX,0x15,unaff_EDX,unaff_ECX,unaff_EBX);
    iVar1 = 0x15;
    do {
      (&unk_dcfd8)[iVar1] = (char)iVar1 + -0x15;
      iVar1 = iVar1 + 1;
    } while (iVar1 < 0x40);
    iVar1 = 0x40;
    do {
      (&unk_dcfd8)[iVar1] = (char)iVar1;
      iVar1 = iVar1 + 1;
    } while (iVar1 < 0x100);
  }
  else {
    iVar1 = 0;
    do {
      (&unk_dcfd8)[iVar1] = (char)iVar1;
      (&unk_dd058)[iVar1] = (char)iVar1;
      iVar1 = iVar1 + 1;
    } while (iVar1 < 0x80);
  }
  setremaptable(&unk_dcfd8);
  return;
}


// ================================================================================================
// hub_printf_at @ 0x1fb1c [__watcall]
// ================================================================================================

void __watcall
hub_printf_at(undefined4 param_1,undefined4 param_2,char *unaff_EBX,undefined4 unaff_ECX)

{
  undefined4 extraout_EDX;
  
  __CHK(0x14);
  sprintf((char *)&unk_dd0d8,unaff_EBX,unaff_ECX);
  printstr_at(&unk_dd0d8,param_1,extraout_EDX);
  return;
}


// ================================================================================================
// hub_printf_at2 @ 0x1fb49 [__watcall]
// ================================================================================================

void __watcall
hub_printf_at2(undefined4 param_1,undefined4 param_2,char *unaff_EBX,undefined4 unaff_ECX,
              undefined4 param_5)

{
  undefined4 extraout_EDX;
  
  __CHK(0x1c);
  sprintf((char *)&unk_dd0d8,unaff_EBX,unaff_ECX,param_5);
  printstr_at(&unk_dd0d8,param_1,extraout_EDX);
  return;
}


// ================================================================================================
// cmp_leaders_points @ 0x1fb7f [__watcall]
// ================================================================================================

int __watcall cmp_leaders_points(int *param_1,int *unaff_EDX)

{
  ushort uVar1;
  ushort uVar2;
  ushort uVar3;
  ushort *puVar4;
  uint uVar6;
  ushort *puVar7;
  uint uVar5;
  
  __CHK(0x14);
  if (stats_playoffs == 0) {
    puVar4 = (ushort *)(dword_dd110 + *param_1 * 0x2f);
    puVar7 = (ushort *)(dword_dd110 + *unaff_EDX * 0x2f);
  }
  else {
    puVar4 = (ushort *)(*param_1 * 0x2f + dword_dd110 + 0x12);
    puVar7 = (ushort *)(dword_dd110 + *unaff_EDX * 0x2f + 0x12);
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
        goto LAB_0001fc86;
      }
    }
  }
  else {
    uVar2 = *puVar7;
    uVar3 = uVar1;
  }
  uVar6 = (uint)uVar2;
  uVar5 = (uint)uVar3;
LAB_0001fc86:
  return uVar6 - uVar5;
}


// ================================================================================================
// cmp_leaders_gaa @ 0x1fc8f [__watcall]
// ================================================================================================

int __watcall cmp_leaders_gaa(int *param_1,int *unaff_EDX)

{
  ushort uVar1;
  ushort *puVar2;
  uint uVar3;
  ushort *puVar4;
  ushort uVar5;
  
  __CHK(0x14);
  if (stats_playoffs == 0) {
    puVar2 = (ushort *)(*param_1 * 0x36 + dword_dd114);
    puVar4 = (ushort *)(dword_dd114 + *unaff_EDX * 0x36);
  }
  else {
    puVar2 = (ushort *)(*param_1 * 0x36 + dword_dd114 + 0x16);
    puVar4 = (ushort *)(dword_dd114 + *unaff_EDX * 0x36 + 0x16);
  }
  uVar5 = puVar2[6];
  if ((uVar5 == 0) == (puVar4[6] == 0)) {
    uVar1 = puVar2[8];
    if (puVar4[8] != uVar1) {
      uVar5 = puVar4[8];
LAB_0001fd5d:
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
            goto LAB_0001fd5d;
          }
          uVar3 = (uint)puVar4[10];
          uVar5 = puVar2[10];
        }
        goto LAB_0001fdf0;
      }
    }
  }
  else {
    uVar1 = puVar4[6];
  }
  uVar3 = (uint)uVar1;
LAB_0001fdf0:
  return uVar3 - uVar5;
}


// ================================================================================================
// load_sfh_shapes @ 0x1fdfe [__watcall]
// ================================================================================================

undefined4 __watcall load_sfh_shapes(undefined4 param_1,void *unaff_EDX)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int unaff_EDI;
  undefined auStack_40 [4];
  short sStack_3c;
  short sStack_3a;
  undefined local_2c [4];
  undefined4 local_28;
  uint local_24;
  int local_20;
  undefined4 local_1c;
  int iStack_18;
  
  __CHK(0x54);
  local_28 = 0xffffffff;
  iVar3 = 0;
  local_1c = 0;
  iStack_18 = file_open_read(param_1,&local_28);
  if (iStack_18 == 0) {
    iStack_18 = file_read(local_28,&local_24,4,2);
    local_24 = local_24 & 0xffff;
  }
  if (iStack_18 == 0) {
    iVar4 = local_24 << 3;
    iVar3 = allocmem(&aSfh,iVar4,0x20);
    iStack_18 = file_read(local_28,iVar3,6,iVar4);
  }
  if (iStack_18 == 0) {
    local_20 = iStack_18;
    iVar4 = 0;
    while ((iVar4 < (int)local_24 && (local_20 == 0))) {
      memcpy(local_2c,(void *)(iVar4 * 4 + iVar3),4);
      iVar1 = memcmp(local_2c,unaff_EDX,4);
      if (iVar1 == 0) {
        local_20 = -1;
        unaff_EDI = local_24 * 8 + 6 + *(int *)(iVar4 * 4 + local_24 * 4 + iVar3);
        iStack_18 = file_read(local_28,auStack_40,unaff_EDI,0x11);
      }
      iVar4 = iVar4 + 1;
    }
  }
  if (iVar3 != 0) {
    freemem(iVar3);
  }
  if ((iStack_18 == 0) && (local_20 != 0)) {
    iVar3 = (int)sStack_3a * (int)sStack_3c + 0x11;
    uVar2 = allocmem(aShape,iVar3,0x20);
    local_1c = uVar2;
    iVar3 = file_read(local_28,uVar2,unaff_EDI,iVar3);
    if (iVar3 < 0) {
      freemem(uVar2);
      local_1c = 0;
    }
  }
  file_close(&local_28);
  return local_1c;
}


// ================================================================================================
// stats_source_title @ 0x1ff86 [__watcall]
// ================================================================================================

void __watcall stats_source_title(char *param_1,char *unaff_EDX,int unaff_EBX,char *unaff_ECX)

{
  size_t sVar1;
  
  __CHK(0x18);
  if (byte_c671c == '\x01') {
    unaff_ECX = s__93____94_Season_000c671d;
LAB_0001ffa7:
    unaff_ECX = unaff_ECX + 1;
    unaff_EBX = 0;
  }
  else {
    if (byte_c672f == '\x01') {
      unaff_ECX = s__93____94_Play_Offs_000c6730 + 1;
    }
    else {
      if (byte_c6745 == '\x01') {
        unaff_ECX = s__WWWWWWWW__Season_000c6746;
        goto LAB_0001ffa7;
      }
      if (byte_c6759 == '\x01') {
        unaff_ECX = s__WWWWWWWW__Season_Play_Offs_000c675a + 1;
      }
      else {
        if (byte_c6777 != '\x01') goto LAB_0001ffee;
        unaff_ECX = s__WWWWWWWW__Play_Offs_000c6778 + 1;
      }
    }
    unaff_EBX = 1;
  }
LAB_0001ffee:
  sVar1 = strlen(unaff_ECX);
  strncpy(param_1,unaff_ECX,sVar1 - unaff_EBX);
  param_1[sVar1 - unaff_EBX] = '\0';
  strcat(param_1,unaff_EDX);
  return;
}


// ================================================================================================
// exh_hub_sports_central @ 0x20016 [__watcall]
// ================================================================================================

undefined8 __watcall exh_hub_sports_central(undefined4 param_1,undefined4 unaff_EDX)

{
  undefined *puVar1;
  undefined auStack_320 [768];
  undefined auStack_20 [16];
  
  __CHK(0x330);
  stats_hub_active = 1;
  stats_current_screen = team_stats_screen;
  stats_current_arg = param_1;
  getpalette(0,0x100,auStack_320);
  fade_palette(1,auStack_320,0x10);
  setdefaultscreen();
  hub_build_remap(1);
  team_stats_screen(param_1);
  draw_menu_items(&unk_cf78f,4,0x40,0x41,0x42);
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
  run_menu(&unk_cf78f,4,0x40,0x41,0x42);
  getpalette(0,0x100,auStack_320);
  fade_palette(1,auStack_320,0x10);
  stats_hub_active = 0;
  stats_current_screen = (code *)0x0;
  return CONCAT44(unaff_EDX,2);
}


