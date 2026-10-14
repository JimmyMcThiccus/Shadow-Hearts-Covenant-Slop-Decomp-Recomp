/* decomp/H/ScytheAddAttribute1.c — cleaned Ghidra output (SH2JP_BATTLE.BIN, JP Furokuban, base 0x00430a00).
 * 8 function(s). Types: see types.h. Names/gp globals resolved from symbols/SLPM_602.19.syms. */
#include "types.h"

/* ---------------------------------------------------------------------------
 * JP: 0x00531a10  __ct__19ScytheAddAttribute1Fiiii
 * C++: ScytheAddAttribute1::__ct(int, int, int, int)
 * size: 0x210 bytes
 * --------------------------------------------------------------------------- */
int __ct__19ScytheAddAttribute1Fiiii
              (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
              undefined4 param_5)

{
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  int iVar1;
  undefined4 *puVar2;
  
  __ct__6BtlEffFii(param_1,param_2,param_3);
  *(undefined4 *)(param_1 + 0x14) = 0x409c50;
  *(undefined4 *)(param_1 + 0x28) = 0x409c60;
  *(undefined4 *)(param_1 + 0x34) = 0x409c70;
  puVar2 = (undefined4 *)(param_1 + 0x70);
  do {
    *puVar2 = in_zero_lo;
    puVar2[1] = in_zero_hi;
    puVar2[2] = in_zero_udw;
    puVar2[3] = in_register_0000000c;
    puVar2 = puVar2 + 4;
  } while (puVar2 != (undefined4 *)(param_1 + 0xf0));
  puVar2 = (undefined4 *)(param_1 + 0x200);
  do {
    *puVar2 = in_zero_lo;
    puVar2[1] = in_zero_hi;
    puVar2[2] = in_zero_udw;
    puVar2[3] = in_register_0000000c;
    puVar2 = puVar2 + 4;
  } while (puVar2 != (undefined4 *)(param_1 + 0x400));
  *(undefined4 *)(param_1 + 0x40) = 0;
  *(undefined4 *)(param_1 + 0x44) = param_2;
  *(undefined4 *)(param_1 + 0x48) = param_3;
  *(undefined4 *)(param_1 + 0x4c) = 6;
  *(undefined4 *)(param_1 + 0x5c) = 0;
  *(undefined4 *)(param_1 + 0x60) = param_4;
  *(undefined4 *)(param_1 + 0xf0) = 0;
  *(undefined4 *)(param_1 + 0xf4) = 0;
  *(undefined4 *)(param_1 + 0xf8) = 0;
  *(undefined4 *)(param_1 + 100) = param_5;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  *(undefined4 *)(param_1 + 0x18) = 0;
  for (iVar1 = 0; iVar1 < 0x20; iVar1 = iVar1 + 1) {
    *(undefined2 *)(param_1 + iVar1 * 2 + 0xfc) = 0;
  }
  Entry__7CPollerFP7CPolObjib(iGpffff858c + 0x48,param_1,0x80,0);
  iVar1 = param_1;
  if (param_1 != 0) {
    iVar1 = param_1 + 0x18;
  }
  AddOT__5WorldFiP8VIF1Prim(0x42bf10,8,iVar1);
  *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfd | 2;
  BtlEffEntry__7CBattleFiP6BtlEff(uGpffff86b4,*(undefined4 *)(param_1 + 0x48),param_1);
  return param_1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00531c20  __dt__19ScytheAddAttribute1Fv
 * C++: ScytheAddAttribute1::__dt()
 * size: 0x154 bytes
 * --------------------------------------------------------------------------- */
int __dt__19ScytheAddAttribute1Fv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x14) = 0x409c50;
    *(undefined4 *)(param_1 + 0x28) = 0x409c60;
    *(undefined4 *)(param_1 + 0x34) = 0x409c70;
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
 * JP: 0x00531d80  Destruct__19ScytheAddAttribute1Fv
 * C++: ScytheAddAttribute1::Destruct()
 * size: 0xcc bytes
 * --------------------------------------------------------------------------- */
void Destruct__19ScytheAddAttribute1Fv(int param_1)

{
  int iVar1;
  
  BtlEffRelease__7CBattleFiP6BtlEff(uGpffff86b4,*(undefined4 *)(param_1 + 0x48),param_1);
  Dispose__7CPollerFP7CPolObj(iGpffff858c + 0x48,param_1);
  if ((long)((ulong)*(byte *)(param_1 + 0x40) << 0x3e) < 0) {
    iVar1 = param_1;
    if (param_1 != 0) {
      iVar1 = param_1 + 0x18;
    }
    ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,iVar1);
  }
  *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfd;
  (**(code **)(*(int *)(param_1 + 0x34) + 0xc))();
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00531e50  Polling__19ScytheAddAttribute1Fv
 * C++: ScytheAddAttribute1::Polling()
 * size: 0x858 bytes
 * --------------------------------------------------------------------------- */
undefined8 Polling__19ScytheAddAttribute1Fv(int param_1)

{
  short sVar1;
  float in_zero_lo;
  float in_zero_hi;
  float in_zero_udw;
  float in_register_0000000c;
  int iVar2;
  float *pfVar3;
  byte *pbVar4;
  int iVar5;
  float fVar6;
  float fVar7;
  undefined1 in_vf0 [16];
  undefined1 auVar8 [16];
  undefined1 auVar9 [16];
  undefined1 auVar10 [16];
  undefined1 auStack_1d0 [16];
  undefined1 auStack_1c0 [16];
  undefined1 auStack_1b0 [8];
  undefined4 uStack_1a8;
  undefined4 uStack_1a4;
  undefined1 auStack_1a0 [16];
  undefined1 auStack_190 [8];
  float fStack_188;
  float fStack_184;
  undefined1 auStack_180 [8];
  undefined4 uStack_178;
  undefined4 uStack_174;
  undefined1 auStack_170 [16];
  undefined1 auStack_160 [8];
  float fStack_158;
  float fStack_154;
  float fStack_150;
  float fStack_14c;
  float fStack_148;
  float fStack_144;
  undefined1 auStack_140 [16];
  undefined1 auStack_130 [16];
  undefined1 auStack_120 [16];
  undefined1 auStack_110 [16];
  float afStack_100 [43];
  undefined4 uStack_54;
  undefined1 auStack_50 [8];
  float fStack_48;
  undefined4 uStack_44;
  undefined1 auStack_40 [64];
  
  fVar6 = *(float *)(iGpffff86b4 + 0x38);
  if ((*(byte *)(iGpffff86b4 + 0x24) & 1) != 0) {
    fVar6 = 0.0;
  }
  *(float *)(param_1 + 0xf8) = *(float *)(param_1 + 0xf8) + fVar6 * 6.2831855 * 0.75;
  if (3.1415927 <= *(float *)(param_1 + 0xf8)) {
    *(float *)(param_1 + 0xf8) = *(float *)(param_1 + 0xf8) - 6.2831855;
  }
  if (((*(int *)(param_1 + 0x5c) != 1) && (*(int *)(param_1 + 0x5c) == 0)) &&
     (*(float *)(param_1 + 0xf0) = *(float *)(param_1 + 0xf0) + fVar6 * 2.0,
     1.0 <= *(float *)(param_1 + 0xf0))) {
    *(undefined4 *)(param_1 + 0xf0) = 0x3f800000;
    *(undefined4 *)(param_1 + 0x5c) = 1;
  }
  pbVar4 = (byte *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x144) + 0xe4
                            ) + *(int *)(param_1 + 100) * 0x110);
  __ct__6MatrixFRC6Matrix(auStack_40,
                  *(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x144) + 0x30)
                  + (uint)*pbVar4 * 0x1f0 + (bGpffff8340 & 1) * 0x40);
  auStack_50._4_4_ = (*(float *)(pbVar4 + 0x14) + *(float *)(pbVar4 + 0x34)) / 2.0;
  auStack_50._0_4_ = (*(float *)(pbVar4 + 0x10) + *(float *)(pbVar4 + 0x30)) / 2.0;
  fStack_48 = (*(float *)(pbVar4 + 0x18) + *(float *)(pbVar4 + 0x38)) / 2.0;
  uStack_44 = 0x3f800000;
  afStack_100[0x2a] = (*(float *)(pbVar4 + 0x28) + *(float *)(pbVar4 + 0x48)) / 2.0;
  afStack_100[0x29] = (*(float *)(pbVar4 + 0x24) + *(float *)(pbVar4 + 0x44)) / 2.0;
  afStack_100[0x28] = (*(float *)(pbVar4 + 0x20) + *(float *)(pbVar4 + 0x40)) / 2.0;
  uStack_54 = 0x3f800000;
  auVar8._4_4_ = afStack_100[0x29];
  auVar8._0_4_ = afStack_100[0x28];
  auVar8._8_4_ = afStack_100[0x2a];
  auVar8._12_4_ = 0x3f800000;
  auVar9 = _lqc2(auVar8);
  auVar8 = _lqc2(_auStack_50);
  auVar8 = _vsub(auVar8,auVar9);
  _auStack_50 = _sqc2(auVar8);
  pfVar3 = afStack_100;
  do {
    *pfVar3 = in_zero_lo;
    pfVar3[1] = in_zero_hi;
    pfVar3[2] = in_zero_udw;
    pfVar3[3] = in_register_0000000c;
    pfVar3 = pfVar3 + 4;
  } while (pfVar3 != afStack_100 + 0x28);
  auVar8 = _vmr32(in_vf0);
  auVar9 = _vmr32(auVar8);
  auVar10 = _vmr32(auVar9);
  auStack_110 = _sqc2(in_vf0);
  auStack_120 = _sqc2(auVar8);
  auStack_130 = _sqc2(auVar9);
  auStack_140 = _sqc2(auVar10);
  *(float *)(param_1 + 0xf4) = *(float *)(param_1 + 0xf4) + fVar6;
  fStack_150 = in_zero_lo;
  fStack_14c = in_zero_hi;
  fStack_148 = in_zero_udw;
  fStack_144 = in_register_0000000c;
  for (iVar5 = 0; iVar5 < 0x20; iVar5 = iVar5 + 1) {
    sVar1 = *(short *)(param_1 + iVar5 * 2 + 0xfc);
    if (sVar1 == 1) {
      iVar2 = param_1 + iVar5 * 4;
      *(float *)(iVar2 + 0x17c) = *(float *)(iVar2 + 0x17c) + fVar6;
      iVar2 = param_1 + iVar5 * 0x10;
      *(float *)(iVar2 + 0x204) = *(float *)(iVar2 + 0x204) - fVar6 * 2.0;
      if (*(float *)(param_1 + iVar5 * 4 + 0x17c) < 0.6666667) {
        *(undefined4 *)(param_1 + iVar5 * 4 + 0x480) = 0x43000000;
      }
      else {
        *(float *)(param_1 + iVar5 * 4 + 0x480) =
             ((1.0 - *(float *)(param_1 + iVar5 * 4 + 0x17c)) / 0.33333334) * 128.0;
      }
      if ((1.0 <= *(float *)(param_1 + iVar5 * 4 + 0x17c)) &&
         (*(undefined2 *)(param_1 + iVar5 * 2 + 0xfc) = 0, 0.06666667 <= *(float *)(param_1 + 0xf4))
         ) {
        *(undefined2 *)(param_1 + iVar5 * 2 + 0xfc) = 1;
        *(undefined4 *)(param_1 + iVar5 * 4 + 0x17c) = 0;
        iVar2 = rand();
        fVar7 = (float)iVar2 / 2.1474836e+09;
        auVar8 = _vmr32(in_vf0);
        auVar9 = _vmr32(auVar8);
        auVar10 = _vmr32(auVar9);
        auStack_110 = _sqc2(in_vf0);
        auStack_120 = _sqc2(auVar8);
        auStack_130 = _sqc2(auVar9);
        auStack_140 = _sqc2(auVar10);
        sceVu0RotMatrixZ((fVar7 * 75.0 * 3.1415927) / 180.0,auStack_140,auStack_140);
        fStack_150 = auStack_50._0_4_;
        fStack_14c = auStack_50._4_4_;
        fStack_148 = fStack_48;
        fStack_144 = (float)uStack_44;
        __amu__7FVectorFf((1.0 - fVar7 * 0.35) + fVar7 * 0.2,&fStack_150);
        ApplyMatrix__6MatrixCFRC7FVector(auStack_1a0,auStack_140,&fStack_150);
        auVar8 = _lqc2(auStack_1a0);
        auVar9._4_4_ = afStack_100[0x29];
        auVar9._0_4_ = afStack_100[0x28];
        auVar9._8_4_ = afStack_100[0x2a];
        auVar9._12_4_ = uStack_54;
        auVar9 = _lqc2(auVar9);
        auVar8 = _vadd(auVar8,auVar9);
        auStack_1d0 = _sqc2(auVar8);
        __ct__7FVectorFRC7FVector(auStack_190,auStack_1d0);
        fStack_150 = auStack_190._0_4_;
        fStack_14c = auStack_190._4_4_;
        fStack_148 = fStack_188;
        fStack_144 = fStack_184;
        ApplyMatrix__6MatrixCFRC7FVector(auStack_1b0,auStack_40,&fStack_150);
        iVar2 = param_1 + iVar5 * 0x10;
        *(int *)(iVar2 + 0x200) = auStack_1b0._0_4_;
        *(int *)(iVar2 + 0x204) = auStack_1b0._4_4_;
        *(undefined4 *)(iVar2 + 0x208) = uStack_1a8;
        *(undefined4 *)(iVar2 + 0x20c) = uStack_1a4;
        *(undefined4 *)(param_1 + iVar5 * 4 + 0x400) = 0x3f800000;
        *(undefined4 *)(param_1 + iVar5 * 4 + 0x480) = 0x3f800000;
        *(float *)(param_1 + 0xf4) = *(float *)(param_1 + 0xf4) - 0.06666667;
      }
    }
    else if ((sVar1 == 0) && (0.06666667 <= *(float *)(param_1 + 0xf4))) {
      *(undefined2 *)(param_1 + iVar5 * 2 + 0xfc) = 1;
      *(undefined4 *)(param_1 + iVar5 * 4 + 0x17c) = 0;
      iVar2 = rand();
      fVar7 = (float)iVar2 / 2.1474836e+09;
      auVar8 = _vmr32(in_vf0);
      auVar9 = _vmr32(auVar8);
      auVar10 = _vmr32(auVar9);
      auStack_110 = _sqc2(in_vf0);
      auStack_120 = _sqc2(auVar8);
      auStack_130 = _sqc2(auVar9);
      auStack_140 = _sqc2(auVar10);
      sceVu0RotMatrixZ((fVar7 * 75.0 * 3.1415927) / 180.0,auStack_140,auStack_140);
      fStack_150 = auStack_50._0_4_;
      fStack_14c = auStack_50._4_4_;
      fStack_148 = fStack_48;
      fStack_144 = (float)uStack_44;
      __amu__7FVectorFf((1.0 - fVar7 * 0.35) + fVar7 * 0.2,&fStack_150);
      ApplyMatrix__6MatrixCFRC7FVector(auStack_170,auStack_140,&fStack_150);
      auVar8 = _lqc2(auStack_170);
      auVar10._4_4_ = afStack_100[0x29];
      auVar10._0_4_ = afStack_100[0x28];
      auVar10._8_4_ = afStack_100[0x2a];
      auVar10._12_4_ = uStack_54;
      auVar9 = _lqc2(auVar10);
      auVar8 = _vadd(auVar8,auVar9);
      auStack_1c0 = _sqc2(auVar8);
      __ct__7FVectorFRC7FVector(auStack_160,auStack_1c0);
      fStack_150 = auStack_160._0_4_;
      fStack_14c = auStack_160._4_4_;
      fStack_148 = fStack_158;
      fStack_144 = fStack_154;
      ApplyMatrix__6MatrixCFRC7FVector(auStack_180,auStack_40,&fStack_150);
      iVar2 = param_1 + iVar5 * 0x10;
      *(int *)(iVar2 + 0x200) = auStack_180._0_4_;
      *(int *)(iVar2 + 0x204) = auStack_180._4_4_;
      *(undefined4 *)(iVar2 + 0x208) = uStack_178;
      *(undefined4 *)(iVar2 + 0x20c) = uStack_174;
      *(undefined4 *)(param_1 + iVar5 * 4 + 0x400) = 0x3f800000;
      *(undefined4 *)(param_1 + iVar5 * 4 + 0x480) = 0x3f800000;
      *(float *)(param_1 + 0xf4) = *(float *)(param_1 + 0xf4) - 0.06666667;
    }
  }
  return 0;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005326b0  MakePacket__19ScytheAddAttribute1Fv
 * C++: ScytheAddAttribute1::MakePacket()
 * size: 0x1fe8 bytes
 * --------------------------------------------------------------------------- */
/* WARNING: Removing unreachable block (ram,0x00533f18) */
/* WARNING: Removing unreachable block (ram,0x00533e58) */
/* WARNING: Removing unreachable block (ram,0x00533fd8) */

void MakePacket__19ScytheAddAttribute1Fv(int param_1)

{
  bool bVar1;
  undefined4 *puVar2;
  undefined1 auVar3 [16];
  bool bVar4;
  bool bVar5;
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  undefined1 auVar8 [16];
  undefined1 auVar9 [16];
  undefined1 auVar10 [16];
  undefined1 auVar11 [16];
  undefined1 auVar12 [16];
  undefined1 auVar13 [16];
  undefined1 auVar14 [16];
  float in_zero_lo;
  float in_zero_hi;
  float in_zero_udw;
  float in_register_0000000c;
  undefined4 uVar15;
  undefined8 uVar16;
  float *pfVar17;
  undefined8 in_v1_udw;
  undefined1 auVar18 [16];
  uint uVar19;
  byte *pbVar20;
  int iVar21;
  int iVar22;
  float fVar23;
  int iVar24;
  int iVar25;
  int iVar26;
  undefined1 in_vf0 [16];
  undefined1 auVar27 [16];
  undefined1 auVar28 [16];
  undefined1 auVar29 [16];
  undefined1 auStack_1680 [16];
  undefined1 auStack_1670 [16];
  undefined1 auStack_1660 [16];
  undefined1 auStack_1650 [16];
  undefined1 auStack_1640 [16];
  undefined1 auStack_1630 [16];
  undefined1 auStack_1620 [16];
  undefined1 auStack_1610 [16];
  undefined1 auStack_1600 [16];
  undefined1 auStack_15f0 [16];
  undefined1 auStack_15e0 [16];
  undefined1 auStack_15d0 [16];
  undefined1 auStack_15c0 [16];
  undefined1 auStack_15b0 [16];
  undefined1 auStack_15a0 [16];
  undefined1 auStack_1590 [16];
  undefined1 auStack_1580 [16];
  undefined1 auStack_1570 [16];
  undefined1 auStack_1560 [16];
  undefined1 auStack_1550 [16];
  undefined1 auStack_1540 [16];
  undefined4 uStack_1530;
  undefined4 uStack_152c;
  undefined4 uStack_1528;
  undefined4 uStack_1524;
  undefined4 uStack_1520;
  undefined4 uStack_151c;
  undefined4 uStack_1518;
  undefined4 uStack_1514;
  undefined4 uStack_1510;
  undefined4 uStack_150c;
  undefined4 uStack_1508;
  undefined4 uStack_1504;
  undefined4 uStack_1500;
  undefined4 uStack_14fc;
  undefined4 uStack_14f8;
  undefined4 uStack_14f4;
  undefined1 auStack_14f0 [64];
  undefined1 auStack_14b0 [8];
  undefined4 uStack_14a8;
  undefined4 uStack_14a4;
  undefined1 auStack_14a0 [16];
  undefined1 auStack_1490 [16];
  undefined1 auStack_1480 [8];
  undefined4 uStack_1478;
  undefined4 uStack_1474;
  undefined1 auStack_1470 [16];
  undefined1 auStack_1460 [16];
  undefined1 auStack_1450 [8];
  undefined4 uStack_1448;
  undefined4 uStack_1444;
  undefined1 auStack_1440 [16];
  undefined1 auStack_1430 [16];
  undefined1 auStack_1420 [8];
  undefined4 uStack_1418;
  undefined4 uStack_1414;
  undefined1 auStack_1410 [16];
  undefined1 auStack_1400 [16];
  undefined1 auStack_13f0 [8];
  undefined4 uStack_13e8;
  undefined4 uStack_13e4;
  undefined1 auStack_13e0 [16];
  undefined1 auStack_13d0 [16];
  undefined1 auStack_13c0 [8];
  undefined4 uStack_13b8;
  undefined4 uStack_13b4;
  undefined1 auStack_13b0 [16];
  undefined1 auStack_13a0 [16];
  undefined1 auStack_1390 [8];
  undefined4 uStack_1388;
  undefined4 uStack_1384;
  undefined1 auStack_1380 [16];
  undefined1 auStack_1370 [16];
  undefined1 auStack_1360 [8];
  undefined4 uStack_1358;
  undefined4 uStack_1354;
  undefined1 auStack_1350 [16];
  undefined1 auStack_1340 [16];
  undefined1 auStack_1330 [8];
  undefined4 uStack_1328;
  undefined4 uStack_1324;
  undefined1 auStack_1320 [16];
  undefined1 auStack_1310 [16];
  undefined1 auStack_1300 [8];
  undefined4 uStack_12f8;
  undefined4 uStack_12f4;
  undefined1 auStack_12f0 [16];
  undefined1 auStack_12e0 [16];
  undefined1 auStack_12d0 [8];
  undefined4 uStack_12c8;
  undefined4 uStack_12c4;
  float afStack_12c0 [512];
  int aiStack_ac0 [568];
  float afStack_1e0 [40];
  undefined1 auStack_140 [16];
  undefined1 auStack_130 [16];
  undefined1 auStack_120 [16];
  undefined1 auStack_110 [16];
  float afStack_100 [43];
  undefined4 uStack_54;
  undefined1 auStack_50 [8];
  float fStack_48;
  undefined4 uStack_44;
  undefined1 auStack_40 [64];
  
  pbVar20 = (byte *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x144) +
                             0xe4) + *(int *)(param_1 + 100) * 0x110);
  __ct__6MatrixFRC6Matrix(auStack_40,
                  *(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x144) + 0x30)
                  + (uint)*pbVar20 * 0x1f0 + (bGpffff8340 & 1) * 0x40);
  auStack_50._4_4_ = (*(float *)(pbVar20 + 0x14) + *(float *)(pbVar20 + 0x34)) / 2.0;
  auStack_50._0_4_ = (*(float *)(pbVar20 + 0x10) + *(float *)(pbVar20 + 0x30)) / 2.0;
  fStack_48 = (*(float *)(pbVar20 + 0x18) + *(float *)(pbVar20 + 0x38)) / 2.0;
  uStack_44 = 0x3f800000;
  afStack_100[0x2a] = (*(float *)(pbVar20 + 0x28) + *(float *)(pbVar20 + 0x48)) / 2.0;
  afStack_100[0x29] = (*(float *)(pbVar20 + 0x24) + *(float *)(pbVar20 + 0x44)) / 2.0;
  afStack_100[0x28] = (*(float *)(pbVar20 + 0x20) + *(float *)(pbVar20 + 0x40)) / 2.0;
  uStack_54 = 0x3f800000;
  auVar27._4_4_ = afStack_100[0x29];
  auVar27._0_4_ = afStack_100[0x28];
  auVar27._8_4_ = afStack_100[0x2a];
  auVar27._12_4_ = 0x3f800000;
  auVar28 = _lqc2(auVar27);
  auVar27 = _lqc2(_auStack_50);
  auVar27 = _vsub(auVar27,auVar28);
  _auStack_50 = _sqc2(auVar27);
  pfVar17 = afStack_100;
  do {
    *pfVar17 = in_zero_lo;
    pfVar17[1] = in_zero_hi;
    pfVar17[2] = in_zero_udw;
    pfVar17[3] = in_register_0000000c;
    pfVar17 = pfVar17 + 4;
  } while (pfVar17 != afStack_100 + 0x28);
  auVar27 = _vmr32(in_vf0);
  auVar28 = _vmr32(auVar27);
  auVar29 = _vmr32(auVar28);
  _sqc2(in_vf0);
  _sqc2(auVar27);
  _sqc2(auVar28);
  _sqc2(auVar29);
  auVar27 = _vmr32(in_vf0);
  auVar28 = _vmr32(auVar27);
  auVar29 = _vmr32(auVar28);
  auStack_110 = _sqc2(in_vf0);
  auStack_120 = _sqc2(auVar27);
  auStack_130 = _sqc2(auVar28);
  auStack_140 = _sqc2(auVar29);
  sceVu0RotMatrixZ(0xbeb2b8c3,auStack_140,auStack_140);
  auVar27 = _lqc2(_auStack_50);
  auVar28 = _qmtc2(0x3f8ccccd);
  auVar27 = _vmulbc(auVar27,auVar28);
  auStack_15f0 = _sqc2(auVar27);
  __ct__7FVectorFRC7FVector(auStack_12f0,auStack_15f0);
  ApplyMatrix__6MatrixCFRC7FVector(auStack_12e0,auStack_140,auStack_12f0);
  auVar27 = _lqc2(auStack_12e0);
  auVar28._4_4_ = afStack_100[0x29];
  auVar28._0_4_ = afStack_100[0x28];
  auVar28._8_4_ = afStack_100[0x2a];
  auVar28._12_4_ = uStack_54;
  auVar28 = _lqc2(auVar28);
  auVar27 = _vadd(auVar27,auVar28);
  auStack_1540 = _sqc2(auVar27);
  __ct__7FVectorFRC7FVector(auStack_12d0,auStack_1540);
  afStack_100[0] = auStack_12d0._0_4_;
  afStack_100[1] = auStack_12d0._4_4_;
  afStack_100[2] = (float)uStack_12c8;
  afStack_100[3] = (float)uStack_12c4;
  auVar27 = _lqc2(_auStack_50);
  auVar28 = _qmtc2(0x3f4ccccd);
  auVar27 = _vmulbc(auVar27,auVar28);
  auStack_1600 = _sqc2(auVar27);
  __ct__7FVectorFRC7FVector(auStack_1320,auStack_1600);
  ApplyMatrix__6MatrixCFRC7FVector(auStack_1310,auStack_140,auStack_1320);
  auVar27 = _lqc2(auStack_1310);
  auVar29._4_4_ = afStack_100[0x29];
  auVar29._0_4_ = afStack_100[0x28];
  auVar29._8_4_ = afStack_100[0x2a];
  auVar29._12_4_ = uStack_54;
  auVar28 = _lqc2(auVar29);
  auVar27 = _vadd(auVar27,auVar28);
  auStack_1550 = _sqc2(auVar27);
  __ct__7FVectorFRC7FVector(auStack_1300,auStack_1550);
  afStack_100[4] = auStack_1300._0_4_;
  afStack_100[5] = auStack_1300._4_4_;
  afStack_100[6] = (float)uStack_12f8;
  afStack_100[7] = (float)uStack_12f4;
  auVar27 = _vmr32(in_vf0);
  auVar28 = _vmr32(auVar27);
  auVar29 = _vmr32(auVar28);
  auStack_110 = _sqc2(in_vf0);
  auStack_120 = _sqc2(auVar27);
  auStack_130 = _sqc2(auVar28);
  auStack_140 = _sqc2(auVar29);
  sceVu0RotMatrixZ(0x3d8efa35,auStack_140,auStack_140);
  auVar27 = _lqc2(_auStack_50);
  auVar28 = _qmtc2(0x3f99999a);
  auVar27 = _vmulbc(auVar27,auVar28);
  auStack_1610 = _sqc2(auVar27);
  __ct__7FVectorFRC7FVector(auStack_1350,auStack_1610);
  ApplyMatrix__6MatrixCFRC7FVector(auStack_1340,auStack_140,auStack_1350);
  auVar27 = _lqc2(auStack_1340);
  auVar7._4_4_ = afStack_100[0x29];
  auVar7._0_4_ = afStack_100[0x28];
  auVar7._8_4_ = afStack_100[0x2a];
  auVar7._12_4_ = uStack_54;
  auVar28 = _lqc2(auVar7);
  auVar27 = _vadd(auVar27,auVar28);
  auStack_1560 = _sqc2(auVar27);
  __ct__7FVectorFRC7FVector(auStack_1330,auStack_1560);
  afStack_100[8] = auStack_1330._0_4_;
  afStack_100[9] = auStack_1330._4_4_;
  afStack_100[10] = (float)uStack_1328;
  afStack_100[0xb] = (float)uStack_1324;
  auVar27 = _lqc2(_auStack_50);
  auVar28 = _qmtc2(0x3f4ccccd);
  auVar27 = _vmulbc(auVar27,auVar28);
  auStack_1620 = _sqc2(auVar27);
  __ct__7FVectorFRC7FVector(auStack_1380,auStack_1620);
  ApplyMatrix__6MatrixCFRC7FVector(auStack_1370,auStack_140,auStack_1380);
  auVar27 = _lqc2(auStack_1370);
  auVar8._4_4_ = afStack_100[0x29];
  auVar8._0_4_ = afStack_100[0x28];
  auVar8._8_4_ = afStack_100[0x2a];
  auVar8._12_4_ = uStack_54;
  auVar28 = _lqc2(auVar8);
  auVar27 = _vadd(auVar27,auVar28);
  auStack_1570 = _sqc2(auVar27);
  __ct__7FVectorFRC7FVector(auStack_1360,auStack_1570);
  afStack_100[0xc] = auStack_1360._0_4_;
  afStack_100[0xd] = auStack_1360._4_4_;
  afStack_100[0xe] = (float)uStack_1358;
  afStack_100[0xf] = (float)uStack_1354;
  auVar27 = _vmr32(in_vf0);
  auVar28 = _vmr32(auVar27);
  auVar29 = _vmr32(auVar28);
  auStack_110 = _sqc2(in_vf0);
  auStack_120 = _sqc2(auVar27);
  auStack_130 = _sqc2(auVar28);
  auStack_140 = _sqc2(auVar29);
  sceVu0RotMatrixZ(0x3f0a8264,auStack_140,auStack_140);
  auVar27 = _lqc2(_auStack_50);
  auVar28 = _qmtc2(0x3f9c28f6);
  auVar27 = _vmulbc(auVar27,auVar28);
  auStack_1630 = _sqc2(auVar27);
  __ct__7FVectorFRC7FVector(auStack_13b0,auStack_1630);
  ApplyMatrix__6MatrixCFRC7FVector(auStack_13a0,auStack_140,auStack_13b0);
  auVar27 = _lqc2(auStack_13a0);
  auVar9._4_4_ = afStack_100[0x29];
  auVar9._0_4_ = afStack_100[0x28];
  auVar9._8_4_ = afStack_100[0x2a];
  auVar9._12_4_ = uStack_54;
  auVar28 = _lqc2(auVar9);
  auVar27 = _vadd(auVar27,auVar28);
  auStack_1580 = _sqc2(auVar27);
  __ct__7FVectorFRC7FVector(auStack_1390,auStack_1580);
  afStack_100[0x10] = auStack_1390._0_4_;
  afStack_100[0x11] = auStack_1390._4_4_;
  afStack_100[0x12] = (float)uStack_1388;
  afStack_100[0x13] = (float)uStack_1384;
  auVar27 = _lqc2(_auStack_50);
  auVar28 = _qmtc2(0x3f333333);
  auVar27 = _vmulbc(auVar27,auVar28);
  auStack_1640 = _sqc2(auVar27);
  __ct__7FVectorFRC7FVector(auStack_13e0,auStack_1640);
  ApplyMatrix__6MatrixCFRC7FVector(auStack_13d0,auStack_140,auStack_13e0);
  auVar27 = _lqc2(auStack_13d0);
  auVar10._4_4_ = afStack_100[0x29];
  auVar10._0_4_ = afStack_100[0x28];
  auVar10._8_4_ = afStack_100[0x2a];
  auVar10._12_4_ = uStack_54;
  auVar28 = _lqc2(auVar10);
  auVar27 = _vadd(auVar27,auVar28);
  auStack_1590 = _sqc2(auVar27);
  __ct__7FVectorFRC7FVector(auStack_13c0,auStack_1590);
  afStack_100[0x14] = auStack_13c0._0_4_;
  afStack_100[0x15] = auStack_13c0._4_4_;
  afStack_100[0x16] = (float)uStack_13b8;
  afStack_100[0x17] = (float)uStack_13b4;
  auVar27 = _vmr32(in_vf0);
  auVar28 = _vmr32(auVar27);
  auVar29 = _vmr32(auVar28);
  auStack_110 = _sqc2(in_vf0);
  auStack_120 = _sqc2(auVar27);
  auStack_130 = _sqc2(auVar28);
  auStack_140 = _sqc2(auVar29);
  sceVu0RotMatrixZ(0x3f8192c0,auStack_140,auStack_140);
  auVar27 = _lqc2(_auStack_50);
  auVar28 = _qmtc2(0x3f9eb852);
  auVar27 = _vmulbc(auVar27,auVar28);
  auStack_1650 = _sqc2(auVar27);
  __ct__7FVectorFRC7FVector(auStack_1410,auStack_1650);
  ApplyMatrix__6MatrixCFRC7FVector(auStack_1400,auStack_140,auStack_1410);
  auVar27 = _lqc2(auStack_1400);
  auVar11._4_4_ = afStack_100[0x29];
  auVar11._0_4_ = afStack_100[0x28];
  auVar11._8_4_ = afStack_100[0x2a];
  auVar11._12_4_ = uStack_54;
  auVar28 = _lqc2(auVar11);
  auVar27 = _vadd(auVar27,auVar28);
  auStack_15a0 = _sqc2(auVar27);
  __ct__7FVectorFRC7FVector(auStack_13f0,auStack_15a0);
  afStack_100[0x18] = auStack_13f0._0_4_;
  afStack_100[0x19] = auStack_13f0._4_4_;
  afStack_100[0x1a] = (float)uStack_13e8;
  afStack_100[0x1b] = (float)uStack_13e4;
  auVar27 = _lqc2(_auStack_50);
  auVar28 = _qmtc2(0x3f147ae1);
  auVar27 = _vmulbc(auVar27,auVar28);
  auStack_1660 = _sqc2(auVar27);
  __ct__7FVectorFRC7FVector(auStack_1440,auStack_1660);
  ApplyMatrix__6MatrixCFRC7FVector(auStack_1430,auStack_140,auStack_1440);
  auVar27 = _lqc2(auStack_1430);
  auVar12._4_4_ = afStack_100[0x29];
  auVar12._0_4_ = afStack_100[0x28];
  auVar12._8_4_ = afStack_100[0x2a];
  auVar12._12_4_ = uStack_54;
  auVar28 = _lqc2(auVar12);
  auVar27 = _vadd(auVar27,auVar28);
  auStack_15b0 = _sqc2(auVar27);
  __ct__7FVectorFRC7FVector(auStack_1420,auStack_15b0);
  afStack_100[0x1c] = auStack_1420._0_4_;
  afStack_100[0x1d] = auStack_1420._4_4_;
  afStack_100[0x1e] = (float)uStack_1418;
  afStack_100[0x1f] = (float)uStack_1414;
  auVar27 = _vmr32(in_vf0);
  auVar28 = _vmr32(auVar27);
  auVar29 = _vmr32(auVar28);
  auStack_110 = _sqc2(in_vf0);
  auStack_120 = _sqc2(auVar27);
  auStack_130 = _sqc2(auVar28);
  auStack_140 = _sqc2(auVar29);
  sceVu0RotMatrixZ(0x3fbde44e,auStack_140,auStack_140);
  auVar27 = _lqc2(_auStack_50);
  auVar28 = _qmtc2(0x3fa33333);
  auVar27 = _vmulbc(auVar27,auVar28);
  auStack_1670 = _sqc2(auVar27);
  __ct__7FVectorFRC7FVector(auStack_1470,auStack_1670);
  ApplyMatrix__6MatrixCFRC7FVector(auStack_1460,auStack_140,auStack_1470);
  auVar27 = _lqc2(auStack_1460);
  auVar13._4_4_ = afStack_100[0x29];
  auVar13._0_4_ = afStack_100[0x28];
  auVar13._8_4_ = afStack_100[0x2a];
  auVar13._12_4_ = uStack_54;
  auVar28 = _lqc2(auVar13);
  auVar27 = _vadd(auVar27,auVar28);
  auStack_15c0 = _sqc2(auVar27);
  __ct__7FVectorFRC7FVector(auStack_1450,auStack_15c0);
  afStack_100[0x20] = auStack_1450._0_4_;
  afStack_100[0x21] = auStack_1450._4_4_;
  afStack_100[0x22] = (float)uStack_1448;
  afStack_100[0x23] = (float)uStack_1444;
  auVar27 = _lqc2(_auStack_50);
  auVar28 = _qmtc2(0x3ed70a3d);
  auVar27 = _vmulbc(auVar27,auVar28);
  auStack_1680 = _sqc2(auVar27);
  __ct__7FVectorFRC7FVector(auStack_14a0,auStack_1680);
  ApplyMatrix__6MatrixCFRC7FVector(auStack_1490,auStack_140,auStack_14a0);
  auVar27 = _lqc2(auStack_1490);
  auVar14._4_4_ = afStack_100[0x29];
  auVar14._0_4_ = afStack_100[0x28];
  auVar14._8_4_ = afStack_100[0x2a];
  auVar14._12_4_ = uStack_54;
  auVar28 = _lqc2(auVar14);
  auVar27 = _vadd(auVar27,auVar28);
  auStack_15d0 = _sqc2(auVar27);
  __ct__7FVectorFRC7FVector(auStack_1480,auStack_15d0);
  afStack_100[0x24] = auStack_1480._0_4_;
  afStack_100[0x25] = auStack_1480._4_4_;
  afStack_100[0x26] = (float)uStack_1478;
  afStack_100[0x27] = (float)uStack_1474;
  pfVar17 = afStack_1e0;
  do {
    *pfVar17 = in_zero_lo;
    pfVar17[1] = in_zero_hi;
    pfVar17[2] = in_zero_udw;
    pfVar17[3] = in_register_0000000c;
    pfVar17 = pfVar17 + 4;
  } while (pfVar17 != (float *)auStack_140);
  RotTransVector(afStack_1e0,afStack_100,auStack_40,10);
  for (iVar22 = 0; iVar22 < 10; iVar22 = iVar22 + 1) {
    auVar27 = _lqc2(*(undefined1 (*) [16])(*(int *)(iGpffff86b4 + 0x4324) + 0x30));
    auVar28 = _lqc2(*(undefined1 (*) [16])(afStack_1e0 + iVar22 * 4));
    auVar27 = _vsub(auVar27,auVar28);
    auStack_15e0 = _sqc2(auVar27);
    __ct__7FVectorFRC7FVector(auStack_14b0,auStack_15e0);
    afStack_100[0] = auStack_14b0._0_4_;
    afStack_100[1] = auStack_14b0._4_4_;
    afStack_100[2] = (float)uStack_14a8;
    afStack_100[3] = (float)uStack_14a4;
    Normalize__7FVectorFv(afStack_100);
    __amu__7FVectorFf(0x3f000000,afStack_100);
    auVar6._4_4_ = afStack_100[1];
    auVar6._0_4_ = afStack_100[0];
    auVar6._8_4_ = afStack_100[2];
    auVar6._12_4_ = afStack_100[3];
    auVar28 = _lqc2(auVar6);
    auVar27 = _lqc2(*(undefined1 (*) [16])(afStack_1e0 + iVar22 * 4));
    auVar27 = _vadd(auVar27,auVar28);
    auVar27 = _sqc2(auVar27);
    *(undefined1 (*) [16])(afStack_1e0 + iVar22 * 4) = auVar27;
  }
  GetViewScreenMatrix__9GsxCameraFv(auStack_14f0,iGpffff8598);
  for (iVar22 = 0; iVar22 < 4; iVar22 = iVar22 + 1) {
    aiStack_ac0[iVar22 * 4 + 0x228] = *(int *)(auStack_140 + iVar22 * 0x10);
    aiStack_ac0[iVar22 * 4 + 0x229] = *(int *)(auStack_140 + iVar22 * 0x10 + 4);
    aiStack_ac0[iVar22 * 4 + 0x22a] = *(int *)(auStack_140 + iVar22 * 0x10 + 8);
    aiStack_ac0[iVar22 * 4 + 0x22b] = *(int *)(auStack_140 + iVar22 * 0x10 + 0xc);
  }
  sceVu0RotTransPersN(aiStack_ac0,aiStack_ac0 + 0x228,afStack_1e0,10,0);
  uStack_1500 = 0xbf800000;
  uStack_14fc = 0xbf800000;
  uStack_14f8 = 0;
  uStack_14f4 = 0x3f800000;
  afStack_100[0] = -1.0;
  afStack_100[1] = -1.0;
  afStack_100[2] = 0.0;
  afStack_100[3] = 1.0;
  uStack_1510 = 0xbf800000;
  uStack_150c = 0x3f800000;
  uStack_1508 = 0;
  uStack_1504 = 0x3f800000;
  afStack_100[4] = -1.0;
  afStack_100[5] = 1.0;
  afStack_100[6] = 0.0;
  afStack_100[7] = 1.0;
  uStack_1520 = 0x3f800000;
  uStack_151c = 0xbf800000;
  uStack_1518 = 0;
  uStack_1514 = 0x3f800000;
  afStack_100[8] = 1.0;
  afStack_100[9] = -1.0;
  afStack_100[10] = 0.0;
  afStack_100[0xb] = 1.0;
  uStack_1530 = 0x3f800000;
  uStack_152c = 0x3f800000;
  uStack_1528 = 0;
  uStack_1524 = 0x3f800000;
  afStack_100[0xc] = 1.0;
  afStack_100[0xd] = 1.0;
  afStack_100[0xe] = 0.0;
  afStack_100[0xf] = 1.0;
  auStack_140 = *(undefined1 (*) [16])(iGpffff8598 + 0x240);
  auStack_130 = *(undefined1 (*) [16])(iGpffff8598 + 0x250);
  auStack_120 = *(undefined1 (*) [16])(iGpffff8598 + 0x260);
  auStack_110._0_12_ = ZEXT812(0);
  auStack_110._12_4_ = 0x3f800000;
  RotTransVector(afStack_1e0,afStack_100,auStack_140,4);
  for (iVar22 = 0; iVar22 < 0x20; iVar22 = iVar22 + 1) {
    for (iVar24 = 0; iVar24 < 4; iVar24 = iVar24 + 1) {
      afStack_12c0[(iVar24 + iVar22 * 4) * 4] =
           *(float *)(param_1 + iVar22 * 0x10 + 0x200) +
           *(float *)(param_1 + iVar22 * 4 + 0x400) * afStack_1e0[iVar24 * 4];
      afStack_12c0[(iVar24 + iVar22 * 4) * 4 + 1] =
           *(float *)(param_1 + iVar22 * 0x10 + 0x204) +
           *(float *)(param_1 + iVar22 * 4 + 0x400) * afStack_1e0[iVar24 * 4 + 1];
      afStack_12c0[(iVar24 + iVar22 * 4) * 4 + 2] =
           *(float *)(param_1 + iVar22 * 0x10 + 0x208) +
           *(float *)(param_1 + iVar22 * 4 + 0x400) * afStack_1e0[iVar24 * 4 + 2];
      afStack_12c0[(iVar24 + iVar22 * 4) * 4 + 3] = 1.0;
    }
  }
  sceVu0RotTransPersN(aiStack_ac0 + 0x28,aiStack_ac0 + 0x228,afStack_12c0,0x80,0);
  bVar5 = true;
  bVar4 = false;
  iVar22 = 0;
  for (iVar24 = 0; iVar24 < 0x8a; iVar24 = iVar24 + 1) {
    if (iVar24 < 10) {
      if ((((aiStack_ac0[iVar24 * 4] < 0) || (0x10000 < aiStack_ac0[iVar24 * 4])) ||
          (aiStack_ac0[iVar24 * 4 + 1] < 0)) ||
         ((0x10000 < aiStack_ac0[iVar24 * 4 + 1] || (aiStack_ac0[iVar24 * 4 + 2] < 0)))) {
        bVar4 = true;
      }
      aiStack_ac0[iVar24 * 4 + 2] = (int)((float)aiStack_ac0[iVar24 * 4 + 2] / 16.0);
      iVar22 = iVar22 + aiStack_ac0[iVar24 * 4 + 2];
    }
    else {
      uVar19 = iVar24 - 10U & 3;
      if (((int)(iVar24 - 10U) < 0) && (uVar19 != 0)) {
        uVar19 = uVar19 - 4;
      }
      if (uVar19 == 0) {
        iVar25 = iVar24 + -10;
        if (iVar25 < 0) {
          iVar25 = iVar24 + -7;
        }
        *(undefined2 *)(param_1 + (iVar25 >> 2) * 2 + 0x13c) = 0;
      }
      if ((((aiStack_ac0[iVar24 * 4] < 0) || (0x10000 < aiStack_ac0[iVar24 * 4])) ||
          (aiStack_ac0[iVar24 * 4 + 1] < 0)) ||
         ((0x10000 < aiStack_ac0[iVar24 * 4 + 1] || (aiStack_ac0[iVar24 * 4 + 2] < 0)))) {
        iVar25 = iVar24 + -10;
        if (iVar25 < 0) {
          iVar25 = iVar24 + -7;
        }
        *(undefined2 *)(param_1 + (iVar25 >> 2) * 2 + 0x13c) = 1;
      }
      aiStack_ac0[iVar24 * 4 + 2] = (int)((float)aiStack_ac0[iVar24 * 4 + 2] / 16.0);
      uVar19 = iVar24 - 10U & 3;
      if (((int)(iVar24 - 10U) < 0) && (uVar19 != 0)) {
        uVar19 = uVar19 - 4;
      }
      if (uVar19 == 3) {
        iVar25 = iVar24 + -10;
        if (iVar25 < 0) {
          iVar25 = iVar24 + -7;
        }
        if (*(short *)(param_1 + (iVar25 >> 2) * 2 + 0x13c) == 0) {
          bVar5 = false;
        }
      }
    }
  }
  if (!bVar4) {
    bVar5 = false;
  }
  *(int *)(param_1 + 0x50) = iVar22 / 10;
  bVar1 = (*(byte *)(param_1 + 0x40) & 1) == 0;
  uVar19 = (uint)bVar1;
  if (*(int *)(param_1 + uVar19 * 4 + 0x18) == 0) {
    uVar15 = __nwa__FUi(0xbc0);
    *(undefined4 *)(param_1 + uVar19 * 4 + 0x18) = uVar15;
    iVar22 = *(int *)(param_1 + uVar19 * 4 + 0x18);
    *(undefined4 *)(iVar22 + 0x10) = 0x10000014;
    *(undefined4 *)(iVar22 + 0x14) = 0;
    *(undefined4 *)(iVar22 + 0x18) = 0;
    *(undefined4 *)(iVar22 + 0x1c) = 0x50000014;
    *(undefined8 *)(iVar22 + 0x20) = 0x6000000000000001;
    *(undefined8 *)(iVar22 + 0x28) = 0xe6e8ee;
    *(undefined8 *)(iVar22 + 0x30) = 1;
    *(undefined8 *)(iVar22 + 0x38) = 0x3f;
    *(undefined8 *)(iVar22 + 0x40) = 0x60;
    *(undefined8 *)(iVar22 + 0x48) = 0x14;
    *(undefined8 *)(iVar22 + 0x50) = 5;
    *(undefined8 *)(iVar22 + 0x58) = 0;
    *(undefined8 *)(iVar22 + 0x60) = 0x53001;
    *(undefined8 *)(iVar22 + 0x68) = 0x47;
    uVar16 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x42ec),1);
    *(undefined8 *)(iVar22 + 0x70) = uVar16;
    *(undefined8 *)(iVar22 + 0x78) = 0;
    *(undefined8 *)(iVar22 + 0x80) = 0x48;
    *(undefined8 *)(iVar22 + 0x88) = 0x42;
    *(undefined8 *)(iVar22 + 0x90) = 0x6400000000000001;
    *(undefined8 *)(iVar22 + 0x98) = 0xc3c310;
    *(undefined8 *)(iVar22 + 0xa0) = 0x154;
    *(undefined8 *)(iVar22 + 0xb0) = 0;
    *(long *)(iVar22 + 0xc0) =
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42ec) + 4) << 4) << 0x10;
    *(undefined8 *)(iVar22 + 0xd0) = 0x2400000000008008;
    *(undefined8 *)(iVar22 + 0xd8) = 0x43;
    *(long *)(iVar22 + 0xe0) =
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42ec) + 2) << 3);
    *(long *)(iVar22 + 0xf0) =
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42ec) + 2) << 3) |
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42ec) + 4) << 4) << 0x10;
    *(long *)(iVar22 + 0x100) =
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42ec) + 2) << 3);
    *(long *)(iVar22 + 0x110) =
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42ec) + 2) << 3) |
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42ec) + 4) << 4) << 0x10;
    *(long *)(iVar22 + 0x120) =
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42ec) + 2) << 3);
    *(long *)(iVar22 + 0x130) =
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42ec) + 2) << 3) |
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42ec) + 4) << 4) << 0x10;
    *(long *)(iVar22 + 0x140) =
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42ec) + 2) << 4);
    *(long *)(iVar22 + 0x150) =
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42ec) + 2) << 4) |
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42ec) + 4) << 4) << 0x10;
    *(undefined4 *)(iVar22 + 0x160) = 0x50000000;
    *(undefined4 *)(iVar22 + 0x164) =
         *(undefined4 *)
          (*(int *)(iGpffff86b4 + 0x42f0) +
           (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f0) + 10) * 4 + 0xc);
    *(undefined4 *)(iVar22 + 0x168) = 0;
    *(undefined4 *)(iVar22 + 0x16c) = 0;
    *(undefined4 *)(iVar22 + 0x170) = 0x600000a4;
    *(undefined4 *)(iVar22 + 0x174) = 0;
    *(undefined4 *)(iVar22 + 0x178) = 0;
    *(undefined4 *)(iVar22 + 0x17c) = 0x500000a4;
    *(undefined8 *)(iVar22 + 0x180) = 0x2000000000000001;
    *(undefined8 *)(iVar22 + 0x188) = 0x6e;
    *(undefined8 *)(iVar22 + 400) = 1;
    *(undefined8 *)(iVar22 + 0x198) = 0x3f;
    uVar16 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x42f0),1);
    *(undefined8 *)(iVar22 + 0x1a0) = uVar16;
    *(undefined8 *)(iVar22 + 0x1a8) = 0;
    auVar18._8_8_ = in_v1_udw;
    auVar18._0_8_ = 0xa400000000008020;
    auVar3._4_4_ = in_zero_hi;
    auVar3._0_4_ = in_zero_lo;
    auVar3._8_4_ = in_zero_udw;
    auVar3._12_4_ = in_register_0000000c;
    auVar27 = _pcpyld(auVar3,auVar18);
    *(long *)(iVar22 + 0x1b0) = auVar27._0_8_;
    *(undefined8 *)(iVar22 + 0x1b8) = 0x4343c3c310;
    for (iVar24 = 0; iVar24 < 0x20; iVar24 = iVar24 + 1) {
      *(undefined8 *)(iVar22 + (iVar24 * 5 + 0x1c) * 0x10) = 0x154;
      *(long *)(iVar22 + (iVar24 * 5 + 0x1d) * 0x10) =
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f0) + 2) << 2) |
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f0) + 4) << 2) << 0x10;
      *(long *)(iVar22 + (iVar24 * 5 + 0x1e) * 0x10) =
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f0) + 2) << 2) |
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f0) + 4) * 0xc) << 0x10;
      *(long *)(iVar22 + (iVar24 * 5 + 0x1f) * 0x10) =
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f0) + 4) << 2) << 0x10 |
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f0) + 2) * 0xc);
      *(long *)(iVar22 + (iVar24 * 5 + 0x20) * 0x10) =
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f0) + 2) * 0xc) |
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f0) + 4) * 0xc) << 0x10;
    }
  }
  puVar2 = *(undefined4 **)(param_1 + uVar19 * 4 + 0x18);
  if (bVar5) {
    *puVar2 = 0x60000000;
    puVar2[1] = 0;
    puVar2[2] = 0;
    puVar2[3] = 0;
    *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfe | bVar1;
  }
  else {
    *puVar2 = 0x50000000;
    puVar2[1] = *(undefined4 *)
                 (*(int *)(iGpffff86b4 + 0x42ec) +
                  (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42ec) + 10) * 4 + 0xc);
    puVar2[2] = 0;
    puVar2[3] = 0;
    iVar22 = (int)(*(float *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x144) +
                             0x4e4) *
                   *(float *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x144) +
                             0x4ec) * 128.0);
    fVar23 = (float)sinf(*(undefined4 *)(param_1 + 0xf8));
    fVar23 = (fVar23 + 1.0) / 2.0;
    iVar24 = (int)((float)*(byte *)(*(int *)(param_1 + 0x60) * 0xc + 0x652b64) +
                  fVar23 * (float)(int)((uint)*(byte *)(*(int *)(param_1 + 0x60) * 0xc + 0x652b68) -
                                       (uint)*(byte *)(*(int *)(param_1 + 0x60) * 0xc + 0x652b64)));
    iVar25 = (int)((float)*(byte *)(*(int *)(param_1 + 0x60) * 0xc + 0x652b65) +
                  fVar23 * (float)(int)((uint)*(byte *)(*(int *)(param_1 + 0x60) * 0xc + 0x652b69) -
                                       (uint)*(byte *)(*(int *)(param_1 + 0x60) * 0xc + 0x652b65)));
    iVar26 = (int)((float)*(byte *)(*(int *)(param_1 + 0x60) * 0xc + 0x652b66) +
                  fVar23 * (float)(int)((uint)*(byte *)(*(int *)(param_1 + 0x60) * 0xc + 0x652b6a) -
                                       (uint)*(byte *)(*(int *)(param_1 + 0x60) * 0xc + 0x652b66)));
    *(ulong *)(puVar2 + 0x2a) =
         (long)iVar22 << 0x18 | (long)iVar26 << 0x10 | (long)iVar24 | (long)iVar25 << 8 |
         0x100000000;
    if (bVar4) {
      *(undefined8 *)(puVar2 + 0x2e) = 0x71006f00;
      *(undefined8 *)(puVar2 + 0x32) = 0x71006f00;
      *(undefined8 *)(puVar2 + 0x3a) = 0x71006f00;
      *(undefined8 *)(puVar2 + 0x3e) = 0x71006f00;
      *(undefined8 *)(puVar2 + 0x42) = 0x71006f00;
      *(undefined8 *)(puVar2 + 0x46) = 0x71006f00;
      *(undefined8 *)(puVar2 + 0x4a) = 0x71006f00;
      *(undefined8 *)(puVar2 + 0x4e) = 0x71006f00;
      *(undefined8 *)(puVar2 + 0x52) = 0x71006f00;
      *(undefined8 *)(puVar2 + 0x56) = 0x71006f00;
    }
    else {
      *(long *)(puVar2 + 0x2e) =
           (long)aiStack_ac0[2] << 0x20 | (long)aiStack_ac0[0] | (long)aiStack_ac0[1] << 0x10;
      *(long *)(puVar2 + 0x32) =
           (long)aiStack_ac0[6] << 0x20 | (long)aiStack_ac0[4] | (long)aiStack_ac0[5] << 0x10;
      *(long *)(puVar2 + 0x3a) =
           (long)aiStack_ac0[10] << 0x20 | (long)aiStack_ac0[8] | (long)aiStack_ac0[9] << 0x10;
      *(long *)(puVar2 + 0x3e) =
           (long)aiStack_ac0[0xe] << 0x20 | (long)aiStack_ac0[0xc] | (long)aiStack_ac0[0xd] << 0x10;
      *(long *)(puVar2 + 0x42) =
           (long)aiStack_ac0[0x12] << 0x20 |
           (long)aiStack_ac0[0x10] | (long)aiStack_ac0[0x11] << 0x10;
      *(long *)(puVar2 + 0x46) =
           (long)aiStack_ac0[0x16] << 0x20 |
           (long)aiStack_ac0[0x14] | (long)aiStack_ac0[0x15] << 0x10;
      *(long *)(puVar2 + 0x4a) =
           (long)aiStack_ac0[0x1a] << 0x20 |
           (long)aiStack_ac0[0x18] | (long)aiStack_ac0[0x19] << 0x10;
      *(long *)(puVar2 + 0x4e) =
           (long)aiStack_ac0[0x1e] << 0x20 |
           (long)aiStack_ac0[0x1c] | (long)aiStack_ac0[0x1d] << 0x10;
      *(long *)(puVar2 + 0x52) =
           (long)aiStack_ac0[0x22] << 0x20 |
           (long)aiStack_ac0[0x20] | (long)aiStack_ac0[0x21] << 0x10;
      *(long *)(puVar2 + 0x56) =
           (long)aiStack_ac0[0x26] << 0x20 |
           (long)aiStack_ac0[0x24] | (long)aiStack_ac0[0x25] << 0x10;
    }
    for (iVar21 = 0; iVar21 < 0x20; iVar21 = iVar21 + 1) {
      if ((*(short *)(param_1 + iVar21 * 2 + 0xfc) == 0) ||
         (*(short *)(param_1 + iVar21 * 2 + 0x13c) != 0)) {
        *(undefined8 *)(puVar2 + (iVar21 * 5 + 0x1d) * 4 + 2) = 0x71006f00;
        *(undefined8 *)(puVar2 + (iVar21 * 5 + 0x1e) * 4 + 2) = 0x71006f00;
        *(undefined8 *)(puVar2 + (iVar21 * 5 + 0x1f) * 4 + 2) = 0x71006f00;
        *(undefined8 *)(puVar2 + (iVar21 * 5 + 0x20) * 4 + 2) = 0x71006f00;
      }
      else {
        *(ulong *)(puVar2 + (iVar21 * 5 + 0x1c) * 4 + 2) =
             (long)(int)(((float)iVar22 * *(float *)(param_1 + iVar21 * 4 + 0x480)) / 128.0) << 0x18
             | (long)iVar26 << 0x10 | (long)iVar24 | (long)iVar25 << 8 | 0x100000000;
        *(long *)(puVar2 + (iVar21 * 5 + 0x1d) * 4 + 2) =
             (long)aiStack_ac0[(iVar21 * 4 + 10) * 4 + 2] << 0x20 |
             (long)aiStack_ac0[(iVar21 * 4 + 10) * 4] |
             (long)aiStack_ac0[(iVar21 * 4 + 10) * 4 + 1] << 0x10;
        *(long *)(puVar2 + (iVar21 * 5 + 0x1e) * 4 + 2) =
             (long)aiStack_ac0[(iVar21 * 4 + 0xb) * 4 + 2] << 0x20 |
             (long)aiStack_ac0[(iVar21 * 4 + 0xb) * 4] |
             (long)aiStack_ac0[(iVar21 * 4 + 0xb) * 4 + 1] << 0x10;
        *(long *)(puVar2 + (iVar21 * 5 + 0x1f) * 4 + 2) =
             (long)aiStack_ac0[(iVar21 * 4 + 0xc) * 4 + 2] << 0x20 |
             (long)aiStack_ac0[(iVar21 * 4 + 0xc) * 4] |
             (long)aiStack_ac0[(iVar21 * 4 + 0xc) * 4 + 1] << 0x10;
        *(long *)(puVar2 + (iVar21 * 5 + 0x20) * 4 + 2) =
             (long)aiStack_ac0[(iVar21 * 4 + 0xd) * 4 + 2] << 0x20 |
             (long)aiStack_ac0[(iVar21 * 4 + 0xd) * 4] |
             (long)aiStack_ac0[(iVar21 * 4 + 0xd) * 4 + 1] << 0x10;
      }
    }
    *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfe | bVar1;
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054ae20  EndSet__19ScytheAddAttribute1Fv
 * C++: ScytheAddAttribute1::EndSet()
 * size: 0x10 bytes
 * --------------------------------------------------------------------------- */
void EndSet__19ScytheAddAttribute1Fv(void)

{
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b850  @24@__dt__19ScytheAddAttribute1Fv
 * C++: @24@__dt__19ScytheAddAttribute1Fv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int * _24___dt__19ScytheAddAttribute1Fv(int *param_1,short param_2)

{
  int *piVar1;
  
  piVar1 = param_1 + -6;
  if (piVar1 != (int *)0x0) {
    param_1[-1] = 0x409c50;
    param_1[4] = 0x409c60;
    param_1[7] = 0x409c70;
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
 * JP: 0x0054b860  @44@__dt__19ScytheAddAttribute1Fv
 * C++: @44@__dt__19ScytheAddAttribute1Fv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int _44___dt__19ScytheAddAttribute1Fv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x2c;
  if (iVar1 != 0) {
    *(undefined4 *)(param_1 + -0x18) = 0x409c50;
    *(undefined4 *)(param_1 + -4) = 0x409c60;
    *(undefined4 *)(param_1 + 8) = 0x409c70;
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

