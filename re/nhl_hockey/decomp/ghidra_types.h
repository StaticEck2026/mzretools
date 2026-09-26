// Basic types used by the Ghidra decompiler output
#pragma once
typedef unsigned char undefined; typedef unsigned char undefined1; typedef unsigned short undefined2;
typedef unsigned int undefined3; typedef unsigned int undefined4; typedef unsigned long long undefined6;
typedef unsigned long long undefined8; typedef unsigned char byte; typedef unsigned short ushort;
typedef unsigned int uint; typedef unsigned int uint3; typedef unsigned long long ulonglong;
typedef long long longlong; typedef unsigned char uchar; typedef int int3; typedef void code;
typedef unsigned char bool; typedef unsigned short word; typedef unsigned int dword;
#define __watcall  /* Watcom register calling convention: eax, edx, ebx, ecx, stack */
#define __regsafe  /* stack arguments, all registers preserved */
