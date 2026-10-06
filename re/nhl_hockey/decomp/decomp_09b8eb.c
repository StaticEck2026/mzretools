// Decompiled by Ghidra from hockey.elf (via ledisasm ELF export)
// This is machine generated pseudo-C meant as a reference for porting, it does not compile as is.
#include "prototypes.h"

// ================================================================================================
// __fill_buffer @ 0x9b8eb [__watcall]
// ================================================================================================

undefined8 __watcall __fill_buffer(undefined4 *param_1,undefined4 unaff_EDX)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  
  if (param_1[2] == 0) {
    __ioalloc();
  }
  if (((*(byte *)((int)param_1 + 0xd) & 0x20) != 0) && ((*(byte *)((int)param_1 + 0xd) & 6) != 0)) {
    __flushall(0x2000);
  }
  uVar1 = param_1[3];
  *param_1 = param_1[2];
  *(byte *)(param_1 + 3) = *(byte *)(param_1 + 3) & 0xfb;
  if (((uVar1 & 0x2400) == 0x2400) && (param_1[4] == 0)) {
    param_1[1] = 0;
    iVar2 = __getche_raw();
    if (iVar2 != -1) {
      *(char *)*param_1 = (char)iVar2;
      param_1[1] = 1;
    }
  }
  else {
    if ((*(byte *)((int)param_1 + 0xd) & 4) == 0) {
      uVar3 = param_1[5];
    }
    else {
      uVar3 = 1;
    }
    uVar3 = __qread(param_1[4],*param_1,uVar3);
    param_1[1] = uVar3;
  }
  if ((int)param_1[1] < 1) {
    if (param_1[1] == 0) {
      *(byte *)(param_1 + 3) = *(byte *)(param_1 + 3) | 0x10;
    }
    else {
      param_1[1] = 0;
      *(byte *)(param_1 + 3) = *(byte *)(param_1 + 3) | 0x20;
    }
  }
  return CONCAT44(unaff_EDX,param_1[1]);
}


// ================================================================================================
// ungetc @ 0x9b996 [__watcall]
// ================================================================================================

uint __watcall ungetc(uint param_1,int *unaff_EDX)

{
  int iVar1;
  undefined *puVar2;
  int *extraout_EDX;
  
  if (param_1 == 0xffffffff) {
    return 0xffffffff;
  }
  if (((*(byte *)((int)unaff_EDX + 0xd) & 0x10) == 0) && ((*(byte *)(unaff_EDX + 3) & 1) != 0)) {
    if (unaff_EDX[2] == 0) {
      __ioalloc(unaff_EDX);
      unaff_EDX = extraout_EDX;
    }
    if (unaff_EDX[1] == 0) {
      *unaff_EDX = unaff_EDX[2] + unaff_EDX[5] + -1;
      *(byte *)(unaff_EDX + 3) = *(byte *)(unaff_EDX + 3) | 4;
      puVar2 = (undefined *)*unaff_EDX;
      unaff_EDX[1] = 1;
    }
    else {
      if (*unaff_EDX == unaff_EDX[2]) goto LAB_0009b9aa;
      iVar1 = *unaff_EDX;
      unaff_EDX[1] = unaff_EDX[1] + 1;
      *unaff_EDX = iVar1 + -1;
      if (*(byte *)(iVar1 + -1) != param_1) {
        *(byte *)(unaff_EDX + 3) = *(byte *)(unaff_EDX + 3) | 4;
      }
      puVar2 = (undefined *)*unaff_EDX;
    }
    *puVar2 = (char)param_1;
    *(byte *)(unaff_EDX + 3) = *(byte *)(unaff_EDX + 3) & 0xef;
    param_1 = param_1 & 0xff;
  }
  else {
LAB_0009b9aa:
    param_1 = 0xffffffff;
  }
  return param_1;
}


// ================================================================================================
// __scnf @ 0x9ba18 [__cdecl]
// ================================================================================================

int __scnf(void)

{
  byte *pbVar1;
  byte bVar2;
  undefined4 *in_EAX;
  uint uVar3;
  int iVar4;
  char *pcVar5;
  byte *in_EDX;
  uint uVar6;
  byte *local_18;
  int local_14;
  
  local_14 = 0;
  *(byte *)(in_EAX + 4) = *(byte *)(in_EAX + 4) & 0xfd;
  local_18 = in_EDX;
  do {
    pbVar1 = local_18 + 1;
    uVar6 = (uint)*local_18;
    if (uVar6 == 0) goto LAB_0009bc1a;
    if (((&unk_c4b6c)[(byte)(*local_18 + 1)] & 2) == 0) {
      if (uVar6 == 0x25) {
        local_18 = (byte *)__scnf_getspec(pbVar1);
        bVar2 = *local_18;
        if (bVar2 != 0) {
          local_18 = local_18 + 1;
        }
        if (bVar2 < 0x65) {
          if (bVar2 < 0x58) {
            if (bVar2 < 0x45) {
              if ((bVar2 == 0x25) && (iVar4 = (*(code *)*in_EAX)(), iVar4 != 0x25))
              goto LAB_0009ba7b;
            }
            else if ((bVar2 < 0x46) || (bVar2 == 0x47)) goto LAB_0009bb8d;
          }
          else {
            if (bVar2 < 0x59) goto LAB_0009bb5e;
            if (bVar2 < 99) {
              if (bVar2 != 0x5b) goto LAB_0009bbe6;
              iVar4 = __scan_charlist();
            }
            else {
              if (99 < bVar2) goto LAB_0009bb5e;
              iVar4 = __scan_char();
            }
LAB_0009bbb9:
            if (iVar4 < 1) goto LAB_0009bc1a;
            if ((*(byte *)(in_EAX + 4) & 1) != 0) {
              local_14 = local_14 + 1;
            }
          }
        }
        else {
          if (bVar2 < 0x68) {
LAB_0009bb8d:
            iVar4 = __scan_float();
            goto LAB_0009bbb9;
          }
          if (bVar2 < 0x70) {
            if (bVar2 < 0x6e) {
              if (bVar2 == 0x69) goto LAB_0009bb5e;
            }
            else {
              if (0x6e < bVar2) {
LAB_0009bb5e:
                iVar4 = __scan_int();
                goto LAB_0009bbb9;
              }
              __report_scan();
            }
          }
          else {
            if (bVar2 < 0x71) goto LAB_0009bb5e;
            if (bVar2 < 0x75) {
              if (bVar2 == 0x73) {
                iVar4 = __scan_string();
                goto LAB_0009bbb9;
              }
            }
            else if ((bVar2 < 0x76) || (bVar2 == 0x78)) goto LAB_0009bb5e;
          }
        }
      }
      else {
        uVar3 = (*(code *)*in_EAX)();
        local_18 = pbVar1;
        if (uVar3 != uVar6) {
LAB_0009ba7b:
          if ((*(byte *)(in_EAX + 4) & 2) == 0) {
            (*(code *)in_EAX[1])();
          }
          goto LAB_0009bc1a;
        }
      }
    }
    else {
      __scan_white();
      local_18 = pbVar1;
    }
LAB_0009bbe6:
  } while ((*(byte *)(in_EAX + 4) & 2) == 0);
  if ((*local_18 == 0x25) && (pcVar5 = (char *)__scnf_getspec(local_18 + 1), *pcVar5 == 'n')) {
    __report_scan();
  }
LAB_0009bc1a:
  if ((local_14 == 0) && ((*(byte *)(in_EAX + 4) & 2) != 0)) {
    local_14 = -1;
  }
  return local_14;
}


// ================================================================================================
// __scnf_getspec @ 0x9bc3a [__watcall]
// ================================================================================================

byte * __watcall __scnf_getspec(byte *param_1,int unaff_EDX)

{
  byte bVar1;
  int iVar2;
  uint local_10;
  
  bVar1 = *(byte *)(unaff_EDX + 0x10);
  *(undefined4 *)(unaff_EDX + 0xc) = 0xffffffff;
  *(byte *)(unaff_EDX + 0x10) = bVar1 | 1;
  *(byte *)(unaff_EDX + 0x10) = bVar1 & 3 | 1;
  if (*param_1 == 0x2a) {
    param_1 = param_1 + 1;
    *(byte *)(unaff_EDX + 0x10) = *(byte *)(unaff_EDX + 0x10) & 0xfe;
  }
  bVar1 = *param_1;
  if (((&unk_c4b6c)[(byte)(bVar1 + 1)] & 0x20) != 0) {
    iVar2 = 0;
    do {
      local_10 = (uint)bVar1;
      param_1 = param_1 + 1;
      iVar2 = iVar2 * 10 + (local_10 - 0x30);
      bVar1 = *param_1;
    } while (((&unk_c4b6c)[(byte)(bVar1 + 1)] & 0x20) != 0);
    *(int *)(unaff_EDX + 0xc) = iVar2;
  }
  if (*param_1 == 0x4e) {
    *(byte *)(unaff_EDX + 0x10) = *(byte *)(unaff_EDX + 0x10) | 8;
    param_1 = param_1 + 1;
  }
  else if (*param_1 == 0x46) {
    *(byte *)(unaff_EDX + 0x10) = *(byte *)(unaff_EDX + 0x10) | 4;
    param_1 = param_1 + 1;
  }
  bVar1 = *param_1;
  if (bVar1 < 0x68) {
    if (bVar1 == 0x4c) {
      *(byte *)(unaff_EDX + 0x10) = *(byte *)(unaff_EDX + 0x10) | 0x40;
      param_1 = param_1 + 1;
    }
  }
  else if (bVar1 < 0x69) {
    *(byte *)(unaff_EDX + 0x10) = *(byte *)(unaff_EDX + 0x10) | 0x10;
    param_1 = param_1 + 1;
  }
  else if ((0x6b < bVar1) && ((bVar1 < 0x6d || (bVar1 == 0x77)))) {
    *(byte *)(unaff_EDX + 0x10) = *(byte *)(unaff_EDX + 0x10) | 0x20;
    param_1 = param_1 + 1;
  }
  return param_1;
}


// ================================================================================================
// __scan_white @ 0x9bd13 [__watcall]
// ================================================================================================

undefined8 __watcall __scan_white(undefined4 *param_1,undefined4 unaff_EDX)

{
  char cVar1;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 uVar2;
  
  do {
    cVar1 = (*(code *)*param_1)();
  } while (((&unk_c4b6c)[(byte)(cVar1 + 1)] & 2) != 0);
  uVar2 = extraout_ECX;
  if ((*(byte *)(param_1 + 4) & 2) == 0) {
    (*(code *)param_1[1])();
    uVar2 = extraout_ECX_00;
  }
  return CONCAT44(unaff_EDX,uVar2);
}


// ================================================================================================
// __scan_char @ 0x9bd48 [__watcall]
// ================================================================================================

int __watcall __scan_char(undefined4 *param_1,int *unaff_EDX)

{
  undefined2 uVar1;
  undefined2 *extraout_ECX;
  int iVar2;
  int extraout_EDX;
  int iVar3;
  
  if ((*(byte *)(param_1 + 4) & 1) != 0) {
    if ((*(byte *)(param_1 + 4) & 4) == 0) {
      if ((*(byte *)(param_1 + 4) & 8) == 0) {
        *unaff_EDX = *unaff_EDX + 4;
      }
      else {
        *unaff_EDX = *unaff_EDX + 4;
      }
    }
    else {
      *unaff_EDX = *unaff_EDX + 8;
    }
  }
  iVar2 = param_1[3];
  iVar3 = 0;
  if (iVar2 == -1) {
    iVar2 = 1;
  }
  while( true ) {
    if (iVar2 < 1) {
      return iVar3;
    }
    uVar1 = (*(code *)*param_1)();
    if ((*(byte *)(param_1 + 4) & 2) != 0) break;
    iVar3 = iVar3 + 1;
    iVar2 = extraout_EDX + -1;
    if ((*(byte *)(param_1 + 4) & 1) != 0) {
      if ((*(byte *)(param_1 + 4) & 0x20) == 0) {
        *(char *)extraout_ECX = (char)uVar1;
      }
      else {
        *extraout_ECX = uVar1;
      }
    }
  }
  return iVar3;
}


// ================================================================================================
// __scan_string @ 0x9bdce [__watcall]
// ================================================================================================

int __watcall __scan_string(undefined4 *param_1,int *unaff_EDX)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  undefined2 *extraout_ECX;
  undefined2 *puVar4;
  undefined2 *extraout_ECX_00;
  int iVar5;
  byte local_18;
  
  if ((*(byte *)(param_1 + 4) & 0x20) == 0) {
    local_18 = 1;
  }
  else {
    local_18 = 2;
  }
  bVar1 = *(byte *)(param_1 + 4);
  if ((bVar1 & 1) != 0) {
    if ((bVar1 & 4) == 0) {
      if ((bVar1 & 8) == 0) {
        *unaff_EDX = *unaff_EDX + 4;
      }
      else {
        *unaff_EDX = *unaff_EDX + 4;
      }
    }
    else {
      *unaff_EDX = *unaff_EDX + 8;
    }
  }
  iVar5 = 0;
  while( true ) {
    iVar3 = (*(code *)*param_1)();
    if (((&unk_c4b6c)[(byte)((char)iVar3 + 1)] & 2) == 0) break;
    iVar5 = iVar5 + 1;
  }
  puVar4 = extraout_ECX;
  if ((*(byte *)(param_1 + 4) & 2) == 0) {
    iVar2 = param_1[3];
    param_1[3] = iVar2 + -1;
    if (iVar2 != 0) {
      do {
        iVar5 = iVar5 + 1;
        if ((*(byte *)(param_1 + 4) & 1) != 0) {
          if (local_18 == 1) {
            *(char *)puVar4 = (char)iVar3;
          }
          else {
            *puVar4 = (short)iVar3;
          }
          puVar4 = (undefined2 *)((int)puVar4 + (uint)local_18);
        }
        iVar3 = __cgetw(param_1);
        if (iVar3 == -1) goto LAB_0009be96;
      } while (((&unk_c4b6c)[(byte)((char)iVar3 + 1)] & 2) == 0);
    }
    (*(code *)param_1[1])();
    puVar4 = extraout_ECX_00;
  }
  else {
    iVar5 = 0;
  }
LAB_0009be96:
  if (((*(byte *)(param_1 + 4) & 1) != 0) && (0 < iVar5)) {
    if (local_18 == 1) {
      *(undefined *)puVar4 = 0;
    }
    else {
      *puVar4 = 0;
    }
  }
  return iVar5;
}


// ================================================================================================
// __report_scan @ 0x9bebc [__watcall]
// ================================================================================================

void __watcall __report_scan(int param_1,int *unaff_EDX,undefined4 unaff_EBX)

{
  byte bVar1;
  undefined6 *puVar2;
  undefined4 *puVar3;
  
  bVar1 = *(byte *)(param_1 + 0x10);
  if ((bVar1 & 1) != 0) {
    if ((bVar1 & 4) == 0) {
      if ((bVar1 & 8) == 0) {
        puVar3 = (undefined4 *)*unaff_EDX;
        *unaff_EDX = (int)(puVar3 + 1);
        puVar3 = (undefined4 *)*puVar3;
      }
      else {
        puVar3 = (undefined4 *)*unaff_EDX;
        *unaff_EDX = (int)(puVar3 + 1);
        puVar3 = (undefined4 *)*puVar3;
      }
    }
    else {
      puVar2 = (undefined6 *)*unaff_EDX;
      *unaff_EDX = (int)(puVar2 + 1);
      puVar3 = (undefined4 *)*puVar2;
    }
    if ((*(byte *)(param_1 + 0x10) & 0x10) != 0) {
      *(short *)puVar3 = (short)unaff_EBX;
      return;
    }
    *puVar3 = unaff_EBX;
  }
  return;
}


// ================================================================================================
// __makelist @ 0x9bf1a [__watcall]
// ================================================================================================

byte * __watcall __makelist(byte *param_1,void *unaff_EDX)

{
  byte *pbVar1;
  uint uVar2;
  
  memset(unaff_EDX,0,0x20);
  uVar2 = (uint)*param_1;
  param_1 = param_1 + 1;
  if (uVar2 != 0) {
    do {
      pbVar1 = (byte *)(((int)uVar2 >> 3) + (int)unaff_EDX);
      *pbVar1 = *pbVar1 | (&unk_c4c78)[uVar2 & 7];
      uVar2 = (uint)*param_1;
      if (uVar2 == 0) {
        return param_1;
      }
      param_1 = param_1 + 1;
    } while (uVar2 != 0x5d);
  }
  return param_1;
}


// ================================================================================================
// __scan_charlist @ 0x9bf5d [__watcall]
// ================================================================================================

int __watcall __scan_charlist(undefined4 *param_1,int *unaff_EDX,undefined4 *unaff_EBX)

{
  byte bVar1;
  undefined6 *puVar2;
  undefined4 *puVar3;
  uint uVar4;
  undefined4 uVar5;
  uint uVar6;
  undefined4 *extraout_ECX;
  undefined4 *extraout_ECX_00;
  int iVar7;
  undefined *unaff_ESI;
  byte abStack_3c [32];
  uint local_1c;
  int local_18;
  
  local_1c = (uint)(*(char *)*unaff_EBX == '^');
  if (local_1c != 0) {
    *unaff_EBX = (char *)*unaff_EBX + 1;
  }
  uVar5 = __makelist(*unaff_EBX,abStack_3c);
  uVar4 = local_1c;
  *unaff_EBX = uVar5;
  bVar1 = *(byte *)(param_1 + 4);
  if ((bVar1 & 1) != 0) {
    if ((bVar1 & 4) == 0) {
      if ((bVar1 & 8) == 0) {
        puVar3 = (undefined4 *)*unaff_EDX;
        *unaff_EDX = (int)(puVar3 + 1);
        unaff_ESI = (undefined *)*puVar3;
      }
      else {
        puVar3 = (undefined4 *)*unaff_EDX;
        *unaff_EDX = (int)(puVar3 + 1);
        unaff_ESI = (undefined *)*puVar3;
      }
    }
    else {
      puVar2 = (undefined6 *)*unaff_EDX;
      *unaff_EDX = (int)(puVar2 + 1);
      unaff_ESI = (undefined *)*puVar2;
    }
  }
  iVar7 = param_1[3];
  local_18 = 0;
  do {
    if (iVar7 == 0) {
LAB_0009c025:
      if (((*(byte *)(param_1 + 4) & 1) != 0) && (0 < local_18)) {
        *unaff_ESI = 0;
      }
      return local_18;
    }
    uVar6 = (*(code *)*param_1)();
    param_1 = extraout_ECX;
    if ((*(byte *)(extraout_ECX + 4) & 2) != 0) goto LAB_0009c025;
    if (((abStack_3c[(int)uVar6 >> 3] & (&unk_c4c78)[uVar6 & 7]) == 0) != uVar4) {
      (*(code *)extraout_ECX[1])();
      param_1 = extraout_ECX_00;
      goto LAB_0009c025;
    }
    local_18 = local_18 + 1;
    iVar7 = iVar7 + -1;
    if ((*(byte *)(extraout_ECX + 4) & 1) != 0) {
      *unaff_ESI = (char)uVar6;
      unaff_ESI = unaff_ESI + 1;
    }
  } while( true );
}


// ================================================================================================
// __scan_float @ 0x9c043 [__watcall]
// ================================================================================================

int __watcall __scan_float(undefined4 *param_1,int *unaff_EDX)

{
  byte bVar1;
  undefined6 *puVar2;
  undefined4 *puVar3;
  bool bVar4;
  int iVar5;
  undefined4 *extraout_ECX;
  undefined4 *extraout_ECX_00;
  undefined4 *extraout_ECX_01;
  undefined4 *puVar6;
  int *piVar7;
  int iVar8;
  char *pcVar9;
  char *pcVar10;
  int iVar11;
  int iVar12;
  char local_88;
  char local_87 [79];
  int local_38;
  int local_34;
  undefined4 local_24;
  undefined2 local_20;
  short sStack_1e;
  
  pcVar10 = &local_88;
  iVar11 = 0;
  iVar8 = 0;
  while( true ) {
    iVar5 = (*(code *)*param_1)();
    if (((&unk_c4b6c)[(byte)((char)iVar5 + 1)] & 2) == 0) break;
    iVar8 = iVar8 + 1;
    param_1 = extraout_ECX;
  }
  puVar6 = extraout_ECX;
  if ((*(byte *)(extraout_ECX + 4) & 2) != 0) goto LAB_0009c263;
  iVar12 = extraout_ECX[3];
  extraout_ECX[3] = iVar12 + -1;
  pcVar10 = &local_88;
  if (iVar12 != 0) {
    if ((iVar5 == 0x2b) || (pcVar10 = &local_88, iVar5 == 0x2d)) {
      local_88 = (char)iVar5;
      iVar5 = __cgetw(extraout_ECX);
      pcVar10 = local_87;
      iVar8 = iVar8 + 1;
      if (iVar5 == -1) goto LAB_0009c263;
    }
    if ((((&unk_c4b6c)[(byte)((char)iVar5 + 1)] & 0x20) != 0) || (iVar5 == 0x2e)) {
      local_20 = 0;
      sStack_1e = 0;
      bVar4 = false;
      if (((&unk_c4b6c)[(byte)((char)iVar5 + 1)] & 0x20) != 0) {
        bVar4 = true;
        do {
          *pcVar10 = (char)iVar5;
          pcVar10 = pcVar10 + 1;
          if ((*(byte *)(extraout_ECX + 4) & 0x10) != 0) {
            sStack_1e = (short)iVar5 + sStack_1e * 10 + -0x30;
          }
          iVar11 = iVar11 + 1;
          iVar5 = __cgetw(extraout_ECX);
          if (iVar5 == -1) goto LAB_0009c263;
        } while (((&unk_c4b6c)[(byte)((char)iVar5 + 1)] & 0x20) != 0);
      }
      pcVar9 = pcVar10;
      iVar12 = iVar11;
      if (iVar5 == 0x2e) {
        *pcVar10 = '.';
        iVar5 = __cgetw(extraout_ECX);
        pcVar10 = pcVar10 + 1;
        if (iVar5 == -1) goto LAB_0009c263;
        if ((!bVar4) && (((&unk_c4b6c)[(byte)((char)iVar5 + 1)] & 0x20) == 0)) goto LAB_0009c25c;
        iVar11 = iVar11 + 1;
        do {
          if (((&unk_c4b6c)[(byte)((char)iVar5 + 1)] & 0x20) == 0) break;
          iVar11 = iVar11 + 1;
          *pcVar10 = (char)iVar5;
          iVar5 = __cgetw(extraout_ECX);
          pcVar10 = pcVar10 + 1;
        } while (iVar5 != -1);
        if ((*(byte *)(extraout_ECX + 4) & 0x10) != 0) {
          local_24 = 0;
          pcVar9 = pcVar10;
          while( true ) {
            pcVar9 = pcVar9 + -1;
            local_20 = (undefined2)local_24;
            if (*pcVar9 == '.') break;
            local_24 = (uint)CONCAT12(*pcVar9 + -0x30,(undefined2)local_24);
            local_24 = local_24 / 10;
          }
        }
        pcVar9 = pcVar10;
        iVar12 = iVar11;
        if (iVar5 == -1) goto LAB_0009c263;
      }
      pcVar10 = pcVar9;
      iVar11 = iVar12;
      if (((*(byte *)(extraout_ECX + 4) & 0x10) == 0) && ((iVar5 == 0x65 || (iVar5 == 0x45)))) {
        iVar11 = iVar12 + 1;
        *pcVar9 = (char)iVar5;
        iVar5 = __cgetw(extraout_ECX);
        pcVar10 = pcVar9 + 1;
        if (iVar5 == -1) goto LAB_0009c263;
        if ((iVar5 == 0x2b) || (iVar5 == 0x2d)) {
          iVar11 = iVar12 + 2;
          *pcVar10 = (char)iVar5;
          iVar5 = __cgetw(extraout_ECX);
          pcVar10 = pcVar9 + 2;
          if (iVar5 == -1) goto LAB_0009c263;
        }
        if (((&unk_c4b6c)[(byte)((char)iVar5 + 1)] & 0x20) == 0) {
          iVar11 = 0;
        }
        else {
          do {
            iVar11 = iVar11 + 1;
            *pcVar10 = (char)iVar5;
            iVar5 = __cgetw(extraout_ECX);
            pcVar10 = pcVar10 + 1;
            if (iVar5 == -1) goto LAB_0009c263;
          } while (((&unk_c4b6c)[(byte)((char)iVar5 + 1)] & 0x20) != 0);
        }
      }
    }
  }
LAB_0009c25c:
  (*(code *)extraout_ECX[1])();
  puVar6 = extraout_ECX_00;
LAB_0009c263:
  iVar5 = CONCAT22(sStack_1e,local_20);
  if ((0 < iVar11) && (iVar11 = iVar11 + iVar8, (*(byte *)(puVar6 + 4) & 1) != 0)) {
    *pcVar10 = '\0';
    if ((*(byte *)(puVar6 + 4) & 0x10) == 0) {
      (*(code *)funcptr_d566c)();
      puVar6 = extraout_ECX_01;
    }
    else {
      iVar5 = CONCAT22(sStack_1e,local_20);
      if (local_88 == '-') {
        iVar5 = -CONCAT22(sStack_1e,local_20);
      }
    }
    if ((*(byte *)(puVar6 + 4) & 4) == 0) {
      if ((*(byte *)(puVar6 + 4) & 8) == 0) {
        puVar3 = (undefined4 *)*unaff_EDX;
        *unaff_EDX = (int)(puVar3 + 1);
        piVar7 = (int *)*puVar3;
      }
      else {
        puVar3 = (undefined4 *)*unaff_EDX;
        *unaff_EDX = (int)(puVar3 + 1);
        piVar7 = (int *)*puVar3;
      }
    }
    else {
      puVar2 = (undefined6 *)*unaff_EDX;
      *unaff_EDX = (int)(puVar2 + 1);
      piVar7 = (int *)*puVar2;
    }
    bVar1 = *(byte *)(puVar6 + 4);
    if ((bVar1 & 0x10) == 0) {
      if (((bVar1 & 0x20) != 0) || ((bVar1 & 0x40) != 0)) {
        *piVar7 = local_38;
        piVar7[1] = local_34;
        return iVar11;
      }
      iVar5 = __FDFS(local_38,local_34);
    }
    *piVar7 = iVar5;
  }
  return iVar11;
}


// ================================================================================================
// __scan_int @ 0x9c321 [__watcall]
// ================================================================================================

int __watcall __scan_int(undefined4 *param_1,int *unaff_EDX,int unaff_EBX,int unaff_ECX)

{
  byte bVar1;
  undefined6 *puVar2;
  undefined4 *puVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  undefined8 uVar10;
  int local_20;
  int local_18;
  
  iVar8 = 0;
  iVar9 = 0;
  local_18 = 0;
  while( true ) {
    iVar4 = (*(code *)*param_1)();
    if (((&unk_c4b6c)[(byte)((char)iVar4 + 1)] & 2) == 0) break;
    iVar9 = iVar9 + 1;
  }
  if ((*(byte *)(param_1 + 4) & 2) == 0) {
    iVar5 = param_1[3];
    param_1[3] = iVar5 + -1;
    if (iVar5 == 0) {
LAB_0009c490:
      (*(code *)param_1[1])();
    }
    else {
      iVar7 = 0x2b;
      local_20 = 0x2b;
      iVar5 = iVar4;
      if ((unaff_ECX != 0) && ((iVar4 == 0x2b || (iVar4 == 0x2d)))) {
        iVar9 = iVar9 + 1;
        iVar5 = __cgetw(param_1);
        local_20 = iVar4;
        if (iVar5 == -1) goto LAB_0009c497;
      }
      if (unaff_EBX == 0) {
        if (iVar5 == 0x30) {
          iVar8 = 1;
          iVar7 = __cgetw(param_1);
          if (iVar7 == -1) goto LAB_0009c497;
          if ((iVar7 == 0x78) || (iVar7 == 0x58)) {
            iVar9 = iVar9 + 2;
            iVar5 = __cgetw(param_1,iVar7,1,iVar7);
            iVar8 = 0;
            if (iVar5 == -1) goto LAB_0009c497;
            unaff_EBX = 0x10;
          }
          else {
            unaff_EBX = 8;
            iVar5 = iVar7;
          }
        }
        else {
          unaff_EBX = 10;
        }
      }
      else if ((unaff_EBX == 0x10) && (iVar5 == 0x30)) {
        iVar8 = 1;
        iVar7 = __cgetw(param_1);
        if (iVar7 == -1) goto LAB_0009c497;
        if ((iVar7 == 0x78) || (iVar5 = iVar7, iVar7 == 0x58)) {
          iVar9 = iVar9 + 2;
          iVar5 = __cgetw(param_1,iVar7,1,iVar7);
          iVar8 = 0;
          goto LAB_0009c433;
        }
      }
      do {
        uVar10 = __radix_value(iVar5);
        if (unaff_EBX <= (int)uVar10) {
          if (((int)((ulonglong)uVar10 >> 0x20) != 0x3a) ||
             (iVar4 = 0x3a, (*(byte *)(param_1 + 4) & 0x80) == 0)) goto LAB_0009c490;
          goto LAB_0009c467;
        }
        iVar8 = iVar8 + 1;
        local_18 = local_18 * unaff_EBX + (int)uVar10;
        iVar5 = __cgetw(param_1,local_18,iVar8,iVar7);
LAB_0009c433:
      } while (iVar5 != -1);
    }
  }
LAB_0009c497:
  if (local_20 == 0x2d) {
    local_18 = -local_18;
  }
  if (0 < iVar8) {
    bVar1 = *(byte *)(param_1 + 4);
    iVar8 = iVar8 + iVar9;
    if ((bVar1 & 1) != 0) {
      if ((bVar1 & 4) == 0) {
        if ((bVar1 & 8) == 0) {
          puVar3 = (undefined4 *)*unaff_EDX;
          *unaff_EDX = (int)(puVar3 + 1);
          piVar6 = (int *)*puVar3;
        }
        else {
          puVar3 = (undefined4 *)*unaff_EDX;
          *unaff_EDX = (int)(puVar3 + 1);
          piVar6 = (int *)*puVar3;
        }
      }
      else {
        puVar2 = (undefined6 *)*unaff_EDX;
        *unaff_EDX = (int)(puVar2 + 1);
        piVar6 = (int *)*puVar2;
      }
      if ((*(byte *)(param_1 + 4) & 0x10) == 0) {
        *piVar6 = local_18;
      }
      else {
        *(short *)piVar6 = (short)local_18;
      }
    }
  }
  return iVar8;
LAB_0009c467:
  iVar8 = iVar8 + 1;
  iVar7 = __cgetw(param_1,iVar4,iVar8,iVar7);
  if (iVar7 == -1) goto LAB_0009c497;
  iVar4 = __radix_value(iVar7,iVar7);
  if (unaff_EBX <= iVar4) goto LAB_0009c490;
  iVar4 = local_18 * unaff_EBX + iVar4;
  local_18 = iVar4;
  goto LAB_0009c467;
}


// ================================================================================================
// __radix_value @ 0x9c519 [__watcall]
// ================================================================================================

int __watcall __radix_value(int param_1)

{
  int iVar1;
  
  if ((0x2f < param_1) && (param_1 < 0x3a)) {
    return param_1 + -0x30;
  }
  iVar1 = tolower();
  if ((0x60 < iVar1) && (iVar1 < 0x67)) {
    return iVar1 + -0x57;
  }
  return 0x10;
}


// ================================================================================================
// __cgetw @ 0x9c540 [__watcall]
// ================================================================================================

undefined8 __watcall __cgetw(undefined4 *param_1,undefined4 unaff_EDX,undefined4 unaff_EBX)

{
  int iVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  
  iVar1 = param_1[3];
  param_1[3] = iVar1 + -1;
  if (iVar1 != 0) {
    uVar3 = (*(code *)*param_1)(unaff_EDX,unaff_EBX);
    uVar2 = (undefined4)uVar3;
    if ((*(byte *)((int)((ulonglong)uVar3 >> 0x20) + 0x10) & 2) == 0) goto LAB_0009c560;
  }
  uVar2 = 0xffffffff;
LAB_0009c560:
  return CONCAT44(unaff_EDX,uVar2);
}


// ================================================================================================
// vsprintf_putc @ 0x9c563 [__watcall]
// ================================================================================================

void __watcall vsprintf_putc(int *param_1,undefined unaff_DL)

{
  undefined *puVar1;
  
  puVar1 = (undefined *)*param_1;
  *param_1 = (int)(puVar1 + 1);
  *puVar1 = unaff_DL;
  param_1[4] = param_1[4] + 1;
  return;
}


// ================================================================================================
// vsprintf @ 0x9c576 [__watcall]
// ================================================================================================

int __watcall vsprintf(char *__s,char *__format,__gnuc_va_list __arg)

{
  int iVar1;
  
  iVar1 = __prtf();
  __s[iVar1] = '\0';
  return iVar1;
}


// ================================================================================================
// vfprintf_alt @ 0x9c58c [__watcall]
// ================================================================================================

int __watcall vfprintf_alt(FILE *__s,char *__format,__gnuc_va_list __arg)

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
// toupper_ascii @ 0x9c594 [__cdecl]
// ================================================================================================

uint toupper_ascii(uint param_1)

{
  if ((0x60 < param_1) && (param_1 < 0x7b)) {
    param_1 = (uint)(byte)((char)param_1 - 0x20);
  }
  return param_1;
}


// ================================================================================================
// return_zero_9c5a8 @ 0x9c5a8 [__watcall]
// ================================================================================================

undefined4 __watcall return_zero_9c5a8(void)

{
  return 0;
}


// ================================================================================================
// palette_closest @ 0x9c5b0 [__cdecl]
// ================================================================================================

uint palette_closest(uint param_1)

{
  char *pcVar1;
  char *pcVar2;
  char cVar3;
  uint uVar4;
  char cVar5;
  char cVar7;
  int iVar6;
  int iVar8;
  int iVar9;
  uint unaff_EDI;
  char local_33c [768];
  int local_3c;
  int local_38;
  char local_34;
  char local_30;
  uint local_2f;
  undefined3 local_2b;
  char cStack_28;
  char local_24;
  byte local_20;
  byte local_1c;
  byte local_18;
  uint local_17;
  uint local_13;
  
  if (dword_d5068 == 0) {
    if (dword_d5064 == (char *)0x0) {
      getpalette(0,0x100,local_33c);
    }
    local_20 = (byte)(param_1 >> 0x12) & 0x3f;
    local_30 = local_20 + 4;
    local_18 = (byte)(param_1 >> 10) & 0x3f;
    local_24 = local_18 + 4;
    local_1c = (byte)(param_1 >> 2) & 0x3f;
    local_34 = local_1c + 4;
    iVar8 = 9;
    pcVar1 = dword_d5064;
    if (dword_d5064 == (char *)0x0) {
      pcVar1 = local_33c;
    }
    uVar4 = 0;
    do {
      if (((((&unk_d506c)[uVar4] != '\0') && ((byte)((local_18 + 4) - pcVar1[1]) < 9)) &&
          ((byte)((local_20 + 4) - *pcVar1) < 9)) && ((byte)((local_1c + 4) - pcVar1[2]) < 9)) {
        cVar5 = local_18 - pcVar1[1];
        if (cVar5 < '\0') {
          cVar5 = -cVar5;
        }
        cVar7 = local_20 - *pcVar1;
        if (cVar7 < '\0') {
          cVar7 = -cVar7;
        }
        cVar3 = local_1c - pcVar1[2];
        if (cVar3 < '\0') {
          cVar3 = -cVar3;
        }
        iVar6 = (int)cVar5 + (int)cVar7 + (int)cVar3;
        if ((iVar6 < iVar8) && (iVar8 = iVar6, unaff_EDI = uVar4, iVar6 == 0)) {
          return uVar4;
        }
      }
      pcVar1 = pcVar1 + 3;
      uVar4 = uVar4 + 1;
    } while ((int)uVar4 < 0x100);
    if (8 < iVar8) {
      local_13 = CONCAT13((char)(param_1 >> 0x12),(undefined3)local_13) & 0x3fffffff;
      local_17 = CONCAT13((char)(param_1 >> 10),(undefined3)local_17) & 0x3fffffff;
      local_2f = CONCAT13((char)(param_1 >> 2),(undefined3)local_2f) & 0x3fffffff;
      iVar8 = 9999;
      pcVar1 = dword_d5064;
      if (dword_d5064 == (char *)0x0) {
        pcVar1 = local_33c;
      }
      uVar4 = 0;
      do {
        cVar5 = *pcVar1;
        pcVar2 = pcVar1 + 1;
        cVar7 = pcVar1[2];
        _local_2b = CONCAT13(cVar7,local_2b);
        pcVar1 = pcVar1 + 3;
        if ((&unk_d506c)[uVar4] != '\0') {
          iVar6 = ((int)local_17 >> 0x18) - (int)*pcVar2;
          iVar9 = ((int)local_13 >> 0x18) - (int)cVar5;
          local_38 = iVar6 * iVar6 + iVar9 * iVar9;
          local_3c = (int)local_2f >> 0x18;
          iVar6 = ((int)local_2f >> 0x18) - (int)cVar7;
          local_38 = local_38 + iVar6 * iVar6;
          if ((local_38 < iVar8) && (((cVar5 != '\0' || (*pcVar2 != '\0')) || (cVar7 != '\0')))) {
            iVar8 = local_38;
            unaff_EDI = uVar4;
          }
        }
        uVar4 = uVar4 + 1;
      } while ((int)uVar4 < 0x100);
    }
  }
  else {
    unaff_EDI = (uint)*(byte *)(dword_d5068 +
                               ((param_1 & 0xff) >> 4 |
                               param_1 >> 8 & 0xf0 | ((param_1 >> 0x10 & 0xff) >> 4) << 8));
  }
  return unaff_EDI;
}


// ================================================================================================
// printstr2_centered @ 0x9c890 [__cdecl]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void printstr2_centered(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  
  iVar2 = _dword_d30b4 - dword_d30ac;
  iVar1 = textwidth(param_1);
  printstr2_at(param_1,(iVar2 - iVar1 >> 1) + dword_d30ac + 1,param_2);
  return;
}


// ================================================================================================
// shape_data_size @ 0x9c8d0 [__watcall]
// ================================================================================================

undefined8 __watcall shape_data_size(int param_1,undefined4 unaff_EDX)

{
  return CONCAT44(unaff_EDX,(*(int *)(param_1 + 4) >> 0x10) * (*(int *)(param_1 + 2) >> 0x10) + 0x10
                 );
}


// ================================================================================================
// unpackfile @ 0x9c8e8 [__watcall]
// ================================================================================================

void __watcall
unpackfile(undefined4 *param_1,int param_2,int param_3,uint param_4,int param_5,int param_6,
          int param_7,int param_8)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined8 uVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  
  puVar6 = (undefined4 *)0x0;
  if ((((((int)(char)*param_1 & 0x80U) != 0) || (param_7 != 0x10000)) || (param_8 != 0x10000)) ||
     (param_6 != 0)) {
    uVar5 = 0x20;
    uVar1 = shape_data_size(param_1);
    puVar2 = (undefined4 *)allocmem(aUnpackf,uVar1,uVar5);
    puVar6 = puVar2;
    if (((int)(char)*param_1 & 0x80U) == 0) {
      uVar4 = shape_data_size(param_1);
      memmove_dwords(param_1,(int)((ulonglong)uVar4 >> 0x20),(int)uVar4);
      param_1 = puVar2;
    }
    else {
      shape_unpack(param_1,puVar2,0);
      debug_printf(aUnpacking);
      param_1 = puVar2;
    }
  }
  if (param_4 != 0) {
    if (param_4 < 2) {
      iVar3 = fixmul16(param_7,*(int *)((int)param_1 + 6) >> 0x10);
      param_2 = param_2 - iVar3;
      iVar3 = fixmul16(param_8,(int)param_1[2] >> 0x10,puVar6,param_4,param_2);
      param_3 = param_3 - iVar3;
    }
    else if (param_4 == 2) {
      param_2 = param_2 + (*(int *)((int)param_1 + 10) >> 0x10);
      param_3 = param_3 + ((int)param_1[3] >> 0x10);
    }
  }
  if (param_7 < 0) {
    iVar3 = fixmul16(-param_7,*(int *)((int)param_1 + 2) >> 0x10);
    param_2 = param_2 - iVar3;
    shape_flip_h(param_1,puVar6,param_4,param_2);
  }
  if (param_8 < 0) {
    iVar3 = fixmul16(-param_8,(int)param_1[1] >> 0x10);
    param_3 = param_3 - iVar3;
    shape_flip_v(param_1);
  }
  if (param_6 != 0) {
    shape_recolor(param_1);
  }
  (*(code *)(&funcptr_d516c)[param_5])(param_1,param_2,param_3);
  if (puVar6 != (undefined4 *)0x0) {
    freemem(puVar6);
  }
  return;
}


// ================================================================================================
// drawshapex_xor @ 0x9ca6c [__cdecl]
// ================================================================================================

void drawshapex_xor(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  unpackfile(param_1,param_2,param_3,0,1,0,0x10000,0x10000);
  return;
}


// ================================================================================================
// drawshapex_xor_home @ 0x9ca90 [__watcall]
// ================================================================================================

void __watcall drawshapex_xor_home(void)

{
  undefined4 in_stack_00000004;
  
  unpackfile(in_stack_00000004,0,0,2,1,0,0x10000,0x10000);
  return;
}


// ================================================================================================
// drawshapex_xor_centered @ 0x9cab4 [__cdecl]
// ================================================================================================

void drawshapex_xor_centered(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  unpackfile(param_1,param_2,param_3,1,1,0,0x10000,0x10000);
  return;
}


// ================================================================================================
// drawshapex_xor_b @ 0x9cadc [__cdecl]
// ================================================================================================

void drawshapex_xor_b(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  unpackfile(param_1,param_2,param_3,0,1,0,0x10000,0x10000);
  return;
}


// ================================================================================================
// drawshapex_xor_home_b @ 0x9cb00 [__cdecl]
// ================================================================================================

void drawshapex_xor_home_b(undefined4 param_1)

{
  unpackfile(param_1,0,0,2,1,0,0x10000,0x10000);
  return;
}


// ================================================================================================
// drawshapex_xor_centered_b @ 0x9cb24 [__cdecl]
// ================================================================================================

void drawshapex_xor_centered_b(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  unpackfile(param_1,param_2,param_3,1,1,0,0x10000,0x10000);
  return;
}


// ================================================================================================
// drawshapex_xor_c @ 0x9cb4c [__cdecl]
// ================================================================================================

void drawshapex_xor_c(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  unpackfile(param_1,param_2,param_3,0,1,0,0x10000,0x10000);
  return;
}


// ================================================================================================
// drawshapex_xor_home_c @ 0x9cb70 [__cdecl]
// ================================================================================================

void drawshapex_xor_home_c(undefined4 param_1)

{
  unpackfile(param_1,0,0,2,1,0,0x10000,0x10000);
  return;
}


// ================================================================================================
// drawshapex_xor_centered_c @ 0x9cb94 [__cdecl]
// ================================================================================================

void drawshapex_xor_centered_c(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  unpackfile(param_1,param_2,param_3,1,1,0,0x10000,0x10000);
  return;
}


// ================================================================================================
// drawshapex_xor_d @ 0x9cbbc [__cdecl]
// ================================================================================================

void drawshapex_xor_d(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  unpackfile(param_1,param_2,param_3,0,1,0,0x10000,0x10000);
  return;
}


// ================================================================================================
// drawshapex_xor_home_d @ 0x9cbe0 [__cdecl]
// ================================================================================================

void drawshapex_xor_home_d(undefined4 param_1)

{
  unpackfile(param_1,0,0,2,1,0,0x10000,0x10000);
  return;
}


// ================================================================================================
// drawshapex_xor_centered_d @ 0x9cc04 [__cdecl]
// ================================================================================================

void drawshapex_xor_centered_d(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  unpackfile(param_1,param_2,param_3,1,1,0,0x10000,0x10000);
  return;
}


// ================================================================================================
// drawshapex_remap @ 0x9cc2c [__cdecl]
// ================================================================================================

void drawshapex_remap(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  unpackfile(param_1,param_2,param_3,0,2,0,0x10000,0x10000);
  return;
}


// ================================================================================================
// drawshapex_remap_home @ 0x9cc50 [__cdecl]
// ================================================================================================

void drawshapex_remap_home(undefined4 param_1)

{
  unpackfile(param_1,0,0,2,2,0,0x10000,0x10000);
  return;
}


// ================================================================================================
// drawshapex_remap_centered @ 0x9cc74 [__cdecl]
// ================================================================================================

void drawshapex_remap_centered(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  unpackfile(param_1,param_2,param_3,1,2,0,0x10000,0x10000);
  return;
}


// ================================================================================================
// drawshapex_remap_b @ 0x9cc9c [__cdecl]
// ================================================================================================

void drawshapex_remap_b(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  unpackfile(param_1,param_2,param_3,0,2,0,0x10000,0x10000);
  return;
}


// ================================================================================================
// drawshapex_remap_home_b @ 0x9ccc0 [__cdecl]
// ================================================================================================

void drawshapex_remap_home_b(undefined4 param_1)

{
  unpackfile(param_1,0,0,2,2,0,0x10000,0x10000);
  return;
}


// ================================================================================================
// drawshapex_remap_centered_b @ 0x9cce4 [__cdecl]
// ================================================================================================

void drawshapex_remap_centered_b(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  unpackfile(param_1,param_2,param_3,1,2,0,0x10000,0x10000);
  return;
}


// ================================================================================================
// drawshapex_xor_hflip @ 0x9cd0c [__cdecl]
// ================================================================================================

void drawshapex_xor_hflip(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  unpackfile(param_1,param_2,param_3,0,1,0,0xffff0000,0x10000);
  return;
}


// ================================================================================================
// drawshapex_xor_hflip_home @ 0x9cd30 [__cdecl]
// ================================================================================================

void drawshapex_xor_hflip_home(undefined4 param_1)

{
  unpackfile(param_1,0,0,2,1,0,0xffff0000,0x10000);
  return;
}


// ================================================================================================
// drawshapex_xor_hflip_centered @ 0x9cd54 [__cdecl]
// ================================================================================================

void drawshapex_xor_hflip_centered(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  unpackfile(param_1,param_2,param_3,1,1,0,0xffff0000,0x10000);
  return;
}


// ================================================================================================
// drawshapex_xor_hflip_b @ 0x9cd7c [__cdecl]
// ================================================================================================

void drawshapex_xor_hflip_b(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  unpackfile(param_1,param_2,param_3,0,1,0,0xffff0000,0x10000);
  return;
}


// ================================================================================================
// drawshapex_xor_hflip_home_b @ 0x9cda0 [__cdecl]
// ================================================================================================

void drawshapex_xor_hflip_home_b(undefined4 param_1)

{
  unpackfile(param_1,0,0,2,1,0,0xffff0000,0x10000);
  return;
}


// ================================================================================================
// drawshapex_xor_hflip_centered_b @ 0x9cdc4 [__cdecl]
// ================================================================================================

void drawshapex_xor_hflip_centered_b(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  unpackfile(param_1,param_2,param_3,1,1,0,0xffff0000,0x10000);
  return;
}


// ================================================================================================
// drawshapex_remap_hflip @ 0x9cdec [__cdecl]
// ================================================================================================

void drawshapex_remap_hflip(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  unpackfile(param_1,param_2,param_3,0,2,0,0xffff0000,0x10000);
  return;
}


// ================================================================================================
// drawshapex_remap_hflip_home @ 0x9ce10 [__cdecl]
// ================================================================================================

void drawshapex_remap_hflip_home(undefined4 param_1)

{
  unpackfile(param_1,0,0,2,2,0,0xffff0000,0x10000);
  return;
}


// ================================================================================================
// drawshapex_remap_hflip_centered @ 0x9ce34 [__cdecl]
// ================================================================================================

void drawshapex_remap_hflip_centered(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  unpackfile(param_1,param_2,param_3,1,2,0,0xffff0000,0x10000);
  return;
}


// ================================================================================================
// drawshapex_remap_hflip_b @ 0x9ce5c [__cdecl]
// ================================================================================================

void drawshapex_remap_hflip_b(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  unpackfile(param_1,param_2,param_3,0,2,0,0xffff0000,0x10000);
  return;
}


// ================================================================================================
// drawshapex_remap_hflip_home_b @ 0x9ce80 [__cdecl]
// ================================================================================================

void drawshapex_remap_hflip_home_b(undefined4 param_1)

{
  unpackfile(param_1,0,0,2,2,0,0xffff0000,0x10000);
  return;
}


// ================================================================================================
// drawshapex_remap_hflip_centered_b @ 0x9cea4 [__cdecl]
// ================================================================================================

void drawshapex_remap_hflip_centered_b(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  unpackfile(param_1,param_2,param_3,1,2,0,0xffff0000,0x10000);
  return;
}


// ================================================================================================
// drawshapex_xor_recolor @ 0x9cecc [__cdecl]
// ================================================================================================

void drawshapex_xor_recolor(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  unpackfile(param_1,param_2,param_3,0,1,1,0x10000,0x10000);
  return;
}


// ================================================================================================
// drawshapex_xor_recolor_home @ 0x9cef0 [__cdecl]
// ================================================================================================

void drawshapex_xor_recolor_home(undefined4 param_1)

{
  unpackfile(param_1,0,0,2,1,1,0x10000,0x10000);
  return;
}


// ================================================================================================
// drawshapex_xor_recolor_centered @ 0x9cf14 [__cdecl]
// ================================================================================================

void drawshapex_xor_recolor_centered(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  unpackfile(param_1,param_2,param_3,1,1,1,0x10000,0x10000);
  return;
}


// ================================================================================================
// drawshapex_xor_recolor_b @ 0x9cf3c [__cdecl]
// ================================================================================================

void drawshapex_xor_recolor_b(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  unpackfile(param_1,param_2,param_3,0,1,1,0x10000,0x10000);
  return;
}


// ================================================================================================
// drawshapex_xor_recolor_home_b @ 0x9cf60 [__cdecl]
// ================================================================================================

void drawshapex_xor_recolor_home_b(undefined4 param_1)

{
  unpackfile(param_1,0,0,2,1,1,0x10000,0x10000);
  return;
}


// ================================================================================================
// drawshapex_xor_recolor_centered_b @ 0x9cf84 [__cdecl]
// ================================================================================================

void drawshapex_xor_recolor_centered_b(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  unpackfile(param_1,param_2,param_3,1,1,1,0x10000,0x10000);
  return;
}


// ================================================================================================
// drawshapex_remap_recolor @ 0x9cfac [__cdecl]
// ================================================================================================

void drawshapex_remap_recolor(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  unpackfile(param_1,param_2,param_3,0,2,1,0x10000,0x10000);
  return;
}


// ================================================================================================
// drawshapex_remap_recolor_home @ 0x9cfd0 [__cdecl]
// ================================================================================================

void drawshapex_remap_recolor_home(undefined4 param_1)

{
  unpackfile(param_1,0,0,2,2,1,0x10000,0x10000);
  return;
}


// ================================================================================================
// drawshapex_remap_recolor_centered @ 0x9cff4 [__cdecl]
// ================================================================================================

void drawshapex_remap_recolor_centered(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  unpackfile(param_1,param_2,param_3,1,2,1,0x10000,0x10000);
  return;
}


// ================================================================================================
// drawshapex_remap_recolor_b @ 0x9d01c [__cdecl]
// ================================================================================================

void drawshapex_remap_recolor_b(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  unpackfile(param_1,param_2,param_3,0,2,1,0x10000,0x10000);
  return;
}


// ================================================================================================
// drawshapex_remap_recolor_home_b @ 0x9d040 [__cdecl]
// ================================================================================================

void drawshapex_remap_recolor_home_b(undefined4 param_1)

{
  unpackfile(param_1,0,0,2,2,1,0x10000,0x10000);
  return;
}


// ================================================================================================
// drawshapex_remap_recolor_centered_b @ 0x9d064 [__cdecl]
// ================================================================================================

void drawshapex_remap_recolor_centered_b(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  unpackfile(param_1,param_2,param_3,1,2,1,0x10000,0x10000);
  return;
}


// ================================================================================================
// save_screen_shape @ 0x9d090 [__cdecl]
// ================================================================================================

undefined4 save_screen_shape(char *param_1)

{
  char cVar1;
  uint uVar2;
  char *pcVar3;
  undefined4 *puVar4;
  uint *puVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  char *pcVar9;
  char *pcVar10;
  byte bVar11;
  undefined auStack_c8 [96];
  char local_68 [80];
  char *local_18;
  int local_14;
  int local_10;
  
  bVar11 = 0;
  uVar7 = (uint)(dword_d2f84 == 7);
  save_screen_state(auStack_c8);
  setdefaultscreen();
  local_10 = dword_d30c4 * dword_d30a8;
  if (dword_d2f84 == 7) {
    local_10 = local_10 * 2;
  }
  local_10 = local_10 + 0x340;
  uVar8 = 0;
  local_14 = reservemem_try(s_voSHAPE_000c4931 + 3,local_10,0x20);
  if (local_14 != 0) {
    pcVar3 = (char *)memblock_ptr(local_14);
    local_18 = pcVar3;
    strncpy(pcVar3,(char *)(&off_d518c)[uVar7],4);
    *(int *)(pcVar3 + 4) = local_10;
    pcVar3[8] = '\x02';
    pcVar3[9] = '\0';
    pcVar3[10] = '\0';
    pcVar3[0xb] = '\0';
    strncpy(pcVar3 + 0xc,(char *)&aSnap,4);
    strncpy(pcVar3 + 0x10,(char *)&aPal_c4944,4);
    pcVar3[0x14] = ' ';
    pcVar3[0x15] = '\0';
    pcVar3[0x16] = '\0';
    pcVar3[0x17] = '\0';
    strncpy(pcVar3 + 0x18,(char *)&aSnap_c494c,4);
    pcVar3[0x1c] = '0';
    pcVar3[0x1d] = '\x03';
    pcVar3[0x1e] = '\0';
    pcVar3[0x1f] = '\0';
    puVar4 = (undefined4 *)locateshape(pcVar3,&aPal_c4944);
    *puVar4 = 0x22;
    *(undefined2 *)(puVar4 + 1) = 0x100;
    *(undefined2 *)((int)puVar4 + 6) = 3;
    *(undefined2 *)(puVar4 + 2) = 0x100;
    *(undefined2 *)((int)puVar4 + 10) = 0;
    *(undefined2 *)(puVar4 + 3) = 0;
    *(undefined2 *)((int)puVar4 + 0xe) = 0;
    getpalette(0,0x100,puVar4 + 4);
    puVar5 = (uint *)locateshape(pcVar3,&aSnap_c494c);
    uVar2 = *(uint *)(&unk_d5184 + uVar7 * 4);
    *(undefined *)puVar5 = 0;
    *puVar5 = *puVar5 & 0xff | uVar2 & 0xff;
    *(undefined2 *)(puVar5 + 1) = (undefined2)dword_d30a4;
    *(undefined2 *)((int)puVar5 + 6) = (undefined2)dword_d30a8;
    *(undefined2 *)(puVar5 + 2) = 0;
    *(undefined2 *)((int)puVar5 + 10) = 0;
    *(undefined2 *)(puVar5 + 3) = 0;
    *(undefined2 *)((int)puVar5 + 0xe) = 0;
    grabshape_home(puVar5);
    pcVar3 = local_68;
    do {
      cVar1 = *param_1;
      *pcVar3 = cVar1;
      if (cVar1 == '\0') break;
      cVar1 = param_1[1];
      param_1 = param_1 + 2;
      pcVar3[1] = cVar1;
      pcVar3 = pcVar3 + 2;
    } while (cVar1 != '\0');
    pcVar3 = local_68;
    do {
      pcVar9 = pcVar3;
      if (*pcVar3 == '.') goto LAB_0009d269;
      if (*pcVar3 == '\0') break;
      pcVar9 = pcVar3 + 1;
      if (*pcVar9 == '.') goto LAB_0009d269;
      pcVar3 = pcVar3 + 2;
    } while (*pcVar9 != '\0');
    pcVar9 = (char *)0x0;
LAB_0009d269:
    if (pcVar9 == (char *)0x0) {
      pcVar3 = (char *)(&off_d517c)[uVar7];
      iVar6 = -1;
      pcVar9 = local_68;
      do {
        pcVar10 = pcVar9;
        if (iVar6 == 0) break;
        iVar6 = iVar6 + -1;
        pcVar10 = pcVar9 + (uint)bVar11 * -2 + 1;
        cVar1 = *pcVar9;
        pcVar9 = pcVar10;
      } while (cVar1 != '\0');
      pcVar10 = pcVar10 + -1;
      do {
        cVar1 = *pcVar3;
        *pcVar10 = cVar1;
        if (cVar1 == '\0') break;
        cVar1 = pcVar3[1];
        pcVar3 = pcVar3 + 2;
        pcVar10[1] = cVar1;
        pcVar10 = pcVar10 + 2;
      } while (cVar1 != '\0');
    }
    uVar8 = savefileblock_try(local_68,local_18,local_10);
    releasememblock(local_14);
  }
  restore_screen_state(auStack_c8);
  return uVar8;
}


// ================================================================================================
// window_select @ 0x9d2e0 [__cdecl]
// ================================================================================================

int window_select(int *param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = *param_1;
  if (iVar1 != 0) {
    uVar2 = identity_8e3c4(iVar1 + 0x30);
    *(undefined4 *)(iVar1 + 0x2c) = uVar2;
    setscreen(iVar1);
  }
  return iVar1;
}


// ================================================================================================
// __setEFGfmt @ 0x9d307 [__watcall]
// ================================================================================================

void __watcall __setEFGfmt(void)

{
  funcptr_d5668 = _EFG_Format;
  funcptr_d566c = __cnvs2d;
  return;
}


// ================================================================================================
// FUN_0009d322 @ 0x9d322
// ================================================================================================

/* WARNING: Removing unreachable block (ram,0x0009d332) */

longdouble FUN_0009d322(void)

{
  int unaff_EBP;
  
  if (unaff_EBP != 0) {
    FUN_0009d352();
  }
  return (longdouble)0;
}


// ================================================================================================
// FUN_0009d352 @ 0x9d352
// ================================================================================================

void FUN_0009d352(void)

{
  undefined4 uVar1;
  code *pcVar2;
  int iVar3;
  char cVar4;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 in_EDX;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  ushort uVar5;
  ushort in_CR0;
  undefined2 uStack_6;
  undefined2 uStack_4;
  
  byte_d4b9c = 3;
  byte_d51dc = 1;
  word_d51da = in_CR0 & 6;
  uVar1 = InterruptDescriptorTableRegister();
  uStack_6 = (undefined2)((uint)uVar1 >> 0x10);
  iVar3 = CONCAT22(uStack_4,uStack_6);
  if (byte_d4d08 == '\0') {
    if (byte_d4d06 == '\0') {
      pcVar2 = (code *)swi(0x21);
      (*pcVar2)();
      pcVar2 = (code *)swi(0x21);
      (*pcVar2)();
    }
    else if (byte_d4d06 == '\t') {
      FUN_0009d41d();
      *(undefined4 *)(iVar3 + 0x38) = extraout_EDX_00;
      *(undefined4 *)(iVar3 + 0x3c) = extraout_ECX_00;
      (**(code **)(dword_d41f4 + 0x30))();
    }
    else {
      uVar5 = (ushort)((uint)in_EDX >> 0x10);
      if (byte_d4d06 == '\x01') {
        __init_387_emulator(0,CONCAT22(uVar5,word_d41f8));
      }
      else {
        cVar4 = __init_387_emulator(0,(uint)uVar5 << 0x10);
        if (cVar4 != '\x01') {
          FUN_0009d43a();
        }
      }
    }
  }
  else {
    FUN_0009d41d();
    *(undefined4 *)(iVar3 + 0x38) = extraout_EDX;
    *(undefined4 *)(iVar3 + 0x3c) = extraout_ECX;
    _set_EM_MP_bits();
  }
  return;
}


// ================================================================================================
// FUN_0009d41d @ 0x9d41d
// ================================================================================================

void FUN_0009d41d(void)

{
  return;
}


// ================================================================================================
// FUN_0009d43a @ 0x9d43a
// ================================================================================================

void FUN_0009d43a(void)

{
  code *pcVar1;
  undefined4 unaff_EBX;
  undefined2 in_ES;
  
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  dword_d51d4 = unaff_EBX;
  word_d51d8 = in_ES;
  if (byte_d4d06 < '\x03') {
    pcVar1 = (code *)swi(0x21);
    (*pcVar1)();
  }
  else {
    pcVar1 = (code *)swi(0x21);
    (*pcVar1)();
    _set_EM_MP_bits();
  }
  return;
}


// ================================================================================================
// _set_EM_MP_bits @ 0x9d487 [__watcall]
// ================================================================================================

void __watcall _set_EM_MP_bits(void)

{
  code *pcVar1;
  
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  dword_d5194 = dword_d5194 & 0xfffffffd | 4;
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  return;
}


// ================================================================================================
// __fini_387_emulator @ 0x9d4a7 [__watcall]
// ================================================================================================

void __watcall
__fini_387_emulator(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

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
// __fini_387_emulator_body @ 0x9d4b1 [__watcall]
// ================================================================================================

void __watcall
__fini_387_emulator_body(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  code *pcVar1;
  char cVar2;
  
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
// unhook_pharlap @ 0x9d521 [__watcall]
// ================================================================================================

void __watcall unhook_pharlap(void)

{
  code *pcVar1;
  
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  if ('\x02' < byte_d4d06) {
    _reset_EM_MP_bits();
  }
  return;
}


// ================================================================================================
// _reset_EM_MP_bits @ 0x9d55c [__watcall]
// ================================================================================================

void __watcall _reset_EM_MP_bits(void)

{
  code *pcVar1;
  
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  dword_d5194 = (uint)word_d51da;
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  return;
}


// ================================================================================================
// unk_9d57d @ 0x9d57d
// ================================================================================================

void unk_9d57d(void)

{
  undefined2 *in_EAX;
  undefined2 in_FPUControlWord;
  undefined2 in_FPUStatusWord;
  undefined2 in_FPUTagWord;
  undefined2 in_FPULastInstructionOpcode;
  undefined4 in_FPUDataPointer;
  undefined4 in_FPUInstructionPointer;
  unkbyte10 in_ST0;
  unkbyte10 in_ST1;
  unkbyte10 in_ST2;
  unkbyte10 in_ST3;
  unkbyte10 in_ST4;
  unkbyte10 in_ST5;
  unkbyte10 in_ST6;
  unkbyte10 in_ST7;
  
  *in_EAX = in_FPUControlWord;
  in_EAX[2] = in_FPUStatusWord;
  in_EAX[4] = in_FPUTagWord;
  *(undefined4 *)(in_EAX + 10) = in_FPUDataPointer;
  *(undefined4 *)(in_EAX + 6) = in_FPUInstructionPointer;
  in_EAX[9] = in_FPULastInstructionOpcode;
  *(unkbyte10 *)(in_EAX + 0xe) = in_ST0;
  *(unkbyte10 *)(in_EAX + 0x13) = in_ST1;
  *(unkbyte10 *)(in_EAX + 0x18) = in_ST2;
  *(unkbyte10 *)(in_EAX + 0x1d) = in_ST3;
  *(unkbyte10 *)(in_EAX + 0x22) = in_ST4;
  *(unkbyte10 *)(in_EAX + 0x27) = in_ST5;
  *(unkbyte10 *)(in_EAX + 0x2c) = in_ST6;
  *(unkbyte10 *)(in_EAX + 0x31) = in_ST7;
  return;
}


// ================================================================================================
// unk_9d582 @ 0x9d582
// ================================================================================================

unkbyte10 unk_9d582(void)

{
  int in_EAX;
  
  return *(unkbyte10 *)(in_EAX + 0x1c);
}


// ================================================================================================
// __init_8087 @ 0x9d586 [__watcall]
// ================================================================================================

void __watcall __init_8087(void)

{
  if (byte_d4b9d != '\0') {
    funcptr_d6600 = unk_9d57d;
    funcptr_d6604 = unk_9d582;
  }
  __get_fpu_cw(word_d65fc);
  return;
}


// ================================================================================================
// __reinit_8087 @ 0x9d5b7 [__watcall]
// ================================================================================================

void __watcall __reinit_8087(void)

{
  if (byte_d4b9d == '\0') {
    return;
  }
  if (byte_d4b9d != '\0') {
    funcptr_d6600 = unk_9d57d;
    funcptr_d6604 = unk_9d582;
  }
  __get_fpu_cw(word_d65fc);
  return;
}


// ================================================================================================
// __chk8087 @ 0x9d5c1 [__watcall]
// ================================================================================================

void __watcall __chk8087(void)

{
  char cVar1;
  
  if (byte_d4b9c == '\0') {
    byte_d4b9d = byte_d4b9c;
    cVar1 = __init_8087();
    if (word_d4d04 == '\0') {
      byte_d4b9c = cVar1;
      byte_d4b9d = cVar1;
    }
  }
  return;
}


// ================================================================================================
// calibrate_delay_loop @ 0x9d601 [__watcall]
// ================================================================================================

void __watcall calibrate_delay_loop(void)

{
  code *pcVar1;
  char extraout_DH;
  char extraout_DH_00;
  char extraout_DH_01;
  int iVar2;
  
  pcVar1 = (code *)swi(0x21);
  (*pcVar1)();
  do {
    pcVar1 = (code *)swi(0x21);
    (*pcVar1)();
  } while (extraout_DH == extraout_DH_00);
  iVar2 = 0;
  do {
    pcVar1 = (code *)swi(0x21);
    (*pcVar1)();
    iVar2 = iVar2 + 1;
  } while (extraout_DH_00 == extraout_DH_01);
  dword_f24cc = iVar2;
  return;
}


// ================================================================================================
// delay_loop @ 0x9d633 [__watcall]
// ================================================================================================

void __watcall delay_loop(int param_1)

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
// __get_errno_ptr @ 0x9d66b [__watcall]
// ================================================================================================

undefined * __watcall __get_errno_ptr(void)

{
  return &unk_f24d4;
}


// ================================================================================================
// __get_doserrno_ptr @ 0x9d671 [__watcall]
// ================================================================================================

undefined * __watcall __get_doserrno_ptr(void)

{
  return &unk_f24d0;
}


// ================================================================================================
// strerror @ 0x9d677 [__watcall]
// ================================================================================================

char * __watcall strerror(int param_1)

{
  if ((-1 < param_1) && (param_1 < 0x10)) {
    return (&off_d51e4)[param_1];
  }
  return aUnknownError;
}


// ================================================================================================
// stackavail @ 0x9d68e [__watcall]
// ================================================================================================

int __watcall stackavail(void)

{
  return (int)&stack0x00000000 - dword_d4ce8;
}


// ================================================================================================
// pcspk_drv_init @ 0x9d698 [__watcall]
// ================================================================================================

void __watcall pcspk_drv_init(void)

{
  short sVar1;
  
  empty_func_902a0();
  for (sVar1 = 0; sVar1 < 0x10; sVar1 = sVar1 + 1) {
    (&unk_f24d9)[sVar1 * 0x30] = 0;
  }
  for (sVar1 = 0; sVar1 < 0x18; sVar1 = sVar1 + 1) {
    (&unk_f27ee)[sVar1 * 0x4e] = 0;
    (&unk_f27ef)[sVar1 * 0x4e] = 0x10;
  }
  pcspk_hw_init();
  return;
}


// ================================================================================================
// pcspk_drv_shutdown @ 0x9d6e6 [__watcall]
// ================================================================================================

void __watcall pcspk_drv_shutdown(void)

{
  empty_func_902a0();
  pcspk_hw_shutdown();
  return;
}


// ================================================================================================
// pcspk_drv_tick @ 0x9d6f3 [__watcall]
// ================================================================================================

void __watcall pcspk_drv_tick(void)

{
  empty_func_902a0();
  pcspk_update_voices();
  return;
}


// ================================================================================================
// pcspk_note_on @ 0x9d700 [__cdecl]
// ================================================================================================

void pcspk_note_on(byte param_1,char param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined8 uVar5;
  
  empty_func_902a0();
  iVar1 = (uint)param_1 * 0x4e;
  if (param_1 == 9) {
    iVar2 = snd_patch_timbre();
    param_2 = '<';
  }
  else {
    iVar2 = *(int *)(&unk_f27f6 + iVar1);
  }
  if (iVar2 != 0) {
    uVar5 = timbre_env_sign(iVar2);
    iVar4 = (int)((ulonglong)uVar5 >> 0x20);
    iVar2 = (int)(short)uVar5;
    if (iVar2 != -1) {
      iVar3 = iVar2 * 0x30;
      (&DAT_000f24e8)[iVar2 * 0xc] = iVar4;
      (&unk_f24d8)[iVar3] = param_1;
      (&DAT_000f2502)[iVar2 * 0xc] = &unk_f27d8 + iVar1;
      (&unk_f24d9)[iVar3] = 1;
      (&DAT_000f24ee)[iVar3] = 1;
      (&DAT_000f24ec)[iVar2 * 0x18] = *(undefined2 *)((&DAT_000f24e8)[iVar2 * 0xc] + 0x1c);
      (&DAT_000f24da)[iVar3] = (&DAT_000f27fc)[iVar1];
      (&DAT_000f24e0)[iVar2 * 0xc] = 0;
      *(undefined4 *)(&DAT_000f24e4 + iVar3) = 100;
      (&DAT_000f24f0)[iVar2 * 0x18] = *(undefined2 *)(iVar4 + 0x2a);
      (&DAT_000f24f2)[iVar2 * 0x18] = *(undefined2 *)(iVar4 + 0x2c);
      (&DAT_000f24fc)[iVar2 * 0x18] = *(undefined2 *)(iVar4 + 0x30);
      (&DAT_000f24f4)[iVar2 * 0x18] = 0;
      (&DAT_000f24fe)[iVar3] = *(undefined *)(iVar4 + 0x34);
      (&DAT_000f24ff)[iVar3] = 0;
      (&DAT_000f24f6)[iVar2 * 0x18] = *(undefined2 *)(iVar4 + 0x36);
      (&DAT_000f24f8)[iVar2 * 0x18] = *(undefined2 *)(iVar4 + 0x38);
      (&DAT_000f2500)[iVar3] = 0;
      (&DAT_000f24fa)[iVar3] = 0;
      (&DAT_000f2501)[iVar3] = 0;
      (&DAT_000f2506)[iVar3] = (char)uVar5;
      pcspk_hw_voice_on((uint)uVar5 & 0xff,&unk_f24d8 + iVar3,(int)(char)(param_2 + *(char *)(iVar4 + 0x10))
               );
    }
  }
  return;
}


// ================================================================================================
// pcspk_note_off @ 0x9d805 [__cdecl]
// ================================================================================================

void pcspk_note_off(byte param_1,char param_2)

{
  short sVar1;
  
  empty_func_902a0();
  sVar1 = 0;
  while ((sVar1 < 0x10 &&
         (((unk_f24d9 == '\0' || (param_2 != DAT_000f24db)) || (param_1 != unk_f24d8))))) {
    sVar1 = sVar1 + 1;
  }
  if (sVar1 < 0x10) {
    unk_f24d9 = '\x02';
    if ((&unk_f27fd)[(uint)unk_f24d8 * 0x4e] != '\0') {
      DAT_000f24ee = 3;
      return;
    }
    DAT_000f24ee = 4;
  }
  return;
}


// ================================================================================================
// pcspk_program @ 0x9d858 [__cdecl]
// ================================================================================================

void pcspk_program(byte param_1)

{
  undefined4 uVar1;
  
  empty_func_902a0();
  uVar1 = snd_patch_timbre();
  *(undefined4 *)(&unk_f27f6 + (uint)param_1 * 0x4e) = uVar1;
  return;
}


// ================================================================================================
// pcspk_update_voices @ 0x9d880 [__watcall]
// ================================================================================================

void __watcall pcspk_update_voices(void)

{
  int iVar1;
  ushort uVar2;
  uint uVar3;
  short sVar4;
  short sVar5;
  byte *pbVar6;
  undefined8 uVar7;
  
  pbVar6 = &unk_f24d8;
  uVar2 = 0;
  do {
    if (byte_d5224 <= uVar2) {
      pcspk_hw_update();
      return;
    }
    if (pbVar6[1] != 0) {
      *(int *)(pbVar6 + 8) = *(int *)(pbVar6 + 8) + 1;
      iVar1 = *(int *)(pbVar6 + 0x10);
      if (pbVar6[0x16] == 1) {
        sVar4 = *(short *)(pbVar6 + 0x14) + *(short *)(iVar1 + 0x20);
        *(short *)(pbVar6 + 0x14) = sVar4;
        sVar5 = *(short *)(iVar1 + 0x1e);
        if (sVar5 <= sVar4) {
          *(short *)(pbVar6 + 0x14) = sVar5;
          if (*(short *)(iVar1 + 0x24) < sVar5) {
            pbVar6[0x16] = 2;
          }
          else {
            pbVar6[0x16] = 3;
          }
        }
      }
      if (pbVar6[0x16] == 2) {
        sVar5 = *(short *)(pbVar6 + 0x14) - *(short *)(iVar1 + 0x22);
        *(short *)(pbVar6 + 0x14) = sVar5;
        if (sVar5 <= *(short *)(iVar1 + 0x24)) {
          pbVar6[0x16] = 3;
          *(undefined2 *)(pbVar6 + 0x14) = *(undefined2 *)(iVar1 + 0x24);
        }
      }
      if ((pbVar6[0x16] == 3) && (*(short *)(iVar1 + 0x24) == 0)) {
        pbVar6[0x16] = 4;
      }
      if (pbVar6[0x16] == 4) {
        sVar5 = *(short *)(pbVar6 + 0x14) - *(short *)(iVar1 + 0x26);
        *(short *)(pbVar6 + 0x14) = sVar5;
        if (sVar5 < 1) {
          pbVar6[0x14] = 0;
          pbVar6[0x15] = 0;
          pbVar6[0x16] = 0;
          pbVar6[1] = 0;
          (&unk_f27ee)[(uint)*pbVar6 * 0x4e] = (&unk_f27ee)[(uint)*pbVar6 * 0x4e] + -1;
          pcspk_hw_voice_off(pbVar6[0x2e]);
        }
      }
      if (*(char *)(iVar1 + 0x28) != '\0') {
        if (*(short *)(pbVar6 + 0x18) == 0) {
          sVar5 = *(short *)(pbVar6 + 0x1a);
          if (sVar5 != 0) {
            if (sVar5 != 0x7fff) {
              *(short *)(pbVar6 + 0x1a) = sVar5 + -1;
            }
            if (pbVar6[0x27] == 0) {
              pbVar6[0x27] = *(byte *)(iVar1 + 0x29);
              if (pbVar6[0x26] == 2) {
                *(short *)(pbVar6 + 0x1c) = *(short *)(pbVar6 + 0x1c) - *(short *)(pbVar6 + 0x24);
                uVar7 = abs((int)*(short *)(pbVar6 + 0x1c),*(undefined2 *)(iVar1 + 0x2e));
                if ((int)((ulonglong)uVar7 >> 0x20) <= (int)uVar7) {
                  if ((*(byte *)(iVar1 + 0x34) & 1) == 0) {
LAB_0009d9c8:
                    pbVar6[0x1c] = 0;
                    pbVar6[0x1d] = 0;
                  }
                  else {
                    pbVar6[0x26] = 1;
                  }
                }
              }
              else {
                sVar5 = *(short *)(pbVar6 + 0x1c);
                *(short *)(pbVar6 + 0x1c) = sVar5 + *(short *)(pbVar6 + 0x24);
                uVar7 = abs((int)(short)(sVar5 + *(short *)(pbVar6 + 0x24)),
                                  *(undefined2 *)(iVar1 + 0x2e));
                if ((int)((ulonglong)uVar7 >> 0x20) <= (int)uVar7) {
                  if ((*(byte *)(iVar1 + 0x34) & 2) == 0) goto LAB_0009d9c8;
                  pbVar6[0x26] = 2;
                }
              }
            }
            else {
              pbVar6[0x27] = pbVar6[0x27] - 1;
            }
          }
        }
        else {
          *(short *)(pbVar6 + 0x18) = *(short *)(pbVar6 + 0x18) + -1;
        }
      }
      if (*(char *)(iVar1 + 0x35) != '\0') {
        if (*(short *)(pbVar6 + 0x1e) == 0) {
          if (*(short *)(pbVar6 + 0x20) != 0) {
            *(short *)(pbVar6 + 0x20) = *(short *)(pbVar6 + 0x20) + -1;
            if (pbVar6[0x28] == 0) {
              pbVar6[0x28] = *(byte *)(iVar1 + 0x3a);
              uVar3 = CONCAT11(pbVar6[0x29],pbVar6[0x29]) & 0xffff07ff;
              pbVar6[0x29] = (char)uVar3 + 1;
              pbVar6[0x22] = *(byte *)((uVar3 >> 8) + 0x3b + iVar1);
            }
            else {
              pbVar6[0x28] = pbVar6[0x28] - 1;
            }
          }
        }
        else {
          *(short *)(pbVar6 + 0x1e) = *(short *)(pbVar6 + 0x1e) + -1;
        }
      }
      pcspk_hw_voice_pitch(pbVar6[0x2e],pbVar6,*(undefined4 *)(pbVar6 + 0x2a),*(undefined4 *)(pbVar6 + 0x10));
    }
    pbVar6 = pbVar6 + 0x30;
    uVar2 = uVar2 + 1;
  } while( true );
}


// ================================================================================================
// timbre_env_sign @ 0x9da99 [__watcall]
// ================================================================================================

undefined4 __watcall timbre_env_sign(int param_1)

{
  if (*(short *)(param_1 + 0xc) == 0) {
    return 0xffffffff;
  }
  return 1;
}


// ================================================================================================
// pcspk_drv_send_midi @ 0x9daac [__watcall]
// ================================================================================================

void __watcall pcspk_drv_send_midi(void)

{
  ushort uVar1;
  byte bVar2;
  int iVar3;
  byte *pbVar4;
  int in_stack_00000004;
  byte *in_stack_00000008;
  byte local_40;
  byte *local_3c;
  byte *local_34;
  byte local_20;
  byte local_1c;
  byte local_14;
  
  empty_func_902a0();
  iVar3 = dword_d4f9a;
  local_1c = 0xc0;
  local_20 = 1;
  local_14 = 0;
  uVar1 = 0;
  pbVar4 = &unk_f21fc + dword_d4f9a;
  dword_d4f9a = dword_d4f9a + 4;
  local_34 = in_stack_00000008;
  local_3c = pbVar4;
  for (; 0 < in_stack_00000004; in_stack_00000004 = in_stack_00000004 + -1) {
    bVar2 = *local_34;
    if ((bVar2 & 0x80) == 0) {
      *local_3c = bVar2;
      uVar1 = uVar1 + 1;
      local_3c = local_3c + 1;
      if (uVar1 == local_20) {
        uVar1 = 0;
        if (local_1c < 0xb0) {
          local_3c = pbVar4;
          if (0x7f < local_1c) {
            if (local_1c < 0x81) {
              pcspk_note_off(local_14,*pbVar4);
            }
            else if (local_1c == 0x90) {
              if ((&DAT_000f21fd)[iVar3] == '\0') {
                pcspk_note_off(local_14,*pbVar4);
              }
              else {
                pcspk_note_on(local_14,*pbVar4,(&DAT_000f21fd)[iVar3]);
              }
            }
          }
        }
        else {
          local_3c = pbVar4;
          if (((0xb0 < local_1c) && (0xbf < local_1c)) && (local_1c < 0xc1)) {
            pcspk_program(local_14,*pbVar4);
          }
        }
      }
    }
    else {
      local_1c = bVar2 & 0xf0;
      local_14 = bVar2 & 0xf;
      if ((bVar2 & 0xf0) == 0xc0) {
        local_40 = 1;
      }
      else {
        local_40 = 2;
      }
      local_20 = local_40;
      uVar1 = 0;
      local_3c = pbVar4;
    }
    local_34 = local_34 + 1;
  }
  dword_d4f9a = dword_d4f9a + -4;
  return;
}


// ================================================================================================
// sbdac_drv_send_midi @ 0x9dc9f [__watcall]
// ================================================================================================

void __watcall sbdac_drv_send_midi(void)

{
  ushort uVar1;
  byte bVar2;
  int iVar3;
  byte *pbVar4;
  short in_stack_00000004;
  byte *in_stack_00000008;
  byte local_34;
  byte *local_2c;
  byte *local_28;
  byte local_1c;
  byte local_18;
  byte local_14;
  
  empty_func_902a0();
  iVar3 = dword_d4f9a;
  local_14 = 0xc0;
  local_18 = 1;
  local_1c = 0;
  uVar1 = 0;
  pbVar4 = &unk_f21fc + dword_d4f9a;
  dword_d4f9a = dword_d4f9a + 4;
  local_2c = in_stack_00000008;
  local_28 = pbVar4;
  for (; 0 < in_stack_00000004; in_stack_00000004 = in_stack_00000004 + -1) {
    bVar2 = *local_2c;
    if ((bVar2 & 0x80) == 0) {
      *local_28 = bVar2;
      uVar1 = uVar1 + 1;
      local_28 = local_28 + 1;
      if (uVar1 == local_18) {
        uVar1 = 0;
        if (local_14 < 0xb0) {
          local_28 = pbVar4;
          if (0x7f < local_14) {
            if (local_14 < 0x81) {
              sbdac_channel_notes_off(local_1c,*pbVar4);
            }
            else if (local_14 == 0x90) {
              if ((&DAT_000f21fd)[iVar3] == '\0') {
                sbdac_channel_notes_off(local_1c,*pbVar4);
              }
              else {
                sbdac_note_on(local_1c,*pbVar4,(&DAT_000f21fd)[iVar3]);
              }
            }
          }
        }
        else if (local_14 < 0xb1) {
          sbdac_controller(local_1c,*pbVar4,(&DAT_000f21fd)[iVar3]);
          local_28 = pbVar4;
        }
        else {
          local_28 = pbVar4;
          if (0xbf < local_14) {
            if (local_14 < 0xc1) {
              sbdac_program(local_1c,*pbVar4);
            }
            else if (local_14 == 0xe0) {
              sbdac_pitch_bend(local_1c,(int)(short)((ushort)(byte)(&DAT_000f21fd)[iVar3] * 0x100 + -0x4000
                                             ));
            }
          }
        }
      }
    }
    else {
      local_14 = bVar2 & 0xf0;
      local_1c = bVar2 & 0xf;
      if ((bVar2 & 0xf0) == 0xc0) {
        local_34 = 1;
      }
      else {
        local_34 = 2;
      }
      local_18 = local_34;
      uVar1 = 0;
      local_28 = pbVar4;
    }
    local_2c = local_2c + 1;
  }
  dword_d4f9a = dword_d4f9a + -4;
  return;
}


// ================================================================================================
// adlib_drv_default_port @ 0x9de9c [__watcall]
// ================================================================================================

void __watcall adlib_drv_default_port(void)

{
  empty_func_902a0();
  opl_default_port();
  return;
}


// ================================================================================================
// adlib_drv_detect @ 0x9dea9 [__watcall]
// ================================================================================================

void __watcall adlib_drv_detect(void)

{
  undefined4 in_stack_00000004;
  
  empty_func_902a0();
  opl_detect(in_stack_00000004);
  return;
}


// ================================================================================================
// adlib_drv_init @ 0x9debe [__watcall]
// ================================================================================================

void __watcall adlib_drv_init(void)

{
  int iVar1;
  ushort uVar2;
  uint uVar3;
  undefined4 in_stack_00000004;
  
  empty_func_902a0();
  word_f3452 = 0x1ff;
  word_f3450 = 0;
  word_f344e = 0;
  for (uVar2 = 0; uVar2 < 0x10; uVar2 = uVar2 + 1) {
    uVar3 = (uint)uVar2;
    iVar1 = uVar3 * 0x1e;
    (&unk_f3108)[uVar3] = (int)&unk_f2f28 + iVar1;
    *(undefined4 *)((int)&unk_f2f28 + iVar1) = 0;
    (&unk_f2f3c)[uVar3 * 0xf] = 0;
    (&unk_f2f40)[uVar3 * 0xf] = 0;
    (&unk_f2f3e)[uVar3 * 0xf] = 0x1ff;
    (&unk_f2f42)[iVar1] = 9;
    (&unk_f2f43)[iVar1] = 0xff;
    (&unk_f2f44)[uVar3 * 0xf] = 100;
  }
  for (uVar2 = 0; uVar2 < 9; uVar2 = uVar2 + 1) {
    (&unk_f3196)[(uint)uVar2 * 0x56] = 0xff;
    (&unk_f3150)[(uint)uVar2 * 0x2b] = uVar2;
  }
  opl_init_port(in_stack_00000004);
  return;
}


// ================================================================================================
// adlib_drv_shutdown @ 0x9df73 [__watcall]
// ================================================================================================

void __watcall adlib_drv_shutdown(void)

{
  empty_func_902a0();
  opl_shutdown();
  return;
}


// ================================================================================================
// adlib_drv_tick @ 0x9df80 [__watcall]
// ================================================================================================

void __watcall adlib_drv_tick(void)

{
  ushort *puVar1;
  ushort uVar2;
  short sVar3;
  uint uVar4;
  int iVar5;
  ushort uVar6;
  ushort uVar7;
  
  empty_func_902a0();
  uVar6 = 1;
  for (uVar7 = 0; uVar7 < 9; uVar7 = uVar7 + 1) {
    if ((uVar6 & word_f3450) != 0) {
      uVar4 = (uint)uVar7;
      iVar5 = uVar4 * 0x56;
      if ((&DAT_000f3170)[uVar4 * 0x2b] == 0) {
        adlib_voice_off(*(undefined4 *)((int)&DAT_000f314c + iVar5),&unk_f3150 + uVar4 * 0x2b,1);
        uVar2 = ~uVar6;
        word_f3450 = word_f3450 & uVar2;
        word_f344e = word_f344e & uVar2;
        word_f3452 = word_f3452 | uVar6;
        puVar1 = (ushort *)(*(int *)((int)&unk_f3148 + iVar5) + 0x14);
        *puVar1 = *puVar1 & uVar2;
        puVar1 = (ushort *)(*(int *)((int)&unk_f3148 + iVar5) + 0x18);
        *puVar1 = *puVar1 & uVar2;
      }
      else {
        if ((short)(&DAT_000f319c)[uVar4 * 0x2b] < 1) {
          sVar3 = 0;
        }
        else {
          sVar3 = (&DAT_000f319c)[uVar4 * 0x2b] + -1;
        }
        (&DAT_000f319c)[uVar4 * 0x2b] = sVar3;
        adlib_voice_output(*(undefined4 *)((int)&DAT_000f314c + iVar5),&unk_f3150 + uVar4 * 0x2b);
      }
    }
    uVar6 = uVar6 * 2;
  }
  opl_flush_regs();
  return;
}


// ================================================================================================
// adlib_voice_patch @ 0x9e026 [__watcall]
// ================================================================================================

void __watcall adlib_voice_patch(int param_1,int unaff_EDX)

{
  undefined4 uVar1;
  int iVar2;
  short sVar3;
  
  iVar2 = snd_patch_record(*(undefined *)(param_1 + 0x1b));
  if (iVar2 != 0) {
    uVar1 = *(undefined4 *)(iVar2 + 0x10);
    *(undefined *)(unaff_EDX + 0x4e) = *(undefined *)(param_1 + 0x1b);
    *(undefined4 *)(unaff_EDX + 4) = uVar1;
    *(int *)(unaff_EDX + 0x50) = iVar2;
    *(undefined *)(param_1 + 0x1a) = *(undefined *)(iVar2 + 6);
    *(ushort *)(param_1 + 0x16) = *(ushort *)(iVar2 + 2) & 0x1ff;
    sVar3 = (ushort)*(byte *)(iVar2 + 0xc) << 4;
    *(short *)(param_1 + 0x1c) = sVar3;
    *(short *)(unaff_EDX + 0x54) = sVar3;
    *(undefined *)(param_1 + 0x11) = *(undefined *)(iVar2 + 8);
    *(undefined *)(param_1 + 0x13) = *(undefined *)(iVar2 + 9);
    *(undefined *)(param_1 + 0x12) = *(undefined *)(iVar2 + 10);
  }
  return;
}


// ================================================================================================
// adlib_channel_release @ 0x9e087 [__watcall]
// ================================================================================================

void __watcall adlib_channel_release(uint param_1,char unaff_DL)

{
  int iVar1;
  int iVar2;
  int iVar3;
  short sVar4;
  ushort uVar5;
  
  iVar1 = (&unk_f3108)[param_1 & 0xff];
  sVar4 = 0;
  uVar5 = 1;
  while( true ) {
    if (8 < sVar4) {
      return;
    }
    if ((((uVar5 & *(ushort *)(iVar1 + 0x14)) != 0) &&
        (iVar2 = (int)sVar4, iVar3 = iVar2 * 0x56, iVar1 == *(int *)((int)&unk_f3148 + iVar3))) &&
       (unaff_DL == (&unk_f3197)[iVar3])) break;
    uVar5 = uVar5 * 2;
    sVar4 = sVar4 + 1;
  }
  if (*(short *)(iVar1 + 10) != 0) {
    *(ushort *)(iVar1 + 0x18) = *(ushort *)(iVar1 + 0x18) | uVar5;
    return;
  }
  word_f344e = word_f344e | uVar5;
  (&DAT_000f319c)[iVar2 * 0x2b] = (short)(&DAT_000f319c)[iVar2 * 0x2b] >> 1;
  adlib_voice_release(*(undefined4 *)((int)&DAT_000f314c + iVar3),&unk_f3150 + iVar2 * 0x2b);
  return;
}


// ================================================================================================
// adlib_controller @ 0x9e0ff [__watcall]
// ================================================================================================

void __watcall adlib_controller(byte param_1,byte unaff_DL,byte unaff_BL)

{
  int iVar1;
  undefined2 uVar2;
  ushort uVar3;
  ushort uVar4;
  ushort uVar5;
  ushort uVar6;
  bool bVar7;
  
  iVar1 = (&unk_f3108)[param_1];
  if (unaff_DL < 0x40) {
    if (unaff_DL < 7) {
      if (unaff_DL == 1) {
        uVar3 = (ushort)unaff_BL * 0x82;
        if (0x3fff < uVar3) {
          uVar3 = 0x4000;
        }
        *(ushort *)(iVar1 + 4) = uVar3;
      }
    }
    else if (unaff_DL < 8) {
      uVar2 = adlib_controller_table(unaff_BL);
      *(undefined2 *)(iVar1 + 6) = uVar2;
    }
    else if (unaff_DL == 10) {
      uVar3 = (ushort)unaff_BL * 0x82;
      if (0x3fff < uVar3) {
        uVar3 = 0x4000;
      }
      *(ushort *)(iVar1 + 8) = uVar3 * 2 + -0x4000;
    }
  }
  else if (unaff_DL < 0x41) {
    bVar7 = (unaff_BL & 0x40) != 0;
    *(ushort *)(iVar1 + 10) = (ushort)bVar7;
    if (!bVar7) {
      uVar3 = *(ushort *)(iVar1 + 0x18);
      *(undefined2 *)(iVar1 + 0x18) = 0;
      uVar6 = 1;
      for (uVar5 = 0; uVar5 < 9; uVar5 = uVar5 + 1) {
        if ((uVar6 & uVar3) != 0) {
          adlib_channel_release(param_1,(&unk_f3197)[(uint)uVar5 * 0x56]);
        }
        uVar6 = uVar6 * 2;
      }
    }
  }
  else if (unaff_DL < 0x5b) {
    if (unaff_DL == 0x5a) {
      *(byte *)(iVar1 + 0xe) = unaff_BL;
    }
  }
  else if (unaff_DL < 0x5c) {
    *(byte *)(iVar1 + 0xf) = unaff_BL;
  }
  else if (unaff_DL == 0x7b) {
    uVar3 = *(ushort *)(iVar1 + 0x14);
    uVar6 = 1;
    for (uVar5 = 0; uVar5 < 9; uVar5 = uVar5 + 1) {
      if ((uVar6 & uVar3) != 0) {
        adlib_voice_off(*(undefined4 *)((int)&DAT_000f314c + (uint)uVar5 * 0x56),
                  &unk_f3150 + (uint)uVar5 * 0x2b,1);
        uVar4 = ~uVar6;
        word_f3450 = word_f3450 & uVar4;
        word_f344e = word_f344e & uVar4;
        word_f3452 = word_f3452 | uVar6;
        *(ushort *)(iVar1 + 0x14) = *(ushort *)(iVar1 + 0x14) & uVar4;
        *(ushort *)(iVar1 + 0x18) = *(ushort *)(iVar1 + 0x18) & uVar4;
      }
      uVar6 = uVar6 * 2;
    }
  }
  return;
}


// ================================================================================================
// adlib_program @ 0x9e28b [__watcall]
// ================================================================================================

void __watcall adlib_program(uint param_1,undefined unaff_DL)

{
  *(undefined *)((&unk_f3108)[param_1 & 0xff] + 0x1b) = unaff_DL;
  return;
}


// ================================================================================================
// adlib_pitch_bend @ 0x9e29b [__watcall]
// ================================================================================================

void __watcall adlib_pitch_bend(uint param_1,short unaff_DX)

{
  *(short *)((&unk_f3108)[param_1 & 0xff] + 0xc) = unaff_DX * 2;
  return;
}


// ================================================================================================
// adlib_voice_load_timbre @ 0x9e2b1 [__watcall]
// ================================================================================================

void __watcall adlib_voice_load_timbre(int param_1,int unaff_EDX,undefined unaff_BL,undefined unaff_CL)

{
  char cVar1;
  short sVar2;
  undefined2 uVar3;
  
  memcpy((void *)(unaff_EDX + 2),(void *)(param_1 + 2),0xd);
  if (*(short *)(param_1 + 0x10) != 0) {
    *(undefined2 *)(unaff_EDX + 0x22) = *(undefined2 *)(param_1 + 0x14);
    sVar2 = *(short *)(param_1 + 0x12);
    *(short *)(unaff_EDX + 0x24) = sVar2;
    *(char *)(unaff_EDX + 0x26) = (sVar2 == 0) + '\x01';
  }
  if (*(short *)(param_1 + 0x22) != 0) {
    adlib_env_init(param_1 + 0x24,unaff_EDX + 0x28);
  }
  if (*(short *)(param_1 + 0x32) != 0) {
    adlib_lfo_init(param_1 + 0x34,unaff_EDX + 0x36);
  }
  *(undefined2 *)(unaff_EDX + 0x1c) = 0;
  *(undefined2 *)(unaff_EDX + 0x1a) = *(undefined2 *)(unaff_EDX + 0x1c);
  *(undefined *)(unaff_EDX + 0x1e) = 0;
  *(undefined *)(unaff_EDX + 0x19) = unaff_BL;
  *(undefined *)(unaff_EDX + 0x18) = unaff_BL;
  cVar1 = *(char *)(*(int *)(unaff_EDX + 0x42) + 0xd);
  sVar2 = adlib_note_fnum();
  *(short *)(unaff_EDX + 0x14) = sVar2 + cVar1;
  uVar3 = adlib_level_table(unaff_CL);
  *(undefined2 *)(unaff_EDX + 0x10) = uVar3;
  *(undefined *)(unaff_EDX + 0x1e) = 1;
  *(undefined2 *)(unaff_EDX + 0x20) = 0xffff;
  return;
}


// ================================================================================================
// adlib_voice_release @ 0x9e378 [__watcall]
// ================================================================================================

void __watcall adlib_voice_release(int param_1,int unaff_EDX)

{
  if (*(short *)(param_1 + 0x10) != 0) {
    *(undefined *)(unaff_EDX + 0x26) = 5;
  }
  *(undefined *)(unaff_EDX + 0x1e) = 0;
  *(undefined2 *)(unaff_EDX + 0x20) = *(undefined2 *)(param_1 + 0x4a);
  return;
}


// ================================================================================================
// adlib_voice_off @ 0x9e390 [__watcall]
// ================================================================================================

void __watcall adlib_voice_off(int param_1,short *unaff_EDX,int unaff_EBX,undefined4 unaff_ECX)

{
  if (*(short *)(param_1 + 0x10) != 0) {
    *(undefined *)(unaff_EDX + 0x13) = 0;
  }
  unaff_EDX[0x11] = 0;
  if (*(short *)(param_1 + 0x22) != 0) {
    *(undefined *)(unaff_EDX + 0x16) = 0;
    unaff_EDX[0x15] = 0;
    unaff_EDX[0x14] = unaff_EDX[0x15];
  }
  if (*(short *)(param_1 + 0x32) != 0) {
    *(undefined *)(unaff_EDX + 0x1c) = 0;
  }
  unaff_EDX[0x1b] = 0;
  *(undefined *)(unaff_EDX + 0xf) = 0;
  unaff_EDX[0x10] = 0;
  if (unaff_EBX != 0) {
    *(byte *)(unaff_EDX + 7) = *(byte *)(unaff_EDX + 7) & 0xdf;
    *(byte *)((int)unaff_EDX + 5) = *(byte *)((int)unaff_EDX + 5) & 0xf0 | 0xe;
    *(byte *)(unaff_EDX + 5) = *(byte *)(unaff_EDX + 5) & 0xf0 | 0xe;
    opl_voice_regs((int)*unaff_EDX,unaff_EDX + 1,unaff_ECX);
    opl_flush_regs();
  }
  return;
}


// ================================================================================================
// adlib_env_step @ 0x9e428 [__watcall]
// ================================================================================================

void __watcall adlib_env_step(int param_1,short *unaff_EDX)

{
  short sVar1;
  
  switch(*(undefined *)(unaff_EDX + 2)) {
  case 1:
    sVar1 = unaff_EDX[1];
    unaff_EDX[1] = sVar1 + -1;
    if ((short)(sVar1 + -1) < 1) {
      *(undefined *)(unaff_EDX + 2) = 2;
      return;
    }
    break;
  case 2:
    sVar1 = *unaff_EDX + *(short *)(param_1 + 4);
    *unaff_EDX = sVar1;
    if (*(short *)(param_1 + 6) <= sVar1) {
      *unaff_EDX = *(short *)(param_1 + 6);
      *(undefined *)(unaff_EDX + 2) = 3;
      return;
    }
    break;
  case 3:
    sVar1 = *unaff_EDX - *(short *)(param_1 + 8);
    *unaff_EDX = sVar1;
    if (sVar1 <= *(short *)(param_1 + 10)) {
      *unaff_EDX = *(short *)(param_1 + 10);
      *(undefined *)(unaff_EDX + 2) = 4;
      return;
    }
    break;
  case 4:
    sVar1 = *unaff_EDX - *(short *)(param_1 + 0xc);
    *unaff_EDX = sVar1;
    goto joined_r0x0009e4c7;
  case 5:
    sVar1 = *unaff_EDX - *(short *)(param_1 + 0xe);
    *unaff_EDX = sVar1;
joined_r0x0009e4c7:
    if (sVar1 < 1) {
      *unaff_EDX = 0;
      *(undefined *)(unaff_EDX + 2) = 0;
    }
  }
  return;
}


// ================================================================================================
// adlib_lfo_init @ 0x9e4d7 [__watcall]
// ================================================================================================

void __watcall adlib_lfo_init(short *param_1,undefined2 *unaff_EDX)

{
  short sVar1;
  
  *unaff_EDX = 0;
  unaff_EDX[3] = param_1[2];
  unaff_EDX[4] = (ushort)*(byte *)((int)param_1 + 3);
  unaff_EDX[5] = 0xffff;
  sVar1 = *param_1;
  unaff_EDX[2] = sVar1;
  if (sVar1 != 0) {
    *(undefined *)(unaff_EDX + 1) = 1;
    return;
  }
  *(undefined *)(unaff_EDX + 1) = 2;
  adlib_lfo_step();
  return;
}


// ================================================================================================
// adlib_lfo_step @ 0x9e511 [__watcall]
// ================================================================================================

void __watcall adlib_lfo_step(int param_1,undefined2 *unaff_EDX)

{
  byte bVar1;
  short sVar2;
  undefined2 uVar3;
  
  while( true ) {
    bVar1 = *(byte *)(unaff_EDX + 1);
    if (bVar1 == 0) {
      return;
    }
    if (1 < bVar1) break;
    sVar2 = unaff_EDX[2];
    unaff_EDX[2] = sVar2 + -1;
    if (0 < (short)(sVar2 + -1)) {
      return;
    }
    *(undefined *)(unaff_EDX + 1) = 2;
  }
  if (bVar1 != 2) {
    return;
  }
  sVar2 = unaff_EDX[3];
  unaff_EDX[3] = sVar2 + -1;
  if ((short)(sVar2 + -1) < 1) {
    *(undefined *)(unaff_EDX + 1) = 0;
    unaff_EDX[5] = 0;
    uVar3 = unaff_EDX[5];
  }
  else {
    sVar2 = unaff_EDX[4];
    unaff_EDX[4] = sVar2 + -1;
    if (0 < (short)(sVar2 + -1)) {
      return;
    }
    unaff_EDX[4] = (ushort)*(byte *)(param_1 + 3);
    sVar2 = unaff_EDX[5];
    unaff_EDX[5] = sVar2 + 1;
    if ((short)(ushort)*(byte *)(param_1 + 2) <= (short)(sVar2 + 1)) {
      unaff_EDX[5] = 0;
    }
    uVar3 = *(undefined2 *)(param_1 + 6 + (short)unaff_EDX[5] * 2);
  }
  *unaff_EDX = uVar3;
  return;
}


// ================================================================================================
// adlib_env_init @ 0x9e59d [__watcall]
// ================================================================================================

void __watcall adlib_env_init(int param_1,undefined2 *unaff_EDX)

{
  undefined2 uVar1;
  
  unaff_EDX[6] = 0;
  uVar1 = unaff_EDX[6];
  unaff_EDX[3] = uVar1;
  unaff_EDX[1] = uVar1;
  *unaff_EDX = uVar1;
  unaff_EDX[4] = *(undefined2 *)(param_1 + 4);
  unaff_EDX[5] = *(undefined2 *)(param_1 + 10);
  *(undefined *)(unaff_EDX + 2) = 1;
  return;
}


// ================================================================================================
// adlib_env_update @ 0x9e5c9 [__watcall]
// ================================================================================================

void __watcall adlib_env_update(short *param_1,short *unaff_EDX)

{
  byte bVar1;
  short sVar2;
  undefined4 uVar3;
  
  bVar1 = *(byte *)(unaff_EDX + 2);
  if (bVar1 == 0) goto LAB_0009e641;
  if (bVar1 < 2) {
    if (unaff_EDX[3] < *param_1) goto LAB_0009e641;
    if (unaff_EDX[3] < param_1[1]) {
      *(undefined *)(unaff_EDX + 2) = 2;
      goto LAB_0009e601;
    }
  }
  else {
    if (bVar1 != 2) goto LAB_0009e641;
LAB_0009e601:
    if (unaff_EDX[3] < param_1[1]) {
      sVar2 = unaff_EDX[6];
      unaff_EDX[6] = sVar2 + unaff_EDX[5];
      uVar3 = sin_lookup((int)(uint)(ushort)(sVar2 + unaff_EDX[5]) >> 6);
      sVar2 = fixmul16((int)unaff_EDX[4] << 2,uVar3);
      unaff_EDX[1] = sVar2;
      goto LAB_0009e641;
    }
  }
  *(undefined *)(unaff_EDX + 2) = 0;
LAB_0009e641:
  sVar2 = param_1[3];
  if (sVar2 < unaff_EDX[1]) {
    *unaff_EDX = sVar2;
  }
  else {
    if (SBORROW4((int)unaff_EDX[1],-(int)sVar2) == (int)unaff_EDX[1] + (int)sVar2 < 0) {
      sVar2 = unaff_EDX[1];
    }
    else {
      sVar2 = -sVar2;
    }
    *unaff_EDX = sVar2;
  }
  unaff_EDX[3] = unaff_EDX[3] + 1;
  return;
}


// ================================================================================================
// adlib_drv_send_midi @ 0x9e676 [__watcall]
// ================================================================================================

void __watcall adlib_drv_send_midi(void)

{
  ushort uVar1;
  byte bVar2;
  int iVar3;
  byte *pbVar4;
  short in_stack_00000004;
  byte *in_stack_00000008;
  byte local_34;
  byte *local_2c;
  byte *local_28;
  byte local_20;
  byte local_1c;
  byte local_14;
  
  empty_func_902a0();
  iVar3 = dword_d4f9a;
  local_1c = 0xc0;
  local_20 = 1;
  local_14 = 0;
  uVar1 = 0;
  pbVar4 = &unk_f21fc + dword_d4f9a;
  dword_d4f9a = dword_d4f9a + 4;
  local_28 = in_stack_00000008;
  local_2c = pbVar4;
  for (; in_stack_00000004 != 0; in_stack_00000004 = in_stack_00000004 + -1) {
    bVar2 = *local_28;
    if ((bVar2 & 0x80) == 0) {
      *local_2c = bVar2;
      uVar1 = uVar1 + 1;
      local_2c = local_2c + 1;
      if (uVar1 == local_20) {
        uVar1 = 0;
        if (local_1c < 0xb0) {
          local_2c = pbVar4;
          if (0x7f < local_1c) {
            if (local_1c < 0x81) {
              adlib_channel_release(local_14,*pbVar4);
            }
            else if (local_1c == 0x90) {
              if ((&DAT_000f21fd)[iVar3] == '\0') {
                adlib_channel_release(local_14,*pbVar4);
              }
              else {
                adlib_note_on(local_14,*pbVar4,(&DAT_000f21fd)[iVar3]);
              }
            }
          }
        }
        else if (local_1c < 0xb1) {
          adlib_controller(local_14,*pbVar4,(&DAT_000f21fd)[iVar3]);
          local_2c = pbVar4;
        }
        else {
          local_2c = pbVar4;
          if (0xbf < local_1c) {
            if (local_1c < 0xc1) {
              adlib_program(local_14,*pbVar4);
            }
            else if (local_1c == 0xe0) {
              adlib_pitch_bend(local_14,(int)(short)((ushort)*pbVar4 +
                                              (ushort)(byte)(&DAT_000f21fd)[iVar3] * 0x80 + -0x2000)
                       );
            }
          }
        }
      }
    }
    else {
      local_1c = bVar2 & 0xf0;
      local_14 = bVar2 & 0xf;
      if ((bVar2 & 0xf0) == 0xc0) {
        local_34 = 1;
      }
      else {
        local_34 = 2;
      }
      local_20 = local_34;
      uVar1 = 0;
      local_2c = pbVar4;
    }
    local_28 = local_28 + 1;
  }
  dword_d4f9a = dword_d4f9a + -4;
  return;
}


// ================================================================================================
// adlib_voice_modulate @ 0x9e85b [__watcall]
// ================================================================================================

void __watcall adlib_voice_modulate(int param_1,int unaff_EDX,undefined2 unaff_BX,short unaff_CX)

{
  char cVar1;
  undefined2 uVar2;
  short sVar3;
  short local_2c;
  
  switch(unaff_BX) {
  case 1:
    *(char *)(unaff_EDX + 0x19) = *(char *)(unaff_EDX + 0x18) + (char)unaff_CX;
    uVar2 = adlib_note_fnum();
    *(undefined2 *)(unaff_EDX + 0x16) = uVar2;
    break;
  case 2:
    *(short *)(unaff_EDX + 0x16) = *(short *)(unaff_EDX + 0x16) + unaff_CX;
    break;
  case 3:
    local_2c = unaff_CX;
    if (unaff_CX < 0) {
      local_2c = -unaff_CX;
    }
    uVar2 = fixmul16((int)*(short *)(unaff_EDX + 0x12) << 2,(int)local_2c);
    *(undefined2 *)(unaff_EDX + 0x12) = uVar2;
    break;
  case 5:
    sVar3 = fixmul16((int)unaff_CX,(int)*(short *)(param_1 + 0x2c));
    *(short *)(unaff_EDX + 0x30) = *(short *)(param_1 + 0x28) + sVar3;
    break;
  case 7:
    if (unaff_CX < 1) {
      if (unaff_CX < 0) {
        if (*(short *)(unaff_EDX + 0x1c) == 0) {
          sVar3 = adlib_note_fnum();
          *(short *)(unaff_EDX + 0x1c) = *(short *)(unaff_EDX + 0x16) - sVar3;
        }
        sVar3 = fixmul16((int)unaff_CX << 2,*(undefined2 *)(unaff_EDX + 0x1c));
        *(short *)(unaff_EDX + 0x16) = *(short *)(unaff_EDX + 0x16) + sVar3;
      }
    }
    else {
      if (*(short *)(unaff_EDX + 0x1a) == 0) {
        sVar3 = adlib_note_fnum();
        *(short *)(unaff_EDX + 0x1a) = sVar3 - *(short *)(unaff_EDX + 0x16);
      }
      sVar3 = fixmul16((int)unaff_CX << 2,*(undefined2 *)(unaff_EDX + 0x1a));
      *(short *)(unaff_EDX + 0x16) = *(short *)(unaff_EDX + 0x16) + sVar3;
    }
    break;
  case 8:
    uVar2 = fixmul16((int)unaff_CX,*(undefined2 *)(param_1 + 0x2e));
    *(undefined2 *)(unaff_EDX + 0x32) = uVar2;
    break;
  case 9:
    cVar1 = fixmul16((int)unaff_CX,0x3f);
    *(byte *)(unaff_EDX + 8) = *(byte *)(unaff_EDX + 8) & 0xc0;
    *(byte *)(unaff_EDX + 8) = *(byte *)(unaff_EDX + 8) | 0x3fU - cVar1 & 0x3f;
  }
  return;
}


// ================================================================================================
// adlib_voice_update @ 0x9eaa6 [__watcall]
// ================================================================================================

void __watcall adlib_voice_update(int param_1,int unaff_EDX)

{
  int iVar1;
  short *psVar2;
  
  iVar1 = *(int *)(unaff_EDX + 0x42);
  *(undefined2 *)(unaff_EDX + 0x16) = *(undefined2 *)(unaff_EDX + 0x14);
  *(undefined2 *)(unaff_EDX + 0x12) = *(undefined2 *)(unaff_EDX + 0x10);
  if (*(short *)(param_1 + 0x32) != 0) {
    adlib_lfo_step(param_1 + 0x34,unaff_EDX + 0x36);
    adlib_voice_modulate(param_1,unaff_EDX,*(undefined2 *)(param_1 + 0x32),(int)*(short *)(unaff_EDX + 0x36));
  }
  adlib_voice_modulate(param_1,unaff_EDX,7,(int)*(short *)(iVar1 + 8));
  if (*(short *)(param_1 + 0x10) != 0) {
    adlib_env_step(param_1 + 0x12,unaff_EDX + 0x22);
    adlib_voice_modulate(param_1,unaff_EDX,*(undefined2 *)(param_1 + 0x10),(int)*(short *)(unaff_EDX + 0x22));
  }
  if (*(short *)(param_1 + 0x22) != 0) {
    adlib_env_update(param_1 + 0x24,unaff_EDX + 0x28);
    adlib_voice_modulate(param_1,unaff_EDX,*(undefined2 *)(param_1 + 0x22),(int)*(short *)(unaff_EDX + 0x28));
  }
  psVar2 = *(short **)(unaff_EDX + 0x42);
  adlib_voice_modulate(param_1,unaff_EDX,5,(int)*psVar2);
  adlib_voice_modulate(param_1,unaff_EDX,3,(int)psVar2[1]);
  return;
}


// ================================================================================================
// adlib_voice_output @ 0x9ebd5 [__watcall]
// ================================================================================================

void __watcall adlib_voice_output(int param_1,short *unaff_EDX)

{
  char cVar1;
  
  adlib_voice_update(param_1,unaff_EDX);
  if ((*(byte *)(unaff_EDX + 6) & 1) == 1) {
    cVar1 = fixmul16((int)unaff_EDX[9] << 2,
                      (int)(short)(0x3f - (ushort)(*(byte *)(param_1 + 8) & 0x3f)));
    *(byte *)(unaff_EDX + 4) = *(byte *)(unaff_EDX + 4) & 0xc0;
    *(byte *)(unaff_EDX + 4) = *(byte *)(unaff_EDX + 4) | 0x3fU - cVar1 & 0x3f;
  }
  cVar1 = fixmul16((int)unaff_EDX[9] << 2,
                    (int)(short)(0x3f - (ushort)(*(byte *)(param_1 + 3) & 0x3f)));
  *(byte *)((int)unaff_EDX + 3) = *(byte *)((int)unaff_EDX + 3) & 0xc0;
  *(byte *)((int)unaff_EDX + 3) = *(byte *)((int)unaff_EDX + 3) | 0x3fU - cVar1 & 0x3f;
  *(short *)((int)unaff_EDX + 0xd) = unaff_EDX[0xb];
  *(byte *)(unaff_EDX + 7) = *(byte *)(unaff_EDX + 7) & 0xdf;
  *(byte *)(unaff_EDX + 7) = *(byte *)(unaff_EDX + 7) | (*(byte *)(unaff_EDX + 0xf) & 1) << 5;
  opl_voice_regs((int)*unaff_EDX,unaff_EDX + 1);
  if (0 < unaff_EDX[0x10]) {
    unaff_EDX[0x10] = unaff_EDX[0x10] + -1;
  }
  return;
}


// ================================================================================================
// adlib_note_on @ 0x9ece8 [__watcall]
// ================================================================================================

void __watcall adlib_note_on(byte param_1,byte unaff_DL,undefined unaff_BL)

{
  ushort uVar1;
  short sVar2;
  int iVar3;
  ushort uVar4;
  uint uVar5;
  int iVar6;
  int *piVar7;
  int *local_44;
  uint local_3c;
  uint local_38;
  uint local_34;
  uint local_28;
  byte local_20;
  
  iVar3 = (&unk_f3108)[param_1];
  local_20 = unaff_DL;
  if (param_1 == 9) {
    if (unaff_DL < 0x24) {
      return;
    }
    if (99 < unaff_DL) {
      return;
    }
    *(byte *)(iVar3 + 0x1b) = unaff_DL + 0x5c;
    local_20 = 0x3c;
  }
  sVar2 = 10000;
  uVar4 = 0;
  local_34 = 1;
  while( true ) {
    if (8 < uVar4) {
      uVar1 = 0;
      for (uVar4 = *(ushort *)(iVar3 + 0x14); uVar4 != 0; uVar4 = uVar4 ^ -uVar4 & uVar4) {
        uVar1 = uVar1 + 1;
      }
      if ((uVar1 < *(byte *)(iVar3 + 0x1a)) &&
         (uVar4 = word_f3452 & *(ushort *)(iVar3 + 0x16), uVar4 != 0)) {
        local_38 = 0;
        for (uVar1 = uVar4; (uVar1 & 1) == 0; uVar1 = (short)uVar1 >> 1) {
          local_38 = local_38 + 1;
        }
        iVar6 = (local_38 & 0xffff) * 0x56;
        uVar4 = uVar4 & -uVar4;
        word_f3452 = word_f3452 & ~uVar4;
        word_f344e = word_f344e & ~uVar4;
        word_f3450 = word_f3450 | uVar4;
        *(ushort *)(iVar3 + 0x14) = *(ushort *)(iVar3 + 0x14) | uVar4;
        *(ushort *)(iVar3 + 0x18) = *(ushort *)(iVar3 + 0x18) & ~uVar4;
        *(int *)((int)&unk_f3148 + iVar6) = iVar3;
        (&unk_f3197)[iVar6] = unaff_DL;
        *(int *)(&DAT_000f3192 + iVar6) = iVar3 + 4;
        adlib_voice_patch(iVar3,(int *)((int)&unk_f3148 + iVar6));
        adlib_voice_load_timbre(*(undefined4 *)((int)&DAT_000f314c + iVar6),
                  &unk_f3150 + (local_38 & 0xffff) * 0x2b,
                  *(char *)(*(int *)(&DAT_000f3198 + iVar6) + 7) + local_20,unaff_BL);
      }
      else {
        uVar4 = word_f344e & *(ushort *)(iVar3 + 0x16);
        if (uVar4 == 0) {
          adlib_voice_off(local_44[1],local_44 + 2,1);
          uVar4 = (ushort)local_28;
          word_f3452 = word_f3452 & ~uVar4;
          word_f344e = word_f344e & ~uVar4;
          word_f3450 = word_f3450 | uVar4;
          *(ushort *)(iVar3 + 0x14) = *(ushort *)(iVar3 + 0x14) | uVar4;
          *(ushort *)(iVar3 + 0x18) = *(ushort *)(iVar3 + 0x18) & ~uVar4;
          *local_44 = iVar3;
          *(byte *)((int)local_44 + 0x4f) = unaff_DL;
          *(int *)((int)local_44 + 0x4a) = iVar3 + 4;
          adlib_voice_patch(iVar3,local_44);
          adlib_voice_load_timbre(local_44[1],local_44 + 2,*(char *)(local_44[0x14] + 7) + local_20,unaff_BL);
        }
        else {
          local_38 = 0;
          for (uVar1 = uVar4; (uVar1 & 1) == 0; uVar1 = (short)uVar1 >> 1) {
            local_38 = local_38 + 1;
          }
          local_38 = local_38 & 0xffff;
          iVar6 = local_38 * 0x56;
          adlib_voice_off(*(undefined4 *)((int)&DAT_000f314c + iVar6),&unk_f3150 + local_38 * 0x2b,1);
          uVar4 = uVar4 & -uVar4;
          word_f3452 = word_f3452 & ~uVar4;
          word_f344e = word_f344e & ~uVar4;
          word_f3450 = word_f3450 | uVar4;
          *(ushort *)(iVar3 + 0x14) = *(ushort *)(iVar3 + 0x14) | uVar4;
          *(ushort *)(iVar3 + 0x18) = *(ushort *)(iVar3 + 0x18) & ~uVar4;
          *(int *)((int)&unk_f3148 + iVar6) = iVar3;
          (&unk_f3197)[iVar6] = unaff_DL;
          *(int *)(&DAT_000f3192 + iVar6) = iVar3 + 4;
          adlib_voice_patch(iVar3,(int *)((int)&unk_f3148 + iVar6));
          adlib_voice_load_timbre(*(undefined4 *)((int)&DAT_000f314c + iVar6),&unk_f3150 + local_38 * 0x2b,
                    *(char *)(*(int *)(&DAT_000f3198 + iVar6) + 7) + local_20,unaff_BL);
        }
      }
      local_3c = 0;
      for (local_34._0_2_ = *(ushort *)(iVar3 + 0x14); (ushort)local_34 != 0;
          local_34._0_2_ = (ushort)local_34 ^ -(ushort)local_34 & (ushort)local_34) {
        local_3c = local_3c + 1;
      }
      if (8 < (local_3c & 0xffff) + 1) {
        sVar2 = 10000;
        local_34 = 1;
        for (uVar4 = 0; uVar4 < 9; uVar4 = uVar4 - 1) {
          uVar5 = (uint)uVar4;
          if ((((ushort)local_34 & word_f3450) != 0) &&
             ((short)(&DAT_000f319c)[uVar5 * 0x2b] < sVar2)) {
            sVar2 = (&DAT_000f319c)[uVar5 * 0x2b];
            local_28 = local_34;
            local_44 = (int *)((int)&unk_f3148 + uVar5 * 0x56);
          }
          local_34 = (uint)(ushort)((ushort)local_34 << 1);
        }
        adlib_voice_off(local_44[1],local_44 + 2,0);
        uVar4 = (ushort)local_28;
        word_f3452 = word_f3452 & ~uVar4;
        word_f344e = word_f344e & ~uVar4;
        word_f3450 = word_f3450 | uVar4;
        *(ushort *)(iVar3 + 0x14) = *(ushort *)(iVar3 + 0x14) | uVar4;
        *(ushort *)(iVar3 + 0x18) = *(ushort *)(iVar3 + 0x18) & ~uVar4;
      }
      return;
    }
    uVar5 = (uint)uVar4;
    iVar6 = uVar5 * 0x56;
    piVar7 = (int *)((int)&unk_f3148 + iVar6);
    if ((((ushort)local_34 & word_f3450) != 0) && ((short)(&DAT_000f319c)[uVar5 * 0x2b] < sVar2)) {
      sVar2 = (&DAT_000f319c)[uVar5 * 0x2b];
      local_28 = local_34;
      local_44 = piVar7;
    }
    if (((((ushort)local_34 & *(ushort *)(iVar3 + 0x14)) != 0) && (iVar3 == *piVar7)) &&
       (unaff_DL == (&unk_f3197)[iVar6])) break;
    uVar4 = uVar4 + 1;
    local_34 = local_34 << 1;
  }
  adlib_voice_off(*(undefined4 *)((int)&DAT_000f314c + iVar6),&unk_f3150 + uVar5 * 0x2b,1);
  word_f3450 = word_f3450 | (ushort)local_34;
  word_f3452 = word_f3452 & ~(ushort)local_34;
  word_f344e = word_f344e & ~(ushort)local_34;
  *(ushort *)(iVar3 + 0x18) = *(ushort *)(iVar3 + 0x18) & ~(ushort)local_34;
  *(ushort *)(iVar3 + 0x14) = *(ushort *)(iVar3 + 0x14) | (ushort)local_34;
  adlib_voice_patch(iVar3,piVar7);
  adlib_voice_load_timbre(*(undefined4 *)((int)&DAT_000f314c + iVar6),&unk_f3150 + uVar5 * 0x2b,
            *(char *)(*(int *)(&DAT_000f3198 + iVar6) + 7) + local_20,unaff_BL);
  return;
}


// ================================================================================================
// sbdac_drv_detect @ 0x9f226 [__watcall]
// ================================================================================================

int __watcall sbdac_drv_detect(void)

{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  byte *pbVar4;
  int *piVar5;
  undefined4 uVar6;
  undefined4 local_14;
  int local_10;
  int local_c;
  int local_8 [2];
  
  local_8[0] = 0x9f22c;
  empty_func_902a0();
  local_8[0] = 0;
  local_c = 0;
  local_10 = -1;
  local_14 = 9;
  pbVar2 = (byte *)getenv(aBLASTER);
  if (pbVar2 != (byte *)0x0) {
    while (bVar1 = *pbVar2, bVar1 != 0) {
      if (bVar1 < 0x56) {
        if (bVar1 < 0x44) {
          if (bVar1 == 0x41) {
LAB_0009f2b7:
            uVar6 = 0x10;
            piVar5 = local_8;
LAB_0009f2c1:
            pbVar4 = pbVar2 + 1;
            pbVar2 = pbVar4;
            goto LAB_0009f31d;
          }
        }
        else if (bVar1 < 0x45) {
LAB_0009f2f0:
          if (((pbVar2[1] == 0x45) && (pbVar2[2] == 0x72)) && (pbVar2[3] == 0x46)) {
            pbVar4 = pbVar2 + 4;
            uVar6 = 10;
            piVar5 = (int *)&unk_d5254;
          }
          else {
            pbVar4 = pbVar2 + 1;
            uVar6 = 10;
            piVar5 = &local_10;
            pbVar2 = pbVar4;
          }
LAB_0009f31d:
          iVar3 = blaster_parse_hex(pbVar4,piVar5,uVar6);
          pbVar2 = pbVar2 + iVar3;
        }
        else if (bVar1 == 0x49) {
LAB_0009f2c5:
          uVar6 = 10;
          piVar5 = &local_c;
          goto LAB_0009f2c1;
        }
      }
      else if (bVar1 < 0x57) {
LAB_0009f2d1:
        iVar3 = blaster_parse_hex(pbVar2 + 1,&local_14,10);
        pbVar2 = pbVar2 + 1 + iVar3;
        sb_mixer_set_volume(local_8[0],local_14);
      }
      else if (bVar1 < 100) {
        if (bVar1 == 0x61) goto LAB_0009f2b7;
      }
      else {
        if (bVar1 < 0x65) goto LAB_0009f2f0;
        if (0x68 < bVar1) {
          if (bVar1 < 0x6a) goto LAB_0009f2c5;
          if (bVar1 == 0x76) goto LAB_0009f2d1;
        }
      }
      if (*pbVar2 != 0) {
        pbVar2 = pbVar2 + 1;
      }
    }
  }
  dword_d524c = local_10;
  return local_c * 0x10000 + local_8[0];
}


// ================================================================================================
// blaster_parse_hex @ 0x9f34c [__watcall]
// ================================================================================================

int __watcall blaster_parse_hex(int param_1,undefined4 *unaff_EDX)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  char local_18 [8];
  undefined local_10 [4];
  
  for (iVar3 = 0; (cVar1 = *(char *)(param_1 + iVar3), cVar1 != '\0' && (cVar1 != ' '));
      iVar3 = iVar3 + 1) {
    local_18[iVar3] = cVar1;
  }
  local_18[iVar3] = '\0';
  uVar2 = strtoul(local_18,local_10);
  *unaff_EDX = uVar2;
  return iVar3;
}


// ================================================================================================
// sbdac_drv_init @ 0x9f387 [__watcall]
// ================================================================================================

undefined4 __watcall sbdac_drv_init(void)

{
  char cVar1;
  void *__s;
  int in_stack_00000004;
  
  empty_func_902a0();
  if (in_stack_00000004 != 0) {
    __s = (void *)dpmi_alloc_dos_memory(0x40,&unk_d5258,&dword_d525c);
    if (0xfe00 < ((uint)__s & 0xffff)) {
      __s = (void *)(((uint)__s & 0xf0000) + 0x10000);
    }
    memset(__s,0x80,0x200);
    cVar1 = mix_init(in_stack_00000004,dword_d524c,__s,0x200);
    if (cVar1 != -1) {
      dword_d5250 = __s;
      return 1;
    }
    dword_d5250 = (void *)0x0;
  }
  return 0;
}


// ================================================================================================
// sbdac_drv_reset_voices @ 0x9f418 [__watcall]
// ================================================================================================

void __watcall sbdac_drv_reset_voices(void)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  empty_func_902a0();
  if (dword_d5250 != 0) {
    word_f3716 = 0xf;
    word_f3718 = 0;
    word_f3714 = 0;
    iVar1 = 0;
    do {
      (&unk_f3454)[iVar1 * 0x11] = (short)(1 << ((byte)iVar1 & 0x1f));
      (&unk_f3456)[iVar1 * 0x11] = (short)iVar1;
      *(undefined2 **)((int)&unk_f3462 + iVar1 * 0x22) = &unk_d522e;
      iVar1 = iVar1 + 1;
    } while (iVar1 < 4);
    iVar1 = 0;
    do {
      puVar3 = (undefined4 *)&unk_d522e;
      puVar4 = (undefined4 *)(&unk_f3534 + iVar1 * 0xf);
      for (iVar2 = 7; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar4 = *puVar3;
        puVar3 = puVar3 + 1;
        puVar4 = puVar4 + 1;
      }
      *(undefined2 *)puVar4 = *(undefined2 *)puVar3;
      iVar1 = iVar1 + 1;
    } while (iVar1 < 0x10);
  }
  return;
}


// ================================================================================================
// sbdac_drv_shutdown @ 0x9f4a0 [__watcall]
// ================================================================================================

void __watcall sbdac_drv_shutdown(void)

{
  empty_func_902a0();
  if (dword_d5250 != 0) {
    mix_shutdown();
    dpmi_free_dos_memory(dword_d525c);
    dword_d5250 = 0;
  }
  return;
}


// ================================================================================================
// sbdac_drv_tick @ 0x9f4c8 [__watcall]
// ================================================================================================

void __watcall sbdac_drv_tick(void)

{
  ushort uVar1;
  short sVar2;
  int iVar3;
  
  empty_func_902a0();
  uVar1 = 1;
  for (iVar3 = 0; iVar3 < 4; iVar3 = iVar3 + 1) {
    if ((uVar1 & word_f3714) != 0) {
      sVar2 = mix_voice_free(iVar3);
      if (sVar2 != 0) {
        sbdac_voice_free(&unk_f3454 + iVar3 * 0x11);
      }
    }
    if ((short)(&DAT_000f345a)[iVar3 * 0x11] < 1) {
      (&DAT_000f345a)[iVar3 * 0x11] = 0;
    }
    else {
      (&DAT_000f345a)[iVar3 * 0x11] = (&DAT_000f345a)[iVar3 * 0x11] + -1;
    }
    uVar1 = uVar1 * 2;
  }
  for (iVar3 = 0; iVar3 < 4; iVar3 = iVar3 + 1) {
    if ((&DAT_000f34e6)[iVar3 * 0xb] != 0) {
      mix_voice_position(iVar3,0,0,(int)*(short *)(*(int *)((int)&unk_f34dc + iVar3 * 0x16) + 4),
                (int)(short)(&DAT_000f34ec)[iVar3 * 0xb]);
    }
  }
  mix_fill_buffer();
  return;
}


// ================================================================================================
// sbdac_drv_control @ 0x9f577 [__watcall]
// ================================================================================================

int __watcall sbdac_drv_control(void)

{
  short sVar1;
  int iVar2;
  ushort uVar3;
  int unaff_ESI;
  int in_stack_00000004;
  
  empty_func_902a0();
  uVar3 = (ushort)in_stack_00000004;
  if (uVar3 < 9) {
    if (uVar3 < 7) {
      return -1;
    }
    if (uVar3 < 8) {
      sVar1 = mix_rate_khz();
    }
    else {
      sVar1 = sb_dma_half_done();
    }
  }
  else {
    if (9 < uVar3) {
      if (uVar3 < 0x32) {
        if (uVar3 == 10) {
          iVar2 = mix_voice_get_volume();
          return iVar2;
        }
      }
      else if (uVar3 < 0x33) {
        mix_voice_volume(in_stack_00000004 >> 0x18,in_stack_00000004 >> 0x10 & 0xff);
      }
      else if (uVar3 == 0x33) {
        sb_mixer_stereo();
        return unaff_ESI;
      }
      return -1;
    }
    sVar1 = mix_voice_free((int)in_stack_00000004._2_2_);
  }
  return (int)sVar1;
}


// ================================================================================================
// sbdac_set_channel_volume @ 0x9f622 [__watcall]
// ================================================================================================

void __watcall sbdac_set_channel_volume(void)

{
  short in_stack_00000004;
  undefined2 in_stack_00000008;
  
  empty_func_902a0();
  *(undefined2 *)(&unk_f3538 + in_stack_00000004 * 0x1e) = in_stack_00000008;
  return;
}


// ================================================================================================
// sbdac_play_sample @ 0x9f642 [__watcall]
// ================================================================================================

void __watcall sbdac_play_sample(void)

{
  short param_5;
  int param_6;
  int param_7;
  undefined4 param_8;
  undefined4 param_9;
  undefined4 in_stack_00000018;
  undefined4 in_stack_0000001c;
  undefined4 in_stack_00000020;
  undefined4 in_stack_00000024;
  
  empty_func_902a0();
  mix_play_sample((int)param_5,param_6 + param_7,param_8,param_9,in_stack_00000018,in_stack_0000001c,
            in_stack_00000020,in_stack_00000024);
  return;
}


// ================================================================================================
// sbdac_channel_notes_off @ 0x9f685 [__watcall]
// ================================================================================================

void __watcall sbdac_channel_notes_off(short param_1,short unaff_DX)

{
  int iVar1;
  short sVar2;
  ushort uVar3;
  int iVar4;
  
  iVar1 = param_1 * 0x1e;
  sVar2 = 0;
  uVar3 = 1;
  do {
    if (3 < sVar2) {
      return;
    }
    if ((uVar3 & (&unk_f3534)[param_1 * 0xf]) != 0) {
      iVar4 = (int)sVar2;
      if ((&unk_f3534 + param_1 * 0xf == *(ushort **)((int)&unk_f3462 + iVar4 * 0x22)) &&
         (unaff_DX == (&unk_f345c)[iVar4 * 0x11])) {
        if ((&DAT_000f3548)[iVar1] != '\0') {
          *(ushort *)(&DAT_000f3536 + iVar1) = *(ushort *)(&DAT_000f3536 + iVar1) | uVar3;
          return;
        }
        word_f3714 = word_f3714 | uVar3;
        (&DAT_000f345a)[iVar4 * 0x11] = (short)(&DAT_000f345a)[iVar4 * 0x11] >> 1;
        (&DAT_000f34e6)[iVar4 * 0xb] = 1;
        if (sVar2 < 2) {
          return;
        }
        mix_voice_release();
        return;
      }
    }
    uVar3 = uVar3 * 2;
    sVar2 = sVar2 + 1;
  } while( true );
}


// ================================================================================================
// sbdac_note_on @ 0x9f725 [__watcall]
// ================================================================================================

void __watcall sbdac_note_on(short param_1,short unaff_DX,short unaff_BX)

{
  int iVar1;
  short sVar2;
  ushort uVar3;
  int iVar4;
  ushort *puVar5;
  short sVar6;
  short sVar7;
  undefined2 *puVar8;
  undefined2 *local_20;
  
  iVar4 = (int)param_1;
  iVar1 = iVar4 * 0x1e;
  puVar5 = &unk_f3534 + iVar4 * 0xf;
  sVar2 = unaff_DX;
  if (param_1 == 9) {
    if (unaff_DX < 0x24) {
      return;
    }
    if (99 < unaff_DX) {
      return;
    }
    sbdac_program(iVar4,(int)(short)(unaff_DX + 0x5c));
    sVar2 = 0x3c;
  }
  if (*(short *)(&unk_f3538 + iVar1) == 0) {
    return;
  }
  if (*(short *)(&DAT_000f353c + iVar1) == 0) {
    return;
  }
  sVar7 = 32000;
  local_20 = &unk_f3454;
  uVar3 = 1;
  for (sVar6 = 0; sVar6 < 4; sVar6 = sVar6 + 1) {
    iVar4 = (int)sVar6;
    if (((word_f3718 & uVar3 & *(ushort *)(&unk_f3538 + iVar1)) != 0) &&
       ((short)(&DAT_000f345a)[iVar4 * 0x11] < sVar7)) {
      sVar7 = (&DAT_000f345a)[iVar4 * 0x11];
      local_20 = &unk_f3454 + iVar4 * 0x11;
    }
    if ((((uVar3 & *puVar5 & *(ushort *)(&unk_f3538 + iVar1)) != 0) &&
        (puVar5 == *(ushort **)((int)&unk_f3462 + iVar4 * 0x22))) &&
       (puVar8 = &unk_f3454 + iVar4 * 0x11, unaff_DX == (&unk_f345c)[iVar4 * 0x11]))
    goto LAB_0009f8b3;
    uVar3 = uVar3 * 2;
  }
  sVar7 = 0;
  for (uVar3 = *puVar5; uVar3 != 0; uVar3 = uVar3 ^ -uVar3 & uVar3) {
    sVar7 = sVar7 + 1;
  }
  if ((sVar7 < *(short *)(&DAT_000f353c + iVar1)) &&
     (uVar3 = word_f3716 & *(ushort *)(&unk_f3538 + iVar1), uVar3 != 0)) {
    sVar7 = -1;
    for (uVar3 = uVar3 & -uVar3; uVar3 != 0; uVar3 = (short)uVar3 >> 1) {
      sVar7 = sVar7 + 1;
    }
  }
  else {
    uVar3 = word_f3714 & *(ushort *)(&unk_f3538 + iVar1);
    puVar8 = local_20;
    if (uVar3 == 0) goto LAB_0009f8b3;
    sVar7 = -1;
    for (uVar3 = uVar3 & -uVar3; uVar3 != 0; uVar3 = (short)uVar3 >> 1) {
      sVar7 = sVar7 + 1;
    }
  }
  puVar8 = &unk_f3454 + sVar7 * 0x11;
LAB_0009f8b3:
  sbdac_voice_start((int)sVar2,(int)unaff_DX,(int)unaff_BX,puVar5,puVar8);
  return;
}


// ================================================================================================
// sbdac_voice_start @ 0x9f8c5 [__watcall]
// ================================================================================================

void __watcall
sbdac_voice_start(short param_1,ushort unaff_DX,ushort unaff_BX,ushort *unaff_ECX,ushort *param_5)

{
  int iVar1;
  
  sbdac_voice_stop((int)(short)param_5[1]);
  **(ushort **)(param_5 + 7) = **(ushort **)(param_5 + 7) & ~*param_5;
  *(ushort *)(*(int *)(param_5 + 7) + 2) = *(ushort *)(*(int *)(param_5 + 7) + 2) & ~*param_5;
  *(ushort **)(param_5 + 7) = unaff_ECX;
  param_5[6] = unaff_ECX[3];
  *(undefined4 *)(param_5 + 9) = *(undefined4 *)(unaff_ECX + 5);
  iVar1 = *(int *)(unaff_ECX + 7);
  *(int *)(param_5 + 0xb) = iVar1;
  sbdac_voice_setup((int)(short)param_5[1],*(undefined4 *)(param_5 + 9),(int)*(char *)(iVar1 + 8),
            (int)*(char *)(iVar1 + 10),*(undefined *)(iVar1 + 0xd));
  param_5[3] = (ushort)*(byte *)(*(int *)(param_5 + 0xb) + 0xc) << 6;
  param_5[4] = unaff_DX;
  param_5[5] = unaff_BX;
  word_f3716 = word_f3716 & ~*param_5;
  word_f3718 = word_f3718 | *param_5;
  word_f3714 = word_f3714 & ~*param_5;
  *unaff_ECX = *unaff_ECX | *param_5;
  unaff_ECX[1] = unaff_ECX[1] & ~*param_5;
  sbdac_voice_set_timbre((int)(short)param_5[1],unaff_ECX + 9);
  sbdac_voice_volume((int)(short)param_5[1],(int)(short)(*(char *)(*(int *)(unaff_ECX + 7) + 7) + param_1),
            (int)(short)unaff_BX);
  sbdac_voice_controller((int)(short)param_5[1],1,(int)*(char *)((int)unaff_ECX + 0x15));
  sbdac_voice_controller((int)(short)param_5[1],7,(int)*(char *)(unaff_ECX + 9));
  return;
}


// ================================================================================================
// sbdac_voice_setup @ 0x9f9c4 [__watcall]
// ================================================================================================

void __watcall
sbdac_voice_setup(short param_1,int unaff_EDX,undefined2 unaff_BX,undefined2 unaff_CX,undefined2 param_5)

{
  int iVar1;
  int iVar2;
  
  iVar1 = (int)param_1;
  iVar2 = iVar1 * 0x16;
  *(int *)(&DAT_000f34e0 + iVar2) = unaff_EDX;
  *(undefined2 *)(&DAT_000f34ee + iVar2) = unaff_BX;
  (&DAT_000f34ec)[iVar1 * 0xb] = unaff_CX;
  *(undefined2 *)(&DAT_000f34f0 + iVar2) = param_5;
  mix_voice_pitch(iVar1,*(undefined2 *)(unaff_EDX + 0x12));
  mix_voice_sample(iVar1,*(undefined4 *)(unaff_EDX + 0xc),*(undefined4 *)(unaff_EDX + 0x14),
            *(undefined4 *)(unaff_EDX + 0x18),*(undefined4 *)(unaff_EDX + 0x1c));
  return;
}


// ================================================================================================
// sbdac_voice_volume @ 0x9fa1a [__watcall]
// ================================================================================================

void __watcall sbdac_voice_volume(short param_1,short unaff_DX,short unaff_BX)

{
  int iVar1;
  
  iVar1 = param_1 * 0x16;
  *(short *)(&DAT_000f34e8 + iVar1) = unaff_DX;
  *(short *)(&DAT_000f34ea + iVar1) = unaff_DX;
  (&DAT_000f34e6)[param_1 * 0xb] = 3;
  iVar1 = (int)unaff_BX + (int)*(short *)(&DAT_000f34f0 + iVar1);
  if (0x7e < iVar1) {
    iVar1 = 0x7f;
  }
  mix_voice_velocity((int)param_1,(int)unaff_DX,(int)(short)iVar1);
  return;
}


// ================================================================================================
// sbdac_controller @ 0x9fa5d [__watcall]
// ================================================================================================

void __watcall sbdac_controller(short param_1,ushort unaff_DX,short unaff_BX)

{
  ushort uVar1;
  int iVar2;
  short sVar3;
  ushort uVar4;
  undefined uVar5;
  
  iVar2 = param_1 * 0x1e;
  uVar5 = (undefined)unaff_BX;
  if (unaff_DX < 10) {
    if (unaff_DX != 0) {
      if (unaff_DX < 2) {
        (&DAT_000f3549)[iVar2] = uVar5;
      }
      else if (unaff_DX == 7) {
        (&DAT_000f3546)[iVar2] = uVar5;
      }
    }
  }
  else if (unaff_DX < 0xb) {
    (&DAT_000f3547)[iVar2] = uVar5;
  }
  else if (0x3f < unaff_DX) {
    if (unaff_DX < 0x41) {
      (&DAT_000f3548)[iVar2] = uVar5;
      if (unaff_BX == 0) {
        uVar1 = *(ushort *)(&DAT_000f3536 + iVar2);
        *(undefined2 *)(&DAT_000f3536 + iVar2) = 0;
        uVar4 = 1;
        for (sVar3 = 0; sVar3 < 4; sVar3 = sVar3 + 1) {
          if ((uVar4 & uVar1) != 0) {
            sbdac_channel_notes_off((int)param_1,(int)(short)(&unk_f345c)[sVar3 * 0x11]);
          }
          uVar4 = uVar4 * 2;
        }
      }
    }
    else if (unaff_DX == 0x7b) {
      uVar1 = (&unk_f3534)[param_1 * 0xf];
      uVar4 = 1;
      for (sVar3 = 0; sVar3 < 4; sVar3 = sVar3 + 1) {
        if ((uVar4 & uVar1) != 0) {
          sbdac_voice_free(&unk_f3454 + sVar3 * 0x11);
        }
        uVar4 = uVar4 * 2;
      }
    }
  }
  uVar1 = (&unk_f3534)[param_1 * 0xf];
  uVar4 = 1;
  for (sVar3 = 0; sVar3 < 4; sVar3 = sVar3 + 1) {
    if ((uVar4 & uVar1) != 0) {
      sbdac_voice_controller((int)sVar3,(int)(short)unaff_DX,(int)unaff_BX);
    }
    uVar4 = uVar4 * 2;
  }
  return;
}


// ================================================================================================
// sbdac_voice_controller @ 0x9fb93 [__watcall]
// ================================================================================================

void __watcall sbdac_voice_controller(short param_1,short unaff_DX,short unaff_BX,undefined4 unaff_ECX)

{
  if (unaff_DX == 7) {
    mix_voice_volume((int)param_1,(int)unaff_BX,unaff_ECX);
  }
  return;
}


// ================================================================================================
// sbdac_voice_set_timbre @ 0x9fbaa [__watcall]
// ================================================================================================

void __watcall sbdac_voice_set_timbre(short param_1,undefined4 unaff_EDX)

{
  *(undefined4 *)((int)&unk_f34dc + param_1 * 0x16) = unaff_EDX;
  return;
}


// ================================================================================================
// sbdac_voice_free @ 0x9fbb5 [__watcall]
// ================================================================================================

void __watcall sbdac_voice_free(int param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  ushort *extraout_EDX;
  
  sbdac_voice_stop((int)*(short *)(param_1 + 2),param_1,unaff_EBX,unaff_ECX,unaff_EDX,unaff_EBX);
  extraout_EDX[3] = 0;
  word_f3716 = word_f3716 | *extraout_EDX;
  word_f3718 = word_f3718 & ~*extraout_EDX;
  word_f3714 = word_f3714 & ~*extraout_EDX;
  **(ushort **)(extraout_EDX + 7) = **(ushort **)(extraout_EDX + 7) & ~*extraout_EDX;
  *(ushort *)(*(int *)(extraout_EDX + 7) + 2) =
       *(ushort *)(*(int *)(extraout_EDX + 7) + 2) & ~*extraout_EDX;
  return;
}


// ================================================================================================
// sbdac_voice_stop @ 0x9fc04 [__watcall]
// ================================================================================================

void __watcall
sbdac_voice_stop(short param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  (&DAT_000f34e6)[param_1 * 0xb] = 0;
  mix_voice_stop((int)param_1,unaff_EDX,unaff_ECX,unaff_EBX);
  return;
}


// ================================================================================================
// sbdac_program @ 0x9fc24 [__watcall]
// ================================================================================================

void __watcall sbdac_program(short param_1,ushort unaff_DX)

{
  int iVar1;
  int iVar2;
  
  iVar1 = param_1 * 0x1e;
  iVar2 = snd_patch_record(unaff_DX & 0xff);
  *(int *)(&DAT_000f3542 + iVar1) = iVar2;
  if (iVar2 != 0) {
    *(undefined4 *)(&DAT_000f353e + iVar1) = *(undefined4 *)(iVar2 + 0x10);
    if (param_1 == 9) {
      *(undefined2 *)(&DAT_000f353c + iVar1) = 4;
    }
    else {
      *(ushort *)(&DAT_000f353c + iVar1) = (ushort)*(byte *)(*(int *)(&DAT_000f3542 + iVar1) + 6);
    }
    *(ushort *)(&unk_f3538 + iVar1) = *(ushort *)(*(int *)(&DAT_000f3542 + iVar1) + 2) & 0xf;
    *(ushort *)(&DAT_000f353a + iVar1) = unaff_DX;
  }
  return;
}


// ================================================================================================
// sbdac_pitch_bend @ 0x9fc94 [__watcall]
// ================================================================================================

void __watcall sbdac_pitch_bend(short param_1,undefined2 unaff_DX)

{
  *(undefined2 *)(&unk_f354a + param_1 * 0x1e) = unaff_DX;
  return;
}


// ================================================================================================
// dpmi_alloc_dos_memory @ 0x9fcab [__watcall]
// ================================================================================================

int __watcall dpmi_alloc_dos_memory(undefined2 param_1,uint *unaff_EDX,uint *unaff_EBX)

{
  ushort local_34 [2];
  undefined2 local_30;
  ushort local_28;
  undefined local_18 [12];
  
  memset(local_18,0,0xc);
  local_34[0] = 0x100;
  local_30 = param_1;
  int386x(0x31,local_34,local_34,local_18);
  *unaff_EDX = (uint)local_34[0];
  *unaff_EBX = (uint)local_28;
  return *unaff_EDX << 4;
}


// ================================================================================================
// dpmi_free_dos_memory @ 0x9fd01 [__watcall]
// ================================================================================================

void __watcall dpmi_free_dos_memory(undefined2 param_1)

{
  undefined2 local_34 [6];
  undefined2 local_28;
  undefined local_18 [12];
  
  memset(local_18,0,0xc);
  local_34[0] = 0x101;
  local_28 = param_1;
  int386x(0x31,local_34,local_34,local_18);
  return;
}


// ================================================================================================
// sb_mixer_set_volume @ 0x9fd3d [__watcall]
// ================================================================================================

void __watcall sb_mixer_set_volume(int param_1,byte unaff_DL)

{
  int iVar1;
  int iVar2;
  
  iVar1 = param_1 + 4;
  param_1 = param_1 + 5;
  outp(iVar1,4);
  iVar2 = (int)(char)(unaff_DL << 4 | unaff_DL);
  outp(param_1,iVar2);
  outp(iVar1,0x22);
  outp(param_1,iVar2);
  outp(iVar1,0x26);
  outp(param_1,iVar2);
  return;
}


// ================================================================================================
// mpu_drv_default_port @ 0x9fd94 [__watcall]
// ================================================================================================

undefined4 __watcall mpu_drv_default_port(void)

{
  return 0x70330;
}


// ================================================================================================
// mpu_drv_detect @ 0x9fd9a [__watcall]
// ================================================================================================

int __watcall mpu_drv_detect(void)

{
  int iVar1;
  uint param_1;
  
  dword_d5260 = param_1 & 0xffff;
  dword_d5264 = dword_d5260 + 1;
  byte_d5279 = param_1._2_1_;
  byte_d527a = '\x01' << (param_1._2_1_ & 0x1f);
  mpu_send_command();
  pit2_delay();
  mpu_read_data();
  iVar1 = mpu_send_command();
  return iVar1 + 1;
}


// ================================================================================================
// mpu_drv_init @ 0x9fdea [__watcall]
// ================================================================================================

void __watcall mpu_drv_init(void)

{
  uint param_1;
  
  dword_d5260 = param_1 & 0xffff;
  dword_d5264 = dword_d5260 + 1;
  byte_d5279 = param_1._2_1_;
  byte_d527a = '\x01' << (param_1._2_1_ & 0x1f);
  dword_d5268 = 0;
  dword_d526c = 0xff;
  mpu_reset(dword_d5270 | dword_d5274);
  return;
}


// ================================================================================================
// mpu_drv_shutdown @ 0x9fe3b [__watcall]
// ================================================================================================

undefined8 __watcall mpu_drv_shutdown(undefined4 param_1,undefined4 unaff_EDX)

{
  int iVar1;
  
  iVar1 = 0x10;
  do {
    mpu_write_data();
    mpu_write_data();
    mpu_write_data();
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  mpu_send_command();
  pit2_delay();
  mpu_send_command();
  pit2_delay();
  return CONCAT44(unaff_EDX,param_1);
}


// ================================================================================================
// mpu_reset @ 0x9fe94 [__watcall]
// ================================================================================================

void __watcall mpu_reset(void)

{
  mpu_send_command();
  pit2_delay();
  mpu_send_command();
  return;
}


// ================================================================================================
// mpu_send_command @ 0x9feb0 [__watcall]
// ================================================================================================

undefined4 __watcall mpu_send_command(void)

{
  code *pcVar1;
  byte bVar2;
  char cVar3;
  int iVar4;
  undefined in_stack_00000004;
  
  iVar4 = 0xff;
  do {
    bVar2 = in((short)dword_d5264);
    if ((bVar2 & 0x40) == 0) {
      out((short)dword_d5264,in_stack_00000004);
      while( true ) {
        iVar4 = 0xff;
        while (cVar3 = in((short)dword_d5264), cVar3 < '\0') {
          iVar4 = iVar4 + -1;
          if (iVar4 == 0) {
            return 0xffffffff;
          }
        }
        cVar3 = in((short)dword_d5260);
        if (cVar3 == -2) break;
        pcVar1 = (code *)swi(10);
        (*pcVar1)();
      }
      return 0;
    }
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  return 0xffffffff;
}


// ================================================================================================
// pit2_delay @ 0x9ff04 [__watcall]
// ================================================================================================

byte __watcall pit2_delay(void)

{
  byte bVar1;
  char cVar2;
  int in_stack_00000004;
  
  bVar1 = in(0x61);
  out(0x61,bVar1 & 0xfe);
  out(0x43,0xb6);
  out(0x42,0);
  out(0x42,0);
  bVar1 = in(0x61);
  out(0x61,bVar1 | 1);
  do {
    do {
      in(0x42);
      cVar2 = in(0x42);
    } while (cVar2 < '\0');
    do {
      in(0x42);
      cVar2 = in(0x42);
    } while (-1 < cVar2);
    in_stack_00000004 = in_stack_00000004 + -1;
  } while (in_stack_00000004 != 0);
  bVar1 = in(0x61);
  out(0x61,bVar1 & 0xfe);
  return bVar1 & 0xfe;
}


// ================================================================================================
// mpu_read_data @ 0x9ff55 [__watcall]
// ================================================================================================

uint __watcall mpu_read_data(void)

{
  char cVar1;
  byte bVar2;
  int iVar3;
  
  iVar3 = 0xff;
  do {
    cVar1 = in((short)dword_d5264);
    if (-1 < cVar1) {
      bVar2 = in((short)dword_d5260);
      return (uint)bVar2;
    }
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  return 0xffffffff;
}


// ================================================================================================
// mpu_write_data @ 0x9ff78 [__watcall]
// ================================================================================================

undefined8 __watcall mpu_write_data(void)

{
  byte bVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 in_stack_00000004;
  
  iVar2 = 0xff;
  do {
    bVar1 = in((short)dword_d5264);
    if ((bVar1 & 0x40) == 0) {
      out((short)dword_d5260,(char)in_stack_00000004);
      uVar3 = dword_d5260;
      goto LAB_0009ff9e;
    }
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  in_stack_00000004 = 0xffffffff;
  uVar3 = dword_d5264;
LAB_0009ff9e:
  return CONCAT44(uVar3,in_stack_00000004);
}


// ================================================================================================
// mpu_drv_send_midi @ 0x9ffa0 [__watcall]
// ================================================================================================

void __watcall mpu_drv_send_midi(void)

{
  short in_stack_00000004;
  
  empty_func_902a0();
  for (; in_stack_00000004 != 0; in_stack_00000004 = in_stack_00000004 + -1) {
    mpu_write_data();
  }
  return;
}


// ================================================================================================
// dpmi_alloc_dos_buffer @ 0x9ffca [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 __watcall dpmi_alloc_dos_buffer(undefined4 param_1,undefined4 unaff_EDX)

{
  ushort local_48 [2];
  undefined2 uStackY_44;
  ushort uStackY_3c;
  undefined auStackY_2c [16];
  uint uStackY_1c;
  
  __CHK(0x4c);
  memset(auStackY_2c,0,0xc);
  local_48[0] = 0x100;
  uStackY_44 = 0x100;
  int386x(0x31,local_48,local_48,auStackY_2c);
  dword_f55ec = (uint)local_48[0];
  _dword_f55f0 = (uint)uStackY_3c;
  uStackY_1c = (uint)local_48[0] * 0x10;
  if ((uStackY_1c & 0xffff0000) != (uStackY_1c + 0x7ff & 0xffff0000)) {
    uStackY_1c = uStackY_1c + 0x800;
  }
  return CONCAT44(unaff_EDX,uStackY_1c + 0xffff);
}


// ================================================================================================
// dpmi_free_dos_buffer @ 0xa0064 [__watcall]
// ================================================================================================

void __watcall dpmi_free_dos_buffer(void)

{
  undefined2 auStackY_40 [6];
  undefined2 uStackY_34;
  undefined auStackY_24 [12];
  
  __CHK(0x44);
  memset(auStackY_24,0,0xc);
  auStackY_40[0] = 0x101;
  uStackY_34 = dword_f55f0;
  int386x(0x31,auStackY_40,auStackY_40,auStackY_24);
  dword_d53a4 = 0;
  return;
}


// ================================================================================================
// gus_load_patches @ 0xa00c1 [__watcall]
// ================================================================================================

void __watcall gus_load_patches(void)

{
  int iVar1;
  undefined auStack_14c [85];
  ushort uStack_f7;
  char acStack_8c [80];
  undefined4 local_3c;
  undefined4 local_38;
  int local_34;
  uint local_30;
  int *local_2c;
  int local_28;
  int local_24;
  int local_20;
  int iStack_1c;
  
  __CHK(0x15c);
  local_3c = dword_f55f4;
  local_38 = dword_f55f4;
  for (iStack_1c = 0; iStack_1c < 0x100; iStack_1c = iStack_1c + 1) {
    *(undefined2 *)(&unk_f371c + iStack_1c * 0x1c) = 0;
    *(undefined4 *)(&unk_f371e + iStack_1c * 0x1c) = 0;
  }
  local_30 = (uint)((dword_d543c & 1 << (dword_f55e4 & 0x1f)) == 0);
  local_28 = 0;
  for (local_2c = &unk_d5408; *local_2c != -1; local_2c = (int *)((int)local_2c + 0xe)) {
    strcpy(acStack_8c,aCULTRASNDMIDI);
    strcat(acStack_8c,(char *)(local_2c + 1));
    strcat(acStack_8c,(char *)&aPAT);
    iVar1 = gus_patch_check_header(acStack_8c,auStack_14c);
    if (iVar1 == 0) {
      if (9 < (int)((uint)uStack_f7 + local_28)) break;
      local_34 = *local_2c;
      iVar1 = gus_load_patch(acStack_8c,auStack_14c,&unk_f371c + local_34 * 0x1c,&local_3c,0x800,
                        &unk_f55f8 + local_28 * 0x49,local_30);
      if (iVar1 == 0) {
        local_28 = local_28 + (uint)uStack_f7;
      }
      else {
        *(undefined2 *)(&unk_f371c + local_34 * 0x1c) = 0;
        *(undefined4 *)(&unk_f371e + local_34 * 0x1c) = 0;
      }
    }
  }
  iStack_1c = 0;
  while (*(int *)(&unk_d5424 + iStack_1c * 4) != -1) {
    iVar1 = iStack_1c + 1;
    local_20 = *(int *)(&unk_d5424 + iStack_1c * 4);
    iStack_1c = iStack_1c + 2;
    local_24 = *(int *)(&unk_d5424 + iVar1 * 4);
    if (*(short *)(&unk_f371c + local_20 * 0x1c) == 0) {
      memcpy(&unk_f371c + local_20 * 0x1c,&unk_f371c + local_24 * 0x1c,0x1c);
    }
  }
  return;
}


// ================================================================================================
// gus_open @ 0xa0288 [__watcall]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __watcall gus_open(void)

{
  byte bVar1;
  short sVar2;
  int iVar3;
  char *__src;
  undefined4 *puVar4;
  undefined4 *puVar5;
  byte bVar6;
  int local_24;
  int local_20;
  
  bVar6 = 0;
  __CHK(0x38);
  if ((dword_d53a8 == 0) && (sVar2 = gus_probe(0), sVar2 != 0)) {
    dword_f55f4 = dpmi_alloc_dos_buffer();
    bVar1 = byte_f5321;
    word_f531c = 0x1c;
    if (7 < byte_f5320) {
      if (byte_f5321 < 8) {
        byte_f5321 = byte_f5320;
        byte_f5320 = bVar1;
      }
      else {
        byte_f5320 = 5;
      }
    }
    iVar3 = gus_open_card(&word_f531c);
    if (iVar3 == 0) {
      gus_midi_open_voices(0x7f);
      dword_d53a8 = 1;
      _dword_f55e4 = 0;
      for (local_20 = gus_mem_reset(); 0x40000 < local_20; local_20 = local_20 + -0x40000) {
        _dword_f55e4 = _dword_f55e4 + 1;
      }
      dword_f55e8 = gus_mem_alloc(0x801);
      __src = (char *)getenv(aULTRADIR);
      if (__src != (char *)0x0) {
        strcpy(aCULTRASNDMIDI,__src);
        strcat(aCULTRASNDMIDI,aMIDI);
      }
      gus_load_patches();
      gus_stream_open(dword_f55f4,dword_f55e8,0x800);
      dword_f58d4._0_2_ = 0xf;
      dword_f58d4._2_2_ = 0;
      dword_f58d0._2_2_ = 0;
      for (local_24 = 0; local_24 < 4; local_24 = local_24 + 1) {
        *(short *)(&unk_f5324 + local_24 * 0x22) = (short)(1 << ((byte)local_24 & 0x1f));
        *(short *)(&unk_f5326 + local_24 * 0x22) = (short)local_24;
        *(undefined2 **)(&unk_f5332 + local_24 * 0x22) = &unk_d5382;
      }
      for (local_24 = 0; local_24 < 0x10; local_24 = local_24 + 1) {
        puVar4 = (undefined4 *)&unk_d5382;
        puVar5 = (undefined4 *)(&unk_f53ac + local_24 * 0x1e);
        for (iVar3 = 7; iVar3 != 0; iVar3 = iVar3 + -1) {
          *puVar5 = *puVar4;
          puVar4 = puVar4 + (uint)bVar6 * -2 + 1;
          puVar5 = puVar5 + (uint)bVar6 * -2 + 1;
        }
        *(undefined2 *)puVar5 = *(undefined2 *)puVar4;
      }
    }
  }
  return;
}


// ================================================================================================
// gus_close @ 0xa044d [__watcall]
// ================================================================================================

void __watcall gus_close(void)

{
  __CHK(0x1c);
  if ((((dword_d53a8 != 0) && (dword_d53b4 == 0)) && (dword_d53b0 == 0)) && (dword_d53ac == 0)) {
    gus_close_card();
    dpmi_free_dos_buffer();
    dword_d53a4 = 0;
    dword_d53a8 = 0;
    gus_stream_close();
  }
  return;
}


// ================================================================================================
// gus_probe @ 0xa04b9 [__cdecl]
// ================================================================================================

undefined4 gus_probe(void)

{
  int iVar1;
  
  __CHK(0x18);
  empty_func_902a0();
  if (dword_d53a4 == 0) {
    if (dword_d53a0 == 0) {
      iVar1 = gus_parse_ultrasnd(&word_f531c);
      if (iVar1 == 0) {
        return 0;
      }
      dword_d53a0 = 1;
    }
    iVar1 = gus_probe_port(word_f531e);
    if (iVar1 == 0) {
      return 0;
    }
    dword_d53a4 = 1;
  }
  return 1;
}


// ================================================================================================
// gus_drv_detect @ 0xa053c [__watcall]
// ================================================================================================

uint __watcall gus_drv_detect(void)

{
  int iVar1;
  uint uStackY_14;
  
  __CHK(0x18);
  empty_func_902a0();
  iVar1 = gus_parse_ultrasnd(&word_f531c);
  if (iVar1 == 0) {
    uStackY_14 = 0;
  }
  else {
    dword_d53a0 = 1;
    uStackY_14 = (uint)CONCAT12(byte_f5320,word_f531e);
  }
  return uStackY_14;
}


// ================================================================================================
// gus_drv_init_music @ 0xa059b [__watcall]
// ================================================================================================

void __watcall gus_drv_init_music(void)

{
  __CHK(0x14);
  empty_func_902a0();
  if (dword_d53b4 == 0) {
    gus_open();
    dword_d53b4 = 1;
  }
  return;
}


// ================================================================================================
// gus_drv_init_digital @ 0xa05d3 [__watcall]
// ================================================================================================

void __watcall gus_drv_init_digital(void)

{
  __CHK(0x14);
  empty_func_902a0();
  if (dword_d53b0 == 0) {
    gus_open();
    dword_d53b0 = 1;
  }
  return;
}


// ================================================================================================
// gus_drv_shutdown_music @ 0xa060b [__watcall]
// ================================================================================================

void __watcall gus_drv_shutdown_music(void)

{
  __CHK(0x14);
  empty_func_902a0();
  if (dword_d53b4 != 0) {
    dword_d53b4 = 0;
    gus_close();
  }
  return;
}


// ================================================================================================
// gus_drv_shutdown_digital @ 0xa0643 [__watcall]
// ================================================================================================

void __watcall gus_drv_shutdown_digital(void)

{
  __CHK(0x14);
  empty_func_902a0();
  if (dword_d53b0 != 0) {
    dword_d53b0 = 0;
    gus_close();
  }
  return;
}


// ================================================================================================
// gus_drv_tick @ 0xa067b [__watcall]
// ================================================================================================

void __watcall gus_drv_tick(void)

{
  int iVar1;
  int iVar2;
  int local_1c;
  undefined2 uStack_16;
  short sStack_14;
  
  __CHK(0x3c);
  empty_func_902a0();
  sStack_14 = 1;
  for (local_1c = 0; local_1c < 4; local_1c = local_1c + 1) {
    iVar2 = local_1c * 0x22;
    uStack_16 = (undefined2)((uint)(&unk_f5324 + iVar2) >> 0x10);
    if ((int)(CONCAT22(sStack_14,uStack_16) & dword_f58d0) >> 0x10 != 0) {
      iVar1 = gus_dig_voice_active(local_1c);
      if (iVar1 != 0) {
        gus_drv_voice_free(&unk_f5324 + iVar2);
      }
    }
    if (*(short *)(&unk_f532a + iVar2) < 1) {
      *(undefined2 *)(&unk_f532a + iVar2) = 0;
    }
    else {
      *(short *)(&unk_f532a + iVar2) = *(short *)(&unk_f532a + iVar2) + -1;
    }
    sStack_14 = sStack_14 << 1;
  }
  for (local_1c = 0; local_1c < 4; local_1c = local_1c + 1) {
    iVar2 = local_1c * 0x16;
    if (*(short *)(&DAT_000f5596 + iVar2) != 0) {
      gus_dig_update(local_1c,0,0,*(int *)(*(int *)(&unk_f558c + iVar2) + 2) >> 0x10,
                *(int *)(&DAT_000f559a + iVar2) >> 0x10);
    }
  }
  gus_stream_tick();
  return;
}


// ================================================================================================
// gus_drv_control @ 0xa076e [__watcall]
// ================================================================================================

undefined4 __watcall gus_drv_control(void)

{
  uint uVar1;
  undefined4 uVar2;
  int in_stack_00000004;
  ushort local_1c;
  
  __CHK(0x28);
  empty_func_902a0();
  if (dword_d53a8 == 0) {
    return 0xffffffff;
  }
  local_1c = (ushort)in_stack_00000004;
  if (local_1c < 9) {
    if (6 < local_1c) {
      if (7 < local_1c) {
        uVar2 = gus_dig_get_voices();
        return uVar2;
      }
      return 0x56;
    }
  }
  else {
    uVar1 = in_stack_00000004 >> 0x10;
    if (local_1c < 10) {
      uVar2 = gus_dig_voice_active(uVar1);
      return uVar2;
    }
    if (local_1c < 0xb) {
      uVar2 = gus_dig_get_rate(uVar1);
      return uVar2;
    }
    if (local_1c == 0x32) {
      gus_dig_pan(in_stack_00000004 >> 0x18,uVar1 & 0xff);
      return 0xffffffff;
    }
  }
  return 0xffffffff;
}


// ================================================================================================
// gus_set_channel_volume @ 0xa0853 [__watcall]
// ================================================================================================

void __watcall gus_set_channel_volume(void)

{
  int in_stack_00000002;
  undefined2 in_stack_00000008;
  
  __CHK(0x14);
  empty_func_902a0();
  *(undefined2 *)(&unk_f53b0 + (in_stack_00000002 >> 0x10) * 0x1e) = in_stack_00000008;
  return;
}


// ================================================================================================
// gus_play_sample @ 0xa0886 [__watcall]
// ================================================================================================

void __watcall gus_play_sample(void)

{
  int in_stack_00000002;
  int param_6;
  int param_7;
  undefined4 param_8;
  undefined4 in_stack_00000014;
  undefined4 in_stack_00000018;
  undefined4 in_stack_0000001c;
  undefined4 in_stack_00000020;
  undefined4 in_stack_00000024;
  
  __CHK(0x34);
  empty_func_902a0();
  if (dword_d53a8 != 0) {
    gus_dig_play(in_stack_00000002 >> 0x10,param_6 + param_7,param_8,in_stack_00000014,
              in_stack_00000018,in_stack_0000001c,in_stack_00000020,in_stack_00000024);
  }
  return;
}


// ================================================================================================
// gus_program @ 0xa08d7 [__watcall]
// ================================================================================================

void __watcall gus_program(short param_1,ushort unaff_DX)

{
  undefined4 uVar1;
  int iVar2;
  
  __CHK(0x28);
  iVar2 = param_1 * 0x1e;
  uVar1 = snd_patch_record(unaff_DX & 0xff);
  *(undefined4 *)(&DAT_000f53ba + iVar2) = uVar1;
  if (*(int *)(&DAT_000f53ba + iVar2) != 0) {
    *(undefined4 *)(&DAT_000f53b6 + iVar2) = *(undefined4 *)(*(int *)(&DAT_000f53ba + iVar2) + 0x10)
    ;
    if (param_1 == 9) {
      *(undefined2 *)(&DAT_000f53b4 + iVar2) = 4;
    }
    else {
      *(ushort *)(&DAT_000f53b4 + iVar2) = (ushort)*(byte *)(*(int *)(&DAT_000f53ba + iVar2) + 6);
    }
    *(ushort *)(&unk_f53b0 + iVar2) = *(ushort *)(*(int *)(&DAT_000f53ba + iVar2) + 2) & 0xf;
    *(ushort *)(&DAT_000f53b2 + iVar2) = unaff_DX;
  }
  return;
}


// ================================================================================================
// gus_pitch_bend @ 0xa0981 [__watcall]
// ================================================================================================

void __watcall gus_pitch_bend(short param_1,undefined2 unaff_DX)

{
  __CHK(0x20);
  *(undefined2 *)(&unk_f53c2 + param_1 * 0x1e) = unaff_DX;
  return;
}


// ================================================================================================
// gus_voice_stop @ 0xa09b9 [__watcall]
// ================================================================================================

void __watcall gus_voice_stop(short param_1)

{
  __CHK(0x28);
  *(undefined2 *)(&DAT_000f5596 + param_1 * 0x16) = 0;
  gus_dig_release((int)param_1);
  return;
}


// ================================================================================================
// gus_voice_start @ 0xa0a08 [__watcall]
// ================================================================================================

void __watcall
gus_voice_start(short param_1,ushort unaff_DX,ushort unaff_BX,ushort *unaff_ECX,ushort *param_5)

{
  __CHK(0x24);
  gus_voice_stop(*(int *)param_5 >> 0x10);
  **(ushort **)(param_5 + 7) = **(ushort **)(param_5 + 7) & ~*param_5;
  *(ushort *)(*(int *)(param_5 + 7) + 2) = *(ushort *)(*(int *)(param_5 + 7) + 2) & ~*param_5;
  *(ushort **)(param_5 + 7) = unaff_ECX;
  param_5[6] = unaff_ECX[3];
  *(undefined4 *)(param_5 + 9) = *(undefined4 *)(unaff_ECX + 5);
  *(undefined4 *)(param_5 + 0xb) = *(undefined4 *)(unaff_ECX + 7);
  gus_voice_setup(*(int *)param_5 >> 0x10,*(undefined4 *)(param_5 + 9),
            (int)(short)*(char *)(*(int *)(param_5 + 0xb) + 8),
            (int)(short)*(char *)(*(int *)(param_5 + 0xb) + 10),
            *(undefined *)(*(int *)(param_5 + 0xb) + 0xd));
  param_5[3] = (ushort)*(byte *)(*(int *)(param_5 + 0xb) + 0xc) << 6;
  param_5[4] = unaff_DX;
  param_5[5] = unaff_BX;
  dword_f58d4._0_2_ = (ushort)dword_f58d4 & ~*param_5;
  dword_f58d4._2_2_ = dword_f58d4._2_2_ | *param_5;
  dword_f58d0._2_2_ = dword_f58d0._2_2_ & ~*param_5;
  *unaff_ECX = *unaff_ECX | *param_5;
  unaff_ECX[1] = unaff_ECX[1] & ~*param_5;
  gus_voice_set_timbre(*(int *)param_5 >> 0x10,unaff_ECX + 9);
  gus_voice_volume(*(int *)param_5 >> 0x10,(int)(short)(*(char *)(*(int *)(unaff_ECX + 7) + 7) + param_1),
            (int)(short)unaff_BX);
  gus_voice_controller(*(int *)param_5 >> 0x10,1,(int)(short)*(char *)((int)unaff_ECX + 0x15));
  gus_voice_controller(*(int *)param_5 >> 0x10,7,(int)(short)*(char *)(unaff_ECX + 9));
  return;
}


// ================================================================================================
// gus_voice_setup @ 0xa0bac [__watcall]
// ================================================================================================

void __watcall
gus_voice_setup(short param_1,undefined4 unaff_EDX,undefined2 unaff_BX,undefined2 unaff_CX,
         undefined2 param_5)

{
  int iVar1;
  
  __CHK(0x3c);
  iVar1 = param_1 * 0x16;
  *(undefined4 *)(&DAT_000f5590 + iVar1) = unaff_EDX;
  *(undefined2 *)(&DAT_000f559e + iVar1) = unaff_BX;
  *(undefined2 *)(&DAT_000f559c + iVar1) = unaff_CX;
  *(undefined2 *)(&DAT_000f55a0 + iVar1) = param_5;
  gus_dig_set_freq();
  gus_dig_set_sample();
  return;
}


// ================================================================================================
// gus_voice_volume @ 0xa0c5b [__watcall]
// ================================================================================================

void __watcall gus_voice_volume(short param_1,undefined2 unaff_DX)

{
  int iVar1;
  
  __CHK(0x38);
  iVar1 = param_1 * 0x16;
  *(undefined2 *)(&DAT_000f5598 + iVar1) = unaff_DX;
  *(undefined2 *)(&DAT_000f559a + iVar1) = *(undefined2 *)(&DAT_000f5598 + iVar1);
  *(undefined2 *)(&DAT_000f5596 + iVar1) = 3;
  gus_dig_volume();
  return;
}


// ================================================================================================
// gus_voice_set_timbre @ 0xa0d0c [__watcall]
// ================================================================================================

void __watcall gus_voice_set_timbre(short param_1,undefined4 unaff_EDX)

{
  __CHK(0x20);
  *(undefined4 *)(&unk_f558c + param_1 * 0x16) = unaff_EDX;
  return;
}


// ================================================================================================
// gus_voice_controller @ 0xa0d43 [__watcall]
// ================================================================================================

void __watcall gus_voice_controller(short param_1,short unaff_DX,short unaff_BX)

{
  __CHK(0x2c);
  if (unaff_DX == 7) {
    gus_dig_pan((int)param_1,(int)unaff_BX,param_1 * 0x16 + 0x558c);
  }
  return;
}


// ================================================================================================
// gus_patch_drv_send_midi @ 0xa0d99 [__watcall]
// ================================================================================================

void __watcall gus_patch_drv_send_midi(void)

{
  ushort uVar1;
  byte bVar2;
  int iVar3;
  byte *pbVar4;
  short in_stack_00000004;
  byte *in_stack_00000008;
  byte local_34;
  byte *local_2c;
  byte *local_28;
  byte local_1c;
  byte local_18;
  byte bStack_14;
  
  __CHK(0x40);
  empty_func_902a0();
  iVar3 = dword_d4f9a;
  local_1c = 0xc0;
  local_18 = 1;
  bStack_14 = 0;
  uVar1 = 0;
  pbVar4 = &unk_f21fc + dword_d4f9a;
  dword_d4f9a = dword_d4f9a + 4;
  if (dword_d53a8 != 0) {
    local_28 = in_stack_00000008;
    local_2c = pbVar4;
    for (; 0 < in_stack_00000004; in_stack_00000004 = in_stack_00000004 + -1) {
      bVar2 = *local_28;
      if ((bVar2 & 0x80) == 0) {
        *local_2c = bVar2;
        uVar1 = uVar1 + 1;
        local_2c = local_2c + 1;
        if (uVar1 == local_18) {
          uVar1 = 0;
          if (local_1c < 0xb0) {
            local_2c = pbVar4;
            if (0x7f < local_1c) {
              if (local_1c < 0x81) {
                gus_midi_voice_start(*pbVar4,bStack_14);
              }
              else if (local_1c == 0x90) {
                if ((&DAT_000f21fd)[iVar3] == '\0') {
                  gus_midi_voice_start(*pbVar4,bStack_14);
                }
                else if (bStack_14 == 9) {
                  gus_midi_note_on(&unk_f371c + (*pbVar4 + 0x80) * 0x1c,1,*pbVar4,(&DAT_000f21fd)[iVar3],9)
                  ;
                }
                else {
                  gus_midi_note_on(0,1,*pbVar4,(&DAT_000f21fd)[iVar3],bStack_14);
                }
              }
            }
          }
          else if (local_1c < 0xb1) {
            gus_midi_controller(bStack_14,*pbVar4,(&DAT_000f21fd)[iVar3]);
            local_2c = pbVar4;
          }
          else {
            local_2c = pbVar4;
            if (0xbf < local_1c) {
              if (local_1c < 0xc1) {
                if (bStack_14 != 9) {
                  gus_midi_program(&unk_f371c + (uint)*pbVar4 * 0x1c,bStack_14);
                }
              }
              else if (local_1c == 0xe0) {
                gus_midi_note_off(bStack_14,*pbVar4,(&DAT_000f21fd)[iVar3]);
              }
            }
          }
        }
      }
      else {
        local_1c = bVar2 & 0xf0;
        bStack_14 = bVar2 & 0xf;
        if ((bVar2 & 0xf0) == 0xc0) {
          local_34 = 1;
        }
        else {
          local_34 = 2;
        }
        local_18 = local_34;
        uVar1 = 0;
        local_2c = pbVar4;
      }
      local_28 = local_28 + 1;
    }
  }
  dword_d4f9a = dword_d4f9a + -4;
  return;
}


// ================================================================================================
// gus_drv_send_midi @ 0xa0fea [__watcall]
// ================================================================================================

void __watcall gus_drv_send_midi(void)

{
  ushort uVar1;
  byte bVar2;
  int iVar3;
  byte *pbVar4;
  short in_stack_00000004;
  byte *in_stack_00000008;
  byte local_34;
  byte *local_2c;
  byte *local_28;
  byte local_1c;
  byte local_18;
  byte bStackY_14;
  
  __CHK(0x3c);
  empty_func_902a0();
  iVar3 = dword_d4f9a;
  local_1c = 0xc0;
  local_18 = 1;
  bStackY_14 = 0;
  uVar1 = 0;
  pbVar4 = &unk_f21fc + dword_d4f9a;
  dword_d4f9a = dword_d4f9a + 4;
  if (dword_d53a8 != 0) {
    local_28 = in_stack_00000008;
    local_2c = pbVar4;
    for (; 0 < in_stack_00000004; in_stack_00000004 = in_stack_00000004 + -1) {
      bVar2 = *local_28;
      if ((bVar2 & 0x80) == 0) {
        *local_2c = bVar2;
        uVar1 = uVar1 + 1;
        local_2c = local_2c + 1;
        if (uVar1 == local_18) {
          uVar1 = 0;
          if (local_1c < 0xb0) {
            local_2c = pbVar4;
            if (0x7f < local_1c) {
              if (local_1c < 0x81) {
                gus_channel_notes_off(bStackY_14,*pbVar4);
              }
              else if (local_1c == 0x90) {
                if ((&DAT_000f21fd)[iVar3] == '\0') {
                  gus_channel_notes_off(bStackY_14,*pbVar4);
                }
                else {
                  gus_note_on(bStackY_14,*pbVar4,(&DAT_000f21fd)[iVar3]);
                }
              }
            }
          }
          else if (local_1c < 0xb1) {
            gus_controller(bStackY_14,*pbVar4,(&DAT_000f21fd)[iVar3]);
            local_2c = pbVar4;
          }
          else {
            local_2c = pbVar4;
            if (0xbf < local_1c) {
              if (local_1c < 0xc1) {
                gus_program(bStackY_14,*pbVar4);
              }
              else if (local_1c == 0xe0) {
                gus_pitch_bend(bStackY_14,
                          (int)(short)((ushort)(byte)(&DAT_000f21fd)[iVar3] * 0x100 + -0x4000));
              }
            }
          }
        }
      }
      else {
        local_1c = bVar2 & 0xf0;
        bStackY_14 = bVar2 & 0xf;
        if ((bVar2 & 0xf0) == 0xc0) {
          local_34 = 1;
        }
        else {
          local_34 = 2;
        }
        local_18 = local_34;
        uVar1 = 0;
        local_2c = pbVar4;
      }
      local_28 = local_28 + 1;
    }
  }
  dword_d4f9a = dword_d4f9a + -4;
  return;
}


// ================================================================================================
// gus_note_on @ 0xa11fe [__watcall]
// ================================================================================================

void __watcall gus_note_on(short param_1,short unaff_DX,short unaff_BX)

{
  short sVar1;
  undefined *puVar2;
  int iVar3;
  int iVar4;
  ushort *puVar5;
  undefined *puVar6;
  undefined2 local_3c;
  undefined2 uStack_3a;
  undefined2 uStack_26;
  ushort local_24;
  short local_20;
  short local_18;
  short sStack_14;
  
  __CHK(0x4c);
  iVar3 = param_1 * 0x1e;
  puVar5 = (ushort *)(&unk_f53ac + iVar3);
  sStack_14 = unaff_DX;
  if (param_1 == 9) {
    if (unaff_DX < 0x24) {
      return;
    }
    if (99 < unaff_DX) {
      return;
    }
    gus_program(9,(int)(short)(unaff_DX + 0x5c));
    sStack_14 = 0x3c;
  }
  if ((*(short *)(&unk_f53b0 + iVar3) != 0) && (*(short *)(&DAT_000f53b4 + iVar3) != 0)) {
    local_18 = 32000;
    puVar2 = (undefined *)0x5324;
    uStack_3a = 0xf;
    local_24 = 1;
    for (sVar1 = 0; local_3c = SUB42(puVar2,0), sVar1 < 4; sVar1 = sVar1 + 1) {
      iVar4 = sVar1 * 0x22;
      puVar6 = &unk_f5324 + iVar4;
      if (((int)(CONCAT22(local_24,uStack_26) & dword_f58d4 & *(uint *)(&DAT_000f53ae + iVar3)) >>
           0x10 != 0) && (*(short *)(&unk_f532a + iVar4) < local_18)) {
        local_18 = *(short *)(&unk_f532a + iVar4);
        uStack_3a = (undefined2)((uint)puVar6 >> 0x10);
        puVar2 = puVar6;
      }
      if (((((int)(short)(local_24 & *puVar5) & *(int *)(&DAT_000f53ae + iVar3) >> 0x10) != 0) &&
          (puVar5 == *(ushort **)(&unk_f5332 + iVar4))) &&
         (unaff_DX == *(short *)(&DAT_000f532c + iVar4))) {
        gus_voice_start((int)sStack_14,(int)unaff_DX,(int)unaff_BX,puVar5,puVar6);
        return;
      }
      local_24 = local_24 << 1;
    }
    sVar1 = 0;
    for (local_24 = *puVar5; local_24 != 0; local_24 = local_24 ^ -local_24 & local_24) {
      sVar1 = sVar1 + 1;
    }
    if (sVar1 < *(short *)(&DAT_000f53b4 + iVar3)) {
      local_24 = (ushort)dword_f58d4 & *(ushort *)(&unk_f53b0 + iVar3);
      if (local_24 != 0) {
        local_20 = -1;
        for (local_24 = local_24 & -local_24; local_24 != 0; local_24 = (short)local_24 >> 1) {
          local_20 = local_20 + 1;
        }
        gus_voice_start((int)sStack_14,(int)unaff_DX,(int)unaff_BX,puVar5,&unk_f5324 + local_20 * 0x22);
        return;
      }
    }
    local_24 = dword_f58d0._2_2_ & *(ushort *)(&unk_f53b0 + iVar3);
    if (local_24 == 0) {
      gus_voice_start((int)sStack_14,(int)unaff_DX,(int)unaff_BX,puVar5,CONCAT22(uStack_3a,local_3c));
    }
    else {
      local_20 = -1;
      for (local_24 = local_24 & -local_24; local_24 != 0; local_24 = (short)local_24 >> 1) {
        local_20 = local_20 + 1;
      }
      gus_voice_start((int)sStack_14,(int)unaff_DX,(int)unaff_BX,puVar5,&unk_f5324 + local_20 * 0x22);
    }
  }
  return;
}


// ================================================================================================
// gus_channel_notes_off @ 0xa14af [__watcall]
// ================================================================================================

void __watcall gus_channel_notes_off(undefined4 param_1,undefined4 unaff_EDX)

{
  short sVar1;
  int iVar2;
  int iVar3;
  short local_28;
  undefined2 uStackY_26;
  ushort local_24;
  undefined2 uStackY_1e;
  
  __CHK(0x3c);
  local_28 = (short)param_1;
  uStackY_26 = (undefined2)((uint)param_1 >> 0x10);
  uStackY_1e = (undefined2)((uint)unaff_EDX >> 0x10);
  iVar2 = local_28 * 0x1e;
  sVar1 = 0;
  local_24 = 1;
  while( true ) {
    if (3 < sVar1) {
      return;
    }
    if ((((int)(CONCAT22(local_24,uStackY_26) &
               CONCAT22(*(undefined2 *)(&unk_f53ac + iVar2),uStackY_1e)) >> 0x10 != 0) &&
        (iVar3 = sVar1 * 0x22,
        (undefined2 *)(&unk_f53ac + iVar2) == *(undefined2 **)(&unk_f5332 + iVar3))) &&
       ((short)unaff_EDX == *(short *)(&DAT_000f532c + iVar3))) break;
    sVar1 = sVar1 + 1;
    local_24 = local_24 << 1;
  }
  if ((&DAT_000f53c0)[iVar2] != '\0') {
    *(ushort *)(&DAT_000f53ae + iVar2) = *(ushort *)(&DAT_000f53ae + iVar2) | local_24;
    return;
  }
  dword_f58d0._2_2_ = dword_f58d0._2_2_ | local_24;
  *(short *)(&unk_f532a + iVar3) = *(short *)(&unk_f532a + iVar3) >> 1;
  *(undefined2 *)(&DAT_000f5596 + sVar1 * 0x16) = 1;
  gus_dig_stop();
  return;
}


// ================================================================================================
// gus_drv_voice_free @ 0xa15aa [__watcall]
// ================================================================================================

void __watcall gus_drv_voice_free(ushort *param_1)

{
  __CHK(0x20);
  gus_voice_stop(*(int *)param_1 >> 0x10);
  param_1[3] = 0;
  dword_f58d4._0_2_ = (ushort)dword_f58d4 | *param_1;
  dword_f58d4._2_2_ = dword_f58d4._2_2_ & ~*param_1;
  dword_f58d0._2_2_ = dword_f58d0._2_2_ & ~*param_1;
  **(ushort **)(param_1 + 7) = **(ushort **)(param_1 + 7) & ~*param_1;
  *(ushort *)(*(int *)(param_1 + 7) + 2) = *(ushort *)(*(int *)(param_1 + 7) + 2) & ~*param_1;
  return;
}


// ================================================================================================
// gus_controller @ 0xa1632 [__watcall]
// ================================================================================================

void __watcall gus_controller(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX)

{
  int iVar1;
  undefined2 uVar2;
  int iVar3;
  ushort local_28;
  undefined2 uStackY_26;
  undefined local_24;
  undefined uStackY_23;
  short local_20;
  undefined2 uStackY_1e;
  short sStackY_1c;
  short sStackY_18;
  undefined2 uStackY_16;
  
  __CHK(0x34);
  local_20 = (short)param_1;
  uStackY_1e = (undefined2)((uint)param_1 >> 0x10);
  local_28 = (ushort)unaff_EDX;
  uStackY_26 = (undefined2)((uint)unaff_EDX >> 0x10);
  local_24 = (undefined)unaff_EBX;
  uStackY_23 = (undefined)((uint)unaff_EBX >> 8);
  iVar3 = local_20 * 0x1e;
  if (local_28 < 10) {
    if (local_28 != 0) {
      if (local_28 < 2) {
        (&DAT_000f53c1)[iVar3] = local_24;
      }
      else if (local_28 == 7) {
        (&DAT_000f53be)[iVar3] = local_24;
      }
    }
  }
  else if (local_28 < 0xb) {
    (&DAT_000f53bf)[iVar3] = local_24;
  }
  else if (0x3f < local_28) {
    if (local_28 < 0x41) {
      (&DAT_000f53c0)[iVar3] = local_24;
      if ((short)unaff_EBX == 0) {
        uVar2 = *(undefined2 *)(&DAT_000f53ae + iVar3);
        *(undefined2 *)(&DAT_000f53ae + iVar3) = 0;
        iVar1 = 0;
        sStackY_1c = 1;
        while( true ) {
          uStackY_16 = (undefined2)((uint)iVar1 >> 0x10);
          sStackY_18 = (short)iVar1;
          if (3 < sStackY_18) break;
          if ((int)(CONCAT22(sStackY_1c,uStackY_1e) & CONCAT22(uVar2,uStackY_16)) >> 0x10 != 0) {
            gus_channel_notes_off((int)local_20,*(int *)(&unk_f532a + sStackY_18 * 0x22) >> 0x10);
          }
          iVar1 = iVar1 + 1;
          sStackY_1c = sStackY_1c << 1;
        }
      }
    }
    else if (local_28 == 0x7b) {
      uVar2 = *(undefined2 *)(&unk_f53ac + iVar3);
      sStackY_1c = 1;
      for (sStackY_18 = 0; sStackY_18 < 4; sStackY_18 = sStackY_18 + 1) {
        if ((int)(CONCAT22(sStackY_1c,uStackY_1e) & CONCAT22(uVar2,uStackY_16)) >> 0x10 != 0) {
          gus_drv_voice_free(&unk_f5324 + sStackY_18 * 0x22);
        }
        sStackY_1c = sStackY_1c << 1;
      }
    }
  }
  uVar2 = *(undefined2 *)(&unk_f53ac + iVar3);
  sStackY_1c = 1;
  for (sStackY_18 = 0; sStackY_18 < 4; sStackY_18 = sStackY_18 + 1) {
    if ((int)(CONCAT22(sStackY_1c,uStackY_1e) & CONCAT22(uVar2,uStackY_16)) >> 0x10 != 0) {
      gus_voice_controller((int)sStackY_18,(int)(short)local_28,
                CONCAT13(uStackY_23,CONCAT12(local_24,uStackY_26)) >> 0x10);
    }
    sStackY_1c = sStackY_1c << 1;
  }
  return;
}


// ================================================================================================
// printstr_centered @ 0xa1800 [__cdecl]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void printstr_centered(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  
  iVar2 = _dword_d30b4 - dword_d30ac;
  iVar1 = textwidth(param_1);
  printstr_at(param_1,(iVar2 - iVar1 >> 1) + dword_d30ac + 1,param_2);
  return;
}


// ================================================================================================
// window_clip_full @ 0xa1840 [__cdecl]
// ================================================================================================

void window_clip_full(undefined4 *param_1)

{
  window_setclip(param_1,0,*param_1,0,param_1[1]);
  return;
}


// ================================================================================================
// setclip_screen @ 0xa185c [__watcall]
// ================================================================================================

void __watcall setclip_screen(void)

{
  setclip(0,dword_d30a4,0,dword_d30a8);
  return;
}


// ================================================================================================
// debug_break @ 0xa1877 [__watcall]
// ================================================================================================

undefined4 __watcall debug_break(undefined4 param_1,undefined2 unaff_DX)

{
  code *pcVar1;
  undefined4 uVar2;
  
  if (byte_d5440 != '\0') {
    pcVar1 = (code *)swi(3);
    uVar2 = (*pcVar1)(unaff_DX);
    return uVar2;
  }
  return 0;
}


// ================================================================================================
// return_one_a188b @ 0xa188b [__watcall]
// ================================================================================================

undefined4 __watcall return_one_a188b(void)

{
  return 1;
}


// ================================================================================================
// return_zero_a189a @ 0xa189a [__watcall]
// ================================================================================================

undefined4 __watcall return_zero_a189a(void)

{
  return 0;
}


// ================================================================================================
// __int386x @ 0xa189e [__watcall]
// ================================================================================================

void __watcall
__int386x(undefined4 param_1,undefined4 *unaff_EDX,undefined2 *unaff_EBX,undefined4 unaff_ECX)

{
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  undefined2 in_ES;
  undefined2 in_DS;
  byte in_CF;
  undefined8 uVar1;
  
  uVar1 = __dointerrupt();
  *unaff_EDX = (int)uVar1;
  unaff_EDX[1] = unaff_EBX;
  unaff_EDX[2] = unaff_ECX;
  unaff_EDX[3] = (int)((ulonglong)uVar1 >> 0x20);
  unaff_EDX[4] = unaff_ESI;
  unaff_EDX[5] = unaff_EDI;
  unaff_EDX[6] = -(uint)in_CF;
  unaff_EBX[3] = in_DS;
  *unaff_EBX = in_ES;
  return;
}


// ================================================================================================
// __dointerrupt @ 0xa18d6 [__watcall]
// ================================================================================================

undefined8 __watcall __dointerrupt(void)

{
  undefined4 *unaff_EDI;
  
  return CONCAT44(unaff_EDI[3],*unaff_EDI);
}


// ================================================================================================
// _DoINTR @ 0xa18fb [__watcall]
// ================================================================================================

undefined8 __watcall
_DoINTR(undefined4 param_1,undefined4 *unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  undefined4 unaff_EBP;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  undefined2 in_ES;
  undefined2 in_DS;
  undefined2 in_FS;
  undefined2 in_GS;
  byte in_CF;
  byte in_PF;
  byte in_AF;
  byte in_ZF;
  byte in_SF;
  byte in_TF;
  byte in_IF;
  byte in_OF;
  byte in_NT;
  undefined8 uVar1;
  
  uVar1 = __dointr_call();
  *unaff_EDX = (int)uVar1;
  *(ushort *)(unaff_EDX + 9) =
       (ushort)(in_NT & 1) * 0x4000 | (ushort)(in_OF & 1) * 0x800 | (ushort)(in_IF & 1) * 0x200 |
       (ushort)(in_TF & 1) * 0x100 | (ushort)(in_SF & 1) * 0x80 | (ushort)(in_ZF & 1) * 0x40 |
       (ushort)(in_AF & 1) * 0x10 | (ushort)(in_PF & 1) * 4 | (ushort)(in_CF & 1);
  unaff_EDX[2] = unaff_ECX;
  unaff_EDX[3] = (int)((ulonglong)uVar1 >> 0x20);
  unaff_EDX[5] = unaff_ESI;
  unaff_EDX[6] = unaff_EDI;
  unaff_EDX[4] = unaff_EBP;
  *(undefined2 *)(unaff_EDX + 7) = in_DS;
  unaff_EDX[1] = unaff_EBX;
  *(undefined2 *)((int)unaff_EDX + 0x1e) = in_ES;
  *(undefined2 *)(unaff_EDX + 8) = in_FS;
  *(undefined2 *)((int)unaff_EDX + 0x22) = in_GS;
  return CONCAT44(unaff_EDX,param_1);
}


// ================================================================================================
// __dointr_call @ 0xa1948 [__watcall]
// ================================================================================================

undefined8 __watcall __dointr_call(undefined4 param_1,undefined4 *unaff_EDX)

{
  return CONCAT44(unaff_EDX[3],*unaff_EDX);
}


// ================================================================================================
// unk_a197c @ 0xa197c
// ================================================================================================

void unk_a197c(void)

{
  code *pcVar1;
  
  pcVar1 = (code *)swi(0);
  (*pcVar1)();
  return;
}


// ================================================================================================
// __Slash_C @ 0xa1c7c [__watcall]
// ================================================================================================

undefined * __watcall __Slash_C(undefined *param_1,char unaff_DL,undefined4 unaff_EBX)

{
  code *pcVar1;
  undefined extraout_DL;
  
  if (unaff_DL == '\0') {
    pcVar1 = (code *)swi(0x21);
    (*pcVar1)(unaff_EBX);
    *param_1 = extraout_DL;
  }
  else {
    *param_1 = 0x2f;
  }
  param_1[1] = 99;
  param_1[2] = 0;
  return param_1;
}


// ================================================================================================
// __file_exists_attr @ 0xa1ca2 [__watcall]
// ================================================================================================

undefined8 __watcall __file_exists_attr(undefined4 param_1,undefined4 unaff_EDX)

{
  int iVar1;
  undefined local_38 [44];
  
  iVar1 = _dos_findfirst(param_1,7,local_38);
  return CONCAT44(unaff_EDX,(uint)(iVar1 == 0));
}


// ================================================================================================
// __spawn_with_args @ 0xa1cc1 [__watcall]
// ================================================================================================

void __watcall
__spawn_with_args(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX,
         undefined4 param_5)

{
  __ccmdline(unaff_EDX,param_5,unaff_EBX,0,param_1,unaff_ECX);
  __dospawn(param_1,unaff_EDX,unaff_EBX,unaff_ECX,param_5);
  return;
}


// ================================================================================================
// spawnve @ 0xa1cf4 [__watcall]
// ================================================================================================

/* WARNING: Removing unreachable block (ram,0x000a1ec8) */
/* WARNING: Removing unreachable block (ram,0x000a1f9d) */
/* WARNING: Type propagation algorithm not settling */

undefined4 __watcall
spawnve(uint param_1,char *unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  char **ppcVar1;
  int iVar2;
  size_t sVar3;
  undefined *puVar4;
  uint uVar5;
  undefined4 uVar6;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  char *pcVar7;
  undefined4 extraout_EDX_01;
  undefined4 extraout_EDX_02;
  undefined4 uVar8;
  char **ppcVar9;
  uint *puVar10;
  uint *puVar11;
  undefined2 in_DS;
  byte bVar12;
  undefined8 uVar13;
  undefined8 uVar14;
  uint local_c4 [28];
  undefined4 local_54;
  char *local_50;
  char *local_4c;
  char **local_48;
  undefined local_44 [4];
  int local_40;
  undefined local_3c [4];
  undefined local_38 [4];
  undefined4 local_34;
  char **local_30;
  int local_2c;
  char *local_28;
  char **local_20;
  undefined4 local_1c;
  char *local_18;
  
  bVar12 = 0;
  __CHK(0xe4);
  local_c4[0] = param_1;
  if (1 < param_1) {
    __set_errno(9);
    return 0xffffffff;
  }
  iVar2 = __cenvarg(unaff_EBX,unaff_ECX,&local_34,local_38,local_3c,&local_40,0);
  puVar10 = local_c4;
  puVar11 = local_c4;
  if (iVar2 == -1) {
    return 0xffffffff;
  }
  sVar3 = strlen(unaff_EDX);
  uVar13 = malloc(sVar3 + 0x9a);
  local_2c = (int)uVar13;
  if (local_2c == 0) {
    uVar5 = (int)((ulonglong)uVar13 >> 0x20) + 3U & 0xfffffffc;
    uVar13 = stackavail();
    if (uVar5 < (uint)uVar13) {
      iVar2 = -uVar5;
      puVar10 = (uint *)((int)local_c4 + iVar2);
      puVar4 = (undefined *)((int)local_c4 + iVar2);
    }
    else {
      puVar4 = (undefined *)0x0;
    }
    uVar13 = CONCAT44((int)((ulonglong)uVar13 >> 0x20),puVar4);
    puVar11 = puVar10;
    if (puVar4 == (undefined *)0x0) {
      *(undefined4 *)((int)puVar10 + -4) = 0xa1d98;
      free(local_34);
      return 0xffffffff;
    }
  }
  local_18 = (char *)uVar13;
  *(char ***)((int)puVar11 + -4) = &local_50;
  *(undefined4 **)((int)puVar11 + -8) = &local_54;
  *(undefined4 *)((int)puVar11 + -0xc) = 0xa1dbb;
  __splitpath_drive(unaff_EDX,local_18 + (int)((ulonglong)uVar13 >> 0x20) + -0x93,&local_4c,&local_48);
  *(undefined4 *)((int)puVar11 + -4) = 0xa1dc4;
  (*(code *)funcptr_d6600)();
  iVar2 = local_40;
  *(undefined4 *)((int)puVar11 + -4) = 0xa1dcc;
  local_30 = (char **)malloc(iVar2);
  local_20 = local_30;
  if (local_30 == (char **)0x0) {
    uVar5 = local_40 + 3U & 0xfffffffc;
    *(undefined4 *)((int)puVar11 + -4) = 0xa1de4;
    uVar13 = stackavail(uVar5,uVar5);
    if ((uint)((ulonglong)uVar13 >> 0x20) < (uint)uVar13) {
      iVar2 = -(local_40 + 3U & 0xfffffffc);
      local_20 = (char **)((int)puVar11 + iVar2);
      puVar11 = (uint *)((int)puVar11 + iVar2);
    }
    else {
      local_20 = (char **)0x0;
    }
    if (local_20 == (char **)0x0) {
      *(undefined4 *)((int)puVar11 + -4) = 0xa1e09;
      __set_errno(2);
      *(undefined4 *)((int)puVar11 + -4) = 0xa1e1a;
      __set_doserrno(10);
      uVar13 = CONCAT44(extraout_EDX,0xffffffff);
      ppcVar9 = &local_4c;
      goto LAB_000a1fc3;
    }
  }
  if (((2 < byte_d4d0f) && (*local_4c == '\0')) && (*(char *)local_48 == '\0')) {
    local_48 = (char **)&unk_c4ab4;
  }
  *(char **)((int)puVar11 + -4) = local_50;
  ppcVar9 = local_48;
  *(undefined4 *)((int)puVar11 + -8) = 0xa1e56;
  _makepath(local_18,local_4c,ppcVar9,local_54);
  *(undefined4 *)((int)puVar11 + -4) = 0xa1e60;
  __set_errno(1);
  if (*local_50 == '\0') {
    *(undefined4 *)((int)puVar11 + -4) = 0xa1ebd;
    sVar3 = strlen(local_18);
    pcVar7 = local_18 + sVar3;
    local_28 = pcVar7;
    *(undefined2 *)((int)puVar11 + -4) = in_DS;
    *(undefined4 *)pcVar7 = aCom;
    pcVar7[(uint)bVar12 * -8 + 4] = (&DAT_000c4ac0)[(uint)bVar12 * -8];
    *(undefined4 *)((int)puVar11 + -4) = 0xa1eec;
    __set_errno(0,local_18,local_20);
    *(undefined4 *)((int)puVar11 + -4) = unaff_EBX;
    uVar6 = local_34;
    uVar5 = local_c4[0];
    *(undefined4 *)((int)puVar11 + -8) = 0xa1efa;
    uVar6 = __spawn_with_args(uVar5,extraout_EDX_01,local_20,uVar6);
    *(undefined4 *)((int)puVar11 + -4) = 0xa1f02;
    uVar14 = __get_errno_ptr();
    pcVar7 = local_28;
    uVar13 = CONCAT44((int)((ulonglong)uVar14 >> 0x20),uVar6);
    ppcVar9 = local_20;
    if (*(int *)uVar14 != 1) goto LAB_000a1fc3;
    *(undefined4 *)((int)puVar11 + -4) = 0xa1f1b;
    __set_errno(0,local_18,local_20);
    *(undefined2 *)((int)puVar11 + -4) = in_DS;
    *(undefined4 *)((int)puVar11 + -4) = unaff_EBX;
    *(undefined4 *)pcVar7 = aExe;
    uVar6 = local_34;
    uVar5 = local_c4[0];
    pcVar7[(uint)bVar12 * -8 + 4] = (&DAT_000c4ac5)[(uint)bVar12 * -8];
    *(undefined4 *)((int)puVar11 + -8) = 0xa1f32;
    uVar6 = __spawn_with_args(uVar5,extraout_EDX_02,local_20,uVar6);
    *(undefined4 *)((int)puVar11 + -4) = 0xa1f3a;
    uVar14 = __get_errno_ptr();
    pcVar7 = local_28;
    uVar8 = (undefined4)((ulonglong)uVar14 >> 0x20);
    uVar13 = CONCAT44(uVar8,uVar6);
    if (*(int *)uVar14 != 1) goto LAB_000a1fc3;
    *(undefined4 *)((int)puVar11 + -4) = 0xa1f52;
    __set_errno(0,uVar8,local_20);
    *(undefined4 *)pcVar7 = aBat;
    pcVar7[(uint)bVar12 * -8 + 4] = (&DAT_000c4abb)[(uint)bVar12 * -8];
    *(undefined4 *)((int)puVar11 + -4) = 0xa1f5c;
    uVar14 = __file_exists_attr(local_18);
    uVar13 = CONCAT44((int)((ulonglong)uVar14 >> 0x20),uVar6);
    iVar2 = (int)uVar14;
  }
  else {
    *(undefined4 *)((int)puVar11 + -4) = 0xa1e72;
    iVar2 = stricmp(local_50,&aBat);
    if (iVar2 != 0) {
      *(undefined4 *)((int)puVar11 + -4) = 0xa1e9f;
      __set_errno(0,local_18,local_20);
      *(undefined4 *)((int)puVar11 + -4) = unaff_EBX;
      uVar6 = local_34;
      uVar5 = local_c4[0];
      *(undefined4 *)((int)puVar11 + -8) = 0xa1ead;
      uVar13 = __spawn_with_args(uVar5,extraout_EDX_00,local_20,uVar6);
      ppcVar9 = local_20;
      goto LAB_000a1fc3;
    }
    *(undefined4 *)((int)puVar11 + -4) = 0xa1e85;
    uVar14 = __file_exists_attr(local_18);
    uVar13 = CONCAT44((int)((ulonglong)uVar14 >> 0x20),0xffffffff);
    iVar2 = (int)uVar14;
  }
  if (iVar2 != 0) {
    *(undefined4 *)((int)puVar11 + -4) = 0xa1f73;
    free(local_34,unaff_EBX,local_20,1);
    local_34 = 0;
    *(undefined4 *)((int)puVar11 + -4) = 0xa1f82;
    __ccmdline(local_18);
    *(undefined4 *)((int)puVar11 + -4) = 0;
    *(char ***)((int)puVar11 + -8) = local_20;
    *(char **)((int)puVar11 + -0xc) = local_18;
    *(undefined4 *)((int)puVar11 + -0x10) = 0xa1f96;
    uVar6 = __Slash_C(local_44,0);
    *(undefined4 *)((int)puVar11 + -0x10) = uVar6;
    *(char **)((int)puVar11 + -0x14) = aCOMMAND;
    *(undefined4 *)((int)puVar11 + -0x18) = 0xa1fb4;
    uVar6 = getenv(aCOMSPEC);
    *(undefined4 *)((int)puVar11 + -0x18) = uVar6;
    *(uint *)((int)puVar11 + -0x1c) = local_c4[0];
    *(undefined4 *)((int)puVar11 + -0x20) = 0xa1fbd;
    uVar13 = spawnl();
    ppcVar9 = local_20;
  }
LAB_000a1fc3:
  ppcVar1 = local_30;
  local_1c = (undefined4)uVar13;
  *(undefined4 *)((int)puVar11 + -4) = 0xa1fcb;
  free(ppcVar1,(int)((ulonglong)uVar13 >> 0x20),ppcVar9);
  iVar2 = local_2c;
  *(undefined4 *)((int)puVar11 + -4) = 0xa1fd3;
  free(iVar2);
  uVar6 = local_34;
  *(undefined4 *)((int)puVar11 + -4) = 0xa1fdb;
  free(uVar6);
  *(undefined4 *)((int)puVar11 + -4) = 0xa1fe4;
  (*(code *)funcptr_d6604)();
  return local_1c;
}


// ================================================================================================
// draw_textured_triangle @ 0xa2000 [__cdecl]
// ================================================================================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void draw_textured_triangle(int param_1,int param_2,int *param_3)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  int *piVar7;
  int *piVar8;
  int *piVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  uint uVar15;
  int iVar16;
  int iVar17;
  uint uVar18;
  bool bVar19;
  uint local_6c;
  int local_58;
  int local_54;
  int local_50;
  int local_4c;
  uint local_48;
  uint local_44;
  int local_40;
  int local_3c;
  int local_30;
  int local_2c;
  int local_28;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  
  iVar11 = *(int *)(param_1 + 2) >> 0x10;
  texture_set(param_1 + 0x10,&unk_f6138);
  uVar15 = 0;
  uVar18 = 0;
  iVar17 = param_3[1];
  local_58 = *param_3;
  uVar2 = 1;
  piVar6 = param_3;
  local_3c = local_58;
  local_1c = iVar17;
  do {
    piVar7 = piVar6 + 2;
    iVar3 = piVar6[3];
    if (local_1c < iVar3) {
      local_58 = *piVar7;
      uVar15 = uVar2;
      local_1c = iVar3;
    }
    else if (iVar3 < iVar17) {
      local_3c = *piVar7;
      iVar17 = iVar3;
      uVar18 = uVar2;
    }
    uVar2 = uVar2 + 1;
    piVar6 = piVar7;
  } while ((int)uVar2 < 3);
  iVar3 = local_58 - local_3c;
  iVar4 = local_1c - iVar17;
  if (iVar4 == 0) {
    return;
  }
  iVar5 = 3 - (uVar18 | uVar15);
  iVar10 = (param_3 + iVar5 * 2)[1];
  iVar1 = param_3[iVar5 * 2];
  iVar13 = iVar1 - (((iVar10 - iVar17) * iVar3) / iVar4 + local_3c);
  bVar19 = iVar13 < 0;
  if (bVar19) {
    iVar13 = -iVar13;
  }
  local_6c = (uint)bVar19;
  if (iVar13 == 0) {
    return;
  }
  if (0x5ff < iVar13) {
    return;
  }
  iVar13 = iVar13 + 2;
  piVar6 = (int *)(param_2 + iVar5 * 8);
  piVar7 = (int *)(param_2 + uVar18 * 8);
  piVar8 = (int *)(param_2 + uVar15 * 8);
  local_50 = ((*piVar6 - (*piVar8 + ((*piVar7 - *piVar8) * (local_1c - iVar10)) / iVar4)) * 0x10000)
             / iVar13;
  local_54 = ((piVar6[1] - (piVar8[1] + ((piVar7[1] - piVar8[1]) * (local_1c - iVar10)) / iVar4)) *
             0x10000) / iVar13;
  if (local_6c != 0) {
    local_50 = -local_50;
    local_54 = -local_54;
  }
  piVar9 = &unk_f6138;
  iVar5 = 0x8000;
  iVar16 = 0x8000;
  while (iVar13 = iVar13 + -1, iVar13 != -1) {
    *piVar9 = (iVar16 >> 0x10) * iVar11 + (iVar5 >> 0x10);
    piVar9 = piVar9 + 1;
    iVar5 = iVar5 + local_50;
    iVar16 = iVar16 + local_54;
  }
  local_14 = local_3c * 0x10000 + 0x8000;
  iVar13 = local_3c * 0x10000 + 0x10000;
  iVar5 = *piVar7 * 0x10000 + 0x8000;
  local_18 = piVar7[1] * 0x10000 + 0x8000;
  local_30 = 0;
  local_2c = 0;
  if (local_6c == 0) {
    iVar16 = iVar17 - local_1c;
    if (iVar16 == 0) goto LAB_000a22e5;
    local_2c = ((*piVar7 - *piVar8) * 0x10000) / iVar16;
    iVar12 = piVar7[1] - piVar8[1];
  }
  else {
    iVar16 = iVar17 - iVar10;
    if (iVar16 == 0) goto LAB_000a22e5;
    local_2c = ((*piVar7 - *piVar6) * 0x10000) / iVar16;
    iVar12 = piVar7[1] - piVar6[1];
  }
  local_30 = (iVar12 * 0x10000) / iVar16;
LAB_000a22e5:
  local_4c = 0;
  local_40 = 0;
  if (iVar17 != iVar10) {
    iVar16 = iVar17 - iVar10;
    iVar12 = (local_3c - iVar1) * 0x10000;
    if (local_6c == 0) {
      if (iVar16 != 0) {
        local_40 = iVar12 / iVar16;
        local_4c = (iVar3 * 0x10000) / iVar4;
      }
    }
    else if (iVar16 != 0) {
      local_4c = iVar12 / iVar16;
      local_40 = (iVar3 * 0x10000) / iVar4;
    }
    iVar13 = iVar13 + local_40 / 2;
    if (iVar17 < iVar10) {
      local_20 = iVar17 * 4;
      do {
        if (dword_d30b8 <= iVar17) {
          return;
        }
        iVar14 = local_14 >> 0x10;
        iVar16 = ((iVar13 >> 0x10) - iVar14) + 1;
        iVar12 = (iVar14 + iVar16) - _dword_d30b4;
        if (0 < iVar12) {
          iVar16 = iVar16 - iVar12;
        }
        iVar12 = dword_d30ac - iVar14;
        if (iVar12 < 1) {
          iVar12 = 0;
        }
        else {
          iVar16 = iVar16 - iVar12;
          iVar14 = iVar14 + iVar12;
          if (0x600 < iVar12) {
            return;
          }
        }
        if ((0 < iVar16) && (dword_d30b0 < iVar17)) {
          texture_span(iVar14 + *(int *)(off_d30cc + local_20),
                    (iVar5 >> 0x10) + iVar11 * (local_18 >> 0x10) + (&unk_f6138)[iVar12],iVar16);
        }
        iVar5 = iVar5 + local_2c;
        local_18 = local_18 + local_30;
        local_14 = local_14 + local_4c;
        iVar13 = iVar13 + local_40;
        local_20 = local_20 + 4;
        iVar17 = iVar17 + 1;
      } while (iVar17 < iVar10);
    }
  }
  if (iVar17 != local_1c) {
    iVar10 = iVar10 - local_1c;
    iVar16 = (iVar1 - local_58) * 0x10000;
    if (local_6c == 0) {
      local_44 = local_6c;
      local_48 = local_6c;
      if (iVar10 != 0) {
        local_48 = iVar16 / iVar10;
        local_44 = (iVar3 * 0x10000) / iVar4;
        iVar13 = iVar1 * 0x10000 + 0x100;
      }
    }
    else {
      local_30 = 0;
      local_2c = 0;
      local_44 = 0;
      local_48 = 0;
      if (iVar10 != 0) {
        local_44 = iVar16 / iVar10;
        local_48 = (iVar3 * 0x10000) / iVar4;
        local_14 = iVar1 * 0x10000 + 0x8000;
        iVar5 = *piVar6 * 0x10000 + 0x8000;
        local_18 = piVar6[1] * 0x10000 + 0x8000;
        local_2c = ((*piVar6 - *piVar8) * 0x10000) / iVar10;
        local_30 = ((piVar6[1] - piVar8[1]) * 0x10000) / iVar10;
      }
    }
    local_28 = iVar17 * 4;
    for (; (iVar17 < local_1c && (iVar17 < dword_d30b8)); iVar17 = iVar17 + 1) {
      iVar4 = local_14 >> 0x10;
      iVar3 = ((iVar13 >> 0x10) - iVar4) + 1;
      iVar10 = (iVar4 + iVar3) - _dword_d30b4;
      if (0 < iVar10) {
        iVar3 = iVar3 - iVar10;
      }
      iVar10 = dword_d30ac - iVar4;
      if (iVar10 < 1) {
        iVar10 = 0;
      }
      else {
        iVar3 = iVar3 - iVar10;
        iVar4 = iVar4 + iVar10;
        if (0x600 < iVar10) {
          return;
        }
      }
      if ((0 < iVar3) && (dword_d30b0 <= iVar17)) {
        texture_span(iVar4 + *(int *)(off_d30cc + local_28),
                  (iVar5 >> 0x10) + iVar11 * (local_18 >> 0x10) + (&unk_f6138)[iVar10],iVar3);
      }
      iVar5 = iVar5 + local_2c;
      local_18 = local_18 + local_30;
      local_14 = local_14 + local_44;
      iVar13 = iVar13 + local_48;
      local_28 = local_28 + 4;
    }
  }
  return;
}


// ================================================================================================
// find_file_ext @ 0xa2610 [__watcall]
// ================================================================================================

char * __watcall find_file_ext(void)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  char *__src;
  char *pcVar4;
  char *in_stack_00000004;
  char *in_stack_00000008;
  char *in_stack_0000000c;
  
  pcVar4 = in_stack_00000008;
  do {
    cVar1 = *in_stack_00000004;
    *pcVar4 = cVar1;
    if (cVar1 == '\0') break;
    cVar1 = in_stack_00000004[1];
    in_stack_00000004 = in_stack_00000004 + 2;
    pcVar4[1] = cVar1;
    pcVar4 = pcVar4 + 2;
  } while (cVar1 != '\0');
  pcVar4 = (char *)strrchr(in_stack_00000008,0x2e);
  if (pcVar4 == (char *)0x0) {
    uVar3 = 0xffffffff;
    pcVar4 = in_stack_00000008;
    do {
      if (uVar3 == 0) break;
      uVar3 = uVar3 - 1;
      cVar1 = *pcVar4;
      pcVar4 = pcVar4 + 1;
    } while (cVar1 != '\0');
    pcVar4 = in_stack_00000008 + (~uVar3 - 1);
    pcVar4[4] = '\0';
    cVar1 = *in_stack_0000000c;
    __src = in_stack_0000000c;
    while (cVar1 != '\0') {
      strncpy(pcVar4,__src,4);
      __src = __src + 4;
      cVar1 = *__src;
    }
    cVar1 = *in_stack_0000000c;
    while (cVar1 != '\0') {
      strncpy(pcVar4,in_stack_0000000c,4);
      iVar2 = file_exists(in_stack_00000008);
      if (iVar2 != 0) {
        return pcVar4;
      }
      in_stack_0000000c = in_stack_0000000c + 4;
      cVar1 = *in_stack_0000000c;
    }
    *pcVar4 = '\0';
  }
  return pcVar4;
}


// ================================================================================================
// packed_read @ 0xa26b0 [__cdecl]
// ================================================================================================

undefined4 packed_read(undefined4 param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined local_10c [256];
  
  uVar2 = 0;
  seekhandle(param_1,param_2);
  iVar1 = param_3 + -8;
  if (0xff < iVar1) {
    iVar1 = 0x100;
  }
  if (iVar1 < 9) {
    param_3 = 8;
  }
  else {
    param_3 = param_3 + -8;
    if (0xff < param_3) {
      param_3 = 0x100;
    }
  }
  iVar1 = dos_read_blocks(param_1,local_10c,param_3);
  if (iVar1 != 0) {
    uVar2 = unpacked_size();
  }
  seekhandle(param_1,param_2);
  return uVar2;
}


// ================================================================================================
// loadfile_packed_data_fatal @ 0xa2744 [__watcall]
// ================================================================================================

void __watcall loadfile_packed_data_fatal(void)

{
  undefined4 in_stack_00000004;
  undefined4 in_stack_00000008;
  
  loadfile_packed_data(in_stack_00000004,in_stack_00000008,1);
  return;
}


// ================================================================================================
// loadfile_packed_data_try @ 0xa275c [__watcall]
// ================================================================================================

void __watcall loadfile_packed_data_try(void)

{
  undefined4 in_stack_00000004;
  undefined4 in_stack_00000008;
  
  loadfile_packed_data(in_stack_00000004,in_stack_00000008,0);
  return;
}


// ================================================================================================
// loadfile_packed_data @ 0xa2774 [__cdecl]
// ================================================================================================

undefined4 * loadfile_packed_data(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)loadfile_packed(param_1,param_2,param_3);
  if (puVar1 != (undefined4 *)0x0) {
    puVar1 = (undefined4 *)*puVar1;
  }
  return puVar1;
}


// ================================================================================================
// loadfile_packed_fatal @ 0xa2794 [__watcall]
// ================================================================================================

void __watcall loadfile_packed_fatal(void)

{
  undefined4 in_stack_00000004;
  undefined4 in_stack_00000008;
  
  loadfile_packed(in_stack_00000004,in_stack_00000008,1);
  return;
}


// ================================================================================================
// loadfile_packed_try @ 0xa27ac [__watcall]
// ================================================================================================

void __watcall loadfile_packed_try(void)

{
  undefined4 in_stack_00000004;
  undefined4 in_stack_00000008;
  
  loadfile_packed(in_stack_00000004,in_stack_00000008,0);
  return;
}


// ================================================================================================
// loadfile_packed @ 0xa27c4 [__cdecl]
// ================================================================================================

undefined4 * loadfile_packed(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 local_1c;
  undefined4 local_18;
  int local_14;
  int local_10;
  
  puVar1 = (undefined4 *)find_loaded_file(param_1);
  if (puVar1 == (undefined4 *)0x0) {
    openhandle(param_1,&local_1c,&local_18,&local_14,param_3);
    if (local_14 == 0) {
      puVar1 = (undefined4 *)0x0;
    }
    else {
      local_10 = packed_read(local_1c,local_18,local_14,param_3);
      if (local_10 == 0) {
        closehandle(local_1c);
        return (undefined4 *)0x0;
      }
      iVar3 = local_10;
      if (local_10 <= local_14) {
        iVar3 = local_14;
      }
      uVar2 = iVar3 + 0x3ebU & 0xfffffffc;
      puVar1 = (undefined4 *)reservemem_locked(param_1,uVar2,param_2,param_3);
      if (puVar1 == (undefined4 *)0x0) {
        closehandle(local_1c);
        return (undefined4 *)0x0;
      }
      iVar3 = identity_8e3cc(*puVar1);
      uVar4 = identity_8e3d4((iVar3 + uVar2) - local_14 & 0xfffffffc);
      dos_read_blocks(local_1c,uVar4,local_14 + 3U & 0xfffffffc);
      unpack(uVar4,*puVar1,local_14,param_3);
      resizemem(puVar1,local_10,param_3);
      closehandle(local_1c);
    }
  }
  return puVar1;
}


// ================================================================================================
// shpi_from_compressed @ 0xa28f0 [__cdecl]
// ================================================================================================

int shpi_from_compressed(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  undefined *puVar6;
  undefined4 uVar7;
  undefined local_38;
  undefined local_37;
  undefined local_36;
  undefined local_35;
  undefined local_34;
  undefined local_33;
  undefined local_32;
  undefined local_31;
  undefined local_30;
  undefined local_2f;
  undefined local_2e;
  undefined local_2d;
  undefined local_2c;
  undefined local_2b;
  undefined local_2a;
  undefined local_29;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  
  iVar2 = read_le_n();
  iVar3 = read_le_n();
  local_14 = iVar2 + 10;
  if (param_2 != 0) {
    local_28 = iVar3;
    memmove_dwords(&aSHPI_d544c,param_2,0x10);
    write_le_n(param_2 + 4,local_14,4);
    write_le_n(param_2 + 8,iVar3,4);
    iVar1 = iVar3 * 8;
    iVar5 = param_2 + 0x10;
    local_10 = param_1 + 6;
    memmove_dwords(local_10 + iVar1,iVar1 + iVar5,iVar2 + -6 + iVar3 * -8);
    local_1c = 0;
    if (0 < iVar3) {
      iVar2 = param_2 + 0x14;
      local_18 = local_10;
      local_20 = iVar3 * 4 + local_10;
      local_24 = iVar1;
      do {
        iVar3 = read_le_n();
        iVar3 = local_24 + iVar3 + 0x10;
        uVar7 = 4;
        uVar4 = read_le_n();
        write_le_n(iVar5,uVar4,uVar7);
        write_le_n(iVar2,iVar3,4);
        puVar6 = (undefined *)(iVar3 + param_2);
        memmove_dwords(puVar6,&local_38,0x10);
        *puVar6 = local_2c;
        puVar6[1] = local_2b;
        puVar6[2] = local_2a;
        puVar6[3] = local_29;
        puVar6[4] = local_38;
        puVar6[5] = local_37;
        puVar6[6] = local_36;
        puVar6[7] = local_35;
        puVar6[8] = local_34;
        puVar6[9] = local_33;
        puVar6[10] = local_32;
        puVar6[0xb] = local_31;
        puVar6[0xc] = local_30;
        puVar6[0xd] = local_2f;
        puVar6[0xe] = local_2e;
        puVar6[0xf] = local_2d;
        iVar2 = iVar2 + 8;
        iVar5 = iVar5 + 8;
        local_18 = local_18 + 4;
        local_20 = local_20 + 4;
        local_1c = local_1c + 1;
      } while (local_1c < local_28);
    }
  }
  return local_14;
}


// ================================================================================================
// packed_size @ 0xa2ab8 [__cdecl]
// ================================================================================================

void packed_size(undefined4 param_1)

{
  shpi_from_compressed(param_1,0);
  return;
}


// ================================================================================================
// abs @ 0xa2ac8 [__watcall]
// ================================================================================================

int __watcall abs(int param_1)

{
  if (param_1 < 0) {
    param_1 = -param_1;
  }
  return param_1;
}


// ================================================================================================
// __init_amblksiz @ 0xa2acf [__watcall]
// ================================================================================================

void __watcall __init_amblksiz(void)

{
  dword_d5674 = 0x8000;
  return;
}


// ================================================================================================
// __float_not_loaded @ 0xa2adc [__watcall]
// ================================================================================================

void __watcall
__float_not_loaded(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  __fatal_runtime_error(aFloatingPointSupportNotL,1,unaff_EBX,unaff_ECX,unaff_EDX);
  return;
}


// ================================================================================================
// ultoa @ 0xa2b13 [__watcall]
// ================================================================================================

char * __watcall ultoa(uint param_1,char *unaff_EDX,uint unaff_EBX)

{
  char cVar1;
  uint uVar2;
  char *pcVar3;
  char *pcVar4;
  char local_33 [35];
  
  pcVar3 = local_33;
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
// ltoa @ 0xa2b5c [__watcall]
// ================================================================================================

undefined * __watcall ltoa(int param_1,undefined *unaff_EDX,int unaff_EBX)

{
  if ((unaff_EBX == 10) && (param_1 < 0)) {
    param_1 = -param_1;
    *unaff_EDX = 0x2d;
  }
  ultoa(param_1);
  return unaff_EDX;
}


// ================================================================================================
// toupper @ 0xa2b77 [__watcall]
// ================================================================================================

int __watcall toupper(int param_1)

{
  if ((0x60 < param_1) && (param_1 < 0x7b)) {
    param_1 = param_1 + -0x20;
  }
  return param_1;
}


// ================================================================================================
// _heapenable @ 0xa2b85 [__watcall]
// ================================================================================================

undefined8 __watcall _heapenable(undefined4 param_1,undefined4 unaff_EDX)

{
  undefined4 uVar1;
  
  uVar1 = dword_d5670;
  dword_d5670 = param_1;
  return CONCAT44(unaff_EDX,uVar1);
}


// ================================================================================================
// sbrk @ 0xa2b95 [__watcall]
// ================================================================================================

undefined8 __watcall sbrk(int param_1)

{
  code *pcVar1;
  undefined3 uVar2;
  uint uVar3;
  undefined2 *puVar4;
  undefined4 *puVar5;
  undefined2 extraout_CX;
  undefined4 extraout_EDX;
  undefined4 uVar6;
  undefined *puVar7;
  undefined *puVar8;
  undefined2 unaff_SI;
  undefined2 unaff_DI;
  ushort in_DS;
  byte bVar9;
  undefined8 uVar10;
  
  puVar7 = &stack0xffffffec;
  puVar8 = &stack0xffffffec;
  if (((byte_d4d06 == 1) && (byte_d4d07 == '\0')) || (byte_d4d06 == 9)) {
    if (param_1 < 1) {
      puVar5 = (undefined4 *)__get_errno_ptr();
      *puVar5 = 9;
    }
    else {
      param_1 = param_1 + 0xfff;
      bVar9 = byte_d4d06 == 0;
      if (byte_d4d06 == 1) {
        uVar3 = param_1 >> 0x10;
        bVar9 = (param_1 >> 0xf & 1U) != 0;
        pcVar1 = (code *)swi(0x31);
        (*pcVar1)();
        puVar4 = (undefined2 *)(1 - bVar9);
        uVar6 = extraout_EDX;
        if (puVar4 != (undefined2 *)0x0) {
          puVar4 = (undefined2 *)CONCAT22((short)((uint)param_1 >> 0x10),extraout_CX);
          *puVar4 = unaff_DI;
          puVar4[1] = unaff_SI;
        }
      }
      else {
        pcVar1 = (code *)swi(0x21);
        uVar10 = (*pcVar1)();
        uVar6 = (undefined4)((ulonglong)uVar10 >> 0x20);
        uVar3 = ~-(uint)bVar9;
        puVar4 = (undefined2 *)((uint)uVar10 & uVar3);
      }
      puVar8 = &stack0xfffffff0;
      if (puVar4 != (undefined2 *)0x0) goto LAB_000a2c4e;
      puVar5 = (undefined4 *)__get_errno_ptr(0,uVar6,uVar3);
      *puVar5 = 5;
      puVar7 = &stack0xfffffff0;
    }
    puVar4 = (undefined2 *)0xffffffff;
    puVar8 = puVar7;
  }
  else {
    if ((1 < byte_d4d06) && (byte_d4d06 < 9)) {
      uVar2 = SegmentLimit((uint)in_DS);
      dword_d4cd8 = (ushort)uVar2 + 1;
    }
    puVar4 = (undefined2 *)__brk(dword_d4cd8 + param_1);
  }
LAB_000a2c4e:
  return CONCAT44(*(undefined4 *)(puVar8 + 8),puVar4);
}


// ================================================================================================
// __brk @ 0xa2c54 [__watcall]
// ================================================================================================

undefined8 __watcall __brk(uint param_1)

{
  code *pcVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  undefined *puVar5;
  uint *puVar6;
  uint *puVar7;
  undefined *puVar8;
  byte bVar9;
  uint local_20;
  undefined auStack_18 [4];
  
  puVar5 = &stack0xffffffe4;
  puVar7 = &local_20;
  local_20 = param_1;
  if (dword_d4cec <= param_1) {
    if (byte_d4d06 == '\0') {
      pcVar1 = (code *)swi(0x21);
      uVar2 = (*pcVar1)();
      bVar9 = 0;
      if ((uVar2 & 1) != 0) {
        pcVar1 = (code *)swi(0x21);
        (*pcVar1)();
        puVar5 = auStack_18;
        puVar7 = (uint *)auStack_18;
        if ((bVar9 & 1) != 0) goto LAB_000a2cbb;
      }
      bVar9 = false;
      puVar6 = (uint *)puVar5;
    }
    else {
      bVar9 = byte_d4d06 == '\0';
      puVar6 = &local_20;
      if ((byte_d4d06 == '\x01') && (bVar9 = 1 < byte_d4d07, puVar6 = &local_20, byte_d4d07 == 1)) {
        bVar9 = false;
        puVar6 = &local_20;
      }
    }
    pcVar1 = (code *)swi(0x21);
    (*pcVar1)();
    puVar7 = (uint *)((int)puVar6 + 4);
    puVar8 = (undefined *)((int)puVar6 + 4);
    if ((bVar9 & 1) == 0) {
      uVar4 = dword_d4cd8;
      dword_d4cd8 = *(undefined4 *)((int)puVar6 + 4);
      goto LAB_000a2c4e;
    }
  }
LAB_000a2cbb:
  *(undefined4 *)((int)puVar7 + -4) = 0xa2cc0;
  puVar3 = (undefined4 *)__get_errno_ptr();
  *puVar3 = 5;
  uVar4 = 0xffffffff;
  puVar8 = (undefined *)puVar7;
LAB_000a2c4e:
  return CONCAT44(*(undefined4 *)(puVar8 + 0x14),uVar4);
}


// ================================================================================================
// tell @ 0xa2d16 [__watcall]
// ================================================================================================

void __watcall tell(int param_1)

{
  lseek(param_1,0,1);
  return;
}


// ================================================================================================
// __InitFiles @ 0xa2d27 [__watcall]
// ================================================================================================

void __watcall
__InitFiles(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  undefined4 *puVar1;
  undefined *puVar2;
  
  byte_d4d59 = byte_d4d59 & 0xf8 | 4;
  for (puVar2 = &unk_d4d18; *(int *)(puVar2 + 0xc) != 0; puVar2 = puVar2 + 0x1a) {
    puVar1 = (undefined4 *)malloc(8);
    if (puVar1 == (undefined4 *)0x0) {
      puVar1 = (undefined4 *)malloc(8);
      if (puVar1 == (undefined4 *)0x0) {
        __fatal_runtime_error(aNotEnoughMemoryToAllocat,1,0,puVar2,unaff_EDX,unaff_ECX,unaff_EBX);
      }
    }
    puVar1[1] = puVar2;
    *puVar1 = dword_f24c8;
    dword_f24c8 = puVar1;
  }
  dword_edf00 = *(int *)(puVar2 + 0xc);
  return;
}


// ================================================================================================
// __full_io_exit @ 0xa2d9f [__watcall]
// ================================================================================================

void __watcall __full_io_exit(void)

{
  __closeall_streams(0);
  __purgefp();
  return;
}


// ================================================================================================
// __closeall_streams @ 0xa2db0 [__watcall]
// ================================================================================================

undefined8 __watcall __closeall_streams(int param_1,undefined4 unaff_EDX)

{
  undefined4 *puVar1;
  undefined *puVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  int iVar5;
  
  iVar5 = 0;
  puVar3 = dword_f24c8;
LAB_000a2df7:
  if (puVar3 == (undefined4 *)0x0) {
    return CONCAT44(unaff_EDX,iVar5);
  }
  puVar1 = (undefined4 *)*puVar3;
  puVar2 = (undefined *)puVar3[1];
  uVar4 = 1;
  puVar3 = puVar1;
  if ((puVar2[0xd] & 0x40) == 0) goto code_r0x000a2de2;
  goto LAB_000a2def;
code_r0x000a2de2:
  if (&unk_d4d18 + param_1 * 0x1a <= puVar2) {
    if (puVar2 < &unk_d4d9a) {
      uVar4 = 0;
    }
LAB_000a2def:
    __shutdown_stream(puVar2,uVar4);
    iVar5 = iVar5 + 1;
  }
  goto LAB_000a2df7;
}


// ================================================================================================
// __qwrite @ 0xa2e02 [__watcall]
// ================================================================================================

uint __watcall __qwrite(undefined4 param_1,undefined4 param_2,uint unaff_EBX)

{
  code *pcVar1;
  bool bVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint extraout_EDX;
  undefined4 *puVar6;
  undefined4 *puVar7;
  byte bVar8;
  undefined6 uVar9;
  
  puVar7 = (undefined4 *)&stack0xffffffec;
  uVar3 = __GetIOMode();
  if ((uVar3 & 0x80) != 0) {
    bVar8 = 0;
    pcVar1 = (code *)swi(0x21);
    uVar9 = (*pcVar1)();
    uVar3 = (uint)uVar9;
    puVar7 = (undefined4 *)&stack0xfffffff0;
    puVar6 = (undefined4 *)&stack0xfffffff0;
    bVar2 = (bVar8 & 1) != 0;
    uVar5 = CONCAT22((ushort)((short)((uint6)uVar9 >> 0x20) << 1 | (ushort)bVar8) >> 1 |
                     (ushort)bVar2 << 0xf,(short)uVar9);
    if (bVar2) goto LAB_000a2e3f;
  }
  bVar8 = 0;
  pcVar1 = (code *)swi(0x21);
  iVar4 = (*pcVar1)();
  puVar6 = puVar7 + 1;
  bVar2 = (bVar8 & 1) != 0;
  uVar3 = (iVar4 << 1 | (uint)bVar8) >> 1;
  uVar5 = uVar3 | (uint)bVar2 << 0x1f;
  if (!bVar2) {
    if (uVar5 == unaff_EBX) {
      return uVar5;
    }
    *puVar7 = 0xa2e74;
    __set_errno(0xc,uVar5,param_1);
    return extraout_EDX;
  }
LAB_000a2e3f:
  *(undefined4 *)((int)puVar6 + -4) = 0xa2e44;
  uVar3 = __set_errno_dos(uVar3 & 0xffff,uVar5,param_1);
  return uVar3;
}


// ================================================================================================
// __flushall @ 0xa2e85 [__watcall]
// ================================================================================================

undefined8 __watcall __flushall(uint param_1,undefined4 unaff_EDX)

{
  undefined4 *extraout_EDX;
  undefined4 *puVar1;
  int iVar2;
  
  iVar2 = 0;
  for (puVar1 = dword_f24c8; puVar1 != (undefined4 *)0x0; puVar1 = (undefined4 *)*puVar1) {
    if (((*(uint *)(puVar1[1] + 0xc) & param_1) != 0) &&
       (iVar2 = iVar2 + 1, (*(byte *)(puVar1[1] + 0xd) & 0x10) != 0)) {
      __flush();
      puVar1 = extraout_EDX;
    }
  }
  return CONCAT44(unaff_EDX,iVar2);
}


// ================================================================================================
// __getche_raw @ 0xa2eb4 [__watcall]
// ================================================================================================

undefined8 __watcall __getche_raw(void)

{
  code *pcVar1;
  uint uVar2;
  undefined4 *puVar3;
  
  uVar2 = dword_d4cf8;
  dword_d4cf8 = 0;
  puVar3 = (undefined4 *)&stack0xfffffffc;
  if (uVar2 == 0) {
    pcVar1 = (code *)swi(0x21);
    uVar2 = (*pcVar1)();
    uVar2 = uVar2 & 0xff;
    puVar3 = (undefined4 *)register0x00000010;
  }
  return CONCAT44(*puVar3,uVar2);
}


// ================================================================================================
// __qread @ 0xa2ed1 [__watcall]
// ================================================================================================

void __watcall __qread(undefined4 param_1)

{
  code *pcVar1;
  uint uVar2;
  bool bVar3;
  int iVar4;
  byte in_CF;
  
  pcVar1 = (code *)swi(0x21);
  iVar4 = (*pcVar1)();
  bVar3 = (in_CF & 1) != 0;
  uVar2 = (iVar4 << 1 | (uint)in_CF) >> 1;
  if (bVar3) {
    __set_errno_dos(uVar2 & 0xffff,uVar2 | (uint)bVar3 << 0x1f,param_1);
  }
  return;
}


// ================================================================================================
// __FDFS @ 0xa2ef0 [__watcall]
// ================================================================================================

uint __watcall __FDFS(uint param_1,uint unaff_EDX)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  if ((unaff_EDX & 0x7ff00000) != 0) {
    uVar1 = (uint)(CARRY4(unaff_EDX,unaff_EDX) ||
                  CARRY4(unaff_EDX * 2,(uint)CARRY4(param_1,param_1))) << 0x1f;
    uVar2 = param_1 * 2 + 0x20000000;
    uVar3 = unaff_EDX * 2 + (uint)CARRY4(param_1,param_1) + (uint)(0xdfffffff < param_1 * 2);
    if ((uVar3 == 0) || (0x8fdfffff < uVar3)) {
      return uVar1 | 0x7f800000;
    }
    if (0x701fffff < uVar3) {
      return ((uVar3 + 0x90000000) * 2 + (uint)CARRY4(uVar2,uVar2)) * 2 +
             (uint)CARRY4(uVar2 * 2,uVar2 * 2) | uVar1;
    }
  }
  return 0;
}


// ================================================================================================
// drawshape_alt @ 0xa2f40 [__cdecl]
// ================================================================================================

void drawshape_alt(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  if (dword_d30c8 == 0) {
    drawshape_alt_linear(param_1,param_2,param_3);
    return;
  }
  funcptr_d43e4 = putpixels_skip_ff;
  drawshape(param_1,param_2,param_3);
  funcptr_d43e4 = memmove_dwords;
  return;
}


// ================================================================================================
// drawshape_alt_home @ 0xa2f84 [__cdecl]
// ================================================================================================

void drawshape_alt_home(int param_1)

{
  drawshape_alt(param_1,*(int *)(param_1 + 10) >> 0x10,*(int *)(param_1 + 0xc) >> 0x10);
  return;
}


// ================================================================================================
// drawshape_alt_centered @ 0xa2fa0 [__cdecl]
// ================================================================================================

void drawshape_alt_centered(int param_1,int param_2,int param_3)

{
  drawshape_alt(param_1,param_2 - (*(int *)(param_1 + 6) >> 0x10),
            param_3 - (*(int *)(param_1 + 8) >> 0x10));
  return;
}


// ================================================================================================
// shape_flip_h @ 0xa2fd0 [__cdecl]
// ================================================================================================

void shape_flip_h(int param_1)

{
  undefined uVar1;
  int iVar2;
  int iVar3;
  undefined *puVar4;
  undefined *puVar5;
  int iVar6;
  undefined *puVar7;
  int iVar8;
  
  iVar2 = *(int *)(param_1 + 2);
  iVar3 = *(int *)(param_1 + 4) >> 0x10;
  iVar8 = 0;
  if (0 < iVar3) {
    puVar4 = (undefined *)(param_1 + 0x10);
    do {
      puVar7 = puVar4 + (iVar2 >> 0x10);
      iVar6 = 0;
      puVar5 = puVar7;
      if (0 < iVar2 >> 0x11) {
        do {
          puVar5 = puVar5 + -1;
          uVar1 = *puVar4;
          *puVar4 = *puVar5;
          *puVar5 = uVar1;
          puVar4 = puVar4 + 1;
          iVar6 = iVar6 + 1;
        } while (iVar6 < iVar2 >> 0x11);
      }
      iVar8 = iVar8 + 1;
      puVar4 = puVar7;
    } while (iVar8 < iVar3);
  }
  *(short *)(param_1 + 8) = (short)((uint)iVar2 >> 0x10) - *(short *)(param_1 + 8);
  return;
}


// ================================================================================================
// shape_flip_v @ 0xa3050 [__cdecl]
// ================================================================================================

void shape_flip_v(int param_1)

{
  undefined uVar1;
  int iVar2;
  undefined *puVar3;
  undefined *puVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  iVar6 = *(int *)(param_1 + 2) >> 0x10;
  iVar2 = *(int *)(param_1 + 4);
  puVar4 = (undefined *)(param_1 + 0x10);
  puVar3 = puVar4 + ((iVar2 >> 0x10) + -1) * iVar6;
  iVar7 = 0;
  if (0 < iVar2 >> 0x11) {
    do {
      iVar5 = 0;
      if (0 < iVar6) {
        do {
          uVar1 = *puVar4;
          *puVar4 = *puVar3;
          *puVar3 = uVar1;
          puVar4 = puVar4 + 1;
          puVar3 = puVar3 + 1;
          iVar5 = iVar5 + 1;
        } while (iVar5 < iVar6);
      }
      puVar3 = puVar3 + iVar6 * -2;
      iVar7 = iVar7 + 1;
    } while (iVar7 < iVar2 >> 0x11);
  }
  *(short *)(param_1 + 10) = (short)((uint)iVar2 >> 0x10) - *(short *)(param_1 + 10);
  return;
}


// ================================================================================================
// shape_recolor @ 0xa30d0 [__cdecl]
// ================================================================================================

void shape_recolor(int param_1)

{
  translate_bytes(param_1 + 0x10,&unk_d42e4,
            (*(int *)(param_1 + 4) >> 0x10) * (*(int *)(param_1 + 2) >> 0x10));
  return;
}


// ================================================================================================
// shapes_recolor_all @ 0xa30f8 [__watcall]
// ================================================================================================

void __watcall shapes_recolor_all(void)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  undefined4 in_stack_00000004;
  char local_10 [8];
  
  iVar3 = 0;
  while( true ) {
    iVar2 = shapecount(in_stack_00000004);
    if (iVar2 <= iVar3) break;
    shape_offset(in_stack_00000004,iVar3,local_10);
    if (local_10[0] != '!') {
      uVar1 = getshape(in_stack_00000004,iVar3);
      shape_recolor(uVar1);
    }
    iVar3 = iVar3 + 1;
  }
  return;
}


// ================================================================================================
// _EFG_Format @ 0xa313f [__watcall]
// ================================================================================================

undefined8 __watcall _EFG_Format(char *param_1,int *unaff_EDX,int unaff_EBX)

{
  undefined4 *puVar1;
  byte bVar2;
  undefined4 uVar3;
  undefined2 in_DS;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  *(undefined4 *)(unaff_EBX + 0xc) = 0;
  local_14 = CONCAT22(local_14._2_2_,in_DS);
  bVar2 = *(byte *)(unaff_EBX + 0x15);
  uVar3 = 0;
  if (bVar2 < 0x47) {
    if (bVar2 < 0x45) goto LAB_000a3210;
    if (bVar2 < 0x46) goto LAB_000a3199;
  }
  else {
    if (bVar2 < 0x48) {
LAB_000a3189:
      if (*(int *)(unaff_EBX + 8) == 0) {
        *(undefined4 *)(unaff_EBX + 8) = 1;
      }
      bVar2 = bVar2 - 2;
    }
    else {
      if (0x65 < bVar2) {
        if (bVar2 < 0x67) goto LAB_000a319e;
        if (bVar2 != 0x67) goto LAB_000a3210;
        goto LAB_000a3189;
      }
      if (bVar2 != 0x65) goto LAB_000a3210;
    }
LAB_000a3199:
    uVar3 = 1;
  }
LAB_000a319e:
  puVar1 = (undefined4 *)*unaff_EDX;
  *unaff_EDX = (int)(puVar1 + 2);
  local_1c = *puVar1;
  local_18 = puVar1[1];
  if (*(int *)(unaff_EBX + 8) == -1) {
    *(undefined4 *)(unaff_EBX + 8) = 6;
  }
  __cvt_float(param_1,&local_1c,*(undefined4 *)(unaff_EBX + 8),0,0x27,uVar3,3,bVar2,
            *(byte *)(unaff_EBX + 0x15) & 0x5f);
  if (*param_1 == '*') {
    *(undefined *)(unaff_EBX + 0x16) = 0x2a;
  }
  param_1[0x27] = '\0';
  for (; *param_1 == ' '; param_1 = param_1 + 1) {
  }
  __cvt_EFG_trim(param_1,unaff_EBX);
  local_14 = CONCAT22(local_14._2_2_,in_DS);
  *(undefined4 *)(unaff_EBX + 8) = 0xffffffff;
LAB_000a3210:
  return CONCAT44(local_14,param_1);
}


// ================================================================================================
// __cvt_EFG_trim @ 0xa321c [__watcall]
// ================================================================================================

void __watcall __cvt_EFG_trim(char *param_1,int unaff_EDX)

{
  char cVar1;
  char *pcVar2;
  
  if ((*(byte *)(unaff_EDX + 0x14) & 1) == 0) {
    for (; ((cVar1 = *param_1, cVar1 != '\0' && (cVar1 != 'e')) && (cVar1 != 'E'));
        param_1 = param_1 + 1) {
    }
    pcVar2 = param_1 + -1;
    if ((*(char *)(unaff_EDX + 0x15) == 'G') || (*(char *)(unaff_EDX + 0x15) == 'g')) {
      for (; *pcVar2 == '0'; pcVar2 = pcVar2 + -1) {
      }
    }
    if (*pcVar2 != '.') {
      pcVar2 = pcVar2 + 1;
    }
    do {
      cVar1 = *param_1;
      param_1 = param_1 + 1;
      *pcVar2 = cVar1;
      pcVar2 = pcVar2 + 1;
    } while (cVar1 != '\0');
  }
  return;
}


// ================================================================================================
// __cnvs2d @ 0xa3264 [__watcall]
// ================================================================================================

void __watcall
__cnvs2d(undefined4 param_1,double *unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  longdouble lVar1;
  
  lVar1 = (longdouble)__strtod(param_1,0,unaff_EDX,unaff_ECX,unaff_EBX);
  *unaff_EDX = (double)lVar1;
  return;
}


// ================================================================================================
// unk_a32d0 @ 0xa32d0
// ================================================================================================

byte * unk_a32d0(void)

{
  int *in_EAX;
  int *piVar1;
  byte *pbVar2;
  
  *in_EAX = (int)(*in_EAX + (int)in_EAX);
  *(char *)in_EAX = *(char *)in_EAX + (char)in_EAX;
  piVar1 = (int *)CONCAT31((int3)((uint)in_EAX >> 8),(char)in_EAX + *(char *)in_EAX);
  pbVar2 = (byte *)((int)piVar1 + *piVar1);
  *(int *)((int)pbVar2 * 2) = *(int *)((int)pbVar2 * 2) + 1;
  *pbVar2 = *pbVar2 + (byte)pbVar2;
  *pbVar2 = *pbVar2 | (byte)pbVar2;
  return pbVar2;
}


// ================================================================================================
// unk_a32d4 @ 0xa32d4
// ================================================================================================

byte * unk_a32d4(void)

{
  char *in_EAX;
  int *piVar1;
  byte *pbVar2;
  
  piVar1 = (int *)CONCAT31((int3)((uint)in_EAX >> 8),(char)in_EAX + *in_EAX);
  pbVar2 = (byte *)((int)piVar1 + *piVar1);
  *(int *)((int)pbVar2 * 2) = *(int *)((int)pbVar2 * 2) + 1;
  *pbVar2 = *pbVar2 + (byte)pbVar2;
  *pbVar2 = *pbVar2 | (byte)pbVar2;
  return pbVar2;
}


// ================================================================================================
// unk_a32d6 @ 0xa32d6
// ================================================================================================

byte * unk_a32d6(void)

{
  int *in_EAX;
  byte *pbVar1;
  
  pbVar1 = (byte *)((int)in_EAX + *in_EAX);
  *(int *)((int)pbVar1 * 2) = *(int *)((int)pbVar1 * 2) + 1;
  *pbVar1 = *pbVar1 + (byte)pbVar1;
  *pbVar1 = *pbVar1 | (byte)pbVar1;
  return pbVar1;
}


// ================================================================================================
// __int7_pl3 @ 0xa35ec [__watcall]
// ================================================================================================

undefined8 __watcall __int7_pl3(undefined4 param_1,undefined4 unaff_EDX)

{
  emu387_decode();
  return CONCAT44(unaff_EDX,param_1);
}


// ================================================================================================
// __int7_X32VM @ 0xa360d [__cdecl]
// ================================================================================================

undefined8 __int7_X32VM(undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 in_EDX;
  
  uVar1 = param_3[4];
  uVar2 = *param_3;
  emu387_decode();
  LOCK();
  UNLOCK();
  *param_3 = uVar2;
  param_3[4] = uVar1;
  return CONCAT44(in_EDX,*param_3);
}


// ================================================================================================
// __int7 @ 0xa365c [__watcall]
// ================================================================================================

undefined8 __watcall __int7(undefined4 param_1,undefined4 unaff_EDX)

{
  emu387_decode();
  return CONCAT44(unaff_EDX,param_1);
}


// ================================================================================================
// emu387_decode @ 0xa3680 [__watcall]
// ================================================================================================

void __watcall emu387_decode(void)

{
  byte bVar1;
  undefined2 uVar2;
  uint uVar3;
  byte *param_14;
  
  bVar1 = *param_14;
  while ((bVar1 < 0x9c &&
         ((((((bVar1 == 0x9b || (bVar1 == 0x26)) || (bVar1 == 0x2e)) ||
            ((bVar1 == 0x36 || (bVar1 == 0x3e)))) ||
           ((bVar1 == 100 || ((bVar1 == 0x65 || (bVar1 == 0x66)))))) || (bVar1 == 0x67))))) {
    param_14 = param_14 + 1;
    bVar1 = *param_14;
  }
  if ((bVar1 & 0xf8) != 0xd8) {
    return;
  }
  bVar1 = param_14[1];
  if (0xbf < bVar1) {
    uVar2 = empty_func_902a0();
                    /* WARNING: Could not recover jumptable at 0x000a37ab. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*(code *)(&PTR_sub_a41e6_000a34ec)[(byte)((byte)((ushort)uVar2 >> 8) & 0x38 | (byte)uVar2)])();
    return;
  }
  uVar3 = CONCAT11(bVar1 >> 3,bVar1) & 0x1807;
  uVar2 = (*(code *)(&PTR_sub_a38de_000a332c)[(byte)((byte)uVar3 | (byte)(uVar3 >> 8))])();
  empty_func_902a0();
                    /* WARNING: Could not recover jumptable at 0x000a36fe. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)(&PTR_sub_a39dd_000a33ec)[(byte)((byte)((ushort)uVar2 >> 8) & 0x38 | (byte)uVar2)])();
  return;
}


// ================================================================================================
// emu387_pop_set_cc @ 0xa3822 [__watcall]
// ================================================================================================

void __watcall emu387_pop_set_cc(int param_1)

{
  ushort uVar1;
  int unaff_EBP;
  int unaff_EDI;
  
  uVar1 = *(ushort *)(unaff_EBP + 4) & 0xb8ff;
  *(ushort *)(unaff_EBP + 4) = CONCAT11((byte)(uVar1 >> 8) | (&DAT_000a331f)[param_1],(char)uVar1);
  *(ushort *)(unaff_EBP + 8) = *(ushort *)(unaff_EBP + 8) & *(ushort *)(&unk_a32ce + unaff_EDI);
  *(ushort *)(unaff_EBP + 8) = *(ushort *)(unaff_EBP + 8) | *(ushort *)(unk_a32d6 + unaff_EDI);
  uVar1 = *(ushort *)(&unk_a3282 + *(ushort *)(&unk_a327e + unaff_EDI));
  *(ushort *)(unaff_EBP + 4) = *(ushort *)(unaff_EBP + 4) & 0xc7ff;
  *(ushort *)(unaff_EBP + 4) = *(ushort *)(unaff_EBP + 4) | uVar1;
  emu387_decode();
  return;
}


// ================================================================================================
// emu387_set_cc @ 0xa3874 [__watcall]
// ================================================================================================

void __watcall emu387_set_cc(int param_1)

{
  ushort uVar1;
  int unaff_EBP;
  
  uVar1 = *(ushort *)(unaff_EBP + 4) & 0xb8ff;
  *(ushort *)(unaff_EBP + 4) = CONCAT11((byte)(uVar1 >> 8) | (&DAT_000a331f)[param_1],(char)uVar1);
  emu387_decode();
  return;
}


// ================================================================================================
// emu387_exception @ 0xa3890 [__watcall]
// ================================================================================================

void __watcall emu387_exception(byte param_1)

{
  int iVar1;
  byte *unaff_EBP;
  byte *pbVar2;
  undefined4 *puVar3;
  undefined4 auStack_80 [29];
  
  unaff_EBP[4] = unaff_EBP[4] | param_1;
  if ((*unaff_EBP & param_1) == 0) {
    pbVar2 = unaff_EBP;
    puVar3 = auStack_80;
    for (iVar1 = 0x1b; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar3 = *(undefined4 *)pbVar2;
      pbVar2 = pbVar2 + 4;
      puVar3 = puVar3 + 1;
    }
    (*(code *)funcptr_d4d11)();
    puVar3 = auStack_80;
    for (iVar1 = 0x1b; iVar1 != 0; iVar1 = iVar1 + -1) {
      *(undefined4 *)unaff_EBP = *puVar3;
      puVar3 = puVar3 + 1;
      unaff_EBP = unaff_EBP + 4;
    }
  }
  return;
}


// ================================================================================================
// emu387_ea_eax @ 0xa38de [__watcall]
// ================================================================================================

void __watcall emu387_ea_eax(void)

{
  return;
}


// ================================================================================================
// emu387_ea_ecx @ 0xa38e4 [__watcall]
// ================================================================================================

void __watcall emu387_ea_ecx(void)

{
  return;
}


// ================================================================================================
// emu387_ea_edx @ 0xa38ea [__watcall]
// ================================================================================================

void __watcall emu387_ea_edx(void)

{
  return;
}


