/* decomp/H/Bullet3.c — cleaned Ghidra output (SH2JP_BATTLE.BIN, JP Furokuban, base 0x00430a00).
 * 8 function(s). Types: see types.h. Names/gp globals resolved from symbols/SLPM_602.19.syms. */
#include "types.h"

/* ---------------------------------------------------------------------------
 * JP: 0x00540f20  __ct__7Bullet3FiiissfiiiiUsUsii
 * C++: Bullet3::__ct(int, int, int, short, short, float, int, int, int, int, ushort, ushort, int, int)
 * size: 0x1a0 bytes
 * --------------------------------------------------------------------------- */
int __ct__7Bullet3FiiissfiiiiUsUsii
              (undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4,
              undefined4 param_5,undefined2 param_6,undefined2 param_7,undefined4 param_8,
              undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined2 param_12,
              undefined2 param_13,undefined4 param_14,undefined4 param_15)

{
  __ct__6BtlEffFii(param_2,param_3,param_4);
  *(undefined4 *)(param_2 + 0x14) = 0x409a20;
  *(undefined4 *)(param_2 + 0x28) = 0x409a30;
  *(undefined4 *)(param_2 + 0x34) = 0x409a40;
  *(undefined4 *)(param_2 + 0x40) = 0;
  *(undefined4 *)(param_2 + 0x44) = param_3;
  *(undefined4 *)(param_2 + 0x48) = param_4;
  *(undefined4 *)(param_2 + 0x4c) = 0x18;
  *(undefined4 *)(param_2 + 0x5c) = param_5;
  *(undefined2 *)(param_2 + 0x60) = param_6;
  *(undefined2 *)(param_2 + 0x62) = param_7;
  *(undefined4 *)(param_2 + 100) = param_1;
  *(undefined4 *)(param_2 + 0x68) = param_9;
  *(undefined4 *)(param_2 + 0x6c) = param_10;
  *(undefined4 *)(param_2 + 0x70) = param_8;
  *(undefined4 *)(param_2 + 0x74) = param_11;
  *(undefined2 *)(param_2 + 0x78) = param_12;
  *(undefined2 *)(param_2 + 0x7a) = param_13;
  *(undefined4 *)(param_2 + 0x7c) = param_14;
  *(undefined4 *)(param_2 + 0x80) = param_15;
  *(undefined4 *)(param_2 + 0x1c) = 0;
  *(undefined4 *)(param_2 + 0x18) = 0;
  *(undefined4 *)(param_2 + 0x84) = 0;
  *(undefined4 *)(param_2 + 0x88) = 0;
  *(undefined4 *)(param_2 + 0x8c) = 0;
  Entry__7CPollerFP7CPolObjib(iGpffff858c + 0x48,param_2,0x80,0);
  BtlEffEntry__7CBattleFiP6BtlEff(uGpffff86b4,*(undefined4 *)(param_2 + 0x48),param_2);
  return param_2;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005410c0  __dt__7Bullet3Fv
 * C++: Bullet3::__dt()
 * size: 0x10c bytes
 * --------------------------------------------------------------------------- */
int __dt__7Bullet3Fv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x14) = 0x409a20;
    *(undefined4 *)(param_1 + 0x28) = 0x409a30;
    *(undefined4 *)(param_1 + 0x34) = 0x409a40;
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
 * JP: 0x005411d0  Destruct__7Bullet3Fv
 * C++: Bullet3::Destruct()
 * size: 0x60 bytes
 * --------------------------------------------------------------------------- */
void Destruct__7Bullet3Fv(int param_1)

{
  BtlEffRelease__7CBattleFiP6BtlEff(uGpffff86b4,*(undefined4 *)(param_1 + 0x48),param_1);
  Dispose__7CPollerFP7CPolObj(iGpffff858c + 0x48,param_1);
  (**(code **)(*(int *)(param_1 + 0x34) + 0xc))();
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00541230  Polling__7Bullet3Fv
 * C++: Bullet3::Polling()
 * size: 0x1d4 bytes
 * --------------------------------------------------------------------------- */
undefined4 Polling__7Bullet3Fv(int param_1)

{
  undefined4 uVar1;
  long lVar2;
  float fStack_14;
  
  fStack_14 = *(float *)(iGpffff86b4 + 0x38);
  if ((*(byte *)(iGpffff86b4 + 0x24) & 1) != 0) {
    fStack_14 = 0.0;
  }
  *(float *)(param_1 + 0x88) = *(float *)(param_1 + 0x88) + fStack_14;
  if (((*(float *)(param_1 + 0x88) < 0.5) && (fStack_14 != 0.0)) &&
     (lVar2 = __nw__FUi(0xd0), lVar2 != 0)) {
    __ct__12Bullet3ChildFiiP7Bullet3issfiiiiUsUsii
              (*(undefined4 *)(param_1 + 100),lVar2,*(undefined4 *)(param_1 + 0x44),
               *(undefined4 *)(param_1 + 0x48),param_1,*(undefined4 *)(param_1 + 0x5c),
               *(undefined2 *)(param_1 + 0x60),*(undefined2 *)(param_1 + 0x62),
               *(undefined4 *)(param_1 + 0x70));
  }
  if ((*(float *)(param_1 + 0x88) < 0.5) || (*(int *)(param_1 + 0x8c) != 0)) {
    uVar1 = 0;
  }
  else {
    BtlEffRelease__7CBattleFiP6BtlEff(iGpffff86b4,*(undefined4 *)(param_1 + 0x48),param_1);
    (**(code **)(*(int *)(param_1 + 0x34) + 0xc))();
    uVar1 = 1;
  }
  return uVar1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054ada0  MakePacket__7Bullet3Fv
 * C++: Bullet3::MakePacket()
 * size: 0x10 bytes
 * --------------------------------------------------------------------------- */
void MakePacket__7Bullet3Fv(void)

{
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054adb0  EndSet__7Bullet3Fv
 * C++: Bullet3::EndSet()
 * size: 0x10 bytes
 * --------------------------------------------------------------------------- */
void EndSet__7Bullet3Fv(void)

{
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b930  @24@__dt__7Bullet3Fv
 * C++: @24@__dt__7Bullet3Fv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int _24___dt__7Bullet3Fv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x18;
  if (iVar1 != 0) {
    *(undefined4 *)(param_1 + -4) = 0x409a20;
    *(undefined4 *)(param_1 + 0x10) = 0x409a30;
    *(undefined4 *)(param_1 + 0x1c) = 0x409a40;
    if (iVar1 != 0) {
      *(undefined4 *)(param_1 + -4) = 0x40a520;
      *(undefined4 *)(param_1 + 0x10) = 0x40a530;
      *(undefined4 *)(param_1 + 0x1c) = 0x40a540;
      if (iVar1 != -0x2c) {
        *(undefined4 *)(param_1 + 0x1c) = 0x4049f0;
      }
      __dt__8VIF1PrimFv(param_1,0);
      __dt__7CPolObjFv(iVar1,0);
    }
    if (0 < param_2) {
      __dl__FPv(iVar1);
    }
  }
  return iVar1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b940  @44@__dt__7Bullet3Fv
 * C++: @44@__dt__7Bullet3Fv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int _44___dt__7Bullet3Fv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x2c;
  if (iVar1 != 0) {
    *(undefined4 *)(param_1 + -0x18) = 0x409a20;
    *(undefined4 *)(param_1 + -4) = 0x409a30;
    *(undefined4 *)(param_1 + 8) = 0x409a40;
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

