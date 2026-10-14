/* decomp/H/WpnBoxAddAttribute1.c — cleaned Ghidra output (SH2JP_BATTLE.BIN, JP Furokuban, base 0x00430a00).
 * 8 function(s). Types: see types.h. Names/gp globals resolved from symbols/SLPM_602.19.syms. */
#include "types.h"

/* ---------------------------------------------------------------------------
 * JP: 0x0052ce30  __ct__19WpnBoxAddAttribute1Fiii
 * C++: WpnBoxAddAttribute1::__ct(int, int, int)
 * size: 0x208 bytes
 * --------------------------------------------------------------------------- */
int __ct__19WpnBoxAddAttribute1Fiii
              (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  int iVar1;
  undefined4 *puVar2;
  
  __ct__6BtlEffFii(param_1,param_2,param_3);
  *(undefined4 *)(param_1 + 0x14) = 0x409cf0;
  *(undefined4 *)(param_1 + 0x28) = 0x409d00;
  *(undefined4 *)(param_1 + 0x34) = 0x409d10;
  puVar2 = (undefined4 *)(param_1 + 0x70);
  do {
    *puVar2 = in_zero_lo;
    puVar2[1] = in_zero_hi;
    puVar2[2] = in_zero_udw;
    puVar2[3] = in_register_0000000c;
    puVar2 = puVar2 + 4;
  } while (puVar2 != (undefined4 *)(param_1 + 0xf0));
  puVar2 = (undefined4 *)(param_1 + 0x200);
  do {
    *puVar2 = in_zero_lo;
    puVar2[1] = in_zero_hi;
    puVar2[2] = in_zero_udw;
    puVar2[3] = in_register_0000000c;
    puVar2 = puVar2 + 4;
  } while (puVar2 != (undefined4 *)(param_1 + 0x400));
  *(undefined4 *)(param_1 + 0x40) = 0;
  *(undefined4 *)(param_1 + 0x44) = param_2;
  *(undefined4 *)(param_1 + 0x48) = param_3;
  *(undefined4 *)(param_1 + 0x4c) = 6;
  *(undefined4 *)(param_1 + 0x5c) = 0;
  *(undefined4 *)(param_1 + 0x60) = param_4;
  *(undefined4 *)(param_1 + 0xf0) = 0;
  *(undefined4 *)(param_1 + 0xf4) = 0;
  *(undefined4 *)(param_1 + 0xf8) = 0;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  *(undefined4 *)(param_1 + 0x18) = 0;
  for (iVar1 = 0; iVar1 < 0x20; iVar1 = iVar1 + 1) {
    *(undefined2 *)(param_1 + iVar1 * 2 + 0xfc) = 0;
  }
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
 * JP: 0x0052d040  __dt__19WpnBoxAddAttribute1Fv
 * C++: WpnBoxAddAttribute1::__dt()
 * size: 0x154 bytes
 * --------------------------------------------------------------------------- */
int __dt__19WpnBoxAddAttribute1Fv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x14) = 0x409cf0;
    *(undefined4 *)(param_1 + 0x28) = 0x409d00;
    *(undefined4 *)(param_1 + 0x34) = 0x409d10;
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
 * JP: 0x0052d1a0  Destruct__19WpnBoxAddAttribute1Fv
 * C++: WpnBoxAddAttribute1::Destruct()
 * size: 0xcc bytes
 * --------------------------------------------------------------------------- */
void Destruct__19WpnBoxAddAttribute1Fv(int param_1)

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
 * JP: 0x0052d270  Polling__19WpnBoxAddAttribute1Fv
 * C++: WpnBoxAddAttribute1::Polling()
 * size: 0x674 bytes
 * --------------------------------------------------------------------------- */
undefined8 Polling__19WpnBoxAddAttribute1Fv(int param_1)

{
  short sVar1;
  float in_zero_lo;
  float in_zero_hi;
  float in_zero_udw;
  undefined4 in_register_0000000c;
  int iVar2;
  int iVar3;
  float fVar4;
  undefined1 auStack_90 [8];
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined1 auStack_80 [8];
  undefined4 uStack_78;
  undefined4 uStack_74;
  float fStack_70;
  float fStack_6c;
  float fStack_68;
  undefined4 uStack_64;
  undefined1 auStack_60 [64];
  float fStack_20;
  float fStack_1c;
  float fStack_18;
  float fStack_14;
  undefined8 uStack_10;
  
  fStack_20 = (float)uRam00650db0;
  fStack_1c = (float)((ulong)uRam00650db0 >> 0x20);
  fStack_18 = fRam00650db8;
  fStack_14 = fRam00650dbc;
  uStack_10 = uRam00650dc0;
  fVar4 = *(float *)(iGpffff86b4 + 0x38);
  if ((*(byte *)(iGpffff86b4 + 0x24) & 1) != 0) {
    fVar4 = 0.0;
  }
  *(float *)(param_1 + 0xf8) = *(float *)(param_1 + 0xf8) + fVar4 * 6.2831855 * 0.75;
  if (3.1415927 <= *(float *)(param_1 + 0xf8)) {
    *(float *)(param_1 + 0xf8) = *(float *)(param_1 + 0xf8) - 6.2831855;
  }
  if (((*(int *)(param_1 + 0x5c) != 1) && (*(int *)(param_1 + 0x5c) == 0)) &&
     (*(float *)(param_1 + 0xf0) = *(float *)(param_1 + 0xf0) + fVar4 * 2.0,
     1.0 <= *(float *)(param_1 + 0xf0))) {
    *(undefined4 *)(param_1 + 0xf0) = 0x3f800000;
    *(undefined4 *)(param_1 + 0x5c) = 1;
  }
  __ct__6MatrixFRC6Matrix(auStack_60,
                  *(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x144)
                                   + 0x52c) + 0x30) +
                  (uint)*(byte *)(*(int *)(*(int *)(*(int *)(iGpffff86b4 +
                                                             *(int *)(param_1 + 0x48) * 0x4f0 +
                                                            0x144) + 0x52c) + 0xe4) + 0x110) * 0x1f0
                  + (bGpffff8340 & 1) * 0x40);
  *(float *)(param_1 + 0xf4) = *(float *)(param_1 + 0xf4) + fVar4;
  fStack_70 = in_zero_lo;
  fStack_6c = in_zero_hi;
  fStack_68 = in_zero_udw;
  uStack_64 = in_register_0000000c;
  for (iVar3 = 0; iVar3 < 0x20; iVar3 = iVar3 + 1) {
    sVar1 = *(short *)(param_1 + iVar3 * 2 + 0xfc);
    if (sVar1 == 1) {
      iVar2 = param_1 + iVar3 * 4;
      *(float *)(iVar2 + 0x17c) = *(float *)(iVar2 + 0x17c) + fVar4;
      iVar2 = param_1 + iVar3 * 0x10;
      *(float *)(iVar2 + 0x204) = *(float *)(iVar2 + 0x204) - fVar4 * 2.0;
      if (*(float *)(param_1 + iVar3 * 4 + 0x17c) < 0.6666667) {
        *(undefined4 *)(param_1 + iVar3 * 4 + 0x480) = 0x43000000;
      }
      else {
        *(float *)(param_1 + iVar3 * 4 + 0x480) =
             ((1.0 - *(float *)(param_1 + iVar3 * 4 + 0x17c)) / 0.33333334) * 128.0;
      }
      if ((1.0 <= *(float *)(param_1 + iVar3 * 4 + 0x17c)) &&
         (*(undefined2 *)(param_1 + iVar3 * 2 + 0xfc) = 0, 0.06666667 <= *(float *)(param_1 + 0xf4))
         ) {
        *(undefined2 *)(param_1 + iVar3 * 2 + 0xfc) = 1;
        *(undefined4 *)(param_1 + iVar3 * 4 + 0x17c) = 0;
        iVar2 = rand();
        fStack_70 = fStack_14 + (fStack_20 - fStack_14) * ((float)iVar2 / 2.1474836e+09);
        iVar2 = rand();
        fStack_6c = (float)uStack_10 +
                    (fStack_1c - (float)uStack_10) * ((float)iVar2 / 2.1474836e+09);
        iVar2 = rand();
        fStack_68 = uStack_10._4_4_ + (fStack_18 - uStack_10._4_4_) * ((float)iVar2 / 2.1474836e+09)
        ;
        uStack_64 = 0x3f800000;
        ApplyMatrix__6MatrixCFRC7FVector(auStack_90,auStack_60,&fStack_70);
        iVar2 = param_1 + iVar3 * 0x10;
        *(int *)(iVar2 + 0x200) = auStack_90._0_4_;
        *(int *)(iVar2 + 0x204) = auStack_90._4_4_;
        *(undefined4 *)(iVar2 + 0x208) = uStack_88;
        *(undefined4 *)(iVar2 + 0x20c) = uStack_84;
        *(undefined4 *)(param_1 + iVar3 * 4 + 0x400) = 0x3fc00000;
        *(undefined4 *)(param_1 + iVar3 * 4 + 0x480) = 0x3f800000;
        *(float *)(param_1 + 0xf4) = *(float *)(param_1 + 0xf4) - 0.06666667;
      }
    }
    else if ((sVar1 == 0) && (0.06666667 <= *(float *)(param_1 + 0xf4))) {
      *(undefined2 *)(param_1 + iVar3 * 2 + 0xfc) = 1;
      *(undefined4 *)(param_1 + iVar3 * 4 + 0x17c) = 0;
      iVar2 = rand();
      fStack_70 = fStack_14 + (fStack_20 - fStack_14) * ((float)iVar2 / 2.1474836e+09);
      iVar2 = rand();
      fStack_6c = (float)uStack_10 + (fStack_1c - (float)uStack_10) * ((float)iVar2 / 2.1474836e+09)
      ;
      iVar2 = rand();
      fStack_68 = uStack_10._4_4_ + (fStack_18 - uStack_10._4_4_) * ((float)iVar2 / 2.1474836e+09);
      uStack_64 = 0x3f800000;
      ApplyMatrix__6MatrixCFRC7FVector(auStack_80,auStack_60,&fStack_70);
      iVar2 = param_1 + iVar3 * 0x10;
      *(int *)(iVar2 + 0x200) = auStack_80._0_4_;
      *(int *)(iVar2 + 0x204) = auStack_80._4_4_;
      *(undefined4 *)(iVar2 + 0x208) = uStack_78;
      *(undefined4 *)(iVar2 + 0x20c) = uStack_74;
      *(undefined4 *)(param_1 + iVar3 * 4 + 0x400) = 0x3fc00000;
      *(undefined4 *)(param_1 + iVar3 * 4 + 0x480) = 0x3f800000;
      *(float *)(param_1 + 0xf4) = *(float *)(param_1 + 0xf4) - 0.06666667;
    }
  }
  return 0;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0052d8f0  MakePacket__19WpnBoxAddAttribute1Fv
 * C++: WpnBoxAddAttribute1::MakePacket()
 * size: 0xedc bytes
 * --------------------------------------------------------------------------- */
/* WARNING: Removing unreachable block (ram,0x0052e358) */
/* WARNING: Removing unreachable block (ram,0x0052e298) */
/* WARNING: Removing unreachable block (ram,0x0052e418) */

void MakePacket__19WpnBoxAddAttribute1Fv(int param_1)

{
  bool bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  byte bVar7;
  byte bVar8;
  byte bVar9;
  byte bVar10;
  undefined4 *puVar11;
  bool bVar12;
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  int iVar13;
  undefined4 uVar14;
  undefined8 uVar15;
  uint uVar16;
  undefined8 in_v1_udw;
  undefined1 auVar17 [16];
  undefined1 auVar18 [16];
  uint uVar19;
  int iVar20;
  int iVar21;
  float fVar22;
  float fVar23;
  float fVar24;
  undefined1 auVar25 [16];
  undefined1 auStack_11a0 [16];
  undefined1 auStack_1190 [8];
  int iStack_1188;
  int iStack_1184;
  undefined4 uStack_1180;
  undefined4 uStack_117c;
  undefined4 uStack_1178;
  undefined4 uStack_1174;
  undefined4 uStack_1170;
  undefined4 uStack_116c;
  undefined4 uStack_1168;
  undefined4 uStack_1164;
  undefined4 uStack_1160;
  undefined4 uStack_115c;
  undefined4 uStack_1158;
  undefined4 uStack_1154;
  undefined4 uStack_1150;
  undefined4 uStack_114c;
  undefined4 uStack_1148;
  undefined4 uStack_1144;
  undefined4 uStack_1140;
  undefined4 uStack_113c;
  undefined4 uStack_1138;
  undefined4 uStack_1134;
  undefined4 uStack_1130;
  undefined4 uStack_112c;
  undefined4 uStack_1128;
  undefined4 uStack_1124;
  undefined4 uStack_1120;
  undefined4 uStack_111c;
  undefined4 uStack_1118;
  undefined4 uStack_1114;
  undefined4 uStack_1110;
  undefined4 uStack_110c;
  undefined4 uStack_1108;
  undefined4 uStack_1104;
  int aiStack_1100 [1024];
  undefined4 auStack_100 [16];
  undefined8 uStack_c0;
  undefined4 auStack_b8 [14];
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
  
  uStack_1110 = 0xbf800000;
  uStack_110c = 0xbf800000;
  uStack_1108 = 0;
  uStack_1104 = 0x3f800000;
  uStack_40 = 0xbf800000;
  uStack_3c = 0xbf800000;
  uStack_38 = 0;
  uStack_34 = 0x3f800000;
  uStack_1120 = 0xbf800000;
  uStack_111c = 0x3f800000;
  uStack_1118 = 0;
  uStack_1114 = 0x3f800000;
  uStack_30 = 0xbf800000;
  uStack_2c = 0x3f800000;
  uStack_28 = 0;
  uStack_24 = 0x3f800000;
  uStack_1130 = 0x3f800000;
  uStack_112c = 0xbf800000;
  uStack_1128 = 0;
  uStack_1124 = 0x3f800000;
  uStack_20 = 0x3f800000;
  uStack_1c = 0xbf800000;
  uStack_18 = 0;
  uStack_14 = 0x3f800000;
  uStack_1140 = 0x3f800000;
  uStack_113c = 0x3f800000;
  uStack_1138 = 0;
  uStack_1134 = 0x3f800000;
  uStack_10 = 0x3f800000;
  uStack_c = 0x3f800000;
  uStack_8 = 0;
  uStack_4 = 0x3f800000;
  __ct__6MatrixFRC6Matrix(auStack_80,iGpffff8598 + 0x240);
  uStack_50 = 0;
  uStack_4c = 0;
  uStack_48 = 0;
  uStack_44 = 0x3f800000;
  RotTransVector(&uStack_c0,&uStack_40,auStack_80,4);
  GetViewScreenMatrix__9GsxCameraFv(&uStack_1180,iGpffff8598);
  auStack_80[0] = uStack_1180;
  auStack_80[1] = uStack_117c;
  auStack_80[2] = uStack_1178;
  auStack_80[3] = uStack_1174;
  auStack_80[4] = uStack_1170;
  auStack_80[5] = uStack_116c;
  auStack_80[6] = uStack_1168;
  uStack_64 = uStack_1164;
  uStack_60 = uStack_1160;
  uStack_5c = uStack_115c;
  uStack_58 = uStack_1158;
  uStack_54 = uStack_1154;
  uStack_50 = uStack_1150;
  uStack_4c = uStack_114c;
  uStack_48 = uStack_1148;
  uStack_44 = uStack_1144;
  for (iVar21 = 0; iVar21 < 4; iVar21 = iVar21 + 1) {
    auStack_100[iVar21 * 4] = auStack_80[iVar21 * 4];
    auStack_100[iVar21 * 4 + 1] = auStack_80[iVar21 * 4 + 1];
    auStack_100[iVar21 * 4 + 2] = auStack_80[iVar21 * 4 + 2];
    auStack_100[iVar21 * 4 + 3] = auStack_80[iVar21 * 4 + 3];
  }
  for (iVar21 = 0; iVar21 < 0x20; iVar21 = iVar21 + 1) {
    for (iVar20 = 0; iVar20 < 4; iVar20 = iVar20 + 1) {
      uStack_38 = auStack_b8[iVar20 * 4];
      uStack_34 = auStack_b8[iVar20 * 4 + 1];
      uStack_40 = (undefined4)(&uStack_c0)[iVar20 * 2];
      uStack_3c = (undefined4)((ulong)(&uStack_c0)[iVar20 * 2] >> 0x20);
      __amu__7FVectorFf(*(undefined4 *)(param_1 + iVar21 * 4 + 0x400),&uStack_40);
      auVar25 = _lqc2(*(undefined1 (*) [16])(param_1 + iVar21 * 0x10 + 0x200));
      auVar18._4_4_ = uStack_3c;
      auVar18._0_4_ = uStack_40;
      auVar18._8_4_ = uStack_38;
      auVar18._12_4_ = uStack_34;
      auVar18 = _lqc2(auVar18);
      auVar18 = _vadd(auVar25,auVar18);
      auStack_11a0 = _sqc2(auVar18);
      __ct__7FVectorFRC7FVector(auStack_1190,auStack_11a0);
      iVar13 = iVar20 + iVar21 * 4;
      aiStack_1100[iVar13 * 4 + 0x200] = auStack_1190._0_4_;
      aiStack_1100[iVar13 * 4 + 0x201] = auStack_1190._4_4_;
      aiStack_1100[iVar13 * 4 + 0x202] = iStack_1188;
      aiStack_1100[iVar13 * 4 + 0x203] = iStack_1184;
    }
  }
  sceVu0RotTransPersN(aiStack_1100,auStack_100,aiStack_1100 + 0x200,0x80,0);
  bVar12 = true;
  for (uVar19 = 0; (int)uVar19 < 0x80; uVar19 = uVar19 + 1) {
    uVar16 = uVar19 & 3;
    if (((int)uVar19 < 0) && (uVar16 != 0)) {
      uVar16 = uVar16 - 4;
    }
    iVar21 = (int)uVar19 >> 2;
    if (uVar16 == 0) {
      iVar20 = iVar21;
      if ((int)uVar19 < 0) {
        iVar20 = (int)(uVar19 + 3) >> 2;
      }
      *(undefined2 *)(param_1 + iVar20 * 2 + 0x13c) = 0;
    }
    if ((((aiStack_1100[uVar19 * 4] < 0) || (0x10000 < aiStack_1100[uVar19 * 4])) ||
        (aiStack_1100[uVar19 * 4 + 1] < 0)) ||
       ((0x10000 < aiStack_1100[uVar19 * 4 + 1] || (aiStack_1100[uVar19 * 4 + 2] < 0)))) {
      iVar20 = iVar21;
      if ((int)uVar19 < 0) {
        iVar20 = (int)(uVar19 + 3) >> 2;
      }
      *(undefined2 *)(param_1 + iVar20 * 2 + 0x13c) = 1;
    }
    aiStack_1100[uVar19 * 4 + 2] = (int)((float)aiStack_1100[uVar19 * 4 + 2] / 16.0);
    uVar16 = uVar19 & 3;
    if (((int)uVar19 < 0) && (uVar16 != 0)) {
      uVar16 = uVar16 - 4;
    }
    if (uVar16 == 3) {
      if ((int)uVar19 < 0) {
        iVar21 = (int)(uVar19 + 3) >> 2;
      }
      if (*(short *)(param_1 + iVar21 * 2 + 0x13c) == 0) {
        bVar12 = false;
      }
    }
  }
  bVar1 = (*(byte *)(param_1 + 0x40) & 1) == 0;
  uVar19 = (uint)bVar1;
  if (*(int *)(param_1 + uVar19 * 4 + 0x18) == 0) {
    uVar14 = __nwa__FUi(0xaa0);
    *(undefined4 *)(param_1 + uVar19 * 4 + 0x18) = uVar14;
    iVar21 = *(int *)(param_1 + uVar19 * 4 + 0x18);
    *(undefined4 *)(iVar21 + 0x10) = 0x600000a8;
    *(undefined4 *)(iVar21 + 0x14) = 0;
    *(undefined4 *)(iVar21 + 0x18) = 0;
    *(undefined4 *)(iVar21 + 0x1c) = 0x500000a8;
    *(undefined8 *)(iVar21 + 0x20) = 0x6000000000000001;
    *(undefined8 *)(iVar21 + 0x28) = 0xe6e8ee;
    *(undefined8 *)(iVar21 + 0x30) = 1;
    *(undefined8 *)(iVar21 + 0x38) = 0x3f;
    *(undefined8 *)(iVar21 + 0x40) = 0x60;
    *(undefined8 *)(iVar21 + 0x48) = 0x14;
    *(undefined8 *)(iVar21 + 0x50) = 5;
    *(undefined8 *)(iVar21 + 0x58) = 0;
    *(undefined8 *)(iVar21 + 0x60) = 0x53001;
    *(undefined8 *)(iVar21 + 0x68) = 0x47;
    uVar15 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x42f0),1);
    *(undefined8 *)(iVar21 + 0x70) = uVar15;
    *(undefined8 *)(iVar21 + 0x78) = 0;
    *(undefined8 *)(iVar21 + 0x80) = 0x48;
    *(undefined8 *)(iVar21 + 0x88) = 0x42;
    auVar17._8_8_ = in_v1_udw;
    auVar17._0_8_ = 0xa400000000008020;
    auVar25._4_4_ = in_zero_hi;
    auVar25._0_4_ = in_zero_lo;
    auVar25._8_4_ = in_zero_udw;
    auVar25._12_4_ = in_register_0000000c;
    auVar18 = _pcpyld(auVar25,auVar17);
    *(long *)(iVar21 + 0x90) = auVar18._0_8_;
    *(undefined8 *)(iVar21 + 0x98) = 0x4343c3c310;
    for (iVar20 = 0; iVar20 < 0x20; iVar20 = iVar20 + 1) {
      *(undefined8 *)(iVar21 + (iVar20 * 5 + 10) * 0x10) = 0x154;
      *(long *)(iVar21 + (iVar20 * 5 + 0xb) * 0x10) =
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f0) + 2) << 2) |
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f0) + 4) << 2) << 0x10;
      *(long *)(iVar21 + (iVar20 * 5 + 0xc) * 0x10) =
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f0) + 2) << 2) |
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f0) + 4) * 0xc) << 0x10;
      *(long *)(iVar21 + (iVar20 * 5 + 0xd) * 0x10) =
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f0) + 4) << 2) << 0x10 |
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f0) + 2) * 0xc);
      *(long *)(iVar21 + (iVar20 * 5 + 0xe) * 0x10) =
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f0) + 2) * 0xc) |
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f0) + 4) * 0xc) << 0x10;
    }
  }
  puVar11 = *(undefined4 **)(param_1 + uVar19 * 4 + 0x18);
  if (bVar12) {
    *puVar11 = 0x60000000;
    puVar11[1] = 0;
    puVar11[2] = 0;
    puVar11[3] = 0;
    *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfe | bVar1;
  }
  else {
    *puVar11 = 0x50000000;
    puVar11[1] = *(undefined4 *)
                  (*(int *)(iGpffff86b4 + 0x42f0) +
                   (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f0) + 10) * 4 + 0xc);
    puVar11[2] = 0;
    puVar11[3] = 0;
    fVar22 = *(float *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x144) + 0x4e4);
    fVar23 = *(float *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x144) + 0x4ec);
    fVar24 = (float)sinf(*(undefined4 *)(param_1 + 0xf8));
    fVar24 = (fVar24 + 1.0) / 2.0;
    bVar2 = *(byte *)(*(int *)(param_1 + 0x60) * 0xc + 0x652b68);
    bVar3 = *(byte *)(*(int *)(param_1 + 0x60) * 0xc + 0x652b64);
    bVar4 = *(byte *)(*(int *)(param_1 + 0x60) * 0xc + 0x652b64);
    bVar5 = *(byte *)(*(int *)(param_1 + 0x60) * 0xc + 0x652b69);
    bVar6 = *(byte *)(*(int *)(param_1 + 0x60) * 0xc + 0x652b65);
    bVar7 = *(byte *)(*(int *)(param_1 + 0x60) * 0xc + 0x652b65);
    bVar8 = *(byte *)(*(int *)(param_1 + 0x60) * 0xc + 0x652b6a);
    bVar9 = *(byte *)(*(int *)(param_1 + 0x60) * 0xc + 0x652b66);
    bVar10 = *(byte *)(*(int *)(param_1 + 0x60) * 0xc + 0x652b66);
    for (iVar21 = 0; iVar21 < 0x20; iVar21 = iVar21 + 1) {
      if ((*(short *)(param_1 + iVar21 * 2 + 0xfc) == 0) ||
         (*(short *)(param_1 + iVar21 * 2 + 0x13c) != 0)) {
        *(undefined8 *)(puVar11 + (iVar21 * 5 + 0xb) * 4 + 2) = 0x71006f00;
        *(undefined8 *)(puVar11 + (iVar21 * 5 + 0xc) * 4 + 2) = 0x71006f00;
        *(undefined8 *)(puVar11 + (iVar21 * 5 + 0xd) * 4 + 2) = 0x71006f00;
        *(undefined8 *)(puVar11 + (iVar21 * 5 + 0xe) * 4 + 2) = 0x71006f00;
      }
      else {
        *(ulong *)(puVar11 + (iVar21 * 5 + 10) * 4 + 2) =
             (long)(int)(((float)(int)(fVar22 * fVar23 * 128.0) *
                         *(float *)(param_1 + iVar21 * 4 + 0x480)) / 128.0) << 0x18 |
             (long)(int)((float)bVar10 + fVar24 * (float)(int)((uint)bVar8 - (uint)bVar9)) << 0x10 |
             (long)(int)((float)bVar4 + fVar24 * (float)(int)((uint)bVar2 - (uint)bVar3)) |
             (long)(int)((float)bVar7 + fVar24 * (float)(int)((uint)bVar5 - (uint)bVar6)) << 8 |
             0x100000000;
        *(long *)(puVar11 + (iVar21 * 5 + 0xb) * 4 + 2) =
             (long)aiStack_1100[iVar21 * 0x10 + 2] << 0x20 |
             (long)aiStack_1100[iVar21 * 0x10] | (long)aiStack_1100[iVar21 * 0x10 + 1] << 0x10;
        *(long *)(puVar11 + (iVar21 * 5 + 0xc) * 4 + 2) =
             (long)aiStack_1100[(iVar21 * 4 + 1) * 4 + 2] << 0x20 |
             (long)aiStack_1100[(iVar21 * 4 + 1) * 4] |
             (long)aiStack_1100[(iVar21 * 4 + 1) * 4 + 1] << 0x10;
        *(long *)(puVar11 + (iVar21 * 5 + 0xd) * 4 + 2) =
             (long)aiStack_1100[(iVar21 * 4 + 2) * 4 + 2] << 0x20 |
             (long)aiStack_1100[(iVar21 * 4 + 2) * 4] |
             (long)aiStack_1100[(iVar21 * 4 + 2) * 4 + 1] << 0x10;
        *(long *)(puVar11 + (iVar21 * 5 + 0xe) * 4 + 2) =
             (long)aiStack_1100[(iVar21 * 4 + 3) * 4 + 2] << 0x20 |
             (long)aiStack_1100[(iVar21 * 4 + 3) * 4] |
             (long)aiStack_1100[(iVar21 * 4 + 3) * 4 + 1] << 0x10;
      }
    }
    *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfe | bVar1;
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054ae40  EndSet__19WpnBoxAddAttribute1Fv
 * C++: WpnBoxAddAttribute1::EndSet()
 * size: 0x10 bytes
 * --------------------------------------------------------------------------- */
void EndSet__19WpnBoxAddAttribute1Fv(void)

{
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b810  @24@__dt__19WpnBoxAddAttribute1Fv
 * C++: @24@__dt__19WpnBoxAddAttribute1Fv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int * _24___dt__19WpnBoxAddAttribute1Fv(int *param_1,short param_2)

{
  int *piVar1;
  
  piVar1 = param_1 + -6;
  if (piVar1 != (int *)0x0) {
    param_1[-1] = 0x409cf0;
    param_1[4] = 0x409d00;
    param_1[7] = 0x409d10;
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
 * JP: 0x0054b820  @44@__dt__19WpnBoxAddAttribute1Fv
 * C++: @44@__dt__19WpnBoxAddAttribute1Fv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int _44___dt__19WpnBoxAddAttribute1Fv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x2c;
  if (iVar1 != 0) {
    *(undefined4 *)(param_1 + -0x18) = 0x409cf0;
    *(undefined4 *)(param_1 + -4) = 0x409d00;
    *(undefined4 *)(param_1 + 8) = 0x409d10;
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

