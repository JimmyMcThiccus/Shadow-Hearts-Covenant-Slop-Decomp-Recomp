/* decomp/H/StraightArea.c — cleaned Ghidra output (SH2JP_BATTLE.BIN, JP Furokuban, base 0x00430a00).
 * 8 function(s). Types: see types.h. Names/gp globals resolved from symbols/SLPM_602.19.syms. */
#include "types.h"

/* ---------------------------------------------------------------------------
 * JP: 0x00537fd0  __ct__12StraightAreaFiiif
 * C++: StraightArea::__ct(int, int, int, float)
 * size: 0xe0 bytes
 * --------------------------------------------------------------------------- */
int __ct__12StraightAreaFiiif
              (undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4,
              undefined4 param_5)

{
  __ct__6BtlEffFii(param_2,param_3,param_4);
  *(undefined4 *)(param_2 + 0x14) = 0x409b60;
  *(undefined4 *)(param_2 + 0x28) = 0x409b70;
  *(undefined4 *)(param_2 + 0x34) = 0x409b80;
  *(undefined4 *)(param_2 + 0x40) = 0;
  *(undefined4 *)(param_2 + 0x44) = param_3;
  *(undefined4 *)(param_2 + 0x48) = param_4;
  *(undefined4 *)(param_2 + 0x4c) = 9;
  *(undefined4 *)(param_2 + 0x5c) = param_5;
  *(undefined4 *)(param_2 + 0x60) = param_1;
  *(undefined4 *)(param_2 + 0x1c) = 0;
  *(undefined4 *)(param_2 + 0x18) = 0;
  BtlEffEntry__7CBattleFiP6BtlEff(uGpffff86b4,*(undefined4 *)(param_2 + 0x48),param_2);
  return param_2;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005380b0  __dt__12StraightAreaFv
 * C++: StraightArea::__dt()
 * size: 0x154 bytes
 * --------------------------------------------------------------------------- */
int __dt__12StraightAreaFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x14) = 0x409b60;
    *(undefined4 *)(param_1 + 0x28) = 0x409b70;
    *(undefined4 *)(param_1 + 0x34) = 0x409b80;
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
 * JP: 0x00538210  Destruct__12StraightAreaFv
 * C++: StraightArea::Destruct()
 * size: 0x4c bytes
 * --------------------------------------------------------------------------- */
void Destruct__12StraightAreaFv(int param_1)

{
  BtlEffRelease__7CBattleFiP6BtlEff(uGpffff86b4,*(undefined4 *)(param_1 + 0x48),param_1);
  (**(code **)(*(int *)(param_1 + 0x34) + 0xc))();
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00538260  Polling__12StraightAreaFv
 * C++: StraightArea::Polling()
 * size: 0x14 bytes
 * --------------------------------------------------------------------------- */
undefined8 Polling__12StraightAreaFv(void)

{
  return 0;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00538280  MakePacket__12StraightAreaFv
 * C++: StraightArea::MakePacket()
 * size: 0x1500 bytes
 * --------------------------------------------------------------------------- */
void MakePacket__12StraightAreaFv(int param_1)

{
  bool bVar1;
  undefined4 *puVar2;
  undefined1 auVar3 [16];
  bool bVar4;
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  undefined4 uVar5;
  int iVar6;
  undefined8 in_a0_udw;
  undefined1 auVar7 [16];
  uint uVar8;
  float fVar9;
  float fVar10;
  undefined1 in_vf0 [16];
  undefined1 auVar11 [16];
  undefined1 auVar12 [16];
  undefined1 auVar13 [16];
  undefined1 auStack_340 [16];
  undefined1 auStack_330 [16];
  undefined1 auStack_320 [16];
  undefined1 auStack_310 [64];
  int aiStack_2d0 [80];
  float afStack_190 [3];
  undefined4 uStack_184;
  float fStack_180;
  undefined4 uStack_17c;
  float fStack_178;
  undefined4 uStack_174;
  float fStack_170;
  undefined4 uStack_16c;
  float fStack_168;
  undefined4 uStack_164;
  float fStack_160;
  undefined4 uStack_15c;
  float fStack_158;
  undefined4 uStack_154;
  float fStack_150;
  undefined4 uStack_14c;
  float fStack_148;
  undefined4 uStack_144;
  float fStack_140;
  undefined4 uStack_13c;
  float fStack_138;
  undefined4 uStack_134;
  float fStack_130;
  undefined4 uStack_12c;
  float fStack_128;
  undefined4 uStack_124;
  float fStack_120;
  undefined4 uStack_11c;
  float fStack_118;
  undefined4 uStack_114;
  float fStack_110;
  float fStack_10c;
  float fStack_108;
  undefined4 uStack_104;
  float fStack_100;
  float fStack_fc;
  float fStack_f8;
  undefined4 uStack_f4;
  float fStack_f0;
  float fStack_ec;
  float fStack_e8;
  undefined4 uStack_e4;
  float fStack_e0;
  float fStack_dc;
  float fStack_d8;
  undefined4 uStack_d4;
  float fStack_d0;
  float fStack_cc;
  float fStack_c8;
  undefined4 uStack_c4;
  float fStack_c0;
  float fStack_bc;
  float fStack_b8;
  undefined4 uStack_b4;
  float fStack_b0;
  float fStack_ac;
  float fStack_a8;
  undefined4 uStack_a4;
  float fStack_a0;
  float fStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  float afStack_90 [2];
  float fStack_88;
  undefined1 auStack_80 [16];
  undefined1 auStack_70 [16];
  undefined1 auStack_60 [16];
  undefined1 auStack_50 [16];
  undefined1 auStack_40 [16];
  float afStack_30 [2];
  float fStack_28;
  uint auStack_20 [2];
  undefined8 uStack_18;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined8 uStack_8;
  
  bVar4 = false;
  auVar11 = _lqc2(*(undefined1 (*) [16])(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x150));
  auVar12 = _lqc2(*(undefined1 (*) [16])(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x390));
  auVar11 = _vadd(auVar11,auVar12);
  auStack_320 = _sqc2(auVar11);
  __ct__7FVectorFRC7FVector(&uStack_10,auStack_320);
  uStack_c = 0;
  auVar11 = _lqc2(*(undefined1 (*) [16])(iGpffff86b4 + *(int *)(param_1 + 0x5c) * 0x4f0 + 0x150));
  auVar12 = _lqc2(*(undefined1 (*) [16])(iGpffff86b4 + *(int *)(param_1 + 0x5c) * 0x4f0 + 0x390));
  auVar11 = _vadd(auVar11,auVar12);
  auStack_330 = _sqc2(auVar11);
  __ct__7FVectorFRC7FVector(auStack_20,auStack_330);
  auStack_20[1] = 0;
  auVar11._4_4_ = 0;
  auVar11._0_4_ = auStack_20[0];
  auVar11._8_8_ = uStack_18;
  auVar11 = _lqc2(auVar11);
  auVar12._4_4_ = uStack_c;
  auVar12._0_4_ = uStack_10;
  auVar12._8_8_ = uStack_8;
  auVar12 = _lqc2(auVar12);
  auVar11 = _vsub(auVar11,auVar12);
  auStack_340 = _sqc2(auVar11);
  __ct__7FVectorFRC7FVector(afStack_30,auStack_340);
  Normalize__7FVectorFv(afStack_30);
  __ct__7FVectorFRC7FVector(auStack_40,afStack_30);
  __amu__7FVectorFf(*(undefined4 *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x3b0),auStack_40
                 );
  auVar13._4_4_ = uStack_c;
  auVar13._0_4_ = uStack_10;
  auVar13._8_8_ = uStack_8;
  auVar12 = _lqc2(auVar13);
  auVar11 = _lqc2(auStack_40);
  auVar11 = _vadd(auVar11,auVar12);
  auStack_40 = _sqc2(auVar11);
  fVar10 = 500.0;
  fVar9 = 500.0;
  if (afStack_30[0] < 0.0) {
    fVar10 = (-*(float *)(iGpffff86b4 + 0x3f14) / 2.0 - (float)auStack_40._0_4_) / afStack_30[0];
  }
  if (0.0 < afStack_30[0]) {
    fVar10 = (*(float *)(iGpffff86b4 + 0x3f14) / 2.0 - (float)auStack_40._0_4_) / afStack_30[0];
  }
  if (fStack_28 < 0.0) {
    fVar9 = (-*(float *)(iGpffff86b4 + 0x3f1c) / 2.0 - (float)auStack_40._8_4_) / fStack_28;
  }
  if (0.0 < fStack_28) {
    fVar9 = (*(float *)(iGpffff86b4 + 0x3f1c) / 2.0 - (float)auStack_40._8_4_) / fStack_28;
  }
  if (fVar10 <= fVar9) {
    fVar9 = fVar10;
  }
  auVar11 = _vmr32(in_vf0);
  auVar12 = _vmr32(auVar11);
  auVar13 = _vmr32(auVar12);
  _sqc2(in_vf0);
  _sqc2(auVar11);
  _sqc2(auVar12);
  _sqc2(auVar13);
  auVar11 = _vmr32(in_vf0);
  auVar12 = _vmr32(auVar11);
  auVar13 = _vmr32(auVar12);
  auStack_50 = _sqc2(in_vf0);
  auStack_60 = _sqc2(auVar11);
  auStack_70 = _sqc2(auVar12);
  auStack_80 = _sqc2(auVar13);
  sceVu0RotMatrixY(0xbfc90fdb,auStack_80,auStack_80);
  ApplyMatrix__6MatrixCFRC7FVector(afStack_90,auStack_80,afStack_30);
  afStack_190[0] = (float)auStack_40._0_4_ + afStack_90[0] * *(float *)(param_1 + 0x60);
  afStack_190[1] = -0.2;
  afStack_190[2] = (float)auStack_40._8_4_ + fStack_88 * *(float *)(param_1 + 0x60);
  uStack_184 = 0x3f800000;
  fStack_180 = (float)auStack_40._0_4_ - afStack_90[0] * *(float *)(param_1 + 0x60);
  uStack_17c = 0xbe4ccccd;
  fStack_178 = (float)auStack_40._8_4_ - fStack_88 * *(float *)(param_1 + 0x60);
  uStack_174 = 0x3f800000;
  fStack_170 = (float)auStack_40._0_4_ + afStack_30[0] * 10.0 +
               afStack_90[0] * *(float *)(param_1 + 0x60);
  uStack_16c = 0xbe4ccccd;
  fStack_168 = (float)auStack_40._8_4_ + fStack_28 * 10.0 + fStack_88 * *(float *)(param_1 + 0x60);
  uStack_164 = 0x3f800000;
  fStack_160 = ((float)auStack_40._0_4_ + afStack_30[0] * 10.0) -
               afStack_90[0] * *(float *)(param_1 + 0x60);
  uStack_15c = 0xbe4ccccd;
  fStack_158 = ((float)auStack_40._8_4_ + fStack_28 * 10.0) - fStack_88 * *(float *)(param_1 + 0x60)
  ;
  uStack_154 = 0x3f800000;
  fStack_150 = (float)auStack_40._0_4_ + afStack_30[0] * fVar9 +
               afStack_90[0] * *(float *)(param_1 + 0x60);
  uStack_14c = 0xbe4ccccd;
  fStack_148 = (float)auStack_40._8_4_ + fStack_28 * fVar9 + fStack_88 * *(float *)(param_1 + 0x60);
  uStack_144 = 0x3f800000;
  fStack_140 = ((float)auStack_40._0_4_ + afStack_30[0] * fVar9) -
               afStack_90[0] * *(float *)(param_1 + 0x60);
  uStack_13c = 0xbe4ccccd;
  fStack_138 = ((float)auStack_40._8_4_ + fStack_28 * fVar9) -
               fStack_88 * *(float *)(param_1 + 0x60);
  uStack_134 = 0x3f800000;
  fStack_130 = (float)auStack_40._0_4_ + afStack_30[0] * (fVar9 + 10.0) +
               afStack_90[0] * *(float *)(param_1 + 0x60);
  uStack_12c = 0xbe4ccccd;
  fStack_128 = (float)auStack_40._8_4_ + fStack_28 * (fVar9 + 10.0) +
               fStack_88 * *(float *)(param_1 + 0x60);
  uStack_124 = 0x3f800000;
  fStack_120 = ((float)auStack_40._0_4_ + afStack_30[0] * (fVar9 + 10.0)) -
               afStack_90[0] * *(float *)(param_1 + 0x60);
  uStack_11c = 0xbe4ccccd;
  fStack_118 = ((float)auStack_40._8_4_ + fStack_28 * (fVar9 + 10.0)) -
               fStack_88 * *(float *)(param_1 + 0x60);
  uStack_114 = 0x3f800000;
  fStack_110 = (float)auStack_40._0_4_ + afStack_90[0] * *(float *)(param_1 + 0x60);
  fStack_10c = -*(float *)(param_1 + 0x60);
  fStack_108 = (float)auStack_40._8_4_ + fStack_88 * *(float *)(param_1 + 0x60);
  uStack_104 = 0x3f800000;
  fStack_100 = (float)auStack_40._0_4_ + afStack_30[0] * 10.0 +
               afStack_90[0] * *(float *)(param_1 + 0x60);
  fStack_fc = -*(float *)(param_1 + 0x60);
  fStack_f8 = (float)auStack_40._8_4_ + fStack_28 * 10.0 + fStack_88 * *(float *)(param_1 + 0x60);
  uStack_f4 = 0x3f800000;
  fStack_f0 = (float)auStack_40._0_4_ + afStack_30[0] * fVar9 +
              afStack_90[0] * *(float *)(param_1 + 0x60);
  fStack_ec = -*(float *)(param_1 + 0x60);
  fStack_e8 = (float)auStack_40._8_4_ + fStack_28 * fVar9 + fStack_88 * *(float *)(param_1 + 0x60);
  uStack_e4 = 0x3f800000;
  fStack_e0 = (float)auStack_40._0_4_ + afStack_30[0] * (fVar9 + 10.0) +
              afStack_90[0] * *(float *)(param_1 + 0x60);
  fStack_dc = -*(float *)(param_1 + 0x60);
  fStack_d8 = (float)auStack_40._8_4_ + fStack_28 * (fVar9 + 10.0) +
              fStack_88 * *(float *)(param_1 + 0x60);
  uStack_d4 = 0x3f800000;
  fStack_d0 = (float)auStack_40._0_4_ - afStack_90[0] * *(float *)(param_1 + 0x60);
  fStack_cc = -*(float *)(param_1 + 0x60);
  fStack_c8 = (float)auStack_40._8_4_ - fStack_88 * *(float *)(param_1 + 0x60);
  uStack_c4 = 0x3f800000;
  fStack_c0 = ((float)auStack_40._0_4_ + afStack_30[0] * 10.0) -
              afStack_90[0] * *(float *)(param_1 + 0x60);
  fStack_bc = -*(float *)(param_1 + 0x60);
  fStack_b8 = ((float)auStack_40._8_4_ + fStack_28 * 10.0) - fStack_88 * *(float *)(param_1 + 0x60);
  uStack_b4 = 0x3f800000;
  fStack_b0 = ((float)auStack_40._0_4_ + afStack_30[0] * fVar9) -
              afStack_90[0] * *(float *)(param_1 + 0x60);
  fStack_ac = -*(float *)(param_1 + 0x60);
  fStack_a8 = ((float)auStack_40._8_4_ + fStack_28 * fVar9) - fStack_88 * *(float *)(param_1 + 0x60)
  ;
  uStack_a4 = 0x3f800000;
  fStack_a0 = ((float)auStack_40._0_4_ + afStack_30[0] * (fVar9 + 10.0)) -
              afStack_90[0] * *(float *)(param_1 + 0x60);
  fStack_9c = -*(float *)(param_1 + 0x60);
  fStack_98 = ((float)auStack_40._8_4_ + fStack_28 * (fVar9 + 10.0)) -
              fStack_88 * *(float *)(param_1 + 0x60);
  uStack_94 = 0x3f800000;
  GetViewScreenMatrix__9GsxCameraFv(auStack_310,uGpffff8598);
  for (iVar6 = 0; iVar6 < 4; iVar6 = iVar6 + 1) {
    aiStack_2d0[iVar6 * 4 + 0x40] = *(int *)(auStack_80 + iVar6 * 0x10);
    aiStack_2d0[iVar6 * 4 + 0x41] = *(int *)(auStack_80 + iVar6 * 0x10 + 4);
    aiStack_2d0[iVar6 * 4 + 0x42] = *(int *)(auStack_80 + iVar6 * 0x10 + 8);
    aiStack_2d0[iVar6 * 4 + 0x43] = *(int *)(auStack_80 + iVar6 * 0x10 + 0xc);
  }
  sceVu0RotTransPersN(aiStack_2d0,aiStack_2d0 + 0x40,afStack_190,0x10,0);
  for (iVar6 = 0; iVar6 < 0x10; iVar6 = iVar6 + 1) {
    if ((((aiStack_2d0[iVar6 * 4] < 0) || (0x10000 < aiStack_2d0[iVar6 * 4])) ||
        (aiStack_2d0[iVar6 * 4 + 1] < 0)) ||
       ((0x10000 < aiStack_2d0[iVar6 * 4 + 1] || (aiStack_2d0[iVar6 * 4 + 2] < 0)))) {
      bVar4 = true;
    }
    aiStack_2d0[iVar6 * 4 + 2] = (int)((float)aiStack_2d0[iVar6 * 4 + 2] / 16.0);
  }
  *(int *)(param_1 + 0x50) = (int)((float)(aiStack_2d0[2] + aiStack_2d0[6]) / 2.0);
  bVar1 = (*(byte *)(param_1 + 0x40) & 1) == 0;
  uVar8 = (uint)bVar1;
  if (*(int *)(param_1 + uVar8 * 4 + 0x18) == 0) {
    uVar5 = __nwa__FUi(0x200);
    *(undefined4 *)(param_1 + uVar8 * 4 + 0x18) = uVar5;
    iVar6 = *(int *)(param_1 + uVar8 * 4 + 0x18);
    *(undefined8 *)(iVar6 + 0x10) = 0x2000000000000001;
    *(undefined8 *)(iVar6 + 0x18) = 0xee;
    *(undefined8 *)(iVar6 + 0x20) = 0x53001;
    *(undefined8 *)(iVar6 + 0x28) = 0x47;
    *(undefined8 *)(iVar6 + 0x30) = 0x44;
    *(undefined8 *)(iVar6 + 0x38) = 0x42;
    auVar7._8_8_ = in_a0_udw;
    auVar7._0_8_ = 0xc400000000000001;
    auVar3._4_4_ = in_zero_hi;
    auVar3._0_4_ = in_zero_lo;
    auVar3._8_4_ = in_zero_udw;
    auVar3._12_4_ = in_register_0000000c;
    auVar11 = _pcpyld(auVar3,auVar7);
    *(long *)(iVar6 + 0x40) = auVar11._0_8_;
    *(undefined8 *)(iVar6 + 0x48) = 0x44144441cc10;
    *(undefined8 *)(iVar6 + 0x50) = 0x4c;
    *(undefined8 *)(iVar6 + 0x58) = 0x10020a0ff;
    *(undefined8 *)(iVar6 + 0x70) = 0x17020a0ff;
    *(undefined8 *)(iVar6 + 0x98) = 0x10020a0ff;
    *(undefined8 *)(iVar6 + 0xb0) = 0x2400000000000002;
    *(undefined8 *)(iVar6 + 0xb8) = 0xc1;
    *(undefined8 *)(iVar6 + 0xc0) = 0x10020a0ff;
    *(undefined8 *)(iVar6 + 0xd0) = 0x10020a0ff;
    *(undefined8 *)(iVar6 + 0xe0) = 0x2400000000000006;
    *(undefined8 *)(iVar6 + 0xe8) = 0x41;
    *(undefined8 *)(iVar6 + 0xf0) = 0x11020a0ff;
    *(undefined8 *)(iVar6 + 0x100) = 0x13020a0ff;
    *(undefined8 *)(iVar6 + 0x110) = 0x11020a0ff;
    *(undefined8 *)(iVar6 + 0x120) = 0x13020a0ff;
    *(undefined8 *)(iVar6 + 0x130) = 0x10020a0ff;
    *(undefined8 *)(iVar6 + 0x140) = 0x10020a0ff;
    *(undefined8 *)(iVar6 + 0x150) = 0x2400000000000002;
    *(undefined8 *)(iVar6 + 0x158) = 0xc1;
    *(undefined8 *)(iVar6 + 0x160) = 0x10020a0ff;
    *(undefined8 *)(iVar6 + 0x170) = 0x10020a0ff;
    *(undefined8 *)(iVar6 + 0x180) = 0x2400000000008006;
    *(undefined8 *)(iVar6 + 0x188) = 0x41;
    *(undefined8 *)(iVar6 + 400) = 0x11020a0ff;
    *(undefined8 *)(iVar6 + 0x1a0) = 0x13020a0ff;
    *(undefined8 *)(iVar6 + 0x1b0) = 0x11020a0ff;
    *(undefined8 *)(iVar6 + 0x1c0) = 0x13020a0ff;
    *(undefined8 *)(iVar6 + 0x1d0) = 0x10020a0ff;
    *(undefined8 *)(iVar6 + 0x1e0) = 0x10020a0ff;
  }
  puVar2 = *(undefined4 **)(param_1 + uVar8 * 4 + 0x18);
  if (bVar4) {
    *(undefined4 **)(param_1 + 0x54) = puVar2;
    *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfe | bVar1;
  }
  else {
    *puVar2 = 0x1000001e;
    puVar2[1] = 0;
    puVar2[2] = 0x11000000;
    puVar2[3] = 0x5000001e;
    *(long *)(puVar2 + 0x18) =
         (long)aiStack_2d0[2] << 0x20 | (long)aiStack_2d0[0] | (long)aiStack_2d0[1] << 0x10;
    *(long *)(puVar2 + 0x1a) =
         (long)aiStack_2d0[6] << 0x20 | (long)aiStack_2d0[4] | (long)aiStack_2d0[5] << 0x10;
    *(long *)(puVar2 + 0x1e) =
         (long)aiStack_2d0[10] << 0x20 | (long)aiStack_2d0[8] | (long)aiStack_2d0[9] << 0x10;
    *(long *)(puVar2 + 0x20) =
         (long)aiStack_2d0[0xe] << 0x20 | (long)aiStack_2d0[0xc] | (long)aiStack_2d0[0xd] << 0x10;
    *(long *)(puVar2 + 0x22) =
         (long)aiStack_2d0[0x12] << 0x20 | (long)aiStack_2d0[0x10] | (long)aiStack_2d0[0x11] << 0x10
    ;
    *(long *)(puVar2 + 0x24) =
         (long)aiStack_2d0[0x16] << 0x20 | (long)aiStack_2d0[0x14] | (long)aiStack_2d0[0x15] << 0x10
    ;
    *(long *)(puVar2 + 0x28) =
         (long)aiStack_2d0[0x1a] << 0x20 | (long)aiStack_2d0[0x18] | (long)aiStack_2d0[0x19] << 0x10
    ;
    *(long *)(puVar2 + 0x2a) =
         (long)aiStack_2d0[0x1e] << 0x20 | (long)aiStack_2d0[0x1c] | (long)aiStack_2d0[0x1d] << 0x10
    ;
    *(long *)(puVar2 + 0x32) =
         (long)aiStack_2d0[0x22] << 0x20 | (long)aiStack_2d0[0x20] | (long)aiStack_2d0[0x21] << 0x10
    ;
    *(long *)(puVar2 + 0x36) =
         (long)aiStack_2d0[2] << 0x20 | (long)aiStack_2d0[0] | (long)aiStack_2d0[1] << 0x10;
    *(long *)(puVar2 + 0x3e) =
         (long)aiStack_2d0[0x26] << 0x20 | (long)aiStack_2d0[0x24] | (long)aiStack_2d0[0x25] << 0x10
    ;
    *(long *)(puVar2 + 0x42) =
         (long)aiStack_2d0[10] << 0x20 | (long)aiStack_2d0[8] | (long)aiStack_2d0[9] << 0x10;
    *(long *)(puVar2 + 0x46) =
         (long)aiStack_2d0[0x2a] << 0x20 | (long)aiStack_2d0[0x28] | (long)aiStack_2d0[0x29] << 0x10
    ;
    *(long *)(puVar2 + 0x4a) =
         (long)aiStack_2d0[0x12] << 0x20 | (long)aiStack_2d0[0x10] | (long)aiStack_2d0[0x11] << 0x10
    ;
    *(long *)(puVar2 + 0x4e) =
         (long)aiStack_2d0[0x2e] << 0x20 | (long)aiStack_2d0[0x2c] | (long)aiStack_2d0[0x2d] << 0x10
    ;
    *(long *)(puVar2 + 0x52) =
         (long)aiStack_2d0[0x1a] << 0x20 | (long)aiStack_2d0[0x18] | (long)aiStack_2d0[0x19] << 0x10
    ;
    *(long *)(puVar2 + 0x5a) =
         (long)aiStack_2d0[0x32] << 0x20 | (long)aiStack_2d0[0x30] | (long)aiStack_2d0[0x31] << 0x10
    ;
    *(long *)(puVar2 + 0x5e) =
         (long)aiStack_2d0[6] << 0x20 | (long)aiStack_2d0[4] | (long)aiStack_2d0[5] << 0x10;
    *(long *)(puVar2 + 0x66) =
         (long)aiStack_2d0[0x36] << 0x20 | (long)aiStack_2d0[0x34] | (long)aiStack_2d0[0x35] << 0x10
    ;
    *(long *)(puVar2 + 0x6a) =
         (long)aiStack_2d0[0xe] << 0x20 | (long)aiStack_2d0[0xc] | (long)aiStack_2d0[0xd] << 0x10;
    *(long *)(puVar2 + 0x6e) =
         (long)aiStack_2d0[0x3a] << 0x20 | (long)aiStack_2d0[0x38] | (long)aiStack_2d0[0x39] << 0x10
    ;
    *(long *)(puVar2 + 0x72) =
         (long)aiStack_2d0[0x16] << 0x20 | (long)aiStack_2d0[0x14] | (long)aiStack_2d0[0x15] << 0x10
    ;
    *(long *)(puVar2 + 0x76) =
         (long)aiStack_2d0[0x3e] << 0x20 | (long)aiStack_2d0[0x3c] | (long)aiStack_2d0[0x3d] << 0x10
    ;
    *(long *)(puVar2 + 0x7a) =
         (long)aiStack_2d0[0x1e] << 0x20 | (long)aiStack_2d0[0x1c] | (long)aiStack_2d0[0x1d] << 0x10
    ;
    *(undefined4 **)(param_1 + 0x54) = puVar2 + 0x7c;
    *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfe | bVar1;
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054adf0  EndSet__12StraightAreaFv
 * C++: StraightArea::EndSet()
 * size: 0x10 bytes
 * --------------------------------------------------------------------------- */
void EndSet__12StraightAreaFv(void)

{
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b8b0  @24@__dt__12StraightAreaFv
 * C++: @24@__dt__12StraightAreaFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int * _24___dt__12StraightAreaFv(int *param_1,short param_2)

{
  int *piVar1;
  
  piVar1 = param_1 + -6;
  if (piVar1 != (int *)0x0) {
    param_1[-1] = 0x409b60;
    param_1[4] = 0x409b70;
    param_1[7] = 0x409b80;
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
 * JP: 0x0054b8c0  @44@__dt__12StraightAreaFv
 * C++: @44@__dt__12StraightAreaFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int _44___dt__12StraightAreaFv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x2c;
  if (iVar1 != 0) {
    *(undefined4 *)(param_1 + -0x18) = 0x409b60;
    *(undefined4 *)(param_1 + -4) = 0x409b70;
    *(undefined4 *)(param_1 + 8) = 0x409b80;
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

