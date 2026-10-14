/* decomp/H/CBtlPAfter2.c — cleaned Ghidra output (SH2JP_BATTLE.BIN, JP Furokuban, base 0x00430a00).
 * 16 function(s). Types: see types.h. Names/gp globals resolved from symbols/SLPM_602.19.syms. */
#include "types.h"

/* ---------------------------------------------------------------------------
 * JP: 0x00589b40  __ct__11CBtlPAfter2Fv
 * C++: CBtlPAfter2::__ct()
 * size: 0x488 bytes
 * --------------------------------------------------------------------------- */
int __ct__11CBtlPAfter2Fv(int param_1)

{
  int iVar1;
  undefined1 in_zero_qw [16];
  undefined4 uVar2;
  undefined8 extraout_v0_udw;
  undefined1 auVar3 [16];
  int iVar4;
  
  __ct__7CPolObjFv(param_1);
  __ct__8VIF1PrimFv(param_1 + 0x18);
  *(undefined4 *)(param_1 + 0x2c) = 0;
  *(undefined4 *)(param_1 + 0x30) = 0;
  *(undefined4 *)(param_1 + 0x34) = 0x4049f0;
  *(undefined4 *)(param_1 + 0x14) = 0x40a6f0;
  *(undefined4 *)(param_1 + 0x28) = 0x40a700;
  *(undefined4 *)(param_1 + 0x34) = 0x40a710;
  __ct__14BtlScrnCaptureFv(param_1 + 0x88);
  *(undefined4 *)(param_1 + 0x38) = 0;
  uVar2 = __nwa__FUi(0x180);
  *(undefined4 *)(param_1 + 0x18) = uVar2;
  uVar2 = __nwa__FUi(0x180);
  *(undefined4 *)(param_1 + 0x1c) = uVar2;
  *(undefined4 *)(param_1 + 0x3c) = 0;
  *(undefined1 *)(param_1 + 0x47) = 0;
  *(undefined1 *)(param_1 + 0x46) = 0;
  *(undefined1 *)(param_1 + 0x45) = 0;
  *(undefined1 *)(param_1 + 0x44) = 0;
  *(undefined4 *)(param_1 + 0x48) = 0;
  *(undefined4 *)(param_1 + 0x4c) = 0;
  uVar2 = GetTimer__7SysToolFv();
  *(undefined4 *)(param_1 + 0x50) = uVar2;
  for (iVar4 = 0; iVar4 < 0xc; iVar4 = iVar4 + 1) {
    *(undefined4 *)(param_1 + iVar4 * 4 + 0x58) = 0;
  }
  iVar4 = *(int *)(param_1 + 0x18);
  iVar1 = *(int *)(param_1 + 0x1c);
  *(undefined4 *)(iVar1 + 0x10) = 0x1000000c;
  *(undefined4 *)(iVar4 + 0x10) = 0x1000000c;
  *(undefined4 *)(iVar1 + 0x14) = 0;
  *(undefined4 *)(iVar4 + 0x14) = 0;
  *(undefined4 *)(iVar1 + 0x18) = 0;
  *(undefined4 *)(iVar4 + 0x18) = 0;
  *(undefined4 *)(iVar1 + 0x1c) = 0x5000000c;
  *(undefined4 *)(iVar4 + 0x1c) = 0x5000000c;
  *(undefined8 *)(iVar1 + 0x20) = 0x2000000000000001;
  *(undefined8 *)(iVar4 + 0x20) = 0x2000000000000001;
  *(undefined8 *)(iVar1 + 0x28) = 0xee;
  *(undefined8 *)(iVar4 + 0x28) = 0xee;
  *(undefined8 *)(iVar1 + 0x30) = 0x23001;
  *(undefined8 *)(iVar4 + 0x30) = 0x23001;
  *(undefined8 *)(iVar1 + 0x38) = 0x47;
  *(undefined8 *)(iVar4 + 0x38) = 0x47;
  *(undefined8 *)(iVar1 + 0x40) = 0x44;
  *(undefined8 *)(iVar4 + 0x40) = 0x44;
  *(undefined8 *)(iVar1 + 0x48) = 0x42;
  *(undefined8 *)(iVar4 + 0x48) = 0x42;
  auVar3._8_8_ = extraout_v0_udw;
  auVar3._0_8_ = 0x8400000000008002;
  auVar3 = _pcpyld(in_zero_qw,auVar3);
  *(long *)(iVar1 + 0x50) = auVar3._0_8_;
  *(long *)(iVar4 + 0x50) = auVar3._0_8_;
  *(undefined8 *)(iVar1 + 0x58) = 0x441cc1f0;
  *(undefined8 *)(iVar4 + 0x58) = 0x441cc1f0;
  *(undefined8 *)(iVar1 + 0x60) = 0x4c;
  *(undefined8 *)(iVar4 + 0x60) = 0x4c;
  *(undefined8 *)(iVar1 + 0x68) = 0;
  *(undefined8 *)(iVar4 + 0x68) = 0;
  *(undefined8 *)(iVar1 + 0x78) = 0x72007000;
  *(undefined8 *)(iVar4 + 0x78) = 0x72007000;
  *(undefined8 *)(iVar1 + 0x80) = 0x72009000;
  *(undefined8 *)(iVar4 + 0x80) = 0x72009000;
  *(undefined8 *)(iVar1 + 0x88) = 0;
  *(undefined8 *)(iVar4 + 0x88) = 0;
  *(undefined8 *)(iVar1 + 0x90) = 0x7a007000;
  *(undefined8 *)(iVar4 + 0x90) = 0x7a007000;
  *(undefined8 *)(iVar1 + 0x98) = 0x7a009000;
  *(undefined8 *)(iVar4 + 0x98) = 0x7a009000;
  *(undefined8 *)(iVar1 + 0xa0) = 0x4c;
  *(undefined8 *)(iVar4 + 0xa0) = 0x4c;
  *(undefined8 *)(iVar1 + 0xa8) = 0;
  *(undefined8 *)(iVar4 + 0xa8) = 0;
  *(undefined8 *)(iVar1 + 0xb8) = 0x8e007000;
  *(undefined8 *)(iVar4 + 0xb8) = 0x8e007000;
  *(undefined8 *)(iVar1 + 0xc0) = 0x8e009000;
  *(undefined8 *)(iVar4 + 0xc0) = 0x8e009000;
  *(undefined8 *)(iVar1 + 200) = 0;
  *(undefined8 *)(iVar4 + 200) = 0;
  *(undefined8 *)(iVar1 + 0xd0) = 0x86007000;
  *(undefined8 *)(iVar4 + 0xd0) = 0x86007000;
  *(undefined8 *)(iVar1 + 0xd8) = 0x86009000;
  *(undefined8 *)(iVar4 + 0xd8) = 0x86009000;
  *(undefined4 *)(iVar1 + 0xf0) = 0x10000007;
  *(undefined4 *)(iVar4 + 0xf0) = 0x10000007;
  *(undefined4 *)(iVar1 + 0xf4) = 0;
  *(undefined4 *)(iVar4 + 0xf4) = 0;
  *(undefined4 *)(iVar1 + 0xf8) = 0;
  *(undefined4 *)(iVar4 + 0xf8) = 0;
  *(undefined4 *)(iVar1 + 0xfc) = 0x50000007;
  *(undefined4 *)(iVar4 + 0xfc) = 0x50000007;
  *(undefined8 *)(iVar1 + 0x100) = 0x2000000000000001;
  *(undefined8 *)(iVar4 + 0x100) = 0x2000000000000001;
  *(undefined8 *)(iVar1 + 0x108) = 0xee;
  *(undefined8 *)(iVar4 + 0x108) = 0xee;
  *(undefined8 *)(iVar1 + 0x110) = 0x3001;
  *(undefined8 *)(iVar4 + 0x110) = 0x3001;
  *(undefined8 *)(iVar1 + 0x118) = 0x47;
  *(undefined8 *)(iVar4 + 0x118) = 0x47;
  *(undefined8 *)(iVar1 + 0x128) = 0x42;
  *(undefined8 *)(iVar4 + 0x128) = 0x42;
  *(undefined8 *)(iVar1 + 0x130) = 0x6400000000008001;
  *(undefined8 *)(iVar4 + 0x130) = 0x6400000000008001;
  *(undefined8 *)(iVar1 + 0x138) = 0x44cc10;
  *(undefined8 *)(iVar4 + 0x138) = 0x44cc10;
  *(undefined8 *)(iVar1 + 0x140) = 0x44;
  *(undefined8 *)(iVar4 + 0x140) = 0x44;
  *(undefined8 *)(iVar1 + 0x150) = 0x64006000;
  *(undefined8 *)(iVar4 + 0x150) = 0x64006000;
  *(undefined8 *)(iVar1 + 0x158) = 0x9c006000;
  *(undefined8 *)(iVar4 + 0x158) = 0x9c006000;
  *(undefined8 *)(iVar1 + 0x160) = 0x6400a000;
  *(undefined8 *)(iVar4 + 0x160) = 0x6400a000;
  *(undefined8 *)(iVar1 + 0x168) = 0x9c00a000;
  *(undefined8 *)(iVar4 + 0x168) = 0x9c00a000;
  Init__14BtlScrnCaptureFii(param_1 + 0x88,0x200,0x1c0);
  createRegsterPacket__7TextureFiiiiiii(param_1 + 0x88,1,0,0,0x200,9,9,0);
  Entry__7CPollerFP7CPolObjib(iGpffff858c + 0x48,param_1,0xa1,0);
  iVar4 = param_1;
  if (param_1 != 0) {
    iVar4 = param_1 + 0x18;
  }
  AddOT__5WorldFiP8VIF1Prim(0x42bf10,0xc,iVar4);
  return param_1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00589fd0  __dt__11CBtlPAfter2Fv
 * C++: CBtlPAfter2::__dt()
 * size: 0x12c bytes
 * --------------------------------------------------------------------------- */
int __dt__11CBtlPAfter2Fv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x14) = 0x40a6f0;
    *(undefined4 *)(param_1 + 0x28) = 0x40a700;
    *(undefined4 *)(param_1 + 0x34) = 0x40a710;
    if (*(int *)(param_1 + 0x18) != 0) {
      __dla__FPv(*(undefined4 *)(param_1 + 0x18));
    }
    if (*(int *)(param_1 + 0x1c) != 0) {
      __dla__FPv(*(undefined4 *)(param_1 + 0x1c));
    }
    __dt__14BtlScrnCaptureFv(param_1 + 0x88,0xffffffffffffffff);
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
 * JP: 0x0058a100  Polling__11CBtlPAfter2Fv
 * C++: CBtlPAfter2::Polling()
 * size: 0x830 bytes
 * --------------------------------------------------------------------------- */
undefined8 Polling__11CBtlPAfter2Fv(int param_1)

{
  int iVar1;
  undefined1 uVar2;
  float fVar3;
  float fStack_14;
  
  iVar1 = GetTimer__7SysToolFv();
  fVar3 = (float)(uint)(iVar1 - *(int *)(param_1 + 0x50)) * 0.001;
  *(int *)(param_1 + 0x50) = iVar1;
  switch(*(undefined4 *)(param_1 + 0x3c)) {
  case 0:
    *(undefined1 *)(param_1 + 0x47) = 0;
    break;
  case 1:
    *(undefined1 *)(param_1 + 0x47) = 0x80;
    break;
  case 2:
    *(undefined1 *)(param_1 + 0x47) = 0x80;
    break;
  case 3:
    *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) + fVar3;
    fStack_14 = 128.0 - (*(float *)(param_1 + 0x54) / *(float *)(param_1 + 0x40)) * 128.0;
    if (fStack_14 < 0.0) {
      fStack_14 = 0.0;
      *(undefined4 *)(param_1 + 0x3c) = 0;
    }
    if (128.0 <= fStack_14) {
      fStack_14 = 128.0;
    }
    if (fStack_14 < 2.1474836e+09) {
      uVar2 = (undefined1)(int)fStack_14;
    }
    else {
      uVar2 = (undefined1)(int)(fStack_14 - 2.1474836e+09);
    }
    *(undefined1 *)(param_1 + 0x47) = uVar2;
    break;
  case 4:
    *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) + fVar3;
    fStack_14 = (*(float *)(param_1 + 0x54) / *(float *)(param_1 + 0x40)) * 128.0;
    if (fStack_14 < 0.0) {
      fStack_14 = 0.0;
    }
    if (128.0 <= fStack_14) {
      fStack_14 = 128.0;
      *(undefined4 *)(param_1 + 0x3c) = 1;
    }
    if (fStack_14 < 2.1474836e+09) {
      uVar2 = (undefined1)(int)fStack_14;
    }
    else {
      uVar2 = (undefined1)(int)(fStack_14 - 2.1474836e+09);
    }
    *(undefined1 *)(param_1 + 0x47) = uVar2;
    break;
  case 5:
    *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) + fVar3;
    fStack_14 = 128.0 - (*(float *)(param_1 + 0x54) / *(float *)(param_1 + 0x40)) * 128.0;
    if (fStack_14 < 0.0) {
      fStack_14 = 0.0;
      *(undefined4 *)(param_1 + 0x3c) = 0;
    }
    if (128.0 <= fStack_14) {
      fStack_14 = 128.0;
    }
    if (fStack_14 < 2.1474836e+09) {
      uVar2 = (undefined1)(int)fStack_14;
    }
    else {
      uVar2 = (undefined1)(int)(fStack_14 - 2.1474836e+09);
    }
    *(undefined1 *)(param_1 + 0x47) = uVar2;
    break;
  case 6:
    *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) + fVar3;
    fStack_14 = (*(float *)(param_1 + 0x54) / *(float *)(param_1 + 0x40)) * 128.0;
    if (fStack_14 < 0.0) {
      fStack_14 = 0.0;
    }
    if (128.0 <= fStack_14) {
      fStack_14 = 128.0;
      *(undefined4 *)(param_1 + 0x3c) = 2;
    }
    if (fStack_14 < 2.1474836e+09) {
      uVar2 = (undefined1)(int)fStack_14;
    }
    else {
      uVar2 = (undefined1)(int)(fStack_14 - 2.1474836e+09);
    }
    *(undefined1 *)(param_1 + 0x47) = uVar2;
    break;
  case 7:
    *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) + fVar3;
    if (*(float *)(param_1 + 0x40) <= *(float *)(param_1 + 0x54)) {
      *(undefined4 *)(param_1 + 0x3c) = 0;
      *(undefined1 *)(param_1 + 0x47) = 0;
    }
    break;
  case 8:
    *(undefined1 *)(param_1 + 0x47) = 0x40;
    break;
  case 9:
    *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) + fVar3;
    fStack_14 = (*(float *)(param_1 + 0x54) / *(float *)(param_1 + 0x40)) * 128.0;
    if (fStack_14 < 0.0) {
      fStack_14 = 0.0;
    }
    if (64.0 <= fStack_14) {
      fStack_14 = 64.0;
      *(undefined4 *)(param_1 + 0x3c) = 8;
    }
    if (fStack_14 < 2.1474836e+09) {
      uVar2 = (undefined1)(int)fStack_14;
    }
    else {
      uVar2 = (undefined1)(int)(fStack_14 - 2.1474836e+09);
    }
    *(undefined1 *)(param_1 + 0x47) = uVar2;
    break;
  case 10:
    *(float *)(param_1 + 0x54) = *(float *)(param_1 + 0x54) + fVar3;
    fStack_14 = 128.0 - (*(float *)(param_1 + 0x54) / *(float *)(param_1 + 0x40)) * 128.0;
    if (fStack_14 < 0.0) {
      fStack_14 = 0.0;
      *(undefined4 *)(param_1 + 0x3c) = 0;
    }
    if (128.0 <= fStack_14) {
      fStack_14 = 128.0;
    }
    if (fStack_14 < 2.1474836e+09) {
      uVar2 = (undefined1)(int)fStack_14;
    }
    else {
      uVar2 = (undefined1)(int)(fStack_14 - 2.1474836e+09);
    }
    *(undefined1 *)(param_1 + 0x47) = uVar2;
  }
  iVar1 = *(int *)(param_1 + 0x48);
  if (iVar1 == 3) {
    *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x4c) - fVar3 * 7.5 * 64.0;
    if (*(float *)(param_1 + 0x4c) <= 0.0) {
      *(undefined4 *)(param_1 + 0x48) = 0;
      *(undefined4 *)(param_1 + 0x4c) = 0;
    }
  }
  else if (((iVar1 != 2) && (iVar1 == 1)) &&
          (*(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x4c) + fVar3 * 7.5 * 64.0,
          64.0 <= *(float *)(param_1 + 0x4c))) {
    *(undefined4 *)(param_1 + 0x48) = 2;
    *(undefined4 *)(param_1 + 0x4c) = 0x42800000;
  }
  *(byte *)(*(int *)(iGpffff86b4 + 0x4324) + 0x19) =
       *(byte *)(*(int *)(iGpffff86b4 + 0x4324) + 0x19) & 0xfe;
  return 0;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0058a930  Destruct__11CBtlPAfter2Fv
 * C++: CBtlPAfter2::Destruct()
 * size: 0x78 bytes
 * --------------------------------------------------------------------------- */
void Destruct__11CBtlPAfter2Fv(int param_1)

{
  int iVar1;
  
  Dispose__7CPollerFP7CPolObj(iGpffff858c + 0x48,param_1);
  iVar1 = param_1;
  if (param_1 != 0) {
    iVar1 = param_1 + 0x18;
  }
  ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,iVar1);
  (**(code **)(*(int *)(param_1 + 0x34) + 0xc))();
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0058a9b0  MakePacket__11CBtlPAfter2Fv
 * C++: CBtlPAfter2::MakePacket()
 * size: 0x8d4 bytes
 * --------------------------------------------------------------------------- */
void MakePacket__11CBtlPAfter2Fv(int param_1)

{
  int iVar1;
  bool bVar2;
  bool bVar3;
  long lVar4;
  int iVar5;
  undefined4 *puVar6;
  uint uVar7;
  float fVar8;
  
  bVar3 = false;
  bVar2 = false;
  uVar7 = (uint)(*(int *)(param_1 + 0x38) == 0);
  puVar6 = *(undefined4 **)(param_1 + uVar7 * 4 + 0x18);
  for (iVar5 = *(int *)(iGpffff86b4 + 0x4370); iVar5 != 0; iVar5 = *(int *)(iVar5 + 0x3c)) {
    if (*(int *)(iVar5 + 0x4c) == 0x12) {
      if (!bVar2) {
        lVar4 = (**(code **)(*(int *)(param_1 + 0x128) + 0x2c))();
        if (lVar4 != 0) {
          *puVar6 = 0x20000000;
          puVar6[1] = (int)lVar4;
          if (bVar3) {
            puVar6[2] = 0;
          }
          else {
            puVar6[2] = 0x13000000;
          }
          puVar6[3] = 0;
          puVar6 = *(undefined4 **)(param_1 + 0x134);
        }
        bVar2 = true;
      }
      lVar4 = (**(code **)(*(int *)(iVar5 + 0x14) + 0x34))();
      if (lVar4 != 0) {
        *puVar6 = 0x20000000;
        puVar6[1] = (int)lVar4;
        if (bVar3) {
          puVar6[2] = 0;
        }
        else {
          puVar6[2] = 0x13000000;
          bVar3 = true;
        }
        puVar6[3] = 0;
        puVar6 = *(undefined4 **)(iVar5 + 0x54);
      }
    }
  }
  for (iVar5 = *(int *)(iGpffff86b4 + 0x4370); iVar5 != 0; iVar5 = *(int *)(iVar5 + 0x3c)) {
    if (*(int *)(iVar5 + 0x4c) == 0x13) {
      if (!bVar2) {
        lVar4 = (**(code **)(*(int *)(param_1 + 0x128) + 0x2c))();
        if (lVar4 != 0) {
          *puVar6 = 0x20000000;
          puVar6[1] = (int)lVar4;
          if (bVar3) {
            puVar6[2] = 0;
          }
          else {
            puVar6[2] = 0x13000000;
          }
          puVar6[3] = 0;
          puVar6 = *(undefined4 **)(param_1 + 0x134);
        }
        bVar2 = true;
      }
      lVar4 = (**(code **)(*(int *)(iVar5 + 0x14) + 0x34))();
      if (lVar4 != 0) {
        *puVar6 = 0x20000000;
        puVar6[1] = (int)lVar4;
        if (bVar3) {
          puVar6[2] = 0;
        }
        else {
          puVar6[2] = 0x13000000;
          bVar3 = true;
        }
        puVar6[3] = 0;
        puVar6 = *(undefined4 **)(iVar5 + 0x54);
      }
    }
  }
  if (0.0 < *(float *)(param_1 + 0x4c)) {
    iVar5 = *(int *)(param_1 + uVar7 * 4 + 0x18);
    *puVar6 = 0x20000000;
    puVar6[1] = iVar5 + 0x10;
    if (bVar3) {
      puVar6[2] = 0;
    }
    else {
      puVar6[2] = 0x13000000;
      bVar3 = true;
    }
    puVar6[3] = 0;
    lVar4 = __fixunssfdi(*(undefined4 *)(param_1 + 0x4c));
    *(long *)(iVar5 + 0x70) = lVar4 << 0x18;
    lVar4 = __fixunssfdi(*(undefined4 *)(param_1 + 0x4c));
    *(long *)(iVar5 + 0xb0) = lVar4 << 0x18;
    puVar6 = (undefined4 *)(iVar5 + 0xe0);
  }
  if (*(char *)(param_1 + 0x47) != '\0') {
    iVar5 = *(int *)(param_1 + uVar7 * 4 + 0x18);
    *puVar6 = 0x20000000;
    puVar6[1] = iVar5 + 0xf0;
    if (bVar3) {
      puVar6[2] = 0;
    }
    else {
      puVar6[2] = 0x13000000;
      bVar3 = true;
    }
    puVar6[3] = 0;
    if (*(int *)(param_1 + 0x3c) == 7) {
      *(undefined8 *)(iVar5 + 0x120) = 0x84;
    }
    else {
      *(undefined8 *)(iVar5 + 0x120) = 0x44;
    }
    *(ulong *)(iVar5 + 0x148) = (ulong)*(uint *)(param_1 + 0x44);
    puVar6 = (undefined4 *)(iVar5 + 0x170);
  }
  for (iVar5 = *(int *)(iGpffff86b4 + 0x4370); iVar5 != 0; iVar5 = *(int *)(iVar5 + 0x3c)) {
    if ((*(int *)(iVar5 + 0x4c) == 0x19) &&
       (lVar4 = (**(code **)(*(int *)(iVar5 + 0x14) + 0x34))(), lVar4 != 0)) {
      *puVar6 = 0x20000000;
      puVar6[1] = (int)lVar4;
      if (bVar3) {
        puVar6[2] = 0;
      }
      else {
        puVar6[2] = 0x13000000;
        bVar3 = true;
      }
      puVar6[3] = 0;
      puVar6 = *(undefined4 **)(iVar5 + 0x54);
    }
  }
  for (iVar5 = *(int *)(iGpffff86b4 + 0x4370); iVar5 != 0; iVar5 = *(int *)(iVar5 + 0x3c)) {
    if ((*(int *)(iVar5 + 0x4c) == 0xd) &&
       (lVar4 = (**(code **)(*(int *)(iVar5 + 0x14) + 0x34))(), lVar4 != 0)) {
      *puVar6 = 0x20000000;
      puVar6[1] = (int)lVar4;
      if (bVar3) {
        puVar6[2] = 0;
      }
      else {
        puVar6[2] = 0x13000000;
        bVar3 = true;
      }
      puVar6[3] = 0;
      puVar6 = *(undefined4 **)(iVar5 + 0x54);
    }
  }
  for (iVar5 = *(int *)(iGpffff86b4 + 0x4370); iVar5 != 0; iVar5 = *(int *)(iVar5 + 0x3c)) {
    if ((*(int *)(iVar5 + 0x4c) == 0x11) &&
       (lVar4 = (**(code **)(*(int *)(iVar5 + 0x14) + 0x34))(), lVar4 != 0)) {
      *puVar6 = 0x20000000;
      puVar6[1] = (int)lVar4;
      if (bVar3) {
        puVar6[2] = 0;
      }
      else {
        puVar6[2] = 0x13000000;
        bVar3 = true;
      }
      puVar6[3] = 0;
      puVar6 = *(undefined4 **)(iVar5 + 0x54);
    }
  }
  fVar8 = 128.0;
  for (iVar5 = 0; iVar5 < 0xc; iVar5 = iVar5 + 1) {
    if (*(int *)(param_1 + iVar5 * 4 + 0x58) != 0) {
      iVar1 = *(int *)(param_1 + iVar5 * 4 + 0x58);
      *(undefined4 *)(iVar1 + 0x70) = 0x41800000;
      *(float *)(iVar1 + 0x74) = fVar8;
      *(undefined4 *)(iVar1 + 0x78) = 0;
      *(undefined4 *)(iVar1 + 0x7c) = 0x3f800000;
      fVar8 = fVar8 + *(float *)(*(int *)(param_1 + iVar5 * 4 + 0x58) + 0x84) * 24.0 + 1.0;
    }
  }
  for (iVar5 = 0xb; -1 < iVar5; iVar5 = iVar5 + -1) {
    if ((*(int *)(param_1 + iVar5 * 4 + 0x58) != 0) &&
       (lVar4 = (**(code **)(*(int *)(*(int *)(param_1 + iVar5 * 4 + 0x58) + 0x14) + 0x34))(),
       lVar4 != 0)) {
      *puVar6 = 0x20000000;
      puVar6[1] = (int)lVar4;
      if (bVar3) {
        puVar6[2] = 0;
      }
      else {
        puVar6[2] = 0x13000000;
        bVar3 = true;
      }
      puVar6[3] = 0;
      puVar6 = *(undefined4 **)(*(int *)(param_1 + iVar5 * 4 + 0x58) + 0x54);
    }
  }
  if ((*(int *)(iGpffff86b4 + 0x4328) != 0) &&
     (lVar4 = (**(code **)(*(int *)(*(int *)(iGpffff86b4 + 0x4328) + 0x14) + 0x30))(), lVar4 != 0))
  {
    *puVar6 = 0x20000000;
    puVar6[1] = (int)lVar4;
    if (bVar3) {
      puVar6[2] = 0;
    }
    else {
      puVar6[2] = 0x13000000;
      bVar3 = true;
    }
    puVar6[3] = 0;
    puVar6 = *(undefined4 **)(*(int *)(iGpffff86b4 + 0x4328) + 0x54);
  }
  if ((*(int *)(iGpffff86b4 + 0x436c) != 0) &&
     (lVar4 = (**(code **)(*(int *)(*(int *)(iGpffff86b4 + 0x436c) + 0x14) + 0x30))(), lVar4 != 0))
  {
    *puVar6 = 0x20000000;
    puVar6[1] = (int)lVar4;
    if (bVar3) {
      puVar6[2] = 0;
    }
    else {
      puVar6[2] = 0x13000000;
      bVar3 = true;
    }
    puVar6[3] = 0;
    puVar6 = *(undefined4 **)(*(int *)(iGpffff86b4 + 0x436c) + 0x54);
  }
  for (iVar5 = *(int *)(iGpffff86b4 + 0x4370); iVar5 != 0; iVar5 = *(int *)(iVar5 + 0x3c)) {
    if ((*(int *)(iVar5 + 0x4c) == 0xf) &&
       (lVar4 = (**(code **)(*(int *)(iVar5 + 0x14) + 0x34))(), lVar4 != 0)) {
      *puVar6 = 0x20000000;
      puVar6[1] = (int)lVar4;
      if (bVar3) {
        puVar6[2] = 0;
      }
      else {
        puVar6[2] = 0x13000000;
        bVar3 = true;
      }
      puVar6[3] = 0;
      puVar6 = *(undefined4 **)(iVar5 + 0x54);
    }
  }
  for (iVar5 = *(int *)(iGpffff86b4 + 0x4370); iVar5 != 0; iVar5 = *(int *)(iVar5 + 0x3c)) {
    if ((*(int *)(iVar5 + 0x4c) == 0x15) &&
       (lVar4 = (**(code **)(*(int *)(iVar5 + 0x14) + 0x34))(), lVar4 != 0)) {
      *puVar6 = 0x20000000;
      puVar6[1] = (int)lVar4;
      if (bVar3) {
        puVar6[2] = 0;
      }
      else {
        puVar6[2] = 0x13000000;
        bVar3 = true;
      }
      puVar6[3] = 0;
      puVar6 = *(undefined4 **)(iVar5 + 0x54);
    }
  }
  *puVar6 = 0x60000000;
  puVar6[1] = 0;
  puVar6[2] = 0;
  puVar6[3] = 0;
  *(uint *)(param_1 + 0x38) = uVar7;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0058b290  SetFadeOut__11CBtlPAfter2Ff
 * C++: CBtlPAfter2::SetFadeOut(float)
 * size: 0x7c bytes
 * --------------------------------------------------------------------------- */
void SetFadeOut__11CBtlPAfter2Ff(undefined4 param_1,int param_2)

{
  if (*(int *)(param_2 + 0x3c) != 1) {
    *(undefined4 *)(param_2 + 0x3c) = 4;
    *(undefined4 *)(param_2 + 0x54) = 0;
    *(undefined4 *)(param_2 + 0x40) = param_1;
    *(undefined1 *)(param_2 + 0x46) = 0;
    *(undefined1 *)(param_2 + 0x45) = 0;
    *(undefined1 *)(param_2 + 0x44) = 0;
    *(undefined1 *)(param_2 + 0x47) = 0;
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0058b310  EntryDDisp__11CBtlPAfter2Fi
 * C++: CBtlPAfter2::EntryDDisp(int)
 * size: 0x2e0 bytes
 * --------------------------------------------------------------------------- */
undefined4 EntryDDisp__11CBtlPAfter2Fi(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  long lVar3;
  int iVar4;
  int iVar5;
  float fVar6;
  float fVar7;
  undefined4 uStack_20;
  float fStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  float fStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  iVar4 = 0;
  do {
    if (0xb < iVar4) {
      iVar4 = 0;
      while( true ) {
        if (0xb < iVar4) {
          iVar4 = -1;
          fVar7 = 128.0;
          for (iVar5 = 0; iVar5 < 0xc; iVar5 = iVar5 + 1) {
            if (*(int *)(param_1 + iVar5 * 4 + 0x58) == 0) {
              fVar6 = fVar7;
              if (iVar4 < 0) {
                lVar3 = __nw__FUi(800);
                uVar2 = 0;
                if (lVar3 != 0) {
                  uStack_20 = 0x41800000;
                  uStack_18 = 0;
                  uStack_14 = 0x3f800000;
                  fStack_1c = fVar7;
                  uVar2 = __ct__12TotalHitInfoFii7FVector(lVar3,iVar5,param_2,&uStack_20);
                }
                *(undefined4 *)(param_1 + iVar5 * 4 + 0x58) = uVar2;
                fVar6 = fVar7 + *(float *)(*(int *)(param_1 + iVar5 * 4 + 0x58) + 0x84) * 24.0 + 1.0
                ;
                iVar4 = iVar5;
              }
            }
            else {
              uStack_10 = 0x41800000;
              uStack_8 = 0;
              uStack_4 = 0x3f800000;
              iVar1 = *(int *)(param_1 + iVar5 * 4 + 0x58);
              *(undefined4 *)(iVar1 + 0x70) = 0x41800000;
              *(float *)(iVar1 + 0x74) = fVar7;
              *(undefined4 *)(iVar1 + 0x78) = 0;
              *(undefined4 *)(iVar1 + 0x7c) = 0x3f800000;
              fVar6 = fVar7 + *(float *)(*(int *)(param_1 + iVar5 * 4 + 0x58) + 0x84) * 24.0 + 1.0;
              fStack_c = fVar7;
            }
            fVar7 = fVar6;
          }
          if (iVar4 < 0) {
            uVar2 = 0;
          }
          else {
            uVar2 = *(undefined4 *)(param_1 + iVar4 * 4 + 0x58);
          }
          return uVar2;
        }
        if ((*(int *)(param_1 + iVar4 * 4 + 0x58) != 0) &&
           (*(int *)(*(int *)(param_1 + iVar4 * 4 + 0x58) + 0x48) == param_2)) break;
        iVar4 = iVar4 + 1;
      }
      return *(undefined4 *)(param_1 + iVar4 * 4 + 0x58);
    }
    iVar5 = iVar4;
    if (*(int *)(param_1 + iVar4 * 4 + 0x58) == 0) {
      do {
        iVar5 = iVar5 + 1;
        if (0xb < iVar5) goto LAB_0058b3c8;
      } while (*(int *)(param_1 + iVar5 * 4 + 0x58) == 0);
      *(undefined4 *)(param_1 + iVar4 * 4 + 0x58) = *(undefined4 *)(param_1 + iVar5 * 4 + 0x58);
      *(int *)(*(int *)(param_1 + iVar4 * 4 + 0x58) + 0x44) = iVar4;
      *(undefined4 *)(param_1 + iVar5 * 4 + 0x58) = 0;
    }
LAB_0058b3c8:
    iVar4 = iVar4 + 1;
  } while( true );
}

/* ---------------------------------------------------------------------------
 * JP: 0x0058b5f0  ReleaseDDisp__11CBtlPAfter2Fi
 * C++: CBtlPAfter2::ReleaseDDisp(int)
 * size: 0x180 bytes
 * --------------------------------------------------------------------------- */
void ReleaseDDisp__11CBtlPAfter2Fi(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  float fVar3;
  
  *(undefined4 *)(param_1 + param_2 * 4 + 0x58) = 0;
  iVar1 = 0;
  do {
    if (0xb < iVar1) {
      fVar3 = 128.0;
      for (iVar1 = 0; iVar1 < 0xc; iVar1 = iVar1 + 1) {
        if (*(int *)(param_1 + iVar1 * 4 + 0x58) != 0) {
          iVar2 = *(int *)(param_1 + iVar1 * 4 + 0x58);
          *(undefined4 *)(iVar2 + 0x70) = 0x41800000;
          *(float *)(iVar2 + 0x74) = fVar3;
          *(undefined4 *)(iVar2 + 0x78) = 0;
          *(undefined4 *)(iVar2 + 0x7c) = 0x3f800000;
          fVar3 = fVar3 + *(float *)(*(int *)(param_1 + iVar1 * 4 + 0x58) + 0x84) * 24.0 + 1.0;
        }
      }
      return;
    }
    iVar2 = iVar1;
    if (*(int *)(param_1 + iVar1 * 4 + 0x58) == 0) {
      do {
        iVar2 = iVar2 + 1;
        if (0xb < iVar2) goto LAB_0058b698;
      } while (*(int *)(param_1 + iVar2 * 4 + 0x58) == 0);
      *(undefined4 *)(param_1 + iVar1 * 4 + 0x58) = *(undefined4 *)(param_1 + iVar2 * 4 + 0x58);
      *(int *)(*(int *)(param_1 + iVar1 * 4 + 0x58) + 0x44) = iVar1;
      *(undefined4 *)(param_1 + iVar2 * 4 + 0x58) = 0;
    }
LAB_0058b698:
    iVar1 = iVar1 + 1;
  } while( true );
}

/* ---------------------------------------------------------------------------
 * JP: 0x0058b770  GetDDisp__11CBtlPAfter2Fi
 * C++: CBtlPAfter2::GetDDisp(int)
 * size: 0x98 bytes
 * --------------------------------------------------------------------------- */
undefined4 GetDDisp__11CBtlPAfter2Fi(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = 0;
  while( true ) {
    if (0xb < iVar1) {
      return 0;
    }
    if ((*(int *)(param_1 + iVar1 * 4 + 0x58) != 0) &&
       (*(int *)(*(int *)(param_1 + iVar1 * 4 + 0x58) + 0x48) == param_2)) break;
    iVar1 = iVar1 + 1;
  }
  return *(undefined4 *)(param_1 + iVar1 * 4 + 0x58);
}

/* ---------------------------------------------------------------------------
 * JP: 0x0058b810  EntryHitCntEffect__11CBtlPAfter2Fii
 * C++: CBtlPAfter2::EntryHitCntEffect(int, int)
 * size: 0xc0 bytes
 * --------------------------------------------------------------------------- */
void EntryHitCntEffect__11CBtlPAfter2Fii(undefined8 param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  long lVar2;
  
  iVar1 = *(int *)(iGpffff86b4 + 0x4370);
  while( true ) {
    if (iVar1 == 0) {
      lVar2 = __nw__FUi(0x68);
      if (lVar2 != 0) {
        __ct__9HitCntEffFiii(lVar2,0,param_2,param_3);
      }
      return;
    }
    if ((*(int *)(iVar1 + 0x4c) == 0xf) && (*(int *)(iVar1 + 0x48) == param_2)) break;
    iVar1 = *(int *)(iVar1 + 0x3c);
  }
  Reset__9HitCntEffFi(iVar1,param_3);
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0058b8d0  SetHitImpact__11CBtlPAfter2Fi7FVectorf
 * C++: CBtlPAfter2::SetHitImpact(int, FVector, float)
 * size: 0xf0 bytes
 * --------------------------------------------------------------------------- */
void SetHitImpact__11CBtlPAfter2Fi7FVectorf
               (undefined4 param_1,undefined8 param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  long lVar2;
  undefined8 uVar3;
  undefined1 auStack_60 [16];
  undefined1 auStack_50 [32];
  int iStack_30;
  undefined4 uStack_20;
  undefined4 uStack_10;
  
  iVar1 = *(int *)(iGpffff86b4 + 0x4370);
  while( true ) {
    iStack_30 = param_3;
    uStack_20 = param_4;
    uStack_10 = param_1;
    if (iVar1 == 0) {
      lVar2 = __nw__FUi(0x80);
      if (lVar2 != 0) {
        uVar3 = __ct__7FVectorFRC7FVector(auStack_60,uStack_20);
        __ct__9HitImpactFii7FVectorf(uStack_10,lVar2,0,iStack_30,uVar3);
      }
      return;
    }
    if ((*(int *)(iVar1 + 0x48) == param_3) && (*(int *)(iVar1 + 0x4c) == 0x12)) break;
    iVar1 = *(int *)(iVar1 + 0x3c);
  }
  uVar3 = __ct__7FVectorFRC7FVector(auStack_50,param_4);
  Reset__9HitImpactF7FVectorf(uStack_10,iVar1,uVar3);
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0058b9c0  SetBattleBlear__11CBtlPAfter2Fifff
 * C++: CBtlPAfter2::SetBattleBlear(int, float, float, float)
 * size: 0xc8 bytes
 * --------------------------------------------------------------------------- */
void SetBattleBlear__11CBtlPAfter2Fifff
               (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined8 param_4,
               undefined4 param_5)

{
  int iVar1;
  long lVar2;
  
  iVar1 = *(int *)(iGpffff86b4 + 0x4370);
  while( true ) {
    if (iVar1 == 0) {
      lVar2 = __nw__FUi(0x70);
      if (lVar2 != 0) {
        __ct__8BtlBlearFiifff(param_1,param_2,param_3,lVar2,0,param_5);
      }
      return;
    }
    if (*(int *)(iVar1 + 0x4c) == 0x13) break;
    iVar1 = *(int *)(iVar1 + 0x3c);
  }
  Reset__8BtlBlearFfff(param_1,param_2,param_3,iVar1);
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0058ba90  getPacket__11CBtlPAfter2Fv
 * C++: CBtlPAfter2::getPacket()
 * size: 0x40 bytes
 * --------------------------------------------------------------------------- */
undefined4 getPacket__11CBtlPAfter2Fv(int param_1)

{
  MakePacket__11CBtlPAfter2Fv(param_1);
  return *(undefined4 *)(param_1 + *(int *)(param_1 + 0x38) * 4 + 0x18);
}

/* ---------------------------------------------------------------------------
 * JP: 0x0058bb70  @24@getPacket__11CBtlPAfter2Fv
 * C++: @24@getPacket__11CBtlPAfter2Fv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
undefined4 _24_getPacket__11CBtlPAfter2Fv(int param_1)

{
  MakePacket__11CBtlPAfter2Fv(param_1 + -0x18);
  return *(undefined4 *)(param_1 + -0x18 + *(int *)(param_1 + 0x20) * 4 + 0x18);
}

/* ---------------------------------------------------------------------------
 * JP: 0x0058bb80  @24@__dt__11CBtlPAfter2Fv
 * C++: @24@__dt__11CBtlPAfter2Fv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int * _24___dt__11CBtlPAfter2Fv(int *param_1,short param_2)

{
  int *piVar1;
  
  piVar1 = param_1 + -6;
  if (piVar1 != (int *)0x0) {
    param_1[-1] = 0x40a6f0;
    param_1[4] = 0x40a700;
    param_1[7] = 0x40a710;
    if (*param_1 != 0) {
      __dla__FPv(*param_1);
    }
    if (param_1[1] != 0) {
      __dla__FPv(param_1[1]);
    }
    __dt__14BtlScrnCaptureFv(param_1 + 0x1c,0xffffffffffffffff);
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
 * JP: 0x0058bb90  @44@__dt__11CBtlPAfter2Fv
 * C++: @44@__dt__11CBtlPAfter2Fv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int _44___dt__11CBtlPAfter2Fv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x2c;
  if (iVar1 != 0) {
    *(undefined4 *)(param_1 + -0x18) = 0x40a6f0;
    *(undefined4 *)(param_1 + -4) = 0x40a700;
    *(undefined4 *)(param_1 + 8) = 0x40a710;
    if (*(int *)(param_1 + -0x14) != 0) {
      __dla__FPv(*(undefined4 *)(param_1 + -0x14));
    }
    if (*(int *)(param_1 + -0x10) != 0) {
      __dla__FPv(*(undefined4 *)(param_1 + -0x10));
    }
    __dt__14BtlScrnCaptureFv(param_1 + 0x5c,0xffffffffffffffff);
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

