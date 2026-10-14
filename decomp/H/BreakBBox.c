/* decomp/H/BreakBBox.c — cleaned Ghidra output (SH2JP_BATTLE.BIN, JP Furokuban, base 0x00430a00).
 * 9 function(s). Types: see types.h. Names/gp globals resolved from symbols/SLPM_602.19.syms. */
#include "types.h"

/* ---------------------------------------------------------------------------
 * JP: 0x005483d0  __ct__9BreakBBoxFiii
 * C++: BreakBBox::__ct(int, int, int)
 * size: 0x784 bytes
 * --------------------------------------------------------------------------- */
undefined8
__ct__9BreakBBoxFiii(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  undefined4 uVar2;
  undefined8 uVar3;
  undefined4 *puVar4;
  int iVar5;
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  undefined1 auStack_1b0 [16];
  undefined1 auStack_1a0 [16];
  undefined4 uStack_190;
  undefined4 uStack_18c;
  undefined4 uStack_188;
  undefined4 uStack_184;
  undefined4 uStack_180;
  undefined4 uStack_17c;
  undefined4 auStack_160 [88];
  
  __ct__6BtlEffFii(param_1,param_2,param_3);
  iVar5 = (int)param_1;
  *(undefined4 *)(iVar5 + 0x14) = 0x409930;
  *(undefined4 *)(iVar5 + 0x28) = 0x409940;
  *(undefined4 *)(iVar5 + 0x34) = 0x409950;
  *(undefined4 *)(iVar5 + 0x40) = 0;
  *(int *)(iVar5 + 0x44) = (int)param_2;
  *(int *)(iVar5 + 0x48) = (int)param_3;
  *(undefined4 *)(iVar5 + 0x4c) = 8;
  *(undefined4 *)(iVar5 + 0x1c) = 0;
  *(undefined4 *)(iVar5 + 0x18) = 0;
  *(undefined4 *)(iVar5 + 0x54) = 0;
  *(undefined4 *)(iVar5 + 0x5c) = param_4;
  *(undefined4 *)(iVar5 + 0x60) =
       *(undefined4 *)
        (*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar5 + 0x48) * 0x4f0 + 0x144) + 0x60) + 4);
  if (*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar5 + 0x48) * 0x4f0 + 0x144) + 0x52c) != 0) {
    *(int *)(iVar5 + 0x60) =
         *(int *)(iVar5 + 0x60) +
         *(int *)(*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar5 + 0x48) * 0x4f0 + 0x144) +
                                   0x52c) + 0x60) + 4);
  }
  if (*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar5 + 0x48) * 0x4f0 + 0x144) + 0x530) != 0) {
    *(int *)(iVar5 + 0x60) =
         *(int *)(iVar5 + 0x60) +
         *(int *)(*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar5 + 0x48) * 0x4f0 + 0x144) +
                                   0x530) + 0x60) + 4);
  }
  *(int *)(iVar5 + 0x60) = *(int *)(iVar5 + 0x60) * 0xc;
  uVar2 = __nwa__FUi(*(int *)(iVar5 + 0x60) << 2);
  *(undefined4 *)(iVar5 + 100) = uVar2;
  iVar1 = *(int *)(iVar5 + 0x60);
  uVar3 = __nwa__FUi(iVar1 * 0x10 + 0x10);
  uVar2 = __construct_new_array(uVar3,0x548b80,0,0x10,iVar1);
  *(undefined4 *)(iVar5 + 0x68) = uVar2;
  iVar1 = *(int *)(iVar5 + 0x60);
  uVar3 = __nwa__FUi(iVar1 * 0x30 + 0x10);
  uVar2 = __construct_new_array(uVar3,0x548b80,0,0x10,iVar1 * 3);
  *(undefined4 *)(iVar5 + 0x6c) = uVar2;
  iVar1 = *(int *)(iVar5 + 0x60);
  uVar3 = __nwa__FUi(iVar1 * 0x10 + 0x10);
  uVar2 = __construct_new_array(uVar3,0x548b80,0,0x10,iVar1);
  *(undefined4 *)(iVar5 + 0x70) = uVar2;
  iVar1 = *(int *)(iVar5 + 0x60);
  uVar3 = __nwa__FUi(iVar1 * 4 + 0x10);
  uVar2 = __construct_new_array(uVar3,0x548b60,0,4,iVar1);
  *(undefined4 *)(iVar5 + 0x74) = uVar2;
  iVar1 = *(int *)(iVar5 + 0x60);
  uVar3 = __nwa__FUi(iVar1 * 0x10 + 0x10);
  uVar2 = __construct_new_array(uVar3,0x548b80,0,0x10,iVar1);
  *(undefined4 *)(iVar5 + 0x78) = uVar2;
  iVar1 = *(int *)(iVar5 + 0x60);
  uVar3 = __nwa__FUi(iVar1 * 0x10 + 0x10);
  uVar2 = __construct_new_array(uVar3,0x548b80,0,0x10,iVar1);
  *(undefined4 *)(iVar5 + 0x7c) = uVar2;
  *(undefined4 *)(iVar5 + 0x80) = 0x3f800000;
  puVar4 = auStack_160;
  do {
    *puVar4 = in_zero_lo;
    puVar4[1] = in_zero_hi;
    puVar4[2] = in_zero_udw;
    puVar4[3] = in_register_0000000c;
    puVar4 = puVar4 + 4;
  } while (puVar4 != auStack_160 + 0xc);
  puVar4 = auStack_160 + 0xc;
  do {
    *puVar4 = in_zero_lo;
    puVar4[1] = in_zero_hi;
    puVar4[2] = in_zero_udw;
    puVar4[3] = in_register_0000000c;
    puVar4 = puVar4 + 4;
  } while (puVar4 != auStack_160 + 0x18);
  puVar4 = auStack_160 + 0x18;
  do {
    *puVar4 = in_zero_lo;
    puVar4[1] = in_zero_hi;
    puVar4[2] = in_zero_udw;
    puVar4[3] = in_register_0000000c;
    puVar4 = puVar4 + 4;
  } while (puVar4 != (undefined4 *)&stack0x00000000);
  uStack_190 = 0xffffffff;
  uStack_18c = 0xffffffff;
  uStack_188 = 0xffffffff;
  uStack_184 = 0;
  uStack_180 = 0;
  uStack_17c = 0;
  auVar6 = _lqc2(*(undefined1 (*) [16])(iGpffff86b4 + *(int *)(iVar5 + 0x48) * 0x4f0 + 0x150));
  auVar7 = _lqc2(*(undefined1 (*) [16])(iGpffff86b4 + *(int *)(iVar5 + 0x48) * 0x4f0 + 0x350));
  auVar6 = _vadd(auVar6,auVar7);
  auStack_1b0 = _sqc2(auVar6);
  __ct__7FVectorFRC7FVector(auStack_1a0,auStack_1b0);
  uVar2 = Length__7FVectorCFv(iGpffff86b4 + *(int *)(iVar5 + 0x48) * 0x4f0 + 0x3a0);
  getLightMatrix__12LightControlFR7FVectorP9keepLightP7FVector(auStack_1a0,&uStack_190,0);
  uVar3 = InitParam__9BreakBBoxFiiP14_ModelBBoxDataP5FrameiP9keepLightf
                    (uVar2,param_1,0,
                     *(undefined4 *)
                      (*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar5 + 0x48) * 0x4f0 + 0x144) +
                               0x60) + 4),
                     *(undefined4 *)
                      (*(int *)(iGpffff86b4 + *(int *)(iVar5 + 0x48) * 0x4f0 + 0x144) + 0xe4),
                     *(undefined4 *)
                      (*(int *)(iGpffff86b4 + *(int *)(iVar5 + 0x48) * 0x4f0 + 0x144) + 0x30),
                     bGpffff8340 & 1,&uStack_190);
  if (*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar5 + 0x48) * 0x4f0 + 0x144) + 0x52c) != 0) {
    uVar3 = InitParam__9BreakBBoxFiiP14_ModelBBoxDataP5FrameiP9keepLightf
                      (uVar2,param_1,uVar3,
                       *(undefined4 *)
                        (*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar5 + 0x48) * 0x4f0 +
                                                   0x144) + 0x52c) + 0x60) + 4),
                       *(undefined4 *)
                        (*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar5 + 0x48) * 0x4f0 + 0x144) +
                                 0x52c) + 0xe4),
                       *(undefined4 *)
                        (*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar5 + 0x48) * 0x4f0 + 0x144) +
                                 0x52c) + 0x30),bGpffff8340 & 1,&uStack_190);
  }
  if (*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar5 + 0x48) * 0x4f0 + 0x144) + 0x530) != 0) {
    uVar3 = InitParam__9BreakBBoxFiiP14_ModelBBoxDataP5FrameiP9keepLightf
                      (uVar2,param_1,uVar3,
                       *(undefined4 *)
                        (*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar5 + 0x48) * 0x4f0 +
                                                   0x144) + 0x530) + 0x60) + 4),
                       *(undefined4 *)
                        (*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar5 + 0x48) * 0x4f0 + 0x144) +
                                 0x530) + 0xe4),
                       *(undefined4 *)
                        (*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar5 + 0x48) * 0x4f0 + 0x144) +
                                 0x530) + 0x30),bGpffff8340 & 1,&uStack_190);
  }
  *(int *)(iVar5 + 0x60) = (int)uVar3;
  Entry__7CPollerFP7CPolObjib(iGpffff858c + 0x48,param_1,0x80,0);
  BtlEffEntry__7CBattleFiP6BtlEff(iGpffff86b4,*(undefined4 *)(iVar5 + 0x48),param_1);
  return param_1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00548ba0  __dt__9BreakBBoxFv
 * C++: BreakBBox::__dt()
 * size: 0x254 bytes
 * --------------------------------------------------------------------------- */
int __dt__9BreakBBoxFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x14) = 0x409930;
    *(undefined4 *)(param_1 + 0x28) = 0x409940;
    *(undefined4 *)(param_1 + 0x34) = 0x409950;
    if (*(int *)(param_1 + 0x18) != 0) {
      __dla__FPv(*(undefined4 *)(param_1 + 0x18));
    }
    if (*(int *)(param_1 + 0x1c) != 0) {
      __dla__FPv(*(undefined4 *)(param_1 + 0x1c));
    }
    __dla__FPv(*(undefined4 *)(param_1 + 100));
    if (*(int *)(param_1 + 0x68) != 0) {
      __dla__FPv(*(int *)(param_1 + 0x68) + -0x10);
    }
    if (*(int *)(param_1 + 0x6c) != 0) {
      __dla__FPv(*(int *)(param_1 + 0x6c) + -0x10);
    }
    if (*(int *)(param_1 + 0x70) != 0) {
      __dla__FPv(*(int *)(param_1 + 0x70) + -0x10);
    }
    if (*(int *)(param_1 + 0x74) != 0) {
      __dla__FPv(*(int *)(param_1 + 0x74) + -0x10);
    }
    if (*(int *)(param_1 + 0x78) != 0) {
      __dla__FPv(*(int *)(param_1 + 0x78) + -0x10);
    }
    if (*(int *)(param_1 + 0x7c) != 0) {
      __dla__FPv(*(int *)(param_1 + 0x7c) + -0x10);
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
 * JP: 0x00548e00  Destruct__9BreakBBoxFv
 * C++: BreakBBox::Destruct()
 * size: 0xc8 bytes
 * --------------------------------------------------------------------------- */
void Destruct__9BreakBBoxFv(int param_1)

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
 * JP: 0x00548ed0  Polling__9BreakBBoxFv
 * C++: BreakBBox::Polling()
 * size: 0x3c0 bytes
 * --------------------------------------------------------------------------- */
undefined4 Polling__9BreakBBoxFv(int param_1)

{
  bool bVar1;
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  undefined8 *puVar2;
  undefined4 uVar3;
  undefined1 (*pauVar4) [16];
  float *pfVar5;
  int iVar6;
  int iVar7;
  float fVar8;
  float fVar9;
  undefined1 auVar10 [16];
  undefined1 auVar11 [16];
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  fVar9 = *(float *)(iGpffff86b4 + 0x38);
  if ((*(byte *)(iGpffff86b4 + 0x24) & 1) != 0) {
    fVar9 = 0.0;
  }
  fVar8 = fVar9 * 0.12;
  bVar1 = false;
  uStack_10 = in_zero_lo;
  uStack_c = in_zero_hi;
  uStack_8 = in_zero_udw;
  uStack_4 = in_register_0000000c;
  for (iVar7 = 0; iVar7 < *(int *)(param_1 + 0x60); iVar7 = iVar7 + 1) {
    if (*(int *)(*(int *)(param_1 + 100) + iVar7 * 4) == 0) {
      puVar2 = (undefined8 *)(*(int *)(param_1 + 0x78) + iVar7 * 0x10);
      uStack_8 = *(undefined4 *)(puVar2 + 1);
      uStack_4 = *(undefined4 *)((int)puVar2 + 0xc);
      uStack_10 = (undefined4)*puVar2;
      uStack_c = (undefined4)((ulong)*puVar2 >> 0x20);
      __amu__7FVectorFf(fVar9 * 30.0,&uStack_10);
      pauVar4 = (undefined1 (*) [16])(*(int *)(param_1 + 0x68) + iVar7 * 0x10);
      auVar10._4_4_ = uStack_c;
      auVar10._0_4_ = uStack_10;
      auVar10._8_4_ = uStack_8;
      auVar10._12_4_ = uStack_4;
      auVar11 = _lqc2(auVar10);
      auVar10 = _lqc2(*pauVar4);
      auVar10 = _vadd(auVar10,auVar11);
      auVar10 = _sqc2(auVar10);
      *pauVar4 = auVar10;
      puVar2 = (undefined8 *)(*(int *)(param_1 + 0x7c) + iVar7 * 0x10);
      uStack_8 = *(undefined4 *)(puVar2 + 1);
      uStack_4 = *(undefined4 *)((int)puVar2 + 0xc);
      uStack_10 = (undefined4)*puVar2;
      uStack_c = (undefined4)((ulong)*puVar2 >> 0x20);
      __amu__7FVectorFf(fVar9 * 30.0,&uStack_10);
      pauVar4 = (undefined1 (*) [16])(*(int *)(param_1 + 0x70) + iVar7 * 0x10);
      auVar11._4_4_ = uStack_c;
      auVar11._0_4_ = uStack_10;
      auVar11._8_4_ = uStack_8;
      auVar11._12_4_ = uStack_4;
      auVar11 = _lqc2(auVar11);
      auVar10 = _lqc2(*pauVar4);
      auVar10 = _vadd(auVar10,auVar11);
      auVar10 = _sqc2(auVar10);
      *pauVar4 = auVar10;
      while (*(float *)(*(int *)(param_1 + 0x70) + iVar7 * 0x10) < -3.1415927) {
        pfVar5 = (float *)(*(int *)(param_1 + 0x70) + iVar7 * 0x10);
        *pfVar5 = *pfVar5 + 6.2831855;
      }
      while (3.1415927 <= *(float *)(*(int *)(param_1 + 0x70) + iVar7 * 0x10)) {
        pfVar5 = (float *)(*(int *)(param_1 + 0x70) + iVar7 * 0x10);
        *pfVar5 = *pfVar5 - 6.2831855;
      }
      while (*(float *)(*(int *)(param_1 + 0x70) + iVar7 * 0x10 + 4) < -3.1415927) {
        iVar6 = *(int *)(param_1 + 0x70) + iVar7 * 0x10;
        *(float *)(iVar6 + 4) = *(float *)(iVar6 + 4) + 6.2831855;
      }
      while (3.1415927 <= *(float *)(*(int *)(param_1 + 0x70) + iVar7 * 0x10 + 4)) {
        iVar6 = *(int *)(param_1 + 0x70) + iVar7 * 0x10;
        *(float *)(iVar6 + 4) = *(float *)(iVar6 + 4) - 6.2831855;
      }
      iVar6 = *(int *)(param_1 + 0x78) + iVar7 * 0x10;
      *(float *)(iVar6 + 4) = *(float *)(iVar6 + 4) + fVar8 * 30.0;
      bVar1 = true;
    }
  }
  *(float *)(param_1 + 0x80) = *(float *)(param_1 + 0x80) - fVar9;
  if ((!bVar1) || (*(float *)(param_1 + 0x80) <= 0.0)) {
    BtlEffRelease__7CBattleFiP6BtlEff(iGpffff86b4,*(undefined4 *)(param_1 + 0x48),param_1);
    if ((long)((ulong)*(byte *)(param_1 + 0x40) << 0x3e) < 0) {
      iVar7 = param_1;
      if (param_1 != 0) {
        iVar7 = param_1 + 0x18;
      }
      ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,iVar7);
    }
    *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfd;
    (**(code **)(*(int *)(param_1 + 0x34) + 0xc))();
    uVar3 = 1;
  }
  else {
    uVar3 = 0;
  }
  return uVar3;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00549290  MakePacket__9BreakBBoxFv
 * C++: BreakBBox::MakePacket()
 * size: 0xabc bytes
 * --------------------------------------------------------------------------- */
void MakePacket__9BreakBBoxFv(int param_1)

{
  bool bVar1;
  int *piVar2;
  int iVar3;
  undefined4 uVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  long lVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  uint uVar13;
  undefined1 in_vf0 [16];
  undefined1 auVar14 [16];
  undefined1 auVar15 [16];
  undefined1 auVar16 [16];
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
  undefined4 auStack_80 [16];
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [16];
  undefined1 auStack_20 [16];
  undefined1 auStack_10 [16];
  
  auVar14 = _vmr32(in_vf0);
  auVar15 = _vmr32(auVar14);
  auVar16 = _vmr32(auVar15);
  auStack_10 = _sqc2(in_vf0);
  auStack_20 = _sqc2(auVar14);
  auStack_30 = _sqc2(auVar15);
  auStack_40 = _sqc2(auVar16);
  uVar5 = __nwa__FUi(*(undefined4 *)(param_1 + 0x60));
  iVar11 = *(int *)(param_1 + 0x60);
  uVar6 = __nwa__FUi(iVar11 * 0x30 + 0x10);
  lVar7 = __construct_new_array(uVar6,0x548b80,0,0x10,iVar11 * 3);
  uVar6 = __nwa__FUi(*(int *)(param_1 + 0x60) * 0x30);
  iVar11 = 0;
  for (iVar12 = 0; iVar10 = (int)lVar7, iVar12 < *(int *)(param_1 + 0x60); iVar12 = iVar12 + 1) {
    if (*(int *)(*(int *)(param_1 + 100) + iVar12 * 4) == 0) {
      auVar14 = _vmr32(in_vf0);
      auVar15 = _vmr32(auVar14);
      auVar16 = _vmr32(auVar15);
      auStack_10 = _sqc2(in_vf0);
      auStack_20 = _sqc2(auVar14);
      auStack_30 = _sqc2(auVar15);
      auStack_40 = _sqc2(auVar16);
      sceVu0RotMatrix(auStack_40,auStack_40,*(int *)(param_1 + 0x70) + iVar12 * 0x10);
      __amu__7FVectorFf(*(undefined4 *)(param_1 + 0x80),auStack_40);
      __amu__7FVectorFf(*(undefined4 *)(param_1 + 0x80),auStack_30);
      __amu__7FVectorFf(*(undefined4 *)(param_1 + 0x80),auStack_20);
      auStack_10 = *(undefined1 (*) [16])(*(int *)(param_1 + 0x68) + iVar12 * 0x10);
      RotTransVector(iVar10 + iVar11 * 0x30,*(int *)(param_1 + 0x6c) + iVar12 * 0x30,auStack_40,3);
      if (((*(float *)(iVar10 + iVar11 * 0x30 + 4) <= 0.0) ||
          (*(float *)(iVar10 + (iVar11 * 3 + 1) * 0x10 + 4) <= 0.0)) ||
         (*(float *)(iVar10 + (iVar11 * 3 + 2) * 0x10 + 4) <= 0.0)) {
        iVar11 = iVar11 + 1;
      }
      else {
        *(undefined4 *)(*(int *)(param_1 + 100) + iVar12 * 4) = 1;
      }
    }
  }
  if (iVar11 != 0) {
    GetViewScreenMatrix__9GsxCameraFv(&uStack_c0,uGpffff8598);
    auStack_40._4_4_ = uStack_bc;
    auStack_40._0_4_ = uStack_c0;
    auStack_40._8_4_ = uStack_b8;
    auStack_40._12_4_ = uStack_b4;
    auStack_30._4_4_ = uStack_ac;
    auStack_30._0_4_ = uStack_b0;
    auStack_30._8_4_ = uStack_a8;
    auStack_30._12_4_ = uStack_a4;
    auStack_20._4_4_ = uStack_9c;
    auStack_20._0_4_ = uStack_a0;
    auStack_20._8_4_ = uStack_98;
    auStack_20._12_4_ = uStack_94;
    auStack_10._4_4_ = uStack_8c;
    auStack_10._0_4_ = uStack_90;
    auStack_10._8_4_ = uStack_88;
    auStack_10._12_4_ = uStack_84;
    for (iVar12 = 0; iVar12 < 4; iVar12 = iVar12 + 1) {
      auStack_80[iVar12 * 4] = *(undefined4 *)(auStack_40 + iVar12 * 0x10);
      auStack_80[iVar12 * 4 + 1] = *(undefined4 *)(auStack_40 + iVar12 * 0x10 + 4);
      auStack_80[iVar12 * 4 + 2] = *(undefined4 *)(auStack_40 + iVar12 * 0x10 + 8);
      auStack_80[iVar12 * 4 + 3] = *(undefined4 *)(auStack_40 + iVar12 * 0x10 + 0xc);
    }
    sceVu0RotTransPersN(uVar6,auStack_80,lVar7,iVar11 * 3,0);
  }
  bVar1 = (*(byte *)(param_1 + 0x40) & 1) == 0;
  uVar13 = (uint)bVar1;
  iVar12 = 0;
  while( true ) {
    iVar9 = (int)uVar6;
    iVar3 = (int)uVar5;
    if (iVar11 <= iVar12) break;
    *(undefined1 *)(iVar3 + iVar12) = 1;
    if ((((-1 < *(int *)(iVar9 + iVar12 * 0x30)) && (*(int *)(iVar9 + iVar12 * 0x30) < 0x10000)) &&
        ((-1 < *(int *)(iVar9 + iVar12 * 0x30 + 4) &&
         ((*(int *)(iVar9 + iVar12 * 0x30 + 4) < 0x10000 &&
          (-1 < *(int *)(iVar9 + iVar12 * 0x30 + 8))))))) &&
       ((-1 < *(int *)(iVar9 + (iVar12 * 3 + 1) * 0x10) &&
        ((((((*(int *)(iVar9 + (iVar12 * 3 + 1) * 0x10) < 0x10000 &&
             (-1 < *(int *)(iVar9 + (iVar12 * 3 + 1) * 0x10 + 4))) &&
            (*(int *)(iVar9 + (iVar12 * 3 + 1) * 0x10 + 4) < 0x10000)) &&
           ((-1 < *(int *)(iVar9 + (iVar12 * 3 + 1) * 0x10 + 8) &&
            (-1 < *(int *)(iVar9 + (iVar12 * 3 + 2) * 0x10))))) &&
          ((*(int *)(iVar9 + (iVar12 * 3 + 2) * 0x10) < 0x10000 &&
           ((-1 < *(int *)(iVar9 + (iVar12 * 3 + 2) * 0x10 + 4) &&
            (*(int *)(iVar9 + (iVar12 * 3 + 2) * 0x10 + 4) < 0x10000)))))) &&
         (-1 < *(int *)(iVar9 + (iVar12 * 3 + 2) * 0x10 + 8))))))) {
      *(undefined1 *)(iVar3 + iVar12) = 0;
      iVar8 = iVar9 + iVar12 * 0x30;
      iVar3 = *(int *)(iVar8 + 8);
      if (iVar3 < 0) {
        iVar3 = iVar3 + 0xf;
      }
      *(int *)(iVar8 + 8) = iVar3 >> 4;
      iVar8 = iVar9 + (iVar12 * 3 + 1) * 0x10;
      iVar3 = *(int *)(iVar8 + 8);
      if (iVar3 < 0) {
        iVar3 = iVar3 + 0xf;
      }
      *(int *)(iVar8 + 8) = iVar3 >> 4;
      iVar9 = iVar9 + (iVar12 * 3 + 2) * 0x10;
      iVar3 = *(int *)(iVar9 + 8);
      if (iVar3 < 0) {
        iVar3 = iVar3 + 0xf;
      }
      *(int *)(iVar9 + 8) = iVar3 >> 4;
    }
    iVar12 = iVar12 + 1;
  }
  if (*(int *)(param_1 + uVar13 * 4 + 0x18) == 0) {
    uVar4 = __nwa__FUi((*(int *)(param_1 + 0x60) * 2 + 8) * 0x10);
    *(undefined4 *)(param_1 + uVar13 * 4 + 0x18) = uVar4;
    iVar12 = *(int *)(param_1 + uVar13 * 4 + 0x18);
    *(undefined8 *)(iVar12 + 0x10) = 0x2000000000000001;
    *(undefined8 *)(iVar12 + 0x18) = 0xee;
    *(undefined8 *)(iVar12 + 0x20) = 0x73000;
    *(undefined8 *)(iVar12 + 0x28) = 0x47;
    *(undefined8 *)(iVar12 + 0x30) = 0x44;
    *(undefined8 *)(iVar12 + 0x38) = 0x42;
    *(undefined8 *)(iVar12 + 0x40) = 0x2400000000000001;
    *(undefined8 *)(iVar12 + 0x48) = 0xf0;
    *(undefined8 *)(iVar12 + 0x50) = 0x43;
    *(undefined8 *)(iVar12 + 0x68) = 0x4cc1;
  }
  piVar2 = *(int **)(param_1 + uVar13 * 4 + 0x18);
  if (iVar11 == 0) {
    *(int **)(param_1 + 0x54) = piVar2;
    *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfe | bVar1;
    __dla__FPv(uVar5);
    if (lVar7 != 0) {
      __dla__FPv(iVar10 + -0x10);
    }
    __dla__FPv(uVar6);
  }
  else {
    *piVar2 = iVar11 * 2 + 0x10000006;
    piVar2[1] = 0;
    piVar2[2] = 0;
    piVar2[3] = iVar11 * 2 + 0x50000006;
    *(ulong *)(piVar2 + 0x18) = (long)iVar11 | 0x4400000000008000;
    for (iVar12 = 0; iVar12 < iVar11; iVar12 = iVar12 + 1) {
      if (*(char *)(iVar3 + iVar12) == '\0') {
        *(ulong *)(piVar2 + (iVar12 * 2 + 7) * 4) =
             (ulong)CONCAT13(*(undefined1 *)(*(int *)(param_1 + 0x74) + iVar12 * 4 + 3),
                             CONCAT12(*(undefined1 *)(*(int *)(param_1 + 0x74) + iVar12 * 4 + 2),
                                      CONCAT11(*(undefined1 *)
                                                (*(int *)(param_1 + 0x74) + iVar12 * 4 + 1),
                                               *(undefined1 *)
                                                (*(int *)(param_1 + 0x74) + iVar12 * 4))));
        *(long *)(piVar2 + (iVar12 * 2 + 7) * 4 + 2) =
             (long)*(int *)(iVar9 + iVar12 * 0x30 + 8) << 0x20 |
             (long)*(int *)(iVar9 + iVar12 * 0x30) |
             (long)*(int *)(iVar9 + iVar12 * 0x30 + 4) << 0x10;
        *(long *)(piVar2 + (iVar12 * 2 + 8) * 4) =
             (long)*(int *)(iVar9 + (iVar12 * 3 + 1) * 0x10 + 8) << 0x20 |
             (long)*(int *)(iVar9 + (iVar12 * 3 + 1) * 0x10) |
             (long)*(int *)(iVar9 + (iVar12 * 3 + 1) * 0x10 + 4) << 0x10;
        *(long *)(piVar2 + (iVar12 * 2 + 8) * 4 + 2) =
             (long)*(int *)(iVar9 + (iVar12 * 3 + 2) * 0x10 + 8) << 0x20 |
             (long)*(int *)(iVar9 + (iVar12 * 3 + 2) * 0x10) |
             (long)*(int *)(iVar9 + (iVar12 * 3 + 2) * 0x10 + 4) << 0x10;
      }
      else {
        (piVar2 + (iVar12 * 2 + 7) * 4 + 2)[0] = 0x71006f00;
        (piVar2 + (iVar12 * 2 + 7) * 4 + 2)[1] = 0;
        (piVar2 + (iVar12 * 2 + 8) * 4)[0] = 0x71006f00;
        (piVar2 + (iVar12 * 2 + 8) * 4)[1] = 0;
        (piVar2 + (iVar12 * 2 + 8) * 4 + 2)[0] = 0x71006f00;
        (piVar2 + (iVar12 * 2 + 8) * 4 + 2)[1] = 0;
      }
    }
    *(int **)(param_1 + 0x54) = piVar2 + (iVar11 * 2 + 7) * 4;
    *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfe | bVar1;
    __dla__FPv(uVar5);
    if (lVar7 != 0) {
      __dla__FPv(iVar10 + -0x10);
    }
    __dla__FPv(uVar6);
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00549d50  InitParam__9BreakBBoxFiiP14_ModelBBoxDataP5FrameiP9keepLightf
 * C++: BreakBBox::InitParam(int, int, _ModelBBoxData *, Frame *, int, keepLight *, float)
 * size: 0x1020 bytes
 * --------------------------------------------------------------------------- */
int InitParam__9BreakBBoxFiiP14_ModelBBoxDataP5FrameiP9keepLightf
              (float param_1,int param_2,int param_3,int param_4,int param_5,int param_6,int param_7
              ,int *param_8)

{
  char cVar1;
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
  int in_zero_lo;
  int in_zero_hi;
  int in_zero_udw;
  int in_register_0000000c;
  int iVar18;
  undefined1 (*pauVar19) [16];
  undefined4 *puVar20;
  undefined1 *puVar21;
  float *pfVar22;
  byte bVar23;
  int iVar24;
  int iVar25;
  float fVar26;
  float fVar27;
  undefined1 in_vf0 [16];
  undefined1 auVar28 [16];
  undefined1 auVar29 [16];
  undefined1 auVar30 [16];
  undefined1 auStack_430 [16];
  undefined1 auStack_420 [16];
  undefined1 auStack_410 [16];
  undefined1 auStack_400 [16];
  undefined1 auStack_3f0 [16];
  undefined1 auStack_3e0 [16];
  undefined1 auStack_3d0 [16];
  undefined1 auStack_3c0 [16];
  undefined1 auStack_3b0 [16];
  undefined1 auStack_3a0 [16];
  undefined1 auStack_390 [16];
  undefined1 auStack_380 [16];
  undefined1 auStack_370 [16];
  undefined1 auStack_360 [16];
  float fStack_350;
  float fStack_34c;
  undefined4 uStack_348;
  undefined4 uStack_344;
  float fStack_340;
  float fStack_33c;
  float fStack_338;
  undefined4 uStack_334;
  undefined4 uStack_330;
  undefined4 uStack_32c;
  undefined4 uStack_328;
  undefined4 uStack_324;
  undefined4 uStack_320;
  undefined4 uStack_31c;
  undefined4 uStack_318;
  undefined4 uStack_314;
  int iStack_310;
  int iStack_30c;
  int iStack_308;
  int iStack_304;
  undefined4 uStack_300;
  undefined4 uStack_2fc;
  undefined4 uStack_2f8;
  undefined4 uStack_2f4;
  undefined4 uStack_2f0;
  undefined4 uStack_2ec;
  undefined4 uStack_2e8;
  undefined4 uStack_2e4;
  undefined4 uStack_2e0;
  undefined4 uStack_2dc;
  undefined4 uStack_2d8;
  undefined4 uStack_2d4;
  undefined4 uStack_2d0;
  undefined4 uStack_2cc;
  undefined4 uStack_2c8;
  undefined4 uStack_2c4;
  undefined1 auStack_2c0 [16];
  undefined4 uStack_2b0;
  undefined4 uStack_2ac;
  undefined4 uStack_2a8;
  undefined4 uStack_2a4;
  undefined1 auStack_2a0 [16];
  undefined1 auStack_290 [16];
  undefined1 auStack_280 [16];
  undefined1 auStack_270 [16];
  undefined1 auStack_260 [16];
  undefined1 auStack_250 [16];
  int iStack_240;
  int iStack_23c;
  int iStack_238;
  int iStack_234;
  int iStack_230;
  int iStack_22c;
  int iStack_228;
  int iStack_224;
  int iStack_220;
  int iStack_21c;
  int iStack_218;
  int iStack_214;
  int iStack_210;
  int iStack_20c;
  int iStack_208;
  int iStack_204;
  int iStack_200;
  int iStack_1fc;
  int iStack_1f8;
  int iStack_1f4;
  int iStack_1f0;
  int iStack_1ec;
  int iStack_1e8;
  int iStack_1e4;
  int iStack_1e0;
  int iStack_1dc;
  int iStack_1d8;
  int iStack_1d4;
  undefined4 uStack_1d0;
  undefined4 uStack_1cc;
  undefined4 uStack_1c8;
  undefined4 uStack_1c4;
  undefined4 uStack_1c0;
  undefined4 uStack_1bc;
  undefined4 uStack_1b8;
  undefined4 uStack_1b4;
  undefined4 uStack_1b0;
  undefined4 uStack_1ac;
  undefined4 uStack_1a8;
  undefined4 uStack_1a4;
  undefined8 uStack_1a0;
  undefined4 uStack_198;
  undefined1 auStack_190 [8];
  float fStack_188;
  int iStack_184;
  int iStack_180;
  int iStack_17c;
  int iStack_178;
  int iStack_174;
  int iStack_170;
  int iStack_16c;
  int iStack_168;
  int iStack_164;
  int iStack_e0;
  int iStack_dc;
  int iStack_d8;
  int iStack_d4;
  int iStack_d0;
  int iStack_cc;
  int iStack_c8;
  int iStack_c4;
  int iStack_c0;
  int iStack_bc;
  int iStack_b8;
  int iStack_b4;
  int iStack_b0;
  int iStack_ac;
  int iStack_a8;
  int iStack_a4;
  int iStack_a0;
  int iStack_9c;
  int iStack_98;
  int iStack_94;
  int iStack_90;
  int iStack_8c;
  int iStack_88;
  int iStack_84;
  int iStack_80;
  int iStack_7c;
  int iStack_78;
  int iStack_74;
  int iStack_70;
  int iStack_6c;
  int iStack_68;
  int iStack_64;
  int iStack_60;
  int iStack_5c;
  int iStack_58;
  int iStack_54;
  undefined1 auStack_50 [16];
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [16];
  undefined1 auStack_20 [16];
  undefined1 uStack_8;
  undefined1 uStack_7;
  undefined1 uStack_6;
  undefined1 uStack_5;
  undefined1 uStack_4;
  undefined1 uStack_3;
  undefined1 uStack_2;
  undefined1 uStack_1;
  
  auVar28 = _vmr32(in_vf0);
  auVar29 = _vmr32(auVar28);
  auVar30 = _vmr32(auVar29);
  _sqc2(in_vf0);
  _sqc2(auVar28);
  _sqc2(auVar29);
  _sqc2(auVar30);
  auStack_190._4_4_ = in_zero_hi;
  auStack_190._0_4_ = in_zero_lo;
  fStack_188 = (float)in_zero_udw;
  iStack_184 = in_register_0000000c;
  uStack_1d0 = (undefined4)uRam00650df0;
  uStack_1cc = (undefined4)((ulong)uRam00650df0 >> 0x20);
  uStack_1c8 = uRam00650df8;
  uStack_1c4 = uRam00650dfc;
  uStack_1c0 = uRam00650e00;
  uStack_1bc = uRam00650e04;
  uStack_1b8 = uRam00650e08;
  uStack_1b4 = uRam00650e0c;
  uStack_1b0 = uRam00650e10;
  uStack_1ac = uRam00650e14;
  uStack_1a8 = uRam00650e18;
  uStack_1a4 = uRam00650e1c;
  uStack_1a0 = uRam00650e20;
  uStack_198 = uRam00650e28;
  iStack_204 = param_8[0x30];
  iStack_208 = param_8[0x2c];
  iStack_20c = param_8[0x28];
  iStack_210 = param_8[0x24];
  iStack_214 = param_8[0x31];
  iStack_218 = param_8[0x2d];
  iStack_21c = param_8[0x29];
  iStack_220 = param_8[0x25];
  iStack_224 = param_8[0x32];
  iStack_228 = param_8[0x2e];
  iStack_22c = param_8[0x2a];
  iStack_230 = param_8[0x26];
  param_1 = param_1 / 7.4;
  iStack_200 = iStack_210;
  iStack_1fc = iStack_20c;
  iStack_1f8 = iStack_208;
  iStack_1f4 = iStack_204;
  iStack_1f0 = iStack_220;
  iStack_1ec = iStack_21c;
  iStack_1e8 = iStack_218;
  iStack_1e4 = iStack_214;
  iStack_1e0 = iStack_230;
  iStack_1dc = iStack_22c;
  iStack_1d8 = iStack_228;
  iStack_1d4 = iStack_224;
  iStack_180 = in_zero_lo;
  iStack_17c = in_zero_hi;
  iStack_178 = in_zero_udw;
  iStack_174 = in_register_0000000c;
  iStack_170 = in_zero_lo;
  iStack_16c = in_zero_hi;
  iStack_168 = in_zero_udw;
  iStack_164 = in_register_0000000c;
  iStack_e0 = in_zero_lo;
  iStack_dc = in_zero_hi;
  iStack_d8 = in_zero_udw;
  iStack_d4 = in_register_0000000c;
  iStack_d0 = in_zero_lo;
  iStack_cc = in_zero_hi;
  iStack_c8 = in_zero_udw;
  iStack_c4 = in_register_0000000c;
  iStack_c0 = in_zero_lo;
  iStack_bc = in_zero_hi;
  iStack_b8 = in_zero_udw;
  iStack_b4 = in_register_0000000c;
  iStack_b0 = in_zero_lo;
  iStack_ac = in_zero_hi;
  iStack_a8 = in_zero_udw;
  iStack_a4 = in_register_0000000c;
  iStack_a0 = in_zero_lo;
  iStack_9c = in_zero_hi;
  iStack_98 = in_zero_udw;
  iStack_94 = in_register_0000000c;
  iStack_90 = in_zero_lo;
  iStack_8c = in_zero_hi;
  iStack_88 = in_zero_udw;
  iStack_84 = in_register_0000000c;
  iStack_80 = in_zero_lo;
  iStack_7c = in_zero_hi;
  iStack_78 = in_zero_udw;
  iStack_74 = in_register_0000000c;
  iStack_70 = in_zero_lo;
  iStack_6c = in_zero_hi;
  iStack_68 = in_zero_udw;
  iStack_64 = in_register_0000000c;
  iStack_60 = in_zero_lo;
  iStack_5c = in_zero_hi;
  iStack_58 = in_zero_udw;
  iStack_54 = in_register_0000000c;
  for (iVar25 = 0; iVar25 < param_4; iVar25 = iVar25 + 1) {
    if (((*(float *)(param_5 + iVar25 * 0x110 + 0x10) != 0.0) ||
        (*(float *)(param_5 + iVar25 * 0x110 + 0x14) != 0.0)) ||
       (*(float *)(param_5 + iVar25 * 0x110 + 0x18) != 0.0)) {
      pauVar19 = (undefined1 (*) [16])
                 (param_6 + (uint)*(byte *)(param_5 + iVar25 * 0x110) * 0x1f0 + param_7 * 0x40);
      auStack_50 = *pauVar19;
      auStack_40 = pauVar19[1];
      auStack_30 = pauVar19[2];
      auStack_20 = pauVar19[3];
      RotTransVector(&iStack_e0,param_5 + iVar25 * 0x110 + 0x10,auStack_50,8);
      auVar28._4_4_ = iStack_dc;
      auVar28._0_4_ = iStack_e0;
      auVar28._8_4_ = iStack_d8;
      auVar28._12_4_ = iStack_d4;
      auVar28 = _lqc2(auVar28);
      auVar29._4_4_ = iStack_cc;
      auVar29._0_4_ = iStack_d0;
      auVar29._8_4_ = iStack_c8;
      auVar29._12_4_ = iStack_c4;
      auVar29 = _lqc2(auVar29);
      auVar28 = _vadd(auVar28,auVar29);
      auStack_3d0 = _sqc2(auVar28);
      __ct__7FVectorFRC7FVector(auStack_2a0,auStack_3d0);
      auVar28 = _lqc2(auStack_2a0);
      auVar30._4_4_ = iStack_bc;
      auVar30._0_4_ = iStack_c0;
      auVar30._8_4_ = iStack_b8;
      auVar30._12_4_ = iStack_b4;
      auVar29 = _lqc2(auVar30);
      auVar28 = _vadd(auVar28,auVar29);
      auStack_3e0 = _sqc2(auVar28);
      __ct__7FVectorFRC7FVector(auStack_290,auStack_3e0);
      auVar28 = _lqc2(auStack_290);
      auVar12._4_4_ = iStack_ac;
      auVar12._0_4_ = iStack_b0;
      auVar12._8_4_ = iStack_a8;
      auVar12._12_4_ = iStack_a4;
      auVar29 = _lqc2(auVar12);
      auVar28 = _vadd(auVar28,auVar29);
      auStack_3f0 = _sqc2(auVar28);
      __ct__7FVectorFRC7FVector(auStack_280,auStack_3f0);
      auVar28 = _lqc2(auStack_280);
      auVar13._4_4_ = iStack_9c;
      auVar13._0_4_ = iStack_a0;
      auVar13._8_4_ = iStack_98;
      auVar13._12_4_ = iStack_94;
      auVar29 = _lqc2(auVar13);
      auVar28 = _vadd(auVar28,auVar29);
      auStack_400 = _sqc2(auVar28);
      __ct__7FVectorFRC7FVector(auStack_270,auStack_400);
      auVar28 = _lqc2(auStack_270);
      auVar14._4_4_ = iStack_8c;
      auVar14._0_4_ = iStack_90;
      auVar14._8_4_ = iStack_88;
      auVar14._12_4_ = iStack_84;
      auVar29 = _lqc2(auVar14);
      auVar28 = _vadd(auVar28,auVar29);
      auStack_410 = _sqc2(auVar28);
      __ct__7FVectorFRC7FVector(auStack_260,auStack_410);
      auVar28 = _lqc2(auStack_260);
      auVar15._4_4_ = iStack_7c;
      auVar15._0_4_ = iStack_80;
      auVar15._8_4_ = iStack_78;
      auVar15._12_4_ = iStack_74;
      auVar29 = _lqc2(auVar15);
      auVar28 = _vadd(auVar28,auVar29);
      auStack_420 = _sqc2(auVar28);
      __ct__7FVectorFRC7FVector(auStack_250,auStack_420);
      auVar28 = _lqc2(auStack_250);
      auVar16._4_4_ = iStack_6c;
      auVar16._0_4_ = iStack_70;
      auVar16._8_4_ = iStack_68;
      auVar16._12_4_ = iStack_64;
      auVar29 = _lqc2(auVar16);
      auVar28 = _vadd(auVar28,auVar29);
      auStack_360 = _sqc2(auVar28);
      __ct__7FVectorFRC7FVector(&iStack_240,auStack_360);
      iStack_60 = iStack_240;
      iStack_5c = iStack_23c;
      iStack_58 = iStack_238;
      iStack_54 = iStack_234;
      __adv__7FVectorFf(0x41000000,&iStack_60);
      for (iVar24 = param_3; iVar24 < param_3 + 0xc; iVar24 = iVar24 + 1) {
        *(undefined4 *)(*(int *)(param_2 + 100) + iVar24 * 4) = 0;
        cVar1 = *(char *)((int)&uStack_1d0 + (iVar24 - param_3) * 5 + 2);
        auVar28 = _lqc2(*(undefined1 (*) [16])
                         (&iStack_e0 + *(char *)((int)&uStack_1d0 + (iVar24 - param_3) * 5) * 4));
        auVar29 = _lqc2(*(undefined1 (*) [16])
                         (&iStack_e0 + *(char *)((int)&uStack_1d0 + (iVar24 - param_3) * 5 + 1) * 4)
                       );
        auVar28 = _vadd(auVar28,auVar29);
        auStack_430 = _sqc2(auVar28);
        __ct__7FVectorFRC7FVector(auStack_2c0,auStack_430);
        auVar28 = _lqc2(auStack_2c0);
        auVar29 = _lqc2(*(undefined1 (*) [16])(&iStack_e0 + cVar1 * 4));
        auVar28 = _vadd(auVar28,auVar29);
        auStack_370 = _sqc2(auVar28);
        __ct__7FVectorFRC7FVector(&uStack_2b0,auStack_370);
        puVar20 = (undefined4 *)(*(int *)(param_2 + 0x68) + iVar24 * 0x10);
        *puVar20 = uStack_2b0;
        puVar20[1] = uStack_2ac;
        puVar20[2] = uStack_2a8;
        puVar20[3] = uStack_2a4;
        __adv__7FVectorFf(0x40400000,*(int *)(param_2 + 0x68) + iVar24 * 0x10);
        auVar28 = _lqc2(*(undefined1 (*) [16])
                         (&iStack_e0 + *(char *)((int)&uStack_1d0 + (iVar24 - param_3) * 5) * 4));
        auVar29 = _lqc2(*(undefined1 (*) [16])(*(int *)(param_2 + 0x68) + iVar24 * 0x10));
        auVar28 = _vsub(auVar28,auVar29);
        auStack_380 = _sqc2(auVar28);
        __ct__7FVectorFRC7FVector(&uStack_2d0,auStack_380);
        puVar20 = (undefined4 *)(*(int *)(param_2 + 0x6c) + iVar24 * 0x30);
        *puVar20 = uStack_2d0;
        puVar20[1] = uStack_2cc;
        puVar20[2] = uStack_2c8;
        puVar20[3] = uStack_2c4;
        auVar28 = _lqc2(*(undefined1 (*) [16])
                         (&iStack_e0 + *(char *)((int)&uStack_1d0 + (iVar24 - param_3) * 5 + 1) * 4)
                       );
        auVar29 = _lqc2(*(undefined1 (*) [16])(*(int *)(param_2 + 0x68) + iVar24 * 0x10));
        auVar28 = _vsub(auVar28,auVar29);
        auStack_390 = _sqc2(auVar28);
        __ct__7FVectorFRC7FVector(&uStack_2e0,auStack_390);
        puVar20 = (undefined4 *)(*(int *)(param_2 + 0x6c) + (iVar24 * 3 + 1) * 0x10);
        *puVar20 = uStack_2e0;
        puVar20[1] = uStack_2dc;
        puVar20[2] = uStack_2d8;
        puVar20[3] = uStack_2d4;
        auVar28 = _lqc2(*(undefined1 (*) [16])
                         (&iStack_e0 + *(char *)((int)&uStack_1d0 + (iVar24 - param_3) * 5 + 2) * 4)
                       );
        auVar29 = _lqc2(*(undefined1 (*) [16])(*(int *)(param_2 + 0x68) + iVar24 * 0x10));
        auVar28 = _vsub(auVar28,auVar29);
        auStack_3a0 = _sqc2(auVar28);
        __ct__7FVectorFRC7FVector(&uStack_2f0,auStack_3a0);
        puVar20 = (undefined4 *)(*(int *)(param_2 + 0x6c) + (iVar24 * 3 + 2) * 0x10);
        *puVar20 = uStack_2f0;
        puVar20[1] = uStack_2ec;
        puVar20[2] = uStack_2e8;
        puVar20[3] = uStack_2e4;
        fVar26 = (float)Length__7FVectorCFv(*(int *)(param_2 + 0x6c) + iVar24 * 0x30);
        if (param_1 < fVar26) {
          Normalize__7FVectorFv(*(int *)(param_2 + 0x6c) + iVar24 * 0x30);
          __amu__7FVectorFf(param_1,*(int *)(param_2 + 0x6c) + iVar24 * 0x30);
        }
        fVar26 = (float)Length__7FVectorCFv(*(int *)(param_2 + 0x6c) + (iVar24 * 3 + 1) * 0x10);
        if (param_1 < fVar26) {
          Normalize__7FVectorFv(*(int *)(param_2 + 0x6c) + (iVar24 * 3 + 1) * 0x10);
          __amu__7FVectorFf(param_1,*(int *)(param_2 + 0x6c) + (iVar24 * 3 + 1) * 0x10);
        }
        fVar26 = (float)Length__7FVectorCFv(*(int *)(param_2 + 0x6c) + (iVar24 * 3 + 2) * 0x10);
        if (param_1 < fVar26) {
          Normalize__7FVectorFv(*(int *)(param_2 + 0x6c) + (iVar24 * 3 + 2) * 0x10);
          __amu__7FVectorFf(param_1,*(int *)(param_2 + 0x6c) + (iVar24 * 3 + 2) * 0x10);
        }
        uStack_300 = 0;
        uStack_2fc = 0;
        uStack_2f8 = 0;
        uStack_2f4 = 0x3f800000;
        puVar20 = (undefined4 *)(*(int *)(param_2 + 0x70) + iVar24 * 0x10);
        *puVar20 = 0;
        puVar20[1] = 0;
        puVar20[2] = 0;
        puVar20[3] = 0x3f800000;
        auVar28 = _lqc2(*(undefined1 (*) [16])
                         (&iStack_e0 + *(char *)((int)&uStack_1d0 + (iVar24 - param_3) * 5 + 3) * 4)
                       );
        auVar29 = _lqc2(*(undefined1 (*) [16])
                         (&iStack_e0 + *(char *)((int)&uStack_1cc + (iVar24 - param_3) * 5) * 4));
        auVar28 = _vsub(auVar28,auVar29);
        auStack_3b0 = _sqc2(auVar28);
        __ct__7FVectorFRC7FVector(&iStack_310,auStack_3b0);
        iStack_170 = iStack_310;
        iStack_16c = iStack_30c;
        iStack_168 = iStack_308;
        iStack_164 = iStack_304;
        Normalize__7FVectorFv(&iStack_170);
        uStack_320 = 0;
        uStack_31c = 0;
        uStack_318 = 0;
        uStack_314 = 0x3f800000;
        _auStack_190 = ZEXT812(0);
        iStack_184 = 0x3f800000;
        bVar23 = -1 < *param_8;
        if ((bool)bVar23) {
          auVar9._4_4_ = iStack_16c;
          auVar9._0_4_ = iStack_170;
          auVar9._8_4_ = iStack_168;
          auVar9._12_4_ = iStack_164;
          auVar28 = _lqc2(auVar9);
          auVar3._4_4_ = iStack_1fc;
          auVar3._0_4_ = iStack_200;
          auVar3._8_4_ = iStack_1f8;
          auVar3._12_4_ = iStack_1f4;
          auVar29 = _lqc2(auVar3);
          auVar28 = _vmul(auVar28,auVar29);
          auVar28 = _vaddbc(auVar28,auVar28);
          auVar28 = _vaddbc(auVar28,auVar28);
          auVar28 = _qmfc2(auVar28._0_4_);
          iStack_180 = param_8[0x34];
          iStack_17c = param_8[0x35];
          iStack_178 = param_8[0x36];
          iStack_174 = param_8[0x37];
          __amu__7FVectorFf(auVar28._0_4_ / 2.0 + 0.5,&iStack_180);
          auVar6._4_4_ = iStack_17c;
          auVar6._0_4_ = iStack_180;
          auVar6._8_4_ = iStack_178;
          auVar6._12_4_ = iStack_174;
          auVar29 = _lqc2(auVar6);
          auVar28 = _lqc2(_auStack_190);
          auVar28 = _vadd(auVar28,auVar29);
          _auStack_190 = _sqc2(auVar28);
        }
        if (-1 < param_8[1]) {
          auVar10._4_4_ = iStack_16c;
          auVar10._0_4_ = iStack_170;
          auVar10._8_4_ = iStack_168;
          auVar10._12_4_ = iStack_164;
          auVar28 = _lqc2(auVar10);
          auVar4._4_4_ = iStack_1ec;
          auVar4._0_4_ = iStack_1f0;
          auVar4._8_4_ = iStack_1e8;
          auVar4._12_4_ = iStack_1e4;
          auVar29 = _lqc2(auVar4);
          auVar28 = _vmul(auVar28,auVar29);
          auVar28 = _vaddbc(auVar28,auVar28);
          auVar28 = _vaddbc(auVar28,auVar28);
          auVar28 = _qmfc2(auVar28._0_4_);
          iStack_180 = param_8[0x38];
          iStack_17c = param_8[0x39];
          iStack_178 = param_8[0x3a];
          iStack_174 = param_8[0x3b];
          __amu__7FVectorFf(auVar28._0_4_ / 2.0 + 0.5,&iStack_180);
          auVar7._4_4_ = iStack_17c;
          auVar7._0_4_ = iStack_180;
          auVar7._8_4_ = iStack_178;
          auVar7._12_4_ = iStack_174;
          auVar29 = _lqc2(auVar7);
          auVar28 = _lqc2(_auStack_190);
          auVar28 = _vadd(auVar28,auVar29);
          _auStack_190 = _sqc2(auVar28);
          bVar23 = bVar23 + 1;
        }
        if (-1 < param_8[2]) {
          auVar11._4_4_ = iStack_16c;
          auVar11._0_4_ = iStack_170;
          auVar11._8_4_ = iStack_168;
          auVar11._12_4_ = iStack_164;
          auVar28 = _lqc2(auVar11);
          auVar5._4_4_ = iStack_1dc;
          auVar5._0_4_ = iStack_1e0;
          auVar5._8_4_ = iStack_1d8;
          auVar5._12_4_ = iStack_1d4;
          auVar29 = _lqc2(auVar5);
          auVar28 = _vmul(auVar28,auVar29);
          auVar28 = _vaddbc(auVar28,auVar28);
          auVar28 = _vaddbc(auVar28,auVar28);
          auVar28 = _qmfc2(auVar28._0_4_);
          iStack_180 = param_8[0x3c];
          iStack_17c = param_8[0x3d];
          iStack_178 = param_8[0x3e];
          iStack_174 = param_8[0x3f];
          __amu__7FVectorFf(auVar28._0_4_ / 2.0 + 0.5,&iStack_180);
          auVar8._4_4_ = iStack_17c;
          auVar8._0_4_ = iStack_180;
          auVar8._8_4_ = iStack_178;
          auVar8._12_4_ = iStack_174;
          auVar29 = _lqc2(auVar8);
          auVar28 = _lqc2(_auStack_190);
          auVar28 = _vadd(auVar28,auVar29);
          _auStack_190 = _sqc2(auVar28);
          bVar23 = bVar23 + 1;
        }
        __adv__7FVectorFf((float)bVar23,auStack_190);
        auVar29 = _lqc2(*(undefined1 (*) [16])(param_8 + 0x40));
        auVar28 = _lqc2(_auStack_190);
        auVar28 = _vadd(auVar28,auVar29);
        _auStack_190 = _sqc2(auVar28);
        if (*(int *)(param_2 + 0x5c) == 1) {
          fVar26 = fStack_188 * 255.0;
          if (fVar26 < 2.1474836e+09) {
            uStack_6 = (undefined1)(int)fVar26;
          }
          else {
            uStack_6 = (undefined1)(int)(fVar26 - 2.1474836e+09);
          }
          fVar26 = (float)auStack_190._4_4_ * 255.0;
          if (fVar26 < 2.1474836e+09) {
            uStack_7 = (undefined1)(int)fVar26;
          }
          else {
            uStack_7 = (undefined1)(int)(fVar26 - 2.1474836e+09);
          }
          fVar26 = (float)auStack_190._0_4_ * 255.0;
          if (2.1474836e+09 <= fVar26) {
            fVar26 = fVar26 - 2.1474836e+09;
          }
          uStack_8 = (undefined1)(int)fVar26;
          uStack_5 = 0x80;
          puVar21 = (undefined1 *)(*(int *)(param_2 + 0x74) + iVar24 * 4);
          *puVar21 = uStack_8;
          puVar21[1] = uStack_7;
          puVar21[2] = uStack_6;
          puVar21[3] = 0x80;
        }
        else if (*(int *)(param_2 + 0x5c) == 0) {
          fVar26 = fStack_188 * 128.0;
          if (fVar26 < 2.1474836e+09) {
            uStack_2 = (undefined1)(int)fVar26;
          }
          else {
            uStack_2 = (undefined1)(int)(fVar26 - 2.1474836e+09);
          }
          fVar26 = (float)auStack_190._4_4_ * 128.0;
          if (fVar26 < 2.1474836e+09) {
            uStack_3 = (undefined1)(int)fVar26;
          }
          else {
            uStack_3 = (undefined1)(int)(fVar26 - 2.1474836e+09);
          }
          fVar26 = (float)auStack_190._0_4_ * 128.0;
          if (2.1474836e+09 <= fVar26) {
            fVar26 = fVar26 - 2.1474836e+09;
          }
          uStack_4 = (undefined1)(int)fVar26;
          uStack_1 = 0x80;
          puVar21 = (undefined1 *)(*(int *)(param_2 + 0x74) + iVar24 * 4);
          *puVar21 = uStack_4;
          puVar21[1] = uStack_3;
          puVar21[2] = uStack_2;
          puVar21[3] = 0x80;
        }
        auVar28 = _lqc2(*(undefined1 (*) [16])(*(int *)(param_2 + 0x68) + iVar24 * 0x10));
        auVar17._4_4_ = iStack_5c;
        auVar17._0_4_ = iStack_60;
        auVar17._8_4_ = iStack_58;
        auVar17._12_4_ = iStack_54;
        auVar29 = _lqc2(auVar17);
        auVar28 = _vsub(auVar28,auVar29);
        auStack_3c0 = _sqc2(auVar28);
        __ct__7FVectorFRC7FVector(&uStack_330,auStack_3c0);
        puVar20 = (undefined4 *)(*(int *)(param_2 + 0x78) + iVar24 * 0x10);
        *puVar20 = uStack_330;
        puVar20[1] = uStack_32c;
        puVar20[2] = uStack_328;
        puVar20[3] = uStack_324;
        iVar18 = rand();
        fVar26 = ((float)iVar18 / 2.1474836e+09) * 0.1 + 0.35;
        iVar18 = rand();
        fVar27 = ((float)iVar18 / 2.1474836e+09) * 0.1 + 0.45;
        iVar18 = rand();
        fStack_340 = ((float)iVar18 / 2.1474836e+09) * 0.1 + 0.35;
        uStack_334 = 0x3f800000;
        pauVar19 = (undefined1 (*) [16])(*(int *)(param_2 + 0x78) + iVar24 * 0x10);
        auVar2._4_4_ = fVar27;
        auVar2._0_4_ = fStack_340;
        auVar2._8_4_ = fVar26;
        auVar2._12_4_ = 0x3f800000;
        auVar29 = _lqc2(auVar2);
        auVar28 = _lqc2(*pauVar19);
        auVar28 = _vmul(auVar28,auVar29);
        auVar28 = _sqc2(auVar28);
        *pauVar19 = auVar28;
        fStack_33c = fVar27;
        fStack_338 = fVar26;
        iVar18 = rand();
        fVar26 = ((float)iVar18 / 2.1474836e+09) * 2.0 - 1.0;
        iVar18 = rand();
        fStack_350 = ((float)iVar18 / 2.1474836e+09) * 2.0 - 1.0;
        uStack_348 = 0;
        uStack_344 = 0x3f800000;
        pfVar22 = (float *)(*(int *)(param_2 + 0x7c) + iVar24 * 0x10);
        *pfVar22 = fStack_350;
        pfVar22[1] = fVar26;
        pfVar22[2] = 0.0;
        pfVar22[3] = 1.0;
        fStack_34c = fVar26;
      }
      param_3 = param_3 + 0xc;
    }
  }
  return param_3;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054ad70  EndSet__9BreakBBoxFv
 * C++: BreakBBox::EndSet()
 * size: 0x10 bytes
 * --------------------------------------------------------------------------- */
void EndSet__9BreakBBoxFv(void)

{
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b9a0  @24@__dt__9BreakBBoxFv
 * C++: @24@__dt__9BreakBBoxFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int * _24___dt__9BreakBBoxFv(int *param_1,short param_2)

{
  int *piVar1;
  
  piVar1 = param_1 + -6;
  if (piVar1 != (int *)0x0) {
    param_1[-1] = 0x409930;
    param_1[4] = 0x409940;
    param_1[7] = 0x409950;
    if (*param_1 != 0) {
      __dla__FPv(*param_1);
    }
    if (param_1[1] != 0) {
      __dla__FPv(param_1[1]);
    }
    __dla__FPv(param_1[0x13]);
    if (param_1[0x14] != 0) {
      __dla__FPv(param_1[0x14] + -0x10);
    }
    if (param_1[0x15] != 0) {
      __dla__FPv(param_1[0x15] + -0x10);
    }
    if (param_1[0x16] != 0) {
      __dla__FPv(param_1[0x16] + -0x10);
    }
    if (param_1[0x17] != 0) {
      __dla__FPv(param_1[0x17] + -0x10);
    }
    if (param_1[0x18] != 0) {
      __dla__FPv(param_1[0x18] + -0x10);
    }
    if (param_1[0x19] != 0) {
      __dla__FPv(param_1[0x19] + -0x10);
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
 * JP: 0x0054b9b0  @44@__dt__9BreakBBoxFv
 * C++: @44@__dt__9BreakBBoxFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int _44___dt__9BreakBBoxFv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x2c;
  if (iVar1 != 0) {
    *(undefined4 *)(param_1 + -0x18) = 0x409930;
    *(undefined4 *)(param_1 + -4) = 0x409940;
    *(undefined4 *)(param_1 + 8) = 0x409950;
    if (*(int *)(param_1 + -0x14) != 0) {
      __dla__FPv(*(undefined4 *)(param_1 + -0x14));
    }
    if (*(int *)(param_1 + -0x10) != 0) {
      __dla__FPv(*(undefined4 *)(param_1 + -0x10));
    }
    __dla__FPv(*(undefined4 *)(param_1 + 0x38));
    if (*(int *)(param_1 + 0x3c) != 0) {
      __dla__FPv(*(int *)(param_1 + 0x3c) + -0x10);
    }
    if (*(int *)(param_1 + 0x40) != 0) {
      __dla__FPv(*(int *)(param_1 + 0x40) + -0x10);
    }
    if (*(int *)(param_1 + 0x44) != 0) {
      __dla__FPv(*(int *)(param_1 + 0x44) + -0x10);
    }
    if (*(int *)(param_1 + 0x48) != 0) {
      __dla__FPv(*(int *)(param_1 + 0x48) + -0x10);
    }
    if (*(int *)(param_1 + 0x4c) != 0) {
      __dla__FPv(*(int *)(param_1 + 0x4c) + -0x10);
    }
    if (*(int *)(param_1 + 0x50) != 0) {
      __dla__FPv(*(int *)(param_1 + 0x50) + -0x10);
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

