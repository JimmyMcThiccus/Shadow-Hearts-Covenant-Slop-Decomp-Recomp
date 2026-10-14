/* decomp/H/HitInfo.c — cleaned Ghidra output (SH2JP_BATTLE.BIN, JP Furokuban, base 0x00430a00).
 * 8 function(s). Types: see types.h. Names/gp globals resolved from symbols/SLPM_602.19.syms. */
#include "types.h"

/* ---------------------------------------------------------------------------
 * JP: 0x004fbef0  __ct__7HitInfoFii7FVectoriPciiff
 * C++: HitInfo::__ct(int, int, FVector, int, char *, int, int, float, float)
 * size: 0x20c bytes
 * --------------------------------------------------------------------------- */
undefined8
__ct__7HitInfoFii7FVectoriPciiff
          (undefined4 param_1,undefined4 param_2,undefined8 param_3,undefined8 param_4,
          undefined8 param_5,undefined8 *param_6,undefined4 param_7,long param_8,undefined4 param_9,
          undefined4 param_10)

{
  undefined8 uVar1;
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  
  __ct__6BtlEffFii(param_3,param_4,param_5);
  iVar5 = (int)param_3;
  *(undefined4 *)(iVar5 + 0x14) = 0x40a430;
  *(undefined4 *)(iVar5 + 0x28) = 0x40a440;
  *(undefined4 *)(iVar5 + 0x34) = 0x40a450;
  *(undefined4 *)(iVar5 + 0x80) = in_zero_lo;
  *(undefined4 *)(iVar5 + 0x84) = in_zero_hi;
  *(undefined4 *)(iVar5 + 0x88) = in_zero_udw;
  *(undefined4 *)(iVar5 + 0x8c) = in_register_0000000c;
  *(int *)(iVar5 + 0x44) = (int)param_4;
  *(int *)(iVar5 + 0x48) = (int)param_5;
  *(undefined4 *)(iVar5 + 0x4c) = 0xd;
  *(undefined4 *)(iVar5 + 0x40) = 0;
  *(undefined4 *)(iVar5 + 0x5c) = param_7;
  *(undefined4 *)(iVar5 + 0x60) = 0;
  *(undefined4 *)(iVar5 + 0x6c) = 0;
  *(undefined4 *)(iVar5 + 0x70) = param_1;
  uVar1 = *param_6;
  uVar3 = *(undefined4 *)(param_6 + 1);
  uVar4 = *(undefined4 *)((int)param_6 + 0xc);
  *(int *)(iVar5 + 0x80) = (int)uVar1;
  *(int *)(iVar5 + 0x84) = (int)((ulong)uVar1 >> 0x20);
  *(undefined4 *)(iVar5 + 0x88) = uVar3;
  *(undefined4 *)(iVar5 + 0x8c) = uVar4;
  *(undefined4 *)(iVar5 + 0x90) = 0;
  *(undefined4 *)(iVar5 + 0x94) = param_2;
  *(undefined4 *)(iVar5 + 0x98) = 0x3f800000;
  if (param_8 == 0) {
    *(undefined4 *)(iVar5 + 0xa4) = 0;
  }
  else {
    iVar2 = strlen(param_8);
    uVar3 = __nwa__FUi(iVar2 + 1);
    *(undefined4 *)(iVar5 + 0xa4) = uVar3;
    strcpy(*(undefined4 *)(iVar5 + 0xa4),param_8);
  }
  *(undefined4 *)(iVar5 + 0xa8) = param_9;
  *(undefined4 *)(iVar5 + 0xac) = param_10;
  *(undefined4 *)(iVar5 + 0xa0) = 0x40c90fdb;
  *(undefined4 *)(iVar5 + 0x9c) = 0x3f800000;
  *(undefined4 *)(iVar5 + 0x1c) = 0;
  *(undefined4 *)(iVar5 + 0x18) = 0;
  *(undefined4 *)(iVar5 + 0x54) = 0;
  if (*(int *)(iVar5 + 0x5c) == 9) {
    *(undefined4 *)(iVar5 + 0x4c) = 0x15;
    *(undefined4 *)(iVar5 + 0x98) = 0x3f400000;
    *(undefined4 *)(iVar5 + 0x9c) = 0;
  }
  Entry__7CPollerFP7CPolObjib(iGpffff858c + 0x48,param_3,0x80,0);
  BtlEffEntry__7CBattleFiP6BtlEff(uGpffff86b4,0xffffffffffffffff,param_3);
  return param_3;
}

/* ---------------------------------------------------------------------------
 * JP: 0x004fc100  __dt__7HitInfoFv
 * C++: HitInfo::__dt()
 * size: 0x174 bytes
 * --------------------------------------------------------------------------- */
int __dt__7HitInfoFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x14) = 0x40a430;
    *(undefined4 *)(param_1 + 0x28) = 0x40a440;
    *(undefined4 *)(param_1 + 0x34) = 0x40a450;
    if (*(int *)(param_1 + 0x18) != 0) {
      __dla__FPv(*(undefined4 *)(param_1 + 0x18));
    }
    if (*(int *)(param_1 + 0x1c) != 0) {
      __dla__FPv(*(undefined4 *)(param_1 + 0x1c));
    }
    if (*(int *)(param_1 + 0xa4) != 0) {
      __dla__FPv(*(undefined4 *)(param_1 + 0xa4));
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
 * JP: 0x004fc280  Destruct__7HitInfoFv
 * C++: HitInfo::Destruct()
 * size: 0x5c bytes
 * --------------------------------------------------------------------------- */
void Destruct__7HitInfoFv(int param_1)

{
  BtlEffRelease__7CBattleFiP6BtlEff(uGpffff86b4,0xffffffffffffffff,param_1);
  Dispose__7CPollerFP7CPolObj(iGpffff858c + 0x48,param_1);
  (**(code **)(*(int *)(param_1 + 0x34) + 0xc))();
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x004fc2e0  Polling__7HitInfoFv
 * C++: HitInfo::Polling()
 * size: 0x690 bytes
 * --------------------------------------------------------------------------- */
undefined4 Polling__7HitInfoFv(int param_1)

{
  float fVar1;
  float fStack_18;
  float fStack_14;
  
  fStack_14 = *(float *)(iGpffff86b4 + 0x38);
  if ((*(byte *)(iGpffff86b4 + 0x24) & 1) != 0) {
    fStack_14 = 0.0;
  }
  if (*(float *)(param_1 + 0x70) != 0.0) {
    *(float *)(param_1 + 0x70) = *(float *)(param_1 + 0x70) - fStack_14;
    if (0.0 < *(float *)(param_1 + 0x70)) {
      return 0;
    }
    *(undefined4 *)(param_1 + 0x70) = 0;
  }
  switch(*(undefined4 *)(param_1 + 0x5c)) {
  case 0:
  case 1:
    *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + fStack_14;
    fStack_18 = *(float *)(param_1 + 0x6c) * 4.1887903;
    if (1.5707964 <= fStack_18) {
      fStack_18 = 1.5707964;
    }
    fVar1 = (float)sinf(fStack_18);
    *(float *)(param_1 + 0x90) = (*(float *)(param_1 + 0x94) + -64.0) * fVar1;
    if (0.5 <= *(float *)(param_1 + 0x6c)) {
      BtlEffRelease__7CBattleFiP6BtlEff(iGpffff86b4,0xffffffffffffffff,param_1);
      (**(code **)(*(int *)(param_1 + 0x34) + 0xc))();
      return 1;
    }
    break;
  case 2:
  case 3:
  case 4:
    *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + fStack_14;
    *(float *)(param_1 + 0xa0) =
         *(float *)(param_1 + 0xa0) + (-*(float *)(param_1 + 0xa0) / 4.0) * fStack_14 * 30.0;
    *(float *)(param_1 + 0x90) =
         *(float *)(param_1 + 0x94) -
         (*(float *)(param_1 + 0x94) * *(float *)(param_1 + 0xa0)) / 6.2831855;
    if (0.5 <= *(float *)(param_1 + 0x6c)) {
      BtlEffRelease__7CBattleFiP6BtlEff(iGpffff86b4,0xffffffffffffffff,param_1);
      (**(code **)(*(int *)(param_1 + 0x34) + 0xc))();
      return 1;
    }
    break;
  case 5:
  case 8:
    *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + fStack_14;
    *(float *)(param_1 + 0x90) = *(float *)(param_1 + 0x94) * *(float *)(param_1 + 0x6c) * 2.0;
    if (0.5 <= *(float *)(param_1 + 0x6c)) {
      *(undefined4 *)(param_1 + 0x90) = *(undefined4 *)(param_1 + 0x94);
    }
    if (1.0 <= *(float *)(param_1 + 0x6c)) {
      BtlEffRelease__7CBattleFiP6BtlEff(iGpffff86b4,0xffffffffffffffff,param_1);
      (**(code **)(*(int *)(param_1 + 0x34) + 0xc))();
      return 1;
    }
    break;
  case 6:
  case 7:
    *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + fStack_14;
    fStack_18 = *(float *)(param_1 + 0x6c) * 4.1887903;
    if (1.5707964 <= fStack_18) {
      fStack_18 = 1.5707964;
    }
    fVar1 = (float)sinf(fStack_18);
    *(float *)(param_1 + 0x90) = (*(float *)(param_1 + 0x94) + -64.0) * fVar1;
    *(float *)(param_1 + 0xa0) =
         *(float *)(param_1 + 0xa0) + (-*(float *)(param_1 + 0xa0) / 4.0) * fStack_14 * 30.0;
    if (1.0 <= *(float *)(param_1 + 0x6c)) {
      BtlEffRelease__7CBattleFiP6BtlEff(iGpffff86b4,0xffffffffffffffff,param_1);
      (**(code **)(*(int *)(param_1 + 0x34) + 0xc))();
      return 1;
    }
    break;
  case 9:
    if (*(int *)(param_1 + 0x60) == 1) {
      *(float *)(param_1 + 0x9c) =
           *(float *)(param_1 + 0x9c) - *(float *)(*(int *)(iGpffff86b4 + 0x4324) + 0x24) * 2.0;
      if (*(float *)(param_1 + 0x9c) <= 0.0) {
        BtlEffRelease__7CBattleFiP6BtlEff(iGpffff86b4,0xffffffffffffffff,param_1);
        (**(code **)(*(int *)(param_1 + 0x34) + 0xc))();
        return 1;
      }
    }
    else if (*(int *)(param_1 + 0x60) == 0) {
      *(float *)(param_1 + 0x6c) =
           *(float *)(param_1 + 0x6c) + *(float *)(*(int *)(iGpffff86b4 + 0x4324) + 0x24);
      if (1.5 <= *(float *)(param_1 + 0x6c)) {
        *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) - 1.5;
      }
      if (*(float *)(param_1 + 0x6c) <= 0.5) {
        *(float *)(param_1 + 0x9c) = *(float *)(param_1 + 0x6c) * 2.0;
      }
      else if (*(float *)(param_1 + 0x6c) <= 1.0) {
        *(undefined4 *)(param_1 + 0x9c) = 0x3f800000;
      }
      else {
        *(float *)(param_1 + 0x9c) = (1.5 - *(float *)(param_1 + 0x6c)) * 2.0;
      }
      if (*(char *)(iGpffff86b4 + 0x45c2) == '\0') {
        *(undefined4 *)(param_1 + 0x60) = 1;
      }
    }
  }
  return 0;
}

/* ---------------------------------------------------------------------------
 * JP: 0x004fc970  MakePacket__7HitInfoFv
 * C++: HitInfo::MakePacket()
 * size: 0x3ff4 bytes
 * --------------------------------------------------------------------------- */
void MakePacket__7HitInfoFv(int param_1)

{
  bool bVar1;
  char cVar2;
  uint uVar3;
  undefined4 *puVar4;
  bool bVar5;
  float in_zero_lo;
  float in_zero_hi;
  float in_zero_udw;
  float in_register_0000000c;
  undefined4 uVar6;
  ulong uVar7;
  long lVar8;
  float *pfVar9;
  uint uVar10;
  undefined8 in_v1_udw;
  undefined1 auVar11 [16];
  undefined1 auVar12 [16];
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  uint auStack_aa0 [128];
  float afStack_8a0 [516];
  int iStack_90;
  int iStack_8c;
  int iStack_88;
  undefined4 auStack_80 [16];
  undefined4 auStack_40 [16];
  
  GetViewScreenMatrix__9GsxCameraFv(auStack_40,uGpffff8598);
  for (iVar16 = 0; iVar16 < 4; iVar16 = iVar16 + 1) {
    auStack_80[iVar16 * 4] = auStack_40[iVar16 * 4];
    auStack_80[iVar16 * 4 + 1] = auStack_40[iVar16 * 4 + 1];
    auStack_80[iVar16 * 4 + 2] = auStack_40[iVar16 * 4 + 2];
    auStack_80[iVar16 * 4 + 3] = auStack_40[iVar16 * 4 + 3];
  }
  sceVu0RotTransPersN(&iStack_90,auStack_80,param_1 + 0x80,1,0);
  if (iStack_90 < 0) {
    iStack_90 = iStack_90 + 0xf;
  }
  afStack_8a0[0x200] = (float)((iStack_90 >> 4) + -0x700);
  if (iStack_8c < 0) {
    iStack_8c = iStack_8c + 0xf;
  }
  afStack_8a0[0x201] = (float)((iStack_8c >> 4) + -0x720) + *(float *)(param_1 + 0x90);
  pfVar9 = afStack_8a0;
  do {
    *pfVar9 = in_zero_lo;
    pfVar9[1] = in_zero_hi;
    pfVar9[2] = in_zero_udw;
    pfVar9[3] = in_register_0000000c;
    pfVar9 = pfVar9 + 4;
  } while (pfVar9 != afStack_8a0 + 0x200);
  iVar13 = 0;
  iVar16 = 0;
  fVar17 = (float)cosf(*(undefined4 *)(param_1 + 0xa0));
  switch(*(undefined4 *)(param_1 + 0x5c)) {
  case 0:
    for (uVar10 = 1000000000; uVar10 != 0; uVar10 = (int)uVar10 / 10 + ((int)uVar10 >> 0x1f)) {
      if ((int)uVar10 <= *(int *)(param_1 + 0xa8)) {
        if (uVar10 == 0) {
          trap(7);
        }
        iVar15 = (*(int *)(param_1 + 0xa8) / (int)uVar10) % 10;
        auStack_aa0[iVar13 * 4] = (uint)*(ushort *)((iVar15 + 0x34) * 8 + 0x651b90);
        auStack_aa0[iVar13 * 4 + 1] = (uint)*(ushort *)((iVar15 + 0x34) * 8 + 0x651b92);
        auStack_aa0[iVar13 * 4 + 2] = (uint)*(ushort *)((iVar15 + 0x34) * 8 + 0x651b94);
        auStack_aa0[iVar13 * 4 + 3] = *(ushort *)((iVar15 + 0x34) * 8 + 0x651b96) - 5;
        iVar16 = iVar16 + (auStack_aa0[iVar13 * 4 + 2] - auStack_aa0[iVar13 * 4]) + -1;
        if (1 < uVar10) {
          iVar16 = iVar16 + -2;
        }
        iVar13 = iVar13 + 1;
      }
    }
    fVar19 = afStack_8a0[0x200] - ((float)iVar16 * *(float *)(param_1 + 0x98)) / 2.0;
    fVar17 = afStack_8a0[0x201] -
             (*(float *)(param_1 + 0x98) * (float)(int)(auStack_aa0[3] - auStack_aa0[1])) / 2.0;
    for (iVar16 = 0; iVar16 < iVar13; iVar16 = iVar16 + 1) {
      afStack_8a0[iVar16 * 0x10] = fVar19;
      afStack_8a0[iVar16 * 0x10 + 1] = fVar17;
      afStack_8a0[iVar16 * 0x10 + 2] = 0.0;
      afStack_8a0[iVar16 * 0x10 + 3] = 1.0;
      uVar10 = auStack_aa0[iVar16 * 4 + 3];
      uVar3 = auStack_aa0[iVar16 * 4 + 1];
      fVar18 = *(float *)(param_1 + 0x98);
      afStack_8a0[iVar16 * 0x10 + 4] = fVar19;
      afStack_8a0[iVar16 * 0x10 + 5] = fVar17 + fVar18 * (float)(int)(uVar10 - uVar3);
      afStack_8a0[iVar16 * 0x10 + 6] = 0.0;
      afStack_8a0[iVar16 * 0x10 + 7] = 1.0;
      afStack_8a0[iVar16 * 0x10 + 8] =
           fVar19 + *(float *)(param_1 + 0x98) *
                    (float)(int)(auStack_aa0[iVar16 * 4 + 2] - auStack_aa0[iVar16 * 4]);
      afStack_8a0[iVar16 * 0x10 + 9] = fVar17;
      afStack_8a0[iVar16 * 0x10 + 10] = 0.0;
      afStack_8a0[iVar16 * 0x10 + 0xb] = 1.0;
      uVar10 = auStack_aa0[iVar16 * 4 + 3];
      uVar3 = auStack_aa0[iVar16 * 4 + 1];
      fVar18 = *(float *)(param_1 + 0x98);
      afStack_8a0[iVar16 * 0x10 + 0xc] =
           fVar19 + *(float *)(param_1 + 0x98) *
                    (float)(int)(auStack_aa0[iVar16 * 4 + 2] - auStack_aa0[iVar16 * 4]);
      afStack_8a0[iVar16 * 0x10 + 0xd] = fVar17 + fVar18 * (float)(int)(uVar10 - uVar3);
      afStack_8a0[iVar16 * 0x10 + 0xe] = 0.0;
      afStack_8a0[iVar16 * 0x10 + 0xf] = 1.0;
      fVar19 = fVar19 + *(float *)(param_1 + 0x98) *
                        (float)(int)((auStack_aa0[iVar16 * 4 + 2] - auStack_aa0[iVar16 * 4]) + -3);
    }
    break;
  case 1:
    for (iVar15 = 0; *(char *)(*(int *)(param_1 + 0xa4) + iVar15) != '\0'; iVar15 = iVar15 + 1) {
      cVar2 = *(char *)(*(int *)(param_1 + 0xa4) + iVar15);
      if (cVar2 == ' ') {
        auStack_aa0[iVar13 * 4] = 0xffffffff;
        auStack_aa0[iVar13 * 4 + 1] = 0xffffffff;
        auStack_aa0[iVar13 * 4 + 2] = 0xffffffff;
        auStack_aa0[iVar13 * 4 + 3] = 0xffffffff;
      }
      else {
        iVar14 = (int)cVar2;
        if ((cVar2 < 'A') || ('Z' < cVar2)) {
          if ((cVar2 < 'a') || ('z' < cVar2)) {
            if ((cVar2 < '0') || ('9' < cVar2)) {
              if (cVar2 == '!') {
                auStack_aa0[iVar13 * 4] = (uint)uRam00651d80;
                auStack_aa0[iVar13 * 4 + 1] = (uint)uRam00651d82;
                auStack_aa0[iVar13 * 4 + 2] = (uint)uRam00651d84;
                auStack_aa0[iVar13 * 4 + 3] = uRam00651d86 - 5;
              }
              else if (cVar2 == '?') {
                auStack_aa0[iVar13 * 4] = (uint)uRam00651d88;
                auStack_aa0[iVar13 * 4 + 1] = (uint)uRam00651d8a;
                auStack_aa0[iVar13 * 4 + 2] = (uint)uRam00651d8c;
                auStack_aa0[iVar13 * 4 + 3] = uRam00651d8e - 5;
              }
              else if (cVar2 == '+') {
                auStack_aa0[iVar13 * 4] = (uint)uRam00651d90;
                auStack_aa0[iVar13 * 4 + 1] = (uint)uRam00651d92;
                auStack_aa0[iVar13 * 4 + 2] = (uint)uRam00651d94;
                auStack_aa0[iVar13 * 4 + 3] = uRam00651d96 - 5;
              }
              else if (cVar2 == '-') {
                auStack_aa0[iVar13 * 4] = (uint)uRam00651d98;
                auStack_aa0[iVar13 * 4 + 1] = (uint)uRam00651d9a;
                auStack_aa0[iVar13 * 4 + 2] = (uint)uRam00651d9c;
                auStack_aa0[iVar13 * 4 + 3] = uRam00651d9e - 5;
              }
              else if (cVar2 == '*') {
                auStack_aa0[iVar13 * 4] = (uint)uRam00651da0;
                auStack_aa0[iVar13 * 4 + 1] = (uint)uRam00651da2;
                auStack_aa0[iVar13 * 4 + 2] = (uint)uRam00651da4;
                auStack_aa0[iVar13 * 4 + 3] = uRam00651da6 - 5;
              }
              else if (cVar2 == '%') {
                auStack_aa0[iVar13 * 4] = (uint)uRam00651da8;
                auStack_aa0[iVar13 * 4 + 1] = (uint)uRam00651daa;
                auStack_aa0[iVar13 * 4 + 2] = (uint)uRam00651dac;
                auStack_aa0[iVar13 * 4 + 3] = uRam00651dae - 5;
              }
              else if (cVar2 == '/') {
                auStack_aa0[iVar13 * 4] = (uint)uRam00651db0;
                auStack_aa0[iVar13 * 4 + 1] = (uint)uRam00651db2;
                auStack_aa0[iVar13 * 4 + 2] = (uint)uRam00651db4;
                auStack_aa0[iVar13 * 4 + 3] = uRam00651db6 - 5;
              }
              else if (cVar2 == '\'') {
                auStack_aa0[iVar13 * 4] = (uint)uRam00651dc0;
                auStack_aa0[iVar13 * 4 + 1] = (uint)uRam00651dc2;
                auStack_aa0[iVar13 * 4 + 2] = (uint)uRam00651dc4;
                auStack_aa0[iVar13 * 4 + 3] = uRam00651dc6 - 5;
              }
              else if (cVar2 == '.') {
                auStack_aa0[iVar13 * 4] = (uint)uRam00651dc8;
                auStack_aa0[iVar13 * 4 + 1] = (uint)uRam00651dca;
                auStack_aa0[iVar13 * 4 + 2] = (uint)uRam00651dcc;
                auStack_aa0[iVar13 * 4 + 3] = uRam00651dce - 5;
              }
              else if (cVar2 == ',') {
                auStack_aa0[iVar13 * 4] = (uint)uRam00651dd0;
                auStack_aa0[iVar13 * 4 + 1] = (uint)uRam00651dd2;
                auStack_aa0[iVar13 * 4 + 2] = (uint)uRam00651dd4;
                auStack_aa0[iVar13 * 4 + 3] = uRam00651dd6 - 5;
              }
            }
            else {
              auStack_aa0[iVar13 * 4] = (uint)*(ushort *)((iVar14 + 4) * 8 + 0x651b90);
              auStack_aa0[iVar13 * 4 + 1] = (uint)*(ushort *)((iVar14 + 4) * 8 + 0x651b92);
              auStack_aa0[iVar13 * 4 + 2] = (uint)*(ushort *)((iVar14 + 4) * 8 + 0x651b94);
              auStack_aa0[iVar13 * 4 + 3] = *(ushort *)((iVar14 + 4) * 8 + 0x651b96) - 5;
            }
          }
          else {
            auStack_aa0[iVar13 * 4] = (uint)*(ushort *)((iVar14 + -0x47) * 8 + 0x651b90);
            auStack_aa0[iVar13 * 4 + 1] = (uint)*(ushort *)((iVar14 + -0x47) * 8 + 0x651b92);
            auStack_aa0[iVar13 * 4 + 2] = (uint)*(ushort *)((iVar14 + -0x47) * 8 + 0x651b94);
            auStack_aa0[iVar13 * 4 + 3] = *(ushort *)((iVar14 + -0x47) * 8 + 0x651b96) - 5;
          }
        }
        else {
          auStack_aa0[iVar13 * 4] = (uint)*(ushort *)((cVar2 + -0x41) * 8 + 0x651b90);
          auStack_aa0[iVar13 * 4 + 1] = (uint)*(ushort *)((cVar2 + -0x41) * 8 + 0x651b92);
          auStack_aa0[iVar13 * 4 + 2] = (uint)*(ushort *)((iVar14 + -0x41) * 8 + 0x651b94);
          auStack_aa0[iVar13 * 4 + 3] = *(ushort *)((iVar14 + -0x41) * 8 + 0x651b96) - 5;
        }
      }
      if (auStack_aa0[iVar13 * 4] == 0xffffffff) {
        iVar16 = iVar16 + 0xd;
      }
      else {
        iVar16 = iVar16 + (auStack_aa0[iVar13 * 4 + 2] - auStack_aa0[iVar13 * 4]) + -3;
      }
      iVar13 = iVar13 + 1;
    }
    fVar19 = afStack_8a0[0x200] - ((float)(iVar16 + 2) * *(float *)(param_1 + 0x98)) / 2.0;
    fVar17 = afStack_8a0[0x201] -
             (*(float *)(param_1 + 0x98) * (float)(int)(auStack_aa0[3] - auStack_aa0[1])) / 2.0;
    for (iVar16 = 0; iVar16 < iVar13; iVar16 = iVar16 + 1) {
      if (auStack_aa0[iVar16 * 4] == 0xffffffff) {
        afStack_8a0[iVar16 * 0x10] = fVar19;
        afStack_8a0[iVar16 * 0x10 + 1] = fVar17;
        afStack_8a0[iVar16 * 0x10 + 2] = 0.0;
        afStack_8a0[iVar16 * 0x10 + 3] = 1.0;
        afStack_8a0[iVar16 * 0x10 + 4] = fVar19;
        afStack_8a0[iVar16 * 0x10 + 5] = fVar17;
        afStack_8a0[iVar16 * 0x10 + 6] = 0.0;
        afStack_8a0[iVar16 * 0x10 + 7] = 1.0;
        afStack_8a0[iVar16 * 0x10 + 8] = fVar19;
        afStack_8a0[iVar16 * 0x10 + 9] = fVar17;
        afStack_8a0[iVar16 * 0x10 + 10] = 0.0;
        afStack_8a0[iVar16 * 0x10 + 0xb] = 1.0;
        afStack_8a0[iVar16 * 0x10 + 0xc] = fVar19;
        afStack_8a0[iVar16 * 0x10 + 0xd] = fVar17;
        afStack_8a0[iVar16 * 0x10 + 0xe] = 0.0;
        afStack_8a0[iVar16 * 0x10 + 0xf] = 1.0;
        fVar18 = *(float *)(param_1 + 0x98) * 13.0;
      }
      else {
        afStack_8a0[iVar16 * 0x10] = fVar19;
        afStack_8a0[iVar16 * 0x10 + 1] = fVar17;
        afStack_8a0[iVar16 * 0x10 + 2] = 0.0;
        afStack_8a0[iVar16 * 0x10 + 3] = 1.0;
        uVar10 = auStack_aa0[iVar16 * 4 + 3];
        uVar3 = auStack_aa0[iVar16 * 4 + 1];
        fVar18 = *(float *)(param_1 + 0x98);
        afStack_8a0[iVar16 * 0x10 + 4] = fVar19;
        afStack_8a0[iVar16 * 0x10 + 5] = fVar17 + fVar18 * (float)(int)(uVar10 - uVar3);
        afStack_8a0[iVar16 * 0x10 + 6] = 0.0;
        afStack_8a0[iVar16 * 0x10 + 7] = 1.0;
        afStack_8a0[iVar16 * 0x10 + 8] =
             fVar19 + *(float *)(param_1 + 0x98) *
                      (float)(int)(auStack_aa0[iVar16 * 4 + 2] - auStack_aa0[iVar16 * 4]);
        afStack_8a0[iVar16 * 0x10 + 9] = fVar17;
        afStack_8a0[iVar16 * 0x10 + 10] = 0.0;
        afStack_8a0[iVar16 * 0x10 + 0xb] = 1.0;
        uVar10 = auStack_aa0[iVar16 * 4 + 3];
        uVar3 = auStack_aa0[iVar16 * 4 + 1];
        fVar18 = *(float *)(param_1 + 0x98);
        afStack_8a0[iVar16 * 0x10 + 0xc] =
             fVar19 + *(float *)(param_1 + 0x98) *
                      (float)(int)(auStack_aa0[iVar16 * 4 + 2] - auStack_aa0[iVar16 * 4]);
        afStack_8a0[iVar16 * 0x10 + 0xd] = fVar17 + fVar18 * (float)(int)(uVar10 - uVar3);
        afStack_8a0[iVar16 * 0x10 + 0xe] = 0.0;
        afStack_8a0[iVar16 * 0x10 + 0xf] = 1.0;
        fVar18 = *(float *)(param_1 + 0x98) *
                 (float)(int)((auStack_aa0[iVar16 * 4 + 2] - auStack_aa0[iVar16 * 4]) + -3);
      }
      fVar19 = fVar19 + fVar18;
    }
    break;
  case 2:
  case 3:
  case 4:
  case 6:
  case 7:
    for (iVar15 = 0; *(char *)(*(int *)(param_1 + 0xa4) + iVar15) != '\0'; iVar15 = iVar15 + 1) {
      cVar2 = *(char *)(*(int *)(param_1 + 0xa4) + iVar15);
      if (cVar2 == ' ') {
        auStack_aa0[iVar13 * 4] = 0xffffffff;
        auStack_aa0[iVar13 * 4 + 1] = 0xffffffff;
        auStack_aa0[iVar13 * 4 + 2] = 0xffffffff;
        auStack_aa0[iVar13 * 4 + 3] = 0xffffffff;
      }
      else {
        iVar14 = (int)cVar2;
        if ((cVar2 < 'A') || ('Z' < cVar2)) {
          if ((cVar2 < 'a') || ('z' < cVar2)) {
            if ((cVar2 < '0') || ('9' < cVar2)) {
              if (cVar2 == '!') {
                auStack_aa0[iVar13 * 4] = (uint)uRam00651d80;
                auStack_aa0[iVar13 * 4 + 1] = (uint)uRam00651d82;
                auStack_aa0[iVar13 * 4 + 2] = (uint)uRam00651d84;
                auStack_aa0[iVar13 * 4 + 3] = (uint)uRam00651d86;
              }
              else if (cVar2 == '?') {
                auStack_aa0[iVar13 * 4] = (uint)uRam00651d88;
                auStack_aa0[iVar13 * 4 + 1] = (uint)uRam00651d8a;
                auStack_aa0[iVar13 * 4 + 2] = (uint)uRam00651d8c;
                auStack_aa0[iVar13 * 4 + 3] = (uint)uRam00651d8e;
              }
              else if (cVar2 == '+') {
                auStack_aa0[iVar13 * 4] = (uint)uRam00651d90;
                auStack_aa0[iVar13 * 4 + 1] = (uint)uRam00651d92;
                auStack_aa0[iVar13 * 4 + 2] = (uint)uRam00651d94;
                auStack_aa0[iVar13 * 4 + 3] = (uint)uRam00651d96;
              }
              else if (cVar2 == '-') {
                auStack_aa0[iVar13 * 4] = (uint)uRam00651d98;
                auStack_aa0[iVar13 * 4 + 1] = (uint)uRam00651d9a;
                auStack_aa0[iVar13 * 4 + 2] = (uint)uRam00651d9c;
                auStack_aa0[iVar13 * 4 + 3] = (uint)uRam00651d9e;
              }
              else if (cVar2 == '*') {
                auStack_aa0[iVar13 * 4] = (uint)uRam00651da0;
                auStack_aa0[iVar13 * 4 + 1] = (uint)uRam00651da2;
                auStack_aa0[iVar13 * 4 + 2] = (uint)uRam00651da4;
                auStack_aa0[iVar13 * 4 + 3] = (uint)uRam00651da6;
              }
              else if (cVar2 == '%') {
                auStack_aa0[iVar13 * 4] = (uint)uRam00651da8;
                auStack_aa0[iVar13 * 4 + 1] = (uint)uRam00651daa;
                auStack_aa0[iVar13 * 4 + 2] = (uint)uRam00651dac;
                auStack_aa0[iVar13 * 4 + 3] = (uint)uRam00651dae;
              }
              else if (cVar2 == '/') {
                auStack_aa0[iVar13 * 4] = (uint)uRam00651db0;
                auStack_aa0[iVar13 * 4 + 1] = (uint)uRam00651db2;
                auStack_aa0[iVar13 * 4 + 2] = (uint)uRam00651db4;
                auStack_aa0[iVar13 * 4 + 3] = (uint)uRam00651db6;
              }
              else if (cVar2 == '\'') {
                auStack_aa0[iVar13 * 4] = (uint)uRam00651dc0;
                auStack_aa0[iVar13 * 4 + 1] = (uint)uRam00651dc2;
                auStack_aa0[iVar13 * 4 + 2] = (uint)uRam00651dc4;
                auStack_aa0[iVar13 * 4 + 3] = (uint)uRam00651dc6;
              }
              else if (cVar2 == '.') {
                auStack_aa0[iVar13 * 4] = (uint)uRam00651dc8;
                auStack_aa0[iVar13 * 4 + 1] = (uint)uRam00651dca;
                auStack_aa0[iVar13 * 4 + 2] = (uint)uRam00651dcc;
                auStack_aa0[iVar13 * 4 + 3] = (uint)uRam00651dce;
              }
              else if (cVar2 == ',') {
                auStack_aa0[iVar13 * 4] = (uint)uRam00651dd0;
                auStack_aa0[iVar13 * 4 + 1] = (uint)uRam00651dd2;
                auStack_aa0[iVar13 * 4 + 2] = (uint)uRam00651dd4;
                auStack_aa0[iVar13 * 4 + 3] = (uint)uRam00651dd6;
              }
            }
            else {
              auStack_aa0[iVar13 * 4] = (uint)*(ushort *)((iVar14 + 4) * 8 + 0x651b90);
              auStack_aa0[iVar13 * 4 + 1] = (uint)*(ushort *)((iVar14 + 4) * 8 + 0x651b92);
              auStack_aa0[iVar13 * 4 + 2] = (uint)*(ushort *)((iVar14 + 4) * 8 + 0x651b94);
              auStack_aa0[iVar13 * 4 + 3] = (uint)*(ushort *)((iVar14 + 4) * 8 + 0x651b96);
            }
          }
          else {
            auStack_aa0[iVar13 * 4] = (uint)*(ushort *)((iVar14 + -0x47) * 8 + 0x651b90);
            auStack_aa0[iVar13 * 4 + 1] = (uint)*(ushort *)((iVar14 + -0x47) * 8 + 0x651b92);
            auStack_aa0[iVar13 * 4 + 2] = (uint)*(ushort *)((iVar14 + -0x47) * 8 + 0x651b94);
            auStack_aa0[iVar13 * 4 + 3] = (uint)*(ushort *)((iVar14 + -0x47) * 8 + 0x651b96);
          }
        }
        else {
          auStack_aa0[iVar13 * 4] = (uint)*(ushort *)((cVar2 + -0x41) * 8 + 0x651b90);
          auStack_aa0[iVar13 * 4 + 1] = (uint)*(ushort *)((cVar2 + -0x41) * 8 + 0x651b92);
          auStack_aa0[iVar13 * 4 + 2] = (uint)*(ushort *)((iVar14 + -0x41) * 8 + 0x651b94);
          auStack_aa0[iVar13 * 4 + 3] = (uint)*(ushort *)((iVar14 + -0x41) * 8 + 0x651b96);
        }
      }
      if (auStack_aa0[iVar13 * 4] == 0xffffffff) {
        iVar16 = iVar16 + 0xd;
      }
      else {
        iVar16 = iVar16 + (auStack_aa0[iVar13 * 4 + 2] - auStack_aa0[iVar13 * 4]) + -3;
      }
      iVar13 = iVar13 + 1;
    }
    fVar18 = afStack_8a0[0x200] -
             fVar17 * (((float)(iVar16 + 2) * *(float *)(param_1 + 0x98)) / 2.0);
    fVar19 = afStack_8a0[0x201] -
             (*(float *)(param_1 + 0x98) * (float)(int)(auStack_aa0[3] - auStack_aa0[1])) / 2.0;
    for (iVar16 = 0; iVar16 < iVar13; iVar16 = iVar16 + 1) {
      if (auStack_aa0[iVar16 * 4] == 0xffffffff) {
        afStack_8a0[iVar16 * 0x10] = fVar18;
        afStack_8a0[iVar16 * 0x10 + 1] = fVar19;
        afStack_8a0[iVar16 * 0x10 + 2] = 0.0;
        afStack_8a0[iVar16 * 0x10 + 3] = 1.0;
        afStack_8a0[iVar16 * 0x10 + 4] = fVar18;
        afStack_8a0[iVar16 * 0x10 + 5] = fVar19;
        afStack_8a0[iVar16 * 0x10 + 6] = 0.0;
        afStack_8a0[iVar16 * 0x10 + 7] = 1.0;
        afStack_8a0[iVar16 * 0x10 + 8] = fVar18;
        afStack_8a0[iVar16 * 0x10 + 9] = fVar19;
        afStack_8a0[iVar16 * 0x10 + 10] = 0.0;
        afStack_8a0[iVar16 * 0x10 + 0xb] = 1.0;
        afStack_8a0[iVar16 * 0x10 + 0xc] = fVar18;
        afStack_8a0[iVar16 * 0x10 + 0xd] = fVar19;
        afStack_8a0[iVar16 * 0x10 + 0xe] = 0.0;
        afStack_8a0[iVar16 * 0x10 + 0xf] = 1.0;
        fVar20 = *(float *)(param_1 + 0x98) * 13.0;
      }
      else {
        afStack_8a0[iVar16 * 0x10] = fVar18;
        afStack_8a0[iVar16 * 0x10 + 1] = fVar19;
        afStack_8a0[iVar16 * 0x10 + 2] = 0.0;
        afStack_8a0[iVar16 * 0x10 + 3] = 1.0;
        uVar10 = auStack_aa0[iVar16 * 4 + 3];
        uVar3 = auStack_aa0[iVar16 * 4 + 1];
        fVar20 = *(float *)(param_1 + 0x98);
        afStack_8a0[iVar16 * 0x10 + 4] = fVar18;
        afStack_8a0[iVar16 * 0x10 + 5] = fVar19 + fVar20 * (float)(int)(uVar10 - uVar3);
        afStack_8a0[iVar16 * 0x10 + 6] = 0.0;
        afStack_8a0[iVar16 * 0x10 + 7] = 1.0;
        afStack_8a0[iVar16 * 0x10 + 8] =
             fVar18 + fVar17 * *(float *)(param_1 + 0x98) *
                               (float)(int)(auStack_aa0[iVar16 * 4 + 2] - auStack_aa0[iVar16 * 4]);
        afStack_8a0[iVar16 * 0x10 + 9] = fVar19;
        afStack_8a0[iVar16 * 0x10 + 10] = 0.0;
        afStack_8a0[iVar16 * 0x10 + 0xb] = 1.0;
        uVar10 = auStack_aa0[iVar16 * 4 + 3];
        uVar3 = auStack_aa0[iVar16 * 4 + 1];
        fVar20 = *(float *)(param_1 + 0x98);
        afStack_8a0[iVar16 * 0x10 + 0xc] =
             fVar18 + fVar17 * *(float *)(param_1 + 0x98) *
                               (float)(int)(auStack_aa0[iVar16 * 4 + 2] - auStack_aa0[iVar16 * 4]);
        afStack_8a0[iVar16 * 0x10 + 0xd] = fVar19 + fVar20 * (float)(int)(uVar10 - uVar3);
        afStack_8a0[iVar16 * 0x10 + 0xe] = 0.0;
        afStack_8a0[iVar16 * 0x10 + 0xf] = 1.0;
        fVar20 = *(float *)(param_1 + 0x98) *
                 (float)(int)((auStack_aa0[iVar16 * 4 + 2] - auStack_aa0[iVar16 * 4]) + -3);
      }
      fVar18 = fVar18 + fVar17 * fVar20;
    }
    break;
  case 5:
  case 8:
    for (iVar15 = 0; *(char *)(*(int *)(param_1 + 0xa4) + iVar15) != '\0'; iVar15 = iVar15 + 1) {
      cVar2 = *(char *)(*(int *)(param_1 + 0xa4) + iVar15);
      if (cVar2 == ' ') {
        auStack_aa0[iVar13 * 4] = 0xffffffff;
        auStack_aa0[iVar13 * 4 + 1] = 0xffffffff;
        auStack_aa0[iVar13 * 4 + 2] = 0xffffffff;
        auStack_aa0[iVar13 * 4 + 3] = 0xffffffff;
      }
      else {
        iVar14 = (int)cVar2;
        if ((cVar2 < 'A') || ('Z' < cVar2)) {
          if ((cVar2 < 'a') || ('z' < cVar2)) {
            if ((cVar2 < '0') || ('9' < cVar2)) {
              if (cVar2 == '!') {
                auStack_aa0[iVar13 * 4] = (uint)uRam00651d80;
                auStack_aa0[iVar13 * 4 + 1] = (uint)uRam00651d82;
                auStack_aa0[iVar13 * 4 + 2] = (uint)uRam00651d84;
                auStack_aa0[iVar13 * 4 + 3] = (uint)uRam00651d86;
              }
              else if (cVar2 == '?') {
                auStack_aa0[iVar13 * 4] = (uint)uRam00651d88;
                auStack_aa0[iVar13 * 4 + 1] = (uint)uRam00651d8a;
                auStack_aa0[iVar13 * 4 + 2] = (uint)uRam00651d8c;
                auStack_aa0[iVar13 * 4 + 3] = (uint)uRam00651d8e;
              }
              else if (cVar2 == '+') {
                auStack_aa0[iVar13 * 4] = (uint)uRam00651d90;
                auStack_aa0[iVar13 * 4 + 1] = (uint)uRam00651d92;
                auStack_aa0[iVar13 * 4 + 2] = (uint)uRam00651d94;
                auStack_aa0[iVar13 * 4 + 3] = (uint)uRam00651d96;
              }
              else if (cVar2 == '-') {
                auStack_aa0[iVar13 * 4] = (uint)uRam00651d98;
                auStack_aa0[iVar13 * 4 + 1] = (uint)uRam00651d9a;
                auStack_aa0[iVar13 * 4 + 2] = (uint)uRam00651d9c;
                auStack_aa0[iVar13 * 4 + 3] = (uint)uRam00651d9e;
              }
              else if (cVar2 == '*') {
                auStack_aa0[iVar13 * 4] = (uint)uRam00651da0;
                auStack_aa0[iVar13 * 4 + 1] = (uint)uRam00651da2;
                auStack_aa0[iVar13 * 4 + 2] = (uint)uRam00651da4;
                auStack_aa0[iVar13 * 4 + 3] = (uint)uRam00651da6;
              }
              else if (cVar2 == '%') {
                auStack_aa0[iVar13 * 4] = (uint)uRam00651da8;
                auStack_aa0[iVar13 * 4 + 1] = (uint)uRam00651daa;
                auStack_aa0[iVar13 * 4 + 2] = (uint)uRam00651dac;
                auStack_aa0[iVar13 * 4 + 3] = (uint)uRam00651dae;
              }
              else if (cVar2 == '/') {
                auStack_aa0[iVar13 * 4] = (uint)uRam00651db0;
                auStack_aa0[iVar13 * 4 + 1] = (uint)uRam00651db2;
                auStack_aa0[iVar13 * 4 + 2] = (uint)uRam00651db4;
                auStack_aa0[iVar13 * 4 + 3] = (uint)uRam00651db6;
              }
              else if (cVar2 == '\'') {
                auStack_aa0[iVar13 * 4] = (uint)uRam00651dc0;
                auStack_aa0[iVar13 * 4 + 1] = (uint)uRam00651dc2;
                auStack_aa0[iVar13 * 4 + 2] = (uint)uRam00651dc4;
                auStack_aa0[iVar13 * 4 + 3] = (uint)uRam00651dc6;
              }
              else if (cVar2 == '.') {
                auStack_aa0[iVar13 * 4] = (uint)uRam00651dc8;
                auStack_aa0[iVar13 * 4 + 1] = (uint)uRam00651dca;
                auStack_aa0[iVar13 * 4 + 2] = (uint)uRam00651dcc;
                auStack_aa0[iVar13 * 4 + 3] = (uint)uRam00651dce;
              }
              else if (cVar2 == ',') {
                auStack_aa0[iVar13 * 4] = (uint)uRam00651dd0;
                auStack_aa0[iVar13 * 4 + 1] = (uint)uRam00651dd2;
                auStack_aa0[iVar13 * 4 + 2] = (uint)uRam00651dd4;
                auStack_aa0[iVar13 * 4 + 3] = (uint)uRam00651dd6;
              }
            }
            else {
              auStack_aa0[iVar13 * 4] = (uint)*(ushort *)((iVar14 + 4) * 8 + 0x651b90);
              auStack_aa0[iVar13 * 4 + 1] = (uint)*(ushort *)((iVar14 + 4) * 8 + 0x651b92);
              auStack_aa0[iVar13 * 4 + 2] = (uint)*(ushort *)((iVar14 + 4) * 8 + 0x651b94);
              auStack_aa0[iVar13 * 4 + 3] = (uint)*(ushort *)((iVar14 + 4) * 8 + 0x651b96);
            }
          }
          else {
            auStack_aa0[iVar13 * 4] = (uint)*(ushort *)((iVar14 + -0x47) * 8 + 0x651b90);
            auStack_aa0[iVar13 * 4 + 1] = (uint)*(ushort *)((iVar14 + -0x47) * 8 + 0x651b92);
            auStack_aa0[iVar13 * 4 + 2] = (uint)*(ushort *)((iVar14 + -0x47) * 8 + 0x651b94);
            auStack_aa0[iVar13 * 4 + 3] = (uint)*(ushort *)((iVar14 + -0x47) * 8 + 0x651b96);
          }
        }
        else {
          auStack_aa0[iVar13 * 4] = (uint)*(ushort *)((cVar2 + -0x41) * 8 + 0x651b90);
          auStack_aa0[iVar13 * 4 + 1] = (uint)*(ushort *)((cVar2 + -0x41) * 8 + 0x651b92);
          auStack_aa0[iVar13 * 4 + 2] = (uint)*(ushort *)((iVar14 + -0x41) * 8 + 0x651b94);
          auStack_aa0[iVar13 * 4 + 3] = (uint)*(ushort *)((iVar14 + -0x41) * 8 + 0x651b96);
        }
      }
      if (auStack_aa0[iVar13 * 4] == 0xffffffff) {
        iVar16 = iVar16 + 0xd;
      }
      else {
        iVar16 = iVar16 + (auStack_aa0[iVar13 * 4 + 2] - auStack_aa0[iVar13 * 4]) + -3;
      }
      iVar13 = iVar13 + 1;
    }
    fVar19 = ((float)-(iVar16 + 2) * *(float *)(param_1 + 0x98)) / 2.0;
    fVar17 = *(float *)(param_1 + 0x98) * (float)(int)(auStack_aa0[1] - auStack_aa0[3]);
    for (iVar16 = 0; iVar16 < iVar13; iVar16 = iVar16 + 1) {
      if (auStack_aa0[iVar16 * 4] == 0xffffffff) {
        fVar18 = afStack_8a0[0x201] + fVar17;
        afStack_8a0[iVar16 * 0x10] = afStack_8a0[0x200] + fVar19;
        afStack_8a0[iVar16 * 0x10 + 1] = fVar18;
        afStack_8a0[iVar16 * 0x10 + 2] = 0.0;
        afStack_8a0[iVar16 * 0x10 + 3] = 1.0;
        fVar18 = afStack_8a0[0x201] + fVar17;
        afStack_8a0[iVar16 * 0x10 + 4] = afStack_8a0[0x200] + fVar19;
        afStack_8a0[iVar16 * 0x10 + 5] = fVar18;
        afStack_8a0[iVar16 * 0x10 + 6] = 0.0;
        afStack_8a0[iVar16 * 0x10 + 7] = 1.0;
        fVar18 = afStack_8a0[0x201] + fVar17;
        afStack_8a0[iVar16 * 0x10 + 8] = afStack_8a0[0x200] + fVar19;
        afStack_8a0[iVar16 * 0x10 + 9] = fVar18;
        afStack_8a0[iVar16 * 0x10 + 10] = 0.0;
        afStack_8a0[iVar16 * 0x10 + 0xb] = 1.0;
        fVar18 = afStack_8a0[0x201] + fVar17;
        afStack_8a0[iVar16 * 0x10 + 0xc] = afStack_8a0[0x200] + fVar19;
        afStack_8a0[iVar16 * 0x10 + 0xd] = fVar18;
        afStack_8a0[iVar16 * 0x10 + 0xe] = 0.0;
        afStack_8a0[iVar16 * 0x10 + 0xf] = 1.0;
        fVar18 = *(float *)(param_1 + 0x98) * 13.0;
      }
      else {
        fVar18 = *(float *)(param_1 + 0x6c) * 5.0;
        if (iVar16 + 1 < iVar13) {
          fVar18 = fVar18 - ((float)(iVar13 - (iVar16 + 1)) * 2.0) / (float)iVar13;
        }
        if (fVar18 < 0.0) {
          fVar18 = 0.0;
        }
        if (1.0 < fVar18) {
          fVar18 = 1.0;
        }
        fVar20 = afStack_8a0[0x201] + fVar17 * fVar18;
        afStack_8a0[iVar16 * 0x10] = afStack_8a0[0x200] + fVar19 * fVar18;
        afStack_8a0[iVar16 * 0x10 + 1] = fVar20;
        afStack_8a0[iVar16 * 0x10 + 2] = 0.0;
        afStack_8a0[iVar16 * 0x10 + 3] = 1.0;
        fVar20 = afStack_8a0[0x201] +
                 fVar18 * (fVar17 + *(float *)(param_1 + 0x98) *
                                    (float)(int)(auStack_aa0[iVar16 * 4 + 3] -
                                                auStack_aa0[iVar16 * 4 + 1]));
        afStack_8a0[iVar16 * 0x10 + 4] = afStack_8a0[0x200] + fVar19 * fVar18;
        afStack_8a0[iVar16 * 0x10 + 5] = fVar20;
        afStack_8a0[iVar16 * 0x10 + 6] = 0.0;
        afStack_8a0[iVar16 * 0x10 + 7] = 1.0;
        fVar20 = afStack_8a0[0x201] + fVar17 * fVar18;
        afStack_8a0[iVar16 * 0x10 + 8] =
             afStack_8a0[0x200] +
             fVar18 * (fVar19 + *(float *)(param_1 + 0x98) *
                                (float)(int)(auStack_aa0[iVar16 * 4 + 2] - auStack_aa0[iVar16 * 4]))
        ;
        afStack_8a0[iVar16 * 0x10 + 9] = fVar20;
        afStack_8a0[iVar16 * 0x10 + 10] = 0.0;
        afStack_8a0[iVar16 * 0x10 + 0xb] = 1.0;
        fVar20 = afStack_8a0[0x201] +
                 fVar18 * (fVar17 + *(float *)(param_1 + 0x98) *
                                    (float)(int)(auStack_aa0[iVar16 * 4 + 3] -
                                                auStack_aa0[iVar16 * 4 + 1]));
        afStack_8a0[iVar16 * 0x10 + 0xc] =
             afStack_8a0[0x200] +
             fVar18 * (fVar19 + *(float *)(param_1 + 0x98) *
                                (float)(int)(auStack_aa0[iVar16 * 4 + 2] - auStack_aa0[iVar16 * 4]))
        ;
        afStack_8a0[iVar16 * 0x10 + 0xd] = fVar20;
        afStack_8a0[iVar16 * 0x10 + 0xe] = 0.0;
        afStack_8a0[iVar16 * 0x10 + 0xf] = 1.0;
        fVar18 = *(float *)(param_1 + 0x98) *
                 (float)(int)((auStack_aa0[iVar16 * 4 + 2] - auStack_aa0[iVar16 * 4]) + -3);
      }
      fVar19 = fVar19 + fVar18;
    }
    break;
  case 9:
    for (iVar15 = 0; *(char *)(*(int *)(param_1 + 0xa4) + iVar15) != '\0'; iVar15 = iVar15 + 1) {
      cVar2 = *(char *)(*(int *)(param_1 + 0xa4) + iVar15);
      if (cVar2 == ' ') {
        auStack_aa0[iVar13 * 4] = 0xffffffff;
        auStack_aa0[iVar13 * 4 + 1] = 0xffffffff;
        auStack_aa0[iVar13 * 4 + 2] = 0xffffffff;
        auStack_aa0[iVar13 * 4 + 3] = 0xffffffff;
      }
      else {
        iVar14 = (int)cVar2;
        if ((cVar2 < 'A') || ('Z' < cVar2)) {
          if ((cVar2 < 'a') || ('z' < cVar2)) {
            if ((cVar2 < '0') || ('9' < cVar2)) {
              if (cVar2 == '!') {
                auStack_aa0[iVar13 * 4] = (uint)uRam00651d80;
                auStack_aa0[iVar13 * 4 + 1] = (uint)uRam00651d82;
                auStack_aa0[iVar13 * 4 + 2] = uRam00651d84 - 1;
                auStack_aa0[iVar13 * 4 + 3] = (uint)uRam00651d86;
              }
              else if (cVar2 == '?') {
                auStack_aa0[iVar13 * 4] = (uint)uRam00651d88;
                auStack_aa0[iVar13 * 4 + 1] = (uint)uRam00651d8a;
                auStack_aa0[iVar13 * 4 + 2] = uRam00651d8c - 1;
                auStack_aa0[iVar13 * 4 + 3] = (uint)uRam00651d8e;
              }
              else if (cVar2 == '+') {
                auStack_aa0[iVar13 * 4] = (uint)uRam00651d90;
                auStack_aa0[iVar13 * 4 + 1] = (uint)uRam00651d92;
                auStack_aa0[iVar13 * 4 + 2] = uRam00651d94 - 1;
                auStack_aa0[iVar13 * 4 + 3] = (uint)uRam00651d96;
              }
              else if (cVar2 == '-') {
                auStack_aa0[iVar13 * 4] = (uint)uRam00651d98;
                auStack_aa0[iVar13 * 4 + 1] = (uint)uRam00651d9a;
                auStack_aa0[iVar13 * 4 + 2] = uRam00651d9c - 1;
                auStack_aa0[iVar13 * 4 + 3] = (uint)uRam00651d9e;
              }
              else if (cVar2 == '*') {
                auStack_aa0[iVar13 * 4] = (uint)uRam00651da0;
                auStack_aa0[iVar13 * 4 + 1] = (uint)uRam00651da2;
                auStack_aa0[iVar13 * 4 + 2] = uRam00651da4 - 1;
                auStack_aa0[iVar13 * 4 + 3] = (uint)uRam00651da6;
              }
              else if (cVar2 == '%') {
                auStack_aa0[iVar13 * 4] = (uint)uRam00651da8;
                auStack_aa0[iVar13 * 4 + 1] = (uint)uRam00651daa;
                auStack_aa0[iVar13 * 4 + 2] = uRam00651dac - 1;
                auStack_aa0[iVar13 * 4 + 3] = (uint)uRam00651dae;
              }
              else if (cVar2 == '/') {
                auStack_aa0[iVar13 * 4] = (uint)uRam00651db0;
                auStack_aa0[iVar13 * 4 + 1] = (uint)uRam00651db2;
                auStack_aa0[iVar13 * 4 + 2] = uRam00651db4 - 1;
                auStack_aa0[iVar13 * 4 + 3] = (uint)uRam00651db6;
              }
              else if (cVar2 == '\'') {
                auStack_aa0[iVar13 * 4] = (uint)uRam00651dc0;
                auStack_aa0[iVar13 * 4 + 1] = (uint)uRam00651dc2;
                auStack_aa0[iVar13 * 4 + 2] = uRam00651dc4 - 1;
                auStack_aa0[iVar13 * 4 + 3] = (uint)uRam00651dc6;
              }
              else if (cVar2 == '.') {
                auStack_aa0[iVar13 * 4] = (uint)uRam00651dc8;
                auStack_aa0[iVar13 * 4 + 1] = (uint)uRam00651dca;
                auStack_aa0[iVar13 * 4 + 2] = uRam00651dcc - 1;
                auStack_aa0[iVar13 * 4 + 3] = (uint)uRam00651dce;
              }
              else if (cVar2 == ',') {
                auStack_aa0[iVar13 * 4] = (uint)uRam00651dd0;
                auStack_aa0[iVar13 * 4 + 1] = (uint)uRam00651dd2;
                auStack_aa0[iVar13 * 4 + 2] = uRam00651dd4 - 1;
                auStack_aa0[iVar13 * 4 + 3] = (uint)uRam00651dd6;
              }
            }
            else {
              auStack_aa0[iVar13 * 4] = (uint)*(ushort *)((iVar14 + 4) * 8 + 0x651b90);
              auStack_aa0[iVar13 * 4 + 1] = (uint)*(ushort *)((iVar14 + 4) * 8 + 0x651b92);
              auStack_aa0[iVar13 * 4 + 2] = *(ushort *)((iVar14 + 4) * 8 + 0x651b94) - 1;
              auStack_aa0[iVar13 * 4 + 3] = (uint)*(ushort *)((iVar14 + 4) * 8 + 0x651b96);
            }
          }
          else {
            auStack_aa0[iVar13 * 4] = (uint)*(ushort *)((iVar14 + -0x47) * 8 + 0x651b90);
            auStack_aa0[iVar13 * 4 + 1] = (uint)*(ushort *)((iVar14 + -0x47) * 8 + 0x651b92);
            auStack_aa0[iVar13 * 4 + 2] = *(ushort *)((iVar14 + -0x47) * 8 + 0x651b94) - 1;
            auStack_aa0[iVar13 * 4 + 3] = (uint)*(ushort *)((iVar14 + -0x47) * 8 + 0x651b96);
          }
        }
        else {
          auStack_aa0[iVar13 * 4] = (uint)*(ushort *)((cVar2 + -0x41) * 8 + 0x651b90);
          auStack_aa0[iVar13 * 4 + 1] = (uint)*(ushort *)((cVar2 + -0x41) * 8 + 0x651b92);
          auStack_aa0[iVar13 * 4 + 2] = *(ushort *)((iVar14 + -0x41) * 8 + 0x651b94) - 1;
          auStack_aa0[iVar13 * 4 + 3] = (uint)*(ushort *)((iVar14 + -0x41) * 8 + 0x651b96);
        }
      }
      if (auStack_aa0[iVar13 * 4] == 0xffffffff) {
        iVar16 = iVar16 + 0xe;
      }
      else {
        iVar16 = iVar16 + (auStack_aa0[iVar13 * 4 + 2] - auStack_aa0[iVar13 * 4]) + -2;
      }
      iVar13 = iVar13 + 1;
    }
    fVar19 = 256.0 - ((float)(iVar16 + 2) * *(float *)(param_1 + 0x98)) / 2.0;
    for (iVar16 = 0; iVar16 < iVar13; iVar16 = iVar16 + 1) {
      if (auStack_aa0[iVar16 * 4] == 0xffffffff) {
        afStack_8a0[iVar16 * 0x10] = fVar19;
        afStack_8a0[iVar16 * 0x10 + 1] = 96.0;
        afStack_8a0[iVar16 * 0x10 + 2] = 0.0;
        afStack_8a0[iVar16 * 0x10 + 3] = 1.0;
        afStack_8a0[iVar16 * 0x10 + 4] = fVar19;
        afStack_8a0[iVar16 * 0x10 + 5] = 96.0;
        afStack_8a0[iVar16 * 0x10 + 6] = 0.0;
        afStack_8a0[iVar16 * 0x10 + 7] = 1.0;
        afStack_8a0[iVar16 * 0x10 + 8] = fVar19;
        afStack_8a0[iVar16 * 0x10 + 9] = 96.0;
        afStack_8a0[iVar16 * 0x10 + 10] = 0.0;
        afStack_8a0[iVar16 * 0x10 + 0xb] = 1.0;
        afStack_8a0[iVar16 * 0x10 + 0xc] = fVar19;
        afStack_8a0[iVar16 * 0x10 + 0xd] = 96.0;
        afStack_8a0[iVar16 * 0x10 + 0xe] = 0.0;
        afStack_8a0[iVar16 * 0x10 + 0xf] = 1.0;
        fVar18 = *(float *)(param_1 + 0x98) * 14.0;
      }
      else {
        afStack_8a0[iVar16 * 0x10] = fVar19;
        afStack_8a0[iVar16 * 0x10 + 1] = 96.0;
        afStack_8a0[iVar16 * 0x10 + 2] = 0.0;
        afStack_8a0[iVar16 * 0x10 + 3] = 1.0;
        uVar10 = auStack_aa0[iVar16 * 4 + 3];
        uVar3 = auStack_aa0[iVar16 * 4 + 1];
        fVar18 = *(float *)(param_1 + 0x98);
        afStack_8a0[iVar16 * 0x10 + 4] = fVar19;
        afStack_8a0[iVar16 * 0x10 + 5] = fVar18 * (float)(int)(uVar10 - uVar3) + 96.0;
        afStack_8a0[iVar16 * 0x10 + 6] = 0.0;
        afStack_8a0[iVar16 * 0x10 + 7] = 1.0;
        afStack_8a0[iVar16 * 0x10 + 8] =
             fVar19 + fVar17 * *(float *)(param_1 + 0x98) *
                               (float)(int)(auStack_aa0[iVar16 * 4 + 2] - auStack_aa0[iVar16 * 4]);
        afStack_8a0[iVar16 * 0x10 + 9] = 96.0;
        afStack_8a0[iVar16 * 0x10 + 10] = 0.0;
        afStack_8a0[iVar16 * 0x10 + 0xb] = 1.0;
        uVar10 = auStack_aa0[iVar16 * 4 + 3];
        uVar3 = auStack_aa0[iVar16 * 4 + 1];
        fVar18 = *(float *)(param_1 + 0x98);
        afStack_8a0[iVar16 * 0x10 + 0xc] =
             fVar19 + fVar17 * *(float *)(param_1 + 0x98) *
                               (float)(int)(auStack_aa0[iVar16 * 4 + 2] - auStack_aa0[iVar16 * 4]);
        afStack_8a0[iVar16 * 0x10 + 0xd] = fVar18 * (float)(int)(uVar10 - uVar3) + 96.0;
        afStack_8a0[iVar16 * 0x10 + 0xe] = 0.0;
        afStack_8a0[iVar16 * 0x10 + 0xf] = 1.0;
        fVar18 = *(float *)(param_1 + 0x98) *
                 (float)(int)((auStack_aa0[iVar16 * 4 + 2] - auStack_aa0[iVar16 * 4]) + -2);
      }
      fVar19 = fVar19 + fVar18;
    }
    iStack_88 = 0;
  }
  bVar5 = false;
  for (iVar16 = 0; iVar16 < iVar13; iVar16 = iVar16 + 1) {
    if ((((afStack_8a0[iVar16 * 0x10] + 1792.0 < 0.0) ||
         (4096.0 < afStack_8a0[iVar16 * 0x10] + 1792.0)) ||
        (afStack_8a0[iVar16 * 0x10 + 1] + 1824.0 < 0.0)) ||
       (4096.0 < afStack_8a0[iVar16 * 0x10 + 1] + 1824.0)) {
      bVar5 = true;
    }
    if (((afStack_8a0[iVar16 * 0x10 + 4] + 1792.0 < 0.0) ||
        (4096.0 < afStack_8a0[iVar16 * 0x10 + 4] + 1792.0)) ||
       ((afStack_8a0[iVar16 * 0x10 + 5] + 1824.0 < 0.0 ||
        (4096.0 < afStack_8a0[iVar16 * 0x10 + 5] + 1824.0)))) {
      bVar5 = true;
    }
    if (((afStack_8a0[iVar16 * 0x10 + 8] + 1792.0 < 0.0) ||
        (4096.0 < afStack_8a0[iVar16 * 0x10 + 8] + 1792.0)) ||
       ((afStack_8a0[iVar16 * 0x10 + 9] + 1824.0 < 0.0 ||
        (4096.0 < afStack_8a0[iVar16 * 0x10 + 9] + 1824.0)))) {
      bVar5 = true;
    }
    if ((((afStack_8a0[iVar16 * 0x10 + 0xc] + 1792.0 < 0.0) ||
         (4096.0 < afStack_8a0[iVar16 * 0x10 + 0xc] + 1792.0)) ||
        (afStack_8a0[iVar16 * 0x10 + 0xd] + 1824.0 < 0.0)) ||
       (4096.0 < afStack_8a0[iVar16 * 0x10 + 0xd] + 1824.0)) {
      bVar5 = true;
    }
    if (iStack_88 < 0) {
      bVar5 = true;
    }
  }
  bVar1 = (*(byte *)(param_1 + 0x40) & 1) == 0;
  uVar10 = (uint)bVar1;
  if (*(int *)(param_1 + uVar10 * 4 + 0x18) == 0) {
    uVar6 = __nwa__FUi((iVar13 * 5 + 0xc) * 0x10);
    *(undefined4 *)(param_1 + uVar10 * 4 + 0x18) = uVar6;
    iVar16 = *(int *)(param_1 + uVar10 * 4 + 0x18);
    *(int *)(iVar16 + 0x10) = iVar13 * 5 + 0x10000009;
    *(undefined4 *)(iVar16 + 0x14) = 0;
    *(undefined4 *)(iVar16 + 0x18) = 0;
    *(int *)(iVar16 + 0x1c) = iVar13 * 5 + 0x50000009;
    *(undefined8 *)(iVar16 + 0x20) = 0x7000000000000001;
    *(undefined8 *)(iVar16 + 0x28) = 0xe6ee8ee;
    *(undefined8 *)(iVar16 + 0x30) = 1;
    *(undefined8 *)(iVar16 + 0x38) = 0x3f;
    *(undefined8 *)(iVar16 + 0x40) = 0x60;
    *(undefined8 *)(iVar16 + 0x48) = 0x14;
    *(undefined8 *)(iVar16 + 0x50) = 5;
    *(undefined8 *)(iVar16 + 0x58) = 0;
    *(undefined8 *)(iVar16 + 0x60) = 0x23001;
    *(undefined8 *)(iVar16 + 0x68) = 0x47;
    uVar7 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x4224),1);
    *(ulong *)(iVar16 + 0x70) = uVar7 & 0xfffffffc0fffff | 0x2000000001300000;
    *(undefined8 *)(iVar16 + 0x78) = 0x16;
    *(ulong *)(iVar16 + 0x80) = uVar7 & 0xffffffffffffff | (long)*(int *)(param_1 + 0xac) << 0x38;
    *(undefined8 *)(iVar16 + 0x88) = 0;
    *(undefined8 *)(iVar16 + 0x90) = 0x44;
    *(undefined8 *)(iVar16 + 0x98) = 0x42;
    auVar11._8_8_ = in_v1_udw;
    auVar11._0_8_ = 0xa000000000000000;
    auVar12._4_4_ = in_zero_hi;
    auVar12._0_4_ = in_zero_lo;
    auVar12._8_4_ = in_zero_udw;
    auVar12._12_4_ = in_register_0000000c;
    auVar12 = _pcpyld(auVar12,auVar11);
    *(ulong *)(iVar16 + 0xa0) = (long)iVar13 | 0x400000000008000U | auVar12._0_8_;
    *(undefined8 *)(iVar16 + 0xa8) = 0x4343c3c310;
    for (iVar15 = 0; iVar15 < iVar13; iVar15 = iVar15 + 1) {
      *(undefined8 *)(iVar16 + (iVar15 * 5 + 0xb) * 0x10) = 0x154;
    }
  }
  puVar4 = *(undefined4 **)(param_1 + uVar10 * 4 + 0x18);
  if ((bVar5) || (*(float *)(param_1 + 0x70) != 0.0)) {
    *(undefined4 **)(param_1 + 0x54) = puVar4;
    *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfe | bVar1;
  }
  else {
    *puVar4 = 0x50000000;
    puVar4[1] = *(undefined4 *)
                 (*(int *)(iGpffff86b4 + 0x4224) +
                  (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x4224) + 10) * 4 + 0xc);
    puVar4[2] = 0;
    puVar4[3] = 0;
    fVar17 = *(float *)(param_1 + 0x9c) * 128.0;
    if (2.1474836e+09 <= fVar17) {
      fVar17 = fVar17 - 2.1474836e+09;
    }
    for (iVar16 = 0; iVar16 < iVar13; iVar16 = iVar16 + 1) {
      if (auStack_aa0[iVar16 * 4] == 0xffffffff) {
        *(undefined8 *)(puVar4 + (iVar16 * 5 + 0xc) * 4 + 2) = 0x71006f00;
        *(undefined8 *)(puVar4 + (iVar16 * 5 + 0xd) * 4 + 2) = 0x71006f00;
        *(undefined8 *)(puVar4 + (iVar16 * 5 + 0xe) * 4 + 2) = 0x71006f00;
        *(undefined8 *)(puVar4 + (iVar16 * 5 + 0xf) * 4 + 2) = 0x71006f00;
      }
      else {
        *(ulong *)(puVar4 + (iVar16 * 5 + 0xb) * 4 + 2) =
             ((long)(int)fVar17 & 0xffU) << 0x18 | 0x808080;
        *(long *)(puVar4 + (iVar16 * 5 + 0xc) * 4) =
             (long)(int)(auStack_aa0[iVar16 * 4] << 4) |
             (long)(int)(auStack_aa0[iVar16 * 4 + 1] << 4) << 0x10;
        lVar8 = __fixunssfdi((afStack_8a0[iVar16 * 0x10 + 1] + 1824.0) * 16.0);
        uVar7 = __fixunssfdi((afStack_8a0[iVar16 * 0x10] + 1792.0) * 16.0);
        *(ulong *)(puVar4 + (iVar16 * 5 + 0xc) * 4 + 2) = uVar7 | lVar8 << 0x10;
        *(long *)(puVar4 + (iVar16 * 5 + 0xd) * 4) =
             (long)(int)(auStack_aa0[iVar16 * 4] << 4) |
             (long)(int)(auStack_aa0[iVar16 * 4 + 3] << 4) << 0x10;
        uVar7 = __fixunssfdi((afStack_8a0[iVar16 * 0x10 + 4] + 1792.0) * 16.0);
        lVar8 = __fixunssfdi((afStack_8a0[iVar16 * 0x10 + 5] + 1824.0) * 16.0);
        *(ulong *)(puVar4 + (iVar16 * 5 + 0xd) * 4 + 2) = uVar7 | lVar8 << 0x10;
        *(long *)(puVar4 + (iVar16 * 5 + 0xe) * 4) =
             (long)(int)(auStack_aa0[iVar16 * 4 + 2] << 4) |
             (long)(int)(auStack_aa0[iVar16 * 4 + 1] << 4) << 0x10;
        uVar7 = __fixunssfdi((afStack_8a0[iVar16 * 0x10 + 8] + 1792.0) * 16.0);
        lVar8 = __fixunssfdi((afStack_8a0[iVar16 * 0x10 + 9] + 1824.0) * 16.0);
        *(ulong *)(puVar4 + (iVar16 * 5 + 0xe) * 4 + 2) = uVar7 | lVar8 << 0x10;
        *(long *)(puVar4 + (iVar16 * 5 + 0xf) * 4) =
             (long)(int)(auStack_aa0[iVar16 * 4 + 2] << 4) |
             (long)(int)(auStack_aa0[iVar16 * 4 + 3] << 4) << 0x10;
        uVar7 = __fixunssfdi((afStack_8a0[iVar16 * 0x10 + 0xc] + 1792.0) * 16.0);
        lVar8 = __fixunssfdi((afStack_8a0[iVar16 * 0x10 + 0xd] + 1824.0) * 16.0);
        *(ulong *)(puVar4 + (iVar16 * 5 + 0xf) * 4 + 2) = uVar7 | lVar8 << 0x10;
      }
    }
    *(undefined4 **)(param_1 + 0x54) = puVar4 + (iVar13 * 5 + 0xb) * 4;
    *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfe | bVar1;
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b2c0  EndSet__7HitInfoFv
 * C++: HitInfo::EndSet()
 * size: 0x30 bytes
 * --------------------------------------------------------------------------- */
void EndSet__7HitInfoFv(int param_1)

{
  (**(code **)(*(int *)(param_1 + 0x14) + 0x30))();
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b4a0  @24@__dt__7HitInfoFv
 * C++: @24@__dt__7HitInfoFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int * _24___dt__7HitInfoFv(int *param_1,short param_2)

{
  int *piVar1;
  
  piVar1 = param_1 + -6;
  if (piVar1 != (int *)0x0) {
    param_1[-1] = 0x40a430;
    param_1[4] = 0x40a440;
    param_1[7] = 0x40a450;
    if (*param_1 != 0) {
      __dla__FPv(*param_1);
    }
    if (param_1[1] != 0) {
      __dla__FPv(param_1[1]);
    }
    if (param_1[0x23] != 0) {
      __dla__FPv(param_1[0x23]);
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
 * JP: 0x0054b4b0  @44@__dt__7HitInfoFv
 * C++: @44@__dt__7HitInfoFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int _44___dt__7HitInfoFv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x2c;
  if (iVar1 != 0) {
    *(undefined4 *)(param_1 + -0x18) = 0x40a430;
    *(undefined4 *)(param_1 + -4) = 0x40a440;
    *(undefined4 *)(param_1 + 8) = 0x40a450;
    if (*(int *)(param_1 + -0x14) != 0) {
      __dla__FPv(*(undefined4 *)(param_1 + -0x14));
    }
    if (*(int *)(param_1 + -0x10) != 0) {
      __dla__FPv(*(undefined4 *)(param_1 + -0x10));
    }
    if (*(int *)(param_1 + 0x78) != 0) {
      __dla__FPv(*(undefined4 *)(param_1 + 0x78));
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

