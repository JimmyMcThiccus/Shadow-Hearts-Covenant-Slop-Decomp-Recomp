/* decomp/H/DownSmoke.c — cleaned Ghidra output (SH2JP_BATTLE.BIN, JP Furokuban, base 0x00430a00).
 * 10 function(s). Types: see types.h. Names/gp globals resolved from symbols/SLPM_602.19.syms. */
#include "types.h"

/* ---------------------------------------------------------------------------
 * JP: 0x0050a8a0  __ct__9DownSmokeFiiii
 * C++: DownSmoke::__ct(int, int, int, int)
 * size: 0xd74 bytes
 * --------------------------------------------------------------------------- */
undefined8
__ct__9DownSmokeFiiii
          (undefined8 param_1,undefined8 param_2,undefined8 param_3,int param_4,ulong param_5)

{
  undefined1 auVar1 [16];
  undefined1 auVar2 [16];
  undefined1 auVar3 [16];
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  int iVar4;
  ulong uVar5;
  int iVar6;
  undefined1 in_vf0 [16];
  undefined1 auVar7 [16];
  undefined1 auVar8 [16];
  undefined4 uVar9;
  undefined1 auStack_330 [16];
  undefined1 auStack_320 [16];
  undefined1 auStack_310 [16];
  undefined1 auStack_300 [16];
  undefined1 auStack_2f0 [16];
  undefined1 auStack_2e0 [16];
  undefined1 auStack_2d0 [16];
  undefined1 auStack_2c0 [16];
  undefined1 auStack_2b0 [16];
  undefined1 auStack_2a0 [16];
  undefined1 auStack_290 [16];
  undefined1 auStack_280 [16];
  undefined1 auStack_270 [16];
  undefined1 auStack_260 [16];
  undefined1 auStack_250 [16];
  undefined1 auStack_240 [8];
  undefined4 uStack_238;
  undefined4 uStack_234;
  undefined1 auStack_230 [16];
  undefined1 auStack_220 [4];
  undefined4 uStack_21c;
  undefined4 uStack_218;
  undefined4 uStack_214;
  float fStack_210;
  float fStack_20c;
  float fStack_208;
  undefined4 uStack_204;
  undefined1 auStack_200 [8];
  undefined4 uStack_1f8;
  undefined4 uStack_1f4;
  undefined1 auStack_1f0 [16];
  undefined1 auStack_1e0 [4];
  undefined4 uStack_1dc;
  undefined4 uStack_1d8;
  undefined4 uStack_1d4;
  float fStack_1d0;
  float fStack_1cc;
  float fStack_1c8;
  undefined4 uStack_1c4;
  undefined1 auStack_1c0 [8];
  undefined4 uStack_1b8;
  undefined4 uStack_1b4;
  undefined1 auStack_1b0 [16];
  undefined1 auStack_1a0 [12];
  undefined4 uStack_194;
  float fStack_190;
  float fStack_18c;
  float fStack_188;
  undefined4 uStack_184;
  undefined1 auStack_180 [8];
  undefined4 uStack_178;
  undefined4 uStack_174;
  undefined1 auStack_170 [16];
  undefined1 auStack_160 [12];
  undefined4 uStack_154;
  float fStack_150;
  float fStack_14c;
  float fStack_148;
  undefined4 uStack_144;
  undefined1 auStack_140 [8];
  undefined4 uStack_138;
  undefined4 uStack_134;
  undefined1 auStack_130 [16];
  undefined4 auStack_120 [2];
  undefined4 uStack_118;
  undefined4 uStack_114;
  float fStack_110;
  undefined4 uStack_10c;
  float fStack_108;
  undefined4 uStack_104;
  undefined4 uStack_100;
  undefined4 uStack_fc;
  undefined4 uStack_f8;
  undefined4 uStack_f4;
  float fStack_f0;
  float fStack_ec;
  float fStack_e8;
  undefined4 uStack_e4;
  float fStack_e0;
  float fStack_dc;
  float fStack_d8;
  undefined4 uStack_d4;
  float afStack_d0 [36];
  undefined1 auStack_40 [64];
  
  __ct__6BtlEffFii(param_1,param_2,param_3);
  iVar6 = (int)param_1;
  *(undefined4 *)(iVar6 + 0x14) = 0x40a210;
  *(undefined4 *)(iVar6 + 0x28) = 0x40a220;
  *(undefined4 *)(iVar6 + 0x34) = 0x40a230;
  *(undefined4 *)(iVar6 + 0x70) = in_zero_lo;
  *(undefined4 *)(iVar6 + 0x74) = in_zero_hi;
  *(undefined4 *)(iVar6 + 0x78) = in_zero_udw;
  *(undefined4 *)(iVar6 + 0x7c) = in_register_0000000c;
  *(undefined4 *)(iVar6 + 0x80) = in_zero_lo;
  *(undefined4 *)(iVar6 + 0x84) = in_zero_hi;
  *(undefined4 *)(iVar6 + 0x88) = in_zero_udw;
  *(undefined4 *)(iVar6 + 0x8c) = in_register_0000000c;
  *(undefined4 *)(iVar6 + 0x5c) = 0;
  *(undefined4 *)(iVar6 + 0x60) = 0;
  *(undefined4 *)(iVar6 + 100) = 0;
  *(undefined4 *)(iVar6 + 0x40) = 0;
  *(int *)(iVar6 + 0x44) = (int)param_2;
  *(int *)(iVar6 + 0x48) = (int)param_3;
  *(undefined4 *)(iVar6 + 0x4c) = 0;
  uStack_100 = 0;
  uStack_fc = 0;
  uStack_f8 = 0;
  uStack_f4 = 0x3f800000;
  *(undefined4 *)(iVar6 + 0x80) = 0;
  *(undefined4 *)(iVar6 + 0x84) = 0;
  *(undefined4 *)(iVar6 + 0x88) = 0;
  *(undefined4 *)(iVar6 + 0x8c) = 0x3f800000;
  __ct__6MatrixFRC6Matrix(auStack_40,
                  *(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar6 + 0x48) * 0x4f0 + 0x144) + 0x30) +
                  (uint)*(byte *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar6 + 0x48) * 0x4f0 +
                                                   0x144) + 0xe4) + param_4 * 0x110) * 0x1f0 +
                  (bGpffff8340 & 1) * 0x40);
  fStack_e0 = 4096.0;
  fStack_dc = 4096.0;
  fStack_d8 = 4096.0;
  uStack_d4 = 0;
  fStack_f0 = -4096.0;
  fStack_ec = -4096.0;
  fStack_e8 = -4096.0;
  uStack_e4 = 0;
  afStack_d0[0x20] = (float)in_zero_lo;
  afStack_d0[0x21] = (float)in_zero_hi;
  afStack_d0[0x22] = (float)in_zero_udw;
  afStack_d0[0x23] = (float)in_register_0000000c;
  RotTransVector(afStack_d0,
                  *(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar6 + 0x48) * 0x4f0 + 0x144) + 0xe4) +
                  param_4 * 0x110 + 0x10,auStack_40,8);
  for (iVar4 = 0; iVar4 < 8; iVar4 = iVar4 + 1) {
    if (afStack_d0[iVar4 * 4] < fStack_e0) {
      fStack_e0 = afStack_d0[iVar4 * 4];
    }
    if (afStack_d0[iVar4 * 4 + 1] < fStack_dc) {
      fStack_dc = afStack_d0[iVar4 * 4 + 1];
    }
    if (afStack_d0[iVar4 * 4 + 2] < fStack_d8) {
      fStack_d8 = afStack_d0[iVar4 * 4 + 2];
    }
    if (fStack_f0 < afStack_d0[iVar4 * 4]) {
      fStack_f0 = afStack_d0[iVar4 * 4];
    }
    if (fStack_ec < afStack_d0[iVar4 * 4 + 1]) {
      fStack_ec = afStack_d0[iVar4 * 4 + 1];
    }
    if (fStack_e8 < afStack_d0[iVar4 * 4 + 2]) {
      fStack_e8 = afStack_d0[iVar4 * 4 + 2];
    }
  }
  uVar5 = param_5 & 7;
  if (uVar5 == 4) {
    fStack_208 = (fStack_d8 + fStack_e8) / 2.0;
    fStack_20c = (fStack_dc + fStack_ec) / 2.0;
    fStack_210 = *(float *)(iGpffff86b4 + 0x3f14) / 2.0 - 3.0;
    uStack_204 = 0x3f800000;
    *(float *)(iVar6 + 0x70) = fStack_210;
    *(float *)(iVar6 + 0x74) = fStack_20c;
    *(float *)(iVar6 + 0x78) = fStack_208;
    *(undefined4 *)(iVar6 + 0x7c) = 0x3f800000;
    if ((param_5 & 8) != 0) {
      auVar7 = _lqc2(*(undefined1 (*) [16])(iGpffff86b4 + *(int *)(iVar6 + 0x48) * 0x4f0 + 0x150));
      auVar8 = _lqc2(*(undefined1 (*) [16])(iGpffff86b4 + *(int *)(iVar6 + 0x48) * 0x4f0 + 0x350));
      auVar7 = _vadd(auVar7,auVar8);
      auStack_330 = _sqc2(auVar7);
      __ct__7FVectorFRC7FVector(auStack_230,auStack_330);
      auVar7 = _lqc2(*(undefined1 (*) [16])(iVar6 + 0x70));
      auVar8 = _lqc2(auStack_230);
      auVar7 = _vsub(auVar7,auVar8);
      auStack_2d0 = _sqc2(auVar7);
      __ct__7FVectorFRC7FVector(auStack_220,auStack_2d0);
      afStack_d0[0x21] = (float)uStack_21c;
      afStack_d0[0x22] = (float)uStack_218;
      afStack_d0[0x23] = (float)uStack_214;
      afStack_d0[0x20] = 0.0;
      Normalize__7FVectorFv(afStack_d0 + 0x20);
      auVar7 = _qmtc2(0x40800000);
      _vdiv(in_vf0,0,auVar7,0);
      auVar7._4_4_ = afStack_d0[0x21];
      auVar7._0_4_ = afStack_d0[0x20];
      auVar7._8_4_ = afStack_d0[0x22];
      auVar7._12_4_ = afStack_d0[0x23];
      auVar7 = _lqc2(auVar7);
      uVar9 = _vwaitq();
      auVar7 = _vmulq(auVar7,uVar9);
      auStack_2e0 = _sqc2(auVar7);
      __ct__7FVectorFRC7FVector(auStack_240,auStack_2e0);
      *(int *)(iVar6 + 0x80) = auStack_240._0_4_;
      *(int *)(iVar6 + 0x84) = auStack_240._4_4_;
      *(undefined4 *)(iVar6 + 0x88) = uStack_238;
      *(undefined4 *)(iVar6 + 0x8c) = uStack_234;
    }
  }
  else if (uVar5 == 3) {
    fStack_1c8 = (fStack_d8 + fStack_e8) / 2.0;
    fStack_1cc = (fStack_dc + fStack_ec) / 2.0;
    fStack_1d0 = -*(float *)(iGpffff86b4 + 0x3f14) / 2.0 + 3.0;
    uStack_1c4 = 0x3f800000;
    *(float *)(iVar6 + 0x70) = fStack_1d0;
    *(float *)(iVar6 + 0x74) = fStack_1cc;
    *(float *)(iVar6 + 0x78) = fStack_1c8;
    *(undefined4 *)(iVar6 + 0x7c) = 0x3f800000;
    if ((param_5 & 8) != 0) {
      auVar7 = _lqc2(*(undefined1 (*) [16])(iGpffff86b4 + *(int *)(iVar6 + 0x48) * 0x4f0 + 0x150));
      auVar8 = _lqc2(*(undefined1 (*) [16])(iGpffff86b4 + *(int *)(iVar6 + 0x48) * 0x4f0 + 0x350));
      auVar7 = _vadd(auVar7,auVar8);
      auStack_320 = _sqc2(auVar7);
      __ct__7FVectorFRC7FVector(auStack_1f0,auStack_320);
      auVar7 = _lqc2(*(undefined1 (*) [16])(iVar6 + 0x70));
      auVar8 = _lqc2(auStack_1f0);
      auVar7 = _vsub(auVar7,auVar8);
      auStack_2b0 = _sqc2(auVar7);
      __ct__7FVectorFRC7FVector(auStack_1e0,auStack_2b0);
      afStack_d0[0x21] = (float)uStack_1dc;
      afStack_d0[0x22] = (float)uStack_1d8;
      afStack_d0[0x23] = (float)uStack_1d4;
      afStack_d0[0x20] = 0.0;
      Normalize__7FVectorFv(afStack_d0 + 0x20);
      auVar7 = _qmtc2(0x40800000);
      _vdiv(in_vf0,0,auVar7,0);
      auVar8._4_4_ = afStack_d0[0x21];
      auVar8._0_4_ = afStack_d0[0x20];
      auVar8._8_4_ = afStack_d0[0x22];
      auVar8._12_4_ = afStack_d0[0x23];
      auVar7 = _lqc2(auVar8);
      uVar9 = _vwaitq();
      auVar7 = _vmulq(auVar7,uVar9);
      auStack_2c0 = _sqc2(auVar7);
      __ct__7FVectorFRC7FVector(auStack_200,auStack_2c0);
      *(int *)(iVar6 + 0x80) = auStack_200._0_4_;
      *(int *)(iVar6 + 0x84) = auStack_200._4_4_;
      *(undefined4 *)(iVar6 + 0x88) = uStack_1f8;
      *(undefined4 *)(iVar6 + 0x8c) = uStack_1f4;
    }
  }
  else if (uVar5 == 2) {
    fStack_188 = -*(float *)(iGpffff86b4 + 0x3f1c) / 2.0 + 3.0;
    fStack_18c = (fStack_dc + fStack_ec) / 2.0;
    fStack_190 = (fStack_e0 + fStack_f0) / 2.0;
    uStack_184 = 0x3f800000;
    *(float *)(iVar6 + 0x70) = fStack_190;
    *(float *)(iVar6 + 0x74) = fStack_18c;
    *(float *)(iVar6 + 0x78) = fStack_188;
    *(undefined4 *)(iVar6 + 0x7c) = 0x3f800000;
    if ((param_5 & 8) != 0) {
      auVar7 = _lqc2(*(undefined1 (*) [16])(iGpffff86b4 + *(int *)(iVar6 + 0x48) * 0x4f0 + 0x150));
      auVar8 = _lqc2(*(undefined1 (*) [16])(iGpffff86b4 + *(int *)(iVar6 + 0x48) * 0x4f0 + 0x350));
      auVar7 = _vadd(auVar7,auVar8);
      auStack_310 = _sqc2(auVar7);
      __ct__7FVectorFRC7FVector(auStack_1b0,auStack_310);
      auVar7 = _lqc2(*(undefined1 (*) [16])(iVar6 + 0x70));
      auVar8 = _lqc2(auStack_1b0);
      auVar7 = _vsub(auVar7,auVar8);
      auStack_290 = _sqc2(auVar7);
      __ct__7FVectorFRC7FVector(auStack_1a0,auStack_290);
      afStack_d0[0x20] = (float)auStack_1a0._0_8_;
      afStack_d0[0x21] = SUB84(auStack_1a0._0_8_,4);
      afStack_d0[0x23] = (float)uStack_194;
      afStack_d0[0x22] = 0.0;
      Normalize__7FVectorFv(afStack_d0 + 0x20);
      auVar7 = _qmtc2(0x40800000);
      _vdiv(in_vf0,0,auVar7,0);
      auVar3._4_4_ = afStack_d0[0x21];
      auVar3._0_4_ = afStack_d0[0x20];
      auVar3._8_4_ = afStack_d0[0x22];
      auVar3._12_4_ = afStack_d0[0x23];
      auVar7 = _lqc2(auVar3);
      uVar9 = _vwaitq();
      auVar7 = _vmulq(auVar7,uVar9);
      auStack_2a0 = _sqc2(auVar7);
      __ct__7FVectorFRC7FVector(auStack_1c0,auStack_2a0);
      *(int *)(iVar6 + 0x80) = auStack_1c0._0_4_;
      *(int *)(iVar6 + 0x84) = auStack_1c0._4_4_;
      *(undefined4 *)(iVar6 + 0x88) = uStack_1b8;
      *(undefined4 *)(iVar6 + 0x8c) = uStack_1b4;
    }
  }
  else if (uVar5 == 1) {
    fStack_148 = *(float *)(iGpffff86b4 + 0x3f1c) / 2.0 - 3.0;
    fStack_14c = (fStack_dc + fStack_ec) / 2.0;
    fStack_150 = (fStack_e0 + fStack_f0) / 2.0;
    uStack_144 = 0x3f800000;
    *(float *)(iVar6 + 0x70) = fStack_150;
    *(float *)(iVar6 + 0x74) = fStack_14c;
    *(float *)(iVar6 + 0x78) = fStack_148;
    *(undefined4 *)(iVar6 + 0x7c) = 0x3f800000;
    if ((param_5 & 8) != 0) {
      auVar7 = _lqc2(*(undefined1 (*) [16])(iGpffff86b4 + *(int *)(iVar6 + 0x48) * 0x4f0 + 0x150));
      auVar8 = _lqc2(*(undefined1 (*) [16])(iGpffff86b4 + *(int *)(iVar6 + 0x48) * 0x4f0 + 0x350));
      auVar7 = _vadd(auVar7,auVar8);
      auStack_300 = _sqc2(auVar7);
      __ct__7FVectorFRC7FVector(auStack_170,auStack_300);
      auVar7 = _lqc2(*(undefined1 (*) [16])(iVar6 + 0x70));
      auVar8 = _lqc2(auStack_170);
      auVar7 = _vsub(auVar7,auVar8);
      auStack_270 = _sqc2(auVar7);
      __ct__7FVectorFRC7FVector(auStack_160,auStack_270);
      afStack_d0[0x20] = (float)auStack_160._0_8_;
      afStack_d0[0x21] = SUB84(auStack_160._0_8_,4);
      afStack_d0[0x23] = (float)uStack_154;
      afStack_d0[0x22] = 0.0;
      Normalize__7FVectorFv(afStack_d0 + 0x20);
      auVar7 = _qmtc2(0x40800000);
      _vdiv(in_vf0,0,auVar7,0);
      auVar2._4_4_ = afStack_d0[0x21];
      auVar2._0_4_ = afStack_d0[0x20];
      auVar2._8_4_ = afStack_d0[0x22];
      auVar2._12_4_ = afStack_d0[0x23];
      auVar7 = _lqc2(auVar2);
      uVar9 = _vwaitq();
      auVar7 = _vmulq(auVar7,uVar9);
      auStack_280 = _sqc2(auVar7);
      __ct__7FVectorFRC7FVector(auStack_180,auStack_280);
      *(int *)(iVar6 + 0x80) = auStack_180._0_4_;
      *(int *)(iVar6 + 0x84) = auStack_180._4_4_;
      *(undefined4 *)(iVar6 + 0x88) = uStack_178;
      *(undefined4 *)(iVar6 + 0x8c) = uStack_174;
    }
  }
  else if (uVar5 == 0) {
    fStack_108 = (fStack_d8 + fStack_e8) / 2.0;
    fStack_110 = (fStack_e0 + fStack_f0) / 2.0;
    uStack_10c = 0xc0400000;
    uStack_104 = 0x3f800000;
    *(float *)(iVar6 + 0x70) = fStack_110;
    *(undefined4 *)(iVar6 + 0x74) = 0xc0400000;
    *(float *)(iVar6 + 0x78) = fStack_108;
    *(undefined4 *)(iVar6 + 0x7c) = 0x3f800000;
    if ((param_5 & 8) != 0) {
      auVar7 = _lqc2(*(undefined1 (*) [16])(iGpffff86b4 + *(int *)(iVar6 + 0x48) * 0x4f0 + 0x150));
      auVar8 = _lqc2(*(undefined1 (*) [16])(iGpffff86b4 + *(int *)(iVar6 + 0x48) * 0x4f0 + 0x350));
      auVar7 = _vadd(auVar7,auVar8);
      auStack_2f0 = _sqc2(auVar7);
      __ct__7FVectorFRC7FVector(auStack_130,auStack_2f0);
      auVar7 = _lqc2(*(undefined1 (*) [16])(iVar6 + 0x70));
      auVar8 = _lqc2(auStack_130);
      auVar7 = _vsub(auVar7,auVar8);
      auStack_250 = _sqc2(auVar7);
      __ct__7FVectorFRC7FVector(auStack_120,auStack_250);
      afStack_d0[0x20] = (float)auStack_120[0];
      afStack_d0[0x22] = (float)uStack_118;
      afStack_d0[0x23] = (float)uStack_114;
      afStack_d0[0x21] = 0.0;
      Normalize__7FVectorFv(afStack_d0 + 0x20);
      auVar7 = _qmtc2(0x40800000);
      _vdiv(in_vf0,0,auVar7,0);
      auVar1._4_4_ = afStack_d0[0x21];
      auVar1._0_4_ = afStack_d0[0x20];
      auVar1._8_4_ = afStack_d0[0x22];
      auVar1._12_4_ = afStack_d0[0x23];
      auVar7 = _lqc2(auVar1);
      uVar9 = _vwaitq();
      auVar7 = _vmulq(auVar7,uVar9);
      auStack_260 = _sqc2(auVar7);
      __ct__7FVectorFRC7FVector(auStack_140,auStack_260);
      *(int *)(iVar6 + 0x80) = auStack_140._0_4_;
      *(int *)(iVar6 + 0x84) = auStack_140._4_4_;
      *(undefined4 *)(iVar6 + 0x88) = uStack_138;
      *(undefined4 *)(iVar6 + 0x8c) = uStack_134;
    }
  }
  *(float *)(iVar6 + 0x90) =
       (((fStack_e8 - fStack_d8) + (fStack_f0 - fStack_e0) + (fStack_ec - fStack_dc)) / 3.0 + 4.0) *
       0.75;
  *(undefined4 *)(iVar6 + 0x94) = 0;
  *(undefined4 *)(iVar6 + 0x1c) = 0;
  *(undefined4 *)(iVar6 + 0x18) = 0;
  Entry__7CPollerFP7CPolObjib(iGpffff858c + 0x48,param_1,0x80,0);
  BtlEffEntry__7CBattleFiP6BtlEff(iGpffff86b4,0xffffffffffffffff,param_1);
  return param_1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0050b620  __dt__9DownSmokeFv
 * C++: DownSmoke::__dt()
 * size: 0x154 bytes
 * --------------------------------------------------------------------------- */
int __dt__9DownSmokeFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x14) = 0x40a210;
    *(undefined4 *)(param_1 + 0x28) = 0x40a220;
    *(undefined4 *)(param_1 + 0x34) = 0x40a230;
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
 * JP: 0x0050b780  Destruct__9DownSmokeFv
 * C++: DownSmoke::Destruct()
 * size: 0xc4 bytes
 * --------------------------------------------------------------------------- */
void Destruct__9DownSmokeFv(int param_1)

{
  int iVar1;
  
  BtlEffRelease__7CBattleFiP6BtlEff(uGpffff86b4,0xffffffffffffffff,param_1);
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
 * JP: 0x0050b850  Polling__9DownSmokeFv
 * C++: DownSmoke::Polling()
 * size: 0x20c bytes
 * --------------------------------------------------------------------------- */
undefined4 Polling__9DownSmokeFv(int param_1)

{
  int iVar1;
  undefined1 auVar2 [16];
  undefined1 auVar3 [16];
  undefined1 auStack_90 [8];
  int iStack_88;
  undefined4 auStack_80 [16];
  undefined4 auStack_40 [16];
  
  if ((*(byte *)(iGpffff86b4 + 0x24) & 1) == 0) {
    auVar3 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x80));
    auVar2 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x70));
    auVar2 = _vadd(auVar2,auVar3);
    auVar2 = _sqc2(auVar2);
    *(undefined1 (*) [16])(param_1 + 0x70) = auVar2;
    *(float *)(param_1 + 0x94) = *(float *)(param_1 + 0x94) + *(float *)(iGpffff86b4 + 0x38);
    *(int *)(param_1 + 100) = (int)(*(float *)(param_1 + 0x94) / 0.033333335);
    if (0xb < *(int *)(param_1 + 100)) {
      BtlEffRelease__7CBattleFiP6BtlEff(iGpffff86b4,0xffffffffffffffff,param_1);
      if ((long)((ulong)*(byte *)(param_1 + 0x40) << 0x3e) < 0) {
        iVar1 = param_1;
        if (param_1 != 0) {
          iVar1 = param_1 + 0x18;
        }
        ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,iVar1);
      }
      *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfd;
      (**(code **)(*(int *)(param_1 + 0x34) + 0xc))();
      return 1;
    }
  }
  GetViewScreenMatrix__9GsxCameraFv(auStack_40,uGpffff8598);
  for (iVar1 = 0; iVar1 < 4; iVar1 = iVar1 + 1) {
    auStack_80[iVar1 * 4] = auStack_40[iVar1 * 4];
    auStack_80[iVar1 * 4 + 1] = auStack_40[iVar1 * 4 + 1];
    auStack_80[iVar1 * 4 + 2] = auStack_40[iVar1 * 4 + 2];
    auStack_80[iVar1 * 4 + 3] = auStack_40[iVar1 * 4 + 3];
  }
  sceVu0RotTransPersN(auStack_90,auStack_80,param_1 + 0x70,1,0);
  *(int *)(param_1 + 0x50) = (int)((float)iStack_88 / 16.0);
  return 0;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0050ba60  MakePacket__9DownSmokeFv
 * C++: DownSmoke::MakePacket()
 * size: 0x790 bytes
 * --------------------------------------------------------------------------- */
void MakePacket__9DownSmokeFv(int param_1)

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
  uint uVar6;
  int iVar7;
  undefined8 in_v1_udw;
  undefined1 auVar8 [16];
  undefined1 auVar9 [16];
  undefined4 uStack_200;
  undefined4 uStack_1fc;
  undefined4 uStack_1f8;
  undefined4 uStack_1f4;
  undefined4 uStack_1f0;
  undefined4 uStack_1ec;
  undefined4 uStack_1e8;
  undefined4 uStack_1e4;
  undefined4 uStack_1e0;
  undefined4 uStack_1dc;
  undefined4 uStack_1d8;
  undefined4 uStack_1d4;
  undefined4 uStack_1d0;
  undefined4 uStack_1cc;
  undefined4 uStack_1c8;
  undefined4 uStack_1c4;
  undefined4 uStack_1c0;
  undefined4 uStack_1bc;
  undefined4 uStack_1b8;
  undefined4 uStack_1b4;
  undefined4 uStack_1b0;
  float fStack_1ac;
  undefined4 uStack_1a8;
  undefined4 uStack_1a4;
  float fStack_1a0;
  undefined4 uStack_19c;
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
  float afStack_140 [16];
  undefined4 auStack_100 [16];
  float afStack_c0 [16];
  undefined4 auStack_80 [7];
  undefined4 uStack_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  float fStack_40;
  float fStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  float fStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  float fStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  fStack_18c = -*(float *)(param_1 + 0x90);
  fStack_190 = -*(float *)(param_1 + 0x90);
  uStack_188 = 0;
  uStack_184 = 0x3f800000;
  uStack_38 = 0;
  uStack_34 = 0x3f800000;
  uStack_19c = *(undefined4 *)(param_1 + 0x90);
  fStack_1a0 = -*(float *)(param_1 + 0x90);
  uStack_198 = 0;
  uStack_194 = 0x3f800000;
  uStack_28 = 0;
  uStack_24 = 0x3f800000;
  fStack_1ac = -*(float *)(param_1 + 0x90);
  uStack_1b0 = *(undefined4 *)(param_1 + 0x90);
  uStack_1a8 = 0;
  uStack_1a4 = 0x3f800000;
  uStack_18 = 0;
  uStack_14 = 0x3f800000;
  uStack_1bc = *(undefined4 *)(param_1 + 0x90);
  uStack_1c0 = *(undefined4 *)(param_1 + 0x90);
  uStack_1b8 = 0;
  uStack_1b4 = 0x3f800000;
  uStack_8 = 0;
  uStack_4 = 0x3f800000;
  fStack_40 = fStack_190;
  fStack_3c = fStack_18c;
  fStack_30 = fStack_1a0;
  uStack_2c = uStack_19c;
  uStack_20 = uStack_1b0;
  fStack_1c = fStack_1ac;
  uStack_10 = uStack_1c0;
  uStack_c = uStack_1bc;
  __ct__6MatrixFRC6Matrix(auStack_80,iGpffff8598 + 0x240);
  uStack_50 = 0;
  uStack_4c = 0;
  uStack_48 = 0;
  uStack_44 = 0x3f800000;
  RotTransVector(afStack_c0,&fStack_40,auStack_80,4);
  GetViewScreenMatrix__9GsxCameraFv(&uStack_200,iGpffff8598);
  auStack_80[0] = uStack_200;
  auStack_80[1] = uStack_1fc;
  auStack_80[2] = uStack_1f8;
  auStack_80[3] = uStack_1f4;
  auStack_80[4] = uStack_1f0;
  auStack_80[5] = uStack_1ec;
  auStack_80[6] = uStack_1e8;
  uStack_64 = uStack_1e4;
  uStack_60 = uStack_1e0;
  uStack_5c = uStack_1dc;
  uStack_58 = uStack_1d8;
  uStack_54 = uStack_1d4;
  uStack_50 = uStack_1d0;
  uStack_4c = uStack_1cc;
  uStack_48 = uStack_1c8;
  uStack_44 = uStack_1c4;
  for (iVar7 = 0; iVar7 < 4; iVar7 = iVar7 + 1) {
    auStack_100[iVar7 * 4] = auStack_80[iVar7 * 4];
    auStack_100[iVar7 * 4 + 1] = auStack_80[iVar7 * 4 + 1];
    auStack_100[iVar7 * 4 + 2] = auStack_80[iVar7 * 4 + 2];
    auStack_100[iVar7 * 4 + 3] = auStack_80[iVar7 * 4 + 3];
  }
  for (iVar7 = 0; iVar7 < 4; iVar7 = iVar7 + 1) {
    afStack_140[iVar7 * 4] = *(float *)(param_1 + 0x70) + afStack_c0[iVar7 * 4];
    afStack_140[iVar7 * 4 + 1] = *(float *)(param_1 + 0x74) + afStack_c0[iVar7 * 4 + 1];
    afStack_140[iVar7 * 4 + 2] = *(float *)(param_1 + 0x78) + afStack_c0[iVar7 * 4 + 2];
    afStack_140[iVar7 * 4 + 3] = 1.0;
  }
  sceVu0RotTransPersN(aiStack_180,auStack_100,afStack_140,4,0);
  bVar3 = false;
  for (iVar7 = 0; iVar7 < 4; iVar7 = iVar7 + 1) {
    if ((((aiStack_180[iVar7 * 4] < 0) || (0x10000 < aiStack_180[iVar7 * 4])) ||
        (aiStack_180[iVar7 * 4 + 1] < 0)) ||
       ((0x10000 < aiStack_180[iVar7 * 4 + 1] || (aiStack_180[iVar7 * 4 + 2] < 0)))) {
      bVar3 = true;
    }
    aiStack_180[iVar7 * 4 + 2] = (int)((float)aiStack_180[iVar7 * 4 + 2] / 16.0);
  }
  bVar1 = (*(byte *)(param_1 + 0x40) & 1) == 0;
  uVar6 = (uint)bVar1;
  if (*(int *)(param_1 + uVar6 * 4 + 0x18) == 0) {
    uVar4 = __nwa__FUi(0x100);
    *(undefined4 *)(param_1 + uVar6 * 4 + 0x18) = uVar4;
    iVar7 = *(int *)(param_1 + uVar6 * 4 + 0x18);
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
    uVar5 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x425c),1);
    *(undefined8 *)(iVar7 + 0x70) = uVar5;
    *(undefined8 *)(iVar7 + 0x78) = 0;
    *(undefined8 *)(iVar7 + 0x80) = 0x44;
    *(undefined8 *)(iVar7 + 0x88) = 0x42;
    auVar8._8_8_ = in_v1_udw;
    auVar8._0_8_ = 0xa400000000008001;
    auVar9._4_4_ = in_zero_hi;
    auVar9._0_4_ = in_zero_lo;
    auVar9._8_4_ = in_zero_udw;
    auVar9._12_4_ = in_register_0000000c;
    auVar9 = _pcpyld(auVar9,auVar8);
    *(long *)(iVar7 + 0x90) = auVar9._0_8_;
    *(undefined8 *)(iVar7 + 0x98) = 0x4343c3c310;
    *(undefined8 *)(iVar7 + 0xa0) = 0x154;
    *(undefined8 *)(iVar7 + 0xa8) = 0x180808080;
  }
  puVar2 = *(undefined4 **)(param_1 + uVar6 * 4 + 0x18);
  uVar6 = *(uint *)(param_1 + 100) & 7;
  iVar7 = *(int *)(param_1 + 100);
  if (iVar7 < 0) {
    iVar7 = iVar7 + 7;
  }
  iVar7 = iVar7 >> 3;
  if (bVar3) {
    *(undefined4 **)(param_1 + 0x54) = puVar2;
    *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfe | bVar1;
  }
  else {
    *puVar2 = 0x50000000;
    puVar2[1] = *(undefined4 *)
                 (*(int *)(iGpffff86b4 + 0x425c) +
                  (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x425c) + 10) * 4 + 0xc);
    puVar2[2] = 0;
    puVar2[3] = 0;
    *(long *)(puVar2 + 0x2c) = (long)(int)(uVar6 << 10) | (long)(iVar7 << 10) << 0x10;
    *(long *)(puVar2 + 0x2e) =
         (long)aiStack_180[2] << 0x20 | (long)aiStack_180[0] | (long)aiStack_180[1] << 0x10;
    *(long *)(puVar2 + 0x30) =
         (long)(int)(uVar6 << 10) | (long)((iVar7 * 0x40 + 0x40) * 0x10) << 0x10;
    *(long *)(puVar2 + 0x32) =
         (long)iStack_168 << 0x20 | (long)aiStack_180[4] | (long)aiStack_180[5] << 0x10;
    *(long *)(puVar2 + 0x34) =
         (long)(int)((uVar6 * 0x40 + 0x40) * 0x10) | (long)(iVar7 << 10) << 0x10;
    *(long *)(puVar2 + 0x36) =
         (long)iStack_158 << 0x20 | (long)iStack_160 | (long)iStack_15c << 0x10;
    *(long *)(puVar2 + 0x38) =
         (long)(int)((uVar6 * 0x40 + 0x40) * 0x10) | (long)((iVar7 * 0x40 + 0x40) * 0x10) << 0x10;
    *(long *)(puVar2 + 0x3a) =
         (long)iStack_148 << 0x20 | (long)iStack_150 | (long)iStack_14c << 0x10;
    *(undefined4 **)(param_1 + 0x54) = puVar2 + 0x3c;
    *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfe | bVar1;
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0050c1f0  getPacket__9DownSmokeFv
 * C++: DownSmoke::getPacket()
 * size: 0xd0 bytes
 * --------------------------------------------------------------------------- */
int getPacket__9DownSmokeFv(int param_1)

{
  int iVar1;
  
  (**(code **)(*(int *)(param_1 + 0x14) + 0x38))();
  if (*(int *)(param_1 + 0x54) == *(int *)(param_1 + (*(byte *)(param_1 + 0x40) & 1) * 4 + 0x18)) {
    iVar1 = 0;
  }
  else if (*(int *)(iGpffff86b8 + 0x3c) == 0xe) {
    iVar1 = *(int *)(param_1 + (*(byte *)(param_1 + 0x40) & 1) * 4 + 0x18) + 0x10;
  }
  else {
    *(undefined4 *)(iGpffff86b8 + 0x3c) = 0xe;
    iVar1 = *(int *)(param_1 + (*(byte *)(param_1 + 0x40) & 1) * 4 + 0x18);
  }
  return iVar1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054af50  EndSet__9DownSmokeFv
 * C++: DownSmoke::EndSet()
 * size: 0x10 bytes
 * --------------------------------------------------------------------------- */
void EndSet__9DownSmokeFv(void)

{
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b5a0  @24@getPacket__9DownSmokeFv
 * C++: @24@getPacket__9DownSmokeFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int _24_getPacket__9DownSmokeFv(int param_1)

{
  int iVar1;
  
  iVar1 = param_1 + -0x18;
  (**(code **)(*(int *)(param_1 + -4) + 0x38))();
  if (*(int *)(param_1 + 0x3c) == *(int *)(iVar1 + (*(byte *)(param_1 + 0x28) & 1) * 4 + 0x18)) {
    iVar1 = 0;
  }
  else if (*(int *)(iGpffff86b8 + 0x3c) == 0xe) {
    iVar1 = *(int *)(iVar1 + (*(byte *)(param_1 + 0x28) & 1) * 4 + 0x18) + 0x10;
  }
  else {
    *(undefined4 *)(iGpffff86b8 + 0x3c) = 0xe;
    iVar1 = *(int *)(iVar1 + (*(byte *)(param_1 + 0x28) & 1) * 4 + 0x18);
  }
  return iVar1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b5b0  @24@__dt__9DownSmokeFv
 * C++: @24@__dt__9DownSmokeFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int * _24___dt__9DownSmokeFv(int *param_1,short param_2)

{
  int *piVar1;
  
  piVar1 = param_1 + -6;
  if (piVar1 != (int *)0x0) {
    param_1[-1] = 0x40a210;
    param_1[4] = 0x40a220;
    param_1[7] = 0x40a230;
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
 * JP: 0x0054b5c0  @44@__dt__9DownSmokeFv
 * C++: @44@__dt__9DownSmokeFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int _44___dt__9DownSmokeFv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x2c;
  if (iVar1 != 0) {
    *(undefined4 *)(param_1 + -0x18) = 0x40a210;
    *(undefined4 *)(param_1 + -4) = 0x40a220;
    *(undefined4 *)(param_1 + 8) = 0x40a230;
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

