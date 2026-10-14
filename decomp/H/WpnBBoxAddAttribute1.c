/* decomp/H/WpnBBoxAddAttribute1.c — cleaned Ghidra output (SH2JP_BATTLE.BIN, JP Furokuban, base 0x00430a00).
 * 8 function(s). Types: see types.h. Names/gp globals resolved from symbols/SLPM_602.19.syms. */
#include "types.h"

/* ---------------------------------------------------------------------------
 * JP: 0x00527600  __ct__20WpnBBoxAddAttribute1Fiiiii
 * C++: WpnBBoxAddAttribute1::__ct(int, int, int, int, int)
 * size: 0x1fc bytes
 * --------------------------------------------------------------------------- */
int __ct__20WpnBBoxAddAttribute1Fiiiii
              (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
              undefined4 param_5,undefined4 param_6)

{
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  int iVar1;
  undefined4 *puVar2;
  
  __ct__6BtlEffFii(param_1,param_2,param_3);
  *(undefined4 *)(param_1 + 0x14) = 0x409d90;
  *(undefined4 *)(param_1 + 0x28) = 0x409da0;
  *(undefined4 *)(param_1 + 0x34) = 0x409db0;
  *(undefined4 *)(param_1 + 0x70) = in_zero_lo;
  *(undefined4 *)(param_1 + 0x74) = in_zero_hi;
  *(undefined4 *)(param_1 + 0x78) = in_zero_udw;
  *(undefined4 *)(param_1 + 0x7c) = in_register_0000000c;
  puVar2 = (undefined4 *)(param_1 + 0x110);
  do {
    *puVar2 = in_zero_lo;
    puVar2[1] = in_zero_hi;
    puVar2[2] = in_zero_udw;
    puVar2[3] = in_register_0000000c;
    puVar2 = puVar2 + 4;
  } while (puVar2 != (undefined4 *)(param_1 + 0x210));
  *(undefined4 *)(param_1 + 0x40) = 0;
  *(undefined4 *)(param_1 + 0x44) = param_2;
  *(undefined4 *)(param_1 + 0x48) = param_3;
  *(undefined4 *)(param_1 + 0x4c) = 6;
  *(undefined4 *)(param_1 + 0x5c) = 0;
  *(undefined4 *)(param_1 + 0x60) = param_4;
  *(undefined4 *)(param_1 + 0x68) = param_5;
  *(undefined4 *)(param_1 + 100) = param_6;
  *(undefined4 *)(param_1 + 0x80) = 0;
  *(undefined4 *)(param_1 + 0x88) = 0;
  *(undefined4 *)(param_1 + 0x8c) = 0;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  *(undefined4 *)(param_1 + 0x18) = 0;
  for (iVar1 = 0; iVar1 < 0x10; iVar1 = iVar1 + 1) {
    *(undefined2 *)(param_1 + iVar1 * 2 + 0x90) = 0;
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
 * JP: 0x00527800  __dt__20WpnBBoxAddAttribute1Fv
 * C++: WpnBBoxAddAttribute1::__dt()
 * size: 0x154 bytes
 * --------------------------------------------------------------------------- */
int __dt__20WpnBBoxAddAttribute1Fv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x14) = 0x409d90;
    *(undefined4 *)(param_1 + 0x28) = 0x409da0;
    *(undefined4 *)(param_1 + 0x34) = 0x409db0;
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
 * JP: 0x00527960  Destruct__20WpnBBoxAddAttribute1Fv
 * C++: WpnBBoxAddAttribute1::Destruct()
 * size: 0xcc bytes
 * --------------------------------------------------------------------------- */
void Destruct__20WpnBBoxAddAttribute1Fv(int param_1)

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
 * JP: 0x00527a30  Polling__20WpnBBoxAddAttribute1Fv
 * C++: WpnBBoxAddAttribute1::Polling()
 * size: 0xb0c bytes
 * --------------------------------------------------------------------------- */
undefined8 Polling__20WpnBBoxAddAttribute1Fv(int param_1)

{
  short sVar1;
  undefined8 uVar2;
  byte *pbVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined1 (*pauVar8) [16];
  int iVar9;
  float fVar10;
  undefined1 in_vf0 [16];
  undefined1 auVar11 [16];
  undefined1 auVar12 [16];
  undefined1 auVar13 [16];
  float fStack_e0;
  float fStack_dc;
  float fStack_d8;
  float fStack_d0;
  float fStack_cc;
  float fStack_c8;
  float afStack_c0 [32];
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [16];
  undefined1 auStack_20 [16];
  undefined1 auStack_10 [16];
  
  fVar10 = *(float *)(iGpffff86b4 + 0x38);
  if ((*(byte *)(iGpffff86b4 + 0x24) & 1) != 0) {
    fVar10 = 0.0;
  }
  *(float *)(param_1 + 0x8c) = *(float *)(param_1 + 0x8c) + fVar10 * 6.2831855 * 0.75;
  if (3.1415927 <= *(float *)(param_1 + 0x8c)) {
    *(float *)(param_1 + 0x8c) = *(float *)(param_1 + 0x8c) - 6.2831855;
  }
  if (((*(int *)(param_1 + 0x5c) != 1) && (*(int *)(param_1 + 0x5c) == 0)) &&
     (*(float *)(param_1 + 0x80) = *(float *)(param_1 + 0x80) + fVar10 * 2.0,
     1.0 <= *(float *)(param_1 + 0x80))) {
    *(undefined4 *)(param_1 + 0x80) = 0x3f800000;
    *(undefined4 *)(param_1 + 0x5c) = 1;
  }
  auVar11 = _vmr32(in_vf0);
  auVar12 = _vmr32(auVar11);
  auVar13 = _vmr32(auVar12);
  _sqc2(in_vf0);
  _sqc2(auVar11);
  _sqc2(auVar12);
  _sqc2(auVar13);
  if (*(int *)(param_1 + 0x68) == 0) {
    pbVar3 = (byte *)(*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 +
                                                0x144) + 0x52c) + 0xe4) +
                     *(int *)(param_1 + 100) * 0x110);
    pauVar8 = (undefined1 (*) [16])
              (*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x144) +
                                0x52c) + 0x30) + (uint)*pbVar3 * 0x1f0 + (bGpffff8340 & 1) * 0x40);
    auStack_40 = *pauVar8;
    auStack_30 = pauVar8[1];
    auStack_20 = pauVar8[2];
    auStack_10 = pauVar8[3];
  }
  else {
    pbVar3 = (byte *)(*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 +
                                                0x144) + 0x530) + 0xe4) +
                     *(int *)(param_1 + 100) * 0x110);
    pauVar8 = (undefined1 (*) [16])
              (*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x144) +
                                0x530) + 0x30) + (uint)*pbVar3 * 0x1f0 + (bGpffff8340 & 1) * 0x40);
    auStack_40 = *pauVar8;
    auStack_30 = pauVar8[1];
    auStack_20 = pauVar8[2];
    auStack_10 = pauVar8[3];
  }
  fStack_d0 = 4096.0;
  fStack_cc = 4096.0;
  fStack_c8 = 4096.0;
  fStack_e0 = -4096.0;
  fStack_dc = -4096.0;
  fStack_d8 = -4096.0;
  RotTransVector(afStack_c0,pbVar3 + 0x10,auStack_40,8);
  for (iVar9 = 0; iVar9 < 8; iVar9 = iVar9 + 1) {
    if (afStack_c0[iVar9 * 4] < fStack_d0) {
      fStack_d0 = afStack_c0[iVar9 * 4];
    }
    if (afStack_c0[iVar9 * 4 + 1] < fStack_cc) {
      fStack_cc = afStack_c0[iVar9 * 4 + 1];
    }
    if (afStack_c0[iVar9 * 4 + 2] < fStack_c8) {
      fStack_c8 = afStack_c0[iVar9 * 4 + 2];
    }
    if (fStack_e0 < afStack_c0[iVar9 * 4]) {
      fStack_e0 = afStack_c0[iVar9 * 4];
    }
    if (fStack_dc < afStack_c0[iVar9 * 4 + 1]) {
      fStack_dc = afStack_c0[iVar9 * 4 + 1];
    }
    if (fStack_d8 < afStack_c0[iVar9 * 4 + 2]) {
      fStack_d8 = afStack_c0[iVar9 * 4 + 2];
    }
  }
  *(float *)(param_1 + 0x70) = (fStack_d0 + fStack_e0) / 2.0;
  *(float *)(param_1 + 0x74) = (fStack_cc + fStack_dc) / 2.0;
  *(float *)(param_1 + 0x78) = (fStack_c8 + fStack_d8) / 2.0;
  *(undefined4 *)(param_1 + 0x7c) = 0x3f800000;
  *(float *)(param_1 + 0x84) =
       *(float *)(param_1 + 0x80) *
       (((fStack_d8 - fStack_c8) / 2.0 +
        (fStack_e0 - fStack_d0) / 2.0 + (fStack_dc - fStack_cc) / 2.0) / 3.0) * 2.6666667;
  *(float *)(param_1 + 0x88) = *(float *)(param_1 + 0x88) + fVar10;
  for (iVar9 = 0; iVar9 < 0x10; iVar9 = iVar9 + 1) {
    sVar1 = *(short *)(param_1 + iVar9 * 2 + 0x90);
    if (sVar1 == 1) {
      iVar4 = param_1 + iVar9 * 4;
      *(float *)(iVar4 + 0xd0) = *(float *)(iVar4 + 0xd0) + fVar10;
      iVar4 = param_1 + iVar9 * 0x10;
      *(float *)(iVar4 + 0x114) = *(float *)(iVar4 + 0x114) - fVar10 * 2.0;
      if (*(float *)(param_1 + iVar9 * 4 + 0xd0) < 0.6666667) {
        *(undefined4 *)(param_1 + iVar9 * 4 + 0x250) = 0x43000000;
      }
      else {
        *(float *)(param_1 + iVar9 * 4 + 0x250) =
             ((1.0 - *(float *)(param_1 + iVar9 * 4 + 0xd0)) / 0.33333334) * 128.0;
      }
      if ((1.0 <= *(float *)(param_1 + iVar9 * 4 + 0xd0)) &&
         (*(undefined2 *)(param_1 + iVar9 * 2 + 0x90) = 0, 0.06666667 <= *(float *)(param_1 + 0x88))
         ) {
        *(undefined2 *)(param_1 + iVar9 * 2 + 0x90) = 1;
        *(undefined4 *)(param_1 + iVar9 * 4 + 0xd0) = 0;
        iVar4 = param_1 + iVar9 * 0x10;
        uVar2 = *(undefined8 *)(param_1 + 0x70);
        uVar6 = *(undefined4 *)(param_1 + 0x78);
        uVar7 = *(undefined4 *)(param_1 + 0x7c);
        *(int *)(iVar4 + 0x110) = (int)uVar2;
        *(int *)(iVar4 + 0x114) = (int)((ulong)uVar2 >> 0x20);
        *(undefined4 *)(iVar4 + 0x118) = uVar6;
        *(undefined4 *)(iVar4 + 0x11c) = uVar7;
        iVar4 = rand();
        iVar5 = param_1 + iVar9 * 0x10;
        *(float *)(iVar5 + 0x110) =
             *(float *)(iVar5 + 0x110) +
             ((*(float *)(param_1 + 0x84) / 3.0) * ((float)iVar4 / 2.1474836e+09) -
             *(float *)(param_1 + 0x84) / 6.0);
        iVar4 = rand();
        iVar5 = param_1 + iVar9 * 0x10;
        *(float *)(iVar5 + 0x114) =
             *(float *)(iVar5 + 0x114) +
             ((*(float *)(param_1 + 0x84) / 3.0) * ((float)iVar4 / 2.1474836e+09) -
             *(float *)(param_1 + 0x84) / 6.0);
        iVar4 = rand();
        iVar5 = param_1 + iVar9 * 0x10;
        *(float *)(iVar5 + 0x118) =
             *(float *)(iVar5 + 0x118) +
             ((*(float *)(param_1 + 0x84) / 3.0) * ((float)iVar4 / 2.1474836e+09) -
             *(float *)(param_1 + 0x84) / 6.0);
        *(float *)(param_1 + iVar9 * 4 + 0x210) = *(float *)(param_1 + 0x84) * 0.375;
        *(undefined4 *)(param_1 + iVar9 * 4 + 0x250) = 0x3f800000;
        *(float *)(param_1 + 0x88) = *(float *)(param_1 + 0x88) - 0.06666667;
      }
    }
    else if ((sVar1 == 0) && (0.06666667 <= *(float *)(param_1 + 0x88))) {
      *(undefined2 *)(param_1 + iVar9 * 2 + 0x90) = 1;
      *(undefined4 *)(param_1 + iVar9 * 4 + 0xd0) = 0;
      iVar4 = param_1 + iVar9 * 0x10;
      uVar2 = *(undefined8 *)(param_1 + 0x70);
      uVar6 = *(undefined4 *)(param_1 + 0x78);
      uVar7 = *(undefined4 *)(param_1 + 0x7c);
      *(int *)(iVar4 + 0x110) = (int)uVar2;
      *(int *)(iVar4 + 0x114) = (int)((ulong)uVar2 >> 0x20);
      *(undefined4 *)(iVar4 + 0x118) = uVar6;
      *(undefined4 *)(iVar4 + 0x11c) = uVar7;
      iVar4 = rand();
      iVar5 = param_1 + iVar9 * 0x10;
      *(float *)(iVar5 + 0x110) =
           *(float *)(iVar5 + 0x110) +
           ((*(float *)(param_1 + 0x84) / 3.0) * ((float)iVar4 / 2.1474836e+09) -
           *(float *)(param_1 + 0x84) / 6.0);
      iVar4 = rand();
      iVar5 = param_1 + iVar9 * 0x10;
      *(float *)(iVar5 + 0x114) =
           *(float *)(iVar5 + 0x114) +
           ((*(float *)(param_1 + 0x84) / 3.0) * ((float)iVar4 / 2.1474836e+09) -
           *(float *)(param_1 + 0x84) / 6.0);
      iVar4 = rand();
      iVar5 = param_1 + iVar9 * 0x10;
      *(float *)(iVar5 + 0x118) =
           *(float *)(iVar5 + 0x118) +
           ((*(float *)(param_1 + 0x84) / 3.0) * ((float)iVar4 / 2.1474836e+09) -
           *(float *)(param_1 + 0x84) / 6.0);
      *(float *)(param_1 + iVar9 * 4 + 0x210) = *(float *)(param_1 + 0x84) * 0.375;
      *(undefined4 *)(param_1 + iVar9 * 4 + 0x250) = 0x3f800000;
      *(float *)(param_1 + 0x88) = *(float *)(param_1 + 0x88) - 0.06666667;
    }
  }
  return 0;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00528540  MakePacket__20WpnBBoxAddAttribute1Fv
 * C++: WpnBBoxAddAttribute1::MakePacket()
 * size: 0x13e0 bytes
 * --------------------------------------------------------------------------- */
/* WARNING: Removing unreachable block (ram,0x00529380) */
/* WARNING: Removing unreachable block (ram,0x005292c0) */
/* WARNING: Removing unreachable block (ram,0x00529440) */

void MakePacket__20WpnBBoxAddAttribute1Fv(int param_1)

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
  undefined8 extraout_v0_udw;
  undefined1 auVar6 [16];
  int iVar7;
  undefined8 in_v1_udw;
  undefined1 auVar8 [16];
  uint uVar9;
  int iVar10;
  float fVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  undefined1 auVar15 [16];
  undefined1 auVar16 [16];
  undefined1 auStack_a20 [16];
  undefined1 auStack_a10 [8];
  undefined4 uStack_a08;
  undefined4 uStack_a04;
  undefined8 uStack_a00;
  undefined4 uStack_9f8;
  undefined4 uStack_9f4;
  undefined8 uStack_9f0;
  undefined4 uStack_9e8;
  undefined4 uStack_9e4;
  undefined8 uStack_9e0;
  undefined4 uStack_9d8;
  undefined4 uStack_9d4;
  undefined4 uStack_9d0;
  undefined4 uStack_9cc;
  undefined4 uStack_9c8;
  undefined4 uStack_9c4;
  undefined4 uStack_9c0;
  undefined4 uStack_9bc;
  undefined4 uStack_9b8;
  undefined4 uStack_9b4;
  undefined4 uStack_9b0;
  undefined4 uStack_9ac;
  undefined4 uStack_9a8;
  undefined4 uStack_9a4;
  undefined4 uStack_9a0;
  undefined4 uStack_99c;
  undefined4 uStack_998;
  undefined4 uStack_994;
  int aiStack_990 [288];
  float afStack_510 [272];
  float fStack_d0;
  float fStack_cc;
  float fStack_c8;
  float afStack_c0 [16];
  int aiStack_80 [7];
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
  
  uStack_9a0 = 0xbf800000;
  uStack_99c = 0xbf800000;
  uStack_998 = 0;
  uStack_994 = 0x3f800000;
  uStack_40 = 0xbf800000;
  uStack_3c = 0xbf800000;
  uStack_38 = 0;
  uStack_34 = 0x3f800000;
  uStack_9b0 = 0xbf800000;
  uStack_9ac = 0x3f800000;
  uStack_9a8 = 0;
  uStack_9a4 = 0x3f800000;
  uStack_30 = 0xbf800000;
  uStack_2c = 0x3f800000;
  uStack_28 = 0;
  uStack_24 = 0x3f800000;
  uStack_9c0 = 0x3f800000;
  uStack_9bc = 0xbf800000;
  uStack_9b8 = 0;
  uStack_9b4 = 0x3f800000;
  uStack_20 = 0x3f800000;
  uStack_1c = 0xbf800000;
  uStack_18 = 0;
  uStack_14 = 0x3f800000;
  uStack_9d0 = 0x3f800000;
  uStack_9cc = 0x3f800000;
  uStack_9c8 = 0;
  uStack_9c4 = 0x3f800000;
  uStack_10 = 0x3f800000;
  uStack_c = 0x3f800000;
  uStack_8 = 0;
  uStack_4 = 0x3f800000;
  __ct__6MatrixFRC6Matrix(aiStack_80,iGpffff8598 + 0x240);
  uStack_50 = 0;
  uStack_4c = 0;
  uStack_48 = 0;
  uStack_44 = 0x3f800000;
  RotTransVector(afStack_c0,&uStack_40,aiStack_80,4);
  auVar15 = _lqc2(*(undefined1 (*) [16])(*(int *)(iGpffff86b4 + 0x4324) + 0x30));
  auVar16 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x70));
  auVar15 = _vsub(auVar15,auVar16);
  auStack_a20 = _sqc2(auVar15);
  __ct__7FVectorFRC7FVector(&fStack_d0,auStack_a20);
  Normalize__7FVectorFv(&fStack_d0);
  __amu__7FVectorFf(*(float *)(param_1 + 0x84) / 3.0,&fStack_d0);
  for (iVar7 = 0; iVar7 < 4; iVar7 = iVar7 + 1) {
    afStack_510[iVar7 * 4] =
         fStack_d0 +
         *(float *)(param_1 + 0x70) + *(float *)(param_1 + 0x84) * afStack_c0[iVar7 * 4] * 1.75;
    afStack_510[iVar7 * 4 + 1] =
         fStack_cc +
         *(float *)(param_1 + 0x74) + *(float *)(param_1 + 0x84) * afStack_c0[iVar7 * 4 + 1] * 1.75;
    afStack_510[iVar7 * 4 + 2] =
         fStack_c8 +
         *(float *)(param_1 + 0x78) + *(float *)(param_1 + 0x84) * afStack_c0[iVar7 * 4 + 2] * 1.75;
    afStack_510[iVar7 * 4 + 3] = 1.0;
  }
  for (iVar7 = 0; iVar7 < 0x10; iVar7 = iVar7 + 1) {
    for (iVar10 = 0; iVar10 < 4; iVar10 = iVar10 + 1) {
      afStack_510[(iVar10 + iVar7 * 4 + 4) * 4] =
           *(float *)(param_1 + iVar7 * 0x10 + 0x110) +
           *(float *)(param_1 + iVar7 * 4 + 0x210) * afStack_c0[iVar10 * 4];
      afStack_510[(iVar10 + iVar7 * 4 + 4) * 4 + 1] =
           *(float *)(param_1 + iVar7 * 0x10 + 0x114) +
           *(float *)(param_1 + iVar7 * 4 + 0x210) * afStack_c0[iVar10 * 4 + 1];
      afStack_510[(iVar10 + iVar7 * 4 + 4) * 4 + 2] =
           *(float *)(param_1 + iVar7 * 0x10 + 0x118) +
           *(float *)(param_1 + iVar7 * 4 + 0x210) * afStack_c0[iVar10 * 4 + 2];
      afStack_510[(iVar10 + iVar7 * 4 + 4) * 4 + 3] = 1.0;
    }
  }
  GetViewScreenMatrix__9GsxCameraFv(auStack_a10,iGpffff8598);
  aiStack_80[0] = auStack_a10._0_4_;
  aiStack_80[1] = auStack_a10._4_4_;
  aiStack_80[2] = uStack_a08;
  aiStack_80[3] = uStack_a04;
  aiStack_80[4] = (int)uStack_a00;
  aiStack_80[5] = (int)((ulong)uStack_a00 >> 0x20);
  aiStack_80[6] = uStack_9f8;
  uStack_64 = uStack_9f4;
  uStack_60 = (int)uStack_9f0;
  uStack_5c = (int)((ulong)uStack_9f0 >> 0x20);
  uStack_58 = uStack_9e8;
  uStack_54 = uStack_9e4;
  uStack_50 = (int)uStack_9e0;
  uStack_4c = (int)((ulong)uStack_9e0 >> 0x20);
  uStack_48 = uStack_9d8;
  uStack_44 = uStack_9d4;
  for (iVar7 = 0; iVar7 < 4; iVar7 = iVar7 + 1) {
    aiStack_990[iVar7 * 4 + 0x110] = aiStack_80[iVar7 * 4];
    aiStack_990[iVar7 * 4 + 0x111] = aiStack_80[iVar7 * 4 + 1];
    aiStack_990[iVar7 * 4 + 0x112] = aiStack_80[iVar7 * 4 + 2];
    aiStack_990[iVar7 * 4 + 0x113] = aiStack_80[iVar7 * 4 + 3];
  }
  sceVu0RotTransPersN(aiStack_990,aiStack_990 + 0x110,afStack_510,0x44,0);
  bVar3 = false;
  iVar7 = 0;
  for (iVar10 = 0; iVar10 < 0x44; iVar10 = iVar10 + 1) {
    if (iVar10 < 4) {
      if (((aiStack_990[iVar10 * 4] < 0) || (0x10000 < aiStack_990[iVar10 * 4])) ||
         ((aiStack_990[iVar10 * 4 + 1] < 0 ||
          ((0x10000 < aiStack_990[iVar10 * 4 + 1] || (aiStack_990[iVar10 * 4 + 2] < 0)))))) {
        bVar3 = true;
      }
      aiStack_990[iVar10 * 4 + 2] = (int)((float)aiStack_990[iVar10 * 4 + 2] / 16.0);
      if (iVar10 < 4) {
        iVar7 = iVar7 + aiStack_990[iVar10 * 4 + 2];
      }
    }
    else {
      uVar9 = iVar10 - 4U & 3;
      if (((int)(iVar10 - 4U) < 0) && (uVar9 != 0)) {
        uVar9 = uVar9 - 4;
      }
      if (uVar9 == 0) {
        iVar12 = iVar10 + -4;
        if (iVar12 < 0) {
          iVar12 = iVar10 + -1;
        }
        *(undefined2 *)(param_1 + (iVar12 >> 2) * 2 + 0xb0) = 0;
      }
      if ((((aiStack_990[iVar10 * 4] < 0) || (0x10000 < aiStack_990[iVar10 * 4])) ||
          (aiStack_990[iVar10 * 4 + 1] < 0)) ||
         ((0x10000 < aiStack_990[iVar10 * 4 + 1] || (aiStack_990[iVar10 * 4 + 2] < 0)))) {
        iVar12 = iVar10 + -4;
        if (iVar12 < 0) {
          iVar12 = iVar10 + -1;
        }
        *(undefined2 *)(param_1 + (iVar12 >> 2) * 2 + 0xb0) = 1;
      }
      aiStack_990[iVar10 * 4 + 2] = (int)((float)aiStack_990[iVar10 * 4 + 2] / 16.0);
    }
  }
  if (iVar7 < 0) {
    iVar7 = iVar7 + 3;
  }
  *(int *)(param_1 + 0x50) = iVar7 >> 2;
  bVar1 = (*(byte *)(param_1 + 0x40) & 1) == 0;
  uVar9 = (uint)bVar1;
  if (*(int *)(param_1 + uVar9 * 4 + 0x18) == 0) {
    uVar4 = __nwa__FUi(0x650);
    *(undefined4 *)(param_1 + uVar9 * 4 + 0x18) = uVar4;
    iVar7 = *(int *)(param_1 + uVar9 * 4 + 0x18);
    *(undefined4 *)(iVar7 + 0x10) = 0x1000000d;
    *(undefined4 *)(iVar7 + 0x14) = 0;
    *(undefined4 *)(iVar7 + 0x18) = 0;
    *(undefined4 *)(iVar7 + 0x1c) = 0x5000000d;
    *(undefined8 *)(iVar7 + 0x20) = 0x6000000000000001;
    *(undefined8 *)(iVar7 + 0x28) = 0xe6e8ee;
    *(undefined8 *)(iVar7 + 0x30) = 1;
    *(undefined8 *)(iVar7 + 0x38) = 0x3f;
    *(undefined8 *)(iVar7 + 0x40) = 0x60;
    *(undefined8 *)(iVar7 + 0x48) = 0x14;
    *(undefined8 *)(iVar7 + 0x50) = 5;
    *(undefined8 *)(iVar7 + 0x58) = 0;
    *(undefined8 *)(iVar7 + 0x60) = 0x53001;
    *(undefined8 *)(iVar7 + 0x68) = 0x47;
    uVar5 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x42ec),1);
    *(undefined8 *)(iVar7 + 0x70) = uVar5;
    *(undefined8 *)(iVar7 + 0x78) = 0;
    *(undefined8 *)(iVar7 + 0x80) = 0x48;
    *(undefined8 *)(iVar7 + 0x88) = 0x42;
    auVar6._8_8_ = extraout_v0_udw;
    auVar6._0_8_ = 0xa400000000008001;
    auVar15._4_4_ = in_zero_hi;
    auVar15._0_4_ = in_zero_lo;
    auVar15._8_4_ = in_zero_udw;
    auVar15._12_4_ = in_register_0000000c;
    auVar15 = _pcpyld(auVar15,auVar6);
    *(long *)(iVar7 + 0x90) = auVar15._0_8_;
    *(undefined8 *)(iVar7 + 0x98) = 0x4343c3c310;
    *(undefined8 *)(iVar7 + 0xa0) = 0x154;
    *(undefined8 *)(iVar7 + 0xb0) = 0;
    *(long *)(iVar7 + 0xc0) =
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42ec) + 4) << 4) << 0x10;
    *(long *)(iVar7 + 0xd0) =
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42ec) + 2) << 4);
    *(long *)(iVar7 + 0xe0) =
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42ec) + 2) << 4) |
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42ec) + 4) << 4) << 0x10;
    *(undefined4 *)(iVar7 + 0xf0) = 0x50000000;
    *(undefined4 *)(iVar7 + 0xf4) =
         *(undefined4 *)
          (*(int *)(iGpffff86b4 + 0x42f0) +
           (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f0) + 10) * 4 + 0xc);
    *(undefined4 *)(iVar7 + 0xf8) = 0;
    *(undefined4 *)(iVar7 + 0xfc) = 0;
    *(undefined4 *)(iVar7 + 0x100) = 0x60000054;
    *(undefined4 *)(iVar7 + 0x104) = 0;
    *(undefined4 *)(iVar7 + 0x108) = 0;
    *(undefined4 *)(iVar7 + 0x10c) = 0x50000054;
    *(undefined8 *)(iVar7 + 0x110) = 0x2000000000000001;
    *(undefined8 *)(iVar7 + 0x118) = 0x6e;
    *(undefined8 *)(iVar7 + 0x120) = 1;
    *(undefined8 *)(iVar7 + 0x128) = 0x3f;
    uVar5 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x42f0),1);
    *(undefined8 *)(iVar7 + 0x130) = uVar5;
    *(undefined8 *)(iVar7 + 0x138) = 0;
    auVar8._8_8_ = in_v1_udw;
    auVar8._0_8_ = 0xa400000000008010;
    auVar16._4_4_ = in_zero_hi;
    auVar16._0_4_ = in_zero_lo;
    auVar16._8_4_ = in_zero_udw;
    auVar16._12_4_ = in_register_0000000c;
    auVar15 = _pcpyld(auVar16,auVar8);
    *(long *)(iVar7 + 0x140) = auVar15._0_8_;
    *(undefined8 *)(iVar7 + 0x148) = 0x4343c3c310;
    for (iVar10 = 0; iVar10 < 0x10; iVar10 = iVar10 + 1) {
      *(undefined8 *)(iVar7 + (iVar10 * 5 + 0x15) * 0x10) = 0x154;
      *(long *)(iVar7 + (iVar10 * 5 + 0x16) * 0x10) =
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f0) + 2) << 2) |
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f0) + 4) << 2) << 0x10;
      *(long *)(iVar7 + (iVar10 * 5 + 0x17) * 0x10) =
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f0) + 2) << 2) |
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f0) + 4) * 0xc) << 0x10;
      *(long *)(iVar7 + (iVar10 * 5 + 0x18) * 0x10) =
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f0) + 4) << 2) << 0x10 |
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f0) + 2) * 0xc);
      *(long *)(iVar7 + (iVar10 * 5 + 0x19) * 0x10) =
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f0) + 2) * 0xc) |
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f0) + 4) * 0xc) << 0x10;
    }
  }
  puVar2 = *(undefined4 **)(param_1 + uVar9 * 4 + 0x18);
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
                 (*(int *)(iGpffff86b4 + 0x42ec) +
                  (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42ec) + 10) * 4 + 0xc);
    puVar2[2] = 0;
    puVar2[3] = 0;
    iVar10 = (int)(*(float *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x144) +
                             0x4e4) *
                   *(float *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x144) +
                             0x4ec) * 128.0);
    fVar11 = (float)sinf(*(undefined4 *)(param_1 + 0x8c));
    fVar11 = (fVar11 + 1.0) / 2.0;
    iVar12 = (int)((float)*(byte *)(*(int *)(param_1 + 0x60) * 0xc + 0x652b64) +
                  fVar11 * (float)(int)((uint)*(byte *)(*(int *)(param_1 + 0x60) * 0xc + 0x652b68) -
                                       (uint)*(byte *)(*(int *)(param_1 + 0x60) * 0xc + 0x652b64)));
    iVar13 = (int)((float)*(byte *)(*(int *)(param_1 + 0x60) * 0xc + 0x652b65) +
                  fVar11 * (float)(int)((uint)*(byte *)(*(int *)(param_1 + 0x60) * 0xc + 0x652b69) -
                                       (uint)*(byte *)(*(int *)(param_1 + 0x60) * 0xc + 0x652b65)));
    iVar14 = (int)((float)*(byte *)(*(int *)(param_1 + 0x60) * 0xc + 0x652b66) +
                  fVar11 * (float)(int)((uint)*(byte *)(*(int *)(param_1 + 0x60) * 0xc + 0x652b6a) -
                                       (uint)*(byte *)(*(int *)(param_1 + 0x60) * 0xc + 0x652b66)));
    *(ulong *)(puVar2 + 0x2a) =
         (long)iVar10 << 0x18 | (long)iVar14 << 0x10 | (long)iVar12 | (long)iVar13 << 8 |
         0x100000000;
    *(long *)(puVar2 + 0x2e) =
         (long)aiStack_990[2] << 0x20 | (long)aiStack_990[0] | (long)aiStack_990[1] << 0x10;
    *(long *)(puVar2 + 0x32) =
         (long)aiStack_990[6] << 0x20 | (long)aiStack_990[4] | (long)aiStack_990[5] << 0x10;
    *(long *)(puVar2 + 0x36) =
         (long)aiStack_990[10] << 0x20 | (long)aiStack_990[8] | (long)aiStack_990[9] << 0x10;
    *(long *)(puVar2 + 0x3a) =
         (long)aiStack_990[0xe] << 0x20 | (long)aiStack_990[0xc] | (long)aiStack_990[0xd] << 0x10;
    for (iVar7 = 0; iVar7 < 0x10; iVar7 = iVar7 + 1) {
      if ((*(short *)(param_1 + iVar7 * 2 + 0x90) == 0) ||
         (*(short *)(param_1 + iVar7 * 2 + 0xb0) != 0)) {
        *(undefined8 *)(puVar2 + (iVar7 * 5 + 0x16) * 4 + 2) = 0x71006f00;
        *(undefined8 *)(puVar2 + (iVar7 * 5 + 0x17) * 4 + 2) = 0x71006f00;
        *(undefined8 *)(puVar2 + (iVar7 * 5 + 0x18) * 4 + 2) = 0x71006f00;
        *(undefined8 *)(puVar2 + (iVar7 * 5 + 0x19) * 4 + 2) = 0x71006f00;
      }
      else {
        *(ulong *)(puVar2 + (iVar7 * 5 + 0x15) * 4 + 2) =
             (long)(int)(((float)iVar10 * *(float *)(param_1 + iVar7 * 4 + 0x250)) / 128.0) << 0x18
             | (long)iVar14 << 0x10 | (long)iVar12 | (long)iVar13 << 8 | 0x100000000;
        *(long *)(puVar2 + (iVar7 * 5 + 0x16) * 4 + 2) =
             (long)aiStack_990[(iVar7 * 4 + 4) * 4 + 2] << 0x20 |
             (long)aiStack_990[(iVar7 * 4 + 4) * 4] |
             (long)aiStack_990[(iVar7 * 4 + 4) * 4 + 1] << 0x10;
        *(long *)(puVar2 + (iVar7 * 5 + 0x17) * 4 + 2) =
             (long)aiStack_990[(iVar7 * 4 + 5) * 4 + 2] << 0x20 |
             (long)aiStack_990[(iVar7 * 4 + 5) * 4] |
             (long)aiStack_990[(iVar7 * 4 + 5) * 4 + 1] << 0x10;
        *(long *)(puVar2 + (iVar7 * 5 + 0x18) * 4 + 2) =
             (long)aiStack_990[(iVar7 * 4 + 6) * 4 + 2] << 0x20 |
             (long)aiStack_990[(iVar7 * 4 + 6) * 4] |
             (long)aiStack_990[(iVar7 * 4 + 6) * 4 + 1] << 0x10;
        *(long *)(puVar2 + (iVar7 * 5 + 0x19) * 4 + 2) =
             (long)aiStack_990[(iVar7 * 4 + 7) * 4 + 2] << 0x20 |
             (long)aiStack_990[(iVar7 * 4 + 7) * 4] |
             (long)aiStack_990[(iVar7 * 4 + 7) * 4 + 1] << 0x10;
      }
    }
    *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfe | bVar1;
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054ae60  EndSet__20WpnBBoxAddAttribute1Fv
 * C++: WpnBBoxAddAttribute1::EndSet()
 * size: 0x10 bytes
 * --------------------------------------------------------------------------- */
void EndSet__20WpnBBoxAddAttribute1Fv(void)

{
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b7d0  @24@__dt__20WpnBBoxAddAttribute1Fv
 * C++: @24@__dt__20WpnBBoxAddAttribute1Fv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int * _24___dt__20WpnBBoxAddAttribute1Fv(int *param_1,short param_2)

{
  int *piVar1;
  
  piVar1 = param_1 + -6;
  if (piVar1 != (int *)0x0) {
    param_1[-1] = 0x409d90;
    param_1[4] = 0x409da0;
    param_1[7] = 0x409db0;
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
 * JP: 0x0054b7e0  @44@__dt__20WpnBBoxAddAttribute1Fv
 * C++: @44@__dt__20WpnBBoxAddAttribute1Fv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int _44___dt__20WpnBBoxAddAttribute1Fv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x2c;
  if (iVar1 != 0) {
    *(undefined4 *)(param_1 + -0x18) = 0x409d90;
    *(undefined4 *)(param_1 + -4) = 0x409da0;
    *(undefined4 *)(param_1 + 8) = 0x409db0;
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

