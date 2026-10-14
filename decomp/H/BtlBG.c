/* decomp/H/BtlBG.c — cleaned Ghidra output (SH2JP_BATTLE.BIN, JP Furokuban, base 0x00430a00).
 * 12 function(s). Types: see types.h. Names/gp globals resolved from symbols/SLPM_602.19.syms. */
#include "types.h"

/* ---------------------------------------------------------------------------
 * JP: 0x0055b3b0  __ct__5BtlBGFii
 * C++: BtlBG::__ct(int, int)
 * size: 0xfc bytes
 * --------------------------------------------------------------------------- */
int __ct__5BtlBGFii(int param_1,undefined2 param_2,undefined2 param_3)

{
  int iVar1;
  
  __ct__5ModelFv(param_1);
  *(undefined4 *)(param_1 + 0x10) = 0x40a680;
  *(undefined4 *)(param_1 + 0x1c) = 0x40a690;
  __ct__10CBgElementFv(param_1 + 0x4d0);
  *(undefined4 *)(param_1 + 0x4b0) = 0;
  *(undefined2 *)(param_1 + 0x4b4) = param_2;
  *(undefined2 *)(param_1 + 0x4b6) = param_3;
  for (iVar1 = 0; iVar1 < 0xc; iVar1 = iVar1 + 1) {
    *(undefined1 *)(param_1 + iVar1 + 0x4c4) = 0x80;
    *(undefined1 *)(param_1 + iVar1 + 0x4b8) = 0x80;
  }
  Clear__10CBgElementFv(param_1 + 0x4d0);
  *(undefined4 *)(param_1 + 0x760) = 0;
  *(undefined4 *)(param_1 + 0x764) = 0;
  return param_1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0055b4b0  __dt__5BtlBGFv
 * C++: BtlBG::__dt()
 * size: 0x94 bytes
 * --------------------------------------------------------------------------- */
int __dt__5BtlBGFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x10) = 0x40a680;
    *(undefined4 *)(param_1 + 0x1c) = 0x40a690;
    __dt__10CBgElementFv(param_1 + 0x4d0,0xffffffffffffffff);
    __dt__5ModelFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0055b550  DeleteSetUp__5BtlBGFv
 * C++: BtlBG::DeleteSetUp()
 * size: 0x90 bytes
 * --------------------------------------------------------------------------- */
void DeleteSetUp__5BtlBGFv(int param_1)

{
  long lVar1;
  
  Clear__10CBgElementFv(param_1 + 0x4d0);
  DeleteSetUp__5ModelFv(param_1);
  while (lVar1 = FindOT__5WorldFP8VIF1Prim(0x42bf10,param_1), lVar1 != 0) {
    ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,param_1);
  }
  *(byte *)(param_1 + 0x4b0) = *(byte *)(param_1 + 0x4b0) & 0xfe;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0055b5e0  TranseCallBack__5BtlBGFRC7FVector7FVector
 * C++: BtlBG::TranseCallBack(FVector *, FVector)
 * size: 0x30 bytes
 * --------------------------------------------------------------------------- */
void TranseCallBack__5BtlBGFRC7FVector7FVector
               (undefined4 param_1,undefined8 param_2,undefined8 param_3,undefined4 param_4)

{
  __ct__7FVectorFRC7FVector(param_1,param_4);
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0055b610  EventCallBack__5BtlBGFPCcPCciiUi
 * C++: BtlBG::EventCallBack(char *, char *, int, int, uint)
 * size: 0x50 bytes
 * --------------------------------------------------------------------------- */
void EventCallBack__5BtlBGFPCcPCciiUi
               (undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
               undefined4 param_5,undefined4 param_6)

{
  EventCallBack__5ModelFPCcPCciiUi(param_1,param_2,param_3,param_4,param_5,param_6);
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0055b660  MotionEndCallBack__5BtlBGFPCc
 * C++: BtlBG::MotionEndCallBack(char *)
 * size: 0x10 bytes
 * --------------------------------------------------------------------------- */
void MotionEndCallBack__5BtlBGFPCc(void)

{
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0055b670  BtlBGInit__5BtlBGFPUc
 * C++: BtlBG::BtlBGInit(uchar *)
 * size: 0x58c bytes
 * --------------------------------------------------------------------------- */
void BtlBGInit__5BtlBGFPUc(undefined8 param_1,undefined8 param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  long lVar4;
  long *plVar5;
  undefined4 *puVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  
  iVar1 = GetFileCount(param_2);
  iVar10 = 0;
  do {
    iVar11 = (int)param_1;
    if (iVar1 <= iVar10) {
LAB_0055b730:
      for (iVar10 = 0; iVar10 < iVar1; iVar10 = iVar10 + 1) {
        uVar3 = GetFileID(param_2,iVar10);
        lVar4 = strcmp(uVar3,0x653388);
        if (lVar4 == 0) {
          uVar3 = GetFileEntry(param_2,iVar10);
          createMotion__5ModelFPUc(param_1,uVar3);
        }
        else {
          lVar4 = strcmp(uVar3,0x653390);
          if (lVar4 == 0) {
            uVar2 = GetFileEntry(param_2,iVar10);
            *(undefined4 *)(iVar11 + 0x75c) = uVar2;
            Create__10CBgElementFPUcb(iVar11 + 0x4d0,*(undefined4 *)(iVar11 + 0x75c),0);
            iVar8 = *(int *)(*(int *)(iVar11 + 0x75c) + 0x1c) + *(int *)(iVar11 + 0x75c);
            iVar7 = *(int *)(iVar8 + 0xc) + iVar8;
            for (iVar9 = 0; iVar9 < *(int *)(iVar8 + 8); iVar9 = iVar9 + 1) {
              plVar5 = (long *)(*(int *)(iVar7 + 0xc) + iVar7);
              lVar4 = *plVar5;
              if (lVar4 == 0x2020544345464645) {
                *(int *)(iVar11 + 0x760) = *(int *)((int)plVar5 + 0xc) + (int)plVar5;
                *(int *)(iVar11 + 0x764) = (int)plVar5[1];
              }
              else if (lVar4 == 0x2020202020474f46) {
                puVar6 = (undefined4 *)(*(int *)((int)plVar5 + 0xc) + (int)plVar5);
                *(undefined1 *)(iGpffff8598 + 0x388) = *(undefined1 *)(puVar6 + 2);
                *(undefined1 *)(iGpffff8598 + 0x389) = *(undefined1 *)((int)puVar6 + 9);
                *(undefined1 *)(iGpffff8598 + 0x38a) = *(undefined1 *)((int)puVar6 + 10);
                *(undefined1 *)(iGpffff8598 + 0x38b) = *(undefined1 *)((int)puVar6 + 0xb);
                *(ulong *)(iGpffff8598 + 0x150) = (ulong)*(uint3 *)(puVar6 + 2);
                uVar2 = puVar6[1];
                *(undefined4 *)(iGpffff8598 + 0x380) = *puVar6;
                *(undefined4 *)(iGpffff8598 + 900) = uVar2;
                *(undefined4 *)(iGpffff8598 + 0x360) = 0;
                *(undefined4 *)(iGpffff8598 + 0x364) = *(undefined4 *)(iGpffff8598 + 0x380);
                *(float *)(iGpffff8598 + 0x368) =
                     256.0 / (*(float *)(iGpffff8598 + 900) - *(float *)(iGpffff8598 + 0x380));
                *(undefined4 *)(iGpffff8598 + 0x36c) = 0x437f0000;
                *(byte *)(iVar11 + 0x4b0) = *(byte *)(iVar11 + 0x4b0) & 0xfb | 4;
              }
              else if ((lVar4 != 0x202020544847494c) && (lVar4 == 0x20524f4c4f434742)) {
                *(undefined4 *)(iGpffff8598 + 0x180) =
                     *(undefined4 *)(*(int *)((int)plVar5 + 0xc) + (int)plVar5);
              }
              iVar7 = iVar7 + 0x10;
            }
          }
        }
      }
      if (-1 < (long)((ulong)*(byte *)(iVar11 + 0x4b0) << 0x3d)) {
        *(undefined1 *)(iGpffff8598 + 0x388) = 0;
        *(undefined1 *)(iGpffff8598 + 0x389) = 0;
        *(undefined1 *)(iGpffff8598 + 0x38a) = 0;
        *(undefined1 *)(iGpffff8598 + 0x38b) = 0;
        *(undefined8 *)(iGpffff8598 + 0x150) = 0;
        *(undefined4 *)(iGpffff8598 + 0x380) = 0x42c80000;
        *(undefined4 *)(iGpffff8598 + 900) = 0x447a0000;
        *(undefined4 *)(iGpffff8598 + 0x360) = 0;
        *(undefined4 *)(iGpffff8598 + 0x364) = *(undefined4 *)(iGpffff8598 + 0x380);
        *(float *)(iGpffff8598 + 0x368) =
             256.0 / (*(float *)(iGpffff8598 + 900) - *(float *)(iGpffff8598 + 0x380));
        *(undefined4 *)(iGpffff8598 + 0x36c) = 0x437f0000;
      }
      setMotion__5ModelFPCcf(0,param_1,0x653398);
      return;
    }
    uVar3 = GetFileID(param_2,iVar10);
    lVar4 = strcmp(uVar3,0x653380);
    if (lVar4 == 0) {
      uVar3 = GetFileEntry(param_2,iVar10);
      (**(code **)(*(int *)(iVar11 + 0x10) + 0x24))(param_1,uVar3);
      *(int *)(iVar11 + 0x758) = (int)param_2;
      goto LAB_0055b730;
    }
    iVar10 = iVar10 + 1;
  } while( true );
}

/* ---------------------------------------------------------------------------
 * JP: 0x0055bc00  OTEntry__5BtlBGFii
 * C++: BtlBG::OTEntry(int, int)
 * size: 0xd8 bytes
 * --------------------------------------------------------------------------- */
void OTEntry__5BtlBGFii(int param_1,undefined4 param_2,undefined4 param_3)

{
  if ((*(byte *)(param_1 + 0x4b0) & 1) == 0) {
    AddDoubleOT__5WorldFiiP8VIF1Prim(0x42bf10,param_2,param_3,param_1);
    setReciveShadow__13ShadowControlFP5Model(uGpffff83c4,param_1);
    if (-1 < *(short *)(param_1 + 0x752)) {
      Dsp__11BgEffectManFi(uGpffff8540,*(short *)(param_1 + 0x752));
    }
    *(byte *)(param_1 + 0x4b0) = *(byte *)(param_1 + 0x4b0) & 0xfe | 1;
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0055bce0  OTRelease__5BtlBGFv
 * C++: BtlBG::OTRelease()
 * size: 0xf0 bytes
 * --------------------------------------------------------------------------- */
void OTRelease__5BtlBGFv(int param_1)

{
  long lVar1;
  
  if ((*(byte *)(param_1 + 0x4b0) & 1) != 0) {
    while (lVar1 = FindOT__5WorldFP8VIF1Prim(0x42bf10,param_1), lVar1 != 0) {
      ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,param_1);
    }
    releaseShadow__13ShadowControlFP5Model(uGpffff83c4,param_1);
    if (-1 < *(short *)(param_1 + 0x752)) {
      Clr__11BgEffectManFi(uGpffff8540,*(short *)(param_1 + 0x752));
    }
    *(byte *)(param_1 + 0x4b0) = *(byte *)(param_1 + 0x4b0) & 0xfe;
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0055bdd0  SetAlpha__5BtlBGFiUcb
 * C++: BtlBG::SetAlpha(int, uchar, bool)
 * size: 0x1c70 bytes
 * --------------------------------------------------------------------------- */
/* WARNING: Removing unreachable block (ram,0x0055c278) */
/* WARNING: Removing unreachable block (ram,0x0055c4f8) */
/* WARNING: Removing unreachable block (ram,0x0055c778) */
/* WARNING: Removing unreachable block (ram,0x0055cc00) */
/* WARNING: Removing unreachable block (ram,0x0055cee0) */
/* WARNING: Removing unreachable block (ram,0x0055d1c0) */
/* WARNING: Removing unreachable block (ram,0x0055d4a0) */
/* WARNING: Removing unreachable block (ram,0x0055d748) */
/* WARNING: Removing unreachable block (ram,0x0055d890) */
/* WARNING: Removing unreachable block (ram,0x0055d608) */
/* WARNING: Removing unreachable block (ram,0x0055d330) */
/* WARNING: Removing unreachable block (ram,0x0055d050) */
/* WARNING: Removing unreachable block (ram,0x0055cd70) */
/* WARNING: Removing unreachable block (ram,0x0055c8b0) */
/* WARNING: Removing unreachable block (ram,0x0055c638) */
/* WARNING: Removing unreachable block (ram,0x0055c3b8) */
/* WARNING: Removing unreachable block (ram,0x0055c140) */
/* WARNING: Removing unreachable block (ram,0x0055d9d0) */

void SetAlpha__5BtlBGFiUcb(int param_1,int param_2,undefined1 param_3,undefined8 param_4)

{
  uint uVar1;
  int iVar2;
  undefined4 *puVar3;
  int iStack_30;
  
  uVar1 = (uint)*(ushort *)(*(int *)(param_1 + 0x5c) + 4);
  if (*(short *)(param_1 + 0x4b6) == 0) {
    iStack_30 = param_2;
    switch(param_2) {
    case 0:
    case 1:
      iStack_30 = 0;
      break;
    case 2:
    case 3:
      iStack_30 = 2;
      break;
    case 4:
    case 5:
      iStack_30 = 4;
      break;
    case 6:
    case 7:
      iStack_30 = 6;
    }
    *(undefined1 *)(param_1 + iStack_30 + 0x4b8) = param_3;
    if ((char)param_4 == '\x01') {
      if (*(byte *)(param_1 + iStack_30 + 0x4c4) < *(byte *)(param_1 + iStack_30 + 0x4b8)) {
        if (*(byte *)(param_1 + iStack_30 + 0x4c4) + 2 <
            (uint)*(byte *)(param_1 + iStack_30 + 0x4b8)) {
          *(char *)(param_1 + iStack_30 + 0x4c4) = *(char *)(param_1 + iStack_30 + 0x4c4) + '\x02';
        }
        else {
          *(undefined1 *)(param_1 + iStack_30 + 0x4c4) =
               *(undefined1 *)(param_1 + iStack_30 + 0x4b8);
        }
      }
      else if (*(byte *)(param_1 + iStack_30 + 0x4b8) < *(byte *)(param_1 + iStack_30 + 0x4c4)) {
        if ((int)(uint)*(byte *)(param_1 + iStack_30 + 0x4b8) <
            (int)(*(byte *)(param_1 + iStack_30 + 0x4c4) - 2)) {
          *(char *)(param_1 + iStack_30 + 0x4c4) = *(char *)(param_1 + iStack_30 + 0x4c4) + -2;
        }
        else {
          *(undefined1 *)(param_1 + iStack_30 + 0x4c4) =
               *(undefined1 *)(param_1 + iStack_30 + 0x4b8);
        }
      }
    }
    else {
      *(undefined1 *)(param_1 + iStack_30 + 0x4c4) = *(undefined1 *)(param_1 + iStack_30 + 0x4b8);
    }
    switch(iStack_30) {
    case 0:
    case 1:
      for (iVar2 = 0; iVar2 < (int)uVar1; iVar2 = iVar2 + 1) {
        if ((*(char *)**(undefined4 **)(*(int *)(param_1 + 0x48) + iVar2 * 4) == 'F') &&
           (*(char *)(**(int **)(*(int *)(param_1 + 0x48) + iVar2 * 4) + 1) == 'R')) {
          setAtomicAlpha__6AtomicFUc(*(undefined4 *)(*(int *)(param_1 + 0x48) + iVar2 * 4),
                          *(undefined1 *)(param_1 + iStack_30 + 0x4c4));
        }
      }
      (**(code **)(*(int *)(param_1 + 0x10) + 0x58))
                ((float)*(byte *)(param_1 + iStack_30 + 0x4c4) / 128.0,param_1,0,0x1f);
      break;
    case 2:
    case 3:
      for (iVar2 = 0; iVar2 < (int)uVar1; iVar2 = iVar2 + 1) {
        if ((*(char *)**(undefined4 **)(*(int *)(param_1 + 0x48) + iVar2 * 4) == 'B') &&
           (*(char *)(**(int **)(*(int *)(param_1 + 0x48) + iVar2 * 4) + 1) == 'A')) {
          setAtomicAlpha__6AtomicFUc(*(undefined4 *)(*(int *)(param_1 + 0x48) + iVar2 * 4),
                          *(undefined1 *)(param_1 + iStack_30 + 0x4c4));
        }
      }
      (**(code **)(*(int *)(param_1 + 0x10) + 0x58))
                ((float)*(byte *)(param_1 + iStack_30 + 0x4c4) / 128.0,param_1,0x20,0x3f);
      break;
    case 4:
    case 5:
      for (iVar2 = 0; iVar2 < (int)uVar1; iVar2 = iVar2 + 1) {
        if ((*(char *)**(undefined4 **)(*(int *)(param_1 + 0x48) + iVar2 * 4) == 'L') &&
           (*(char *)(**(int **)(*(int *)(param_1 + 0x48) + iVar2 * 4) + 1) == 'E')) {
          setAtomicAlpha__6AtomicFUc(*(undefined4 *)(*(int *)(param_1 + 0x48) + iVar2 * 4),
                          *(undefined1 *)(param_1 + iStack_30 + 0x4c4));
        }
      }
      (**(code **)(*(int *)(param_1 + 0x10) + 0x58))
                ((float)*(byte *)(param_1 + iStack_30 + 0x4c4) / 128.0,param_1,0x40,0x5f);
      break;
    case 6:
    case 7:
      for (iVar2 = 0; iVar2 < (int)uVar1; iVar2 = iVar2 + 1) {
        if ((*(char *)**(undefined4 **)(*(int *)(param_1 + 0x48) + iVar2 * 4) == 'R') &&
           (*(char *)(**(int **)(*(int *)(param_1 + 0x48) + iVar2 * 4) + 1) == 'I')) {
          setAtomicAlpha__6AtomicFUc(*(undefined4 *)(*(int *)(param_1 + 0x48) + iVar2 * 4),
                          *(undefined1 *)(param_1 + iStack_30 + 0x4c4));
        }
      }
      (**(code **)(*(int *)(param_1 + 0x10) + 0x58))
                ((float)*(byte *)(param_1 + iStack_30 + 0x4c4) / 128.0,param_1,0x60,0x7f);
      break;
    case 8:
      for (iVar2 = 0; iVar2 < (int)uVar1; iVar2 = iVar2 + 1) {
        if ((*(char *)**(undefined4 **)(*(int *)(param_1 + 0x48) + iVar2 * 4) == 'R') &&
           (*(char *)(**(int **)(*(int *)(param_1 + 0x48) + iVar2 * 4) + 1) == 'O')) {
          setAtomicAlpha__6AtomicFUc(*(undefined4 *)(*(int *)(param_1 + 0x48) + iVar2 * 4),
                          *(undefined1 *)(param_1 + iStack_30 + 0x4c4));
        }
      }
      (**(code **)(*(int *)(param_1 + 0x10) + 0x58))
                ((float)*(byte *)(param_1 + iStack_30 + 0x4c4) / 128.0,param_1,0x80,0x8f);
      break;
    case 9:
      for (iVar2 = 0; iVar2 < (int)uVar1; iVar2 = iVar2 + 1) {
        if ((*(char *)**(undefined4 **)(*(int *)(param_1 + 0x48) + iVar2 * 4) == 'F') &&
           (*(char *)(**(int **)(*(int *)(param_1 + 0x48) + iVar2 * 4) + 1) == 'L')) {
          setAtomicAlpha__6AtomicFUc(*(undefined4 *)(*(int *)(param_1 + 0x48) + iVar2 * 4),
                          *(undefined1 *)(param_1 + iStack_30 + 0x4c4));
        }
      }
      (**(code **)(*(int *)(param_1 + 0x10) + 0x58))
                ((float)*(byte *)(param_1 + iStack_30 + 0x4c4) / 128.0,param_1,0x90,0x9f);
      break;
    case 10:
      for (iVar2 = 0; iVar2 < (int)uVar1; iVar2 = iVar2 + 1) {
        if ((*(char *)**(undefined4 **)(*(int *)(param_1 + 0x48) + iVar2 * 4) == 'F') &&
           (*(char *)(**(int **)(*(int *)(param_1 + 0x48) + iVar2 * 4) + 1) == 'A')) {
          setAtomicAlpha__6AtomicFUc(*(undefined4 *)(*(int *)(param_1 + 0x48) + iVar2 * 4),
                          *(undefined1 *)(param_1 + iStack_30 + 0x4c4));
        }
      }
      (**(code **)(*(int *)(param_1 + 0x10) + 0x58))
                ((float)*(byte *)(param_1 + iStack_30 + 0x4c4) / 128.0,param_1,0xa0,0xaf);
    }
  }
  else {
    *(undefined1 *)(param_1 + param_2 + 0x4b8) = param_3;
    if ((char)param_4 == '\x01') {
      if (*(byte *)(param_1 + param_2 + 0x4c4) < *(byte *)(param_1 + param_2 + 0x4b8)) {
        if (*(byte *)(param_1 + param_2 + 0x4c4) + 2 < (uint)*(byte *)(param_1 + param_2 + 0x4b8)) {
          *(char *)(param_1 + param_2 + 0x4c4) = *(char *)(param_1 + param_2 + 0x4c4) + '\x02';
        }
        else {
          *(undefined1 *)(param_1 + param_2 + 0x4c4) = *(undefined1 *)(param_1 + param_2 + 0x4b8);
        }
      }
      else if (*(byte *)(param_1 + param_2 + 0x4b8) < *(byte *)(param_1 + param_2 + 0x4c4)) {
        if ((int)(uint)*(byte *)(param_1 + param_2 + 0x4b8) <
            (int)(*(byte *)(param_1 + param_2 + 0x4c4) - 2)) {
          *(char *)(param_1 + param_2 + 0x4c4) = *(char *)(param_1 + param_2 + 0x4c4) + -2;
        }
        else {
          *(undefined1 *)(param_1 + param_2 + 0x4c4) = *(undefined1 *)(param_1 + param_2 + 0x4b8);
        }
      }
    }
    else {
      *(undefined1 *)(param_1 + param_2 + 0x4c4) = *(undefined1 *)(param_1 + param_2 + 0x4b8);
    }
    switch(param_2) {
    case 0:
      for (iVar2 = 0; iVar2 < (int)uVar1; iVar2 = iVar2 + 1) {
        if (((*(char *)**(undefined4 **)(*(int *)(param_1 + 0x48) + iVar2 * 4) == 'F') &&
            (*(char *)(**(int **)(*(int *)(param_1 + 0x48) + iVar2 * 4) + 1) == 'R')) &&
           (*(char *)(**(int **)(*(int *)(param_1 + 0x48) + iVar2 * 4) + 2) == 'L')) {
          setAtomicAlpha__6AtomicFUc(*(undefined4 *)(*(int *)(param_1 + 0x48) + iVar2 * 4),
                          *(undefined1 *)(param_1 + param_2 + 0x4c4));
        }
      }
      (**(code **)(*(int *)(param_1 + 0x10) + 0x58))
                ((float)*(byte *)(param_1 + param_2 + 0x4c4) / 128.0,param_1,0,0xf);
      break;
    case 1:
      for (iVar2 = 0; iVar2 < (int)uVar1; iVar2 = iVar2 + 1) {
        if (((*(char *)**(undefined4 **)(*(int *)(param_1 + 0x48) + iVar2 * 4) == 'F') &&
            (*(char *)(**(int **)(*(int *)(param_1 + 0x48) + iVar2 * 4) + 1) == 'R')) &&
           (*(char *)(**(int **)(*(int *)(param_1 + 0x48) + iVar2 * 4) + 2) == 'R')) {
          setAtomicAlpha__6AtomicFUc(*(undefined4 *)(*(int *)(param_1 + 0x48) + iVar2 * 4),
                          *(undefined1 *)(param_1 + param_2 + 0x4c4));
        }
      }
      (**(code **)(*(int *)(param_1 + 0x10) + 0x58))
                ((float)*(byte *)(param_1 + param_2 + 0x4c4) / 128.0,param_1,0x10,0x1f);
      break;
    case 2:
      for (iVar2 = 0; iVar2 < (int)uVar1; iVar2 = iVar2 + 1) {
        if (((*(char *)**(undefined4 **)(*(int *)(param_1 + 0x48) + iVar2 * 4) == 'B') &&
            (*(char *)(**(int **)(*(int *)(param_1 + 0x48) + iVar2 * 4) + 1) == 'A')) &&
           (*(char *)(**(int **)(*(int *)(param_1 + 0x48) + iVar2 * 4) + 2) == 'L')) {
          setAtomicAlpha__6AtomicFUc(*(undefined4 *)(*(int *)(param_1 + 0x48) + iVar2 * 4),
                          *(undefined1 *)(param_1 + param_2 + 0x4c4));
        }
      }
      (**(code **)(*(int *)(param_1 + 0x10) + 0x58))
                ((float)*(byte *)(param_1 + param_2 + 0x4c4) / 128.0,param_1,0x20,0x2f);
      break;
    case 3:
      for (iVar2 = 0; iVar2 < (int)uVar1; iVar2 = iVar2 + 1) {
        if (((*(char *)**(undefined4 **)(*(int *)(param_1 + 0x48) + iVar2 * 4) == 'B') &&
            (*(char *)(**(int **)(*(int *)(param_1 + 0x48) + iVar2 * 4) + 1) == 'A')) &&
           (*(char *)(**(int **)(*(int *)(param_1 + 0x48) + iVar2 * 4) + 2) == 'R')) {
          setAtomicAlpha__6AtomicFUc(*(undefined4 *)(*(int *)(param_1 + 0x48) + iVar2 * 4),
                          *(undefined1 *)(param_1 + param_2 + 0x4c4));
        }
      }
      (**(code **)(*(int *)(param_1 + 0x10) + 0x58))
                ((float)*(byte *)(param_1 + param_2 + 0x4c4) / 128.0,param_1,0x30,0x3f);
      break;
    case 4:
      for (iVar2 = 0; iVar2 < (int)uVar1; iVar2 = iVar2 + 1) {
        if (((*(char *)**(undefined4 **)(*(int *)(param_1 + 0x48) + iVar2 * 4) == 'L') &&
            (*(char *)(**(int **)(*(int *)(param_1 + 0x48) + iVar2 * 4) + 1) == 'E')) &&
           (*(char *)(**(int **)(*(int *)(param_1 + 0x48) + iVar2 * 4) + 2) == 'F')) {
          setAtomicAlpha__6AtomicFUc(*(undefined4 *)(*(int *)(param_1 + 0x48) + iVar2 * 4),
                          *(undefined1 *)(param_1 + param_2 + 0x4c4));
        }
      }
      (**(code **)(*(int *)(param_1 + 0x10) + 0x58))
                ((float)*(byte *)(param_1 + param_2 + 0x4c4) / 128.0,param_1,0x40,0x4f);
      break;
    case 5:
      for (iVar2 = 0; iVar2 < (int)uVar1; iVar2 = iVar2 + 1) {
        if (((*(char *)**(undefined4 **)(*(int *)(param_1 + 0x48) + iVar2 * 4) == 'L') &&
            (*(char *)(**(int **)(*(int *)(param_1 + 0x48) + iVar2 * 4) + 1) == 'E')) &&
           (*(char *)(**(int **)(*(int *)(param_1 + 0x48) + iVar2 * 4) + 2) == 'B')) {
          puVar3 = (undefined4 *)(*(int *)(param_1 + 0x48) + iVar2 * 4);
          param_4 = setAtomicAlpha__6AtomicFUc(*puVar3,*(undefined1 *)(param_1 + param_2 + 0x4c4),puVar3,
                                    param_4);
        }
      }
      (**(code **)(*(int *)(param_1 + 0x10) + 0x58))
                ((float)*(byte *)(param_1 + param_2 + 0x4c4) / 128.0,param_1,0x50,0x5f);
      break;
    case 6:
      for (iVar2 = 0; iVar2 < (int)uVar1; iVar2 = iVar2 + 1) {
        if (((*(char *)**(undefined4 **)(*(int *)(param_1 + 0x48) + iVar2 * 4) == 'R') &&
            (*(char *)(**(int **)(*(int *)(param_1 + 0x48) + iVar2 * 4) + 1) == 'I')) &&
           (*(char *)(**(int **)(*(int *)(param_1 + 0x48) + iVar2 * 4) + 2) == 'F')) {
          setAtomicAlpha__6AtomicFUc(*(undefined4 *)(*(int *)(param_1 + 0x48) + iVar2 * 4),
                          *(undefined1 *)(param_1 + param_2 + 0x4c4));
        }
      }
      (**(code **)(*(int *)(param_1 + 0x10) + 0x58))
                ((float)*(byte *)(param_1 + param_2 + 0x4c4) / 128.0,param_1,0x60,0x6f);
      break;
    case 7:
      for (iVar2 = 0; iVar2 < (int)uVar1; iVar2 = iVar2 + 1) {
        if (((*(char *)**(undefined4 **)(*(int *)(param_1 + 0x48) + iVar2 * 4) == 'R') &&
            (*(char *)(**(int **)(*(int *)(param_1 + 0x48) + iVar2 * 4) + 1) == 'I')) &&
           (*(char *)(**(int **)(*(int *)(param_1 + 0x48) + iVar2 * 4) + 2) == 'B')) {
          setAtomicAlpha__6AtomicFUc(*(undefined4 *)(*(int *)(param_1 + 0x48) + iVar2 * 4),
                          *(undefined1 *)(param_1 + param_2 + 0x4c4));
        }
      }
      (**(code **)(*(int *)(param_1 + 0x10) + 0x58))
                ((float)*(byte *)(param_1 + param_2 + 0x4c4) / 128.0,param_1,0x70,0x7f);
      break;
    case 8:
      for (iVar2 = 0; iVar2 < (int)uVar1; iVar2 = iVar2 + 1) {
        if ((*(char *)**(undefined4 **)(*(int *)(param_1 + 0x48) + iVar2 * 4) == 'R') &&
           (*(char *)(**(int **)(*(int *)(param_1 + 0x48) + iVar2 * 4) + 1) == 'O')) {
          setAtomicAlpha__6AtomicFUc(*(undefined4 *)(*(int *)(param_1 + 0x48) + iVar2 * 4),
                          *(undefined1 *)(param_1 + param_2 + 0x4c4));
        }
      }
      (**(code **)(*(int *)(param_1 + 0x10) + 0x58))
                ((float)*(byte *)(param_1 + param_2 + 0x4c4) / 128.0,param_1,0x80,0x8f);
      break;
    case 9:
      for (iVar2 = 0; iVar2 < (int)uVar1; iVar2 = iVar2 + 1) {
        if ((*(char *)**(undefined4 **)(*(int *)(param_1 + 0x48) + iVar2 * 4) == 'F') &&
           (*(char *)(**(int **)(*(int *)(param_1 + 0x48) + iVar2 * 4) + 1) == 'L')) {
          setAtomicAlpha__6AtomicFUc(*(undefined4 *)(*(int *)(param_1 + 0x48) + iVar2 * 4),
                          *(undefined1 *)(param_1 + param_2 + 0x4c4));
        }
      }
      (**(code **)(*(int *)(param_1 + 0x10) + 0x58))
                ((float)*(byte *)(param_1 + param_2 + 0x4c4) / 128.0,param_1,0x90,0x9f);
      break;
    case 10:
      for (iVar2 = 0; iVar2 < (int)uVar1; iVar2 = iVar2 + 1) {
        if ((*(char *)**(undefined4 **)(*(int *)(param_1 + 0x48) + iVar2 * 4) == 'F') &&
           (*(char *)(**(int **)(*(int *)(param_1 + 0x48) + iVar2 * 4) + 1) == 'A')) {
          setAtomicAlpha__6AtomicFUc(*(undefined4 *)(*(int *)(param_1 + 0x48) + iVar2 * 4),
                          *(undefined1 *)(param_1 + param_2 + 0x4c4));
        }
      }
      (**(code **)(*(int *)(param_1 + 0x10) + 0x58))
                ((float)*(byte *)(param_1 + param_2 + 0x4c4) / 128.0,param_1,0xa0,0xaf);
    }
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0055da40  SetBtlBGEffectAlpha__5BtlBGFiif
 * C++: BtlBG::SetBtlBGEffectAlpha(int, int, float)
 * size: 0x184 bytes
 * --------------------------------------------------------------------------- */
void SetBtlBGEffectAlpha__5BtlBGFiif(undefined4 param_1,int param_2,int param_3,int param_4)

{
  short sVar1;
  long lVar2;
  short *psVar3;
  int iVar4;
  undefined4 uStack_10;
  
  sVar1 = *(short *)(param_2 + 0x752);
  if ((((*(int *)(param_2 + 0x760) != 0) && (*(int *)(param_2 + 0x764) != 0)) && (iGpffff8540 != 0))
     && (-1 < sVar1)) {
    uStack_10 = param_1;
    if ((*(byte *)(param_2 + 0x4b0) & 1) == 0) {
      uStack_10 = 0;
    }
    psVar3 = *(short **)(param_2 + 0x760);
    for (iVar4 = 0; iVar4 < *(int *)(param_2 + 0x764); iVar4 = iVar4 + 1) {
      if ((((long)param_3 <= (long)*psVar3) && ((long)*psVar3 <= (long)param_4)) &&
         (((*(byte *)(psVar3 + 2) & 1) == 1 &&
          (lVar2 = GetEffect__11BgEffectManFii(iGpffff8540,sVar1,iVar4), lVar2 != 0)))) {
        (**(code **)(*(int *)((int)lVar2 + 0x10) + 0x34))(uStack_10,lVar2,0);
      }
      psVar3 = psVar3 + 8;
    }
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0055dbd0  @20@__dt__5BtlBGFv
 * C++: @20@__dt__5BtlBGFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int _20___dt__5BtlBGFv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x14;
  if (iVar1 != 0) {
    *(undefined4 *)(param_1 + -4) = 0x40a680;
    *(undefined4 *)(param_1 + 8) = 0x40a690;
    __dt__10CBgElementFv(param_1 + 0x4bc,0xffffffffffffffff);
    __dt__5ModelFv(iVar1,0);
    if (0 < param_2) {
      __dl__FPv(iVar1);
    }
  }
  return iVar1;
}

