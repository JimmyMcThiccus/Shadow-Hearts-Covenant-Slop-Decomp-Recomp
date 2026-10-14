/* decomp/H/BtlScrnCapture.c — cleaned Ghidra output (SH2JP_BATTLE.BIN, JP Furokuban, base 0x00430a00).
 * 7 function(s). Types: see types.h. Names/gp globals resolved from symbols/SLPM_602.19.syms. */
#include "types.h"

/* ---------------------------------------------------------------------------
 * JP: 0x00587380  __ct__14BtlScrnCaptureFv
 * C++: BtlScrnCapture::__ct()
 * size: 0x5c bytes
 * --------------------------------------------------------------------------- */
int __ct__14BtlScrnCaptureFv(int param_1)

{
  __ct__14LayeredTextureFv(param_1);
  *(undefined4 *)(param_1 + 0xa0) = 0x40a770;
  *(undefined4 *)(param_1 + 0x90) = 0x40a778;
  *(undefined4 *)(param_1 + 0x9c) = 0x40a788;
  return param_1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005873e0  __dt__14BtlScrnCaptureFv
 * C++: BtlScrnCapture::__dt()
 * size: 0xe4 bytes
 * --------------------------------------------------------------------------- */
int __dt__14BtlScrnCaptureFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0xa0) = 0x40a770;
    *(undefined4 *)(param_1 + 0x90) = 0x40a778;
    *(undefined4 *)(param_1 + 0x9c) = 0x40a788;
    if (*(int *)(param_1 + 0xa4) != 0) {
      __dla__FPv(*(undefined4 *)(param_1 + 0xa4));
      *(undefined4 *)(param_1 + 0xa4) = 0;
    }
    if (*(int *)(param_1 + 0xa8) != 0) {
      __dla__FPv(*(undefined4 *)(param_1 + 0xa8));
      *(undefined4 *)(param_1 + 0xa8) = 0;
    }
    __dt__14LayeredTextureFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005874d0  Init__14BtlScrnCaptureFii
 * C++: BtlScrnCapture::Init(int, int)
 * size: 0x88 bytes
 * --------------------------------------------------------------------------- */
void Init__14BtlScrnCaptureFii(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  
  *(undefined4 *)(param_1 + 0x68) = param_2;
  *(undefined4 *)(param_1 + 0x6c) = param_3;
  *(undefined4 *)(param_1 + 0x70) = 1;
  *(undefined4 *)(param_1 + 0xb0) = 0x3f800000;
  uVar1 = __nwa__FUi(0x100);
  *(undefined4 *)(param_1 + 0xa4) = uVar1;
  uVar1 = __nwa__FUi(0x100);
  *(undefined4 *)(param_1 + 0xa8) = uVar1;
  *(undefined4 *)(param_1 + 0xac) = 0;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00587560  getPacket__14BtlScrnCaptureFv
 * C++: BtlScrnCapture::getPacket()
 * size: 0x2a0 bytes
 * --------------------------------------------------------------------------- */
undefined4 getPacket__14BtlScrnCaptureFv(int param_1)

{
  undefined4 *puVar1;
  undefined8 uVar2;
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  
  puVar1 = *(undefined4 **)(param_1 + (bGpffff8340 & 1) * 4 + 0xa4);
  puVar6 = *(undefined4 **)(param_1 + (bGpffff8340 & 1) * 4 + 0xa4);
  for (iVar3 = 0; iVar3 < 0x10; iVar3 = iVar3 + 1) {
    *puVar6 = in_zero_lo;
    puVar6[1] = in_zero_hi;
    puVar6[2] = in_zero_udw;
    puVar6[3] = in_register_0000000c;
    puVar6 = puVar6 + 4;
  }
  *puVar1 = 0x50000000;
  puVar1[1] = *(undefined4 *)(param_1 + 0x18);
  puVar1[2] = 0x11000000;
  puVar1[4] = 0x10000007;
  puVar1[7] = 0x50000007;
  *(undefined8 *)(puVar1 + 8) = 0x1000000000008006;
  *(undefined8 *)(puVar1 + 10) = 0xe;
  *(undefined8 *)(puVar1 + 0xe) = 0x3b;
  *(undefined8 *)(puVar1 + 0xc) = 0x8000000080;
  *(undefined8 *)(puVar1 + 0x12) = 0x48;
  *(undefined8 *)(puVar1 + 0x10) = 0;
  iVar3 = getTex0GsPacket__7TextureFiiii(param_1,0,
                          (uint)*(ushort *)
                                 (iGpffff8598 + (*(byte *)(iGpffff8598 + 0x394) ^ 1) * 2 + 0x38c) <<
                          5,0xffffffffffffffff,0xffffffffffffffff);
  uVar2 = *(undefined8 *)(iVar3 + 0x20);
  uVar4 = *(undefined4 *)(iVar3 + 0x28);
  uVar5 = *(undefined4 *)(iVar3 + 0x2c);
  puVar1[0x14] = (int)uVar2;
  puVar1[0x15] = (int)((ulong)uVar2 >> 0x20);
  puVar1[0x16] = uVar4;
  puVar1[0x17] = uVar5;
  *(undefined8 *)(puVar1 + 0x1a) = 0;
  *(undefined8 *)(puVar1 + 0x18) = 0x316;
  *(undefined8 *)(puVar1 + 0x1e) = 0x4d;
  *(undefined8 *)(puVar1 + 0x1c) = 0x80150;
  *(undefined8 *)(puVar1 + 0x22) = 9;
  *(undefined8 *)(puVar1 + 0x20) = 5;
  puVar1[0x24] = 0x10000004;
  puVar1[0x27] = 0x50000004;
  *(undefined8 *)(puVar1 + 0x28) = 0x3400000000008002;
  *(undefined8 *)(puVar1 + 0x2a) = 0x513;
  *(undefined8 *)(puVar1 + 0x2c) = 0x80008;
  *(undefined8 *)(puVar1 + 0x2e) = 0x3f80000080808080;
  *(undefined8 *)(puVar1 + 0x30) = 0xffe3d072007000;
  *(undefined8 *)(puVar1 + 0x32) = 0x1c002000;
  *(undefined8 *)(puVar1 + 0x34) = 0x3f80000080808080;
  *(undefined8 *)(puVar1 + 0x36) = 0xffe3d08e009000;
  *(undefined4 **)(param_1 + 0xac) = puVar1 + 0x38;
  return *(undefined4 *)(param_1 + (bGpffff8340 & 1) * 4 + 0xa4);
}

/* ---------------------------------------------------------------------------
 * JP: 0x0058bb10  @128@getPacket__14BtlScrnCaptureFv
 * C++: @128@getPacket__14BtlScrnCaptureFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
undefined4 _128_getPacket__14BtlScrnCaptureFv(int param_1)

{
  undefined4 *puVar1;
  undefined8 uVar2;
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  undefined4 *puVar7;
  
  iVar6 = param_1 + -0x80;
  puVar1 = *(undefined4 **)(iVar6 + (bGpffff8340 & 1) * 4 + 0xa4);
  puVar7 = *(undefined4 **)(iVar6 + (bGpffff8340 & 1) * 4 + 0xa4);
  for (iVar3 = 0; iVar3 < 0x10; iVar3 = iVar3 + 1) {
    *puVar7 = in_zero_lo;
    puVar7[1] = in_zero_hi;
    puVar7[2] = in_zero_udw;
    puVar7[3] = in_register_0000000c;
    puVar7 = puVar7 + 4;
  }
  *puVar1 = 0x50000000;
  puVar1[1] = *(undefined4 *)(param_1 + -0x68);
  puVar1[2] = 0x11000000;
  puVar1[4] = 0x10000007;
  puVar1[7] = 0x50000007;
  *(undefined8 *)(puVar1 + 8) = 0x1000000000008006;
  *(undefined8 *)(puVar1 + 10) = 0xe;
  *(undefined8 *)(puVar1 + 0xe) = 0x3b;
  *(undefined8 *)(puVar1 + 0xc) = 0x8000000080;
  *(undefined8 *)(puVar1 + 0x12) = 0x48;
  *(undefined8 *)(puVar1 + 0x10) = 0;
  iVar3 = getTex0GsPacket__7TextureFiiii(iVar6,0,(uint)*(ushort *)
                                         (iGpffff8598 + (*(byte *)(iGpffff8598 + 0x394) ^ 1) * 2 +
                                         0x38c) << 5,0xffffffffffffffff,0xffffffffffffffff);
  uVar2 = *(undefined8 *)(iVar3 + 0x20);
  uVar4 = *(undefined4 *)(iVar3 + 0x28);
  uVar5 = *(undefined4 *)(iVar3 + 0x2c);
  puVar1[0x14] = (int)uVar2;
  puVar1[0x15] = (int)((ulong)uVar2 >> 0x20);
  puVar1[0x16] = uVar4;
  puVar1[0x17] = uVar5;
  *(undefined8 *)(puVar1 + 0x1a) = 0;
  *(undefined8 *)(puVar1 + 0x18) = 0x316;
  *(undefined8 *)(puVar1 + 0x1e) = 0x4d;
  *(undefined8 *)(puVar1 + 0x1c) = 0x80150;
  *(undefined8 *)(puVar1 + 0x22) = 9;
  *(undefined8 *)(puVar1 + 0x20) = 5;
  puVar1[0x24] = 0x10000004;
  puVar1[0x27] = 0x50000004;
  *(undefined8 *)(puVar1 + 0x28) = 0x3400000000008002;
  *(undefined8 *)(puVar1 + 0x2a) = 0x513;
  *(undefined8 *)(puVar1 + 0x2c) = 0x80008;
  *(undefined8 *)(puVar1 + 0x2e) = 0x3f80000080808080;
  *(undefined8 *)(puVar1 + 0x30) = 0xffe3d072007000;
  *(undefined8 *)(puVar1 + 0x32) = 0x1c002000;
  *(undefined8 *)(puVar1 + 0x34) = 0x3f80000080808080;
  *(undefined8 *)(puVar1 + 0x36) = 0xffe3d08e009000;
  *(undefined4 **)(param_1 + 0x2c) = puVar1 + 0x38;
  return *(undefined4 *)(iVar6 + (bGpffff8340 & 1) * 4 + 0xa4);
}

/* ---------------------------------------------------------------------------
 * JP: 0x0058bb20  @128@__dt__14BtlScrnCaptureFv
 * C++: @128@__dt__14BtlScrnCaptureFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int _128___dt__14BtlScrnCaptureFv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x80;
  if (iVar1 != 0) {
    *(undefined4 *)(param_1 + 0x20) = 0x40a770;
    *(undefined4 *)(param_1 + 0x10) = 0x40a778;
    *(undefined4 *)(param_1 + 0x1c) = 0x40a788;
    if (*(int *)(param_1 + 0x24) != 0) {
      __dla__FPv(*(undefined4 *)(param_1 + 0x24));
      *(undefined4 *)(param_1 + 0x24) = 0;
    }
    if (*(int *)(param_1 + 0x28) != 0) {
      __dla__FPv(*(undefined4 *)(param_1 + 0x28));
      *(undefined4 *)(param_1 + 0x28) = 0;
    }
    __dt__14LayeredTextureFv(iVar1,0);
    if (0 < param_2) {
      __dl__FPv(iVar1);
    }
  }
  return iVar1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0058bb30  @148@__dt__14BtlScrnCaptureFv
 * C++: @148@__dt__14BtlScrnCaptureFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int _148___dt__14BtlScrnCaptureFv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x94;
  if (iVar1 != 0) {
    *(undefined4 *)(param_1 + 0xc) = 0x40a770;
    *(undefined4 *)(param_1 + -4) = 0x40a778;
    *(undefined4 *)(param_1 + 8) = 0x40a788;
    if (*(int *)(param_1 + 0x10) != 0) {
      __dla__FPv(*(undefined4 *)(param_1 + 0x10));
      *(undefined4 *)(param_1 + 0x10) = 0;
    }
    if (*(int *)(param_1 + 0x14) != 0) {
      __dla__FPv(*(undefined4 *)(param_1 + 0x14));
      *(undefined4 *)(param_1 + 0x14) = 0;
    }
    __dt__14LayeredTextureFv(iVar1,0);
    if (0 < param_2) {
      __dl__FPv(iVar1);
    }
  }
  return iVar1;
}

