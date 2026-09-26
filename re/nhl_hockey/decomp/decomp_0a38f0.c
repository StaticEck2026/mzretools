// Decompiled by Ghidra from hockey.elf (via ledisasm ELF export)
// This is machine generated pseudo-C meant as a reference for porting, it does not compile as is.
#include "prototypes.h"

// ================================================================================================
// sub_a38f0 @ 0xa38f0 [__watcall]
// ================================================================================================

void __watcall sub_a38f0(void)

{
  return;
}


// ================================================================================================
// sub_a38f6 @ 0xa38f6 [__watcall]
// ================================================================================================

void __watcall sub_a38f6(void)

{
  return;
}


// ================================================================================================
// sub_a38fe @ 0xa38fe [__watcall]
// ================================================================================================

void __watcall sub_a38fe(void)

{
  return;
}


// ================================================================================================
// sub_a3904 @ 0xa3904 [__watcall]
// ================================================================================================

void __watcall sub_a3904(void)

{
  return;
}


// ================================================================================================
// sub_a390a @ 0xa390a [__watcall]
// ================================================================================================

void __watcall sub_a390a(void)

{
  return;
}


// ================================================================================================
// sub_a3910 @ 0xa3910 [__watcall]
// ================================================================================================

void __watcall sub_a3910(void)

{
  return;
}


// ================================================================================================
// sub_a3918 @ 0xa3918 [__watcall]
// ================================================================================================

void __watcall sub_a3918(void)

{
  return;
}


// ================================================================================================
// sub_a3920 @ 0xa3920 [__watcall]
// ================================================================================================

void __watcall sub_a3920(void)

{
  return;
}


// ================================================================================================
// sub_a3928 @ 0xa3928 [__watcall]
// ================================================================================================

void __watcall sub_a3928(void)

{
  return;
}


// ================================================================================================
// sub_a3930 @ 0xa3930 [__watcall]
// ================================================================================================

void __watcall sub_a3930(void)

{
  return;
}


// ================================================================================================
// sub_a393a @ 0xa393a [__watcall]
// ================================================================================================

void __watcall sub_a393a(void)

{
  return;
}


// ================================================================================================
// sub_a3944 @ 0xa3944 [__watcall]
// ================================================================================================

void __watcall sub_a3944(void)

{
  return;
}


// ================================================================================================
// sub_a394c @ 0xa394c [__watcall]
// ================================================================================================

void __watcall sub_a394c(void)

{
  return;
}


// ================================================================================================
// sub_a3954 @ 0xa3954 [__watcall]
// ================================================================================================

void __watcall sub_a3954(void)

{
  return;
}


// ================================================================================================
// sub_a395d @ 0xa395d [__watcall]
// ================================================================================================

void __watcall sub_a395d(void)

{
  return;
}


// ================================================================================================
// sub_a3966 @ 0xa3966 [__watcall]
// ================================================================================================

void __watcall sub_a3966(void)

{
  return;
}


// ================================================================================================
// sub_a396f @ 0xa396f [__watcall]
// ================================================================================================

void __watcall sub_a396f(void)

{
  return;
}


// ================================================================================================
// sub_a3978 @ 0xa3978 [__watcall]
// ================================================================================================

void __watcall sub_a3978(void)

{
  return;
}


// ================================================================================================
// sub_a3983 @ 0xa3983 [__watcall]
// ================================================================================================

void __watcall sub_a3983(void)

{
  return;
}


// ================================================================================================
// sub_a398e @ 0xa398e [__watcall]
// ================================================================================================

void __watcall sub_a398e(void)

{
  return;
}


// ================================================================================================
// sub_a3997 @ 0xa3997 [__watcall]
// ================================================================================================

void __watcall sub_a3997(void)

{
  return;
}


// ================================================================================================
// sub_a39a0 @ 0xa39a0 [__watcall]
// ================================================================================================

void __watcall sub_a39a0(undefined4 param_1,undefined4 param_2,undefined4 unaff_EBX)

{
  uint uVar1;
  undefined *unaff_ESI;
  
  uVar1 = CONCAT31((int3)((uint)unaff_EBX >> 8),*unaff_ESI) & 0xffffff07;
  uVar1 = CONCAT22((short)(uVar1 >> 0x10),CONCAT11((byte)((uint)param_1 >> 8) >> 3,(char)uVar1)) &
          0xffff18ff;
  (*(code *)(&PTR_sub_a38de_000a338c)
            [CONCAT22((short)(uVar1 >> 0x10),(ushort)(byte)((byte)uVar1 | (byte)(uVar1 >> 8)))])();
  return;
}


// ================================================================================================
// sub_a39d8 @ 0xa39d8 [__watcall]
// ================================================================================================

void __watcall sub_a39d8(void)

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
    uVar2 = sub_902a0();
                    /* WARNING: Could not recover jumptable at 0x000a37ab. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*(code *)(&PTR_sub_a41e6_000a34ec)[(byte)((byte)((ushort)uVar2 >> 8) & 0x38 | (byte)uVar2)])();
    return;
  }
  uVar3 = CONCAT11(bVar1 >> 3,bVar1) & 0x1807;
  uVar2 = (*(code *)(&PTR_sub_a38de_000a332c)[(byte)((byte)uVar3 | (byte)(uVar3 >> 8))])();
  sub_902a0();
                    /* WARNING: Could not recover jumptable at 0x000a36fe. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)(&PTR_sub_a39dd_000a33ec)[(byte)((byte)((ushort)uVar2 >> 8) & 0x38 | (byte)uVar2)])();
  return;
}


// ================================================================================================
// sub_a39dd @ 0xa39dd [__watcall]
// ================================================================================================

void __watcall sub_a39dd(void)

{
  int unaff_EBP;
  undefined4 *unaff_ESI;
  int unaff_EDI;
  
  sub_a55ce(*unaff_ESI,unaff_EBP + 0x6c);
  sub_a4da4(unaff_EDI + 0x1c + unaff_EBP,unaff_EBP + 0x6c,unaff_EDI + 0x1c + unaff_EBP);
                    /* WARNING: Could not recover jumptable at 0x000a39f8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(unaff_EBP + 0x76))();
  return;
}


// ================================================================================================
// sub_a39fc @ 0xa39fc [__watcall]
// ================================================================================================

void __watcall sub_a39fc(void)

{
  int unaff_EBP;
  undefined4 *unaff_ESI;
  int unaff_EDI;
  
  sub_a55ce(*unaff_ESI,unaff_EBP + 0x6c);
  sub_a51d8(unaff_EDI + 0x1c + unaff_EBP,unaff_EBP + 0x6c,unaff_EDI + 0x1c + unaff_EBP);
                    /* WARNING: Could not recover jumptable at 0x000a3a17. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(unaff_EBP + 0x76))();
  return;
}


// ================================================================================================
// sub_a3a1b @ 0xa3a1b [__watcall]
// ================================================================================================

void __watcall sub_a3a1b(void)

{
  int unaff_EBP;
  undefined4 *unaff_ESI;
  int unaff_EDI;
  
  sub_a55ce(*unaff_ESI,unaff_EBP + 0x6c);
  sub_a4f6a(unaff_EDI + 0x1c + unaff_EBP,unaff_EBP + 0x6c);
  sub_a3874();
  return;
}


// ================================================================================================
// sub_a3a37 @ 0xa3a37 [__watcall]
// ================================================================================================

void __watcall sub_a3a37(void)

{
  int unaff_EBP;
  undefined4 *unaff_ESI;
  int unaff_EDI;
  
  sub_a55ce(*unaff_ESI,unaff_EBP + 0x6c);
  sub_a4f6a(unaff_EDI + 0x1c + unaff_EBP,unaff_EBP + 0x6c);
  sub_a3822();
  return;
}


// ================================================================================================
// sub_a3a53 @ 0xa3a53 [__watcall]
// ================================================================================================

void __watcall sub_a3a53(void)

{
  int unaff_EBP;
  undefined4 *unaff_ESI;
  int unaff_EDI;
  
  sub_a55ce(*unaff_ESI,unaff_EBP + 0x6c);
  sub_a4d96(unaff_EDI + 0x1c + unaff_EBP,unaff_EBP + 0x6c,unaff_EDI + 0x1c + unaff_EBP);
                    /* WARNING: Could not recover jumptable at 0x000a3a6e. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(unaff_EBP + 0x76))();
  return;
}


// ================================================================================================
// sub_a3a72 @ 0xa3a72 [__watcall]
// ================================================================================================

void __watcall sub_a3a72(void)

{
  int unaff_EBP;
  undefined4 *unaff_ESI;
  int unaff_EDI;
  
  sub_a55ce(*unaff_ESI,unaff_EBP + 0x6c);
  sub_a4d96(unaff_EBP + 0x6c,unaff_EDI + 0x1c + unaff_EBP,unaff_EDI + 0x1c + unaff_EBP);
                    /* WARNING: Could not recover jumptable at 0x000a3a8d. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(unaff_EBP + 0x76))();
  return;
}


// ================================================================================================
// sub_a3a91 @ 0xa3a91 [__watcall]
// ================================================================================================

void __watcall sub_a3a91(void)

{
  int unaff_EBP;
  undefined4 *unaff_ESI;
  int unaff_EDI;
  
  sub_a55ce(*unaff_ESI,unaff_EBP + 0x6c);
  sub_a5003(unaff_EDI + 0x1c + unaff_EBP,unaff_EBP + 0x6c,unaff_EDI + 0x1c + unaff_EBP);
                    /* WARNING: Could not recover jumptable at 0x000a3aac. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(unaff_EBP + 0x76))();
  return;
}


// ================================================================================================
// sub_a3ab0 @ 0xa3ab0 [__watcall]
// ================================================================================================

void __watcall sub_a3ab0(void)

{
  int unaff_EBP;
  undefined4 *unaff_ESI;
  int unaff_EDI;
  
  sub_a55ce(*unaff_ESI,unaff_EBP + 0x6c);
  sub_a5003(unaff_EBP + 0x6c,unaff_EDI + 0x1c + unaff_EBP,unaff_EDI + 0x1c + unaff_EBP);
                    /* WARNING: Could not recover jumptable at 0x000a3acb. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(unaff_EBP + 0x76))();
  return;
}


// ================================================================================================
// sub_a3acf @ 0xa3acf [__watcall]
// ================================================================================================

void __watcall sub_a3acf(void)

{
  ushort uVar1;
  int unaff_EBP;
  undefined4 *unaff_ESI;
  int unaff_EDI;
  uint uVar2;
  
  uVar2 = (uint)*(ushort *)(&unk_a3280 + unaff_EDI);
  uVar1 = *(ushort *)(&unk_a3282 + uVar2);
  *(ushort *)(unaff_EBP + 4) = *(ushort *)(unaff_EBP + 4) & 0xc7ff;
  *(ushort *)(unaff_EBP + 4) = *(ushort *)(unaff_EBP + 4) | uVar1;
  *(ushort *)(unaff_EBP + 8) = *(ushort *)(unaff_EBP + 8) & *(ushort *)(&unk_a32ce + uVar2);
  sub_a55ce(*unaff_ESI,uVar2 + 0x1c + unaff_EBP);
  sub_a3680();
  return;
}


// ================================================================================================
// sub_a3b09 @ 0xa3b09 [__watcall]
// ================================================================================================

void __watcall sub_a3b09(void)

{
  undefined4 uVar1;
  int unaff_EBP;
  undefined4 *unaff_ESI;
  int unaff_EDI;
  
  uVar1 = sub_a5488(unaff_EDI + 0x1c + unaff_EBP);
  *unaff_ESI = uVar1;
  sub_a3680();
  return;
}


// ================================================================================================
// sub_a3b1a @ 0xa3b1a [__watcall]
// ================================================================================================

void __watcall sub_a3b1a(void)

{
  ushort uVar1;
  undefined4 uVar2;
  int unaff_EBP;
  undefined4 *unaff_ESI;
  int unaff_EDI;
  
  uVar2 = sub_a5488(unaff_EDI + 0x1c + unaff_EBP);
  *unaff_ESI = uVar2;
  *(ushort *)(unaff_EBP + 8) = *(ushort *)(unaff_EBP + 8) & *(ushort *)(&unk_a32ce + unaff_EDI);
  *(ushort *)(unaff_EBP + 8) = *(ushort *)(unaff_EBP + 8) | *(ushort *)(unk_a32d6 + unaff_EDI);
  uVar1 = *(ushort *)(&unk_a3282 + *(ushort *)(&unk_a327e + unaff_EDI));
  *(ushort *)(unaff_EBP + 4) = *(ushort *)(unaff_EBP + 4) & 0xc7ff;
  *(ushort *)(unaff_EBP + 4) = *(ushort *)(unaff_EBP + 4) | uVar1;
  sub_a3680();
  return;
}


// ================================================================================================
// sub_a3b2b @ 0xa3b2b [__watcall]
// ================================================================================================

void __watcall sub_a3b2b(void)

{
  int iVar1;
  undefined4 *unaff_EBP;
  undefined4 *unaff_ESI;
  
  for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
    *unaff_EBP = *unaff_ESI;
    unaff_ESI = unaff_ESI + 1;
    unaff_EBP = unaff_EBP + 1;
  }
  sub_a3680();
  return;
}


// ================================================================================================
// sub_a3b49 @ 0xa3b49 [__watcall]
// ================================================================================================

void __watcall sub_a3b49(void)

{
  ushort uVar1;
  ushort *unaff_EBP;
  ushort *unaff_ESI;
  
  uVar1 = *unaff_ESI;
  *unaff_EBP = uVar1;
  uVar1 = uVar1 & 0x300;
  if (uVar1 == 0x300) {
    *(code **)(unaff_EBP + 0x3b) = sub_a3680;
  }
  else if (uVar1 == 0x200) {
    *(undefined4 **)(unaff_EBP + 0x3b) = &dword_a37f0;
  }
  else {
    *(undefined4 **)(unaff_EBP + 0x3b) = &dword_a37b4;
  }
  sub_a3680();
  return;
}


// ================================================================================================
// sub_a3b89 @ 0xa3b89 [__watcall]
// ================================================================================================

void __watcall sub_a3b89(void)

{
  int iVar1;
  undefined4 *unaff_EBP;
  undefined4 *unaff_ESI;
  
  for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
    *unaff_ESI = *unaff_EBP;
    unaff_EBP = unaff_EBP + 1;
    unaff_ESI = unaff_ESI + 1;
  }
  sub_a3680();
  return;
}


// ================================================================================================
// sub_a3b9d @ 0xa3b9d [__watcall]
// ================================================================================================

void __watcall sub_a3b9d(void)

{
  undefined2 *unaff_EBP;
  undefined2 *unaff_ESI;
  
  *unaff_ESI = *unaff_EBP;
  sub_a3680();
  return;
}


// ================================================================================================
// sub_a3bab @ 0xa3bab [__watcall]
// ================================================================================================

void __watcall sub_a3bab(void)

{
  int unaff_EBP;
  undefined4 *unaff_ESI;
  int unaff_EDI;
  
  sub_a53c2(*unaff_ESI,unaff_EBP + 0x6c);
  sub_a4da4(unaff_EDI + 0x1c + unaff_EBP,unaff_EBP + 0x6c,unaff_EDI + 0x1c + unaff_EBP);
                    /* WARNING: Could not recover jumptable at 0x000a3bc6. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(unaff_EBP + 0x76))();
  return;
}


// ================================================================================================
// sub_a3bca @ 0xa3bca [__watcall]
// ================================================================================================

void __watcall sub_a3bca(void)

{
  int unaff_EBP;
  undefined4 *unaff_ESI;
  int unaff_EDI;
  
  sub_a53c2(*unaff_ESI,unaff_EBP + 0x6c);
  sub_a51d8(unaff_EDI + 0x1c + unaff_EBP,unaff_EBP + 0x6c,unaff_EDI + 0x1c + unaff_EBP);
                    /* WARNING: Could not recover jumptable at 0x000a3be5. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(unaff_EBP + 0x76))();
  return;
}


// ================================================================================================
// sub_a3be9 @ 0xa3be9 [__watcall]
// ================================================================================================

void __watcall sub_a3be9(void)

{
  int unaff_EBP;
  undefined4 *unaff_ESI;
  int unaff_EDI;
  
  sub_a53c2(*unaff_ESI,unaff_EBP + 0x6c);
  sub_a4f6a(unaff_EDI + 0x1c + unaff_EBP,unaff_EBP + 0x6c);
  sub_a3874();
  return;
}


// ================================================================================================
// sub_a3c05 @ 0xa3c05 [__watcall]
// ================================================================================================

void __watcall sub_a3c05(void)

{
  int unaff_EBP;
  undefined4 *unaff_ESI;
  int unaff_EDI;
  
  sub_a53c2(*unaff_ESI,unaff_EBP + 0x6c);
  sub_a4f6a(unaff_EDI + 0x1c + unaff_EBP,unaff_EBP + 0x6c);
  sub_a3822();
  return;
}


// ================================================================================================
// sub_a3c21 @ 0xa3c21 [__watcall]
// ================================================================================================

void __watcall sub_a3c21(void)

{
  int unaff_EBP;
  undefined4 *unaff_ESI;
  int unaff_EDI;
  
  sub_a53c2(*unaff_ESI,unaff_EBP + 0x6c);
  sub_a4d96(unaff_EDI + 0x1c + unaff_EBP,unaff_EBP + 0x6c,unaff_EDI + 0x1c + unaff_EBP);
                    /* WARNING: Could not recover jumptable at 0x000a3c3c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(unaff_EBP + 0x76))();
  return;
}


// ================================================================================================
// sub_a3c40 @ 0xa3c40 [__watcall]
// ================================================================================================

void __watcall sub_a3c40(void)

{
  int unaff_EBP;
  undefined4 *unaff_ESI;
  int unaff_EDI;
  
  sub_a53c2(*unaff_ESI,unaff_EBP + 0x6c);
  sub_a4d96(unaff_EBP + 0x6c,unaff_EDI + 0x1c + unaff_EBP,unaff_EDI + 0x1c + unaff_EBP);
                    /* WARNING: Could not recover jumptable at 0x000a3c5b. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(unaff_EBP + 0x76))();
  return;
}


// ================================================================================================
// sub_a3c5f @ 0xa3c5f [__watcall]
// ================================================================================================

void __watcall sub_a3c5f(void)

{
  int unaff_EBP;
  undefined4 *unaff_ESI;
  int unaff_EDI;
  
  sub_a53c2(*unaff_ESI,unaff_EBP + 0x6c);
  sub_a5003(unaff_EDI + 0x1c + unaff_EBP,unaff_EBP + 0x6c,unaff_EDI + 0x1c + unaff_EBP);
                    /* WARNING: Could not recover jumptable at 0x000a3c7a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(unaff_EBP + 0x76))();
  return;
}


// ================================================================================================
// sub_a3c7e @ 0xa3c7e [__watcall]
// ================================================================================================

void __watcall sub_a3c7e(void)

{
  int unaff_EBP;
  undefined4 *unaff_ESI;
  int unaff_EDI;
  
  sub_a53c2(*unaff_ESI,unaff_EBP + 0x6c);
  sub_a5003(unaff_EBP + 0x6c,unaff_EDI + 0x1c + unaff_EBP,unaff_EDI + 0x1c + unaff_EBP);
                    /* WARNING: Could not recover jumptable at 0x000a3c99. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(unaff_EBP + 0x76))();
  return;
}


// ================================================================================================
// sub_a3c9d @ 0xa3c9d [__watcall]
// ================================================================================================

void __watcall sub_a3c9d(void)

{
  ushort uVar1;
  int unaff_EBP;
  undefined4 *unaff_ESI;
  int unaff_EDI;
  uint uVar2;
  
  uVar2 = (uint)*(ushort *)(&unk_a3280 + unaff_EDI);
  uVar1 = *(ushort *)(&unk_a3282 + uVar2);
  *(ushort *)(unaff_EBP + 4) = *(ushort *)(unaff_EBP + 4) & 0xc7ff;
  *(ushort *)(unaff_EBP + 4) = *(ushort *)(unaff_EBP + 4) | uVar1;
  *(ushort *)(unaff_EBP + 8) = *(ushort *)(unaff_EBP + 8) & *(ushort *)(&unk_a32ce + uVar2);
  sub_a53c2(*unaff_ESI,uVar2 + 0x1c + unaff_EBP);
  sub_a3680();
  return;
}


// ================================================================================================
// sub_a3cd7 @ 0xa3cd7 [__watcall]
// ================================================================================================

void __watcall sub_a3cd7(void)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  ushort *unaff_EBP;
  undefined4 *unaff_ESI;
  int unaff_EDI;
  
  puVar1 = (undefined4 *)(unaff_EDI + 0x1c + (int)unaff_EBP);
  uVar2 = *puVar1;
  uVar3 = puVar1[1];
  uVar4 = *(undefined4 *)((int)puVar1 + 6);
  sub_a5693(unaff_EDI + 0x1c + (int)unaff_EBP,*unaff_EBP & 0xc00);
  uVar5 = sub_a5353(unaff_EDI + 0x1c + (int)unaff_EBP);
  *unaff_ESI = uVar5;
  puVar1 = (undefined4 *)(unaff_EDI + 0x1c + (int)unaff_EBP);
  *(undefined4 *)((int)puVar1 + 6) = uVar4;
  puVar1[1] = uVar3;
  *puVar1 = uVar2;
  sub_a3680();
  return;
}


// ================================================================================================
// sub_a3d13 @ 0xa3d13 [__watcall]
// ================================================================================================

void __watcall sub_a3d13(void)

{
  ushort uVar1;
  undefined4 uVar2;
  ushort *unaff_EBP;
  undefined4 *unaff_ESI;
  int unaff_EDI;
  
  sub_a5693(unaff_EDI + 0x1c + (int)unaff_EBP,*unaff_EBP & 0xc00);
  uVar2 = sub_a5353(unaff_EDI + 0x1c + (int)unaff_EBP);
  *unaff_ESI = uVar2;
  unaff_EBP[4] = unaff_EBP[4] & *(ushort *)(&unk_a32ce + unaff_EDI);
  unaff_EBP[4] = unaff_EBP[4] | *(ushort *)(unk_a32d6 + unaff_EDI);
  uVar1 = *(ushort *)(&unk_a3282 + *(ushort *)(&unk_a327e + unaff_EDI));
  unaff_EBP[2] = unaff_EBP[2] & 0xc7ff;
  unaff_EBP[2] = unaff_EBP[2] | uVar1;
  sub_a3680();
  return;
}


// ================================================================================================
// sub_a3d37 @ 0xa3d37 [__watcall]
// ================================================================================================

void __watcall sub_a3d37(void)

{
  int unaff_EBP;
  undefined4 *unaff_ESI;
  int unaff_EDI;
  
  sub_a5408(*unaff_ESI,unaff_ESI[1],unaff_EBP + 0x6c);
  sub_a4da4(unaff_EDI + 0x1c + unaff_EBP,unaff_EBP + 0x6c,unaff_EDI + 0x1c + unaff_EBP);
                    /* WARNING: Could not recover jumptable at 0x000a3d56. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(unaff_EBP + 0x76))();
  return;
}


// ================================================================================================
// sub_a3d5a @ 0xa3d5a [__watcall]
// ================================================================================================

void __watcall sub_a3d5a(void)

{
  int unaff_EBP;
  undefined4 *unaff_ESI;
  int unaff_EDI;
  
  sub_a5408(*unaff_ESI,unaff_ESI[1],unaff_EBP + 0x6c);
  sub_a51d8(unaff_EDI + 0x1c + unaff_EBP,unaff_EBP + 0x6c,unaff_EDI + 0x1c + unaff_EBP);
                    /* WARNING: Could not recover jumptable at 0x000a3d79. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(unaff_EBP + 0x76))();
  return;
}


// ================================================================================================
// sub_a3d7d @ 0xa3d7d [__watcall]
// ================================================================================================

void __watcall sub_a3d7d(void)

{
  int unaff_EBP;
  undefined4 *unaff_ESI;
  int unaff_EDI;
  
  sub_a5408(*unaff_ESI,unaff_ESI[1],unaff_EBP + 0x6c);
  sub_a4f6a(unaff_EDI + 0x1c + unaff_EBP,unaff_EBP + 0x6c);
  sub_a3874();
  return;
}


// ================================================================================================
// sub_a3d9d @ 0xa3d9d [__watcall]
// ================================================================================================

void __watcall sub_a3d9d(void)

{
  int unaff_EBP;
  undefined4 *unaff_ESI;
  int unaff_EDI;
  
  sub_a5408(*unaff_ESI,unaff_ESI[1],unaff_EBP + 0x6c);
  sub_a4f6a(unaff_EDI + 0x1c + unaff_EBP,unaff_EBP + 0x6c);
  sub_a3822();
  return;
}


// ================================================================================================
// sub_a3dbd @ 0xa3dbd [__watcall]
// ================================================================================================

void __watcall sub_a3dbd(void)

{
  int unaff_EBP;
  undefined4 *unaff_ESI;
  int unaff_EDI;
  
  sub_a5408(*unaff_ESI,unaff_ESI[1],unaff_EBP + 0x6c);
  sub_a4d96(unaff_EDI + 0x1c + unaff_EBP,unaff_EBP + 0x6c,unaff_EDI + 0x1c + unaff_EBP);
                    /* WARNING: Could not recover jumptable at 0x000a3ddc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(unaff_EBP + 0x76))();
  return;
}


// ================================================================================================
// sub_a3de0 @ 0xa3de0 [__watcall]
// ================================================================================================

void __watcall sub_a3de0(void)

{
  int unaff_EBP;
  undefined4 *unaff_ESI;
  int unaff_EDI;
  
  sub_a5408(*unaff_ESI,unaff_ESI[1],unaff_EBP + 0x6c);
  sub_a4d96(unaff_EBP + 0x6c,unaff_EDI + 0x1c + unaff_EBP,unaff_EDI + 0x1c + unaff_EBP);
                    /* WARNING: Could not recover jumptable at 0x000a3dff. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(unaff_EBP + 0x76))();
  return;
}


// ================================================================================================
// sub_a3e03 @ 0xa3e03 [__watcall]
// ================================================================================================

void __watcall sub_a3e03(void)

{
  int unaff_EBP;
  undefined4 *unaff_ESI;
  int unaff_EDI;
  
  sub_a5408(*unaff_ESI,unaff_ESI[1],unaff_EBP + 0x6c);
  sub_a5003(unaff_EDI + 0x1c + unaff_EBP,unaff_EBP + 0x6c,unaff_EDI + 0x1c + unaff_EBP);
                    /* WARNING: Could not recover jumptable at 0x000a3e22. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(unaff_EBP + 0x76))();
  return;
}


// ================================================================================================
// sub_a3e26 @ 0xa3e26 [__watcall]
// ================================================================================================

void __watcall sub_a3e26(void)

{
  int unaff_EBP;
  undefined4 *unaff_ESI;
  int unaff_EDI;
  
  sub_a5408(*unaff_ESI,unaff_ESI[1],unaff_EBP + 0x6c);
  sub_a5003(unaff_EBP + 0x6c,unaff_EDI + 0x1c + unaff_EBP,unaff_EDI + 0x1c + unaff_EBP);
                    /* WARNING: Could not recover jumptable at 0x000a3e45. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(unaff_EBP + 0x76))();
  return;
}


// ================================================================================================
// sub_a3e49 @ 0xa3e49 [__watcall]
// ================================================================================================

void __watcall sub_a3e49(void)

{
  ushort uVar1;
  int unaff_EBP;
  undefined4 *unaff_ESI;
  int unaff_EDI;
  uint uVar2;
  
  uVar2 = (uint)*(ushort *)(&unk_a3280 + unaff_EDI);
  uVar1 = *(ushort *)(&unk_a3282 + uVar2);
  *(ushort *)(unaff_EBP + 4) = *(ushort *)(unaff_EBP + 4) & 0xc7ff;
  *(ushort *)(unaff_EBP + 4) = *(ushort *)(unaff_EBP + 4) | uVar1;
  *(ushort *)(unaff_EBP + 8) = *(ushort *)(unaff_EBP + 8) & *(ushort *)(&unk_a32ce + uVar2);
  *(undefined4 *)(uVar2 + 0x1c + unaff_EBP) = *unaff_ESI;
  *(undefined4 *)(uVar2 + 0x20 + unaff_EBP) = unaff_ESI[1];
  *(undefined2 *)(uVar2 + 0x24 + unaff_EBP) = *(undefined2 *)(unaff_ESI + 2);
  sub_a3680();
  return;
}


// ================================================================================================
// sub_a3e90 @ 0xa3e90 [__watcall]
// ================================================================================================

void __watcall sub_a3e90(void)

{
  ushort uVar1;
  int unaff_EBP;
  undefined4 *unaff_ESI;
  int unaff_EDI;
  uint uVar2;
  
  uVar2 = (uint)*(ushort *)(&unk_a3280 + unaff_EDI);
  uVar1 = *(ushort *)(&unk_a3282 + uVar2);
  *(ushort *)(unaff_EBP + 4) = *(ushort *)(unaff_EBP + 4) & 0xc7ff;
  *(ushort *)(unaff_EBP + 4) = *(ushort *)(unaff_EBP + 4) | uVar1;
  *(ushort *)(unaff_EBP + 8) = *(ushort *)(unaff_EBP + 8) & *(ushort *)(&unk_a32ce + uVar2);
  sub_a5408(*unaff_ESI,unaff_ESI[1],uVar2 + 0x1c + unaff_EBP);
  sub_a3680();
  return;
}


// ================================================================================================
// sub_a3ece @ 0xa3ece [__watcall]
// ================================================================================================

void __watcall sub_a3ece(void)

{
  int unaff_EBP;
  undefined8 *unaff_ESI;
  int unaff_EDI;
  undefined8 uVar1;
  
  uVar1 = sub_a5507(unaff_EDI + 0x1c + unaff_EBP);
  *unaff_ESI = uVar1;
  sub_a3680();
  return;
}


// ================================================================================================
// sub_a3ee3 @ 0xa3ee3 [__watcall]
// ================================================================================================

void __watcall sub_a3ee3(void)

{
  ushort uVar1;
  int unaff_EBP;
  undefined4 *unaff_ESI;
  int unaff_EDI;
  
  *unaff_ESI = *(undefined4 *)(unaff_EDI + 0x1c + unaff_EBP);
  unaff_ESI[1] = *(undefined4 *)(unaff_EDI + 0x20 + unaff_EBP);
  *(undefined2 *)(unaff_ESI + 2) = *(undefined2 *)(unaff_EDI + 0x24 + unaff_EBP);
  *(ushort *)(unaff_EBP + 8) = *(ushort *)(unaff_EBP + 8) & *(ushort *)(&unk_a32ce + unaff_EDI);
  *(ushort *)(unaff_EBP + 8) = *(ushort *)(unaff_EBP + 8) | *(ushort *)(unk_a32d6 + unaff_EDI);
  uVar1 = *(ushort *)(&unk_a3282 + *(ushort *)(&unk_a327e + unaff_EDI));
  *(ushort *)(unaff_EBP + 4) = *(ushort *)(unaff_EBP + 4) & 0xc7ff;
  *(ushort *)(unaff_EBP + 4) = *(ushort *)(unaff_EBP + 4) | uVar1;
  sub_a3680();
  return;
}


// ================================================================================================
// sub_a3f01 @ 0xa3f01 [__watcall]
// ================================================================================================

void __watcall sub_a3f01(void)

{
  ushort uVar1;
  int unaff_EBP;
  undefined8 *unaff_ESI;
  int unaff_EDI;
  undefined8 uVar2;
  
  uVar2 = sub_a5507(unaff_EDI + 0x1c + unaff_EBP);
  *unaff_ESI = uVar2;
  *(ushort *)(unaff_EBP + 8) = *(ushort *)(unaff_EBP + 8) & *(ushort *)(&unk_a32ce + unaff_EDI);
  *(ushort *)(unaff_EBP + 8) = *(ushort *)(unaff_EBP + 8) | *(ushort *)(unk_a32d6 + unaff_EDI);
  uVar1 = *(ushort *)(&unk_a3282 + *(ushort *)(&unk_a327e + unaff_EDI));
  *(ushort *)(unaff_EBP + 4) = *(ushort *)(unaff_EBP + 4) & 0xc7ff;
  *(ushort *)(unaff_EBP + 4) = *(ushort *)(unaff_EBP + 4) | uVar1;
  sub_a3680();
  return;
}


// ================================================================================================
// sub_a3f16 @ 0xa3f16 [__watcall]
// ================================================================================================

void __watcall sub_a3f16(void)

{
  undefined4 *puVar1;
  int iVar2;
  uint uVar3;
  undefined4 *unaff_EBP;
  undefined4 *unaff_ESI;
  undefined4 *puVar4;
  
  puVar4 = unaff_EBP;
  for (iVar2 = 7; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar4 = *unaff_ESI;
    unaff_ESI = unaff_ESI + 1;
    puVar4 = puVar4 + 1;
  }
  uVar3 = ((unaff_EBP[1] & 0x3800) >> 0xb) * 10;
  iVar2 = 8;
  do {
    puVar4 = (undefined4 *)((int)unaff_EBP + uVar3 + 0x1c);
    *puVar4 = *unaff_ESI;
    puVar1 = unaff_ESI + 2;
    puVar4[1] = unaff_ESI[1];
    unaff_ESI = (undefined4 *)((int)unaff_ESI + 10);
    *(undefined2 *)(puVar4 + 2) = *(undefined2 *)puVar1;
    uVar3 = (uint)*(ushort *)(&unk_a327e + uVar3);
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  sub_a3680();
  return;
}


// ================================================================================================
// sub_a3f5d @ 0xa3f5d [__watcall]
// ================================================================================================

void __watcall sub_a3f5d(void)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *unaff_EBP;
  undefined4 *unaff_ESI;
  undefined4 *puVar3;
  uint unaff_EDI;
  
  puVar3 = unaff_EBP;
  for (iVar2 = 7; iVar2 != 0; iVar2 = iVar2 + -1) {
    *unaff_ESI = *puVar3;
    puVar3 = puVar3 + 1;
    unaff_ESI = unaff_ESI + 1;
  }
  iVar2 = 8;
  do {
    puVar3 = (undefined4 *)(unaff_EDI + 0x1c + (int)unaff_EBP);
    *unaff_ESI = *puVar3;
    puVar1 = unaff_ESI + 2;
    unaff_ESI[1] = puVar3[1];
    unaff_ESI = (undefined4 *)((int)unaff_ESI + 10);
    *(undefined2 *)puVar1 = *(undefined2 *)(puVar3 + 2);
    unaff_EDI = (uint)*(ushort *)(&unk_a327e + unaff_EDI);
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  FUN_000a4873();
  return;
}


// ================================================================================================
// sub_a3f88 @ 0xa3f88 [__watcall]
// ================================================================================================

void __watcall sub_a3f88(void)

{
  int unaff_EBP;
  undefined2 *unaff_ESI;
  
  *unaff_ESI = *(undefined2 *)(unaff_EBP + 4);
  sub_a3680();
  return;
}


// ================================================================================================
// sub_a3f96 @ 0xa3f96 [__watcall]
// ================================================================================================

void __watcall sub_a3f96(void)

{
  int unaff_EBP;
  short *unaff_ESI;
  int unaff_EDI;
  
  sub_a53c2((int)*unaff_ESI,unaff_EBP + 0x6c);
  sub_a4da4(unaff_EDI + 0x1c + unaff_EBP,unaff_EBP + 0x6c,unaff_EDI + 0x1c + unaff_EBP);
                    /* WARNING: Could not recover jumptable at 0x000a3fb3. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(unaff_EBP + 0x76))();
  return;
}


// ================================================================================================
// sub_a3fb7 @ 0xa3fb7 [__watcall]
// ================================================================================================

void __watcall sub_a3fb7(void)

{
  int unaff_EBP;
  short *unaff_ESI;
  int unaff_EDI;
  
  sub_a53c2((int)*unaff_ESI,unaff_EBP + 0x6c);
  sub_a51d8(unaff_EDI + 0x1c + unaff_EBP,unaff_EBP + 0x6c,unaff_EDI + 0x1c + unaff_EBP);
                    /* WARNING: Could not recover jumptable at 0x000a3fd4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(unaff_EBP + 0x76))();
  return;
}


// ================================================================================================
// sub_a3fd8 @ 0xa3fd8 [__watcall]
// ================================================================================================

void __watcall sub_a3fd8(void)

{
  int unaff_EBP;
  short *unaff_ESI;
  int unaff_EDI;
  
  sub_a53c2((int)*unaff_ESI,unaff_EBP + 0x6c);
  sub_a4f6a(unaff_EDI + 0x1c + unaff_EBP,unaff_EBP + 0x6c);
  sub_a3874();
  return;
}


// ================================================================================================
// sub_a3ff6 @ 0xa3ff6 [__watcall]
// ================================================================================================

void __watcall sub_a3ff6(void)

{
  int unaff_EBP;
  short *unaff_ESI;
  int unaff_EDI;
  
  sub_a53c2((int)*unaff_ESI,unaff_EBP + 0x6c);
  sub_a4f6a(unaff_EDI + 0x1c + unaff_EBP,unaff_EBP + 0x6c);
  sub_a3822();
  return;
}


// ================================================================================================
// sub_a4014 @ 0xa4014 [__watcall]
// ================================================================================================

void __watcall sub_a4014(void)

{
  int unaff_EBP;
  short *unaff_ESI;
  int unaff_EDI;
  
  sub_a53c2((int)*unaff_ESI,unaff_EBP + 0x6c);
  sub_a4d96(unaff_EDI + 0x1c + unaff_EBP,unaff_EBP + 0x6c,unaff_EDI + 0x1c + unaff_EBP);
                    /* WARNING: Could not recover jumptable at 0x000a4031. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(unaff_EBP + 0x76))();
  return;
}


// ================================================================================================
// sub_a4035 @ 0xa4035 [__watcall]
// ================================================================================================

void __watcall sub_a4035(void)

{
  int unaff_EBP;
  short *unaff_ESI;
  int unaff_EDI;
  
  sub_a53c2((int)*unaff_ESI,unaff_EBP + 0x6c);
  sub_a4d96(unaff_EBP + 0x6c,unaff_EDI + 0x1c + unaff_EBP,unaff_EDI + 0x1c + unaff_EBP);
                    /* WARNING: Could not recover jumptable at 0x000a4052. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(unaff_EBP + 0x76))();
  return;
}


// ================================================================================================
// sub_a4056 @ 0xa4056 [__watcall]
// ================================================================================================

void __watcall sub_a4056(void)

{
  int unaff_EBP;
  short *unaff_ESI;
  int unaff_EDI;
  
  sub_a53c2((int)*unaff_ESI,unaff_EBP + 0x6c);
  sub_a5003(unaff_EDI + 0x1c + unaff_EBP,unaff_EBP + 0x6c,unaff_EDI + 0x1c + unaff_EBP);
                    /* WARNING: Could not recover jumptable at 0x000a4073. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(unaff_EBP + 0x76))();
  return;
}


// ================================================================================================
// sub_a4077 @ 0xa4077 [__watcall]
// ================================================================================================

void __watcall sub_a4077(void)

{
  int unaff_EBP;
  short *unaff_ESI;
  int unaff_EDI;
  
  sub_a53c2((int)*unaff_ESI,unaff_EBP + 0x6c);
  sub_a5003(unaff_EBP + 0x6c,unaff_EDI + 0x1c + unaff_EBP,unaff_EDI + 0x1c + unaff_EBP);
                    /* WARNING: Could not recover jumptable at 0x000a4094. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(unaff_EBP + 0x76))();
  return;
}


// ================================================================================================
// sub_a4098 @ 0xa4098 [__watcall]
// ================================================================================================

void __watcall sub_a4098(void)

{
  ushort uVar1;
  int unaff_EBP;
  short *unaff_ESI;
  int unaff_EDI;
  uint uVar2;
  
  uVar2 = (uint)*(ushort *)(&unk_a3280 + unaff_EDI);
  uVar1 = *(ushort *)(&unk_a3282 + uVar2);
  *(ushort *)(unaff_EBP + 4) = *(ushort *)(unaff_EBP + 4) & 0xc7ff;
  *(ushort *)(unaff_EBP + 4) = *(ushort *)(unaff_EBP + 4) | uVar1;
  *(ushort *)(unaff_EBP + 8) = *(ushort *)(unaff_EBP + 8) & *(ushort *)(&unk_a32ce + uVar2);
  sub_a53c2((int)*unaff_ESI,uVar2 + 0x1c + unaff_EBP);
  sub_a3680();
  return;
}


// ================================================================================================
// sub_a40d4 @ 0xa40d4 [__watcall]
// ================================================================================================

void __watcall sub_a40d4(undefined4 param_1,undefined4 unaff_EDX)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  short sVar5;
  int iVar6;
  undefined2 *unaff_EBP;
  short *unaff_ESI;
  int unaff_EDI;
  
  puVar1 = (undefined4 *)(unaff_EDI + 0x1c + (int)unaff_EBP);
  uVar2 = *puVar1;
  uVar3 = puVar1[1];
  uVar4 = *(undefined4 *)((int)puVar1 + 6);
  sub_a5693(unaff_EDI + 0x1c + (int)unaff_EBP,
            CONCAT22((short)((uint)unaff_EDX >> 0x10),*unaff_EBP) & 0xffff0c00);
  iVar6 = sub_a5353(unaff_EDI + 0x1c + (int)unaff_EBP);
  sVar5 = (short)iVar6;
  if (sVar5 != iVar6) {
    sVar5 = -0x8000;
  }
  *unaff_ESI = sVar5;
  puVar1 = (undefined4 *)(unaff_EDI + 0x1c + (int)unaff_EBP);
  *(undefined4 *)((int)puVar1 + 6) = uVar4;
  puVar1[1] = uVar3;
  *puVar1 = uVar2;
  sub_a3680();
  return;
}


// ================================================================================================
// sub_a411c @ 0xa411c [__watcall]
// ================================================================================================

void __watcall sub_a411c(undefined4 param_1,undefined4 unaff_EDX)

{
  ushort uVar1;
  short sVar2;
  int iVar3;
  undefined2 *unaff_EBP;
  short *unaff_ESI;
  int unaff_EDI;
  
  sub_a5693(unaff_EDI + 0x1c + (int)unaff_EBP,
            CONCAT22((short)((uint)unaff_EDX >> 0x10),*unaff_EBP) & 0xffff0c00);
  iVar3 = sub_a5353(unaff_EDI + 0x1c + (int)unaff_EBP);
  sVar2 = (short)iVar3;
  if (sVar2 != iVar3) {
    sVar2 = -0x8000;
  }
  *unaff_ESI = sVar2;
  unaff_EBP[4] = unaff_EBP[4] & *(ushort *)(&unk_a32ce + unaff_EDI);
  unaff_EBP[4] = unaff_EBP[4] | *(ushort *)(unk_a32d6 + unaff_EDI);
  uVar1 = *(ushort *)(&unk_a3282 + *(ushort *)(&unk_a327e + unaff_EDI));
  unaff_EBP[2] = unaff_EBP[2] & 0xc7ff;
  unaff_EBP[2] = unaff_EBP[2] | uVar1;
  sub_a3680();
  return;
}


// ================================================================================================
// sub_a414c @ 0xa414c [__watcall]
// ================================================================================================

void __watcall sub_a414c(void)

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
    uVar2 = sub_902a0();
                    /* WARNING: Could not recover jumptable at 0x000a37ab. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*(code *)(&PTR_sub_a41e6_000a34ec)[(byte)((byte)((ushort)uVar2 >> 8) & 0x38 | (byte)uVar2)])();
    return;
  }
  uVar3 = CONCAT11(bVar1 >> 3,bVar1) & 0x1807;
  uVar2 = (*(code *)(&PTR_sub_a38de_000a332c)[(byte)((byte)uVar3 | (byte)(uVar3 >> 8))])();
  sub_902a0();
                    /* WARNING: Could not recover jumptable at 0x000a36fe. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)(&PTR_sub_a39dd_000a33ec)[(byte)((byte)((ushort)uVar2 >> 8) & 0x38 | (byte)uVar2)])();
  return;
}


// ================================================================================================
// sub_a4151 @ 0xa4151 [__watcall]
// ================================================================================================

void __watcall sub_a4151(void)

{
  ushort uVar1;
  int unaff_EBP;
  undefined4 *unaff_ESI;
  int unaff_EDI;
  uint uVar2;
  
  uVar2 = (uint)*(ushort *)(&unk_a3280 + unaff_EDI);
  uVar1 = *(ushort *)(&unk_a3282 + uVar2);
  *(ushort *)(unaff_EBP + 4) = *(ushort *)(unaff_EBP + 4) & 0xc7ff;
  *(ushort *)(unaff_EBP + 4) = *(ushort *)(unaff_EBP + 4) | uVar1;
  *(ushort *)(unaff_EBP + 8) = *(ushort *)(unaff_EBP + 8) & *(ushort *)(&unk_a32ce + uVar2);
  sub_a53d3(*unaff_ESI,uVar2 + 0x1c + unaff_EBP);
  sub_a3680();
  return;
}


// ================================================================================================
// sub_a418b @ 0xa418b [__watcall]
// ================================================================================================

void __watcall sub_a418b(void)

{
  ushort uVar1;
  int unaff_EBP;
  int unaff_EDI;
  
  *(ushort *)(unaff_EBP + 8) = *(ushort *)(unaff_EBP + 8) & *(ushort *)(&unk_a32ce + unaff_EDI);
  *(ushort *)(unaff_EBP + 8) = *(ushort *)(unaff_EBP + 8) | *(ushort *)(unk_a32d6 + unaff_EDI);
  uVar1 = *(ushort *)(&unk_a3282 + *(ushort *)(&unk_a327e + unaff_EDI));
  *(ushort *)(unaff_EBP + 4) = *(ushort *)(unaff_EBP + 4) & 0xc7ff;
  *(ushort *)(unaff_EBP + 4) = *(ushort *)(unaff_EBP + 4) | uVar1;
  sub_a3680();
  return;
}


// ================================================================================================
// sub_a4190 @ 0xa4190 [__watcall]
// ================================================================================================

void __watcall sub_a4190(void)

{
  ushort uVar1;
  undefined4 uVar2;
  ushort *unaff_EBP;
  undefined4 *unaff_ESI;
  int unaff_EDI;
  
  sub_a5693(unaff_EDI + 0x1c + (int)unaff_EBP,*unaff_EBP & 0xc00);
  uVar2 = sub_a5358(unaff_EDI + 0x1c + (int)unaff_EBP);
  *unaff_ESI = uVar2;
  unaff_EBP[4] = unaff_EBP[4] & *(ushort *)(&unk_a32ce + unaff_EDI);
  unaff_EBP[4] = unaff_EBP[4] | *(ushort *)(unk_a32d6 + unaff_EDI);
  uVar1 = *(ushort *)(&unk_a3282 + *(ushort *)(&unk_a327e + unaff_EDI));
  unaff_EBP[2] = unaff_EBP[2] & 0xc7ff;
  unaff_EBP[2] = unaff_EBP[2] | uVar1;
  sub_a3680();
  return;
}


// ================================================================================================
// sub_a41b4 @ 0xa41b4 [__watcall]
// ================================================================================================

void __watcall sub_a41b4(void)

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
    uVar2 = sub_902a0();
                    /* WARNING: Could not recover jumptable at 0x000a37ab. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*(code *)(&PTR_sub_a41e6_000a34ec)[(byte)((byte)((ushort)uVar2 >> 8) & 0x38 | (byte)uVar2)])();
    return;
  }
  uVar3 = CONCAT11(bVar1 >> 3,bVar1) & 0x1807;
  uVar2 = (*(code *)(&PTR_sub_a38de_000a332c)[(byte)((byte)uVar3 | (byte)(uVar3 >> 8))])();
  sub_902a0();
                    /* WARNING: Could not recover jumptable at 0x000a36fe. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)(&PTR_sub_a39dd_000a33ec)[(byte)((byte)((ushort)uVar2 >> 8) & 0x38 | (byte)uVar2)])();
  return;
}


// ================================================================================================
// sub_a41b9 @ 0xa41b9 [__watcall]
// ================================================================================================

void __watcall sub_a41b9(undefined4 param_1,undefined4 param_2,int unaff_EBX)

{
                    /* WARNING: Could not recover jumptable at 0x000a41b9. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(&DAT_000a41c1 + unaff_EBX * 4))();
  return;
}


// ================================================================================================
// sub_a41e6 @ 0xa41e6 [__watcall]
// ================================================================================================

void __watcall sub_a41e6(void)

{
  int unaff_EBP;
  int unaff_ESI;
  int unaff_EDI;
  
  sub_a4da4(unaff_EDI + 0x1c + unaff_EBP,unaff_ESI + 0x1c + unaff_EBP,unaff_EDI + 0x1c + unaff_EBP);
                    /* WARNING: Could not recover jumptable at 0x000a41f7. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(unaff_EBP + 0x76))();
  return;
}


// ================================================================================================
// sub_a41fb @ 0xa41fb [__watcall]
// ================================================================================================

void __watcall sub_a41fb(void)

{
  int unaff_EBP;
  int unaff_ESI;
  int unaff_EDI;
  
  sub_a51d8(unaff_EDI + 0x1c + unaff_EBP,unaff_ESI + 0x1c + unaff_EBP,unaff_EDI + 0x1c + unaff_EBP);
                    /* WARNING: Could not recover jumptable at 0x000a420c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(unaff_EBP + 0x76))();
  return;
}


// ================================================================================================
// sub_a4210 @ 0xa4210 [__watcall]
// ================================================================================================

void __watcall sub_a4210(void)

{
  int unaff_EBP;
  int unaff_ESI;
  int unaff_EDI;
  
  sub_a4f6a(unaff_EDI + 0x1c + unaff_EBP,unaff_ESI + 0x1c + unaff_EBP);
  sub_a3874();
  return;
}


// ================================================================================================
// sub_a4222 @ 0xa4222 [__watcall]
// ================================================================================================

void __watcall sub_a4222(void)

{
  int unaff_EBP;
  int unaff_ESI;
  int unaff_EDI;
  
  sub_a4f6a(unaff_EDI + 0x1c + unaff_EBP,unaff_ESI + 0x1c + unaff_EBP);
  sub_a3822();
  return;
}


// ================================================================================================
// sub_a4234 @ 0xa4234 [__watcall]
// ================================================================================================

void __watcall sub_a4234(void)

{
  int unaff_EBP;
  int unaff_ESI;
  int unaff_EDI;
  
  sub_a4d96(unaff_EDI + 0x1c + unaff_EBP,unaff_ESI + 0x1c + unaff_EBP,unaff_EDI + 0x1c + unaff_EBP);
                    /* WARNING: Could not recover jumptable at 0x000a4245. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(unaff_EBP + 0x76))();
  return;
}


// ================================================================================================
// sub_a4249 @ 0xa4249 [__watcall]
// ================================================================================================

void __watcall sub_a4249(void)

{
  int unaff_EBP;
  int unaff_ESI;
  int unaff_EDI;
  
  sub_a4d96(unaff_ESI + 0x1c + unaff_EBP,unaff_EDI + 0x1c + unaff_EBP,unaff_EDI + 0x1c + unaff_EBP);
                    /* WARNING: Could not recover jumptable at 0x000a425a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(unaff_EBP + 0x76))();
  return;
}


// ================================================================================================
// sub_a425e @ 0xa425e [__watcall]
// ================================================================================================

void __watcall sub_a425e(void)

{
  int unaff_EBP;
  int unaff_ESI;
  int unaff_EDI;
  
  sub_a5003(unaff_EDI + 0x1c + unaff_EBP,unaff_ESI + 0x1c + unaff_EBP,unaff_EDI + 0x1c + unaff_EBP);
                    /* WARNING: Could not recover jumptable at 0x000a426f. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(unaff_EBP + 0x76))();
  return;
}


// ================================================================================================
// sub_a4273 @ 0xa4273 [__watcall]
// ================================================================================================

void __watcall sub_a4273(void)

{
  int unaff_EBP;
  int unaff_ESI;
  int unaff_EDI;
  
  sub_a5003(unaff_ESI + 0x1c + unaff_EBP,unaff_EDI + 0x1c + unaff_EBP,unaff_EDI + 0x1c + unaff_EBP);
                    /* WARNING: Could not recover jumptable at 0x000a4284. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(unaff_EBP + 0x76))();
  return;
}


// ================================================================================================
// sub_a4288 @ 0xa4288 [__watcall]
// ================================================================================================

void __watcall sub_a4288(void)

{
  ushort uVar1;
  int unaff_EBP;
  int unaff_ESI;
  int unaff_EDI;
  uint uVar2;
  
  uVar2 = (uint)*(ushort *)(&unk_a3280 + unaff_EDI);
  uVar1 = *(ushort *)(&unk_a3282 + uVar2);
  *(ushort *)(unaff_EBP + 4) = *(ushort *)(unaff_EBP + 4) & 0xc7ff;
  *(ushort *)(unaff_EBP + 4) = *(ushort *)(unaff_EBP + 4) | uVar1;
  *(ushort *)(unaff_EBP + 8) = *(ushort *)(unaff_EBP + 8) & *(ushort *)(&unk_a32ce + uVar2);
  *(undefined4 *)(uVar2 + 0x1c + unaff_EBP) = *(undefined4 *)(unaff_ESI + 0x1c + unaff_EBP);
  *(undefined4 *)(uVar2 + 0x20 + unaff_EBP) = *(undefined4 *)(unaff_ESI + 0x20 + unaff_EBP);
  *(undefined2 *)(uVar2 + 0x24 + unaff_EBP) = *(undefined2 *)(unaff_ESI + 0x24 + unaff_EBP);
  sub_a3680();
  return;
}


// ================================================================================================
// sub_a42d0 @ 0xa42d0 [__watcall]
// ================================================================================================

void __watcall sub_a42d0(void)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined2 uVar3;
  undefined4 uVar4;
  int unaff_EBP;
  int unaff_ESI;
  int unaff_EDI;
  
  puVar1 = (undefined4 *)(unaff_EDI + 0x1c + unaff_EBP);
  puVar2 = (undefined4 *)(unaff_ESI + 0x1c + unaff_EBP);
  LOCK();
  uVar4 = *puVar1;
  *puVar1 = *puVar2;
  UNLOCK();
  *puVar2 = uVar4;
  LOCK();
  uVar4 = puVar1[1];
  puVar1[1] = puVar2[1];
  UNLOCK();
  puVar2[1] = uVar4;
  LOCK();
  uVar3 = *(undefined2 *)(puVar1 + 2);
  *(undefined2 *)(puVar1 + 2) = *(undefined2 *)(puVar2 + 2);
  UNLOCK();
  *(undefined2 *)(puVar2 + 2) = uVar3;
  sub_a3680();
  return;
}


// ================================================================================================
// sub_a42f8 @ 0xa42f8 [__watcall]
// ================================================================================================

void __watcall sub_a42f8(undefined4 param_1,undefined4 param_2,int unaff_EBX)

{
                    /* WARNING: Could not recover jumptable at 0x000a42f8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)(&PTR_LAB_000a4300)[unaff_EBX])();
  return;
}


// ================================================================================================
// sub_a4379 @ 0xa4379 [__watcall]
// ================================================================================================

void __watcall sub_a4379(undefined4 param_1,undefined4 param_2,int unaff_EBX)

{
                    /* WARNING: Could not recover jumptable at 0x000a4379. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(&DAT_000a4381 + unaff_EBX * 4))();
  return;
}


// ================================================================================================
// sub_a4594 @ 0xa4594 [__watcall]
// ================================================================================================

void __watcall sub_a4594(undefined4 param_1,undefined4 param_2,int unaff_EBX)

{
                    /* WARNING: Could not recover jumptable at 0x000a4594. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)(&PTR_LAB_000a459c)[unaff_EBX])();
  return;
}


// ================================================================================================
// sub_a469e @ 0xa469e [__watcall]
// ================================================================================================

void __watcall sub_a469e(undefined4 param_1,undefined4 param_2,int unaff_EBX)

{
                    /* WARNING: Could not recover jumptable at 0x000a469e. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(&DAT_000a46a6 + unaff_EBX * 4))();
  return;
}


// ================================================================================================
// sub_a47b6 @ 0xa47b6 [__watcall]
// ================================================================================================

void __watcall sub_a47b6(undefined4 param_1,undefined4 param_2,int unaff_EBX)

{
                    /* WARNING: Could not recover jumptable at 0x000a47b6. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(&DAT_000a47be + unaff_EBX * 4))();
  return;
}


// ================================================================================================
// sub_a483f @ 0xa483f [__watcall]
// ================================================================================================

void __watcall sub_a483f(undefined4 param_1,undefined4 param_2,int unaff_EBX)

{
                    /* WARNING: Could not recover jumptable at 0x000a483f. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(&DAT_000a4847 + unaff_EBX * 4))();
  return;
}


// ================================================================================================
// FUN_000a4873 @ 0xa4873
// ================================================================================================

void FUN_000a4873(void)

{
  undefined2 *unaff_EBP;
  
  *unaff_EBP = 0x33f;
  unaff_EBP[2] = 0;
  unaff_EBP[4] = 0xffff;
  *(code **)(unaff_EBP + 0x3b) = sub_a3680;
  sub_a3680();
  return;
}


// ================================================================================================
// sub_a4899 @ 0xa4899 [__watcall]
// ================================================================================================

void __watcall sub_a4899(void)

{
  int unaff_EBP;
  int unaff_ESI;
  int unaff_EDI;
  
  sub_a4da4(unaff_ESI + 0x1c + unaff_EBP,unaff_EDI + 0x1c + unaff_EBP,unaff_ESI + 0x1c + unaff_EBP);
                    /* WARNING: Could not recover jumptable at 0x000a48aa. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(unaff_EBP + 0x76))();
  return;
}


// ================================================================================================
// sub_a48ae @ 0xa48ae [__watcall]
// ================================================================================================

void __watcall sub_a48ae(void)

{
  int unaff_EBP;
  int unaff_ESI;
  int unaff_EDI;
  
  sub_a51d8(unaff_ESI + 0x1c + unaff_EBP,unaff_EDI + 0x1c + unaff_EBP,unaff_ESI + 0x1c + unaff_EBP);
                    /* WARNING: Could not recover jumptable at 0x000a48bf. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(unaff_EBP + 0x76))();
  return;
}


// ================================================================================================
// sub_a48c3 @ 0xa48c3 [__watcall]
// ================================================================================================

void __watcall sub_a48c3(void)

{
  int unaff_EBP;
  int unaff_ESI;
  int unaff_EDI;
  
  sub_a4d96(unaff_EDI + 0x1c + unaff_EBP,unaff_ESI + 0x1c + unaff_EBP,unaff_ESI + 0x1c + unaff_EBP);
                    /* WARNING: Could not recover jumptable at 0x000a48d4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(unaff_EBP + 0x76))();
  return;
}


// ================================================================================================
// sub_a48d8 @ 0xa48d8 [__watcall]
// ================================================================================================

void __watcall sub_a48d8(void)

{
  int unaff_EBP;
  int unaff_ESI;
  int unaff_EDI;
  
  sub_a4d96(unaff_ESI + 0x1c + unaff_EBP,unaff_EDI + 0x1c + unaff_EBP,unaff_ESI + 0x1c + unaff_EBP);
                    /* WARNING: Could not recover jumptable at 0x000a48e9. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(unaff_EBP + 0x76))();
  return;
}


// ================================================================================================
// sub_a48ed @ 0xa48ed [__watcall]
// ================================================================================================

void __watcall sub_a48ed(void)

{
  int unaff_EBP;
  int unaff_ESI;
  int unaff_EDI;
  
  sub_a5003(unaff_EDI + 0x1c + unaff_EBP,unaff_ESI + 0x1c + unaff_EBP,unaff_ESI + 0x1c + unaff_EBP);
                    /* WARNING: Could not recover jumptable at 0x000a48fe. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(unaff_EBP + 0x76))();
  return;
}


// ================================================================================================
// sub_a4902 @ 0xa4902 [__watcall]
// ================================================================================================

void __watcall sub_a4902(void)

{
  int unaff_EBP;
  int unaff_ESI;
  int unaff_EDI;
  
  sub_a5003(unaff_ESI + 0x1c + unaff_EBP,unaff_EDI + 0x1c + unaff_EBP,unaff_ESI + 0x1c + unaff_EBP);
                    /* WARNING: Could not recover jumptable at 0x000a4913. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(unaff_EBP + 0x76))();
  return;
}


// ================================================================================================
// sub_a4917 @ 0xa4917 [__watcall]
// ================================================================================================

void __watcall sub_a4917(void)

{
  int unaff_EBP;
  int unaff_ESI;
  
  *(ushort *)(unaff_EBP + 8) = *(ushort *)(unaff_EBP + 8) & *(ushort *)(&unk_a32ce + unaff_ESI);
  *(ushort *)(unaff_EBP + 8) = *(ushort *)(unaff_EBP + 8) | *(ushort *)(unk_a32d6 + unaff_ESI);
  sub_a3680();
  return;
}


// ================================================================================================
// sub_a4936 @ 0xa4936 [__watcall]
// ================================================================================================

void __watcall sub_a4936(void)

{
  int unaff_EBP;
  int unaff_ESI;
  int unaff_EDI;
  
  *(undefined4 *)(unaff_ESI + 0x1c + unaff_EBP) = *(undefined4 *)(unaff_EDI + 0x1c + unaff_EBP);
  *(undefined4 *)(unaff_ESI + 0x20 + unaff_EBP) = *(undefined4 *)(unaff_EDI + 0x20 + unaff_EBP);
  *(undefined2 *)(unaff_ESI + 0x24 + unaff_EBP) = *(undefined2 *)(unaff_EDI + 0x24 + unaff_EBP);
  *(ushort *)(unaff_EBP + 8) = *(ushort *)(unaff_EBP + 8) & *(ushort *)(&unk_a32ce + unaff_ESI);
  sub_a3680();
  return;
}


// ================================================================================================
// sub_a4962 @ 0xa4962 [__watcall]
// ================================================================================================

void __watcall sub_a4962(void)

{
  int unaff_EBP;
  int unaff_ESI;
  int unaff_EDI;
  
  sub_a4f6a(unaff_EDI + 0x1c + unaff_EBP,unaff_ESI + 0x1c + unaff_EBP);
  sub_a3874();
  return;
}


// ================================================================================================
// sub_a4974 @ 0xa4974 [__watcall]
// ================================================================================================

void __watcall sub_a4974(void)

{
  int unaff_EBP;
  int unaff_ESI;
  int unaff_EDI;
  
  sub_a4f6a(unaff_EDI + 0x1c + unaff_EBP,unaff_ESI + 0x1c + unaff_EBP);
  sub_a3822();
  return;
}


// ================================================================================================
// sub_a4986 @ 0xa4986 [__watcall]
// ================================================================================================

void __watcall sub_a4986(void)

{
  ushort uVar1;
  int unaff_EBP;
  int unaff_ESI;
  int unaff_EDI;
  
  *(undefined4 *)(unaff_ESI + 0x1c + unaff_EBP) = *(undefined4 *)(unaff_EDI + 0x1c + unaff_EBP);
  *(undefined4 *)(unaff_ESI + 0x20 + unaff_EBP) = *(undefined4 *)(unaff_EDI + 0x20 + unaff_EBP);
  *(undefined2 *)(unaff_ESI + 0x24 + unaff_EBP) = *(undefined2 *)(unaff_EDI + 0x24 + unaff_EBP);
  *(ushort *)(unaff_EBP + 8) = *(ushort *)(unaff_EBP + 8) & *(ushort *)(&unk_a32ce + unaff_ESI);
  *(ushort *)(unaff_EBP + 8) = *(ushort *)(unaff_EBP + 8) & *(ushort *)(&unk_a32ce + unaff_EDI);
  *(ushort *)(unaff_EBP + 8) = *(ushort *)(unaff_EBP + 8) | *(ushort *)(unk_a32d6 + unaff_EDI);
  uVar1 = *(ushort *)(&unk_a3282 + *(ushort *)(&unk_a327e + unaff_EDI));
  *(ushort *)(unaff_EBP + 4) = *(ushort *)(unaff_EBP + 4) & 0xc7ff;
  *(ushort *)(unaff_EBP + 4) = *(ushort *)(unaff_EBP + 4) | uVar1;
  sub_a3680();
  return;
}


// ================================================================================================
// sub_a49b2 @ 0xa49b2 [__watcall]
// ================================================================================================

void __watcall sub_a49b2(void)

{
  ushort uVar1;
  int unaff_EBP;
  int unaff_ESI;
  int unaff_EDI;
  
  sub_a4da4(unaff_ESI + 0x1c + unaff_EBP,unaff_EDI + 0x1c + unaff_EBP,unaff_ESI + 0x1c + unaff_EBP);
  *(ushort *)(unaff_EBP + 8) = *(ushort *)(unaff_EBP + 8) & *(ushort *)(&unk_a32ce + unaff_EDI);
  *(ushort *)(unaff_EBP + 8) = *(ushort *)(unaff_EBP + 8) | *(ushort *)(unk_a32d6 + unaff_EDI);
  uVar1 = *(ushort *)(&unk_a3282 + *(ushort *)(&unk_a327e + unaff_EDI));
  *(ushort *)(unaff_EBP + 4) = *(ushort *)(unaff_EBP + 4) & 0xc7ff;
  *(ushort *)(unaff_EBP + 4) = *(ushort *)(unaff_EBP + 4) | uVar1;
                    /* WARNING: Could not recover jumptable at 0x000a49f9. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(unaff_EBP + 0x76))();
  return;
}


// ================================================================================================
// sub_a49fd @ 0xa49fd [__watcall]
// ================================================================================================

void __watcall sub_a49fd(void)

{
  ushort uVar1;
  int unaff_EBP;
  int unaff_ESI;
  int unaff_EDI;
  
  sub_a51d8(unaff_ESI + 0x1c + unaff_EBP,unaff_EDI + 0x1c + unaff_EBP,unaff_ESI + 0x1c + unaff_EBP);
  *(ushort *)(unaff_EBP + 8) = *(ushort *)(unaff_EBP + 8) & *(ushort *)(&unk_a32ce + unaff_EDI);
  *(ushort *)(unaff_EBP + 8) = *(ushort *)(unaff_EBP + 8) | *(ushort *)(unk_a32d6 + unaff_EDI);
  uVar1 = *(ushort *)(&unk_a3282 + *(ushort *)(&unk_a327e + unaff_EDI));
  *(ushort *)(unaff_EBP + 4) = *(ushort *)(unaff_EBP + 4) & 0xc7ff;
  *(ushort *)(unaff_EBP + 4) = *(ushort *)(unaff_EBP + 4) | uVar1;
                    /* WARNING: Could not recover jumptable at 0x000a4a44. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(unaff_EBP + 0x76))();
  return;
}


// ================================================================================================
// sub_a4a48 @ 0xa4a48 [__watcall]
// ================================================================================================

void __watcall sub_a4a48(undefined4 param_1,undefined4 param_2,int unaff_EBX)

{
                    /* WARNING: Could not recover jumptable at 0x000a4a48. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)(&PTR_sub_a41b4_000a4a50)[unaff_EBX])();
  return;
}


// ================================================================================================
// sub_a4ad1 @ 0xa4ad1 [__watcall]
// ================================================================================================

void __watcall sub_a4ad1(void)

{
  ushort uVar1;
  int unaff_EBP;
  int unaff_ESI;
  int unaff_EDI;
  
  sub_a4d96(unaff_EDI + 0x1c + unaff_EBP,unaff_ESI + 0x1c + unaff_EBP,unaff_ESI + 0x1c + unaff_EBP);
  *(ushort *)(unaff_EBP + 8) = *(ushort *)(unaff_EBP + 8) & *(ushort *)(&unk_a32ce + unaff_EDI);
  *(ushort *)(unaff_EBP + 8) = *(ushort *)(unaff_EBP + 8) | *(ushort *)(unk_a32d6 + unaff_EDI);
  uVar1 = *(ushort *)(&unk_a3282 + *(ushort *)(&unk_a327e + unaff_EDI));
  *(ushort *)(unaff_EBP + 4) = *(ushort *)(unaff_EBP + 4) & 0xc7ff;
  *(ushort *)(unaff_EBP + 4) = *(ushort *)(unaff_EBP + 4) | uVar1;
                    /* WARNING: Could not recover jumptable at 0x000a4b18. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(unaff_EBP + 0x76))();
  return;
}


// ================================================================================================
// sub_a4b1c @ 0xa4b1c [__watcall]
// ================================================================================================

void __watcall sub_a4b1c(void)

{
  ushort uVar1;
  int unaff_EBP;
  int unaff_ESI;
  int unaff_EDI;
  
  sub_a4d96(unaff_ESI + 0x1c + unaff_EBP,unaff_EDI + 0x1c + unaff_EBP,unaff_ESI + 0x1c + unaff_EBP);
  *(ushort *)(unaff_EBP + 8) = *(ushort *)(unaff_EBP + 8) & *(ushort *)(&unk_a32ce + unaff_EDI);
  *(ushort *)(unaff_EBP + 8) = *(ushort *)(unaff_EBP + 8) | *(ushort *)(unk_a32d6 + unaff_EDI);
  uVar1 = *(ushort *)(&unk_a3282 + *(ushort *)(&unk_a327e + unaff_EDI));
  *(ushort *)(unaff_EBP + 4) = *(ushort *)(unaff_EBP + 4) & 0xc7ff;
  *(ushort *)(unaff_EBP + 4) = *(ushort *)(unaff_EBP + 4) | uVar1;
                    /* WARNING: Could not recover jumptable at 0x000a4b63. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(unaff_EBP + 0x76))();
  return;
}


// ================================================================================================
// sub_a4b67 @ 0xa4b67 [__watcall]
// ================================================================================================

void __watcall sub_a4b67(void)

{
  ushort uVar1;
  int unaff_EBP;
  int unaff_ESI;
  int unaff_EDI;
  
  sub_a5003(unaff_EDI + 0x1c + unaff_EBP,unaff_ESI + 0x1c + unaff_EBP,unaff_ESI + 0x1c + unaff_EBP);
  *(ushort *)(unaff_EBP + 8) = *(ushort *)(unaff_EBP + 8) & *(ushort *)(&unk_a32ce + unaff_EDI);
  *(ushort *)(unaff_EBP + 8) = *(ushort *)(unaff_EBP + 8) | *(ushort *)(unk_a32d6 + unaff_EDI);
  uVar1 = *(ushort *)(&unk_a3282 + *(ushort *)(&unk_a327e + unaff_EDI));
  *(ushort *)(unaff_EBP + 4) = *(ushort *)(unaff_EBP + 4) & 0xc7ff;
  *(ushort *)(unaff_EBP + 4) = *(ushort *)(unaff_EBP + 4) | uVar1;
                    /* WARNING: Could not recover jumptable at 0x000a4bae. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(unaff_EBP + 0x76))();
  return;
}


// ================================================================================================
// sub_a4bb2 @ 0xa4bb2 [__watcall]
// ================================================================================================

void __watcall sub_a4bb2(void)

{
  ushort uVar1;
  int unaff_EBP;
  int unaff_ESI;
  int unaff_EDI;
  
  sub_a5003(unaff_ESI + 0x1c + unaff_EBP,unaff_EDI + 0x1c + unaff_EBP,unaff_ESI + 0x1c + unaff_EBP);
  *(ushort *)(unaff_EBP + 8) = *(ushort *)(unaff_EBP + 8) & *(ushort *)(&unk_a32ce + unaff_EDI);
  *(ushort *)(unaff_EBP + 8) = *(ushort *)(unaff_EBP + 8) | *(ushort *)(unk_a32d6 + unaff_EDI);
  uVar1 = *(ushort *)(&unk_a3282 + *(ushort *)(&unk_a327e + unaff_EDI));
  *(ushort *)(unaff_EBP + 4) = *(ushort *)(unaff_EBP + 4) & 0xc7ff;
  *(ushort *)(unaff_EBP + 4) = *(ushort *)(unaff_EBP + 4) | uVar1;
                    /* WARNING: Could not recover jumptable at 0x000a4bf9. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(unaff_EBP + 0x76))();
  return;
}


// ================================================================================================
// sub_a4bfd @ 0xa4bfd [__watcall]
// ================================================================================================

void __watcall sub_a4bfd(undefined4 param_1,undefined4 param_2,int unaff_EBX)

{
                    /* WARNING: Could not recover jumptable at 0x000a4bfd. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(&DAT_000a4c05 + unaff_EBX * 4))();
  return;
}


// ================================================================================================
// sub_a4d96 @ 0xa4d96 [__watcall]
// ================================================================================================

void __watcall
sub_a4d96(undefined4 *param_1,undefined4 *unaff_EDX,undefined8 *unaff_EBX,undefined4 unaff_ECX)

{
  undefined2 uVar1;
  undefined8 uVar2;
  
  uVar1 = *(undefined2 *)(param_1 + 2);
  uVar2 = sub_a4dfe(*param_1,param_1[1],*unaff_EDX,unaff_EDX[1],unaff_EBX,unaff_ECX);
  *unaff_EBX = uVar2;
  *(undefined2 *)(unaff_EBX + 1) = uVar1;
  return;
}


// ================================================================================================
// sub_a4da4 @ 0xa4da4 [__watcall]
// ================================================================================================

void __watcall
sub_a4da4(undefined4 *param_1,undefined4 *unaff_EDX,undefined8 *unaff_EBX,undefined4 unaff_ECX)

{
  undefined2 uVar1;
  undefined8 uVar2;
  
  uVar1 = *(undefined2 *)(param_1 + 2);
  uVar2 = sub_a4dfe(*param_1,param_1[1],*unaff_EDX,unaff_EDX[1],unaff_EBX,unaff_ECX);
  *unaff_EBX = uVar2;
  *(undefined2 *)(unaff_EBX + 1) = uVar1;
  return;
}


// ================================================================================================
// sub_a4dce @ 0xa4dce [__watcall]
// ================================================================================================

void __watcall
sub_a4dce(undefined4 *param_1,undefined4 param_2,undefined8 *unaff_EBX,undefined4 unaff_ECX,
         undefined4 param_5,undefined4 param_6)

{
  undefined2 uVar1;
  undefined8 uVar2;
  
  uVar1 = *(undefined2 *)(param_1 + 2);
  uVar2 = sub_a4dfe(*param_1,param_1[1],param_5,param_6,unaff_EBX,unaff_ECX);
  *unaff_EBX = uVar2;
  *(undefined2 *)(unaff_EBX + 1) = uVar1;
  return;
}


// ================================================================================================
// sub_a4dfe @ 0xa4dfe [__watcall]
// ================================================================================================

undefined8 __watcall sub_a4dfe(uint param_1,uint unaff_EDX,uint unaff_EBX,uint unaff_ECX)

{
  uint uVar1;
  byte bVar2;
  short sVar3;
  ushort uVar4;
  short sVar5;
  byte bVar8;
  uint uVar6;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  ushort uVar12;
  uint unaff_ESI;
  uint uVar13;
  bool bVar14;
  bool bVar15;
  bool bVar16;
  int iVar7;
  
  if ((param_1 == 0) && (unaff_EDX == 0)) {
    uVar4 = (ushort)unaff_ESI;
    if ((unaff_ESI & 0x7fff) == 0) {
      return CONCAT44(unaff_ECX,unaff_EBX);
    }
    unaff_ESI = CONCAT22((short)(unaff_ESI >> 0x10),
                         uVar4 & 0x7fff | (ushort)CARRY2(uVar4,uVar4) << 0xf);
  }
  if (((unaff_ECX == 0) && (unaff_EBX == 0)) && ((unaff_ESI & 0x7fff0000) == 0)) {
    return CONCAT44(unaff_EDX,param_1);
  }
  uVar6 = (int)unaff_ESI >> 0x10 & 0x80007fff;
  sVar3 = (short)(uVar6 >> 0x10) + ((short)unaff_ESI >> 0xf & 0x8000U);
  uVar13 = (int)(unaff_ESI << 0x10 | unaff_ESI >> 0x10) >> 0x10 & 0x7fff;
  uVar4 = (ushort)(unaff_ESI >> 0x10) & 0x7fff;
  uVar12 = (ushort)uVar13;
  sVar5 = uVar4 - uVar12;
  iVar7 = CONCAT22(sVar3,sVar5);
  uVar9 = param_1;
  uVar10 = unaff_EDX;
  if (sVar5 != 0) {
    if (uVar4 < uVar12) {
      iVar7 = CONCAT22(sVar3,-sVar5);
      uVar9 = unaff_EBX;
      uVar10 = unaff_ECX;
      unaff_EBX = param_1;
      uVar6 = uVar13;
      unaff_ECX = unaff_EDX;
    }
    if (0x40 < (ushort)iVar7) {
      return CONCAT44(unaff_ECX,unaff_EBX);
    }
  }
  uVar4 = (ushort)iVar7 & 0xff;
  if (iVar7 < 0) {
    uVar4 = CONCAT11(0xff,(char)iVar7);
    bVar14 = unaff_EBX != 0;
    unaff_EBX = -unaff_EBX;
    unaff_ECX = -(uint)bVar14 - unaff_ECX;
  }
  uVar12 = (ushort)uVar6;
  uVar13 = 0;
  bVar2 = (byte)uVar4;
  if (bVar2 != 0) {
    if (0x1f < bVar2) {
      uVar13 = (uint)(uVar9 != 0);
      uVar9 = uVar10;
      if (bVar2 == 0x40) {
        uVar13 = uVar13 | uVar10;
        uVar9 = 0;
      }
      uVar10 = 0;
    }
    uVar13 = uVar13 | 0U >> (bVar2 & 0x1f) | uVar9 << 0x20 - (bVar2 & 0x1f);
    uVar9 = uVar9 >> (bVar2 & 0x1f) | uVar10 << 0x20 - (bVar2 & 0x1f);
    uVar10 = uVar10 >> (bVar2 & 0x1f) | 0 << 0x20 - (bVar2 & 0x1f);
  }
  uVar1 = uVar9 + unaff_EBX;
  uVar11 = uVar10 + unaff_ECX + (uint)CARRY4(uVar9,unaff_EBX);
  bVar8 = (char)(uVar4 >> 8) +
          (CARRY4(uVar10,unaff_ECX) || CARRY4(uVar10 + unaff_ECX,(uint)CARRY4(uVar9,unaff_EBX)));
  if ((char)bVar8 < '\0') {
    if (bVar2 == 0x40) {
      uVar9 = (uint)((uVar13 & 0x7fffffff) != 0);
      bVar14 = CARRY4(uVar1,uVar9);
      uVar1 = uVar1 + uVar9;
      uVar11 = uVar11 + bVar14;
    }
    bVar14 = uVar1 != 0;
    uVar1 = -uVar1;
    uVar11 = -(uint)bVar14 - uVar11;
    bVar8 = 0;
  }
  if ((CONCAT31((int3)(uVar1 >> 8),(byte)uVar1 | bVar8) == 0 && uVar11 == 0) ||
     (uVar6 = uVar6 & 0xffff, uVar12 == 0)) goto LAB_000a4f53;
  if (bVar8 == 0) {
    bVar14 = (int)uVar13 < 0;
    uVar13 = uVar13 & 0x7fffffff | (uint)bVar14 << 0x1f;
    do {
      uVar12 = (short)uVar6 - 1;
      uVar6 = (uint)uVar12;
      if (uVar12 == 0) goto LAB_000a4f53;
      bVar15 = CARRY4(uVar1,uVar1);
      uVar9 = uVar1 * 2;
      uVar1 = uVar9 + bVar14;
      uVar9 = (uint)(bVar15 || CARRY4(uVar9,(uint)bVar14));
      bVar16 = CARRY4(uVar11,uVar11);
      bVar15 = CARRY4(uVar11 * 2,uVar9);
      bVar14 = bVar16 || bVar15;
      uVar11 = uVar11 * 2 + uVar9;
    } while (!bVar16 && !bVar15);
  }
  if (uVar12 != 0x7ffe) {
    uVar9 = uVar11 & 1;
    uVar11 = uVar11 >> 1 | 0x80000000;
    uVar10 = uVar1 & 1;
    uVar6 = uVar1 >> 1;
    uVar9 = (uint)(uVar9 != 0) << 0x1f;
    uVar1 = uVar6 | uVar9;
    if (uVar10 == 0) goto LAB_000a4f53;
    bVar14 = CARRY4(uVar13,uVar13);
    if ((uVar13 & 0x7fffffff) == 0) {
      bVar14 = (uVar6 & 1) != 0;
      uVar1 = uVar6 & 0xfffffffe | uVar9 | (uint)bVar14;
    }
    bVar15 = CARRY4(uVar1,(uint)bVar14);
    uVar1 = uVar1 + bVar14;
    uVar13 = (uint)bVar15;
    bVar14 = CARRY4(uVar11,uVar13);
    uVar11 = uVar11 + uVar13;
    if (!bVar14) goto LAB_000a4f53;
    uVar13 = uVar11 & 1;
    uVar11 = uVar11 >> 1 | (uint)bVar14 << 0x1f;
    uVar1 = uVar1 >> 1 | (uint)(uVar13 != 0) << 0x1f;
    if (uVar12 != 0x7ffd) goto LAB_000a4f53;
  }
  uVar1 = 0;
  uVar11 = 0x80000000;
LAB_000a4f53:
  return CONCAT44(uVar11,uVar1);
}


// ================================================================================================
// sub_a4f6a @ 0xa4f6a [__watcall]
// ================================================================================================

int __watcall sub_a4f6a(uint *param_1,uint *unaff_EDX)

{
  ushort uVar1;
  uint uVar2;
  bool bVar3;
  bool bVar4;
  
  if ((((*(ushort *)(param_1 + 2) | 0x8000) == 0xffff) &&
      ((param_1[1] & 0x7fffffff) != 0 || *param_1 != 0)) ||
     (((*(ushort *)(unaff_EDX + 2) | 0x8000) == 0xffff &&
      ((unaff_EDX[1] & 0x7fffffff) != 0 || *unaff_EDX != 0)))) {
    return 2;
  }
  uVar2 = *(uint *)((int)param_1 + 6);
  if ((int)(*(uint *)((int)unaff_EDX + 6) ^ uVar2) < 0) {
    if ((CONCAT22(*(undefined2 *)(param_1 + 2),*(undefined2 *)(unaff_EDX + 2)) & 0x7fff7fff) == 0 &&
        (((*param_1 == 0 && *unaff_EDX == 0) && param_1[1] == 0) && unaff_EDX[1] == 0)) {
      return 0;
    }
  }
  else {
    uVar1 = *(ushort *)(param_1 + 2);
    bVar3 = uVar1 < *(ushort *)(unaff_EDX + 2);
    bVar4 = uVar1 == *(ushort *)(unaff_EDX + 2);
    if (bVar4) {
      bVar3 = param_1[1] < unaff_EDX[1];
      bVar4 = param_1[1] == unaff_EDX[1];
      if (bVar4) {
        bVar3 = *param_1 < *unaff_EDX;
        bVar4 = *param_1 == *unaff_EDX;
      }
    }
    if (bVar4) {
      return 0;
    }
    uVar2 = CONCAT22((short)(uVar2 >> 0x10),uVar1) ^ ((uint)param_1 >> 1 | (uint)bVar3 << 0x1f);
  }
  return (uint)CARRY4(uVar2,uVar2) * -2 + 1;
}


// ================================================================================================
// sub_a5003 @ 0xa5003 [__watcall]
// ================================================================================================

void __watcall
sub_a5003(undefined4 *param_1,undefined4 *unaff_EDX,undefined8 *unaff_EBX,undefined4 unaff_ECX)

{
  undefined2 uVar1;
  undefined8 uVar2;
  
  uVar1 = *(undefined2 *)(param_1 + 2);
  uVar2 = sub_a502d(*param_1,param_1[1],*unaff_EDX,unaff_EDX[1],unaff_EBX,unaff_ECX);
  *unaff_EBX = uVar2;
  *(undefined2 *)(unaff_EBX + 1) = uVar1;
  return;
}


// ================================================================================================
// sub_a502d @ 0xa502d [__watcall]
// ================================================================================================

longlong __watcall sub_a502d(uint param_1,uint unaff_EDX,uint unaff_EBX,uint unaff_ECX)

{
  uint uVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  longlong lVar4;
  int iVar5;
  uint uVar6;
  ushort uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint unaff_ESI;
  undefined2 uVar13;
  uint uVar11;
  uint uVar12;
  byte bVar14;
  ushort uVar15;
  ushort uVar16;
  bool bVar17;
  bool bVar18;
  bool bVar19;
  undefined4 local_20;
  undefined4 local_1c;
  
  uVar13 = (undefined2)(unaff_ESI >> 0x10);
  uVar7 = (ushort)unaff_ESI;
  if (((unaff_ECX == 0) && (unaff_EBX == 0)) && ((unaff_ESI & 0x7fff0000) == 0)) {
    if (((param_1 == 0) && (unaff_EDX == 0)) && ((unaff_ESI & 0x7fff) == 0)) {
      sub_a3890(CONCAT22(uVar13,0x8101));
      uVar10 = 0xc0000000;
    }
    else {
      sub_a3890(0x8304);
      uVar10 = 0x80000000;
    }
    return (ulonglong)uVar10 << 0x20;
  }
  if ((param_1 == 0) && (unaff_EDX == 0)) {
    if ((unaff_ESI & 0x7fff) == 0) {
      return 0;
    }
    unaff_ESI = CONCAT22(uVar13,uVar7 & 0x7fff | (ushort)CARRY2(uVar7,uVar7) << 0xf);
  }
  uVar7 = (ushort)(unaff_ESI >> 0x10) & 0x7fff;
  uVar10 = (int)(unaff_ESI << 0x10 | unaff_ESI >> 0x10) >> 0x10 & 0x7fff;
  uVar15 = (ushort)uVar10;
  if (uVar15 == 0) {
    do {
      bVar17 = CARRY4(param_1,param_1);
      param_1 = param_1 * 2;
      unaff_EDX = unaff_EDX * 2 + (uint)bVar17;
      uVar15 = (short)uVar10 - 1;
      uVar10 = (uint)uVar15;
    } while (-1 < (int)unaff_EDX);
  }
  if ((unaff_ESI & 0x7fff0000) == 0) {
    do {
      bVar17 = CARRY4(unaff_EBX,unaff_EBX);
      unaff_EBX = unaff_EBX * 2;
      unaff_ECX = unaff_ECX * 2 + (uint)bVar17;
      uVar7 = uVar7 - 1;
    } while (-1 < (int)unaff_ECX);
  }
  uVar16 = (uVar15 - uVar7) + 0x3fff;
  if (((short)uVar16 < 0) || (uVar16 < 0x7fff)) {
    if ((short)uVar16 < -0x40) {
      local_20 = 0;
      local_1c = 0;
    }
    else {
      uVar10 = unaff_EDX;
      if (unaff_ECX <= unaff_EDX) {
        uVar10 = unaff_EDX - unaff_ECX;
      }
      bVar17 = unaff_ECX <= unaff_EDX;
      uVar2 = CONCAT44(uVar10,param_1) / (ulonglong)unaff_ECX;
      local_1c = (uint)uVar2;
      uVar3 = (ulonglong)unaff_EBX * (uVar2 & 0xffffffff);
      iVar5 = (int)uVar3;
      lVar4 = (ulonglong)unaff_ECX * (uVar2 & 0xffffffff) + (uVar3 >> 0x20);
      if (bVar17) {
        lVar4 = lVar4 + CONCAT44(unaff_ECX,unaff_EBX);
      }
      uVar8 = -iVar5;
      uVar10 = (uint)(iVar5 != 0);
      uVar1 = param_1 - (uint)lVar4;
      uVar11 = uVar1 - uVar10;
      for (iVar5 = (unaff_EDX - (int)((ulonglong)lVar4 >> 0x20)) -
                   (uint)(param_1 < (uint)lVar4 || uVar1 < uVar10); iVar5 != 0;
          iVar5 = iVar5 + (uint)(bVar19 || CARRY4(uVar10,(uint)bVar18))) {
        bVar18 = local_1c == 0;
        local_1c = local_1c - 1;
        bVar17 = (bool)(bVar17 ^ bVar18);
        bVar18 = CARRY4(uVar8,unaff_EBX);
        uVar8 = uVar8 + unaff_EBX;
        bVar19 = CARRY4(uVar11,unaff_ECX);
        uVar10 = uVar11 + unaff_ECX;
        uVar11 = uVar10 + bVar18;
      }
      if (unaff_ECX <= uVar11) {
        uVar11 = uVar11 - unaff_ECX;
        bVar18 = 0xfffffffe < local_1c;
        local_1c = local_1c + 1;
        bVar17 = (bool)(bVar17 ^ bVar18);
      }
      uVar2 = CONCAT44(uVar11,uVar8) / (ulonglong)unaff_ECX;
      local_20 = (uint)uVar2;
      if (local_20 != 0) {
        uVar3 = (ulonglong)unaff_EBX * (uVar2 & 0xffffffff);
        iVar5 = (int)uVar3;
        lVar4 = (ulonglong)unaff_ECX * (uVar2 & 0xffffffff) + (uVar3 >> 0x20);
        uVar6 = (uint)lVar4;
        uVar9 = -iVar5;
        uVar10 = (uint)(iVar5 != 0);
        uVar1 = uVar8 - uVar6;
        uVar12 = uVar1 - uVar10;
        for (iVar5 = (uVar11 - (int)((ulonglong)lVar4 >> 0x20)) -
                     (uint)(uVar8 < uVar6 || uVar1 < uVar10); iVar5 != 0;
            iVar5 = iVar5 + (uint)(bVar19 || CARRY4(uVar10,(uint)bVar18))) {
          bVar19 = local_20 == 0;
          local_20 = local_20 - 1;
          bVar18 = local_1c < bVar19;
          local_1c = local_1c - bVar19;
          bVar17 = (bool)(bVar17 ^ bVar18);
          bVar18 = CARRY4(uVar9,unaff_EBX);
          uVar9 = uVar9 + unaff_EBX;
          bVar19 = CARRY4(uVar12,unaff_ECX);
          uVar10 = uVar12 + unaff_ECX;
          uVar12 = uVar10 + bVar18;
        }
      }
      uVar7 = (uVar15 - uVar7) + 0x3ffe;
      if (bVar17) {
        uVar10 = local_1c & 1;
        local_1c = local_1c >> 1 | (uint)bVar17 << 0x1f;
        local_20 = local_20 >> 1 | (uint)(uVar10 != 0) << 0x1f;
        uVar7 = uVar16;
      }
      if ((short)uVar7 < 1) {
        if (uVar7 == 0) {
          bVar14 = 1;
        }
        else {
          bVar14 = -(char)uVar7;
        }
        local_20 = local_20 >> (bVar14 & 0x1f) | local_1c << 0x20 - (bVar14 & 0x1f);
        local_1c = local_1c >> (bVar14 & 0x1f) | 0 << 0x20 - (bVar14 & 0x1f);
      }
    }
  }
  else {
    local_1c = 0x80000000;
    local_20 = 0;
  }
  return CONCAT44(local_1c,local_20);
}


// ================================================================================================
// sub_a51d8 @ 0xa51d8 [__watcall]
// ================================================================================================

void __watcall
sub_a51d8(undefined4 *param_1,undefined4 *unaff_EDX,undefined8 *unaff_EBX,undefined4 unaff_ECX)

{
  undefined2 uVar1;
  undefined8 uVar2;
  
  uVar1 = *(undefined2 *)(param_1 + 2);
  uVar2 = sub_a5202(*param_1,param_1[1],*unaff_EDX,unaff_EDX[1],unaff_EBX,unaff_ECX);
  *unaff_EBX = uVar2;
  *(undefined2 *)(unaff_EBX + 1) = uVar1;
  return;
}


// ================================================================================================
// sub_a5202 @ 0xa5202 [__watcall]
// ================================================================================================

ulonglong __watcall sub_a5202(uint param_1,uint unaff_EDX,uint unaff_EBX,uint unaff_ECX)

{
  longlong lVar1;
  ulonglong uVar2;
  longlong lVar3;
  ulonglong uVar4;
  uint uVar5;
  byte bVar6;
  ushort uVar7;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint unaff_ESI;
  uint uVar13;
  bool bVar14;
  ushort uVar8;
  
  if ((param_1 == 0) && (unaff_EDX == 0)) {
    uVar8 = (ushort)unaff_ESI;
    if ((unaff_ESI & 0x7fff) == 0) {
      return 0;
    }
    unaff_ESI = CONCAT22((short)(unaff_ESI >> 0x10),
                         uVar8 & 0x7fff | (ushort)CARRY2(uVar8,uVar8) << 0xf);
  }
  if (((unaff_ECX == 0) && (unaff_EBX == 0)) && ((unaff_ESI & 0x7fff0000) == 0)) {
    return 0;
  }
  uVar8 = (ushort)(((int)unaff_ESI >> 0x10 & 0x80007fffU) +
                  ((int)(unaff_ESI << 0x10 | unaff_ESI >> 0x10) >> 0x10 & 0x80007fffU));
  uVar7 = uVar8 + 0xc002;
  if ((uVar8 < 0x3ffe) || (uVar7 < 0x7fff)) {
    if ((short)uVar7 < -0x40) {
      return 0;
    }
    uVar11 = (uint)((ulonglong)param_1 * (ulonglong)unaff_EBX >> 0x20);
    lVar1 = (ulonglong)unaff_ECX * (ulonglong)param_1;
    lVar3 = lVar1 + (ulonglong)uVar11;
    uVar9 = (uint)lVar3;
    uVar13 = (uint)((ulonglong)lVar3 >> 0x20);
    uVar12 = (uint)((ulonglong)unaff_EBX * (ulonglong)unaff_EDX >> 0x20);
    uVar5 = (uint)((ulonglong)unaff_EBX * (ulonglong)unaff_EDX);
    uVar10 = uVar9 + uVar5;
    uVar5 = (uint)CARRY4(uVar9,uVar5);
    uVar9 = uVar13 + uVar12;
    uVar2 = (ulonglong)unaff_EDX * (ulonglong)unaff_ECX +
            CONCAT44((uint)CARRY4((uint)((ulonglong)lVar1 >> 0x20),(uint)CARRY4(uVar11,(uint)lVar1))
                     + (uint)(CARRY4(uVar13,uVar12) || CARRY4(uVar9,uVar5)),uVar9 + uVar5);
    uVar5 = (uint)uVar2;
    if (-1 < (longlong)uVar2) {
      bVar14 = CARRY4(uVar10,uVar10);
      uVar10 = uVar10 * 2;
      uVar2 = CONCAT44((int)(uVar2 >> 0x20) * 2 +
                       (uint)(CARRY4(uVar5,uVar5) || CARRY4(uVar5 * 2,(uint)bVar14)),
                       uVar5 * 2 + (uint)bVar14);
      uVar7 = uVar8 + 0xc001;
    }
    bVar14 = CARRY4(uVar10,uVar10);
    if (bVar14) {
      if (((uVar10 & 0x7fffffff) == 0) &&
         (bVar14 = (int)((ulonglong)param_1 * (ulonglong)unaff_EBX) != 0, !bVar14)) {
        bVar14 = (uVar2 & 1) != 0;
      }
      uVar5 = (uint)bVar14;
      uVar4 = uVar2 + uVar5;
      bVar14 = CARRY4((uint)(uVar2 >> 0x20),(uint)CARRY4((uint)uVar2,uVar5));
      uVar2 = uVar2 + uVar5;
      if (bVar14) {
        uVar2 = CONCAT44((uint)(uVar4 >> 0x21) | (uint)bVar14 << 0x1f,
                         (uint)uVar4 >> 1 | (uint)((uVar4 & 0x100000000) != 0) << 0x1f);
        uVar7 = uVar7 + 1;
        if (uVar7 == 0x7fff) goto LAB_000a52f1;
      }
    }
    uVar5 = (uint)(uVar2 >> 0x20);
    if ((short)uVar7 < 1) {
      if (uVar7 == 0) {
        bVar6 = 1;
      }
      else {
        bVar6 = -(char)uVar7;
      }
      uVar2 = CONCAT44(uVar5 >> (bVar6 & 0x1f) | 0 << 0x20 - (bVar6 & 0x1f),
                       (uint)uVar2 >> (bVar6 & 0x1f) | uVar5 << 0x20 - (bVar6 & 0x1f));
    }
  }
  else {
LAB_000a52f1:
    uVar2 = 0x8000000000000000;
  }
  return uVar2;
}


// ================================================================================================
// sub_a52fe @ 0xa52fe [__watcall]
// ================================================================================================

int __watcall sub_a52fe(uint *param_1)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  short sVar4;
  byte bVar5;
  byte bVar6;
  uint uVar7;
  bool bVar8;
  
  sVar4 = (*(ushort *)(param_1 + 2) & 0x7fff) + 0xc002;
  if ((*(ushort *)(param_1 + 2) & 0x7fff) < 0x3ffe) {
    return 0;
  }
  if (sVar4 < 0x21) {
    uVar7 = CONCAT11(*(byte *)((int)param_1 + 9) >> 1 | 0xa0,0xa0) & 0xffffff3f;
    bVar6 = (byte)sVar4;
    if ((char)bVar6 <= (char)uVar7) {
      uVar2 = param_1[1];
      bVar1 = (byte)(uVar7 >> 8) >> 1;
      bVar5 = bVar1 | CARRY4(*param_1,*param_1) << 7;
      if (bVar6 == 0x20) {
        bVar8 = CARRY1(bVar5,bVar5);
        uVar7 = uVar2;
      }
      else {
        uVar7 = 0 << (bVar6 & 0x1f) | uVar2 >> 0x20 - (bVar6 & 0x1f);
        uVar2 = uVar2 << (bVar6 & 0x1f);
        bVar8 = CARRY4(uVar2,uVar2);
      }
      bVar6 = bVar1 * '\x02' & (bVar8 << 7 | 0x7fU);
      iVar3 = uVar7 + CARRY1(bVar6,bVar6);
      if (CARRY1(bVar6 * '\x02',bVar6 * '\x02')) {
        iVar3 = -iVar3;
      }
      return iVar3;
    }
  }
  return -0x80000000;
}


// ================================================================================================
// sub_a5303 @ 0xa5303 [__watcall]
// ================================================================================================

uint __watcall sub_a5303(int *param_1)

{
  byte bVar1;
  byte bVar2;
  uint uVar3;
  ushort uVar4;
  short sVar5;
  
  bVar1 = *(byte *)((int)param_1 + 9);
  uVar4 = *(ushort *)(param_1 + 2) & 0x7fff;
  if (uVar4 == 0) {
    uVar3 = 0;
  }
  else {
    sVar5 = uVar4 + 0xc002;
    if (sVar5 == 0 || uVar4 < 0x3ffe) {
      uVar3 = -(uint)CARRY1(bVar1,bVar1);
    }
    else if (sVar5 < 0x20) {
      bVar2 = (byte)sVar5 & 0x1f;
      uVar3 = 0 << bVar2 | (uint)param_1[1] >> 0x20 - bVar2;
      if (CARRY1(bVar1,bVar1)) {
        if (*param_1 != 0 || param_1[1] << ((byte)sVar5 & 0x1f) != 0) {
          uVar3 = uVar3 + 1;
        }
        uVar3 = -uVar3;
      }
    }
    else {
      uVar3 = 0x80000000;
    }
  }
  return uVar3;
}


// ================================================================================================
// sub_a5353 @ 0xa5353 [__watcall]
// ================================================================================================

int __watcall sub_a5353(int param_1)

{
  byte bVar1;
  int iVar2;
  byte bVar3;
  ushort uVar4;
  short sVar5;
  uint uVar6;
  
  uVar4 = *(ushort *)(param_1 + 8) & 0x7fff;
  sVar5 = uVar4 + 0xc002;
  if (uVar4 < 0x3ffe) {
    return 0;
  }
  if ((sVar5 < 0x21) && (bVar3 = (byte)sVar5, (char)bVar3 < ' ')) {
    uVar6 = *(uint *)(param_1 + 4);
    bVar1 = (byte)(*(byte *)(param_1 + 9) >> 1 | 0x1f) >> 1;
    if (bVar3 != 0x20) {
      uVar6 = 0 << (bVar3 & 0x1f) | uVar6 >> 0x20 - (bVar3 & 0x1f);
    }
    bVar3 = bVar1 * '\x02';
    bVar1 = bVar1 << 2;
    iVar2 = uVar6 + CARRY1(bVar3,bVar3);
    if (CARRY1(bVar1,bVar1)) {
      iVar2 = -iVar2;
    }
    return iVar2;
  }
  return -0x80000000;
}


// ================================================================================================
// sub_a5358 @ 0xa5358 [__watcall]
// ================================================================================================

int __watcall sub_a5358(int param_1)

{
  byte bVar1;
  int iVar2;
  byte bVar3;
  ushort uVar4;
  short sVar5;
  uint uVar6;
  
  uVar4 = *(ushort *)(param_1 + 8) & 0x7fff;
  sVar5 = uVar4 + 0xc002;
  if (uVar4 < 0x3ffe) {
    return 0;
  }
  if ((sVar5 < 0x21) && (bVar3 = (byte)sVar5, (char)bVar3 < '!')) {
    uVar6 = *(uint *)(param_1 + 4);
    bVar1 = (byte)(*(byte *)(param_1 + 9) >> 1 | 0x20) >> 1;
    if (bVar3 != 0x20) {
      uVar6 = 0 << (bVar3 & 0x1f) | uVar6 >> 0x20 - (bVar3 & 0x1f);
    }
    bVar3 = bVar1 * '\x02';
    bVar1 = bVar1 << 2;
    iVar2 = uVar6 + CARRY1(bVar3,bVar3);
    if (CARRY1(bVar1,bVar1)) {
      iVar2 = -iVar2;
    }
    return iVar2;
  }
  return -0x80000000;
}


// ================================================================================================
// sub_a53c2 @ 0xa53c2 [__watcall]
// ================================================================================================

void __watcall sub_a53c2(uint param_1,undefined4 *unaff_EDX)

{
  int iVar1;
  int iVar2;
  short sVar3;
  
  if ((int)param_1 < 0) {
    param_1 = -param_1;
    sVar3 = -0x4001;
  }
  else {
    sVar3 = 0x3fff;
  }
  if (param_1 == 0) {
    iVar2 = 0;
    sVar3 = 0;
  }
  else {
    iVar1 = 0x1f;
    if (param_1 != 0) {
      for (; param_1 >> iVar1 == 0; iVar1 = iVar1 + -1) {
      }
    }
    iVar2 = param_1 << (0x1fU - (char)iVar1 & 0x1f);
    sVar3 = ((ushort)iVar1 & 0xff) + sVar3;
  }
  *unaff_EDX = 0;
  unaff_EDX[1] = iVar2;
  *(short *)(unaff_EDX + 2) = sVar3;
  return;
}


// ================================================================================================
// sub_a53d3 @ 0xa53d3 [__watcall]
// ================================================================================================

void __watcall sub_a53d3(uint param_1,undefined4 *unaff_EDX)

{
  int iVar1;
  int iVar2;
  short sVar3;
  
  if (param_1 == 0) {
    iVar2 = 0;
    sVar3 = 0;
  }
  else {
    iVar1 = 0x1f;
    if (param_1 != 0) {
      for (; param_1 >> iVar1 == 0; iVar1 = iVar1 + -1) {
      }
    }
    iVar2 = param_1 << (0x1fU - (char)iVar1 & 0x1f);
    sVar3 = ((ushort)iVar1 & 0xff) + 0x3fff;
  }
  *unaff_EDX = 0;
  unaff_EDX[1] = iVar2;
  *(short *)(unaff_EDX + 2) = sVar3;
  return;
}


// ================================================================================================
// sub_a5408 @ 0xa5408 [__watcall]
// ================================================================================================

void __watcall sub_a5408(uint param_1,int unaff_EDX,uint *unaff_EBX)

{
  uint uVar1;
  uint uVar2;
  ushort uVar3;
  undefined2 uVar5;
  uint uVar4;
  uint uVar6;
  uint extraout_EDX;
  bool bVar7;
  
  uVar6 = unaff_EDX << 0xb | param_1 >> 0x15;
  uVar1 = param_1 << 0xb;
  uVar3 = (ushort)(unaff_EDX >> 0x14) & 0x7ff;
  uVar4 = unaff_EDX >> 0x14 & 0xffff07ff;
  uVar5 = (undefined2)(uVar4 >> 0x10);
  uVar2 = uVar1;
  if (uVar3 == 0) {
    if ((uVar6 == 0) && (uVar1 == 0)) {
      uVar4 = 0;
    }
    else {
      uVar4 = CONCAT22(uVar5,0x3c01);
      if (uVar6 == 0) {
        uVar4 = CONCAT22(uVar5,0x3be1);
        uVar2 = 0;
        uVar6 = uVar1;
      }
      for (; -1 < (int)uVar6; uVar6 = uVar6 * 2 + (uint)bVar7) {
        bVar7 = CARRY4(uVar2,uVar2);
        uVar2 = uVar2 * 2;
        uVar4 = CONCAT22((short)(uVar4 >> 0x10),(short)uVar4 + -1);
      }
    }
  }
  else {
    if (uVar3 == 0x7ff) {
      uVar4 = CONCAT22(uVar5,0x7fff);
      if (((unaff_EDX << 0xb & 0x7fffffffU) != 0 || param_1 >> 0x15 != 0) || uVar1 != 0) {
        sub_a3890(CONCAT22((short)(uVar1 >> 0x10),0x8101));
        uVar6 = extraout_EDX | 0x40000000;
      }
    }
    else {
      uVar4 = CONCAT22(uVar5,(short)uVar4 + 0x3c00);
    }
    uVar6 = uVar6 | 0x80000000;
  }
  *unaff_EBX = uVar2;
  unaff_EBX[1] = uVar6;
  *(ushort *)(unaff_EBX + 2) = (ushort)uVar4 & 0x7fff | (ushort)CARRY4(uVar4,uVar4) << 0xf;
  return;
}


// ================================================================================================
// sub_a5488 @ 0xa5488 [__watcall]
// ================================================================================================

undefined8 __watcall sub_a5488(int *param_1,undefined4 unaff_EDX)

{
  uint uVar1;
  ushort uVar2;
  ushort uVar3;
  uint uVar4;
  bool bVar5;
  
  uVar4 = 0xffffff00;
  uVar1 = param_1[1];
  uVar2 = *(ushort *)(param_1 + 2);
  if ((int)(uVar1 << 0x18) < 0) {
    if (((uVar1 & 0x7f) == 0) && (*param_1 == 0)) {
      uVar4 = 0xfffffe00;
    }
    bVar5 = 0xfffffeff < uVar1;
    uVar1 = uVar1 + 0x100;
    if (bVar5) {
      uVar1 = 0x80000000;
      uVar2 = uVar2 + 1;
    }
  }
  uVar1 = uVar1 & uVar4;
  if ((uVar2 & 0x7fff) != 0) {
    if ((uVar2 & 0x7fff) == 0x7fff) {
      uVar1 = (uVar1 * 2 >> 8 | 0xff000000) >> 1 | (uint)CARRY2(uVar2,uVar2) << 0x1f;
    }
    else {
      uVar3 = (uVar2 & 0x7fff) + 0xc080;
      if ((short)uVar3 < 0) {
        uVar1 = 0;
      }
      else if ((short)uVar3 < 0xff) {
        uVar1 = (uVar1 * 2 >> 8 | (uint)uVar3 << 0x18) >> 1 | (uint)CARRY2(uVar2,uVar2) << 0x1f;
      }
      else {
        uVar1 = (uint)CARRY2(uVar2,uVar2) << 0x1f | 0x7f800000;
      }
    }
  }
  return CONCAT44(unaff_EDX,uVar1);
}


// ================================================================================================
// sub_a5507 @ 0xa5507 [__watcall]
// ================================================================================================

uint __watcall sub_a5507(uint *param_1)

{
  bool bVar1;
  uint uVar2;
  uint uVar3;
  byte bVar4;
  ushort uVar5;
  ushort uVar6;
  ushort uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  bool bVar11;
  
  uVar5 = *(ushort *)(param_1 + 2);
  uVar8 = param_1[1];
  uVar2 = *param_1;
  uVar10 = 0xfffff800;
  if ((int)(uVar2 << 0x15) < 0) {
    if ((uVar2 & 0x3ff) == 0) {
      uVar10 = 0xfffff000;
    }
    bVar11 = 0xfffff7ff < uVar2;
    uVar2 = uVar2 + 0x800;
    bVar1 = CARRY4(uVar8,(uint)bVar11);
    uVar8 = uVar8 + bVar11;
    if (bVar1) {
      uVar8 = 0x80000000;
      uVar5 = uVar5 + 1;
    }
  }
  uVar2 = uVar2 & uVar10;
  uVar6 = uVar5 & 0x7fff;
  uVar7 = uVar6 + 0xc400;
  if (uVar7 < 0x7ff) {
    if (uVar6 == 0x3c00) {
      uVar2 = uVar2 >> 0xc | uVar8 << 0x14;
    }
    else {
      uVar2 = uVar2 >> 0xb | uVar8 << 0x15;
    }
  }
  else if (uVar7 < 0xc400) {
    uVar2 = uVar2 >> 0xb | uVar8 << 0x15;
    if (uVar7 != 0x43ff) {
      sub_a3890(CONCAT22((short)(uVar2 >> 0x10),0x8408),
                uVar8 * 2 >> 0xc | (uint)CARRY2(uVar5,uVar5) << 0x1f | 0x7ff00000,uVar5 * 2);
    }
  }
  else if ((short)uVar7 < -0x34) {
    uVar2 = 0;
  }
  else {
    bVar4 = -((char)uVar6 + -0xc);
    uVar3 = uVar2;
    uVar9 = uVar8;
    if (0x1f < bVar4) {
      bVar4 = bVar4 - 0x20;
      uVar9 = 0;
      uVar3 = uVar8;
      uVar10 = uVar2;
    }
    uVar8 = uVar10 >> (bVar4 & 0x1f) | uVar3 << 0x20 - (bVar4 & 0x1f);
    uVar2 = (uVar3 >> (bVar4 & 0x1f) | uVar9 << 0x20 - (bVar4 & 0x1f)) + (uint)CARRY4(uVar8,uVar8);
  }
  return uVar2;
}


// ================================================================================================
// sub_a55ce @ 0xa55ce [__watcall]
// ================================================================================================

void __watcall sub_a55ce(uint param_1,undefined4 *unaff_EDX)

{
  ushort uVar1;
  undefined2 uVar3;
  uint uVar2;
  
  uVar1 = (ushort)((int)param_1 >> 0x17) & 0xff;
  uVar2 = (int)param_1 >> 0x17 & 0xffff00ff;
  if (uVar1 != 0) {
    param_1 = param_1 << 8;
    uVar3 = (undefined2)(uVar2 >> 0x10);
    if ((char)uVar2 == -1) {
      uVar2 = CONCAT22(uVar3,0xffff);
      param_1 = param_1 & 0x7fffffff;
      if (param_1 != 0) {
        param_1 = param_1 | 0x40000000;
      }
    }
    else {
      uVar2 = CONCAT22(uVar3,uVar1 + 0x3f80);
    }
    uVar2 = (uint)(ushort)((ushort)uVar2 & 0x7fff | (ushort)CARRY4(uVar2,uVar2) << 0xf);
    param_1 = param_1 | 0x80000000;
  }
  *unaff_EDX = 0;
  unaff_EDX[1] = param_1;
  *(short *)(unaff_EDX + 2) = (short)uVar2;
  return;
}


// ================================================================================================
// sub_a5693 @ 0xa5693 [__watcall]
// ================================================================================================

void __watcall sub_a5693(uint *param_1,ushort unaff_DX)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  ushort uVar5;
  ushort uVar6;
  uint uVar7;
  bool bVar8;
  
  if ((unaff_DX == 0x400 || unaff_DX == 0x800) && ((short)*(ushort *)(param_1 + 2) < 0)) {
    unaff_DX = unaff_DX ^ 0xc00;
  }
  if (unaff_DX == 0xc00) {
    unaff_DX = 0x400;
  }
  uVar5 = *(ushort *)(param_1 + 2) & 0x7fff;
  if (0x403e < uVar5) {
    return;
  }
  uVar4 = *param_1;
  uVar6 = uVar5 + 0xbfe1;
  if (SCARRY2(uVar5 + 0xbfc1,0x20) == (short)uVar6 < 0) {
    uVar3 = *(uint *)(&unk_a5613 + (uint)uVar6 * 4);
    uVar4 = uVar4 & uVar3;
    *param_1 = *param_1 ^ uVar4;
    uVar3 = uVar3 + 1;
    if (unaff_DX != 0x400) {
      if (unaff_DX == 0) {
        uVar4 = uVar4 * 2;
        if (uVar4 < uVar3) {
          return;
        }
        if (uVar3 == uVar4) {
          uVar7 = (uint)((int)uVar3 < 0);
          if ((int)uVar3 < 0) {
            uVar2 = param_1[1];
          }
          else {
            uVar2 = *param_1;
          }
          if ((uVar2 & (uVar3 * 2 | uVar7)) == 0) {
            return;
          }
          uVar3 = uVar3 & 0x7fffffff | (uint)(uVar7 != 0) << 0x1f;
        }
      }
      if (uVar4 != 0) {
        uVar4 = *param_1;
        *param_1 = *param_1 + uVar3;
        uVar7 = param_1[1];
        bVar8 = CARRY4(uVar7,(uint)CARRY4(uVar4,uVar3));
        param_1[1] = uVar7 + CARRY4(uVar4,uVar3);
        if (bVar8) {
          param_1[1] = param_1[1] >> 1 | (uint)bVar8 << 0x1f;
          *(short *)(param_1 + 2) = *(short *)(param_1 + 2) + 1;
        }
      }
    }
    return;
  }
  *param_1 = 0;
  if (SCARRY2(uVar6,0x20) != (short)(uVar5 + 0xc001) < 0) {
    if ((unaff_DX != 0x400) &&
       ((unaff_DX != 0 || ((uVar5 == 0x3ffe && ((param_1[1] != 0x80000000 || (uVar4 != 0)))))))) {
      param_1[1] = 0x80000000;
      *(ushort *)(param_1 + 2) = *(ushort *)(param_1 + 2) | 0x3fff;
      return;
    }
    param_1[1] = 0;
    *(undefined2 *)(param_1 + 2) = 0;
    return;
  }
  uVar3 = *(uint *)(&unk_a5613 + (uint)(ushort)(uVar5 + 0xc001) * 4);
  uVar7 = param_1[1] & uVar3;
  param_1[1] = param_1[1] ^ uVar7;
  uVar3 = uVar3 + 1;
  if (unaff_DX == 0x400) {
    return;
  }
  if (unaff_DX == 0) {
    bVar8 = (int)uVar4 < 0;
    uVar4 = uVar4 << 1 | (uint)bVar8;
    uVar7 = uVar7 * 2 + (uint)bVar8;
    if (uVar7 < uVar3) {
      return;
    }
    if (uVar3 == uVar7) {
      if (uVar4 != 0) goto LAB_000a5776;
      uVar2 = uVar3 * 2;
      if (!CARRY4(uVar3,uVar3)) {
        uVar2 = param_1[1] & uVar2;
      }
      if (uVar2 == 0) {
        return;
      }
      uVar3 = uVar3 & 0x7fffffff;
    }
  }
  if (uVar4 == 0 && uVar7 == 0) {
    return;
  }
LAB_000a5776:
  puVar1 = param_1 + 1;
  uVar4 = *puVar1;
  *puVar1 = *puVar1 + uVar3;
  if (CARRY4(uVar4,uVar3)) {
    param_1[1] = param_1[1] >> 1 | (uint)CARRY4(uVar4,uVar3) << 0x1f;
    *(short *)(param_1 + 2) = *(short *)(param_1 + 2) + 1;
  }
  return;
}


// ================================================================================================
// sub_a5820 @ 0xa5820 [__watcall]
// ================================================================================================

void __watcall sub_a5820(int param_1,int unaff_EDX,undefined4 *unaff_EBX)

{
  char cVar1;
  
  if ((*(ushort *)(param_1 + 8) & 0x7fff) == 0) {
    if ((*(byte *)(unaff_EDX + 9) & 0x80) == 0) {
      *(undefined2 *)(unaff_EBX + 2) = 0;
      unaff_EBX[1] = 0;
      *unaff_EBX = 0;
    }
    else {
      *(undefined2 *)(unaff_EBX + 2) = 0x4000;
      unaff_EBX[1] = 0xc90fdaa2;
      *unaff_EBX = 0x2168c235;
    }
  }
  else if ((*(ushort *)(unaff_EDX + 8) & 0x7fff) == 0) {
    *(ushort *)(unaff_EBX + 2) = *(ushort *)(param_1 + 8) & 0x8000 | 0x3fff;
    unaff_EBX[1] = 0xc90fdaa2;
    *unaff_EBX = 0x2168c235;
  }
  else {
    cVar1 = *(char *)(param_1 + 9);
    sub_a5003();
    sub_a58d6(unaff_EBX);
    if (cVar1 < '\0') {
      if ('\0' < *(char *)((int)unaff_EBX + 9)) {
        sub_a4dce(unaff_EBX);
      }
    }
    else if (*(char *)((int)unaff_EBX + 9) < '\0') {
      sub_a4dce(unaff_EBX);
    }
  }
  return;
}


// ================================================================================================
// sub_a58d6 @ 0xa58d6 [__watcall]
// ================================================================================================

void __watcall
sub_a58d6(uint *param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  undefined2 uVar1;
  undefined2 uVar2;
  byte bVar4;
  uint uVar3;
  undefined4 extraout_EDX;
  bool bVar6;
  bool bVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  byte bVar5;
  
  bVar4 = *(byte *)((int)param_1 + 9);
  uVar3 = CONCAT31((int3)((uint)unaff_ECX >> 8),bVar4) & 0xffff00ff;
  *(byte *)((int)param_1 + 9) = *(byte *)((int)param_1 + 9) & 0x7f;
  if (((*(short *)(param_1 + 2) == 0x3fff) && (param_1[1] == 0x80000000)) && (*param_1 == 0)) {
    *param_1 = 0x2168c235;
    param_1[1] = 0xc90fdaa2;
    *(ushort *)(param_1 + 2) = CONCAT11(bVar4 & 0x80 | 0x3f,0xfe);
    return;
  }
  if (0x3ffe < *(short *)(param_1 + 2)) {
    uVar8 = sub_a502d(0,0x80000000,*param_1,param_1[1],uVar3,unaff_EBX,unaff_EDX,unaff_ECX);
    *(undefined8 *)param_1 = uVar8;
    *(undefined2 *)(param_1 + 2) = 0x3fff;
    uVar3 = CONCAT22((short)(uVar3 >> 0x10),CONCAT11(2,(char)uVar3));
  }
  bVar6 = *(ushort *)(param_1 + 2) < 0x3ffd;
  bVar7 = *(ushort *)(param_1 + 2) == 0x3ffd;
  if (bVar7) {
    bVar6 = param_1[1] < 0x8930a2f4;
    bVar7 = param_1[1] == 0x8930a2f4;
    if (bVar7) {
      bVar6 = *param_1 < 0xf66ab09b;
      bVar7 = *param_1 == 0xf66ab09b;
    }
  }
  if (!bVar6 && !bVar7) {
    uVar1 = *(undefined2 *)(param_1 + 2);
    uVar8 = sub_a4dfe(*param_1,param_1[1],0xc265539e,0xddb3d742);
    uVar2 = *(undefined2 *)(param_1 + 2);
    uVar9 = sub_a5202(*param_1,param_1[1],0xc265539e,0xddb3d742,CONCAT22(0x3fff,uVar1));
    uVar9 = sub_a4dfe((int)uVar9,(int)((ulonglong)uVar9 >> 0x20),0,0x80000000);
    uVar8 = sub_a502d((int)uVar9,(int)((ulonglong)uVar9 >> 0x20),(int)uVar8,
                      (int)((ulonglong)uVar8 >> 0x20));
    *(undefined8 *)param_1 = uVar8;
    *(undefined2 *)(param_1 + 2) = uVar2;
    uVar3 = uVar3 | 0x100;
  }
  sub_a6452(param_1,&dword_a57c6,8);
  bVar5 = (byte)(uVar3 >> 8);
  bVar4 = bVar5 >> 1;
  if ((bool)(bVar5 & 1)) {
    sub_a4dce(param_1,extraout_EDX,param_1,
              CONCAT22((short)(uVar3 >> 0x10),CONCAT11(bVar4,(char)uVar3)),0x6b9b2c23,0x860a91c1,
              0x3ffe);
  }
  if ((bool)(bVar4 & 1)) {
    sub_a4dce(param_1);
    *(byte *)((int)param_1 + 9) = *(byte *)((int)param_1 + 9) ^ 0x80;
  }
  if ((char)uVar3 < '\0') {
    *(byte *)((int)param_1 + 9) = *(byte *)((int)param_1 + 9) ^ 0x80;
  }
  return;
}


// ================================================================================================
// sub_a5a39 @ 0xa5a39 [__watcall]
// ================================================================================================

longlong __watcall sub_a5a39(int *param_1,int *unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  undefined2 uVar1;
  undefined2 uVar2;
  undefined4 unaff_EDI;
  undefined8 uVar3;
  
  if (((*(short *)(param_1 + 2) == 0) && (param_1[1] == 0)) && (*param_1 == 0)) {
    return ZEXT48(unaff_EDX) << 0x20;
  }
  if (((*(short *)(unaff_EDX + 2) == 0) && (unaff_EDX[1] == 0)) && (*unaff_EDX == 0)) {
    *param_1 = 0;
    param_1[1] = 0;
    *(undefined2 *)(param_1 + 2) = 0;
    return 0;
  }
  uVar1 = *(undefined2 *)(param_1 + 2);
  uVar2 = *(undefined2 *)(unaff_EDX + 2);
  uVar3 = sub_a5a9f(*param_1,param_1[1],*unaff_EDX,unaff_EDX[1],param_1,unaff_EBX,unaff_ECX);
  *(undefined8 *)param_1 = uVar3;
  *(undefined2 *)(param_1 + 2) = uVar1;
  return CONCAT44(unaff_EDX,CONCAT22((short)((uint)unaff_EDI >> 0x10),uVar2));
}


// ================================================================================================
// sub_a5a9f @ 0xa5a9f [__watcall]
// ================================================================================================

void __watcall sub_a5a9f(uint param_1,uint unaff_EDX,uint unaff_EBX,uint unaff_ECX)

{
  uint uVar1;
  uint unaff_ESI;
  int iVar2;
  int iVar3;
  uint unaff_EDI;
  bool bVar4;
  bool bVar5;
  
  iVar2 = (unaff_ESI & 0x7fff) - (unaff_EDI & 0x7fff);
  if ((unaff_ESI & 0x7fff) < (unaff_EDI & 0x7fff)) {
    return;
  }
LAB_000a5ab3:
  bVar4 = unaff_ECX < unaff_EDX;
  if (((unaff_ECX != unaff_EDX) || (bVar4 = unaff_EBX < param_1, unaff_EBX != param_1)) &&
     (iVar3 = iVar2, !bVar4)) goto LAB_000a5ac6;
  do {
    bVar4 = param_1 < unaff_EBX;
    param_1 = param_1 - unaff_EBX;
    unaff_EDX = (unaff_EDX - unaff_ECX) - (uint)bVar4;
    iVar3 = iVar2;
LAB_000a5ac6:
    while( true ) {
      iVar2 = iVar3 + -1;
      if (iVar3 < 1) {
        if ((param_1 == 0) && (unaff_EDX == 0)) {
          return;
        }
        for (; -1 < (int)unaff_EDX; unaff_EDX = unaff_EDX * 2 + (uint)bVar4) {
          bVar4 = CARRY4(param_1,param_1);
          param_1 = param_1 * 2;
        }
        return;
      }
      bVar4 = CARRY4(param_1,param_1);
      param_1 = param_1 * 2;
      bVar5 = CARRY4(unaff_EDX,unaff_EDX);
      uVar1 = unaff_EDX * 2;
      unaff_EDX = uVar1 + bVar4;
      if (bVar5 || CARRY4(uVar1,(uint)bVar4)) break;
      iVar3 = iVar2;
      if ((int)unaff_EDX < 0) goto LAB_000a5ab3;
    }
  } while( true );
}


// ================================================================================================
// sub_a5b1a @ 0xa5b1a [__watcall]
// ================================================================================================

void __watcall sub_a5b1a(int *param_1)

{
  byte bVar1;
  byte bVar3;
  ushort uVar2;
  int unaff_EBP;
  int unaff_EDI;
  bool bVar4;
  
  uVar2 = *(ushort *)(unk_a32d6 + unaff_EDI);
  if ((uVar2 & *(ushort *)(unaff_EBP + 8)) == uVar2) {
    bVar1 = 0x41;
    bVar3 = 0;
  }
  else {
    *(ushort *)(unaff_EBP + 8) = *(ushort *)(unaff_EBP + 8) & ~uVar2;
    bVar3 = ((short)*(ushort *)(param_1 + 2) < 0) << 1;
    uVar2 = *(ushort *)(param_1 + 2) & 0x7fff;
    if (uVar2 == 0) {
      bVar1 = 0x44;
      if (param_1[1] == 0 && *param_1 == 0) {
        *(ushort *)(unaff_EBP + 8) = *(ushort *)(unaff_EBP + 8) | *(ushort *)(unk_a32d0 + unaff_EDI)
        ;
        bVar1 = 0x40;
      }
    }
    else if (uVar2 == 0x7fff) {
      *(ushort *)(unaff_EBP + 8) = *(ushort *)(unaff_EBP + 8) | *(ushort *)(unk_a32d4 + unaff_EDI);
      bVar4 = *param_1 == 0;
      if (bVar4) {
        bVar4 = param_1[1] == -0x80000000;
      }
      bVar1 = 1;
      if (bVar4) {
        bVar1 = 5;
      }
    }
    else {
      bVar1 = 4;
      if ((*(byte *)((int)param_1 + 7) & 0x80) == 0) {
        *(ushort *)(unaff_EBP + 8) = *(ushort *)(unaff_EBP + 8) | *(ushort *)(unk_a32d4 + unaff_EDI)
        ;
        bVar1 = 0x44;
      }
    }
  }
  uVar2 = *(ushort *)(unaff_EBP + 4) & 0xb8ff;
  *(ushort *)(unaff_EBP + 4) = CONCAT11((byte)(uVar2 >> 8) | bVar1 | bVar3,(char)uVar2);
  return;
}


// ================================================================================================
// sub_a5c08 @ 0xa5c08 [__watcall]
// ================================================================================================

void __watcall
sub_a5c08(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  undefined8 *extraout_EDX;
  undefined8 uVar1;
  undefined8 *puVar2;
  undefined4 uVar3;
  
  sub_a4dce(param_1,unaff_EDX,param_1,unaff_ECX,0,0x80000000,0x3fff);
  uVar3 = unaff_ECX;
  sub_a5c64();
  puVar2 = extraout_EDX;
  sub_a51d8(param_1,extraout_EDX,extraout_EDX,unaff_ECX,extraout_EDX,unaff_EBX,uVar3,unaff_EDX);
  uVar1 = sub_a5202(0x5c17f0bd,0xb8aa3b29,*(undefined4 *)puVar2,*(undefined4 *)((int)puVar2 + 4));
  *puVar2 = uVar1;
  *(undefined2 *)(puVar2 + 1) = 0x3fff;
  return;
}


// ================================================================================================
// sub_a5c21 @ 0xa5c21 [__watcall]
// ================================================================================================

void __watcall
sub_a5c21(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  undefined8 *extraout_EDX;
  undefined8 uVar1;
  undefined8 *puVar2;
  undefined4 uVar3;
  
  uVar3 = unaff_ECX;
  sub_a5c64();
  puVar2 = extraout_EDX;
  sub_a51d8(param_1,extraout_EDX,extraout_EDX,unaff_ECX,extraout_EDX,unaff_EBX,uVar3,unaff_EDX);
  uVar1 = sub_a5202(0x5c17f0bd,0xb8aa3b29,*(undefined4 *)puVar2,*(undefined4 *)((int)puVar2 + 4));
  *puVar2 = uVar1;
  *(undefined2 *)(puVar2 + 1) = 0x3fff;
  return;
}


// ================================================================================================
// sub_a5c64 @ 0xa5c64 [__watcall]
// ================================================================================================

void __watcall
sub_a5c64(uint *param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  ushort uVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  bool bVar5;
  bool bVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  
  iVar2 = *(ushort *)(param_1 + 2) - 0x3ffe;
  *(undefined2 *)(param_1 + 2) = 0x3ffe;
  uVar7 = sub_a4dfe(*param_1,param_1[1],0,0x80000000,iVar2,unaff_EBX,unaff_ECX,unaff_EDX);
  bVar5 = *(ushort *)(param_1 + 2) < 0x3ffe;
  bVar6 = *(ushort *)(param_1 + 2) == 0x3ffe;
  if (bVar6) {
    bVar5 = param_1[1] < 0xb504f333;
    bVar6 = param_1[1] == 0xb504f333;
    if (bVar6) {
      bVar5 = *param_1 < 0xf9de6484;
      bVar6 = *param_1 == 0xf9de6484;
    }
  }
  if (bVar5 || bVar6) {
    *(undefined8 *)param_1 = uVar7;
    *(undefined2 *)(param_1 + 2) = 0x3ffe;
    iVar2 = iVar2 + -1;
  }
  else {
    uVar7 = sub_a4dfe((int)uVar7,(int)((ulonglong)uVar7 >> 0x20),0,0x80000000,iVar2,unaff_EBX,
                      unaff_ECX,unaff_EDX);
  }
  uVar8 = sub_a4dfe(*param_1,param_1[1],0,0x80000000);
  uVar7 = sub_a502d((int)uVar7,(int)((ulonglong)uVar7 >> 0x20),(int)uVar8,
                    (int)((ulonglong)uVar8 >> 0x20));
  uVar3 = (undefined4)((ulonglong)uVar7 >> 0x20);
  uVar8 = sub_a5202((int)uVar7,uVar3,(int)uVar7,uVar3);
  *(undefined8 *)param_1 = uVar8;
  *(undefined2 *)(param_1 + 2) = 0x3ffe;
  uVar8 = sub_a6400((int)uVar8,(int)((ulonglong)uVar8 >> 0x20),3,&dword_a5be0);
  uVar1 = *(ushort *)(param_1 + 2);
  uVar9 = sub_a6400(*param_1,param_1[1],2,&dword_a5bc2,0x3ffe3ffe);
  uVar8 = sub_a502d((int)uVar9,(int)((ulonglong)uVar9 >> 0x20),(int)uVar8,
                    (int)((ulonglong)uVar8 >> 0x20));
  uVar8 = sub_a5202((int)uVar8,(int)((ulonglong)uVar8 >> 0x20),*param_1,param_1[1]);
  uVar8 = sub_a5202((int)uVar8,(int)((ulonglong)uVar8 >> 0x20),(int)uVar7,
                    (int)((ulonglong)uVar7 >> 0x20));
  uVar4 = CONCAT22(uVar1,0x3ffe) << 0x10 | (uint)uVar1;
  uVar7 = sub_a4dfe((int)uVar8,(int)((ulonglong)uVar8 >> 0x20),(int)uVar7,
                    (int)((ulonglong)uVar7 >> 0x20));
  if (iVar2 != 0) {
    sub_a53c2(iVar2,param_1);
    sub_a5202(*param_1,param_1[1],0x865435c,0xde8082e3,uVar4,(int)((ulonglong)uVar7 >> 0x20),
              (int)uVar7);
    uVar7 = sub_a4dfe();
    uVar1 = *(ushort *)(param_1 + 2);
    uVar8 = sub_a5202(*param_1,param_1[1],0,0xb1800000);
    uVar4 = (uint)uVar1;
    uVar7 = sub_a4dfe((int)uVar8,(int)((ulonglong)uVar8 >> 0x20),(int)uVar7,
                      (int)((ulonglong)uVar7 >> 0x20));
  }
  *(undefined8 *)param_1 = uVar7;
  *(short *)(param_1 + 2) = (short)uVar4;
  return;
}


// ================================================================================================
// sub_a5efc @ 0xa5efc [__watcall]
// ================================================================================================

void __watcall sub_a5efc(longlong *param_1)

{
  longlong *plVar1;
  byte bVar2;
  undefined2 uVar3;
  uint uVar4;
  short sVar6;
  longlong **pplVar7;
  byte unaff_SI;
  ushort uVar8;
  char cVar9;
  bool bVar10;
  longlong lVar11;
  undefined8 uVar12;
  longlong lVar13;
  longlong *local_2c;
  undefined4 local_20;
  undefined4 local_1c;
  ushort local_18;
  uint uVar5;
  
  lVar13 = CONCAT44(local_1c,local_20);
  uVar3 = *(undefined2 *)(param_1 + 1);
  cVar9 = -2;
  local_2c = param_1;
  lVar11 = sub_a5a9f(*(undefined4 *)param_1,*(undefined4 *)((int)param_1 + 4),0x2168c235,0xc90fdaa2)
  ;
  plVar1 = local_2c;
  *local_2c = lVar11;
  *(undefined2 *)(local_2c + 1) = uVar3;
  bVar10 = (*(byte *)((int)local_2c + 9) & 0x80) != 0;
  if (bVar10) {
    local_2c = (longlong *)0x3ffe;
    sub_a4dce(plVar1,(int)((ulonglong)lVar11 >> 0x20),plVar1,plVar1,0x2168c235,0xc90fdaa2);
    cVar9 = -3;
  }
  bVar2 = cVar9 + (unaff_SI & 2);
  uVar4 = CONCAT11(unaff_SI,bVar2) & 0xffffff07;
  if (bVar10) {
    local_2c = (longlong *)0xbffe;
    sub_a4dce(plVar1);
    *(byte *)((int)plVar1 + 9) = *(byte *)((int)plVar1 + 9) ^ 0x80;
  }
  sVar6 = *(short *)(plVar1 + 1) + -0x3ffe;
  if (sVar6 < -0x20) {
    lVar13 = -0x8000000000000000;
    local_18 = 0x3fff;
    pplVar7 = (longlong **)&stack0xffffffd8;
  }
  else {
    if (-1 < sVar6) {
      sVar6 = 0;
    }
    uVar5 = (uint)(ushort)-sVar6;
    if (8 < -sVar6) {
      uVar5 = 8;
    }
    local_2c = (longlong *)(uint)*(ushort *)((int)&unk_a5eea + uVar5 * 2);
    uVar5 = CONCAT31((int3)(uVar4 >> 8),bVar10 + 1U) & 0xffffff02;
    uVar3 = (undefined2)uVar5;
    if (((bVar10 + 1U & 2) != 0) || ((char)(uVar5 >> 8) == '\x01')) {
      local_18 = *(ushort *)(plVar1 + 1);
      uVar12 = sub_a5202(*(undefined4 *)plVar1,*(undefined4 *)((int)plVar1 + 4),
                         *(undefined4 *)plVar1,*(undefined4 *)((int)plVar1 + 4));
      lVar13 = sub_a6400((int)uVar12,(int)((ulonglong)uVar12 >> 0x20),8 - (int)local_2c,
                         &unk_a5e90 + (int)local_2c * 10);
    }
    pplVar7 = &local_2c;
    if (((char)uVar3 == '\0') || ((char)((ushort)uVar3 >> 8) == '\x01')) {
      sub_a6452(plVar1,(int)&dword_a5e36 + (int)local_2c * 10,8 - (int)local_2c);
      pplVar7 = &local_2c;
    }
  }
  uVar8 = local_18;
  lVar11 = lVar13;
  if ((bVar10 + 1U & 2) == 0) {
    uVar8 = *(ushort *)(plVar1 + 1);
    lVar11 = *plVar1;
  }
  if ((bVar2 & 4) != 0) {
    uVar8 = uVar8 ^ 0x8000;
  }
  if ((char)(uVar4 >> 8) == '\x01') {
    if ((bVar10 + 3U & 2) == 0) {
      lVar13 = *plVar1;
      local_18 = *(ushort *)(plVar1 + 1);
    }
    if ((lVar13 == 0) && ((local_18 & 0x7fff) == 0)) {
      lVar11 = -0x8000000000000000;
      uVar8 = uVar8 | 0x7fff;
    }
    else {
      *(undefined4 *)((int)pplVar7 + -4) = 0xa60e2;
      lVar11 = sub_a502d();
    }
  }
  *plVar1 = lVar11;
  *(ushort *)(plVar1 + 1) = uVar8;
  return;
}


// ================================================================================================
// sub_a60f3 @ 0xa60f3 [__watcall]
// ================================================================================================

void __watcall sub_a60f3(void)

{
  sub_a5efc();
  return;
}


// ================================================================================================
// sub_a60fd @ 0xa60fd [__watcall]
// ================================================================================================

void __watcall sub_a60fd(void)

{
  sub_a5efc();
  return;
}


// ================================================================================================
// sub_a610a @ 0xa610a [__watcall]
// ================================================================================================

void __watcall sub_a610a(void)

{
  sub_a5efc();
  return;
}


// ================================================================================================
// sub_a6140 @ 0xa6140 [__watcall]
// ================================================================================================

void __watcall
sub_a6140(uint *param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  ushort uVar8;
  short sVar9;
  undefined4 uVar10;
  undefined4 *puVar11;
  bool bVar12;
  bool bVar13;
  undefined8 uVar14;
  undefined8 uVar15;
  undefined2 uVar16;
  undefined4 uVar17;
  
  uVar10 = 0;
  *(byte *)((int)param_1 + 9) = *(byte *)((int)param_1 + 9) & 0x7f;
  bVar13 = *(short *)(param_1 + 2) == 0;
  if ((bVar13) && (bVar13 = param_1[1] == 0, bVar13)) {
    bVar13 = *param_1 == 0;
  }
  if (bVar13) {
    uVar3 = 0;
  }
  else {
    if (*(short *)(param_1 + 2) < 0) {
      uVar10 = 0xffffffff;
      sub_a4dce(param_1);
      *(byte *)((int)param_1 + 9) = *(byte *)((int)param_1 + 9) ^ 0x80;
    }
    uVar3 = 0;
    uVar4 = param_1[1];
    uVar2 = *param_1;
    for (uVar8 = *(short *)(param_1 + 2) + 4; 0x3ffe < uVar8; uVar8 = uVar8 - 1) {
      bVar13 = CARRY4(uVar2,uVar2);
      uVar2 = uVar2 * 2;
      bVar12 = CARRY4(uVar4,uVar4);
      uVar1 = uVar4 * 2;
      uVar4 = uVar1 + bVar13;
      uVar3 = uVar3 * 2 + (uint)(bVar12 || CARRY4(uVar1,(uint)bVar13));
    }
    if (uVar4 == 0 && uVar2 == 0) {
      sVar9 = 0;
    }
    else {
      for (; -1 < (int)uVar4; uVar4 = uVar4 * 2 + (uint)bVar13) {
        bVar13 = CARRY4(uVar2,uVar2);
        uVar2 = uVar2 * 2;
        uVar8 = uVar8 - 1;
      }
      sVar9 = uVar8 - 4;
    }
    *param_1 = uVar2;
    param_1[1] = uVar4;
    *(short *)(param_1 + 2) = sVar9;
  }
  uVar8 = *(ushort *)(param_1 + 2);
  uVar14 = sub_a5202(*param_1,param_1[1],*param_1,param_1[1],uVar3,uVar10,unaff_EBX,unaff_ECX,
                     unaff_EDX);
  uVar5 = (undefined4)((ulonglong)uVar14 >> 0x20);
  uVar7 = (undefined4)uVar14;
  uVar4 = uVar8 | 0x40030000;
  uVar14 = sub_a4dfe(uVar7,uVar5,0x1bf21f8c,0xa6829a79);
  uVar6 = (undefined4)((ulonglong)uVar14 >> 0x20);
  uVar17 = (undefined4)uVar14;
  LOCK();
  UNLOCK();
  LOCK();
  UNLOCK();
  LOCK();
  UNLOCK();
  uVar14 = sub_a5202(uVar7,uVar5,0x9d7bfdb,0xec96f0d6,uVar4);
  uVar16 = (undefined2)uVar4;
  uVar14 = sub_a4dfe((int)uVar14,(int)((ulonglong)uVar14 >> 0x20),0xe536e187,0xe6d5051a);
  uVar14 = sub_a5202((int)uVar14,(int)((ulonglong)uVar14 >> 0x20),*param_1,param_1[1]);
  uVar7 = (undefined4)((ulonglong)uVar14 >> 0x20);
  uVar4 = CONCAT22(uVar8,uVar16);
  uVar15 = sub_a4dfe((int)uVar14,uVar7,uVar17,uVar6);
  LOCK();
  UNLOCK();
  LOCK();
  UNLOCK();
  LOCK();
  UNLOCK();
  uVar14 = sub_a4dfe((int)uVar14,uVar7,uVar17,uVar6,uVar4 << 0x10 | (uVar4 ^ 0x80000000) >> 0x10);
  uVar14 = sub_a502d((int)uVar14,(int)((ulonglong)uVar14 >> 0x20),(int)uVar15,
                     (int)((ulonglong)uVar15 >> 0x20));
  uVar7 = (undefined4)((ulonglong)uVar14 >> 0x20);
  *(undefined8 *)param_1 = uVar14;
  *(ushort *)(param_1 + 2) = uVar8;
  puVar11 = &dword_a6118;
  while (uVar3 != 0) {
    uVar4 = uVar3 & 1;
    uVar3 = uVar3 >> 1;
    if (uVar4 != 0) {
      uVar16 = *(undefined2 *)(puVar11 + 2);
      uVar14 = sub_a5202(*puVar11,puVar11[1],*param_1,param_1[1]);
      uVar7 = (undefined4)((ulonglong)uVar14 >> 0x20);
      *(undefined8 *)param_1 = uVar14;
      *(undefined2 *)(param_1 + 2) = uVar16;
    }
    puVar11 = (undefined4 *)((int)puVar11 + 10);
  }
  *(short *)(param_1 + 2) = *(short *)(param_1 + 2) + (short)uVar10;
  sub_a4dce(param_1,uVar7,param_1,0,0,0x80000000,0xbfff);
  return;
}


// ================================================================================================
// sub_a6314 @ 0xa6314 [__watcall]
// ================================================================================================

void __watcall sub_a6314(uint *param_1)

{
  uint uVar1;
  ushort uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  bool bVar7;
  
  uVar2 = *(ushort *)(param_1 + 2);
  uVar4 = *param_1;
  if (uVar4 == 0) {
    if (param_1[1] != 0) {
      if (uVar2 == 0x7fff) {
        return;
      }
      goto LAB_000a635a;
    }
    if ((uVar2 & 0x7fff) == 0) {
      return;
    }
  }
  else {
LAB_000a635a:
    if (((uVar2 & 0x7fff) == 0x7fff) || (CARRY2(uVar2,uVar2))) goto LAB_000a6346;
    if (((uVar2 & 0x7fff) == 0) || (CARRY4(param_1[1],param_1[1]))) {
      uVar3 = param_1[1];
      uVar6 = 0;
      uVar2 = (uVar2 & 0x7fff) + 0xc001;
      if ((uVar2 & 1) == 0) {
        uVar5 = uVar3 & 1;
        uVar3 = uVar3 >> 1;
        uVar6 = uVar4 & 1;
        uVar4 = uVar4 >> 1 | (uint)(uVar5 != 0) << 0x1f;
        uVar6 = (uint)(uVar6 != 0) << 0x1f;
      }
      *(short *)(param_1 + 2) = ((short)uVar2 >> 1) + 0x3fff;
      uVar5 = uVar3 >> 1 | 0x80000000;
      if (uVar3 == 0xffffffff) {
        bVar7 = uVar4 < uVar5;
        if (uVar4 == uVar5) goto LAB_000a63d2;
        uVar3 = (uint)(CONCAT44(uVar4,uVar6) / (ulonglong)uVar5);
      }
      else {
        while( true ) {
          uVar1 = (uint)(CONCAT44(uVar3,uVar4) / (ulonglong)uVar5);
          if (uVar5 - 1 <= uVar1) break;
          uVar5 = uVar5 + uVar1 >> 1 | (uint)CARRY4(uVar5,uVar1) << 0x1f;
        }
        uVar3 = (uint)((CONCAT44(uVar3,uVar4) % (ulonglong)uVar5 << 0x20 | (ulonglong)uVar6) /
                      (ulonglong)uVar5);
        uVar5 = uVar5 + uVar1;
      }
      uVar4 = uVar5 & 1;
      uVar5 = uVar5 >> 1 | 0x80000000;
      uVar4 = uVar3 >> 1 | (uint)(uVar4 != 0) << 0x1f;
      uVar3 = (uint)((uVar3 & 1) != 0);
      bVar7 = CARRY4(uVar4,uVar3);
      uVar4 = uVar4 + uVar3;
LAB_000a63d2:
      *param_1 = uVar4;
      param_1[1] = uVar5 + bVar7;
      return;
    }
  }
  *(undefined2 *)(param_1 + 2) = 0xffff;
  param_1[1] = 0;
  *param_1 = 0;
LAB_000a6346:
  *(byte *)((int)param_1 + 7) = *(byte *)((int)param_1 + 7) | 0xc0;
  return;
}


// ================================================================================================
// sub_a63e0 @ 0xa63e0 [__watcall]
// ================================================================================================

void __watcall
sub_a63e0(undefined8 *param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  undefined2 uVar1;
  undefined8 uVar2;
  
  uVar1 = *(undefined2 *)(param_1 + 1);
  uVar2 = sub_a6400(*(undefined4 *)param_1,*(undefined4 *)((int)param_1 + 4),unaff_EBX,unaff_EDX,
                    param_1,unaff_ECX);
  *param_1 = uVar2;
  *(undefined2 *)(param_1 + 1) = uVar1;
  return;
}


// ================================================================================================
// sub_a6400 @ 0xa6400 [__watcall]
// ================================================================================================

void __watcall
sub_a6400(undefined4 param_1,undefined4 unaff_EDX,int unaff_EBX,undefined8 *unaff_ECX)

{
  undefined8 uVar1;
  
  uVar1 = *unaff_ECX;
  do {
    uVar1 = sub_a5202((int)uVar1,(int)((ulonglong)uVar1 >> 0x20),param_1,unaff_EDX);
    uVar1 = sub_a4dfe((int)uVar1,(int)((ulonglong)uVar1 >> 0x20),
                      *(undefined4 *)((int)unaff_ECX + 10),*(undefined4 *)((int)unaff_ECX + 0xe));
    unaff_EBX = unaff_EBX + -1;
    unaff_ECX = (undefined8 *)((int)unaff_ECX + 10);
  } while (unaff_EBX != 0);
  return;
}


// ================================================================================================
// sub_a6452 @ 0xa6452 [__watcall]
// ================================================================================================

void __watcall
sub_a6452(undefined8 *param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  undefined2 uVar1;
  undefined8 uVar2;
  
  uVar1 = *(undefined2 *)(param_1 + 1);
  uVar2 = sub_a5202(*(undefined4 *)param_1,*(undefined4 *)((int)param_1 + 4),*(undefined4 *)param_1,
                    *(undefined4 *)((int)param_1 + 4),unaff_EDX,unaff_EBX,unaff_ECX);
  uVar2 = sub_a6400((int)uVar2,(int)((ulonglong)uVar2 >> 0x20),unaff_EBX,unaff_EDX);
  uVar2 = sub_a5202((int)uVar2,(int)((ulonglong)uVar2 >> 0x20),*(undefined4 *)param_1,
                    *(undefined4 *)((int)param_1 + 4));
  *param_1 = uVar2;
  *(undefined2 *)(param_1 + 1) = uVar1;
  return;
}


// ================================================================================================
// sub_a649a @ 0xa649a [__watcall]
// ================================================================================================

undefined4 __watcall sub_a649a(int param_1)

{
  code *pcVar1;
  char cVar2;
  short sVar3;
  undefined2 extraout_var;
  undefined extraout_DL;
  undefined4 extraout_EDX;
  undefined4 *puVar4;
  undefined2 in_ES;
  undefined2 in_CS;
  undefined auStack_14 [4];
  
  pcVar1 = (code *)swi(0x2f);
  cVar2 = (*pcVar1)();
  puVar4 = (undefined4 *)&stack0xffffffe8;
  if ((cVar2 != '\0') && (puVar4 = (undefined4 *)&stack0xffffffe8, cVar2 != -0x80)) {
    pcVar1 = (code *)swi(0x2f);
    sVar3 = (*pcVar1)();
    puVar4 = (undefined4 *)auStack_14;
    if (sVar3 == 0x666) {
      pcVar1 = (code *)swi(0x2f);
      sVar3 = (*pcVar1)();
      puVar4 = (undefined4 *)&stack0xfffffff0;
      if (sVar3 == 0) {
        byte_d65f9 = 1;
        pcVar1 = (code *)swi(0x2f);
        (*pcVar1)();
        pcVar1 = (code *)swi(0x2f);
        (*pcVar1)();
        return 1;
      }
    }
  }
  if ((param_1 != 0) || ((short)*puVar4 != 0)) {
    cVar2 = '\0';
    *(undefined2 *)(puVar4 + -1) = in_ES;
    pcVar1 = (code *)swi(0x31);
    (*pcVar1)();
    if (cVar2 == '\0') {
      *puVar4 = 0xa6531;
      sub_98ac8(7,extraout_EDX,sub_a365c,CONCAT22(extraout_var,in_CS));
      *(undefined *)(param_1 + 0x3e) = 1;
      *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) | 4;
      pcVar1 = (code *)swi(0x21);
      (*pcVar1)();
      byte_d65f8 = extraout_DL;
    }
  }
  return 0;
}


// ================================================================================================
// sub_a6564 @ 0xa6564 [__watcall]
// ================================================================================================

undefined4 __watcall
sub_a6564(int param_1,undefined4 param_2,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  code *pcVar1;
  
  if (byte_d65f9 != '\0') {
    pcVar1 = (code *)swi(0x2f);
    (*pcVar1)();
    pcVar1 = (code *)swi(0x2f);
    (*pcVar1)();
    return 1;
  }
  if (byte_d65f8 != '\0') {
    *(undefined *)(param_1 + 0x3e) = 0;
    *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfb;
    pcVar1 = (code *)swi(0x21);
    (*pcVar1)(unaff_ECX,unaff_EBX);
  }
  return 0;
}


// ================================================================================================
// unk_a65bd @ 0xa65bd
// ================================================================================================

void unk_a65bd(void)

{
  return;
}


// ================================================================================================
// sub_a65be @ 0xa65be [__watcall]
// ================================================================================================

undefined2 __watcall sub_a65be(void)

{
  undefined2 *puVar1;
  undefined2 in_SS;
  undefined local_2 [2];
  
  LOCK();
  UNLOCK();
  puVar1 = (undefined2 *)segment(in_SS,(short)local_2);
  return *puVar1;
}


// ================================================================================================
// sub_a65e8 @ 0xa65e8 [__watcall]
// ================================================================================================

undefined4 __watcall sub_a65e8(void)

{
  out(0x43,0xb6);
  sub_a6618(0xb6);
  byte_d6785 = 0x7f;
  byte_d6786 = 0x7f;
  byte_d6787 = 0x7f;
  byte_d6788 = 0x7f;
  byte_d6789 = 0x7f;
  return 5;
}


// ================================================================================================
// sub_a6612 @ 0xa6612 [__watcall]
// ================================================================================================

void __watcall sub_a6612(void)

{
  sub_a6618();
  return;
}


// ================================================================================================
// sub_a6618 @ 0xa6618 [__watcall]
// ================================================================================================

void __watcall sub_a6618(void)

{
  byte bVar1;
  
  bVar1 = in(0x61);
  out(0x61,bVar1 & 0xfc);
  byte_d6775 = 0;
  byte_d6776 = 0;
  byte_d6777 = 0;
  byte_d6778 = 0;
  return;
}


// ================================================================================================
// sub_a6635 @ 0xa6635 [__cdecl]
// ================================================================================================

void sub_a6635(int param_1,int param_2,byte param_3)

{
  undefined2 uVar1;
  
  if (param_1 != 0) {
    *(byte *)(param_2 + 3) = param_3;
    if (param_3 != 0xff) {
      uVar1 = *(undefined2 *)(&unk_d6608 + (uint)param_3 * 2);
      *(undefined2 *)(param_2 + 4) = uVar1;
      *(undefined2 *)(param_2 + 6) = uVar1;
    }
    (&byte_d6774)[param_1] = 0xff;
  }
  return;
}


// ================================================================================================
// sub_a6672 @ 0xa6672 [__cdecl]
// ================================================================================================

void sub_a6672(int param_1)

{
  (&byte_d6774)[param_1] = 0;
  return;
}


// ================================================================================================
// sub_a6684 @ 0xa6684 [__cdecl]
// ================================================================================================

void sub_a6684(int param_1,int param_2,int param_3,int param_4)

{
  ushort uVar1;
  int iVar2;
  
  if (*(char *)(param_2 + 1) != '\0') {
    if (*(char *)(param_4 + 0x35) == '\x01') {
      byte_d6770 = *(char *)(param_2 + 0x22) + *(char *)(param_2 + 3);
      uVar1 = *(ushort *)(&unk_d6608 + (uint)byte_d6770 * 2);
    }
    else {
      uVar1 = *(ushort *)(param_2 + 4);
      byte_d6770 = *(byte *)(param_2 + 3);
    }
    iVar2 = (uint)uVar1 - (int)*(char *)(param_4 + 0x11);
    if (*(short *)(param_3 + 0x26) != 0) {
      if (*(short *)(param_3 + 0x26) < 0) {
        iVar2 = iVar2 + (int)(((ulonglong)
                               ((uint)*(ushort *)
                                       (&unk_d6608 +
                                       (uint)(byte)(byte_d6770 - *(char *)(param_4 + 0x12)) * 2) -
                               iVar2) * (ulonglong)-(uint)*(ushort *)(param_3 + 0x26)) / 0x1f80);
      }
      else {
        iVar2 = iVar2 - (int)(((ulonglong)
                               (iVar2 - (uint)*(ushort *)
                                               (&unk_d6608 +
                                               (uint)(byte)(byte_d6770 + *(char *)(param_4 + 0x12))
                                               * 2)) * (ulonglong)*(ushort *)(param_3 + 0x26)) /
                             0x1f80);
      }
    }
    if (*(char *)(param_4 + 0x28) == '\x02') {
      iVar2 = iVar2 + *(int *)(param_2 + 0x1c);
    }
    if (*(char *)(param_4 + 0x19) == '\x02') {
      iVar2 = iVar2 + *(int *)(param_2 + 0x14);
    }
    *(short *)(&unk_d677b + param_1 * 2) = (short)iVar2;
    *(int *)(param_2 + 6) = iVar2;
    return;
  }
  return;
}


// ================================================================================================
// sub_a677b @ 0xa677b [__cdecl]
// ================================================================================================

void sub_a677b(void)

{
  byte bVar1;
  undefined2 uVar2;
  int iVar3;
  int iVar4;
  
  byte_d678c = byte_d6774;
  iVar3 = 4;
  iVar4 = 4;
  do {
    if ((&byte_d6785)[iVar4] == '\0') {
      (&byte_d678c)[iVar4] = 0;
    }
    else {
      (&byte_d678c)[iVar4] = (&byte_d6774)[iVar4];
    }
    iVar4 = iVar4 + -1;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  if (byte_d678c == '\0') {
    if ((byte_d678f == '\0' && byte_d6790 == '\0') ||
       (((byte_d679a & 2) != 0 && (byte_d678d != '\0' || byte_d678e != '\0')))) {
      uVar2 = word_d677d;
      if ((byte_d678d == '\0') && (uVar2 = word_d677f, byte_d678e == '\0')) {
        bVar1 = in(0x61);
        out(0x61,bVar1 & 0xfe);
        goto LAB_000a684a;
      }
    }
    else {
      uVar2 = word_d6783;
      if (byte_d678f != '\0') {
        uVar2 = word_d6781;
      }
    }
    out(0x42,(char)uVar2);
    out(0x42,(char)((ushort)uVar2 >> 8));
    bVar1 = in(0x61);
    out(0x61,bVar1 | 3);
  }
LAB_000a684a:
  byte_d679a = byte_d679a + 1;
  return;
}


// ================================================================================================
// sub_a6858 @ 0xa6858 [__watcall]
// ================================================================================================

undefined6 __watcall sub_a6858(undefined4 param_1,short unaff_DX)

{
  int iVar1;
  
  out(unaff_DX,(char)param_1);
  iVar1 = dword_d67a0;
  do {
    in(unaff_DX);
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  out(unaff_DX + 1,(char)((uint)param_1 >> 8));
  iVar1 = dword_d67a4;
  do {
    in(unaff_DX);
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return CONCAT24(unaff_DX,param_1);
}


// ================================================================================================
// sub_a687d @ 0xa687d [__watcall]
// ================================================================================================

void __watcall sub_a687d(void)

{
  char cVar1;
  undefined2 uVar2;
  undefined *puVar3;
  undefined *puVar4;
  undefined6 uVar5;
  
  cVar1 = '\x01';
  uVar2 = word_d679c;
  do {
    uVar5 = sub_a6858(cVar1,uVar2);
    uVar2 = (undefined2)((uint6)uVar5 >> 0x20);
    cVar1 = (char)uVar5 + '\x01';
  } while (cVar1 != -10);
  sub_a6858(0x2001);
  cVar1 = '\0';
  puVar3 = &unk_d68fc;
  puVar4 = &unk_d69ff;
  do {
    *puVar3 = 0;
    *puVar4 = 0;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
    cVar1 = cVar1 + '\x01';
  } while (cVar1 != '\0');
  do {
    cVar1 = sub_a6957();
  } while ((char)(cVar1 + '\x01') < -0x6a);
  sub_a68c9();
  return;
}


// ================================================================================================
// sub_a68c9 @ 0xa68c9 [__watcall]
// ================================================================================================

void __watcall sub_a68c9(void)

{
  char cVar1;
  char extraout_AH;
  char extraout_AH_00;
  char cVar2;
  char extraout_AH_01;
  char extraout_AH_02;
  undefined2 extraout_DX;
  undefined2 extraout_DX_00;
  undefined2 uVar3;
  char *pcVar4;
  char *pcVar5;
  
  cVar1 = ' ';
  pcVar4 = &unk_d691c;
  pcVar5 = &unk_d6a1f;
  uVar3 = word_d679c;
  do {
    cVar2 = *pcVar4;
    if (cVar2 != *pcVar5) {
      cVar1 = sub_a6858(cVar1,uVar3);
      cVar2 = extraout_AH;
      uVar3 = extraout_DX;
    }
    *pcVar5 = cVar2;
    pcVar4 = pcVar4 + 1;
    pcVar5 = pcVar5 + 1;
    cVar1 = cVar1 + '\x01';
  } while (cVar1 != -0x6a);
  cVar1 = -0x43;
  pcVar4 = &unk_d69b9;
  pcVar5 = &unk_d6abc;
  do {
    cVar2 = *pcVar4;
    if (cVar2 != *pcVar5) {
      cVar1 = sub_a6858(cVar1,uVar3);
      cVar2 = extraout_AH_00;
      uVar3 = extraout_DX_00;
    }
    *pcVar5 = cVar2;
    pcVar4 = pcVar4 + 1;
    pcVar5 = pcVar5 + 1;
    cVar1 = cVar1 + '\x01';
  } while (cVar1 != -10);
  cVar1 = -0x60;
  pcVar4 = &unk_d699c;
  pcVar5 = &unk_d6a9f;
  do {
    if ((*pcVar4 != *pcVar5) || (pcVar4[0x10] != pcVar5[0x10])) {
      cVar1 = sub_a6858(cVar1 + '\x10');
      pcVar5[0x10] = extraout_AH_01;
      cVar1 = sub_a6858(cVar1 + -0x10);
      *pcVar5 = extraout_AH_02;
    }
    pcVar4 = pcVar4 + 1;
    pcVar5 = pcVar5 + 1;
    cVar1 = cVar1 + '\x01';
  } while (cVar1 != -0x57);
  return;
}


// ================================================================================================
// sub_a6957 @ 0xa6957 [__watcall]
// ================================================================================================

uint __watcall sub_a6957(uint param_1)

{
  if (((byte)param_1 < 0x20) || (0xf5 < (byte)param_1)) {
    param_1 = sub_a6858(param_1,word_d679c);
  }
  else {
    (&unk_d68fc)[param_1 & 0xff] = (char)(param_1 >> 8);
  }
  return param_1;
}


// ================================================================================================
// sub_a6983 @ 0xa6983 [__watcall]
// ================================================================================================

uint __watcall sub_a6983(uint param_1)

{
  if ((0x1f < (byte)param_1) && ((byte)param_1 < 0xf6)) {
    param_1 = (uint)(byte)(&unk_d68fc)[param_1 & 0xff];
  }
  return param_1;
}


// ================================================================================================
// sub_a699d @ 0xa699d [__cdecl]
// ================================================================================================

void sub_a699d(ushort param_1)

{
  char cVar1;
  char cVar2;
  char *pcVar3;
  char *pcVar4;
  undefined2 in_SS;
  undefined auStack_6 [2];
  
  if (8 < param_1) {
    segment(in_SS,(short)auStack_6);
    return;
  }
  cVar2 = (&unk_d67a8)[param_1];
  cVar1 = '\n';
  pcVar3 = &unk_d67b4;
  do {
    pcVar4 = pcVar3 + 1;
    sub_a6957(*pcVar3 + cVar2);
    cVar1 = cVar1 + -1;
    pcVar3 = pcVar4;
  } while (cVar1 != '\0');
  cVar2 = '\x03';
  do {
    sub_a6957(*pcVar4 + (char)param_1);
    cVar2 = cVar2 + -1;
    pcVar4 = pcVar4 + 1;
  } while (cVar2 != '\0');
  segment(in_SS,(short)auStack_6);
  return;
}


// ================================================================================================
// sub_a69e8 @ 0xa69e8 [__cdecl]
// ================================================================================================

void sub_a69e8(undefined2 param_1)

{
  word_d679c = param_1;
  sub_a687d();
  return;
}


// ================================================================================================
// sub_a69fb @ 0xa69fb [__watcall]
// ================================================================================================

void __watcall sub_a69fb(void)

{
  sub_a687d();
  return;
}


// ================================================================================================
// sub_a6a01 @ 0xa6a01 [__watcall]
// ================================================================================================

undefined8 __watcall sub_a6a01(void)

{
  return 0x388;
}


// ================================================================================================
// sub_a6a09 @ 0xa6a09 [__cdecl]
// ================================================================================================

bool sub_a6a09(undefined2 param_1)

{
  undefined in_CF;
  
  word_d679c = param_1;
  dword_d67a0 = 0x20;
  dword_d67a4 = 0x8c;
  sub_a6a42();
  if (!(bool)in_CF) {
    sub_a6ac2(0);
  }
  return !(bool)in_CF;
}


// ================================================================================================
// sub_a6a42 @ 0xa6a42 [__watcall]
// ================================================================================================

undefined6 __watcall
sub_a6a42(undefined2 param_1,undefined2 unaff_DX,undefined4 param_3,undefined2 unaff_CX)

{
  undefined2 *puVar1;
  undefined2 *puVar2;
  byte bVar3;
  undefined2 extraout_var;
  int iVar4;
  undefined2 extraout_DX;
  undefined2 extraout_DX_00;
  short sVar5;
  undefined2 in_SS;
  undefined2 uStack_6;
  undefined2 uStack_4;
  undefined2 uStack_2;
  
  uStack_6 = unaff_DX;
  uStack_4 = unaff_CX;
  uStack_2 = param_1;
  sub_a6858(1,word_d679c);
  sub_a6858(0x6004);
  sub_a6858(0x8004);
  in(extraout_DX);
  sub_a6858(0xff02);
  sub_a6858(0x2104);
  iVar4 = 50000;
  do {
    bVar3 = in(extraout_DX_00);
    if ((bVar3 & 0xe0) == 0xc0) break;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  sub_a6858(0x6004);
  sub_a6858(0x8004);
  sVar5 = (short)&uStack_6;
  puVar1 = (undefined2 *)segment(in_SS,sVar5);
  segment(in_SS,sVar5 + 2);
  puVar2 = (undefined2 *)segment(in_SS,sVar5 + 4);
  return CONCAT24(*puVar1,CONCAT22(extraout_var,*puVar2));
}


// ================================================================================================
// sub_a6ac2 @ 0xa6ac2 [__watcall]
// ================================================================================================

undefined8 __watcall sub_a6ac2(void)

{
  undefined2 *puVar1;
  ushort *puVar2;
  byte bVar3;
  undefined uVar4;
  undefined uVar5;
  int iVar6;
  short sVar7;
  undefined2 in_SS;
  undefined auStack_6 [6];
  
  bVar3 = in(0x61);
  out(0x61,bVar3 & 0xfe);
  out(0x43,0xb0);
  out(0x42,0);
  out(0x42,0);
  bVar3 = in(0x61);
  out(0x61,bVar3 | 1);
  iVar6 = 1000;
  do {
    in(word_d679c);
    iVar6 = iVar6 + -1;
  } while (iVar6 != 0);
  bVar3 = in(0x61);
  out(0x61,bVar3 & 0xfe);
  uVar4 = in(0x42);
  uVar5 = in(0x42);
  sVar7 = (short)auStack_6;
  puVar1 = (undefined2 *)segment(in_SS,sVar7);
  segment(in_SS,sVar7 + 2);
  puVar2 = (ushort *)segment(in_SS,sVar7 + 4);
  return CONCAT44(CONCAT22((short)(30000U % (ulonglong)-(uint)CONCAT11(uVar5,uVar4) >> 0x10),*puVar1
                          ),(uint)*puVar2);
}


// ================================================================================================
// sub_a6b32 @ 0xa6b32 [__watcall]
// ================================================================================================

uint __watcall sub_a6b32(void)

{
  byte in_stack_00000004;
  char in_stack_00000008;
  
  return (uint)*(ushort *)
                (&unk_d67f4 + (short)(char)(in_stack_00000004 % 0xc + in_stack_00000008) * 2) |
         (uint)(ushort)(in_stack_00000004 / 0xc) << 10;
}


// ================================================================================================
// sub_a6b5d @ 0xa6b5d [__cdecl]
// ================================================================================================

undefined2 sub_a6b5d(byte param_1)

{
  return *(undefined2 *)(&unk_d683c + ((param_1 & 0x7c) >> 1));
}


// ================================================================================================
// sub_a6b73 @ 0xa6b73 [__cdecl]
// ================================================================================================

undefined2 sub_a6b73(byte param_1)

{
  return *(undefined2 *)(&unk_d687c + (param_1 & 0x7e));
}


// ================================================================================================
// sub_a6b87 @ 0xa6b87 [__watcall]
// ================================================================================================

undefined8 __watcall sub_a6b87(char *param_1,undefined4 unaff_EDX)

{
  char cVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int *piVar6;
  char *pcVar7;
  
  if ((dword_d5444 != (int *)0x0) && (param_1 != (char *)0x0)) {
    uVar4 = 0xffffffff;
    pcVar7 = param_1;
    do {
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      cVar1 = *pcVar7;
      pcVar7 = pcVar7 + 1;
    } while (cVar1 != '\0');
    iVar5 = ~uVar4 - 1;
    for (piVar6 = dword_d5444; iVar3 = *piVar6, iVar3 != 0; piVar6 = piVar6 + 1) {
      iVar2 = sub_909e0(iVar3,param_1,iVar5);
      if ((iVar2 == 0) && (*(char *)(iVar3 + iVar5) == '=')) {
        iVar3 = ~uVar4 + iVar3;
        goto LAB_000a6bda;
      }
    }
  }
  iVar3 = 0;
LAB_000a6bda:
  return CONCAT44(unaff_EDX,iVar3);
}


// ================================================================================================
// sub_a6be1 @ 0xa6be1 [__watcall]
// ================================================================================================

uint __watcall sub_a6be1(char *param_1,undefined4 *unaff_EDX,int unaff_EBX,int unaff_ECX)

{
  char cVar1;
  bool bVar2;
  uint uVar3;
  char *pcVar4;
  char *pcVar5;
  uint uVar6;
  undefined8 uVar7;
  
  pcVar4 = param_1;
  if (unaff_EDX != (undefined4 *)0x0) {
    *unaff_EDX = param_1;
  }
  while (((&unk_c4b6c)[(byte)(*pcVar4 + 1)] & 2) != 0) {
    pcVar4 = pcVar4 + 1;
  }
  cVar1 = *pcVar4;
  if ((cVar1 == '+') || (cVar1 == '-')) {
    pcVar4 = pcVar4 + 1;
  }
  if (unaff_EBX == 0) {
    if ((*pcVar4 == '0') && ((pcVar4[1] == 'x' || (pcVar4[1] == 'X')))) {
      unaff_EBX = 0x10;
    }
    else if (*pcVar4 == '0') {
      unaff_EBX = 8;
    }
    else {
      unaff_EBX = 10;
    }
  }
  if ((unaff_EBX < 2) || (0x24 < unaff_EBX)) {
    sub_9878a(0xd);
    uVar3 = 0;
  }
  else {
    if (((unaff_EBX == 0x10) && (*pcVar4 == '0')) && ((pcVar4[1] == 'x' || (pcVar4[1] == 'X')))) {
      pcVar4 = pcVar4 + 2;
    }
    bVar2 = false;
    pcVar5 = pcVar4;
    uVar3 = 0;
    while( true ) {
      uVar7 = sub_a6d2c(*pcVar5);
      pcVar5 = (char *)((ulonglong)uVar7 >> 0x20);
      if (unaff_EBX <= (int)uVar7) break;
      uVar6 = uVar3 * unaff_EBX + (int)uVar7;
      if (uVar6 < uVar3) {
        bVar2 = true;
      }
      pcVar5 = pcVar5 + 1;
      uVar3 = uVar6;
    }
    if (pcVar5 == pcVar4) {
      pcVar5 = param_1;
    }
    if (unaff_EDX != (undefined4 *)0x0) {
      *unaff_EDX = pcVar5;
    }
    if (((unaff_ECX == 1) && (0x7fffffff < uVar3)) && ((uVar3 != 0x80000000 || (cVar1 != '-')))) {
      bVar2 = true;
    }
    if (bVar2) {
      sub_9878a(0xe);
      if (unaff_ECX == 0) {
        uVar3 = 0xffffffff;
      }
      else if (cVar1 == '-') {
        uVar3 = 0x80000000;
      }
      else {
        uVar3 = 0x7fffffff;
      }
    }
    else if (cVar1 == '-') {
      uVar3 = -uVar3;
    }
  }
  return uVar3;
}


// ================================================================================================
// sub_a6d1a @ 0xa6d1a [__watcall]
// ================================================================================================

void __watcall sub_a6d1a(void)

{
  sub_a6be1();
  return;
}


// ================================================================================================
// sub_a6d24 @ 0xa6d24 [__watcall]
// ================================================================================================

void __watcall sub_a6d24(void)

{
  sub_a6be1();
  return;
}


// ================================================================================================
// sub_a6d2c @ 0xa6d2c [__watcall]
// ================================================================================================

undefined8 __watcall sub_a6d2c(byte param_1,undefined4 unaff_EDX)

{
  byte bVar1;
  
  if ((0x2f < param_1) && (param_1 < 0x3a)) {
    return CONCAT44(unaff_EDX,param_1 - 0x30);
  }
  bVar1 = sub_9afb0(param_1);
  if ((0x60 < bVar1) && (bVar1 < 0x6a)) {
    return CONCAT44(unaff_EDX,bVar1 - 0x57);
  }
  if (((bVar1 < 0x6a) || (0x72 < bVar1)) && ((bVar1 < 0x73 || (0x7a < bVar1)))) {
    return CONCAT44(unaff_EDX,0x25);
  }
  return CONCAT44(unaff_EDX,bVar1 - 0x57);
}


// ================================================================================================
// sub_a6d84 @ 0xa6d84 [__watcall]
// ================================================================================================

void __watcall sub_a6d84(void)

{
  uint unaff_ESI;
  
  if (3 < unaff_ESI) {
    return;
  }
  return;
}


// ================================================================================================
// sub_a6d8d @ 0xa6d8d [__watcall]
// ================================================================================================

undefined8 __watcall sub_a6d8d(undefined4 param_1,undefined4 unaff_EDX)

{
  return CONCAT44(unaff_EDX,dword_a9c8a / 0x100);
}


// ================================================================================================
// sub_a6da0 @ 0xa6da0 [__cdecl]
// ================================================================================================

undefined4 sub_a6da0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  
  sub_a6df8();
  iVar1 = 4;
  iVar2 = 0;
  do {
    (&off_d71f0)[iVar2][1] = 0xff;
    iVar2 = iVar2 + 1;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  iVar1 = sub_a9bd0(param_2,param_3,param_4);
  if (iVar1 != -1) {
    return 0x44;
  }
  return 0xffffffff;
}


// ================================================================================================
// sub_a6ded @ 0xa6ded [__watcall]
// ================================================================================================

void __watcall sub_a6ded(void)

{
  sub_a6df8();
  sub_a9c1b();
  return;
}


// ================================================================================================
// sub_a6df8 @ 0xa6df8 [__watcall]
// ================================================================================================

void __watcall sub_a6df8(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = 4;
  iVar2 = 0;
  do {
    *(&off_d71f0)[iVar2] = 0;
    iVar2 = iVar2 + 1;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return;
}


// ================================================================================================
// sub_a6e10 @ 0xa6e10 [__cdecl]
// ================================================================================================

void sub_a6e10(int param_1,char param_2,undefined4 param_3)

{
  undefined *puVar1;
  ulonglong uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 unaff_EBX;
  undefined in_CF;
  
  sub_a6d84(param_3);
  if (!(bool)in_CF) {
    puVar1 = (&off_d71f0)[param_1];
    puVar1[2] = param_2;
    if (param_2 != -1) {
      uVar2 = (ulonglong)*(uint *)(&unk_d6b00 + CONCAT31((int3)((uint)unaff_EBX >> 8),param_2) * 4)
              * (ulonglong)*(uint *)(puVar1 + 0x20) & 0xffffffff0000;
      uVar3 = (undefined4)uVar2;
      uVar4 = (undefined4)(uVar2 >> 0x20);
      *(undefined4 *)(puVar1 + 0x34) = uVar4;
      *(undefined4 *)(puVar1 + 0x38) = uVar3;
      *(undefined4 *)(puVar1 + 0x24) = uVar4;
      *(undefined4 *)(puVar1 + 0x28) = uVar3;
    }
    *(undefined4 *)(puVar1 + 0x18) = *(undefined4 *)(puVar1 + 0xc);
    uVar3 = *(undefined4 *)(puVar1 + 0x10);
    if (*(int *)(puVar1 + 4) == 0) {
      uVar3 = *(undefined4 *)(puVar1 + 0x14);
    }
    *(undefined4 *)(puVar1 + 0x1c) = uVar3;
    *(undefined4 *)(puVar1 + 0x2c) = *(undefined4 *)(puVar1 + 8);
    *(undefined4 *)(puVar1 + 0x30) = 0;
    *puVar1 = 1;
  }
  return;
}


// ================================================================================================
// sub_a6e7b @ 0xa6e7b [__watcall]
// ================================================================================================

void __watcall sub_a6e7b(void)

{
  undefined *puVar1;
  undefined in_CF;
  int in_stack_00000004;
  
  sub_a6d84();
  if ((!(bool)in_CF) && (1 < in_stack_00000004)) {
    puVar1 = (&off_d71f0)[in_stack_00000004];
    *(undefined4 *)(puVar1 + 0x1c) = *(undefined4 *)(puVar1 + 0x10);
    *puVar1 = 0;
  }
  return;
}


// ================================================================================================
// sub_a6ea2 @ 0xa6ea2 [__cdecl]
// ================================================================================================

void sub_a6ea2(int param_1)

{
  undefined in_CF;
  
  sub_a6d84();
  if ((!(bool)in_CF) && (1 < param_1)) {
    *(&off_d71f0)[param_1] = 0;
  }
  return;
}


// ================================================================================================
// sub_a6ec3 @ 0xa6ec3 [__cdecl]
// ================================================================================================

void sub_a6ec3(int param_1,int param_2)

{
  undefined *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined in_CF;
  
  sub_a6d84();
  if (!(bool)in_CF) {
    puVar1 = (&off_d71f0)[param_1];
    if ((char)param_2 != puVar1[1]) {
      puVar1[1] = (char)param_2;
      iVar2 = 0;
      iVar4 = param_2 * -0x100;
      puVar1[0x44] = 0;
      puVar1[0xc4] = -(char)param_2;
      iVar3 = 0x7f;
      puVar1 = puVar1 + 0x44;
      do {
        iVar2 = iVar2 + (uint)(byte)((char)param_2 << 1);
        puVar1[1] = (char)((uint)iVar2 >> 8);
        iVar4 = iVar4 + (uint)(byte)((char)param_2 << 1);
        puVar1[0x81] = (char)((uint)iVar4 >> 8);
        iVar3 = iVar3 + -1;
        puVar1 = puVar1 + 1;
      } while (iVar3 != 0);
    }
  }
  return;
}


// ================================================================================================
// sub_a6f1b @ 0xa6f1b [__watcall]
// ================================================================================================

void __watcall sub_a6f1b(void)

{
  undefined in_CF;
  ushort in_stack_00000004;
  undefined2 in_stack_00000008;
  
  sub_a6d84();
  if (!(bool)in_CF) {
    *(undefined2 *)((&off_d71f0)[in_stack_00000004] + 0x3c) = in_stack_00000008;
  }
  return;
}


// ================================================================================================
// sub_a6f3c @ 0xa6f3c [__cdecl]
// ================================================================================================

void sub_a6f3c(int param_1,uint param_2)

{
  undefined *puVar1;
  ulonglong uVar2;
  uint uVar3;
  uint uVar4;
  undefined4 uVar5;
  undefined in_CF;
  
  sub_a6d84();
  uVar4 = dword_a9c8a;
  if (!(bool)in_CF) {
    puVar1 = (&off_d71f0)[param_1];
    uVar2 = (ulonglong)dword_a9c8a;
    uVar3 = param_2 / dword_a9c8a;
    *(uint *)(puVar1 + 0x34) = uVar3;
    *(uint *)(puVar1 + 0x24) = uVar3;
    uVar4 = (uint)(((ulonglong)param_2 % uVar2 << 0x20) / (ulonglong)uVar4);
    *(uint *)(puVar1 + 0x38) = uVar4;
    *(uint *)(puVar1 + 0x28) = uVar4;
    *(uint *)(puVar1 + 0x20) = (uVar4 & 0xffff0000 | uVar3) >> 0x10 | uVar3 << 0x10;
    if (*(uint *)(puVar1 + 0x20) == 0x10000) {
      uVar5 = 0x80;
    }
    else if (*(uint *)(puVar1 + 0x20) < 0x10001) {
      uVar5 = 0x40;
    }
    else {
      uVar5 = 0x100;
    }
    *(undefined4 *)(puVar1 + 0x40) = uVar5;
  }
  return;
}


// ================================================================================================
// sub_a6fa2 @ 0xa6fa2 [__cdecl]
// ================================================================================================

void sub_a6fa2(int param_1,int param_2,int param_3,int param_4,int param_5)

{
  undefined *puVar1;
  undefined in_CF;
  
  sub_a6d84();
  if (!(bool)in_CF) {
    puVar1 = (&off_d71f0)[param_1];
    puVar1[3] = 0;
    *(int *)(puVar1 + 8) = param_2;
    *(int *)(puVar1 + 0x14) = param_3 + param_2;
    *(int *)(puVar1 + 0xc) = param_4 + param_2;
    *(int *)(puVar1 + 0x10) = param_4 + param_2 + param_5;
    *(int *)(puVar1 + 4) = param_5;
  }
  return;
}


// ================================================================================================
// sub_a6fe1 @ 0xa6fe1 [__cdecl]
// ================================================================================================

int sub_a6fe1(int param_1,byte *param_2,undefined4 param_3,uint param_4,undefined4 param_5,
             int param_6,undefined4 param_7,int param_8)

{
  byte bVar1;
  undefined *puVar2;
  int iVar3;
  char cVar4;
  byte in_CF;
  byte in_PF;
  byte in_AF;
  byte in_ZF;
  byte in_SF;
  byte in_TF;
  byte in_IF;
  byte in_OF;
  byte in_NT;
  byte in_AC;
  byte in_VIF;
  byte in_VIP;
  byte in_ID;
  uint uVar5;
  
  uVar5 = (uint)(in_NT & 1) * 0x4000 | (uint)(in_OF & 1) * 0x800 | (uint)(in_IF & 1) * 0x200 |
          (uint)(in_TF & 1) * 0x100 | (uint)(in_SF & 1) * 0x80 | (uint)(in_ZF & 1) * 0x40 |
          (uint)(in_AF & 1) * 0x10 | (uint)(in_PF & 1) * 4 | (uint)(in_CF & 1) |
          (uint)(in_ID & 1) * 0x200000 | (uint)(in_VIP & 1) * 0x100000 |
          (uint)(in_VIF & 1) * 0x80000 | (uint)(in_AC & 1) * 0x40000;
  iVar3 = sub_a6d84();
  if (!(bool)in_CF) {
    puVar2 = (&off_d71f0)[param_1];
    if (param_6 == 0) {
      sub_a6e7b();
      return param_1;
    }
    sub_a6f3c(param_1,param_6,uVar5);
    sub_a6ec3(param_1,param_7);
    sub_a6fa2(param_1,param_2,param_3,param_4,param_5);
    puVar2[0x3e] = 0;
    puVar2[0x3f] = 0;
    puVar2[3] = (char)param_8;
    if ((param_8 != 0) && (param_4 != 0)) {
      cVar4 = '\0';
      uVar5 = 0;
      do {
        bVar1 = *param_2;
        param_2 = param_2 + 1;
        cVar4 = cVar4 + (char)*(undefined2 *)(&unk_d7414 + (uint)bVar1 * 2) +
                (char)((ushort)*(undefined2 *)(&unk_d7414 + (uint)bVar1 * 2) >> 8);
        uVar5 = uVar5 + 1;
      } while (uVar5 < param_4);
      puVar2[0x3f] = cVar4;
    }
    iVar3 = sub_a6e10(param_1,0xff,0x7f);
  }
  return iVar3;
}


// ================================================================================================
// sub_a7094 @ 0xa7094 [__cdecl]
// ================================================================================================

undefined4 sub_a7094(int param_1)

{
  undefined in_CF;
  
  sub_a6d84();
  if ((!(bool)in_CF) && (*(&off_d71f0)[param_1] != '\0')) {
    return 0;
  }
  return 1;
}


// ================================================================================================
// sub_a70bc @ 0xa70bc [__watcall]
// ================================================================================================

undefined __watcall sub_a70bc(void)

{
  undefined in_CF;
  int in_stack_00000004;
  
  sub_a6d84();
  if (!(bool)in_CF) {
    return (&off_d71f0)[in_stack_00000004][1];
  }
  return 0;
}


// ================================================================================================
// sub_a70dd @ 0xa70dd [__cdecl]
// ================================================================================================

void sub_a70dd(int param_1,undefined4 param_2,int param_3,uint param_4,char param_5)

{
  undefined *puVar1;
  longlong lVar2;
  uint uVar3;
  uint uVar4;
  undefined in_CF;
  
  sub_a6d84(param_2);
  if (!(bool)in_CF) {
    puVar1 = (&off_d71f0)[param_1];
    uVar4 = ((*(uint *)(puVar1 + 0x28) | *(uint *)(puVar1 + 0x24)) >> 0x10 |
            (*(uint *)(puVar1 + 0x28) | *(uint *)(puVar1 + 0x24)) << 0x10) + param_3;
    if (param_4 != 0) {
      uVar3 = ((uint)((ulonglong)*(uint *)(&unk_d6b00 + (uint)(byte)(puVar1[2] + param_5) * 4) *
                     (ulonglong)*(uint *)(puVar1 + 0x20)) >> 0x10 |
              (int)((ulonglong)*(uint *)(&unk_d6b00 + (uint)(byte)(puVar1[2] + param_5) * 4) *
                    (ulonglong)*(uint *)(puVar1 + 0x20) >> 0x20) << 0x10) - uVar4;
      if (((int)param_4 < 1) && ((int)param_4 < 0)) {
        lVar2 = (ulonglong)uVar3 * (ulonglong)-param_4;
        uVar4 = uVar4 - ((uint)lVar2 >> 0xe | (int)((ulonglong)lVar2 >> 0x20) << 0x12);
      }
      else {
        lVar2 = (ulonglong)uVar3 * (ulonglong)param_4;
        uVar4 = uVar4 + ((uint)lVar2 >> 0xe | (int)((ulonglong)lVar2 >> 0x20) << 0x12);
      }
    }
    *(uint *)(puVar1 + 0x38) = uVar4 << 0x10;
    *(uint *)(puVar1 + 0x34) = uVar4 >> 0x10;
  }
  return;
}


// ================================================================================================
// sub_a715c @ 0xa715c [__watcall]
// ================================================================================================

void __watcall sub_a715c(undefined4 param_1,uint unaff_EDX,int unaff_EBX,uint unaff_ECX)

{
  uint uVar1;
  uint uVar2;
  byte *unaff_ESI;
  byte *pbVar3;
  int unaff_EDI;
  
  word_d7214 = word_d7214 + *(char *)(unaff_EBX + (uint)*unaff_ESI);
  pbVar3 = unaff_ESI + (uint)CARRY4(unaff_ECX,unaff_EDX) + unaff_EDI;
  word_d7216 = word_d7216 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = unaff_ECX + unaff_EDX + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(unaff_ECX + unaff_EDX,unaff_EDX) + unaff_EDI;
  word_d7218._0_2_ = (short)word_d7218 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7218._2_2_ = word_d7218._2_2_ + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d721c = word_d721c + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d721e = word_d721e + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7220 = word_d7220 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7222 = word_d7222 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7224 = word_d7224 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7226 = word_d7226 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7228 = word_d7228 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d722a = word_d722a + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d722c = word_d722c + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d722e = word_d722e + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7230 = word_d7230 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7232 = word_d7232 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7234 = word_d7234 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7236 = word_d7236 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7238 = word_d7238 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d723a = word_d723a + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d723c = word_d723c + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d723e = word_d723e + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7240 = word_d7240 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7242 = word_d7242 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7244 = word_d7244 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7246 = word_d7246 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7248 = word_d7248 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d724a = word_d724a + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d724c = word_d724c + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d724e = word_d724e + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7250 = word_d7250 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7252 = word_d7252 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7254 = word_d7254 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7256 = word_d7256 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7258 = word_d7258 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d725a = word_d725a + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d725c = word_d725c + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d725e = word_d725e + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7260 = word_d7260 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7262 = word_d7262 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7264 = word_d7264 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7266 = word_d7266 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7268 = word_d7268 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d726a = word_d726a + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d726c = word_d726c + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d726e = word_d726e + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7270 = word_d7270 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7272 = word_d7272 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7274 = word_d7274 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7276 = word_d7276 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7278 = word_d7278 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d727a = word_d727a + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d727c = word_d727c + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d727e = word_d727e + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7280 = word_d7280 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7282 = word_d7282 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7284 = word_d7284 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7286 = word_d7286 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7288 = word_d7288 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d728a = word_d728a + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d728c = word_d728c + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d728e = word_d728e + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7290 = word_d7290 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7292 = word_d7292 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7294 = word_d7294 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7296 = word_d7296 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7298 = word_d7298 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d729a = word_d729a + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d729c = word_d729c + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d729e = word_d729e + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d72a0 = word_d72a0 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d72a2 = word_d72a2 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d72a4 = word_d72a4 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d72a6 = word_d72a6 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d72a8 = word_d72a8 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d72aa = word_d72aa + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d72ac = word_d72ac + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d72ae = word_d72ae + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d72b0 = word_d72b0 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d72b2 = word_d72b2 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d72b4 = word_d72b4 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d72b6 = word_d72b6 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d72b8 = word_d72b8 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d72ba = word_d72ba + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d72bc = word_d72bc + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d72be = word_d72be + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d72c0 = word_d72c0 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d72c2 = word_d72c2 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d72c4 = word_d72c4 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d72c6 = word_d72c6 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d72c8 = word_d72c8 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d72ca = word_d72ca + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d72cc = word_d72cc + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d72ce = word_d72ce + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d72d0 = word_d72d0 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d72d2 = word_d72d2 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d72d4 = word_d72d4 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d72d6 = word_d72d6 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d72d8 = word_d72d8 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d72da = word_d72da + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d72dc = word_d72dc + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d72de = word_d72de + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d72e0 = word_d72e0 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d72e2 = word_d72e2 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d72e4 = word_d72e4 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d72e6 = word_d72e6 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d72e8 = word_d72e8 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d72ea = word_d72ea + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d72ec = word_d72ec + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d72ee = word_d72ee + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d72f0 = word_d72f0 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d72f2 = word_d72f2 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d72f4 = word_d72f4 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d72f6 = word_d72f6 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d72f8 = word_d72f8 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d72fa = word_d72fa + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d72fc = word_d72fc + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d72fe = word_d72fe + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7300 = word_d7300 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7302 = word_d7302 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7304 = word_d7304 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7306 = word_d7306 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7308 = word_d7308 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d730a = word_d730a + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d730c = word_d730c + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d730e = word_d730e + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7310 = word_d7310 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7312 = word_d7312 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7314 = word_d7314 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7316 = word_d7316 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7318 = word_d7318 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d731a = word_d731a + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d731c = word_d731c + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d731e = word_d731e + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7320 = word_d7320 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7322 = word_d7322 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7324 = word_d7324 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7326 = word_d7326 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7328 = word_d7328 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d732a = word_d732a + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d732c = word_d732c + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d732e = word_d732e + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7330 = word_d7330 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7332 = word_d7332 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7334 = word_d7334 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7336 = word_d7336 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7338 = word_d7338 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d733a = word_d733a + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d733c = word_d733c + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d733e = word_d733e + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7340 = word_d7340 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7342 = word_d7342 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7344 = word_d7344 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7346 = word_d7346 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7348 = word_d7348 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d734a = word_d734a + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d734c = word_d734c + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d734e = word_d734e + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7350 = word_d7350 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7352 = word_d7352 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7354 = word_d7354 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7356 = word_d7356 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7358 = word_d7358 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d735a = word_d735a + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d735c = word_d735c + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d735e = word_d735e + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7360 = word_d7360 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7362 = word_d7362 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7364 = word_d7364 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7366 = word_d7366 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7368 = word_d7368 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d736a = word_d736a + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d736c = word_d736c + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d736e = word_d736e + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7370 = word_d7370 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7372 = word_d7372 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7374 = word_d7374 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7376 = word_d7376 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7378 = word_d7378 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d737a = word_d737a + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d737c = word_d737c + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d737e = word_d737e + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7380 = word_d7380 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7382 = word_d7382 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7384 = word_d7384 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7386 = word_d7386 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7388 = word_d7388 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d738a = word_d738a + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d738c = word_d738c + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d738e = word_d738e + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7390 = word_d7390 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7392 = word_d7392 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7394 = word_d7394 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7396 = word_d7396 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7398 = word_d7398 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d739a = word_d739a + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d739c = word_d739c + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d739e = word_d739e + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d73a0 = word_d73a0 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d73a2 = word_d73a2 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d73a4 = word_d73a4 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d73a6 = word_d73a6 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d73a8 = word_d73a8 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d73aa = word_d73aa + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d73ac = word_d73ac + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d73ae = word_d73ae + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d73b0 = word_d73b0 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d73b2 = word_d73b2 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d73b4 = word_d73b4 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d73b6 = word_d73b6 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d73b8 = word_d73b8 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d73ba = word_d73ba + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d73bc = word_d73bc + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d73be = word_d73be + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d73c0 = word_d73c0 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d73c2 = word_d73c2 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d73c4 = word_d73c4 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d73c6 = word_d73c6 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d73c8 = word_d73c8 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d73ca = word_d73ca + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d73cc = word_d73cc + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d73ce = word_d73ce + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d73d0 = word_d73d0 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d73d2 = word_d73d2 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d73d4 = word_d73d4 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d73d6 = word_d73d6 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d73d8 = word_d73d8 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d73da = word_d73da + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d73dc = word_d73dc + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d73de = word_d73de + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d73e0 = word_d73e0 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d73e2 = word_d73e2 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d73e4 = word_d73e4 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d73e6 = word_d73e6 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d73e8 = word_d73e8 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d73ea = word_d73ea + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d73ec = word_d73ec + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d73ee = word_d73ee + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d73f0 = word_d73f0 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d73f2 = word_d73f2 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d73f4 = word_d73f4 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d73f6 = word_d73f6 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d73f8 = word_d73f8 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d73fa = word_d73fa + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d73fc = word_d73fc + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d73fe = word_d73fe + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7400 = word_d7400 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7402 = word_d7402 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7404 = word_d7404 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7406 = word_d7406 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7408 = word_d7408 + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d740a = word_d740a + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar1 = uVar2 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d740c = word_d740c + *(char *)(unaff_EBX + (uint)*pbVar3);
  uVar2 = uVar1 + unaff_EDX;
  pbVar3 = pbVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d740e = word_d740e + *(char *)(unaff_EBX + (uint)*pbVar3);
  word_d7410 = word_d7410 +
               *(char *)(unaff_EBX + (uint)pbVar3[(uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI]);
  word_d7412 = word_d7412 +
               *(char *)(unaff_EBX +
                        (uint)(pbVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI)
                              [(uint)CARRY4(uVar2 + unaff_EDX,unaff_EDX) + unaff_EDI]);
  return;
}


// ================================================================================================
// sub_a815d @ 0xa815d [__watcall]
// ================================================================================================

void __watcall sub_a815d(undefined4 param_1,uint unaff_EDX,undefined4 param_3,uint unaff_ECX)

{
  uint uVar1;
  uint uVar2;
  char *unaff_ESI;
  char *pcVar3;
  int unaff_EDI;
  
  word_d7214 = word_d7214 + *unaff_ESI;
  pcVar3 = unaff_ESI + (uint)CARRY4(unaff_ECX,unaff_EDX) + unaff_EDI;
  word_d7216 = word_d7216 + *pcVar3;
  uVar1 = unaff_ECX + unaff_EDX + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(unaff_ECX + unaff_EDX,unaff_EDX) + unaff_EDI;
  word_d7218._0_2_ = (short)word_d7218 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7218._2_2_ = word_d7218._2_2_ + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d721c = word_d721c + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d721e = word_d721e + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7220 = word_d7220 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7222 = word_d7222 + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7224 = word_d7224 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7226 = word_d7226 + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7228 = word_d7228 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d722a = word_d722a + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d722c = word_d722c + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d722e = word_d722e + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7230 = word_d7230 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7232 = word_d7232 + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7234 = word_d7234 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7236 = word_d7236 + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7238 = word_d7238 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d723a = word_d723a + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d723c = word_d723c + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d723e = word_d723e + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7240 = word_d7240 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7242 = word_d7242 + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7244 = word_d7244 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7246 = word_d7246 + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7248 = word_d7248 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d724a = word_d724a + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d724c = word_d724c + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d724e = word_d724e + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7250 = word_d7250 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7252 = word_d7252 + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7254 = word_d7254 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7256 = word_d7256 + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7258 = word_d7258 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d725a = word_d725a + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d725c = word_d725c + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d725e = word_d725e + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7260 = word_d7260 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7262 = word_d7262 + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7264 = word_d7264 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7266 = word_d7266 + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7268 = word_d7268 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d726a = word_d726a + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d726c = word_d726c + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d726e = word_d726e + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7270 = word_d7270 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7272 = word_d7272 + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7274 = word_d7274 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7276 = word_d7276 + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7278 = word_d7278 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d727a = word_d727a + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d727c = word_d727c + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d727e = word_d727e + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7280 = word_d7280 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7282 = word_d7282 + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7284 = word_d7284 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7286 = word_d7286 + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7288 = word_d7288 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d728a = word_d728a + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d728c = word_d728c + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d728e = word_d728e + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7290 = word_d7290 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7292 = word_d7292 + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7294 = word_d7294 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7296 = word_d7296 + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7298 = word_d7298 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d729a = word_d729a + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d729c = word_d729c + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d729e = word_d729e + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d72a0 = word_d72a0 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d72a2 = word_d72a2 + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d72a4 = word_d72a4 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d72a6 = word_d72a6 + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d72a8 = word_d72a8 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d72aa = word_d72aa + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d72ac = word_d72ac + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d72ae = word_d72ae + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d72b0 = word_d72b0 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d72b2 = word_d72b2 + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d72b4 = word_d72b4 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d72b6 = word_d72b6 + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d72b8 = word_d72b8 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d72ba = word_d72ba + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d72bc = word_d72bc + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d72be = word_d72be + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d72c0 = word_d72c0 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d72c2 = word_d72c2 + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d72c4 = word_d72c4 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d72c6 = word_d72c6 + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d72c8 = word_d72c8 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d72ca = word_d72ca + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d72cc = word_d72cc + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d72ce = word_d72ce + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d72d0 = word_d72d0 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d72d2 = word_d72d2 + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d72d4 = word_d72d4 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d72d6 = word_d72d6 + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d72d8 = word_d72d8 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d72da = word_d72da + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d72dc = word_d72dc + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d72de = word_d72de + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d72e0 = word_d72e0 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d72e2 = word_d72e2 + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d72e4 = word_d72e4 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d72e6 = word_d72e6 + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d72e8 = word_d72e8 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d72ea = word_d72ea + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d72ec = word_d72ec + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d72ee = word_d72ee + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d72f0 = word_d72f0 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d72f2 = word_d72f2 + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d72f4 = word_d72f4 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d72f6 = word_d72f6 + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d72f8 = word_d72f8 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d72fa = word_d72fa + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d72fc = word_d72fc + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d72fe = word_d72fe + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7300 = word_d7300 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7302 = word_d7302 + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7304 = word_d7304 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7306 = word_d7306 + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7308 = word_d7308 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d730a = word_d730a + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d730c = word_d730c + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d730e = word_d730e + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7310 = word_d7310 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7312 = word_d7312 + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7314 = word_d7314 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7316 = word_d7316 + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7318 = word_d7318 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d731a = word_d731a + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d731c = word_d731c + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d731e = word_d731e + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7320 = word_d7320 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7322 = word_d7322 + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7324 = word_d7324 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7326 = word_d7326 + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7328 = word_d7328 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d732a = word_d732a + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d732c = word_d732c + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d732e = word_d732e + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7330 = word_d7330 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7332 = word_d7332 + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7334 = word_d7334 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7336 = word_d7336 + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7338 = word_d7338 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d733a = word_d733a + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d733c = word_d733c + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d733e = word_d733e + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7340 = word_d7340 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7342 = word_d7342 + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7344 = word_d7344 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7346 = word_d7346 + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7348 = word_d7348 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d734a = word_d734a + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d734c = word_d734c + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d734e = word_d734e + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7350 = word_d7350 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7352 = word_d7352 + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7354 = word_d7354 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7356 = word_d7356 + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7358 = word_d7358 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d735a = word_d735a + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d735c = word_d735c + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d735e = word_d735e + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7360 = word_d7360 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7362 = word_d7362 + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7364 = word_d7364 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7366 = word_d7366 + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7368 = word_d7368 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d736a = word_d736a + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d736c = word_d736c + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d736e = word_d736e + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7370 = word_d7370 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7372 = word_d7372 + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7374 = word_d7374 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7376 = word_d7376 + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7378 = word_d7378 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d737a = word_d737a + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d737c = word_d737c + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d737e = word_d737e + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7380 = word_d7380 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7382 = word_d7382 + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7384 = word_d7384 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7386 = word_d7386 + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7388 = word_d7388 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d738a = word_d738a + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d738c = word_d738c + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d738e = word_d738e + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7390 = word_d7390 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7392 = word_d7392 + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7394 = word_d7394 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7396 = word_d7396 + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7398 = word_d7398 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d739a = word_d739a + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d739c = word_d739c + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d739e = word_d739e + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d73a0 = word_d73a0 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d73a2 = word_d73a2 + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d73a4 = word_d73a4 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d73a6 = word_d73a6 + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d73a8 = word_d73a8 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d73aa = word_d73aa + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d73ac = word_d73ac + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d73ae = word_d73ae + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d73b0 = word_d73b0 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d73b2 = word_d73b2 + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d73b4 = word_d73b4 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d73b6 = word_d73b6 + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d73b8 = word_d73b8 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d73ba = word_d73ba + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d73bc = word_d73bc + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d73be = word_d73be + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d73c0 = word_d73c0 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d73c2 = word_d73c2 + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d73c4 = word_d73c4 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d73c6 = word_d73c6 + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d73c8 = word_d73c8 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d73ca = word_d73ca + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d73cc = word_d73cc + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d73ce = word_d73ce + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d73d0 = word_d73d0 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d73d2 = word_d73d2 + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d73d4 = word_d73d4 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d73d6 = word_d73d6 + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d73d8 = word_d73d8 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d73da = word_d73da + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d73dc = word_d73dc + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d73de = word_d73de + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d73e0 = word_d73e0 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d73e2 = word_d73e2 + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d73e4 = word_d73e4 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d73e6 = word_d73e6 + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d73e8 = word_d73e8 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d73ea = word_d73ea + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d73ec = word_d73ec + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d73ee = word_d73ee + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d73f0 = word_d73f0 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d73f2 = word_d73f2 + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d73f4 = word_d73f4 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d73f6 = word_d73f6 + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d73f8 = word_d73f8 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d73fa = word_d73fa + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d73fc = word_d73fc + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d73fe = word_d73fe + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7400 = word_d7400 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7402 = word_d7402 + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7404 = word_d7404 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d7406 = word_d7406 + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d7408 = word_d7408 + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d740a = word_d740a + *pcVar3;
  uVar1 = uVar2 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI;
  word_d740c = word_d740c + *pcVar3;
  uVar2 = uVar1 + unaff_EDX;
  pcVar3 = pcVar3 + (uint)CARRY4(uVar1,unaff_EDX) + unaff_EDI;
  word_d740e = word_d740e + *pcVar3;
  word_d7410 = word_d7410 + pcVar3[(uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI];
  word_d7412 = word_d7412 +
               (pcVar3 + (uint)CARRY4(uVar2,unaff_EDX) + unaff_EDI)
               [(uint)CARRY4(uVar2 + unaff_EDX,unaff_EDX) + unaff_EDI];
  return;
}


// ================================================================================================
// sub_a905e @ 0xa905e [__cdecl]
// ================================================================================================

void sub_a905e(void)

{
  char cVar1;
  undefined2 uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  byte bVar6;
  byte *pbVar7;
  undefined4 *puVar8;
  bool bVar9;
  
  iVar4 = 0x80;
  puVar8 = (undefined4 *)&word_d7214;
  do {
    *puVar8 = 0;
    uVar5 = dword_d6d10;
    pbVar7 = dword_d6d0c;
    puVar8 = puVar8 + 1;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  bVar6 = byte_d6d1e;
  if (byte_d6ce0 != '\0') {
    if (byte_d6ce3 == '\0') {
      if (dword_d6d0c +
          (uint)CARRY4(dword_d6d18 * 0x100,dword_d6d10) +
          ((((((((dword_d6d14 << 1 | (uint)((int)dword_d6d18 < 0)) << 1 |
                (uint)((int)(dword_d6d18 << 1) < 0)) << 1 | (uint)((int)(dword_d6d18 << 2) < 0)) <<
               1 | (uint)((int)(dword_d6d18 << 3) < 0)) << 1 | (uint)((int)(dword_d6d18 << 4) < 0))
             << 1 | (uint)((int)(dword_d6d18 << 5) < 0)) << 1 | (uint)((int)(dword_d6d18 << 6) < 0))
           << 1 | (uint)((int)(dword_d6d18 << 7) < 0)) < dword_d6cfc) {
        dword_d7200 = dword_d6d0c;
        if (byte_d6ce1 < 0x7f) {
          sub_a715c(dword_d6d0c,dword_d6d18,&unk_d6d24);
        }
        else {
          sub_a815d();
        }
LAB_000a9105:
        dword_d6d0c = dword_d6d0c + ((int)pbVar7 - (int)dword_d7200);
        pbVar7 = dword_d6d0c;
        dword_d6d10 = uVar5;
        bVar6 = byte_d6d1e;
      }
      else {
        dword_d720c = (byte *)0x0;
        do {
          uVar3 = dword_d6d18;
          iVar4 = dword_d6d14;
          dword_d7204 = (int)dword_d6cfc - (int)dword_d6d0c;
          dword_d7200 = dword_d6d0c;
          dword_d7208 = dword_d6d0c + dword_d7204;
          uVar5 = dword_d6d10;
          pbVar7 = dword_d6d0c;
          while( true ) {
            (&word_d7214)[(int)dword_d720c] =
                 (&word_d7214)[(int)dword_d720c] + (short)(char)(&unk_d6d24)[*pbVar7];
            dword_d720c = dword_d720c + 1;
            bVar9 = CARRY4(uVar5,uVar3);
            uVar5 = uVar5 + uVar3;
            pbVar7 = pbVar7 + (uint)bVar9 + iVar4;
            if (dword_d7208 <= pbVar7) break;
            if (dword_d720c == (byte *)0x100) goto LAB_000a9105;
          }
          bVar6 = byte_d6d1e;
          if ((byte_d6ce0 != '\x01') || (dword_d6ce4 == 0)) {
            byte_d6ce0 = '\0';
            pbVar7 = dword_d6d0c;
            break;
          }
          dword_d6d0c = dword_d6cf8;
          pbVar7 = dword_d6d0c;
          dword_d6d10 = uVar5;
        } while (dword_d720c != (byte *)0x100);
      }
    }
    else {
      uVar5 = (int)dword_d6cfc - (int)dword_d6d0c;
      if (dword_d6d20 < (uint)((int)dword_d6cfc - (int)dword_d6d0c)) {
        uVar5 = dword_d6d20;
      }
      dword_d720c = dword_d6d0c + uVar5;
      iVar4 = 0;
      while( true ) {
        uVar5 = (uint)byte_d6d1e;
        if (dword_d6d00 == 0x10000) {
          do {
            uVar2 = *(undefined2 *)(&unk_d7414 + (uint)*pbVar7 * 2);
            bVar6 = (char)uVar5 + (char)uVar2;
            (&word_d7214)[iVar4] = (&word_d7214)[iVar4] + (short)(char)(&unk_d6d24)[bVar6];
            bVar6 = bVar6 + (char)((ushort)uVar2 >> 8);
            uVar5 = (uint)bVar6;
            (&word_d7214)[iVar4 + 1] = (&word_d7214)[iVar4 + 1] + (short)(char)(&unk_d6d24)[uVar5];
            iVar4 = iVar4 + 2;
            pbVar7 = pbVar7 + 1;
          } while (pbVar7 < dword_d720c);
        }
        else if (dword_d6d00 < 0x10001) {
          do {
            uVar2 = *(undefined2 *)(&unk_d7414 + (uint)*pbVar7 * 2);
            bVar6 = (char)uVar5 + (char)uVar2;
            cVar1 = (&unk_d6d24)[bVar6];
            (&word_d7214)[iVar4] = (&word_d7214)[iVar4] + (short)cVar1;
            (&word_d7214)[iVar4 + 1] = (&word_d7214)[iVar4 + 1] + (short)cVar1;
            bVar6 = bVar6 + (char)((ushort)uVar2 >> 8);
            uVar5 = (uint)bVar6;
            cVar1 = (&unk_d6d24)[uVar5];
            (&word_d7214)[iVar4 + 2] = (&word_d7214)[iVar4 + 2] + (short)cVar1;
            (&word_d7214)[iVar4 + 3] = (&word_d7214)[iVar4 + 3] + (short)cVar1;
            iVar4 = iVar4 + 4;
            pbVar7 = pbVar7 + 1;
          } while (pbVar7 < dword_d720c);
        }
        else {
          do {
            uVar2 = *(undefined2 *)(&unk_d7414 + (uint)*pbVar7 * 2);
            bVar6 = (char)uVar5 + (char)uVar2;
            (&word_d7214)[iVar4] = (&word_d7214)[iVar4] + (short)(char)(&unk_d6d24)[bVar6];
            iVar4 = iVar4 + 1;
            bVar6 = bVar6 + (char)((ushort)uVar2 >> 8);
            uVar5 = (uint)bVar6;
            pbVar7 = pbVar7 + 1;
          } while (pbVar7 < dword_d720c);
        }
        if (pbVar7 != dword_d6cfc) goto LAB_000a933a;
        if ((byte_d6ce0 != '\x01') || (dword_d6ce4 == 0)) {
          byte_d6ce0 = '\0';
          pbVar7 = dword_d6d0c;
          bVar6 = byte_d6d1e;
          goto LAB_000a933a;
        }
        byte_d6d1e = byte_d6d1f;
        if (dword_d6d0c + (dword_d6d20 - (int)pbVar7) == (byte *)0x0) break;
        dword_d720c = dword_d6cf8 + (int)(dword_d6d0c + (dword_d6d20 - (int)pbVar7));
        pbVar7 = dword_d6cf8;
      }
      dword_d6d0c = dword_d6cf8;
      pbVar7 = dword_d6d0c;
      bVar6 = byte_d6d1e;
    }
  }
LAB_000a933a:
  byte_d6d1e = bVar6;
  dword_d6d0c = pbVar7;
  uVar5 = dword_d6e54;
  pbVar7 = dword_d6e50;
  bVar6 = byte_d6e62;
  if (byte_d6e24 != '\0') {
    if (byte_d6e27 == '\0') {
      if (dword_d6e50 +
          (uint)CARRY4(dword_d6e5c * 0x100,dword_d6e54) +
          ((((((((dword_d6e58 << 1 | (uint)((int)dword_d6e5c < 0)) << 1 |
                (uint)((int)(dword_d6e5c << 1) < 0)) << 1 | (uint)((int)(dword_d6e5c << 2) < 0)) <<
               1 | (uint)((int)(dword_d6e5c << 3) < 0)) << 1 | (uint)((int)(dword_d6e5c << 4) < 0))
             << 1 | (uint)((int)(dword_d6e5c << 5) < 0)) << 1 | (uint)((int)(dword_d6e5c << 6) < 0))
           << 1 | (uint)((int)(dword_d6e5c << 7) < 0)) < dword_d6e40) {
        dword_d7200 = dword_d6e50;
        if (byte_d6e25 < 0x7f) {
          sub_a715c(dword_d6e50,dword_d6e5c,&unk_d6e68);
        }
        else {
          sub_a815d();
        }
LAB_000a93cc:
        dword_d6e50 = dword_d6e50 + ((int)pbVar7 - (int)dword_d7200);
        pbVar7 = dword_d6e50;
        dword_d6e54 = uVar5;
        bVar6 = byte_d6e62;
      }
      else {
        dword_d720c = (byte *)0x0;
        do {
          uVar3 = dword_d6e5c;
          iVar4 = dword_d6e58;
          dword_d7204 = (int)dword_d6e40 - (int)dword_d6e50;
          dword_d7200 = dword_d6e50;
          dword_d7208 = dword_d6e50 + dword_d7204;
          uVar5 = dword_d6e54;
          pbVar7 = dword_d6e50;
          while( true ) {
            (&word_d7214)[(int)dword_d720c] =
                 (&word_d7214)[(int)dword_d720c] + (short)(char)(&unk_d6e68)[*pbVar7];
            dword_d720c = dword_d720c + 1;
            bVar9 = CARRY4(uVar5,uVar3);
            uVar5 = uVar5 + uVar3;
            pbVar7 = pbVar7 + (uint)bVar9 + iVar4;
            if (dword_d7208 <= pbVar7) break;
            if (dword_d720c == (byte *)0x100) goto LAB_000a93cc;
          }
          bVar6 = byte_d6e62;
          if ((byte_d6e24 != '\x01') || (dword_d6e28 == 0)) {
            byte_d6e24 = '\0';
            pbVar7 = dword_d6e50;
            break;
          }
          dword_d6e50 = dword_d6e3c;
          pbVar7 = dword_d6e50;
          dword_d6e54 = uVar5;
        } while (dword_d720c != (byte *)0x100);
      }
    }
    else {
      uVar5 = (int)dword_d6e40 - (int)dword_d6e50;
      if (dword_d6e64 < (uint)((int)dword_d6e40 - (int)dword_d6e50)) {
        uVar5 = dword_d6e64;
      }
      dword_d720c = dword_d6e50 + uVar5;
      iVar4 = 0;
      while( true ) {
        uVar5 = (uint)byte_d6e62;
        if (dword_d6e44 == 0x10000) {
          do {
            uVar2 = *(undefined2 *)(&unk_d7414 + (uint)*pbVar7 * 2);
            bVar6 = (char)uVar5 + (char)uVar2;
            (&word_d7214)[iVar4] = (&word_d7214)[iVar4] + (short)(char)(&unk_d6e68)[bVar6];
            bVar6 = bVar6 + (char)((ushort)uVar2 >> 8);
            uVar5 = (uint)bVar6;
            (&word_d7214)[iVar4 + 1] = (&word_d7214)[iVar4 + 1] + (short)(char)(&unk_d6e68)[uVar5];
            iVar4 = iVar4 + 2;
            pbVar7 = pbVar7 + 1;
          } while (pbVar7 < dword_d720c);
        }
        else if (dword_d6e44 < 0x10001) {
          do {
            uVar2 = *(undefined2 *)(&unk_d7414 + (uint)*pbVar7 * 2);
            bVar6 = (char)uVar5 + (char)uVar2;
            cVar1 = (&unk_d6e68)[bVar6];
            (&word_d7214)[iVar4] = (&word_d7214)[iVar4] + (short)cVar1;
            (&word_d7214)[iVar4 + 1] = (&word_d7214)[iVar4 + 1] + (short)cVar1;
            bVar6 = bVar6 + (char)((ushort)uVar2 >> 8);
            uVar5 = (uint)bVar6;
            cVar1 = (&unk_d6e68)[uVar5];
            (&word_d7214)[iVar4 + 2] = (&word_d7214)[iVar4 + 2] + (short)cVar1;
            (&word_d7214)[iVar4 + 3] = (&word_d7214)[iVar4 + 3] + (short)cVar1;
            iVar4 = iVar4 + 4;
            pbVar7 = pbVar7 + 1;
          } while (pbVar7 < dword_d720c);
        }
        else {
          do {
            uVar2 = *(undefined2 *)(&unk_d7414 + (uint)*pbVar7 * 2);
            bVar6 = (char)uVar5 + (char)uVar2;
            (&word_d7214)[iVar4] = (&word_d7214)[iVar4] + (short)(char)(&unk_d6e68)[bVar6];
            iVar4 = iVar4 + 1;
            bVar6 = bVar6 + (char)((ushort)uVar2 >> 8);
            uVar5 = (uint)bVar6;
            pbVar7 = pbVar7 + 1;
          } while (pbVar7 < dword_d720c);
        }
        if (pbVar7 != dword_d6e40) goto LAB_000a9601;
        if ((byte_d6e24 != '\x01') || (dword_d6e28 == 0)) {
          byte_d6e24 = '\0';
          pbVar7 = dword_d6e50;
          bVar6 = byte_d6e62;
          goto LAB_000a9601;
        }
        byte_d6e62 = byte_d6e63;
        if (dword_d6e50 + (dword_d6e64 - (int)pbVar7) == (byte *)0x0) break;
        dword_d720c = dword_d6e3c + (int)(dword_d6e50 + (dword_d6e64 - (int)pbVar7));
        pbVar7 = dword_d6e3c;
      }
      dword_d6e50 = dword_d6e3c;
      pbVar7 = dword_d6e50;
      bVar6 = byte_d6e62;
    }
  }
LAB_000a9601:
  byte_d6e62 = bVar6;
  dword_d6e50 = pbVar7;
  uVar5 = dword_d6f98;
  pbVar7 = dword_d6f94;
  bVar6 = byte_d6fa6;
  if (byte_d6f68 != '\0') {
    if (byte_d6f6b == '\0') {
      if (dword_d6f94 +
          (uint)CARRY4(dword_d6fa0 * 0x100,dword_d6f98) +
          ((((((((dword_d6f9c << 1 | (uint)((int)dword_d6fa0 < 0)) << 1 |
                (uint)((int)(dword_d6fa0 << 1) < 0)) << 1 | (uint)((int)(dword_d6fa0 << 2) < 0)) <<
               1 | (uint)((int)(dword_d6fa0 << 3) < 0)) << 1 | (uint)((int)(dword_d6fa0 << 4) < 0))
             << 1 | (uint)((int)(dword_d6fa0 << 5) < 0)) << 1 | (uint)((int)(dword_d6fa0 << 6) < 0))
           << 1 | (uint)((int)(dword_d6fa0 << 7) < 0)) < dword_d6f84) {
        dword_d7200 = dword_d6f94;
        if (byte_d6f69 < 0x7f) {
          sub_a715c(dword_d6f94,dword_d6fa0,&unk_d6fac);
        }
        else {
          sub_a815d();
        }
LAB_000a9693:
        dword_d6f94 = dword_d6f94 + ((int)pbVar7 - (int)dword_d7200);
        pbVar7 = dword_d6f94;
        dword_d6f98 = uVar5;
        bVar6 = byte_d6fa6;
      }
      else {
        dword_d720c = (byte *)0x0;
        do {
          uVar3 = dword_d6fa0;
          iVar4 = dword_d6f9c;
          dword_d7204 = (int)dword_d6f84 - (int)dword_d6f94;
          dword_d7200 = dword_d6f94;
          dword_d7208 = dword_d6f94 + dword_d7204;
          uVar5 = dword_d6f98;
          pbVar7 = dword_d6f94;
          while( true ) {
            (&word_d7214)[(int)dword_d720c] =
                 (&word_d7214)[(int)dword_d720c] + (short)(char)(&unk_d6fac)[*pbVar7];
            dword_d720c = dword_d720c + 1;
            bVar9 = CARRY4(uVar5,uVar3);
            uVar5 = uVar5 + uVar3;
            pbVar7 = pbVar7 + (uint)bVar9 + iVar4;
            if (dword_d7208 <= pbVar7) break;
            if (dword_d720c == (byte *)0x100) goto LAB_000a9693;
          }
          bVar6 = byte_d6fa6;
          if ((byte_d6f68 != '\x01') || (dword_d6f6c == 0)) {
            byte_d6f68 = '\0';
            pbVar7 = dword_d6f94;
            break;
          }
          dword_d6f94 = dword_d6f80;
          pbVar7 = dword_d6f94;
          dword_d6f98 = uVar5;
        } while (dword_d720c != (byte *)0x100);
      }
    }
    else {
      uVar5 = (int)dword_d6f84 - (int)dword_d6f94;
      if (dword_d6fa8 < (uint)((int)dword_d6f84 - (int)dword_d6f94)) {
        uVar5 = dword_d6fa8;
      }
      dword_d720c = dword_d6f94 + uVar5;
      iVar4 = 0;
      while( true ) {
        uVar5 = (uint)byte_d6fa6;
        if (dword_d6f88 == 0x10000) {
          do {
            uVar2 = *(undefined2 *)(&unk_d7414 + (uint)*pbVar7 * 2);
            bVar6 = (char)uVar5 + (char)uVar2;
            (&word_d7214)[iVar4] = (&word_d7214)[iVar4] + (short)(char)(&unk_d6fac)[bVar6];
            bVar6 = bVar6 + (char)((ushort)uVar2 >> 8);
            uVar5 = (uint)bVar6;
            (&word_d7214)[iVar4 + 1] = (&word_d7214)[iVar4 + 1] + (short)(char)(&unk_d6fac)[uVar5];
            iVar4 = iVar4 + 2;
            pbVar7 = pbVar7 + 1;
          } while (pbVar7 < dword_d720c);
        }
        else if (dword_d6f88 < 0x10001) {
          do {
            uVar2 = *(undefined2 *)(&unk_d7414 + (uint)*pbVar7 * 2);
            bVar6 = (char)uVar5 + (char)uVar2;
            cVar1 = (&unk_d6fac)[bVar6];
            (&word_d7214)[iVar4] = (&word_d7214)[iVar4] + (short)cVar1;
            (&word_d7214)[iVar4 + 1] = (&word_d7214)[iVar4 + 1] + (short)cVar1;
            bVar6 = bVar6 + (char)((ushort)uVar2 >> 8);
            uVar5 = (uint)bVar6;
            cVar1 = (&unk_d6fac)[uVar5];
            (&word_d7214)[iVar4 + 2] = (&word_d7214)[iVar4 + 2] + (short)cVar1;
            (&word_d7214)[iVar4 + 3] = (&word_d7214)[iVar4 + 3] + (short)cVar1;
            iVar4 = iVar4 + 4;
            pbVar7 = pbVar7 + 1;
          } while (pbVar7 < dword_d720c);
        }
        else {
          do {
            uVar2 = *(undefined2 *)(&unk_d7414 + (uint)*pbVar7 * 2);
            bVar6 = (char)uVar5 + (char)uVar2;
            (&word_d7214)[iVar4] = (&word_d7214)[iVar4] + (short)(char)(&unk_d6fac)[bVar6];
            iVar4 = iVar4 + 1;
            bVar6 = bVar6 + (char)((ushort)uVar2 >> 8);
            uVar5 = (uint)bVar6;
            pbVar7 = pbVar7 + 1;
          } while (pbVar7 < dword_d720c);
        }
        if (pbVar7 != dword_d6f84) goto LAB_000a98c8;
        if ((byte_d6f68 != '\x01') || (dword_d6f6c == 0)) {
          byte_d6f68 = '\0';
          pbVar7 = dword_d6f94;
          bVar6 = byte_d6fa6;
          goto LAB_000a98c8;
        }
        byte_d6fa6 = byte_d6fa7;
        if (dword_d6f94 + (dword_d6fa8 - (int)pbVar7) == (byte *)0x0) break;
        dword_d720c = dword_d6f80 + (int)(dword_d6f94 + (dword_d6fa8 - (int)pbVar7));
        pbVar7 = dword_d6f80;
      }
      dword_d6f94 = dword_d6f80;
      pbVar7 = dword_d6f94;
      bVar6 = byte_d6fa6;
    }
  }
LAB_000a98c8:
  byte_d6fa6 = bVar6;
  dword_d6f94 = pbVar7;
  uVar5 = dword_d70dc;
  pbVar7 = dword_d70d8;
  bVar6 = byte_d70ea;
  if (byte_d70ac != '\0') {
    if (byte_d70af == '\0') {
      if (dword_d70d8 +
          (uint)CARRY4(dword_d70e4 * 0x100,dword_d70dc) +
          ((((((((dword_d70e0 << 1 | (uint)((int)dword_d70e4 < 0)) << 1 |
                (uint)((int)(dword_d70e4 << 1) < 0)) << 1 | (uint)((int)(dword_d70e4 << 2) < 0)) <<
               1 | (uint)((int)(dword_d70e4 << 3) < 0)) << 1 | (uint)((int)(dword_d70e4 << 4) < 0))
             << 1 | (uint)((int)(dword_d70e4 << 5) < 0)) << 1 | (uint)((int)(dword_d70e4 << 6) < 0))
           << 1 | (uint)((int)(dword_d70e4 << 7) < 0)) < dword_d70c8) {
        dword_d7200 = dword_d70d8;
        if (byte_d70ad < 0x7f) {
          sub_a715c(dword_d70d8,dword_d70e4,&unk_d70f0);
        }
        else {
          sub_a815d();
        }
LAB_000a995a:
        dword_d70d8 = dword_d70d8 + ((int)pbVar7 - (int)dword_d7200);
        pbVar7 = dword_d70d8;
        dword_d70dc = uVar5;
        bVar6 = byte_d70ea;
      }
      else {
        dword_d720c = (byte *)0x0;
        do {
          uVar3 = dword_d70e4;
          iVar4 = dword_d70e0;
          dword_d7204 = (int)dword_d70c8 - (int)dword_d70d8;
          dword_d7200 = dword_d70d8;
          dword_d7208 = dword_d70d8 + dword_d7204;
          uVar5 = dword_d70dc;
          pbVar7 = dword_d70d8;
          while( true ) {
            (&word_d7214)[(int)dword_d720c] =
                 (&word_d7214)[(int)dword_d720c] + (short)(char)(&unk_d70f0)[*pbVar7];
            dword_d720c = dword_d720c + 1;
            bVar9 = CARRY4(uVar5,uVar3);
            uVar5 = uVar5 + uVar3;
            pbVar7 = pbVar7 + (uint)bVar9 + iVar4;
            if (dword_d7208 <= pbVar7) break;
            if (dword_d720c == (byte *)0x100) goto LAB_000a995a;
          }
          bVar6 = byte_d70ea;
          if ((byte_d70ac != '\x01') || (dword_d70b0 == 0)) {
            byte_d70ac = '\0';
            pbVar7 = dword_d70d8;
            break;
          }
          dword_d70d8 = dword_d70c4;
          pbVar7 = dword_d70d8;
          dword_d70dc = uVar5;
        } while (dword_d720c != (byte *)0x100);
      }
    }
    else {
      uVar5 = (int)dword_d70c8 - (int)dword_d70d8;
      if (dword_d70ec < (uint)((int)dword_d70c8 - (int)dword_d70d8)) {
        uVar5 = dword_d70ec;
      }
      dword_d720c = dword_d70d8 + uVar5;
      iVar4 = 0;
      while( true ) {
        uVar5 = (uint)byte_d70ea;
        if (dword_d70cc == 0x10000) {
          do {
            uVar2 = *(undefined2 *)(&unk_d7414 + (uint)*pbVar7 * 2);
            bVar6 = (char)uVar5 + (char)uVar2;
            (&word_d7214)[iVar4] = (&word_d7214)[iVar4] + (short)(char)(&unk_d70f0)[bVar6];
            bVar6 = bVar6 + (char)((ushort)uVar2 >> 8);
            uVar5 = (uint)bVar6;
            (&word_d7214)[iVar4 + 1] = (&word_d7214)[iVar4 + 1] + (short)(char)(&unk_d70f0)[uVar5];
            iVar4 = iVar4 + 2;
            pbVar7 = pbVar7 + 1;
          } while (pbVar7 < dword_d720c);
        }
        else if (dword_d70cc < 0x10001) {
          do {
            uVar2 = *(undefined2 *)(&unk_d7414 + (uint)*pbVar7 * 2);
            bVar6 = (char)uVar5 + (char)uVar2;
            cVar1 = (&unk_d70f0)[bVar6];
            (&word_d7214)[iVar4] = (&word_d7214)[iVar4] + (short)cVar1;
            (&word_d7214)[iVar4 + 1] = (&word_d7214)[iVar4 + 1] + (short)cVar1;
            bVar6 = bVar6 + (char)((ushort)uVar2 >> 8);
            uVar5 = (uint)bVar6;
            cVar1 = (&unk_d70f0)[uVar5];
            (&word_d7214)[iVar4 + 2] = (&word_d7214)[iVar4 + 2] + (short)cVar1;
            (&word_d7214)[iVar4 + 3] = (&word_d7214)[iVar4 + 3] + (short)cVar1;
            iVar4 = iVar4 + 4;
            pbVar7 = pbVar7 + 1;
          } while (pbVar7 < dword_d720c);
        }
        else {
          do {
            uVar2 = *(undefined2 *)(&unk_d7414 + (uint)*pbVar7 * 2);
            bVar6 = (char)uVar5 + (char)uVar2;
            (&word_d7214)[iVar4] = (&word_d7214)[iVar4] + (short)(char)(&unk_d70f0)[bVar6];
            iVar4 = iVar4 + 1;
            bVar6 = bVar6 + (char)((ushort)uVar2 >> 8);
            uVar5 = (uint)bVar6;
            pbVar7 = pbVar7 + 1;
          } while (pbVar7 < dword_d720c);
        }
        if (pbVar7 != dword_d70c8) goto LAB_000a9b8f;
        if ((byte_d70ac != '\x01') || (dword_d70b0 == 0)) {
          byte_d70ac = '\0';
          pbVar7 = dword_d70d8;
          bVar6 = byte_d70ea;
          goto LAB_000a9b8f;
        }
        byte_d70ea = byte_d70eb;
        if (dword_d70d8 + (dword_d70ec - (int)pbVar7) == (byte *)0x0) break;
        dword_d720c = dword_d70c4 + (int)(dword_d70d8 + (dword_d70ec - (int)pbVar7));
        pbVar7 = dword_d70c4;
      }
      dword_d70d8 = dword_d70c4;
      pbVar7 = dword_d70d8;
      bVar6 = byte_d70ea;
    }
  }
LAB_000a9b8f:
  byte_d70ea = bVar6;
  dword_d70d8 = pbVar7;
  sub_a9c4a();
  return;
}


// ================================================================================================
// sub_a9ba4 @ 0xa9ba4 [__watcall]
// ================================================================================================

undefined4 __watcall sub_a9ba4(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = sub_aa1b2();
  iVar2 = dword_d7a1e;
  if (iVar1 < dword_d7a1e) {
    iVar2 = 0;
  }
  if (iVar2 == dword_d7614) {
    return 0;
  }
  return 1;
}


// ================================================================================================
// sub_a9bd0 @ 0xa9bd0 [__cdecl]
// ================================================================================================

undefined4 sub_a9bd0(undefined4 param_1,undefined4 param_2,uint param_3)

{
  int iVar1;
  
  dword_d7a1e = param_3 >> 1;
  dword_d7a22 = param_2;
  iVar1 = sub_a9f93();
  if (iVar1 != -1) {
    byte_d7618 = 1;
    return 0;
  }
  byte_d7618 = 0;
  sub_a9e34();
  return 0xffffffff;
}


// ================================================================================================
// sub_a9c1b @ 0xa9c1b [__watcall]
// ================================================================================================

void __watcall sub_a9c1b(void)

{
  if (byte_d7618 != '\0') {
    byte_d7618 = '\0';
    sub_a9e34();
  }
  return;
}


// ================================================================================================
// sub_a9c37 @ 0xa9c37 [__watcall]
// ================================================================================================

void __watcall sub_a9c37(void)

{
  byte_d7619 = 1;
  return;
}


// ================================================================================================
// sub_a9c42 @ 0xa9c42 [__watcall]
// ================================================================================================

void __watcall sub_a9c42(void)

{
  byte_d7619 = 0;
  return;
}


// ================================================================================================
// sub_a9c4a @ 0xa9c4a [__watcall]
// ================================================================================================

void __watcall sub_a9c4a(void)

{
  uint uVar1;
  short *unaff_ESI;
  undefined *puVar2;
  
  puVar2 = (undefined *)(dword_d7a22 + dword_d7614);
  uVar1 = dword_d7a1e;
  do {
    *puVar2 = (&unk_d781c)[*unaff_ESI];
    unaff_ESI = unaff_ESI + 1;
    puVar2 = puVar2 + 1;
    uVar1 = uVar1 - 1;
  } while (uVar1 != 0);
  dword_d7614 = dword_d7614 ^ dword_d7a1e;
  return;
}


// ================================================================================================
// sub_a9c9c @ 0xa9c9c [__watcall]
// ================================================================================================

undefined2 __watcall sub_a9c9c(byte param_1,undefined4 param_2,undefined4 unaff_EBX)

{
  code *pcVar1;
  byte bVar2;
  byte bVar3;
  undefined2 in_ES;
  byte in_CF;
  byte in_PF;
  byte in_AF;
  byte in_ZF;
  byte in_SF;
  byte in_TF;
  byte in_IF;
  byte in_OF;
  byte in_NT;
  byte in_AC;
  byte in_VIF;
  byte in_VIP;
  byte in_ID;
  
  pcVar1 = (code *)swi(0x21);
  byte_a9c91 = param_1;
  (*pcVar1)((uint)(in_NT & 1) * 0x4000 | (uint)(in_OF & 1) * 0x800 | (uint)(in_IF & 1) * 0x200 |
            (uint)(in_TF & 1) * 0x100 | (uint)(in_SF & 1) * 0x80 | (uint)(in_ZF & 1) * 0x40 |
            (uint)(in_AF & 1) * 0x10 | (uint)(in_PF & 1) * 4 | (uint)(in_CF & 1) |
            (uint)(in_ID & 1) * 0x200000 | (uint)(in_VIP & 1) * 0x100000 |
            (uint)(in_VIF & 1) * 0x80000 | (uint)(in_AC & 1) * 0x40000);
  pcVar1 = (code *)swi(0x21);
  dword_a9c92 = unaff_EBX;
  word_a9c96 = in_ES;
  (*pcVar1)();
  out(0x20,0x20);
  out(0xa0,0x20);
  if (7 < byte_a9c91) {
    bVar3 = ~('\x01' << (byte_a9c91 - 8 & 0x1f));
    bVar2 = in(0x21);
    bVar2 = bVar2 & bVar3;
    out(0x21,bVar2);
    return CONCAT11(bVar3,bVar2);
  }
  bVar3 = ~('\x01' << (byte_a9c91 & 0x1f));
  bVar2 = in(0x21);
  bVar2 = bVar2 & bVar3;
  out(0x21,bVar2);
  return CONCAT11(bVar3,bVar2);
}


// ================================================================================================
// sub_a9d1d @ 0xa9d1d [__watcall]
// ================================================================================================

void __watcall sub_a9d1d(void)

{
  code *pcVar1;
  byte in_AF;
  byte in_TF;
  byte in_IF;
  byte in_NT;
  byte in_AC;
  byte in_VIF;
  byte in_VIP;
  byte in_ID;
  
  if (byte_a9c91 != '\0') {
    pcVar1 = (code *)swi(0x21);
    (*pcVar1)((uint)(in_NT & 1) * 0x4000 | (uint)(in_IF & 1) * 0x200 | (uint)(in_TF & 1) * 0x100 |
              (uint)(byte_a9c91 < '\0') * 0x80 | (uint)(byte_a9c91 == '\0') * 0x40 |
              (uint)(in_AF & 1) * 0x10 | (uint)((POPCOUNT(byte_a9c91) & 1U) == 0) * 4 |
              (uint)(in_ID & 1) * 0x200000 | (uint)(in_VIP & 1) * 0x100000 |
              (uint)(in_VIF & 1) * 0x80000 | (uint)(in_AC & 1) * 0x40000);
    byte_a9c91 = '\0';
  }
  return;
}


// ================================================================================================
// sub_a9d4c @ 0xa9d4c [__watcall]
// ================================================================================================

undefined8 __watcall sub_a9d4c(undefined4 param_1,undefined4 unaff_EDX)

{
  byte bVar1;
  int iVar2;
  bool bVar3;
  
  sub_902a0();
  in(word_a9c86 + 0xe);
  if (byte_a9c8e != '\x01') {
    iVar2 = 1000;
    do {
      bVar1 = in(word_a9c86 + 0xc);
      bVar3 = (bVar1 & 0x80) != 0;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0 && bVar3);
    if (!bVar3) {
      out(word_a9c86 + 0xc,0x14);
    }
    iVar2 = 1000;
    do {
      bVar1 = in(word_a9c86 + 0xc);
      bVar3 = (bVar1 & 0x80) != 0;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0 && bVar3);
    if (!bVar3) {
      out(word_a9c86 + 0xc,0xff);
    }
    iVar2 = 1000;
    do {
      bVar1 = in(word_a9c86 + 0xc);
      bVar3 = (bVar1 & 0x80) != 0;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0 && bVar3);
    if (!bVar3) {
      out(word_a9c86 + 0xc,0xff);
    }
  }
  out(0xa0,0x20);
  out(0x20,0x20);
  return CONCAT44(unaff_EDX,param_1);
}


// ================================================================================================
// sub_a9deb @ 0xa9deb [__watcall]
// ================================================================================================

void __watcall sub_a9deb(undefined4 param_1)

{
  byte bVar1;
  int iVar2;
  bool bVar3;
  
  iVar2 = 1000;
  do {
    bVar1 = in(word_a9c86 + 0xc);
    bVar3 = (bVar1 & 0x80) != 0;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0 && bVar3);
  if (!bVar3) {
    out(word_a9c86 + 0xc,(char)((uint)param_1 >> 8));
  }
  return;
}


// ================================================================================================
// sub_a9e0f @ 0xa9e0f [__watcall]
// ================================================================================================

byte __watcall sub_a9e0f(void)

{
  byte bVar1;
  int iVar2;
  
  iVar2 = 1000;
  do {
    bVar1 = in(word_a9c86 + 0xe);
    bVar1 = bVar1 & 0x80;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0 && bVar1 == 0);
  if (bVar1 != 0) {
    bVar1 = in(word_a9c86 + 10);
  }
  return bVar1;
}


// ================================================================================================
// sub_a9e34 @ 0xa9e34 [__watcall]
// ================================================================================================

void __watcall sub_a9e34(void)

{
  sub_aa14d();
  out(0x21,byte_a9c8f);
  out(0xa1,byte_a9c90);
  sub_a9e55(byte_a9c90);
  return;
}


// ================================================================================================
// sub_a9e55 @ 0xa9e55 [__watcall]
// ================================================================================================

uint __watcall sub_a9e55(void)

{
  uint uVar1;
  byte bVar2;
  byte bVar3;
  int iVar4;
  int iVar5;
  bool bVar6;
  
  in(word_a9c86 + 0xe);
  out(word_a9c86 + 6,1);
  iVar4 = 0x14;
  do {
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  iVar4 = 0x14;
  do {
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  iVar4 = 0x14;
  do {
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  out(word_a9c86 + 6,0);
  iVar4 = 0x14;
  do {
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  iVar4 = 0x14;
  do {
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  iVar4 = 0x14;
  do {
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  iVar4 = 1000;
  do {
    iVar5 = 1000;
    do {
      bVar2 = in(word_a9c86 + 0xe);
      bVar3 = bVar2 & 0x80;
      bVar6 = (bVar2 & 0x80) == 0;
      iVar5 = iVar5 + -1;
    } while (iVar5 != 0 && bVar6);
    if (!bVar6) {
      bVar3 = in(word_a9c86 + 10);
    }
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0 && bVar3 != 0xaa);
  uVar1 = (uint)(bVar3 != 0xaa);
  return uVar1 * -2 | (uint)(uVar1 != 0);
}


// ================================================================================================
// sub_a9f1a @ 0xa9f1a [__watcall]
// ================================================================================================

undefined4 __watcall sub_a9f1a(undefined4 param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  
  sub_a9deb();
  iVar2 = 20000;
  do {
    iVar3 = 0x14;
    do {
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  sub_a9e0f(0);
  uVar1 = sub_a9e0f();
  if (uVar1 < 0x201) {
    dword_a9c8a = 0x2b11;
    byte_a9c8e = 0;
  }
  else if (uVar1 < 0x400) {
    dword_a9c8a = 0x5622;
    byte_a9c8e = 1;
  }
  else {
    dword_a9c8a = 0x5622;
    byte_a9c8e = 0;
  }
  return param_1;
}


// ================================================================================================
// sub_a9f93 @ 0xa9f93 [__cdecl]
// ================================================================================================

uint sub_a9f93(undefined2 param_1,undefined param_2,byte param_3,undefined4 param_4,short param_5)

{
  uint uVar1;
  undefined uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 uVar7;
  bool bVar8;
  byte bVar9;
  byte bVar10;
  undefined8 uVar11;
  
  byte_a9c8f = in(0x21);
  byte_a9c90 = in(0xa1);
  bVar8 = false;
  byte_a9c91 = 0;
  word_a9c86 = param_1;
  byte_a9c88 = param_2;
  byte_a9c89 = param_3;
  uVar3 = sub_a9e55();
  if (bVar8) {
    return uVar3;
  }
  sub_a9f1a();
  bVar9 = 0;
  uVar7 = extraout_EDX;
  uVar3 = dword_a9c8a;
  if (dword_a9c8a != 0) {
    iVar4 = (int)(256000000 / (ulonglong)dword_a9c8a);
    bVar9 = iVar4 != 0;
    uVar3 = -iVar4;
    uVar11 = sub_a9deb(CONCAT22((short)(uVar3 >> 0x10),CONCAT11(0x40,(char)uVar3)),
                       (int)(256000000 % (ulonglong)dword_a9c8a),uVar3);
    uVar7 = (undefined4)((ulonglong)uVar11 >> 0x20);
    if (!(bool)bVar9) {
      sub_a9deb(CONCAT11((char)(uVar3 >> 8),(char)uVar11),uVar7,uVar3);
      uVar7 = extraout_EDX_00;
    }
  }
  bVar10 = bVar9 != 0;
  uVar1 = (uint)bVar9 * -2;
  uVar5 = uVar1 | bVar10;
  if ((bool)bVar10) {
    return uVar5;
  }
  sub_a9deb(CONCAT22((short)(uVar1 >> 0x10),CONCAT11(0xd1,(char)uVar5)),uVar7,uVar3);
  uVar3 = (uint)bVar10;
  if (uVar3 != 0) {
    return uVar3 * -2 | (uint)(uVar3 != 0);
  }
  word_a9c83 = param_5;
  word_a9c81 = (undefined2)param_4;
  byte_a9c80 = (undefined)((uint)param_4 >> 0x10);
  if (byte_a9c85 == '\0') {
    byte_a9c85 = 1;
    sub_a9c9c(byte_a9c88,sub_a9d4c);
    out(10,byte_a9c89 | 4);
    out(0xb,byte_a9c89 | 0x58);
    out(0xc,byte_a9c89 | 0x58);
    out((ushort)(byte)(byte_a9c89 << 1),(char)word_a9c81);
    out((ushort)(byte)(byte_a9c89 << 1),(char)((ushort)word_a9c81 >> 8));
    out((ushort)(byte)(&unk_a9c98)[byte_a9c89],byte_a9c80);
    bVar10 = byte_a9c89 * '\x02' + 1;
    uVar2 = (undefined)(word_a9c83 + -1);
    out(0xc,uVar2);
    out((ushort)bVar10,uVar2);
    out((ushort)bVar10,(char)((ushort)(word_a9c83 + -1) >> 8));
    out(10,byte_a9c89);
    bVar9 = byte_a9c8e == '\0';
    if (byte_a9c8e == '\x01') {
      sub_a9deb(CONCAT11(0x48,byte_a9c89),bVar10);
      if (!(bool)bVar9) {
        iVar4 = 20000;
        do {
          iVar6 = 0x14;
          do {
            iVar6 = iVar6 + -1;
          } while (iVar6 != 0);
          bVar9 = (bVar9 & 1) != 0;
          iVar4 = iVar4 + -1;
        } while (iVar4 != 0);
        sub_a9deb();
        if (!(bool)bVar9) {
          sub_a9deb();
          sub_a9deb();
        }
      }
    }
    else {
      sub_a9deb(CONCAT11(0x14,byte_a9c89),bVar10);
      if (!(bool)bVar9) {
        iVar4 = 20000;
        do {
          iVar6 = 0x14;
          do {
            iVar6 = iVar6 + -1;
          } while (iVar6 != 0);
          bVar9 = (bVar9 & 1) != 0;
          iVar4 = iVar4 + -1;
        } while (iVar4 != 0);
        sub_a9deb();
        if (!(bool)bVar9) {
          sub_a9deb();
        }
      }
    }
    return (uint)bVar9 * -2 | (uint)(bVar9 != 0);
  }
  return 0;
}


// ================================================================================================
// sub_aa14d @ 0xaa14d [__watcall]
// ================================================================================================

byte __watcall sub_aa14d(byte param_1)

{
  if (byte_a9c85 != '\0') {
    out(10,byte_a9c89 | 4);
    in(word_a9c86 + 0xe);
    byte_a9c85 = '\0';
    param_1 = byte_a9c91;
    if (byte_a9c91 != 0) {
      param_1 = sub_a9d1d();
      if (byte_a9c88 != 0xff) {
        if (byte_a9c88 < 8) {
          param_1 = in(0x21);
          param_1 = param_1 | '\x01' << (byte_a9c88 & 0x1f);
          out(0x21,param_1);
        }
        else {
          param_1 = in(0xa1);
          param_1 = param_1 | '\x01' << (byte_a9c88 - 8 & 0x1f);
          out(0xa1,param_1);
        }
      }
    }
  }
  return param_1;
}


// ================================================================================================
// sub_aa1b2 @ 0xaa1b2 [__watcall]
// ================================================================================================

int __watcall sub_aa1b2(void)

{
  undefined uVar1;
  undefined uVar2;
  short sVar3;
  
  sVar3 = (ushort)byte_a9c89 * 2 + 1;
  uVar1 = in(sVar3);
  uVar2 = in(sVar3);
  return (word_a9c83 - 1) - (uint)CONCAT11(uVar2,uVar1);
}


// ================================================================================================
// sub_aa1d9 @ 0xaa1d9 [__watcall]
// ================================================================================================

undefined8 __watcall sub_aa1d9(void)

{
  undefined4 uVar1;
  int in_stack_00000004;
  
  out(word_a9c86 + 4,0xe);
  uVar1 = 0;
  if (in_stack_00000004 == 0) {
    uVar1 = 0x20;
  }
  out((short)(word_a9c86 + 5),(char)uVar1);
  return CONCAT44(word_a9c86 + 5,uVar1);
}


// ================================================================================================
// sub_aa200 @ 0xaa200 [__watcall]
// ================================================================================================

undefined8 __watcall sub_aa200(undefined4 param_1,undefined unaff_DL)

{
  out((short)param_1,unaff_DL);
  return CONCAT44(param_1,CONCAT31((int3)((uint)param_1 >> 8),unaff_DL));
}


// ================================================================================================
// sub_aa210 @ 0xaa210 [__watcall]
// ================================================================================================

undefined4 __watcall sub_aa210(undefined4 param_1,int unaff_EDX)

{
  short sVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  undefined8 uVar5;
  
  uVar5 = sub_b0a78();
  iVar2 = (int)uVar5;
  if (iVar2 < 0) {
    word_f799c = -(short)uVar5;
    uVar3 = 0x10;
  }
  else {
    if (iVar2 == -1) {
      return 0x11;
    }
    sVar1 = sub_b0a14(iVar2,(int)((ulonglong)uVar5 >> 0x20),0x81);
    if (sVar1 != 0x81) {
      sub_b0a40(iVar2);
      return 0xe;
    }
    iVar4 = sub_98a9f(unaff_EDX,aGF1PATCH110,8);
    if (iVar4 != 0) {
      sub_b0a40(iVar2);
      return 0xe;
    }
    iVar4 = strcmp((char *)(unaff_EDX + 8),(char *)&a110);
    if (iVar4 < 0) {
      sub_b0a40(iVar2);
      return 0xf;
    }
    sVar1 = sub_b0a14(iVar2,unaff_EDX + 0x81,0x3f);
    if (sVar1 != 0x3f) {
      sub_b0a40(iVar2);
      return 0xe;
    }
    sub_b0a40(iVar2);
    uVar3 = 0;
  }
  return uVar3;
}


// ================================================================================================
// sub_aa300 @ 0xaa300 [__watcall]
// ================================================================================================

undefined4 __watcall
sub_aa300(undefined4 param_1,int param_2,int unaff_EBX,int *unaff_ECX,ushort param_5,uint *param_6,
         byte param_7)

{
  byte bVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  uint uVar6;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  ushort *extraout_EDX_01;
  ushort uVar7;
  int iVar8;
  uint *puVar9;
  ulonglong uVar10;
  undefined local_c8 [7];
  undefined local_c1;
  uint local_c0;
  uint local_bc;
  uint local_b8;
  undefined2 uStack_b4;
  undefined2 local_b2;
  undefined2 uStack_b0;
  uint local_ae;
  uint local_aa;
  undefined local_a4;
  undefined auStack_a3 [6];
  undefined auStack_9d [6];
  undefined local_97;
  undefined local_96;
  undefined local_95;
  undefined local_94;
  undefined local_93;
  undefined local_92;
  undefined local_91;
  undefined2 local_90;
  undefined2 uStack_8e;
  char local_68 [6];
  byte local_62;
  int local_38;
  undefined *local_34;
  uint local_30;
  uint local_2c;
  uint local_18;
  uint local_10;
  
  uVar7 = 0;
  puVar9 = param_6;
  if (*(short *)(param_2 + 0x55) == 0) {
    uVar3 = 0;
  }
  else {
    do {
      uVar7 = uVar7 + 1;
      puVar9[5] = 0;
      puVar9 = (uint *)((int)puVar9 + 0x49);
    } while (uVar7 < *(ushort *)(param_2 + 0x55));
    uVar3 = 0;
  }
  while( true ) {
    bVar1 = *(byte *)(param_2 + 0x97);
    if (bVar1 <= uVar3) break;
    iVar4 = uVar3 * 4;
    uVar3 = uVar3 + 1;
    *(undefined4 *)(iVar4 + unaff_EBX + 2) = 0;
  }
  *(undefined2 *)(unaff_EBX + 0x1a) = 0x400;
  iVar4 = sub_b0a78(param_1);
  if (iVar4 < 0) {
    word_f799c = -(short)iVar4;
    uVar5 = 0x10;
  }
  else {
    if (iVar4 == -1) {
      return 0x11;
    }
    sVar2 = sub_b0a5c(iVar4,0xc0,0);
    if (sVar2 != 0) {
      sub_b0a40(iVar4);
      return extraout_EDX;
    }
    local_38 = 0;
    for (local_18 = 0; local_18 < bVar1; local_18 = local_18 + 1) {
      sVar2 = sub_b0a14(iVar4,local_68,0x2f);
      if (sVar2 != 0x2f) {
        sub_b0a40(iVar4);
        sub_aa758(unaff_EBX);
        return 0xe;
      }
      iVar8 = local_18 * 2 + unaff_EBX;
      if (local_68[0] == '\0') {
        *(ushort *)(iVar8 + 0x12) = (ushort)local_62;
        puVar9 = param_6;
        for (uVar7 = 0; uVar7 < local_62; uVar7 = uVar7 + 1) {
          sVar2 = sub_b0a14(iVar4,local_c8,0x60);
          if (sVar2 != 0x60) {
            sub_b0a40(iVar4);
            sub_aa758(unaff_EBX);
            return 0xe;
          }
          if (uVar7 == 0) {
            *(uint **)(local_18 * 4 + unaff_EBX + 2) = puVar9;
          }
          *puVar9 = local_bc;
          puVar9[1] = local_b8;
          *(undefined *)(puVar9 + 0xd) = local_c1;
          puVar9[2] = CONCAT22(uStack_b0,local_b2);
          puVar9[3] = local_ae;
          puVar9[4] = local_aa;
          *(undefined *)((int)puVar9 + 0x35) = local_a4;
          *(undefined2 *)(puVar9 + 6) = local_90;
          *(undefined2 *)(puVar9 + 7) = uStack_8e;
          *(undefined *)((int)puVar9 + 0x42) = local_97;
          *(undefined *)((int)puVar9 + 0x43) = local_96;
          *(undefined *)(puVar9 + 0x11) = local_95;
          *(undefined *)((int)puVar9 + 0x45) = local_94;
          *(undefined *)((int)puVar9 + 0x46) = local_93;
          *(undefined *)((int)puVar9 + 0x47) = local_92;
          *(undefined *)(puVar9 + 0x12) = local_91;
          *(undefined2 *)((int)puVar9 + 0x1a) = uStack_b4;
          puVar9[0xc] = local_c0;
          for (uVar3 = 0; uVar3 < 6; uVar3 = uVar3 + 1) {
            *(undefined *)((int)puVar9 + uVar3 + 0x36) = auStack_a3[uVar3];
            *(undefined *)((int)puVar9 + uVar3 + 0x3c) = auStack_9d[uVar3];
          }
          local_2c = puVar9[0xc];
          uVar3 = local_2c;
          if (((param_7 & 1) != 0) && ((*(byte *)(puVar9 + 0x12) & 1) != 0)) {
            uVar3 = local_2c >> 1;
          }
          uVar10 = sub_ad4dc(uVar3);
          local_30 = (uint)uVar10;
          if (local_30 == 0) {
            sub_b0a40(iVar4);
            sub_aa758(unaff_EBX);
            return 6;
          }
          puVar9[5] = local_30;
          while (iVar8 = local_38, local_2c != 0) {
            local_10 = (uint)param_5;
            if (local_2c < param_5) {
              local_10 = local_2c;
            }
            local_2c = local_2c - (local_10 & 0xffff);
            uVar3 = sub_b0a14(iVar4,*unaff_ECX,local_10 & 0xffff);
            if ((uVar3 & 0xffff) != (local_10 & 0xffff)) {
              sub_b0a40(iVar4);
              sub_aa758(unaff_EBX);
              return 0xe;
            }
            if (((param_7 & 1) != 0) && ((*(byte *)(puVar9 + 0x12) & 1) != 0)) {
              iVar8 = 0;
              for (uVar3 = 1; uVar3 < (local_10 & 0xffff); uVar3 = uVar3 + 2) {
                local_34 = (undefined *)(*unaff_ECX + iVar8);
                iVar8 = iVar8 + 1;
                *local_34 = *(undefined *)(*unaff_ECX + uVar3);
              }
              local_10 = local_10 >> 1 & 0x7fff;
            }
            iVar8 = sub_b0fa8();
            uVar3 = local_30;
            if (iVar8 != 0) {
LAB_000aa69c:
              sub_b0a40(iVar4,iVar8);
              sub_aa758(unaff_EBX);
              return extraout_EDX_00;
            }
            uVar6 = 0;
            if (((param_7 & 1) == 0) && ((*(byte *)(puVar9 + 0x12) & 1) != 0)) {
              uVar6 = 0x40;
            }
            if ((*(byte *)(puVar9 + 0x12) & 2) != 0) {
              uVar6 = uVar6 | 0x80;
            }
            iVar8 = sub_b0d6c(unaff_ECX,local_10 & 0xffff,local_30,uVar6,1);
            if ((iVar8 != 0) || (iVar8 = sub_b0fa8(0,0), iVar8 != 0)) goto LAB_000aa69c;
            local_30 = local_30 + (local_10 & 0xffff);
            uVar10 = (ulonglong)uVar3;
          }
          if (((param_7 & 1) != 0) && ((*(byte *)(puVar9 + 0x12) & 1) != 0)) {
            uVar3 = puVar9[0xc];
            *puVar9 = *puVar9 >> 1;
            uVar6 = puVar9[1];
            puVar9[0xc] = uVar3 >> 1;
            puVar9[1] = uVar6 >> 1;
            uVar10 = CONCAT44(uVar6 >> 1,CONCAT31((uint3)(uVar3 >> 9),*(byte *)(puVar9 + 0x12))) &
                     0xfffffffffffffffe;
            *(byte *)(puVar9 + 0x12) = *(byte *)(puVar9 + 0x12) & 0xfe;
          }
          sub_b10d0(puVar9,(int)(uVar10 >> 0x20),(int)uVar10);
          local_38 = iVar8 + 1;
          puVar9 = (uint *)((int)puVar9 + 0x49);
        }
      }
      else {
        *(int *)(local_18 * 4 + unaff_EBX + 2) = (local_38 + -1) * 0x49 + (int)param_6;
        *(undefined2 *)(iVar8 + 0x12) = *(undefined2 *)(iVar8 + 0x10);
      }
      local_38 = local_38 + 1;
    }
    sub_b0a40(iVar4,unaff_EBX);
    *extraout_EDX_01 = (ushort)bVar1;
    uVar5 = 0;
  }
  return uVar5;
}


// ================================================================================================
// sub_aa758 @ 0xaa758 [__watcall]
// ================================================================================================

void __watcall
sub_aa758(undefined4 param_1,undefined4 param_2,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  int iVar1;
  undefined4 extraout_EDX;
  undefined2 *extraout_EDX_00;
  undefined2 *extraout_EDX_01;
  undefined2 *puVar2;
  int iVar3;
  int iVar4;
  byte in_CF;
  byte in_PF;
  byte in_AF;
  byte in_ZF;
  byte in_SF;
  byte in_TF;
  byte in_IF;
  byte in_OF;
  byte in_NT;
  
  sub_b122f(param_1,param_1,unaff_EBX,unaff_ECX,
            (ushort)(in_NT & 1) * 0x4000 | (ushort)(in_OF & 1) * 0x800 | (ushort)(in_IF & 1) * 0x200
            | (ushort)(in_TF & 1) * 0x100 | (ushort)(in_SF & 1) * 0x80 | (ushort)(in_ZF & 1) * 0x40
            | (ushort)(in_AF & 1) * 0x10 | (ushort)(in_PF & 1) * 4 | (ushort)(in_CF & 1));
  sub_ad160(extraout_EDX);
  puVar2 = extraout_EDX_00;
  for (iVar1 = 0; iVar1 < *(int *)(puVar2 + -1) >> 0x10; iVar1 = iVar1 + 1) {
    iVar3 = *(int *)(puVar2 + iVar1 * 2 + 1);
    for (iVar4 = 0; iVar4 < *(int *)(puVar2 + iVar1 + 8) >> 0x10; iVar4 = iVar4 + 1) {
      if (*(int *)(iVar3 + 0x14) != 0) {
        sub_ad610(*(int *)(iVar3 + 0x14));
        *(undefined4 *)(iVar3 + 0x14) = 0;
        puVar2 = extraout_EDX_01;
      }
      iVar3 = iVar3 + 0x49;
    }
  }
  *puVar2 = 0;
  sub_ad260(puVar2);
  sub_b1256();
  return;
}


// ================================================================================================
// sub_aa7cc @ 0xaa7cc [__watcall]
// ================================================================================================

void __watcall sub_aa7cc(int param_1,undefined2 unaff_DX)

{
  *(undefined2 *)(param_1 + 0x1a) = unaff_DX;
  return;
}


// ================================================================================================
// sub_aa7e0 @ 0xaa7e0 [__watcall]
// ================================================================================================

void __watcall
sub_aa7e0(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  int iVar1;
  int extraout_EDX;
  
  sub_aa200(word_d8772,0x41,unaff_EBX,unaff_ECX,unaff_EDX);
  sub_aa200(word_d8776,0);
  sub_aa200(word_d8772,0x45);
  sub_aa200(word_d8776,0);
  sub_aa200(word_d8772,0x49);
  sub_aa200(word_d8776,0);
  sub_b128c(word_d8762);
  sub_aa200(word_d8772,0x41);
  sub_b128c(word_d8776);
  sub_aa200(word_d8772,0x49);
  sub_b128c(word_d8776);
  sub_aa200(word_d8772,0x8f);
  iVar1 = 0;
  do {
    sub_b128c(word_d8776,iVar1 + 1);
    iVar1 = extraout_EDX;
  } while (extraout_EDX < 0x20);
  return;
}


// ================================================================================================
// sub_aa8c0 @ 0xaa8c0 [__watcall]
// ================================================================================================

void __watcall sub_aa8c0(int param_1,int unaff_EDX)

{
  if (param_1 != unaff_EDX) {
    sub_b0b5c(unaff_EDX);
  }
  sub_b0b5c(param_1);
  return;
}


// ================================================================================================
// sub_aa8e0 @ 0xaa8e0 [__watcall]
// ================================================================================================

void __watcall sub_aa8e0(int param_1,undefined4 unaff_EDX)

{
  int extraout_EDX;
  undefined2 in_CS;
  
  sub_b0abc(param_1,unaff_EDX,sub_b12a0,in_CS);
  if (param_1 != extraout_EDX) {
    sub_b0abc(extraout_EDX,extraout_EDX,sub_b131c,in_CS);
  }
  return;
}


// ================================================================================================
// sub_aa910 @ 0xaa910 [__watcall]
// ================================================================================================

int __watcall
sub_aa910(undefined4 param_1,byte unaff_DL,byte unaff_BL,undefined unaff_CL,undefined param_5,
         undefined4 param_6)

{
  int iVar1;
  byte in_AF;
  byte in_TF;
  byte in_IF;
  byte in_NT;
  ushort uVar2;
  byte local_c [4];
  
  uVar2 = (ushort)(in_NT & 1) * 0x4000 | (ushort)SBORROW4((int)&stack0xfffffff8,4) * 0x800 |
          (ushort)(in_IF & 1) * 0x200 | (ushort)(in_TF & 1) * 0x100 |
          (ushort)((int)local_c < 0) * 0x80 | (ushort)(&stack0x00000000 == (undefined *)0xc) * 0x40
          | (ushort)(in_AF & 1) * 0x10 | (ushort)((POPCOUNT((uint)local_c & 0xff) & 1U) == 0) * 4 |
          (ushort)(&stack0xfffffff8 < (undefined *)0x4);
  local_c[0] = unaff_DL;
  iVar1 = sub_b13b5(param_1);
  if (iVar1 == 0) {
    sub_b121c();
    sub_b1400();
    if ((&unk_d7a2c)[local_c[0]] == '\0') {
      return 2;
    }
    byte_f79a8 = local_c[0];
    if ((&unk_d7a2c)[unaff_BL] == '\0') {
      return 2;
    }
    byte_f79a6 = param_5;
    byte_f79a4 = unaff_CL;
    byte_f79a7 = unaff_BL;
    sub_aae40(param_6,0,unaff_BL,param_6,uVar2);
    sub_aa8e0(byte_f79a8,byte_f79a7);
    iVar1 = 0;
  }
  return iVar1;
}


// ================================================================================================
// sub_aa9c0 @ 0xaa9c0 [__watcall]
// ================================================================================================

void __watcall sub_aa9c0(void)

{
  uint uVar1;
  undefined4 unaff_ECX;
  uint uVar2;
  byte in_CF;
  byte in_PF;
  byte in_AF;
  byte in_ZF;
  byte in_SF;
  byte in_TF;
  byte in_IF;
  byte in_OF;
  byte in_NT;
  ushort uVar3;
  
  uVar3 = (ushort)(in_NT & 1) * 0x4000 | (ushort)(in_OF & 1) * 0x800 | (ushort)(in_IF & 1) * 0x200 |
          (ushort)(in_TF & 1) * 0x100 | (ushort)(in_SF & 1) * 0x80 | (ushort)(in_ZF & 1) * 0x40 |
          (ushort)(in_AF & 1) * 0x10 | (ushort)(in_PF & 1) * 4 | (ushort)(in_CF & 1);
  sub_b122f();
  uVar2 = 0;
  if (word_f79a0 == 0) {
    uVar2 = 0;
  }
  else {
    do {
      sub_aa200(word_d8770,uVar2 & 0xffff,uVar2,unaff_ECX,uVar3);
      sub_aa200(word_d8772,0xd);
      sub_aa200(word_d8776,3);
      sub_b13a1();
      sub_aa200(word_d8776,3);
      sub_b13a1();
      sub_aa200(word_d8772,0x89);
      uVar1 = sub_b1951(word_d8774);
      if (5 < uVar1 >> 8) {
        sub_aa200(word_d8772,7);
        sub_aa200(word_d8776,5);
        sub_aa200(word_d8772,6);
        sub_aa200(word_d8776,1);
        sub_aa200(word_d8772,0xd);
        sub_aa200(word_d8776,0x40);
      }
      uVar2 = uVar2 + 1;
    } while ((ushort)uVar2 < word_f79a0);
    uVar2 = 0;
  }
  for (; (ushort)uVar2 < word_f79a0; uVar2 = uVar2 + 1) {
    sub_aa200(word_d8770,uVar2 & 0xffff,uVar2,unaff_ECX,uVar3);
    do {
      sub_aa200(word_d8772,0x8d,uVar2,unaff_ECX,uVar3);
      uVar1 = sub_b128c(word_d8776);
    } while ((uVar1 & 3) == 0);
    sub_aa200(word_d8772,0);
    sub_aa200(word_d8776,3);
    sub_b13a1();
    sub_aa200(word_d8776,3);
  }
  sub_b1256();
  return;
}


// ================================================================================================
// sub_aab5c @ 0xaab5c [__watcall]
// ================================================================================================

undefined8 __watcall sub_aab5c(undefined2 *param_1,undefined4 unaff_EDX,undefined4 unaff_EBX)

{
  int iVar1;
  byte in_AF;
  byte in_TF;
  byte in_IF;
  byte in_NT;
  ushort uVar2;
  
  if (dword_d7a28 == 0) {
    word_f799e = 0;
    uVar2 = (ushort)(in_NT & 1) * 0x4000 | (ushort)(in_IF & 1) * 0x200 | (ushort)(in_TF & 1) * 0x100
            | 0x40 | (ushort)(in_AF & 1) * 0x10 | 4;
    iVar1 = sub_af2e0(param_1[1]);
    if (iVar1 == 0) {
      return CONCAT44(unaff_EDX,10);
    }
    byte_f79a5 = 3;
    sub_aa200(param_1[1],3,unaff_EBX,0,uVar2);
    iVar1 = sub_aa910(param_1[1],*(undefined *)(param_1 + 2),*(undefined *)((int)param_1 + 5),
                      *(undefined *)((int)param_1 + 7),*(undefined *)(param_1 + 3),*param_1);
    if (iVar1 != 0) {
      return CONCAT44(unaff_EDX,iVar1);
    }
    sub_aacac();
    word_f799e = word_f799e | 1;
    dword_d7a28 = dword_d7a28 + 1;
    iVar1 = sub_b195c();
    if (iVar1 == 0) {
      byte_f79a5 = byte_f79a5 & 0xfd;
      sub_aa200(param_1[1],byte_f79a5);
      iVar1 = 0;
    }
  }
  else {
    dword_d7a28 = dword_d7a28 + 1;
    iVar1 = 0;
  }
  return CONCAT44(unaff_EDX,iVar1);
}


// ================================================================================================
// sub_aac48 @ 0xaac48 [__watcall]
// ================================================================================================

undefined8 __watcall
sub_aac48(undefined4 param_1,undefined4 unaff_EDX,undefined4 unaff_EBX,undefined4 unaff_ECX)

{
  undefined4 uVar1;
  byte in_AF;
  byte in_TF;
  byte in_IF;
  bool bVar2;
  byte in_NT;
  ushort uVar3;
  
  if ((word_f799e & 1) == 0) {
    uVar1 = 5;
  }
  else {
    bVar2 = SBORROW4(dword_d7a28,1);
    dword_d7a28 = dword_d7a28 - 1;
    if (dword_d7a28 == 0) {
      uVar3 = (ushort)(in_NT & 1) * 0x4000 | (ushort)bVar2 * 0x800 | (ushort)(in_IF & 1) * 0x200 |
              (ushort)(in_TF & 1) * 0x100 | (ushort)((int)dword_d7a28 < 0) * 0x80 |
              (ushort)(dword_d7a28 == 0) * 0x40 | (ushort)(in_AF & 1) * 0x10 |
              (ushort)((POPCOUNT(dword_d7a28 & 0xff) & 1U) == 0) * 4;
      sub_aa9c0();
      sub_aa7e0();
      sub_aa8c0(byte_f79a8,byte_f79a7,unaff_EBX,unaff_ECX,uVar3);
      word_f799e = word_f799e & 0xfffe;
    }
    uVar1 = 0;
  }
  return CONCAT44(unaff_EDX,uVar1);
}


// ================================================================================================
// sub_aacac @ 0xaacac [__watcall]
// ================================================================================================

void __watcall sub_aacac(void)

{
  byte bVar1;
  byte bVar2;
  byte in_AF;
  byte in_TF;
  byte in_IF;
  byte in_NT;
  
  if (byte_f79a8 == byte_f79a7) {
    bVar2 = (&unk_d7a2c)[byte_f79a8] | 0x40;
  }
  else {
    bVar2 = (&unk_d7a2c)[byte_f79a8] | (&unk_d7a2c)[byte_f79a7] << 3;
  }
  if (byte_f79a4 == byte_f79a6) {
    bVar1 = (&unk_d877a)[byte_f79a4] | 0x40;
  }
  else {
    bVar1 = (&unk_d877a)[byte_f79a4] | (&unk_d877a)[byte_f79a6] << 3;
  }
  sub_aa200(word_d876a,5,bVar2,bVar1,
            (ushort)(in_NT & 1) * 0x4000 | (ushort)(in_IF & 1) * 0x200 | (ushort)(in_TF & 1) * 0x100
            | (ushort)((char)bVar1 < '\0') * 0x80 | (ushort)(bVar1 == 0) * 0x40 |
            (ushort)(in_AF & 1) * 0x10 | (ushort)((POPCOUNT(bVar1) & 1U) == 0) * 4);
  sub_aa200(word_d8760,byte_f79a5);
  sub_aa200(word_d8768,0);
  sub_aa200(word_d876a,0);
  sub_aa200(word_d8760,byte_f79a5);
  sub_aa200(word_d8768,bVar1 | 0x80);
  sub_aa200(word_d8760,byte_f79a5 | 0x40);
  sub_aa200(word_d8768,bVar2);
  sub_aa200(word_d8760,byte_f79a5);
  sub_aa200(word_d8768,bVar1);
  sub_aa200(word_d8760,byte_f79a5 | 0x40);
  sub_aa200(word_d8768,bVar2);
  sub_aa200(word_d876a,0);
  byte_f79a5 = byte_f79a5 | 8;
  sub_aa200(word_d8760,byte_f79a5);
  sub_aa200(word_d876a,0);
  return;
}


// ================================================================================================
// sub_aae40 @ 0xaae40 [__watcall]
// ================================================================================================

void __watcall sub_aae40(uint param_1,undefined4 param_2,undefined4 param_3,undefined4 unaff_ECX)

{
  uint uVar1;
  ushort uVar2;
  bool bVar3;
  byte in_AF;
  byte in_TF;
  byte in_IF;
  bool bVar4;
  byte in_NT;
  
  if ((int)param_1 < 0xe) {
    param_1 = 0xe;
  }
  bVar3 = param_1 < 0x20;
  bVar4 = SBORROW4(param_1,0x20);
  uVar1 = param_1 - 0x20;
  if (uVar1 != 0 && 0x1f < (int)param_1) {
    param_1 = 0x20;
  }
  word_f79a0 = 0x20;
  sub_aa200(word_d8772,0x4c,param_1,unaff_ECX,
            (ushort)(in_NT & 1) * 0x4000 | (ushort)bVar4 * 0x800 | (ushort)(in_IF & 1) * 0x200 |
            (ushort)(in_TF & 1) * 0x100 | (ushort)((int)uVar1 < 0) * 0x80 |
            (ushort)(uVar1 == 0) * 0x40 | (ushort)(in_AF & 1) * 0x10 |
            (ushort)((POPCOUNT(uVar1 & 0xff) & 1U) == 0) * 4 | (ushort)bVar3);
  sub_aa200(word_d8776,0);
  sub_b13a1();
  sub_b13a1();
  sub_aa200(word_d8772,0x4c);
  sub_aa200(word_d8776,1);
  sub_b13a1();
  sub_b13a1();
  sub_aa200(word_d8772,0xe);
  sub_aa200(word_d8776,(char)word_f79a0 - 1U | 0xc0);
  sub_aa7e0();
  for (uVar2 = 0; uVar2 < word_f79a0; uVar2 = uVar2 + 1) {
    sub_aa200(word_d8770,uVar2);
    sub_aa200(word_d8772,0);
    sub_aa200(word_d8776,3);
    sub_aa200(word_d8772,0xd);
    sub_aa200(word_d8776,3);
    sub_b13a1();
    sub_aa200(word_d8772,0);
    sub_aa200(word_d8776,3);
    sub_aa200(word_d8772,0xd);
    sub_aa200(word_d8776,3);
    sub_aa200(word_d8772,2);
    sub_b19c7(word_d8774,0);
    sub_aa200(word_d8772,3);
    sub_b19c7(word_d8774,0);
    sub_aa200(word_d8772,4);
    sub_b19c7(word_d8774,0);
    sub_aa200(word_d8772,5);
    sub_b19c7(word_d8774,0);
    sub_aa200(word_d8772,6);
    sub_aa200(word_d8776,0x3f);
    sub_aa200(word_d8772,7);
    sub_aa200(word_d8776,5);
    sub_aa200(word_d8772,8);
    sub_aa200(word_d8776,0xfb);
    sub_aa200(word_d8772,9);
    sub_b19c7(word_d8774,0x500);
    sub_aa200(word_d8772,10);
    sub_b19c7(word_d8774,0);
    sub_aa200(word_d8772,0xb);
    sub_b19c7(word_d8774,0x6000);
  }
  sub_aa7e0();
  word_f79a0 = (ushort)param_1;
  sub_aa200(word_d8772,0xe);
  sub_aa200(word_d8776,(char)word_f79a0 - 1U | 0xc0);
  sub_aa7e0();
  sub_aa200(word_d8772,0x4c);
  sub_aa200(word_d8776,7);
  sub_b13a1();
  sub_b13a1();
  return;
}


// ================================================================================================
// sub_ab180 @ 0xab180 [__watcall]
// ================================================================================================

undefined8 __watcall sub_ab180(undefined4 param_1,undefined4 unaff_EDX)

{
  undefined4 *puVar1;
  undefined *puVar2;
  int iVar3;
  
  byte_d87d8 = 1;
  byte_d7aec = 1;
  puVar1 = &unk_f5bf8;
  for (iVar3 = 0; iVar3 < 0x20; iVar3 = iVar3 + 1) {
    *(undefined *)((int)puVar1 + 0x13) = 0;
    *(undefined *)(puVar1 + 5) = 0;
    *(undefined *)((int)puVar1 + 0x15) = 0x40;
    *(undefined *)(puVar1 + 7) = 0x7f;
    *(undefined2 *)((int)puVar1 + 0x11) = 0xff;
    *(undefined *)((int)puVar1 + 0x1a) = 1;
    *(undefined *)((int)puVar1 + 0x16) = 0;
    puVar1 = (undefined4 *)((int)puVar1 + 0x21);
  }
  puVar2 = &unk_f59f8;
  for (iVar3 = 0; iVar3 < 0x20; iVar3 = iVar3 + 1) {
    *puVar2 = 0;
    puVar2[1] = 100;
    *(undefined2 *)(puVar2 + 2) = 0x400;
    *(undefined4 *)(puVar2 + 4) = 0;
    puVar2[9] = 0;
    puVar2[10] = 0;
    puVar2[0xb] = 0;
    puVar2[0xc] = 0;
    puVar2[0xd] = 0;
    puVar2[0xe] = 0;
    puVar2[8] = 0x10;
    puVar2 = puVar2 + 0x10;
  }
  word_f611a = 0;
  dword_f6116._2_2_ = 0x7f;
  iVar3 = sub_b151c(sub_acd58);
  if (iVar3 == 0) {
    iVar3 = sub_b14e4(sub_accc0);
    if (iVar3 == 0) goto LAB_000ab23b;
  }
  iVar3 = 8;
LAB_000ab23b:
  return CONCAT44(unaff_EDX,iVar3);
}


// ================================================================================================
// sub_ab244 @ 0xab244 [__watcall]
// ================================================================================================

void __watcall sub_ab244(int param_1)

{
  byte bVar1;
  undefined uVar2;
  int iVar3;
  undefined2 uVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  int extraout_EDX;
  int iVar8;
  int *piVar9;
  uint uVar10;
  uint uVar11;
  byte in_AF;
  byte in_TF;
  byte in_IF;
  byte in_NT;
  ushort uVar12;
  int local_24;
  uint local_20;
  uint local_1c;
  uint local_18;
  
  uVar12 = (ushort)(in_NT & 1) * 0x4000 | (ushort)SBORROW4((int)&stack0xffffffec,0x10) * 0x800 |
           (ushort)(in_IF & 1) * 0x200 | (ushort)(in_TF & 1) * 0x100 |
           (ushort)((int)&local_24 < 0) * 0x80 |
           (ushort)(&stack0x00000000 == (undefined *)0x24) * 0x40 | (ushort)(in_AF & 1) * 0x10 |
           (ushort)((POPCOUNT((uint)&local_24 & 0xff) & 1U) == 0) * 4 |
           (ushort)(&stack0xffffffec < (undefined *)0x10);
  sub_b122f();
  iVar3 = param_1 * 0x21;
  piVar9 = (int *)((int)&unk_f5bf8 + iVar3);
  if (byte_d7aec == '\0') {
    iVar5 = ((byte)(&DAT_000f5c14)[iVar3] + 0x80) * ((dword_f6116 >> 0x10) + 0x40);
    uVar10 = extraout_EDX + 0x80;
  }
  else {
    iVar5 = ((dword_f6116 >> 0x10) + 0x40) * (uint)(byte)(&unk_d7a3c)[(byte)(&DAT_000f5c14)[iVar3]];
    uVar10 = (uint)(byte)(&unk_d7a3c)[extraout_EDX];
  }
  *(short *)((int)&DAT_000f5c09 + iVar3) = (short)((int)(uVar10 * iVar5) / 0xbe41);
  if ((*(char *)(*piVar9 + 0x44) != '\0') ||
     ((&unk_f5a04)[(uint)(byte)(&DAT_000f5c15)[iVar3] * 0x10] != '\0')) {
    sub_abc38(param_1,(&DAT_000f5c15)[iVar3],piVar9,param_1,uVar12);
  }
  sub_aa200(word_d8770,param_1);
  uVar4 = word_d8772;
  (&DAT_000f5c0d)[iVar3] = (&DAT_000f5c0d)[iVar3] & 0x47;
  sub_aa200(uVar4,0xd);
  sub_aa200(word_d8776,3);
  sub_b13a1();
  sub_aa200(word_d8776,3);
  sub_aa200(word_d8772,0x89);
  iVar5 = sub_b1951(word_d8774);
  uVar10 = (uint)(byte)(&DAT_000f5c13)[iVar3];
  if ((&DAT_000f5c0e)[iVar3] == '\0') {
    if (((&DAT_000f5c17)[iVar3] == (&DAT_000f5c18)[iVar3]) ||
       (((uVar10 == 3 && ((*(byte *)(*piVar9 + 0x48) & 0x20) != 0)) &&
        (((&unk_f5c0b)[iVar3] & 2) != 0)))) {
LAB_000ab3c6:
      *(undefined4 *)(&DAT_000f5bfc + iVar3) = 0x400;
    }
    else {
      iVar6 = (int)(((iVar5 >> 4) + (uint)(byte)(&DAT_000f5c18)[iVar3] * -0x10) * 0x400) /
              (int)(((uint)(byte)(&DAT_000f5c17)[iVar3] - (uint)(byte)(&DAT_000f5c18)[iVar3]) * 0x10
                   );
      *(int *)(&DAT_000f5bfc + iVar3) = iVar6;
      if (iVar6 < 0) {
        *(int *)(&DAT_000f5bfc + iVar3) = -iVar6;
      }
      else if (iVar6 == 0) goto LAB_000ab3c6;
    }
    if (0x400 < *(int *)(&DAT_000f5bfc + iVar3)) {
      *(undefined4 *)(&DAT_000f5bfc + iVar3) = 0x400;
    }
  }
  if (uVar10 == 0) {
    uVar7 = ((uint)*(byte *)(*piVar9 + 0x3c) * (uint)*(ushort *)((int)&DAT_000f5c09 + iVar3)) / 0xff
    ;
    local_18 = 0;
  }
  else if (uVar10 < 6) {
    if ((uVar10 == 3) && ((*(byte *)(*piVar9 + 0x48) & 0x20) != 0)) {
      if (((&unk_f5c0b)[iVar3] & 2) != 0) {
        uVar7 = ((uint)*(ushort *)((int)&DAT_000f5c09 + iVar3) * (uint)(byte)(&DAT_000f5c16)[iVar3])
                / 0xff;
        local_18 = uVar7;
        goto LAB_000ab4bf;
      }
      uVar11 = (uint)*(ushort *)((int)&DAT_000f5c09 + iVar3);
      uVar7 = *(byte *)(*piVar9 + 0x3f) * uVar11;
      bVar1 = (&DAT_000f5c16)[iVar3];
    }
    else {
      local_24 = *piVar9 + uVar10;
      uVar11 = (uint)*(ushort *)((int)&DAT_000f5c09 + iVar3);
      uVar7 = *(byte *)(local_24 + 0x3c) * uVar11;
      bVar1 = *(byte *)(local_24 + 0x3b);
    }
    uVar7 = uVar7 / 0xff;
    local_18 = (bVar1 * uVar11) / 0xff;
  }
  else {
    uVar7 = ((uint)*(ushort *)((int)&DAT_000f5c09 + iVar3) * (uint)*(byte *)(*piVar9 + 0x41)) / 0xff
    ;
    local_18 = uVar7;
  }
LAB_000ab4bf:
  if (uVar7 < 5) {
    uVar7 = 5;
  }
  if (local_18 < 5) {
    local_18 = 5;
  }
  iVar6 = (uVar7 - local_18) * *(int *)(&DAT_000f5bfc + iVar3) + 0x200;
  iVar8 = iVar6 >> 0x1f;
  local_1c = local_18 + ((int)((iVar6 + iVar8 * -0x400) - (uint)(iVar8 << 9 < 0)) >> 10);
  if (local_1c < 0xfc) {
    if (local_1c < 5) {
      local_1c = 5;
    }
  }
  else {
    local_1c = 0xfb;
  }
  local_20 = (uint)(iVar5 >> 4) >> 4;
  if (local_1c < local_20) {
    (&DAT_000f5c0d)[iVar3] = (&DAT_000f5c0d)[iVar3] | 0x40;
    sub_aa200(word_d8772,7);
    sub_aa200(word_d8776,local_1c & 0xff);
    sub_aa200(word_d8772,8);
    uVar2 = (undefined)local_20;
  }
  else {
    uVar11 = local_1c;
    if ((local_1c <= local_20) || (uVar11 = local_20, 3 < uVar10)) goto LAB_000ab5c4;
    (&DAT_000f5c0d)[iVar3] = (&DAT_000f5c0d)[iVar3] & 0xbf;
    sub_aa200(word_d8772,7);
    sub_aa200(word_d8776,local_20 & 0xff);
    sub_aa200(word_d8772,8);
    uVar2 = (undefined)local_1c;
  }
  sub_aa200(word_d8776,uVar2);
  uVar11 = local_1c;
LAB_000ab5c4:
  local_1c = uVar11;
  if (local_1c != local_20) {
    (&DAT_000f5c18)[iVar3] = (undefined)local_18;
    uVar4 = word_d8772;
    (&DAT_000f5c17)[iVar3] = (char)uVar7;
    sub_aa200(uVar4,6);
    sub_aa200(word_d8776,0x43);
  }
  (&DAT_000f5c0e)[iVar3] = (&DAT_000f5c13)[iVar3] + '\x01';
  (&DAT_000f5c0d)[iVar3] = (&DAT_000f5c0d)[iVar3] | 0x20;
  sub_aa200(word_d8772,0xd);
  sub_aa200(word_d8776,(&DAT_000f5c0d)[iVar3]);
  sub_b13a1();
  sub_aa200(word_d8776,(&DAT_000f5c0d)[iVar3]);
  sub_b1256();
  return;
}


// ================================================================================================
// sub_ab658 @ 0xab658 [__watcall]
// ================================================================================================

void __watcall sub_ab658(int param_1,uint unaff_EDX)

{
  uint uVar1;
  undefined4 *puVar2;
  bool bVar3;
  bool bVar4;
  byte in_AF;
  bool bVar5;
  bool bVar6;
  byte in_TF;
  byte in_IF;
  bool bVar7;
  byte in_NT;
  ushort uVar8;
  char local_14;
  
  bVar3 = unaff_EDX == 0;
  bVar7 = SBORROW4(unaff_EDX,1);
  uVar1 = unaff_EDX - 1;
  bVar6 = (int)uVar1 < 0;
  bVar5 = uVar1 == 0;
  bVar4 = (POPCOUNT(uVar1 & 0xff) & 1U) == 0;
  if (bVar3) {
    unaff_EDX = 1;
  }
  else {
    bVar3 = unaff_EDX < 0x7f;
    bVar7 = SBORROW4(unaff_EDX,0x7f);
    uVar1 = unaff_EDX - 0x7f;
    bVar6 = (int)uVar1 < 0;
    bVar5 = uVar1 == 0;
    bVar4 = (POPCOUNT(uVar1 & 0xff) & 1U) == 0;
    if (!bVar3 && !bVar5) {
      unaff_EDX = 0x7f;
    }
  }
  uVar8 = (ushort)(in_NT & 1) * 0x4000 | (ushort)bVar7 * 0x800 | (ushort)(in_IF & 1) * 0x200 |
          (ushort)(in_TF & 1) * 0x100 | (ushort)bVar6 * 0x80 | (ushort)bVar5 * 0x40 |
          (ushort)(in_AF & 1) * 0x10 | (ushort)bVar4 * 4 | (ushort)bVar3;
  sub_b122f();
  puVar2 = &unk_f5bf8;
  (&unk_f59f9)[param_1 * 0x10] = (char)unaff_EDX;
  for (uVar1 = 0; uVar1 < word_f79a0; uVar1 = uVar1 + 1) {
    if (((*(byte *)((int)puVar2 + 0x13) & 1) != 0) &&
       (local_14 = (char)param_1, local_14 == *(char *)((int)puVar2 + 0x1d))) {
      sub_ab244(uVar1,unaff_EDX,unaff_EDX,uVar1,uVar8);
    }
    puVar2 = (undefined4 *)((int)puVar2 + 0x21);
  }
  sub_b1256();
  return;
}


// ================================================================================================
// sub_ab6d0 @ 0xab6d0 [__watcall]
// ================================================================================================

void __watcall sub_ab6d0(int param_1,int unaff_EDX)

{
  int *piVar1;
  uint uVar2;
  byte in_AF;
  byte in_TF;
  byte in_IF;
  byte in_NT;
  ushort uVar3;
  int local_18;
  
  uVar3 = (ushort)(in_NT & 1) * 0x4000 | (ushort)SBORROW4((int)&stack0xffffffec,4) * 0x800 |
          (ushort)(in_IF & 1) * 0x200 | (ushort)(in_TF & 1) * 0x100 |
          (ushort)((int)&local_18 < 0) * 0x80 |
          (ushort)(&stack0x00000000 == (undefined *)0x18) * 0x40 | (ushort)(in_AF & 1) * 0x10 |
          (ushort)((POPCOUNT((uint)&local_18 & 0xff) & 1U) == 0) * 4 |
          (ushort)(&stack0xffffffec < (undefined *)0x4);
  local_18 = param_1;
  sub_b122f();
  piVar1 = &unk_f5bf8;
  uVar2 = 0;
  while( true ) {
    if (word_f79a0 <= uVar2) break;
    if (((*(byte *)((int)piVar1 + 0x13) & 1) != 0) &&
       ((char)local_18 == *(char *)((int)piVar1 + 0x1d))) {
      *(short *)((int)piVar1 + 10) = (short)((int)((uint)*(ushort *)(piVar1 + 2) * unaff_EDX) >> 10)
      ;
      if ((*(char *)(*piVar1 + 0x47) != '\0') || ((&unk_f5a01)[local_18 * 0x10] != '\0')) {
        sub_abad8(uVar2,1,local_18,piVar1,uVar3);
      }
      sub_aa200(word_d8770,uVar2);
      sub_aa200(word_d8772,1);
      sub_b19c7(word_d8774,(uint)*(ushort *)((int)piVar1 + 10) * 2);
    }
    uVar2 = uVar2 + 1;
    piVar1 = (int *)((int)piVar1 + 0x21);
  }
  (&unk_f59fa)[local_18 * 8] = (short)unaff_EDX;
  sub_b1256();
  return;
}


// ================================================================================================
// sub_ab79c @ 0xab79c [__watcall]
// ================================================================================================

void __watcall sub_ab79c(uint param_1)

{
  undefined4 *puVar1;
  uint uVar2;
  bool bVar3;
  bool bVar4;
  byte in_AF;
  bool bVar5;
  bool bVar6;
  byte in_TF;
  byte in_IF;
  bool bVar7;
  byte in_NT;
  ushort uVar8;
  
  bVar3 = param_1 == 0;
  bVar7 = SBORROW4(param_1,1);
  uVar2 = param_1 - 1;
  bVar6 = (int)uVar2 < 0;
  bVar5 = uVar2 == 0;
  bVar4 = (POPCOUNT(uVar2 & 0xff) & 1U) == 0;
  if ((int)param_1 < 1) {
    param_1 = 1;
  }
  else {
    bVar3 = param_1 < 0x7f;
    bVar7 = SBORROW4(param_1,0x7f);
    uVar2 = param_1 - 0x7f;
    bVar6 = (int)uVar2 < 0;
    bVar5 = uVar2 == 0;
    bVar4 = (POPCOUNT(uVar2 & 0xff) & 1U) == 0;
    if (!bVar5 && 0x7e < (int)param_1) {
      param_1 = 0x7f;
    }
  }
  puVar1 = &unk_f5bf8;
  dword_f6116._2_2_ = (undefined2)param_1;
  uVar8 = (ushort)(in_NT & 1) * 0x4000 | (ushort)bVar7 * 0x800 | (ushort)(in_IF & 1) * 0x200 |
          (ushort)(in_TF & 1) * 0x100 | (ushort)bVar6 * 0x80 | (ushort)bVar5 * 0x40 |
          (ushort)(in_AF & 1) * 0x10 | (ushort)bVar4 * 4 | (ushort)bVar3;
  sub_b122f();
  for (uVar2 = 0; uVar2 < word_f79a0; uVar2 = uVar2 + 1) {
    if ((*(byte *)((int)puVar1 + 0x13) & 1) != 0) {
      sub_ab244(uVar2,(&unk_f59f9)[(uint)*(byte *)((int)puVar1 + 0x1d) * 0x10],uVar2,puVar1,uVar8);
    }
    puVar1 = (undefined4 *)((int)puVar1 + 0x21);
  }
  sub_b1256();
  return;
}


// ================================================================================================
// sub_ab80c @ 0xab80c [__watcall]
// ================================================================================================

void __watcall sub_ab80c(int param_1,int unaff_EDX,undefined unaff_BL)

{
  char cVar1;
  bool bVar2;
  int *piVar3;
  int iVar4;
  short sVar5;
  uint uVar6;
  uint uVar7;
  byte in_AF;
  byte in_TF;
  byte in_IF;
  bool bVar8;
  byte in_NT;
  ushort uVar9;
  char local_1c;
  
  bVar8 = false;
  if (unaff_EDX == 0) {
    iVar4 = 0;
  }
  else {
    iVar4 = unaff_EDX * 0x1e >> 0x1f;
    iVar4 = (int)((unaff_EDX * 0x1e + iVar4 * -0x80) - (uint)(iVar4 << 6 < 0)) >> 7;
    bVar8 = SCARRY4(iVar4,2);
    iVar4 = iVar4 + 2;
    unaff_BL = 200;
  }
  uVar6 = param_1 * 0x10;
  uVar9 = (ushort)(in_NT & 1) * 0x4000 | (ushort)bVar8 * 0x800 | (ushort)(in_IF & 1) * 0x200 |
          (ushort)(in_TF & 1) * 0x100 | (ushort)((int)uVar6 < 0) * 0x80 |
          (ushort)(uVar6 == 0) * 0x40 | (ushort)(in_AF & 1) * 0x10 |
          (ushort)((POPCOUNT(uVar6 & 0xff) & 1U) == 0) * 4 | (ushort)(param_1 << 3 < 0);
  sub_b122f();
  (&DAT_000f5a03)[uVar6] = 0;
  piVar3 = &unk_f5bf8;
  cVar1 = (&unk_f5a01)[uVar6];
  (&DAT_000f5a02)[uVar6] = unaff_BL;
  uVar7 = 0;
  (&unk_f5a01)[uVar6] = (char)iVar4;
  do {
    if (word_f79a0 <= uVar7) {
      sub_b1256();
      return;
    }
    if (((*(byte *)((int)piVar3 + 0x13) & 1) != 0) &&
       (local_1c = (char)param_1, local_1c == *(char *)((int)piVar3 + 0x1d))) {
      if ((cVar1 == '\0') && (*(char *)(*piVar3 + 0x47) == '\0')) {
        bVar8 = false;
      }
      else {
        bVar8 = true;
      }
      if ((iVar4 == 0) && (*(char *)(*piVar3 + 0x47) == '\0')) {
        bVar2 = false;
      }
      else {
        bVar2 = true;
      }
      if (bVar2 != bVar8) {
        if (bVar2) {
          sVar5 = word_f611a + 1;
          bVar8 = word_f611a == 0;
          word_f611a = sVar5;
          if (bVar8) {
            sub_abab0();
            goto LAB_000ab91a;
          }
        }
        if (!bVar2) {
          word_f611a = word_f611a + -1;
          if (word_f611a == 0) {
            sub_abacc();
          }
        }
      }
LAB_000ab91a:
      if ((*(char *)(*piVar3 + 0x47) != '\0') || ((&unk_f5a01)[uVar6] != '\0')) {
        sub_abad8(uVar7,iVar4 == 0,param_1,piVar3,uVar9);
      }
    }
    uVar7 = uVar7 + 1;
    piVar3 = (int *)((int)piVar3 + 0x21);
  } while( true );
}


