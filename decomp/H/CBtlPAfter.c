/* decomp/H/CBtlPAfter.c — cleaned Ghidra output (SH2JP_BATTLE.BIN, JP Furokuban, base 0x00430a00).
 * 9 function(s). Types: see types.h. Names/gp globals resolved from symbols/SLPM_602.19.syms. */
#include "types.h"

/* ---------------------------------------------------------------------------
 * JP: 0x00587800  __ct__10CBtlPAfterFv
 * C++: CBtlPAfter::__ct()
 * size: 0x10c bytes
 * --------------------------------------------------------------------------- */
int __ct__10CBtlPAfterFv(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  __ct__7CPolObjFv(param_1);
  __ct__8VIF1PrimFv(param_1 + 0x18);
  *(undefined4 *)(param_1 + 0x2c) = 0;
  *(undefined4 *)(param_1 + 0x30) = 0;
  *(undefined4 *)(param_1 + 0x34) = 0x4049f0;
  *(undefined4 *)(param_1 + 0x14) = 0x40a730;
  *(undefined4 *)(param_1 + 0x28) = 0x40a740;
  *(undefined4 *)(param_1 + 0x34) = 0x40a750;
  *(undefined4 *)(param_1 + 0x38) = 0;
  uVar1 = __nwa__FUi(0x10);
  *(undefined4 *)(param_1 + 0x18) = uVar1;
  uVar1 = __nwa__FUi(0x10);
  *(undefined4 *)(param_1 + 0x1c) = uVar1;
  Entry__7CPollerFP7CPolObjib(iGpffff858c + 0x48,param_1,0xa0,0);
  iVar2 = param_1;
  if (param_1 != 0) {
    iVar2 = param_1 + 0x18;
  }
  AddOT__5WorldFiP8VIF1Prim(0x42bf10,7,iVar2);
  return param_1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00587910  __dt__10CBtlPAfterFv
 * C++: CBtlPAfter::__dt()
 * size: 0x114 bytes
 * --------------------------------------------------------------------------- */
int __dt__10CBtlPAfterFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x14) = 0x40a730;
    *(undefined4 *)(param_1 + 0x28) = 0x40a740;
    *(undefined4 *)(param_1 + 0x34) = 0x40a750;
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
 * JP: 0x00587a30  Polling__10CBtlPAfterFv
 * C++: CBtlPAfter::Polling()
 * size: 0x1cc4 bytes
 * --------------------------------------------------------------------------- */
undefined8 Polling__10CBtlPAfterFv(void)

{
  bool bVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  float fVar7;
  int iVar8;
  undefined1 in_vf0 [16];
  undefined1 auVar9 [16];
  undefined1 auVar10 [16];
  undefined1 auVar11 [16];
  undefined1 auStack_da0 [64];
  float afStack_d60 [76];
  int aiStack_c30 [76];
  int aiStack_b00 [32];
  int aiStack_a80 [32];
  undefined1 auStack_a00 [16];
  undefined1 auStack_9f0 [16];
  undefined1 auStack_9e0 [16];
  undefined1 auStack_9d0 [16];
  undefined4 auStack_9c0 [16];
  undefined1 auStack_980 [8];
  int aiStack_978 [302];
  float afStack_4c0 [304];
  
  auVar9 = _vmr32(in_vf0);
  auVar10 = _vmr32(auVar9);
  auVar11 = _vmr32(auVar10);
  auStack_9d0 = _sqc2(in_vf0);
  auStack_9e0 = _sqc2(auVar9);
  auStack_9f0 = _sqc2(auVar10);
  auStack_a00 = _sqc2(auVar11);
  if (*(int *)(iGpffff86b4 + 0x4324) != 0) {
    BtlCameraFunc__9BtlCameraFv(*(undefined4 *)(iGpffff86b4 + 0x4324));
  }
  if (-1 < (long)((ulong)*(byte *)(iGpffff86b4 + 0x24) << 0x3e)) {
    GetViewScreenMatrix__9GsxCameraFv(auStack_da0,uGpffff8598);
    for (iVar6 = 0; iVar6 < 4; iVar6 = iVar6 + 1) {
      auStack_9c0[iVar6 * 4] = *(undefined4 *)(auStack_a00 + iVar6 * 0x10);
      auStack_9c0[iVar6 * 4 + 1] = *(undefined4 *)(auStack_a00 + iVar6 * 0x10 + 4);
      auStack_9c0[iVar6 * 4 + 2] = *(undefined4 *)(auStack_a00 + iVar6 * 0x10 + 8);
      auStack_9c0[iVar6 * 4 + 3] = *(undefined4 *)(auStack_a00 + iVar6 * 0x10 + 0xc);
    }
    iVar4 = 0;
    iVar6 = 0;
    for (iVar5 = 0; iVar5 < 0xc; iVar5 = iVar5 + 1) {
      if ((((*(byte *)(iGpffff86b4 + iVar5 * 0x4f0 + 0xb0) & 1) != 0) &&
          ((long)((ulong)*(byte *)(iGpffff86b4 + iVar5 * 0x4f0 + 0xb0) << 0x3e) < 0)) &&
         (-1 < (long)((ulong)*(byte *)(iGpffff86b4 + iVar5 * 0x4f0 + 0xb2) << 0x3d))) {
        aiStack_c30[iVar4] = iVar5;
        iVar4 = iVar4 + 1;
        iVar6 = iVar6 + 1;
      }
    }
    iVar8 = 0;
    for (iVar5 = *(int *)(iGpffff86b4 + 0x4378); iVar5 != 0; iVar5 = *(int *)(iVar5 + 0x534)) {
      aiStack_a80[iVar8] = iVar5;
      aiStack_c30[iVar4] = iVar8 + 0x100;
      iVar8 = iVar8 + 1;
      iVar4 = iVar4 + 1;
    }
    iVar3 = 0;
    for (iVar5 = *(int *)(iGpffff86b4 + 0x4370); iVar5 != 0; iVar5 = *(int *)(iVar5 + 0x3c)) {
      if (*(int *)(iVar5 + 0x4c) == 7) {
        aiStack_b00[iVar3] = iVar5;
        aiStack_c30[iVar4] = iVar3 + 0x200;
        iVar3 = iVar3 + 1;
        iVar4 = iVar4 + 1;
      }
    }
    if (iVar4 != 0) {
      for (iVar5 = 0; iVar5 < iVar6 + iVar8; iVar5 = iVar5 + 1) {
        if (aiStack_c30[iVar5] < 0x100) {
          afStack_4c0[iVar5 * 4] =
               *(float *)(iGpffff86b4 + aiStack_c30[iVar5] * 0x4f0 + 0x150) +
               *(float *)(iGpffff86b4 + aiStack_c30[iVar5] * 0x4f0 + 0x390);
          afStack_4c0[iVar5 * 4 + 1] =
               *(float *)(iGpffff86b4 + aiStack_c30[iVar5] * 0x4f0 + 0x154) +
               *(float *)(iGpffff86b4 + aiStack_c30[iVar5] * 0x4f0 + 0x394);
          afStack_4c0[iVar5 * 4 + 2] =
               *(float *)(iGpffff86b4 + aiStack_c30[iVar5] * 0x4f0 + 0x158) +
               *(float *)(iGpffff86b4 + aiStack_c30[iVar5] * 0x4f0 + 0x398);
        }
        else if (aiStack_c30[iVar5] < 0x200) {
          afStack_4c0[iVar5 * 4] = *(float *)(aiStack_a80[aiStack_c30[iVar5] + -0x100] + 0x540);
          afStack_4c0[iVar5 * 4 + 1] = *(float *)(aiStack_a80[aiStack_c30[iVar5] + -0x100] + 0x544);
          afStack_4c0[iVar5 * 4 + 2] = *(float *)(aiStack_a80[aiStack_c30[iVar5] + -0x100] + 0x548);
        }
        afStack_4c0[iVar5 * 4 + 3] = 1.0;
      }
      sceVu0RotTransPersN(auStack_980,auStack_9c0,afStack_4c0,iVar6 + iVar8,0);
      for (iVar5 = 0; iVar5 < iVar6 + iVar8; iVar5 = iVar5 + 1) {
        afStack_d60[iVar5] = (float)aiStack_978[iVar5 * 4] / 16.0;
      }
      for (iVar5 = iVar6 + iVar8; iVar5 < iVar3 + iVar6 + iVar8; iVar5 = iVar5 + 1) {
        afStack_d60[iVar5] = (float)*(int *)(aiStack_b00[aiStack_c30[iVar5] + -0x200] + 0x50) / 16.0
        ;
      }
      for (iVar6 = 0; iVar5 = iVar6, iVar8 = iVar6, iVar6 < iVar4; iVar6 = iVar6 + 1) {
        for (; iVar8 < iVar4; iVar8 = iVar8 + 1) {
          iVar3 = iVar8;
          if (afStack_d60[iVar5] <= afStack_d60[iVar8]) {
            iVar3 = iVar5;
          }
          iVar5 = iVar3;
        }
        if (*(char *)(iGpffff86b4 + 0x45ac) == '\0') {
          if (*(char *)(iGpffff86b4 + 0x45b4) == '\0') {
            if (((0xff < aiStack_c30[iVar5]) && (aiStack_c30[iVar5] < 0x200)) &&
               (iVar8 = iVar5, iVar3 = iVar6,
               *(int *)(aiStack_a80[aiStack_c30[iVar5] + -0x100] + 0x5a0) == 0xd)) {
              for (; (iVar5 = iVar8, iVar3 < iVar4 &&
                     ((0xff < aiStack_c30[iVar3] ||
                      (iVar5 = iVar3,
                      aiStack_c30[iVar3] !=
                      *(int *)(aiStack_a80[aiStack_c30[iVar8] + -0x100] + 0x5a8)))));
                  iVar3 = iVar3 + 1) {
                iVar5 = iVar8;
                if ((0xff < aiStack_c30[iVar3]) &&
                   ((((aiStack_c30[iVar3] < 0x200 &&
                      (*(int *)(aiStack_a80[aiStack_c30[iVar8] + -0x100] + 0x5a8) ==
                       *(int *)(aiStack_a80[aiStack_c30[iVar3] + -0x100] + 0x5a8))) &&
                     (*(int *)(aiStack_a80[aiStack_c30[iVar3] + -0x100] + 0x5a0) == 0xd)) &&
                    (iVar5 = iVar3,
                    *(float *)(aiStack_a80[aiStack_c30[iVar8] + -0x100] + 0x560) <=
                    *(float *)(aiStack_a80[aiStack_c30[iVar3] + -0x100] + 0x560))))) {
                  iVar5 = iVar8;
                }
                iVar8 = iVar5;
              }
            }
          }
          else {
            bVar1 = false;
            if (aiStack_c30[iVar5] < 0x100) {
              if ((long)*(char *)(iGpffff86b4 + 0x45b7) == (long)aiStack_c30[iVar5]) {
                bVar1 = true;
              }
            }
            else if ((aiStack_c30[iVar5] < 0x200) &&
                    ((*(int *)(aiStack_a80[aiStack_c30[iVar5] + -0x100] + 0x5a0) == 0xb ||
                     (*(int *)(aiStack_a80[aiStack_c30[iVar5] + -0x100] + 0x5a0) == 0xc)))) {
              bVar1 = true;
            }
            if (bVar1) {
              uVar2 = 4;
              for (iVar8 = iVar6; iVar8 < iVar4; iVar8 = iVar8 + 1) {
                if (aiStack_c30[iVar8] < 0x100) {
                  if (((long)*(char *)(iGpffff86b4 + 0x45b6) == (long)aiStack_c30[iVar8]) &&
                     (uVar2 != 0)) {
                    uVar2 = 0;
                    iVar5 = iVar8;
                  }
                  else if (((long)*(char *)(iGpffff86b4 + 0x45b7) == (long)aiStack_c30[iVar8]) &&
                          (1 < uVar2)) {
                    uVar2 = 1;
                    iVar5 = iVar8;
                  }
                }
                else if (aiStack_c30[iVar8] < 0x200) {
                  if ((*(int *)(aiStack_a80[aiStack_c30[iVar8] + -0x100] + 0x5a0) == 0xc) &&
                     (2 < uVar2)) {
                    uVar2 = 2;
                    iVar5 = iVar8;
                  }
                  else if ((*(int *)(aiStack_a80[aiStack_c30[iVar8] + -0x100] + 0x5a0) == 0xb) &&
                          (3 < uVar2)) {
                    uVar2 = 3;
                    iVar5 = iVar8;
                  }
                }
              }
            }
          }
        }
        else {
          bVar1 = false;
          if (aiStack_c30[iVar5] < 0x100) {
            if ((long)*(char *)(iGpffff86b4 + 0x45af) == (long)aiStack_c30[iVar5]) {
              bVar1 = true;
            }
          }
          else if ((aiStack_c30[iVar5] < 0x200) &&
                  ((*(int *)(aiStack_a80[aiStack_c30[iVar5] + -0x100] + 0x5a0) == 9 ||
                   (*(int *)(aiStack_a80[aiStack_c30[iVar5] + -0x100] + 0x5a0) == 10)))) {
            bVar1 = true;
          }
          if (bVar1) {
            uVar2 = 4;
            for (iVar8 = iVar6; iVar8 < iVar4; iVar8 = iVar8 + 1) {
              if (aiStack_c30[iVar8] < 0x100) {
                if (((long)*(char *)(iGpffff86b4 + 0x45ae) == (long)aiStack_c30[iVar8]) &&
                   (uVar2 != 0)) {
                  uVar2 = 0;
                  iVar5 = iVar8;
                }
                else if (((long)*(char *)(iGpffff86b4 + 0x45af) == (long)aiStack_c30[iVar8]) &&
                        (1 < uVar2)) {
                  uVar2 = 1;
                  iVar5 = iVar8;
                }
              }
              else if (aiStack_c30[iVar8] < 0x200) {
                if ((*(int *)(aiStack_a80[aiStack_c30[iVar8] + -0x100] + 0x5a0) == 10) &&
                   (2 < uVar2)) {
                  uVar2 = 2;
                  iVar5 = iVar8;
                }
                else if ((*(int *)(aiStack_a80[aiStack_c30[iVar8] + -0x100] + 0x5a0) == 9) &&
                        (3 < uVar2)) {
                  uVar2 = 3;
                  iVar5 = iVar8;
                }
              }
            }
          }
        }
        iVar8 = aiStack_c30[iVar5];
        aiStack_c30[iVar5] = aiStack_c30[iVar6];
        aiStack_c30[iVar6] = iVar8;
        fVar7 = afStack_d60[iVar5];
        afStack_d60[iVar5] = afStack_d60[iVar6];
        afStack_d60[iVar6] = fVar7;
        if (aiStack_c30[iVar6] < 0x100) {
          iVar5 = aiStack_c30[iVar6];
          if ((long)((ulong)*(byte *)(*(int *)(iGpffff86b4 + aiStack_c30[iVar6] * 0x4f0 + 0x144) +
                                     0x4b0) << 0x3e) < 0) {
            iVar8 = (int)(*(float *)(*(int *)(iGpffff86b4 + aiStack_c30[iVar6] * 0x4f0 + 0x144) +
                                    0x4e4) *
                          *(float *)(*(int *)(iGpffff86b4 + aiStack_c30[iVar6] * 0x4f0 + 0x144) +
                                    0x4ec) * 128.0);
            if (iVar8 == 0x80) {
              OTRelease__8BtlModelFv
                        (*(undefined4 *)(iGpffff86b4 + aiStack_c30[iVar6] * 0x4f0 + 0x144));
              OTEntry__8BtlModelFii
                        (*(undefined4 *)(iGpffff86b4 + aiStack_c30[iVar6] * 0x4f0 + 0x144),4,8);
              for (iVar8 = 0; iVar3 = iVar6, iVar8 < 0x10; iVar8 = iVar8 + 4) {
                if (((*(int *)(iGpffff86b4 + iVar8 * 4 + 0x3bf0) != 0) &&
                    ((long)*(short *)(*(int *)(iGpffff86b4 + iVar8 * 4 + 0x3bf0) + 0x4b4) ==
                     (long)aiStack_c30[iVar6])) &&
                   (iVar3 = iVar8,
                   (long)((ulong)*(byte *)(*(int *)(iGpffff86b4 + iVar8 * 4 + 0x3bf0) + 0x4b1) <<
                         0x39) < 0)) {
                  for (; iVar3 < iVar8 + 4; iVar3 = iVar3 + 1) {
                    OTRelease__8BtlModelFv(*(undefined4 *)(iGpffff86b4 + iVar3 * 4 + 0x3bf0));
                    OTEntry__8BtlModelFii(*(undefined4 *)(iGpffff86b4 + iVar3 * 4 + 0x3bf0),4,8);
                  }
                }
              }
              do {
                iVar3 = iVar3 + 1;
                if (iVar4 <= iVar3) goto LAB_00589028;
              } while (((aiStack_c30[iVar3] < 0x100) || (0x1ff < aiStack_c30[iVar3])) ||
                      ((*(int *)(aiStack_a80[aiStack_c30[iVar3] + -0x100] + 0x5a0) != 0xd ||
                       (aiStack_c30[iVar6] !=
                        *(int *)(aiStack_a80[aiStack_c30[iVar3] + -0x100] + 0x5a8)))));
              iVar6 = iVar6 + 1;
              iVar8 = aiStack_c30[iVar3];
              aiStack_c30[iVar3] = aiStack_c30[iVar6];
              aiStack_c30[iVar6] = iVar8;
              fVar7 = afStack_d60[iVar3];
              afStack_d60[iVar3] = afStack_d60[iVar6];
              afStack_d60[iVar6] = fVar7;
              OTRelease__6EffMdlFv(aiStack_a80[aiStack_c30[iVar6] + -0x100]);
              OTEntry__6EffMdlFii(aiStack_a80[aiStack_c30[iVar6] + -0x100],4,8);
            }
            else if (iVar8 < 1) {
              OTRelease__8BtlModelFv
                        (*(undefined4 *)(iGpffff86b4 + aiStack_c30[iVar6] * 0x4f0 + 0x144));
              iVar8 = *(int *)(iGpffff86b4 + aiStack_c30[iVar6] * 0x4f0 + 0x144);
              *(byte *)(iVar8 + 0x4b0) = *(byte *)(iVar8 + 0x4b0) & 0xfd | 2;
              for (iVar8 = 0; iVar3 = iVar6, iVar8 < 0x10; iVar8 = iVar8 + 4) {
                if (((*(int *)(iGpffff86b4 + iVar8 * 4 + 0x3bf0) != 0) &&
                    ((long)*(short *)(*(int *)(iGpffff86b4 + iVar8 * 4 + 0x3bf0) + 0x4b4) ==
                     (long)aiStack_c30[iVar6])) &&
                   (iVar3 = iVar8,
                   (long)((ulong)*(byte *)(*(int *)(iGpffff86b4 + iVar8 * 4 + 0x3bf0) + 0x4b1) <<
                         0x39) < 0)) {
                  for (; iVar3 < iVar8 + 4; iVar3 = iVar3 + 1) {
                    OTRelease__8BtlModelFv(*(undefined4 *)(iGpffff86b4 + iVar3 * 4 + 0x3bf0));
                  }
                }
              }
              do {
                iVar3 = iVar3 + 1;
                if (iVar4 <= iVar3) goto LAB_00589028;
              } while (((aiStack_c30[iVar3] < 0x100) || (0x1ff < aiStack_c30[iVar3])) ||
                      ((*(int *)(aiStack_a80[aiStack_c30[iVar3] + -0x100] + 0x5a0) != 0xd ||
                       (aiStack_c30[iVar6] !=
                        *(int *)(aiStack_a80[aiStack_c30[iVar3] + -0x100] + 0x5a8)))));
              iVar6 = iVar6 + 1;
              iVar8 = aiStack_c30[iVar3];
              aiStack_c30[iVar3] = aiStack_c30[iVar6];
              aiStack_c30[iVar6] = iVar8;
              fVar7 = afStack_d60[iVar3];
              afStack_d60[iVar3] = afStack_d60[iVar6];
              afStack_d60[iVar6] = fVar7;
              OTRelease__6EffMdlFv(aiStack_a80[aiStack_c30[iVar6] + -0x100]);
            }
            else {
              OTRelease__8BtlModelFv
                        (*(undefined4 *)(iGpffff86b4 + aiStack_c30[iVar6] * 0x4f0 + 0x144));
              OTEntry__8BtlModelFii
                        (*(undefined4 *)(iGpffff86b4 + aiStack_c30[iVar6] * 0x4f0 + 0x144),4,8);
              for (iVar8 = 0; iVar3 = iVar6, iVar8 < 0x10; iVar8 = iVar8 + 4) {
                if (((*(int *)(iGpffff86b4 + iVar8 * 4 + 0x3bf0) != 0) &&
                    ((long)*(short *)(*(int *)(iGpffff86b4 + iVar8 * 4 + 0x3bf0) + 0x4b4) ==
                     (long)aiStack_c30[iVar6])) &&
                   (iVar3 = iVar8,
                   (long)((ulong)*(byte *)(*(int *)(iGpffff86b4 + iVar8 * 4 + 0x3bf0) + 0x4b1) <<
                         0x39) < 0)) {
                  for (; iVar3 < iVar8 + 4; iVar3 = iVar3 + 1) {
                    OTRelease__8BtlModelFv(*(undefined4 *)(iGpffff86b4 + iVar3 * 4 + 0x3bf0));
                    OTEntry__8BtlModelFii(*(undefined4 *)(iGpffff86b4 + iVar3 * 4 + 0x3bf0),4,8);
                  }
                }
              }
              do {
                iVar3 = iVar3 + 1;
                if (iVar4 <= iVar3) goto LAB_00589028;
              } while ((((aiStack_c30[iVar3] < 0x100) || (0x1ff < aiStack_c30[iVar3])) ||
                       (*(int *)(aiStack_a80[aiStack_c30[iVar3] + -0x100] + 0x5a0) != 0xd)) ||
                      (aiStack_c30[iVar6] !=
                       *(int *)(aiStack_a80[aiStack_c30[iVar3] + -0x100] + 0x5a8)));
              iVar6 = iVar6 + 1;
              iVar8 = aiStack_c30[iVar3];
              aiStack_c30[iVar3] = aiStack_c30[iVar6];
              aiStack_c30[iVar6] = iVar8;
              fVar7 = afStack_d60[iVar3];
              afStack_d60[iVar3] = afStack_d60[iVar6];
              afStack_d60[iVar6] = fVar7;
              OTRelease__6EffMdlFv(aiStack_a80[aiStack_c30[iVar6] + -0x100]);
              OTEntry__6EffMdlFii(aiStack_a80[aiStack_c30[iVar6] + -0x100],4,8);
            }
LAB_00589028:
            for (iVar8 = *(int *)(iGpffff86b4 + iVar5 * 0x4f0 + 0x54c); iVar8 != 0;
                iVar8 = *(int *)(iVar8 + 0x3c)) {
              if ((*(int *)(iVar8 + 0x4c) == 6) &&
                 ((long)((ulong)*(byte *)(iVar8 + 0x40) << 0x3e) < 0)) {
                iVar3 = iVar8;
                if (iVar8 != 0) {
                  iVar3 = iVar8 + 0x18;
                }
                ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,iVar3);
                if ((long)((ulong)*(byte *)(*(int *)(iGpffff86b4 + iVar5 * 0x4f0 + 0x144) + 0x4b0)
                          << 0x3e) < 0) {
                  iVar3 = iVar8;
                  if (iVar8 != 0) {
                    iVar3 = iVar8 + 0x18;
                  }
                  AddOT__5WorldFiP8VIF1Prim(0x42bf10,8,iVar3);
                }
              }
            }
            for (iVar8 = *(int *)(iGpffff86b4 + iVar5 * 0x4f0 + 0x54c); iVar8 != 0;
                iVar8 = *(int *)(iVar8 + 0x3c)) {
              if ((*(int *)(iVar8 + 0x4c) == 7) &&
                 ((long)((ulong)*(byte *)(iVar8 + 0x40) << 0x3e) < 0)) {
                iVar3 = iVar8;
                if (iVar8 != 0) {
                  iVar3 = iVar8 + 0x18;
                }
                ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,iVar3);
                iVar3 = iVar8;
                if (iVar8 != 0) {
                  iVar3 = iVar8 + 0x18;
                }
                AddOT__5WorldFiP8VIF1Prim(0x42bf10,8,iVar3);
              }
            }
            for (iVar8 = *(int *)(iGpffff86b4 + iVar5 * 0x4f0 + 0x54c); iVar8 != 0;
                iVar8 = *(int *)(iVar8 + 0x3c)) {
              if ((*(int *)(iVar8 + 0x4c) == 0x17) &&
                 ((long)((ulong)*(byte *)(iVar8 + 0x40) << 0x3e) < 0)) {
                iVar3 = iVar8;
                if (iVar8 != 0) {
                  iVar3 = iVar8 + 0x18;
                }
                ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,iVar3);
                iVar3 = iVar8;
                if (iVar8 != 0) {
                  iVar3 = iVar8 + 0x18;
                }
                AddOT__5WorldFiP8VIF1Prim(0x42bf10,8,iVar3);
              }
            }
            for (iVar8 = *(int *)(iGpffff86b4 + iVar5 * 0x4f0 + 0x54c); iVar8 != 0;
                iVar8 = *(int *)(iVar8 + 0x3c)) {
              if (((*(int *)(iVar8 + 0x4c) == 0x14) && (*(int *)(iVar8 + 0x48) == iVar5)) &&
                 ((long)((ulong)*(byte *)(iVar8 + 0x40) << 0x3e) < 0)) {
                iVar3 = iVar8;
                if (iVar8 != 0) {
                  iVar3 = iVar8 + 0x18;
                }
                ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,iVar3);
                iVar3 = iVar8;
                if (iVar8 != 0) {
                  iVar3 = iVar8 + 0x18;
                }
                AddOT__5WorldFiP8VIF1Prim(0x42bf10,4,iVar3);
              }
            }
          }
          else {
            for (iVar8 = *(int *)(iGpffff86b4 + iVar5 * 0x4f0 + 0x54c); iVar8 != 0;
                iVar8 = *(int *)(iVar8 + 0x3c)) {
              if ((*(int *)(iVar8 + 0x4c) == 6) &&
                 ((long)((ulong)*(byte *)(iVar8 + 0x40) << 0x3e) < 0)) {
                iVar3 = iVar8;
                if (iVar8 != 0) {
                  iVar3 = iVar8 + 0x18;
                }
                ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,iVar3);
              }
            }
            for (iVar8 = *(int *)(iGpffff86b4 + iVar5 * 0x4f0 + 0x54c); iVar8 != 0;
                iVar8 = *(int *)(iVar8 + 0x3c)) {
              if ((*(int *)(iVar8 + 0x4c) == 7) &&
                 ((long)((ulong)*(byte *)(iVar8 + 0x40) << 0x3e) < 0)) {
                iVar3 = iVar8;
                if (iVar8 != 0) {
                  iVar3 = iVar8 + 0x18;
                }
                ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,iVar3);
                iVar3 = iVar8;
                if (iVar8 != 0) {
                  iVar3 = iVar8 + 0x18;
                }
                AddOT__5WorldFiP8VIF1Prim(0x42bf10,8,iVar3);
              }
            }
            for (iVar8 = *(int *)(iGpffff86b4 + iVar5 * 0x4f0 + 0x54c); iVar8 != 0;
                iVar8 = *(int *)(iVar8 + 0x3c)) {
              if ((*(int *)(iVar8 + 0x4c) == 0x17) &&
                 ((long)((ulong)*(byte *)(iVar8 + 0x40) << 0x3e) < 0)) {
                iVar3 = iVar8;
                if (iVar8 != 0) {
                  iVar3 = iVar8 + 0x18;
                }
                ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,iVar3);
                iVar3 = iVar8;
                if (iVar8 != 0) {
                  iVar3 = iVar8 + 0x18;
                }
                AddOT__5WorldFiP8VIF1Prim(0x42bf10,8,iVar3);
              }
            }
            for (iVar5 = *(int *)(iGpffff86b4 + iVar5 * 0x4f0 + 0x54c); iVar5 != 0;
                iVar5 = *(int *)(iVar5 + 0x3c)) {
              if ((*(int *)(iVar5 + 0x4c) == 0x14) &&
                 ((long)((ulong)*(byte *)(iVar5 + 0x40) << 0x3e) < 0)) {
                iVar8 = iVar5;
                if (iVar5 != 0) {
                  iVar8 = iVar5 + 0x18;
                }
                ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,iVar8);
              }
            }
          }
        }
        else if (aiStack_c30[iVar6] < 0x200) {
          if ((*(byte *)(aiStack_a80[aiStack_c30[iVar6] + -0x100] + 0x538) & 1) != 0) {
            OTRelease__6EffMdlFv(aiStack_a80[aiStack_c30[iVar6] + -0x100]);
            OTEntry__6EffMdlFii(aiStack_a80[aiStack_c30[iVar6] + -0x100],4,8);
          }
        }
        else if ((long)((ulong)*(byte *)(aiStack_b00[aiStack_c30[iVar6] + -0x200] + 0x40) << 0x3e) <
                 0) {
          iVar5 = aiStack_b00[aiStack_c30[iVar6] + -0x200];
          if (iVar5 != 0) {
            iVar5 = iVar5 + 0x18;
          }
          ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,iVar5);
          iVar5 = aiStack_b00[aiStack_c30[iVar6] + -0x200];
          if (iVar5 != 0) {
            iVar5 = iVar5 + 0x18;
          }
          AddOT__5WorldFiP8VIF1Prim(0x42bf10,4,iVar5);
        }
      }
    }
  }
  return 0;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00589700  Destruct__10CBtlPAfterFv
 * C++: CBtlPAfter::Destruct()
 * size: 0x78 bytes
 * --------------------------------------------------------------------------- */
void Destruct__10CBtlPAfterFv(int param_1)

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
 * JP: 0x00589780  MakePacket__10CBtlPAfterFv
 * C++: CBtlPAfter::MakePacket()
 * size: 0x3bc bytes
 * --------------------------------------------------------------------------- */
void MakePacket__10CBtlPAfterFv(int param_1)

{
  bool bVar1;
  int iVar2;
  long lVar3;
  undefined4 *puVar4;
  int iVar5;
  int unaff_s4_lo;
  uint uVar6;
  int iVar7;
  int iStack_14;
  
  uVar6 = (uint)(*(int *)(param_1 + 0x38) == 0);
  puVar4 = *(undefined4 **)(param_1 + uVar6 * 4 + 0x18);
  if ((long)((ulong)*(byte *)(iGpffff86b4 + 0x24) << 0x3e) < 0) {
    *puVar4 = 0x60000000;
    puVar4[1] = 0;
    puVar4[2] = 0;
    puVar4[3] = 0;
    *(uint *)(param_1 + 0x38) = uVar6;
  }
  else {
    *(undefined4 *)(param_1 + 0x3c) = 0xffffffff;
    iVar7 = 0;
    while( true ) {
      bVar1 = false;
      iVar5 = 0;
      for (iVar2 = *(int *)(iGpffff86b4 + 0x4370); iVar2 != 0; iVar2 = *(int *)(iVar2 + 0x3c)) {
        if ((((*(int *)(iVar2 + 0x4c) == 0) || (*(int *)(iVar2 + 0x4c) == 1)) ||
            (*(int *)(iVar2 + 0x4c) == 5)) || (*(int *)(iVar2 + 0x4c) == 6)) {
          if (iVar7 == 0) {
            if (bVar1) {
              if (*(int *)(iVar2 + 0x50) < unaff_s4_lo) {
                unaff_s4_lo = *(int *)(iVar2 + 0x50);
                iVar5 = iVar2;
              }
            }
            else {
              unaff_s4_lo = *(int *)(iVar2 + 0x50);
              bVar1 = true;
              iVar5 = iVar2;
            }
          }
          else if (iStack_14 <= *(int *)(iVar2 + 0x50)) {
            if (bVar1) {
              if (*(int *)(iVar2 + 0x50) < unaff_s4_lo) {
                unaff_s4_lo = *(int *)(iVar2 + 0x50);
                iVar5 = iVar2;
              }
            }
            else {
              unaff_s4_lo = *(int *)(iVar2 + 0x50);
              bVar1 = true;
              iVar5 = iVar2;
            }
          }
        }
      }
      if (iVar5 == 0) break;
      iVar2 = (**(code **)(*(int *)(iVar5 + 0x14) + 0x34))();
      if (iVar2 != 0) {
        *puVar4 = 0x20000000;
        puVar4[1] = iVar2;
        puVar4[2] = 0;
        puVar4[3] = 0;
        puVar4 = *(undefined4 **)(iVar5 + 0x54);
      }
      *(int *)(iVar5 + 0x50) = *(int *)(iVar5 + 0x50) + -1;
      iVar7 = iVar7 + 1;
      iStack_14 = unaff_s4_lo;
    }
    for (iVar7 = 0; iVar7 < 0xc; iVar7 = iVar7 + 1) {
      if ((((*(byte *)(iGpffff86b4 + iVar7 * 0x4f0 + 0xb0) & 1) != 0) &&
          ((long)((ulong)*(byte *)(iGpffff86b4 + iVar7 * 0x4f0 + 0xb0) << 0x3e) < 0)) &&
         (-1 < (long)((ulong)*(byte *)(iGpffff86b4 + iVar7 * 0x4f0 + 0xb2) << 0x3d))) {
        for (iVar2 = *(int *)(iGpffff86b4 + iVar7 * 0x4f0 + 0x54c); iVar2 != 0;
            iVar2 = *(int *)(iVar2 + 0x3c)) {
          if (((*(int *)(iVar2 + 0x4c) == 8) || (*(int *)(iVar2 + 0x4c) == 9)) ||
             (*(int *)(iVar2 + 0x4c) == 10)) {
            lVar3 = (**(code **)(*(int *)(iVar2 + 0x14) + 0x34))();
            if (lVar3 != 0) {
              *puVar4 = 0x20000000;
              puVar4[1] = (int)lVar3;
              puVar4[2] = 0;
              puVar4[3] = 0;
              puVar4 = *(undefined4 **)(iVar2 + 0x54);
            }
          }
        }
      }
    }
    *puVar4 = 0x60000000;
    puVar4[1] = 0;
    puVar4[2] = 0;
    puVar4[3] = 0;
    *(uint *)(param_1 + 0x38) = uVar6;
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0058bad0  getPacket__10CBtlPAfterFv
 * C++: CBtlPAfter::getPacket()
 * size: 0x40 bytes
 * --------------------------------------------------------------------------- */
undefined4 getPacket__10CBtlPAfterFv(int param_1)

{
  MakePacket__10CBtlPAfterFv(param_1);
  return *(undefined4 *)(param_1 + *(int *)(param_1 + 0x38) * 4 + 0x18);
}

/* ---------------------------------------------------------------------------
 * JP: 0x0058bb40  @24@getPacket__10CBtlPAfterFv
 * C++: @24@getPacket__10CBtlPAfterFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
undefined4 _24_getPacket__10CBtlPAfterFv(int param_1)

{
  MakePacket__10CBtlPAfterFv(param_1 + -0x18);
  return *(undefined4 *)(param_1 + -0x18 + *(int *)(param_1 + 0x20) * 4 + 0x18);
}

/* ---------------------------------------------------------------------------
 * JP: 0x0058bb50  @24@__dt__10CBtlPAfterFv
 * C++: @24@__dt__10CBtlPAfterFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int * _24___dt__10CBtlPAfterFv(int *param_1,short param_2)

{
  int *piVar1;
  
  piVar1 = param_1 + -6;
  if (piVar1 != (int *)0x0) {
    param_1[-1] = 0x40a730;
    param_1[4] = 0x40a740;
    param_1[7] = 0x40a750;
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
 * JP: 0x0058bb60  @44@__dt__10CBtlPAfterFv
 * C++: @44@__dt__10CBtlPAfterFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int _44___dt__10CBtlPAfterFv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x2c;
  if (iVar1 != 0) {
    *(undefined4 *)(param_1 + -0x18) = 0x40a730;
    *(undefined4 *)(param_1 + -4) = 0x40a740;
    *(undefined4 *)(param_1 + 8) = 0x40a750;
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

