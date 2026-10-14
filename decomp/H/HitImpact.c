/* decomp/H/HitImpact.c — cleaned Ghidra output (SH2JP_BATTLE.BIN, JP Furokuban, base 0x00430a00).
 * 9 function(s). Types: see types.h. Names/gp globals resolved from symbols/SLPM_602.19.syms. */
#include "types.h"

/* ---------------------------------------------------------------------------
 * JP: 0x0051dca0  __ct__9HitImpactFii7FVectorf
 * C++: HitImpact::__ct(int, int, FVector, float)
 * size: 0x10c bytes
 * --------------------------------------------------------------------------- */
undefined8
__ct__9HitImpactFii7FVectorf
          (undefined4 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
          undefined8 *param_5)

{
  undefined8 uVar1;
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  
  __ct__6BtlEffFii(param_2,param_3,param_4);
  iVar4 = (int)param_2;
  *(undefined4 *)(iVar4 + 0x14) = 0x409f20;
  *(undefined4 *)(iVar4 + 0x28) = 0x409f30;
  *(undefined4 *)(iVar4 + 0x34) = 0x409f40;
  *(undefined4 *)(iVar4 + 0x60) = in_zero_lo;
  *(undefined4 *)(iVar4 + 100) = in_zero_hi;
  *(undefined4 *)(iVar4 + 0x68) = in_zero_udw;
  *(undefined4 *)(iVar4 + 0x6c) = in_register_0000000c;
  *(undefined4 *)(iVar4 + 0x40) = 0;
  *(int *)(iVar4 + 0x44) = (int)param_3;
  *(int *)(iVar4 + 0x48) = (int)param_4;
  *(undefined4 *)(iVar4 + 0x4c) = 0x12;
  *(undefined4 *)(iVar4 + 0x5c) = 0;
  uVar1 = *param_5;
  uVar2 = *(undefined4 *)(param_5 + 1);
  uVar3 = *(undefined4 *)((int)param_5 + 0xc);
  *(int *)(iVar4 + 0x60) = (int)uVar1;
  *(int *)(iVar4 + 100) = (int)((ulong)uVar1 >> 0x20);
  *(undefined4 *)(iVar4 + 0x68) = uVar2;
  *(undefined4 *)(iVar4 + 0x6c) = uVar3;
  *(undefined4 *)(iVar4 + 0x74) = param_1;
  *(undefined4 *)(iVar4 + 0x70) = param_1;
  *(undefined4 *)(iVar4 + 0x78) = 0;
  *(undefined4 *)(iVar4 + 0x1c) = 0;
  *(undefined4 *)(iVar4 + 0x18) = 0;
  Entry__7CPollerFP7CPolObjib(iGpffff858c + 0x48,param_2,0x80,0);
  BtlEffEntry__7CBattleFiP6BtlEff(uGpffff86b4,0xffffffffffffffff,param_2);
  return param_2;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0051ddb0  __dt__9HitImpactFv
 * C++: HitImpact::__dt()
 * size: 0x154 bytes
 * --------------------------------------------------------------------------- */
int __dt__9HitImpactFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x14) = 0x409f20;
    *(undefined4 *)(param_1 + 0x28) = 0x409f30;
    *(undefined4 *)(param_1 + 0x34) = 0x409f40;
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
 * JP: 0x0051df10  Destruct__9HitImpactFv
 * C++: HitImpact::Destruct()
 * size: 0x5c bytes
 * --------------------------------------------------------------------------- */
void Destruct__9HitImpactFv(int param_1)

{
  BtlEffRelease__7CBattleFiP6BtlEff(uGpffff86b4,0xffffffffffffffff,param_1);
  Dispose__7CPollerFP7CPolObj(iGpffff858c + 0x48,param_1);
  (**(code **)(*(int *)(param_1 + 0x34) + 0xc))();
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0051df70  Polling__9HitImpactFv
 * C++: HitImpact::Polling()
 * size: 0x118 bytes
 * --------------------------------------------------------------------------- */
undefined4 Polling__9HitImpactFv(int param_1)

{
  if ((*(byte *)(iGpffff86b4 + 0x24) & 1) == 0) {
    if (*(float *)(param_1 + 0x5c) != 0.0) {
      *(float *)(param_1 + 0x74) =
           *(float *)(param_1 + 0x74) - *(float *)(iGpffff86b4 + 0x38) * 30.0;
    }
    *(float *)(param_1 + 0x5c) = *(float *)(param_1 + 0x5c) + *(float *)(iGpffff86b4 + 0x38);
    *(float *)(param_1 + 0x78) =
         *(float *)(param_1 + 0x78) + *(float *)(iGpffff86b4 + 0x38) * 4.0 * 30.0;
    if (*(float *)(param_1 + 0x74) <= 0.0) {
      BtlEffRelease__7CBattleFiP6BtlEff(iGpffff86b4,0xffffffffffffffff,param_1);
      (**(code **)(*(int *)(param_1 + 0x34) + 0xc))();
      return 1;
    }
  }
  return 0;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0051e090  MakePacket__9HitImpactFv
 * C++: HitImpact::MakePacket()
 * size: 0x1204 bytes
 * --------------------------------------------------------------------------- */
void MakePacket__9HitImpactFv(int param_1)

{
  bool bVar1;
  undefined4 *puVar2;
  undefined1 auVar3 [16];
  float in_zero_lo;
  float in_zero_hi;
  float in_zero_udw;
  float in_register_0000000c;
  undefined4 uVar4;
  long lVar5;
  ulong uVar6;
  float *pfVar7;
  undefined8 in_v1_udw;
  undefined1 auVar8 [16];
  undefined1 auVar9 [16];
  uint uVar10;
  int iVar11;
  int iVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  undefined1 auVar18 [16];
  undefined1 auStack_1120 [16];
  undefined1 auStack_1110 [8];
  float fStack_1108;
  float fStack_1104;
  float fStack_1100;
  undefined4 uStack_10fc;
  undefined4 uStack_10f8;
  undefined4 uStack_10f4;
  undefined4 uStack_10f0;
  undefined4 uStack_10ec;
  undefined4 uStack_10e8;
  undefined4 uStack_10e4;
  undefined4 uStack_10e0;
  undefined4 uStack_10dc;
  undefined4 uStack_10d8;
  undefined4 uStack_10d4;
  undefined4 uStack_10d0;
  undefined4 uStack_10cc;
  undefined4 uStack_10c8;
  undefined4 uStack_10c4;
  float fStack_10c0;
  float fStack_10bc;
  undefined4 uStack_10b8;
  undefined4 uStack_10b4;
  float fStack_10b0;
  float fStack_10ac;
  undefined4 uStack_10a8;
  undefined4 uStack_10a4;
  int aiStack_10a0 [260];
  float afStack_c90 [259];
  undefined4 uStack_884;
  float afStack_880 [16];
  float afStack_840 [263];
  undefined4 uStack_424;
  undefined4 uStack_420;
  undefined4 uStack_41c;
  undefined4 uStack_418;
  undefined4 uStack_414;
  undefined4 uStack_410;
  undefined4 uStack_40c;
  undefined4 uStack_408;
  undefined4 uStack_404;
  float afStack_400 [256];
  
  fVar16 = *(float *)(param_1 + 0x78);
  fVar13 = *(float *)(param_1 + 0x78) *
           ((*(float *)(param_1 + 0x70) - *(float *)(param_1 + 0x74) * 1.2) /
           *(float *)(param_1 + 0x70));
  if (fVar13 <= 0.0) {
    fVar13 = 0.0;
  }
  fVar15 = 0.0;
  pfVar7 = afStack_400;
  do {
    *pfVar7 = in_zero_lo;
    pfVar7[1] = in_zero_hi;
    pfVar7[2] = in_zero_udw;
    pfVar7[3] = in_register_0000000c;
    pfVar7 = pfVar7 + 4;
  } while (pfVar7 != (float *)&stack0x00000000);
  for (iVar11 = 0; iVar11 < 0x20; iVar11 = iVar11 + 1) {
    fVar14 = (float)sinf(fVar15);
    fVar14 = fVar16 * -fVar14;
    fStack_10b0 = (float)cosf(fVar15);
    fStack_10b0 = fVar16 * fStack_10b0;
    uStack_10a8 = 0;
    uStack_10a4 = 0x3f800000;
    afStack_400[iVar11 * 8] = fStack_10b0;
    afStack_400[iVar11 * 8 + 1] = fVar14;
    afStack_400[iVar11 * 8 + 2] = 0.0;
    afStack_400[iVar11 * 8 + 3] = 1.0;
    fStack_10ac = fVar14;
    fVar14 = (float)sinf(fVar15);
    fVar14 = fVar13 * -fVar14;
    fStack_10c0 = (float)cosf(fVar15);
    fStack_10c0 = fVar13 * fStack_10c0;
    uStack_10b8 = 0;
    uStack_10b4 = 0x3f800000;
    iVar12 = iVar11 * 2 + 1;
    afStack_400[iVar12 * 4] = fStack_10c0;
    afStack_400[iVar12 * 4 + 1] = fVar14;
    afStack_400[iVar12 * 4 + 2] = 0.0;
    afStack_400[iVar12 * 4 + 3] = 1.0;
    fVar15 = fVar15 + 0.19634955;
    fStack_10bc = fVar14;
  }
  __ct__6MatrixFRC6Matrix(afStack_840 + 0x100,iGpffff8598 + 0x240);
  uStack_410 = 0;
  uStack_40c = 0;
  uStack_408 = 0;
  uStack_404 = 0x3f800000;
  pfVar7 = afStack_840;
  do {
    *pfVar7 = in_zero_lo;
    pfVar7[1] = in_zero_hi;
    pfVar7[2] = in_zero_udw;
    pfVar7[3] = in_register_0000000c;
    pfVar7 = pfVar7 + 4;
  } while (pfVar7 != afStack_840 + 0x100);
  RotTransVector(afStack_840,afStack_400,afStack_840 + 0x100,0x40);
  GetViewScreenMatrix__9GsxCameraFv(&fStack_1100,iGpffff8598);
  afStack_840[0x100] = fStack_1100;
  afStack_840[0x101] = (float)uStack_10fc;
  afStack_840[0x102] = (float)uStack_10f8;
  afStack_840[0x103] = (float)uStack_10f4;
  afStack_840[0x104] = (float)uStack_10f0;
  afStack_840[0x105] = (float)uStack_10ec;
  afStack_840[0x106] = (float)uStack_10e8;
  uStack_424 = uStack_10e4;
  uStack_420 = uStack_10e0;
  uStack_41c = uStack_10dc;
  uStack_418 = uStack_10d8;
  uStack_414 = uStack_10d4;
  uStack_410 = uStack_10d0;
  uStack_40c = uStack_10cc;
  uStack_408 = uStack_10c8;
  uStack_404 = uStack_10c4;
  for (iVar11 = 0; iVar11 < 4; iVar11 = iVar11 + 1) {
    afStack_880[iVar11 * 4] = afStack_840[iVar11 * 4 + 0x100];
    afStack_880[iVar11 * 4 + 1] = afStack_840[iVar11 * 4 + 0x101];
    afStack_880[iVar11 * 4 + 2] = afStack_840[iVar11 * 4 + 0x102];
    afStack_880[iVar11 * 4 + 3] = afStack_840[iVar11 * 4 + 0x103];
  }
  for (iVar11 = 0; iVar11 < 0x40; iVar11 = iVar11 + 1) {
    afStack_c90[iVar11 * 4] = *(float *)(param_1 + 0x60) + afStack_840[iVar11 * 4];
    afStack_c90[iVar11 * 4 + 1] = *(float *)(param_1 + 100) + afStack_840[iVar11 * 4 + 1];
    afStack_c90[iVar11 * 4 + 2] = *(float *)(param_1 + 0x68) + afStack_840[iVar11 * 4 + 2];
    afStack_c90[iVar11 * 4 + 3] = 1.0;
  }
  afStack_c90[0x100] = *(float *)(param_1 + 0x60);
  afStack_c90[0x101] = *(float *)(param_1 + 100);
  afStack_c90[0x102] = *(float *)(param_1 + 0x68);
  uStack_884 = 0x3f800000;
  sceVu0RotTransPersN(aiStack_10a0,afStack_880,afStack_c90,0x41,0);
  afStack_400[0] = (float)aiStack_10a0[0x100] / 16.0 - 1792.0;
  afStack_400[1] = (float)aiStack_10a0[0x101] / 16.0 - 1824.0;
  afStack_400[2] = 0.0;
  afStack_400[3] = 1.0;
  fVar13 = *(float *)(param_1 + 0x70);
  fVar16 = *(float *)(param_1 + 0x74);
  for (iVar11 = 0; iVar11 < 0x40; iVar11 = iVar11 + 1) {
    fVar14 = 1.0;
    fVar15 = 1.0;
    if (aiStack_10a0[iVar11 * 4] < 0) {
      fVar17 = ((float)aiStack_10a0[iVar11 * 4] / 16.0 - 1792.0) - afStack_400[0];
      fVar14 = afStack_400[0] + 1792.0;
      if (fVar17 < 0.0) {
        fVar17 = fVar17 * -1.0;
      }
      if (fVar14 < 0.0) {
        fVar14 = fVar14 * -1.0;
      }
      fVar14 = fVar14 / fVar17;
    }
    else if (0x10000 < aiStack_10a0[iVar11 * 4]) {
      fVar17 = ((float)aiStack_10a0[iVar11 * 4] / 16.0 - 1792.0) - afStack_400[0];
      fVar14 = 2304.0 - afStack_400[0];
      if (fVar17 < 0.0) {
        fVar17 = fVar17 * -1.0;
      }
      if (fVar14 < 0.0) {
        fVar14 = fVar14 * -1.0;
      }
      fVar14 = fVar14 / fVar17;
    }
    if (aiStack_10a0[iVar11 * 4 + 1] < 0) {
      fVar17 = ((float)aiStack_10a0[iVar11 * 4 + 1] / 16.0 - 1824.0) - afStack_400[1];
      fVar15 = afStack_400[1] + 1824.0;
      if (fVar17 < 0.0) {
        fVar17 = fVar17 * -1.0;
      }
      if (fVar15 < 0.0) {
        fVar15 = fVar15 * -1.0;
      }
      fVar15 = fVar15 / fVar17;
    }
    else if (0x10000 < aiStack_10a0[iVar11 * 4 + 1]) {
      fVar17 = ((float)aiStack_10a0[iVar11 * 4 + 1] / 16.0 - 1824.0) - afStack_400[1];
      fVar15 = 2272.0 - afStack_400[1];
      if (fVar17 < 0.0) {
        fVar17 = fVar17 * -1.0;
      }
      if (fVar15 < 0.0) {
        fVar15 = fVar15 * -1.0;
      }
      fVar15 = fVar15 / fVar17;
    }
    if ((fVar14 != 1.0) || (fVar15 != 1.0)) {
      if (fVar14 <= fVar15) {
        fVar15 = fVar14;
      }
      afStack_400[4] = ((float)aiStack_10a0[iVar11 * 4] / 16.0 - 1792.0) - afStack_400[0];
      afStack_400[5] = ((float)aiStack_10a0[iVar11 * 4 + 1] / 16.0 - 1824.0) - afStack_400[1];
      afStack_400[6] = 0.0;
      afStack_400[7] = 1.0;
      __amu__7FVectorFf(fVar15,afStack_400 + 4);
      aiStack_10a0[iVar11 * 4] = (int)((afStack_400[4] + afStack_400[0] + 1792.0) * 16.0);
      aiStack_10a0[iVar11 * 4 + 1] = (int)((afStack_400[5] + afStack_400[1] + 1824.0) * 16.0);
    }
    afStack_400[4] = ((float)aiStack_10a0[iVar11 * 4] / 16.0 - 1792.0) - afStack_400[0];
    afStack_400[5] = ((float)aiStack_10a0[iVar11 * 4 + 1] / 16.0 - 1824.0) - afStack_400[1];
    afStack_400[6] = 0.0;
    afStack_400[7] = 1.0;
    __amu__7FVectorFf(1.0 - fVar16 / (fVar13 / 0.3),afStack_400 + 4);
    auVar18._4_4_ = afStack_400[5];
    auVar18._0_4_ = afStack_400[4];
    auVar18._8_4_ = afStack_400[6];
    auVar18._12_4_ = afStack_400[7];
    auVar18 = _lqc2(auVar18);
    auVar9._4_4_ = afStack_400[1];
    auVar9._0_4_ = afStack_400[0];
    auVar9._8_4_ = afStack_400[2];
    auVar9._12_4_ = afStack_400[3];
    auVar9 = _lqc2(auVar9);
    auVar9 = _vadd(auVar18,auVar9);
    auStack_1120 = _sqc2(auVar9);
    __ct__7FVectorFRC7FVector(auStack_1110,auStack_1120);
    afStack_840[iVar11 * 4] = auStack_1110._0_4_;
    afStack_840[iVar11 * 4 + 1] = auStack_1110._4_4_;
    afStack_840[iVar11 * 4 + 2] = fStack_1108;
    afStack_840[iVar11 * 4 + 3] = fStack_1104;
    fVar14 = 1.0;
    fVar15 = 1.0;
    if ((afStack_840[iVar11 * 4] < 0.0) || (512.0 < afStack_840[iVar11 * 4])) {
      fVar14 = afStack_840[iVar11 * 4] - 256.0;
      if (fVar14 < 0.0) {
        fVar14 = fVar14 * -1.0;
      }
      fVar14 = 256.0 / fVar14;
    }
    if ((afStack_840[iVar11 * 4 + 1] < 0.0) || (448.0 < afStack_840[iVar11 * 4 + 1])) {
      fVar15 = afStack_840[iVar11 * 4 + 1] - 224.0;
      if (fVar15 < 0.0) {
        fVar15 = fVar15 * -1.0;
      }
      fVar15 = 224.0 / fVar15;
    }
    if ((fVar14 != 1.0) || (fVar15 != 1.0)) {
      if (fVar14 <= fVar15) {
        fVar15 = fVar14;
      }
      fVar14 = afStack_840[iVar11 * 4 + 1];
      afStack_840[iVar11 * 4] = fVar15 * (afStack_840[iVar11 * 4] - 256.0) + 256.0;
      afStack_840[iVar11 * 4 + 1] = fVar15 * (fVar14 - 224.0) + 224.0;
    }
  }
  iVar12 = 0;
  bVar1 = (*(byte *)(param_1 + 0x40) & 1) == 0;
  for (iVar11 = 0; iVar11 < 0x40; iVar11 = iVar11 + 1) {
    if ((((0x6fff < aiStack_10a0[iVar11 * 4]) && (aiStack_10a0[iVar11 * 4] < 0x9001)) &&
        (0x71ff < aiStack_10a0[iVar11 * 4 + 1])) &&
       ((aiStack_10a0[iVar11 * 4 + 1] < 0x8e01 && (-1 < aiStack_10a0[iVar11 * 4 + 2])))) {
      iVar12 = iVar12 + 1;
    }
  }
  uVar10 = (uint)bVar1;
  if (*(int *)(param_1 + uVar10 * 4 + 0x18) == 0) {
    uVar4 = __nwa__FUi(0x4d0);
    *(undefined4 *)(param_1 + uVar10 * 4 + 0x18) = uVar4;
    iVar11 = *(int *)(param_1 + uVar10 * 4 + 0x18);
    *(undefined8 *)(iVar11 + 0x10) = 0x5000000000000001;
    *(undefined8 *)(iVar11 + 0x18) = 0x6ee8e;
    *(undefined8 *)(iVar11 + 0x20) = 0x60;
    *(undefined8 *)(iVar11 + 0x28) = 0x14;
    *(undefined8 *)(iVar11 + 0x30) = 5;
    *(undefined8 *)(iVar11 + 0x38) = 0;
    *(undefined8 *)(iVar11 + 0x40) = 0x3001;
    *(undefined8 *)(iVar11 + 0x48) = 0x47;
    *(undefined8 *)(iVar11 + 0x50) = 0x44;
    *(undefined8 *)(iVar11 + 0x58) = 0x42;
    auVar8._8_8_ = in_v1_udw;
    auVar8._0_8_ = 0xffffffffffffc000;
    auVar3._4_4_ = in_zero_hi;
    auVar3._0_4_ = in_zero_lo;
    auVar3._8_4_ = in_zero_udw;
    auVar3._12_4_ = in_register_0000000c;
    auVar9 = _pcpyld(auVar3,auVar8);
    *(ulong *)(iVar11 + 0x60) =
         (**(ulong **)(iGpffff8598 + 0x340) & 0x7ffffffff & auVar9._0_8_) + 0x2a00;
    *(undefined8 *)(iVar11 + 0x68) = 0;
    *(undefined8 *)(iVar11 + 0x70) = 0x6400000000000001;
    *(undefined8 *)(iVar11 + 0x78) = 0xc3c310;
    *(undefined8 *)(iVar11 + 0x80) = 0x154;
    *(undefined8 *)(iVar11 + 0x88) = 0x180808080;
    *(undefined8 *)(iVar11 + 0xb0) = 0x4400000000008020;
    *(undefined8 *)(iVar11 + 0xb8) = 0x4343;
  }
  puVar2 = *(undefined4 **)(param_1 + uVar10 * 4 + 0x18);
  if (iVar12 == 0) {
    *(undefined4 **)(param_1 + 0x54) = puVar2;
    *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfe | bVar1;
  }
  else {
    *puVar2 = 0x1000004b;
    puVar2[1] = 0;
    puVar2[2] = 0;
    puVar2[3] = 0x5000004b;
    lVar5 = __fixunssfdi((afStack_840[1] + 0.0) * 16.0);
    uVar6 = __fixunssfdi(afStack_840[0] * 16.0);
    *(ulong *)(puVar2 + 0x24) = uVar6 | lVar5 << 0x10;
    *(long *)(puVar2 + 0x26) = (long)aiStack_10a0[0] | (long)aiStack_10a0[1] << 0x10;
    lVar5 = __fixunssfdi((afStack_840[5] + 0.0) * 16.0);
    uVar6 = __fixunssfdi(afStack_840[4] * 16.0);
    *(ulong *)(puVar2 + 0x28) = uVar6 | lVar5 << 0x10;
    *(long *)(puVar2 + 0x2a) = (long)aiStack_10a0[4] | (long)aiStack_10a0[5] << 0x10;
    for (iVar11 = 1; iVar11 < 0x20; iVar11 = iVar11 + 1) {
      lVar5 = __fixunssfdi((afStack_840[iVar11 * 8 + 1] + 0.0) * 16.0);
      uVar6 = __fixunssfdi(afStack_840[iVar11 * 8] * 16.0);
      *(ulong *)(puVar2 + (iVar11 * 2 + 10) * 4) = uVar6 | lVar5 << 0x10;
      *(long *)(puVar2 + (iVar11 * 2 + 10) * 4 + 2) =
           (long)aiStack_10a0[iVar11 * 8] | (long)aiStack_10a0[iVar11 * 8 + 1] << 0x10;
      lVar5 = __fixunssfdi((afStack_840[(iVar11 * 2 + 1) * 4 + 1] + 0.0) * 16.0);
      uVar6 = __fixunssfdi(afStack_840[(iVar11 * 2 + 1) * 4] * 16.0);
      *(ulong *)(puVar2 + (iVar11 * 2 + 0xb) * 4) = uVar6 | lVar5 << 0x10;
      *(long *)(puVar2 + (iVar11 * 2 + 0xb) * 4 + 2) =
           (long)aiStack_10a0[(iVar11 * 2 + 1) * 4] |
           (long)aiStack_10a0[(iVar11 * 2 + 1) * 4 + 1] << 0x10;
    }
    lVar5 = __fixunssfdi((afStack_840[1] + 0.0) * 16.0);
    uVar6 = __fixunssfdi(afStack_840[0] * 16.0);
    *(ulong *)(puVar2 + 0x128) = uVar6 | lVar5 << 0x10;
    *(long *)(puVar2 + 0x12a) = (long)aiStack_10a0[0] | (long)aiStack_10a0[1] << 0x10;
    lVar5 = __fixunssfdi((afStack_840[5] + 0.0) * 16.0);
    uVar6 = __fixunssfdi(afStack_840[4] * 16.0);
    *(ulong *)(puVar2 + 300) = uVar6 | lVar5 << 0x10;
    *(long *)(puVar2 + 0x12e) = (long)aiStack_10a0[4] | (long)aiStack_10a0[5] << 0x10;
    *(undefined4 **)(param_1 + 0x54) = puVar2 + 0x130;
    *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfe | bVar1;
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0051f2a0  Reset__9HitImpactF7FVectorf
 * C++: HitImpact::Reset(FVector, float)
 * size: 0x34 bytes
 * --------------------------------------------------------------------------- */
void Reset__9HitImpactF7FVectorf(undefined4 param_1,int param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  *(undefined4 *)(param_2 + 0x5c) = 0;
  uVar1 = param_3[1];
  uVar2 = param_3[2];
  uVar3 = param_3[3];
  *(undefined4 *)(param_2 + 0x60) = *param_3;
  *(undefined4 *)(param_2 + 100) = uVar1;
  *(undefined4 *)(param_2 + 0x68) = uVar2;
  *(undefined4 *)(param_2 + 0x6c) = uVar3;
  *(undefined4 *)(param_2 + 0x74) = param_1;
  *(undefined4 *)(param_2 + 0x70) = param_1;
  *(undefined4 *)(param_2 + 0x78) = 0;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054aee0  EndSet__9HitImpactFv
 * C++: HitImpact::EndSet()
 * size: 0x30 bytes
 * --------------------------------------------------------------------------- */
void EndSet__9HitImpactFv(int param_1)

{
  (**(code **)(*(int *)(param_1 + 0x14) + 0x30))();
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b720  @24@__dt__9HitImpactFv
 * C++: @24@__dt__9HitImpactFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int * _24___dt__9HitImpactFv(int *param_1,short param_2)

{
  int *piVar1;
  
  piVar1 = param_1 + -6;
  if (piVar1 != (int *)0x0) {
    param_1[-1] = 0x409f20;
    param_1[4] = 0x409f30;
    param_1[7] = 0x409f40;
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
 * JP: 0x0054b730  @44@__dt__9HitImpactFv
 * C++: @44@__dt__9HitImpactFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int _44___dt__9HitImpactFv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x2c;
  if (iVar1 != 0) {
    *(undefined4 *)(param_1 + -0x18) = 0x409f20;
    *(undefined4 *)(param_1 + -4) = 0x409f30;
    *(undefined4 *)(param_1 + 8) = 0x409f40;
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

