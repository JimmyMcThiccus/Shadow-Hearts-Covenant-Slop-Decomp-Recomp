/* decomp/H/BoxAddAttribute1.c — cleaned Ghidra output (SH2JP_BATTLE.BIN, JP Furokuban, base 0x00430a00).
 * 8 function(s). Types: see types.h. Names/gp globals resolved from symbols/SLPM_602.19.syms. */
#include "types.h"

/* ---------------------------------------------------------------------------
 * JP: 0x0052e7d0  __ct__16BoxAddAttribute1Fiiii
 * C++: BoxAddAttribute1::__ct(int, int, int, int)
 * size: 0x210 bytes
 * --------------------------------------------------------------------------- */
int __ct__16BoxAddAttribute1Fiiii
              (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
              undefined4 param_5)

{
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  int iVar1;
  undefined4 *puVar2;
  
  __ct__6BtlEffFii(param_1,param_2,param_3);
  *(undefined4 *)(param_1 + 0x14) = 0x409ca0;
  *(undefined4 *)(param_1 + 0x28) = 0x409cb0;
  *(undefined4 *)(param_1 + 0x34) = 0x409cc0;
  puVar2 = (undefined4 *)(param_1 + 0x70);
  do {
    *puVar2 = in_zero_lo;
    puVar2[1] = in_zero_hi;
    puVar2[2] = in_zero_udw;
    puVar2[3] = in_register_0000000c;
    puVar2 = puVar2 + 4;
  } while (puVar2 != (undefined4 *)(param_1 + 0xf0));
  puVar2 = (undefined4 *)(param_1 + 0x180);
  do {
    *puVar2 = in_zero_lo;
    puVar2[1] = in_zero_hi;
    puVar2[2] = in_zero_udw;
    puVar2[3] = in_register_0000000c;
    puVar2 = puVar2 + 4;
  } while (puVar2 != (undefined4 *)(param_1 + 0x280));
  *(undefined4 *)(param_1 + 0x40) = 0;
  *(undefined4 *)(param_1 + 0x44) = param_2;
  *(undefined4 *)(param_1 + 0x48) = param_3;
  *(undefined4 *)(param_1 + 0x4c) = 6;
  *(undefined4 *)(param_1 + 0x5c) = 0;
  *(undefined4 *)(param_1 + 0x60) = param_4;
  *(undefined4 *)(param_1 + 0xf0) = 0;
  *(undefined4 *)(param_1 + 0xf4) = 0;
  *(undefined4 *)(param_1 + 0xf8) = 0;
  *(undefined4 *)(param_1 + 100) = param_5;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  *(undefined4 *)(param_1 + 0x18) = 0;
  for (iVar1 = 0; iVar1 < 0x10; iVar1 = iVar1 + 1) {
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
 * JP: 0x0052e9e0  __dt__16BoxAddAttribute1Fv
 * C++: BoxAddAttribute1::__dt()
 * size: 0x154 bytes
 * --------------------------------------------------------------------------- */
int __dt__16BoxAddAttribute1Fv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x14) = 0x409ca0;
    *(undefined4 *)(param_1 + 0x28) = 0x409cb0;
    *(undefined4 *)(param_1 + 0x34) = 0x409cc0;
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
 * JP: 0x0052eb40  Destruct__16BoxAddAttribute1Fv
 * C++: BoxAddAttribute1::Destruct()
 * size: 0xcc bytes
 * --------------------------------------------------------------------------- */
void Destruct__16BoxAddAttribute1Fv(int param_1)

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
 * JP: 0x0052ec10  Polling__16BoxAddAttribute1Fv
 * C++: BoxAddAttribute1::Polling()
 * size: 0x948 bytes
 * --------------------------------------------------------------------------- */
undefined8 Polling__16BoxAddAttribute1Fv(int param_1)

{
  short sVar1;
  undefined1 auVar2 [16];
  undefined1 auVar3 [16];
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  int iVar4;
  byte *pbVar5;
  int iVar6;
  int iVar7;
  float fVar8;
  undefined1 auVar9 [16];
  undefined1 auVar10 [16];
  undefined1 auStack_180 [16];
  undefined1 auStack_170 [16];
  undefined1 auStack_160 [16];
  undefined1 auStack_150 [16];
  undefined1 auStack_140 [16];
  undefined1 auStack_130 [16];
  undefined1 auStack_120 [16];
  undefined1 auStack_110 [16];
  undefined1 auStack_100 [16];
  undefined1 auStack_f0 [8];
  undefined4 uStack_e8;
  undefined4 uStack_e4;
  undefined1 auStack_e0 [8];
  undefined4 uStack_d8;
  undefined4 uStack_d4;
  undefined1 auStack_d0 [8];
  undefined4 uStack_c8;
  undefined4 uStack_c4;
  undefined1 auStack_c0 [16];
  undefined1 auStack_b0 [8];
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  undefined1 auStack_a0 [8];
  undefined4 uStack_98;
  undefined4 uStack_94;
  undefined1 auStack_90 [8];
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
  undefined1 auStack_60 [64];
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined8 uStack_10;
  undefined4 uStack_8;
  undefined2 uStack_4;
  
  uStack_20 = (undefined4)uRam00650dd0;
  uStack_1c = (undefined4)((ulong)uRam00650dd0 >> 0x20);
  uStack_18 = uRam00650dd8;
  uStack_14 = uRam00650ddc;
  uStack_10 = uRam00650de0;
  uStack_8 = uRam00650de8;
  uStack_4 = uRam00650dec;
  fVar8 = *(float *)(iGpffff86b4 + 0x38);
  if ((*(byte *)(iGpffff86b4 + 0x24) & 1) != 0) {
    fVar8 = 0.0;
  }
  *(float *)(param_1 + 0xf8) = *(float *)(param_1 + 0xf8) + fVar8 * 6.2831855 * 0.75;
  if (3.1415927 <= *(float *)(param_1 + 0xf8)) {
    *(float *)(param_1 + 0xf8) = *(float *)(param_1 + 0xf8) - 6.2831855;
  }
  if (((*(int *)(param_1 + 0x5c) != 1) && (*(int *)(param_1 + 0x5c) == 0)) &&
     (*(float *)(param_1 + 0xf0) = *(float *)(param_1 + 0xf0) + fVar8 * 2.0,
     1.0 <= *(float *)(param_1 + 0xf0))) {
    *(undefined4 *)(param_1 + 0xf0) = 0x3f800000;
    *(undefined4 *)(param_1 + 0x5c) = 1;
  }
  pbVar5 = (byte *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x144) + 0xe4
                            ) + *(int *)(param_1 + 100) * 0x110);
  __ct__6MatrixFRC6Matrix(auStack_60,
                  *(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x144) + 0x30)
                  + (uint)*pbVar5 * 0x1f0 + (bGpffff8340 & 1) * 0x40);
  RotTransVector(param_1 + 0x70,pbVar5 + 0x10,auStack_60,8);
  *(float *)(param_1 + 0xf4) = *(float *)(param_1 + 0xf4) + fVar8;
  uStack_80 = in_zero_lo;
  uStack_7c = in_zero_hi;
  uStack_78 = in_zero_udw;
  uStack_74 = in_register_0000000c;
  uStack_70 = in_zero_lo;
  uStack_6c = in_zero_hi;
  uStack_68 = in_zero_udw;
  uStack_64 = in_register_0000000c;
  for (iVar6 = 0; iVar6 < 0x10; iVar6 = iVar6 + 1) {
    sVar1 = *(short *)(param_1 + iVar6 * 2 + 0xfc);
    if (sVar1 == 1) {
      iVar4 = param_1 + iVar6 * 4;
      *(float *)(iVar4 + 0x13c) = *(float *)(iVar4 + 0x13c) + fVar8;
      iVar4 = param_1 + iVar6 * 0x10;
      *(float *)(iVar4 + 0x184) = *(float *)(iVar4 + 0x184) - fVar8 * 2.0;
      if (*(float *)(param_1 + iVar6 * 4 + 0x13c) < 0.6666667) {
        *(undefined4 *)(param_1 + iVar6 * 4 + 0x2c0) = 0x43000000;
      }
      else {
        *(float *)(param_1 + iVar6 * 4 + 0x2c0) =
             ((1.0 - *(float *)(param_1 + iVar6 * 4 + 0x13c)) / 0.33333334) * 128.0;
      }
      if ((1.0 <= *(float *)(param_1 + iVar6 * 4 + 0x13c)) &&
         (*(undefined2 *)(param_1 + iVar6 * 2 + 0xfc) = 0, 0.06666667 <= *(float *)(param_1 + 0xf4))
         ) {
        *(undefined2 *)(param_1 + iVar6 * 2 + 0xfc) = 1;
        *(undefined4 *)(param_1 + iVar6 * 4 + 0x13c) = 0;
        iVar4 = rand();
        iVar7 = (int)(((float)iVar4 / 2.1474836e+09) * 6.0);
        auVar9 = _lqc2(*(undefined1 (*) [16])
                        (param_1 + *(char *)((int)&uStack_20 + iVar7 * 5) * 0x10 + 0x70));
        auVar10 = _lqc2(*(undefined1 (*) [16])
                         (param_1 + *(char *)((int)&uStack_20 + iVar7 * 5 + 1) * 0x10 + 0x70));
        auVar9 = _vsub(auVar9,auVar10);
        auStack_140 = _sqc2(auVar9);
        __ct__7FVectorFRC7FVector(auStack_d0,auStack_140);
        uStack_80 = auStack_d0._0_4_;
        uStack_7c = auStack_d0._4_4_;
        uStack_78 = uStack_c8;
        uStack_74 = uStack_c4;
        iVar4 = rand();
        __amu__7FVectorFf((float)iVar4 / 2.1474836e+09,&uStack_80);
        auVar9 = _lqc2(*(undefined1 (*) [16])
                        (param_1 + *(char *)((int)&uStack_20 + iVar7 * 5 + 2) * 0x10 + 0x70));
        auVar10 = _lqc2(*(undefined1 (*) [16])
                         (param_1 + *(char *)((int)&uStack_20 + iVar7 * 5 + 3) * 0x10 + 0x70));
        auVar9 = _vsub(auVar9,auVar10);
        auStack_150 = _sqc2(auVar9);
        __ct__7FVectorFRC7FVector(auStack_e0,auStack_150);
        uStack_70 = auStack_e0._0_4_;
        uStack_6c = auStack_e0._4_4_;
        uStack_68 = uStack_d8;
        uStack_64 = uStack_d4;
        iVar4 = rand();
        __amu__7FVectorFf((float)iVar4 / 2.1474836e+09,&uStack_70);
        auVar10 = _lqc2(*(undefined1 (*) [16])
                         (param_1 + *(char *)((int)&uStack_1c + iVar7 * 5) * 0x10 + 0x70));
        auVar9._4_4_ = uStack_7c;
        auVar9._0_4_ = uStack_80;
        auVar9._8_4_ = uStack_78;
        auVar9._12_4_ = uStack_74;
        auVar9 = _lqc2(auVar9);
        auVar9 = _vadd(auVar10,auVar9);
        auStack_180 = _sqc2(auVar9);
        __ct__7FVectorFRC7FVector(auStack_100,auStack_180);
        auVar9 = _lqc2(auStack_100);
        auVar10._4_4_ = uStack_6c;
        auVar10._0_4_ = uStack_70;
        auVar10._8_4_ = uStack_68;
        auVar10._12_4_ = uStack_64;
        auVar10 = _lqc2(auVar10);
        auVar9 = _vadd(auVar9,auVar10);
        auStack_160 = _sqc2(auVar9);
        __ct__7FVectorFRC7FVector(auStack_f0,auStack_160);
        iVar4 = param_1 + iVar6 * 0x10;
        *(int *)(iVar4 + 0x180) = auStack_f0._0_4_;
        *(int *)(iVar4 + 0x184) = auStack_f0._4_4_;
        *(undefined4 *)(iVar4 + 0x188) = uStack_e8;
        *(undefined4 *)(iVar4 + 0x18c) = uStack_e4;
        *(undefined4 *)(param_1 + iVar6 * 4 + 0x280) = 0x3f800000;
        *(undefined4 *)(param_1 + iVar6 * 4 + 0x2c0) = 0x3f800000;
        *(float *)(param_1 + 0xf4) = *(float *)(param_1 + 0xf4) - 0.06666667;
      }
    }
    else if ((sVar1 == 0) && (0.06666667 <= *(float *)(param_1 + 0xf4))) {
      *(undefined2 *)(param_1 + iVar6 * 2 + 0xfc) = 1;
      *(undefined4 *)(param_1 + iVar6 * 4 + 0x13c) = 0;
      iVar4 = rand();
      iVar7 = (int)(((float)iVar4 / 2.1474836e+09) * 6.0);
      auVar9 = _lqc2(*(undefined1 (*) [16])
                      (param_1 + *(char *)((int)&uStack_20 + iVar7 * 5) * 0x10 + 0x70));
      auVar10 = _lqc2(*(undefined1 (*) [16])
                       (param_1 + *(char *)((int)&uStack_20 + iVar7 * 5 + 1) * 0x10 + 0x70));
      auVar9 = _vsub(auVar9,auVar10);
      auStack_110 = _sqc2(auVar9);
      __ct__7FVectorFRC7FVector(auStack_90,auStack_110);
      uStack_80 = auStack_90._0_4_;
      uStack_7c = auStack_90._4_4_;
      uStack_78 = uStack_88;
      uStack_74 = uStack_84;
      iVar4 = rand();
      __amu__7FVectorFf((float)iVar4 / 2.1474836e+09,&uStack_80);
      auVar9 = _lqc2(*(undefined1 (*) [16])
                      (param_1 + *(char *)((int)&uStack_20 + iVar7 * 5 + 2) * 0x10 + 0x70));
      auVar10 = _lqc2(*(undefined1 (*) [16])
                       (param_1 + *(char *)((int)&uStack_20 + iVar7 * 5 + 3) * 0x10 + 0x70));
      auVar9 = _vsub(auVar9,auVar10);
      auStack_120 = _sqc2(auVar9);
      __ct__7FVectorFRC7FVector(auStack_a0,auStack_120);
      uStack_70 = auStack_a0._0_4_;
      uStack_6c = auStack_a0._4_4_;
      uStack_68 = uStack_98;
      uStack_64 = uStack_94;
      iVar4 = rand();
      __amu__7FVectorFf((float)iVar4 / 2.1474836e+09,&uStack_70);
      auVar9 = _lqc2(*(undefined1 (*) [16])
                      (param_1 + *(char *)((int)&uStack_1c + iVar7 * 5) * 0x10 + 0x70));
      auVar2._4_4_ = uStack_7c;
      auVar2._0_4_ = uStack_80;
      auVar2._8_4_ = uStack_78;
      auVar2._12_4_ = uStack_74;
      auVar10 = _lqc2(auVar2);
      auVar9 = _vadd(auVar9,auVar10);
      auStack_170 = _sqc2(auVar9);
      __ct__7FVectorFRC7FVector(auStack_c0,auStack_170);
      auVar9 = _lqc2(auStack_c0);
      auVar3._4_4_ = uStack_6c;
      auVar3._0_4_ = uStack_70;
      auVar3._8_4_ = uStack_68;
      auVar3._12_4_ = uStack_64;
      auVar10 = _lqc2(auVar3);
      auVar9 = _vadd(auVar9,auVar10);
      auStack_130 = _sqc2(auVar9);
      __ct__7FVectorFRC7FVector(auStack_b0,auStack_130);
      iVar4 = param_1 + iVar6 * 0x10;
      *(int *)(iVar4 + 0x180) = auStack_b0._0_4_;
      *(int *)(iVar4 + 0x184) = auStack_b0._4_4_;
      *(undefined4 *)(iVar4 + 0x188) = uStack_a8;
      *(undefined4 *)(iVar4 + 0x18c) = uStack_a4;
      *(undefined4 *)(param_1 + iVar6 * 4 + 0x280) = 0x3f800000;
      *(undefined4 *)(param_1 + iVar6 * 4 + 0x2c0) = 0x3f800000;
      *(float *)(param_1 + 0xf4) = *(float *)(param_1 + 0xf4) - 0.06666667;
    }
  }
  return 0;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0052f560  MakePacket__16BoxAddAttribute1Fv
 * C++: BoxAddAttribute1::MakePacket()
 * size: 0x24b0 bytes
 * --------------------------------------------------------------------------- */
/* WARNING: Removing unreachable block (ram,0x005313d8) */
/* WARNING: Removing unreachable block (ram,0x00531258) */
/* WARNING: Removing unreachable block (ram,0x00531318) */
/* WARNING: Removing unreachable block (ram,0x005310bc) */

void MakePacket__16BoxAddAttribute1Fv(int param_1)

{
  bool bVar1;
  undefined4 *puVar2;
  undefined1 auVar3 [16];
  bool bVar4;
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
  float in_zero_lo;
  float in_zero_hi;
  float in_zero_udw;
  undefined4 in_register_0000000c;
  undefined4 uVar26;
  undefined8 uVar27;
  int iVar28;
  undefined8 in_v1_udw;
  undefined1 auVar29 [16];
  uint uVar30;
  int iVar31;
  float fVar32;
  float fVar33;
  float fVar34;
  float fVar35;
  int iVar36;
  int iVar37;
  int iVar38;
  undefined1 in_vf0 [16];
  undefined1 auVar39 [16];
  undefined1 auVar40 [16];
  undefined1 auVar41 [16];
  undefined1 auStack_f80 [16];
  undefined1 auStack_f70 [16];
  undefined1 auStack_f60 [16];
  undefined1 auStack_f50 [16];
  undefined1 auStack_f40 [16];
  undefined1 auStack_f30 [16];
  undefined1 auStack_f20 [16];
  undefined1 auStack_f10 [16];
  undefined1 auStack_f00 [16];
  undefined1 auStack_ef0 [16];
  undefined1 auStack_ee0 [16];
  undefined1 auStack_ed0 [16];
  undefined1 auStack_ec0 [16];
  undefined1 auStack_eb0 [16];
  undefined1 auStack_ea0 [16];
  undefined1 auStack_e90 [16];
  undefined1 auStack_e80 [16];
  undefined1 auStack_e70 [16];
  undefined1 auStack_e60 [16];
  undefined1 auStack_e50 [16];
  undefined1 auStack_e40 [16];
  float fStack_e30;
  float fStack_e2c;
  undefined4 uStack_e28;
  undefined4 uStack_e24;
  float fStack_e20;
  float fStack_e1c;
  undefined4 uStack_e18;
  undefined4 uStack_e14;
  undefined4 uStack_e10;
  float fStack_e0c;
  undefined4 uStack_e08;
  undefined4 uStack_e04;
  undefined4 uStack_e00;
  float fStack_dfc;
  undefined4 uStack_df8;
  undefined4 uStack_df4;
  undefined4 uStack_df0;
  float fStack_dec;
  undefined4 uStack_de8;
  undefined4 uStack_de4;
  undefined4 uStack_de0;
  float fStack_ddc;
  undefined4 uStack_dd8;
  undefined4 uStack_dd4;
  float fStack_dd0;
  float fStack_dcc;
  undefined4 uStack_dc8;
  undefined4 uStack_dc4;
  float fStack_dc0;
  float fStack_dbc;
  undefined4 uStack_db8;
  undefined4 uStack_db4;
  undefined4 uStack_db0;
  undefined4 uStack_dac;
  undefined4 uStack_da8;
  undefined4 uStack_da4;
  undefined4 uStack_da0;
  undefined4 uStack_d9c;
  undefined4 uStack_d98;
  undefined4 uStack_d94;
  undefined4 uStack_d90;
  undefined4 uStack_d8c;
  undefined4 uStack_d88;
  undefined4 uStack_d84;
  undefined4 uStack_d80;
  undefined4 uStack_d7c;
  undefined4 uStack_d78;
  undefined4 uStack_d74;
  undefined1 auStack_d70 [64];
  undefined4 uStack_d30;
  undefined4 uStack_d2c;
  undefined4 uStack_d28;
  undefined4 uStack_d24;
  float fStack_d20;
  float fStack_d1c;
  float fStack_d18;
  undefined4 uStack_d14;
  undefined4 uStack_d10;
  undefined4 uStack_d0c;
  undefined4 uStack_d08;
  undefined4 uStack_d04;
  undefined4 uStack_d00;
  undefined4 uStack_cfc;
  undefined4 uStack_cf8;
  undefined4 uStack_cf4;
  undefined4 uStack_cf0;
  undefined4 uStack_cec;
  undefined4 uStack_ce8;
  undefined4 uStack_ce4;
  undefined4 uStack_ce0;
  undefined4 uStack_cdc;
  undefined4 uStack_cd8;
  undefined4 uStack_cd4;
  undefined4 uStack_cd0;
  undefined4 uStack_ccc;
  undefined4 uStack_cc8;
  undefined4 uStack_cc4;
  undefined4 uStack_cc0;
  undefined4 uStack_cbc;
  undefined4 uStack_cb8;
  undefined4 uStack_cb4;
  undefined4 uStack_cb0;
  undefined4 uStack_cac;
  undefined4 uStack_ca8;
  undefined4 uStack_ca4;
  undefined4 uStack_ca0;
  undefined4 uStack_c9c;
  undefined4 uStack_c98;
  undefined4 uStack_c94;
  undefined4 uStack_c90;
  undefined4 uStack_c8c;
  undefined4 uStack_c88;
  undefined4 uStack_c84;
  undefined4 uStack_c80;
  undefined4 uStack_c7c;
  undefined4 uStack_c78;
  undefined4 uStack_c74;
  undefined1 auStack_c70 [16];
  undefined1 auStack_c60 [16];
  undefined1 auStack_c50 [16];
  undefined1 auStack_c40 [16];
  undefined4 uStack_c30;
  undefined4 uStack_c2c;
  undefined4 uStack_c28;
  undefined4 uStack_c24;
  undefined1 auStack_c20 [16];
  undefined1 auStack_c10 [16];
  float fStack_c00;
  undefined4 uStack_bfc;
  undefined4 uStack_bf8;
  undefined4 uStack_bf4;
  undefined4 uStack_bf0;
  undefined4 uStack_bec;
  undefined4 uStack_be8;
  undefined4 uStack_be4;
  undefined4 uStack_be0;
  undefined4 uStack_bdc;
  undefined4 uStack_bd8;
  undefined4 uStack_bd4;
  undefined4 uStack_bd0;
  undefined4 uStack_bcc;
  undefined4 uStack_bc8;
  undefined4 uStack_bc4;
  undefined4 uStack_bc0;
  undefined4 uStack_bbc;
  undefined4 uStack_bb8;
  undefined4 uStack_bb4;
  undefined4 uStack_bb0;
  undefined4 uStack_bac;
  undefined4 uStack_ba8;
  undefined4 uStack_ba4;
  int aiStack_ba0 [304];
  int aiStack_6e0 [6];
  int iStack_6c8;
  float afStack_6a0 [5];
  undefined4 uStack_68c;
  undefined4 uStack_688;
  undefined4 uStack_684;
  float fStack_680;
  float fStack_67c;
  float fStack_678;
  undefined4 uStack_674;
  float fStack_670;
  float fStack_66c;
  float fStack_668;
  undefined4 uStack_664;
  float afStack_2a0 [16];
  float afStack_260 [16];
  float fStack_220;
  float fStack_21c;
  undefined4 uStack_218;
  undefined4 uStack_214;
  float fStack_210;
  float fStack_20c;
  undefined4 uStack_208;
  undefined4 uStack_204;
  undefined4 uStack_200;
  float fStack_1fc;
  undefined4 uStack_1f8;
  undefined4 uStack_1f4;
  undefined4 uStack_1f0;
  float fStack_1ec;
  undefined4 uStack_1e8;
  undefined4 uStack_1e4;
  undefined4 uStack_1e0;
  float fStack_1dc;
  undefined4 uStack_1d8;
  undefined4 uStack_1d4;
  undefined4 uStack_1d0;
  float fStack_1cc;
  undefined4 uStack_1c8;
  undefined4 uStack_1c4;
  float fStack_1c0;
  float fStack_1bc;
  undefined4 uStack_1b8;
  undefined4 uStack_1b4;
  float fStack_1b0;
  float fStack_1ac;
  undefined4 uStack_1a8;
  undefined4 uStack_1a4;
  undefined4 uStack_1a0;
  undefined4 uStack_19c;
  undefined4 uStack_198;
  undefined4 uStack_194;
  undefined4 uStack_190;
  undefined4 uStack_18c;
  undefined4 uStack_188;
  undefined4 uStack_184;
  float afStack_180 [7];
  undefined4 uStack_164;
  undefined1 auStack_160 [8];
  float fStack_158;
  undefined4 uStack_154;
  undefined1 auStack_150 [8];
  float fStack_148;
  undefined4 uStack_144;
  float fStack_140;
  float fStack_13c;
  float fStack_138;
  undefined4 uStack_134;
  undefined4 uStack_130;
  undefined4 uStack_12c;
  undefined4 uStack_128;
  undefined4 uStack_124;
  float afStack_120 [16];
  float fStack_e0;
  float fStack_dc;
  float fStack_d8;
  undefined1 auStack_d0 [16];
  undefined1 auStack_c0 [16];
  undefined1 auStack_b0 [16];
  undefined1 auStack_a0 [16];
  undefined1 auStack_90 [16];
  undefined1 auStack_80 [16];
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
  float fStack_10;
  float fStack_c;
  float fStack_8;
  float fStack_4;
  
  uStack_bb0 = 0xbf800000;
  uStack_bac = 0xbf800000;
  uStack_ba8 = 0;
  uStack_ba4 = 0x3f800000;
  auStack_90._0_12_ = ZEXT812(0xbf800000bf800000);
  auStack_90._12_4_ = 0x3f800000;
  uStack_bc0 = 0xbf800000;
  uStack_bbc = 0x3f800000;
  uStack_bb8 = 0;
  uStack_bb4 = 0x3f800000;
  auStack_80._0_12_ = ZEXT812(0x3f800000bf800000);
  auStack_80._12_4_ = 0x3f800000;
  uStack_bd0 = 0x3f800000;
  uStack_bcc = 0xbf800000;
  uStack_bc8 = 0;
  uStack_bc4 = 0x3f800000;
  uStack_70 = 0x3f800000;
  uStack_6c = 0xbf800000;
  uStack_68 = 0;
  uStack_64 = 0x3f800000;
  uStack_be0 = 0x3f800000;
  uStack_bdc = 0x3f800000;
  uStack_bd8 = 0;
  uStack_bd4 = 0x3f800000;
  uStack_60 = 0x3f800000;
  uStack_5c = 0x3f800000;
  uStack_58 = 0;
  uStack_54 = 0x3f800000;
  uStack_bf0 = 0x40400000;
  uStack_bec = 0;
  uStack_be8 = 0;
  uStack_be4 = 0x3f800000;
  uStack_50 = 0x40400000;
  uStack_4c = 0;
  uStack_48 = 0;
  uStack_44 = 0x3f800000;
  __ct__6MatrixFRC6Matrix(auStack_d0,iGpffff8598 + 0x240);
  auStack_a0._0_12_ = ZEXT812(0);
  auStack_a0._12_4_ = 0x3f800000;
  fStack_e0 = in_zero_lo;
  fStack_dc = in_zero_hi;
  fStack_d8 = in_zero_udw;
  RotTransVector(afStack_120,auStack_90,auStack_d0,5);
  auVar39 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x70));
  auVar40 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x90));
  auVar39 = _vadd(auVar39,auVar40);
  auStack_f50 = _sqc2(auVar39);
  __ct__7FVectorFRC7FVector(auStack_c20,auStack_f50);
  auVar39 = _lqc2(auStack_c20);
  auVar40 = _lqc2(*(undefined1 (*) [16])(param_1 + 0xb0));
  auVar39 = _vadd(auVar39,auVar40);
  auStack_f60 = _sqc2(auVar39);
  __ct__7FVectorFRC7FVector(auStack_c10,auStack_f60);
  auVar39 = _lqc2(auStack_c10);
  auVar40 = _lqc2(*(undefined1 (*) [16])(param_1 + 0xd0));
  auVar39 = _vadd(auVar39,auVar40);
  auStack_e40 = _sqc2(auVar39);
  __ct__7FVectorFRC7FVector(&fStack_c00,auStack_e40);
  fStack_140 = fStack_c00;
  fStack_13c = (float)uStack_bfc;
  fStack_138 = (float)uStack_bf8;
  uStack_134 = uStack_bf4;
  __adv__7FVectorFf(0x40800000,&fStack_140);
  auVar39 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x80));
  auVar40 = _lqc2(*(undefined1 (*) [16])(param_1 + 0xa0));
  auVar39 = _vadd(auVar39,auVar40);
  auStack_f70 = _sqc2(auVar39);
  __ct__7FVectorFRC7FVector(auStack_c50,auStack_f70);
  auVar39 = _lqc2(auStack_c50);
  auVar40 = _lqc2(*(undefined1 (*) [16])(param_1 + 0xc0));
  auVar39 = _vadd(auVar39,auVar40);
  auStack_f80 = _sqc2(auVar39);
  __ct__7FVectorFRC7FVector(auStack_c40,auStack_f80);
  auVar39 = _lqc2(auStack_c40);
  auVar40 = _lqc2(*(undefined1 (*) [16])(param_1 + 0xe0));
  auVar39 = _vadd(auVar39,auVar40);
  auStack_e50 = _sqc2(auVar39);
  __ct__7FVectorFRC7FVector(&uStack_c30,auStack_e50);
  uStack_130 = uStack_c30;
  uStack_12c = uStack_c2c;
  uStack_128 = uStack_c28;
  uStack_124 = uStack_c24;
  __adv__7FVectorFf(0x40800000,&uStack_130);
  auVar40 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x70));
  auVar39._4_4_ = fStack_13c;
  auVar39._0_4_ = fStack_140;
  auVar39._8_4_ = fStack_138;
  auVar39._12_4_ = uStack_134;
  auVar39 = _lqc2(auVar39);
  auVar39 = _vsub(auVar40,auVar39);
  auStack_e60 = _sqc2(auVar39);
  __ct__7FVectorFRC7FVector(auStack_c60,auStack_e60);
  auVar39 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x90));
  auVar40._4_4_ = fStack_13c;
  auVar40._0_4_ = fStack_140;
  auVar40._8_4_ = fStack_138;
  auVar40._12_4_ = uStack_134;
  auVar40 = _lqc2(auVar40);
  auVar39 = _vsub(auVar39,auVar40);
  auStack_e70 = _sqc2(auVar39);
  __ct__7FVectorFRC7FVector(auStack_c70,auStack_e70);
  auVar39 = _lqc2(*(undefined1 (*) [16])(param_1 + 0xb0));
  auVar41._4_4_ = fStack_13c;
  auVar41._0_4_ = fStack_140;
  auVar41._8_4_ = fStack_138;
  auVar41._12_4_ = uStack_134;
  auVar40 = _lqc2(auVar41);
  auVar39 = _vsub(auVar39,auVar40);
  auStack_e80 = _sqc2(auVar39);
  __ct__7FVectorFRC7FVector(&uStack_c80,auStack_e80);
  uStack_70 = uStack_c80;
  uStack_6c = uStack_c7c;
  uStack_68 = uStack_c78;
  uStack_64 = uStack_c74;
  auVar39 = _lqc2(*(undefined1 (*) [16])(param_1 + 0xd0));
  auVar13._4_4_ = fStack_13c;
  auVar13._0_4_ = fStack_140;
  auVar13._8_4_ = fStack_138;
  auVar13._12_4_ = uStack_134;
  auVar40 = _lqc2(auVar13);
  auVar39 = _vsub(auVar39,auVar40);
  auStack_e90 = _sqc2(auVar39);
  __ct__7FVectorFRC7FVector(&uStack_c90,auStack_e90);
  uStack_60 = uStack_c90;
  uStack_5c = uStack_c8c;
  uStack_58 = uStack_c88;
  uStack_54 = uStack_c84;
  auVar39 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x80));
  auVar17._4_4_ = uStack_12c;
  auVar17._0_4_ = uStack_130;
  auVar17._8_4_ = uStack_128;
  auVar17._12_4_ = uStack_124;
  auVar40 = _lqc2(auVar17);
  auVar39 = _vsub(auVar39,auVar40);
  auStack_ea0 = _sqc2(auVar39);
  __ct__7FVectorFRC7FVector(&uStack_ca0,auStack_ea0);
  uStack_50 = uStack_ca0;
  uStack_4c = uStack_c9c;
  uStack_48 = uStack_c98;
  uStack_44 = uStack_c94;
  auVar39 = _lqc2(*(undefined1 (*) [16])(param_1 + 0xa0));
  auVar18._4_4_ = uStack_12c;
  auVar18._0_4_ = uStack_130;
  auVar18._8_4_ = uStack_128;
  auVar18._12_4_ = uStack_124;
  auVar40 = _lqc2(auVar18);
  auVar39 = _vsub(auVar39,auVar40);
  auStack_eb0 = _sqc2(auVar39);
  __ct__7FVectorFRC7FVector(&uStack_cb0,auStack_eb0);
  uStack_40 = uStack_cb0;
  uStack_3c = uStack_cac;
  uStack_38 = uStack_ca8;
  uStack_34 = uStack_ca4;
  auVar39 = _lqc2(*(undefined1 (*) [16])(param_1 + 0xc0));
  auVar19._4_4_ = uStack_12c;
  auVar19._0_4_ = uStack_130;
  auVar19._8_4_ = uStack_128;
  auVar19._12_4_ = uStack_124;
  auVar40 = _lqc2(auVar19);
  auVar39 = _vsub(auVar39,auVar40);
  auStack_ec0 = _sqc2(auVar39);
  __ct__7FVectorFRC7FVector(&uStack_cc0,auStack_ec0);
  uStack_30 = uStack_cc0;
  uStack_2c = uStack_cbc;
  uStack_28 = uStack_cb8;
  uStack_24 = uStack_cb4;
  auVar39 = _lqc2(*(undefined1 (*) [16])(param_1 + 0xe0));
  auVar20._4_4_ = uStack_12c;
  auVar20._0_4_ = uStack_130;
  auVar20._8_4_ = uStack_128;
  auVar20._12_4_ = uStack_124;
  auVar40 = _lqc2(auVar20);
  auVar39 = _vsub(auVar39,auVar40);
  auStack_ed0 = _sqc2(auVar39);
  __ct__7FVectorFRC7FVector(&uStack_cd0,auStack_ed0);
  uStack_20 = uStack_cd0;
  uStack_1c = uStack_ccc;
  uStack_18 = uStack_cc8;
  uStack_14 = uStack_cc4;
  fVar32 = (float)Length__7FVectorCFv(auStack_90);
  fVar33 = (float)Length__7FVectorCFv(auStack_80);
  fVar34 = (float)Length__7FVectorCFv(&uStack_70);
  fVar35 = (float)Length__7FVectorCFv(&uStack_60);
  fStack_8 = (fVar35 + fVar34 + fVar32 + fVar33) / 4.0;
  fVar32 = (float)Length__7FVectorCFv(&uStack_50);
  fVar33 = (float)Length__7FVectorCFv(&uStack_40);
  fVar34 = (float)Length__7FVectorCFv(&uStack_30);
  fVar35 = (float)Length__7FVectorCFv(&uStack_20);
  fStack_4 = (fVar35 + fVar34 + fVar32 + fVar33) / 4.0;
  auVar14._4_4_ = fStack_13c;
  auVar14._0_4_ = fStack_140;
  auVar14._8_4_ = fStack_138;
  auVar14._12_4_ = uStack_134;
  auVar39 = _lqc2(auVar14);
  auVar21._4_4_ = uStack_12c;
  auVar21._0_4_ = uStack_130;
  auVar21._8_4_ = uStack_128;
  auVar21._12_4_ = uStack_124;
  auVar40 = _lqc2(auVar21);
  auVar39 = _vsub(auVar39,auVar40);
  auStack_ee0 = _sqc2(auVar39);
  __ct__7FVectorFRC7FVector(&uStack_ce0,auStack_ee0);
  auStack_90._4_4_ = uStack_cdc;
  auStack_90._0_4_ = uStack_ce0;
  auStack_90._8_4_ = uStack_cd8;
  auStack_90._12_4_ = uStack_cd4;
  auVar22._4_4_ = uStack_12c;
  auVar22._0_4_ = uStack_130;
  auVar22._8_4_ = uStack_128;
  auVar22._12_4_ = uStack_124;
  auVar39 = _lqc2(auVar22);
  auVar15._4_4_ = fStack_13c;
  auVar15._0_4_ = fStack_140;
  auVar15._8_4_ = fStack_138;
  auVar15._12_4_ = uStack_134;
  auVar40 = _lqc2(auVar15);
  auVar39 = _vsub(auVar39,auVar40);
  auStack_ef0 = _sqc2(auVar39);
  __ct__7FVectorFRC7FVector(&uStack_cf0,auStack_ef0);
  auStack_80._4_4_ = uStack_cec;
  auStack_80._0_4_ = uStack_cf0;
  auStack_80._8_4_ = uStack_ce8;
  auStack_80._12_4_ = uStack_ce4;
  if ((((*(byte *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0xb1) & 1) == 0) ||
      (*(short *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x120) != 7)) ||
     (*(short *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0xba) != 0xf)) {
    __amu__7FVectorFf(0x3f666666,auStack_90);
    __amu__7FVectorFf(0x3f666666,auStack_80);
  }
  else if (*(int *)(param_1 + 0x44) == 100) {
    __amu__7FVectorFf(0x3f333333,auStack_90);
    __amu__7FVectorFf(0x3f666666,auStack_80);
  }
  else {
    __amu__7FVectorFf(0x3f666666,auStack_90);
    __amu__7FVectorFf(0x3f333333,auStack_80);
  }
  auVar23._4_4_ = uStack_12c;
  auVar23._0_4_ = uStack_130;
  auVar23._8_4_ = uStack_128;
  auVar23._12_4_ = uStack_124;
  auVar40 = _lqc2(auVar23);
  auVar39 = _lqc2(auStack_90);
  auVar39 = _vadd(auVar39,auVar40);
  auStack_90 = _sqc2(auVar39);
  auVar16._4_4_ = fStack_13c;
  auVar16._0_4_ = fStack_140;
  auVar16._8_4_ = fStack_138;
  auVar16._12_4_ = uStack_134;
  auVar40 = _lqc2(auVar16);
  auVar39 = _lqc2(auStack_80);
  auVar39 = _vadd(auVar39,auVar40);
  auStack_80 = _sqc2(auVar39);
  auVar39 = _lqc2(*(undefined1 (*) [16])(*(int *)(iGpffff86b4 + 0x4324) + 0x30));
  auVar40 = _lqc2(auStack_90);
  auVar39 = _vsub(auVar39,auVar40);
  auStack_f00 = _sqc2(auVar39);
  __ct__7FVectorFRC7FVector(&uStack_d00,auStack_f00);
  uStack_70 = uStack_d00;
  uStack_6c = uStack_cfc;
  uStack_68 = uStack_cf8;
  uStack_64 = uStack_cf4;
  auVar39 = _lqc2(*(undefined1 (*) [16])(*(int *)(iGpffff86b4 + 0x4324) + 0x30));
  auVar40 = _lqc2(auStack_80);
  auVar39 = _vsub(auVar39,auVar40);
  auStack_f10 = _sqc2(auVar39);
  __ct__7FVectorFRC7FVector(&uStack_d10,auStack_f10);
  uStack_60 = uStack_d10;
  uStack_5c = uStack_d0c;
  uStack_58 = uStack_d08;
  uStack_54 = uStack_d04;
  Normalize__7FVectorFv(&uStack_70);
  Normalize__7FVectorFv(&uStack_60);
  __amu__7FVectorFf(fStack_8,&uStack_70);
  __amu__7FVectorFf(fStack_4,&uStack_60);
  auVar39 = _lqc2(auStack_90);
  auVar24._4_4_ = uStack_6c;
  auVar24._0_4_ = uStack_70;
  auVar24._8_4_ = uStack_68;
  auVar24._12_4_ = uStack_64;
  auVar40 = _lqc2(auVar24);
  auVar39 = _vadd(auVar39,auVar40);
  auStack_f20 = _sqc2(auVar39);
  __ct__7FVectorFRC7FVector(&fStack_d20,auStack_f20);
  fStack_140 = fStack_d20;
  fStack_13c = fStack_d1c;
  fStack_138 = fStack_d18;
  uStack_134 = uStack_d14;
  auVar39 = _lqc2(auStack_80);
  auVar25._4_4_ = uStack_5c;
  auVar25._0_4_ = uStack_60;
  auVar25._8_4_ = uStack_58;
  auVar25._12_4_ = uStack_54;
  auVar40 = _lqc2(auVar25);
  auVar39 = _vadd(auVar39,auVar40);
  auStack_f30 = _sqc2(auVar39);
  __ct__7FVectorFRC7FVector(&uStack_d30,auStack_f30);
  uStack_130 = uStack_d30;
  uStack_12c = uStack_d2c;
  uStack_128 = uStack_d28;
  uStack_124 = uStack_d24;
  auStack_160._4_4_ = in_zero_hi;
  auStack_160._0_4_ = in_zero_lo;
  fStack_158 = in_zero_udw;
  uStack_154 = in_register_0000000c;
  auStack_150._4_4_ = in_zero_hi;
  auStack_150._0_4_ = in_zero_lo;
  fStack_148 = in_zero_udw;
  uStack_144 = in_register_0000000c;
  afStack_180[0] = in_zero_lo;
  afStack_180[1] = in_zero_hi;
  afStack_180[2] = in_zero_udw;
  afStack_180[3] = (float)in_register_0000000c;
  afStack_180[4] = in_zero_lo;
  afStack_180[5] = in_zero_hi;
  afStack_180[6] = in_zero_udw;
  uStack_164 = in_register_0000000c;
  GetViewScreenMatrix__9GsxCameraFv(auStack_d70,iGpffff8598);
  for (iVar28 = 0; iVar28 < 4; iVar28 = iVar28 + 1) {
    aiStack_ba0[iVar28 * 4 + 0x120] = *(int *)(auStack_d0 + iVar28 * 0x10);
    aiStack_ba0[iVar28 * 4 + 0x121] = *(int *)(auStack_d0 + iVar28 * 0x10 + 4);
    aiStack_ba0[iVar28 * 4 + 0x122] = *(int *)(auStack_d0 + iVar28 * 0x10 + 8);
    aiStack_ba0[iVar28 * 4 + 0x123] = *(int *)(auStack_d0 + iVar28 * 0x10 + 0xc);
  }
  afStack_6a0[0] = fStack_140;
  afStack_6a0[1] = fStack_13c;
  afStack_6a0[2] = fStack_138;
  afStack_6a0[3] = 1.0;
  afStack_6a0[4] = (float)uStack_130;
  uStack_68c = uStack_12c;
  uStack_688 = uStack_128;
  uStack_684 = 0x3f800000;
  fStack_680 = fStack_140 + fStack_e0 * fStack_8;
  fStack_67c = fStack_13c + fStack_dc * fStack_8;
  fStack_678 = fStack_138 + fStack_d8 * fStack_8;
  uStack_674 = 0x3f800000;
  fStack_670 = fStack_140 + fStack_e0 * fStack_4;
  fStack_66c = fStack_13c + fStack_dc * fStack_4;
  fStack_668 = fStack_138 + fStack_d8 * fStack_4;
  uStack_664 = 0x3f800000;
  sceVu0RotTransPersN(aiStack_6e0,aiStack_ba0 + 0x120,afStack_6a0,4,0);
  for (iVar28 = 0; iVar28 < 4; iVar28 = iVar28 + 1) {
    afStack_180[iVar28 * 4] = (float)aiStack_6e0[iVar28 * 4] / 16.0 - 1792.0;
    afStack_180[iVar28 * 4 + 1] = (float)aiStack_6e0[iVar28 * 4 + 1] / 16.0 - 1824.0;
    afStack_180[iVar28 * 4 + 2] = 0.0;
    afStack_180[iVar28 * 4 + 3] = 1.0;
  }
  auVar12._4_4_ = afStack_180[5];
  auVar12._0_4_ = afStack_180[4];
  auVar12._8_4_ = afStack_180[6];
  auVar12._12_4_ = uStack_164;
  auVar39 = _lqc2(auVar12);
  auVar9._4_4_ = afStack_180[1];
  auVar9._0_4_ = afStack_180[0];
  auVar9._8_4_ = afStack_180[2];
  auVar9._12_4_ = afStack_180[3];
  auVar40 = _lqc2(auVar9);
  auVar39 = _vsub(auVar39,auVar40);
  auStack_f40 = _sqc2(auVar39);
  __ct__7FVectorFRC7FVector(&uStack_d80,auStack_f40);
  uStack_1a0 = uStack_d80;
  uStack_19c = uStack_d7c;
  uStack_198 = uStack_d78;
  uStack_194 = uStack_d74;
  Normalize__7FVectorFv(&uStack_1a0);
  uStack_d90 = 0x3f800000;
  uStack_d8c = 0;
  uStack_d88 = 0;
  uStack_d84 = 0x3f800000;
  auVar6._4_4_ = uStack_19c;
  auVar6._0_4_ = uStack_1a0;
  auVar6._8_4_ = uStack_198;
  auVar6._12_4_ = uStack_194;
  auVar39 = _lqc2(auVar6);
  auVar5._12_4_ = 0x3f800000;
  auVar5._0_12_ = ZEXT812(0x3f800000);
  auVar40 = _lqc2(auVar5);
  auVar39 = _vmul(auVar39,auVar40);
  auVar39 = _vaddbc(auVar39,auVar39);
  auVar39 = _vaddbc(auVar39,auVar39);
  auVar39 = _qmfc2(auVar39._0_4_);
  if (auVar39._0_4_ <= -1.0) {
    fVar32 = 3.141592;
  }
  else if (1.0 <= auVar39._0_4_) {
    fVar32 = 0.0;
  }
  else {
    fVar32 = (float)acosf();
  }
  auVar39 = _vmr32(in_vf0);
  auVar40 = _vmr32(auVar39);
  auVar41 = _vmr32(auVar40);
  auStack_a0 = _sqc2(in_vf0);
  auStack_b0 = _sqc2(auVar39);
  auStack_c0 = _sqc2(auVar40);
  auStack_d0 = _sqc2(auVar41);
  sceVu0RotMatrixZ(fVar32,auStack_d0,auStack_d0);
  uStack_db0 = 0x3f800000;
  uStack_dac = 0;
  uStack_da8 = 0;
  uStack_da4 = 0x3f800000;
  ApplyMatrix__6MatrixCFRC7FVector(&uStack_da0,auStack_d0,&uStack_db0);
  uStack_190 = uStack_da0;
  uStack_18c = uStack_d9c;
  uStack_188 = uStack_d98;
  uStack_184 = uStack_d94;
  auVar8._4_4_ = uStack_d9c;
  auVar8._0_4_ = uStack_da0;
  auVar8._8_4_ = uStack_d98;
  auVar8._12_4_ = uStack_d94;
  auVar39 = _lqc2(auVar8);
  auVar7._4_4_ = uStack_19c;
  auVar7._0_4_ = uStack_1a0;
  auVar7._8_4_ = uStack_198;
  auVar7._12_4_ = uStack_194;
  auVar40 = _lqc2(auVar7);
  auVar39 = _vmul(auVar39,auVar40);
  auVar39 = _vaddbc(auVar39,auVar39);
  auVar39 = _vaddbc(auVar39,auVar39);
  auVar39 = _qmfc2(auVar39._0_4_);
  if (auVar39._0_4_ < 0.999999) {
    fVar32 = -fVar32;
  }
  auVar39 = _vmr32(in_vf0);
  auVar40 = _vmr32(auVar39);
  auVar41 = _vmr32(auVar40);
  auStack_a0 = _sqc2(in_vf0);
  auStack_b0 = _sqc2(auVar39);
  auStack_c0 = _sqc2(auVar40);
  auStack_d0 = _sqc2(auVar41);
  sceVu0RotMatrixZ(fVar32,auStack_d0,auStack_d0);
  auVar10._4_4_ = afStack_180[1];
  auVar10._0_4_ = afStack_180[0];
  auVar10._8_4_ = afStack_180[2];
  auVar10._12_4_ = afStack_180[3];
  auVar40 = _lqc2(auVar10);
  auVar39 = _lqc2(_auStack_160);
  auVar39 = _vsub(auVar39,auVar40);
  _auStack_160 = _sqc2(auVar39);
  auVar11._4_4_ = afStack_180[1];
  auVar11._0_4_ = afStack_180[0];
  auVar11._8_4_ = afStack_180[2];
  auVar11._12_4_ = afStack_180[3];
  auVar40 = _lqc2(auVar11);
  auVar39 = _lqc2(_auStack_150);
  auVar39 = _vsub(auVar39,auVar40);
  _auStack_150 = _sqc2(auVar39);
  fStack_10 = (float)Length__7FVectorCFv(auStack_160);
  fStack_e30 = (float)Length__7FVectorCFv(auStack_150);
  fStack_dc0 = -fStack_10;
  fStack_dbc = fStack_10;
  uStack_db8 = 0;
  uStack_db4 = 0x3f800000;
  fStack_21c = fStack_10;
  uStack_218 = 0;
  uStack_214 = 0x3f800000;
  fStack_dd0 = -fStack_10;
  fStack_dcc = -fStack_10;
  uStack_dc8 = 0;
  uStack_dc4 = 0x3f800000;
  uStack_208 = 0;
  uStack_204 = 0x3f800000;
  uStack_de0 = 0;
  fStack_ddc = fStack_10;
  uStack_dd8 = 0;
  uStack_dd4 = 0x3f800000;
  uStack_200 = 0;
  fStack_1fc = fStack_10;
  uStack_1f8 = 0;
  uStack_1f4 = 0x3f800000;
  uStack_df0 = 0;
  fStack_dec = -fStack_10;
  uStack_de8 = 0;
  uStack_de4 = 0x3f800000;
  uStack_1f0 = 0;
  uStack_1e8 = 0;
  uStack_1e4 = 0x3f800000;
  uStack_e00 = 0;
  uStack_df8 = 0;
  uStack_df4 = 0x3f800000;
  uStack_1e0 = 0;
  uStack_1d8 = 0;
  uStack_1d4 = 0x3f800000;
  fStack_e0c = -fStack_e30;
  uStack_e10 = 0;
  uStack_e08 = 0;
  uStack_e04 = 0x3f800000;
  uStack_1d0 = 0;
  uStack_1c8 = 0;
  uStack_1c4 = 0x3f800000;
  uStack_e18 = 0;
  uStack_e14 = 0x3f800000;
  uStack_1b8 = 0;
  uStack_1b4 = 0x3f800000;
  fStack_e2c = -fStack_e30;
  uStack_e28 = 0;
  uStack_e24 = 0x3f800000;
  uStack_1a8 = 0;
  uStack_1a4 = 0x3f800000;
  fStack_e20 = fStack_e30;
  fStack_e1c = fStack_e30;
  fStack_dfc = fStack_e30;
  fStack_220 = fStack_dc0;
  fStack_210 = fStack_dd0;
  fStack_20c = fStack_dcc;
  fStack_1ec = fStack_dec;
  fStack_1dc = fStack_e30;
  fStack_1cc = fStack_e0c;
  fStack_1c0 = fStack_e30;
  fStack_1bc = fStack_e30;
  fStack_1b0 = fStack_e30;
  fStack_1ac = fStack_e2c;
  fStack_c = fStack_e30;
  RotTransVector(afStack_2a0,&fStack_220,auStack_d0,8);
  for (iVar28 = 0; iVar28 < 4; iVar28 = iVar28 + 1) {
    aiStack_ba0[iVar28 * 4] = (int)((afStack_180[0] + afStack_2a0[iVar28 * 4] + 1792.0) * 16.0);
    aiStack_ba0[iVar28 * 4 + 1] =
         (int)((afStack_180[1] + afStack_2a0[iVar28 * 4 + 1] + 1824.0) * 16.0);
    aiStack_ba0[iVar28 * 4 + 2] = aiStack_6e0[2];
  }
  for (iVar28 = 4; iVar28 < 8; iVar28 = iVar28 + 1) {
    aiStack_ba0[iVar28 * 4] = (int)((afStack_180[4] + afStack_2a0[iVar28 * 4] + 1792.0) * 16.0);
    aiStack_ba0[iVar28 * 4 + 1] =
         (int)((afStack_180[5] + afStack_2a0[iVar28 * 4 + 1] + 1824.0) * 16.0);
    aiStack_ba0[iVar28 * 4 + 2] = iStack_6c8;
  }
  for (iVar28 = 0; iVar28 < 0x10; iVar28 = iVar28 + 1) {
    for (iVar36 = 0; iVar36 < 4; iVar36 = iVar36 + 1) {
      afStack_6a0[(iVar36 + iVar28 * 4) * 4] =
           *(float *)(param_1 + iVar28 * 0x10 + 0x180) +
           *(float *)(param_1 + iVar28 * 4 + 0x280) * afStack_120[iVar36 * 4];
      afStack_6a0[(iVar36 + iVar28 * 4) * 4 + 1] =
           *(float *)(param_1 + iVar28 * 0x10 + 0x184) +
           *(float *)(param_1 + iVar28 * 4 + 0x280) * afStack_120[iVar36 * 4 + 1];
      afStack_6a0[(iVar36 + iVar28 * 4) * 4 + 2] =
           *(float *)(param_1 + iVar28 * 0x10 + 0x188) +
           *(float *)(param_1 + iVar28 * 4 + 0x280) * afStack_120[iVar36 * 4 + 2];
      afStack_6a0[(iVar36 + iVar28 * 4) * 4 + 3] = 1.0;
    }
  }
  sceVu0RotTransPersN(aiStack_ba0 + 0x20,aiStack_ba0 + 0x120,afStack_6a0,0x40,0);
  bVar4 = false;
  iVar28 = 0;
  for (iVar36 = 0; iVar36 < 0x48; iVar36 = iVar36 + 1) {
    if (iVar36 < 8) {
      if ((((aiStack_ba0[iVar36 * 4] < 0) || (0x10000 < aiStack_ba0[iVar36 * 4])) ||
          (aiStack_ba0[iVar36 * 4 + 1] < 0)) ||
         ((0x10000 < aiStack_ba0[iVar36 * 4 + 1] || (aiStack_ba0[iVar36 * 4 + 2] < 0)))) {
        bVar4 = true;
      }
      aiStack_ba0[iVar36 * 4 + 2] = (int)((float)aiStack_ba0[iVar36 * 4 + 2] / 16.0);
      iVar28 = iVar28 + aiStack_ba0[iVar36 * 4 + 2];
    }
    else {
      uVar30 = iVar36 - 8U & 3;
      if (((int)(iVar36 - 8U) < 0) && (uVar30 != 0)) {
        uVar30 = uVar30 - 4;
      }
      if (uVar30 == 0) {
        iVar37 = iVar36 + -8;
        if (iVar37 < 0) {
          iVar37 = iVar36 + -5;
        }
        *(undefined2 *)(param_1 + (iVar37 >> 2) * 2 + 0x11c) = 0;
      }
      if (((aiStack_ba0[iVar36 * 4] < 0) || (0x10000 < aiStack_ba0[iVar36 * 4])) ||
         ((aiStack_ba0[iVar36 * 4 + 1] < 0 ||
          ((0x10000 < aiStack_ba0[iVar36 * 4 + 1] || (aiStack_ba0[iVar36 * 4 + 2] < 0)))))) {
        iVar37 = iVar36 + -8;
        if (iVar37 < 0) {
          iVar37 = iVar36 + -5;
        }
        *(undefined2 *)(param_1 + (iVar37 >> 2) * 2 + 0x11c) = 1;
      }
      aiStack_ba0[iVar36 * 4 + 2] = (int)((float)aiStack_ba0[iVar36 * 4 + 2] / 16.0);
    }
  }
  if (iVar28 < 0) {
    iVar28 = iVar28 + 7;
  }
  *(int *)(param_1 + 0x50) = iVar28 >> 3;
  bVar1 = (*(byte *)(param_1 + 0x40) & 1) == 0;
  uVar30 = (uint)bVar1;
  if (*(int *)(param_1 + uVar30 * 4 + 0x18) == 0) {
    uVar26 = __nwa__FUi(0x6a0);
    *(undefined4 *)(param_1 + uVar30 * 4 + 0x18) = uVar26;
    iVar28 = *(int *)(param_1 + uVar30 * 4 + 0x18);
    *(undefined4 *)(iVar28 + 0x10) = 0x10000012;
    *(undefined4 *)(iVar28 + 0x14) = 0;
    *(undefined4 *)(iVar28 + 0x18) = 0;
    *(undefined4 *)(iVar28 + 0x1c) = 0x50000012;
    *(undefined8 *)(iVar28 + 0x20) = 0x6000000000000001;
    *(undefined8 *)(iVar28 + 0x28) = 0xe6e8ee;
    *(undefined8 *)(iVar28 + 0x30) = 1;
    *(undefined8 *)(iVar28 + 0x38) = 0x3f;
    *(undefined8 *)(iVar28 + 0x40) = 0x60;
    *(undefined8 *)(iVar28 + 0x48) = 0x14;
    *(undefined8 *)(iVar28 + 0x50) = 5;
    *(undefined8 *)(iVar28 + 0x58) = 0;
    *(undefined8 *)(iVar28 + 0x60) = 0x53001;
    *(undefined8 *)(iVar28 + 0x68) = 0x47;
    uVar27 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x42ec),1);
    *(undefined8 *)(iVar28 + 0x70) = uVar27;
    *(undefined8 *)(iVar28 + 0x78) = 0;
    *(undefined8 *)(iVar28 + 0x80) = 0x48;
    *(undefined8 *)(iVar28 + 0x88) = 0x42;
    *(undefined8 *)(iVar28 + 0x90) = 0x6400000000000001;
    *(undefined8 *)(iVar28 + 0x98) = 0xc3c310;
    *(undefined8 *)(iVar28 + 0xa0) = 0x154;
    *(undefined8 *)(iVar28 + 0xb0) = 0;
    *(long *)(iVar28 + 0xc0) =
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42ec) + 4) << 4) << 0x10;
    *(undefined8 *)(iVar28 + 0xd0) = 0x2400000000008006;
    *(undefined8 *)(iVar28 + 0xd8) = 0x43;
    *(long *)(iVar28 + 0xe0) =
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42ec) + 2) << 3);
    *(long *)(iVar28 + 0xf0) =
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42ec) + 2) << 3) |
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42ec) + 4) << 4) << 0x10;
    *(long *)(iVar28 + 0x100) =
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42ec) + 2) << 3);
    *(long *)(iVar28 + 0x110) =
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42ec) + 2) << 3) |
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42ec) + 4) << 4) << 0x10;
    *(long *)(iVar28 + 0x120) =
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42ec) + 2) << 4);
    *(long *)(iVar28 + 0x130) =
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42ec) + 2) << 4) |
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42ec) + 4) << 4) << 0x10;
    *(undefined4 *)(iVar28 + 0x140) = 0x50000000;
    *(undefined4 *)(iVar28 + 0x144) =
         *(undefined4 *)
          (*(int *)(iGpffff86b4 + 0x42f0) +
           (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f0) + 10) * 4 + 0xc);
    *(undefined4 *)(iVar28 + 0x148) = 0;
    *(undefined4 *)(iVar28 + 0x14c) = 0;
    *(undefined4 *)(iVar28 + 0x150) = 0x60000054;
    *(undefined4 *)(iVar28 + 0x154) = 0;
    *(undefined4 *)(iVar28 + 0x158) = 0;
    *(undefined4 *)(iVar28 + 0x15c) = 0x50000054;
    *(undefined8 *)(iVar28 + 0x160) = 0x2000000000000001;
    *(undefined8 *)(iVar28 + 0x168) = 0x6e;
    *(undefined8 *)(iVar28 + 0x170) = 1;
    *(undefined8 *)(iVar28 + 0x178) = 0x3f;
    uVar27 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x42f0),1);
    *(undefined8 *)(iVar28 + 0x180) = uVar27;
    *(undefined8 *)(iVar28 + 0x188) = 0;
    auVar29._8_8_ = in_v1_udw;
    auVar29._0_8_ = 0xa400000000008010;
    auVar3._4_4_ = in_zero_hi;
    auVar3._0_4_ = in_zero_lo;
    auVar3._8_4_ = in_zero_udw;
    auVar3._12_4_ = in_register_0000000c;
    auVar39 = _pcpyld(auVar3,auVar29);
    *(long *)(iVar28 + 400) = auVar39._0_8_;
    *(undefined8 *)(iVar28 + 0x198) = 0x4343c3c310;
    for (iVar36 = 0; iVar36 < 0x10; iVar36 = iVar36 + 1) {
      *(undefined8 *)(iVar28 + (iVar36 * 5 + 0x1a) * 0x10) = 0x154;
      *(long *)(iVar28 + (iVar36 * 5 + 0x1b) * 0x10) =
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f0) + 2) << 2) |
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f0) + 4) << 2) << 0x10;
      *(long *)(iVar28 + (iVar36 * 5 + 0x1c) * 0x10) =
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f0) + 2) << 2) |
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f0) + 4) * 0xc) << 0x10;
      *(long *)(iVar28 + (iVar36 * 5 + 0x1d) * 0x10) =
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f0) + 4) << 2) << 0x10 |
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f0) + 2) * 0xc);
      *(long *)(iVar28 + (iVar36 * 5 + 0x1e) * 0x10) =
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f0) + 2) * 0xc) |
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f0) + 4) * 0xc) << 0x10;
    }
  }
  puVar2 = *(undefined4 **)(param_1 + uVar30 * 4 + 0x18);
  *puVar2 = 0x50000000;
  puVar2[1] = *(undefined4 *)
               (*(int *)(iGpffff86b4 + 0x42ec) +
                (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42ec) + 10) * 4 + 0xc);
  puVar2[2] = 0;
  puVar2[3] = 0;
  iVar28 = (int)(*(float *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x144) + 0x4e4
                           ) *
                 *(float *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x144) + 0x4ec
                           ) * 128.0);
  fVar32 = (float)sinf(*(undefined4 *)(param_1 + 0xf8));
  fVar32 = (fVar32 + 1.0) / 2.0;
  iVar36 = (int)((float)*(byte *)(*(int *)(param_1 + 0x60) * 0xc + 0x652b64) +
                fVar32 * (float)(int)((uint)*(byte *)(*(int *)(param_1 + 0x60) * 0xc + 0x652b68) -
                                     (uint)*(byte *)(*(int *)(param_1 + 0x60) * 0xc + 0x652b64)));
  iVar37 = (int)((float)*(byte *)(*(int *)(param_1 + 0x60) * 0xc + 0x652b65) +
                fVar32 * (float)(int)((uint)*(byte *)(*(int *)(param_1 + 0x60) * 0xc + 0x652b69) -
                                     (uint)*(byte *)(*(int *)(param_1 + 0x60) * 0xc + 0x652b65)));
  iVar38 = (int)((float)*(byte *)(*(int *)(param_1 + 0x60) * 0xc + 0x652b66) +
                fVar32 * (float)(int)((uint)*(byte *)(*(int *)(param_1 + 0x60) * 0xc + 0x652b6a) -
                                     (uint)*(byte *)(*(int *)(param_1 + 0x60) * 0xc + 0x652b66)));
  *(ulong *)(puVar2 + 0x2a) =
       (long)iVar28 << 0x18 | (long)iVar38 << 0x10 | (long)iVar36 | (long)iVar37 << 8 | 0x100000000;
  if (bVar4) {
    *(undefined8 *)(puVar2 + 0x2e) = 0x71006f00;
    *(undefined8 *)(puVar2 + 0x32) = 0x71006f00;
    *(undefined8 *)(puVar2 + 0x3a) = 0x71006f00;
    *(undefined8 *)(puVar2 + 0x3e) = 0x71006f00;
    *(undefined8 *)(puVar2 + 0x42) = 0x71006f00;
    *(undefined8 *)(puVar2 + 0x46) = 0x71006f00;
    *(undefined8 *)(puVar2 + 0x4a) = 0x71006f00;
    *(undefined8 *)(puVar2 + 0x4e) = 0x71006f00;
  }
  else {
    *(long *)(puVar2 + 0x2e) =
         (long)aiStack_ba0[2] << 0x20 | (long)aiStack_ba0[0] | (long)aiStack_ba0[1] << 0x10;
    *(long *)(puVar2 + 0x32) =
         (long)aiStack_ba0[6] << 0x20 | (long)aiStack_ba0[4] | (long)aiStack_ba0[5] << 0x10;
    *(long *)(puVar2 + 0x3a) =
         (long)aiStack_ba0[10] << 0x20 | (long)aiStack_ba0[8] | (long)aiStack_ba0[9] << 0x10;
    *(long *)(puVar2 + 0x3e) =
         (long)aiStack_ba0[0xe] << 0x20 | (long)aiStack_ba0[0xc] | (long)aiStack_ba0[0xd] << 0x10;
    *(long *)(puVar2 + 0x42) =
         (long)aiStack_ba0[0x12] << 0x20 | (long)aiStack_ba0[0x10] | (long)aiStack_ba0[0x11] << 0x10
    ;
    *(long *)(puVar2 + 0x46) =
         (long)aiStack_ba0[0x16] << 0x20 | (long)aiStack_ba0[0x14] | (long)aiStack_ba0[0x15] << 0x10
    ;
    *(long *)(puVar2 + 0x4a) =
         (long)aiStack_ba0[0x1a] << 0x20 | (long)aiStack_ba0[0x18] | (long)aiStack_ba0[0x19] << 0x10
    ;
    *(long *)(puVar2 + 0x4e) =
         (long)aiStack_ba0[0x1e] << 0x20 | (long)aiStack_ba0[0x1c] | (long)aiStack_ba0[0x1d] << 0x10
    ;
  }
  for (iVar31 = 0; iVar31 < 0x10; iVar31 = iVar31 + 1) {
    if ((*(short *)(param_1 + iVar31 * 2 + 0xfc) == 0) ||
       (*(short *)(param_1 + iVar31 * 2 + 0x11c) != 0)) {
      *(undefined8 *)(puVar2 + (iVar31 * 5 + 0x1b) * 4 + 2) = 0x71006f00;
      *(undefined8 *)(puVar2 + (iVar31 * 5 + 0x1c) * 4 + 2) = 0x71006f00;
      *(undefined8 *)(puVar2 + (iVar31 * 5 + 0x1d) * 4 + 2) = 0x71006f00;
      *(undefined8 *)(puVar2 + (iVar31 * 5 + 0x1e) * 4 + 2) = 0x71006f00;
    }
    else {
      *(ulong *)(puVar2 + (iVar31 * 5 + 0x1a) * 4 + 2) =
           (long)(int)(((float)iVar28 * *(float *)(param_1 + iVar31 * 4 + 0x2c0)) / 128.0) << 0x18 |
           (long)iVar38 << 0x10 | (long)iVar36 | (long)iVar37 << 8 | 0x100000000;
      *(long *)(puVar2 + (iVar31 * 5 + 0x1b) * 4 + 2) =
           (long)aiStack_ba0[(iVar31 * 4 + 8) * 4 + 2] << 0x20 |
           (long)aiStack_ba0[(iVar31 * 4 + 8) * 4] |
           (long)aiStack_ba0[(iVar31 * 4 + 8) * 4 + 1] << 0x10;
      *(long *)(puVar2 + (iVar31 * 5 + 0x1c) * 4 + 2) =
           (long)aiStack_ba0[(iVar31 * 4 + 9) * 4 + 2] << 0x20 |
           (long)aiStack_ba0[(iVar31 * 4 + 9) * 4] |
           (long)aiStack_ba0[(iVar31 * 4 + 9) * 4 + 1] << 0x10;
      *(long *)(puVar2 + (iVar31 * 5 + 0x1d) * 4 + 2) =
           (long)aiStack_ba0[(iVar31 * 4 + 10) * 4 + 2] << 0x20 |
           (long)aiStack_ba0[(iVar31 * 4 + 10) * 4] |
           (long)aiStack_ba0[(iVar31 * 4 + 10) * 4 + 1] << 0x10;
      *(long *)(puVar2 + (iVar31 * 5 + 0x1e) * 4 + 2) =
           (long)aiStack_ba0[(iVar31 * 4 + 0xb) * 4 + 2] << 0x20 |
           (long)aiStack_ba0[(iVar31 * 4 + 0xb) * 4] |
           (long)aiStack_ba0[(iVar31 * 4 + 0xb) * 4 + 1] << 0x10;
    }
  }
  *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfe | bVar1;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054ae30  EndSet__16BoxAddAttribute1Fv
 * C++: BoxAddAttribute1::EndSet()
 * size: 0x10 bytes
 * --------------------------------------------------------------------------- */
void EndSet__16BoxAddAttribute1Fv(void)

{
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b830  @24@__dt__16BoxAddAttribute1Fv
 * C++: @24@__dt__16BoxAddAttribute1Fv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int * _24___dt__16BoxAddAttribute1Fv(int *param_1,short param_2)

{
  int *piVar1;
  
  piVar1 = param_1 + -6;
  if (piVar1 != (int *)0x0) {
    param_1[-1] = 0x409ca0;
    param_1[4] = 0x409cb0;
    param_1[7] = 0x409cc0;
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
 * JP: 0x0054b840  @44@__dt__16BoxAddAttribute1Fv
 * C++: @44@__dt__16BoxAddAttribute1Fv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int _44___dt__16BoxAddAttribute1Fv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x2c;
  if (iVar1 != 0) {
    *(undefined4 *)(param_1 + -0x18) = 0x409ca0;
    *(undefined4 *)(param_1 + -4) = 0x409cb0;
    *(undefined4 *)(param_1 + 8) = 0x409cc0;
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

