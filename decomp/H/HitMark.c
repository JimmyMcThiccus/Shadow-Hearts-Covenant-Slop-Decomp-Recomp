/* decomp/H/HitMark.c — cleaned Ghidra output (SH2JP_BATTLE.BIN, JP Furokuban, base 0x00430a00).
 * 10 function(s). Types: see types.h. Names/gp globals resolved from symbols/SLPM_602.19.syms. */
#include "types.h"

/* ---------------------------------------------------------------------------
 * JP: 0x00507ec0  __ct__7HitMarkFii7FVectorif
 * C++: HitMark::__ct(int, int, FVector, int, float)
 * size: 0x110 bytes
 * --------------------------------------------------------------------------- */
undefined8
__ct__7HitMarkFii7FVectorif
          (undefined4 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
          undefined8 *param_5,undefined4 param_6)

{
  undefined8 uVar1;
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  
  __ct__6BtlEffFii(param_2,param_3,param_4);
  iVar4 = (int)param_2;
  *(undefined4 *)(iVar4 + 0x14) = 0x40a300;
  *(undefined4 *)(iVar4 + 0x28) = 0x40a310;
  *(undefined4 *)(iVar4 + 0x34) = 0x40a320;
  *(undefined4 *)(iVar4 + 0x70) = in_zero_lo;
  *(undefined4 *)(iVar4 + 0x74) = in_zero_hi;
  *(undefined4 *)(iVar4 + 0x78) = in_zero_udw;
  *(undefined4 *)(iVar4 + 0x7c) = in_register_0000000c;
  *(int *)(iVar4 + 0x44) = (int)param_3;
  *(int *)(iVar4 + 0x48) = (int)param_4;
  *(undefined4 *)(iVar4 + 0x4c) = 1;
  *(undefined4 *)(iVar4 + 0x5c) = param_6;
  *(undefined4 *)(iVar4 + 0x60) = 0;
  uVar1 = *param_5;
  uVar2 = *(undefined4 *)(param_5 + 1);
  uVar3 = *(undefined4 *)((int)param_5 + 0xc);
  *(int *)(iVar4 + 0x70) = (int)uVar1;
  *(int *)(iVar4 + 0x74) = (int)((ulong)uVar1 >> 0x20);
  *(undefined4 *)(iVar4 + 0x78) = uVar2;
  *(undefined4 *)(iVar4 + 0x7c) = uVar3;
  *(undefined4 *)(iVar4 + 0x80) = 0;
  *(undefined4 *)(iVar4 + 0x1c) = 0;
  *(undefined4 *)(iVar4 + 0x18) = 0;
  *(undefined4 *)(iVar4 + 0x88) = param_1;
  *(undefined4 *)(iVar4 + 0x8c) = 0;
  Entry__7CPollerFP7CPolObjib(iGpffff858c + 0x48,param_2,0x80,0);
  BtlEffEntry__7CBattleFiP6BtlEff(uGpffff86b4,0xffffffffffffffff,param_2);
  return param_2;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00507fd0  __dt__7HitMarkFv
 * C++: HitMark::__dt()
 * size: 0x154 bytes
 * --------------------------------------------------------------------------- */
int __dt__7HitMarkFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x14) = 0x40a300;
    *(undefined4 *)(param_1 + 0x28) = 0x40a310;
    *(undefined4 *)(param_1 + 0x34) = 0x40a320;
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
 * JP: 0x00508130  Destruct__7HitMarkFv
 * C++: HitMark::Destruct()
 * size: 0xc8 bytes
 * --------------------------------------------------------------------------- */
void Destruct__7HitMarkFv(int param_1)

{
  int iVar1;
  
  BtlEffRelease__7CBattleFiP6BtlEff(uGpffff86b4,0xffffffffffffffff,param_1);
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
 * JP: 0x00508200  Polling__7HitMarkFv
 * C++: HitMark::Polling()
 * size: 0x250 bytes
 * --------------------------------------------------------------------------- */
undefined4 Polling__7HitMarkFv(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined1 auStack_b0 [8];
  int iStack_a8;
  undefined4 auStack_a0 [16];
  undefined4 auStack_60 [19];
  float fStack_14;
  int iStack_10;
  
  fStack_14 = *(float *)(iGpffff86b4 + 0x38) * *(float *)(param_1 + 0x88);
  if ((*(byte *)(iGpffff86b4 + 0x24) & 1) == 0) {
    *(float *)(param_1 + 0x80) = *(float *)(param_1 + 0x80) + fStack_14 * 1.5;
  }
  *(int *)(param_1 + 0x60) = (int)((*(float *)(param_1 + 0x80) * 60.0) / 4.0) << 6;
  iStack_10 = param_1;
  if (*(int *)(param_1 + 0x60) < 0x340) {
    GetViewScreenMatrix__9GsxCameraFv(auStack_60,uGpffff8598);
    for (iVar2 = 0; iVar2 < 4; iVar2 = iVar2 + 1) {
      auStack_a0[iVar2 * 4] = auStack_60[iVar2 * 4];
      auStack_a0[iVar2 * 4 + 1] = auStack_60[iVar2 * 4 + 1];
      auStack_a0[iVar2 * 4 + 2] = auStack_60[iVar2 * 4 + 2];
      auStack_a0[iVar2 * 4 + 3] = auStack_60[iVar2 * 4 + 3];
    }
    sceVu0RotTransPersN(auStack_b0,auStack_a0,iStack_10 + 0x70,1,0);
    *(int *)(iStack_10 + 0x50) = (int)((float)iStack_a8 / 16.0);
    uVar1 = 0;
  }
  else {
    BtlEffRelease__7CBattleFiP6BtlEff(iGpffff86b4,0xffffffffffffffff,param_1);
    if ((long)((ulong)*(byte *)(iStack_10 + 0x40) << 0x3e) < 0) {
      iVar2 = iStack_10;
      if (iStack_10 != 0) {
        iVar2 = iStack_10 + 0x18;
      }
      ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,iVar2);
    }
    *(byte *)(iStack_10 + 0x40) = *(byte *)(iStack_10 + 0x40) & 0xfd;
    (**(code **)(*(int *)(iStack_10 + 0x34) + 0xc))();
    uVar1 = 1;
  }
  return uVar1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00508450  MakePacket__7HitMarkFv
 * C++: HitMark::MakePacket()
 * size: 0xc4c bytes
 * --------------------------------------------------------------------------- */
void MakePacket__7HitMarkFv(int param_1)

{
  bool bVar1;
  undefined4 *puVar2;
  bool bVar3;
  float in_zero_lo;
  float in_zero_hi;
  float in_zero_udw;
  float in_register_0000000c;
  undefined4 uVar4;
  undefined8 uVar5;
  long lVar6;
  undefined8 extraout_v0_udw;
  float *pfVar7;
  int iVar8;
  uint uVar9;
  float fVar10;
  undefined1 in_vf0 [16];
  undefined1 auVar11 [16];
  undefined1 auVar12 [16];
  undefined1 auVar13 [16];
  undefined1 auStack_6c0 [64];
  undefined4 auStack_680 [16];
  undefined1 auStack_640 [16];
  undefined1 auStack_630 [16];
  undefined1 auStack_620 [16];
  undefined1 auStack_610 [16];
  int aiStack_600 [96];
  float afStack_480 [96];
  float afStack_300 [192];
  
  pfVar7 = afStack_300 + 0x60;
  do {
    *pfVar7 = in_zero_lo;
    pfVar7[1] = in_zero_hi;
    pfVar7[2] = in_zero_udw;
    pfVar7[3] = in_register_0000000c;
    pfVar7 = pfVar7 + 4;
  } while (pfVar7 != (float *)&stack0x00000000);
  pfVar7 = afStack_300;
  do {
    *pfVar7 = in_zero_lo;
    pfVar7[1] = in_zero_hi;
    pfVar7[2] = in_zero_udw;
    pfVar7[3] = in_register_0000000c;
    pfVar7 = pfVar7 + 4;
  } while (pfVar7 != afStack_300 + 0x60);
  auVar11 = _vmr32(in_vf0);
  auVar12 = _vmr32(auVar11);
  auVar13 = _vmr32(auVar12);
  auStack_610 = _sqc2(in_vf0);
  auStack_620 = _sqc2(auVar11);
  auStack_630 = _sqc2(auVar12);
  auStack_640 = _sqc2(auVar13);
  GetViewScreenMatrix__9GsxCameraFv(auStack_6c0,iGpffff8598);
  for (iVar8 = 0; iVar8 < 4; iVar8 = iVar8 + 1) {
    auStack_680[iVar8 * 4] = *(undefined4 *)(auStack_640 + iVar8 * 0x10);
    auStack_680[iVar8 * 4 + 1] = *(undefined4 *)(auStack_640 + iVar8 * 0x10 + 4);
    auStack_680[iVar8 * 4 + 2] = *(undefined4 *)(auStack_640 + iVar8 * 0x10 + 8);
    auStack_680[iVar8 * 4 + 3] = *(undefined4 *)(auStack_640 + iVar8 * 0x10 + 0xc);
  }
  auStack_640 = *(undefined1 (*) [16])(iGpffff8598 + 0x240);
  auStack_630 = *(undefined1 (*) [16])(iGpffff8598 + 0x250);
  auStack_620 = *(undefined1 (*) [16])(iGpffff8598 + 0x260);
  auStack_610._0_12_ = ZEXT812(0);
  auStack_610._12_4_ = 0x3f800000;
  bVar1 = (*(byte *)(param_1 + 0x40) & 1) == 0;
  uVar9 = (uint)bVar1;
  if (*(int *)(param_1 + 0x5c) == 3) {
    fVar10 = 0.0;
    if (*(float *)(param_1 + 0x80) <= 0.13333334) {
      fVar10 = ((*(float *)(param_1 + 0x80) * 60.0) / 8.0) * 96.0;
    }
    else if (*(float *)(param_1 + 0x80) <= 0.46666667) {
      fVar10 = 96.0;
    }
    else if (*(float *)(param_1 + 0x80) <= 0.8666667) {
      fVar10 = ((52.0 - *(float *)(param_1 + 0x80) * 60.0) / 24.0) * 96.0;
    }
    afStack_300[0x70] = (*(float *)(param_1 + 0x80) * 60.0 * 20.0) / 52.0;
    afStack_300[0x60] = 0.0;
    afStack_300[0x61] = 0.0;
    afStack_300[0x62] = 0.0;
    afStack_300[99] = 1.0;
    afStack_300[100] = -afStack_300[0x70];
    afStack_300[0x65] = 0.0;
    afStack_300[0x66] = 0.0;
    afStack_300[0x67] = 1.0;
    afStack_300[0x68] = -afStack_300[0x70];
    afStack_300[0x69] = -afStack_300[0x70];
    afStack_300[0x6a] = 0.0;
    afStack_300[0x6b] = 1.0;
    afStack_300[0x6d] = -afStack_300[0x70];
    afStack_300[0x6c] = 0.0;
    afStack_300[0x6e] = 0.0;
    afStack_300[0x6f] = 1.0;
    afStack_300[0x71] = -afStack_300[0x70];
    afStack_300[0x72] = 0.0;
    afStack_300[0x73] = 1.0;
    afStack_300[0x75] = 0.0;
    afStack_300[0x76] = 0.0;
    afStack_300[0x77] = 1.0;
    afStack_300[0x7a] = 0.0;
    afStack_300[0x7b] = 1.0;
    afStack_300[0x7c] = 0.0;
    afStack_300[0x7e] = 0.0;
    afStack_300[0x7f] = 1.0;
    afStack_300[0x80] = -afStack_300[0x70];
    afStack_300[0x82] = 0.0;
    afStack_300[0x83] = 1.0;
    afStack_300[0x84] = -afStack_300[0x70];
    afStack_300[0x85] = 0.0;
    afStack_300[0x86] = 0.0;
    afStack_300[0x87] = 1.0;
    afStack_300[0x74] = afStack_300[0x70];
    afStack_300[0x78] = afStack_300[0x70];
    afStack_300[0x79] = afStack_300[0x70];
    afStack_300[0x7d] = afStack_300[0x70];
    afStack_300[0x81] = afStack_300[0x70];
    RotTransVector(afStack_300,afStack_300 + 0x60,auStack_640,10);
    for (iVar8 = 0; iVar8 < 10; iVar8 = iVar8 + 1) {
      afStack_480[iVar8 * 4] = *(float *)(param_1 + 0x70) + afStack_300[iVar8 * 4];
      afStack_480[iVar8 * 4 + 1] = *(float *)(param_1 + 0x74) + afStack_300[iVar8 * 4 + 1];
      afStack_480[iVar8 * 4 + 2] = *(float *)(param_1 + 0x78) + afStack_300[iVar8 * 4 + 2];
      afStack_480[iVar8 * 4 + 3] = 1.0;
    }
    sceVu0RotTransPersN(aiStack_600,auStack_680,afStack_480,10,0);
    bVar3 = false;
    for (iVar8 = 0; iVar8 < 10; iVar8 = iVar8 + 1) {
      if ((((aiStack_600[iVar8 * 4] < 0) || (0x10000 < aiStack_600[iVar8 * 4])) ||
          (aiStack_600[iVar8 * 4 + 1] < 0)) ||
         ((0x10000 < aiStack_600[iVar8 * 4 + 1] || (aiStack_600[iVar8 * 4 + 2] < 0)))) {
        bVar3 = true;
      }
      aiStack_600[iVar8 * 4 + 2] = (int)((float)aiStack_600[iVar8 * 4 + 2] / 16.0);
    }
    if (*(int *)(param_1 + uVar9 * 4 + 0x18) == 0) {
      uVar4 = __nwa__FUi(0x160);
      *(undefined4 *)(param_1 + uVar9 * 4 + 0x18) = uVar4;
      iVar8 = *(int *)(param_1 + uVar9 * 4 + 0x18);
      *(undefined4 *)(iVar8 + 0x10) = 0x10000013;
      *(undefined4 *)(iVar8 + 0x14) = 0;
      *(undefined4 *)(iVar8 + 0x18) = 0;
      *(undefined4 *)(iVar8 + 0x1c) = 0x50000013;
      *(undefined8 *)(iVar8 + 0x20) = 0x4000000000000001;
      *(undefined8 *)(iVar8 + 0x28) = 0xeeee;
      *(undefined8 *)(iVar8 + 0x30) = 1;
      *(undefined8 *)(iVar8 + 0x38) = 0x3f;
      *(undefined8 *)(iVar8 + 0x40) = 0x60;
      *(undefined8 *)(iVar8 + 0x48) = 0x14;
      *(undefined8 *)(iVar8 + 0x50) = 0x53001;
      *(undefined8 *)(iVar8 + 0x58) = 0x47;
      *(undefined8 *)(iVar8 + 0x60) = 0x48;
      *(undefined8 *)(iVar8 + 0x68) = 0x42;
      auVar12._8_8_ = extraout_v0_udw;
      auVar12._0_8_ = 0x8400000000000001;
      auVar11._4_4_ = in_zero_hi;
      auVar11._0_4_ = in_zero_lo;
      auVar11._8_4_ = in_zero_udw;
      auVar11._12_4_ = in_register_0000000c;
      auVar11 = _pcpyld(auVar11,auVar12);
      *(long *)(iVar8 + 0x70) = auVar11._0_8_;
      *(undefined8 *)(iVar8 + 0x78) = 0xc3c31068;
      *(undefined8 *)(iVar8 + 0x80) = 5;
      uVar5 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x4250),1);
      *(undefined8 *)(iVar8 + 0x88) = uVar5;
      *(undefined8 *)(iVar8 + 0x90) = 0x155;
      *(long *)(iVar8 + 0xa0) =
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x4250) + 2) << 4) |
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x4250) + 4) << 4) << 0x10;
      *(long *)(iVar8 + 0xb0) =
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x4250) + 4) << 4) << 0x10;
      *(undefined8 *)(iVar8 + 0xc0) = 0x2400000000008008;
      *(undefined8 *)(iVar8 + 200) = 0x43;
      *(undefined8 *)(iVar8 + 0xd0) = 0;
      *(long *)(iVar8 + 0xe0) =
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x4250) + 2) << 4);
      *(undefined8 *)(iVar8 + 0xf0) = 0;
      *(long *)(iVar8 + 0x100) =
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x4250) + 4) << 4) << 0x10;
      *(undefined8 *)(iVar8 + 0x110) = 0;
      *(long *)(iVar8 + 0x120) =
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x4250) + 2) << 4);
      *(undefined8 *)(iVar8 + 0x130) = 0;
      *(long *)(iVar8 + 0x140) =
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x4250) + 4) << 4) << 0x10;
    }
    puVar2 = *(undefined4 **)(param_1 + uVar9 * 4 + 0x18);
    if (bVar3) {
      *(undefined4 **)(param_1 + 0x54) = puVar2;
      *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfe | bVar1;
      return;
    }
    *puVar2 = 0x50000000;
    puVar2[1] = *(undefined4 *)
                 (*(int *)(iGpffff86b4 + 0x4250) +
                  (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x4250) + 10) * 4 + 0xc);
    puVar2[2] = 0;
    puVar2[3] = 0;
    lVar6 = __fixunssfdi(fVar10);
    *(ulong *)(puVar2 + 0x26) = lVar6 << 0x18 | 0x808080;
    *(long *)(puVar2 + 0x2a) =
         (long)aiStack_600[2] << 0x20 | (long)aiStack_600[0] | (long)aiStack_600[1] << 0x10;
    *(long *)(puVar2 + 0x2e) =
         (long)aiStack_600[6] << 0x20 | (long)aiStack_600[4] | (long)aiStack_600[5] << 0x10;
    *(long *)(puVar2 + 0x36) =
         (long)aiStack_600[10] << 0x20 | (long)aiStack_600[8] | (long)aiStack_600[9] << 0x10;
    *(long *)(puVar2 + 0x3a) =
         (long)aiStack_600[0xe] << 0x20 | (long)aiStack_600[0xc] | (long)aiStack_600[0xd] << 0x10;
    *(long *)(puVar2 + 0x3e) =
         (long)aiStack_600[0x12] << 0x20 | (long)aiStack_600[0x10] | (long)aiStack_600[0x11] << 0x10
    ;
    *(long *)(puVar2 + 0x42) =
         (long)aiStack_600[0x16] << 0x20 | (long)aiStack_600[0x14] | (long)aiStack_600[0x15] << 0x10
    ;
    *(long *)(puVar2 + 0x46) =
         (long)aiStack_600[0x1a] << 0x20 | (long)aiStack_600[0x18] | (long)aiStack_600[0x19] << 0x10
    ;
    *(long *)(puVar2 + 0x4a) =
         (long)aiStack_600[0x1e] << 0x20 | (long)aiStack_600[0x1c] | (long)aiStack_600[0x1d] << 0x10
    ;
    *(long *)(puVar2 + 0x4e) =
         (long)aiStack_600[0x22] << 0x20 | (long)aiStack_600[0x20] | (long)aiStack_600[0x21] << 0x10
    ;
    *(long *)(puVar2 + 0x52) =
         (long)aiStack_600[0x26] << 0x20 | (long)aiStack_600[0x24] | (long)aiStack_600[0x25] << 0x10
    ;
    *(undefined4 **)(param_1 + 0x54) = puVar2 + 0x54;
  }
  *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfe | bVar1;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005090a0  getPacket__7HitMarkFv
 * C++: HitMark::getPacket()
 * size: 0x138 bytes
 * --------------------------------------------------------------------------- */
int getPacket__7HitMarkFv(int param_1)

{
  int iVar1;
  
  (**(code **)(*(int *)(param_1 + 0x14) + 0x38))();
  if ((*(int *)(param_1 + 0x8c) == 0) &&
     (*(int *)(param_1 + 0x54) != *(int *)(param_1 + (*(byte *)(param_1 + 0x40) & 1) * 4 + 0x18))) {
    if (*(int *)(param_1 + 0x5c) == 3) {
      if (*(int *)(iGpffff86b8 + 0x3c) == 0xb) {
        *(undefined4 *)(iGpffff86b8 + 0x3c) = 0xb;
        return *(int *)(param_1 + (*(byte *)(param_1 + 0x40) & 1) * 4 + 0x18) + 0x10;
      }
      *(undefined4 *)(iGpffff86b8 + 0x3c) = 0xb;
    }
    iVar1 = *(int *)(param_1 + (*(byte *)(param_1 + 0x40) & 1) * 4 + 0x18);
  }
  else {
    iVar1 = 0;
  }
  return iVar1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b200  EndSet__7HitMarkFv
 * C++: HitMark::EndSet()
 * size: 0x30 bytes
 * --------------------------------------------------------------------------- */
void EndSet__7HitMarkFv(int param_1)

{
  (**(code **)(*(int *)(param_1 + 0x14) + 0x30))();
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b530  @24@getPacket__7HitMarkFv
 * C++: @24@getPacket__7HitMarkFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int _24_getPacket__7HitMarkFv(int param_1)

{
  int iVar1;
  
  iVar1 = param_1 + -0x18;
  (**(code **)(*(int *)(param_1 + -4) + 0x38))();
  if ((*(int *)(param_1 + 0x74) == 0) &&
     (*(int *)(param_1 + 0x3c) != *(int *)(iVar1 + (*(byte *)(param_1 + 0x28) & 1) * 4 + 0x18))) {
    if (*(int *)(param_1 + 0x44) == 3) {
      if (*(int *)(iGpffff86b8 + 0x3c) == 0xb) {
        *(undefined4 *)(iGpffff86b8 + 0x3c) = 0xb;
        return *(int *)(iVar1 + (*(byte *)(param_1 + 0x28) & 1) * 4 + 0x18) + 0x10;
      }
      *(undefined4 *)(iGpffff86b8 + 0x3c) = 0xb;
    }
    iVar1 = *(int *)(iVar1 + (*(byte *)(param_1 + 0x28) & 1) * 4 + 0x18);
  }
  else {
    iVar1 = 0;
  }
  return iVar1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b540  @24@__dt__7HitMarkFv
 * C++: @24@__dt__7HitMarkFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int * _24___dt__7HitMarkFv(int *param_1,short param_2)

{
  int *piVar1;
  
  piVar1 = param_1 + -6;
  if (piVar1 != (int *)0x0) {
    param_1[-1] = 0x40a300;
    param_1[4] = 0x40a310;
    param_1[7] = 0x40a320;
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
 * JP: 0x0054b550  @44@__dt__7HitMarkFv
 * C++: @44@__dt__7HitMarkFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int _44___dt__7HitMarkFv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x2c;
  if (iVar1 != 0) {
    *(undefined4 *)(param_1 + -0x18) = 0x40a300;
    *(undefined4 *)(param_1 + -4) = 0x40a310;
    *(undefined4 *)(param_1 + 8) = 0x40a320;
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

