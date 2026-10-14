/* decomp/H/FrictionSmokeCall.c — cleaned Ghidra output (SH2JP_BATTLE.BIN, JP Furokuban, base 0x00430a00).
 * 8 function(s). Types: see types.h. Names/gp globals resolved from symbols/SLPM_602.19.syms. */
#include "types.h"

/* ---------------------------------------------------------------------------
 * JP: 0x0050a220  __ct__17FrictionSmokeCallFii
 * C++: FrictionSmokeCall::__ct(int, int)
 * size: 0x140 bytes
 * --------------------------------------------------------------------------- */
int __ct__17FrictionSmokeCallFii(int param_1,undefined4 param_2,undefined4 param_3)

{
  __ct__6BtlEffFii(param_1,param_2,param_3);
  *(undefined4 *)(param_1 + 0x14) = 0x40a260;
  *(undefined4 *)(param_1 + 0x28) = 0x40a270;
  *(undefined4 *)(param_1 + 0x34) = 0x40a280;
  *(undefined4 *)(param_1 + 0x5c) = 0;
  *(undefined4 *)(param_1 + 0x60) = 0;
  *(undefined4 *)(param_1 + 100) = 0;
  *(undefined4 *)(param_1 + 0x44) = param_2;
  *(undefined4 *)(param_1 + 0x48) = param_3;
  *(undefined4 *)(param_1 + 0x4c) = 3;
  *(undefined4 *)(param_1 + 0x68) = 0;
  Entry__7CPollerFP7CPolObjib(iGpffff858c + 0x48,param_1,0x80,0);
  BtlEffEntry__7CBattleFiP6BtlEff(uGpffff86b4,*(undefined4 *)(param_1 + 0x48),param_1);
  return param_1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0050a310  Destruct__17FrictionSmokeCallFv
 * C++: FrictionSmokeCall::Destruct()
 * size: 0x60 bytes
 * --------------------------------------------------------------------------- */
void Destruct__17FrictionSmokeCallFv(int param_1)

{
  BtlEffRelease__7CBattleFiP6BtlEff(uGpffff86b4,*(undefined4 *)(param_1 + 0x48),param_1);
  Dispose__7CPollerFP7CPolObj(iGpffff858c + 0x48,param_1);
  (**(code **)(*(int *)(param_1 + 0x34) + 0xc))();
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0050a370  Polling__17FrictionSmokeCallFv
 * C++: FrictionSmokeCall::Polling()
 * size: 0x530 bytes
 * --------------------------------------------------------------------------- */
undefined8 Polling__17FrictionSmokeCallFv(int param_1)

{
  int iVar1;
  int iVar2;
  float in_zero_lo;
  float in_zero_hi;
  float in_zero_udw;
  undefined4 in_register_0000000c;
  int iVar3;
  long lVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  bool bVar9;
  undefined1 auStack_90 [8];
  float fStack_88;
  undefined4 uStack_84;
  float fStack_80;
  float fStack_7c;
  float fStack_78;
  undefined4 uStack_74;
  float fStack_70;
  float fStack_6c;
  float fStack_68;
  undefined4 uStack_64;
  undefined1 auStack_60 [64];
  undefined1 auStack_20 [32];
  
  if ((((-1 < (long)((ulong)*(byte *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0xb0) << 0x3a
                    )) && (*(int *)(param_1 + 0x5c) == 0)) &&
      ((*(byte *)(iGpffff86b4 + 0x24) & 1) == 0)) &&
     (*(float *)(param_1 + 0x68) = *(float *)(param_1 + 0x68) + *(float *)(iGpffff86b4 + 0x38),
     0.06666667 <= *(float *)(param_1 + 0x68))) {
    *(float *)(param_1 + 0x68) = *(float *)(param_1 + 0x68) - 0.06666667;
    iVar6 = 0;
    iVar3 = *(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x534) + 0x10);
    if (iVar3 != 0) {
      iVar1 = *(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x538);
      iVar2 = *(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x534) + 0x14);
      for (iVar8 = 0; iVar8 < iVar3; iVar8 = iVar8 + 1) {
        lVar4 = searchBBoxIndex__8BtlModelFPci
                          (*(undefined4 *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x144),
                           iVar1 + iVar2 + iVar8 * 0xc,0);
        if (lVar4 != -1) {
          iVar5 = (int)lVar4;
          __ct__6MatrixFRC6Matrix(auStack_60,
                          *(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x144)
                                  + 0x30) +
                          (uint)*(byte *)(*(int *)(*(int *)(iGpffff86b4 +
                                                            *(int *)(param_1 + 0x48) * 0x4f0 + 0x144
                                                           ) + 0xe4) + iVar5 * 0x110) * 0x1f0 +
                          (bGpffff8340 & 1) * 0x40);
          bVar9 = false;
          fStack_80 = in_zero_lo;
          fStack_7c = in_zero_hi;
          fStack_78 = in_zero_udw;
          uStack_74 = in_register_0000000c;
          fStack_70 = in_zero_lo;
          fStack_6c = in_zero_hi;
          fStack_68 = in_zero_udw;
          uStack_64 = in_register_0000000c;
          for (iVar7 = 0; iVar7 < 8; iVar7 = iVar7 + 1) {
            fStack_70 = *(float *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0
                                                    + 0x144) + 0xe4) + iVar5 * 0x110 + iVar7 * 0x10
                                  + 0x10) * 1.2;
            fStack_6c = *(float *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0
                                                    + 0x144) + 0xe4) + iVar5 * 0x110 + iVar7 * 0x10
                                  + 0x14) * 1.2;
            fStack_68 = *(float *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0
                                                    + 0x144) + 0xe4) + iVar5 * 0x110 + iVar7 * 0x10
                                  + 0x18) * 1.2;
            uStack_64 = *(undefined4 *)
                         (*(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x144)
                                  + 0xe4) + iVar5 * 0x110 + iVar7 * 0x10 + 0x1c);
            ApplyMatrix__6MatrixCFRC7FVector(auStack_90,auStack_60,&fStack_70);
            fStack_80 = auStack_90._0_4_;
            fStack_7c = auStack_90._4_4_;
            fStack_78 = fStack_88;
            uStack_74 = uStack_84;
            if (-0.5 <= fStack_7c) {
              bVar9 = true;
            }
          }
          if (bVar9) {
            auStack_20[iVar6] = (char)lVar4;
            iVar6 = iVar6 + 1;
          }
        }
      }
      if (iVar6 != 0) {
        iVar3 = rand();
        lVar4 = __nw__FUi(0xa0);
        if (lVar4 != 0) {
          __ct__9DownSmokeFiiii
                    (lVar4,*(undefined4 *)(param_1 + 0x44),*(undefined4 *)(param_1 + 0x48),
                     auStack_20[(int)((float)iVar6 * ((float)iVar3 / 2.1474836e+09))],0);
        }
      }
    }
  }
  return 0;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054af60  MakePacket__17FrictionSmokeCallFv
 * C++: FrictionSmokeCall::MakePacket()
 * size: 0x10 bytes
 * --------------------------------------------------------------------------- */
void MakePacket__17FrictionSmokeCallFv(void)

{
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054af70  EndSet__17FrictionSmokeCallFv
 * C++: FrictionSmokeCall::EndSet()
 * size: 0x30 bytes
 * --------------------------------------------------------------------------- */
void EndSet__17FrictionSmokeCallFv(int param_1)

{
  (**(code **)(*(int *)(param_1 + 0x14) + 0x30))();
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054afa0  __dt__17FrictionSmokeCallFv
 * C++: FrictionSmokeCall::__dt()
 * size: 0x10c bytes
 * --------------------------------------------------------------------------- */
int __dt__17FrictionSmokeCallFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x14) = 0x40a260;
    *(undefined4 *)(param_1 + 0x28) = 0x40a270;
    *(undefined4 *)(param_1 + 0x34) = 0x40a280;
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
 * JP: 0x0054b580  @24@__dt__17FrictionSmokeCallFv
 * C++: @24@__dt__17FrictionSmokeCallFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int _24___dt__17FrictionSmokeCallFv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x18;
  if (iVar1 != 0) {
    *(undefined4 *)(param_1 + -4) = 0x40a260;
    *(undefined4 *)(param_1 + 0x10) = 0x40a270;
    *(undefined4 *)(param_1 + 0x1c) = 0x40a280;
    if (iVar1 != 0) {
      *(undefined4 *)(param_1 + -4) = 0x40a520;
      *(undefined4 *)(param_1 + 0x10) = 0x40a530;
      *(undefined4 *)(param_1 + 0x1c) = 0x40a540;
      if (iVar1 != -0x2c) {
        *(undefined4 *)(param_1 + 0x1c) = 0x4049f0;
      }
      __dt__8VIF1PrimFv(param_1,0);
      __dt__7CPolObjFv(iVar1,0);
    }
    if (0 < param_2) {
      __dl__FPv(iVar1);
    }
  }
  return iVar1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b590  @44@__dt__17FrictionSmokeCallFv
 * C++: @44@__dt__17FrictionSmokeCallFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int _44___dt__17FrictionSmokeCallFv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x2c;
  if (iVar1 != 0) {
    *(undefined4 *)(param_1 + -0x18) = 0x40a260;
    *(undefined4 *)(param_1 + -4) = 0x40a270;
    *(undefined4 *)(param_1 + 8) = 0x40a280;
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

