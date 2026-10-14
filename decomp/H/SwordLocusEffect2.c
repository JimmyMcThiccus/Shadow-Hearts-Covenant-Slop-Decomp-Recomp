/* decomp/H/SwordLocusEffect2.c — cleaned Ghidra output (SH2JP_BATTLE.BIN, JP Furokuban, base 0x00430a00).
 * 9 function(s). Types: see types.h. Names/gp globals resolved from symbols/SLPM_602.19.syms. */
#include "types.h"

/* ---------------------------------------------------------------------------
 * JP: 0x0050ed20  __ct__17SwordLocusEffect2Fiiiii
 * C++: SwordLocusEffect2::__ct(int, int, int, int, int)
 * size: 0x2ec bytes
 * --------------------------------------------------------------------------- */
undefined8
__ct__17SwordLocusEffect2Fiiiii
          (undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined4 param_4,
          undefined4 param_5,undefined4 param_6)

{
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined1 auVar4 [16];
  undefined1 auVar5 [16];
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [8];
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined1 auStack_10 [16];
  
  __ct__6BtlEffFii(param_1,param_2,param_3);
  iVar3 = (int)param_1;
  *(undefined4 *)(iVar3 + 0x14) = 0x40a170;
  *(undefined4 *)(iVar3 + 0x28) = 0x40a180;
  *(undefined4 *)(iVar3 + 0x34) = 0x40a190;
  puVar2 = (undefined4 *)(iVar3 + 0x80);
  do {
    *puVar2 = in_zero_lo;
    puVar2[1] = in_zero_hi;
    puVar2[2] = in_zero_udw;
    puVar2[3] = in_register_0000000c;
    puVar2 = puVar2 + 4;
  } while (puVar2 != (undefined4 *)(iVar3 + 0x180));
  puVar2 = (undefined4 *)(iVar3 + 0x180);
  do {
    *puVar2 = in_zero_lo;
    puVar2[1] = in_zero_hi;
    puVar2[2] = in_zero_udw;
    puVar2[3] = in_register_0000000c;
    puVar2 = puVar2 + 4;
  } while (puVar2 != (undefined4 *)(iVar3 + 0x980));
  *(undefined4 *)(iVar3 + 0x5c) = 0;
  *(undefined4 *)(iVar3 + 0x60) = 0;
  *(undefined4 *)(iVar3 + 100) = 0;
  *(undefined4 *)(iVar3 + 0x40) = 0;
  *(int *)(iVar3 + 0x44) = (int)param_2;
  *(int *)(iVar3 + 0x48) = (int)param_3;
  *(undefined4 *)(iVar3 + 0x4c) = 8;
  *(undefined4 *)(iVar3 + 0x6c) = 0;
  *(undefined4 *)(iVar3 + 0x68) = 0;
  *(undefined4 *)(iVar3 + 0x70) = 0;
  *(undefined4 *)(iVar3 + 0x1c) = 0;
  *(undefined4 *)(iVar3 + 0x18) = 0;
  *(undefined4 *)(iVar3 + 0x54) = 0;
  *(undefined4 *)(iVar3 + 0x984) = 0;
  *(undefined4 *)(iVar3 + 0x980) = 0;
  *(undefined4 *)(iVar3 + 0x98c) = param_4;
  *(undefined4 *)(iVar3 + 0x990) = param_5;
  *(undefined4 *)(iVar3 + 0x994) = param_6;
  if (*(int *)(iVar3 + 0x990) == 0) {
    iVar1 = iGpffff86b4 + *(int *)(iVar3 + 0x48) * 0x4f0;
    uStack_18 = *(undefined4 *)(iVar1 + 0x468);
    uStack_14 = *(undefined4 *)(iVar1 + 0x46c);
    uStack_20 = (undefined4)*(undefined8 *)(iVar1 + 0x460);
    uStack_1c = (undefined4)((ulong)*(undefined8 *)(iVar1 + 0x460) >> 0x20);
    auStack_10 = *(undefined1 (*) [16])(iGpffff86b4 + *(int *)(iVar3 + 0x48) * 0x4f0 + 0x470);
  }
  else {
    iVar1 = iGpffff86b4 + *(int *)(iVar3 + 0x48) * 0x4f0;
    uStack_18 = *(undefined4 *)(iVar1 + 0x488);
    uStack_14 = *(undefined4 *)(iVar1 + 0x48c);
    uStack_20 = (undefined4)*(undefined8 *)(iVar1 + 0x480);
    uStack_1c = (undefined4)((ulong)*(undefined8 *)(iVar1 + 0x480) >> 0x20);
    auStack_10 = *(undefined1 (*) [16])(iGpffff86b4 + *(int *)(iVar3 + 0x48) * 0x4f0 + 0x490);
  }
  auVar4._4_4_ = uStack_1c;
  auVar4._0_4_ = uStack_20;
  auVar4._8_4_ = uStack_18;
  auVar4._12_4_ = uStack_14;
  auVar5 = _lqc2(auVar4);
  auVar4 = _lqc2(auStack_10);
  auVar4 = _vsub(auVar4,auVar5);
  auStack_10 = _sqc2(auVar4);
  __amu__7FVectorFf(0x3f4ccccd,auStack_10);
  iVar1 = iVar3 + *(int *)(iVar3 + 0x6c) * 0x20;
  *(undefined4 *)(iVar1 + 0x80) = uStack_20;
  *(undefined4 *)(iVar1 + 0x84) = uStack_1c;
  *(undefined4 *)(iVar1 + 0x88) = uStack_18;
  *(undefined4 *)(iVar1 + 0x8c) = uStack_14;
  auVar5._4_4_ = uStack_1c;
  auVar5._0_4_ = uStack_20;
  auVar5._8_4_ = uStack_18;
  auVar5._12_4_ = uStack_14;
  auVar4 = _lqc2(auVar5);
  auVar5 = _lqc2(auStack_10);
  auVar4 = _vadd(auVar4,auVar5);
  auStack_40 = _sqc2(auVar4);
  __ct__7FVectorFRC7FVector(auStack_30,auStack_40);
  iVar1 = iVar3 + *(int *)(iVar3 + 0x6c) * 0x20;
  *(int *)(iVar1 + 0x90) = auStack_30._0_4_;
  *(int *)(iVar1 + 0x94) = auStack_30._4_4_;
  *(undefined4 *)(iVar1 + 0x98) = uStack_28;
  *(undefined4 *)(iVar1 + 0x9c) = uStack_24;
  *(int *)(iVar3 + 0x6c) = *(int *)(iVar3 + 0x6c) + 1;
  *(int *)(iVar3 + 0x68) = *(int *)(iVar3 + 0x68) + 1;
  Entry__7CPollerFP7CPolObjib(iGpffff858c + 0x48,param_1,0x80,0);
  BtlEffEntry__7CBattleFiP6BtlEff(iGpffff86b4,*(undefined4 *)(iVar3 + 0x48),param_1);
  return param_1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0050f010  __dt__17SwordLocusEffect2Fv
 * C++: SwordLocusEffect2::__dt()
 * size: 0x154 bytes
 * --------------------------------------------------------------------------- */
int __dt__17SwordLocusEffect2Fv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x14) = 0x40a170;
    *(undefined4 *)(param_1 + 0x28) = 0x40a180;
    *(undefined4 *)(param_1 + 0x34) = 0x40a190;
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
 * JP: 0x0050f170  Destruct__17SwordLocusEffect2Fv
 * C++: SwordLocusEffect2::Destruct()
 * size: 0xc8 bytes
 * --------------------------------------------------------------------------- */
void Destruct__17SwordLocusEffect2Fv(int param_1)

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
 * JP: 0x0050f240  Polling__17SwordLocusEffect2Fv
 * C++: SwordLocusEffect2::Polling()
 * size: 0x17b0 bytes
 * --------------------------------------------------------------------------- */
undefined4 Polling__17SwordLocusEffect2Fv(int param_1)

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
  undefined1 auVar27 [16];
  undefined1 auVar28 [16];
  undefined1 auVar29 [16];
  undefined1 auVar30 [16];
  undefined1 auVar31 [16];
  undefined1 auVar32 [16];
  undefined1 auVar33 [16];
  undefined1 auVar34 [16];
  undefined1 auVar35 [16];
  undefined1 auVar36 [16];
  undefined1 auVar37 [16];
  undefined1 auVar38 [16];
  undefined1 auVar39 [16];
  undefined1 auVar40 [16];
  undefined1 auVar41 [16];
  undefined1 auVar42 [16];
  undefined1 auVar43 [16];
  undefined1 auVar44 [16];
  undefined1 auVar45 [16];
  undefined1 auVar46 [16];
  undefined1 auVar47 [16];
  undefined1 auVar48 [16];
  undefined1 auVar49 [16];
  undefined1 auVar50 [16];
  undefined1 auVar51 [16];
  undefined1 auVar52 [16];
  undefined1 auVar53 [16];
  undefined1 auVar54 [16];
  undefined1 auVar55 [16];
  undefined1 auVar56 [16];
  undefined1 auVar57 [16];
  undefined1 auVar58 [16];
  undefined1 auVar59 [16];
  undefined1 auVar60 [16];
  undefined1 auVar61 [16];
  undefined1 auVar62 [16];
  undefined1 auVar63 [16];
  undefined1 auVar64 [16];
  undefined1 auVar65 [16];
  undefined1 auVar66 [16];
  undefined1 auVar67 [16];
  undefined1 auVar68 [16];
  undefined1 auVar69 [16];
  undefined1 auVar70 [16];
  undefined1 auVar71 [16];
  undefined1 auVar72 [16];
  undefined1 auVar73 [16];
  undefined1 auVar74 [16];
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  int iVar75;
  int iVar76;
  undefined4 uVar77;
  undefined4 uVar78;
  int iVar79;
  byte *pbVar80;
  float fVar81;
  undefined1 in_vf0 [16];
  undefined1 auVar82 [16];
  undefined1 auVar83 [16];
  undefined1 auVar84 [16];
  undefined1 auStack_8e0 [16];
  undefined1 auStack_8d0 [16];
  undefined1 auStack_8c0 [16];
  undefined1 auStack_8b0 [16];
  undefined1 auStack_8a0 [16];
  undefined1 auStack_890 [16];
  undefined1 auStack_880 [16];
  undefined1 auStack_870 [16];
  undefined1 auStack_860 [16];
  undefined1 auStack_850 [16];
  undefined1 auStack_840 [16];
  undefined1 auStack_830 [16];
  undefined1 auStack_820 [16];
  undefined1 auStack_810 [16];
  undefined1 auStack_800 [16];
  undefined1 auStack_7f0 [16];
  undefined1 auStack_7e0 [16];
  undefined1 auStack_7d0 [16];
  undefined1 auStack_7c0 [16];
  undefined1 auStack_7b0 [16];
  undefined1 auStack_7a0 [16];
  undefined1 auStack_790 [16];
  undefined1 auStack_780 [16];
  undefined1 auStack_770 [16];
  undefined1 auStack_760 [16];
  undefined1 auStack_750 [16];
  undefined1 auStack_740 [16];
  undefined1 auStack_730 [16];
  undefined1 auStack_720 [16];
  undefined1 auStack_710 [16];
  undefined1 auStack_700 [16];
  undefined1 auStack_6f0 [16];
  undefined1 auStack_6e0 [16];
  undefined1 auStack_6d0 [16];
  undefined1 auStack_6c0 [16];
  undefined1 auStack_6b0 [16];
  undefined1 auStack_6a0 [16];
  undefined1 auStack_690 [16];
  undefined1 auStack_680 [16];
  undefined1 auStack_670 [16];
  undefined1 auStack_660 [16];
  undefined1 auStack_650 [16];
  undefined1 auStack_640 [16];
  undefined1 auStack_630 [16];
  undefined1 auStack_620 [16];
  undefined1 auStack_610 [16];
  undefined1 auStack_600 [16];
  undefined1 auStack_5f0 [16];
  undefined1 auStack_5e0 [16];
  undefined1 auStack_5d0 [16];
  undefined1 auStack_5c0 [16];
  undefined1 auStack_5b0 [16];
  undefined1 auStack_5a0 [8];
  undefined4 uStack_598;
  undefined4 uStack_594;
  undefined1 auStack_590 [8];
  undefined4 uStack_588;
  undefined4 uStack_584;
  undefined1 auStack_580 [16];
  undefined1 auStack_570 [8];
  undefined4 uStack_568;
  undefined4 uStack_564;
  undefined1 auStack_560 [8];
  undefined4 uStack_558;
  undefined4 uStack_554;
  undefined1 auStack_550 [16];
  undefined1 auStack_540 [8];
  undefined4 uStack_538;
  undefined4 uStack_534;
  undefined1 auStack_530 [8];
  undefined4 uStack_528;
  undefined4 uStack_524;
  undefined8 uStack_520;
  undefined4 uStack_518;
  undefined4 uStack_514;
  undefined8 uStack_510;
  undefined4 uStack_508;
  undefined4 uStack_504;
  undefined8 uStack_500;
  undefined4 uStack_4f8;
  undefined4 uStack_4f4;
  undefined8 uStack_4f0;
  undefined4 uStack_4e8;
  undefined4 uStack_4e4;
  undefined8 uStack_4e0;
  undefined4 uStack_4d8;
  undefined4 uStack_4d4;
  undefined8 uStack_4d0;
  undefined4 uStack_4c8;
  undefined4 uStack_4c4;
  undefined8 uStack_4c0;
  undefined4 uStack_4b8;
  undefined4 uStack_4b4;
  undefined8 uStack_4b0;
  undefined4 uStack_4a8;
  undefined4 uStack_4a4;
  undefined8 uStack_4a0;
  undefined4 uStack_498;
  undefined4 uStack_494;
  undefined8 uStack_490;
  undefined4 uStack_488;
  undefined4 uStack_484;
  undefined1 auStack_480 [16];
  undefined1 auStack_470 [16];
  undefined8 uStack_460;
  undefined4 uStack_458;
  undefined4 uStack_454;
  undefined1 auStack_450 [16];
  undefined1 auStack_440 [16];
  undefined8 uStack_430;
  undefined4 uStack_428;
  undefined4 uStack_424;
  undefined1 auStack_420 [16];
  undefined1 auStack_410 [16];
  undefined8 uStack_400;
  undefined4 uStack_3f8;
  undefined4 uStack_3f4;
  undefined1 auStack_3f0 [16];
  undefined1 auStack_3e0 [16];
  undefined8 uStack_3d0;
  undefined4 uStack_3c8;
  undefined4 uStack_3c4;
  undefined1 auStack_3c0 [16];
  undefined1 auStack_3b0 [16];
  undefined8 uStack_3a0;
  undefined4 uStack_398;
  undefined4 uStack_394;
  undefined1 auStack_390 [16];
  undefined1 auStack_380 [16];
  undefined8 uStack_370;
  undefined4 uStack_368;
  undefined4 uStack_364;
  undefined1 auStack_360 [16];
  undefined1 auStack_350 [16];
  undefined8 uStack_340;
  undefined4 uStack_338;
  undefined4 uStack_334;
  undefined1 auStack_330 [16];
  undefined1 auStack_320 [16];
  undefined8 uStack_310;
  undefined4 uStack_308;
  undefined4 uStack_304;
  undefined1 auStack_300 [16];
  undefined1 auStack_2f0 [16];
  undefined8 uStack_2e0;
  undefined4 uStack_2d8;
  undefined4 uStack_2d4;
  undefined1 auStack_2d0 [16];
  undefined1 auStack_2c0 [16];
  undefined8 uStack_2b0;
  undefined4 uStack_2a8;
  undefined4 uStack_2a4;
  undefined1 auStack_2a0 [16];
  undefined1 auStack_290 [16];
  undefined8 uStack_280;
  undefined4 uStack_278;
  undefined4 uStack_274;
  undefined1 auStack_270 [16];
  undefined1 auStack_260 [16];
  undefined8 uStack_250;
  undefined4 uStack_248;
  undefined4 uStack_244;
  undefined4 auStack_240 [7];
  undefined4 uStack_224;
  undefined4 auStack_1c0 [7];
  undefined4 uStack_1a4;
  undefined1 auStack_140 [64];
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
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [16];
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined1 auStack_10 [8];
  undefined1 auStack_8 [8];
  
  auStack_40._4_4_ = in_zero_hi;
  auStack_40._0_4_ = in_zero_lo;
  auStack_40._8_4_ = in_zero_udw;
  auStack_40._12_4_ = in_register_0000000c;
  auStack_30._4_4_ = in_zero_hi;
  auStack_30._0_4_ = in_zero_lo;
  auStack_30._8_4_ = in_zero_udw;
  auStack_30._12_4_ = in_register_0000000c;
  auVar82 = _vmr32(in_vf0);
  auVar83 = _vmr32(auVar82);
  auVar84 = _vmr32(auVar83);
  auStack_d0 = _sqc2(in_vf0);
  auStack_e0 = _sqc2(auVar82);
  auStack_f0 = _sqc2(auVar83);
  auStack_100 = _sqc2(auVar84);
  fVar81 = *(float *)(iGpffff86b4 + 0x38);
  if ((*(byte *)(iGpffff86b4 + 0x24) & 1) != 0) {
    fVar81 = 0.0;
  }
  if ((fVar81 != 0.0) &&
     (pbVar80 = (byte *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x144) +
                                 0xe4) + *(int *)(param_1 + 0x98c) * 0x110), pbVar80 != (byte *)0x0)
     ) {
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
    __ct__6MatrixFRC6Matrix(auStack_140,
                    *(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x144) + 0x30
                            ) + (uint)*pbVar80 * 0x1f0 + (bGpffff8340 & 1) * 0x40);
    RotTransVector(&uStack_c0,pbVar80 + 0x10,auStack_140,8);
    iVar79 = *(int *)(param_1 + 0x994);
    if (iVar79 == 0x31) {
      auVar84._4_4_ = uStack_5c;
      auVar84._0_4_ = uStack_60;
      auVar84._8_4_ = uStack_58;
      auVar84._12_4_ = uStack_54;
      auVar82 = _lqc2(auVar84);
      auVar72._4_4_ = uStack_4c;
      auVar72._0_4_ = uStack_50;
      auVar72._8_4_ = uStack_48;
      auVar72._12_4_ = uStack_44;
      auVar83 = _lqc2(auVar72);
      auVar82 = _vadd(auVar82,auVar83);
      auStack_6f0 = _sqc2(auVar82);
      __ct__7FVectorFRC7FVector(&uStack_510,auStack_6f0);
      auStack_40._8_4_ = uStack_508;
      auStack_40._0_8_ = uStack_510;
      auStack_40._12_4_ = uStack_504;
      auVar82._4_4_ = uStack_7c;
      auVar82._0_4_ = uStack_80;
      auVar82._8_4_ = uStack_78;
      auVar82._12_4_ = uStack_74;
      auVar82 = _lqc2(auVar82);
      auVar83._4_4_ = uStack_6c;
      auVar83._0_4_ = uStack_70;
      auVar83._8_4_ = uStack_68;
      auVar83._12_4_ = uStack_64;
      auVar83 = _lqc2(auVar83);
      auVar82 = _vadd(auVar82,auVar83);
      auStack_700 = _sqc2(auVar82);
      __ct__7FVectorFRC7FVector(&uStack_520,auStack_700);
      auStack_30._8_4_ = uStack_518;
      auStack_30._0_8_ = uStack_520;
      auStack_30._12_4_ = uStack_514;
      __adv__7FVectorFf(0x40000000,auStack_40);
      __adv__7FVectorFf(0x40000000,auStack_30);
      auVar83 = _lqc2(auStack_30);
      auVar82 = _lqc2(auStack_40);
      auVar82 = _vsub(auVar82,auVar83);
      auStack_40 = _sqc2(auVar82);
      __amu__7FVectorFf(0x3f4ccccd,auStack_40);
      auVar83 = _lqc2(auStack_30);
      auVar82 = _lqc2(auStack_40);
      auVar82 = _vadd(auVar82,auVar83);
      auStack_40 = _sqc2(auVar82);
    }
    else if (iVar79 == 9) {
      auVar39._4_4_ = uStack_8c;
      auVar39._0_4_ = uStack_90;
      auVar39._8_4_ = uStack_88;
      auVar39._12_4_ = uStack_84;
      auVar82 = _lqc2(auVar39);
      auVar57._4_4_ = uStack_6c;
      auVar57._0_4_ = uStack_70;
      auVar57._8_4_ = uStack_68;
      auVar57._12_4_ = uStack_64;
      auVar83 = _lqc2(auVar57);
      auVar82 = _vadd(auVar82,auVar83);
      auStack_6d0 = _sqc2(auVar82);
      __ct__7FVectorFRC7FVector(&uStack_4f0,auStack_6d0);
      auStack_40._8_4_ = uStack_4e8;
      auStack_40._0_8_ = uStack_4f0;
      auStack_40._12_4_ = uStack_4e4;
      auVar17._4_4_ = uStack_bc;
      auVar17._0_4_ = uStack_c0;
      auVar17._8_4_ = uStack_b8;
      auVar17._12_4_ = uStack_b4;
      auVar82 = _lqc2(auVar17);
      auVar65._4_4_ = uStack_5c;
      auVar65._0_4_ = uStack_60;
      auVar65._8_4_ = uStack_58;
      auVar65._12_4_ = uStack_54;
      auVar83 = _lqc2(auVar65);
      auVar82 = _vadd(auVar82,auVar83);
      auStack_6e0 = _sqc2(auVar82);
      __ct__7FVectorFRC7FVector(&uStack_500,auStack_6e0);
      auStack_30._8_4_ = uStack_4f8;
      auStack_30._0_8_ = uStack_500;
      auStack_30._12_4_ = uStack_4f4;
      __adv__7FVectorFf(0x40000000,auStack_40);
      __adv__7FVectorFf(0x40000000,auStack_30);
      auVar83 = _lqc2(auStack_30);
      auVar82 = _lqc2(auStack_40);
      auVar82 = _vsub(auVar82,auVar83);
      auStack_40 = _sqc2(auVar82);
      __amu__7FVectorFf(0x3f4ccccd,auStack_40);
      auVar83 = _lqc2(auStack_30);
      auVar82 = _lqc2(auStack_40);
      auVar82 = _vadd(auVar82,auVar83);
      auStack_40 = _sqc2(auVar82);
    }
    else if (iVar79 == 8) {
      auVar16._4_4_ = uStack_bc;
      auVar16._0_4_ = uStack_c0;
      auVar16._8_4_ = uStack_b8;
      auVar16._12_4_ = uStack_b4;
      auVar82 = _lqc2(auVar16);
      auVar64._4_4_ = uStack_5c;
      auVar64._0_4_ = uStack_60;
      auVar64._8_4_ = uStack_58;
      auVar64._12_4_ = uStack_54;
      auVar83 = _lqc2(auVar64);
      auVar82 = _vadd(auVar82,auVar83);
      auStack_6b0 = _sqc2(auVar82);
      __ct__7FVectorFRC7FVector(&uStack_4d0,auStack_6b0);
      auStack_40._8_4_ = uStack_4c8;
      auStack_40._0_8_ = uStack_4d0;
      auStack_40._12_4_ = uStack_4c4;
      auVar38._4_4_ = uStack_8c;
      auVar38._0_4_ = uStack_90;
      auVar38._8_4_ = uStack_88;
      auVar38._12_4_ = uStack_84;
      auVar82 = _lqc2(auVar38);
      auVar56._4_4_ = uStack_6c;
      auVar56._0_4_ = uStack_70;
      auVar56._8_4_ = uStack_68;
      auVar56._12_4_ = uStack_64;
      auVar83 = _lqc2(auVar56);
      auVar82 = _vadd(auVar82,auVar83);
      auStack_6c0 = _sqc2(auVar82);
      __ct__7FVectorFRC7FVector(&uStack_4e0,auStack_6c0);
      auStack_30._8_4_ = uStack_4d8;
      auStack_30._0_8_ = uStack_4e0;
      auStack_30._12_4_ = uStack_4d4;
      __adv__7FVectorFf(0x40000000,auStack_40);
      __adv__7FVectorFf(0x40000000,auStack_30);
      auVar83 = _lqc2(auStack_30);
      auVar82 = _lqc2(auStack_40);
      auVar82 = _vsub(auVar82,auVar83);
      auStack_40 = _sqc2(auVar82);
      __amu__7FVectorFf(0x3f4ccccd,auStack_40);
      auVar83 = _lqc2(auStack_30);
      auVar82 = _lqc2(auStack_40);
      auVar82 = _vadd(auVar82,auVar83);
      auStack_40 = _sqc2(auVar82);
    }
    else if (iVar79 == 7) {
      auVar47._4_4_ = uStack_7c;
      auVar47._0_4_ = uStack_80;
      auVar47._8_4_ = uStack_78;
      auVar47._12_4_ = uStack_74;
      auVar82 = _lqc2(auVar47);
      auVar55._4_4_ = uStack_6c;
      auVar55._0_4_ = uStack_70;
      auVar55._8_4_ = uStack_68;
      auVar55._12_4_ = uStack_64;
      auVar83 = _lqc2(auVar55);
      auVar82 = _vadd(auVar82,auVar83);
      auStack_690 = _sqc2(auVar82);
      __ct__7FVectorFRC7FVector(&uStack_4b0,auStack_690);
      auStack_40._8_4_ = uStack_4a8;
      auStack_40._0_8_ = uStack_4b0;
      auStack_40._12_4_ = uStack_4a4;
      auVar15._4_4_ = uStack_bc;
      auVar15._0_4_ = uStack_c0;
      auVar15._8_4_ = uStack_b8;
      auVar15._12_4_ = uStack_b4;
      auVar82 = _lqc2(auVar15);
      auVar25._4_4_ = uStack_ac;
      auVar25._0_4_ = uStack_b0;
      auVar25._8_4_ = uStack_a8;
      auVar25._12_4_ = uStack_a4;
      auVar83 = _lqc2(auVar25);
      auVar82 = _vadd(auVar82,auVar83);
      auStack_6a0 = _sqc2(auVar82);
      __ct__7FVectorFRC7FVector(&uStack_4c0,auStack_6a0);
      auStack_30._8_4_ = uStack_4b8;
      auStack_30._0_8_ = uStack_4c0;
      auStack_30._12_4_ = uStack_4b4;
      __adv__7FVectorFf(0x40000000,auStack_40);
      __adv__7FVectorFf(0x40000000,auStack_30);
      auVar83 = _lqc2(auStack_30);
      auVar82 = _lqc2(auStack_40);
      auVar82 = _vsub(auVar82,auVar83);
      auStack_40 = _sqc2(auVar82);
      __amu__7FVectorFf(0x3f4ccccd,auStack_40);
      auVar83 = _lqc2(auStack_30);
      auVar82 = _lqc2(auStack_40);
      auVar82 = _vadd(auVar82,auVar83);
      auStack_40 = _sqc2(auVar82);
    }
    else if (iVar79 == 6) {
      auVar14._4_4_ = uStack_bc;
      auVar14._0_4_ = uStack_c0;
      auVar14._8_4_ = uStack_b8;
      auVar14._12_4_ = uStack_b4;
      auVar82 = _lqc2(auVar14);
      auVar24._4_4_ = uStack_ac;
      auVar24._0_4_ = uStack_b0;
      auVar24._8_4_ = uStack_a8;
      auVar24._12_4_ = uStack_a4;
      auVar83 = _lqc2(auVar24);
      auVar82 = _vadd(auVar82,auVar83);
      auStack_670 = _sqc2(auVar82);
      __ct__7FVectorFRC7FVector(&uStack_490,auStack_670);
      auStack_40._8_4_ = uStack_488;
      auStack_40._0_8_ = uStack_490;
      auStack_40._12_4_ = uStack_484;
      auVar46._4_4_ = uStack_7c;
      auVar46._0_4_ = uStack_80;
      auVar46._8_4_ = uStack_78;
      auVar46._12_4_ = uStack_74;
      auVar82 = _lqc2(auVar46);
      auVar54._4_4_ = uStack_6c;
      auVar54._0_4_ = uStack_70;
      auVar54._8_4_ = uStack_68;
      auVar54._12_4_ = uStack_64;
      auVar83 = _lqc2(auVar54);
      auVar82 = _vadd(auVar82,auVar83);
      auStack_680 = _sqc2(auVar82);
      __ct__7FVectorFRC7FVector(&uStack_4a0,auStack_680);
      auStack_30._8_4_ = uStack_498;
      auStack_30._0_8_ = uStack_4a0;
      auStack_30._12_4_ = uStack_494;
      __adv__7FVectorFf(0x40000000,auStack_40);
      __adv__7FVectorFf(0x40000000,auStack_30);
      auVar83 = _lqc2(auStack_40);
      auVar82 = _lqc2(auStack_30);
      auVar82 = _vsub(auVar82,auVar83);
      auStack_30 = _sqc2(auVar82);
      __amu__7FVectorFf(0x3f4ccccd,auStack_30);
      auVar83 = _lqc2(auStack_40);
      auVar82 = _lqc2(auStack_30);
      auVar82 = _vadd(auVar82,auVar83);
      auStack_30 = _sqc2(auVar82);
    }
    else if (iVar79 == 5) {
      auVar31._4_4_ = uStack_9c;
      auVar31._0_4_ = uStack_a0;
      auVar31._8_4_ = uStack_98;
      auVar31._12_4_ = uStack_94;
      auVar82 = _lqc2(auVar31);
      auVar37._4_4_ = uStack_8c;
      auVar37._0_4_ = uStack_90;
      auVar37._8_4_ = uStack_88;
      auVar37._12_4_ = uStack_84;
      auVar83 = _lqc2(auVar37);
      auVar82 = _vadd(auVar82,auVar83);
      auStack_890 = _sqc2(auVar82);
      __ct__7FVectorFRC7FVector(auStack_450,auStack_890);
      auVar82 = _lqc2(auStack_450);
      auVar45._4_4_ = uStack_7c;
      auVar45._0_4_ = uStack_80;
      auVar45._8_4_ = uStack_78;
      auVar45._12_4_ = uStack_74;
      auVar83 = _lqc2(auVar45);
      auVar82 = _vadd(auVar82,auVar83);
      auStack_8a0 = _sqc2(auVar82);
      __ct__7FVectorFRC7FVector(auStack_440,auStack_8a0);
      auVar82 = _lqc2(auStack_440);
      auVar53._4_4_ = uStack_6c;
      auVar53._0_4_ = uStack_70;
      auVar53._8_4_ = uStack_68;
      auVar53._12_4_ = uStack_64;
      auVar83 = _lqc2(auVar53);
      auVar82 = _vadd(auVar82,auVar83);
      auStack_650 = _sqc2(auVar82);
      __ct__7FVectorFRC7FVector(&uStack_430,auStack_650);
      auStack_40._8_4_ = uStack_428;
      auStack_40._0_8_ = uStack_430;
      auStack_40._12_4_ = uStack_424;
      auVar13._4_4_ = uStack_bc;
      auVar13._0_4_ = uStack_c0;
      auVar13._8_4_ = uStack_b8;
      auVar13._12_4_ = uStack_b4;
      auVar82 = _lqc2(auVar13);
      auVar23._4_4_ = uStack_ac;
      auVar23._0_4_ = uStack_b0;
      auVar23._8_4_ = uStack_a8;
      auVar23._12_4_ = uStack_a4;
      auVar83 = _lqc2(auVar23);
      auVar82 = _vadd(auVar82,auVar83);
      auStack_8b0 = _sqc2(auVar82);
      __ct__7FVectorFRC7FVector(auStack_480,auStack_8b0);
      auVar82 = _lqc2(auStack_480);
      auVar63._4_4_ = uStack_5c;
      auVar63._0_4_ = uStack_60;
      auVar63._8_4_ = uStack_58;
      auVar63._12_4_ = uStack_54;
      auVar83 = _lqc2(auVar63);
      auVar82 = _vadd(auVar82,auVar83);
      auStack_8c0 = _sqc2(auVar82);
      __ct__7FVectorFRC7FVector(auStack_470,auStack_8c0);
      auVar82 = _lqc2(auStack_470);
      auVar71._4_4_ = uStack_4c;
      auVar71._0_4_ = uStack_50;
      auVar71._8_4_ = uStack_48;
      auVar71._12_4_ = uStack_44;
      auVar83 = _lqc2(auVar71);
      auVar82 = _vadd(auVar82,auVar83);
      auStack_660 = _sqc2(auVar82);
      __ct__7FVectorFRC7FVector(&uStack_460,auStack_660);
      auStack_30._8_4_ = uStack_458;
      auStack_30._0_8_ = uStack_460;
      auStack_30._12_4_ = uStack_454;
      __adv__7FVectorFf(0x40800000,auStack_40);
      __adv__7FVectorFf(0x40800000,auStack_30);
      auVar83 = _lqc2(auStack_40);
      auVar82 = _lqc2(auStack_30);
      auVar82 = _vsub(auVar82,auVar83);
      auStack_30 = _sqc2(auVar82);
      __amu__7FVectorFf(0x3f4ccccd,auStack_30);
      auVar83 = _lqc2(auStack_40);
      auVar82 = _lqc2(auStack_30);
      auVar82 = _vadd(auVar82,auVar83);
      auStack_30 = _sqc2(auVar82);
    }
    else if (iVar79 == 4) {
      auVar12._4_4_ = uStack_bc;
      auVar12._0_4_ = uStack_c0;
      auVar12._8_4_ = uStack_b8;
      auVar12._12_4_ = uStack_b4;
      auVar82 = _lqc2(auVar12);
      auVar22._4_4_ = uStack_ac;
      auVar22._0_4_ = uStack_b0;
      auVar22._8_4_ = uStack_a8;
      auVar22._12_4_ = uStack_a4;
      auVar83 = _lqc2(auVar22);
      auVar82 = _vadd(auVar82,auVar83);
      auStack_850 = _sqc2(auVar82);
      __ct__7FVectorFRC7FVector(auStack_3f0,auStack_850);
      auVar82 = _lqc2(auStack_3f0);
      auVar62._4_4_ = uStack_5c;
      auVar62._0_4_ = uStack_60;
      auVar62._8_4_ = uStack_58;
      auVar62._12_4_ = uStack_54;
      auVar83 = _lqc2(auVar62);
      auVar82 = _vadd(auVar82,auVar83);
      auStack_860 = _sqc2(auVar82);
      __ct__7FVectorFRC7FVector(auStack_3e0,auStack_860);
      auVar82 = _lqc2(auStack_3e0);
      auVar70._4_4_ = uStack_4c;
      auVar70._0_4_ = uStack_50;
      auVar70._8_4_ = uStack_48;
      auVar70._12_4_ = uStack_44;
      auVar83 = _lqc2(auVar70);
      auVar82 = _vadd(auVar82,auVar83);
      auStack_630 = _sqc2(auVar82);
      __ct__7FVectorFRC7FVector(&uStack_3d0,auStack_630);
      auStack_40._8_4_ = uStack_3c8;
      auStack_40._0_8_ = uStack_3d0;
      auStack_40._12_4_ = uStack_3c4;
      auVar30._4_4_ = uStack_9c;
      auVar30._0_4_ = uStack_a0;
      auVar30._8_4_ = uStack_98;
      auVar30._12_4_ = uStack_94;
      auVar82 = _lqc2(auVar30);
      auVar36._4_4_ = uStack_8c;
      auVar36._0_4_ = uStack_90;
      auVar36._8_4_ = uStack_88;
      auVar36._12_4_ = uStack_84;
      auVar83 = _lqc2(auVar36);
      auVar82 = _vadd(auVar82,auVar83);
      auStack_870 = _sqc2(auVar82);
      __ct__7FVectorFRC7FVector(auStack_420,auStack_870);
      auVar82 = _lqc2(auStack_420);
      auVar44._4_4_ = uStack_7c;
      auVar44._0_4_ = uStack_80;
      auVar44._8_4_ = uStack_78;
      auVar44._12_4_ = uStack_74;
      auVar83 = _lqc2(auVar44);
      auVar82 = _vadd(auVar82,auVar83);
      auStack_880 = _sqc2(auVar82);
      __ct__7FVectorFRC7FVector(auStack_410,auStack_880);
      auVar82 = _lqc2(auStack_410);
      auVar52._4_4_ = uStack_6c;
      auVar52._0_4_ = uStack_70;
      auVar52._8_4_ = uStack_68;
      auVar52._12_4_ = uStack_64;
      auVar83 = _lqc2(auVar52);
      auVar82 = _vadd(auVar82,auVar83);
      auStack_640 = _sqc2(auVar82);
      __ct__7FVectorFRC7FVector(&uStack_400,auStack_640);
      auStack_30._8_4_ = uStack_3f8;
      auStack_30._0_8_ = uStack_400;
      auStack_30._12_4_ = uStack_3f4;
      __adv__7FVectorFf(0x40800000,auStack_40);
      __adv__7FVectorFf(0x40800000,auStack_30);
      auVar83 = _lqc2(auStack_40);
      auVar82 = _lqc2(auStack_30);
      auVar82 = _vsub(auVar82,auVar83);
      auStack_30 = _sqc2(auVar82);
      __amu__7FVectorFf(0x3f4ccccd,auStack_30);
      auVar83 = _lqc2(auStack_40);
      auVar82 = _lqc2(auStack_30);
      auVar82 = _vadd(auVar82,auVar83);
      auStack_30 = _sqc2(auVar82);
    }
    else if (iVar79 == 3) {
      auVar21._4_4_ = uStack_ac;
      auVar21._0_4_ = uStack_b0;
      auVar21._8_4_ = uStack_a8;
      auVar21._12_4_ = uStack_a4;
      auVar82 = _lqc2(auVar21);
      auVar35._4_4_ = uStack_8c;
      auVar35._0_4_ = uStack_90;
      auVar35._8_4_ = uStack_88;
      auVar35._12_4_ = uStack_84;
      auVar83 = _lqc2(auVar35);
      auVar82 = _vadd(auVar82,auVar83);
      auStack_810 = _sqc2(auVar82);
      __ct__7FVectorFRC7FVector(auStack_390,auStack_810);
      auVar82 = _lqc2(auStack_390);
      auVar51._4_4_ = uStack_6c;
      auVar51._0_4_ = uStack_70;
      auVar51._8_4_ = uStack_68;
      auVar51._12_4_ = uStack_64;
      auVar83 = _lqc2(auVar51);
      auVar82 = _vadd(auVar82,auVar83);
      auStack_820 = _sqc2(auVar82);
      __ct__7FVectorFRC7FVector(auStack_380,auStack_820);
      auVar82 = _lqc2(auStack_380);
      auVar69._4_4_ = uStack_4c;
      auVar69._0_4_ = uStack_50;
      auVar69._8_4_ = uStack_48;
      auVar69._12_4_ = uStack_44;
      auVar83 = _lqc2(auVar69);
      auVar82 = _vadd(auVar82,auVar83);
      auStack_610 = _sqc2(auVar82);
      __ct__7FVectorFRC7FVector(&uStack_370,auStack_610);
      auStack_40._8_4_ = uStack_368;
      auStack_40._0_8_ = uStack_370;
      auStack_40._12_4_ = uStack_364;
      auVar11._4_4_ = uStack_bc;
      auVar11._0_4_ = uStack_c0;
      auVar11._8_4_ = uStack_b8;
      auVar11._12_4_ = uStack_b4;
      auVar82 = _lqc2(auVar11);
      auVar29._4_4_ = uStack_9c;
      auVar29._0_4_ = uStack_a0;
      auVar29._8_4_ = uStack_98;
      auVar29._12_4_ = uStack_94;
      auVar83 = _lqc2(auVar29);
      auVar82 = _vadd(auVar82,auVar83);
      auStack_830 = _sqc2(auVar82);
      __ct__7FVectorFRC7FVector(auStack_3c0,auStack_830);
      auVar82 = _lqc2(auStack_3c0);
      auVar43._4_4_ = uStack_7c;
      auVar43._0_4_ = uStack_80;
      auVar43._8_4_ = uStack_78;
      auVar43._12_4_ = uStack_74;
      auVar83 = _lqc2(auVar43);
      auVar82 = _vadd(auVar82,auVar83);
      auStack_840 = _sqc2(auVar82);
      __ct__7FVectorFRC7FVector(auStack_3b0,auStack_840);
      auVar82 = _lqc2(auStack_3b0);
      auVar61._4_4_ = uStack_5c;
      auVar61._0_4_ = uStack_60;
      auVar61._8_4_ = uStack_58;
      auVar61._12_4_ = uStack_54;
      auVar83 = _lqc2(auVar61);
      auVar82 = _vadd(auVar82,auVar83);
      auStack_620 = _sqc2(auVar82);
      __ct__7FVectorFRC7FVector(&uStack_3a0,auStack_620);
      auStack_30._8_4_ = uStack_398;
      auStack_30._0_8_ = uStack_3a0;
      auStack_30._12_4_ = uStack_394;
      __adv__7FVectorFf(0x40800000,auStack_40);
      __adv__7FVectorFf(0x40800000,auStack_30);
      auVar83 = _lqc2(auStack_40);
      auVar82 = _lqc2(auStack_30);
      auVar82 = _vsub(auVar82,auVar83);
      auStack_30 = _sqc2(auVar82);
      __amu__7FVectorFf(0x3f4ccccd,auStack_30);
      auVar83 = _lqc2(auStack_40);
      auVar82 = _lqc2(auStack_30);
      auVar82 = _vadd(auVar82,auVar83);
      auStack_30 = _sqc2(auVar82);
    }
    else if (iVar79 == 2) {
      auVar10._4_4_ = uStack_bc;
      auVar10._0_4_ = uStack_c0;
      auVar10._8_4_ = uStack_b8;
      auVar10._12_4_ = uStack_b4;
      auVar82 = _lqc2(auVar10);
      auVar28._4_4_ = uStack_9c;
      auVar28._0_4_ = uStack_a0;
      auVar28._8_4_ = uStack_98;
      auVar28._12_4_ = uStack_94;
      auVar83 = _lqc2(auVar28);
      auVar82 = _vadd(auVar82,auVar83);
      auStack_7d0 = _sqc2(auVar82);
      __ct__7FVectorFRC7FVector(auStack_330,auStack_7d0);
      auVar82 = _lqc2(auStack_330);
      auVar42._4_4_ = uStack_7c;
      auVar42._0_4_ = uStack_80;
      auVar42._8_4_ = uStack_78;
      auVar42._12_4_ = uStack_74;
      auVar83 = _lqc2(auVar42);
      auVar82 = _vadd(auVar82,auVar83);
      auStack_7e0 = _sqc2(auVar82);
      __ct__7FVectorFRC7FVector(auStack_320,auStack_7e0);
      auVar82 = _lqc2(auStack_320);
      auVar60._4_4_ = uStack_5c;
      auVar60._0_4_ = uStack_60;
      auVar60._8_4_ = uStack_58;
      auVar60._12_4_ = uStack_54;
      auVar83 = _lqc2(auVar60);
      auVar82 = _vadd(auVar82,auVar83);
      auStack_5f0 = _sqc2(auVar82);
      __ct__7FVectorFRC7FVector(&uStack_310,auStack_5f0);
      auStack_40._8_4_ = uStack_308;
      auStack_40._0_8_ = uStack_310;
      auStack_40._12_4_ = uStack_304;
      auVar20._4_4_ = uStack_ac;
      auVar20._0_4_ = uStack_b0;
      auVar20._8_4_ = uStack_a8;
      auVar20._12_4_ = uStack_a4;
      auVar82 = _lqc2(auVar20);
      auVar34._4_4_ = uStack_8c;
      auVar34._0_4_ = uStack_90;
      auVar34._8_4_ = uStack_88;
      auVar34._12_4_ = uStack_84;
      auVar83 = _lqc2(auVar34);
      auVar82 = _vadd(auVar82,auVar83);
      auStack_7f0 = _sqc2(auVar82);
      __ct__7FVectorFRC7FVector(auStack_360,auStack_7f0);
      auVar82 = _lqc2(auStack_360);
      auVar50._4_4_ = uStack_6c;
      auVar50._0_4_ = uStack_70;
      auVar50._8_4_ = uStack_68;
      auVar50._12_4_ = uStack_64;
      auVar83 = _lqc2(auVar50);
      auVar82 = _vadd(auVar82,auVar83);
      auStack_800 = _sqc2(auVar82);
      __ct__7FVectorFRC7FVector(auStack_350,auStack_800);
      auVar82 = _lqc2(auStack_350);
      auVar68._4_4_ = uStack_4c;
      auVar68._0_4_ = uStack_50;
      auVar68._8_4_ = uStack_48;
      auVar68._12_4_ = uStack_44;
      auVar83 = _lqc2(auVar68);
      auVar82 = _vadd(auVar82,auVar83);
      auStack_600 = _sqc2(auVar82);
      __ct__7FVectorFRC7FVector(&uStack_340,auStack_600);
      auStack_30._8_4_ = uStack_338;
      auStack_30._0_8_ = uStack_340;
      auStack_30._12_4_ = uStack_334;
      __adv__7FVectorFf(0x40800000,auStack_40);
      __adv__7FVectorFf(0x40800000,auStack_30);
      auVar83 = _lqc2(auStack_40);
      auVar82 = _lqc2(auStack_30);
      auVar82 = _vsub(auVar82,auVar83);
      auStack_30 = _sqc2(auVar82);
      __amu__7FVectorFf(0x3f4ccccd,auStack_30);
      auVar83 = _lqc2(auStack_40);
      auVar82 = _lqc2(auStack_30);
      auVar82 = _vadd(auVar82,auVar83);
      auStack_30 = _sqc2(auVar82);
    }
    else if (iVar79 == 1) {
      auVar41._4_4_ = uStack_7c;
      auVar41._0_4_ = uStack_80;
      auVar41._8_4_ = uStack_78;
      auVar41._12_4_ = uStack_74;
      auVar82 = _lqc2(auVar41);
      auVar49._4_4_ = uStack_6c;
      auVar49._0_4_ = uStack_70;
      auVar49._8_4_ = uStack_68;
      auVar49._12_4_ = uStack_64;
      auVar83 = _lqc2(auVar49);
      auVar82 = _vadd(auVar82,auVar83);
      auStack_790 = _sqc2(auVar82);
      __ct__7FVectorFRC7FVector(auStack_2d0,auStack_790);
      auVar82 = _lqc2(auStack_2d0);
      auVar59._4_4_ = uStack_5c;
      auVar59._0_4_ = uStack_60;
      auVar59._8_4_ = uStack_58;
      auVar59._12_4_ = uStack_54;
      auVar83 = _lqc2(auVar59);
      auVar82 = _vadd(auVar82,auVar83);
      auStack_7a0 = _sqc2(auVar82);
      __ct__7FVectorFRC7FVector(auStack_2c0,auStack_7a0);
      auVar82 = _lqc2(auStack_2c0);
      auVar67._4_4_ = uStack_4c;
      auVar67._0_4_ = uStack_50;
      auVar67._8_4_ = uStack_48;
      auVar67._12_4_ = uStack_44;
      auVar83 = _lqc2(auVar67);
      auVar82 = _vadd(auVar82,auVar83);
      auStack_5d0 = _sqc2(auVar82);
      __ct__7FVectorFRC7FVector(&uStack_2b0,auStack_5d0);
      auStack_40._8_4_ = uStack_2a8;
      auStack_40._0_8_ = uStack_2b0;
      auStack_40._12_4_ = uStack_2a4;
      auVar9._4_4_ = uStack_bc;
      auVar9._0_4_ = uStack_c0;
      auVar9._8_4_ = uStack_b8;
      auVar9._12_4_ = uStack_b4;
      auVar82 = _lqc2(auVar9);
      auVar19._4_4_ = uStack_ac;
      auVar19._0_4_ = uStack_b0;
      auVar19._8_4_ = uStack_a8;
      auVar19._12_4_ = uStack_a4;
      auVar83 = _lqc2(auVar19);
      auVar82 = _vadd(auVar82,auVar83);
      auStack_7b0 = _sqc2(auVar82);
      __ct__7FVectorFRC7FVector(auStack_300,auStack_7b0);
      auVar82 = _lqc2(auStack_300);
      auVar27._4_4_ = uStack_9c;
      auVar27._0_4_ = uStack_a0;
      auVar27._8_4_ = uStack_98;
      auVar27._12_4_ = uStack_94;
      auVar83 = _lqc2(auVar27);
      auVar82 = _vadd(auVar82,auVar83);
      auStack_7c0 = _sqc2(auVar82);
      __ct__7FVectorFRC7FVector(auStack_2f0,auStack_7c0);
      auVar82 = _lqc2(auStack_2f0);
      auVar33._4_4_ = uStack_8c;
      auVar33._0_4_ = uStack_90;
      auVar33._8_4_ = uStack_88;
      auVar33._12_4_ = uStack_84;
      auVar83 = _lqc2(auVar33);
      auVar82 = _vadd(auVar82,auVar83);
      auStack_5e0 = _sqc2(auVar82);
      __ct__7FVectorFRC7FVector(&uStack_2e0,auStack_5e0);
      auStack_30._8_4_ = uStack_2d8;
      auStack_30._0_8_ = uStack_2e0;
      auStack_30._12_4_ = uStack_2d4;
      __adv__7FVectorFf(0x40800000,auStack_40);
      __adv__7FVectorFf(0x40800000,auStack_30);
      auVar83 = _lqc2(auStack_40);
      auVar82 = _lqc2(auStack_30);
      auVar82 = _vsub(auVar82,auVar83);
      auStack_30 = _sqc2(auVar82);
      __amu__7FVectorFf(0x3f4ccccd,auStack_30);
      auVar83 = _lqc2(auStack_40);
      auVar82 = _lqc2(auStack_30);
      auVar82 = _vadd(auVar82,auVar83);
      auStack_30 = _sqc2(auVar82);
    }
    else if (iVar79 == 0) {
      auVar8._4_4_ = uStack_bc;
      auVar8._0_4_ = uStack_c0;
      auVar8._8_4_ = uStack_b8;
      auVar8._12_4_ = uStack_b4;
      auVar82 = _lqc2(auVar8);
      auVar18._4_4_ = uStack_ac;
      auVar18._0_4_ = uStack_b0;
      auVar18._8_4_ = uStack_a8;
      auVar18._12_4_ = uStack_a4;
      auVar83 = _lqc2(auVar18);
      auVar82 = _vadd(auVar82,auVar83);
      auStack_750 = _sqc2(auVar82);
      __ct__7FVectorFRC7FVector(auStack_270,auStack_750);
      auVar82 = _lqc2(auStack_270);
      auVar26._4_4_ = uStack_9c;
      auVar26._0_4_ = uStack_a0;
      auVar26._8_4_ = uStack_98;
      auVar26._12_4_ = uStack_94;
      auVar83 = _lqc2(auVar26);
      auVar82 = _vadd(auVar82,auVar83);
      auStack_760 = _sqc2(auVar82);
      __ct__7FVectorFRC7FVector(auStack_260,auStack_760);
      auVar82 = _lqc2(auStack_260);
      auVar32._4_4_ = uStack_8c;
      auVar32._0_4_ = uStack_90;
      auVar32._8_4_ = uStack_88;
      auVar32._12_4_ = uStack_84;
      auVar83 = _lqc2(auVar32);
      auVar82 = _vadd(auVar82,auVar83);
      auStack_5b0 = _sqc2(auVar82);
      __ct__7FVectorFRC7FVector(&uStack_250,auStack_5b0);
      auStack_40._8_4_ = uStack_248;
      auStack_40._0_8_ = uStack_250;
      auStack_40._12_4_ = uStack_244;
      auVar40._4_4_ = uStack_7c;
      auVar40._0_4_ = uStack_80;
      auVar40._8_4_ = uStack_78;
      auVar40._12_4_ = uStack_74;
      auVar82 = _lqc2(auVar40);
      auVar48._4_4_ = uStack_6c;
      auVar48._0_4_ = uStack_70;
      auVar48._8_4_ = uStack_68;
      auVar48._12_4_ = uStack_64;
      auVar83 = _lqc2(auVar48);
      auVar82 = _vadd(auVar82,auVar83);
      auStack_770 = _sqc2(auVar82);
      __ct__7FVectorFRC7FVector(auStack_2a0,auStack_770);
      auVar82 = _lqc2(auStack_2a0);
      auVar58._4_4_ = uStack_5c;
      auVar58._0_4_ = uStack_60;
      auVar58._8_4_ = uStack_58;
      auVar58._12_4_ = uStack_54;
      auVar83 = _lqc2(auVar58);
      auVar82 = _vadd(auVar82,auVar83);
      auStack_780 = _sqc2(auVar82);
      __ct__7FVectorFRC7FVector(auStack_290,auStack_780);
      auVar82 = _lqc2(auStack_290);
      auVar66._4_4_ = uStack_4c;
      auVar66._0_4_ = uStack_50;
      auVar66._8_4_ = uStack_48;
      auVar66._12_4_ = uStack_44;
      auVar83 = _lqc2(auVar66);
      auVar82 = _vadd(auVar82,auVar83);
      auStack_5c0 = _sqc2(auVar82);
      __ct__7FVectorFRC7FVector(&uStack_280,auStack_5c0);
      auStack_30._8_4_ = uStack_278;
      auStack_30._0_8_ = uStack_280;
      auStack_30._12_4_ = uStack_274;
      __adv__7FVectorFf(0x40800000,auStack_40);
      __adv__7FVectorFf(0x40800000,auStack_30);
      auVar83 = _lqc2(auStack_40);
      auVar82 = _lqc2(auStack_30);
      auVar82 = _vsub(auVar82,auVar83);
      auStack_30 = _sqc2(auVar82);
      __amu__7FVectorFf(0x3f4ccccd,auStack_30);
      auVar83 = _lqc2(auStack_40);
      auVar82 = _lqc2(auStack_30);
      auVar82 = _vadd(auVar82,auVar83);
      auStack_30 = _sqc2(auVar82);
    }
    iVar79 = param_1 + *(int *)(param_1 + 0x6c) * 0x20;
    *(int *)(iVar79 + 0x80) = auStack_40._0_4_;
    *(int *)(iVar79 + 0x84) = auStack_40._4_4_;
    *(undefined4 *)(iVar79 + 0x88) = auStack_40._8_4_;
    *(undefined4 *)(iVar79 + 0x8c) = auStack_40._12_4_;
    iVar79 = param_1 + *(int *)(param_1 + 0x6c) * 0x20;
    *(int *)(iVar79 + 0x90) = auStack_30._0_4_;
    *(int *)(iVar79 + 0x94) = auStack_30._4_4_;
    *(undefined4 *)(iVar79 + 0x98) = auStack_30._8_4_;
    *(undefined4 *)(iVar79 + 0x9c) = auStack_30._12_4_;
    *(int *)(param_1 + 0x6c) = *(int *)(param_1 + 0x6c) + 1;
    if (7 < *(int *)(param_1 + 0x6c)) {
      *(undefined4 *)(param_1 + 0x6c) = 0;
    }
    *(int *)(param_1 + 0x68) = *(int *)(param_1 + 0x68) + 1;
    if (8 < *(int *)(param_1 + 0x68)) {
      *(undefined4 *)(param_1 + 0x68) = 8;
    }
  }
  iVar79 = *(int *)(param_1 + 0x6c);
  auStack_240[0] = in_zero_lo;
  auStack_240[1] = in_zero_hi;
  auStack_240[2] = in_zero_udw;
  auStack_240[3] = in_register_0000000c;
  auStack_240[4] = in_zero_lo;
  auStack_240[5] = in_zero_hi;
  auStack_240[6] = in_zero_udw;
  uStack_224 = in_register_0000000c;
  auStack_1c0[0] = in_zero_lo;
  auStack_1c0[1] = in_zero_hi;
  auStack_1c0[2] = in_zero_udw;
  auStack_1c0[3] = in_register_0000000c;
  auStack_1c0[4] = in_zero_lo;
  auStack_1c0[5] = in_zero_hi;
  auStack_1c0[6] = in_zero_udw;
  uStack_1a4 = in_register_0000000c;
  for (iVar75 = 0; iVar75 < *(int *)(param_1 + 0x68); iVar75 = iVar75 + 1) {
    iVar79 = iVar79 + -1;
    if (iVar79 < 0) {
      iVar79 = 7;
    }
    iVar76 = param_1 + iVar79 * 0x20;
    uVar1 = *(undefined8 *)(iVar76 + 0x80);
    uVar77 = *(undefined4 *)(iVar76 + 0x88);
    uVar78 = *(undefined4 *)(iVar76 + 0x8c);
    auStack_1c0[iVar75 * 4] = (int)uVar1;
    auStack_1c0[iVar75 * 4 + 1] = (int)((ulong)uVar1 >> 0x20);
    auStack_1c0[iVar75 * 4 + 2] = uVar77;
    auStack_1c0[iVar75 * 4 + 3] = uVar78;
    iVar76 = param_1 + iVar79 * 0x20;
    uVar1 = *(undefined8 *)(iVar76 + 0x90);
    uVar77 = *(undefined4 *)(iVar76 + 0x98);
    uVar78 = *(undefined4 *)(iVar76 + 0x9c);
    auStack_240[iVar75 * 4] = (int)uVar1;
    auStack_240[iVar75 * 4 + 1] = (int)((ulong)uVar1 >> 0x20);
    auStack_240[iVar75 * 4 + 2] = uVar77;
    auStack_240[iVar75 * 4 + 3] = uVar78;
  }
  if (*(int *)(param_1 + 0x5c) == 0) {
    iVar79 = (*(int *)(param_1 + 0x68) + -1) * 8 + 1;
    *(int *)(param_1 + 0x70) = iVar79;
  }
  else {
    *(float *)(param_1 + 0x988) = *(float *)(param_1 + 0x988) + fVar81;
    while ((1 < *(int *)(param_1 + 100) && (0.004166667 < *(float *)(param_1 + 0x988)))) {
      *(float *)(param_1 + 0x988) = *(float *)(param_1 + 0x988) - 0.004166667;
      *(int *)(param_1 + 100) = *(int *)(param_1 + 100) + -1;
    }
    if (*(int *)(param_1 + 100) < 2) {
      BtlEffRelease__7CBattleFiP6BtlEff(iGpffff86b4,*(undefined4 *)(param_1 + 0x48),param_1);
      if ((long)((ulong)*(byte *)(param_1 + 0x40) << 0x3e) < 0) {
        iVar79 = param_1;
        if (param_1 != 0) {
          iVar79 = param_1 + 0x18;
        }
        ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,iVar79);
      }
      *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfd;
      (**(code **)(*(int *)(param_1 + 0x34) + 0xc))();
      return 1;
    }
    iVar79 = (*(int *)(param_1 + 0x68) + -1) * 8 + 1;
    *(undefined4 *)(param_1 + 0x70) = *(undefined4 *)(param_1 + 100);
  }
  if (*(int *)(param_1 + 0x68) == 1) {
    *(undefined4 *)(param_1 + 0x180) = auStack_1c0[0];
    *(undefined4 *)(param_1 + 0x184) = auStack_1c0[1];
    *(undefined4 *)(param_1 + 0x188) = auStack_1c0[2];
    *(undefined4 *)(param_1 + 0x18c) = auStack_1c0[3];
    *(undefined4 *)(param_1 + 400) = auStack_240[0];
    *(undefined4 *)(param_1 + 0x194) = auStack_240[1];
    *(undefined4 *)(param_1 + 0x198) = auStack_240[2];
    *(undefined4 *)(param_1 + 0x19c) = auStack_240[3];
  }
  else if (*(int *)(param_1 + 0x68) == 2) {
    *(undefined4 *)(param_1 + 0x180) = auStack_1c0[0];
    *(undefined4 *)(param_1 + 0x184) = auStack_1c0[1];
    *(undefined4 *)(param_1 + 0x188) = auStack_1c0[2];
    *(undefined4 *)(param_1 + 0x18c) = auStack_1c0[3];
    *(undefined4 *)(param_1 + 400) = auStack_240[0];
    *(undefined4 *)(param_1 + 0x194) = auStack_240[1];
    *(undefined4 *)(param_1 + 0x198) = auStack_240[2];
    *(undefined4 *)(param_1 + 0x19c) = auStack_240[3];
    auVar4._4_4_ = auStack_1c0[1];
    auVar4._0_4_ = auStack_1c0[0];
    auVar4._8_4_ = auStack_1c0[2];
    auVar4._12_4_ = auStack_1c0[3];
    auVar82 = _lqc2(auVar4);
    auVar5._4_4_ = auStack_1c0[5];
    auVar5._0_4_ = auStack_1c0[4];
    auVar5._8_4_ = auStack_1c0[6];
    auVar5._12_4_ = uStack_1a4;
    auVar83 = _lqc2(auVar5);
    auVar82 = _vsub(auVar82,auVar83);
    auStack_710 = _sqc2(auVar82);
    __ct__7FVectorFRC7FVector(auStack_530,auStack_710);
    uStack_20 = auStack_530._0_4_;
    uStack_1c = auStack_530._4_4_;
    uStack_18 = uStack_528;
    uStack_14 = uStack_524;
    for (iVar79 = 1; iVar79 < 8; iVar79 = iVar79 + 1) {
      iVar75 = iVar79;
      if (iVar79 < 0) {
        iVar75 = iVar79 + 7;
      }
      auVar73._4_4_ = uStack_1c;
      auVar73._0_4_ = uStack_20;
      auVar73._8_4_ = uStack_18;
      auVar73._12_4_ = uStack_14;
      auVar82 = _lqc2(auVar73);
      auVar83 = _qmtc2((float)(iVar75 >> 3));
      auVar82 = _vmulbc(auVar82,auVar83);
      auStack_8d0 = _sqc2(auVar82);
      __ct__7FVectorFRC7FVector(auStack_550,auStack_8d0);
      auVar6._4_4_ = auStack_1c0[5];
      auVar6._0_4_ = auStack_1c0[4];
      auVar6._8_4_ = auStack_1c0[6];
      auVar6._12_4_ = uStack_1a4;
      auVar82 = _lqc2(auVar6);
      auVar83 = _lqc2(auStack_550);
      auVar82 = _vadd(auVar82,auVar83);
      auStack_720 = _sqc2(auVar82);
      __ct__7FVectorFRC7FVector(auStack_540,auStack_720);
      iVar75 = param_1 + iVar79 * 0x20;
      *(int *)(iVar75 + 0x180) = auStack_540._0_4_;
      *(int *)(iVar75 + 0x184) = auStack_540._4_4_;
      *(undefined4 *)(iVar75 + 0x188) = uStack_538;
      *(undefined4 *)(iVar75 + 0x18c) = uStack_534;
    }
    auVar2._4_4_ = auStack_240[1];
    auVar2._0_4_ = auStack_240[0];
    auVar2._8_4_ = auStack_240[2];
    auVar2._12_4_ = auStack_240[3];
    auVar82 = _lqc2(auVar2);
    auVar3._4_4_ = auStack_240[5];
    auVar3._0_4_ = auStack_240[4];
    auVar3._8_4_ = auStack_240[6];
    auVar3._12_4_ = uStack_224;
    auVar83 = _lqc2(auVar3);
    auVar82 = _vsub(auVar82,auVar83);
    auStack_730 = _sqc2(auVar82);
    __ct__7FVectorFRC7FVector(auStack_560,auStack_730);
    uStack_20 = auStack_560._0_4_;
    uStack_1c = auStack_560._4_4_;
    uStack_18 = uStack_558;
    uStack_14 = uStack_554;
    for (iVar79 = 1; iVar79 < 8; iVar79 = iVar79 + 1) {
      iVar75 = iVar79;
      if (iVar79 < 0) {
        iVar75 = iVar79 + 7;
      }
      auVar74._4_4_ = uStack_1c;
      auVar74._0_4_ = uStack_20;
      auVar74._8_4_ = uStack_18;
      auVar74._12_4_ = uStack_14;
      auVar82 = _lqc2(auVar74);
      auVar83 = _qmtc2((float)(iVar75 >> 3));
      auVar82 = _vmulbc(auVar82,auVar83);
      auStack_8e0 = _sqc2(auVar82);
      __ct__7FVectorFRC7FVector(auStack_580,auStack_8e0);
      auVar7._4_4_ = auStack_1c0[5];
      auVar7._0_4_ = auStack_1c0[4];
      auVar7._8_4_ = auStack_1c0[6];
      auVar7._12_4_ = uStack_1a4;
      auVar82 = _lqc2(auVar7);
      auVar83 = _lqc2(auStack_580);
      auVar82 = _vadd(auVar82,auVar83);
      auStack_740 = _sqc2(auVar82);
      __ct__7FVectorFRC7FVector(auStack_570,auStack_740);
      iVar75 = param_1 + iVar79 * 0x20;
      *(int *)(iVar75 + 400) = auStack_570._0_4_;
      *(int *)(iVar75 + 0x194) = auStack_570._4_4_;
      *(undefined4 *)(iVar75 + 0x198) = uStack_568;
      *(undefined4 *)(iVar75 + 0x19c) = uStack_564;
    }
    *(undefined4 *)(param_1 + 0x280) = auStack_1c0[4];
    *(undefined4 *)(param_1 + 0x284) = auStack_1c0[5];
    *(undefined4 *)(param_1 + 0x288) = auStack_1c0[6];
    *(undefined4 *)(param_1 + 0x28c) = uStack_1a4;
    *(undefined4 *)(param_1 + 0x290) = auStack_240[4];
    *(undefined4 *)(param_1 + 0x294) = auStack_240[5];
    *(undefined4 *)(param_1 + 0x298) = auStack_240[6];
    *(undefined4 *)(param_1 + 0x29c) = uStack_224;
  }
  else {
    __ct__9GsxSplineFv(auStack_8);
    __ct__9GsxSplineFv(auStack_10);
    Create__9GsxSplineFUiUiP7FVector(auStack_8,*(undefined4 *)(param_1 + 0x68),0,auStack_1c0);
    Create__9GsxSplineFUiUiP7FVector(auStack_10,*(undefined4 *)(param_1 + 0x68),0,auStack_240);
    fVar81 = 0.0;
    for (iVar75 = 0; iVar75 < *(int *)(param_1 + 0x70); iVar75 = iVar75 + 1) {
      GetPosition__9GsxSplineFf(fVar81,auStack_590,auStack_8);
      iVar76 = param_1 + iVar75 * 0x20;
      *(int *)(iVar76 + 0x180) = auStack_590._0_4_;
      *(int *)(iVar76 + 0x184) = auStack_590._4_4_;
      *(undefined4 *)(iVar76 + 0x188) = uStack_588;
      *(undefined4 *)(iVar76 + 0x18c) = uStack_584;
      GetPosition__9GsxSplineFf(fVar81,auStack_5a0,auStack_10);
      iVar76 = param_1 + iVar75 * 0x20;
      *(int *)(iVar76 + 400) = auStack_5a0._0_4_;
      *(int *)(iVar76 + 0x194) = auStack_5a0._4_4_;
      *(undefined4 *)(iVar76 + 0x198) = uStack_598;
      *(undefined4 *)(iVar76 + 0x19c) = uStack_594;
      fVar81 = fVar81 + 1.0 / (float)(iVar79 + -1);
      if (1.0 < fVar81) {
        fVar81 = 1.0;
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
 * JP: 0x005109f0  MakePacket__17SwordLocusEffect2Fv
 * C++: SwordLocusEffect2::MakePacket()
 * size: 0xd3c bytes
 * --------------------------------------------------------------------------- */
/* WARNING: Removing unreachable block (ram,0x00510ba8) */
/* WARNING: Removing unreachable block (ram,0x00510d1c) */
/* WARNING: Removing unreachable block (ram,0x00510c48) */

void MakePacket__17SwordLocusEffect2Fv(int param_1)

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
      *puVar9 = (ulong)(uint)(fStack_4 * afStack_310[iVar11]);
      if (iVar11 == *(int *)(param_1 + 0x70) + -1) {
        puVar9[1] = (ulong)(uint)fStack_4 << 0x20 | 0x808080;
      }
      else {
        puVar9[1] = (ulong)(uint)fStack_4 << 0x20 | 0x30808080;
      }
      puVar9[2] = (long)aiStack_14a0[iVar11 * 8 + 2] << 0x20 |
                  (long)aiStack_14a0[iVar11 * 8] | (long)aiStack_14a0[iVar11 * 8 + 1] << 0x10;
      fVar15 = 16.0 / (float)aiStack_14a0[(iVar11 * 2 + 1) * 4 + 3];
      fStack_8 = afStack_410[0] * fVar15;
      fStack_c = fVar14 * fVar15;
      puVar9[3] = CONCAT44(fStack_c,afStack_410[0] * fVar15);
      if (iVar11 == *(int *)(param_1 + 0x70) + -1) {
        puVar9[4] = (ulong)(uint)fVar15 << 0x20 | 0x808080;
      }
      else {
        puVar9[4] = (ulong)(uint)fVar15 << 0x20 | 0x30808080;
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
 * JP: 0x00511730  EndSet__17SwordLocusEffect2Fv
 * C++: SwordLocusEffect2::EndSet()
 * size: 0x54 bytes
 * --------------------------------------------------------------------------- */
void EndSet__17SwordLocusEffect2Fv(int param_1)

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
 * JP: 0x00511790  ForceEndSet__17SwordLocusEffect2Fv
 * C++: SwordLocusEffect2::ForceEndSet()
 * size: 0x54 bytes
 * --------------------------------------------------------------------------- */
void ForceEndSet__17SwordLocusEffect2Fv(int param_1)

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
 * JP: 0x0054b5f0  @24@__dt__17SwordLocusEffect2Fv
 * C++: @24@__dt__17SwordLocusEffect2Fv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int * _24___dt__17SwordLocusEffect2Fv(int *param_1,short param_2)

{
  int *piVar1;
  
  piVar1 = param_1 + -6;
  if (piVar1 != (int *)0x0) {
    param_1[-1] = 0x40a170;
    param_1[4] = 0x40a180;
    param_1[7] = 0x40a190;
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
 * JP: 0x0054b600  @44@__dt__17SwordLocusEffect2Fv
 * C++: @44@__dt__17SwordLocusEffect2Fv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int _44___dt__17SwordLocusEffect2Fv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x2c;
  if (iVar1 != 0) {
    *(undefined4 *)(param_1 + -0x18) = 0x40a170;
    *(undefined4 *)(param_1 + -4) = 0x40a180;
    *(undefined4 *)(param_1 + 8) = 0x40a190;
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

