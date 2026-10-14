/* decomp/H/NormalDeathEfct.c — cleaned Ghidra output (SH2JP_BATTLE.BIN, JP Furokuban, base 0x00430a00).
 * 10 function(s). Types: see types.h. Names/gp globals resolved from symbols/SLPM_602.19.syms. */
#include "types.h"

/* ---------------------------------------------------------------------------
 * JP: 0x0051c960  __ct__15NormalDeathEfctFii
 * C++: NormalDeathEfct::__ct(int, int)
 * size: 0x13c bytes
 * --------------------------------------------------------------------------- */
int __ct__15NormalDeathEfctFii(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  __ct__6BtlEffFii(param_1,param_2,param_3);
  *(undefined4 *)(param_1 + 0x14) = 0x409f70;
  *(undefined4 *)(param_1 + 0x28) = 0x409f80;
  *(undefined4 *)(param_1 + 0x34) = 0x409f90;
  *(undefined4 *)(param_1 + 0x44) = param_2;
  *(undefined4 *)(param_1 + 0x48) = param_3;
  *(undefined4 *)(param_1 + 0x40) = 0;
  *(undefined4 *)(param_1 + 0x4c) = 0x17;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  *(undefined4 *)(param_1 + 0x18) = 0;
  *(undefined4 *)(param_1 + 0x5c) = 0;
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
 * JP: 0x0051caa0  __dt__15NormalDeathEfctFv
 * C++: NormalDeathEfct::__dt()
 * size: 0x154 bytes
 * --------------------------------------------------------------------------- */
int __dt__15NormalDeathEfctFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x14) = 0x409f70;
    *(undefined4 *)(param_1 + 0x28) = 0x409f80;
    *(undefined4 *)(param_1 + 0x34) = 0x409f90;
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
 * JP: 0x0051cc00  Destruct__15NormalDeathEfctFv
 * C++: NormalDeathEfct::Destruct()
 * size: 0xa8 bytes
 * --------------------------------------------------------------------------- */
void Destruct__15NormalDeathEfctFv(int param_1)

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
  Dispose__7CPollerFP7CPolObj(iGpffff858c + 0x48,param_1);
  (**(code **)(*(int *)(param_1 + 0x34) + 0xc))();
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0051ccb0  Polling__15NormalDeathEfctFv
 * C++: NormalDeathEfct::Polling()
 * size: 0x23c bytes
 * --------------------------------------------------------------------------- */
undefined4 Polling__15NormalDeathEfctFv(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  float fVar3;
  undefined1 auVar4 [16];
  undefined1 auVar5 [16];
  undefined1 auStack_b0 [16];
  undefined1 auStack_a0 [8];
  int iStack_98;
  undefined1 auStack_90 [16];
  undefined4 auStack_80 [16];
  undefined4 auStack_40 [16];
  
  fVar3 = *(float *)(iGpffff86b4 + 0x38);
  if ((*(byte *)(iGpffff86b4 + 0x24) & 1) != 0) {
    fVar3 = 0.0;
  }
  *(float *)(param_1 + 0x5c) = *(float *)(param_1 + 0x5c) + fVar3 * 3.75;
  if (1.0 <= *(float *)(param_1 + 0x5c)) {
    BtlEffRelease__7CBattleFiP6BtlEff(iGpffff86b4,*(undefined4 *)(param_1 + 0x48),param_1);
    if ((long)((ulong)*(byte *)(param_1 + 0x40) << 0x3e) < 0) {
      iVar2 = param_1;
      if (param_1 != 0) {
        iVar2 = param_1 + 0x18;
      }
      ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,iVar2);
    }
    (**(code **)(*(int *)(param_1 + 0x34) + 0xc))();
    uVar1 = 1;
  }
  else {
    GetViewScreenMatrix__9GsxCameraFv(auStack_40,uGpffff8598);
    for (iVar2 = 0; iVar2 < 4; iVar2 = iVar2 + 1) {
      auStack_80[iVar2 * 4] = auStack_40[iVar2 * 4];
      auStack_80[iVar2 * 4 + 1] = auStack_40[iVar2 * 4 + 1];
      auStack_80[iVar2 * 4 + 2] = auStack_40[iVar2 * 4 + 2];
      auStack_80[iVar2 * 4 + 3] = auStack_40[iVar2 * 4 + 3];
    }
    auVar4 = _lqc2(*(undefined1 (*) [16])(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x150));
    auVar5 = _lqc2(*(undefined1 (*) [16])(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x350));
    auVar4 = _vadd(auVar4,auVar5);
    auStack_b0 = _sqc2(auVar4);
    __ct__7FVectorFRC7FVector(auStack_90,auStack_b0);
    sceVu0RotTransPersN(auStack_a0,auStack_80,auStack_90,1,0);
    *(int *)(param_1 + 0x50) = (int)((float)iStack_98 / 16.0);
    uVar1 = 0;
  }
  return uVar1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0051cef0  MakePacket__15NormalDeathEfctFv
 * C++: NormalDeathEfct::MakePacket()
 * size: 0xd54 bytes
 * --------------------------------------------------------------------------- */
void MakePacket__15NormalDeathEfctFv(int param_1)

{
  bool bVar1;
  undefined4 *puVar2;
  undefined1 auVar3 [16];
  bool bVar4;
  undefined1 auVar5 [16];
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  int iVar8;
  undefined8 uVar9;
  long lVar10;
  undefined8 in_v1_udw;
  undefined1 auVar11 [16];
  ulong uVar12;
  ulong uVar13;
  ulong uVar14;
  uint uVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  undefined4 uVar19;
  float fVar20;
  undefined1 in_vf0 [16];
  undefined1 auVar21 [16];
  undefined1 auVar22 [16];
  undefined1 auVar23 [16];
  undefined1 auStack_260 [16];
  undefined1 auStack_250 [64];
  undefined1 auStack_210 [8];
  float fStack_208;
  float fStack_204;
  undefined4 uStack_200;
  undefined4 uStack_1fc;
  float fStack_1f8;
  undefined4 uStack_1f4;
  undefined4 uStack_1f0;
  float fStack_1ec;
  undefined4 uStack_1e8;
  undefined4 uStack_1e4;
  float fStack_1e0;
  undefined4 uStack_1dc;
  undefined4 uStack_1d8;
  undefined4 uStack_1d4;
  undefined4 auStack_1d0 [16];
  undefined1 auStack_190 [16];
  undefined1 auStack_180 [16];
  undefined1 auStack_170 [16];
  undefined1 auStack_160 [16];
  int iStack_150;
  int iStack_14c;
  int iStack_148;
  int iStack_140;
  int iStack_13c;
  int aiStack_130 [34];
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
  float afStack_80 [32];
  
  auVar21 = _vmr32(in_vf0);
  auVar22 = _vmr32(auVar21);
  auVar23 = _vmr32(auVar22);
  _sqc2(in_vf0);
  _sqc2(auVar21);
  _sqc2(auVar22);
  _sqc2(auVar23);
  iVar8 = iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0;
  fStack_1e0 = *(float *)(iVar8 + 0x380) * 2.0;
  uStack_1dc = 0;
  uStack_1d8 = 0;
  uStack_1d4 = 0x3f800000;
  afStack_80[1] = 0.0;
  afStack_80[2] = 0.0;
  afStack_80[3] = 1.0;
  fStack_1ec = *(float *)(iVar8 + 900) * 2.0;
  uStack_1f0 = 0;
  uStack_1e8 = 0;
  uStack_1e4 = 0x3f800000;
  afStack_80[4] = 0.0;
  afStack_80[6] = 0.0;
  afStack_80[7] = 1.0;
  fStack_1f8 = *(float *)(iVar8 + 0x388) * 2.0;
  uStack_200 = 0;
  uStack_1fc = 0;
  uStack_1f4 = 0x3f800000;
  afStack_80[8] = 0.0;
  afStack_80[9] = 0.0;
  afStack_80[0xb] = 1.0;
  auVar21 = _vmr32(in_vf0);
  auVar22 = _vmr32(auVar21);
  auVar23 = _vmr32(auVar22);
  auStack_160 = _sqc2(in_vf0);
  auStack_170 = _sqc2(auVar21);
  auStack_180 = _sqc2(auVar22);
  auStack_190 = _sqc2(auVar23);
  aiStack_130[0x20] = in_zero_lo;
  aiStack_130[0x21] = in_zero_hi;
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
  afStack_80[0] = fStack_1e0;
  afStack_80[5] = fStack_1ec;
  afStack_80[10] = fStack_1f8;
  uVar19 = GetRad(*(undefined4 *)(iVar8 + 0x174));
  sceVu0RotMatrixY(uVar19,auStack_190,auStack_190);
  RotTransVector(aiStack_130 + 0x20,afStack_80,auStack_190,3);
  for (uVar15 = 0; (int)uVar15 < 8; uVar15 = uVar15 + 1) {
    auVar21 = _lqc2(*(undefined1 (*) [16])(iVar8 + 0x150));
    auVar22 = _lqc2(*(undefined1 (*) [16])(iVar8 + 0x370));
    auVar21 = _vadd(auVar21,auVar22);
    auStack_260 = _sqc2(auVar21);
    __ct__7FVectorFRC7FVector(auStack_210,auStack_260);
    afStack_80[uVar15 * 4] = auStack_210._0_4_;
    afStack_80[uVar15 * 4 + 1] = auStack_210._4_4_;
    afStack_80[uVar15 * 4 + 2] = fStack_208;
    afStack_80[uVar15 * 4 + 3] = fStack_204;
    if ((uVar15 & 1) == 0) {
      auVar21._4_4_ = aiStack_130[0x21];
      auVar21._0_4_ = aiStack_130[0x20];
      auVar21._8_4_ = uStack_a8;
      auVar21._12_4_ = uStack_a4;
      auVar22 = _lqc2(auVar21);
      auVar21 = _lqc2(*(undefined1 (*) [16])(afStack_80 + uVar15 * 4));
      auVar21 = _vsub(auVar21,auVar22);
      auVar21 = _sqc2(auVar21);
      *(undefined1 (*) [16])(afStack_80 + uVar15 * 4) = auVar21;
    }
    else {
      auVar22._4_4_ = aiStack_130[0x21];
      auVar22._0_4_ = aiStack_130[0x20];
      auVar22._8_4_ = uStack_a8;
      auVar22._12_4_ = uStack_a4;
      auVar22 = _lqc2(auVar22);
      auVar21 = _lqc2(*(undefined1 (*) [16])(afStack_80 + uVar15 * 4));
      auVar21 = _vadd(auVar21,auVar22);
      auVar21 = _sqc2(auVar21);
      *(undefined1 (*) [16])(afStack_80 + uVar15 * 4) = auVar21;
    }
    if ((uVar15 & 2) == 0) {
      auVar23._4_4_ = uStack_9c;
      auVar23._0_4_ = uStack_a0;
      auVar23._8_4_ = uStack_98;
      auVar23._12_4_ = uStack_94;
      auVar22 = _lqc2(auVar23);
      auVar21 = _lqc2(*(undefined1 (*) [16])(afStack_80 + uVar15 * 4));
      auVar21 = _vsub(auVar21,auVar22);
      auVar21 = _sqc2(auVar21);
      *(undefined1 (*) [16])(afStack_80 + uVar15 * 4) = auVar21;
    }
    else {
      auVar5._4_4_ = uStack_9c;
      auVar5._0_4_ = uStack_a0;
      auVar5._8_4_ = uStack_98;
      auVar5._12_4_ = uStack_94;
      auVar22 = _lqc2(auVar5);
      auVar21 = _lqc2(*(undefined1 (*) [16])(afStack_80 + uVar15 * 4));
      auVar21 = _vadd(auVar21,auVar22);
      auVar21 = _sqc2(auVar21);
      *(undefined1 (*) [16])(afStack_80 + uVar15 * 4) = auVar21;
    }
    if ((uVar15 & 4) == 0) {
      auVar7._4_4_ = uStack_8c;
      auVar7._0_4_ = uStack_90;
      auVar7._8_4_ = uStack_88;
      auVar7._12_4_ = uStack_84;
      auVar22 = _lqc2(auVar7);
      auVar21 = _lqc2(*(undefined1 (*) [16])(afStack_80 + uVar15 * 4));
      auVar21 = _vsub(auVar21,auVar22);
      auVar21 = _sqc2(auVar21);
      *(undefined1 (*) [16])(afStack_80 + uVar15 * 4) = auVar21;
    }
    else {
      auVar6._4_4_ = uStack_8c;
      auVar6._0_4_ = uStack_90;
      auVar6._8_4_ = uStack_88;
      auVar6._12_4_ = uStack_84;
      auVar22 = _lqc2(auVar6);
      auVar21 = _lqc2(*(undefined1 (*) [16])(afStack_80 + uVar15 * 4));
      auVar21 = _vadd(auVar21,auVar22);
      auVar21 = _sqc2(auVar21);
      *(undefined1 (*) [16])(afStack_80 + uVar15 * 4) = auVar21;
    }
  }
  GetViewScreenMatrix__9GsxCameraFv(auStack_250,uGpffff8598);
  for (iVar8 = 0; iVar8 < 4; iVar8 = iVar8 + 1) {
    auStack_1d0[iVar8 * 4] = *(undefined4 *)(auStack_190 + iVar8 * 0x10);
    auStack_1d0[iVar8 * 4 + 1] = *(undefined4 *)(auStack_190 + iVar8 * 0x10 + 4);
    auStack_1d0[iVar8 * 4 + 2] = *(undefined4 *)(auStack_190 + iVar8 * 0x10 + 8);
    auStack_1d0[iVar8 * 4 + 3] = *(undefined4 *)(auStack_190 + iVar8 * 0x10 + 0xc);
  }
  sceVu0RotTransPersN(aiStack_130,auStack_1d0,afStack_80,8,0);
  bVar4 = false;
  for (iVar8 = 0; iVar8 < 8; iVar8 = iVar8 + 1) {
    if ((((aiStack_130[iVar8 * 4] < 0) || (0x10000 < aiStack_130[iVar8 * 4])) ||
        (aiStack_130[iVar8 * 4 + 1] < 0)) ||
       ((0x10000 < aiStack_130[iVar8 * 4 + 1] || (aiStack_130[iVar8 * 4 + 2] < 0)))) {
      bVar4 = true;
    }
    aiStack_130[iVar8 * 4 + 2] = (int)((float)aiStack_130[iVar8 * 4 + 2] / 16.0);
  }
  iStack_140 = aiStack_130[0];
  iStack_150 = aiStack_130[0];
  iStack_13c = aiStack_130[1];
  iStack_14c = aiStack_130[1];
  iStack_148 = aiStack_130[2];
  for (iVar8 = 1; iVar8 < 8; iVar8 = iVar8 + 1) {
    if (aiStack_130[iVar8 * 4] < iStack_150) {
      iStack_150 = aiStack_130[iVar8 * 4];
    }
    if (aiStack_130[iVar8 * 4 + 1] < iStack_14c) {
      iStack_14c = aiStack_130[iVar8 * 4 + 1];
    }
    if (iStack_140 < aiStack_130[iVar8 * 4]) {
      iStack_140 = aiStack_130[iVar8 * 4];
    }
    if (iStack_13c < aiStack_130[iVar8 * 4 + 1]) {
      iStack_13c = aiStack_130[iVar8 * 4 + 1];
    }
    iStack_148 = iStack_148 + aiStack_130[iVar8 * 4 + 2];
  }
  if (iStack_148 < 0) {
    iStack_148 = iStack_148 + 7;
  }
  iStack_148 = iStack_148 >> 3;
  aiStack_130[0] = iStack_150 + iStack_140;
  if (aiStack_130[0] < 0) {
    aiStack_130[0] = aiStack_130[0] + 1;
  }
  aiStack_130[0] = aiStack_130[0] >> 1;
  aiStack_130[1] = iStack_14c + iStack_13c;
  if (aiStack_130[1] < 0) {
    aiStack_130[1] = aiStack_130[1] + 1;
  }
  aiStack_130[1] = aiStack_130[1] >> 1;
  iVar8 = (iStack_140 - iStack_150) + 1;
  if (iVar8 < 0) {
    iVar8 = (iStack_140 - iStack_150) + 2;
  }
  aiStack_130[5] = (iStack_13c - iStack_14c) + 1;
  if (aiStack_130[5] < 0) {
    aiStack_130[5] = (iStack_13c - iStack_14c) + 2;
  }
  aiStack_130[5] = aiStack_130[5] >> 1;
  aiStack_130[4] = iVar8 >> 1;
  if (iVar8 >> 1 < aiStack_130[5]) {
    aiStack_130[4] = aiStack_130[5];
  }
  iStack_150 = aiStack_130[0] - aiStack_130[4];
  iStack_14c = (int)((float)aiStack_130[1] - (float)aiStack_130[4] * 1.1666666);
  iStack_140 = aiStack_130[0] + aiStack_130[4];
  iStack_13c = (int)((float)aiStack_130[1] + (float)aiStack_130[4] * 1.1666666);
  bVar1 = (*(byte *)(param_1 + 0x40) & 1) == 0;
  uVar15 = (uint)bVar1;
  if (*(int *)(param_1 + uVar15 * 4 + 0x18) == 0) {
    uVar19 = __nwa__FUi(0xf0);
    *(undefined4 *)(param_1 + uVar15 * 4 + 0x18) = uVar19;
    puVar2 = *(undefined4 **)(param_1 + uVar15 * 4 + 0x18);
    *puVar2 = 0x50000000;
    puVar2[1] = *(undefined4 *)
                 (*(int *)(iGpffff86b4 + 0x42fc) +
                  (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42fc) + 10) * 4 + 0xc);
    puVar2[2] = 0;
    puVar2[3] = 0;
    puVar2[4] = 0x6000000d;
    puVar2[5] = 0;
    puVar2[6] = 0;
    puVar2[7] = 0x5000000d;
    *(undefined8 *)(puVar2 + 8) = 0x6000000000000001;
    *(undefined8 *)(puVar2 + 10) = 0x6ee8ee;
    *(undefined8 *)(puVar2 + 0xc) = 1;
    *(undefined8 *)(puVar2 + 0xe) = 0x3f;
    *(undefined8 *)(puVar2 + 0x10) = 0x60;
    *(undefined8 *)(puVar2 + 0x12) = 0x14;
    *(undefined8 *)(puVar2 + 0x14) = 5;
    *(undefined8 *)(puVar2 + 0x16) = 0;
    *(undefined8 *)(puVar2 + 0x18) = 0x43001;
    *(undefined8 *)(puVar2 + 0x1a) = 0x47;
    *(undefined8 *)(puVar2 + 0x1c) = 0x48;
    *(undefined8 *)(puVar2 + 0x1e) = 0x42;
    uVar9 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x42fc),1);
    *(undefined8 *)(puVar2 + 0x20) = uVar9;
    *(undefined8 *)(puVar2 + 0x22) = 0;
    auVar11._8_8_ = in_v1_udw;
    auVar11._0_8_ = 0xa400000000008001;
    auVar3._4_4_ = in_zero_hi;
    auVar3._0_4_ = in_zero_lo;
    auVar3._8_4_ = in_zero_udw;
    auVar3._12_4_ = in_register_0000000c;
    auVar21 = _pcpyld(auVar3,auVar11);
    *(long *)(puVar2 + 0x24) = auVar21._0_8_;
    *(undefined8 *)(puVar2 + 0x26) = 0x4343c3c310;
    *(undefined8 *)(puVar2 + 0x28) = 0x154;
    *(undefined8 *)(puVar2 + 0x2c) = 0;
    *(long *)(puVar2 + 0x30) =
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42fc) + 4) << 4) << 0x10;
    *(long *)(puVar2 + 0x34) =
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42fc) + 2) << 4);
    *(long *)(puVar2 + 0x38) =
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42fc) + 2) << 4) |
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42fc) + 4) << 4) << 0x10;
  }
  iVar8 = *(int *)(param_1 + uVar15 * 4 + 0x18);
  if (bVar4) {
    *(undefined8 *)(iVar8 + 0xb8) = 0x71006f00;
    *(undefined8 *)(iVar8 + 200) = 0x71006f00;
    *(undefined8 *)(iVar8 + 0xd8) = 0x71006f00;
    *(undefined8 *)(iVar8 + 0xe8) = 0x71006f00;
  }
  else {
    if (*(float *)(param_1 + 0x5c) < 0.5) {
      fVar20 = (*(float *)(param_1 + 0x5c) * 196.0) / 0.5;
    }
    else {
      fVar20 = 196.0;
    }
    if (*(float *)(param_1 + 0x5c) < 0.5) {
      uVar12 = 0xff;
      uVar13 = uVar12;
      uVar14 = uVar12;
    }
    else {
      fVar16 = 255.0 - ((*(float *)(param_1 + 0x5c) - 0.5) * 116.0) / 0.5;
      if (2.1474836e+09 <= fVar16) {
        fVar16 = fVar16 - 2.1474836e+09;
      }
      fVar17 = 255.0 - ((*(float *)(param_1 + 0x5c) - 0.5) * 196.0) / 0.5;
      if (2.1474836e+09 <= fVar17) {
        fVar17 = fVar17 - 2.1474836e+09;
      }
      fVar18 = 255.0 - ((*(float *)(param_1 + 0x5c) - 0.5) * 76.0) / 0.5;
      if (2.1474836e+09 <= fVar18) {
        fVar18 = fVar18 - 2.1474836e+09;
      }
      uVar12 = (long)(int)fVar18 & 0xff;
      uVar13 = (long)(int)fVar17 & 0xff;
      uVar14 = (long)(int)fVar16 & 0xff;
    }
    lVar10 = __fixunssfdi(fVar20);
    *(ulong *)(iVar8 + 0xa8) = lVar10 << 0x18 | uVar12 << 0x10 | uVar14 | uVar13 << 8 | 0x100000000;
    *(long *)(iVar8 + 0xb8) = (long)iStack_148 << 0x20 | (long)iStack_150 | (long)iStack_14c << 0x10
    ;
    *(long *)(iVar8 + 200) = (long)iStack_148 << 0x20 | (long)iStack_150 | (long)iStack_13c << 0x10;
    *(long *)(iVar8 + 0xd8) = (long)iStack_148 << 0x20 | (long)iStack_140 | (long)iStack_14c << 0x10
    ;
    *(long *)(iVar8 + 0xe8) = (long)iStack_148 << 0x20 | (long)iStack_140 | (long)iStack_13c << 0x10
    ;
  }
  *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfe | bVar1;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0051dc50  getPacket__15NormalDeathEfctFv
 * C++: NormalDeathEfct::getPacket()
 * size: 0x4c bytes
 * --------------------------------------------------------------------------- */
undefined4 getPacket__15NormalDeathEfctFv(int param_1)

{
  (**(code **)(*(int *)(param_1 + 0x14) + 0x38))();
  return *(undefined4 *)(param_1 + (*(byte *)(param_1 + 0x40) & 1) * 4 + 0x18);
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054af10  EndSet__15NormalDeathEfctFv
 * C++: NormalDeathEfct::EndSet()
 * size: 0x30 bytes
 * --------------------------------------------------------------------------- */
void EndSet__15NormalDeathEfctFv(int param_1)

{
  (**(code **)(*(int *)(param_1 + 0x14) + 0x30))();
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b6f0  @24@getPacket__15NormalDeathEfctFv
 * C++: @24@getPacket__15NormalDeathEfctFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
undefined4 _24_getPacket__15NormalDeathEfctFv(int param_1)

{
  (**(code **)(*(int *)(param_1 + -4) + 0x38))();
  return *(undefined4 *)(param_1 + (*(byte *)(param_1 + 0x28) & 1) * 4);
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b700  @24@__dt__15NormalDeathEfctFv
 * C++: @24@__dt__15NormalDeathEfctFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int * _24___dt__15NormalDeathEfctFv(int *param_1,short param_2)

{
  int *piVar1;
  
  piVar1 = param_1 + -6;
  if (piVar1 != (int *)0x0) {
    param_1[-1] = 0x409f70;
    param_1[4] = 0x409f80;
    param_1[7] = 0x409f90;
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
 * JP: 0x0054b710  @44@__dt__15NormalDeathEfctFv
 * C++: @44@__dt__15NormalDeathEfctFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int _44___dt__15NormalDeathEfctFv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x2c;
  if (iVar1 != 0) {
    *(undefined4 *)(param_1 + -0x18) = 0x409f70;
    *(undefined4 *)(param_1 + -4) = 0x409f80;
    *(undefined4 *)(param_1 + 8) = 0x409f90;
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

