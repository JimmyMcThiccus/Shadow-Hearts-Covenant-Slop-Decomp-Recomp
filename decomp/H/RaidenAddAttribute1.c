/* decomp/H/RaidenAddAttribute1.c — cleaned Ghidra output (SH2JP_BATTLE.BIN, JP Furokuban, base 0x00430a00).
 * 8 function(s). Types: see types.h. Names/gp globals resolved from symbols/SLPM_602.19.syms. */
#include "types.h"

/* ---------------------------------------------------------------------------
 * JP: 0x005346a0  __ct__19RaidenAddAttribute1Fiiiii
 * C++: RaidenAddAttribute1::__ct(int, int, int, int, int)
 * size: 0x228 bytes
 * --------------------------------------------------------------------------- */
int __ct__19RaidenAddAttribute1Fiiiii
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
  *(undefined4 *)(param_1 + 0x14) = 0x409c00;
  *(undefined4 *)(param_1 + 0x28) = 0x409c10;
  *(undefined4 *)(param_1 + 0x34) = 0x409c20;
  puVar2 = (undefined4 *)(param_1 + 0x70);
  do {
    *puVar2 = in_zero_lo;
    puVar2[1] = in_zero_hi;
    puVar2[2] = in_zero_udw;
    puVar2[3] = in_register_0000000c;
    puVar2 = puVar2 + 4;
  } while (puVar2 != (undefined4 *)(param_1 + 0xf0));
  puVar2 = (undefined4 *)(param_1 + 0x180);
  do {
    *puVar2 = in_zero_lo;
    puVar2[1] = in_zero_hi;
    puVar2[2] = in_zero_udw;
    puVar2[3] = in_register_0000000c;
    puVar2 = puVar2 + 4;
  } while (puVar2 != (undefined4 *)(param_1 + 0x280));
  *(undefined4 *)(param_1 + 0x40) = 0;
  *(undefined4 *)(param_1 + 0x44) = param_2;
  *(undefined4 *)(param_1 + 0x48) = param_3;
  *(undefined4 *)(param_1 + 0x6c) = 6;
  *(undefined4 *)(param_1 + 0x5c) = 0;
  *(undefined4 *)(param_1 + 0x60) = param_4;
  *(undefined4 *)(param_1 + 0xf0) = 0;
  *(undefined4 *)(param_1 + 0xf4) = 0;
  *(undefined4 *)(param_1 + 0xf8) = 0;
  *(undefined4 *)(param_1 + 100) = param_5;
  *(undefined4 *)(param_1 + 0x6c) = param_6;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  *(undefined4 *)(param_1 + 0x18) = 0;
  for (iVar1 = 0; iVar1 < 0x10; iVar1 = iVar1 + 1) {
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
 * JP: 0x005348d0  __dt__19RaidenAddAttribute1Fv
 * C++: RaidenAddAttribute1::__dt()
 * size: 0x154 bytes
 * --------------------------------------------------------------------------- */
int __dt__19RaidenAddAttribute1Fv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x14) = 0x409c00;
    *(undefined4 *)(param_1 + 0x28) = 0x409c10;
    *(undefined4 *)(param_1 + 0x34) = 0x409c20;
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
 * JP: 0x00534a30  Destruct__19RaidenAddAttribute1Fv
 * C++: RaidenAddAttribute1::Destruct()
 * size: 0xcc bytes
 * --------------------------------------------------------------------------- */
void Destruct__19RaidenAddAttribute1Fv(int param_1)

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
 * JP: 0x00534b00  Polling__19RaidenAddAttribute1Fv
 * C++: RaidenAddAttribute1::Polling()
 * size: 0x6c4 bytes
 * --------------------------------------------------------------------------- */
undefined8 Polling__19RaidenAddAttribute1Fv(int param_1)

{
  short sVar1;
  float in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  int iVar2;
  int iVar3;
  float fVar4;
  undefined1 auStack_b0 [8];
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  float fStack_a0;
  undefined4 uStack_9c;
  undefined4 uStack_98;
  undefined4 uStack_94;
  float fStack_90;
  undefined4 uStack_8c;
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined1 auStack_80 [8];
  undefined4 uStack_78;
  undefined4 uStack_74;
  float fStack_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  float fStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  float fStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined1 auStack_40 [64];
  
  fVar4 = *(float *)(iGpffff86b4 + 0x38);
  if ((*(byte *)(iGpffff86b4 + 0x24) & 1) != 0) {
    fVar4 = 0.0;
  }
  *(float *)(param_1 + 0xf8) = *(float *)(param_1 + 0xf8) + fVar4 * 6.2831855 * 0.75;
  if (3.1415927 <= *(float *)(param_1 + 0xf8)) {
    *(float *)(param_1 + 0xf8) = *(float *)(param_1 + 0xf8) - 6.2831855;
  }
  if (((*(int *)(param_1 + 0x5c) != 1) && (*(int *)(param_1 + 0x5c) == 0)) &&
     (*(float *)(param_1 + 0xf0) = *(float *)(param_1 + 0xf0) + fVar4 * 2.0,
     1.0 <= *(float *)(param_1 + 0xf0))) {
    *(undefined4 *)(param_1 + 0xf0) = 0x3f800000;
    *(undefined4 *)(param_1 + 0x5c) = 1;
  }
  __ct__6MatrixFRC6Matrix(auStack_40,
                  *(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x144) + 0x30)
                  + (uint)*(byte *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0
                                                     + 0x144) + 0xe4) +
                                   *(int *)(param_1 + 100) * 0x110) * 0x1f0 +
                  (bGpffff8340 & 1) * 0x40);
  *(float *)(param_1 + 0xf4) = *(float *)(param_1 + 0xf4) + fVar4;
  fStack_50 = in_zero_lo;
  uStack_4c = in_zero_hi;
  uStack_48 = in_zero_udw;
  uStack_44 = in_register_0000000c;
  for (iVar3 = 0; iVar3 < 0x10; iVar3 = iVar3 + 1) {
    sVar1 = *(short *)(param_1 + iVar3 * 2 + 0xfc);
    if (sVar1 == 1) {
      iVar2 = param_1 + iVar3 * 4;
      *(float *)(iVar2 + 0x13c) = *(float *)(iVar2 + 0x13c) + fVar4;
      iVar2 = param_1 + iVar3 * 0x10;
      *(float *)(iVar2 + 0x184) = *(float *)(iVar2 + 0x184) - fVar4 * 2.0;
      if (*(float *)(param_1 + iVar3 * 4 + 0x13c) < 0.6666667) {
        *(undefined4 *)(param_1 + iVar3 * 4 + 0x2c0) = 0x43000000;
      }
      else {
        *(float *)(param_1 + iVar3 * 4 + 0x2c0) =
             ((1.0 - *(float *)(param_1 + iVar3 * 4 + 0x13c)) / 0.33333334) * 128.0;
      }
      if ((1.0 <= *(float *)(param_1 + iVar3 * 4 + 0x13c)) &&
         (*(undefined2 *)(param_1 + iVar3 * 2 + 0xfc) = 0, 0.06666667 <= *(float *)(param_1 + 0xf4))
         ) {
        *(undefined2 *)(param_1 + iVar3 * 2 + 0xfc) = 1;
        *(undefined4 *)(param_1 + iVar3 * 4 + 0x13c) = 0;
        iVar2 = rand();
        fStack_50 = ((float)iVar2 / 2.1474836e+09) * 4.6000004;
        if (*(int *)(param_1 + 0x6c) == 0) {
          fStack_90 = fStack_50 + 10.9;
          uStack_8c = 0xc1866666;
          uStack_88 = 0xbf800000;
          uStack_84 = 0x3f800000;
          uStack_4c = 0xc1866666;
          uStack_48 = 0xbf800000;
        }
        else {
          fStack_a0 = fStack_50 + 10.9;
          uStack_9c = 0xc1880000;
          uStack_98 = 0x3fb33333;
          uStack_94 = 0x3f800000;
          uStack_4c = 0xc1880000;
          uStack_48 = 0x3fb33333;
        }
        fStack_50 = fStack_50 + 10.9;
        uStack_44 = 0x3f800000;
        ApplyMatrix__6MatrixCFRC7FVector(auStack_b0,auStack_40,&fStack_50);
        iVar2 = param_1 + iVar3 * 0x10;
        *(int *)(iVar2 + 0x180) = auStack_b0._0_4_;
        *(int *)(iVar2 + 0x184) = auStack_b0._4_4_;
        *(undefined4 *)(iVar2 + 0x188) = uStack_a8;
        *(undefined4 *)(iVar2 + 0x18c) = uStack_a4;
        *(undefined4 *)(param_1 + iVar3 * 4 + 0x280) = 0x3f800000;
        *(undefined4 *)(param_1 + iVar3 * 4 + 0x2c0) = 0x3f800000;
        *(float *)(param_1 + 0xf4) = *(float *)(param_1 + 0xf4) - 0.06666667;
      }
    }
    else if ((sVar1 == 0) && (0.06666667 <= *(float *)(param_1 + 0xf4))) {
      *(undefined2 *)(param_1 + iVar3 * 2 + 0xfc) = 1;
      *(undefined4 *)(param_1 + iVar3 * 4 + 0x13c) = 0;
      iVar2 = rand();
      fStack_50 = ((float)iVar2 / 2.1474836e+09) * 4.6000004;
      if (*(int *)(param_1 + 0x6c) == 0) {
        fStack_60 = fStack_50 + 10.9;
        uStack_5c = 0xc1866666;
        uStack_58 = 0xbf800000;
        uStack_54 = 0x3f800000;
        uStack_4c = 0xc1866666;
        uStack_48 = 0xbf800000;
      }
      else {
        fStack_70 = fStack_50 + 10.9;
        uStack_6c = 0xc1880000;
        uStack_68 = 0x3fb33333;
        uStack_64 = 0x3f800000;
        uStack_4c = 0xc1880000;
        uStack_48 = 0x3fb33333;
      }
      fStack_50 = fStack_50 + 10.9;
      uStack_44 = 0x3f800000;
      ApplyMatrix__6MatrixCFRC7FVector(auStack_80,auStack_40,&fStack_50);
      iVar2 = param_1 + iVar3 * 0x10;
      *(int *)(iVar2 + 0x180) = auStack_80._0_4_;
      *(int *)(iVar2 + 0x184) = auStack_80._4_4_;
      *(undefined4 *)(iVar2 + 0x188) = uStack_78;
      *(undefined4 *)(iVar2 + 0x18c) = uStack_74;
      *(undefined4 *)(param_1 + iVar3 * 4 + 0x280) = 0x3f800000;
      *(undefined4 *)(param_1 + iVar3 * 4 + 0x2c0) = 0x3f800000;
      *(float *)(param_1 + 0xf4) = *(float *)(param_1 + 0xf4) - 0.06666667;
    }
  }
  return 0;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005351d0  MakePacket__19RaidenAddAttribute1Fv
 * C++: RaidenAddAttribute1::MakePacket()
 * size: 0x2044 bytes
 * --------------------------------------------------------------------------- */
/* WARNING: Removing unreachable block (ram,0x00536bd8) */
/* WARNING: Removing unreachable block (ram,0x00536a58) */
/* WARNING: Removing unreachable block (ram,0x00536b18) */
/* WARNING: Removing unreachable block (ram,0x005368bc) */

void MakePacket__19RaidenAddAttribute1Fv(int param_1)

{
  bool bVar1;
  undefined4 *puVar2;
  undefined1 auVar3 [16];
  bool bVar4;
  undefined1 auVar5 [16];
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  undefined1 auVar8 [16];
  undefined1 auVar9 [16];
  undefined1 auVar10 [16];
  float in_zero_lo;
  float in_zero_hi;
  float in_zero_udw;
  undefined4 in_register_0000000c;
  undefined4 uVar11;
  undefined8 uVar12;
  int iVar13;
  undefined8 in_v1_udw;
  undefined1 auVar14 [16];
  uint uVar15;
  int iVar16;
  float fVar17;
  int iVar18;
  int iVar19;
  int iVar20;
  undefined1 in_vf0 [16];
  undefined1 auVar21 [16];
  undefined1 auVar22 [16];
  undefined1 auVar23 [16];
  undefined1 auStack_dc0 [16];
  undefined1 auStack_db0 [16];
  float fStack_da0;
  float fStack_d9c;
  undefined4 uStack_d98;
  undefined4 uStack_d94;
  float fStack_d90;
  float fStack_d8c;
  undefined4 uStack_d88;
  undefined4 uStack_d84;
  undefined4 uStack_d80;
  float fStack_d7c;
  undefined4 uStack_d78;
  undefined4 uStack_d74;
  undefined4 uStack_d70;
  float fStack_d6c;
  undefined4 uStack_d68;
  undefined4 uStack_d64;
  undefined4 uStack_d60;
  float fStack_d5c;
  undefined4 uStack_d58;
  undefined4 uStack_d54;
  undefined4 uStack_d50;
  float fStack_d4c;
  undefined4 uStack_d48;
  undefined4 uStack_d44;
  float fStack_d40;
  float fStack_d3c;
  undefined4 uStack_d38;
  undefined4 uStack_d34;
  float fStack_d30;
  float fStack_d2c;
  undefined4 uStack_d28;
  undefined4 uStack_d24;
  undefined4 uStack_d20;
  undefined4 uStack_d1c;
  undefined4 uStack_d18;
  undefined4 uStack_d14;
  undefined4 uStack_d10;
  undefined4 uStack_d0c;
  undefined4 uStack_d08;
  undefined4 uStack_d04;
  undefined4 uStack_d00;
  undefined4 uStack_cfc;
  undefined4 uStack_cf8;
  undefined4 uStack_cf4;
  undefined4 uStack_cf0;
  undefined4 uStack_cec;
  undefined4 uStack_ce8;
  undefined4 uStack_ce4;
  undefined4 uStack_ce0;
  undefined4 uStack_cdc;
  undefined4 uStack_cd8;
  undefined4 uStack_cd4;
  undefined4 uStack_cd0;
  undefined4 uStack_ccc;
  undefined4 uStack_cc8;
  undefined4 uStack_cc4;
  undefined4 uStack_cc0;
  undefined4 uStack_cbc;
  undefined4 uStack_cb8;
  undefined4 uStack_cb4;
  undefined4 uStack_cb0;
  undefined4 uStack_cac;
  undefined4 uStack_ca8;
  undefined4 uStack_ca4;
  undefined4 uStack_ca0;
  undefined4 uStack_c9c;
  undefined4 uStack_c98;
  undefined4 uStack_c94;
  undefined1 auStack_c90 [64];
  undefined4 uStack_c50;
  undefined4 uStack_c4c;
  undefined4 uStack_c48;
  undefined4 uStack_c44;
  undefined4 uStack_c40;
  undefined4 uStack_c3c;
  undefined4 uStack_c38;
  undefined4 uStack_c34;
  undefined4 uStack_c30;
  undefined4 uStack_c2c;
  undefined4 uStack_c28;
  undefined4 uStack_c24;
  undefined4 uStack_c20;
  undefined4 uStack_c1c;
  undefined4 uStack_c18;
  undefined4 uStack_c14;
  undefined4 uStack_c10;
  undefined4 uStack_c0c;
  undefined4 uStack_c08;
  undefined4 uStack_c04;
  int aiStack_c00 [288];
  float fStack_780;
  float fStack_77c;
  float fStack_778;
  float fStack_770;
  float fStack_76c;
  float fStack_768;
  undefined4 uStack_760;
  undefined4 uStack_75c;
  undefined4 uStack_758;
  undefined4 uStack_754;
  undefined4 uStack_750;
  undefined4 uStack_74c;
  undefined4 uStack_748;
  undefined4 uStack_744;
  undefined4 auStack_740 [16];
  int aiStack_700 [6];
  int iStack_6e8;
  float afStack_6c0 [5];
  float fStack_6ac;
  float fStack_6a8;
  undefined4 uStack_6a4;
  float fStack_6a0;
  float fStack_69c;
  float fStack_698;
  undefined4 uStack_694;
  float fStack_690;
  float fStack_68c;
  float fStack_688;
  undefined4 uStack_684;
  float afStack_2c0 [16];
  float afStack_280 [16];
  float fStack_240;
  float fStack_23c;
  undefined4 uStack_238;
  undefined4 uStack_234;
  float fStack_230;
  float fStack_22c;
  undefined4 uStack_228;
  undefined4 uStack_224;
  undefined4 uStack_220;
  float fStack_21c;
  undefined4 uStack_218;
  undefined4 uStack_214;
  undefined4 uStack_210;
  float fStack_20c;
  undefined4 uStack_208;
  undefined4 uStack_204;
  undefined4 uStack_200;
  float fStack_1fc;
  undefined4 uStack_1f8;
  undefined4 uStack_1f4;
  undefined4 uStack_1f0;
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
  float afStack_1a0 [7];
  undefined4 uStack_184;
  undefined1 auStack_180 [8];
  float fStack_178;
  undefined4 uStack_174;
  undefined1 auStack_170 [8];
  float fStack_168;
  undefined4 uStack_164;
  float afStack_160 [16];
  float fStack_120;
  float fStack_11c;
  float fStack_118;
  undefined1 auStack_110 [16];
  undefined1 auStack_100 [16];
  undefined1 auStack_f0 [16];
  undefined1 auStack_e0 [16];
  undefined4 uStack_d0;
  undefined4 uStack_cc;
  undefined4 uStack_c8;
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
  undefined1 auStack_50 [72];
  float fStack_8;
  float fStack_4;
  
  __ct__6MatrixFRC6Matrix(auStack_50,
                  *(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x144) + 0x30)
                  + (uint)*(byte *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0
                                                     + 0x144) + 0xe4) +
                                   *(int *)(param_1 + 100) * 0x110) * 0x1f0 +
                  (bGpffff8340 & 1) * 0x40);
  uStack_c10 = 0xbf800000;
  uStack_c0c = 0xbf800000;
  uStack_c08 = 0;
  uStack_c04 = 0x3f800000;
  uStack_d0 = 0xbf800000;
  uStack_cc = 0xbf800000;
  uStack_c8 = 0;
  uStack_c4 = 0x3f800000;
  uStack_c20 = 0xbf800000;
  uStack_c1c = 0x3f800000;
  uStack_c18 = 0;
  uStack_c14 = 0x3f800000;
  uStack_c0 = 0xbf800000;
  uStack_bc = 0x3f800000;
  uStack_b8 = 0;
  uStack_b4 = 0x3f800000;
  uStack_c30 = 0x3f800000;
  uStack_c2c = 0xbf800000;
  uStack_c28 = 0;
  uStack_c24 = 0x3f800000;
  uStack_b0 = 0x3f800000;
  uStack_ac = 0xbf800000;
  uStack_a8 = 0;
  uStack_a4 = 0x3f800000;
  uStack_c40 = 0x3f800000;
  uStack_c3c = 0x3f800000;
  uStack_c38 = 0;
  uStack_c34 = 0x3f800000;
  uStack_a0 = 0x3f800000;
  uStack_9c = 0x3f800000;
  uStack_98 = 0;
  uStack_94 = 0x3f800000;
  uStack_c50 = 0x40400000;
  uStack_c4c = 0;
  uStack_c48 = 0;
  uStack_c44 = 0x3f800000;
  uStack_90 = 0x40400000;
  uStack_8c = 0;
  uStack_88 = 0;
  uStack_84 = 0x3f800000;
  __ct__6MatrixFRC6Matrix(auStack_110,iGpffff8598 + 0x240);
  auStack_e0._0_12_ = ZEXT812(0);
  auStack_e0._12_4_ = 0x3f800000;
  fStack_120 = in_zero_lo;
  fStack_11c = in_zero_hi;
  fStack_118 = in_zero_udw;
  RotTransVector(afStack_160,&uStack_d0,auStack_110,5);
  auStack_180._4_4_ = in_zero_hi;
  auStack_180._0_4_ = in_zero_lo;
  fStack_178 = in_zero_udw;
  uStack_174 = in_register_0000000c;
  auStack_170._4_4_ = in_zero_hi;
  auStack_170._0_4_ = in_zero_lo;
  fStack_168 = in_zero_udw;
  uStack_164 = in_register_0000000c;
  afStack_1a0[0] = in_zero_lo;
  afStack_1a0[1] = in_zero_hi;
  afStack_1a0[2] = in_zero_udw;
  afStack_1a0[3] = (float)in_register_0000000c;
  afStack_1a0[4] = in_zero_lo;
  afStack_1a0[5] = in_zero_hi;
  afStack_1a0[6] = in_zero_udw;
  uStack_184 = in_register_0000000c;
  GetViewScreenMatrix__9GsxCameraFv(auStack_c90,iGpffff8598);
  for (iVar13 = 0; iVar13 < 4; iVar13 = iVar13 + 1) {
    auStack_740[iVar13 * 4] = *(undefined4 *)(auStack_110 + iVar13 * 0x10);
    auStack_740[iVar13 * 4 + 1] = *(undefined4 *)(auStack_110 + iVar13 * 0x10 + 4);
    auStack_740[iVar13 * 4 + 2] = *(undefined4 *)(auStack_110 + iVar13 * 0x10 + 8);
    auStack_740[iVar13 * 4 + 3] = *(undefined4 *)(auStack_110 + iVar13 * 0x10 + 0xc);
  }
  if (*(int *)(param_1 + 0x6c) == 0) {
    uStack_ca0 = 0x412e6666;
    uStack_c9c = 0xc1866666;
    uStack_c98 = 0xbf800000;
    uStack_c94 = 0x3f800000;
    uStack_75c = 0xc1866666;
    uStack_758 = 0xbf800000;
    uStack_cb0 = 0x41780000;
    uStack_cac = 0xc1866666;
    uStack_ca8 = 0xbf800000;
    uStack_ca4 = 0x3f800000;
    uStack_74c = 0xc1866666;
    uStack_748 = 0xbf800000;
  }
  else {
    uStack_cc0 = 0x412e6666;
    uStack_cbc = 0xc1880000;
    uStack_cb8 = 0x3fb33333;
    uStack_cb4 = 0x3f800000;
    uStack_75c = 0xc1880000;
    uStack_758 = 0x3fb33333;
    uStack_cd0 = 0x41780000;
    uStack_ccc = 0xc1880000;
    uStack_cc8 = 0x3fb33333;
    uStack_cc4 = 0x3f800000;
    uStack_74c = 0xc1880000;
    uStack_748 = 0x3fb33333;
  }
  uStack_744 = 0x3f800000;
  uStack_750 = 0x41780000;
  uStack_754 = 0x3f800000;
  uStack_760 = 0x412e6666;
  fStack_780 = in_zero_lo;
  fStack_77c = in_zero_hi;
  fStack_778 = in_zero_udw;
  fStack_770 = in_zero_lo;
  fStack_76c = in_zero_hi;
  fStack_768 = in_zero_udw;
  RotTransVector(&fStack_780,&uStack_760,auStack_50,2);
  for (iVar13 = 0; iVar13 < 2; iVar13 = iVar13 + 1) {
    auVar21 = _lqc2(*(undefined1 (*) [16])(*(int *)(iGpffff86b4 + 0x4324) + 0x30));
    auVar22 = _lqc2(*(undefined1 (*) [16])(&fStack_780 + iVar13 * 4));
    auVar21 = _vsub(auVar21,auVar22);
    auStack_db0 = _sqc2(auVar21);
    __ct__7FVectorFRC7FVector(&uStack_ce0,auStack_db0);
    uStack_760 = uStack_ce0;
    uStack_75c = uStack_cdc;
    uStack_758 = uStack_cd8;
    uStack_754 = uStack_cd4;
    Normalize__7FVectorFv(&uStack_760);
    __amu__7FVectorFf(0x3f000000,&uStack_760);
    auVar21._4_4_ = uStack_75c;
    auVar21._0_4_ = uStack_760;
    auVar21._8_4_ = uStack_758;
    auVar21._12_4_ = uStack_754;
    auVar22 = _lqc2(auVar21);
    auVar21 = _lqc2(*(undefined1 (*) [16])(&fStack_780 + iVar13 * 4));
    auVar21 = _vadd(auVar21,auVar22);
    auVar21 = _sqc2(auVar21);
    *(undefined1 (*) [16])(&fStack_780 + iVar13 * 4) = auVar21;
  }
  afStack_6c0[0] = fStack_780;
  afStack_6c0[1] = fStack_77c;
  afStack_6c0[2] = fStack_778;
  afStack_6c0[3] = 1.0;
  afStack_6c0[4] = fStack_770;
  fStack_6ac = fStack_76c;
  fStack_6a8 = fStack_768;
  uStack_6a4 = 0x3f800000;
  fStack_6a0 = fStack_780 + fStack_120;
  fStack_69c = fStack_77c + fStack_11c;
  fStack_698 = fStack_778 + fStack_118;
  uStack_694 = 0x3f800000;
  fStack_690 = fStack_770 + fStack_120;
  fStack_68c = fStack_76c + fStack_11c;
  fStack_688 = fStack_768 + fStack_118;
  uStack_684 = 0x3f800000;
  sceVu0RotTransPersN(aiStack_700,auStack_740,afStack_6c0,4,0);
  for (iVar13 = 0; iVar13 < 4; iVar13 = iVar13 + 1) {
    afStack_1a0[iVar13 * 4] = (float)aiStack_700[iVar13 * 4] / 16.0 - 1792.0;
    afStack_1a0[iVar13 * 4 + 1] = (float)aiStack_700[iVar13 * 4 + 1] / 16.0 - 1824.0;
    afStack_1a0[iVar13 * 4 + 2] = 0.0;
    afStack_1a0[iVar13 * 4 + 3] = 1.0;
  }
  auVar9._4_4_ = afStack_1a0[5];
  auVar9._0_4_ = afStack_1a0[4];
  auVar9._8_4_ = afStack_1a0[6];
  auVar9._12_4_ = uStack_184;
  auVar21 = _lqc2(auVar9);
  auVar7._4_4_ = afStack_1a0[1];
  auVar7._0_4_ = afStack_1a0[0];
  auVar7._8_4_ = afStack_1a0[2];
  auVar7._12_4_ = afStack_1a0[3];
  auVar22 = _lqc2(auVar7);
  auVar21 = _vsub(auVar21,auVar22);
  auStack_dc0 = _sqc2(auVar21);
  __ct__7FVectorFRC7FVector(&uStack_cf0,auStack_dc0);
  uStack_1c0 = uStack_cf0;
  uStack_1bc = uStack_cec;
  uStack_1b8 = uStack_ce8;
  uStack_1b4 = uStack_ce4;
  Normalize__7FVectorFv(&uStack_1c0);
  uStack_d00 = 0x3f800000;
  uStack_cfc = 0;
  uStack_cf8 = 0;
  uStack_cf4 = 0x3f800000;
  auVar23._4_4_ = uStack_1bc;
  auVar23._0_4_ = uStack_1c0;
  auVar23._8_4_ = uStack_1b8;
  auVar23._12_4_ = uStack_1b4;
  auVar21 = _lqc2(auVar23);
  auVar22._12_4_ = 0x3f800000;
  auVar22._0_12_ = ZEXT812(0x3f800000);
  auVar22 = _lqc2(auVar22);
  auVar21 = _vmul(auVar21,auVar22);
  auVar21 = _vaddbc(auVar21,auVar21);
  auVar21 = _vaddbc(auVar21,auVar21);
  auVar21 = _qmfc2(auVar21._0_4_);
  if (auVar21._0_4_ <= -1.0) {
    fVar17 = 3.141592;
  }
  else if (1.0 <= auVar21._0_4_) {
    fVar17 = 0.0;
  }
  else {
    fVar17 = (float)acosf();
  }
  auVar21 = _vmr32(in_vf0);
  auVar22 = _vmr32(auVar21);
  auVar23 = _vmr32(auVar22);
  auStack_e0 = _sqc2(in_vf0);
  auStack_f0 = _sqc2(auVar21);
  auStack_100 = _sqc2(auVar22);
  auStack_110 = _sqc2(auVar23);
  sceVu0RotMatrixZ(fVar17,auStack_110,auStack_110);
  uStack_d20 = 0x3f800000;
  uStack_d1c = 0;
  uStack_d18 = 0;
  uStack_d14 = 0x3f800000;
  ApplyMatrix__6MatrixCFRC7FVector(&uStack_d10,auStack_110,&uStack_d20);
  uStack_1b0 = uStack_d10;
  uStack_1ac = uStack_d0c;
  uStack_1a8 = uStack_d08;
  uStack_1a4 = uStack_d04;
  auVar6._4_4_ = uStack_d0c;
  auVar6._0_4_ = uStack_d10;
  auVar6._8_4_ = uStack_d08;
  auVar6._12_4_ = uStack_d04;
  auVar21 = _lqc2(auVar6);
  auVar5._4_4_ = uStack_1bc;
  auVar5._0_4_ = uStack_1c0;
  auVar5._8_4_ = uStack_1b8;
  auVar5._12_4_ = uStack_1b4;
  auVar22 = _lqc2(auVar5);
  auVar21 = _vmul(auVar21,auVar22);
  auVar21 = _vaddbc(auVar21,auVar21);
  auVar21 = _vaddbc(auVar21,auVar21);
  auVar21 = _qmfc2(auVar21._0_4_);
  if (auVar21._0_4_ < 0.999999) {
    fVar17 = -fVar17;
  }
  auVar21 = _vmr32(in_vf0);
  auVar22 = _vmr32(auVar21);
  auVar23 = _vmr32(auVar22);
  auStack_e0 = _sqc2(in_vf0);
  auStack_f0 = _sqc2(auVar21);
  auStack_100 = _sqc2(auVar22);
  auStack_110 = _sqc2(auVar23);
  sceVu0RotMatrixZ(fVar17,auStack_110,auStack_110);
  auVar8._4_4_ = afStack_1a0[1];
  auVar8._0_4_ = afStack_1a0[0];
  auVar8._8_4_ = afStack_1a0[2];
  auVar8._12_4_ = afStack_1a0[3];
  auVar22 = _lqc2(auVar8);
  auVar21 = _lqc2(_auStack_180);
  auVar21 = _vsub(auVar21,auVar22);
  _auStack_180 = _sqc2(auVar21);
  auVar10._4_4_ = afStack_1a0[5];
  auVar10._0_4_ = afStack_1a0[4];
  auVar10._8_4_ = afStack_1a0[6];
  auVar10._12_4_ = uStack_184;
  auVar22 = _lqc2(auVar10);
  auVar21 = _lqc2(_auStack_170);
  auVar21 = _vsub(auVar21,auVar22);
  _auStack_170 = _sqc2(auVar21);
  fStack_8 = (float)Length__7FVectorCFv(auStack_180);
  fStack_da0 = (float)Length__7FVectorCFv(auStack_170);
  fStack_d30 = -fStack_8;
  fStack_d2c = fStack_8;
  uStack_d28 = 0;
  uStack_d24 = 0x3f800000;
  fStack_23c = fStack_8;
  uStack_238 = 0;
  uStack_234 = 0x3f800000;
  fStack_d40 = -fStack_8;
  fStack_d3c = -fStack_8;
  uStack_d38 = 0;
  uStack_d34 = 0x3f800000;
  uStack_228 = 0;
  uStack_224 = 0x3f800000;
  uStack_d50 = 0;
  fStack_d4c = fStack_8;
  uStack_d48 = 0;
  uStack_d44 = 0x3f800000;
  uStack_220 = 0;
  fStack_21c = fStack_8;
  uStack_218 = 0;
  uStack_214 = 0x3f800000;
  uStack_d60 = 0;
  fStack_d5c = -fStack_8;
  uStack_d58 = 0;
  uStack_d54 = 0x3f800000;
  uStack_210 = 0;
  uStack_208 = 0;
  uStack_204 = 0x3f800000;
  uStack_d70 = 0;
  uStack_d68 = 0;
  uStack_d64 = 0x3f800000;
  uStack_200 = 0;
  uStack_1f8 = 0;
  uStack_1f4 = 0x3f800000;
  fStack_d7c = -fStack_da0;
  uStack_d80 = 0;
  uStack_d78 = 0;
  uStack_d74 = 0x3f800000;
  uStack_1f0 = 0;
  uStack_1e8 = 0;
  uStack_1e4 = 0x3f800000;
  uStack_d88 = 0;
  uStack_d84 = 0x3f800000;
  uStack_1d8 = 0;
  uStack_1d4 = 0x3f800000;
  fStack_d9c = -fStack_da0;
  uStack_d98 = 0;
  uStack_d94 = 0x3f800000;
  uStack_1c8 = 0;
  uStack_1c4 = 0x3f800000;
  fStack_d90 = fStack_da0;
  fStack_d8c = fStack_da0;
  fStack_d6c = fStack_da0;
  fStack_240 = fStack_d30;
  fStack_230 = fStack_d40;
  fStack_22c = fStack_d3c;
  fStack_20c = fStack_d5c;
  fStack_1fc = fStack_da0;
  fStack_1ec = fStack_d7c;
  fStack_1e0 = fStack_da0;
  fStack_1dc = fStack_da0;
  fStack_1d0 = fStack_da0;
  fStack_1cc = fStack_d9c;
  fStack_4 = fStack_da0;
  RotTransVector(afStack_2c0,&fStack_240,auStack_110,8);
  for (iVar13 = 0; iVar13 < 4; iVar13 = iVar13 + 1) {
    aiStack_c00[iVar13 * 4] = (int)((afStack_1a0[0] + afStack_2c0[iVar13 * 4] + 1792.0) * 16.0);
    aiStack_c00[iVar13 * 4 + 1] =
         (int)((afStack_1a0[1] + afStack_2c0[iVar13 * 4 + 1] + 1824.0) * 16.0);
    aiStack_c00[iVar13 * 4 + 2] = aiStack_700[2];
    aiStack_c00[iVar13 * 4 + 3] = 1;
  }
  for (iVar13 = 4; iVar13 < 8; iVar13 = iVar13 + 1) {
    aiStack_c00[iVar13 * 4] = (int)((afStack_1a0[4] + afStack_2c0[iVar13 * 4] + 1792.0) * 16.0);
    aiStack_c00[iVar13 * 4 + 1] =
         (int)((afStack_1a0[5] + afStack_2c0[iVar13 * 4 + 1] + 1824.0) * 16.0);
    aiStack_c00[iVar13 * 4 + 2] = iStack_6e8;
    aiStack_c00[iVar13 * 4 + 3] = 1;
  }
  for (iVar13 = 0; iVar13 < 0x10; iVar13 = iVar13 + 1) {
    for (iVar18 = 0; iVar18 < 4; iVar18 = iVar18 + 1) {
      afStack_6c0[(iVar18 + iVar13 * 4) * 4] =
           *(float *)(param_1 + iVar13 * 0x10 + 0x180) +
           *(float *)(param_1 + iVar13 * 4 + 0x280) * afStack_160[iVar18 * 4];
      afStack_6c0[(iVar18 + iVar13 * 4) * 4 + 1] =
           *(float *)(param_1 + iVar13 * 0x10 + 0x184) +
           *(float *)(param_1 + iVar13 * 4 + 0x280) * afStack_160[iVar18 * 4 + 1];
      afStack_6c0[(iVar18 + iVar13 * 4) * 4 + 2] =
           *(float *)(param_1 + iVar13 * 0x10 + 0x188) +
           *(float *)(param_1 + iVar13 * 4 + 0x280) * afStack_160[iVar18 * 4 + 2];
      afStack_6c0[(iVar18 + iVar13 * 4) * 4 + 3] = 1.0;
    }
  }
  sceVu0RotTransPersN(aiStack_c00 + 0x20,auStack_740,afStack_6c0,0x40,0);
  bVar4 = false;
  iVar13 = 0;
  for (iVar18 = 0; iVar18 < 0x48; iVar18 = iVar18 + 1) {
    if (iVar18 < 8) {
      if (((aiStack_c00[iVar18 * 4] < 0) || (0x10000 < aiStack_c00[iVar18 * 4])) ||
         ((aiStack_c00[iVar18 * 4 + 1] < 0 ||
          ((0x10000 < aiStack_c00[iVar18 * 4 + 1] || (aiStack_c00[iVar18 * 4 + 2] < 0)))))) {
        bVar4 = true;
      }
      aiStack_c00[iVar18 * 4 + 2] = (int)((float)aiStack_c00[iVar18 * 4 + 2] / 16.0);
      iVar13 = iVar13 + aiStack_c00[iVar18 * 4 + 2];
    }
    else {
      uVar15 = iVar18 - 8U & 3;
      if (((int)(iVar18 - 8U) < 0) && (uVar15 != 0)) {
        uVar15 = uVar15 - 4;
      }
      if (uVar15 == 0) {
        iVar19 = iVar18 + -8;
        if (iVar19 < 0) {
          iVar19 = iVar18 + -5;
        }
        *(undefined2 *)(param_1 + (iVar19 >> 2) * 2 + 0x11c) = 0;
      }
      if ((((aiStack_c00[iVar18 * 4] < 0) || (0x10000 < aiStack_c00[iVar18 * 4])) ||
          (aiStack_c00[iVar18 * 4 + 1] < 0)) ||
         ((0x10000 < aiStack_c00[iVar18 * 4 + 1] || (aiStack_c00[iVar18 * 4 + 2] < 0)))) {
        iVar19 = iVar18 + -8;
        if (iVar19 < 0) {
          iVar19 = iVar18 + -5;
        }
        *(undefined2 *)(param_1 + (iVar19 >> 2) * 2 + 0x11c) = 1;
      }
      aiStack_c00[iVar18 * 4 + 2] = (int)((float)aiStack_c00[iVar18 * 4 + 2] / 16.0);
    }
  }
  if (iVar13 < 0) {
    iVar13 = iVar13 + 7;
  }
  *(int *)(param_1 + 0x50) = iVar13 >> 3;
  bVar1 = (*(byte *)(param_1 + 0x40) & 1) == 0;
  uVar15 = (uint)bVar1;
  if (*(int *)(param_1 + uVar15 * 4 + 0x18) == 0) {
    uVar11 = __nwa__FUi(0x6a0);
    *(undefined4 *)(param_1 + uVar15 * 4 + 0x18) = uVar11;
    iVar13 = *(int *)(param_1 + uVar15 * 4 + 0x18);
    *(undefined4 *)(iVar13 + 0x10) = 0x10000012;
    *(undefined4 *)(iVar13 + 0x14) = 0;
    *(undefined4 *)(iVar13 + 0x18) = 0;
    *(undefined4 *)(iVar13 + 0x1c) = 0x50000012;
    *(undefined8 *)(iVar13 + 0x20) = 0x6000000000000001;
    *(undefined8 *)(iVar13 + 0x28) = 0xe6e8ee;
    *(undefined8 *)(iVar13 + 0x30) = 1;
    *(undefined8 *)(iVar13 + 0x38) = 0x3f;
    *(undefined8 *)(iVar13 + 0x40) = 0x60;
    *(undefined8 *)(iVar13 + 0x48) = 0x14;
    *(undefined8 *)(iVar13 + 0x50) = 5;
    *(undefined8 *)(iVar13 + 0x58) = 0;
    *(undefined8 *)(iVar13 + 0x60) = 0x53001;
    *(undefined8 *)(iVar13 + 0x68) = 0x47;
    uVar12 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x42ec),1);
    *(undefined8 *)(iVar13 + 0x70) = uVar12;
    *(undefined8 *)(iVar13 + 0x78) = 0;
    *(undefined8 *)(iVar13 + 0x80) = 0x48;
    *(undefined8 *)(iVar13 + 0x88) = 0x42;
    *(undefined8 *)(iVar13 + 0x90) = 0x6400000000000001;
    *(undefined8 *)(iVar13 + 0x98) = 0xc3c310;
    *(undefined8 *)(iVar13 + 0xa0) = 0x154;
    *(undefined8 *)(iVar13 + 0xb0) = 0;
    *(long *)(iVar13 + 0xc0) =
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42ec) + 4) << 4) << 0x10;
    *(undefined8 *)(iVar13 + 0xd0) = 0x2400000000008006;
    *(undefined8 *)(iVar13 + 0xd8) = 0x43;
    *(long *)(iVar13 + 0xe0) =
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42ec) + 2) << 3);
    *(long *)(iVar13 + 0xf0) =
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42ec) + 2) << 3) |
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42ec) + 4) << 4) << 0x10;
    *(long *)(iVar13 + 0x100) =
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42ec) + 2) << 3);
    *(long *)(iVar13 + 0x110) =
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42ec) + 2) << 3) |
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42ec) + 4) << 4) << 0x10;
    *(long *)(iVar13 + 0x120) =
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42ec) + 2) << 4);
    *(long *)(iVar13 + 0x130) =
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42ec) + 2) << 4) |
         (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42ec) + 4) << 4) << 0x10;
    *(undefined4 *)(iVar13 + 0x140) = 0x50000000;
    *(undefined4 *)(iVar13 + 0x144) =
         *(undefined4 *)
          (*(int *)(iGpffff86b4 + 0x42f0) +
           (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f0) + 10) * 4 + 0xc);
    *(undefined4 *)(iVar13 + 0x148) = 0;
    *(undefined4 *)(iVar13 + 0x14c) = 0;
    *(undefined4 *)(iVar13 + 0x150) = 0x60000054;
    *(undefined4 *)(iVar13 + 0x154) = 0;
    *(undefined4 *)(iVar13 + 0x158) = 0;
    *(undefined4 *)(iVar13 + 0x15c) = 0x50000054;
    *(undefined8 *)(iVar13 + 0x160) = 0x2000000000000001;
    *(undefined8 *)(iVar13 + 0x168) = 0x6e;
    *(undefined8 *)(iVar13 + 0x170) = 1;
    *(undefined8 *)(iVar13 + 0x178) = 0x3f;
    uVar12 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x42f0),1);
    *(undefined8 *)(iVar13 + 0x180) = uVar12;
    *(undefined8 *)(iVar13 + 0x188) = 0;
    auVar14._8_8_ = in_v1_udw;
    auVar14._0_8_ = 0xa400000000008010;
    auVar3._4_4_ = in_zero_hi;
    auVar3._0_4_ = in_zero_lo;
    auVar3._8_4_ = in_zero_udw;
    auVar3._12_4_ = in_register_0000000c;
    auVar21 = _pcpyld(auVar3,auVar14);
    *(long *)(iVar13 + 400) = auVar21._0_8_;
    *(undefined8 *)(iVar13 + 0x198) = 0x4343c3c310;
    for (iVar18 = 0; iVar18 < 0x10; iVar18 = iVar18 + 1) {
      *(undefined8 *)(iVar13 + (iVar18 * 5 + 0x1a) * 0x10) = 0x154;
      *(long *)(iVar13 + (iVar18 * 5 + 0x1b) * 0x10) =
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f0) + 2) << 2) |
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f0) + 4) << 2) << 0x10;
      *(long *)(iVar13 + (iVar18 * 5 + 0x1c) * 0x10) =
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f0) + 2) << 2) |
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f0) + 4) * 0xc) << 0x10;
      *(long *)(iVar13 + (iVar18 * 5 + 0x1d) * 0x10) =
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f0) + 4) << 2) << 0x10 |
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f0) + 2) * 0xc);
      *(long *)(iVar13 + (iVar18 * 5 + 0x1e) * 0x10) =
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f0) + 2) * 0xc) |
           (long)(int)((uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42f0) + 4) * 0xc) << 0x10;
    }
  }
  puVar2 = *(undefined4 **)(param_1 + uVar15 * 4 + 0x18);
  *puVar2 = 0x50000000;
  puVar2[1] = *(undefined4 *)
               (*(int *)(iGpffff86b4 + 0x42ec) +
                (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42ec) + 10) * 4 + 0xc);
  puVar2[2] = 0;
  puVar2[3] = 0;
  iVar13 = (int)(*(float *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x144) + 0x4e4
                           ) *
                 *(float *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x144) + 0x4ec
                           ) * 128.0);
  fVar17 = (float)sinf(*(undefined4 *)(param_1 + 0xf8));
  fVar17 = (fVar17 + 1.0) / 2.0;
  iVar18 = (int)((float)*(byte *)(*(int *)(param_1 + 0x60) * 0xc + 0x652b64) +
                fVar17 * (float)(int)((uint)*(byte *)(*(int *)(param_1 + 0x60) * 0xc + 0x652b68) -
                                     (uint)*(byte *)(*(int *)(param_1 + 0x60) * 0xc + 0x652b64)));
  iVar19 = (int)((float)*(byte *)(*(int *)(param_1 + 0x60) * 0xc + 0x652b65) +
                fVar17 * (float)(int)((uint)*(byte *)(*(int *)(param_1 + 0x60) * 0xc + 0x652b69) -
                                     (uint)*(byte *)(*(int *)(param_1 + 0x60) * 0xc + 0x652b65)));
  iVar20 = (int)((float)*(byte *)(*(int *)(param_1 + 0x60) * 0xc + 0x652b66) +
                fVar17 * (float)(int)((uint)*(byte *)(*(int *)(param_1 + 0x60) * 0xc + 0x652b6a) -
                                     (uint)*(byte *)(*(int *)(param_1 + 0x60) * 0xc + 0x652b66)));
  *(ulong *)(puVar2 + 0x2a) =
       (long)iVar13 << 0x18 | (long)iVar20 << 0x10 | (long)iVar18 | (long)iVar19 << 8 | 0x100000000;
  if (bVar4) {
    *(undefined8 *)(puVar2 + 0x2e) = 0x71006f00;
    *(undefined8 *)(puVar2 + 0x32) = 0x71006f00;
    *(undefined8 *)(puVar2 + 0x3a) = 0x71006f00;
    *(undefined8 *)(puVar2 + 0x3e) = 0x71006f00;
    *(undefined8 *)(puVar2 + 0x42) = 0x71006f00;
    *(undefined8 *)(puVar2 + 0x46) = 0x71006f00;
    *(undefined8 *)(puVar2 + 0x4a) = 0x71006f00;
    *(undefined8 *)(puVar2 + 0x4e) = 0x71006f00;
  }
  else {
    *(long *)(puVar2 + 0x2e) =
         (long)aiStack_c00[2] << 0x20 | (long)aiStack_c00[0] | (long)aiStack_c00[1] << 0x10;
    *(long *)(puVar2 + 0x32) =
         (long)aiStack_c00[6] << 0x20 | (long)aiStack_c00[4] | (long)aiStack_c00[5] << 0x10;
    *(long *)(puVar2 + 0x3a) =
         (long)aiStack_c00[10] << 0x20 | (long)aiStack_c00[8] | (long)aiStack_c00[9] << 0x10;
    *(long *)(puVar2 + 0x3e) =
         (long)aiStack_c00[0xe] << 0x20 | (long)aiStack_c00[0xc] | (long)aiStack_c00[0xd] << 0x10;
    *(long *)(puVar2 + 0x42) =
         (long)aiStack_c00[0x12] << 0x20 | (long)aiStack_c00[0x10] | (long)aiStack_c00[0x11] << 0x10
    ;
    *(long *)(puVar2 + 0x46) =
         (long)aiStack_c00[0x16] << 0x20 | (long)aiStack_c00[0x14] | (long)aiStack_c00[0x15] << 0x10
    ;
    *(long *)(puVar2 + 0x4a) =
         (long)aiStack_c00[0x1a] << 0x20 | (long)aiStack_c00[0x18] | (long)aiStack_c00[0x19] << 0x10
    ;
    *(long *)(puVar2 + 0x4e) =
         (long)aiStack_c00[0x1e] << 0x20 | (long)aiStack_c00[0x1c] | (long)aiStack_c00[0x1d] << 0x10
    ;
  }
  for (iVar16 = 0; iVar16 < 0x10; iVar16 = iVar16 + 1) {
    if ((*(short *)(param_1 + iVar16 * 2 + 0xfc) == 0) ||
       (*(short *)(param_1 + iVar16 * 2 + 0x11c) != 0)) {
      *(undefined8 *)(puVar2 + (iVar16 * 5 + 0x1b) * 4 + 2) = 0x71006f00;
      *(undefined8 *)(puVar2 + (iVar16 * 5 + 0x1c) * 4 + 2) = 0x71006f00;
      *(undefined8 *)(puVar2 + (iVar16 * 5 + 0x1d) * 4 + 2) = 0x71006f00;
      *(undefined8 *)(puVar2 + (iVar16 * 5 + 0x1e) * 4 + 2) = 0x71006f00;
    }
    else {
      *(ulong *)(puVar2 + (iVar16 * 5 + 0x1a) * 4 + 2) =
           (long)(int)(((float)iVar13 * *(float *)(param_1 + iVar16 * 4 + 0x2c0)) / 128.0) << 0x18 |
           (long)iVar20 << 0x10 | (long)iVar18 | (long)iVar19 << 8 | 0x100000000;
      *(long *)(puVar2 + (iVar16 * 5 + 0x1b) * 4 + 2) =
           (long)aiStack_c00[(iVar16 * 4 + 8) * 4 + 2] << 0x20 |
           (long)aiStack_c00[(iVar16 * 4 + 8) * 4] |
           (long)aiStack_c00[(iVar16 * 4 + 8) * 4 + 1] << 0x10;
      *(long *)(puVar2 + (iVar16 * 5 + 0x1c) * 4 + 2) =
           (long)aiStack_c00[(iVar16 * 4 + 9) * 4 + 2] << 0x20 |
           (long)aiStack_c00[(iVar16 * 4 + 9) * 4] |
           (long)aiStack_c00[(iVar16 * 4 + 9) * 4 + 1] << 0x10;
      *(long *)(puVar2 + (iVar16 * 5 + 0x1d) * 4 + 2) =
           (long)aiStack_c00[(iVar16 * 4 + 10) * 4 + 2] << 0x20 |
           (long)aiStack_c00[(iVar16 * 4 + 10) * 4] |
           (long)aiStack_c00[(iVar16 * 4 + 10) * 4 + 1] << 0x10;
      *(long *)(puVar2 + (iVar16 * 5 + 0x1e) * 4 + 2) =
           (long)aiStack_c00[(iVar16 * 4 + 0xb) * 4 + 2] << 0x20 |
           (long)aiStack_c00[(iVar16 * 4 + 0xb) * 4] |
           (long)aiStack_c00[(iVar16 * 4 + 0xb) * 4 + 1] << 0x10;
    }
  }
  *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfe | bVar1;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054ae10  EndSet__19RaidenAddAttribute1Fv
 * C++: RaidenAddAttribute1::EndSet()
 * size: 0x10 bytes
 * --------------------------------------------------------------------------- */
void EndSet__19RaidenAddAttribute1Fv(void)

{
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b870  @24@__dt__19RaidenAddAttribute1Fv
 * C++: @24@__dt__19RaidenAddAttribute1Fv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int * _24___dt__19RaidenAddAttribute1Fv(int *param_1,short param_2)

{
  int *piVar1;
  
  piVar1 = param_1 + -6;
  if (piVar1 != (int *)0x0) {
    param_1[-1] = 0x409c00;
    param_1[4] = 0x409c10;
    param_1[7] = 0x409c20;
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
 * JP: 0x0054b880  @44@__dt__19RaidenAddAttribute1Fv
 * C++: @44@__dt__19RaidenAddAttribute1Fv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int _44___dt__19RaidenAddAttribute1Fv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x2c;
  if (iVar1 != 0) {
    *(undefined4 *)(param_1 + -0x18) = 0x409c00;
    *(undefined4 *)(param_1 + -4) = 0x409c10;
    *(undefined4 *)(param_1 + 8) = 0x409c20;
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

