/* decomp/H/FanLocusEffect1.c — cleaned Ghidra output (SH2JP_BATTLE.BIN, JP Furokuban, base 0x00430a00).
 * 9 function(s). Types: see types.h. Names/gp globals resolved from symbols/SLPM_602.19.syms. */
#include "types.h"

/* ---------------------------------------------------------------------------
 * JP: 0x00513f20  __ct__15FanLocusEffect1Fiiii
 * C++: FanLocusEffect1::__ct(int, int, int, int)
 * size: 0x3d8 bytes
 * --------------------------------------------------------------------------- */
undefined8
__ct__15FanLocusEffect1Fiiii
          (undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined4 param_4,
          undefined4 param_5)

{
  float in_zero_lo;
  float in_zero_hi;
  float in_zero_udw;
  float in_register_0000000c;
  undefined4 uVar1;
  int iVar2;
  float *pfVar3;
  int iVar4;
  byte *pbVar5;
  undefined1 auStack_e0 [64];
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  float fStack_94;
  float fStack_90;
  float fStack_8c;
  float fStack_88;
  float fStack_84;
  undefined1 auStack_80 [16];
  float fStack_70;
  float fStack_6c;
  float fStack_68;
  float fStack_60;
  float fStack_5c;
  float fStack_58;
  float fStack_40;
  float fStack_3c;
  float fStack_38;
  float fStack_10;
  float fStack_c;
  float fStack_8;
  
  __ct__6BtlEffFii(param_1,param_2,param_3);
  iVar4 = (int)param_1;
  *(undefined4 *)(iVar4 + 0x14) = 0x40a0d0;
  *(undefined4 *)(iVar4 + 0x28) = 0x40a0e0;
  *(undefined4 *)(iVar4 + 0x34) = 0x40a0f0;
  pfVar3 = (float *)(iVar4 + 0x80);
  do {
    *pfVar3 = in_zero_lo;
    pfVar3[1] = in_zero_hi;
    pfVar3[2] = in_zero_udw;
    pfVar3[3] = in_register_0000000c;
    pfVar3 = pfVar3 + 4;
  } while (pfVar3 != (float *)(iVar4 + 0x180));
  pfVar3 = (float *)(iVar4 + 0x180);
  do {
    *pfVar3 = in_zero_lo;
    pfVar3[1] = in_zero_hi;
    pfVar3[2] = in_zero_udw;
    pfVar3[3] = in_register_0000000c;
    pfVar3 = pfVar3 + 4;
  } while (pfVar3 != (float *)(iVar4 + 0x980));
  *(undefined4 *)(iVar4 + 0x5c) = 0;
  *(undefined4 *)(iVar4 + 0x60) = 0;
  *(undefined4 *)(iVar4 + 100) = 0;
  *(undefined4 *)(iVar4 + 0x40) = 0;
  *(int *)(iVar4 + 0x44) = (int)param_2;
  *(int *)(iVar4 + 0x48) = (int)param_3;
  *(undefined4 *)(iVar4 + 0x4c) = 8;
  *(undefined4 *)(iVar4 + 0x6c) = 0;
  *(undefined4 *)(iVar4 + 0x68) = 0;
  *(undefined4 *)(iVar4 + 0x70) = 0;
  *(undefined4 *)(iVar4 + 0x1c) = 0;
  *(undefined4 *)(iVar4 + 0x18) = 0;
  *(undefined4 *)(iVar4 + 0x54) = 0;
  *(undefined4 *)(iVar4 + 0x984) = 0;
  *(undefined4 *)(iVar4 + 0x980) = 0;
  *(undefined4 *)(iVar4 + 0x98c) = param_4;
  *(undefined4 *)(iVar4 + 0x994) = param_5;
  fStack_a0 = in_zero_lo;
  fStack_9c = in_zero_hi;
  fStack_98 = in_zero_udw;
  fStack_90 = in_zero_lo;
  fStack_8c = in_zero_hi;
  fStack_88 = in_zero_udw;
  fStack_84 = in_register_0000000c;
  if (*(int *)(iVar4 + 0x98c) == 0) {
    fStack_70 = in_zero_lo;
    fStack_6c = in_zero_hi;
    fStack_68 = in_zero_udw;
    fStack_60 = in_zero_lo;
    fStack_5c = in_zero_hi;
    fStack_58 = in_zero_udw;
    fStack_40 = in_zero_lo;
    fStack_3c = in_zero_hi;
    fStack_38 = in_zero_udw;
    fStack_10 = in_zero_lo;
    fStack_c = in_zero_hi;
    fStack_8 = in_zero_udw;
    uVar1 = searchRWBBoxIndex__8BtlModelFPci
                      (*(undefined4 *)(iGpffff86b4 + *(int *)(iVar4 + 0x48) * 0x4f0 + 0x144),
                       0x652c98,0);
    *(undefined4 *)(iVar4 + 0x990) = uVar1;
    pbVar5 = (byte *)(*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar4 + 0x48) * 0x4f0 +
                                                0x144) + 0x52c) + 0xe4) +
                     *(int *)(iVar4 + 0x990) * 0x110);
    __ct__6MatrixFRC6Matrix(auStack_e0,
                    *(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar4 + 0x48) * 0x4f0 + 0x144)
                                     + 0x52c) + 0x30) + (uint)*pbVar5 * 0x1f0 +
                    (bGpffff8340 & 1) * 0x40);
    RotTransVector(auStack_80,pbVar5 + 0x10,auStack_e0,8);
    fStack_a0 = (fStack_60 + fStack_40) / 2.0;
    fStack_9c = (fStack_5c + fStack_3c) / 2.0;
    fStack_98 = (fStack_58 + fStack_38) / 2.0;
    fStack_90 = (fStack_70 + fStack_10) / 2.0;
    fStack_8c = (fStack_6c + fStack_c) / 2.0;
    fStack_88 = (fStack_68 + fStack_8) / 2.0;
    fStack_84 = 1.0;
  }
  iVar2 = iVar4 + *(int *)(iVar4 + 0x6c) * 0x20;
  *(float *)(iVar2 + 0x80) = fStack_a0;
  *(float *)(iVar2 + 0x84) = fStack_9c;
  *(float *)(iVar2 + 0x88) = fStack_98;
  *(float *)(iVar2 + 0x8c) = fStack_84;
  iVar2 = iVar4 + *(int *)(iVar4 + 0x6c) * 0x20;
  *(float *)(iVar2 + 0x90) = fStack_90;
  *(float *)(iVar2 + 0x94) = fStack_8c;
  *(float *)(iVar2 + 0x98) = fStack_88;
  *(float *)(iVar2 + 0x9c) = fStack_84;
  *(int *)(iVar4 + 0x6c) = *(int *)(iVar4 + 0x6c) + 1;
  *(int *)(iVar4 + 0x68) = *(int *)(iVar4 + 0x68) + 1;
  fStack_94 = fStack_84;
  Entry__7CPollerFP7CPolObjib(iGpffff858c + 0x48,param_1,0x80,0);
  BtlEffEntry__7CBattleFiP6BtlEff(iGpffff86b4,*(undefined4 *)(iVar4 + 0x48),param_1);
  return param_1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00514300  __dt__15FanLocusEffect1Fv
 * C++: FanLocusEffect1::__dt()
 * size: 0x154 bytes
 * --------------------------------------------------------------------------- */
int __dt__15FanLocusEffect1Fv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x14) = 0x40a0d0;
    *(undefined4 *)(param_1 + 0x28) = 0x40a0e0;
    *(undefined4 *)(param_1 + 0x34) = 0x40a0f0;
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
 * JP: 0x00514460  Destruct__15FanLocusEffect1Fv
 * C++: FanLocusEffect1::Destruct()
 * size: 0xc8 bytes
 * --------------------------------------------------------------------------- */
void Destruct__15FanLocusEffect1Fv(int param_1)

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
 * JP: 0x00514530  Polling__15FanLocusEffect1Fv
 * C++: FanLocusEffect1::Polling()
 * size: 0x910 bytes
 * --------------------------------------------------------------------------- */
undefined4 Polling__15FanLocusEffect1Fv(int param_1)

{
  undefined8 uVar1;
  undefined1 auVar2 [16];
  undefined1 auVar3 [16];
  undefined1 auVar4 [16];
  undefined1 auVar5 [16];
  undefined1 auVar6 [16];
  float in_zero_lo;
  float in_zero_hi;
  float in_zero_udw;
  undefined4 in_register_0000000c;
  byte *pbVar7;
  int iVar8;
  int iVar9;
  float fVar10;
  float fVar11;
  undefined1 (*pauVar12) [16];
  int iVar13;
  float fVar14;
  undefined1 in_vf0 [16];
  undefined1 auVar15 [16];
  undefined1 auVar16 [16];
  undefined1 auVar17 [16];
  undefined1 auStack_2e0 [16];
  undefined1 auStack_2d0 [16];
  undefined1 auStack_2c0 [16];
  undefined1 auStack_2b0 [16];
  undefined1 auStack_2a0 [16];
  undefined1 auStack_290 [16];
  undefined1 auStack_280 [8];
  undefined4 uStack_278;
  undefined4 uStack_274;
  undefined1 auStack_270 [8];
  undefined4 uStack_268;
  undefined4 uStack_264;
  undefined1 auStack_260 [16];
  undefined1 auStack_250 [8];
  undefined4 uStack_248;
  undefined4 uStack_244;
  undefined1 auStack_240 [8];
  undefined4 uStack_238;
  undefined4 uStack_234;
  undefined1 auStack_230 [16];
  undefined1 auStack_220 [8];
  undefined4 uStack_218;
  undefined4 uStack_214;
  undefined1 auStack_210 [8];
  undefined4 uStack_208;
  undefined4 uStack_204;
  float afStack_200 [7];
  undefined4 uStack_1e4;
  float afStack_180 [7];
  undefined4 uStack_164;
  undefined1 auStack_100 [16];
  undefined1 auStack_f0 [16];
  undefined1 auStack_e0 [16];
  undefined1 auStack_d0 [16];
  undefined1 auStack_c0 [16];
  float fStack_b0;
  float fStack_ac;
  float fStack_a8;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  float fStack_80;
  float fStack_7c;
  float fStack_78;
  float fStack_50;
  float fStack_4c;
  float fStack_48;
  float fStack_40;
  float fStack_3c;
  float fStack_38;
  undefined4 uStack_34;
  float fStack_30;
  float fStack_2c;
  float fStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined1 auStack_10 [8];
  undefined1 auStack_8 [8];
  
  auVar15 = _vmr32(in_vf0);
  auVar16 = _vmr32(auVar15);
  auVar17 = _vmr32(auVar16);
  auStack_d0 = _sqc2(in_vf0);
  auStack_e0 = _sqc2(auVar15);
  auStack_f0 = _sqc2(auVar16);
  auStack_100 = _sqc2(auVar17);
  fVar14 = *(float *)(iGpffff86b4 + 0x38);
  if ((*(byte *)(iGpffff86b4 + 0x24) & 1) != 0) {
    fVar14 = 0.0;
  }
  fStack_40 = in_zero_lo;
  fStack_3c = in_zero_hi;
  fStack_38 = in_zero_udw;
  fStack_30 = in_zero_lo;
  fStack_2c = in_zero_hi;
  fStack_28 = in_zero_udw;
  uStack_24 = in_register_0000000c;
  if (fVar14 != 0.0) {
    if (*(int *)(param_1 + 0x98c) == 0) {
      pbVar7 = (byte *)(*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 +
                                                  0x144) + 0x52c) + 0xe4) +
                       *(int *)(param_1 + 0x990) * 0x110);
      pauVar12 = (undefined1 (*) [16])
                 (*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x144)
                                   + 0x52c) + 0x30) + (uint)*pbVar7 * 0x1f0 +
                 (bGpffff8340 & 1) * 0x40);
      auStack_100 = *pauVar12;
      auStack_f0 = pauVar12[1];
      auStack_e0 = pauVar12[2];
      auStack_d0 = pauVar12[3];
      fStack_b0 = in_zero_lo;
      fStack_ac = in_zero_hi;
      fStack_a8 = in_zero_udw;
      fStack_a0 = in_zero_lo;
      fStack_9c = in_zero_hi;
      fStack_98 = in_zero_udw;
      fStack_80 = in_zero_lo;
      fStack_7c = in_zero_hi;
      fStack_78 = in_zero_udw;
      fStack_50 = in_zero_lo;
      fStack_4c = in_zero_hi;
      fStack_48 = in_zero_udw;
      RotTransVector(auStack_c0,pbVar7 + 0x10,auStack_100,8);
      fStack_40 = (fStack_a0 + fStack_80) / 2.0;
      fStack_3c = (fStack_9c + fStack_7c) / 2.0;
      fStack_38 = (fStack_98 + fStack_78) / 2.0;
      fStack_30 = (fStack_b0 + fStack_50) / 2.0;
      fStack_2c = (fStack_ac + fStack_4c) / 2.0;
      fStack_28 = (fStack_a8 + fStack_48) / 2.0;
      uStack_24 = 0x3f800000;
    }
    iVar13 = param_1 + *(int *)(param_1 + 0x6c) * 0x20;
    *(float *)(iVar13 + 0x80) = fStack_40;
    *(float *)(iVar13 + 0x84) = fStack_3c;
    *(float *)(iVar13 + 0x88) = fStack_38;
    *(undefined4 *)(iVar13 + 0x8c) = uStack_24;
    iVar13 = param_1 + *(int *)(param_1 + 0x6c) * 0x20;
    *(float *)(iVar13 + 0x90) = fStack_30;
    *(float *)(iVar13 + 0x94) = fStack_2c;
    *(float *)(iVar13 + 0x98) = fStack_28;
    *(undefined4 *)(iVar13 + 0x9c) = uStack_24;
    *(int *)(param_1 + 0x6c) = *(int *)(param_1 + 0x6c) + 1;
    if (7 < *(int *)(param_1 + 0x6c)) {
      *(undefined4 *)(param_1 + 0x6c) = 0;
    }
    *(int *)(param_1 + 0x68) = *(int *)(param_1 + 0x68) + 1;
    if (8 < *(int *)(param_1 + 0x68)) {
      *(undefined4 *)(param_1 + 0x68) = 8;
    }
  }
  iVar13 = *(int *)(param_1 + 0x6c);
  afStack_200[0] = in_zero_lo;
  afStack_200[1] = in_zero_hi;
  afStack_200[2] = in_zero_udw;
  afStack_200[3] = (float)in_register_0000000c;
  afStack_200[4] = in_zero_lo;
  afStack_200[5] = in_zero_hi;
  afStack_200[6] = in_zero_udw;
  uStack_1e4 = in_register_0000000c;
  afStack_180[0] = in_zero_lo;
  afStack_180[1] = in_zero_hi;
  afStack_180[2] = in_zero_udw;
  afStack_180[3] = (float)in_register_0000000c;
  afStack_180[4] = in_zero_lo;
  afStack_180[5] = in_zero_hi;
  afStack_180[6] = in_zero_udw;
  uStack_164 = in_register_0000000c;
  uStack_34 = uStack_24;
  for (iVar8 = 0; iVar8 < *(int *)(param_1 + 0x68); iVar8 = iVar8 + 1) {
    iVar13 = iVar13 + -1;
    if (iVar13 < 0) {
      iVar13 = 7;
    }
    iVar9 = param_1 + iVar13 * 0x20;
    uVar1 = *(undefined8 *)(iVar9 + 0x80);
    fVar10 = *(float *)(iVar9 + 0x88);
    fVar11 = *(float *)(iVar9 + 0x8c);
    afStack_180[iVar8 * 4] = (float)uVar1;
    afStack_180[iVar8 * 4 + 1] = (float)((ulong)uVar1 >> 0x20);
    afStack_180[iVar8 * 4 + 2] = fVar10;
    afStack_180[iVar8 * 4 + 3] = fVar11;
    iVar9 = param_1 + iVar13 * 0x20;
    uVar1 = *(undefined8 *)(iVar9 + 0x90);
    fVar10 = *(float *)(iVar9 + 0x98);
    fVar11 = *(float *)(iVar9 + 0x9c);
    afStack_200[iVar8 * 4] = (float)uVar1;
    afStack_200[iVar8 * 4 + 1] = (float)((ulong)uVar1 >> 0x20);
    afStack_200[iVar8 * 4 + 2] = fVar10;
    afStack_200[iVar8 * 4 + 3] = fVar11;
  }
  if (*(int *)(param_1 + 0x5c) == 0) {
    iVar13 = (*(int *)(param_1 + 0x68) + -1) * 8 + 1;
    *(int *)(param_1 + 0x70) = iVar13;
  }
  else {
    *(float *)(param_1 + 0x988) = *(float *)(param_1 + 0x988) + fVar14;
    while ((1 < *(int *)(param_1 + 100) && (0.004166667 < *(float *)(param_1 + 0x988)))) {
      *(float *)(param_1 + 0x988) = *(float *)(param_1 + 0x988) - 0.004166667;
      *(int *)(param_1 + 100) = *(int *)(param_1 + 100) + -1;
    }
    if (*(int *)(param_1 + 100) < 2) {
      BtlEffRelease__7CBattleFiP6BtlEff(iGpffff86b4,*(undefined4 *)(param_1 + 0x48),param_1);
      if ((long)((ulong)*(byte *)(param_1 + 0x40) << 0x3e) < 0) {
        iVar13 = param_1;
        if (param_1 != 0) {
          iVar13 = param_1 + 0x18;
        }
        ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,iVar13);
      }
      *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfd;
      (**(code **)(*(int *)(param_1 + 0x34) + 0xc))();
      return 1;
    }
    iVar13 = (*(int *)(param_1 + 0x68) + -1) * 8 + 1;
    *(undefined4 *)(param_1 + 0x70) = *(undefined4 *)(param_1 + 100);
  }
  if (*(int *)(param_1 + 0x68) == 1) {
    *(float *)(param_1 + 0x180) = afStack_180[0];
    *(float *)(param_1 + 0x184) = afStack_180[1];
    *(float *)(param_1 + 0x188) = afStack_180[2];
    *(float *)(param_1 + 0x18c) = afStack_180[3];
    *(float *)(param_1 + 400) = afStack_200[0];
    *(float *)(param_1 + 0x194) = afStack_200[1];
    *(float *)(param_1 + 0x198) = afStack_200[2];
    *(float *)(param_1 + 0x19c) = afStack_200[3];
  }
  else if (*(int *)(param_1 + 0x68) == 2) {
    *(float *)(param_1 + 0x180) = afStack_180[0];
    *(float *)(param_1 + 0x184) = afStack_180[1];
    *(float *)(param_1 + 0x188) = afStack_180[2];
    *(float *)(param_1 + 0x18c) = afStack_180[3];
    *(float *)(param_1 + 400) = afStack_200[0];
    *(float *)(param_1 + 0x194) = afStack_200[1];
    *(float *)(param_1 + 0x198) = afStack_200[2];
    *(float *)(param_1 + 0x19c) = afStack_200[3];
    auVar15._4_4_ = afStack_180[1];
    auVar15._0_4_ = afStack_180[0];
    auVar15._8_4_ = afStack_180[2];
    auVar15._12_4_ = afStack_180[3];
    auVar15 = _lqc2(auVar15);
    auVar16._4_4_ = afStack_180[5];
    auVar16._0_4_ = afStack_180[4];
    auVar16._8_4_ = afStack_180[6];
    auVar16._12_4_ = uStack_164;
    auVar16 = _lqc2(auVar16);
    auVar15 = _vsub(auVar15,auVar16);
    auStack_290 = _sqc2(auVar15);
    __ct__7FVectorFRC7FVector(auStack_210,auStack_290);
    uStack_20 = auStack_210._0_4_;
    uStack_1c = auStack_210._4_4_;
    uStack_18 = uStack_208;
    uStack_14 = uStack_204;
    for (iVar13 = 1; iVar13 < 8; iVar13 = iVar13 + 1) {
      iVar8 = iVar13;
      if (iVar13 < 0) {
        iVar8 = iVar13 + 7;
      }
      auVar5._4_4_ = uStack_1c;
      auVar5._0_4_ = uStack_20;
      auVar5._8_4_ = uStack_18;
      auVar5._12_4_ = uStack_14;
      auVar15 = _lqc2(auVar5);
      auVar16 = _qmtc2((float)(iVar8 >> 3));
      auVar15 = _vmulbc(auVar15,auVar16);
      auStack_2d0 = _sqc2(auVar15);
      __ct__7FVectorFRC7FVector(auStack_230,auStack_2d0);
      auVar17._4_4_ = afStack_180[5];
      auVar17._0_4_ = afStack_180[4];
      auVar17._8_4_ = afStack_180[6];
      auVar17._12_4_ = uStack_164;
      auVar15 = _lqc2(auVar17);
      auVar16 = _lqc2(auStack_230);
      auVar15 = _vadd(auVar15,auVar16);
      auStack_2a0 = _sqc2(auVar15);
      __ct__7FVectorFRC7FVector(auStack_220,auStack_2a0);
      iVar8 = param_1 + iVar13 * 0x20;
      *(int *)(iVar8 + 0x180) = auStack_220._0_4_;
      *(int *)(iVar8 + 0x184) = auStack_220._4_4_;
      *(undefined4 *)(iVar8 + 0x188) = uStack_218;
      *(undefined4 *)(iVar8 + 0x18c) = uStack_214;
    }
    auVar2._4_4_ = afStack_200[1];
    auVar2._0_4_ = afStack_200[0];
    auVar2._8_4_ = afStack_200[2];
    auVar2._12_4_ = afStack_200[3];
    auVar15 = _lqc2(auVar2);
    auVar3._4_4_ = afStack_200[5];
    auVar3._0_4_ = afStack_200[4];
    auVar3._8_4_ = afStack_200[6];
    auVar3._12_4_ = uStack_1e4;
    auVar16 = _lqc2(auVar3);
    auVar15 = _vsub(auVar15,auVar16);
    auStack_2b0 = _sqc2(auVar15);
    __ct__7FVectorFRC7FVector(auStack_240,auStack_2b0);
    uStack_20 = auStack_240._0_4_;
    uStack_1c = auStack_240._4_4_;
    uStack_18 = uStack_238;
    uStack_14 = uStack_234;
    for (iVar13 = 1; iVar13 < 8; iVar13 = iVar13 + 1) {
      iVar8 = iVar13;
      if (iVar13 < 0) {
        iVar8 = iVar13 + 7;
      }
      auVar6._4_4_ = uStack_1c;
      auVar6._0_4_ = uStack_20;
      auVar6._8_4_ = uStack_18;
      auVar6._12_4_ = uStack_14;
      auVar15 = _lqc2(auVar6);
      auVar16 = _qmtc2((float)(iVar8 >> 3));
      auVar15 = _vmulbc(auVar15,auVar16);
      auStack_2e0 = _sqc2(auVar15);
      __ct__7FVectorFRC7FVector(auStack_260,auStack_2e0);
      auVar4._4_4_ = afStack_180[5];
      auVar4._0_4_ = afStack_180[4];
      auVar4._8_4_ = afStack_180[6];
      auVar4._12_4_ = uStack_164;
      auVar15 = _lqc2(auVar4);
      auVar16 = _lqc2(auStack_260);
      auVar15 = _vadd(auVar15,auVar16);
      auStack_2c0 = _sqc2(auVar15);
      __ct__7FVectorFRC7FVector(auStack_250,auStack_2c0);
      iVar8 = param_1 + iVar13 * 0x20;
      *(int *)(iVar8 + 400) = auStack_250._0_4_;
      *(int *)(iVar8 + 0x194) = auStack_250._4_4_;
      *(undefined4 *)(iVar8 + 0x198) = uStack_248;
      *(undefined4 *)(iVar8 + 0x19c) = uStack_244;
    }
    *(float *)(param_1 + 0x280) = afStack_180[4];
    *(float *)(param_1 + 0x284) = afStack_180[5];
    *(float *)(param_1 + 0x288) = afStack_180[6];
    *(undefined4 *)(param_1 + 0x28c) = uStack_164;
    *(float *)(param_1 + 0x290) = afStack_200[4];
    *(float *)(param_1 + 0x294) = afStack_200[5];
    *(float *)(param_1 + 0x298) = afStack_200[6];
    *(undefined4 *)(param_1 + 0x29c) = uStack_1e4;
  }
  else {
    __ct__9GsxSplineFv(auStack_8);
    __ct__9GsxSplineFv(auStack_10);
    Create__9GsxSplineFUiUiP7FVector(auStack_8,*(undefined4 *)(param_1 + 0x68),0,afStack_180);
    Create__9GsxSplineFUiUiP7FVector(auStack_10,*(undefined4 *)(param_1 + 0x68),0,afStack_200);
    fVar14 = 0.0;
    for (iVar8 = 0; iVar8 < *(int *)(param_1 + 0x70); iVar8 = iVar8 + 1) {
      GetPosition__9GsxSplineFf(fVar14,auStack_270,auStack_8);
      iVar9 = param_1 + iVar8 * 0x20;
      *(int *)(iVar9 + 0x180) = auStack_270._0_4_;
      *(int *)(iVar9 + 0x184) = auStack_270._4_4_;
      *(undefined4 *)(iVar9 + 0x188) = uStack_268;
      *(undefined4 *)(iVar9 + 0x18c) = uStack_264;
      GetPosition__9GsxSplineFf(fVar14,auStack_280,auStack_10);
      iVar9 = param_1 + iVar8 * 0x20;
      *(int *)(iVar9 + 400) = auStack_280._0_4_;
      *(int *)(iVar9 + 0x194) = auStack_280._4_4_;
      *(undefined4 *)(iVar9 + 0x198) = uStack_278;
      *(undefined4 *)(iVar9 + 0x19c) = uStack_274;
      fVar14 = fVar14 + 1.0 / (float)(iVar13 + -1);
      if (1.0 < fVar14) {
        fVar14 = 1.0;
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
 * JP: 0x00514e40  MakePacket__15FanLocusEffect1Fv
 * C++: FanLocusEffect1::MakePacket()
 * size: 0x1024 bytes
 * --------------------------------------------------------------------------- */
/* WARNING: Removing unreachable block (ram,0x005152a0) */
/* WARNING: Removing unreachable block (ram,0x0051517c) */
/* WARNING: Removing unreachable block (ram,0x00515008) */
/* WARNING: Removing unreachable block (ram,0x00515200) */
/* WARNING: Removing unreachable block (ram,0x00515374) */
/* WARNING: Removing unreachable block (ram,0x005150a8) */

void MakePacket__15FanLocusEffect1Fv(int param_1)

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
  long lVar7;
  undefined8 in_a1_udw;
  undefined8 uVar10;
  undefined1 auVar8 [16];
  undefined1 auVar9 [16];
  ulong *puVar11;
  uint uVar12;
  int iVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  undefined1 auVar18 [16];
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
  
  fVar16 = 0.0;
  fVar17 = 0.0;
  uStack_420 = in_zero_lo;
  uStack_41c = in_zero_hi;
  uStack_418 = in_zero_udw;
  uStack_414 = in_register_0000000c;
  for (iVar13 = 0; iVar13 < *(int *)(param_1 + 0x70) + -1; iVar13 = iVar13 + 1) {
    auVar9 = _lqc2(*(undefined1 (*) [16])(param_1 + (iVar13 + 1) * 0x20 + 0x180));
    auVar18 = _lqc2(*(undefined1 (*) [16])(param_1 + iVar13 * 0x20 + 0x180));
    auVar9 = _vsub(auVar9,auVar18);
    auStack_14d0 = _sqc2(auVar9);
    __ct__7FVectorFRC7FVector(auStack_14b0,auStack_14d0);
    uStack_420 = auStack_14b0._0_4_;
    uStack_41c = auStack_14b0._4_4_;
    uStack_418 = uStack_14a8;
    uStack_414 = uStack_14a4;
    fVar14 = (float)Length__7FVectorCFv(&uStack_420);
    afStack_110[iVar13] = fVar14;
    fVar16 = fVar16 + afStack_110[iVar13];
    auVar9 = _lqc2(*(undefined1 (*) [16])(param_1 + (iVar13 + 1) * 0x20 + 400));
    auVar18 = _lqc2(*(undefined1 (*) [16])(param_1 + iVar13 * 0x20 + 400));
    auVar9 = _vsub(auVar9,auVar18);
    auStack_14e0 = _sqc2(auVar9);
    __ct__7FVectorFRC7FVector(auStack_14c0,auStack_14e0);
    uStack_420 = auStack_14c0._0_4_;
    uStack_41c = auStack_14c0._4_4_;
    uStack_418 = uStack_14b8;
    uStack_414 = uStack_14b4;
    fVar14 = (float)Length__7FVectorCFv(&uStack_420);
    afStack_210[iVar13] = fVar14;
    fVar17 = fVar17 + afStack_210[iVar13];
  }
  afStack_310[0] = 0.0;
  afStack_410[0] = 0.0;
  fVar14 = 0.0;
  fVar15 = 0.0;
  if (*(int *)(param_1 + 0x994) == 0) {
    for (iVar13 = 0; iVar13 < *(int *)(param_1 + 0x70) + -1; iVar13 = iVar13 + 1) {
      fVar14 = fVar14 + afStack_110[iVar13];
      afStack_310[iVar13 + 1] =
           ((float)*(ushort *)(*(int *)(iGpffff86b4 + 0x4254) + 2) * (fVar14 / fVar16)) /
           (float)(1 << (uint)(((ulong)*(byte *)(*(int *)(iGpffff86b4 + 0x4254) + 0x53) << 0x3a) >>
                              0x3c));
      fVar15 = fVar15 + afStack_210[iVar13];
      afStack_410[iVar13 + 1] =
           ((float)*(ushort *)(*(int *)(iGpffff86b4 + 0x4254) + 2) * (fVar15 / fVar17)) /
           (float)(1 << (uint)(((ulong)*(byte *)(*(int *)(iGpffff86b4 + 0x4254) + 0x53) << 0x3a) >>
                              0x3c));
    }
    fVar16 = (float)*(ushort *)(*(int *)(iGpffff86b4 + 0x4254) + 4) /
             (float)(1 << (uint)((ulong)(*(long *)(*(int *)(iGpffff86b4 + 0x4254) + 0x50) << 0x1e)
                                >> 0x3c));
  }
  else {
    for (iVar13 = 0; iVar13 < *(int *)(param_1 + 0x70) + -1; iVar13 = iVar13 + 1) {
      fVar14 = fVar14 + afStack_110[iVar13];
      afStack_310[iVar13 + 1] =
           ((float)*(ushort *)(*(int *)(iGpffff86b4 + 0x4300) + 2) * (fVar14 / fVar16)) /
           (float)(1 << (uint)(((ulong)*(byte *)(*(int *)(iGpffff86b4 + 0x4300) + 0x53) << 0x3a) >>
                              0x3c));
      fVar15 = fVar15 + afStack_210[iVar13];
      afStack_410[iVar13 + 1] =
           ((float)*(ushort *)(*(int *)(iGpffff86b4 + 0x4300) + 2) * (fVar15 / fVar17)) /
           (float)(1 << (uint)(((ulong)*(byte *)(*(int *)(iGpffff86b4 + 0x4300) + 0x53) << 0x3a) >>
                              0x3c));
    }
    fVar16 = (float)*(ushort *)(*(int *)(iGpffff86b4 + 0x4300) + 4) /
             (float)(1 << (uint)((ulong)(*(long *)(*(int *)(iGpffff86b4 + 0x4300) + 0x50) << 0x1e)
                                >> 0x3c));
  }
  GetViewScreenMatrix__9GsxCameraFv(auStack_460,uGpffff8598);
  for (iVar13 = 0; iVar13 < 4; iVar13 = iVar13 + 1) {
    auStack_4a0[iVar13 * 4] = auStack_460[iVar13 * 4];
    auStack_4a0[iVar13 * 4 + 1] = auStack_460[iVar13 * 4 + 1];
    auStack_4a0[iVar13 * 4 + 2] = auStack_460[iVar13 * 4 + 2];
    auStack_4a0[iVar13 * 4 + 3] = auStack_460[iVar13 * 4 + 3];
  }
  for (iVar13 = 0; iVar13 < *(int *)(param_1 + 0x70); iVar13 = iVar13 + 1) {
    auStack_ca0[iVar13 * 8] = *(undefined4 *)(param_1 + iVar13 * 0x20 + 0x180);
    auStack_ca0[iVar13 * 8 + 1] = *(undefined4 *)(param_1 + iVar13 * 0x20 + 0x184);
    auStack_ca0[iVar13 * 8 + 2] = *(undefined4 *)(param_1 + iVar13 * 0x20 + 0x188);
    auStack_ca0[iVar13 * 8 + 3] = 0x3f800000;
    auStack_ca0[(iVar13 * 2 + 1) * 4] = *(undefined4 *)(param_1 + iVar13 * 0x20 + 400);
    auStack_ca0[(iVar13 * 2 + 1) * 4 + 1] = *(undefined4 *)(param_1 + iVar13 * 0x20 + 0x194);
    auStack_ca0[(iVar13 * 2 + 1) * 4 + 2] = *(undefined4 *)(param_1 + iVar13 * 0x20 + 0x198);
    auStack_ca0[(iVar13 * 2 + 1) * 4 + 3] = 0x3f800000;
  }
  auVar9._0_8_ = (long)(int)auStack_4a0;
  auVar9._8_8_ = in_a1_udw;
  sceVu0RotTransPersN(aiStack_14a0,auVar9._0_8_,auStack_ca0,*(int *)(param_1 + 0x70) << 1,0);
  bVar3 = false;
  for (iVar13 = 0; iVar13 < *(int *)(param_1 + 0x70) << 1; iVar13 = iVar13 + 1) {
    if ((((aiStack_14a0[iVar13 * 4] < 0) || (0x10000 < aiStack_14a0[iVar13 * 4])) ||
        (aiStack_14a0[iVar13 * 4 + 1] < 0)) ||
       ((0x10000 < aiStack_14a0[iVar13 * 4 + 1] || (aiStack_14a0[iVar13 * 4 + 2] < 0)))) {
      bVar3 = true;
    }
    aiStack_14a0[iVar13 * 4 + 2] = (int)((float)aiStack_14a0[iVar13 * 4 + 2] / 16.0);
  }
  if (*(int *)(param_1 + 0x70) < 2) {
    bVar3 = true;
  }
  bVar1 = (*(byte *)(param_1 + 0x40) & 1) == 0;
  uVar12 = (uint)bVar1;
  iVar13 = *(int *)(param_1 + 0x70) * 3;
  if (*(int *)(param_1 + uVar12 * 4 + 0x980) != iVar13 + 0xd) {
    __dla__FPv(*(undefined4 *)(param_1 + uVar12 * 4 + 0x18));
    *(undefined4 *)(param_1 + uVar12 * 4 + 0x18) = 0;
    *(undefined4 *)(param_1 + uVar12 * 4 + 0x980) = 0;
  }
  uVar10 = auVar9._8_8_;
  if (*(int *)(param_1 + uVar12 * 4 + 0x18) == 0) {
    uVar4 = __nwa__FUi((iVar13 + 0xd) * 0x10);
    uVar10 = auVar9._8_8_;
    *(undefined4 *)(param_1 + uVar12 * 4 + 0x18) = uVar4;
    *(int *)(param_1 + uVar12 * 4 + 0x980) = iVar13 + 0xd;
  }
  puVar2 = *(undefined4 **)(param_1 + uVar12 * 4 + 0x18);
  if (bVar3) {
    *(undefined4 **)(param_1 + 0x54) = puVar2;
    *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfe | bVar1;
  }
  else {
    if (*(int *)(param_1 + 0x994) != 0) {
      ChangeClut__6JRCTexFUs(*(undefined4 *)(iGpffff86b4 + 0x4300),*(int *)(param_1 + 0x994) - 1U & 0xffff)
      ;
    }
    *puVar2 = 0x50000000;
    if (*(int *)(param_1 + 0x994) == 0) {
      puVar2[1] = *(undefined4 *)
                   (*(int *)(iGpffff86b4 + 0x4254) +
                    (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x4254) + 10) * 4 + 0xc);
    }
    else {
      puVar2[1] = *(undefined4 *)
                   (*(int *)(iGpffff86b4 + 0x4300) +
                    (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x4300) + 10) * 4 + 0xc);
    }
    puVar2[2] = 0;
    puVar2[3] = 0;
    puVar2[4] = iVar13 + 0x1000000a;
    puVar2[5] = 0;
    puVar2[6] = 0;
    puVar2[7] = iVar13 + 0x5000000a;
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
    if (*(int *)(param_1 + 0x994) == 0) {
      uVar5 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x4254),1);
      *(undefined8 *)(puVar2 + 0x1c) = uVar5;
    }
    else {
      uVar5 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x4300),1);
      *(undefined8 *)(puVar2 + 0x1c) = uVar5;
    }
    *(undefined8 *)(puVar2 + 0x1e) = 0;
    if (*(int *)(param_1 + 0x994) == 6) {
      *(undefined8 *)(puVar2 + 0x20) = 0x44;
    }
    else {
      *(undefined8 *)(puVar2 + 0x20) = 0x48;
    }
    *(undefined8 *)(puVar2 + 0x22) = 0x42;
    if (*(int *)(param_1 + 0x994) == 0) {
      lVar6 = 0;
      lVar7 = 0x30;
    }
    else {
      lVar6 = 0x80;
      lVar7 = lVar6;
    }
    auVar8._8_8_ = uVar10;
    auVar8._0_8_ = 0x8400000000000001;
    auVar18._4_4_ = in_zero_hi;
    auVar18._0_4_ = in_zero_lo;
    auVar18._8_4_ = in_zero_udw;
    auVar18._12_4_ = in_register_0000000c;
    auVar9 = _pcpyld(auVar18,auVar8);
    *(long *)(puVar2 + 0x24) = auVar9._0_8_;
    *(undefined8 *)(puVar2 + 0x26) = 0xc12c12f0;
    *(undefined8 *)(puVar2 + 0x28) = 0x5c;
    *(undefined8 *)(puVar2 + 0x2a) = 0;
    *(ulong *)(puVar2 + 0x2c) = (ulong)(uint)(afStack_310[0] * (16.0 / (float)aiStack_14a0[3]));
    *(ulong *)(puVar2 + 0x2e) =
         lVar7 << 0x18 | 0x808080U | (ulong)(uint)(16.0 / (float)aiStack_14a0[3]) << 0x20;
    *(long *)(puVar2 + 0x30) =
         (long)aiStack_14a0[2] << 0x20 | (long)aiStack_14a0[0] | (long)aiStack_14a0[1] << 0x10;
    fVar17 = 16.0 / (float)iStack_1484;
    fStack_8 = afStack_410[0] * fVar17;
    fStack_c = fVar16 * fVar17;
    *(ulong *)(puVar2 + 0x32) = CONCAT44(fVar16 * fVar17,afStack_410[0] * fVar17);
    *(ulong *)(puVar2 + 0x34) = lVar7 << 0x18 | 0x808080U | (ulong)(uint)fVar17 << 0x20;
    *(long *)(puVar2 + 0x36) =
         (long)iStack_1488 << 0x20 | (long)aiStack_14a0[4] | (long)aiStack_14a0[5] << 0x10;
    *(ulong *)(puVar2 + 0x38) = (long)(*(int *)(param_1 + 0x70) + -1) | 0x6400000000008000;
    *(undefined8 *)(puVar2 + 0x3a) = 0x412412;
    puVar11 = (ulong *)(puVar2 + 0x3c);
    for (iVar13 = 1; iVar13 < *(int *)(param_1 + 0x70); iVar13 = iVar13 + 1) {
      fStack_4 = 16.0 / (float)aiStack_14a0[iVar13 * 8 + 3];
      fStack_8 = fStack_4 * afStack_310[iVar13];
      fStack_c = 0.0;
      *puVar11 = (ulong)(uint)(fStack_4 * afStack_310[iVar13]);
      if (iVar13 == *(int *)(param_1 + 0x70) + -1) {
        puVar11[1] = lVar6 << 0x18 | 0x808080U | (ulong)(uint)fStack_4 << 0x20;
      }
      else {
        puVar11[1] = lVar7 << 0x18 | 0x808080U | (ulong)(uint)fStack_4 << 0x20;
      }
      puVar11[2] = (long)aiStack_14a0[iVar13 * 8 + 2] << 0x20 |
                   (long)aiStack_14a0[iVar13 * 8] | (long)aiStack_14a0[iVar13 * 8 + 1] << 0x10;
      fStack_4 = 16.0 / (float)aiStack_14a0[(iVar13 * 2 + 1) * 4 + 3];
      fStack_8 = fStack_4 * afStack_410[iVar13];
      fStack_c = fVar16 * fStack_4;
      puVar11[3] = CONCAT44(fVar16 * fStack_4,fStack_4 * afStack_410[iVar13]);
      if (iVar13 == *(int *)(param_1 + 0x70) + -1) {
        puVar11[4] = lVar6 << 0x18 | 0x808080U | (ulong)(uint)fStack_4 << 0x20;
      }
      else {
        puVar11[4] = lVar7 << 0x18 | 0x808080U | (ulong)(uint)fStack_4 << 0x20;
      }
      puVar11[5] = (long)aiStack_14a0[(iVar13 * 2 + 1) * 4 + 2] << 0x20 |
                   (long)aiStack_14a0[(iVar13 * 2 + 1) * 4] |
                   (long)aiStack_14a0[(iVar13 * 2 + 1) * 4 + 1] << 0x10;
      puVar11 = puVar11 + 6;
    }
    *(ulong **)(param_1 + 0x54) = puVar11;
    *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfe | bVar1;
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00515e70  EndSet__15FanLocusEffect1Fv
 * C++: FanLocusEffect1::EndSet()
 * size: 0x10 bytes
 * --------------------------------------------------------------------------- */
void EndSet__15FanLocusEffect1Fv(void)

{
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00515e80  ForceEndSet__15FanLocusEffect1Fv
 * C++: FanLocusEffect1::ForceEndSet()
 * size: 0x54 bytes
 * --------------------------------------------------------------------------- */
void ForceEndSet__15FanLocusEffect1Fv(int param_1)

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
 * JP: 0x0054b630  @24@__dt__15FanLocusEffect1Fv
 * C++: @24@__dt__15FanLocusEffect1Fv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int * _24___dt__15FanLocusEffect1Fv(int *param_1,short param_2)

{
  int *piVar1;
  
  piVar1 = param_1 + -6;
  if (piVar1 != (int *)0x0) {
    param_1[-1] = 0x40a0d0;
    param_1[4] = 0x40a0e0;
    param_1[7] = 0x40a0f0;
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
 * JP: 0x0054b640  @44@__dt__15FanLocusEffect1Fv
 * C++: @44@__dt__15FanLocusEffect1Fv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int _44___dt__15FanLocusEffect1Fv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x2c;
  if (iVar1 != 0) {
    *(undefined4 *)(param_1 + -0x18) = 0x40a0d0;
    *(undefined4 *)(param_1 + -4) = 0x40a0e0;
    *(undefined4 *)(param_1 + 8) = 0x40a0f0;
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

