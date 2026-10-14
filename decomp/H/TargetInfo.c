/* decomp/H/TargetInfo.c — cleaned Ghidra output (SH2JP_BATTLE.BIN, JP Furokuban, base 0x00430a00).
 * 8 function(s). Types: see types.h. Names/gp globals resolved from symbols/SLPM_602.19.syms. */
#include "types.h"

/* ---------------------------------------------------------------------------
 * JP: 0x00501fd0  __ct__10TargetInfoFiiiss
 * C++: TargetInfo::__ct(int, int, int, short, short)
 * size: 0x140 bytes
 * --------------------------------------------------------------------------- */
int __ct__10TargetInfoFiiiss
              (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
              undefined2 param_5,undefined2 param_6)

{
  int iVar1;
  
  __ct__6BtlEffFii(param_1,param_2,param_3);
  *(undefined4 *)(param_1 + 0x14) = 0x40a390;
  *(undefined4 *)(param_1 + 0x28) = 0x40a3a0;
  *(undefined4 *)(param_1 + 0x34) = 0x40a3b0;
  *(undefined4 *)(param_1 + 0x44) = param_2;
  *(undefined4 *)(param_1 + 0x48) = param_3;
  *(undefined4 *)(param_1 + 0x4c) = 0x11;
  *(undefined4 *)(param_1 + 0x40) = 0;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  *(undefined4 *)(param_1 + 0x18) = 0;
  *(undefined4 *)(param_1 + 0x54) = 0;
  *(undefined4 *)(param_1 + 0x5c) = param_4;
  *(undefined2 *)(param_1 + 0x60) = param_5;
  *(undefined2 *)(param_1 + 0x62) = param_6;
  for (iVar1 = 0; iVar1 < 9; iVar1 = iVar1 + 1) {
    *(undefined4 *)(param_1 + iVar1 * 4 + 100) = 0;
    *(undefined4 *)(param_1 + iVar1 * 4 + 0x88) = 0;
  }
  BtlEffEntry__7CBattleFiP6BtlEff(uGpffff86b4,0xffffffffffffffff,param_1);
  return param_1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00502110  __dt__10TargetInfoFv
 * C++: TargetInfo::__dt()
 * size: 0x154 bytes
 * --------------------------------------------------------------------------- */
int __dt__10TargetInfoFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x14) = 0x40a390;
    *(undefined4 *)(param_1 + 0x28) = 0x40a3a0;
    *(undefined4 *)(param_1 + 0x34) = 0x40a3b0;
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
 * JP: 0x00502270  Destruct__10TargetInfoFv
 * C++: TargetInfo::Destruct()
 * size: 0x48 bytes
 * --------------------------------------------------------------------------- */
void Destruct__10TargetInfoFv(int param_1)

{
  BtlEffRelease__7CBattleFiP6BtlEff(uGpffff86b4,0xffffffffffffffff,param_1);
  (**(code **)(*(int *)(param_1 + 0x34) + 0xc))();
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005022c0  Polling__10TargetInfoFv
 * C++: TargetInfo::Polling()
 * size: 0x210 bytes
 * --------------------------------------------------------------------------- */
undefined8 Polling__10TargetInfoFv(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  float fStack_20;
  uint uStack_1c;
  int iStack_18;
  float fStack_14;
  int iStack_10;
  
  fStack_14 = *(float *)(iGpffff86b4 + 0x38);
  if ((*(byte *)(iGpffff86b4 + 0x24) & 1) != 0) {
    fStack_14 = 0.0;
  }
  iStack_18 = 0;
  uStack_1c = 0;
  uVar4 = 0;
  iStack_10 = param_1;
  GetIconList__7CBattleFiPiPi(iGpffff86b4,*(undefined4 *)(param_1 + 0x48),&iStack_18,&uStack_1c);
  for (iVar3 = 0; iVar3 < iStack_18; iVar3 = iVar3 + 1) {
    for (; (uStack_1c & 1 << (uVar4 & 0x1f)) == 0; uVar4 = uVar4 + 1) {
    }
    iVar2 = *(int *)(uVar4 * 4 + 0x650d80);
    fStack_20 = *(float *)(iVar2 + *(int *)(iStack_10 + iVar3 * 4 + 0x88) * 8 + 4);
    if (fStack_20 != 0.0) {
      iVar1 = iStack_10 + iVar3 * 4;
      *(float *)(iVar1 + 100) = *(float *)(iVar1 + 100) + fStack_14;
      if (fStack_20 < 0.0) {
        fStack_20 = fStack_20 * -1.0;
      }
      if (fStack_20 <= *(float *)(iStack_10 + iVar3 * 4 + 100)) {
        iVar1 = iStack_10 + iVar3 * 4;
        *(float *)(iVar1 + 100) = *(float *)(iVar1 + 100) - fStack_20;
        if (0.0 < *(float *)(iVar2 + *(int *)(iStack_10 + iVar3 * 4 + 0x88) * 8 + 4)) {
          iVar2 = iStack_10 + iVar3 * 4;
          *(int *)(iVar2 + 0x88) = *(int *)(iVar2 + 0x88) + 1;
        }
        else {
          *(undefined4 *)(iStack_10 + iVar3 * 4 + 0x88) = 0;
        }
      }
    }
    uVar4 = uVar4 + 1;
  }
  return 0;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005024d0  MakePacket__10TargetInfoFv
 * C++: TargetInfo::MakePacket()
 * size: 0x4a34 bytes
 * --------------------------------------------------------------------------- */
/* WARNING: Removing unreachable block (ram,0x00504e10) */
/* WARNING: Removing unreachable block (ram,0x00502554) */
/* WARNING: Removing unreachable block (ram,0x00505640) */
/* WARNING: Removing unreachable block (ram,0x005055a0) */

void MakePacket__10TargetInfoFv(int param_1)

{
  bool bVar1;
  ushort uVar2;
  undefined4 *puVar3;
  undefined1 auVar4 [16];
  int iVar5;
  undefined1 in_zero_qw [16];
  undefined4 uVar6;
  uint uVar7;
  undefined8 uVar8;
  ulong uVar9;
  long lVar10;
  ulong uVar11;
  int iVar12;
  undefined1 auVar13 [16];
  ushort uVar14;
  undefined8 in_a2_udw;
  short sVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  undefined8 in_t1_udw;
  short sVar19;
  int iVar20;
  uint uStack_48;
  uint uStack_44;
  int iStack_3c;
  uint uStack_38;
  int iStack_34;
  int iStack_30;
  int iStack_2c;
  int iStack_28;
  float fStack_24;
  int iStack_20;
  uint uStack_1c;
  int iStack_18;
  short sStack_14;
  short sStack_12;
  int iStack_10;
  
  iStack_2c = 0x832;
  iStack_30 = 0x75c;
  iVar20 = (int)((float)*(ushort *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x140) * 0.8 +
                 0.5 + 37.0);
  if (iVar20 < 0x68) {
    iVar20 = 0x68;
  }
  iVar16 = 0x32;
  if (((*(char *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0xb8) == '\x0e') ||
      (*(char *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0xb8) == '\x0f')) ||
     (*(char *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0xb8) == '\x10')) {
    iVar16 = 0x49;
  }
  iStack_34 = 0;
  uStack_38 = 0;
  iStack_3c = 0;
  iStack_10 = param_1;
  GetIconList__7CBattleFiPiPi
            (iGpffff86b4,*(undefined4 *)(param_1 + 0x48),(short)&stack0x00000000 + -0x34,&uStack_38)
  ;
  if (iStack_34 != 0) {
    iStack_3c = (iVar20 + -0x11) / 0x12;
    for (iVar12 = iStack_34; iStack_3c < iVar12; iVar12 = iVar12 - iStack_3c) {
      iVar16 = iVar16 + 0x16;
    }
    if (iVar12 != 0) {
      iVar16 = iVar16 + 0x16;
    }
  }
  if (iVar16 < 0x48) {
    iVar16 = 0x48;
  }
  bVar1 = (*(byte *)(iStack_10 + 0x40) & 1) == 0;
  uStack_44 = (uint)bVar1;
  if (*(int *)(iStack_10 + uStack_44 * 4 + 0x18) == 0) {
    uVar6 = __nwa__FUi(0x990);
    *(undefined4 *)(iStack_10 + uStack_44 * 4 + 0x18) = uVar6;
    iVar12 = *(int *)(iStack_10 + uStack_44 * 4 + 0x18);
    *(undefined4 *)(iVar12 + 0x10) = 0x10000024;
    *(undefined4 *)(iVar12 + 0x14) = 0;
    *(undefined4 *)(iVar12 + 0x18) = 0;
    *(undefined4 *)(iVar12 + 0x1c) = 0x50000024;
    *(undefined8 *)(iVar12 + 0x20) = 0x6000000000000001;
    *(undefined8 *)(iVar12 + 0x28) = 0x6ee8ee;
    *(undefined8 *)(iVar12 + 0x30) = 1;
    *(undefined8 *)(iVar12 + 0x38) = 0x3f;
    *(undefined8 *)(iVar12 + 0x40) = 0;
    *(undefined8 *)(iVar12 + 0x48) = 0x14;
    *(undefined8 *)(iVar12 + 0x50) = 5;
    *(undefined8 *)(iVar12 + 0x58) = 0;
    *(undefined8 *)(iVar12 + 0x60) = 0x3001;
    *(undefined8 *)(iVar12 + 0x68) = 0x47;
    *(undefined8 *)(iVar12 + 0x70) = 0x44;
    *(undefined8 *)(iVar12 + 0x78) = 0x42;
    uVar8 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x4244),1);
    *(undefined8 *)(iVar12 + 0x80) = uVar8;
    *(undefined8 *)(iVar12 + 0x88) = 0;
    auVar13._8_8_ = in_a2_udw;
    auVar13._0_8_ = 0xa400000000000001;
    auVar13 = _pcpyld(in_zero_qw,auVar13);
    *(long *)(iVar12 + 0x90) = auVar13._0_8_;
    *(undefined8 *)(iVar12 + 0x98) = 0x4141c1c1f0;
    *(undefined8 *)(iVar12 + 0xa0) = 0x4c;
    *(undefined8 *)(iVar12 + 0xa8) = 0;
    *(undefined8 *)(iVar12 + 0xb0) = 0x4c4e4141;
    *(undefined8 *)(iVar12 + 0xc0) = 0x4c0a080a;
    *(undefined8 *)(iVar12 + 0xd0) = 0x4c4e4141;
    *(undefined8 *)(iVar12 + 0xe0) = 0x4c0a080a;
    *(undefined8 *)(iVar12 + 0xf0) = 0x2400000000000001;
    *(undefined8 *)(iVar12 + 0xf8) = 0x10;
    *(undefined8 *)(iVar12 + 0x100) = 0x156;
    *(undefined8 *)(iVar12 + 0x108) = 0x80808080;
    *(undefined8 *)(iVar12 + 0x110) = 0x440000000000800a;
    *(undefined8 *)(iVar12 + 0x118) = 0x43c3;
    *(undefined8 *)(iVar12 + 0x120) = 0x4600020;
    *(undefined8 *)(iVar12 + 0x130) = 0x4d00260;
    *(undefined8 *)(iVar12 + 0x140) = 0x4600020;
    *(undefined8 *)(iVar12 + 0x150) = 0x4d00260;
    *(undefined8 *)(iVar12 + 0x160) = 0x4f00000;
    *(undefined8 *)(iVar12 + 0x170) = 0x65000e0;
    *(undefined8 *)(iVar12 + 0x180) = 0x4f00000;
    *(undefined8 *)(iVar12 + 400) = 0x65000e0;
    *(undefined8 *)(iVar12 + 0x1a0) = 0x1d00000;
    *(undefined8 *)(iVar12 + 0x1b0) = 0x3800300;
    *(undefined8 *)(iVar12 + 0x1c0) = 0x1d00000;
    *(undefined8 *)(iVar12 + 0x1d0) = 0x3800300;
    *(undefined8 *)(iVar12 + 0x1e0) = 0x3800000;
    *(undefined8 *)(iVar12 + 0x1f0) = 0x46001a0;
    *(undefined8 *)(iVar12 + 0x200) = 0x3800000;
    *(undefined8 *)(iVar12 + 0x210) = 0x46001a0;
    *(undefined8 *)(iVar12 + 0x220) = 0x1d00300;
    *(undefined8 *)(iVar12 + 0x230) = 0x5c005a0;
    *(undefined8 *)(iVar12 + 0x240) = 0x1d00300;
    *(undefined8 *)(iVar12 + 0x250) = 0x5c005a0;
    *(undefined4 *)(iVar12 + 0x260) = 0x50000000;
    *(undefined4 *)(iVar12 + 0x264) =
         *(undefined4 *)
          (*(int *)(iGpffff86b4 + 0x4264) +
           (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x4264) + 10) * 4 + 0xc);
    *(undefined4 *)(iVar12 + 0x268) = 0;
    *(undefined4 *)(iVar12 + 0x26c) = 0;
    *(undefined4 *)(iVar12 + 0x270) = 0x10000008;
    *(undefined4 *)(iVar12 + 0x274) = 0;
    *(undefined4 *)(iVar12 + 0x278) = 0;
    *(undefined4 *)(iVar12 + 0x27c) = 0x50000008;
    *(undefined8 *)(iVar12 + 0x280) = 0x3000000000000001;
    *(undefined8 *)(iVar12 + 0x288) = 0x6ee;
    *(undefined8 *)(iVar12 + 0x290) = 1;
    *(undefined8 *)(iVar12 + 0x298) = 0x3f;
    *(undefined8 *)(iVar12 + 0x2a0) = 0x60;
    *(undefined8 *)(iVar12 + 0x2a8) = 0x14;
    uVar8 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x4264),1);
    *(undefined8 *)(iVar12 + 0x2b0) = uVar8;
    *(undefined8 *)(iVar12 + 0x2b8) = 0;
    *(undefined8 *)(iVar12 + 0x2c0) = 0x6400000000008001;
    *(undefined8 *)(iVar12 + 0x2c8) = 0x43c310;
    *(undefined8 *)(iVar12 + 0x2d0) = 0x156;
    *(undefined8 *)(iVar12 + 0x2d8) = 0x80808080;
    *(undefined8 *)(iVar12 + 0x2e0) = 0;
    *(undefined8 *)(iVar12 + 0x2f0) = 0x3200250;
    *(undefined4 *)(iVar12 + 0x300) = 0x50000000;
    *(undefined4 *)(iVar12 + 0x308) = 0;
    *(undefined4 *)(iVar12 + 0x30c) = 0;
    *(undefined4 *)(iVar12 + 0x310) = 0x10000007;
    *(undefined4 *)(iVar12 + 0x314) = 0;
    *(undefined4 *)(iVar12 + 0x318) = 0;
    *(undefined4 *)(iVar12 + 0x31c) = 0x50000007;
    *(undefined8 *)(iVar12 + 800) = 0x2000000000000001;
    *(undefined8 *)(iVar12 + 0x328) = 0x6e;
    *(undefined8 *)(iVar12 + 0x330) = 1;
    *(undefined8 *)(iVar12 + 0x338) = 0x3f;
    *(undefined8 *)(iVar12 + 0x348) = 0;
    *(undefined8 *)(iVar12 + 0x350) = 0x6400000000008001;
    *(undefined8 *)(iVar12 + 0x358) = 0x43c310;
    *(undefined8 *)(iVar12 + 0x360) = 0x156;
    *(undefined8 *)(iVar12 + 0x368) = 0x80808080;
    *(undefined4 *)(iVar12 + 0x390) = 0x50000000;
    *(undefined4 *)(iVar12 + 0x394) =
         *(undefined4 *)
          (*(int *)(iGpffff86b4 + 0x4230) +
           (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x4230) + 10) * 4 + 0xc);
    *(undefined4 *)(iVar12 + 0x398) = 0;
    *(undefined4 *)(iVar12 + 0x39c) = 0;
    *(undefined4 *)(iVar12 + 0x3a0) = 0x10000014;
    *(undefined4 *)(iVar12 + 0x3a4) = 0;
    *(undefined4 *)(iVar12 + 0x3a8) = 0;
    *(undefined4 *)(iVar12 + 0x3ac) = 0x50000014;
    *(undefined8 *)(iVar12 + 0x3b0) = 0x2000000000000001;
    *(undefined8 *)(iVar12 + 0x3b8) = 0x6e;
    *(undefined8 *)(iVar12 + 0x3c0) = 1;
    *(undefined8 *)(iVar12 + 0x3c8) = 0x3f;
    uVar8 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x4230),1);
    *(undefined8 *)(iVar12 + 0x3d0) = uVar8;
    *(undefined8 *)(iVar12 + 0x3d8) = 0;
    *(undefined8 *)(iVar12 + 0x3e0) = 0x6400000000000001;
    *(undefined8 *)(iVar12 + 1000) = 0xc3c310;
    *(undefined8 *)(iVar12 + 0x3f0) = 0x154;
    *(undefined8 *)(iVar12 + 0x3f8) = 0x80808080;
    *(undefined8 *)(iVar12 + 0x400) = 0x800000;
    *(undefined8 *)(iVar12 + 0x410) = 0x1000000;
    *(undefined8 *)(iVar12 + 0x420) = 0x4400000000000003;
    *(undefined8 *)(iVar12 + 0x428) = 0x4343;
    *(undefined8 *)(iVar12 + 0x430) = 0x800030;
    *(undefined8 *)(iVar12 + 0x440) = 0x1000030;
    *(undefined8 *)(iVar12 + 0x450) = 0x800300;
    *(undefined8 *)(iVar12 + 0x460) = 0x1000300;
    *(undefined8 *)(iVar12 + 0x470) = 0x800330;
    *(undefined8 *)(iVar12 + 0x480) = 0x1000330;
    auVar4._8_8_ = in_t1_udw;
    auVar4._0_8_ = 0xa400000000008001;
    auVar13 = _pcpyld(in_zero_qw,auVar4);
    *(long *)(iVar12 + 0x490) = auVar13._0_8_;
    *(undefined8 *)(iVar12 + 0x498) = 0x4343c3c310;
    *(undefined8 *)(iVar12 + 0x4a0) = 0x154;
    *(undefined8 *)(iVar12 + 0x4a8) = 0x80808080;
    *(undefined8 *)(iVar12 + 0x4b0) = 0x20;
    *(undefined8 *)(iVar12 + 0x4c0) = 0x800020;
    *(undefined4 *)(iVar12 + 0x4f0) = 0x50000000;
    *(undefined4 *)(iVar12 + 0x4f4) =
         *(undefined4 *)
          (*(int *)(iGpffff86b4 + 0x4228) +
           (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x4228) + 10) * 4 + 0xc);
    *(undefined4 *)(iVar12 + 0x4f8) = 0;
    *(undefined4 *)(iVar12 + 0x4fc) = 0;
    *(undefined4 *)(iVar12 + 0x500) = 0x1000000b;
    *(undefined4 *)(iVar12 + 0x504) = 0;
    *(undefined4 *)(iVar12 + 0x508) = 0;
    *(undefined4 *)(iVar12 + 0x50c) = 0x5000000b;
    *(undefined8 *)(iVar12 + 0x510) = 0x3000000000000001;
    *(undefined8 *)(iVar12 + 0x518) = 0x6ee;
    *(undefined8 *)(iVar12 + 0x520) = 1;
    *(undefined8 *)(iVar12 + 0x528) = 0x3f;
    uVar9 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x4228),1);
    *(ulong *)(iVar12 + 0x530) = uVar9 & 0xfffffffc0fffff | 0x2000000001300000;
    *(undefined8 *)(iVar12 + 0x538) = 0x16;
    *(ulong *)(iVar12 + 0x540) = uVar9 & 0xffffffffffffff | 0x100000000000000;
    *(undefined8 *)(iVar12 + 0x548) = 0;
    *(undefined8 *)(iVar12 + 0x550) = 0x6400000000008002;
    *(undefined8 *)(iVar12 + 0x558) = 0x43c310;
    *(undefined8 *)(iVar12 + 0x560) = 0x156;
    *(undefined8 *)(iVar12 + 0x568) = 0x80000000;
    *(undefined8 *)(iVar12 + 0x590) = 0x156;
    *(undefined8 *)(iVar12 + 0x598) = 0x80808080;
    *(undefined4 *)(iVar12 + 0x5c0) = 0x50000000;
    *(undefined4 *)(iVar12 + 0x5c4) =
         *(undefined4 *)
          (*(int *)(iGpffff86b4 + 0x422c) +
           (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x422c) + 10) * 4 + 0xc);
    *(undefined4 *)(iVar12 + 0x5c8) = 0;
    *(undefined4 *)(iVar12 + 0x5cc) = 0;
    *(undefined4 *)(iVar12 + 0x5d0) = 0x10000014;
    *(undefined4 *)(iVar12 + 0x5d4) = 0;
    *(undefined4 *)(iVar12 + 0x5d8) = 0;
    *(undefined4 *)(iVar12 + 0x5dc) = 0x50000014;
    *(undefined8 *)(iVar12 + 0x5e0) = 0x2000000000000001;
    *(undefined8 *)(iVar12 + 0x5e8) = 0x6e;
    *(undefined8 *)(iVar12 + 0x5f0) = 1;
    *(undefined8 *)(iVar12 + 0x5f8) = 0x3f;
    uVar8 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x422c),1);
    *(undefined8 *)(iVar12 + 0x600) = uVar8;
    *(undefined8 *)(iVar12 + 0x608) = 0;
    *(undefined8 *)(iVar12 + 0x610) = 0x6400000000000001;
    *(undefined8 *)(iVar12 + 0x618) = 0x43c310;
    *(undefined8 *)(iVar12 + 0x620) = 0x156;
    *(undefined8 *)(iVar12 + 0x628) = 0x80808080;
    *(undefined8 *)(iVar12 + 0x630) = 0x100010;
    *(undefined8 *)(iVar12 + 0x640) = 0xb00130;
    *(undefined8 *)(iVar12 + 0x650) = 0x2400000000000001;
    *(undefined8 *)(iVar12 + 0x658) = 0x10;
    *(undefined8 *)(iVar12 + 0x660) = 0x156;
    *(undefined8 *)(iVar12 + 0x670) = 0x4400000000008005;
    *(undefined8 *)(iVar12 + 0x678) = 0x43c3;
    *(undefined4 *)(iVar12 + 0x720) = 0x50000000;
    *(undefined4 *)(iVar12 + 0x724) =
         *(undefined4 *)
          (*(int *)(iGpffff86b4 + 0x4240) +
           (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x4240) + 10) * 4 + 0xc);
    *(undefined4 *)(iVar12 + 0x728) = 0;
    *(undefined4 *)(iVar12 + 0x72c) = 0;
    *(undefined4 *)(iVar12 + 0x730) = 0x10000007;
    *(undefined4 *)(iVar12 + 0x734) = 0;
    *(undefined4 *)(iVar12 + 0x738) = 0;
    *(undefined4 *)(iVar12 + 0x73c) = 0x50000007;
    *(undefined8 *)(iVar12 + 0x740) = 0x2000000000000001;
    *(undefined8 *)(iVar12 + 0x748) = 0x6e;
    *(undefined8 *)(iVar12 + 0x750) = 1;
    *(undefined8 *)(iVar12 + 0x758) = 0x3f;
    uVar8 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x4240),1);
    *(undefined8 *)(iVar12 + 0x760) = uVar8;
    *(undefined8 *)(iVar12 + 0x768) = 0;
    *(undefined8 *)(iVar12 + 0x770) = 0x6400000000008001;
    *(undefined8 *)(iVar12 + 0x778) = 0x43c310;
    *(undefined8 *)(iVar12 + 0x780) = 0x156;
    *(undefined8 *)(iVar12 + 0x788) = 0x80808080;
    *(undefined8 *)(iVar12 + 0x790) = 0;
    *(undefined8 *)(iVar12 + 0x7a0) = 0x1700490;
    *(undefined4 *)(iVar12 + 0x7b0) = 0x50000000;
    *(undefined4 *)(iVar12 + 0x7b4) =
         *(undefined4 *)
          (*(int *)(iGpffff86b4 + 0x430c) +
           (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x430c) + 10) * 4 + 0xc);
    *(undefined4 *)(iVar12 + 0x7b8) = 0;
    *(undefined4 *)(iVar12 + 0x7bc) = 0;
    *(undefined4 *)(iVar12 + 0x7c0) = 0x10000018;
    *(undefined4 *)(iVar12 + 0x7c4) = 0;
    *(undefined4 *)(iVar12 + 0x7c8) = 0;
    *(undefined4 *)(iVar12 + 0x7cc) = 0x50000018;
    *(undefined8 *)(iVar12 + 2000) = 0x2000000000000001;
    *(undefined8 *)(iVar12 + 0x7d8) = 0x6e;
    *(undefined8 *)(iVar12 + 0x7e0) = 1;
    *(undefined8 *)(iVar12 + 0x7e8) = 0x3f;
    uVar8 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x430c),1);
    *(undefined8 *)(iVar12 + 0x7f0) = uVar8;
    *(undefined8 *)(iVar12 + 0x7f8) = 0;
    *(undefined8 *)(iVar12 + 0x800) = 0x2400000000000001;
    *(undefined8 *)(iVar12 + 0x808) = 0x10;
    *(undefined8 *)(iVar12 + 0x810) = 0x156;
    *(undefined8 *)(iVar12 + 0x818) = 0x80808080;
    *(undefined8 *)(iVar12 + 0x820) = 0x4400000000008009;
    *(undefined8 *)(iVar12 + 0x828) = 0x43c3;
  }
  iVar5 = iStack_2c;
  iVar17 = iStack_30;
  puVar3 = *(undefined4 **)(iStack_10 + uStack_44 * 4 + 0x18);
  *puVar3 = 0x50000000;
  puVar3[1] = *(undefined4 *)
               (*(int *)(iGpffff86b4 + 0x4244) +
                (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x4244) + 10) * 4 + 0xc);
  puVar3[2] = 0;
  puVar3[3] = 0;
  iVar12 = (iStack_2c + -2) * 0x10;
  uVar9 = (long)iVar12 | (long)((iStack_30 + -2) * 0x10) << 0x10;
  *(ulong *)(puVar3 + 0x2e) =
       CONCAT44((int)(uVar9 >> 0x20),CONCAT22((short)(uVar9 >> 0x10),(short)iVar12));
  iVar12 = (iStack_30 + iVar16 + 2) * 0x10;
  *(ulong *)(puVar3 + 0x32) =
       (long)((iStack_2c + -2) * 0x10) |
       (ulong)CONCAT42((int)(short)((uint)iVar12 >> 0x10),(short)iVar12) << 0x10;
  iVar12 = (iStack_30 + -2) * 0x10;
  iVar18 = (iStack_2c + iVar20 + 0x10) * 0x10;
  uVar9 = (ulong)CONCAT42((int)(short)((uint)iVar12 >> 0x10),(short)iVar12) << 0x10 | (long)iVar18;
  *(ulong *)(puVar3 + 0x36) =
       CONCAT44((int)(uVar9 >> 0x20),CONCAT22((short)(uVar9 >> 0x10),(short)iVar18));
  iVar12 = (iStack_2c + iVar20 + 0x10) * 0x10;
  uVar9 = (long)iVar12 | (long)((iStack_30 + iVar16 + 2) * 0x10) << 0x10;
  *(ulong *)(puVar3 + 0x3a) =
       CONCAT44((int)(uVar9 >> 0x20),CONCAT22((short)(uVar9 >> 0x10),(short)iVar12));
  *(long *)(puVar3 + 0x4a) =
       (long)((iStack_2c + 0x18) * 0x10 + 3) | (long)((iStack_30 + -7) * 0x10) << 0x10;
  *(ulong *)(puVar3 + 0x4e) =
       (ulong)CONCAT42((int)(short)((uint)(iStack_30 << 4) >> 0x10),(short)(iStack_30 << 4)) << 0x10
       | (long)((iStack_2c + iVar20 + -0xb) * 0x10);
  iVar12 = (iStack_30 + iVar16 + 7) * 0x10;
  *(ulong *)(puVar3 + 0x52) =
       (long)((iStack_2c + 0x1a) * 0x10) |
       (ulong)CONCAT42((int)(short)((uint)iVar12 >> 0x10),(short)iVar12) << 0x10;
  iVar12 = (iStack_30 + iVar16) * 0x10;
  *(ulong *)(puVar3 + 0x56) =
       (long)((iStack_2c + iVar20 + -10) * 0x10) |
       (ulong)CONCAT42((int)(short)((uint)iVar12 >> 0x10),(short)iVar12) << 0x10;
  *(long *)(puVar3 + 0x5a) =
       (long)((iStack_2c + -0xe) * 0x10) | (long)((iStack_30 + 0x19) * 0x10) << 0x10;
  *(long *)(puVar3 + 0x5e) =
       (long)(iStack_2c << 4) | (long)((iStack_30 + iVar16 + -0x30) * 0x10) << 0x10;
  *(long *)(puVar3 + 0x62) =
       (long)((iStack_30 + 0x31) * 0x10) << 0x10 | (long)((iStack_2c + iVar20 + 0x1c) * 0x10);
  *(long *)(puVar3 + 0x66) =
       (long)((iStack_2c + iVar20 + 0xe) * 0x10) |
       (long)((iStack_30 + iVar16 + -0x18) * 0x10) << 0x10;
  iVar12 = (iStack_2c + -0x17) * 0x10;
  uVar9 = (long)iVar12 | (long)((iStack_30 + -0xe) * 0x10) << 0x10;
  *(ulong *)(puVar3 + 0x6a) =
       CONCAT44((int)(uVar9 >> 0x20),CONCAT22((short)(uVar9 >> 0x10),(short)iVar12));
  iVar12 = (iStack_2c + 0x19) * 0x10;
  uVar9 = (long)iVar12 | (long)((iStack_30 + 0xd) * 0x10) << 0x10;
  *(ulong *)(puVar3 + 0x6e) =
       CONCAT44((int)(uVar9 >> 0x20),CONCAT22((short)(uVar9 >> 0x10),(short)iVar12));
  iVar12 = (iStack_30 + iVar16 + 0xe) * 0x10;
  *(ulong *)(puVar3 + 0x72) =
       (long)((iStack_2c + iVar20 + 0x25) * 0x10) |
       (ulong)CONCAT42((int)(short)((uint)iVar12 >> 0x10),(short)iVar12) << 0x10;
  iVar12 = (iStack_2c + iVar20 + -0xb) * 0x10;
  uVar9 = (long)iVar12 | (long)((iStack_30 + iVar16 + -0xd) * 0x10) << 0x10;
  *(ulong *)(puVar3 + 0x76) =
       CONCAT44((int)(uVar9 >> 0x20),CONCAT22((short)(uVar9 >> 0x10),(short)iVar12));
  iVar12 = (iStack_2c + -0x17) * 0x10;
  uVar9 = (long)iVar12 | (long)((iStack_30 + 0xb) * 0x10) << 0x10;
  *(ulong *)(puVar3 + 0x7a) =
       CONCAT44((int)(uVar9 >> 0x20),CONCAT22((short)(uVar9 >> 0x10),(short)iVar12));
  iVar12 = (iStack_2c + 3) * 0x10;
  uVar9 = (long)iVar12 | (long)((iStack_30 + 0x19) * 0x10) << 0x10;
  *(ulong *)(puVar3 + 0x7e) =
       CONCAT44((int)(uVar9 >> 0x20),CONCAT22((short)(uVar9 >> 0x10),(short)iVar12));
  iVar12 = (iStack_30 + iVar16 + -0xb) * 0x10;
  *(ulong *)(puVar3 + 0x82) =
       (long)((iStack_2c + iVar20 + 0x25) * 0x10) |
       (ulong)CONCAT42((int)(short)((uint)iVar12 >> 0x10),(short)iVar12) << 0x10;
  iVar12 = (iStack_2c + iVar20 + 0xb) * 0x10;
  uVar9 = (long)iVar12 | (long)((iStack_30 + iVar16 + -0x19) * 0x10) << 0x10;
  *(ulong *)(puVar3 + 0x86) =
       CONCAT44((int)(uVar9 >> 0x20),CONCAT22((short)(uVar9 >> 0x10),(short)iVar12));
  iVar12 = (iStack_30 + iVar16 + -0x32) * 0x10;
  *(ulong *)(puVar3 + 0x8a) =
       (long)((iStack_2c + -0x10) * 0x10) |
       (ulong)CONCAT42((int)(short)((uint)iVar12 >> 0x10),(short)iVar12) << 0x10;
  *(long *)(puVar3 + 0x8e) =
       (long)((iStack_2c + 0x1a) * 0x10) | (long)((iStack_30 + iVar16 + 0xd) * 0x10) << 0x10;
  *(long *)(puVar3 + 0x92) =
       (long)((iStack_30 + 0x32) * 0x10) << 0x10 | (long)((iStack_2c + iVar20 + 0x1e) * 0x10);
  *(long *)(puVar3 + 0x96) =
       (long)((iStack_30 + -0xd) * 0x10) << 0x10 | (long)((iStack_2c + iVar20 + -0xd) * 0x10);
  lVar10 = __fixunssfdi((float)iStack_30 * 16.0);
  iVar16 = iStack_2c;
  iVar20 = iStack_30;
  *(long *)(puVar3 + 0xba) = lVar10 << 0x10 | (long)(iVar5 << 4);
  iVar12 = (iVar17 + 0x32) * 0x10;
  *(ulong *)(puVar3 + 0xbe) =
       (long)((iVar5 + 0x25) * 0x10) |
       (ulong)CONCAT42((int)(short)((uint)iVar12 >> 0x10),(short)iVar12) << 0x10;
  if ((*(byte *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0xb4) & 1) == 0) {
    if (*(short *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0x120) < 8) {
      puVar3[0xc1] = *(undefined4 *)
                      (*(int *)(iGpffff86b4 + 0x42b4) +
                       (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42b4) + 10) * 4 + 0xc);
      uVar8 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x42b4),1);
      *(undefined8 *)(puVar3 + 0xd0) = uVar8;
      if ((*(byte *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0xb1) & 1) == 0) {
        uVar9 = (ulong)*(short *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0x18c);
        if (uVar9 == 0x51) {
          uVar9 = 5;
        }
        if (uVar9 == 0x54) {
          uVar9 = 3;
        }
        if (uVar9 == 0x57) {
          uVar9 = 4;
        }
      }
      else {
        uVar9 = (ulong)*(ushort *)
                        (ourBtlSaveDat +
                         *(short *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0x120) * 0xc0
                        + 0x48);
      }
      if ((long)uVar9 < 6) {
        sVar19 = 0;
        sVar15 = (short)uVar9 * 0x2e;
      }
      else {
        sVar19 = 0x24;
        sVar15 = ((short)uVar9 + -6) * 0x2e;
      }
    }
    else if (*(short *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0x120) < 0xb) {
      puVar3[0xc1] = *(undefined4 *)
                      (*(int *)(iGpffff86b4 + 0x42b8) +
                       (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42b8) + 10) * 4 + 0xc);
      uVar8 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x42b8),1);
      *(undefined8 *)(puVar3 + 0xd0) = uVar8;
      sVar19 = 0;
      sVar15 = (*(short *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0x120) + -8) * 0x2e;
    }
    else {
      puVar3[0xc1] = *(undefined4 *)
                      (*(int *)(iGpffff86b4 + 0x42bc) +
                       (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42bc) + 10) * 4 + 0xc);
      uVar8 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x42bc),1);
      *(undefined8 *)(puVar3 + 0xd0) = uVar8;
      sVar19 = 0;
      sVar15 = 0;
    }
  }
  else {
    puVar3[0xc1] = *(undefined4 *)
                    (*(int *)(iGpffff86b4 + 0x42c0) +
                     (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42c0) + 10) * 4 + 0xc);
    uVar8 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x42c0),1);
    *(undefined8 *)(puVar3 + 0xd0) = uVar8;
    if ((long)((ulong)*(byte *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0xb0) << 0x3b) <
        0) {
      sVar19 = 0x48;
      sVar15 = 0;
    }
    else if (*(short *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0x120) < 4) {
      sVar19 = 0;
      sVar15 = *(short *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0x120) * 0x2e;
    }
    else if (*(short *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0x120) < 8) {
      sVar19 = 0x24;
      sVar15 = (*(short *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0x120) + -4) * 0x2e;
    }
    else {
      sVar19 = 0x48;
      sVar15 = (*(short *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0x120) + -8) * 0x2e;
    }
  }
  iVar12 = iStack_30;
  sStack_12 = 0x24;
  sStack_14 = 0x2e;
  *(long *)(puVar3 + 0xdc) = (long)((int)sVar19 << 4) | (long)((int)sVar15 << 4) << 0x10;
  iVar17 = (iVar20 + 1) * 0x10;
  *(ulong *)(puVar3 + 0xde) =
       (long)((iVar16 + 1) * 0x10) |
       (ulong)CONCAT42((int)(short)((uint)iVar17 >> 0x10),(short)iVar17) << 0x10;
  iVar17 = (sVar15 + 0x2e) * 0x10;
  *(ulong *)(puVar3 + 0xe0) =
       CONCAT44((int)(short)((uint)iVar17 >> 0x10),CONCAT22((short)iVar17,(sVar19 + 0x24) * 0x10));
  *(long *)(puVar3 + 0xe2) = (long)((iVar16 + 0x25) * 0x10) | (long)((iVar20 + 0x2f) * 0x10) << 0x10
  ;
  iVar20 = iStack_30 + 0x28;
  *(ulong *)(puVar3 + 0x102) =
       (long)((iStack_2c + 0x24) * 0x10) |
       (ulong)CONCAT42((int)(short)((uint)(iVar20 * 0x10) >> 0x10),(short)(iVar20 * 0x10)) << 0x10;
  *(long *)(puVar3 + 0x106) =
       (long)((iStack_2c + 0x24) * 0x10) | (long)((iStack_30 + 0x30) * 0x10) << 0x10;
  iVar16 = (iStack_2c + 0x27) * 0x10;
  uVar9 = (long)iVar16 | (long)(iVar20 * 0x10) << 0x10;
  *(ulong *)(puVar3 + 0x10e) =
       CONCAT44((int)(uVar9 >> 0x20),CONCAT22((short)(uVar9 >> 0x10),(short)iVar16));
  *(long *)(puVar3 + 0x112) =
       (long)((iStack_2c + 0x27) * 0x10) | (long)((iStack_30 + 0x30) * 0x10) << 0x10;
  *(long *)(puVar3 + 0x116) = (long)((iStack_2c + 0x65) * 0x10) | (long)(iVar20 * 0x10) << 0x10;
  *(long *)(puVar3 + 0x11a) =
       (long)((iStack_2c + 0x65) * 0x10) | (long)((iStack_30 + 0x30) * 0x10) << 0x10;
  iVar16 = (iStack_2c + 0x68) * 0x10;
  uVar9 = (long)iVar16 | (long)(iVar20 * 0x10) << 0x10;
  *(ulong *)(puVar3 + 0x11e) =
       CONCAT44((int)(uVar9 >> 0x20),CONCAT22((short)(uVar9 >> 0x10),(short)iVar16));
  *(long *)(puVar3 + 0x122) =
       (long)((iStack_2c + 0x68) * 0x10) | (long)((iStack_30 + 0x30) * 0x10) << 0x10;
  fStack_24 = ((float)(int)*(short *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0x124) *
              63.0) / (float)*(ushort *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0x122);
  if (fStack_24 < 0.0) {
    fStack_24 = 0.0;
  }
  iVar16 = iStack_2c + 0x26;
  if (fStack_24 == 0.0) {
    *(undefined8 *)(puVar3 + 0x12e) = 0x71006f00;
    *(undefined8 *)(puVar3 + 0x132) = 0x71006f00;
    *(undefined8 *)(puVar3 + 0x136) = 0x71006f00;
    *(undefined8 *)(puVar3 + 0x13a) = 0x71006f00;
  }
  else {
    *(long *)(puVar3 + 0x12e) = (long)(iVar16 * 0x10) | (long)(iVar20 * 0x10) << 0x10;
    uVar9 = (long)(iVar16 * 0x10) | (long)((iStack_30 + 0x30) * 0x10) << 0x10;
    *(ulong *)(puVar3 + 0x132) =
         CONCAT44((int)(uVar9 >> 0x20),CONCAT22((short)(uVar9 >> 0x10),(short)(iVar16 * 0x10)));
    uVar8 = __fixunssfdi(((fStack_24 * 46.0) / 63.0 + 2.0 + 1.0) * 16.0);
    *(undefined8 *)(puVar3 + 0x134) = uVar8;
    uVar9 = __fixunssfdi(((float)iVar16 + fStack_24 + 1.0) * 16.0);
    *(ulong *)(puVar3 + 0x136) =
         uVar9 | (ulong)CONCAT42((int)(short)((uint)(iVar20 * 0x10) >> 0x10),(short)(iVar20 * 0x10))
                 << 0x10;
    uVar9 = __fixunssfdi(((fStack_24 * 46.0) / 63.0 + 2.0 + 1.0) * 16.0);
    *(ulong *)(puVar3 + 0x138) = uVar9 | 0x800000;
    uVar9 = __fixunssfdi(((float)iVar16 + fStack_24 + 1.0) * 16.0);
    *(ulong *)(puVar3 + 0x13a) = uVar9 | (long)((iVar12 + 0x30) * 0x10) << 0x10;
  }
  iVar20 = iStack_2c + 0x25;
  iVar12 = iStack_30 + 3;
  sVar19 = *(short *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0x13c);
  sVar15 = *(short *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0x13e);
  sStack_12 = *(short *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0x140) + sVar19;
  sStack_14 = *(short *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0x142) + sVar15;
  *(long *)(puVar3 + 0x15c) = (long)((int)sVar19 << 4) | (long)((int)sVar15 << 4) << 0x10;
  *(long *)(puVar3 + 0x15e) =
       (long)((iStack_2c + 0x26) * 0x10) | (long)((iStack_30 + 4) * 0x10) << 0x10;
  *(ulong *)(puVar3 + 0x160) =
       (long)((int)sStack_12 << 4) |
       (ulong)CONCAT42((int)(short)((uint)((int)sStack_14 << 4) >> 0x10),
                       (short)((int)sStack_14 << 4)) << 0x10;
  uVar9 = __fixunssfdi(((float)iVar20 + (float)((int)sStack_12 + (int)sVar19) * 0.8 + 1.0) * 16.0
                         );
  *(ulong *)(puVar3 + 0x162) =
       uVar9 | (long)((iVar12 + ((int)sStack_14 - (int)sVar15) + 1) * 0x10) << 0x10;
  *(ulong *)(puVar3 + 0x168) =
       (long)((int)sVar19 << 4) |
       (ulong)CONCAT42((int)(short)((uint)((int)sVar15 << 4) >> 0x10),(short)((int)sVar15 << 4)) <<
       0x10;
  *(long *)(puVar3 + 0x16a) = (long)(iVar20 * 0x10) | (long)(iVar12 * 0x10) << 0x10;
  *(long *)(puVar3 + 0x16c) = (long)((int)sStack_12 << 4) | (long)((int)sStack_14 << 4) << 0x10;
  uVar9 = __fixunssfdi(((float)iVar20 + (float)((int)sStack_12 - (int)sVar19) * 0.8) * 16.0);
  iVar16 = iStack_30;
  iVar20 = (iVar12 + ((int)sStack_14 - (int)sVar15)) * 0x10;
  *(ulong *)(puVar3 + 0x16e) =
       uVar9 | (ulong)CONCAT42((int)(short)((uint)iVar20 >> 0x10),(short)iVar20) << 0x10;
  iVar20 = iStack_30 + 0x1b;
  iVar12 = (iStack_2c + 0x26) * 0x10;
  uVar9 = (long)iVar12 | (long)(iVar20 * 0x10) << 0x10;
  *(ulong *)(puVar3 + 0x18e) =
       CONCAT44((int)(uVar9 >> 0x20),CONCAT22((short)(uVar9 >> 0x10),(short)iVar12));
  *(long *)(puVar3 + 0x192) =
       (long)((iStack_2c + 0x38) * 0x10) | (long)((iStack_30 + 0x25) * 0x10) << 0x10;
  uStack_1c = (int)(uint)*(ushort *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0x122) >> 1;
  if ((uStack_1c < 2) && (2 < *(ushort *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0x122))
     ) {
    uStack_1c = 2;
  }
  iStack_20 = (int)(uint)*(ushort *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0x122) >> 2;
  if ((iStack_20 == 0) &&
     (1 < *(ushort *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0x122))) {
    iStack_20 = 1;
  }
  sVar19 = *(short *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0x124);
  if ((long)(int)uStack_1c < CONCAT44((int)(((long)sVar19 << 0x30) >> 0x3f),(int)sVar19)) {
    *(undefined8 *)(puVar3 + 0x19a) = 0x80808080;
  }
  else {
    sVar19 = *(short *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0x124);
    if ((long)iStack_20 < CONCAT44((int)(((long)sVar19 << 0x30) >> 0x3f),(int)sVar19)) {
      *(undefined8 *)(puVar3 + 0x19a) = 0x80008080;
    }
    else {
      *(undefined8 *)(puVar3 + 0x19a) = 0x80000080;
    }
  }
  iVar12 = iStack_2c + 0x3b;
  fStack_24 = 0.0;
  if (*(short *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0x124) < 10000) {
    if ((*(byte *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0xb4) & 1) != 0) {
      uVar2 = *(ushort *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0xba);
      uVar14 = uVar2 & 7;
      if (((int)(((long)(short)uVar2 << 0x30) >> 0x3f) < 0) && ((uVar2 & 7) != 0)) {
        uVar14 = uVar14 - 8;
      }
      if (((uint)*(byte *)(ourBtlSaveDat +
                           ((int)*(short *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0xba)
                           >> 3) + 0xdcf) & 1 << (uVar14 & 0x1f)) == 0) goto LAB_005058c8;
    }
    *(undefined8 *)(puVar3 + 0x1a2) = 0x71006f00;
    *(undefined8 *)(puVar3 + 0x1a6) = 0x71006f00;
  }
  else {
LAB_005058c8:
    sVar19 = (short)(((int)*(short *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0x124) /
                     10000) % 10);
    if ((*(byte *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0xb4) & 1) != 0) {
      uVar2 = *(ushort *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0xba);
      uVar14 = uVar2 & 7;
      if (((short)uVar2 < 0) && ((uVar2 & 7) != 0)) {
        uVar14 = uVar14 - 8;
      }
      if (((uint)*(byte *)(ourBtlSaveDat +
                           ((int)*(short *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0xba)
                           >> 3) + 0xdcf) & 1 << (uVar14 & 0x1f)) == 0) {
        sVar19 = 0xb;
      }
    }
    *(ulong *)(puVar3 + 0x1a0) = (long)((sVar19 * 10 + (int)sVar19 + 0x4d) * 0x10) | 0x100000;
    *(long *)(puVar3 + 0x1a2) = (long)(iVar12 * 0x10) | (long)(iVar20 * 0x10) << 0x10;
    *(ulong *)(puVar3 + 0x1a4) = (long)(((sVar19 + 1) * 0xb + 0x4d) * 0x10) | 0xe00000;
    uVar11 = __fixunssfdi((float)(iVar12 * 0x10) + 140.8);
    uVar9 = uVar11 | (long)((iVar16 + 0x28) * 0x10) << 0x10;
    *(ulong *)(puVar3 + 0x1a6) =
         CONCAT44((int)(uVar9 >> 0x20),CONCAT22((short)(uVar9 >> 0x10),(short)uVar11));
  }
  fStack_24 = fStack_24 + 140.8;
  if (*(short *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0x124) < 1000) {
    if ((*(byte *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0xb4) & 1) != 0) {
      uVar2 = *(ushort *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0xba);
      uVar14 = uVar2 & 7;
      if (((short)uVar2 < 0) && (uVar14 != 0)) {
        uVar14 = uVar14 - 8;
      }
      if (((uint)*(byte *)(ourBtlSaveDat +
                           ((int)*(short *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0xba)
                           >> 3) + 0xdcf) & 1 << (uVar14 & 0x1f)) == 0) goto LAB_00505cb0;
    }
    *(undefined8 *)(puVar3 + 0x1aa) = 0x71006f00;
    *(undefined8 *)(puVar3 + 0x1ae) = 0x71006f00;
  }
  else {
LAB_00505cb0:
    sVar19 = (short)(((int)*(short *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0x124) /
                     1000) % 10);
    if ((*(byte *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0xb4) & 1) != 0) {
      uVar2 = *(ushort *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0xba);
      uVar14 = uVar2 & 7;
      if (((short)uVar2 < 0) && (uVar14 != 0)) {
        uVar14 = uVar14 - 8;
      }
      if (((uint)*(byte *)(ourBtlSaveDat +
                           ((int)*(short *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0xba)
                           >> 3) + 0xdcf) & 1 << (uVar14 & 0x1f)) == 0) {
        sVar19 = 0xb;
      }
    }
    *(ulong *)(puVar3 + 0x1a8) =
         (long)(((sVar19 * 4 + (int)sVar19) * 2 + (int)sVar19 + 0x4d) * 0x10) | 0x100000;
    uVar9 = __fixunssfdi(fStack_24 + (float)(iVar12 * 0x10));
    *(ulong *)(puVar3 + 0x1aa) =
         uVar9 | (ulong)CONCAT42((int)(short)((uint)(iVar20 * 0x10) >> 0x10),(short)(iVar20 * 0x10))
                 << 0x10;
    *(ulong *)(puVar3 + 0x1ac) = (long)(((sVar19 + 1) * 0xb + 0x4d) * 0x10) | 0xe00000;
    uVar11 = __fixunssfdi(fStack_24 + (float)(iVar12 * 0x10) + 140.8);
    uVar9 = uVar11 | (long)((iVar16 + 0x28) * 0x10) << 0x10;
    *(ulong *)(puVar3 + 0x1ae) =
         CONCAT44((int)(uVar9 >> 0x20),CONCAT22((short)(uVar9 >> 0x10),(short)uVar11));
  }
  fStack_24 = fStack_24 + 140.8;
  if (*(short *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0x124) < 100) {
    if ((*(byte *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0xb4) & 1) != 0) {
      uVar2 = *(ushort *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0xba);
      uVar7 = (int)(short)uVar2 & 7;
      if (((int)(((long)(short)uVar2 << 0x30) >> 0x3f) < 0) && ((uVar2 & 7) != 0)) {
        uVar7 = uVar7 - 8;
      }
      if (((uint)*(byte *)(ourBtlSaveDat +
                           ((int)*(short *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0xba)
                           >> 3) + 0xdcf) & 1 << (uVar7 & 0x1f)) == 0) goto LAB_005060b8;
    }
    *(undefined8 *)(puVar3 + 0x1b2) = 0x71006f00;
    *(undefined8 *)(puVar3 + 0x1b6) = 0x71006f00;
  }
  else {
LAB_005060b8:
    sVar19 = (short)(((int)*(short *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0x124) /
                     100) % 10);
    if ((*(byte *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0xb4) & 1) != 0) {
      uVar2 = *(ushort *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0xba);
      uVar14 = uVar2 & 7;
      if (((short)uVar2 < 0) && (uVar14 != 0)) {
        uVar14 = uVar14 - 8;
      }
      if (((uint)*(byte *)(ourBtlSaveDat +
                           ((int)*(short *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0xba)
                           >> 3) + 0xdcf) & 1 << (uVar14 & 0x1f)) == 0) {
        sVar19 = 0xb;
      }
    }
    *(ulong *)(puVar3 + 0x1b0) =
         (long)(((sVar19 * 4 + (int)sVar19) * 2 + (int)sVar19 + 0x4d) * 0x10) | 0x100000;
    uVar9 = __fixunssfdi(fStack_24 + (float)(iVar12 * 0x10));
    *(ulong *)(puVar3 + 0x1b2) = uVar9 | (long)(iVar20 * 0x10) << 0x10;
    *(ulong *)(puVar3 + 0x1b4) = (long)(((sVar19 + 1) * 0xb + 0x4d) * 0x10) | 0xe00000;
    uVar11 = __fixunssfdi(fStack_24 + (float)(iVar12 * 0x10) + 140.8);
    uVar9 = uVar11 | (long)((iVar16 + 0x28) * 0x10) << 0x10;
    *(ulong *)(puVar3 + 0x1b6) =
         CONCAT44((int)(uVar9 >> 0x20),CONCAT22((short)(uVar9 >> 0x10),(short)uVar11));
  }
  fStack_24 = fStack_24 + 140.8;
  sVar19 = *(short *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0x124);
  if (CONCAT44((int)(((long)sVar19 << 0x30) >> 0x3f),(int)sVar19) < 10) {
    if ((*(byte *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0xb4) & 1) != 0) {
      uVar11 = (ulong)*(short *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0xba);
      uVar9 = uVar11 & 7;
      uVar7 = (uint)uVar9;
      if (((long)uVar11 < 0) && (uVar9 != 0)) {
        uVar7 = uVar7 - 8 & 0xffff;
      }
      if (((uint)*(byte *)(ourBtlSaveDat +
                           ((int)*(short *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0xba)
                           >> 3) + 0xdcf) & 1 << (uVar7 & 0x1f)) == 0) goto LAB_005064c0;
    }
    *(undefined8 *)(puVar3 + 0x1ba) = 0x71006f00;
    *(undefined8 *)(puVar3 + 0x1be) = 0x71006f00;
  }
  else {
LAB_005064c0:
    sVar19 = *(short *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0x124);
    sVar19 = (short)((int)((int)sVar19 / 10 + ((int)sVar19 >> 0x1f) +
                          (uint)((ushort)(sVar19 >> 0xf) >> 0xf)) % 10);
    if ((*(byte *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0xb4) & 1) != 0) {
      sVar15 = *(short *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0xba);
      uVar7 = (int)sVar15 & 7;
      if (((int)(((long)sVar15 << 0x30) >> 0x3f) < 0) && (((int)sVar15 & 7U) != 0)) {
        uVar7 = uVar7 - 8;
      }
      if (((uint)*(byte *)(ourBtlSaveDat +
                           ((int)*(short *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0xba)
                           >> 3) + 0xdcf) & 1 << (uVar7 & 0x1f)) == 0) {
        sVar19 = 0xb;
      }
    }
    *(ulong *)(puVar3 + 0x1b8) = (long)((sVar19 * 10 + (int)sVar19 + 0x4d) * 0x10) | 0x100000;
    uVar9 = __fixunssfdi(fStack_24 + (float)(iVar12 * 0x10));
    *(ulong *)(puVar3 + 0x1ba) = uVar9 | (long)(iVar20 * 0x10) << 0x10;
    *(ulong *)(puVar3 + 0x1bc) = (long)(((sVar19 + 1) * 0xb + 0x4d) * 0x10) | 0xe00000;
    uVar9 = __fixunssfdi(fStack_24 + (float)(iVar12 * 0x10) + 140.8);
    *(ulong *)(puVar3 + 0x1be) = uVar9 | (long)((iVar16 + 0x28) * 0x10) << 0x10;
  }
  fStack_24 = fStack_24 + 140.8;
  sVar19 = *(short *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0x124) % 10;
  if ((*(byte *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0xb4) & 1) != 0) {
    sVar15 = *(short *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0xba);
    uVar7 = (int)sVar15 & 7;
    if (((int)((long)((ulong)(uint)(int)sVar15 << 0x30) >> 0x3f) < 0) && (((int)sVar15 & 7U) != 0))
    {
      uVar7 = uVar7 - 8;
    }
    if (((uint)*(byte *)(ourBtlSaveDat +
                         ((int)*(short *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0xba)
                         >> 3) + 0xdcf) & 1 << (uVar7 & 0x1f)) == 0) {
      sVar19 = 0xb;
    }
  }
  *(ulong *)(puVar3 + 0x1c0) = (long)((sVar19 * 10 + (int)sVar19 + 0x4d) * 0x10) | 0x100000;
  uVar11 = __fixunssfdi(fStack_24 + (float)(iVar12 * 0x10));
  uVar9 = uVar11 | (long)(iVar20 * 0x10) << 0x10;
  *(ulong *)(puVar3 + 0x1c2) =
       CONCAT44((int)(uVar9 >> 0x20),CONCAT22((short)(uVar9 >> 0x10),(short)uVar11));
  *(ulong *)(puVar3 + 0x1c4) = (long)(((sVar19 + 1) * 0xb + 0x4d) * 0x10) | 0xe00000;
  uVar9 = __fixunssfdi(fStack_24 + (float)(iVar12 * 0x10) + 140.8);
  iVar20 = (iVar16 + 0x28) * 0x10;
  *(ulong *)(puVar3 + 0x1c6) =
       uVar9 | (ulong)CONCAT42((int)(short)((uint)iVar20 >> 0x10),(short)iVar20) << 0x10;
  iStack_28 = 0x32;
  if (((*(char *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0xb8) == '\x0e') ||
      (*(char *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0xb8) == '\x0f')) ||
     (*(char *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0xb8) == '\x10')) {
    *(long *)(puVar3 + 0x1e6) =
         (long)((iStack_2c + 0x11) * 0x10) | (long)((iStack_30 + 0x32) * 0x10) << 0x10;
    iVar20 = (iStack_2c + 0x5a) * 0x10;
    uVar9 = (long)iVar20 | (long)((iStack_30 + 0x49) * 0x10) << 0x10;
    *(ulong *)(puVar3 + 0x1ea) =
         CONCAT44((int)(uVar9 >> 0x20),CONCAT22((short)(uVar9 >> 0x10),(short)iVar20));
    iStack_28 = 0x49;
  }
  else {
    *(undefined8 *)(puVar3 + 0x1e6) = 0x71006f00;
    *(undefined8 *)(puVar3 + 0x1ea) = 0x71006f00;
  }
  iVar16 = 0x83;
  iVar20 = iStack_2c + 0xe;
  iStack_30 = iStack_30 + iStack_28;
  if (iStack_34 != 0) {
    iStack_18 = 0;
    uStack_48 = 0;
    for (iVar12 = 0; iVar12 < iStack_34; iVar12 = iVar12 + 1) {
      for (; (uStack_38 & 1 << (uStack_48 & 0x1f)) == 0; uStack_48 = uStack_48 + 1) {
      }
      iVar17 = *(int *)(uStack_48 * 4 + 0x650d80);
      sVar19 = *(short *)(iVar17 + *(int *)(iStack_10 + iVar12 * 4 + 0x88) * 8) * 0x12;
      sVar15 = *(short *)(iVar17 + *(int *)(iStack_10 + iVar12 * 4 + 0x88) * 8 + 2) * 0x16;
      iVar17 = (int)sVar19 << 4;
      uVar9 = (long)iVar17 | (long)((int)sVar15 << 4) << 0x10;
      *(ulong *)(puVar3 + iVar16 * 4) =
           CONCAT44((int)(uVar9 >> 0x20),CONCAT22((short)(uVar9 >> 0x10),(short)iVar17));
      uVar9 = (long)(iVar20 << 4) |
              (ulong)CONCAT42((int)(short)((uint)(iStack_30 << 4) >> 0x10),(short)(iStack_30 << 4))
              << 0x10;
      *(ulong *)(puVar3 + iVar16 * 4 + 2) =
           CONCAT44((int)(uVar9 >> 0x20),CONCAT22((short)(uVar9 >> 0x10),(short)(iVar20 << 4)));
      iVar17 = (sVar19 + 0x12) * 0x10;
      uVar9 = (long)iVar17 | (long)((sVar15 + 0x16) * 0x10) << 0x10;
      *(ulong *)(puVar3 + (iVar16 + 1) * 4) =
           CONCAT44((int)(uVar9 >> 0x20),CONCAT22((short)(uVar9 >> 0x10),(short)iVar17));
      *(long *)(puVar3 + (iVar16 + 1) * 4 + 2) =
           (long)((iVar20 + 0x12) * 0x10) | (long)((iStack_30 + 0x16) * 0x10) << 0x10;
      iVar16 = iVar16 + 2;
      iVar20 = iVar20 + 0x12;
      uStack_48 = uStack_48 + 1;
      iStack_18 = iStack_18 + 1;
      if (iStack_3c <= iStack_18) {
        iVar20 = iStack_2c + 0xe;
        iStack_30 = iStack_30 + 0x16;
        iStack_18 = 0;
      }
    }
  }
  for (; iStack_34 < 9; iStack_34 = iStack_34 + 1) {
    *(undefined8 *)(puVar3 + iVar16 * 4 + 2) = 0x71006f00;
    *(undefined8 *)(puVar3 + (iVar16 + 1) * 4 + 2) = 0x71006f00;
    iVar16 = iVar16 + 2;
  }
  *(undefined4 **)(iStack_10 + 0x54) = puVar3 + iVar16 * 4;
  *(byte *)(iStack_10 + 0x40) = *(byte *)(iStack_10 + 0x40) & 0xfe | bVar1;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b280  EndSet__10TargetInfoFv
 * C++: TargetInfo::EndSet()
 * size: 0x30 bytes
 * --------------------------------------------------------------------------- */
void EndSet__10TargetInfoFv(int param_1)

{
  (**(code **)(*(int *)(param_1 + 0x14) + 0x30))();
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b4e0  @24@__dt__10TargetInfoFv
 * C++: @24@__dt__10TargetInfoFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int * _24___dt__10TargetInfoFv(int *param_1,short param_2)

{
  int *piVar1;
  
  piVar1 = param_1 + -6;
  if (piVar1 != (int *)0x0) {
    param_1[-1] = 0x40a390;
    param_1[4] = 0x40a3a0;
    param_1[7] = 0x40a3b0;
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
 * JP: 0x0054b4f0  @44@__dt__10TargetInfoFv
 * C++: @44@__dt__10TargetInfoFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int _44___dt__10TargetInfoFv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x2c;
  if (iVar1 != 0) {
    *(undefined4 *)(param_1 + -0x18) = 0x40a390;
    *(undefined4 *)(param_1 + -4) = 0x40a3a0;
    *(undefined4 *)(param_1 + 8) = 0x40a3b0;
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

