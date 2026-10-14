/* decomp/H/ParamDisp.c — cleaned Ghidra output (SH2JP_BATTLE.BIN, JP Furokuban, base 0x00430a00).
 * 12 function(s). Types: see types.h. Names/gp globals resolved from symbols/SLPM_602.19.syms. */
#include "types.h"

/* ---------------------------------------------------------------------------
 * JP: 0x004dca20  __ct__9ParamDispFv
 * C++: ParamDisp::__ct()
 * size: 0x14c bytes
 * --------------------------------------------------------------------------- */
int __ct__9ParamDispFv(int param_1)

{
  __ct__7CPolObjFv(param_1);
  __ct__8VIF1PrimFv(param_1 + 0x18);
  *(undefined4 *)(param_1 + 0x2c) = 0;
  *(undefined4 *)(param_1 + 0x30) = 0;
  *(undefined4 *)(param_1 + 0x34) = 0x4049f0;
  *(undefined4 *)(param_1 + 0x14) = 0x40a5f0;
  *(undefined4 *)(param_1 + 0x28) = 0x40a600;
  *(undefined4 *)(param_1 + 0x34) = 0x40a610;
  *(undefined4 *)(param_1 + 0x38) = 0;
  *(undefined4 *)(param_1 + 0x3c) = 0;
  *(undefined4 *)(param_1 + 0x40) = 0;
  *(undefined4 *)(param_1 + 0x44) = 0;
  *(undefined4 *)(param_1 + 0x48) = 0;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  *(undefined4 *)(param_1 + 0x18) = 0;
  *(undefined4 *)(param_1 + 0x54) = 0;
  *(undefined4 *)(param_1 + 0x50) = 0;
  *(undefined4 *)(param_1 + 0x4c) = 0;
  *(undefined4 *)(param_1 + 0x60) = 0x43960000;
  *(undefined2 *)(param_1 + 100) = 0xffff;
  *(undefined4 *)(param_1 + 0x68) = 0;
  SetParty__9ParamDispFii(param_1,0,0xffffffffffffffff);
  *(undefined4 *)(param_1 + 0x280) = 3;
  *(undefined4 *)(param_1 + 0x2b4) = 0;
  Entry__7CPollerFP7CPolObjib(iGpffff858c + 0x48,param_1,0x80,0);
  return param_1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x004dcb70  __dt__9ParamDispFv
 * C++: ParamDisp::__dt()
 * size: 0x114 bytes
 * --------------------------------------------------------------------------- */
int __dt__9ParamDispFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x14) = 0x40a5f0;
    *(undefined4 *)(param_1 + 0x28) = 0x40a600;
    *(undefined4 *)(param_1 + 0x34) = 0x40a610;
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
 * JP: 0x004dcc90  Destruct__9ParamDispFv
 * C++: ParamDisp::Destruct()
 * size: 0x48 bytes
 * --------------------------------------------------------------------------- */
void Destruct__9ParamDispFv(int param_1)

{
  Dispose__7CPollerFP7CPolObj(iGpffff858c + 0x48,param_1);
  (**(code **)(*(int *)(param_1 + 0x34) + 0xc))();
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x004dcce0  Polling__9ParamDispFv
 * C++: ParamDisp::Polling()
 * size: 0x1870 bytes
 * --------------------------------------------------------------------------- */
/* WARNING: Removing unreachable block (ram,0x004dd7e0) */
/* WARNING: Removing unreachable block (ram,0x004ddb38) */
/* WARNING: Removing unreachable block (ram,0x004dde90) */

undefined8 Polling__9ParamDispFv(int param_1)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  float fVar6;
  float fStack_1c;
  float fStack_18;
  float fStack_14;
  
  fStack_14 = *(float *)(iGpffff86b4 + 0x38);
  if ((*(byte *)(iGpffff86b4 + 0x24) & 1) != 0) {
    fStack_14 = 0.0;
  }
  *(float *)(param_1 + 0x48) = *(float *)(param_1 + 0x48) + fStack_14;
  *(int *)(param_1 + 0x40) = *(int *)(param_1 + 0x40) + 1;
  for (iVar3 = 0; iVar3 < *(int *)(param_1 + 0x68); iVar3 = iVar3 + 1) {
    if (*(int *)(param_1 + 0x2b4) == 0) {
      if (*(float *)(param_1 + iVar3 * 4 + 0x24c) != 0.0) {
        iVar1 = param_1 + iVar3 * 4;
        *(float *)(iVar1 + 0x24c) =
             *(float *)(iVar1 + 0x24c) - *(float *)(iGpffff86b4 + 0x38) * 37.5 * 60.0;
        if (*(float *)(param_1 + iVar3 * 4 + 0x24c) < 0.0) {
          *(undefined4 *)(param_1 + iVar3 * 4 + 0x24c) = 0;
        }
        *(undefined4 *)(param_1 + 0x280) = 3;
      }
      fStack_18 = (float)(*(int *)(param_1 + 0x68) - iVar3) * -25.0;
      if (*(float *)(param_1 + iVar3 * 4 + 0x284) != fStack_18) {
        fStack_18 = fStack_18 - *(float *)(param_1 + iVar3 * 4 + 0x284);
        if (*(float *)(iGpffff86b4 + 0x38) * 12.5 * 60.0 < fStack_18) {
          fStack_18 = *(float *)(iGpffff86b4 + 0x38) * 12.5 * 60.0;
        }
        else if (fStack_18 < *(float *)(iGpffff86b4 + 0x38) * -12.5 * 60.0) {
          fStack_18 = *(float *)(iGpffff86b4 + 0x38) * -12.5 * 60.0;
        }
        iVar1 = param_1 + iVar3 * 4;
        *(float *)(iVar1 + 0x284) = *(float *)(iVar1 + 0x284) + fStack_18;
        *(undefined4 *)(param_1 + 0x280) = 3;
      }
    }
    else if ((*(uint *)(param_1 + 0x2b4) & 1 << (*(uint *)(param_1 + iVar3 * 4 + 0x6c) & 0x1f)) == 0
            ) {
      if (*(float *)(param_1 + iVar3 * 4 + 0x24c) < 300.0) {
        iVar1 = param_1 + iVar3 * 4;
        *(float *)(iVar1 + 0x24c) =
             *(float *)(iVar1 + 0x24c) + *(float *)(iGpffff86b4 + 0x38) * 37.5 * 60.0;
        if (300.0 <= *(float *)(param_1 + iVar3 * 4 + 0x24c)) {
          *(undefined4 *)(param_1 + iVar3 * 4 + 0x24c) = 0x43960000;
        }
        *(undefined4 *)(param_1 + 0x280) = 3;
      }
    }
    else {
      if (*(float *)(param_1 + iVar3 * 4 + 0x24c) != 0.0) {
        iVar1 = param_1 + iVar3 * 4;
        *(float *)(iVar1 + 0x24c) =
             *(float *)(iVar1 + 0x24c) - *(float *)(iGpffff86b4 + 0x38) * 37.5 * 60.0;
        if (*(float *)(param_1 + iVar3 * 4 + 0x24c) < 0.0) {
          *(undefined4 *)(param_1 + iVar3 * 4 + 0x24c) = 0;
        }
        *(undefined4 *)(param_1 + 0x280) = 3;
      }
      iVar4 = 0;
      for (iVar1 = 0; iVar1 < *(int *)(param_1 + 0x68); iVar1 = iVar1 + 1) {
        if ((*(uint *)(param_1 + 0x2b4) & 1 << (*(uint *)(param_1 + iVar1 * 4 + 0x6c) & 0x1f)) != 0)
        {
          iVar4 = iVar4 + 1;
        }
      }
      if (iVar4 == *(int *)(param_1 + 0x68)) {
        fStack_18 = (float)(*(int *)(param_1 + 0x68) - iVar3) * -25.0;
        if (*(float *)(param_1 + iVar3 * 4 + 0x284) != fStack_18) {
          fStack_18 = fStack_18 - *(float *)(param_1 + iVar3 * 4 + 0x284);
          if (*(float *)(iGpffff86b4 + 0x38) * 12.5 * 60.0 < fStack_18) {
            fStack_18 = *(float *)(iGpffff86b4 + 0x38) * 12.5 * 60.0;
          }
          else if (fStack_18 < *(float *)(iGpffff86b4 + 0x38) * -12.5 * 60.0) {
            fStack_18 = *(float *)(iGpffff86b4 + 0x38) * -12.5 * 60.0;
          }
          iVar1 = param_1 + iVar3 * 4;
          *(float *)(iVar1 + 0x284) = *(float *)(iVar1 + 0x284) + fStack_18;
          *(undefined4 *)(param_1 + 0x280) = 3;
        }
      }
      else if ((long)*(int *)(param_1 + iVar3 * 4 + 0x6c) == (long)*(char *)(iGpffff86b4 + 0x2c)) {
        if (*(float *)(param_1 + iVar3 * 4 + 0x284) != -25.0) {
          fStack_18 = -25.0 - *(float *)(param_1 + iVar3 * 4 + 0x284);
          if (*(float *)(iGpffff86b4 + 0x38) * 12.5 * 60.0 < fStack_18) {
            fStack_18 = *(float *)(iGpffff86b4 + 0x38) * 12.5 * 60.0;
          }
          else if (fStack_18 < *(float *)(iGpffff86b4 + 0x38) * -12.5 * 60.0) {
            fStack_18 = *(float *)(iGpffff86b4 + 0x38) * -12.5 * 60.0;
          }
          iVar1 = param_1 + iVar3 * 4;
          *(float *)(iVar1 + 0x284) = *(float *)(iVar1 + 0x284) + fStack_18;
          *(undefined4 *)(param_1 + 0x280) = 3;
        }
      }
      else {
        iVar5 = 0;
        for (iVar1 = 0; iVar1 <= iVar3; iVar1 = iVar1 + 1) {
          if (((*(uint *)(param_1 + 0x2b4) & 1 << (*(uint *)(param_1 + iVar1 * 4 + 0x6c) & 0x1f)) !=
               0) && ((long)*(int *)(param_1 + iVar1 * 4 + 0x6c) !=
                      (long)*(char *)(iGpffff86b4 + 0x2c))) {
            iVar5 = iVar5 + 1;
          }
        }
        fStack_18 = (float)(iVar4 - (iVar5 + -1)) * -25.0;
        if (*(float *)(param_1 + iVar3 * 4 + 0x284) != fStack_18) {
          fStack_18 = fStack_18 - *(float *)(param_1 + iVar3 * 4 + 0x284);
          if (*(float *)(iGpffff86b4 + 0x38) * 12.5 * 60.0 < fStack_18) {
            fStack_18 = *(float *)(iGpffff86b4 + 0x38) * 12.5 * 60.0;
          }
          else if (fStack_18 < *(float *)(iGpffff86b4 + 0x38) * -12.5 * 60.0) {
            fStack_18 = *(float *)(iGpffff86b4 + 0x38) * -12.5 * 60.0;
          }
          iVar1 = param_1 + iVar3 * 4;
          *(float *)(iVar1 + 0x284) = *(float *)(iVar1 + 0x284) + fStack_18;
          *(undefined4 *)(param_1 + 0x280) = 3;
        }
      }
    }
    if (*(float *)(param_1 + iVar3 * 0x18 + 0x9c) !=
        (float)(int)*(short *)(iGpffff86b4 + *(int *)(param_1 + iVar3 * 4 + 0x6c) * 0x4f0 + 0x124))
    {
      if (*(float *)(param_1 + iVar3 * 0x18 + 0xa8) !=
          (float)(int)*(short *)(iGpffff86b4 + *(int *)(param_1 + iVar3 * 4 + 0x6c) * 0x4f0 + 0x124)
         ) {
        *(undefined4 *)(param_1 + iVar3 * 0xc + 0x1bc) = 0;
      }
      *(float *)(param_1 + iVar3 * 0x18 + 0xa8) =
           (float)(int)*(short *)(iGpffff86b4 + *(int *)(param_1 + iVar3 * 4 + 0x6c) * 0x4f0 + 0x124
                                 );
      iVar1 = param_1 + iVar3 * 0xc;
      *(float *)(iVar1 + 0x1bc) = *(float *)(iVar1 + 0x1bc) + fStack_14;
      *(undefined4 *)(param_1 + iVar3 * 0xc + 0x1bc) = 0x3f800000;
      if (*(float *)(iGpffff86b4 + 0x38) == 0.0) {
        fStack_18 = 0.0;
      }
      else {
        fStack_18 = ((float)*(ushort *)
                             (iGpffff86b4 + *(int *)(param_1 + iVar3 * 4 + 0x6c) * 0x4f0 + 0x122) /
                    46.0) * *(float *)(iGpffff86b4 + 0x38) * 30.0;
        if (46.0 < fStack_18) {
          fStack_18 = 46.0;
        }
      }
      fStack_1c = *(float *)(param_1 + iVar3 * 0x18 + 0xa8) -
                  *(float *)(param_1 + iVar3 * 0x18 + 0x9c);
      if (0.0 < fStack_1c) {
        if (fStack_18 < fStack_1c) {
          fStack_1c = fStack_18;
        }
      }
      else if ((fStack_1c < 0.0) && (fStack_1c < -fStack_18)) {
        fStack_1c = -fStack_18;
      }
      iVar1 = param_1 + iVar3 * 0x18;
      *(float *)(iVar1 + 0x9c) = *(float *)(iVar1 + 0x9c) + fStack_1c;
      *(undefined4 *)(param_1 + 0x280) = 3;
    }
    if (*(float *)(param_1 + iVar3 * 0x18 + 0xa0) !=
        (float)(int)*(short *)(iGpffff86b4 + *(int *)(param_1 + iVar3 * 4 + 0x6c) * 0x4f0 + 0x128))
    {
      if (*(float *)(param_1 + iVar3 * 0x18 + 0xac) !=
          (float)(int)*(short *)(iGpffff86b4 + *(int *)(param_1 + iVar3 * 4 + 0x6c) * 0x4f0 + 0x128)
         ) {
        *(undefined4 *)(param_1 + iVar3 * 0xc + 0x1c0) = 0;
      }
      *(float *)(param_1 + iVar3 * 0x18 + 0xac) =
           (float)(int)*(short *)(iGpffff86b4 + *(int *)(param_1 + iVar3 * 4 + 0x6c) * 0x4f0 + 0x128
                                 );
      iVar1 = param_1 + iVar3 * 0xc;
      *(float *)(iVar1 + 0x1c0) = *(float *)(iVar1 + 0x1c0) + fStack_14;
      *(undefined4 *)(param_1 + iVar3 * 0xc + 0x1c0) = 0x3f800000;
      if (*(float *)(iGpffff86b4 + 0x38) == 0.0) {
        fStack_18 = 0.0;
      }
      else {
        fStack_18 = ((float)*(ushort *)
                             (iGpffff86b4 + *(int *)(param_1 + iVar3 * 4 + 0x6c) * 0x4f0 + 0x126) /
                    46.0) * *(float *)(iGpffff86b4 + 0x38) * 30.0;
        if (46.0 < fStack_18) {
          fStack_18 = 46.0;
        }
      }
      fStack_1c = *(float *)(param_1 + iVar3 * 0x18 + 0xac) -
                  *(float *)(param_1 + iVar3 * 0x18 + 0xa0);
      if (0.0 < fStack_1c) {
        if (fStack_18 < fStack_1c) {
          fStack_1c = fStack_18;
        }
      }
      else if ((fStack_1c < 0.0) && (fStack_1c < -fStack_18)) {
        fStack_1c = -fStack_18;
      }
      iVar1 = param_1 + iVar3 * 0x18;
      *(float *)(iVar1 + 0xa0) = *(float *)(iVar1 + 0xa0) + fStack_1c;
      *(undefined4 *)(param_1 + 0x280) = 3;
    }
    if (*(float *)(param_1 + iVar3 * 0x18 + 0xa4) !=
        (float)(int)*(short *)(iGpffff86b4 + *(int *)(param_1 + iVar3 * 4 + 0x6c) * 0x4f0 + 300)) {
      if (*(float *)(param_1 + iVar3 * 0x18 + 0xb0) !=
          (float)(int)*(short *)(iGpffff86b4 + *(int *)(param_1 + iVar3 * 4 + 0x6c) * 0x4f0 + 300))
      {
        *(undefined4 *)(param_1 + iVar3 * 0xc + 0x1c4) = 0;
      }
      *(float *)(param_1 + iVar3 * 0x18 + 0xb0) =
           (float)(int)*(short *)(iGpffff86b4 + *(int *)(param_1 + iVar3 * 4 + 0x6c) * 0x4f0 + 300);
      iVar1 = param_1 + iVar3 * 0xc;
      *(float *)(iVar1 + 0x1c4) = *(float *)(iVar1 + 0x1c4) + fStack_14;
      *(undefined4 *)(param_1 + iVar3 * 0xc + 0x1c4) = 0x3f800000;
      if (*(float *)(iGpffff86b4 + 0x38) == 0.0) {
        fStack_18 = 0.0;
      }
      else {
        fStack_18 = ((float)*(ushort *)
                             (iGpffff86b4 + *(int *)(param_1 + iVar3 * 4 + 0x6c) * 0x4f0 + 0x12a) /
                    46.0) * *(float *)(iGpffff86b4 + 0x38) * 30.0;
        if (46.0 < fStack_18) {
          fStack_18 = 46.0;
        }
      }
      fStack_1c = *(float *)(param_1 + iVar3 * 0x18 + 0xb0);
      if (fStack_1c < 0.0) {
        fStack_1c = 0.0;
      }
      fStack_1c = fStack_1c - *(float *)(param_1 + iVar3 * 0x18 + 0xa4);
      if (0.0 < fStack_1c) {
        if (fStack_18 < fStack_1c) {
          fStack_1c = fStack_18;
        }
      }
      else if ((fStack_1c < 0.0) && (fStack_1c < -fStack_18)) {
        fStack_1c = -fStack_18;
      }
      iVar1 = param_1 + iVar3 * 0x18;
      *(float *)(iVar1 + 0xa4) = *(float *)(iVar1 + 0xa4) + fStack_1c;
      *(undefined4 *)(param_1 + 0x280) = 3;
    }
  }
  iVar3 = *(int *)(param_1 + 0x38);
  if (iVar3 == 4) {
    *(float *)(param_1 + 0x60) = *(float *)(param_1 + 0x60) + fStack_14 * 37.5 * 60.0;
    if (300.0 <= *(float *)(param_1 + 0x60)) {
      *(undefined4 *)(param_1 + 0x38) = 1;
      *(undefined4 *)(param_1 + 0x3c) = 0;
      *(undefined4 *)(param_1 + 0x60) = 0x43960000;
      *(undefined2 *)(param_1 + 100) = *(undefined2 *)(param_1 + 0x66);
      *(undefined4 *)(param_1 + 0x68) = 0;
      for (uVar2 = 0; (int)uVar2 < 0xc; uVar2 = uVar2 + 1) {
        if ((*(uint *)(param_1 + 0x27c) & 1 << (uVar2 & 0x1f)) != 0) {
          *(uint *)(param_1 + *(int *)(param_1 + 0x68) * 4 + 0x6c) = uVar2;
          fVar6 = (float)(int)*(short *)(iGpffff86b4 + uVar2 * 0x4f0 + 0x124);
          *(float *)(param_1 + *(int *)(param_1 + 0x68) * 0x18 + 0xa8) = fVar6;
          *(float *)(param_1 + *(int *)(param_1 + 0x68) * 0x18 + 0x9c) = fVar6;
          fVar6 = (float)(int)*(short *)(iGpffff86b4 + uVar2 * 0x4f0 + 0x128);
          *(float *)(param_1 + *(int *)(param_1 + 0x68) * 0x18 + 0xac) = fVar6;
          *(float *)(param_1 + *(int *)(param_1 + 0x68) * 0x18 + 0xa0) = fVar6;
          fVar6 = (float)(int)*(short *)(iGpffff86b4 + uVar2 * 0x4f0 + 300);
          *(float *)(param_1 + *(int *)(param_1 + 0x68) * 0x18 + 0xb0) = fVar6;
          *(float *)(param_1 + *(int *)(param_1 + 0x68) * 0x18 + 0xa4) = fVar6;
          if (*(float *)(param_1 + *(int *)(param_1 + 0x68) * 0x18 + 0xa4) < 0.0) {
            *(undefined4 *)(param_1 + *(int *)(param_1 + 0x68) * 0x18 + 0xa4) = 0;
          }
          *(undefined4 *)(param_1 + *(int *)(param_1 + 0x68) * 0xc + 0x1c4) = 0x3f800000;
          *(undefined4 *)(param_1 + *(int *)(param_1 + 0x68) * 0xc + 0x1c0) = 0x3f800000;
          *(undefined4 *)(param_1 + *(int *)(param_1 + 0x68) * 0xc + 0x1bc) = 0x3f800000;
          *(undefined4 *)(param_1 + *(int *)(param_1 + 0x68) * 4 + 0x24c) = 0;
          for (iVar3 = 0; iVar3 < *(int *)(param_1 + 0x68); iVar3 = iVar3 + 1) {
            iVar1 = param_1 + iVar3 * 4;
            *(float *)(iVar1 + 0x284) = *(float *)(iVar1 + 0x284) - 25.0;
          }
          *(undefined4 *)(param_1 + *(int *)(param_1 + 0x68) * 4 + 0x284) = 0xc1c80000;
          *(int *)(param_1 + 0x68) = *(int *)(param_1 + 0x68) + 1;
        }
      }
    }
    *(undefined4 *)(param_1 + 0x280) = 3;
  }
  else if (iVar3 == 3) {
    *(float *)(param_1 + 0x60) = *(float *)(param_1 + 0x60) + fStack_14 * 37.5 * 60.0;
    if (300.0 <= *(float *)(param_1 + 0x60)) {
      *(undefined4 *)(param_1 + 0x38) = 0;
      *(undefined4 *)(param_1 + 0x3c) = 0;
      *(undefined4 *)(param_1 + 0x60) = 0x43960000;
    }
    *(undefined4 *)(param_1 + 0x280) = 3;
  }
  else if ((iVar3 != 2) && (iVar3 == 1)) {
    *(float *)(param_1 + 0x60) = *(float *)(param_1 + 0x60) - fStack_14 * 37.5 * 60.0;
    if (*(float *)(param_1 + 0x60) <= 0.0) {
      *(undefined4 *)(param_1 + 0x38) = 2;
      *(undefined4 *)(param_1 + 0x3c) = 0;
      *(undefined4 *)(param_1 + 0x60) = 0;
    }
    *(undefined4 *)(param_1 + 0x280) = 3;
  }
  return 0;
}

/* ---------------------------------------------------------------------------
 * JP: 0x004de550  MakePacket__9ParamDispFv
 * C++: ParamDisp::MakePacket()
 * size: 0xa6c4 bytes
 * --------------------------------------------------------------------------- */
/* WARNING: Removing unreachable block (ram,0x004e70f4) */
/* WARNING: Removing unreachable block (ram,0x004e6204) */
/* WARNING: Removing unreachable block (ram,0x004e2220) */
/* WARNING: Removing unreachable block (ram,0x004e22bc) */
/* WARNING: Removing unreachable block (ram,0x004e62f8) */
/* WARNING: Removing unreachable block (ram,0x004e415c) */
/* WARNING: Removing unreachable block (ram,0x004e2714) */
/* WARNING: Removing unreachable block (ram,0x004e71e8) */
/* WARNING: Removing unreachable block (ram,0x004e2b4c) */
/* WARNING: Removing unreachable block (ram,0x004e20e0) */
/* WARNING: Removing unreachable block (ram,0x004e4234) */

void MakePacket__9ParamDispFv(int param_1)

{
  bool bVar1;
  ushort uVar2;
  short sVar3;
  undefined1 in_zero_qw [16];
  undefined4 uVar4;
  int iVar5;
  ulong *puVar6;
  uint extraout_v0_lo;
  int iVar7;
  undefined8 uVar8;
  ulong uVar9;
  long lVar10;
  uint extraout_v0_hi;
  ulong uVar11;
  undefined8 uVar12;
  undefined1 auVar13 [16];
  undefined1 auVar14 [16];
  short sVar15;
  short sVar16;
  ushort uVar17;
  int iVar18;
  undefined4 *puVar19;
  int iVar20;
  uint uVar21;
  int iVar22;
  undefined4 in_a2_udw;
  undefined4 in_register_0000006c;
  short sVar23;
  uint uVar24;
  float fVar25;
  float fVar26;
  uint uStack_350;
  uint uStack_2f0;
  uint uStack_160;
  float fStack_4c;
  float fStack_40;
  float fStack_38;
  float fStack_34;
  float fStack_28;
  int iStack_1c;
  uint uStack_18;
  
  iVar7 = *(int *)(param_1 + 0x68) * 0x71 + 1;
  bVar1 = *(int *)(param_1 + 0x44) == 0;
  uVar24 = (uint)bVar1;
  if ((*(int *)(param_1 + (uint)bVar1 * 4 + 0x18) != 0) &&
     (*(int *)(param_1 + uVar24 * 4 + 0x4c) != iVar7)) {
    __dla__FPv(*(undefined4 *)(param_1 + uVar24 * 4 + 0x18));
    *(undefined4 *)(param_1 + uVar24 * 4 + 0x18) = 0;
    *(undefined4 *)(param_1 + uVar24 * 4 + 0x4c) = 0;
  }
  iVar5 = 0;
  if (*(int *)(param_1 + uVar24 * 4 + 0x18) == 0) {
    uVar4 = __nwa__FUi(iVar7 * 0x10);
    *(undefined4 *)(param_1 + uVar24 * 4 + 0x18) = uVar4;
    *(int *)(param_1 + uVar24 * 4 + 0x4c) = iVar7;
    *(undefined4 *)(param_1 + 0x280) = 3;
    iVar7 = *(int *)(param_1 + uVar24 * 4 + 0x18);
    for (iVar18 = 0; iVar18 < *(int *)(param_1 + 0x68); iVar18 = iVar18 + 1) {
      *(undefined4 *)(iVar7 + iVar5 * 0x10) = 0x10000000;
      *(undefined4 *)(iVar7 + iVar5 * 0x10 + 4) = 0;
      *(undefined4 *)(iVar7 + iVar5 * 0x10 + 8) = 0;
      *(undefined4 *)(iVar7 + iVar5 * 0x10 + 0xc) = 0x50000000;
      *(undefined8 *)(iVar7 + (iVar5 + 1) * 0x10) = 0x2000000000000001;
      *(undefined8 *)(iVar7 + (iVar5 + 1) * 0x10 + 8) = 0xee;
      *(undefined8 *)(iVar7 + (iVar5 + 2) * 0x10) = 0x23003;
      *(undefined8 *)(iVar7 + (iVar5 + 2) * 0x10 + 8) = 0x47;
      *(undefined8 *)(iVar7 + (iVar5 + 3) * 0x10) = 0x44;
      *(undefined8 *)(iVar7 + (iVar5 + 3) * 0x10 + 8) = 0x42;
      auVar13._8_4_ = in_a2_udw;
      auVar13._0_8_ = 0xe400000000000001;
      auVar13._12_4_ = in_register_0000006c;
      auVar13 = _pcpyld(in_zero_qw,auVar13);
      *(long *)(iVar7 + (iVar5 + 4) * 0x10) = auVar13._0_8_;
      *(undefined8 *)(iVar7 + (iVar5 + 4) * 0x10 + 8) = 0x41414141c1c1f0;
      *(undefined8 *)(iVar7 + (iVar5 + 5) * 0x10) = 0x4c;
      *(undefined8 *)(iVar7 + (iVar5 + 5) * 0x10 + 8) = 0;
      *(undefined8 *)(iVar7 + (iVar5 + 6) * 0x10) = 0;
      *(undefined8 *)(iVar7 + (iVar5 + 7) * 0x10) = 0;
      *(undefined8 *)(iVar7 + (iVar5 + 8) * 0x10) = 0x40000000;
      *(undefined8 *)(iVar7 + (iVar5 + 9) * 0x10) = 0x40000000;
      *(undefined8 *)(iVar7 + (iVar5 + 10) * 0x10) = 0x40000000;
      *(undefined8 *)(iVar7 + (iVar5 + 0xb) * 0x10) = 0x40000000;
      auVar14._8_4_ = auVar13._8_4_;
      auVar14._0_8_ = 0xc400000000000001;
      auVar14._12_4_ = auVar13._12_4_;
      auVar14 = _pcpyld(in_zero_qw,auVar14);
      *(long *)(iVar7 + (iVar5 + 0xc) * 0x10) = auVar14._0_8_;
      *(undefined8 *)(iVar7 + (iVar5 + 0xc) * 0x10 + 8) = 0x414141c1c1f0;
      *(undefined8 *)(iVar7 + (iVar5 + 0xd) * 0x10) = 0x4c;
      *(undefined8 *)(iVar7 + (iVar5 + 0xd) * 0x10 + 8) = 0;
      *(undefined8 *)(iVar7 + (iVar5 + 0xe) * 0x10) = 0x40ffff00;
      *(undefined8 *)(iVar7 + (iVar5 + 0xf) * 0x10) = 0x40ffff00;
      *(undefined8 *)(iVar7 + (iVar5 + 0x10) * 0x10) = 0x40ffff00;
      *(undefined8 *)(iVar7 + (iVar5 + 0x11) * 0x10) = 0x40ff0000;
      *(undefined8 *)(iVar7 + (iVar5 + 0x12) * 0x10) = 0x40ff0000;
      iVar20 = iVar5 + 0x13;
      *(undefined4 *)(iVar7 + iVar20 * 0x10) = 0x50000000;
      *(undefined4 *)(iVar7 + iVar20 * 0x10 + 4) =
           *(undefined4 *)
            (*(int *)(iGpffff86b4 + 0x4230) +
             (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x4230) + 10) * 4 + 0xc);
      *(undefined4 *)(iVar7 + iVar20 * 0x10 + 8) = 0;
      *(undefined4 *)(iVar7 + iVar20 * 0x10 + 0xc) = 0;
      *(undefined4 *)(iVar7 + (iVar5 + 0x14) * 0x10) = 0x10000000;
      *(undefined4 *)(iVar7 + (iVar5 + 0x14) * 0x10 + 4) = 0;
      *(undefined4 *)(iVar7 + (iVar5 + 0x14) * 0x10 + 8) = 0;
      *(undefined4 *)(iVar7 + (iVar5 + 0x14) * 0x10 + 0xc) = 0x50000000;
      *(undefined8 *)(iVar7 + (iVar5 + 0x15) * 0x10) = 0x4000000000000001;
      *(undefined8 *)(iVar7 + (iVar5 + 0x15) * 0x10 + 8) = 0x68ee;
      *(undefined8 *)(iVar7 + (iVar5 + 0x16) * 0x10) = 1;
      *(undefined8 *)(iVar7 + (iVar5 + 0x16) * 0x10 + 8) = 0x3f;
      *(undefined8 *)(iVar7 + (iVar5 + 0x17) * 0x10) = 0x60;
      *(undefined8 *)(iVar7 + (iVar5 + 0x17) * 0x10 + 8) = 0x14;
      *(undefined8 *)(iVar7 + (iVar5 + 0x18) * 0x10) = 5;
      *(undefined8 *)(iVar7 + (iVar5 + 0x18) * 0x10 + 8) = 0;
      uVar8 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x4230),1);
      *(undefined8 *)(iVar7 + (iVar5 + 0x19) * 0x10) = uVar8;
      *(undefined8 *)(iVar7 + (iVar5 + 0x19) * 0x10 + 8) = 0;
      *(undefined8 *)(iVar7 + (iVar5 + 0x1a) * 0x10) = 0x6400000000000006;
      *(undefined8 *)(iVar7 + (iVar5 + 0x1a) * 0x10 + 8) = 0x43c310;
      *(undefined8 *)(iVar7 + (iVar5 + 0x1b) * 0x10) = 0x156;
      *(undefined8 *)(iVar7 + (iVar5 + 0x1b) * 0x10 + 8) = 0x80808080;
      *(undefined8 *)(iVar7 + (iVar5 + 0x1c) * 0x10) = 0x800000;
      *(undefined8 *)(iVar7 + (iVar5 + 0x1d) * 0x10) = 0x1000330;
      *(undefined8 *)(iVar7 + (iVar5 + 0x1e) * 0x10) = 0x156;
      *(undefined8 *)(iVar7 + (iVar5 + 0x1e) * 0x10 + 8) = 0x80808080;
      *(undefined8 *)(iVar7 + (iVar5 + 0x1f) * 0x10) = 0x800330;
      *(undefined8 *)(iVar7 + (iVar5 + 0x20) * 0x10) = 0x1000660;
      *(undefined8 *)(iVar7 + (iVar5 + 0x21) * 0x10) = 0x156;
      *(undefined8 *)(iVar7 + (iVar5 + 0x21) * 0x10 + 8) = 0x80808080;
      *(undefined8 *)(iVar7 + (iVar5 + 0x22) * 0x10) = 0x800660;
      *(undefined8 *)(iVar7 + (iVar5 + 0x23) * 0x10) = 0x1000990;
      *(undefined8 *)(iVar7 + (iVar5 + 0x24) * 0x10) = 0x156;
      *(undefined8 *)(iVar7 + (iVar5 + 0x24) * 0x10 + 8) = 0x80808080;
      *(undefined8 *)(iVar7 + (iVar5 + 0x25) * 0x10) = 0x20;
      *(undefined8 *)(iVar7 + (iVar5 + 0x27) * 0x10) = 0x156;
      *(undefined8 *)(iVar7 + (iVar5 + 0x27) * 0x10 + 8) = 0x80808080;
      *(undefined8 *)(iVar7 + (iVar5 + 0x28) * 0x10) = 0x350;
      *(undefined8 *)(iVar7 + (iVar5 + 0x2a) * 0x10) = 0x156;
      *(undefined8 *)(iVar7 + (iVar5 + 0x2a) * 0x10 + 8) = 0x80808080;
      *(undefined8 *)(iVar7 + (iVar5 + 0x2b) * 0x10) = 0x680;
      iVar20 = iVar5 + 0x2d;
      *(undefined4 *)(iVar7 + iVar20 * 0x10) = 0x50000000;
      *(undefined4 *)(iVar7 + iVar20 * 0x10 + 4) =
           *(undefined4 *)
            (*(int *)(iGpffff86b4 + 0x4228) +
             (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x4228) + 10) * 4 + 0xc);
      *(undefined4 *)(iVar7 + iVar20 * 0x10 + 8) = 0;
      *(undefined4 *)(iVar7 + iVar20 * 0x10 + 0xc) = 0;
      *(undefined4 *)(iVar7 + (iVar5 + 0x2e) * 0x10) = 0x10000000;
      *(undefined4 *)(iVar7 + (iVar5 + 0x2e) * 0x10 + 4) = 0;
      *(undefined4 *)(iVar7 + (iVar5 + 0x2e) * 0x10 + 8) = 0;
      *(undefined4 *)(iVar7 + (iVar5 + 0x2e) * 0x10 + 0xc) = 0x50000000;
      *(undefined8 *)(iVar7 + (iVar5 + 0x2f) * 0x10) = 0x3000000000000001;
      *(undefined8 *)(iVar7 + (iVar5 + 0x2f) * 0x10 + 8) = 0x6ee;
      *(undefined8 *)(iVar7 + (iVar5 + 0x30) * 0x10) = 1;
      *(undefined8 *)(iVar7 + (iVar5 + 0x30) * 0x10 + 8) = 0x3f;
      uVar9 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x4228),1);
      *(ulong *)(iVar7 + (iVar5 + 0x31) * 0x10) = uVar9 & 0xfffffffc0fffff | 0x2000000001300000;
      *(undefined8 *)(iVar7 + (iVar5 + 0x31) * 0x10 + 8) = 0x16;
      *(ulong *)(iVar7 + (iVar5 + 0x32) * 0x10) = uVar9 & 0xffffffffffffff | 0x100000000000000;
      *(undefined8 *)(iVar7 + (iVar5 + 0x32) * 0x10 + 8) = 0;
      *(undefined8 *)(iVar7 + (iVar5 + 0x33) * 0x10) = 0x6400000000000002;
      *(undefined8 *)(iVar7 + (iVar5 + 0x33) * 0x10 + 8) = 0x43c310;
      *(undefined8 *)(iVar7 + (iVar5 + 0x34) * 0x10) = 0x156;
      *(undefined8 *)(iVar7 + (iVar5 + 0x34) * 0x10 + 8) = 0x80000000;
      *(undefined8 *)(iVar7 + (iVar5 + 0x37) * 0x10) = 0x156;
      *(undefined8 *)(iVar7 + (iVar5 + 0x37) * 0x10 + 8) = 0x80808080;
      iVar20 = iVar5 + 0x3a;
      *(undefined4 *)(iVar7 + iVar20 * 0x10) = 0x50000000;
      *(undefined4 *)(iVar7 + iVar20 * 0x10 + 4) =
           *(undefined4 *)
            (*(int *)(iGpffff86b4 + 0x422c) +
             (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x422c) + 10) * 4 + 0xc);
      *(undefined4 *)(iVar7 + iVar20 * 0x10 + 8) = 0;
      *(undefined4 *)(iVar7 + iVar20 * 0x10 + 0xc) = 0;
      *(undefined4 *)(iVar7 + (iVar5 + 0x3b) * 0x10) = 0x10000000;
      *(undefined4 *)(iVar7 + (iVar5 + 0x3b) * 0x10 + 4) = 0;
      *(undefined4 *)(iVar7 + (iVar5 + 0x3b) * 0x10 + 8) = 0;
      *(undefined4 *)(iVar7 + (iVar5 + 0x3b) * 0x10 + 0xc) = 0x50000000;
      *(undefined8 *)(iVar7 + (iVar5 + 0x3c) * 0x10) = 0x2000000000000001;
      *(undefined8 *)(iVar7 + (iVar5 + 0x3c) * 0x10 + 8) = 0x6e;
      *(undefined8 *)(iVar7 + (iVar5 + 0x3d) * 0x10) = 1;
      *(undefined8 *)(iVar7 + (iVar5 + 0x3d) * 0x10 + 8) = 0x3f;
      uVar8 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x422c),1);
      *(undefined8 *)(iVar7 + (iVar5 + 0x3e) * 0x10) = uVar8;
      *(undefined8 *)(iVar7 + (iVar5 + 0x3e) * 0x10 + 8) = 0;
      *(undefined8 *)(iVar7 + (iVar5 + 0x3f) * 0x10) = 0x6400000000000003;
      *(undefined8 *)(iVar7 + (iVar5 + 0x3f) * 0x10 + 8) = 0x43c310;
      *(undefined8 *)(iVar7 + (iVar5 + 0x40) * 0x10) = 0x156;
      *(undefined8 *)(iVar7 + (iVar5 + 0x40) * 0x10 + 8) = 0x80808080;
      *(undefined8 *)(iVar7 + (iVar5 + 0x41) * 0x10) = 0x100010;
      *(undefined8 *)(iVar7 + (iVar5 + 0x42) * 0x10) = 0xb00130;
      *(undefined8 *)(iVar7 + (iVar5 + 0x43) * 0x10) = 0x156;
      *(undefined8 *)(iVar7 + (iVar5 + 0x43) * 0x10 + 8) = 0x80808080;
      *(undefined8 *)(iVar7 + (iVar5 + 0x44) * 0x10) = 0x100140;
      *(undefined8 *)(iVar7 + (iVar5 + 0x45) * 0x10) = 0xb00260;
      *(undefined8 *)(iVar7 + (iVar5 + 0x46) * 0x10) = 0x156;
      *(undefined8 *)(iVar7 + (iVar5 + 0x46) * 0x10 + 8) = 0x80808080;
      *(undefined8 *)(iVar7 + (iVar5 + 0x47) * 0x10) = 0x100270;
      *(undefined8 *)(iVar7 + (iVar5 + 0x48) * 0x10) = 0xb00390;
      *(undefined8 *)(iVar7 + (iVar5 + 0x49) * 0x10) = 0x2400000000000001;
      *(undefined8 *)(iVar7 + (iVar5 + 0x49) * 0x10 + 8) = 0x10;
      *(undefined8 *)(iVar7 + (iVar5 + 0x4a) * 0x10) = 0x156;
      *(undefined8 *)(iVar7 + (iVar5 + 0x4b) * 0x10) = 0x4400000000000005;
      *(undefined8 *)(iVar7 + (iVar5 + 0x4b) * 0x10 + 8) = 0x43c3;
      *(undefined8 *)(iVar7 + (iVar5 + 0x56) * 0x10) = 0x2400000000000001;
      *(undefined8 *)(iVar7 + (iVar5 + 0x56) * 0x10 + 8) = 0x10;
      *(undefined8 *)(iVar7 + (iVar5 + 0x57) * 0x10) = 0x156;
      *(undefined8 *)(iVar7 + (iVar5 + 0x58) * 0x10) = 0x4400000000000003;
      *(undefined8 *)(iVar7 + (iVar5 + 0x58) * 0x10 + 8) = 0x43c3;
      *(undefined8 *)(iVar7 + (iVar5 + 0x5f) * 0x10) = 0x2400000000000001;
      *(undefined8 *)(iVar7 + (iVar5 + 0x5f) * 0x10 + 8) = 0x10;
      *(undefined8 *)(iVar7 + (iVar5 + 0x60) * 0x10) = 0x156;
      *(undefined8 *)(iVar7 + (iVar5 + 0x61) * 0x10) = 0x4400000000000003;
      *(undefined8 *)(iVar7 + (iVar5 + 0x61) * 0x10 + 8) = 0x43c3;
      iVar20 = iVar5 + 0x68;
      *(undefined4 *)(iVar7 + iVar20 * 0x10) = 0x50000000;
      *(undefined4 *)(iVar7 + iVar20 * 0x10 + 4) =
           *(undefined4 *)
            (*(int *)(iGpffff86b4 + 0x430c) +
             (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x430c) + 10) * 4 + 0xc);
      *(undefined4 *)(iVar7 + iVar20 * 0x10 + 8) = 0;
      *(undefined4 *)(iVar7 + iVar20 * 0x10 + 0xc) = 0;
      *(undefined4 *)(iVar7 + (iVar5 + 0x69) * 0x10) = 0x10000000;
      *(undefined4 *)(iVar7 + (iVar5 + 0x69) * 0x10 + 4) = 0;
      *(undefined4 *)(iVar7 + (iVar5 + 0x69) * 0x10 + 8) = 0;
      *(undefined4 *)(iVar7 + (iVar5 + 0x69) * 0x10 + 0xc) = 0x50000000;
      *(undefined8 *)(iVar7 + (iVar5 + 0x6a) * 0x10) = 0x2000000000000001;
      *(undefined8 *)(iVar7 + (iVar5 + 0x6a) * 0x10 + 8) = 0x6e;
      *(undefined8 *)(iVar7 + (iVar5 + 0x6b) * 0x10) = 1;
      *(undefined8 *)(iVar7 + (iVar5 + 0x6b) * 0x10 + 8) = 0x3f;
      uVar8 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x430c),1);
      *(undefined8 *)(iVar7 + (iVar5 + 0x6c) * 0x10) = uVar8;
      *(undefined8 *)(iVar7 + (iVar5 + 0x6c) * 0x10 + 8) = 0;
      *(undefined8 *)(iVar7 + (iVar5 + 0x6d) * 0x10) = 0x6400000000000001;
      *(undefined8 *)(iVar7 + (iVar5 + 0x6d) * 0x10 + 8) = 0x43c310;
      *(undefined8 *)(iVar7 + (iVar5 + 0x6e) * 0x10) = 0x156;
      *(undefined8 *)(iVar7 + (iVar5 + 0x6e) * 0x10 + 8) = 0x80808080;
      iVar5 = iVar5 + 0x71;
    }
  }
  iVar7 = *(int *)(param_1 + uVar24 * 4 + 0x18);
  if (300.0 <= *(float *)(param_1 + 0x60)) {
    *(int *)(param_1 + 0x54) = iVar7;
    *(uint *)(param_1 + 0x44) = uVar24;
    *(undefined4 *)(param_1 + 0x280) = 3;
  }
  else {
    iVar5 = 0;
    if ((((*(uint *)(param_1 + 0x280) & 1) == 0) && (!bVar1)) ||
       (((*(uint *)(param_1 + 0x280) & 2) == 0 && (bVar1)))) {
      for (iVar18 = 0; iVar18 < *(int *)(param_1 + 0x68); iVar18 = iVar18 + 1) {
        fVar26 = *(float *)(param_1 + iVar18 * 4 + 0x284) + 2230.0;
        if (-1 < (int)((long)((ulong)(uint)(int)*(short *)(iGpffff86b4 +
                                                           *(int *)(param_1 + iVar18 * 4 + 0x6c) *
                                                           0x4f0 + 0x58a) << 0x30) >> 0x3f)) {
          iVar20 = *(int *)(*(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 +
                                      0x58a) * 4 + 0x650d80);
          sVar23 = *(short *)(iVar20 + *(short *)(iGpffff86b4 +
                                                  *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 +
                                                 0x58c) * 8) * 0x12;
          sVar15 = *(short *)(iVar20 + *(short *)(iGpffff86b4 +
                                                  *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 +
                                                 0x58c) * 8 + 2) * 0x16;
          fVar25 = (*(float *)(param_1 + 0x60) + 2304.0 + *(float *)(param_1 + iVar18 * 4 + 0x24c))
                   - 25.8;
          fStack_40 = 9.0;
          if (*(float *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x594) < 0.25
             ) {
            fStack_40 = (float)sinf(*(float *)(iGpffff86b4 +
                                                          *(int *)(param_1 + iVar18 * 4 + 0x6c) *
                                                          0x4f0 + 0x594) * 4.0 * 1.5707964);
            fStack_40 = fStack_40 * 9.0;
          }
          else if (1.75 <= *(float *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 +
                                     0x594)) {
            fStack_40 = (float)sinf((2.0 - *(float *)(iGpffff86b4 +
                                                                 *(int *)(param_1 + iVar18 * 4 +
                                                                         0x6c) * 0x4f0 + 0x594)) *
                                               4.0 * 1.5707964);
            fStack_40 = fStack_40 * 9.0;
          }
          *(ulong *)(iVar7 + (iVar5 + 0x6f) * 0x10) =
               (long)((int)sVar23 << 4) |
               CONCAT44((int)(short)((uint)((int)sVar15 << 4) >> 0x10),(int)sVar15 << 0x14);
          uVar8 = __fixunssfdi((fVar26 + 1.0) * 16.0);
          uVar9 = __fixunssfdi((fVar25 - fStack_40) * 16.0);
          *(ulong *)(iVar7 + (iVar5 + 0x6f) * 0x10 + 8) =
               CONCAT44((int)((ulong)uVar8 >> 0x10),(int)uVar8 << 0x10) | uVar9;
          *(ulong *)(iVar7 + (iVar5 + 0x70) * 0x10) =
               (long)((sVar23 + 0x12) * 0x10) |
               CONCAT44((int)(short)((uint)((sVar15 + 0x16) * 0x10) >> 0x10),
                        (sVar15 + 0x16) * 0x100000);
          lVar10 = __fixunssfdi((fVar26 + 23.0) * 16.0);
          uVar9 = __fixunssfdi((fVar25 + fStack_40) * 16.0);
          *(ulong *)(iVar7 + (iVar5 + 0x70) * 0x10 + 8) =
               CONCAT44((int)((ulong)lVar10 >> 0x10),(int)(lVar10 << 0x10)) | uVar9;
        }
        iVar5 = iVar5 + 0x71;
      }
      *(undefined4 *)(param_1 + 0x54) = *(undefined4 *)(param_1 + (uint)bVar1 * 4 + 0x58);
      *(uint *)(param_1 + 0x44) = uVar24;
    }
    else {
      for (iVar18 = 0; iVar18 < *(int *)(param_1 + 0x68); iVar18 = iVar18 + 1) {
        fVar26 = *(float *)(param_1 + iVar18 * 4 + 0x284) + 2230.0;
        puVar19 = (undefined4 *)(iVar7 + iVar5 * 0x10);
        *(undefined4 *)(iVar7 + iVar5 * 0x10) = 0x10000000;
        *(undefined4 *)(iVar7 + iVar5 * 0x10 + 4) = 0;
        *(undefined4 *)(iVar7 + iVar5 * 0x10 + 8) = 0;
        *(undefined4 *)(iVar7 + iVar5 * 0x10 + 0xc) = 0x50000000;
        if ((*(byte *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0xb4) & 1) == 0
           ) {
          sVar23 = *(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x120);
          if (((CONCAT44((int)((long)((ulong)(uint)(int)sVar23 << 0x30) >> 0x3f),(int)sVar23) == 8)
              || (sVar23 = *(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 +
                                     0x120),
                 CONCAT44((int)(((long)sVar23 << 0x30) >> 0x3f),(int)sVar23) == 9)) ||
             (sVar23 = *(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 +
                                 0x120),
             CONCAT44((int)(((long)sVar23 << 0x30) >> 0x3f),(int)sVar23) == 10)) {
            fStack_28 = (*(float *)(param_1 + 0x60) + 2304.0 +
                        *(float *)(param_1 + iVar18 * 4 + 0x24c)) - 271.8;
          }
          else {
            fStack_28 = (*(float *)(param_1 + 0x60) + 2304.0 +
                        *(float *)(param_1 + iVar18 * 4 + 0x24c)) - 322.8;
          }
        }
        else {
          fStack_28 = (*(float *)(param_1 + 0x60) + 2304.0 +
                      *(float *)(param_1 + iVar18 * 4 + 0x24c)) - 280.8;
        }
        uVar9 = __fixunssfdi(fStack_28 * 16.0);
        lVar10 = __fixunssfdi(fVar26 * 16.0);
        *(ulong *)(iVar7 + (iVar5 + 6) * 0x10 + 8) =
             uVar9 | CONCAT44((int)((ulong)lVar10 >> 0x10),(int)(lVar10 << 0x10));
        lVar10 = __fixunssfdi((fVar26 + 24.0) * 16.0);
        uVar9 = __fixunssfdi(fStack_28 * 16.0);
        *(ulong *)(iVar7 + (iVar5 + 7) * 0x10 + 8) =
             uVar9 | CONCAT44((int)((ulong)lVar10 >> 0x10),(int)(lVar10 << 0x10));
        if ((*(byte *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0xb4) & 1) == 0
           ) {
          sVar23 = *(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x120);
          if (((CONCAT44((int)((long)((ulong)(uint)(int)sVar23 << 0x30) >> 0x3f),(int)sVar23) == 8)
              || (sVar23 = *(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 +
                                     0x120),
                 CONCAT44((int)(((long)sVar23 << 0x30) >> 0x3f),(int)sVar23) == 9)) ||
             (sVar23 = *(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 +
                                 0x120),
             CONCAT44((int)((long)((ulong)(uint)(int)sVar23 << 0x30) >> 0x3f),(int)sVar23) == 10)) {
            fStack_28 = (*(float *)(param_1 + 0x60) + 2304.0 +
                        *(float *)(param_1 + iVar18 * 4 + 0x24c)) - 183.79999;
          }
          else {
            fStack_28 = (*(float *)(param_1 + 0x60) + 2304.0 +
                        *(float *)(param_1 + iVar18 * 4 + 0x24c)) - 234.79999;
          }
        }
        else {
          fStack_28 = (*(float *)(param_1 + 0x60) + 2304.0 +
                      *(float *)(param_1 + iVar18 * 4 + 0x24c)) - 192.79999;
        }
        uVar9 = __fixunssfdi(fStack_28 * 16.0);
        lVar10 = __fixunssfdi(fVar26 * 16.0);
        *(ulong *)(iVar7 + (iVar5 + 8) * 0x10 + 8) = uVar9 | lVar10 << 0x10;
        lVar10 = __fixunssfdi((fVar26 + 24.0) * 16.0);
        uVar9 = __fixunssfdi(fStack_28 * 16.0);
        *(ulong *)(iVar7 + (iVar5 + 9) * 0x10 + 8) =
             uVar9 | CONCAT44((int)((ulong)lVar10 >> 0x10),(int)(lVar10 << 0x10));
        fVar25 = *(float *)(param_1 + 0x60) + 2304.0 + *(float *)(param_1 + iVar18 * 4 + 0x24c) +
                 16.0;
        uVar9 = __fixunssfdi(fVar25 * 16.0);
        lVar10 = __fixunssfdi(fVar26 * 16.0);
        *(ulong *)(iVar7 + (iVar5 + 10) * 0x10 + 8) = uVar9 | lVar10 << 0x10;
        lVar10 = __fixunssfdi((fVar26 + 24.0) * 16.0);
        uVar9 = __fixunssfdi(fVar25 * 16.0);
        *(ulong *)(iVar7 + (iVar5 + 0xb) * 0x10 + 8) =
             uVar9 | CONCAT44((int)((ulong)lVar10 >> 0x10),(int)(lVar10 << 0x10));
        puVar6 = (ulong *)(iVar7 + (iVar5 + 0xc) * 0x10);
        lVar10 = (long)*(char *)(iGpffff86b4 + 0x2c) << 0x38;
        if (((long)*(int *)(param_1 + iVar18 * 4 + 0x6c) ==
             CONCAT44((int)(lVar10 >> 0x3f),
                      CONCAT22((short)(lVar10 >> 0x3f),(short)*(char *)(iGpffff86b4 + 0x2c)))) &&
           (CONCAT44((int)(((long)*(short *)(param_1 + 100) << 0x30) >> 0x3f),
                     (int)*(short *)(param_1 + 100)) != 2)) {
          if ((*(byte *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0xb4) & 1) ==
              0) {
            sVar23 = *(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x120)
            ;
            if (((CONCAT44((int)((long)((ulong)(uint)(int)sVar23 << 0x30) >> 0x3f),(int)sVar23) == 8
                 ) || (*(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 +
                                 0x120) == 9)) ||
               (sVar23 = *(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 +
                                   0x120),
               CONCAT44((int)((long)((ulong)(uint)(int)sVar23 << 0x30) >> 0x3f),(int)sVar23) == 10))
            {
              fStack_28 = (*(float *)(param_1 + 0x60) + 2304.0 +
                          *(float *)(param_1 + iVar18 * 4 + 0x24c)) - 227.8;
            }
            else {
              fStack_28 = (*(float *)(param_1 + 0x60) + 2304.0 +
                          *(float *)(param_1 + iVar18 * 4 + 0x24c)) - 278.8;
            }
          }
          else {
            fStack_28 = (*(float *)(param_1 + 0x60) + 2304.0 +
                        *(float *)(param_1 + iVar18 * 4 + 0x24c)) - 192.8;
          }
          lVar10 = __fixunssfdi((fVar26 + 24.0) * 16.0);
          uVar9 = __fixunssfdi(fStack_28 * 16.0);
          *(ulong *)(iVar7 + (iVar5 + 0xe) * 0x10 + 8) =
               uVar9 | CONCAT44((int)((ulong)lVar10 >> 0x10),(int)(lVar10 << 0x10));
          if ((*(byte *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0xb4) & 1) ==
              0) {
            sVar23 = *(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x120)
            ;
            if (((CONCAT44((int)(((long)sVar23 << 0x30) >> 0x3f),(int)sVar23) == 8) ||
                (*(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x120) ==
                 9)) || (sVar23 = *(short *)(iGpffff86b4 +
                                             *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x120),
                        CONCAT44((int)((long)((ulong)(uint)(int)sVar23 << 0x30) >> 0x3f),(int)sVar23
                                ) == 10)) {
              fStack_28 = (*(float *)(param_1 + 0x60) + 2304.0 +
                          *(float *)(param_1 + iVar18 * 4 + 0x24c)) - 139.8;
            }
            else {
              fStack_28 = (*(float *)(param_1 + 0x60) + 2304.0 +
                          *(float *)(param_1 + iVar18 * 4 + 0x24c)) - 190.8;
            }
          }
          else {
            fStack_28 = (*(float *)(param_1 + 0x60) + 2304.0 +
                        *(float *)(param_1 + iVar18 * 4 + 0x24c)) - 104.8;
          }
          uVar9 = __fixunssfdi(fStack_28 * 16.0);
          lVar10 = __fixunssfdi(fVar26 * 16.0);
          *(ulong *)(iVar7 + (iVar5 + 0xf) * 0x10 + 8) = uVar9 | lVar10 << 0x10;
          lVar10 = __fixunssfdi((fVar26 + 24.0) * 16.0);
          uVar9 = __fixunssfdi(fStack_28 * 16.0);
          *(ulong *)(iVar7 + (iVar5 + 0x10) * 0x10 + 8) = uVar9 | lVar10 << 0x10;
          fVar25 = *(float *)(param_1 + 0x60) + 2304.0 + *(float *)(param_1 + iVar18 * 4 + 0x24c) +
                   16.0;
          uVar9 = __fixunssfdi(fVar25 * 16.0);
          lVar10 = __fixunssfdi(fVar26 * 16.0);
          *(ulong *)(iVar7 + (iVar5 + 0x11) * 0x10 + 8) = uVar9 | lVar10 << 0x10;
          uVar8 = __fixunssfdi((fVar26 + 24.0) * 16.0);
          __fixunssfdi(fVar25 * 16.0);
          iVar20 = iVar7 + (iVar5 + 0x12) * 0x10;
          *(uint *)(iVar20 + 8) = extraout_v0_lo | (int)uVar8 << 0x10;
          *(uint *)(iVar20 + 0xc) = extraout_v0_hi | (uint)((ulong)uVar8 >> 0x10);
        }
        else {
          *(undefined8 *)(iVar7 + (iVar5 + 0xe) * 0x10 + 8) = 0x71006f00;
          *(undefined8 *)(iVar7 + (iVar5 + 0xf) * 0x10 + 8) = 0x71006f00;
          *(undefined8 *)(iVar7 + (iVar5 + 0x10) * 0x10 + 8) = 0x71006f00;
          *(undefined8 *)(iVar7 + (iVar5 + 0x11) * 0x10 + 8) = 0x71006f00;
          *(undefined8 *)(iVar7 + (iVar5 + 0x12) * 0x10 + 8) = 0x71006f00;
        }
        *puVar6 = *puVar6 | 0x8000;
        *puVar19 = 0x10000012;
        puVar19[3] = 0x50000012;
        puVar19 = (undefined4 *)(iVar7 + (iVar5 + 0x14) * 0x10);
        puVar6 = (ulong *)(iVar7 + (iVar5 + 0x1a) * 0x10);
        if ((*(byte *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0xb4) & 1) == 0
           ) {
          sVar23 = *(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x120);
          if (((CONCAT44((int)((long)((ulong)(uint)(int)sVar23 << 0x30) >> 0x3f),(int)sVar23) == 8)
              || (sVar23 = *(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 +
                                     0x120),
                 CONCAT44((int)(((long)sVar23 << 0x30) >> 0x3f),(int)sVar23) == 9)) ||
             (*(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x120) == 10)
             ) {
            fStack_28 = (*(float *)(param_1 + 0x60) + 2304.0 +
                        *(float *)(param_1 + iVar18 * 4 + 0x24c)) - 136.8;
          }
          else {
            fStack_28 = (*(float *)(param_1 + 0x60) + 2304.0 +
                        *(float *)(param_1 + iVar18 * 4 + 0x24c)) - 187.8;
          }
          fStack_34 = 51.0;
        }
        else {
          fStack_28 = (*(float *)(param_1 + 0x60) + 2304.0 +
                      *(float *)(param_1 + iVar18 * 4 + 0x24c)) - 101.8;
          fStack_34 = 67.0;
        }
        lVar10 = __fixunssfdi((fVar26 + 15.0) * 16.0);
        uVar9 = __fixunssfdi(fStack_28 * 16.0);
        *(ulong *)(iVar7 + (iVar5 + 0x1c) * 0x10 + 8) =
             uVar9 | CONCAT44((int)((ulong)lVar10 >> 0x10),(int)(lVar10 << 0x10));
        lVar10 = __fixunssfdi((fVar26 + 23.0) * 16.0);
        uVar9 = __fixunssfdi((fStack_28 + fStack_34) * 16.0);
        *(ulong *)(iVar7 + (iVar5 + 0x1d) * 0x10 + 8) =
             CONCAT44((int)((ulong)lVar10 >> 0x10),(int)(lVar10 << 0x10)) | uVar9;
        if ((*(byte *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0xb4) & 1) == 0
           ) {
          sVar23 = *(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x120);
          if (((CONCAT44((int)((long)((ulong)(uint)(int)sVar23 << 0x30) >> 0x3f),(int)sVar23) == 8)
              || (*(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x120) ==
                  9)) ||
             (sVar23 = *(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 +
                                 0x120),
             CONCAT44((int)(((long)sVar23 << 0x30) >> 0x3f),(int)sVar23) == 10)) {
            fStack_28 = (*(float *)(param_1 + 0x60) + 2304.0 +
                        *(float *)(param_1 + iVar18 * 4 + 0x24c)) - 85.8;
          }
          else {
            fStack_28 = (*(float *)(param_1 + 0x60) + 2304.0 +
                        *(float *)(param_1 + iVar18 * 4 + 0x24c)) - 136.8;
          }
          uVar8 = __fixunssfdi((fVar26 + 15.0) * 16.0);
          uVar9 = __fixunssfdi(fStack_28 * 16.0);
          *(ulong *)(iVar7 + (iVar5 + 0x1f) * 0x10 + 8) =
               uVar9 | CONCAT44((int)((ulong)uVar8 >> 0x10),(int)uVar8 << 0x10);
          uVar9 = __fixunssfdi((fStack_28 + 51.0) * 16.0);
          lVar10 = __fixunssfdi((fVar26 + 23.0) * 16.0);
          *(ulong *)(iVar7 + (iVar5 + 0x20) * 0x10 + 8) = uVar9 | lVar10 << 0x10;
        }
        else {
          *(undefined8 *)(iVar7 + (iVar5 + 0x1f) * 0x10 + 8) = 0x71006f00;
          *(undefined8 *)(iVar7 + (iVar5 + 0x20) * 0x10 + 8) = 0x71006f00;
        }
        if ((*(byte *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0xb4) & 1) == 0
           ) {
          if (((*(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x120) == 8
               ) || (sVar23 = *(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0
                                        + 0x120),
                    CONCAT44((int)((long)((ulong)(uint)(int)sVar23 << 0x30) >> 0x3f),(int)sVar23) ==
                    9)) ||
             (sVar23 = *(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 +
                                 0x120),
             CONCAT44((int)((long)((ulong)(uint)(int)sVar23 << 0x30) >> 0x3f),(int)sVar23) == 10)) {
            *(undefined8 *)(iVar7 + (iVar5 + 0x22) * 0x10 + 8) = 0x71006f00;
            *(undefined8 *)(iVar7 + (iVar5 + 0x23) * 0x10 + 8) = 0x71006f00;
          }
          else {
            fVar25 = (*(float *)(param_1 + 0x60) + 2304.0 + *(float *)(param_1 + iVar18 * 4 + 0x24c)
                     ) - 85.8;
            uVar8 = __fixunssfdi((fVar26 + 15.0) * 16.0);
            uVar9 = __fixunssfdi(fVar25 * 16.0);
            *(ulong *)(iVar7 + (iVar5 + 0x22) * 0x10 + 8) =
                 uVar9 | CONCAT44((int)((ulong)uVar8 >> 0x10),(int)uVar8 << 0x10);
            uVar11 = __fixunssfdi((fVar25 + 51.0) * 16.0);
            lVar10 = __fixunssfdi((fVar26 + 23.0) * 16.0);
            uVar9 = uVar11 | CONCAT44((int)((ulong)lVar10 >> 0x10),(int)(lVar10 << 0x10));
            *(ulong *)(iVar7 + (iVar5 + 0x23) * 0x10 + 8) =
                 CONCAT44((int)(uVar9 >> 0x20),CONCAT22((short)(uVar9 >> 0x10),(short)uVar11));
          }
        }
        else {
          *(undefined8 *)(iVar7 + (iVar5 + 0x22) * 0x10 + 8) = 0x71006f00;
          *(undefined8 *)(iVar7 + (iVar5 + 0x23) * 0x10 + 8) = 0x71006f00;
        }
        if ((*(byte *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0xb4) & 1) == 0
           ) {
          sVar23 = *(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x120);
          if (((CONCAT44((int)(((long)sVar23 << 0x30) >> 0x3f),(int)sVar23) == 8) ||
              (sVar23 = *(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 +
                                  0x120),
              CONCAT44((int)(((long)sVar23 << 0x30) >> 0x3f),(int)sVar23) == 9)) ||
             (*(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x120) == 10)
             ) {
            fStack_28 = (*(float *)(param_1 + 0x60) + 2304.0 +
                        *(float *)(param_1 + iVar18 * 4 + 0x24c)) - 134.8;
          }
          else {
            fStack_28 = (*(float *)(param_1 + 0x60) + 2304.0 +
                        *(float *)(param_1 + iVar18 * 4 + 0x24c)) - 185.8;
          }
          fStack_38 = (*(float *)(param_1 + iVar18 * 0x18 + 0x9c) * 46.0) /
                      (float)*(ushort *)
                              (iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x122);
          fStack_34 = fStack_38;
        }
        else {
          fStack_28 = (*(float *)(param_1 + 0x60) + 2304.0 +
                      *(float *)(param_1 + iVar18 * 4 + 0x24c)) - 99.8;
          fStack_34 = (*(float *)(param_1 + iVar18 * 0x18 + 0x9c) * 62.0) /
                      (float)*(ushort *)
                              (iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x122);
          fStack_38 = (*(float *)(param_1 + iVar18 * 0x18 + 0x9c) * 46.0) /
                      (float)*(ushort *)
                              (iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x122);
        }
        if (fStack_34 < 0.0) {
          fStack_34 = 0.0;
        }
        lVar10 = __fixunssfdi((fVar26 + 15.0) * 16.0);
        uVar9 = __fixunssfdi(fStack_28 * 16.0);
        *(ulong *)(iVar7 + (iVar5 + 0x25) * 0x10 + 8) =
             uVar9 | CONCAT44((int)((ulong)lVar10 >> 0x10),(int)(lVar10 << 0x10));
        uVar9 = __fixunssfdi(fStack_38 * 16.0);
        *(ulong *)(iVar7 + (iVar5 + 0x26) * 0x10) = uVar9 | 0x800000;
        lVar10 = __fixunssfdi((fVar26 + 23.0) * 16.0);
        uVar9 = __fixunssfdi((fStack_28 + fStack_34) * 16.0);
        *(ulong *)(iVar7 + (iVar5 + 0x26) * 0x10 + 8) =
             CONCAT44((int)((ulong)lVar10 >> 0x10),(int)(lVar10 << 0x10)) | uVar9;
        if ((*(byte *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0xb4) & 1) == 0
           ) {
          sVar23 = *(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x120);
          if (((CONCAT44((int)((long)((ulong)(uint)(int)sVar23 << 0x30) >> 0x3f),(int)sVar23) == 8)
              || (sVar23 = *(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 +
                                     0x120),
                 CONCAT44((int)(((long)sVar23 << 0x30) >> 0x3f),(int)sVar23) == 9)) ||
             (*(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x120) == 10)
             ) {
            fStack_28 = (*(float *)(param_1 + 0x60) + 2304.0 +
                        *(float *)(param_1 + iVar18 * 4 + 0x24c)) - 83.8;
          }
          else {
            fStack_28 = (*(float *)(param_1 + 0x60) + 2304.0 +
                        *(float *)(param_1 + iVar18 * 4 + 0x24c)) - 134.8;
          }
          fStack_34 = (*(float *)(param_1 + iVar18 * 0x18 + 0xa0) * 46.0) /
                      (float)*(ushort *)
                              (iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x126);
          if (fStack_34 < 0.0) {
            fStack_34 = 0.0;
          }
          lVar10 = __fixunssfdi((fVar26 + 15.0) * 16.0);
          uVar9 = __fixunssfdi(fStack_28 * 16.0);
          *(ulong *)(iVar7 + (iVar5 + 0x28) * 0x10 + 8) =
               uVar9 | CONCAT44((int)((ulong)lVar10 >> 0x10),(int)(lVar10 << 0x10));
          uVar9 = __fixunssfdi((fStack_34 + 53.0) * 16.0);
          *(ulong *)(iVar7 + (iVar5 + 0x29) * 0x10) = uVar9 | 0x800000;
          lVar10 = __fixunssfdi((fVar26 + 23.0) * 16.0);
          uVar9 = __fixunssfdi((fStack_28 + fStack_34) * 16.0);
          *(ulong *)(iVar7 + (iVar5 + 0x29) * 0x10 + 8) =
               CONCAT44((int)((ulong)lVar10 >> 0x10),(int)(lVar10 << 0x10)) | uVar9;
        }
        else {
          *(undefined8 *)(iVar7 + (iVar5 + 0x28) * 0x10 + 8) = 0x71006f00;
          *(undefined8 *)(iVar7 + (iVar5 + 0x29) * 0x10) = 0x800640;
          *(undefined8 *)(iVar7 + (iVar5 + 0x29) * 0x10 + 8) = 0x71006f00;
        }
        if ((*(byte *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0xb4) & 1) == 0
           ) {
          sVar23 = *(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x120);
          if (((CONCAT44((int)((long)((ulong)(uint)(int)sVar23 << 0x30) >> 0x3f),(int)sVar23) == 8)
              || (sVar23 = *(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 +
                                     0x120),
                 CONCAT44((int)(((long)sVar23 << 0x30) >> 0x3f),(int)sVar23) == 9)) ||
             (sVar23 = *(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 +
                                 0x120),
             CONCAT44((int)((long)((ulong)(uint)(int)sVar23 << 0x30) >> 0x3f),(int)sVar23) == 10)) {
            *(undefined8 *)(iVar7 + (iVar5 + 0x2b) * 0x10 + 8) = 0x71006f00;
            *(undefined8 *)(iVar7 + (iVar5 + 0x2c) * 0x10 + 8) = 0x71006f00;
          }
          else {
            fVar25 = (*(float *)(param_1 + 0x60) + 2304.0 + *(float *)(param_1 + iVar18 * 4 + 0x24c)
                     ) - 83.8;
            fStack_34 = (*(float *)(param_1 + iVar18 * 0x18 + 0xa4) * 46.0) /
                        (float)*(ushort *)
                                (iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x12a
                                );
            if (fStack_34 < 0.0) {
              fStack_34 = 0.0;
            }
            lVar10 = __fixunssfdi((fVar26 + 15.0) * 16.0);
            uVar9 = __fixunssfdi(fVar25 * 16.0);
            *(ulong *)(iVar7 + (iVar5 + 0x2b) * 0x10 + 8) =
                 uVar9 | CONCAT44((int)((ulong)lVar10 >> 0x10),(int)(lVar10 << 0x10));
            uVar9 = __fixunssfdi((fStack_34 + 104.0) * 16.0);
            *(ulong *)(iVar7 + (iVar5 + 0x2c) * 0x10) = uVar9 | 0x800000;
            lVar10 = __fixunssfdi((fVar26 + 23.0) * 16.0);
            uVar9 = __fixunssfdi((fVar25 + fStack_34) * 16.0);
            *(ulong *)(iVar7 + (iVar5 + 0x2c) * 0x10 + 8) =
                 CONCAT44((int)((ulong)lVar10 >> 0x10),(int)(lVar10 << 0x10)) | uVar9;
          }
        }
        else {
          *(undefined8 *)(iVar7 + (iVar5 + 0x2b) * 0x10 + 8) = 0x71006f00;
          *(undefined8 *)(iVar7 + (iVar5 + 0x2c) * 0x10 + 8) = 0x71006f00;
        }
        *puVar6 = *puVar6 | 0x8000;
        *puVar19 = 0x10000018;
        puVar19[3] = 0x50000018;
        puVar19 = (undefined4 *)(iVar7 + (iVar5 + 0x2e) * 0x10);
        if ((*(byte *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0xb4) & 1) == 0
           ) {
          sVar23 = *(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x120);
          if (((CONCAT44((int)(((long)sVar23 << 0x30) >> 0x3f),(int)sVar23) == 8) ||
              (*(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x120) == 9)
              ) || (sVar23 = *(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0
                                       + 0x120),
                   CONCAT44((int)(((long)sVar23 << 0x30) >> 0x3f),(int)sVar23) == 10)) {
            fStack_28 = (*(float *)(param_1 + 0x60) + 2304.0 +
                        *(float *)(param_1 + iVar18 * 4 + 0x24c)) - 138.8;
          }
          else {
            fStack_28 = (*(float *)(param_1 + 0x60) + 2304.0 +
                        *(float *)(param_1 + iVar18 * 4 + 0x24c)) - 189.8;
          }
        }
        else {
          fStack_28 = (*(float *)(param_1 + 0x60) + 2304.0 +
                      *(float *)(param_1 + iVar18 * 4 + 0x24c)) - 103.8;
        }
        sVar23 = *(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x13c);
        sVar15 = *(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x13e);
        sVar3 = *(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x140) +
                sVar23;
        sVar16 = *(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x142) +
                 sVar15;
        *(long *)(iVar7 + (iVar5 + 0x35) * 0x10) =
             (long)((int)sVar23 << 4) | (long)((int)sVar15 << 4) << 0x10;
        uVar9 = __fixunssfdi(((fStack_28 - (float)((int)sVar3 - (int)sVar23) * 0.8) + 1.0) * 16.0
                               );
        lVar10 = __fixunssfdi((fVar26 + 2.0) * 16.0);
        *(ulong *)(iVar7 + (iVar5 + 0x35) * 0x10 + 8) = lVar10 << 0x10 | uVar9;
        *(ulong *)(iVar7 + (iVar5 + 0x36) * 0x10) =
             (long)((int)sVar3 << 4) |
             (ulong)CONCAT42((int)(short)((uint)((int)sVar16 << 4) >> 0x10),
                             (short)((int)sVar16 << 4)) << 0x10;
        uVar8 = __fixunssfdi((fVar26 + (float)((int)sVar16 - (int)sVar15) + 2.0) * 16.0);
        uVar9 = __fixunssfdi((fStack_28 + 1.0) * 16.0);
        *(ulong *)(iVar7 + (iVar5 + 0x36) * 0x10 + 8) =
             uVar9 | CONCAT44((int)((ulong)uVar8 >> 0x10),(int)uVar8 << 0x10);
        *(long *)(iVar7 + (iVar5 + 0x38) * 0x10) =
             (long)((int)sVar23 << 4) | (long)((int)sVar15 << 4) << 0x10;
        uVar9 = __fixunssfdi((fStack_28 - (float)((int)sVar3 - (int)sVar23) * 0.8) * 16.0);
        uVar8 = __fixunssfdi((fVar26 + 1.0) * 16.0);
        *(ulong *)(iVar7 + (iVar5 + 0x38) * 0x10 + 8) =
             CONCAT44((int)((ulong)uVar8 >> 0x10),(int)uVar8 << 0x10) | uVar9;
        *(ulong *)(iVar7 + (iVar5 + 0x39) * 0x10) =
             (long)((int)sVar3 << 4) |
             (ulong)CONCAT42((int)(short)((uint)((int)sVar16 << 4) >> 0x10),
                             (short)((int)sVar16 << 4)) << 0x10;
        lVar10 = __fixunssfdi((fVar26 + (float)((int)sVar16 - (int)sVar15) + 1.0) * 16.0);
        uVar9 = __fixunssfdi(fStack_28 * 16.0);
        *(ulong *)(iVar7 + (iVar5 + 0x39) * 0x10 + 8) =
             uVar9 | CONCAT44((int)((ulong)lVar10 >> 0x10),(int)(lVar10 << 0x10));
        *puVar6 = *puVar6 | 0x8000;
        *puVar19 = 0x1000000b;
        puVar19[3] = 0x5000000b;
        puVar19 = (undefined4 *)(iVar7 + (iVar5 + 0x3b) * 0x10);
        if ((*(byte *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0xb4) & 1) == 0
           ) {
          sVar23 = *(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x120);
          if (((CONCAT44((int)(((long)sVar23 << 0x30) >> 0x3f),(int)sVar23) == 8) ||
              (*(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x120) == 9)
              ) || (sVar23 = *(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0
                                       + 0x120),
                   CONCAT44((int)((long)((ulong)(uint)(int)sVar23 << 0x30) >> 0x3f),(int)sVar23) ==
                   10)) {
            fStack_28 = (*(float *)(param_1 + 0x60) + 2304.0 +
                        *(float *)(param_1 + iVar18 * 4 + 0x24c)) - 136.8;
          }
          else {
            fStack_28 = (*(float *)(param_1 + 0x60) + 2304.0 +
                        *(float *)(param_1 + iVar18 * 4 + 0x24c)) - 187.8;
          }
        }
        else {
          fStack_28 = (*(float *)(param_1 + 0x60) + 2304.0 +
                      *(float *)(param_1 + iVar18 * 4 + 0x24c)) - 101.8;
        }
        uVar9 = __fixunssfdi((fStack_28 + 1.0) * 16.0);
        lVar10 = __fixunssfdi((fVar26 + 1.0) * 16.0);
        *(ulong *)(iVar7 + (iVar5 + 0x41) * 0x10 + 8) = uVar9 | lVar10 << 0x10;
        uVar11 = __fixunssfdi((fStack_28 + 19.0) * 16.0);
        lVar10 = __fixunssfdi((fVar26 + 11.0) * 16.0);
        uVar9 = uVar11 | CONCAT44((int)((ulong)lVar10 >> 0x10),(int)(lVar10 << 0x10));
        *(ulong *)(iVar7 + (iVar5 + 0x42) * 0x10 + 8) =
             CONCAT44((int)(uVar9 >> 0x20),CONCAT22((short)(uVar9 >> 0x10),(short)uVar11));
        if ((*(byte *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0xb4) & 1) == 0
           ) {
          sVar23 = *(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x120);
          if (((CONCAT44((int)(((long)sVar23 << 0x30) >> 0x3f),(int)sVar23) == 8) ||
              (*(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x120) == 9)
              ) || (sVar23 = *(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0
                                       + 0x120),
                   CONCAT44((int)(((long)sVar23 << 0x30) >> 0x3f),(int)sVar23) == 10)) {
            fStack_28 = (*(float *)(param_1 + 0x60) + 2304.0 +
                        *(float *)(param_1 + iVar18 * 4 + 0x24c)) - 85.8;
          }
          else {
            fStack_28 = (*(float *)(param_1 + 0x60) + 2304.0 +
                        *(float *)(param_1 + iVar18 * 4 + 0x24c)) - 136.8;
          }
          uVar9 = __fixunssfdi((fStack_28 + 1.0) * 16.0);
          lVar10 = __fixunssfdi((fVar26 + 1.0) * 16.0);
          *(ulong *)(iVar7 + (iVar5 + 0x44) * 0x10 + 8) = uVar9 | lVar10 << 0x10;
          uVar11 = __fixunssfdi((fStack_28 + 19.0) * 16.0);
          lVar10 = __fixunssfdi((fVar26 + 11.0) * 16.0);
          uVar9 = uVar11 | CONCAT44((int)((ulong)lVar10 >> 0x10),(int)(lVar10 << 0x10));
          *(ulong *)(iVar7 + (iVar5 + 0x45) * 0x10 + 8) =
               CONCAT44((int)(uVar9 >> 0x20),CONCAT22((short)(uVar9 >> 0x10),(short)uVar11));
        }
        else {
          *(undefined8 *)(iVar7 + (iVar5 + 0x44) * 0x10 + 8) = 0x71006f00;
          *(undefined8 *)(iVar7 + (iVar5 + 0x45) * 0x10 + 8) = 0x71006f00;
        }
        if ((*(byte *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0xb4) & 1) == 0
           ) {
          sVar23 = *(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x120);
          if (((CONCAT44((int)(((long)sVar23 << 0x30) >> 0x3f),(int)sVar23) == 8) ||
              (*(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x120) == 9)
              ) || (sVar23 = *(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0
                                       + 0x120),
                   CONCAT44((int)(((long)sVar23 << 0x30) >> 0x3f),(int)sVar23) == 10)) {
            *(undefined8 *)(iVar7 + (iVar5 + 0x47) * 0x10 + 8) = 0x71006f00;
            *(undefined8 *)(iVar7 + (iVar5 + 0x48) * 0x10 + 8) = 0x71006f00;
          }
          else {
            fVar25 = (*(float *)(param_1 + 0x60) + 2304.0 + *(float *)(param_1 + iVar18 * 4 + 0x24c)
                     ) - 85.8;
            uVar9 = __fixunssfdi((fVar25 + 1.0) * 16.0);
            lVar10 = __fixunssfdi((fVar26 + 1.0) * 16.0);
            *(ulong *)(iVar7 + (iVar5 + 0x47) * 0x10 + 8) =
                 uVar9 | CONCAT44((int)((ulong)lVar10 >> 0x10),(int)(lVar10 << 0x10));
            uVar9 = __fixunssfdi((fVar25 + 19.0) * 16.0);
            lVar10 = __fixunssfdi((fVar26 + 11.0) * 16.0);
            *(ulong *)(iVar7 + (iVar5 + 0x48) * 0x10 + 8) = uVar9 | lVar10 << 0x10;
          }
        }
        else {
          *(undefined8 *)(iVar7 + (iVar5 + 0x47) * 0x10 + 8) = 0x71006f00;
          *(undefined8 *)(iVar7 + (iVar5 + 0x48) * 0x10 + 8) = 0x71006f00;
        }
        uStack_18 = (int)(uint)*(ushort *)
                                (iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x122
                                ) >> 1;
        if ((uStack_18 < 2) &&
           (2 < *(ushort *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x122))) {
          uStack_18 = 2;
        }
        iStack_1c = (int)(uint)*(ushort *)
                                (iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x122
                                ) >> 2;
        if ((iStack_1c == 0) &&
           (1 < *(ushort *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x122))) {
          iStack_1c = 1;
        }
        if ((long)(int)uStack_18 <
            (long)*(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x124)) {
          *(undefined8 *)(iVar7 + (iVar5 + 0x4a) * 0x10 + 8) = 0x80808080;
        }
        else if ((long)iStack_1c <
                 (long)*(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 +
                                 0x124)) {
          *(undefined8 *)(iVar7 + (iVar5 + 0x4a) * 0x10 + 8) = 0x80008080;
        }
        else {
          *(undefined8 *)(iVar7 + (iVar5 + 0x4a) * 0x10 + 8) = 0x80000080;
        }
        iVar20 = iVar5 + 0x4c;
        if ((*(byte *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0xb4) & 1) == 0
           ) {
          if (((*(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x120) == 8
               ) || (sVar23 = *(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0
                                        + 0x120),
                    CONCAT44((int)(((long)sVar23 << 0x30) >> 0x3f),(int)sVar23) == 9)) ||
             (*(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x120) == 10)
             ) {
            fStack_28 = (*(float *)(param_1 + 0x60) + 2304.0 +
                        *(float *)(param_1 + iVar18 * 4 + 0x24c)) - 88.8;
          }
          else {
            fStack_28 = (*(float *)(param_1 + 0x60) + 2304.0 +
                        *(float *)(param_1 + iVar18 * 4 + 0x24c)) - 139.8;
          }
        }
        else {
          fStack_28 = (*(float *)(param_1 + 0x60) + 2304.0 +
                      *(float *)(param_1 + iVar18 * 4 + 0x24c)) - 37.8;
        }
        sVar23 = *(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x124);
        if (CONCAT44((int)((long)((ulong)(uint)(int)sVar23 << 0x30) >> 0x3f),(int)sVar23) < 10000) {
          if ((*(byte *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0xb4) & 1) !=
              0) {
            uVar2 = *(ushort *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0xba);
            uVar17 = uVar2 & 7;
            if (((short)uVar2 < 0) && ((uVar2 & 7) != 0)) {
              uVar17 = uVar17 - 8;
            }
            if (((uint)*(byte *)(ourBtlSaveDat +
                                 ((int)*(short *)(iGpffff86b4 +
                                                  *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 +
                                                 0xba) >> 3) + 0xdcf) & 1 << (uVar17 & 0x1f)) == 0)
            goto LAB_004e4860;
          }
          *(undefined8 *)(iVar7 + iVar20 * 0x10 + 8) = 0x71006f00;
          *(undefined8 *)(iVar7 + (iVar5 + 0x4d) * 0x10 + 8) = 0x71006f00;
        }
        else {
LAB_004e4860:
          sVar23 = *(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x124);
          sVar23 = (short)((int)((int)sVar23 / 10000 + ((int)sVar23 >> 0x1f) +
                                (uint)((ushort)(sVar23 >> 0xf) >> 0xf)) % 10);
          if ((*(byte *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0xb4) & 1) !=
              0) {
            uVar2 = *(ushort *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0xba);
            uStack_2f0 = (uint)(uVar2 & 7);
            if (((int)(((long)(short)uVar2 << 0x30) >> 0x3f) < 0) && (uStack_2f0 != 0)) {
              uStack_2f0 = uStack_2f0 - 8;
            }
            if (((uint)*(byte *)(ourBtlSaveDat +
                                 ((int)*(short *)(iGpffff86b4 +
                                                  *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 +
                                                 0xba) >> 3) + 0xdcf) & 1 << (uStack_2f0 & 0x1f)) ==
                0) {
              sVar23 = 0xb;
            }
          }
          *(ulong *)(iVar7 + iVar20 * 0x10) =
               (long)(((sVar23 * 4 + (int)sVar23) * 2 + (int)sVar23 + 0x4d) * 0x10) | 0x100000;
          uVar11 = __fixunssfdi((fStack_28 - 40.0) * 16.0);
          lVar10 = __fixunssfdi((fVar26 + 1.0) * 16.0);
          uVar9 = uVar11 | lVar10 << 0x10;
          *(ulong *)(iVar7 + iVar20 * 0x10 + 8) =
               CONCAT44((int)(uVar9 >> 0x20),CONCAT22((short)(uVar9 >> 0x10),(short)uVar11));
          *(ulong *)(iVar7 + (iVar5 + 0x4d) * 0x10) =
               (long)(((sVar23 + 1) * 0xb + 0x4d) * 0x10) | 0xf00000;
          uVar11 = __fixunssfdi((fStack_28 - 31.2) * 16.0);
          lVar10 = __fixunssfdi((fVar26 + 15.0) * 16.0);
          uVar9 = uVar11 | lVar10 << 0x10;
          *(ulong *)(iVar7 + (iVar5 + 0x4d) * 0x10 + 8) =
               CONCAT44((int)(uVar9 >> 0x20),CONCAT22((short)(uVar9 >> 0x10),(short)uVar11));
        }
        if (*(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x124) < 1000)
        {
          if ((*(byte *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0xb4) & 1) !=
              0) {
            sVar23 = *(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0xba);
            uVar21 = (int)sVar23 & 7;
            if (((int)((long)((ulong)(uint)(int)sVar23 << 0x30) >> 0x3f) < 0) && (uVar21 != 0)) {
              uVar21 = uVar21 - 8 & 0xffff;
            }
            if (((uint)*(byte *)(ourBtlSaveDat +
                                 ((int)*(short *)(iGpffff86b4 +
                                                  *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 +
                                                 0xba) >> 3) + 0xdcf) & 1 << (uVar21 & 0x1f)) == 0)
            goto LAB_004e4e28;
          }
          *(undefined8 *)(iVar7 + (iVar5 + 0x4e) * 0x10 + 8) = 0x71006f00;
          *(undefined8 *)(iVar7 + (iVar5 + 0x4f) * 0x10 + 8) = 0x71006f00;
        }
        else {
LAB_004e4e28:
          sVar23 = *(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x124);
          sVar23 = (short)((int)((int)sVar23 / 1000 + ((int)sVar23 >> 0x1f) +
                                (uint)((ushort)(sVar23 >> 0xf) >> 0xf)) % 10);
          if ((*(byte *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0xb4) & 1) !=
              0) {
            uVar11 = (ulong)*(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 +
                                      0xba);
            uVar9 = uVar11 & 7;
            uVar21 = (uint)uVar9;
            if (((long)uVar11 < 0) && (uVar9 != 0)) {
              uVar21 = uVar21 - 8;
            }
            if (((uint)*(byte *)(ourBtlSaveDat +
                                 ((int)*(short *)(iGpffff86b4 +
                                                  *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 +
                                                 0xba) >> 3) + 0xdcf) & 1 << (uVar21 & 0x1f)) == 0)
            {
              sVar23 = 0xb;
            }
          }
          *(ulong *)(iVar7 + (iVar5 + 0x4e) * 0x10) =
               (long)((sVar23 * 10 + (int)sVar23 + 0x4d) * 0x10) | 0x100000;
          uVar9 = __fixunssfdi((fStack_28 - 32.0) * 16.0);
          lVar10 = __fixunssfdi((fVar26 + 1.0) * 16.0);
          *(ulong *)(iVar7 + (iVar5 + 0x4e) * 0x10 + 8) = uVar9 | lVar10 << 0x10;
          *(ulong *)(iVar7 + (iVar5 + 0x4f) * 0x10) =
               (long)(((sVar23 + 1) * 0xb + 0x4d) * 0x10) | 0xf00000;
          uVar9 = __fixunssfdi((fStack_28 - 23.2) * 16.0);
          lVar10 = __fixunssfdi((fVar26 + 15.0) * 16.0);
          *(ulong *)(iVar7 + (iVar5 + 0x4f) * 0x10 + 8) =
               uVar9 | CONCAT44((int)((ulong)lVar10 >> 0x10),(int)(lVar10 << 0x10));
        }
        if (*(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x124) < 100) {
          if ((*(byte *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0xb4) & 1) !=
              0) {
            uVar2 = *(ushort *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0xba);
            uVar17 = uVar2 & 7;
            if (((int)(((long)(short)uVar2 << 0x30) >> 0x3f) < 0) && ((uVar2 & 7) != 0)) {
              uVar17 = uVar17 - 8;
            }
            if (((uint)*(byte *)(ourBtlSaveDat +
                                 ((int)*(short *)(iGpffff86b4 +
                                                  *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 +
                                                 0xba) >> 3) + 0xdcf) & 1 << (uVar17 & 0x1f)) == 0)
            goto LAB_004e5408;
          }
          *(undefined8 *)(iVar7 + (iVar5 + 0x50) * 0x10 + 8) = 0x71006f00;
          *(undefined8 *)(iVar7 + (iVar5 + 0x51) * 0x10 + 8) = 0x71006f00;
        }
        else {
LAB_004e5408:
          sVar23 = (short)(((int)*(short *)(iGpffff86b4 +
                                            *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x124) /
                           100) % 10);
          if ((*(byte *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0xb4) & 1) !=
              0) {
            uVar2 = *(ushort *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0xba);
            uVar17 = uVar2 & 7;
            if (((int)(((long)(short)uVar2 << 0x30) >> 0x3f) < 0) && ((uVar2 & 7) != 0)) {
              uVar17 = uVar17 - 8;
            }
            if (((uint)*(byte *)(ourBtlSaveDat +
                                 ((int)*(short *)(iGpffff86b4 +
                                                  *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 +
                                                 0xba) >> 3) + 0xdcf) & 1 << (uVar17 & 0x1f)) == 0)
            {
              sVar23 = 0xb;
            }
          }
          *(ulong *)(iVar7 + (iVar5 + 0x50) * 0x10) =
               (long)((sVar23 * 0xb + 0x4d) * 0x10) | 0x100000;
          uVar11 = __fixunssfdi((fStack_28 - 24.0) * 16.0);
          lVar10 = __fixunssfdi((fVar26 + 1.0) * 16.0);
          uVar9 = uVar11 | lVar10 << 0x10;
          *(ulong *)(iVar7 + (iVar5 + 0x50) * 0x10 + 8) =
               CONCAT44((int)(uVar9 >> 0x20),CONCAT22((short)(uVar9 >> 0x10),(short)uVar11));
          *(ulong *)(iVar7 + (iVar5 + 0x51) * 0x10) =
               (long)(((sVar23 + 1) * 0xb + 0x4d) * 0x10) | 0xf00000;
          uVar11 = __fixunssfdi((fStack_28 - 15.2) * 16.0);
          lVar10 = __fixunssfdi((fVar26 + 15.0) * 16.0);
          uVar9 = uVar11 | lVar10 << 0x10;
          *(ulong *)(iVar7 + (iVar5 + 0x51) * 0x10 + 8) =
               CONCAT44((int)(uVar9 >> 0x20),CONCAT22((short)(uVar9 >> 0x10),(short)uVar11));
        }
        if (*(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x124) < 10) {
          if ((*(byte *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0xb4) & 1) !=
              0) {
            uVar11 = (ulong)*(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 +
                                      0xba);
            uVar9 = uVar11 & 7;
            uVar21 = (uint)uVar9;
            if (((long)uVar11 < 0) && (uVar9 != 0)) {
              uVar21 = uVar21 - 8;
            }
            if (((uint)*(byte *)(ourBtlSaveDat +
                                 ((int)*(short *)(iGpffff86b4 +
                                                  *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 +
                                                 0xba) >> 3) + 0xdcf) & 1 << (uVar21 & 0x1f)) == 0)
            goto LAB_004e59c8;
          }
          *(undefined8 *)(iVar7 + (iVar5 + 0x52) * 0x10 + 8) = 0x71006f00;
          *(undefined8 *)(iVar7 + (iVar5 + 0x53) * 0x10 + 8) = 0x71006f00;
        }
        else {
LAB_004e59c8:
          sVar23 = (short)(((int)*(short *)(iGpffff86b4 +
                                            *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x124) /
                           10) % 10);
          if ((*(byte *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0xb4) & 1) !=
              0) {
            sVar15 = *(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0xba);
            uStack_160 = (int)sVar15 & 7;
            if (((int)(((long)sVar15 << 0x30) >> 0x3f) < 0) && (((int)sVar15 & 7U) != 0)) {
              uStack_160 = uStack_160 - 8;
            }
            if (((uint)*(byte *)(ourBtlSaveDat +
                                 ((int)*(short *)(iGpffff86b4 +
                                                  *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 +
                                                 0xba) >> 3) + 0xdcf) & 1 << (uStack_160 & 0x1f)) ==
                0) {
              sVar23 = 0xb;
            }
          }
          *(ulong *)(iVar7 + (iVar5 + 0x52) * 0x10) =
               (long)((sVar23 * 0xb + 0x4d) * 0x10) | 0x100000;
          uVar11 = __fixunssfdi((fStack_28 - 16.0) * 16.0);
          lVar10 = __fixunssfdi((fVar26 + 1.0) * 16.0);
          uVar9 = uVar11 | CONCAT44((int)((ulong)lVar10 >> 0x10),(int)(lVar10 << 0x10));
          *(ulong *)(iVar7 + (iVar5 + 0x52) * 0x10 + 8) =
               CONCAT44((int)(uVar9 >> 0x20),CONCAT22((short)(uVar9 >> 0x10),(short)uVar11));
          *(ulong *)(iVar7 + (iVar5 + 0x53) * 0x10) =
               (long)(((sVar23 + 1) * 0xb + 0x4d) * 0x10) | 0xf00000;
          uVar9 = __fixunssfdi((fStack_28 - 7.2000003) * 16.0);
          lVar10 = __fixunssfdi((fVar26 + 15.0) * 16.0);
          *(ulong *)(iVar7 + (iVar5 + 0x53) * 0x10 + 8) = uVar9 | lVar10 << 0x10;
        }
        sVar23 = *(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x124) %
                 10;
        if ((*(byte *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0xb4) & 1) != 0
           ) {
          sVar15 = *(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0xba);
          uStack_350 = (int)sVar15 & 7;
          if (((int)((long)((ulong)(uint)(int)sVar15 << 0x30) >> 0x3f) < 0) && (uStack_350 != 0)) {
            uStack_350 = uStack_350 - 8;
          }
          if (((uint)*(byte *)(ourBtlSaveDat +
                               ((int)*(short *)(iGpffff86b4 +
                                                *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0xba
                                               ) >> 3) + 0xdcf) & 1 << (uStack_350 & 0x1f)) == 0) {
            sVar23 = 0xb;
          }
        }
        *(ulong *)(iVar7 + (iVar5 + 0x54) * 0x10) = (long)((sVar23 * 0xb + 0x4d) * 0x10) | 0x100000;
        uVar9 = __fixunssfdi((fStack_28 - 8.0) * 16.0);
        lVar10 = __fixunssfdi((fVar26 + 1.0) * 16.0);
        *(ulong *)(iVar7 + (iVar5 + 0x54) * 0x10 + 8) = uVar9 | lVar10 << 0x10;
        *(ulong *)(iVar7 + (iVar5 + 0x55) * 0x10) =
             (long)(((sVar23 + 1) * 0xb + 0x4d) * 0x10) | 0xf00000;
        uVar9 = __fixunssfdi((fStack_28 + 0.8) * 16.0);
        lVar10 = __fixunssfdi((fVar26 + 15.0) * 16.0);
        *(ulong *)(iVar7 + (iVar5 + 0x55) * 0x10 + 8) = uVar9 | lVar10 << 0x10;
        uStack_18 = (int)(uint)*(ushort *)
                                (iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x126
                                ) >> 1;
        if ((uStack_18 < 2) &&
           (2 < *(ushort *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x126))) {
          uStack_18 = 2;
        }
        iStack_1c = (int)(uint)*(ushort *)
                                (iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x126
                                ) >> 2;
        if ((iStack_1c == 0) &&
           (1 < *(ushort *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x126))) {
          iStack_1c = 1;
        }
        sVar23 = *(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x128);
        if ((long)(int)uStack_18 < CONCAT44((int)(((long)sVar23 << 0x30) >> 0x3f),(int)sVar23)) {
          *(undefined8 *)(iVar7 + (iVar5 + 0x57) * 0x10 + 8) = 0x80808080;
        }
        else {
          sVar23 = *(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x128);
          if ((long)iStack_1c < CONCAT44((int)(((long)sVar23 << 0x30) >> 0x3f),(int)sVar23)) {
            *(undefined8 *)(iVar7 + (iVar5 + 0x57) * 0x10 + 8) = 0x80008080;
          }
          else {
            *(undefined8 *)(iVar7 + (iVar5 + 0x57) * 0x10 + 8) = 0x80000080;
          }
        }
        iVar20 = iVar5 + 0x59;
        if ((*(byte *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0xb4) & 1) == 0
           ) {
          sVar23 = *(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x120);
          if (((CONCAT44((int)((long)((ulong)(uint)(int)sVar23 << 0x30) >> 0x3f),(int)sVar23) == 8)
              || (*(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x120) ==
                  9)) ||
             (sVar23 = *(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 +
                                 0x120),
             CONCAT44((int)((long)((ulong)(uint)(int)sVar23 << 0x30) >> 0x3f),(int)sVar23) == 10)) {
            fStack_28 = (*(float *)(param_1 + 0x60) + 2304.0 +
                        *(float *)(param_1 + iVar18 * 4 + 0x24c)) - 37.8;
          }
          else {
            fStack_28 = (*(float *)(param_1 + 0x60) + 2304.0 +
                        *(float *)(param_1 + iVar18 * 4 + 0x24c)) - 88.8;
          }
        }
        sVar23 = *(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x128);
        if ((CONCAT44((int)((long)((ulong)(uint)(int)sVar23 << 0x30) >> 0x3f),(int)sVar23) < 100) ||
           ((*(byte *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0xb4) & 1) != 0
           )) {
          *(undefined8 *)(iVar7 + iVar20 * 0x10 + 8) = 0x71006f00;
          *(undefined8 *)(iVar7 + (iVar5 + 0x5a) * 0x10 + 8) = 0x71006f00;
        }
        else {
          sVar23 = *(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x128);
          sVar23 = (short)((int)((int)sVar23 / 100 + ((int)sVar23 >> 0x1f) +
                                (uint)((ushort)(sVar23 >> 0xf) >> 0xf)) % 10);
          *(ulong *)(iVar7 + iVar20 * 0x10) = (long)((sVar23 * 0xb + 0x4d) * 0x10) | 0x100000;
          uVar9 = __fixunssfdi((fStack_28 - 24.0) * 16.0);
          lVar10 = __fixunssfdi((fVar26 + 1.0) * 16.0);
          *(ulong *)(iVar7 + iVar20 * 0x10 + 8) =
               uVar9 | CONCAT44((int)((ulong)lVar10 >> 0x10),(int)(lVar10 << 0x10));
          *(ulong *)(iVar7 + (iVar5 + 0x5a) * 0x10) =
               (long)(((sVar23 + 1) * 0xb + 0x4d) * 0x10) | 0xf00000;
          uVar9 = __fixunssfdi((fStack_28 - 15.2) * 16.0);
          lVar10 = __fixunssfdi((fVar26 + 15.0) * 16.0);
          *(ulong *)(iVar7 + (iVar5 + 0x5a) * 0x10 + 8) = uVar9 | lVar10 << 0x10;
        }
        if ((*(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x128) < 10)
           || ((*(byte *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0xb4) & 1)
               != 0)) {
          *(undefined8 *)(iVar7 + (iVar5 + 0x5b) * 0x10 + 8) = 0x71006f00;
          *(undefined8 *)(iVar7 + (iVar5 + 0x5c) * 0x10 + 8) = 0x71006f00;
        }
        else {
          sVar23 = (short)(((int)*(short *)(iGpffff86b4 +
                                            *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x128) /
                           10) % 10);
          *(ulong *)(iVar7 + (iVar5 + 0x5b) * 0x10) =
               (long)((sVar23 * 0xb + 0x4d) * 0x10) | 0x100000;
          uVar9 = __fixunssfdi((fStack_28 - 16.0) * 16.0);
          lVar10 = __fixunssfdi((fVar26 + 1.0) * 16.0);
          *(ulong *)(iVar7 + (iVar5 + 0x5b) * 0x10 + 8) =
               uVar9 | CONCAT44((int)((ulong)lVar10 >> 0x10),(int)(lVar10 << 0x10));
          *(ulong *)(iVar7 + (iVar5 + 0x5c) * 0x10) =
               (long)(((sVar23 + 1) * 0xb + 0x4d) * 0x10) | 0xf00000;
          uVar9 = __fixunssfdi((fStack_28 - 7.2000003) * 16.0);
          lVar10 = __fixunssfdi((fVar26 + 15.0) * 16.0);
          *(ulong *)(iVar7 + (iVar5 + 0x5c) * 0x10 + 8) = uVar9 | lVar10 << 0x10;
        }
        if ((*(byte *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0xb4) & 1) == 0
           ) {
          sVar23 = *(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x128) %
                   10;
          *(ulong *)(iVar7 + (iVar5 + 0x5d) * 0x10) =
               (long)((sVar23 * 10 + (int)sVar23 + 0x4d) * 0x10) | 0x100000;
          uVar9 = __fixunssfdi((fStack_28 - 8.0) * 16.0);
          lVar10 = __fixunssfdi((fVar26 + 1.0) * 16.0);
          *(ulong *)(iVar7 + (iVar5 + 0x5d) * 0x10 + 8) = uVar9 | lVar10 << 0x10;
          *(ulong *)(iVar7 + (iVar5 + 0x5e) * 0x10) =
               (long)(((sVar23 + 1) * 0xb + 0x4d) * 0x10) | 0xf00000;
          uVar8 = __fixunssfdi((fStack_28 + 0.8) * 16.0);
          uVar12 = __fixunssfdi((fVar26 + 15.0) * 16.0);
          iVar20 = iVar7 + (iVar5 + 0x5e) * 0x10;
          *(uint *)(iVar20 + 8) = (uint)uVar8 | (int)uVar12 << 0x10;
          *(uint *)(iVar20 + 0xc) = (uint)((ulong)uVar8 >> 0x20) | (uint)((ulong)uVar12 >> 0x10);
        }
        else {
          *(undefined8 *)(iVar7 + (iVar5 + 0x5d) * 0x10 + 8) = 0x71006f00;
          *(undefined8 *)(iVar7 + (iVar5 + 0x5e) * 0x10 + 8) = 0x71006f00;
        }
        uStack_18 = (int)(uint)*(ushort *)
                                (iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x12a
                                ) >> 1;
        if ((uStack_18 < 2) &&
           (2 < *(ushort *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x12a))) {
          uStack_18 = 2;
        }
        iStack_1c = (int)(uint)*(ushort *)
                                (iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x12a
                                ) >> 2;
        if ((iStack_1c == 0) &&
           (1 < *(ushort *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x12a))) {
          iStack_1c = 1;
        }
        if ((long)(int)uStack_18 <
            (long)*(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 300)) {
          *(undefined8 *)(iVar7 + (iVar5 + 0x60) * 0x10 + 8) = 0x80808080;
        }
        else if ((long)iStack_1c <
                 (long)*(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 300)
                ) {
          *(undefined8 *)(iVar7 + (iVar5 + 0x60) * 0x10 + 8) = 0x80008080;
        }
        else {
          *(undefined8 *)(iVar7 + (iVar5 + 0x60) * 0x10 + 8) = 0x80000080;
        }
        puVar6 = (ulong *)(iVar7 + (iVar5 + 0x61) * 0x10);
        iVar22 = iVar5 + 0x62;
        fVar25 = (*(float *)(param_1 + 0x60) + 2304.0 + *(float *)(param_1 + iVar18 * 4 + 0x24c)) -
                 37.8;
        sVar23 = *(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 300);
        iVar20 = (int)sVar23;
        if ((((iVar20 < -9) &&
             ((*(byte *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0xb4) & 1) ==
              0)) && (sVar15 = *(short *)(iGpffff86b4 +
                                          *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x120),
                     CONCAT44((int)(((long)sVar15 << 0x30) >> 0x3f),(int)sVar15) != 8)) &&
           ((sVar15 = *(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x120
                                ), CONCAT44((int)(((long)sVar15 << 0x30) >> 0x3f),(int)sVar15) != 9
            && (*(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x120) !=
                10)))) {
          *(undefined8 *)(iVar7 + iVar22 * 0x10) = 0x100bb0;
          uVar11 = __fixunssfdi((fVar25 - 24.0) * 16.0);
          lVar10 = __fixunssfdi((fVar26 + 1.0) * 16.0);
          uVar9 = uVar11 | lVar10 << 0x10;
          *(ulong *)(iVar7 + iVar22 * 0x10 + 8) =
               CONCAT44((int)(uVar9 >> 0x20),CONCAT22((short)(uVar9 >> 0x10),(short)uVar11));
          *(undefined8 *)(iVar7 + (iVar5 + 99) * 0x10) = 0xf00c60;
          uVar9 = __fixunssfdi((fVar25 - 15.2) * 16.0);
          lVar10 = __fixunssfdi((fVar26 + 15.0) * 16.0);
          *(ulong *)(iVar7 + (iVar5 + 99) * 0x10 + 8) = uVar9 | lVar10 << 0x10;
        }
        else {
          *(undefined8 *)(iVar7 + iVar22 * 0x10 + 8) = 0x71006f00;
          *(undefined8 *)(iVar7 + (iVar5 + 99) * 0x10 + 8) = 0x71006f00;
        }
        if (((iVar20 < 10) ||
            ((*(byte *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0xb4) & 1) !=
             0)) || ((*(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x120
                                ) == 8 ||
                     ((sVar15 = *(short *)(iGpffff86b4 +
                                           *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x120),
                      CONCAT44((int)(((long)sVar15 << 0x30) >> 0x3f),(int)sVar15) == 9 ||
                      (*(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 +
                                 0x120) == 10)))))) {
          if ((iVar20 >> 0x1f < 0) &&
             (((((*(byte *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0xb4) & 1)
                 == 0 && (sVar15 = *(short *)(iGpffff86b4 +
                                              *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x120)
                         , CONCAT44((int)((long)((ulong)(uint)(int)sVar15 << 0x30) >> 0x3f),
                                    (int)sVar15) != 8)) &&
               (sVar15 = *(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 +
                                   0x120),
               CONCAT44((int)(((long)sVar15 << 0x30) >> 0x3f),(int)sVar15) != 9)) &&
              (*(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x120) != 10
              )))) {
            if (iVar20 < -9) {
              sVar15 = (short)(-sVar23 / 10) % 10;
            }
            else {
              sVar15 = 10;
            }
            *(ulong *)(iVar7 + (iVar5 + 100) * 0x10) =
                 (long)((sVar15 * 10 + (int)sVar15 + 0x4d) * 0x10) | 0x100000;
            uVar9 = __fixunssfdi((fVar25 - 16.0) * 16.0);
            lVar10 = __fixunssfdi((fVar26 + 1.0) * 16.0);
            *(ulong *)(iVar7 + (iVar5 + 100) * 0x10 + 8) = uVar9 | lVar10 << 0x10;
            *(ulong *)(iVar7 + (iVar5 + 0x65) * 0x10) =
                 (long)(((sVar15 + 1) * 0xb + 0x4d) * 0x10) | 0xf00000;
            uVar9 = __fixunssfdi((fVar25 - 7.2000003) * 16.0);
            lVar10 = __fixunssfdi((fVar26 + 15.0) * 16.0);
            *(ulong *)(iVar7 + (iVar5 + 0x65) * 0x10 + 8) =
                 uVar9 | CONCAT44((int)((ulong)lVar10 >> 0x10),(int)(lVar10 << 0x10));
          }
          else {
            *(undefined8 *)(iVar7 + (iVar5 + 100) * 0x10 + 8) = 0x71006f00;
            *(undefined8 *)(iVar7 + (iVar5 + 0x65) * 0x10 + 8) = 0x71006f00;
          }
        }
        else {
          sVar15 = (short)((iVar20 / 10) % 10);
          *(ulong *)(iVar7 + (iVar5 + 100) * 0x10) =
               (long)((sVar15 * 10 + (int)sVar15 + 0x4d) * 0x10) | 0x100000;
          uVar9 = __fixunssfdi((fVar25 - 16.0) * 16.0);
          lVar10 = __fixunssfdi((fVar26 + 1.0) * 16.0);
          *(ulong *)(iVar7 + (iVar5 + 100) * 0x10 + 8) = uVar9 | lVar10 << 0x10;
          *(ulong *)(iVar7 + (iVar5 + 0x65) * 0x10) =
               (long)(((sVar15 + 1) * 0xb + 0x4d) * 0x10) | 0xf00000;
          uVar11 = __fixunssfdi((fVar25 - 7.2000003) * 16.0);
          lVar10 = __fixunssfdi((fVar26 + 15.0) * 16.0);
          uVar9 = uVar11 | CONCAT44((int)((ulong)lVar10 >> 0x10),(int)(lVar10 << 0x10));
          *(ulong *)(iVar7 + (iVar5 + 0x65) * 0x10 + 8) =
               CONCAT44((int)(uVar9 >> 0x20),CONCAT22((short)(uVar9 >> 0x10),(short)uVar11));
        }
        if ((((*(byte *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0xb4) & 1) ==
              0) && (sVar15 = *(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0
                                        + 0x120),
                    CONCAT44((int)(((long)sVar15 << 0x30) >> 0x3f),(int)sVar15) != 8)) &&
           ((sVar15 = *(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x120
                                ),
            CONCAT44((int)((long)((ulong)(uint)(int)sVar15 << 0x30) >> 0x3f),(int)sVar15) != 9 &&
            (*(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x120) != 10))
           )) {
          if (iVar20 < 0) {
            sVar23 = -sVar23;
          }
          *(ulong *)(iVar7 + (iVar5 + 0x66) * 0x10) =
               (long)(((sVar23 % 10) * 0xb + 0x4d) * 0x10) | 0x100000;
          uVar9 = __fixunssfdi((fVar25 - 8.0) * 16.0);
          lVar10 = __fixunssfdi((fVar26 + 1.0) * 16.0);
          *(ulong *)(iVar7 + (iVar5 + 0x66) * 0x10 + 8) = uVar9 | lVar10 << 0x10;
          *(ulong *)(iVar7 + (iVar5 + 0x67) * 0x10) =
               (long)(((sVar23 % 10 + 1) * 0xb + 0x4d) * 0x10) | 0xf00000;
          uVar9 = __fixunssfdi((fVar25 + 0.8) * 16.0);
          lVar10 = __fixunssfdi((fVar26 + 15.0) * 16.0);
          *(ulong *)(iVar7 + (iVar5 + 0x67) * 0x10 + 8) = uVar9 | lVar10 << 0x10;
        }
        else {
          *(undefined8 *)(iVar7 + (iVar5 + 0x66) * 0x10 + 8) = 0x71006f00;
          *(undefined8 *)(iVar7 + (iVar5 + 0x67) * 0x10 + 8) = 0x71006f00;
        }
        *puVar6 = *puVar6 | 0x8000;
        *puVar19 = 0x1000002c;
        puVar19[3] = 0x5000002c;
        puVar19 = (undefined4 *)(iVar7 + (iVar5 + 0x69) * 0x10);
        puVar6 = (ulong *)(iVar7 + (iVar5 + 0x6d) * 0x10);
        if (*(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x58a) < 0) {
          *(undefined8 *)(iVar7 + (iVar5 + 0x6f) * 0x10 + 8) = 0x71006f00;
          *(undefined8 *)(iVar7 + (iVar5 + 0x70) * 0x10 + 8) = 0x71006f00;
        }
        else {
          iVar20 = *(int *)(*(short *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 +
                                      0x58a) * 4 + 0x650d80);
          fVar25 = (*(float *)(param_1 + 0x60) + 2304.0 + *(float *)(param_1 + iVar18 * 4 + 0x24c))
                   - 25.8;
          sVar15 = *(short *)(iVar20 + *(short *)(iGpffff86b4 +
                                                  *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 +
                                                 0x58c) * 8) * 0x12;
          sVar23 = *(short *)(iVar20 + *(short *)(iGpffff86b4 +
                                                  *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 +
                                                 0x58c) * 8 + 2) * 0x16;
          fStack_4c = 9.0;
          if (*(float *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 + 0x594) < 0.25
             ) {
            fStack_4c = (float)sinf(*(float *)(iGpffff86b4 +
                                                          *(int *)(param_1 + iVar18 * 4 + 0x6c) *
                                                          0x4f0 + 0x594) * 4.0 * 1.5707964);
            fStack_4c = fStack_4c * 9.0;
          }
          else if (1.75 <= *(float *)(iGpffff86b4 + *(int *)(param_1 + iVar18 * 4 + 0x6c) * 0x4f0 +
                                     0x594)) {
            fStack_4c = (float)sinf((2.0 - *(float *)(iGpffff86b4 +
                                                                 *(int *)(param_1 + iVar18 * 4 +
                                                                         0x6c) * 0x4f0 + 0x594)) *
                                               4.0 * 1.5707964);
            fStack_4c = fStack_4c * 9.0;
          }
          *(ulong *)(iVar7 + (iVar5 + 0x6f) * 0x10) =
               (long)((int)sVar15 << 4) |
               CONCAT44((int)(short)((uint)((int)sVar23 << 4) >> 0x10),(int)sVar23 << 0x14);
          lVar10 = __fixunssfdi((fVar26 + 1.0) * 16.0);
          uVar9 = __fixunssfdi((fVar25 - fStack_4c) * 16.0);
          *(ulong *)(iVar7 + (iVar5 + 0x6f) * 0x10 + 8) =
               CONCAT44((int)((ulong)lVar10 >> 0x10),(int)(lVar10 << 0x10)) | uVar9;
          *(long *)(iVar7 + (iVar5 + 0x70) * 0x10) =
               (long)((sVar15 + 0x12) * 0x10) | (long)((sVar23 + 0x16) * 0x10) << 0x10;
          uVar8 = __fixunssfdi((fVar26 + 23.0) * 16.0);
          uVar9 = __fixunssfdi((fVar25 + fStack_4c) * 16.0);
          *(ulong *)(iVar7 + (iVar5 + 0x70) * 0x10 + 8) =
               CONCAT44((int)((ulong)uVar8 >> 0x10),(int)uVar8 << 0x10) | uVar9;
        }
        iVar5 = iVar5 + 0x71;
        *puVar6 = *puVar6 | 0x8000;
        *puVar19 = 0x10000007;
        puVar19[3] = 0x50000007;
      }
      iVar7 = iVar7 + iVar5 * 0x10;
      *(int *)(param_1 + uVar24 * 4 + 0x58) = iVar7;
      *(int *)(param_1 + 0x54) = iVar7;
      *(uint *)(param_1 + 0x44) = uVar24;
      if (bVar1) {
        *(uint *)(param_1 + 0x280) = *(uint *)(param_1 + 0x280) & 0xffffffd;
      }
      else {
        *(uint *)(param_1 + 0x280) = *(uint *)(param_1 + 0x280) & 0xffffffe;
      }
    }
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x004e8c20  ParamOpen__9ParamDispFv
 * C++: ParamDisp::ParamOpen()
 * size: 0x38 bytes
 * --------------------------------------------------------------------------- */
void ParamOpen__9ParamDispFv(int param_1)

{
  *(undefined4 *)(param_1 + 0x38) = 1;
  *(undefined4 *)(param_1 + 0x3c) = 0;
  *(undefined4 *)(param_1 + 0x60) = 0x43960000;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x004e8c60  ParamClose__9ParamDispFv
 * C++: ParamDisp::ParamClose()
 * size: 0x34 bytes
 * --------------------------------------------------------------------------- */
void ParamClose__9ParamDispFv(int param_1)

{
  *(undefined4 *)(param_1 + 0x38) = 3;
  *(undefined4 *)(param_1 + 0x3c) = 0;
  *(undefined4 *)(param_1 + 0x60) = 0;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x004e8ca0  SetParty__9ParamDispFii
 * C++: ParamDisp::SetParty(int, int)
 * size: 0x15dc bytes
 * --------------------------------------------------------------------------- */
void SetParty__9ParamDispFii(int param_1,int param_2,uint param_3)

{
  int iVar1;
  uint uVar2;
  undefined2 uVar3;
  int iVar4;
  int iVar5;
  float fVar6;
  
  uVar3 = (undefined2)param_2;
  if ((long)param_2 == (long)*(short *)(param_1 + 100)) {
    if (param_2 == 2) {
      iVar1 = 0;
      while ((iVar1 < *(int *)(param_1 + 0x68) && (*(uint *)(param_1 + iVar1 * 4 + 0x6c) != param_3)
             )) {
        iVar1 = iVar1 + 1;
      }
      if (*(int *)(param_1 + 0x68) <= iVar1) {
        if ((*(byte *)(iGpffff86b4 + *(int *)(param_1 + 0x6c) * 0x4f0 + 0xb4) & 1) ==
            (*(byte *)(iGpffff86b4 + param_3 * 0x4f0 + 0xb4) & 1)) {
          iVar1 = *(int *)(param_1 + 0x68);
          while (iVar5 = iVar1 + -1, -1 < iVar5) {
            *(undefined4 *)(param_1 + iVar1 * 4 + 0x6c) =
                 *(undefined4 *)(param_1 + iVar5 * 4 + 0x6c);
            *(undefined4 *)(param_1 + iVar1 * 0x18 + 0x9c) =
                 *(undefined4 *)(param_1 + iVar5 * 0x18 + 0x9c);
            *(undefined4 *)(param_1 + iVar1 * 0x18 + 0xa0) =
                 *(undefined4 *)(param_1 + iVar5 * 0x18 + 0xa0);
            *(undefined4 *)(param_1 + iVar1 * 0x18 + 0xa4) =
                 *(undefined4 *)(param_1 + iVar5 * 0x18 + 0xa4);
            *(undefined4 *)(param_1 + iVar1 * 0x18 + 0xa8) =
                 *(undefined4 *)(param_1 + iVar5 * 0x18 + 0xa8);
            *(undefined4 *)(param_1 + iVar1 * 0x18 + 0xac) =
                 *(undefined4 *)(param_1 + iVar5 * 0x18 + 0xac);
            *(undefined4 *)(param_1 + iVar1 * 0x18 + 0xb0) =
                 *(undefined4 *)(param_1 + iVar5 * 0x18 + 0xb0);
            *(undefined4 *)(param_1 + iVar1 * 0xc + 0x1bc) =
                 *(undefined4 *)(param_1 + iVar5 * 0xc + 0x1bc);
            *(undefined4 *)(param_1 + iVar1 * 0xc + 0x1c0) =
                 *(undefined4 *)(param_1 + iVar5 * 0xc + 0x1c0);
            *(undefined4 *)(param_1 + iVar1 * 0xc + 0x1c4) =
                 *(undefined4 *)(param_1 + iVar5 * 0xc + 0x1c4);
            *(undefined4 *)(param_1 + iVar1 * 4 + 0x24c) =
                 *(undefined4 *)(param_1 + iVar5 * 4 + 0x24c);
            *(undefined4 *)(param_1 + iVar1 * 4 + 0x284) =
                 *(undefined4 *)(param_1 + iVar5 * 4 + 0x284);
            iVar1 = iVar5;
          }
          *(uint *)(param_1 + 0x6c) = param_3;
          fVar6 = (float)(int)*(short *)(iGpffff86b4 + param_3 * 0x4f0 + 0x124);
          *(float *)(param_1 + 0xa8) = fVar6;
          *(float *)(param_1 + 0x9c) = fVar6;
          fVar6 = (float)(int)*(short *)(iGpffff86b4 + param_3 * 0x4f0 + 0x128);
          *(float *)(param_1 + 0xac) = fVar6;
          *(float *)(param_1 + 0xa0) = fVar6;
          fVar6 = (float)(int)*(short *)(iGpffff86b4 + param_3 * 0x4f0 + 300);
          *(float *)(param_1 + 0xb0) = fVar6;
          *(float *)(param_1 + 0xa4) = fVar6;
          if (*(float *)(param_1 + 0xa4) < 0.0) {
            *(undefined4 *)(param_1 + 0xa4) = 0;
          }
          *(undefined4 *)(param_1 + 0x1c4) = 0x3f800000;
          *(undefined4 *)(param_1 + 0x1c0) = 0x3f800000;
          *(undefined4 *)(param_1 + 0x1bc) = 0x3f800000;
          *(undefined4 *)(param_1 + 0x24c) = 0x43960000;
          *(float *)(param_1 + 0x284) = (float)(*(int *)(param_1 + 0x68) + 1) * 25.0;
          *(int *)(param_1 + 0x68) = *(int *)(param_1 + 0x68) + 1;
          *(undefined4 *)(param_1 + 0x280) = 3;
        }
        else if (*(int *)(param_1 + 0x38) == 0) {
          *(undefined4 *)(param_1 + 0x68) = 0;
          *(uint *)(param_1 + *(int *)(param_1 + 0x68) * 4 + 0x6c) = param_3;
          fVar6 = (float)(int)*(short *)(iGpffff86b4 + param_3 * 0x4f0 + 0x124);
          *(float *)(param_1 + *(int *)(param_1 + 0x68) * 0x18 + 0xa8) = fVar6;
          *(float *)(param_1 + *(int *)(param_1 + 0x68) * 0x18 + 0x9c) = fVar6;
          fVar6 = (float)(int)*(short *)(iGpffff86b4 + param_3 * 0x4f0 + 0x128);
          *(float *)(param_1 + *(int *)(param_1 + 0x68) * 0x18 + 0xac) = fVar6;
          *(float *)(param_1 + *(int *)(param_1 + 0x68) * 0x18 + 0xa0) = fVar6;
          fVar6 = (float)(int)*(short *)(iGpffff86b4 + param_3 * 0x4f0 + 300);
          *(float *)(param_1 + *(int *)(param_1 + 0x68) * 0x18 + 0xb0) = fVar6;
          *(float *)(param_1 + *(int *)(param_1 + 0x68) * 0x18 + 0xa4) = fVar6;
          if (*(float *)(param_1 + *(int *)(param_1 + 0x68) * 0x18 + 0xa4) < 0.0) {
            *(undefined4 *)(param_1 + *(int *)(param_1 + 0x68) * 0x18 + 0xa4) = 0;
          }
          *(undefined4 *)(param_1 + *(int *)(param_1 + 0x68) * 0xc + 0x1c4) = 0x3f800000;
          *(undefined4 *)(param_1 + *(int *)(param_1 + 0x68) * 0xc + 0x1c0) = 0x3f800000;
          *(undefined4 *)(param_1 + *(int *)(param_1 + 0x68) * 0xc + 0x1bc) = 0x3f800000;
          *(undefined4 *)(param_1 + *(int *)(param_1 + 0x68) * 4 + 0x24c) = 0;
          *(undefined4 *)(param_1 + *(int *)(param_1 + 0x68) * 4 + 0x284) = 0x41c80000;
          *(int *)(param_1 + 0x68) = *(int *)(param_1 + 0x68) + 1;
          *(undefined2 *)(param_1 + 100) = 2;
          *(undefined4 *)(param_1 + 0x280) = 3;
        }
        else {
          *(int *)(param_1 + 0x27c) = 1 << (param_3 & 0x1f);
          *(undefined2 *)(param_1 + 0x66) = 2;
          if (*(int *)(param_1 + 0x38) != 4) {
            *(undefined4 *)(param_1 + 0x38) = 4;
            *(undefined4 *)(param_1 + 0x3c) = 0;
          }
          *(undefined4 *)(param_1 + 0x280) = 3;
        }
      }
    }
  }
  else {
    switch(param_2) {
    case 3:
      *(undefined4 *)(param_1 + 0x68) = 0;
    case 0:
      if (*(int *)(param_1 + 0x38) == 0) {
        *(undefined4 *)(param_1 + 0x68) = 0;
        for (iVar1 = 0; iVar1 < 0xc; iVar1 = iVar1 + 1) {
          if (((((*(byte *)(iGpffff86b4 + iVar1 * 0x4f0 + 0xb0) & 1) != 0) &&
               ((long)((ulong)*(byte *)(iGpffff86b4 + iVar1 * 0x4f0 + 0xb0) << 0x3e) < 0)) &&
              (-1 < (long)((ulong)*(byte *)(iGpffff86b4 + iVar1 * 0x4f0 + 0xb2) << 0x3d))) &&
             ((*(byte *)(iGpffff86b4 + iVar1 * 0x4f0 + 0xb4) & 1) == 0)) {
            *(int *)(param_1 + *(int *)(param_1 + 0x68) * 4 + 0x6c) = iVar1;
            fVar6 = (float)(int)*(short *)(iGpffff86b4 + iVar1 * 0x4f0 + 0x124);
            *(float *)(param_1 + *(int *)(param_1 + 0x68) * 0x18 + 0xa8) = fVar6;
            *(float *)(param_1 + *(int *)(param_1 + 0x68) * 0x18 + 0x9c) = fVar6;
            fVar6 = (float)(int)*(short *)(iGpffff86b4 + iVar1 * 0x4f0 + 0x128);
            *(float *)(param_1 + *(int *)(param_1 + 0x68) * 0x18 + 0xac) = fVar6;
            *(float *)(param_1 + *(int *)(param_1 + 0x68) * 0x18 + 0xa0) = fVar6;
            fVar6 = (float)(int)*(short *)(iGpffff86b4 + iVar1 * 0x4f0 + 300);
            *(float *)(param_1 + *(int *)(param_1 + 0x68) * 0x18 + 0xb0) = fVar6;
            *(float *)(param_1 + *(int *)(param_1 + 0x68) * 0x18 + 0xa4) = fVar6;
            if (*(float *)(param_1 + *(int *)(param_1 + 0x68) * 0x18 + 0xa4) < 0.0) {
              *(undefined4 *)(param_1 + *(int *)(param_1 + 0x68) * 0x18 + 0xa4) = 0;
            }
            *(undefined4 *)(param_1 + *(int *)(param_1 + 0x68) * 0xc + 0x1c4) = 0x3f800000;
            *(undefined4 *)(param_1 + *(int *)(param_1 + 0x68) * 0xc + 0x1c0) = 0x3f800000;
            *(undefined4 *)(param_1 + *(int *)(param_1 + 0x68) * 0xc + 0x1bc) = 0x3f800000;
            *(undefined4 *)(param_1 + *(int *)(param_1 + 0x68) * 4 + 0x24c) = 0;
            for (iVar5 = 0; iVar5 < *(int *)(param_1 + 0x68); iVar5 = iVar5 + 1) {
              iVar4 = param_1 + iVar5 * 4;
              *(float *)(iVar4 + 0x284) = *(float *)(iVar4 + 0x284) - 25.0;
            }
            *(undefined4 *)(param_1 + *(int *)(param_1 + 0x68) * 4 + 0x284) = 0xc1c80000;
            *(int *)(param_1 + 0x68) = *(int *)(param_1 + 0x68) + 1;
          }
        }
        *(undefined2 *)(param_1 + 100) = uVar3;
        *(undefined4 *)(param_1 + 0x280) = 3;
      }
      else {
        *(undefined4 *)(param_1 + 0x27c) = 0;
        for (uVar2 = 0; (int)uVar2 < 0xc; uVar2 = uVar2 + 1) {
          if ((((*(byte *)(iGpffff86b4 + uVar2 * 0x4f0 + 0xb0) & 1) != 0) &&
              ((long)((ulong)*(byte *)(iGpffff86b4 + uVar2 * 0x4f0 + 0xb0) << 0x3e) < 0)) &&
             ((-1 < (long)((ulong)*(byte *)(iGpffff86b4 + uVar2 * 0x4f0 + 0xb2) << 0x3d) &&
              ((*(byte *)(iGpffff86b4 + uVar2 * 0x4f0 + 0xb4) & 1) == 0)))) {
            *(uint *)(param_1 + 0x27c) = *(uint *)(param_1 + 0x27c) | 1 << (uVar2 & 0x1f);
          }
        }
        *(undefined2 *)(param_1 + 0x66) = uVar3;
        if (*(int *)(param_1 + 0x38) != 4) {
          *(undefined4 *)(param_1 + 0x38) = 4;
          *(undefined4 *)(param_1 + 0x3c) = 0;
        }
        *(undefined4 *)(param_1 + 0x280) = 3;
      }
      break;
    case 4:
      *(undefined4 *)(param_1 + 0x68) = 0;
    case 1:
      if (*(int *)(param_1 + 0x38) == 0) {
        *(undefined4 *)(param_1 + 0x68) = 0;
        for (iVar1 = 0; iVar1 < 0xc; iVar1 = iVar1 + 1) {
          if ((((*(byte *)(iGpffff86b4 + iVar1 * 0x4f0 + 0xb0) & 1) != 0) &&
              ((long)((ulong)*(byte *)(iGpffff86b4 + iVar1 * 0x4f0 + 0xb0) << 0x3e) < 0)) &&
             ((-1 < (long)((ulong)*(byte *)(iGpffff86b4 + iVar1 * 0x4f0 + 0xb2) << 0x3d) &&
              ((*(byte *)(iGpffff86b4 + iVar1 * 0x4f0 + 0xb4) & 1) != 0)))) {
            *(int *)(param_1 + *(int *)(param_1 + 0x68) * 4 + 0x6c) = iVar1;
            fVar6 = (float)(int)*(short *)(iGpffff86b4 + iVar1 * 0x4f0 + 0x124);
            *(float *)(param_1 + *(int *)(param_1 + 0x68) * 0x18 + 0xa8) = fVar6;
            *(float *)(param_1 + *(int *)(param_1 + 0x68) * 0x18 + 0x9c) = fVar6;
            fVar6 = (float)(int)*(short *)(iGpffff86b4 + iVar1 * 0x4f0 + 0x128);
            *(float *)(param_1 + *(int *)(param_1 + 0x68) * 0x18 + 0xac) = fVar6;
            *(float *)(param_1 + *(int *)(param_1 + 0x68) * 0x18 + 0xa0) = fVar6;
            fVar6 = (float)(int)*(short *)(iGpffff86b4 + iVar1 * 0x4f0 + 300);
            *(float *)(param_1 + *(int *)(param_1 + 0x68) * 0x18 + 0xb0) = fVar6;
            *(float *)(param_1 + *(int *)(param_1 + 0x68) * 0x18 + 0xa4) = fVar6;
            if (*(float *)(param_1 + *(int *)(param_1 + 0x68) * 0x18 + 0xa4) < 0.0) {
              *(undefined4 *)(param_1 + *(int *)(param_1 + 0x68) * 0x18 + 0xa4) = 0;
            }
            *(undefined4 *)(param_1 + *(int *)(param_1 + 0x68) * 0xc + 0x1c4) = 0x3f800000;
            *(undefined4 *)(param_1 + *(int *)(param_1 + 0x68) * 0xc + 0x1c0) = 0x3f800000;
            *(undefined4 *)(param_1 + *(int *)(param_1 + 0x68) * 0xc + 0x1bc) = 0x3f800000;
            *(undefined4 *)(param_1 + *(int *)(param_1 + 0x68) * 4 + 0x24c) = 0;
            for (iVar5 = 0; iVar5 < *(int *)(param_1 + 0x68); iVar5 = iVar5 + 1) {
              iVar4 = param_1 + iVar5 * 4;
              *(float *)(iVar4 + 0x284) = *(float *)(iVar4 + 0x284) - 25.0;
            }
            *(undefined4 *)(param_1 + *(int *)(param_1 + 0x68) * 4 + 0x284) = 0xc1c80000;
            *(int *)(param_1 + 0x68) = *(int *)(param_1 + 0x68) + 1;
          }
        }
        *(undefined2 *)(param_1 + 100) = uVar3;
        *(undefined4 *)(param_1 + 0x280) = 3;
      }
      else {
        *(undefined4 *)(param_1 + 0x27c) = 0;
        for (uVar2 = 0; (int)uVar2 < 0xc; uVar2 = uVar2 + 1) {
          if (((((*(byte *)(iGpffff86b4 + uVar2 * 0x4f0 + 0xb0) & 1) != 0) &&
               ((long)((ulong)*(byte *)(iGpffff86b4 + uVar2 * 0x4f0 + 0xb0) << 0x3e) < 0)) &&
              (-1 < (long)((ulong)*(byte *)(iGpffff86b4 + uVar2 * 0x4f0 + 0xb2) << 0x3d))) &&
             ((*(byte *)(iGpffff86b4 + uVar2 * 0x4f0 + 0xb4) & 1) != 0)) {
            *(uint *)(param_1 + 0x27c) = *(uint *)(param_1 + 0x27c) | 1 << (uVar2 & 0x1f);
          }
        }
        *(undefined2 *)(param_1 + 0x66) = uVar3;
        if (*(int *)(param_1 + 0x38) != 4) {
          *(undefined4 *)(param_1 + 0x38) = 4;
          *(undefined4 *)(param_1 + 0x3c) = 0;
        }
        *(undefined4 *)(param_1 + 0x280) = 3;
      }
      break;
    case 5:
      *(undefined4 *)(param_1 + 0x68) = 0;
    case 2:
      if (*(int *)(param_1 + 0x38) == 0) {
        *(undefined4 *)(param_1 + 0x68) = 0;
        *(uint *)(param_1 + *(int *)(param_1 + 0x68) * 4 + 0x6c) = param_3;
        fVar6 = (float)(int)*(short *)(iGpffff86b4 + param_3 * 0x4f0 + 0x124);
        *(float *)(param_1 + *(int *)(param_1 + 0x68) * 0x18 + 0xa8) = fVar6;
        *(float *)(param_1 + *(int *)(param_1 + 0x68) * 0x18 + 0x9c) = fVar6;
        fVar6 = (float)(int)*(short *)(iGpffff86b4 + param_3 * 0x4f0 + 0x128);
        *(float *)(param_1 + *(int *)(param_1 + 0x68) * 0x18 + 0xac) = fVar6;
        *(float *)(param_1 + *(int *)(param_1 + 0x68) * 0x18 + 0xa0) = fVar6;
        fVar6 = (float)(int)*(short *)(iGpffff86b4 + param_3 * 0x4f0 + 300);
        *(float *)(param_1 + *(int *)(param_1 + 0x68) * 0x18 + 0xb0) = fVar6;
        *(float *)(param_1 + *(int *)(param_1 + 0x68) * 0x18 + 0xa4) = fVar6;
        if (*(float *)(param_1 + *(int *)(param_1 + 0x68) * 0x18 + 0xa4) < 0.0) {
          *(undefined4 *)(param_1 + *(int *)(param_1 + 0x68) * 0x18 + 0xa4) = 0;
        }
        *(undefined4 *)(param_1 + *(int *)(param_1 + 0x68) * 0xc + 0x1c4) = 0x3f800000;
        *(undefined4 *)(param_1 + *(int *)(param_1 + 0x68) * 0xc + 0x1c0) = 0x3f800000;
        *(undefined4 *)(param_1 + *(int *)(param_1 + 0x68) * 0xc + 0x1bc) = 0x3f800000;
        *(undefined4 *)(param_1 + *(int *)(param_1 + 0x68) * 4 + 0x24c) = 0;
        *(undefined4 *)(param_1 + *(int *)(param_1 + 0x68) * 4 + 0x284) = 0xc1c80000;
        *(int *)(param_1 + 0x68) = *(int *)(param_1 + 0x68) + 1;
        *(undefined2 *)(param_1 + 100) = uVar3;
        *(undefined4 *)(param_1 + 0x280) = 3;
      }
      else {
        *(int *)(param_1 + 0x27c) = 1 << (param_3 & 0x1f);
        *(undefined2 *)(param_1 + 0x66) = uVar3;
        if (*(int *)(param_1 + 0x38) != 4) {
          *(undefined4 *)(param_1 + 0x38) = 4;
          *(undefined4 *)(param_1 + 0x3c) = 0;
        }
        *(undefined4 *)(param_1 + 0x280) = 3;
      }
    }
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b380  getPacket__9ParamDispFv
 * C++: ParamDisp::getPacket()
 * size: 0x28 bytes
 * --------------------------------------------------------------------------- */
void getPacket__9ParamDispFv(undefined4 param_1)

{
  MakePacket__9ParamDispFv(param_1);
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b3b0  @24@getPacket__9ParamDispFv
 * C++: @24@getPacket__9ParamDispFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
void _24_getPacket__9ParamDispFv(int param_1)

{
  MakePacket__9ParamDispFv(param_1 + -0x18);
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b3c0  @24@__dt__9ParamDispFv
 * C++: @24@__dt__9ParamDispFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int * _24___dt__9ParamDispFv(int *param_1,short param_2)

{
  int *piVar1;
  
  piVar1 = param_1 + -6;
  if (piVar1 != (int *)0x0) {
    param_1[-1] = 0x40a5f0;
    param_1[4] = 0x40a600;
    param_1[7] = 0x40a610;
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
 * JP: 0x0054b3d0  @44@__dt__9ParamDispFv
 * C++: @44@__dt__9ParamDispFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int _44___dt__9ParamDispFv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x2c;
  if (iVar1 != 0) {
    *(undefined4 *)(param_1 + -0x18) = 0x40a5f0;
    *(undefined4 *)(param_1 + -4) = 0x40a600;
    *(undefined4 *)(param_1 + 8) = 0x40a610;
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

