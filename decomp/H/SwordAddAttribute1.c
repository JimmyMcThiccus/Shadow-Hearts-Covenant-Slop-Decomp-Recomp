/* decomp/H/SwordAddAttribute1.c — cleaned Ghidra output (SH2JP_BATTLE.BIN, JP Furokuban, base 0x00430a00).
 * 10 function(s). Types: see types.h. Names/gp globals resolved from symbols/SLPM_602.19.syms. */
#include "types.h"

/* ---------------------------------------------------------------------------
 * JP: 0x00523b70  __ct__18SwordAddAttribute1Fiii
 * C++: SwordAddAttribute1::__ct(int, int, int)
 * size: 0x208 bytes
 * --------------------------------------------------------------------------- */
int __ct__18SwordAddAttribute1Fiii
              (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  int iVar1;
  undefined4 *puVar2;
  
  __ct__6BtlEffFii(param_1,param_2,param_3);
  *(undefined4 *)(param_1 + 0x14) = 0x409de0;
  *(undefined4 *)(param_1 + 0x28) = 0x409df0;
  *(undefined4 *)(param_1 + 0x34) = 0x409e00;
  puVar2 = (undefined4 *)(param_1 + 0x70);
  do {
    *puVar2 = in_zero_lo;
    puVar2[1] = in_zero_hi;
    puVar2[2] = in_zero_udw;
    puVar2[3] = in_register_0000000c;
    puVar2 = puVar2 + 4;
  } while (puVar2 != (undefined4 *)(param_1 + 0x90));
  puVar2 = (undefined4 *)(param_1 + 0x1a0);
  do {
    *puVar2 = in_zero_lo;
    puVar2[1] = in_zero_hi;
    puVar2[2] = in_zero_udw;
    puVar2[3] = in_register_0000000c;
    puVar2 = puVar2 + 4;
  } while (puVar2 != (undefined4 *)(param_1 + 0x3a0));
  *(undefined4 *)(param_1 + 0x40) = 0;
  *(undefined4 *)(param_1 + 0x44) = param_2;
  *(undefined4 *)(param_1 + 0x48) = param_3;
  *(undefined4 *)(param_1 + 0x4c) = 6;
  *(undefined4 *)(param_1 + 0x5c) = 0;
  *(undefined4 *)(param_1 + 0x60) = param_4;
  *(undefined4 *)(param_1 + 0x90) = 0;
  *(undefined4 *)(param_1 + 0x94) = 0;
  *(undefined4 *)(param_1 + 0x98) = 0;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  *(undefined4 *)(param_1 + 0x18) = 0;
  for (iVar1 = 0; iVar1 < 0x20; iVar1 = iVar1 + 1) {
    *(undefined2 *)(param_1 + iVar1 * 2 + 0x9c) = 0;
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
 * JP: 0x00523d80  __dt__18SwordAddAttribute1Fv
 * C++: SwordAddAttribute1::__dt()
 * size: 0x154 bytes
 * --------------------------------------------------------------------------- */
int __dt__18SwordAddAttribute1Fv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x14) = 0x409de0;
    *(undefined4 *)(param_1 + 0x28) = 0x409df0;
    *(undefined4 *)(param_1 + 0x34) = 0x409e00;
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
 * JP: 0x00523ee0  Destruct__18SwordAddAttribute1Fv
 * C++: SwordAddAttribute1::Destruct()
 * size: 0xcc bytes
 * --------------------------------------------------------------------------- */
void Destruct__18SwordAddAttribute1Fv(int param_1)

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
 * JP: 0x00523fb0  Polling__18SwordAddAttribute1Fv
 * C++: SwordAddAttribute1::Polling()
 * size: 0xbd8 bytes
 * --------------------------------------------------------------------------- */
undefined8 Polling__18SwordAddAttribute1Fv(int param_1)

{
  short sVar1;
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  int iVar2;
  int iVar3;
  undefined1 (*pauVar4) [16];
  int iVar5;
  float fVar6;
  undefined1 in_vf0 [16];
  undefined1 auVar7 [16];
  undefined1 auVar8 [16];
  undefined1 auVar9 [16];
  undefined1 auStack_110 [16];
  undefined1 auStack_100 [16];
  undefined1 auStack_f0 [16];
  undefined1 auStack_e0 [16];
  undefined1 auStack_d0 [8];
  undefined4 uStack_c8;
  undefined4 uStack_c4;
  undefined1 auStack_c0 [8];
  undefined4 uStack_b8;
  undefined4 uStack_b4;
  undefined1 auStack_b0 [8];
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  undefined1 auStack_a0 [8];
  undefined4 uStack_98;
  undefined4 uStack_94;
  undefined4 uStack_90;
  undefined4 uStack_8c;
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined1 auStack_80 [8];
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined1 auStack_60 [8];
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
  
  fVar6 = *(float *)(iGpffff86b4 + 0x38);
  if ((*(byte *)(iGpffff86b4 + 0x24) & 1) != 0) {
    fVar6 = 0.0;
  }
  *(float *)(param_1 + 0x98) = *(float *)(param_1 + 0x98) + fVar6 * 6.2831855 * 0.75;
  if (3.1415927 <= *(float *)(param_1 + 0x98)) {
    *(float *)(param_1 + 0x98) = *(float *)(param_1 + 0x98) - 6.2831855;
  }
  if (((*(int *)(param_1 + 0x5c) != 1) && (*(int *)(param_1 + 0x5c) == 0)) &&
     (*(float *)(param_1 + 0x90) = *(float *)(param_1 + 0x90) + fVar6 * 2.0,
     1.0 <= *(float *)(param_1 + 0x90))) {
    *(undefined4 *)(param_1 + 0x90) = 0x3f800000;
    *(undefined4 *)(param_1 + 0x5c) = 1;
  }
  iVar2 = GetRegDat__9RegDatApiFiii(0x3a,*(undefined4 *)
                                (iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x55c),
                          0xffffffffffffffff);
  iVar2 = *(int *)(*(short *)(iVar2 + 0x14) * 4 + 0x651180);
  sVar1 = *(short *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 400);
  auVar7 = _vmr32(in_vf0);
  auVar8 = _vmr32(auVar7);
  auVar9 = _vmr32(auVar8);
  auStack_10 = _sqc2(in_vf0);
  auStack_20 = _sqc2(auVar7);
  auStack_30 = _sqc2(auVar8);
  auStack_40 = _sqc2(auVar9);
  iVar3 = (int)sVar1;
  switch(*(undefined2 *)(iVar2 + sVar1 * 0x1c)) {
  case 0:
    pauVar4 = (undefined1 (*) [16])
              (*(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x144) + 0x30) +
               (uint)*(ushort *)(iVar2 + iVar3 * 0x1c + 2) * 0x1f0 + (bGpffff8340 & 1) * 0x40);
    auStack_40 = *pauVar4;
    auStack_30 = pauVar4[1];
    auStack_20 = pauVar4[2];
    auStack_10 = pauVar4[3];
    break;
  case 1:
    pauVar4 = (undefined1 (*) [16])
              (*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x144) +
                                0x52c) + 0x30) + (uint)*(ushort *)(iVar2 + iVar3 * 0x1c + 2) * 0x1f0
              + (bGpffff8340 & 1) * 0x40);
    auStack_40 = *pauVar4;
    auStack_30 = pauVar4[1];
    auStack_20 = pauVar4[2];
    auStack_10 = pauVar4[3];
    break;
  case 2:
    pauVar4 = (undefined1 (*) [16])
              (*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x144) +
                                0x530) + 0x30) + (uint)*(ushort *)(iVar2 + iVar3 * 0x1c + 2) * 0x1f0
              + (bGpffff8340 & 1) * 0x40);
    auStack_40 = *pauVar4;
    auStack_30 = pauVar4[1];
    auStack_20 = pauVar4[2];
    auStack_10 = pauVar4[3];
    break;
  case 3:
    pauVar4 = (undefined1 (*) [16])
              (*(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x144) + 0x30) +
               (uint)*(byte *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 +
                                                0x144) + 0xe4) +
                              (uint)*(ushort *)(iVar2 + iVar3 * 0x1c + 2) * 0x110) * 0x1f0 +
              (bGpffff8340 & 1) * 0x40);
    auStack_40 = *pauVar4;
    auStack_30 = pauVar4[1];
    auStack_20 = pauVar4[2];
    auStack_10 = pauVar4[3];
    break;
  case 4:
    pauVar4 = (undefined1 (*) [16])
              (*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x144) +
                                0x52c) + 0x30) +
               (uint)*(byte *)(*(int *)(*(int *)(*(int *)(iGpffff86b4 +
                                                          *(int *)(param_1 + 0x48) * 0x4f0 + 0x144)
                                                + 0x52c) + 0xe4) +
                              (uint)*(ushort *)(iVar2 + iVar3 * 0x1c + 2) * 0x110) * 0x1f0 +
              (bGpffff8340 & 1) * 0x40);
    auStack_40 = *pauVar4;
    auStack_30 = pauVar4[1];
    auStack_20 = pauVar4[2];
    auStack_10 = pauVar4[3];
    break;
  case 5:
    pauVar4 = (undefined1 (*) [16])
              (*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x144) +
                                0x530) + 0x30) +
               (uint)*(byte *)(*(int *)(*(int *)(*(int *)(iGpffff86b4 +
                                                          *(int *)(param_1 + 0x48) * 0x4f0 + 0x144)
                                                + 0x530) + 0xe4) +
                              (uint)*(ushort *)(iVar2 + iVar3 * 0x1c + 2) * 0x110) * 0x1f0 +
              (bGpffff8340 & 1) * 0x40);
    auStack_40 = *pauVar4;
    auStack_30 = pauVar4[1];
    auStack_20 = pauVar4[2];
    auStack_10 = pauVar4[3];
  }
  iVar5 = (int)sVar1;
  uStack_68 = *(undefined4 *)(iVar2 + iVar5 * 0x1c + 0xc);
  uStack_6c = *(undefined4 *)(iVar2 + iVar5 * 0x1c + 8);
  uStack_70 = *(undefined4 *)(iVar2 + iVar5 * 0x1c + 4);
  uStack_64 = 0x3f800000;
  ApplyMatrix__6MatrixCFRC7FVector(auStack_60,auStack_40,&uStack_70);
  *(int *)(param_1 + 0x70) = auStack_60._0_4_;
  *(int *)(param_1 + 0x74) = auStack_60._4_4_;
  *(undefined4 *)(param_1 + 0x78) = uStack_58;
  *(undefined4 *)(param_1 + 0x7c) = uStack_54;
  uStack_88 = *(undefined4 *)(iVar2 + iVar5 * 0x1c + 0x18);
  uStack_8c = *(undefined4 *)(iVar2 + iVar3 * 0x1c + 0x14);
  uStack_90 = *(undefined4 *)(iVar2 + iVar3 * 0x1c + 0x10);
  uStack_84 = 0x3f800000;
  ApplyMatrix__6MatrixCFRC7FVector(auStack_80,auStack_40,&uStack_90);
  *(int *)(param_1 + 0x80) = auStack_80._0_4_;
  *(int *)(param_1 + 0x84) = auStack_80._4_4_;
  *(undefined4 *)(param_1 + 0x88) = uStack_78;
  *(undefined4 *)(param_1 + 0x8c) = uStack_74;
  *(float *)(param_1 + 0x94) = *(float *)(param_1 + 0x94) + fVar6;
  uStack_50 = in_zero_lo;
  uStack_4c = in_zero_hi;
  uStack_48 = in_zero_udw;
  uStack_44 = in_register_0000000c;
  for (iVar2 = 0; iVar2 < 0x20; iVar2 = iVar2 + 1) {
    sVar1 = *(short *)(param_1 + iVar2 * 2 + 0x9c);
    if (sVar1 == 1) {
      iVar3 = param_1 + iVar2 * 4;
      *(float *)(iVar3 + 0x11c) = *(float *)(iVar3 + 0x11c) + fVar6;
      iVar3 = param_1 + iVar2 * 0x10;
      *(float *)(iVar3 + 0x1a4) = *(float *)(iVar3 + 0x1a4) - fVar6 * 2.0;
      if (*(float *)(param_1 + iVar2 * 4 + 0x11c) < 0.6666667) {
        *(undefined4 *)(param_1 + iVar2 * 4 + 0x3a0) = 0x43000000;
      }
      else {
        *(float *)(param_1 + iVar2 * 4 + 0x3a0) =
             ((1.0 - *(float *)(param_1 + iVar2 * 4 + 0x11c)) / 0.33333334) * 128.0;
      }
      if ((1.0 <= *(float *)(param_1 + iVar2 * 4 + 0x11c)) &&
         (*(undefined2 *)(param_1 + iVar2 * 2 + 0x9c) = 0, 0.033333335 <= *(float *)(param_1 + 0x94)
         )) {
        *(undefined2 *)(param_1 + iVar2 * 2 + 0x9c) = 1;
        *(undefined4 *)(param_1 + iVar2 * 4 + 0x11c) = 0;
        auVar7 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x80));
        auVar8 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x70));
        auVar7 = _vsub(auVar7,auVar8);
        auStack_100 = _sqc2(auVar7);
        __ct__7FVectorFRC7FVector(auStack_c0,auStack_100);
        uStack_50 = auStack_c0._0_4_;
        uStack_4c = auStack_c0._4_4_;
        uStack_48 = uStack_b8;
        uStack_44 = uStack_b4;
        iVar3 = rand();
        __amu__7FVectorFf((float)iVar3 / 2.1474836e+09,&uStack_50);
        auVar8 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x70));
        auVar7._4_4_ = uStack_4c;
        auVar7._0_4_ = uStack_50;
        auVar7._8_4_ = uStack_48;
        auVar7._12_4_ = uStack_44;
        auVar7 = _lqc2(auVar7);
        auVar7 = _vadd(auVar8,auVar7);
        auStack_110 = _sqc2(auVar7);
        __ct__7FVectorFRC7FVector(auStack_d0,auStack_110);
        iVar3 = param_1 + iVar2 * 0x10;
        *(int *)(iVar3 + 0x1a0) = auStack_d0._0_4_;
        *(int *)(iVar3 + 0x1a4) = auStack_d0._4_4_;
        *(undefined4 *)(iVar3 + 0x1a8) = uStack_c8;
        *(undefined4 *)(iVar3 + 0x1ac) = uStack_c4;
        *(undefined4 *)(param_1 + iVar2 * 4 + 0x3a0) = 0x3f800000;
        *(float *)(param_1 + 0x94) = *(float *)(param_1 + 0x94) - 0.033333335;
      }
    }
    else if ((sVar1 == 0) && (0.033333335 <= *(float *)(param_1 + 0x94))) {
      *(undefined2 *)(param_1 + iVar2 * 2 + 0x9c) = 1;
      *(undefined4 *)(param_1 + iVar2 * 4 + 0x11c) = 0;
      auVar7 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x80));
      auVar8 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x70));
      auVar7 = _vsub(auVar7,auVar8);
      auStack_e0 = _sqc2(auVar7);
      __ct__7FVectorFRC7FVector(auStack_a0,auStack_e0);
      uStack_50 = auStack_a0._0_4_;
      uStack_4c = auStack_a0._4_4_;
      uStack_48 = uStack_98;
      uStack_44 = uStack_94;
      iVar3 = rand();
      __amu__7FVectorFf((float)iVar3 / 2.1474836e+09,&uStack_50);
      auVar7 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x70));
      auVar8._4_4_ = uStack_4c;
      auVar8._0_4_ = uStack_50;
      auVar8._8_4_ = uStack_48;
      auVar8._12_4_ = uStack_44;
      auVar8 = _lqc2(auVar8);
      auVar7 = _vadd(auVar7,auVar8);
      auStack_f0 = _sqc2(auVar7);
      __ct__7FVectorFRC7FVector(auStack_b0,auStack_f0);
      iVar3 = param_1 + iVar2 * 0x10;
      *(int *)(iVar3 + 0x1a0) = auStack_b0._0_4_;
      *(int *)(iVar3 + 0x1a4) = auStack_b0._4_4_;
      *(undefined4 *)(iVar3 + 0x1a8) = uStack_a8;
      *(undefined4 *)(iVar3 + 0x1ac) = uStack_a4;
      *(undefined4 *)(param_1 + iVar2 * 4 + 0x3a0) = 0x3f800000;
      *(float *)(param_1 + 0x94) = *(float *)(param_1 + 0x94) - 0.033333335;
    }
  }
  return 0;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00524b90  MakePacket__18SwordAddAttribute1Fv
 * C++: SwordAddAttribute1::MakePacket()
 * size: 0x29d8 bytes
 * --------------------------------------------------------------------------- */
/* WARNING: Removing unreachable block (ram,0x00526ce0) */
/* WARNING: Removing unreachable block (ram,0x00526c20) */
/* WARNING: Removing unreachable block (ram,0x00526da0) */

void MakePacket__18SwordAddAttribute1Fv(int param_1)

{
  bool bVar1;
  undefined4 *puVar2;
  bool bVar3;
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  undefined8 uVar4;
  undefined8 in_v1_udw;
  undefined1 auVar5 [16];
  uint uVar6;
  int iVar7;
  undefined4 uVar8;
  int iVar9;
  float fVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  undefined1 in_vf0 [16];
  undefined1 auVar14 [16];
  undefined1 auVar15 [16];
  undefined1 auVar16 [16];
  undefined1 auStack_14b0 [16];
  undefined1 auStack_14a0 [16];
  undefined1 auStack_1490 [16];
  undefined1 auStack_1480 [16];
  undefined1 auStack_1470 [8];
  float fStack_1468;
  undefined4 uStack_1464;
  undefined4 uStack_1460;
  undefined4 uStack_145c;
  undefined4 uStack_1458;
  undefined4 uStack_1454;
  undefined4 uStack_1450;
  undefined4 uStack_144c;
  undefined4 uStack_1448;
  undefined4 uStack_1444;
  undefined4 uStack_1440;
  undefined4 uStack_143c;
  undefined4 uStack_1438;
  undefined4 uStack_1434;
  undefined4 uStack_1430;
  undefined4 uStack_142c;
  undefined4 uStack_1428;
  undefined4 uStack_1424;
  undefined1 auStack_1420 [16];
  undefined1 auStack_1410 [64];
  undefined1 auStack_13d0 [8];
  float fStack_13c8;
  undefined4 uStack_13c4;
  undefined1 auStack_13c0 [8];
  float fStack_13b8;
  undefined4 uStack_13b4;
  undefined4 uStack_13b0;
  undefined4 uStack_13ac;
  undefined4 uStack_13a8;
  undefined4 uStack_13a4;
  undefined4 uStack_13a0;
  undefined4 uStack_139c;
  undefined4 uStack_1398;
  undefined4 uStack_1394;
  undefined4 uStack_1390;
  undefined4 uStack_138c;
  undefined4 uStack_1388;
  undefined4 uStack_1384;
  undefined4 uStack_1380;
  undefined4 uStack_137c;
  undefined4 uStack_1378;
  undefined4 uStack_1374;
  undefined1 auStack_1370 [64];
  float fStack_1330;
  float fStack_132c;
  float fStack_1328;
  undefined4 uStack_1324;
  float fStack_1320;
  float fStack_131c;
  float fStack_1318;
  undefined4 uStack_1314;
  float fStack_1310;
  float fStack_130c;
  float fStack_1308;
  undefined4 uStack_1304;
  float fStack_1300;
  float fStack_12fc;
  float fStack_12f8;
  undefined4 uStack_12f4;
  float fStack_12f0;
  float fStack_12ec;
  float fStack_12e8;
  undefined4 uStack_12e4;
  undefined1 auStack_12e0 [8];
  float fStack_12d8;
  undefined1 auStack_12d0 [16];
  float fStack_12c0;
  float fStack_12bc;
  undefined4 uStack_12b8;
  undefined4 uStack_12b4;
  float fStack_12b0;
  float fStack_12ac;
  undefined4 uStack_12a8;
  undefined4 uStack_12a4;
  int aiStack_12a0 [576];
  float fStack_9a0;
  float fStack_99c;
  float fStack_998;
  undefined4 uStack_994;
  float fStack_990;
  float fStack_98c;
  float fStack_988;
  undefined4 uStack_984;
  float afStack_980 [5];
  float fStack_96c;
  float fStack_968;
  undefined4 uStack_964;
  float fStack_960;
  float fStack_95c;
  float fStack_958;
  undefined4 uStack_954;
  float fStack_950;
  float fStack_94c;
  float fStack_948;
  undefined4 uStack_944;
  float fStack_940;
  float fStack_93c;
  float fStack_938;
  undefined4 uStack_934;
  float fStack_930;
  float fStack_92c;
  float fStack_928;
  undefined4 uStack_924;
  float fStack_920;
  float fStack_91c;
  float fStack_918;
  undefined4 uStack_914;
  float fStack_910;
  float fStack_90c;
  float fStack_908;
  undefined4 uStack_904;
  float fStack_900;
  float fStack_8fc;
  float fStack_8f8;
  undefined4 uStack_8f4;
  float fStack_8f0;
  float fStack_8ec;
  float fStack_8e8;
  undefined4 uStack_8e4;
  float fStack_8e0;
  float fStack_8dc;
  float fStack_8d8;
  undefined4 uStack_8d4;
  float fStack_8d0;
  float fStack_8cc;
  float fStack_8c8;
  undefined4 uStack_8c4;
  float afStack_c0 [16];
  undefined1 auStack_80 [4];
  float afStack_7c [2];
  int iStack_74;
  undefined1 auStack_70 [16];
  undefined1 auStack_60 [16];
  undefined1 auStack_50 [16];
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
  
  uStack_1380 = 0xbf800000;
  uStack_137c = 0xbf800000;
  uStack_1378 = 0;
  uStack_1374 = 0x3f800000;
  uStack_40 = 0xbf800000;
  uStack_3c = 0xbf800000;
  uStack_38 = 0;
  uStack_34 = 0x3f800000;
  uStack_1390 = 0xbf800000;
  uStack_138c = 0x3f800000;
  uStack_1388 = 0;
  uStack_1384 = 0x3f800000;
  uStack_30 = 0xbf800000;
  uStack_2c = 0x3f800000;
  uStack_28 = 0;
  uStack_24 = 0x3f800000;
  uStack_13a0 = 0x3f800000;
  uStack_139c = 0xbf800000;
  uStack_1398 = 0;
  uStack_1394 = 0x3f800000;
  uStack_20 = 0x3f800000;
  uStack_1c = 0xbf800000;
  uStack_18 = 0;
  uStack_14 = 0x3f800000;
  uStack_13b0 = 0x3f800000;
  uStack_13ac = 0x3f800000;
  uStack_13a8 = 0;
  uStack_13a4 = 0x3f800000;
  uStack_10 = 0x3f800000;
  uStack_c = 0x3f800000;
  uStack_8 = 0;
  uStack_4 = 0x3f800000;
  __ct__6MatrixFRC6Matrix(auStack_80,iGpffff8598 + 0x240);
  auStack_50._0_12_ = ZEXT812(0);
  auStack_50._12_4_ = 0x3f800000;
  RotTransVector(afStack_c0,&uStack_40,auStack_80,4);
  auVar14 = _lqc2(*(undefined1 (*) [16])(*(int *)(iGpffff86b4 + 0x4324) + 0x30));
  auVar15 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x70));
  auVar14 = _vsub(auVar14,auVar15);
  auStack_1490 = _sqc2(auVar14);
  __ct__7FVectorFRC7FVector(auStack_13c0,auStack_1490);
  fStack_990 = auStack_13c0._0_4_;
  fStack_98c = auStack_13c0._4_4_;
  fStack_988 = fStack_13b8;
  uStack_984 = uStack_13b4;
  auVar14 = _lqc2(*(undefined1 (*) [16])(*(int *)(iGpffff86b4 + 0x4324) + 0x30));
  auVar15 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x80));
  auVar14 = _vsub(auVar14,auVar15);
  auStack_14a0 = _sqc2(auVar14);
  __ct__7FVectorFRC7FVector(auStack_13d0,auStack_14a0);
  fStack_9a0 = auStack_13d0._0_4_;
  fStack_99c = auStack_13d0._4_4_;
  fStack_998 = fStack_13c8;
  uStack_994 = uStack_13c4;
  Normalize__7FVectorFv(&fStack_990);
  Normalize__7FVectorFv(&fStack_9a0);
  if ((((*(byte *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0xb1) & 1) == 0) ||
      (*(short *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x120) != 0)) ||
     (*(short *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0xba) != 5)) {
    if ((((*(byte *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0xb1) & 1) == 0) ||
        (*(short *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x120) != 7)) ||
       (*(short *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0xba) != 0x10)) {
      if (((*(byte *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0xb1) & 1) != 0) ||
         (*(short *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x120) != 7)) {
        __amu__7FVectorFf(0x3f000000,&fStack_990);
        __amu__7FVectorFf(0x3f000000,&fStack_9a0);
      }
    }
    else {
      __amu__7FVectorFf(0x40000000,&fStack_990);
    }
  }
  else {
    __amu__7FVectorFf(0x3fa00000,&fStack_990);
    __amu__7FVectorFf(0x3fa00000,&fStack_9a0);
  }
  afStack_980[0] = *(float *)(param_1 + 0x70) + fStack_990;
  afStack_980[1] = *(float *)(param_1 + 0x74) + fStack_98c;
  afStack_980[2] = *(float *)(param_1 + 0x78) + fStack_988;
  afStack_980[3] = 1.0;
  afStack_980[4] = *(float *)(param_1 + 0x80) + fStack_9a0;
  fStack_96c = *(float *)(param_1 + 0x84) + fStack_99c;
  fStack_968 = *(float *)(param_1 + 0x88) + fStack_998;
  uStack_964 = 0x3f800000;
  GetViewScreenMatrix__9GsxCameraFv(auStack_1410,iGpffff8598);
  for (iVar7 = 0; iVar7 < 4; iVar7 = iVar7 + 1) {
    aiStack_12a0[iVar7 * 4 + 0x230] = *(int *)(auStack_80 + iVar7 * 0x10);
    aiStack_12a0[iVar7 * 4 + 0x231] = *(int *)(auStack_80 + iVar7 * 0x10 + 4);
    aiStack_12a0[iVar7 * 4 + 0x232] = *(int *)(auStack_80 + iVar7 * 0x10 + 8);
    aiStack_12a0[iVar7 * 4 + 0x233] = *(int *)(auStack_80 + iVar7 * 0x10 + 0xc);
  }
  sceVu0RotTransPersN(aiStack_12a0,aiStack_12a0 + 0x230,afStack_980,2,0);
  fStack_12ac = (float)aiStack_12a0[1] / 16.0 - 1824.0;
  fStack_12b0 = (float)aiStack_12a0[0] / 16.0 - 1792.0;
  uStack_12a8 = 0;
  uStack_12a4 = 0x3f800000;
  fStack_12bc = (float)aiStack_12a0[5] / 16.0 - 1824.0;
  fStack_12c0 = (float)aiStack_12a0[4] / 16.0 - 1792.0;
  uStack_12b8 = 0;
  uStack_12b4 = 0x3f800000;
  auVar14._4_4_ = fStack_12bc;
  auVar14._0_4_ = fStack_12c0;
  auVar14._8_4_ = 0;
  auVar14._12_4_ = 0x3f800000;
  auVar14 = _lqc2(auVar14);
  auVar15._4_4_ = fStack_12ac;
  auVar15._0_4_ = fStack_12b0;
  auVar15._8_4_ = 0;
  auVar15._12_4_ = 0x3f800000;
  auVar15 = _lqc2(auVar15);
  auVar14 = _vsub(auVar14,auVar15);
  auStack_1480 = _sqc2(auVar14);
  __ct__7FVectorFRC7FVector(auStack_12d0,auStack_1480);
  uVar4 = __ct__7FVectorFRC7FVector(auStack_1420,auStack_12d0);
  Get3DAngle2__F7FVector(auStack_12e0,uVar4);
  uStack_1430 = 0;
  uStack_142c = 0x3f800000;
  uStack_1428 = 0;
  uStack_1424 = 0x3f800000;
  fStack_1330 = 0.0;
  fStack_132c = 1.0;
  fStack_1328 = 0.0;
  uStack_1324 = 0x3f800000;
  uStack_1440 = 0;
  uStack_143c = 0xbf800000;
  uStack_1438 = 0;
  uStack_1434 = 0x3f800000;
  fStack_1320 = 0.0;
  fStack_131c = -1.0;
  fStack_1318 = 0.0;
  uStack_1314 = 0x3f800000;
  uStack_1450 = 0;
  uStack_144c = 0x3f800000;
  uStack_1448 = 0;
  uStack_1444 = 0x3f800000;
  fStack_1310 = 0.0;
  fStack_130c = 1.0;
  fStack_1308 = 0.0;
  uStack_1304 = 0x3f800000;
  uStack_1460 = 0;
  uStack_145c = 0xbf800000;
  uStack_1458 = 0;
  uStack_1454 = 0x3f800000;
  fStack_1300 = 0.0;
  fStack_12fc = -1.0;
  fStack_12f8 = 0.0;
  uStack_12f4 = 0x3f800000;
  auVar14 = _vmr32(in_vf0);
  auVar15 = _vmr32(auVar14);
  auVar16 = _vmr32(auVar15);
  auStack_50 = _sqc2(in_vf0);
  auStack_60 = _sqc2(auVar14);
  auStack_70 = _sqc2(auVar15);
  _auStack_80 = _sqc2(auVar16);
  uVar8 = GetRad(-fStack_12d8);
  sceVu0RotMatrixZ(uVar8,auStack_80,auStack_80);
  RotTransVector(auStack_1370,&fStack_1330,auStack_80,4);
  _auStack_80 = *(undefined1 (*) [16])(iGpffff8598 + 0x240);
  auStack_70 = *(undefined1 (*) [16])(iGpffff8598 + 0x250);
  auStack_60 = *(undefined1 (*) [16])(iGpffff8598 + 0x260);
  auStack_50 = *(undefined1 (*) [16])(iGpffff8598 + 0x270);
  for (iVar7 = 0; iVar7 < 3; iVar7 = iVar7 + 1) {
    *(float *)(auStack_80 + iVar7 * 0x10) = *(float *)(auStack_80 + iVar7 * 0x10) * -1.0;
    *(float *)(auStack_80 + iVar7 * 0x10 + 4) = *(float *)(auStack_80 + iVar7 * 0x10 + 4) * -1.0;
    *(float *)(auStack_80 + iVar7 * 0x10 + 8) = *(float *)(auStack_80 + iVar7 * 0x10 + 8) * -1.0;
  }
  auStack_50._0_12_ = ZEXT812(0);
  auStack_50._12_4_ = 0x3f800000;
  RotTransVector(&fStack_1330,auStack_1370,auStack_80,4);
  Normalize__7FVectorFv(&fStack_1330);
  Normalize__7FVectorFv(&fStack_1320);
  Normalize__7FVectorFv(&fStack_1310);
  Normalize__7FVectorFv(&fStack_1300);
  auVar14 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x80));
  auVar15 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x70));
  auVar14 = _vsub(auVar14,auVar15);
  auStack_14b0 = _sqc2(auVar14);
  __ct__7FVectorFRC7FVector(auStack_1470,auStack_14b0);
  fStack_12f0 = auStack_1470._0_4_;
  fStack_12ec = auStack_1470._4_4_;
  fStack_12e8 = fStack_1468;
  uStack_12e4 = uStack_1464;
  Normalize__7FVectorFv(&fStack_12f0);
  if ((((*(byte *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0xb1) & 1) == 0) ||
      (*(short *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x120) != 0)) ||
     (*(short *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0xba) != 5)) {
    if ((((*(byte *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0xb1) & 1) == 0) ||
        (*(short *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x120) != 7)) ||
       (*(short *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0xba) != 0x10)) {
      if (((*(byte *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0xb1) & 1) == 0) &&
         (*(short *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x120) == 7)) {
        __amu__7FVectorFf(0x3fa00000,&fStack_1330);
        __amu__7FVectorFf(0x3fa00000,&fStack_1320);
        __amu__7FVectorFf(0x3fa00000,&fStack_1310);
        __amu__7FVectorFf(0x3fa00000,&fStack_1300);
      }
    }
    else {
      __amu__7FVectorFf(0x40400000,&fStack_1330);
      __amu__7FVectorFf(0x40400000,&fStack_1320);
      __amu__7FVectorFf(0x3fc00000,&fStack_1310);
      __amu__7FVectorFf(0x3fc00000,&fStack_1300);
    }
  }
  else {
    __amu__7FVectorFf(0x3fc00000,&fStack_1330);
    __amu__7FVectorFf(0x3fc00000,&fStack_1320);
    __amu__7FVectorFf(0x3fc00000,&fStack_1310);
    __amu__7FVectorFf(0x3fc00000,&fStack_1300);
  }
  afStack_980[0] =
       fStack_1330 * *(float *)(param_1 + 0x90) * 3.2 +
       ((*(float *)(param_1 + 0x70) + fStack_990) - fStack_12f0 * *(float *)(param_1 + 0x90));
  afStack_980[1] =
       fStack_132c * *(float *)(param_1 + 0x90) * 3.2 +
       ((*(float *)(param_1 + 0x74) + fStack_98c) - fStack_12ec * *(float *)(param_1 + 0x90));
  afStack_980[2] =
       fStack_1328 * *(float *)(param_1 + 0x90) * 3.2 +
       ((*(float *)(param_1 + 0x78) + fStack_988) - fStack_12e8 * *(float *)(param_1 + 0x90));
  afStack_980[3] = 1.0;
  afStack_980[4] =
       (*(float *)(param_1 + 0x70) + fStack_990) - fStack_12f0 * *(float *)(param_1 + 0x90);
  fStack_96c = (*(float *)(param_1 + 0x74) + fStack_98c) - fStack_12ec * *(float *)(param_1 + 0x90);
  fStack_968 = (*(float *)(param_1 + 0x78) + fStack_988) - fStack_12e8 * *(float *)(param_1 + 0x90);
  uStack_964 = 0x3f800000;
  fStack_960 = fStack_1320 * *(float *)(param_1 + 0x90) * 3.2 +
               ((*(float *)(param_1 + 0x70) + fStack_990) - fStack_12f0 * *(float *)(param_1 + 0x90)
               );
  fStack_95c = fStack_131c * *(float *)(param_1 + 0x90) * 3.2 +
               ((*(float *)(param_1 + 0x74) + fStack_98c) - fStack_12ec * *(float *)(param_1 + 0x90)
               );
  fStack_958 = fStack_1318 * *(float *)(param_1 + 0x90) * 3.2 +
               ((*(float *)(param_1 + 0x78) + fStack_988) - fStack_12e8 * *(float *)(param_1 + 0x90)
               );
  uStack_954 = 0x3f800000;
  fStack_950 = *(float *)(param_1 + 0x70) + fStack_990 +
               fStack_1330 * *(float *)(param_1 + 0x90) * 3.2;
  fStack_94c = *(float *)(param_1 + 0x74) + fStack_98c +
               fStack_132c * *(float *)(param_1 + 0x90) * 3.2;
  fStack_948 = *(float *)(param_1 + 0x78) + fStack_988 +
               fStack_1328 * *(float *)(param_1 + 0x90) * 3.2;
  uStack_944 = 0x3f800000;
  fStack_940 = *(float *)(param_1 + 0x70) + fStack_990;
  fStack_93c = *(float *)(param_1 + 0x74) + fStack_98c;
  fStack_938 = *(float *)(param_1 + 0x78) + fStack_988;
  uStack_934 = 0x3f800000;
  fStack_930 = *(float *)(param_1 + 0x70) + fStack_990 +
               fStack_1320 * *(float *)(param_1 + 0x90) * 3.2;
  fStack_92c = *(float *)(param_1 + 0x74) + fStack_98c +
               fStack_131c * *(float *)(param_1 + 0x90) * 3.2;
  fStack_928 = *(float *)(param_1 + 0x78) + fStack_988 +
               fStack_1318 * *(float *)(param_1 + 0x90) * 3.2;
  uStack_924 = 0x3f800000;
  fStack_920 = *(float *)(param_1 + 0x80) + fStack_9a0 +
               fStack_1310 * *(float *)(param_1 + 0x90) * 3.2;
  fStack_91c = *(float *)(param_1 + 0x84) + fStack_99c +
               fStack_130c * *(float *)(param_1 + 0x90) * 3.2;
  fStack_918 = *(float *)(param_1 + 0x88) + fStack_998 +
               fStack_1308 * *(float *)(param_1 + 0x90) * 3.2;
  uStack_914 = 0x3f800000;
  fStack_910 = *(float *)(param_1 + 0x80) + fStack_9a0;
  fStack_90c = *(float *)(param_1 + 0x84) + fStack_99c;
  fStack_908 = *(float *)(param_1 + 0x88) + fStack_998;
  uStack_904 = 0x3f800000;
  fStack_900 = *(float *)(param_1 + 0x80) + fStack_9a0 +
               fStack_1300 * *(float *)(param_1 + 0x90) * 3.2;
  fStack_8fc = *(float *)(param_1 + 0x84) + fStack_99c +
               fStack_12fc * *(float *)(param_1 + 0x90) * 3.2;
  fStack_8f8 = *(float *)(param_1 + 0x88) + fStack_998 +
               fStack_12f8 * *(float *)(param_1 + 0x90) * 3.2;
  uStack_8f4 = 0x3f800000;
  fStack_8f0 = fStack_1310 * *(float *)(param_1 + 0x90) * 3.2 +
               *(float *)(param_1 + 0x80) + fStack_9a0 + fStack_12f0 * *(float *)(param_1 + 0x90);
  fStack_8ec = fStack_130c * *(float *)(param_1 + 0x90) * 3.2 +
               *(float *)(param_1 + 0x84) + fStack_99c + fStack_12ec * *(float *)(param_1 + 0x90);
  fStack_8e8 = fStack_1308 * *(float *)(param_1 + 0x90) * 3.2 +
               *(float *)(param_1 + 0x88) + fStack_998 + fStack_12e8 * *(float *)(param_1 + 0x90);
  uStack_8e4 = 0x3f800000;
  fStack_8e0 = *(float *)(param_1 + 0x80) + fStack_9a0 + fStack_12f0 * *(float *)(param_1 + 0x90);
  fStack_8dc = *(float *)(param_1 + 0x84) + fStack_99c + fStack_12ec * *(float *)(param_1 + 0x90);
  fStack_8d8 = *(float *)(param_1 + 0x88) + fStack_998 + fStack_12e8 * *(float *)(param_1 + 0x90);
  uStack_8d4 = 0x3f800000;
  fStack_8d0 = fStack_1300 * *(float *)(param_1 + 0x90) * 3.2 +
               *(float *)(param_1 + 0x80) + fStack_9a0 + fStack_12f0 * *(float *)(param_1 + 0x90);
  fStack_8cc = fStack_12fc * *(float *)(param_1 + 0x90) * 3.2 +
               *(float *)(param_1 + 0x84) + fStack_99c + fStack_12ec * *(float *)(param_1 + 0x90);
  fStack_8c8 = fStack_12f8 * *(float *)(param_1 + 0x90) * 3.2 +
               *(float *)(param_1 + 0x88) + fStack_998 + fStack_12e8 * *(float *)(param_1 + 0x90);
  uStack_8c4 = 0x3f800000;
  for (iVar7 = 0; iVar7 < 0x20; iVar7 = iVar7 + 1) {
    for (iVar9 = 0; iVar9 < 4; iVar9 = iVar9 + 1) {
      afStack_980[(iVar9 + iVar7 * 4 + 0xc) * 4] =
           *(float *)(param_1 + iVar7 * 0x10 + 0x1a0) + afStack_c0[iVar9 * 4];
      afStack_980[(iVar9 + iVar7 * 4 + 0xc) * 4 + 1] =
           *(float *)(param_1 + iVar7 * 0x10 + 0x1a4) + afStack_c0[iVar9 * 4 + 1];
      afStack_980[(iVar9 + iVar7 * 4 + 0xc) * 4 + 2] =
           *(float *)(param_1 + iVar7 * 0x10 + 0x1a8) + afStack_c0[iVar9 * 4 + 2];
      afStack_980[(iVar9 + iVar7 * 4 + 0xc) * 4 + 3] = 1.0;
    }
  }
  sceVu0RotTransPersN(aiStack_12a0,aiStack_12a0 + 0x230,afStack_980,0x8c,0);
  bVar3 = false;
  iVar7 = 0;
  for (iVar9 = 0; iVar9 < 0x8c; iVar9 = iVar9 + 1) {
    if (iVar9 < 0xc) {
      if (((aiStack_12a0[iVar9 * 4] < 0) || (0x10000 < aiStack_12a0[iVar9 * 4])) ||
         ((aiStack_12a0[iVar9 * 4 + 1] < 0 ||
          ((0x10000 < aiStack_12a0[iVar9 * 4 + 1] || (aiStack_12a0[iVar9 * 4 + 2] < 0)))))) {
        bVar3 = true;
      }
      aiStack_12a0[iVar9 * 4 + 2] = (int)((float)aiStack_12a0[iVar9 * 4 + 2] / 16.0);
      if (iVar9 < 0xc) {
        iVar7 = iVar7 + aiStack_12a0[iVar9 * 4 + 2];
      }
    }
    else {
      uVar6 = iVar9 - 0xcU & 3;
      if (((int)(iVar9 - 0xcU) < 0) && (uVar6 != 0)) {
        uVar6 = uVar6 - 4;
      }
      if (uVar6 == 0) {
        iVar11 = iVar9 + -0xc;
        if (iVar11 < 0) {
          iVar11 = iVar9 + -9;
        }
        *(undefined2 *)(param_1 + (iVar11 >> 2) * 2 + 0xdc) = 0;
      }
      if ((((aiStack_12a0[iVar9 * 4] < 0) || (0x10000 < aiStack_12a0[iVar9 * 4])) ||
          (aiStack_12a0[iVar9 * 4 + 1] < 0)) ||
         ((0x10000 < aiStack_12a0[iVar9 * 4 + 1] || (aiStack_12a0[iVar9 * 4 + 2] < 0)))) {
        iVar11 = iVar9 + -0xc;
        if (iVar11 < 0) {
          iVar11 = iVar9 + -9;
        }
        *(undefined2 *)(param_1 + (iVar11 >> 2) * 2 + 0xdc) = 1;
      }
      aiStack_12a0[iVar9 * 4 + 2] = (int)((float)aiStack_12a0[iVar9 * 4 + 2] / 16.0);
    }
  }
  *(int *)(param_1 + 0x50) = iVar7 / 0xc;
  bVar1 = (*(byte *)(param_1 + 0x40) & 1) == 0;
  uVar6 = (uint)bVar1;
  if (*(int *)(param_1 + uVar6 * 4 + 0x18) == 0) {
    uVar8 = __nwa__FUi(0xc50);
    *(undefined4 *)(param_1 + uVar6 * 4 + 0x18) = uVar8;
    iVar7 = *(int *)(param_1 + uVar6 * 4 + 0x18);
    *(undefined4 *)(iVar7 + 0x10) = 0x1000001d;
    *(undefined4 *)(iVar7 + 0x14) = 0;
    *(undefined4 *)(iVar7 + 0x18) = 0;
    *(undefined4 *)(iVar7 + 0x1c) = 0x5000001d;
    *(undefined8 *)(iVar7 + 0x20) = 0x6000000000000001;
    *(undefined8 *)(iVar7 + 0x28) = 0x6ee8ee;
    *(undefined8 *)(iVar7 + 0x30) = 1;
    *(undefined8 *)(iVar7 + 0x38) = 0x3f;
    *(undefined8 *)(iVar7 + 0x40) = 0x60;
    *(undefined8 *)(iVar7 + 0x48) = 0x14;
    *(undefined8 *)(iVar7 + 0x50) = 5;
    *(undefined8 *)(iVar7 + 0x58) = 0;
    *(undefined8 *)(iVar7 + 0x60) = 0x53001;
    *(undefined8 *)(iVar7 + 0x68) = 0x47;
    *(undefined8 *)(iVar7 + 0x70) = 0x48;
    *(undefined8 *)(iVar7 + 0x78) = 0x42;
    uVar4 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x42f4),1);
    *(undefined8 *)(iVar7 + 0x80) = uVar4;
    *(undefined8 *)(iVar7 + 0x88) = 0;
    *(undefined8 *)(iVar7 + 0x90) = 0x6400000000000001;
    *(undefined8 *)(iVar7 + 0x98) = 0xc3c310;
    *(undefined8 *)(iVar7 + 0xa0) = 0x154;
    *(undefined8 *)(iVar7 + 0xb0) = 0;
    *(long *)(iVar7 + 0xc0) =
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f4) + 2) << 3);
    *(undefined8 *)(iVar7 + 0xd0) = 0x2400000000000006;
    *(undefined8 *)(iVar7 + 0xd8) = 0x43;
    *(undefined8 *)(iVar7 + 0xe0) = 0x1400000;
    *(ulong *)(iVar7 + 0xf0) =
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f4) + 2) << 3) | 0x1400000;
    *(long *)(iVar7 + 0x100) =
         (long)(int)((*(ushort *)(*(int *)(iGpffff86b4 + 0x42f4) + 4) - 0x14) * 0x10) << 0x10;
    *(long *)(iVar7 + 0x110) =
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f4) + 2) << 3) |
         (long)(int)((*(ushort *)(*(int *)(iGpffff86b4 + 0x42f4) + 4) - 0x14) * 0x10) << 0x10;
    *(long *)(iVar7 + 0x120) =
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f4) + 4) << 4) << 0x10;
    *(long *)(iVar7 + 0x130) =
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f4) + 2) << 3) |
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f4) + 4) << 4) << 0x10;
    *(undefined8 *)(iVar7 + 0x140) = 0x6400000000000001;
    *(undefined8 *)(iVar7 + 0x148) = 0xc3c310;
    *(undefined8 *)(iVar7 + 0x150) = 0x154;
    *(long *)(iVar7 + 0x160) =
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f4) + 2) << 3);
    *(long *)(iVar7 + 0x170) =
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f4) + 2) << 4);
    *(undefined8 *)(iVar7 + 0x180) = 0x2400000000008006;
    *(undefined8 *)(iVar7 + 0x188) = 0x43;
    *(ulong *)(iVar7 + 400) =
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f4) + 2) << 3) | 0x1400000;
    *(ulong *)(iVar7 + 0x1a0) =
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f4) + 2) << 4) | 0x1400000;
    *(long *)(iVar7 + 0x1b0) =
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f4) + 2) << 3) |
         (long)(int)((*(ushort *)(*(int *)(iGpffff86b4 + 0x42f4) + 4) - 0x14) * 0x10) << 0x10;
    *(long *)(iVar7 + 0x1c0) =
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f4) + 2) << 4) |
         (long)(int)((*(ushort *)(*(int *)(iGpffff86b4 + 0x42f4) + 4) - 0x14) * 0x10) << 0x10;
    *(long *)(iVar7 + 0x1d0) =
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f4) + 2) << 3) |
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f4) + 4) << 4) << 0x10;
    *(long *)(iVar7 + 0x1e0) =
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f4) + 2) << 4) |
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f4) + 4) << 4) << 0x10;
    *(undefined4 *)(iVar7 + 0x1f0) = 0x50000000;
    *(undefined4 *)(iVar7 + 500) =
         *(undefined4 *)
          (*(int *)(iGpffff86b4 + 0x42f0) +
           (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f0) + 10) * 4 + 0xc);
    *(undefined4 *)(iVar7 + 0x1f8) = 0;
    *(undefined4 *)(iVar7 + 0x1fc) = 0;
    *(undefined4 *)(iVar7 + 0x200) = 0x600000a4;
    *(undefined4 *)(iVar7 + 0x204) = 0;
    *(undefined4 *)(iVar7 + 0x208) = 0;
    *(undefined4 *)(iVar7 + 0x20c) = 0x500000a4;
    *(undefined8 *)(iVar7 + 0x210) = 0x2000000000000001;
    *(undefined8 *)(iVar7 + 0x218) = 0x6e;
    *(undefined8 *)(iVar7 + 0x220) = 1;
    *(undefined8 *)(iVar7 + 0x228) = 0x3f;
    uVar4 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x42f0),1);
    *(undefined8 *)(iVar7 + 0x230) = uVar4;
    *(undefined8 *)(iVar7 + 0x238) = 0;
    auVar5._8_8_ = in_v1_udw;
    auVar5._0_8_ = 0xa400000000008020;
    auVar16._4_4_ = in_zero_hi;
    auVar16._0_4_ = in_zero_lo;
    auVar16._8_4_ = in_zero_udw;
    auVar16._12_4_ = in_register_0000000c;
    auVar14 = _pcpyld(auVar16,auVar5);
    *(long *)(iVar7 + 0x240) = auVar14._0_8_;
    *(undefined8 *)(iVar7 + 0x248) = 0x4343c3c310;
    for (iVar9 = 0; iVar9 < 0x20; iVar9 = iVar9 + 1) {
      *(undefined8 *)(iVar7 + (iVar9 * 5 + 0x25) * 0x10) = 0x154;
      *(long *)(iVar7 + (iVar9 * 5 + 0x26) * 0x10) =
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f0) + 2) << 2) |
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f0) + 4) << 2) << 0x10;
      *(long *)(iVar7 + (iVar9 * 5 + 0x27) * 0x10) =
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f0) + 2) << 2) |
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f0) + 4) * 0xc) << 0x10;
      *(long *)(iVar7 + (iVar9 * 5 + 0x28) * 0x10) =
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f0) + 4) << 2) << 0x10 |
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f0) + 2) * 0xc);
      *(long *)(iVar7 + (iVar9 * 5 + 0x29) * 0x10) =
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f0) + 2) * 0xc) |
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f0) + 4) * 0xc) << 0x10;
    }
  }
  puVar2 = *(undefined4 **)(param_1 + uVar6 * 4 + 0x18);
  if (bVar3) {
    *puVar2 = 0x60000000;
    puVar2[1] = 0;
    puVar2[2] = 0;
    puVar2[3] = 0;
    *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfe | bVar1;
  }
  else {
    *puVar2 = 0x50000000;
    puVar2[1] = *(undefined4 *)
                 (*(int *)(iGpffff86b4 + 0x42f4) +
                  (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f4) + 10) * 4 + 0xc);
    puVar2[2] = 0;
    puVar2[3] = 0;
    iVar9 = (int)(*(float *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x144) +
                            0x4e4) *
                  *(float *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x144) +
                            0x4ec) * 128.0);
    fVar10 = (float)sinf(*(undefined4 *)(param_1 + 0x98));
    fVar10 = (fVar10 + 1.0) / 2.0;
    iVar11 = (int)((float)*(byte *)(*(int *)(param_1 + 0x60) * 0xc + 0x652b64) +
                  fVar10 * (float)(int)((uint)*(byte *)(*(int *)(param_1 + 0x60) * 0xc + 0x652b68) -
                                       (uint)*(byte *)(*(int *)(param_1 + 0x60) * 0xc + 0x652b64)));
    iVar12 = (int)((float)*(byte *)(*(int *)(param_1 + 0x60) * 0xc + 0x652b65) +
                  fVar10 * (float)(int)((uint)*(byte *)(*(int *)(param_1 + 0x60) * 0xc + 0x652b69) -
                                       (uint)*(byte *)(*(int *)(param_1 + 0x60) * 0xc + 0x652b65)));
    iVar13 = (int)((float)*(byte *)(*(int *)(param_1 + 0x60) * 0xc + 0x652b66) +
                  fVar10 * (float)(int)((uint)*(byte *)(*(int *)(param_1 + 0x60) * 0xc + 0x652b6a) -
                                       (uint)*(byte *)(*(int *)(param_1 + 0x60) * 0xc + 0x652b66)));
    *(ulong *)(puVar2 + 0x2a) =
         (long)iVar9 << 0x18 | (long)iVar13 << 0x10 | (long)iVar11 | (long)iVar12 << 8 | 0x100000000
    ;
    *(long *)(puVar2 + 0x2e) =
         (long)aiStack_12a0[2] << 0x20 | (long)aiStack_12a0[0] | (long)aiStack_12a0[1] << 0x10;
    *(long *)(puVar2 + 0x32) =
         (long)aiStack_12a0[6] << 0x20 | (long)aiStack_12a0[4] | (long)aiStack_12a0[5] << 0x10;
    *(long *)(puVar2 + 0x3a) =
         (long)aiStack_12a0[0xe] << 0x20 | (long)aiStack_12a0[0xc] | (long)aiStack_12a0[0xd] << 0x10
    ;
    *(long *)(puVar2 + 0x3e) =
         (long)aiStack_12a0[0x12] << 0x20 |
         (long)aiStack_12a0[0x10] | (long)aiStack_12a0[0x11] << 0x10;
    *(long *)(puVar2 + 0x42) =
         (long)aiStack_12a0[0x1a] << 0x20 |
         (long)aiStack_12a0[0x18] | (long)aiStack_12a0[0x19] << 0x10;
    *(long *)(puVar2 + 0x46) =
         (long)aiStack_12a0[0x1e] << 0x20 |
         (long)aiStack_12a0[0x1c] | (long)aiStack_12a0[0x1d] << 0x10;
    *(long *)(puVar2 + 0x4a) =
         (long)aiStack_12a0[0x26] << 0x20 |
         (long)aiStack_12a0[0x24] | (long)aiStack_12a0[0x25] << 0x10;
    *(long *)(puVar2 + 0x4e) =
         (long)aiStack_12a0[0x2a] << 0x20 |
         (long)aiStack_12a0[0x28] | (long)aiStack_12a0[0x29] << 0x10;
    *(ulong *)(puVar2 + 0x56) =
         (long)iVar9 << 0x18 | (long)iVar13 << 0x10 | (long)iVar11 | (long)iVar12 << 8 | 0x100000000
    ;
    *(long *)(puVar2 + 0x5a) =
         (long)aiStack_12a0[6] << 0x20 | (long)aiStack_12a0[4] | (long)aiStack_12a0[5] << 0x10;
    *(long *)(puVar2 + 0x5e) =
         (long)aiStack_12a0[10] << 0x20 | (long)aiStack_12a0[8] | (long)aiStack_12a0[9] << 0x10;
    *(long *)(puVar2 + 0x66) =
         (long)aiStack_12a0[0x12] << 0x20 |
         (long)aiStack_12a0[0x10] | (long)aiStack_12a0[0x11] << 0x10;
    *(long *)(puVar2 + 0x6a) =
         (long)aiStack_12a0[0x16] << 0x20 |
         (long)aiStack_12a0[0x14] | (long)aiStack_12a0[0x15] << 0x10;
    *(long *)(puVar2 + 0x6e) =
         (long)aiStack_12a0[0x1e] << 0x20 |
         (long)aiStack_12a0[0x1c] | (long)aiStack_12a0[0x1d] << 0x10;
    *(long *)(puVar2 + 0x72) =
         (long)aiStack_12a0[0x22] << 0x20 |
         (long)aiStack_12a0[0x20] | (long)aiStack_12a0[0x21] << 0x10;
    *(long *)(puVar2 + 0x76) =
         (long)aiStack_12a0[0x2a] << 0x20 |
         (long)aiStack_12a0[0x28] | (long)aiStack_12a0[0x29] << 0x10;
    *(long *)(puVar2 + 0x7a) =
         (long)aiStack_12a0[0x2e] << 0x20 |
         (long)aiStack_12a0[0x2c] | (long)aiStack_12a0[0x2d] << 0x10;
    for (iVar7 = 0; iVar7 < 0x20; iVar7 = iVar7 + 1) {
      if ((*(short *)(param_1 + iVar7 * 2 + 0x9c) == 0) ||
         (*(short *)(param_1 + iVar7 * 2 + 0xdc) != 0)) {
        *(undefined8 *)(puVar2 + (iVar7 * 5 + 0x26) * 4 + 2) = 0x71006f00;
        *(undefined8 *)(puVar2 + (iVar7 * 5 + 0x27) * 4 + 2) = 0x71006f00;
        *(undefined8 *)(puVar2 + (iVar7 * 5 + 0x28) * 4 + 2) = 0x71006f00;
        *(undefined8 *)(puVar2 + (iVar7 * 5 + 0x29) * 4 + 2) = 0x71006f00;
      }
      else {
        *(ulong *)(puVar2 + (iVar7 * 5 + 0x25) * 4 + 2) =
             (long)(int)(((float)iVar9 * *(float *)(param_1 + iVar7 * 4 + 0x3a0)) / 128.0) << 0x18 |
             (long)iVar13 << 0x10 | (long)iVar11 | (long)iVar12 << 8 | 0x100000000;
        *(long *)(puVar2 + (iVar7 * 5 + 0x26) * 4 + 2) =
             (long)aiStack_12a0[(iVar7 * 4 + 0xc) * 4 + 2] << 0x20 |
             (long)aiStack_12a0[(iVar7 * 4 + 0xc) * 4] |
             (long)aiStack_12a0[(iVar7 * 4 + 0xc) * 4 + 1] << 0x10;
        *(long *)(puVar2 + (iVar7 * 5 + 0x27) * 4 + 2) =
             (long)aiStack_12a0[(iVar7 * 4 + 0xd) * 4 + 2] << 0x20 |
             (long)aiStack_12a0[(iVar7 * 4 + 0xd) * 4] |
             (long)aiStack_12a0[(iVar7 * 4 + 0xd) * 4 + 1] << 0x10;
        *(long *)(puVar2 + (iVar7 * 5 + 0x28) * 4 + 2) =
             (long)aiStack_12a0[(iVar7 * 4 + 0xe) * 4 + 2] << 0x20 |
             (long)aiStack_12a0[(iVar7 * 4 + 0xe) * 4] |
             (long)aiStack_12a0[(iVar7 * 4 + 0xe) * 4 + 1] << 0x10;
        *(long *)(puVar2 + (iVar7 * 5 + 0x29) * 4 + 2) =
             (long)aiStack_12a0[(iVar7 * 4 + 0xf) * 4 + 2] << 0x20 |
             (long)aiStack_12a0[(iVar7 * 4 + 0xf) * 4] |
             (long)aiStack_12a0[(iVar7 * 4 + 0xf) * 4 + 1] << 0x10;
      }
    }
    *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfe | bVar1;
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00527570  getPacket__18SwordAddAttribute1Fv
 * C++: SwordAddAttribute1::getPacket()
 * size: 0x90 bytes
 * --------------------------------------------------------------------------- */
undefined4 getPacket__18SwordAddAttribute1Fv(int param_1)

{
  undefined4 uVar1;
  
  if ((*(byte *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x144) + 0x4b2) & 1) == 0
     ) {
    (**(code **)(*(int *)(param_1 + 0x14) + 0x38))();
    uVar1 = *(undefined4 *)(param_1 + (*(byte *)(param_1 + 0x40) & 1) * 4 + 0x18);
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054ae70  EndSet__18SwordAddAttribute1Fv
 * C++: SwordAddAttribute1::EndSet()
 * size: 0x10 bytes
 * --------------------------------------------------------------------------- */
void EndSet__18SwordAddAttribute1Fv(void)

{
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b7a0  @24@getPacket__18SwordAddAttribute1Fv
 * C++: @24@getPacket__18SwordAddAttribute1Fv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
undefined4 _24_getPacket__18SwordAddAttribute1Fv(int param_1)

{
  undefined4 uVar1;
  
  if ((*(byte *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x30) * 0x4f0 + 0x144) + 0x4b2) & 1) == 0
     ) {
    (**(code **)(*(int *)(param_1 + -4) + 0x38))();
    uVar1 = *(undefined4 *)(param_1 + (*(byte *)(param_1 + 0x28) & 1) * 4);
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b7b0  @24@__dt__18SwordAddAttribute1Fv
 * C++: @24@__dt__18SwordAddAttribute1Fv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int * _24___dt__18SwordAddAttribute1Fv(int *param_1,short param_2)

{
  int *piVar1;
  
  piVar1 = param_1 + -6;
  if (piVar1 != (int *)0x0) {
    param_1[-1] = 0x409de0;
    param_1[4] = 0x409df0;
    param_1[7] = 0x409e00;
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
 * JP: 0x0054b7c0  @44@__dt__18SwordAddAttribute1Fv
 * C++: @44@__dt__18SwordAddAttribute1Fv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int _44___dt__18SwordAddAttribute1Fv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x2c;
  if (iVar1 != 0) {
    *(undefined4 *)(param_1 + -0x18) = 0x409de0;
    *(undefined4 *)(param_1 + -4) = 0x409df0;
    *(undefined4 *)(param_1 + 8) = 0x409e00;
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

