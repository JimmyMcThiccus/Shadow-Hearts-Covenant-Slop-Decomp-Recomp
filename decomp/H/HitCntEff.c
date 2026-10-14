/* decomp/H/HitCntEff.c — cleaned Ghidra output (SH2JP_BATTLE.BIN, JP Furokuban, base 0x00430a00).
 * 9 function(s). Types: see types.h. Names/gp globals resolved from symbols/SLPM_602.19.syms. */
#include "types.h"

/* ---------------------------------------------------------------------------
 * JP: 0x004fb030  __ct__9HitCntEffFiii
 * C++: HitCntEff::__ct(int, int, int)
 * size: 0x174 bytes
 * --------------------------------------------------------------------------- */
int __ct__9HitCntEffFiii(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  __ct__6BtlEffFii(param_1,param_2,param_3);
  *(undefined4 *)(param_1 + 0x14) = 0x40a480;
  *(undefined4 *)(param_1 + 0x28) = 0x40a490;
  *(undefined4 *)(param_1 + 0x34) = 0x40a4a0;
  *(undefined4 *)(param_1 + 0x44) = param_2;
  *(undefined4 *)(param_1 + 0x48) = param_3;
  *(undefined4 *)(param_1 + 0x4c) = 0xf;
  *(undefined4 *)(param_1 + 0x40) = 0;
  *(undefined4 *)(param_1 + 0x5c) = 0x3e4ccccd;
  *(undefined4 *)(param_1 + 100) = param_4;
  *(float *)(param_1 + 0x60) = (float)*(int *)(param_1 + 100) / 25.0 + 2.0;
  if (4.0 <= *(float *)(param_1 + 0x60)) {
    *(undefined4 *)(param_1 + 0x60) = 0x40800000;
  }
  *(undefined4 *)(param_1 + 0x1c) = 0;
  *(undefined4 *)(param_1 + 0x18) = 0;
  *(undefined4 *)(param_1 + 0x54) = 0;
  Entry__7CPollerFP7CPolObjib(iGpffff858c + 0x48,param_1,0x80,0);
  BtlEffEntry__7CBattleFiP6BtlEff(uGpffff86b4,0xffffffffffffffff,param_1);
  return param_1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x004fb1b0  __dt__9HitCntEffFv
 * C++: HitCntEff::__dt()
 * size: 0x154 bytes
 * --------------------------------------------------------------------------- */
int __dt__9HitCntEffFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x14) = 0x40a480;
    *(undefined4 *)(param_1 + 0x28) = 0x40a490;
    *(undefined4 *)(param_1 + 0x34) = 0x40a4a0;
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
 * JP: 0x004fb310  Destruct__9HitCntEffFv
 * C++: HitCntEff::Destruct()
 * size: 0x5c bytes
 * --------------------------------------------------------------------------- */
void Destruct__9HitCntEffFv(int param_1)

{
  BtlEffRelease__7CBattleFiP6BtlEff(uGpffff86b4,0xffffffffffffffff,param_1);
  Dispose__7CPollerFP7CPolObj(iGpffff858c + 0x48,param_1);
  (**(code **)(*(int *)(param_1 + 0x34) + 0xc))();
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x004fb370  Polling__9HitCntEffFv
 * C++: HitCntEff::Polling()
 * size: 0x560 bytes
 * --------------------------------------------------------------------------- */
bool Polling__9HitCntEffFv(int param_1)

{
  bool bVar1;
  undefined4 uStack_14;
  
  uStack_14 = *(float *)(iGpffff86b4 + 0x38);
  if ((*(byte *)(iGpffff86b4 + 0x24) & 1) != 0) {
    uStack_14 = 0.0;
  }
  *(float *)(param_1 + 0x5c) = *(float *)(param_1 + 0x5c) - uStack_14;
  *(float *)(param_1 + 0x60) = (float)*(int *)(param_1 + 100) / 25.0 + 1.0;
  if (3.0 <= *(float *)(param_1 + 0x60)) {
    *(undefined4 *)(param_1 + 0x60) = 0x40400000;
  }
  *(float *)(param_1 + 0x60) = *(float *)(param_1 + 0x60) * (*(float *)(param_1 + 0x5c) / 0.2);
  *(float *)(param_1 + 0x60) = *(float *)(param_1 + 0x60) + 1.0;
  bVar1 = *(float *)(param_1 + 0x5c) <= 0.0;
  if (bVar1) {
    BtlEffRelease__7CBattleFiP6BtlEff(iGpffff86b4,0xffffffffffffffff,param_1);
    (**(code **)(*(int *)(param_1 + 0x34) + 0xc))();
  }
  return bVar1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x004fb4e0  MakePacket__9HitCntEffFv
 * C++: HitCntEff::MakePacket()
 * size: 0x954 bytes
 * --------------------------------------------------------------------------- */
void MakePacket__9HitCntEffFv(int param_1)

{
  bool bVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  undefined1 in_zero_qw [16];
  int iVar5;
  undefined4 uVar6;
  ulong uVar7;
  long lVar8;
  int iVar9;
  undefined8 in_v1_udw;
  undefined1 auVar10 [16];
  int iVar11;
  uint uVar12;
  uint auStack_80 [24];
  undefined4 uStack_20;
  float fStack_1c;
  float fStack_18;
  float fStack_14;
  int iStack_10;
  
  iStack_10 = param_1;
  iVar5 = GetDDisp__11CBtlPAfter2Fi(uGpffff86bc,*(undefined4 *)(param_1 + 0x48));
  bVar1 = (*(byte *)(iStack_10 + 0x40) & 1) == 0;
  uVar12 = (uint)bVar1;
  if (*(int *)(iStack_10 + uVar12 * 4 + 0x18) == 0) {
    uVar6 = __nwa__FUi(0x260);
    *(undefined4 *)(iStack_10 + uVar12 * 4 + 0x18) = uVar6;
    puVar3 = *(undefined4 **)(iStack_10 + uVar12 * 4 + 0x18);
    *puVar3 = 0x50000000;
    uStack_20 = *(undefined4 *)
                 (*(int *)(iGpffff86b4 + 0x4224) +
                  (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x4224) + 10) * 4 + 0xc);
    puVar3[1] = uStack_20;
    puVar3[2] = 0;
    puVar3[3] = 0;
    puVar3[4] = 0x10000023;
    puVar3[5] = 0;
    puVar3[6] = 0;
    puVar3[7] = 0x50000023;
    *(undefined8 *)(puVar3 + 8) = 0x7000000000000001;
    *(undefined8 *)(puVar3 + 10) = 0xe6ee8ee;
    *(undefined8 *)(puVar3 + 0xc) = 1;
    *(undefined8 *)(puVar3 + 0xe) = 0x3f;
    *(undefined8 *)(puVar3 + 0x10) = 0x60;
    *(undefined8 *)(puVar3 + 0x12) = 0x14;
    *(undefined8 *)(puVar3 + 0x14) = 5;
    *(undefined8 *)(puVar3 + 0x16) = 0;
    *(undefined8 *)(puVar3 + 0x18) = 0x23003;
    *(undefined8 *)(puVar3 + 0x1a) = 0x47;
    uVar7 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x4224),1);
    *(ulong *)(puVar3 + 0x1c) = uVar7 & 0xfffffffc0fffff | 0x2000000001300000;
    *(undefined8 *)(puVar3 + 0x1e) = 0x16;
    *(ulong *)(puVar3 + 0x20) = uVar7 & 0xffffffffffffff | 0x200000000000000;
    *(undefined8 *)(puVar3 + 0x22) = 0;
    *(undefined8 *)(puVar3 + 0x24) = 0x44;
    *(undefined8 *)(puVar3 + 0x26) = 0x42;
    *(undefined8 *)(puVar3 + 0x28) = 0x2400000000000001;
    *(undefined8 *)(puVar3 + 0x2a) = 0x10;
    *(undefined8 *)(puVar3 + 0x2c) = 0x154;
    *(undefined8 *)(puVar3 + 0x2e) = 0x80808080;
    auVar10._8_8_ = in_v1_udw;
    auVar10._0_8_ = 0x8400000000008006;
    auVar10 = _pcpyld(in_zero_qw,auVar10);
    *(long *)(puVar3 + 0x30) = auVar10._0_8_;
    *(undefined8 *)(puVar3 + 0x32) = 0x4343c3c3;
  }
  iVar4 = *(int *)(iStack_10 + uVar12 * 4 + 0x18);
  iVar11 = 0;
  fStack_1c = 0.0;
  for (iVar9 = 10000; 0 < iVar9; iVar9 = iVar9 / 10 + (iVar9 >> 0x1f)) {
    if ((iVar9 <= *(int *)(iStack_10 + 100)) || (iVar9 == 1)) {
      if (iVar9 == 0) {
        trap(7);
      }
      iVar2 = (*(int *)(iStack_10 + 100) / iVar9) % 10;
      auStack_80[iVar11 * 4] = (uint)*(ushort *)((iVar2 + 0x34) * 8 + 0x651b90);
      auStack_80[iVar11 * 4 + 1] = (uint)*(ushort *)((iVar2 + 0x34) * 8 + 0x651b92);
      auStack_80[iVar11 * 4 + 2] = (uint)*(ushort *)((iVar2 + 0x34) * 8 + 0x651b94);
      auStack_80[iVar11 * 4 + 3] = (uint)*(ushort *)((iVar2 + 0x34) * 8 + 0x651b96);
      fStack_1c = fStack_1c +
                  *(float *)(iStack_10 + 0x60) *
                  (float)(int)((auStack_80[iVar11 * 4 + 2] - auStack_80[iVar11 * 4]) + -2);
      iVar11 = iVar11 + 1;
    }
  }
  fStack_14 = *(float *)(iVar5 + 0x310) - fStack_1c / 2.0;
  fStack_18 = *(float *)(iVar5 + 0x314) -
              (*(float *)(iStack_10 + 0x60) * (float)(int)(auStack_80[3] - auStack_80[1])) / 2.0;
  for (iVar5 = 0; iVar5 < iVar11; iVar5 = iVar5 + 1) {
    *(long *)(iVar4 + (iVar5 * 4 + 0xd) * 0x10) =
         (long)(int)(auStack_80[iVar5 * 4] << 4) |
         (long)(int)(auStack_80[iVar5 * 4 + 1] << 4) << 0x10;
    uVar7 = __fixunssfdi(fStack_14 * 16.0);
    lVar8 = __fixunssfdi(fStack_18 * 16.0);
    *(ulong *)(iVar4 + (iVar5 * 4 + 0xd) * 0x10 + 8) = uVar7 | lVar8 << 0x10;
    *(long *)(iVar4 + (iVar5 * 4 + 0xe) * 0x10) =
         (long)(int)(auStack_80[iVar5 * 4] << 4) |
         (long)(int)(auStack_80[iVar5 * 4 + 3] << 4) << 0x10;
    lVar8 = __fixunssfdi((fStack_18 +
                            *(float *)(iStack_10 + 0x60) *
                            (float)(int)(auStack_80[iVar5 * 4 + 3] - auStack_80[iVar5 * 4 + 1])) *
                            16.0);
    uVar7 = __fixunssfdi(fStack_14 * 16.0);
    *(ulong *)(iVar4 + (iVar5 * 4 + 0xe) * 0x10 + 8) =
         uVar7 | CONCAT44((int)((ulong)lVar8 >> 0x10),(int)(lVar8 << 0x10));
    *(long *)(iVar4 + (iVar5 * 4 + 0xf) * 0x10) =
         (long)(int)(auStack_80[iVar5 * 4 + 2] << 4) |
         (long)(int)(auStack_80[iVar5 * 4 + 1] << 4) << 0x10;
    uVar7 = __fixunssfdi((fStack_14 +
                            *(float *)(iStack_10 + 0x60) *
                            (float)(int)(auStack_80[iVar5 * 4 + 2] - auStack_80[iVar5 * 4])) * 16.0)
    ;
    lVar8 = __fixunssfdi(fStack_18 * 16.0);
    *(ulong *)(iVar4 + (iVar5 * 4 + 0xf) * 0x10 + 8) = lVar8 << 0x10 | uVar7;
    *(long *)(iVar4 + (iVar5 * 4 + 0x10) * 0x10) =
         (long)(int)(auStack_80[iVar5 * 4 + 2] << 4) |
         (long)(int)(auStack_80[iVar5 * 4 + 3] << 4) << 0x10;
    lVar8 = __fixunssfdi((fStack_18 +
                            *(float *)(iStack_10 + 0x60) *
                            (float)(int)(auStack_80[iVar5 * 4 + 3] - auStack_80[iVar5 * 4 + 1])) *
                            16.0);
    uVar7 = __fixunssfdi((fStack_14 +
                            *(float *)(iStack_10 + 0x60) *
                            (float)(int)(auStack_80[iVar5 * 4 + 2] - auStack_80[iVar5 * 4])) * 16.0)
    ;
    *(ulong *)(iVar4 + (iVar5 * 4 + 0x10) * 0x10 + 8) =
         uVar7 | CONCAT44((int)((ulong)lVar8 >> 0x10),(int)(lVar8 << 0x10));
    fStack_14 = fStack_14 +
                *(float *)(iStack_10 + 0x60) *
                ((float)(int)(auStack_80[iVar5 * 4 + 2] - auStack_80[iVar5 * 4]) - 2.0);
  }
  for (; iVar5 < 6; iVar5 = iVar5 + 1) {
    *(undefined8 *)(iVar4 + (iVar5 * 4 + 0xd) * 0x10 + 8) = 0x71006f00;
    *(undefined8 *)(iVar4 + (iVar5 * 4 + 0xe) * 0x10 + 8) = 0x71006f00;
    *(undefined8 *)(iVar4 + (iVar5 * 4 + 0xf) * 0x10 + 8) = 0x71006f00;
    *(undefined8 *)(iVar4 + (iVar5 * 4 + 0x10) * 0x10 + 8) = 0x71006f00;
  }
  *(int *)(iStack_10 + 0x54) = iVar4 + 0x250;
  *(byte *)(iStack_10 + 0x40) = *(byte *)(iStack_10 + 0x40) & 0xfe | bVar1;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x004fbe40  Reset__9HitCntEffFi
 * C++: HitCntEff::Reset(int)
 * size: 0xa4 bytes
 * --------------------------------------------------------------------------- */
void Reset__9HitCntEffFi(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 0x5c) = 0x3e4ccccd;
  *(undefined4 *)(param_1 + 100) = param_2;
  *(float *)(param_1 + 0x60) = (float)*(int *)(param_1 + 100) / 25.0 + 2.0;
  if (4.0 <= *(float *)(param_1 + 0x60)) {
    *(undefined4 *)(param_1 + 0x60) = 0x40800000;
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b2f0  EndSet__9HitCntEffFv
 * C++: HitCntEff::EndSet()
 * size: 0x30 bytes
 * --------------------------------------------------------------------------- */
void EndSet__9HitCntEffFv(int param_1)

{
  (**(code **)(*(int *)(param_1 + 0x14) + 0x30))();
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b480  @24@__dt__9HitCntEffFv
 * C++: @24@__dt__9HitCntEffFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int * _24___dt__9HitCntEffFv(int *param_1,short param_2)

{
  int *piVar1;
  
  piVar1 = param_1 + -6;
  if (piVar1 != (int *)0x0) {
    param_1[-1] = 0x40a480;
    param_1[4] = 0x40a490;
    param_1[7] = 0x40a4a0;
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
 * JP: 0x0054b490  @44@__dt__9HitCntEffFv
 * C++: @44@__dt__9HitCntEffFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int _44___dt__9HitCntEffFv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x2c;
  if (iVar1 != 0) {
    *(undefined4 *)(param_1 + -0x18) = 0x40a480;
    *(undefined4 *)(param_1 + -4) = 0x40a490;
    *(undefined4 *)(param_1 + 8) = 0x40a4a0;
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

