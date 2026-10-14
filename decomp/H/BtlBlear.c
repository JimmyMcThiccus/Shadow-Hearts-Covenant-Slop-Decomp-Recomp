/* decomp/H/BtlBlear.c — cleaned Ghidra output (SH2JP_BATTLE.BIN, JP Furokuban, base 0x00430a00).
 * 9 function(s). Types: see types.h. Names/gp globals resolved from symbols/SLPM_602.19.syms. */
#include "types.h"

/* ---------------------------------------------------------------------------
 * JP: 0x0051f2e0  __ct__8BtlBlearFiifff
 * C++: BtlBlear::__ct(int, int, float, float, float)
 * size: 0x118 bytes
 * --------------------------------------------------------------------------- */
int __ct__8BtlBlearFiifff
              (undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4,
              undefined4 param_5,undefined4 param_6)

{
  __ct__6BtlEffFii(param_4,param_5,param_6);
  *(undefined4 *)(param_4 + 0x14) = 0x409ed0;
  *(undefined4 *)(param_4 + 0x28) = 0x409ee0;
  *(undefined4 *)(param_4 + 0x34) = 0x409ef0;
  *(undefined4 *)(param_4 + 0x40) = 0;
  *(undefined4 *)(param_4 + 0x44) = param_5;
  *(undefined4 *)(param_4 + 0x48) = param_6;
  *(undefined4 *)(param_4 + 0x4c) = 0x13;
  *(undefined4 *)(param_4 + 0x60) = param_1;
  *(undefined4 *)(param_4 + 0x5c) = param_1;
  *(undefined4 *)(param_4 + 0x68) = param_2;
  *(undefined4 *)(param_4 + 100) = param_2;
  *(undefined4 *)(param_4 + 0x6c) = param_3;
  *(undefined4 *)(param_4 + 0x1c) = 0;
  *(undefined4 *)(param_4 + 0x18) = 0;
  Entry__7CPollerFP7CPolObjib(iGpffff858c + 0x48,param_4,0x80,0);
  BtlEffEntry__7CBattleFiP6BtlEff(uGpffff86b4,0xffffffffffffffff,param_4);
  return param_4;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0051f400  __dt__8BtlBlearFv
 * C++: BtlBlear::__dt()
 * size: 0x154 bytes
 * --------------------------------------------------------------------------- */
int __dt__8BtlBlearFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x14) = 0x409ed0;
    *(undefined4 *)(param_1 + 0x28) = 0x409ee0;
    *(undefined4 *)(param_1 + 0x34) = 0x409ef0;
    if (*(int *)(param_1 + 0x18) != 0) {
      __dla__FPv(*(undefined4 *)(param_1 + 0x18));
    }
    if (*(int *)(param_1 + 0x1c) != 0) {
      __dla__FPv(*(undefined4 *)(param_1 + 0x1c));
    }
    if (param_1 != 0) {
      *(undefined4 *)(param_1 + 0x14) = 0x40a520;
      *(undefined4 *)(param_1 + 0x28) = 0x40a530;
      *(undefined4 *)(param_1 + 0x34) = 0x40a540;
      if (param_1 != -0x2c) {
        *(undefined4 *)(param_1 + 0x34) = 0x4049f0;
      }
      __dt__8VIF1PrimFv(param_1 + 0x18,0);
      __dt__7CPolObjFv(param_1,0);
    }
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0051f560  Destruct__8BtlBlearFv
 * C++: BtlBlear::Destruct()
 * size: 0x5c bytes
 * --------------------------------------------------------------------------- */
void Destruct__8BtlBlearFv(int param_1)

{
  BtlEffRelease__7CBattleFiP6BtlEff(uGpffff86b4,0xffffffffffffffff,param_1);
  Dispose__7CPollerFP7CPolObj(iGpffff858c + 0x48,param_1);
  (**(code **)(*(int *)(param_1 + 0x34) + 0xc))();
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0051f5c0  Polling__8BtlBlearFv
 * C++: BtlBlear::Polling()
 * size: 0xf0 bytes
 * --------------------------------------------------------------------------- */
undefined4 Polling__8BtlBlearFv(int param_1)

{
  if ((*(byte *)(iGpffff86b4 + 0x24) & 1) == 0) {
    *(float *)(param_1 + 0x60) = *(float *)(param_1 + 0x60) - *(float *)(iGpffff86b4 + 0x38);
    *(float *)(param_1 + 0x68) =
         ((*(float *)(param_1 + 100) - 1.0) * *(float *)(param_1 + 0x60)) /
         *(float *)(param_1 + 0x5c) + 1.0;
    if (*(float *)(param_1 + 0x60) <= 0.0) {
      BtlEffRelease__7CBattleFiP6BtlEff(iGpffff86b4,0xffffffffffffffff,param_1);
      (**(code **)(*(int *)(param_1 + 0x34) + 0xc))();
      return 1;
    }
  }
  return 0;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0051f6b0  MakePacket__8BtlBlearFv
 * C++: BtlBlear::MakePacket()
 * size: 0x4d8 bytes
 * --------------------------------------------------------------------------- */
/* WARNING: Removing unreachable block (ram,0x0051f84c) */

void MakePacket__8BtlBlearFv(int param_1)

{
  bool bVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 uVar4;
  long lVar5;
  ulong uVar6;
  uint uVar7;
  float fVar8;
  float fStack_14;
  
  bVar1 = (*(byte *)(param_1 + 0x40) & 1) == 0;
  uVar7 = (uint)bVar1;
  if (*(int *)(param_1 + uVar7 * 4 + 0x18) == 0) {
    uVar4 = __nwa__FUi(0xc0);
    *(undefined4 *)(param_1 + uVar7 * 4 + 0x18) = uVar4;
    puVar2 = *(undefined4 **)(param_1 + uVar7 * 4 + 0x18);
    *puVar2 = 0x1000000a;
    puVar2[1] = 0;
    puVar2[2] = 0;
    puVar2[3] = 0x5000000a;
    *(undefined8 *)(puVar2 + 4) = 0x5000000000000001;
    *(undefined8 *)(puVar2 + 6) = 0x6ee8e;
    *(undefined8 *)(puVar2 + 8) = 0x60;
    *(undefined8 *)(puVar2 + 10) = 0x14;
    *(undefined8 *)(puVar2 + 0xc) = 5;
    *(undefined8 *)(puVar2 + 0xe) = 0;
    *(undefined8 *)(puVar2 + 0x10) = 0x3001;
    *(undefined8 *)(puVar2 + 0x12) = 0x47;
    *(undefined8 *)(puVar2 + 0x14) = 0x44;
    *(undefined8 *)(puVar2 + 0x16) = 0x42;
    *(ulong *)(puVar2 + 0x18) = **(ulong **)(iGpffff8598 + 0x340) & 0x7ffffffff;
    *(undefined8 *)(puVar2 + 0x1a) = 0;
    *(undefined8 *)(puVar2 + 0x1c) = 0x6400000000008001;
    *(undefined8 *)(puVar2 + 0x1e) = 0x43c310;
    *(undefined8 *)(puVar2 + 0x20) = 0x156;
  }
  iVar3 = *(int *)(param_1 + uVar7 * 4 + 0x18);
  fStack_14 = (float)*(ushort *)(iGpffff8598 + 0x34a);
  if (((*(byte *)(iGpffff8598 + 0x390) & 1) != 0) && (*(char *)(iGpffff8598 + 0x394) == '\0')) {
    fStack_14 = 0.0;
  }
  if (*(float *)(param_1 + 0x5c) / 2.0 <= *(float *)(param_1 + 0x60)) {
    fVar8 = *(float *)(param_1 + 0x6c) * 128.0;
    if (2.1474836e+09 <= fVar8) {
      fVar8 = fVar8 - 2.1474836e+09;
    }
  }
  else {
    fVar8 = (*(float *)(param_1 + 0x6c) * 128.0 * *(float *)(param_1 + 0x60)) /
            (*(float *)(param_1 + 0x5c) / 2.0);
    if (2.1474836e+09 <= fVar8) {
      fVar8 = fVar8 - 2.1474836e+09;
    }
  }
  *(ulong *)(iVar3 + 0x88) = ((long)(int)fVar8 & 0xffU) << 0x18 | 0x100808080;
  lVar5 = __fixunssfdi(fStack_14 * 16.0);
  *(long *)(iVar3 + 0x90) = lVar5 << 0x10;
  uVar6 = __fixunssfdi((2048.0 - *(float *)(param_1 + 0x68) * 256.0) * 16.0);
  lVar5 = __fixunssfdi((2048.0 - *(float *)(param_1 + 0x68) * 224.0) * 16.0);
  *(ulong *)(iVar3 + 0x98) = uVar6 | lVar5 << 0x10;
  lVar5 = __fixunssfdi((fStack_14 + 448.0) * 16.0);
  *(ulong *)(iVar3 + 0xa0) = lVar5 << 0x10 | 0x2000;
  uVar6 = __fixunssfdi((*(float *)(param_1 + 0x68) * 256.0 + 2048.0) * 16.0);
  lVar5 = __fixunssfdi((*(float *)(param_1 + 0x68) * 224.0 + 2048.0) * 16.0);
  *(ulong *)(iVar3 + 0xa8) = uVar6 | lVar5 << 0x10;
  *(int *)(param_1 + 0x54) = iVar3 + 0xb0;
  *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfe | bVar1;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0051fb90  Reset__8BtlBlearFfff
 * C++: BtlBlear::Reset(float, float, float)
 * size: 0x54 bytes
 * --------------------------------------------------------------------------- */
void Reset__8BtlBlearFfff(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  *(undefined4 *)(param_4 + 0x60) = param_1;
  *(undefined4 *)(param_4 + 0x5c) = param_1;
  *(undefined4 *)(param_4 + 0x68) = param_2;
  *(undefined4 *)(param_4 + 100) = param_2;
  *(undefined4 *)(param_4 + 0x6c) = param_3;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054aeb0  EndSet__8BtlBlearFv
 * C++: BtlBlear::EndSet()
 * size: 0x30 bytes
 * --------------------------------------------------------------------------- */
void EndSet__8BtlBlearFv(int param_1)

{
  (**(code **)(*(int *)(param_1 + 0x14) + 0x30))();
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b740  @24@__dt__8BtlBlearFv
 * C++: @24@__dt__8BtlBlearFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int * _24___dt__8BtlBlearFv(int *param_1,short param_2)

{
  int *piVar1;
  
  piVar1 = param_1 + -6;
  if (piVar1 != (int *)0x0) {
    param_1[-1] = 0x409ed0;
    param_1[4] = 0x409ee0;
    param_1[7] = 0x409ef0;
    if (*param_1 != 0) {
      __dla__FPv(*param_1);
    }
    if (param_1[1] != 0) {
      __dla__FPv(param_1[1]);
    }
    if (piVar1 != (int *)0x0) {
      param_1[-1] = 0x40a520;
      param_1[4] = 0x40a530;
      param_1[7] = 0x40a540;
      if (piVar1 != (int *)0xffffffd4) {
        param_1[7] = 0x4049f0;
      }
      __dt__8VIF1PrimFv(param_1,0);
      __dt__7CPolObjFv(piVar1,0);
    }
    if (0 < param_2) {
      __dl__FPv(piVar1);
    }
  }
  return piVar1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b750  @44@__dt__8BtlBlearFv
 * C++: @44@__dt__8BtlBlearFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int _44___dt__8BtlBlearFv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x2c;
  if (iVar1 != 0) {
    *(undefined4 *)(param_1 + -0x18) = 0x409ed0;
    *(undefined4 *)(param_1 + -4) = 0x409ee0;
    *(undefined4 *)(param_1 + 8) = 0x409ef0;
    if (*(int *)(param_1 + -0x14) != 0) {
      __dla__FPv(*(undefined4 *)(param_1 + -0x14));
    }
    if (*(int *)(param_1 + -0x10) != 0) {
      __dla__FPv(*(undefined4 *)(param_1 + -0x10));
    }
    if (iVar1 != 0) {
      *(undefined4 *)(param_1 + -0x18) = 0x40a520;
      *(undefined4 *)(param_1 + -4) = 0x40a530;
      *(undefined4 *)(param_1 + 8) = 0x40a540;
      if (iVar1 != -0x2c) {
        *(undefined4 *)(param_1 + 8) = 0x4049f0;
      }
      __dt__8VIF1PrimFv(param_1 + -0x14,0);
      __dt__7CPolObjFv(iVar1,0);
    }
    if (0 < param_2) {
      __dl__FPv(iVar1);
    }
  }
  return iVar1;
}

