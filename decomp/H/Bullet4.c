/* decomp/H/Bullet4.c — cleaned Ghidra output (SH2JP_BATTLE.BIN, JP Furokuban, base 0x00430a00).
 * 8 function(s). Types: see types.h. Names/gp globals resolved from symbols/SLPM_602.19.syms. */
#include "types.h"

/* ---------------------------------------------------------------------------
 * JP: 0x00543d20  __ct__7Bullet4FiiissfiiiiUsUsii
 * C++: Bullet4::__ct(int, int, int, short, short, float, int, int, int, int, ushort, ushort, int, int)
 * size: 0x1810 bytes
 * --------------------------------------------------------------------------- */
undefined8
__ct__7Bullet4FiiissfiiiiUsUsii
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
  int iVar32;
  undefined8 uVar33;
  float *pfVar34;
  undefined1 (*pauVar35) [16];
  int iVar36;
  float fVar37;
  undefined1 in_vf0 [16];
  undefined1 auVar38 [16];
  undefined1 auVar39 [16];
  undefined1 auVar40 [16];
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
  iVar36 = (int)param_2;
  *(undefined4 *)(iVar36 + 0x14) = 0x409980;
  *(undefined4 *)(iVar36 + 0x28) = 0x409990;
  *(undefined4 *)(iVar36 + 0x34) = 0x4099a0;
  pfVar34 = (float *)(iVar36 + 0x70);
  do {
    *pfVar34 = in_zero_lo;
    pfVar34[1] = in_zero_hi;
    pfVar34[2] = in_zero_udw;
    pfVar34[3] = in_register_0000000c;
    pfVar34 = pfVar34 + 4;
  } while (pfVar34 != (float *)(iVar36 + 0x170));
  *(float *)(iVar36 + 0x170) = in_zero_lo;
  *(float *)(iVar36 + 0x174) = in_zero_hi;
  *(float *)(iVar36 + 0x178) = in_zero_udw;
  *(float *)(iVar36 + 0x17c) = in_register_0000000c;
  *(undefined4 *)(iVar36 + 0x40) = 0;
  *(int *)(iVar36 + 0x44) = (int)param_3;
  *(int *)(iVar36 + 0x48) = (int)param_4;
  *(undefined4 *)(iVar36 + 0x4c) = 10;
  *(undefined4 *)(iVar36 + 0x5c) = param_5;
  *(undefined2 *)(iVar36 + 0x60) = param_6;
  *(undefined2 *)(iVar36 + 0x62) = param_7;
  *(undefined4 *)(iVar36 + 100) = param_1;
  *(undefined4 *)(iVar36 + 0x180) = param_9;
  *(undefined4 *)(iVar36 + 0x184) = param_10;
  *(undefined4 *)(iVar36 + 0x188) = param_8;
  *(undefined4 *)(iVar36 + 0x18c) = param_11;
  *(undefined2 *)(iVar36 + 400) = param_12;
  *(undefined2 *)(iVar36 + 0x192) = param_13;
  *(undefined4 *)(iVar36 + 0x194) = param_14;
  *(undefined4 *)(iVar36 + 0x198) = param_15;
  *(undefined4 *)(iVar36 + 0x1c) = 0;
  *(undefined4 *)(iVar36 + 0x18) = 0;
  *(undefined4 *)(iVar36 + 0x1a4) = 0;
  *(undefined4 *)(iVar36 + 0x1a0) = 0;
  *(undefined2 *)(iVar36 + 0x19c) = 0;
  iVar30 = GetRegDat__9RegDatApiFiii(0x3a,*(undefined4 *)
                                 (iGpffff86b4 + *(int *)(iVar36 + 0x48) * 0x4f0 + 0x55c),
                           0xffffffffffffffff);
  iVar30 = *(int *)(*(short *)(iVar30 + 0x14) * 4 + 0x651b70);
  auVar38 = _vmr32(in_vf0);
  auVar39 = _vmr32(auVar38);
  auVar40 = _vmr32(auVar39);
  _sqc2(in_vf0);
  _sqc2(auVar38);
  _sqc2(auVar39);
  _sqc2(auVar40);
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
  if (*(short *)(iVar36 + 0x62) == 0) {
    if (*(short *)(iVar30 + 2) == 2) {
      pbVar31 = (byte *)(*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar36 + 0x48) * 0x4f0 +
                                                   0x144) + 0x530) + 0xe4) +
                        *(short *)(iVar30 + *(short *)(iVar36 + 0x60) * 0x20 + 4) * 0x110);
      pauVar35 = (undefined1 (*) [16])
                 (*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar36 + 0x48) * 0x4f0 + 0x144)
                                   + 0x530) + 0x30) + (uint)*pbVar31 * 0x1f0 +
                 (bGpffff8340 & 1) * 0x40);
      auStack_40 = *pauVar35;
      auStack_30 = pauVar35[1];
      auStack_20 = pauVar35[2];
      auStack_10 = pauVar35[3];
    }
    else if (*(short *)(iVar30 + 2) == 1) {
      pbVar31 = (byte *)(*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar36 + 0x48) * 0x4f0 +
                                                   0x144) + 0x52c) + 0xe4) +
                        *(short *)(iVar30 + *(short *)(iVar36 + 0x60) * 0x20 + 4) * 0x110);
      pauVar35 = (undefined1 (*) [16])
                 (*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar36 + 0x48) * 0x4f0 + 0x144)
                                   + 0x52c) + 0x30) + (uint)*pbVar31 * 0x1f0 +
                 (bGpffff8340 & 1) * 0x40);
      auStack_40 = *pauVar35;
      auStack_30 = pauVar35[1];
      auStack_20 = pauVar35[2];
      auStack_10 = pauVar35[3];
    }
    else {
      pbVar31 = (byte *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar36 + 0x48) * 0x4f0 + 0x144) +
                                 0xe4) +
                        *(short *)(iVar30 + *(short *)(iVar36 + 0x60) * 0x20 + 4) * 0x110);
      pauVar35 = (undefined1 (*) [16])
                 (*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar36 + 0x48) * 0x4f0 + 0x144) + 0x30) +
                  (uint)*pbVar31 * 0x1f0 + (bGpffff8340 & 1) * 0x40);
      auStack_40 = *pauVar35;
      auStack_30 = pauVar35[1];
      auStack_20 = pauVar35[2];
      auStack_10 = pauVar35[3];
    }
    fStack_120 = in_zero_lo;
    fStack_11c = in_zero_hi;
    fStack_118 = in_zero_udw;
    fStack_114 = in_register_0000000c;
    if (((*(float *)(iVar30 + *(short *)(iVar36 + 0x60) * 0x20 + 8) == 0.0) &&
        (*(float *)(iVar30 + *(short *)(iVar36 + 0x60) * 0x20 + 0xc) == 0.0)) &&
       (*(float *)(iVar30 + *(short *)(iVar36 + 0x60) * 0x20 + 0x10) == 0.0)) {
      RotTransVector(&fStack_c0,pbVar31 + 0x10,auStack_40,8);
      auVar7._4_4_ = fStack_bc;
      auVar7._0_4_ = fStack_c0;
      auVar7._8_4_ = fStack_b8;
      auVar7._12_4_ = fStack_b4;
      auVar38 = _lqc2(auVar7);
      auVar11._4_4_ = fStack_ac;
      auVar11._0_4_ = fStack_b0;
      auVar11._8_4_ = fStack_a8;
      auVar11._12_4_ = fStack_a4;
      auVar39 = _lqc2(auVar11);
      auVar38 = _vadd(auVar38,auVar39);
      auStack_3e0 = _sqc2(auVar38);
      __ct__7FVectorFRC7FVector(auStack_1e0,auStack_3e0);
      auVar38 = _lqc2(auStack_1e0);
      auVar13._4_4_ = fStack_9c;
      auVar13._0_4_ = fStack_a0;
      auVar13._8_4_ = fStack_98;
      auVar13._12_4_ = fStack_94;
      auVar39 = _lqc2(auVar13);
      auVar38 = _vadd(auVar38,auVar39);
      auStack_3f0 = _sqc2(auVar38);
      __ct__7FVectorFRC7FVector(auStack_1d0,auStack_3f0);
      auVar38 = _lqc2(auStack_1d0);
      auVar15._4_4_ = fStack_8c;
      auVar15._0_4_ = fStack_90;
      auVar15._8_4_ = fStack_88;
      auVar15._12_4_ = fStack_84;
      auVar39 = _lqc2(auVar15);
      auVar38 = _vadd(auVar38,auVar39);
      auStack_400 = _sqc2(auVar38);
      __ct__7FVectorFRC7FVector(auStack_1c0,auStack_400);
      auVar38 = _lqc2(auStack_1c0);
      auVar18._4_4_ = fStack_7c;
      auVar18._0_4_ = fStack_80;
      auVar18._8_4_ = fStack_78;
      auVar18._12_4_ = fStack_74;
      auVar39 = _lqc2(auVar18);
      auVar38 = _vadd(auVar38,auVar39);
      auStack_410 = _sqc2(auVar38);
      __ct__7FVectorFRC7FVector(auStack_1b0,auStack_410);
      auVar38 = _lqc2(auStack_1b0);
      auVar21._4_4_ = fStack_6c;
      auVar21._0_4_ = fStack_70;
      auVar21._8_4_ = fStack_68;
      auVar21._12_4_ = fStack_64;
      auVar39 = _lqc2(auVar21);
      auVar38 = _vadd(auVar38,auVar39);
      auStack_420 = _sqc2(auVar38);
      __ct__7FVectorFRC7FVector(auStack_1a0,auStack_420);
      auVar38 = _lqc2(auStack_1a0);
      auVar24._4_4_ = fStack_5c;
      auVar24._0_4_ = fStack_60;
      auVar24._8_4_ = fStack_58;
      auVar24._12_4_ = fStack_54;
      auVar39 = _lqc2(auVar24);
      auVar38 = _vadd(auVar38,auVar39);
      auStack_430 = _sqc2(auVar38);
      __ct__7FVectorFRC7FVector(auStack_190,auStack_430);
      auVar38 = _lqc2(auStack_190);
      auVar27._4_4_ = fStack_4c;
      auVar27._0_4_ = fStack_50;
      auVar27._8_4_ = fStack_48;
      auVar27._12_4_ = fStack_44;
      auVar39 = _lqc2(auVar27);
      auVar38 = _vadd(auVar38,auVar39);
      auStack_380 = _sqc2(auVar38);
      __ct__7FVectorFRC7FVector(&uStack_180,auStack_380);
      fStack_138 = (float)uStack_178;
      auStack_140 = (undefined1  [8])uStack_180;
      fStack_134 = (float)uStack_174;
      __adv__7FVectorFf(0x41000000,auStack_140);
    }
    else {
      fStack_148 = *(float *)(iVar30 + *(short *)(iVar36 + 0x60) * 0x20 + 0x10);
      fStack_14c = *(float *)(iVar30 + *(short *)(iVar36 + 0x60) * 0x20 + 0xc);
      fStack_150 = *(float *)(iVar30 + *(short *)(iVar36 + 0x60) * 0x20 + 8);
      uStack_144 = 0x3f800000;
      fStack_b4 = 1.0;
      uStack_168 = *(undefined4 *)(iVar30 + *(short *)(iVar36 + 0x60) * 0x20 + 0x1c);
      uStack_16c = *(undefined4 *)(iVar30 + *(short *)(iVar36 + 0x60) * 0x20 + 0x18);
      uStack_170 = *(undefined4 *)(iVar30 + *(short *)(iVar36 + 0x60) * 0x20 + 0x14);
      uStack_164 = 0x3f800000;
      auVar6._4_4_ = fStack_14c;
      auVar6._0_4_ = fStack_150;
      auVar6._8_4_ = fStack_148;
      auVar6._12_4_ = 0x3f800000;
      auVar38 = _lqc2(auVar6);
      auVar3._4_4_ = uStack_16c;
      auVar3._0_4_ = uStack_170;
      auVar3._8_4_ = uStack_168;
      auVar3._12_4_ = 0x3f800000;
      auVar39 = _lqc2(auVar3);
      auVar38 = _vadd(auVar38,auVar39);
      auStack_370 = _sqc2(auVar38);
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
    if (*(short *)(iVar30 + *(short *)(iVar36 + 0x60) * 0x20 + 6) < -1) {
      if (*(short *)(iVar30 + 2) == 2) {
        pbVar31 = (byte *)(*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar36 + 0x48) * 0x4f0
                                                     + 0x144) + 0x530) + 0xe4) +
                          *(short *)(iVar30 + *(short *)(iVar36 + 0x60) * 0x20 + 6) * -0x110);
        pauVar35 = (undefined1 (*) [16])
                   (*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar36 + 0x48) * 0x4f0 + 0x144
                                              ) + 0x530) + 0x30) + (uint)*pbVar31 * 0x1f0 +
                   (bGpffff8340 & 1) * 0x40);
        auStack_40 = *pauVar35;
        auStack_30 = pauVar35[1];
        auStack_20 = pauVar35[2];
        auStack_10 = pauVar35[3];
      }
      else if (*(short *)(iVar30 + 2) == 1) {
        pbVar31 = (byte *)(*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar36 + 0x48) * 0x4f0
                                                     + 0x144) + 0x52c) + 0xe4) +
                          *(short *)(iVar30 + *(short *)(iVar36 + 0x60) * 0x20 + 6) * -0x110);
        pauVar35 = (undefined1 (*) [16])
                   (*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar36 + 0x48) * 0x4f0 + 0x144
                                              ) + 0x52c) + 0x30) + (uint)*pbVar31 * 0x1f0 +
                   (bGpffff8340 & 1) * 0x40);
        auStack_40 = *pauVar35;
        auStack_30 = pauVar35[1];
        auStack_20 = pauVar35[2];
        auStack_10 = pauVar35[3];
      }
      else {
        pbVar31 = (byte *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar36 + 0x48) * 0x4f0 + 0x144)
                                   + 0xe4) +
                          *(short *)(iVar30 + *(short *)(iVar36 + 0x60) * 0x20 + 6) * -0x110);
        pauVar35 = (undefined1 (*) [16])
                   (*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar36 + 0x48) * 0x4f0 + 0x144) + 0x30)
                    + (uint)*pbVar31 * 0x1f0 + (bGpffff8340 & 1) * 0x40);
        auStack_40 = *pauVar35;
        auStack_30 = pauVar35[1];
        auStack_20 = pauVar35[2];
        auStack_10 = pauVar35[3];
      }
      if (((*(float *)(iVar30 + *(short *)(iVar36 + 0x60) * 0x20 + 8) == 0.0) &&
          (*(float *)(iVar30 + *(short *)(iVar36 + 0x60) * 0x20 + 0xc) == 0.0)) &&
         (*(float *)(iVar30 + *(short *)(iVar36 + 0x60) * 0x20 + 0x10) == 0.0)) {
        RotTransVector(&fStack_c0,pbVar31 + 0x10,auStack_40,8);
        auVar9._4_4_ = fStack_bc;
        auVar9._0_4_ = fStack_c0;
        auVar9._8_4_ = fStack_b8;
        auVar9._12_4_ = fStack_b4;
        auVar38 = _lqc2(auVar9);
        auVar12._4_4_ = fStack_ac;
        auVar12._0_4_ = fStack_b0;
        auVar12._8_4_ = fStack_a8;
        auVar12._12_4_ = fStack_a4;
        auVar39 = _lqc2(auVar12);
        auVar38 = _vadd(auVar38,auVar39);
        auStack_440 = _sqc2(auVar38);
        __ct__7FVectorFRC7FVector(auStack_280,auStack_440);
        auVar38 = _lqc2(auStack_280);
        auVar14._4_4_ = fStack_9c;
        auVar14._0_4_ = fStack_a0;
        auVar14._8_4_ = fStack_98;
        auVar14._12_4_ = fStack_94;
        auVar39 = _lqc2(auVar14);
        auVar38 = _vadd(auVar38,auVar39);
        auStack_450 = _sqc2(auVar38);
        __ct__7FVectorFRC7FVector(auStack_270,auStack_450);
        auVar38 = _lqc2(auStack_270);
        auVar16._4_4_ = fStack_8c;
        auVar16._0_4_ = fStack_90;
        auVar16._8_4_ = fStack_88;
        auVar16._12_4_ = fStack_84;
        auVar39 = _lqc2(auVar16);
        auVar38 = _vadd(auVar38,auVar39);
        auStack_460 = _sqc2(auVar38);
        __ct__7FVectorFRC7FVector(auStack_260,auStack_460);
        auVar38 = _lqc2(auStack_260);
        auVar19._4_4_ = fStack_7c;
        auVar19._0_4_ = fStack_80;
        auVar19._8_4_ = fStack_78;
        auVar19._12_4_ = fStack_74;
        auVar39 = _lqc2(auVar19);
        auVar38 = _vadd(auVar38,auVar39);
        auStack_470 = _sqc2(auVar38);
        __ct__7FVectorFRC7FVector(auStack_250,auStack_470);
        auVar38 = _lqc2(auStack_250);
        auVar22._4_4_ = fStack_6c;
        auVar22._0_4_ = fStack_70;
        auVar22._8_4_ = fStack_68;
        auVar22._12_4_ = fStack_64;
        auVar39 = _lqc2(auVar22);
        auVar38 = _vadd(auVar38,auVar39);
        auStack_480 = _sqc2(auVar38);
        __ct__7FVectorFRC7FVector(auStack_240,auStack_480);
        auVar38 = _lqc2(auStack_240);
        auVar25._4_4_ = fStack_5c;
        auVar25._0_4_ = fStack_60;
        auVar25._8_4_ = fStack_58;
        auVar25._12_4_ = fStack_54;
        auVar39 = _lqc2(auVar25);
        auVar38 = _vadd(auVar38,auVar39);
        auStack_490 = _sqc2(auVar38);
        __ct__7FVectorFRC7FVector(auStack_230,auStack_490);
        auVar38 = _lqc2(auStack_230);
        auVar28._4_4_ = fStack_4c;
        auVar28._0_4_ = fStack_50;
        auVar28._8_4_ = fStack_48;
        auVar28._12_4_ = fStack_44;
        auVar39 = _lqc2(auVar28);
        auVar38 = _vadd(auVar38,auVar39);
        auStack_3a0 = _sqc2(auVar38);
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
        auVar39 = _lqc2(auVar4);
        auVar38 = _lqc2(_auStack_140);
        auVar38 = _vadd(auVar38,auVar39);
        _auStack_140 = _sqc2(auVar38);
        __adv__7FVectorFf(0x40000000,auStack_140);
      }
      else {
        fStack_1e8 = *(float *)(iVar30 + *(short *)(iVar36 + 0x60) * 0x20 + 0x10);
        fStack_1ec = *(float *)(iVar30 + *(short *)(iVar36 + 0x60) * 0x20 + 0xc);
        fStack_1f0 = *(float *)(iVar30 + *(short *)(iVar36 + 0x60) * 0x20 + 8);
        uStack_1e4 = 0x3f800000;
        fStack_b4 = 1.0;
        uStack_208 = *(undefined4 *)(iVar30 + *(short *)(iVar36 + 0x60) * 0x20 + 0x1c);
        uStack_20c = *(undefined4 *)(iVar30 + *(short *)(iVar36 + 0x60) * 0x20 + 0x18);
        uStack_210 = *(undefined4 *)(iVar30 + *(short *)(iVar36 + 0x60) * 0x20 + 0x14);
        uStack_204 = 0x3f800000;
        auVar8._4_4_ = fStack_1ec;
        auVar8._0_4_ = fStack_1f0;
        auVar8._8_4_ = fStack_1e8;
        auVar8._12_4_ = 0x3f800000;
        auVar38 = _lqc2(auVar8);
        auVar2._4_4_ = uStack_20c;
        auVar2._0_4_ = uStack_210;
        auVar2._8_4_ = uStack_208;
        auVar2._12_4_ = 0x3f800000;
        auVar39 = _lqc2(auVar2);
        auVar38 = _vadd(auVar38,auVar39);
        auStack_390 = _sqc2(auVar38);
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
        auVar39 = _lqc2(auVar5);
        auVar38 = _lqc2(_auStack_140);
        auVar38 = _vadd(auVar38,auVar39);
        _auStack_140 = _sqc2(auVar38);
        __adv__7FVectorFf(0x40000000,auStack_140);
      }
    }
  }
  else {
    if (*(short *)(iVar30 + 2) == 2) {
      pbVar31 = (byte *)(*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar36 + 0x48) * 0x4f0 +
                                                   0x144) + 0x530) + 0xe4) +
                        *(short *)(iVar30 + *(short *)(iVar36 + 0x60) * 0x20 + 6) * 0x110);
      pauVar35 = (undefined1 (*) [16])
                 (*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar36 + 0x48) * 0x4f0 + 0x144)
                                   + 0x530) + 0x30) + (uint)*pbVar31 * 0x1f0 +
                 (bGpffff8340 & 1) * 0x40);
      auStack_40 = *pauVar35;
      auStack_30 = pauVar35[1];
      auStack_20 = pauVar35[2];
      auStack_10 = pauVar35[3];
    }
    else if (*(short *)(iVar30 + 2) == 1) {
      pbVar31 = (byte *)(*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar36 + 0x48) * 0x4f0 +
                                                   0x144) + 0x52c) + 0xe4) +
                        *(short *)(iVar30 + *(short *)(iVar36 + 0x60) * 0x20 + 6) * 0x110);
      pauVar35 = (undefined1 (*) [16])
                 (*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar36 + 0x48) * 0x4f0 + 0x144)
                                   + 0x52c) + 0x30) + (uint)*pbVar31 * 0x1f0 +
                 (bGpffff8340 & 1) * 0x40);
      auStack_40 = *pauVar35;
      auStack_30 = pauVar35[1];
      auStack_20 = pauVar35[2];
      auStack_10 = pauVar35[3];
    }
    else {
      pbVar31 = (byte *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar36 + 0x48) * 0x4f0 + 0x144) +
                                 0xe4) +
                        *(short *)(iVar30 + *(short *)(iVar36 + 0x60) * 0x20 + 6) * 0x110);
      pauVar35 = (undefined1 (*) [16])
                 (*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar36 + 0x48) * 0x4f0 + 0x144) + 0x30) +
                  (uint)*pbVar31 * 0x1f0 + (bGpffff8340 & 1) * 0x40);
      auStack_40 = *pauVar35;
      auStack_30 = pauVar35[1];
      auStack_20 = pauVar35[2];
      auStack_10 = pauVar35[3];
    }
    if (((*(float *)(iVar30 + *(short *)(iVar36 + 0x60) * 0x20 + 8) == 0.0) &&
        (*(float *)(iVar30 + *(short *)(iVar36 + 0x60) * 0x20 + 0xc) == 0.0)) &&
       (*(float *)(iVar30 + *(short *)(iVar36 + 0x60) * 0x20 + 0x10) == 0.0)) {
      RotTransVector(&fStack_c0,pbVar31 + 0x10,auStack_40,8);
      auVar38._4_4_ = fStack_bc;
      auVar38._0_4_ = fStack_c0;
      auVar38._8_4_ = fStack_b8;
      auVar38._12_4_ = fStack_b4;
      auVar38 = _lqc2(auVar38);
      auVar39._4_4_ = fStack_ac;
      auVar39._0_4_ = fStack_b0;
      auVar39._8_4_ = fStack_a8;
      auVar39._12_4_ = fStack_a4;
      auVar39 = _lqc2(auVar39);
      auVar38 = _vadd(auVar38,auVar39);
      auStack_4a0 = _sqc2(auVar38);
      __ct__7FVectorFRC7FVector(auStack_320,auStack_4a0);
      auVar38 = _lqc2(auStack_320);
      auVar40._4_4_ = fStack_9c;
      auVar40._0_4_ = fStack_a0;
      auVar40._8_4_ = fStack_98;
      auVar40._12_4_ = fStack_94;
      auVar39 = _lqc2(auVar40);
      auVar38 = _vadd(auVar38,auVar39);
      auStack_4b0 = _sqc2(auVar38);
      __ct__7FVectorFRC7FVector(auStack_310,auStack_4b0);
      auVar38 = _lqc2(auStack_310);
      auVar17._4_4_ = fStack_8c;
      auVar17._0_4_ = fStack_90;
      auVar17._8_4_ = fStack_88;
      auVar17._12_4_ = fStack_84;
      auVar39 = _lqc2(auVar17);
      auVar38 = _vadd(auVar38,auVar39);
      auStack_4c0 = _sqc2(auVar38);
      __ct__7FVectorFRC7FVector(auStack_300,auStack_4c0);
      auVar38 = _lqc2(auStack_300);
      auVar20._4_4_ = fStack_7c;
      auVar20._0_4_ = fStack_80;
      auVar20._8_4_ = fStack_78;
      auVar20._12_4_ = fStack_74;
      auVar39 = _lqc2(auVar20);
      auVar38 = _vadd(auVar38,auVar39);
      auStack_4d0 = _sqc2(auVar38);
      __ct__7FVectorFRC7FVector(auStack_2f0,auStack_4d0);
      auVar38 = _lqc2(auStack_2f0);
      auVar23._4_4_ = fStack_6c;
      auVar23._0_4_ = fStack_70;
      auVar23._8_4_ = fStack_68;
      auVar23._12_4_ = fStack_64;
      auVar39 = _lqc2(auVar23);
      auVar38 = _vadd(auVar38,auVar39);
      auStack_4e0 = _sqc2(auVar38);
      __ct__7FVectorFRC7FVector(auStack_2e0,auStack_4e0);
      auVar38 = _lqc2(auStack_2e0);
      auVar26._4_4_ = fStack_5c;
      auVar26._0_4_ = fStack_60;
      auVar26._8_4_ = fStack_58;
      auVar26._12_4_ = fStack_54;
      auVar39 = _lqc2(auVar26);
      auVar38 = _vadd(auVar38,auVar39);
      auStack_4f0 = _sqc2(auVar38);
      __ct__7FVectorFRC7FVector(auStack_2d0,auStack_4f0);
      auVar38 = _lqc2(auStack_2d0);
      auVar29._4_4_ = fStack_4c;
      auVar29._0_4_ = fStack_50;
      auVar29._8_4_ = fStack_48;
      auVar29._12_4_ = fStack_44;
      auVar39 = _lqc2(auVar29);
      auVar38 = _vadd(auVar38,auVar39);
      auStack_3c0 = _sqc2(auVar38);
      __ct__7FVectorFRC7FVector(&uStack_2c0,auStack_3c0);
      fStack_138 = (float)uStack_2b8;
      auStack_140 = (undefined1  [8])uStack_2c0;
      fStack_134 = (float)uStack_2b4;
      __adv__7FVectorFf(0x41000000,auStack_140);
    }
    else {
      fStack_288 = *(float *)(iVar30 + *(short *)(iVar36 + 0x60) * 0x20 + 0x10);
      fStack_28c = *(float *)(iVar30 + *(short *)(iVar36 + 0x60) * 0x20 + 0xc);
      fStack_290 = *(float *)(iVar30 + *(short *)(iVar36 + 0x60) * 0x20 + 8);
      uStack_284 = 0x3f800000;
      fStack_b4 = 1.0;
      uStack_2a8 = *(undefined4 *)(iVar30 + *(short *)(iVar36 + 0x60) * 0x20 + 0x1c);
      uStack_2ac = *(undefined4 *)(iVar30 + *(short *)(iVar36 + 0x60) * 0x20 + 0x18);
      uStack_2b0 = *(undefined4 *)(iVar30 + *(short *)(iVar36 + 0x60) * 0x20 + 0x14);
      uStack_2a4 = 0x3f800000;
      auVar10._4_4_ = fStack_28c;
      auVar10._0_4_ = fStack_290;
      auVar10._8_4_ = fStack_288;
      auVar10._12_4_ = 0x3f800000;
      auVar38 = _lqc2(auVar10);
      auVar1._4_4_ = uStack_2ac;
      auVar1._0_4_ = uStack_2b0;
      auVar1._8_4_ = uStack_2a8;
      auVar1._12_4_ = 0x3f800000;
      auVar39 = _lqc2(auVar1);
      auVar38 = _vadd(auVar38,auVar39);
      auStack_3b0 = _sqc2(auVar38);
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
  for (iVar30 = 0; iVar30 < 0x10; iVar30 = iVar30 + 1) {
    iVar32 = iVar36 + iVar30 * 0x10;
    *(int *)(iVar32 + 0x70) = auStack_140._0_4_;
    *(int *)(iVar32 + 0x74) = auStack_140._4_4_;
    *(float *)(iVar32 + 0x78) = fStack_138;
    *(float *)(iVar32 + 0x7c) = fStack_134;
  }
  *(undefined2 *)(iVar36 + 0x19e) = 1;
  fVar37 = 0.0;
  if (-1 < *(int *)(iVar36 + 0x5c)) {
    auVar38 = _lqc2(*(undefined1 (*) [16])(iGpffff86b4 + *(int *)(iVar36 + 0x5c) * 0x4f0 + 0x150));
    auVar39 = _lqc2(*(undefined1 (*) [16])(iGpffff86b4 + *(int *)(iVar36 + 0x5c) * 0x4f0 + 0x350));
    auVar38 = _vadd(auVar38,auVar39);
    auStack_500 = _sqc2(auVar38);
    __ct__7FVectorFRC7FVector(auStack_340,auStack_500);
    auVar38 = _lqc2(auStack_340);
    auVar39 = _lqc2(*(undefined1 (*) [16])(iVar36 + 0x70));
    auVar38 = _vsub(auVar38,auVar39);
    auStack_3d0 = _sqc2(auVar38);
    __ct__7FVectorFRC7FVector(auStack_330,auStack_3d0);
    fStack_c0 = auStack_330._0_4_;
    fStack_bc = auStack_330._4_4_;
    fStack_b8 = fStack_328;
    fStack_b4 = fStack_324;
    uVar33 = __ct__7FVectorFRC7FVector(auStack_360,&fStack_c0);
    Get3DAngle__F7FVector(auStack_350,uVar33);
    fStack_ac = auStack_350._4_4_;
    fStack_a8 = fStack_348;
    fStack_a4 = fStack_344;
    fStack_b0 = auStack_350._0_4_;
    for (fVar37 = fStack_b0; fVar37 < -180.0; fVar37 = fVar37 + 360.0) {
    }
    for (; 180.0 <= fVar37; fVar37 = fVar37 - 360.0) {
    }
  }
  *(float *)(iVar36 + 0x170) = fVar37 / 2.0;
  *(undefined4 *)(iVar36 + 0x174) =
       *(undefined4 *)(iGpffff86b4 + *(int *)(iVar36 + 0x48) * 0x4f0 + 0x174);
  *(undefined4 *)(iVar36 + 0x178) = 0;
  *(undefined4 *)(iVar36 + 0x17c) = 0x3f800000;
  Entry__7CPollerFP7CPolObjib(iGpffff858c + 0x48,param_2,0x80,0);
  BtlEffEntry__7CBattleFiP6BtlEff(iGpffff86b4,*(undefined4 *)(iVar36 + 0x48),param_2);
  return param_2;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00545530  __dt__7Bullet4Fv
 * C++: Bullet4::__dt()
 * size: 0x154 bytes
 * --------------------------------------------------------------------------- */
int __dt__7Bullet4Fv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x14) = 0x409980;
    *(undefined4 *)(param_1 + 0x28) = 0x409990;
    *(undefined4 *)(param_1 + 0x34) = 0x4099a0;
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
 * JP: 0x00545690  Destruct__7Bullet4Fv
 * C++: Bullet4::Destruct()
 * size: 0xcc bytes
 * --------------------------------------------------------------------------- */
void Destruct__7Bullet4Fv(int param_1)

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
 * JP: 0x00545760  Polling__7Bullet4Fv
 * C++: Bullet4::Polling()
 * size: 0x924 bytes
 * --------------------------------------------------------------------------- */
undefined4 Polling__7Bullet4Fv(int param_1)

{
  float in_zero_lo;
  float in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  char cVar1;
  int iVar2;
  FVector *pFVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  undefined4 uVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  undefined1 in_vf0 [16];
  undefined1 auVar14 [16];
  undefined1 auVar15 [16];
  undefined1 auVar16 [16];
  undefined1 auStack_130 [16];
  undefined1 auStack_120 [16];
  undefined1 auStack_110 [16];
  undefined1 auStack_100 [16];
  undefined1 auStack_f0 [16];
  undefined1 auStack_e0 [16];
  undefined1 auStack_d0 [16];
  undefined4 uStack_c0;
  undefined4 uStack_bc;
  float fStack_b8;
  undefined4 uStack_b4;
  undefined8 uStack_b0;
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  undefined1 auStack_a0 [16];
  undefined1 auStack_90 [8];
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined1 auStack_80 [16];
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
  
  auVar14 = _vmr32(in_vf0);
  auVar15 = _vmr32(auVar14);
  auVar16 = _vmr32(auVar15);
  auStack_30 = _sqc2(in_vf0);
  auStack_40 = _sqc2(auVar14);
  auStack_50 = _sqc2(auVar15);
  auStack_60 = _sqc2(auVar16);
  fVar13 = pCGpffff86b4->flDeltaT;
  if ((pCGpffff86b4->bFlags24 & 1) != 0) {
    fVar13 = 0.0;
  }
  fStack_20 = in_zero_lo;
  fStack_1c = in_zero_hi;
  uStack_18 = in_zero_udw;
  uStack_14 = in_register_0000000c;
  fStack_10 = in_zero_lo;
  fStack_c = in_zero_hi;
  uStack_8 = in_zero_udw;
  uStack_4 = in_register_0000000c;
  if (*(short *)(param_1 + 0x19c) == 0) {
    if ((-1 < *(int *)(param_1 + 0x5c)) && (fVar13 != 0.0)) {
      auVar14 = _lqc2(*(undefined1 (*) [16])pCGpffff86b4->aChr[*(int *)(param_1 + 0x5c)].aPos);
      auVar15 = _lqc2(*(undefined1 (*) [16])
                       &pCGpffff86b4->aChr[*(int *)(param_1 + 0x5c)].field_0x2a0);
      auVar14 = _vadd(auVar14,auVar15);
      auStack_130 = _sqc2(auVar14);
      __ct__7FVectorFRC7FVector(auStack_80,auStack_130);
      auVar14 = _lqc2(auStack_80);
      auVar15 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x70));
      auVar14 = _vsub(auVar14,auVar15);
      auStack_120 = _sqc2(auVar14);
      __ct__7FVectorFRC7FVector(auStack_70,auStack_120);
      fStack_10 = auStack_70._0_4_;
      fStack_c = auStack_70._4_4_;
      uStack_8 = uStack_68;
      uStack_4 = uStack_64;
      uVar4 = __ct__7FVectorFRC7FVector(auStack_a0,&fStack_10);
      Get3DAngle__F7FVector(auStack_90,uVar4);
      fStack_20 = auStack_90._0_4_;
      fStack_1c = auStack_90._4_4_;
      uStack_18 = uStack_88;
      uStack_14 = uStack_84;
      for (fVar10 = fStack_20 - *(float *)(param_1 + 0x170); fVar10 < -180.0;
          fVar10 = fVar10 + 360.0) {
      }
      for (; 180.0 <= fVar10; fVar10 = fVar10 - 360.0) {
      }
      fVar12 = fVar13 * 10.0 * 30.0;
      fVar11 = fVar12;
      if (fVar10 <= fVar12) {
        fVar11 = fVar10;
      }
      if (fVar11 < -fVar12) {
        fVar11 = -fVar12;
      }
      *(float *)(param_1 + 0x170) = *(float *)(param_1 + 0x170) + fVar11;
      for (fVar10 = (180.0 - fStack_1c) - *(float *)(param_1 + 0x174); fVar10 < -180.0;
          fVar10 = fVar10 + 360.0) {
      }
      for (; 180.0 <= fVar10; fVar10 = fVar10 - 360.0) {
      }
      fVar11 = fVar12;
      if (fVar10 <= fVar12) {
        fVar11 = fVar10;
      }
      if (fVar11 < -fVar12) {
        fVar11 = -fVar12;
      }
      *(float *)(param_1 + 0x174) = *(float *)(param_1 + 0x174) + fVar11;
    }
    if (fVar13 != 0.0) {
      auVar14 = _vmr32(in_vf0);
      auVar15 = _vmr32(auVar14);
      auVar16 = _vmr32(auVar15);
      auStack_30 = _sqc2(in_vf0);
      auStack_40 = _sqc2(auVar14);
      auStack_50 = _sqc2(auVar15);
      auStack_60 = _sqc2(auVar16);
      uVar9 = GetRad(*(undefined4 *)(param_1 + 0x170));
      sceVu0RotMatrixX(uVar9,auStack_60,auStack_60);
      uVar9 = GetRad(*(undefined4 *)(param_1 + 0x174));
      sceVu0RotMatrixY(uVar9,auStack_60,auStack_60);
      uStack_c0 = 0;
      uStack_bc = 0;
      fStack_b8 = fVar13 * -10.0 * 30.0;
      uStack_b4 = 0x3f800000;
      ApplyMatrix__6MatrixCFRC7FVector(&uStack_b0,auStack_60,&uStack_c0);
      fStack_10 = (float)uStack_b0;
      fStack_c = (float)((ulong)uStack_b0 >> 0x20);
      uStack_8 = uStack_a8;
      uStack_4 = uStack_a4;
      *(short *)(param_1 + 0x19e) = *(short *)(param_1 + 0x19e) + 1;
      if (0xf < *(short *)(param_1 + 0x19e)) {
        *(undefined2 *)(param_1 + 0x19e) = 0x10;
      }
      iVar8 = (int)*(short *)(param_1 + 0x19e);
      while (iVar7 = iVar8 + -1, 0 < iVar7) {
        iVar2 = param_1 + iVar7 * 0x10;
        iVar8 = param_1 + (iVar8 + -2) * 0x10;
        uVar4 = *(undefined8 *)(iVar8 + 0x70);
        uVar9 = *(undefined4 *)(iVar8 + 0x78);
        uVar6 = *(undefined4 *)(iVar8 + 0x7c);
        *(int *)(iVar2 + 0x70) = (int)uVar4;
        *(int *)(iVar2 + 0x74) = (int)((ulong)uVar4 >> 0x20);
        *(undefined4 *)(iVar2 + 0x78) = uVar9;
        *(undefined4 *)(iVar2 + 0x7c) = uVar6;
        iVar8 = iVar7;
      }
      auVar14._8_4_ = uStack_a8;
      auVar14._0_8_ = uStack_b0;
      auVar14._12_4_ = uStack_a4;
      auVar15 = _lqc2(auVar14);
      auVar14 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x70));
      auVar14 = _vadd(auVar14,auVar15);
      auVar14 = _sqc2(auVar14);
      *(undefined1 (*) [16])(param_1 + 0x70) = auVar14;
    }
    if (((long)((ulong)*(byte *)(param_1 + 0x40) << 0x3d) < 0) && (fVar13 != 0.0)) {
      *(undefined2 *)(param_1 + 0x19c) = 1;
    }
    if (*(float *)(param_1 + 0x80) < (-*(float *)&pCGpffff86b4->field_0x3f14 - 10.0) / 2.0) {
      *(undefined2 *)(param_1 + 0x19c) = 1;
    }
    if ((*(float *)&pCGpffff86b4->field_0x3f14 + 10.0) / 2.0 < *(float *)(param_1 + 0x80)) {
      *(undefined2 *)(param_1 + 0x19c) = 1;
    }
    if (0.0 < *(float *)(param_1 + 0x84)) {
      *(undefined2 *)(param_1 + 0x19c) = 1;
    }
    if (*(float *)(param_1 + 0x88) < (-*(float *)&pCGpffff86b4->field_0x3f1c - 10.0) / 2.0) {
      *(undefined2 *)(param_1 + 0x19c) = 1;
    }
    if ((*(float *)&pCGpffff86b4->field_0x3f1c + 10.0) / 2.0 < *(float *)(param_1 + 0x88)) {
      *(undefined2 *)(param_1 + 0x19c) = 1;
    }
    if (((((-1 < *(int *)(param_1 + 0x5c)) &&
          (-1 < (long)((ulong)*(byte *)(param_1 + 0x40) << 0x3d))) &&
         (*(short *)(param_1 + 0x19c) == 0)) &&
        ((-1 < (long)((ulong)pCGpffff86b4->aChr[*(int *)(param_1 + 0x5c)].bFlagsB << 0x3c) &&
         (pCGpffff86b4->aChr[*(int *)(param_1 + 0x5c)].bState != 0x29)))) &&
       (pCGpffff86b4->aChr[*(int *)(param_1 + 0x5c)].bState != 0x2c)) {
      uVar4 = __ct__7FVectorFRC7FVector(auStack_d0,param_1 + 0x70);
      cVar1 = VSCircleHitCheck__7CBattleFi7FVectorfP7FVector
                        (0x3f800000,pCGpffff86b4,*(undefined4 *)(param_1 + 0x5c),uVar4,&fStack_10);
      if (cVar1 == '\x01') {
        pFVar3 = (FVector *)__ct__7FVectorFRC7FVector(auStack_e0,&fStack_10);
        PAtkHitSet__7CBattleFii7FVectorfiiiiUsUsfii
                  (pCGpffff86b4,*(int *)(param_1 + 0x48),*(int *)(param_1 + 0x5c),pFVar3,
                   *(float *)(param_1 + 0x174),*(int *)(param_1 + 0x180),*(int *)(param_1 + 0x184),
                   *(int *)(param_1 + 0x188),*(int *)(param_1 + 0x18c),*(ushort *)(param_1 + 400),
                   *(ushort *)(param_1 + 0x192),*(float *)(param_1 + 100),*(int *)(param_1 + 0x194),
                   *(int *)(param_1 + 0x198));
        *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfb | 4;
      }
      else {
        uVar4 = __ct__7FVectorFRC7FVector(auStack_f0,param_1 + 0x70);
        uVar5 = __ct__7FVectorFRC7FVector(auStack_100,param_1 + 0x80);
        cVar1 = VSLineHitCheck__7CBattleFi7FVector7FVectorP7FVector
                          (pCGpffff86b4,*(undefined4 *)(param_1 + 0x5c),uVar4,uVar5,&fStack_10);
        if (cVar1 == '\x01') {
          pFVar3 = (FVector *)__ct__7FVectorFRC7FVector(auStack_110,&fStack_10);
          PAtkHitSet__7CBattleFii7FVectorfiiiiUsUsfii
                    (pCGpffff86b4,*(int *)(param_1 + 0x48),*(int *)(param_1 + 0x5c),pFVar3,
                     *(float *)(param_1 + 0x174),*(int *)(param_1 + 0x180),*(int *)(param_1 + 0x184)
                     ,*(int *)(param_1 + 0x188),*(int *)(param_1 + 0x18c),*(ushort *)(param_1 + 400)
                     ,*(ushort *)(param_1 + 0x192),*(float *)(param_1 + 100),
                     *(int *)(param_1 + 0x194),*(int *)(param_1 + 0x198));
          *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfb | 4;
        }
      }
    }
  }
  else if (fVar13 != 0.0) {
    *(short *)(param_1 + 0x19e) = *(short *)(param_1 + 0x19e) + -1;
  }
  if ((*(short *)(param_1 + 0x19c) == 0) || (1 < *(short *)(param_1 + 0x19e))) {
    uVar9 = 0;
  }
  else {
    BtlEffRelease__7CBattleFiP6BtlEff(pCGpffff86b4,*(undefined4 *)(param_1 + 0x48),param_1);
    if ((long)((ulong)*(byte *)(param_1 + 0x40) << 0x3e) < 0) {
      iVar8 = param_1;
      if (param_1 != 0) {
        iVar8 = param_1 + 0x18;
      }
      ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,iVar8);
    }
    *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfd;
    (**(code **)(*(int *)(param_1 + 0x34) + 0xc))();
    uVar9 = 1;
  }
  return uVar9;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00546090  MakePacket__7Bullet4Fv
 * C++: Bullet4::MakePacket()
 * size: 0x2334 bytes
 * --------------------------------------------------------------------------- */
void MakePacket__7Bullet4Fv(int param_1)

{
  bool bVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined1 auVar4 [16];
  undefined1 auVar5 [16];
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  bool bVar8;
  undefined1 auVar9 [16];
  undefined1 auVar10 [16];
  undefined1 auVar11 [16];
  undefined1 auVar12 [16];
  undefined1 auVar13 [16];
  float in_zero_lo;
  float in_zero_hi;
  float in_zero_udw;
  float in_register_0000000c;
  int iVar14;
  undefined8 uVar15;
  float *pfVar16;
  uint uVar17;
  int iVar18;
  undefined8 in_v1_udw;
  uint uVar19;
  int iVar20;
  long lVar21;
  float fVar22;
  undefined4 uVar23;
  undefined1 in_vf0 [16];
  undefined1 auVar24 [16];
  undefined1 auVar25 [16];
  undefined1 auVar26 [16];
  undefined1 auStack_b30 [16];
  undefined1 auStack_b20 [16];
  undefined1 auStack_b10 [16];
  undefined1 auStack_b00 [16];
  undefined1 auStack_af0 [16];
  undefined1 auStack_ae0 [16];
  undefined1 auStack_ad0 [16];
  undefined1 auStack_ac0 [16];
  undefined1 auStack_ab0 [16];
  undefined1 auStack_aa0 [16];
  undefined1 auStack_a90 [64];
  undefined1 auStack_a50 [8];
  float fStack_a48;
  float fStack_a44;
  undefined1 auStack_a40 [8];
  float fStack_a38;
  float fStack_a34;
  undefined1 auStack_a30 [8];
  float fStack_a28;
  float fStack_a24;
  undefined1 auStack_a20 [8];
  float fStack_a18;
  float fStack_a14;
  undefined4 uStack_a10;
  undefined4 uStack_a0c;
  undefined4 uStack_a08;
  undefined4 uStack_a04;
  undefined4 uStack_a00;
  undefined4 uStack_9fc;
  undefined4 uStack_9f8;
  undefined4 uStack_9f4;
  undefined4 uStack_9f0;
  undefined4 uStack_9ec;
  undefined4 uStack_9e8;
  undefined4 uStack_9e4;
  undefined4 uStack_9e0;
  undefined4 uStack_9dc;
  undefined4 uStack_9d8;
  undefined4 uStack_9d4;
  undefined1 auStack_9d0 [16];
  undefined1 auStack_9c0 [8];
  float fStack_9b8;
  float fStack_9b4;
  undefined1 auStack_9b0 [16];
  undefined1 auStack_9a0 [8];
  float fStack_998;
  float fStack_994;
  undefined1 auStack_990 [16];
  undefined1 auStack_980 [8];
  float fStack_978;
  float fStack_974;
  float fStack_970;
  float fStack_96c;
  undefined4 uStack_968;
  undefined4 uStack_964;
  float fStack_960;
  float fStack_95c;
  undefined4 uStack_958;
  undefined4 uStack_954;
  float fStack_950;
  float fStack_94c;
  undefined4 uStack_948;
  undefined4 uStack_944;
  undefined1 auStack_940 [16];
  undefined1 auStack_930 [8];
  float fStack_928;
  float fStack_924;
  undefined1 auStack_920 [8];
  undefined4 uStack_918;
  undefined4 uStack_914;
  undefined1 auStack_910 [8];
  undefined4 uStack_908;
  undefined4 uStack_904;
  undefined1 auStack_900 [8];
  undefined4 uStack_8f8;
  undefined4 uStack_8f4;
  int aiStack_8f0 [6];
  int iStack_8d8;
  int iStack_8d0;
  int iStack_8cc;
  int iStack_8c8;
  undefined4 auStack_5b0 [16];
  undefined1 auStack_570 [64];
  undefined4 uStack_530;
  undefined4 uStack_52c;
  undefined4 uStack_528;
  undefined4 uStack_524;
  undefined4 uStack_520;
  undefined4 uStack_51c;
  undefined4 uStack_518;
  undefined4 uStack_514;
  undefined4 uStack_510;
  undefined4 uStack_50c;
  undefined4 uStack_508;
  undefined4 uStack_504;
  undefined4 uStack_500;
  undefined4 uStack_4fc;
  undefined4 uStack_4f8;
  undefined4 uStack_4f4;
  float fStack_4c0;
  float fStack_4bc;
  undefined4 uStack_4b8;
  undefined4 uStack_4b4;
  float fStack_4b0;
  float fStack_4ac;
  undefined4 uStack_4a8;
  undefined4 uStack_4a4;
  float fStack_4a0;
  float fStack_49c;
  undefined4 uStack_498;
  undefined4 uStack_494;
  undefined1 auStack_490 [16];
  undefined1 auStack_480 [16];
  undefined1 auStack_470 [16];
  undefined1 auStack_460 [16];
  float afStack_450 [272];
  float fStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  fStack_10 = 0.0;
  uStack_c = 0;
  uStack_8 = 0;
  uStack_4 = 0x3f800000;
  pfVar16 = afStack_450 + 0xd0;
  do {
    *pfVar16 = in_zero_lo;
    pfVar16[1] = in_zero_hi;
    pfVar16[2] = in_zero_udw;
    pfVar16[3] = in_register_0000000c;
    pfVar16 = pfVar16 + 4;
  } while (pfVar16 != &fStack_10);
  lVar21 = 0;
  while (lVar21 < *(short *)(param_1 + 0x19e)) {
    iVar14 = (int)lVar21;
    if (1 < *(short *)(param_1 + 0x19e)) {
      if (lVar21 == 0) {
        auVar24 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x80));
        auVar25 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x70));
        auVar24 = _vsub(auVar24,auVar25);
        auStack_aa0 = _sqc2(auVar24);
        __ct__7FVectorFRC7FVector(auStack_900,auStack_aa0);
        fStack_10 = auStack_900._0_4_;
        uStack_c = auStack_900._4_4_;
        uStack_8 = uStack_8f8;
        uStack_4 = uStack_8f4;
      }
      else if ((long)(iVar14 + 1) < (long)*(short *)(param_1 + 0x19e)) {
        auVar24 = _lqc2(*(undefined1 (*) [16])(param_1 + (iVar14 + 1) * 0x10 + 0x70));
        auVar25 = _lqc2(*(undefined1 (*) [16])(param_1 + iVar14 * 0x10 + 0x70));
        auVar24 = _vsub(auVar24,auVar25);
        auStack_ab0 = _sqc2(auVar24);
        __ct__7FVectorFRC7FVector(auStack_910,auStack_ab0);
        fStack_10 = auStack_910._0_4_;
        uStack_c = auStack_910._4_4_;
        uStack_8 = uStack_908;
        uStack_4 = uStack_904;
      }
      else {
        auVar24 = _lqc2(*(undefined1 (*) [16])(param_1 + iVar14 * 0x10 + 0x70));
        auVar25 = _lqc2(*(undefined1 (*) [16])(param_1 + (iVar14 + -1) * 0x10 + 0x70));
        auVar24 = _vsub(auVar24,auVar25);
        auStack_ac0 = _sqc2(auVar24);
        __ct__7FVectorFRC7FVector(auStack_920,auStack_ac0);
        fStack_10 = auStack_920._0_4_;
        uStack_c = auStack_920._4_4_;
        uStack_8 = uStack_918;
        uStack_4 = uStack_914;
      }
    }
    uVar15 = __ct__7FVectorFRC7FVector(auStack_940,&fStack_10);
    Get3DAngleRad__F7FVector(auStack_930,uVar15);
    afStack_450[iVar14 * 4 + 0xd0] = auStack_930._0_4_;
    afStack_450[iVar14 * 4 + 0xd1] = auStack_930._4_4_;
    afStack_450[iVar14 * 4 + 0xd2] = fStack_928;
    afStack_450[iVar14 * 4 + 0xd3] = fStack_924;
    lVar21 = (long)(iVar14 + 1);
  }
  pfVar16 = afStack_450;
  do {
    *pfVar16 = in_zero_lo;
    pfVar16[1] = in_zero_hi;
    pfVar16[2] = in_zero_udw;
    pfVar16[3] = in_register_0000000c;
    pfVar16 = pfVar16 + 4;
  } while (pfVar16 != afStack_450 + 0xd0);
  auVar24 = _vmr32(in_vf0);
  auVar25 = _vmr32(auVar24);
  auVar26 = _vmr32(auVar25);
  auStack_460 = _sqc2(in_vf0);
  auStack_470 = _sqc2(auVar24);
  auStack_480 = _sqc2(auVar25);
  auStack_490 = _sqc2(auVar26);
  fVar22 = (float)sinf(0);
  fStack_950 = (float)cosf(0);
  fStack_950 = fStack_950 * 0.5;
  uStack_948 = 0;
  uStack_944 = 0x3f800000;
  uStack_4b8 = 0;
  uStack_4b4 = 0x3f800000;
  fStack_94c = -fVar22 * 0.5;
  fStack_4c0 = fStack_950;
  fStack_4bc = -fVar22 * 0.5;
  fVar22 = (float)sinf(0x40060a92);
  fStack_960 = (float)cosf(0x40060a92);
  fStack_960 = fStack_960 * 0.5;
  uStack_958 = 0;
  uStack_954 = 0x3f800000;
  uStack_4a8 = 0;
  uStack_4a4 = 0x3f800000;
  fStack_95c = -fVar22 * 0.5;
  fStack_4b0 = fStack_960;
  fStack_4ac = -fVar22 * 0.5;
  fVar22 = (float)sinf(0xc0060a92);
  fStack_970 = (float)cosf(0xc0060a92);
  fStack_970 = fStack_970 * 0.5;
  uStack_968 = 0;
  uStack_964 = 0x3f800000;
  uStack_498 = 0;
  uStack_494 = 0x3f800000;
  lVar21 = 0;
  fStack_96c = -fVar22 * 0.5;
  fStack_4a0 = fStack_970;
  fStack_49c = -fVar22 * 0.5;
  while (lVar21 < *(short *)(param_1 + 0x19e)) {
    iVar14 = (int)lVar21;
    if (lVar21 == 0) {
      afStack_450[2] = *(float *)(param_1 + 0x78);
      afStack_450[3] = *(float *)(param_1 + 0x7c);
      afStack_450[0] = (float)*(undefined8 *)(param_1 + 0x70);
      afStack_450[1] = (float)((ulong)*(undefined8 *)(param_1 + 0x70) >> 0x20);
      afStack_450[4] = afStack_450[0];
      afStack_450[5] = afStack_450[1];
      afStack_450[6] = afStack_450[2];
      afStack_450[7] = afStack_450[3];
      afStack_450[8] = afStack_450[0];
      afStack_450[9] = afStack_450[1];
      afStack_450[10] = afStack_450[2];
      afStack_450[0xb] = afStack_450[3];
    }
    else {
      auVar24 = _vmr32(in_vf0);
      auVar25 = _vmr32(auVar24);
      auVar26 = _vmr32(auVar25);
      auStack_460 = _sqc2(in_vf0);
      auStack_470 = _sqc2(auVar24);
      auStack_480 = _sqc2(auVar25);
      auStack_490 = _sqc2(auVar26);
      sceVu0RotMatrixX(afStack_450[iVar14 * 4 + 0xd0],auStack_490,auStack_490);
      sceVu0RotMatrixY(3.1415927 - afStack_450[iVar14 * 4 + 0xd1],auStack_490,auStack_490);
      ApplyMatrix__6MatrixCFRC7FVector(auStack_990,auStack_490,&fStack_4c0);
      auVar24 = _lqc2(auStack_990);
      auVar25 = _lqc2(*(undefined1 (*) [16])(param_1 + iVar14 * 0x10 + 0x70));
      auVar24 = _vadd(auVar24,auVar25);
      auStack_ad0 = _sqc2(auVar24);
      __ct__7FVectorFRC7FVector(auStack_980,auStack_ad0);
      afStack_450[iVar14 * 0xc] = auStack_980._0_4_;
      afStack_450[iVar14 * 0xc + 1] = auStack_980._4_4_;
      afStack_450[iVar14 * 0xc + 2] = fStack_978;
      afStack_450[iVar14 * 0xc + 3] = fStack_974;
      ApplyMatrix__6MatrixCFRC7FVector(auStack_9b0,auStack_490,&fStack_4b0);
      auVar24 = _lqc2(auStack_9b0);
      auVar25 = _lqc2(*(undefined1 (*) [16])(param_1 + iVar14 * 0x10 + 0x70));
      auVar24 = _vadd(auVar24,auVar25);
      auStack_ae0 = _sqc2(auVar24);
      __ct__7FVectorFRC7FVector(auStack_9a0,auStack_ae0);
      iVar20 = iVar14 * 3 + 1;
      afStack_450[iVar20 * 4] = auStack_9a0._0_4_;
      afStack_450[iVar20 * 4 + 1] = auStack_9a0._4_4_;
      afStack_450[iVar20 * 4 + 2] = fStack_998;
      afStack_450[iVar20 * 4 + 3] = fStack_994;
      ApplyMatrix__6MatrixCFRC7FVector(auStack_9d0,auStack_490,&fStack_4a0);
      auVar24 = _lqc2(auStack_9d0);
      auVar25 = _lqc2(*(undefined1 (*) [16])(param_1 + iVar14 * 0x10 + 0x70));
      auVar24 = _vadd(auVar24,auVar25);
      auStack_af0 = _sqc2(auVar24);
      __ct__7FVectorFRC7FVector(auStack_9c0,auStack_af0);
      iVar20 = iVar14 * 3 + 2;
      afStack_450[iVar20 * 4] = auStack_9c0._0_4_;
      afStack_450[iVar20 * 4 + 1] = auStack_9c0._4_4_;
      afStack_450[iVar20 * 4 + 2] = fStack_9b8;
      afStack_450[iVar20 * 4 + 3] = fStack_9b4;
    }
    lVar21 = (long)(iVar14 + 1);
  }
  uStack_9e0 = 0xc0a00000;
  uStack_9dc = 0xc0a00000;
  uStack_9d8 = 0;
  uStack_9d4 = 0x3f800000;
  uStack_530 = 0xc0a00000;
  uStack_52c = 0xc0a00000;
  uStack_528 = 0;
  uStack_524 = 0x3f800000;
  uStack_9f0 = 0xc0a00000;
  uStack_9ec = 0x40a00000;
  uStack_9e8 = 0;
  uStack_9e4 = 0x3f800000;
  uStack_520 = 0xc0a00000;
  uStack_51c = 0x40a00000;
  uStack_518 = 0;
  uStack_514 = 0x3f800000;
  uStack_a00 = 0x40a00000;
  uStack_9fc = 0xc0a00000;
  uStack_9f8 = 0;
  uStack_9f4 = 0x3f800000;
  uStack_510 = 0x40a00000;
  uStack_50c = 0xc0a00000;
  uStack_508 = 0;
  uStack_504 = 0x3f800000;
  uStack_a10 = 0x40a00000;
  uStack_a0c = 0x40a00000;
  uStack_a08 = 0;
  uStack_a04 = 0x3f800000;
  uStack_500 = 0x40a00000;
  uStack_4fc = 0x40a00000;
  uStack_4f8 = 0;
  uStack_4f4 = 0x3f800000;
  auVar24 = _vmr32(in_vf0);
  auVar25 = _vmr32(auVar24);
  auVar26 = _vmr32(auVar25);
  auStack_460 = _sqc2(in_vf0);
  auStack_470 = _sqc2(auVar24);
  auStack_480 = _sqc2(auVar25);
  auStack_490 = _sqc2(auVar26);
  uVar23 = GetRad(*(undefined4 *)(*(int *)(iGpffff86b4 + 0x4324) + 0x40));
  sceVu0RotMatrixZ(uVar23,auStack_490,auStack_490);
  uVar23 = GetRad(*(undefined4 *)(*(int *)(iGpffff86b4 + 0x4324) + 0x44));
  sceVu0RotMatrixZ(uVar23,auStack_490,auStack_490);
  RotTransVector(auStack_570,&uStack_530,auStack_490,4);
  auStack_490 = *(undefined1 (*) [16])(iGpffff8598 + 0x240);
  auStack_480 = *(undefined1 (*) [16])(iGpffff8598 + 0x250);
  auStack_470 = *(undefined1 (*) [16])(iGpffff8598 + 0x260);
  auStack_460._0_12_ = ZEXT812(0);
  auStack_460._12_4_ = 0x3f800000;
  RotTransVector(&uStack_530,auStack_570,auStack_490,4);
  auVar10._4_4_ = afStack_450[1];
  auVar10._0_4_ = afStack_450[0];
  auVar10._8_4_ = afStack_450[2];
  auVar10._12_4_ = afStack_450[3];
  auVar25 = _lqc2(auVar10);
  auVar24._4_4_ = uStack_52c;
  auVar24._0_4_ = uStack_530;
  auVar24._8_4_ = uStack_528;
  auVar24._12_4_ = uStack_524;
  auVar24 = _lqc2(auVar24);
  auVar24 = _vadd(auVar25,auVar24);
  auStack_b00 = _sqc2(auVar24);
  __ct__7FVectorFRC7FVector(auStack_a20,auStack_b00);
  iVar14 = (int)*(short *)(param_1 + 0x19e);
  afStack_450[iVar14 * 0xc] = auStack_a20._0_4_;
  afStack_450[iVar14 * 0xc + 1] = auStack_a20._4_4_;
  afStack_450[iVar14 * 0xc + 2] = fStack_a18;
  afStack_450[iVar14 * 0xc + 3] = fStack_a14;
  auVar11._4_4_ = afStack_450[1];
  auVar11._0_4_ = afStack_450[0];
  auVar11._8_4_ = afStack_450[2];
  auVar11._12_4_ = afStack_450[3];
  auVar24 = _lqc2(auVar11);
  auVar25._4_4_ = uStack_51c;
  auVar25._0_4_ = uStack_520;
  auVar25._8_4_ = uStack_518;
  auVar25._12_4_ = uStack_514;
  auVar25 = _lqc2(auVar25);
  auVar24 = _vadd(auVar24,auVar25);
  auStack_b10 = _sqc2(auVar24);
  __ct__7FVectorFRC7FVector(auStack_a30,auStack_b10);
  iVar14 = *(short *)(param_1 + 0x19e) * 3 + 1;
  afStack_450[iVar14 * 4] = auStack_a30._0_4_;
  afStack_450[iVar14 * 4 + 1] = auStack_a30._4_4_;
  afStack_450[iVar14 * 4 + 2] = fStack_a28;
  afStack_450[iVar14 * 4 + 3] = fStack_a24;
  auVar12._4_4_ = afStack_450[1];
  auVar12._0_4_ = afStack_450[0];
  auVar12._8_4_ = afStack_450[2];
  auVar12._12_4_ = afStack_450[3];
  auVar24 = _lqc2(auVar12);
  auVar26._4_4_ = uStack_50c;
  auVar26._0_4_ = uStack_510;
  auVar26._8_4_ = uStack_508;
  auVar26._12_4_ = uStack_504;
  auVar25 = _lqc2(auVar26);
  auVar24 = _vadd(auVar24,auVar25);
  auStack_b20 = _sqc2(auVar24);
  __ct__7FVectorFRC7FVector(auStack_a40,auStack_b20);
  iVar14 = *(short *)(param_1 + 0x19e) * 3 + 2;
  afStack_450[iVar14 * 4] = auStack_a40._0_4_;
  afStack_450[iVar14 * 4 + 1] = auStack_a40._4_4_;
  afStack_450[iVar14 * 4 + 2] = fStack_a38;
  afStack_450[iVar14 * 4 + 3] = fStack_a34;
  auVar13._4_4_ = afStack_450[1];
  auVar13._0_4_ = afStack_450[0];
  auVar13._8_4_ = afStack_450[2];
  auVar13._12_4_ = afStack_450[3];
  auVar24 = _lqc2(auVar13);
  auVar9._4_4_ = uStack_4fc;
  auVar9._0_4_ = uStack_500;
  auVar9._8_4_ = uStack_4f8;
  auVar9._12_4_ = uStack_4f4;
  auVar25 = _lqc2(auVar9);
  auVar24 = _vadd(auVar24,auVar25);
  auStack_b30 = _sqc2(auVar24);
  __ct__7FVectorFRC7FVector(auStack_a50,auStack_b30);
  iVar14 = *(short *)(param_1 + 0x19e) * 3 + 3;
  afStack_450[iVar14 * 4] = auStack_a50._0_4_;
  afStack_450[iVar14 * 4 + 1] = auStack_a50._4_4_;
  afStack_450[iVar14 * 4 + 2] = fStack_a48;
  afStack_450[iVar14 * 4 + 3] = fStack_a44;
  GetViewScreenMatrix__9GsxCameraFv(auStack_a90,iGpffff8598);
  for (iVar14 = 0; iVar14 < 4; iVar14 = iVar14 + 1) {
    auStack_5b0[iVar14 * 4] = *(undefined4 *)(auStack_490 + iVar14 * 0x10);
    auStack_5b0[iVar14 * 4 + 1] = *(undefined4 *)(auStack_490 + iVar14 * 0x10 + 4);
    auStack_5b0[iVar14 * 4 + 2] = *(undefined4 *)(auStack_490 + iVar14 * 0x10 + 8);
    auStack_5b0[iVar14 * 4 + 3] = *(undefined4 *)(auStack_490 + iVar14 * 0x10 + 0xc);
  }
  sceVu0RotTransPersN(aiStack_8f0,auStack_5b0,afStack_450,*(short *)(param_1 + 0x19e) * 3 + 4,0);
  bVar8 = false;
  for (iVar14 = 0; iVar14 < *(short *)(param_1 + 0x19e) * 3 + 4; iVar14 = iVar14 + 1) {
    if ((((aiStack_8f0[iVar14 * 4] >> 0x1f < 0) || (0x10000 < aiStack_8f0[iVar14 * 4])) ||
        (aiStack_8f0[iVar14 * 4 + 1] >> 0x1f < 0)) ||
       ((0x10000 < aiStack_8f0[iVar14 * 4 + 1] || (aiStack_8f0[iVar14 * 4 + 2] >> 0x1f < 0)))) {
      bVar8 = true;
    }
  }
  if ((CONCAT44(*(short *)(param_1 + 0x19c) >> 0xf,(int)*(short *)(param_1 + 0x19c)) != 0) &&
     (CONCAT44((int)((long)((ulong)(uint)(int)*(short *)(param_1 + 0x19e) << 0x30) >> 0x3f),
               (int)*(short *)(param_1 + 0x19e)) < 2)) {
    bVar8 = true;
  }
  bVar1 = (*(byte *)(param_1 + 0x40) & 1) == 0;
  uVar19 = (uint)bVar1;
  if (*(int *)(param_1 + uVar19 * 4 + 0x1a0) != (*(short *)(param_1 + 0x19e) * 2 + 2) * 3 + 0x14) {
    __dla__FPv(*(undefined4 *)(param_1 + uVar19 * 4 + 0x18));
    *(undefined4 *)(param_1 + uVar19 * 4 + 0x18) = 0;
    *(undefined4 *)(param_1 + uVar19 * 4 + 0x1a0) = 0;
  }
  if (*(int *)(param_1 + uVar19 * 4 + 0x18) == 0) {
    uVar23 = __nwa__FUi(((*(short *)(param_1 + 0x19e) * 2 + 2) * 3 + 0x14) * 0x10);
    *(undefined4 *)(param_1 + uVar19 * 4 + 0x18) = uVar23;
    *(int *)(param_1 + uVar19 * 4 + 0x1a0) = (*(short *)(param_1 + 0x19e) * 2 + 2) * 3 + 9;
    iVar14 = *(int *)(param_1 + uVar19 * 4 + 0x18);
    if (*(short *)(param_1 + 0x19e) < 2) {
      *(undefined4 *)(iVar14 + 0x10) = 0x1000000d;
      *(undefined4 *)(iVar14 + 0x14) = 0;
      *(undefined4 *)(iVar14 + 0x18) = 0;
      *(undefined4 *)(iVar14 + 0x1c) = 0x5000000d;
    }
    else {
      *(int *)(iVar14 + 0x10) = (*(short *)(param_1 + 0x19e) * 2 + 2) * 3 + 0x10000011;
      *(undefined4 *)(iVar14 + 0x14) = 0;
      *(undefined4 *)(iVar14 + 0x18) = 0;
      *(int *)(iVar14 + 0x1c) = (*(short *)(param_1 + 0x19e) * 2 + 2) * 3 + 0x50000011;
    }
    *(undefined8 *)(iVar14 + 0x20) = 0x6000000000000001;
    *(undefined8 *)(iVar14 + 0x28) = 0xe6e8ee;
    *(undefined8 *)(iVar14 + 0x30) = 1;
    *(undefined8 *)(iVar14 + 0x38) = 0x3f;
    *(undefined8 *)(iVar14 + 0x40) = 0x60;
    *(undefined8 *)(iVar14 + 0x48) = 0x14;
    *(undefined8 *)(iVar14 + 0x50) = 5;
    *(undefined8 *)(iVar14 + 0x58) = 0;
    *(undefined8 *)(iVar14 + 0x60) = 0x53001;
    *(undefined8 *)(iVar14 + 0x68) = 0x47;
    uVar15 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x42e4),1);
    *(undefined8 *)(iVar14 + 0x70) = uVar15;
    *(undefined8 *)(iVar14 + 0x78) = 0;
    *(undefined8 *)(iVar14 + 0x80) = 0x48;
    *(undefined8 *)(iVar14 + 0x88) = 0x42;
    if (CONCAT44((int)((long)((ulong)(uint)(int)*(short *)(param_1 + 0x19e) << 0x30) >> 0x3f),
                 (int)*(short *)(param_1 + 0x19e)) < 2) {
      auVar4._4_4_ = in_zero_hi;
      auVar4._0_4_ = in_zero_lo;
      auVar4._8_4_ = in_zero_udw;
      auVar4._12_4_ = in_register_0000000c;
      auVar6._8_8_ = in_v1_udw;
      auVar6._0_8_ = 0xa400000000008001;
      auVar24 = _pcpyld(auVar4,auVar6);
      *(long *)(iVar14 + 0x90) = auVar24._0_8_;
      *(undefined8 *)(iVar14 + 0x98) = 0x4343c3c310;
      *(undefined8 *)(iVar14 + 0xa0) = 0x154;
      *(undefined8 *)(iVar14 + 0xa8) = 0x170808080;
      *(undefined8 *)(iVar14 + 0xb0) = 0;
      *(long *)(iVar14 + 0xc0) =
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42e4) + 4) << 4) << 0x10;
      *(long *)(iVar14 + 0xd0) =
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42e4) + 2) << 4);
      uVar17 = (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42e4) + 4);
      *(ulong *)(iVar14 + 0xe0) =
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42e4) + 2) << 4) |
           CONCAT44((int)(short)((uVar17 << 4) >> 0x10),uVar17 << 0x14);
    }
    else {
      auVar5._4_4_ = in_zero_hi;
      auVar5._0_4_ = in_zero_lo;
      auVar5._8_4_ = in_zero_udw;
      auVar5._12_4_ = in_register_0000000c;
      auVar7._8_8_ = in_v1_udw;
      auVar7._0_8_ = 0xa400000000000001;
      auVar24 = _pcpyld(auVar5,auVar7);
      *(long *)(iVar14 + 0x90) = auVar24._0_8_;
      *(undefined8 *)(iVar14 + 0x98) = 0x4343c3c310;
      *(undefined8 *)(iVar14 + 0xa0) = 0x154;
      *(undefined8 *)(iVar14 + 0xa8) = 0x170808080;
      *(undefined8 *)(iVar14 + 0xb0) = 0;
      *(long *)(iVar14 + 0xc0) =
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42e4) + 4) << 4) << 0x10;
      *(long *)(iVar14 + 0xd0) =
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42e4) + 2) << 4);
      uVar17 = (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42e4) + 4);
      *(ulong *)(iVar14 + 0xe0) =
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42e4) + 2) << 4) |
           CONCAT44((int)(short)((uVar17 << 4) >> 0x10),uVar17 << 0x14);
      *(undefined8 *)(iVar14 + 0xf0) = 0x6400000000000001;
      *(undefined8 *)(iVar14 + 0xf8) = 0x4cc1f0;
      *(undefined8 *)(iVar14 + 0x100) = 0x4c;
      *(undefined8 *)(iVar14 + 0x108) = 0;
      *(undefined8 *)(iVar14 + 0x110) = 0x70ffff80;
      *(undefined8 *)(iVar14 + 0x130) = 0x4400000000000001;
      *(undefined8 *)(iVar14 + 0x138) = 0xcc10;
      *(undefined8 *)(iVar14 + 0x140) = 0x4c;
      *(undefined8 *)(iVar14 + 0x148) = 0x70ffff80;
      *(ulong *)(iVar14 + 0x160) = (long)(*(short *)(param_1 + 0x19e) + -1) | 0x4400000000000000;
      *(undefined8 *)(iVar14 + 0x168) = 0x44f1;
      iVar20 = 0x17;
      for (iVar18 = 1;
          (long)iVar18 <
          CONCAT44((int)((long)((ulong)(uint)(int)*(short *)(param_1 + 0x19e) << 0x30) >> 0x3f),
                   (int)*(short *)(param_1 + 0x19e)); iVar18 = iVar18 + 1) {
        *(undefined8 *)(iVar14 + iVar20 * 0x10 + 8) = 0;
        iVar20 = iVar20 + 2;
      }
      *(undefined8 *)(iVar14 + iVar20 * 0x10) = 0x4400000000000001;
      *(undefined8 *)(iVar14 + iVar20 * 0x10 + 8) = 0xcc10;
      *(undefined8 *)(iVar14 + (iVar20 + 1) * 0x10) = 0x4c;
      *(undefined8 *)(iVar14 + (iVar20 + 1) * 0x10 + 8) = 0x70ffff80;
      *(ulong *)(iVar14 + (iVar20 + 3) * 0x10) =
           (long)(*(short *)(param_1 + 0x19e) + -1) | 0x4400000000000000;
      *(undefined8 *)(iVar14 + (iVar20 + 3) * 0x10 + 8) = 0x44f1;
      iVar20 = iVar20 + 4;
      for (iVar18 = 1;
          (long)iVar18 <
          CONCAT44((int)((long)((ulong)(uint)(int)*(short *)(param_1 + 0x19e) << 0x30) >> 0x3f),
                   (int)*(short *)(param_1 + 0x19e)); iVar18 = iVar18 + 1) {
        *(undefined8 *)(iVar14 + iVar20 * 0x10 + 8) = 0;
        iVar20 = iVar20 + 2;
      }
      *(undefined8 *)(iVar14 + iVar20 * 0x10) = 0x4400000000000001;
      *(undefined8 *)(iVar14 + iVar20 * 0x10 + 8) = 0xcc10;
      *(undefined8 *)(iVar14 + (iVar20 + 1) * 0x10) = 0x4c;
      *(undefined8 *)(iVar14 + (iVar20 + 1) * 0x10 + 8) = 0x70ffff80;
      *(ulong *)(iVar14 + (iVar20 + 3) * 0x10) =
           (long)(*(short *)(param_1 + 0x19e) + -1) | 0x4400000000008000;
      *(undefined8 *)(iVar14 + (iVar20 + 3) * 0x10 + 8) = 0x44f1;
      iVar20 = iVar20 + 4;
      for (iVar18 = 1;
          (long)iVar18 <
          CONCAT44((int)((long)((ulong)(uint)(int)*(short *)(param_1 + 0x19e) << 0x30) >> 0x3f),
                   (int)*(short *)(param_1 + 0x19e)); iVar18 = iVar18 + 1) {
        *(undefined8 *)(iVar14 + iVar20 * 0x10 + 8) = 0;
        iVar20 = iVar20 + 2;
      }
    }
  }
  puVar2 = *(undefined4 **)(param_1 + uVar19 * 4 + 0x18);
  if (bVar8) {
    *(undefined4 **)(param_1 + 0x54) = puVar2;
    *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfe | bVar1;
  }
  else {
    *puVar2 = 0x50000000;
    puVar2[1] = *(undefined4 *)
                 (*(int *)(iGpffff86b4 + 0x42e4) +
                  (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42e4) + 10) * 4 + 0xc);
    puVar2[2] = 0;
    puVar2[3] = 0;
    if (CONCAT44(*(short *)(param_1 + 0x19c) >> 0xf,(int)*(short *)(param_1 + 0x19c)) == 0) {
      iVar14 = aiStack_8f0[*(short *)(param_1 + 0x19e) * 0xc + 1];
      iVar20 = aiStack_8f0[*(short *)(param_1 + 0x19e) * 0xc];
      lVar21 = __fixunssfdi((float)aiStack_8f0[*(short *)(param_1 + 0x19e) * 0xc + 2] / 16.0);
      *(long *)(puVar2 + 0x2e) = lVar21 << 0x20 | (long)iVar20 | (long)iVar14 << 0x10;
      iVar14 = aiStack_8f0[(*(short *)(param_1 + 0x19e) * 3 + 1) * 4 + 1];
      iVar20 = aiStack_8f0[(*(short *)(param_1 + 0x19e) * 3 + 1) * 4];
      lVar21 = __fixunssfdi((float)aiStack_8f0[(*(short *)(param_1 + 0x19e) * 3 + 1) * 4 + 2] /
                               16.0);
      *(long *)(puVar2 + 0x32) = lVar21 << 0x20 | (long)iVar20 | (long)iVar14 << 0x10;
      iVar14 = aiStack_8f0[(*(short *)(param_1 + 0x19e) * 3 + 2) * 4 + 1];
      iVar20 = aiStack_8f0[(*(short *)(param_1 + 0x19e) * 3 + 2) * 4];
      lVar21 = __fixunssfdi((float)aiStack_8f0[(*(short *)(param_1 + 0x19e) * 3 + 2) * 4 + 2] /
                               16.0);
      *(long *)(puVar2 + 0x36) = lVar21 << 0x20 | (long)iVar20 | (long)iVar14 << 0x10;
      iVar14 = aiStack_8f0[(*(short *)(param_1 + 0x19e) * 3 + 3) * 4 + 1];
      iVar20 = aiStack_8f0[(*(short *)(param_1 + 0x19e) * 3 + 3) * 4];
      lVar21 = __fixunssfdi((float)aiStack_8f0[(*(short *)(param_1 + 0x19e) * 3 + 3) * 4 + 2] /
                               16.0);
      *(long *)(puVar2 + 0x3a) = lVar21 << 0x20 | (long)iVar20 | (long)iVar14 << 0x10;
    }
    else {
      *(undefined8 *)(puVar2 + 0x2e) = 0x71006f00;
      *(undefined8 *)(puVar2 + 0x32) = 0x71006f00;
      *(undefined8 *)(puVar2 + 0x36) = 0x71006f00;
      *(undefined8 *)(puVar2 + 0x3a) = 0x71006f00;
    }
    iVar14 = 0xf;
    if (1 < CONCAT44((int)((long)((ulong)(uint)(int)*(short *)(param_1 + 0x19e) << 0x30) >> 0x3f),
                     (int)*(short *)(param_1 + 0x19e))) {
      lVar21 = __fixunssfdi((float)aiStack_8f0[2] / 16.0);
      *(long *)(puVar2 + 0x46) =
           lVar21 << 0x20 | (long)aiStack_8f0[0] | (long)aiStack_8f0[1] << 0x10;
      lVar21 = __fixunssfdi((float)iStack_8d8 / 16.0);
      *(long *)(puVar2 + 0x48) =
           lVar21 << 0x20 | (long)aiStack_8f0[4] | (long)aiStack_8f0[5] << 0x10;
      lVar21 = __fixunssfdi((float)iStack_8c8 / 16.0);
      *(long *)(puVar2 + 0x4a) = lVar21 << 0x20 | (long)iStack_8d0 | (long)iStack_8cc << 0x10;
      lVar21 = __fixunssfdi((float)aiStack_8f0[2] / 16.0);
      *(long *)(puVar2 + 0x54) =
           lVar21 << 0x20 | (long)aiStack_8f0[0] | (long)aiStack_8f0[1] << 0x10;
      lVar21 = __fixunssfdi((float)iStack_8d8 / 16.0);
      *(long *)(puVar2 + 0x56) =
           lVar21 << 0x20 | (long)aiStack_8f0[4] | (long)aiStack_8f0[5] << 0x10;
      iVar14 = 0x17;
      for (iVar20 = 1; (long)iVar20 < (long)*(short *)(param_1 + 0x19e); iVar20 = iVar20 + 1) {
        iVar18 = *(short *)(param_1 + 0x19e) + -1;
        if (iVar18 == 0) {
          trap(7);
        }
        *(ulong *)(puVar2 + iVar14 * 4) =
             (ulong)((0x70 - (iVar20 * 0x70) / iVar18) * 0x1000000 | 0xffff80);
        iVar18 = aiStack_8f0[iVar20 * 0xc + 1];
        iVar3 = aiStack_8f0[iVar20 * 0xc];
        lVar21 = __fixunssfdi((float)aiStack_8f0[iVar20 * 0xc + 2] / 16.0);
        *(ulong *)(puVar2 + (iVar14 + 1) * 4) =
             lVar21 << 0x20 |
             (long)iVar3 | CONCAT44((int)(short)((uint)iVar18 >> 0x10),iVar18 << 0x10);
        iVar18 = aiStack_8f0[(iVar20 * 3 + 1) * 4 + 1];
        iVar3 = aiStack_8f0[(iVar20 * 3 + 1) * 4];
        lVar21 = __fixunssfdi((float)aiStack_8f0[(iVar20 * 3 + 1) * 4 + 2] / 16.0);
        *(ulong *)(puVar2 + (iVar14 + 1) * 4 + 2) =
             lVar21 << 0x20 |
             (long)iVar3 | CONCAT44((int)(short)((uint)iVar18 >> 0x10),iVar18 << 0x10);
        iVar14 = iVar14 + 2;
      }
      lVar21 = __fixunssfdi((float)iStack_8d8 / 16.0);
      *(long *)(puVar2 + (iVar14 + 2) * 4) =
           lVar21 << 0x20 | (long)aiStack_8f0[4] | (long)aiStack_8f0[5] << 0x10;
      lVar21 = __fixunssfdi((float)iStack_8c8 / 16.0);
      *(long *)(puVar2 + (iVar14 + 2) * 4 + 2) =
           lVar21 << 0x20 | (long)iStack_8d0 | (long)iStack_8cc << 0x10;
      iVar14 = iVar14 + 4;
      for (iVar20 = 1; (long)iVar20 < (long)*(short *)(param_1 + 0x19e); iVar20 = iVar20 + 1) {
        iVar18 = *(short *)(param_1 + 0x19e) + -1;
        if (iVar18 == 0) {
          trap(7);
        }
        *(ulong *)(puVar2 + iVar14 * 4) =
             (ulong)((0x70 - (iVar20 * 0x70) / iVar18) * 0x1000000 | 0xffff80);
        iVar18 = aiStack_8f0[(iVar20 * 3 + 1) * 4 + 1];
        iVar3 = aiStack_8f0[(iVar20 * 3 + 1) * 4];
        lVar21 = __fixunssfdi((float)aiStack_8f0[(iVar20 * 3 + 1) * 4 + 2] / 16.0);
        *(ulong *)(puVar2 + (iVar14 + 1) * 4) =
             lVar21 << 0x20 |
             (long)iVar3 | CONCAT44((int)(short)((uint)iVar18 >> 0x10),iVar18 << 0x10);
        iVar18 = aiStack_8f0[(iVar20 * 3 + 2) * 4 + 1];
        iVar3 = aiStack_8f0[(iVar20 * 3 + 2) * 4];
        lVar21 = __fixunssfdi((float)aiStack_8f0[(iVar20 * 3 + 2) * 4 + 2] / 16.0);
        *(ulong *)(puVar2 + (iVar14 + 1) * 4 + 2) =
             lVar21 << 0x20 |
             (long)iVar3 | CONCAT44((int)(short)((uint)iVar18 >> 0x10),iVar18 << 0x10);
        iVar14 = iVar14 + 2;
      }
      lVar21 = __fixunssfdi((float)iStack_8c8 / 16.0);
      *(long *)(puVar2 + (iVar14 + 2) * 4) =
           lVar21 << 0x20 | (long)iStack_8d0 | (long)iStack_8cc << 0x10;
      lVar21 = __fixunssfdi((float)aiStack_8f0[2] / 16.0);
      *(ulong *)(puVar2 + (iVar14 + 2) * 4 + 2) =
           lVar21 << 0x20 |
           (long)aiStack_8f0[0] |
           CONCAT44((int)(short)((uint)aiStack_8f0[1] >> 0x10),aiStack_8f0[1] << 0x10);
      iVar14 = iVar14 + 4;
      for (iVar20 = 1;
          (long)iVar20 <
          CONCAT44((int)((long)((ulong)(uint)(int)*(short *)(param_1 + 0x19e) << 0x30) >> 0x3f),
                   (int)*(short *)(param_1 + 0x19e)); iVar20 = iVar20 + 1) {
        iVar18 = *(short *)(param_1 + 0x19e) + -1;
        if (iVar18 == 0) {
          trap(7);
        }
        *(ulong *)(puVar2 + iVar14 * 4) =
             (ulong)((0x70 - (iVar20 * 0x70) / iVar18) * 0x1000000 | 0xffff80);
        iVar18 = aiStack_8f0[(iVar20 * 3 + 2) * 4 + 1];
        iVar3 = aiStack_8f0[(iVar20 * 3 + 2) * 4];
        lVar21 = __fixunssfdi((float)aiStack_8f0[(iVar20 * 3 + 2) * 4 + 2] / 16.0);
        *(ulong *)(puVar2 + (iVar14 + 1) * 4) =
             lVar21 << 0x20 |
             (long)iVar3 | CONCAT44((int)(short)((uint)iVar18 >> 0x10),iVar18 << 0x10);
        iVar18 = aiStack_8f0[iVar20 * 0xc + 1];
        iVar3 = aiStack_8f0[iVar20 * 0xc];
        lVar21 = __fixunssfdi((float)aiStack_8f0[iVar20 * 0xc + 2] / 16.0);
        *(ulong *)(puVar2 + (iVar14 + 1) * 4 + 2) =
             lVar21 << 0x20 |
             (long)iVar3 | CONCAT44((int)(short)((uint)iVar18 >> 0x10),iVar18 << 0x10);
        iVar14 = iVar14 + 2;
      }
    }
    *(undefined4 **)(param_1 + 0x54) = puVar2 + iVar14 * 4;
    *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfe | bVar1;
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054ad80  EndSet__7Bullet4Fv
 * C++: Bullet4::EndSet()
 * size: 0x10 bytes
 * --------------------------------------------------------------------------- */
void EndSet__7Bullet4Fv(void)

{
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b970  @24@__dt__7Bullet4Fv
 * C++: @24@__dt__7Bullet4Fv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int * _24___dt__7Bullet4Fv(int *param_1,short param_2)

{
  int *piVar1;
  
  piVar1 = param_1 + -6;
  if (piVar1 != (int *)0x0) {
    param_1[-1] = 0x409980;
    param_1[4] = 0x409990;
    param_1[7] = 0x4099a0;
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
 * JP: 0x0054b980  @44@__dt__7Bullet4Fv
 * C++: @44@__dt__7Bullet4Fv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int _44___dt__7Bullet4Fv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x2c;
  if (iVar1 != 0) {
    *(undefined4 *)(param_1 + -0x18) = 0x409980;
    *(undefined4 *)(param_1 + -4) = 0x409990;
    *(undefined4 *)(param_1 + 8) = 0x4099a0;
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

