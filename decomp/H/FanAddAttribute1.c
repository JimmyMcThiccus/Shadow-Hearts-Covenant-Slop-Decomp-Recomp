/* decomp/H/FanAddAttribute1.c — cleaned Ghidra output (SH2JP_BATTLE.BIN, JP Furokuban, base 0x00430a00).
 * 8 function(s). Types: see types.h. Names/gp globals resolved from symbols/SLPM_602.19.syms. */
#include "types.h"

/* ---------------------------------------------------------------------------
 * JP: 0x00529920  __ct__16FanAddAttribute1Fiii
 * C++: FanAddAttribute1::__ct(int, int, int)
 * size: 0x208 bytes
 * --------------------------------------------------------------------------- */
int __ct__16FanAddAttribute1Fiii
              (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  int iVar1;
  undefined4 *puVar2;
  
  __ct__6BtlEffFii(param_1,param_2,param_3);
  *(undefined4 *)(param_1 + 0x14) = 0x409d40;
  *(undefined4 *)(param_1 + 0x28) = 0x409d50;
  *(undefined4 *)(param_1 + 0x34) = 0x409d60;
  puVar2 = (undefined4 *)(param_1 + 0x70);
  do {
    *puVar2 = in_zero_lo;
    puVar2[1] = in_zero_hi;
    puVar2[2] = in_zero_udw;
    puVar2[3] = in_register_0000000c;
    puVar2 = puVar2 + 4;
  } while (puVar2 != (undefined4 *)(param_1 + 0xf0));
  puVar2 = (undefined4 *)(param_1 + 0x1c0);
  do {
    *puVar2 = in_zero_lo;
    puVar2[1] = in_zero_hi;
    puVar2[2] = in_zero_udw;
    puVar2[3] = in_register_0000000c;
    puVar2 = puVar2 + 4;
  } while (puVar2 != (undefined4 *)(param_1 + 0x340));
  *(undefined4 *)(param_1 + 0x40) = 0;
  *(undefined4 *)(param_1 + 0x44) = param_2;
  *(undefined4 *)(param_1 + 0x48) = param_3;
  *(undefined4 *)(param_1 + 0x4c) = 6;
  *(undefined4 *)(param_1 + 0x5c) = 0;
  *(undefined4 *)(param_1 + 0x60) = param_4;
  *(undefined4 *)(param_1 + 0xf0) = 0;
  *(undefined4 *)(param_1 + 0xf4) = 0;
  *(undefined4 *)(param_1 + 0xf8) = 0;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  *(undefined4 *)(param_1 + 0x18) = 0;
  for (iVar1 = 0; iVar1 < 0x18; iVar1 = iVar1 + 1) {
    *(undefined2 *)(param_1 + iVar1 * 2 + 0xfc) = 0;
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
 * JP: 0x00529b30  __dt__16FanAddAttribute1Fv
 * C++: FanAddAttribute1::__dt()
 * size: 0x154 bytes
 * --------------------------------------------------------------------------- */
int __dt__16FanAddAttribute1Fv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x14) = 0x409d40;
    *(undefined4 *)(param_1 + 0x28) = 0x409d50;
    *(undefined4 *)(param_1 + 0x34) = 0x409d60;
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
 * JP: 0x00529c90  Destruct__16FanAddAttribute1Fv
 * C++: FanAddAttribute1::Destruct()
 * size: 0xcc bytes
 * --------------------------------------------------------------------------- */
void Destruct__16FanAddAttribute1Fv(int param_1)

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
 * JP: 0x00529d60  Polling__16FanAddAttribute1Fv
 * C++: FanAddAttribute1::Polling()
 * size: 0x14b8 bytes
 * --------------------------------------------------------------------------- */
undefined8 Polling__16FanAddAttribute1Fv(int param_1)

{
  short sVar1;
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
  float in_zero_lo;
  float in_zero_hi;
  float in_zero_udw;
  undefined4 in_register_0000000c;
  int iVar26;
  undefined8 *puVar27;
  int iVar28;
  float fVar29;
  float fVar30;
  undefined1 auVar31 [16];
  undefined1 auVar32 [16];
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
  undefined1 auStack_350 [16];
  undefined1 auStack_340 [16];
  undefined1 auStack_330 [16];
  undefined1 auStack_320 [16];
  undefined1 auStack_310 [16];
  undefined1 auStack_300 [16];
  undefined1 auStack_2f0 [16];
  undefined1 auStack_2e0 [16];
  undefined1 auStack_2d0 [16];
  undefined1 auStack_2c0 [16];
  undefined1 auStack_2b0 [16];
  undefined1 auStack_2a0 [16];
  undefined1 auStack_290 [16];
  undefined1 auStack_280 [16];
  undefined1 auStack_270 [8];
  undefined4 uStack_268;
  undefined4 uStack_264;
  undefined1 auStack_260 [8];
  float fStack_258;
  undefined4 uStack_254;
  undefined1 auStack_250 [8];
  float fStack_248;
  undefined4 uStack_244;
  undefined1 auStack_240 [8];
  float fStack_238;
  undefined4 uStack_234;
  undefined1 auStack_230 [8];
  float fStack_228;
  undefined4 uStack_224;
  undefined1 auStack_220 [8];
  float fStack_218;
  undefined4 uStack_214;
  undefined1 auStack_210 [8];
  float fStack_208;
  undefined4 uStack_204;
  undefined1 auStack_200 [8];
  float fStack_1f8;
  undefined4 uStack_1f4;
  undefined1 auStack_1f0 [8];
  float fStack_1e8;
  undefined4 uStack_1e4;
  undefined1 auStack_1e0 [8];
  float fStack_1d8;
  undefined4 uStack_1d4;
  undefined1 auStack_1d0 [8];
  float fStack_1c8;
  undefined4 uStack_1c4;
  undefined1 auStack_1c0 [16];
  undefined1 auStack_1b0 [8];
  undefined4 uStack_1a8;
  undefined4 uStack_1a4;
  undefined1 auStack_1a0 [8];
  float fStack_198;
  undefined4 uStack_194;
  undefined1 auStack_190 [8];
  float fStack_188;
  undefined4 uStack_184;
  undefined1 auStack_180 [8];
  float fStack_178;
  undefined4 uStack_174;
  undefined1 auStack_170 [8];
  float fStack_168;
  undefined4 uStack_164;
  undefined1 auStack_160 [8];
  float fStack_158;
  undefined4 uStack_154;
  undefined1 auStack_150 [8];
  float fStack_148;
  undefined4 uStack_144;
  undefined1 auStack_140 [8];
  float fStack_138;
  undefined4 uStack_134;
  undefined1 auStack_130 [8];
  float fStack_128;
  undefined4 uStack_124;
  undefined1 auStack_120 [8];
  float fStack_118;
  undefined4 uStack_114;
  undefined1 auStack_110 [8];
  float fStack_108;
  undefined4 uStack_104;
  undefined1 auStack_100 [16];
  undefined1 auStack_f0 [16];
  undefined1 auStack_e0 [8];
  undefined4 uStack_d8;
  undefined4 uStack_d4;
  float fStack_d0;
  float fStack_cc;
  float fStack_c8;
  undefined4 uStack_c4;
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
  float fStack_80;
  float fStack_7c;
  float fStack_78;
  undefined4 uStack_74;
  float fStack_70;
  float fStack_6c;
  float fStack_68;
  undefined4 uStack_64;
  float fStack_60;
  float fStack_5c;
  float fStack_58;
  undefined4 uStack_54;
  float fStack_50;
  float fStack_4c;
  float fStack_48;
  float fStack_40;
  float fStack_3c;
  float fStack_38;
  float fStack_30;
  float fStack_2c;
  float fStack_28;
  float fStack_20;
  float fStack_1c;
  float fStack_18;
  float fStack_10;
  float fStack_c;
  float fStack_8;
  
  fVar30 = *(float *)(iGpffff86b4 + 0x38);
  if ((*(byte *)(iGpffff86b4 + 0x24) & 1) != 0) {
    fVar30 = 0.0;
  }
  *(float *)(param_1 + 0xf8) = *(float *)(param_1 + 0xf8) + fVar30 * 6.2831855 * 0.75;
  if (3.1415927 <= *(float *)(param_1 + 0xf8)) {
    *(float *)(param_1 + 0xf8) = *(float *)(param_1 + 0xf8) - 6.2831855;
  }
  if (((*(int *)(param_1 + 0x5c) != 1) && (*(int *)(param_1 + 0x5c) == 0)) &&
     (*(float *)(param_1 + 0xf0) = *(float *)(param_1 + 0xf0) + fVar30 * 2.0,
     1.0 <= *(float *)(param_1 + 0xf0))) {
    *(undefined4 *)(param_1 + 0xf0) = 0x3f800000;
    *(undefined4 *)(param_1 + 0x5c) = 1;
  }
  iVar28 = *(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x144) +
                            0x52c) + 0xe4);
  fStack_80 = in_zero_lo;
  fStack_7c = in_zero_hi;
  fStack_78 = in_zero_udw;
  uStack_74 = in_register_0000000c;
  fStack_70 = in_zero_lo;
  fStack_6c = in_zero_hi;
  fStack_68 = in_zero_udw;
  uStack_64 = in_register_0000000c;
  fStack_60 = in_zero_lo;
  fStack_5c = in_zero_hi;
  fStack_58 = in_zero_udw;
  uStack_54 = in_register_0000000c;
  fStack_50 = in_zero_lo;
  fStack_4c = in_zero_hi;
  fStack_48 = in_zero_udw;
  fStack_40 = in_zero_lo;
  fStack_3c = in_zero_hi;
  fStack_38 = in_zero_udw;
  fStack_30 = in_zero_lo;
  fStack_2c = in_zero_hi;
  fStack_28 = in_zero_udw;
  fStack_20 = in_zero_lo;
  fStack_1c = in_zero_hi;
  fStack_18 = in_zero_udw;
  fStack_10 = in_zero_lo;
  fStack_c = in_zero_hi;
  fStack_8 = in_zero_udw;
  __ct__6MatrixFRC6Matrix(&uStack_c0,
                  *(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x144)
                                   + 0x52c) + 0x30) + (uint)*(byte *)(iVar28 + 0x110) * 0x1f0 +
                  (bGpffff8340 & 1) * 0x40);
  RotTransVector(&fStack_80,iVar28 + 0x120,&uStack_c0,8);
  *(float *)(param_1 + 0x70) = (fStack_30 + fStack_40 + fStack_60 + fStack_50) / 4.0;
  *(float *)(param_1 + 0x74) = (fStack_2c + fStack_3c + fStack_5c + fStack_4c) / 4.0;
  *(float *)(param_1 + 0x78) = (fStack_28 + fStack_38 + fStack_58 + fStack_48) / 4.0;
  *(undefined4 *)(param_1 + 0x7c) = 0x3f800000;
  *(float *)(param_1 + 0x80) = (fStack_10 + fStack_20 + fStack_80 + fStack_70) / 4.0;
  *(float *)(param_1 + 0x84) = (fStack_c + fStack_1c + fStack_7c + fStack_6c) / 4.0;
  *(float *)(param_1 + 0x88) = (fStack_8 + fStack_18 + fStack_78 + fStack_68) / 4.0;
  *(undefined4 *)(param_1 + 0x8c) = 0x3f800000;
  iVar28 = *(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x144) +
                            0x52c) + 0xe4);
  puVar27 = (undefined8 *)
            (*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x144) +
                              0x52c) + 0x30) + (uint)*(byte *)(iVar28 + 0x220) * 0x1f0 +
            (bGpffff8340 & 1) * 0x40);
  uStack_b8 = *(undefined4 *)(puVar27 + 1);
  uStack_b4 = *(undefined4 *)((int)puVar27 + 0xc);
  uStack_c0 = (undefined4)*puVar27;
  uStack_bc = (undefined4)((ulong)*puVar27 >> 0x20);
  uStack_b0 = *(undefined4 *)(puVar27 + 2);
  uStack_ac = *(undefined4 *)((int)puVar27 + 0x14);
  uStack_a8 = *(undefined4 *)(puVar27 + 3);
  uStack_a4 = *(undefined4 *)((int)puVar27 + 0x1c);
  uStack_a0 = *(undefined4 *)(puVar27 + 4);
  uStack_9c = *(undefined4 *)((int)puVar27 + 0x24);
  uStack_98 = *(undefined4 *)(puVar27 + 5);
  uStack_94 = *(undefined4 *)((int)puVar27 + 0x2c);
  uStack_90 = *(undefined4 *)(puVar27 + 6);
  uStack_8c = *(undefined4 *)((int)puVar27 + 0x34);
  uStack_88 = *(undefined4 *)(puVar27 + 7);
  uStack_84 = *(undefined4 *)((int)puVar27 + 0x3c);
  RotTransVector(&fStack_80,iVar28 + 0x230,&uStack_c0,8);
  *(float *)(param_1 + 0x90) = (fStack_80 + fStack_20) / 2.0;
  *(float *)(param_1 + 0x94) = (fStack_7c + fStack_1c) / 2.0;
  *(float *)(param_1 + 0x98) = (fStack_78 + fStack_18) / 2.0;
  *(undefined4 *)(param_1 + 0x9c) = 0x3f800000;
  *(float *)(param_1 + 0xa0) = (fStack_50 + fStack_30) / 2.0;
  *(float *)(param_1 + 0xa4) = (fStack_4c + fStack_2c) / 2.0;
  *(float *)(param_1 + 0xa8) = (fStack_48 + fStack_28) / 2.0;
  *(undefined4 *)(param_1 + 0xac) = 0x3f800000;
  iVar28 = *(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x144) +
                            0x52c) + 0xe4);
  puVar27 = (undefined8 *)
            (*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x144) +
                              0x52c) + 0x30) + (uint)*(byte *)(iVar28 + 0x440) * 0x1f0 +
            (bGpffff8340 & 1) * 0x40);
  uStack_b8 = *(undefined4 *)(puVar27 + 1);
  uStack_b4 = *(undefined4 *)((int)puVar27 + 0xc);
  uStack_c0 = (undefined4)*puVar27;
  uStack_bc = (undefined4)((ulong)*puVar27 >> 0x20);
  uStack_b0 = *(undefined4 *)(puVar27 + 2);
  uStack_ac = *(undefined4 *)((int)puVar27 + 0x14);
  uStack_a8 = *(undefined4 *)(puVar27 + 3);
  uStack_a4 = *(undefined4 *)((int)puVar27 + 0x1c);
  uStack_a0 = *(undefined4 *)(puVar27 + 4);
  uStack_9c = *(undefined4 *)((int)puVar27 + 0x24);
  uStack_98 = *(undefined4 *)(puVar27 + 5);
  uStack_94 = *(undefined4 *)((int)puVar27 + 0x2c);
  uStack_90 = *(undefined4 *)(puVar27 + 6);
  uStack_8c = *(undefined4 *)((int)puVar27 + 0x34);
  uStack_88 = *(undefined4 *)(puVar27 + 7);
  uStack_84 = *(undefined4 *)((int)puVar27 + 0x3c);
  RotTransVector(&fStack_80,iVar28 + 0x450,&uStack_c0,8);
  *(float *)(param_1 + 0xb0) = (fStack_60 + fStack_40) / 2.0;
  *(float *)(param_1 + 0xb4) = (fStack_5c + fStack_3c) / 2.0;
  *(float *)(param_1 + 0xb8) = (fStack_58 + fStack_38) / 2.0;
  *(undefined4 *)(param_1 + 0xbc) = 0x3f800000;
  iVar28 = *(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x144) +
                            0x52c) + 0xe4);
  puVar27 = (undefined8 *)
            (*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x144) +
                              0x52c) + 0x30) + (uint)*(byte *)(iVar28 + 0x550) * 0x1f0 +
            (bGpffff8340 & 1) * 0x40);
  uStack_b8 = *(undefined4 *)(puVar27 + 1);
  uStack_b4 = *(undefined4 *)((int)puVar27 + 0xc);
  uStack_c0 = (undefined4)*puVar27;
  uStack_bc = (undefined4)((ulong)*puVar27 >> 0x20);
  uStack_b0 = *(undefined4 *)(puVar27 + 2);
  uStack_ac = *(undefined4 *)((int)puVar27 + 0x14);
  uStack_a8 = *(undefined4 *)(puVar27 + 3);
  uStack_a4 = *(undefined4 *)((int)puVar27 + 0x1c);
  uStack_a0 = *(undefined4 *)(puVar27 + 4);
  uStack_9c = *(undefined4 *)((int)puVar27 + 0x24);
  uStack_98 = *(undefined4 *)(puVar27 + 5);
  uStack_94 = *(undefined4 *)((int)puVar27 + 0x2c);
  uStack_90 = *(undefined4 *)(puVar27 + 6);
  uStack_8c = *(undefined4 *)((int)puVar27 + 0x34);
  uStack_88 = *(undefined4 *)(puVar27 + 7);
  uStack_84 = *(undefined4 *)((int)puVar27 + 0x3c);
  RotTransVector(&fStack_80,iVar28 + 0x560,&uStack_c0,8);
  *(float *)(param_1 + 0xc0) = (fStack_60 + fStack_40) / 2.0;
  *(float *)(param_1 + 0xc4) = (fStack_5c + fStack_3c) / 2.0;
  *(float *)(param_1 + 200) = (fStack_58 + fStack_38) / 2.0;
  *(undefined4 *)(param_1 + 0xcc) = 0x3f800000;
  iVar28 = *(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x144) +
                            0x52c) + 0xe4);
  puVar27 = (undefined8 *)
            (*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x144) +
                              0x52c) + 0x30) + (uint)*(byte *)(iVar28 + 0x660) * 0x1f0 +
            (bGpffff8340 & 1) * 0x40);
  uStack_b8 = *(undefined4 *)(puVar27 + 1);
  uStack_b4 = *(undefined4 *)((int)puVar27 + 0xc);
  uStack_c0 = (undefined4)*puVar27;
  uStack_bc = (undefined4)((ulong)*puVar27 >> 0x20);
  uStack_b0 = *(undefined4 *)(puVar27 + 2);
  uStack_ac = *(undefined4 *)((int)puVar27 + 0x14);
  uStack_a8 = *(undefined4 *)(puVar27 + 3);
  uStack_a4 = *(undefined4 *)((int)puVar27 + 0x1c);
  uStack_a0 = *(undefined4 *)(puVar27 + 4);
  uStack_9c = *(undefined4 *)((int)puVar27 + 0x24);
  uStack_98 = *(undefined4 *)(puVar27 + 5);
  uStack_94 = *(undefined4 *)((int)puVar27 + 0x2c);
  uStack_90 = *(undefined4 *)(puVar27 + 6);
  uStack_8c = *(undefined4 *)((int)puVar27 + 0x34);
  uStack_88 = *(undefined4 *)(puVar27 + 7);
  uStack_84 = *(undefined4 *)((int)puVar27 + 0x3c);
  RotTransVector(&fStack_80,iVar28 + 0x670,&uStack_c0,8);
  *(float *)(param_1 + 0xd0) = (fStack_20 + fStack_40 + fStack_80 + fStack_60) / 4.0;
  *(float *)(param_1 + 0xd4) = (fStack_1c + fStack_3c + fStack_7c + fStack_5c) / 4.0;
  *(float *)(param_1 + 0xd8) = (fStack_18 + fStack_38 + fStack_78 + fStack_58) / 4.0;
  *(undefined4 *)(param_1 + 0xdc) = 0x3f800000;
  auVar31 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x70));
  auVar32 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x80));
  auVar31 = _vadd(auVar31,auVar32);
  auStack_400 = _sqc2(auVar31);
  __ct__7FVectorFRC7FVector(auStack_100,auStack_400);
  auVar31 = _lqc2(auStack_100);
  auVar32 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x90));
  auVar31 = _vadd(auVar31,auVar32);
  auStack_410 = _sqc2(auVar31);
  __ct__7FVectorFRC7FVector(auStack_f0,auStack_410);
  auVar31 = _lqc2(auStack_f0);
  auVar32 = _lqc2(*(undefined1 (*) [16])(param_1 + 0xa0));
  auVar31 = _vadd(auVar31,auVar32);
  auStack_290 = _sqc2(auVar31);
  __ct__7FVectorFRC7FVector(auStack_e0,auStack_290);
  *(int *)(param_1 + 0xe0) = auStack_e0._0_4_;
  *(int *)(param_1 + 0xe4) = auStack_e0._4_4_;
  *(undefined4 *)(param_1 + 0xe8) = uStack_d8;
  *(undefined4 *)(param_1 + 0xec) = uStack_d4;
  __adv__7FVectorFf(0x40800000,param_1 + 0xe0);
  *(float *)(param_1 + 0xf4) = *(float *)(param_1 + 0xf4) + fVar30;
  fStack_d0 = in_zero_lo;
  fStack_cc = in_zero_hi;
  fStack_c8 = in_zero_udw;
  uStack_c4 = in_register_0000000c;
  for (iVar28 = 0; iVar28 < 0x18; iVar28 = iVar28 + 1) {
    sVar1 = *(short *)(param_1 + iVar28 * 2 + 0xfc);
    if (sVar1 == 1) {
      iVar26 = param_1 + iVar28 * 4;
      *(float *)(iVar26 + 0x15c) = *(float *)(iVar26 + 0x15c) + fVar30;
      iVar26 = param_1 + iVar28 * 0x10;
      *(float *)(iVar26 + 0x1c4) = *(float *)(iVar26 + 0x1c4) - fVar30 * 2.0;
      if (*(float *)(param_1 + iVar28 * 4 + 0x15c) < 0.6666667) {
        *(undefined4 *)(param_1 + iVar28 * 4 + 0x3a0) = 0x43000000;
      }
      else {
        *(float *)(param_1 + iVar28 * 4 + 0x3a0) =
             ((1.0 - *(float *)(param_1 + iVar28 * 4 + 0x15c)) / 0.33333334) * 128.0;
      }
      if ((1.0 <= *(float *)(param_1 + iVar28 * 4 + 0x15c)) &&
         (*(undefined2 *)(param_1 + iVar28 * 2 + 0xfc) = 0, 0.06666667 <= *(float *)(param_1 + 0xf4)
         )) {
        *(undefined2 *)(param_1 + iVar28 * 2 + 0xfc) = 1;
        *(undefined4 *)(param_1 + iVar28 * 4 + 0x15c) = 0;
        iVar26 = rand();
        fVar29 = ((float)iVar26 / 2.1474836e+09) * 4.0;
        auVar31 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x80));
        auVar32 = _lqc2(*(undefined1 (*) [16])(param_1 + 0xa0));
        auVar31 = _vadd(auVar31,auVar32);
        auStack_350 = _sqc2(auVar31);
        __ct__7FVectorFRC7FVector(auStack_1d0,auStack_350);
        fStack_d0 = auStack_1d0._0_4_;
        fStack_cc = auStack_1d0._4_4_;
        fStack_c8 = fStack_1c8;
        uStack_c4 = uStack_1c4;
        __adv__7FVectorFf(0x40000000,&fStack_d0);
        if (fVar29 < 1.0) {
          auVar32 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x90));
          auVar31._4_4_ = fStack_cc;
          auVar31._0_4_ = fStack_d0;
          auVar31._8_4_ = fStack_c8;
          auVar31._12_4_ = uStack_c4;
          auVar31 = _lqc2(auVar31);
          auVar31 = _vsub(auVar32,auVar31);
          auStack_360 = _sqc2(auVar31);
          __ct__7FVectorFRC7FVector(auStack_1e0,auStack_360);
          fStack_80 = auStack_1e0._0_4_;
          fStack_7c = auStack_1e0._4_4_;
          fStack_78 = fStack_1d8;
          uStack_74 = uStack_1d4;
          auVar31 = _lqc2(*(undefined1 (*) [16])(param_1 + 0xd0));
          auVar32._4_4_ = fStack_cc;
          auVar32._0_4_ = fStack_d0;
          auVar32._8_4_ = fStack_c8;
          auVar32._12_4_ = uStack_c4;
          auVar32 = _lqc2(auVar32);
          auVar31 = _vsub(auVar31,auVar32);
          auStack_370 = _sqc2(auVar31);
          __ct__7FVectorFRC7FVector(auStack_1f0,auStack_370);
          fStack_70 = auStack_1f0._0_4_;
          fStack_6c = auStack_1f0._4_4_;
          fStack_68 = fStack_1e8;
          uStack_64 = uStack_1e4;
        }
        else if (fVar29 < 2.0) {
          auVar31 = _lqc2(*(undefined1 (*) [16])(param_1 + 0xd0));
          auVar11._4_4_ = fStack_cc;
          auVar11._0_4_ = fStack_d0;
          auVar11._8_4_ = fStack_c8;
          auVar11._12_4_ = uStack_c4;
          auVar32 = _lqc2(auVar11);
          auVar31 = _vsub(auVar31,auVar32);
          auStack_380 = _sqc2(auVar31);
          __ct__7FVectorFRC7FVector(auStack_200,auStack_380);
          fStack_80 = auStack_200._0_4_;
          fStack_7c = auStack_200._4_4_;
          fStack_78 = fStack_1f8;
          uStack_74 = uStack_1f4;
          auVar31 = _lqc2(*(undefined1 (*) [16])(param_1 + 0xc0));
          auVar12._4_4_ = fStack_cc;
          auVar12._0_4_ = fStack_d0;
          auVar12._8_4_ = fStack_c8;
          auVar12._12_4_ = uStack_c4;
          auVar32 = _lqc2(auVar12);
          auVar31 = _vsub(auVar31,auVar32);
          auStack_390 = _sqc2(auVar31);
          __ct__7FVectorFRC7FVector(auStack_210,auStack_390);
          fStack_70 = auStack_210._0_4_;
          fStack_6c = auStack_210._4_4_;
          fStack_68 = fStack_208;
          uStack_64 = uStack_204;
        }
        else if (fVar29 < 3.0) {
          auVar31 = _lqc2(*(undefined1 (*) [16])(param_1 + 0xc0));
          auVar13._4_4_ = fStack_cc;
          auVar13._0_4_ = fStack_d0;
          auVar13._8_4_ = fStack_c8;
          auVar13._12_4_ = uStack_c4;
          auVar32 = _lqc2(auVar13);
          auVar31 = _vsub(auVar31,auVar32);
          auStack_3a0 = _sqc2(auVar31);
          __ct__7FVectorFRC7FVector(auStack_220,auStack_3a0);
          fStack_80 = auStack_220._0_4_;
          fStack_7c = auStack_220._4_4_;
          fStack_78 = fStack_218;
          uStack_74 = uStack_214;
          auVar31 = _lqc2(*(undefined1 (*) [16])(param_1 + 0xb0));
          auVar14._4_4_ = fStack_cc;
          auVar14._0_4_ = fStack_d0;
          auVar14._8_4_ = fStack_c8;
          auVar14._12_4_ = uStack_c4;
          auVar32 = _lqc2(auVar14);
          auVar31 = _vsub(auVar31,auVar32);
          auStack_3b0 = _sqc2(auVar31);
          __ct__7FVectorFRC7FVector(auStack_230,auStack_3b0);
          fStack_70 = auStack_230._0_4_;
          fStack_6c = auStack_230._4_4_;
          fStack_68 = fStack_228;
          uStack_64 = uStack_224;
        }
        else {
          auVar31 = _lqc2(*(undefined1 (*) [16])(param_1 + 0xb0));
          auVar15._4_4_ = fStack_cc;
          auVar15._0_4_ = fStack_d0;
          auVar15._8_4_ = fStack_c8;
          auVar15._12_4_ = uStack_c4;
          auVar32 = _lqc2(auVar15);
          auVar31 = _vsub(auVar31,auVar32);
          auStack_3c0 = _sqc2(auVar31);
          __ct__7FVectorFRC7FVector(auStack_240,auStack_3c0);
          fStack_80 = auStack_240._0_4_;
          fStack_7c = auStack_240._4_4_;
          fStack_78 = fStack_238;
          uStack_74 = uStack_234;
          auVar31 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x70));
          auVar16._4_4_ = fStack_cc;
          auVar16._0_4_ = fStack_d0;
          auVar16._8_4_ = fStack_c8;
          auVar16._12_4_ = uStack_c4;
          auVar32 = _lqc2(auVar16);
          auVar31 = _vsub(auVar31,auVar32);
          auStack_3d0 = _sqc2(auVar31);
          __ct__7FVectorFRC7FVector(auStack_250,auStack_3d0);
          fStack_70 = auStack_250._0_4_;
          fStack_6c = auStack_250._4_4_;
          fStack_68 = fStack_248;
          uStack_64 = uStack_244;
        }
        iVar26 = rand();
        fVar29 = (float)iVar26 / 2.1474836e+09;
        __amu__7FVectorFf(fVar29,&fStack_80);
        __amu__7FVectorFf(fVar29,&fStack_70);
        auVar23._4_4_ = fStack_6c;
        auVar23._0_4_ = fStack_70;
        auVar23._8_4_ = fStack_68;
        auVar23._12_4_ = uStack_64;
        auVar31 = _lqc2(auVar23);
        auVar20._4_4_ = fStack_7c;
        auVar20._0_4_ = fStack_80;
        auVar20._8_4_ = fStack_78;
        auVar20._12_4_ = uStack_74;
        auVar32 = _lqc2(auVar20);
        auVar31 = _vsub(auVar31,auVar32);
        auStack_3e0 = _sqc2(auVar31);
        __ct__7FVectorFRC7FVector(auStack_260,auStack_3e0);
        fStack_60 = auStack_260._0_4_;
        fStack_5c = auStack_260._4_4_;
        fStack_58 = fStack_258;
        uStack_54 = uStack_254;
        iVar26 = rand();
        __amu__7FVectorFf((float)iVar26 / 2.1474836e+09,&fStack_60);
        auVar17._4_4_ = fStack_cc;
        auVar17._0_4_ = fStack_d0;
        auVar17._8_4_ = fStack_c8;
        auVar17._12_4_ = uStack_c4;
        auVar31 = _lqc2(auVar17);
        auVar21._4_4_ = fStack_7c;
        auVar21._0_4_ = fStack_80;
        auVar21._8_4_ = fStack_78;
        auVar21._12_4_ = uStack_74;
        auVar32 = _lqc2(auVar21);
        auVar31 = _vadd(auVar31,auVar32);
        auStack_430 = _sqc2(auVar31);
        __ct__7FVectorFRC7FVector(auStack_280,auStack_430);
        auVar31 = _lqc2(auStack_280);
        auVar25._4_4_ = fStack_5c;
        auVar25._0_4_ = fStack_60;
        auVar25._8_4_ = fStack_58;
        auVar25._12_4_ = uStack_54;
        auVar32 = _lqc2(auVar25);
        auVar31 = _vadd(auVar31,auVar32);
        auStack_3f0 = _sqc2(auVar31);
        __ct__7FVectorFRC7FVector(auStack_270,auStack_3f0);
        iVar26 = param_1 + iVar28 * 0x10;
        *(int *)(iVar26 + 0x1c0) = auStack_270._0_4_;
        *(int *)(iVar26 + 0x1c4) = auStack_270._4_4_;
        *(undefined4 *)(iVar26 + 0x1c8) = uStack_268;
        *(undefined4 *)(iVar26 + 0x1cc) = uStack_264;
        *(undefined4 *)(param_1 + iVar28 * 4 + 0x340) = 0x3f800000;
        *(undefined4 *)(param_1 + iVar28 * 4 + 0x3a0) = 0x3f800000;
        *(float *)(param_1 + 0xf4) = *(float *)(param_1 + 0xf4) - 0.06666667;
      }
    }
    else if ((sVar1 == 0) && (0.06666667 <= *(float *)(param_1 + 0xf4))) {
      *(undefined2 *)(param_1 + iVar28 * 2 + 0xfc) = 1;
      *(undefined4 *)(param_1 + iVar28 * 4 + 0x15c) = 0;
      iVar26 = rand();
      fVar29 = ((float)iVar26 / 2.1474836e+09) * 4.0;
      auVar31 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x80));
      auVar32 = _lqc2(*(undefined1 (*) [16])(param_1 + 0xa0));
      auVar31 = _vadd(auVar31,auVar32);
      auStack_2a0 = _sqc2(auVar31);
      __ct__7FVectorFRC7FVector(auStack_110,auStack_2a0);
      fStack_d0 = auStack_110._0_4_;
      fStack_cc = auStack_110._4_4_;
      fStack_c8 = fStack_108;
      uStack_c4 = uStack_104;
      __adv__7FVectorFf(0x40000000,&fStack_d0);
      if (fVar29 < 1.0) {
        auVar31 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x90));
        auVar2._4_4_ = fStack_cc;
        auVar2._0_4_ = fStack_d0;
        auVar2._8_4_ = fStack_c8;
        auVar2._12_4_ = uStack_c4;
        auVar32 = _lqc2(auVar2);
        auVar31 = _vsub(auVar31,auVar32);
        auStack_2b0 = _sqc2(auVar31);
        __ct__7FVectorFRC7FVector(auStack_120,auStack_2b0);
        fStack_80 = auStack_120._0_4_;
        fStack_7c = auStack_120._4_4_;
        fStack_78 = fStack_118;
        uStack_74 = uStack_114;
        auVar31 = _lqc2(*(undefined1 (*) [16])(param_1 + 0xd0));
        auVar3._4_4_ = fStack_cc;
        auVar3._0_4_ = fStack_d0;
        auVar3._8_4_ = fStack_c8;
        auVar3._12_4_ = uStack_c4;
        auVar32 = _lqc2(auVar3);
        auVar31 = _vsub(auVar31,auVar32);
        auStack_2c0 = _sqc2(auVar31);
        __ct__7FVectorFRC7FVector(auStack_130,auStack_2c0);
        fStack_70 = auStack_130._0_4_;
        fStack_6c = auStack_130._4_4_;
        fStack_68 = fStack_128;
        uStack_64 = uStack_124;
      }
      else if (fVar29 < 2.0) {
        auVar31 = _lqc2(*(undefined1 (*) [16])(param_1 + 0xd0));
        auVar4._4_4_ = fStack_cc;
        auVar4._0_4_ = fStack_d0;
        auVar4._8_4_ = fStack_c8;
        auVar4._12_4_ = uStack_c4;
        auVar32 = _lqc2(auVar4);
        auVar31 = _vsub(auVar31,auVar32);
        auStack_2d0 = _sqc2(auVar31);
        __ct__7FVectorFRC7FVector(auStack_140,auStack_2d0);
        fStack_80 = auStack_140._0_4_;
        fStack_7c = auStack_140._4_4_;
        fStack_78 = fStack_138;
        uStack_74 = uStack_134;
        auVar31 = _lqc2(*(undefined1 (*) [16])(param_1 + 0xc0));
        auVar5._4_4_ = fStack_cc;
        auVar5._0_4_ = fStack_d0;
        auVar5._8_4_ = fStack_c8;
        auVar5._12_4_ = uStack_c4;
        auVar32 = _lqc2(auVar5);
        auVar31 = _vsub(auVar31,auVar32);
        auStack_2e0 = _sqc2(auVar31);
        __ct__7FVectorFRC7FVector(auStack_150,auStack_2e0);
        fStack_70 = auStack_150._0_4_;
        fStack_6c = auStack_150._4_4_;
        fStack_68 = fStack_148;
        uStack_64 = uStack_144;
      }
      else if (fVar29 < 3.0) {
        auVar31 = _lqc2(*(undefined1 (*) [16])(param_1 + 0xc0));
        auVar6._4_4_ = fStack_cc;
        auVar6._0_4_ = fStack_d0;
        auVar6._8_4_ = fStack_c8;
        auVar6._12_4_ = uStack_c4;
        auVar32 = _lqc2(auVar6);
        auVar31 = _vsub(auVar31,auVar32);
        auStack_2f0 = _sqc2(auVar31);
        __ct__7FVectorFRC7FVector(auStack_160,auStack_2f0);
        fStack_80 = auStack_160._0_4_;
        fStack_7c = auStack_160._4_4_;
        fStack_78 = fStack_158;
        uStack_74 = uStack_154;
        auVar31 = _lqc2(*(undefined1 (*) [16])(param_1 + 0xb0));
        auVar7._4_4_ = fStack_cc;
        auVar7._0_4_ = fStack_d0;
        auVar7._8_4_ = fStack_c8;
        auVar7._12_4_ = uStack_c4;
        auVar32 = _lqc2(auVar7);
        auVar31 = _vsub(auVar31,auVar32);
        auStack_300 = _sqc2(auVar31);
        __ct__7FVectorFRC7FVector(auStack_170,auStack_300);
        fStack_70 = auStack_170._0_4_;
        fStack_6c = auStack_170._4_4_;
        fStack_68 = fStack_168;
        uStack_64 = uStack_164;
      }
      else {
        auVar31 = _lqc2(*(undefined1 (*) [16])(param_1 + 0xb0));
        auVar8._4_4_ = fStack_cc;
        auVar8._0_4_ = fStack_d0;
        auVar8._8_4_ = fStack_c8;
        auVar8._12_4_ = uStack_c4;
        auVar32 = _lqc2(auVar8);
        auVar31 = _vsub(auVar31,auVar32);
        auStack_310 = _sqc2(auVar31);
        __ct__7FVectorFRC7FVector(auStack_180,auStack_310);
        fStack_80 = auStack_180._0_4_;
        fStack_7c = auStack_180._4_4_;
        fStack_78 = fStack_178;
        uStack_74 = uStack_174;
        auVar31 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x70));
        auVar9._4_4_ = fStack_cc;
        auVar9._0_4_ = fStack_d0;
        auVar9._8_4_ = fStack_c8;
        auVar9._12_4_ = uStack_c4;
        auVar32 = _lqc2(auVar9);
        auVar31 = _vsub(auVar31,auVar32);
        auStack_320 = _sqc2(auVar31);
        __ct__7FVectorFRC7FVector(auStack_190,auStack_320);
        fStack_70 = auStack_190._0_4_;
        fStack_6c = auStack_190._4_4_;
        fStack_68 = fStack_188;
        uStack_64 = uStack_184;
      }
      iVar26 = rand();
      fVar29 = (float)iVar26 / 2.1474836e+09;
      __amu__7FVectorFf(fVar29,&fStack_80);
      __amu__7FVectorFf(fVar29,&fStack_70);
      auVar22._4_4_ = fStack_6c;
      auVar22._0_4_ = fStack_70;
      auVar22._8_4_ = fStack_68;
      auVar22._12_4_ = uStack_64;
      auVar31 = _lqc2(auVar22);
      auVar18._4_4_ = fStack_7c;
      auVar18._0_4_ = fStack_80;
      auVar18._8_4_ = fStack_78;
      auVar18._12_4_ = uStack_74;
      auVar32 = _lqc2(auVar18);
      auVar31 = _vsub(auVar31,auVar32);
      auStack_330 = _sqc2(auVar31);
      __ct__7FVectorFRC7FVector(auStack_1a0,auStack_330);
      fStack_60 = auStack_1a0._0_4_;
      fStack_5c = auStack_1a0._4_4_;
      fStack_58 = fStack_198;
      uStack_54 = uStack_194;
      iVar26 = rand();
      __amu__7FVectorFf((float)iVar26 / 2.1474836e+09,&fStack_60);
      auVar10._4_4_ = fStack_cc;
      auVar10._0_4_ = fStack_d0;
      auVar10._8_4_ = fStack_c8;
      auVar10._12_4_ = uStack_c4;
      auVar31 = _lqc2(auVar10);
      auVar19._4_4_ = fStack_7c;
      auVar19._0_4_ = fStack_80;
      auVar19._8_4_ = fStack_78;
      auVar19._12_4_ = uStack_74;
      auVar32 = _lqc2(auVar19);
      auVar31 = _vadd(auVar31,auVar32);
      auStack_420 = _sqc2(auVar31);
      __ct__7FVectorFRC7FVector(auStack_1c0,auStack_420);
      auVar31 = _lqc2(auStack_1c0);
      auVar24._4_4_ = fStack_5c;
      auVar24._0_4_ = fStack_60;
      auVar24._8_4_ = fStack_58;
      auVar24._12_4_ = uStack_54;
      auVar32 = _lqc2(auVar24);
      auVar31 = _vadd(auVar31,auVar32);
      auStack_340 = _sqc2(auVar31);
      __ct__7FVectorFRC7FVector(auStack_1b0,auStack_340);
      iVar26 = param_1 + iVar28 * 0x10;
      *(int *)(iVar26 + 0x1c0) = auStack_1b0._0_4_;
      *(int *)(iVar26 + 0x1c4) = auStack_1b0._4_4_;
      *(undefined4 *)(iVar26 + 0x1c8) = uStack_1a8;
      *(undefined4 *)(iVar26 + 0x1cc) = uStack_1a4;
      *(undefined4 *)(param_1 + iVar28 * 4 + 0x340) = 0x3f800000;
      *(undefined4 *)(param_1 + iVar28 * 4 + 0x3a0) = 0x3f800000;
      *(float *)(param_1 + 0xf4) = *(float *)(param_1 + 0xf4) - 0.06666667;
    }
  }
  return 0;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0052b220  MakePacket__16FanAddAttribute1Fv
 * C++: FanAddAttribute1::MakePacket()
 * size: 0x1c08 bytes
 * --------------------------------------------------------------------------- */
/* WARNING: Removing unreachable block (ram,0x0052c6c0) */
/* WARNING: Removing unreachable block (ram,0x0052c600) */
/* WARNING: Removing unreachable block (ram,0x0052c780) */

void MakePacket__16FanAddAttribute1Fv(int param_1)

{
  bool bVar1;
  undefined4 *puVar2;
  undefined1 auVar3 [16];
  undefined1 auVar4 [16];
  bool bVar5;
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
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  undefined8 uVar19;
  undefined8 extraout_v0_udw;
  undefined1 auVar20 [16];
  undefined8 in_v1_udw;
  undefined1 auVar21 [16];
  uint uVar22;
  int iVar23;
  undefined4 uVar24;
  int iVar25;
  float fVar26;
  int iVar27;
  int iVar28;
  int iVar29;
  undefined1 auVar30 [16];
  undefined1 auVar31 [16];
  undefined1 auStack_1040 [16];
  undefined1 auStack_1030 [16];
  undefined1 auStack_1020 [16];
  undefined1 auStack_1010 [16];
  undefined1 auStack_1000 [16];
  undefined1 auStack_ff0 [16];
  undefined1 auStack_fe0 [16];
  undefined1 auStack_fd0 [16];
  undefined1 auStack_fc0 [16];
  undefined1 auStack_fb0 [16];
  undefined1 auStack_fa0 [8];
  undefined4 uStack_f98;
  undefined4 uStack_f94;
  undefined8 uStack_f90;
  undefined4 uStack_f88;
  undefined4 uStack_f84;
  undefined8 uStack_f80;
  undefined4 uStack_f78;
  undefined4 uStack_f74;
  undefined8 uStack_f70;
  undefined4 uStack_f68;
  undefined4 uStack_f64;
  undefined4 uStack_f60;
  undefined4 uStack_f5c;
  undefined4 uStack_f58;
  undefined4 uStack_f54;
  undefined1 auStack_f50 [16];
  undefined4 uStack_f40;
  undefined4 uStack_f3c;
  undefined4 uStack_f38;
  undefined4 uStack_f34;
  undefined4 uStack_f30;
  undefined4 uStack_f2c;
  undefined4 uStack_f28;
  undefined4 uStack_f24;
  undefined4 uStack_f20;
  undefined4 uStack_f1c;
  undefined4 uStack_f18;
  undefined4 uStack_f14;
  undefined4 uStack_f10;
  undefined4 uStack_f0c;
  undefined4 uStack_f08;
  undefined4 uStack_f04;
  undefined1 auStack_f00 [16];
  undefined1 auStack_ef0 [16];
  undefined4 uStack_ee0;
  undefined4 uStack_edc;
  undefined4 uStack_ed8;
  undefined4 uStack_ed4;
  undefined4 uStack_ed0;
  undefined4 uStack_ecc;
  undefined4 uStack_ec8;
  undefined4 uStack_ec4;
  undefined4 uStack_ec0;
  undefined4 uStack_ebc;
  undefined4 uStack_eb8;
  undefined4 uStack_eb4;
  undefined4 uStack_eb0;
  undefined4 uStack_eac;
  undefined4 uStack_ea8;
  undefined4 uStack_ea4;
  undefined4 uStack_ea0;
  undefined4 uStack_e9c;
  undefined4 uStack_e98;
  undefined4 uStack_e94;
  int aiStack_e90 [440];
  float afStack_7b0 [5];
  undefined4 uStack_79c;
  undefined4 uStack_798;
  undefined4 uStack_794;
  undefined4 uStack_790;
  undefined4 uStack_78c;
  undefined4 uStack_788;
  undefined4 uStack_784;
  undefined4 uStack_780;
  undefined4 uStack_77c;
  undefined4 uStack_778;
  undefined4 uStack_774;
  undefined4 uStack_770;
  undefined4 uStack_76c;
  undefined4 uStack_768;
  undefined4 uStack_764;
  undefined4 uStack_760;
  undefined4 uStack_75c;
  undefined4 uStack_758;
  undefined4 uStack_754;
  undefined4 uStack_750;
  undefined4 uStack_74c;
  undefined4 uStack_748;
  undefined4 uStack_744;
  undefined4 uStack_740;
  undefined4 uStack_73c;
  undefined4 uStack_738;
  undefined4 uStack_734;
  undefined4 uStack_730;
  undefined4 uStack_72c;
  undefined4 uStack_728;
  undefined4 uStack_724;
  undefined4 uStack_720;
  undefined4 uStack_71c;
  undefined4 uStack_718;
  undefined4 uStack_714;
  undefined1 auStack_110 [16];
  float afStack_100 [16];
  int aiStack_c0 [7];
  undefined4 uStack_a4;
  undefined4 uStack_a0;
  undefined4 uStack_9c;
  undefined4 uStack_98;
  undefined4 uStack_94;
  undefined4 uStack_90;
  undefined4 uStack_8c;
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined4 auStack_80 [28];
  undefined1 auStack_10 [16];
  
  uStack_ea0 = 0xbf800000;
  uStack_e9c = 0xbf800000;
  uStack_e98 = 0;
  uStack_e94 = 0x3f800000;
  auStack_80[0] = 0xbf800000;
  auStack_80[1] = 0xbf800000;
  auStack_80[2] = 0;
  auStack_80[3] = 0x3f800000;
  uStack_eb0 = 0xbf800000;
  uStack_eac = 0x3f800000;
  uStack_ea8 = 0;
  uStack_ea4 = 0x3f800000;
  auStack_80[4] = 0xbf800000;
  auStack_80[5] = 0x3f800000;
  auStack_80[6] = 0;
  auStack_80[7] = 0x3f800000;
  uStack_ec0 = 0x3f800000;
  uStack_ebc = 0xbf800000;
  uStack_eb8 = 0;
  uStack_eb4 = 0x3f800000;
  auStack_80[8] = 0x3f800000;
  auStack_80[9] = 0xbf800000;
  auStack_80[10] = 0;
  auStack_80[0xb] = 0x3f800000;
  uStack_ed0 = 0x3f800000;
  uStack_ecc = 0x3f800000;
  uStack_ec8 = 0;
  uStack_ec4 = 0x3f800000;
  auStack_80[0xc] = 0x3f800000;
  auStack_80[0xd] = 0x3f800000;
  auStack_80[0xe] = 0;
  auStack_80[0xf] = 0x3f800000;
  auStack_80[0x10] = in_zero_lo;
  auStack_80[0x11] = in_zero_hi;
  auStack_80[0x12] = in_zero_udw;
  auStack_80[0x14] = in_zero_lo;
  auStack_80[0x15] = in_zero_hi;
  auStack_80[0x16] = in_zero_udw;
  auStack_80[0x18] = in_zero_lo;
  auStack_80[0x19] = in_zero_hi;
  auStack_80[0x1a] = in_zero_udw;
  __ct__6MatrixFRC6Matrix(aiStack_c0,iGpffff8598 + 0x240);
  uStack_90 = 0;
  uStack_8c = 0;
  uStack_88 = 0;
  uStack_84 = 0x3f800000;
  RotTransVector(afStack_100,auStack_80,aiStack_c0,4);
  auVar30 = _lqc2(*(undefined1 (*) [16])(*(int *)(iGpffff86b4 + 0x4324) + 0x30));
  auVar31 = _lqc2(*(undefined1 (*) [16])(param_1 + 0xe0));
  auVar30 = _vsub(auVar30,auVar31);
  auStack_fb0 = _sqc2(auVar30);
  __ct__7FVectorFRC7FVector(auStack_110,auStack_fb0);
  Normalize__7FVectorFv(auStack_110);
  __amu__7FVectorFf(0x3e4ccccd,auStack_110);
  for (iVar23 = 0; iVar23 < 7; iVar23 = iVar23 + 1) {
    auVar30 = _lqc2(*(undefined1 (*) [16])(param_1 + iVar23 * 0x10 + 0x70));
    auVar31 = _lqc2(*(undefined1 (*) [16])(param_1 + 0xe0));
    auVar30 = _vsub(auVar30,auVar31);
    auStack_fc0 = _sqc2(auVar30);
    __ct__7FVectorFRC7FVector(&uStack_ee0,auStack_fc0);
    auStack_80[iVar23 * 4] = uStack_ee0;
    auStack_80[iVar23 * 4 + 1] = uStack_edc;
    auStack_80[iVar23 * 4 + 2] = uStack_ed8;
    auStack_80[iVar23 * 4 + 3] = uStack_ed4;
    if ((iVar23 == 0) || (iVar23 == 2)) {
      __amu__7FVectorFf(0x3fcccccd,auStack_80 + iVar23 * 4);
    }
    else {
      __amu__7FVectorFf(0x3fb33333,auStack_80 + iVar23 * 4);
    }
    auVar30 = _lqc2(*(undefined1 (*) [16])(param_1 + 0xe0));
    auVar31 = _lqc2(auStack_110);
    auVar30 = _vadd(auVar30,auVar31);
    auStack_fd0 = _sqc2(auVar30);
    __ct__7FVectorFRC7FVector(auStack_ef0,auStack_fd0);
    auVar31 = _lqc2(auStack_ef0);
    auVar30 = _lqc2(*(undefined1 (*) [16])(auStack_80 + iVar23 * 4));
    auVar30 = _vadd(auVar30,auVar31);
    auVar30 = _sqc2(auVar30);
    *(undefined1 (*) [16])(auStack_80 + iVar23 * 4) = auVar30;
  }
  auVar12._4_4_ = auStack_80[9];
  auVar12._0_4_ = auStack_80[8];
  auVar12._8_4_ = auStack_80[10];
  auVar12._12_4_ = auStack_80[0xb];
  auVar30 = _lqc2(auVar12);
  auVar31._4_4_ = auStack_80[5];
  auVar31._0_4_ = auStack_80[4];
  auVar31._8_4_ = auStack_80[6];
  auVar31._12_4_ = auStack_80[7];
  auVar31 = _lqc2(auVar31);
  auVar30 = _vsub(auVar30,auVar31);
  auStack_fe0 = _sqc2(auVar30);
  __ct__7FVectorFRC7FVector(auStack_f00,auStack_fe0);
  uVar24 = Length__7FVectorCFv(auStack_10);
  auVar30 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x90));
  auVar31 = _lqc2(*(undefined1 (*) [16])(param_1 + 0xa0));
  auVar30 = _vsub(auVar30,auVar31);
  auStack_ff0 = _sqc2(auVar30);
  __ct__7FVectorFRC7FVector(&uStack_f10,auStack_ff0);
  auStack_10._4_4_ = uStack_f0c;
  auStack_10._0_4_ = uStack_f10;
  auStack_10._8_4_ = uStack_f08;
  auStack_10._12_4_ = uStack_f04;
  Normalize__7FVectorFv(auStack_10);
  __amu__7FVectorFf(uVar24,auStack_10);
  auVar6._4_4_ = auStack_80[5];
  auVar6._0_4_ = auStack_80[4];
  auVar6._8_4_ = auStack_80[6];
  auVar6._12_4_ = auStack_80[7];
  auVar31 = _lqc2(auVar6);
  auVar30 = _lqc2(auStack_10);
  auVar30 = _vadd(auVar30,auVar31);
  auStack_10 = _sqc2(auVar30);
  afStack_7b0[0] = (float)auStack_10._0_4_;
  afStack_7b0[1] = (float)auStack_10._4_4_;
  afStack_7b0[2] = (float)auStack_10._8_4_;
  afStack_7b0[3] = 1.0;
  afStack_7b0[4] = (float)auStack_80[4];
  uStack_79c = auStack_80[5];
  uStack_798 = auStack_80[6];
  uStack_794 = 0x3f800000;
  uStack_790 = auStack_80[0x18];
  uStack_78c = auStack_80[0x19];
  uStack_788 = auStack_80[0x1a];
  uStack_784 = 0x3f800000;
  auVar13._4_4_ = auStack_80[0xd];
  auVar13._0_4_ = auStack_80[0xc];
  auVar13._8_4_ = auStack_80[0xe];
  auVar13._12_4_ = auStack_80[0xf];
  auVar30 = _lqc2(auVar13);
  auVar7._4_4_ = auStack_80[5];
  auVar7._0_4_ = auStack_80[4];
  auVar7._8_4_ = auStack_80[6];
  auVar7._12_4_ = auStack_80[7];
  auVar31 = _lqc2(auVar7);
  auVar30 = _vsub(auVar30,auVar31);
  auStack_1000 = _sqc2(auVar30);
  __ct__7FVectorFRC7FVector(&uStack_f20,auStack_1000);
  auStack_10._4_4_ = uStack_f1c;
  auStack_10._0_4_ = uStack_f20;
  auStack_10._8_4_ = uStack_f18;
  auStack_10._12_4_ = uStack_f14;
  __adv__7FVectorFf(0x40800000,auStack_10);
  auVar8._4_4_ = auStack_80[5];
  auVar8._0_4_ = auStack_80[4];
  auVar8._8_4_ = auStack_80[6];
  auVar8._12_4_ = auStack_80[7];
  auVar31 = _lqc2(auVar8);
  auVar30 = _lqc2(auStack_10);
  auVar30 = _vadd(auVar30,auVar31);
  auStack_10 = _sqc2(auVar30);
  uStack_780 = auStack_10._0_4_;
  uStack_77c = auStack_10._4_4_;
  uStack_778 = auStack_10._8_4_;
  uStack_774 = 0x3f800000;
  uStack_770 = auStack_80[0x14];
  uStack_76c = auStack_80[0x15];
  uStack_768 = auStack_80[0x16];
  uStack_764 = 0x3f800000;
  auVar14._4_4_ = auStack_80[0xd];
  auVar14._0_4_ = auStack_80[0xc];
  auVar14._8_4_ = auStack_80[0xe];
  auVar14._12_4_ = auStack_80[0xf];
  auVar30 = _lqc2(auVar14);
  auVar9._4_4_ = auStack_80[5];
  auVar9._0_4_ = auStack_80[4];
  auVar9._8_4_ = auStack_80[6];
  auVar9._12_4_ = auStack_80[7];
  auVar31 = _lqc2(auVar9);
  auVar30 = _vsub(auVar30,auVar31);
  auStack_1010 = _sqc2(auVar30);
  __ct__7FVectorFRC7FVector(&uStack_f30,auStack_1010);
  auStack_10._4_4_ = uStack_f2c;
  auStack_10._0_4_ = uStack_f30;
  auStack_10._8_4_ = uStack_f28;
  auStack_10._12_4_ = uStack_f24;
  __adv__7FVectorFf(0x40000000,auStack_10);
  auVar10._4_4_ = auStack_80[5];
  auVar10._0_4_ = auStack_80[4];
  auVar10._8_4_ = auStack_80[6];
  auVar10._12_4_ = auStack_80[7];
  auVar31 = _lqc2(auVar10);
  auVar30 = _lqc2(auStack_10);
  auVar30 = _vadd(auVar30,auVar31);
  auStack_10 = _sqc2(auVar30);
  uStack_760 = auStack_10._0_4_;
  uStack_75c = auStack_10._4_4_;
  uStack_758 = auStack_10._8_4_;
  uStack_754 = 0x3f800000;
  uStack_750 = auStack_80[0x10];
  uStack_74c = auStack_80[0x11];
  uStack_748 = auStack_80[0x12];
  uStack_744 = 0x3f800000;
  auVar11._4_4_ = auStack_80[5];
  auVar11._0_4_ = auStack_80[4];
  auVar11._8_4_ = auStack_80[6];
  auVar11._12_4_ = auStack_80[7];
  auVar30 = _lqc2(auVar11);
  auVar15._4_4_ = auStack_80[0xd];
  auVar15._0_4_ = auStack_80[0xc];
  auVar15._8_4_ = auStack_80[0xe];
  auVar15._12_4_ = auStack_80[0xf];
  auVar31 = _lqc2(auVar15);
  auVar30 = _vsub(auVar30,auVar31);
  auStack_1020 = _sqc2(auVar30);
  __ct__7FVectorFRC7FVector(&uStack_f40,auStack_1020);
  auStack_10._4_4_ = uStack_f3c;
  auStack_10._0_4_ = uStack_f40;
  auStack_10._8_4_ = uStack_f38;
  auStack_10._12_4_ = uStack_f34;
  __adv__7FVectorFf(0x40800000,auStack_10);
  auVar16._4_4_ = auStack_80[0xd];
  auVar16._0_4_ = auStack_80[0xc];
  auVar16._8_4_ = auStack_80[0xe];
  auVar16._12_4_ = auStack_80[0xf];
  auVar31 = _lqc2(auVar16);
  auVar30 = _lqc2(auStack_10);
  auVar30 = _vadd(auVar30,auVar31);
  auStack_10 = _sqc2(auVar30);
  uStack_740 = auStack_10._0_4_;
  uStack_73c = auStack_10._4_4_;
  uStack_738 = auStack_10._8_4_;
  uStack_734 = 0x3f800000;
  auVar30._4_4_ = auStack_80[1];
  auVar30._0_4_ = auStack_80[0];
  auVar30._8_4_ = auStack_80[2];
  auVar30._12_4_ = auStack_80[3];
  auVar30 = _lqc2(auVar30);
  auVar17._4_4_ = auStack_80[0xd];
  auVar17._0_4_ = auStack_80[0xc];
  auVar17._8_4_ = auStack_80[0xe];
  auVar17._12_4_ = auStack_80[0xf];
  auVar31 = _lqc2(auVar17);
  auVar30 = _vsub(auVar30,auVar31);
  auStack_1030 = _sqc2(auVar30);
  __ct__7FVectorFRC7FVector(auStack_f50,auStack_1030);
  uVar24 = Length__7FVectorCFv(auStack_10);
  auVar30 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x70));
  auVar31 = _lqc2(*(undefined1 (*) [16])(param_1 + 0x80));
  auVar30 = _vsub(auVar30,auVar31);
  auStack_1040 = _sqc2(auVar30);
  __ct__7FVectorFRC7FVector(&uStack_f60,auStack_1040);
  auStack_10._4_4_ = uStack_f5c;
  auStack_10._0_4_ = uStack_f60;
  auStack_10._8_4_ = uStack_f58;
  auStack_10._12_4_ = uStack_f54;
  Normalize__7FVectorFv(auStack_10);
  __amu__7FVectorFf(uVar24,auStack_10);
  auVar18._4_4_ = auStack_80[0xd];
  auVar18._0_4_ = auStack_80[0xc];
  auVar18._8_4_ = auStack_80[0xe];
  auVar18._12_4_ = auStack_80[0xf];
  auVar31 = _lqc2(auVar18);
  auVar30 = _lqc2(auStack_10);
  auVar30 = _vadd(auVar30,auVar31);
  auStack_10 = _sqc2(auVar30);
  auVar30 = auStack_10;
  uStack_730 = auStack_10._0_4_;
  uStack_72c = auStack_10._4_4_;
  uStack_728 = auStack_10._8_4_;
  uStack_724 = 0x3f800000;
  uStack_720 = auStack_80[0xc];
  uStack_71c = auStack_80[0xd];
  uStack_718 = auStack_80[0xe];
  uStack_714 = 0x3f800000;
  auStack_10 = auVar30;
  for (iVar23 = 0; iVar23 < 0x18; iVar23 = iVar23 + 1) {
    for (iVar25 = 0; iVar25 < 4; iVar25 = iVar25 + 1) {
      afStack_7b0[(iVar25 + iVar23 * 4 + 10) * 4] =
           *(float *)(param_1 + iVar23 * 0x10 + 0x1c0) +
           *(float *)(param_1 + iVar23 * 4 + 0x340) * afStack_100[iVar25 * 4];
      afStack_7b0[(iVar25 + iVar23 * 4 + 10) * 4 + 1] =
           *(float *)(param_1 + iVar23 * 0x10 + 0x1c4) +
           *(float *)(param_1 + iVar23 * 4 + 0x340) * afStack_100[iVar25 * 4 + 1];
      afStack_7b0[(iVar25 + iVar23 * 4 + 10) * 4 + 2] =
           *(float *)(param_1 + iVar23 * 0x10 + 0x1c8) +
           *(float *)(param_1 + iVar23 * 4 + 0x340) * afStack_100[iVar25 * 4 + 2];
      afStack_7b0[(iVar25 + iVar23 * 4 + 10) * 4 + 3] = 1.0;
    }
  }
  GetViewScreenMatrix__9GsxCameraFv(auStack_fa0,iGpffff8598);
  aiStack_c0[0] = auStack_fa0._0_4_;
  aiStack_c0[1] = auStack_fa0._4_4_;
  aiStack_c0[2] = uStack_f98;
  aiStack_c0[3] = uStack_f94;
  aiStack_c0[4] = (int)uStack_f90;
  aiStack_c0[5] = (int)((ulong)uStack_f90 >> 0x20);
  aiStack_c0[6] = uStack_f88;
  uStack_a4 = uStack_f84;
  uStack_a0 = (int)uStack_f80;
  uStack_9c = (int)((ulong)uStack_f80 >> 0x20);
  uStack_98 = uStack_f78;
  uStack_94 = uStack_f74;
  uStack_90 = (int)uStack_f70;
  uStack_8c = (int)((ulong)uStack_f70 >> 0x20);
  uStack_88 = uStack_f68;
  uStack_84 = uStack_f64;
  for (iVar23 = 0; iVar23 < 4; iVar23 = iVar23 + 1) {
    aiStack_e90[iVar23 * 4 + 0x1a8] = aiStack_c0[iVar23 * 4];
    aiStack_e90[iVar23 * 4 + 0x1a9] = aiStack_c0[iVar23 * 4 + 1];
    aiStack_e90[iVar23 * 4 + 0x1aa] = aiStack_c0[iVar23 * 4 + 2];
    aiStack_e90[iVar23 * 4 + 0x1ab] = aiStack_c0[iVar23 * 4 + 3];
  }
  sceVu0RotTransPersN(aiStack_e90,aiStack_e90 + 0x1a8,afStack_7b0,0x6a,0);
  bVar5 = false;
  iVar23 = 0;
  for (iVar25 = 0; iVar25 < 0x6a; iVar25 = iVar25 + 1) {
    if (iVar25 < 10) {
      if (((aiStack_e90[iVar25 * 4] < 0) || (0x10000 < aiStack_e90[iVar25 * 4])) ||
         ((aiStack_e90[iVar25 * 4 + 1] < 0 ||
          ((0x10000 < aiStack_e90[iVar25 * 4 + 1] || (aiStack_e90[iVar25 * 4 + 2] < 0)))))) {
        bVar5 = true;
      }
      aiStack_e90[iVar25 * 4 + 2] = (int)((float)aiStack_e90[iVar25 * 4 + 2] / 16.0);
      if (iVar25 < 10) {
        iVar23 = iVar23 + aiStack_e90[iVar25 * 4 + 2];
      }
    }
    else {
      uVar22 = iVar25 - 10U & 3;
      if (((int)(iVar25 - 10U) < 0) && (uVar22 != 0)) {
        uVar22 = uVar22 - 4;
      }
      if (uVar22 == 0) {
        iVar27 = iVar25 + -10;
        if (iVar27 < 0) {
          iVar27 = iVar25 + -7;
        }
        *(undefined2 *)(param_1 + (iVar27 >> 2) * 2 + 300) = 0;
      }
      if ((((aiStack_e90[iVar25 * 4] < 0) || (0x10000 < aiStack_e90[iVar25 * 4])) ||
          (aiStack_e90[iVar25 * 4 + 1] < 0)) ||
         ((0x10000 < aiStack_e90[iVar25 * 4 + 1] || (aiStack_e90[iVar25 * 4 + 2] < 0)))) {
        iVar27 = iVar25 + -10;
        if (iVar27 < 0) {
          iVar27 = iVar25 + -7;
        }
        *(undefined2 *)(param_1 + (iVar27 >> 2) * 2 + 300) = 1;
      }
      aiStack_e90[iVar25 * 4 + 2] = (int)((float)aiStack_e90[iVar25 * 4 + 2] / 16.0);
    }
  }
  *(int *)(param_1 + 0x50) = iVar23 / 10;
  bVar1 = (*(byte *)(param_1 + 0x40) & 1) == 0;
  uVar22 = (uint)bVar1;
  if (*(int *)(param_1 + uVar22 * 4 + 0x18) == 0) {
    uVar24 = __nwa__FUi(0x960);
    *(undefined4 *)(param_1 + uVar22 * 4 + 0x18) = uVar24;
    iVar23 = *(int *)(param_1 + uVar22 * 4 + 0x18);
    *(undefined4 *)(iVar23 + 0x10) = 0x10000016;
    *(undefined4 *)(iVar23 + 0x14) = 0;
    *(undefined4 *)(iVar23 + 0x18) = 0;
    *(undefined4 *)(iVar23 + 0x1c) = 0x50000016;
    *(undefined8 *)(iVar23 + 0x20) = 0x6000000000000001;
    *(undefined8 *)(iVar23 + 0x28) = 0xe6e8ee;
    *(undefined8 *)(iVar23 + 0x30) = 1;
    *(undefined8 *)(iVar23 + 0x38) = 0x3f;
    *(undefined8 *)(iVar23 + 0x40) = 0x60;
    *(undefined8 *)(iVar23 + 0x48) = 0x14;
    *(undefined8 *)(iVar23 + 0x50) = 5;
    *(undefined8 *)(iVar23 + 0x58) = 0;
    *(undefined8 *)(iVar23 + 0x60) = 0x53001;
    *(undefined8 *)(iVar23 + 0x68) = 0x47;
    uVar19 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x42f4),1);
    *(undefined8 *)(iVar23 + 0x70) = uVar19;
    *(undefined8 *)(iVar23 + 0x78) = 0;
    *(undefined8 *)(iVar23 + 0x80) = 0x48;
    *(undefined8 *)(iVar23 + 0x88) = 0x42;
    auVar20._8_8_ = extraout_v0_udw;
    auVar20._0_8_ = 0xe400000000000001;
    auVar3._4_4_ = in_zero_hi;
    auVar3._0_4_ = in_zero_lo;
    auVar3._8_4_ = in_zero_udw;
    auVar3._12_4_ = in_register_0000000c;
    auVar30 = _pcpyld(auVar3,auVar20);
    *(long *)(iVar23 + 0x90) = auVar30._0_8_;
    *(undefined8 *)(iVar23 + 0x98) = 0xc3c34343c3c310;
    *(undefined8 *)(iVar23 + 0xa0) = 0x154;
    *(long *)(iVar23 + 0xb0) =
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f4) + 2) << 3);
    *(long *)(iVar23 + 0xc0) =
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f4) + 2) << 3) |
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f4) + 4) << 4) << 0x10;
    *(undefined8 *)(iVar23 + 0xd0) = 0;
    *(long *)(iVar23 + 0xe0) =
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f4) + 4) << 4) << 0x10;
    *(long *)(iVar23 + 0xf0) =
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f4) + 2) << 3);
    *(long *)(iVar23 + 0x100) =
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f4) + 2) << 3) |
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f4) + 4) << 4) << 0x10;
    *(undefined8 *)(iVar23 + 0x110) = 0x2400000000008006;
    *(undefined8 *)(iVar23 + 0x118) = 0x43;
    *(long *)(iVar23 + 0x120) =
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f4) + 2) << 3);
    *(long *)(iVar23 + 0x130) =
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f4) + 2) << 3) |
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f4) + 4) << 4) << 0x10;
    *(long *)(iVar23 + 0x140) =
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f4) + 2) << 3);
    *(long *)(iVar23 + 0x150) =
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f4) + 2) << 3) |
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f4) + 4) << 4) << 0x10;
    *(long *)(iVar23 + 0x160) =
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f4) + 2) << 4);
    *(long *)(iVar23 + 0x170) =
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f4) + 2) << 4) |
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f4) + 4) << 4) << 0x10;
    *(undefined4 *)(iVar23 + 0x180) = 0x50000000;
    *(undefined4 *)(iVar23 + 0x184) =
         *(undefined4 *)
          (*(int *)(iGpffff86b4 + 0x42f0) +
           (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f0) + 10) * 4 + 0xc);
    *(undefined4 *)(iVar23 + 0x188) = 0;
    *(undefined4 *)(iVar23 + 0x18c) = 0;
    *(undefined4 *)(iVar23 + 400) = 0x6000007c;
    *(undefined4 *)(iVar23 + 0x194) = 0;
    *(undefined4 *)(iVar23 + 0x198) = 0;
    *(undefined4 *)(iVar23 + 0x19c) = 0x5000007c;
    *(undefined8 *)(iVar23 + 0x1a0) = 0x2000000000000001;
    *(undefined8 *)(iVar23 + 0x1a8) = 0x6e;
    *(undefined8 *)(iVar23 + 0x1b0) = 1;
    *(undefined8 *)(iVar23 + 0x1b8) = 0x3f;
    uVar19 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x42f0),1);
    *(undefined8 *)(iVar23 + 0x1c0) = uVar19;
    *(undefined8 *)(iVar23 + 0x1c8) = 0;
    auVar21._8_8_ = in_v1_udw;
    auVar21._0_8_ = 0xa400000000008018;
    auVar4._4_4_ = in_zero_hi;
    auVar4._0_4_ = in_zero_lo;
    auVar4._8_4_ = in_zero_udw;
    auVar4._12_4_ = in_register_0000000c;
    auVar30 = _pcpyld(auVar4,auVar21);
    *(long *)(iVar23 + 0x1d0) = auVar30._0_8_;
    *(undefined8 *)(iVar23 + 0x1d8) = 0x4343c3c310;
    for (iVar25 = 0; iVar25 < 0x18; iVar25 = iVar25 + 1) {
      *(undefined8 *)(iVar23 + (iVar25 * 5 + 0x1e) * 0x10) = 0x154;
      *(long *)(iVar23 + (iVar25 * 5 + 0x1f) * 0x10) =
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f0) + 2) << 2) |
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f0) + 4) << 2) << 0x10;
      *(long *)(iVar23 + (iVar25 * 5 + 0x20) * 0x10) =
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f0) + 2) << 2) |
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f0) + 4) * 0xc) << 0x10;
      *(long *)(iVar23 + (iVar25 * 5 + 0x21) * 0x10) =
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f0) + 4) << 2) << 0x10 |
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f0) + 2) * 0xc);
      *(long *)(iVar23 + (iVar25 * 5 + 0x22) * 0x10) =
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f0) + 2) * 0xc) |
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f0) + 4) * 0xc) << 0x10;
    }
  }
  puVar2 = *(undefined4 **)(param_1 + uVar22 * 4 + 0x18);
  if (bVar5) {
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
    iVar25 = (int)(*(float *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x144) +
                             0x4e4) *
                   *(float *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x144) +
                             0x4ec) * 128.0);
    fVar26 = (float)sinf(*(undefined4 *)(param_1 + 0xf8));
    fVar26 = (fVar26 + 1.0) / 2.0;
    iVar27 = (int)((float)*(byte *)(*(int *)(param_1 + 0x60) * 0xc + 0x652b64) +
                  fVar26 * (float)(int)((uint)*(byte *)(*(int *)(param_1 + 0x60) * 0xc + 0x652b68) -
                                       (uint)*(byte *)(*(int *)(param_1 + 0x60) * 0xc + 0x652b64)));
    iVar28 = (int)((float)*(byte *)(*(int *)(param_1 + 0x60) * 0xc + 0x652b65) +
                  fVar26 * (float)(int)((uint)*(byte *)(*(int *)(param_1 + 0x60) * 0xc + 0x652b69) -
                                       (uint)*(byte *)(*(int *)(param_1 + 0x60) * 0xc + 0x652b65)));
    iVar29 = (int)((float)*(byte *)(*(int *)(param_1 + 0x60) * 0xc + 0x652b66) +
                  fVar26 * (float)(int)((uint)*(byte *)(*(int *)(param_1 + 0x60) * 0xc + 0x652b6a) -
                                       (uint)*(byte *)(*(int *)(param_1 + 0x60) * 0xc + 0x652b66)));
    *(ulong *)(puVar2 + 0x2a) =
         (long)iVar25 << 0x18 | (long)iVar29 << 0x10 | (long)iVar27 | (long)iVar28 << 8 |
         0x100000000;
    *(long *)(puVar2 + 0x2e) =
         (long)aiStack_e90[10] << 0x20 | (long)aiStack_e90[8] | (long)aiStack_e90[9] << 0x10;
    *(long *)(puVar2 + 0x32) =
         (long)aiStack_e90[0xe] << 0x20 | (long)aiStack_e90[0xc] | (long)aiStack_e90[0xd] << 0x10;
    *(long *)(puVar2 + 0x36) =
         (long)aiStack_e90[2] << 0x20 | (long)aiStack_e90[0] | (long)aiStack_e90[1] << 0x10;
    *(long *)(puVar2 + 0x3a) =
         (long)aiStack_e90[6] << 0x20 | (long)aiStack_e90[4] | (long)aiStack_e90[5] << 0x10;
    *(long *)(puVar2 + 0x3e) =
         (long)aiStack_e90[10] << 0x20 | (long)aiStack_e90[8] | (long)aiStack_e90[9] << 0x10;
    *(long *)(puVar2 + 0x42) =
         (long)aiStack_e90[0xe] << 0x20 | (long)aiStack_e90[0xc] | (long)aiStack_e90[0xd] << 0x10;
    *(long *)(puVar2 + 0x4a) =
         (long)aiStack_e90[0x12] << 0x20 | (long)aiStack_e90[0x10] | (long)aiStack_e90[0x11] << 0x10
    ;
    *(long *)(puVar2 + 0x4e) =
         (long)aiStack_e90[0x16] << 0x20 | (long)aiStack_e90[0x14] | (long)aiStack_e90[0x15] << 0x10
    ;
    *(long *)(puVar2 + 0x52) =
         (long)aiStack_e90[0x1a] << 0x20 | (long)aiStack_e90[0x18] | (long)aiStack_e90[0x19] << 0x10
    ;
    *(long *)(puVar2 + 0x56) =
         (long)aiStack_e90[0x1e] << 0x20 | (long)aiStack_e90[0x1c] | (long)aiStack_e90[0x1d] << 0x10
    ;
    *(long *)(puVar2 + 0x5a) =
         (long)aiStack_e90[0x22] << 0x20 | (long)aiStack_e90[0x20] | (long)aiStack_e90[0x21] << 0x10
    ;
    *(long *)(puVar2 + 0x5e) =
         (long)aiStack_e90[0x26] << 0x20 | (long)aiStack_e90[0x24] | (long)aiStack_e90[0x25] << 0x10
    ;
    for (iVar23 = 0; iVar23 < 0x18; iVar23 = iVar23 + 1) {
      if ((*(short *)(param_1 + iVar23 * 2 + 0xfc) == 0) ||
         (*(short *)(param_1 + iVar23 * 2 + 300) != 0)) {
        *(undefined8 *)(puVar2 + (iVar23 * 5 + 0x1f) * 4 + 2) = 0x71006f00;
        *(undefined8 *)(puVar2 + (iVar23 * 5 + 0x20) * 4 + 2) = 0x71006f00;
        *(undefined8 *)(puVar2 + (iVar23 * 5 + 0x21) * 4 + 2) = 0x71006f00;
        *(undefined8 *)(puVar2 + (iVar23 * 5 + 0x22) * 4 + 2) = 0x71006f00;
      }
      else {
        *(ulong *)(puVar2 + (iVar23 * 5 + 0x1e) * 4 + 2) =
             (long)(int)(((float)iVar25 * *(float *)(param_1 + iVar23 * 4 + 0x3a0)) / 128.0) << 0x18
             | (long)iVar29 << 0x10 | (long)iVar27 | (long)iVar28 << 8 | 0x100000000;
        *(long *)(puVar2 + (iVar23 * 5 + 0x1f) * 4 + 2) =
             (long)aiStack_e90[(iVar23 * 4 + 10) * 4 + 2] << 0x20 |
             (long)aiStack_e90[(iVar23 * 4 + 10) * 4] |
             (long)aiStack_e90[(iVar23 * 4 + 10) * 4 + 1] << 0x10;
        *(long *)(puVar2 + (iVar23 * 5 + 0x20) * 4 + 2) =
             (long)aiStack_e90[(iVar23 * 4 + 0xb) * 4 + 2] << 0x20 |
             (long)aiStack_e90[(iVar23 * 4 + 0xb) * 4] |
             (long)aiStack_e90[(iVar23 * 4 + 0xb) * 4 + 1] << 0x10;
        *(long *)(puVar2 + (iVar23 * 5 + 0x21) * 4 + 2) =
             (long)aiStack_e90[(iVar23 * 4 + 0xc) * 4 + 2] << 0x20 |
             (long)aiStack_e90[(iVar23 * 4 + 0xc) * 4] |
             (long)aiStack_e90[(iVar23 * 4 + 0xc) * 4 + 1] << 0x10;
        *(long *)(puVar2 + (iVar23 * 5 + 0x22) * 4 + 2) =
             (long)aiStack_e90[(iVar23 * 4 + 0xd) * 4 + 2] << 0x20 |
             (long)aiStack_e90[(iVar23 * 4 + 0xd) * 4] |
             (long)aiStack_e90[(iVar23 * 4 + 0xd) * 4 + 1] << 0x10;
      }
    }
    *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfe | bVar1;
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054ae50  EndSet__16FanAddAttribute1Fv
 * C++: FanAddAttribute1::EndSet()
 * size: 0x10 bytes
 * --------------------------------------------------------------------------- */
void EndSet__16FanAddAttribute1Fv(void)

{
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b7f0  @24@__dt__16FanAddAttribute1Fv
 * C++: @24@__dt__16FanAddAttribute1Fv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int * _24___dt__16FanAddAttribute1Fv(int *param_1,short param_2)

{
  int *piVar1;
  
  piVar1 = param_1 + -6;
  if (piVar1 != (int *)0x0) {
    param_1[-1] = 0x409d40;
    param_1[4] = 0x409d50;
    param_1[7] = 0x409d60;
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
 * JP: 0x0054b800  @44@__dt__16FanAddAttribute1Fv
 * C++: @44@__dt__16FanAddAttribute1Fv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int _44___dt__16FanAddAttribute1Fv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x2c;
  if (iVar1 != 0) {
    *(undefined4 *)(param_1 + -0x18) = 0x409d40;
    *(undefined4 *)(param_1 + -4) = 0x409d50;
    *(undefined4 *)(param_1 + 8) = 0x409d60;
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

