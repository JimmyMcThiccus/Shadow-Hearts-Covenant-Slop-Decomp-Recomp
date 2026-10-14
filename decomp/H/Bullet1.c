/* decomp/H/Bullet1.c — cleaned Ghidra output (SH2JP_BATTLE.BIN, JP Furokuban, base 0x00430a00).
 * 8 function(s). Types: see types.h. Names/gp globals resolved from symbols/SLPM_602.19.syms. */
#include "types.h"

/* ---------------------------------------------------------------------------
 * JP: 0x0053ba90  __ct__7Bullet1FiiissfiiiiUsUsii
 * C++: Bullet1::__ct(int, int, int, short, short, float, int, int, int, int, ushort, ushort, int, int)
 * size: 0x9c4 bytes
 * --------------------------------------------------------------------------- */
undefined8
__ct__7Bullet1FiiissfiiiiUsUsii
          (undefined4 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
          undefined4 param_5,undefined2 param_6,undefined2 param_7,undefined4 param_8,
          undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined2 param_12,
          undefined2 param_13,undefined4 param_14,undefined4 param_15)

{
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  int iVar1;
  undefined8 uVar2;
  long lVar3;
  undefined8 uVar4;
  undefined4 *puVar5;
  undefined1 (*pauVar6) [16];
  int iVar7;
  float fVar8;
  undefined1 in_vf0 [16];
  undefined1 auVar9 [16];
  undefined1 auVar10 [16];
  undefined1 auVar11 [16];
  undefined1 auStack_140 [16];
  undefined1 auStack_130 [16];
  undefined1 auStack_120 [16];
  undefined1 auStack_110 [16];
  undefined1 auStack_100 [16];
  undefined1 auStack_f0 [8];
  undefined4 uStack_e8;
  undefined4 uStack_e4;
  undefined1 auStack_e0 [16];
  undefined1 auStack_d0 [8];
  undefined4 uStack_c8;
  undefined4 uStack_c4;
  undefined4 uStack_c0;
  undefined4 uStack_bc;
  undefined4 uStack_b8;
  undefined4 uStack_b4;
  undefined1 auStack_b0 [8];
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  undefined4 uStack_a0;
  undefined4 uStack_9c;
  undefined4 uStack_98;
  undefined4 uStack_94;
  undefined4 uStack_90;
  float fStack_8c;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined1 auStack_70 [16];
  undefined4 uStack_60;
  float fStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  float fStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [16];
  undefined1 auStack_20 [16];
  undefined1 auStack_10 [16];
  
  __ct__6BtlEffFii(param_2,param_3,param_4);
  iVar7 = (int)param_2;
  *(undefined4 *)(iVar7 + 0x14) = 0x409ac0;
  *(undefined4 *)(iVar7 + 0x28) = 0x409ad0;
  *(undefined4 *)(iVar7 + 0x34) = 0x409ae0;
  puVar5 = (undefined4 *)(iVar7 + 0x70);
  do {
    *puVar5 = in_zero_lo;
    puVar5[1] = in_zero_hi;
    puVar5[2] = in_zero_udw;
    puVar5[3] = in_register_0000000c;
    puVar5 = puVar5 + 4;
  } while (puVar5 != (undefined4 *)(iVar7 + 0x90));
  *(undefined4 *)(iVar7 + 0x90) = in_zero_lo;
  *(undefined4 *)(iVar7 + 0x94) = in_zero_hi;
  *(undefined4 *)(iVar7 + 0x98) = in_zero_udw;
  *(undefined4 *)(iVar7 + 0x9c) = in_register_0000000c;
  *(undefined4 *)(iVar7 + 0x40) = 0;
  *(int *)(iVar7 + 0x44) = (int)param_3;
  *(int *)(iVar7 + 0x48) = (int)param_4;
  *(undefined4 *)(iVar7 + 0x4c) = 10;
  *(undefined4 *)(iVar7 + 0x5c) = param_5;
  *(undefined2 *)(iVar7 + 0x60) = param_6;
  *(undefined2 *)(iVar7 + 0x62) = param_7;
  *(undefined4 *)(iVar7 + 100) = param_1;
  *(undefined4 *)(iVar7 + 0xa0) = param_9;
  *(undefined4 *)(iVar7 + 0xa4) = param_10;
  *(undefined4 *)(iVar7 + 0xa8) = param_8;
  *(undefined4 *)(iVar7 + 0xac) = param_11;
  *(undefined2 *)(iVar7 + 0xb0) = param_12;
  *(undefined2 *)(iVar7 + 0xb2) = param_13;
  *(undefined4 *)(iVar7 + 0xb4) = param_14;
  *(undefined4 *)(iVar7 + 0xb8) = param_15;
  *(undefined4 *)(iVar7 + 0x1c) = 0;
  *(undefined4 *)(iVar7 + 0x18) = 0;
  iVar1 = GetRegDat__9RegDatApiFiii(0x3a,*(undefined4 *)(iGpffff86b4 + *(int *)(iVar7 + 0x48) * 0x4f0 + 0x55c)
                          ,0xffffffffffffffff);
  iVar1 = *(int *)(*(short *)(iVar1 + 0x14) * 4 + 0x651b70);
  auVar9 = _vmr32(in_vf0);
  auVar10 = _vmr32(auVar9);
  auVar11 = _vmr32(auVar10);
  _sqc2(in_vf0);
  _sqc2(auVar9);
  _sqc2(auVar10);
  _sqc2(auVar11);
  if (*(short *)(iVar1 + 2) == 2) {
    pauVar6 = (undefined1 (*) [16])
              (*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar7 + 0x48) * 0x4f0 + 0x144) +
                                0x530) + 0x30) +
               (uint)*(byte *)(*(int *)(*(int *)(*(int *)(iGpffff86b4 +
                                                          *(int *)(iVar7 + 0x48) * 0x4f0 + 0x144) +
                                                0x530) + 0xe4) +
                              *(short *)(iVar1 + *(short *)(iVar7 + 0x60) * 0x20 + 4) * 0x110) *
               0x1f0 + (bGpffff8340 & 1) * 0x40);
    auStack_40 = *pauVar6;
    auStack_30 = pauVar6[1];
    auStack_20 = pauVar6[2];
    auStack_10 = pauVar6[3];
  }
  else if (*(short *)(iVar1 + 2) == 1) {
    pauVar6 = (undefined1 (*) [16])
              (*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar7 + 0x48) * 0x4f0 + 0x144) +
                                0x52c) + 0x30) +
               (uint)*(byte *)(*(int *)(*(int *)(*(int *)(iGpffff86b4 +
                                                          *(int *)(iVar7 + 0x48) * 0x4f0 + 0x144) +
                                                0x52c) + 0xe4) +
                              *(short *)(iVar1 + *(short *)(iVar7 + 0x60) * 0x20 + 4) * 0x110) *
               0x1f0 + (bGpffff8340 & 1) * 0x40);
    auStack_40 = *pauVar6;
    auStack_30 = pauVar6[1];
    auStack_20 = pauVar6[2];
    auStack_10 = pauVar6[3];
  }
  else {
    pauVar6 = (undefined1 (*) [16])
              (*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar7 + 0x48) * 0x4f0 + 0x144) + 0x30) +
               (uint)*(byte *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar7 + 0x48) * 0x4f0 +
                                                0x144) + 0xe4) +
                              *(short *)(iVar1 + *(short *)(iVar7 + 0x60) * 0x20 + 4) * 0x110) *
               0x1f0 + (bGpffff8340 & 1) * 0x40);
    auStack_40 = *pauVar6;
    auStack_30 = pauVar6[1];
    auStack_20 = pauVar6[2];
    auStack_10 = pauVar6[3];
  }
  uStack_98 = *(undefined4 *)(iVar1 + *(short *)(iVar7 + 0x60) * 0x20 + 0x10);
  uStack_9c = *(undefined4 *)(iVar1 + *(short *)(iVar7 + 0x60) * 0x20 + 0xc);
  uStack_a0 = *(undefined4 *)(iVar1 + *(short *)(iVar7 + 0x60) * 0x20 + 8);
  uStack_94 = 0x3f800000;
  uStack_54 = 0x3f800000;
  uStack_b8 = *(undefined4 *)(iVar1 + *(short *)(iVar7 + 0x60) * 0x20 + 0x1c);
  uStack_bc = *(undefined4 *)(iVar1 + *(short *)(iVar7 + 0x60) * 0x20 + 0x18);
  uStack_c0 = *(undefined4 *)(iVar1 + *(short *)(iVar7 + 0x60) * 0x20 + 0x14);
  uStack_b4 = 0x3f800000;
  auVar10._4_4_ = uStack_9c;
  auVar10._0_4_ = uStack_a0;
  auVar10._8_4_ = uStack_98;
  auVar10._12_4_ = 0x3f800000;
  auVar10 = _lqc2(auVar10);
  auVar9._4_4_ = uStack_bc;
  auVar9._0_4_ = uStack_c0;
  auVar9._8_4_ = uStack_b8;
  auVar9._12_4_ = 0x3f800000;
  auVar9 = _lqc2(auVar9);
  auVar9 = _vadd(auVar10,auVar9);
  auStack_120 = _sqc2(auVar9);
  uStack_60 = uStack_a0;
  fStack_5c = (float)uStack_9c;
  uStack_58 = uStack_98;
  __ct__7FVectorFRC7FVector(auStack_b0,auStack_120);
  fStack_50 = auStack_b0._0_4_;
  uStack_4c = auStack_b0._4_4_;
  uStack_48 = uStack_a8;
  uStack_44 = uStack_a4;
  auStack_70._4_4_ = in_zero_hi;
  auStack_70._0_4_ = in_zero_lo;
  auStack_70._8_4_ = in_zero_udw;
  auStack_70._12_4_ = in_register_0000000c;
  uStack_80 = in_zero_lo;
  uStack_7c = in_zero_hi;
  uStack_78 = in_zero_udw;
  uStack_74 = in_register_0000000c;
  RotTransVector(&uStack_80,&uStack_60,auStack_40,2);
  *(undefined4 *)(iVar7 + 0x70) = uStack_80;
  *(undefined4 *)(iVar7 + 0x74) = uStack_7c;
  *(undefined4 *)(iVar7 + 0x78) = uStack_78;
  *(undefined4 *)(iVar7 + 0x7c) = uStack_74;
  *(undefined4 *)(iVar7 + 0x80) = uStack_80;
  *(undefined4 *)(iVar7 + 0x84) = uStack_7c;
  *(undefined4 *)(iVar7 + 0x88) = uStack_78;
  *(undefined4 *)(iVar7 + 0x8c) = uStack_74;
  fVar8 = 0.0;
  if (-1 < *(int *)(iVar7 + 0x5c)) {
    auVar9 = _lqc2(*(undefined1 (*) [16])(iGpffff86b4 + *(int *)(iVar7 + 0x5c) * 0x4f0 + 0x150));
    auVar10 = _lqc2(*(undefined1 (*) [16])(iGpffff86b4 + *(int *)(iVar7 + 0x5c) * 0x4f0 + 0x350));
    auVar9 = _vadd(auVar9,auVar10);
    auStack_140 = _sqc2(auVar9);
    __ct__7FVectorFRC7FVector(auStack_e0,auStack_140);
    auVar9 = _lqc2(auStack_e0);
    auVar10 = _lqc2(*(undefined1 (*) [16])(iVar7 + 0x70));
    auVar9 = _vsub(auVar9,auVar10);
    auStack_130 = _sqc2(auVar9);
    __ct__7FVectorFRC7FVector(auStack_d0,auStack_130);
    uStack_60 = auStack_d0._0_4_;
    fStack_5c = auStack_d0._4_4_;
    uStack_58 = uStack_c8;
    uStack_54 = uStack_c4;
    uVar2 = __ct__7FVectorFRC7FVector(auStack_100,&uStack_60);
    Get3DAngle__F7FVector(auStack_f0,uVar2);
    uStack_4c = auStack_f0._4_4_;
    uStack_48 = uStack_e8;
    uStack_44 = uStack_e4;
    fStack_50 = auStack_f0._0_4_;
    for (fVar8 = fStack_50; fVar8 < -180.0; fVar8 = fVar8 + 360.0) {
    }
    for (; 180.0 <= fVar8; fVar8 = fVar8 - 360.0) {
    }
  }
  *(float *)(iVar7 + 0x90) = fVar8;
  *(undefined4 *)(iVar7 + 0x94) =
       *(undefined4 *)(iGpffff86b4 + *(int *)(iVar7 + 0x48) * 0x4f0 + 0x174);
  *(undefined4 *)(iVar7 + 0x98) = 0;
  *(undefined4 *)(iVar7 + 0x9c) = 0x3f800000;
  lVar3 = __nw__FUi(0x5c0);
  uVar2 = 0;
  if (lVar3 != 0) {
    uVar2 = GetFileEntry(*(undefined4 *)(iGpffff86b4 + 0x45a8),0x16);
    uVar4 = GetFileEntry(*(undefined4 *)(iGpffff86b4 + 0x45a8),0x17);
    uVar2 = __ct__6EffMdlFPUcPUcfii(0x3f800000,lVar3,uVar2,uVar4,0xffffffffffffffff,6);
  }
  setMotion__7ExModelFPCc((int)uVar2 + 0x20,0x652d58);
  SetPos__6EffMdlFP7FVector(uVar2,iVar7 + 0x70);
  auVar11._4_4_ = uStack_7c;
  auVar11._0_4_ = uStack_80;
  auVar11._8_4_ = uStack_78;
  auVar11._12_4_ = uStack_74;
  auVar10 = _lqc2(auVar11);
  auVar9 = _lqc2(auStack_70);
  auVar9 = _vsub(auVar9,auVar10);
  auStack_70 = _sqc2(auVar9);
  uVar4 = __ct__7FVectorFRC7FVector(auStack_110,auStack_70);
  Get3DAngleRad__F7FVector(&uStack_90,uVar4);
  uStack_60 = uStack_90;
  uStack_58 = 0;
  uStack_54 = 0x3f800000;
  for (fStack_5c = 3.1415927 - fStack_8c; fStack_5c < -3.1415927; fStack_5c = fStack_5c + 6.2831855)
  {
  }
  for (; 3.1415927 <= fStack_5c; fStack_5c = fStack_5c - 6.2831855) {
  }
  SetAngle__6EffMdlFP7FVector(uVar2,&uStack_60);
  OTEntry__6EffMdlFii(uVar2,4,8);
  Entry__7CPollerFP7CPolObjib(iGpffff858c + 0x48,param_2,0x80,0);
  BtlEffEntry__7CBattleFiP6BtlEff(iGpffff86b4,*(undefined4 *)(iVar7 + 0x48),param_2);
  return param_2;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0053c460  __dt__7Bullet1Fv
 * C++: Bullet1::__dt()
 * size: 0x154 bytes
 * --------------------------------------------------------------------------- */
int __dt__7Bullet1Fv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x14) = 0x409ac0;
    *(undefined4 *)(param_1 + 0x28) = 0x409ad0;
    *(undefined4 *)(param_1 + 0x34) = 0x409ae0;
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
 * JP: 0x0053c5c0  Destruct__7Bullet1Fv
 * C++: Bullet1::Destruct()
 * size: 0xcc bytes
 * --------------------------------------------------------------------------- */
void Destruct__7Bullet1Fv(int param_1)

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
 * JP: 0x0053c690  Polling__7Bullet1Fv
 * C++: Bullet1::Polling()
 * size: 0xa9c bytes
 * --------------------------------------------------------------------------- */
undefined4 Polling__7Bullet1Fv(int param_1)

{
  float in_zero_lo;
  float in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  char cVar1;
  FVector *pFVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  int iVar5;
  undefined4 uVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  undefined1 in_vf0 [16];
  undefined1 auVar11 [16];
  undefined1 auVar12 [16];
  undefined1 auVar13 [16];
  undefined1 auStack_130 [16];
  undefined1 auStack_120 [16];
  undefined1 auStack_110 [16];
  undefined1 auStack_100 [16];
  undefined1 auStack_f0 [16];
  undefined1 auStack_e0 [16];
  undefined1 auStack_d0 [16];
  undefined4 uStack_c0;
  undefined4 uStack_bc;
  float fStack_b8;
  undefined4 uStack_b4;
  undefined8 uStack_b0;
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  undefined1 auStack_a0 [16];
  undefined1 auStack_90 [8];
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined1 auStack_80 [16];
  undefined1 auStack_70 [8];
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined1 auStack_60 [16];
  undefined1 auStack_50 [16];
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [16];
  float fStack_20;
  float fStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  float fStack_10;
  float fStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  auVar11 = _vmr32(in_vf0);
  auVar12 = _vmr32(auVar11);
  auVar13 = _vmr32(auVar12);
  auStack_30 = _sqc2(in_vf0);
  auStack_40 = _sqc2(auVar11);
  auStack_50 = _sqc2(auVar12);
  auStack_60 = _sqc2(auVar13);
  fVar10 = pCGpffff86b4->flDeltaT;
  if ((pCGpffff86b4->bFlags24 & 1) != 0) {
    fVar10 = 0.0;
  }
  fStack_20 = in_zero_lo;
  fStack_1c = in_zero_hi;
  uStack_18 = in_zero_udw;
  uStack_14 = in_register_0000000c;
  fStack_10 = in_zero_lo;
  fStack_c = in_zero_hi;
  uStack_8 = in_zero_udw;
  uStack_4 = in_register_0000000c;
  if ((-1 < *(int *)(param_1 + 0x5c)) && (fVar10 != 0.0)) {
    auVar11 = _lqc2(*(undefined1 (*) [16])pCGpffff86b4->aChr[*(int *)(param_1 + 0x5c)].aPos);
    auVar12 = _lqc2(*(undefined1 (*) [16])&pCGpffff86b4->aChr[*(int *)(param_1 + 0x5c)].field_0x2a0)
    ;
    auVar11 = _vadd(auVar11,auVar12);
    auStack_130 = _sqc2(auVar11);
    __ct__7FVectorFRC7FVector(auStack_80,auStack_130);
    auVar11 = _lqc2(auStack_80);
    auVar12 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x70));
    auVar11 = _vsub(auVar11,auVar12);
    auStack_120 = _sqc2(auVar11);
    __ct__7FVectorFRC7FVector(auStack_70,auStack_120);
    fStack_10 = auStack_70._0_4_;
    fStack_c = auStack_70._4_4_;
    uStack_8 = uStack_68;
    uStack_4 = uStack_64;
    uVar3 = __ct__7FVectorFRC7FVector(auStack_a0,&fStack_10);
    Get3DAngle__F7FVector(auStack_90,uVar3);
    fStack_20 = auStack_90._0_4_;
    fStack_1c = auStack_90._4_4_;
    uStack_18 = uStack_88;
    uStack_14 = uStack_84;
    for (fVar7 = fStack_20 - *(float *)(param_1 + 0x90); fVar7 < -180.0; fVar7 = fVar7 + 360.0) {
    }
    for (; 180.0 <= fVar7; fVar7 = fVar7 - 360.0) {
    }
    fVar9 = fVar10 * 5.0 * 30.0;
    fVar8 = fVar9;
    if (fVar7 <= fVar9) {
      fVar8 = fVar7;
    }
    if (fVar8 < -fVar9) {
      fVar8 = -fVar9;
    }
    *(float *)(param_1 + 0x90) = *(float *)(param_1 + 0x90) + fVar8;
    for (fVar7 = (180.0 - fStack_1c) - *(float *)(param_1 + 0x94); fVar7 < -180.0;
        fVar7 = fVar7 + 360.0) {
    }
    for (; 180.0 <= fVar7; fVar7 = fVar7 - 360.0) {
    }
    fVar8 = fVar9;
    if (fVar7 <= fVar9) {
      fVar8 = fVar7;
    }
    if (fVar8 < -fVar9) {
      fVar8 = -fVar9;
    }
    *(float *)(param_1 + 0x94) = *(float *)(param_1 + 0x94) + fVar8;
  }
  if (fVar10 != 0.0) {
    auVar11 = _vmr32(in_vf0);
    auVar12 = _vmr32(auVar11);
    auVar13 = _vmr32(auVar12);
    auStack_30 = _sqc2(in_vf0);
    auStack_40 = _sqc2(auVar11);
    auStack_50 = _sqc2(auVar12);
    auStack_60 = _sqc2(auVar13);
    uVar6 = GetRad(*(undefined4 *)(param_1 + 0x90));
    sceVu0RotMatrixX(uVar6,auStack_60,auStack_60);
    uVar6 = GetRad(*(undefined4 *)(param_1 + 0x94));
    sceVu0RotMatrixY(uVar6,auStack_60,auStack_60);
    uStack_c0 = 0;
    uStack_bc = 0;
    fStack_b8 = fVar10 * -20.0 * 30.0;
    uStack_b4 = 0x3f800000;
    ApplyMatrix__6MatrixCFRC7FVector(&uStack_b0,auStack_60,&uStack_c0);
    fStack_10 = (float)uStack_b0;
    fStack_c = (float)((ulong)uStack_b0 >> 0x20);
    uStack_8 = uStack_a8;
    uStack_4 = uStack_a4;
    *(int *)(param_1 + 0x80) = (int)*(undefined8 *)(param_1 + 0x70);
    *(int *)(param_1 + 0x84) = (int)((ulong)*(undefined8 *)(param_1 + 0x70) >> 0x20);
    *(undefined4 *)(param_1 + 0x88) = *(undefined4 *)(param_1 + 0x78);
    *(undefined4 *)(param_1 + 0x8c) = *(undefined4 *)(param_1 + 0x7c);
    auVar11._8_4_ = uStack_a8;
    auVar11._0_8_ = uStack_b0;
    auVar11._12_4_ = uStack_a4;
    auVar12 = _lqc2(auVar11);
    auVar11 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x70));
    auVar11 = _vadd(auVar11,auVar12);
    auVar11 = _sqc2(auVar11);
    *(undefined1 (*) [16])(param_1 + 0x70) = auVar11;
  }
  if (((long)((ulong)*(byte *)(param_1 + 0x40) << 0x3d) < 0) && (fVar10 != 0.0)) {
    BtlEffRelease__7CBattleFiP6BtlEff(pCGpffff86b4,*(undefined4 *)(param_1 + 0x48),param_1);
    if ((long)((ulong)*(byte *)(param_1 + 0x40) << 0x3e) < 0) {
      iVar5 = param_1;
      if (param_1 != 0) {
        iVar5 = param_1 + 0x18;
      }
      ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,iVar5);
    }
    *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfd;
    (**(code **)(*(int *)(param_1 + 0x34) + 0xc))();
    uVar6 = 1;
  }
  else if (*(float *)(param_1 + 0x80) < (-*(float *)&pCGpffff86b4->field_0x3f14 - 10.0) / 2.0) {
    BtlEffRelease__7CBattleFiP6BtlEff(pCGpffff86b4,*(undefined4 *)(param_1 + 0x48),param_1);
    if ((long)((ulong)*(byte *)(param_1 + 0x40) << 0x3e) < 0) {
      iVar5 = param_1;
      if (param_1 != 0) {
        iVar5 = param_1 + 0x18;
      }
      ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,iVar5);
    }
    *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfd;
    (**(code **)(*(int *)(param_1 + 0x34) + 0xc))();
    uVar6 = 1;
  }
  else if ((*(float *)&pCGpffff86b4->field_0x3f14 + 10.0) / 2.0 < *(float *)(param_1 + 0x80)) {
    BtlEffRelease__7CBattleFiP6BtlEff(pCGpffff86b4,*(undefined4 *)(param_1 + 0x48),param_1);
    if ((long)((ulong)*(byte *)(param_1 + 0x40) << 0x3e) < 0) {
      iVar5 = param_1;
      if (param_1 != 0) {
        iVar5 = param_1 + 0x18;
      }
      ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,iVar5);
    }
    *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfd;
    (**(code **)(*(int *)(param_1 + 0x34) + 0xc))();
    uVar6 = 1;
  }
  else if (0.0 < *(float *)(param_1 + 0x84)) {
    BtlEffRelease__7CBattleFiP6BtlEff(pCGpffff86b4,*(undefined4 *)(param_1 + 0x48),param_1);
    if ((long)((ulong)*(byte *)(param_1 + 0x40) << 0x3e) < 0) {
      iVar5 = param_1;
      if (param_1 != 0) {
        iVar5 = param_1 + 0x18;
      }
      ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,iVar5);
    }
    *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfd;
    (**(code **)(*(int *)(param_1 + 0x34) + 0xc))();
    uVar6 = 1;
  }
  else if (*(float *)(param_1 + 0x88) < (-*(float *)&pCGpffff86b4->field_0x3f1c - 10.0) / 2.0) {
    BtlEffRelease__7CBattleFiP6BtlEff(pCGpffff86b4,*(undefined4 *)(param_1 + 0x48),param_1);
    if ((long)((ulong)*(byte *)(param_1 + 0x40) << 0x3e) < 0) {
      iVar5 = param_1;
      if (param_1 != 0) {
        iVar5 = param_1 + 0x18;
      }
      ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,iVar5);
    }
    *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfd;
    (**(code **)(*(int *)(param_1 + 0x34) + 0xc))();
    uVar6 = 1;
  }
  else if ((*(float *)&pCGpffff86b4->field_0x3f1c + 10.0) / 2.0 < *(float *)(param_1 + 0x88)) {
    BtlEffRelease__7CBattleFiP6BtlEff(pCGpffff86b4,*(undefined4 *)(param_1 + 0x48),param_1);
    if ((long)((ulong)*(byte *)(param_1 + 0x40) << 0x3e) < 0) {
      iVar5 = param_1;
      if (param_1 != 0) {
        iVar5 = param_1 + 0x18;
      }
      ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,iVar5);
    }
    *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfd;
    (**(code **)(*(int *)(param_1 + 0x34) + 0xc))();
    uVar6 = 1;
  }
  else {
    if ((-1 < *(int *)(param_1 + 0x5c)) && (-1 < (long)((ulong)*(byte *)(param_1 + 0x40) << 0x3d)))
    {
      uVar3 = __ct__7FVectorFRC7FVector(auStack_d0,param_1 + 0x70);
      cVar1 = VSCircleHitCheck__7CBattleFi7FVectorfP7FVector
                        (0x3f800000,pCGpffff86b4,*(undefined4 *)(param_1 + 0x5c),uVar3,&fStack_10);
      if (cVar1 == '\x01') {
        if (0 < pCGpffff86b4->aChr[*(int *)(param_1 + 0x5c)].nHp) {
          pFVar2 = (FVector *)__ct__7FVectorFRC7FVector(auStack_e0,&fStack_10);
          PAtkHitSet__7CBattleFii7FVectorfiiiiUsUsfii
                    (pCGpffff86b4,*(int *)(param_1 + 0x48),*(int *)(param_1 + 0x5c),pFVar2,
                     *(float *)(param_1 + 0x94),*(int *)(param_1 + 0xa0),*(int *)(param_1 + 0xa4),
                     *(int *)(param_1 + 0xa8),*(int *)(param_1 + 0xac),*(ushort *)(param_1 + 0xb0),
                     *(ushort *)(param_1 + 0xb2),*(float *)(param_1 + 100),*(int *)(param_1 + 0xb4),
                     *(int *)(param_1 + 0xb8));
        }
        *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfb | 4;
      }
      else {
        uVar3 = __ct__7FVectorFRC7FVector(auStack_f0,param_1 + 0x70);
        uVar4 = __ct__7FVectorFRC7FVector(auStack_100,param_1 + 0x80);
        cVar1 = VSLineHitCheck__7CBattleFi7FVector7FVectorP7FVector
                          (pCGpffff86b4,*(undefined4 *)(param_1 + 0x5c),uVar3,uVar4,&fStack_10);
        if (cVar1 == '\x01') {
          if (0 < pCGpffff86b4->aChr[*(int *)(param_1 + 0x5c)].nHp) {
            pFVar2 = (FVector *)__ct__7FVectorFRC7FVector(auStack_110,&fStack_10);
            PAtkHitSet__7CBattleFii7FVectorfiiiiUsUsfii
                      (pCGpffff86b4,*(int *)(param_1 + 0x48),*(int *)(param_1 + 0x5c),pFVar2,
                       *(float *)(param_1 + 0x94),*(int *)(param_1 + 0xa0),*(int *)(param_1 + 0xa4),
                       *(int *)(param_1 + 0xa8),*(int *)(param_1 + 0xac),*(ushort *)(param_1 + 0xb0)
                       ,*(ushort *)(param_1 + 0xb2),*(float *)(param_1 + 100),
                       *(int *)(param_1 + 0xb4),*(int *)(param_1 + 0xb8));
          }
          *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfb | 4;
        }
      }
    }
    uVar6 = 0;
  }
  return uVar6;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0053d130  MakePacket__7Bullet1Fv
 * C++: Bullet1::MakePacket()
 * size: 0x4a4 bytes
 * --------------------------------------------------------------------------- */
void MakePacket__7Bullet1Fv(int param_1)

{
  bool bVar1;
  undefined4 *puVar2;
  bool bVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  int aiStack_d0 [4];
  int iStack_c0;
  int iStack_bc;
  int iStack_b8;
  undefined4 auStack_b0 [16];
  undefined4 auStack_70 [16];
  undefined4 auStack_30 [8];
  int iStack_10;
  
  iStack_10 = param_1;
  for (iVar5 = 0; iVar5 < 2; iVar5 = iVar5 + 1) {
    auStack_30[iVar5 * 4] = *(undefined4 *)(iStack_10 + iVar5 * 0x10 + 0x70);
    auStack_30[iVar5 * 4 + 1] = *(undefined4 *)(iStack_10 + iVar5 * 0x10 + 0x74);
    auStack_30[iVar5 * 4 + 2] = *(undefined4 *)(iStack_10 + iVar5 * 0x10 + 0x78);
    auStack_30[iVar5 * 4 + 3] = 0x3f800000;
  }
  GetViewScreenMatrix__9GsxCameraFv(auStack_70,uGpffff8598);
  for (iVar5 = 0; iVar5 < 4; iVar5 = iVar5 + 1) {
    auStack_b0[iVar5 * 4] = auStack_70[iVar5 * 4];
    auStack_b0[iVar5 * 4 + 1] = auStack_70[iVar5 * 4 + 1];
    auStack_b0[iVar5 * 4 + 2] = auStack_70[iVar5 * 4 + 2];
    auStack_b0[iVar5 * 4 + 3] = auStack_70[iVar5 * 4 + 3];
  }
  sceVu0RotTransPersN(aiStack_d0,auStack_b0,auStack_30,2,0);
  bVar3 = false;
  iVar5 = 0;
  for (iVar6 = 0; iVar6 < 2; iVar6 = iVar6 + 1) {
    if ((((aiStack_d0[iVar6 * 4] < 0) || (0x10000 < aiStack_d0[iVar6 * 4])) ||
        (aiStack_d0[iVar6 * 4 + 1] < 0)) ||
       ((0x10000 < aiStack_d0[iVar6 * 4 + 1] || (aiStack_d0[iVar6 * 4 + 2] < 0)))) {
      bVar3 = true;
    }
    aiStack_d0[iVar6 * 4 + 2] = (int)((float)aiStack_d0[iVar6 * 4 + 2] / 16.0);
    iVar5 = iVar5 + aiStack_d0[iVar6 * 4 + 2];
  }
  if (iVar5 < 0) {
    iVar5 = iVar5 + 1;
  }
  *(int *)(iStack_10 + 0x50) = iVar5 >> 1;
  bVar1 = (*(byte *)(iStack_10 + 0x40) & 1) == 0;
  uVar7 = (uint)bVar1;
  if (*(int *)(iStack_10 + uVar7 * 4 + 0x18) == 0) {
    uVar4 = __nwa__FUi(0x90);
    *(undefined4 *)(iStack_10 + uVar7 * 4 + 0x18) = uVar4;
    iVar5 = *(int *)(iStack_10 + uVar7 * 4 + 0x18);
    *(undefined8 *)(iVar5 + 0x10) = 0x2000000000000001;
    *(undefined8 *)(iVar5 + 0x18) = 0xee;
    *(undefined8 *)(iVar5 + 0x20) = 0x53001;
    *(undefined8 *)(iVar5 + 0x28) = 0x47;
    *(undefined8 *)(iVar5 + 0x30) = 0x48;
    *(undefined8 *)(iVar5 + 0x38) = 0x42;
    *(undefined8 *)(iVar5 + 0x40) = 0x6400000000008001;
    *(undefined8 *)(iVar5 + 0x48) = 0x41c1f0;
    *(undefined8 *)(iVar5 + 0x50) = 0x14a;
    *(undefined8 *)(iVar5 + 0x58) = 0;
    *(undefined8 *)(iVar5 + 0x60) = 0x1800080c0;
    *(undefined8 *)(iVar5 + 0x70) = 0x110001020;
  }
  puVar2 = *(undefined4 **)(iStack_10 + uVar7 * 4 + 0x18);
  if (bVar3) {
    *(undefined4 **)(iStack_10 + 0x54) = puVar2;
    *(byte *)(iStack_10 + 0x40) = *(byte *)(iStack_10 + 0x40) & 0xfe | bVar1;
  }
  else {
    *puVar2 = 0x10000007;
    puVar2[1] = 0;
    puVar2[2] = 0;
    puVar2[3] = 0x50000007;
    *(long *)(puVar2 + 0x1a) =
         (long)aiStack_d0[2] << 0x20 | (long)aiStack_d0[0] | (long)aiStack_d0[1] << 0x10;
    *(long *)(puVar2 + 0x1e) = (long)iStack_b8 << 0x20 | (long)iStack_c0 | (long)iStack_bc << 0x10;
    *(undefined4 **)(iStack_10 + 0x54) = puVar2 + 0x20;
    *(byte *)(iStack_10 + 0x40) = *(byte *)(iStack_10 + 0x40) & 0xfe | bVar1;
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054add0  EndSet__7Bullet1Fv
 * C++: Bullet1::EndSet()
 * size: 0x10 bytes
 * --------------------------------------------------------------------------- */
void EndSet__7Bullet1Fv(void)

{
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b8f0  @24@__dt__7Bullet1Fv
 * C++: @24@__dt__7Bullet1Fv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int * _24___dt__7Bullet1Fv(int *param_1,short param_2)

{
  int *piVar1;
  
  piVar1 = param_1 + -6;
  if (piVar1 != (int *)0x0) {
    param_1[-1] = 0x409ac0;
    param_1[4] = 0x409ad0;
    param_1[7] = 0x409ae0;
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
 * JP: 0x0054b900  @44@__dt__7Bullet1Fv
 * C++: @44@__dt__7Bullet1Fv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int _44___dt__7Bullet1Fv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x2c;
  if (iVar1 != 0) {
    *(undefined4 *)(param_1 + -0x18) = 0x409ac0;
    *(undefined4 *)(param_1 + -4) = 0x409ad0;
    *(undefined4 *)(param_1 + 8) = 0x409ae0;
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

