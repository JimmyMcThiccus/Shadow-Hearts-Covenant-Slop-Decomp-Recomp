/* decomp/H/CircleArea.c — cleaned Ghidra output (SH2JP_BATTLE.BIN, JP Furokuban, base 0x00430a00).
 * 9 function(s). Types: see types.h. Names/gp globals resolved from symbols/SLPM_602.19.syms. */
#include "types.h"

/* ---------------------------------------------------------------------------
 * JP: 0x00537220  __ct__10CircleAreaFiif
 * C++: CircleArea::__ct(int, int, float)
 * size: 0xd0 bytes
 * --------------------------------------------------------------------------- */
int __ct__10CircleAreaFiif(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  __ct__6BtlEffFii(param_2,param_3,param_4);
  *(undefined4 *)(param_2 + 0x14) = 0x409bb0;
  *(undefined4 *)(param_2 + 0x28) = 0x409bc0;
  *(undefined4 *)(param_2 + 0x34) = 0x409bd0;
  *(undefined4 *)(param_2 + 0x40) = 0;
  *(undefined4 *)(param_2 + 0x44) = param_3;
  *(undefined4 *)(param_2 + 0x48) = param_4;
  *(undefined4 *)(param_2 + 0x4c) = 9;
  *(undefined4 *)(param_2 + 0x5c) = param_1;
  *(undefined4 *)(param_2 + 0x1c) = 0;
  *(undefined4 *)(param_2 + 0x18) = 0;
  BtlEffEntry__7CBattleFiP6BtlEff(uGpffff86b4,*(undefined4 *)(param_2 + 0x48),param_2);
  return param_2;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005372f0  __dt__10CircleAreaFv
 * C++: CircleArea::__dt()
 * size: 0x154 bytes
 * --------------------------------------------------------------------------- */
int __dt__10CircleAreaFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x14) = 0x409bb0;
    *(undefined4 *)(param_1 + 0x28) = 0x409bc0;
    *(undefined4 *)(param_1 + 0x34) = 0x409bd0;
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
 * JP: 0x00537450  Destruct__10CircleAreaFv
 * C++: CircleArea::Destruct()
 * size: 0x4c bytes
 * --------------------------------------------------------------------------- */
void Destruct__10CircleAreaFv(int param_1)

{
  BtlEffRelease__7CBattleFiP6BtlEff(uGpffff86b4,*(undefined4 *)(param_1 + 0x48),param_1);
  (**(code **)(*(int *)(param_1 + 0x34) + 0xc))();
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005374a0  Polling__10CircleAreaFv
 * C++: CircleArea::Polling()
 * size: 0x14 bytes
 * --------------------------------------------------------------------------- */
undefined8 Polling__10CircleAreaFv(void)

{
  return 0;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005374c0  MakePacket__10CircleAreaFv
 * C++: CircleArea::MakePacket()
 * size: 0xaa4 bytes
 * --------------------------------------------------------------------------- */
void MakePacket__10CircleAreaFv(int param_1)

{
  bool bVar1;
  undefined4 *puVar2;
  bool bVar3;
  undefined4 uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  float fVar8;
  float fVar9;
  undefined1 auVar10 [16];
  undefined1 auVar11 [16];
  undefined1 auStack_8c0 [16];
  int aiStack_8b0 [276];
  int aiStack_460 [16];
  float afStack_420 [4];
  float afStack_410 [260];
  
  auVar10 = _lqc2(*(undefined1 (*) [16])(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x150));
  auVar11 = _lqc2(*(undefined1 (*) [16])(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x390));
  auVar10 = _vadd(auVar10,auVar11);
  auStack_8c0 = _sqc2(auVar10);
  __ct__7FVectorFRC7FVector(afStack_420,auStack_8c0);
  afStack_420[1] = 0.0;
  fVar9 = 0.0;
  afStack_410[0] = afStack_420[0];
  afStack_410[1] = -0.2;
  afStack_410[2] = afStack_420[2];
  afStack_410[3] = 1.0;
  for (iVar7 = 0; iVar7 < 0x20; iVar7 = iVar7 + 1) {
    fVar8 = (float)cosf(fVar9);
    afStack_410[(iVar7 + 1) * 4] = afStack_420[0] + *(float *)(param_1 + 0x5c) * fVar8;
    afStack_410[(iVar7 + 1) * 4 + 1] = -0.2;
    fVar8 = (float)sinf(fVar9);
    afStack_410[(iVar7 + 1) * 4 + 2] = afStack_420[2] - *(float *)(param_1 + 0x5c) * fVar8;
    afStack_410[(iVar7 + 1) * 4 + 3] = 1.0;
    fVar8 = (float)cosf(fVar9);
    afStack_410[(iVar7 + 0x21) * 4] = afStack_420[0] + *(float *)(param_1 + 0x5c) * fVar8;
    afStack_410[(iVar7 + 0x21) * 4 + 1] = -30.0;
    fVar8 = (float)sinf(fVar9);
    afStack_410[(iVar7 + 0x21) * 4 + 2] = afStack_420[2] - *(float *)(param_1 + 0x5c) * fVar8;
    afStack_410[(iVar7 + 0x21) * 4 + 3] = 1.0;
    fVar9 = fVar9 + 0.19634955;
    if (3.1415927 <= fVar9) {
      fVar9 = fVar9 - 6.2831855;
    }
  }
  GetViewScreenMatrix__9GsxCameraFv(aiStack_460,uGpffff8598);
  for (iVar7 = 0; iVar7 < 4; iVar7 = iVar7 + 1) {
    aiStack_8b0[iVar7 * 4 + 0x104] = aiStack_460[iVar7 * 4];
    aiStack_8b0[iVar7 * 4 + 0x105] = aiStack_460[iVar7 * 4 + 1];
    aiStack_8b0[iVar7 * 4 + 0x106] = aiStack_460[iVar7 * 4 + 2];
    aiStack_8b0[iVar7 * 4 + 0x107] = aiStack_460[iVar7 * 4 + 3];
  }
  sceVu0RotTransPersN(aiStack_8b0,aiStack_8b0 + 0x104,afStack_410,0x41,0);
  bVar3 = false;
  iVar7 = 0;
  for (iVar6 = 0; iVar6 < 0x41; iVar6 = iVar6 + 1) {
    if (iVar6 == 0) {
      if ((((aiStack_8b0[0] < 0) || (0x10000 < aiStack_8b0[0])) || (aiStack_8b0[1] < 0)) ||
         ((0x10000 < aiStack_8b0[1] || (aiStack_8b0[2] < 0)))) {
        bVar3 = true;
      }
      iVar7 = (int)((float)aiStack_8b0[2] / 16.0);
      aiStack_8b0[2] = iVar7;
    }
    else {
      aiStack_8b0[iVar6 * 4 + 2] = (int)((float)aiStack_8b0[iVar6 * 4 + 2] / 16.0);
    }
  }
  *(int *)(param_1 + 0x50) = iVar7;
  bVar1 = (*(byte *)(param_1 + 0x40) & 1) == 0;
  uVar5 = (uint)bVar1;
  if (*(int *)(param_1 + uVar5 * 4 + 0x18) == 0) {
    uVar4 = __nwa__FUi(0x5f0);
    *(undefined4 *)(param_1 + uVar5 * 4 + 0x18) = uVar4;
    iVar7 = *(int *)(param_1 + uVar5 * 4 + 0x18);
    *(undefined8 *)(iVar7 + 0x10) = 0x2000000000000001;
    *(undefined8 *)(iVar7 + 0x18) = 0xee;
    *(undefined8 *)(iVar7 + 0x20) = 0x53001;
    *(undefined8 *)(iVar7 + 0x28) = 0x47;
    *(undefined8 *)(iVar7 + 0x30) = 0x44;
    *(undefined8 *)(iVar7 + 0x38) = 0x42;
    *(undefined8 *)(iVar7 + 0x40) = 0x6400000000000001;
    *(undefined8 *)(iVar7 + 0x48) = 0xc1c1f0;
    *(undefined8 *)(iVar7 + 0x50) = 0x4d;
    *(undefined8 *)(iVar7 + 0x58) = 0;
    *(undefined8 *)(iVar7 + 0x60) = 0x10020a0ff;
    *(undefined8 *)(iVar7 + 0x70) = 0x17020a0ff;
    *(undefined8 *)(iVar7 + 0x80) = 0x2400000000000010;
    *(undefined8 *)(iVar7 + 0x88) = 0x44;
    *(undefined8 *)(iVar7 + 400) = 0x6400000000000001;
    *(undefined8 *)(iVar7 + 0x198) = 0xc1c1f0;
    *(undefined8 *)(iVar7 + 0x1a0) = 0x4c;
    *(undefined8 *)(iVar7 + 0x1a8) = 0;
    *(undefined8 *)(iVar7 + 0x1b0) = 0x11080c0ff;
    *(undefined8 *)(iVar7 + 0x1c0) = 0x13080c0ff;
    *(undefined8 *)(iVar7 + 0x1d0) = 0x4400000000008020;
    *(undefined8 *)(iVar7 + 0x1d8) = 0x4141;
    for (iVar6 = 0; iVar6 < 0x20; iVar6 = iVar6 + 1) {
      *(undefined8 *)(iVar7 + (iVar6 * 2 + 0x1e) * 0x10) = 0x11080c0ff;
      *(undefined8 *)(iVar7 + (iVar6 * 2 + 0x1f) * 0x10) = 0x13080c0ff;
    }
  }
  puVar2 = *(undefined4 **)(param_1 + uVar5 * 4 + 0x18);
  if (bVar3) {
    *(undefined4 **)(param_1 + 0x54) = puVar2;
    *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfe | bVar1;
  }
  else {
    *puVar2 = 0x1000005d;
    puVar2[1] = 0;
    puVar2[2] = 0x11000000;
    puVar2[3] = 0x5000005d;
    *(long *)(puVar2 + 0x1a) =
         (long)aiStack_8b0[2] << 0x20 | (long)aiStack_8b0[0] | (long)aiStack_8b0[1] << 0x10;
    *(long *)(puVar2 + 0x1e) =
         (long)aiStack_8b0[6] << 0x20 | (long)aiStack_8b0[4] | (long)aiStack_8b0[5] << 0x10;
    for (iVar7 = 0; iVar7 < 0xf; iVar7 = iVar7 + 1) {
      *(long *)(puVar2 + (iVar7 + 9) * 4) =
           (long)aiStack_8b0[(iVar7 * 2 + 2) * 4 + 2] << 0x20 |
           (long)aiStack_8b0[(iVar7 * 2 + 2) * 4] |
           (long)aiStack_8b0[(iVar7 * 2 + 2) * 4 + 1] << 0x10;
      *(long *)(puVar2 + (iVar7 + 9) * 4 + 2) =
           (long)aiStack_8b0[(iVar7 * 2 + 3) * 4 + 2] << 0x20 |
           (long)aiStack_8b0[(iVar7 * 2 + 3) * 4] |
           (long)aiStack_8b0[(iVar7 * 2 + 3) * 4 + 1] << 0x10;
    }
    *(long *)(puVar2 + 0x60) =
         (long)aiStack_8b0[0x82] << 0x20 | (long)aiStack_8b0[0x80] | (long)aiStack_8b0[0x81] << 0x10
    ;
    *(long *)(puVar2 + 0x62) =
         (long)aiStack_8b0[6] << 0x20 | (long)aiStack_8b0[4] | (long)aiStack_8b0[5] << 0x10;
    *(long *)(puVar2 + 0x6e) =
         (long)aiStack_8b0[0x86] << 0x20 | (long)aiStack_8b0[0x84] | (long)aiStack_8b0[0x85] << 0x10
    ;
    *(long *)(puVar2 + 0x72) =
         (long)aiStack_8b0[6] << 0x20 | (long)aiStack_8b0[4] | (long)aiStack_8b0[5] << 0x10;
    for (iVar7 = 0; iVar7 < 0x1f; iVar7 = iVar7 + 1) {
      *(long *)(puVar2 + (iVar7 * 2 + 0x1e) * 4 + 2) =
           (long)aiStack_8b0[(iVar7 + 0x22) * 4 + 2] << 0x20 |
           (long)aiStack_8b0[(iVar7 + 0x22) * 4] | (long)aiStack_8b0[(iVar7 + 0x22) * 4 + 1] << 0x10
      ;
      *(long *)(puVar2 + (iVar7 * 2 + 0x1f) * 4 + 2) =
           (long)aiStack_8b0[(iVar7 + 2) * 4 + 2] << 0x20 |
           (long)aiStack_8b0[(iVar7 + 2) * 4] | (long)aiStack_8b0[(iVar7 + 2) * 4 + 1] << 0x10;
    }
    *(long *)(puVar2 + 0x172) =
         (long)aiStack_8b0[0x86] << 0x20 | (long)aiStack_8b0[0x84] | (long)aiStack_8b0[0x85] << 0x10
    ;
    *(long *)(puVar2 + 0x176) =
         (long)aiStack_8b0[6] << 0x20 | (long)aiStack_8b0[4] | (long)aiStack_8b0[5] << 0x10;
    *(undefined4 **)(param_1 + 0x54) = puVar2 + 0x178;
    *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfe | bVar1;
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00537f70  ChangeTarget__10CircleAreaFi
 * C++: CircleArea::ChangeTarget(int)
 * size: 0x5c bytes
 * --------------------------------------------------------------------------- */
void ChangeTarget__10CircleAreaFi(int param_1,undefined4 param_2)

{
  BtlEffRelease__7CBattleFiP6BtlEff(uGpffff86b4,*(undefined4 *)(param_1 + 0x48),param_1);
  *(undefined4 *)(param_1 + 0x48) = param_2;
  BtlEffEntry__7CBattleFiP6BtlEff(uGpffff86b4,*(undefined4 *)(param_1 + 0x48),param_1);
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054ae00  EndSet__10CircleAreaFv
 * C++: CircleArea::EndSet()
 * size: 0x10 bytes
 * --------------------------------------------------------------------------- */
void EndSet__10CircleAreaFv(void)

{
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b890  @24@__dt__10CircleAreaFv
 * C++: @24@__dt__10CircleAreaFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int * _24___dt__10CircleAreaFv(int *param_1,short param_2)

{
  int *piVar1;
  
  piVar1 = param_1 + -6;
  if (piVar1 != (int *)0x0) {
    param_1[-1] = 0x409bb0;
    param_1[4] = 0x409bc0;
    param_1[7] = 0x409bd0;
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
 * JP: 0x0054b8a0  @44@__dt__10CircleAreaFv
 * C++: @44@__dt__10CircleAreaFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int _44___dt__10CircleAreaFv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x2c;
  if (iVar1 != 0) {
    *(undefined4 *)(param_1 + -0x18) = 0x409bb0;
    *(undefined4 *)(param_1 + -4) = 0x409bc0;
    *(undefined4 *)(param_1 + 8) = 0x409bd0;
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

