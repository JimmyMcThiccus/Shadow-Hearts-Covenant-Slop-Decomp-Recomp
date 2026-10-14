/* decomp/H/BCursole.c — cleaned Ghidra output (SH2JP_BATTLE.BIN, JP Furokuban, base 0x00430a00).
 * 9 function(s). Types: see types.h. Names/gp globals resolved from symbols/SLPM_602.19.syms. */
#include "types.h"

/* ---------------------------------------------------------------------------
 * JP: 0x005d7ad0  __ct__8BCursoleFiiUcUcUcUcUcP7FVector
 * C++: BCursole::__ct(int, int, uchar, uchar, uchar, uchar, uchar, FVector *)
 * size: 0x1cc bytes
 * --------------------------------------------------------------------------- */
undefined4 *
__ct__8BCursoleFiiUcUcUcUcUcP7FVector
          (undefined4 *param_1,undefined4 param_2,undefined2 param_3,undefined1 param_4,
          undefined1 param_5,undefined1 param_6,undefined1 param_7,undefined1 param_8,
          undefined8 *param_9)

{
  undefined8 uVar1;
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0x4049f0;
  __ct__10MenuRenderFv(param_1 + 3);
  param_1[2] = 0x40a7a0;
  param_1[7] = 0x40a7b0;
  param_1[0xd] = 0x40a7c0;
  param_1[0xe] = 0x40a7d0;
  __ct__6CursorFv(param_1 + 0x16);
  param_1[0x58] = in_zero_lo;
  param_1[0x59] = in_zero_hi;
  param_1[0x5a] = in_zero_udw;
  param_1[0x5b] = in_register_0000000c;
  *(undefined2 *)(param_1 + 0x15) = 0;
  param_1[0x14] = param_2;
  *(undefined2 *)((int)param_1 + 0x56) = param_3;
  *(undefined1 *)(param_1 + 0x55) = param_4;
  *(undefined1 *)((int)param_1 + 0x155) = param_5;
  *(undefined1 *)((int)param_1 + 0x156) = param_6;
  *(undefined1 *)((int)param_1 + 0x157) = param_7;
  *(undefined1 *)(param_1 + 0x56) = param_8;
  if (param_9 != (undefined8 *)0x0) {
    *(byte *)(param_1 + 0x15) = *(byte *)(param_1 + 0x15) & 0xfb | 4;
    uVar1 = *param_9;
    uVar2 = *(undefined4 *)(param_9 + 1);
    uVar3 = *(undefined4 *)((int)param_9 + 0xc);
    param_1[0x58] = (int)uVar1;
    param_1[0x59] = (int)((ulong)uVar1 >> 0x20);
    param_1[0x5a] = uVar2;
    param_1[0x5b] = uVar3;
    uVar2 = GetTimer__7SysToolFv();
    param_1[0x5c] = uVar2;
    param_1[0x5d] = 0;
  }
  Create__10MenuRenderFv(param_1 + 3);
  ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,param_1 + 3);
  AddOT__5WorldFiP8VIF1Prim(0x42bf10,0xb,param_1 + 3);
  puVar4 = param_1;
  if (param_1 != (undefined4 *)0x0) {
    puVar4 = param_1 + 8;
  }
  Entry__7CPollerFP7CPolObjib(iGpffff858c + 0x48,puVar4,0x80,0);
  BCurEntry__7BtlMenuFP8BCursole(param_1);
  return param_1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005d7ca0  __dt__8BCursoleFv
 * C++: BCursole::__dt()
 * size: 0x104 bytes
 * --------------------------------------------------------------------------- */
int __dt__8BCursoleFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 8) = 0x40a7a0;
    *(undefined4 *)(param_1 + 0x1c) = 0x40a7b0;
    *(undefined4 *)(param_1 + 0x34) = 0x40a7c0;
    *(undefined4 *)(param_1 + 0x38) = 0x40a7d0;
    if ((long)((ulong)*(byte *)(param_1 + 0x54) << 0x3e) < 0) {
      Release__7MenuObjFv(param_1 + 0x58);
    }
    __dt__6CursorFv(param_1 + 0x58,0xffffffffffffffff);
    __dt__10MenuRenderFv(param_1 + 0xc,0);
    if (param_1 != 0) {
      *(undefined4 *)(param_1 + 8) = 0x4049f0;
    }
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005d7db0  Destruct__8BCursoleFv
 * C++: BCursole::Destruct()
 * size: 0xd0 bytes
 * --------------------------------------------------------------------------- */
void Destruct__8BCursoleFv(int param_1)

{
  int iVar1;
  
  if ((*(byte *)(param_1 + 0x54) & 1) != 0) {
    RemoveObj__12MenuObjTableFP7MenuObj(param_1 + 0x38,param_1 + 0x58);
  }
  *(byte *)(param_1 + 0x54) = *(byte *)(param_1 + 0x54) & 0xfe;
  ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,param_1 + 0xc);
  iVar1 = param_1;
  if (param_1 != 0) {
    iVar1 = param_1 + 0x20;
  }
  Dispose__7CPollerFP7CPolObj(iGpffff858c + 0x48,iVar1);
  (**(code **)(*(int *)(param_1 + 8) + 0xc))();
  BCurRelease__7BtlMenuFP8BCursole(param_1);
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005d7e80  Polling__8BCursoleFv
 * C++: BCursole::Polling()
 * size: 0xd64 bytes
 * --------------------------------------------------------------------------- */
undefined8 Polling__8BCursoleFv(int param_1)

{
  float in_zero_hi;
  ulong uVar1;
  int iVar2;
  int iVar3;
  undefined8 *puVar4;
  float fVar5;
  float fVar6;
  int aiStack_230 [80];
  int aiStack_f0 [7];
  undefined4 uStack_d4;
  undefined4 uStack_d0;
  undefined4 uStack_cc;
  undefined4 uStack_c8;
  undefined4 uStack_c4;
  undefined4 uStack_c0;
  undefined4 uStack_bc;
  undefined4 uStack_b8;
  undefined4 uStack_b4;
  float fStack_b0;
  float fStack_ac;
  float fStack_a8;
  float fStack_a4;
  int aiStack_a0 [34];
  float fStack_18;
  float fStack_14;
  int iStack_10;
  
  iStack_10 = param_1;
  if ((long)((ulong)*(byte *)(param_1 + 0x54) << 0x3d) < 0) {
    fStack_ac = in_zero_hi;
    iVar3 = GetTimer__7SysToolFv();
    fStack_18 = (float)(uint)(iVar3 - *(int *)(iStack_10 + 0x170)) * 0.001;
    *(int *)(iStack_10 + 0x170) = iVar3;
    *(float *)(iStack_10 + 0x174) = *(float *)(iStack_10 + 0x174) + fStack_18 * 6.2831855;
    if (3.1415927 <= *(float *)(iStack_10 + 0x174)) {
      *(float *)(iStack_10 + 0x174) = *(float *)(iStack_10 + 0x174) - 6.2831855;
    }
    if (*(char *)(iStack_10 + 0x156) == '\x01') {
      fStack_b0 = *(float *)(iStack_10 + 0x160) + 1792.0;
      fVar6 = (float)sinf(*(undefined4 *)(iStack_10 + 0x174));
      fStack_a8 = *(float *)(iStack_10 + 0x164) + 1824.0 + fVar6 * 8.0;
    }
    else if (*(char *)(iStack_10 + 0x156) == '\x02') {
      fStack_b0 = *(float *)(iStack_10 + 0x160) + 1792.0;
      fVar6 = (float)sinf(*(undefined4 *)(iStack_10 + 0x174));
      fStack_a8 = (*(float *)(iStack_10 + 0x164) + 1824.0) - fVar6 * 8.0;
    }
    else if (*(char *)(iStack_10 + 0x156) == '\x04') {
      fVar6 = (float)sinf(*(undefined4 *)(iStack_10 + 0x174));
      fStack_b0 = *(float *)(iStack_10 + 0x160) + 1792.0 + fVar6 * 8.0;
      fStack_a8 = *(float *)(iStack_10 + 0x164) + 1824.0;
    }
    else {
      fVar6 = (float)sinf(*(undefined4 *)(iStack_10 + 0x174));
      fStack_b0 = (*(float *)(iStack_10 + 0x160) + 1792.0) - fVar6 * 8.0;
      fStack_a8 = *(float *)(iStack_10 + 0x164) + 1824.0;
    }
    fStack_a4 = 0.0;
    if (-1 < (long)((ulong)*(byte *)(iStack_10 + 0x54) << 0x3e)) {
      Create__6CursorFUcUcUcUc(iStack_10 + 0x58,*(undefined1 *)(iStack_10 + 0x154),
                      *(undefined1 *)(iStack_10 + 0x155),*(undefined1 *)(iStack_10 + 0x156),
                      *(undefined1 *)(iStack_10 + 0x157));
    }
    if ((*(byte *)(iStack_10 + 0x54) & 1) == 0) {
      AddPriority__12MenuObjTableFP7MenuObj(iStack_10 + 0x38,iStack_10 + 0x58);
    }
    *(byte *)(iStack_10 + 0x54) = *(byte *)(iStack_10 + 0x54) & 0xfe | 1;
    *(ushort *)(iStack_10 + 0x10a) =
         *(ushort *)(iStack_10 + 0x10a) & 0xfc3f | (*(byte *)(iStack_10 + 0x158) & 0xf) << 6;
    uVar1 = (ulong)*(byte *)(iStack_10 + 0x109) & 0xfffffffffffffffd | 2;
    *(char *)(iStack_10 + 0x109) = (char)uVar1;
    *(byte *)(iStack_10 + 0x108) =
         *(byte *)(iStack_10 + 0x108) & 0xfd | (byte)((uint)((uVar1 << 0x3e) >> 0x3f) << 1);
    *(undefined2 *)(iStack_10 + 0x6c) = 0x10;
    if ((((fStack_b0 < 0.0) || (4096.0 <= fStack_b0)) || (fStack_a8 < 0.0)) ||
       ((4096.0 <= fStack_a8 || (fStack_a4 < 0.0)))) {
      *(byte *)(iStack_10 + 0x6a) = *(byte *)(iStack_10 + 0x6a) & 0xfe;
    }
    else {
      SetTarget__6CursorFff(fStack_b0 - 1792.0,fStack_a8 - 1824.0,iStack_10 + 0x58);
      *(byte *)(iStack_10 + 0x6a) = *(byte *)(iStack_10 + 0x6a) & 0xfe | 1;
    }
    if (-1 < (long)((ulong)*(byte *)(iStack_10 + 0x54) << 0x3e)) {
      QuickMove__6CursorFv(iStack_10 + 0x58);
    }
    *(byte *)(iStack_10 + 0x54) = *(byte *)(iStack_10 + 0x54) & 0xfd | 2;
  }
  else {
    GetViewScreenMatrix__9GsxCameraFv(aiStack_f0,uGpffff8598);
    for (iVar3 = 0; iVar3 < 4; iVar3 = iVar3 + 1) {
      aiStack_230[iVar3 * 4 + 0x40] = aiStack_f0[iVar3 * 4];
      aiStack_230[iVar3 * 4 + 0x41] = aiStack_f0[iVar3 * 4 + 1];
      aiStack_230[iVar3 * 4 + 0x42] = aiStack_f0[iVar3 * 4 + 2];
      aiStack_230[iVar3 * 4 + 0x43] = aiStack_f0[iVar3 * 4 + 3];
    }
    fStack_b0 = 65535.0;
    fStack_ac = -65535.0;
    fStack_a8 = 65535.0;
    fStack_a4 = 0.0;
    for (iVar3 = 0;
        iVar3 < *(int *)(*(int *)(iGpffff86b4 +
                                  (*(short *)(iStack_10 + 0x56) * 0x50 -
                                  (int)*(short *)(iStack_10 + 0x56)) * 0x10 + 0x534) + 8);
        iVar3 = iVar3 + 1) {
      puVar4 = (undefined8 *)
               (*(int *)(*(int *)(iGpffff86b4 +
                                  (*(short *)(iStack_10 + 0x56) * 0x50 -
                                  (int)*(short *)(iStack_10 + 0x56)) * 0x10 + 0x144) + 0x30) +
                (uint)*(byte *)(*(int *)(*(int *)(iGpffff86b4 +
                                                  (*(short *)(iStack_10 + 0x56) * 0x50 -
                                                  (int)*(short *)(iStack_10 + 0x56)) * 0x10 + 0x144)
                                        + 0xe4) +
                               *(short *)(iGpffff86b4 +
                                          (*(short *)(iStack_10 + 0x56) * 0x50 -
                                          (int)*(short *)(iStack_10 + 0x56)) * 0x10 + iVar3 * 2 +
                                         0x53c) * 0x110) * 0x1f0 + (bGpffff8340 & 1) * 0x40);
      aiStack_f0[2] = *(int *)(puVar4 + 1);
      aiStack_f0[3] = *(undefined4 *)((int)puVar4 + 0xc);
      aiStack_f0[0] = (int)*puVar4;
      aiStack_f0[1] = (int)((ulong)*puVar4 >> 0x20);
      aiStack_f0[4] = *(int *)(puVar4 + 2);
      aiStack_f0[5] = *(undefined4 *)((int)puVar4 + 0x14);
      aiStack_f0[6] = *(int *)(puVar4 + 3);
      uStack_d4 = *(undefined4 *)((int)puVar4 + 0x1c);
      uStack_d0 = *(undefined4 *)(puVar4 + 4);
      uStack_cc = *(undefined4 *)((int)puVar4 + 0x24);
      uStack_c8 = *(undefined4 *)(puVar4 + 5);
      uStack_c4 = *(undefined4 *)((int)puVar4 + 0x2c);
      uStack_c0 = *(undefined4 *)(puVar4 + 6);
      uStack_bc = *(undefined4 *)((int)puVar4 + 0x34);
      uStack_b8 = *(undefined4 *)(puVar4 + 7);
      uStack_b4 = *(undefined4 *)((int)puVar4 + 0x3c);
      RotTransVector(aiStack_a0,
                      *(int *)(*(int *)(iGpffff86b4 +
                                        (*(short *)(iStack_10 + 0x56) * 0x50 -
                                        (int)*(short *)(iStack_10 + 0x56)) * 0x10 + 0x144) + 0xe4) +
                      *(short *)(iGpffff86b4 +
                                 (*(short *)(iStack_10 + 0x56) * 0x50 -
                                 (int)*(short *)(iStack_10 + 0x56)) * 0x10 + iVar3 * 2 + 0x53c) *
                      0x110 + 0x10,aiStack_f0,8);
      for (iVar2 = 0; iVar2 < 8; iVar2 = iVar2 + 1) {
        aiStack_230[iVar2 * 4 + 0x20] = aiStack_a0[iVar2 * 4];
        aiStack_230[iVar2 * 4 + 0x21] = aiStack_a0[iVar2 * 4 + 1];
        aiStack_230[iVar2 * 4 + 0x22] = aiStack_a0[iVar2 * 4 + 2];
        aiStack_230[iVar2 * 4 + 0x23] = 0x3f800000;
      }
      sceVu0RotTransPersN(aiStack_230,aiStack_230 + 0x40,aiStack_230 + 0x20,8,0);
      for (iVar2 = 0; iVar2 < 8; iVar2 = iVar2 + 1) {
        fVar5 = (float)aiStack_230[iVar2 * 4] / 16.0;
        fVar6 = fVar5;
        if (fStack_b0 <= fVar5) {
          fVar6 = fStack_b0;
        }
        fStack_b0 = fVar6;
        if (fVar5 <= fStack_ac) {
          fVar5 = fStack_ac;
        }
        fStack_ac = fVar5;
        fStack_14 = (float)aiStack_230[iVar2 * 4 + 1] / 16.0;
        fVar6 = fStack_14;
        if (fStack_a8 <= fStack_14) {
          fVar6 = fStack_a8;
        }
        fStack_a8 = fVar6;
        fStack_a4 = fStack_a4 + (float)aiStack_230[iVar2 * 4 + 2] / 16.0;
      }
    }
    fStack_b0 = (fStack_b0 + fStack_ac) / 2.0;
    fStack_a8 = fStack_a8 - 4.0;
    fStack_a4 = fStack_a4 /
                ((float)*(int *)(*(int *)(iGpffff86b4 +
                                          (*(short *)(iStack_10 + 0x56) * 0x50 -
                                          (int)*(short *)(iStack_10 + 0x56)) * 0x10 + 0x534) + 8) *
                8.0);
    if (-1 < (long)((ulong)*(byte *)(iStack_10 + 0x54) << 0x3e)) {
      Create__6CursorFUcUcUcUc(iStack_10 + 0x58,*(undefined1 *)(iStack_10 + 0x154),
                      *(undefined1 *)(iStack_10 + 0x155),*(undefined1 *)(iStack_10 + 0x156),
                      *(undefined1 *)(iStack_10 + 0x157));
    }
    *(byte *)(iStack_10 + 0x54) = *(byte *)(iStack_10 + 0x54) & 0xfd | 2;
    if ((*(byte *)(iStack_10 + 0x54) & 1) == 0) {
      AddPriority__12MenuObjTableFP7MenuObj(iStack_10 + 0x38,iStack_10 + 0x58);
    }
    *(byte *)(iStack_10 + 0x54) = *(byte *)(iStack_10 + 0x54) & 0xfe | 1;
    *(ushort *)(iStack_10 + 0x10a) =
         *(ushort *)(iStack_10 + 0x10a) & 0xfc3f | (*(byte *)(iStack_10 + 0x158) & 0xf) << 6;
    uVar1 = (ulong)*(byte *)(iStack_10 + 0x109) & 0xfffffffffffffffd | 2;
    *(char *)(iStack_10 + 0x109) = (char)uVar1;
    *(byte *)(iStack_10 + 0x108) =
         *(byte *)(iStack_10 + 0x108) & 0xfd | (byte)((uint)((uVar1 << 0x3e) >> 0x3f) << 1);
    *(undefined2 *)(iStack_10 + 0x6c) = 0x10;
    if (((fStack_b0 < 0.0) || (4096.0 <= fStack_b0)) ||
       ((fStack_a8 < 0.0 || ((4096.0 <= fStack_a8 || (fStack_a4 < 0.0)))))) {
      *(byte *)(iStack_10 + 0x6a) = *(byte *)(iStack_10 + 0x6a) & 0xfe;
    }
    else {
      SetTarget__6CursorFff(fStack_b0 - 1792.0,fStack_a8 - 1824.0,iStack_10 + 0x58);
      *(byte *)(iStack_10 + 0x6a) = *(byte *)(iStack_10 + 0x6a) & 0xfe | 1;
    }
    QuickMove__6CursorFv(iStack_10 + 0x58);
  }
  Polling__10MenuRenderFv(iStack_10 + 0xc);
  return 0;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005d8c10  @32@Polling__8BCursoleFv
 * C++: @32@Polling__8BCursoleFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
undefined8 _32_Polling__8BCursoleFv(int param_1)

{
  float in_zero_hi;
  ulong uVar1;
  int iVar2;
  int iVar3;
  undefined8 *puVar4;
  float fVar5;
  float fVar6;
  int aiStack_230 [80];
  int aiStack_f0 [7];
  undefined4 uStack_d4;
  undefined4 uStack_d0;
  undefined4 uStack_cc;
  undefined4 uStack_c8;
  undefined4 uStack_c4;
  undefined4 uStack_c0;
  undefined4 uStack_bc;
  undefined4 uStack_b8;
  undefined4 uStack_b4;
  float fStack_b0;
  float fStack_ac;
  float fStack_a8;
  float fStack_a4;
  int aiStack_a0 [34];
  float fStack_18;
  float fStack_14;
  int iStack_10;
  
  iStack_10 = param_1 + -0x20;
  if ((long)((ulong)*(byte *)(param_1 + 0x34) << 0x3d) < 0) {
    fStack_ac = in_zero_hi;
    iVar3 = GetTimer__7SysToolFv();
    fStack_18 = (float)(uint)(iVar3 - *(int *)(iStack_10 + 0x170)) * 0.001;
    *(int *)(iStack_10 + 0x170) = iVar3;
    *(float *)(iStack_10 + 0x174) = *(float *)(iStack_10 + 0x174) + fStack_18 * 6.2831855;
    if (3.1415927 <= *(float *)(iStack_10 + 0x174)) {
      *(float *)(iStack_10 + 0x174) = *(float *)(iStack_10 + 0x174) - 6.2831855;
    }
    if (*(char *)(iStack_10 + 0x156) == '\x01') {
      fStack_b0 = *(float *)(iStack_10 + 0x160) + 1792.0;
      fVar6 = (float)sinf(*(undefined4 *)(iStack_10 + 0x174));
      fStack_a8 = *(float *)(iStack_10 + 0x164) + 1824.0 + fVar6 * 8.0;
    }
    else if (*(char *)(iStack_10 + 0x156) == '\x02') {
      fStack_b0 = *(float *)(iStack_10 + 0x160) + 1792.0;
      fVar6 = (float)sinf(*(undefined4 *)(iStack_10 + 0x174));
      fStack_a8 = (*(float *)(iStack_10 + 0x164) + 1824.0) - fVar6 * 8.0;
    }
    else if (*(char *)(iStack_10 + 0x156) == '\x04') {
      fVar6 = (float)sinf(*(undefined4 *)(iStack_10 + 0x174));
      fStack_b0 = *(float *)(iStack_10 + 0x160) + 1792.0 + fVar6 * 8.0;
      fStack_a8 = *(float *)(iStack_10 + 0x164) + 1824.0;
    }
    else {
      fVar6 = (float)sinf(*(undefined4 *)(iStack_10 + 0x174));
      fStack_b0 = (*(float *)(iStack_10 + 0x160) + 1792.0) - fVar6 * 8.0;
      fStack_a8 = *(float *)(iStack_10 + 0x164) + 1824.0;
    }
    fStack_a4 = 0.0;
    if (-1 < (long)((ulong)*(byte *)(iStack_10 + 0x54) << 0x3e)) {
      Create__6CursorFUcUcUcUc(iStack_10 + 0x58,*(undefined1 *)(iStack_10 + 0x154),
                      *(undefined1 *)(iStack_10 + 0x155),*(undefined1 *)(iStack_10 + 0x156),
                      *(undefined1 *)(iStack_10 + 0x157));
    }
    if ((*(byte *)(iStack_10 + 0x54) & 1) == 0) {
      AddPriority__12MenuObjTableFP7MenuObj(iStack_10 + 0x38,iStack_10 + 0x58);
    }
    *(byte *)(iStack_10 + 0x54) = *(byte *)(iStack_10 + 0x54) & 0xfe | 1;
    *(ushort *)(iStack_10 + 0x10a) =
         *(ushort *)(iStack_10 + 0x10a) & 0xfc3f | (*(byte *)(iStack_10 + 0x158) & 0xf) << 6;
    uVar1 = (ulong)*(byte *)(iStack_10 + 0x109) & 0xfffffffffffffffd | 2;
    *(char *)(iStack_10 + 0x109) = (char)uVar1;
    *(byte *)(iStack_10 + 0x108) =
         *(byte *)(iStack_10 + 0x108) & 0xfd | (byte)((uint)((uVar1 << 0x3e) >> 0x3f) << 1);
    *(undefined2 *)(iStack_10 + 0x6c) = 0x10;
    if ((((fStack_b0 < 0.0) || (4096.0 <= fStack_b0)) || (fStack_a8 < 0.0)) ||
       ((4096.0 <= fStack_a8 || (fStack_a4 < 0.0)))) {
      *(byte *)(iStack_10 + 0x6a) = *(byte *)(iStack_10 + 0x6a) & 0xfe;
    }
    else {
      SetTarget__6CursorFff(fStack_b0 - 1792.0,fStack_a8 - 1824.0,iStack_10 + 0x58);
      *(byte *)(iStack_10 + 0x6a) = *(byte *)(iStack_10 + 0x6a) & 0xfe | 1;
    }
    if (-1 < (long)((ulong)*(byte *)(iStack_10 + 0x54) << 0x3e)) {
      QuickMove__6CursorFv(iStack_10 + 0x58);
    }
    *(byte *)(iStack_10 + 0x54) = *(byte *)(iStack_10 + 0x54) & 0xfd | 2;
  }
  else {
    GetViewScreenMatrix__9GsxCameraFv(aiStack_f0,uGpffff8598);
    for (iVar3 = 0; iVar3 < 4; iVar3 = iVar3 + 1) {
      aiStack_230[iVar3 * 4 + 0x40] = aiStack_f0[iVar3 * 4];
      aiStack_230[iVar3 * 4 + 0x41] = aiStack_f0[iVar3 * 4 + 1];
      aiStack_230[iVar3 * 4 + 0x42] = aiStack_f0[iVar3 * 4 + 2];
      aiStack_230[iVar3 * 4 + 0x43] = aiStack_f0[iVar3 * 4 + 3];
    }
    fStack_b0 = 65535.0;
    fStack_ac = -65535.0;
    fStack_a8 = 65535.0;
    fStack_a4 = 0.0;
    for (iVar3 = 0;
        iVar3 < *(int *)(*(int *)(iGpffff86b4 +
                                  (*(short *)(iStack_10 + 0x56) * 0x50 -
                                  (int)*(short *)(iStack_10 + 0x56)) * 0x10 + 0x534) + 8);
        iVar3 = iVar3 + 1) {
      puVar4 = (undefined8 *)
               (*(int *)(*(int *)(iGpffff86b4 +
                                  (*(short *)(iStack_10 + 0x56) * 0x50 -
                                  (int)*(short *)(iStack_10 + 0x56)) * 0x10 + 0x144) + 0x30) +
                (uint)*(byte *)(*(int *)(*(int *)(iGpffff86b4 +
                                                  (*(short *)(iStack_10 + 0x56) * 0x50 -
                                                  (int)*(short *)(iStack_10 + 0x56)) * 0x10 + 0x144)
                                        + 0xe4) +
                               *(short *)(iGpffff86b4 +
                                          (*(short *)(iStack_10 + 0x56) * 0x50 -
                                          (int)*(short *)(iStack_10 + 0x56)) * 0x10 + iVar3 * 2 +
                                         0x53c) * 0x110) * 0x1f0 + (bGpffff8340 & 1) * 0x40);
      aiStack_f0[2] = *(int *)(puVar4 + 1);
      aiStack_f0[3] = *(undefined4 *)((int)puVar4 + 0xc);
      aiStack_f0[0] = (int)*puVar4;
      aiStack_f0[1] = (int)((ulong)*puVar4 >> 0x20);
      aiStack_f0[4] = *(int *)(puVar4 + 2);
      aiStack_f0[5] = *(undefined4 *)((int)puVar4 + 0x14);
      aiStack_f0[6] = *(int *)(puVar4 + 3);
      uStack_d4 = *(undefined4 *)((int)puVar4 + 0x1c);
      uStack_d0 = *(undefined4 *)(puVar4 + 4);
      uStack_cc = *(undefined4 *)((int)puVar4 + 0x24);
      uStack_c8 = *(undefined4 *)(puVar4 + 5);
      uStack_c4 = *(undefined4 *)((int)puVar4 + 0x2c);
      uStack_c0 = *(undefined4 *)(puVar4 + 6);
      uStack_bc = *(undefined4 *)((int)puVar4 + 0x34);
      uStack_b8 = *(undefined4 *)(puVar4 + 7);
      uStack_b4 = *(undefined4 *)((int)puVar4 + 0x3c);
      RotTransVector(aiStack_a0,
                      *(int *)(*(int *)(iGpffff86b4 +
                                        (*(short *)(iStack_10 + 0x56) * 0x50 -
                                        (int)*(short *)(iStack_10 + 0x56)) * 0x10 + 0x144) + 0xe4) +
                      *(short *)(iGpffff86b4 +
                                 (*(short *)(iStack_10 + 0x56) * 0x50 -
                                 (int)*(short *)(iStack_10 + 0x56)) * 0x10 + iVar3 * 2 + 0x53c) *
                      0x110 + 0x10,aiStack_f0,8);
      for (iVar2 = 0; iVar2 < 8; iVar2 = iVar2 + 1) {
        aiStack_230[iVar2 * 4 + 0x20] = aiStack_a0[iVar2 * 4];
        aiStack_230[iVar2 * 4 + 0x21] = aiStack_a0[iVar2 * 4 + 1];
        aiStack_230[iVar2 * 4 + 0x22] = aiStack_a0[iVar2 * 4 + 2];
        aiStack_230[iVar2 * 4 + 0x23] = 0x3f800000;
      }
      sceVu0RotTransPersN(aiStack_230,aiStack_230 + 0x40,aiStack_230 + 0x20,8,0);
      for (iVar2 = 0; iVar2 < 8; iVar2 = iVar2 + 1) {
        fVar5 = (float)aiStack_230[iVar2 * 4] / 16.0;
        fVar6 = fVar5;
        if (fStack_b0 <= fVar5) {
          fVar6 = fStack_b0;
        }
        fStack_b0 = fVar6;
        if (fVar5 <= fStack_ac) {
          fVar5 = fStack_ac;
        }
        fStack_ac = fVar5;
        fStack_14 = (float)aiStack_230[iVar2 * 4 + 1] / 16.0;
        fVar6 = fStack_14;
        if (fStack_a8 <= fStack_14) {
          fVar6 = fStack_a8;
        }
        fStack_a8 = fVar6;
        fStack_a4 = fStack_a4 + (float)aiStack_230[iVar2 * 4 + 2] / 16.0;
      }
    }
    fStack_b0 = (fStack_b0 + fStack_ac) / 2.0;
    fStack_a8 = fStack_a8 - 4.0;
    fStack_a4 = fStack_a4 /
                ((float)*(int *)(*(int *)(iGpffff86b4 +
                                          (*(short *)(iStack_10 + 0x56) * 0x50 -
                                          (int)*(short *)(iStack_10 + 0x56)) * 0x10 + 0x534) + 8) *
                8.0);
    if (-1 < (long)((ulong)*(byte *)(iStack_10 + 0x54) << 0x3e)) {
      Create__6CursorFUcUcUcUc(iStack_10 + 0x58,*(undefined1 *)(iStack_10 + 0x154),
                      *(undefined1 *)(iStack_10 + 0x155),*(undefined1 *)(iStack_10 + 0x156),
                      *(undefined1 *)(iStack_10 + 0x157));
    }
    *(byte *)(iStack_10 + 0x54) = *(byte *)(iStack_10 + 0x54) & 0xfd | 2;
    if ((*(byte *)(iStack_10 + 0x54) & 1) == 0) {
      AddPriority__12MenuObjTableFP7MenuObj(iStack_10 + 0x38,iStack_10 + 0x58);
    }
    *(byte *)(iStack_10 + 0x54) = *(byte *)(iStack_10 + 0x54) & 0xfe | 1;
    *(ushort *)(iStack_10 + 0x10a) =
         *(ushort *)(iStack_10 + 0x10a) & 0xfc3f | (*(byte *)(iStack_10 + 0x158) & 0xf) << 6;
    uVar1 = (ulong)*(byte *)(iStack_10 + 0x109) & 0xfffffffffffffffd | 2;
    *(char *)(iStack_10 + 0x109) = (char)uVar1;
    *(byte *)(iStack_10 + 0x108) =
         *(byte *)(iStack_10 + 0x108) & 0xfd | (byte)((uint)((uVar1 << 0x3e) >> 0x3f) << 1);
    *(undefined2 *)(iStack_10 + 0x6c) = 0x10;
    if (((fStack_b0 < 0.0) || (4096.0 <= fStack_b0)) ||
       ((fStack_a8 < 0.0 || ((4096.0 <= fStack_a8 || (fStack_a4 < 0.0)))))) {
      *(byte *)(iStack_10 + 0x6a) = *(byte *)(iStack_10 + 0x6a) & 0xfe;
    }
    else {
      SetTarget__6CursorFff(fStack_b0 - 1792.0,fStack_a8 - 1824.0,iStack_10 + 0x58);
      *(byte *)(iStack_10 + 0x6a) = *(byte *)(iStack_10 + 0x6a) & 0xfe | 1;
    }
    QuickMove__6CursorFv(iStack_10 + 0x58);
  }
  Polling__10MenuRenderFv(iStack_10 + 0xc);
  return 0;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005d8c20  @32@__dt__8BCursoleFv
 * C++: @32@__dt__8BCursoleFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int _32___dt__8BCursoleFv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x20;
  if (iVar1 != 0) {
    *(undefined4 *)(param_1 + -0x18) = 0x40a7a0;
    *(undefined4 *)(param_1 + -4) = 0x40a7b0;
    *(undefined4 *)(param_1 + 0x14) = 0x40a7c0;
    *(undefined4 *)(param_1 + 0x18) = 0x40a7d0;
    if ((long)((ulong)*(byte *)(param_1 + 0x34) << 0x3e) < 0) {
      Release__7MenuObjFv(param_1 + 0x38);
    }
    __dt__6CursorFv(param_1 + 0x38,0xffffffffffffffff);
    __dt__10MenuRenderFv(param_1 + -0x14,0);
    if (iVar1 != 0) {
      *(undefined4 *)(param_1 + -0x18) = 0x4049f0;
    }
    if (0 < param_2) {
      __dl__FPv(iVar1);
    }
  }
  return iVar1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005d8c30  @56@__dt__8BCursoleFv
 * C++: @56@__dt__8BCursoleFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
undefined4 * _56___dt__8BCursoleFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -0xe;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-0xc] = 0x40a7a0;
    param_1[-7] = 0x40a7b0;
    param_1[-1] = 0x40a7c0;
    *param_1 = 0x40a7d0;
    if ((long)((ulong)*(byte *)(param_1 + 7) << 0x3e) < 0) {
      Release__7MenuObjFv(param_1 + 8);
    }
    __dt__6CursorFv(param_1 + 8,0xffffffffffffffff);
    __dt__10MenuRenderFv(param_1 + -0xb,0);
    if (puVar1 != (undefined4 *)0x0) {
      param_1[-0xc] = 0x4049f0;
    }
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005d8c40  @12@Polling__8BCursoleFv
 * C++: @12@Polling__8BCursoleFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
undefined8 _12_Polling__8BCursoleFv(int param_1)

{
  float in_zero_hi;
  ulong uVar1;
  int iVar2;
  int iVar3;
  undefined8 *puVar4;
  float fVar5;
  float fVar6;
  int aiStack_230 [80];
  int aiStack_f0 [7];
  undefined4 uStack_d4;
  undefined4 uStack_d0;
  undefined4 uStack_cc;
  undefined4 uStack_c8;
  undefined4 uStack_c4;
  undefined4 uStack_c0;
  undefined4 uStack_bc;
  undefined4 uStack_b8;
  undefined4 uStack_b4;
  float fStack_b0;
  float fStack_ac;
  float fStack_a8;
  float fStack_a4;
  int aiStack_a0 [34];
  float fStack_18;
  float fStack_14;
  int iStack_10;
  
  iStack_10 = param_1 + -0xc;
  if ((long)((ulong)*(byte *)(param_1 + 0x48) << 0x3d) < 0) {
    fStack_ac = in_zero_hi;
    iVar3 = GetTimer__7SysToolFv();
    fStack_18 = (float)(uint)(iVar3 - *(int *)(iStack_10 + 0x170)) * 0.001;
    *(int *)(iStack_10 + 0x170) = iVar3;
    *(float *)(iStack_10 + 0x174) = *(float *)(iStack_10 + 0x174) + fStack_18 * 6.2831855;
    if (3.1415927 <= *(float *)(iStack_10 + 0x174)) {
      *(float *)(iStack_10 + 0x174) = *(float *)(iStack_10 + 0x174) - 6.2831855;
    }
    if (*(char *)(iStack_10 + 0x156) == '\x01') {
      fStack_b0 = *(float *)(iStack_10 + 0x160) + 1792.0;
      fVar6 = (float)sinf(*(undefined4 *)(iStack_10 + 0x174));
      fStack_a8 = *(float *)(iStack_10 + 0x164) + 1824.0 + fVar6 * 8.0;
    }
    else if (*(char *)(iStack_10 + 0x156) == '\x02') {
      fStack_b0 = *(float *)(iStack_10 + 0x160) + 1792.0;
      fVar6 = (float)sinf(*(undefined4 *)(iStack_10 + 0x174));
      fStack_a8 = (*(float *)(iStack_10 + 0x164) + 1824.0) - fVar6 * 8.0;
    }
    else if (*(char *)(iStack_10 + 0x156) == '\x04') {
      fVar6 = (float)sinf(*(undefined4 *)(iStack_10 + 0x174));
      fStack_b0 = *(float *)(iStack_10 + 0x160) + 1792.0 + fVar6 * 8.0;
      fStack_a8 = *(float *)(iStack_10 + 0x164) + 1824.0;
    }
    else {
      fVar6 = (float)sinf(*(undefined4 *)(iStack_10 + 0x174));
      fStack_b0 = (*(float *)(iStack_10 + 0x160) + 1792.0) - fVar6 * 8.0;
      fStack_a8 = *(float *)(iStack_10 + 0x164) + 1824.0;
    }
    fStack_a4 = 0.0;
    if (-1 < (long)((ulong)*(byte *)(iStack_10 + 0x54) << 0x3e)) {
      Create__6CursorFUcUcUcUc(iStack_10 + 0x58,*(undefined1 *)(iStack_10 + 0x154),
                      *(undefined1 *)(iStack_10 + 0x155),*(undefined1 *)(iStack_10 + 0x156),
                      *(undefined1 *)(iStack_10 + 0x157));
    }
    if ((*(byte *)(iStack_10 + 0x54) & 1) == 0) {
      AddPriority__12MenuObjTableFP7MenuObj(iStack_10 + 0x38,iStack_10 + 0x58);
    }
    *(byte *)(iStack_10 + 0x54) = *(byte *)(iStack_10 + 0x54) & 0xfe | 1;
    *(ushort *)(iStack_10 + 0x10a) =
         *(ushort *)(iStack_10 + 0x10a) & 0xfc3f | (*(byte *)(iStack_10 + 0x158) & 0xf) << 6;
    uVar1 = (ulong)*(byte *)(iStack_10 + 0x109) & 0xfffffffffffffffd | 2;
    *(char *)(iStack_10 + 0x109) = (char)uVar1;
    *(byte *)(iStack_10 + 0x108) =
         *(byte *)(iStack_10 + 0x108) & 0xfd | (byte)((uint)((uVar1 << 0x3e) >> 0x3f) << 1);
    *(undefined2 *)(iStack_10 + 0x6c) = 0x10;
    if ((((fStack_b0 < 0.0) || (4096.0 <= fStack_b0)) || (fStack_a8 < 0.0)) ||
       ((4096.0 <= fStack_a8 || (fStack_a4 < 0.0)))) {
      *(byte *)(iStack_10 + 0x6a) = *(byte *)(iStack_10 + 0x6a) & 0xfe;
    }
    else {
      SetTarget__6CursorFff(fStack_b0 - 1792.0,fStack_a8 - 1824.0,iStack_10 + 0x58);
      *(byte *)(iStack_10 + 0x6a) = *(byte *)(iStack_10 + 0x6a) & 0xfe | 1;
    }
    if (-1 < (long)((ulong)*(byte *)(iStack_10 + 0x54) << 0x3e)) {
      QuickMove__6CursorFv(iStack_10 + 0x58);
    }
    *(byte *)(iStack_10 + 0x54) = *(byte *)(iStack_10 + 0x54) & 0xfd | 2;
  }
  else {
    GetViewScreenMatrix__9GsxCameraFv(aiStack_f0,uGpffff8598);
    for (iVar3 = 0; iVar3 < 4; iVar3 = iVar3 + 1) {
      aiStack_230[iVar3 * 4 + 0x40] = aiStack_f0[iVar3 * 4];
      aiStack_230[iVar3 * 4 + 0x41] = aiStack_f0[iVar3 * 4 + 1];
      aiStack_230[iVar3 * 4 + 0x42] = aiStack_f0[iVar3 * 4 + 2];
      aiStack_230[iVar3 * 4 + 0x43] = aiStack_f0[iVar3 * 4 + 3];
    }
    fStack_b0 = 65535.0;
    fStack_ac = -65535.0;
    fStack_a8 = 65535.0;
    fStack_a4 = 0.0;
    for (iVar3 = 0;
        iVar3 < *(int *)(*(int *)(iGpffff86b4 +
                                  (*(short *)(iStack_10 + 0x56) * 0x50 -
                                  (int)*(short *)(iStack_10 + 0x56)) * 0x10 + 0x534) + 8);
        iVar3 = iVar3 + 1) {
      puVar4 = (undefined8 *)
               (*(int *)(*(int *)(iGpffff86b4 +
                                  (*(short *)(iStack_10 + 0x56) * 0x50 -
                                  (int)*(short *)(iStack_10 + 0x56)) * 0x10 + 0x144) + 0x30) +
                (uint)*(byte *)(*(int *)(*(int *)(iGpffff86b4 +
                                                  (*(short *)(iStack_10 + 0x56) * 0x50 -
                                                  (int)*(short *)(iStack_10 + 0x56)) * 0x10 + 0x144)
                                        + 0xe4) +
                               *(short *)(iGpffff86b4 +
                                          (*(short *)(iStack_10 + 0x56) * 0x50 -
                                          (int)*(short *)(iStack_10 + 0x56)) * 0x10 + iVar3 * 2 +
                                         0x53c) * 0x110) * 0x1f0 + (bGpffff8340 & 1) * 0x40);
      aiStack_f0[2] = *(int *)(puVar4 + 1);
      aiStack_f0[3] = *(undefined4 *)((int)puVar4 + 0xc);
      aiStack_f0[0] = (int)*puVar4;
      aiStack_f0[1] = (int)((ulong)*puVar4 >> 0x20);
      aiStack_f0[4] = *(int *)(puVar4 + 2);
      aiStack_f0[5] = *(undefined4 *)((int)puVar4 + 0x14);
      aiStack_f0[6] = *(int *)(puVar4 + 3);
      uStack_d4 = *(undefined4 *)((int)puVar4 + 0x1c);
      uStack_d0 = *(undefined4 *)(puVar4 + 4);
      uStack_cc = *(undefined4 *)((int)puVar4 + 0x24);
      uStack_c8 = *(undefined4 *)(puVar4 + 5);
      uStack_c4 = *(undefined4 *)((int)puVar4 + 0x2c);
      uStack_c0 = *(undefined4 *)(puVar4 + 6);
      uStack_bc = *(undefined4 *)((int)puVar4 + 0x34);
      uStack_b8 = *(undefined4 *)(puVar4 + 7);
      uStack_b4 = *(undefined4 *)((int)puVar4 + 0x3c);
      RotTransVector(aiStack_a0,
                      *(int *)(*(int *)(iGpffff86b4 +
                                        (*(short *)(iStack_10 + 0x56) * 0x50 -
                                        (int)*(short *)(iStack_10 + 0x56)) * 0x10 + 0x144) + 0xe4) +
                      *(short *)(iGpffff86b4 +
                                 (*(short *)(iStack_10 + 0x56) * 0x50 -
                                 (int)*(short *)(iStack_10 + 0x56)) * 0x10 + iVar3 * 2 + 0x53c) *
                      0x110 + 0x10,aiStack_f0,8);
      for (iVar2 = 0; iVar2 < 8; iVar2 = iVar2 + 1) {
        aiStack_230[iVar2 * 4 + 0x20] = aiStack_a0[iVar2 * 4];
        aiStack_230[iVar2 * 4 + 0x21] = aiStack_a0[iVar2 * 4 + 1];
        aiStack_230[iVar2 * 4 + 0x22] = aiStack_a0[iVar2 * 4 + 2];
        aiStack_230[iVar2 * 4 + 0x23] = 0x3f800000;
      }
      sceVu0RotTransPersN(aiStack_230,aiStack_230 + 0x40,aiStack_230 + 0x20,8,0);
      for (iVar2 = 0; iVar2 < 8; iVar2 = iVar2 + 1) {
        fVar5 = (float)aiStack_230[iVar2 * 4] / 16.0;
        fVar6 = fVar5;
        if (fStack_b0 <= fVar5) {
          fVar6 = fStack_b0;
        }
        fStack_b0 = fVar6;
        if (fVar5 <= fStack_ac) {
          fVar5 = fStack_ac;
        }
        fStack_ac = fVar5;
        fStack_14 = (float)aiStack_230[iVar2 * 4 + 1] / 16.0;
        fVar6 = fStack_14;
        if (fStack_a8 <= fStack_14) {
          fVar6 = fStack_a8;
        }
        fStack_a8 = fVar6;
        fStack_a4 = fStack_a4 + (float)aiStack_230[iVar2 * 4 + 2] / 16.0;
      }
    }
    fStack_b0 = (fStack_b0 + fStack_ac) / 2.0;
    fStack_a8 = fStack_a8 - 4.0;
    fStack_a4 = fStack_a4 /
                ((float)*(int *)(*(int *)(iGpffff86b4 +
                                          (*(short *)(iStack_10 + 0x56) * 0x50 -
                                          (int)*(short *)(iStack_10 + 0x56)) * 0x10 + 0x534) + 8) *
                8.0);
    if (-1 < (long)((ulong)*(byte *)(iStack_10 + 0x54) << 0x3e)) {
      Create__6CursorFUcUcUcUc(iStack_10 + 0x58,*(undefined1 *)(iStack_10 + 0x154),
                      *(undefined1 *)(iStack_10 + 0x155),*(undefined1 *)(iStack_10 + 0x156),
                      *(undefined1 *)(iStack_10 + 0x157));
    }
    *(byte *)(iStack_10 + 0x54) = *(byte *)(iStack_10 + 0x54) & 0xfd | 2;
    if ((*(byte *)(iStack_10 + 0x54) & 1) == 0) {
      AddPriority__12MenuObjTableFP7MenuObj(iStack_10 + 0x38,iStack_10 + 0x58);
    }
    *(byte *)(iStack_10 + 0x54) = *(byte *)(iStack_10 + 0x54) & 0xfe | 1;
    *(ushort *)(iStack_10 + 0x10a) =
         *(ushort *)(iStack_10 + 0x10a) & 0xfc3f | (*(byte *)(iStack_10 + 0x158) & 0xf) << 6;
    uVar1 = (ulong)*(byte *)(iStack_10 + 0x109) & 0xfffffffffffffffd | 2;
    *(char *)(iStack_10 + 0x109) = (char)uVar1;
    *(byte *)(iStack_10 + 0x108) =
         *(byte *)(iStack_10 + 0x108) & 0xfd | (byte)((uint)((uVar1 << 0x3e) >> 0x3f) << 1);
    *(undefined2 *)(iStack_10 + 0x6c) = 0x10;
    if (((fStack_b0 < 0.0) || (4096.0 <= fStack_b0)) ||
       ((fStack_a8 < 0.0 || ((4096.0 <= fStack_a8 || (fStack_a4 < 0.0)))))) {
      *(byte *)(iStack_10 + 0x6a) = *(byte *)(iStack_10 + 0x6a) & 0xfe;
    }
    else {
      SetTarget__6CursorFff(fStack_b0 - 1792.0,fStack_a8 - 1824.0,iStack_10 + 0x58);
      *(byte *)(iStack_10 + 0x6a) = *(byte *)(iStack_10 + 0x6a) & 0xfe | 1;
    }
    QuickMove__6CursorFv(iStack_10 + 0x58);
  }
  Polling__10MenuRenderFv(iStack_10 + 0xc);
  return 0;
}

/* ---------------------------------------------------------------------------
 * JP: 0x005d8c50  @12@__dt__8BCursoleFv
 * C++: @12@__dt__8BCursoleFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int _12___dt__8BCursoleFv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0xc;
  if (iVar1 != 0) {
    *(undefined4 *)(param_1 + -4) = 0x40a7a0;
    *(undefined4 *)(param_1 + 0x10) = 0x40a7b0;
    *(undefined4 *)(param_1 + 0x28) = 0x40a7c0;
    *(undefined4 *)(param_1 + 0x2c) = 0x40a7d0;
    if ((long)((ulong)*(byte *)(param_1 + 0x48) << 0x3e) < 0) {
      Release__7MenuObjFv(param_1 + 0x4c);
    }
    __dt__6CursorFv(param_1 + 0x4c,0xffffffffffffffff);
    __dt__10MenuRenderFv(param_1,0);
    if (iVar1 != 0) {
      *(undefined4 *)(param_1 + -4) = 0x4049f0;
    }
    if (0 < param_2) {
      __dl__FPv(iVar1);
    }
  }
  return iVar1;
}

