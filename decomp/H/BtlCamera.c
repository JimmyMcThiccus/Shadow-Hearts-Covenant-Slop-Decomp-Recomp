/* decomp/H/BtlCamera.c — cleaned Ghidra output (SH2JP_BATTLE.BIN, JP Furokuban, base 0x00430a00).
 * 31 function(s). Types: see types.h. Names/gp globals resolved from symbols/SLPM_602.19.syms. */
#include "types.h"

/* ---------------------------------------------------------------------------
 * JP: 0x0055dbe0  __ct__9BtlCameraFv
 * C++: BtlCamera::__ct()
 * size: 0x55c bytes
 * --------------------------------------------------------------------------- */
undefined8 __ct__9BtlCameraFv(undefined8 param_1)

{
  undefined1 auVar1 [16];
  undefined8 uVar2;
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  undefined4 uVar3;
  int iVar4;
  long lVar5;
  undefined4 uVar6;
  undefined4 *puVar7;
  int iVar8;
  undefined1 in_vf0 [16];
  undefined1 auVar9 [16];
  undefined1 auVar10 [16];
  undefined1 auVar11 [16];
  
  __ct__7CPolObjFv(param_1);
  iVar8 = (int)param_1;
  *(undefined4 *)(iVar8 + 0x14) = 0x40a6e0;
  *(undefined4 *)(iVar8 + 0x30) = in_zero_lo;
  *(undefined4 *)(iVar8 + 0x34) = in_zero_hi;
  *(undefined4 *)(iVar8 + 0x38) = in_zero_udw;
  *(undefined4 *)(iVar8 + 0x3c) = in_register_0000000c;
  *(undefined4 *)(iVar8 + 0x40) = in_zero_lo;
  *(undefined4 *)(iVar8 + 0x44) = in_zero_hi;
  *(undefined4 *)(iVar8 + 0x48) = in_zero_udw;
  *(undefined4 *)(iVar8 + 0x4c) = in_register_0000000c;
  *(undefined4 *)(iVar8 + 0x50) = in_zero_lo;
  *(undefined4 *)(iVar8 + 0x54) = in_zero_hi;
  *(undefined4 *)(iVar8 + 0x58) = in_zero_udw;
  *(undefined4 *)(iVar8 + 0x5c) = in_register_0000000c;
  *(undefined4 *)(iVar8 + 0x60) = in_zero_lo;
  *(undefined4 *)(iVar8 + 100) = in_zero_hi;
  *(undefined4 *)(iVar8 + 0x68) = in_zero_udw;
  *(undefined4 *)(iVar8 + 0x6c) = in_register_0000000c;
  *(undefined4 *)(iVar8 + 0x70) = in_zero_lo;
  *(undefined4 *)(iVar8 + 0x74) = in_zero_hi;
  *(undefined4 *)(iVar8 + 0x78) = in_zero_udw;
  *(undefined4 *)(iVar8 + 0x7c) = in_register_0000000c;
  *(undefined4 *)(iVar8 + 0xa0) = in_zero_lo;
  *(undefined4 *)(iVar8 + 0xa4) = in_zero_hi;
  *(undefined4 *)(iVar8 + 0xa8) = in_zero_udw;
  *(undefined4 *)(iVar8 + 0xac) = in_register_0000000c;
  *(undefined4 *)(iVar8 + 0xb0) = in_zero_lo;
  *(undefined4 *)(iVar8 + 0xb4) = in_zero_hi;
  *(undefined4 *)(iVar8 + 0xb8) = in_zero_udw;
  *(undefined4 *)(iVar8 + 0xbc) = in_register_0000000c;
  *(undefined4 *)(iVar8 + 0xc0) = in_zero_lo;
  *(undefined4 *)(iVar8 + 0xc4) = in_zero_hi;
  *(undefined4 *)(iVar8 + 200) = in_zero_udw;
  *(undefined4 *)(iVar8 + 0xcc) = in_register_0000000c;
  puVar7 = (undefined4 *)(iVar8 + 0x100);
  do {
    *puVar7 = in_zero_lo;
    puVar7[1] = in_zero_hi;
    puVar7[2] = in_zero_udw;
    puVar7[3] = in_register_0000000c;
    puVar7 = puVar7 + 4;
  } while (puVar7 != (undefined4 *)(iVar8 + 0x140));
  *(undefined4 *)(iVar8 + 0x200) = in_zero_lo;
  *(undefined4 *)(iVar8 + 0x204) = in_zero_hi;
  *(undefined4 *)(iVar8 + 0x208) = in_zero_udw;
  *(undefined4 *)(iVar8 + 0x20c) = in_register_0000000c;
  *(undefined4 *)(iVar8 + 0x18) = 0;
  *(undefined2 *)(iVar8 + 0x1c) = 0;
  *(undefined2 *)(iVar8 + 0x1e) = 0;
  uVar3 = GetTimer__7SysToolFv();
  *(undefined4 *)(iVar8 + 0x20) = uVar3;
  *(undefined4 *)(iVar8 + 0x24) = 0;
  *(undefined4 *)(iVar8 + 0x30) = 0;
  *(undefined4 *)(iVar8 + 0x34) = 0xc1000000;
  *(undefined4 *)(iVar8 + 0x38) = 0xc30c0000;
  *(undefined4 *)(iVar8 + 0x3c) = 0x3f800000;
  *(undefined4 *)(iVar8 + 0x40) = 0xc1200000;
  *(undefined4 *)(iVar8 + 0x44) = 0;
  *(undefined4 *)(iVar8 + 0x48) = 0;
  *(undefined4 *)(iVar8 + 0x4c) = 0x3f800000;
  *(undefined4 *)(iVar8 + 0x50) = 0;
  *(undefined4 *)(iVar8 + 0x54) = 0xc1000000;
  *(undefined4 *)(iVar8 + 0x58) = 0xc30c0000;
  *(undefined4 *)(iVar8 + 0x5c) = 0x3f800000;
  *(undefined4 *)(iVar8 + 0x60) = 0xc1200000;
  *(undefined4 *)(iVar8 + 100) = 0;
  *(undefined4 *)(iVar8 + 0x68) = 0;
  *(undefined4 *)(iVar8 + 0x6c) = 0x3f800000;
  *(undefined4 *)(iVar8 + 0x70) = 0;
  *(undefined4 *)(iVar8 + 0x74) = 0xc1000000;
  *(undefined4 *)(iVar8 + 0x78) = 0;
  *(undefined4 *)(iVar8 + 0x7c) = 0x3f800000;
  *(undefined4 *)(iVar8 + 0x80) = 0x42480000;
  *(undefined4 *)(iVar8 + 0x84) = 0x44000000;
  *(undefined4 *)(iVar8 + 0x8c) = 0;
  *(undefined4 *)(iVar8 + 0xb0) = 0;
  *(undefined4 *)(iVar8 + 0xb4) = 0;
  *(undefined4 *)(iVar8 + 0xb8) = 0;
  *(undefined4 *)(iVar8 + 0xbc) = 0x3f800000;
  *(undefined4 *)(iVar8 + 0x140) = 0;
  *(undefined4 *)(iVar8 + 0x1e8) = 0;
  *(undefined4 *)(iVar8 + 0x1ec) = 0;
  *(undefined4 *)(iVar8 + 0x200) = 0;
  *(undefined4 *)(iVar8 + 0x204) = 0;
  *(undefined4 *)(iVar8 + 0x208) = 0;
  *(undefined4 *)(iVar8 + 0x20c) = 0x3f800000;
  *(byte *)(iVar8 + 0x18) = *(byte *)(iVar8 + 0x18) & 0x7f | 0x80;
  *(undefined4 *)(iVar8 + 0x210) = 0xffffffff;
  *(undefined4 *)(iVar8 + 0x214) = 0xffffffff;
  Entry__7CPollerFP7CPolObjib(iGpffff858c + 0x48,param_1,0x80,1);
  if (iGpffff8598 == 0) {
    lVar5 = __nw__FUi(0x3a0);
    iVar4 = 0;
    if (lVar5 != 0) {
      iVar4 = __ct__9GsxCameraFUiUiUiUiUi(lVar5,0,0,0,0x18,0xb);
    }
    iGpffff8598 = iVar4;
    *(undefined4 *)(iGpffff8598 + 0x180) = 0;
    *(undefined4 *)(iGpffff8598 + 0x370) = 0x3f800000;
    *(undefined4 *)(iGpffff8598 + 0x374) = 0x46fa0000;
    SetViewMatrix__9GsxCameraFfffff(*(undefined4 *)(iVar8 + 0x84),0x3f4ccccd,0x3f6eeeef,0x3f800000,0x4b7fff28,
                    iGpffff8598);
    SetCamera__5WorldFUiiP9GsxCamera(0x42bf10,0,0,iGpffff8598);
    SetFFMode__3GsxFibi(0,1,2);
    SetInter30__3GsxFi(1);
  }
  else {
    *(undefined4 *)(iGpffff8598 + 0x370) = 0x3f800000;
    *(undefined4 *)(iGpffff8598 + 0x374) = 0x46fa0000;
    SetViewMatrix__9GsxCameraFfffff(*(undefined4 *)(iVar8 + 0x84),0x3f4ccccd,0x3f6eeeef,0x3f800000,0x4b7fff28,
                    iGpffff8598);
  }
  auVar9 = _vmr32(in_vf0);
  auVar10 = _vmr32(auVar9);
  auVar11 = _vmr32(auVar10);
  auVar1 = _sqc2(in_vf0);
  *(undefined1 (*) [16])(iGpffff8598 + 0x270) = auVar1;
  auVar1 = _sqc2(auVar9);
  *(undefined1 (*) [16])(iGpffff8598 + 0x260) = auVar1;
  auVar1 = _sqc2(auVar10);
  *(undefined1 (*) [16])(iGpffff8598 + 0x250) = auVar1;
  auVar1 = _sqc2(auVar11);
  *(undefined1 (*) [16])(iGpffff8598 + 0x240) = auVar1;
  uVar3 = GetRad(*(undefined4 *)(iVar8 + 0x40));
  sceVu0RotMatrixX(uVar3,iGpffff8598 + 0x240,iGpffff8598 + 0x240);
  uVar3 = GetRad(*(undefined4 *)(iVar8 + 0x44));
  sceVu0RotMatrixY(uVar3,iGpffff8598 + 0x240,iGpffff8598 + 0x240);
  uVar3 = GetRad(*(undefined4 *)(iVar8 + 0x48));
  sceVu0RotMatrixZ(uVar3,iGpffff8598 + 0x240,iGpffff8598 + 0x240);
  uVar2 = *(undefined8 *)(iVar8 + 0x30);
  uVar3 = *(undefined4 *)(iVar8 + 0x38);
  uVar6 = *(undefined4 *)(iVar8 + 0x3c);
  *(int *)(iGpffff8598 + 0x270) = (int)uVar2;
  *(int *)(iGpffff8598 + 0x274) = (int)((ulong)uVar2 >> 0x20);
  *(undefined4 *)(iGpffff8598 + 0x278) = uVar3;
  *(undefined4 *)(iGpffff8598 + 0x27c) = uVar6;
  ApplyFrame__9GsxCameraFv(iGpffff8598);
  return param_1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0055e140  __dt__9BtlCameraFv
 * C++: BtlCamera::__dt()
 * size: 0x94 bytes
 * --------------------------------------------------------------------------- */
int __dt__9BtlCameraFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x14) = 0x40a6e0;
    if (*(int *)(param_1 + 0x210) != -1) {
      release__12LightControlFi(*(undefined4 *)(param_1 + 0x210));
    }
    __dt__7CPolObjFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0055e1e0  Polling__9BtlCameraFv
 * C++: BtlCamera::Polling()
 * size: 0x1dd88 bytes
 * --------------------------------------------------------------------------- */
{"error":"Decompilation did not complete. Reason: Exception while decompiling 0055e1e0: process: timeout\n"}

/* ---------------------------------------------------------------------------
 * JP: 0x0057c070  UpdateCamera__9BtlCameraFv
 * C++: BtlCamera::UpdateCamera()
 * size: 0x1550 bytes
 * --------------------------------------------------------------------------- */
void UpdateCamera__9BtlCameraFv(int param_1)

{
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  undefined4 uVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  undefined1 in_vf0 [16];
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  undefined1 auVar8 [16];
  undefined1 auVar9 [16];
  undefined1 auStack_100 [16];
  undefined1 auStack_f0 [16];
  undefined1 auStack_e0 [16];
  undefined1 auStack_d0 [16];
  undefined1 auStack_c0 [16];
  undefined1 auStack_b0 [8];
  float fStack_a8;
  undefined4 uStack_a4;
  undefined1 auStack_a0 [8];
  undefined4 uStack_98;
  undefined4 uStack_94;
  undefined1 auStack_90 [8];
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined1 auStack_80 [8];
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined1 auStack_70 [16];
  undefined1 auStack_60 [16];
  undefined1 auStack_50 [16];
  undefined1 auStack_40 [16];
  float fStack_30;
  float fStack_2c;
  float fStack_28;
  undefined4 uStack_24;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  auVar6 = _vmr32(in_vf0);
  auVar7 = _vmr32(auVar6);
  auVar8 = _vmr32(auVar7);
  auStack_40 = _sqc2(in_vf0);
  auStack_50 = _sqc2(auVar6);
  auStack_60 = _sqc2(auVar7);
  auStack_70 = _sqc2(auVar8);
  if ((long)((ulong)*(byte *)(param_1 + 0x18) << 0x3b) < 0) {
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfe | 1;
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfd | 2;
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfb | 4;
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xf7 | 8;
    *(int *)(param_1 + 0x40) = (int)*(undefined8 *)(param_1 + 0x60);
    *(int *)(param_1 + 0x44) = (int)((ulong)*(undefined8 *)(param_1 + 0x60) >> 0x20);
    *(undefined4 *)(param_1 + 0x48) = *(undefined4 *)(param_1 + 0x68);
    *(undefined4 *)(param_1 + 0x4c) = *(undefined4 *)(param_1 + 0x6c);
    *(int *)(param_1 + 0x30) = (int)*(undefined8 *)(param_1 + 0x50);
    *(int *)(param_1 + 0x34) = (int)((ulong)*(undefined8 *)(param_1 + 0x50) >> 0x20);
    *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(param_1 + 0x58);
    *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(param_1 + 0x5c);
    uStack_10 = in_zero_lo;
    uStack_c = in_zero_hi;
    uStack_8 = in_zero_udw;
    uStack_4 = in_register_0000000c;
  }
  else {
    if ((*(byte *)(param_1 + 0x18) & 1) == 0) {
      if (*(float *)(param_1 + 0x8c) == 0.0) {
        auVar6 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x50));
        auVar7 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x30));
        auVar6 = _vsub(auVar6,auVar7);
        auStack_e0 = _sqc2(auVar6);
        __ct__7FVectorFRC7FVector(auStack_90,auStack_e0);
        uStack_10 = auStack_90._0_4_;
        uStack_c = auStack_90._4_4_;
        uStack_8 = uStack_88;
        uStack_4 = uStack_84;
        uVar1 = Length__7FVectorCFv(&uStack_10);
        *(undefined4 *)(param_1 + 0x8c) = uVar1;
        if (*(float *)(param_1 + 0x8c) <= *(float *)(param_1 + 0x88)) {
          *(undefined4 *)(param_1 + 0x88) = *(undefined4 *)(param_1 + 0x8c);
          *(int *)(param_1 + 0x30) = (int)*(undefined8 *)(param_1 + 0x50);
          *(int *)(param_1 + 0x34) = (int)((ulong)*(undefined8 *)(param_1 + 0x50) >> 0x20);
          *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(param_1 + 0x58);
          *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(param_1 + 0x5c);
          *(undefined4 *)(param_1 + 0x8c) = 0;
          *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfe | 1;
        }
        else {
          *(float *)(param_1 + 0x8c) = *(float *)(param_1 + 0x8c) - *(float *)(param_1 + 0x88);
          *(undefined4 *)(param_1 + 0x90) = 0;
          Normalize__7FVectorFv(&uStack_10);
          __amu__7FVectorFf(*(undefined4 *)(param_1 + 0x88),&uStack_10);
          auVar6._4_4_ = uStack_c;
          auVar6._0_4_ = uStack_10;
          auVar6._8_4_ = uStack_8;
          auVar6._12_4_ = uStack_4;
          auVar7 = _lqc2(auVar6);
          auVar6 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x30));
          auVar6 = _vadd(auVar6,auVar7);
          auVar6 = _sqc2(auVar6);
          *(undefined1 (*) [16])(param_1 + 0x30) = auVar6;
        }
      }
      else {
        uVar1 = GetRad(*(undefined4 *)(param_1 + 0x90));
        fVar3 = (float)cosf(uVar1);
        fVar4 = (-fVar3 + 1.0) / 2.0;
        *(float *)(param_1 + 0x90) = *(float *)(param_1 + 0x90) + *(float *)(param_1 + 0x24) * 360.0
        ;
        uVar1 = GetRad(*(undefined4 *)(param_1 + 0x90));
        fVar3 = (float)cosf(uVar1);
        fVar5 = (-fVar3 + 1.0) / 2.0;
        auVar6 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x50));
        auVar7 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x30));
        auVar6 = _vsub(auVar6,auVar7);
        auStack_f0 = _sqc2(auVar6);
        __ct__7FVectorFRC7FVector(auStack_a0,auStack_f0);
        uStack_10 = auStack_a0._0_4_;
        uStack_c = auStack_a0._4_4_;
        uStack_8 = uStack_98;
        uStack_4 = uStack_94;
        fVar3 = (float)Length__7FVectorCFv(&uStack_10);
        *(float *)(param_1 + 0x88) = fVar3 - *(float *)(param_1 + 0x8c) * (1.0 - fVar4);
        Normalize__7FVectorFv(&uStack_10);
        fVar5 = *(float *)(param_1 + 0x88) +
                (*(float *)(param_1 + 0x8c) * fVar5 - *(float *)(param_1 + 0x8c) * fVar4);
        if (fVar5 <= fVar3) {
          fVar3 = fVar5;
        }
        __amu__7FVectorFf(fVar3,&uStack_10);
        auVar7._4_4_ = uStack_c;
        auVar7._0_4_ = uStack_10;
        auVar7._8_4_ = uStack_8;
        auVar7._12_4_ = uStack_4;
        auVar7 = _lqc2(auVar7);
        auVar6 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x30));
        auVar6 = _vadd(auVar6,auVar7);
        auVar6 = _sqc2(auVar6);
        *(undefined1 (*) [16])(param_1 + 0x30) = auVar6;
        if (180.0 <= *(float *)(param_1 + 0x90)) {
          *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfe | 1;
          *(undefined4 *)(param_1 + 0x8c) = 0;
          *(undefined4 *)(param_1 + 0x90) = 0;
        }
      }
    }
    else {
      auVar6 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x50));
      auVar7 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x30));
      auVar6 = _vsub(auVar6,auVar7);
      auStack_d0 = _sqc2(auVar6);
      __ct__7FVectorFRC7FVector(auStack_80,auStack_d0);
      uStack_10 = auStack_80._0_4_;
      uStack_c = auStack_80._4_4_;
      uStack_8 = uStack_78;
      uStack_4 = uStack_74;
      uVar1 = Length__7FVectorCFv(&uStack_10);
      *(undefined4 *)(param_1 + 0x88) = uVar1;
      *(int *)(param_1 + 0x30) = (int)*(undefined8 *)(param_1 + 0x50);
      *(int *)(param_1 + 0x34) = (int)((ulong)*(undefined8 *)(param_1 + 0x50) >> 0x20);
      *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(param_1 + 0x58);
      *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(param_1 + 0x5c);
      *(undefined4 *)(param_1 + 0x8c) = 0;
    }
    if ((long)((ulong)*(byte *)(param_1 + 0x18) << 0x3e) < 0) {
      for (fVar3 = *(float *)(param_1 + 0x60) - *(float *)(param_1 + 0x40); fVar3 < -180.0;
          fVar3 = fVar3 + 360.0) {
      }
      for (; 180.0 < fVar3; fVar3 = fVar3 - 360.0) {
      }
      *(float *)(param_1 + 0xa0) = fVar3;
      *(undefined4 *)(param_1 + 0x40) = *(undefined4 *)(param_1 + 0x60);
      *(undefined4 *)(param_1 + 0xb0) = 0;
    }
    else if (*(float *)(param_1 + 0xb0) == 0.0) {
      for (fVar3 = *(float *)(param_1 + 0x60) - *(float *)(param_1 + 0x40); fVar3 < -180.0;
          fVar3 = fVar3 + 360.0) {
      }
      for (; 180.0 < fVar3; fVar3 = fVar3 - 360.0) {
      }
      fVar5 = fVar3;
      if (fVar3 < 0.0) {
        fVar5 = -fVar3;
      }
      *(float *)(param_1 + 0xb0) = fVar5;
      if (*(float *)(param_1 + 0xb0) <= *(float *)(param_1 + 0xa0)) {
        *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_1 + 0xb0);
        *(undefined4 *)(param_1 + 0x40) = *(undefined4 *)(param_1 + 0x60);
        *(undefined4 *)(param_1 + 0xb0) = 0;
        *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfd | 2;
      }
      else {
        *(float *)(param_1 + 0xb0) = *(float *)(param_1 + 0xb0) - *(float *)(param_1 + 0xa0);
        *(undefined4 *)(param_1 + 0xc0) = 0;
        fVar5 = *(float *)(param_1 + 0xa0);
        if (fVar3 < 0.0) {
          fVar5 = -*(float *)(param_1 + 0xa0);
        }
        *(float *)(param_1 + 0x40) = *(float *)(param_1 + 0x40) + fVar5;
      }
    }
    else {
      uVar1 = GetRad(*(undefined4 *)(param_1 + 0xc0));
      fVar3 = (float)cosf(uVar1);
      fVar4 = (-fVar3 + 1.0) / 2.0;
      *(float *)(param_1 + 0xc0) = *(float *)(param_1 + 0xc0) + *(float *)(param_1 + 0x24) * 360.0;
      uVar1 = GetRad(*(undefined4 *)(param_1 + 0xc0));
      fVar3 = (float)cosf(uVar1);
      fVar5 = (-fVar3 + 1.0) / 2.0;
      for (fVar3 = *(float *)(param_1 + 0x60) - *(float *)(param_1 + 0x40); fVar3 < -180.0;
          fVar3 = fVar3 + 360.0) {
      }
      for (; 180.0 < fVar3; fVar3 = fVar3 - 360.0) {
      }
      fVar2 = fVar3;
      if (fVar3 < 0.0) {
        fVar2 = -fVar3;
      }
      *(float *)(param_1 + 0xa0) = fVar2 - *(float *)(param_1 + 0xb0) * (1.0 - fVar4);
      if (0.0 <= fVar3) {
        fVar5 = *(float *)(param_1 + 0xa0) +
                (*(float *)(param_1 + 0xb0) * fVar5 - *(float *)(param_1 + 0xb0) * fVar4);
        if (fVar5 <= fVar3) {
          fVar3 = fVar5;
        }
      }
      else {
        fVar5 = -(*(float *)(param_1 + 0xa0) +
                 (*(float *)(param_1 + 0xb0) * fVar5 - *(float *)(param_1 + 0xb0) * fVar4));
        if (fVar3 <= fVar5) {
          fVar3 = fVar5;
        }
      }
      *(float *)(param_1 + 0x40) = *(float *)(param_1 + 0x40) + fVar3;
      if (180.0 <= *(float *)(param_1 + 0xc0)) {
        *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfd | 2;
        *(undefined4 *)(param_1 + 0xb0) = 0;
        *(undefined4 *)(param_1 + 0xc0) = 0;
      }
    }
    if ((long)((ulong)*(byte *)(param_1 + 0x18) << 0x3d) < 0) {
      for (fVar3 = *(float *)(param_1 + 100) - *(float *)(param_1 + 0x44); fVar3 < -180.0;
          fVar3 = fVar3 + 360.0) {
      }
      for (; 180.0 < fVar3; fVar3 = fVar3 - 360.0) {
      }
      if (0.0 < fVar3) {
        *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xdf;
      }
      else if (fVar3 < 0.0) {
        *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xdf | 0x20;
      }
      *(float *)(param_1 + 0xa4) = fVar3;
      *(undefined4 *)(param_1 + 0x44) = *(undefined4 *)(param_1 + 100);
      *(undefined4 *)(param_1 + 0xb4) = 0;
    }
    else if (*(float *)(param_1 + 0xb4) == 0.0) {
      for (fVar3 = *(float *)(param_1 + 100) - *(float *)(param_1 + 0x44); fVar3 < -180.0;
          fVar3 = fVar3 + 360.0) {
      }
      for (; 180.0 < fVar3; fVar3 = fVar3 - 360.0) {
      }
      fVar5 = fVar3;
      if (0.0 < fVar3) {
        *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xdf;
      }
      else if (fVar3 < 0.0) {
        *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xdf | 0x20;
        fVar5 = -fVar3;
      }
      *(float *)(param_1 + 0xb4) = fVar5;
      if (*(float *)(param_1 + 0xb4) <= *(float *)(param_1 + 0xa4)) {
        *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(param_1 + 0xb4);
        *(undefined4 *)(param_1 + 0x44) = *(undefined4 *)(param_1 + 100);
        *(undefined4 *)(param_1 + 0xb4) = 0;
        *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfb | 4;
      }
      else {
        *(float *)(param_1 + 0xb4) = *(float *)(param_1 + 0xb4) - *(float *)(param_1 + 0xa4);
        *(undefined4 *)(param_1 + 0xc4) = 0;
        fVar5 = *(float *)(param_1 + 0xa4);
        if (fVar3 < 0.0) {
          fVar5 = -*(float *)(param_1 + 0xa4);
        }
        *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) + fVar5;
      }
    }
    else {
      uVar1 = GetRad(*(undefined4 *)(param_1 + 0xc4));
      fVar3 = (float)cosf(uVar1);
      fVar4 = (-fVar3 + 1.0) / 2.0;
      *(float *)(param_1 + 0xc4) = *(float *)(param_1 + 0xc4) + *(float *)(param_1 + 0x24) * 360.0;
      uVar1 = GetRad(*(undefined4 *)(param_1 + 0xc4));
      fVar3 = (float)cosf(uVar1);
      fVar5 = (-fVar3 + 1.0) / 2.0;
      for (fVar3 = *(float *)(param_1 + 100) - *(float *)(param_1 + 0x44); fVar3 < -180.0;
          fVar3 = fVar3 + 360.0) {
      }
      for (; 180.0 < fVar3; fVar3 = fVar3 - 360.0) {
      }
      fVar2 = fVar3;
      if (0.0 < fVar3) {
        *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xdf;
      }
      else if (fVar3 < 0.0) {
        *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xdf | 0x20;
        fVar2 = -fVar3;
      }
      *(float *)(param_1 + 0xa4) = fVar2 - *(float *)(param_1 + 0xb4) * (1.0 - fVar4);
      if (0.0 <= fVar3) {
        fVar5 = *(float *)(param_1 + 0xa4) +
                (*(float *)(param_1 + 0xb4) * fVar5 - *(float *)(param_1 + 0xb4) * fVar4);
        if (fVar5 <= fVar3) {
          fVar3 = fVar5;
        }
      }
      else {
        fVar5 = -(*(float *)(param_1 + 0xa4) +
                 (*(float *)(param_1 + 0xb4) * fVar5 - *(float *)(param_1 + 0xb4) * fVar4));
        if (fVar3 <= fVar5) {
          fVar3 = fVar5;
        }
      }
      *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) + fVar3;
      if (180.0 <= *(float *)(param_1 + 0xc4)) {
        *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfb | 4;
        *(undefined4 *)(param_1 + 0xb4) = 0;
        *(undefined4 *)(param_1 + 0xc4) = 0;
      }
    }
    if ((long)((ulong)*(byte *)(param_1 + 0x18) << 0x3c) < 0) {
      for (fVar3 = *(float *)(param_1 + 0x68) - *(float *)(param_1 + 0x48); fVar3 < -180.0;
          fVar3 = fVar3 + 360.0) {
      }
      for (; 180.0 < fVar3; fVar3 = fVar3 - 360.0) {
      }
      *(float *)(param_1 + 0xa8) = fVar3;
      *(undefined4 *)(param_1 + 0x48) = *(undefined4 *)(param_1 + 0x68);
      *(undefined4 *)(param_1 + 0xb8) = 0;
    }
    else if (*(float *)(param_1 + 0xb8) == 0.0) {
      for (fVar3 = *(float *)(param_1 + 0x68) - *(float *)(param_1 + 0x48); fVar3 < -180.0;
          fVar3 = fVar3 + 360.0) {
      }
      for (; 180.0 < fVar3; fVar3 = fVar3 - 360.0) {
      }
      fVar5 = fVar3;
      if (fVar3 < 0.0) {
        fVar5 = -fVar3;
      }
      *(float *)(param_1 + 0xb8) = fVar5;
      if (*(float *)(param_1 + 0xb8) <= *(float *)(param_1 + 0xa8)) {
        *(undefined4 *)(param_1 + 0xa8) = *(undefined4 *)(param_1 + 0xb8);
        *(undefined4 *)(param_1 + 0x48) = *(undefined4 *)(param_1 + 0x68);
        *(undefined4 *)(param_1 + 0xb8) = 0;
        *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xf7 | 8;
      }
      else {
        *(float *)(param_1 + 0xb8) = *(float *)(param_1 + 0xb8) - *(float *)(param_1 + 0xa8);
        *(undefined4 *)(param_1 + 200) = 0;
        fVar5 = *(float *)(param_1 + 0xa8);
        if (fVar3 < 0.0) {
          fVar5 = -*(float *)(param_1 + 0xa8);
        }
        *(float *)(param_1 + 0x48) = *(float *)(param_1 + 0x48) + fVar5;
      }
    }
    else {
      uVar1 = GetRad(*(undefined4 *)(param_1 + 200));
      fVar3 = (float)cosf(uVar1);
      fVar4 = (-fVar3 + 1.0) / 2.0;
      *(float *)(param_1 + 200) = *(float *)(param_1 + 200) + *(float *)(param_1 + 0x24) * 360.0;
      uVar1 = GetRad(*(undefined4 *)(param_1 + 200));
      fVar3 = (float)cosf(uVar1);
      fVar5 = (-fVar3 + 1.0) / 2.0;
      for (fVar3 = *(float *)(param_1 + 0x68) - *(float *)(param_1 + 0x48); fVar3 < -180.0;
          fVar3 = fVar3 + 360.0) {
      }
      for (; 180.0 < fVar3; fVar3 = fVar3 - 360.0) {
      }
      fVar2 = fVar3;
      if (fVar3 < 0.0) {
        fVar2 = -fVar3;
      }
      *(float *)(param_1 + 0xa8) = fVar2 - *(float *)(param_1 + 0xb8) * (1.0 - fVar4);
      if (0.0 <= fVar3) {
        fVar5 = *(float *)(param_1 + 0xa8) +
                (*(float *)(param_1 + 0xb8) * fVar5 - *(float *)(param_1 + 0xb8) * fVar4);
        if (fVar5 <= fVar3) {
          fVar3 = fVar5;
        }
      }
      else {
        fVar5 = -(*(float *)(param_1 + 0xa8) +
                 (*(float *)(param_1 + 0xb8) * fVar5 - *(float *)(param_1 + 0xb8) * fVar4));
        if (fVar3 <= fVar5) {
          fVar3 = fVar5;
        }
      }
      *(float *)(param_1 + 0x48) = *(float *)(param_1 + 0x48) + fVar3;
      if (180.0 <= *(float *)(param_1 + 200)) {
        *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xf7 | 8;
        *(undefined4 *)(param_1 + 0xb8) = 0;
        *(undefined4 *)(param_1 + 200) = 0;
      }
    }
  }
  SetViewMatrix__9GsxCameraFfffff(*(undefined4 *)(param_1 + 0x84),0x3f4ccccd,0x3f6eeeef,0x3f800000,0x4b7fff28,
                  iGpffff8598);
  auVar7 = _vmr32(in_vf0);
  auVar8 = _vmr32(auVar7);
  auVar9 = _vmr32(auVar8);
  auVar6 = _sqc2(in_vf0);
  *(undefined1 (*) [16])(iGpffff8598 + 0x270) = auVar6;
  auVar6 = _sqc2(auVar7);
  *(undefined1 (*) [16])(iGpffff8598 + 0x260) = auVar6;
  auVar6 = _sqc2(auVar8);
  *(undefined1 (*) [16])(iGpffff8598 + 0x250) = auVar6;
  auVar6 = _sqc2(auVar9);
  *(undefined1 (*) [16])(iGpffff8598 + 0x240) = auVar6;
  uVar1 = GetRad(*(undefined4 *)(param_1 + 0x40));
  sceVu0RotMatrixX(uVar1,iGpffff8598 + 0x240,iGpffff8598 + 0x240);
  uVar1 = GetRad(*(undefined4 *)(param_1 + 0x44));
  sceVu0RotMatrixY(uVar1,iGpffff8598 + 0x240,iGpffff8598 + 0x240);
  uVar1 = GetRad(*(undefined4 *)(param_1 + 0x48));
  sceVu0RotMatrixZ(uVar1,iGpffff8598 + 0x240,iGpffff8598 + 0x240);
  if (*(float *)(param_1 + 0x1e8) == 0.0) {
    fStack_28 = *(float *)(param_1 + 0x38);
    uStack_24 = *(undefined4 *)(param_1 + 0x3c);
    fStack_30 = (float)*(undefined8 *)(param_1 + 0x30);
    fStack_2c = (float)((ulong)*(undefined8 *)(param_1 + 0x30) >> 0x20);
  }
  else {
    auStack_70 = *(undefined1 (*) [16])(iGpffff8598 + 0x240);
    auStack_60 = *(undefined1 (*) [16])(iGpffff8598 + 0x250);
    auStack_50 = *(undefined1 (*) [16])(iGpffff8598 + 0x260);
    auStack_40 = *(undefined1 (*) [16])(iGpffff8598 + 0x270);
    ApplyMatrix__6MatrixCFRC7FVector(auStack_c0,auStack_70,param_1 + 0x200);
    auVar6 = _lqc2(auStack_c0);
    auVar7 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x30));
    auVar6 = _vadd(auVar6,auVar7);
    auStack_100 = _sqc2(auVar6);
    __ct__7FVectorFRC7FVector(auStack_b0,auStack_100);
    fStack_30 = auStack_b0._0_4_;
    fStack_2c = auStack_b0._4_4_;
    fStack_28 = fStack_a8;
    uStack_24 = uStack_a4;
  }
  fVar5 = (-*(float *)(iGpffff86b4 + 0x3f14) - 10.0) / 2.0 - fStack_30;
  fVar3 = fStack_30 - (*(float *)(iGpffff86b4 + 0x3f14) + 10.0) / 2.0;
  if (fVar3 <= fVar5) {
    fVar3 = fVar5;
  }
  fVar5 = (-*(float *)(iGpffff86b4 + 0x3f1c) - 10.0) / 2.0 - fStack_28;
  if (fVar5 <= fVar3) {
    fVar5 = fVar3;
  }
  fVar3 = fStack_28 - (*(float *)(iGpffff86b4 + 0x3f1c) + 10.0) / 2.0;
  if (fVar3 <= fVar5) {
    fVar3 = fVar5;
  }
  if (fVar3 <= 1.0) {
    fVar3 = 1.0;
  }
  if (10.0 <= fVar3) {
    fVar3 = 10.0;
  }
  if (-fVar3 < fStack_2c) {
    fStack_2c = -fVar3;
  }
  *(float *)(iGpffff8598 + 0x270) = fStack_30;
  *(float *)(iGpffff8598 + 0x274) = fStack_2c;
  *(float *)(iGpffff8598 + 0x278) = fStack_28;
  *(undefined4 *)(iGpffff8598 + 0x27c) = uStack_24;
  ApplyFrame__9GsxCameraFv(iGpffff8598);
  *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xef;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0057d5c0  CameraYPosCheck__9BtlCameraFv
 * C++: BtlCamera::CameraYPosCheck()
 * size: 0x1e4 bytes
 * --------------------------------------------------------------------------- */
void CameraYPosCheck__9BtlCameraFv(int param_1)

{
  float fVar1;
  float fStack_14;
  
  fVar1 = (-*(float *)(iGpffff86b4 + 0x3f14) - 10.0) / 2.0 - *(float *)(param_1 + 0x50);
  fStack_14 = *(float *)(param_1 + 0x50) - (*(float *)(iGpffff86b4 + 0x3f14) + 10.0) / 2.0;
  if (fStack_14 <= fVar1) {
    fStack_14 = fVar1;
  }
  fVar1 = (-*(float *)(iGpffff86b4 + 0x3f1c) - 10.0) / 2.0 - *(float *)(param_1 + 0x58);
  if (fVar1 <= fStack_14) {
    fVar1 = fStack_14;
  }
  fStack_14 = fVar1;
  fVar1 = *(float *)(param_1 + 0x58) - (*(float *)(iGpffff86b4 + 0x3f1c) + 10.0) / 2.0;
  if (fVar1 <= fStack_14) {
    fVar1 = fStack_14;
  }
  fStack_14 = fVar1;
  if (fStack_14 <= 1.0) {
    fStack_14 = 1.0;
  }
  if (10.0 <= fStack_14) {
    fStack_14 = 10.0;
  }
  if (-fStack_14 < *(float *)(param_1 + 0x54)) {
    *(float *)(param_1 + 0x54) = -fStack_14;
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0057d7b0  SetFieldCamera__9BtlCameraF7FVectorb
 * C++: BtlCamera::SetFieldCamera(FVector, bool)
 * size: 0x1f4 bytes
 * --------------------------------------------------------------------------- */
void SetFieldCamera__9BtlCameraF7FVectorb(int param_1,undefined8 *param_2,byte param_3)

{
  undefined8 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  if (*(int *)(param_1 + 0x210) != -1) {
    release__12LightControlFi(*(undefined4 *)(param_1 + 0x210));
    *(undefined4 *)(param_1 + 0x210) = 0xffffffff;
  }
  if (((long)((ulong)*(byte *)(param_1 + 0x19) << 0x3e) < 0) &&
     ((long)((ulong)*(byte *)(param_1 + 0x19) << 0x3d) < 0)) {
    *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xfd;
    *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xfb;
    *(undefined4 *)(param_1 + 0x214) = 0xffffffff;
  }
  *(undefined2 *)(param_1 + 0x1c) = 1;
  *(undefined2 *)(param_1 + 0x1e) = 0;
  uVar1 = *param_2;
  uVar2 = *(undefined4 *)(param_2 + 1);
  uVar3 = *(undefined4 *)((int)param_2 + 0xc);
  *(int *)(param_1 + 0x60) = (int)uVar1;
  *(int *)(param_1 + 100) = (int)((ulong)uVar1 >> 0x20);
  *(undefined4 *)(param_1 + 0x68) = uVar2;
  *(undefined4 *)(param_1 + 0x6c) = uVar3;
  *(undefined4 *)(param_1 + 0x84) = 0x44000000;
  *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xef | (param_3 & 1) << 4;
  *(undefined4 *)(param_1 + 0x140) = 0;
  if (param_3 == 0) {
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfe;
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfd;
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfb;
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xf7;
  }
  else {
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0x7f | 0x80;
    *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xfe | 1;
  }
  *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xf7 | 8;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0057d9b0  SetNextComboCharacterCamera1__9BtlCameraFiiib
 * C++: BtlCamera::SetNextComboCharacterCamera1(int, int, int, bool)
 * size: 0x29c bytes
 * --------------------------------------------------------------------------- */
void SetNextComboCharacterCamera1__9BtlCameraFiiib
               (int param_1,uint param_2,undefined4 param_3,uint param_4,byte param_5)

{
  if (*(int *)(param_1 + 0x210) != -1) {
    release__12LightControlFi(*(undefined4 *)(param_1 + 0x210));
    *(undefined4 *)(param_1 + 0x210) = 0xffffffff;
  }
  if (((long)((ulong)*(byte *)(param_1 + 0x19) << 0x3e) < 0) &&
     ((long)((ulong)*(byte *)(param_1 + 0x19) << 0x3d) < 0)) {
    *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xfd;
    *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xfb;
    *(undefined4 *)(param_1 + 0x214) = 0xffffffff;
  }
  if (*(short *)(param_1 + 0x1c) != 4) {
    *(undefined2 *)(param_1 + 0x1c) = 4;
    *(undefined2 *)(param_1 + 0x1e) = 0;
    *(undefined4 *)(param_1 + 0xdc) = 0;
    *(undefined4 *)(param_1 + 0x84) = 0x44000000;
  }
  *(uint *)(param_1 + 0xd0) = param_2;
  *(undefined4 *)(param_1 + 0xd4) = param_3;
  *(uint *)(param_1 + 0xd8) = param_4;
  *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xef | (param_5 & 1) << 4;
  *(int *)(param_1 + 0x140) = 3 << ((param_2 & 0xf) << 1) | 3 << ((param_4 & 0xf) << 1);
  if (param_5 == 0) {
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfe;
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfd;
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfb;
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xf7;
  }
  else {
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0x7f | 0x80;
    *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xfe | 1;
  }
  *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xf7 | 8;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0057dc50  SetNextComboCharacterCamera2__9BtlCameraF7FVectoriib
 * C++: BtlCamera::SetNextComboCharacterCamera2(FVector, int, int, bool)
 * size: 0x244 bytes
 * --------------------------------------------------------------------------- */
void SetNextComboCharacterCamera2__9BtlCameraF7FVectoriib
               (int param_1,undefined8 *param_2,uint param_3,undefined4 param_4,byte param_5)

{
  undefined8 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  if (*(int *)(param_1 + 0x210) != -1) {
    release__12LightControlFi(*(undefined4 *)(param_1 + 0x210));
    *(undefined4 *)(param_1 + 0x210) = 0xffffffff;
  }
  if (((long)((ulong)*(byte *)(param_1 + 0x19) << 0x3e) < 0) &&
     ((long)((ulong)*(byte *)(param_1 + 0x19) << 0x3d) < 0)) {
    *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xfd;
    *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xfb;
    *(undefined4 *)(param_1 + 0x214) = 0xffffffff;
  }
  if (*(short *)(param_1 + 0x1c) != 5) {
    *(undefined2 *)(param_1 + 0x1c) = 5;
    *(undefined2 *)(param_1 + 0x1e) = 0;
    uVar1 = *param_2;
    uVar2 = *(undefined4 *)(param_2 + 1);
    uVar3 = *(undefined4 *)((int)param_2 + 0xc);
    *(int *)(param_1 + 0x100) = (int)uVar1;
    *(int *)(param_1 + 0x104) = (int)((ulong)uVar1 >> 0x20);
    *(undefined4 *)(param_1 + 0x108) = uVar2;
    *(undefined4 *)(param_1 + 0x10c) = uVar3;
    *(undefined4 *)(param_1 + 0xdc) = 0;
    *(undefined4 *)(param_1 + 0x84) = 0x44000000;
  }
  *(uint *)(param_1 + 0xd0) = param_3;
  *(undefined4 *)(param_1 + 0xd4) = param_4;
  *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xef | (param_5 & 1) << 4;
  *(int *)(param_1 + 0x140) = 3 << ((param_3 & 0xf) << 1);
  if (param_5 == 0) {
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfe;
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfd;
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfb;
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xf7;
  }
  else {
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0x7f | 0x80;
    *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xfe | 1;
  }
  *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xf7 | 8;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0057dea0  SetHomeCharacterCamera1__9BtlCameraFib
 * C++: BtlCamera::SetHomeCharacterCamera1(int, bool)
 * size: 0x25c bytes
 * --------------------------------------------------------------------------- */
void SetHomeCharacterCamera1__9BtlCameraFib(int param_1,uint param_2,byte param_3)

{
  if (*(int *)(param_1 + 0x210) != -1) {
    release__12LightControlFi(*(undefined4 *)(param_1 + 0x210));
    *(undefined4 *)(param_1 + 0x210) = 0xffffffff;
  }
  if (((long)((ulong)*(byte *)(param_1 + 0x19) << 0x3e) < 0) &&
     ((long)((ulong)*(byte *)(param_1 + 0x19) << 0x3d) < 0)) {
    *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xfd;
    *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xfb;
    *(undefined4 *)(param_1 + 0x214) = 0xffffffff;
  }
  *(undefined2 *)(param_1 + 0x1c) = 6;
  *(undefined2 *)(param_1 + 0x1e) = 0;
  *(uint *)(param_1 + 0xd0) = param_2;
  *(undefined4 *)(param_1 + 0x84) = 0x44000000;
  *(undefined4 *)(param_1 + 0xdc) = 0;
  *(undefined4 *)(param_1 + 0xe0) = 0x41a00000;
  *(int *)(param_1 + 0x140) = 3 << ((param_2 & 0xf) << 1);
  *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xef | (param_3 & 1) << 4;
  if (param_3 == 0) {
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfe;
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfd;
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfb;
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xf7;
  }
  else {
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0x7f | 0x80;
    *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xfe | 1;
  }
  *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xf7 | 8;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0057e100  SetCharacterCamera1__9BtlCameraFib
 * C++: BtlCamera::SetCharacterCamera1(int, bool)
 * size: 0x244 bytes
 * --------------------------------------------------------------------------- */
void SetCharacterCamera1__9BtlCameraFib(int param_1,uint param_2,byte param_3)

{
  if (*(int *)(param_1 + 0x210) != -1) {
    release__12LightControlFi(*(undefined4 *)(param_1 + 0x210));
    *(undefined4 *)(param_1 + 0x210) = 0xffffffff;
  }
  if (((long)((ulong)*(byte *)(param_1 + 0x19) << 0x3e) < 0) &&
     ((long)((ulong)*(byte *)(param_1 + 0x19) << 0x3d) < 0)) {
    *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xfd;
    *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xfb;
    *(undefined4 *)(param_1 + 0x214) = 0xffffffff;
  }
  *(undefined2 *)(param_1 + 0x1c) = 7;
  *(undefined2 *)(param_1 + 0x1e) = 0;
  *(uint *)(param_1 + 0xd0) = param_2;
  *(undefined4 *)(param_1 + 0x84) = 0x44000000;
  *(int *)(param_1 + 0x140) = 3 << ((param_2 & 0xf) << 1);
  *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xef | (param_3 & 1) << 4;
  if (param_3 == 0) {
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfe;
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfd;
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfb;
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xf7;
  }
  else {
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0x7f | 0x80;
    *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xfe | 1;
  }
  *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xf7 | 8;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0057e350  SetCharacterCamera2__9BtlCameraFib
 * C++: BtlCamera::SetCharacterCamera2(int, bool)
 * size: 0x244 bytes
 * --------------------------------------------------------------------------- */
void SetCharacterCamera2__9BtlCameraFib(int param_1,uint param_2,byte param_3)

{
  if (*(int *)(param_1 + 0x210) != -1) {
    release__12LightControlFi(*(undefined4 *)(param_1 + 0x210));
    *(undefined4 *)(param_1 + 0x210) = 0xffffffff;
  }
  if (((long)((ulong)*(byte *)(param_1 + 0x19) << 0x3e) < 0) &&
     ((long)((ulong)*(byte *)(param_1 + 0x19) << 0x3d) < 0)) {
    *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xfd;
    *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xfb;
    *(undefined4 *)(param_1 + 0x214) = 0xffffffff;
  }
  *(undefined2 *)(param_1 + 0x1c) = 8;
  *(undefined2 *)(param_1 + 0x1e) = 0;
  *(uint *)(param_1 + 0xd0) = param_2;
  *(undefined4 *)(param_1 + 0x84) = 0x44000000;
  *(int *)(param_1 + 0x140) = 3 << ((param_2 & 0xf) << 1);
  *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xef | (param_3 & 1) << 4;
  if (param_3 == 0) {
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfe;
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfd;
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfb;
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xf7;
  }
  else {
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0x7f | 0x80;
    *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xfe | 1;
  }
  *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xf7 | 8;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0057e5a0  SetCharacterCamera3__9BtlCameraFib
 * C++: BtlCamera::SetCharacterCamera3(int, bool)
 * size: 0x244 bytes
 * --------------------------------------------------------------------------- */
void SetCharacterCamera3__9BtlCameraFib(int param_1,uint param_2,byte param_3)

{
  if (*(int *)(param_1 + 0x210) != -1) {
    release__12LightControlFi(*(undefined4 *)(param_1 + 0x210));
    *(undefined4 *)(param_1 + 0x210) = 0xffffffff;
  }
  if (((long)((ulong)*(byte *)(param_1 + 0x19) << 0x3e) < 0) &&
     ((long)((ulong)*(byte *)(param_1 + 0x19) << 0x3d) < 0)) {
    *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xfd;
    *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xfb;
    *(undefined4 *)(param_1 + 0x214) = 0xffffffff;
  }
  *(undefined2 *)(param_1 + 0x1c) = 9;
  *(undefined2 *)(param_1 + 0x1e) = 0;
  *(uint *)(param_1 + 0xd0) = param_2;
  *(undefined4 *)(param_1 + 0x84) = 0x44000000;
  *(int *)(param_1 + 0x140) = 3 << ((param_2 & 0xf) << 1);
  *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xef | (param_3 & 1) << 4;
  if (param_3 == 0) {
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfe;
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfd;
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfb;
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xf7;
  }
  else {
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0x7f | 0x80;
    *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xfe | 1;
  }
  *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xf7 | 8;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0057e7f0  SetSingleTargetCamera1__9BtlCameraFib
 * C++: BtlCamera::SetSingleTargetCamera1(int, bool)
 * size: 0x2ac bytes
 * --------------------------------------------------------------------------- */
void SetSingleTargetCamera1__9BtlCameraFib(int param_1,uint param_2,byte param_3)

{
  if (*(int *)(param_1 + 0x210) != -1) {
    release__12LightControlFi(*(undefined4 *)(param_1 + 0x210));
    *(undefined4 *)(param_1 + 0x210) = 0xffffffff;
  }
  if (((long)((ulong)*(byte *)(param_1 + 0x19) << 0x3e) < 0) &&
     ((long)((ulong)*(byte *)(param_1 + 0x19) << 0x3d) < 0)) {
    *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xfd;
    *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xfb;
    *(undefined4 *)(param_1 + 0x214) = 0xffffffff;
  }
  if (*(short *)(param_1 + 0x1c) != 10) {
    *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xef;
    *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xdf;
  }
  *(undefined2 *)(param_1 + 0x1c) = 10;
  *(undefined2 *)(param_1 + 0x1e) = 0;
  *(undefined4 *)(param_1 + 0xdc) = 0;
  *(undefined4 *)(param_1 + 0x84) = 0x44000000;
  *(uint *)(param_1 + 0xd0) = param_2;
  *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xef | (param_3 & 1) << 4;
  *(int *)(param_1 + 0x140) = 3 << ((param_2 & 0xf) << 1);
  if (param_3 == 0) {
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfe;
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfd;
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfb;
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xf7;
  }
  else {
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0x7f | 0x80;
    *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xfe | 1;
  }
  *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xf7 | 8;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0057eaa0  SetSingleTargetCamera2__9BtlCameraFiib
 * C++: BtlCamera::SetSingleTargetCamera2(int, int, bool)
 * size: 0x2e4 bytes
 * --------------------------------------------------------------------------- */
void SetSingleTargetCamera2__9BtlCameraFiib(int param_1,uint param_2,uint param_3,byte param_4)

{
  if (*(int *)(param_1 + 0x210) != -1) {
    release__12LightControlFi(*(undefined4 *)(param_1 + 0x210));
    *(undefined4 *)(param_1 + 0x210) = 0xffffffff;
  }
  if (((long)((ulong)*(byte *)(param_1 + 0x19) << 0x3e) < 0) &&
     ((long)((ulong)*(byte *)(param_1 + 0x19) << 0x3d) < 0)) {
    *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xfd;
    *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xfb;
    *(undefined4 *)(param_1 + 0x214) = 0xffffffff;
  }
  if (*(short *)(param_1 + 0x1c) != 0xb) {
    *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xef;
    *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xdf;
  }
  *(undefined2 *)(param_1 + 0x1c) = 0xb;
  *(undefined2 *)(param_1 + 0x1e) = 0;
  *(uint *)(param_1 + 0xd0) = param_2;
  *(uint *)(param_1 + 0xd4) = param_3;
  *(undefined4 *)(param_1 + 0x84) = 0x44000000;
  *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0x3f;
  *(int *)(param_1 + 0x140) = 3 << ((param_2 & 0xf) << 1) | 3 << ((param_3 & 0xf) << 1);
  *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xef | (param_4 & 1) << 4;
  if (param_4 == 0) {
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfe;
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfd;
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfb;
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xf7;
  }
  else {
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0x7f | 0x80;
    *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xfe | 1;
  }
  *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xf7 | 8;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0057ed90  SetCircleTargetCamera1__9BtlCameraFiiiiP8ECCParamb
 * C++: BtlCamera::SetCircleTargetCamera1(int, int, int, int, ECCParam *, bool)
 * size: 0x340 bytes
 * --------------------------------------------------------------------------- */
void SetCircleTargetCamera1__9BtlCameraFiiiiP8ECCParamb
               (int param_1,int param_2,int param_3,int param_4,int param_5,void *param_6,
               byte param_7)

{
  int iVar1;
  uint auStack_b0 [15];
  int iStack_74;
  int iStack_70;
  int iStack_60;
  int iStack_50;
  int iStack_40;
  int iStack_30;
  void *pvStack_20;
  byte bStack_10;
  
  iStack_70 = param_1;
  iStack_60 = param_2;
  iStack_50 = param_3;
  iStack_40 = param_4;
  iStack_30 = param_5;
  pvStack_20 = param_6;
  bStack_10 = param_7;
  if (*(int *)(param_1 + 0x210) != -1) {
    release__12LightControlFi(*(undefined4 *)(param_1 + 0x210));
    *(undefined4 *)(iStack_70 + 0x210) = 0xffffffff;
  }
  if (((long)((ulong)*(byte *)(iStack_70 + 0x19) << 0x3e) < 0) &&
     ((long)((ulong)*(byte *)(iStack_70 + 0x19) << 0x3d) < 0)) {
    *(byte *)(iStack_70 + 0x19) = *(byte *)(iStack_70 + 0x19) & 0xfd;
    *(byte *)(iStack_70 + 0x19) = *(byte *)(iStack_70 + 0x19) & 0xfb;
    *(undefined4 *)(iStack_70 + 0x214) = 0xffffffff;
  }
  if (*(short *)(iStack_70 + 0x1c) != 0xc) {
    *(byte *)(iStack_70 + 0x19) = *(byte *)(iStack_70 + 0x19) & 0xef | 0x10;
    *(byte *)(iStack_70 + 0x19) = *(byte *)(iStack_70 + 0x19) & 0xdf;
  }
  *(undefined2 *)(iStack_70 + 0x1c) = 0xc;
  *(undefined2 *)(iStack_70 + 0x1e) = 0;
  *(int *)(iStack_70 + 0xd0) = iStack_60;
  *(int *)(iStack_70 + 0xd4) = iStack_50;
  *(int *)(iStack_70 + 0xd8) = iStack_30;
  *(undefined4 *)(iStack_70 + 0x84) = 0x44000000;
  *(byte *)(iStack_70 + 0x18) = *(byte *)(iStack_70 + 0x18) & 0xef | (bStack_10 & 1) << 4;
  GetTargetList__7CBattleFiiiiiP8ECCParamPiPi
            (pCGpffff86b4,iStack_60,iStack_50,iStack_40,1,iStack_30,pvStack_20,&iStack_74,
             (int *)auStack_b0);
  *(undefined4 *)(iStack_70 + 0x140) = 0;
  for (iVar1 = 0; iVar1 < iStack_74; iVar1 = iVar1 + 1) {
    *(uint *)(iStack_70 + 0x140) =
         *(uint *)(iStack_70 + 0x140) | 3 << ((auStack_b0[iVar1] & 0xf) << 1);
  }
  if (bStack_10 == 0) {
    *(byte *)(iStack_70 + 0x18) = *(byte *)(iStack_70 + 0x18) & 0xfe;
    *(byte *)(iStack_70 + 0x18) = *(byte *)(iStack_70 + 0x18) & 0xfd;
    *(byte *)(iStack_70 + 0x18) = *(byte *)(iStack_70 + 0x18) & 0xfb;
    *(byte *)(iStack_70 + 0x18) = *(byte *)(iStack_70 + 0x18) & 0xf7;
  }
  else {
    *(byte *)(iStack_70 + 0x18) = *(byte *)(iStack_70 + 0x18) & 0x7f | 0x80;
    *(byte *)(iStack_70 + 0x19) = *(byte *)(iStack_70 + 0x19) & 0xfe | 1;
  }
  *(byte *)(iStack_70 + 0x19) = *(byte *)(iStack_70 + 0x19) & 0xf7 | 8;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0057f0d0  SetStraightTargetCamera1__9BtlCameraFiiiiP8ECCParamb
 * C++: BtlCamera::SetStraightTargetCamera1(int, int, int, int, ECCParam *, bool)
 * size: 0x350 bytes
 * --------------------------------------------------------------------------- */
void SetStraightTargetCamera1__9BtlCameraFiiiiP8ECCParamb
               (int param_1,uint param_2,int param_3,int param_4,int param_5,void *param_6,
               byte param_7)

{
  int iVar1;
  uint auStack_b0 [15];
  int iStack_74;
  int iStack_70;
  uint uStack_60;
  int iStack_50;
  int iStack_40;
  int iStack_30;
  void *pvStack_20;
  byte bStack_10;
  
  iStack_70 = param_1;
  uStack_60 = param_2;
  iStack_50 = param_3;
  iStack_40 = param_4;
  iStack_30 = param_5;
  pvStack_20 = param_6;
  bStack_10 = param_7;
  if (*(int *)(param_1 + 0x210) != -1) {
    release__12LightControlFi(*(undefined4 *)(param_1 + 0x210));
    *(undefined4 *)(iStack_70 + 0x210) = 0xffffffff;
  }
  if (((long)((ulong)*(byte *)(iStack_70 + 0x19) << 0x3e) < 0) &&
     ((long)((ulong)*(byte *)(iStack_70 + 0x19) << 0x3d) < 0)) {
    *(byte *)(iStack_70 + 0x19) = *(byte *)(iStack_70 + 0x19) & 0xfd;
    *(byte *)(iStack_70 + 0x19) = *(byte *)(iStack_70 + 0x19) & 0xfb;
    *(undefined4 *)(iStack_70 + 0x214) = 0xffffffff;
  }
  if (*(short *)(iStack_70 + 0x1c) != 0xd) {
    *(byte *)(iStack_70 + 0x19) = *(byte *)(iStack_70 + 0x19) & 0xef | 0x10;
    *(byte *)(iStack_70 + 0x19) = *(byte *)(iStack_70 + 0x19) & 0xdf;
  }
  *(undefined2 *)(iStack_70 + 0x1c) = 0xd;
  *(undefined2 *)(iStack_70 + 0x1e) = 0;
  *(uint *)(iStack_70 + 0xd0) = uStack_60;
  *(int *)(iStack_70 + 0xd4) = iStack_50;
  *(int *)(iStack_70 + 0xd8) = iStack_30;
  *(undefined4 *)(iStack_70 + 0x84) = 0x44000000;
  *(byte *)(iStack_70 + 0x18) = *(byte *)(iStack_70 + 0x18) & 0xef | (bStack_10 & 1) << 4;
  GetTargetList__7CBattleFiiiiiP8ECCParamPiPi
            (pCGpffff86b4,uStack_60,iStack_50,iStack_40,3,iStack_30,pvStack_20,&iStack_74,
             (int *)auStack_b0);
  *(int *)(iStack_70 + 0x140) = 3 << ((uStack_60 & 0xf) << 1);
  for (iVar1 = 0; iVar1 < iStack_74; iVar1 = iVar1 + 1) {
    *(uint *)(iStack_70 + 0x140) =
         *(uint *)(iStack_70 + 0x140) | 3 << ((auStack_b0[iVar1] & 0xf) << 1);
  }
  if (bStack_10 == 0) {
    *(byte *)(iStack_70 + 0x18) = *(byte *)(iStack_70 + 0x18) & 0xfe;
    *(byte *)(iStack_70 + 0x18) = *(byte *)(iStack_70 + 0x18) & 0xfd;
    *(byte *)(iStack_70 + 0x18) = *(byte *)(iStack_70 + 0x18) & 0xfb;
    *(byte *)(iStack_70 + 0x18) = *(byte *)(iStack_70 + 0x18) & 0xf7;
  }
  else {
    *(byte *)(iStack_70 + 0x18) = *(byte *)(iStack_70 + 0x18) & 0x7f | 0x80;
    *(byte *)(iStack_70 + 0x19) = *(byte *)(iStack_70 + 0x19) & 0xfe | 1;
  }
  *(byte *)(iStack_70 + 0x19) = *(byte *)(iStack_70 + 0x19) & 0xf7 | 8;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0057f420  SetStraightEXTargetCamera1__9BtlCameraFiiiiP8ECCParamb
 * C++: BtlCamera::SetStraightEXTargetCamera1(int, int, int, int, ECCParam *, bool)
 * size: 0x350 bytes
 * --------------------------------------------------------------------------- */
void SetStraightEXTargetCamera1__9BtlCameraFiiiiP8ECCParamb
               (int param_1,uint param_2,int param_3,int param_4,int param_5,void *param_6,
               byte param_7)

{
  int iVar1;
  uint auStack_b0 [15];
  int iStack_74;
  int iStack_70;
  uint uStack_60;
  int iStack_50;
  int iStack_40;
  int iStack_30;
  void *pvStack_20;
  byte bStack_10;
  
  iStack_70 = param_1;
  uStack_60 = param_2;
  iStack_50 = param_3;
  iStack_40 = param_4;
  iStack_30 = param_5;
  pvStack_20 = param_6;
  bStack_10 = param_7;
  if (*(int *)(param_1 + 0x210) != -1) {
    release__12LightControlFi(*(undefined4 *)(param_1 + 0x210));
    *(undefined4 *)(iStack_70 + 0x210) = 0xffffffff;
  }
  if (((long)((ulong)*(byte *)(iStack_70 + 0x19) << 0x3e) < 0) &&
     ((long)((ulong)*(byte *)(iStack_70 + 0x19) << 0x3d) < 0)) {
    *(byte *)(iStack_70 + 0x19) = *(byte *)(iStack_70 + 0x19) & 0xfd;
    *(byte *)(iStack_70 + 0x19) = *(byte *)(iStack_70 + 0x19) & 0xfb;
    *(undefined4 *)(iStack_70 + 0x214) = 0xffffffff;
  }
  if (*(short *)(iStack_70 + 0x1c) != 0xe) {
    *(byte *)(iStack_70 + 0x19) = *(byte *)(iStack_70 + 0x19) & 0xef | 0x10;
    *(byte *)(iStack_70 + 0x19) = *(byte *)(iStack_70 + 0x19) & 0xdf;
  }
  *(undefined2 *)(iStack_70 + 0x1c) = 0xe;
  *(undefined2 *)(iStack_70 + 0x1e) = 0;
  *(uint *)(iStack_70 + 0xd0) = uStack_60;
  *(int *)(iStack_70 + 0xd4) = iStack_50;
  *(int *)(iStack_70 + 0xd8) = iStack_30;
  *(undefined4 *)(iStack_70 + 0x84) = 0x44000000;
  *(byte *)(iStack_70 + 0x18) = *(byte *)(iStack_70 + 0x18) & 0xef | (bStack_10 & 1) << 4;
  GetTargetList__7CBattleFiiiiiP8ECCParamPiPi
            (pCGpffff86b4,uStack_60,iStack_50,iStack_40,4,iStack_30,pvStack_20,&iStack_74,
             (int *)auStack_b0);
  *(int *)(iStack_70 + 0x140) = 3 << ((uStack_60 & 0xf) << 1);
  for (iVar1 = 0; iVar1 < iStack_74; iVar1 = iVar1 + 1) {
    *(uint *)(iStack_70 + 0x140) =
         *(uint *)(iStack_70 + 0x140) | 3 << ((auStack_b0[iVar1] & 0xf) << 1);
  }
  if (bStack_10 == 0) {
    *(byte *)(iStack_70 + 0x18) = *(byte *)(iStack_70 + 0x18) & 0xfe;
    *(byte *)(iStack_70 + 0x18) = *(byte *)(iStack_70 + 0x18) & 0xfd;
    *(byte *)(iStack_70 + 0x18) = *(byte *)(iStack_70 + 0x18) & 0xfb;
    *(byte *)(iStack_70 + 0x18) = *(byte *)(iStack_70 + 0x18) & 0xf7;
  }
  else {
    *(byte *)(iStack_70 + 0x18) = *(byte *)(iStack_70 + 0x18) & 0x7f | 0x80;
    *(byte *)(iStack_70 + 0x19) = *(byte *)(iStack_70 + 0x19) & 0xfe | 1;
  }
  *(byte *)(iStack_70 + 0x19) = *(byte *)(iStack_70 + 0x19) & 0xf7 | 8;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0057f770  SetAllTargetCamera1__9BtlCameraFiiiP8ECCParamb
 * C++: BtlCamera::SetAllTargetCamera1(int, int, int, ECCParam *, bool)
 * size: 0x2e8 bytes
 * --------------------------------------------------------------------------- */
void SetAllTargetCamera1__9BtlCameraFiiiP8ECCParamb
               (int param_1,uint param_2,int param_3,int param_4,void *param_5,byte param_6)

{
  int iVar1;
  uint auStack_a0 [15];
  int iStack_64;
  int iStack_60;
  uint uStack_50;
  int iStack_40;
  int iStack_30;
  void *pvStack_20;
  byte bStack_10;
  
  iStack_60 = param_1;
  uStack_50 = param_2;
  iStack_40 = param_3;
  iStack_30 = param_4;
  pvStack_20 = param_5;
  bStack_10 = param_6;
  if (*(int *)(param_1 + 0x210) != -1) {
    release__12LightControlFi(*(undefined4 *)(param_1 + 0x210));
    *(undefined4 *)(iStack_60 + 0x210) = 0xffffffff;
  }
  if (((long)((ulong)*(byte *)(iStack_60 + 0x19) << 0x3e) < 0) &&
     ((long)((ulong)*(byte *)(iStack_60 + 0x19) << 0x3d) < 0)) {
    *(byte *)(iStack_60 + 0x19) = *(byte *)(iStack_60 + 0x19) & 0xfd;
    *(byte *)(iStack_60 + 0x19) = *(byte *)(iStack_60 + 0x19) & 0xfb;
    *(undefined4 *)(iStack_60 + 0x214) = 0xffffffff;
  }
  *(undefined2 *)(iStack_60 + 0x1c) = 0xf;
  *(undefined2 *)(iStack_60 + 0x1e) = 0;
  *(uint *)(iStack_60 + 0xd0) = uStack_50;
  *(int *)(iStack_60 + 0xd8) = iStack_30;
  *(undefined4 *)(iStack_60 + 0x84) = 0x44000000;
  *(byte *)(iStack_60 + 0x18) = *(byte *)(iStack_60 + 0x18) & 0xef | (bStack_10 & 1) << 4;
  GetTargetList__7CBattleFiiiiiP8ECCParamPiPi
            (pCGpffff86b4,uStack_50,-1,iStack_40,5,iStack_30,pvStack_20,&iStack_64,(int *)auStack_a0
            );
  *(int *)(iStack_60 + 0x140) = 3 << ((uStack_50 & 0xf) << 1);
  for (iVar1 = 0; iVar1 < iStack_64; iVar1 = iVar1 + 1) {
    *(uint *)(iStack_60 + 0x140) =
         *(uint *)(iStack_60 + 0x140) | 3 << ((auStack_a0[iVar1] & 0xf) << 1);
  }
  if (bStack_10 == 0) {
    *(byte *)(iStack_60 + 0x18) = *(byte *)(iStack_60 + 0x18) & 0xfe;
    *(byte *)(iStack_60 + 0x18) = *(byte *)(iStack_60 + 0x18) & 0xfd;
    *(byte *)(iStack_60 + 0x18) = *(byte *)(iStack_60 + 0x18) & 0xfb;
    *(byte *)(iStack_60 + 0x18) = *(byte *)(iStack_60 + 0x18) & 0xf7;
  }
  else {
    *(byte *)(iStack_60 + 0x18) = *(byte *)(iStack_60 + 0x18) & 0x7f | 0x80;
    *(byte *)(iStack_60 + 0x19) = *(byte *)(iStack_60 + 0x19) & 0xfe | 1;
  }
  *(byte *)(iStack_60 + 0x19) = *(byte *)(iStack_60 + 0x19) & 0xf7 | 8;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0057fa60  SetMoveTargetCamera1__9BtlCameraF7FVectorib
 * C++: BtlCamera::SetMoveTargetCamera1(FVector, int, bool)
 * size: 0x230 bytes
 * --------------------------------------------------------------------------- */
void SetMoveTargetCamera1__9BtlCameraF7FVectorib
               (int param_1,undefined8 *param_2,uint param_3,byte param_4)

{
  undefined8 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  if (*(int *)(param_1 + 0x210) != -1) {
    release__12LightControlFi(*(undefined4 *)(param_1 + 0x210));
    *(undefined4 *)(param_1 + 0x210) = 0xffffffff;
  }
  if (((long)((ulong)*(byte *)(param_1 + 0x19) << 0x3e) < 0) &&
     ((long)((ulong)*(byte *)(param_1 + 0x19) << 0x3d) < 0)) {
    *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xfd;
    *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xfb;
    *(undefined4 *)(param_1 + 0x214) = 0xffffffff;
  }
  if (*(short *)(param_1 + 0x1c) != 0x10) {
    *(undefined2 *)(param_1 + 0x1c) = 0x10;
    *(undefined2 *)(param_1 + 0x1e) = 0;
    uVar1 = *param_2;
    uVar2 = *(undefined4 *)(param_2 + 1);
    uVar3 = *(undefined4 *)((int)param_2 + 0xc);
    *(int *)(param_1 + 0x100) = (int)uVar1;
    *(int *)(param_1 + 0x104) = (int)((ulong)uVar1 >> 0x20);
    *(undefined4 *)(param_1 + 0x108) = uVar2;
    *(undefined4 *)(param_1 + 0x10c) = uVar3;
    *(undefined4 *)(param_1 + 0xdc) = 0;
    *(undefined4 *)(param_1 + 0x84) = 0x44000000;
  }
  *(uint *)(param_1 + 0xd0) = param_3;
  *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xef | (param_4 & 1) << 4;
  *(int *)(param_1 + 0x140) = 3 << ((param_3 & 0xf) << 1);
  if (param_4 == 0) {
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfe;
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfd;
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfb;
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xf7;
  }
  else {
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0x7f | 0x80;
    *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xfe | 1;
  }
  *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xf7 | 8;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0057fc90  SetJudgementRingCamera1__9BtlCameraFiib
 * C++: BtlCamera::SetJudgementRingCamera1(int, int, bool)
 * size: 0x264 bytes
 * --------------------------------------------------------------------------- */
void SetJudgementRingCamera1__9BtlCameraFiib(int param_1,uint param_2,uint param_3,byte param_4)

{
  if (*(int *)(param_1 + 0x210) != -1) {
    release__12LightControlFi(*(undefined4 *)(param_1 + 0x210));
    *(undefined4 *)(param_1 + 0x210) = 0xffffffff;
  }
  if (((long)((ulong)*(byte *)(param_1 + 0x19) << 0x3e) < 0) &&
     ((long)((ulong)*(byte *)(param_1 + 0x19) << 0x3d) < 0)) {
    *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xfd;
    *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xfb;
    *(undefined4 *)(param_1 + 0x214) = 0xffffffff;
  }
  *(undefined2 *)(param_1 + 0x1c) = 0x11;
  *(undefined2 *)(param_1 + 0x1e) = 0;
  *(uint *)(param_1 + 0xd0) = param_2;
  *(uint *)(param_1 + 0xd4) = param_3;
  *(undefined4 *)(param_1 + 0x84) = 0x44000000;
  *(int *)(param_1 + 0x140) = 3 << ((param_2 & 0xf) << 1) | 3 << ((param_3 & 0xf) << 1);
  *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xef | (param_4 & 1) << 4;
  if (param_4 == 0) {
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfe;
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfd;
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfb;
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xf7;
  }
  else {
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0x7f | 0x80;
    *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xfe | 1;
  }
  *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xf7 | 8;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0057ff00  SetAttackMoveCamera1__9BtlCameraFiib
 * C++: BtlCamera::SetAttackMoveCamera1(int, int, bool)
 * size: 0x264 bytes
 * --------------------------------------------------------------------------- */
void SetAttackMoveCamera1__9BtlCameraFiib(int param_1,uint param_2,uint param_3,byte param_4)

{
  if (*(int *)(param_1 + 0x210) != -1) {
    release__12LightControlFi(*(undefined4 *)(param_1 + 0x210));
    *(undefined4 *)(param_1 + 0x210) = 0xffffffff;
  }
  if (((long)((ulong)*(byte *)(param_1 + 0x19) << 0x3e) < 0) &&
     ((long)((ulong)*(byte *)(param_1 + 0x19) << 0x3d) < 0)) {
    *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xfd;
    *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xfb;
    *(undefined4 *)(param_1 + 0x214) = 0xffffffff;
  }
  *(undefined2 *)(param_1 + 0x1c) = 0x12;
  *(undefined2 *)(param_1 + 0x1e) = 0;
  *(uint *)(param_1 + 0xd0) = param_2;
  *(uint *)(param_1 + 0xd4) = param_3;
  *(undefined4 *)(param_1 + 0x84) = 0x44000000;
  *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xef | (param_4 & 1) << 4;
  *(int *)(param_1 + 0x140) = 3 << ((param_2 & 0xf) << 1) | 3 << ((param_3 & 0xf) << 1);
  if (param_4 == 0) {
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfe;
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfd;
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfb;
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xf7;
  }
  else {
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0x7f | 0x80;
    *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xfe | 1;
  }
  *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xf7 | 8;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00580170  SetAttackCamera1__9BtlCameraFiiib
 * C++: BtlCamera::SetAttackCamera1(int, int, int, bool)
 * size: 0x27c bytes
 * --------------------------------------------------------------------------- */
void SetAttackCamera1__9BtlCameraFiiib
               (int param_1,uint param_2,uint param_3,undefined4 param_4,byte param_5)

{
  if (*(int *)(param_1 + 0x210) != -1) {
    release__12LightControlFi(*(undefined4 *)(param_1 + 0x210));
    *(undefined4 *)(param_1 + 0x210) = 0xffffffff;
  }
  if (((long)((ulong)*(byte *)(param_1 + 0x19) << 0x3e) < 0) &&
     ((long)((ulong)*(byte *)(param_1 + 0x19) << 0x3d) < 0)) {
    *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xfd;
    *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xfb;
    *(undefined4 *)(param_1 + 0x214) = 0xffffffff;
  }
  *(undefined2 *)(param_1 + 0x1c) = 0x13;
  *(undefined2 *)(param_1 + 0x1e) = 0;
  *(uint *)(param_1 + 0xd0) = param_2;
  *(uint *)(param_1 + 0xd4) = param_3;
  *(undefined4 *)(param_1 + 0xd8) = param_4;
  *(undefined4 *)(param_1 + 0x84) = 0x44000000;
  *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xef | (param_5 & 1) << 4;
  *(int *)(param_1 + 0x140) = 3 << ((param_2 & 0xf) << 1) | 3 << ((param_3 & 0xf) << 1);
  if (param_5 == 0) {
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfe;
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfd;
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfb;
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xf7;
  }
  else {
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0x7f | 0x80;
    *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xfe | 1;
  }
  *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xf7 | 8;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005803f0  SetMoveCamera1__9BtlCameraFi7FVectorib
 * C++: BtlCamera::SetMoveCamera1(int, FVector, int, bool)
 * size: 0x244 bytes
 * --------------------------------------------------------------------------- */
void SetMoveCamera1__9BtlCameraFi7FVectorib
               (int param_1,uint param_2,undefined8 *param_3,long param_4,byte param_5)

{
  undefined8 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  if (*(int *)(param_1 + 0x210) != -1) {
    release__12LightControlFi(*(undefined4 *)(param_1 + 0x210));
    *(undefined4 *)(param_1 + 0x210) = 0xffffffff;
  }
  if (((long)((ulong)*(byte *)(param_1 + 0x19) << 0x3e) < 0) &&
     ((long)((ulong)*(byte *)(param_1 + 0x19) << 0x3d) < 0)) {
    *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xfd;
    *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xfb;
    *(undefined4 *)(param_1 + 0x214) = 0xffffffff;
  }
  *(undefined2 *)(param_1 + 0x1c) = 0x14;
  *(undefined2 *)(param_1 + 0x1e) = 0;
  *(uint *)(param_1 + 0xd0) = param_2;
  uVar1 = *param_3;
  uVar2 = *(undefined4 *)(param_3 + 1);
  uVar3 = *(undefined4 *)((int)param_3 + 0xc);
  *(int *)(param_1 + 0x100) = (int)uVar1;
  *(int *)(param_1 + 0x104) = (int)((ulong)uVar1 >> 0x20);
  *(undefined4 *)(param_1 + 0x108) = uVar2;
  *(undefined4 *)(param_1 + 0x10c) = uVar3;
  *(undefined4 *)(param_1 + 0x84) = 0x44000000;
  *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xef | (param_5 & 1) << 4;
  *(int *)(param_1 + 0x140) = 3 << ((param_2 & 0xf) << 1);
  if (param_4 != -1) {
    *(uint *)(param_1 + 0x140) = *(uint *)(param_1 + 0x140) | 3 << (((uint)param_4 & 0xf) << 1);
  }
  if (param_5 == 0) {
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfe;
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfd;
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfb;
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xf7;
  }
  else {
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0x7f | 0x80;
    *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xfe | 1;
  }
  *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xf7 | 8;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00580640  SetComboMemberCamera1__9BtlCameraFib
 * C++: BtlCamera::SetComboMemberCamera1(int, bool)
 * size: 0x2b8 bytes
 * --------------------------------------------------------------------------- */
void SetComboMemberCamera1__9BtlCameraFib(int param_1,uint param_2,byte param_3)

{
  uint uVar1;
  
  if (*(int *)(param_1 + 0x210) != -1) {
    release__12LightControlFi(*(undefined4 *)(param_1 + 0x210));
    *(undefined4 *)(param_1 + 0x210) = 0xffffffff;
  }
  if (((long)((ulong)*(byte *)(param_1 + 0x19) << 0x3e) < 0) &&
     ((long)((ulong)*(byte *)(param_1 + 0x19) << 0x3d) < 0)) {
    *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xfd;
    *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xfb;
    *(undefined4 *)(param_1 + 0x214) = 0xffffffff;
  }
  if (*(short *)(param_1 + 0x1c) != 0x15) {
    *(undefined2 *)(param_1 + 0x1c) = 0x15;
    *(undefined2 *)(param_1 + 0x1e) = 0;
    *(undefined4 *)(param_1 + 0xdc) = 0;
    *(undefined4 *)(param_1 + 0x84) = 0x44000000;
  }
  *(uint *)(param_1 + 0xd0) = param_2;
  *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xef | (param_3 & 1) << 4;
  *(undefined4 *)(param_1 + 0x140) = 0;
  for (uVar1 = 0; (int)uVar1 < 0xc; uVar1 = uVar1 + 1) {
    if ((param_2 & 1 << (uVar1 & 0x1f)) != 0) {
      *(uint *)(param_1 + 0x140) = *(uint *)(param_1 + 0x140) | 3 << ((uVar1 & 0xf) << 1);
    }
  }
  if (param_3 == 0) {
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfe;
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfd;
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfb;
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xf7;
  }
  else {
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0x7f | 0x80;
    *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xfe | 1;
  }
  *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xf7 | 8;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00580900  SetComboMemberCamera2__9BtlCameraFiib
 * C++: BtlCamera::SetComboMemberCamera2(int, int, bool)
 * size: 0x2d8 bytes
 * --------------------------------------------------------------------------- */
void SetComboMemberCamera2__9BtlCameraFiib(int param_1,uint param_2,uint param_3,byte param_4)

{
  uint uVar1;
  
  if (*(int *)(param_1 + 0x210) != -1) {
    release__12LightControlFi(*(undefined4 *)(param_1 + 0x210));
    *(undefined4 *)(param_1 + 0x210) = 0xffffffff;
  }
  if (((long)((ulong)*(byte *)(param_1 + 0x19) << 0x3e) < 0) &&
     ((long)((ulong)*(byte *)(param_1 + 0x19) << 0x3d) < 0)) {
    *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xfd;
    *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xfb;
    *(undefined4 *)(param_1 + 0x214) = 0xffffffff;
  }
  if (*(short *)(param_1 + 0x1c) != 0x16) {
    *(undefined2 *)(param_1 + 0x1c) = 0x16;
    *(undefined2 *)(param_1 + 0x1e) = 0;
    *(undefined4 *)(param_1 + 0xdc) = 0;
    *(undefined4 *)(param_1 + 0x84) = 0x44000000;
  }
  *(uint *)(param_1 + 0xd0) = param_2;
  *(uint *)(param_1 + 0xd4) = param_3;
  *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xef | (param_4 & 1) << 4;
  *(int *)(param_1 + 0x140) = 3 << ((param_3 & 0xf) << 1);
  for (uVar1 = 0; (int)uVar1 < 0xc; uVar1 = uVar1 + 1) {
    if ((param_2 & 1 << (uVar1 & 0x1f)) != 0) {
      *(uint *)(param_1 + 0x140) = *(uint *)(param_1 + 0x140) | 3 << ((uVar1 & 0xf) << 1);
    }
  }
  if (param_4 == 0) {
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfe;
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfd;
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfb;
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xf7;
  }
  else {
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0x7f | 0x80;
    *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xfe | 1;
  }
  *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xf7 | 8;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00580be0  SetWinCamera1__9BtlCameraFib
 * C++: BtlCamera::SetWinCamera1(int, bool)
 * size: 0x3ac bytes
 * --------------------------------------------------------------------------- */
void SetWinCamera1__9BtlCameraFib(int param_1,int param_2,byte param_3)

{
  uint uVar1;
  float fVar2;
  undefined1 auVar3 [16];
  undefined1 auVar4 [16];
  undefined1 auStack_20 [16];
  undefined1 auStack_10 [8];
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  if (*(int *)(param_1 + 0x210) != -1) {
    release__12LightControlFi(*(undefined4 *)(param_1 + 0x210));
    *(undefined4 *)(param_1 + 0x210) = 0xffffffff;
  }
  if (((long)((ulong)*(byte *)(param_1 + 0x19) << 0x3e) < 0) &&
     ((long)((ulong)*(byte *)(param_1 + 0x19) << 0x3d) < 0)) {
    *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xfd;
    *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xfb;
    *(undefined4 *)(param_1 + 0x214) = 0xffffffff;
  }
  *(undefined2 *)(param_1 + 0x1c) = 0x18;
  *(undefined2 *)(param_1 + 0x1e) = 0;
  *(int *)(param_1 + 0xd0) = param_2;
  *(undefined4 *)(param_1 + 0x84) = 0x44000000;
  *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xef | (param_3 & 1) << 4;
  *(undefined4 *)(param_1 + 0x140) = 0;
  for (uVar1 = 0; (int)uVar1 < 0xc; uVar1 = uVar1 + 1) {
    if (((((*(byte *)(iGpffff86b4 + uVar1 * 0x4f0 + 0xb0) & 1) != 0) &&
         ((long)((ulong)*(byte *)(iGpffff86b4 + uVar1 * 0x4f0 + 0xb0) << 0x3e) < 0)) &&
        (-1 < (long)((ulong)*(byte *)(iGpffff86b4 + uVar1 * 0x4f0 + 0xb2) << 0x3d))) &&
       ((*(byte *)(iGpffff86b4 + uVar1 * 0x4f0 + 0xb4) & 1) == 0)) {
      *(uint *)(param_1 + 0x140) = *(uint *)(param_1 + 0x140) | 3 << ((uVar1 & 0xf) << 1);
    }
  }
  auVar3 = _lqc2(*(undefined1 (*) [16])(iGpffff86b4 + param_2 * 0x4f0 + 0x150));
  auVar4 = _lqc2(*(undefined1 (*) [16])(iGpffff86b4 + param_2 * 0x4f0 + 0x390));
  auVar3 = _vadd(auVar3,auVar4);
  auStack_20 = _sqc2(auVar3);
  __ct__7FVectorFRC7FVector(auStack_10,auStack_20);
  *(int *)(param_1 + 0x70) = auStack_10._0_4_;
  *(int *)(param_1 + 0x74) = auStack_10._4_4_;
  *(undefined4 *)(param_1 + 0x78) = uStack_8;
  *(undefined4 *)(param_1 + 0x7c) = uStack_4;
  fVar2 = (float)Length__7FVectorCFv(iGpffff86b4 + param_2 * 0x4f0 + 0x3a0);
  *(float *)(param_1 + 0xec) = *(float *)(iGpffff86b4 + param_2 * 0x4f0 + 0x3b0) + fVar2;
  if (param_3 == 0) {
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfe;
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfd;
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfb;
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xf7;
  }
  else {
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0x7f | 0x80;
    *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xfe | 1;
  }
  *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xf7 | 8;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00580f90  SetLoseCamera1__9BtlCameraFb
 * C++: BtlCamera::SetLoseCamera1(bool)
 * size: 0x328 bytes
 * --------------------------------------------------------------------------- */
void SetLoseCamera1__9BtlCameraFb(int param_1,byte param_2)

{
  uint uVar1;
  
  if (*(int *)(param_1 + 0x210) != -1) {
    release__12LightControlFi(*(undefined4 *)(param_1 + 0x210));
    *(undefined4 *)(param_1 + 0x210) = 0xffffffff;
  }
  if (((long)((ulong)*(byte *)(param_1 + 0x19) << 0x3e) < 0) &&
     ((long)((ulong)*(byte *)(param_1 + 0x19) << 0x3d) < 0)) {
    *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xfd;
    *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xfb;
    *(undefined4 *)(param_1 + 0x214) = 0xffffffff;
  }
  *(undefined2 *)(param_1 + 0x1c) = 0x19;
  *(undefined2 *)(param_1 + 0x1e) = 0;
  *(undefined4 *)(param_1 + 0x84) = 0x44000000;
  *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xef | (param_2 & 1) << 4;
  *(undefined4 *)(param_1 + 0x140) = 0;
  for (uVar1 = 0; (int)uVar1 < 0xc; uVar1 = uVar1 + 1) {
    if (((((*(byte *)(iGpffff86b4 + uVar1 * 0x4f0 + 0xb0) & 1) != 0) &&
         ((long)((ulong)*(byte *)(iGpffff86b4 + uVar1 * 0x4f0 + 0xb0) << 0x3e) < 0)) &&
        (-1 < (long)((ulong)*(byte *)(iGpffff86b4 + uVar1 * 0x4f0 + 0xb2) << 0x3d))) &&
       ((*(byte *)(iGpffff86b4 + uVar1 * 0x4f0 + 0xb4) & 1) == 0)) {
      *(uint *)(param_1 + 0x140) = *(uint *)(param_1 + 0x140) | 3 << ((uVar1 & 0xf) << 1);
    }
  }
  if (param_2 == 0) {
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfe;
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfd;
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfb;
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xf7;
  }
  else {
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0x7f | 0x80;
    *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xfe | 1;
  }
  *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xf7 | 8;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005812c0  SetFusionCamera1__9BtlCameraFiib
 * C++: BtlCamera::SetFusionCamera1(int, int, bool)
 * size: 0x274 bytes
 * --------------------------------------------------------------------------- */
void SetFusionCamera1__9BtlCameraFiib(int param_1,uint param_2,uint param_3,byte param_4)

{
  if (*(int *)(param_1 + 0x210) != -1) {
    release__12LightControlFi(*(undefined4 *)(param_1 + 0x210));
    *(undefined4 *)(param_1 + 0x210) = 0xffffffff;
  }
  if (((long)((ulong)*(byte *)(param_1 + 0x19) << 0x3e) < 0) &&
     ((long)((ulong)*(byte *)(param_1 + 0x19) << 0x3d) < 0)) {
    *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xfd;
    *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xfb;
    *(undefined4 *)(param_1 + 0x214) = 0xffffffff;
  }
  *(undefined2 *)(param_1 + 0x1c) = 0x1a;
  *(undefined2 *)(param_1 + 0x1e) = 0;
  *(uint *)(param_1 + 0xd0) = param_2;
  *(undefined4 *)(param_1 + 0x84) = 0x44000000;
  *(undefined4 *)(param_1 + 0xdc) = 0;
  *(undefined4 *)(param_1 + 0xe0) = 0x41a00000;
  *(int *)(param_1 + 0x140) = 3 << ((param_2 & 0xf) << 1) | 3 << ((param_3 & 0xf) << 1);
  *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xef | (param_4 & 1) << 4;
  if (param_4 == 0) {
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfe;
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfd;
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfb;
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xf7;
  }
  else {
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0x7f | 0x80;
    *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xfe | 1;
  }
  *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) & 0xf7 | 8;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00581540  BtlCameraFunc__9BtlCameraFv
 * C++: BtlCamera::BtlCameraFunc()
 * size: 0x758 bytes
 * --------------------------------------------------------------------------- */
void BtlCameraFunc__9BtlCameraFv(undefined8 param_1)

{
  byte bVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  long lVar4;
  int iVar5;
  undefined1 auStack_120 [16];
  undefined1 auStack_110 [16];
  undefined1 auStack_100 [16];
  undefined1 auStack_f0 [16];
  undefined1 auStack_e0 [16];
  undefined1 auStack_d0 [16];
  undefined1 auStack_c0 [16];
  undefined1 auStack_b0 [16];
  undefined1 auStack_a0 [16];
  undefined4 uStack_90;
  undefined4 uStack_8c;
  undefined4 uStack_88;
  undefined4 uStack_84;
  float fStack_80;
  float fStack_7c;
  undefined4 uStack_78;
  undefined4 uStack_74;
  float fStack_70;
  float fStack_6c;
  undefined1 auStack_60 [16];
  undefined1 auStack_50 [8];
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined1 auStack_40 [48];
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  iVar5 = (int)param_1;
  if ((long)((ulong)*(byte *)(iVar5 + 0x19) << 0x3c) < 0) {
    (**(code **)(*(int *)(iVar5 + 0x14) + 0xc))();
  }
  __ct__6MatrixFRC6Matrix(auStack_40,iGpffff8598 + 0x240);
  __ct__7FVectorFRC7FVector(auStack_50,&uStack_10);
  uStack_10 = 0;
  uStack_c = 0;
  uStack_8 = 0;
  uStack_4 = 0x3f800000;
  uStack_90 = 0;
  uStack_8c = 0;
  uStack_88 = 0x3f800000;
  uStack_84 = 0x3f800000;
  ApplyMatrix__6MatrixCFRC7FVector(auStack_60,auStack_40,&uStack_90);
  uVar2 = __ct__7FVectorFRC7FVector(auStack_a0,auStack_60);
  Get3DAngle__F7FVector(&fStack_70,uVar2);
  fStack_80 = -fStack_70;
  fStack_7c = -fStack_6c;
  uStack_78 = 0;
  uStack_74 = 0x3f800000;
  if ((long)((ulong)*(byte *)(iVar5 + 0x19) << 0x3e) < 0) {
    *(int *)(iVar5 + 0x30) = auStack_50._0_4_;
    *(int *)(iVar5 + 0x34) = auStack_50._4_4_;
    *(undefined4 *)(iVar5 + 0x38) = uStack_48;
    *(undefined4 *)(iVar5 + 0x3c) = uStack_44;
    *(float *)(iVar5 + 0x40) = fStack_80;
    *(float *)(iVar5 + 0x44) = fStack_7c;
    *(undefined4 *)(iVar5 + 0x48) = 0;
    *(undefined4 *)(iVar5 + 0x4c) = 0x3f800000;
    *(int *)(iVar5 + 0x50) = (int)*(undefined8 *)(iVar5 + 0x30);
    *(int *)(iVar5 + 0x54) = (int)((ulong)*(undefined8 *)(iVar5 + 0x30) >> 0x20);
    *(undefined4 *)(iVar5 + 0x58) = *(undefined4 *)(iVar5 + 0x38);
    *(undefined4 *)(iVar5 + 0x5c) = *(undefined4 *)(iVar5 + 0x3c);
    *(int *)(iVar5 + 0x60) = (int)*(undefined8 *)(iVar5 + 0x40);
    *(int *)(iVar5 + 100) = (int)((ulong)*(undefined8 *)(iVar5 + 0x40) >> 0x20);
    *(undefined4 *)(iVar5 + 0x68) = *(undefined4 *)(iVar5 + 0x48);
    *(undefined4 *)(iVar5 + 0x6c) = *(undefined4 *)(iVar5 + 0x4c);
    *(undefined4 *)(iVar5 + 0x140) = 0;
    for (lVar4 = 0; lVar4 < *(short *)(iGpffff86b4 + 0x3c30); lVar4 = (long)((int)lVar4 + 1)) {
      *(uint *)(iVar5 + 0x140) =
           *(uint *)(iVar5 + 0x140) |
           3 << ((*(uint *)(iGpffff86b4 + (int)lVar4 * 0x14 + 0x3c34) & 0xf) << 1);
    }
    for (lVar4 = 0; lVar4 < *(short *)(iGpffff86b4 + 0x3c32); lVar4 = (long)((int)lVar4 + 1)) {
      *(uint *)(iVar5 + 0x140) =
           *(uint *)(iVar5 + 0x140) |
           3 << ((*(uint *)(iGpffff86b4 + (int)lVar4 * 0x14 + 0x3d24) & 0xf) << 1);
    }
    while (*(float *)(iVar5 + 0x40) < -180.0) {
      *(float *)(iVar5 + 0x40) = *(float *)(iVar5 + 0x40) + 360.0;
    }
    while (180.0 <= *(float *)(iVar5 + 0x40)) {
      *(float *)(iVar5 + 0x40) = *(float *)(iVar5 + 0x40) - 360.0;
    }
    while (*(float *)(iVar5 + 0x44) < -180.0) {
      *(float *)(iVar5 + 0x44) = *(float *)(iVar5 + 0x44) + 360.0;
    }
    while (180.0 <= *(float *)(iVar5 + 0x44)) {
      *(float *)(iVar5 + 0x44) = *(float *)(iVar5 + 0x44) - 360.0;
    }
    while (*(float *)(iVar5 + 0x48) < -180.0) {
      *(float *)(iVar5 + 0x48) = *(float *)(iVar5 + 0x48) + 360.0;
    }
    while (180.0 <= *(float *)(iVar5 + 0x48)) {
      *(float *)(iVar5 + 0x48) = *(float *)(iVar5 + 0x48) - 360.0;
    }
    bVar1 = *(byte *)(iVar5 + 0x18);
    uVar2 = __ct__7FVectorFRC7FVector(auStack_f0,iVar5 + 0x30);
    uVar3 = __ct__7FVectorFRC7FVector(auStack_100,iVar5 + 0x40);
    BtlChrAlphaCtrl__9BtlCameraF7FVector7FVectorb
              (param_1,uVar2,uVar3,(long)((ulong)bVar1 << 0x38) < 0);
    bVar1 = *(byte *)(iVar5 + 0x18);
    uVar2 = __ct__7FVectorFRC7FVector(auStack_110,iVar5 + 0x30);
    uVar3 = __ct__7FVectorFRC7FVector(auStack_120,iVar5 + 0x40);
    BtlBGWallAlphaCtrl__9BtlCameraF7FVector7FVectorfb
              (*(undefined4 *)(iVar5 + 0x24),param_1,uVar2,uVar3,(long)((ulong)bVar1 << 0x38) < 0);
  }
  else {
    while (*(float *)(iVar5 + 0x40) < -180.0) {
      *(float *)(iVar5 + 0x40) = *(float *)(iVar5 + 0x40) + 360.0;
    }
    while (180.0 <= *(float *)(iVar5 + 0x40)) {
      *(float *)(iVar5 + 0x40) = *(float *)(iVar5 + 0x40) - 360.0;
    }
    while (*(float *)(iVar5 + 0x44) < -180.0) {
      *(float *)(iVar5 + 0x44) = *(float *)(iVar5 + 0x44) + 360.0;
    }
    while (180.0 <= *(float *)(iVar5 + 0x44)) {
      *(float *)(iVar5 + 0x44) = *(float *)(iVar5 + 0x44) - 360.0;
    }
    while (*(float *)(iVar5 + 0x48) < -180.0) {
      *(float *)(iVar5 + 0x48) = *(float *)(iVar5 + 0x48) + 360.0;
    }
    while (180.0 <= *(float *)(iVar5 + 0x48)) {
      *(float *)(iVar5 + 0x48) = *(float *)(iVar5 + 0x48) - 360.0;
    }
    bVar1 = *(byte *)(iVar5 + 0x18);
    uVar2 = __ct__7FVectorFRC7FVector(auStack_b0,auStack_50);
    uVar3 = __ct__7FVectorFRC7FVector(auStack_c0,iVar5 + 0x40);
    BtlChrAlphaCtrl__9BtlCameraF7FVector7FVectorb
              (param_1,uVar2,uVar3,(long)((ulong)bVar1 << 0x38) < 0);
    if (*(char *)(iGpffff86b4 + 0x3f0d) == '\x02') {
      bVar1 = *(byte *)(iVar5 + 0x18);
      uVar2 = __ct__7FVectorFRC7FVector(auStack_d0,auStack_50);
      uVar3 = __ct__7FVectorFRC7FVector(auStack_e0,iVar5 + 0x40);
      BtlBGWallAlphaCtrl__9BtlCameraF7FVector7FVectorfb
                (*(undefined4 *)(iVar5 + 0x24),param_1,uVar2,uVar3,(long)((ulong)bVar1 << 0x38) < 0)
      ;
    }
  }
  *(byte *)(iVar5 + 0x18) = *(byte *)(iVar5 + 0x18) & 0x7f;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00581ca0  BtlChrAlphaCtrl__9BtlCameraF7FVector7FVectorb
 * C++: BtlCamera::BtlChrAlphaCtrl(FVector, FVector, bool)
 * size: 0x15d0 bytes
 * --------------------------------------------------------------------------- */
void BtlChrAlphaCtrl__9BtlCameraF7FVector7FVectorb
               (int param_1,undefined1 (*param_2) [16],float *param_3,char param_4)

{
  float in_zero_lo;
  float in_zero_hi;
  float in_zero_udw;
  float in_register_0000000c;
  undefined8 uVar1;
  float *pfVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  undefined4 uVar7;
  float fVar8;
  float fVar9;
  undefined1 in_vf0 [16];
  undefined1 auVar10 [16];
  undefined1 auVar11 [16];
  undefined1 auVar12 [16];
  undefined1 auStack_ea0 [16];
  undefined1 auStack_e90 [16];
  undefined1 auStack_e80 [16];
  undefined1 auStack_e70 [64];
  undefined1 auStack_e30 [8];
  float fStack_e28;
  float fStack_e24;
  float fStack_e20;
  float fStack_e1c;
  float fStack_e18;
  undefined4 uStack_e14;
  float fStack_e10;
  float fStack_e0c;
  float fStack_e08;
  undefined4 uStack_e04;
  float fStack_e00;
  float fStack_dfc;
  float fStack_df8;
  undefined4 uStack_df4;
  float fStack_df0;
  float fStack_dec;
  float fStack_de8;
  undefined4 uStack_de4;
  float fStack_de0;
  float fStack_ddc;
  float fStack_dd8;
  undefined4 uStack_dd4;
  float fStack_dd0;
  float fStack_dcc;
  float fStack_dc8;
  undefined4 uStack_dc4;
  float fStack_dc0;
  float fStack_dbc;
  float fStack_db8;
  undefined4 uStack_db4;
  float fStack_db0;
  float fStack_dac;
  float fStack_da8;
  undefined4 uStack_da4;
  undefined1 auStack_da0 [8];
  float fStack_d98;
  float fStack_d94;
  undefined1 auStack_d90 [16];
  undefined1 auStack_d80 [8];
  float fStack_d78;
  float fStack_d74;
  undefined1 auStack_d70 [16];
  undefined1 auStack_d60 [8];
  undefined4 uStack_d58;
  undefined4 uStack_d54;
  int aiStack_d50 [384];
  undefined4 auStack_750 [16];
  float fStack_710;
  float fStack_70c;
  float fStack_708;
  float fStack_704;
  float fStack_700;
  float fStack_6fc;
  float fStack_6f8;
  float fStack_6f4;
  float fStack_6f0;
  float fStack_6ec;
  float fStack_6e8;
  float fStack_6e4;
  float fStack_6e0;
  float fStack_6dc;
  float fStack_6d8;
  float fStack_6d4;
  float fStack_6d0;
  float fStack_6cc;
  float fStack_6c8;
  float fStack_6c4;
  float fStack_6c0;
  float fStack_6bc;
  float fStack_6b8;
  float fStack_6b4;
  float fStack_6b0;
  float fStack_6ac;
  float fStack_6a8;
  float fStack_6a4;
  float fStack_6a0;
  float fStack_69c;
  float fStack_698;
  float fStack_694;
  float afStack_690 [396];
  undefined1 auStack_60 [4];
  float afStack_5c [3];
  undefined1 auStack_50 [16];
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [16];
  float fStack_20;
  float fStack_1c;
  float fStack_18;
  float fStack_14;
  float fStack_10;
  float fStack_c;
  float fStack_8;
  float fStack_4;
  
  fStack_20 = in_zero_lo;
  fStack_1c = in_zero_hi;
  fStack_18 = in_zero_udw;
  fStack_14 = in_register_0000000c;
  fStack_10 = in_zero_lo;
  fStack_c = in_zero_hi;
  fStack_8 = in_zero_udw;
  fStack_4 = in_register_0000000c;
  __ct__6MatrixFRC6Matrix(auStack_60,iGpffff8598 + 0x240);
  for (iVar3 = 0; iVar3 < 3; iVar3 = iVar3 + 1) {
    *(float *)(auStack_60 + iVar3 * 0x10) = *(float *)(auStack_60 + iVar3 * 0x10) * -1.0;
    *(float *)(auStack_60 + iVar3 * 0x10 + 4) = *(float *)(auStack_60 + iVar3 * 0x10 + 4) * -1.0;
    *(float *)(auStack_60 + iVar3 * 0x10 + 8) = *(float *)(auStack_60 + iVar3 * 0x10 + 8) * -1.0;
    *(float *)(auStack_60 + iVar3 * 0x10 + 0xc) = *(float *)(auStack_60 + iVar3 * 0x10 + 0xc) * -1.0
    ;
  }
  auStack_30._0_12_ = ZEXT812(0);
  auStack_30._12_4_ = 0x3f800000;
  for (uVar5 = 0; (int)uVar5 < 0xc; uVar5 = uVar5 + 1) {
    if (((((*(byte *)(iGpffff86b4 + uVar5 * 0x4f0 + 0xb0) & 1) != 0) &&
         ((long)((ulong)*(byte *)(iGpffff86b4 + uVar5 * 0x4f0 + 0xb0) << 0x3e) < 0)) &&
        (-1 < (long)((ulong)*(byte *)(iGpffff86b4 + uVar5 * 0x4f0 + 0xb2) << 0x3d))) &&
       ('\x02' < *(char *)(iGpffff86b4 + uVar5 * 0x4f0 + 0xb8))) {
      iVar3 = iGpffff86b4 + uVar5 * 0x4f0;
      *(byte *)(iVar3 + 0xb0) = *(byte *)(iVar3 + 0xb0) & 0xf7;
      auVar10 = _lqc2(*(undefined1 (*) [16])(iGpffff86b4 + uVar5 * 0x4f0 + 0x150));
      auVar11 = _lqc2(*(undefined1 (*) [16])(iGpffff86b4 + uVar5 * 0x4f0 + 0x350));
      auVar10 = _vadd(auVar10,auVar11);
      auStack_ea0 = _sqc2(auVar10);
      __ct__7FVectorFRC7FVector(auStack_d70,auStack_ea0);
      auVar10 = _lqc2(auStack_d70);
      auVar11 = _lqc2(*param_2);
      auVar10 = _vsub(auVar10,auVar11);
      auStack_e80 = _sqc2(auVar10);
      __ct__7FVectorFRC7FVector(auStack_d60,auStack_e80);
      fStack_10 = auStack_d60._0_4_;
      fStack_c = auStack_d60._4_4_;
      fStack_8 = (float)uStack_d58;
      fStack_4 = (float)uStack_d54;
      uVar1 = __ct__7FVectorFRC7FVector(auStack_d90,&fStack_10);
      Get3DAngle__F7FVector(auStack_d80,uVar1);
      fStack_20 = auStack_d80._0_4_;
      fStack_1c = auStack_d80._4_4_;
      fStack_18 = fStack_d78;
      fStack_14 = fStack_d74;
      ApplyMatrix__6MatrixCFRC7FVector(auStack_da0,auStack_60,&fStack_10);
      fStack_10 = auStack_da0._0_4_;
      fStack_c = auStack_da0._4_4_;
      fStack_8 = fStack_d98;
      fStack_4 = fStack_d94;
      fVar8 = (float)Length__7FVectorCFv(&fStack_10);
      fVar9 = (float)Length__7FVectorCFv(iGpffff86b4 + uVar5 * 0x4f0 + 0x360);
      if (fVar9 < *(float *)(iGpffff86b4 + uVar5 * 0x4f0 + 0x3b0)) {
        fVar9 = *(float *)(iGpffff86b4 + uVar5 * 0x4f0 + 0x3b0);
      }
      fVar9 = fVar9 * 1.5;
      if (fVar8 <= fVar9 + 10.0) {
        if ((*(uint *)(param_1 + 0x140) & 3 << ((uVar5 & 0xf) << 1)) == 3 << ((uVar5 & 0xf) << 1)) {
          fVar8 = 1.0;
        }
        else {
          fVar8 = (fVar8 - fVar9) / ((fVar9 + 10.0) - fVar9);
          if (fVar8 < 0.0) {
            fVar8 = 0.0;
          }
          if (1.0 <= fVar8) {
            fVar8 = 1.0;
          }
        }
      }
      else {
        for (fVar8 = -fStack_20 - *param_3; fVar8 < -180.0; fVar8 = fVar8 + 360.0) {
        }
        for (; 180.0 < fVar8; fVar8 = fVar8 - 360.0) {
        }
        for (fVar9 = -fStack_1c - param_3[1]; fVar9 < -180.0; fVar9 = fVar9 + 360.0) {
        }
        for (; 180.0 < fVar9; fVar9 = fVar9 - 360.0) {
        }
        if (((45.0 < fVar8) || (fVar8 < -45.0)) || ((45.0 < fVar9 || (fVar9 < -45.0)))) {
          iVar3 = iGpffff86b4 + uVar5 * 0x4f0;
          *(byte *)(iVar3 + 0xb0) = *(byte *)(iVar3 + 0xb0) & 0xf7 | 8;
        }
        fVar8 = 1.0;
      }
      if (param_4 == '\0') {
        SetCameraAlpha__8BtlModelFfb(fVar8,*(undefined4 *)(iGpffff86b4 + uVar5 * 0x4f0 + 0x144),0);
      }
      else {
        SetCameraAlpha__8BtlModelFfb(fVar8,*(undefined4 *)(iGpffff86b4 + uVar5 * 0x4f0 + 0x144),1);
      }
    }
  }
  iVar3 = 0;
  pfVar2 = afStack_690;
  do {
    *pfVar2 = in_zero_lo;
    pfVar2[1] = in_zero_hi;
    pfVar2[2] = in_zero_udw;
    pfVar2[3] = in_register_0000000c;
    pfVar2 = pfVar2 + 4;
  } while (pfVar2 != afStack_690 + 0x180);
  fStack_710 = in_zero_lo;
  fStack_70c = in_zero_hi;
  fStack_708 = in_zero_udw;
  fStack_704 = in_register_0000000c;
  fStack_700 = in_zero_lo;
  fStack_6fc = in_zero_hi;
  fStack_6f8 = in_zero_udw;
  fStack_6f4 = in_register_0000000c;
  fStack_6f0 = in_zero_lo;
  fStack_6ec = in_zero_hi;
  fStack_6e8 = in_zero_udw;
  fStack_6e4 = in_register_0000000c;
  fStack_6e0 = in_zero_lo;
  fStack_6dc = in_zero_hi;
  fStack_6d8 = in_zero_udw;
  fStack_6d4 = in_register_0000000c;
  fStack_6d0 = in_zero_lo;
  fStack_6cc = in_zero_hi;
  fStack_6c8 = in_zero_udw;
  fStack_6c4 = in_register_0000000c;
  fStack_6c0 = in_zero_lo;
  fStack_6bc = in_zero_hi;
  fStack_6b8 = in_zero_udw;
  fStack_6b4 = in_register_0000000c;
  fStack_6b0 = in_zero_lo;
  fStack_6ac = in_zero_hi;
  fStack_6a8 = in_zero_udw;
  fStack_6a4 = in_register_0000000c;
  fStack_6a0 = in_zero_lo;
  fStack_69c = in_zero_hi;
  fStack_698 = in_zero_udw;
  fStack_694 = in_register_0000000c;
  for (fVar8 = 0.0; (int)fVar8 < 0xc; fVar8 = (float)((int)fVar8 + 1)) {
    if (((((*(byte *)(iGpffff86b4 + (int)fVar8 * 0x4f0 + 0xb0) & 1) != 0) &&
         ((long)((ulong)*(byte *)(iGpffff86b4 + (int)fVar8 * 0x4f0 + 0xb0) << 0x3e) < 0)) &&
        (-1 < (long)((ulong)*(byte *)(iGpffff86b4 + (int)fVar8 * 0x4f0 + 0xb2) << 0x3d))) &&
       ('\x02' < *(char *)(iGpffff86b4 + (int)fVar8 * 0x4f0 + 0xb8))) {
      afStack_690[iVar3 + 0x180] = fVar8;
      auVar10 = _vmr32(in_vf0);
      auVar11 = _vmr32(auVar10);
      auVar12 = _vmr32(auVar11);
      auStack_30 = _sqc2(in_vf0);
      auStack_40 = _sqc2(auVar10);
      auStack_50 = _sqc2(auVar11);
      _auStack_60 = _sqc2(auVar12);
      uVar7 = GetRad(-*(float *)(iGpffff86b4 + (int)fVar8 * 0x4f0 + 0x174));
      sceVu0RotMatrixY(uVar7,auStack_60,auStack_60);
      fStack_da8 = -*(float *)(iGpffff86b4 + (int)fVar8 * 0x4f0 + 0x368);
      fStack_dac = -*(float *)(iGpffff86b4 + (int)fVar8 * 0x4f0 + 0x364);
      fStack_db0 = -*(float *)(iGpffff86b4 + (int)fVar8 * 0x4f0 + 0x360);
      uStack_da4 = 0x3f800000;
      fStack_704 = 1.0;
      fStack_db8 = -*(float *)(iGpffff86b4 + (int)fVar8 * 0x4f0 + 0x368);
      fStack_dbc = -*(float *)(iGpffff86b4 + (int)fVar8 * 0x4f0 + 0x364);
      fStack_dc0 = *(float *)(iGpffff86b4 + (int)fVar8 * 0x4f0 + 0x360);
      uStack_db4 = 0x3f800000;
      fStack_6f4 = 1.0;
      fStack_dc8 = *(float *)(iGpffff86b4 + (int)fVar8 * 0x4f0 + 0x368);
      fStack_dcc = -*(float *)(iGpffff86b4 + (int)fVar8 * 0x4f0 + 0x364);
      fStack_dd0 = -*(float *)(iGpffff86b4 + (int)fVar8 * 0x4f0 + 0x360);
      uStack_dc4 = 0x3f800000;
      fStack_6e4 = 1.0;
      fStack_dd8 = *(float *)(iGpffff86b4 + (int)fVar8 * 0x4f0 + 0x368);
      fStack_ddc = -*(float *)(iGpffff86b4 + (int)fVar8 * 0x4f0 + 0x364);
      fStack_de0 = *(float *)(iGpffff86b4 + (int)fVar8 * 0x4f0 + 0x360);
      uStack_dd4 = 0x3f800000;
      fStack_6d4 = 1.0;
      fStack_de8 = -*(float *)(iGpffff86b4 + (int)fVar8 * 0x4f0 + 0x368);
      fStack_dec = *(float *)(iGpffff86b4 + (int)fVar8 * 0x4f0 + 0x364);
      fStack_df0 = -*(float *)(iGpffff86b4 + (int)fVar8 * 0x4f0 + 0x360);
      uStack_de4 = 0x3f800000;
      fStack_6c4 = 1.0;
      fStack_df8 = -*(float *)(iGpffff86b4 + (int)fVar8 * 0x4f0 + 0x368);
      fStack_dfc = *(float *)(iGpffff86b4 + (int)fVar8 * 0x4f0 + 0x364);
      fStack_e00 = *(float *)(iGpffff86b4 + (int)fVar8 * 0x4f0 + 0x360);
      uStack_df4 = 0x3f800000;
      fStack_6b4 = 1.0;
      fStack_e08 = *(float *)(iGpffff86b4 + (int)fVar8 * 0x4f0 + 0x368);
      fStack_e0c = *(float *)(iGpffff86b4 + (int)fVar8 * 0x4f0 + 0x364);
      fStack_e10 = -*(float *)(iGpffff86b4 + (int)fVar8 * 0x4f0 + 0x360);
      uStack_e04 = 0x3f800000;
      fStack_6a4 = 1.0;
      fStack_e18 = *(float *)(iGpffff86b4 + (int)fVar8 * 0x4f0 + 0x368);
      fStack_e1c = *(float *)(iGpffff86b4 + (int)fVar8 * 0x4f0 + 0x364);
      fStack_e20 = *(float *)(iGpffff86b4 + (int)fVar8 * 0x4f0 + 0x360);
      uStack_e14 = 0x3f800000;
      fStack_694 = 1.0;
      fStack_710 = fStack_db0;
      fStack_70c = fStack_dac;
      fStack_708 = fStack_da8;
      fStack_700 = fStack_dc0;
      fStack_6fc = fStack_dbc;
      fStack_6f8 = fStack_db8;
      fStack_6f0 = fStack_dd0;
      fStack_6ec = fStack_dcc;
      fStack_6e8 = fStack_dc8;
      fStack_6e0 = fStack_de0;
      fStack_6dc = fStack_ddc;
      fStack_6d8 = fStack_dd8;
      fStack_6d0 = fStack_df0;
      fStack_6cc = fStack_dec;
      fStack_6c8 = fStack_de8;
      fStack_6c0 = fStack_e00;
      fStack_6bc = fStack_dfc;
      fStack_6b8 = fStack_df8;
      fStack_6b0 = fStack_e10;
      fStack_6ac = fStack_e0c;
      fStack_6a8 = fStack_e08;
      fStack_6a0 = fStack_e20;
      fStack_69c = fStack_e1c;
      fStack_698 = fStack_e18;
      RotTransVector(afStack_690 + iVar3 * 0x20,&fStack_710,auStack_60,8);
      auVar10 = _lqc2(*(undefined1 (*) [16])(iGpffff86b4 + (int)fVar8 * 0x4f0 + 0x150));
      auVar11 = _lqc2(*(undefined1 (*) [16])(iGpffff86b4 + (int)fVar8 * 0x4f0 + 0x350));
      auVar10 = _vadd(auVar10,auVar11);
      auStack_e90 = _sqc2(auVar10);
      __ct__7FVectorFRC7FVector(auStack_e30,auStack_e90);
      fStack_10 = auStack_e30._0_4_;
      fStack_c = auStack_e30._4_4_;
      fStack_8 = fStack_e28;
      fStack_4 = fStack_e24;
      for (iVar6 = 0; iVar6 < 8; iVar6 = iVar6 + 1) {
        auVar10._4_4_ = fStack_c;
        auVar10._0_4_ = fStack_10;
        auVar10._8_4_ = fStack_8;
        auVar10._12_4_ = fStack_4;
        auVar11 = _lqc2(auVar10);
        auVar10 = _lqc2(*(undefined1 (*) [16])(afStack_690 + (iVar6 + iVar3 * 8) * 4));
        auVar10 = _vadd(auVar10,auVar11);
        auVar10 = _sqc2(auVar10);
        *(undefined1 (*) [16])(afStack_690 + (iVar6 + iVar3 * 8) * 4) = auVar10;
      }
      iVar3 = iVar3 + 1;
    }
  }
  if (iVar3 != 0) {
    GetViewScreenMatrix__9GsxCameraFv(auStack_e70,iGpffff8598);
    for (iVar6 = 0; iVar6 < 4; iVar6 = iVar6 + 1) {
      auStack_750[iVar6 * 4] = *(undefined4 *)(auStack_60 + iVar6 * 0x10);
      auStack_750[iVar6 * 4 + 1] = *(undefined4 *)(auStack_60 + iVar6 * 0x10 + 4);
      auStack_750[iVar6 * 4 + 2] = *(undefined4 *)(auStack_60 + iVar6 * 0x10 + 8);
      auStack_750[iVar6 * 4 + 3] = *(undefined4 *)(auStack_60 + iVar6 * 0x10 + 0xc);
    }
    sceVu0RotTransPersN(aiStack_d50,auStack_750,afStack_690,iVar3 << 3,0);
    for (iVar6 = 0; iVar6 < iVar3; iVar6 = iVar6 + 1) {
      fVar8 = (float)aiStack_d50[iVar6 * 0x20] / 16.0 - 1792.0;
      afStack_690[(iVar6 * 2 + 1) * 4] = fVar8;
      afStack_690[iVar6 * 8] = fVar8;
      fVar8 = (float)aiStack_d50[iVar6 * 0x20 + 1] / 16.0 - 1824.0;
      afStack_690[(iVar6 * 2 + 1) * 4 + 1] = fVar8;
      afStack_690[iVar6 * 8 + 1] = fVar8;
      iVar4 = aiStack_d50[iVar6 * 0x20 + 2];
      afStack_690[(iVar6 * 2 + 1) * 4 + 2] = (float)iVar4 / 16.0;
      afStack_690[iVar6 * 8 + 2] = (float)iVar4 / 16.0;
      for (iVar4 = 1; iVar4 < 8; iVar4 = iVar4 + 1) {
        fVar8 = (float)aiStack_d50[(iVar4 + iVar6 * 8) * 4] / 16.0 - 1792.0;
        if (fVar8 < afStack_690[iVar6 * 8]) {
          afStack_690[iVar6 * 8] = fVar8;
        }
        if (afStack_690[(iVar6 * 2 + 1) * 4] < fVar8) {
          afStack_690[(iVar6 * 2 + 1) * 4] = fVar8;
        }
        fVar8 = (float)aiStack_d50[(iVar4 + iVar6 * 8) * 4 + 1] / 16.0 - 1824.0;
        if (fVar8 < afStack_690[iVar6 * 8 + 1]) {
          afStack_690[iVar6 * 8 + 1] = fVar8;
        }
        if (afStack_690[(iVar6 * 2 + 1) * 4 + 1] < fVar8) {
          afStack_690[(iVar6 * 2 + 1) * 4 + 1] = fVar8;
        }
        fVar8 = (float)aiStack_d50[(iVar4 + iVar6 * 8) * 4 + 2] / 16.0;
        if (fVar8 < afStack_690[iVar6 * 8 + 2]) {
          afStack_690[iVar6 * 8 + 2] = fVar8;
        }
        if (afStack_690[(iVar6 * 2 + 1) * 4 + 2] < fVar8) {
          afStack_690[(iVar6 * 2 + 1) * 4 + 2] = fVar8;
        }
      }
      fVar9 = afStack_690[(iVar6 * 2 + 1) * 4];
      fVar8 = afStack_690[iVar6 * 8];
      afStack_690[iVar6 * 8] = (afStack_690[iVar6 * 8] + afStack_690[(iVar6 * 2 + 1) * 4]) / 2.0;
      afStack_690[(iVar6 * 2 + 1) * 4] = (fVar9 - fVar8) / 2.0;
      fVar9 = afStack_690[(iVar6 * 2 + 1) * 4 + 1];
      fVar8 = afStack_690[iVar6 * 8 + 1];
      afStack_690[iVar6 * 8 + 1] =
           (afStack_690[iVar6 * 8 + 1] + afStack_690[(iVar6 * 2 + 1) * 4 + 1]) / 2.0;
      afStack_690[(iVar6 * 2 + 1) * 4 + 1] = (fVar9 - fVar8) / 2.0;
    }
    for (iVar6 = 0; iVar6 < iVar3; iVar6 = iVar6 + 1) {
      if (((uint)(2 << (((uint)afStack_690[iVar6 + 0x180] & 0xf) << 1)) <=
           (*(uint *)(param_1 + 0x140) & 3 << (((uint)afStack_690[iVar6 + 0x180] & 0xf) << 1))) &&
         (0.0 <= afStack_690[(iVar6 * 2 + 1) * 4 + 2])) {
        for (iVar4 = 0; iVar4 < iVar3; iVar4 = iVar4 + 1) {
          if ((((*(uint *)(param_1 + 0x140) & 3 << (((uint)afStack_690[iVar4 + 0x180] & 0xf) << 1))
                < (uint)(2 << (((uint)afStack_690[iVar4 + 0x180] & 0xf) << 1))) &&
              (0.0 <= afStack_690[(iVar4 * 2 + 1) * 4 + 2])) &&
             ((afStack_690[(iVar6 * 2 + 1) * 4 + 2] <= afStack_690[(iVar4 * 2 + 1) * 4 + 2] &&
              (iVar6 != iVar4)))) {
            fVar8 = afStack_690[iVar6 * 8] - afStack_690[iVar4 * 8];
            if (fVar8 < 0.0) {
              fVar8 = fVar8 * -1.0;
            }
            if (fVar8 <= (afStack_690[(iVar6 * 2 + 1) * 4] + afStack_690[(iVar4 * 2 + 1) * 4]) * 1.1
               ) {
              fVar8 = afStack_690[iVar6 * 8 + 1] - afStack_690[iVar4 * 8 + 1];
              if (fVar8 < 0.0) {
                fVar8 = fVar8 * -1.0;
              }
              if (fVar8 <= (afStack_690[(iVar6 * 2 + 1) * 4 + 1] +
                           afStack_690[(iVar4 * 2 + 1) * 4 + 1]) * 1.1) {
                if (param_4 == '\0') {
                  SetCameraAlpha__8BtlModelFfb
                            (0,*(undefined4 *)(iGpffff86b4 + iVar4 * 0x4f0 + 0x144),0);
                }
                else {
                  SetCameraAlpha__8BtlModelFfb
                            (0,*(undefined4 *)(iGpffff86b4 + iVar4 * 0x4f0 + 0x144),1);
                }
              }
            }
          }
        }
      }
    }
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00583270  BtlBGWallAlphaCtrl__9BtlCameraF7FVector7FVectorfb
 * C++: BtlCamera::BtlBGWallAlphaCtrl(FVector, FVector, float, bool)
 * size: 0x4110 bytes
 * --------------------------------------------------------------------------- */
void BtlBGWallAlphaCtrl__9BtlCameraF7FVector7FVectorfb
               (float param_1,int param_2,undefined1 (*param_3) [16],undefined8 param_4,char param_5
               )

{
  undefined1 auVar1 [16];
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
  undefined1 auVar65 [12];
  undefined1 auVar66 [12];
  undefined1 auVar67 [12];
  float fVar68;
  uint uVar69;
  undefined1 auVar70 [16];
  undefined1 auVar71 [16];
  undefined1 auStack_5c0 [16];
  undefined1 auStack_5b0 [16];
  undefined1 auStack_5a0 [16];
  undefined1 auStack_590 [16];
  undefined1 auStack_580 [16];
  undefined1 auStack_570 [16];
  undefined1 auStack_560 [16];
  undefined1 auStack_550 [16];
  undefined1 auStack_540 [16];
  undefined1 auStack_530 [16];
  undefined1 auStack_520 [16];
  undefined1 auStack_510 [16];
  undefined1 auStack_500 [16];
  undefined1 auStack_4f0 [16];
  undefined1 auStack_4e0 [16];
  undefined1 auStack_4d0 [16];
  undefined1 auStack_4c0 [16];
  undefined1 auStack_4b0 [16];
  undefined1 auStack_4a0 [16];
  undefined1 auStack_490 [16];
  undefined1 auStack_480 [16];
  undefined1 auStack_470 [16];
  undefined4 uStack_460;
  undefined4 uStack_45c;
  undefined4 uStack_458;
  undefined4 uStack_454;
  undefined4 uStack_450;
  undefined4 uStack_44c;
  undefined4 uStack_448;
  undefined4 uStack_444;
  undefined4 uStack_440;
  undefined4 uStack_43c;
  undefined4 uStack_438;
  undefined4 uStack_434;
  undefined4 uStack_430;
  undefined4 uStack_42c;
  undefined4 uStack_428;
  undefined4 uStack_424;
  undefined4 uStack_420;
  undefined4 uStack_41c;
  undefined4 uStack_418;
  undefined4 uStack_414;
  undefined4 uStack_410;
  float fStack_40c;
  undefined4 uStack_408;
  undefined4 uStack_404;
  undefined4 uStack_400;
  undefined4 uStack_3fc;
  undefined4 uStack_3f8;
  undefined4 uStack_3f4;
  undefined4 uStack_3f0;
  undefined4 uStack_3ec;
  undefined4 uStack_3e8;
  undefined4 uStack_3e4;
  float fStack_3e0;
  float fStack_3dc;
  undefined4 uStack_3d8;
  undefined4 uStack_3d4;
  undefined4 uStack_3d0;
  undefined4 uStack_3cc;
  undefined4 uStack_3c8;
  undefined4 uStack_3c4;
  undefined4 uStack_3c0;
  undefined4 uStack_3bc;
  undefined4 uStack_3b8;
  undefined4 uStack_3b4;
  float fStack_3b0;
  float fStack_3ac;
  float fStack_3a8;
  undefined4 uStack_3a4;
  undefined4 uStack_3a0;
  undefined4 uStack_39c;
  undefined4 uStack_398;
  undefined4 uStack_394;
  undefined4 uStack_390;
  undefined4 uStack_38c;
  undefined4 uStack_388;
  undefined4 uStack_384;
  float fStack_380;
  float fStack_37c;
  undefined4 uStack_378;
  undefined4 uStack_374;
  undefined4 uStack_370;
  undefined4 uStack_36c;
  undefined4 uStack_368;
  undefined4 uStack_364;
  undefined4 uStack_360;
  undefined4 uStack_35c;
  undefined4 uStack_358;
  undefined4 uStack_354;
  float fStack_350;
  float fStack_34c;
  float fStack_348;
  undefined4 uStack_344;
  undefined4 uStack_340;
  undefined4 uStack_33c;
  undefined4 uStack_338;
  undefined4 uStack_334;
  undefined4 uStack_330;
  undefined4 uStack_32c;
  undefined4 uStack_328;
  undefined4 uStack_324;
  float fStack_320;
  float fStack_31c;
  undefined4 uStack_318;
  undefined4 uStack_314;
  undefined4 uStack_310;
  undefined4 uStack_30c;
  undefined4 uStack_308;
  undefined4 uStack_304;
  undefined4 uStack_300;
  undefined4 uStack_2fc;
  undefined4 uStack_2f8;
  undefined4 uStack_2f4;
  float fStack_2f0;
  float fStack_2ec;
  float fStack_2e8;
  undefined4 uStack_2e4;
  undefined4 uStack_2e0;
  undefined4 uStack_2dc;
  undefined4 uStack_2d8;
  undefined4 uStack_2d4;
  undefined4 uStack_2d0;
  undefined4 uStack_2cc;
  undefined4 uStack_2c8;
  undefined4 uStack_2c4;
  float fStack_2c0;
  float fStack_2bc;
  undefined4 uStack_2b8;
  undefined4 uStack_2b4;
  undefined4 uStack_2b0;
  undefined4 uStack_2ac;
  undefined4 uStack_2a8;
  undefined4 uStack_2a4;
  undefined4 uStack_2a0;
  undefined4 uStack_29c;
  undefined4 uStack_298;
  undefined4 uStack_294;
  float fStack_290;
  float fStack_28c;
  float fStack_288;
  undefined4 uStack_284;
  undefined4 uStack_280;
  undefined4 uStack_27c;
  undefined4 uStack_278;
  undefined4 uStack_274;
  undefined4 uStack_270;
  undefined4 uStack_26c;
  undefined4 uStack_268;
  undefined4 uStack_264;
  undefined4 uStack_260;
  float fStack_25c;
  float fStack_258;
  undefined4 uStack_254;
  undefined4 uStack_250;
  undefined4 uStack_24c;
  undefined4 uStack_248;
  undefined4 uStack_244;
  undefined4 uStack_240;
  undefined4 uStack_23c;
  undefined4 uStack_238;
  undefined4 uStack_234;
  float fStack_230;
  float fStack_22c;
  float fStack_228;
  undefined4 uStack_224;
  undefined4 uStack_220;
  undefined4 uStack_21c;
  undefined4 uStack_218;
  undefined4 uStack_214;
  undefined4 uStack_210;
  undefined4 uStack_20c;
  undefined4 uStack_208;
  undefined4 uStack_204;
  undefined4 uStack_200;
  float fStack_1fc;
  float fStack_1f8;
  undefined4 uStack_1f4;
  undefined4 uStack_1f0;
  undefined4 uStack_1ec;
  undefined4 uStack_1e8;
  undefined4 uStack_1e4;
  undefined4 uStack_1e0;
  undefined4 uStack_1dc;
  undefined4 uStack_1d8;
  undefined4 uStack_1d4;
  float fStack_1d0;
  float fStack_1cc;
  float fStack_1c8;
  undefined4 uStack_1c4;
  undefined4 uStack_1c0;
  undefined4 uStack_1bc;
  undefined4 uStack_1b8;
  undefined4 uStack_1b4;
  undefined4 uStack_1b0;
  undefined4 uStack_1ac;
  undefined4 uStack_1a8;
  undefined4 uStack_1a4;
  undefined4 uStack_1a0;
  float fStack_19c;
  float fStack_198;
  undefined4 uStack_194;
  undefined4 uStack_190;
  undefined4 uStack_18c;
  undefined4 uStack_188;
  undefined4 uStack_184;
  undefined4 uStack_180;
  undefined4 uStack_17c;
  undefined4 uStack_178;
  undefined4 uStack_174;
  float fStack_170;
  float fStack_16c;
  float fStack_168;
  undefined4 uStack_164;
  undefined4 uStack_160;
  undefined4 uStack_15c;
  undefined4 uStack_158;
  undefined4 uStack_154;
  undefined4 uStack_150;
  undefined4 uStack_14c;
  undefined4 uStack_148;
  undefined4 uStack_144;
  undefined4 uStack_140;
  float fStack_13c;
  float fStack_138;
  undefined4 uStack_134;
  undefined4 uStack_130;
  undefined4 uStack_12c;
  undefined4 uStack_128;
  undefined4 uStack_124;
  undefined4 uStack_120;
  undefined4 uStack_11c;
  undefined4 uStack_118;
  undefined4 uStack_114;
  float fStack_110;
  float fStack_10c;
  float fStack_108;
  undefined4 uStack_104;
  undefined4 uStack_100;
  undefined4 uStack_fc;
  undefined4 uStack_f8;
  undefined4 uStack_f4;
  undefined4 uStack_f0;
  undefined4 uStack_ec;
  undefined4 uStack_e8;
  undefined4 uStack_e4;
  float fStack_e0;
  float fStack_dc;
  undefined4 uStack_d8;
  undefined4 uStack_d4;
  undefined4 uStack_d0;
  undefined4 uStack_cc;
  undefined4 uStack_c8;
  undefined4 uStack_c4;
  undefined4 uStack_c0;
  undefined4 uStack_bc;
  undefined4 uStack_b8;
  undefined4 uStack_b4;
  float fStack_b0;
  float fStack_ac;
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
  float fStack_7c;
  float fStack_78;
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
  float fStack_4c;
  float fStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  float fStack_20;
  float fStack_1c;
  float fStack_18;
  undefined4 uStack_14;
  float fStack_10;
  float fStack_c;
  float fStack_8;
  
  if (*(short *)(*(int *)(iGpffff86b4 + 0x3f20) + 0x4b6) == 0) {
    fStack_48 = (*(float *)(iGpffff86b4 + 0x3f1c) + 10.0) / 2.0;
    fStack_4c = -*(float *)(iGpffff86b4 + 0x3f18) / 2.0;
    uStack_50 = 0;
    uStack_44 = 0x3f800000;
    fStack_20 = 0.0;
    uStack_14 = 0x3f800000;
    uStack_60 = 0;
    uStack_5c = 0;
    uStack_58 = 0xbf800000;
    uStack_54 = 0x3f800000;
    uStack_30 = 0;
    uStack_2c = 0;
    uStack_28 = 0xbf800000;
    uStack_24 = 0x3f800000;
    auVar70 = _lqc2(*param_3);
    auVar66._4_4_ = fStack_48;
    auVar66._0_4_ = fStack_4c;
    auVar66._8_4_ = 0;
    auVar43._12_4_ = 0x3f800000;
    auVar43._0_12_ = auVar66 << 0x20;
    auVar71 = _lqc2(auVar43);
    auVar70 = _vsub(auVar70,auVar71);
    auStack_470 = _sqc2(auVar70);
    fStack_1c = fStack_4c;
    fStack_18 = fStack_48;
    __ct__7FVectorFRC7FVector(&uStack_70,auStack_470);
    uStack_40 = uStack_70;
    uStack_3c = uStack_6c;
    uStack_38 = uStack_68;
    uStack_34 = uStack_64;
    auVar1._4_4_ = uStack_6c;
    auVar1._0_4_ = uStack_70;
    auVar1._8_4_ = uStack_68;
    auVar1._12_4_ = uStack_64;
    auVar70 = _lqc2(auVar1);
    auVar21._4_4_ = uStack_2c;
    auVar21._0_4_ = uStack_30;
    auVar21._8_4_ = uStack_28;
    auVar21._12_4_ = uStack_24;
    auVar71 = _lqc2(auVar21);
    auVar70 = _vmul(auVar70,auVar71);
    auVar70 = _vaddbc(auVar70,auVar70);
    auVar70 = _vaddbc(auVar70,auVar70);
    auVar70 = _qmfc2(auVar70._0_4_);
    fStack_10 = auVar70._0_4_;
    if ((fStack_10 <= 0.0) || ((*(byte *)(param_2 + 0x214) & 1) == 0)) {
      *(undefined4 *)(param_2 + 0x174) = 0;
      if ((*(float *)(param_2 + 0x144) != 0.0) || (param_5 == '\x01')) {
        *(undefined4 *)(param_2 + 0x144) = 0;
        fVar68 = *(float *)(param_2 + 0x144);
        if (fVar68 < 2.1474836e+09) {
          uVar69 = (uint)fVar68;
        }
        else {
          uVar69 = (int)(fVar68 - 2.1474836e+09) | 0x80000000;
        }
        (**(code **)(*(int *)(*(int *)(iGpffff86b4 + 0x3f20) + 0x10) + 0x54))
                  (*(int *)(iGpffff86b4 + 0x3f20),0,uVar69,0);
      }
    }
    else if (param_5 == '\x01') {
      *(undefined4 *)(param_2 + 0x144) = 0x43000000;
      *(undefined4 *)(param_2 + 0x174) = 0x3f000000;
      fVar68 = *(float *)(param_2 + 0x144);
      if (fVar68 < 2.1474836e+09) {
        uVar69 = (uint)fVar68;
      }
      else {
        uVar69 = (int)(fVar68 - 2.1474836e+09) | 0x80000000;
      }
      (**(code **)(*(int *)(*(int *)(iGpffff86b4 + 0x3f20) + 0x10) + 0x54))
                (*(int *)(iGpffff86b4 + 0x3f20),0,uVar69,0);
    }
    else {
      *(float *)(param_2 + 0x174) = *(float *)(param_2 + 0x174) + param_1;
      if ((0.5 <= *(float *)(param_2 + 0x174)) &&
         (*(undefined4 *)(param_2 + 0x174) = 0x3f000000, *(float *)(param_2 + 0x144) < 128.0)) {
        *(float *)(param_2 + 0x144) = *(float *)(param_2 + 0x144) + param_1 * 256.0;
        if (128.0 < *(float *)(param_2 + 0x144)) {
          *(undefined4 *)(param_2 + 0x144) = 0x43000000;
        }
        fVar68 = *(float *)(param_2 + 0x144);
        if (fVar68 < 2.1474836e+09) {
          uVar69 = (uint)fVar68;
        }
        else {
          uVar69 = (int)(fVar68 - 2.1474836e+09) | 0x80000000;
        }
        (**(code **)(*(int *)(*(int *)(iGpffff86b4 + 0x3f20) + 0x10) + 0x54))
                  (*(int *)(iGpffff86b4 + 0x3f20),0,uVar69,0);
      }
    }
    fStack_78 = (-*(float *)(iGpffff86b4 + 0x3f1c) - 10.0) / 2.0;
    fStack_7c = -*(float *)(iGpffff86b4 + 0x3f18) / 2.0;
    uStack_80 = 0;
    uStack_74 = 0x3f800000;
    fStack_20 = 0.0;
    uStack_14 = 0x3f800000;
    uStack_90 = 0;
    uStack_8c = 0;
    uStack_88 = 0x3f800000;
    uStack_84 = 0x3f800000;
    uStack_30 = 0;
    uStack_2c = 0;
    uStack_28 = 0x3f800000;
    uStack_24 = 0x3f800000;
    auVar70 = _lqc2(*param_3);
    auVar67._4_4_ = fStack_78;
    auVar67._0_4_ = fStack_7c;
    auVar67._8_4_ = 0;
    auVar44._12_4_ = 0x3f800000;
    auVar44._0_12_ = auVar67 << 0x20;
    auVar71 = _lqc2(auVar44);
    auVar70 = _vsub(auVar70,auVar71);
    auStack_480 = _sqc2(auVar70);
    fStack_1c = fStack_7c;
    fStack_18 = fStack_78;
    __ct__7FVectorFRC7FVector(&uStack_a0,auStack_480);
    uStack_40 = uStack_a0;
    uStack_3c = uStack_9c;
    uStack_38 = uStack_98;
    uStack_34 = uStack_94;
    auVar2._4_4_ = uStack_9c;
    auVar2._0_4_ = uStack_a0;
    auVar2._8_4_ = uStack_98;
    auVar2._12_4_ = uStack_94;
    auVar70 = _lqc2(auVar2);
    auVar22._4_4_ = uStack_2c;
    auVar22._0_4_ = uStack_30;
    auVar22._8_4_ = uStack_28;
    auVar22._12_4_ = uStack_24;
    auVar71 = _lqc2(auVar22);
    auVar70 = _vmul(auVar70,auVar71);
    auVar70 = _vaddbc(auVar70,auVar70);
    auVar70 = _vaddbc(auVar70,auVar70);
    auVar70 = _qmfc2(auVar70._0_4_);
    fStack_10 = auVar70._0_4_;
    if ((fStack_10 <= 0.0) || (-1 < (long)((ulong)*(byte *)(param_2 + 0x214) << 0x3d))) {
      *(undefined4 *)(param_2 + 0x17c) = 0;
      if ((*(float *)(param_2 + 0x14c) != 0.0) || (param_5 == '\x01')) {
        *(undefined4 *)(param_2 + 0x14c) = 0;
        fVar68 = *(float *)(param_2 + 0x14c);
        if (fVar68 < 2.1474836e+09) {
          uVar69 = (uint)fVar68;
        }
        else {
          uVar69 = (int)(fVar68 - 2.1474836e+09) | 0x80000000;
        }
        (**(code **)(*(int *)(*(int *)(iGpffff86b4 + 0x3f20) + 0x10) + 0x54))
                  (*(int *)(iGpffff86b4 + 0x3f20),2,uVar69,0);
      }
    }
    else if (param_5 == '\x01') {
      *(undefined4 *)(param_2 + 0x14c) = 0x43000000;
      *(undefined4 *)(param_2 + 0x17c) = 0x3f000000;
      fVar68 = *(float *)(param_2 + 0x14c);
      if (fVar68 < 2.1474836e+09) {
        uVar69 = (uint)fVar68;
      }
      else {
        uVar69 = (int)(fVar68 - 2.1474836e+09) | 0x80000000;
      }
      (**(code **)(*(int *)(*(int *)(iGpffff86b4 + 0x3f20) + 0x10) + 0x54))
                (*(int *)(iGpffff86b4 + 0x3f20),2,uVar69,0);
    }
    else {
      *(float *)(param_2 + 0x17c) = *(float *)(param_2 + 0x17c) + param_1;
      if ((0.5 <= *(float *)(param_2 + 0x17c)) &&
         (*(undefined4 *)(param_2 + 0x17c) = 0x3f000000, *(float *)(param_2 + 0x14c) < 128.0)) {
        *(float *)(param_2 + 0x14c) = *(float *)(param_2 + 0x14c) + param_1 * 256.0;
        if (128.0 < *(float *)(param_2 + 0x14c)) {
          *(undefined4 *)(param_2 + 0x14c) = 0x43000000;
        }
        fVar68 = *(float *)(param_2 + 0x14c);
        if (fVar68 < 2.1474836e+09) {
          uVar69 = (uint)fVar68;
        }
        else {
          uVar69 = (int)(fVar68 - 2.1474836e+09) | 0x80000000;
        }
        (**(code **)(*(int *)(*(int *)(iGpffff86b4 + 0x3f20) + 0x10) + 0x54))
                  (*(int *)(iGpffff86b4 + 0x3f20),2,uVar69,0);
      }
    }
    fStack_ac = -*(float *)(iGpffff86b4 + 0x3f18) / 2.0;
    fStack_b0 = (-*(float *)(iGpffff86b4 + 0x3f14) - 10.0) / 2.0;
    uStack_a8 = 0;
    uStack_a4 = 0x3f800000;
    fStack_18 = 0.0;
    uStack_14 = 0x3f800000;
    uStack_c0 = 0x3f800000;
    uStack_bc = 0;
    uStack_b8 = 0;
    uStack_b4 = 0x3f800000;
    uStack_30 = 0x3f800000;
    uStack_2c = 0;
    uStack_28 = 0;
    uStack_24 = 0x3f800000;
    auVar70 = _lqc2(*param_3);
    auVar45._4_4_ = fStack_ac;
    auVar45._0_4_ = fStack_b0;
    auVar45._8_4_ = 0;
    auVar45._12_4_ = 0x3f800000;
    auVar71 = _lqc2(auVar45);
    auVar70 = _vsub(auVar70,auVar71);
    auStack_490 = _sqc2(auVar70);
    fStack_20 = fStack_b0;
    fStack_1c = fStack_ac;
    __ct__7FVectorFRC7FVector(&uStack_d0,auStack_490);
    uStack_40 = uStack_d0;
    uStack_3c = uStack_cc;
    uStack_38 = uStack_c8;
    uStack_34 = uStack_c4;
    auVar3._4_4_ = uStack_cc;
    auVar3._0_4_ = uStack_d0;
    auVar3._8_4_ = uStack_c8;
    auVar3._12_4_ = uStack_c4;
    auVar70 = _lqc2(auVar3);
    auVar23._4_4_ = uStack_2c;
    auVar23._0_4_ = uStack_30;
    auVar23._8_4_ = uStack_28;
    auVar23._12_4_ = uStack_24;
    auVar71 = _lqc2(auVar23);
    auVar70 = _vmul(auVar70,auVar71);
    auVar70 = _vaddbc(auVar70,auVar70);
    auVar70 = _vaddbc(auVar70,auVar70);
    auVar70 = _qmfc2(auVar70._0_4_);
    fStack_10 = auVar70._0_4_;
    if ((fStack_10 <= 0.0) || (-1 < (long)((ulong)*(byte *)(param_2 + 0x214) << 0x3b))) {
      *(undefined4 *)(param_2 + 0x184) = 0;
      if ((*(float *)(param_2 + 0x154) != 0.0) || (param_5 == '\x01')) {
        *(undefined4 *)(param_2 + 0x154) = 0;
        fVar68 = *(float *)(param_2 + 0x154);
        if (fVar68 < 2.1474836e+09) {
          uVar69 = (uint)fVar68;
        }
        else {
          uVar69 = (int)(fVar68 - 2.1474836e+09) | 0x80000000;
        }
        (**(code **)(*(int *)(*(int *)(iGpffff86b4 + 0x3f20) + 0x10) + 0x54))
                  (*(int *)(iGpffff86b4 + 0x3f20),4,uVar69,0);
      }
    }
    else if (param_5 == '\x01') {
      *(undefined4 *)(param_2 + 0x154) = 0x43000000;
      *(undefined4 *)(param_2 + 0x184) = 0x3f000000;
      fVar68 = *(float *)(param_2 + 0x154);
      if (fVar68 < 2.1474836e+09) {
        uVar69 = (uint)fVar68;
      }
      else {
        uVar69 = (int)(fVar68 - 2.1474836e+09) | 0x80000000;
      }
      (**(code **)(*(int *)(*(int *)(iGpffff86b4 + 0x3f20) + 0x10) + 0x54))
                (*(int *)(iGpffff86b4 + 0x3f20),4,uVar69,0);
    }
    else {
      *(float *)(param_2 + 0x184) = *(float *)(param_2 + 0x184) + param_1;
      if ((0.5 <= *(float *)(param_2 + 0x184)) &&
         (*(undefined4 *)(param_2 + 0x184) = 0x3f000000, *(float *)(param_2 + 0x154) < 128.0)) {
        *(float *)(param_2 + 0x154) = *(float *)(param_2 + 0x154) + param_1 * 256.0;
        if (128.0 < *(float *)(param_2 + 0x154)) {
          *(undefined4 *)(param_2 + 0x154) = 0x43000000;
        }
        fVar68 = *(float *)(param_2 + 0x154);
        if (fVar68 < 2.1474836e+09) {
          uVar69 = (uint)fVar68;
        }
        else {
          uVar69 = (int)(fVar68 - 2.1474836e+09) | 0x80000000;
        }
        (**(code **)(*(int *)(*(int *)(iGpffff86b4 + 0x3f20) + 0x10) + 0x54))
                  (*(int *)(iGpffff86b4 + 0x3f20),4,uVar69,0);
      }
    }
    fStack_dc = -*(float *)(iGpffff86b4 + 0x3f18) / 2.0;
    fStack_e0 = (*(float *)(iGpffff86b4 + 0x3f14) + 10.0) / 2.0;
    uStack_d8 = 0;
    uStack_d4 = 0x3f800000;
    fStack_18 = 0.0;
    uStack_14 = 0x3f800000;
    uStack_f0 = 0xbf800000;
    uStack_ec = 0;
    uStack_e8 = 0;
    uStack_e4 = 0x3f800000;
    uStack_30 = 0xbf800000;
    uStack_2c = 0;
    uStack_28 = 0;
    uStack_24 = 0x3f800000;
    auVar70 = _lqc2(*param_3);
    auVar46._4_4_ = fStack_dc;
    auVar46._0_4_ = fStack_e0;
    auVar46._8_4_ = 0;
    auVar46._12_4_ = 0x3f800000;
    auVar71 = _lqc2(auVar46);
    auVar70 = _vsub(auVar70,auVar71);
    auStack_4a0 = _sqc2(auVar70);
    fStack_20 = fStack_e0;
    fStack_1c = fStack_dc;
    __ct__7FVectorFRC7FVector(&uStack_100,auStack_4a0);
    uStack_40 = uStack_100;
    uStack_3c = uStack_fc;
    uStack_38 = uStack_f8;
    uStack_34 = uStack_f4;
    auVar4._4_4_ = uStack_fc;
    auVar4._0_4_ = uStack_100;
    auVar4._8_4_ = uStack_f8;
    auVar4._12_4_ = uStack_f4;
    auVar70 = _lqc2(auVar4);
    auVar24._4_4_ = uStack_2c;
    auVar24._0_4_ = uStack_30;
    auVar24._8_4_ = uStack_28;
    auVar24._12_4_ = uStack_24;
    auVar71 = _lqc2(auVar24);
    auVar70 = _vmul(auVar70,auVar71);
    auVar70 = _vaddbc(auVar70,auVar70);
    auVar70 = _vaddbc(auVar70,auVar70);
    auVar70 = _qmfc2(auVar70._0_4_);
    fStack_10 = auVar70._0_4_;
    if ((fStack_10 <= 0.0) || (-1 < (long)((ulong)*(byte *)(param_2 + 0x214) << 0x39))) {
      *(undefined4 *)(param_2 + 0x18c) = 0;
      if ((*(float *)(param_2 + 0x15c) != 0.0) || (param_5 == '\x01')) {
        *(undefined4 *)(param_2 + 0x15c) = 0;
        fVar68 = *(float *)(param_2 + 0x15c);
        if (fVar68 < 2.1474836e+09) {
          uVar69 = (uint)fVar68;
        }
        else {
          uVar69 = (int)(fVar68 - 2.1474836e+09) | 0x80000000;
        }
        (**(code **)(*(int *)(*(int *)(iGpffff86b4 + 0x3f20) + 0x10) + 0x54))
                  (*(int *)(iGpffff86b4 + 0x3f20),6,uVar69,0);
      }
    }
    else if (param_5 == '\x01') {
      *(undefined4 *)(param_2 + 0x15c) = 0x43000000;
      *(undefined4 *)(param_2 + 0x18c) = 0x3f000000;
      fVar68 = *(float *)(param_2 + 0x15c);
      if (fVar68 < 2.1474836e+09) {
        uVar69 = (uint)fVar68;
      }
      else {
        uVar69 = (int)(fVar68 - 2.1474836e+09) | 0x80000000;
      }
      (**(code **)(*(int *)(*(int *)(iGpffff86b4 + 0x3f20) + 0x10) + 0x54))
                (*(int *)(iGpffff86b4 + 0x3f20),6,uVar69,0);
    }
    else {
      *(float *)(param_2 + 0x18c) = *(float *)(param_2 + 0x18c) + param_1;
      if ((0.5 <= *(float *)(param_2 + 0x18c)) &&
         (*(undefined4 *)(param_2 + 0x18c) = 0x3f000000, *(float *)(param_2 + 0x15c) < 128.0)) {
        *(float *)(param_2 + 0x15c) = *(float *)(param_2 + 0x15c) + param_1 * 256.0;
        if (128.0 < *(float *)(param_2 + 0x15c)) {
          *(undefined4 *)(param_2 + 0x15c) = 0x43000000;
        }
        fVar68 = *(float *)(param_2 + 0x15c);
        if (fVar68 < 2.1474836e+09) {
          uVar69 = (uint)fVar68;
        }
        else {
          uVar69 = (int)(fVar68 - 2.1474836e+09) | 0x80000000;
        }
        (**(code **)(*(int *)(*(int *)(iGpffff86b4 + 0x3f20) + 0x10) + 0x54))
                  (*(int *)(iGpffff86b4 + 0x3f20),6,uVar69,0);
      }
    }
  }
  else {
    fStack_108 = (*(float *)(iGpffff86b4 + 0x3f1c) + 10.0) / 2.0;
    fStack_10c = -*(float *)(iGpffff86b4 + 0x3f18) / 2.0;
    fStack_110 = (-*(float *)(iGpffff86b4 + 0x3f14) - 10.0) / 4.0;
    uStack_104 = 0x3f800000;
    uStack_14 = 0x3f800000;
    uStack_120 = 0;
    uStack_11c = 0;
    uStack_118 = 0xbf800000;
    uStack_114 = 0x3f800000;
    uStack_30 = 0;
    uStack_2c = 0;
    uStack_28 = 0xbf800000;
    uStack_24 = 0x3f800000;
    auVar70 = _lqc2(*param_3);
    auVar47._4_4_ = fStack_10c;
    auVar47._0_4_ = fStack_110;
    auVar47._8_4_ = fStack_108;
    auVar47._12_4_ = 0x3f800000;
    auVar71 = _lqc2(auVar47);
    auVar70 = _vsub(auVar70,auVar71);
    auStack_4b0 = _sqc2(auVar70);
    fStack_20 = fStack_110;
    fStack_1c = fStack_10c;
    fStack_18 = fStack_108;
    __ct__7FVectorFRC7FVector(&uStack_130,auStack_4b0);
    uStack_40 = uStack_130;
    uStack_3c = uStack_12c;
    uStack_38 = uStack_128;
    uStack_34 = uStack_124;
    auVar70._4_4_ = uStack_12c;
    auVar70._0_4_ = uStack_130;
    auVar70._8_4_ = uStack_128;
    auVar70._12_4_ = uStack_124;
    auVar70 = _lqc2(auVar70);
    auVar25._4_4_ = uStack_2c;
    auVar25._0_4_ = uStack_30;
    auVar25._8_4_ = uStack_28;
    auVar25._12_4_ = uStack_24;
    auVar71 = _lqc2(auVar25);
    auVar70 = _vmul(auVar70,auVar71);
    auVar70 = _vaddbc(auVar70,auVar70);
    auVar70 = _vaddbc(auVar70,auVar70);
    auVar70 = _qmfc2(auVar70._0_4_);
    fStack_10 = auVar70._0_4_;
    fStack_138 = (*(float *)(iGpffff86b4 + 0x3f1c) + 10.0) / 2.0 + 10.0;
    fStack_13c = -*(float *)(iGpffff86b4 + 0x3f18) / 2.0;
    uStack_140 = 0x41200000;
    uStack_134 = 0x3f800000;
    fStack_20 = 10.0;
    uStack_14 = 0x3f800000;
    uStack_150 = 0x3f800000;
    uStack_14c = 0;
    uStack_148 = 0xbf800000;
    uStack_144 = 0x3f800000;
    uStack_30 = 0x3f800000;
    uStack_2c = 0;
    uStack_28 = 0xbf800000;
    uStack_24 = 0x3f800000;
    auVar70 = _lqc2(*param_3);
    auVar48._4_4_ = fStack_13c;
    auVar48._0_4_ = 0x41200000;
    auVar48._8_4_ = fStack_138;
    auVar48._12_4_ = 0x3f800000;
    auVar71 = _lqc2(auVar48);
    auVar70 = _vsub(auVar70,auVar71);
    auStack_4c0 = _sqc2(auVar70);
    fStack_1c = fStack_13c;
    fStack_18 = fStack_138;
    __ct__7FVectorFRC7FVector(&uStack_160,auStack_4c0);
    uStack_40 = uStack_160;
    uStack_3c = uStack_15c;
    uStack_38 = uStack_158;
    uStack_34 = uStack_154;
    auVar71._4_4_ = uStack_15c;
    auVar71._0_4_ = uStack_160;
    auVar71._8_4_ = uStack_158;
    auVar71._12_4_ = uStack_154;
    auVar70 = _lqc2(auVar71);
    auVar26._4_4_ = uStack_2c;
    auVar26._0_4_ = uStack_30;
    auVar26._8_4_ = uStack_28;
    auVar26._12_4_ = uStack_24;
    auVar71 = _lqc2(auVar26);
    auVar70 = _vmul(auVar70,auVar71);
    auVar70 = _vaddbc(auVar70,auVar70);
    auVar70 = _vaddbc(auVar70,auVar70);
    auVar70 = _qmfc2(auVar70._0_4_);
    fStack_8 = auVar70._0_4_;
    if (((fStack_10 <= 0.0) && (fStack_8 <= 0.0)) || ((*(byte *)(param_2 + 0x214) & 1) == 0)) {
      *(undefined4 *)(param_2 + 0x174) = 0;
      if ((*(float *)(param_2 + 0x144) != 0.0) || (param_5 == '\x01')) {
        *(undefined4 *)(param_2 + 0x144) = 0;
        fVar68 = *(float *)(param_2 + 0x144);
        if (fVar68 < 2.1474836e+09) {
          uVar69 = (uint)fVar68;
        }
        else {
          uVar69 = (int)(fVar68 - 2.1474836e+09) | 0x80000000;
        }
        (**(code **)(*(int *)(*(int *)(iGpffff86b4 + 0x3f20) + 0x10) + 0x54))
                  (*(int *)(iGpffff86b4 + 0x3f20),0,uVar69,0);
      }
    }
    else if (param_5 == '\x01') {
      *(undefined4 *)(param_2 + 0x144) = 0x43000000;
      *(undefined4 *)(param_2 + 0x174) = 0x3f000000;
      fVar68 = *(float *)(param_2 + 0x144);
      if (fVar68 < 2.1474836e+09) {
        uVar69 = (uint)fVar68;
      }
      else {
        uVar69 = (int)(fVar68 - 2.1474836e+09) | 0x80000000;
      }
      (**(code **)(*(int *)(*(int *)(iGpffff86b4 + 0x3f20) + 0x10) + 0x54))
                (*(int *)(iGpffff86b4 + 0x3f20),0,uVar69,0);
    }
    else {
      *(float *)(param_2 + 0x174) = *(float *)(param_2 + 0x174) + param_1;
      if ((0.5 <= *(float *)(param_2 + 0x174)) &&
         (*(undefined4 *)(param_2 + 0x174) = 0x3f000000, *(float *)(param_2 + 0x144) < 128.0)) {
        *(float *)(param_2 + 0x144) = *(float *)(param_2 + 0x144) + param_1 * 256.0;
        if (128.0 < *(float *)(param_2 + 0x144)) {
          *(undefined4 *)(param_2 + 0x144) = 0x43000000;
        }
        fVar68 = *(float *)(param_2 + 0x144);
        if (fVar68 < 2.1474836e+09) {
          uVar69 = (uint)fVar68;
        }
        else {
          uVar69 = (int)(fVar68 - 2.1474836e+09) | 0x80000000;
        }
        (**(code **)(*(int *)(*(int *)(iGpffff86b4 + 0x3f20) + 0x10) + 0x54))
                  (*(int *)(iGpffff86b4 + 0x3f20),0,uVar69,0);
      }
    }
    fStack_168 = (*(float *)(iGpffff86b4 + 0x3f1c) + 10.0) / 2.0;
    fStack_16c = -*(float *)(iGpffff86b4 + 0x3f18) / 2.0;
    fStack_170 = (*(float *)(iGpffff86b4 + 0x3f14) + 10.0) / 4.0;
    uStack_164 = 0x3f800000;
    uStack_14 = 0x3f800000;
    uStack_180 = 0;
    uStack_17c = 0;
    uStack_178 = 0xbf800000;
    uStack_174 = 0x3f800000;
    uStack_30 = 0;
    uStack_2c = 0;
    uStack_28 = 0xbf800000;
    uStack_24 = 0x3f800000;
    auVar70 = _lqc2(*param_3);
    auVar49._4_4_ = fStack_16c;
    auVar49._0_4_ = fStack_170;
    auVar49._8_4_ = fStack_168;
    auVar49._12_4_ = 0x3f800000;
    auVar71 = _lqc2(auVar49);
    auVar70 = _vsub(auVar70,auVar71);
    auStack_4d0 = _sqc2(auVar70);
    fStack_20 = fStack_170;
    fStack_1c = fStack_16c;
    fStack_18 = fStack_168;
    __ct__7FVectorFRC7FVector(&uStack_190,auStack_4d0);
    uStack_40 = uStack_190;
    uStack_3c = uStack_18c;
    uStack_38 = uStack_188;
    uStack_34 = uStack_184;
    auVar5._4_4_ = uStack_18c;
    auVar5._0_4_ = uStack_190;
    auVar5._8_4_ = uStack_188;
    auVar5._12_4_ = uStack_184;
    auVar70 = _lqc2(auVar5);
    auVar27._4_4_ = uStack_2c;
    auVar27._0_4_ = uStack_30;
    auVar27._8_4_ = uStack_28;
    auVar27._12_4_ = uStack_24;
    auVar71 = _lqc2(auVar27);
    auVar70 = _vmul(auVar70,auVar71);
    auVar70 = _vaddbc(auVar70,auVar70);
    auVar70 = _vaddbc(auVar70,auVar70);
    auVar70 = _qmfc2(auVar70._0_4_);
    fStack_10 = auVar70._0_4_;
    fStack_198 = (*(float *)(iGpffff86b4 + 0x3f1c) + 10.0) / 2.0 + 10.0;
    fStack_19c = -*(float *)(iGpffff86b4 + 0x3f18) / 2.0;
    uStack_1a0 = 0xc1200000;
    uStack_194 = 0x3f800000;
    fStack_20 = -10.0;
    uStack_14 = 0x3f800000;
    uStack_1b0 = 0xbf800000;
    uStack_1ac = 0;
    uStack_1a8 = 0xbf800000;
    uStack_1a4 = 0x3f800000;
    uStack_30 = 0xbf800000;
    uStack_2c = 0;
    uStack_28 = 0xbf800000;
    uStack_24 = 0x3f800000;
    auVar70 = _lqc2(*param_3);
    auVar50._4_4_ = fStack_19c;
    auVar50._0_4_ = 0xc1200000;
    auVar50._8_4_ = fStack_198;
    auVar50._12_4_ = 0x3f800000;
    auVar71 = _lqc2(auVar50);
    auVar70 = _vsub(auVar70,auVar71);
    auStack_4e0 = _sqc2(auVar70);
    fStack_1c = fStack_19c;
    fStack_18 = fStack_198;
    __ct__7FVectorFRC7FVector(&uStack_1c0,auStack_4e0);
    uStack_40 = uStack_1c0;
    uStack_3c = uStack_1bc;
    uStack_38 = uStack_1b8;
    uStack_34 = uStack_1b4;
    auVar6._4_4_ = uStack_1bc;
    auVar6._0_4_ = uStack_1c0;
    auVar6._8_4_ = uStack_1b8;
    auVar6._12_4_ = uStack_1b4;
    auVar70 = _lqc2(auVar6);
    auVar28._4_4_ = uStack_2c;
    auVar28._0_4_ = uStack_30;
    auVar28._8_4_ = uStack_28;
    auVar28._12_4_ = uStack_24;
    auVar71 = _lqc2(auVar28);
    auVar70 = _vmul(auVar70,auVar71);
    auVar70 = _vaddbc(auVar70,auVar70);
    auVar70 = _vaddbc(auVar70,auVar70);
    auVar70 = _qmfc2(auVar70._0_4_);
    fStack_c = auVar70._0_4_;
    if (((fStack_10 <= 0.0) && (fStack_c <= 0.0)) ||
       (-1 < (long)((ulong)*(byte *)(param_2 + 0x214) << 0x3e))) {
      *(undefined4 *)(param_2 + 0x178) = 0;
      if ((*(float *)(param_2 + 0x148) != 0.0) || (param_5 == '\x01')) {
        *(undefined4 *)(param_2 + 0x148) = 0;
        fVar68 = *(float *)(param_2 + 0x148);
        if (fVar68 < 2.1474836e+09) {
          uVar69 = (uint)fVar68;
        }
        else {
          uVar69 = (int)(fVar68 - 2.1474836e+09) | 0x80000000;
        }
        (**(code **)(*(int *)(*(int *)(iGpffff86b4 + 0x3f20) + 0x10) + 0x54))
                  (*(int *)(iGpffff86b4 + 0x3f20),1,uVar69,0);
      }
    }
    else if (param_5 == '\x01') {
      *(undefined4 *)(param_2 + 0x148) = 0x43000000;
      *(undefined4 *)(param_2 + 0x178) = 0x3f000000;
      fVar68 = *(float *)(param_2 + 0x148);
      if (fVar68 < 2.1474836e+09) {
        uVar69 = (uint)fVar68;
      }
      else {
        uVar69 = (int)(fVar68 - 2.1474836e+09) | 0x80000000;
      }
      (**(code **)(*(int *)(*(int *)(iGpffff86b4 + 0x3f20) + 0x10) + 0x54))
                (*(int *)(iGpffff86b4 + 0x3f20),1,uVar69,0);
    }
    else {
      *(float *)(param_2 + 0x178) = *(float *)(param_2 + 0x178) + param_1;
      if ((0.5 <= *(float *)(param_2 + 0x178)) &&
         (*(undefined4 *)(param_2 + 0x178) = 0x3f000000, *(float *)(param_2 + 0x148) < 128.0)) {
        *(float *)(param_2 + 0x148) = *(float *)(param_2 + 0x148) + param_1 * 256.0;
        if (128.0 < *(float *)(param_2 + 0x148)) {
          *(undefined4 *)(param_2 + 0x148) = 0x43000000;
        }
        fVar68 = *(float *)(param_2 + 0x148);
        if (fVar68 < 2.1474836e+09) {
          uVar69 = (uint)fVar68;
        }
        else {
          uVar69 = (int)(fVar68 - 2.1474836e+09) | 0x80000000;
        }
        (**(code **)(*(int *)(*(int *)(iGpffff86b4 + 0x3f20) + 0x10) + 0x54))
                  (*(int *)(iGpffff86b4 + 0x3f20),1,uVar69,0);
      }
    }
    fStack_1c8 = (-*(float *)(iGpffff86b4 + 0x3f1c) - 10.0) / 2.0;
    fStack_1cc = -*(float *)(iGpffff86b4 + 0x3f18) / 2.0;
    fStack_1d0 = (-*(float *)(iGpffff86b4 + 0x3f14) - 10.0) / 4.0;
    uStack_1c4 = 0x3f800000;
    uStack_14 = 0x3f800000;
    uStack_1e0 = 0;
    uStack_1dc = 0;
    uStack_1d8 = 0x3f800000;
    uStack_1d4 = 0x3f800000;
    uStack_30 = 0;
    uStack_2c = 0;
    uStack_28 = 0x3f800000;
    uStack_24 = 0x3f800000;
    auVar70 = _lqc2(*param_3);
    auVar51._4_4_ = fStack_1cc;
    auVar51._0_4_ = fStack_1d0;
    auVar51._8_4_ = fStack_1c8;
    auVar51._12_4_ = 0x3f800000;
    auVar71 = _lqc2(auVar51);
    auVar70 = _vsub(auVar70,auVar71);
    auStack_4f0 = _sqc2(auVar70);
    fStack_20 = fStack_1d0;
    fStack_1c = fStack_1cc;
    fStack_18 = fStack_1c8;
    __ct__7FVectorFRC7FVector(&uStack_1f0,auStack_4f0);
    uStack_40 = uStack_1f0;
    uStack_3c = uStack_1ec;
    uStack_38 = uStack_1e8;
    uStack_34 = uStack_1e4;
    auVar7._4_4_ = uStack_1ec;
    auVar7._0_4_ = uStack_1f0;
    auVar7._8_4_ = uStack_1e8;
    auVar7._12_4_ = uStack_1e4;
    auVar70 = _lqc2(auVar7);
    auVar29._4_4_ = uStack_2c;
    auVar29._0_4_ = uStack_30;
    auVar29._8_4_ = uStack_28;
    auVar29._12_4_ = uStack_24;
    auVar71 = _lqc2(auVar29);
    auVar70 = _vmul(auVar70,auVar71);
    auVar70 = _vaddbc(auVar70,auVar70);
    auVar70 = _vaddbc(auVar70,auVar70);
    auVar70 = _qmfc2(auVar70._0_4_);
    fStack_10 = auVar70._0_4_;
    fStack_1f8 = (-*(float *)(iGpffff86b4 + 0x3f1c) - 10.0) / 2.0 - 10.0;
    fStack_1fc = -*(float *)(iGpffff86b4 + 0x3f18) / 2.0;
    uStack_200 = 0x41200000;
    uStack_1f4 = 0x3f800000;
    fStack_20 = 10.0;
    uStack_14 = 0x3f800000;
    uStack_210 = 0x3f800000;
    uStack_20c = 0;
    uStack_208 = 0x3f800000;
    uStack_204 = 0x3f800000;
    uStack_30 = 0x3f800000;
    uStack_2c = 0;
    uStack_28 = 0x3f800000;
    uStack_24 = 0x3f800000;
    auVar70 = _lqc2(*param_3);
    auVar52._4_4_ = fStack_1fc;
    auVar52._0_4_ = 0x41200000;
    auVar52._8_4_ = fStack_1f8;
    auVar52._12_4_ = 0x3f800000;
    auVar71 = _lqc2(auVar52);
    auVar70 = _vsub(auVar70,auVar71);
    auStack_500 = _sqc2(auVar70);
    fStack_1c = fStack_1fc;
    fStack_18 = fStack_1f8;
    __ct__7FVectorFRC7FVector(&uStack_220,auStack_500);
    uStack_40 = uStack_220;
    uStack_3c = uStack_21c;
    uStack_38 = uStack_218;
    uStack_34 = uStack_214;
    auVar8._4_4_ = uStack_21c;
    auVar8._0_4_ = uStack_220;
    auVar8._8_4_ = uStack_218;
    auVar8._12_4_ = uStack_214;
    auVar70 = _lqc2(auVar8);
    auVar30._4_4_ = uStack_2c;
    auVar30._0_4_ = uStack_30;
    auVar30._8_4_ = uStack_28;
    auVar30._12_4_ = uStack_24;
    auVar71 = _lqc2(auVar30);
    auVar70 = _vmul(auVar70,auVar71);
    auVar70 = _vaddbc(auVar70,auVar70);
    auVar70 = _vaddbc(auVar70,auVar70);
    auVar70 = _qmfc2(auVar70._0_4_);
    fStack_8 = auVar70._0_4_;
    if (((fStack_10 <= 0.0) && (fStack_8 <= 0.0)) ||
       (-1 < (long)((ulong)*(byte *)(param_2 + 0x214) << 0x3d))) {
      *(undefined4 *)(param_2 + 0x17c) = 0;
      if ((*(float *)(param_2 + 0x14c) != 0.0) || (param_5 == '\x01')) {
        *(undefined4 *)(param_2 + 0x14c) = 0;
        fVar68 = *(float *)(param_2 + 0x14c);
        if (fVar68 < 2.1474836e+09) {
          uVar69 = (uint)fVar68;
        }
        else {
          uVar69 = (int)(fVar68 - 2.1474836e+09) | 0x80000000;
        }
        (**(code **)(*(int *)(*(int *)(iGpffff86b4 + 0x3f20) + 0x10) + 0x54))
                  (*(int *)(iGpffff86b4 + 0x3f20),2,uVar69,0);
      }
    }
    else if (param_5 == '\x01') {
      *(undefined4 *)(param_2 + 0x14c) = 0x43000000;
      *(undefined4 *)(param_2 + 0x17c) = 0x3f000000;
      fVar68 = *(float *)(param_2 + 0x14c);
      if (fVar68 < 2.1474836e+09) {
        uVar69 = (uint)fVar68;
      }
      else {
        uVar69 = (int)(fVar68 - 2.1474836e+09) | 0x80000000;
      }
      (**(code **)(*(int *)(*(int *)(iGpffff86b4 + 0x3f20) + 0x10) + 0x54))
                (*(int *)(iGpffff86b4 + 0x3f20),2,uVar69,0);
    }
    else {
      *(float *)(param_2 + 0x17c) = *(float *)(param_2 + 0x17c) + param_1;
      if ((0.5 <= *(float *)(param_2 + 0x17c)) &&
         (*(undefined4 *)(param_2 + 0x17c) = 0x3f000000, *(float *)(param_2 + 0x14c) < 128.0)) {
        *(float *)(param_2 + 0x14c) = *(float *)(param_2 + 0x14c) + param_1 * 256.0;
        if (128.0 < *(float *)(param_2 + 0x14c)) {
          *(undefined4 *)(param_2 + 0x14c) = 0x43000000;
        }
        fVar68 = *(float *)(param_2 + 0x14c);
        if (fVar68 < 2.1474836e+09) {
          uVar69 = (uint)fVar68;
        }
        else {
          uVar69 = (int)(fVar68 - 2.1474836e+09) | 0x80000000;
        }
        (**(code **)(*(int *)(*(int *)(iGpffff86b4 + 0x3f20) + 0x10) + 0x54))
                  (*(int *)(iGpffff86b4 + 0x3f20),2,uVar69,0);
      }
    }
    fStack_228 = (-*(float *)(iGpffff86b4 + 0x3f1c) - 10.0) / 2.0;
    fStack_22c = -*(float *)(iGpffff86b4 + 0x3f18) / 2.0;
    fStack_230 = (*(float *)(iGpffff86b4 + 0x3f14) + 10.0) / 4.0;
    uStack_224 = 0x3f800000;
    uStack_14 = 0x3f800000;
    uStack_240 = 0;
    uStack_23c = 0;
    uStack_238 = 0x3f800000;
    uStack_234 = 0x3f800000;
    uStack_30 = 0;
    uStack_2c = 0;
    uStack_28 = 0x3f800000;
    uStack_24 = 0x3f800000;
    auVar70 = _lqc2(*param_3);
    auVar53._4_4_ = fStack_22c;
    auVar53._0_4_ = fStack_230;
    auVar53._8_4_ = fStack_228;
    auVar53._12_4_ = 0x3f800000;
    auVar71 = _lqc2(auVar53);
    auVar70 = _vsub(auVar70,auVar71);
    auStack_510 = _sqc2(auVar70);
    fStack_20 = fStack_230;
    fStack_1c = fStack_22c;
    fStack_18 = fStack_228;
    __ct__7FVectorFRC7FVector(&uStack_250,auStack_510);
    uStack_40 = uStack_250;
    uStack_3c = uStack_24c;
    uStack_38 = uStack_248;
    uStack_34 = uStack_244;
    auVar9._4_4_ = uStack_24c;
    auVar9._0_4_ = uStack_250;
    auVar9._8_4_ = uStack_248;
    auVar9._12_4_ = uStack_244;
    auVar70 = _lqc2(auVar9);
    auVar31._4_4_ = uStack_2c;
    auVar31._0_4_ = uStack_30;
    auVar31._8_4_ = uStack_28;
    auVar31._12_4_ = uStack_24;
    auVar71 = _lqc2(auVar31);
    auVar70 = _vmul(auVar70,auVar71);
    auVar70 = _vaddbc(auVar70,auVar70);
    auVar70 = _vaddbc(auVar70,auVar70);
    auVar70 = _qmfc2(auVar70._0_4_);
    fStack_10 = auVar70._0_4_;
    fStack_258 = (-*(float *)(iGpffff86b4 + 0x3f1c) - 10.0) / 2.0 - 10.0;
    fStack_25c = -*(float *)(iGpffff86b4 + 0x3f18) / 2.0;
    uStack_260 = 0xc1200000;
    uStack_254 = 0x3f800000;
    fStack_20 = -10.0;
    uStack_14 = 0x3f800000;
    uStack_270 = 0xbf800000;
    uStack_26c = 0;
    uStack_268 = 0x3f800000;
    uStack_264 = 0x3f800000;
    uStack_30 = 0xbf800000;
    uStack_2c = 0;
    uStack_28 = 0x3f800000;
    uStack_24 = 0x3f800000;
    auVar70 = _lqc2(*param_3);
    auVar54._4_4_ = fStack_25c;
    auVar54._0_4_ = 0xc1200000;
    auVar54._8_4_ = fStack_258;
    auVar54._12_4_ = 0x3f800000;
    auVar71 = _lqc2(auVar54);
    auVar70 = _vsub(auVar70,auVar71);
    auStack_520 = _sqc2(auVar70);
    fStack_1c = fStack_25c;
    fStack_18 = fStack_258;
    __ct__7FVectorFRC7FVector(&uStack_280,auStack_520);
    uStack_40 = uStack_280;
    uStack_3c = uStack_27c;
    uStack_38 = uStack_278;
    uStack_34 = uStack_274;
    auVar10._4_4_ = uStack_27c;
    auVar10._0_4_ = uStack_280;
    auVar10._8_4_ = uStack_278;
    auVar10._12_4_ = uStack_274;
    auVar70 = _lqc2(auVar10);
    auVar32._4_4_ = uStack_2c;
    auVar32._0_4_ = uStack_30;
    auVar32._8_4_ = uStack_28;
    auVar32._12_4_ = uStack_24;
    auVar71 = _lqc2(auVar32);
    auVar70 = _vmul(auVar70,auVar71);
    auVar70 = _vaddbc(auVar70,auVar70);
    auVar70 = _vaddbc(auVar70,auVar70);
    auVar70 = _qmfc2(auVar70._0_4_);
    fStack_c = auVar70._0_4_;
    if (((fStack_10 <= 0.0) && (fStack_c <= 0.0)) ||
       (-1 < (long)((ulong)*(byte *)(param_2 + 0x214) << 0x3c))) {
      *(undefined4 *)(param_2 + 0x180) = 0;
      if ((*(float *)(param_2 + 0x150) != 0.0) || (param_5 == '\x01')) {
        *(undefined4 *)(param_2 + 0x150) = 0;
        fVar68 = *(float *)(param_2 + 0x150);
        if (fVar68 < 2.1474836e+09) {
          uVar69 = (uint)fVar68;
        }
        else {
          uVar69 = (int)(fVar68 - 2.1474836e+09) | 0x80000000;
        }
        (**(code **)(*(int *)(*(int *)(iGpffff86b4 + 0x3f20) + 0x10) + 0x54))
                  (*(int *)(iGpffff86b4 + 0x3f20),3,uVar69,0);
      }
    }
    else if (param_5 == '\x01') {
      *(undefined4 *)(param_2 + 0x150) = 0x43000000;
      *(undefined4 *)(param_2 + 0x180) = 0x3f000000;
      fVar68 = *(float *)(param_2 + 0x150);
      if (fVar68 < 2.1474836e+09) {
        uVar69 = (uint)fVar68;
      }
      else {
        uVar69 = (int)(fVar68 - 2.1474836e+09) | 0x80000000;
      }
      (**(code **)(*(int *)(*(int *)(iGpffff86b4 + 0x3f20) + 0x10) + 0x54))
                (*(int *)(iGpffff86b4 + 0x3f20),3,uVar69,0);
    }
    else {
      *(float *)(param_2 + 0x180) = *(float *)(param_2 + 0x180) + param_1;
      if ((0.5 <= *(float *)(param_2 + 0x180)) &&
         (*(undefined4 *)(param_2 + 0x180) = 0x3f000000, *(float *)(param_2 + 0x150) < 128.0)) {
        *(float *)(param_2 + 0x150) = *(float *)(param_2 + 0x150) + param_1 * 256.0;
        if (128.0 < *(float *)(param_2 + 0x150)) {
          *(undefined4 *)(param_2 + 0x150) = 0x43000000;
        }
        fVar68 = *(float *)(param_2 + 0x150);
        if (fVar68 < 2.1474836e+09) {
          uVar69 = (uint)fVar68;
        }
        else {
          uVar69 = (int)(fVar68 - 2.1474836e+09) | 0x80000000;
        }
        (**(code **)(*(int *)(*(int *)(iGpffff86b4 + 0x3f20) + 0x10) + 0x54))
                  (*(int *)(iGpffff86b4 + 0x3f20),3,uVar69,0);
      }
    }
    fStack_288 = (*(float *)(iGpffff86b4 + 0x3f1c) + 10.0) / 4.0;
    fStack_28c = -*(float *)(iGpffff86b4 + 0x3f18) / 2.0;
    fStack_290 = (-*(float *)(iGpffff86b4 + 0x3f14) - 10.0) / 2.0;
    uStack_284 = 0x3f800000;
    uStack_14 = 0x3f800000;
    uStack_2a0 = 0x3f800000;
    uStack_29c = 0;
    uStack_298 = 0;
    uStack_294 = 0x3f800000;
    uStack_30 = 0x3f800000;
    uStack_2c = 0;
    uStack_28 = 0;
    uStack_24 = 0x3f800000;
    auVar70 = _lqc2(*param_3);
    auVar55._4_4_ = fStack_28c;
    auVar55._0_4_ = fStack_290;
    auVar55._8_4_ = fStack_288;
    auVar55._12_4_ = 0x3f800000;
    auVar71 = _lqc2(auVar55);
    auVar70 = _vsub(auVar70,auVar71);
    auStack_530 = _sqc2(auVar70);
    fStack_20 = fStack_290;
    fStack_1c = fStack_28c;
    fStack_18 = fStack_288;
    __ct__7FVectorFRC7FVector(&uStack_2b0,auStack_530);
    uStack_40 = uStack_2b0;
    uStack_3c = uStack_2ac;
    uStack_38 = uStack_2a8;
    uStack_34 = uStack_2a4;
    auVar11._4_4_ = uStack_2ac;
    auVar11._0_4_ = uStack_2b0;
    auVar11._8_4_ = uStack_2a8;
    auVar11._12_4_ = uStack_2a4;
    auVar70 = _lqc2(auVar11);
    auVar33._4_4_ = uStack_2c;
    auVar33._0_4_ = uStack_30;
    auVar33._8_4_ = uStack_28;
    auVar33._12_4_ = uStack_24;
    auVar71 = _lqc2(auVar33);
    auVar70 = _vmul(auVar70,auVar71);
    auVar70 = _vaddbc(auVar70,auVar70);
    auVar70 = _vaddbc(auVar70,auVar70);
    auVar70 = _qmfc2(auVar70._0_4_);
    fStack_10 = auVar70._0_4_;
    fStack_2bc = -*(float *)(iGpffff86b4 + 0x3f18) / 2.0;
    fStack_2c0 = (-*(float *)(iGpffff86b4 + 0x3f14) - 10.0) / 2.0 - 10.0;
    uStack_2b8 = 0xc1200000;
    uStack_2b4 = 0x3f800000;
    fStack_18 = -10.0;
    uStack_14 = 0x3f800000;
    uStack_2d0 = 0x3f800000;
    uStack_2cc = 0;
    uStack_2c8 = 0xbf800000;
    uStack_2c4 = 0x3f800000;
    uStack_30 = 0x3f800000;
    uStack_2c = 0;
    uStack_28 = 0xbf800000;
    uStack_24 = 0x3f800000;
    auVar70 = _lqc2(*param_3);
    auVar56._4_4_ = fStack_2bc;
    auVar56._0_4_ = fStack_2c0;
    auVar56._8_4_ = 0xc1200000;
    auVar56._12_4_ = 0x3f800000;
    auVar71 = _lqc2(auVar56);
    auVar70 = _vsub(auVar70,auVar71);
    auStack_540 = _sqc2(auVar70);
    fStack_20 = fStack_2c0;
    fStack_1c = fStack_2bc;
    __ct__7FVectorFRC7FVector(&uStack_2e0,auStack_540);
    uStack_40 = uStack_2e0;
    uStack_3c = uStack_2dc;
    uStack_38 = uStack_2d8;
    uStack_34 = uStack_2d4;
    auVar12._4_4_ = uStack_2dc;
    auVar12._0_4_ = uStack_2e0;
    auVar12._8_4_ = uStack_2d8;
    auVar12._12_4_ = uStack_2d4;
    auVar70 = _lqc2(auVar12);
    auVar34._4_4_ = uStack_2c;
    auVar34._0_4_ = uStack_30;
    auVar34._8_4_ = uStack_28;
    auVar34._12_4_ = uStack_24;
    auVar71 = _lqc2(auVar34);
    auVar70 = _vmul(auVar70,auVar71);
    auVar70 = _vaddbc(auVar70,auVar70);
    auVar70 = _vaddbc(auVar70,auVar70);
    auVar70 = _qmfc2(auVar70._0_4_);
    fStack_8 = auVar70._0_4_;
    if (((fStack_10 <= 0.0) && (fStack_8 <= 0.0)) ||
       (-1 < (long)((ulong)*(byte *)(param_2 + 0x214) << 0x3b))) {
      *(undefined4 *)(param_2 + 0x184) = 0;
      if ((*(float *)(param_2 + 0x154) != 0.0) || (param_5 == '\x01')) {
        *(undefined4 *)(param_2 + 0x154) = 0;
        fVar68 = *(float *)(param_2 + 0x154);
        if (fVar68 < 2.1474836e+09) {
          uVar69 = (uint)fVar68;
        }
        else {
          uVar69 = (int)(fVar68 - 2.1474836e+09) | 0x80000000;
        }
        (**(code **)(*(int *)(*(int *)(iGpffff86b4 + 0x3f20) + 0x10) + 0x54))
                  (*(int *)(iGpffff86b4 + 0x3f20),4,uVar69,0);
      }
    }
    else if (param_5 == '\x01') {
      *(undefined4 *)(param_2 + 0x154) = 0x43000000;
      *(undefined4 *)(param_2 + 0x184) = 0x3f000000;
      fVar68 = *(float *)(param_2 + 0x154);
      if (fVar68 < 2.1474836e+09) {
        uVar69 = (uint)fVar68;
      }
      else {
        uVar69 = (int)(fVar68 - 2.1474836e+09) | 0x80000000;
      }
      (**(code **)(*(int *)(*(int *)(iGpffff86b4 + 0x3f20) + 0x10) + 0x54))
                (*(int *)(iGpffff86b4 + 0x3f20),4,uVar69,0);
    }
    else {
      *(float *)(param_2 + 0x184) = *(float *)(param_2 + 0x184) + param_1;
      if ((0.5 <= *(float *)(param_2 + 0x184)) &&
         (*(undefined4 *)(param_2 + 0x184) = 0x3f000000, *(float *)(param_2 + 0x154) < 128.0)) {
        *(float *)(param_2 + 0x154) = *(float *)(param_2 + 0x154) + param_1 * 256.0;
        if (128.0 < *(float *)(param_2 + 0x154)) {
          *(undefined4 *)(param_2 + 0x154) = 0x43000000;
        }
        fVar68 = *(float *)(param_2 + 0x154);
        if (fVar68 < 2.1474836e+09) {
          uVar69 = (uint)fVar68;
        }
        else {
          uVar69 = (int)(fVar68 - 2.1474836e+09) | 0x80000000;
        }
        (**(code **)(*(int *)(*(int *)(iGpffff86b4 + 0x3f20) + 0x10) + 0x54))
                  (*(int *)(iGpffff86b4 + 0x3f20),4,uVar69,0);
      }
    }
    fStack_2e8 = (-*(float *)(iGpffff86b4 + 0x3f1c) - 10.0) / 4.0;
    fStack_2ec = -*(float *)(iGpffff86b4 + 0x3f18) / 2.0;
    fStack_2f0 = (-*(float *)(iGpffff86b4 + 0x3f14) - 10.0) / 2.0;
    uStack_2e4 = 0x3f800000;
    uStack_14 = 0x3f800000;
    uStack_300 = 0x3f800000;
    uStack_2fc = 0;
    uStack_2f8 = 0;
    uStack_2f4 = 0x3f800000;
    uStack_30 = 0x3f800000;
    uStack_2c = 0;
    uStack_28 = 0;
    uStack_24 = 0x3f800000;
    auVar70 = _lqc2(*param_3);
    auVar57._4_4_ = fStack_2ec;
    auVar57._0_4_ = fStack_2f0;
    auVar57._8_4_ = fStack_2e8;
    auVar57._12_4_ = 0x3f800000;
    auVar71 = _lqc2(auVar57);
    auVar70 = _vsub(auVar70,auVar71);
    auStack_550 = _sqc2(auVar70);
    fStack_20 = fStack_2f0;
    fStack_1c = fStack_2ec;
    fStack_18 = fStack_2e8;
    __ct__7FVectorFRC7FVector(&uStack_310,auStack_550);
    uStack_40 = uStack_310;
    uStack_3c = uStack_30c;
    uStack_38 = uStack_308;
    uStack_34 = uStack_304;
    auVar13._4_4_ = uStack_30c;
    auVar13._0_4_ = uStack_310;
    auVar13._8_4_ = uStack_308;
    auVar13._12_4_ = uStack_304;
    auVar70 = _lqc2(auVar13);
    auVar35._4_4_ = uStack_2c;
    auVar35._0_4_ = uStack_30;
    auVar35._8_4_ = uStack_28;
    auVar35._12_4_ = uStack_24;
    auVar71 = _lqc2(auVar35);
    auVar70 = _vmul(auVar70,auVar71);
    auVar70 = _vaddbc(auVar70,auVar70);
    auVar70 = _vaddbc(auVar70,auVar70);
    auVar70 = _qmfc2(auVar70._0_4_);
    fStack_10 = auVar70._0_4_;
    fStack_31c = -*(float *)(iGpffff86b4 + 0x3f18) / 2.0;
    fStack_320 = (-*(float *)(iGpffff86b4 + 0x3f14) - 10.0) / 2.0 - 10.0;
    uStack_318 = 0x41200000;
    uStack_314 = 0x3f800000;
    fStack_18 = 10.0;
    uStack_14 = 0x3f800000;
    uStack_330 = 0x3f800000;
    uStack_32c = 0;
    uStack_328 = 0x3f800000;
    uStack_324 = 0x3f800000;
    uStack_30 = 0x3f800000;
    uStack_2c = 0;
    uStack_28 = 0x3f800000;
    uStack_24 = 0x3f800000;
    auVar70 = _lqc2(*param_3);
    auVar58._4_4_ = fStack_31c;
    auVar58._0_4_ = fStack_320;
    auVar58._8_4_ = 0x41200000;
    auVar58._12_4_ = 0x3f800000;
    auVar71 = _lqc2(auVar58);
    auVar70 = _vsub(auVar70,auVar71);
    auStack_560 = _sqc2(auVar70);
    fStack_20 = fStack_320;
    fStack_1c = fStack_31c;
    __ct__7FVectorFRC7FVector(&uStack_340,auStack_560);
    uStack_40 = uStack_340;
    uStack_3c = uStack_33c;
    uStack_38 = uStack_338;
    uStack_34 = uStack_334;
    auVar14._4_4_ = uStack_33c;
    auVar14._0_4_ = uStack_340;
    auVar14._8_4_ = uStack_338;
    auVar14._12_4_ = uStack_334;
    auVar70 = _lqc2(auVar14);
    auVar36._4_4_ = uStack_2c;
    auVar36._0_4_ = uStack_30;
    auVar36._8_4_ = uStack_28;
    auVar36._12_4_ = uStack_24;
    auVar71 = _lqc2(auVar36);
    auVar70 = _vmul(auVar70,auVar71);
    auVar70 = _vaddbc(auVar70,auVar70);
    auVar70 = _vaddbc(auVar70,auVar70);
    auVar70 = _qmfc2(auVar70._0_4_);
    fStack_c = auVar70._0_4_;
    if (((fStack_10 <= 0.0) && (fStack_c <= 0.0)) ||
       (-1 < (long)((ulong)*(byte *)(param_2 + 0x214) << 0x3a))) {
      *(undefined4 *)(param_2 + 0x188) = 0;
      if ((*(float *)(param_2 + 0x158) != 0.0) || (param_5 == '\x01')) {
        *(undefined4 *)(param_2 + 0x158) = 0;
        fVar68 = *(float *)(param_2 + 0x158);
        if (fVar68 < 2.1474836e+09) {
          uVar69 = (uint)fVar68;
        }
        else {
          uVar69 = (int)(fVar68 - 2.1474836e+09) | 0x80000000;
        }
        (**(code **)(*(int *)(*(int *)(iGpffff86b4 + 0x3f20) + 0x10) + 0x54))
                  (*(int *)(iGpffff86b4 + 0x3f20),5,uVar69,0);
      }
    }
    else if (param_5 == '\x01') {
      *(undefined4 *)(param_2 + 0x158) = 0x43000000;
      *(undefined4 *)(param_2 + 0x188) = 0x3f000000;
      fVar68 = *(float *)(param_2 + 0x158);
      if (fVar68 < 2.1474836e+09) {
        uVar69 = (uint)fVar68;
      }
      else {
        uVar69 = (int)(fVar68 - 2.1474836e+09) | 0x80000000;
      }
      (**(code **)(*(int *)(*(int *)(iGpffff86b4 + 0x3f20) + 0x10) + 0x54))
                (*(int *)(iGpffff86b4 + 0x3f20),5,uVar69,0);
    }
    else {
      *(float *)(param_2 + 0x188) = *(float *)(param_2 + 0x188) + param_1;
      if ((0.5 <= *(float *)(param_2 + 0x188)) &&
         (*(undefined4 *)(param_2 + 0x188) = 0x3f000000, *(float *)(param_2 + 0x158) < 128.0)) {
        *(float *)(param_2 + 0x158) = *(float *)(param_2 + 0x158) + param_1 * 256.0;
        if (128.0 < *(float *)(param_2 + 0x158)) {
          *(undefined4 *)(param_2 + 0x158) = 0x43000000;
        }
        fVar68 = *(float *)(param_2 + 0x158);
        if (fVar68 < 2.1474836e+09) {
          uVar69 = (uint)fVar68;
        }
        else {
          uVar69 = (int)(fVar68 - 2.1474836e+09) | 0x80000000;
        }
        (**(code **)(*(int *)(*(int *)(iGpffff86b4 + 0x3f20) + 0x10) + 0x54))
                  (*(int *)(iGpffff86b4 + 0x3f20),5,uVar69,0);
      }
    }
    fStack_348 = (*(float *)(iGpffff86b4 + 0x3f1c) + 10.0) / 4.0;
    fStack_34c = -*(float *)(iGpffff86b4 + 0x3f18) / 2.0;
    fStack_350 = (*(float *)(iGpffff86b4 + 0x3f14) + 10.0) / 2.0;
    uStack_344 = 0x3f800000;
    uStack_14 = 0x3f800000;
    uStack_360 = 0xbf800000;
    uStack_35c = 0;
    uStack_358 = 0;
    uStack_354 = 0x3f800000;
    uStack_30 = 0xbf800000;
    uStack_2c = 0;
    uStack_28 = 0;
    uStack_24 = 0x3f800000;
    auVar70 = _lqc2(*param_3);
    auVar59._4_4_ = fStack_34c;
    auVar59._0_4_ = fStack_350;
    auVar59._8_4_ = fStack_348;
    auVar59._12_4_ = 0x3f800000;
    auVar71 = _lqc2(auVar59);
    auVar70 = _vsub(auVar70,auVar71);
    auStack_570 = _sqc2(auVar70);
    fStack_20 = fStack_350;
    fStack_1c = fStack_34c;
    fStack_18 = fStack_348;
    __ct__7FVectorFRC7FVector(&uStack_370,auStack_570);
    uStack_40 = uStack_370;
    uStack_3c = uStack_36c;
    uStack_38 = uStack_368;
    uStack_34 = uStack_364;
    auVar15._4_4_ = uStack_36c;
    auVar15._0_4_ = uStack_370;
    auVar15._8_4_ = uStack_368;
    auVar15._12_4_ = uStack_364;
    auVar70 = _lqc2(auVar15);
    auVar37._4_4_ = uStack_2c;
    auVar37._0_4_ = uStack_30;
    auVar37._8_4_ = uStack_28;
    auVar37._12_4_ = uStack_24;
    auVar71 = _lqc2(auVar37);
    auVar70 = _vmul(auVar70,auVar71);
    auVar70 = _vaddbc(auVar70,auVar70);
    auVar70 = _vaddbc(auVar70,auVar70);
    auVar70 = _qmfc2(auVar70._0_4_);
    fStack_10 = auVar70._0_4_;
    fStack_37c = -*(float *)(iGpffff86b4 + 0x3f18) / 2.0;
    fStack_380 = (*(float *)(iGpffff86b4 + 0x3f14) + 10.0) / 2.0 + 10.0;
    uStack_378 = 0xc1200000;
    uStack_374 = 0x3f800000;
    fStack_18 = -10.0;
    uStack_14 = 0x3f800000;
    uStack_390 = 0xbf800000;
    uStack_38c = 0;
    uStack_388 = 0xbf800000;
    uStack_384 = 0x3f800000;
    uStack_30 = 0xbf800000;
    uStack_2c = 0;
    uStack_28 = 0xbf800000;
    uStack_24 = 0x3f800000;
    auVar70 = _lqc2(*param_3);
    auVar60._4_4_ = fStack_37c;
    auVar60._0_4_ = fStack_380;
    auVar60._8_4_ = 0xc1200000;
    auVar60._12_4_ = 0x3f800000;
    auVar71 = _lqc2(auVar60);
    auVar70 = _vsub(auVar70,auVar71);
    auStack_580 = _sqc2(auVar70);
    fStack_20 = fStack_380;
    fStack_1c = fStack_37c;
    __ct__7FVectorFRC7FVector(&uStack_3a0,auStack_580);
    uStack_40 = uStack_3a0;
    uStack_3c = uStack_39c;
    uStack_38 = uStack_398;
    uStack_34 = uStack_394;
    auVar16._4_4_ = uStack_39c;
    auVar16._0_4_ = uStack_3a0;
    auVar16._8_4_ = uStack_398;
    auVar16._12_4_ = uStack_394;
    auVar70 = _lqc2(auVar16);
    auVar38._4_4_ = uStack_2c;
    auVar38._0_4_ = uStack_30;
    auVar38._8_4_ = uStack_28;
    auVar38._12_4_ = uStack_24;
    auVar71 = _lqc2(auVar38);
    auVar70 = _vmul(auVar70,auVar71);
    auVar70 = _vaddbc(auVar70,auVar70);
    auVar70 = _vaddbc(auVar70,auVar70);
    auVar70 = _qmfc2(auVar70._0_4_);
    fStack_8 = auVar70._0_4_;
    if (((fStack_10 <= 0.0) && (fStack_8 <= 0.0)) ||
       (-1 < (long)((ulong)*(byte *)(param_2 + 0x214) << 0x39))) {
      *(undefined4 *)(param_2 + 0x18c) = 0;
      if ((*(float *)(param_2 + 0x15c) != 0.0) || (param_5 == '\x01')) {
        *(undefined4 *)(param_2 + 0x15c) = 0;
        fVar68 = *(float *)(param_2 + 0x15c);
        if (fVar68 < 2.1474836e+09) {
          uVar69 = (uint)fVar68;
        }
        else {
          uVar69 = (int)(fVar68 - 2.1474836e+09) | 0x80000000;
        }
        (**(code **)(*(int *)(*(int *)(iGpffff86b4 + 0x3f20) + 0x10) + 0x54))
                  (*(int *)(iGpffff86b4 + 0x3f20),6,uVar69,0);
      }
    }
    else if (param_5 == '\x01') {
      *(undefined4 *)(param_2 + 0x15c) = 0x43000000;
      *(undefined4 *)(param_2 + 0x18c) = 0x3f000000;
      fVar68 = *(float *)(param_2 + 0x15c);
      if (fVar68 < 2.1474836e+09) {
        uVar69 = (uint)fVar68;
      }
      else {
        uVar69 = (int)(fVar68 - 2.1474836e+09) | 0x80000000;
      }
      (**(code **)(*(int *)(*(int *)(iGpffff86b4 + 0x3f20) + 0x10) + 0x54))
                (*(int *)(iGpffff86b4 + 0x3f20),6,uVar69,0);
    }
    else {
      *(float *)(param_2 + 0x18c) = *(float *)(param_2 + 0x18c) + param_1;
      if ((0.5 <= *(float *)(param_2 + 0x18c)) &&
         (*(undefined4 *)(param_2 + 0x18c) = 0x3f000000, *(float *)(param_2 + 0x15c) < 128.0)) {
        *(float *)(param_2 + 0x15c) = *(float *)(param_2 + 0x15c) + param_1 * 256.0;
        if (128.0 < *(float *)(param_2 + 0x15c)) {
          *(undefined4 *)(param_2 + 0x15c) = 0x43000000;
        }
        fVar68 = *(float *)(param_2 + 0x15c);
        if (fVar68 < 2.1474836e+09) {
          uVar69 = (uint)fVar68;
        }
        else {
          uVar69 = (int)(fVar68 - 2.1474836e+09) | 0x80000000;
        }
        (**(code **)(*(int *)(*(int *)(iGpffff86b4 + 0x3f20) + 0x10) + 0x54))
                  (*(int *)(iGpffff86b4 + 0x3f20),6,uVar69,0);
      }
    }
    fStack_3a8 = (-*(float *)(iGpffff86b4 + 0x3f1c) - 10.0) / 4.0;
    fStack_3ac = -*(float *)(iGpffff86b4 + 0x3f18) / 2.0;
    fStack_3b0 = (*(float *)(iGpffff86b4 + 0x3f14) + 10.0) / 2.0;
    uStack_3a4 = 0x3f800000;
    uStack_14 = 0x3f800000;
    uStack_3c0 = 0xbf800000;
    uStack_3bc = 0;
    uStack_3b8 = 0;
    uStack_3b4 = 0x3f800000;
    uStack_30 = 0xbf800000;
    uStack_2c = 0;
    uStack_28 = 0;
    uStack_24 = 0x3f800000;
    auVar70 = _lqc2(*param_3);
    auVar61._4_4_ = fStack_3ac;
    auVar61._0_4_ = fStack_3b0;
    auVar61._8_4_ = fStack_3a8;
    auVar61._12_4_ = 0x3f800000;
    auVar71 = _lqc2(auVar61);
    auVar70 = _vsub(auVar70,auVar71);
    auStack_590 = _sqc2(auVar70);
    fStack_20 = fStack_3b0;
    fStack_1c = fStack_3ac;
    fStack_18 = fStack_3a8;
    __ct__7FVectorFRC7FVector(&uStack_3d0,auStack_590);
    uStack_40 = uStack_3d0;
    uStack_3c = uStack_3cc;
    uStack_38 = uStack_3c8;
    uStack_34 = uStack_3c4;
    auVar17._4_4_ = uStack_3cc;
    auVar17._0_4_ = uStack_3d0;
    auVar17._8_4_ = uStack_3c8;
    auVar17._12_4_ = uStack_3c4;
    auVar70 = _lqc2(auVar17);
    auVar39._4_4_ = uStack_2c;
    auVar39._0_4_ = uStack_30;
    auVar39._8_4_ = uStack_28;
    auVar39._12_4_ = uStack_24;
    auVar71 = _lqc2(auVar39);
    auVar70 = _vmul(auVar70,auVar71);
    auVar70 = _vaddbc(auVar70,auVar70);
    auVar70 = _vaddbc(auVar70,auVar70);
    auVar70 = _qmfc2(auVar70._0_4_);
    fStack_10 = auVar70._0_4_;
    fStack_3dc = -*(float *)(iGpffff86b4 + 0x3f18) / 2.0;
    fStack_3e0 = (*(float *)(iGpffff86b4 + 0x3f14) + 10.0) / 2.0 + 10.0;
    uStack_3d8 = 0x41200000;
    uStack_3d4 = 0x3f800000;
    fStack_18 = 10.0;
    uStack_14 = 0x3f800000;
    uStack_3f0 = 0xbf800000;
    uStack_3ec = 0;
    uStack_3e8 = 0x3f800000;
    uStack_3e4 = 0x3f800000;
    uStack_30 = 0xbf800000;
    uStack_2c = 0;
    uStack_28 = 0x3f800000;
    uStack_24 = 0x3f800000;
    auVar70 = _lqc2(*param_3);
    auVar62._4_4_ = fStack_3dc;
    auVar62._0_4_ = fStack_3e0;
    auVar62._8_4_ = 0x41200000;
    auVar62._12_4_ = 0x3f800000;
    auVar71 = _lqc2(auVar62);
    auVar70 = _vsub(auVar70,auVar71);
    auStack_5a0 = _sqc2(auVar70);
    fStack_20 = fStack_3e0;
    fStack_1c = fStack_3dc;
    __ct__7FVectorFRC7FVector(&uStack_400,auStack_5a0);
    uStack_40 = uStack_400;
    uStack_3c = uStack_3fc;
    uStack_38 = uStack_3f8;
    uStack_34 = uStack_3f4;
    auVar18._4_4_ = uStack_3fc;
    auVar18._0_4_ = uStack_400;
    auVar18._8_4_ = uStack_3f8;
    auVar18._12_4_ = uStack_3f4;
    auVar70 = _lqc2(auVar18);
    auVar40._4_4_ = uStack_2c;
    auVar40._0_4_ = uStack_30;
    auVar40._8_4_ = uStack_28;
    auVar40._12_4_ = uStack_24;
    auVar71 = _lqc2(auVar40);
    auVar70 = _vmul(auVar70,auVar71);
    auVar70 = _vaddbc(auVar70,auVar70);
    auVar70 = _vaddbc(auVar70,auVar70);
    auVar70 = _qmfc2(auVar70._0_4_);
    fStack_c = auVar70._0_4_;
    if (((fStack_10 <= 0.0) && (fStack_c <= 0.0)) ||
       (-1 < (long)((ulong)*(byte *)(param_2 + 0x214) << 0x38))) {
      *(undefined4 *)(param_2 + 400) = 0;
      if ((*(float *)(param_2 + 0x160) != 0.0) || (param_5 == '\x01')) {
        *(undefined4 *)(param_2 + 0x160) = 0;
        fVar68 = *(float *)(param_2 + 0x160);
        if (fVar68 < 2.1474836e+09) {
          uVar69 = (uint)fVar68;
        }
        else {
          uVar69 = (int)(fVar68 - 2.1474836e+09) | 0x80000000;
        }
        (**(code **)(*(int *)(*(int *)(iGpffff86b4 + 0x3f20) + 0x10) + 0x54))
                  (*(int *)(iGpffff86b4 + 0x3f20),7,uVar69,0);
      }
    }
    else if (param_5 == '\x01') {
      *(undefined4 *)(param_2 + 0x160) = 0x43000000;
      *(undefined4 *)(param_2 + 400) = 0x3f000000;
      fVar68 = *(float *)(param_2 + 0x160);
      if (fVar68 < 2.1474836e+09) {
        uVar69 = (uint)fVar68;
      }
      else {
        uVar69 = (int)(fVar68 - 2.1474836e+09) | 0x80000000;
      }
      (**(code **)(*(int *)(*(int *)(iGpffff86b4 + 0x3f20) + 0x10) + 0x54))
                (*(int *)(iGpffff86b4 + 0x3f20),7,uVar69,0);
    }
    else {
      *(float *)(param_2 + 400) = *(float *)(param_2 + 400) + param_1;
      if ((0.5 <= *(float *)(param_2 + 400)) &&
         (*(undefined4 *)(param_2 + 400) = 0x3f000000, *(float *)(param_2 + 0x160) < 128.0)) {
        *(float *)(param_2 + 0x160) = *(float *)(param_2 + 0x160) + param_1 * 256.0;
        if (128.0 < *(float *)(param_2 + 0x160)) {
          *(undefined4 *)(param_2 + 0x160) = 0x43000000;
        }
        fVar68 = *(float *)(param_2 + 0x160);
        if (fVar68 < 2.1474836e+09) {
          uVar69 = (uint)fVar68;
        }
        else {
          uVar69 = (int)(fVar68 - 2.1474836e+09) | 0x80000000;
        }
        (**(code **)(*(int *)(*(int *)(iGpffff86b4 + 0x3f20) + 0x10) + 0x54))
                  (*(int *)(iGpffff86b4 + 0x3f20),7,uVar69,0);
      }
    }
  }
  fStack_40c = -*(float *)(iGpffff86b4 + 0x3f18);
  uStack_410 = 0;
  uStack_408 = 0;
  uStack_404 = 0x3f800000;
  fStack_20 = 0.0;
  fStack_18 = 0.0;
  uStack_14 = 0x3f800000;
  uStack_420 = 0;
  uStack_41c = 0x3f800000;
  uStack_418 = 0;
  uStack_414 = 0x3f800000;
  uStack_30 = 0;
  uStack_2c = 0x3f800000;
  uStack_28 = 0;
  uStack_24 = 0x3f800000;
  auVar70 = _lqc2(*param_3);
  auVar65._4_8_ = 0;
  auVar65._0_4_ = fStack_40c;
  auVar63._12_4_ = 0x3f800000;
  auVar63._0_12_ = auVar65 << 0x20;
  auVar71 = _lqc2(auVar63);
  auVar70 = _vsub(auVar70,auVar71);
  auStack_5b0 = _sqc2(auVar70);
  fStack_1c = fStack_40c;
  __ct__7FVectorFRC7FVector(&uStack_430,auStack_5b0);
  uStack_40 = uStack_430;
  uStack_3c = uStack_42c;
  uStack_38 = uStack_428;
  uStack_34 = uStack_424;
  auVar19._4_4_ = uStack_42c;
  auVar19._0_4_ = uStack_430;
  auVar19._8_4_ = uStack_428;
  auVar19._12_4_ = uStack_424;
  auVar70 = _lqc2(auVar19);
  auVar41._4_4_ = uStack_2c;
  auVar41._0_4_ = uStack_30;
  auVar41._8_4_ = uStack_28;
  auVar41._12_4_ = uStack_24;
  auVar71 = _lqc2(auVar41);
  auVar70 = _vmul(auVar70,auVar71);
  auVar70 = _vaddbc(auVar70,auVar70);
  auVar70 = _vaddbc(auVar70,auVar70);
  auVar70 = _qmfc2(auVar70._0_4_);
  fStack_10 = auVar70._0_4_;
  if ((fStack_10 <= 0.0) || ((*(byte *)(param_2 + 0x215) & 1) == 0)) {
    *(undefined4 *)(param_2 + 0x194) = 0;
    if ((*(float *)(param_2 + 0x164) != 0.0) || (param_5 == '\x01')) {
      *(undefined4 *)(param_2 + 0x164) = 0;
      fVar68 = *(float *)(param_2 + 0x164);
      if (fVar68 < 2.1474836e+09) {
        uVar69 = (uint)fVar68;
      }
      else {
        uVar69 = (int)(fVar68 - 2.1474836e+09) | 0x80000000;
      }
      (**(code **)(*(int *)(*(int *)(iGpffff86b4 + 0x3f20) + 0x10) + 0x54))
                (*(int *)(iGpffff86b4 + 0x3f20),8,uVar69,0);
    }
  }
  else if (param_5 == '\x01') {
    *(undefined4 *)(param_2 + 0x164) = 0x43000000;
    *(undefined4 *)(param_2 + 0x194) = 0x3f000000;
    fVar68 = *(float *)(param_2 + 0x164);
    if (fVar68 < 2.1474836e+09) {
      uVar69 = (uint)fVar68;
    }
    else {
      uVar69 = (int)(fVar68 - 2.1474836e+09) | 0x80000000;
    }
    (**(code **)(*(int *)(*(int *)(iGpffff86b4 + 0x3f20) + 0x10) + 0x54))
              (*(int *)(iGpffff86b4 + 0x3f20),8,uVar69,0);
  }
  else {
    *(float *)(param_2 + 0x194) = *(float *)(param_2 + 0x194) + param_1;
    if ((0.5 <= *(float *)(param_2 + 0x194)) &&
       (*(undefined4 *)(param_2 + 0x194) = 0x3f000000, *(float *)(param_2 + 0x164) < 128.0)) {
      *(float *)(param_2 + 0x164) = *(float *)(param_2 + 0x164) + param_1 * 256.0;
      if (128.0 < *(float *)(param_2 + 0x164)) {
        *(undefined4 *)(param_2 + 0x164) = 0x43000000;
      }
      fVar68 = *(float *)(param_2 + 0x164);
      if (fVar68 < 2.1474836e+09) {
        uVar69 = (uint)fVar68;
      }
      else {
        uVar69 = (int)(fVar68 - 2.1474836e+09) | 0x80000000;
      }
      (**(code **)(*(int *)(*(int *)(iGpffff86b4 + 0x3f20) + 0x10) + 0x54))
                (*(int *)(iGpffff86b4 + 0x3f20),8,uVar69,0);
    }
  }
  uStack_440 = 0;
  uStack_43c = 0;
  uStack_438 = 0;
  uStack_434 = 0x3f800000;
  fStack_20 = 0.0;
  fStack_1c = 0.0;
  fStack_18 = 0.0;
  uStack_14 = 0x3f800000;
  uStack_450 = 0;
  uStack_44c = 0xbf800000;
  uStack_448 = 0;
  uStack_444 = 0x3f800000;
  uStack_30 = 0;
  uStack_2c = 0xbf800000;
  uStack_28 = 0;
  uStack_24 = 0x3f800000;
  auVar70 = _lqc2(*param_3);
  auVar64._12_4_ = 0x3f800000;
  auVar64._0_12_ = ZEXT812(0);
  auVar71 = _lqc2(auVar64);
  auVar70 = _vsub(auVar70,auVar71);
  auStack_5c0 = _sqc2(auVar70);
  __ct__7FVectorFRC7FVector(&uStack_460,auStack_5c0);
  uStack_40 = uStack_460;
  uStack_3c = uStack_45c;
  uStack_38 = uStack_458;
  uStack_34 = uStack_454;
  auVar20._4_4_ = uStack_45c;
  auVar20._0_4_ = uStack_460;
  auVar20._8_4_ = uStack_458;
  auVar20._12_4_ = uStack_454;
  auVar70 = _lqc2(auVar20);
  auVar42._4_4_ = uStack_2c;
  auVar42._0_4_ = uStack_30;
  auVar42._8_4_ = uStack_28;
  auVar42._12_4_ = uStack_24;
  auVar71 = _lqc2(auVar42);
  auVar70 = _vmul(auVar70,auVar71);
  auVar70 = _vaddbc(auVar70,auVar70);
  auVar70 = _vaddbc(auVar70,auVar70);
  auVar70 = _qmfc2(auVar70._0_4_);
  fStack_10 = auVar70._0_4_;
  if ((fStack_10 <= 0.0) || (-1 < (long)((ulong)*(byte *)(param_2 + 0x215) << 0x3e))) {
    *(undefined4 *)(param_2 + 0x198) = 0;
    if ((*(float *)(param_2 + 0x168) != 0.0) || (param_5 == '\x01')) {
      *(undefined4 *)(param_2 + 0x168) = 0;
      fVar68 = *(float *)(param_2 + 0x168);
      if (fVar68 < 2.1474836e+09) {
        uVar69 = (uint)fVar68;
      }
      else {
        uVar69 = (int)(fVar68 - 2.1474836e+09) | 0x80000000;
      }
      (**(code **)(*(int *)(*(int *)(iGpffff86b4 + 0x3f20) + 0x10) + 0x54))
                (*(int *)(iGpffff86b4 + 0x3f20),9,uVar69,0);
    }
  }
  else if (param_5 == '\x01') {
    *(undefined4 *)(param_2 + 0x168) = 0x43000000;
    *(undefined4 *)(param_2 + 0x198) = 0x3f000000;
    fVar68 = *(float *)(param_2 + 0x168);
    if (fVar68 < 2.1474836e+09) {
      uVar69 = (uint)fVar68;
    }
    else {
      uVar69 = (int)(fVar68 - 2.1474836e+09) | 0x80000000;
    }
    (**(code **)(*(int *)(*(int *)(iGpffff86b4 + 0x3f20) + 0x10) + 0x54))
              (*(int *)(iGpffff86b4 + 0x3f20),9,uVar69,0);
  }
  else {
    *(float *)(param_2 + 0x198) = *(float *)(param_2 + 0x198) + param_1;
    if ((0.5 <= *(float *)(param_2 + 0x198)) &&
       (*(undefined4 *)(param_2 + 0x198) = 0x3f000000, *(float *)(param_2 + 0x168) < 128.0)) {
      *(float *)(param_2 + 0x168) = *(float *)(param_2 + 0x168) + param_1 * 256.0;
      if (128.0 < *(float *)(param_2 + 0x168)) {
        *(undefined4 *)(param_2 + 0x168) = 0x43000000;
      }
      fVar68 = *(float *)(param_2 + 0x168);
      if (fVar68 < 2.1474836e+09) {
        uVar69 = (uint)fVar68;
      }
      else {
        uVar69 = (int)(fVar68 - 2.1474836e+09) | 0x80000000;
      }
      (**(code **)(*(int *)(*(int *)(iGpffff86b4 + 0x3f20) + 0x10) + 0x54))
                (*(int *)(iGpffff86b4 + 0x3f20),9,uVar69,0);
    }
  }
  if ((long)((ulong)*(byte *)(param_2 + 0x215) << 0x3d) < 0) {
    if (param_5 == '\x01') {
      *(undefined4 *)(param_2 + 0x16c) = 0x43000000;
      *(undefined4 *)(param_2 + 0x19c) = 0x3f000000;
      fVar68 = *(float *)(param_2 + 0x16c);
      if (fVar68 < 2.1474836e+09) {
        uVar69 = (uint)fVar68;
      }
      else {
        uVar69 = (int)(fVar68 - 2.1474836e+09) | 0x80000000;
      }
      (**(code **)(*(int *)(*(int *)(iGpffff86b4 + 0x3f20) + 0x10) + 0x54))
                (*(int *)(iGpffff86b4 + 0x3f20),10,uVar69,0);
    }
    else {
      *(float *)(param_2 + 0x19c) = *(float *)(param_2 + 0x19c) + param_1;
      if ((0.5 <= *(float *)(param_2 + 0x19c)) &&
         (*(undefined4 *)(param_2 + 0x19c) = 0x3f000000, *(float *)(param_2 + 0x16c) < 128.0)) {
        *(float *)(param_2 + 0x16c) = *(float *)(param_2 + 0x16c) + param_1 * 256.0;
        if (128.0 < *(float *)(param_2 + 0x16c)) {
          *(undefined4 *)(param_2 + 0x16c) = 0x43000000;
        }
        fVar68 = *(float *)(param_2 + 0x16c);
        if (fVar68 < 2.1474836e+09) {
          uVar69 = (uint)fVar68;
        }
        else {
          uVar69 = (int)(fVar68 - 2.1474836e+09) | 0x80000000;
        }
        (**(code **)(*(int *)(*(int *)(iGpffff86b4 + 0x3f20) + 0x10) + 0x54))
                  (*(int *)(iGpffff86b4 + 0x3f20),10,uVar69,0);
      }
    }
  }
  else {
    *(undefined4 *)(param_2 + 0x19c) = 0;
    if ((*(float *)(param_2 + 0x16c) != 0.0) || (param_5 == '\x01')) {
      *(undefined4 *)(param_2 + 0x16c) = 0;
      fVar68 = *(float *)(param_2 + 0x16c);
      if (fVar68 < 2.1474836e+09) {
        uVar69 = (uint)fVar68;
      }
      else {
        uVar69 = (int)(fVar68 - 2.1474836e+09) | 0x80000000;
      }
      (**(code **)(*(int *)(*(int *)(iGpffff86b4 + 0x3f20) + 0x10) + 0x54))
                (*(int *)(iGpffff86b4 + 0x3f20),10,uVar69,0);
    }
  }
  return;
}

