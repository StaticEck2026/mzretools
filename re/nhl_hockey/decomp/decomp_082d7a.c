// Decompiled by Ghidra from hockey.elf (via ledisasm ELF export)
// This is machine generated pseudo-C meant as a reference for porting, it does not compile as is.
#include "prototypes.h"

// ================================================================================================
// load_sound_config @ 0x82d7a [__watcall]
// ================================================================================================

undefined8 __watcall load_sound_config(uint param_1,undefined4 unaff_EDX)

{
  undefined4 uVar1;
  FILE *__stream;
  int iVar2;
  undefined *puVar3;
  undefined4 extraout_EDX;
  int iVar4;
  bool bVar5;
  char acStack_5c [16];
  char acStack_4c [16];
  char acStack_3c [16];
  undefined local_2c [4];
  undefined local_28 [4];
  undefined local_24 [4];
  int local_20;
  uint uStack_1c;
  
  __CHK(0x74);
  iVar4 = 0;
  local_20 = 1;
  if (dword_d2423 != 0) {
    if ((dword_c541f == 2) || (dword_c541f == 0x20)) {
      speech_shutdown();
      freemem(dword_ed7a8);
      dword_ed7a8 = 0;
    }
    else if (dword_c541f == 4) {
      kms_unload(dword_ed7a4);
    }
    sound_shutdown();
  }
  dword_ccc94 = 0x20;
  dword_d2423 = 0;
  do {
    if (param_1 < 4) {
      if (param_1 == 0) {
LAB_00082f66:
        strcpy(acStack_3c,aPCBEEP_d2399);
        strcpy(acStack_4c,(char *)&aPC);
        dword_d2427 = 0;
        dword_d242b = -1;
        byte_d2439 = '\0';
      }
      else if (param_1 < 2) {
        strcpy(acStack_3c,aPCBEEP);
        strcpy(acStack_4c,(char *)&aPC);
        dword_d2427 = 1;
        dword_d242b = -1;
        byte_d2439 = '\0';
      }
      else {
        if (param_1 != 2) goto LAB_00082f66;
        strcpy(acStack_3c,aSBDAC);
        strcpy(acStack_4c,(char *)&aPC);
        dword_d242b = 3;
        byte_d242f = '\x01';
        byte_d2439 = '\x01';
        dword_d2427 = 2;
      }
    }
    else if (param_1 < 5) {
      strcpy(acStack_3c,aADLIB);
      strcpy(acStack_4c,(char *)&aPC);
      dword_d2427 = 2;
      dword_d242b = -1;
      byte_d2439 = '\0';
    }
    else {
      if (param_1 < 8) goto LAB_00082f66;
      if (param_1 < 9) {
        strcpy(acStack_3c,(char *)&aMT32_d238b);
        strcpy(acStack_4c,(char *)&aPC);
        dword_d2427 = 4;
        dword_d242b = -1;
        byte_d2439 = '\0';
      }
      else {
        if (param_1 != 0x20) goto LAB_00082f66;
        strcpy(acStack_3c,aSBDAC_d2390);
        strcpy(acStack_4c,(char *)&aPC);
        dword_d2427 = 5;
        dword_d242b = 6;
        byte_d242f = '\x01';
        byte_d2439 = '\x01';
      }
    }
    sound_timer_install();
    if (((-1 < dword_d2427) && (iVar4 = drv_open(dword_d2427), iVar4 != -1)) &&
       ((dword_d242b < 0 || (local_20 = drv_open(dword_d242b), local_20 != -1)))) {
      dword_d2423 = -1;
    }
    if (dword_d2423 == 0) {
      if ((param_1 == 0x10) || (param_1 == 1)) {
        dword_d2423 = -1;
      }
      else {
        if (param_1 < 4) {
          if (param_1 == 2) {
            dword_d24a0 = aSoundBlaster_d2479;
          }
        }
        else if (param_1 < 5) {
          dword_d24a0 = aAdlib;
        }
        else if (7 < param_1) {
          if (param_1 < 9) {
            dword_d24a0 = (char *)&aMT32_d248c;
          }
          else if (param_1 == 0x20) {
            dword_d24a0 = aULTRASOUND;
          }
        }
        uStack_1c = 0;
        getmouse(local_24,local_28,local_2c);
        message_dialog(0xffffffff,0xffffffff,&off_d249c,3,0,0,local_28,local_2c,0);
        do {
          iVar2 = event_queue_pop();
          if (iVar2 != 0) {
            uStack_1c = (*ui_poll_callback)();
          }
        } while ((uStack_1c & 2) == 0);
        restore_dialog_background();
        param_1 = 0x10;
      }
      sound_shutdown();
      settimeout(100);
      waittimeout();
    }
    else {
      loadpatches(acStack_3c,acStack_4c);
      if (param_1 == 4) {
        puVar3 = install_path;
        if (byte_ed95b != '\x01') {
          puVar3 = (undefined *)0x0;
        }
        make_path(acStack_5c,puVar3,aSlapshot,0);
        dword_ed7a4 = music_load_kms(acStack_5c);
      }
      if ((param_1 == 8) && (dword_d2350 == 0)) {
        message_dialog(0xffffffff,0xffffffff,&off_d24d1,2,0,0,local_28,local_2c,0);
        puVar3 = install_path;
        if (byte_ed8c3 != '\x01') {
          puVar3 = (undefined *)0x0;
        }
        make_path(acStack_5c,puVar3,aMT32HOCK,0);
        uVar1 = music_load_kms(acStack_5c);
        dword_d2350 = -1;
        dword_c541f = 8;
        play_sample_by_ptr(uVar1,uVar1);
        sfx_set_volume();
        kms_unload(extraout_EDX);
        restore_dialog_background();
      }
      bVar5 = byte_d2439 == '\0';
      byte_d2439 = (char)local_20;
      if (bVar5) {
        byte_d2439 = (char)iVar4;
      }
      byte_d242f = (char)local_20;
      dword_c541f = param_1;
      dword_ed360 = param_1;
      make_path(acStack_5c,0,&aNHL_c36a8,&aCFG_c8145);
      __stream = fopen(acStack_5c,(char *)&aR_c36ac);
      if (__stream == (FILE *)0x0) {
        fatalerror(aCannotOpenNhlCfg_c36af);
      }
      for (iVar2 = 0; param_1 != (&unk_d243a)[iVar2]; iVar2 = iVar2 + 1) {
      }
      fprintf(__stream,a04x,iVar2);
      fclose(__stream);
      if ((dword_c541f == 2) || (dword_c541f == 0x20)) {
        sound_enabled = 1;
        dword_d2431 = dword_d242b;
      }
      else {
        sound_enabled = 0;
      }
    }
    if (dword_d2423 != 0) {
      if ((dword_c541f == 2) || (dword_c541f == 0x20)) {
        dword_ed7a8 = allocmem(aEmmcopybuf,0x400,0x20);
        speech_init(byte_d242f,dword_c4cfc,dword_ed7a8);
      }
      dword_ccc94 = 0;
      return CONCAT44(unaff_EDX,1);
    }
  } while( true );
}


// ================================================================================================
// speech_timer @ 0x832bc [__watcall]
// ================================================================================================

void __watcall speech_timer(void)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  __CHK(0x20);
  if (speech_enabled != 0) {
    if (*(int *)(dword_ed7ac + 0x5c) != 0) {
      *(int *)(dword_ed7ac + 0x5c) = *(int *)(dword_ed7ac + 0x5c) + -1;
    }
    if (*(int *)(dword_ed7ac + 0x60) != 0) {
      if (*(int *)(dword_ed7ac + 0x50) == 0) {
        iVar1 = *(int *)(dword_ed7ac + 0x58);
        *(int *)(dword_ed7ac + 0x58) = iVar1 + 1;
        if (iVar1 < *(int *)(dword_ed7ac + 0x54)) {
          iVar1 = *(int *)(dword_ed7ac + iVar1 * 4);
          if (iVar1 == -1) {
            *(undefined4 *)(dword_ed7ac + 0x60) = 0;
          }
          else {
            iVar3 = iVar1 * 0x26 + dword_ed7b0;
            uVar2 = *(undefined4 *)(iVar3 + 0xe);
            iVar1 = *(int *)(iVar3 + 0x16);
            *(undefined4 *)(dword_ed7ac + 0x50) = *(undefined4 *)(iVar3 + 0x1e);
            dword_d27b2 = dword_d27b2 + 1 & 1;
            if (*(char *)(iVar3 + 0xd) == 'G') {
              playsample_raw(uVar2,dword_d2431,dword_d27b2,iVar1,0x2b11,0x7f);
            }
            else {
              playsample_raw_loop(uVar2,dword_d2431,dword_d27b2,iVar1 * 2,0x2b11,0x7f);
            }
          }
        }
        else {
          *(undefined4 *)(dword_ed7ac + 0x60) = 0;
          *(undefined4 *)(dword_ed7ac + 0x5c) = *(undefined4 *)(dword_ed7b0 + 0x3b70);
        }
      }
      else {
        *(int *)(dword_ed7ac + 0x50) = *(int *)(dword_ed7ac + 0x50) + -1;
      }
    }
  }
  return;
}


// ================================================================================================
// speech_clip_clear @ 0x833c5 [__watcall]
// ================================================================================================

void __watcall speech_clip_clear(undefined *param_1)

{
  __CHK(4);
  *param_1 = 0;
  param_1[0xd] = 0;
  *(undefined4 *)(param_1 + 0xe) = 0;
  *(undefined4 *)(param_1 + 0x12) = 0;
  *(undefined4 *)(param_1 + 0x16) = 0;
  *(undefined4 *)(param_1 + 0x1e) = 0;
  *(undefined4 *)(param_1 + 0x22) = 0;
  return;
}


// ================================================================================================
// speech_reset @ 0x833fa [__watcall]
// ================================================================================================

void __watcall
speech_reset(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  __CHK(0xc);
  *(undefined4 *)(dword_ed7ac + 0x60) = 0;
  _memset_dwords(dword_ed7ac,0xffffffff,unaff_EBX,0x14,unaff_EDX,unaff_ECX);
  *(undefined4 *)(dword_ed7ac + 0x54) = 0;
  *(undefined4 *)(dword_ed7ac + 0x58) = 0;
  *(undefined4 *)(dword_ed7ac + 0x50) = 0;
  *(undefined4 *)(dword_ed7ac + 0x5c) = 0;
  return;
}


// ================================================================================================
// speech_clips_init @ 0x83459 [__watcall]
// ================================================================================================

void __watcall speech_clips_init(int param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  undefined4 uVar1;
  int iVar2;
  int extraout_EDX;
  
  __CHK(0x1c);
  iVar2 = 0;
  do {
    speech_clip_clear(iVar2 * 0x26 + dword_ed7b0);
    iVar2 = extraout_EDX + 1;
  } while (iVar2 < 400);
  *(int *)(dword_ed7b0 + 0x3b68) = param_1 + -5000;
  uVar1 = reservemem_fatal(aSpeechbuf,param_1,dword_ccc94,unaff_EDX,unaff_ECX,unaff_EBX);
  *(undefined4 *)(dword_ed7b0 + 0x3b60) = uVar1;
  uVar1 = memblock_ptr(*(undefined4 *)(dword_ed7b0 + 0x3b60));
  *(undefined4 *)(dword_ed7b0 + 0x3b64) = uVar1;
  *(undefined4 *)(dword_ed7b0 + 0x3b6c) = 0;
  *(undefined4 *)(dword_ed7b0 + 0x3b74) = 0;
  *(undefined4 *)(dword_ed7b0 + 0x3b70) = 0;
  *(undefined4 *)(dword_ed7b0 + 0x3b78) = 0;
  return;
}


// ================================================================================================
// speech_begin @ 0x83520 [__watcall]
// ================================================================================================

void __watcall speech_begin(void)

{
  int iVar1;
  
  __CHK(0xc);
  iVar1 = 0;
  do {
    *(undefined *)(iVar1 * 0xd + dword_ed7b4) = 0;
    iVar1 = iVar1 + 1;
  } while (iVar1 < 0x14);
  *(undefined4 *)(dword_ed7b4 + 0x10c) = 0;
  *(undefined4 *)(dword_ed7b4 + 0x108) = 0;
  *(undefined4 *)(dword_ed7b4 + 0x104) = 0;
  return;
}


// ================================================================================================
// speech_init @ 0x8357a [__watcall]
// ================================================================================================

void __watcall
speech_init(undefined param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  int iVar1;
  
  __CHK(0x1c);
  iVar1 = speech_is_enabled();
  if (iVar1 == 0) {
    dword_d27b2 = 0;
    byte_d27b6 = param_1;
    dword_d27b7 = unaff_ECX;
    dword_ed7b8 = unaff_EBX;
    dword_ed7ac = allocmem(aSentence,100,dword_ccc94);
    speech_reset();
    dword_ed7b4 = allocmem(aSampleMemMan,0x110,dword_ccc94);
    speech_begin();
    dword_ed7b0 = allocmem(aSpeechBank,0x3b93,dword_ccc94);
    speech_clips_init(unaff_EDX);
    addtimer(speech_timer);
    speech_enabled = 1;
  }
  return;
}


// ================================================================================================
// speech_shutdown @ 0x8363c [__watcall]
// ================================================================================================

void __watcall speech_shutdown(void)

{
  __CHK(0x20);
  if (speech_enabled != 0) {
    removetimer(speech_timer);
    if (*(int *)(dword_ed7b0 + 0x3b78) != 0) {
      close(*(int *)(dword_ed7b0 + 0x3b7c));
    }
    freemem(dword_ed7ac);
    releasememblock(*(undefined4 *)(dword_ed7b0 + 0x3b60));
    freemem(dword_ed7b0);
    freemem(dword_ed7b4);
    speech_enabled = 0;
  }
  return;
}


// ================================================================================================
// speech_is_enabled @ 0x836ca [__watcall]
// ================================================================================================

bool __watcall speech_is_enabled(void)

{
  __CHK(4);
  return speech_enabled != 0;
}


// ================================================================================================
// speech_clip_pending @ 0x836e4 [__watcall]
// ================================================================================================

undefined4 __watcall speech_clip_pending(void)

{
  __CHK(4);
  if ((speech_enabled != 0) &&
     ((*(int *)(dword_ed7ac + 0x60) != 0 || (*(int *)(dword_ed7ac + 0x5c) != 0)))) {
    return 1;
  }
  return 0;
}


// ================================================================================================
// speech_available @ 0x83711 [__watcall]
// ================================================================================================

undefined4 __watcall speech_available(void)

{
  __CHK(4);
  if (((speech_enabled != 0) && (*(int *)(dword_ed7ac + 0x60) == 0)) &&
     (*(int *)(dword_ed7ac + 0x5c) == 0)) {
    return 1;
  }
  return 0;
}


// ================================================================================================
// speech_stop_and_flush @ 0x8373e [__watcall]
// ================================================================================================

void __watcall speech_stop_and_flush(void)

{
  __CHK(4);
  speech_stop_channels();
  __CHK(0x10);
  if (speech_enabled != 0) {
    *(undefined4 *)(dword_ed7ac + 0x60) = 0;
    *(int *)(dword_ed7ac + 0x5c) = *(int *)(dword_ed7ac + 0x50) + *(int *)(dword_ed7b0 + 0x3b70);
  }
  return;
}


// ================================================================================================
// speech_flush @ 0x8374d [__watcall]
// ================================================================================================

void __watcall speech_flush(void)

{
  __CHK(0x10);
  if (speech_enabled != 0) {
    *(undefined4 *)(dword_ed7ac + 0x60) = 0;
    *(int *)(dword_ed7ac + 0x5c) = *(int *)(dword_ed7ac + 0x50) + *(int *)(dword_ed7b0 + 0x3b70);
  }
  return;
}


// ================================================================================================
// speech_stop_channel3 @ 0x8378c [__watcall]
// ================================================================================================

void __watcall
speech_stop_channel3(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  __CHK(8);
  sound_channel_stop(dword_d2431,3,unaff_EBX,unaff_ECX,unaff_EDX);
  return;
}


// ================================================================================================
// speech_stop_channels @ 0x837a8 [__watcall]
// ================================================================================================

void __watcall
speech_stop_channels(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  __CHK(8);
  if (speech_enabled != 0) {
    sound_channel_stop(dword_d2431,0,unaff_EBX,unaff_ECX,unaff_EDX);
    sound_channel_stop(dword_d2431,1);
  }
  return;
}


// ================================================================================================
// bswap16 @ 0x837d9 [__watcall]
// ================================================================================================

undefined8 __watcall bswap16(uint param_1,undefined4 unaff_EDX)

{
  __CHK(8);
  return CONCAT44(unaff_EDX,param_1 >> 8 & 0xff | (param_1 & 0xff) << 8);
}


// ================================================================================================
// read_be32 @ 0x837fb [__watcall]
// ================================================================================================

undefined8 __watcall read_be32(undefined4 param_1,undefined4 unaff_EDX)

{
  undefined2 in_DS;
  undefined auStack_18 [4];
  undefined4 uStack_14;
  
  __CHK(0x20);
  uStack_14 = uStack_14 & 0xffffff;
  read_bytes(param_1,1,(int)&uStack_14 + 2,in_DS,auStack_18);
  read_bytes(param_1,1,(int)&uStack_14 + 1,in_DS,auStack_18);
  read_bytes(param_1,1,&uStack_14,in_DS,auStack_18);
  return CONCAT44(unaff_EDX,uStack_14);
}


// ================================================================================================
// read_clip_name @ 0x8385f [__watcall]
// ================================================================================================

void __watcall read_clip_name(char *param_1,undefined4 unaff_EDX)

{
  char cVar1;
  undefined2 in_DS;
  undefined auStack_14 [4];
  
  __CHK(0x1c);
  do {
    read_bytes(unaff_EDX,1,param_1,in_DS,auStack_14);
    cVar1 = *param_1;
    param_1 = param_1 + 1;
  } while (cVar1 != '\0');
  return;
}


// ================================================================================================
// speech_load_bank @ 0x83897 [__watcall]
// ================================================================================================

void __watcall
speech_load_bank(char *param_1,undefined4 unaff_EDX,undefined4 param_3,undefined4 unaff_ECX)

{
  int iVar1;
  undefined2 uVar2;
  ushort uVar3;
  int iVar4;
  undefined4 uVar5;
  undefined2 uVar7;
  undefined4 uVar6;
  int iVar8;
  undefined2 in_DS;
  longdouble lVar9;
  int local_38;
  undefined local_30 [4];
  int local_2c;
  undefined2 local_28;
  undefined2 uStack_26;
  short asStack_24 [2];
  ushort auStack_20 [3];
  undefined4 uStack_1a;
  
  __CHK(0x40);
  if (speech_enabled != 0) {
    if (*(int *)(dword_ed7b0 + 0x3b78) != 0) {
      iVar4 = stricmp_alpha(param_1,dword_ed7b0 + 0x3b80);
      if (iVar4 != 0) {
        return;
      }
      close(*(int *)(dword_ed7b0 + 0x3b7c));
    }
    open(param_1,0,&local_28);
    strncpy((char *)(dword_ed7b0 + 0x3b80),param_1,0xd);
    *(uint *)(dword_ed7b0 + 0x3b7c) = CONCAT22(uStack_26,local_28);
    *(undefined4 *)(dword_ed7b0 + 0x3b70) = unaff_EDX;
    *(undefined4 *)(dword_ed7b0 + 0x3b78) = 1;
    *(undefined4 *)(dword_ed7b0 + 0x3b6c) = 0;
    *(undefined4 *)(dword_ed7b0 + 0x3b74) = 0;
    uVar7 = (undefined2)((uint)unaff_ECX >> 0x10);
    read_bytes(CONCAT22(uStack_26,local_28),2,(int)&uStack_1a + 2,CONCAT22(uVar7,in_DS),local_30);
    uVar2 = bswap16(uStack_1a >> 0x10);
    *(undefined2 *)(dword_ed7b0 + 0x3b8d) = uVar2;
    read_bytes(CONCAT22(uStack_26,local_28),2,asStack_24,CONCAT22(uVar7,in_DS),local_30);
    uVar2 = bswap16((int)asStack_24[0]);
    *(undefined2 *)(dword_ed7b0 + 0x3b8f) = uVar2;
    uVar6 = CONCAT22(uVar7,in_DS);
    read_bytes(CONCAT22(uStack_26,local_28),2,auStack_20 + 2,uVar6,local_30);
    uVar2 = bswap16((int)(short)auStack_20[2]);
    *(undefined2 *)(dword_ed7b0 + 0x3b91) = uVar2;
    for (iVar4 = 0; iVar4 < *(int *)(dword_ed7b0 + 0x3b8f) >> 0x10; iVar4 = iVar4 + 1) {
      iVar8 = iVar4 * 0x26;
      *(undefined4 *)(iVar8 + 0xe + dword_ed7b0) = 0;
      uVar5 = read_be32(CONCAT22(uStack_26,local_28));
      *(undefined4 *)(iVar8 + 0x12 + dword_ed7b0) = uVar5;
      uVar5 = read_be32(CONCAT22(uStack_26,local_28));
      *(undefined4 *)(dword_ed7b0 + 0x1a + iVar8) = uVar5;
      read_clip_name(dword_ed7b0 + iVar8,CONCAT22(uStack_26,local_28));
      *(undefined4 *)(iVar8 + 0x22 + dword_ed7b0) = 0;
    }
    for (iVar4 = 0; iVar8 = *(int *)(dword_ed7b0 + 0x3b8f) >> 0x10, iVar4 < iVar8; iVar4 = iVar4 + 1
        ) {
      iVar1 = iVar4 * 0x26;
      iVar8 = *(int *)(iVar1 + 0x12 + dword_ed7b0);
      lseek(CONCAT22(uStack_26,local_28),iVar8,0);
      uVar2 = (undefined2)((uint)uVar6 >> 0x10);
      read_bytes(CONCAT22(uStack_26,local_28),2,auStack_20,CONCAT22(uVar2,in_DS),local_30);
      uVar3 = auStack_20[0] & 0xff;
      auStack_20[0] = auStack_20[0] >> 8;
      auStack_20[1] = 0;
      if (uVar3 == 0x47) {
        lseek(CONCAT22(uStack_26,local_28),iVar8 + 6,0);
        uVar6 = CONCAT22(uVar2,in_DS);
        read_bytes(CONCAT22(uStack_26,local_28),2,&local_2c,uVar6,local_30);
        local_2c = bswap16(local_2c);
        local_2c = local_2c + -5;
        *(int *)(dword_ed7b0 + 0x16 + iVar1) = local_2c;
        lVar9 = (longdouble)fround();
        local_38 = (int)(longlong)ROUND(lVar9);
        *(int *)(dword_ed7b0 + 0x1e + iVar1) = local_38;
        *(undefined *)(iVar1 + 0xd + dword_ed7b0) = 0x47;
      }
      else {
        local_2c = *(int *)(dword_ed7b0 + 0x1a + iVar1);
        *(int *)(dword_ed7b0 + 0x16 + iVar1) = local_2c;
        uVar6 = 0;
        lVar9 = (longdouble)fround();
        local_38 = (int)(longlong)ROUND(lVar9);
        *(int *)(dword_ed7b0 + 0x1e + iVar1) = local_38 + -0x1a;
        *(undefined *)(iVar1 + 0xd + dword_ed7b0) = 0xff;
      }
    }
    for (; iVar8 < 400; iVar8 = iVar8 + 1) {
      speech_clip_clear(iVar8 * 0x26 + dword_ed7b0);
    }
  }
  return;
}


// ================================================================================================
// speech_clip_size @ 0x83bc7 [__watcall]
// ================================================================================================

longlong __watcall speech_clip_size(int param_1,uint unaff_EDX)

{
  __CHK(8);
  if (param_1 == -1) {
    return (ulonglong)unaff_EDX << 0x20;
  }
  return CONCAT44(unaff_EDX,*(undefined4 *)(dword_ed7b0 + 0x16 + param_1 * 0x26));
}


// ================================================================================================
// speech_delta_decode @ 0x83bf3 [__watcall]
// ================================================================================================

void __watcall speech_delta_decode(int param_1,undefined4 unaff_EDX)

{
  int iVar1;
  int iVar2;
  undefined2 extraout_var;
  int iVar3;
  char cVar4;
  undefined2 in_DS;
  undefined local_24 [4];
  int local_20;
  __off_t local_1c;
  int iStack_18;
  
  __CHK(0x38);
  iVar1 = param_1 * 0x26 + dword_ed7b0;
  iVar2 = *(int *)(iVar1 + 0x1a);
  iVar3 = *(int *)(dword_ed7b0 + 0x3b7c);
  local_1c = *(__off_t *)(iVar1 + 0x12);
  local_20 = *(int *)(iVar1 + 0x16);
  iVar1 = identity_972f0(unaff_EDX);
  iStack_18 = (local_20 - iVar2) + 5000 + iVar1;
  lseek(iVar3,local_1c,0);
  read_bytes(iVar3,iVar2,iStack_18,CONCAT22(extraout_var,in_DS),local_24);
  iVar2 = unpack_fatal(iStack_18,iVar1,iVar2);
  cVar4 = '\0';
  for (iVar3 = 0; iVar3 < iVar2 + -5; iVar3 = iVar3 + 1) {
    *(char *)(iVar3 + iVar1) = *(char *)(iVar3 + 5 + iVar1) + cVar4;
    cVar4 = cVar4 + *(char *)(iVar3 + 5 + iVar1);
  }
  return;
}


// ================================================================================================
// speech_clip_decode @ 0x83cae [__watcall]
// ================================================================================================

void __watcall speech_clip_decode(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  longdouble extraout_ST0;
  undefined8 uVar4;
  undefined4 uStackY_18;
  
  __CHK(0x1c);
  if (param_1 == 0) {
    iVar2 = *(int *)(dword_ed7b0 + 0x3b64);
  }
  else {
    iVar2 = (param_1 + -1) * 0x26 + dword_ed7b0;
    iVar2 = *(int *)(iVar2 + 0xe) + *(int *)(iVar2 + 0x16);
  }
  iVar1 = param_1 * 0x26;
  *(int *)(iVar1 + 0xe + dword_ed7b0) = iVar2;
  uVar3 = speech_delta_decode(param_1);
  *(undefined4 *)(iVar1 + 0x16 + dword_ed7b0) = uVar3;
  iVar2 = *(int *)(dword_ed7b0 + 0x3b70);
  uVar4 = fround();
  uStackY_18 = (int)(longlong)ROUND(extraout_ST0);
  *(int *)(iVar1 + 0x1e + (int)uVar4) = uStackY_18 - iVar2;
  *(undefined4 *)(iVar1 + 0x22 + dword_ed7b0) = 1;
  *(int *)(dword_ed7b0 + 0x3b6c) = *(int *)(dword_ed7b0 + 0x3b6c) + (int)((ulonglong)uVar4 >> 0x20);
  *(int *)(dword_ed7b0 + 0x3b74) = *(int *)(dword_ed7b0 + 0x3b74) + 1;
  return;
}


// ================================================================================================
// speech_clip_read @ 0x83d78 [__watcall]
// ================================================================================================

void __watcall speech_clip_read(int param_1)

{
  int __fd;
  int iVar1;
  undefined2 in_DS;
  int local_20;
  undefined4 uStack_1c;
  
  __CHK(0x28);
  if (param_1 == 0) {
    iVar1 = *(int *)(dword_ed7b0 + 0x3b64);
  }
  else {
    iVar1 = *(int *)(dword_ed7b0 + 0xe + (param_1 + -1) * 0x26) +
            *(int *)(dword_ed7b0 + 0x16 + (param_1 + -1) * 0x26);
  }
  *(int *)(dword_ed7b0 + 0xe + param_1 * 0x26) = iVar1;
  __fd = *(int *)(dword_ed7b0 + 0x3b7c);
  uStack_1c = *(undefined4 *)(dword_ed7b0 + 0x1a + param_1 * 0x26);
  lseek(__fd,*(__off_t *)(dword_ed7b0 + 0x12 + param_1 * 0x26),0);
  read_bytes(__fd,uStack_1c,iVar1,in_DS,&local_20);
  *(undefined4 *)(dword_ed7b0 + 0x22 + param_1 * 0x26) = 1;
  *(int *)(dword_ed7b0 + 0x3b6c) = *(int *)(dword_ed7b0 + 0x3b6c) + local_20;
  *(int *)(dword_ed7b0 + 0x3b74) = *(int *)(dword_ed7b0 + 0x3b74) + 1;
  return;
}


// ================================================================================================
// stricmp_alpha @ 0x83e32 [__watcall]
// ================================================================================================

undefined4 __watcall stricmp_alpha(char *param_1,char *unaff_EDX)

{
  char cVar1;
  char cVar2;
  
  __CHK(0xc);
  while ((*param_1 != '\0' || (*unaff_EDX != '\0'))) {
    cVar1 = *param_1;
    cVar2 = *unaff_EDX;
    param_1 = param_1 + 1;
    unaff_EDX = unaff_EDX + 1;
    if (((int)cVar1 & 0xdfU) != ((int)cVar2 & 0xdfU)) {
      return 0;
    }
  }
  return 1;
}


// ================================================================================================
// speech_find_free_clip @ 0x83e6d [__watcall]
// ================================================================================================

undefined8 __watcall speech_find_free_clip(int param_1,undefined4 unaff_EDX)

{
  __CHK(0xc);
  while( true ) {
    if (399 < param_1) {
      return CONCAT44(unaff_EDX,0xffffffff);
    }
    if (*(int *)(dword_ed7b0 + 0x22 + param_1 * 0x26) == 0) break;
    param_1 = param_1 + 1;
  }
  return CONCAT44(unaff_EDX,param_1);
}


// ================================================================================================
// speech_find_loaded_clip @ 0x83eac [__watcall]
// ================================================================================================

undefined8 __watcall speech_find_loaded_clip(int param_1,undefined4 unaff_EDX)

{
  __CHK(0xc);
  while( true ) {
    if (399 < param_1) {
      return CONCAT44(unaff_EDX,0xffffffff);
    }
    if (*(int *)(dword_ed7b0 + 0x22 + param_1 * 0x26) == 1) break;
    param_1 = param_1 + 1;
  }
  return CONCAT44(unaff_EDX,param_1);
}


// ================================================================================================
// speech_find_clip @ 0x83eeb [__watcall]
// ================================================================================================

undefined8 __watcall speech_find_clip(undefined4 param_1,undefined4 unaff_EDX)

{
  int iVar1;
  int iVar2;
  
  __CHK(0x10);
  iVar2 = 0;
  do {
    iVar1 = stricmp_alpha(param_1,dword_ed7b0 + iVar2 * 0x26);
    if (iVar1 != 0) {
      return CONCAT44(unaff_EDX,iVar2);
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 < 400);
  return CONCAT44(unaff_EDX,0xffffffff);
}


// ================================================================================================
// speech_clip_loaded @ 0x83f35 [__watcall]
// ================================================================================================

undefined8 __watcall speech_clip_loaded(int param_1,undefined4 unaff_EDX)

{
  __CHK(8);
  return CONCAT44(unaff_EDX,(uint)(*(int *)(dword_ed7b0 + 0x22 + param_1 * 0x26) == 1));
}


// ================================================================================================
// speech_find_bank_entry @ 0x83f61 [__watcall]
// ================================================================================================

longlong __watcall speech_find_bank_entry(undefined4 param_1,uint unaff_EDX)

{
  int iVar1;
  int iVar2;
  
  __CHK(0x14);
  iVar2 = 0;
  while( true ) {
    if (*(int *)(dword_ed7b4 + 0x108) <= iVar2) {
      return (ulonglong)unaff_EDX << 0x20;
    }
    iVar1 = stricmp_alpha(param_1,dword_ed7b4 + iVar2 * 0xd);
    if (iVar1 != 0) break;
    iVar2 = iVar2 + 1;
  }
  return CONCAT44(unaff_EDX,1);
}


// ================================================================================================
// speech_queue_clip @ 0x83faf [__watcall]
// ================================================================================================

void __watcall speech_queue_clip(char *param_1)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  undefined8 uVar4;
  
  __CHK(0x14);
  iVar2 = speech_find_bank_entry();
  if (iVar2 != 1) {
    iVar2 = *(int *)(dword_ed7b4 + 0x108);
    *(int *)(dword_ed7b4 + 0x108) = iVar2 + 1;
    strncpy((char *)(iVar2 * 0xd + dword_ed7b4),param_1,0xd);
    iVar2 = speech_find_clip(param_1);
    if (iVar2 != -1) {
      iVar3 = speech_clip_loaded();
      if (iVar3 == 0) {
        uVar4 = speech_clip_size(iVar2,dword_ed7b4);
        piVar1 = (int *)((int)((ulonglong)uVar4 >> 0x20) + 0x104);
        *piVar1 = *piVar1 + (int)uVar4;
      }
    }
    *(int *)(dword_ed7b4 + 0x10c) = *(int *)(dword_ed7b4 + 0x10c) + 1;
  }
  return;
}


// ================================================================================================
// speech_lru_clip @ 0x84036 [__watcall]
// ================================================================================================

undefined8 __watcall speech_lru_clip(undefined4 param_1,undefined4 unaff_EDX)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  
  __CHK(0x10);
  iVar2 = 399;
  do {
    if (iVar2 < 0) {
      uVar3 = 0;
LAB_000840a3:
      return CONCAT44(unaff_EDX,uVar3);
    }
    iVar1 = iVar2 * 0x26;
    if (*(int *)(dword_ed7b0 + iVar1 + 0x22) == 1) {
      uVar4 = speech_find_bank_entry();
      iVar2 = (int)((ulonglong)uVar4 >> 0x20);
      if ((int)uVar4 == 0) {
        *(undefined4 *)(iVar1 + 0x22 + dword_ed7b0) = 0;
        *(int *)(dword_ed7b0 + 0x3b6c) =
             *(int *)(dword_ed7b0 + 0x3b6c) - *(int *)(iVar1 + 0x16 + dword_ed7b0);
        *(int *)(dword_ed7b0 + 0x3b74) = *(int *)(dword_ed7b0 + 0x3b74) + -1;
        uVar3 = 1;
        goto LAB_000840a3;
      }
    }
    iVar2 = iVar2 + -1;
  } while( true );
}


// ================================================================================================
// speech_copy_to_buffer @ 0x840a9 [__watcall]
// ================================================================================================

void __watcall speech_copy_to_buffer(int param_1,int unaff_EDX,uint unaff_EBX)

{
  undefined4 uVar1;
  undefined2 extraout_var;
  undefined2 extraout_var_00;
  undefined2 extraout_var_01;
  undefined2 extraout_var_02;
  uint uVar2;
  undefined2 in_DS;
  
  __CHK(0x20);
  for (; unaff_EBX != 0; unaff_EBX = unaff_EBX - uVar2) {
    uVar2 = unaff_EBX;
    if (dword_d27b7 < unaff_EBX) {
      uVar2 = dword_d27b7;
    }
    uVar1 = identity_972f0(unaff_EDX);
    memmove_fs(dword_ed7b8,CONCAT22(extraout_var_01,in_DS),uVar1,CONCAT22(extraout_var,in_DS),uVar2);
    uVar1 = identity_972f0(param_1);
    memmove_fs(uVar1,CONCAT22(extraout_var_02,in_DS),dword_ed7b8,CONCAT22(extraout_var_00,in_DS),
              uVar2);
    unaff_EDX = unaff_EDX + uVar2;
    param_1 = param_1 + uVar2;
  }
  return;
}


// ================================================================================================
// speech_clip_play_data @ 0x84125 [__watcall]
// ================================================================================================

void __watcall speech_clip_play_data(int param_1,int unaff_EDX)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 auStackY_40 [10];
  int iStackY_18;
  
  __CHK(0x44);
  if (param_1 == 0) {
    iVar2 = *(int *)(dword_ed7b0 + 0x3b64);
  }
  else {
    iVar2 = *(int *)(dword_ed7b0 + 0xe + (param_1 + -1) * 0x26) +
            *(int *)(dword_ed7b0 + 0x16 + (param_1 + -1) * 0x26);
  }
  iStackY_18 = unaff_EDX * 0x26;
  speech_copy_to_buffer(iVar2,*(undefined4 *)(dword_ed7b0 + 0xe + unaff_EDX * 0x26),
            *(undefined4 *)(dword_ed7b0 + iStackY_18 + 0x16));
  puVar4 = (undefined4 *)(dword_ed7b0 + param_1 * 0x26);
  puVar3 = puVar4;
  puVar5 = auStackY_40;
  for (iVar1 = 9; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar5 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar5 = puVar5 + 1;
  }
  *(undefined2 *)puVar5 = *(undefined2 *)puVar3;
  puVar3 = (undefined4 *)(iStackY_18 + dword_ed7b0);
  for (iVar1 = 9; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar4 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  }
  *(undefined2 *)puVar4 = *(undefined2 *)puVar3;
  puVar4 = auStackY_40;
  puVar3 = (undefined4 *)(dword_ed7b0 + iStackY_18);
  for (iVar1 = 9; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar4;
    puVar4 = puVar4 + 1;
    puVar3 = puVar3 + 1;
  }
  *(undefined2 *)puVar3 = *(undefined2 *)puVar4;
  *(int *)(param_1 * 0x26 + 0xe + dword_ed7b0) = iVar2;
  *(undefined4 *)(dword_ed7b0 + iStackY_18 + 0x22) = 0;
  return;
}


// ================================================================================================
// speech_make_room @ 0x84205 [__watcall]
// ================================================================================================

void __watcall speech_make_room(void)

{
  uint uVar1;
  bool bVar2;
  uint uVar3;
  int iVar4;
  int extraout_EDX;
  
  __CHK(0x14);
  iVar4 = 0;
  bVar2 = false;
  uVar1 = *(uint *)(dword_ed7b0 + 0x3b68);
  uVar3 = *(int *)(dword_ed7b0 + 0x3b6c) + *(int *)(dword_ed7b4 + 0x104);
  if (uVar1 < uVar3) {
    do {
      speech_lru_clip(uVar3,iVar4);
      uVar3 = *(int *)(dword_ed7b0 + 0x3b6c) + *(int *)(dword_ed7b4 + 0x104);
      if (uVar3 < uVar1) {
        bVar2 = true;
      }
    } while ((!bVar2) && (iVar4 = extraout_EDX + 1, iVar4 < 400));
  }
  return;
}


// ================================================================================================
// speech_play_sentence @ 0x8426f [__watcall]
// ================================================================================================

void __watcall speech_play_sentence(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined8 uVar3;
  
  __CHK(4);
  speech_make_room();
  __CHK(0xc);
  uVar3 = speech_find_free_clip(0);
  iVar2 = (int)uVar3;
  if (iVar2 == -1) goto LAB_0008429f;
  while( true ) {
    uVar1 = speech_find_loaded_clip();
    uVar3 = CONCAT44(uVar1,iVar2);
LAB_0008429f:
    if ((int)((ulonglong)uVar3 >> 0x20) == -1) break;
    speech_clip_play_data((int)uVar3);
    iVar2 = speech_find_free_clip((int)uVar3);
  }
  return;
}


// ================================================================================================
// speech_minutes_clip @ 0x842ba [__watcall]
// ================================================================================================

void __watcall speech_minutes_clip(int param_1,char *unaff_EDX,undefined4 unaff_EBX)

{
  char *__src;
  
  __CHK(0x14);
  if (param_1 < 2) {
    if (param_1 == -1) {
      sprintf(unaff_EDX,aGamemiscS,&aCor,unaff_EBX);
      return;
    }
  }
  else if ((2 < param_1) && (param_1 == 5)) {
    __src = a5minCor;
    goto LAB_000842ff;
  }
  __src = a2minCor;
LAB_000842ff:
  strcpy(unaff_EDX,__src);
  return;
}


// ================================================================================================
// speech_playoff_round @ 0x84306 [__watcall]
// ================================================================================================

uint __watcall
speech_playoff_round(char *param_1,uint unaff_EDX,uint unaff_EBX,undefined4 unaff_ECX)

{
  uint uVar1;
  char *__format;
  
  __CHK(0x10);
  if (unaff_EDX < 2) {
    if (unaff_EDX != 1) {
      return unaff_EBX;
    }
    if (unaff_EBX < 2) {
      if (unaff_EBX != 1) {
        return unaff_EBX;
      }
      __format = aEastquadBar;
    }
    else if (unaff_EBX < 3) {
      __format = aEastsemdBar;
    }
    else {
      if (unaff_EBX != 3) {
        return unaff_EBX;
      }
      __format = aEastfindBar;
    }
  }
  else if (unaff_EDX < 3) {
    if (unaff_EBX < 2) {
      if (unaff_EBX != 1) {
        return unaff_EBX;
      }
      __format = aWestquadBar;
    }
    else if (unaff_EBX < 3) {
      __format = aWestsemdBar;
    }
    else {
      if (unaff_EBX != 3) {
        return unaff_EBX;
      }
      __format = aWestfindBar;
    }
  }
  else {
    if (unaff_EDX != 3) {
      return unaff_EBX;
    }
    __format = aStanleydBar;
  }
  uVar1 = sprintf(param_1,__format,unaff_ECX);
  return uVar1;
}


// ================================================================================================
// speech_playoff_round2 @ 0x8438f [__watcall]
// ================================================================================================

uint __watcall
speech_playoff_round2(char *param_1,uint unaff_EDX,uint unaff_EBX,undefined4 unaff_ECX)

{
  uint uVar1;
  char *__format;
  
  __CHK(0x10);
  if (unaff_EDX < 2) {
    if (unaff_EDX != 1) {
      return unaff_EBX;
    }
    if (unaff_EBX < 2) {
      if (unaff_EBX != 1) {
        return unaff_EBX;
      }
      __format = aEastquauBar;
    }
    else if (unaff_EBX < 3) {
      __format = aEastsemuBar;
    }
    else {
      if (unaff_EBX != 3) {
        return unaff_EBX;
      }
      __format = aEastfinuBar;
    }
  }
  else if (unaff_EDX < 3) {
    if (unaff_EBX < 2) {
      if (unaff_EBX != 1) {
        return unaff_EBX;
      }
      __format = aWestquauBar;
    }
    else if (unaff_EBX < 3) {
      __format = aWestsemuBar;
    }
    else {
      if (unaff_EBX != 3) {
        return unaff_EBX;
      }
      __format = aWestfinuBar;
    }
  }
  else {
    if (unaff_EDX != 3) {
      return unaff_EBX;
    }
    __format = aStanleyuBar;
  }
  uVar1 = sprintf(param_1,__format,unaff_ECX);
  return uVar1;
}


// ================================================================================================
// speech_release_clip @ 0x84418 [__watcall]
// ================================================================================================

undefined8 __watcall speech_release_clip(undefined4 param_1,undefined4 unaff_EDX)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  undefined4 auStackY_50 [10];
  int local_28;
  int local_24;
  int local_20;
  int iStackY_1c;
  
  __CHK(0x54);
  iVar4 = *(int *)(dword_ed7ac + 0x54);
  *(int *)(dword_ed7ac + 0x54) = iVar4 + 1;
  local_20 = iVar4;
  iVar1 = speech_find_clip(param_1);
  if (iVar1 != -1) {
    iVar3 = speech_clip_loaded();
    if (iVar3 != 0) {
      *(int *)(dword_ed7ac + iVar4 * 4) = iVar1;
LAB_0008452c:
      uVar2 = 1;
      goto LAB_000836c3;
    }
    iVar4 = speech_find_free_clip();
    iStackY_1c = iVar4;
    if (iVar4 != -1) {
      local_28 = iVar4 * 0x26;
      local_24 = dword_ed7b0;
      puVar6 = (undefined4 *)(dword_ed7b0 + iVar4 * 0x26);
      puVar5 = puVar6;
      puVar7 = auStackY_50;
      for (iVar3 = 9; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar7 = *puVar5;
        puVar5 = puVar5 + 1;
        puVar7 = puVar7 + 1;
      }
      *(undefined2 *)puVar7 = *(undefined2 *)puVar5;
      puVar5 = (undefined4 *)(local_24 + iVar1 * 0x26);
      for (iVar3 = 9; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar6 = *puVar5;
        puVar5 = puVar5 + 1;
        puVar6 = puVar6 + 1;
      }
      *(undefined2 *)puVar6 = *(undefined2 *)puVar5;
      puVar6 = auStackY_50;
      puVar5 = (undefined4 *)(dword_ed7b0 + iVar1 * 0x26);
      for (iVar3 = 9; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar5 = *puVar6;
        puVar6 = puVar6 + 1;
        puVar5 = puVar5 + 1;
      }
      *(undefined2 *)puVar5 = *(undefined2 *)puVar6;
      if ((uint)(*(int *)(dword_ed7b0 + 0x3b6c) + *(int *)(local_28 + dword_ed7b0 + 0x16)) <=
          *(uint *)(dword_ed7b0 + 0x3b68)) {
        if (*(char *)(local_28 + dword_ed7b0 + 0xd) == 'G') {
          speech_clip_decode(iVar4);
        }
        else {
          speech_clip_read(iVar4);
        }
        *(int *)(dword_ed7ac + local_20 * 4) = iStackY_1c;
        goto LAB_0008452c;
      }
    }
  }
  uVar2 = 0;
  *(int *)(dword_ed7ac + 0x54) = *(int *)(dword_ed7ac + 0x54) + -1;
LAB_000836c3:
  return CONCAT44(unaff_EDX,uVar2);
}


// ================================================================================================
// speech_preload_clip @ 0x84539 [__watcall]
// ================================================================================================

undefined8 __watcall speech_preload_clip(undefined4 param_1,undefined4 unaff_EDX)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  undefined4 auStackY_44 [10];
  int iStackY_1c;
  
  __CHK(0x48);
  iVar1 = speech_find_clip();
  if (iVar1 != -1) {
    iVar3 = speech_clip_loaded();
    if (iVar3 != 0) {
LAB_00084602:
      uVar2 = 1;
      goto LAB_000836c3;
    }
    iVar3 = speech_find_free_clip();
    if (iVar3 != -1) {
      iStackY_1c = iVar1 * 0x26;
      puVar6 = (undefined4 *)(iVar1 * 0x26 + dword_ed7b0);
      if ((uint)(*(int *)(dword_ed7b0 + 0x3b6c) + *(int *)((int)puVar6 + 0x16)) <=
          *(uint *)(dword_ed7b0 + 0x3b68)) {
        puVar4 = (undefined4 *)(dword_ed7b0 + iVar3 * 0x26);
        puVar5 = puVar4;
        puVar7 = auStackY_44;
        for (iVar1 = 9; iVar1 != 0; iVar1 = iVar1 + -1) {
          *puVar7 = *puVar5;
          puVar5 = puVar5 + 1;
          puVar7 = puVar7 + 1;
        }
        *(undefined2 *)puVar7 = *(undefined2 *)puVar5;
        for (iVar1 = 9; iVar1 != 0; iVar1 = iVar1 + -1) {
          *puVar4 = *puVar6;
          puVar6 = puVar6 + 1;
          puVar4 = puVar4 + 1;
        }
        *(undefined2 *)puVar4 = *(undefined2 *)puVar6;
        puVar6 = auStackY_44;
        puVar5 = (undefined4 *)(dword_ed7b0 + iStackY_1c);
        for (iVar1 = 9; iVar1 != 0; iVar1 = iVar1 + -1) {
          *puVar5 = *puVar6;
          puVar6 = puVar6 + 1;
          puVar5 = puVar5 + 1;
        }
        *(undefined2 *)puVar5 = *(undefined2 *)puVar6;
        if (*(char *)(dword_ed7b0 + 0xd + iVar3 * 0x26) == 'G') {
          speech_clip_decode(iVar3);
        }
        else {
          speech_clip_read(iVar3);
        }
        goto LAB_00084602;
      }
    }
  }
  uVar2 = 0;
LAB_000836c3:
  return CONCAT44(unaff_EDX,uVar2);
}


// ================================================================================================
// speech_say_clip @ 0x8460f [__watcall]
// ================================================================================================

undefined8 __watcall speech_say_clip(void)

{
  int iVar1;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 unaff_retaddr;
  
  iVar1 = speech_available();
  if (iVar1 != 0) {
    speech_reset();
    speech_begin();
    *(undefined4 *)(dword_ed7b0 + 0x3b70) = 0;
    speech_queue_clip(extraout_EDX);
    speech_play_sentence();
    speech_release_clip(extraout_EDX_00);
    *(undefined4 *)(dword_ed7ac + 0x60) = 1;
    iVar1 = 1;
  }
  return CONCAT44(unaff_retaddr,iVar1);
}


// ================================================================================================
// speech_say_clip_b @ 0x84657 [__watcall]
// ================================================================================================

longlong __watcall speech_say_clip_b(undefined4 param_1,uint unaff_EDX)

{
  int iVar1;
  int extraout_EDX;
  int extraout_EDX_00;
  
  __CHK(8);
  if (speech_enabled == 0) {
    return (ulonglong)unaff_EDX << 0x20;
  }
  iVar1 = speech_available(param_1,param_1);
  if (iVar1 != 0) {
    speech_reset();
    speech_begin();
    speech_queue_clip((&off_d2776)[extraout_EDX]);
    speech_play_sentence();
    speech_release_clip((&off_d2776)[extraout_EDX_00]);
    *(undefined4 *)(dword_ed7ac + 0x60) = 1;
    iVar1 = 1;
  }
  return CONCAT44(unaff_EDX,iVar1);
}


// ================================================================================================
// say_nhl_int @ 0x846b4 [__watcall]
// ================================================================================================

longlong __watcall say_nhl_int(undefined4 param_1,uint unaff_EDX)

{
  int iVar1;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  
  __CHK(4);
  __CHK(8);
  if (speech_enabled == 0) {
    return (ulonglong)unaff_EDX << 0x20;
  }
  iVar1 = speech_available(aNhlInt,aNhlInt);
  if (iVar1 != 0) {
    speech_reset();
    speech_begin();
    *(undefined4 *)(dword_ed7b0 + 0x3b70) = 0;
    speech_queue_clip(extraout_EDX);
    speech_play_sentence();
    speech_release_clip(extraout_EDX_00);
    *(undefined4 *)(dword_ed7ac + 0x60) = 1;
    iVar1 = 1;
  }
  return CONCAT44(unaff_EDX,iVar1);
}


// ================================================================================================
// say_goodnite_int @ 0x846c8 [__watcall]
// ================================================================================================

longlong __watcall say_goodnite_int(undefined4 param_1,uint unaff_EDX)

{
  int iVar1;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  
  __CHK(4);
  __CHK(8);
  if (speech_enabled == 0) {
    return (ulonglong)unaff_EDX << 0x20;
  }
  iVar1 = speech_available(aGoodniteInt,aGoodniteInt);
  if (iVar1 != 0) {
    speech_reset();
    speech_begin();
    *(undefined4 *)(dword_ed7b0 + 0x3b70) = 0;
    speech_queue_clip(extraout_EDX);
    speech_play_sentence();
    speech_release_clip(extraout_EDX_00);
    *(undefined4 *)(dword_ed7ac + 0x60) = 1;
    iVar1 = 1;
  }
  return CONCAT44(unaff_EDX,iVar1);
}


// ================================================================================================
// say_lineups_int @ 0x846dc [__watcall]
// ================================================================================================

longlong __watcall say_lineups_int(undefined4 param_1,uint unaff_EDX)

{
  int iVar1;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  
  __CHK(4);
  __CHK(8);
  if (speech_enabled == 0) {
    return (ulonglong)unaff_EDX << 0x20;
  }
  iVar1 = speech_available(aLineupsInt,aLineupsInt);
  if (iVar1 != 0) {
    speech_reset();
    speech_begin();
    *(undefined4 *)(dword_ed7b0 + 0x3b70) = 0;
    speech_queue_clip(extraout_EDX);
    speech_play_sentence();
    speech_release_clip(extraout_EDX_00);
    *(undefined4 *)(dword_ed7ac + 0x60) = 1;
    iVar1 = 1;
  }
  return CONCAT44(unaff_EDX,iVar1);
}


// ================================================================================================
// say_nowback_int @ 0x846f0 [__watcall]
// ================================================================================================

longlong __watcall say_nowback_int(undefined4 param_1,uint unaff_EDX)

{
  int iVar1;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  
  __CHK(4);
  __CHK(8);
  if (speech_enabled == 0) {
    return (ulonglong)unaff_EDX << 0x20;
  }
  iVar1 = speech_available(aNowbackInt,aNowbackInt);
  if (iVar1 != 0) {
    speech_reset();
    speech_begin();
    *(undefined4 *)(dword_ed7b0 + 0x3b70) = 0;
    speech_queue_clip(extraout_EDX);
    speech_play_sentence();
    speech_release_clip(extraout_EDX_00);
    *(undefined4 *)(dword_ed7ac + 0x60) = 1;
    iVar1 = 1;
  }
  return CONCAT44(unaff_EDX,iVar1);
}


// ================================================================================================
// release_nowback_int @ 0x84704 [__watcall]
// ================================================================================================

void __watcall release_nowback_int(void)

{
  int iVar1;
  int iVar2;
  
  __CHK(4);
  __CHK(0xc);
  iVar1 = speech_find_clip(aNowbackInt);
  if (iVar1 != -1) {
    iVar2 = dword_ed7b0 + iVar1 * 0x26;
    if (*(int *)(iVar2 + 0x22) == 1) {
      *(undefined4 *)(iVar2 + 0x22) = 0;
      *(int *)(dword_ed7b0 + 0x3b6c) =
           *(int *)(dword_ed7b0 + 0x3b6c) - *(int *)(iVar1 * 0x26 + 0x16 + dword_ed7b0);
      *(int *)(dword_ed7b0 + 0x3b74) = *(int *)(dword_ed7b0 + 0x3b74) + -1;
      speech_play_sentence();
    }
  }
  return;
}


// ================================================================================================
// say_backmomt_int @ 0x84715 [__watcall]
// ================================================================================================

longlong __watcall say_backmomt_int(undefined4 param_1,uint unaff_EDX)

{
  int iVar1;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  
  __CHK(4);
  __CHK(8);
  if (speech_enabled == 0) {
    return (ulonglong)unaff_EDX << 0x20;
  }
  iVar1 = speech_available(aBackmomtInt,aBackmomtInt);
  if (iVar1 != 0) {
    speech_reset();
    speech_begin();
    *(undefined4 *)(dword_ed7b0 + 0x3b70) = 0;
    speech_queue_clip(extraout_EDX);
    speech_play_sentence();
    speech_release_clip(extraout_EDX_00);
    *(undefined4 *)(dword_ed7ac + 0x60) = 1;
    iVar1 = 1;
  }
  return CONCAT44(unaff_EDX,iVar1);
}


// ================================================================================================
// release_backmomt_int @ 0x84729 [__watcall]
// ================================================================================================

void __watcall release_backmomt_int(void)

{
  int iVar1;
  int iVar2;
  
  __CHK(4);
  __CHK(0xc);
  iVar1 = speech_find_clip(aBackmomtInt);
  if (iVar1 != -1) {
    iVar2 = dword_ed7b0 + iVar1 * 0x26;
    if (*(int *)(iVar2 + 0x22) == 1) {
      *(undefined4 *)(iVar2 + 0x22) = 0;
      *(int *)(dword_ed7b0 + 0x3b6c) =
           *(int *)(dword_ed7b0 + 0x3b6c) - *(int *)(iVar1 * 0x26 + 0x16 + dword_ed7b0);
      *(int *)(dword_ed7b0 + 0x3b74) = *(int *)(dword_ed7b0 + 0x3b74) + -1;
      speech_play_sentence();
    }
  }
  return;
}


// ================================================================================================
// say_coachclp_int @ 0x8473a [__watcall]
// ================================================================================================

longlong __watcall say_coachclp_int(undefined4 param_1,uint unaff_EDX)

{
  int iVar1;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  
  __CHK(4);
  __CHK(8);
  if (speech_enabled == 0) {
    return (ulonglong)unaff_EDX << 0x20;
  }
  iVar1 = speech_available(aCoachclpInt,aCoachclpInt);
  if (iVar1 != 0) {
    speech_reset();
    speech_begin();
    *(undefined4 *)(dword_ed7b0 + 0x3b70) = 0;
    speech_queue_clip(extraout_EDX);
    speech_play_sentence();
    speech_release_clip(extraout_EDX_00);
    *(undefined4 *)(dword_ed7ac + 0x60) = 1;
    iVar1 = 1;
  }
  return CONCAT44(unaff_EDX,iVar1);
}


// ================================================================================================
// release_coachclp_int @ 0x8474e [__watcall]
// ================================================================================================

void __watcall release_coachclp_int(void)

{
  int iVar1;
  int iVar2;
  
  __CHK(4);
  __CHK(0xc);
  iVar1 = speech_find_clip(aCoachclpInt);
  if (iVar1 != -1) {
    iVar2 = dword_ed7b0 + iVar1 * 0x26;
    if (*(int *)(iVar2 + 0x22) == 1) {
      *(undefined4 *)(iVar2 + 0x22) = 0;
      *(int *)(dword_ed7b0 + 0x3b6c) =
           *(int *)(dword_ed7b0 + 0x3b6c) - *(int *)(iVar1 * 0x26 + 0x16 + dword_ed7b0);
      *(int *)(dword_ed7b0 + 0x3b74) = *(int *)(dword_ed7b0 + 0x3b74) + -1;
      speech_play_sentence();
    }
  }
  return;
}


// ================================================================================================
// say_elsenhl_int @ 0x847ba [__watcall]
// ================================================================================================

longlong __watcall say_elsenhl_int(undefined4 param_1,uint unaff_EDX)

{
  int iVar1;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  
  __CHK(4);
  __CHK(8);
  if (speech_enabled == 0) {
    return (ulonglong)unaff_EDX << 0x20;
  }
  iVar1 = speech_available(aElsenhlInt,aElsenhlInt);
  if (iVar1 != 0) {
    speech_reset();
    speech_begin();
    *(undefined4 *)(dword_ed7b0 + 0x3b70) = 0;
    speech_queue_clip(extraout_EDX);
    speech_play_sentence();
    speech_release_clip(extraout_EDX_00);
    *(undefined4 *)(dword_ed7ac + 0x60) = 1;
    iVar1 = 1;
  }
  return CONCAT44(unaff_EDX,iVar1);
}


// ================================================================================================
// say_highlight_intro @ 0x847ce [__watcall]
// ================================================================================================

int __watcall say_highlight_intro(undefined4 param_1,undefined4 param_2,undefined4 unaff_EBX)

{
  int iVar1;
  undefined4 extraout_EDX;
  char acStack_34 [16];
  char acStack_24 [16];
  char acStack_14 [12];
  undefined4 uStack_8;
  
  uStack_8 = 0x847d8;
  __CHK(0x48);
  if (speech_enabled == 0) {
    return 0;
  }
  iVar1 = speech_available();
  if (iVar1 != 0) {
    *(undefined4 *)(dword_ed7b0 + 0x3b70) = 0;
    sprintf(acStack_14,unk_d24dc,param_1,&aRnk);
    sprintf(acStack_24,unk_d24dc,extraout_EDX,&aAwa);
    sprintf(acStack_34,unk_d24dc,unaff_EBX,&aHom);
    speech_reset();
    speech_begin();
    speech_queue_clip(aTakeynowBar);
    speech_queue_clip(acStack_14);
    speech_queue_clip(aHighliteBar);
    speech_queue_clip(aOfBar);
    speech_queue_clip(aGamebtwnBar);
    speech_queue_clip(acStack_24);
    speech_queue_clip(aAndBar);
    speech_queue_clip(acStack_34);
    speech_play_sentence();
    speech_release_clip(aTakeynowBar);
    speech_release_clip(acStack_14);
    speech_release_clip(aHighliteBar);
    speech_release_clip(aOfBar);
    speech_release_clip(aGamebtwnBar);
    speech_release_clip(acStack_24);
    speech_release_clip(aAndBar);
    speech_release_clip(acStack_34);
    *(undefined4 *)(dword_ed7ac + 0x60) = 1;
    iVar1 = 1;
  }
  return iVar1;
}


// ================================================================================================
// say_series_result @ 0x8490d [__watcall]
// ================================================================================================

int __watcall
say_series_result(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 param_4,
                 int param_5,int param_6)

{
  int iVar1;
  undefined4 extraout_ECX;
  char acStack_4c [16];
  undefined auStack_3c [16];
  undefined auStack_2c [16];
  char acStack_1c [16];
  
  __CHK(100);
  if (speech_enabled == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = speech_available();
    if (iVar1 != 0) {
      *(undefined4 *)(dword_ed7b0 + 0x3b70) = 0;
      sprintf(acStack_1c,unk_d24dc,param_1,&aAwa);
      itoa(unaff_EDX,auStack_2c,10);
      sprintf(acStack_4c,unk_c38ca,aGamenum,auStack_2c,&aBar);
      speech_playoff_round(auStack_3c,unaff_EBX,extraout_ECX);
      speech_begin();
      speech_reset();
      if (param_5 != 0) {
        speech_queue_clip(aOvertimeBar);
      }
      speech_queue_clip(acStack_1c);
      speech_queue_clip(aHavewonBar);
      if (param_6 == 0) {
        speech_queue_clip(aGamenumBar);
        speech_queue_clip(acStack_4c);
        speech_queue_clip(aOfBar);
      }
      speech_queue_clip(auStack_3c);
      speech_play_sentence();
      if (param_5 != 0) {
        speech_release_clip(aOvertimeBar);
      }
      speech_release_clip(acStack_1c);
      speech_release_clip(aHavewonBar);
      if (param_6 == 0) {
        speech_release_clip(aGamenumBar);
        speech_release_clip(acStack_4c);
        speech_release_clip(aOfBar);
      }
      speech_release_clip(auStack_3c);
      *(undefined4 *)(dword_ed7ac + 0x60) = 1;
      iVar1 = 1;
    }
  }
  return iVar1;
}


// ================================================================================================
// say_thegame_bar @ 0x84a6c [__watcall]
// ================================================================================================

longlong __watcall say_thegame_bar(undefined4 param_1,uint unaff_EDX)

{
  int iVar1;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  
  __CHK(4);
  __CHK(8);
  if (speech_enabled == 0) {
    return (ulonglong)unaff_EDX << 0x20;
  }
  iVar1 = speech_available(aThegameBar,aThegameBar);
  if (iVar1 != 0) {
    speech_reset();
    speech_begin();
    *(undefined4 *)(dword_ed7b0 + 0x3b70) = 0;
    speech_queue_clip(extraout_EDX);
    speech_play_sentence();
    speech_release_clip(extraout_EDX_00);
    *(undefined4 *)(dword_ed7ac + 0x60) = 1;
    iVar1 = 1;
  }
  return CONCAT44(unaff_EDX,iVar1);
}


// ================================================================================================
// say_period_score_bar @ 0x84a7d [__watcall]
// ================================================================================================

longlong __watcall say_period_score_bar(uint param_1,uint unaff_EDX,int unaff_EBX)

{
  int iVar1;
  char *pcVar2;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  
  __CHK(4);
  if (unaff_EBX == 0) {
    if (unaff_EDX == 0) {
      if (param_1 < 2) {
        if (param_1 != 1) {
          return 0;
        }
        pcVar2 = aScor1perBar;
      }
      else if (param_1 < 3) {
        pcVar2 = aScor2perBar;
      }
      else {
        if (param_1 != 3) {
          return 0;
        }
        pcVar2 = aScor3perBar;
      }
    }
    else {
      if (param_1 < 2) {
        if (param_1 == 1) {
          pcVar2 = aScor1otpBar;
          goto LAB_00084aae;
        }
      }
      else {
        if (param_1 < 3) {
          pcVar2 = aScor2otpBar;
          goto LAB_00084aae;
        }
        if (param_1 == 3) {
          pcVar2 = aScor3otpBar;
          goto LAB_00084aae;
        }
      }
      pcVar2 = aScortotpBar;
    }
  }
  else {
    pcVar2 = aThegameBar;
  }
LAB_00084aae:
  __CHK(8);
  if (speech_enabled != 0) {
    iVar1 = speech_available(pcVar2,pcVar2);
    if (iVar1 != 0) {
      speech_reset();
      speech_begin();
      *(undefined4 *)(dword_ed7b0 + 0x3b70) = 0;
      speech_queue_clip(extraout_EDX);
      speech_play_sentence();
      speech_release_clip(extraout_EDX_00);
      *(undefined4 *)(dword_ed7ac + 0x60) = 1;
      iVar1 = 1;
    }
    return CONCAT44(unaff_EDX,iVar1);
  }
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// say_game_intro @ 0x84b0d [__watcall]
// ================================================================================================

int __watcall say_game_intro(undefined4 param_1,undefined4 param_2,undefined4 unaff_EBX)

{
  int iVar1;
  undefined4 extraout_EDX;
  char acStack_34 [16];
  char acStack_24 [16];
  char acStack_14 [12];
  undefined4 uStack_8;
  
  uStack_8 = 0x84b17;
  __CHK(0x48);
  if (speech_enabled == 0) {
    return 0;
  }
  iVar1 = speech_available();
  if (iVar1 != 0) {
    *(undefined4 *)(dword_ed7b0 + 0x3b70) = 0;
    sprintf(acStack_14,unk_d24dc,param_1,&aRnk);
    sprintf(acStack_24,unk_d24dc,extraout_EDX,&aAwa);
    sprintf(acStack_34,unk_d24dc,unaff_EBX,&aHom);
    speech_reset();
    speech_begin();
    speech_queue_clip(aTonightBar);
    speech_queue_clip(acStack_14);
    speech_queue_clip(aEasportsBar);
    speech_queue_clip(aGamebtwnBar);
    speech_queue_clip(acStack_24);
    speech_queue_clip(aAndBar);
    speech_queue_clip(acStack_34);
    speech_play_sentence();
    speech_release_clip(aTonightBar);
    speech_release_clip(acStack_14);
    speech_release_clip(aEasportsBar);
    speech_release_clip(aGamebtwnBar);
    speech_release_clip(acStack_24);
    speech_release_clip(aAndBar);
    speech_release_clip(acStack_34);
    *(undefined4 *)(dword_ed7ac + 0x60) = 1;
    iVar1 = 1;
  }
  return iVar1;
}


// ================================================================================================
// say_playoff_game_intro @ 0x84c38 [__watcall]
// ================================================================================================

int __watcall
say_playoff_game_intro
          (undefined4 param_1,undefined4 param_2,undefined4 unaff_EBX,undefined4 param_4,
          undefined4 param_5,undefined4 param_6)

{
  int iVar1;
  undefined4 extraout_ECX;
  undefined4 extraout_EDX;
  undefined auStack_64 [16];
  char acStack_54 [16];
  char acStack_44 [16];
  undefined auStack_34 [16];
  char acStack_24 [16];
  char acStack_14 [12];
  undefined4 uStack_8;
  
  uStack_8 = 0x84c42;
  __CHK(0x7c);
  if (speech_enabled == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = speech_available();
    if (iVar1 != 0) {
      *(undefined4 *)(dword_ed7b0 + 0x3b70) = 0;
      sprintf(acStack_24,unk_d24dc,param_1,&aRnk);
      sprintf(acStack_14,unk_d24dc,extraout_EDX,&aAwa);
      sprintf(acStack_54,unk_d24dc,unaff_EBX,&aHom);
      itoa(extraout_ECX,auStack_34,10);
      sprintf(acStack_44,unk_c38ca,aGamenum,auStack_34,&aBar);
      speech_playoff_round2(auStack_64,param_5,param_6);
      speech_reset();
      speech_begin();
      speech_queue_clip(aTonightBar);
      speech_queue_clip(acStack_24);
      speech_queue_clip(aEasportsBar);
      speech_queue_clip(acStack_44);
      speech_queue_clip(aOfBar);
      speech_queue_clip(auStack_64);
      speech_queue_clip(aBetweenBar);
      speech_queue_clip(acStack_14);
      speech_queue_clip(aAndBar);
      speech_queue_clip(acStack_54);
      speech_play_sentence();
      speech_release_clip(aTonightBar);
      speech_release_clip(acStack_24);
      speech_release_clip(aEasportsBar);
      speech_release_clip(acStack_44);
      speech_release_clip(aOfBar);
      speech_release_clip(auStack_64);
      speech_release_clip(aBetweenBar);
      speech_release_clip(acStack_14);
      speech_release_clip(aAndBar);
      speech_release_clip(acStack_54);
      *(undefined4 *)(dword_ed7ac + 0x60) = 1;
      iVar1 = 1;
    }
  }
  return iVar1;
}


// ================================================================================================
// say_time_remaining @ 0x84ddd [__watcall]
// ================================================================================================

void __watcall say_time_remaining(int param_1)

{
  char *pcVar1;
  char *pcVar2;
  undefined4 extraout_EDX;
  int extraout_EDX_00;
  int extraout_EDX_01;
  int iVar3;
  char acStack_24 [16];
  char acStack_14 [12];
  undefined4 uStack_8;
  
  uStack_8 = 0x84de7;
  __CHK(0x38);
  sprintf(acStack_14,unk_c38d6,param_1,&aNum);
  sprintf(acStack_24,a02dS,extraout_EDX,&aNum);
  pcVar2 = acStack_24;
  speech_queue_clip(aAtCor);
  speech_queue_clip(aPauseCor);
  iVar3 = extraout_EDX_00;
  if (param_1 != 0) {
    if (extraout_EDX_00 == 0) {
      if (param_1 == 1) {
        pcVar1 = a1minuteCor;
      }
      else {
        speech_queue_clip(acStack_14);
        pcVar1 = aMinutesCor;
      }
    }
    else {
      pcVar1 = acStack_14;
    }
    speech_queue_clip(pcVar1);
    iVar3 = extraout_EDX_01;
  }
  if (iVar3 == 1) {
    if (param_1 == 0) {
      pcVar2 = a1secondCor;
    }
  }
  else {
    if (iVar3 < 1) {
      return;
    }
    pcVar2 = acStack_24;
    if (param_1 == 0) {
      sprintf(acStack_24,unk_c38d6,iVar3,&aNum);
      speech_queue_clip(acStack_24);
      pcVar2 = aSecondsCor;
    }
  }
  speech_queue_clip(pcVar2);
  return;
}


// ================================================================================================
// release_time_remaining_clips @ 0x84eac [__watcall]
// ================================================================================================

void __watcall release_time_remaining_clips(int param_1)

{
  char *pcVar1;
  char *pcVar2;
  undefined4 extraout_EDX;
  int extraout_EDX_00;
  int extraout_EDX_01;
  int iVar3;
  char acStack_24 [16];
  char acStack_14 [12];
  undefined4 uStack_8;
  
  uStack_8 = 0x84eb6;
  __CHK(0x38);
  sprintf(acStack_14,unk_c38d6,param_1,&aNum);
  sprintf(acStack_24,a02dS,extraout_EDX,&aNum);
  pcVar2 = acStack_24;
  speech_release_clip(aAtCor);
  speech_release_clip(aPauseCor);
  iVar3 = extraout_EDX_00;
  if (param_1 != 0) {
    if (extraout_EDX_00 == 0) {
      if (param_1 == 1) {
        pcVar1 = a1minuteCor;
      }
      else {
        speech_release_clip(acStack_14);
        pcVar1 = aMinutesCor;
      }
    }
    else {
      pcVar1 = acStack_14;
    }
    speech_release_clip(pcVar1);
    iVar3 = extraout_EDX_01;
  }
  if (iVar3 == 1) {
    if (param_1 == 0) {
      pcVar2 = a1secondCor;
    }
  }
  else {
    if (iVar3 < 1) {
      return;
    }
    pcVar2 = acStack_24;
    if (param_1 == 0) {
      sprintf(acStack_24,unk_c38d6,iVar3,&aNum);
      speech_release_clip(acStack_24);
      pcVar2 = aSecondsCor;
    }
  }
  speech_release_clip(pcVar2);
  return;
}


// ================================================================================================
// say_penalty @ 0x84f7b [__watcall]
// ================================================================================================

int __watcall
say_penalty(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
           undefined4 param_5,undefined4 param_6,int param_7,int param_8,int param_9)

{
  int iVar1;
  char *pcVar2;
  undefined4 extraout_ECX;
  undefined4 extraout_EDX;
  int extraout_EDX_00;
  char acStack_4c [16];
  char acStack_3c [16];
  undefined auStack_2c [16];
  char acStack_1c [16];
  
  __CHK(0x60);
  iVar1 = speech_enabled;
  if (speech_enabled != 0) {
    iVar1 = speech_available();
    if (iVar1 != 0) {
      *(undefined4 *)(dword_ed7b0 + 0x3b70) = 0x1a;
      sprintf(acStack_4c,unk_d24dc,param_1,&aTea);
      sprintf(acStack_1c,unk_c38d6,extraout_EDX,&aNum);
      speech_minutes_clip(param_3,auStack_2c);
      sprintf(acStack_3c,unk_d24dc,extraout_ECX,&aPen_c38e8);
      speech_begin();
      speech_reset();
      speech_queue_clip(aOneleftCor);
      if (param_7 == 1) {
        speech_queue_clip(acStack_4c);
        if (extraout_EDX_00 < param_8) {
          pcVar2 = aPensnumCor;
        }
        else {
          pcVar2 = aPennumCor;
        }
      }
      else {
        pcVar2 = aAndnumCor;
      }
      speech_queue_clip(pcVar2);
      speech_queue_clip(acStack_1c);
      speech_queue_clip(aPauseCor);
      speech_queue_clip(auStack_2c);
      speech_queue_clip(acStack_3c);
      speech_queue_clip(aPauseCor);
      if (param_9 != 0) {
        say_time_remaining(param_5,param_6);
      }
      speech_play_sentence();
      if (param_7 == 1) {
        speech_release_clip(acStack_4c);
        if (param_8 < 2) {
          pcVar2 = aPennumCor;
        }
        else {
          pcVar2 = aPensnumCor;
        }
      }
      else {
        pcVar2 = aAndnumCor;
      }
      speech_release_clip(pcVar2);
      speech_release_clip(acStack_1c);
      speech_release_clip(aPauseCor);
      speech_release_clip(auStack_2c);
      speech_release_clip(acStack_3c);
      speech_release_clip(aPauseCor);
      if (param_9 != 0) {
        release_time_remaining_clips(param_5,param_6);
      }
      *(undefined4 *)(dword_ed7ac + 0x60) = 1;
      iVar1 = 1;
    }
  }
  return iVar1;
}


// ================================================================================================
// say_penalty_shot @ 0x8511e [__watcall]
// ================================================================================================

int __watcall say_penalty_shot(undefined4 param_1,undefined4 param_2,undefined4 unaff_EBX)

{
  int iVar1;
  undefined4 extraout_ECX;
  undefined4 extraout_EDX;
  char acStack_24 [16];
  char acStack_14 [12];
  undefined4 uStack_8;
  
  uStack_8 = 0x85128;
  __CHK(0x38);
  if (speech_enabled == 0) {
    return 0;
  }
  iVar1 = speech_available();
  if (iVar1 != 0) {
    *(undefined4 *)(dword_ed7b0 + 0x3b70) = 0x1a;
    sprintf(acStack_14,unk_d24dc,param_1,&aTea);
    sprintf(acStack_24,unk_c38d6,extraout_EDX,&aNum);
    speech_begin();
    speech_reset();
    speech_queue_clip(aOneleftCor);
    speech_queue_clip(acStack_14);
    speech_queue_clip(aPenshotCor);
    speech_queue_clip(acStack_24);
    speech_queue_clip(aPauseCor);
    say_time_remaining(unaff_EBX,extraout_ECX);
    speech_play_sentence();
    speech_release_clip(acStack_14);
    speech_release_clip(aPenshotCor);
    speech_release_clip(acStack_24);
    speech_release_clip(aPauseCor);
    release_time_remaining_clips(unaff_EBX,extraout_ECX);
    *(undefined4 *)(dword_ed7ac + 0x60) = 1;
    iVar1 = 1;
  }
  return iVar1;
}


// ================================================================================================
// say_star @ 0x85213 [__watcall]
// ================================================================================================

int __watcall say_star(undefined4 param_1,undefined4 param_2,undefined4 unaff_EBX)

{
  int iVar1;
  int extraout_EDX;
  char acStack_38 [16];
  char acStack_28 [16];
  char acStack_18 [16];
  
  __CHK(0x4c);
  if (speech_enabled == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = speech_available();
    if (iVar1 != 0) {
      *(undefined4 *)(dword_ed7b0 + 0x3b70) = 0x1a;
      sprintf(acStack_18,unk_d24dc,param_1,&aFrm);
      strncpy(acStack_38,*(char **)(a3rdstarCor + extraout_EDX * 4 + 8),0xd);
      sprintf(acStack_28,unk_c38d6,unaff_EBX,&aNum);
      speech_begin();
      speech_reset();
      speech_queue_clip(aOneleftCor);
      speech_queue_clip(acStack_38);
      speech_queue_clip(acStack_18);
      speech_queue_clip(aPauseCor);
      speech_queue_clip(aNumberCor);
      speech_queue_clip(acStack_28);
      speech_play_sentence();
      speech_release_clip(acStack_38);
      speech_release_clip(acStack_18);
      speech_release_clip(aPauseCor);
      speech_release_clip(aNumberCor);
      speech_release_clip(acStack_28);
      *(undefined4 *)(dword_ed7ac + 0x60) = 1;
      iVar1 = 1;
    }
  }
  return iVar1;
}


// ================================================================================================
// say_goal @ 0x8531f [__watcall]
// ================================================================================================

int __watcall
say_goal(undefined4 param_1,undefined4 param_2,undefined4 unaff_EBX,undefined4 param_4,
        undefined4 param_5)

{
  int iVar1;
  undefined4 extraout_ECX;
  int extraout_EDX;
  int extraout_EDX_00;
  int extraout_EDX_01;
  int extraout_EDX_02;
  char acStack_48 [16];
  char acStack_38 [16];
  char acStack_28 [16];
  char acStack_18 [16];
  
  __CHK(0x5c);
  if (speech_enabled == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = speech_available();
    if (iVar1 != 0) {
      *(undefined4 *)(dword_ed7b0 + 0x3b70) = 0x1a;
      sprintf(acStack_18,unk_d24dc,param_1,&aTea);
      sprintf(acStack_48,unk_c38d6,unaff_EBX,&aNum);
      sprintf(acStack_28,unk_c38d6,extraout_ECX,&aNum);
      sprintf(acStack_38,unk_c38d6,param_5,&aNum);
      speech_begin();
      speech_reset();
      speech_queue_clip(aOneleftCor);
      speech_queue_clip(acStack_18);
      speech_queue_clip(aGoalnumCor);
      speech_queue_clip(acStack_48);
      iVar1 = extraout_EDX;
      if (0 < extraout_EDX) {
        speech_queue_clip(aPauseCor);
        speech_queue_clip(aAsstnumCor);
        speech_queue_clip(acStack_28);
        iVar1 = extraout_EDX_00;
      }
      if (1 < iVar1) {
        speech_queue_clip(aPauseCor);
        speech_queue_clip(aAndnumCor);
        speech_queue_clip(acStack_38);
      }
      speech_play_sentence();
      speech_release_clip(acStack_18);
      speech_release_clip(aGoalnumCor);
      speech_release_clip(acStack_48);
      iVar1 = extraout_EDX_01;
      if (0 < extraout_EDX_01) {
        speech_release_clip(aPauseCor);
        speech_release_clip(aAsstnumCor);
        speech_release_clip(acStack_28);
        iVar1 = extraout_EDX_02;
      }
      if (1 < iVar1) {
        speech_release_clip(aPauseCor);
        speech_release_clip(aAndnumCor);
        speech_release_clip(acStack_38);
      }
      *(undefined4 *)(dword_ed7ac + 0x60) = 1;
      iVar1 = 1;
    }
  }
  return iVar1;
}


// ================================================================================================
// say_one_minute_left @ 0x854ac [__watcall]
// ================================================================================================

int __watcall say_one_minute_left(void)

{
  int iVar1;
  
  __CHK(8);
  if (speech_enabled == 0) {
    return 0;
  }
  iVar1 = speech_available();
  if (iVar1 != 0) {
    speech_begin();
    speech_reset();
    speech_queue_clip(aOneleftCor);
    speech_play_sentence();
    speech_release_clip(aOneleftCor);
    dword_ccc98 = 1;
    *(undefined4 *)(dword_ed7ac + 0x60) = 1;
    iVar1 = 1;
  }
  return iVar1;
}


// ================================================================================================
// speech_load_xbruce2 @ 0x85507 [__watcall]
// ================================================================================================

undefined8 __watcall speech_load_xbruce2(undefined4 param_1,undefined4 unaff_EDX)

{
  int iVar1;
  undefined *puVar2;
  undefined auStackY_1c [16];
  
  __CHK(0x20);
  if (speech_enabled == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = speech_available();
    if (iVar1 != 0) {
      speech_begin();
      speech_reset();
      puVar2 = install_path;
      if (byte_ed98c != '\x01') {
        puVar2 = (undefined *)0x0;
      }
      make_path(auStackY_1c,puVar2,aXBRUCE2,&aVIV);
      speech_load_bank(auStackY_1c,0);
      iVar1 = 1;
    }
  }
  return CONCAT44(unaff_EDX,iVar1);
}


// ================================================================================================
// say_player_name @ 0x85570 [__watcall]
// ================================================================================================

void __watcall say_player_name(void)

{
  int iVar1;
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
  char acStack_14 [12];
  undefined4 uStack_8;
  
  uStack_8 = 0x8557a;
  __CHK(0x28);
  if (100000 < (uint)(*(int *)(dword_ed7b0 + 0x3b68) - *(int *)(dword_ed7b0 + 0x3b6c))) {
    speech_begin();
    speech_reset();
    iVar1 = 0;
    do {
      sprintf(acStack_14,unk_c38d6,iVar1,&aNum);
      speech_queue_clip(acStack_14);
      iVar1 = extraout_EDX + 1;
    } while (iVar1 < 10);
    iVar1 = 0;
    do {
      sprintf(acStack_14,unk_c38d6,iVar1,&aNum);
      speech_release_clip(acStack_14);
      iVar1 = extraout_EDX_00 + 1;
    } while (iVar1 < 10);
  }
  if (100000 < (uint)(*(int *)(dword_ed7b0 + 0x3b68) - *(int *)(dword_ed7b0 + 0x3b6c))) {
    speech_begin();
    speech_reset();
    iVar1 = 10;
    do {
      sprintf(acStack_14,unk_c38d6,iVar1,&aNum);
      speech_queue_clip(acStack_14);
      iVar1 = extraout_EDX_01 + 1;
    } while (iVar1 < 0x14);
    iVar1 = 10;
    do {
      sprintf(acStack_14,unk_c38d6,iVar1,&aNum);
      speech_release_clip(acStack_14);
      iVar1 = extraout_EDX_02 + 1;
    } while (iVar1 < 0x14);
  }
  if (100000 < (uint)(*(int *)(dword_ed7b0 + 0x3b68) - *(int *)(dword_ed7b0 + 0x3b6c))) {
    speech_begin();
    speech_reset();
    iVar1 = 0x14;
    do {
      sprintf(acStack_14,unk_c38d6,iVar1,&aNum);
      speech_queue_clip(acStack_14);
      iVar1 = extraout_EDX_03 + 1;
    } while (iVar1 < 0x1e);
    iVar1 = 0x14;
    do {
      sprintf(acStack_14,unk_c38d6,iVar1,&aNum);
      speech_release_clip(acStack_14);
      iVar1 = extraout_EDX_04 + 1;
    } while (iVar1 < 0x1e);
  }
  if (100000 < (uint)(*(int *)(dword_ed7b0 + 0x3b68) - *(int *)(dword_ed7b0 + 0x3b6c))) {
    speech_begin();
    speech_reset();
    iVar1 = 0;
    do {
      sprintf(acStack_14,a02dS,iVar1,&aNum);
      speech_queue_clip(acStack_14);
      iVar1 = extraout_EDX_05 + 1;
    } while (iVar1 < 10);
    iVar1 = 0;
    do {
      sprintf(acStack_14,a02dS,iVar1,&aNum);
      speech_release_clip(acStack_14);
      iVar1 = extraout_EDX_06 + 1;
    } while (iVar1 < 10);
  }
  if (150000 < (uint)(*(int *)(dword_ed7b0 + 0x3b68) - *(int *)(dword_ed7b0 + 0x3b6c))) {
    speech_begin();
    speech_reset();
    iVar1 = 0;
    do {
      speech_queue_clip((&off_d273e)[iVar1]);
      iVar1 = extraout_EDX_07 + 1;
    } while (iVar1 < 0xe);
    iVar1 = 0;
    do {
      speech_release_clip((&off_d273e)[iVar1]);
      iVar1 = extraout_EDX_08 + 1;
    } while (iVar1 < 0xe);
  }
  return;
}


// ================================================================================================
// preload_speech @ 0x8579e [__watcall]
// ================================================================================================

int __watcall preload_speech(undefined4 param_1,undefined4 unaff_EDX)

{
  int iVar1;
  undefined *puVar2;
  undefined auStack_40 [16];
  char acStack_30 [16];
  char acStack_20 [16];
  
  __CHK(0x54);
  if (speech_enabled == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = speech_available();
    if (iVar1 != 0) {
      speech_begin();
      speech_reset();
      puVar2 = install_path;
      if (byte_ed98c != '\x01') {
        puVar2 = (undefined *)0x0;
      }
      make_path(auStack_40,puVar2,aXBRUCE2,&aVIV);
      speech_load_bank(auStack_40,0x1a);
      sprintf(acStack_20,unk_d24dc,param_1,&aTea);
      sprintf(acStack_30,unk_d24dc,unaff_EDX,&aTea);
      speech_queue_clip(aOneleftCor);
      speech_queue_clip(aPauseCor);
      speech_queue_clip(acStack_20);
      speech_queue_clip(acStack_30);
      speech_queue_clip(aGoalnumCor);
      speech_queue_clip(aAsstnumCor);
      speech_queue_clip(aAndnumCor);
      speech_queue_clip(aPennumCor);
      speech_queue_clip(aPensnumCor);
      speech_queue_clip(a2minCor);
      speech_queue_clip(aAtCor);
      speech_release_clip(aOneleftCor);
      speech_release_clip(aPauseCor);
      speech_release_clip(acStack_20);
      speech_release_clip(acStack_30);
      speech_release_clip(aGoalnumCor);
      speech_release_clip(aAsstnumCor);
      speech_release_clip(aAndnumCor);
      speech_release_clip(aPennumCor);
      speech_release_clip(aPensnumCor);
      speech_release_clip(a2minCor);
      speech_release_clip(aAtCor);
      say_player_name();
      iVar1 = 1;
    }
  }
  return iVar1;
}


// ================================================================================================
// broadcast_booth_screen @ 0x85924 [__watcall]
// ================================================================================================

undefined8 __watcall broadcast_booth_screen(undefined4 param_1,undefined4 unaff_EDX)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 unaff_EBP;
  byte bVar4;
  undefined auStackY_1030 [3944];
  char *__format;
  int iStack_5a;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined auStack_40 [24];
  int local_28 [4];
  
  bVar4 = 0;
  __CHK(0xcc);
  getfontstate(&stack0xffffff4c);
  setfont(font_main);
  make_path(&uStack_48,&league_dir,aGsummaryDb_c38f8,0);
  _dos_findfirst(&uStack_48,0);
  local_28[2] = 0;
  if (dword_c53fb == 0) {
    iVar3 = iStack_5a + 0x1328 >> 0x1f;
    local_28[0] = (int)((iStack_5a + 0x1328 + iVar3 * -0x400) - (uint)(iVar3 << 9 < 0)) >> 10;
    local_28[1] = 0;
    iVar3 = check_disk_space(0,local_28);
    if (iVar3 == 0) {
      if (dword_c5130 == 0) {
        iVar3 = save_game_dialog(&uStack_48);
        if (iVar3 != 0) {
          setfontstate(&stack0xffffff4c);
          unaff_EBP = 0;
          goto LAB_00085d5d;
        }
      }
      else {
        uStack_48 = aDemoNhl;
        (&uStack_44)[(uint)bVar4 * -2] = (&DAT_000c3927)[(uint)bVar4 * -2];
        auStack_40[(uint)bVar4 * -8 + (uint)bVar4 * -8] =
             (&DAT_000c392b)[(uint)bVar4 * -8 + (uint)bVar4 * -8];
      }
      byte_c52f2 = byte_c52f2 | 0x80;
      option_flags._1_1_ = option_flags._1_1_ | 0x80;
      load_game_set(&settings_exhibition);
      iVar3 = file_create(&uStack_48,local_28 + 3);
      if (iVar3 != 0) {
        fatalerror(&aH2);
      }
      iVar3 = file_write(local_28[3],&settings_exhibition,0xffffffff,0x75);
      if (iVar3 != 0) {
        fatalerror(&aH3);
      }
      make_path(&uStack_48,0,aGsummary_c3932,&aDB);
      uVar1 = loadfile(&uStack_48,0);
      uVar2 = filesize(&uStack_48);
      iVar3 = file_write(local_28[3],uVar1,0xffffffff,uVar2);
      if (iVar3 != 0) {
        fatalerror(&aH4);
      }
      freemem(uVar1);
      iVar3 = file_write(local_28[3],&unk_dd774,0xffffffff,0xc);
      if (iVar3 != 0) {
        fatalerror(&aH5);
      }
      iVar3 = file_write(local_28[3],&unk_dd788,0xffffffff,0xc);
      if (iVar3 != 0) {
        fatalerror(&aH6);
      }
      iVar3 = file_write(local_28[3],&unk_dd730,0xffffffff,0x18);
      if (iVar3 != 0) {
        fatalerror(&aH7_c3944);
      }
      save_game(local_28[3]);
      file_close(local_28 + 3);
    }
    else {
      set_dialog_colors(0xf9,0xfa,0xf8,0xfa,0);
      __format = aAGameYouRequire3dKbytes;
LAB_000859eb:
      sprintf(aAGameYouRequireXXXKbytes,__format,iVar3);
      message_dialog(0xffffffff,0xffffffff,&off_d2855,3,0,0,&dword_dc88c,&dword_dc888,800);
    }
  }
  else {
    iVar3 = iStack_5a + 0x3ff >> 0x1f;
    local_28[0] = (int)((iStack_5a + 0x3ff + iVar3 * -0x400) - (uint)(iVar3 << 9 < 0)) >> 10;
    local_28[1] = 4;
    iVar3 = check_disk_space(0,local_28);
    if (iVar3 != 0) {
      set_dialog_colors(0xf9,0xfa,0xf8,0xfa,0);
      __format = aAGameYouRequire3dKbytes_c3947;
      goto LAB_000859eb;
    }
    settimeout(200);
    set_dialog_colors(0xf9,0xfa,0xf8,0xfa,0);
    make_path(&uStack_48,&league_dir,aGameSav_c3966,0);
    iVar3 = file_create(&uStack_48,local_28 + 3);
    if (iVar3 != 0) {
      fatalerror(&aH1);
    }
    if (dword_c53fb == 2) {
      message_dialog(0xffffffff,0xffffffff,&off_d27ef,2,0,0,0,0,0);
      word_c53db._1_1_ = word_c53db._1_1_ | 0x80;
      option_flags._1_1_ = option_flags._1_1_ | 0x80;
      load_game_set(&settings_league);
      league_save_db(local_28[3]);
    }
    else {
      message_dialog(0xffffffff,0xffffffff,&off_d27f7,2,0,0,0,0,0);
      word_c5366._1_1_ = word_c5366._1_1_ | 0x80;
      option_flags._1_1_ = option_flags._1_1_ | 0x80;
      load_game_set(&settings_playoff);
    }
    save_game(local_28[3]);
    file_close(local_28 + 3);
    iVar3 = copy_file(aGsummary_c3932,&aDb_c3972,&aSav_c3976,&league_dir,&league_dir);
    if (iVar3 != 0) {
      fatalerror(&aA3_c397b);
    }
    waittimeout();
    restore_dialog_background();
  }
  setfontstate(&stack0xffffff4c);
LAB_00085d5d:
  return CONCAT44(unaff_EDX,unaff_EBP);
}


// ================================================================================================
// save_game_dialog @ 0x85d6c [__watcall]
// ================================================================================================

undefined8 __watcall save_game_dialog(char *param_1,undefined4 unaff_EDX)

{
  ulonglong uVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 uVar4;
  undefined *puVar5;
  undefined4 extraout_EDX;
  undefined4 ***pppuVar6;
  undefined4 ***pppuVar7;
  int iVar8;
  int iVar9;
  undefined4 *puVar10;
  undefined4 *puVar11;
  undefined4 *puVar12;
  undefined4 *puVar13;
  int iVar14;
  int iVar15;
  byte bVar16;
  ulonglong uVar17;
  undefined8 uVar18;
  undefined auStack_a8 [108];
  undefined4 **local_3c;
  undefined4 **local_38;
  undefined4 **local_34;
  int local_30;
  undefined4 **local_2c;
  undefined4 *local_28;
  undefined4 local_24;
  undefined4 *local_20;
  undefined4 *puStack_1c;
  
  bVar16 = 0;
  __CHK(0xc0);
  local_30 = ((int)pointer_shapes[1] >> 0x10) * ((*(int *)((int)pointer_shapes + 2) >> 0x10) + 8) +
             0x11;
  puVar2 = (undefined4 *)allocmem(aPointer_c397e,local_30,0x20);
  puVar10 = puVar2 + (uint)bVar16 * -2 + 1;
  pppuVar6 = pointer_shapes + (uint)bVar16 * -2 + 1;
  *puVar2 = *pointer_shapes;
  puVar11 = puVar10 + (uint)bVar16 * -2 + 1;
  pppuVar7 = pppuVar6 + (uint)bVar16 * -2 + 1;
  *puVar10 = *pppuVar6;
  *puVar11 = *pppuVar7;
  puVar11[(uint)bVar16 * -2 + 1] = pppuVar7[(uint)bVar16 * -2 + 1];
  *(undefined *)(puVar11 + (uint)bVar16 * -2 + 1 + (uint)bVar16 * -2 + 1) =
       *(undefined *)(pppuVar7 + (uint)bVar16 * -2 + 1 + (uint)bVar16 * -2 + 1);
  setdefaultscreen();
  getmouse(&local_30,&local_34,&local_38);
  local_3c = local_34;
  local_2c = local_38;
  grabshape(puVar2,local_34,local_38);
  drawshape2_remap(pointer_shapes,local_34,local_38);
  puVar5 = install_path;
  if (byte_ed92f != '\x01') {
    puVar5 = (undefined *)0x0;
  }
  make_path(auStack_a8,puVar5,aSavegame,0);
  local_24 = loadshapes(auStack_a8,0);
  local_28 = (undefined4 *)locateshape(local_24,&aPrmt);
  local_30 = ((*(int *)((int)local_28 + 2) >> 0x10) + 8) * ((int)local_28[1] >> 0x10) + 0x11;
  puStack_1c = local_28;
  local_20 = (undefined4 *)allocmem(aDialog,local_30,0x20);
  puVar12 = local_20 + (uint)bVar16 * -2 + 1;
  puVar10 = local_28 + (uint)bVar16 * -2 + 1;
  *local_20 = *local_28;
  puVar13 = puVar12 + (uint)bVar16 * -2 + 1;
  puVar11 = puVar10 + (uint)bVar16 * -2 + 1;
  *puVar12 = *puVar10;
  *puVar13 = *puVar11;
  puVar13[(uint)bVar16 * -2 + 1] = puVar11[(uint)bVar16 * -2 + 1];
  *(undefined *)(puVar13 + (uint)bVar16 * -2 + 1 + (uint)bVar16 * -2 + 1) =
       *(undefined *)(puVar11 + (uint)bVar16 * -2 + 1 + (uint)bVar16 * -2 + 1);
  iVar8 = 0x140 - (*(int *)((int)local_28 + 2) >> 0x10) / 2;
  iVar14 = 0xf0 - ((int)local_28[1] >> 0x10) / 2;
  grabshape(local_20,iVar8,iVar14);
  drawshape2(local_28,iVar8,iVar14);
  settextpos(0xfa,0xf8);
  iVar8 = iVar8 + (*(int *)((int)local_28 + 6) >> 0x10);
  iVar14 = iVar14 + ((int)local_28[2] >> 0x10);
  *param_1 = '\0';
  text_entry_loop(param_1,8,100,iVar8,iVar14,0,0,1);
  strcat(param_1,(char *)&aNhl_c399b);
  drawshape2(puVar2,local_34,local_38);
  do {
    if ((*param_1 != '.') && (iVar3 = _dos_findfirst(param_1,0), iVar3 != 0)) {
      drawshape(puVar2,local_34,local_38);
      puVar10 = local_20;
      drawshape2(local_20,0x140 - (*(int *)((int)puStack_1c + 2) >> 0x10) / 2,
                 0xf0 - ((int)puStack_1c[1] >> 0x10) / 2);
      freemem(puVar10);
      freemem(puVar2);
      freemem(local_24);
LAB_00086609:
      uVar4 = 0;
LAB_00085d65:
      return CONCAT44(unaff_EDX,uVar4);
    }
    if (*param_1 != '.') {
      drawshape2(local_20,0x140 - (*(int *)((int)puStack_1c + 2) >> 0x10) / 2,
                 0xf0 - ((int)puStack_1c[1] >> 0x10) / 2);
      freemem(local_20);
      local_28 = (undefined4 *)locateshape(local_24,&aErr1);
      local_30 = ((*(int *)((int)local_28 + 2) >> 0x10) + 8) * ((int)local_28[1] >> 0x10) + 0x11;
      puStack_1c = local_28;
      local_20 = (undefined4 *)allocmem(aDialog,local_30,0x20);
      puVar12 = local_20 + (uint)bVar16 * -2 + 1;
      puVar10 = local_28 + (uint)bVar16 * -2 + 1;
      *local_20 = *local_28;
      puVar13 = puVar12 + (uint)bVar16 * -2 + 1;
      puVar11 = puVar10 + (uint)bVar16 * -2 + 1;
      *puVar12 = *puVar10;
      *puVar13 = *puVar11;
      puVar13[(uint)bVar16 * -2 + 1] = puVar11[(uint)bVar16 * -2 + 1];
      *(undefined *)(puVar13 + (uint)bVar16 * -2 + 1 + (uint)bVar16 * -2 + 1) =
           *(undefined *)(puVar11 + (uint)bVar16 * -2 + 1 + (uint)bVar16 * -2 + 1);
      iVar9 = 0x140 - (*(int *)((int)local_28 + 2) >> 0x10) / 2;
      iVar15 = 0xf0 - ((int)local_28[1] >> 0x10) / 2;
      grabshape(local_20,iVar9,iVar15);
      drawshape2_remap(local_28,iVar9,iVar15);
      iVar8 = *(int *)((int)local_28 + 6);
      iVar14 = local_28[2];
      for (iVar3 = 0; param_1[iVar3] != '.'; iVar3 = iVar3 + 1) {
      }
      param_1[iVar3] = '\0';
      settextpos(0xfa,0xf9);
      printstr2_at(param_1,iVar9 + (iVar8 >> 0x10),iVar15 + (iVar14 >> 0x10));
      event_queue_reset();
      setmousepos(0x181,0xfe);
      grabshape(puVar2,0x181,0xfe);
      pppuVar6 = pointer_shapes;
      drawshape2_remap(pointer_shapes,0x181,0xfe);
      local_3c = (undefined4 ***)0x181;
      local_34 = (undefined4 ***)0x181;
      local_2c = (undefined4 ***)0xfe;
      local_38 = (undefined4 ***)0xfe;
      uVar17 = event_queue_reset();
LAB_00086177:
      uVar4 = 0;
      do {
        uVar18 = event_queue_pop((int)uVar17,(int)(uVar17 >> 0x20),pppuVar6);
        uVar1 = CONCAT44((int)((ulonglong)uVar18 >> 0x20),uVar4);
        if ((int)uVar18 == 0) break;
        pppuVar6 = &local_2c;
        uVar17 = (*ui_poll_callback)();
        uVar4 = (undefined4)uVar17;
        uVar1 = uVar17;
      } while ((uVar17 & 2) == 0);
      uVar17 = CONCAT44((int)(uVar1 >> 0x20),local_2c);
      if ((uVar1 & 2) == 0) break;
      if ((0x108 < (int)local_2c) || ((int)local_2c < 0xf8)) goto LAB_000861b5;
      if ((0xda < (int)local_3c) && ((int)local_3c < 0x107)) {
        drawshape(puVar2,local_34,local_38);
        puVar10 = local_20;
        drawshape2(local_20,0x140 - (*(int *)((int)puStack_1c + 2) >> 0x10) / 2,
                   0xf0 - ((int)puStack_1c[1] >> 0x10) / 2);
        freemem(puVar10);
        freemem(puVar2);
        freemem(local_24);
        strcat(param_1,(char *)&aNhl_c399b);
        goto LAB_00086609;
      }
      if ((0x114 < (int)local_3c) && ((int)local_3c < 0x148)) {
        drawshape(puVar2,local_34,local_38);
        puVar10 = local_20;
        drawshape2(local_20,0x140 - (*(int *)((int)puStack_1c + 2) >> 0x10) / 2,
                   0xf0 - ((int)puStack_1c[1] >> 0x10) / 2);
        freemem(puVar10);
        freemem(puVar2);
        freemem(local_24);
        uVar4 = 1;
        goto LAB_00085d65;
      }
      if (((int)local_3c < 0x15e) || (0x1a1 < (int)local_3c)) {
        drawshape(puVar2,local_34,local_38);
        grabshape(puVar2,local_3c,local_2c);
        pppuVar6 = (undefined4 ***)local_2c;
        goto LAB_000861f2;
      }
      drawshape(puVar2,local_34,local_38);
      drawshape2(local_20,0x140 - (*(int *)((int)puStack_1c + 2) >> 0x10) / 2,
                 0xf0 - ((int)puStack_1c[1] >> 0x10) / 2);
      freemem(local_20);
      local_28 = (undefined4 *)locateshape(local_24,&aPrmt);
      local_30 = ((int)local_28[1] >> 0x10) * ((*(int *)((int)local_28 + 2) >> 0x10) + 8) + 0x11;
      puStack_1c = local_28;
      local_20 = (undefined4 *)allocmem(aDialog,local_30,0x20);
      puVar12 = local_20 + (uint)bVar16 * -2 + 1;
      puVar10 = local_28 + (uint)bVar16 * -2 + 1;
      *local_20 = *local_28;
      puVar13 = puVar12 + (uint)bVar16 * -2 + 1;
      puVar11 = puVar10 + (uint)bVar16 * -2 + 1;
      *puVar12 = *puVar10;
      *puVar13 = *puVar11;
      puVar13[(uint)bVar16 * -2 + 1] = puVar11[(uint)bVar16 * -2 + 1];
      *(undefined *)(puVar13 + (uint)bVar16 * -2 + 1 + (uint)bVar16 * -2 + 1) =
           *(undefined *)(puVar11 + (uint)bVar16 * -2 + 1 + (uint)bVar16 * -2 + 1);
      iVar8 = 0x140 - (*(int *)((int)local_28 + 2) >> 0x10) / 2;
      iVar14 = 0xf0 - ((int)local_28[1] >> 0x10) / 2;
      grabshape(local_20,iVar8,iVar14);
      drawshape2(local_28,iVar8,iVar14);
      iVar8 = iVar8 + (*(int *)((int)local_28 + 6) >> 0x10);
      iVar14 = iVar14 + ((int)local_28[2] >> 0x10);
      grabshape(puVar2,local_34,local_38);
    }
    for (iVar3 = 0; (param_1[iVar3] != '.' && (param_1[iVar3] != '\0')); iVar3 = iVar3 + 1) {
    }
    param_1[iVar3] = '\0';
    settextpos(0xfa,0xf8);
    text_entry_loop(param_1,8,100,iVar8,iVar14,0,0,1);
    strcat(param_1,(char *)&aNhl_c399b);
  } while( true );
  if ((local_3c != local_34) || (local_2c != local_38)) {
LAB_000861b5:
    drawshape(puVar2,local_34,local_38);
    grabshape(puVar2,local_3c,local_2c);
    pppuVar6 = (undefined4 ***)local_3c;
LAB_000861f2:
    drawshape_remap(pointer_shapes,local_3c,local_2c);
    uVar17 = CONCAT44(extraout_EDX,local_2c);
    local_34 = local_3c;
    local_38 = local_2c;
  }
  goto LAB_00086177;
}


// ================================================================================================
// menu_play_next_game @ 0x86627 [__watcall]
// ================================================================================================

undefined4 __watcall menu_play_next_game(void)

{
  __CHK(4);
  return 4;
}


// ================================================================================================
// menu_return_to_central @ 0x86637 [__watcall]
// ================================================================================================

undefined4 __watcall menu_return_to_central(void)

{
  __CHK(4);
  return 1;
}


// ================================================================================================
// playoff_highlights @ 0x86647 [__watcall]
// ================================================================================================

longlong __watcall playoff_highlights(undefined4 param_1,uint unaff_EDX)

{
  int iVar1;
  
  __CHK(8);
  save_settings(&settings_exhibition);
  apply_settings(&settings_playoff);
  dword_c53fb = 0;
  iVar1 = league_highlights_flow();
  if (iVar1 == 0) {
    apply_settings(&settings_exhibition);
    return CONCAT44(unaff_EDX,2);
  }
  apply_settings(&settings_exhibition);
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// stanley_cup_tree_screen @ 0x86696 [__watcall]
// ================================================================================================

undefined8 __watcall stanley_cup_tree_screen(undefined4 param_1,undefined4 unaff_EDX)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  undefined *puVar6;
  bool bVar7;
  undefined auStack_e0 [64];
  undefined auStack_a0 [44];
  undefined auStack_74 [32];
  char acStack_54 [16];
  undefined auStack_44 [4];
  undefined auStack_40 [4];
  undefined auStack_3c [4];
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined uStack_20;
  undefined uStack_1f;
  undefined uStack_1e;
  undefined auStack_1c [4];
  
  __CHK(0xf8);
  acStack_54[0] = '.';
  acStack_54[1] = '\0';
  acStack_54[2] = '\0';
  acStack_54[3] = '\0';
  acStack_54[4] = '\0';
  acStack_54[5] = '\0';
  acStack_54[6] = '\0';
  acStack_54[7] = '\0';
  acStack_54[8] = '\0';
  acStack_54[9] = '\0';
  acStack_54[10] = '\0';
  acStack_54[0xb] = '\0';
  acStack_54[0xc] = 0;
  local_34 = dword_c71cc;
  local_30 = dword_c71d0;
  local_28 = dword_c71d4;
  local_24 = dword_c71d8;
  local_2c = dword_c71dc;
  dword_c71cc = 0x41;
  dword_c71d0 = 0x40;
  dword_c71d4 = 0x42;
  dword_c71d8 = 0x40;
  dword_c71dc = 0x43;
  save_settings(&settings_exhibition);
  uVar1 = allocmem(aPalette_c39b3,0x300,0x20);
  getpalette(0,0x100,uVar1);
  fade_palette(1,uVar1,0x10);
  setdefaultscreen();
  if (dword_c65ac == 0) {
    puVar6 = install_path;
    if (byte_ed859 != '\x01') {
      puVar6 = (undefined *)0x0;
    }
    make_path(auStack_74,puVar6,aEmbscup_c39bb,0);
    uVar2 = loadshapes(auStack_74,0);
    setclip(0,0x280,0,0x1e0);
    uVar3 = locateshape(uVar2,&aBkgd_c39c3);
    drawshape_remap_home(uVar3);
    freemem(uVar2);
  }
  else {
    uVar2 = locateshape(dword_c65ac,&aBkgd_c39c3);
    drawshape2_home(uVar2);
  }
  puVar6 = install_path;
  if (byte_ed85a != '\x01') {
    puVar6 = (undefined *)0x0;
  }
  make_path(auStack_74,puVar6,aEmbpal_c39c8,0);
  uVar2 = loadshapes(auStack_74,0);
  iVar4 = locateshape(uVar2,&aPal_c39cf);
  fade_palette(0,iVar4 + 0x10,0x10);
  settextpos(0x40,0x41);
  set_dialog_colors(0x41,0x40,0x42,0x40,0x43);
  uStack_1e = 0x3f;
  uStack_1f = 0x3f;
  uStack_20 = 0x3f;
  getpalette(3,1,auStack_1c);
  setpalette(3,1,&uStack_20);
  iVar4 = text_entry_dialog(aPleaseEnterNewPlayOffNam,acStack_54,8,0x36,0,0,0,0,5);
  setpalette(3,1,auStack_1c);
  getmouse(auStack_44,auStack_3c,auStack_40);
  if ((iVar4 != 0x1b) && (acStack_54[0] != '\0')) {
    settings_playoff = 1;
    dword_c535e = 0xc;
    dword_c5362 = 0x15;
    word_c5366 = (word_c5366 >> 8 & 0x80) << 8 | 0x79ff;
    if ((input_devices & 2) == 0) {
      if ((input_devices & 4) == 0) {
        if ((input_devices & 8) == 0) {
          if ((input_devices & 1) == 0) {
            dword_c5372 = 0x10;
          }
          else {
            dword_c5372 = 1;
          }
        }
        else {
          dword_c5372 = 8;
        }
      }
      else {
        dword_c5372 = 4;
      }
    }
    else {
      dword_c5372 = 2;
    }
    if (dword_c5372 == 0x10) {
      dword_c536a = 0xffffffff;
    }
    else {
      dword_c536a = 0xc;
    }
    dword_c5376 = 0x10;
    dword_c536e = 0xfffffffe;
    bVar7 = false;
    dword_c537a = 0;
    dword_c537e = 1;
    apply_settings(&settings_playoff);
    strcat(acStack_54,(char *)&aPO_c39f3);
    iVar4 = _dos_findfirst(acStack_54,0x10,auStack_a0);
    if (iVar4 != 0) goto LAB_00086a8e;
    iVar4 = message_dialog(0xffffffff,0xffffffff,&off_d28eb,2,&unk_c7733,2,auStack_3c,auStack_40,
                           0xffffffff);
    if (iVar4 != 0) {
      delete_directory(acStack_54);
      bVar7 = false;
      goto LAB_00086a8e;
    }
  }
  freemem(uVar2);
  freemem(uVar1);
  bVar7 = true;
LAB_00086a8e:
  if (!bVar7) {
    strcpy(&league_dir,acStack_54);
    strcpy(&byte_dd750,acStack_54);
    strcat(&byte_dd750,aSDb);
    strcpy(&byte_dd710,&byte_dd750);
    iVar4 = mkdir(acStack_54,0xdd750);
    if (iVar4 == 0) {
      iVar4 = choose_db_or_org();
      if (-1 < iVar4) {
        db_file_sizes_kb(0,&unk_d2864,dword_dd770);
        make_path(auStack_74,&league_dir,aGameSet_c39fe,0);
        iVar4 = file_exists_rd(auStack_74);
        if (iVar4 != 0) {
          dword_d2884 = 0;
        }
        iVar4 = check_disk_space(0,&unk_d2864);
        if (iVar4 != 0) {
          sprintf(aXXXXKbytesOfFreeDiskSpac_d29cb,a4dKbytesOfFreeDiskSpace_c3a07,iVar4);
          message_dialog(0xffffffff,0xffffffff,&off_d29ef,3,0,0,auStack_3c,auStack_40,600);
          iVar4 = 1;
        }
      }
      if ((iVar4 == 0) && (iVar4 = locker_room_hub(), iVar4 != 3)) {
        getpalette(0,0x100,uVar1);
        fade_palette(1,uVar1,0x10);
        if (dword_c65ac == 0) {
          puVar6 = install_path;
          if (byte_ed859 != '\x01') {
            puVar6 = (undefined *)0x0;
          }
          make_path(auStack_74,puVar6,aEmbscup_c39bb,0);
          local_38 = loadshapes(auStack_74,0);
          uVar3 = locateshape(local_38,&aBkgd_c39c3);
          drawshape2_home(uVar3);
          freemem(local_38);
        }
        else {
          uVar3 = locateshape(dword_c65ac,&aBkgd_c39c3);
          drawshape2_home(uVar3);
        }
        iVar4 = locateshape(uVar2,&aPal_c39cf);
        fade_palette(0,iVar4 + 0x10,0x10);
        freemem(uVar2);
        freemem(uVar1);
        cup_tree_seed_bracket(auStack_e0);
        message_dialog(0xffffffff,0xffffffff,&off_d2983,2,0,0,auStack_3c,auStack_40,0);
        iVar4 = 0;
        do {
          iVar5 = copy_file((&off_c80d7)[iVar4],dword_dd770,&aDB,&byte_c8164,&league_dir);
          if (iVar5 != 0) {
            settimeout(400);
            delete_directory(acStack_54);
            bVar7 = true;
            waittimeout();
            break;
          }
          iVar4 = iVar4 + 1;
          bVar7 = false;
        } while (iVar4 < 7);
        if (!bVar7) {
          iVar4 = load_schedule_db(auStack_e0,acStack_54);
          if (iVar4 != 0) {
            settimeout(400);
            message_dialog(0xffffffff,0xffffffff,&off_d2950,4,0,0,auStack_3c,auStack_40,0);
            delete_directory(acStack_54);
            waittimeout();
            restore_dialog_background();
          }
          load_game_set(&settings_playoff);
          set_league_menu_titles();
          set_menu_mode(0);
          dword_ce583 = playoff_tree_screen;
          dword_ce5a3 = league_settings_screen;
          dword_ce5c3 = playoff_highlights;
          dword_d29fb = 0;
        }
        restore_dialog_background();
      }
      else {
        rmdir(acStack_54);
        freemem(uVar2);
        freemem(uVar1);
      }
    }
    else {
      message_dialog(0xffffffff,0xffffffff,&off_d2950,4,0,0,auStack_3c,auStack_40,400);
    }
  }
  uVar1 = allocmem(&aTemp_c3a26,0x300,0x20);
  getpalette(0,0x100,uVar1);
  fade_palette(1,uVar1,0x10);
  freemem(uVar1);
  apply_settings(&settings_exhibition);
  dword_c71cc = local_34;
  dword_c71d0 = local_30;
  dword_c71d4 = local_28;
  dword_c71d8 = local_24;
  dword_c71dc = local_2c;
  return CONCAT44(unaff_EDX,2);
}


// ================================================================================================
// cup_tree_seed_bracket @ 0x86e8b [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall cup_tree_seed_bracket(int param_1)

{
  short sVar1;
  short sVar2;
  int *piVar3;
  int iVar4;
  uint *puVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  
  __CHK(0x20);
  iVar6 = 0;
  do {
    *(undefined4 *)(param_1 + iVar6 * 4) = 0xfffffff0;
    iVar6 = iVar6 + 1;
  } while (iVar6 < 0x10);
  iVar6 = 0;
  do {
    sVar1 = randomrange(0x10);
    for (iVar4 = (int)sVar1; piVar3 = (int *)(iVar4 * 4 + param_1), *piVar3 != -0x10;
        iVar4 = (iVar4 + 1) % 0x10) {
    }
    *piVar3 = -3;
    sVar1 = randomrange(0x10);
    for (iVar4 = (int)sVar1; piVar3 = (int *)(iVar4 * 4 + param_1), *piVar3 != -0x10;
        iVar4 = (iVar4 + 1) % 0x10) {
    }
    *piVar3 = -0xc;
    iVar6 = iVar6 + 2;
  } while (iVar6 < 0x10);
  if (*(int *)(&unk_c5581 + user2_team._2_2_ * 4) == *(int *)(&unk_c5581 + _away_team_id * 4)) {
    iVar6 = 0;
    while( true ) {
      piVar3 = (int *)(iVar6 * 4 + param_1);
      if (-*piVar3 == *(int *)(&unk_c5581 + user2_team._2_2_ * 4)) break;
      iVar6 = iVar6 + 1;
    }
    *piVar3 = (int)user2_team._2_2_;
    iVar6 = 0xf;
    while( true ) {
      piVar3 = (int *)(iVar6 * 4 + param_1);
      if (-*piVar3 == *(int *)(&unk_c5581 + _away_team_id * 4)) break;
      iVar6 = iVar6 + -1;
    }
    *piVar3 = (int)_away_team_id;
  }
  else {
    sVar1 = randomrange(3);
    iVar4 = 0;
    iVar6 = -1;
    while (iVar6 != sVar1) {
      if (-*(int *)(param_1 + iVar4 * 4) == *(int *)(&unk_c5581 + user2_team._2_2_ * 4)) {
        iVar6 = iVar6 + 1;
      }
      iVar4 = iVar4 + 1;
    }
    iVar4 = iVar4 + -1;
    *(int *)(param_1 + iVar4 * 4) = (int)user2_team._2_2_;
    sVar2 = randomrange((int)(short)(4 - sVar1));
    iVar7 = 0;
    iVar6 = -1;
    while (iVar6 != (int)sVar1 + (int)sVar2) {
      if (-*(int *)(param_1 + iVar7 * 4) == *(int *)(&unk_c5581 + _away_team_id * 4)) {
        iVar6 = iVar6 + 1;
      }
      iVar7 = iVar7 + 1;
    }
    puVar5 = (uint *)((iVar7 + -1) * 4 + param_1);
    *puVar5 = (int)_away_team_id;
    if (iVar7 + -1 < iVar4) {
      uVar8 = *(uint *)(param_1 + iVar4 * 4) ^ *puVar5;
      *(uint *)(param_1 + iVar4 * 4) = uVar8;
      *puVar5 = uVar8 ^ *puVar5;
      *(uint *)(param_1 + iVar4 * 4) = *(uint *)(param_1 + iVar4 * 4) ^ *puVar5;
      iVar6 = 0;
      do {
        piVar3 = (int *)(iVar6 * 4 + param_1);
        if (-*piVar3 == *(int *)(&unk_c5581 + user2_team._2_2_ * 4)) {
          *piVar3 = -*(int *)(&unk_c5581 + _away_team_id * 4);
        }
        else if (-*piVar3 == *(int *)(&unk_c5581 + _away_team_id * 4)) {
          *piVar3 = -*(int *)(&unk_c5581 + user2_team._2_2_ * 4);
        }
        iVar6 = iVar6 + 1;
      } while (iVar6 < 0x10);
    }
  }
  cup_tree_pick_teams(param_1,3,0,0xc);
  cup_tree_pick_teams(param_1,0xc,0xc,0xe);
  return;
}


// ================================================================================================
// cup_tree_pick_teams @ 0x870b6 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall cup_tree_pick_teams(int param_1,uint unaff_EDX,int unaff_EBX,int unaff_ECX)

{
  short sVar1;
  uint uVar2;
  int *piVar3;
  int extraout_EDX;
  int iVar4;
  uint uVar5;
  int iVar6;
  int local_2c [8];
  
  __CHK(0x38);
  uVar5 = 0;
  if ((*(uint *)(&unk_c5519 + user2_team._2_2_ * 4) & unaff_EDX) != 0) {
    for (iVar4 = 0;
        (iVar4 < unaff_ECX && ((int)user2_team._2_2_ != (&unk_c55e9)[iVar4 + unaff_EBX]));
        iVar4 = iVar4 + 1) {
    }
    uVar5 = 1 << ((byte)iVar4 & 0x1f);
  }
  if ((unaff_EDX & *(uint *)(&unk_c5519 + _away_team_id * 4)) != 0) {
    for (iVar4 = 0; (iVar4 < unaff_ECX && ((int)_away_team_id != (&unk_c55e9)[iVar4 + unaff_EBX]));
        iVar4 = iVar4 + 1) {
    }
    uVar5 = uVar5 | 1 << ((byte)iVar4 & 0x1f);
  }
  iVar4 = 0;
  do {
    sVar1 = randomrange((int)(short)unaff_ECX);
    local_2c[iVar4] = (int)sVar1;
    while( true ) {
      iVar6 = local_2c[1];
      uVar2 = 1 << (*(byte *)(local_2c + iVar4) & 0x1f);
      if ((uVar5 & uVar2) == 0) break;
      sVar1 = randomrange((int)(short)unaff_ECX);
      *(int *)((int)local_2c + extraout_EDX) = (int)sVar1;
    }
    uVar5 = uVar5 | uVar2;
    iVar4 = iVar4 + 1;
  } while (iVar4 < 8);
  if (*(int *)(&unk_c5519 + (&unk_c55e9)[local_2c[0]] * 4) ==
      *(int *)(&unk_c5519 + (&unk_c55e9)[local_2c[1]] * 4)) {
    iVar4 = 2;
    while (*(int *)(&unk_c5519 + (&unk_c55e9)[local_2c[0]] * 4) ==
           *(int *)(&unk_c5519 + (&unk_c55e9)[local_2c[iVar4]] * 4)) {
      iVar4 = iVar4 + 1;
    }
    local_2c[1] = local_2c[iVar4];
    local_2c[iVar4] = iVar6;
  }
  iVar6 = 0;
  for (iVar4 = 0; iVar4 < 0x10; iVar4 = iVar4 + 1) {
    piVar3 = (int *)(iVar4 * 4 + param_1);
    if (-*piVar3 == unaff_EDX) {
      *piVar3 = (&unk_c55e9)[local_2c[iVar6] + unaff_EBX];
      iVar6 = iVar6 + 1;
    }
  }
  return;
}


// ================================================================================================
// load_schedule_db @ 0x8721f [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 __watcall load_schedule_db(undefined4 param_1,undefined4 unaff_EDX)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  undefined auStack_98 [64];
  undefined auStack_58 [64];
  undefined4 uStack_18;
  
  __CHK(0xa8);
  make_path(auStack_98,unaff_EDX,aScheduleDb_c3a2b,0);
  iVar1 = loadfile_data(auStack_98,0x20);
  iVar3 = iVar1 + 2;
  if (iVar3 == 0) {
    uVar2 = 1;
  }
  else {
    *(undefined4 *)(iVar1 + 0x8a) = 7;
    uVar2 = *(undefined4 *)(iVar1 + 0x8a);
    *(undefined4 *)(iVar1 + 0x86) = uVar2;
    *(undefined4 *)(iVar1 + 0x82) = uVar2;
    *(undefined4 *)(iVar1 + 0x7e) = uVar2;
    *(undefined4 *)(iVar1 + 0x7a) = uVar2;
    *(undefined4 *)(iVar1 + 0x76) = uVar2;
    *(undefined4 *)(iVar1 + 0x72) = uVar2;
    *(undefined4 *)(iVar1 + 0x6e) = uVar2;
    *(undefined4 *)(iVar1 + 0x6a) = uVar2;
    *(undefined4 *)(iVar1 + 0x66) = uVar2;
    *(undefined4 *)(iVar1 + 0x62) = uVar2;
    *(undefined4 *)(iVar1 + 0x5e) = uVar2;
    *(undefined4 *)(iVar1 + 0x5a) = uVar2;
    *(undefined4 *)(iVar1 + 0x56) = uVar2;
    *(undefined4 *)(iVar1 + 0x52) = uVar2;
    schedule_build_bracket(iVar3,param_1);
    if (*(int *)(&unk_c5581 + (short)user2_team._2_2_ * 4) !=
        *(int *)(&unk_c5581 + _away_team_id * 4)) {
      make_path(auStack_58,unaff_EDX,off_c80eb,&aDB);
      dword_d07bb = loadfile(auStack_58,0x20);
      dword_d07d3 = filesize(auStack_58);
      make_path(auStack_58,unaff_EDX,off_c80db,&aDB);
      dword_d07bf = loadfile(auStack_58,0x20);
      dword_d07d7 = filesize(auStack_58);
      make_path(auStack_58,unaff_EDX,off_c80d7,&aDB);
      dword_d07c7 = loadfile(auStack_58,0x20);
      dword_d07df = filesize(auStack_58);
      playoff_eliminate_round1(iVar3,(int)(short)user2_team._2_2_,(int)_away_team_id);
      schedule_advance_round1(iVar3);
      playoff_eliminate_round2(iVar3,(int)(short)user2_team._2_2_,(int)_away_team_id);
      schedule_advance_round2(iVar3);
      playoff_eliminate_round3(iVar3,(int)(short)user2_team._2_2_,(int)_away_team_id);
      schedule_advance_final(iVar3);
      make_path(auStack_58,unaff_EDX,off_c80eb,&aDB);
      savefile(auStack_58,dword_d07bb,dword_d07d3);
      if (dword_d07bb != 0) {
        freemem(dword_d07bb);
      }
      if (dword_d07bf != 0) {
        freemem(dword_d07bf);
      }
      if (dword_d07c7 != 0) {
        freemem(dword_d07c7);
      }
      dword_d07bb = 0;
      dword_d07bf = 0;
      dword_d07c7 = 0;
      dword_d07d3 = 0;
      dword_d07d7 = 0;
      dword_d07df = 0;
    }
    iVar4 = 0;
    for (iVar3 = iVar1 + 0x199a;
        (*(byte *)(iVar3 + 2) != user2_team._2_2_ ||
        (CONCAT11((char)(user2_team._2_2_ >> 8),*(undefined *)(iVar3 + 3)) != _away_team_id));
        iVar3 = iVar3 + 0x2a) {
      iVar4 = iVar4 + 7;
    }
    *(int *)(iVar1 + 0x42) = iVar4;
    *(int *)(iVar1 + 0x46) = iVar4 / 7;
    uVar2 = filesize(auStack_98);
    iVar3 = file_open_trunc(auStack_98,&uStack_18,7,uVar2);
    if (iVar3 == 0) {
      uVar2 = file_write(uStack_18,iVar1,0);
      file_close(&uStack_18);
    }
    else {
      uVar2 = 1;
    }
    freemem(iVar1);
  }
  return uVar2;
}


// ================================================================================================
// playoff_set_series_b @ 0x87520 [__watcall]
// ================================================================================================

void __watcall playoff_set_series_b(int param_1,int unaff_EDX,int unaff_EBX)

{
  undefined uVar1;
  undefined uVar2;
  int iVar3;
  
  __CHK(8);
  uVar1 = (undefined)unaff_EDX;
  uVar2 = (undefined)unaff_EBX;
  if ((*(uint *)(&unk_c5519 + unaff_EDX * 4) | *(uint *)(&unk_c5519 + unaff_EBX * 4)) == 3) {
    *(undefined *)(param_1 + 0x26) = uVar1;
    *(undefined *)(param_1 + 0x20) = uVar1;
    *(undefined *)(param_1 + 0x1b) = uVar1;
    *(undefined *)(param_1 + 0x15) = uVar1;
    *(undefined *)(param_1 + 0xf) = uVar1;
    *(undefined *)(param_1 + 8) = uVar1;
    *(undefined *)(param_1 + 2) = uVar1;
    *(undefined *)(param_1 + 0x27) = uVar2;
    *(undefined *)(param_1 + 0x21) = uVar2;
    *(undefined *)(param_1 + 0x1a) = uVar2;
  }
  else {
    *(undefined *)(param_1 + 0x26) = uVar1;
    *(undefined *)(param_1 + 0x21) = uVar1;
    *(undefined *)(param_1 + 0x1a) = uVar1;
    *(undefined *)(param_1 + 0x15) = uVar1;
    *(undefined *)(param_1 + 0xf) = uVar1;
    *(undefined *)(param_1 + 8) = uVar1;
    *(undefined *)(param_1 + 2) = uVar1;
    *(undefined *)(param_1 + 0x27) = uVar2;
    *(undefined *)(param_1 + 0x20) = uVar2;
    *(undefined *)(param_1 + 0x1b) = uVar2;
  }
  *(undefined *)(param_1 + 0x14) = uVar2;
  *(undefined *)(param_1 + 0xe) = uVar2;
  *(undefined *)(param_1 + 9) = uVar2;
  *(undefined *)(param_1 + 3) = uVar2;
  iVar3 = 0;
  do {
    *(undefined *)(param_1 + 4 + iVar3 * 6) = 0xff;
    *(undefined *)(param_1 + 5 + iVar3 * 6) = 0xff;
    iVar3 = iVar3 + 1;
  } while (iVar3 < 7);
  return;
}


// ================================================================================================
// schedule_build_bracket @ 0x875a3 [__watcall]
// ================================================================================================

void __watcall schedule_build_bracket(int param_1,int unaff_EDX)

{
  int iVar1;
  undefined *puVar2;
  byte bVar3;
  int iVar4;
  int iVar5;
  char *pcVar6;
  int local_38 [5];
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 uStackY_18;
  
  __CHK(0x3c);
  iVar4 = 0;
  do {
    *(undefined4 *)(param_1 + iVar4 * 4) = *(undefined4 *)(unaff_EDX + iVar4 * 4);
    iVar4 = iVar4 + 1;
  } while (iVar4 < 0x10);
  iVar4 = 0;
  do {
    pcVar6 = (char *)(iVar4 * 6 + param_1 + 0x1998);
    *pcVar6 = '\x04';
    bVar3 = (char)(iVar4 % 7) * '\x02' + 0x11;
    pcVar6[1] = bVar3;
    if (0x1e < bVar3) {
      *pcVar6 = *pcVar6 + '\x01';
      pcVar6[1] = pcVar6[1] + -0x1e;
    }
    iVar4 = iVar4 + 1;
  } while (iVar4 < 0x1c);
  iVar4 = 0;
  do {
    pcVar6 = (char *)(iVar4 * 6 + param_1 + 0x1a40);
    *pcVar6 = '\x04';
    uStackY_18 = 7;
    bVar3 = (char)(iVar4 % 7) * '\x02' + 0x10;
    pcVar6[1] = bVar3;
    if (0x1e < bVar3) {
      *pcVar6 = *pcVar6 + '\x01';
      pcVar6[1] = pcVar6[1] + -0x1e;
    }
    iVar4 = iVar4 + 1;
  } while (iVar4 < 0x1c);
  iVar4 = 0;
  for (iVar5 = 0; iVar5 < 0x10; iVar5 = iVar5 + 1) {
    iVar1 = *(int *)(iVar5 * 4 + unaff_EDX);
    if (*(int *)(&unk_c5581 + iVar1 * 4) == 3) {
      local_38[iVar4] = iVar1;
      iVar4 = iVar4 + 1;
    }
  }
  playoff_set_series_b(param_1 + 0x1998,local_38[0],local_1c);
  playoff_set_series_b(param_1 + 0x19c2,local_38[1],local_20);
  playoff_set_series_b(param_1 + 0x19ec,local_38[2],local_24);
  playoff_set_series_b(param_1 + 0x1a16,local_38[3]);
  iVar4 = 0;
  for (iVar5 = 0; iVar5 < 0x10; iVar5 = iVar5 + 1) {
    iVar1 = *(int *)(iVar5 * 4 + unaff_EDX);
    if (*(int *)(&unk_c5581 + iVar1 * 4) == 0xc) {
      local_38[iVar4] = iVar1;
      iVar4 = iVar4 + 1;
    }
  }
  playoff_set_series_b(param_1 + 0x1a40,local_38[0],local_1c);
  playoff_set_series_b(param_1 + 0x1a6a,local_38[1],local_20);
  playoff_set_series_b(param_1 + 0x1a94,local_38[2],local_24);
  playoff_set_series_b(param_1 + 0x1abe,local_38[3]);
  puVar2 = (undefined *)(param_1 + 0x1ae8);
  iVar4 = 0;
  do {
    puVar2[1] = 0;
    *puVar2 = puVar2[1];
    puVar2[3] = 0xff;
    puVar2[2] = puVar2[3];
    puVar2[5] = 0xff;
    puVar2[4] = puVar2[5];
    iVar4 = iVar4 + 1;
    puVar2 = puVar2 + 6;
  } while (iVar4 < 0x31);
  return;
}


// ================================================================================================
// series_winner @ 0x87760 [__watcall]
// ================================================================================================

uint __watcall series_winner(int param_1,uint unaff_EDX)

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
LAB_000877ba:
        uVar3 = uVar3 + 1;
        uVar4 = uVar5;
      }
    }
    else if (*(byte *)(param_1 + 5) < *(byte *)(param_1 + 4)) goto LAB_000877ba;
    param_1 = param_1 + 6;
    uVar5 = uVar4;
  } while( true );
}


// ================================================================================================
// series_wins @ 0x877e9 [__watcall]
// ================================================================================================

undefined4 __watcall
series_wins(int param_1,int *unaff_EDX,int *unaff_EBX,uint *unaff_ECX,uint *param_5)

{
  int iVar1;
  
  __CHK(0x10);
  *unaff_ECX = (uint)*(byte *)(param_1 + 2);
  *param_5 = (uint)*(byte *)(param_1 + 3);
  *unaff_EBX = 0;
  *unaff_EDX = *unaff_EBX;
  do {
    if ((3 < *unaff_EDX) || (iVar1 = *unaff_EBX, 3 < iVar1)) {
      return 0;
    }
    if (*(char *)(param_1 + 4) == -1) {
      return 0xffffffff;
    }
    if ((uint)*(byte *)(param_1 + 2) == *unaff_ECX) {
      if (*(byte *)(param_1 + 5) < *(byte *)(param_1 + 4)) {
LAB_00087848:
        *unaff_EDX = *unaff_EDX + 1;
      }
      else {
        *unaff_EBX = iVar1 + 1;
      }
    }
    else {
      if (*(byte *)(param_1 + 4) <= *(byte *)(param_1 + 5)) goto LAB_00087848;
      *unaff_EBX = iVar1 + 1;
    }
    param_1 = param_1 + 6;
  } while( true );
}


// ================================================================================================
// schedule_advance_round1 @ 0x87863 [__watcall]
// ================================================================================================

void __watcall schedule_advance_round1(int param_1)

{
  byte bVar1;
  uint uVar2;
  byte *pbVar3;
  byte bVar4;
  byte bVar5;
  int iVar6;
  int iVar7;
  uint local_48 [8];
  uint local_28 [4];
  
  __CHK(0x4c);
  pbVar3 = (byte *)(param_1 + 0x19bc);
  iVar6 = 0;
  do {
    if (((((pbVar3[4] != 0xff) || (pbVar3[0x2e] != 0xff)) || (pbVar3[0x58] != 0xff)) ||
        ((pbVar3[0x82] != 0xff || (pbVar3[0xac] != 0xff)))) ||
       ((pbVar3[0xd6] != 0xff || ((pbVar3[0x100] != 0xff || (pbVar3[0x12a] != 0xff)))))) break;
    iVar6 = iVar6 + 1;
    pbVar3 = pbVar3 + -6;
  } while (iVar6 < 6);
  bVar1 = *pbVar3;
  local_28[0] = (uint)bVar1;
  bVar5 = pbVar3[1];
  pbVar3 = (byte *)(param_1 + 0x1ae8);
  iVar6 = 0;
  do {
    *pbVar3 = bVar1;
    bVar4 = (char)((longlong)iVar6 % 7) * '\x02' + bVar5 + 3;
    pbVar3[1] = bVar4;
    if (0x1e < bVar4) {
      *pbVar3 = *pbVar3 + 1;
      pbVar3[1] = pbVar3[1] - 0x1e;
    }
    iVar6 = iVar6 + 1;
    pbVar3 = pbVar3 + 6;
  } while (iVar6 < 0xe);
  local_28[1] = bVar5 + 2;
  pbVar3 = (byte *)(param_1 + 0x1b3c);
  iVar6 = 0;
  do {
    *pbVar3 = bVar1;
    bVar5 = (char)((longlong)iVar6 % 7) * '\x02' + (char)local_28[1];
    pbVar3[1] = bVar5;
    if (0x1e < bVar5) {
      *pbVar3 = *pbVar3 + 1;
      pbVar3[1] = pbVar3[1] - 0x1e;
    }
    iVar6 = iVar6 + 1;
    pbVar3 = pbVar3 + 6;
  } while (iVar6 < 0xe);
  _memset_dwords(local_48,0xffffffff,iVar6,8);
  local_28[0] = series_winner(param_1 + 0x1998,*(undefined4 *)(param_1 + 0x50));
  uVar2 = local_28[0];
  if (local_28[0] == *(byte *)(param_1 + 0x199a)) {
    local_48[0] = (uint)*(byte *)(param_1 + 0x199a);
    uVar2 = local_48[7];
  }
  local_48[7] = uVar2;
  local_28[1] = series_winner(param_1 + 0x19c2,*(undefined4 *)(param_1 + 0x54));
  uVar2 = local_28[1];
  if (local_28[1] == *(byte *)(param_1 + 0x19c4)) {
    local_48[1] = (uint)*(byte *)(param_1 + 0x19c4);
    uVar2 = local_48[6];
  }
  local_48[6] = uVar2;
  local_28[2] = series_winner(param_1 + 0x19ec,*(undefined4 *)(param_1 + 0x58));
  uVar2 = local_28[2];
  if (local_28[2] == *(byte *)(param_1 + 0x19ee)) {
    local_48[2] = (uint)*(byte *)(param_1 + 0x19ee);
    uVar2 = local_48[5];
  }
  local_48[5] = uVar2;
  local_28[3] = series_winner(param_1 + 0x1a16,*(undefined4 *)(param_1 + 0x5c));
  if (local_28[3] == *(byte *)(param_1 + 0x1a18)) {
    local_48[3] = (uint)*(byte *)(param_1 + 0x1a18);
  }
  else {
    local_48[4] = local_28[3];
  }
  iVar6 = 0;
  for (iVar7 = 0; iVar7 < 8; iVar7 = iVar7 + 1) {
    uVar2 = local_48[iVar7];
    if ((-1 < (int)uVar2) && ((int)uVar2 < 0x1a)) {
      local_28[iVar6] = uVar2;
      iVar6 = iVar6 + 1;
    }
  }
  playoff_set_series_b(param_1 + 0x1ae8,local_28[0],local_28[3]);
  uVar2 = local_28[2];
  playoff_set_series_b(param_1 + 0x1b12,local_28[1]);
  _memset_dwords(local_48,0xffffffff,uVar2,8);
  local_28[0] = series_winner(param_1 + 0x1a40,*(undefined4 *)(param_1 + 0x60));
  uVar2 = local_28[0];
  if (local_28[0] == *(byte *)(param_1 + 0x1a42)) {
    local_48[0] = (uint)*(byte *)(param_1 + 0x1a42);
    uVar2 = local_48[7];
  }
  local_48[7] = uVar2;
  local_28[1] = series_winner(param_1 + 0x1a6a,*(undefined4 *)(param_1 + 100));
  uVar2 = local_28[1];
  if (local_28[1] == *(byte *)(param_1 + 0x1a6c)) {
    local_48[1] = (uint)*(byte *)(param_1 + 0x1a6c);
    uVar2 = local_48[6];
  }
  local_48[6] = uVar2;
  local_28[2] = series_winner(param_1 + 0x1a94,*(undefined4 *)(param_1 + 0x68));
  uVar2 = local_28[2];
  if (local_28[2] == *(byte *)(param_1 + 0x1a96)) {
    local_48[2] = (uint)*(byte *)(param_1 + 0x1a96);
    uVar2 = local_48[5];
  }
  local_48[5] = uVar2;
  local_28[3] = series_winner(param_1 + 0x1abe,*(undefined4 *)(param_1 + 0x6c));
  if (local_28[3] == *(byte *)(param_1 + 0x1ac0)) {
    local_48[3] = (uint)*(byte *)(param_1 + 0x1ac0);
  }
  else {
    local_48[4] = local_28[3];
  }
  iVar6 = 0;
  for (iVar7 = 0; iVar7 < 8; iVar7 = iVar7 + 1) {
    uVar2 = local_48[iVar7];
    if ((-1 < (int)uVar2) && ((int)uVar2 < 0x1a)) {
      local_28[iVar6] = uVar2;
      iVar6 = iVar6 + 1;
    }
  }
  playoff_set_series_b(param_1 + 0x1b3c,local_28[0],local_28[3]);
  playoff_set_series_b(param_1 + 0x1b66,local_28[1],local_28[2]);
  return;
}


// ================================================================================================
// schedule_advance_round2 @ 0x87b33 [__watcall]
// ================================================================================================

void __watcall schedule_advance_round2(int *param_1)

{
  char cVar1;
  char cVar2;
  byte bVar3;
  int iVar4;
  int *piVar5;
  char *pcVar6;
  int iVar7;
  int iVar8;
  
  __CHK(0x20);
  piVar5 = param_1 + 0x6c3;
  iVar8 = 0;
  do {
    if ((((*(char *)(piVar5 + 1) != -1) || (*(char *)((int)piVar5 + 0x2e) != -1)) ||
        (*(char *)(piVar5 + 0x16) != -1)) || (*(char *)((int)piVar5 + 0x82) != -1)) break;
    iVar8 = iVar8 + 1;
    piVar5 = (int *)((int)piVar5 + -6);
  } while (iVar8 < 3);
  cVar1 = *(char *)piVar5;
  cVar2 = *(char *)((int)piVar5 + 1);
  piVar5 = param_1 + 0x6e4;
  iVar8 = 0;
  do {
    *(char *)piVar5 = cVar1;
    bVar3 = (char)(iVar8 % 7) * '\x02' + cVar2 + '\x03';
    *(byte *)((int)piVar5 + 1) = bVar3;
    if (0x1f < bVar3) {
      *(char *)piVar5 = *(char *)piVar5 + '\x01';
      *(char *)((int)piVar5 + 1) = *(char *)((int)piVar5 + 1) + -0x1f;
    }
    iVar8 = iVar8 + 1;
    piVar5 = (int *)((int)piVar5 + 6);
  } while (iVar8 < 7);
  pcVar6 = (char *)((int)param_1 + 0x1bba);
  iVar8 = 0;
  do {
    *pcVar6 = cVar1;
    bVar3 = (char)(iVar8 % 7) * '\x02' + cVar2 + '\x02';
    pcVar6[1] = bVar3;
    if (0x1f < bVar3) {
      *pcVar6 = *pcVar6 + '\x01';
      pcVar6[1] = pcVar6[1] + -0x1f;
    }
    iVar8 = iVar8 + 1;
    pcVar6 = pcVar6 + 6;
  } while (iVar8 < 7);
  iVar8 = series_winner(param_1 + 0x6ba,param_1[0x1c]);
  iVar4 = series_winner((int)param_1 + 0x1b12,param_1[0x1d]);
  for (piVar5 = param_1; (*piVar5 != iVar8 && (iVar4 != *piVar5)); piVar5 = piVar5 + 1) {
  }
  iVar7 = iVar4;
  if (*piVar5 == iVar8) {
    iVar7 = iVar8;
    iVar8 = iVar4;
  }
  playoff_set_series_b(param_1 + 0x6e4,iVar7,iVar8);
  iVar8 = series_winner(param_1 + 0x6cf,param_1[0x1e]);
  iVar4 = series_winner((int)param_1 + 0x1b66,param_1[0x1f]);
  for (piVar5 = param_1; (*piVar5 != iVar8 && (iVar4 != *piVar5)); piVar5 = piVar5 + 1) {
  }
  iVar7 = iVar4;
  if (*piVar5 == iVar8) {
    iVar7 = iVar8;
    iVar8 = iVar4;
  }
  playoff_set_series_b((int)param_1 + 0x1bba,iVar7,iVar8);
  return;
}


// ================================================================================================
// schedule_advance_final @ 0x87c9e [__watcall]
// ================================================================================================

void __watcall schedule_advance_final(int *param_1)

{
  char cVar1;
  char cVar2;
  int iVar3;
  int *piVar4;
  byte bVar5;
  int iVar6;
  int iVar7;
  
  __CHK(0x20);
  piVar4 = param_1 + 0x6ed;
  iVar7 = 0;
  do {
    if ((*(char *)(piVar4 + 1) != -1) || (*(char *)((int)piVar4 + 0x2e) != -1)) break;
    iVar7 = iVar7 + 1;
    piVar4 = (int *)((int)piVar4 + -6);
  } while (iVar7 < 3);
  cVar1 = *(char *)piVar4;
  cVar2 = *(char *)((int)piVar4 + 1);
  piVar4 = param_1 + 0x6f9;
  iVar7 = 0;
  do {
    *(char *)piVar4 = cVar1;
    bVar5 = (char)((longlong)iVar7 % 7) * '\x02' + cVar2 + '\x03';
    *(byte *)((int)piVar4 + 1) = bVar5;
    if (0x1f < bVar5) {
      *(char *)piVar4 = *(char *)piVar4 + '\x01';
      *(char *)((int)piVar4 + 1) = *(char *)((int)piVar4 + 1) + -0x1f;
    }
    iVar7 = iVar7 + 1;
    piVar4 = (int *)((int)piVar4 + 6);
  } while (iVar7 < 7);
  iVar7 = series_winner(param_1 + 0x6e4,param_1[0x20]);
  iVar3 = series_winner((int)param_1 + 0x1bba,param_1[0x21]);
  for (piVar4 = param_1; (*piVar4 != iVar7 && (iVar3 != *piVar4)); piVar4 = piVar4 + 1) {
  }
  iVar6 = iVar3;
  if (*piVar4 == iVar7) {
    iVar6 = iVar7;
    iVar7 = iVar3;
  }
  playoff_set_series_b(param_1 + 0x6f9,iVar6,iVar7);
  return;
}


// ================================================================================================
// playoff_update_team_db_e @ 0x87d5a [__watcall]
// ================================================================================================

void __watcall playoff_update_team_db_e(int param_1)

{
  int iVar1;
  undefined *puVar2;
  int iVar4;
  int iVar5;
  undefined auStack_60 [64];
  undefined local_20 [4];
  undefined local_1c [4];
  undefined4 *puVar3;
  
  __CHK(0x70);
  puVar2 = auStack_60;
  make_path(auStack_60,&league_dir,off_c80e7,&aDB);
  iVar1 = file_open_rw(auStack_60,local_1c);
  if (iVar1 != 0) {
    fatalerror(&aE1);
  }
  make_path(auStack_60,&league_dir,off_c80e3,&aDB);
  iVar1 = file_open_read(auStack_60,local_20);
  if (iVar1 != 0) {
    fatalerror(&aE2_c3a3a);
  }
  iVar5 = 0;
  iVar1 = 0;
  do {
    if (3 < iVar5) {
      *(undefined4 *)(puVar2 + -4) = 0x87e66;
      file_close(puVar2 + 0x44);
      *(undefined4 *)(puVar2 + -4) = 0x87e6f;
      file_close(puVar2 + 0x40);
      return;
    }
    if (iVar1 < iVar5) {
      *(undefined4 *)(puVar2 + -4) = 2;
      *(undefined4 *)(puVar2 + -8) = *(undefined4 *)(puVar2 + 0x40);
      *(undefined4 *)(puVar2 + -0xc) = *(undefined4 *)(puVar2 + 0x44);
    }
    else if ((uint)*(byte *)(param_1 + 2) == *(uint *)(puVar2 + 0x48)) {
      *(undefined4 *)(puVar2 + -4) = 0;
      *(undefined4 *)(puVar2 + -8) = *(undefined4 *)(puVar2 + 0x40);
      *(undefined4 *)(puVar2 + -0xc) = *(undefined4 *)(puVar2 + 0x44);
    }
    else {
      *(undefined4 *)(puVar2 + -4) = 1;
      *(undefined4 *)(puVar2 + -8) = *(undefined4 *)(puVar2 + 0x40);
      *(undefined4 *)(puVar2 + -0xc) = *(undefined4 *)(puVar2 + 0x44);
    }
    puVar3 = (undefined4 *)(puVar2 + -0x10);
    puVar2 = puVar2 + -0x10;
    *puVar3 = 0x87e2e;
    playoff_setup_screen(&league_dir,&aDB,0x44c,param_1);
    iVar4 = iVar1 + 1;
    if ((uint)*(byte *)(param_1 + 2) == *(uint *)(puVar2 + 0x48)) {
      if (*(byte *)(param_1 + 5) < *(byte *)(param_1 + 4)) {
LAB_00087e47:
        iVar4 = iVar1;
        iVar5 = iVar5 + 1;
      }
    }
    else if (*(byte *)(param_1 + 4) < *(byte *)(param_1 + 5)) goto LAB_00087e47;
    param_1 = param_1 + 6;
    iVar1 = iVar4;
  } while( true );
}


// ================================================================================================
// playoff_update_team_db_f @ 0x87e77 [__watcall]
// ================================================================================================

void __watcall playoff_update_team_db_f(int param_1)

{
  int iVar1;
  undefined *puVar2;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  undefined auStack_64 [64];
  undefined local_24 [4];
  undefined local_20 [4];
  uint local_1c;
  undefined4 *puVar3;
  
  __CHK(0x74);
  puVar2 = auStack_64;
  local_1c = (uint)*(byte *)(param_1 + 2);
  make_path(auStack_64,&league_dir,off_c80e7,&aDB);
  iVar1 = file_open_rw(auStack_64,local_20);
  if (iVar1 != 0) {
    fatalerror(&aF1_c3a3d);
  }
  make_path(auStack_64,&league_dir,off_c80e3,&aDB);
  iVar1 = file_open_read(auStack_64,local_24);
  if (iVar1 != 0) {
    fatalerror(&aF2);
  }
  uVar6 = 0;
  uVar5 = 0;
  do {
    if ((*(uint *)(puVar2 + 0x4c) <= uVar5) || (*(uint *)(puVar2 + 0x4c) <= uVar6)) {
      *(undefined4 *)(puVar2 + -4) = 0x87f74;
      file_close(puVar2 + 0x44);
      *(undefined4 *)(puVar2 + -4) = 0x87f7d;
      file_close(puVar2 + 0x40);
      return;
    }
    if (*(char *)(param_1 + 4) == -1) {
      *(undefined4 *)(puVar2 + -4) = 2;
      *(undefined4 *)(puVar2 + -8) = *(undefined4 *)(puVar2 + 0x40);
      *(undefined4 *)(puVar2 + -0xc) = *(undefined4 *)(puVar2 + 0x44);
      puVar3 = (undefined4 *)(puVar2 + -0x10);
      puVar2 = puVar2 + -0x10;
      *puVar3 = 0x87f35;
      playoff_setup_screen(&league_dir,&aDB,0x44c,param_1);
    }
    uVar4 = uVar5 + 1;
    if ((uint)*(byte *)(param_1 + 2) == *(uint *)(puVar2 + 0x48)) {
      if (*(byte *)(param_1 + 4) <= *(byte *)(param_1 + 5)) {
LAB_00087f4e:
        uVar4 = uVar5;
        uVar6 = uVar6 + 1;
      }
    }
    else if (*(byte *)(param_1 + 5) < *(byte *)(param_1 + 4)) goto LAB_00087f4e;
    param_1 = param_1 + 6;
    uVar5 = uVar4;
  } while( true );
}


// ================================================================================================
// playoff_eliminate_round1 @ 0x87f85 [__watcall]
// ================================================================================================

void __watcall playoff_eliminate_round1(int param_1,uint unaff_EDX,uint unaff_EBX)

{
  uint uVar1;
  int iVar2;
  
  __CHK(0x10);
  param_1 = param_1 + 0x1998;
  iVar2 = 0;
  do {
    uVar1 = unaff_EDX;
    if ((((*(byte *)(param_1 + 2) == unaff_EDX) || (*(byte *)(param_1 + 3) == unaff_EDX)) ||
        (uVar1 = unaff_EBX, *(byte *)(param_1 + 2) == unaff_EBX)) ||
       (*(byte *)(param_1 + 3) == unaff_EBX)) {
      playoff_update_team_db_e(param_1,uVar1);
    }
    else {
      playoff_update_team_db_f(param_1,7);
    }
    iVar2 = iVar2 + 1;
    param_1 = param_1 + 0x2a;
  } while (iVar2 < 8);
  return;
}


// ================================================================================================
// playoff_eliminate_round2 @ 0x87fe0 [__watcall]
// ================================================================================================

void __watcall playoff_eliminate_round2(int param_1,uint unaff_EDX,uint unaff_EBX)

{
  uint uVar1;
  int iVar2;
  
  __CHK(0x10);
  param_1 = param_1 + 0x1ae8;
  iVar2 = 0;
  do {
    uVar1 = unaff_EDX;
    if ((((*(byte *)(param_1 + 2) == unaff_EDX) || (*(byte *)(param_1 + 3) == unaff_EDX)) ||
        (uVar1 = unaff_EBX, *(byte *)(param_1 + 2) == unaff_EBX)) ||
       (*(byte *)(param_1 + 3) == unaff_EBX)) {
      playoff_update_team_db_e(param_1,uVar1);
    }
    else {
      playoff_update_team_db_f(param_1,7);
    }
    iVar2 = iVar2 + 1;
    param_1 = param_1 + 0x2a;
  } while (iVar2 < 4);
  return;
}


// ================================================================================================
// playoff_eliminate_round3 @ 0x8803b [__watcall]
// ================================================================================================

void __watcall playoff_eliminate_round3(int param_1,uint unaff_EDX,uint unaff_EBX)

{
  uint uVar1;
  int iVar2;
  
  __CHK(0x10);
  param_1 = param_1 + 0x1b90;
  iVar2 = 0;
  do {
    uVar1 = unaff_EDX;
    if ((((*(byte *)(param_1 + 2) == unaff_EDX) || (*(byte *)(param_1 + 3) == unaff_EDX)) ||
        (uVar1 = unaff_EBX, *(byte *)(param_1 + 2) == unaff_EBX)) ||
       (*(byte *)(param_1 + 3) == unaff_EBX)) {
      playoff_update_team_db_e(param_1,uVar1);
    }
    else {
      playoff_update_team_db_f(param_1,7);
    }
    iVar2 = iVar2 + 1;
    param_1 = param_1 + 0x2a;
  } while (iVar2 < 2);
  return;
}


// ================================================================================================
// playoff_results_screen @ 0x88096 [__watcall]
// ================================================================================================

void __watcall playoff_results_screen(int param_1,int unaff_EDX)

{
  int iVar1;
  undefined uVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  undefined *puVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  undefined auStack_84 [64];
  undefined auStack_44 [32];
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  int iStack_18;
  
  __CHK(0x9c);
  local_20 = 0xa0;
  local_24 = 100;
  dword_c6d26 = 0;
  playoff_bracket_screen();
  puVar6 = install_path;
  if (byte_ed85a != '\x01') {
    puVar6 = (undefined *)0x0;
  }
  make_path(auStack_44,puVar6,aEmbpal_c39c8);
  uVar3 = loadshapes(auStack_44,0);
  local_1c = uVar3;
  iStack_18 = locateshape(uVar3,&aPal_c39cf);
  iStack_18 = iStack_18 + 0x10;
  if (param_1 == 0) {
    draw_menu_items(&unk_cf90f,3,0x40,0x41,0x42);
    fade_palette(0,iStack_18,0x10);
    goto LAB_0008751a;
  }
  set_dialog_colors(0x41,0x40,0x42,0x40,0);
  make_path(auStack_84,&league_dir,off_c80eb,&aDB);
  dword_d07bb = loadfile(auStack_84,0x20);
  dword_d07d3 = filesize(auStack_84);
  make_path(auStack_84,&league_dir,off_c80db,&aDB);
  dword_d07bf = loadfile(auStack_84,0x20);
  dword_d07d7 = filesize(auStack_84);
  make_path(auStack_84,&league_dir,off_c80d7,&aDB);
  dword_d07c7 = loadfile(auStack_84,0x20);
  dword_d07df = filesize(auStack_84);
  if (param_1 == 1) {
    fade_palette(0,iStack_18,0x10);
    iVar4 = message_dialog(0xffffffff,0xffffffff,&off_d2b0c,4,&unk_d2b38,2,&local_20,&local_24,
                           0xffffffff);
    if (iVar4 != 0) {
      message_dialog(0xffffffff,0xffffffff,&off_d2b34,1,0,0,&local_20,&local_24,0);
      uVar5 = *(uint *)(unaff_EDX + 0x44);
      if (uVar5 < 8) {
        uVar5 = (uint)(option_flags << 0x11) >> 0x1d;
        *(uint *)(unaff_EDX + 0x7c) = uVar5;
        *(uint *)(unaff_EDX + 0x78) = uVar5;
        *(uint *)(unaff_EDX + 0x74) = uVar5;
        *(uint *)(unaff_EDX + 0x70) = uVar5;
        iVar4 = unaff_EDX + 0x1ae8;
        iVar9 = 8;
        do {
          playoff_update_team_db_f(iVar4,(uint)(option_flags << 0x11) >> 0x1d);
          for (iVar7 = 0; (iVar7 < 7 && (*(char *)(iVar4 + 4 + iVar7 * 6) != -1)); iVar7 = iVar7 + 1
              ) {
          }
          iVar8 = ((uint)(option_flags << 0x11) >> 0x1e) + 1;
          iVar7 = iVar7 - iVar8;
          for (; iVar8 < 4; iVar8 = iVar8 + 1) {
            iVar1 = iVar7 + iVar8;
            *(undefined *)(iVar4 + 5 + iVar1 * 6) = 0xff;
            uVar2 = *(undefined *)(iVar4 + 5 + iVar1 * 6);
            *(undefined *)(iVar4 + 4 + iVar1 * 6) = uVar2;
            *(undefined *)(iVar4 + 3 + iVar1 * 6) = uVar2;
            *(undefined *)(iVar4 + 2 + iVar1 * 6) = uVar2;
            *(undefined *)(iVar4 + 1 + iVar1 * 6) = uVar2;
            *(undefined *)(iVar4 + iVar1 * 6) = uVar2;
          }
          iVar9 = iVar9 + 1;
          iVar4 = iVar4 + 0x2a;
        } while (iVar9 < 0xc);
        schedule_advance_round2(unaff_EDX);
LAB_00088339:
        uVar5 = (uint)(option_flags << 0x11) >> 0x1d;
        *(uint *)(unaff_EDX + 0x84) = uVar5;
        *(uint *)(unaff_EDX + 0x80) = uVar5;
        iVar4 = unaff_EDX + 0x1b90;
        iVar9 = 0xc;
        do {
          playoff_update_team_db_f(iVar4,(uint)(option_flags << 0x11) >> 0x1d);
          for (iVar7 = 0; (iVar7 < 7 && (*(char *)(iVar4 + 4 + iVar7 * 6) != -1)); iVar7 = iVar7 + 1
              ) {
          }
          iVar8 = ((uint)(option_flags << 0x11) >> 0x1e) + 1;
          iVar7 = iVar7 - iVar8;
          for (; iVar8 < 4; iVar8 = iVar8 + 1) {
            iVar1 = iVar7 + iVar8;
            *(undefined *)(iVar4 + 5 + iVar1 * 6) = 0xff;
            uVar2 = *(undefined *)(iVar4 + 5 + iVar1 * 6);
            *(undefined *)(iVar4 + 4 + iVar1 * 6) = uVar2;
            *(undefined *)(iVar4 + 3 + iVar1 * 6) = uVar2;
            *(undefined *)(iVar4 + 2 + iVar1 * 6) = uVar2;
            *(undefined *)(iVar4 + 1 + iVar1 * 6) = uVar2;
            *(undefined *)(iVar4 + iVar1 * 6) = uVar2;
          }
          iVar9 = iVar9 + 1;
          iVar4 = iVar4 + 0x2a;
        } while (iVar9 < 0xe);
        schedule_advance_final(unaff_EDX);
LAB_000883d3:
        *(uint *)(unaff_EDX + 0x88) = (uint)(option_flags << 0x11) >> 0x1d;
        playoff_update_team_db_f(unaff_EDX + 0x1be4,(uint)(option_flags << 0x11) >> 0x1d);
        for (iVar4 = 0; (iVar4 < 7 && (*(char *)(unaff_EDX + 0x1be8 + iVar4 * 6) != -1));
            iVar4 = iVar4 + 1) {
        }
        iVar9 = ((uint)(option_flags << 0x11) >> 0x1e) + 1;
        iVar4 = iVar4 - iVar9;
        for (; iVar9 < 4; iVar9 = iVar9 + 1) {
          iVar7 = iVar4 + iVar9;
          *(undefined *)(unaff_EDX + 0x1be9 + iVar7 * 6) = 0xff;
          uVar2 = *(undefined *)(unaff_EDX + 0x1be9 + iVar7 * 6);
          *(undefined *)(unaff_EDX + 0x1be8 + iVar7 * 6) = uVar2;
          *(undefined *)(unaff_EDX + 0x1be7 + iVar7 * 6) = uVar2;
          *(undefined *)(unaff_EDX + 0x1be6 + iVar7 * 6) = uVar2;
          *(undefined *)(unaff_EDX + 0x1be5 + iVar7 * 6) = uVar2;
          *(undefined *)(unaff_EDX + 0x1be4 + iVar7 * 6) = uVar2;
        }
      }
      else {
        if (uVar5 < 0xc) goto LAB_00088339;
        if (uVar5 < 0xe) goto LAB_000883d3;
      }
      iVar4 = unaff_EDX + 0x1ae8;
      iVar9 = 0x10;
      do {
        (&dword_dc7b8)[iVar9] = (uint)*(byte *)(iVar4 + 2);
        (&unk_dc7bc)[iVar9] = (uint)*(byte *)(iVar4 + 3);
        if ((&dword_dc7b8)[iVar9] == 0xff) {
          (&dword_dc7b8)[iVar9] = 0x1a;
        }
        if ((&unk_dc7bc)[iVar9] == 0xff) {
          (&unk_dc7bc)[iVar9] = 0x1a;
        }
        iVar9 = iVar9 + 2;
        iVar4 = iVar4 + 0x2a;
      } while (iVar9 < 0x1e);
      dword_dc830 = series_winner(unaff_EDX + 0x1be4,*(undefined4 *)(unaff_EDX + 0x88));
      if (dword_dc830 == -1) {
        dword_dc830 = 0x1a;
      }
      restore_dialog_background();
    }
  }
  else {
    settimeout(1000);
    fade_palette(0,iStack_18,0x10);
    message_dialog(0xffffffff,0xffffffff,&off_d2b1c,6,0,0,&local_20,&local_24,0);
    waittimeout();
    restore_dialog_background();
  }
  fade_palette(1,iStack_18,0x10);
  make_path(auStack_84,&league_dir,off_c80eb,&aDB);
  savefile(auStack_84,dword_d07bb,dword_d07d3);
  if (dword_d07bb != 0) {
    freemem(dword_d07bb);
  }
  if (dword_d07bf != 0) {
    freemem(dword_d07bf);
  }
  if (dword_d07c7 != 0) {
    freemem(dword_d07c7);
  }
  dword_d07bb = 0;
  dword_d07bf = 0;
  dword_d07c7 = 0;
  dword_d07d3 = 0;
  dword_d07d7 = 0;
  dword_d07df = 0;
  save_schedule_db(unaff_EDX);
  dword_c6d26 = 0;
  playoff_bracket_screen();
  draw_menu_items(&unk_cf90f,3,0x40,0x41,0x42);
  fade_palette(0,iStack_18,0x10);
  uVar3 = local_1c;
LAB_0008751a:
  freemem(uVar3);
  return;
}


// ================================================================================================
// playoff_record_series @ 0x88625 [__watcall]
// ================================================================================================

void __watcall playoff_record_series(int param_1,int unaff_EDX)

{
  int iVar1;
  int iVar2;
  undefined *puVar3;
  undefined *puVar4;
  int iVar6;
  int iVar7;
  undefined auStack_3c [32];
  undefined local_1c [4];
  undefined local_18 [4];
  undefined4 *puVar5;
  
  __CHK(0x4c);
  puVar4 = auStack_3c;
  iVar6 = param_1 + 0x1998 + unaff_EDX * 0x2a;
  iVar1 = series_winner(iVar6,(uint)(option_flags << 0x11) >> 0x1d);
  if (iVar1 < 0) {
    make_path(auStack_3c,&league_dir,off_c80e7,&aDB);
    iVar1 = file_open_rw(auStack_3c,local_18);
    if (iVar1 != 0) {
      fatalerror(&aE31);
    }
    puVar3 = off_c80e3;
    make_path(auStack_3c,&league_dir,off_c80e3,&aDB);
    iVar1 = file_open_read(auStack_3c,local_1c);
    if (iVar1 != 0) {
      fatalerror(&aE32);
    }
    iVar1 = iVar6;
    for (iVar7 = 0; iVar7 < *(int *)(puVar4 + 0x28); iVar7 = iVar7 + 1) {
      if (*(char *)(iVar1 + 4) == -1) {
        *(undefined4 *)(puVar4 + -4) = 0x886f2;
        iVar2 = series_winner(iVar6,(uint)(option_flags << 0x11) >> 0x1d,puVar3);
        if (-1 < iVar2) break;
        *(undefined4 *)(puVar4 + -4) = 2;
        *(undefined4 *)(puVar4 + -8) = *(undefined4 *)(puVar4 + 0x20);
        *(undefined4 *)(puVar4 + -0xc) = *(undefined4 *)(puVar4 + 0x24);
        puVar3 = (undefined *)0x4b0;
        puVar5 = (undefined4 *)(puVar4 + -0x10);
        puVar4 = puVar4 + -0x10;
        *puVar5 = 0x88718;
        playoff_setup_screen(&league_dir,&aDB,0x4b0,iVar1);
      }
      iVar1 = iVar1 + 6;
    }
    *(undefined4 *)(puVar4 + -4) = 0x8872b;
    file_close(puVar4 + 0x24);
    *(undefined4 *)(puVar4 + -4) = 0x88734;
    file_close(puVar4 + 0x20);
  }
  return;
}


// ================================================================================================
// season_standings_db @ 0x8873c [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 __watcall season_standings_db(int param_1,undefined4 unaff_EDX)

{
  int iVar1;
  undefined uVar2;
  byte bVar3;
  char cVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  undefined5 *puVar10;
  undefined auStack_74 [64];
  uint local_34;
  undefined4 local_30;
  int iStack_2c;
  int iStack_28;
  int iStack_24;
  int local_20;
  uint uStack_1c;
  
  __CHK(0x90);
  local_30 = 0;
  uStack_1c = *(int *)(param_1 + 0x40);
  iVar6 = uStack_1c + 0x444;
  season_record_result(&league_dir,&aDb_c3a4b,(int)(short)user2_team._2_2_,0,iVar6,&league_dir);
  season_record_result(&league_dir,&aDb_c3a4b,(int)(short)_away_team_id,1,iVar6,&league_dir);
  iVar8 = param_1 + iVar6 * 6;
  iVar6 = (int)uStack_1c % 7 + 1;
  uStack_1c = (int)uStack_1c / 7;
  *(undefined *)(iVar8 + 4) = dword_df622._2_1_;
  *(undefined *)(iVar8 + 5) = dword_df722._2_1_;
  make_path(auStack_74,&league_dir,off_c80eb,&aDB);
  dword_d07bb = loadfile(auStack_74,0x20);
  dword_d07d3 = filesize(auStack_74);
  make_path(auStack_74,&league_dir,off_c80db,&aDB);
  dword_d07bf = loadfile(auStack_74,0x20);
  dword_d07d7 = filesize(auStack_74);
  make_path(auStack_74,&league_dir,off_c80d7,&aDB);
  dword_d07c7 = loadfile(auStack_74,0x20);
  dword_d07df = filesize(auStack_74);
  if ((int)uStack_1c < 8) {
    uVar9 = 0;
    do {
      if (uVar9 != uStack_1c) {
        playoff_record_series(param_1,uVar9,iVar6);
      }
      uVar9 = uVar9 + 1;
    } while ((int)uVar9 < 8);
  }
  else if ((int)uStack_1c < 0xc) {
    uVar9 = 8;
    do {
      if (uVar9 != uStack_1c) {
        playoff_record_series(param_1,uVar9,iVar6);
      }
      uVar9 = uVar9 + 1;
    } while ((int)uVar9 < 0xc);
  }
  else if ((int)uStack_1c < 0xe) {
    uVar9 = 0xc;
    do {
      if (uVar9 != uStack_1c) {
        playoff_record_series(param_1,uVar9,iVar6);
      }
      uVar9 = uVar9 + 1;
    } while ((int)uVar9 < 0xe);
  }
  iVar6 = param_1 + (uStack_1c * 7 + 0x444) * 6;
  uVar9 = series_winner(iVar6,(uint)(option_flags << 0x11) >> 0x1d);
  if ((int)uVar9 < 0) {
    local_20 = 0;
    iStack_24 = 0;
    iVar8 = *(int *)(param_1 + 0x40);
    *(int *)(param_1 + 0x40) = *(int *)(param_1 + 0x40) + 1;
    iVar8 = param_1 + (iVar8 + 0x445) * 6;
    series_wins(iVar6,&local_20,&iStack_24,&iStack_28,&iStack_2c);
    iVar6 = local_20;
    iVar5 = iStack_24;
    if (local_20 == iStack_24) {
      puVar10 = &aTied;
    }
    else if (iStack_24 < local_20) {
      puVar10 = (undefined5 *)(&team_abbrev)[iStack_28];
    }
    else {
      puVar10 = (undefined5 *)(&team_abbrev)[iStack_2c];
      iVar6 = iStack_24;
      iVar5 = local_20;
    }
    sprintf(&unk_ed7bc,off_d288c,puVar10,iVar6,iVar5);
    strcpy(&unk_ddcfb,&unk_ed7bc);
  }
  else {
    local_34 = (uint)(uVar9 == (int)(short)user2_team._2_2_);
    uVar7 = option_flags << 0x11;
    if ((int)uStack_1c < 8) {
      uVar7 = uVar7 >> 0x1d;
      *(uint *)(param_1 + 0x6c) = uVar7;
      *(uint *)(param_1 + 0x68) = uVar7;
      *(uint *)(param_1 + 100) = uVar7;
      *(uint *)(param_1 + 0x60) = uVar7;
      *(uint *)(param_1 + 0x5c) = uVar7;
      *(uint *)(param_1 + 0x58) = uVar7;
      *(uint *)(param_1 + 0x54) = uVar7;
      *(uint *)(param_1 + 0x50) = uVar7;
      iVar6 = param_1 + 0x1998;
      uVar7 = 0;
      do {
        if (uVar7 != uStack_1c) {
          playoff_update_team_db_f(iVar6,(uint)(option_flags << 0x11) >> 0x1d);
        }
        for (iVar8 = 0; (iVar8 < 7 && (*(char *)(iVar6 + 4 + iVar8 * 6) != -1)); iVar8 = iVar8 + 1)
        {
        }
        iVar5 = ((uint)(option_flags << 0x11) >> 0x1e) + 1;
        iVar8 = iVar8 - iVar5;
        for (; iVar5 < 4; iVar5 = iVar5 + 1) {
          iVar1 = iVar8 + iVar5;
          *(undefined *)(iVar6 + 5 + iVar1 * 6) = 0xff;
          uVar2 = *(undefined *)(iVar6 + 5 + iVar1 * 6);
          *(undefined *)(iVar6 + 4 + iVar1 * 6) = uVar2;
          *(undefined *)(iVar6 + 3 + iVar1 * 6) = uVar2;
          *(undefined *)(iVar6 + 2 + iVar1 * 6) = uVar2;
          *(undefined *)(iVar6 + 1 + iVar1 * 6) = uVar2;
          *(undefined *)(iVar6 + iVar1 * 6) = uVar2;
        }
        uVar7 = uVar7 + 1;
        iVar6 = iVar6 + 0x2a;
      } while ((int)uVar7 < 8);
      schedule_advance_round1(param_1);
    }
    else if ((int)uStack_1c < 0xc) {
      uVar7 = uVar7 >> 0x1d;
      *(uint *)(param_1 + 0x7c) = uVar7;
      *(uint *)(param_1 + 0x78) = uVar7;
      *(uint *)(param_1 + 0x74) = uVar7;
      *(uint *)(param_1 + 0x70) = uVar7;
      iVar6 = param_1 + 0x1ae8;
      uVar7 = 8;
      do {
        if (uVar7 != uStack_1c) {
          playoff_update_team_db_f(iVar6,(uint)(option_flags << 0x11) >> 0x1d);
        }
        for (iVar8 = 0; (iVar8 < 7 && (*(char *)(iVar6 + 4 + iVar8 * 6) != -1)); iVar8 = iVar8 + 1)
        {
        }
        iVar5 = ((uint)(option_flags << 0x11) >> 0x1e) + 1;
        iVar8 = iVar8 - iVar5;
        for (; iVar5 < 4; iVar5 = iVar5 + 1) {
          iVar1 = iVar8 + iVar5;
          *(undefined *)(iVar6 + 5 + iVar1 * 6) = 0xff;
          uVar2 = *(undefined *)(iVar6 + 5 + iVar1 * 6);
          *(undefined *)(iVar6 + 4 + iVar1 * 6) = uVar2;
          *(undefined *)(iVar6 + 3 + iVar1 * 6) = uVar2;
          *(undefined *)(iVar6 + 2 + iVar1 * 6) = uVar2;
          *(undefined *)(iVar6 + 1 + iVar1 * 6) = uVar2;
          *(undefined *)(iVar6 + iVar1 * 6) = uVar2;
        }
        uVar7 = uVar7 + 1;
        iVar6 = iVar6 + 0x2a;
      } while ((int)uVar7 < 0xc);
      schedule_advance_round2(param_1);
    }
    else if ((int)uStack_1c < 0xe) {
      *(uint *)(param_1 + 0x84) = uVar7 >> 0x1d;
      *(uint *)(param_1 + 0x80) = uVar7 >> 0x1d;
      iVar6 = param_1 + 0x1b90;
      uVar7 = 0xc;
      do {
        if (uVar7 != uStack_1c) {
          playoff_update_team_db_f(iVar6,(uint)(option_flags << 0x11) >> 0x1d);
        }
        for (iVar8 = 0; (iVar8 < 7 && (*(char *)(iVar6 + 4 + iVar8 * 6) != -1)); iVar8 = iVar8 + 1)
        {
        }
        iVar5 = ((uint)(option_flags << 0x11) >> 0x1e) + 1;
        iVar8 = iVar8 - iVar5;
        for (; iVar5 < 4; iVar5 = iVar5 + 1) {
          iVar1 = iVar8 + iVar5;
          *(undefined *)(iVar6 + 5 + iVar1 * 6) = 0xff;
          uVar2 = *(undefined *)(iVar6 + 5 + iVar1 * 6);
          *(undefined *)(iVar6 + 4 + iVar1 * 6) = uVar2;
          *(undefined *)(iVar6 + 3 + iVar1 * 6) = uVar2;
          *(undefined *)(iVar6 + 2 + iVar1 * 6) = uVar2;
          *(undefined *)(iVar6 + 1 + iVar1 * 6) = uVar2;
          *(undefined *)(iVar6 + iVar1 * 6) = uVar2;
        }
        uVar7 = uVar7 + 1;
        iVar6 = iVar6 + 0x2a;
      } while ((int)uVar7 < 0xe);
      schedule_advance_final(param_1);
    }
    else {
      *(uint *)(param_1 + 0x88) = uVar7 >> 0x1d;
      for (iVar6 = 0; (iVar6 < 7 && (*(char *)(param_1 + 0x1be8 + iVar6 * 6) != -1));
          iVar6 = iVar6 + 1) {
      }
      iVar8 = ((uint)(option_flags << 0x11) >> 0x1e) + 1;
      iVar6 = iVar6 - iVar8;
      for (; iVar8 < 4; iVar8 = iVar8 + 1) {
        iVar5 = iVar6 + iVar8;
        *(undefined *)(param_1 + 0x1be9 + iVar5 * 6) = 0xff;
        uVar2 = *(undefined *)(param_1 + 0x1be9 + iVar5 * 6);
        *(undefined *)(param_1 + 0x1be8 + iVar5 * 6) = uVar2;
        *(undefined *)(param_1 + 0x1be7 + iVar5 * 6) = uVar2;
        *(undefined *)(param_1 + 0x1be6 + iVar5 * 6) = uVar2;
        *(undefined *)(param_1 + 0x1be5 + iVar5 * 6) = uVar2;
        *(undefined *)(param_1 + 0x1be4 + iVar5 * 6) = uVar2;
      }
    }
    iVar8 = param_1 + 0x1ae8;
    iVar6 = 0x10;
    do {
      (&dword_dc7b8)[iVar6] = (uint)*(byte *)(iVar8 + 2);
      (&unk_dc7bc)[iVar6] = (uint)*(byte *)(iVar8 + 3);
      if ((&dword_dc7b8)[iVar6] == 0xff) {
        (&dword_dc7b8)[iVar6] = 0x1a;
      }
      if ((&unk_dc7bc)[iVar6] == 0xff) {
        (&unk_dc7bc)[iVar6] = 0x1a;
      }
      iVar6 = iVar6 + 2;
      iVar8 = iVar8 + 0x2a;
    } while (iVar6 < 0x1e);
    iVar8 = param_1 + 0x1be4;
    dword_dc830 = series_winner(iVar8,*(undefined4 *)(param_1 + 0x88));
    if (dword_dc830 == -1) {
      dword_dc830 = 0x1a;
    }
    if (uStack_1c < 8) {
      if (uStack_1c < 4) {
        if ((*(byte *)(param_1 + 0x1aea) == uVar9) || (*(byte *)(param_1 + 0x1aeb) == uVar9)) {
          uStack_1c = 8;
          iVar8 = param_1 + 0x1ae8;
        }
        else {
          uStack_1c = 9;
          iVar8 = param_1 + 0x1b12;
        }
      }
      else if ((*(byte *)(param_1 + 0x1b3e) == uVar9) || (*(byte *)(param_1 + 0x1b3f) == uVar9)) {
        uStack_1c = 10;
        iVar8 = param_1 + 0x1b3c;
      }
      else {
        uStack_1c = 0xb;
        iVar8 = param_1 + 0x1b66;
      }
    }
    else if (uStack_1c < 10) {
      uStack_1c = 0xc;
      iVar8 = param_1 + 0x1b90;
    }
    else if (uStack_1c < 0xc) {
      uStack_1c = 0xd;
      iVar8 = param_1 + 0x1bba;
    }
    else if (uStack_1c < 0xe) {
      uStack_1c = 0xe;
      iVar8 = param_1 + 0x1be4;
    }
    else if (uStack_1c == 0xe) {
      uStack_1c = 0xf;
      funcptr_cf983 = (undefined *)0x0;
      *(undefined4 *)(param_1 + 0x40) = 0x69;
      save_schedule_db();
    }
    *(uint *)(param_1 + 0x40) = uStack_1c * 7;
    load_game_set(&settings_playoff);
  }
  make_path(auStack_74,&league_dir,off_c80eb,&aDB);
  savefile(auStack_74,dword_d07bb,dword_d07d3);
  if (dword_d07bb != 0) {
    freemem(dword_d07bb);
  }
  if (dword_d07bf != 0) {
    freemem(dword_d07bf);
  }
  if (dword_d07c7 != 0) {
    freemem(dword_d07c7);
  }
  dword_d07bb = 0;
  dword_d07bf = 0;
  dword_d07c7 = 0;
  dword_d07d3 = 0;
  dword_d07d7 = 0;
  dword_d07df = 0;
  if (0xe < (int)uStack_1c) goto LAB_00087b2c;
  if ((int)uVar9 < 0) {
    bVar3 = *(byte *)(iVar8 + 2);
    user2_team._2_2_ = (ushort)bVar3;
    _away_team_id = (ushort)*(byte *)(iVar8 + 3);
    if ((dword_c5403 == 0xffffffff) ||
       ((dword_c5403 != 0xfffffffe &&
        ((int)(uint)CONCAT12(bVar3,(undefined2)user2_team) >> 0x10 == dword_c5403)))) {
      dword_c5413 = 0;
    }
    else {
      dword_c5413 = 1;
    }
    if (dword_c5407 == 0xffffffff) {
      dword_c5417 = 0;
      goto LAB_00087b2c;
    }
    if ((dword_c5407 != 0xfffffffe) &&
       ((int)(uint)CONCAT12(bVar3,(undefined2)user2_team) >> 0x10 == dword_c5407)) {
      dword_c5417 = 0;
      goto LAB_00087b2c;
    }
  }
  else {
    if ((dword_c5413 == dword_c5417) ||
       (cVar4 = (int)dword_c5407 < 0 != (int)dword_c5403 < 0, (bool)cVar4)) {
      cVar4 = '\x01';
    }
    else if ((-1 < (int)dword_c5403) || (-1 < (int)dword_c5407)) {
      cVar4 = '\x02';
    }
    if (cVar4 == '\x01') {
      if ((uVar9 != dword_c5403) && (uVar9 != dword_c5407)) {
        *(undefined4 *)(param_1 + 0x40) = 0x69;
        funcptr_cf983 = (undefined *)0x0;
        save_schedule_db(param_1);
        local_30 = 1;
        goto LAB_00087b2c;
      }
    }
    else if (cVar4 == '\x02') {
      strcpy(unk_d2a68 + 4,&unk_dbc35 + local_34 * 0x2e8);
      strcpy(unk_d2aab + 4,&unk_dbc35 + (uint)(local_34 == 0) * 0x2e8);
      if (uVar9 == dword_c5403) {
        dword_c5407 = (dword_c5417 == 0) - 2;
      }
      else {
        dword_c5403 = (dword_c5413 == 0) - 2;
      }
      local_30 = 2;
    }
    *(uint *)(param_1 + 0x44) = uStack_1c;
    user2_team._2_2_ = (ushort)*(byte *)(iVar8 + 2);
    _away_team_id = (ushort)*(byte *)(iVar8 + 3);
    if ((uVar9 == dword_c5403) && (dword_c5403 == dword_c5407)) {
      if (*(byte *)(iVar8 + 2) == dword_c5403) {
        dword_c5417 = uVar9 ^ dword_c5407;
        dword_c5413 = 0;
      }
      else {
        dword_c5417 = 1;
        dword_c5413 = 1;
      }
      goto LAB_00087b2c;
    }
    if (uVar9 != dword_c5403) {
      if (uVar9 == dword_c5407) {
        if (*(byte *)(iVar8 + 2) == dword_c5407) {
          dword_c5417 = 0;
          dword_c5403 = 0xfffffffe;
          dword_c5413 = 1;
        }
        else {
          dword_c5417 = 1;
          dword_c5403 = 0xffffffff;
          dword_c5413 = uVar9 ^ dword_c5407;
        }
      }
      goto LAB_00087b2c;
    }
    if (*(byte *)(iVar8 + 2) != uVar9) {
      dword_c5413 = 1;
      dword_c5407 = 0xffffffff;
      dword_c5417 = 0;
      goto LAB_00087b2c;
    }
    dword_c5413 = 0;
    dword_c5407 = 0xfffffffe;
  }
  dword_c5417 = 1;
LAB_00087b2c:
  return CONCAT44(unaff_EDX,local_30);
}


// ================================================================================================
// load_schedule_file @ 0x891b2 [__watcall]
// ================================================================================================

longlong __watcall load_schedule_file(int *param_1,uint unaff_EDX)

{
  int iVar1;
  char acStack_50 [64];
  
  __CHK(0x60);
  sprintf(acStack_50,&byte_dd750,aSchedule);
  iVar1 = loadfile_data(acStack_50,0x20);
  *param_1 = iVar1;
  if (iVar1 == 0) {
    sprintf(acStack_50,&byte_dd710,aSchedule);
    iVar1 = loadfile_data(acStack_50,0x20);
    *param_1 = iVar1;
  }
  return (ulonglong)unaff_EDX << 0x20;
}


// ================================================================================================
// save_schedule_db @ 0x89223 [__watcall]
// ================================================================================================

void __watcall save_schedule_db(int param_1)

{
  undefined4 uVar1;
  undefined auStack_50 [64];
  
  __CHK(0x60);
  make_path(auStack_50,&league_dir,aScheduleDb_c3a2b,0);
  uVar1 = filesize(auStack_50);
  savefile(auStack_50,param_1 + -2,uVar1);
  return;
}


// ================================================================================================
// playoff_tree_screen @ 0x89268 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 __watcall playoff_tree_screen(int *param_1,undefined4 unaff_EDX)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined *puVar4;
  int iVar5;
  undefined *puVar6;
  char acStack_48 [32];
  int local_28;
  int local_24;
  undefined4 uStack_20;
  uint uStack_1c;
  
  __CHK(0x58);
  uStack_20 = 0;
  local_24 = 0;
  local_28 = 0;
  save_settings(&settings_exhibition);
  apply_settings(&settings_playoff);
  set_menu_mode(2);
  set_hub_title(1);
  if (*param_1 < 0) {
    make_path(acStack_48,&league_dir,aGameSav_c3a5d,0);
    iVar1 = file_open_read(acStack_48,param_1);
    if (iVar1 != 0) {
      *param_1 = -1;
    }
  }
  set_dialog_colors(0xf9,0xfa,0xf8,0xfa,0);
  if ((-1 < *param_1) && (iVar1 = check_disk_space_for_game(), iVar1 == 0)) {
    load_schedule_file(&local_28);
    iVar1 = local_28;
    dword_dc234 = *(int *)(local_28 + 0x42) + 0x444;
    local_28 = local_28 + 2;
    freemem(iVar1);
    local_28 = 0;
    if ((sound_enabled != '\0') && (dword_c721d != 0)) {
      sound_fade(dword_d2431,3,100);
    }
    uVar2 = allocmem(aPalette_c39b3,0x300,0x20);
    getpalette(0,0x100,uVar2);
    fade_palette(1,uVar2,0x10);
    freemem(uVar2);
    if ((sound_enabled != '\0') && (dword_c721d != 0)) {
      do {
        iVar1 = sound_channel_status(ram0x000d242c >> 0x18,3);
      } while (iVar1 == 0);
      releasememblock(dword_c721d);
      dword_c721d = 0;
      local_24 = 1;
    }
    loading_screen();
    setup_pause_menu_teams();
    setup_controls();
    dword_c65c0 = exh_hub_sports_central;
    dword_c65c4 = exh_hub_playoff_tree;
    dword_c65c8 = exh_hub_league_calendar;
    dword_c65cc = exh_hub_standings;
    dword_c65d0 = exh_hub_stats;
    play_game(param_1);
    dword_c65c0 = hub_sports_central;
    dword_c65c4 = hub_playoff_tree;
    dword_c65c8 = hub_league_calendar;
    dword_c65cc = hub_standings;
    dword_c65d0 = hub_stats;
    dword_c7290 = 0x50;
    if (local_28 == 0) {
      load_schedule_file(&local_28);
      local_28 = local_28 + 2;
    }
    if (dword_c53f7 == 1) {
      make_path(acStack_48,&league_dir,aGameSav_c3a5d,0);
      iVar1 = file_open_read(acStack_48,param_1);
      if (iVar1 == 0) {
        remove_file(acStack_48);
        word_c5366._1_1_ = word_c5366._1_1_ & 0x7f;
        option_flags._1_1_ = option_flags._1_1_ & 0x7f;
      }
      uStack_20 = season_standings_db(local_28);
      save_schedule_db(local_28);
    }
    uVar2 = allocmem(aPalette_c39b3,0x300,0x20);
    getpalette(0,0x100,uVar2);
    fade_palette(1,uVar2,0x10);
    freemem(uVar2);
    ui_init();
  }
  if (-1 < *param_1) {
    file_close(param_1);
  }
  if (local_28 == 0) {
    load_schedule_file(&local_28);
    local_28 = local_28 + 2;
  }
  iVar5 = local_28 + 0x1998;
  iVar1 = 0;
  do {
    (&dword_dc7b8)[iVar1] = (uint)*(byte *)(iVar5 + 2);
    (&unk_dc7bc)[iVar1] = (uint)*(byte *)(iVar5 + 3);
    if ((&dword_dc7b8)[iVar1] == 0xff) {
      (&dword_dc7b8)[iVar1] = 0x1a;
    }
    if ((&unk_dc7bc)[iVar1] == 0xff) {
      (&unk_dc7bc)[iVar1] = 0x1a;
    }
    iVar1 = iVar1 + 2;
    iVar5 = iVar5 + 0x2a;
  } while (iVar1 < 0x1e);
  dword_dc830 = series_winner(local_28 + 0x1be4,*(undefined4 *)(local_28 + 0x88));
  if (dword_dc830 == -1) {
    dword_dc830 = 0x1a;
  }
  iVar1 = 0;
  do {
    strcpy(&unk_ddac4 + iVar1 * 0x15,(&off_c54a9)[iVar1]);
    iVar1 = iVar1 + 1;
  } while (iVar1 < 0x1a);
  strcpy(&unk_ddce6,(char *)&asc_c3a66);
  if (dword_c65ac == 0) {
    puVar6 = install_path;
    if (byte_ed859 != '\x01') {
      puVar6 = (undefined *)0x0;
    }
    make_path(acStack_48,puVar6,aEmbscup_c39bb);
    dword_c65ac = loadshapes(acStack_48,0x20);
  }
  if ((local_24 == 0) && (sound_enabled != '\0')) {
    sound_fade(dword_d2431,3,100);
  }
  uVar2 = allocmem(aPalette_c39b3,0x300,0x20);
  getpalette(0,0x100,uVar2);
  fade_palette(1,uVar2);
  freemem(uVar2);
  if ((local_24 == 0) && (sound_enabled != '\0')) {
    do {
      iVar1 = sound_channel_status(ram0x000d242c >> 0x18,3);
    } while (iVar1 == 0);
    if (dword_c721d != 0) {
      releasememblock(dword_c721d);
    }
    dword_c721d = 0;
  }
  playoff_results_screen(uStack_20,local_28);
  save_schedule_db(local_28);
  iVar1 = *(int *)(local_28 + 0x40);
  puVar6 = (undefined *)(local_28 + (iVar1 + 0x444) * 6);
  dword_d29fb = iVar1 % 7;
  if (iVar1 / 7 < 0xf) {
    funcptr_cf983 = menu_play_next_game;
  }
  else {
    funcptr_cf983 = (undefined *)0x0;
  }
  dword_c6d26 = 0;
  draw_menu_items(&unk_cf90f,3,0x40,0x41,0x42);
  uVar2 = *(undefined4 *)(local_28 + 0x44);
  while (iVar1 = playoff_tree_menu(&unk_cf90f,3,0x40,0x41,0x42,uVar2), iVar1 == 0) {
    if (dword_c65ac != 0) {
      freemem(dword_c65ac);
      dword_c65ac = 0;
    }
    uVar2 = allocmem(aPalette_c39b3,0x300,0x20);
    getpalette(0,0x100,uVar2);
    fade_palette(1,uVar2,0x10);
    set_dialog_colors(0x41,0x40,0x42,0x40,0x43);
    clearscreen_default(0);
    setpalette(0,0x100,uVar2);
    iVar1 = check_disk_space_for_game();
    if (iVar1 == 0) {
      fade_palette(1,uVar2);
      freemem(uVar2);
      setup_controls();
      load_game_set(&settings_playoff);
      save_schedule_db(local_28);
      dword_dc234 = *(int *)(local_28 + 0x40) + 0x444;
      setup_pause_menu_teams();
      make_path(acStack_48,&league_dir,aGameSav_c3a5d,0);
      uVar3 = file_open_read(acStack_48,param_1);
      if (uVar3 == 0) {
        uStack_1c = uVar3;
        loading_screen();
      }
      else {
        *param_1 = -1;
        begin_game_session(*puVar6,puVar6[1]);
        uStack_1c = team_select_screen((int)user2_team._2_2_,(int)_away_team_id);
        ui_shutdown();
      }
      freemem(local_28 + -2);
      local_28 = 0;
      if ((uStack_1c & 4) == 0) {
        dword_c65c0 = exh_hub_sports_central;
        dword_c65c4 = exh_hub_playoff_tree;
        dword_c65c8 = exh_hub_league_calendar;
        dword_c65cc = exh_hub_standings;
        dword_c65d0 = exh_hub_stats;
        play_game(param_1);
        dword_c65c0 = hub_sports_central;
        dword_c65c4 = hub_playoff_tree;
        dword_c65c8 = hub_league_calendar;
        dword_c65cc = hub_standings;
        dword_c65d0 = hub_stats;
      }
      dword_c7290 = 0x50;
    }
    else {
      fade_palette(1,uVar2);
      freemem(uVar2);
      uStack_1c = 4;
    }
    if (local_28 == 0) {
      load_schedule_file(&local_28);
      local_28 = local_28 + 2;
    }
    if ((dword_c53f7 == 1) && ((uStack_1c & 4) == 0)) {
      uStack_20 = season_standings_db(local_28);
      save_schedule_db(local_28);
    }
    else {
      uStack_20 = 0;
    }
    puVar6 = (undefined *)(local_28 + (*(int *)(local_28 + 0x40) + 0x444) * 6);
    if (dword_c65ac == 0) {
      puVar4 = install_path;
      if (byte_ed859 != '\x01') {
        puVar4 = (undefined *)0x0;
      }
      make_path(acStack_48,puVar4,aEmbscup_c39bb,0);
      dword_c65ac = loadshapes(acStack_48,0x20);
    }
    uVar2 = allocmem(aPalette_c39b3,0x300,0x20);
    getpalette(0,0x100,uVar2);
    fade_palette(1,uVar2,0x10);
    freemem(uVar2);
    dword_c6d26 = 0;
    draw_menu_items(&unk_cf90f,3,0x40,0x41,0x42);
    ui_init();
    playoff_results_screen(uStack_20,local_28);
    save_schedule_db(local_28);
    dword_d29fb = *(int *)(local_28 + 0x40) % 7;
    uVar2 = *(undefined4 *)(local_28 + 0x44);
  }
  freemem(local_28 + -2);
  if (dword_c65ac != 0) {
    freemem(dword_c65ac);
    dword_c65ac = 0;
  }
  uVar2 = allocmem(aPalette_c39b3,0x300,0x20);
  getpalette(0,0x100,uVar2);
  fade_palette(1,uVar2,0x10);
  freemem(uVar2);
  set_menu_mode(0);
  load_game_set(&settings_playoff);
  apply_settings(&settings_exhibition);
  return CONCAT44(unaff_EDX,2);
}


// ================================================================================================
// return_zero_89b5c @ 0x89b5c [__watcall]
// ================================================================================================

undefined4 __watcall return_zero_89b5c(void)

{
  __CHK(4);
  return 0;
}


// ================================================================================================
// playoff_tree_highlight @ 0x89b69 [__watcall]
// ================================================================================================

void __watcall playoff_tree_highlight(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  __CHK(0x30);
  iVar1 = *(int *)(&unk_d2b70 + param_1 * 4);
  iVar2 = *(int *)(&unk_d2bec + param_1 * 4);
  if (param_1 < 0x1c) {
    iVar3 = iVar2 + 0x1f;
  }
  else {
    iVar3 = iVar2 + 0x3c;
  }
  xorbox(iVar1,iVar2,iVar1 + 0x74,iVar3,0x80);
  xorbox(iVar1 + -1,iVar2 + -1,iVar1 + 0x75,iVar3 + 1,0x80);
  return;
}


// ================================================================================================
// playoff_tree_menu @ 0x89bd2 [__watcall]
// ================================================================================================

undefined4 __watcall
playoff_tree_menu(int *param_1,int unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX,
                 undefined4 param_5,int param_6)

{
  ulonglong uVar1;
  undefined4 ****ppppuVar2;
  undefined4 *puVar3;
  int iVar4;
  int *piVar5;
  undefined4 uVar6;
  undefined4 extraout_EDX;
  undefined *puVar7;
  undefined4 *****pppppuVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  int iVar11;
  int iVar12;
  undefined4 *puVar13;
  undefined4 *puVar14;
  byte bVar15;
  ulonglong uVar16;
  undefined8 uVar17;
  int *local_d4;
  int local_d0 [8];
  undefined auStack_b0 [32];
  int local_90 [8];
  int *local_70 [4];
  int local_60 [4];
  undefined local_50;
  undefined uStack_4f;
  undefined uStack_4e;
  undefined uStack_4d;
  undefined local_4c;
  undefined uStack_4b;
  undefined uStack_4a;
  undefined uStack_49;
  undefined local_48;
  undefined uStack_47;
  undefined uStack_46;
  undefined uStack_45;
  int local_44;
  int local_40;
  undefined4 ****local_3c;
  int iStack_38;
  int local_34;
  undefined4 *local_30;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  undefined4 ****local_10;
  
  bVar15 = 0;
  __CHK(0xf4);
  local_28 = 0;
  local_70[3] = (int *)0x0;
  local_70[2] = (int *)0x0;
  local_70[1] = (int *)0x0;
  local_90[7] = 0;
  local_90[6] = 0;
  local_90[5] = 0;
  local_90[4] = 0;
  local_90[3] = 0;
  local_90[2] = 0;
  local_90[1] = 0;
  local_90[0] = 0;
  local_d0[1] = 0;
  local_d0[0] = 0;
  local_d4 = param_1;
  local_70[0] = param_1;
  local_60[0] = unaff_EDX;
  puVar3 = (undefined4 *)
           allocmem(aPointer_c3a68,
                    (((int)pointer_shapes[1] >> 0x10) + 1) *
                    ((*(int *)((int)pointer_shapes + 2) >> 0x10) * 4 + 4) + 0x11,0x20);
  puVar13 = puVar3 + (uint)bVar15 * -2 + 1;
  puVar9 = pointer_shapes + (uint)bVar15 * -2 + 1;
  *puVar3 = *pointer_shapes;
  puVar14 = puVar13 + (uint)bVar15 * -2 + 1;
  puVar10 = puVar9 + (uint)bVar15 * -2 + 1;
  *puVar13 = *puVar9;
  *puVar14 = *puVar10;
  puVar14[(uint)bVar15 * -2 + 1] = puVar10[(uint)bVar15 * -2 + 1];
  *(undefined *)(puVar14 + (uint)bVar15 * -2 + 1 + (uint)bVar15 * -2 + 1) =
       *(undefined *)(puVar10 + (uint)bVar15 * -2 + 1 + (uint)bVar15 * -2 + 1);
  *(short *)(puVar3 + 1) = *(short *)(pointer_shapes + 1) + 1;
  *(short *)((int)puVar3 + 6) = *(short *)((int)pointer_shapes + 6) + 1;
  pppppuVar8 = (undefined4 *****)local_70[0][2];
  iStack_38 = (*local_70[0] + (int)pppppuVar8) / 2;
  local_3c = (undefined4 ****)((local_70[0][1] + local_70[0][3]) / 2);
  local_30 = puVar3;
  local_2c = iStack_38;
  local_10 = local_3c;
  setdefaultscreen();
  ppppuVar2 = local_10;
  iVar11 = local_2c;
  grabshape(puVar3,local_2c,local_10);
  drawshape_remap(pointer_shapes,iVar11,ppppuVar2);
  setmouselimits(0,0,0x280,0x1e0);
  setmousepos(iVar11,ppppuVar2);
  (*(code *)mouse_update_callback)();
  event_queue_reset();
  local_18 = param_6 * 2;
  if (local_18 == 0x1e) {
    local_1c = -1;
  }
  else {
    local_1c = local_18 + 1;
  }
  uVar16 = playoff_tree_highlight(local_18);
LAB_00089d6e:
  uVar6 = 0;
  do {
    uVar17 = event_queue_pop((int)uVar16,(int)(uVar16 >> 0x20),pppppuVar8);
    uVar1 = CONCAT44((int)((ulonglong)uVar17 >> 0x20),uVar6);
    if ((int)uVar17 == 0) break;
    pppppuVar8 = &local_3c;
    uVar16 = (*ui_poll_callback)();
    uVar6 = (undefined4)uVar16;
    uVar1 = uVar16;
  } while ((uVar16 & 2) == 0);
  ppppuVar2 = local_10;
  iVar11 = local_2c;
  puVar3 = local_30;
  uVar16 = CONCAT44((int)(uVar1 >> 0x20),local_3c);
  if ((uVar1 & 2) == 0) goto code_r0x00089d9c;
  drawshape(local_30,local_2c,local_10);
  iVar4 = hit_test_menus(iStack_38,local_3c,local_70,local_28,local_60,local_d0,&local_40,&local_44)
  ;
  if (iVar4 == 0) {
    drawshape(local_30,iVar11,ppppuVar2);
    iVar11 = local_28;
    if (local_28 != 0) {
      for (; -1 < iVar11; iVar11 = iVar11 + -1) {
        if (local_90[iVar11 + 4] != 0) {
          drawshape(local_90[iVar11 + 4],local_d0[iVar11 * 2],local_d0[iVar11 * 2 + 1]);
          local_d0[iVar11 * 2 + 1] = 0;
          local_d0[iVar11 * 2] = 0;
          freemem(local_90[iVar11 + 4]);
          local_90[iVar11 + 4] = 0;
          local_70[iVar11] = (int *)0x0;
          local_60[iVar11] = 0;
        }
      }
      local_28 = 0;
    }
  }
  else {
    if (local_70[local_40][local_44 * 8 + 5] == 0) {
      if (local_70[local_40][local_44 * 8 + 6] == 0) {
        drawshape(local_30,local_2c,local_10);
        uVar6 = unaff_ECX;
        highlight_menu_item(local_70[local_40] + local_90[local_40] * 8,local_d0[local_40 * 2],
                            local_d0[local_40 * 2 + 1],unaff_EBX,unaff_ECX,param_5);
        iVar12 = local_40;
        local_90[local_40] = local_44;
        iVar11 = local_d0[iVar12 * 2 + 1];
        iVar4 = local_d0[iVar12 * 2];
        piVar5 = local_70[iVar12] + local_90[iVar12] * 8;
      }
      else {
        drawshape(local_30,local_2c,local_10);
        iVar11 = local_28;
        if (local_28 != local_40) {
          for (; local_40 < iVar11; iVar11 = iVar11 + -1) {
            local_90[iVar11] = 0;
            if (local_90[iVar11 + 4] != 0) {
              drawshape(local_90[iVar11 + 4],local_d0[iVar11 * 2],local_d0[iVar11 * 2 + 1]);
              local_d0[iVar11 * 2 + 1] = 0;
              local_d0[iVar11 * 2] = 0;
              freemem(local_90[iVar11 + 4]);
              local_90[iVar11 + 4] = 0;
              local_70[iVar11] = (int *)0x0;
              local_60[iVar11] = 0;
            }
          }
          local_28 = local_40;
        }
        iVar12 = local_28;
        highlight_menu_item(local_70[local_28] + local_90[local_28] * 8,local_d0[local_28 * 2],
                            local_d0[local_28 * 2 + 1],unaff_EBX,unaff_ECX,param_5);
        iVar11 = local_44;
        local_90[iVar12] = local_44;
        unhighlight_menu_item
                  (local_70[iVar12] + iVar11 * 8,local_d0[iVar12 * 2],local_d0[iVar12 * 2 + 1],
                   unaff_EBX,unaff_ECX,param_5);
        iVar4 = local_40;
        iVar11 = local_44;
        iVar12 = iVar12 + 1;
        local_28 = iVar12;
        local_70[iVar12] = (int *)local_70[local_40][local_44 * 8 + 6];
        piVar5 = local_70[iVar4] + iVar11 * 8;
        local_60[iVar12] = piVar5[7];
        if (iVar12 == 1) {
          iVar11 = *piVar5;
        }
        else {
          iVar11 = piVar5[2];
        }
        local_d0[local_28 * 2] = iVar11 + local_d0[local_28 * 2 + -2];
        if (local_28 == 1) {
          iVar11 = local_70[local_40][local_44 * 8 + 3];
        }
        else {
          iVar11 = local_70[local_40][local_44 * 8 + 1];
        }
        local_34 = local_28 * 8;
        local_d0[local_28 * 2 + 1] = iVar11 + (int)(&local_d4)[local_28 * 2];
        iVar12 = local_28;
        piVar5 = local_70[local_28];
        local_20 = (piVar5[local_60[local_28] * 8 + -6] - *piVar5) + 1;
        local_24 = (piVar5[local_60[local_28] * 8 + -5] - piVar5[1]) + 1;
        puVar3 = (undefined4 *)allocmem(aMenubuff_c3a70,local_20 * local_24 + 0x11,0x20);
        local_90[iVar12 + 4] = (int)puVar3;
        puVar10 = puVar3 + (uint)bVar15 * -2 + 1;
        puVar9 = pointer_shapes + (uint)bVar15 * -2 + 1;
        *puVar3 = *pointer_shapes;
        puVar13 = puVar10 + (uint)bVar15 * -2 + 1;
        puVar3 = puVar9 + (uint)bVar15 * -2 + 1;
        *puVar10 = *puVar9;
        *puVar13 = *puVar3;
        puVar13[(uint)bVar15 * -2 + 1] = puVar3[(uint)bVar15 * -2 + 1];
        *(undefined *)(puVar13 + (uint)bVar15 * -2 + 1 + (uint)bVar15 * -2 + 1) =
             *(undefined *)(puVar3 + (uint)bVar15 * -2 + 1 + (uint)bVar15 * -2 + 1);
        *(short *)(local_90[iVar12 + 4] + 4) = (short)local_20;
        *(short *)(local_90[iVar12 + 4] + 6) = (short)local_24;
        grabshape(local_90[iVar12 + 4],*(undefined4 *)((int)local_d0 + local_34),
                  *(undefined4 *)((int)local_d0 + local_34 + 4));
        draw_menu(local_70[iVar12],local_60[iVar12],*(undefined4 *)((int)local_d0 + local_34),
                  *(undefined4 *)((int)local_d0 + local_34 + 4),unaff_EBX,unaff_ECX,param_5);
        local_90[iVar12] = 0;
        iVar11 = *(int *)((int)local_d0 + local_34 + 4);
        iVar4 = *(int *)((int)local_d0 + local_34);
        piVar5 = local_70[iVar12];
        uVar6 = unaff_ECX;
      }
    }
    else {
      if (local_44 == local_90[local_40]) {
        drawshape(local_30,iVar11,local_10);
        for (iVar11 = 3; -1 < iVar11; iVar11 = iVar11 + -1) {
          if (local_90[iVar11 + 4] != 0) {
            drawshape(local_90[iVar11 + 4],local_d0[iVar11 * 2],local_d0[iVar11 * 2 + 1]);
            local_d0[iVar11 * 2 + 1] = 0;
            local_d0[iVar11 * 2] = 0;
            freemem(local_90[iVar11 + 4]);
          }
        }
        local_28 = 0;
        playoff_tree_highlight(local_18,local_1c);
        local_14 = dword_c6d22 >> 0x10;
        freemem(local_30);
        local_50 = 0x18;
        uStack_4f = 0;
        uStack_4e = 0;
        uStack_4d = 0x2a;
        local_4c = 0;
        uStack_4b = 0;
        uStack_4a = 0x3b;
        uStack_49 = 0x12;
        local_48 = 0;
        uStack_47 = 0x3b;
        uStack_46 = 0x3b;
        uStack_45 = 0x3b;
        setpalette(0xfb,4,&local_50);
        iVar11 = (*(code *)local_70[local_40][local_44 * 8 + 5])();
        local_30 = (undefined4 *)
                   allocmem(aPointer_c3a68,
                            (((int)pointer_shapes[1] >> 0x10) + 1) *
                            ((*(int *)((int)pointer_shapes + 2) >> 0x10) * 4 + 4) + 0x11,0x20);
        puVar10 = local_30 + (uint)bVar15 * -2 + 1;
        puVar3 = pointer_shapes + (uint)bVar15 * -2 + 1;
        *local_30 = *pointer_shapes;
        puVar13 = puVar10 + (uint)bVar15 * -2 + 1;
        puVar9 = puVar3 + (uint)bVar15 * -2 + 1;
        *puVar10 = *puVar3;
        *puVar13 = *puVar9;
        puVar13[(uint)bVar15 * -2 + 1] = puVar9[(uint)bVar15 * -2 + 1];
        *(undefined *)(puVar13 + (uint)bVar15 * -2 + 1 + (uint)bVar15 * -2 + 1) =
             *(undefined *)(puVar9 + (uint)bVar15 * -2 + 1 + (uint)bVar15 * -2 + 1);
        *(short *)(local_30 + 1) = *(short *)(local_30 + 1) + 1;
        *(short *)((int)local_30 + 6) = *(short *)((int)local_30 + 6) + 1;
        local_70[3] = (int *)0x0;
        local_70[2] = (int *)0x0;
        local_70[1] = (int *)0x0;
        local_90[6] = 0;
        local_90[5] = 0;
        local_90[4] = 0;
        local_90[3] = 0;
        local_90[2] = 0;
        local_90[1] = 0;
        local_60[3] = 0;
        local_60[2] = 0;
        local_60[1] = 0;
        if (iVar11 == 1) {
          freemem(local_30);
          uVar6 = 1;
        }
        else {
          if (iVar11 != 4) {
            if (iVar11 == 2) {
              if (dword_c65ac == 0) {
                puVar7 = (undefined *)0x0;
                if (byte_ed859 == '\x01') {
                  puVar7 = install_path;
                }
                make_path(auStack_b0,puVar7,aEmbscup_c39bb);
                dword_c65ac = loadshapes(auStack_b0,0x20);
              }
              puVar7 = install_path;
              if (byte_ed85a != '\x01') {
                puVar7 = (undefined *)0x0;
              }
              make_path(auStack_b0,puVar7,aEmbpal_c39c8,0);
              uVar6 = loadshapes(auStack_b0,0);
              iVar11 = locateshape(uVar6,&aPal_c39cf);
              setdefaultscreen();
              dword_c6d26 = 0;
              playoff_bracket_screen();
              draw_menu_items(local_d4,unaff_EDX,unaff_EBX,unaff_ECX,param_5);
              fade_palette(0,iVar11 + 0x10,0x10);
              freemem(uVar6);
            }
            setdefaultscreen();
            if (dword_c6d22 >> 0x10 != local_14) {
              dword_c6d22 = CONCAT22((short)local_14,(undefined2)dword_c6d22);
              playoff_bracket_screen();
            }
            playoff_tree_highlight(local_18,local_1c);
            setmousepos(local_2c,local_10);
            iStack_38 = local_2c;
            local_3c = local_10;
            event_queue_reset();
            goto LAB_0008a624;
          }
          freemem(local_30);
          uVar6 = 0;
        }
        return uVar6;
      }
      drawshape(local_30,iVar11,local_10);
      highlight_menu_item(local_70[local_40] + local_90[local_40] * 8,local_d0[local_40 * 2],
                          local_d0[local_40 * 2 + 1],unaff_EBX,unaff_ECX,param_5);
      iVar12 = local_40;
      local_90[local_40] = local_44;
      iVar11 = local_d0[iVar12 * 2 + 1];
      iVar4 = local_d0[iVar12 * 2];
      piVar5 = local_70[iVar12] + local_90[iVar12] * 8;
      uVar6 = unaff_ECX;
    }
    unhighlight_menu_item(piVar5,iVar4,iVar11,unaff_EBX,unaff_ECX,param_5);
    unaff_ECX = uVar6;
  }
LAB_0008a624:
  setdefaultscreen();
  puVar3 = local_30;
  goto LAB_00089ded;
code_r0x00089d9c:
  if ((iStack_38 != local_2c) || (local_3c != local_10)) {
    drawshape(local_30,local_2c,local_10);
LAB_00089ded:
    grabshape(puVar3,iStack_38,local_3c);
    pppppuVar8 = (undefined4 *****)local_3c;
    drawshape_remap(pointer_shapes,iStack_38,local_3c);
    uVar16 = CONCAT44(extraout_EDX,local_3c);
    local_2c = iStack_38;
    local_10 = local_3c;
  }
  goto LAB_00089d6e;
}


// ================================================================================================
// playoff_bracket_screen @ 0x8a652 [__watcall]
// ================================================================================================

/* WARNING: Type propagation algorithm not settling */

void __watcall playoff_bracket_screen(void)

{
  byte bVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  short sVar7;
  int extraout_ECX;
  int extraout_ECX_00;
  int extraout_ECX_01;
  int extraout_ECX_02;
  undefined *puVar8;
  int extraout_EDX;
  int extraout_EDX_00;
  short sVar9;
  ushort uVar10;
  char *pcVar11;
  char *pcVar12;
  undefined4 *puVar13;
  undefined4 *puVar14;
  byte bVar15;
  char acStackY_241e [1018];
  undefined2 auStackY_2024 [1018];
  undefined4 auStackY_1830 [1477];
  undefined4 auStack_10c [30];
  undefined auStack_94 [64];
  undefined4 uStack_54;
  undefined4 uStack_50;
  char acStack_4a [22];
  undefined auStack_34 [16];
  int local_24;
  undefined2 local_20;
  undefined2 uStack_1e;
  short sStack_1c;
  
  bVar15 = 0;
  __CHK(0x120);
  uVar6 = font_main;
  uVar5 = font_kaufm;
  local_24 = 0;
  setclip(0,0x280,0x13,0x1e0);
  uVar2 = locateshape(dword_c65ac,&aBkgd_c693b);
  drawshape_remap_home(uVar2);
  setclip(0,0x280,0,0x1e0);
  if (dword_c6d26 == 1) {
    puVar8 = install_path;
    if (byte_ed85a != '\x01') {
      puVar8 = (undefined *)0x0;
    }
    make_path(auStack_34,puVar8,aEmbpal_c39c8,0);
    uVar2 = loadshapes(auStack_34,0);
    iVar3 = locateshape(uVar2,&aPal_c39cf);
    setpalette(0,0x100,iVar3 + 0x10);
    freemem(uVar2);
    dword_c6d26 = 0;
  }
  playoff_bracket_build(&dword_dc7b8,auStack_10c,1);
  set_text_colors(0x40,0x43);
  if ((int)(&dword_dc7b8)[byte_c6d72] < 0x1a) {
    puVar8 = install_path;
    if (byte_ed908 != '\x01') {
      puVar8 = (undefined *)0x0;
    }
    make_path(auStack_34,puVar8,aPstatbar_c3a9b,0);
    uVar2 = loadshapes(auStack_34,0);
    uVar4 = locateshape(uVar2,&aRst1_c3aa4);
    drawshape_remap(uVar4,0,0x1a);
    uVar4 = locateshape(uVar2,&aRst2_c3aa9);
    drawshape_remap(uVar4,0xf,0x192);
    freemem(uVar2);
    puVar8 = install_path;
    if (byte_ed93a != '\x01') {
      puVar8 = (undefined *)0x0;
    }
    make_path(auStack_34,puVar8,aScuparrw_c3aae,0);
    uVar2 = loadshapes(auStack_34,0);
    local_20 = (undefined2)uVar2;
    uStack_1e = (undefined2)((uint)uVar2 >> 0x10);
    text_capture_begin();
    getfontstate(auStack_94);
    setfont(uVar6);
    set_text_colors(0x40,0x43);
    strcpy((char *)&uStack_54,s__WWWWWWWW__Play_Offs_000c6778 + 1);
    print_centered_shadow(0x16,&uStack_54);
    setfont(uVar5);
    uStack_54._0_1_ = aWesternConference_c3ab7[0];
    uStack_54._1_1_ = aWesternConference_c3ab7[1];
    uStack_54._2_1_ = aWesternConference_c3ab7[2];
    uStack_54._3_1_ = aWesternConference_c3ab7[3];
    puVar13 = (undefined4 *)(&stack0xffffffb4 + (uint)bVar15 * -8 + (uint)bVar15 * -8);
    pcVar11 = aWesternConference_c3ab7 + (uint)bVar15 * -8 + (uint)bVar15 * -8 + 8;
    (&uStack_50)[(uint)bVar15 * -2] =
         *(undefined4 *)(aWesternConference_c3ab7 + (uint)bVar15 * -8 + 4);
    puVar14 = puVar13 + (uint)bVar15 * -2 + 1;
    pcVar12 = pcVar11 + ((uint)bVar15 * -2 + 1) * 4;
    *puVar13 = *(undefined4 *)pcVar11;
    *puVar14 = *(undefined4 *)pcVar12;
    *(undefined2 *)(puVar14 + (uint)bVar15 * -2 + 1) =
         *(undefined2 *)(pcVar12 + ((uint)bVar15 * -2 + 1) * 4);
    *(char *)((int)(puVar14 + (uint)bVar15 * -2 + 1) + (uint)bVar15 * -4 + 2) =
         (pcVar12 + ((uint)bVar15 * -2 + 1) * 4)[(uint)bVar15 * -4 + 2];
    iVar3 = textwidth(&uStack_54);
    print_outlined(0x140 - (iVar3 >> 1),0x2f,&uStack_54);
    uStack_54._0_1_ = aEasternConference_c3aca[0];
    uStack_54._1_1_ = aEasternConference_c3aca[1];
    uStack_54._2_1_ = aEasternConference_c3aca[2];
    uStack_54._3_1_ = aEasternConference_c3aca[3];
    puVar13 = (undefined4 *)(&stack0xffffffb4 + (uint)bVar15 * -8 + (uint)bVar15 * -8);
    pcVar11 = aEasternConference_c3aca + (uint)bVar15 * -8 + (uint)bVar15 * -8 + 8;
    (&uStack_50)[(uint)bVar15 * -2] =
         *(undefined4 *)(aEasternConference_c3aca + (uint)bVar15 * -8 + 4);
    puVar14 = puVar13 + (uint)bVar15 * -2 + 1;
    pcVar12 = pcVar11 + ((uint)bVar15 * -2 + 1) * 4;
    *puVar13 = *(undefined4 *)pcVar11;
    *puVar14 = *(undefined4 *)pcVar12;
    *(undefined2 *)(puVar14 + (uint)bVar15 * -2 + 1) =
         *(undefined2 *)(pcVar12 + ((uint)bVar15 * -2 + 1) * 4);
    *(char *)((int)(puVar14 + (uint)bVar15 * -2 + 1) + (uint)bVar15 * -4 + 2) =
         (pcVar12 + ((uint)bVar15 * -2 + 1) * 4)[(uint)bVar15 * -4 + 2];
    iVar3 = textwidth(&uStack_54);
    print_outlined(0x140 - (iVar3 >> 1),0x1a7,&uStack_54);
    setfont(uVar6);
    for (sVar7 = 0; sVar7 < 8; sVar7 = sVar7 + 1) {
      if (sVar7 < 4) {
        bVar1 = (&byte_c6d72)[sVar7 * 2];
      }
      else {
        bVar1 = *(byte *)(0xc6d79 - (sVar7 * 2 + -8));
      }
      *(int *)(&unk_c6dba + (&dword_dc7b8)[(short)(ushort)bVar1] * 4) = (int)sVar7;
      iVar3 = sVar7 * 2;
      if (sVar7 < 4) {
        bVar1 = (&unk_c6db2)[iVar3];
      }
      else {
        bVar1 = *(byte *)(0xc6db9 - (iVar3 + -8));
      }
      *(int *)(&unk_c6dba + (&dword_dc7b8)[(short)(ushort)bVar1] * 4) = (int)sVar7;
    }
    sStack_1c = 0x48;
    iVar3 = 0;
    while (sVar7 = (short)iVar3, sVar7 < 8) {
      if (sVar7 < 4) {
        bVar1 = (&byte_c6d72)[sVar7 * 2];
        sVar9 = sVar7;
      }
      else {
        sVar9 = 7 - sVar7;
        bVar1 = *(byte *)(0xc6d79 - (sVar7 * 2 + -8));
      }
      set_text_colors(0x40,0x43);
      uVar10 = (ushort)bVar1;
      sprintf((char *)&uStack_54,(char *)&aC_c3add,
              *(int *)(&unk_c6dba + (&dword_dc7b8)[(short)uVar10] * 4) + 0x91);
      strcat((char *)&uStack_54,&unk_ddac4 + (&dword_dc7b8)[(short)uVar10] * 0x15);
      print_text_at(*(undefined4 *)(&unk_c6e22 + sVar9 * 2),(int)sStack_1c,&uStack_54);
      sVar7 = (&unk_c6e22)[sVar9 * 2];
      iVar3 = (&dword_dc7b8)[(short)uVar10];
      if (((((&dword_dc7b8)[byte_c6d7a] == iVar3) || (iVar3 == (&dword_dc7b8)[byte_c6d7b])) ||
          (iVar3 == (&dword_dc7b8)[byte_c6d7c])) || (iVar3 == (&dword_dc7b8)[byte_c6d7d])) {
        uVar5 = 0x44;
      }
      else {
        uVar5 = 0x40;
      }
      set_text_colors(uVar5,0x43);
      sprintf((char *)&uStack_54,(char *)&aD_c3ae1,
              *(undefined4 *)((int)auStack_10c + (short)uVar10 * 4));
      print_text_at((int)(short)(sVar7 + 0x6a),(int)sStack_1c,&uStack_54);
      if ((short)extraout_ECX == 3) {
        sStack_1c = sStack_1c + 0x10;
      }
      iVar3 = extraout_ECX + 1;
    }
    if ((((int)(&dword_dc7b8)[byte_c6d7a] < 0x1a) && ((int)(&dword_dc7b8)[byte_c6d7b] < 0x1a)) &&
       (((int)(&dword_dc7b8)[byte_c6d7c] < 0x1a && ((int)(&dword_dc7b8)[byte_c6d7d] < 0x1a)))) {
      sStack_1c = sStack_1c + 0x3f;
      uVar5 = locateshape(CONCAT22(uStack_1e,local_20),&aAup1_c3ae4);
      drawshape_remap_home(uVar5);
      iVar3 = 0;
      while (sVar7 = (short)iVar3, sVar7 < 4) {
        if (sVar7 < 2) {
          sVar9 = sVar7 + 4;
          bVar1 = (&byte_c6d7a)[sVar7 * 2];
        }
        else {
          sVar9 = 7 - sVar7;
          bVar1 = (&byte_c6d7d)[-(sVar7 * 2 + -4)];
        }
        set_text_colors(0x40,0x43);
        uVar10 = (ushort)bVar1;
        sprintf((char *)&uStack_54,(char *)&aC_c3add,
                *(int *)(&unk_c6dba + (&dword_dc7b8)[(short)uVar10] * 4) + 0x91);
        strcat((char *)&uStack_54,&unk_ddac4 + (&dword_dc7b8)[(short)uVar10] * 0x15);
        print_text_at(*(undefined4 *)(&unk_c6e22 + sVar9 * 2),(int)sStack_1c,&uStack_54);
        sVar7 = (&unk_c6e22)[sVar9 * 2];
        if (((&dword_dc7b8)[byte_c6d82] == (&dword_dc7b8)[(short)uVar10]) ||
           ((&dword_dc7b8)[(short)uVar10] == (&dword_dc7b8)[byte_c6d83])) {
          uVar5 = 0x44;
        }
        else {
          uVar5 = 0x40;
        }
        set_text_colors(uVar5,0x43);
        sprintf((char *)&uStack_54,(char *)&aD_c3ae1,
                *(undefined4 *)((int)auStack_10c + (short)uVar10 * 4));
        print_text_at((int)(short)(sVar7 + 0x6a),(int)sStack_1c,&uStack_54);
        if ((short)extraout_ECX_00 == 1) {
          sStack_1c = sStack_1c + 0x10;
        }
        iVar3 = extraout_ECX_00 + 1;
      }
      sStack_1c = sStack_1c + 0x3d;
      if (((int)(&dword_dc7b8)[byte_c6d82] < 0x1a) && ((int)(&dword_dc7b8)[byte_c6d83] < 0x1a)) {
        uVar5 = locateshape(CONCAT22(uStack_1e,local_20),&aAup2_c3ae9);
        drawshape_remap_home(uVar5);
        uVar10 = (ushort)byte_c6d82;
        set_text_colors(0x40,0x43);
        sprintf((char *)&uStack_54,(char *)&aC_c3add,
                *(int *)(&unk_c6dba + (&dword_dc7b8)[(short)uVar10] * 4) + 0x91);
        strcat((char *)&uStack_54,&unk_ddac4 + (&dword_dc7b8)[(short)uVar10] * 0x15);
        print_text_at(0x48,sStack_1c + -1,&uStack_54);
        if (((&dword_dc7b8)[byte_c6d8a] == (&dword_dc7b8)[(short)uVar10]) ||
           ((&dword_dc7b8)[(short)uVar10] == (&dword_dc7b8)[byte_c6d9a])) {
          uVar5 = 0x44;
        }
        else {
          uVar5 = 0x40;
        }
        set_text_colors(uVar5,0x43);
        sprintf((char *)&uStack_54,(char *)&aD_c3ae1,
                *(undefined4 *)((int)auStack_10c + (short)uVar10 * 4));
        print_text_at(0xb2,sStack_1c + -1,&uStack_54);
        uVar10 = (ushort)byte_c6d83;
        sStack_1c = sStack_1c + 0x10;
        set_text_colors(0x40,0x43);
        sprintf((char *)&uStack_54,(char *)&aC_c3add,
                *(int *)(&unk_c6dba + (&dword_dc7b8)[(short)uVar10] * 4) + 0x91);
        strcat((char *)&uStack_54,&unk_ddac4 + (&dword_dc7b8)[(short)uVar10] * 0x15);
        print_text_at(0x48,sStack_1c + -1,&uStack_54);
        if (((&dword_dc7b8)[byte_c6d8a] == (&dword_dc7b8)[(short)uVar10]) ||
           ((&dword_dc7b8)[(short)uVar10] == (&dword_dc7b8)[byte_c6d9a])) {
          uVar5 = 0x44;
        }
        else {
          uVar5 = 0x40;
        }
        set_text_colors(uVar5,0x43);
        sprintf((char *)&uStack_54,(char *)&aD_c3ae1,
                *(undefined4 *)((int)auStack_10c + (short)uVar10 * 4));
        print_text_at(0xb2,sStack_1c + -1,&uStack_54);
        sStack_1c = sStack_1c + -0x10;
      }
    }
    else {
      sStack_1c = sStack_1c + 0x8c;
    }
    if ((int)(&dword_dc7b8)[byte_c6d8a] < 0x1a) {
      uVar5 = CONCAT22(uStack_1e,local_20);
      uVar6 = locateshape(uVar5,&aAup3_c3aee);
      drawshape_remap_home(uVar6);
      local_24 = 1;
      uVar5 = locateshape(uVar5,&aMidl_c3af3);
      drawshape_remap_home(uVar5);
      set_text_colors(0x40,0x43);
      uStack_54._0_2_ = asc_c3af8;
      *(undefined1 *)((int)&uStack_54 + (uint)bVar15 * -4 + 2) = (&DAT_000c3afa)[(uint)bVar15 * -4];
      uVar10 = (ushort)byte_c6d8a;
      strcat((char *)&uStack_54,&unk_ddac4 + (&dword_dc7b8)[byte_c6d8a] * 0x15);
      print_text_at(0x102,sStack_1c + -4,&uStack_54);
      sprintf((char *)&uStack_54,(char *)&aD_c3ae1,
              *(undefined4 *)((int)auStack_10c + (short)uVar10 * 4));
      if ((&dword_dc7b8)[byte_c6d92] == *(int *)((int)&dword_dc7b8 + extraout_EDX)) {
        if (*(int *)(&unk_c5581 + extraout_EDX) == 3) {
          uVar5 = 0x44;
        }
        else {
          uVar5 = 0xc4;
        }
      }
      else {
        uVar5 = 0x40;
      }
      set_text_colors(uVar5,0x43);
      print_text_at(0x16c,sStack_1c + -4,&uStack_54);
    }
    if ((int)(&dword_dc7b8)[byte_c6d9a] < 0x1a) {
      uVar5 = CONCAT22(uStack_1e,local_20);
      uVar6 = locateshape(uVar5,&aAdn3_c3afb);
      drawshape_remap_home(uVar6);
      if (local_24 == 0) {
        uVar5 = locateshape(uVar5,&aMidl_c3af3);
        drawshape_remap_home(uVar5);
      }
      sStack_1c = sStack_1c + 0x10;
      set_text_colors(0x40,0x43);
      uStack_54._0_2_ = asc_c3af8;
      *(undefined1 *)((int)&uStack_54 + (uint)bVar15 * -4 + 2) = (&DAT_000c3afa)[(uint)bVar15 * -4];
      uVar10 = (ushort)byte_c6d9a;
      strcat((char *)&uStack_54,&unk_ddac4 + (&dword_dc7b8)[byte_c6d9a] * 0x15);
      print_text_at(0x102,sStack_1c + -4,&uStack_54);
      sprintf((char *)&uStack_54,(char *)&aD_c3ae1,
              *(undefined4 *)((int)auStack_10c + (short)uVar10 * 4));
      if ((&dword_dc7b8)[byte_c6d92] == *(int *)((int)&dword_dc7b8 + extraout_EDX_00)) {
        if (*(int *)(&unk_c5581 + extraout_EDX_00) == 3) {
          uVar5 = 0x44;
        }
        else {
          uVar5 = 0xc4;
        }
      }
      else {
        uVar5 = 0x40;
      }
      set_text_colors(uVar5,0x43);
      print_text_at(0x16c,sStack_1c + -4,&uStack_54);
      sStack_1c = sStack_1c + -0x10;
    }
    if (((int)(&dword_dc7b8)[byte_c6da2] < 0x1a) && ((int)(&dword_dc7b8)[byte_c6da3] < 0x1a)) {
      uVar10 = (ushort)byte_c6da2;
      set_text_colors(0x40,0x43);
      sprintf((char *)&uStack_54,(char *)&aC_c3add,
              *(int *)(&unk_c6dba + (&dword_dc7b8)[(short)uVar10] * 4) + 0x91);
      strcat((char *)&uStack_54,&unk_ddac4 + (&dword_dc7b8)[(short)uVar10] * 0x15);
      print_text_at(0x1c6,sStack_1c + -1,&uStack_54);
      if (((&dword_dc7b8)[byte_c6d8a] == (&dword_dc7b8)[(short)uVar10]) ||
         ((&dword_dc7b8)[(short)uVar10] == (&dword_dc7b8)[byte_c6d9a])) {
        uVar5 = 0xc4;
      }
      else {
        uVar5 = 0x40;
      }
      set_text_colors(uVar5,0x43);
      sprintf((char *)&uStack_54,(char *)&aD_c3ae1,
              *(undefined4 *)((int)auStack_10c + (short)uVar10 * 4));
      print_text_at(0x230,sStack_1c + -1,&uStack_54);
      uVar10 = (ushort)byte_c6da3;
      sStack_1c = sStack_1c + 0x10;
      set_text_colors(0x40,0x43);
      sprintf((char *)&uStack_54,(char *)&aC_c3add,
              *(int *)(&unk_c6dba + (&dword_dc7b8)[(short)uVar10] * 4) + 0x91);
      strcat((char *)&uStack_54,&unk_ddac4 + (&dword_dc7b8)[(short)uVar10] * 0x15);
      print_text_at(0x1c6,sStack_1c + -1,&uStack_54);
      if (((&dword_dc7b8)[byte_c6d8a] == (&dword_dc7b8)[(short)uVar10]) ||
         ((&dword_dc7b8)[(short)uVar10] == (&dword_dc7b8)[byte_c6d9a])) {
        uVar5 = 0xc4;
      }
      else {
        uVar5 = 0x40;
      }
      set_text_colors(uVar5,0x43);
      sprintf((char *)&uStack_54,(char *)&aD_c3ae1,
              *(undefined4 *)((int)auStack_10c + (short)uVar10 * 4));
      print_text_at(0x230,sStack_1c + -1,&uStack_54);
      sStack_1c = sStack_1c + 0x3d;
      uVar5 = locateshape(CONCAT22(uStack_1e,local_20),&aAdn2_c3b00);
      drawshape_remap_home(uVar5);
    }
    else {
      sStack_1c = sStack_1c + 0x4d;
    }
    if (((((int)(&dword_dc7b8)[byte_c6daa] < 0x1a) && ((int)(&dword_dc7b8)[byte_c6dab] < 0x1a)) &&
        ((int)(&dword_dc7b8)[byte_c6dac] < 0x1a)) && ((int)(&dword_dc7b8)[byte_c6dad] < 0x1a)) {
      iVar3 = 0;
      while (sVar7 = (short)iVar3, sVar7 < 4) {
        if (sVar7 < 2) {
          bVar15 = (&byte_c6daa)[sVar7 * 2];
          sVar9 = sVar7;
        }
        else {
          sVar9 = 3 - sVar7;
          bVar15 = (&byte_c6dad)[-(sVar7 * 2 + -4)];
        }
        set_text_colors(0x40,0x43);
        uVar10 = (ushort)bVar15;
        sprintf((char *)&uStack_54,(char *)&aC_c3add,
                *(int *)(&unk_c6dba + (&dword_dc7b8)[(short)uVar10] * 4) + 0x91);
        strcat((char *)&uStack_54,&unk_ddac4 + (&dword_dc7b8)[(short)uVar10] * 0x15);
        print_text_at(0x280 - (*(int *)(&unk_c6e22 + (5 - sVar9) * 2) + 100),(int)sStack_1c,
                      &uStack_54);
        sVar7 = (&unk_c6e22)[(5 - sVar9) * 2];
        if (((&dword_dc7b8)[byte_c6da2] == (&dword_dc7b8)[(short)uVar10]) ||
           ((&dword_dc7b8)[(short)uVar10] == (&dword_dc7b8)[byte_c6da3])) {
          uVar5 = 0xc4;
        }
        else {
          uVar5 = 0x40;
        }
        set_text_colors(uVar5,0x43);
        sprintf((char *)&uStack_54,(char *)&aD_c3ae1,
                *(undefined4 *)((int)auStack_10c + (short)uVar10 * 4));
        print_text_at((int)(short)(0x286 - sVar7),(int)sStack_1c,&uStack_54);
        if ((short)extraout_ECX_01 == 1) {
          sStack_1c = sStack_1c + 0x10;
        }
        iVar3 = extraout_ECX_01 + 1;
      }
      sStack_1c = sStack_1c + 0x3d;
      uVar5 = locateshape(CONCAT22(uStack_1e,local_20),&aAdn1_c3b05);
      drawshape_remap_home(uVar5);
    }
    else {
      sStack_1c = sStack_1c + 0x4d;
    }
    iVar3 = 0;
    while (sVar7 = (short)iVar3, sVar7 < 8) {
      if (sVar7 < 4) {
        bVar15 = (&unk_c6db2)[sVar7 * 2];
        sVar9 = sVar7;
      }
      else {
        sVar9 = 7 - sVar7;
        bVar15 = *(byte *)(0xc6db9 - (sVar7 * 2 + -8));
      }
      set_text_colors(0x40,0x43);
      uVar10 = (ushort)bVar15;
      sprintf((char *)&uStack_54,(char *)&aC_c3add,
              *(int *)(&unk_c6dba + (&dword_dc7b8)[(short)uVar10] * 4) + 0x91);
      strcat((char *)&uStack_54,&unk_ddac4 + (&dword_dc7b8)[(short)uVar10] * 0x15);
      print_text_at(*(undefined4 *)(&unk_c6e22 + sVar9 * 2),(int)sStack_1c,&uStack_54);
      sVar7 = (&unk_c6e22)[sVar9 * 2];
      iVar3 = (&dword_dc7b8)[(short)uVar10];
      if ((((&dword_dc7b8)[byte_c6daa] == iVar3) || (iVar3 == (&dword_dc7b8)[byte_c6dab])) ||
         ((iVar3 == (&dword_dc7b8)[byte_c6dac] || (iVar3 == (&dword_dc7b8)[byte_c6dad])))) {
        uVar5 = 0xc4;
      }
      else {
        uVar5 = 0x40;
      }
      set_text_colors(uVar5,0x43);
      sprintf((char *)&uStack_54,(char *)&aD_c3ae1,
              *(undefined4 *)((int)auStack_10c + (short)uVar10 * 4));
      print_text_at((int)(short)(sVar7 + 0x6a),(int)sStack_1c,&uStack_54);
      if ((short)extraout_ECX_02 == 3) {
        sStack_1c = sStack_1c + 0x10;
      }
      iVar3 = extraout_ECX_02 + 1;
    }
    text_capture_stop();
    freemem(CONCAT22(uStack_1e,local_20));
    setfontstate(auStack_94);
  }
  else {
    setfont(uVar5);
    pcVar11 = aPlayoffsHaveNotBeenSeede_c3a79;
    puVar13 = &uStack_54;
    for (iVar3 = 8; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar13 = *(undefined4 *)pcVar11;
      pcVar11 = pcVar11 + ((uint)bVar15 * -2 + 1) * 4;
      puVar13 = puVar13 + (uint)bVar15 * -2 + 1;
    }
    *(undefined2 *)puVar13 = *(undefined2 *)pcVar11;
    iVar3 = textwidth(&uStack_54);
    print_outlined(0x140 - (iVar3 >> 1),0xf0,&uStack_54);
    setfont(uVar6);
  }
  return;
}


