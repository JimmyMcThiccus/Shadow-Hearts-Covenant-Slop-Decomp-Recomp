/* decomp/H/Bullet2.c — cleaned Ghidra output (SH2JP_BATTLE.BIN, JP Furokuban, base 0x00430a00).
 * 8 function(s). Types: see types.h. Names/gp globals resolved from symbols/SLPM_602.19.syms. */
#include "types.h"

/* ---------------------------------------------------------------------------
 * JP: 0x0053d5e0  __ct__7Bullet2FiiissfiiiiUsUsii
 * C++: Bullet2::__ct(int, int, int, short, short, float, int, int, int, int, ushort, ushort, int, int)
 * size: 0x1828 bytes
 * --------------------------------------------------------------------------- */
undefined8
__ct__7Bullet2FiiissfiiiiUsUsii
          (undefined4 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
          undefined4 param_5,undefined2 param_6,undefined2 param_7,undefined4 param_8,
          undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined2 param_12,
          undefined2 param_13,undefined4 param_14,undefined4 param_15)

{
  undefined1 auVar1 [16];
  undefined1 auVar2 [16];
  undefined1 auVar3 [16];
  undefined1 auVar4 [16];
  undefined1 auVar5 [16];
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  undefined1 auVar8 [16];
  undefined1 auVar9 [16];
  undefined1 auVar10 [16];
  undefined1 auVar11 [16];
  undefined1 auVar12 [16];
  undefined1 auVar13 [16];
  undefined1 auVar14 [16];
  undefined1 auVar15 [16];
  undefined1 auVar16 [16];
  undefined1 auVar17 [16];
  undefined1 auVar18 [16];
  undefined1 auVar19 [16];
  undefined1 auVar20 [16];
  undefined1 auVar21 [16];
  undefined1 auVar22 [16];
  undefined1 auVar23 [16];
  undefined1 auVar24 [16];
  undefined1 auVar25 [16];
  undefined1 auVar26 [16];
  undefined1 auVar27 [16];
  undefined1 auVar28 [16];
  undefined1 auVar29 [16];
  float in_zero_lo;
  float in_zero_hi;
  float in_zero_udw;
  float in_register_0000000c;
  int iVar30;
  byte *pbVar31;
  undefined8 uVar32;
  float *pfVar33;
  undefined1 (*pauVar34) [16];
  int iVar35;
  float fVar36;
  undefined1 in_vf0 [16];
  undefined1 auVar37 [16];
  undefined1 auVar38 [16];
  undefined1 auVar39 [16];
  undefined1 auStack_500 [16];
  undefined1 auStack_4f0 [16];
  undefined1 auStack_4e0 [16];
  undefined1 auStack_4d0 [16];
  undefined1 auStack_4c0 [16];
  undefined1 auStack_4b0 [16];
  undefined1 auStack_4a0 [16];
  undefined1 auStack_490 [16];
  undefined1 auStack_480 [16];
  undefined1 auStack_470 [16];
  undefined1 auStack_460 [16];
  undefined1 auStack_450 [16];
  undefined1 auStack_440 [16];
  undefined1 auStack_430 [16];
  undefined1 auStack_420 [16];
  undefined1 auStack_410 [16];
  undefined1 auStack_400 [16];
  undefined1 auStack_3f0 [16];
  undefined1 auStack_3e0 [16];
  undefined1 auStack_3d0 [16];
  undefined1 auStack_3c0 [16];
  undefined1 auStack_3b0 [16];
  undefined1 auStack_3a0 [16];
  undefined1 auStack_390 [16];
  undefined1 auStack_380 [16];
  undefined1 auStack_370 [16];
  undefined1 auStack_360 [16];
  undefined1 auStack_350 [8];
  float fStack_348;
  float fStack_344;
  undefined1 auStack_340 [16];
  undefined1 auStack_330 [8];
  float fStack_328;
  float fStack_324;
  undefined1 auStack_320 [16];
  undefined1 auStack_310 [16];
  undefined1 auStack_300 [16];
  undefined1 auStack_2f0 [16];
  undefined1 auStack_2e0 [16];
  undefined1 auStack_2d0 [16];
  undefined8 uStack_2c0;
  undefined4 uStack_2b8;
  undefined4 uStack_2b4;
  undefined4 uStack_2b0;
  undefined4 uStack_2ac;
  undefined4 uStack_2a8;
  undefined4 uStack_2a4;
  undefined1 auStack_2a0 [8];
  float fStack_298;
  float fStack_294;
  float fStack_290;
  float fStack_28c;
  float fStack_288;
  undefined4 uStack_284;
  undefined1 auStack_280 [16];
  undefined1 auStack_270 [16];
  undefined1 auStack_260 [16];
  undefined1 auStack_250 [16];
  undefined1 auStack_240 [16];
  undefined1 auStack_230 [16];
  undefined1 auStack_220 [8];
  float fStack_218;
  float fStack_214;
  undefined4 uStack_210;
  undefined4 uStack_20c;
  undefined4 uStack_208;
  undefined4 uStack_204;
  undefined1 auStack_200 [8];
  float fStack_1f8;
  float fStack_1f4;
  float fStack_1f0;
  float fStack_1ec;
  float fStack_1e8;
  undefined4 uStack_1e4;
  undefined1 auStack_1e0 [16];
  undefined1 auStack_1d0 [16];
  undefined1 auStack_1c0 [16];
  undefined1 auStack_1b0 [16];
  undefined1 auStack_1a0 [16];
  undefined1 auStack_190 [16];
  undefined8 uStack_180;
  undefined4 uStack_178;
  undefined4 uStack_174;
  undefined4 uStack_170;
  undefined4 uStack_16c;
  undefined4 uStack_168;
  undefined4 uStack_164;
  undefined1 auStack_160 [8];
  float fStack_158;
  float fStack_154;
  float fStack_150;
  float fStack_14c;
  float fStack_148;
  undefined4 uStack_144;
  undefined1 auStack_140 [8];
  float fStack_138;
  float fStack_134;
  float fStack_130;
  float fStack_12c;
  float fStack_128;
  float fStack_124;
  float fStack_120;
  float fStack_11c;
  float fStack_118;
  float fStack_114;
  float fStack_c0;
  float fStack_bc;
  float fStack_b8;
  float fStack_b4;
  float fStack_b0;
  float fStack_ac;
  float fStack_a8;
  float fStack_a4;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  float fStack_94;
  float fStack_90;
  float fStack_8c;
  float fStack_88;
  float fStack_84;
  float fStack_80;
  float fStack_7c;
  float fStack_78;
  float fStack_74;
  float fStack_70;
  float fStack_6c;
  float fStack_68;
  float fStack_64;
  float fStack_60;
  float fStack_5c;
  float fStack_58;
  float fStack_54;
  float fStack_50;
  float fStack_4c;
  float fStack_48;
  float fStack_44;
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [16];
  undefined1 auStack_20 [16];
  undefined1 auStack_10 [16];
  
  __ct__6BtlEffFii(param_2,param_3,param_4);
  iVar35 = (int)param_2;
  *(undefined4 *)(iVar35 + 0x14) = 0x409a70;
  *(undefined4 *)(iVar35 + 0x28) = 0x409a80;
  *(undefined4 *)(iVar35 + 0x34) = 0x409a90;
  pfVar33 = (float *)(iVar35 + 0x70);
  do {
    *pfVar33 = in_zero_lo;
    pfVar33[1] = in_zero_hi;
    pfVar33[2] = in_zero_udw;
    pfVar33[3] = in_register_0000000c;
    pfVar33 = pfVar33 + 4;
  } while (pfVar33 != (float *)(iVar35 + 0x90));
  *(float *)(iVar35 + 0x90) = in_zero_lo;
  *(float *)(iVar35 + 0x94) = in_zero_hi;
  *(float *)(iVar35 + 0x98) = in_zero_udw;
  *(float *)(iVar35 + 0x9c) = in_register_0000000c;
  pfVar33 = (float *)(iVar35 + 0x1c0);
  do {
    *pfVar33 = in_zero_lo;
    pfVar33[1] = in_zero_hi;
    pfVar33[2] = in_zero_udw;
    pfVar33[3] = in_register_0000000c;
    pfVar33 = pfVar33 + 4;
  } while (pfVar33 != (float *)(iVar35 + 0x3c0));
  *(undefined4 *)(iVar35 + 0x40) = 0;
  *(int *)(iVar35 + 0x44) = (int)param_3;
  *(int *)(iVar35 + 0x48) = (int)param_4;
  *(undefined4 *)(iVar35 + 0x4c) = 10;
  *(undefined4 *)(iVar35 + 0x5c) = param_5;
  *(undefined2 *)(iVar35 + 0x60) = param_6;
  *(undefined2 *)(iVar35 + 0x62) = param_7;
  *(undefined4 *)(iVar35 + 100) = param_1;
  *(undefined4 *)(iVar35 + 0xa0) = param_9;
  *(undefined4 *)(iVar35 + 0xa4) = param_10;
  *(undefined4 *)(iVar35 + 0xa8) = param_8;
  *(undefined4 *)(iVar35 + 0xac) = param_11;
  *(undefined2 *)(iVar35 + 0xb0) = param_12;
  *(undefined2 *)(iVar35 + 0xb2) = param_13;
  *(undefined4 *)(iVar35 + 0xb4) = param_14;
  *(undefined4 *)(iVar35 + 0xb8) = param_15;
  *(undefined4 *)(iVar35 + 0x1c) = 0;
  *(undefined4 *)(iVar35 + 0x18) = 0;
  *(undefined4 *)(iVar35 + 0x4c0) = 0;
  for (iVar30 = 0; iVar30 < 0x20; iVar30 = iVar30 + 1) {
    *(undefined2 *)(iVar35 + iVar30 * 2 + 0xbc) = 0;
  }
  iVar30 = GetRegDat__9RegDatApiFiii(0x3a,*(undefined4 *)
                                 (iGpffff86b4 + *(int *)(iVar35 + 0x48) * 0x4f0 + 0x55c),
                           0xffffffffffffffff);
  iVar30 = *(int *)(*(short *)(iVar30 + 0x14) * 4 + 0x651b70);
  auVar37 = _vmr32(in_vf0);
  auVar38 = _vmr32(auVar37);
  auVar39 = _vmr32(auVar38);
  _sqc2(in_vf0);
  _sqc2(auVar37);
  _sqc2(auVar38);
  _sqc2(auVar39);
  auStack_140._4_4_ = in_zero_hi;
  auStack_140._0_4_ = in_zero_lo;
  fStack_138 = in_zero_udw;
  fStack_134 = in_register_0000000c;
  fStack_130 = in_zero_lo;
  fStack_12c = in_zero_hi;
  fStack_128 = in_zero_udw;
  fStack_124 = in_register_0000000c;
  fStack_c0 = in_zero_lo;
  fStack_bc = in_zero_hi;
  fStack_b8 = in_zero_udw;
  fStack_b4 = in_register_0000000c;
  fStack_b0 = in_zero_lo;
  fStack_ac = in_zero_hi;
  fStack_a8 = in_zero_udw;
  fStack_a4 = in_register_0000000c;
  fStack_a0 = in_zero_lo;
  fStack_9c = in_zero_hi;
  fStack_98 = in_zero_udw;
  fStack_94 = in_register_0000000c;
  fStack_90 = in_zero_lo;
  fStack_8c = in_zero_hi;
  fStack_88 = in_zero_udw;
  fStack_84 = in_register_0000000c;
  fStack_80 = in_zero_lo;
  fStack_7c = in_zero_hi;
  fStack_78 = in_zero_udw;
  fStack_74 = in_register_0000000c;
  fStack_70 = in_zero_lo;
  fStack_6c = in_zero_hi;
  fStack_68 = in_zero_udw;
  fStack_64 = in_register_0000000c;
  fStack_60 = in_zero_lo;
  fStack_5c = in_zero_hi;
  fStack_58 = in_zero_udw;
  fStack_54 = in_register_0000000c;
  fStack_50 = in_zero_lo;
  fStack_4c = in_zero_hi;
  fStack_48 = in_zero_udw;
  fStack_44 = in_register_0000000c;
  if (*(short *)(iVar35 + 0x62) == 0) {
    if (*(short *)(iVar30 + 2) == 2) {
      pbVar31 = (byte *)(*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar35 + 0x48) * 0x4f0 +
                                                   0x144) + 0x530) + 0xe4) +
                        *(short *)(iVar30 + *(short *)(iVar35 + 0x60) * 0x20 + 4) * 0x110);
      pauVar34 = (undefined1 (*) [16])
                 (*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar35 + 0x48) * 0x4f0 + 0x144)
                                   + 0x530) + 0x30) + (uint)*pbVar31 * 0x1f0 +
                 (bGpffff8340 & 1) * 0x40);
      auStack_40 = *pauVar34;
      auStack_30 = pauVar34[1];
      auStack_20 = pauVar34[2];
      auStack_10 = pauVar34[3];
    }
    else if (*(short *)(iVar30 + 2) == 1) {
      pbVar31 = (byte *)(*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar35 + 0x48) * 0x4f0 +
                                                   0x144) + 0x52c) + 0xe4) +
                        *(short *)(iVar30 + *(short *)(iVar35 + 0x60) * 0x20 + 4) * 0x110);
      pauVar34 = (undefined1 (*) [16])
                 (*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar35 + 0x48) * 0x4f0 + 0x144)
                                   + 0x52c) + 0x30) + (uint)*pbVar31 * 0x1f0 +
                 (bGpffff8340 & 1) * 0x40);
      auStack_40 = *pauVar34;
      auStack_30 = pauVar34[1];
      auStack_20 = pauVar34[2];
      auStack_10 = pauVar34[3];
    }
    else {
      pbVar31 = (byte *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar35 + 0x48) * 0x4f0 + 0x144) +
                                 0xe4) +
                        *(short *)(iVar30 + *(short *)(iVar35 + 0x60) * 0x20 + 4) * 0x110);
      pauVar34 = (undefined1 (*) [16])
                 (*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar35 + 0x48) * 0x4f0 + 0x144) + 0x30) +
                  (uint)*pbVar31 * 0x1f0 + (bGpffff8340 & 1) * 0x40);
      auStack_40 = *pauVar34;
      auStack_30 = pauVar34[1];
      auStack_20 = pauVar34[2];
      auStack_10 = pauVar34[3];
    }
    fStack_120 = in_zero_lo;
    fStack_11c = in_zero_hi;
    fStack_118 = in_zero_udw;
    fStack_114 = in_register_0000000c;
    if (((*(float *)(iVar30 + *(short *)(iVar35 + 0x60) * 0x20 + 8) == 0.0) &&
        (*(float *)(iVar30 + *(short *)(iVar35 + 0x60) * 0x20 + 0xc) == 0.0)) &&
       (*(float *)(iVar30 + *(short *)(iVar35 + 0x60) * 0x20 + 0x10) == 0.0)) {
      RotTransVector(&fStack_c0,pbVar31 + 0x10,auStack_40,8);
      auVar7._4_4_ = fStack_bc;
      auVar7._0_4_ = fStack_c0;
      auVar7._8_4_ = fStack_b8;
      auVar7._12_4_ = fStack_b4;
      auVar37 = _lqc2(auVar7);
      auVar11._4_4_ = fStack_ac;
      auVar11._0_4_ = fStack_b0;
      auVar11._8_4_ = fStack_a8;
      auVar11._12_4_ = fStack_a4;
      auVar38 = _lqc2(auVar11);
      auVar37 = _vadd(auVar37,auVar38);
      auStack_3e0 = _sqc2(auVar37);
      __ct__7FVectorFRC7FVector(auStack_1e0,auStack_3e0);
      auVar37 = _lqc2(auStack_1e0);
      auVar13._4_4_ = fStack_9c;
      auVar13._0_4_ = fStack_a0;
      auVar13._8_4_ = fStack_98;
      auVar13._12_4_ = fStack_94;
      auVar38 = _lqc2(auVar13);
      auVar37 = _vadd(auVar37,auVar38);
      auStack_3f0 = _sqc2(auVar37);
      __ct__7FVectorFRC7FVector(auStack_1d0,auStack_3f0);
      auVar37 = _lqc2(auStack_1d0);
      auVar15._4_4_ = fStack_8c;
      auVar15._0_4_ = fStack_90;
      auVar15._8_4_ = fStack_88;
      auVar15._12_4_ = fStack_84;
      auVar38 = _lqc2(auVar15);
      auVar37 = _vadd(auVar37,auVar38);
      auStack_400 = _sqc2(auVar37);
      __ct__7FVectorFRC7FVector(auStack_1c0,auStack_400);
      auVar37 = _lqc2(auStack_1c0);
      auVar18._4_4_ = fStack_7c;
      auVar18._0_4_ = fStack_80;
      auVar18._8_4_ = fStack_78;
      auVar18._12_4_ = fStack_74;
      auVar38 = _lqc2(auVar18);
      auVar37 = _vadd(auVar37,auVar38);
      auStack_410 = _sqc2(auVar37);
      __ct__7FVectorFRC7FVector(auStack_1b0,auStack_410);
      auVar37 = _lqc2(auStack_1b0);
      auVar21._4_4_ = fStack_6c;
      auVar21._0_4_ = fStack_70;
      auVar21._8_4_ = fStack_68;
      auVar21._12_4_ = fStack_64;
      auVar38 = _lqc2(auVar21);
      auVar37 = _vadd(auVar37,auVar38);
      auStack_420 = _sqc2(auVar37);
      __ct__7FVectorFRC7FVector(auStack_1a0,auStack_420);
      auVar37 = _lqc2(auStack_1a0);
      auVar24._4_4_ = fStack_5c;
      auVar24._0_4_ = fStack_60;
      auVar24._8_4_ = fStack_58;
      auVar24._12_4_ = fStack_54;
      auVar38 = _lqc2(auVar24);
      auVar37 = _vadd(auVar37,auVar38);
      auStack_430 = _sqc2(auVar37);
      __ct__7FVectorFRC7FVector(auStack_190,auStack_430);
      auVar37 = _lqc2(auStack_190);
      auVar27._4_4_ = fStack_4c;
      auVar27._0_4_ = fStack_50;
      auVar27._8_4_ = fStack_48;
      auVar27._12_4_ = fStack_44;
      auVar38 = _lqc2(auVar27);
      auVar37 = _vadd(auVar37,auVar38);
      auStack_380 = _sqc2(auVar37);
      __ct__7FVectorFRC7FVector(&uStack_180,auStack_380);
      fStack_138 = (float)uStack_178;
      auStack_140 = (undefined1  [8])uStack_180;
      fStack_134 = (float)uStack_174;
      __adv__7FVectorFf(0x41000000,auStack_140);
    }
    else {
      fStack_148 = *(float *)(iVar30 + *(short *)(iVar35 + 0x60) * 0x20 + 0x10);
      fStack_14c = *(float *)(iVar30 + *(short *)(iVar35 + 0x60) * 0x20 + 0xc);
      fStack_150 = *(float *)(iVar30 + *(short *)(iVar35 + 0x60) * 0x20 + 8);
      uStack_144 = 0x3f800000;
      fStack_b4 = 1.0;
      uStack_168 = *(undefined4 *)(iVar30 + *(short *)(iVar35 + 0x60) * 0x20 + 0x1c);
      uStack_16c = *(undefined4 *)(iVar30 + *(short *)(iVar35 + 0x60) * 0x20 + 0x18);
      uStack_170 = *(undefined4 *)(iVar30 + *(short *)(iVar35 + 0x60) * 0x20 + 0x14);
      uStack_164 = 0x3f800000;
      auVar6._4_4_ = fStack_14c;
      auVar6._0_4_ = fStack_150;
      auVar6._8_4_ = fStack_148;
      auVar6._12_4_ = 0x3f800000;
      auVar37 = _lqc2(auVar6);
      auVar3._4_4_ = uStack_16c;
      auVar3._0_4_ = uStack_170;
      auVar3._8_4_ = uStack_168;
      auVar3._12_4_ = 0x3f800000;
      auVar38 = _lqc2(auVar3);
      auVar37 = _vadd(auVar37,auVar38);
      auStack_370 = _sqc2(auVar37);
      fStack_c0 = fStack_150;
      fStack_bc = fStack_14c;
      fStack_b8 = fStack_148;
      __ct__7FVectorFRC7FVector(auStack_160,auStack_370);
      fStack_b0 = auStack_160._0_4_;
      fStack_ac = auStack_160._4_4_;
      fStack_a8 = fStack_158;
      fStack_a4 = fStack_154;
      RotTransVector(auStack_140,&fStack_c0,auStack_40,2);
    }
    if (*(short *)(iVar30 + *(short *)(iVar35 + 0x60) * 0x20 + 6) < -1) {
      if (*(short *)(iVar30 + 2) == 2) {
        pbVar31 = (byte *)(*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar35 + 0x48) * 0x4f0
                                                     + 0x144) + 0x530) + 0xe4) +
                          *(short *)(iVar30 + *(short *)(iVar35 + 0x60) * 0x20 + 6) * -0x110);
        pauVar34 = (undefined1 (*) [16])
                   (*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar35 + 0x48) * 0x4f0 + 0x144
                                              ) + 0x530) + 0x30) + (uint)*pbVar31 * 0x1f0 +
                   (bGpffff8340 & 1) * 0x40);
        auStack_40 = *pauVar34;
        auStack_30 = pauVar34[1];
        auStack_20 = pauVar34[2];
        auStack_10 = pauVar34[3];
      }
      else if (*(short *)(iVar30 + 2) == 1) {
        pbVar31 = (byte *)(*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar35 + 0x48) * 0x4f0
                                                     + 0x144) + 0x52c) + 0xe4) +
                          *(short *)(iVar30 + *(short *)(iVar35 + 0x60) * 0x20 + 6) * -0x110);
        pauVar34 = (undefined1 (*) [16])
                   (*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar35 + 0x48) * 0x4f0 + 0x144
                                              ) + 0x52c) + 0x30) + (uint)*pbVar31 * 0x1f0 +
                   (bGpffff8340 & 1) * 0x40);
        auStack_40 = *pauVar34;
        auStack_30 = pauVar34[1];
        auStack_20 = pauVar34[2];
        auStack_10 = pauVar34[3];
      }
      else {
        pbVar31 = (byte *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar35 + 0x48) * 0x4f0 + 0x144)
                                   + 0xe4) +
                          *(short *)(iVar30 + *(short *)(iVar35 + 0x60) * 0x20 + 6) * -0x110);
        pauVar34 = (undefined1 (*) [16])
                   (*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar35 + 0x48) * 0x4f0 + 0x144) + 0x30)
                    + (uint)*pbVar31 * 0x1f0 + (bGpffff8340 & 1) * 0x40);
        auStack_40 = *pauVar34;
        auStack_30 = pauVar34[1];
        auStack_20 = pauVar34[2];
        auStack_10 = pauVar34[3];
      }
      if (((*(float *)(iVar30 + *(short *)(iVar35 + 0x60) * 0x20 + 8) == 0.0) &&
          (*(float *)(iVar30 + *(short *)(iVar35 + 0x60) * 0x20 + 0xc) == 0.0)) &&
         (*(float *)(iVar30 + *(short *)(iVar35 + 0x60) * 0x20 + 0x10) == 0.0)) {
        RotTransVector(&fStack_c0,pbVar31 + 0x10,auStack_40,8);
        auVar9._4_4_ = fStack_bc;
        auVar9._0_4_ = fStack_c0;
        auVar9._8_4_ = fStack_b8;
        auVar9._12_4_ = fStack_b4;
        auVar37 = _lqc2(auVar9);
        auVar12._4_4_ = fStack_ac;
        auVar12._0_4_ = fStack_b0;
        auVar12._8_4_ = fStack_a8;
        auVar12._12_4_ = fStack_a4;
        auVar38 = _lqc2(auVar12);
        auVar37 = _vadd(auVar37,auVar38);
        auStack_440 = _sqc2(auVar37);
        __ct__7FVectorFRC7FVector(auStack_280,auStack_440);
        auVar37 = _lqc2(auStack_280);
        auVar14._4_4_ = fStack_9c;
        auVar14._0_4_ = fStack_a0;
        auVar14._8_4_ = fStack_98;
        auVar14._12_4_ = fStack_94;
        auVar38 = _lqc2(auVar14);
        auVar37 = _vadd(auVar37,auVar38);
        auStack_450 = _sqc2(auVar37);
        __ct__7FVectorFRC7FVector(auStack_270,auStack_450);
        auVar37 = _lqc2(auStack_270);
        auVar16._4_4_ = fStack_8c;
        auVar16._0_4_ = fStack_90;
        auVar16._8_4_ = fStack_88;
        auVar16._12_4_ = fStack_84;
        auVar38 = _lqc2(auVar16);
        auVar37 = _vadd(auVar37,auVar38);
        auStack_460 = _sqc2(auVar37);
        __ct__7FVectorFRC7FVector(auStack_260,auStack_460);
        auVar37 = _lqc2(auStack_260);
        auVar19._4_4_ = fStack_7c;
        auVar19._0_4_ = fStack_80;
        auVar19._8_4_ = fStack_78;
        auVar19._12_4_ = fStack_74;
        auVar38 = _lqc2(auVar19);
        auVar37 = _vadd(auVar37,auVar38);
        auStack_470 = _sqc2(auVar37);
        __ct__7FVectorFRC7FVector(auStack_250,auStack_470);
        auVar37 = _lqc2(auStack_250);
        auVar22._4_4_ = fStack_6c;
        auVar22._0_4_ = fStack_70;
        auVar22._8_4_ = fStack_68;
        auVar22._12_4_ = fStack_64;
        auVar38 = _lqc2(auVar22);
        auVar37 = _vadd(auVar37,auVar38);
        auStack_480 = _sqc2(auVar37);
        __ct__7FVectorFRC7FVector(auStack_240,auStack_480);
        auVar37 = _lqc2(auStack_240);
        auVar25._4_4_ = fStack_5c;
        auVar25._0_4_ = fStack_60;
        auVar25._8_4_ = fStack_58;
        auVar25._12_4_ = fStack_54;
        auVar38 = _lqc2(auVar25);
        auVar37 = _vadd(auVar37,auVar38);
        auStack_490 = _sqc2(auVar37);
        __ct__7FVectorFRC7FVector(auStack_230,auStack_490);
        auVar37 = _lqc2(auStack_230);
        auVar28._4_4_ = fStack_4c;
        auVar28._0_4_ = fStack_50;
        auVar28._8_4_ = fStack_48;
        auVar28._12_4_ = fStack_44;
        auVar38 = _lqc2(auVar28);
        auVar37 = _vadd(auVar37,auVar38);
        auStack_3a0 = _sqc2(auVar37);
        __ct__7FVectorFRC7FVector(auStack_220,auStack_3a0);
        fStack_130 = auStack_220._0_4_;
        fStack_12c = auStack_220._4_4_;
        fStack_128 = fStack_218;
        fStack_124 = fStack_214;
        __adv__7FVectorFf(0x41000000,&fStack_130);
        auVar4._4_4_ = fStack_12c;
        auVar4._0_4_ = fStack_130;
        auVar4._8_4_ = fStack_128;
        auVar4._12_4_ = fStack_124;
        auVar38 = _lqc2(auVar4);
        auVar37 = _lqc2(_auStack_140);
        auVar37 = _vadd(auVar37,auVar38);
        _auStack_140 = _sqc2(auVar37);
        __adv__7FVectorFf(0x40000000,auStack_140);
      }
      else {
        fStack_1e8 = *(float *)(iVar30 + *(short *)(iVar35 + 0x60) * 0x20 + 0x10);
        fStack_1ec = *(float *)(iVar30 + *(short *)(iVar35 + 0x60) * 0x20 + 0xc);
        fStack_1f0 = *(float *)(iVar30 + *(short *)(iVar35 + 0x60) * 0x20 + 8);
        uStack_1e4 = 0x3f800000;
        fStack_b4 = 1.0;
        uStack_208 = *(undefined4 *)(iVar30 + *(short *)(iVar35 + 0x60) * 0x20 + 0x1c);
        uStack_20c = *(undefined4 *)(iVar30 + *(short *)(iVar35 + 0x60) * 0x20 + 0x18);
        uStack_210 = *(undefined4 *)(iVar30 + *(short *)(iVar35 + 0x60) * 0x20 + 0x14);
        uStack_204 = 0x3f800000;
        auVar8._4_4_ = fStack_1ec;
        auVar8._0_4_ = fStack_1f0;
        auVar8._8_4_ = fStack_1e8;
        auVar8._12_4_ = 0x3f800000;
        auVar37 = _lqc2(auVar8);
        auVar2._4_4_ = uStack_20c;
        auVar2._0_4_ = uStack_210;
        auVar2._8_4_ = uStack_208;
        auVar2._12_4_ = 0x3f800000;
        auVar38 = _lqc2(auVar2);
        auVar37 = _vadd(auVar37,auVar38);
        auStack_390 = _sqc2(auVar37);
        fStack_c0 = fStack_1f0;
        fStack_bc = fStack_1ec;
        fStack_b8 = fStack_1e8;
        __ct__7FVectorFRC7FVector(auStack_200,auStack_390);
        fStack_b0 = auStack_200._0_4_;
        fStack_ac = auStack_200._4_4_;
        fStack_a8 = fStack_1f8;
        fStack_a4 = fStack_1f4;
        RotTransVector(&fStack_120,&fStack_c0,auStack_40,2);
        auVar5._4_4_ = fStack_11c;
        auVar5._0_4_ = fStack_120;
        auVar5._8_4_ = fStack_118;
        auVar5._12_4_ = fStack_114;
        auVar38 = _lqc2(auVar5);
        auVar37 = _lqc2(_auStack_140);
        auVar37 = _vadd(auVar37,auVar38);
        _auStack_140 = _sqc2(auVar37);
        __adv__7FVectorFf(0x40000000,auStack_140);
      }
    }
  }
  else {
    if (*(short *)(iVar30 + 2) == 2) {
      pbVar31 = (byte *)(*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar35 + 0x48) * 0x4f0 +
                                                   0x144) + 0x530) + 0xe4) +
                        *(short *)(iVar30 + *(short *)(iVar35 + 0x60) * 0x20 + 6) * 0x110);
      pauVar34 = (undefined1 (*) [16])
                 (*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar35 + 0x48) * 0x4f0 + 0x144)
                                   + 0x530) + 0x30) + (uint)*pbVar31 * 0x1f0 +
                 (bGpffff8340 & 1) * 0x40);
      auStack_40 = *pauVar34;
      auStack_30 = pauVar34[1];
      auStack_20 = pauVar34[2];
      auStack_10 = pauVar34[3];
    }
    else if (*(short *)(iVar30 + 2) == 1) {
      pbVar31 = (byte *)(*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar35 + 0x48) * 0x4f0 +
                                                   0x144) + 0x52c) + 0xe4) +
                        *(short *)(iVar30 + *(short *)(iVar35 + 0x60) * 0x20 + 6) * 0x110);
      pauVar34 = (undefined1 (*) [16])
                 (*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar35 + 0x48) * 0x4f0 + 0x144)
                                   + 0x52c) + 0x30) + (uint)*pbVar31 * 0x1f0 +
                 (bGpffff8340 & 1) * 0x40);
      auStack_40 = *pauVar34;
      auStack_30 = pauVar34[1];
      auStack_20 = pauVar34[2];
      auStack_10 = pauVar34[3];
    }
    else {
      pbVar31 = (byte *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar35 + 0x48) * 0x4f0 + 0x144) +
                                 0xe4) +
                        *(short *)(iVar30 + *(short *)(iVar35 + 0x60) * 0x20 + 6) * 0x110);
      pauVar34 = (undefined1 (*) [16])
                 (*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar35 + 0x48) * 0x4f0 + 0x144) + 0x30) +
                  (uint)*pbVar31 * 0x1f0 + (bGpffff8340 & 1) * 0x40);
      auStack_40 = *pauVar34;
      auStack_30 = pauVar34[1];
      auStack_20 = pauVar34[2];
      auStack_10 = pauVar34[3];
    }
    if (((*(float *)(iVar30 + *(short *)(iVar35 + 0x60) * 0x20 + 8) == 0.0) &&
        (*(float *)(iVar30 + *(short *)(iVar35 + 0x60) * 0x20 + 0xc) == 0.0)) &&
       (*(float *)(iVar30 + *(short *)(iVar35 + 0x60) * 0x20 + 0x10) == 0.0)) {
      RotTransVector(&fStack_c0,pbVar31 + 0x10,auStack_40,8);
      auVar37._4_4_ = fStack_bc;
      auVar37._0_4_ = fStack_c0;
      auVar37._8_4_ = fStack_b8;
      auVar37._12_4_ = fStack_b4;
      auVar37 = _lqc2(auVar37);
      auVar38._4_4_ = fStack_ac;
      auVar38._0_4_ = fStack_b0;
      auVar38._8_4_ = fStack_a8;
      auVar38._12_4_ = fStack_a4;
      auVar38 = _lqc2(auVar38);
      auVar37 = _vadd(auVar37,auVar38);
      auStack_4a0 = _sqc2(auVar37);
      __ct__7FVectorFRC7FVector(auStack_320,auStack_4a0);
      auVar37 = _lqc2(auStack_320);
      auVar39._4_4_ = fStack_9c;
      auVar39._0_4_ = fStack_a0;
      auVar39._8_4_ = fStack_98;
      auVar39._12_4_ = fStack_94;
      auVar38 = _lqc2(auVar39);
      auVar37 = _vadd(auVar37,auVar38);
      auStack_4b0 = _sqc2(auVar37);
      __ct__7FVectorFRC7FVector(auStack_310,auStack_4b0);
      auVar37 = _lqc2(auStack_310);
      auVar17._4_4_ = fStack_8c;
      auVar17._0_4_ = fStack_90;
      auVar17._8_4_ = fStack_88;
      auVar17._12_4_ = fStack_84;
      auVar38 = _lqc2(auVar17);
      auVar37 = _vadd(auVar37,auVar38);
      auStack_4c0 = _sqc2(auVar37);
      __ct__7FVectorFRC7FVector(auStack_300,auStack_4c0);
      auVar37 = _lqc2(auStack_300);
      auVar20._4_4_ = fStack_7c;
      auVar20._0_4_ = fStack_80;
      auVar20._8_4_ = fStack_78;
      auVar20._12_4_ = fStack_74;
      auVar38 = _lqc2(auVar20);
      auVar37 = _vadd(auVar37,auVar38);
      auStack_4d0 = _sqc2(auVar37);
      __ct__7FVectorFRC7FVector(auStack_2f0,auStack_4d0);
      auVar37 = _lqc2(auStack_2f0);
      auVar23._4_4_ = fStack_6c;
      auVar23._0_4_ = fStack_70;
      auVar23._8_4_ = fStack_68;
      auVar23._12_4_ = fStack_64;
      auVar38 = _lqc2(auVar23);
      auVar37 = _vadd(auVar37,auVar38);
      auStack_4e0 = _sqc2(auVar37);
      __ct__7FVectorFRC7FVector(auStack_2e0,auStack_4e0);
      auVar37 = _lqc2(auStack_2e0);
      auVar26._4_4_ = fStack_5c;
      auVar26._0_4_ = fStack_60;
      auVar26._8_4_ = fStack_58;
      auVar26._12_4_ = fStack_54;
      auVar38 = _lqc2(auVar26);
      auVar37 = _vadd(auVar37,auVar38);
      auStack_4f0 = _sqc2(auVar37);
      __ct__7FVectorFRC7FVector(auStack_2d0,auStack_4f0);
      auVar37 = _lqc2(auStack_2d0);
      auVar29._4_4_ = fStack_4c;
      auVar29._0_4_ = fStack_50;
      auVar29._8_4_ = fStack_48;
      auVar29._12_4_ = fStack_44;
      auVar38 = _lqc2(auVar29);
      auVar37 = _vadd(auVar37,auVar38);
      auStack_3c0 = _sqc2(auVar37);
      __ct__7FVectorFRC7FVector(&uStack_2c0,auStack_3c0);
      fStack_138 = (float)uStack_2b8;
      auStack_140 = (undefined1  [8])uStack_2c0;
      fStack_134 = (float)uStack_2b4;
      __adv__7FVectorFf(0x41000000,auStack_140);
    }
    else {
      fStack_288 = *(float *)(iVar30 + *(short *)(iVar35 + 0x60) * 0x20 + 0x10);
      fStack_28c = *(float *)(iVar30 + *(short *)(iVar35 + 0x60) * 0x20 + 0xc);
      fStack_290 = *(float *)(iVar30 + *(short *)(iVar35 + 0x60) * 0x20 + 8);
      uStack_284 = 0x3f800000;
      fStack_b4 = 1.0;
      uStack_2a8 = *(undefined4 *)(iVar30 + *(short *)(iVar35 + 0x60) * 0x20 + 0x1c);
      uStack_2ac = *(undefined4 *)(iVar30 + *(short *)(iVar35 + 0x60) * 0x20 + 0x18);
      uStack_2b0 = *(undefined4 *)(iVar30 + *(short *)(iVar35 + 0x60) * 0x20 + 0x14);
      uStack_2a4 = 0x3f800000;
      auVar10._4_4_ = fStack_28c;
      auVar10._0_4_ = fStack_290;
      auVar10._8_4_ = fStack_288;
      auVar10._12_4_ = 0x3f800000;
      auVar37 = _lqc2(auVar10);
      auVar1._4_4_ = uStack_2ac;
      auVar1._0_4_ = uStack_2b0;
      auVar1._8_4_ = uStack_2a8;
      auVar1._12_4_ = 0x3f800000;
      auVar38 = _lqc2(auVar1);
      auVar37 = _vadd(auVar37,auVar38);
      auStack_3b0 = _sqc2(auVar37);
      fStack_c0 = fStack_290;
      fStack_bc = fStack_28c;
      fStack_b8 = fStack_288;
      __ct__7FVectorFRC7FVector(auStack_2a0,auStack_3b0);
      fStack_b0 = auStack_2a0._0_4_;
      fStack_ac = auStack_2a0._4_4_;
      fStack_a8 = fStack_298;
      fStack_a4 = fStack_294;
      RotTransVector(auStack_140,&fStack_c0,auStack_40,2);
    }
  }
  *(int *)(iVar35 + 0x70) = auStack_140._0_4_;
  *(int *)(iVar35 + 0x74) = auStack_140._4_4_;
  *(float *)(iVar35 + 0x78) = fStack_138;
  *(float *)(iVar35 + 0x7c) = fStack_134;
  *(int *)(iVar35 + 0x80) = auStack_140._0_4_;
  *(int *)(iVar35 + 0x84) = auStack_140._4_4_;
  *(float *)(iVar35 + 0x88) = fStack_138;
  *(float *)(iVar35 + 0x8c) = fStack_134;
  fVar36 = 0.0;
  if (-1 < *(int *)(iVar35 + 0x5c)) {
    auVar37 = _lqc2(*(undefined1 (*) [16])(iGpffff86b4 + *(int *)(iVar35 + 0x5c) * 0x4f0 + 0x150));
    auVar38 = _lqc2(*(undefined1 (*) [16])(iGpffff86b4 + *(int *)(iVar35 + 0x5c) * 0x4f0 + 0x350));
    auVar37 = _vadd(auVar37,auVar38);
    auStack_500 = _sqc2(auVar37);
    __ct__7FVectorFRC7FVector(auStack_340,auStack_500);
    auVar37 = _lqc2(auStack_340);
    auVar38 = _lqc2(*(undefined1 (*) [16])(iVar35 + 0x70));
    auVar37 = _vsub(auVar37,auVar38);
    auStack_3d0 = _sqc2(auVar37);
    __ct__7FVectorFRC7FVector(auStack_330,auStack_3d0);
    fStack_c0 = auStack_330._0_4_;
    fStack_bc = auStack_330._4_4_;
    fStack_b8 = fStack_328;
    fStack_b4 = fStack_324;
    uVar32 = __ct__7FVectorFRC7FVector(auStack_360,&fStack_c0);
    Get3DAngle__F7FVector(auStack_350,uVar32);
    fStack_ac = auStack_350._4_4_;
    fStack_a8 = fStack_348;
    fStack_a4 = fStack_344;
    fStack_b0 = auStack_350._0_4_;
    for (fVar36 = fStack_b0; fVar36 < -180.0; fVar36 = fVar36 + 360.0) {
    }
    for (; 180.0 <= fVar36; fVar36 = fVar36 - 360.0) {
    }
  }
  *(float *)(iVar35 + 0x90) = fVar36;
  *(undefined4 *)(iVar35 + 0x94) =
       *(undefined4 *)(iGpffff86b4 + *(int *)(iVar35 + 0x48) * 0x4f0 + 0x174);
  *(undefined4 *)(iVar35 + 0x98) = 0;
  *(undefined4 *)(iVar35 + 0x9c) = 0x3f800000;
  Entry__7CPollerFP7CPolObjib(iGpffff858c + 0x48,param_2,0x80,0);
  BtlEffEntry__7CBattleFiP6BtlEff(iGpffff86b4,*(undefined4 *)(iVar35 + 0x48),param_2);
  return param_2;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0053ee10  __dt__7Bullet2Fv
 * C++: Bullet2::__dt()
 * size: 0x154 bytes
 * --------------------------------------------------------------------------- */
int __dt__7Bullet2Fv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x14) = 0x409a70;
    *(undefined4 *)(param_1 + 0x28) = 0x409a80;
    *(undefined4 *)(param_1 + 0x34) = 0x409a90;
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
 * JP: 0x0053ef70  Destruct__7Bullet2Fv
 * C++: Bullet2::Destruct()
 * size: 0xcc bytes
 * --------------------------------------------------------------------------- */
void Destruct__7Bullet2Fv(int param_1)

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
 * JP: 0x0053f040  Polling__7Bullet2Fv
 * C++: Bullet2::Polling()
 * size: 0xf14 bytes
 * --------------------------------------------------------------------------- */
undefined4 Polling__7Bullet2Fv(int param_1)

{
  short sVar1;
  bool bVar2;
  float in_zero_lo;
  float in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  char cVar3;
  FVector *pFVar4;
  int iVar5;
  int iVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined1 (*pauVar9) [16];
  int iVar10;
  int iVar11;
  undefined4 uVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  undefined1 in_vf0 [16];
  undefined1 auVar17 [16];
  undefined1 auVar18 [16];
  undefined1 auVar19 [16];
  undefined1 auStack_190 [16];
  undefined1 auStack_180 [16];
  undefined1 auStack_170 [16];
  float fStack_160;
  float fStack_15c;
  undefined4 uStack_158;
  undefined4 uStack_154;
  undefined1 auStack_150 [16];
  float fStack_140;
  float fStack_13c;
  undefined4 uStack_138;
  undefined4 uStack_134;
  undefined1 auStack_130 [16];
  undefined1 auStack_120 [16];
  undefined1 auStack_110 [16];
  undefined1 auStack_100 [16];
  undefined1 auStack_f0 [16];
  undefined1 auStack_e0 [16];
  undefined4 uStack_d0;
  undefined4 uStack_cc;
  float fStack_c8;
  undefined4 uStack_c4;
  undefined8 uStack_c0;
  undefined4 uStack_b8;
  undefined4 uStack_b4;
  undefined1 auStack_b0 [16];
  undefined1 auStack_a0 [8];
  undefined4 uStack_98;
  undefined4 uStack_94;
  undefined1 auStack_90 [16];
  undefined1 auStack_80 [8];
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined1 auStack_70 [8];
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined1 auStack_60 [16];
  undefined1 auStack_50 [16];
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [16];
  float fStack_20;
  float fStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  float fStack_10;
  float fStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  auVar17 = _vmr32(in_vf0);
  auVar18 = _vmr32(auVar17);
  auVar19 = _vmr32(auVar18);
  auStack_30 = _sqc2(in_vf0);
  auStack_40 = _sqc2(auVar17);
  auStack_50 = _sqc2(auVar18);
  auStack_60 = _sqc2(auVar19);
  fVar15 = pCGpffff86b4->flDeltaT;
  if ((pCGpffff86b4->bFlags24 & 1) != 0) {
    fVar15 = 0.0;
  }
  fStack_20 = in_zero_lo;
  fStack_1c = in_zero_hi;
  uStack_18 = in_zero_udw;
  uStack_14 = in_register_0000000c;
  fStack_10 = in_zero_lo;
  fStack_c = in_zero_hi;
  uStack_8 = in_zero_udw;
  uStack_4 = in_register_0000000c;
  if (*(int *)(param_1 + 0x4c0) == 0) {
    if ((-1 < *(int *)(param_1 + 0x5c)) && (fVar15 != 0.0)) {
      auVar17 = _lqc2(*(undefined1 (*) [16])pCGpffff86b4->aChr[*(int *)(param_1 + 0x5c)].aPos);
      auVar18 = _lqc2(*(undefined1 (*) [16])
                       &pCGpffff86b4->aChr[*(int *)(param_1 + 0x5c)].field_0x2a0);
      auVar17 = _vadd(auVar17,auVar18);
      auStack_190 = _sqc2(auVar17);
      __ct__7FVectorFRC7FVector(auStack_90,auStack_190);
      auVar17 = _lqc2(auStack_90);
      auVar18 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x70));
      auVar17 = _vsub(auVar17,auVar18);
      auStack_180 = _sqc2(auVar17);
      __ct__7FVectorFRC7FVector(auStack_80,auStack_180);
      fStack_10 = auStack_80._0_4_;
      fStack_c = auStack_80._4_4_;
      uStack_8 = uStack_78;
      uStack_4 = uStack_74;
      uVar7 = __ct__7FVectorFRC7FVector(auStack_b0,&fStack_10);
      Get3DAngle__F7FVector(auStack_a0,uVar7);
      fStack_20 = auStack_a0._0_4_;
      fStack_1c = auStack_a0._4_4_;
      uStack_18 = uStack_98;
      uStack_14 = uStack_94;
      for (fVar16 = fStack_20 - *(float *)(param_1 + 0x90); fVar16 < -180.0; fVar16 = fVar16 + 360.0
          ) {
      }
      for (; 180.0 <= fVar16; fVar16 = fVar16 - 360.0) {
      }
      fVar14 = fVar15 * 5.0 * 30.0;
      fVar13 = fVar14;
      if (fVar16 <= fVar14) {
        fVar13 = fVar16;
      }
      if (fVar13 < -fVar14) {
        fVar13 = -fVar14;
      }
      *(float *)(param_1 + 0x90) = *(float *)(param_1 + 0x90) + fVar13;
      for (fVar16 = (180.0 - fStack_1c) - *(float *)(param_1 + 0x94); fVar16 < -180.0;
          fVar16 = fVar16 + 360.0) {
      }
      for (; 180.0 <= fVar16; fVar16 = fVar16 - 360.0) {
      }
      fVar13 = fVar14;
      if (fVar16 <= fVar14) {
        fVar13 = fVar16;
      }
      if (fVar13 < -fVar14) {
        fVar13 = -fVar14;
      }
      *(float *)(param_1 + 0x94) = *(float *)(param_1 + 0x94) + fVar13;
    }
    if (fVar15 != 0.0) {
      auVar17 = _vmr32(in_vf0);
      auVar18 = _vmr32(auVar17);
      auVar19 = _vmr32(auVar18);
      auStack_30 = _sqc2(in_vf0);
      auStack_40 = _sqc2(auVar17);
      auStack_50 = _sqc2(auVar18);
      auStack_60 = _sqc2(auVar19);
      uVar12 = GetRad(*(undefined4 *)(param_1 + 0x90));
      sceVu0RotMatrixX(uVar12,auStack_60,auStack_60);
      uVar12 = GetRad(*(undefined4 *)(param_1 + 0x94));
      sceVu0RotMatrixY(uVar12,auStack_60,auStack_60);
      uStack_d0 = 0;
      uStack_cc = 0;
      fStack_c8 = fVar15 * -10.0 * 30.0;
      uStack_c4 = 0x3f800000;
      ApplyMatrix__6MatrixCFRC7FVector(&uStack_c0,auStack_60,&uStack_d0);
      fStack_10 = (float)uStack_c0;
      fStack_c = (float)((ulong)uStack_c0 >> 0x20);
      uStack_8 = uStack_b8;
      uStack_4 = uStack_b4;
      *(int *)(param_1 + 0x80) = (int)*(undefined8 *)(param_1 + 0x70);
      *(int *)(param_1 + 0x84) = (int)((ulong)*(undefined8 *)(param_1 + 0x70) >> 0x20);
      *(undefined4 *)(param_1 + 0x88) = *(undefined4 *)(param_1 + 0x78);
      *(undefined4 *)(param_1 + 0x8c) = *(undefined4 *)(param_1 + 0x7c);
      auVar17._8_4_ = uStack_b8;
      auVar17._0_8_ = uStack_c0;
      auVar17._12_4_ = uStack_b4;
      auVar18 = _lqc2(auVar17);
      auVar17 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x70));
      auVar17 = _vadd(auVar17,auVar18);
      auVar17 = _sqc2(auVar17);
      *(undefined1 (*) [16])(param_1 + 0x70) = auVar17;
    }
    if (((long)((ulong)*(byte *)(param_1 + 0x40) << 0x3d) < 0) && (fVar15 != 0.0)) {
      *(undefined4 *)(param_1 + 0x4c0) = 1;
    }
    if (*(float *)(param_1 + 0x80) < (-*(float *)&pCGpffff86b4->field_0x3f14 - 10.0) / 2.0) {
      *(undefined4 *)(param_1 + 0x4c0) = 1;
    }
    if ((*(float *)&pCGpffff86b4->field_0x3f14 + 10.0) / 2.0 < *(float *)(param_1 + 0x80)) {
      *(undefined4 *)(param_1 + 0x4c0) = 1;
    }
    if (0.0 < *(float *)(param_1 + 0x84)) {
      *(undefined4 *)(param_1 + 0x4c0) = 1;
    }
    if (*(float *)(param_1 + 0x88) < (-*(float *)&pCGpffff86b4->field_0x3f1c - 10.0) / 2.0) {
      *(undefined4 *)(param_1 + 0x4c0) = 1;
    }
    if ((*(float *)&pCGpffff86b4->field_0x3f1c + 10.0) / 2.0 < *(float *)(param_1 + 0x88)) {
      *(undefined4 *)(param_1 + 0x4c0) = 1;
    }
    if (((((-1 < *(int *)(param_1 + 0x5c)) &&
          (-1 < (long)((ulong)*(byte *)(param_1 + 0x40) << 0x3d))) &&
         (*(int *)(param_1 + 0x4c0) == 0)) &&
        ((-1 < (long)((ulong)pCGpffff86b4->aChr[*(int *)(param_1 + 0x5c)].bFlagsB << 0x3c) &&
         (pCGpffff86b4->aChr[*(int *)(param_1 + 0x5c)].bState != 0x29)))) &&
       (pCGpffff86b4->aChr[*(int *)(param_1 + 0x5c)].bState != 0x2c)) {
      uVar7 = __ct__7FVectorFRC7FVector(auStack_e0,param_1 + 0x70);
      cVar3 = VSCircleHitCheck__7CBattleFi7FVectorfP7FVector
                        (0x3f800000,pCGpffff86b4,*(undefined4 *)(param_1 + 0x5c),uVar7,&fStack_10);
      if (cVar3 == '\x01') {
        pFVar4 = (FVector *)__ct__7FVectorFRC7FVector(auStack_f0,&fStack_10);
        PAtkHitSet__7CBattleFii7FVectorfiiiiUsUsfii
                  (pCGpffff86b4,*(int *)(param_1 + 0x48),*(int *)(param_1 + 0x5c),pFVar4,
                   *(float *)(param_1 + 0x94),*(int *)(param_1 + 0xa0),*(int *)(param_1 + 0xa4),
                   *(int *)(param_1 + 0xa8),*(int *)(param_1 + 0xac),*(ushort *)(param_1 + 0xb0),
                   *(ushort *)(param_1 + 0xb2),*(float *)(param_1 + 100),*(int *)(param_1 + 0xb4),
                   *(int *)(param_1 + 0xb8));
        *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfb | 4;
      }
      else {
        uVar7 = __ct__7FVectorFRC7FVector(auStack_100,param_1 + 0x70);
        uVar8 = __ct__7FVectorFRC7FVector(auStack_110,param_1 + 0x80);
        cVar3 = VSLineHitCheck__7CBattleFi7FVector7FVectorP7FVector
                          (pCGpffff86b4,*(undefined4 *)(param_1 + 0x5c),uVar7,uVar8,&fStack_10);
        if (cVar3 == '\x01') {
          pFVar4 = (FVector *)__ct__7FVectorFRC7FVector(auStack_120,&fStack_10);
          PAtkHitSet__7CBattleFii7FVectorfiiiiUsUsfii
                    (pCGpffff86b4,*(int *)(param_1 + 0x48),*(int *)(param_1 + 0x5c),pFVar4,
                     *(float *)(param_1 + 0x94),*(int *)(param_1 + 0xa0),*(int *)(param_1 + 0xa4),
                     *(int *)(param_1 + 0xa8),*(int *)(param_1 + 0xac),*(ushort *)(param_1 + 0xb0),
                     *(ushort *)(param_1 + 0xb2),*(float *)(param_1 + 100),*(int *)(param_1 + 0xb4),
                     *(int *)(param_1 + 0xb8));
          *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfb | 4;
        }
      }
    }
  }
  iVar10 = 8;
  bVar2 = false;
  if ((*(int *)(param_1 + 0x4c0) != 0) || (fVar15 == 0.0)) {
    iVar10 = 0;
  }
  fVar16 = 0.125;
  auVar17 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x70));
  auVar18 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x80));
  auVar17 = _vsub(auVar17,auVar18);
  auStack_170 = _sqc2(auVar17);
  __ct__7FVectorFRC7FVector(auStack_70,auStack_170);
  auVar17 = _vmr32(in_vf0);
  auVar18 = _vmr32(auVar17);
  auVar19 = _vmr32(auVar18);
  auStack_30 = _sqc2(in_vf0);
  auStack_40 = _sqc2(auVar17);
  auStack_50 = _sqc2(auVar18);
  auStack_60 = _sqc2(auVar19);
  uVar12 = GetRad(*(undefined4 *)(param_1 + 0x90));
  sceVu0RotMatrixX(uVar12,auStack_60,auStack_60);
  uVar12 = GetRad(*(undefined4 *)(param_1 + 0x94));
  sceVu0RotMatrixY(uVar12,auStack_60,auStack_60);
  for (iVar11 = 0; iVar11 < 0x20; iVar11 = iVar11 + 1) {
    sVar1 = *(short *)(param_1 + iVar11 * 2 + 0xbc);
    if (sVar1 == 1) {
      iVar5 = param_1 + iVar11 * 4;
      *(float *)(iVar5 + 0x13c) = *(float *)(iVar5 + 0x13c) + fVar15;
      *(float *)(param_1 + iVar11 * 4 + 0x440) =
           ((0.1 - *(float *)(param_1 + iVar11 * 4 + 0x13c)) / 0.1) * 128.0;
      *(float *)(param_1 + iVar11 * 4 + 0x3c0) =
           (0.1 - *(float *)(param_1 + iVar11 * 4 + 0x13c)) / 0.1;
      if ((0.1 <= *(float *)(param_1 + iVar11 * 4 + 0x13c)) &&
         (*(undefined2 *)(param_1 + iVar11 * 2 + 0xbc) = 0, 0 < iVar10)) {
        *(undefined2 *)(param_1 + iVar11 * 2 + 0xbc) = 1;
        iVar5 = param_1 + iVar11 * 0x10;
        *(int *)(iVar5 + 0x1c0) = auStack_70._0_4_;
        *(int *)(iVar5 + 0x1c4) = auStack_70._4_4_;
        *(undefined4 *)(iVar5 + 0x1c8) = uStack_68;
        *(undefined4 *)(iVar5 + 0x1cc) = uStack_64;
        __amu__7FVectorFf((float)iVar10,param_1 + iVar11 * 0x10 + 0x1c0);
        __adv__7FVectorFf(0x41000000,param_1 + iVar11 * 0x10 + 0x1c0);
        pauVar9 = (undefined1 (*) [16])(param_1 + iVar11 * 0x10 + 0x1c0);
        auVar18 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x80));
        auVar17 = _lqc2(*pauVar9);
        auVar17 = _vadd(auVar17,auVar18);
        auVar17 = _sqc2(auVar17);
        *pauVar9 = auVar17;
        iVar5 = rand();
        iVar6 = rand();
        fStack_160 = ((float)iVar6 / 2.1474836e+09) * 5.0 - 2.5;
        uStack_158 = 0;
        uStack_154 = 0x3f800000;
        fStack_15c = ((float)iVar5 / 2.1474836e+09) * 5.0 - 2.5;
        ApplyMatrix__6MatrixCFRC7FVector(auStack_150,auStack_60,&fStack_160);
        pauVar9 = (undefined1 (*) [16])(param_1 + iVar11 * 0x10 + 0x1c0);
        auVar18 = _lqc2(auStack_150);
        auVar17 = _lqc2(*pauVar9);
        auVar17 = _vadd(auVar17,auVar18);
        auVar17 = _sqc2(auVar17);
        *pauVar9 = auVar17;
        *(float *)(param_1 + iVar11 * 4 + 0x13c) = fVar16 / 30.0;
        *(float *)(param_1 + iVar11 * 4 + 0x440) =
             ((0.1 - *(float *)(param_1 + iVar11 * 4 + 0x13c)) / 0.1) * 128.0;
        *(float *)(param_1 + iVar11 * 4 + 0x3c0) =
             (0.1 - *(float *)(param_1 + iVar11 * 4 + 0x13c)) / 0.1;
        iVar10 = iVar10 + -1;
        fVar16 = fVar16 + 0.125;
      }
    }
    else if ((sVar1 == 0) && (0 < iVar10)) {
      *(undefined2 *)(param_1 + iVar11 * 2 + 0xbc) = 1;
      iVar5 = param_1 + iVar11 * 0x10;
      *(int *)(iVar5 + 0x1c0) = auStack_70._0_4_;
      *(int *)(iVar5 + 0x1c4) = auStack_70._4_4_;
      *(undefined4 *)(iVar5 + 0x1c8) = uStack_68;
      *(undefined4 *)(iVar5 + 0x1cc) = uStack_64;
      __amu__7FVectorFf((float)iVar10,param_1 + iVar11 * 0x10 + 0x1c0);
      __adv__7FVectorFf(0x41000000,param_1 + iVar11 * 0x10 + 0x1c0);
      pauVar9 = (undefined1 (*) [16])(param_1 + iVar11 * 0x10 + 0x1c0);
      auVar18 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x80));
      auVar17 = _lqc2(*pauVar9);
      auVar17 = _vadd(auVar17,auVar18);
      auVar17 = _sqc2(auVar17);
      *pauVar9 = auVar17;
      iVar5 = rand();
      iVar6 = rand();
      fStack_140 = ((float)iVar6 / 2.1474836e+09) * 5.0 - 2.5;
      uStack_138 = 0;
      uStack_134 = 0x3f800000;
      fStack_13c = ((float)iVar5 / 2.1474836e+09) * 5.0 - 2.5;
      ApplyMatrix__6MatrixCFRC7FVector(auStack_130,auStack_60,&fStack_140);
      pauVar9 = (undefined1 (*) [16])(param_1 + iVar11 * 0x10 + 0x1c0);
      auVar18 = _lqc2(auStack_130);
      auVar17 = _lqc2(*pauVar9);
      auVar17 = _vadd(auVar17,auVar18);
      auVar17 = _sqc2(auVar17);
      *pauVar9 = auVar17;
      *(float *)(param_1 + iVar11 * 4 + 0x13c) = fVar16 / 30.0;
      *(float *)(param_1 + iVar11 * 4 + 0x440) =
           ((0.1 - *(float *)(param_1 + iVar11 * 4 + 0x13c)) / 0.1) * 128.0;
      *(float *)(param_1 + iVar11 * 4 + 0x3c0) =
           (0.1 - *(float *)(param_1 + iVar11 * 4 + 0x13c)) / 0.1;
      iVar10 = iVar10 + -1;
      fVar16 = fVar16 + 0.125;
    }
    if (*(short *)(param_1 + iVar11 * 2 + 0xbc) != 0) {
      bVar2 = true;
    }
  }
  if ((*(int *)(param_1 + 0x4c0) == 0) || (bVar2)) {
    uVar12 = 0;
  }
  else {
    BtlEffRelease__7CBattleFiP6BtlEff(pCGpffff86b4,*(undefined4 *)(param_1 + 0x48),param_1);
    if ((long)((ulong)*(byte *)(param_1 + 0x40) << 0x3e) < 0) {
      iVar10 = param_1;
      if (param_1 != 0) {
        iVar10 = param_1 + 0x18;
      }
      ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,iVar10);
    }
    *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfd;
    (**(code **)(*(int *)(param_1 + 0x34) + 0xc))();
    uVar12 = 1;
  }
  return uVar12;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0053ff60  MakePacket__7Bullet2Fv
 * C++: Bullet2::MakePacket()
 * size: 0xfbc bytes
 * --------------------------------------------------------------------------- */
void MakePacket__7Bullet2Fv(int param_1)

{
  bool bVar1;
  undefined4 *puVar2;
  bool bVar3;
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  undefined4 uVar4;
  undefined8 uVar5;
  long lVar6;
  int iVar7;
  undefined8 in_v1_udw;
  undefined1 auVar8 [16];
  undefined1 auVar9 [16];
  int iVar10;
  int iVar11;
  int iVar12;
  uint uVar13;
  undefined4 uStack_1200;
  undefined4 uStack_11fc;
  undefined4 uStack_11f8;
  undefined4 uStack_11f4;
  undefined4 uStack_11f0;
  undefined4 uStack_11ec;
  undefined4 uStack_11e8;
  undefined4 uStack_11e4;
  undefined4 uStack_11e0;
  undefined4 uStack_11dc;
  undefined4 uStack_11d8;
  undefined4 uStack_11d4;
  undefined4 uStack_11d0;
  undefined4 uStack_11cc;
  undefined4 uStack_11c8;
  undefined4 uStack_11c4;
  undefined4 uStack_11c0;
  undefined4 uStack_11bc;
  undefined4 uStack_11b8;
  undefined4 uStack_11b4;
  undefined4 uStack_11b0;
  undefined4 uStack_11ac;
  undefined4 uStack_11a8;
  undefined4 uStack_11a4;
  undefined4 uStack_11a0;
  undefined4 uStack_119c;
  undefined4 uStack_1198;
  undefined4 uStack_1194;
  undefined4 uStack_1190;
  undefined4 uStack_118c;
  undefined4 uStack_1188;
  undefined4 uStack_1184;
  int aiStack_1180 [4];
  int iStack_1170;
  int iStack_116c;
  int iStack_1168;
  int iStack_1160;
  int iStack_115c;
  int iStack_1158;
  int iStack_1150;
  int iStack_114c;
  int iStack_1148;
  int aiStack_1140 [528];
  float afStack_900 [528];
  float afStack_c0 [16];
  int aiStack_80 [7];
  undefined4 uStack_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  uStack_1190 = 0xbf800000;
  uStack_118c = 0xbf800000;
  uStack_1188 = 0;
  uStack_1184 = 0x3f800000;
  uStack_40 = 0xbf800000;
  uStack_3c = 0xbf800000;
  uStack_38 = 0;
  uStack_34 = 0x3f800000;
  uStack_11a0 = 0xbf800000;
  uStack_119c = 0x3f800000;
  uStack_1198 = 0;
  uStack_1194 = 0x3f800000;
  uStack_30 = 0xbf800000;
  uStack_2c = 0x3f800000;
  uStack_28 = 0;
  uStack_24 = 0x3f800000;
  uStack_11b0 = 0x3f800000;
  uStack_11ac = 0xbf800000;
  uStack_11a8 = 0;
  uStack_11a4 = 0x3f800000;
  uStack_20 = 0x3f800000;
  uStack_1c = 0xbf800000;
  uStack_18 = 0;
  uStack_14 = 0x3f800000;
  uStack_11c0 = 0x3f800000;
  uStack_11bc = 0x3f800000;
  uStack_11b8 = 0;
  uStack_11b4 = 0x3f800000;
  uStack_10 = 0x3f800000;
  uStack_c = 0x3f800000;
  uStack_8 = 0;
  uStack_4 = 0x3f800000;
  __ct__6MatrixFRC6Matrix(aiStack_80,iGpffff8598 + 0x240);
  uStack_50 = 0;
  uStack_4c = 0;
  uStack_48 = 0;
  uStack_44 = 0x3f800000;
  RotTransVector(afStack_c0,&uStack_40,aiStack_80,4);
  for (iVar7 = 0; iVar7 < 4; iVar7 = iVar7 + 1) {
    afStack_900[iVar7 * 4] = *(float *)(param_1 + 0x70) + afStack_c0[iVar7 * 4] * 5.0;
    afStack_900[iVar7 * 4 + 1] = *(float *)(param_1 + 0x74) + afStack_c0[iVar7 * 4 + 1] * 5.0;
    afStack_900[iVar7 * 4 + 2] = *(float *)(param_1 + 0x78) + afStack_c0[iVar7 * 4 + 2] * 5.0;
    afStack_900[iVar7 * 4 + 3] = 1.0;
  }
  for (iVar7 = 0; iVar7 < 0x20; iVar7 = iVar7 + 1) {
    for (iVar12 = 0; iVar12 < 4; iVar12 = iVar12 + 1) {
      afStack_900[(iVar12 + (iVar7 + 1) * 4) * 4] =
           *(float *)(param_1 + iVar7 * 0x10 + 0x1c0) +
           *(float *)(param_1 + iVar7 * 4 + 0x3c0) * afStack_c0[iVar12 * 4] * 2.0;
      afStack_900[(iVar12 + (iVar7 + 1) * 4) * 4 + 1] =
           *(float *)(param_1 + iVar7 * 0x10 + 0x1c4) +
           *(float *)(param_1 + iVar7 * 4 + 0x3c0) * afStack_c0[iVar12 * 4 + 1] * 2.0;
      afStack_900[(iVar12 + (iVar7 + 1) * 4) * 4 + 2] =
           *(float *)(param_1 + iVar7 * 0x10 + 0x1c8) +
           *(float *)(param_1 + iVar7 * 4 + 0x3c0) * afStack_c0[iVar12 * 4 + 2] * 2.0;
      afStack_900[(iVar12 + (iVar7 + 1) * 4) * 4 + 3] = 1.0;
    }
  }
  GetViewScreenMatrix__9GsxCameraFv(&uStack_1200,iGpffff8598);
  aiStack_80[0] = uStack_1200;
  aiStack_80[1] = uStack_11fc;
  aiStack_80[2] = uStack_11f8;
  aiStack_80[3] = uStack_11f4;
  aiStack_80[4] = uStack_11f0;
  aiStack_80[5] = uStack_11ec;
  aiStack_80[6] = uStack_11e8;
  uStack_64 = uStack_11e4;
  uStack_60 = uStack_11e0;
  uStack_5c = uStack_11dc;
  uStack_58 = uStack_11d8;
  uStack_54 = uStack_11d4;
  uStack_50 = uStack_11d0;
  uStack_4c = uStack_11cc;
  uStack_48 = uStack_11c8;
  uStack_44 = uStack_11c4;
  for (iVar7 = 0; iVar7 < 4; iVar7 = iVar7 + 1) {
    aiStack_1140[iVar7 * 4 + 0x200] = aiStack_80[iVar7 * 4];
    aiStack_1140[iVar7 * 4 + 0x201] = aiStack_80[iVar7 * 4 + 1];
    aiStack_1140[iVar7 * 4 + 0x202] = aiStack_80[iVar7 * 4 + 2];
    aiStack_1140[iVar7 * 4 + 0x203] = aiStack_80[iVar7 * 4 + 3];
  }
  sceVu0RotTransPersN(aiStack_1180,aiStack_1140 + 0x200,afStack_900,0x84,0);
  bVar3 = false;
  iVar7 = 0;
  for (iVar12 = 0; iVar12 < 0x21; iVar12 = iVar12 + 1) {
    if (iVar12 != 0) {
      *(undefined2 *)(param_1 + (iVar12 + -1) * 2 + 0xfc) = 0;
    }
    for (iVar10 = 0; iVar10 < 4; iVar10 = iVar10 + 1) {
      if (iVar12 == 0) {
        if (((aiStack_1180[iVar10 * 4] < 0) || (0x10000 < aiStack_1180[iVar10 * 4])) ||
           ((aiStack_1180[iVar10 * 4 + 1] < 0 ||
            ((0x10000 < aiStack_1180[iVar10 * 4 + 1] || (aiStack_1180[iVar10 * 4 + 2] < 0)))))) {
          bVar3 = true;
        }
        aiStack_1180[iVar10 * 4 + 2] = (int)((float)aiStack_1180[iVar10 * 4 + 2] / 16.0);
        iVar7 = iVar7 + aiStack_1180[iVar10 * 4 + 2];
      }
      else {
        if ((((aiStack_1180[(iVar10 + iVar12 * 4) * 4] < 0) ||
             (0x10000 < aiStack_1180[(iVar10 + iVar12 * 4) * 4])) ||
            (aiStack_1180[(iVar10 + iVar12 * 4) * 4 + 1] < 0)) ||
           ((0x10000 < aiStack_1180[(iVar10 + iVar12 * 4) * 4 + 1] ||
            (aiStack_1180[(iVar10 + iVar12 * 4) * 4 + 2] < 0)))) {
          *(undefined2 *)(param_1 + (iVar12 + -1) * 2 + 0xfc) = 1;
        }
        iVar11 = iVar10 + iVar12 * 4;
        aiStack_1180[iVar11 * 4 + 2] = (int)((float)aiStack_1180[iVar11 * 4 + 2] / 16.0);
      }
    }
  }
  if (iVar7 < 0) {
    iVar7 = iVar7 + 3;
  }
  *(int *)(param_1 + 0x50) = iVar7 >> 2;
  bVar1 = (*(byte *)(param_1 + 0x40) & 1) == 0;
  uVar13 = (uint)bVar1;
  if (*(int *)(param_1 + uVar13 * 4 + 0x18) == 0) {
    uVar4 = __nwa__FUi(0xd00);
    *(undefined4 *)(param_1 + uVar13 * 4 + 0x18) = uVar4;
    iVar7 = *(int *)(param_1 + uVar13 * 4 + 0x18);
    *(undefined4 *)(iVar7 + 0x10) = 0x100000ad;
    *(undefined4 *)(iVar7 + 0x14) = 0;
    *(undefined4 *)(iVar7 + 0x18) = 0;
    *(undefined4 *)(iVar7 + 0x1c) = 0x500000ad;
    *(undefined8 *)(iVar7 + 0x20) = 0x6000000000000001;
    *(undefined8 *)(iVar7 + 0x28) = 0xe6e8ee;
    *(undefined8 *)(iVar7 + 0x30) = 1;
    *(undefined8 *)(iVar7 + 0x38) = 0x3f;
    *(undefined8 *)(iVar7 + 0x40) = 0x60;
    *(undefined8 *)(iVar7 + 0x48) = 0x14;
    *(undefined8 *)(iVar7 + 0x50) = 5;
    *(undefined8 *)(iVar7 + 0x58) = 0;
    *(undefined8 *)(iVar7 + 0x60) = 0x53001;
    *(undefined8 *)(iVar7 + 0x68) = 0x47;
    uVar5 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x42e4),1);
    *(undefined8 *)(iVar7 + 0x70) = uVar5;
    *(undefined8 *)(iVar7 + 0x78) = 0;
    *(undefined8 *)(iVar7 + 0x80) = 0x48;
    *(undefined8 *)(iVar7 + 0x88) = 0x42;
    auVar8._8_8_ = in_v1_udw;
    auVar8._0_8_ = 0xa400000000008021;
    auVar9._4_4_ = in_zero_hi;
    auVar9._0_4_ = in_zero_lo;
    auVar9._8_4_ = in_zero_udw;
    auVar9._12_4_ = in_register_0000000c;
    auVar9 = _pcpyld(auVar9,auVar8);
    *(long *)(iVar7 + 0x90) = auVar9._0_8_;
    *(undefined8 *)(iVar7 + 0x98) = 0x4343c3c310;
    *(undefined8 *)(iVar7 + 0xa0) = 0x154;
    *(undefined8 *)(iVar7 + 0xa8) = 0x180808080;
    *(undefined8 *)(iVar7 + 0xb0) = 0;
    *(long *)(iVar7 + 0xc0) =
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42e4) + 4) << 4) << 0x10;
    *(long *)(iVar7 + 0xd0) =
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42e4) + 2) << 4);
    *(long *)(iVar7 + 0xe0) =
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42e4) + 2) << 4) |
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42e4) + 4) << 4) << 0x10;
    for (iVar12 = 0; iVar12 < 0x20; iVar12 = iVar12 + 1) {
      *(undefined8 *)(iVar7 + (iVar12 * 5 + 0xf) * 0x10) = 0x154;
      *(undefined8 *)(iVar7 + (iVar12 * 5 + 0x10) * 0x10) = 0;
      *(long *)(iVar7 + (iVar12 * 5 + 0x11) * 0x10) =
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42e4) + 4) << 4) << 0x10;
      *(long *)(iVar7 + (iVar12 * 5 + 0x12) * 0x10) =
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42e4) + 2) << 4);
      *(long *)(iVar7 + (iVar12 * 5 + 0x13) * 0x10) =
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42e4) + 2) << 4) |
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42e4) + 4) << 4) << 0x10;
    }
  }
  puVar2 = *(undefined4 **)(param_1 + uVar13 * 4 + 0x18);
  *puVar2 = 0x50000000;
  puVar2[1] = *(undefined4 *)
               (*(int *)(iGpffff86b4 + 0x42e4) +
                (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42e4) + 10) * 4 + 0xc);
  puVar2[2] = 0;
  puVar2[3] = 0;
  if (bVar3) {
    *(ulong *)(puVar2 + 0x2e) = (long)aiStack_1180[2] << 0x20 | 0x71006f00;
    *(ulong *)(puVar2 + 0x32) = (long)iStack_1168 << 0x20 | 0x71006f00;
    *(ulong *)(puVar2 + 0x36) = (long)iStack_1158 << 0x20 | 0x71006f00;
    *(ulong *)(puVar2 + 0x3a) = (long)iStack_1148 << 0x20 | 0x71006f00;
  }
  else {
    *(long *)(puVar2 + 0x2e) =
         (long)aiStack_1180[2] << 0x20 | (long)aiStack_1180[0] | (long)aiStack_1180[1] << 0x10;
    *(long *)(puVar2 + 0x32) =
         (long)iStack_1168 << 0x20 | (long)iStack_1170 | (long)iStack_116c << 0x10;
    *(long *)(puVar2 + 0x36) =
         (long)iStack_1158 << 0x20 | (long)iStack_1160 | (long)iStack_115c << 0x10;
    *(long *)(puVar2 + 0x3a) =
         (long)iStack_1148 << 0x20 | (long)iStack_1150 | (long)iStack_114c << 0x10;
  }
  for (iVar7 = 0; iVar7 < 0x20; iVar7 = iVar7 + 1) {
    lVar6 = __fixunssfdi(*(undefined4 *)(param_1 + iVar7 * 4 + 0x440));
    *(ulong *)(puVar2 + (iVar7 * 5 + 0xf) * 4 + 2) = lVar6 << 0x18 | 0x100808080;
    if (*(short *)(param_1 + iVar7 * 2 + 0xfc) == 0) {
      *(long *)(puVar2 + (iVar7 * 5 + 0x10) * 4 + 2) =
           (long)aiStack_1180[(iVar7 * 4 + 4) * 4 + 2] << 0x20 |
           (long)aiStack_1180[(iVar7 * 4 + 4) * 4] |
           (long)aiStack_1180[(iVar7 * 4 + 4) * 4 + 1] << 0x10;
      *(long *)(puVar2 + (iVar7 * 5 + 0x11) * 4 + 2) =
           (long)aiStack_1180[(iVar7 * 4 + 5) * 4 + 2] << 0x20 |
           (long)aiStack_1180[(iVar7 * 4 + 5) * 4] |
           (long)aiStack_1180[(iVar7 * 4 + 5) * 4 + 1] << 0x10;
      *(long *)(puVar2 + (iVar7 * 5 + 0x12) * 4 + 2) =
           (long)aiStack_1180[(iVar7 * 4 + 6) * 4 + 2] << 0x20 |
           (long)aiStack_1180[(iVar7 * 4 + 6) * 4] |
           (long)aiStack_1180[(iVar7 * 4 + 6) * 4 + 1] << 0x10;
      *(long *)(puVar2 + (iVar7 * 5 + 0x13) * 4 + 2) =
           (long)aiStack_1180[(iVar7 * 4 + 7) * 4 + 2] << 0x20 |
           (long)aiStack_1180[(iVar7 * 4 + 7) * 4] |
           (long)aiStack_1180[(iVar7 * 4 + 7) * 4 + 1] << 0x10;
    }
    else {
      *(ulong *)(puVar2 + (iVar7 * 5 + 0x10) * 4 + 2) =
           (long)aiStack_1180[(iVar7 * 4 + 4) * 4 + 2] << 0x20 | 0x71006f00;
      *(ulong *)(puVar2 + (iVar7 * 5 + 0x11) * 4 + 2) =
           (long)aiStack_1180[(iVar7 * 4 + 5) * 4 + 2] << 0x20 | 0x71006f00;
      *(ulong *)(puVar2 + (iVar7 * 5 + 0x12) * 4 + 2) =
           (long)aiStack_1180[(iVar7 * 4 + 6) * 4 + 2] << 0x20 | 0x71006f00;
      *(ulong *)(puVar2 + (iVar7 * 5 + 0x13) * 4 + 2) =
           (long)aiStack_1180[(iVar7 * 4 + 7) * 4 + 2] << 0x20 | 0x71006f00;
    }
  }
  *(undefined4 **)(param_1 + 0x54) = puVar2 + 700;
  *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfe | bVar1;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054adc0  EndSet__7Bullet2Fv
 * C++: Bullet2::EndSet()
 * size: 0x10 bytes
 * --------------------------------------------------------------------------- */
void EndSet__7Bullet2Fv(void)

{
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b910  @24@__dt__7Bullet2Fv
 * C++: @24@__dt__7Bullet2Fv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int * _24___dt__7Bullet2Fv(int *param_1,short param_2)

{
  int *piVar1;
  
  piVar1 = param_1 + -6;
  if (piVar1 != (int *)0x0) {
    param_1[-1] = 0x409a70;
    param_1[4] = 0x409a80;
    param_1[7] = 0x409a90;
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
 * JP: 0x0054b920  @44@__dt__7Bullet2Fv
 * C++: @44@__dt__7Bullet2Fv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int _44___dt__7Bullet2Fv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x2c;
  if (iVar1 != 0) {
    *(undefined4 *)(param_1 + -0x18) = 0x409a70;
    *(undefined4 *)(param_1 + -4) = 0x409a80;
    *(undefined4 *)(param_1 + 8) = 0x409a90;
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

