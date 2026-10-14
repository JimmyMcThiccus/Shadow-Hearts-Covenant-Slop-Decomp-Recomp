/* decomp/H/SwordLocusEffect3.c — cleaned Ghidra output (SH2JP_BATTLE.BIN, JP Furokuban, base 0x00430a00).
 * 9 function(s). Types: see types.h. Names/gp globals resolved from symbols/SLPM_602.19.syms. */
#include "types.h"

/* ---------------------------------------------------------------------------
 * JP: 0x005117f0  __ct__17SwordLocusEffect3Fiiiiii
 * C++: SwordLocusEffect3::__ct(int, int, int, int, int, int)
 * size: 0x8d8 bytes
 * --------------------------------------------------------------------------- */
undefined8
__ct__17SwordLocusEffect3Fiiiiii
          (undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined4 param_4,
          undefined4 param_5,undefined4 param_6,undefined4 param_7)

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
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  byte *pbVar18;
  int iVar19;
  undefined4 *puVar20;
  undefined1 (*pauVar21) [16];
  int iVar22;
  undefined1 in_vf0 [16];
  undefined1 auVar23 [16];
  undefined1 auVar24 [16];
  undefined1 auVar25 [16];
  undefined1 auStack_2a0 [16];
  undefined1 auStack_290 [16];
  undefined1 auStack_280 [16];
  undefined1 auStack_270 [16];
  undefined1 auStack_260 [16];
  undefined1 auStack_250 [16];
  undefined1 auStack_240 [16];
  undefined1 auStack_230 [16];
  undefined1 auStack_220 [16];
  undefined1 auStack_210 [16];
  undefined1 auStack_200 [16];
  undefined1 auStack_1f0 [16];
  undefined1 auStack_1e0 [16];
  undefined1 auStack_1d0 [16];
  undefined1 auStack_1c0 [8];
  undefined4 uStack_1b8;
  undefined4 uStack_1b4;
  undefined1 auStack_1b0 [8];
  undefined4 uStack_1a8;
  undefined4 uStack_1a4;
  undefined1 auStack_1a0 [16];
  undefined1 auStack_190 [16];
  undefined1 auStack_180 [8];
  undefined4 uStack_178;
  undefined4 uStack_174;
  undefined1 auStack_170 [16];
  undefined1 auStack_160 [16];
  undefined1 auStack_150 [8];
  undefined4 uStack_148;
  undefined4 uStack_144;
  undefined1 auStack_140 [16];
  undefined1 auStack_130 [16];
  undefined1 auStack_120 [8];
  undefined4 uStack_118;
  undefined4 uStack_114;
  undefined1 auStack_110 [16];
  undefined1 auStack_100 [16];
  undefined1 auStack_f0 [8];
  undefined4 uStack_e8;
  undefined4 uStack_e4;
  undefined4 uStack_e0;
  undefined4 uStack_dc;
  undefined4 uStack_d8;
  undefined4 uStack_d4;
  undefined4 uStack_d0;
  undefined4 uStack_cc;
  undefined4 uStack_c8;
  undefined4 uStack_c4;
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
  
  __ct__6BtlEffFii(param_1,param_2,param_3);
  iVar22 = (int)param_1;
  *(undefined4 *)(iVar22 + 0x14) = 0x40a120;
  *(undefined4 *)(iVar22 + 0x28) = 0x40a130;
  *(undefined4 *)(iVar22 + 0x34) = 0x40a140;
  puVar20 = (undefined4 *)(iVar22 + 0x80);
  do {
    *puVar20 = in_zero_lo;
    puVar20[1] = in_zero_hi;
    puVar20[2] = in_zero_udw;
    puVar20[3] = in_register_0000000c;
    puVar20 = puVar20 + 4;
  } while (puVar20 != (undefined4 *)(iVar22 + 0x180));
  puVar20 = (undefined4 *)(iVar22 + 0x180);
  do {
    *puVar20 = in_zero_lo;
    puVar20[1] = in_zero_hi;
    puVar20[2] = in_zero_udw;
    puVar20[3] = in_register_0000000c;
    puVar20 = puVar20 + 4;
  } while (puVar20 != (undefined4 *)(iVar22 + 0x980));
  *(undefined4 *)(iVar22 + 0x5c) = 0;
  *(undefined4 *)(iVar22 + 0x60) = 0;
  *(undefined4 *)(iVar22 + 100) = 0;
  *(undefined4 *)(iVar22 + 0x40) = 0;
  *(int *)(iVar22 + 0x44) = (int)param_2;
  *(int *)(iVar22 + 0x48) = (int)param_3;
  *(undefined4 *)(iVar22 + 0x4c) = 8;
  *(undefined4 *)(iVar22 + 0x6c) = 0;
  *(undefined4 *)(iVar22 + 0x68) = 0;
  *(undefined4 *)(iVar22 + 0x70) = 0;
  *(undefined4 *)(iVar22 + 0x1c) = 0;
  *(undefined4 *)(iVar22 + 0x18) = 0;
  *(undefined4 *)(iVar22 + 0x54) = 0;
  *(undefined4 *)(iVar22 + 0x984) = 0;
  *(undefined4 *)(iVar22 + 0x980) = 0;
  *(undefined4 *)(iVar22 + 0x98c) = param_4;
  *(undefined4 *)(iVar22 + 0x990) = param_5;
  *(undefined4 *)(iVar22 + 0x994) = param_6;
  *(undefined4 *)(iVar22 + 0x998) = param_7;
  auVar23 = _vmr32(in_vf0);
  auVar24 = _vmr32(auVar23);
  auVar25 = _vmr32(auVar24);
  auStack_10 = _sqc2(in_vf0);
  auStack_20 = _sqc2(auVar23);
  auStack_30 = _sqc2(auVar24);
  auStack_40 = _sqc2(auVar25);
  if (*(int *)(iVar22 + 0x990) == 1) {
    pbVar18 = (byte *)(*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar22 + 0x48) * 0x4f0 +
                                                 0x144) + 0x530) + 0xe4) +
                      *(int *)(iVar22 + 0x98c) * 0x110);
  }
  else if (*(int *)(iVar22 + 0x990) == 0) {
    pbVar18 = (byte *)(*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar22 + 0x48) * 0x4f0 +
                                                 0x144) + 0x52c) + 0xe4) +
                      *(int *)(iVar22 + 0x98c) * 0x110);
  }
  else {
    pbVar18 = (byte *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar22 + 0x48) * 0x4f0 + 0x144) +
                               0xe4) + *(int *)(iVar22 + 0x98c) * 0x110);
  }
  uStack_e0 = in_zero_lo;
  uStack_dc = in_zero_hi;
  uStack_d8 = in_zero_udw;
  uStack_d4 = in_register_0000000c;
  uStack_d0 = in_zero_lo;
  uStack_cc = in_zero_hi;
  uStack_c8 = in_zero_udw;
  uStack_c4 = in_register_0000000c;
  if (pbVar18 != (byte *)0x0) {
    if (*(int *)(iVar22 + 0x990) == 1) {
      pauVar21 = (undefined1 (*) [16])
                 (*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar22 + 0x48) * 0x4f0 + 0x144)
                                   + 0x530) + 0x30) + (uint)*pbVar18 * 0x1f0 +
                 (bGpffff8340 & 1) * 0x40);
      auStack_40 = *pauVar21;
      auStack_30 = pauVar21[1];
      auStack_20 = pauVar21[2];
      auStack_10 = pauVar21[3];
    }
    else if (*(int *)(iVar22 + 0x990) == 0) {
      pauVar21 = (undefined1 (*) [16])
                 (*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar22 + 0x48) * 0x4f0 + 0x144)
                                   + 0x52c) + 0x30) + (uint)*pbVar18 * 0x1f0 +
                 (bGpffff8340 & 1) * 0x40);
      auStack_40 = *pauVar21;
      auStack_30 = pauVar21[1];
      auStack_20 = pauVar21[2];
      auStack_10 = pauVar21[3];
    }
    else {
      pauVar21 = (undefined1 (*) [16])
                 (*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar22 + 0x48) * 0x4f0 + 0x144) + 0x30) +
                  (uint)*pbVar18 * 0x1f0 + (bGpffff8340 & 1) * 0x40);
      auStack_40 = *pauVar21;
      auStack_30 = pauVar21[1];
      auStack_20 = pauVar21[2];
      auStack_10 = pauVar21[3];
    }
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
    RotTransVector(&uStack_c0,pbVar18 + 0x10,auStack_40,8);
    iVar19 = *(int *)(iVar22 + 0x994);
    if (iVar19 == 2) {
      auVar23._4_4_ = uStack_bc;
      auVar23._0_4_ = uStack_c0;
      auVar23._8_4_ = uStack_b8;
      auVar23._12_4_ = uStack_b4;
      auVar23 = _lqc2(auVar23);
      auVar24._4_4_ = uStack_ac;
      auVar24._0_4_ = uStack_b0;
      auVar24._8_4_ = uStack_a8;
      auVar24._12_4_ = uStack_a4;
      auVar24 = _lqc2(auVar24);
      auVar23 = _vadd(auVar23,auVar24);
      auStack_210 = _sqc2(auVar23);
      __ct__7FVectorFRC7FVector(auStack_1b0,auStack_210);
      uStack_e0 = auStack_1b0._0_4_;
      uStack_dc = auStack_1b0._4_4_;
      uStack_d8 = uStack_1a8;
      uStack_d4 = uStack_1a4;
      auVar25._4_4_ = uStack_7c;
      auVar25._0_4_ = uStack_80;
      auVar25._8_4_ = uStack_78;
      auVar25._12_4_ = uStack_74;
      auVar23 = _lqc2(auVar25);
      auVar13._4_4_ = uStack_6c;
      auVar13._0_4_ = uStack_70;
      auVar13._8_4_ = uStack_68;
      auVar13._12_4_ = uStack_64;
      auVar24 = _lqc2(auVar13);
      auVar23 = _vadd(auVar23,auVar24);
      auStack_220 = _sqc2(auVar23);
      __ct__7FVectorFRC7FVector(auStack_1c0,auStack_220);
      uStack_d0 = auStack_1c0._0_4_;
      uStack_cc = auStack_1c0._4_4_;
      uStack_c8 = uStack_1b8;
      uStack_c4 = uStack_1b4;
      __adv__7FVectorFf(0x40000000,&uStack_e0);
      __adv__7FVectorFf(0x40000000,&uStack_d0);
    }
    else if (iVar19 == 1) {
      auVar2._4_4_ = uStack_bc;
      auVar2._0_4_ = uStack_c0;
      auVar2._8_4_ = uStack_b8;
      auVar2._12_4_ = uStack_b4;
      auVar23 = _lqc2(auVar2);
      auVar4._4_4_ = uStack_ac;
      auVar4._0_4_ = uStack_b0;
      auVar4._8_4_ = uStack_a8;
      auVar4._12_4_ = uStack_a4;
      auVar24 = _lqc2(auVar4);
      auVar23 = _vadd(auVar23,auVar24);
      auStack_270 = _sqc2(auVar23);
      __ct__7FVectorFRC7FVector(auStack_170,auStack_270);
      auVar23 = _lqc2(auStack_170);
      auVar15._4_4_ = uStack_5c;
      auVar15._0_4_ = uStack_60;
      auVar15._8_4_ = uStack_58;
      auVar15._12_4_ = uStack_54;
      auVar24 = _lqc2(auVar15);
      auVar23 = _vadd(auVar23,auVar24);
      auStack_280 = _sqc2(auVar23);
      __ct__7FVectorFRC7FVector(auStack_160,auStack_280);
      auVar23 = _lqc2(auStack_160);
      auVar17._4_4_ = uStack_4c;
      auVar17._0_4_ = uStack_50;
      auVar17._8_4_ = uStack_48;
      auVar17._12_4_ = uStack_44;
      auVar24 = _lqc2(auVar17);
      auVar23 = _vadd(auVar23,auVar24);
      auStack_1f0 = _sqc2(auVar23);
      __ct__7FVectorFRC7FVector(auStack_150,auStack_1f0);
      uStack_e0 = auStack_150._0_4_;
      uStack_dc = auStack_150._4_4_;
      uStack_d8 = uStack_148;
      uStack_d4 = uStack_144;
      auVar6._4_4_ = uStack_9c;
      auVar6._0_4_ = uStack_a0;
      auVar6._8_4_ = uStack_98;
      auVar6._12_4_ = uStack_94;
      auVar23 = _lqc2(auVar6);
      auVar8._4_4_ = uStack_8c;
      auVar8._0_4_ = uStack_90;
      auVar8._8_4_ = uStack_88;
      auVar8._12_4_ = uStack_84;
      auVar24 = _lqc2(auVar8);
      auVar23 = _vadd(auVar23,auVar24);
      auStack_290 = _sqc2(auVar23);
      __ct__7FVectorFRC7FVector(auStack_1a0,auStack_290);
      auVar23 = _lqc2(auStack_1a0);
      auVar10._4_4_ = uStack_7c;
      auVar10._0_4_ = uStack_80;
      auVar10._8_4_ = uStack_78;
      auVar10._12_4_ = uStack_74;
      auVar24 = _lqc2(auVar10);
      auVar23 = _vadd(auVar23,auVar24);
      auStack_2a0 = _sqc2(auVar23);
      __ct__7FVectorFRC7FVector(auStack_190,auStack_2a0);
      auVar23 = _lqc2(auStack_190);
      auVar12._4_4_ = uStack_6c;
      auVar12._0_4_ = uStack_70;
      auVar12._8_4_ = uStack_68;
      auVar12._12_4_ = uStack_64;
      auVar24 = _lqc2(auVar12);
      auVar23 = _vadd(auVar23,auVar24);
      auStack_200 = _sqc2(auVar23);
      __ct__7FVectorFRC7FVector(auStack_180,auStack_200);
      uStack_d0 = auStack_180._0_4_;
      uStack_cc = auStack_180._4_4_;
      uStack_c8 = uStack_178;
      uStack_c4 = uStack_174;
      __adv__7FVectorFf(0x40800000,&uStack_e0);
      __adv__7FVectorFf(0x40800000,&uStack_d0);
    }
    else if (iVar19 == 0) {
      auVar3._4_4_ = uStack_ac;
      auVar3._0_4_ = uStack_b0;
      auVar3._8_4_ = uStack_a8;
      auVar3._12_4_ = uStack_a4;
      auVar23 = _lqc2(auVar3);
      auVar7._4_4_ = uStack_8c;
      auVar7._0_4_ = uStack_90;
      auVar7._8_4_ = uStack_88;
      auVar7._12_4_ = uStack_84;
      auVar24 = _lqc2(auVar7);
      auVar23 = _vadd(auVar23,auVar24);
      auStack_230 = _sqc2(auVar23);
      __ct__7FVectorFRC7FVector(auStack_110,auStack_230);
      auVar23 = _lqc2(auStack_110);
      auVar11._4_4_ = uStack_6c;
      auVar11._0_4_ = uStack_70;
      auVar11._8_4_ = uStack_68;
      auVar11._12_4_ = uStack_64;
      auVar24 = _lqc2(auVar11);
      auVar23 = _vadd(auVar23,auVar24);
      auStack_240 = _sqc2(auVar23);
      __ct__7FVectorFRC7FVector(auStack_100,auStack_240);
      auVar23 = _lqc2(auStack_100);
      auVar16._4_4_ = uStack_4c;
      auVar16._0_4_ = uStack_50;
      auVar16._8_4_ = uStack_48;
      auVar16._12_4_ = uStack_44;
      auVar24 = _lqc2(auVar16);
      auVar23 = _vadd(auVar23,auVar24);
      auStack_1d0 = _sqc2(auVar23);
      __ct__7FVectorFRC7FVector(auStack_f0,auStack_1d0);
      uStack_e0 = auStack_f0._0_4_;
      uStack_dc = auStack_f0._4_4_;
      uStack_d8 = uStack_e8;
      uStack_d4 = uStack_e4;
      auVar1._4_4_ = uStack_bc;
      auVar1._0_4_ = uStack_c0;
      auVar1._8_4_ = uStack_b8;
      auVar1._12_4_ = uStack_b4;
      auVar23 = _lqc2(auVar1);
      auVar5._4_4_ = uStack_9c;
      auVar5._0_4_ = uStack_a0;
      auVar5._8_4_ = uStack_98;
      auVar5._12_4_ = uStack_94;
      auVar24 = _lqc2(auVar5);
      auVar23 = _vadd(auVar23,auVar24);
      auStack_250 = _sqc2(auVar23);
      __ct__7FVectorFRC7FVector(auStack_140,auStack_250);
      auVar23 = _lqc2(auStack_140);
      auVar9._4_4_ = uStack_7c;
      auVar9._0_4_ = uStack_80;
      auVar9._8_4_ = uStack_78;
      auVar9._12_4_ = uStack_74;
      auVar24 = _lqc2(auVar9);
      auVar23 = _vadd(auVar23,auVar24);
      auStack_260 = _sqc2(auVar23);
      __ct__7FVectorFRC7FVector(auStack_130,auStack_260);
      auVar23 = _lqc2(auStack_130);
      auVar14._4_4_ = uStack_5c;
      auVar14._0_4_ = uStack_60;
      auVar14._8_4_ = uStack_58;
      auVar14._12_4_ = uStack_54;
      auVar24 = _lqc2(auVar14);
      auVar23 = _vadd(auVar23,auVar24);
      auStack_1e0 = _sqc2(auVar23);
      __ct__7FVectorFRC7FVector(auStack_120,auStack_1e0);
      uStack_d0 = auStack_120._0_4_;
      uStack_cc = auStack_120._4_4_;
      uStack_c8 = uStack_118;
      uStack_c4 = uStack_114;
      __adv__7FVectorFf(0x40800000,&uStack_e0);
      __adv__7FVectorFf(0x40800000,&uStack_d0);
    }
    iVar19 = iVar22 + *(int *)(iVar22 + 0x6c) * 0x20;
    *(undefined4 *)(iVar19 + 0x80) = uStack_e0;
    *(undefined4 *)(iVar19 + 0x84) = uStack_dc;
    *(undefined4 *)(iVar19 + 0x88) = uStack_d8;
    *(undefined4 *)(iVar19 + 0x8c) = uStack_d4;
    iVar19 = iVar22 + *(int *)(iVar22 + 0x6c) * 0x20;
    *(undefined4 *)(iVar19 + 0x90) = uStack_d0;
    *(undefined4 *)(iVar19 + 0x94) = uStack_cc;
    *(undefined4 *)(iVar19 + 0x98) = uStack_c8;
    *(undefined4 *)(iVar19 + 0x9c) = uStack_c4;
    *(int *)(iVar22 + 0x6c) = *(int *)(iVar22 + 0x6c) + 1;
    *(int *)(iVar22 + 0x68) = *(int *)(iVar22 + 0x68) + 1;
  }
  Entry__7CPollerFP7CPolObjib(iGpffff858c + 0x48,param_1,0x80,0);
  BtlEffEntry__7CBattleFiP6BtlEff(iGpffff86b4,*(undefined4 *)(iVar22 + 0x48),param_1);
  return param_1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005120d0  __dt__17SwordLocusEffect3Fv
 * C++: SwordLocusEffect3::__dt()
 * size: 0x154 bytes
 * --------------------------------------------------------------------------- */
int __dt__17SwordLocusEffect3Fv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x14) = 0x40a120;
    *(undefined4 *)(param_1 + 0x28) = 0x40a130;
    *(undefined4 *)(param_1 + 0x34) = 0x40a140;
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
 * JP: 0x00512230  Destruct__17SwordLocusEffect3Fv
 * C++: SwordLocusEffect3::Destruct()
 * size: 0xc8 bytes
 * --------------------------------------------------------------------------- */
void Destruct__17SwordLocusEffect3Fv(int param_1)

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
 * JP: 0x00512300  Polling__17SwordLocusEffect3Fv
 * C++: SwordLocusEffect3::Polling()
 * size: 0xdf8 bytes
 * --------------------------------------------------------------------------- */
undefined4 Polling__17SwordLocusEffect3Fv(int param_1)

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
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  byte *pbVar27;
  int iVar28;
  int iVar29;
  undefined4 uVar30;
  undefined4 uVar31;
  undefined1 (*pauVar32) [16];
  int iVar33;
  float fVar34;
  undefined1 in_vf0 [16];
  undefined1 auVar35 [16];
  undefined1 auVar36 [16];
  undefined1 auVar37 [16];
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
  undefined1 auStack_360 [8];
  undefined4 uStack_358;
  undefined4 uStack_354;
  undefined1 auStack_350 [8];
  undefined4 uStack_348;
  undefined4 uStack_344;
  undefined1 auStack_340 [16];
  undefined1 auStack_330 [8];
  undefined4 uStack_328;
  undefined4 uStack_324;
  undefined1 auStack_320 [8];
  undefined4 uStack_318;
  undefined4 uStack_314;
  undefined1 auStack_310 [16];
  undefined1 auStack_300 [8];
  undefined4 uStack_2f8;
  undefined4 uStack_2f4;
  undefined1 auStack_2f0 [8];
  undefined4 uStack_2e8;
  undefined4 uStack_2e4;
  undefined1 auStack_2e0 [8];
  undefined4 uStack_2d8;
  undefined4 uStack_2d4;
  undefined1 auStack_2d0 [8];
  undefined4 uStack_2c8;
  undefined4 uStack_2c4;
  undefined1 auStack_2c0 [16];
  undefined1 auStack_2b0 [16];
  undefined1 auStack_2a0 [8];
  undefined4 uStack_298;
  undefined4 uStack_294;
  undefined1 auStack_290 [16];
  undefined1 auStack_280 [16];
  undefined1 auStack_270 [8];
  undefined4 uStack_268;
  undefined4 uStack_264;
  undefined1 auStack_260 [16];
  undefined1 auStack_250 [16];
  undefined1 auStack_240 [8];
  undefined4 uStack_238;
  undefined4 uStack_234;
  undefined1 auStack_230 [16];
  undefined1 auStack_220 [16];
  undefined1 auStack_210 [8];
  undefined4 uStack_208;
  undefined4 uStack_204;
  undefined4 auStack_200 [7];
  undefined4 uStack_1e4;
  undefined4 auStack_180 [7];
  undefined4 uStack_164;
  undefined1 auStack_100 [16];
  undefined1 auStack_f0 [16];
  undefined1 auStack_e0 [16];
  undefined1 auStack_d0 [16];
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
  undefined1 auStack_10 [8];
  undefined1 auStack_8 [8];
  
  auVar35 = _vmr32(in_vf0);
  auVar36 = _vmr32(auVar35);
  auVar37 = _vmr32(auVar36);
  auStack_d0 = _sqc2(in_vf0);
  auStack_e0 = _sqc2(auVar35);
  auStack_f0 = _sqc2(auVar36);
  auStack_100 = _sqc2(auVar37);
  fVar34 = *(float *)(iGpffff86b4 + 0x38);
  if ((*(byte *)(iGpffff86b4 + 0x24) & 1) != 0) {
    fVar34 = 0.0;
  }
  uStack_40 = in_zero_lo;
  uStack_3c = in_zero_hi;
  uStack_38 = in_zero_udw;
  uStack_34 = in_register_0000000c;
  uStack_30 = in_zero_lo;
  uStack_2c = in_zero_hi;
  uStack_28 = in_zero_udw;
  uStack_24 = in_register_0000000c;
  if (fVar34 != 0.0) {
    if (*(int *)(param_1 + 0x990) == 1) {
      pbVar27 = (byte *)(*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 +
                                                   0x144) + 0x530) + 0xe4) +
                        *(int *)(param_1 + 0x98c) * 0x110);
    }
    else if (*(int *)(param_1 + 0x990) == 0) {
      pbVar27 = (byte *)(*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 +
                                                   0x144) + 0x52c) + 0xe4) +
                        *(int *)(param_1 + 0x98c) * 0x110);
    }
    else {
      pbVar27 = (byte *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x144) +
                                 0xe4) + *(int *)(param_1 + 0x98c) * 0x110);
    }
    if (pbVar27 != (byte *)0x0) {
      if (*(int *)(param_1 + 0x990) == 1) {
        pauVar32 = (undefined1 (*) [16])
                   (*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 +
                                              0x144) + 0x530) + 0x30) + (uint)*pbVar27 * 0x1f0 +
                   (bGpffff8340 & 1) * 0x40);
        auStack_100 = *pauVar32;
        auStack_f0 = pauVar32[1];
        auStack_e0 = pauVar32[2];
        auStack_d0 = pauVar32[3];
      }
      else if (*(int *)(param_1 + 0x990) == 0) {
        pauVar32 = (undefined1 (*) [16])
                   (*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 +
                                              0x144) + 0x52c) + 0x30) + (uint)*pbVar27 * 0x1f0 +
                   (bGpffff8340 & 1) * 0x40);
        auStack_100 = *pauVar32;
        auStack_f0 = pauVar32[1];
        auStack_e0 = pauVar32[2];
        auStack_d0 = pauVar32[3];
      }
      else {
        pauVar32 = (undefined1 (*) [16])
                   (*(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x144) + 0x30
                            ) + (uint)*pbVar27 * 0x1f0 + (bGpffff8340 & 1) * 0x40);
        auStack_100 = *pauVar32;
        auStack_f0 = pauVar32[1];
        auStack_e0 = pauVar32[2];
        auStack_d0 = pauVar32[3];
      }
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
      RotTransVector(&uStack_c0,pbVar27 + 0x10,auStack_100,8);
      iVar33 = *(int *)(param_1 + 0x994);
      if (iVar33 == 2) {
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
        auStack_3b0 = _sqc2(auVar35);
        __ct__7FVectorFRC7FVector(auStack_2d0,auStack_3b0);
        uStack_40 = auStack_2d0._0_4_;
        uStack_3c = auStack_2d0._4_4_;
        uStack_38 = uStack_2c8;
        uStack_34 = uStack_2c4;
        auVar37._4_4_ = uStack_7c;
        auVar37._0_4_ = uStack_80;
        auVar37._8_4_ = uStack_78;
        auVar37._12_4_ = uStack_74;
        auVar35 = _lqc2(auVar37);
        auVar20._4_4_ = uStack_6c;
        auVar20._0_4_ = uStack_70;
        auVar20._8_4_ = uStack_68;
        auVar20._12_4_ = uStack_64;
        auVar36 = _lqc2(auVar20);
        auVar35 = _vadd(auVar35,auVar36);
        auStack_3c0 = _sqc2(auVar35);
        __ct__7FVectorFRC7FVector(auStack_2e0,auStack_3c0);
        uStack_30 = auStack_2e0._0_4_;
        uStack_2c = auStack_2e0._4_4_;
        uStack_28 = uStack_2d8;
        uStack_24 = uStack_2d4;
        __adv__7FVectorFf(0x40000000,&uStack_40);
        __adv__7FVectorFf(0x40000000,&uStack_30);
      }
      else if (iVar33 == 1) {
        auVar9._4_4_ = uStack_bc;
        auVar9._0_4_ = uStack_c0;
        auVar9._8_4_ = uStack_b8;
        auVar9._12_4_ = uStack_b4;
        auVar35 = _lqc2(auVar9);
        auVar11._4_4_ = uStack_ac;
        auVar11._0_4_ = uStack_b0;
        auVar11._8_4_ = uStack_a8;
        auVar11._12_4_ = uStack_a4;
        auVar36 = _lqc2(auVar11);
        auVar35 = _vadd(auVar35,auVar36);
        auStack_450 = _sqc2(auVar35);
        __ct__7FVectorFRC7FVector(auStack_290,auStack_450);
        auVar35 = _lqc2(auStack_290);
        auVar22._4_4_ = uStack_5c;
        auVar22._0_4_ = uStack_60;
        auVar22._8_4_ = uStack_58;
        auVar22._12_4_ = uStack_54;
        auVar36 = _lqc2(auVar22);
        auVar35 = _vadd(auVar35,auVar36);
        auStack_460 = _sqc2(auVar35);
        __ct__7FVectorFRC7FVector(auStack_280,auStack_460);
        auVar35 = _lqc2(auStack_280);
        auVar24._4_4_ = uStack_4c;
        auVar24._0_4_ = uStack_50;
        auVar24._8_4_ = uStack_48;
        auVar24._12_4_ = uStack_44;
        auVar36 = _lqc2(auVar24);
        auVar35 = _vadd(auVar35,auVar36);
        auStack_390 = _sqc2(auVar35);
        __ct__7FVectorFRC7FVector(auStack_270,auStack_390);
        uStack_40 = auStack_270._0_4_;
        uStack_3c = auStack_270._4_4_;
        uStack_38 = uStack_268;
        uStack_34 = uStack_264;
        auVar13._4_4_ = uStack_9c;
        auVar13._0_4_ = uStack_a0;
        auVar13._8_4_ = uStack_98;
        auVar13._12_4_ = uStack_94;
        auVar35 = _lqc2(auVar13);
        auVar15._4_4_ = uStack_8c;
        auVar15._0_4_ = uStack_90;
        auVar15._8_4_ = uStack_88;
        auVar15._12_4_ = uStack_84;
        auVar36 = _lqc2(auVar15);
        auVar35 = _vadd(auVar35,auVar36);
        auStack_470 = _sqc2(auVar35);
        __ct__7FVectorFRC7FVector(auStack_2c0,auStack_470);
        auVar35 = _lqc2(auStack_2c0);
        auVar17._4_4_ = uStack_7c;
        auVar17._0_4_ = uStack_80;
        auVar17._8_4_ = uStack_78;
        auVar17._12_4_ = uStack_74;
        auVar36 = _lqc2(auVar17);
        auVar35 = _vadd(auVar35,auVar36);
        auStack_480 = _sqc2(auVar35);
        __ct__7FVectorFRC7FVector(auStack_2b0,auStack_480);
        auVar35 = _lqc2(auStack_2b0);
        auVar19._4_4_ = uStack_6c;
        auVar19._0_4_ = uStack_70;
        auVar19._8_4_ = uStack_68;
        auVar19._12_4_ = uStack_64;
        auVar36 = _lqc2(auVar19);
        auVar35 = _vadd(auVar35,auVar36);
        auStack_3a0 = _sqc2(auVar35);
        __ct__7FVectorFRC7FVector(auStack_2a0,auStack_3a0);
        uStack_30 = auStack_2a0._0_4_;
        uStack_2c = auStack_2a0._4_4_;
        uStack_28 = uStack_298;
        uStack_24 = uStack_294;
        __adv__7FVectorFf(0x40800000,&uStack_40);
        __adv__7FVectorFf(0x40800000,&uStack_30);
      }
      else if (iVar33 == 0) {
        auVar10._4_4_ = uStack_ac;
        auVar10._0_4_ = uStack_b0;
        auVar10._8_4_ = uStack_a8;
        auVar10._12_4_ = uStack_a4;
        auVar35 = _lqc2(auVar10);
        auVar14._4_4_ = uStack_8c;
        auVar14._0_4_ = uStack_90;
        auVar14._8_4_ = uStack_88;
        auVar14._12_4_ = uStack_84;
        auVar36 = _lqc2(auVar14);
        auVar35 = _vadd(auVar35,auVar36);
        auStack_410 = _sqc2(auVar35);
        __ct__7FVectorFRC7FVector(auStack_230,auStack_410);
        auVar35 = _lqc2(auStack_230);
        auVar18._4_4_ = uStack_6c;
        auVar18._0_4_ = uStack_70;
        auVar18._8_4_ = uStack_68;
        auVar18._12_4_ = uStack_64;
        auVar36 = _lqc2(auVar18);
        auVar35 = _vadd(auVar35,auVar36);
        auStack_420 = _sqc2(auVar35);
        __ct__7FVectorFRC7FVector(auStack_220,auStack_420);
        auVar35 = _lqc2(auStack_220);
        auVar23._4_4_ = uStack_4c;
        auVar23._0_4_ = uStack_50;
        auVar23._8_4_ = uStack_48;
        auVar23._12_4_ = uStack_44;
        auVar36 = _lqc2(auVar23);
        auVar35 = _vadd(auVar35,auVar36);
        auStack_370 = _sqc2(auVar35);
        __ct__7FVectorFRC7FVector(auStack_210,auStack_370);
        uStack_40 = auStack_210._0_4_;
        uStack_3c = auStack_210._4_4_;
        uStack_38 = uStack_208;
        uStack_34 = uStack_204;
        auVar8._4_4_ = uStack_bc;
        auVar8._0_4_ = uStack_c0;
        auVar8._8_4_ = uStack_b8;
        auVar8._12_4_ = uStack_b4;
        auVar35 = _lqc2(auVar8);
        auVar12._4_4_ = uStack_9c;
        auVar12._0_4_ = uStack_a0;
        auVar12._8_4_ = uStack_98;
        auVar12._12_4_ = uStack_94;
        auVar36 = _lqc2(auVar12);
        auVar35 = _vadd(auVar35,auVar36);
        auStack_430 = _sqc2(auVar35);
        __ct__7FVectorFRC7FVector(auStack_260,auStack_430);
        auVar35 = _lqc2(auStack_260);
        auVar16._4_4_ = uStack_7c;
        auVar16._0_4_ = uStack_80;
        auVar16._8_4_ = uStack_78;
        auVar16._12_4_ = uStack_74;
        auVar36 = _lqc2(auVar16);
        auVar35 = _vadd(auVar35,auVar36);
        auStack_440 = _sqc2(auVar35);
        __ct__7FVectorFRC7FVector(auStack_250,auStack_440);
        auVar35 = _lqc2(auStack_250);
        auVar21._4_4_ = uStack_5c;
        auVar21._0_4_ = uStack_60;
        auVar21._8_4_ = uStack_58;
        auVar21._12_4_ = uStack_54;
        auVar36 = _lqc2(auVar21);
        auVar35 = _vadd(auVar35,auVar36);
        auStack_380 = _sqc2(auVar35);
        __ct__7FVectorFRC7FVector(auStack_240,auStack_380);
        uStack_30 = auStack_240._0_4_;
        uStack_2c = auStack_240._4_4_;
        uStack_28 = uStack_238;
        uStack_24 = uStack_234;
        __adv__7FVectorFf(0x40800000,&uStack_40);
        __adv__7FVectorFf(0x40800000,&uStack_30);
      }
      iVar33 = param_1 + *(int *)(param_1 + 0x6c) * 0x20;
      *(undefined4 *)(iVar33 + 0x80) = uStack_40;
      *(undefined4 *)(iVar33 + 0x84) = uStack_3c;
      *(undefined4 *)(iVar33 + 0x88) = uStack_38;
      *(undefined4 *)(iVar33 + 0x8c) = uStack_34;
      iVar33 = param_1 + *(int *)(param_1 + 0x6c) * 0x20;
      *(undefined4 *)(iVar33 + 0x90) = uStack_30;
      *(undefined4 *)(iVar33 + 0x94) = uStack_2c;
      *(undefined4 *)(iVar33 + 0x98) = uStack_28;
      *(undefined4 *)(iVar33 + 0x9c) = uStack_24;
      *(int *)(param_1 + 0x6c) = *(int *)(param_1 + 0x6c) + 1;
      if (7 < *(int *)(param_1 + 0x6c)) {
        *(undefined4 *)(param_1 + 0x6c) = 0;
      }
      *(int *)(param_1 + 0x68) = *(int *)(param_1 + 0x68) + 1;
      if (8 < *(int *)(param_1 + 0x68)) {
        *(undefined4 *)(param_1 + 0x68) = 8;
      }
    }
  }
  iVar33 = *(int *)(param_1 + 0x6c);
  auStack_200[0] = in_zero_lo;
  auStack_200[1] = in_zero_hi;
  auStack_200[2] = in_zero_udw;
  auStack_200[3] = in_register_0000000c;
  auStack_200[4] = in_zero_lo;
  auStack_200[5] = in_zero_hi;
  auStack_200[6] = in_zero_udw;
  uStack_1e4 = in_register_0000000c;
  auStack_180[0] = in_zero_lo;
  auStack_180[1] = in_zero_hi;
  auStack_180[2] = in_zero_udw;
  auStack_180[3] = in_register_0000000c;
  auStack_180[4] = in_zero_lo;
  auStack_180[5] = in_zero_hi;
  auStack_180[6] = in_zero_udw;
  uStack_164 = in_register_0000000c;
  for (iVar28 = 0; iVar28 < *(int *)(param_1 + 0x68); iVar28 = iVar28 + 1) {
    iVar33 = iVar33 + -1;
    if (iVar33 < 0) {
      iVar33 = 7;
    }
    iVar29 = param_1 + iVar33 * 0x20;
    uVar1 = *(undefined8 *)(iVar29 + 0x80);
    uVar30 = *(undefined4 *)(iVar29 + 0x88);
    uVar31 = *(undefined4 *)(iVar29 + 0x8c);
    auStack_180[iVar28 * 4] = (int)uVar1;
    auStack_180[iVar28 * 4 + 1] = (int)((ulong)uVar1 >> 0x20);
    auStack_180[iVar28 * 4 + 2] = uVar30;
    auStack_180[iVar28 * 4 + 3] = uVar31;
    iVar29 = param_1 + iVar33 * 0x20;
    uVar1 = *(undefined8 *)(iVar29 + 0x90);
    uVar30 = *(undefined4 *)(iVar29 + 0x98);
    uVar31 = *(undefined4 *)(iVar29 + 0x9c);
    auStack_200[iVar28 * 4] = (int)uVar1;
    auStack_200[iVar28 * 4 + 1] = (int)((ulong)uVar1 >> 0x20);
    auStack_200[iVar28 * 4 + 2] = uVar30;
    auStack_200[iVar28 * 4 + 3] = uVar31;
  }
  if (*(int *)(param_1 + 0x5c) == 0) {
    iVar33 = (*(int *)(param_1 + 0x68) + -1) * 8 + 1;
    *(int *)(param_1 + 0x70) = iVar33;
  }
  else {
    *(float *)(param_1 + 0x988) = *(float *)(param_1 + 0x988) + fVar34;
    while ((1 < *(int *)(param_1 + 100) && (0.004166667 < *(float *)(param_1 + 0x988)))) {
      *(float *)(param_1 + 0x988) = *(float *)(param_1 + 0x988) - 0.004166667;
      *(int *)(param_1 + 100) = *(int *)(param_1 + 100) + -1;
    }
    if (*(int *)(param_1 + 100) < 2) {
      BtlEffRelease__7CBattleFiP6BtlEff(iGpffff86b4,*(undefined4 *)(param_1 + 0x48),param_1);
      if ((long)((ulong)*(byte *)(param_1 + 0x40) << 0x3e) < 0) {
        iVar33 = param_1;
        if (param_1 != 0) {
          iVar33 = param_1 + 0x18;
        }
        ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,iVar33);
      }
      *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfd;
      (**(code **)(*(int *)(param_1 + 0x34) + 0xc))();
      return 1;
    }
    iVar33 = (*(int *)(param_1 + 0x68) + -1) * 8 + 1;
    *(undefined4 *)(param_1 + 0x70) = *(undefined4 *)(param_1 + 100);
  }
  if (*(int *)(param_1 + 0x68) == 1) {
    *(undefined4 *)(param_1 + 0x180) = auStack_180[0];
    *(undefined4 *)(param_1 + 0x184) = auStack_180[1];
    *(undefined4 *)(param_1 + 0x188) = auStack_180[2];
    *(undefined4 *)(param_1 + 0x18c) = auStack_180[3];
    *(undefined4 *)(param_1 + 400) = auStack_200[0];
    *(undefined4 *)(param_1 + 0x194) = auStack_200[1];
    *(undefined4 *)(param_1 + 0x198) = auStack_200[2];
    *(undefined4 *)(param_1 + 0x19c) = auStack_200[3];
  }
  else if (*(int *)(param_1 + 0x68) == 2) {
    *(undefined4 *)(param_1 + 0x180) = auStack_180[0];
    *(undefined4 *)(param_1 + 0x184) = auStack_180[1];
    *(undefined4 *)(param_1 + 0x188) = auStack_180[2];
    *(undefined4 *)(param_1 + 0x18c) = auStack_180[3];
    *(undefined4 *)(param_1 + 400) = auStack_200[0];
    *(undefined4 *)(param_1 + 0x194) = auStack_200[1];
    *(undefined4 *)(param_1 + 0x198) = auStack_200[2];
    *(undefined4 *)(param_1 + 0x19c) = auStack_200[3];
    auVar4._4_4_ = auStack_180[1];
    auVar4._0_4_ = auStack_180[0];
    auVar4._8_4_ = auStack_180[2];
    auVar4._12_4_ = auStack_180[3];
    auVar35 = _lqc2(auVar4);
    auVar5._4_4_ = auStack_180[5];
    auVar5._0_4_ = auStack_180[4];
    auVar5._8_4_ = auStack_180[6];
    auVar5._12_4_ = uStack_164;
    auVar36 = _lqc2(auVar5);
    auVar35 = _vsub(auVar35,auVar36);
    auStack_3d0 = _sqc2(auVar35);
    __ct__7FVectorFRC7FVector(auStack_2f0,auStack_3d0);
    uStack_20 = auStack_2f0._0_4_;
    uStack_1c = auStack_2f0._4_4_;
    uStack_18 = uStack_2e8;
    uStack_14 = uStack_2e4;
    for (iVar33 = 1; iVar33 < 8; iVar33 = iVar33 + 1) {
      iVar28 = iVar33;
      if (iVar33 < 0) {
        iVar28 = iVar33 + 7;
      }
      auVar25._4_4_ = uStack_1c;
      auVar25._0_4_ = uStack_20;
      auVar25._8_4_ = uStack_18;
      auVar25._12_4_ = uStack_14;
      auVar35 = _lqc2(auVar25);
      auVar36 = _qmtc2((float)(iVar28 >> 3));
      auVar35 = _vmulbc(auVar35,auVar36);
      auStack_490 = _sqc2(auVar35);
      __ct__7FVectorFRC7FVector(auStack_310,auStack_490);
      auVar6._4_4_ = auStack_180[5];
      auVar6._0_4_ = auStack_180[4];
      auVar6._8_4_ = auStack_180[6];
      auVar6._12_4_ = uStack_164;
      auVar35 = _lqc2(auVar6);
      auVar36 = _lqc2(auStack_310);
      auVar35 = _vadd(auVar35,auVar36);
      auStack_3e0 = _sqc2(auVar35);
      __ct__7FVectorFRC7FVector(auStack_300,auStack_3e0);
      iVar28 = param_1 + iVar33 * 0x20;
      *(int *)(iVar28 + 0x180) = auStack_300._0_4_;
      *(int *)(iVar28 + 0x184) = auStack_300._4_4_;
      *(undefined4 *)(iVar28 + 0x188) = uStack_2f8;
      *(undefined4 *)(iVar28 + 0x18c) = uStack_2f4;
    }
    auVar2._4_4_ = auStack_200[1];
    auVar2._0_4_ = auStack_200[0];
    auVar2._8_4_ = auStack_200[2];
    auVar2._12_4_ = auStack_200[3];
    auVar35 = _lqc2(auVar2);
    auVar3._4_4_ = auStack_200[5];
    auVar3._0_4_ = auStack_200[4];
    auVar3._8_4_ = auStack_200[6];
    auVar3._12_4_ = uStack_1e4;
    auVar36 = _lqc2(auVar3);
    auVar35 = _vsub(auVar35,auVar36);
    auStack_3f0 = _sqc2(auVar35);
    __ct__7FVectorFRC7FVector(auStack_320,auStack_3f0);
    uStack_20 = auStack_320._0_4_;
    uStack_1c = auStack_320._4_4_;
    uStack_18 = uStack_318;
    uStack_14 = uStack_314;
    for (iVar33 = 1; iVar33 < 8; iVar33 = iVar33 + 1) {
      iVar28 = iVar33;
      if (iVar33 < 0) {
        iVar28 = iVar33 + 7;
      }
      auVar26._4_4_ = uStack_1c;
      auVar26._0_4_ = uStack_20;
      auVar26._8_4_ = uStack_18;
      auVar26._12_4_ = uStack_14;
      auVar35 = _lqc2(auVar26);
      auVar36 = _qmtc2((float)(iVar28 >> 3));
      auVar35 = _vmulbc(auVar35,auVar36);
      auStack_4a0 = _sqc2(auVar35);
      __ct__7FVectorFRC7FVector(auStack_340,auStack_4a0);
      auVar7._4_4_ = auStack_180[5];
      auVar7._0_4_ = auStack_180[4];
      auVar7._8_4_ = auStack_180[6];
      auVar7._12_4_ = uStack_164;
      auVar35 = _lqc2(auVar7);
      auVar36 = _lqc2(auStack_340);
      auVar35 = _vadd(auVar35,auVar36);
      auStack_400 = _sqc2(auVar35);
      __ct__7FVectorFRC7FVector(auStack_330,auStack_400);
      iVar28 = param_1 + iVar33 * 0x20;
      *(int *)(iVar28 + 400) = auStack_330._0_4_;
      *(int *)(iVar28 + 0x194) = auStack_330._4_4_;
      *(undefined4 *)(iVar28 + 0x198) = uStack_328;
      *(undefined4 *)(iVar28 + 0x19c) = uStack_324;
    }
    *(undefined4 *)(param_1 + 0x280) = auStack_180[4];
    *(undefined4 *)(param_1 + 0x284) = auStack_180[5];
    *(undefined4 *)(param_1 + 0x288) = auStack_180[6];
    *(undefined4 *)(param_1 + 0x28c) = uStack_164;
    *(undefined4 *)(param_1 + 0x290) = auStack_200[4];
    *(undefined4 *)(param_1 + 0x294) = auStack_200[5];
    *(undefined4 *)(param_1 + 0x298) = auStack_200[6];
    *(undefined4 *)(param_1 + 0x29c) = uStack_1e4;
  }
  else {
    __ct__9GsxSplineFv(auStack_8);
    __ct__9GsxSplineFv(auStack_10);
    Create__9GsxSplineFUiUiP7FVector(auStack_8,*(undefined4 *)(param_1 + 0x68),0,auStack_180);
    Create__9GsxSplineFUiUiP7FVector(auStack_10,*(undefined4 *)(param_1 + 0x68),0,auStack_200);
    fVar34 = 0.0;
    for (iVar28 = 0; iVar28 < *(int *)(param_1 + 0x70); iVar28 = iVar28 + 1) {
      GetPosition__9GsxSplineFf(fVar34,auStack_350,auStack_8);
      iVar29 = param_1 + iVar28 * 0x20;
      *(int *)(iVar29 + 0x180) = auStack_350._0_4_;
      *(int *)(iVar29 + 0x184) = auStack_350._4_4_;
      *(undefined4 *)(iVar29 + 0x188) = uStack_348;
      *(undefined4 *)(iVar29 + 0x18c) = uStack_344;
      GetPosition__9GsxSplineFf(fVar34,auStack_360,auStack_10);
      iVar29 = param_1 + iVar28 * 0x20;
      *(int *)(iVar29 + 400) = auStack_360._0_4_;
      *(int *)(iVar29 + 0x194) = auStack_360._4_4_;
      *(undefined4 *)(iVar29 + 0x198) = uStack_358;
      *(undefined4 *)(iVar29 + 0x19c) = uStack_354;
      fVar34 = fVar34 + 1.0 / (float)(iVar33 + -1);
      if (1.0 < fVar34) {
        fVar34 = 1.0;
      }
    }
    Release__9GsxSplineFv(auStack_8);
    Release__9GsxSplineFv(auStack_10);
    __dt__9GsxSplineFv(auStack_10,0xffffffffffffffff);
    __dt__9GsxSplineFv(auStack_8,0xffffffffffffffff);
  }
  return 0;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00513100  MakePacket__17SwordLocusEffect3Fv
 * C++: SwordLocusEffect3::MakePacket()
 * size: 0xd44 bytes
 * --------------------------------------------------------------------------- */
/* WARNING: Removing unreachable block (ram,0x005132b8) */
/* WARNING: Removing unreachable block (ram,0x0051342c) */
/* WARNING: Removing unreachable block (ram,0x00513358) */

void MakePacket__17SwordLocusEffect3Fv(int param_1)

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
  undefined8 uVar8;
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  ulong *puVar9;
  uint uVar10;
  int iVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  undefined1 auVar16 [16];
  undefined1 auStack_14e0 [16];
  undefined1 auStack_14d0 [16];
  undefined1 auStack_14c0 [8];
  undefined4 uStack_14b8;
  undefined4 uStack_14b4;
  undefined1 auStack_14b0 [8];
  undefined4 uStack_14a8;
  undefined4 uStack_14a4;
  int aiStack_14a0 [6];
  int iStack_1488;
  int iStack_1484;
  int aiStack_1480 [504];
  undefined4 auStack_ca0 [512];
  undefined4 auStack_4a0 [16];
  undefined4 auStack_460 [16];
  undefined4 uStack_420;
  undefined4 uStack_41c;
  undefined4 uStack_418;
  undefined4 uStack_414;
  float afStack_410 [64];
  float afStack_310 [64];
  float afStack_210 [64];
  float afStack_110 [65];
  float fStack_c;
  float fStack_8;
  float fStack_4;
  
  fVar14 = 0.0;
  fVar15 = 0.0;
  uStack_420 = in_zero_lo;
  uStack_41c = in_zero_hi;
  uStack_418 = in_zero_udw;
  uStack_414 = in_register_0000000c;
  for (iVar11 = 0; iVar11 < *(int *)(param_1 + 0x70) + -1; iVar11 = iVar11 + 1) {
    auVar7 = _lqc2(*(undefined1 (*) [16])(param_1 + (iVar11 + 1) * 0x20 + 0x180));
    auVar16 = _lqc2(*(undefined1 (*) [16])(param_1 + iVar11 * 0x20 + 0x180));
    auVar7 = _vsub(auVar7,auVar16);
    auStack_14d0 = _sqc2(auVar7);
    __ct__7FVectorFRC7FVector(auStack_14b0,auStack_14d0);
    uStack_420 = auStack_14b0._0_4_;
    uStack_41c = auStack_14b0._4_4_;
    uStack_418 = uStack_14a8;
    uStack_414 = uStack_14a4;
    fVar12 = (float)Length__7FVectorCFv(&uStack_420);
    afStack_110[iVar11] = fVar12;
    fVar14 = fVar14 + afStack_110[iVar11];
    auVar7 = _lqc2(*(undefined1 (*) [16])(param_1 + (iVar11 + 1) * 0x20 + 400));
    auVar16 = _lqc2(*(undefined1 (*) [16])(param_1 + iVar11 * 0x20 + 400));
    auVar7 = _vsub(auVar7,auVar16);
    auStack_14e0 = _sqc2(auVar7);
    __ct__7FVectorFRC7FVector(auStack_14c0,auStack_14e0);
    uStack_420 = auStack_14c0._0_4_;
    uStack_41c = auStack_14c0._4_4_;
    uStack_418 = uStack_14b8;
    uStack_414 = uStack_14b4;
    fVar12 = (float)Length__7FVectorCFv(&uStack_420);
    afStack_210[iVar11] = fVar12;
    fVar15 = fVar15 + afStack_210[iVar11];
  }
  afStack_310[0] = 0.0;
  afStack_410[0] = 0.0;
  fVar12 = 0.0;
  fVar13 = 0.0;
  for (iVar11 = 0; iVar11 < *(int *)(param_1 + 0x70) + -1; iVar11 = iVar11 + 1) {
    fVar12 = fVar12 + afStack_110[iVar11];
    afStack_310[iVar11 + 1] =
         ((float)*(ushort *)(*(int *)(iGpffff86b4 + 0x4254) + 2) * (fVar12 / fVar14)) /
         (float)(1 << (uint)(((ulong)*(byte *)(*(int *)(iGpffff86b4 + 0x4254) + 0x53) << 0x3a) >>
                            0x3c));
    fVar13 = fVar13 + afStack_210[iVar11];
    afStack_410[iVar11 + 1] =
         ((float)*(ushort *)(*(int *)(iGpffff86b4 + 0x4254) + 2) * (fVar13 / fVar15)) /
         (float)(1 << (uint)(((ulong)*(byte *)(*(int *)(iGpffff86b4 + 0x4254) + 0x53) << 0x3a) >>
                            0x3c));
  }
  fVar14 = (float)*(ushort *)(*(int *)(iGpffff86b4 + 0x4254) + 4) /
           (float)(1 << (uint)((ulong)(*(long *)(*(int *)(iGpffff86b4 + 0x4254) + 0x50) << 0x1e) >>
                              0x3c));
  GetViewScreenMatrix__9GsxCameraFv(auStack_460,uGpffff8598);
  for (iVar11 = 0; iVar11 < 4; iVar11 = iVar11 + 1) {
    auStack_4a0[iVar11 * 4] = auStack_460[iVar11 * 4];
    auStack_4a0[iVar11 * 4 + 1] = auStack_460[iVar11 * 4 + 1];
    auStack_4a0[iVar11 * 4 + 2] = auStack_460[iVar11 * 4 + 2];
    auStack_4a0[iVar11 * 4 + 3] = auStack_460[iVar11 * 4 + 3];
  }
  for (iVar11 = 0; iVar11 < *(int *)(param_1 + 0x70); iVar11 = iVar11 + 1) {
    auStack_ca0[iVar11 * 8] = *(undefined4 *)(param_1 + iVar11 * 0x20 + 0x180);
    auStack_ca0[iVar11 * 8 + 1] = *(undefined4 *)(param_1 + iVar11 * 0x20 + 0x184);
    auStack_ca0[iVar11 * 8 + 2] = *(undefined4 *)(param_1 + iVar11 * 0x20 + 0x188);
    auStack_ca0[iVar11 * 8 + 3] = 0x3f800000;
    auStack_ca0[(iVar11 * 2 + 1) * 4] = *(undefined4 *)(param_1 + iVar11 * 0x20 + 400);
    auStack_ca0[(iVar11 * 2 + 1) * 4 + 1] = *(undefined4 *)(param_1 + iVar11 * 0x20 + 0x194);
    auStack_ca0[(iVar11 * 2 + 1) * 4 + 2] = *(undefined4 *)(param_1 + iVar11 * 0x20 + 0x198);
    auStack_ca0[(iVar11 * 2 + 1) * 4 + 3] = 0x3f800000;
  }
  auVar7._0_8_ = (long)(int)auStack_4a0;
  auVar7._8_8_ = in_a1_udw;
  sceVu0RotTransPersN(aiStack_14a0,auVar7._0_8_,auStack_ca0,*(int *)(param_1 + 0x70) << 1,0);
  bVar3 = false;
  for (iVar11 = 0; iVar11 < *(int *)(param_1 + 0x70) << 1; iVar11 = iVar11 + 1) {
    if ((((aiStack_14a0[iVar11 * 4] < 0) || (0x10000 < aiStack_14a0[iVar11 * 4])) ||
        (aiStack_14a0[iVar11 * 4 + 1] < 0)) ||
       ((0x10000 < aiStack_14a0[iVar11 * 4 + 1] || (aiStack_14a0[iVar11 * 4 + 2] < 0)))) {
      bVar3 = true;
    }
    aiStack_14a0[iVar11 * 4 + 2] = (int)((float)aiStack_14a0[iVar11 * 4 + 2] / 16.0);
  }
  if (*(int *)(param_1 + 0x70) < 2) {
    bVar3 = true;
  }
  bVar1 = (*(byte *)(param_1 + 0x40) & 1) == 0;
  uVar10 = (uint)bVar1;
  iVar11 = *(int *)(param_1 + 0x70) * 3;
  if (*(int *)(param_1 + uVar10 * 4 + 0x980) != iVar11 + 0xd) {
    __dla__FPv(*(undefined4 *)(param_1 + uVar10 * 4 + 0x18));
    *(undefined4 *)(param_1 + uVar10 * 4 + 0x18) = 0;
    *(undefined4 *)(param_1 + uVar10 * 4 + 0x980) = 0;
  }
  uVar8 = auVar7._8_8_;
  if (*(int *)(param_1 + uVar10 * 4 + 0x18) == 0) {
    uVar4 = __nwa__FUi((iVar11 + 0xd) * 0x10);
    uVar8 = auVar7._8_8_;
    *(undefined4 *)(param_1 + uVar10 * 4 + 0x18) = uVar4;
    *(int *)(param_1 + uVar10 * 4 + 0x980) = iVar11 + 0xd;
  }
  puVar2 = *(undefined4 **)(param_1 + uVar10 * 4 + 0x18);
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
    puVar2[4] = iVar11 + 0x1000000a;
    puVar2[5] = 0;
    puVar2[6] = 0;
    puVar2[7] = iVar11 + 0x5000000a;
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
    auVar6._8_8_ = uVar8;
    auVar6._0_8_ = 0x8400000000000001;
    auVar16._4_4_ = in_zero_hi;
    auVar16._0_4_ = in_zero_lo;
    auVar16._8_4_ = in_zero_udw;
    auVar16._12_4_ = in_register_0000000c;
    auVar7 = _pcpyld(auVar16,auVar6);
    *(long *)(puVar2 + 0x24) = auVar7._0_8_;
    *(undefined8 *)(puVar2 + 0x26) = 0xc12c12f0;
    *(undefined8 *)(puVar2 + 0x28) = 0x5c;
    *(undefined8 *)(puVar2 + 0x2a) = 0;
    *(ulong *)(puVar2 + 0x2c) = (ulong)(uint)(afStack_310[0] * (16.0 / (float)aiStack_14a0[3]));
    *(ulong *)(puVar2 + 0x2e) = (ulong)(uint)(16.0 / (float)aiStack_14a0[3]) << 0x20 | 0x30808080;
    *(long *)(puVar2 + 0x30) =
         (long)aiStack_14a0[2] << 0x20 | (long)aiStack_14a0[0] | (long)aiStack_14a0[1] << 0x10;
    fVar15 = 16.0 / (float)iStack_1484;
    fStack_8 = afStack_410[0] * fVar15;
    fStack_c = fVar14 * fVar15;
    *(ulong *)(puVar2 + 0x32) = CONCAT44(fStack_c,afStack_410[0] * fVar15);
    *(ulong *)(puVar2 + 0x34) = (ulong)(uint)fVar15 << 0x20 | 0x30808080;
    *(long *)(puVar2 + 0x36) =
         (long)iStack_1488 << 0x20 | (long)aiStack_14a0[4] | (long)aiStack_14a0[5] << 0x10;
    *(ulong *)(puVar2 + 0x38) = (long)(*(int *)(param_1 + 0x70) + -1) | 0x6400000000008000;
    *(undefined8 *)(puVar2 + 0x3a) = 0x412412;
    puVar9 = (ulong *)(puVar2 + 0x3c);
    for (iVar11 = 1; iVar11 < *(int *)(param_1 + 0x70); iVar11 = iVar11 + 1) {
      fStack_4 = 16.0 / (float)aiStack_14a0[iVar11 * 8 + 3];
      fStack_8 = fStack_4 * afStack_310[iVar11];
      fStack_c = 0.0;
      *puVar9 = (ulong)(uint)(fStack_4 * afStack_310[iVar11]);
      if (iVar11 == *(int *)(param_1 + 0x70) + -1) {
        puVar9[1] = (ulong)(uint)fStack_4 << 0x20 | 0x808080;
      }
      else {
        puVar9[1] = (ulong)(uint)fStack_4 << 0x20 | 0x30808080;
      }
      puVar9[2] = (long)aiStack_14a0[iVar11 * 8 + 2] << 0x20 |
                  (long)aiStack_14a0[iVar11 * 8] | (long)aiStack_14a0[iVar11 * 8 + 1] << 0x10;
      fStack_4 = 16.0 / (float)aiStack_14a0[(iVar11 * 2 + 1) * 4 + 3];
      fStack_8 = fStack_4 * afStack_410[iVar11];
      fStack_c = fVar14 * fStack_4;
      puVar9[3] = CONCAT44(fStack_c,fStack_4 * afStack_410[iVar11]);
      if (iVar11 == *(int *)(param_1 + 0x70) + -1) {
        puVar9[4] = (ulong)(uint)fStack_4 << 0x20 | 0x808080;
      }
      else {
        puVar9[4] = (ulong)(uint)fStack_4 << 0x20 | 0x30808080;
      }
      puVar9[5] = (long)aiStack_14a0[(iVar11 * 2 + 1) * 4 + 2] << 0x20 |
                  (long)aiStack_14a0[(iVar11 * 2 + 1) * 4] |
                  (long)aiStack_14a0[(iVar11 * 2 + 1) * 4 + 1] << 0x10;
      puVar9 = puVar9 + 6;
    }
    *(ulong **)(param_1 + 0x54) = puVar9;
    *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfe | bVar1;
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00513e50  EndSet__17SwordLocusEffect3Fv
 * C++: SwordLocusEffect3::EndSet()
 * size: 0x64 bytes
 * --------------------------------------------------------------------------- */
void EndSet__17SwordLocusEffect3Fv(int param_1)

{
  if ((*(int *)(param_1 + 0x5c) == 0) && (*(int *)(param_1 + 0x998) == 0)) {
    *(undefined4 *)(param_1 + 0x5c) = 1;
    *(undefined4 *)(param_1 + 0x60) = 0;
    *(undefined4 *)(param_1 + 100) = *(undefined4 *)(param_1 + 0x70);
    *(undefined4 *)(param_1 + 0x988) = 0;
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00513ec0  ForceEndSet__17SwordLocusEffect3Fv
 * C++: SwordLocusEffect3::ForceEndSet()
 * size: 0x54 bytes
 * --------------------------------------------------------------------------- */
void ForceEndSet__17SwordLocusEffect3Fv(int param_1)

{
  if (*(int *)(param_1 + 0x5c) == 0) {
    *(undefined4 *)(param_1 + 0x5c) = 1;
    *(undefined4 *)(param_1 + 0x60) = 0;
    *(undefined4 *)(param_1 + 100) = *(undefined4 *)(param_1 + 0x70);
    *(undefined4 *)(param_1 + 0x988) = 0;
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b610  @24@__dt__17SwordLocusEffect3Fv
 * C++: @24@__dt__17SwordLocusEffect3Fv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int * _24___dt__17SwordLocusEffect3Fv(int *param_1,short param_2)

{
  int *piVar1;
  
  piVar1 = param_1 + -6;
  if (piVar1 != (int *)0x0) {
    param_1[-1] = 0x40a120;
    param_1[4] = 0x40a130;
    param_1[7] = 0x40a140;
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
 * JP: 0x0054b620  @44@__dt__17SwordLocusEffect3Fv
 * C++: @44@__dt__17SwordLocusEffect3Fv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int _44___dt__17SwordLocusEffect3Fv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x2c;
  if (iVar1 != 0) {
    *(undefined4 *)(param_1 + -0x18) = 0x40a120;
    *(undefined4 *)(param_1 + -4) = 0x40a130;
    *(undefined4 *)(param_1 + 8) = 0x40a140;
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

