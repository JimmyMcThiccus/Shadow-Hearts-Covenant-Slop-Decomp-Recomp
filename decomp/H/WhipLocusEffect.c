/* decomp/H/WhipLocusEffect.c — cleaned Ghidra output (SH2JP_BATTLE.BIN, JP Furokuban, base 0x00430a00).
 * 9 function(s). Types: see types.h. Names/gp globals resolved from symbols/SLPM_602.19.syms. */
#include "types.h"

/* ---------------------------------------------------------------------------
 * JP: 0x00515ee0  __ct__15WhipLocusEffectFiii
 * C++: WhipLocusEffect::__ct(int, int, int)
 * size: 0xad4 bytes
 * --------------------------------------------------------------------------- */
undefined8
__ct__15WhipLocusEffectFiii
          (undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined4 param_4)

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
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  undefined4 uVar14;
  byte *pbVar15;
  int iVar16;
  undefined4 *puVar17;
  undefined1 (*pauVar18) [16];
  int iVar19;
  int iVar20;
  undefined1 in_vf0 [16];
  undefined1 auVar21 [16];
  undefined1 auVar22 [16];
  undefined1 auVar23 [16];
  undefined1 auStack_240 [16];
  undefined1 auStack_230 [16];
  undefined1 auStack_220 [16];
  undefined1 auStack_210 [16];
  undefined1 auStack_200 [16];
  undefined1 auStack_1f0 [16];
  undefined1 auStack_1e0 [16];
  undefined1 auStack_1d0 [16];
  undefined1 auStack_1c0 [16];
  undefined1 auStack_1b0 [16];
  undefined1 auStack_1a0 [16];
  undefined1 auStack_190 [16];
  undefined1 auStack_180 [16];
  undefined1 auStack_170 [16];
  undefined1 auStack_160 [8];
  undefined4 uStack_158;
  undefined4 uStack_154;
  undefined1 auStack_150 [16];
  undefined1 auStack_140 [16];
  undefined1 auStack_130 [8];
  undefined4 uStack_128;
  undefined4 uStack_124;
  undefined1 auStack_120 [16];
  undefined1 auStack_110 [16];
  undefined1 auStack_100 [8];
  undefined4 uStack_f8;
  undefined4 uStack_f4;
  undefined1 auStack_f0 [16];
  undefined1 auStack_e0 [16];
  undefined1 auStack_d0 [8];
  undefined4 uStack_c8;
  undefined4 uStack_c4;
  undefined1 auStack_c0 [16];
  undefined1 auStack_b0 [16];
  undefined1 auStack_a0 [16];
  undefined1 auStack_90 [16];
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
  
  __ct__6BtlEffFii(param_1,param_2,param_3);
  iVar19 = (int)param_1;
  *(undefined4 *)(iVar19 + 0x14) = 0x40a080;
  *(undefined4 *)(iVar19 + 0x28) = 0x40a090;
  *(undefined4 *)(iVar19 + 0x34) = 0x40a0a0;
  puVar17 = (undefined4 *)(iVar19 + 0x80);
  do {
    *puVar17 = in_zero_lo;
    puVar17[1] = in_zero_hi;
    puVar17[2] = in_zero_udw;
    puVar17[3] = in_register_0000000c;
    puVar17 = puVar17 + 4;
  } while (puVar17 != (undefined4 *)(iVar19 + 0x680));
  puVar17 = (undefined4 *)(iVar19 + 0x680);
  do {
    *puVar17 = in_zero_lo;
    puVar17[1] = in_zero_hi;
    puVar17[2] = in_zero_udw;
    puVar17[3] = in_register_0000000c;
    puVar17 = puVar17 + 4;
  } while (puVar17 != (undefined4 *)(iVar19 + 0x3680));
  *(undefined4 *)(iVar19 + 0x5c) = 0;
  *(undefined4 *)(iVar19 + 0x60) = 0;
  *(undefined4 *)(iVar19 + 100) = 0;
  *(undefined4 *)(iVar19 + 0x40) = 0;
  *(int *)(iVar19 + 0x44) = (int)param_2;
  *(int *)(iVar19 + 0x48) = (int)param_3;
  *(undefined4 *)(iVar19 + 0x4c) = 8;
  *(undefined4 *)(iVar19 + 0x6c) = 0;
  *(undefined4 *)(iVar19 + 0x68) = 0;
  *(undefined4 *)(iVar19 + 0x70) = 0;
  *(undefined4 *)(iVar19 + 0x36a4) = param_4;
  *(undefined4 *)(iVar19 + 0x1c) = 0;
  *(undefined4 *)(iVar19 + 0x18) = 0;
  *(undefined4 *)(iVar19 + 0x54) = 0;
  *(undefined4 *)(iVar19 + 0x3684) = 0;
  *(undefined4 *)(iVar19 + 0x3680) = 0;
  auVar21 = _vmr32(in_vf0);
  auVar22 = _vmr32(auVar21);
  auVar23 = _vmr32(auVar22);
  auStack_90 = _sqc2(in_vf0);
  auStack_a0 = _sqc2(auVar21);
  auStack_b0 = _sqc2(auVar22);
  auStack_c0 = _sqc2(auVar23);
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
  uStack_40 = in_zero_lo;
  uStack_3c = in_zero_hi;
  uStack_38 = in_zero_udw;
  uStack_34 = in_register_0000000c;
  uStack_30 = in_zero_lo;
  uStack_2c = in_zero_hi;
  uStack_28 = in_zero_udw;
  uStack_24 = in_register_0000000c;
  uStack_20 = in_zero_lo;
  uStack_1c = in_zero_hi;
  uStack_18 = in_zero_udw;
  uStack_14 = in_register_0000000c;
  uStack_10 = in_zero_lo;
  uStack_c = in_zero_hi;
  uStack_8 = in_zero_udw;
  uStack_4 = in_register_0000000c;
  if (*(int *)(iVar19 + 0x36a4) == 1) {
    uVar14 = searchBBoxIndex__8BtlModelFPci
                       (*(undefined4 *)(iGpffff86b4 + *(int *)(iVar19 + 0x48) * 0x4f0 + 0x144),
                        0x652cd0,0);
    *(undefined4 *)(iVar19 + 0x368c) = uVar14;
    uVar14 = searchBBoxIndex__8BtlModelFPci
                       (*(undefined4 *)(iGpffff86b4 + *(int *)(iVar19 + 0x48) * 0x4f0 + 0x144),
                        0x652cd8,0);
    *(undefined4 *)(iVar19 + 0x3690) = uVar14;
    uVar14 = searchBBoxIndex__8BtlModelFPci
                       (*(undefined4 *)(iGpffff86b4 + *(int *)(iVar19 + 0x48) * 0x4f0 + 0x144),
                        0x652ce0,0);
    *(undefined4 *)(iVar19 + 0x3694) = uVar14;
    uVar14 = searchBBoxIndex__8BtlModelFPci
                       (*(undefined4 *)(iGpffff86b4 + *(int *)(iVar19 + 0x48) * 0x4f0 + 0x144),
                        0x652ce8,0);
    *(undefined4 *)(iVar19 + 0x3698) = uVar14;
    uVar14 = searchBBoxIndex__8BtlModelFPci
                       (*(undefined4 *)(iGpffff86b4 + *(int *)(iVar19 + 0x48) * 0x4f0 + 0x144),
                        0x652cf0,0);
    *(undefined4 *)(iVar19 + 0x369c) = uVar14;
    uVar14 = searchBBoxIndex__8BtlModelFPci
                       (*(undefined4 *)(iGpffff86b4 + *(int *)(iVar19 + 0x48) * 0x4f0 + 0x144),
                        0x652cf8,0);
    *(undefined4 *)(iVar19 + 0x36a0) = uVar14;
    for (iVar20 = 0; iVar20 < 6; iVar20 = iVar20 + 1) {
      pbVar15 = (byte *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar19 + 0x48) * 0x4f0 + 0x144) +
                                 0xe4) + *(int *)(iVar19 + iVar20 * 4 + 0x368c) * 0x110);
      if (pbVar15 != (byte *)0x0) {
        pauVar18 = (undefined1 (*) [16])
                   (*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar19 + 0x48) * 0x4f0 + 0x144) + 0x30)
                    + (uint)*pbVar15 * 0x1f0 + (bGpffff8340 & 1) * 0x40);
        auStack_c0 = *pauVar18;
        auStack_b0 = pauVar18[1];
        auStack_a0 = pauVar18[2];
        auStack_90 = pauVar18[3];
        RotTransVector(&uStack_80,pbVar15 + 0x10,auStack_c0,8);
        auVar21._4_4_ = uStack_7c;
        auVar21._0_4_ = uStack_80;
        auVar21._8_4_ = uStack_78;
        auVar21._12_4_ = uStack_74;
        auVar21 = _lqc2(auVar21);
        auVar23._4_4_ = uStack_5c;
        auVar23._0_4_ = uStack_60;
        auVar23._8_4_ = uStack_58;
        auVar23._12_4_ = uStack_54;
        auVar22 = _lqc2(auVar23);
        auVar21 = _vadd(auVar21,auVar22);
        auStack_210 = _sqc2(auVar21);
        __ct__7FVectorFRC7FVector(auStack_150,auStack_210);
        auVar21 = _lqc2(auStack_150);
        auVar7._4_4_ = uStack_3c;
        auVar7._0_4_ = uStack_40;
        auVar7._8_4_ = uStack_38;
        auVar7._12_4_ = uStack_34;
        auVar22 = _lqc2(auVar7);
        auVar21 = _vadd(auVar21,auVar22);
        auStack_220 = _sqc2(auVar21);
        __ct__7FVectorFRC7FVector(auStack_140,auStack_220);
        auVar21 = _lqc2(auStack_140);
        auVar11._4_4_ = uStack_1c;
        auVar11._0_4_ = uStack_20;
        auVar11._8_4_ = uStack_18;
        auVar11._12_4_ = uStack_14;
        auVar22 = _lqc2(auVar11);
        auVar21 = _vadd(auVar21,auVar22);
        auStack_1b0 = _sqc2(auVar21);
        __ct__7FVectorFRC7FVector(auStack_130,auStack_1b0);
        iVar16 = iVar19 + *(int *)(iVar19 + 0x6c) * 0xc0 + iVar20 * 0x20;
        *(int *)(iVar16 + 0x80) = auStack_130._0_4_;
        *(int *)(iVar16 + 0x84) = auStack_130._4_4_;
        *(undefined4 *)(iVar16 + 0x88) = uStack_128;
        *(undefined4 *)(iVar16 + 0x8c) = uStack_124;
        __adv__7FVectorFf(0x40800000,iVar19 + *(int *)(iVar19 + 0x6c) * 0xc0 + iVar20 * 0x20 + 0x80);
        auVar22._4_4_ = uStack_6c;
        auVar22._0_4_ = uStack_70;
        auVar22._8_4_ = uStack_68;
        auVar22._12_4_ = uStack_64;
        auVar21 = _lqc2(auVar22);
        auVar5._4_4_ = uStack_4c;
        auVar5._0_4_ = uStack_50;
        auVar5._8_4_ = uStack_48;
        auVar5._12_4_ = uStack_44;
        auVar22 = _lqc2(auVar5);
        auVar21 = _vadd(auVar21,auVar22);
        auStack_230 = _sqc2(auVar21);
        __ct__7FVectorFRC7FVector(auStack_180,auStack_230);
        auVar21 = _lqc2(auStack_180);
        auVar9._4_4_ = uStack_2c;
        auVar9._0_4_ = uStack_30;
        auVar9._8_4_ = uStack_28;
        auVar9._12_4_ = uStack_24;
        auVar22 = _lqc2(auVar9);
        auVar21 = _vadd(auVar21,auVar22);
        auStack_240 = _sqc2(auVar21);
        __ct__7FVectorFRC7FVector(auStack_170,auStack_240);
        auVar21 = _lqc2(auStack_170);
        auVar13._4_4_ = uStack_c;
        auVar13._0_4_ = uStack_10;
        auVar13._8_4_ = uStack_8;
        auVar13._12_4_ = uStack_4;
        auVar22 = _lqc2(auVar13);
        auVar21 = _vadd(auVar21,auVar22);
        auStack_1c0 = _sqc2(auVar21);
        __ct__7FVectorFRC7FVector(auStack_160,auStack_1c0);
        iVar16 = iVar19 + *(int *)(iVar19 + 0x6c) * 0xc0 + (iVar20 * 2 + 1) * 0x10;
        *(int *)(iVar16 + 0x80) = auStack_160._0_4_;
        *(int *)(iVar16 + 0x84) = auStack_160._4_4_;
        *(undefined4 *)(iVar16 + 0x88) = uStack_158;
        *(undefined4 *)(iVar16 + 0x8c) = uStack_154;
        __adv__7FVectorFf(0x40800000,
                        iVar19 + *(int *)(iVar19 + 0x6c) * 0xc0 + (iVar20 * 2 + 1) * 0x10 + 0x80);
      }
    }
    *(int *)(iVar19 + 0x6c) = *(int *)(iVar19 + 0x6c) + 1;
    *(int *)(iVar19 + 0x68) = *(int *)(iVar19 + 0x68) + 1;
  }
  else if (*(int *)(iVar19 + 0x36a4) == 0) {
    uVar14 = searchRWBBoxIndex__8BtlModelFPci
                       (*(undefined4 *)(iGpffff86b4 + *(int *)(iVar19 + 0x48) * 0x4f0 + 0x144),
                        0x652ca0,0);
    *(undefined4 *)(iVar19 + 0x368c) = uVar14;
    uVar14 = searchRWBBoxIndex__8BtlModelFPci
                       (*(undefined4 *)(iGpffff86b4 + *(int *)(iVar19 + 0x48) * 0x4f0 + 0x144),
                        0x652ca8,0);
    *(undefined4 *)(iVar19 + 0x3690) = uVar14;
    uVar14 = searchRWBBoxIndex__8BtlModelFPci
                       (*(undefined4 *)(iGpffff86b4 + *(int *)(iVar19 + 0x48) * 0x4f0 + 0x144),
                        0x652cb0,0);
    *(undefined4 *)(iVar19 + 0x3694) = uVar14;
    uVar14 = searchRWBBoxIndex__8BtlModelFPci
                       (*(undefined4 *)(iGpffff86b4 + *(int *)(iVar19 + 0x48) * 0x4f0 + 0x144),
                        0x652cb8,0);
    *(undefined4 *)(iVar19 + 0x3698) = uVar14;
    uVar14 = searchRWBBoxIndex__8BtlModelFPci
                       (*(undefined4 *)(iGpffff86b4 + *(int *)(iVar19 + 0x48) * 0x4f0 + 0x144),
                        0x652cc0,0);
    *(undefined4 *)(iVar19 + 0x369c) = uVar14;
    uVar14 = searchRWBBoxIndex__8BtlModelFPci
                       (*(undefined4 *)(iGpffff86b4 + *(int *)(iVar19 + 0x48) * 0x4f0 + 0x144),
                        0x652cc8,0);
    *(undefined4 *)(iVar19 + 0x36a0) = uVar14;
    for (iVar20 = 0; iVar20 < 6; iVar20 = iVar20 + 1) {
      pbVar15 = (byte *)(*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar19 + 0x48) * 0x4f0 +
                                                   0x144) + 0x52c) + 0xe4) +
                        *(int *)(iVar19 + iVar20 * 4 + 0x368c) * 0x110);
      if (pbVar15 != (byte *)0x0) {
        pauVar18 = (undefined1 (*) [16])
                   (*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar19 + 0x48) * 0x4f0 + 0x144
                                              ) + 0x52c) + 0x30) + (uint)*pbVar15 * 0x1f0 +
                   (bGpffff8340 & 1) * 0x40);
        auStack_c0 = *pauVar18;
        auStack_b0 = pauVar18[1];
        auStack_a0 = pauVar18[2];
        auStack_90 = pauVar18[3];
        RotTransVector(&uStack_80,pbVar15 + 0x10,auStack_c0,8);
        auVar3._4_4_ = uStack_5c;
        auVar3._0_4_ = uStack_60;
        auVar3._8_4_ = uStack_58;
        auVar3._12_4_ = uStack_54;
        auVar21 = _lqc2(auVar3);
        auVar4._4_4_ = uStack_4c;
        auVar4._0_4_ = uStack_50;
        auVar4._8_4_ = uStack_48;
        auVar4._12_4_ = uStack_44;
        auVar22 = _lqc2(auVar4);
        auVar21 = _vadd(auVar21,auVar22);
        auStack_1d0 = _sqc2(auVar21);
        __ct__7FVectorFRC7FVector(auStack_f0,auStack_1d0);
        auVar21 = _lqc2(auStack_f0);
        auVar6._4_4_ = uStack_3c;
        auVar6._0_4_ = uStack_40;
        auVar6._8_4_ = uStack_38;
        auVar6._12_4_ = uStack_34;
        auVar22 = _lqc2(auVar6);
        auVar21 = _vadd(auVar21,auVar22);
        auStack_1e0 = _sqc2(auVar21);
        __ct__7FVectorFRC7FVector(auStack_e0,auStack_1e0);
        auVar21 = _lqc2(auStack_e0);
        auVar8._4_4_ = uStack_2c;
        auVar8._0_4_ = uStack_30;
        auVar8._8_4_ = uStack_28;
        auVar8._12_4_ = uStack_24;
        auVar22 = _lqc2(auVar8);
        auVar21 = _vadd(auVar21,auVar22);
        auStack_190 = _sqc2(auVar21);
        __ct__7FVectorFRC7FVector(auStack_d0,auStack_190);
        iVar16 = iVar19 + *(int *)(iVar19 + 0x6c) * 0xc0 + iVar20 * 0x20;
        *(int *)(iVar16 + 0x80) = auStack_d0._0_4_;
        *(int *)(iVar16 + 0x84) = auStack_d0._4_4_;
        *(undefined4 *)(iVar16 + 0x88) = uStack_c8;
        *(undefined4 *)(iVar16 + 0x8c) = uStack_c4;
        __adv__7FVectorFf(0x40800000,iVar19 + *(int *)(iVar19 + 0x6c) * 0xc0 + iVar20 * 0x20 + 0x80);
        auVar1._4_4_ = uStack_7c;
        auVar1._0_4_ = uStack_80;
        auVar1._8_4_ = uStack_78;
        auVar1._12_4_ = uStack_74;
        auVar21 = _lqc2(auVar1);
        auVar2._4_4_ = uStack_6c;
        auVar2._0_4_ = uStack_70;
        auVar2._8_4_ = uStack_68;
        auVar2._12_4_ = uStack_64;
        auVar22 = _lqc2(auVar2);
        auVar21 = _vadd(auVar21,auVar22);
        auStack_1f0 = _sqc2(auVar21);
        __ct__7FVectorFRC7FVector(auStack_120,auStack_1f0);
        auVar21 = _lqc2(auStack_120);
        auVar10._4_4_ = uStack_1c;
        auVar10._0_4_ = uStack_20;
        auVar10._8_4_ = uStack_18;
        auVar10._12_4_ = uStack_14;
        auVar22 = _lqc2(auVar10);
        auVar21 = _vadd(auVar21,auVar22);
        auStack_200 = _sqc2(auVar21);
        __ct__7FVectorFRC7FVector(auStack_110,auStack_200);
        auVar21 = _lqc2(auStack_110);
        auVar12._4_4_ = uStack_c;
        auVar12._0_4_ = uStack_10;
        auVar12._8_4_ = uStack_8;
        auVar12._12_4_ = uStack_4;
        auVar22 = _lqc2(auVar12);
        auVar21 = _vadd(auVar21,auVar22);
        auStack_1a0 = _sqc2(auVar21);
        __ct__7FVectorFRC7FVector(auStack_100,auStack_1a0);
        iVar16 = iVar19 + *(int *)(iVar19 + 0x6c) * 0xc0 + (iVar20 * 2 + 1) * 0x10;
        *(int *)(iVar16 + 0x80) = auStack_100._0_4_;
        *(int *)(iVar16 + 0x84) = auStack_100._4_4_;
        *(undefined4 *)(iVar16 + 0x88) = uStack_f8;
        *(undefined4 *)(iVar16 + 0x8c) = uStack_f4;
        __adv__7FVectorFf(0x40800000,
                        iVar19 + *(int *)(iVar19 + 0x6c) * 0xc0 + (iVar20 * 2 + 1) * 0x10 + 0x80);
      }
    }
    *(int *)(iVar19 + 0x6c) = *(int *)(iVar19 + 0x6c) + 1;
    *(int *)(iVar19 + 0x68) = *(int *)(iVar19 + 0x68) + 1;
  }
  Entry__7CPollerFP7CPolObjib(iGpffff858c + 0x48,param_1,0x80,0);
  BtlEffEntry__7CBattleFiP6BtlEff(iGpffff86b4,*(undefined4 *)(iVar19 + 0x48),param_1);
  return param_1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005169c0  __dt__15WhipLocusEffectFv
 * C++: WhipLocusEffect::__dt()
 * size: 0x154 bytes
 * --------------------------------------------------------------------------- */
int __dt__15WhipLocusEffectFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x14) = 0x40a080;
    *(undefined4 *)(param_1 + 0x28) = 0x40a090;
    *(undefined4 *)(param_1 + 0x34) = 0x40a0a0;
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
 * JP: 0x00516b20  Destruct__15WhipLocusEffectFv
 * C++: WhipLocusEffect::Destruct()
 * size: 0xc8 bytes
 * --------------------------------------------------------------------------- */
void Destruct__15WhipLocusEffectFv(int param_1)

{
  int iVar1;
  
  BtlEffRelease__7CBattleFiP6BtlEff(uGpffff86b4,*(undefined4 *)(param_1 + 0x48),param_1);
  if ((long)((ulong)*(byte *)(param_1 + 0x40) << 0x3e) < 0) {
    iVar1 = param_1;
    if (param_1 != 0) {
      iVar1 = param_1 + 0x18;
    }
    ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,iVar1);
  }
  *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfd;
  Dispose__7CPollerFP7CPolObj(iGpffff858c + 0x48,param_1);
  (**(code **)(*(int *)(param_1 + 0x34) + 0xc))();
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00516bf0  Polling__15WhipLocusEffectFv
 * C++: WhipLocusEffect::Polling()
 * size: 0xc84 bytes
 * --------------------------------------------------------------------------- */
undefined4 Polling__15WhipLocusEffectFv(int param_1)

{
  undefined8 uVar1;
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
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  byte *pbVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  undefined4 uVar20;
  undefined4 uVar21;
  undefined8 *puVar22;
  undefined1 (*pauVar23) [16];
  int iVar24;
  float fVar25;
  undefined1 in_vf0 [16];
  undefined1 auVar26 [16];
  undefined1 auVar27 [16];
  undefined1 auVar28 [16];
  undefined1 auStack_8d0 [16];
  undefined1 auStack_8c0 [16];
  undefined1 auStack_8b0 [16];
  undefined1 auStack_8a0 [16];
  undefined1 auStack_890 [16];
  undefined1 auStack_880 [16];
  undefined1 auStack_870 [16];
  undefined1 auStack_860 [16];
  undefined1 auStack_850 [16];
  undefined1 auStack_840 [16];
  undefined1 auStack_830 [16];
  undefined1 auStack_820 [16];
  undefined1 auStack_810 [16];
  undefined1 auStack_800 [16];
  undefined1 auStack_7f0 [16];
  undefined1 auStack_7e0 [8];
  undefined4 uStack_7d8;
  undefined4 uStack_7d4;
  undefined1 auStack_7d0 [16];
  undefined1 auStack_7c0 [8];
  undefined4 uStack_7b8;
  undefined4 uStack_7b4;
  undefined1 auStack_7b0 [8];
  undefined4 uStack_7a8;
  undefined4 uStack_7a4;
  undefined1 auStack_7a0 [16];
  undefined1 auStack_790 [16];
  undefined1 auStack_780 [8];
  undefined4 uStack_778;
  undefined4 uStack_774;
  undefined1 auStack_770 [16];
  undefined1 auStack_760 [16];
  undefined1 auStack_750 [8];
  undefined4 uStack_748;
  undefined4 uStack_744;
  undefined1 auStack_740 [16];
  undefined1 auStack_730 [16];
  undefined1 auStack_720 [8];
  undefined4 uStack_718;
  undefined4 uStack_714;
  undefined1 auStack_710 [16];
  undefined1 auStack_700 [16];
  undefined1 auStack_6f0 [8];
  undefined4 uStack_6e8;
  undefined4 uStack_6e4;
  undefined8 uStack_6e0;
  undefined4 auStack_6d8 [2];
  undefined8 uStack_6d0;
  undefined4 auStack_6c8 [378];
  undefined1 auStack_e0 [16];
  undefined1 auStack_d0 [16];
  undefined1 auStack_c0 [16];
  undefined1 auStack_b0 [16];
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
  undefined1 auStack_8 [8];
  
  auVar26 = _vmr32(in_vf0);
  auVar27 = _vmr32(auVar26);
  auVar28 = _vmr32(auVar27);
  auStack_b0 = _sqc2(in_vf0);
  auStack_c0 = _sqc2(auVar26);
  auStack_d0 = _sqc2(auVar27);
  auStack_e0 = _sqc2(auVar28);
  fVar25 = *(float *)(iGpffff86b4 + 0x38);
  if ((*(byte *)(iGpffff86b4 + 0x24) & 1) != 0) {
    fVar25 = 0.0;
  }
  uStack_20 = in_zero_lo;
  uStack_1c = in_zero_hi;
  uStack_18 = in_zero_udw;
  uStack_14 = in_register_0000000c;
  if (fVar25 != 0.0) {
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
    uStack_40 = in_zero_lo;
    uStack_3c = in_zero_hi;
    uStack_38 = in_zero_udw;
    uStack_34 = in_register_0000000c;
    uStack_30 = in_zero_lo;
    uStack_2c = in_zero_hi;
    uStack_28 = in_zero_udw;
    uStack_24 = in_register_0000000c;
    if (*(int *)(param_1 + 0x36a4) == 1) {
      for (iVar24 = 0; iVar24 < 6; iVar24 = iVar24 + 1) {
        pbVar16 = (byte *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x144)
                                   + 0xe4) + *(int *)(param_1 + iVar24 * 4 + 0x368c) * 0x110);
        if (pbVar16 != (byte *)0x0) {
          pauVar23 = (undefined1 (*) [16])
                     (*(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x144) +
                              0x30) + (uint)*pbVar16 * 0x1f0 + (bGpffff8340 & 1) * 0x40);
          auStack_e0 = *pauVar23;
          auStack_d0 = pauVar23[1];
          auStack_c0 = pauVar23[2];
          auStack_b0 = pauVar23[3];
          RotTransVector(&uStack_a0,pbVar16 + 0x10,auStack_e0,8);
          auVar26._4_4_ = uStack_9c;
          auVar26._0_4_ = uStack_a0;
          auVar26._8_4_ = uStack_98;
          auVar26._12_4_ = uStack_94;
          auVar26 = _lqc2(auVar26);
          auVar28._4_4_ = uStack_7c;
          auVar28._0_4_ = uStack_80;
          auVar28._8_4_ = uStack_78;
          auVar28._12_4_ = uStack_74;
          auVar27 = _lqc2(auVar28);
          auVar26 = _vadd(auVar26,auVar27);
          auStack_890 = _sqc2(auVar26);
          __ct__7FVectorFRC7FVector(auStack_770,auStack_890);
          auVar26 = _lqc2(auStack_770);
          auVar8._4_4_ = uStack_5c;
          auVar8._0_4_ = uStack_60;
          auVar8._8_4_ = uStack_58;
          auVar8._12_4_ = uStack_54;
          auVar27 = _lqc2(auVar8);
          auVar26 = _vadd(auVar26,auVar27);
          auStack_8a0 = _sqc2(auVar26);
          __ct__7FVectorFRC7FVector(auStack_760,auStack_8a0);
          auVar26 = _lqc2(auStack_760);
          auVar12._4_4_ = uStack_3c;
          auVar12._0_4_ = uStack_40;
          auVar12._8_4_ = uStack_38;
          auVar12._12_4_ = uStack_34;
          auVar27 = _lqc2(auVar12);
          auVar26 = _vadd(auVar26,auVar27);
          auStack_810 = _sqc2(auVar26);
          __ct__7FVectorFRC7FVector(auStack_750,auStack_810);
          iVar17 = param_1 + *(int *)(param_1 + 0x6c) * 0xc0 + iVar24 * 0x20;
          *(int *)(iVar17 + 0x80) = auStack_750._0_4_;
          *(int *)(iVar17 + 0x84) = auStack_750._4_4_;
          *(undefined4 *)(iVar17 + 0x88) = uStack_748;
          *(undefined4 *)(iVar17 + 0x8c) = uStack_744;
          __adv__7FVectorFf(0x40800000,
                          param_1 + *(int *)(param_1 + 0x6c) * 0xc0 + iVar24 * 0x20 + 0x80);
          auVar27._4_4_ = uStack_8c;
          auVar27._0_4_ = uStack_90;
          auVar27._8_4_ = uStack_88;
          auVar27._12_4_ = uStack_84;
          auVar26 = _lqc2(auVar27);
          auVar6._4_4_ = uStack_6c;
          auVar6._0_4_ = uStack_70;
          auVar6._8_4_ = uStack_68;
          auVar6._12_4_ = uStack_64;
          auVar27 = _lqc2(auVar6);
          auVar26 = _vadd(auVar26,auVar27);
          auStack_8b0 = _sqc2(auVar26);
          __ct__7FVectorFRC7FVector(auStack_7a0,auStack_8b0);
          auVar26 = _lqc2(auStack_7a0);
          auVar10._4_4_ = uStack_4c;
          auVar10._0_4_ = uStack_50;
          auVar10._8_4_ = uStack_48;
          auVar10._12_4_ = uStack_44;
          auVar27 = _lqc2(auVar10);
          auVar26 = _vadd(auVar26,auVar27);
          auStack_8c0 = _sqc2(auVar26);
          __ct__7FVectorFRC7FVector(auStack_790,auStack_8c0);
          auVar26 = _lqc2(auStack_790);
          auVar14._4_4_ = uStack_2c;
          auVar14._0_4_ = uStack_30;
          auVar14._8_4_ = uStack_28;
          auVar14._12_4_ = uStack_24;
          auVar27 = _lqc2(auVar14);
          auVar26 = _vadd(auVar26,auVar27);
          auStack_820 = _sqc2(auVar26);
          __ct__7FVectorFRC7FVector(auStack_780,auStack_820);
          iVar17 = param_1 + *(int *)(param_1 + 0x6c) * 0xc0 + (iVar24 * 2 + 1) * 0x10;
          *(int *)(iVar17 + 0x80) = auStack_780._0_4_;
          *(int *)(iVar17 + 0x84) = auStack_780._4_4_;
          *(undefined4 *)(iVar17 + 0x88) = uStack_778;
          *(undefined4 *)(iVar17 + 0x8c) = uStack_774;
          __adv__7FVectorFf(0x40800000,
                          param_1 + *(int *)(param_1 + 0x6c) * 0xc0 + (iVar24 * 2 + 1) * 0x10 + 0x80
                         );
        }
      }
    }
    else if (*(int *)(param_1 + 0x36a4) == 0) {
      for (iVar24 = 0; iVar24 < 6; iVar24 = iVar24 + 1) {
        pbVar16 = (byte *)(*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0
                                                     + 0x144) + 0x52c) + 0xe4) +
                          *(int *)(param_1 + iVar24 * 4 + 0x368c) * 0x110);
        if (pbVar16 != (byte *)0x0) {
          pauVar23 = (undefined1 (*) [16])
                     (*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 +
                                                0x144) + 0x52c) + 0x30) + (uint)*pbVar16 * 0x1f0 +
                     (bGpffff8340 & 1) * 0x40);
          auStack_e0 = *pauVar23;
          auStack_d0 = pauVar23[1];
          auStack_c0 = pauVar23[2];
          auStack_b0 = pauVar23[3];
          RotTransVector(&uStack_a0,pbVar16 + 0x10,auStack_e0,8);
          auVar4._4_4_ = uStack_7c;
          auVar4._0_4_ = uStack_80;
          auVar4._8_4_ = uStack_78;
          auVar4._12_4_ = uStack_74;
          auVar26 = _lqc2(auVar4);
          auVar5._4_4_ = uStack_6c;
          auVar5._0_4_ = uStack_70;
          auVar5._8_4_ = uStack_68;
          auVar5._12_4_ = uStack_64;
          auVar27 = _lqc2(auVar5);
          auVar26 = _vadd(auVar26,auVar27);
          auStack_850 = _sqc2(auVar26);
          __ct__7FVectorFRC7FVector(auStack_710,auStack_850);
          auVar26 = _lqc2(auStack_710);
          auVar7._4_4_ = uStack_5c;
          auVar7._0_4_ = uStack_60;
          auVar7._8_4_ = uStack_58;
          auVar7._12_4_ = uStack_54;
          auVar27 = _lqc2(auVar7);
          auVar26 = _vadd(auVar26,auVar27);
          auStack_860 = _sqc2(auVar26);
          __ct__7FVectorFRC7FVector(auStack_700,auStack_860);
          auVar26 = _lqc2(auStack_700);
          auVar9._4_4_ = uStack_4c;
          auVar9._0_4_ = uStack_50;
          auVar9._8_4_ = uStack_48;
          auVar9._12_4_ = uStack_44;
          auVar27 = _lqc2(auVar9);
          auVar26 = _vadd(auVar26,auVar27);
          auStack_7f0 = _sqc2(auVar26);
          __ct__7FVectorFRC7FVector(auStack_6f0,auStack_7f0);
          iVar17 = param_1 + *(int *)(param_1 + 0x6c) * 0xc0 + iVar24 * 0x20;
          *(int *)(iVar17 + 0x80) = auStack_6f0._0_4_;
          *(int *)(iVar17 + 0x84) = auStack_6f0._4_4_;
          *(undefined4 *)(iVar17 + 0x88) = uStack_6e8;
          *(undefined4 *)(iVar17 + 0x8c) = uStack_6e4;
          __adv__7FVectorFf(0x40800000,
                          param_1 + *(int *)(param_1 + 0x6c) * 0xc0 + iVar24 * 0x20 + 0x80);
          auVar2._4_4_ = uStack_9c;
          auVar2._0_4_ = uStack_a0;
          auVar2._8_4_ = uStack_98;
          auVar2._12_4_ = uStack_94;
          auVar26 = _lqc2(auVar2);
          auVar3._4_4_ = uStack_8c;
          auVar3._0_4_ = uStack_90;
          auVar3._8_4_ = uStack_88;
          auVar3._12_4_ = uStack_84;
          auVar27 = _lqc2(auVar3);
          auVar26 = _vadd(auVar26,auVar27);
          auStack_870 = _sqc2(auVar26);
          __ct__7FVectorFRC7FVector(auStack_740,auStack_870);
          auVar26 = _lqc2(auStack_740);
          auVar11._4_4_ = uStack_3c;
          auVar11._0_4_ = uStack_40;
          auVar11._8_4_ = uStack_38;
          auVar11._12_4_ = uStack_34;
          auVar27 = _lqc2(auVar11);
          auVar26 = _vadd(auVar26,auVar27);
          auStack_880 = _sqc2(auVar26);
          __ct__7FVectorFRC7FVector(auStack_730,auStack_880);
          auVar26 = _lqc2(auStack_730);
          auVar13._4_4_ = uStack_2c;
          auVar13._0_4_ = uStack_30;
          auVar13._8_4_ = uStack_28;
          auVar13._12_4_ = uStack_24;
          auVar27 = _lqc2(auVar13);
          auVar26 = _vadd(auVar26,auVar27);
          auStack_800 = _sqc2(auVar26);
          __ct__7FVectorFRC7FVector(auStack_720,auStack_800);
          iVar17 = param_1 + *(int *)(param_1 + 0x6c) * 0xc0 + (iVar24 * 2 + 1) * 0x10;
          *(int *)(iVar17 + 0x80) = auStack_720._0_4_;
          *(int *)(iVar17 + 0x84) = auStack_720._4_4_;
          *(undefined4 *)(iVar17 + 0x88) = uStack_718;
          *(undefined4 *)(iVar17 + 0x8c) = uStack_714;
          __adv__7FVectorFf(0x40800000,
                          param_1 + *(int *)(param_1 + 0x6c) * 0xc0 + (iVar24 * 2 + 1) * 0x10 + 0x80
                         );
        }
      }
    }
    *(int *)(param_1 + 0x6c) = *(int *)(param_1 + 0x6c) + 1;
    if (7 < *(int *)(param_1 + 0x6c)) {
      *(undefined4 *)(param_1 + 0x6c) = 0;
    }
    *(int *)(param_1 + 0x68) = *(int *)(param_1 + 0x68) + 1;
    if (8 < *(int *)(param_1 + 0x68)) {
      *(undefined4 *)(param_1 + 0x68) = 8;
    }
  }
  puVar22 = &uStack_6e0;
  do {
    *(undefined4 *)puVar22 = in_zero_lo;
    *(undefined4 *)((int)puVar22 + 4) = in_zero_hi;
    *(undefined4 *)(puVar22 + 1) = in_zero_udw;
    *(undefined4 *)((int)puVar22 + 0xc) = in_register_0000000c;
    puVar22 = puVar22 + 2;
  } while (puVar22 != (undefined8 *)auStack_e0);
  iVar24 = *(int *)(param_1 + 0x6c);
  for (iVar17 = 0; iVar17 < *(int *)(param_1 + 0x68); iVar17 = iVar17 + 1) {
    iVar24 = iVar24 + -1;
    if (iVar24 < 0) {
      iVar24 = 7;
    }
    for (iVar18 = 0; iVar18 < 0xc; iVar18 = iVar18 + 1) {
      iVar19 = param_1 + iVar24 * 0xc0 + iVar18 * 0x10;
      uVar1 = *(undefined8 *)(iVar19 + 0x80);
      uVar20 = *(undefined4 *)(iVar19 + 0x88);
      uVar21 = *(undefined4 *)(iVar19 + 0x8c);
      *(int *)(&uStack_6e0 + iVar18 * 0x10 + iVar17 * 2) = (int)uVar1;
      *(int *)((int)&uStack_6e0 + iVar17 * 0x10 + iVar18 * 0x80 + 4) = (int)((ulong)uVar1 >> 0x20);
      auStack_6d8[iVar18 * 0x20 + iVar17 * 4] = uVar20;
      auStack_6d8[iVar18 * 0x20 + iVar17 * 4 + 1] = uVar21;
    }
  }
  if (*(int *)(param_1 + 0x5c) == 0) {
    iVar24 = (*(int *)(param_1 + 0x68) + -1) * 8 + 1;
    *(int *)(param_1 + 0x70) = iVar24;
  }
  else {
    *(float *)(param_1 + 0x3688) = *(float *)(param_1 + 0x3688) + fVar25;
    while ((1 < *(int *)(param_1 + 100) && (0.004166667 < *(float *)(param_1 + 0x3688)))) {
      *(float *)(param_1 + 0x3688) = *(float *)(param_1 + 0x3688) - 0.004166667;
      *(int *)(param_1 + 100) = *(int *)(param_1 + 100) + -1;
    }
    if (*(int *)(param_1 + 100) < 2) {
      BtlEffRelease__7CBattleFiP6BtlEff(iGpffff86b4,*(undefined4 *)(param_1 + 0x48),param_1);
      if ((long)((ulong)*(byte *)(param_1 + 0x40) << 0x3e) < 0) {
        iVar24 = param_1;
        if (param_1 != 0) {
          iVar24 = param_1 + 0x18;
        }
        ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,iVar24);
      }
      *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfd;
      (**(code **)(*(int *)(param_1 + 0x34) + 0xc))();
      return 1;
    }
    iVar24 = (*(int *)(param_1 + 0x68) + -1) * 8 + 1;
    *(undefined4 *)(param_1 + 0x70) = *(undefined4 *)(param_1 + 100);
  }
  if (*(int *)(param_1 + 0x68) == 1) {
    for (iVar24 = 0; iVar24 < 0xc; iVar24 = iVar24 + 1) {
      iVar17 = param_1 + iVar24 * 0x10;
      uVar1 = (&uStack_6e0)[iVar24 * 0x10];
      uVar20 = auStack_6d8[iVar24 * 0x20];
      uVar21 = auStack_6d8[iVar24 * 0x20 + 1];
      *(int *)(iVar17 + 0x680) = (int)uVar1;
      *(int *)(iVar17 + 0x684) = (int)((ulong)uVar1 >> 0x20);
      *(undefined4 *)(iVar17 + 0x688) = uVar20;
      *(undefined4 *)(iVar17 + 0x68c) = uVar21;
    }
  }
  else if (*(int *)(param_1 + 0x68) == 2) {
    for (iVar24 = 0; iVar24 < 0xc; iVar24 = iVar24 + 1) {
      iVar17 = param_1 + iVar24 * 0x10;
      uVar1 = (&uStack_6e0)[iVar24 * 0x10];
      uVar20 = auStack_6d8[iVar24 * 0x20];
      uVar21 = auStack_6d8[iVar24 * 0x20 + 1];
      *(int *)(iVar17 + 0x680) = (int)uVar1;
      *(int *)(iVar17 + 0x684) = (int)((ulong)uVar1 >> 0x20);
      *(undefined4 *)(iVar17 + 0x688) = uVar20;
      *(undefined4 *)(iVar17 + 0x68c) = uVar21;
      auVar26 = _lqc2(*(undefined1 (*) [16])(&uStack_6e0 + iVar24 * 2));
      auVar27 = _lqc2(*(undefined1 (*) [16])(&uStack_6d0 + iVar24 * 0x10));
      auVar26 = _vsub(auVar26,auVar27);
      auStack_830 = _sqc2(auVar26);
      __ct__7FVectorFRC7FVector(auStack_7b0,auStack_830);
      uStack_20 = auStack_7b0._0_4_;
      uStack_1c = auStack_7b0._4_4_;
      uStack_18 = uStack_7a8;
      uStack_14 = uStack_7a4;
      for (iVar17 = 1; iVar17 < 8; iVar17 = iVar17 + 1) {
        iVar18 = iVar17;
        if (iVar17 < 0) {
          iVar18 = iVar17 + 7;
        }
        auVar15._4_4_ = uStack_1c;
        auVar15._0_4_ = uStack_20;
        auVar15._8_4_ = uStack_18;
        auVar15._12_4_ = uStack_14;
        auVar26 = _lqc2(auVar15);
        auVar27 = _qmtc2((float)(iVar18 >> 3));
        auVar26 = _vmulbc(auVar26,auVar27);
        auStack_8d0 = _sqc2(auVar26);
        __ct__7FVectorFRC7FVector(auStack_7d0,auStack_8d0);
        auVar26 = _lqc2(*(undefined1 (*) [16])(&uStack_6d0 + iVar24 * 0x10));
        auVar27 = _lqc2(auStack_7d0);
        auVar26 = _vadd(auVar26,auVar27);
        auStack_840 = _sqc2(auVar26);
        __ct__7FVectorFRC7FVector(auStack_7c0,auStack_840);
        iVar18 = param_1 + iVar17 * 0xc0 + iVar24 * 0x10;
        *(int *)(iVar18 + 0x680) = auStack_7c0._0_4_;
        *(int *)(iVar18 + 0x684) = auStack_7c0._4_4_;
        *(undefined4 *)(iVar18 + 0x688) = uStack_7b8;
        *(undefined4 *)(iVar18 + 0x68c) = uStack_7b4;
      }
      iVar17 = param_1 + iVar24 * 0x10;
      uVar1 = (&uStack_6d0)[iVar24 * 0x10];
      uVar20 = auStack_6c8[iVar24 * 0x20];
      uVar21 = auStack_6c8[iVar24 * 0x20 + 1];
      *(int *)(iVar17 + 0xc80) = (int)uVar1;
      *(int *)(iVar17 + 0xc84) = (int)((ulong)uVar1 >> 0x20);
      *(undefined4 *)(iVar17 + 0xc88) = uVar20;
      *(undefined4 *)(iVar17 + 0xc8c) = uVar21;
    }
  }
  else {
    __ct__9GsxSplineFv(auStack_8);
    for (iVar17 = 0; iVar17 < 0xc; iVar17 = iVar17 + 1) {
      Create__9GsxSplineFUiUiP7FVector(auStack_8,*(undefined4 *)(param_1 + 0x68),0,&uStack_6e0 + iVar17 * 0x10);
      fVar25 = 0.0;
      for (iVar18 = 0; iVar18 < *(int *)(param_1 + 0x70); iVar18 = iVar18 + 1) {
        GetPosition__9GsxSplineFf(fVar25,auStack_7e0,auStack_8);
        iVar19 = param_1 + iVar18 * 0xc0 + iVar17 * 0x10;
        *(int *)(iVar19 + 0x680) = auStack_7e0._0_4_;
        *(int *)(iVar19 + 0x684) = auStack_7e0._4_4_;
        *(undefined4 *)(iVar19 + 0x688) = uStack_7d8;
        *(undefined4 *)(iVar19 + 0x68c) = uStack_7d4;
        fVar25 = fVar25 + 1.0 / (float)(iVar24 + -1);
        if (1.0 < fVar25) {
          fVar25 = 1.0;
        }
      }
      Release__9GsxSplineFv(auStack_8);
    }
    __dt__9GsxSplineFv(auStack_8,0xffffffffffffffff);
  }
  return 0;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00517880  MakePacket__15WhipLocusEffectFv
 * C++: WhipLocusEffect::MakePacket()
 * size: 0xe80 bytes
 * --------------------------------------------------------------------------- */
/* WARNING: Removing unreachable block (ram,0x00517a08) */

void MakePacket__15WhipLocusEffectFv(int param_1)

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
  undefined8 in_a1_udw;
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  undefined8 uVar8;
  int iVar9;
  undefined8 *puVar10;
  uint uVar11;
  int iVar12;
  float fVar13;
  float fVar14;
  undefined1 auVar15 [16];
  undefined1 auStack_78f0 [16];
  undefined1 auStack_78e0 [8];
  undefined4 uStack_78d8;
  undefined4 uStack_78d4;
  float afStack_78d0 [12];
  int aiStack_78a0 [3072];
  undefined4 auStack_48a0 [3072];
  undefined4 auStack_18a0 [16];
  undefined4 auStack_1860 [16];
  undefined4 uStack_1820;
  undefined4 uStack_181c;
  undefined4 uStack_1818;
  undefined4 uStack_1814;
  float afStack_1810 [768];
  float afStack_c10 [772];
  
  uStack_1820 = in_zero_lo;
  uStack_181c = in_zero_hi;
  uStack_1818 = in_zero_udw;
  uStack_1814 = in_register_0000000c;
  for (iVar9 = 0; iVar9 < 0xc; iVar9 = iVar9 + 1) {
    fVar13 = 0.0;
    for (iVar12 = 0; iVar12 < *(int *)(param_1 + 0x70) + -1; iVar12 = iVar12 + 1) {
      auVar7 = _lqc2(*(undefined1 (*) [16])(param_1 + (iVar12 + 1) * 0xc0 + iVar9 * 0x10 + 0x680));
      auVar15 = _lqc2(*(undefined1 (*) [16])(param_1 + iVar12 * 0xc0 + iVar9 * 0x10 + 0x680));
      auVar7 = _vsub(auVar7,auVar15);
      auStack_78f0 = _sqc2(auVar7);
      __ct__7FVectorFRC7FVector(auStack_78e0,auStack_78f0);
      uStack_1820 = auStack_78e0._0_4_;
      uStack_181c = auStack_78e0._4_4_;
      uStack_1818 = uStack_78d8;
      uStack_1814 = uStack_78d4;
      fVar14 = (float)Length__7FVectorCFv(&uStack_1820);
      afStack_c10[iVar12 * 0xc + iVar9] = fVar14;
      fVar13 = fVar13 + afStack_c10[iVar12 * 0xc + iVar9];
    }
    afStack_1810[iVar9] = 0.0;
    fVar14 = 0.0;
    for (iVar12 = 0; iVar12 < *(int *)(param_1 + 0x70) + -1; iVar12 = iVar12 + 1) {
      fVar14 = fVar14 + afStack_c10[iVar12 * 0xc + iVar9];
      afStack_1810[(iVar12 + 1) * 0xc + iVar9] =
           ((float)*(ushort *)(*(int *)(iGpffff86b4 + 0x4254) + 2) * (fVar14 / fVar13)) /
           (float)(1 << (uint)(((ulong)*(byte *)(*(int *)(iGpffff86b4 + 0x4254) + 0x53) << 0x3a) >>
                              0x3c));
    }
  }
  GetViewScreenMatrix__9GsxCameraFv(auStack_1860,uGpffff8598);
  for (iVar9 = 0; iVar9 < 4; iVar9 = iVar9 + 1) {
    auStack_18a0[iVar9 * 4] = auStack_1860[iVar9 * 4];
    auStack_18a0[iVar9 * 4 + 1] = auStack_1860[iVar9 * 4 + 1];
    auStack_18a0[iVar9 * 4 + 2] = auStack_1860[iVar9 * 4 + 2];
    auStack_18a0[iVar9 * 4 + 3] = auStack_1860[iVar9 * 4 + 3];
  }
  for (iVar9 = 0; iVar9 < *(int *)(param_1 + 0x70); iVar9 = iVar9 + 1) {
    for (iVar12 = 0; iVar12 < 0xc; iVar12 = iVar12 + 1) {
      auStack_48a0[(iVar12 + iVar9 * 0xc) * 4] =
           *(undefined4 *)(param_1 + iVar9 * 0xc0 + iVar12 * 0x10 + 0x680);
      auStack_48a0[(iVar12 + iVar9 * 0xc) * 4 + 1] =
           *(undefined4 *)(param_1 + iVar9 * 0xc0 + iVar12 * 0x10 + 0x684);
      auStack_48a0[(iVar12 + iVar9 * 0xc) * 4 + 2] =
           *(undefined4 *)(param_1 + iVar9 * 0xc0 + iVar12 * 0x10 + 0x688);
      auStack_48a0[(iVar12 + iVar9 * 0xc) * 4 + 3] = 0x3f800000;
    }
  }
  auVar7._0_8_ = (long)(int)auStack_18a0;
  auVar7._8_8_ = in_a1_udw;
  sceVu0RotTransPersN(aiStack_78a0,auVar7._0_8_,auStack_48a0,*(int *)(param_1 + 0x70) * 0xc,0);
  bVar3 = false;
  for (iVar9 = 0; iVar9 < *(int *)(param_1 + 0x70) * 0xc; iVar9 = iVar9 + 1) {
    if ((((aiStack_78a0[iVar9 * 4] < 0) || (0x10000 < aiStack_78a0[iVar9 * 4])) ||
        (aiStack_78a0[iVar9 * 4 + 1] < 0)) ||
       ((0x10000 < aiStack_78a0[iVar9 * 4 + 1] || (aiStack_78a0[iVar9 * 4 + 2] < 0)))) {
      bVar3 = true;
    }
    aiStack_78a0[iVar9 * 4 + 2] = (int)((float)aiStack_78a0[iVar9 * 4 + 2] / 16.0);
  }
  if (*(int *)(param_1 + 0x70) < 2) {
    bVar3 = true;
  }
  bVar1 = (*(byte *)(param_1 + 0x40) & 1) == 0;
  uVar11 = (uint)bVar1;
  iVar9 = (*(int *)(param_1 + 0x70) * 3 + 3) * 0xb;
  if (*(int *)(param_1 + uVar11 * 4 + 0x3680) != iVar9 + 10) {
    __dla__FPv(*(undefined4 *)(param_1 + uVar11 * 4 + 0x18));
    *(undefined4 *)(param_1 + uVar11 * 4 + 0x18) = 0;
    *(undefined4 *)(param_1 + uVar11 * 4 + 0x3680) = 0;
  }
  uVar8 = auVar7._8_8_;
  if (*(int *)(param_1 + uVar11 * 4 + 0x18) == 0) {
    uVar4 = __nwa__FUi((iVar9 + 10) * 0x10);
    uVar8 = auVar7._8_8_;
    *(undefined4 *)(param_1 + uVar11 * 4 + 0x18) = uVar4;
    *(int *)(param_1 + uVar11 * 4 + 0x3680) = iVar9 + 10;
  }
  puVar2 = *(undefined4 **)(param_1 + uVar11 * 4 + 0x18);
  if (bVar3) {
    *(undefined4 **)(param_1 + 0x54) = puVar2;
    *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfe | bVar1;
  }
  else {
    *puVar2 = 0x50000000;
    puVar2[1] = *(undefined4 *)
                 (*(int *)(iGpffff86b4 + 0x4254) +
                  (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x4254) + 10) * 4 + 0xc);
    puVar2[2] = 0;
    puVar2[3] = 0;
    puVar2[4] = iVar9 + 0x10000007;
    puVar2[5] = 0;
    puVar2[6] = 0;
    puVar2[7] = iVar9 + 0x50000007;
    *(undefined8 *)(puVar2 + 8) = 0x6000000000000001;
    *(undefined8 *)(puVar2 + 10) = 0xe6e8ee;
    *(undefined8 *)(puVar2 + 0xc) = 1;
    *(undefined8 *)(puVar2 + 0xe) = 0x3f;
    *(undefined8 *)(puVar2 + 0x10) = 0x60;
    *(undefined8 *)(puVar2 + 0x12) = 0x14;
    *(undefined8 *)(puVar2 + 0x14) = 5;
    *(undefined8 *)(puVar2 + 0x16) = 0;
    *(undefined8 *)(puVar2 + 0x18) = 0x73001;
    *(undefined8 *)(puVar2 + 0x1a) = 0x47;
    uVar5 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x4254),1);
    *(undefined8 *)(puVar2 + 0x1c) = uVar5;
    *(undefined8 *)(puVar2 + 0x1e) = 0;
    *(undefined8 *)(puVar2 + 0x20) = 0x48;
    *(undefined8 *)(puVar2 + 0x22) = 0x42;
    puVar10 = (undefined8 *)(puVar2 + 0x24);
    for (iVar9 = 0; iVar9 < 0xc; iVar9 = iVar9 + 1) {
      afStack_78d0[iVar9] =
           ((float)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x4254) + 4) * iVar9) / 11.0) /
           (float)(1 << (uint)((ulong)(*(long *)(*(int *)(iGpffff86b4 + 0x4254) + 0x50) << 0x1e) >>
                              0x3c));
    }
    for (iVar9 = 0; iVar9 < 0xb; iVar9 = iVar9 + 1) {
      auVar6._8_8_ = uVar8;
      auVar6._0_8_ = 0x8400000000000001;
      auVar15._4_4_ = in_zero_hi;
      auVar15._0_4_ = in_zero_lo;
      auVar15._8_4_ = in_zero_udw;
      auVar15._12_4_ = in_register_0000000c;
      auVar7 = _pcpyld(auVar15,auVar6);
      *puVar10 = auVar7._0_8_;
      uVar8 = auVar7._8_8_;
      puVar10[1] = 0xc12c12f0;
      puVar10[2] = 0x5c;
      puVar10[3] = 0;
      puVar10[4] = CONCAT44((16.0 / (float)aiStack_78a0[iVar9 * 4 + 3]) * afStack_78d0[iVar9],
                            (16.0 / (float)aiStack_78a0[iVar9 * 4 + 3]) * afStack_1810[iVar9]);
      puVar10[5] = 0x30808080;
      puVar10[6] = (long)aiStack_78a0[iVar9 * 4 + 2] << 0x20 |
                   (long)aiStack_78a0[iVar9 * 4] | (long)aiStack_78a0[iVar9 * 4 + 1] << 0x10;
      fVar13 = 16.0 / (float)aiStack_78a0[(iVar9 + 1) * 4 + 3];
      puVar10[7] = CONCAT44(fVar13 * afStack_78d0[iVar9 + 1],fVar13 * afStack_1810[iVar9 + 1]);
      puVar10[8] = (ulong)(uint)fVar13 << 0x20 | 0x30808080;
      puVar10[9] = (long)aiStack_78a0[(iVar9 + 1) * 4 + 2] << 0x20 |
                   (long)aiStack_78a0[(iVar9 + 1) * 4] |
                   (long)aiStack_78a0[(iVar9 + 1) * 4 + 1] << 0x10;
      if (iVar9 + 1 < 0xb) {
        puVar10[10] = (long)(*(int *)(param_1 + 0x70) + -1) | 0x6400000000000000;
      }
      else {
        puVar10[10] = (long)(*(int *)(param_1 + 0x70) + -1) | 0x6400000000008000;
      }
      puVar10[0xb] = 0x412412;
      puVar10 = puVar10 + 0xc;
      for (iVar12 = 1; iVar12 < *(int *)(param_1 + 0x70); iVar12 = iVar12 + 1) {
        fVar13 = 16.0 / (float)aiStack_78a0[(iVar9 + iVar12 * 0xc) * 4 + 3];
        *puVar10 = CONCAT44(fVar13 * afStack_78d0[iVar9],fVar13 * afStack_1810[iVar12 * 0xc + iVar9]
                           );
        if (iVar12 + 1 < *(int *)(param_1 + 0x70)) {
          puVar10[1] = (ulong)(uint)fVar13 << 0x20 | 0x30808080;
        }
        else {
          puVar10[1] = (ulong)(uint)fVar13 << 0x20 | 0x808080;
        }
        puVar10[2] = (long)aiStack_78a0[(iVar9 + iVar12 * 0xc) * 4 + 2] << 0x20 |
                     (long)aiStack_78a0[(iVar9 + iVar12 * 0xc) * 4] |
                     (long)aiStack_78a0[(iVar9 + iVar12 * 0xc) * 4 + 1] << 0x10;
        fVar13 = 16.0 / (float)aiStack_78a0[(iVar9 + iVar12 * 0xc + 1) * 4 + 3];
        puVar10[3] = CONCAT44(fVar13 * afStack_78d0[iVar9 + 1],
                              fVar13 * afStack_1810[iVar12 * 0xc + iVar9 + 1]);
        if (iVar12 + 1 < *(int *)(param_1 + 0x70)) {
          puVar10[4] = (ulong)(uint)fVar13 << 0x20 | 0x30808080;
        }
        else {
          puVar10[4] = (ulong)(uint)fVar13 << 0x20 | 0x808080;
        }
        puVar10[5] = (long)aiStack_78a0[(iVar9 + iVar12 * 0xc + 1) * 4 + 2] << 0x20 |
                     (long)aiStack_78a0[(iVar9 + iVar12 * 0xc + 1) * 4] |
                     (long)aiStack_78a0[(iVar9 + iVar12 * 0xc + 1) * 4 + 1] << 0x10;
        puVar10 = puVar10 + 6;
      }
    }
    *(undefined8 **)(param_1 + 0x54) = puVar10;
    *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfe | bVar1;
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00518700  ForceEndSet__15WhipLocusEffectFv
 * C++: WhipLocusEffect::ForceEndSet()
 * size: 0x54 bytes
 * --------------------------------------------------------------------------- */
void ForceEndSet__15WhipLocusEffectFv(int param_1)

{
  if (*(int *)(param_1 + 0x5c) == 0) {
    *(undefined4 *)(param_1 + 0x5c) = 1;
    *(undefined4 *)(param_1 + 0x60) = 0;
    *(undefined4 *)(param_1 + 100) = *(undefined4 *)(param_1 + 0x70);
    *(undefined4 *)(param_1 + 0x3688) = 0;
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054af40  EndSet__15WhipLocusEffectFv
 * C++: WhipLocusEffect::EndSet()
 * size: 0x10 bytes
 * --------------------------------------------------------------------------- */
void EndSet__15WhipLocusEffectFv(void)

{
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b650  @24@__dt__15WhipLocusEffectFv
 * C++: @24@__dt__15WhipLocusEffectFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int * _24___dt__15WhipLocusEffectFv(int *param_1,short param_2)

{
  int *piVar1;
  
  piVar1 = param_1 + -6;
  if (piVar1 != (int *)0x0) {
    param_1[-1] = 0x40a080;
    param_1[4] = 0x40a090;
    param_1[7] = 0x40a0a0;
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
 * JP: 0x0054b660  @44@__dt__15WhipLocusEffectFv
 * C++: @44@__dt__15WhipLocusEffectFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int _44___dt__15WhipLocusEffectFv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x2c;
  if (iVar1 != 0) {
    *(undefined4 *)(param_1 + -0x18) = 0x40a080;
    *(undefined4 *)(param_1 + -4) = 0x40a090;
    *(undefined4 *)(param_1 + 8) = 0x40a0a0;
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

