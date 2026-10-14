/* decomp/H/ComboForm.c — cleaned Ghidra output (SH2JP_BATTLE.BIN, JP Furokuban, base 0x00430a00).
 * 10 function(s). Types: see types.h. Names/gp globals resolved from symbols/SLPM_602.19.syms. */
#include "types.h"

/* ---------------------------------------------------------------------------
 * JP: 0x004f0c00  __ct__9ComboFormFv
 * C++: ComboForm::__ct()
 * size: 0x1f8 bytes
 * --------------------------------------------------------------------------- */
int __ct__9ComboFormFv(int param_1)

{
  int iVar1;
  int iVar2;
  
  __ct__7CPolObjFv(param_1);
  __ct__8VIF1PrimFv(param_1 + 0x18);
  *(undefined4 *)(param_1 + 0x2c) = 0;
  *(undefined4 *)(param_1 + 0x30) = 0;
  *(undefined4 *)(param_1 + 0x34) = 0x4049f0;
  *(undefined4 *)(param_1 + 0x14) = 0x40a570;
  *(undefined4 *)(param_1 + 0x28) = 0x40a580;
  *(undefined4 *)(param_1 + 0x34) = 0x40a590;
  *(undefined4 *)(param_1 + 0x38) = 0;
  *(undefined4 *)(param_1 + 0x3c) = 0;
  *(undefined4 *)(param_1 + 0x4c) = 0;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  *(undefined4 *)(param_1 + 0x18) = 0;
  *(undefined4 *)(param_1 + 0x40) = 0;
  *(undefined4 *)(param_1 + 0x48) = 0;
  *(undefined4 *)(param_1 + 0x44) = 0;
  for (iVar2 = 0; iVar2 < 0xc; iVar2 = iVar2 + 1) {
    *(undefined1 *)(param_1 + iVar2 + 0x50) = 0;
    *(undefined4 *)(param_1 + iVar2 * 8 + 0x74) = 0;
    *(undefined4 *)(param_1 + iVar2 * 8 + 0x78) = 0;
    *(undefined2 *)(param_1 + iVar2 * 2 + 0x5c) = 0;
    iVar1 = rand();
    *(float *)(param_1 + iVar2 * 4 + 0xd4) = ((float)iVar1 / 2.1474836e+09) * 6.2831855 - 3.1415927;
  }
  *(undefined4 *)(param_1 + 0x108) = 0;
  Entry__7CPollerFP7CPolObjib(iGpffff858c + 0x48,param_1,0xa0,0);
  iVar2 = param_1;
  if (param_1 != 0) {
    iVar2 = param_1 + 0x18;
  }
  AddOT__5WorldFiP8VIF1Prim(0x42bf10,3,iVar2);
  return param_1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x004f0e00  __dt__9ComboFormFv
 * C++: ComboForm::__dt()
 * size: 0x114 bytes
 * --------------------------------------------------------------------------- */
int __dt__9ComboFormFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x14) = 0x40a570;
    *(undefined4 *)(param_1 + 0x28) = 0x40a580;
    *(undefined4 *)(param_1 + 0x34) = 0x40a590;
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
 * JP: 0x004f0f20  Destruct__9ComboFormFv
 * C++: ComboForm::Destruct()
 * size: 0x78 bytes
 * --------------------------------------------------------------------------- */
void Destruct__9ComboFormFv(int param_1)

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
 * JP: 0x004f0fa0  Polling__9ComboFormFv
 * C++: ComboForm::Polling()
 * size: 0x1198 bytes
 * --------------------------------------------------------------------------- */
undefined8 Polling__9ComboFormFv(int param_1)

{
  char cVar1;
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  int iVar2;
  undefined8 uVar3;
  undefined4 *puVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  undefined4 uVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  undefined1 in_vf0 [16];
  undefined1 auVar13 [16];
  undefined1 auVar14 [16];
  undefined1 auVar15 [16];
  undefined1 auStack_2a0 [16];
  undefined1 auStack_290 [16];
  undefined1 auStack_280 [16];
  undefined1 auStack_270 [8];
  undefined4 uStack_268;
  undefined4 uStack_264;
  undefined1 auStack_260 [8];
  undefined4 uStack_258;
  undefined4 uStack_254;
  undefined1 auStack_250 [8];
  undefined4 uStack_248;
  undefined4 uStack_244;
  undefined1 auStack_240 [8];
  undefined4 uStack_238;
  undefined4 uStack_234;
  undefined4 uStack_230;
  undefined4 uStack_22c;
  undefined4 uStack_228;
  undefined4 uStack_224;
  float afStack_220 [12];
  undefined4 auStack_1f0 [48];
  undefined1 auStack_130 [16];
  undefined1 auStack_120 [16];
  undefined1 auStack_110 [16];
  undefined1 auStack_100 [16];
  undefined4 auStack_f0 [51];
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  puVar4 = auStack_f0;
  auStack_f0[0x30] = in_zero_lo;
  auStack_f0[0x31] = in_zero_hi;
  auStack_f0[0x32] = in_zero_udw;
  do {
    *puVar4 = in_zero_lo;
    puVar4[1] = in_zero_hi;
    puVar4[2] = in_zero_udw;
    puVar4[3] = in_register_0000000c;
    puVar4 = puVar4 + 4;
  } while (puVar4 != auStack_f0 + 0x30);
  auVar13 = _vmr32(in_vf0);
  auVar14 = _vmr32(auVar13);
  auVar15 = _vmr32(auVar14);
  auStack_100 = _sqc2(in_vf0);
  auStack_110 = _sqc2(auVar13);
  auStack_120 = _sqc2(auVar14);
  auStack_130 = _sqc2(auVar15);
  fVar12 = *(float *)(iGpffff86b4 + 0x38);
  if ((*(byte *)(iGpffff86b4 + 0x24) & 1) != 0) {
    fVar12 = 0.0;
  }
  *(float *)(param_1 + 0x3c) = *(float *)(param_1 + 0x3c) + fVar12 * 6.2831855;
  if (3.1415927 <= *(float *)(param_1 + 0x3c)) {
    *(float *)(param_1 + 0x3c) = *(float *)(param_1 + 0x3c) - 6.2831855;
  }
  puVar4 = auStack_1f0;
  do {
    *puVar4 = in_zero_lo;
    puVar4[1] = in_zero_hi;
    puVar4[2] = in_zero_udw;
    puVar4[3] = in_register_0000000c;
    puVar4 = puVar4 + 4;
  } while (puVar4 != (undefined4 *)auStack_130);
  uStack_24 = in_register_0000000c;
  uStack_20 = in_zero_lo;
  uStack_1c = in_zero_hi;
  uStack_18 = in_zero_udw;
  uStack_14 = in_register_0000000c;
  uStack_10 = in_zero_lo;
  uStack_c = in_zero_hi;
  uStack_8 = in_zero_udw;
  uStack_4 = in_register_0000000c;
  for (iVar5 = 0; iVar5 < 0xc; iVar5 = iVar5 + 1) {
    if ((((*(byte *)(iGpffff86b4 + iVar5 * 0x4f0 + 0xb0) & 1) != 0) &&
        ((long)((ulong)*(byte *)(iGpffff86b4 + iVar5 * 0x4f0 + 0xb0) << 0x3e) < 0)) &&
       (-1 < (long)((ulong)*(byte *)(iGpffff86b4 + iVar5 * 0x4f0 + 0xb2) << 0x3d))) {
      uStack_228 = *(undefined4 *)(iGpffff86b4 + iVar5 * 0x4f0 + 0x3b8);
      uStack_230 = *(undefined4 *)(iGpffff86b4 + iVar5 * 0x4f0 + 0x3b4);
      uStack_22c = 0;
      uStack_224 = 0x3f800000;
      auStack_1f0[iVar5 * 4] = uStack_230;
      auStack_1f0[iVar5 * 4 + 1] = 0;
      auStack_1f0[iVar5 * 4 + 2] = uStack_228;
      auStack_1f0[iVar5 * 4 + 3] = 0x3f800000;
      auVar13 = _vmr32(in_vf0);
      auVar14 = _vmr32(auVar13);
      auVar15 = _vmr32(auVar14);
      auStack_100 = _sqc2(in_vf0);
      auStack_110 = _sqc2(auVar13);
      auStack_120 = _sqc2(auVar14);
      auStack_130 = _sqc2(auVar15);
      uVar9 = GetRad(*(undefined4 *)(iGpffff86b4 + iVar5 * 0x4f0 + 0x174));
      sceVu0RotMatrixY(uVar9,auStack_130,auStack_130);
      ApplyMatrix__6MatrixCFRC7FVector(auStack_240,auStack_130,auStack_1f0 + iVar5 * 4);
      auStack_1f0[iVar5 * 4] = auStack_240._0_4_;
      auStack_1f0[iVar5 * 4 + 1] = auStack_240._4_4_;
      auStack_1f0[iVar5 * 4 + 2] = uStack_238;
      auStack_1f0[iVar5 * 4 + 3] = uStack_234;
      afStack_220[iVar5] = *(float *)(iGpffff86b4 + iVar5 * 0x4f0 + 0x3b0);
    }
  }
  for (uVar8 = 0; (int)uVar8 < 0xc; uVar8 = uVar8 + 1) {
    iVar5 = param_1 + uVar8 * 4;
    *(float *)(iVar5 + 0xd4) = *(float *)(iVar5 + 0xd4) - fVar12 * 3.1415927;
    if (*(float *)(param_1 + uVar8 * 4 + 0xd4) < -3.1415927) {
      iVar5 = param_1 + uVar8 * 4;
      *(float *)(iVar5 + 0xd4) = *(float *)(iVar5 + 0xd4) + 6.2831855;
    }
    if ((((*(byte *)(iGpffff86b4 + uVar8 * 0x4f0 + 0xb0) & 1) == 0) ||
        (-1 < (long)((ulong)*(byte *)(iGpffff86b4 + uVar8 * 0x4f0 + 0xb0) << 0x3e))) ||
       ((long)((ulong)*(byte *)(iGpffff86b4 + uVar8 * 0x4f0 + 0xb2) << 0x3d) < 0)) {
      *(undefined1 *)(param_1 + uVar8 + 0x50) = 0;
      *(undefined4 *)(param_1 + uVar8 * 8 + 0x74) = 0;
      for (iVar5 = 0; iVar5 < 0xc; iVar5 = iVar5 + 1) {
        if (((uint)*(ushort *)(param_1 + iVar5 * 2 + 0x5c) & 1 << (uVar8 & 0x1f)) != 0) {
          iVar6 = param_1 + iVar5 * 2;
          *(short *)(iVar6 + 0x5c) = *(short *)(iVar6 + 0x5c) - (short)(1 << (uVar8 & 0x1f));
        }
      }
    }
    else {
      if (((*(short *)(iGpffff86b4 + uVar8 * 0x4f0 + 0x124) < 1) ||
          (*(char *)(iGpffff86b4 + uVar8 * 0x4f0 + 0xb8) == '\b')) ||
         ((*(char *)(iGpffff86b4 + uVar8 * 0x4f0 + 0xb8) == '\t' ||
          ((((*(char *)(iGpffff86b4 + uVar8 * 0x4f0 + 0xb8) == '\n' ||
             (*(char *)(iGpffff86b4 + uVar8 * 0x4f0 + 0xb8) == '\v')) ||
            (*(char *)(iGpffff86b4 + uVar8 * 0x4f0 + 0xb8) == '\f')) ||
           (*(char *)(iGpffff86b4 + uVar8 * 0x4f0 + 0xb8) == '(')))))) {
        if (*(char *)(param_1 + uVar8 + 0x50) == '\x01') {
          *(undefined1 *)(param_1 + uVar8 + 0x50) = 3;
        }
        else if (*(char *)(param_1 + uVar8 + 0x50) == '\x02') {
          *(undefined1 *)(param_1 + uVar8 + 0x50) = 3;
          *(undefined4 *)(param_1 + uVar8 * 8 + 0x74) = 0x43000000;
        }
        for (iVar5 = 0; iVar5 < 0xc; iVar5 = iVar5 + 1) {
          if (((uint)*(ushort *)(param_1 + iVar5 * 2 + 0x5c) & 1 << (uVar8 & 0x1f)) != 0) {
            iVar6 = param_1 + iVar5 * 2;
            *(short *)(iVar6 + 0x5c) = *(short *)(iVar6 + 0x5c) - (short)(1 << (uVar8 & 0x1f));
          }
        }
      }
      if ((((*(byte *)(iGpffff86b4 + uVar8 * 0x4f0 + 0xb4) & 1) == 0) &&
          (*(short *)(iGpffff86b4 + uVar8 * 0x4f0 + 300) < 1)) &&
         ((*(short *)(iGpffff86b4 + uVar8 * 0x4f0 + 0x120) != 8 &&
          ((*(short *)(iGpffff86b4 + uVar8 * 0x4f0 + 0x120) != 9 &&
           (*(short *)(iGpffff86b4 + uVar8 * 0x4f0 + 0x120) != 10)))))) {
        if (*(char *)(param_1 + uVar8 + 0x50) == '\x01') {
          *(undefined1 *)(param_1 + uVar8 + 0x50) = 3;
        }
        else if (*(char *)(param_1 + uVar8 + 0x50) == '\x02') {
          *(undefined1 *)(param_1 + uVar8 + 0x50) = 3;
          *(undefined4 *)(param_1 + uVar8 * 8 + 0x74) = 0x43000000;
        }
        for (iVar5 = 0; iVar5 < 0xc; iVar5 = iVar5 + 1) {
          if (((uint)*(ushort *)(param_1 + iVar5 * 2 + 0x5c) & 1 << (uVar8 & 0x1f)) != 0) {
            iVar6 = param_1 + iVar5 * 2;
            *(short *)(iVar6 + 0x5c) = *(short *)(iVar6 + 0x5c) - (short)(1 << (uVar8 & 0x1f));
          }
        }
      }
      iVar5 = 0;
      for (iVar6 = 0; iVar6 < 0x20; iVar6 = iVar6 + 1) {
        if (((*(char *)(iGpffff86b4 + uVar8 * 0x4f0 + iVar6 * 0xc + 0x1bc) == 'G') &&
            (((ulong)*(byte *)(iGpffff86b4 + uVar8 * 0x4f0 + iVar6 * 0xc + 0x1b9) & 0x1f) >> 2 == 0)
            ) && ((*(uint *)(iGpffff86b4 + uVar8 * 0x4f0 + iVar6 * 0xc + 0x1c0) & 0x24) != 0)) {
          iVar5 = iVar5 + 1;
        }
      }
      if (iVar5 != 0) {
        if (*(char *)(param_1 + uVar8 + 0x50) == '\x01') {
          *(undefined1 *)(param_1 + uVar8 + 0x50) = 3;
        }
        else if (*(char *)(param_1 + uVar8 + 0x50) == '\x02') {
          *(undefined1 *)(param_1 + uVar8 + 0x50) = 3;
          *(undefined4 *)(param_1 + uVar8 * 8 + 0x74) = 0x43000000;
        }
        for (iVar5 = 0; iVar5 < 0xc; iVar5 = iVar5 + 1) {
          if (((uint)*(ushort *)(param_1 + iVar5 * 2 + 0x5c) & 1 << (uVar8 & 0x1f)) != 0) {
            iVar6 = param_1 + iVar5 * 2;
            *(short *)(iVar6 + 0x5c) = *(short *)(iVar6 + 0x5c) - (short)(1 << (uVar8 & 0x1f));
          }
        }
      }
      if ((*(char *)(iGpffff86b4 + uVar8 * 0x4f0 + 0xb8) == '\x0f') ||
         (('\x15' < *(char *)(iGpffff86b4 + uVar8 * 0x4f0 + 0xb8) &&
          (*(char *)(iGpffff86b4 + uVar8 * 0x4f0 + 0xb8) < '\'')))) {
        if (((long)((ulong)*(byte *)(iGpffff86b4 + uVar8 * 0x4f0 + 0xb4) << 0x39) < 0) ||
           (((long)((ulong)*(byte *)(iGpffff86b4 + uVar8 * 0x4f0 + 0xb5) << 0x3c) < 0 ||
            ((long)((ulong)*(byte *)(iGpffff86b4 + uVar8 * 0x4f0 + 0xb1) << 0x3b) < 0)))) {
          iVar5 = iGpffff86b4 + uVar8 * 0x4f0;
          uStack_8 = *(undefined4 *)(iVar5 + 0x168);
          uStack_4 = *(undefined4 *)(iVar5 + 0x16c);
          uStack_10 = (undefined4)*(undefined8 *)(iVar5 + 0x160);
          uStack_c = (undefined4)((ulong)*(undefined8 *)(iVar5 + 0x160) >> 0x20);
        }
        else {
          auVar13 = _lqc2(*(undefined1 (*) [16])(iGpffff86b4 + uVar8 * 0x4f0 + 0x150));
          auVar14 = _lqc2(*(undefined1 (*) [16])(auStack_1f0 + uVar8 * 4));
          auVar13 = _vadd(auVar13,auVar14);
          auStack_280 = _sqc2(auVar13);
          __ct__7FVectorFRC7FVector(auStack_250,auStack_280);
          uStack_10 = auStack_250._0_4_;
          uStack_c = auStack_250._4_4_;
          uStack_8 = uStack_248;
          uStack_4 = uStack_244;
        }
        iVar5 = 0;
        for (iVar6 = 0; iVar6 < 0xc; iVar6 = iVar6 + 1) {
          if (((uint)*(ushort *)(param_1 + iVar6 * 2 + 0x5c) & 1 << (uVar8 & 0x1f)) != 0) {
            if ((((long)((ulong)*(byte *)(iGpffff86b4 + iVar6 * 0x4f0 + 0xb4) << 0x39) < 0) ||
                ((long)((ulong)*(byte *)(iGpffff86b4 + iVar6 * 0x4f0 + 0xb5) << 0x3c) < 0)) ||
               ((long)((ulong)*(byte *)(iGpffff86b4 + iVar6 * 0x4f0 + 0xb1) << 0x3b) < 0)) {
              iVar2 = iGpffff86b4 + iVar6 * 0x4f0;
              uStack_18 = *(undefined4 *)(iVar2 + 0x168);
              uStack_14 = *(undefined4 *)(iVar2 + 0x16c);
              uStack_20 = (undefined4)*(undefined8 *)(iVar2 + 0x160);
              uStack_1c = (undefined4)((ulong)*(undefined8 *)(iVar2 + 0x160) >> 0x20);
            }
            else {
              auVar13 = _lqc2(*(undefined1 (*) [16])(iGpffff86b4 + iVar6 * 0x4f0 + 0x150));
              auVar14 = _lqc2(*(undefined1 (*) [16])(auStack_1f0 + iVar6 * 4));
              auVar13 = _vadd(auVar13,auVar14);
              auStack_290 = _sqc2(auVar13);
              __ct__7FVectorFRC7FVector(auStack_260,auStack_290);
              uStack_20 = auStack_260._0_4_;
              uStack_1c = auStack_260._4_4_;
              uStack_18 = uStack_258;
              uStack_14 = uStack_254;
            }
            auVar14._4_4_ = uStack_c;
            auVar14._0_4_ = uStack_10;
            auVar14._8_4_ = uStack_8;
            auVar14._12_4_ = uStack_4;
            auVar14 = _lqc2(auVar14);
            auVar13._4_4_ = uStack_1c;
            auVar13._0_4_ = uStack_20;
            auVar13._8_4_ = uStack_18;
            auVar13._12_4_ = uStack_14;
            auVar13 = _lqc2(auVar13);
            auVar13 = _vsub(auVar14,auVar13);
            auStack_2a0 = _sqc2(auVar13);
            __ct__7FVectorFRC7FVector(auStack_270,auStack_2a0);
            auStack_f0[0x30] = auStack_270._0_4_;
            auStack_f0[0x32] = uStack_268;
            uStack_24 = uStack_264;
            auStack_f0[0x31] = 0;
            fVar11 = (float)Length__7FVectorCFv(auStack_f0 + 0x30);
            if (fVar11 < afStack_220[uVar8] + afStack_220[iVar6] + 10.0) {
              iVar5 = iVar5 + 1;
            }
          }
        }
        if (iVar5 == 0) {
          if (*(char *)(param_1 + uVar8 + 0x50) == '\x01') {
            *(undefined1 *)(param_1 + uVar8 + 0x50) = 3;
          }
          else if (*(char *)(param_1 + uVar8 + 0x50) == '\x02') {
            *(undefined1 *)(param_1 + uVar8 + 0x50) = 3;
            *(undefined4 *)(param_1 + uVar8 * 8 + 0x74) = 0x43000000;
          }
          for (iVar5 = 0; iVar5 < 0xc; iVar5 = iVar5 + 1) {
            if (((uint)*(ushort *)(param_1 + iVar5 * 2 + 0x5c) & 1 << (uVar8 & 0x1f)) != 0) {
              iVar6 = param_1 + iVar5 * 2;
              *(short *)(iVar6 + 0x5c) = *(short *)(iVar6 + 0x5c) - (short)(1 << (uVar8 & 0x1f));
            }
          }
        }
      }
      iVar5 = 0;
      for (uVar7 = 0; (int)uVar7 < 0xc; uVar7 = uVar7 + 1) {
        if (((uint)*(ushort *)(param_1 + uVar8 * 2 + 0x5c) & 1 << (uVar7 & 0x1f)) != 0) {
          iVar5 = iVar5 + 1;
        }
      }
      fVar11 = 0.0;
      if ((iVar5 != 0) && (fVar11 = (float)(iVar5 + -1) * 0.25, 1 < iVar5)) {
        uVar3 = fptodp(*(undefined4 *)(param_1 + 0x3c));
        uVar3 = sin(uVar3);
        uVar3 = dpdiv(uVar3,0x4000000000000000);
        uVar3 = dpadd(0x3fe0000000000000,uVar3);
        uVar3 = dpmul(0x3fd0000000000000,uVar3);
        fVar10 = (float)dptofp(uVar3);
        fVar11 = fVar11 - fVar10;
      }
      *(float *)(param_1 + uVar8 * 8 + 0x78) = fVar11;
      cVar1 = *(char *)(param_1 + uVar8 + 0x50);
      if (cVar1 == '\x03') {
        iVar5 = param_1 + uVar8 * 8;
        *(float *)(iVar5 + 0x74) = *(float *)(iVar5 + 0x74) - fVar12 * 640.0;
        if (*(float *)(param_1 + uVar8 * 8 + 0x74) <= 0.0) {
          *(undefined1 *)(param_1 + uVar8 + 0x50) = 0;
          *(undefined4 *)(param_1 + uVar8 * 8 + 0x74) = 0;
        }
      }
      else if (cVar1 == '\x02') {
        *(undefined4 *)(param_1 + uVar8 * 8 + 0x74) = 0x43000000;
      }
      else if ((cVar1 == '\x01') &&
              (iVar5 = param_1 + uVar8 * 8,
              *(float *)(iVar5 + 0x74) = *(float *)(iVar5 + 0x74) + fVar12 * 640.0,
              128.0 <= *(float *)(param_1 + uVar8 * 8 + 0x74))) {
        *(undefined1 *)(param_1 + uVar8 + 0x50) = 2;
        *(undefined4 *)(param_1 + uVar8 * 8 + 0x74) = 0x43000000;
      }
    }
  }
  return 0;
}

/* ---------------------------------------------------------------------------
 * JP: 0x004f2140  MakePacket__9ComboFormFv
 * C++: ComboForm::MakePacket()
 * size: 0x34f8 bytes
 * --------------------------------------------------------------------------- */
/* WARNING: Removing unreachable block (ram,0x004f3f58) */
/* WARNING: Removing unreachable block (ram,0x004f3f00) */
/* WARNING: Removing unreachable block (ram,0x004f3ce8) */
/* WARNING: Removing unreachable block (ram,0x004f36f8) */
/* WARNING: Removing unreachable block (ram,0x004f3634) */
/* WARNING: Removing unreachable block (ram,0x004f3764) */
/* WARNING: Removing unreachable block (ram,0x004f35dc) */
/* WARNING: Removing unreachable block (ram,0x004f32c8) */
/* WARNING: Removing unreachable block (ram,0x004f3270) */
/* WARNING: Removing unreachable block (ram,0x004f3058) */
/* WARNING: Removing unreachable block (ram,0x004f2f94) */
/* WARNING: Removing unreachable block (ram,0x004f311c) */
/* WARNING: Removing unreachable block (ram,0x004f2fec) */
/* WARNING: Removing unreachable block (ram,0x004f30b0) */
/* WARNING: Removing unreachable block (ram,0x004f36a0) */
/* WARNING: Removing unreachable block (ram,0x004f38b8) */
/* WARNING: Removing unreachable block (ram,0x004f3910) */
/* WARNING: Removing unreachable block (ram,0x004f3c24) */
/* WARNING: Removing unreachable block (ram,0x004f3dac) */
/* WARNING: Removing unreachable block (ram,0x004f3c7c) */
/* WARNING: Removing unreachable block (ram,0x004f3d40) */
/* WARNING: Removing unreachable block (ram,0x004f3e04) */
/* WARNING: Removing unreachable block (ram,0x004f37bc) */
/* WARNING: Removing unreachable block (ram,0x004f3174) */
/* WARNING: Removing unreachable block (ram,0x004f334c) */
/* WARNING: Removing unreachable block (ram,0x004f3994) */
/* WARNING: Removing unreachable block (ram,0x004f3fdc) */
/* WARNING: Removing unreachable block (ram,0x004f39ec) */
/* WARNING: Removing unreachable block (ram,0x004f33a4) */
/* WARNING: Removing unreachable block (ram,0x004f4034) */

void MakePacket__9ComboFormFv(int param_1)

{
  undefined4 *puVar1;
  undefined1 auVar2 [16];
  long lVar3;
  ulong uVar4;
  undefined1 auVar5 [16];
  undefined1 auVar6 [16];
  float in_zero_lo;
  float in_zero_hi;
  float in_zero_udw;
  float in_register_0000000c;
  int iVar7;
  undefined4 uVar8;
  uint uVar9;
  undefined8 uVar10;
  undefined4 uVar11;
  float *pfVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  uint uVar17;
  byte bVar18;
  undefined4 uVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  undefined1 in_vf0 [16];
  undefined1 auVar23 [16];
  undefined1 auVar24 [16];
  undefined1 auVar25 [16];
  undefined1 auStack_3e50 [16];
  undefined1 auStack_3e40 [56];
  undefined4 uStack_3e08;
  undefined4 uStack_3e04;
  float fStack_3e00;
  undefined4 uStack_3dfc;
  float fStack_3df8;
  undefined4 uStack_3df4;
  float fStack_3df0;
  undefined4 uStack_3dec;
  float fStack_3de8;
  undefined4 uStack_3de4;
  undefined4 uStack_3de0;
  undefined4 uStack_3ddc;
  undefined4 uStack_3dd8;
  undefined4 uStack_3dd4;
  undefined1 auStack_3dd0 [16];
  float fStack_3dc0;
  float fStack_3dbc;
  float fStack_3db8;
  float fStack_3db4;
  float fStack_3db0;
  undefined4 uStack_3dac;
  float fStack_3da8;
  undefined4 uStack_3da4;
  float afStack_3da0 [396];
  byte abStack_3770 [32];
  float afStack_3750 [140];
  int aiStack_3520 [1584];
  float afStack_1c60 [1600];
  float afStack_360 [132];
  undefined1 auStack_150 [256];
  undefined1 auStack_50 [8];
  float afStack_48 [2];
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [16];
  undefined1 auStack_20 [16];
  char acStack_10 [16];
  
  auVar23 = _vmr32(in_vf0);
  auVar24 = _vmr32(auVar23);
  auVar25 = _vmr32(auVar24);
  auStack_20 = _sqc2(in_vf0);
  auStack_30 = _sqc2(auVar23);
  auStack_40 = _sqc2(auVar24);
  _auStack_50 = _sqc2(auVar25);
  pfVar12 = afStack_360 + 0x40;
  do {
    *pfVar12 = in_zero_lo;
    pfVar12[1] = in_zero_hi;
    pfVar12[2] = in_zero_udw;
    pfVar12[3] = in_register_0000000c;
    pfVar12 = pfVar12 + 4;
  } while (pfVar12 != (float *)auStack_50);
  pfVar12 = afStack_360;
  do {
    *pfVar12 = in_zero_lo;
    pfVar12[1] = in_zero_hi;
    pfVar12[2] = in_zero_udw;
    pfVar12[3] = in_register_0000000c;
    pfVar12 = pfVar12 + 4;
  } while (pfVar12 != afStack_360 + 0x40);
  afStack_3750[0x48] = 8.0;
  afStack_3750[0x49] = 8.0;
  fVar22 = 0.0;
  for (iVar13 = 0; iVar13 < 0x10; iVar13 = iVar13 + 1) {
    fVar20 = (float)cosf(fVar22);
    fVar20 = (fVar20 / 2.0 + 0.5) * 16.0;
    afStack_3750[(iVar13 + 0x11) * 2 + 0x48] = fVar20;
    afStack_3750[(iVar13 + 1) * 2 + 0x48] = fVar20;
    fVar20 = (float)sinf(fVar22);
    fVar20 = (-fVar20 / 2.0 + 0.5) * 16.0;
    afStack_3750[(iVar13 + 0x11) * 2 + 0x49] = fVar20;
    afStack_3750[(iVar13 + 1) * 2 + 0x49] = fVar20;
    fVar22 = fVar22 + 0.41887903;
  }
  pfVar12 = afStack_3750 + 0x18;
  do {
    *pfVar12 = in_zero_lo;
    pfVar12[1] = in_zero_hi;
    pfVar12[2] = in_zero_udw;
    pfVar12[3] = in_register_0000000c;
    pfVar12 = pfVar12 + 4;
  } while (pfVar12 != afStack_3750 + 0x48);
  for (iVar13 = 0; iVar13 < 0xc; iVar13 = iVar13 + 1) {
    if ((((*(byte *)(iGpffff86b4 + iVar13 * 0x4f0 + 0xb0) & 1) != 0) &&
        (((ulong)*(byte *)(iGpffff86b4 + iVar13 * 0x4f0 + 0xb0) & 3) >> 1 != 0)) &&
       (((ulong)*(byte *)(iGpffff86b4 + iVar13 * 0x4f0 + 0xb2) & 7) >> 2 == 0)) {
      fStack_3da8 = *(float *)(iGpffff86b4 + iVar13 * 0x4f0 + 0x3b8);
      fStack_3db0 = *(float *)(iGpffff86b4 + iVar13 * 0x4f0 + 0x3b4);
      uStack_3dac = 0;
      uStack_3da4 = 0x3f800000;
      afStack_3750[iVar13 * 4 + 0x18] = fStack_3db0;
      afStack_3750[iVar13 * 4 + 0x19] = 0.0;
      afStack_3750[iVar13 * 4 + 0x1a] = fStack_3da8;
      afStack_3750[iVar13 * 4 + 0x1b] = 1.0;
      auVar23 = _vmr32(in_vf0);
      auVar24 = _vmr32(auVar23);
      auVar25 = _vmr32(auVar24);
      auStack_20 = _sqc2(in_vf0);
      auStack_30 = _sqc2(auVar23);
      auStack_40 = _sqc2(auVar24);
      _auStack_50 = _sqc2(auVar25);
      uVar19 = GetRad(*(undefined4 *)(iGpffff86b4 + iVar13 * 0x4f0 + 0x174));
      sceVu0RotMatrixY(uVar19,auStack_50,auStack_50);
      iVar14 = iGpffff86b4 + iVar13 * 0x4f0;
      ApplyMatrix__6MatrixCFRC7FVector(auStack_3dd0,auStack_50,afStack_3750 + iVar13 * 4 + 0x18);
      auVar23 = _lqc2(auStack_3dd0);
      auVar24 = _lqc2(*(undefined1 (*) [16])(iVar14 + 0x150));
      auVar23 = _vadd(auVar23,auVar24);
      auStack_3e50 = _sqc2(auVar23);
      __ct__7FVectorFRC7FVector(&fStack_3dc0,auStack_3e50);
      afStack_3750[iVar13 * 4 + 0x18] = fStack_3dc0;
      afStack_3750[iVar13 * 4 + 0x19] = fStack_3dbc;
      afStack_3750[iVar13 * 4 + 0x1a] = fStack_3db8;
      afStack_3750[iVar13 * 4 + 0x1b] = fStack_3db4;
      afStack_3750[iVar13 * 2] = *(float *)(iGpffff86b4 + iVar13 * 0x4f0 + 0x3b0) + 7.5;
      afStack_3750[iVar13 * 2 + 1] = *(float *)(iGpffff86b4 + iVar13 * 0x4f0 + 0x3b0) + 5.0;
    }
  }
  for (iVar13 = 0; iVar13 < 0xc; iVar13 = iVar13 + 1) {
    acStack_10[iVar13] = '\0';
    if ((*(char *)(param_1 + iVar13 + 0x50) != '\0') && (param_1 + iVar13 * 8 != -0x74)) {
      fVar22 = 0.0;
      uStack_3de0 = 0;
      uStack_3ddc = 0;
      uStack_3dd8 = 0;
      uStack_3dd4 = 0;
      afStack_360[0x40] = 0.0;
      afStack_360[0x41] = 0.0;
      afStack_360[0x42] = 0.0;
      afStack_360[0x43] = 0.0;
      for (iVar14 = 0; iVar14 < 0x10; iVar14 = iVar14 + 1) {
        fVar20 = (float)sinf(fVar22);
        fVar20 = afStack_3750[iVar13 * 2] * fVar20;
        fVar21 = (float)cosf(fVar22);
        fStack_3df0 = afStack_3750[iVar13 * 2] * -fVar21;
        uStack_3dec = 0;
        uStack_3de4 = 0x3f800000;
        iVar16 = iVar14 + 1;
        afStack_360[iVar16 * 4 + 0x40] = fStack_3df0;
        afStack_360[iVar16 * 4 + 0x41] = 0.0;
        afStack_360[iVar16 * 4 + 0x42] = fVar20;
        afStack_360[iVar16 * 4 + 0x43] = 1.0;
        fStack_3de8 = fVar20;
        fVar20 = (float)sinf(fVar22);
        fVar20 = afStack_3750[iVar13 * 2 + 1] * fVar20;
        fVar21 = (float)cosf(fVar22);
        fStack_3e00 = afStack_3750[iVar13 * 2 + 1] * -fVar21;
        uStack_3dfc = 0;
        uStack_3df4 = 0x3f800000;
        afStack_360[iVar14 * 4] = fStack_3e00;
        afStack_360[iVar14 * 4 + 1] = 0.0;
        afStack_360[iVar14 * 4 + 2] = fVar20;
        afStack_360[iVar14 * 4 + 3] = 1.0;
        fVar22 = fVar22 + 0.41887903;
        fStack_3df8 = fVar20;
      }
      auVar23 = _vmr32(in_vf0);
      auVar24 = _vmr32(auVar23);
      auVar25 = _vmr32(auVar24);
      auStack_20 = _sqc2(in_vf0);
      auStack_30 = _sqc2(auVar23);
      auStack_40 = _sqc2(auVar24);
      _auStack_50 = _sqc2(auVar25);
      sceVu0RotMatrixY(*(undefined4 *)(param_1 + iVar13 * 4 + 0xd4),auStack_50,auStack_50);
      RotTransVector(auStack_150,afStack_360,auStack_50,0x10);
      for (iVar14 = 0; iVar14 < 0x21; iVar14 = iVar14 + 1) {
        afStack_1c60[(iVar14 + iVar13 * 0x21) * 4] =
             afStack_3750[iVar13 * 4 + 0x18] + afStack_360[iVar14 * 4 + 0x40];
        afStack_1c60[(iVar14 + iVar13 * 0x21) * 4 + 1] = -0.2;
        afStack_1c60[(iVar14 + iVar13 * 0x21) * 4 + 2] =
             afStack_3750[iVar13 * 4 + 0x1a] + afStack_360[iVar14 * 4 + 0x42];
        afStack_1c60[(iVar14 + iVar13 * 0x21) * 4 + 3] = 1.0;
      }
      acStack_10[iVar13] = '\x01';
      if ((*(byte *)(iGpffff86b4 + iVar13 * 0x4f0 + 0xb4) & 1) != 0) {
        acStack_10[iVar13] = '\x02';
      }
      fVar22 = *(float *)(param_1 + iVar13 * 8 + 0x74);
      if (fVar22 < 2.1474836e+09) {
        bVar18 = (byte)(int)fVar22;
      }
      else {
        bVar18 = (byte)(int)(fVar22 - 2.1474836e+09);
      }
      abStack_3770[iVar13 * 2] = bVar18;
      fVar22 = *(float *)(param_1 + iVar13 * 8 + 0x74) * *(float *)(param_1 + iVar13 * 8 + 0x78);
      if (fVar22 < 2.1474836e+09) {
        bVar18 = (byte)(int)fVar22;
      }
      else {
        bVar18 = (byte)(int)(fVar22 - 2.1474836e+09);
      }
      abStack_3770[iVar13 * 2 + 1] = bVar18;
    }
  }
  GetViewScreenMatrix__9GsxCameraFv(auStack_3e40,uGpffff8598);
  for (iVar13 = 0; iVar13 < 4; iVar13 = iVar13 + 1) {
    afStack_1c60[iVar13 * 4 + 0x630] = *(float *)(auStack_50 + iVar13 * 0x10);
    afStack_1c60[iVar13 * 4 + 0x631] = *(float *)(auStack_50 + iVar13 * 0x10 + 4);
    afStack_1c60[iVar13 * 4 + 0x632] = *(float *)(auStack_50 + iVar13 * 0x10 + 8);
    afStack_1c60[iVar13 * 4 + 0x633] = *(float *)(auStack_50 + iVar13 * 0x10 + 0xc);
  }
  sceVu0RotTransPersN(aiStack_3520,afStack_1c60 + 0x630,afStack_1c60,0x18c,0);
  iVar14 = 0;
  for (iVar13 = 0; iVar13 < 0xc; iVar13 = iVar13 + 1) {
    iVar16 = 0;
    while (((iVar16 < 0x21 && (-1 < aiStack_3520[(iVar16 + iVar13 * 0x21) * 4] >> 0x1f)) &&
           ((aiStack_3520[(iVar16 + iVar13 * 0x21) * 4] < 0x10001 &&
            (((-1 < aiStack_3520[(iVar16 + iVar13 * 0x21) * 4 + 1] >> 0x1f &&
              (aiStack_3520[(iVar16 + iVar13 * 0x21) * 4 + 1] < 0x10001)) &&
             (-1 < aiStack_3520[(iVar16 + iVar13 * 0x21) * 4 + 2] >> 0x1f))))))) {
      iVar16 = iVar16 + 1;
    }
    if (iVar16 < 0x21) {
      acStack_10[iVar13] = '\0';
    }
    else {
      for (iVar16 = 0; iVar16 < 0x21; iVar16 = iVar16 + 1) {
        iVar7 = iVar16 + iVar13 * 0x21;
        iVar15 = aiStack_3520[iVar7 * 4 + 2];
        if (iVar15 < 0) {
          iVar15 = iVar15 + 0xf;
        }
        aiStack_3520[iVar7 * 4 + 2] = iVar15 >> 4;
        afStack_3da0[iVar16 + iVar13 * 0x21] =
             1.0 / ((float)aiStack_3520[(iVar16 + iVar13 * 0x21) * 4 + 3] / 16.0);
      }
      iVar14 = iVar14 + 1;
    }
  }
  uVar17 = (uint)(*(int *)(param_1 + 0x4c) == 0);
  uVar19 = uStack_3e08;
  uVar11 = uStack_3e04;
  if ((*(int *)(param_1 + uVar17 * 4 + 0x18) != 0) &&
     (*(int *)(param_1 + uVar17 * 4 + 0x44) != 0x40e)) {
    __dla__FPv(*(undefined4 *)(param_1 + uVar17 * 4 + 0x18));
    *(undefined4 *)(param_1 + uVar17 * 4 + 0x18) = 0;
    *(undefined4 *)(param_1 + uVar17 * 4 + 0x44) = 0;
    uVar19 = uStack_3e08;
    uVar11 = uStack_3e04;
  }
  if (*(int *)(param_1 + uVar17 * 4 + 0x18) == 0) {
    uVar8 = __nwa__FUi(0x40e0);
    *(undefined4 *)(param_1 + uVar17 * 4 + 0x18) = uVar8;
    *(undefined4 *)(param_1 + uVar17 * 4 + 0x44) = 0x40e;
    puVar1 = *(undefined4 **)(param_1 + uVar17 * 4 + 0x18);
    *puVar1 = 0x10000007;
    puVar1[1] = 0;
    puVar1[2] = 0x10000000;
    puVar1[3] = 0x50000007;
    *(undefined8 *)(puVar1 + 4) = 0x2000000000000001;
    *(undefined8 *)(puVar1 + 6) = 0xee;
    *(undefined8 *)(puVar1 + 8) = 0x23001;
    *(undefined8 *)(puVar1 + 10) = 0x47;
    *(undefined8 *)(puVar1 + 0xc) = 0x44;
    *(undefined8 *)(puVar1 + 0xe) = 0x42;
    *(undefined8 *)(puVar1 + 0x10) = 0x6400000000008001;
    *(undefined8 *)(puVar1 + 0x12) = 0x44cc10;
    *(undefined8 *)(puVar1 + 0x14) = 0x44;
    *(undefined8 *)(puVar1 + 0x18) = 0x71006f00;
    *(undefined8 *)(puVar1 + 0x1a) = 0x8f006f00;
    *(undefined8 *)(puVar1 + 0x1c) = 0x71009100;
    *(undefined8 *)(puVar1 + 0x1e) = 0x8f009100;
    puVar1[0x24] = 0x10000157;
    puVar1[0x25] = 0;
    puVar1[0x26] = 0;
    puVar1[0x27] = 0x50000157;
    *(undefined8 *)(puVar1 + 0x28) = 0x6000000000000001;
    *(undefined8 *)(puVar1 + 0x2a) = 0xe6e8ee;
    *(undefined8 *)(puVar1 + 0x2c) = 1;
    *(undefined8 *)(puVar1 + 0x2e) = 0x3f;
    *(undefined8 *)(puVar1 + 0x30) = 0x60;
    *(undefined8 *)(puVar1 + 0x32) = 0x14;
    *(undefined8 *)(puVar1 + 0x34) = 5;
    *(undefined8 *)(puVar1 + 0x36) = 0;
    *(undefined8 *)(puVar1 + 0x38) = 0x53001;
    *(undefined8 *)(puVar1 + 0x3a) = 0x47;
    uVar10 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x42d4),1);
    *(undefined8 *)(puVar1 + 0x3c) = uVar10;
    *(undefined8 *)(puVar1 + 0x3e) = 0;
    *(undefined8 *)(puVar1 + 0x40) = 0x48;
    *(undefined8 *)(puVar1 + 0x42) = 0x42;
    iVar13 = 0x11;
    for (iVar16 = 0; iVar16 < 0xc; iVar16 = iVar16 + 1) {
      auVar23._4_4_ = in_zero_hi;
      auVar23._0_4_ = in_zero_lo;
      auVar23._8_4_ = in_zero_udw;
      auVar23._12_4_ = in_register_0000000c;
      auVar24._8_4_ = uVar19;
      auVar24._0_8_ = 0xa400000000000001;
      auVar24._12_4_ = uVar11;
      auVar23 = _pcpyld(auVar23,auVar24);
      *(long *)(puVar1 + iVar13 * 4) = auVar23._0_8_;
      *(undefined8 *)(puVar1 + iVar13 * 4 + 2) = 0x431c31c310;
      *(undefined8 *)(puVar1 + (iVar13 + 1) * 4) = 0x15d;
      uVar4 = __fixunssfdi((float)*(ushort *)(*(int *)(iGpffff86b4 + 0x42d4) + 2) *
                              afStack_3750[0x48]);
      uVar10 = __fixunssfdi((float)*(ushort *)(*(int *)(iGpffff86b4 + 0x42d4) + 4) *
                               afStack_3750[0x49]);
      *(ulong *)(puVar1 + (iVar13 + 2) * 4) =
           uVar4 | CONCAT44((int)((ulong)uVar10 >> 0x10),(int)uVar10 << 0x10);
      uVar4 = __fixunssfdi((float)*(ushort *)(*(int *)(iGpffff86b4 + 0x42d4) + 2) *
                              afStack_3750[0x4a]);
      uVar10 = __fixunssfdi((float)*(ushort *)(*(int *)(iGpffff86b4 + 0x42d4) + 4) *
                               afStack_3750[0x4b]);
      *(ulong *)(puVar1 + (iVar13 + 3) * 4 + 2) =
           uVar4 | CONCAT44((int)((ulong)uVar10 >> 0x10),(int)uVar10 << 0x10);
      uVar4 = __fixunssfdi((float)*(ushort *)(*(int *)(iGpffff86b4 + 0x42d4) + 2) *
                              afStack_3750[0x4c]);
      uVar10 = __fixunssfdi((float)*(ushort *)(*(int *)(iGpffff86b4 + 0x42d4) + 4) *
                               afStack_3750[0x4d]);
      *(ulong *)(puVar1 + (iVar13 + 5) * 4) =
           uVar4 | CONCAT44((int)((ulong)uVar10 >> 0x10),(int)uVar10 << 0x10);
      if (iVar16 == 0xb) {
        *(undefined8 *)(puVar1 + (iVar13 + 6) * 4) = 0x6400000000008007;
      }
      else {
        *(undefined8 *)(puVar1 + (iVar13 + 6) * 4) = 0x6400000000000007;
      }
      *(undefined8 *)(puVar1 + (iVar13 + 6) * 4 + 2) = 0x431431;
      iVar13 = iVar13 + 7;
      for (iVar15 = 0; iVar15 < 7; iVar15 = iVar15 + 1) {
        lVar3 = __fixunssfdi((float)*(ushort *)(*(int *)(iGpffff86b4 + 0x42d4) + 4) *
                                afStack_3750[(iVar15 * 2 + 3) * 2 + 0x49]);
        uVar4 = __fixunssfdi((float)*(ushort *)(*(int *)(iGpffff86b4 + 0x42d4) + 2) *
                                afStack_3750[(iVar15 * 2 + 3) * 2 + 0x48]);
        *(ulong *)(puVar1 + iVar13 * 4 + 2) = uVar4 | lVar3 << 0x10;
        lVar3 = __fixunssfdi((float)*(ushort *)(*(int *)(iGpffff86b4 + 0x42d4) + 4) *
                                afStack_3750[(iVar15 * 2 + 4) * 2 + 0x49]);
        uVar4 = __fixunssfdi((float)*(ushort *)(*(int *)(iGpffff86b4 + 0x42d4) + 2) *
                                afStack_3750[(iVar15 * 2 + 4) * 2 + 0x48]);
        *(ulong *)(puVar1 + (iVar13 + 2) * 4) = uVar4 | lVar3 << 0x10;
        iVar13 = iVar13 + 3;
      }
    }
    puVar1[iVar13 * 4] = 0x50000000;
    puVar1[iVar13 * 4 + 1] =
         *(undefined4 *)
          (*(int *)(iGpffff86b4 + 0x42d8) +
           (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42d8) + 10) * 4 + 0xc);
    puVar1[iVar13 * 4 + 2] = 0;
    puVar1[iVar13 * 4 + 3] = 0;
    puVar1[(iVar13 + 1) * 4] = 0x10000153;
    puVar1[(iVar13 + 1) * 4 + 1] = 0;
    puVar1[(iVar13 + 1) * 4 + 2] = 0;
    puVar1[(iVar13 + 1) * 4 + 3] = 0x50000153;
    *(undefined8 *)(puVar1 + (iVar13 + 2) * 4) = 0x2000000000000001;
    *(undefined8 *)(puVar1 + (iVar13 + 2) * 4 + 2) = 0x6e;
    *(undefined8 *)(puVar1 + (iVar13 + 3) * 4) = 1;
    *(undefined8 *)(puVar1 + (iVar13 + 3) * 4 + 2) = 0x3f;
    uVar10 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x42d8),1);
    *(undefined8 *)(puVar1 + (iVar13 + 4) * 4) = uVar10;
    *(undefined8 *)(puVar1 + (iVar13 + 4) * 4 + 2) = 0;
    iVar13 = iVar13 + 5;
    for (iVar16 = 0; iVar16 < 0xc; iVar16 = iVar16 + 1) {
      auVar25._4_4_ = in_zero_hi;
      auVar25._0_4_ = in_zero_lo;
      auVar25._8_4_ = in_zero_udw;
      auVar25._12_4_ = in_register_0000000c;
      auVar6._8_4_ = uVar19;
      auVar6._0_8_ = 0xa400000000000001;
      auVar6._12_4_ = uVar11;
      auVar23 = _pcpyld(auVar25,auVar6);
      *(long *)(puVar1 + iVar13 * 4) = auVar23._0_8_;
      *(undefined8 *)(puVar1 + iVar13 * 4 + 2) = 0x431c31c310;
      *(undefined8 *)(puVar1 + (iVar13 + 1) * 4) = 0x15d;
      uVar4 = __fixunssfdi((float)*(ushort *)(*(int *)(iGpffff86b4 + 0x42d8) + 2) *
                              afStack_3750[0x48]);
      uVar10 = __fixunssfdi((float)*(ushort *)(*(int *)(iGpffff86b4 + 0x42d8) + 4) *
                               afStack_3750[0x49]);
      *(ulong *)(puVar1 + (iVar13 + 2) * 4) =
           uVar4 | CONCAT44((int)((ulong)uVar10 >> 0x10),(int)uVar10 << 0x10);
      uVar4 = __fixunssfdi((float)*(ushort *)(*(int *)(iGpffff86b4 + 0x42d8) + 2) *
                              afStack_3750[0x6a]);
      uVar10 = __fixunssfdi((float)*(ushort *)(*(int *)(iGpffff86b4 + 0x42d8) + 4) *
                               afStack_3750[0x6b]);
      *(ulong *)(puVar1 + (iVar13 + 3) * 4 + 2) =
           uVar4 | CONCAT44((int)((ulong)uVar10 >> 0x10),(int)uVar10 << 0x10);
      uVar4 = __fixunssfdi((float)*(ushort *)(*(int *)(iGpffff86b4 + 0x42d8) + 2) *
                              afStack_3750[0x6c]);
      uVar10 = __fixunssfdi((float)*(ushort *)(*(int *)(iGpffff86b4 + 0x42d8) + 4) *
                               afStack_3750[0x6d]);
      *(ulong *)(puVar1 + (iVar13 + 5) * 4) =
           uVar4 | CONCAT44((int)((ulong)uVar10 >> 0x10),(int)uVar10 << 0x10);
      if (iVar16 == 0xb) {
        *(undefined8 *)(puVar1 + (iVar13 + 6) * 4) = 0x6400000000008007;
      }
      else {
        *(undefined8 *)(puVar1 + (iVar13 + 6) * 4) = 0x6400000000000007;
      }
      *(undefined8 *)(puVar1 + (iVar13 + 6) * 4 + 2) = 0x431431;
      iVar13 = iVar13 + 7;
      for (iVar15 = 0; iVar15 < 7; iVar15 = iVar15 + 1) {
        lVar3 = __fixunssfdi((float)*(ushort *)(*(int *)(iGpffff86b4 + 0x42d8) + 4) *
                                afStack_3750[(iVar15 * 2 + 0x13) * 2 + 0x49]);
        uVar4 = __fixunssfdi((float)*(ushort *)(*(int *)(iGpffff86b4 + 0x42d8) + 2) *
                                afStack_3750[(iVar15 * 2 + 0x13) * 2 + 0x48]);
        *(ulong *)(puVar1 + iVar13 * 4 + 2) = uVar4 | lVar3 << 0x10;
        lVar3 = __fixunssfdi((float)*(ushort *)(*(int *)(iGpffff86b4 + 0x42d8) + 4) *
                                afStack_3750[(iVar15 * 2 + 0x14) * 2 + 0x49]);
        uVar4 = __fixunssfdi((float)*(ushort *)(*(int *)(iGpffff86b4 + 0x42d8) + 2) *
                                afStack_3750[(iVar15 * 2 + 0x14) * 2 + 0x48]);
        *(ulong *)(puVar1 + (iVar13 + 2) * 4) = uVar4 | lVar3 << 0x10;
        iVar13 = iVar13 + 3;
      }
    }
    puVar1[iVar13 * 4] = 0x50000000;
    puVar1[iVar13 * 4 + 1] =
         *(undefined4 *)
          (*(int *)(iGpffff86b4 + 0x42dc) +
           (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42dc) + 10) * 4 + 0xc);
    puVar1[iVar13 * 4 + 2] = 0;
    puVar1[iVar13 * 4 + 3] = 0;
    puVar1[(iVar13 + 1) * 4] = 0x10000153;
    puVar1[(iVar13 + 1) * 4 + 1] = 0;
    puVar1[(iVar13 + 1) * 4 + 2] = 0;
    puVar1[(iVar13 + 1) * 4 + 3] = 0x50000153;
    *(undefined8 *)(puVar1 + (iVar13 + 2) * 4) = 0x2000000000000001;
    *(undefined8 *)(puVar1 + (iVar13 + 2) * 4 + 2) = 0x6e;
    *(undefined8 *)(puVar1 + (iVar13 + 3) * 4) = 1;
    *(undefined8 *)(puVar1 + (iVar13 + 3) * 4 + 2) = 0x3f;
    uVar10 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x42dc),1);
    *(undefined8 *)(puVar1 + (iVar13 + 4) * 4) = uVar10;
    *(undefined8 *)(puVar1 + (iVar13 + 4) * 4 + 2) = 0;
    iVar13 = iVar13 + 5;
    for (iVar16 = 0; iVar16 < 0xc; iVar16 = iVar16 + 1) {
      auVar2._4_4_ = in_zero_hi;
      auVar2._0_4_ = in_zero_lo;
      auVar2._8_4_ = in_zero_udw;
      auVar2._12_4_ = in_register_0000000c;
      auVar5._8_4_ = uVar19;
      auVar5._0_8_ = 0xa400000000000001;
      auVar5._12_4_ = uVar11;
      auVar23 = _pcpyld(auVar2,auVar5);
      *(long *)(puVar1 + iVar13 * 4) = auVar23._0_8_;
      *(undefined8 *)(puVar1 + iVar13 * 4 + 2) = 0x431c31c310;
      *(undefined8 *)(puVar1 + (iVar13 + 1) * 4) = 0x15d;
      uVar4 = __fixunssfdi((float)*(ushort *)(*(int *)(iGpffff86b4 + 0x42dc) + 2) *
                              afStack_3750[0x48]);
      uVar10 = __fixunssfdi((float)*(ushort *)(*(int *)(iGpffff86b4 + 0x42dc) + 4) *
                               afStack_3750[0x49]);
      *(ulong *)(puVar1 + (iVar13 + 2) * 4) =
           uVar4 | CONCAT44((int)((ulong)uVar10 >> 0x10),(int)uVar10 << 0x10);
      uVar4 = __fixunssfdi((float)*(ushort *)(*(int *)(iGpffff86b4 + 0x42dc) + 2) *
                              afStack_3750[0x6a]);
      uVar10 = __fixunssfdi((float)*(ushort *)(*(int *)(iGpffff86b4 + 0x42dc) + 4) *
                               afStack_3750[0x6b]);
      *(ulong *)(puVar1 + (iVar13 + 3) * 4 + 2) =
           uVar4 | CONCAT44((int)((ulong)uVar10 >> 0x10),(int)uVar10 << 0x10);
      uVar4 = __fixunssfdi((float)*(ushort *)(*(int *)(iGpffff86b4 + 0x42dc) + 2) *
                              afStack_3750[0x6c]);
      uVar10 = __fixunssfdi((float)*(ushort *)(*(int *)(iGpffff86b4 + 0x42dc) + 4) *
                               afStack_3750[0x6d]);
      *(ulong *)(puVar1 + (iVar13 + 5) * 4) =
           uVar4 | CONCAT44((int)((ulong)uVar10 >> 0x10),(int)uVar10 << 0x10);
      if (iVar16 == 0xb) {
        *(undefined8 *)(puVar1 + (iVar13 + 6) * 4) = 0x6400000000008007;
      }
      else {
        *(undefined8 *)(puVar1 + (iVar13 + 6) * 4) = 0x6400000000000007;
      }
      *(undefined8 *)(puVar1 + (iVar13 + 6) * 4 + 2) = 0x431431;
      iVar13 = iVar13 + 7;
      for (iVar15 = 0; iVar15 < 7; iVar15 = iVar15 + 1) {
        lVar3 = __fixunssfdi((float)*(ushort *)(*(int *)(iGpffff86b4 + 0x42dc) + 4) *
                                afStack_3750[(iVar15 * 2 + 0x13) * 2 + 0x49]);
        uVar4 = __fixunssfdi((float)*(ushort *)(*(int *)(iGpffff86b4 + 0x42dc) + 2) *
                                afStack_3750[(iVar15 * 2 + 0x13) * 2 + 0x48]);
        *(ulong *)(puVar1 + iVar13 * 4 + 2) = uVar4 | lVar3 << 0x10;
        lVar3 = __fixunssfdi((float)*(ushort *)(*(int *)(iGpffff86b4 + 0x42dc) + 4) *
                                afStack_3750[(iVar15 * 2 + 0x14) * 2 + 0x49]);
        uVar4 = __fixunssfdi((float)*(ushort *)(*(int *)(iGpffff86b4 + 0x42dc) + 2) *
                                afStack_3750[(iVar15 * 2 + 0x14) * 2 + 0x48]);
        *(ulong *)(puVar1 + (iVar13 + 2) * 4) = uVar4 | lVar3 << 0x10;
        iVar13 = iVar13 + 3;
      }
    }
  }
  iVar13 = *(int *)(param_1 + uVar17 * 4 + 0x18);
  lVar3 = __fixunssfdi(*(undefined4 *)(param_1 + 0x108));
  *(long *)(iVar13 + 0x58) = lVar3 << 0x18;
  if ((iVar14 == 0) || (*(int *)(param_1 + 0x38) != 0)) {
    *(int *)(param_1 + 0x40) = iVar13 + 0x80;
    *(uint *)(param_1 + 0x4c) = uVar17;
  }
  else {
    *(undefined4 *)(iVar13 + 0x80) = 0x50000000;
    *(undefined4 *)(iVar13 + 0x84) =
         *(undefined4 *)
          (*(int *)(iGpffff86b4 + 0x42d4) +
           (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42d4) + 10) * 4 + 0xc);
    *(undefined4 *)(iVar13 + 0x88) = 0;
    *(undefined4 *)(iVar13 + 0x8c) = 0;
    iVar14 = 0x11;
    for (iVar16 = 0; iVar16 < 0xc; iVar16 = iVar16 + 1) {
      if (acStack_10[iVar16] == '\0') {
        *(undefined8 *)(iVar13 + (iVar14 + 2) * 0x10 + 8) = 0x71006f00;
        *(undefined8 *)(iVar13 + (iVar14 + 4) * 0x10) = 0x71006f00;
        *(undefined8 *)(iVar13 + (iVar14 + 5) * 0x10 + 8) = 0x71006f00;
        iVar14 = iVar14 + 7;
        for (iVar15 = 0; iVar15 < 7; iVar15 = iVar15 + 1) {
          *(undefined8 *)(iVar13 + (iVar14 + 1) * 0x10) = 0x71006f00;
          *(undefined8 *)(iVar13 + (iVar14 + 2) * 0x10 + 8) = 0x71006f00;
          iVar14 = iVar14 + 3;
        }
      }
      else {
        if (acStack_10[iVar16] == '\x01') {
          bVar18 = abStack_3770[iVar16 * 2];
          uVar9 = __fixunssfdi(afStack_3da0[0]);
          *(ulong *)(iVar13 + (iVar14 + 1) * 0x10 + 8) =
               (ulong)uVar9 << 0x20 | (ulong)bVar18 << 0x18 | 0x808023;
          bVar18 = abStack_3770[iVar16 * 2];
          uVar9 = __fixunssfdi(afStack_3da0[1]);
          *(ulong *)(iVar13 + (iVar14 + 3) * 0x10) =
               (ulong)uVar9 << 0x20 | (ulong)bVar18 << 0x18 | 0x550f00;
          bVar18 = abStack_3770[iVar16 * 2];
          uVar9 = __fixunssfdi(afStack_3da0[2]);
          *(ulong *)(iVar13 + (iVar14 + 4) * 0x10 + 8) =
               (ulong)uVar9 << 0x20 | (ulong)bVar18 << 0x18 | 0x550f00;
        }
        else {
          bVar18 = abStack_3770[iVar16 * 2];
          uVar9 = __fixunssfdi(afStack_3da0[0]);
          *(ulong *)(iVar13 + (iVar14 + 1) * 0x10 + 8) =
               (ulong)uVar9 << 0x20 | (ulong)bVar18 << 0x18 | 0x285080;
          bVar18 = abStack_3770[iVar16 * 2];
          uVar9 = __fixunssfdi(afStack_3da0[1]);
          *(ulong *)(iVar13 + (iVar14 + 3) * 0x10) =
               (ulong)uVar9 << 0x20 | (ulong)bVar18 << 0x18 | 0x5055a;
          bVar18 = abStack_3770[iVar16 * 2];
          uVar9 = __fixunssfdi(afStack_3da0[2]);
          *(ulong *)(iVar13 + (iVar14 + 4) * 0x10 + 8) =
               (ulong)uVar9 << 0x20 | (ulong)bVar18 << 0x18 | 0x5055a;
        }
        *(long *)(iVar13 + (iVar14 + 2) * 0x10 + 8) =
             (long)aiStack_3520[iVar16 * 0x84 + 2] << 0x20 |
             (long)aiStack_3520[iVar16 * 0x84] | (long)aiStack_3520[iVar16 * 0x84 + 1] << 0x10;
        *(long *)(iVar13 + (iVar14 + 4) * 0x10) =
             (long)aiStack_3520[(iVar16 * 0x21 + 1) * 4 + 2] << 0x20 |
             (long)aiStack_3520[(iVar16 * 0x21 + 1) * 4] |
             (long)aiStack_3520[(iVar16 * 0x21 + 1) * 4 + 1] << 0x10;
        *(long *)(iVar13 + (iVar14 + 5) * 0x10 + 8) =
             (long)aiStack_3520[(iVar16 * 0x21 + 2) * 4 + 2] << 0x20 |
             (long)aiStack_3520[(iVar16 * 0x21 + 2) * 4] |
             (long)aiStack_3520[(iVar16 * 0x21 + 2) * 4 + 1] << 0x10;
        iVar14 = iVar14 + 7;
        for (iVar15 = 0; iVar15 < 7; iVar15 = iVar15 + 1) {
          if (acStack_10[iVar16] == '\x01') {
            bVar18 = abStack_3770[iVar16 * 2];
            uVar9 = __fixunssfdi(afStack_3da0[iVar15 * 2 + 3]);
            *(ulong *)(iVar13 + iVar14 * 0x10) =
                 (ulong)bVar18 << 0x18 | 0x550f00 | (ulong)uVar9 << 0x20;
            bVar18 = abStack_3770[iVar16 * 2];
            uVar9 = __fixunssfdi(afStack_3da0[iVar15 * 2 + 4]);
            *(ulong *)(iVar13 + (iVar14 + 1) * 0x10 + 8) =
                 (ulong)bVar18 << 0x18 | 0x550f00 | (ulong)uVar9 << 0x20;
          }
          else {
            bVar18 = abStack_3770[iVar16 * 2];
            uVar9 = __fixunssfdi(afStack_3da0[iVar15 * 2 + 3]);
            *(ulong *)(iVar13 + iVar14 * 0x10) =
                 (ulong)bVar18 << 0x18 | 0x5055a | (ulong)uVar9 << 0x20;
            bVar18 = abStack_3770[iVar16 * 2];
            uVar9 = __fixunssfdi(afStack_3da0[iVar15 * 2 + 4]);
            *(ulong *)(iVar13 + (iVar14 + 1) * 0x10 + 8) =
                 (ulong)bVar18 << 0x18 | 0x5055a | (ulong)uVar9 << 0x20;
          }
          *(long *)(iVar13 + (iVar14 + 1) * 0x10) =
               (long)aiStack_3520[(iVar16 * 0x21 + iVar15 * 2 + 3) * 4 + 2] << 0x20 |
               (long)aiStack_3520[(iVar16 * 0x21 + iVar15 * 2 + 3) * 4] |
               (long)aiStack_3520[(iVar16 * 0x21 + iVar15 * 2 + 3) * 4 + 1] << 0x10;
          *(long *)(iVar13 + (iVar14 + 2) * 0x10 + 8) =
               (long)aiStack_3520[(iVar16 * 0x21 + iVar15 * 2 + 4) * 4 + 2] << 0x20 |
               (long)aiStack_3520[(iVar16 * 0x21 + iVar15 * 2 + 4) * 4] |
               (long)aiStack_3520[(iVar16 * 0x21 + iVar15 * 2 + 4) * 4 + 1] << 0x10;
          iVar14 = iVar14 + 3;
        }
      }
    }
    iVar14 = iVar14 + 5;
    for (iVar16 = 0; iVar16 < 0xc; iVar16 = iVar16 + 1) {
      if (acStack_10[iVar16] == '\0') {
        *(undefined8 *)(iVar13 + (iVar14 + 2) * 0x10 + 8) = 0x71006f00;
        *(undefined8 *)(iVar13 + (iVar14 + 4) * 0x10) = 0x71006f00;
        *(undefined8 *)(iVar13 + (iVar14 + 5) * 0x10 + 8) = 0x71006f00;
        iVar14 = iVar14 + 7;
        for (iVar15 = 0; iVar15 < 7; iVar15 = iVar15 + 1) {
          *(undefined8 *)(iVar13 + (iVar14 + 1) * 0x10) = 0x71006f00;
          *(undefined8 *)(iVar13 + (iVar14 + 2) * 0x10 + 8) = 0x71006f00;
          iVar14 = iVar14 + 3;
        }
      }
      else {
        if (acStack_10[iVar16] == '\x01') {
          bVar18 = abStack_3770[iVar16 * 2 + 1];
          uVar9 = __fixunssfdi(afStack_3da0[0]);
          *(ulong *)(iVar13 + (iVar14 + 1) * 0x10 + 8) =
               (ulong)uVar9 << 0x20 | (ulong)bVar18 << 0x18 | 0x550f00;
          bVar18 = abStack_3770[iVar16 * 2 + 1];
          uVar9 = __fixunssfdi(afStack_3da0[0x11]);
          *(ulong *)(iVar13 + (iVar14 + 3) * 0x10) =
               (ulong)uVar9 << 0x20 | (ulong)bVar18 << 0x18 | 0x550f00;
          bVar18 = abStack_3770[iVar16 * 2 + 1];
          uVar9 = __fixunssfdi(afStack_3da0[0x12]);
          *(ulong *)(iVar13 + (iVar14 + 4) * 0x10 + 8) =
               (ulong)uVar9 << 0x20 | (ulong)bVar18 << 0x18 | 0x550f00;
        }
        else {
          bVar18 = abStack_3770[iVar16 * 2 + 1];
          uVar9 = __fixunssfdi(afStack_3da0[0]);
          *(ulong *)(iVar13 + (iVar14 + 1) * 0x10 + 8) =
               (ulong)uVar9 << 0x20 | (ulong)bVar18 << 0x18 | 0x5055a;
          bVar18 = abStack_3770[iVar16 * 2 + 1];
          uVar9 = __fixunssfdi(afStack_3da0[0x11]);
          *(ulong *)(iVar13 + (iVar14 + 3) * 0x10) =
               (ulong)uVar9 << 0x20 | (ulong)bVar18 << 0x18 | 0x5055a;
          bVar18 = abStack_3770[iVar16 * 2 + 1];
          uVar9 = __fixunssfdi(afStack_3da0[0x12]);
          *(ulong *)(iVar13 + (iVar14 + 4) * 0x10 + 8) =
               (ulong)uVar9 << 0x20 | (ulong)bVar18 << 0x18 | 0x5055a;
        }
        *(long *)(iVar13 + (iVar14 + 2) * 0x10 + 8) =
             (long)aiStack_3520[iVar16 * 0x84 + 2] << 0x20 |
             (long)aiStack_3520[iVar16 * 0x84] | (long)aiStack_3520[iVar16 * 0x84 + 1] << 0x10;
        *(long *)(iVar13 + (iVar14 + 4) * 0x10) =
             (long)aiStack_3520[(iVar16 * 0x21 + 0x11) * 4 + 2] << 0x20 |
             (long)aiStack_3520[(iVar16 * 0x21 + 0x11) * 4] |
             (long)aiStack_3520[(iVar16 * 0x21 + 0x11) * 4 + 1] << 0x10;
        *(long *)(iVar13 + (iVar14 + 5) * 0x10 + 8) =
             (long)aiStack_3520[(iVar16 * 0x21 + 0x12) * 4 + 2] << 0x20 |
             (long)aiStack_3520[(iVar16 * 0x21 + 0x12) * 4] |
             (long)aiStack_3520[(iVar16 * 0x21 + 0x12) * 4 + 1] << 0x10;
        iVar14 = iVar14 + 7;
        for (iVar15 = 0; iVar15 < 7; iVar15 = iVar15 + 1) {
          if (acStack_10[iVar16] == '\x01') {
            bVar18 = abStack_3770[iVar16 * 2 + 1];
            uVar9 = __fixunssfdi(afStack_3da0[iVar15 * 2 + 0x13]);
            *(ulong *)(iVar13 + iVar14 * 0x10) =
                 (ulong)bVar18 << 0x18 | 0x550f00 | (ulong)uVar9 << 0x20;
            bVar18 = abStack_3770[iVar16 * 2 + 1];
            uVar9 = __fixunssfdi(afStack_3da0[iVar15 * 2 + 0x14]);
            *(ulong *)(iVar13 + (iVar14 + 1) * 0x10 + 8) =
                 (ulong)bVar18 << 0x18 | 0x550f00 | (ulong)uVar9 << 0x20;
          }
          else {
            bVar18 = abStack_3770[iVar16 * 2 + 1];
            uVar9 = __fixunssfdi(afStack_3da0[iVar15 * 2 + 0x13]);
            *(ulong *)(iVar13 + iVar14 * 0x10) =
                 (ulong)bVar18 << 0x18 | 0x5055a | (ulong)uVar9 << 0x20;
            bVar18 = abStack_3770[iVar16 * 2 + 1];
            uVar9 = __fixunssfdi(afStack_3da0[iVar15 * 2 + 0x14]);
            *(ulong *)(iVar13 + (iVar14 + 1) * 0x10 + 8) =
                 (ulong)bVar18 << 0x18 | 0x5055a | (ulong)uVar9 << 0x20;
          }
          *(long *)(iVar13 + (iVar14 + 1) * 0x10) =
               (long)aiStack_3520[(iVar16 * 0x21 + iVar15 * 2 + 0x13) * 4 + 2] << 0x20 |
               (long)aiStack_3520[(iVar16 * 0x21 + iVar15 * 2 + 0x13) * 4] |
               (long)aiStack_3520[(iVar16 * 0x21 + iVar15 * 2 + 0x13) * 4 + 1] << 0x10;
          *(long *)(iVar13 + (iVar14 + 2) * 0x10 + 8) =
               (long)aiStack_3520[(iVar16 * 0x21 + iVar15 * 2 + 0x14) * 4 + 2] << 0x20 |
               (long)aiStack_3520[(iVar16 * 0x21 + iVar15 * 2 + 0x14) * 4] |
               (long)aiStack_3520[(iVar16 * 0x21 + iVar15 * 2 + 0x14) * 4 + 1] << 0x10;
          iVar14 = iVar14 + 3;
        }
      }
    }
    iVar14 = iVar14 + 5;
    for (iVar16 = 0; iVar16 < 0xc; iVar16 = iVar16 + 1) {
      if (acStack_10[iVar16] == '\0') {
        *(undefined8 *)(iVar13 + (iVar14 + 2) * 0x10 + 8) = 0x71006f00;
        *(undefined8 *)(iVar13 + (iVar14 + 4) * 0x10) = 0x71006f00;
        *(undefined8 *)(iVar13 + (iVar14 + 5) * 0x10 + 8) = 0x71006f00;
        iVar14 = iVar14 + 7;
        for (iVar15 = 0; iVar15 < 7; iVar15 = iVar15 + 1) {
          *(undefined8 *)(iVar13 + (iVar14 + 1) * 0x10) = 0x71006f00;
          *(undefined8 *)(iVar13 + (iVar14 + 2) * 0x10 + 8) = 0x71006f00;
          iVar14 = iVar14 + 3;
        }
      }
      else {
        if (acStack_10[iVar16] == '\x01') {
          bVar18 = abStack_3770[iVar16 * 2 + 1];
          uVar9 = __fixunssfdi(afStack_3da0[0]);
          *(ulong *)(iVar13 + (iVar14 + 1) * 0x10 + 8) =
               (ulong)uVar9 << 0x20 | (ulong)bVar18 << 0x18 | 0x808023;
          bVar18 = abStack_3770[iVar16 * 2 + 1];
          uVar9 = __fixunssfdi(afStack_3da0[0x11]);
          *(ulong *)(iVar13 + (iVar14 + 3) * 0x10) =
               (ulong)uVar9 << 0x20 | (ulong)bVar18 << 0x18 | 0x808023;
          bVar18 = abStack_3770[iVar16 * 2 + 1];
          uVar9 = __fixunssfdi(afStack_3da0[0x12]);
          *(ulong *)(iVar13 + (iVar14 + 4) * 0x10 + 8) =
               (ulong)uVar9 << 0x20 | (ulong)bVar18 << 0x18 | 0x808023;
        }
        else {
          bVar18 = abStack_3770[iVar16 * 2 + 1];
          uVar9 = __fixunssfdi(afStack_3da0[0]);
          *(ulong *)(iVar13 + (iVar14 + 1) * 0x10 + 8) =
               (ulong)uVar9 << 0x20 | (ulong)bVar18 << 0x18 | 0x285080;
          bVar18 = abStack_3770[iVar16 * 2 + 1];
          uVar9 = __fixunssfdi(afStack_3da0[0x11]);
          *(ulong *)(iVar13 + (iVar14 + 3) * 0x10) =
               (ulong)uVar9 << 0x20 | (ulong)bVar18 << 0x18 | 0x285080;
          bVar18 = abStack_3770[iVar16 * 2 + 1];
          uVar9 = __fixunssfdi(afStack_3da0[0x12]);
          *(ulong *)(iVar13 + (iVar14 + 4) * 0x10 + 8) =
               (ulong)uVar9 << 0x20 | (ulong)bVar18 << 0x18 | 0x285080;
        }
        *(long *)(iVar13 + (iVar14 + 2) * 0x10 + 8) =
             (long)aiStack_3520[iVar16 * 0x84 + 2] << 0x20 |
             (long)aiStack_3520[iVar16 * 0x84] | (long)aiStack_3520[iVar16 * 0x84 + 1] << 0x10;
        *(long *)(iVar13 + (iVar14 + 4) * 0x10) =
             (long)aiStack_3520[(iVar16 * 0x21 + 0x11) * 4 + 2] << 0x20 |
             (long)aiStack_3520[(iVar16 * 0x21 + 0x11) * 4] |
             (long)aiStack_3520[(iVar16 * 0x21 + 0x11) * 4 + 1] << 0x10;
        *(long *)(iVar13 + (iVar14 + 5) * 0x10 + 8) =
             (long)aiStack_3520[(iVar16 * 0x21 + 0x12) * 4 + 2] << 0x20 |
             (long)aiStack_3520[(iVar16 * 0x21 + 0x12) * 4] |
             (long)aiStack_3520[(iVar16 * 0x21 + 0x12) * 4 + 1] << 0x10;
        iVar14 = iVar14 + 7;
        for (iVar15 = 0; iVar15 < 7; iVar15 = iVar15 + 1) {
          if (acStack_10[iVar16] == '\x01') {
            bVar18 = abStack_3770[iVar16 * 2 + 1];
            uVar9 = __fixunssfdi(afStack_3da0[iVar15 * 2 + 0x13]);
            *(ulong *)(iVar13 + iVar14 * 0x10) =
                 (ulong)bVar18 << 0x18 | 0x808023 | (ulong)uVar9 << 0x20;
            bVar18 = abStack_3770[iVar16 * 2 + 1];
            uVar9 = __fixunssfdi(afStack_3da0[iVar15 * 2 + 0x14]);
            *(ulong *)(iVar13 + (iVar14 + 1) * 0x10 + 8) =
                 (ulong)bVar18 << 0x18 | 0x808023 | (ulong)uVar9 << 0x20;
          }
          else {
            bVar18 = abStack_3770[iVar16 * 2 + 1];
            uVar9 = __fixunssfdi(afStack_3da0[iVar15 * 2 + 0x13]);
            *(ulong *)(iVar13 + iVar14 * 0x10) =
                 (ulong)bVar18 << 0x18 | 0x285080 | (ulong)uVar9 << 0x20;
            bVar18 = abStack_3770[iVar16 * 2 + 1];
            uVar9 = __fixunssfdi(afStack_3da0[iVar15 * 2 + 0x14]);
            *(ulong *)(iVar13 + (iVar14 + 1) * 0x10 + 8) =
                 (ulong)bVar18 << 0x18 | 0x285080 | (ulong)uVar9 << 0x20;
          }
          *(long *)(iVar13 + (iVar14 + 1) * 0x10) =
               (long)aiStack_3520[(iVar16 * 0x21 + iVar15 * 2 + 0x13) * 4 + 2] << 0x20 |
               (long)aiStack_3520[(iVar16 * 0x21 + iVar15 * 2 + 0x13) * 4] |
               (long)aiStack_3520[(iVar16 * 0x21 + iVar15 * 2 + 0x13) * 4 + 1] << 0x10;
          *(long *)(iVar13 + (iVar14 + 2) * 0x10 + 8) =
               (long)aiStack_3520[(iVar16 * 0x21 + iVar15 * 2 + 0x14) * 4 + 2] << 0x20 |
               (long)aiStack_3520[(iVar16 * 0x21 + iVar15 * 2 + 0x14) * 4] |
               (long)aiStack_3520[(iVar16 * 0x21 + iVar15 * 2 + 0x14) * 4 + 1] << 0x10;
          iVar14 = iVar14 + 3;
        }
      }
    }
    *(int *)(param_1 + 0x40) = iVar13 + iVar14 * 0x10;
    *(uint *)(param_1 + 0x4c) = uVar17;
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x004f5640  getPacket__9ComboFormFv
 * C++: ComboForm::getPacket()
 * size: 0x18c bytes
 * --------------------------------------------------------------------------- */
undefined4 getPacket__9ComboFormFv(int param_1)

{
  int iVar1;
  long lVar2;
  undefined4 *puVar3;
  
  MakePacket__9ComboFormFv(param_1);
  puVar3 = *(undefined4 **)(param_1 + 0x40);
  *(undefined4 *)(param_1 + 0x104) = 0x2e;
  for (iVar1 = *(int *)(iGpffff86b4 + 0x4370); iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x3c)) {
    if (((*(int *)(iVar1 + 0x4c) == 4) && (*(int *)(iVar1 + 0x54) != 0)) &&
       (lVar2 = (**(code **)(*(int *)(iVar1 + 0x14) + 0x34))(), lVar2 != 0)) {
      *puVar3 = 0x20000000;
      puVar3[1] = (int)lVar2;
      puVar3[2] = 0;
      puVar3[3] = 0;
      puVar3 = *(undefined4 **)(iVar1 + 0x54);
    }
  }
  for (iVar1 = *(int *)(iGpffff86b4 + 0x4370); iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x3c)) {
    if (((*(int *)(iVar1 + 0x4c) == 0xc) && (*(int *)(iVar1 + 0x54) != 0)) &&
       (lVar2 = (**(code **)(*(int *)(iVar1 + 0x14) + 0x34))(), lVar2 != 0)) {
      *puVar3 = 0x20000000;
      puVar3[1] = (int)lVar2;
      puVar3[2] = 0;
      puVar3[3] = 0;
      puVar3 = *(undefined4 **)(iVar1 + 0x54);
    }
  }
  *puVar3 = 0x60000000;
  puVar3[1] = 0;
  puVar3[2] = 0;
  puVar3[3] = 0;
  return *(undefined4 *)(param_1 + *(int *)(param_1 + 0x4c) * 4 + 0x18);
}

/* ---------------------------------------------------------------------------
 * JP: 0x004f5820  ComboAreaReset__9ComboFormFv
 * C++: ComboForm::ComboAreaReset()
 * size: 0x5d0 bytes
 * --------------------------------------------------------------------------- */
void ComboAreaReset__9ComboFormFv(int param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  
  for (uVar1 = 0; (int)uVar1 < 0xc; uVar1 = uVar1 + 1) {
    if (((((*(byte *)(iGpffff86b4 + uVar1 * 0x4f0 + 0xb0) & 1) == 0) ||
         (-1 < (long)((ulong)*(byte *)(iGpffff86b4 + uVar1 * 0x4f0 + 0xb0) << 0x3e))) ||
        ((long)((ulong)*(byte *)(iGpffff86b4 + uVar1 * 0x4f0 + 0xb2) << 0x3d) < 0)) ||
       (*(short *)(iGpffff86b4 + uVar1 * 0x4f0 + 0x124) < 1)) {
      *(undefined1 *)(param_1 + uVar1 + 0x50) = 0;
      *(undefined4 *)(param_1 + uVar1 * 8 + 0x74) = 0;
    }
    else if ((((*(byte *)(iGpffff86b4 + uVar1 * 0x4f0 + 0xb4) & 1) == 0) &&
             (*(short *)(iGpffff86b4 + uVar1 * 0x4f0 + 0x120) != 8)) &&
            ((*(short *)(iGpffff86b4 + uVar1 * 0x4f0 + 0x120) != 9 &&
             ((*(short *)(iGpffff86b4 + uVar1 * 0x4f0 + 0x120) != 10 &&
              (*(short *)(iGpffff86b4 + uVar1 * 0x4f0 + 300) < 1)))))) {
      *(undefined1 *)(param_1 + uVar1 + 0x50) = 0;
      *(undefined4 *)(param_1 + uVar1 * 8 + 0x74) = 0;
    }
    else {
      iVar3 = 0;
      for (iVar2 = 0; iVar2 < 0x20; iVar2 = iVar2 + 1) {
        if (((*(char *)(iGpffff86b4 + uVar1 * 0x4f0 + iVar2 * 0xc + 0x1bc) == 'G') &&
            (((ulong)*(byte *)(iGpffff86b4 + uVar1 * 0x4f0 + iVar2 * 0xc + 0x1b9) & 0x1f) >> 2 == 0)
            ) && ((*(uint *)(iGpffff86b4 + uVar1 * 0x4f0 + iVar2 * 0xc + 0x1c0) & 0x24) != 0)) {
          iVar3 = iVar3 + 1;
        }
      }
      if (iVar3 == 0) {
        if ((*(char *)(iGpffff86b4 + uVar1 * 0x4f0 + 0xb8) < '\x16') ||
           ('&' < *(char *)(iGpffff86b4 + uVar1 * 0x4f0 + 0xb8))) {
          *(undefined2 *)(param_1 + uVar1 * 2 + 0x5c) =
               *(undefined2 *)(iGpffff86b4 + uVar1 * 0x4f0 + 0x57e);
          if (((uint)*(ushort *)(param_1 + uVar1 * 2 + 0x5c) & 1 << (uVar1 & 0x1f)) != 0) {
            iVar2 = param_1 + uVar1 * 2;
            *(short *)(iVar2 + 0x5c) = *(short *)(iVar2 + 0x5c) - (short)(1 << (uVar1 & 0x1f));
          }
          if (*(short *)(param_1 + uVar1 * 2 + 0x5c) == 0) {
            if (*(char *)(param_1 + uVar1 + 0x50) == '\x01') {
              *(undefined1 *)(param_1 + uVar1 + 0x50) = 3;
            }
            else if (*(char *)(param_1 + uVar1 + 0x50) == '\x02') {
              *(undefined1 *)(param_1 + uVar1 + 0x50) = 3;
              *(undefined4 *)(param_1 + uVar1 * 8 + 0x74) = 0x43000000;
            }
          }
          else if (*(char *)(param_1 + uVar1 + 0x50) == '\0') {
            *(undefined1 *)(param_1 + uVar1 + 0x50) = 1;
            *(undefined4 *)(param_1 + uVar1 * 8 + 0x74) = 0;
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,0x2001004,0,0);
          }
          else if (*(char *)(param_1 + uVar1 + 0x50) == '\x03') {
            *(undefined1 *)(param_1 + uVar1 + 0x50) = 1;
            PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd_ptr,0x2001004,0,0);
          }
        }
        else {
          *(undefined1 *)(param_1 + uVar1 + 0x50) = 0;
          *(undefined4 *)(param_1 + uVar1 * 8 + 0x74) = 0;
        }
      }
      else {
        *(undefined1 *)(param_1 + uVar1 + 0x50) = 0;
        *(undefined4 *)(param_1 + uVar1 * 8 + 0x74) = 0;
      }
    }
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b410  @24@getPacket__9ComboFormFv
 * C++: @24@getPacket__9ComboFormFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
undefined4 _24_getPacket__9ComboFormFv(int param_1)

{
  int iVar1;
  long lVar2;
  undefined4 *puVar3;
  
  MakePacket__9ComboFormFv(param_1 + -0x18);
  puVar3 = *(undefined4 **)(param_1 + 0x28);
  *(undefined4 *)(param_1 + 0xec) = 0x2e;
  for (iVar1 = *(int *)(iGpffff86b4 + 0x4370); iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x3c)) {
    if (((*(int *)(iVar1 + 0x4c) == 4) && (*(int *)(iVar1 + 0x54) != 0)) &&
       (lVar2 = (**(code **)(*(int *)(iVar1 + 0x14) + 0x34))(), lVar2 != 0)) {
      *puVar3 = 0x20000000;
      puVar3[1] = (int)lVar2;
      puVar3[2] = 0;
      puVar3[3] = 0;
      puVar3 = *(undefined4 **)(iVar1 + 0x54);
    }
  }
  for (iVar1 = *(int *)(iGpffff86b4 + 0x4370); iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x3c)) {
    if (((*(int *)(iVar1 + 0x4c) == 0xc) && (*(int *)(iVar1 + 0x54) != 0)) &&
       (lVar2 = (**(code **)(*(int *)(iVar1 + 0x14) + 0x34))(), lVar2 != 0)) {
      *puVar3 = 0x20000000;
      puVar3[1] = (int)lVar2;
      puVar3[2] = 0;
      puVar3[3] = 0;
      puVar3 = *(undefined4 **)(iVar1 + 0x54);
    }
  }
  *puVar3 = 0x60000000;
  puVar3[1] = 0;
  puVar3[2] = 0;
  puVar3[3] = 0;
  return *(undefined4 *)(param_1 + -0x18 + *(int *)(param_1 + 0x34) * 4 + 0x18);
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b420  @24@__dt__9ComboFormFv
 * C++: @24@__dt__9ComboFormFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int * _24___dt__9ComboFormFv(int *param_1,short param_2)

{
  int *piVar1;
  
  piVar1 = param_1 + -6;
  if (piVar1 != (int *)0x0) {
    param_1[-1] = 0x40a570;
    param_1[4] = 0x40a580;
    param_1[7] = 0x40a590;
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
 * JP: 0x0054b430  @44@__dt__9ComboFormFv
 * C++: @44@__dt__9ComboFormFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int _44___dt__9ComboFormFv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x2c;
  if (iVar1 != 0) {
    *(undefined4 *)(param_1 + -0x18) = 0x40a570;
    *(undefined4 *)(param_1 + -4) = 0x40a580;
    *(undefined4 *)(param_1 + 8) = 0x40a590;
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

