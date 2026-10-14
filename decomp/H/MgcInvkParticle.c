/* decomp/H/MgcInvkParticle.c — cleaned Ghidra output (SH2JP_BATTLE.BIN, JP Furokuban, base 0x00430a00).
 * 8 function(s). Types: see types.h. Names/gp globals resolved from symbols/SLPM_602.19.syms. */
#include "types.h"

/* ---------------------------------------------------------------------------
 * JP: 0x0051fbf0  __ct__15MgcInvkParticleFii7FVectorf
 * C++: MgcInvkParticle::__ct(int, int, FVector, float)
 * size: 0x380 bytes
 * --------------------------------------------------------------------------- */
int __ct__15MgcInvkParticleFii7FVectorf
              (undefined4 param_1,int param_2,undefined8 param_3,undefined8 param_4,
              undefined8 *param_5)

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
  undefined1 in_vf0 [16];
  undefined1 auVar8 [16];
  undefined1 auVar9 [16];
  undefined1 auVar10 [16];
  undefined1 auStack_60 [8];
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined1 auStack_50 [16];
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [16];
  undefined1 auStack_20 [16];
  undefined4 uStack_10;
  undefined4 uStack_c;
  float fStack_8;
  undefined4 uStack_4;
  
  __ct__6BtlEffFii(param_2,param_3,param_4);
  *(undefined4 *)(param_2 + 0x14) = 0x409e80;
  *(undefined4 *)(param_2 + 0x28) = 0x409e90;
  *(undefined4 *)(param_2 + 0x34) = 0x409ea0;
  *(undefined4 *)(param_2 + 0x70) = in_zero_lo;
  *(undefined4 *)(param_2 + 0x74) = in_zero_hi;
  *(undefined4 *)(param_2 + 0x78) = in_zero_udw;
  *(undefined4 *)(param_2 + 0x7c) = in_register_0000000c;
  puVar6 = (undefined4 *)(param_2 + 0x80);
  do {
    *puVar6 = in_zero_lo;
    puVar6[1] = in_zero_hi;
    puVar6[2] = in_zero_udw;
    puVar6[3] = in_register_0000000c;
    puVar6 = puVar6 + 4;
  } while (puVar6 != (undefined4 *)(param_2 + 0x480));
  *(undefined4 *)(param_2 + 0x40) = 0;
  *(int *)(param_2 + 0x44) = (int)param_3;
  *(int *)(param_2 + 0x48) = (int)param_4;
  *(undefined4 *)(param_2 + 0x4c) = 7;
  *(undefined4 *)(param_2 + 0x5c) = 0;
  *(undefined4 *)(param_2 + 0x60) = 0x3f800000;
  uVar1 = *param_5;
  uVar4 = *(undefined4 *)(param_5 + 1);
  uVar5 = *(undefined4 *)((int)param_5 + 0xc);
  *(int *)(param_2 + 0x70) = (int)uVar1;
  *(int *)(param_2 + 0x74) = (int)((ulong)uVar1 >> 0x20);
  *(undefined4 *)(param_2 + 0x78) = uVar4;
  *(undefined4 *)(param_2 + 0x7c) = uVar5;
  *(undefined4 *)(param_2 + 0x680) = param_1;
  for (iVar7 = 0; iVar7 < 0x40; iVar7 = iVar7 + 1) {
    iVar2 = rand();
    iVar3 = rand();
    fStack_8 = *(float *)(param_2 + 0x680) * ((float)iVar3 / 2.1474836e+09);
    uStack_10 = 0;
    uStack_c = 0;
    uStack_4 = 0x3f800000;
    auVar8 = _vmr32(in_vf0);
    auVar9 = _vmr32(auVar8);
    auVar10 = _vmr32(auVar9);
    _sqc2(in_vf0);
    _sqc2(auVar8);
    _sqc2(auVar9);
    _sqc2(auVar10);
    auVar8 = _vmr32(in_vf0);
    auVar9 = _vmr32(auVar8);
    auVar10 = _vmr32(auVar9);
    auStack_20 = _sqc2(in_vf0);
    auStack_30 = _sqc2(auVar8);
    auStack_40 = _sqc2(auVar9);
    auStack_50 = _sqc2(auVar10);
    sceVu0RotMatrixY(((float)iVar2 / 2.1474836e+09) * 6.2831855 - 3.1415927,auStack_50,auStack_50);
    ApplyMatrix__6MatrixCFRC7FVector(auStack_60,auStack_50,&uStack_10);
    iVar2 = param_2 + iVar7 * 0x10;
    *(int *)(iVar2 + 0x80) = auStack_60._0_4_;
    *(int *)(iVar2 + 0x84) = auStack_60._4_4_;
    *(undefined4 *)(iVar2 + 0x88) = uStack_58;
    *(undefined4 *)(iVar2 + 0x8c) = uStack_54;
    iVar2 = rand();
    *(float *)(param_2 + iVar7 * 0x10 + 0x84) = ((float)iVar2 / 2.1474836e+09) * 37.5 + 7.5;
    *(undefined4 *)(param_2 + iVar7 * 4 + 0x480) = 0x3f800000;
    iVar2 = rand();
    if ((float)iVar2 / 2.1474836e+09 < 0.5) {
      *(undefined4 *)(param_2 + iVar7 * 4 + 0x580) = 0x3e800000;
    }
    else {
      *(undefined4 *)(param_2 + iVar7 * 4 + 0x580) = 0x3f800000;
    }
  }
  *(undefined4 *)(param_2 + 0x1c) = 0;
  *(undefined4 *)(param_2 + 0x18) = 0;
  Entry__7CPollerFP7CPolObjib(iGpffff858c + 0x48,param_2,0x80,0);
  iVar7 = param_2;
  if (param_2 != 0) {
    iVar7 = param_2 + 0x18;
  }
  AddOT__5WorldFiP8VIF1Prim(0x42bf10,4,iVar7);
  *(byte *)(param_2 + 0x40) = *(byte *)(param_2 + 0x40) & 0xfd | 2;
  BtlEffEntry__7CBattleFiP6BtlEff(uGpffff86b4,*(undefined4 *)(param_2 + 0x48),param_2);
  return param_2;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0051ff70  __dt__15MgcInvkParticleFv
 * C++: MgcInvkParticle::__dt()
 * size: 0x154 bytes
 * --------------------------------------------------------------------------- */
int __dt__15MgcInvkParticleFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x14) = 0x409e80;
    *(undefined4 *)(param_1 + 0x28) = 0x409e90;
    *(undefined4 *)(param_1 + 0x34) = 0x409ea0;
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
 * JP: 0x005200d0  Destruct__15MgcInvkParticleFv
 * C++: MgcInvkParticle::Destruct()
 * size: 0xcc bytes
 * --------------------------------------------------------------------------- */
void Destruct__15MgcInvkParticleFv(int param_1)

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
 * JP: 0x005201a0  Polling__15MgcInvkParticleFv
 * C++: MgcInvkParticle::Polling()
 * size: 0x47c bytes
 * --------------------------------------------------------------------------- */
undefined4 Polling__15MgcInvkParticleFv(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined1 in_vf0 [16];
  undefined1 auVar4 [16];
  undefined1 auVar5 [16];
  undefined1 auVar6 [16];
  undefined1 auStack_f0 [64];
  undefined1 auStack_b0 [8];
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  undefined1 auStack_a0 [8];
  undefined4 uStack_98;
  undefined4 auStack_90 [16];
  undefined4 uStack_50;
  undefined4 uStack_4c;
  float fStack_48;
  undefined4 uStack_44;
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [16];
  undefined1 auStack_20 [16];
  undefined1 auStack_10 [16];
  
  auVar4 = _vmr32(in_vf0);
  auVar5 = _vmr32(auVar4);
  auVar6 = _vmr32(auVar5);
  auStack_10 = _sqc2(in_vf0);
  auStack_20 = _sqc2(auVar4);
  auStack_30 = _sqc2(auVar5);
  auStack_40 = _sqc2(auVar6);
  if ((*(byte *)(iGpffff86b4 + 0x24) & 1) == 0) {
    for (iVar3 = 0; iVar3 < 0x40; iVar3 = iVar3 + 1) {
      iVar1 = param_1 + iVar3 * 0x10;
      *(float *)(iVar1 + 0x84) = *(float *)(iVar1 + 0x84) - *(float *)(iGpffff86b4 + 0x38) * 40.0;
      if (-20.0 <= *(float *)(param_1 + iVar3 * 0x10 + 0x84)) {
        *(undefined4 *)(param_1 + iVar3 * 4 + 0x480) = 0x3f800000;
      }
      else {
        *(float *)(param_1 + iVar3 * 4 + 0x480) =
             (*(float *)(param_1 + iVar3 * 0x10 + 0x84) + 30.0) / 10.0;
      }
      if (*(float *)(param_1 + iVar3 * 4 + 0x580) == 1.0) {
        *(undefined4 *)(param_1 + iVar3 * 4 + 0x580) = 0x3e800000;
      }
      else {
        *(undefined4 *)(param_1 + iVar3 * 4 + 0x580) = 0x3f800000;
      }
      if (*(float *)(param_1 + iVar3 * 0x10 + 0x84) < -30.0) {
        *(undefined4 *)(param_1 + iVar3 * 4 + 0x480) = 0x3f800000;
        iVar1 = rand();
        iVar2 = rand();
        fStack_48 = *(float *)(param_1 + 0x680) * ((float)iVar2 / 2.1474836e+09);
        uStack_50 = 0;
        uStack_4c = 0;
        uStack_44 = 0x3f800000;
        auVar4 = _vmr32(in_vf0);
        auVar5 = _vmr32(auVar4);
        auVar6 = _vmr32(auVar5);
        auStack_10 = _sqc2(in_vf0);
        auStack_20 = _sqc2(auVar4);
        auStack_30 = _sqc2(auVar5);
        auStack_40 = _sqc2(auVar6);
        sceVu0RotMatrixY(((float)iVar1 / 2.1474836e+09) * 6.2831855 - 3.1415927,auStack_40,auStack_40
                       );
        ApplyMatrix__6MatrixCFRC7FVector(auStack_b0,auStack_40,&uStack_50);
        iVar1 = param_1 + iVar3 * 0x10;
        *(int *)(iVar1 + 0x80) = auStack_b0._0_4_;
        *(int *)(iVar1 + 0x84) = auStack_b0._4_4_;
        *(undefined4 *)(iVar1 + 0x88) = uStack_a8;
        *(undefined4 *)(iVar1 + 0x8c) = uStack_a4;
        *(undefined4 *)(param_1 + iVar3 * 0x10 + 0x84) = 0x40f00000;
      }
    }
    if ((*(int *)(param_1 + 0x5c) != 0) &&
       (*(float *)(param_1 + 0x60) =
             *(float *)(param_1 + 0x60) - *(float *)(iGpffff86b4 + 0x38) * 2.5,
       *(float *)(param_1 + 0x60) <= 0.0)) {
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
  GetViewScreenMatrix__9GsxCameraFv(auStack_f0,uGpffff8598);
  for (iVar3 = 0; iVar3 < 4; iVar3 = iVar3 + 1) {
    auStack_90[iVar3 * 4] = *(undefined4 *)(auStack_40 + iVar3 * 0x10);
    auStack_90[iVar3 * 4 + 1] = *(undefined4 *)(auStack_40 + iVar3 * 0x10 + 4);
    auStack_90[iVar3 * 4 + 2] = *(undefined4 *)(auStack_40 + iVar3 * 0x10 + 8);
    auStack_90[iVar3 * 4 + 3] = *(undefined4 *)(auStack_40 + iVar3 * 0x10 + 0xc);
  }
  sceVu0RotTransPersN(auStack_a0,auStack_90,param_1 + 0x70,1,0);
  *(undefined4 *)(param_1 + 0x50) = uStack_98;
  return 0;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00520620  MakePacket__15MgcInvkParticleFv
 * C++: MgcInvkParticle::MakePacket()
 * size: 0x1364 bytes
 * --------------------------------------------------------------------------- */
void MakePacket__15MgcInvkParticleFv(int param_1)

{
  bool bVar1;
  undefined4 *puVar2;
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  undefined4 uVar3;
  undefined8 uVar4;
  undefined8 extraout_v0_udw;
  undefined8 in_v1_udw;
  undefined1 auVar5 [16];
  int iVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  undefined1 in_vf0 [16];
  undefined1 auVar10 [16];
  undefined1 auVar11 [16];
  undefined1 auVar12 [16];
  undefined1 auStack_2380 [16];
  undefined1 auStack_2370 [64];
  undefined1 auStack_2330 [16];
  undefined4 uStack_2320;
  float fStack_231c;
  undefined4 uStack_2318;
  undefined4 uStack_2314;
  undefined4 uStack_2310;
  undefined4 uStack_230c;
  undefined4 uStack_2308;
  undefined4 uStack_2304;
  undefined4 uStack_2300;
  undefined4 uStack_22fc;
  undefined4 uStack_22f8;
  undefined4 uStack_22f4;
  undefined4 uStack_22f0;
  undefined4 uStack_22ec;
  undefined4 uStack_22e8;
  undefined4 uStack_22e4;
  undefined4 uStack_22e0;
  undefined4 uStack_22dc;
  undefined4 uStack_22d8;
  undefined4 uStack_22d4;
  undefined4 uStack_22d0;
  undefined4 uStack_22cc;
  undefined4 uStack_22c8;
  undefined4 uStack_22c4;
  undefined4 uStack_22c0;
  undefined4 uStack_22bc;
  undefined4 uStack_22b8;
  undefined4 uStack_22b4;
  undefined4 uStack_22b0;
  undefined4 uStack_22ac;
  undefined4 uStack_22a8;
  undefined4 uStack_22a4;
  undefined4 uStack_22a0;
  undefined4 uStack_229c;
  undefined4 uStack_2298;
  undefined4 uStack_2294;
  int aiStack_2290 [64];
  int aiStack_2190 [1040];
  float afStack_1150 [1024];
  float afStack_150 [16];
  float afStack_110 [16];
  undefined1 auStack_d0 [16];
  undefined1 auStack_c0 [16];
  undefined1 auStack_b0 [16];
  undefined1 auStack_a0 [16];
  undefined4 uStack_90;
  float fStack_8c;
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
  
  uStack_22a0 = 0xc0200000;
  uStack_229c = 0xc0f00000;
  uStack_2298 = 0;
  uStack_2294 = 0x3f800000;
  uStack_80 = 0xc0200000;
  uStack_7c = 0xc0f00000;
  uStack_78 = 0;
  uStack_74 = 0x3f800000;
  uStack_22b0 = 0xc0200000;
  uStack_22ac = 0x40f00000;
  uStack_22a8 = 0;
  uStack_22a4 = 0x3f800000;
  uStack_70 = 0xc0200000;
  uStack_6c = 0x40f00000;
  uStack_68 = 0;
  uStack_64 = 0x3f800000;
  uStack_22c0 = 0x40200000;
  uStack_22bc = 0xc0f00000;
  uStack_22b8 = 0;
  uStack_22b4 = 0x3f800000;
  uStack_60 = 0x40200000;
  uStack_5c = 0xc0f00000;
  uStack_58 = 0;
  uStack_54 = 0x3f800000;
  uStack_22d0 = 0x40200000;
  uStack_22cc = 0x40f00000;
  uStack_22c8 = 0;
  uStack_22c4 = 0x3f800000;
  uStack_50 = 0x40200000;
  uStack_4c = 0x40f00000;
  uStack_48 = 0;
  uStack_44 = 0x3f800000;
  uStack_22e0 = 0xbf400000;
  uStack_22dc = 0xbf400000;
  uStack_22d8 = 0;
  uStack_22d4 = 0x3f800000;
  uStack_40 = 0xbf400000;
  uStack_3c = 0xbf400000;
  uStack_38 = 0;
  uStack_34 = 0x3f800000;
  uStack_22f0 = 0xbf400000;
  uStack_22ec = 0x3f400000;
  uStack_22e8 = 0;
  uStack_22e4 = 0x3f800000;
  uStack_30 = 0xbf400000;
  uStack_2c = 0x3f400000;
  uStack_28 = 0;
  uStack_24 = 0x3f800000;
  uStack_2300 = 0x3f400000;
  uStack_22fc = 0xbf400000;
  uStack_22f8 = 0;
  uStack_22f4 = 0x3f800000;
  uStack_20 = 0x3f400000;
  uStack_1c = 0xbf400000;
  uStack_18 = 0;
  uStack_14 = 0x3f800000;
  uStack_2310 = 0x3f400000;
  uStack_230c = 0x3f400000;
  uStack_2308 = 0;
  uStack_2304 = 0x3f800000;
  uStack_10 = 0x3f400000;
  uStack_c = 0x3f400000;
  uStack_8 = 0;
  uStack_4 = 0x3f800000;
  auVar10 = _lqc2(*(undefined1 (*) [16])(*(int *)(iGpffff86b4 + 0x4324) + 0x30));
  auVar11 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x70));
  auVar10 = _vsub(auVar10,auVar11);
  auStack_2380 = _sqc2(auVar10);
  __ct__7FVectorFRC7FVector(&uStack_90,auStack_2380);
  uVar4 = __ct__7FVectorFRC7FVector(auStack_2330,&uStack_90);
  Get3DAngleRad__F7FVector(&uStack_2320,uVar4);
  uStack_90 = uStack_2320;
  fStack_8c = fStack_231c;
  uStack_88 = uStack_2318;
  uStack_84 = uStack_2314;
  auVar10 = _vmr32(in_vf0);
  auVar11 = _vmr32(auVar10);
  auVar12 = _vmr32(auVar11);
  _sqc2(in_vf0);
  _sqc2(auVar10);
  _sqc2(auVar11);
  _sqc2(auVar12);
  auVar10 = _vmr32(in_vf0);
  auVar11 = _vmr32(auVar10);
  auVar12 = _vmr32(auVar11);
  auStack_a0 = _sqc2(in_vf0);
  auStack_b0 = _sqc2(auVar10);
  auStack_c0 = _sqc2(auVar11);
  auStack_d0 = _sqc2(auVar12);
  sceVu0RotMatrixY(-fStack_231c,auStack_d0,auStack_d0);
  RotTransVector(afStack_150,&uStack_80,auStack_d0,4);
  auStack_d0 = *(undefined1 (*) [16])(iGpffff8598 + 0x240);
  auStack_c0 = *(undefined1 (*) [16])(iGpffff8598 + 0x250);
  auStack_b0 = *(undefined1 (*) [16])(iGpffff8598 + 0x260);
  auStack_a0._0_12_ = ZEXT812(0);
  auStack_a0._12_4_ = 0x3f800000;
  RotTransVector(afStack_110,&uStack_40,auStack_d0,4);
  for (iVar6 = 0; iVar6 < 0x20; iVar6 = iVar6 + 1) {
    for (iVar9 = 0; iVar9 < 4; iVar9 = iVar9 + 1) {
      afStack_1150[(iVar9 + iVar6 * 4) * 4] =
           *(float *)(param_1 + 0x70) + *(float *)(param_1 + iVar6 * 0x10 + 0x80) +
           afStack_150[iVar9 * 4];
      afStack_1150[(iVar9 + iVar6 * 4) * 4 + 1] =
           *(float *)(param_1 + 0x74) + *(float *)(param_1 + iVar6 * 0x10 + 0x84) +
           afStack_150[iVar9 * 4 + 1];
      afStack_1150[(iVar9 + iVar6 * 4) * 4 + 2] =
           *(float *)(param_1 + 0x78) + *(float *)(param_1 + iVar6 * 0x10 + 0x88) +
           afStack_150[iVar9 * 4 + 2];
      afStack_1150[(iVar9 + iVar6 * 4) * 4 + 3] = 1.0;
    }
  }
  for (iVar6 = 0x20; iVar6 < 0x40; iVar6 = iVar6 + 1) {
    for (iVar9 = 0; iVar9 < 4; iVar9 = iVar9 + 1) {
      afStack_1150[(iVar9 + iVar6 * 4) * 4] =
           *(float *)(param_1 + 0x70) + *(float *)(param_1 + iVar6 * 0x10 + 0x80) +
           afStack_150[(iVar9 + 4) * 4];
      afStack_1150[(iVar9 + iVar6 * 4) * 4 + 1] =
           *(float *)(param_1 + 0x74) + *(float *)(param_1 + iVar6 * 0x10 + 0x84) +
           afStack_150[(iVar9 + 4) * 4 + 1];
      afStack_1150[(iVar9 + iVar6 * 4) * 4 + 2] =
           *(float *)(param_1 + 0x78) + *(float *)(param_1 + iVar6 * 0x10 + 0x88) +
           afStack_150[(iVar9 + 4) * 4 + 2];
      afStack_1150[(iVar9 + iVar6 * 4) * 4 + 3] = 1.0;
    }
  }
  GetViewScreenMatrix__9GsxCameraFv(auStack_2370,iGpffff8598);
  for (iVar6 = 0; iVar6 < 4; iVar6 = iVar6 + 1) {
    aiStack_2190[iVar6 * 4 + 0x400] = *(int *)(auStack_d0 + iVar6 * 0x10);
    aiStack_2190[iVar6 * 4 + 0x401] = *(int *)(auStack_d0 + iVar6 * 0x10 + 4);
    aiStack_2190[iVar6 * 4 + 0x402] = *(int *)(auStack_d0 + iVar6 * 0x10 + 8);
    aiStack_2190[iVar6 * 4 + 0x403] = *(int *)(auStack_d0 + iVar6 * 0x10 + 0xc);
  }
  sceVu0RotTransPersN(aiStack_2190,aiStack_2190 + 0x400,afStack_1150,0x100,0);
  for (iVar6 = 0; iVar6 < 0x40; iVar6 = iVar6 + 1) {
    aiStack_2290[iVar6] = 0;
    for (iVar9 = 0; iVar9 < 4; iVar9 = iVar9 + 1) {
      if ((((aiStack_2190[(iVar9 + iVar6 * 4) * 4] < 0) ||
           (0x10000 < aiStack_2190[(iVar9 + iVar6 * 4) * 4])) ||
          (aiStack_2190[(iVar9 + iVar6 * 4) * 4 + 1] < 0)) ||
         ((0x10000 < aiStack_2190[(iVar9 + iVar6 * 4) * 4 + 1] ||
          (aiStack_2190[(iVar9 + iVar6 * 4) * 4 + 2] < 0)))) {
        aiStack_2290[iVar6] = 1;
      }
      iVar7 = iVar9 + iVar6 * 4;
      aiStack_2190[iVar7 * 4 + 2] = (int)((float)aiStack_2190[iVar7 * 4 + 2] / 16.0);
    }
  }
  bVar1 = (*(byte *)(param_1 + 0x40) & 1) == 0;
  uVar8 = (uint)bVar1;
  if (*(int *)(param_1 + uVar8 * 4 + 0x18) == 0) {
    uVar3 = __nwa__FUi(0x1500);
    *(undefined4 *)(param_1 + uVar8 * 4 + 0x18) = uVar3;
    iVar6 = *(int *)(param_1 + uVar8 * 4 + 0x18);
    *(undefined4 *)(iVar6 + 0x10) = 0x100000a8;
    *(undefined4 *)(iVar6 + 0x14) = 0;
    *(undefined4 *)(iVar6 + 0x18) = 0;
    *(undefined4 *)(iVar6 + 0x1c) = 0x500000a8;
    *(undefined8 *)(iVar6 + 0x20) = 0x6000000000000001;
    *(undefined8 *)(iVar6 + 0x28) = 0x6ee8ee;
    *(undefined8 *)(iVar6 + 0x30) = 1;
    *(undefined8 *)(iVar6 + 0x38) = 0x3f;
    *(undefined8 *)(iVar6 + 0x40) = 0x60;
    *(undefined8 *)(iVar6 + 0x48) = 0x14;
    *(undefined8 *)(iVar6 + 0x50) = 5;
    *(undefined8 *)(iVar6 + 0x58) = 0;
    *(undefined8 *)(iVar6 + 0x60) = 0x53001;
    *(undefined8 *)(iVar6 + 0x68) = 0x47;
    *(undefined8 *)(iVar6 + 0x70) = 0x48;
    *(undefined8 *)(iVar6 + 0x78) = 0x42;
    uVar4 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x42e0),1);
    *(undefined8 *)(iVar6 + 0x80) = uVar4;
    *(undefined8 *)(iVar6 + 0x88) = 0;
    auVar11._8_8_ = extraout_v0_udw;
    auVar11._0_8_ = 0xa400000000008020;
    auVar10._4_4_ = in_zero_hi;
    auVar10._0_4_ = in_zero_lo;
    auVar10._8_4_ = in_zero_udw;
    auVar10._12_4_ = in_register_0000000c;
    auVar10 = _pcpyld(auVar10,auVar11);
    *(long *)(iVar6 + 0x90) = auVar10._0_8_;
    *(undefined8 *)(iVar6 + 0x98) = 0x4343c3c310;
    for (iVar9 = 0; iVar9 < 0x20; iVar9 = iVar9 + 1) {
      *(undefined8 *)(iVar6 + (iVar9 * 5 + 10) * 0x10) = 0x154;
      *(undefined8 *)(iVar6 + (iVar9 * 5 + 0xb) * 0x10) = 0;
      *(long *)(iVar6 + (iVar9 * 5 + 0xc) * 0x10) =
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42e0) + 4) << 4) << 0x10;
      *(long *)(iVar6 + (iVar9 * 5 + 0xd) * 0x10) =
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42e0) + 2) << 4);
      *(long *)(iVar6 + (iVar9 * 5 + 0xe) * 0x10) =
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42e0) + 2) << 4) |
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42e0) + 4) << 4) << 0x10;
    }
    *(undefined4 *)(iVar6 + 0xaa0) = 0x50000000;
    *(undefined4 *)(iVar6 + 0xaa4) =
         *(undefined4 *)
          (*(int *)(iGpffff86b4 + 0x42e4) +
           (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42e4) + 10) * 4 + 0xc);
    *(undefined4 *)(iVar6 + 0xaa8) = 0;
    *(undefined4 *)(iVar6 + 0xaac) = 0;
    *(undefined4 *)(iVar6 + 0xab0) = 0x600000a4;
    *(undefined4 *)(iVar6 + 0xab4) = 0;
    *(undefined4 *)(iVar6 + 0xab8) = 0;
    *(undefined4 *)(iVar6 + 0xabc) = 0x500000a4;
    *(undefined8 *)(iVar6 + 0xac0) = 0x2000000000000001;
    *(undefined8 *)(iVar6 + 0xac8) = 0x6e;
    *(undefined8 *)(iVar6 + 0xad0) = 1;
    *(undefined8 *)(iVar6 + 0xad8) = 0x3f;
    uVar4 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x42e4),1);
    *(undefined8 *)(iVar6 + 0xae0) = uVar4;
    *(undefined8 *)(iVar6 + 0xae8) = 0;
    auVar5._8_8_ = in_v1_udw;
    auVar5._0_8_ = 0xa400000000008020;
    auVar12._4_4_ = in_zero_hi;
    auVar12._0_4_ = in_zero_lo;
    auVar12._8_4_ = in_zero_udw;
    auVar12._12_4_ = in_register_0000000c;
    auVar10 = _pcpyld(auVar12,auVar5);
    *(long *)(iVar6 + 0xaf0) = auVar10._0_8_;
    *(undefined8 *)(iVar6 + 0xaf8) = 0x4343c3c310;
    for (iVar9 = 0; iVar9 < 0x20; iVar9 = iVar9 + 1) {
      *(undefined8 *)(iVar6 + (iVar9 * 5 + 0xb0) * 0x10) = 0x154;
      *(undefined8 *)(iVar6 + (iVar9 * 5 + 0xb1) * 0x10) = 0;
      *(long *)(iVar6 + (iVar9 * 5 + 0xb2) * 0x10) =
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42e4) + 4) << 4) << 0x10;
      *(long *)(iVar6 + (iVar9 * 5 + 0xb3) * 0x10) =
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42e4) + 2) << 4);
      *(long *)(iVar6 + (iVar9 * 5 + 0xb4) * 0x10) =
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42e4) + 2) << 4) |
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42e4) + 4) << 4) << 0x10;
    }
  }
  puVar2 = *(undefined4 **)(param_1 + uVar8 * 4 + 0x18);
  *puVar2 = 0x50000000;
  puVar2[1] = *(undefined4 *)
               (*(int *)(iGpffff86b4 + 0x42e0) +
                (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42e0) + 10) * 4 + 0xc);
  puVar2[2] = 0;
  puVar2[3] = 0;
  for (iVar6 = 0; iVar6 < 0x20; iVar6 = iVar6 + 1) {
    if (aiStack_2290[iVar6] == 0) {
      iVar9 = (int)(((*(float *)(param_1 + iVar6 * 0x10 + 0x84) + 30.0) * 128.0) / 37.5);
      if (iVar9 < 0) {
        iVar9 = 0;
      }
      if (0x80 < iVar9) {
        iVar9 = 0x80;
      }
      *(ulong *)(puVar2 + (iVar6 * 5 + 10) * 4 + 2) =
           (long)iVar9 | 0x808000U |
           (long)(int)(*(float *)(param_1 + iVar6 * 4 + 0x480) * *(float *)(param_1 + 0x60) * 80.0)
           << 0x18 | 0x100000000;
      *(long *)(puVar2 + (iVar6 * 5 + 0xb) * 4 + 2) =
           (long)aiStack_2190[iVar6 * 0x10 + 2] << 0x20 |
           (long)aiStack_2190[iVar6 * 0x10] | (long)aiStack_2190[iVar6 * 0x10 + 1] << 0x10;
      *(long *)(puVar2 + (iVar6 * 5 + 0xc) * 4 + 2) =
           (long)aiStack_2190[(iVar6 * 4 + 1) * 4 + 2] << 0x20 |
           (long)aiStack_2190[(iVar6 * 4 + 1) * 4] |
           (long)aiStack_2190[(iVar6 * 4 + 1) * 4 + 1] << 0x10;
      *(long *)(puVar2 + (iVar6 * 5 + 0xd) * 4 + 2) =
           (long)aiStack_2190[(iVar6 * 4 + 2) * 4 + 2] << 0x20 |
           (long)aiStack_2190[(iVar6 * 4 + 2) * 4] |
           (long)aiStack_2190[(iVar6 * 4 + 2) * 4 + 1] << 0x10;
      *(long *)(puVar2 + (iVar6 * 5 + 0xe) * 4 + 2) =
           (long)aiStack_2190[(iVar6 * 4 + 3) * 4 + 2] << 0x20 |
           (long)aiStack_2190[(iVar6 * 4 + 3) * 4] |
           (long)aiStack_2190[(iVar6 * 4 + 3) * 4 + 1] << 0x10;
    }
    else {
      *(undefined8 *)(puVar2 + (iVar6 * 5 + 0xb) * 4 + 2) = 0x71006f00;
      *(undefined8 *)(puVar2 + (iVar6 * 5 + 0xc) * 4 + 2) = 0x71006f00;
      *(undefined8 *)(puVar2 + (iVar6 * 5 + 0xd) * 4 + 2) = 0x71006f00;
      *(undefined8 *)(puVar2 + (iVar6 * 5 + 0xe) * 4 + 2) = 0x71006f00;
    }
  }
  for (iVar6 = 0x20; iVar6 < 0x40; iVar6 = iVar6 + 1) {
    if (aiStack_2290[iVar6] == 0) {
      *(ulong *)(puVar2 + (iVar6 * 5 + 0x10) * 4 + 2) =
           (long)(int)(*(float *)(param_1 + iVar6 * 4 + 0x580) *
                       *(float *)(param_1 + iVar6 * 4 + 0x480) * *(float *)(param_1 + 0x60) * 96.0)
           << 0x18 | 0x100808080;
      *(long *)(puVar2 + (iVar6 * 5 + 0x11) * 4 + 2) =
           (long)aiStack_2190[iVar6 * 0x10 + 2] << 0x20 |
           (long)aiStack_2190[iVar6 * 0x10] | (long)aiStack_2190[iVar6 * 0x10 + 1] << 0x10;
      *(long *)(puVar2 + (iVar6 * 5 + 0x12) * 4 + 2) =
           (long)aiStack_2190[(iVar6 * 4 + 1) * 4 + 2] << 0x20 |
           (long)aiStack_2190[(iVar6 * 4 + 1) * 4] |
           (long)aiStack_2190[(iVar6 * 4 + 1) * 4 + 1] << 0x10;
      *(long *)(puVar2 + (iVar6 * 5 + 0x13) * 4 + 2) =
           (long)aiStack_2190[(iVar6 * 4 + 2) * 4 + 2] << 0x20 |
           (long)aiStack_2190[(iVar6 * 4 + 2) * 4] |
           (long)aiStack_2190[(iVar6 * 4 + 2) * 4 + 1] << 0x10;
      *(long *)(puVar2 + (iVar6 * 5 + 0x14) * 4 + 2) =
           (long)aiStack_2190[(iVar6 * 4 + 3) * 4 + 2] << 0x20 |
           (long)aiStack_2190[(iVar6 * 4 + 3) * 4] |
           (long)aiStack_2190[(iVar6 * 4 + 3) * 4 + 1] << 0x10;
    }
    else {
      *(undefined8 *)(puVar2 + (iVar6 * 5 + 0x11) * 4 + 2) = 0x71006f00;
      *(undefined8 *)(puVar2 + (iVar6 * 5 + 0x12) * 4 + 2) = 0x71006f00;
      *(undefined8 *)(puVar2 + (iVar6 * 5 + 0x13) * 4 + 2) = 0x71006f00;
      *(undefined8 *)(puVar2 + (iVar6 * 5 + 0x14) * 4 + 2) = 0x71006f00;
    }
  }
  *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfe | bVar1;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054ae90  EndSet__15MgcInvkParticleFv
 * C++: MgcInvkParticle::EndSet()
 * size: 0x20 bytes
 * --------------------------------------------------------------------------- */
void EndSet__15MgcInvkParticleFv(int param_1)

{
  *(undefined4 *)(param_1 + 0x5c) = 1;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b760  @24@__dt__15MgcInvkParticleFv
 * C++: @24@__dt__15MgcInvkParticleFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int * _24___dt__15MgcInvkParticleFv(int *param_1,short param_2)

{
  int *piVar1;
  
  piVar1 = param_1 + -6;
  if (piVar1 != (int *)0x0) {
    param_1[-1] = 0x409e80;
    param_1[4] = 0x409e90;
    param_1[7] = 0x409ea0;
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
 * JP: 0x0054b770  @44@__dt__15MgcInvkParticleFv
 * C++: @44@__dt__15MgcInvkParticleFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int _44___dt__15MgcInvkParticleFv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x2c;
  if (iVar1 != 0) {
    *(undefined4 *)(param_1 + -0x18) = 0x409e80;
    *(undefined4 *)(param_1 + -4) = 0x409e90;
    *(undefined4 *)(param_1 + 8) = 0x409ea0;
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

