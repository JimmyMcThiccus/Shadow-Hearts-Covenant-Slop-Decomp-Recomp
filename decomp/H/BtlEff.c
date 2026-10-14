/* decomp/H/BtlEff.c — cleaned Ghidra output (SH2JP_BATTLE.BIN, JP Furokuban, base 0x00430a00).
 * 7 function(s). Types: see types.h. Names/gp globals resolved from symbols/SLPM_602.19.syms. */
#include "types.h"

/* ---------------------------------------------------------------------------
 * JP: 0x00480e90  ForceEndSet__6BtlEffFv
 * C++: BtlEff::ForceEndSet()
 * size: 0x30 bytes
 * --------------------------------------------------------------------------- */
void ForceEndSet__6BtlEffFv(int param_1)

{
  (**(code **)(*(int *)(param_1 + 0x14) + 0x3c))();
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x004f57d0  getPacket__6BtlEffFv
 * C++: BtlEff::getPacket()
 * size: 0x4c bytes
 * --------------------------------------------------------------------------- */
undefined4 getPacket__6BtlEffFv(int param_1)

{
  (**(code **)(*(int *)(param_1 + 0x14) + 0x38))();
  return *(undefined4 *)(param_1 + (*(byte *)(param_1 + 0x40) & 1) * 4 + 0x18);
}

/* ---------------------------------------------------------------------------
 * JP: 0x004f5df0  __ct__6BtlEffFii
 * C++: BtlEff::__ct(int, int)
 * size: 0xcc bytes
 * --------------------------------------------------------------------------- */
int __ct__6BtlEffFii(int param_1,undefined4 param_2,undefined4 param_3)

{
  __ct__7CPolObjFv(param_1);
  __ct__8VIF1PrimFv(param_1 + 0x18);
  *(undefined4 *)(param_1 + 0x2c) = 0;
  *(undefined4 *)(param_1 + 0x30) = 0;
  *(undefined4 *)(param_1 + 0x34) = 0x4049f0;
  *(undefined4 *)(param_1 + 0x14) = 0x40a520;
  *(undefined4 *)(param_1 + 0x28) = 0x40a530;
  *(undefined4 *)(param_1 + 0x34) = 0x40a540;
  *(undefined4 *)(param_1 + 0x38) = 0;
  *(undefined4 *)(param_1 + 0x3c) = 0;
  *(undefined4 *)(param_1 + 0x44) = param_2;
  *(undefined4 *)(param_1 + 0x48) = param_3;
  *(undefined4 *)(param_1 + 0x58) = 0xffffffff;
  return param_1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x004f6040  __dt__6BtlEffFv
 * C++: BtlEff::__dt()
 * size: 0xd4 bytes
 * --------------------------------------------------------------------------- */
int __dt__6BtlEffFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x14) = 0x40a520;
    *(undefined4 *)(param_1 + 0x28) = 0x40a530;
    *(undefined4 *)(param_1 + 0x34) = 0x40a540;
    if (param_1 != -0x2c) {
      *(undefined4 *)(param_1 + 0x34) = 0x4049f0;
    }
    __dt__8VIF1PrimFv(param_1 + 0x18,0);
    __dt__7CPolObjFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b440  @24@__dt__6BtlEffFv
 * C++: @24@__dt__6BtlEffFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int _24___dt__6BtlEffFv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x18;
  if (iVar1 != 0) {
    *(undefined4 *)(param_1 + -4) = 0x40a520;
    *(undefined4 *)(param_1 + 0x10) = 0x40a530;
    *(undefined4 *)(param_1 + 0x1c) = 0x40a540;
    if (iVar1 != -0x2c) {
      *(undefined4 *)(param_1 + 0x1c) = 0x4049f0;
    }
    __dt__8VIF1PrimFv(param_1,0);
    __dt__7CPolObjFv(iVar1,0);
    if (0 < param_2) {
      __dl__FPv(iVar1);
    }
  }
  return iVar1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b450  @44@__dt__6BtlEffFv
 * C++: @44@__dt__6BtlEffFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int _44___dt__6BtlEffFv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x2c;
  if (iVar1 != 0) {
    *(undefined4 *)(param_1 + -0x18) = 0x40a520;
    *(undefined4 *)(param_1 + -4) = 0x40a530;
    *(undefined4 *)(param_1 + 8) = 0x40a540;
    if (iVar1 != -0x2c) {
      *(undefined4 *)(param_1 + 8) = 0x4049f0;
    }
    __dt__8VIF1PrimFv(param_1 + -0x14,0);
    __dt__7CPolObjFv(iVar1,0);
    if (0 < param_2) {
      __dl__FPv(iVar1);
    }
  }
  return iVar1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b990  @24@getPacket__6BtlEffFv
 * C++: @24@getPacket__6BtlEffFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
undefined4 _24_getPacket__6BtlEffFv(int param_1)

{
  (**(code **)(*(int *)(param_1 + -4) + 0x38))();
  return *(undefined4 *)(param_1 + (*(byte *)(param_1 + 0x28) & 1) * 4);
}

