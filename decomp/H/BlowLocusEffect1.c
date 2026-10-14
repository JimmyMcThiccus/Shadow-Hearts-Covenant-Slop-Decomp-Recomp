/* decomp/H/BlowLocusEffect1.c — cleaned Ghidra output (SH2JP_BATTLE.BIN, JP Furokuban, base 0x00430a00).
 * 8 function(s). Types: see types.h. Names/gp globals resolved from symbols/SLPM_602.19.syms. */
#include "types.h"

/* ---------------------------------------------------------------------------
 * JP: 0x00518760  __ct__16BlowLocusEffect1Fiii
 * C++: BlowLocusEffect1::__ct(int, int, int)
 * size: 0x2c8 bytes
 * --------------------------------------------------------------------------- */
undefined8
__ct__16BlowLocusEffect1Fiii
          (undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined4 param_4)

{
  undefined8 uVar1;
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  int iVar7;
  
  __ct__6BtlEffFii(param_1,param_2,param_3);
  iVar7 = (int)param_1;
  *(undefined4 *)(iVar7 + 0x14) = 0x40a030;
  *(undefined4 *)(iVar7 + 0x28) = 0x40a040;
  *(undefined4 *)(iVar7 + 0x34) = 0x40a050;
  puVar6 = (undefined4 *)(iVar7 + 0x80);
  do {
    *puVar6 = in_zero_lo;
    puVar6[1] = in_zero_hi;
    puVar6[2] = in_zero_udw;
    puVar6[3] = in_register_0000000c;
    puVar6 = puVar6 + 4;
  } while (puVar6 != (undefined4 *)(iVar7 + 0x100));
  puVar6 = (undefined4 *)(iVar7 + 0x100);
  do {
    *puVar6 = in_zero_lo;
    puVar6[1] = in_zero_hi;
    puVar6[2] = in_zero_udw;
    puVar6[3] = in_register_0000000c;
    puVar6 = puVar6 + 4;
  } while (puVar6 != (undefined4 *)(iVar7 + 0x300));
  *(undefined4 *)(iVar7 + 0x5c) = 0;
  *(undefined4 *)(iVar7 + 0x60) = 0;
  *(undefined4 *)(iVar7 + 100) = 0;
  *(undefined4 *)(iVar7 + 0x40) = 0;
  *(int *)(iVar7 + 0x44) = (int)param_2;
  *(int *)(iVar7 + 0x48) = (int)param_3;
  *(undefined4 *)(iVar7 + 0x4c) = 8;
  *(undefined4 *)(iVar7 + 0x394) = param_4;
  *(undefined4 *)(iVar7 + 0x6c) = 0;
  *(undefined4 *)(iVar7 + 0x68) = 0;
  *(undefined4 *)(iVar7 + 0x70) = 0;
  *(undefined4 *)(iVar7 + 0x388) = 0;
  *(undefined4 *)(iVar7 + 0x1c) = 0;
  *(undefined4 *)(iVar7 + 0x18) = 0;
  *(undefined4 *)(iVar7 + 0x54) = 0;
  *(undefined4 *)(iVar7 + 900) = 0;
  *(undefined4 *)(iVar7 + 0x380) = 0;
  iVar2 = iGpffff86b4 + *(int *)(iVar7 + 0x48) * 0x4f0 + *(int *)(iVar7 + 0x394) * 0x10;
  iVar3 = iVar7 + *(int *)(iVar7 + 0x6c) * 0x10;
  uVar1 = *(undefined8 *)(iVar2 + 0x460);
  uVar4 = *(undefined4 *)(iVar2 + 0x468);
  uVar5 = *(undefined4 *)(iVar2 + 0x46c);
  *(int *)(iVar3 + 0x80) = (int)uVar1;
  *(int *)(iVar3 + 0x84) = (int)((ulong)uVar1 >> 0x20);
  *(undefined4 *)(iVar3 + 0x88) = uVar4;
  *(undefined4 *)(iVar3 + 0x8c) = uVar5;
  *(float *)(iVar7 + 0x390) =
       *(float *)(iGpffff86b4 + *(int *)(iVar7 + 0x48) * 0x4f0 + 0x4e0) * 0.75;
  *(int *)(iVar7 + 0x6c) = *(int *)(iVar7 + 0x6c) + 1;
  *(int *)(iVar7 + 0x68) = *(int *)(iVar7 + 0x68) + 1;
  for (iVar2 = 0; iVar2 < 0x10; iVar2 = iVar2 + 1) {
    iVar3 = rand();
    *(float *)(iVar7 + iVar2 * 4 + 0x300) = ((float)iVar3 / 2.1474836e+09) * 6.2831855 - 3.1415927;
    if (iVar2 == 0) {
      *(undefined4 *)(iVar7 + 0x340) = 0;
    }
    else {
      iVar3 = rand();
      *(float *)(iVar7 + iVar2 * 4 + 0x340) = ((float)iVar3 / 2.1474836e+09) * 2.0 - 1.0;
    }
  }
  Entry__7CPollerFP7CPolObjib(iGpffff858c + 0x48,param_1,0x80,0);
  BtlEffEntry__7CBattleFiP6BtlEff(iGpffff86b4,*(undefined4 *)(iVar7 + 0x48),param_1);
  return param_1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00518a30  __dt__16BlowLocusEffect1Fv
 * C++: BlowLocusEffect1::__dt()
 * size: 0x154 bytes
 * --------------------------------------------------------------------------- */
int __dt__16BlowLocusEffect1Fv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x14) = 0x40a030;
    *(undefined4 *)(param_1 + 0x28) = 0x40a040;
    *(undefined4 *)(param_1 + 0x34) = 0x40a050;
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
 * JP: 0x00518b90  Destruct__16BlowLocusEffect1Fv
 * C++: BlowLocusEffect1::Destruct()
 * size: 0xc8 bytes
 * --------------------------------------------------------------------------- */
void Destruct__16BlowLocusEffect1Fv(int param_1)

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
 * JP: 0x00518c60  Polling__16BlowLocusEffect1Fv
 * C++: BlowLocusEffect1::Polling()
 * size: 0x55c bytes
 * --------------------------------------------------------------------------- */
undefined4 Polling__16BlowLocusEffect1Fv(int param_1)

{
  undefined8 uVar1;
  undefined1 auVar2 [16];
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  float fVar8;
  undefined1 auVar9 [16];
  undefined1 auVar10 [16];
  undefined1 auStack_100 [16];
  undefined1 auStack_f0 [16];
  undefined1 auStack_e0 [16];
  undefined1 auStack_d0 [8];
  undefined4 uStack_c8;
  undefined4 uStack_c4;
  undefined1 auStack_c0 [16];
  undefined1 auStack_b0 [8];
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  undefined1 auStack_a0 [16];
  undefined4 auStack_90 [7];
  undefined4 uStack_74;
  undefined1 auStack_8 [8];
  
  if (*(int *)(param_1 + 0x5c) == 1) {
    if ((*(byte *)(iGpffff86b4 + 0x24) & 1) == 0) {
      *(float *)(param_1 + 0x390) =
           *(float *)(param_1 + 0x390) * (1.0 - *(float *)(iGpffff86b4 + 0x38));
      *(float *)(param_1 + 0x38c) = *(float *)(param_1 + 0x38c) + *(float *)(iGpffff86b4 + 0x38);
      while ((1 < *(int *)(param_1 + 0x70) && (0.008333334 < *(float *)(param_1 + 0x38c)))) {
        *(float *)(param_1 + 0x38c) = *(float *)(param_1 + 0x38c) - 0.008333334;
        *(int *)(param_1 + 0x70) = *(int *)(param_1 + 0x70) + -1;
      }
      if (*(int *)(param_1 + 0x70) < 2) {
        BtlEffRelease__7CBattleFiP6BtlEff(iGpffff86b4,*(undefined4 *)(param_1 + 0x48),param_1);
        if ((long)((ulong)*(byte *)(param_1 + 0x40) << 0x3e) < 0) {
          iVar3 = param_1;
          if (param_1 != 0) {
            iVar3 = param_1 + 0x18;
          }
          ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,iVar3);
        }
        *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfd;
        (**(code **)(*(int *)(param_1 + 0x34) + 0xc))();
        return 1;
      }
    }
  }
  else if ((*(int *)(param_1 + 0x5c) == 0) && ((*(byte *)(iGpffff86b4 + 0x24) & 1) == 0)) {
    iVar3 = iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + *(int *)(param_1 + 0x394) * 0x10;
    iVar4 = param_1 + *(int *)(param_1 + 0x6c) * 0x10;
    uVar1 = *(undefined8 *)(iVar3 + 0x3e0);
    uVar6 = *(undefined4 *)(iVar3 + 1000);
    uVar7 = *(undefined4 *)(iVar3 + 0x3ec);
    *(int *)(iVar4 + 0x80) = (int)uVar1;
    *(int *)(iVar4 + 0x84) = (int)((ulong)uVar1 >> 0x20);
    *(undefined4 *)(iVar4 + 0x88) = uVar6;
    *(undefined4 *)(iVar4 + 0x8c) = uVar7;
    *(float *)(param_1 + 0x390) =
         *(float *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x4e0) * 0.75;
    *(int *)(param_1 + 0x6c) = *(int *)(param_1 + 0x6c) + 1;
    if (7 < *(int *)(param_1 + 0x6c)) {
      *(undefined4 *)(param_1 + 0x6c) = 0;
    }
    *(int *)(param_1 + 0x68) = *(int *)(param_1 + 0x68) + 1;
    if (8 < *(int *)(param_1 + 0x68)) {
      *(undefined4 *)(param_1 + 0x68) = 8;
    }
    iVar3 = *(int *)(param_1 + 0x6c);
    auStack_90[0] = in_zero_lo;
    auStack_90[1] = in_zero_hi;
    auStack_90[2] = in_zero_udw;
    auStack_90[3] = in_register_0000000c;
    auStack_90[4] = in_zero_lo;
    auStack_90[5] = in_zero_hi;
    auStack_90[6] = in_zero_udw;
    uStack_74 = in_register_0000000c;
    for (iVar4 = 0; iVar4 < *(int *)(param_1 + 0x68); iVar4 = iVar4 + 1) {
      iVar3 = iVar3 + -1;
      if (iVar3 < 0) {
        iVar3 = 7;
      }
      iVar5 = param_1 + iVar3 * 0x10;
      uVar1 = *(undefined8 *)(iVar5 + 0x80);
      uVar6 = *(undefined4 *)(iVar5 + 0x88);
      uVar7 = *(undefined4 *)(iVar5 + 0x8c);
      auStack_90[iVar4 * 4] = (int)uVar1;
      auStack_90[iVar4 * 4 + 1] = (int)((ulong)uVar1 >> 0x20);
      auStack_90[iVar4 * 4 + 2] = uVar6;
      auStack_90[iVar4 * 4 + 3] = uVar7;
    }
    *(int *)(param_1 + 0x70) = (*(int *)(param_1 + 0x68) + -1) * 4 + 1;
    if (*(int *)(param_1 + 0x68) == 1) {
      *(undefined4 *)(param_1 + 0x100) = auStack_90[0];
      *(undefined4 *)(param_1 + 0x104) = auStack_90[1];
      *(undefined4 *)(param_1 + 0x108) = auStack_90[2];
      *(undefined4 *)(param_1 + 0x10c) = auStack_90[3];
    }
    else if (*(int *)(param_1 + 0x68) == 2) {
      *(undefined4 *)(param_1 + 0x100) = auStack_90[0];
      *(undefined4 *)(param_1 + 0x104) = auStack_90[1];
      *(undefined4 *)(param_1 + 0x108) = auStack_90[2];
      *(undefined4 *)(param_1 + 0x10c) = auStack_90[3];
      auVar9._4_4_ = auStack_90[1];
      auVar9._0_4_ = auStack_90[0];
      auVar9._8_4_ = auStack_90[2];
      auVar9._12_4_ = auStack_90[3];
      auVar9 = _lqc2(auVar9);
      auVar10._4_4_ = auStack_90[5];
      auVar10._0_4_ = auStack_90[4];
      auVar10._8_4_ = auStack_90[6];
      auVar10._12_4_ = uStack_74;
      auVar10 = _lqc2(auVar10);
      auVar9 = _vsub(auVar9,auVar10);
      auStack_e0 = _sqc2(auVar9);
      __ct__7FVectorFRC7FVector(auStack_a0,auStack_e0);
      for (iVar3 = 1; iVar3 < 4; iVar3 = iVar3 + 1) {
        iVar4 = -iVar3 + 4;
        if (iVar4 < 0) {
          iVar4 = -iVar3 + 7;
        }
        auVar9 = _lqc2(auStack_a0);
        auVar10 = _qmtc2((float)(iVar4 >> 2));
        auVar9 = _vmulbc(auVar9,auVar10);
        auStack_100 = _sqc2(auVar9);
        __ct__7FVectorFRC7FVector(auStack_c0,auStack_100);
        auVar2._4_4_ = auStack_90[5];
        auVar2._0_4_ = auStack_90[4];
        auVar2._8_4_ = auStack_90[6];
        auVar2._12_4_ = uStack_74;
        auVar9 = _lqc2(auVar2);
        auVar10 = _lqc2(auStack_c0);
        auVar9 = _vadd(auVar9,auVar10);
        auStack_f0 = _sqc2(auVar9);
        __ct__7FVectorFRC7FVector(auStack_b0,auStack_f0);
        iVar4 = param_1 + iVar3 * 0x10;
        *(int *)(iVar4 + 0x100) = auStack_b0._0_4_;
        *(int *)(iVar4 + 0x104) = auStack_b0._4_4_;
        *(undefined4 *)(iVar4 + 0x108) = uStack_a8;
        *(undefined4 *)(iVar4 + 0x10c) = uStack_a4;
      }
      *(undefined4 *)(param_1 + 0x140) = auStack_90[4];
      *(undefined4 *)(param_1 + 0x144) = auStack_90[5];
      *(undefined4 *)(param_1 + 0x148) = auStack_90[6];
      *(undefined4 *)(param_1 + 0x14c) = uStack_74;
    }
    else {
      __ct__9GsxSplineFv(auStack_8);
      Create__9GsxSplineFUiUiP7FVector(auStack_8,*(undefined4 *)(param_1 + 0x68),0,auStack_90);
      fVar8 = 0.0;
      for (iVar3 = 0; iVar3 < *(int *)(param_1 + 0x70); iVar3 = iVar3 + 1) {
        GetPosition__9GsxSplineFf(fVar8,auStack_d0,auStack_8);
        iVar4 = param_1 + iVar3 * 0x10;
        *(int *)(iVar4 + 0x100) = auStack_d0._0_4_;
        *(int *)(iVar4 + 0x104) = auStack_d0._4_4_;
        *(undefined4 *)(iVar4 + 0x108) = uStack_c8;
        *(undefined4 *)(iVar4 + 0x10c) = uStack_c4;
        fVar8 = fVar8 + 1.0 / (float)(*(int *)(param_1 + 0x70) + -1);
        if (1.0 < fVar8) {
          fVar8 = 1.0;
        }
      }
      Release__9GsxSplineFv(auStack_8);
      __dt__9GsxSplineFv(auStack_8,0xffffffffffffffff);
    }
  }
  return 0;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005191c0  MakePacket__16BlowLocusEffect1Fv
 * C++: BlowLocusEffect1::MakePacket()
 * size: 0xd3c bytes
 * --------------------------------------------------------------------------- */
/* WARNING: Removing unreachable block (ram,0x005192e8) */
/* WARNING: Removing unreachable block (ram,0x00519c50) */

void MakePacket__16BlowLocusEffect1Fv(int param_1)

{
  bool bVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  bool bVar5;
  float in_zero_lo;
  float in_zero_hi;
  float in_zero_udw;
  float in_register_0000000c;
  undefined4 uVar6;
  undefined8 uVar7;
  ulong uVar8;
  long lVar9;
  float *pfVar10;
  int iVar11;
  ulong *puVar12;
  uint uVar13;
  int iVar14;
  float fVar15;
  float fVar16;
  undefined1 in_vf0 [16];
  undefined1 auVar17 [16];
  undefined1 auVar18 [16];
  undefined1 auVar19 [16];
  undefined1 auStack_ab0 [16];
  undefined1 auStack_aa0 [16];
  undefined1 auStack_a90 [16];
  undefined1 auStack_a80 [16];
  undefined1 auStack_a70 [8];
  float fStack_a68;
  undefined4 uStack_a64;
  undefined1 auStack_a60 [8];
  undefined4 uStack_a58;
  undefined4 uStack_a54;
  undefined4 uStack_a50;
  float fStack_a4c;
  undefined4 uStack_a48;
  undefined4 uStack_a44;
  undefined4 uStack_a40;
  undefined4 uStack_a3c;
  undefined4 uStack_a38;
  undefined4 uStack_a34;
  undefined4 uStack_a30;
  undefined4 uStack_a2c;
  undefined4 uStack_a28;
  undefined4 uStack_a24;
  undefined4 uStack_a20;
  undefined4 uStack_a1c;
  undefined4 uStack_a18;
  undefined4 uStack_a14;
  undefined4 uStack_a10;
  undefined4 uStack_a0c;
  undefined4 uStack_a08;
  undefined4 uStack_a04;
  undefined1 auStack_a00 [16];
  undefined1 auStack_9f0 [8];
  float fStack_9e8;
  float fStack_9e4;
  undefined1 auStack_9e0 [8];
  float fStack_9d8;
  undefined4 uStack_9d4;
  undefined1 auStack_9d0 [8];
  float fStack_9c8;
  undefined4 uStack_9c4;
  undefined1 auStack_9c0 [8];
  float fStack_9b8;
  undefined4 uStack_9b4;
  undefined1 auStack_9b0 [8];
  float fStack_9a8;
  float fStack_9a4;
  int aiStack_9a0 [128];
  undefined4 auStack_7a0 [16];
  float afStack_760 [128];
  undefined1 auStack_560 [16];
  undefined1 auStack_550 [16];
  undefined1 auStack_540 [16];
  undefined1 auStack_530 [16];
  float afStack_520 [261];
  float fStack_10c;
  float fStack_108;
  float fStack_104;
  float afStack_100 [32];
  float afStack_80 [32];
  
  fVar16 = 0.0;
  afStack_520[0x104] = in_zero_lo;
  fStack_10c = in_zero_hi;
  fStack_108 = in_zero_udw;
  fStack_104 = in_register_0000000c;
  for (iVar11 = 0; iVar11 < *(int *)(param_1 + 0x70) + -1; iVar11 = iVar11 + 1) {
    auVar17 = _lqc2(*(undefined1 (*) [16])(param_1 + (iVar11 + 1) * 0x10 + 0x100));
    auVar18 = _lqc2(*(undefined1 (*) [16])(param_1 + iVar11 * 0x10 + 0x100));
    auVar17 = _vsub(auVar17,auVar18);
    auStack_a80 = _sqc2(auVar17);
    __ct__7FVectorFRC7FVector(auStack_9b0,auStack_a80);
    afStack_520[0x104] = auStack_9b0._0_4_;
    fStack_10c = auStack_9b0._4_4_;
    fStack_108 = fStack_9a8;
    fStack_104 = fStack_9a4;
    fVar15 = (float)Length__7FVectorCFv(afStack_520 + 0x104);
    afStack_80[iVar11] = fVar15;
    fVar16 = fVar16 + afStack_80[iVar11];
  }
  afStack_100[0] = 0.0;
  fVar15 = 0.0;
  for (iVar11 = 0; iVar11 < *(int *)(param_1 + 0x70) + -1; iVar11 = iVar11 + 1) {
    fVar15 = fVar15 + afStack_80[iVar11];
    afStack_100[iVar11 + 1] =
         (float)*(ushort *)(*(int *)(iGpffff86b4 + 0x4258) + 2) * (fVar15 / fVar16) * 16.0;
  }
  afStack_520[0x100] = 0.0;
  afStack_520[0x101] = 0.0;
  afStack_520[0x102] = 0.0;
  afStack_520[0x103] = 1.0;
  pfVar10 = afStack_520 + 0x80;
  do {
    *pfVar10 = in_zero_lo;
    pfVar10[1] = in_zero_hi;
    pfVar10[2] = in_zero_udw;
    pfVar10[3] = in_register_0000000c;
    pfVar10 = pfVar10 + 4;
  } while (pfVar10 != afStack_520 + 0x100);
  for (iVar11 = 0; iVar11 < *(int *)(param_1 + 0x70); iVar11 = iVar11 + 1) {
    if (1 < *(int *)(param_1 + 0x70)) {
      if (iVar11 == 0) {
        auVar17 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x110));
        auVar18 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x100));
        auVar17 = _vsub(auVar17,auVar18);
        auStack_a90 = _sqc2(auVar17);
        __ct__7FVectorFRC7FVector(auStack_9c0,auStack_a90);
        afStack_520[0x100] = auStack_9c0._0_4_;
        afStack_520[0x101] = auStack_9c0._4_4_;
        afStack_520[0x102] = fStack_9b8;
        afStack_520[0x103] = (float)uStack_9b4;
      }
      else if (iVar11 + 1 < *(int *)(param_1 + 0x70)) {
        auVar17 = _lqc2(*(undefined1 (*) [16])(param_1 + (iVar11 + 1) * 0x10 + 0x100));
        auVar18 = _lqc2(*(undefined1 (*) [16])(param_1 + iVar11 * 0x10 + 0x100));
        auVar17 = _vsub(auVar17,auVar18);
        auStack_aa0 = _sqc2(auVar17);
        __ct__7FVectorFRC7FVector(auStack_9d0,auStack_aa0);
        afStack_520[0x100] = auStack_9d0._0_4_;
        afStack_520[0x101] = auStack_9d0._4_4_;
        afStack_520[0x102] = fStack_9c8;
        afStack_520[0x103] = (float)uStack_9c4;
      }
      else {
        auVar17 = _lqc2(*(undefined1 (*) [16])(param_1 + iVar11 * 0x10 + 0x100));
        auVar18 = _lqc2(*(undefined1 (*) [16])(param_1 + (iVar11 + -1) * 0x10 + 0x100));
        auVar17 = _vsub(auVar17,auVar18);
        auStack_ab0 = _sqc2(auVar17);
        __ct__7FVectorFRC7FVector(auStack_9e0,auStack_ab0);
        afStack_520[0x100] = auStack_9e0._0_4_;
        afStack_520[0x101] = auStack_9e0._4_4_;
        afStack_520[0x102] = fStack_9d8;
        afStack_520[0x103] = (float)uStack_9d4;
      }
    }
    uVar7 = __ct__7FVectorFRC7FVector(auStack_a00,afStack_520 + 0x100);
    Get3DAngleRad__F7FVector(auStack_9f0,uVar7);
    afStack_520[iVar11 * 4 + 0x80] = auStack_9f0._0_4_;
    afStack_520[iVar11 * 4 + 0x81] = auStack_9f0._4_4_;
    afStack_520[iVar11 * 4 + 0x82] = fStack_9e8;
    afStack_520[iVar11 * 4 + 0x83] = fStack_9e4;
  }
  pfVar10 = afStack_520;
  do {
    *pfVar10 = in_zero_lo;
    pfVar10[1] = in_zero_hi;
    pfVar10[2] = in_zero_udw;
    pfVar10[3] = in_register_0000000c;
    pfVar10 = pfVar10 + 4;
  } while (pfVar10 != afStack_520 + 0x80);
  auVar17 = _vmr32(in_vf0);
  auVar18 = _vmr32(auVar17);
  auVar19 = _vmr32(auVar18);
  auStack_530 = _sqc2(in_vf0);
  auStack_540 = _sqc2(auVar17);
  auStack_550 = _sqc2(auVar18);
  auStack_560 = _sqc2(auVar19);
  for (iVar11 = 0; iVar11 < *(int *)(param_1 + 0x70); iVar11 = iVar11 + 1) {
    iVar14 = param_1 + iVar11 * 0x10;
    uVar7 = *(undefined8 *)(iVar14 + 0x100);
    fVar16 = *(float *)(iVar14 + 0x108);
    fVar15 = *(float *)(iVar14 + 0x10c);
    afStack_520[iVar11 * 4] = (float)uVar7;
    afStack_520[iVar11 * 4 + 1] = (float)((ulong)uVar7 >> 0x20);
    afStack_520[iVar11 * 4 + 2] = fVar16;
    afStack_520[iVar11 * 4 + 3] = fVar15;
  }
  for (iVar11 = 0; iVar11 < *(int *)(param_1 + 0x70); iVar11 = iVar11 + 1) {
    afStack_760[iVar11 * 4] = afStack_520[iVar11 * 4];
    afStack_760[iVar11 * 4 + 1] = afStack_520[iVar11 * 4 + 1];
    afStack_760[iVar11 * 4 + 2] = afStack_520[iVar11 * 4 + 2];
    afStack_760[iVar11 * 4 + 3] = 1.0;
  }
  GetViewScreenMatrix__9GsxCameraFv(&uStack_a40,uGpffff8598);
  auStack_560._4_4_ = uStack_a3c;
  auStack_560._0_4_ = uStack_a40;
  auStack_560._8_4_ = uStack_a38;
  auStack_560._12_4_ = uStack_a34;
  auStack_550._4_4_ = uStack_a2c;
  auStack_550._0_4_ = uStack_a30;
  auStack_550._8_4_ = uStack_a28;
  auStack_550._12_4_ = uStack_a24;
  auStack_540._4_4_ = uStack_a1c;
  auStack_540._0_4_ = uStack_a20;
  auStack_540._8_4_ = uStack_a18;
  auStack_540._12_4_ = uStack_a14;
  auStack_530._4_4_ = uStack_a0c;
  auStack_530._0_4_ = uStack_a10;
  auStack_530._8_4_ = uStack_a08;
  auStack_530._12_4_ = uStack_a04;
  for (iVar11 = 0; iVar11 < 4; iVar11 = iVar11 + 1) {
    auStack_7a0[iVar11 * 4] = *(undefined4 *)(auStack_560 + iVar11 * 0x10);
    auStack_7a0[iVar11 * 4 + 1] = *(undefined4 *)(auStack_560 + iVar11 * 0x10 + 4);
    auStack_7a0[iVar11 * 4 + 2] = *(undefined4 *)(auStack_560 + iVar11 * 0x10 + 8);
    auStack_7a0[iVar11 * 4 + 3] = *(undefined4 *)(auStack_560 + iVar11 * 0x10 + 0xc);
  }
  sceVu0RotTransPersN(aiStack_9a0,auStack_7a0,afStack_760,*(undefined4 *)(param_1 + 0x70),0);
  bVar5 = false;
  for (iVar11 = 0; iVar11 < *(int *)(param_1 + 0x70); iVar11 = iVar11 + 1) {
    if ((((aiStack_9a0[iVar11 * 4] < 0) || (0x10000 < aiStack_9a0[iVar11 * 4])) ||
        (aiStack_9a0[iVar11 * 4 + 1] < 0)) ||
       ((0x10000 < aiStack_9a0[iVar11 * 4 + 1] || (aiStack_9a0[iVar11 * 4 + 2] < 0)))) {
      bVar5 = true;
    }
  }
  if (*(int *)(param_1 + 0x70) < 2) {
    bVar5 = true;
  }
  bVar1 = (*(byte *)(param_1 + 0x40) & 1) == 0;
  uVar13 = (uint)bVar1;
  iVar11 = (*(int *)(param_1 + 0x70) + 3) * 0x10;
  iVar14 = iVar11 + 10;
  if (*(int *)(param_1 + uVar13 * 4 + 0x380) != iVar14) {
    __dla__FPv(*(undefined4 *)(param_1 + uVar13 * 4 + 0x18));
    *(undefined4 *)(param_1 + uVar13 * 4 + 0x18) = 0;
    *(undefined4 *)(param_1 + uVar13 * 4 + 0x380) = 0;
  }
  if (*(int *)(param_1 + uVar13 * 4 + 0x18) == 0) {
    uVar6 = __nwa__FUi(iVar14 * 0x10);
    *(undefined4 *)(param_1 + uVar13 * 4 + 0x18) = uVar6;
    *(int *)(param_1 + uVar13 * 4 + 0x380) = iVar14;
    iVar14 = *(int *)(param_1 + uVar13 * 4 + 0x18);
    *(int *)(iVar14 + 0x10) = iVar11 + 0x10000007;
    *(undefined4 *)(iVar14 + 0x14) = 0;
    *(undefined4 *)(iVar14 + 0x18) = 0;
    *(int *)(iVar14 + 0x1c) = iVar11 + 0x50000007;
    *(undefined8 *)(iVar14 + 0x20) = 0x6000000000000001;
    *(undefined8 *)(iVar14 + 0x28) = 0xe6e8ee;
    *(undefined8 *)(iVar14 + 0x30) = 1;
    *(undefined8 *)(iVar14 + 0x38) = 0x3f;
    *(undefined8 *)(iVar14 + 0x40) = 0x60;
    *(undefined8 *)(iVar14 + 0x48) = 0x14;
    *(undefined8 *)(iVar14 + 0x50) = 5;
    *(undefined8 *)(iVar14 + 0x58) = 0;
    *(undefined8 *)(iVar14 + 0x60) = 0x73001;
    *(undefined8 *)(iVar14 + 0x68) = 0x47;
    uVar7 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x4258),1);
    *(undefined8 *)(iVar14 + 0x70) = uVar7;
    *(undefined8 *)(iVar14 + 0x78) = 0;
    *(undefined8 *)(iVar14 + 0x80) = 0x44;
    *(undefined8 *)(iVar14 + 0x88) = 0x42;
  }
  puVar2 = *(undefined4 **)(param_1 + uVar13 * 4 + 0x18);
  if (bVar5) {
    *(undefined4 **)(param_1 + 0x54) = puVar2;
    *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfe | bVar1;
  }
  else {
    *puVar2 = 0x50000000;
    puVar2[1] = *(undefined4 *)
                 (*(int *)(iGpffff86b4 + 0x4258) +
                  (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x4258) + 10) * 4 + 0xc);
    puVar2[2] = 0;
    puVar2[3] = 0;
    puVar12 = (ulong *)(puVar2 + 0x24);
    for (iVar11 = 0; iVar11 < 0x10; iVar11 = iVar11 + 1) {
      if (iVar11 != 0) {
        fStack_a4c = -*(float *)(param_1 + 0x390) * *(float *)(param_1 + iVar11 * 4 + 0x340);
        uStack_a50 = 0;
        uStack_a48 = 0;
        uStack_a44 = 0x3f800000;
        afStack_520[0x100] = 0.0;
        afStack_520[0x102] = 0.0;
        afStack_520[0x103] = 1.0;
        auVar17 = _vmr32(in_vf0);
        auVar18 = _vmr32(auVar17);
        auVar19 = _vmr32(auVar18);
        auStack_530 = _sqc2(in_vf0);
        auStack_540 = _sqc2(auVar17);
        auStack_550 = _sqc2(auVar18);
        auStack_560 = _sqc2(auVar19);
        afStack_520[0x101] = fStack_a4c;
        sceVu0RotMatrixZ(*(undefined4 *)(param_1 + iVar11 * 4 + 0x300),auStack_560,auStack_560);
        ApplyMatrix__6MatrixCFRC7FVector(auStack_a60,auStack_560,afStack_520 + 0x100);
        afStack_520[0x100] = (float)auStack_a60._0_4_;
        afStack_520[0x101] = (float)auStack_a60._4_4_;
        afStack_520[0x102] = (float)uStack_a58;
        afStack_520[0x103] = (float)uStack_a54;
        auVar17 = _vmr32(in_vf0);
        auVar18 = _vmr32(auVar17);
        auVar19 = _vmr32(auVar18);
        auStack_530 = _sqc2(in_vf0);
        auStack_540 = _sqc2(auVar17);
        auStack_550 = _sqc2(auVar18);
        auStack_560 = _sqc2(auVar19);
        sceVu0RotMatrixX(afStack_520[iVar11 * 4 + 0x80],auStack_560,auStack_560);
        sceVu0RotMatrixY(3.1415927 - afStack_520[iVar11 * 4 + 0x81],auStack_560,auStack_560);
        ApplyMatrix__6MatrixCFRC7FVector(auStack_a70,auStack_560,afStack_520 + 0x100);
        afStack_520[0x100] = auStack_a70._0_4_;
        afStack_520[0x101] = auStack_a70._4_4_;
        afStack_520[0x102] = fStack_a68;
        afStack_520[0x103] = (float)uStack_a64;
        for (iVar14 = 0; iVar14 < *(int *)(param_1 + 0x70); iVar14 = iVar14 + 1) {
          afStack_760[iVar14 * 4] = *(float *)(param_1 + iVar14 * 0x10 + 0x100) + afStack_520[0x100]
          ;
          afStack_760[iVar14 * 4 + 1] =
               *(float *)(param_1 + iVar14 * 0x10 + 0x104) + afStack_520[0x101];
          afStack_760[iVar14 * 4 + 2] =
               *(float *)(param_1 + iVar14 * 0x10 + 0x108) + afStack_520[0x102];
          afStack_760[iVar14 * 4 + 3] = 1.0;
        }
        sceVu0RotTransPersN(aiStack_9a0,auStack_7a0,afStack_760,*(undefined4 *)(param_1 + 0x70),0);
      }
      fVar16 = (float)*(ushort *)(*(int *)(iGpffff86b4 + 0x4258) + 4) *
               (*(float *)(param_1 + iVar11 * 4 + 0x340) / 2.0 + 0.5) * 16.0;
      *puVar12 = 0x4400000000000001;
      puVar12[1] = 0xc310;
      puVar12[2] = 0x152;
      puVar12[3] = 0x80808080;
      uVar8 = __fixunssfdi(afStack_100[0]);
      lVar9 = __fixunssfdi(fVar16);
      puVar12[4] = uVar8 | lVar9 << 0x10;
      lVar9 = __fixunssfdi((float)aiStack_9a0[2] / 16.0);
      puVar12[5] = lVar9 << 0x20 | (long)aiStack_9a0[0] | (long)aiStack_9a0[1] << 0x10;
      if (iVar11 == 0xf) {
        puVar12[6] = (long)(*(int *)(param_1 + 0x70) + -1) | 0x2400000000008000;
      }
      else {
        puVar12[6] = (long)(*(int *)(param_1 + 0x70) + -1) | 0x2400000000000000;
      }
      puVar12[7] = 0x43;
      puVar12 = puVar12 + 8;
      for (iVar14 = 1; iVar14 < *(int *)(param_1 + 0x70); iVar14 = iVar14 + 1) {
        lVar9 = __fixunssfdi(fVar16);
        uVar8 = __fixunssfdi(afStack_100[iVar14]);
        *puVar12 = lVar9 << 0x10 | uVar8;
        iVar3 = aiStack_9a0[iVar14 * 4 + 1];
        iVar4 = aiStack_9a0[iVar14 * 4];
        lVar9 = __fixunssfdi((float)aiStack_9a0[iVar14 * 4 + 2] / 16.0);
        puVar12[1] = lVar9 << 0x20 | (long)iVar4 | (long)iVar3 << 0x10;
        puVar12 = puVar12 + 2;
      }
    }
    *(ulong **)(param_1 + 0x54) = puVar12;
    *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfe | bVar1;
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00519f00  EndSet__16BlowLocusEffect1Fv
 * C++: BlowLocusEffect1::EndSet()
 * size: 0x4c bytes
 * --------------------------------------------------------------------------- */
void EndSet__16BlowLocusEffect1Fv(int param_1)

{
  if (*(int *)(param_1 + 0x5c) == 0) {
    *(undefined4 *)(param_1 + 0x5c) = 1;
    *(undefined4 *)(param_1 + 0x60) = 0;
    *(undefined4 *)(param_1 + 100) = 0;
    *(undefined4 *)(param_1 + 0x38c) = 0;
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b670  @24@__dt__16BlowLocusEffect1Fv
 * C++: @24@__dt__16BlowLocusEffect1Fv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int * _24___dt__16BlowLocusEffect1Fv(int *param_1,short param_2)

{
  int *piVar1;
  
  piVar1 = param_1 + -6;
  if (piVar1 != (int *)0x0) {
    param_1[-1] = 0x40a030;
    param_1[4] = 0x40a040;
    param_1[7] = 0x40a050;
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
 * JP: 0x0054b680  @44@__dt__16BlowLocusEffect1Fv
 * C++: @44@__dt__16BlowLocusEffect1Fv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int _44___dt__16BlowLocusEffect1Fv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x2c;
  if (iVar1 != 0) {
    *(undefined4 *)(param_1 + -0x18) = 0x40a030;
    *(undefined4 *)(param_1 + -4) = 0x40a040;
    *(undefined4 *)(param_1 + 8) = 0x40a050;
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

