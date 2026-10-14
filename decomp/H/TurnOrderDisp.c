/* decomp/H/TurnOrderDisp.c — cleaned Ghidra output (SH2JP_BATTLE.BIN, JP Furokuban, base 0x00430a00).
 * 12 function(s). Types: see types.h. Names/gp globals resolved from symbols/SLPM_602.19.syms. */
#include "types.h"

/* ---------------------------------------------------------------------------
 * JP: 0x004ea280  __ct__13TurnOrderDispFv
 * C++: TurnOrderDisp::__ct()
 * size: 0x1ac bytes
 * --------------------------------------------------------------------------- */
int __ct__13TurnOrderDispFv(int param_1)

{
  int iVar1;
  
  __ct__7CPolObjFv(param_1);
  __ct__8VIF1PrimFv(param_1 + 0x18);
  *(undefined4 *)(param_1 + 0x2c) = 0;
  *(undefined4 *)(param_1 + 0x30) = 0;
  *(undefined4 *)(param_1 + 0x34) = 0x4049f0;
  *(undefined4 *)(param_1 + 0x14) = 0x40a5b0;
  *(undefined4 *)(param_1 + 0x28) = 0x40a5c0;
  *(undefined4 *)(param_1 + 0x34) = 0x40a5d0;
  *(undefined4 *)(param_1 + 0x38) = 0;
  *(undefined4 *)(param_1 + 0x3c) = 0;
  *(undefined4 *)(param_1 + 0x40) = 0;
  *(undefined4 *)(param_1 + 0x44) = 0;
  *(undefined4 *)(param_1 + 0x60) = 0xc3000000;
  *(undefined4 *)(param_1 + 0x6c) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x68) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x48) = 0;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  *(undefined4 *)(param_1 + 0x18) = 0;
  *(undefined4 *)(param_1 + 0x54) = 0;
  *(undefined4 *)(param_1 + 0x50) = 0;
  *(undefined4 *)(param_1 + 0x4c) = 0;
  *(undefined4 *)(param_1 + 100) = 0;
  *(undefined4 *)(param_1 + 0x70) = 3;
  *(undefined4 *)(param_1 + 0x74) = 0;
  for (iVar1 = 0; iVar1 < 0x10; iVar1 = iVar1 + 1) {
    *(undefined1 *)(param_1 + iVar1 + 0x78) = 0xff;
    *(undefined1 *)(param_1 + iVar1 + 0x88) = 0;
    *(undefined2 *)(param_1 + iVar1 * 2 + 0xb8) = 0;
    *(undefined2 *)(param_1 + iVar1 * 2 + 0x98) = 0;
  }
  Entry__7CPollerFP7CPolObjib(iGpffff858c + 0x48,param_1,0x80,0);
  return param_1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x004ea430  __dt__13TurnOrderDispFv
 * C++: TurnOrderDisp::__dt()
 * size: 0x114 bytes
 * --------------------------------------------------------------------------- */
int __dt__13TurnOrderDispFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x14) = 0x40a5b0;
    *(undefined4 *)(param_1 + 0x28) = 0x40a5c0;
    *(undefined4 *)(param_1 + 0x34) = 0x40a5d0;
    if (*(int *)(param_1 + 0x18) != 0) {
      __dla__FPv(*(undefined4 *)(param_1 + 0x18));
    }
    if (*(int *)(param_1 + 0x1c) != 0) {
      __dla__FPv(*(undefined4 *)(param_1 + 0x1c));
    }
    if (param_1 != -0x2c) {
      *(undefined4 *)(param_1 + 0x34) = 0x4049f0;
    }
    __dt__8VIF1PrimFv(param_1 + 0x18,0);
    __dt__7CPolObjFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x004ea550  Destruct__13TurnOrderDispFv
 * C++: TurnOrderDisp::Destruct()
 * size: 0x48 bytes
 * --------------------------------------------------------------------------- */
void Destruct__13TurnOrderDispFv(int param_1)

{
  Dispose__7CPollerFP7CPolObj(iGpffff858c + 0x48,param_1);
  (**(code **)(*(int *)(param_1 + 0x34) + 0xc))();
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x004ea5a0  Polling__13TurnOrderDispFv
 * C++: TurnOrderDisp::Polling()
 * size: 0x3a0 bytes
 * --------------------------------------------------------------------------- */
undefined8 Polling__13TurnOrderDispFv(int param_1)

{
  int iVar1;
  float fStack_18;
  float fStack_14;
  
  fStack_14 = *(float *)(iGpffff86b4 + 0x38);
  if ((*(byte *)(iGpffff86b4 + 0x24) & 1) != 0) {
    fStack_14 = 0.0;
  }
  *(int *)(param_1 + 0x40) = *(int *)(param_1 + 0x40) + 1;
  *(float *)(param_1 + 0x48) = *(float *)(param_1 + 0x48) + fStack_14;
  *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) + fStack_14 * 6.2831855 * 2.0;
  if (3.1415927 <= *(float *)(param_1 + 0x74)) {
    *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 6.2831855;
  }
  if (*(float *)(param_1 + 0x6c) < *(float *)(param_1 + 0x68)) {
    fStack_18 = *(float *)(param_1 + 0x68) - *(float *)(param_1 + 0x6c);
    if (fStack_14 * 2.0 < fStack_18) {
      fStack_18 = fStack_14 * 2.0;
    }
    *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + fStack_18;
    *(uint *)(param_1 + 0x70) = *(uint *)(param_1 + 0x70) | 3;
  }
  else if (*(float *)(param_1 + 0x68) < *(float *)(param_1 + 0x6c)) {
    fStack_18 = *(float *)(param_1 + 0x68) - *(float *)(param_1 + 0x6c);
    if (fStack_18 < -fStack_14 * 2.0) {
      fStack_18 = -fStack_14 * 2.0;
    }
    *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + fStack_18;
    *(uint *)(param_1 + 0x70) = *(uint *)(param_1 + 0x70) | 3;
  }
  iVar1 = *(int *)(param_1 + 0x38);
  if (iVar1 == 3) {
    *(float *)(param_1 + 0x60) =
         *(float *)(param_1 + 0x60) -
         ((*(float *)(param_1 + 0x6c) * 128.0) / 8.0) * fStack_14 * 60.0;
    if (*(float *)(param_1 + 0x60) <= *(float *)(param_1 + 0x6c) * -128.0) {
      *(undefined4 *)(param_1 + 0x38) = 0;
      *(undefined4 *)(param_1 + 0x3c) = 0;
      *(float *)(param_1 + 0x60) = *(float *)(param_1 + 0x6c) * -128.0;
    }
    *(undefined4 *)(param_1 + 0x70) = 3;
  }
  else if ((iVar1 != 2) && (iVar1 == 1)) {
    *(float *)(param_1 + 0x60) =
         *(float *)(param_1 + 0x60) +
         ((*(float *)(param_1 + 0x6c) * 128.0) / 8.0) * fStack_14 * 60.0;
    if (0.0 <= *(float *)(param_1 + 0x60)) {
      *(undefined4 *)(param_1 + 0x38) = 2;
      *(undefined4 *)(param_1 + 0x3c) = 0;
      *(undefined4 *)(param_1 + 0x60) = 0;
    }
    *(undefined4 *)(param_1 + 0x70) = 3;
  }
  return 0;
}

/* ---------------------------------------------------------------------------
 * JP: 0x004ea940  MakePacket__13TurnOrderDispFv
 * C++: TurnOrderDisp::MakePacket()
 * size: 0x61a4 bytes
 * --------------------------------------------------------------------------- */
/* WARNING: Removing unreachable block (ram,0x004f004c) */
/* WARNING: Removing unreachable block (ram,0x004ecd2c) */
/* WARNING: Removing unreachable block (ram,0x004ecb98) */
/* WARNING: Removing unreachable block (ram,0x004eca00) */
/* WARNING: Removing unreachable block (ram,0x004ec8d0) */
/* WARNING: Removing unreachable block (ram,0x004ec178) */
/* WARNING: Removing unreachable block (ram,0x004ebe8c) */
/* WARNING: Removing unreachable block (ram,0x004ebdc4) */
/* WARNING: Removing unreachable block (ram,0x004eb950) */
/* WARNING: Removing unreachable block (ram,0x004eb820) */
/* WARNING: Removing unreachable block (ram,0x004eb8b8) */
/* WARNING: Removing unreachable block (ram,0x004eb0cc) */
/* WARNING: Removing unreachable block (ram,0x004eb130) */
/* WARNING: Removing unreachable block (ram,0x004ebe24) */
/* WARNING: Removing unreachable block (ram,0x004ebf04) */
/* WARNING: Removing unreachable block (ram,0x004ec1dc) */
/* WARNING: Removing unreachable block (ram,0x004ec968) */
/* WARNING: Removing unreachable block (ram,0x004eca5c) */
/* WARNING: Removing unreachable block (ram,0x004ecc64) */
/* WARNING: Removing unreachable block (ram,0x004ecd9c) */
/* WARNING: Removing unreachable block (ram,0x004f00b4) */
/* WARNING: Removing unreachable block (ram,0x004eb9ac) */

undefined4 MakePacket__13TurnOrderDispFv(int param_1)

{
  bool bVar1;
  short sVar2;
  undefined4 *puVar3;
  undefined1 auVar4 [16];
  undefined1 auVar5 [16];
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  undefined1 auVar8 [16];
  undefined1 auVar9 [16];
  float in_zero_lo;
  float in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  undefined4 uVar10;
  uint uVar11;
  int iVar12;
  ulong uVar13;
  long lVar14;
  long lVar15;
  undefined8 uVar16;
  undefined1 auVar17 [16];
  undefined8 *puVar18;
  undefined8 *puVar19;
  ulong *puVar20;
  int iVar21;
  byte *pbVar22;
  uint uVar23;
  int iVar24;
  int iVar25;
  int iVar26;
  float fVar27;
  int iVar28;
  float fVar29;
  undefined4 uVar30;
  undefined1 in_vf0 [16];
  undefined1 auVar31 [16];
  undefined1 auVar32 [16];
  undefined1 auVar33 [16];
  int iStack_400;
  uint uStack_3f0;
  int iStack_3e0;
  int iStack_3d0;
  int iStack_3c0;
  int iStack_3b0;
  int iStack_3a0;
  uint uStack_370;
  int iStack_360;
  int iStack_350;
  undefined1 auStack_280 [16];
  undefined4 uStack_270;
  undefined4 uStack_26c;
  undefined4 uStack_268;
  undefined4 uStack_264;
  undefined4 uStack_260;
  undefined4 uStack_25c;
  undefined4 uStack_258;
  undefined4 uStack_254;
  undefined4 uStack_250;
  undefined4 uStack_24c;
  undefined4 uStack_248;
  undefined4 uStack_244;
  float fStack_240;
  float fStack_23c;
  undefined4 uStack_238;
  undefined4 uStack_234;
  float fStack_230;
  float fStack_22c;
  undefined4 uStack_228;
  undefined4 uStack_224;
  float fStack_220;
  float fStack_21c;
  undefined4 uStack_218;
  undefined4 uStack_214;
  float fStack_210;
  float fStack_20c;
  undefined4 uStack_208;
  undefined4 uStack_204;
  float fStack_200;
  float fStack_1fc;
  undefined4 uStack_1f8;
  undefined4 uStack_1f4;
  float fStack_1f0;
  float fStack_1ec;
  undefined4 uStack_1e8;
  undefined4 uStack_1e4;
  float fStack_1e0;
  float fStack_1dc;
  undefined4 uStack_1d8;
  undefined4 uStack_1d4;
  float fStack_1d0;
  float fStack_1cc;
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
  undefined4 uStack_1a0;
  undefined4 uStack_19c;
  undefined4 uStack_198;
  undefined4 uStack_194;
  undefined4 uStack_190;
  undefined4 uStack_18c;
  undefined4 uStack_188;
  undefined4 uStack_184;
  float fStack_180;
  float fStack_17c;
  undefined4 uStack_178;
  undefined4 uStack_174;
  float fStack_170;
  float fStack_16c;
  undefined4 uStack_168;
  undefined4 uStack_164;
  float fStack_160;
  float fStack_15c;
  undefined4 uStack_158;
  undefined4 uStack_154;
  float fStack_150;
  float fStack_14c;
  undefined4 uStack_148;
  undefined4 uStack_144;
  undefined4 uStack_140;
  undefined4 uStack_13c;
  undefined4 uStack_138;
  undefined4 uStack_134;
  undefined4 uStack_130;
  undefined4 uStack_12c;
  undefined4 uStack_128;
  undefined4 uStack_124;
  undefined4 uStack_120;
  undefined4 uStack_11c;
  undefined4 uStack_118;
  undefined4 uStack_114;
  undefined4 uStack_110;
  undefined4 uStack_10c;
  undefined4 uStack_108;
  undefined4 uStack_104;
  float fStack_100;
  float fStack_fc;
  undefined4 uStack_f8;
  undefined4 uStack_f4;
  float fStack_f0;
  float fStack_ec;
  undefined4 uStack_e8;
  undefined4 uStack_e4;
  float fStack_e0;
  float fStack_dc;
  undefined4 uStack_d8;
  undefined4 uStack_d4;
  float fStack_d0;
  float fStack_cc;
  undefined4 uStack_c8;
  undefined4 uStack_c4;
  undefined1 auStack_c0 [16];
  undefined1 auStack_b0 [16];
  undefined1 auStack_a0 [16];
  undefined1 auStack_90 [16];
  float fStack_80;
  float fStack_7c;
  undefined4 uStack_78;
  undefined4 uStack_74;
  float fStack_70;
  float fStack_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  float fStack_60;
  float fStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  float fStack_50;
  float fStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined1 auStack_40 [8];
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined1 auStack_30 [8];
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined1 auStack_20 [8];
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined1 auStack_10 [8];
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  iVar25 = iGpffff86b4;
  uVar30 = *(undefined4 *)(iGpffff8598 + 0x378);
  pbVar22 = (byte *)(iGpffff86b4 + 0x3e14);
  for (iVar21 = 0; iVar21 < 0x10; iVar21 = iVar21 + 1) {
    if ((long)*(char *)(param_1 + iVar21 + 0x78) != (ulong)pbVar22[iVar21 * 8 + 2]) {
      *(byte *)(param_1 + iVar21 + 0x78) = pbVar22[iVar21 * 8 + 2];
      *(undefined4 *)(param_1 + 0x70) = 3;
    }
    if (*(byte *)(param_1 + iVar21 + 0x88) != pbVar22[iVar21 * 8 + 3]) {
      *(byte *)(param_1 + iVar21 + 0x88) = pbVar22[iVar21 * 8 + 3];
      *(undefined4 *)(param_1 + 0x70) = 3;
    }
    if (*(short *)(param_1 + iVar21 * 2 + 0x98) != *(short *)(pbVar22 + iVar21 * 8)) {
      *(undefined2 *)(param_1 + iVar21 * 2 + 0x98) = *(undefined2 *)(pbVar22 + iVar21 * 8);
      *(undefined4 *)(param_1 + 0x70) = 3;
    }
    if (*(short *)(param_1 + iVar21 * 2 + 0xb8) != *(short *)(pbVar22 + iVar21 * 8 + 4)) {
      *(undefined2 *)(param_1 + iVar21 * 2 + 0xb8) = *(undefined2 *)(pbVar22 + iVar21 * 8 + 4);
      *(undefined4 *)(param_1 + 0x70) = 3;
    }
  }
  bVar1 = (*(byte *)(iGpffff86b4 + (uint)*(byte *)(iGpffff86b4 + 0x3e16) * 0x4f0 + 0xb4) & 1) != 0;
  iStack_3a0 = 0;
  iStack_3b0 = 0;
  iStack_3c0 = 0;
  iStack_3d0 = 0;
  for (iVar21 = 1; iVar21 < 10; iVar21 = iVar21 + 1) {
    if ((*(byte *)(iGpffff86b4 + (uint)pbVar22[iVar21 * 8 + 2] * 0x4f0 + 0xb4) & 1) == 0) {
      if (*(short *)(iGpffff86b4 + (uint)pbVar22[iVar21 * 8 + 2] * 0x4f0 + 0x120) < 8) {
        iStack_3a0 = iStack_3a0 + 1;
      }
      else if (*(short *)(iGpffff86b4 + (uint)pbVar22[iVar21 * 8 + 2] * 0x4f0 + 0x120) < 0xb) {
        iStack_3b0 = iStack_3b0 + 1;
      }
      else {
        iStack_3c0 = iStack_3c0 + 1;
      }
    }
    else {
      iStack_3d0 = iStack_3d0 + 1;
    }
  }
  iVar21 = 0x52;
  if (iStack_3a0 != 0) {
    iVar21 = iStack_3a0 * 3 + 0x58;
  }
  if (iStack_3b0 != 0) {
    iVar21 = iVar21 + iStack_3b0 * 3 + 6;
  }
  if (iStack_3c0 != 0) {
    iVar21 = iVar21 + iStack_3c0 * 3 + 6;
  }
  if (iStack_3d0 != 0) {
    iVar21 = iVar21 + iStack_3d0 * 3 + 6;
  }
  iStack_3e0 = 0;
  uStack_3f0 = 0;
  uVar23 = 0;
  for (uVar11 = 0; (int)uVar11 < 10; uVar11 = uVar11 + 1) {
    if (((((uint)*(ushort *)(iGpffff86b4 + 0x32) & 1 << (pbVar22[uVar11 * 8 + 2] & 0x1f)) != 0) &&
        (*(byte *)(iGpffff86b4 + 0x3e16) != pbVar22[uVar11 * 8 + 2])) &&
       ((uVar23 & 1 << (pbVar22[uVar11 * 8 + 2] & 0x1f)) == 0)) {
      iStack_3e0 = iStack_3e0 + 1;
      uStack_3f0 = uStack_3f0 | 1 << (uVar11 & 0x1f);
      uVar23 = uVar23 | 1 << (pbVar22[uVar11 * 8 + 2] & 0x1f);
    }
  }
  if (iStack_3e0 != 0) {
    iVar21 = iVar21 + (iStack_3e0 + 1) * 3;
  }
  iStack_400 = 0;
  for (uVar23 = 0; (int)uVar23 < 0xc; uVar23 = uVar23 + 1) {
    if ((*(uint *)(param_1 + 100) & 3 << ((uVar23 & 0xf) << 1)) != 0) {
      for (iVar24 = 1; iVar24 < 10; iVar24 = iVar24 + 1) {
        if (uVar23 == pbVar22[iVar24 * 8 + 2]) {
          iStack_400 = iStack_400 + 1;
        }
      }
    }
  }
  if (iStack_400 != 0) {
    iVar21 = iVar21 + iStack_400 * 3 + 6;
  }
  uVar23 = (uint)(*(int *)(param_1 + 0x44) == 0);
  if ((*(int *)(param_1 + uVar23 * 4 + 0x18) != 0) &&
     (*(int *)(param_1 + uVar23 * 4 + 0x4c) != iVar21)) {
    __dla__FPv(*(undefined4 *)(param_1 + uVar23 * 4 + 0x18));
    *(undefined4 *)(param_1 + uVar23 * 4 + 0x18) = 0;
    *(undefined4 *)(param_1 + uVar23 * 4 + 0x4c) = 0;
  }
  if (*(int *)(param_1 + uVar23 * 4 + 0x18) == 0) {
    uVar10 = __nwa__FUi(iVar21 << 4);
    *(undefined4 *)(param_1 + uVar23 * 4 + 0x18) = uVar10;
    *(int *)(param_1 + uVar23 * 4 + 0x4c) = iVar21;
    *(undefined4 *)(param_1 + 0x70) = 3;
  }
  puVar3 = *(undefined4 **)(param_1 + uVar23 * 4 + 0x18);
  if (*(float *)(param_1 + 0x60) <= *(float *)(param_1 + 0x6c) * -128.0) {
    *(undefined4 **)(param_1 + 0x54) = puVar3;
    *(uint *)(param_1 + 0x44) = uVar23;
    *(undefined4 *)(param_1 + 0x70) = 3;
    uVar30 = 0;
  }
  else {
    auVar31 = _vmr32(in_vf0);
    auVar32 = _vmr32(auVar31);
    auVar33 = _vmr32(auVar32);
    auStack_90 = _sqc2(in_vf0);
    auStack_a0 = _sqc2(auVar31);
    auStack_b0 = _sqc2(auVar32);
    auStack_c0 = _sqc2(auVar33);
    fStack_80 = in_zero_lo;
    fStack_7c = in_zero_hi;
    uStack_78 = in_zero_udw;
    uStack_74 = in_register_0000000c;
    fStack_70 = in_zero_lo;
    fStack_6c = in_zero_hi;
    uStack_68 = in_zero_udw;
    uStack_64 = in_register_0000000c;
    fStack_60 = in_zero_lo;
    fStack_5c = in_zero_hi;
    uStack_58 = in_zero_udw;
    uStack_54 = in_register_0000000c;
    fStack_50 = in_zero_lo;
    fStack_4c = in_zero_hi;
    uStack_48 = in_zero_udw;
    uStack_44 = in_register_0000000c;
    if ((((*(uint *)(param_1 + 0x70) & 1) == 0) && (uVar23 == 0)) ||
       (((*(uint *)(param_1 + 0x70) & 2) == 0 && (uVar23 != 0)))) {
      iVar21 = (int)(*(float *)(param_1 + 0x6c) * 31.0 + 1792.0);
      iVar24 = (int)(*(float *)(param_1 + 0x60) + 1824.0 + *(float *)(param_1 + 0x6c) * 38.0);
      if ((*(uint *)(param_1 + 100) & 3 << ((*(byte *)(iVar25 + 0x3e16) & 0xf) << 1)) == 0) {
        if (bVar1) {
          fStack_1d0 = (float)iVar21;
          fStack_1cc = (float)iVar24;
          uStack_1c8 = 0;
          uStack_1c4 = 0;
          auStack_40._4_4_ = fStack_1cc;
          auStack_40._0_4_ = fStack_1d0;
          _uStack_38 = 0;
          fStack_1dc = (float)iVar24 +
                       (float)*(ushort *)(*(int *)(iGpffff86b4 + 0x426c) + 4) *
                       *(float *)(param_1 + 0x6c);
          fStack_1e0 = (float)iVar21;
          uStack_1d8 = 0;
          uStack_1d4 = 0;
          auStack_30._4_4_ = fStack_1dc;
          auStack_30._0_4_ = fStack_1e0;
          _uStack_28 = 0;
          fStack_1f0 = (float)iVar21 +
                       (float)*(ushort *)(*(int *)(iGpffff86b4 + 0x426c) + 2) *
                       *(float *)(param_1 + 0x6c);
          fStack_1ec = (float)iVar24;
          uStack_1e8 = 0;
          uStack_1e4 = 0;
          auStack_20._4_4_ = fStack_1ec;
          auStack_20._0_4_ = fStack_1f0;
          _uStack_18 = 0;
          fStack_1fc = (float)iVar24 +
                       (float)*(ushort *)(*(int *)(iGpffff86b4 + 0x426c) + 4) *
                       *(float *)(param_1 + 0x6c);
          fStack_200 = (float)iVar21 +
                       (float)*(ushort *)(*(int *)(iGpffff86b4 + 0x426c) + 2) *
                       *(float *)(param_1 + 0x6c);
          uStack_1f8 = 0;
          uStack_1f4 = 0;
          auStack_10._4_4_ = fStack_1fc;
          auStack_10._0_4_ = fStack_200;
          _uStack_8 = 0;
        }
        else {
          uStack_190 = 0x44de0000;
          uStack_18c = 0x44e20000;
          uStack_188 = 0;
          uStack_184 = 0;
          _auStack_40 = ZEXT816(0x44e2000044de0000);
          uStack_1a0 = 0x44de0000;
          uStack_19c = 0x44e20000;
          uStack_198 = 0;
          uStack_194 = 0;
          _auStack_30 = ZEXT816(0x44e2000044de0000);
          uStack_1b0 = 0x44de0000;
          uStack_1ac = 0x44e20000;
          uStack_1a8 = 0;
          uStack_1a4 = 0;
          _auStack_20 = ZEXT816(0x44e2000044de0000);
          uStack_1c0 = 0x44de0000;
          uStack_1bc = 0x44e20000;
          uStack_1b8 = 0;
          uStack_1b4 = 0;
          _auStack_10 = ZEXT816(0x44e2000044de0000);
        }
      }
      else {
        iVar25 = (int)(((float)*(ushort *)(*(int *)(iGpffff86b4 + 0x426c) + 2) *
                       *(float *)(param_1 + 0x6c)) / 2.0);
        iVar26 = (int)(((float)*(ushort *)(*(int *)(iGpffff86b4 + 0x426c) + 4) *
                       *(float *)(param_1 + 0x6c)) / 2.0);
        fVar27 = (float)sinf(*(undefined4 *)(param_1 + 0x74));
        fVar29 = (float)-iVar26 * (fVar27 * 0.25 + 1.25);
        fVar27 = (float)sinf(*(undefined4 *)(param_1 + 0x74));
        fStack_d0 = (float)-iVar25 * (fVar27 * 0.25 + 1.25);
        uStack_c8 = 0;
        uStack_c4 = 0;
        uStack_78 = 0;
        uStack_74 = 0;
        fStack_cc = fVar29;
        fStack_80 = fStack_d0;
        fStack_7c = fVar29;
        fVar27 = (float)sinf(*(undefined4 *)(param_1 + 0x74));
        fVar29 = (float)iVar26 * (fVar27 * 0.25 + 1.25);
        fVar27 = (float)sinf(*(undefined4 *)(param_1 + 0x74));
        fStack_e0 = (float)-iVar25 * (fVar27 * 0.25 + 1.25);
        uStack_d8 = 0;
        uStack_d4 = 0;
        uStack_68 = 0;
        uStack_64 = 0;
        fStack_dc = fVar29;
        fStack_70 = fStack_e0;
        fStack_6c = fVar29;
        fVar27 = (float)sinf(*(undefined4 *)(param_1 + 0x74));
        fVar29 = (float)-iVar26 * (fVar27 * 0.25 + 1.25);
        fVar27 = (float)sinf(*(undefined4 *)(param_1 + 0x74));
        fStack_f0 = (float)iVar25 * (fVar27 * 0.25 + 1.25);
        uStack_e8 = 0;
        uStack_e4 = 0;
        uStack_58 = 0;
        uStack_54 = 0;
        fStack_ec = fVar29;
        fStack_60 = fStack_f0;
        fStack_5c = fVar29;
        fVar27 = (float)sinf(*(undefined4 *)(param_1 + 0x74));
        fVar29 = (float)iVar26 * (fVar27 * 0.25 + 1.25);
        fVar27 = (float)sinf(*(undefined4 *)(param_1 + 0x74));
        fStack_100 = (float)iVar25 * (fVar27 * 0.25 + 1.25);
        uStack_f8 = 0;
        uStack_f4 = 0;
        uStack_48 = 0;
        uStack_44 = 0;
        auVar31 = _vmr32(in_vf0);
        auVar32 = _vmr32(auVar31);
        auVar33 = _vmr32(auVar32);
        auStack_90 = _sqc2(in_vf0);
        auStack_a0 = _sqc2(auVar31);
        auStack_b0 = _sqc2(auVar32);
        auStack_c0 = _sqc2(auVar33);
        fStack_fc = fVar29;
        fStack_50 = fStack_100;
        fStack_4c = fVar29;
        sceVu0RotMatrixZ(0x3f060a92,auStack_c0,auStack_c0);
        ApplyMatrix__6MatrixCFRC7FVector(&uStack_110,auStack_c0,&fStack_80);
        auStack_40._4_4_ = uStack_10c;
        auStack_40._0_4_ = uStack_110;
        uStack_38 = uStack_108;
        uStack_34 = uStack_104;
        ApplyMatrix__6MatrixCFRC7FVector(&uStack_120,auStack_c0,&fStack_70);
        auStack_30._4_4_ = uStack_11c;
        auStack_30._0_4_ = uStack_120;
        uStack_28 = uStack_118;
        uStack_24 = uStack_114;
        ApplyMatrix__6MatrixCFRC7FVector(&uStack_130,auStack_c0,&fStack_60);
        auStack_20._4_4_ = uStack_12c;
        auStack_20._0_4_ = uStack_130;
        uStack_18 = uStack_128;
        uStack_14 = uStack_124;
        ApplyMatrix__6MatrixCFRC7FVector(&uStack_140,auStack_c0,&fStack_50);
        auStack_10._4_4_ = uStack_13c;
        auStack_10._0_4_ = uStack_140;
        uStack_8 = uStack_138;
        uStack_4 = uStack_134;
        fStack_150 = (float)(iVar21 + iVar25);
        fStack_14c = (float)(iVar24 + iVar26);
        uStack_148 = 0;
        uStack_144 = 0;
        auVar9._4_4_ = fStack_14c;
        auVar9._0_4_ = fStack_150;
        auVar9._8_8_ = 0;
        auVar32 = _lqc2(auVar9);
        auVar31 = _lqc2(_auStack_40);
        auVar31 = _vadd(auVar31,auVar32);
        _auStack_40 = _sqc2(auVar31);
        fStack_160 = (float)(iVar21 + iVar25);
        fStack_15c = (float)(iVar24 + iVar26);
        uStack_158 = 0;
        uStack_154 = 0;
        auVar33._4_4_ = fStack_15c;
        auVar33._0_4_ = fStack_160;
        auVar33._8_8_ = 0;
        auVar32 = _lqc2(auVar33);
        auVar31 = _lqc2(_auStack_30);
        auVar31 = _vadd(auVar31,auVar32);
        _auStack_30 = _sqc2(auVar31);
        fStack_170 = (float)(iVar21 + iVar25);
        fStack_16c = (float)(iVar24 + iVar26);
        uStack_168 = 0;
        uStack_164 = 0;
        auVar32._4_4_ = fStack_16c;
        auVar32._0_4_ = fStack_170;
        auVar32._8_8_ = 0;
        auVar32 = _lqc2(auVar32);
        auVar31 = _lqc2(_auStack_20);
        auVar31 = _vadd(auVar31,auVar32);
        _auStack_20 = _sqc2(auVar31);
        fStack_180 = (float)(iVar21 + iVar25);
        fStack_17c = (float)(iVar24 + iVar26);
        uStack_178 = 0;
        uStack_174 = 0;
        auVar31._4_4_ = fStack_17c;
        auVar31._0_4_ = fStack_180;
        auVar31._8_8_ = 0;
        auVar32 = _lqc2(auVar31);
        auVar31 = _lqc2(_auStack_10);
        auVar31 = _vadd(auVar31,auVar32);
        _auStack_10 = _sqc2(auVar31);
      }
      uVar13 = __fixunssfdi((float)auStack_40._0_4_ * 16.0);
      lVar14 = __fixunssfdi((float)auStack_40._4_4_ * 16.0);
      lVar15 = __fixunssfdi(uVar30);
      *(ulong *)(puVar3 + 0x52) = lVar15 << 0x20 | uVar13 | lVar14 << 0x10;
      uVar13 = __fixunssfdi((float)auStack_30._0_4_ * 16.0);
      lVar14 = __fixunssfdi((float)auStack_30._4_4_ * 16.0);
      lVar15 = __fixunssfdi(uVar30);
      *(ulong *)(puVar3 + 0x56) = lVar15 << 0x20 | uVar13 | lVar14 << 0x10;
      uVar13 = __fixunssfdi((float)auStack_20._0_4_ * 16.0);
      lVar14 = __fixunssfdi((float)auStack_20._4_4_ * 16.0);
      lVar15 = __fixunssfdi(uVar30);
      *(ulong *)(puVar3 + 0x5a) = lVar15 << 0x20 | uVar13 | lVar14 << 0x10;
      uVar13 = __fixunssfdi((float)auStack_10._0_4_ * 16.0);
      lVar14 = __fixunssfdi((float)auStack_10._4_4_ * 16.0);
      lVar15 = __fixunssfdi(uVar30);
      *(ulong *)(puVar3 + 0x5e) = lVar15 << 0x20 | uVar13 | lVar14 << 0x10;
      *(undefined4 *)(param_1 + 0x54) = *(undefined4 *)(param_1 + uVar23 * 4 + 0x58);
      *(uint *)(param_1 + 0x44) = uVar23;
      uVar30 = *(undefined4 *)(param_1 + *(int *)(param_1 + 0x44) * 4 + 0x18);
    }
    else {
      *puVar3 = 0x50000000;
      puVar3[1] = *(undefined4 *)
                   (*(int *)(iGpffff86b4 + 17000) +
                    (uint)*(ushort *)(*(int *)(iGpffff86b4 + 17000) + 10) * 4 + 0xc);
      puVar3[2] = 0;
      puVar3[3] = 0;
      puVar3[4] = 0x10000000;
      puVar3[5] = 0;
      puVar3[6] = 0;
      puVar3[7] = 0x50000000;
      *(undefined8 *)(puVar3 + 8) = 0x6000000000000001;
      *(undefined8 *)(puVar3 + 10) = 0xe6e8ee;
      *(undefined8 *)(puVar3 + 0xc) = 1;
      *(undefined8 *)(puVar3 + 0xe) = 0x3f;
      *(undefined8 *)(puVar3 + 0x10) = 0x60;
      *(undefined8 *)(puVar3 + 0x12) = 0x14;
      *(undefined8 *)(puVar3 + 0x14) = 5;
      *(undefined8 *)(puVar3 + 0x16) = 0;
      *(undefined8 *)(puVar3 + 0x18) = 0x23001;
      *(undefined8 *)(puVar3 + 0x1a) = 0x47;
      uVar16 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 17000),1);
      *(undefined8 *)(puVar3 + 0x1c) = uVar16;
      *(undefined8 *)(puVar3 + 0x1e) = 0;
      *(undefined8 *)(puVar3 + 0x20) = 0x44;
      *(undefined8 *)(puVar3 + 0x22) = 0x42;
      iVar21 = (int)(*(float *)(param_1 + 0x6c) * 14.0 + 1792.0);
      iVar24 = (int)(*(float *)(param_1 + 0x60) + 1824.0 + *(float *)(param_1 + 0x6c) * 11.0);
      *(undefined8 *)(puVar3 + 0x24) = 0x6400000000008001;
      *(undefined8 *)(puVar3 + 0x26) = 0x43c310;
      *(undefined8 *)(puVar3 + 0x28) = 0x156;
      *(undefined8 *)(puVar3 + 0x2a) = 0x80808080;
      *(undefined8 *)(puVar3 + 0x2c) = 0;
      uVar13 = __fixunssfdi((float)iVar21 * 16.0);
      lVar14 = __fixunssfdi((float)iVar24 * 16.0);
      lVar15 = __fixunssfdi(uVar30);
      *(ulong *)(puVar3 + 0x2e) = lVar15 << 0x20 | uVar13 | lVar14 << 0x10;
      uVar13 = __fixunssfdi((float)*(ushort *)(*(int *)(iGpffff86b4 + 17000) + 2) * 16.0);
      lVar14 = __fixunssfdi((float)*(ushort *)(*(int *)(iGpffff86b4 + 17000) + 4) * 16.0);
      *(ulong *)(puVar3 + 0x30) = uVar13 | lVar14 << 0x10;
      uVar13 = __fixunssfdi(((float)iVar21 +
                               (float)*(ushort *)(*(int *)(iGpffff86b4 + 17000) + 2) *
                               *(float *)(param_1 + 0x6c)) * 16.0);
      lVar14 = __fixunssfdi(((float)iVar24 +
                               (float)*(ushort *)(*(int *)(iGpffff86b4 + 17000) + 4) *
                               *(float *)(param_1 + 0x6c)) * 16.0);
      lVar15 = __fixunssfdi(uVar30);
      *(ulong *)(puVar3 + 0x32) = lVar15 << 0x20 | uVar13 | lVar14 << 0x10;
      puVar3[4] = 0x1000000b;
      puVar3[7] = 0x5000000b;
      puVar3[0x34] = 0x50000000;
      if ((*(uint *)(param_1 + 100) & 3 << ((*(byte *)(iVar25 + 0x3e16) & 0xf) << 1)) == 0) {
        puVar3[0x35] = *(undefined4 *)
                        (*(int *)(iGpffff86b4 + 0x426c) +
                         (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x426c) + 10) * 4 + 0xc);
      }
      else {
        puVar3[0x35] = *(undefined4 *)
                        (*(int *)(iGpffff86b4 + 0x4270) +
                         (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x4270) + 10) * 4 + 0xc);
      }
      puVar3[0x36] = 0;
      puVar3[0x37] = 0;
      puVar3[0x38] = 0x10000000;
      puVar3[0x39] = 0;
      puVar3[0x3a] = 0;
      puVar3[0x3b] = 0x50000000;
      *(undefined8 *)(puVar3 + 0x3c) = 0x2000000000000001;
      *(undefined8 *)(puVar3 + 0x3e) = 0x6e;
      *(undefined8 *)(puVar3 + 0x40) = 1;
      *(undefined8 *)(puVar3 + 0x42) = 0x3f;
      if ((*(uint *)(param_1 + 100) & 3 << ((*(byte *)(iVar25 + 0x3e16) & 0xf) << 1)) == 0) {
        uVar16 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x426c),1);
        *(undefined8 *)(puVar3 + 0x44) = uVar16;
      }
      else {
        uVar16 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x4270),1);
        *(undefined8 *)(puVar3 + 0x44) = uVar16;
      }
      *(undefined8 *)(puVar3 + 0x46) = 0;
      iVar21 = (int)(*(float *)(param_1 + 0x6c) * 31.0 + 1792.0);
      iVar24 = (int)(*(float *)(param_1 + 0x60) + 1824.0 + *(float *)(param_1 + 0x6c) * 38.0);
      if ((*(uint *)(param_1 + 100) & 3 << ((*(byte *)(iVar25 + 0x3e16) & 0xf) << 1)) == 0) {
        if (bVar1) {
          auStack_40._4_4_ = (float)iVar24;
          auStack_40._0_4_ = (float)iVar21;
          _uStack_38 = 0;
          auStack_30._4_4_ =
               (float)iVar24 +
               (float)*(ushort *)(*(int *)(iGpffff86b4 + 0x426c) + 4) * *(float *)(param_1 + 0x6c);
          auStack_30._0_4_ = (float)iVar21;
          _uStack_28 = 0;
          auStack_20._4_4_ = (float)iVar24;
          auStack_20._0_4_ =
               (float)iVar21 +
               (float)*(ushort *)(*(int *)(iGpffff86b4 + 0x426c) + 2) * *(float *)(param_1 + 0x6c);
          _uStack_18 = 0;
          uVar16 = 0;
          auStack_10._4_4_ =
               (float)iVar24 +
               (float)*(ushort *)(*(int *)(iGpffff86b4 + 0x426c) + 4) * *(float *)(param_1 + 0x6c);
          auStack_10._0_4_ =
               (float)iVar21 +
               (float)*(ushort *)(*(int *)(iGpffff86b4 + 0x426c) + 2) * *(float *)(param_1 + 0x6c);
          _uStack_8 = 0;
        }
        else {
          _auStack_40 = ZEXT816(0x44e2000044de0000);
          _auStack_30 = ZEXT816(0x44e2000044de0000);
          _auStack_20 = ZEXT816(0x44e2000044de0000);
          uVar16 = 0;
          _auStack_10 = ZEXT816(0x44e2000044de0000);
        }
      }
      else {
        iVar26 = (int)(((float)*(ushort *)(*(int *)(iGpffff86b4 + 0x4270) + 2) *
                       *(float *)(param_1 + 0x6c)) / 2.0);
        iVar28 = (int)(((float)*(ushort *)(*(int *)(iGpffff86b4 + 0x4270) + 4) *
                       *(float *)(param_1 + 0x6c)) / 2.0);
        fVar27 = (float)sinf(*(undefined4 *)(param_1 + 0x74));
        fVar29 = (float)-iVar28 * (fVar27 * 0.25 + 1.25);
        fVar27 = (float)sinf(*(undefined4 *)(param_1 + 0x74));
        fStack_210 = (float)-iVar26 * (fVar27 * 0.25 + 1.25);
        uStack_208 = 0;
        uStack_204 = 0;
        uStack_78 = 0;
        uStack_74 = 0;
        fStack_20c = fVar29;
        fStack_80 = fStack_210;
        fStack_7c = fVar29;
        fVar27 = (float)sinf(*(undefined4 *)(param_1 + 0x74));
        fVar29 = (float)iVar28 * (fVar27 * 0.25 + 1.25);
        fVar27 = (float)sinf(*(undefined4 *)(param_1 + 0x74));
        fStack_220 = (float)-iVar26 * (fVar27 * 0.25 + 1.25);
        uStack_218 = 0;
        uStack_214 = 0;
        uStack_68 = 0;
        uStack_64 = 0;
        fStack_21c = fVar29;
        fStack_70 = fStack_220;
        fStack_6c = fVar29;
        fVar27 = (float)sinf(*(undefined4 *)(param_1 + 0x74));
        fVar29 = (float)-iVar28 * (fVar27 * 0.25 + 1.25);
        fVar27 = (float)sinf(*(undefined4 *)(param_1 + 0x74));
        fStack_230 = (float)iVar26 * (fVar27 * 0.25 + 1.25);
        uStack_228 = 0;
        uStack_224 = 0;
        uStack_58 = 0;
        uStack_54 = 0;
        fStack_22c = fVar29;
        fStack_60 = fStack_230;
        fStack_5c = fVar29;
        fVar27 = (float)sinf(*(undefined4 *)(param_1 + 0x74));
        fVar29 = (float)iVar28 * (fVar27 * 0.25 + 1.25);
        fVar27 = (float)sinf(*(undefined4 *)(param_1 + 0x74));
        fStack_240 = (float)iVar26 * (fVar27 * 0.25 + 1.25);
        uStack_238 = 0;
        uStack_234 = 0;
        uStack_48 = 0;
        uStack_44 = 0;
        auVar31 = _vmr32(in_vf0);
        auVar32 = _vmr32(auVar31);
        auVar33 = _vmr32(auVar32);
        auStack_90 = _sqc2(in_vf0);
        auStack_a0 = _sqc2(auVar31);
        auStack_b0 = _sqc2(auVar32);
        auStack_c0 = _sqc2(auVar33);
        fStack_23c = fVar29;
        fStack_50 = fStack_240;
        fStack_4c = fVar29;
        sceVu0RotMatrixZ(0x3f060a92,auStack_c0,auStack_c0);
        ApplyMatrix__6MatrixCFRC7FVector(&uStack_250,auStack_c0,&fStack_80);
        auStack_40._4_4_ = uStack_24c;
        auStack_40._0_4_ = uStack_250;
        uStack_38 = uStack_248;
        uStack_34 = uStack_244;
        ApplyMatrix__6MatrixCFRC7FVector(&uStack_260,auStack_c0,&fStack_70);
        auStack_30._4_4_ = uStack_25c;
        auStack_30._0_4_ = uStack_260;
        uStack_28 = uStack_258;
        uStack_24 = uStack_254;
        ApplyMatrix__6MatrixCFRC7FVector(&uStack_270,auStack_c0,&fStack_60);
        auStack_20._4_4_ = uStack_26c;
        auStack_20._0_4_ = uStack_270;
        uStack_18 = uStack_268;
        uStack_14 = uStack_264;
        ApplyMatrix__6MatrixCFRC7FVector(auStack_280,auStack_c0,&fStack_50);
        uVar16 = auStack_280._8_8_;
        auVar8._4_4_ = (float)(iVar24 + iVar28);
        auVar8._0_4_ = (float)(iVar21 + iVar26);
        auVar8._8_8_ = 0;
        auVar32 = _lqc2(auVar8);
        auVar31 = _lqc2(_auStack_40);
        auVar31 = _vadd(auVar31,auVar32);
        _auStack_40 = _sqc2(auVar31);
        auVar7._4_4_ = (float)(iVar24 + iVar28);
        auVar7._0_4_ = (float)(iVar21 + iVar26);
        auVar7._8_8_ = 0;
        auVar32 = _lqc2(auVar7);
        auVar31 = _lqc2(_auStack_30);
        auVar31 = _vadd(auVar31,auVar32);
        _auStack_30 = _sqc2(auVar31);
        auVar6._4_4_ = (float)(iVar24 + iVar28);
        auVar6._0_4_ = (float)(iVar21 + iVar26);
        auVar6._8_8_ = 0;
        auVar32 = _lqc2(auVar6);
        auVar31 = _lqc2(_auStack_20);
        auVar31 = _vadd(auVar31,auVar32);
        _auStack_20 = _sqc2(auVar31);
        auVar5._4_4_ = (float)(iVar24 + iVar28);
        auVar5._0_4_ = (float)(iVar21 + iVar26);
        auVar5._8_8_ = 0;
        auVar32 = _lqc2(auVar5);
        auVar31 = _lqc2(auStack_280);
        auVar31 = _vadd(auVar31,auVar32);
        _auStack_10 = _sqc2(auVar31);
      }
      auVar17._8_8_ = uVar16;
      auVar17._0_8_ = 0xa400000000008001;
      auVar4._4_4_ = in_zero_hi;
      auVar4._0_4_ = in_zero_lo;
      auVar4._8_4_ = in_zero_udw;
      auVar4._12_4_ = in_register_0000000c;
      auVar31 = _pcpyld(auVar4,auVar17);
      *(long *)(puVar3 + 0x48) = auVar31._0_8_;
      *(undefined8 *)(puVar3 + 0x4a) = 0x4343c3c310;
      *(undefined8 *)(puVar3 + 0x4c) = 0x154;
      *(undefined8 *)(puVar3 + 0x4e) = 0x80808080;
      *(undefined8 *)(puVar3 + 0x50) = 0;
      uVar13 = __fixunssfdi((float)auStack_40._0_4_ * 16.0);
      lVar14 = __fixunssfdi((float)auStack_40._4_4_ * 16.0);
      lVar15 = __fixunssfdi(uVar30);
      *(ulong *)(puVar3 + 0x52) = lVar15 << 0x20 | uVar13 | lVar14 << 0x10;
      lVar14 = __fixunssfdi((float)*(ushort *)(*(int *)(iGpffff86b4 + 0x426c) + 4) * 16.0 - 8.0);
      *(long *)(puVar3 + 0x54) = lVar14 << 0x10;
      uVar13 = __fixunssfdi((float)auStack_30._0_4_ * 16.0);
      lVar14 = __fixunssfdi((float)auStack_30._4_4_ * 16.0);
      lVar15 = __fixunssfdi(uVar30);
      *(ulong *)(puVar3 + 0x56) = lVar15 << 0x20 | uVar13 | lVar14 << 0x10;
      uVar16 = __fixunssfdi((float)*(ushort *)(*(int *)(iGpffff86b4 + 0x426c) + 2) * 16.0 - 8.0);
      *(undefined8 *)(puVar3 + 0x58) = uVar16;
      uVar13 = __fixunssfdi((float)auStack_20._0_4_ * 16.0);
      lVar14 = __fixunssfdi((float)auStack_20._4_4_ * 16.0);
      lVar15 = __fixunssfdi(uVar30);
      *(ulong *)(puVar3 + 0x5a) = lVar15 << 0x20 | uVar13 | lVar14 << 0x10;
      uVar13 = __fixunssfdi((float)*(ushort *)(*(int *)(iGpffff86b4 + 0x426c) + 2) * 16.0 - 8.0);
      lVar14 = __fixunssfdi((float)*(ushort *)(*(int *)(iGpffff86b4 + 0x426c) + 4) * 16.0 - 8.0);
      *(ulong *)(puVar3 + 0x5c) = uVar13 | lVar14 << 0x10;
      uVar13 = __fixunssfdi((float)auStack_10._0_4_ * 16.0);
      lVar14 = __fixunssfdi((float)auStack_10._4_4_ * 16.0);
      lVar15 = __fixunssfdi(uVar30);
      *(ulong *)(puVar3 + 0x5e) = lVar15 << 0x20 | uVar13 | lVar14 << 0x10;
      puVar3[0x38] = 0x10000009;
      puVar3[0x3b] = 0x50000009;
      puVar3[0x60] = 0x50000000;
      puVar3[0x61] = *(undefined4 *)
                      (*(int *)(iGpffff86b4 + 0x4264) +
                       (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x4264) + 10) * 4 + 0xc);
      puVar3[0x62] = 0;
      puVar3[99] = 0;
      puVar3[100] = 0x10000000;
      puVar3[0x65] = 0;
      puVar3[0x66] = 0;
      puVar3[0x67] = 0x50000000;
      *(undefined8 *)(puVar3 + 0x68) = 0x2000000000000001;
      *(undefined8 *)(puVar3 + 0x6a) = 0x6e;
      *(undefined8 *)(puVar3 + 0x6c) = 1;
      *(undefined8 *)(puVar3 + 0x6e) = 0x3f;
      uVar16 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x4264),1);
      *(undefined8 *)(puVar3 + 0x70) = uVar16;
      *(undefined8 *)(puVar3 + 0x72) = 0;
      fVar27 = *(float *)(param_1 + 0x6c) * 84.0 + 1792.0;
      iVar26 = (int)(*(float *)(param_1 + 0x60) + 1824.0 + *(float *)(param_1 + 0x6c) * 40.0);
      *(undefined8 *)(puVar3 + 0x74) = 0x6400000000008009;
      *(undefined8 *)(puVar3 + 0x76) = 0x43c310;
      puVar18 = (undefined8 *)(puVar3 + 0x78);
      iVar21 = 4;
      for (iVar24 = 0; iVar28 = (int)fVar27, iVar24 < 9; iVar24 = iVar24 + 1) {
        *puVar18 = 0x156;
        puVar18[1] = 0x80808080;
        puVar18[2] = 0;
        uVar13 = __fixunssfdi(((float)iVar28 - *(float *)(param_1 + 0x6c)) * 16.0);
        lVar14 = __fixunssfdi(((float)iVar26 - *(float *)(param_1 + 0x6c)) * 16.0);
        lVar15 = __fixunssfdi(uVar30);
        puVar18[3] = lVar15 << 0x20 | uVar13 | lVar14 << 0x10;
        puVar18[4] = 0x3200250;
        uVar13 = __fixunssfdi(((float)iVar28 + *(float *)(param_1 + 0x6c) * 36.0) * 16.0);
        lVar14 = __fixunssfdi(((float)iVar26 + *(float *)(param_1 + 0x6c) * 49.0) * 16.0);
        lVar15 = __fixunssfdi(uVar30);
        puVar18[5] = lVar15 << 0x20 | uVar13 | lVar14 << 0x10;
        puVar18 = puVar18 + 6;
        iVar21 = iVar21 + 3;
        fVar27 = (float)iVar28 + *(float *)(param_1 + 0x6c) * 26.0;
      }
      puVar3[100] = iVar21 + 0x10000000;
      puVar3[0x67] = iVar21 + 0x50000000;
      *(undefined4 *)puVar18 = 0x50000000;
      if (bVar1) {
        if ((long)((ulong)*(byte *)(iGpffff86b4 + (uint)*(byte *)(iVar25 + 0x3e16) * 0x4f0 + 0xb0)
                  << 0x3b) < 0) {
          *(undefined4 *)((int)puVar18 + 4) =
               *(undefined4 *)
                (*(int *)(iGpffff86b4 + 0x42b0) +
                 (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42b0) + 10) * 4 + 0xc);
        }
        else {
          *(undefined4 *)((int)puVar18 + 4) =
               *(undefined4 *)
                (*(int *)(iGpffff86b4 + 0x42ac) +
                 (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42ac) + 10) * 4 + 0xc);
        }
      }
      else if ((*(byte *)(iGpffff86b4 + (uint)*(byte *)(iVar25 + 0x3e16) * 0x4f0 + 0xb1) & 1) == 0)
      {
        if (*(short *)(iGpffff86b4 + (uint)*(byte *)(iVar25 + 0x3e16) * 0x4f0 + 0x18c) == 0x51) {
          iVar21 = *(int *)(iGpffff86b4 + sRam00652bba * 4 + 0x4224);
          *(undefined4 *)((int)puVar18 + 4) =
               *(undefined4 *)(iVar21 + (uint)*(ushort *)(iVar21 + 10) * 4 + 0xc);
        }
        else if (*(short *)(iGpffff86b4 + (uint)*(byte *)(iVar25 + 0x3e16) * 0x4f0 + 0x18c) == 0x54)
        {
          iVar21 = *(int *)(iGpffff86b4 + sRam00652bb6 * 4 + 0x4224);
          *(undefined4 *)((int)puVar18 + 4) =
               *(undefined4 *)(iVar21 + (uint)*(ushort *)(iVar21 + 10) * 4 + 0xc);
        }
        else if (*(short *)(iGpffff86b4 + (uint)*(byte *)(iVar25 + 0x3e16) * 0x4f0 + 0x18c) == 0x57)
        {
          iVar21 = *(int *)(iGpffff86b4 + sRam00652bb8 * 4 + 0x4224);
          *(undefined4 *)((int)puVar18 + 4) =
               *(undefined4 *)(iVar21 + (uint)*(ushort *)(iVar21 + 10) * 4 + 0xc);
        }
        else {
          iVar21 = *(int *)(iGpffff86b4 +
                            *(short *)(*(short *)(iGpffff86b4 +
                                                  (uint)*(byte *)(iVar25 + 0x3e16) * 0x4f0 + 0x18c)
                                       * 2 + 0x652bb0) * 4 + 0x4224);
          *(undefined4 *)((int)puVar18 + 4) =
               *(undefined4 *)(iVar21 + (uint)*(ushort *)(iVar21 + 10) * 4 + 0xc);
        }
      }
      else {
        iVar21 = *(int *)(iGpffff86b4 +
                          *(short *)((uint)*(ushort *)
                                            (ourBtlSaveDat +
                                             *(short *)(iGpffff86b4 +
                                                        (uint)*(byte *)(iVar25 + 0x3e16) * 0x4f0 +
                                                       0x120) * 0xc0 + 0x48) * 2 + 0x652bb0) * 4 +
                         0x4224);
        *(undefined4 *)((int)puVar18 + 4) =
             *(undefined4 *)(iVar21 + (uint)*(ushort *)(iVar21 + 10) * 4 + 0xc);
      }
      *(undefined4 *)(puVar18 + 1) = 0;
      *(undefined4 *)((int)puVar18 + 0xc) = 0;
      *(undefined4 *)(puVar18 + 2) = 0x10000000;
      *(undefined4 *)((int)puVar18 + 0x14) = 0;
      *(undefined4 *)(puVar18 + 3) = 0;
      *(undefined4 *)((int)puVar18 + 0x1c) = 0x50000000;
      puVar18[4] = 0x2000000000000001;
      puVar18[5] = 0x6e;
      puVar18[6] = 1;
      puVar18[7] = 0x3f;
      puVar19 = puVar18 + 8;
      if (bVar1) {
        if ((long)((ulong)*(byte *)(iGpffff86b4 + (uint)*(byte *)(iVar25 + 0x3e16) * 0x4f0 + 0xb0)
                  << 0x3b) < 0) {
          uVar16 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x42b0),1);
          *puVar19 = uVar16;
          iStack_350 = 0;
          iStack_360 = 0;
          uVar11 = (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42b0) + 2);
          uStack_370 = (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42b0) + 4);
          iVar21 = (int)(*(float *)(param_1 + 0x6c) * 19.0 + 1792.0);
          iVar24 = (int)(*(float *)(param_1 + 0x60) + 1824.0 + *(float *)(param_1 + 0x6c) * 51.0);
        }
        else if (*(short *)(iGpffff86b4 + (uint)*(byte *)(iVar25 + 0x3e16) * 0x4f0 + 0x120) < 4) {
          uVar16 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x42ac),1);
          *puVar19 = uVar16;
          iStack_350 = 0;
          iStack_360 = *(short *)(iGpffff86b4 + (uint)*(byte *)(iVar25 + 0x3e16) * 0x4f0 + 0x120) *
                       0x30;
          uVar11 = 0x24;
          uStack_370 = 0x30;
          iVar21 = (int)(*(float *)(param_1 + 0x6c) * 33.0 + 1792.0);
          iVar24 = (int)(*(float *)(param_1 + 0x60) + 1824.0 + *(float *)(param_1 + 0x6c) * 41.0);
        }
        else {
          uVar16 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x42ac),1);
          *puVar19 = uVar16;
          iStack_350 = 0x24;
          iStack_360 = (*(short *)(iGpffff86b4 + (uint)*(byte *)(iVar25 + 0x3e16) * 0x4f0 + 0x120) +
                       -4) * 0x30;
          uVar11 = 0x24;
          uStack_370 = 0x30;
          iVar21 = (int)(*(float *)(param_1 + 0x6c) * 33.0 + 1792.0);
          iVar24 = (int)(*(float *)(param_1 + 0x60) + 1824.0 + *(float *)(param_1 + 0x6c) * 41.0);
        }
      }
      else {
        if ((*(byte *)(iGpffff86b4 + (uint)*(byte *)(iVar25 + 0x3e16) * 0x4f0 + 0xb1) & 1) == 0) {
          if (*(short *)(iGpffff86b4 + (uint)*(byte *)(iVar25 + 0x3e16) * 0x4f0 + 0x18c) == 0x51) {
            uVar16 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + sRam00652bba * 4 + 0x4224),1);
            *puVar19 = uVar16;
            uVar11 = (uint)*(ushort *)(*(int *)(iGpffff86b4 + sRam00652bba * 4 + 0x4224) + 2);
            uStack_370 = (uint)*(ushort *)(*(int *)(iGpffff86b4 + sRam00652bba * 4 + 0x4224) + 4);
          }
          else if (*(short *)(iGpffff86b4 + (uint)*(byte *)(iVar25 + 0x3e16) * 0x4f0 + 0x18c) ==
                   0x54) {
            uVar16 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + sRam00652bb6 * 4 + 0x4224),1);
            *puVar19 = uVar16;
            uVar11 = (uint)*(ushort *)(*(int *)(iGpffff86b4 + sRam00652bb6 * 4 + 0x4224) + 2);
            uStack_370 = (uint)*(ushort *)(*(int *)(iGpffff86b4 + sRam00652bb6 * 4 + 0x4224) + 4);
          }
          else if (*(short *)(iGpffff86b4 + (uint)*(byte *)(iVar25 + 0x3e16) * 0x4f0 + 0x18c) ==
                   0x57) {
            uVar16 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + sRam00652bb8 * 4 + 0x4224),1);
            *puVar19 = uVar16;
            uVar11 = (uint)*(ushort *)(*(int *)(iGpffff86b4 + sRam00652bb8 * 4 + 0x4224) + 2);
            uStack_370 = (uint)*(ushort *)(*(int *)(iGpffff86b4 + sRam00652bb8 * 4 + 0x4224) + 4);
          }
          else {
            uVar16 = GetTex0__6JRCTexFb(*(undefined4 *)
                                      (iGpffff86b4 +
                                       *(short *)(*(short *)(iGpffff86b4 +
                                                             (uint)*(byte *)(iVar25 + 0x3e16) *
                                                             0x4f0 + 0x18c) * 2 + 0x652bb0) * 4 +
                                      0x4224),1);
            *puVar19 = uVar16;
            uVar11 = (uint)*(ushort *)
                            (*(int *)(iGpffff86b4 +
                                      *(short *)(*(short *)(iGpffff86b4 +
                                                            (uint)*(byte *)(iVar25 + 0x3e16) * 0x4f0
                                                           + 0x18c) * 2 + 0x652bb0) * 4 + 0x4224) +
                            2);
            uStack_370 = (uint)*(ushort *)
                                (*(int *)(iGpffff86b4 +
                                          *(short *)(*(short *)(iGpffff86b4 +
                                                                (uint)*(byte *)(iVar25 + 0x3e16) *
                                                                0x4f0 + 0x18c) * 2 + 0x652bb0) * 4 +
                                         0x4224) + 4);
          }
        }
        else {
          uVar16 = GetTex0__6JRCTexFb(*(undefined4 *)
                                    (iGpffff86b4 +
                                     *(short *)((uint)*(ushort *)
                                                       (ourBtlSaveDat +
                                                        *(short *)(iGpffff86b4 +
                                                                   (uint)*(byte *)(iVar25 + 0x3e16)
                                                                   * 0x4f0 + 0x120) * 0xc0 + 0x48) *
                                                2 + 0x652bb0) * 4 + 0x4224),1);
          *puVar19 = uVar16;
          uVar11 = (uint)*(ushort *)
                          (*(int *)(iGpffff86b4 +
                                    *(short *)((uint)*(ushort *)
                                                      (ourBtlSaveDat +
                                                       *(short *)(iGpffff86b4 +
                                                                  (uint)*(byte *)(iVar25 + 0x3e16) *
                                                                  0x4f0 + 0x120) * 0xc0 + 0x48) * 2
                                              + 0x652bb0) * 4 + 0x4224) + 2);
          uStack_370 = (uint)*(ushort *)
                              (*(int *)(iGpffff86b4 +
                                        *(short *)((uint)*(ushort *)
                                                          (ourBtlSaveDat +
                                                           *(short *)(iGpffff86b4 +
                                                                      (uint)*(byte *)(iVar25 + 
                                                  0x3e16) * 0x4f0 + 0x120) * 0xc0 + 0x48) * 2 +
                                                  0x652bb0) * 4 + 0x4224) + 4);
        }
        iStack_350 = 0;
        iStack_360 = 0;
        iVar21 = (int)(*(float *)(param_1 + 0x6c) * 21.0 + 1792.0);
        iVar24 = (int)(*(float *)(param_1 + 0x60) + 1824.0 + *(float *)(param_1 + 0x6c) * 28.0);
      }
      puVar18[9] = 0;
      puVar18[10] = 0x6400000000008001;
      puVar18[0xb] = 0x43c310;
      puVar18[0xc] = 0x156;
      if ((((bVar1) || ('\0' < *(char *)(iVar25 + 0x3e17))) ||
          (*(short *)(iGpffff86b4 + (uint)*(byte *)(iVar25 + 0x3e16) * 0x4f0 + 0x120) == 8)) ||
         ((*(short *)(iGpffff86b4 + (uint)*(byte *)(iVar25 + 0x3e16) * 0x4f0 + 0x120) == 9 ||
          (*(short *)(iGpffff86b4 + (uint)*(byte *)(iVar25 + 0x3e16) * 0x4f0 + 0x120) == 10)))) {
        if (((bVar1) || (0 < *(short *)(iVar25 + 0x3e18))) && ((*pbVar22 & 1) == 0)) {
          puVar18[0xd] = 0x80808080;
        }
        else {
          puVar18[0xd] = 0x80189696;
        }
      }
      else {
        puVar18[0xd] = 0x802020a0;
      }
      uVar13 = __fixunssfdi((float)iStack_350 * 16.0);
      lVar14 = __fixunssfdi((float)iStack_360 * 16.0);
      puVar18[0xe] = uVar13 | lVar14 << 0x10;
      uVar13 = __fixunssfdi((float)iVar21 * 16.0);
      lVar14 = __fixunssfdi((float)iVar24 * 16.0);
      lVar15 = __fixunssfdi(uVar30);
      puVar18[0xf] = lVar15 << 0x20 | uVar13 | lVar14 << 0x10;
      uVar13 = __fixunssfdi((float)(iStack_350 + uVar11) * 16.0);
      lVar14 = __fixunssfdi((float)(int)(iStack_360 + uStack_370) * 16.0);
      puVar18[0x10] = uVar13 | lVar14 << 0x10;
      uVar13 = __fixunssfdi(((float)iVar21 + (float)uVar11 * *(float *)(param_1 + 0x6c)) * 16.0);
      lVar14 = __fixunssfdi(((float)iVar24 + (float)uStack_370 * *(float *)(param_1 + 0x6c)) *
                               16.0);
      lVar15 = __fixunssfdi(uVar30);
      puVar18[0x11] = lVar15 << 0x20 | uVar13 | lVar14 << 0x10;
      puVar19 = puVar18 + 0x12;
      *(undefined4 *)(puVar18 + 2) = 0x10000007;
      *(undefined4 *)((int)puVar18 + 0x1c) = 0x50000007;
      if (iStack_3a0 != 0) {
        *(undefined4 *)puVar19 = 0x50000000;
        *(undefined4 *)((int)puVar18 + 0x94) =
             *(undefined4 *)
              (*(int *)(iGpffff86b4 + 0x42b4) +
               (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42b4) + 10) * 4 + 0xc);
        *(undefined4 *)(puVar18 + 0x13) = 0;
        *(undefined4 *)((int)puVar18 + 0x9c) = 0;
        *(int *)(puVar18 + 0x14) = 0x10000000;
        *(undefined4 *)((int)puVar18 + 0xa4) = 0;
        *(undefined4 *)(puVar18 + 0x15) = 0;
        *(undefined4 *)((int)puVar18 + 0xac) = 0x50000000;
        puVar18[0x16] = 0x2000000000000001;
        puVar18[0x17] = 0x6e;
        puVar18[0x18] = 1;
        puVar18[0x19] = 0x3f;
        uVar16 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x42b4),1);
        puVar18[0x1a] = uVar16;
        puVar18[0x1b] = 0;
        fVar27 = *(float *)(param_1 + 0x6c) * 84.0 + 1792.0;
        iVar26 = (int)(*(float *)(param_1 + 0x60) + 1824.0 + *(float *)(param_1 + 0x6c) * 40.0);
        puVar18[0x1c] = (long)iStack_3a0 | 0x6400000000008000;
        puVar18[0x1d] = 0x43c310;
        puVar19 = puVar18 + 0x1e;
        iVar21 = 4;
        for (iVar24 = 1; iVar28 = (int)fVar27, iVar24 < 10; iVar24 = iVar24 + 1) {
          if (((*(byte *)(iGpffff86b4 + (uint)pbVar22[iVar24 * 8 + 2] * 0x4f0 + 0xb4) & 1) == 0) &&
             (*(short *)(iGpffff86b4 + (uint)pbVar22[iVar24 * 8 + 2] * 0x4f0 + 0x120) < 8)) {
            if ((*(byte *)(iGpffff86b4 + (uint)pbVar22[iVar24 * 8 + 2] * 0x4f0 + 0xb1) & 1) == 0) {
              uVar13 = (ulong)*(short *)(iGpffff86b4 + (uint)pbVar22[iVar24 * 8 + 2] * 0x4f0 + 0x18c
                                        );
              if (uVar13 == 0x51) {
                uVar13 = 5;
              }
              if (uVar13 == 0x54) {
                uVar13 = 3;
              }
              if (uVar13 == 0x57) {
                uVar13 = 4;
              }
            }
            else {
              uVar13 = (ulong)*(ushort *)
                               (ourBtlSaveDat +
                                *(short *)(iGpffff86b4 + (uint)pbVar22[iVar24 * 8 + 2] * 0x4f0 +
                                          0x120) * 0xc0 + 0x48);
            }
            iStack_360 = (int)uVar13;
            if ((long)uVar13 < 6) {
              iStack_350 = 0;
            }
            else {
              iStack_350 = 0x24;
              iStack_360 = iStack_360 + -6;
            }
            iStack_360 = iStack_360 * 0x2e;
            *puVar19 = 0x156;
            if ((*(byte *)(iVar25 + 0x3e16) == pbVar22[iVar24 * 8 + 2]) ||
               ((*(uint *)(param_1 + 100) & 3 << ((pbVar22[iVar24 * 8 + 2] & 0xf) << 1)) != 0)) {
              if ((char)pbVar22[iVar24 * 8 + 3] < '\x01') {
                puVar19[1] = 0x802020a0;
              }
              else if ((*(short *)(pbVar22 + iVar24 * 8 + 4) < 1) ||
                      ((pbVar22[iVar24 * 8] & 1) != 0)) {
                puVar19[1] = 0x80189696;
              }
              else {
                puVar19[1] = 0x80808080;
              }
            }
            else if ((char)pbVar22[iVar24 * 8 + 3] < '\x01') {
              puVar19[1] = 0x402020a0;
            }
            else if ((*(short *)(pbVar22 + iVar24 * 8 + 4) < 1) || ((pbVar22[iVar24 * 8] & 1) != 0))
            {
              puVar19[1] = 0x40189696;
            }
            else {
              puVar19[1] = 0x40808080;
            }
            uVar13 = __fixunssfdi((float)iStack_350 * 16.0);
            lVar14 = __fixunssfdi((float)iStack_360 * 16.0);
            puVar19[2] = uVar13 | lVar14 << 0x10;
            uVar13 = __fixunssfdi((float)iVar28 * 16.0);
            lVar14 = __fixunssfdi((float)iVar26 * 16.0);
            lVar15 = __fixunssfdi(uVar30);
            puVar19[3] = lVar15 << 0x20 | uVar13 | lVar14 << 0x10;
            uVar13 = __fixunssfdi(((float)iStack_350 + 36.0) * 16.0);
            lVar14 = __fixunssfdi(((float)iStack_360 + 46.0) * 16.0);
            puVar19[4] = uVar13 | lVar14 << 0x10;
            uVar13 = __fixunssfdi(((float)iVar28 + *(float *)(param_1 + 0x6c) * 36.0) * 16.0);
            lVar14 = __fixunssfdi(((float)iVar26 + *(float *)(param_1 + 0x6c) * 46.0) * 16.0);
            lVar15 = __fixunssfdi(uVar30);
            puVar19[5] = lVar15 << 0x20 | uVar13 | lVar14 << 0x10;
            puVar19 = puVar19 + 6;
            iVar21 = iVar21 + 3;
          }
          fVar27 = (float)iVar28 + *(float *)(param_1 + 0x6c) * 26.0;
        }
        *(int *)(puVar18 + 0x14) = iVar21 + 0x10000000;
        *(int *)((int)puVar18 + 0xac) = iVar21 + 0x50000000;
      }
      puVar18 = puVar19;
      if (iStack_3b0 != 0) {
        *(undefined4 *)puVar19 = 0x50000000;
        *(undefined4 *)((int)puVar19 + 4) =
             *(undefined4 *)
              (*(int *)(iGpffff86b4 + 0x42b8) +
               (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42b8) + 10) * 4 + 0xc);
        *(undefined4 *)(puVar19 + 1) = 0;
        *(undefined4 *)((int)puVar19 + 0xc) = 0;
        *(int *)(puVar19 + 2) = 0x10000000;
        *(undefined4 *)((int)puVar19 + 0x14) = 0;
        *(undefined4 *)(puVar19 + 3) = 0;
        *(undefined4 *)((int)puVar19 + 0x1c) = 0x50000000;
        puVar19[4] = 0x2000000000000001;
        puVar19[5] = 0x6e;
        puVar19[6] = 1;
        puVar19[7] = 0x3f;
        uVar16 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x42b8),1);
        puVar19[8] = uVar16;
        puVar19[9] = 0;
        fVar27 = *(float *)(param_1 + 0x6c) * 84.0 + 1792.0;
        iVar26 = (int)(*(float *)(param_1 + 0x60) + 1824.0 + *(float *)(param_1 + 0x6c) * 40.0);
        puVar19[10] = (long)iStack_3b0 | 0x6400000000008000;
        puVar19[0xb] = 0x43c310;
        puVar18 = puVar19 + 0xc;
        iVar21 = 4;
        for (iVar24 = 1; iVar28 = (int)fVar27, iVar24 < 10; iVar24 = iVar24 + 1) {
          if ((((*(byte *)(iGpffff86b4 + (uint)pbVar22[iVar24 * 8 + 2] * 0x4f0 + 0xb4) & 1) == 0) &&
              (7 < *(short *)(iGpffff86b4 + (uint)pbVar22[iVar24 * 8 + 2] * 0x4f0 + 0x120))) &&
             (*(short *)(iGpffff86b4 + (uint)pbVar22[iVar24 * 8 + 2] * 0x4f0 + 0x120) < 0xb)) {
            iVar12 = (*(short *)(iGpffff86b4 + (uint)pbVar22[iVar24 * 8 + 2] * 0x4f0 + 0x120) + -8)
                     * 0x2e;
            *puVar18 = 0x156;
            if ((*(byte *)(iVar25 + 0x3e16) == pbVar22[iVar24 * 8 + 2]) ||
               ((*(uint *)(param_1 + 100) & 3 << ((pbVar22[iVar24 * 8 + 2] & 0xf) << 1)) != 0)) {
              if ((*(short *)(pbVar22 + iVar24 * 8 + 4) < 1) || ((pbVar22[iVar24 * 8] & 1) != 0)) {
                puVar18[1] = 0x80189696;
              }
              else {
                puVar18[1] = 0x80808080;
              }
            }
            else if ((*(short *)(pbVar22 + iVar24 * 8 + 4) < 1) || ((pbVar22[iVar24 * 8] & 1) != 0))
            {
              puVar18[1] = 0x40189696;
            }
            else {
              puVar18[1] = 0x40808080;
            }
            uVar13 = __fixunssfdi(0);
            lVar14 = __fixunssfdi((float)iVar12 * 16.0);
            puVar18[2] = uVar13 | lVar14 << 0x10;
            uVar13 = __fixunssfdi((float)iVar28 * 16.0);
            lVar14 = __fixunssfdi((float)iVar26 * 16.0);
            lVar15 = __fixunssfdi(uVar30);
            puVar18[3] = lVar15 << 0x20 | uVar13 | lVar14 << 0x10;
            uVar13 = __fixunssfdi(0x44100000);
            lVar14 = __fixunssfdi(((float)iVar12 + 46.0) * 16.0);
            puVar18[4] = uVar13 | lVar14 << 0x10;
            uVar13 = __fixunssfdi(((float)iVar28 + *(float *)(param_1 + 0x6c) * 36.0) * 16.0);
            lVar14 = __fixunssfdi(((float)iVar26 + *(float *)(param_1 + 0x6c) * 46.0) * 16.0);
            lVar15 = __fixunssfdi(uVar30);
            puVar18[5] = lVar15 << 0x20 | uVar13 | lVar14 << 0x10;
            puVar18 = puVar18 + 6;
            iVar21 = iVar21 + 3;
          }
          fVar27 = (float)iVar28 + *(float *)(param_1 + 0x6c) * 26.0;
        }
        *(int *)(puVar19 + 2) = iVar21 + 0x10000000;
        *(int *)((int)puVar19 + 0x1c) = iVar21 + 0x50000000;
      }
      puVar19 = puVar18;
      if (iStack_3c0 != 0) {
        *(undefined4 *)puVar18 = 0x50000000;
        *(undefined4 *)((int)puVar18 + 4) =
             *(undefined4 *)
              (*(int *)(iGpffff86b4 + 0x42bc) +
               (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42bc) + 10) * 4 + 0xc);
        *(undefined4 *)(puVar18 + 1) = 0;
        *(undefined4 *)((int)puVar18 + 0xc) = 0;
        *(int *)(puVar18 + 2) = 0x10000000;
        *(undefined4 *)((int)puVar18 + 0x14) = 0;
        *(undefined4 *)(puVar18 + 3) = 0;
        *(undefined4 *)((int)puVar18 + 0x1c) = 0x50000000;
        puVar18[4] = 0x2000000000000001;
        puVar18[5] = 0x6e;
        puVar18[6] = 1;
        puVar18[7] = 0x3f;
        uVar16 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x42bc),1);
        puVar18[8] = uVar16;
        puVar18[9] = 0;
        fVar27 = *(float *)(param_1 + 0x6c) * 84.0 + 1792.0;
        iVar26 = (int)(*(float *)(param_1 + 0x60) + 1824.0 + *(float *)(param_1 + 0x6c) * 40.0);
        puVar18[10] = (long)iStack_3c0 | 0x6400000000008000;
        puVar18[0xb] = 0x43c310;
        puVar19 = puVar18 + 0xc;
        iVar21 = 4;
        for (iVar24 = 1; iVar28 = (int)fVar27, iVar24 < 10; iVar24 = iVar24 + 1) {
          if (((*(byte *)(iGpffff86b4 + (uint)pbVar22[iVar24 * 8 + 2] * 0x4f0 + 0xb4) & 1) == 0) &&
             (*(short *)(iGpffff86b4 + (uint)pbVar22[iVar24 * 8 + 2] * 0x4f0 + 0x120) == 0xb)) {
            *puVar19 = 0x156;
            if ((*(byte *)(iVar25 + 0x3e16) == pbVar22[iVar24 * 8 + 2]) ||
               ((*(uint *)(param_1 + 100) & 3 << ((pbVar22[iVar24 * 8 + 2] & 0xf) << 1)) != 0)) {
              if ((char)pbVar22[iVar24 * 8 + 3] < '\x01') {
                puVar19[1] = 0x802020a0;
              }
              else if ((*(short *)(pbVar22 + iVar24 * 8 + 4) < 1) ||
                      ((pbVar22[iVar24 * 8] & 1) != 0)) {
                puVar19[1] = 0x80189696;
              }
              else {
                puVar19[1] = 0x80808080;
              }
            }
            else if ((char)pbVar22[iVar24 * 8 + 3] < '\x01') {
              puVar19[1] = 0x402020a0;
            }
            else if ((*(short *)(pbVar22 + iVar24 * 8 + 4) < 1) || ((pbVar22[iVar24 * 8] & 1) != 0))
            {
              puVar19[1] = 0x40189696;
            }
            else {
              puVar19[1] = 0x40808080;
            }
            uVar13 = __fixunssfdi(0);
            lVar14 = __fixunssfdi(0);
            puVar19[2] = uVar13 | lVar14 << 0x10;
            uVar13 = __fixunssfdi((float)iVar28 * 16.0);
            lVar14 = __fixunssfdi((float)iVar26 * 16.0);
            lVar15 = __fixunssfdi(uVar30);
            puVar19[3] = lVar15 << 0x20 | uVar13 | lVar14 << 0x10;
            uVar13 = __fixunssfdi(0x44100000);
            lVar14 = __fixunssfdi(0x44380000);
            puVar19[4] = uVar13 | lVar14 << 0x10;
            uVar13 = __fixunssfdi(((float)iVar28 + *(float *)(param_1 + 0x6c) * 36.0) * 16.0);
            lVar14 = __fixunssfdi(((float)iVar26 + *(float *)(param_1 + 0x6c) * 46.0) * 16.0);
            lVar15 = __fixunssfdi(uVar30);
            puVar19[5] = lVar15 << 0x20 | uVar13 | lVar14 << 0x10;
            puVar19 = puVar19 + 6;
            iVar21 = iVar21 + 3;
          }
          fVar27 = (float)iVar28 + *(float *)(param_1 + 0x6c) * 26.0;
        }
        *(int *)(puVar18 + 2) = iVar21 + 0x10000000;
        *(int *)((int)puVar18 + 0x1c) = iVar21 + 0x50000000;
      }
      puVar18 = puVar19;
      if (iStack_3d0 != 0) {
        *(undefined4 *)puVar19 = 0x50000000;
        *(undefined4 *)((int)puVar19 + 4) =
             *(undefined4 *)
              (*(int *)(iGpffff86b4 + 0x42c0) +
               (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42c0) + 10) * 4 + 0xc);
        *(undefined4 *)(puVar19 + 1) = 0;
        *(undefined4 *)((int)puVar19 + 0xc) = 0;
        *(int *)(puVar19 + 2) = 0x10000000;
        *(undefined4 *)((int)puVar19 + 0x14) = 0;
        *(undefined4 *)(puVar19 + 3) = 0;
        *(undefined4 *)((int)puVar19 + 0x1c) = 0x50000000;
        puVar19[4] = 0x2000000000000001;
        puVar19[5] = 0x6e;
        puVar19[6] = 1;
        puVar19[7] = 0x3f;
        uVar16 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x42c0),1);
        puVar19[8] = uVar16;
        puVar19[9] = 0;
        fVar27 = *(float *)(param_1 + 0x6c) * 84.0 + 1792.0;
        iVar26 = (int)(*(float *)(param_1 + 0x60) + 1824.0 + *(float *)(param_1 + 0x6c) * 40.0);
        puVar19[10] = (long)iStack_3d0 | 0x6400000000008000;
        puVar19[0xb] = 0x43c310;
        puVar18 = puVar19 + 0xc;
        iVar21 = 4;
        for (iVar24 = 1; iVar28 = (int)fVar27, iVar24 < 10; iVar24 = iVar24 + 1) {
          if ((*(byte *)(iGpffff86b4 + (uint)pbVar22[iVar24 * 8 + 2] * 0x4f0 + 0xb4) & 1) != 0) {
            if ((long)((ulong)*(byte *)(iGpffff86b4 + (uint)pbVar22[iVar24 * 8 + 2] * 0x4f0 + 0xb0)
                      << 0x3b) < 0) {
              iStack_350 = 0x48;
              iStack_360 = 0;
            }
            else if (*(short *)(iGpffff86b4 + (uint)pbVar22[iVar24 * 8 + 2] * 0x4f0 + 0x120) < 4) {
              iStack_350 = 0;
              sVar2 = *(short *)(iGpffff86b4 + (uint)pbVar22[iVar24 * 8 + 2] * 0x4f0 + 0x120);
              iStack_360 = (sVar2 * 0x18 - (int)sVar2) * 2;
            }
            else {
              iStack_350 = 0x24;
              iStack_360 = (*(short *)(iGpffff86b4 + (uint)pbVar22[iVar24 * 8 + 2] * 0x4f0 + 0x120)
                           + -4) * 0x2e;
            }
            *puVar18 = 0x156;
            if ((*(byte *)(iVar25 + 0x3e16) == pbVar22[iVar24 * 8 + 2]) ||
               ((*(uint *)(param_1 + 100) & 3 << ((pbVar22[iVar24 * 8 + 2] & 0xf) << 1)) != 0)) {
              if ((*(short *)(pbVar22 + iVar24 * 8 + 4) < 1) || ((pbVar22[iVar24 * 8] & 1) != 0)) {
                puVar18[1] = 0x80189696;
              }
              else {
                puVar18[1] = 0x80808080;
              }
            }
            else if ((*(short *)(pbVar22 + iVar24 * 8 + 4) < 1) || ((pbVar22[iVar24 * 8] & 1) != 0))
            {
              puVar18[1] = 0x40189696;
            }
            else {
              puVar18[1] = 0x40808080;
            }
            uVar13 = __fixunssfdi((float)iStack_350 * 16.0);
            lVar14 = __fixunssfdi((float)iStack_360 * 16.0);
            puVar18[2] = uVar13 | lVar14 << 0x10;
            uVar13 = __fixunssfdi((float)iVar28 * 16.0);
            lVar14 = __fixunssfdi((float)iVar26 * 16.0);
            lVar15 = __fixunssfdi(uVar30);
            puVar18[3] = lVar15 << 0x20 | uVar13 | lVar14 << 0x10;
            uVar13 = __fixunssfdi(((float)iStack_350 + 36.0) * 16.0);
            lVar14 = __fixunssfdi(((float)iStack_360 + 46.0) * 16.0);
            puVar18[4] = uVar13 | lVar14 << 0x10;
            uVar13 = __fixunssfdi(((float)iVar28 + *(float *)(param_1 + 0x6c) * 36.0) * 16.0);
            lVar14 = __fixunssfdi(((float)iVar26 + *(float *)(param_1 + 0x6c) * 46.0) * 16.0);
            lVar15 = __fixunssfdi(uVar30);
            puVar18[5] = lVar15 << 0x20 | uVar13 | lVar14 << 0x10;
            puVar18 = puVar18 + 6;
            iVar21 = iVar21 + 3;
          }
          fVar27 = (float)iVar28 + *(float *)(param_1 + 0x6c) * 26.0;
        }
        *(int *)(puVar19 + 2) = iVar21 + 0x10000000;
        *(int *)((int)puVar19 + 0x1c) = iVar21 + 0x50000000;
      }
      puVar19 = puVar18;
      if (iStack_400 != 0) {
        *(undefined4 *)puVar18 = 0x50000000;
        *(undefined4 *)((int)puVar18 + 4) =
             *(undefined4 *)
              (*(int *)(iGpffff86b4 + 0x4264) +
               (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x4264) + 10) * 4 + 0xc);
        *(undefined4 *)(puVar18 + 1) = 0;
        *(undefined4 *)((int)puVar18 + 0xc) = 0;
        *(int *)(puVar18 + 2) = 0x10000000;
        *(undefined4 *)((int)puVar18 + 0x14) = 0;
        *(undefined4 *)(puVar18 + 3) = 0;
        *(undefined4 *)((int)puVar18 + 0x1c) = 0x50000000;
        puVar18[4] = 0x2000000000000001;
        puVar18[5] = 0x6e;
        puVar18[6] = 1;
        puVar18[7] = 0x3f;
        uVar16 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x4264),1);
        puVar18[8] = uVar16;
        puVar18[9] = 0;
        fVar27 = *(float *)(param_1 + 0x6c) * 84.0 + 1792.0;
        iVar24 = (int)(*(float *)(param_1 + 0x60) + 1824.0 + *(float *)(param_1 + 0x6c) * 40.0);
        puVar18[10] = (long)iStack_400 | 0x6400000000008000;
        puVar18[0xb] = 0x43c310;
        puVar19 = puVar18 + 0xc;
        iVar25 = 4;
        for (iVar21 = 1; iVar26 = (int)fVar27, iVar21 < 10; iVar21 = iVar21 + 1) {
          if ((*(uint *)(param_1 + 100) & 3 << ((pbVar22[iVar21 * 8 + 2] & 0xf) << 1)) != 0) {
            *puVar19 = 0x156;
            uVar11 = *(uint *)(param_1 + 100) >> ((pbVar22[iVar21 * 8 + 2] & 0xf) << 1) & 3;
            if (uVar11 == 3) {
              puVar19[1] = 0x80015a7d;
            }
            else if (uVar11 == 2) {
              puVar19[1] = 0x80000080;
            }
            else if (uVar11 == 1) {
              puVar19[1] = 0x805a7d01;
            }
            puVar19[2] = 0x250;
            uVar13 = __fixunssfdi((float)iVar26 * 16.0);
            lVar14 = __fixunssfdi((float)iVar24 * 16.0);
            lVar15 = __fixunssfdi(uVar30);
            puVar19[3] = lVar15 << 0x20 | uVar13 | lVar14 << 0x10;
            puVar19[4] = 0x2e00460;
            uVar13 = __fixunssfdi(((float)iVar26 + *(float *)(param_1 + 0x6c) * 33.0) * 16.0);
            lVar14 = __fixunssfdi(((float)iVar24 + *(float *)(param_1 + 0x6c) * 46.0) * 16.0);
            lVar15 = __fixunssfdi(uVar30);
            puVar19[5] = lVar15 << 0x20 | uVar13 | lVar14 << 0x10;
            puVar19 = puVar19 + 6;
            iVar25 = iVar25 + 3;
          }
          fVar27 = (float)iVar26 + *(float *)(param_1 + 0x6c) * 26.0;
        }
        *(int *)(puVar18 + 2) = iVar25 + 0x10000000;
        *(int *)((int)puVar18 + 0x1c) = iVar25 + 0x50000000;
      }
      *(undefined4 *)puVar19 = 0x50000000;
      *(undefined4 *)((int)puVar19 + 4) =
           *(undefined4 *)
            (*(int *)(iGpffff86b4 + 0x4260) +
             (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x4260) + 10) * 4 + 0xc);
      *(undefined4 *)(puVar19 + 1) = 0;
      *(undefined4 *)((int)puVar19 + 0xc) = 0;
      *(int *)(puVar19 + 2) = 0x10000000;
      *(undefined4 *)((int)puVar19 + 0x14) = 0;
      *(undefined4 *)(puVar19 + 3) = 0;
      *(undefined4 *)((int)puVar19 + 0x1c) = 0x50000000;
      puVar19[4] = 0x2000000000000001;
      puVar19[5] = 0x6e;
      puVar19[6] = 1;
      puVar19[7] = 0x3f;
      uVar16 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x4260),1);
      puVar19[8] = uVar16;
      puVar19[9] = 0;
      puVar20 = puVar19 + 10;
      if (iStack_3e0 == 0) {
        *puVar20 = 0x6400000000000003;
      }
      else {
        *puVar20 = (long)(iStack_3e0 + 4) | 0x6400000000000000;
      }
      puVar19[0xb] = 0x43c310;
      iVar25 = (int)(*(float *)(param_1 + 0x6c) * 79.0 + 1792.0);
      iVar21 = (int)(*(float *)(param_1 + 0x60) + 1824.0 + *(float *)(param_1 + 0x6c) * 25.0);
      puVar19[0xc] = 0x156;
      puVar19[0xd] = 0x80808080;
      puVar19[0xe] = 0;
      uVar13 = __fixunssfdi((float)iVar25 * 16.0);
      lVar14 = __fixunssfdi((float)iVar21 * 16.0);
      lVar15 = __fixunssfdi(uVar30);
      puVar19[0xf] = lVar15 << 0x20 | uVar13 | lVar14 << 0x10;
      uVar13 = __fixunssfdi((float)*(ushort *)(*(int *)(iGpffff86b4 + 0x4260) + 2) * 16.0);
      puVar19[0x10] = uVar13 | 0x1200000;
      uVar13 = __fixunssfdi(((float)iVar25 +
                               (float)*(ushort *)(*(int *)(iGpffff86b4 + 0x4260) + 2) *
                               *(float *)(param_1 + 0x6c)) * 16.0);
      lVar14 = __fixunssfdi(((float)iVar21 + *(float *)(param_1 + 0x6c) * 18.0) * 16.0);
      lVar15 = __fixunssfdi(uVar30);
      puVar19[0x11] = lVar15 << 0x20 | uVar13 | lVar14 << 0x10;
      iVar25 = (int)(*(float *)(param_1 + 0x6c) * 52.0 + 1792.0);
      iVar21 = (int)(*(float *)(param_1 + 0x60) + 1824.0 + *(float *)(param_1 + 0x6c) * 75.0);
      puVar19[0x12] = 0x156;
      puVar19[0x13] = 0x80808080;
      puVar19[0x14] = 0x1200000;
      uVar13 = __fixunssfdi((float)iVar25 * 16.0);
      lVar14 = __fixunssfdi((float)iVar21 * 16.0);
      lVar15 = __fixunssfdi(uVar30);
      puVar19[0x15] = lVar15 << 0x20 | uVar13 | lVar14 << 0x10;
      puVar19[0x16] = 0x3200280;
      uVar13 = __fixunssfdi(((float)iVar25 + *(float *)(param_1 + 0x6c) * 40.0) * 16.0);
      lVar14 = __fixunssfdi(((float)iVar21 + *(float *)(param_1 + 0x6c) * 32.0) * 16.0);
      lVar15 = __fixunssfdi(uVar30);
      puVar19[0x17] = lVar15 << 0x20 | uVar13 | lVar14 << 0x10;
      if (iStack_3e0 == 0) {
        iVar25 = (int)(*(float *)(param_1 + 0x6c) * 92.0 + 1792.0);
        iVar21 = (int)(*(float *)(param_1 + 0x60) + 1824.0 + *(float *)(param_1 + 0x6c) * 75.0);
        puVar19[0x18] = 0x156;
        puVar19[0x19] = 0x80808080;
        puVar19[0x1a] = 0x12003c8;
        uVar13 = __fixunssfdi((float)iVar25 * 16.0);
        lVar14 = __fixunssfdi((float)iVar21 * 16.0);
        lVar15 = __fixunssfdi(uVar30);
        puVar19[0x1b] = lVar15 << 0x20 | uVar13 | lVar14 << 0x10;
        puVar19[0x1c] = 0x32004c0;
        uVar13 = __fixunssfdi(((float)iVar25 + *(float *)(param_1 + 0x6c) * 16.0) * 16.0);
        lVar14 = __fixunssfdi(((float)iVar21 + *(float *)(param_1 + 0x6c) * 32.0) * 16.0);
        lVar15 = __fixunssfdi(uVar30);
        puVar19[0x1d] = lVar15 << 0x20 | uVar13 | lVar14 << 0x10;
        puVar18 = puVar19 + 0x1e;
        iVar25 = 0xd;
      }
      else {
        for (uVar11 = 9; (0 < (int)uVar11 && ((uStack_3f0 & 1 << (uVar11 & 0x1f)) == 0));
            uVar11 = uVar11 - 1) {
        }
        iVar25 = (int)(*(float *)(param_1 + 0x6c) * 92.0 + 1792.0);
        iVar21 = (int)(*(float *)(param_1 + 0x60) + 1824.0 + *(float *)(param_1 + 0x6c) * 75.0);
        iVar24 = (int)((((float)(int)(uVar11 - 1) * 26.0 + 17.0) - 4.0) * *(float *)(param_1 + 0x6c)
                      );
        puVar19[0x18] = 0x156;
        puVar19[0x19] = 0x80808080;
        puVar19[0x1a] = 0x1200508;
        uVar13 = __fixunssfdi((float)iVar25 * 16.0);
        lVar14 = __fixunssfdi((float)iVar21 * 16.0);
        lVar15 = __fixunssfdi(uVar30);
        puVar19[0x1b] = lVar15 << 0x20 | uVar13 | lVar14 << 0x10;
        puVar19[0x1c] = 0x3200600;
        lVar14 = __fixunssfdi(((float)iVar21 + *(float *)(param_1 + 0x6c) * 32.0) * 16.0);
        uVar13 = __fixunssfdi((float)(iVar25 + iVar24) * 16.0);
        lVar15 = __fixunssfdi(uVar30);
        puVar19[0x1d] = lVar15 << 0x20 | uVar13 | lVar14 << 0x10;
        iVar25 = (int)(*(float *)(param_1 + 0x6c) * 92.0 + 1792.0 + (float)iVar24);
        iVar21 = (int)(*(float *)(param_1 + 0x60) + 1824.0 + *(float *)(param_1 + 0x6c) * 75.0);
        puVar19[0x1e] = 0x156;
        puVar19[0x1f] = 0x80808080;
        puVar19[0x20] = 0x12003c8;
        uVar13 = __fixunssfdi((float)iVar25 * 16.0);
        lVar14 = __fixunssfdi((float)iVar21 * 16.0);
        lVar15 = __fixunssfdi(uVar30);
        puVar19[0x21] = lVar15 << 0x20 | uVar13 | lVar14 << 0x10;
        puVar19[0x22] = 0x32004c0;
        uVar13 = __fixunssfdi(((float)iVar25 + *(float *)(param_1 + 0x6c) * 16.0) * 16.0);
        lVar14 = __fixunssfdi(((float)iVar21 + *(float *)(param_1 + 0x6c) * 32.0) * 16.0);
        lVar15 = __fixunssfdi(uVar30);
        puVar19[0x23] = lVar15 << 0x20 | uVar13 | lVar14 << 0x10;
        puVar18 = puVar19 + 0x24;
        iVar25 = 0x10;
        fVar27 = *(float *)(param_1 + 0x6c) * 88.0 + 1792.0;
        iVar21 = (int)(*(float *)(param_1 + 0x60) + 1824.0 + *(float *)(param_1 + 0x6c) * 75.0);
        for (uVar11 = 1; iVar24 = (int)fVar27, (int)uVar11 < 10; uVar11 = uVar11 + 1) {
          if ((uStack_3f0 & 1 << (uVar11 & 0x1f)) != 0) {
            *puVar18 = 0x156;
            puVar18[1] = 0x80808080;
            puVar18[2] = 0x12002a0;
            uVar13 = __fixunssfdi((float)iVar24 * 16.0);
            lVar14 = __fixunssfdi((float)iVar21 * 16.0);
            lVar15 = __fixunssfdi(uVar30);
            puVar18[3] = lVar15 << 0x20 | uVar13 | lVar14 << 0x10;
            puVar18[4] = 0x32003b0;
            uVar13 = __fixunssfdi(((float)iVar24 + *(float *)(param_1 + 0x6c) * 17.0) * 16.0);
            lVar14 = __fixunssfdi(((float)iVar21 + *(float *)(param_1 + 0x6c) * 32.0) * 16.0);
            lVar15 = __fixunssfdi(uVar30);
            puVar18[5] = lVar15 << 0x20 | uVar13 | lVar14 << 0x10;
            puVar18 = puVar18 + 6;
            iVar25 = iVar25 + 3;
          }
          fVar27 = (float)iVar24 + *(float *)(param_1 + 0x6c) * 26.0;
        }
      }
      *(int *)(puVar19 + 2) = iVar25 + 0x10000000;
      *(int *)((int)puVar19 + 0x1c) = iVar25 + 0x50000000;
      *puVar20 = *puVar20 | 0x8000;
      *(undefined8 **)(param_1 + 0x54) = puVar18;
      *(undefined8 **)(param_1 + uVar23 * 4 + 0x58) = puVar18;
      *(uint *)(param_1 + 0x44) = uVar23;
      if (uVar23 == 0) {
        *(uint *)(param_1 + 0x70) = *(uint *)(param_1 + 0x70) & 0xfffffffe;
      }
      else {
        *(uint *)(param_1 + 0x70) = *(uint *)(param_1 + 0x70) & 0xfffffffd;
      }
      uVar30 = *(undefined4 *)(param_1 + *(int *)(param_1 + 0x44) * 4 + 0x18);
    }
  }
  return uVar30;
}

/* ---------------------------------------------------------------------------
 * JP: 0x004f0af0  TurnOrderOpen__13TurnOrderDispFv
 * C++: TurnOrderDisp::TurnOrderOpen()
 * size: 0x50 bytes
 * --------------------------------------------------------------------------- */
void TurnOrderOpen__13TurnOrderDispFv(int param_1)

{
  *(undefined4 *)(param_1 + 0x38) = 1;
  *(undefined4 *)(param_1 + 0x3c) = 0;
  *(float *)(param_1 + 0x60) = *(float *)(param_1 + 0x6c) * -96.0;
  *(undefined4 *)(param_1 + 0x70) = 3;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x004f0b40  TurnOrderClose__13TurnOrderDispFv
 * C++: TurnOrderDisp::TurnOrderClose()
 * size: 0x40 bytes
 * --------------------------------------------------------------------------- */
void TurnOrderClose__13TurnOrderDispFv(int param_1)

{
  *(undefined4 *)(param_1 + 0x38) = 3;
  *(undefined4 *)(param_1 + 0x3c) = 0;
  *(undefined4 *)(param_1 + 0x60) = 0;
  *(undefined4 *)(param_1 + 0x70) = 3;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x004f0b80  SetSelectChr__13TurnOrderDispFii
 * C++: TurnOrderDisp::SetSelectChr(int, int)
 * size: 0x7c bytes
 * --------------------------------------------------------------------------- */
void SetSelectChr__13TurnOrderDispFii(int param_1,uint param_2,int param_3)

{
  *(uint *)(param_1 + 100) =
       *(int *)(param_1 + 100) - (*(uint *)(param_1 + 100) & 3 << ((param_2 & 0xf) << 1));
  *(uint *)(param_1 + 100) = *(uint *)(param_1 + 100) | param_3 << ((param_2 & 0xf) << 1);
  *(undefined4 *)(param_1 + 0x70) = 3;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b350  getPacket__13TurnOrderDispFv
 * C++: TurnOrderDisp::getPacket()
 * size: 0x28 bytes
 * --------------------------------------------------------------------------- */
void getPacket__13TurnOrderDispFv(undefined4 param_1)

{
  MakePacket__13TurnOrderDispFv(param_1);
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b3e0  @24@getPacket__13TurnOrderDispFv
 * C++: @24@getPacket__13TurnOrderDispFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
void _24_getPacket__13TurnOrderDispFv(int param_1)

{
  MakePacket__13TurnOrderDispFv(param_1 + -0x18);
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b3f0  @24@__dt__13TurnOrderDispFv
 * C++: @24@__dt__13TurnOrderDispFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int * _24___dt__13TurnOrderDispFv(int *param_1,short param_2)

{
  int *piVar1;
  
  piVar1 = param_1 + -6;
  if (piVar1 != (int *)0x0) {
    param_1[-1] = 0x40a5b0;
    param_1[4] = 0x40a5c0;
    param_1[7] = 0x40a5d0;
    if (*param_1 != 0) {
      __dla__FPv(*param_1);
    }
    if (param_1[1] != 0) {
      __dla__FPv(param_1[1]);
    }
    if (piVar1 != (int *)0xffffffd4) {
      param_1[7] = 0x4049f0;
    }
    __dt__8VIF1PrimFv(param_1,0);
    __dt__7CPolObjFv(piVar1,0);
    if (0 < param_2) {
      __dl__FPv(piVar1);
    }
  }
  return piVar1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b400  @44@__dt__13TurnOrderDispFv
 * C++: @44@__dt__13TurnOrderDispFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int _44___dt__13TurnOrderDispFv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x2c;
  if (iVar1 != 0) {
    *(undefined4 *)(param_1 + -0x18) = 0x40a5b0;
    *(undefined4 *)(param_1 + -4) = 0x40a5c0;
    *(undefined4 *)(param_1 + 8) = 0x40a5d0;
    if (*(int *)(param_1 + -0x14) != 0) {
      __dla__FPv(*(undefined4 *)(param_1 + -0x14));
    }
    if (*(int *)(param_1 + -0x10) != 0) {
      __dla__FPv(*(undefined4 *)(param_1 + -0x10));
    }
    if (iVar1 != -0x2c) {
      *(undefined4 *)(param_1 + 8) = 0x4049f0;
    }
    __dt__8VIF1PrimFv(param_1 + -0x14,0);
    __dt__7CPolObjFv(iVar1,0);
    if (0 < param_2) {
      __dl__FPv(iVar1);
    }
  }
  return iVar1;
}

