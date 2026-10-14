/* decomp/H/Bullet3Child.c — cleaned Ghidra output (SH2JP_BATTLE.BIN, JP Furokuban, base 0x00430a00).
 * 8 function(s). Types: see types.h. Names/gp globals resolved from symbols/SLPM_602.19.syms. */
#include "types.h"

/* ---------------------------------------------------------------------------
 * JP: 0x00541410  __ct__12Bullet3ChildFiiP7Bullet3issfiiiiUsUsii
 * C++: Bullet3Child::__ct(int, int, Bullet3 *, int, short, short, float, int, int, int, int, ushort, ushort, int, int)
 * size: 0x1714 bytes
 * --------------------------------------------------------------------------- */
undefined8
__ct__12Bullet3ChildFiiP7Bullet3issfiiiiUsUsii
          (undefined4 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
          undefined4 param_5,undefined4 param_6,undefined2 param_7,undefined2 param_8,
          undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
          undefined2 param_13,undefined2 param_14,undefined4 param_15,undefined4 param_16)

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
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  int iVar29;
  byte *pbVar30;
  undefined8 uVar31;
  undefined4 *puVar32;
  undefined1 (*pauVar33) [16];
  int iVar34;
  undefined1 in_vf0 [16];
  undefined1 auVar35 [16];
  undefined1 auVar36 [16];
  undefined1 auVar37 [16];
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
  undefined1 auStack_350 [16];
  undefined1 auStack_340 [16];
  undefined1 auStack_330 [16];
  undefined1 auStack_320 [16];
  undefined1 auStack_310 [16];
  undefined1 auStack_300 [16];
  undefined1 auStack_2f0 [16];
  undefined1 auStack_2e0 [16];
  undefined8 uStack_2d0;
  undefined4 uStack_2c8;
  undefined4 uStack_2c4;
  undefined4 uStack_2c0;
  undefined4 uStack_2bc;
  undefined4 uStack_2b8;
  undefined4 uStack_2b4;
  undefined1 auStack_2b0 [8];
  undefined4 uStack_2a8;
  undefined4 uStack_2a4;
  undefined4 uStack_2a0;
  undefined4 uStack_29c;
  undefined4 uStack_298;
  undefined4 uStack_294;
  undefined1 auStack_290 [16];
  undefined1 auStack_280 [16];
  undefined1 auStack_270 [16];
  undefined1 auStack_260 [16];
  undefined1 auStack_250 [16];
  undefined1 auStack_240 [16];
  undefined8 uStack_230;
  undefined4 uStack_228;
  undefined4 uStack_224;
  undefined4 uStack_220;
  undefined4 uStack_21c;
  undefined4 uStack_218;
  undefined4 uStack_214;
  undefined1 auStack_210 [8];
  undefined4 uStack_208;
  undefined4 uStack_204;
  undefined4 uStack_200;
  undefined4 uStack_1fc;
  undefined4 uStack_1f8;
  undefined4 uStack_1f4;
  undefined1 auStack_1f0 [16];
  undefined1 auStack_1e0 [16];
  undefined1 auStack_1d0 [16];
  undefined1 auStack_1c0 [16];
  undefined1 auStack_1b0 [16];
  undefined1 auStack_1a0 [16];
  undefined8 uStack_190;
  undefined4 uStack_188;
  undefined4 uStack_184;
  undefined4 uStack_180;
  undefined4 uStack_17c;
  undefined4 uStack_178;
  undefined4 uStack_174;
  undefined1 auStack_170 [8];
  undefined4 uStack_168;
  undefined4 uStack_164;
  undefined4 uStack_160;
  undefined4 uStack_15c;
  undefined4 uStack_158;
  undefined4 uStack_154;
  undefined4 uStack_150;
  float fStack_14c;
  undefined1 auStack_140 [16];
  undefined1 auStack_130 [16];
  undefined4 uStack_120;
  undefined4 uStack_11c;
  undefined4 uStack_118;
  undefined4 uStack_114;
  undefined4 uStack_c0;
  undefined4 uStack_bc;
  undefined4 uStack_b8;
  undefined4 uStack_b4;
  undefined4 uStack_b0;
  undefined4 uStack_ac;
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  undefined4 uStack_a0;
  undefined4 uStack_9c;
  undefined4 uStack_98;
  undefined4 uStack_94;
  undefined4 uStack_90;
  undefined4 uStack_8c;
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [16];
  undefined1 auStack_20 [16];
  undefined1 auStack_10 [16];
  
  __ct__6BtlEffFii(param_2,param_3,param_4);
  iVar34 = (int)param_2;
  *(undefined4 *)(iVar34 + 0x14) = 0x4099d0;
  *(undefined4 *)(iVar34 + 0x28) = 0x4099e0;
  *(undefined4 *)(iVar34 + 0x34) = 0x4099f0;
  puVar32 = (undefined4 *)(iVar34 + 0x70);
  do {
    *puVar32 = in_zero_lo;
    puVar32[1] = in_zero_hi;
    puVar32[2] = in_zero_udw;
    puVar32[3] = in_register_0000000c;
    puVar32 = puVar32 + 4;
  } while (puVar32 != (undefined4 *)(iVar34 + 0x90));
  *(undefined4 *)(iVar34 + 0x90) = in_zero_lo;
  *(undefined4 *)(iVar34 + 0x94) = in_zero_hi;
  *(undefined4 *)(iVar34 + 0x98) = in_zero_udw;
  *(undefined4 *)(iVar34 + 0x9c) = in_register_0000000c;
  *(undefined4 *)(iVar34 + 0x40) = 0;
  *(int *)(iVar34 + 0x44) = (int)param_3;
  *(int *)(iVar34 + 0x48) = (int)param_4;
  *(undefined4 *)(iVar34 + 0x4c) = 10;
  *(undefined4 *)(iVar34 + 0x5c) = param_5;
  *(undefined4 *)(iVar34 + 0x60) = param_6;
  *(undefined2 *)(iVar34 + 100) = param_7;
  *(undefined2 *)(iVar34 + 0x66) = param_8;
  *(undefined4 *)(iVar34 + 0x68) = param_1;
  *(undefined4 *)(iVar34 + 0xa0) = param_10;
  *(undefined4 *)(iVar34 + 0xa4) = param_11;
  *(undefined4 *)(iVar34 + 0xa8) = param_9;
  *(undefined4 *)(iVar34 + 0xac) = param_12;
  *(undefined2 *)(iVar34 + 0xb0) = param_13;
  *(undefined2 *)(iVar34 + 0xb2) = param_14;
  *(undefined4 *)(iVar34 + 0xb4) = param_15;
  *(undefined4 *)(iVar34 + 0xb8) = param_16;
  *(undefined4 *)(iVar34 + 0x1c) = 0;
  *(undefined4 *)(iVar34 + 0x18) = 0;
  *(undefined4 *)(iVar34 + 0xbc) = 0;
  *(undefined4 *)(iVar34 + 0xc0) = 0;
  *(int *)(*(int *)(iVar34 + 0x5c) + 0x8c) = *(int *)(*(int *)(iVar34 + 0x5c) + 0x8c) + 1;
  iVar29 = GetRegDat__9RegDatApiFiii(0x3a,*(undefined4 *)
                                 (iGpffff86b4 + *(int *)(iVar34 + 0x48) * 0x4f0 + 0x55c),
                           0xffffffffffffffff);
  iVar29 = *(int *)(*(short *)(iVar29 + 0x14) * 4 + 0x651b70);
  auVar35 = _vmr32(in_vf0);
  auVar36 = _vmr32(auVar35);
  auVar37 = _vmr32(auVar36);
  _sqc2(in_vf0);
  _sqc2(auVar35);
  _sqc2(auVar36);
  _sqc2(auVar37);
  auStack_140._4_4_ = in_zero_hi;
  auStack_140._0_4_ = in_zero_lo;
  auStack_140._8_4_ = in_zero_udw;
  auStack_140._12_4_ = in_register_0000000c;
  auStack_130._4_4_ = in_zero_hi;
  auStack_130._0_4_ = in_zero_lo;
  auStack_130._8_4_ = in_zero_udw;
  auStack_130._12_4_ = in_register_0000000c;
  uStack_c0 = in_zero_lo;
  uStack_bc = in_zero_hi;
  uStack_b8 = in_zero_udw;
  uStack_b4 = in_register_0000000c;
  uStack_b0 = in_zero_lo;
  uStack_ac = in_zero_hi;
  uStack_a8 = in_zero_udw;
  uStack_a4 = in_register_0000000c;
  uStack_a0 = in_zero_lo;
  uStack_9c = in_zero_hi;
  uStack_98 = in_zero_udw;
  uStack_94 = in_register_0000000c;
  uStack_90 = in_zero_lo;
  uStack_8c = in_zero_hi;
  uStack_88 = in_zero_udw;
  uStack_84 = in_register_0000000c;
  uStack_80 = in_zero_lo;
  uStack_7c = in_zero_hi;
  uStack_78 = in_zero_udw;
  uStack_74 = in_register_0000000c;
  uStack_70 = in_zero_lo;
  uStack_6c = in_zero_hi;
  uStack_68 = in_zero_udw;
  uStack_64 = in_register_0000000c;
  uStack_60 = in_zero_lo;
  uStack_5c = in_zero_hi;
  uStack_58 = in_zero_udw;
  uStack_54 = in_register_0000000c;
  uStack_50 = in_zero_lo;
  uStack_4c = in_zero_hi;
  uStack_48 = in_zero_udw;
  uStack_44 = in_register_0000000c;
  if (*(short *)(iVar34 + 0x66) == 0) {
    if (*(short *)(iVar29 + 2) == 2) {
      pbVar30 = (byte *)(*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar34 + 0x48) * 0x4f0 +
                                                   0x144) + 0x530) + 0xe4) +
                        *(short *)(iVar29 + *(short *)(iVar34 + 100) * 0x20 + 4) * 0x110);
      pauVar33 = (undefined1 (*) [16])
                 (*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar34 + 0x48) * 0x4f0 + 0x144)
                                   + 0x530) + 0x30) + (uint)*pbVar30 * 0x1f0 +
                 (bGpffff8340 & 1) * 0x40);
      auStack_40 = *pauVar33;
      auStack_30 = pauVar33[1];
      auStack_20 = pauVar33[2];
      auStack_10 = pauVar33[3];
    }
    else if (*(short *)(iVar29 + 2) == 1) {
      pbVar30 = (byte *)(*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar34 + 0x48) * 0x4f0 +
                                                   0x144) + 0x52c) + 0xe4) +
                        *(short *)(iVar29 + *(short *)(iVar34 + 100) * 0x20 + 4) * 0x110);
      pauVar33 = (undefined1 (*) [16])
                 (*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar34 + 0x48) * 0x4f0 + 0x144)
                                   + 0x52c) + 0x30) + (uint)*pbVar30 * 0x1f0 +
                 (bGpffff8340 & 1) * 0x40);
      auStack_40 = *pauVar33;
      auStack_30 = pauVar33[1];
      auStack_20 = pauVar33[2];
      auStack_10 = pauVar33[3];
    }
    else {
      pbVar30 = (byte *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar34 + 0x48) * 0x4f0 + 0x144) +
                                 0xe4) +
                        *(short *)(iVar29 + *(short *)(iVar34 + 100) * 0x20 + 4) * 0x110);
      pauVar33 = (undefined1 (*) [16])
                 (*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar34 + 0x48) * 0x4f0 + 0x144) + 0x30) +
                  (uint)*pbVar30 * 0x1f0 + (bGpffff8340 & 1) * 0x40);
      auStack_40 = *pauVar33;
      auStack_30 = pauVar33[1];
      auStack_20 = pauVar33[2];
      auStack_10 = pauVar33[3];
    }
    uStack_120 = in_zero_lo;
    uStack_11c = in_zero_hi;
    uStack_118 = in_zero_udw;
    uStack_114 = in_register_0000000c;
    if (((*(float *)(iVar29 + *(short *)(iVar34 + 100) * 0x20 + 8) == 0.0) &&
        (*(float *)(iVar29 + *(short *)(iVar34 + 100) * 0x20 + 0xc) == 0.0)) &&
       (*(float *)(iVar29 + *(short *)(iVar34 + 100) * 0x20 + 0x10) == 0.0)) {
      RotTransVector(&uStack_c0,pbVar30 + 0x10,auStack_40,8);
      auVar6._4_4_ = uStack_bc;
      auVar6._0_4_ = uStack_c0;
      auVar6._8_4_ = uStack_b8;
      auVar6._12_4_ = uStack_b4;
      auVar35 = _lqc2(auVar6);
      auVar10._4_4_ = uStack_ac;
      auVar10._0_4_ = uStack_b0;
      auVar10._8_4_ = uStack_a8;
      auVar10._12_4_ = uStack_a4;
      auVar36 = _lqc2(auVar10);
      auVar35 = _vadd(auVar35,auVar36);
      auStack_3b0 = _sqc2(auVar35);
      __ct__7FVectorFRC7FVector(auStack_1f0,auStack_3b0);
      auVar35 = _lqc2(auStack_1f0);
      auVar12._4_4_ = uStack_9c;
      auVar12._0_4_ = uStack_a0;
      auVar12._8_4_ = uStack_98;
      auVar12._12_4_ = uStack_94;
      auVar36 = _lqc2(auVar12);
      auVar35 = _vadd(auVar35,auVar36);
      auStack_3c0 = _sqc2(auVar35);
      __ct__7FVectorFRC7FVector(auStack_1e0,auStack_3c0);
      auVar35 = _lqc2(auStack_1e0);
      auVar14._4_4_ = uStack_8c;
      auVar14._0_4_ = uStack_90;
      auVar14._8_4_ = uStack_88;
      auVar14._12_4_ = uStack_84;
      auVar36 = _lqc2(auVar14);
      auVar35 = _vadd(auVar35,auVar36);
      auStack_3d0 = _sqc2(auVar35);
      __ct__7FVectorFRC7FVector(auStack_1d0,auStack_3d0);
      auVar35 = _lqc2(auStack_1d0);
      auVar17._4_4_ = uStack_7c;
      auVar17._0_4_ = uStack_80;
      auVar17._8_4_ = uStack_78;
      auVar17._12_4_ = uStack_74;
      auVar36 = _lqc2(auVar17);
      auVar35 = _vadd(auVar35,auVar36);
      auStack_3e0 = _sqc2(auVar35);
      __ct__7FVectorFRC7FVector(auStack_1c0,auStack_3e0);
      auVar35 = _lqc2(auStack_1c0);
      auVar20._4_4_ = uStack_6c;
      auVar20._0_4_ = uStack_70;
      auVar20._8_4_ = uStack_68;
      auVar20._12_4_ = uStack_64;
      auVar36 = _lqc2(auVar20);
      auVar35 = _vadd(auVar35,auVar36);
      auStack_3f0 = _sqc2(auVar35);
      __ct__7FVectorFRC7FVector(auStack_1b0,auStack_3f0);
      auVar35 = _lqc2(auStack_1b0);
      auVar23._4_4_ = uStack_5c;
      auVar23._0_4_ = uStack_60;
      auVar23._8_4_ = uStack_58;
      auVar23._12_4_ = uStack_54;
      auVar36 = _lqc2(auVar23);
      auVar35 = _vadd(auVar35,auVar36);
      auStack_400 = _sqc2(auVar35);
      __ct__7FVectorFRC7FVector(auStack_1a0,auStack_400);
      auVar35 = _lqc2(auStack_1a0);
      auVar26._4_4_ = uStack_4c;
      auVar26._0_4_ = uStack_50;
      auVar26._8_4_ = uStack_48;
      auVar26._12_4_ = uStack_44;
      auVar36 = _lqc2(auVar26);
      auVar35 = _vadd(auVar35,auVar36);
      auStack_360 = _sqc2(auVar35);
      __ct__7FVectorFRC7FVector(&uStack_190,auStack_360);
      auStack_140._8_4_ = uStack_188;
      auStack_140._0_8_ = uStack_190;
      auStack_140._12_4_ = uStack_184;
      __adv__7FVectorFf(0x41000000,auStack_140);
    }
    else {
      uStack_158 = *(undefined4 *)(iVar29 + *(short *)(iVar34 + 100) * 0x20 + 0x10);
      uStack_15c = *(undefined4 *)(iVar29 + *(short *)(iVar34 + 100) * 0x20 + 0xc);
      uStack_160 = *(undefined4 *)(iVar29 + *(short *)(iVar34 + 100) * 0x20 + 8);
      uStack_154 = 0x3f800000;
      uStack_b4 = 0x3f800000;
      uStack_178 = *(undefined4 *)(iVar29 + *(short *)(iVar34 + 100) * 0x20 + 0x1c);
      uStack_17c = *(undefined4 *)(iVar29 + *(short *)(iVar34 + 100) * 0x20 + 0x18);
      uStack_180 = *(undefined4 *)(iVar29 + *(short *)(iVar34 + 100) * 0x20 + 0x14);
      uStack_174 = 0x3f800000;
      auVar5._4_4_ = uStack_15c;
      auVar5._0_4_ = uStack_160;
      auVar5._8_4_ = uStack_158;
      auVar5._12_4_ = 0x3f800000;
      auVar35 = _lqc2(auVar5);
      auVar3._4_4_ = uStack_17c;
      auVar3._0_4_ = uStack_180;
      auVar3._8_4_ = uStack_178;
      auVar3._12_4_ = 0x3f800000;
      auVar36 = _lqc2(auVar3);
      auVar35 = _vadd(auVar35,auVar36);
      auStack_350 = _sqc2(auVar35);
      uStack_c0 = uStack_160;
      uStack_bc = uStack_15c;
      uStack_b8 = uStack_158;
      __ct__7FVectorFRC7FVector(auStack_170,auStack_350);
      uStack_b0 = auStack_170._0_4_;
      uStack_ac = auStack_170._4_4_;
      uStack_a8 = uStack_168;
      uStack_a4 = uStack_164;
      RotTransVector(auStack_140,&uStack_c0,auStack_40,2);
    }
    if (*(short *)(iVar29 + *(short *)(iVar34 + 100) * 0x20 + 6) < -1) {
      if (*(short *)(iVar29 + 2) == 2) {
        pbVar30 = (byte *)(*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar34 + 0x48) * 0x4f0
                                                     + 0x144) + 0x530) + 0xe4) +
                          *(short *)(iVar29 + *(short *)(iVar34 + 100) * 0x20 + 6) * -0x110);
        pauVar33 = (undefined1 (*) [16])
                   (*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar34 + 0x48) * 0x4f0 + 0x144
                                              ) + 0x530) + 0x30) + (uint)*pbVar30 * 0x1f0 +
                   (bGpffff8340 & 1) * 0x40);
        auStack_40 = *pauVar33;
        auStack_30 = pauVar33[1];
        auStack_20 = pauVar33[2];
        auStack_10 = pauVar33[3];
      }
      else if (*(short *)(iVar29 + 2) == 1) {
        pbVar30 = (byte *)(*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar34 + 0x48) * 0x4f0
                                                     + 0x144) + 0x52c) + 0xe4) +
                          *(short *)(iVar29 + *(short *)(iVar34 + 100) * 0x20 + 6) * -0x110);
        pauVar33 = (undefined1 (*) [16])
                   (*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar34 + 0x48) * 0x4f0 + 0x144
                                              ) + 0x52c) + 0x30) + (uint)*pbVar30 * 0x1f0 +
                   (bGpffff8340 & 1) * 0x40);
        auStack_40 = *pauVar33;
        auStack_30 = pauVar33[1];
        auStack_20 = pauVar33[2];
        auStack_10 = pauVar33[3];
      }
      else {
        pbVar30 = (byte *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar34 + 0x48) * 0x4f0 + 0x144)
                                   + 0xe4) +
                          *(short *)(iVar29 + *(short *)(iVar34 + 100) * 0x20 + 6) * -0x110);
        pauVar33 = (undefined1 (*) [16])
                   (*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar34 + 0x48) * 0x4f0 + 0x144) + 0x30)
                    + (uint)*pbVar30 * 0x1f0 + (bGpffff8340 & 1) * 0x40);
        auStack_40 = *pauVar33;
        auStack_30 = pauVar33[1];
        auStack_20 = pauVar33[2];
        auStack_10 = pauVar33[3];
      }
      if (((*(float *)(iVar29 + *(short *)(iVar34 + 100) * 0x20 + 8) == 0.0) &&
          (*(float *)(iVar29 + *(short *)(iVar34 + 100) * 0x20 + 0xc) == 0.0)) &&
         (*(float *)(iVar29 + *(short *)(iVar34 + 100) * 0x20 + 0x10) == 0.0)) {
        RotTransVector(&uStack_c0,pbVar30 + 0x10,auStack_40,8);
        auVar8._4_4_ = uStack_bc;
        auVar8._0_4_ = uStack_c0;
        auVar8._8_4_ = uStack_b8;
        auVar8._12_4_ = uStack_b4;
        auVar35 = _lqc2(auVar8);
        auVar11._4_4_ = uStack_ac;
        auVar11._0_4_ = uStack_b0;
        auVar11._8_4_ = uStack_a8;
        auVar11._12_4_ = uStack_a4;
        auVar36 = _lqc2(auVar11);
        auVar35 = _vadd(auVar35,auVar36);
        auStack_410 = _sqc2(auVar35);
        __ct__7FVectorFRC7FVector(auStack_290,auStack_410);
        auVar35 = _lqc2(auStack_290);
        auVar13._4_4_ = uStack_9c;
        auVar13._0_4_ = uStack_a0;
        auVar13._8_4_ = uStack_98;
        auVar13._12_4_ = uStack_94;
        auVar36 = _lqc2(auVar13);
        auVar35 = _vadd(auVar35,auVar36);
        auStack_420 = _sqc2(auVar35);
        __ct__7FVectorFRC7FVector(auStack_280,auStack_420);
        auVar35 = _lqc2(auStack_280);
        auVar15._4_4_ = uStack_8c;
        auVar15._0_4_ = uStack_90;
        auVar15._8_4_ = uStack_88;
        auVar15._12_4_ = uStack_84;
        auVar36 = _lqc2(auVar15);
        auVar35 = _vadd(auVar35,auVar36);
        auStack_430 = _sqc2(auVar35);
        __ct__7FVectorFRC7FVector(auStack_270,auStack_430);
        auVar35 = _lqc2(auStack_270);
        auVar18._4_4_ = uStack_7c;
        auVar18._0_4_ = uStack_80;
        auVar18._8_4_ = uStack_78;
        auVar18._12_4_ = uStack_74;
        auVar36 = _lqc2(auVar18);
        auVar35 = _vadd(auVar35,auVar36);
        auStack_440 = _sqc2(auVar35);
        __ct__7FVectorFRC7FVector(auStack_260,auStack_440);
        auVar35 = _lqc2(auStack_260);
        auVar21._4_4_ = uStack_6c;
        auVar21._0_4_ = uStack_70;
        auVar21._8_4_ = uStack_68;
        auVar21._12_4_ = uStack_64;
        auVar36 = _lqc2(auVar21);
        auVar35 = _vadd(auVar35,auVar36);
        auStack_450 = _sqc2(auVar35);
        __ct__7FVectorFRC7FVector(auStack_250,auStack_450);
        auVar35 = _lqc2(auStack_250);
        auVar24._4_4_ = uStack_5c;
        auVar24._0_4_ = uStack_60;
        auVar24._8_4_ = uStack_58;
        auVar24._12_4_ = uStack_54;
        auVar36 = _lqc2(auVar24);
        auVar35 = _vadd(auVar35,auVar36);
        auStack_460 = _sqc2(auVar35);
        __ct__7FVectorFRC7FVector(auStack_240,auStack_460);
        auVar35 = _lqc2(auStack_240);
        auVar27._4_4_ = uStack_4c;
        auVar27._0_4_ = uStack_50;
        auVar27._8_4_ = uStack_48;
        auVar27._12_4_ = uStack_44;
        auVar36 = _lqc2(auVar27);
        auVar35 = _vadd(auVar35,auVar36);
        auStack_380 = _sqc2(auVar35);
        __ct__7FVectorFRC7FVector(&uStack_230,auStack_380);
        auStack_130._8_4_ = uStack_228;
        auStack_130._0_8_ = uStack_230;
        auStack_130._12_4_ = uStack_224;
        __adv__7FVectorFf(0x41000000,auStack_130);
        auVar36 = _lqc2(auStack_130);
        auVar35 = _lqc2(auStack_140);
        auVar35 = _vadd(auVar35,auVar36);
        auStack_140 = _sqc2(auVar35);
        __adv__7FVectorFf(0x40000000,auStack_140);
      }
      else {
        uStack_1f8 = *(undefined4 *)(iVar29 + *(short *)(iVar34 + 100) * 0x20 + 0x10);
        uStack_1fc = *(undefined4 *)(iVar29 + *(short *)(iVar34 + 100) * 0x20 + 0xc);
        uStack_200 = *(undefined4 *)(iVar29 + *(short *)(iVar34 + 100) * 0x20 + 8);
        uStack_1f4 = 0x3f800000;
        uStack_b4 = 0x3f800000;
        uStack_218 = *(undefined4 *)(iVar29 + *(short *)(iVar34 + 100) * 0x20 + 0x1c);
        uStack_21c = *(undefined4 *)(iVar29 + *(short *)(iVar34 + 100) * 0x20 + 0x18);
        uStack_220 = *(undefined4 *)(iVar29 + *(short *)(iVar34 + 100) * 0x20 + 0x14);
        uStack_214 = 0x3f800000;
        auVar7._4_4_ = uStack_1fc;
        auVar7._0_4_ = uStack_200;
        auVar7._8_4_ = uStack_1f8;
        auVar7._12_4_ = 0x3f800000;
        auVar35 = _lqc2(auVar7);
        auVar2._4_4_ = uStack_21c;
        auVar2._0_4_ = uStack_220;
        auVar2._8_4_ = uStack_218;
        auVar2._12_4_ = 0x3f800000;
        auVar36 = _lqc2(auVar2);
        auVar35 = _vadd(auVar35,auVar36);
        auStack_370 = _sqc2(auVar35);
        uStack_c0 = uStack_200;
        uStack_bc = uStack_1fc;
        uStack_b8 = uStack_1f8;
        __ct__7FVectorFRC7FVector(auStack_210,auStack_370);
        uStack_b0 = auStack_210._0_4_;
        uStack_ac = auStack_210._4_4_;
        uStack_a8 = uStack_208;
        uStack_a4 = uStack_204;
        RotTransVector(&uStack_120,&uStack_c0,auStack_40,2);
        auVar4._4_4_ = uStack_11c;
        auVar4._0_4_ = uStack_120;
        auVar4._8_4_ = uStack_118;
        auVar4._12_4_ = uStack_114;
        auVar36 = _lqc2(auVar4);
        auVar35 = _lqc2(auStack_140);
        auVar35 = _vadd(auVar35,auVar36);
        auStack_140 = _sqc2(auVar35);
        __adv__7FVectorFf(0x40000000,auStack_140);
      }
    }
  }
  else {
    if (*(short *)(iVar29 + 2) == 2) {
      pbVar30 = (byte *)(*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar34 + 0x48) * 0x4f0 +
                                                   0x144) + 0x530) + 0xe4) +
                        *(short *)(iVar29 + *(short *)(iVar34 + 100) * 0x20 + 6) * 0x110);
      pauVar33 = (undefined1 (*) [16])
                 (*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar34 + 0x48) * 0x4f0 + 0x144)
                                   + 0x530) + 0x30) + (uint)*pbVar30 * 0x1f0 +
                 (bGpffff8340 & 1) * 0x40);
      auStack_40 = *pauVar33;
      auStack_30 = pauVar33[1];
      auStack_20 = pauVar33[2];
      auStack_10 = pauVar33[3];
    }
    else if (*(short *)(iVar29 + 2) == 1) {
      pbVar30 = (byte *)(*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar34 + 0x48) * 0x4f0 +
                                                   0x144) + 0x52c) + 0xe4) +
                        *(short *)(iVar29 + *(short *)(iVar34 + 100) * 0x20 + 6) * 0x110);
      pauVar33 = (undefined1 (*) [16])
                 (*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar34 + 0x48) * 0x4f0 + 0x144)
                                   + 0x52c) + 0x30) + (uint)*pbVar30 * 0x1f0 +
                 (bGpffff8340 & 1) * 0x40);
      auStack_40 = *pauVar33;
      auStack_30 = pauVar33[1];
      auStack_20 = pauVar33[2];
      auStack_10 = pauVar33[3];
    }
    else {
      pbVar30 = (byte *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar34 + 0x48) * 0x4f0 + 0x144) +
                                 0xe4) +
                        *(short *)(iVar29 + *(short *)(iVar34 + 100) * 0x20 + 6) * 0x110);
      pauVar33 = (undefined1 (*) [16])
                 (*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar34 + 0x48) * 0x4f0 + 0x144) + 0x30) +
                  (uint)*pbVar30 * 0x1f0 + (bGpffff8340 & 1) * 0x40);
      auStack_40 = *pauVar33;
      auStack_30 = pauVar33[1];
      auStack_20 = pauVar33[2];
      auStack_10 = pauVar33[3];
    }
    if (((*(float *)(iVar29 + *(short *)(iVar34 + 100) * 0x20 + 8) == 0.0) &&
        (*(float *)(iVar29 + *(short *)(iVar34 + 100) * 0x20 + 0xc) == 0.0)) &&
       (*(float *)(iVar29 + *(short *)(iVar34 + 100) * 0x20 + 0x10) == 0.0)) {
      RotTransVector(&uStack_c0,pbVar30 + 0x10,auStack_40,8);
      auVar35._4_4_ = uStack_bc;
      auVar35._0_4_ = uStack_c0;
      auVar35._8_4_ = uStack_b8;
      auVar35._12_4_ = uStack_b4;
      auVar35 = _lqc2(auVar35);
      auVar36._4_4_ = uStack_ac;
      auVar36._0_4_ = uStack_b0;
      auVar36._8_4_ = uStack_a8;
      auVar36._12_4_ = uStack_a4;
      auVar36 = _lqc2(auVar36);
      auVar35 = _vadd(auVar35,auVar36);
      auStack_470 = _sqc2(auVar35);
      __ct__7FVectorFRC7FVector(auStack_330,auStack_470);
      auVar35 = _lqc2(auStack_330);
      auVar37._4_4_ = uStack_9c;
      auVar37._0_4_ = uStack_a0;
      auVar37._8_4_ = uStack_98;
      auVar37._12_4_ = uStack_94;
      auVar36 = _lqc2(auVar37);
      auVar35 = _vadd(auVar35,auVar36);
      auStack_480 = _sqc2(auVar35);
      __ct__7FVectorFRC7FVector(auStack_320,auStack_480);
      auVar35 = _lqc2(auStack_320);
      auVar16._4_4_ = uStack_8c;
      auVar16._0_4_ = uStack_90;
      auVar16._8_4_ = uStack_88;
      auVar16._12_4_ = uStack_84;
      auVar36 = _lqc2(auVar16);
      auVar35 = _vadd(auVar35,auVar36);
      auStack_490 = _sqc2(auVar35);
      __ct__7FVectorFRC7FVector(auStack_310,auStack_490);
      auVar35 = _lqc2(auStack_310);
      auVar19._4_4_ = uStack_7c;
      auVar19._0_4_ = uStack_80;
      auVar19._8_4_ = uStack_78;
      auVar19._12_4_ = uStack_74;
      auVar36 = _lqc2(auVar19);
      auVar35 = _vadd(auVar35,auVar36);
      auStack_4a0 = _sqc2(auVar35);
      __ct__7FVectorFRC7FVector(auStack_300,auStack_4a0);
      auVar35 = _lqc2(auStack_300);
      auVar22._4_4_ = uStack_6c;
      auVar22._0_4_ = uStack_70;
      auVar22._8_4_ = uStack_68;
      auVar22._12_4_ = uStack_64;
      auVar36 = _lqc2(auVar22);
      auVar35 = _vadd(auVar35,auVar36);
      auStack_4b0 = _sqc2(auVar35);
      __ct__7FVectorFRC7FVector(auStack_2f0,auStack_4b0);
      auVar35 = _lqc2(auStack_2f0);
      auVar25._4_4_ = uStack_5c;
      auVar25._0_4_ = uStack_60;
      auVar25._8_4_ = uStack_58;
      auVar25._12_4_ = uStack_54;
      auVar36 = _lqc2(auVar25);
      auVar35 = _vadd(auVar35,auVar36);
      auStack_4c0 = _sqc2(auVar35);
      __ct__7FVectorFRC7FVector(auStack_2e0,auStack_4c0);
      auVar35 = _lqc2(auStack_2e0);
      auVar28._4_4_ = uStack_4c;
      auVar28._0_4_ = uStack_50;
      auVar28._8_4_ = uStack_48;
      auVar28._12_4_ = uStack_44;
      auVar36 = _lqc2(auVar28);
      auVar35 = _vadd(auVar35,auVar36);
      auStack_3a0 = _sqc2(auVar35);
      __ct__7FVectorFRC7FVector(&uStack_2d0,auStack_3a0);
      auStack_140._8_4_ = uStack_2c8;
      auStack_140._0_8_ = uStack_2d0;
      auStack_140._12_4_ = uStack_2c4;
      __adv__7FVectorFf(0x41000000,auStack_140);
    }
    else {
      uStack_298 = *(undefined4 *)(iVar29 + *(short *)(iVar34 + 100) * 0x20 + 0x10);
      uStack_29c = *(undefined4 *)(iVar29 + *(short *)(iVar34 + 100) * 0x20 + 0xc);
      uStack_2a0 = *(undefined4 *)(iVar29 + *(short *)(iVar34 + 100) * 0x20 + 8);
      uStack_294 = 0x3f800000;
      uStack_b4 = 0x3f800000;
      uStack_2b8 = *(undefined4 *)(iVar29 + *(short *)(iVar34 + 100) * 0x20 + 0x1c);
      uStack_2bc = *(undefined4 *)(iVar29 + *(short *)(iVar34 + 100) * 0x20 + 0x18);
      uStack_2c0 = *(undefined4 *)(iVar29 + *(short *)(iVar34 + 100) * 0x20 + 0x14);
      uStack_2b4 = 0x3f800000;
      auVar9._4_4_ = uStack_29c;
      auVar9._0_4_ = uStack_2a0;
      auVar9._8_4_ = uStack_298;
      auVar9._12_4_ = 0x3f800000;
      auVar35 = _lqc2(auVar9);
      auVar1._4_4_ = uStack_2bc;
      auVar1._0_4_ = uStack_2c0;
      auVar1._8_4_ = uStack_2b8;
      auVar1._12_4_ = 0x3f800000;
      auVar36 = _lqc2(auVar1);
      auVar35 = _vadd(auVar35,auVar36);
      auStack_390 = _sqc2(auVar35);
      uStack_c0 = uStack_2a0;
      uStack_bc = uStack_29c;
      uStack_b8 = uStack_298;
      __ct__7FVectorFRC7FVector(auStack_2b0,auStack_390);
      uStack_b0 = auStack_2b0._0_4_;
      uStack_ac = auStack_2b0._4_4_;
      uStack_a8 = uStack_2a8;
      uStack_a4 = uStack_2a4;
      RotTransVector(auStack_140,&uStack_c0,auStack_40,2);
    }
  }
  *(int *)(iVar34 + 0x70) = auStack_140._0_4_;
  *(int *)(iVar34 + 0x74) = auStack_140._4_4_;
  *(undefined4 *)(iVar34 + 0x78) = auStack_140._8_4_;
  *(undefined4 *)(iVar34 + 0x7c) = auStack_140._12_4_;
  *(int *)(iVar34 + 0x80) = auStack_140._0_4_;
  *(int *)(iVar34 + 0x84) = auStack_140._4_4_;
  *(undefined4 *)(iVar34 + 0x88) = auStack_140._8_4_;
  *(undefined4 *)(iVar34 + 0x8c) = auStack_140._12_4_;
  auVar36 = _lqc2(auStack_140);
  auVar35 = _lqc2(auStack_130);
  auVar35 = _vsub(auVar35,auVar36);
  auStack_130 = _sqc2(auVar35);
  uVar31 = __ct__7FVectorFRC7FVector(auStack_340,auStack_130);
  Get3DAngle__F7FVector(&uStack_150,uVar31);
  *(undefined4 *)(iVar34 + 0x90) = uStack_150;
  *(float *)(iVar34 + 0x94) = 180.0 - fStack_14c;
  iVar29 = rand();
  *(float *)(iVar34 + 0x98) = ((float)iVar29 / 2.1474836e+09) * 6.2831855 - 3.1415927;
  *(undefined4 *)(iVar34 + 0x9c) = 0x3f800000;
  Entry__7CPollerFP7CPolObjib(iGpffff858c + 0x48,param_2,0x80,0);
  BtlEffEntry__7CBattleFiP6BtlEff(iGpffff86b4,*(undefined4 *)(iVar34 + 0x48),param_2);
  return param_2;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00542b30  __dt__12Bullet3ChildFv
 * C++: Bullet3Child::__dt()
 * size: 0x154 bytes
 * --------------------------------------------------------------------------- */
int __dt__12Bullet3ChildFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x14) = 0x4099d0;
    *(undefined4 *)(param_1 + 0x28) = 0x4099e0;
    *(undefined4 *)(param_1 + 0x34) = 0x4099f0;
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
 * JP: 0x00542c90  Destruct__12Bullet3ChildFv
 * C++: Bullet3Child::Destruct()
 * size: 0xdc bytes
 * --------------------------------------------------------------------------- */
void Destruct__12Bullet3ChildFv(int param_1)

{
  int iVar1;
  
  *(int *)(*(int *)(param_1 + 0x5c) + 0x8c) = *(int *)(*(int *)(param_1 + 0x5c) + 0x8c) + -1;
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
 * JP: 0x00542d70  Polling__12Bullet3ChildFv
 * C++: Bullet3Child::Polling()
 * size: 0x654 bytes
 * --------------------------------------------------------------------------- */
undefined4 Polling__12Bullet3ChildFv(int param_1)

{
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  char cVar1;
  FVector *pFVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  int iVar5;
  undefined4 uVar6;
  float fVar7;
  undefined1 in_vf0 [16];
  undefined1 auVar8 [16];
  undefined1 auVar9 [16];
  undefined1 auVar10 [16];
  undefined1 auStack_d0 [16];
  undefined1 auStack_c0 [16];
  undefined1 auStack_b0 [16];
  undefined1 auStack_a0 [16];
  undefined1 auStack_90 [16];
  undefined4 uStack_80;
  undefined4 uStack_7c;
  float fStack_78;
  undefined4 uStack_74;
  undefined8 uStack_70;
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined1 auStack_60 [16];
  undefined1 auStack_50 [16];
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [16];
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  auVar8 = _vmr32(in_vf0);
  auVar9 = _vmr32(auVar8);
  auVar10 = _vmr32(auVar9);
  auStack_30 = _sqc2(in_vf0);
  auStack_40 = _sqc2(auVar8);
  auStack_50 = _sqc2(auVar9);
  auStack_60 = _sqc2(auVar10);
  fVar7 = pCGpffff86b4->flDeltaT;
  if ((pCGpffff86b4->bFlags24 & 1) != 0) {
    fVar7 = 0.0;
  }
  *(float *)(param_1 + 0xc0) = *(float *)(param_1 + 0xc0) + fVar7;
  uStack_10 = in_zero_lo;
  uStack_c = in_zero_hi;
  uStack_8 = in_zero_udw;
  uStack_4 = in_register_0000000c;
  if (*(int *)(param_1 + 0xbc) == 0) {
    if (fVar7 != 0.0) {
      auVar8 = _vmr32(in_vf0);
      auVar9 = _vmr32(auVar8);
      auVar10 = _vmr32(auVar9);
      auStack_30 = _sqc2(in_vf0);
      auStack_40 = _sqc2(auVar8);
      auStack_50 = _sqc2(auVar9);
      auStack_60 = _sqc2(auVar10);
      uVar6 = GetRad(*(undefined4 *)(param_1 + 0x90));
      sceVu0RotMatrixX(uVar6,auStack_60,auStack_60);
      uVar6 = GetRad(*(undefined4 *)(param_1 + 0x94));
      sceVu0RotMatrixY(uVar6,auStack_60,auStack_60);
      uStack_80 = 0;
      uStack_7c = 0;
      fStack_78 = fVar7 * -3.0 * 30.0;
      uStack_74 = 0x3f800000;
      ApplyMatrix__6MatrixCFRC7FVector(&uStack_70,auStack_60,&uStack_80);
      uStack_10 = (undefined4)uStack_70;
      uStack_c = (undefined4)((ulong)uStack_70 >> 0x20);
      uStack_8 = uStack_68;
      uStack_4 = uStack_64;
      *(int *)(param_1 + 0x80) = (int)*(undefined8 *)(param_1 + 0x70);
      *(int *)(param_1 + 0x84) = (int)((ulong)*(undefined8 *)(param_1 + 0x70) >> 0x20);
      *(undefined4 *)(param_1 + 0x88) = *(undefined4 *)(param_1 + 0x78);
      *(undefined4 *)(param_1 + 0x8c) = *(undefined4 *)(param_1 + 0x7c);
      auVar8._8_4_ = uStack_68;
      auVar8._0_8_ = uStack_70;
      auVar8._12_4_ = uStack_64;
      auVar9 = _lqc2(auVar8);
      auVar8 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x70));
      auVar8 = _vadd(auVar8,auVar9);
      auVar8 = _sqc2(auVar8);
      *(undefined1 (*) [16])(param_1 + 0x70) = auVar8;
    }
    if (((long)((ulong)*(byte *)(param_1 + 0x40) << 0x3d) < 0) && (fVar7 != 0.0)) {
      *(undefined4 *)(param_1 + 0xbc) = 1;
    }
    if (*(float *)(param_1 + 0x80) < (-*(float *)&pCGpffff86b4->field_0x3f14 - 10.0) / 2.0) {
      *(undefined4 *)(param_1 + 0xbc) = 1;
    }
    if ((*(float *)&pCGpffff86b4->field_0x3f14 + 10.0) / 2.0 < *(float *)(param_1 + 0x80)) {
      *(undefined4 *)(param_1 + 0xbc) = 1;
    }
    if (*(float *)(param_1 + 0x88) < (-*(float *)&pCGpffff86b4->field_0x3f1c - 10.0) / 2.0) {
      *(undefined4 *)(param_1 + 0xbc) = 1;
    }
    if ((*(float *)&pCGpffff86b4->field_0x3f1c + 10.0) / 2.0 < *(float *)(param_1 + 0x88)) {
      *(undefined4 *)(param_1 + 0xbc) = 1;
    }
    if (((((-1 < *(int *)(param_1 + 0x60)) &&
          (-1 < (long)((ulong)*(byte *)(param_1 + 0x40) << 0x3d))) &&
         (*(int *)(param_1 + 0xbc) == 0)) &&
        ((*(int *)(*(int *)(param_1 + 0x5c) + 0x84) == 0 &&
         (-1 < (long)((ulong)pCGpffff86b4->aChr[*(int *)(param_1 + 0x60)].bFlagsB << 0x3c))))) &&
       ((pCGpffff86b4->aChr[*(int *)(param_1 + 0x60)].bState != 0x29 &&
        (pCGpffff86b4->aChr[*(int *)(param_1 + 0x60)].bState != 0x2c)))) {
      uVar3 = __ct__7FVectorFRC7FVector(auStack_90,param_1 + 0x70);
      cVar1 = VSCircleHitCheck__7CBattleFi7FVectorfP7FVector
                        (0x3f800000,pCGpffff86b4,*(undefined4 *)(param_1 + 0x60),uVar3,&uStack_10);
      if (cVar1 == '\x01') {
        pFVar2 = (FVector *)__ct__7FVectorFRC7FVector(auStack_a0,&uStack_10);
        PAtkHitSet__7CBattleFii7FVectorfiiiiUsUsfii
                  (pCGpffff86b4,*(int *)(param_1 + 0x48),*(int *)(param_1 + 0x60),pFVar2,
                   *(float *)(param_1 + 0x94),*(int *)(param_1 + 0xa0),*(int *)(param_1 + 0xa4),
                   *(int *)(param_1 + 0xa8),*(int *)(param_1 + 0xac),*(ushort *)(param_1 + 0xb0),
                   *(ushort *)(param_1 + 0xb2),*(float *)(param_1 + 0x68),*(int *)(param_1 + 0xb4),
                   *(int *)(param_1 + 0xb8));
        *(undefined4 *)(*(int *)(param_1 + 0x5c) + 0x84) = 1;
        *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfb | 4;
      }
      else {
        uVar3 = __ct__7FVectorFRC7FVector(auStack_b0,param_1 + 0x70);
        uVar4 = __ct__7FVectorFRC7FVector(auStack_c0,param_1 + 0x80);
        cVar1 = VSLineHitCheck__7CBattleFi7FVector7FVectorP7FVector
                          (pCGpffff86b4,*(undefined4 *)(param_1 + 0x60),uVar3,uVar4,&uStack_10);
        if (cVar1 == '\x01') {
          pFVar2 = (FVector *)__ct__7FVectorFRC7FVector(auStack_d0,&uStack_10);
          PAtkHitSet__7CBattleFii7FVectorfiiiiUsUsfii
                    (pCGpffff86b4,*(int *)(param_1 + 0x48),*(int *)(param_1 + 0x60),pFVar2,
                     *(float *)(param_1 + 0x94),*(int *)(param_1 + 0xa0),*(int *)(param_1 + 0xa4),
                     *(int *)(param_1 + 0xa8),*(int *)(param_1 + 0xac),*(ushort *)(param_1 + 0xb0),
                     *(ushort *)(param_1 + 0xb2),*(float *)(param_1 + 0x68),*(int *)(param_1 + 0xb4)
                     ,*(int *)(param_1 + 0xb8));
          *(undefined4 *)(*(int *)(param_1 + 0x5c) + 0x84) = 1;
          *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfb | 4;
        }
      }
    }
  }
  if ((*(int *)(param_1 + 0xbc) != 0) || (0.4 <= *(float *)(param_1 + 0xc0))) {
    *(int *)(*(int *)(param_1 + 0x5c) + 0x8c) = *(int *)(*(int *)(param_1 + 0x5c) + 0x8c) + -1;
    BtlEffRelease__7CBattleFiP6BtlEff(pCGpffff86b4,*(undefined4 *)(param_1 + 0x48),param_1);
    if ((long)((ulong)*(byte *)(param_1 + 0x40) << 0x3e) < 0) {
      iVar5 = param_1;
      if (param_1 != 0) {
        iVar5 = param_1 + 0x18;
      }
      ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,iVar5);
    }
    *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfd;
    (**(code **)(*(int *)(param_1 + 0x34) + 0xc))();
    uVar6 = 1;
  }
  else {
    uVar6 = 0;
  }
  return uVar6;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005433d0  MakePacket__12Bullet3ChildFv
 * C++: Bullet3Child::MakePacket()
 * size: 0x94c bytes
 * --------------------------------------------------------------------------- */
void MakePacket__12Bullet3ChildFv(int param_1)

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
  int iVar8;
  uint uVar9;
  undefined1 in_vf0 [16];
  undefined1 auVar10 [16];
  undefined1 auVar11 [16];
  undefined1 auVar12 [16];
  undefined1 auStack_200 [64];
  float fStack_1c0;
  float fStack_1bc;
  undefined4 uStack_1b8;
  undefined4 uStack_1b4;
  float fStack_1b0;
  float fStack_1ac;
  undefined4 uStack_1a8;
  undefined4 uStack_1a4;
  float fStack_1a0;
  float fStack_19c;
  undefined4 uStack_198;
  undefined4 uStack_194;
  float fStack_190;
  float fStack_18c;
  undefined4 uStack_188;
  undefined4 uStack_184;
  int aiStack_180 [6];
  int iStack_168;
  int iStack_160;
  int iStack_15c;
  int iStack_158;
  int iStack_150;
  int iStack_14c;
  int iStack_148;
  undefined4 auStack_140 [16];
  float afStack_100 [16];
  undefined1 auStack_c0 [64];
  undefined1 auStack_80 [16];
  undefined1 auStack_70 [16];
  undefined1 auStack_60 [16];
  undefined1 auStack_50 [16];
  float afStack_40 [6];
  undefined4 uStack_28;
  undefined4 uStack_24;
  float fStack_20;
  float fStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  float fStack_10;
  float fStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  fStack_1c0 = *(float *)(param_1 + 0xc0) * 6.0;
  if (fStack_1c0 < 0.75) {
    fStack_1c0 = 0.75;
  }
  fStack_190 = -fStack_1c0;
  fStack_18c = -fStack_1c0;
  uStack_188 = 0;
  uStack_184 = 0x3f800000;
  afStack_40[2] = 0.0;
  afStack_40[3] = 1.0;
  fStack_1a0 = -fStack_1c0;
  uStack_198 = 0;
  uStack_194 = 0x3f800000;
  uStack_28 = 0;
  uStack_24 = 0x3f800000;
  fStack_1ac = -fStack_1c0;
  uStack_1a8 = 0;
  uStack_1a4 = 0x3f800000;
  uStack_18 = 0;
  uStack_14 = 0x3f800000;
  uStack_1b8 = 0;
  uStack_1b4 = 0x3f800000;
  uStack_8 = 0;
  uStack_4 = 0x3f800000;
  auVar10 = _vmr32(in_vf0);
  auVar11 = _vmr32(auVar10);
  auVar12 = _vmr32(auVar11);
  _sqc2(in_vf0);
  _sqc2(auVar10);
  _sqc2(auVar11);
  _sqc2(auVar12);
  auVar10 = _vmr32(in_vf0);
  auVar11 = _vmr32(auVar10);
  auVar12 = _vmr32(auVar11);
  auStack_50 = _sqc2(in_vf0);
  auStack_60 = _sqc2(auVar10);
  auStack_70 = _sqc2(auVar11);
  auStack_80 = _sqc2(auVar12);
  fStack_1bc = fStack_1c0;
  fStack_1b0 = fStack_1c0;
  fStack_19c = fStack_1c0;
  afStack_40[0] = fStack_190;
  afStack_40[1] = fStack_18c;
  afStack_40[4] = fStack_1a0;
  afStack_40[5] = fStack_1c0;
  fStack_20 = fStack_1c0;
  fStack_1c = fStack_1ac;
  fStack_10 = fStack_1c0;
  fStack_c = fStack_1c0;
  sceVu0RotMatrixZ(*(undefined4 *)(param_1 + 0x98),auStack_80,auStack_80);
  RotTransVector(auStack_c0,afStack_40,auStack_80,4);
  auStack_80 = *(undefined1 (*) [16])(iGpffff8598 + 0x240);
  auStack_70 = *(undefined1 (*) [16])(iGpffff8598 + 0x250);
  auStack_60 = *(undefined1 (*) [16])(iGpffff8598 + 0x260);
  auStack_50._0_12_ = ZEXT812(0);
  auStack_50._12_4_ = 0x3f800000;
  RotTransVector(afStack_40,auStack_c0,auStack_80,4);
  for (iVar7 = 0; iVar7 < 4; iVar7 = iVar7 + 1) {
    afStack_100[iVar7 * 4] = *(float *)(param_1 + 0x70) + afStack_40[iVar7 * 4] * 5.0;
    afStack_100[iVar7 * 4 + 1] = *(float *)(param_1 + 0x74) + afStack_40[iVar7 * 4 + 1] * 5.0;
    afStack_100[iVar7 * 4 + 2] = *(float *)(param_1 + 0x78) + afStack_40[iVar7 * 4 + 2] * 5.0;
    afStack_100[iVar7 * 4 + 3] = 1.0;
  }
  GetViewScreenMatrix__9GsxCameraFv(auStack_200,iGpffff8598);
  for (iVar7 = 0; iVar7 < 4; iVar7 = iVar7 + 1) {
    auStack_140[iVar7 * 4] = *(undefined4 *)(auStack_80 + iVar7 * 0x10);
    auStack_140[iVar7 * 4 + 1] = *(undefined4 *)(auStack_80 + iVar7 * 0x10 + 4);
    auStack_140[iVar7 * 4 + 2] = *(undefined4 *)(auStack_80 + iVar7 * 0x10 + 8);
    auStack_140[iVar7 * 4 + 3] = *(undefined4 *)(auStack_80 + iVar7 * 0x10 + 0xc);
  }
  sceVu0RotTransPersN(aiStack_180,auStack_140,afStack_100,4,0);
  bVar3 = false;
  iVar7 = 0;
  for (iVar8 = 0; iVar8 < 4; iVar8 = iVar8 + 1) {
    if ((((aiStack_180[iVar8 * 4] < 0) || (0x10000 < aiStack_180[iVar8 * 4])) ||
        (aiStack_180[iVar8 * 4 + 1] < 0)) ||
       ((0x10000 < aiStack_180[iVar8 * 4 + 1] || (aiStack_180[iVar8 * 4 + 2] < 0)))) {
      bVar3 = true;
    }
    aiStack_180[iVar8 * 4 + 2] = (int)((float)aiStack_180[iVar8 * 4 + 2] / 16.0);
    iVar7 = iVar7 + aiStack_180[iVar8 * 4 + 2];
  }
  if (iVar7 < 0) {
    iVar7 = iVar7 + 3;
  }
  *(int *)(param_1 + 0x50) = iVar7 >> 2;
  bVar1 = (*(byte *)(param_1 + 0x40) & 1) == 0;
  uVar9 = (uint)bVar1;
  if (*(int *)(param_1 + uVar9 * 4 + 0x18) == 0) {
    uVar4 = __nwa__FUi(0x100);
    *(undefined4 *)(param_1 + uVar9 * 4 + 0x18) = uVar4;
    iVar7 = *(int *)(param_1 + uVar9 * 4 + 0x18);
    *(undefined4 *)(iVar7 + 0x10) = 0x1000000d;
    *(undefined4 *)(iVar7 + 0x14) = 0;
    *(undefined4 *)(iVar7 + 0x18) = 0;
    *(undefined4 *)(iVar7 + 0x1c) = 0x5000000d;
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
    uVar5 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x42f8),1);
    *(undefined8 *)(iVar7 + 0x70) = uVar5;
    *(undefined8 *)(iVar7 + 0x78) = 0;
    *(undefined8 *)(iVar7 + 0x80) = 0x48;
    *(undefined8 *)(iVar7 + 0x88) = 0x42;
    auVar11._8_8_ = in_v1_udw;
    auVar11._0_8_ = 0xa400000000008001;
    auVar10._4_4_ = in_zero_hi;
    auVar10._0_4_ = in_zero_lo;
    auVar10._8_4_ = in_zero_udw;
    auVar10._12_4_ = in_register_0000000c;
    auVar10 = _pcpyld(auVar10,auVar11);
    *(long *)(iVar7 + 0x90) = auVar10._0_8_;
    *(undefined8 *)(iVar7 + 0x98) = 0x4343c3c310;
    *(undefined8 *)(iVar7 + 0xa0) = 0x154;
    *(undefined8 *)(iVar7 + 0xb0) = 0;
    *(long *)(iVar7 + 0xc0) =
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f8) + 4) << 4) << 0x10;
    *(long *)(iVar7 + 0xd0) =
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f8) + 2) << 4);
    *(long *)(iVar7 + 0xe0) =
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f8) + 2) << 4) |
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f8) + 4) << 4) << 0x10;
  }
  puVar2 = *(undefined4 **)(param_1 + uVar9 * 4 + 0x18);
  *puVar2 = 0x50000000;
  puVar2[1] = *(undefined4 *)
               (*(int *)(iGpffff86b4 + 0x42f8) +
                (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f8) + 10) * 4 + 0xc);
  puVar2[2] = 0;
  puVar2[3] = 0;
  if (*(float *)(param_1 + 0xc0) < 0.2) {
    *(undefined8 *)(puVar2 + 0x2a) = 0x180806040;
  }
  else {
    lVar6 = __fixunssfdi(((0.2 - (*(float *)(param_1 + 0xc0) - 0.2)) * 128.0) / 0.2);
    *(ulong *)(puVar2 + 0x2a) = lVar6 << 0x18 | 0x100806040;
  }
  if (bVar3) {
    *(ulong *)(puVar2 + 0x2e) = (long)aiStack_180[2] << 0x20 | 0x71006f00;
    *(ulong *)(puVar2 + 0x32) = (long)iStack_168 << 0x20 | 0x71006f00;
    *(ulong *)(puVar2 + 0x36) = (long)iStack_158 << 0x20 | 0x71006f00;
    *(ulong *)(puVar2 + 0x3a) = (long)iStack_148 << 0x20 | 0x71006f00;
  }
  else {
    *(long *)(puVar2 + 0x2e) =
         (long)aiStack_180[2] << 0x20 | (long)aiStack_180[0] | (long)aiStack_180[1] << 0x10;
    *(long *)(puVar2 + 0x32) =
         (long)iStack_168 << 0x20 | (long)aiStack_180[4] | (long)aiStack_180[5] << 0x10;
    *(long *)(puVar2 + 0x36) =
         (long)iStack_158 << 0x20 | (long)iStack_160 | (long)iStack_15c << 0x10;
    *(long *)(puVar2 + 0x3a) =
         (long)iStack_148 << 0x20 | (long)iStack_150 | (long)iStack_14c << 0x10;
  }
  *(undefined4 **)(param_1 + 0x54) = puVar2 + 0x3c;
  *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfe | bVar1;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054ad90  EndSet__12Bullet3ChildFv
 * C++: Bullet3Child::EndSet()
 * size: 0x10 bytes
 * --------------------------------------------------------------------------- */
void EndSet__12Bullet3ChildFv(void)

{
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b950  @24@__dt__12Bullet3ChildFv
 * C++: @24@__dt__12Bullet3ChildFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int * _24___dt__12Bullet3ChildFv(int *param_1,short param_2)

{
  int *piVar1;
  
  piVar1 = param_1 + -6;
  if (piVar1 != (int *)0x0) {
    param_1[-1] = 0x4099d0;
    param_1[4] = 0x4099e0;
    param_1[7] = 0x4099f0;
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
 * JP: 0x0054b960  @44@__dt__12Bullet3ChildFv
 * C++: @44@__dt__12Bullet3ChildFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int _44___dt__12Bullet3ChildFv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x2c;
  if (iVar1 != 0) {
    *(undefined4 *)(param_1 + -0x18) = 0x4099d0;
    *(undefined4 *)(param_1 + -4) = 0x4099e0;
    *(undefined4 *)(param_1 + 8) = 0x4099f0;
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

