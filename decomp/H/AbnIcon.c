/* decomp/H/AbnIcon.c — cleaned Ghidra output (SH2JP_BATTLE.BIN, JP Furokuban, base 0x00430a00).
 * 8 function(s). Types: see types.h. Names/gp globals resolved from symbols/SLPM_602.19.syms. */
#include "types.h"

/* ---------------------------------------------------------------------------
 * JP: 0x00500970  __ct__7AbnIconFii
 * C++: AbnIcon::__ct(int, int)
 * size: 0x354 bytes
 * --------------------------------------------------------------------------- */
int __ct__7AbnIconFii(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  float fVar2;
  
  __ct__6BtlEffFii(param_1,param_2,param_3);
  *(undefined4 *)(param_1 + 0x14) = 0x40a3e0;
  *(undefined4 *)(param_1 + 0x28) = 0x40a3f0;
  *(undefined4 *)(param_1 + 0x34) = 0x40a400;
  *(undefined4 *)(param_1 + 0x44) = param_2;
  *(undefined4 *)(param_1 + 0x48) = param_3;
  *(undefined4 *)(param_1 + 0x4c) = 0x14;
  *(undefined4 *)(param_1 + 0x40) = 0;
  *(undefined4 *)(param_1 + 0x5c) = 0;
  *(undefined4 *)(param_1 + 0x60) = 0;
  *(undefined4 *)(param_1 + 100) = 0;
  *(undefined4 *)(param_1 + 0x68) = 0;
  *(undefined4 *)(param_1 + 0x74) = 0;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  *(undefined4 *)(param_1 + 0x18) = 0;
  *(undefined4 *)(param_1 + 0x54) = 0;
  *(undefined2 *)(param_1 + 0x6c) =
       *(undefined2 *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x58a);
  *(undefined2 *)(param_1 + 0x6e) =
       *(undefined2 *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x58c);
  *(undefined4 *)(param_1 + 0x70) = 0x40200000;
  if (*(float *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x594) < 0.25) {
    fVar2 = (float)sinf(*(float *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x594
                                             ) * 4.0 * 1.5707964);
    *(float *)(param_1 + 0x70) = fVar2 * 2.5;
  }
  else if (1.75 <= *(float *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x594)) {
    fVar2 = (float)sinf((2.0 - *(float *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0
                                                    + 0x594)) * 4.0 * 1.5707964);
    *(float *)(param_1 + 0x70) = fVar2 * 2.5;
  }
  Entry__7CPollerFP7CPolObjib(iGpffff858c + 0x48,param_1,0x80,0);
  iVar1 = param_1;
  if (param_1 != 0) {
    iVar1 = param_1 + 0x18;
  }
  AddOT__5WorldFiP8VIF1Prim(0x42bf10,8,iVar1);
  *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfd | 2;
  BtlEffEntry__7CBattleFiP6BtlEff(iGpffff86b4,*(undefined4 *)(param_1 + 0x48),param_1);
  return param_1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00500cd0  __dt__7AbnIconFv
 * C++: AbnIcon::__dt()
 * size: 0x154 bytes
 * --------------------------------------------------------------------------- */
int __dt__7AbnIconFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x14) = 0x40a3e0;
    *(undefined4 *)(param_1 + 0x28) = 0x40a3f0;
    *(undefined4 *)(param_1 + 0x34) = 0x40a400;
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
 * JP: 0x00500e30  Destruct__7AbnIconFv
 * C++: AbnIcon::Destruct()
 * size: 0xcc bytes
 * --------------------------------------------------------------------------- */
void Destruct__7AbnIconFv(int param_1)

{
  int iVar1;
  
  BtlEffRelease__7CBattleFiP6BtlEff(uGpffff86b4,*(undefined4 *)(param_1 + 0x48),param_1);
  Dispose__7CPollerFP7CPolObj(iGpffff858c + 0x48,param_1);
  if ((long)((ulong)*(byte *)(param_1 + 0x40) << 0x3e) < 0) {
    iVar1 = param_1;
    if (param_1 != 0) {
      iVar1 = param_1 + 0x18;
    }
    ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,iVar1);
  }
  *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfd;
  (**(code **)(*(int *)(param_1 + 0x34) + 0xc))();
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x00500f00  Polling__7AbnIconFv
 * C++: AbnIcon::Polling()
 * size: 0x2cc bytes
 * --------------------------------------------------------------------------- */
undefined4 Polling__7AbnIconFv(int param_1)

{
  int iVar1;
  float fStack_14;
  
  fStack_14 = *(float *)(iGpffff86b4 + 0x38);
  if ((*(byte *)(iGpffff86b4 + 0x24) & 1) != 0) {
    fStack_14 = 0.0;
  }
  *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) + fStack_14 * 6.2831855;
  if (3.1415927 <= *(float *)(param_1 + 0x74)) {
    *(float *)(param_1 + 0x74) = *(float *)(param_1 + 0x74) - 6.2831855;
  }
  iVar1 = *(int *)(param_1 + 0x5c);
  if (iVar1 != 2) {
    if (iVar1 != 1) {
      if (iVar1 != 0) {
        return 0;
      }
      *(float *)(param_1 + 0x68) = *(float *)(param_1 + 0x68) + fStack_14 * 4.0;
      if (*(float *)(param_1 + 0x68) < 1.0) {
        return 0;
      }
      *(undefined4 *)(param_1 + 0x68) = 0x3f800000;
      *(undefined4 *)(param_1 + 0x5c) = 1;
      return 0;
    }
    if (-1 < *(short *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x58a)) {
      return 0;
    }
    *(undefined4 *)(param_1 + 0x5c) = 2;
  }
  *(float *)(param_1 + 0x68) = *(float *)(param_1 + 0x68) - fStack_14 * 4.0;
  if (*(short *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x58a) < 0) {
    if (*(float *)(param_1 + 0x68) <= 0.0) {
      BtlEffRelease__7CBattleFiP6BtlEff(iGpffff86b4,*(undefined4 *)(param_1 + 0x48),param_1);
      if ((long)((ulong)*(byte *)(param_1 + 0x40) << 0x3e) < 0) {
        iVar1 = param_1;
        if (param_1 != 0) {
          iVar1 = param_1 + 0x18;
        }
        ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,iVar1);
      }
      *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfd;
      (**(code **)(*(int *)(param_1 + 0x34) + 0xc))();
      return 1;
    }
  }
  else {
    *(undefined4 *)(param_1 + 0x5c) = 0;
  }
  return 0;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005011d0  MakePacket__7AbnIconFv
 * C++: AbnIcon::MakePacket()
 * size: 0xe00 bytes
 * --------------------------------------------------------------------------- */
void MakePacket__7AbnIconFv(int param_1)

{
  bool bVar1;
  undefined4 *puVar2;
  bool bVar3;
  undefined1 auVar4 [16];
  undefined1 auVar5 [16];
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  undefined4 uVar6;
  undefined8 uVar7;
  undefined8 *puVar8;
  int iVar9;
  uint uVar10;
  uint uVar11;
  int iVar12;
  float fVar13;
  undefined1 auVar14 [16];
  undefined1 auVar15 [16];
  undefined1 auStack_260 [16];
  undefined1 auStack_250 [16];
  undefined1 auStack_240 [16];
  undefined1 auStack_230 [16];
  undefined4 uStack_220;
  undefined4 uStack_21c;
  undefined4 uStack_218;
  undefined4 uStack_214;
  undefined4 uStack_210;
  undefined4 uStack_20c;
  undefined4 uStack_208;
  undefined4 uStack_204;
  undefined4 uStack_200;
  undefined4 uStack_1fc;
  undefined4 uStack_1f8;
  undefined4 uStack_1f4;
  undefined4 uStack_1f0;
  undefined4 uStack_1ec;
  undefined4 uStack_1e8;
  undefined4 uStack_1e4;
  undefined4 uStack_1e0;
  undefined4 uStack_1dc;
  undefined4 uStack_1d8;
  undefined4 uStack_1d4;
  float fStack_1d0;
  float fStack_1cc;
  undefined4 uStack_1c8;
  undefined4 uStack_1c4;
  float fStack_1c0;
  float fStack_1bc;
  undefined4 uStack_1b8;
  undefined4 uStack_1b4;
  int iStack_1b0;
  int iStack_1ac;
  int iStack_1a8;
  int iStack_1a0;
  int iStack_19c;
  int iStack_198;
  float fStack_190;
  float fStack_18c;
  float fStack_188;
  undefined4 uStack_184;
  undefined1 auStack_180 [16];
  undefined1 aauStack_170 [7] [16];
  float fStack_100;
  float fStack_fc;
  float fStack_f8;
  undefined4 uStack_f4;
  float fStack_f0;
  float fStack_ec;
  float fStack_e8;
  undefined4 uStack_e4;
  undefined4 auStack_e0 [16];
  undefined4 uStack_a0;
  undefined4 uStack_9c;
  undefined4 uStack_98;
  undefined4 uStack_94;
  undefined4 uStack_90;
  undefined4 uStack_8c;
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined4 auStack_70 [7];
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
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
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  if ((*(int *)(param_1 + 0x5c) != 2) &&
     (-1 < *(short *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x58a))) {
    *(undefined2 *)(param_1 + 0x6c) =
         *(undefined2 *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x58a);
    *(undefined2 *)(param_1 + 0x6e) =
         *(undefined2 *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x58c);
    *(undefined4 *)(param_1 + 0x70) = 0x40200000;
    if (*(float *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x594) < 0.25) {
      fVar13 = (float)sinf(*(float *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 +
                                                0x594) * 4.0 * 1.5707964);
      *(float *)(param_1 + 0x70) = fVar13 * 2.5;
    }
    else if (1.75 <= *(float *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x594)) {
      fVar13 = (float)sinf((2.0 - *(float *)(iGpffff86b4 +
                                                        *(int *)(param_1 + 0x48) * 0x4f0 + 0x594)) *
                                      4.0 * 1.5707964);
      *(float *)(param_1 + 0x70) = fVar13 * 2.5;
    }
  }
  fVar13 = (float)sinf(*(undefined4 *)(param_1 + 0x74));
  fStack_1bc = *(float *)(param_1 + 0x68) * -5.0 + fVar13 / 2.0;
  fStack_1c0 = -*(float *)(param_1 + 0x70) * *(float *)(param_1 + 0x68);
  uStack_1b8 = 0;
  uStack_1b4 = 0x3f800000;
  uStack_28 = 0;
  uStack_24 = 0x3f800000;
  fStack_30 = fStack_1c0;
  fStack_2c = fStack_1bc;
  fStack_1cc = (float)sinf(*(undefined4 *)(param_1 + 0x74));
  fStack_1cc = fStack_1cc / 2.0;
  fStack_1d0 = *(float *)(param_1 + 0x70) * *(float *)(param_1 + 0x68);
  uStack_1c8 = 0;
  uStack_1c4 = 0x3f800000;
  uStack_18 = 0;
  uStack_14 = 0x3f800000;
  uStack_1e0 = 0;
  uStack_1dc = 0xbf800000;
  uStack_1d8 = 0;
  uStack_1d4 = 0x3f800000;
  uStack_10 = 0;
  uStack_c = 0xbf800000;
  uStack_8 = 0;
  uStack_4 = 0x3f800000;
  fStack_20 = fStack_1d0;
  fStack_1c = fStack_1cc;
  __ct__6MatrixFRC6Matrix(auStack_70,iGpffff8598 + 0x240);
  uStack_40 = 0;
  uStack_3c = 0;
  uStack_38 = 0;
  uStack_34 = 0x3f800000;
  uStack_a0 = in_zero_lo;
  uStack_9c = in_zero_hi;
  uStack_98 = in_zero_udw;
  uStack_94 = in_register_0000000c;
  uStack_90 = in_zero_lo;
  uStack_8c = in_zero_hi;
  uStack_88 = in_zero_udw;
  uStack_84 = in_register_0000000c;
  uStack_80 = in_zero_lo;
  uStack_7c = in_zero_hi;
  uStack_78 = in_zero_udw;
  uStack_74 = in_register_0000000c;
  RotTransVector(&uStack_a0,&fStack_30,auStack_70,3);
  GetViewScreenMatrix__9GsxCameraFv(&uStack_220,iGpffff8598);
  auStack_70[0] = uStack_220;
  auStack_70[1] = uStack_21c;
  auStack_70[2] = uStack_218;
  auStack_70[3] = uStack_214;
  auStack_70[4] = uStack_210;
  auStack_70[5] = uStack_20c;
  auStack_70[6] = uStack_208;
  uStack_54 = uStack_204;
  uStack_50 = uStack_200;
  uStack_4c = uStack_1fc;
  uStack_48 = uStack_1f8;
  uStack_44 = uStack_1f4;
  uStack_40 = uStack_1f0;
  uStack_3c = uStack_1ec;
  uStack_38 = uStack_1e8;
  uStack_34 = uStack_1e4;
  for (iVar12 = 0; iVar12 < 4; iVar12 = iVar12 + 1) {
    auStack_e0[iVar12 * 4] = auStack_70[iVar12 * 4];
    auStack_e0[iVar12 * 4 + 1] = auStack_70[iVar12 * 4 + 1];
    auStack_e0[iVar12 * 4 + 2] = auStack_70[iVar12 * 4 + 2];
    auStack_e0[iVar12 * 4 + 3] = auStack_70[iVar12 * 4 + 3];
  }
  fStack_f0 = 65535.0;
  fStack_ec = 65535.0;
  fStack_e8 = 65535.0;
  uStack_e4 = 0x3f800000;
  fStack_100 = -65535.0;
  fStack_fc = -65535.0;
  fStack_f8 = -65535.0;
  uStack_f4 = 0x3f800000;
  for (iVar12 = 0;
      iVar12 < *(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x534) + 8);
      iVar12 = iVar12 + 1) {
    puVar8 = (undefined8 *)
             (*(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x144) + 0x30) +
              (uint)*(byte *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 +
                                               0x144) + 0xe4) +
                             *(short *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + iVar12 * 2
                                       + 0x53c) * 0x110) * 0x1f0 + (bGpffff8340 & 1) * 0x40);
    auStack_70[2] = *(undefined4 *)(puVar8 + 1);
    auStack_70[3] = *(undefined4 *)((int)puVar8 + 0xc);
    auStack_70[0] = (undefined4)*puVar8;
    auStack_70[1] = (undefined4)((ulong)*puVar8 >> 0x20);
    auStack_70[4] = *(undefined4 *)(puVar8 + 2);
    auStack_70[5] = *(undefined4 *)((int)puVar8 + 0x14);
    auStack_70[6] = *(undefined4 *)(puVar8 + 3);
    uStack_54 = *(undefined4 *)((int)puVar8 + 0x1c);
    uStack_50 = *(undefined4 *)(puVar8 + 4);
    uStack_4c = *(undefined4 *)((int)puVar8 + 0x24);
    uStack_48 = *(undefined4 *)(puVar8 + 5);
    uStack_44 = *(undefined4 *)((int)puVar8 + 0x2c);
    uStack_40 = *(undefined4 *)(puVar8 + 6);
    uStack_3c = *(undefined4 *)((int)puVar8 + 0x34);
    uStack_38 = *(undefined4 *)(puVar8 + 7);
    uStack_34 = *(undefined4 *)((int)puVar8 + 0x3c);
    RotTransVector(auStack_180,
                    *(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x144) + 0xe4
                            ) +
                    *(short *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + iVar12 * 2 + 0x53c)
                    * 0x110 + 0x10,auStack_70,8);
    for (iVar9 = 0; iVar9 < 8; iVar9 = iVar9 + 1) {
      if (*(float *)(auStack_180 + iVar9 * 0x10) < fStack_f0) {
        fStack_f0 = *(float *)(auStack_180 + iVar9 * 0x10);
      }
      if (fStack_100 < *(float *)(auStack_180 + iVar9 * 0x10)) {
        fStack_100 = *(float *)(auStack_180 + iVar9 * 0x10);
      }
      if (*(float *)(aauStack_170[iVar9 + -1] + 4) < fStack_ec) {
        fStack_ec = *(float *)(aauStack_170[iVar9 + -1] + 4);
      }
      if (fStack_fc < *(float *)(aauStack_170[iVar9 + -1] + 4)) {
        fStack_fc = *(float *)(aauStack_170[iVar9 + -1] + 4);
      }
      if (*(float *)(aauStack_170[iVar9 + -1] + 8) < fStack_e8) {
        fStack_e8 = *(float *)(aauStack_170[iVar9 + -1] + 8);
      }
      if (fStack_f8 < *(float *)(aauStack_170[iVar9 + -1] + 8)) {
        fStack_f8 = *(float *)(aauStack_170[iVar9 + -1] + 8);
      }
    }
  }
  fStack_188 = (fStack_f8 + fStack_e8) / 2.0;
  fStack_18c = (fStack_fc + fStack_ec) / 2.0;
  fStack_190 = (fStack_100 + fStack_f0) / 2.0;
  uStack_184 = 0x3f800000;
  fVar13 = ((fStack_f8 - fStack_e8) + (fStack_100 - fStack_f0) + (fStack_fc - fStack_ec)) / 6.0;
  auStack_180._4_4_ = uStack_7c;
  auStack_180._0_4_ = uStack_80;
  auStack_180._8_4_ = uStack_78;
  auStack_180._12_4_ = uStack_74;
  aauStack_170[0]._4_4_ = uStack_7c;
  aauStack_170[0]._0_4_ = uStack_80;
  aauStack_170[0]._8_4_ = uStack_78;
  aauStack_170[0]._12_4_ = uStack_74;
  __amu__7FVectorFf(fVar13,auStack_180);
  __amu__7FVectorFf(fVar13,aauStack_170);
  auVar14._4_4_ = fStack_18c;
  auVar14._0_4_ = fStack_190;
  auVar14._8_4_ = fStack_188;
  auVar14._12_4_ = uStack_184;
  auVar14 = _lqc2(auVar14);
  auVar4._4_4_ = uStack_9c;
  auVar4._0_4_ = uStack_a0;
  auVar4._8_4_ = uStack_98;
  auVar4._12_4_ = uStack_94;
  auVar15 = _lqc2(auVar4);
  auVar14 = _vadd(auVar14,auVar15);
  auStack_250 = _sqc2(auVar14);
  __ct__7FVectorFRC7FVector(auStack_230,auStack_250);
  auVar15 = _lqc2(auStack_230);
  auVar14 = _lqc2(auStack_180);
  auVar14 = _vadd(auVar14,auVar15);
  auStack_180 = _sqc2(auVar14);
  auVar15._4_4_ = fStack_18c;
  auVar15._0_4_ = fStack_190;
  auVar15._8_4_ = fStack_188;
  auVar15._12_4_ = uStack_184;
  auVar14 = _lqc2(auVar15);
  auVar5._4_4_ = uStack_8c;
  auVar5._0_4_ = uStack_90;
  auVar5._8_4_ = uStack_88;
  auVar5._12_4_ = uStack_84;
  auVar15 = _lqc2(auVar5);
  auVar14 = _vadd(auVar14,auVar15);
  auStack_260 = _sqc2(auVar14);
  __ct__7FVectorFRC7FVector(auStack_240,auStack_260);
  auVar15 = _lqc2(auStack_240);
  auVar14 = _lqc2(aauStack_170[0]);
  auVar14 = _vadd(auVar14,auVar15);
  aauStack_170[0] = _sqc2(auVar14);
  sceVu0RotTransPersN(&iStack_1b0,auStack_e0,auStack_180,2,0);
  bVar1 = (*(byte *)(param_1 + 0x40) & 1) == 0;
  uVar10 = (uint)bVar1;
  if (*(int *)(param_1 + uVar10 * 4 + 0x18) == 0) {
    uVar6 = __nwa__FUi(0xd0);
    *(undefined4 *)(param_1 + uVar10 * 4 + 0x18) = uVar6;
    iVar12 = *(int *)(param_1 + uVar10 * 4 + 0x18);
    *(undefined4 *)(iVar12 + 0x10) = 0x6000000b;
    *(undefined4 *)(iVar12 + 0x14) = 0;
    *(undefined4 *)(iVar12 + 0x18) = 0x11000000;
    *(undefined4 *)(iVar12 + 0x1c) = 0x5000000b;
    *(undefined8 *)(iVar12 + 0x20) = 0x6000000000000001;
    *(undefined8 *)(iVar12 + 0x28) = 0xe6e8ee;
    *(undefined8 *)(iVar12 + 0x30) = 1;
    *(undefined8 *)(iVar12 + 0x38) = 0x3f;
    *(undefined8 *)(iVar12 + 0x40) = 0x60;
    *(undefined8 *)(iVar12 + 0x48) = 0x14;
    *(undefined8 *)(iVar12 + 0x50) = 5;
    *(undefined8 *)(iVar12 + 0x58) = 0;
    *(undefined8 *)(iVar12 + 0x60) = 0x3001;
    *(undefined8 *)(iVar12 + 0x68) = 0x47;
    uVar7 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x4308),1);
    *(undefined8 *)(iVar12 + 0x70) = uVar7;
    *(undefined8 *)(iVar12 + 0x78) = 0;
    *(undefined8 *)(iVar12 + 0x80) = 0x44;
    *(undefined8 *)(iVar12 + 0x88) = 0x42;
    *(undefined8 *)(iVar12 + 0x90) = 0x6400000000008001;
    *(undefined8 *)(iVar12 + 0x98) = 0x43c310;
    *(undefined8 *)(iVar12 + 0xa0) = 0x156;
  }
  puVar2 = *(undefined4 **)(param_1 + uVar10 * 4 + 0x18);
  bVar3 = false;
  if ((((iStack_1b0 < 0) || (0x10000 < iStack_1b0)) || (iStack_1a0 < 0)) || (0x10000 < iStack_1a0))
  {
    bVar3 = true;
  }
  if (((iStack_1ac < 0) || (0x10000 < iStack_1ac)) || ((iStack_19c < 0 || (0x10000 < iStack_19c))))
  {
    bVar3 = true;
  }
  if ((iStack_1a8 < 0) || (iStack_198 < 0)) {
    bVar3 = true;
  }
  if (bVar3) {
    *puVar2 = 0x60000000;
    puVar2[1] = 0;
    puVar2[2] = 0;
    puVar2[3] = 0;
    *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfe | bVar1;
  }
  else {
    *puVar2 = 0x50000000;
    puVar2[1] = *(undefined4 *)
                 (*(int *)(iGpffff86b4 + 0x4308) +
                  (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x4308) + 10) * 4 + 0xc);
    puVar2[2] = 0;
    puVar2[3] = 0;
    iVar12 = *(int *)(*(short *)(param_1 + 0x6c) * 4 + 0x650d80);
    uVar10 = (uint)*(ushort *)(iVar12 + *(short *)(param_1 + 0x6e) * 8);
    uVar11 = (uint)*(ushort *)(iVar12 + *(short *)(param_1 + 0x6e) * 8 + 2);
    *(ulong *)(puVar2 + 0x2a) =
         (long)(int)(*(float *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x144) +
                               0x4e4) *
                     *(float *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x144) +
                               0x4ec) * 128.0) << 0x18 | 0x808080;
    *(long *)(puVar2 + 0x2c) = (long)(int)(uVar10 * 800) | (long)(int)(uVar11 * 800) << 0x10;
    *(long *)(puVar2 + 0x2e) = (long)iStack_1b0 | (long)iStack_1ac << 0x10;
    *(long *)(puVar2 + 0x30) =
         (long)(int)((uVar10 * 0x32 + 0x32) * 0x10) |
         (long)(int)((uVar11 * 0x32 + 0x32) * 0x10) << 0x10;
    *(long *)(puVar2 + 0x32) = (long)iStack_1a0 | (long)iStack_19c << 0x10;
    *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfe | bVar1;
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b2b0  EndSet__7AbnIconFv
 * C++: AbnIcon::EndSet()
 * size: 0x10 bytes
 * --------------------------------------------------------------------------- */
void EndSet__7AbnIconFv(void)

{
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b4c0  @24@__dt__7AbnIconFv
 * C++: @24@__dt__7AbnIconFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int * _24___dt__7AbnIconFv(int *param_1,short param_2)

{
  int *piVar1;
  
  piVar1 = param_1 + -6;
  if (piVar1 != (int *)0x0) {
    param_1[-1] = 0x40a3e0;
    param_1[4] = 0x40a3f0;
    param_1[7] = 0x40a400;
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
 * JP: 0x0054b4d0  @44@__dt__7AbnIconFv
 * C++: @44@__dt__7AbnIconFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int _44___dt__7AbnIconFv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x2c;
  if (iVar1 != 0) {
    *(undefined4 *)(param_1 + -0x18) = 0x40a3e0;
    *(undefined4 *)(param_1 + -4) = 0x40a3f0;
    *(undefined4 *)(param_1 + 8) = 0x40a400;
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

