/* decomp/H/DownHitSmokeCall.c — cleaned Ghidra output (SH2JP_BATTLE.BIN, JP Furokuban, base 0x00430a00).
 * 8 function(s). Types: see types.h. Names/gp globals resolved from symbols/SLPM_602.19.syms. */
#include "types.h"

/* ---------------------------------------------------------------------------
 * JP: 0x005091e0  __ct__16DownHitSmokeCallFiii
 * C++: DownHitSmokeCall::__ct(int, int, int)
 * size: 0x194 bytes
 * --------------------------------------------------------------------------- */
int __ct__16DownHitSmokeCallFiii
              (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  __ct__6BtlEffFii(param_1,param_2,param_3);
  *(undefined4 *)(param_1 + 0x14) = 0x40a2b0;
  *(undefined4 *)(param_1 + 0x28) = 0x40a2c0;
  *(undefined4 *)(param_1 + 0x34) = 0x40a2d0;
  *(undefined4 *)(param_1 + 0x5c) = param_4;
  *(undefined4 *)(param_1 + 0x60) = 0;
  *(undefined4 *)(param_1 + 100) = 0;
  *(undefined4 *)(param_1 + 0x44) = param_2;
  *(undefined4 *)(param_1 + 0x48) = param_3;
  *(undefined4 *)(param_1 + 0x4c) = 3;
  for (iVar1 = 0; iVar1 < **(int **)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x534);
      iVar1 = iVar1 + 1) {
    *(undefined1 *)(param_1 + iVar1 + 0xe8) = 0;
    *(undefined1 *)(param_1 + iVar1 + 200) = 0;
    *(undefined1 *)(param_1 + iVar1 + 0xa8) = 0;
    *(undefined1 *)(param_1 + iVar1 + 0x88) = 0;
    *(undefined1 *)(param_1 + iVar1 + 0x68) = 0;
  }
  Entry__7CPollerFP7CPolObjib(iGpffff858c + 0x48,param_1,0x80,0);
  BtlEffEntry__7CBattleFiP6BtlEff(iGpffff86b4,*(undefined4 *)(param_1 + 0x48),param_1);
  return param_1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00509380  Destruct__16DownHitSmokeCallFv
 * C++: DownHitSmokeCall::Destruct()
 * size: 0x60 bytes
 * --------------------------------------------------------------------------- */
void Destruct__16DownHitSmokeCallFv(int param_1)

{
  BtlEffRelease__7CBattleFiP6BtlEff(uGpffff86b4,*(undefined4 *)(param_1 + 0x48),param_1);
  Dispose__7CPollerFP7CPolObj(iGpffff858c + 0x48,param_1);
  (**(code **)(*(int *)(param_1 + 0x34) + 0xc))();
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005093e0  Polling__16DownHitSmokeCallFv
 * C++: DownHitSmokeCall::Polling()
 * size: 0xe34 bytes
 * --------------------------------------------------------------------------- */
undefined8 Polling__16DownHitSmokeCallFv(int param_1)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  int iVar6;
  undefined4 uVar7;
  long lVar8;
  int iVar9;
  float afStack_1b0 [32];
  undefined1 auStack_130 [64];
  undefined1 auStack_f0 [4];
  float afStack_ec [31];
  undefined1 auStack_70 [64];
  undefined1 *puStack_30;
  undefined1 *puStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  int iStack_10;
  
  if ((-1 < (long)((ulong)*(byte *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0xb0) << 0x3a))
     && ((*(byte *)(iGpffff86b4 + 0x24) & 1) == 0)) {
    iStack_10 = param_1;
    if (*(int *)(param_1 + 0x5c) == 1) {
      for (iVar9 = 0; iVar9 < **(int **)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0x534);
          iVar9 = iVar9 + 1) {
        if (*(short *)(*(int *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0x548) +
                      iVar9 * 2) == -1) {
          *(undefined1 *)(iStack_10 + iVar9 + 0x68) = 1;
          *(undefined1 *)(iStack_10 + iVar9 + 0x88) = 1;
          *(undefined1 *)(iStack_10 + iVar9 + 0xa8) = 1;
          *(undefined1 *)(iStack_10 + iVar9 + 200) = 1;
          *(undefined1 *)(iStack_10 + iVar9 + 0xe8) = 1;
          uVar7 = uStack_28;
        }
        else {
          puStack_30 = &bGpffff8340;
          __ct__6MatrixFRC6Matrix(auStack_130,
                          *(int *)(*(int *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0x144
                                           ) + 0x30) +
                          (uint)*(byte *)(*(int *)(*(int *)(iGpffff86b4 +
                                                            *(int *)(iStack_10 + 0x48) * 0x4f0 +
                                                           0x144) + 0xe4) +
                                         *(short *)(*(int *)(iGpffff86b4 +
                                                             *(int *)(iStack_10 + 0x48) * 0x4f0 +
                                                            0x548) + iVar9 * 2) * 0x110) * 0x1f0 +
                          (bGpffff8340 & 1) * 0x40);
          RotTransVector(afStack_1b0,
                          *(int *)(*(int *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0x144
                                           ) + 0xe4) +
                          *(short *)(*(int *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 +
                                             0x548) + iVar9 * 2) * 0x110 + 0x10,auStack_130,8);
          bVar5 = false;
          bVar4 = false;
          bVar3 = false;
          bVar2 = false;
          bVar1 = false;
          for (iVar6 = 0; iVar6 < 8; iVar6 = iVar6 + 1) {
            if ((*(char *)(iStack_10 + iVar9 + 0x68) == '\0') &&
               (-0.5 <= afStack_1b0[iVar6 * 4 + 1])) {
              bVar1 = true;
            }
            if ((((*(float *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0x174) <= 67.5) &&
                 (-67.5 <= *(float *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0x174))) ||
                (112.5 <= *(float *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0x174))) ||
               (*(float *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0x174) <= -112.5)) {
              if ((*(char *)(iStack_10 + iVar9 + 0x88) == '\0') &&
                 (*(float *)(iGpffff86b4 + 0x3f1c) / 2.0 - 0.5 <= afStack_1b0[iVar6 * 4 + 2])) {
                bVar2 = true;
              }
              if ((*(char *)(iStack_10 + iVar9 + 0xa8) == '\0') &&
                 (afStack_1b0[iVar6 * 4 + 2] <= -*(float *)(iGpffff86b4 + 0x3f1c) / 2.0 + 0.5)) {
                bVar3 = true;
              }
            }
            if (((22.5 <= *(float *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0x174)) &&
                (*(float *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0x174) <= 157.5)) ||
               ((*(float *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0x174) <= -22.5 &&
                (-157.5 <= *(float *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0x174)))))
            {
              if ((*(char *)(iStack_10 + iVar9 + 200) == '\0') &&
                 (afStack_1b0[iVar6 * 4] <= -*(float *)(iGpffff86b4 + 0x3f14) / 2.0 + 0.5)) {
                bVar4 = true;
              }
              if ((*(char *)(iStack_10 + iVar9 + 0xe8) == '\0') &&
                 (*(float *)(iGpffff86b4 + 0x3f14) / 2.0 - 0.5 <= afStack_1b0[iVar6 * 4])) {
                bVar5 = true;
              }
            }
          }
          uVar7 = uStack_18;
          if (bVar1) {
            *(undefined1 *)(iStack_10 + iVar9 + 0x68) = 1;
            lVar8 = __nw__FUi(0xa0);
            uVar7 = 0;
            if (lVar8 != 0) {
              uVar7 = __ct__9DownSmokeFiiii
                                (lVar8,*(undefined4 *)(iStack_10 + 0x44),
                                 *(undefined4 *)(iStack_10 + 0x48),
                                 *(undefined2 *)
                                  (*(int *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0x548
                                           ) + iVar9 * 2),8);
            }
          }
          uStack_18 = uVar7;
          uVar7 = uStack_1c;
          if (bVar2) {
            *(undefined1 *)(iStack_10 + iVar9 + 0x88) = 1;
            lVar8 = __nw__FUi(0xa0);
            uVar7 = 0;
            if (lVar8 != 0) {
              uVar7 = __ct__9DownSmokeFiiii
                                (lVar8,*(undefined4 *)(iStack_10 + 0x44),
                                 *(undefined4 *)(iStack_10 + 0x48),
                                 *(undefined2 *)
                                  (*(int *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0x548
                                           ) + iVar9 * 2),9);
            }
          }
          uStack_1c = uVar7;
          uVar7 = uStack_20;
          if (bVar3) {
            *(undefined1 *)(iStack_10 + iVar9 + 0xa8) = 1;
            lVar8 = __nw__FUi(0xa0);
            uVar7 = 0;
            if (lVar8 != 0) {
              uVar7 = __ct__9DownSmokeFiiii
                                (lVar8,*(undefined4 *)(iStack_10 + 0x44),
                                 *(undefined4 *)(iStack_10 + 0x48),
                                 *(undefined2 *)
                                  (*(int *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0x548
                                           ) + iVar9 * 2),10);
            }
          }
          uStack_20 = uVar7;
          uVar7 = uStack_24;
          if (bVar4) {
            *(undefined1 *)(iStack_10 + iVar9 + 200) = 1;
            lVar8 = __nw__FUi(0xa0);
            uVar7 = 0;
            if (lVar8 != 0) {
              uVar7 = __ct__9DownSmokeFiiii
                                (lVar8,*(undefined4 *)(iStack_10 + 0x44),
                                 *(undefined4 *)(iStack_10 + 0x48),
                                 *(undefined2 *)
                                  (*(int *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0x548
                                           ) + iVar9 * 2),0xb);
            }
          }
          uStack_24 = uVar7;
          uVar7 = uStack_28;
          if (bVar5) {
            *(undefined1 *)(iStack_10 + iVar9 + 0xe8) = 1;
            lVar8 = __nw__FUi(0xa0);
            uVar7 = 0;
            if (lVar8 != 0) {
              uVar7 = __ct__9DownSmokeFiiii
                                (lVar8,*(undefined4 *)(iStack_10 + 0x44),
                                 *(undefined4 *)(iStack_10 + 0x48),
                                 *(undefined2 *)
                                  (*(int *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0x548
                                           ) + iVar9 * 2),0xc);
            }
          }
        }
        uStack_28 = uVar7;
      }
    }
    else if (*(int *)(param_1 + 0x5c) == 0) {
      for (iVar9 = 0; iVar9 < **(int **)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0x534);
          iVar9 = iVar9 + 1) {
        uVar7 = uStack_14;
        if (*(char *)(iStack_10 + iVar9 + 0x68) == '\0') {
          if (*(short *)(*(int *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 + 0x548) +
                        iVar9 * 2) == -1) {
            *(undefined1 *)(iStack_10 + iVar9 + 0x68) = 1;
          }
          else {
            puStack_2c = &bGpffff8340;
            __ct__6MatrixFRC6Matrix(auStack_70,
                            *(int *)(*(int *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 +
                                             0x144) + 0x30) +
                            (uint)*(byte *)(*(int *)(*(int *)(iGpffff86b4 +
                                                              *(int *)(iStack_10 + 0x48) * 0x4f0 +
                                                             0x144) + 0xe4) +
                                           *(short *)(*(int *)(iGpffff86b4 +
                                                               *(int *)(iStack_10 + 0x48) * 0x4f0 +
                                                              0x548) + iVar9 * 2) * 0x110) * 0x1f0 +
                            (bGpffff8340 & 1) * 0x40);
            RotTransVector(auStack_f0,
                            *(int *)(*(int *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 +
                                             0x144) + 0xe4) +
                            *(short *)(*(int *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 +
                                               0x548) + iVar9 * 2) * 0x110 + 0x10,auStack_70,8);
            bVar1 = false;
            for (iVar6 = 0; iVar6 < 8; iVar6 = iVar6 + 1) {
              if (-0.5 <= afStack_ec[iVar6 * 4]) {
                bVar1 = true;
                break;
              }
            }
            uVar7 = uStack_14;
            if (bVar1) {
              *(undefined1 *)(iStack_10 + iVar9 + 0x68) = 1;
              lVar8 = __nw__FUi(0xa0);
              uVar7 = 0;
              if (lVar8 != 0) {
                uVar7 = __ct__9DownSmokeFiiii
                                  (lVar8,*(undefined4 *)(iStack_10 + 0x44),
                                   *(undefined4 *)(iStack_10 + 0x48),
                                   *(undefined2 *)
                                    (*(int *)(iGpffff86b4 + *(int *)(iStack_10 + 0x48) * 0x4f0 +
                                             0x548) + iVar9 * 2),8);
              }
            }
          }
        }
        uStack_14 = uVar7;
      }
    }
  }
  return 0;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b0b0  MakePacket__16DownHitSmokeCallFv
 * C++: DownHitSmokeCall::MakePacket()
 * size: 0x10 bytes
 * --------------------------------------------------------------------------- */
void MakePacket__16DownHitSmokeCallFv(void)

{
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b0c0  EndSet__16DownHitSmokeCallFv
 * C++: DownHitSmokeCall::EndSet()
 * size: 0x30 bytes
 * --------------------------------------------------------------------------- */
void EndSet__16DownHitSmokeCallFv(int param_1)

{
  (**(code **)(*(int *)(param_1 + 0x14) + 0x30))();
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b0f0  __dt__16DownHitSmokeCallFv
 * C++: DownHitSmokeCall::__dt()
 * size: 0x10c bytes
 * --------------------------------------------------------------------------- */
int __dt__16DownHitSmokeCallFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x14) = 0x40a2b0;
    *(undefined4 *)(param_1 + 0x28) = 0x40a2c0;
    *(undefined4 *)(param_1 + 0x34) = 0x40a2d0;
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
 * JP: 0x0054b560  @24@__dt__16DownHitSmokeCallFv
 * C++: @24@__dt__16DownHitSmokeCallFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int _24___dt__16DownHitSmokeCallFv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x18;
  if (iVar1 != 0) {
    *(undefined4 *)(param_1 + -4) = 0x40a2b0;
    *(undefined4 *)(param_1 + 0x10) = 0x40a2c0;
    *(undefined4 *)(param_1 + 0x1c) = 0x40a2d0;
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
 * JP: 0x0054b570  @44@__dt__16DownHitSmokeCallFv
 * C++: @44@__dt__16DownHitSmokeCallFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int _44___dt__16DownHitSmokeCallFv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x2c;
  if (iVar1 != 0) {
    *(undefined4 *)(param_1 + -0x18) = 0x40a2b0;
    *(undefined4 *)(param_1 + -4) = 0x40a2c0;
    *(undefined4 *)(param_1 + 8) = 0x40a2d0;
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

