/* decomp/H/CmbBreak.c — cleaned Ghidra output (SH2JP_BATTLE.BIN, JP Furokuban, base 0x00430a00).
 * 9 function(s). Types: see types.h. Names/gp globals resolved from symbols/SLPM_602.19.syms. */
#include "types.h"

/* ---------------------------------------------------------------------------
 * JP: 0x00506f10  __ct__8CmbBreakFi
 * C++: CmbBreak::__ct(int)
 * size: 0x13c bytes
 * --------------------------------------------------------------------------- */
int __ct__8CmbBreakFi(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  __ct__7CPolObjFv(param_1);
  __ct__8VIF1PrimFv(param_1 + 0x18);
  *(undefined4 *)(param_1 + 0x2c) = 0;
  *(undefined4 *)(param_1 + 0x30) = 0;
  *(undefined4 *)(param_1 + 0x34) = 0x4049f0;
  *(undefined4 *)(param_1 + 0x14) = 0x40a350;
  *(undefined4 *)(param_1 + 0x28) = 0x40a360;
  *(undefined4 *)(param_1 + 0x34) = 0x40a370;
  *(undefined4 *)(param_1 + 0x38) = 0;
  iGpffff86d0 = param_1;
  uVar1 = GetTimer__7SysToolFv();
  *(undefined4 *)(param_1 + 0x3c) = uVar1;
  *(undefined4 *)(param_1 + 0x40) = 0;
  *(undefined4 *)(param_1 + 0x44) = param_2;
  *(undefined4 *)(param_1 + 0x48) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x18) = 0;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  Entry__7CPollerFP7CPolObjib(iGpffff858c + 0x48,param_1,0x80,0);
  iVar2 = param_1;
  if (param_1 != 0) {
    iVar2 = param_1 + 0x18;
  }
  AddOT__5WorldFiP8VIF1Prim(0x42bf10,0xd,iVar2);
  return param_1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00507050  __dt__8CmbBreakFv
 * C++: CmbBreak::__dt()
 * size: 0x11c bytes
 * --------------------------------------------------------------------------- */
int __dt__8CmbBreakFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x14) = 0x40a350;
    *(undefined4 *)(param_1 + 0x28) = 0x40a360;
    *(undefined4 *)(param_1 + 0x34) = 0x40a370;
    if (*(int *)(param_1 + 0x18) != 0) {
      __dla__FPv(*(undefined4 *)(param_1 + 0x18));
    }
    if (*(int *)(param_1 + 0x1c) != 0) {
      __dla__FPv(*(undefined4 *)(param_1 + 0x1c));
    }
    uGpffff86d0 = 0;
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
 * JP: 0x00507170  Destruct__8CmbBreakFf
 * C++: CmbBreak::Destruct(float)
 * size: 0x74 bytes
 * --------------------------------------------------------------------------- */
void Destruct__8CmbBreakFf(undefined4 param_1)

{
  if ((iGpffff86d0 != 0) && (-1 < (long)((ulong)*(byte *)(iGpffff86d0 + 0x38) << 0x3e))) {
    *(byte *)(iGpffff86d0 + 0x38) = *(byte *)(iGpffff86d0 + 0x38) & 0xfd | 2;
    *(undefined4 *)(iGpffff86d0 + 0x4c) = param_1;
    *(undefined4 *)(iGpffff86d0 + 0x50) = param_1;
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005071f0  Polling__8CmbBreakFv
 * C++: CmbBreak::Polling()
 * size: 0x1a0 bytes
 * --------------------------------------------------------------------------- */
undefined4 Polling__8CmbBreakFv(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  float fVar3;
  
  iVar1 = GetTimer__7SysToolFv();
  fVar3 = (float)(uint)(iVar1 - *(int *)(param_1 + 0x3c)) * 0.001;
  *(int *)(param_1 + 0x3c) = iVar1;
  *(float *)(param_1 + 0x40) = *(float *)(param_1 + 0x40) + fVar3;
  if ((long)((ulong)*(byte *)(param_1 + 0x38) << 0x3e) < 0) {
    *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x4c) - fVar3;
    *(float *)(param_1 + 0x48) = *(float *)(param_1 + 0x4c) / *(float *)(param_1 + 0x50);
  }
  if ((1.4 <= *(float *)(param_1 + 0x40)) ||
     (((long)((ulong)*(byte *)(param_1 + 0x38) << 0x3e) < 0 && (*(float *)(param_1 + 0x4c) <= 0.0)))
     ) {
    iVar1 = iGpffff86d0;
    if (iGpffff86d0 != 0) {
      iVar1 = iGpffff86d0 + 0x18;
    }
    ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,iVar1);
    (**(code **)(*(int *)(iGpffff86d0 + 0x34) + 0xc))();
    uVar2 = 1;
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00507390  MakePacket__8CmbBreakFv
 * C++: CmbBreak::MakePacket()
 * size: 0xb2c bytes
 * --------------------------------------------------------------------------- */
/* WARNING: Removing unreachable block (ram,0x0050788c) */

void MakePacket__8CmbBreakFv(int param_1)

{
  bool bVar1;
  undefined4 *puVar2;
  undefined1 auVar3 [16];
  undefined1 auVar4 [16];
  undefined1 auVar5 [16];
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  undefined1 auVar8 [16];
  undefined1 auVar9 [16];
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  int iVar10;
  int iVar11;
  undefined4 uVar12;
  ulong uVar13;
  long lVar14;
  undefined8 extraout_v0_udw;
  undefined1 auVar15 [16];
  uint uVar16;
  ulong uVar17;
  float fVar18;
  float fVar19;
  undefined1 auVar20 [16];
  undefined1 auVar21 [16];
  undefined1 auStack_160 [16];
  undefined1 auStack_150 [16];
  undefined1 auStack_140 [16];
  undefined1 auStack_130 [16];
  float fStack_120;
  float fStack_11c;
  undefined4 uStack_118;
  undefined4 uStack_114;
  float fStack_110;
  float fStack_10c;
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
  float fStack_c0;
  float fStack_bc;
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
  float fStack_80;
  float fStack_7c;
  undefined4 uStack_78;
  undefined4 uStack_74;
  float fStack_70;
  float fStack_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  float fStack_50;
  float fStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  float fStack_40;
  float fStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  float fStack_30;
  float fStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  float fStack_20;
  float fStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  float fStack_10;
  float fStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  fVar18 = *(float *)(param_1 + 0x48) * 128.0;
  if (2.1474836e+09 <= fVar18) {
    fVar18 = fVar18 - 2.1474836e+09;
  }
  uVar17 = (long)(int)fVar18 & 0xff;
  if (*(float *)(param_1 + 0x40) < 0.2) {
    uStack_60 = 0x43800000;
    uStack_5c = 0x43600000;
    uStack_58 = 0;
    uStack_54 = 0x3f800000;
    fStack_10 = 256.0;
    fStack_c = 224.0;
    fVar18 = ((0.2 - *(float *)(param_1 + 0x40)) / 0.25) * 7.0 + 1.0;
  }
  else if (*(float *)(param_1 + 0x40) < 0.3) {
    iVar10 = rand();
    iVar11 = rand();
    fStack_70 = (((float)iVar10 / 2.1474836e+09) * 16.0 - 8.0) + 256.0;
    fStack_6c = (((float)iVar11 / 2.1474836e+09) * 16.0 - 8.0) + 224.0;
    uStack_68 = 0;
    uStack_64 = 0x3f800000;
    fVar18 = 1.0;
    fStack_10 = fStack_70;
    fStack_c = fStack_6c;
  }
  else if (*(float *)(param_1 + 0x40) < 0.5) {
    iVar10 = rand();
    iVar11 = rand();
    fStack_80 = (((float)iVar10 / 2.1474836e+09) * 16.0 - 8.0) *
                ((0.2 - (*(float *)(param_1 + 0x40) - 0.3)) / 0.2) + 256.0;
    fStack_7c = (((float)iVar11 / 2.1474836e+09) * 16.0 - 8.0) *
                ((0.2 - (*(float *)(param_1 + 0x40) - 0.3)) / 0.2) + 224.0;
    uStack_78 = 0;
    uStack_74 = 0x3f800000;
    fVar18 = 1.0;
    fStack_10 = fStack_80;
    fStack_c = fStack_7c;
  }
  else if (*(float *)(param_1 + 0x40) < 1.2) {
    uStack_90 = 0x43800000;
    uStack_8c = 0x43600000;
    uStack_88 = 0;
    uStack_84 = 0x3f800000;
    fStack_10 = 256.0;
    fStack_c = 224.0;
    fVar18 = 1.0;
  }
  else {
    uStack_a0 = 0x43800000;
    uStack_9c = 0x43600000;
    uStack_98 = 0;
    uStack_94 = 0x3f800000;
    fStack_10 = 256.0;
    fStack_c = 224.0;
    fVar18 = 1.0;
    fVar19 = (float)(int)uVar17 * ((1.4 - *(float *)(param_1 + 0x40)) / 0.2);
    if (2.1474836e+09 <= fVar19) {
      fVar19 = fVar19 - 2.1474836e+09;
    }
    uVar17 = (long)(int)fVar19 & 0xff;
  }
  uStack_4 = 0x3f800000;
  uStack_8 = 0;
  fStack_c0 = fVar18 * -127.5;
  fStack_bc = fVar18 * -23.0;
  uStack_b8 = 0;
  uStack_b4 = 0x3f800000;
  auVar6._4_4_ = fStack_c;
  auVar6._0_4_ = fStack_10;
  auVar6._8_4_ = 0;
  auVar6._12_4_ = 0x3f800000;
  auVar20 = _lqc2(auVar6);
  auVar5._4_4_ = fStack_bc;
  auVar5._0_4_ = fStack_c0;
  auVar5._8_4_ = 0;
  auVar5._12_4_ = 0x3f800000;
  auVar21 = _lqc2(auVar5);
  auVar20 = _vadd(auVar20,auVar21);
  auStack_130 = _sqc2(auVar20);
  __ct__7FVectorFRC7FVector(&fStack_b0,auStack_130);
  fStack_50 = fStack_b0;
  fStack_4c = fStack_ac;
  uStack_48 = uStack_a8;
  uStack_44 = uStack_a4;
  fStack_e0 = fVar18 * -127.5;
  fStack_dc = fVar18 * 23.0;
  uStack_d8 = 0;
  uStack_d4 = 0x3f800000;
  auVar7._4_4_ = fStack_c;
  auVar7._0_4_ = fStack_10;
  auVar7._8_4_ = uStack_8;
  auVar7._12_4_ = uStack_4;
  auVar20 = _lqc2(auVar7);
  auVar4._4_4_ = fStack_dc;
  auVar4._0_4_ = fStack_e0;
  auVar4._8_4_ = 0;
  auVar4._12_4_ = 0x3f800000;
  auVar21 = _lqc2(auVar4);
  auVar20 = _vadd(auVar20,auVar21);
  auStack_140 = _sqc2(auVar20);
  __ct__7FVectorFRC7FVector(&fStack_d0,auStack_140);
  fStack_40 = fStack_d0;
  fStack_3c = fStack_cc;
  uStack_38 = uStack_c8;
  uStack_34 = uStack_c4;
  fStack_100 = fVar18 * 127.5;
  fStack_fc = fVar18 * -23.0;
  uStack_f8 = 0;
  uStack_f4 = 0x3f800000;
  auVar8._4_4_ = fStack_c;
  auVar8._0_4_ = fStack_10;
  auVar8._8_4_ = uStack_8;
  auVar8._12_4_ = uStack_4;
  auVar20 = _lqc2(auVar8);
  auVar21._4_4_ = fStack_fc;
  auVar21._0_4_ = fStack_100;
  auVar21._8_4_ = 0;
  auVar21._12_4_ = 0x3f800000;
  auVar21 = _lqc2(auVar21);
  auVar20 = _vadd(auVar20,auVar21);
  auStack_150 = _sqc2(auVar20);
  __ct__7FVectorFRC7FVector(&fStack_f0,auStack_150);
  fStack_30 = fStack_f0;
  fStack_2c = fStack_ec;
  uStack_28 = uStack_e8;
  uStack_24 = uStack_e4;
  fStack_120 = fVar18 * 127.5;
  fStack_11c = fVar18 * 23.0;
  uStack_118 = 0;
  uStack_114 = 0x3f800000;
  auVar9._4_4_ = fStack_c;
  auVar9._0_4_ = fStack_10;
  auVar9._8_4_ = uStack_8;
  auVar9._12_4_ = uStack_4;
  auVar21 = _lqc2(auVar9);
  auVar20._4_4_ = fStack_11c;
  auVar20._0_4_ = fStack_120;
  auVar20._8_4_ = 0;
  auVar20._12_4_ = 0x3f800000;
  auVar20 = _lqc2(auVar20);
  auVar20 = _vadd(auVar21,auVar20);
  auStack_160 = _sqc2(auVar20);
  __ct__7FVectorFRC7FVector(&fStack_110,auStack_160);
  fStack_20 = fStack_110;
  fStack_1c = fStack_10c;
  uStack_18 = uStack_108;
  uStack_14 = uStack_104;
  bVar1 = (*(byte *)(param_1 + 0x38) & 1) == 0;
  uVar16 = (uint)bVar1;
  if (*(int *)(param_1 + uVar16 * 4 + 0x18) == 0) {
    uVar12 = __nwa__FUi(0x100);
    *(undefined4 *)(param_1 + uVar16 * 4 + 0x18) = uVar12;
    puVar2 = *(undefined4 **)(param_1 + uVar16 * 4 + 0x18);
    *puVar2 = 0x50000000;
    puVar2[1] = *(undefined4 *)
                 (*(int *)(iGpffff86b4 + 0x424c) +
                  (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x424c) + 10) * 4 + 0xc);
    puVar2[2] = 0;
    puVar2[3] = 0;
    puVar2[4] = 0x6000000e;
    puVar2[5] = 0;
    puVar2[6] = 0;
    puVar2[7] = 0x5000000e;
    *(undefined8 *)(puVar2 + 8) = 0x7000000000000001;
    *(undefined8 *)(puVar2 + 10) = 0xe6ee8ee;
    *(undefined8 *)(puVar2 + 0xc) = 1;
    *(undefined8 *)(puVar2 + 0xe) = 0x3f;
    *(undefined8 *)(puVar2 + 0x10) = 0x60;
    *(undefined8 *)(puVar2 + 0x12) = 0x14;
    *(undefined8 *)(puVar2 + 0x14) = 5;
    *(undefined8 *)(puVar2 + 0x16) = 0;
    *(undefined8 *)(puVar2 + 0x18) = 0x3001;
    *(undefined8 *)(puVar2 + 0x1a) = 0x47;
    uVar13 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x424c),1);
    *(ulong *)(puVar2 + 0x1c) = uVar13 & 0xfffffffc0fffff | 0x2000000001300000;
    *(undefined8 *)(puVar2 + 0x1e) = 0x16;
    *(ulong *)(puVar2 + 0x20) = uVar13 & 0xffffffffffffff | (long)*(int *)(param_1 + 0x44) << 0x38;
    *(undefined8 *)(puVar2 + 0x22) = 0;
    *(undefined8 *)(puVar2 + 0x24) = 0x44;
    *(undefined8 *)(puVar2 + 0x26) = 0x42;
    auVar15._8_8_ = extraout_v0_udw;
    auVar15._0_8_ = 0xa400000000008001;
    auVar3._4_4_ = in_zero_hi;
    auVar3._0_4_ = in_zero_lo;
    auVar3._8_4_ = in_zero_udw;
    auVar3._12_4_ = in_register_0000000c;
    auVar20 = _pcpyld(auVar3,auVar15);
    *(long *)(puVar2 + 0x28) = auVar20._0_8_;
    *(undefined8 *)(puVar2 + 0x2a) = 0x4343c3c310;
    *(undefined8 *)(puVar2 + 0x2c) = 0x154;
    *(undefined8 *)(puVar2 + 0x30) = 0;
    *(undefined8 *)(puVar2 + 0x34) = 0x2e00000;
    *(undefined8 *)(puVar2 + 0x38) = 0xff0;
    *(undefined8 *)(puVar2 + 0x3c) = 0x2e00ff0;
  }
  iVar10 = *(int *)(param_1 + uVar16 * 4 + 0x18);
  *(ulong *)(iVar10 + 0xb8) = uVar17 << 0x18 | 0x808080;
  uVar17 = __fixunssfdi((fStack_50 + 1792.0) * 16.0);
  lVar14 = __fixunssfdi((fStack_4c + 1824.0) * 16.0);
  *(ulong *)(iVar10 + 200) = uVar17 | lVar14 << 0x10;
  uVar17 = __fixunssfdi((fStack_40 + 1792.0) * 16.0);
  lVar14 = __fixunssfdi((fStack_3c + 1824.0) * 16.0);
  *(ulong *)(iVar10 + 0xd8) = uVar17 | lVar14 << 0x10;
  uVar17 = __fixunssfdi((fStack_30 + 1792.0) * 16.0);
  lVar14 = __fixunssfdi((fStack_2c + 1824.0) * 16.0);
  *(ulong *)(iVar10 + 0xe8) = uVar17 | lVar14 << 0x10;
  uVar17 = __fixunssfdi((fStack_20 + 1792.0) * 16.0);
  lVar14 = __fixunssfdi((fStack_1c + 1824.0) * 16.0);
  *(ulong *)(iVar10 + 0xf8) = uVar17 | lVar14 << 0x10;
  *(byte *)(param_1 + 0x38) = *(byte *)(param_1 + 0x38) & 0xfe | bVar1;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b230  getPacket__8CmbBreakFv
 * C++: CmbBreak::getPacket()
 * size: 0x44 bytes
 * --------------------------------------------------------------------------- */
undefined4 getPacket__8CmbBreakFv(int param_1)

{
  MakePacket__8CmbBreakFv(param_1);
  return *(undefined4 *)(param_1 + (*(byte *)(param_1 + 0x38) & 1) * 4 + 0x18);
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b500  @24@getPacket__8CmbBreakFv
 * C++: @24@getPacket__8CmbBreakFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
undefined4 _24_getPacket__8CmbBreakFv(int param_1)

{
  MakePacket__8CmbBreakFv(param_1 + -0x18);
  return *(undefined4 *)(param_1 + -0x18 + (*(byte *)(param_1 + 0x20) & 1) * 4 + 0x18);
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b510  @24@__dt__8CmbBreakFv
 * C++: @24@__dt__8CmbBreakFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int * _24___dt__8CmbBreakFv(int *param_1,short param_2)

{
  int *piVar1;
  
  piVar1 = param_1 + -6;
  if (piVar1 != (int *)0x0) {
    param_1[-1] = 0x40a350;
    param_1[4] = 0x40a360;
    param_1[7] = 0x40a370;
    if (*param_1 != 0) {
      __dla__FPv(*param_1);
    }
    if (param_1[1] != 0) {
      __dla__FPv(param_1[1]);
    }
    uGpffff86d0 = 0;
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
 * JP: 0x0054b520  @44@__dt__8CmbBreakFv
 * C++: @44@__dt__8CmbBreakFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int _44___dt__8CmbBreakFv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x2c;
  if (iVar1 != 0) {
    *(undefined4 *)(param_1 + -0x18) = 0x40a350;
    *(undefined4 *)(param_1 + -4) = 0x40a360;
    *(undefined4 *)(param_1 + 8) = 0x40a370;
    if (*(int *)(param_1 + -0x14) != 0) {
      __dla__FPv(*(undefined4 *)(param_1 + -0x14));
    }
    if (*(int *)(param_1 + -0x10) != 0) {
      __dla__FPv(*(undefined4 *)(param_1 + -0x10));
    }
    uGpffff86d0 = 0;
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

