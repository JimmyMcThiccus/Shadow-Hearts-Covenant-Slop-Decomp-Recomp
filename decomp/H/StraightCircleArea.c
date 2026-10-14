/* decomp/H/StraightCircleArea.c — cleaned Ghidra output (SH2JP_BATTLE.BIN, JP Furokuban, base 0x00430a00).
 * 8 function(s). Types: see types.h. Names/gp globals resolved from symbols/SLPM_602.19.syms. */
#include "types.h"

/* ---------------------------------------------------------------------------
 * JP: 0x00539780  __ct__18StraightCircleAreaFiiiff
 * C++: StraightCircleArea::__ct(int, int, int, float, float)
 * size: 0x100 bytes
 * --------------------------------------------------------------------------- */
int __ct__18StraightCircleAreaFiiiff
              (undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4,
              undefined4 param_5,undefined4 param_6)

{
  __ct__6BtlEffFii(param_3,param_4,param_5);
  *(undefined4 *)(param_3 + 0x14) = 0x409b10;
  *(undefined4 *)(param_3 + 0x28) = 0x409b20;
  *(undefined4 *)(param_3 + 0x34) = 0x409b30;
  *(undefined4 *)(param_3 + 0x40) = 0;
  *(undefined4 *)(param_3 + 0x44) = param_4;
  *(undefined4 *)(param_3 + 0x48) = param_5;
  *(undefined4 *)(param_3 + 0x4c) = 9;
  *(undefined4 *)(param_3 + 0x5c) = param_6;
  *(undefined4 *)(param_3 + 0x60) = param_1;
  *(undefined4 *)(param_3 + 100) = param_2;
  *(undefined4 *)(param_3 + 0x1c) = 0;
  *(undefined4 *)(param_3 + 0x18) = 0;
  *(undefined4 *)(param_3 + 0x6c) = 0;
  *(undefined4 *)(param_3 + 0x68) = 0;
  BtlEffEntry__7CBattleFiP6BtlEff(uGpffff86b4,*(undefined4 *)(param_3 + 0x48),param_3);
  return param_3;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00539880  __dt__18StraightCircleAreaFv
 * C++: StraightCircleArea::__dt()
 * size: 0x154 bytes
 * --------------------------------------------------------------------------- */
int __dt__18StraightCircleAreaFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x14) = 0x409b10;
    *(undefined4 *)(param_1 + 0x28) = 0x409b20;
    *(undefined4 *)(param_1 + 0x34) = 0x409b30;
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
 * JP: 0x005399e0  Destruct__18StraightCircleAreaFv
 * C++: StraightCircleArea::Destruct()
 * size: 0x4c bytes
 * --------------------------------------------------------------------------- */
void Destruct__18StraightCircleAreaFv(int param_1)

{
  BtlEffRelease__7CBattleFiP6BtlEff(uGpffff86b4,*(undefined4 *)(param_1 + 0x48),param_1);
  (**(code **)(*(int *)(param_1 + 0x34) + 0xc))();
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00539a30  Polling__18StraightCircleAreaFv
 * C++: StraightCircleArea::Polling()
 * size: 0x14 bytes
 * --------------------------------------------------------------------------- */
undefined8 Polling__18StraightCircleAreaFv(void)

{
  return 0;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00539a50  MakePacket__18StraightCircleAreaFv
 * C++: StraightCircleArea::MakePacket()
 * size: 0x2034 bytes
 * --------------------------------------------------------------------------- */
void MakePacket__18StraightCircleAreaFv(int param_1)

{
  bool bVar1;
  undefined4 *puVar2;
  undefined1 auVar3 [16];
  undefined1 auVar4 [16];
  bool bVar5;
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  undefined1 auVar8 [16];
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  undefined4 uVar9;
  undefined8 uVar10;
  undefined8 in_a0_udw;
  undefined1 auVar11 [16];
  undefined1 auVar12 [16];
  uint uVar13;
  int iVar14;
  int iVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  undefined1 in_vf0 [16];
  undefined1 auVar20 [16];
  undefined1 auVar21 [16];
  undefined1 auVar22 [16];
  undefined1 auStack_12e0 [16];
  undefined1 auStack_12d0 [16];
  undefined1 auStack_12c0 [16];
  undefined1 auStack_12b0 [16];
  undefined1 auStack_12a0 [16];
  undefined1 auStack_1290 [16];
  undefined1 auStack_1280 [8];
  undefined4 uStack_1278;
  undefined4 uStack_1274;
  int aiStack_1270 [4];
  int iStack_1260;
  int iStack_125c;
  int iStack_1258;
  int aiStack_1250 [126];
  int iStack_1058;
  int aiStack_1050 [126];
  int iStack_e58;
  int iStack_e50;
  int iStack_e4c;
  int iStack_e48;
  int iStack_e40;
  int iStack_e3c;
  int iStack_e38;
  int iStack_e30;
  int iStack_e2c;
  int iStack_e28;
  int iStack_e20;
  int iStack_e1c;
  int iStack_e18;
  int iStack_e10;
  int iStack_e0c;
  int iStack_e08;
  int iStack_e00;
  int iStack_dfc;
  int iStack_df8;
  int iStack_df0;
  int iStack_dec;
  int iStack_de8;
  float afStack_de0 [2];
  float fStack_dd8;
  undefined1 auStack_dd0 [16];
  undefined1 auStack_dc0 [16];
  undefined1 auStack_db0 [16];
  undefined1 auStack_da0 [16];
  float afStack_d90 [263];
  undefined4 uStack_974;
  float fStack_970;
  undefined4 uStack_96c;
  float fStack_968;
  undefined4 uStack_964;
  float fStack_960;
  undefined4 uStack_95c;
  float fStack_958;
  undefined4 uStack_954;
  float fStack_950;
  undefined4 uStack_94c;
  float fStack_948;
  undefined4 uStack_944;
  float fStack_940;
  undefined4 uStack_93c;
  float fStack_938;
  undefined4 uStack_934;
  float fStack_930;
  undefined4 uStack_92c;
  float fStack_928;
  undefined4 uStack_924;
  float fStack_920;
  undefined4 uStack_91c;
  float fStack_918;
  undefined4 uStack_914;
  float fStack_910;
  undefined4 uStack_90c;
  float fStack_908;
  undefined4 uStack_904;
  undefined1 auStack_900 [4];
  float fStack_8fc;
  int aiStack_8f0 [4];
  int iStack_8e0;
  int iStack_8dc;
  int iStack_8d8;
  int aiStack_8d0 [126];
  int iStack_6d8;
  int aiStack_6d0 [124];
  float afStack_4e0 [260];
  undefined1 auStack_d0 [4];
  undefined4 uStack_cc;
  undefined4 uStack_c8;
  undefined4 uStack_c4;
  undefined1 auStack_c0 [16];
  float afStack_b0 [2];
  float fStack_a8;
  float fStack_a0;
  undefined4 uStack_9c;
  float fStack_98;
  undefined4 uStack_94;
  undefined4 uStack_90;
  undefined4 uStack_8c;
  undefined8 uStack_88;
  undefined4 auStack_80 [16];
  undefined4 auStack_40 [16];
  
  bVar5 = false;
  GetViewScreenMatrix__9GsxCameraFv(auStack_40,uGpffff8598);
  for (iVar15 = 0; iVar15 < 4; iVar15 = iVar15 + 1) {
    auStack_80[iVar15 * 4] = auStack_40[iVar15 * 4];
    auStack_80[iVar15 * 4 + 1] = auStack_40[iVar15 * 4 + 1];
    auStack_80[iVar15 * 4 + 2] = auStack_40[iVar15 * 4 + 2];
    auStack_80[iVar15 * 4 + 3] = auStack_40[iVar15 * 4 + 3];
  }
  auVar20 = _lqc2(*(undefined1 (*) [16])(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x150));
  auVar21 = _lqc2(*(undefined1 (*) [16])(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x390));
  auVar20 = _vadd(auVar20,auVar21);
  auStack_12a0 = _sqc2(auVar20);
  __ct__7FVectorFRC7FVector(&uStack_90,auStack_12a0);
  uStack_8c = 0;
  auVar20 = _lqc2(*(undefined1 (*) [16])(iGpffff86b4 + *(int *)(param_1 + 0x5c) * 0x4f0 + 0x150));
  auVar21 = _lqc2(*(undefined1 (*) [16])(iGpffff86b4 + *(int *)(param_1 + 0x5c) * 0x4f0 + 0x390));
  auVar20 = _vadd(auVar20,auVar21);
  auStack_12b0 = _sqc2(auVar20);
  __ct__7FVectorFRC7FVector(&fStack_a0,auStack_12b0);
  uStack_9c = 0;
  auVar20._4_4_ = 0;
  auVar20._0_4_ = fStack_a0;
  auVar20._8_4_ = fStack_98;
  auVar20._12_4_ = uStack_94;
  auVar20 = _lqc2(auVar20);
  auVar22._4_4_ = uStack_8c;
  auVar22._0_4_ = uStack_90;
  auVar22._8_8_ = uStack_88;
  auVar21 = _lqc2(auVar22);
  auVar20 = _vsub(auVar20,auVar21);
  auStack_12c0 = _sqc2(auVar20);
  __ct__7FVectorFRC7FVector(afStack_b0,auStack_12c0);
  Normalize__7FVectorFv(afStack_b0);
  __ct__7FVectorFRC7FVector(auStack_c0,afStack_b0);
  __amu__7FVectorFf(*(undefined4 *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x3b0),auStack_c0
                 );
  auVar7._4_4_ = uStack_8c;
  auVar7._0_4_ = uStack_90;
  auVar7._8_8_ = uStack_88;
  auVar21 = _lqc2(auVar7);
  auVar20 = _lqc2(auStack_c0);
  auVar20 = _vadd(auVar20,auVar21);
  auStack_c0 = _sqc2(auVar20);
  auVar20 = _lqc2(auStack_c0);
  auVar21._4_4_ = uStack_9c;
  auVar21._0_4_ = fStack_a0;
  auVar21._8_4_ = fStack_98;
  auVar21._12_4_ = uStack_94;
  auVar21 = _lqc2(auVar21);
  auVar20 = _vsub(auVar20,auVar21);
  auStack_12d0 = _sqc2(auVar20);
  __ct__7FVectorFRC7FVector(auStack_d0,auStack_12d0);
  uStack_cc = 0;
  fVar16 = (float)Length__7FVectorCFv(auStack_d0);
  if (fVar16 <= *(float *)(param_1 + 100)) {
    fVar16 = 0.0;
    afStack_4e0[0] = fStack_a0;
    afStack_4e0[1] = -0.2;
    afStack_4e0[2] = fStack_98;
    afStack_4e0[3] = 1.0;
    for (iVar15 = 0; iVar15 < 0x20; iVar15 = iVar15 + 1) {
      fVar17 = (float)cosf(fVar16);
      afStack_4e0[(iVar15 + 1) * 4] = fStack_a0 + *(float *)(param_1 + 100) * fVar17;
      afStack_4e0[(iVar15 + 1) * 4 + 1] = -0.2;
      fVar17 = (float)sinf(fVar16);
      afStack_4e0[(iVar15 + 1) * 4 + 2] = fStack_98 - *(float *)(param_1 + 100) * fVar17;
      afStack_4e0[(iVar15 + 1) * 4 + 3] = 1.0;
      fVar17 = (float)cosf(fVar16);
      afStack_4e0[(iVar15 + 0x21) * 4] = fStack_a0 + *(float *)(param_1 + 100) * fVar17;
      afStack_4e0[(iVar15 + 0x21) * 4 + 1] = -30.0;
      fVar17 = (float)sinf(fVar16);
      afStack_4e0[(iVar15 + 0x21) * 4 + 2] = fStack_98 - *(float *)(param_1 + 100) * fVar17;
      afStack_4e0[(iVar15 + 0x21) * 4 + 3] = 1.0;
      fVar16 = fVar16 + 0.19634955;
      if (3.1415927 <= fVar16) {
        fVar16 = fVar16 - 6.2831855;
      }
    }
    sceVu0RotTransPersN(aiStack_8f0,auStack_80,afStack_4e0,0x41,0);
    iVar15 = 0;
    for (iVar14 = 0; iVar14 < 0x41; iVar14 = iVar14 + 1) {
      if (iVar14 == 0) {
        if ((((aiStack_8f0[0] < 0) || (0x10000 < aiStack_8f0[0])) || (aiStack_8f0[1] < 0)) ||
           ((0x10000 < aiStack_8f0[1] || (aiStack_8f0[2] < 0)))) {
          bVar5 = true;
        }
        iVar15 = (int)((float)aiStack_8f0[2] / 16.0);
        aiStack_8f0[2] = iVar15;
      }
      else {
        aiStack_8f0[iVar14 * 4 + 2] = (int)((float)aiStack_8f0[iVar14 * 4 + 2] / 16.0);
      }
    }
    *(int *)(param_1 + 0x50) = iVar15;
    bVar1 = (*(byte *)(param_1 + 0x40) & 1) == 0;
    uVar13 = (uint)bVar1;
    if ((*(int *)(param_1 + uVar13 * 4 + 0x18) != 0) &&
       (*(int *)(param_1 + uVar13 * 4 + 0x68) != 0x5f)) {
      __dla__FPv(*(undefined4 *)(param_1 + uVar13 * 4 + 0x18));
      *(undefined4 *)(param_1 + uVar13 * 4 + 0x18) = 0;
      *(undefined4 *)(param_1 + uVar13 * 4 + 0x68) = 0;
    }
    if (*(int *)(param_1 + uVar13 * 4 + 0x18) == 0) {
      uVar9 = __nwa__FUi(0x5f0);
      *(undefined4 *)(param_1 + uVar13 * 4 + 0x18) = uVar9;
      *(undefined4 *)(param_1 + uVar13 * 4 + 0x68) = 0x5f;
      iVar15 = *(int *)(param_1 + uVar13 * 4 + 0x18);
      *(undefined8 *)(iVar15 + 0x10) = 0x2000000000000001;
      *(undefined8 *)(iVar15 + 0x18) = 0xee;
      *(undefined8 *)(iVar15 + 0x20) = 0x53001;
      *(undefined8 *)(iVar15 + 0x28) = 0x47;
      *(undefined8 *)(iVar15 + 0x30) = 0x44;
      *(undefined8 *)(iVar15 + 0x38) = 0x42;
      *(undefined8 *)(iVar15 + 0x40) = 0x6400000000000001;
      *(undefined8 *)(iVar15 + 0x48) = 0xc1c1f0;
      *(undefined8 *)(iVar15 + 0x50) = 0x4d;
      *(undefined8 *)(iVar15 + 0x58) = 0;
      *(undefined8 *)(iVar15 + 0x60) = 0x10020a0ff;
      *(undefined8 *)(iVar15 + 0x70) = 0x17020a0ff;
      *(undefined8 *)(iVar15 + 0x80) = 0x2400000000000010;
      *(undefined8 *)(iVar15 + 0x88) = 0x44;
      *(undefined8 *)(iVar15 + 400) = 0x6400000000000001;
      *(undefined8 *)(iVar15 + 0x198) = 0xc1c1f0;
      *(undefined8 *)(iVar15 + 0x1a0) = 0x4c;
      *(undefined8 *)(iVar15 + 0x1a8) = 0;
      *(undefined8 *)(iVar15 + 0x1b0) = 0x11080c0ff;
      *(undefined8 *)(iVar15 + 0x1c0) = 0x13080c0ff;
      *(undefined8 *)(iVar15 + 0x1d0) = 0x4400000000008020;
      *(undefined8 *)(iVar15 + 0x1d8) = 0x4141;
      for (iVar14 = 0; iVar14 < 0x20; iVar14 = iVar14 + 1) {
        *(undefined8 *)(iVar15 + (iVar14 * 2 + 0x1e) * 0x10) = 0x11080c0ff;
        *(undefined8 *)(iVar15 + (iVar14 * 2 + 0x1f) * 0x10) = 0x13080c0ff;
      }
    }
    puVar2 = *(undefined4 **)(param_1 + uVar13 * 4 + 0x18);
    if (bVar5) {
      *(undefined4 **)(param_1 + 0x54) = puVar2;
      *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfe | bVar1;
    }
    else {
      *puVar2 = 0x1000005d;
      puVar2[1] = 0;
      puVar2[2] = 0x11000000;
      puVar2[3] = 0x5000005d;
      *(long *)(puVar2 + 0x1a) =
           (long)aiStack_8f0[2] << 0x20 | (long)aiStack_8f0[0] | (long)aiStack_8f0[1] << 0x10;
      *(long *)(puVar2 + 0x1e) =
           (long)iStack_8d8 << 0x20 | (long)iStack_8e0 | (long)iStack_8dc << 0x10;
      for (iVar15 = 0; iVar15 < 0xf; iVar15 = iVar15 + 1) {
        *(long *)(puVar2 + (iVar15 + 9) * 4) =
             (long)aiStack_8f0[(iVar15 * 2 + 2) * 4 + 2] << 0x20 |
             (long)aiStack_8f0[(iVar15 * 2 + 2) * 4] |
             (long)aiStack_8f0[(iVar15 * 2 + 2) * 4 + 1] << 0x10;
        *(long *)(puVar2 + (iVar15 + 9) * 4 + 2) =
             (long)aiStack_8f0[(iVar15 * 2 + 3) * 4 + 2] << 0x20 |
             (long)aiStack_8f0[(iVar15 * 2 + 3) * 4] |
             (long)aiStack_8f0[(iVar15 * 2 + 3) * 4 + 1] << 0x10;
      }
      *(long *)(puVar2 + 0x60) =
           (long)aiStack_8d0[0x7a] << 0x20 |
           (long)aiStack_8d0[0x78] | (long)aiStack_8d0[0x79] << 0x10;
      *(long *)(puVar2 + 0x62) =
           (long)iStack_8d8 << 0x20 | (long)iStack_8e0 | (long)iStack_8dc << 0x10;
      *(long *)(puVar2 + 0x6e) =
           (long)iStack_6d8 << 0x20 | (long)aiStack_8d0[0x7c] | (long)aiStack_8d0[0x7d] << 0x10;
      *(long *)(puVar2 + 0x72) =
           (long)iStack_8d8 << 0x20 | (long)iStack_8e0 | (long)iStack_8dc << 0x10;
      for (iVar15 = 0; iVar15 < 0x1f; iVar15 = iVar15 + 1) {
        *(long *)(puVar2 + (iVar15 * 2 + 0x1e) * 4 + 2) =
             (long)aiStack_8f0[(iVar15 + 0x22) * 4 + 2] << 0x20 |
             (long)aiStack_8f0[(iVar15 + 0x22) * 4] |
             (long)aiStack_8f0[(iVar15 + 0x22) * 4 + 1] << 0x10;
        *(long *)(puVar2 + (iVar15 * 2 + 0x1f) * 4 + 2) =
             (long)aiStack_8f0[(iVar15 + 2) * 4 + 2] << 0x20 |
             (long)aiStack_8f0[(iVar15 + 2) * 4] | (long)aiStack_8f0[(iVar15 + 2) * 4 + 1] << 0x10;
      }
      *(long *)(puVar2 + 0x172) =
           (long)iStack_6d8 << 0x20 | (long)aiStack_8d0[0x7c] | (long)aiStack_8d0[0x7d] << 0x10;
      *(long *)(puVar2 + 0x176) =
           (long)iStack_8d8 << 0x20 | (long)iStack_8e0 | (long)iStack_8dc << 0x10;
      *(undefined4 **)(param_1 + 0x54) = puVar2 + 0x178;
      *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfe | bVar1;
    }
  }
  else {
    fVar17 = (float)asinf(*(float *)(param_1 + 0x60) / *(float *)(param_1 + 100));
    auVar8._4_4_ = uStack_8c;
    auVar8._0_4_ = uStack_90;
    auVar8._8_8_ = uStack_88;
    auVar20 = _lqc2(auVar8);
    auVar6._4_4_ = uStack_9c;
    auVar6._0_4_ = fStack_a0;
    auVar6._8_4_ = fStack_98;
    auVar6._12_4_ = uStack_94;
    auVar21 = _lqc2(auVar6);
    auVar20 = _vsub(auVar20,auVar21);
    auStack_12e0 = _sqc2(auVar20);
    __ct__7FVectorFRC7FVector(auStack_1280,auStack_12e0);
    uStack_c8 = uStack_1278;
    uStack_c4 = uStack_1274;
    uStack_cc = 0;
    uVar10 = __ct__7FVectorFRC7FVector(auStack_1290,auStack_d0);
    Get3DAngleRad__F7FVector(auStack_900,uVar10);
    afStack_d90[0] = fStack_a0;
    afStack_d90[1] = -0.2;
    afStack_d90[2] = fStack_98;
    afStack_d90[3] = 1.0;
    for (fVar19 = (-fStack_8fc - 1.5707964) + fVar17; 3.1415927 <= fVar19;
        fVar19 = fVar19 - 6.2831855) {
    }
    for (; fVar19 < -3.1415927; fVar19 = fVar19 + 6.2831855) {
    }
    for (iVar15 = 0; iVar15 < 0x20; iVar15 = iVar15 + 1) {
      fVar18 = (float)cosf(fVar19);
      afStack_d90[(iVar15 + 1) * 4] = fStack_a0 + *(float *)(param_1 + 100) * fVar18;
      afStack_d90[(iVar15 + 1) * 4 + 1] = -0.2;
      fVar18 = (float)sinf(fVar19);
      afStack_d90[(iVar15 + 1) * 4 + 2] = fStack_98 - *(float *)(param_1 + 100) * fVar18;
      afStack_d90[(iVar15 + 1) * 4 + 3] = 1.0;
      fVar18 = (float)cosf(fVar19);
      afStack_d90[(iVar15 + 0x21) * 4] = fStack_a0 + *(float *)(param_1 + 100) * fVar18;
      afStack_d90[(iVar15 + 0x21) * 4 + 1] = -30.0;
      fVar18 = (float)sinf(fVar19);
      afStack_d90[(iVar15 + 0x21) * 4 + 2] = fStack_98 - *(float *)(param_1 + 100) * fVar18;
      afStack_d90[(iVar15 + 0x21) * 4 + 3] = 1.0;
      fVar19 = fVar19 + (6.2831855 - fVar17 * 2.0) / 31.0;
      if (3.1415927 <= fVar19) {
        fVar19 = fVar19 - 6.2831855;
      }
    }
    auVar20 = _vmr32(in_vf0);
    auVar21 = _vmr32(auVar20);
    auVar22 = _vmr32(auVar21);
    _sqc2(in_vf0);
    _sqc2(auVar20);
    _sqc2(auVar21);
    _sqc2(auVar22);
    auVar20 = _vmr32(in_vf0);
    auVar21 = _vmr32(auVar20);
    auVar22 = _vmr32(auVar21);
    auStack_da0 = _sqc2(in_vf0);
    auStack_db0 = _sqc2(auVar20);
    auStack_dc0 = _sqc2(auVar21);
    auStack_dd0 = _sqc2(auVar22);
    sceVu0RotMatrixY(0xbfc90fdb,auStack_dd0,auStack_dd0);
    ApplyMatrix__6MatrixCFRC7FVector(afStack_de0,auStack_dd0,afStack_b0);
    afStack_d90[0x104] = (float)auStack_c0._0_4_ + afStack_de0[0] * *(float *)(param_1 + 0x60);
    afStack_d90[0x105] = -0.2;
    afStack_d90[0x106] = (float)auStack_c0._8_4_ + fStack_dd8 * *(float *)(param_1 + 0x60);
    uStack_974 = 0x3f800000;
    fStack_970 = (float)auStack_c0._0_4_ - afStack_de0[0] * *(float *)(param_1 + 0x60);
    uStack_96c = 0xbe4ccccd;
    fStack_968 = (float)auStack_c0._8_4_ - fStack_dd8 * *(float *)(param_1 + 0x60);
    uStack_964 = 0x3f800000;
    if (*(float *)(param_1 + 100) + 10.0 < fVar16) {
      fStack_960 = (float)auStack_c0._0_4_ + afStack_b0[0] * 10.0 +
                   afStack_de0[0] * *(float *)(param_1 + 0x60);
      fStack_958 = (float)auStack_c0._8_4_ + fStack_a8 * 10.0 +
                   fStack_dd8 * *(float *)(param_1 + 0x60);
      fStack_950 = ((float)auStack_c0._0_4_ + afStack_b0[0] * 10.0) -
                   afStack_de0[0] * *(float *)(param_1 + 0x60);
      fStack_948 = ((float)auStack_c0._8_4_ + fStack_a8 * 10.0) -
                   fStack_dd8 * *(float *)(param_1 + 0x60);
    }
    else {
      fStack_960 = afStack_d90[4];
      fStack_958 = afStack_d90[6];
      fStack_950 = afStack_d90[0x80];
      fStack_948 = afStack_d90[0x82];
    }
    uStack_944 = 0x3f800000;
    uStack_94c = 0xbe4ccccd;
    uStack_954 = 0x3f800000;
    uStack_95c = 0xbe4ccccd;
    uStack_93c = 0xc1f00000;
    uStack_934 = 0x3f800000;
    uStack_92c = 0xc1f00000;
    uStack_924 = 0x3f800000;
    fStack_920 = fStack_960;
    uStack_91c = 0xc1f00000;
    fStack_918 = fStack_958;
    uStack_914 = 0x3f800000;
    fStack_910 = fStack_950;
    uStack_90c = 0xc1f00000;
    fStack_908 = fStack_948;
    uStack_904 = 0x3f800000;
    fStack_940 = afStack_d90[0x104];
    fStack_938 = afStack_d90[0x106];
    fStack_930 = fStack_970;
    fStack_928 = fStack_968;
    sceVu0RotTransPersN(aiStack_1270,auStack_80,afStack_d90,0x49,0);
    iVar15 = 0;
    for (iVar14 = 0; iVar14 < 0x49; iVar14 = iVar14 + 1) {
      if (iVar14 == 0) {
        if ((((aiStack_1270[0] < 0) || (0x10000 < aiStack_1270[0])) || (aiStack_1270[1] < 0)) ||
           ((0x10000 < aiStack_1270[1] || (aiStack_1270[2] < 0)))) {
          bVar5 = true;
        }
        iVar15 = (int)((float)aiStack_1270[2] / 16.0);
        aiStack_1270[2] = iVar15;
      }
      else {
        aiStack_1270[iVar14 * 4 + 2] = (int)((float)aiStack_1270[iVar14 * 4 + 2] / 16.0);
      }
    }
    *(int *)(param_1 + 0x50) = iVar15;
    bVar1 = (*(byte *)(param_1 + 0x40) & 1) == 0;
    uVar13 = (uint)bVar1;
    if ((*(int *)(param_1 + uVar13 * 4 + 0x18) != 0) &&
       (*(int *)(param_1 + uVar13 * 4 + 0x68) != 0x70)) {
      __dla__FPv(*(undefined4 *)(param_1 + uVar13 * 4 + 0x18));
      *(undefined4 *)(param_1 + uVar13 * 4 + 0x18) = 0;
      *(undefined4 *)(param_1 + uVar13 * 4 + 0x68) = 0;
    }
    if (*(int *)(param_1 + uVar13 * 4 + 0x18) == 0) {
      uVar9 = __nwa__FUi(0x700);
      *(undefined4 *)(param_1 + uVar13 * 4 + 0x18) = uVar9;
      *(undefined4 *)(param_1 + uVar13 * 4 + 0x68) = 0x70;
      iVar15 = *(int *)(param_1 + uVar13 * 4 + 0x18);
      *(undefined8 *)(iVar15 + 0x10) = 0x2000000000000001;
      *(undefined8 *)(iVar15 + 0x18) = 0xee;
      *(undefined8 *)(iVar15 + 0x20) = 0x53001;
      *(undefined8 *)(iVar15 + 0x28) = 0x47;
      *(undefined8 *)(iVar15 + 0x30) = 0x44;
      *(undefined8 *)(iVar15 + 0x38) = 0x42;
      *(undefined8 *)(iVar15 + 0x40) = 0x6400000000000001;
      *(undefined8 *)(iVar15 + 0x48) = 0xc1c1f0;
      *(undefined8 *)(iVar15 + 0x50) = 0x4d;
      *(undefined8 *)(iVar15 + 0x58) = 0;
      *(undefined8 *)(iVar15 + 0x60) = 0x10020a0ff;
      *(undefined8 *)(iVar15 + 0x70) = 0x17020a0ff;
      *(undefined8 *)(iVar15 + 0x80) = 0x2400000000000010;
      *(undefined8 *)(iVar15 + 0x88) = 0x44;
      *(undefined8 *)(iVar15 + 400) = 0x6400000000000001;
      *(undefined8 *)(iVar15 + 0x198) = 0xc1c1f0;
      *(undefined8 *)(iVar15 + 0x1a0) = 0x4c;
      *(undefined8 *)(iVar15 + 0x1a8) = 0;
      *(undefined8 *)(iVar15 + 0x1b0) = 0x11080c0ff;
      *(undefined8 *)(iVar15 + 0x1c0) = 0x13080c0ff;
      *(undefined8 *)(iVar15 + 0x1d0) = 0x440000000000001f;
      *(undefined8 *)(iVar15 + 0x1d8) = 0x4141;
      for (iVar14 = 0; iVar14 < 0x1f; iVar14 = iVar14 + 1) {
        *(undefined8 *)(iVar15 + (iVar14 * 2 + 0x1e) * 0x10) = 0x11080c0ff;
        *(undefined8 *)(iVar15 + (iVar14 * 2 + 0x1f) * 0x10) = 0x13080c0ff;
      }
      auVar11._8_8_ = in_a0_udw;
      auVar11._0_8_ = 0xa400000000000001;
      auVar3._4_4_ = in_zero_hi;
      auVar3._0_4_ = in_zero_lo;
      auVar3._8_4_ = in_zero_udw;
      auVar3._12_4_ = in_register_0000000c;
      auVar20 = _pcpyld(auVar3,auVar11);
      *(long *)(iVar15 + 0x5c0) = auVar20._0_8_;
      auVar12._8_8_ = auVar20._8_8_;
      *(undefined8 *)(iVar15 + 0x5c8) = 0x4444f1cc10;
      *(undefined8 *)(iVar15 + 0x5d0) = 0x4c;
      *(undefined8 *)(iVar15 + 0x5d8) = 0x10020a0ff;
      *(undefined8 *)(iVar15 + 0x5f0) = 0x17020a0ff;
      *(undefined8 *)(iVar15 + 0x5f8) = 0;
      auVar12._0_8_ = 0xc400000000008002;
      auVar4._4_4_ = in_zero_hi;
      auVar4._0_4_ = in_zero_lo;
      auVar4._8_4_ = in_zero_udw;
      auVar4._12_4_ = in_register_0000000c;
      auVar20 = _pcpyld(auVar4,auVar12);
      *(long *)(iVar15 + 0x620) = auVar20._0_8_;
      *(undefined8 *)(iVar15 + 0x628) = 0x41414141c1c1;
      *(undefined8 *)(iVar15 + 0x630) = 0x10080c0ff;
      *(undefined8 *)(iVar15 + 0x640) = 0x10080c0ff;
      *(undefined8 *)(iVar15 + 0x650) = 0x11080c0ff;
      *(undefined8 *)(iVar15 + 0x660) = 0x13080c0ff;
      *(undefined8 *)(iVar15 + 0x670) = 0x11080c0ff;
      *(undefined8 *)(iVar15 + 0x680) = 0x13080c0ff;
      *(undefined8 *)(iVar15 + 0x690) = 0x10080c0ff;
      *(undefined8 *)(iVar15 + 0x6a0) = 0x10080c0ff;
      *(undefined8 *)(iVar15 + 0x6b0) = 0x11080c0ff;
      *(undefined8 *)(iVar15 + 0x6c0) = 0x13080c0ff;
      *(undefined8 *)(iVar15 + 0x6d0) = 0x11080c0ff;
      *(undefined8 *)(iVar15 + 0x6e0) = 0x13080c0ff;
    }
    puVar2 = *(undefined4 **)(param_1 + uVar13 * 4 + 0x18);
    if (bVar5) {
      *(undefined4 **)(param_1 + 0x54) = puVar2;
      *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfe | bVar1;
    }
    else {
      *puVar2 = 0x1000006e;
      puVar2[1] = 0;
      puVar2[2] = 0x11000000;
      puVar2[3] = 0x5000006e;
      *(long *)(puVar2 + 0x1a) =
           (long)aiStack_1270[2] << 0x20 | (long)aiStack_1270[0] | (long)aiStack_1270[1] << 0x10;
      *(long *)(puVar2 + 0x1e) =
           (long)iStack_1258 << 0x20 | (long)iStack_1260 | (long)iStack_125c << 0x10;
      for (iVar15 = 0; iVar15 < 0xf; iVar15 = iVar15 + 1) {
        *(long *)(puVar2 + (iVar15 + 9) * 4) =
             (long)aiStack_1270[(iVar15 * 2 + 2) * 4 + 2] << 0x20 |
             (long)aiStack_1270[(iVar15 * 2 + 2) * 4] |
             (long)aiStack_1270[(iVar15 * 2 + 2) * 4 + 1] << 0x10;
        *(long *)(puVar2 + (iVar15 + 9) * 4 + 2) =
             (long)aiStack_1270[(iVar15 * 2 + 3) * 4 + 2] << 0x20 |
             (long)aiStack_1270[(iVar15 * 2 + 3) * 4] |
             (long)aiStack_1270[(iVar15 * 2 + 3) * 4 + 1] << 0x10;
      }
      *(long *)(puVar2 + 0x60) =
           (long)aiStack_1250[0x7a] << 0x20 |
           (long)aiStack_1250[0x78] | (long)aiStack_1250[0x79] << 0x10;
      *(long *)(puVar2 + 0x62) =
           (long)iStack_1258 << 0x20 | (long)iStack_1260 | (long)iStack_125c << 0x10;
      *(long *)(puVar2 + 0x6e) =
           (long)iStack_1058 << 0x20 | (long)aiStack_1250[0x7c] | (long)aiStack_1250[0x7d] << 0x10;
      *(long *)(puVar2 + 0x72) =
           (long)iStack_1258 << 0x20 | (long)iStack_1260 | (long)iStack_125c << 0x10;
      for (iVar15 = 0; iVar15 < 0x1f; iVar15 = iVar15 + 1) {
        *(long *)(puVar2 + (iVar15 * 2 + 0x1e) * 4 + 2) =
             (long)aiStack_1270[(iVar15 + 0x22) * 4 + 2] << 0x20 |
             (long)aiStack_1270[(iVar15 + 0x22) * 4] |
             (long)aiStack_1270[(iVar15 + 0x22) * 4 + 1] << 0x10;
        *(long *)(puVar2 + (iVar15 * 2 + 0x1f) * 4 + 2) =
             (long)aiStack_1270[(iVar15 + 2) * 4 + 2] << 0x20 |
             (long)aiStack_1270[(iVar15 + 2) * 4] | (long)aiStack_1270[(iVar15 + 2) * 4 + 1] << 0x10
        ;
      }
      *(long *)(puVar2 + 0x178) =
           (long)iStack_e58 << 0x20 | (long)aiStack_1050[0x7c] | (long)aiStack_1050[0x7d] << 0x10;
      *(long *)(puVar2 + 0x17a) =
           (long)iStack_e48 << 0x20 | (long)iStack_e50 | (long)iStack_e4c << 0x10;
      *(long *)(puVar2 + 0x180) =
           (long)iStack_e38 << 0x20 | (long)iStack_e40 | (long)iStack_e3c << 0x10;
      *(long *)(puVar2 + 0x182) =
           (long)iStack_e28 << 0x20 | (long)iStack_e30 | (long)iStack_e2c << 0x10;
      *(long *)(puVar2 + 0x184) =
           (long)iStack_1258 << 0x20 | (long)iStack_1260 | (long)iStack_125c << 0x10;
      *(long *)(puVar2 + 0x186) =
           (long)aiStack_1250[0x7a] << 0x20 |
           (long)aiStack_1250[0x78] | (long)aiStack_1250[0x79] << 0x10;
      *(long *)(puVar2 + 0x18e) =
           (long)iStack_e18 << 0x20 | (long)iStack_e20 | (long)iStack_e1c << 0x10;
      *(long *)(puVar2 + 0x192) =
           (long)iStack_e58 << 0x20 | (long)aiStack_1050[0x7c] | (long)aiStack_1050[0x7d] << 0x10;
      *(long *)(puVar2 + 0x196) =
           (long)iStack_df8 << 0x20 | (long)iStack_e00 | (long)iStack_dfc << 0x10;
      *(long *)(puVar2 + 0x19a) =
           (long)iStack_e38 << 0x20 | (long)iStack_e40 | (long)iStack_e3c << 0x10;
      *(long *)(puVar2 + 0x19e) =
           (long)iStack_1058 << 0x20 | (long)aiStack_1250[0x7c] | (long)aiStack_1250[0x7d] << 0x10;
      *(long *)(puVar2 + 0x1a2) =
           (long)iStack_1258 << 0x20 | (long)iStack_1260 | (long)iStack_125c << 0x10;
      *(long *)(puVar2 + 0x1a6) =
           (long)iStack_e08 << 0x20 | (long)iStack_e10 | (long)iStack_e0c << 0x10;
      *(long *)(puVar2 + 0x1aa) =
           (long)iStack_e48 << 0x20 | (long)iStack_e50 | (long)iStack_e4c << 0x10;
      *(long *)(puVar2 + 0x1ae) =
           (long)iStack_de8 << 0x20 | (long)iStack_df0 | (long)iStack_dec << 0x10;
      *(long *)(puVar2 + 0x1b2) =
           (long)iStack_e28 << 0x20 | (long)iStack_e30 | (long)iStack_e2c << 0x10;
      *(long *)(puVar2 + 0x1b6) =
           (long)aiStack_1050[0x7a] << 0x20 |
           (long)aiStack_1050[0x78] | (long)aiStack_1050[0x79] << 0x10;
      *(long *)(puVar2 + 0x1ba) =
           (long)aiStack_1250[0x7a] << 0x20 |
           (long)aiStack_1250[0x78] | (long)aiStack_1250[0x79] << 0x10;
      *(undefined4 **)(param_1 + 0x54) = puVar2 + 0x1bc;
      *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfe | bVar1;
    }
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054ade0  EndSet__18StraightCircleAreaFv
 * C++: StraightCircleArea::EndSet()
 * size: 0x10 bytes
 * --------------------------------------------------------------------------- */
void EndSet__18StraightCircleAreaFv(void)

{
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b8d0  @24@__dt__18StraightCircleAreaFv
 * C++: @24@__dt__18StraightCircleAreaFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int * _24___dt__18StraightCircleAreaFv(int *param_1,short param_2)

{
  int *piVar1;
  
  piVar1 = param_1 + -6;
  if (piVar1 != (int *)0x0) {
    param_1[-1] = 0x409b10;
    param_1[4] = 0x409b20;
    param_1[7] = 0x409b30;
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
 * JP: 0x0054b8e0  @44@__dt__18StraightCircleAreaFv
 * C++: @44@__dt__18StraightCircleAreaFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int _44___dt__18StraightCircleAreaFv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x2c;
  if (iVar1 != 0) {
    *(undefined4 *)(param_1 + -0x18) = 0x409b10;
    *(undefined4 *)(param_1 + -4) = 0x409b20;
    *(undefined4 *)(param_1 + 8) = 0x409b30;
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

