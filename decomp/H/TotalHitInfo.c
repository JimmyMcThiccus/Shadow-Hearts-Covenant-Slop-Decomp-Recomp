/* decomp/H/TotalHitInfo.c — cleaned Ghidra output (SH2JP_BATTLE.BIN, JP Furokuban, base 0x00430a00).
 * 10 function(s). Types: see types.h. Names/gp globals resolved from symbols/SLPM_602.19.syms. */
#include "types.h"

/* ---------------------------------------------------------------------------
 * JP: 0x004f5ec0  __ct__12TotalHitInfoFii7FVector
 * C++: TotalHitInfo::__ct(int, int, FVector)
 * size: 0x180 bytes
 * --------------------------------------------------------------------------- */
undefined8
__ct__12TotalHitInfoFii7FVector
          (undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 *param_4)

{
  undefined8 uVar1;
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  
  __ct__6BtlEffFii(param_1,param_2,param_3);
  iVar5 = (int)param_1;
  *(undefined4 *)(iVar5 + 0x14) = 0x40a4d0;
  *(undefined4 *)(iVar5 + 0x28) = 0x40a4e0;
  *(undefined4 *)(iVar5 + 0x34) = 0x40a4f0;
  *(undefined4 *)(iVar5 + 0x70) = in_zero_lo;
  *(undefined4 *)(iVar5 + 0x74) = in_zero_hi;
  *(undefined4 *)(iVar5 + 0x78) = in_zero_udw;
  *(undefined4 *)(iVar5 + 0x7c) = in_register_0000000c;
  *(undefined4 *)(iVar5 + 0x310) = in_zero_lo;
  *(undefined4 *)(iVar5 + 0x314) = in_zero_hi;
  *(undefined4 *)(iVar5 + 0x318) = in_zero_udw;
  *(undefined4 *)(iVar5 + 0x31c) = in_register_0000000c;
  *(int *)(iVar5 + 0x44) = (int)param_2;
  *(int *)(iVar5 + 0x48) = (int)param_3;
  *(undefined4 *)(iVar5 + 0x4c) = 0xe;
  *(undefined4 *)(iVar5 + 0x40) = 0;
  *(undefined2 *)(iVar5 + 0x5c) = 0;
  *(undefined2 *)(iVar5 + 0x5e) = 0;
  *(undefined4 *)(iVar5 + 0x60) = 0;
  uVar1 = *param_4;
  uVar2 = *(undefined4 *)(param_4 + 1);
  uVar3 = *(undefined4 *)((int)param_4 + 0xc);
  *(int *)(iVar5 + 0x70) = (int)uVar1;
  *(int *)(iVar5 + 0x74) = (int)((ulong)uVar1 >> 0x20);
  *(undefined4 *)(iVar5 + 0x78) = uVar2;
  *(undefined4 *)(iVar5 + 0x7c) = uVar3;
  *(undefined4 *)(iVar5 + 0x84) = 0x3f400000;
  *(undefined4 *)(iVar5 + 0x80) = 0x3f400000;
  *(undefined4 *)(iVar5 + 0x1c) = 0;
  *(undefined4 *)(iVar5 + 0x18) = 0;
  *(undefined4 *)(iVar5 + 0x88) = 0;
  *(undefined4 *)(iVar5 + 0x88) = 0;
  *(undefined4 *)(iVar5 + 0x54) = 0;
  for (iVar4 = 0; iVar4 < 0x10; iVar4 = iVar4 + 1) {
    *(undefined1 *)(iVar5 + iVar4 * 0x28 + 0x90) = 0;
    *(undefined1 *)(iVar5 + iVar4 * 0x28 + 0x94) = 0;
    *(undefined1 *)(iVar5 + iVar4 * 0x28 + 0xa4) = 0;
  }
  Entry__7CPollerFP7CPolObjib(iGpffff858c + 0x48,param_1,0x80,0);
  BtlEffEntry__7CBattleFiP6BtlEff(uGpffff86b4,0xffffffffffffffff,param_1);
  *(int *)(g_86bc + (int)param_2 * 4 + 0x58) = iVar5;
  return param_1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x004f6120  __dt__12TotalHitInfoFv
 * C++: TotalHitInfo::__dt()
 * size: 0x154 bytes
 * --------------------------------------------------------------------------- */
int __dt__12TotalHitInfoFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x14) = 0x40a4d0;
    *(undefined4 *)(param_1 + 0x28) = 0x40a4e0;
    *(undefined4 *)(param_1 + 0x34) = 0x40a4f0;
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
 * JP: 0x004f6280  Destruct__12TotalHitInfoFv
 * C++: TotalHitInfo::Destruct()
 * size: 0x70 bytes
 * --------------------------------------------------------------------------- */
void Destruct__12TotalHitInfoFv(int param_1)

{
  BtlEffRelease__7CBattleFiP6BtlEff(uGpffff86b4,0xffffffffffffffff,param_1);
  ReleaseDDisp__11CBtlPAfter2Fi(uGpffff86bc,*(undefined4 *)(param_1 + 0x44));
  Dispose__7CPollerFP7CPolObj(iGpffff858c + 0x48,param_1);
  (**(code **)(*(int *)(param_1 + 0x34) + 0xc))();
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x004f62f0  Polling__12TotalHitInfoFv
 * C++: TotalHitInfo::Polling()
 * size: 0x6c4 bytes
 * --------------------------------------------------------------------------- */
undefined4 Polling__12TotalHitInfoFv(int param_1)

{
  bool bVar1;
  float fStack_1c;
  float fStack_18;
  float fStack_14;
  
  fStack_1c = *(float *)(iGpffff86b4 + 0x38);
  if ((*(byte *)(iGpffff86b4 + 0x24) & 1) != 0) {
    fStack_1c = 0.0;
  }
  if (*(short *)(param_1 + 0x5c) == 1) {
    fStack_14 = 0.75;
    if ((*(uint *)(*(int *)(iGpffff86b4 + 0x436c) + 100) & 1 << (*(uint *)(param_1 + 0x48) & 0x1f))
        != 0) {
      fStack_14 = 0.90000004;
    }
    *(float *)(param_1 + 0x80) =
         *(float *)(param_1 + 0x80) + (fStack_14 - *(float *)(param_1 + 0x80)) * fStack_1c * 10.0;
    *(float *)(param_1 + 0x84) =
         *(float *)(param_1 + 0x84) + (0.0 - *(float *)(param_1 + 0x84)) * fStack_1c * 10.0;
    if (*(float *)(param_1 + 0x84) <= 0.01) {
      BtlEffRelease__7CBattleFiP6BtlEff(iGpffff86b4,0xffffffffffffffff,param_1);
      ReleaseDDisp__11CBtlPAfter2Fi(uGpffff86bc,*(undefined4 *)(param_1 + 0x44));
      (**(code **)(*(int *)(param_1 + 0x34) + 0xc))();
      return 1;
    }
  }
  else if (*(short *)(param_1 + 0x5c) == 0) {
    fStack_18 = 0.75;
    fStack_14 = 0.75;
    if ((*(uint *)(*(int *)(iGpffff86b4 + 0x436c) + 100) &
        3 << ((*(uint *)(param_1 + 0x48) & 0xf) << 1)) != 0) {
      fStack_14 = 0.90000004;
      fStack_18 = 0.90000004;
    }
    *(float *)(param_1 + 0x80) =
         *(float *)(param_1 + 0x80) + (fStack_14 - *(float *)(param_1 + 0x80)) * fStack_1c * 10.0;
    *(float *)(param_1 + 0x84) =
         *(float *)(param_1 + 0x84) + (fStack_18 - *(float *)(param_1 + 0x84)) * fStack_1c * 10.0;
    *(float *)(param_1 + 0x60) = *(float *)(param_1 + 0x60) + fStack_1c;
    bVar1 = *(float *)(param_1 + 0x60) < 4.0;
    if ((*(char *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0xb8) == '$') &&
       (*(char *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0xb9) < '\x02')) {
      bVar1 = true;
    }
    if ((*(char *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0xb8) == '%') &&
       (*(char *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0xb9) < '\x02')) {
      bVar1 = true;
    }
    if ((((*(char *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0xb8) != '$') &&
         (*(char *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0xb8) != '%')) &&
        ('\x15' < *(char *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0xb8))) &&
       (*(char *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0xb8) < '\'')) {
      bVar1 = true;
    }
    if ((((*(byte *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0xb4) & 1) == 0) &&
        (*(short *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x124) < 1)) &&
       ((*(char *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0xb8) == '&' &&
        (*(char *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0xb9) != '\0')))) {
      bVar1 = false;
    }
    if ((((*(byte *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0xb4) & 1) != 0) &&
        ((long)((ulong)*(byte *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0xb4) << 0x3c) < 0
        )) && (*(short *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x192) == -1)) {
      bVar1 = false;
    }
    if (!bVar1) {
      *(undefined2 *)(param_1 + 0x5c) = 1;
    }
  }
  return 0;
}

/* ---------------------------------------------------------------------------
 * JP: 0x004f69c0  MakePacket__12TotalHitInfoFv
 * C++: TotalHitInfo::MakePacket()
 * size: 0x42dc bytes
 * --------------------------------------------------------------------------- */
void MakePacket__12TotalHitInfoFv(int param_1)

{
  bool bVar1;
  char cVar2;
  short sVar3;
  ushort uVar4;
  ushort uVar5;
  ushort uVar6;
  undefined4 *puVar7;
  undefined1 auVar8 [16];
  undefined1 in_zero_qw [16];
  undefined4 uVar9;
  uint uVar10;
  uint uVar11;
  undefined8 uVar12;
  undefined4 in_v0_udw;
  undefined4 in_register_0000002c;
  int iVar13;
  int iVar14;
  int iVar15;
  undefined1 auVar16 [16];
  undefined1 auVar17 [16];
  undefined1 auVar18 [16];
  ulong uVar19;
  undefined8 in_a2_udw;
  undefined1 auVar20 [16];
  undefined1 auVar21 [16];
  undefined1 auVar22 [16];
  undefined1 auVar23 [16];
  undefined1 auVar24 [16];
  long lVar25;
  int iVar26;
  int iVar27;
  ulong unaff_s2;
  int iVar28;
  undefined4 in_s3_udw;
  undefined4 in_register_0000013c;
  uint uVar29;
  ulong unaff_s4;
  uint uVar30;
  int iVar31;
  ulong unaff_s6;
  int iVar32;
  ulong unaff_s7;
  float fVar33;
  float fVar34;
  float fVar35;
  float fStack_90;
  int iStack_24;
  float fStack_1c;
  uint uStack_14;
  
  fVar35 = *(float *)(param_1 + 0x74) + 1824.0;
  fStack_90 = *(float *)(param_1 + 0x70) + 1792.0;
  iStack_24 = 0x1f;
  for (iVar26 = 0; iVar26 < 0x10; iVar26 = iVar26 + 1) {
    if ((((*(byte *)(param_1 + iVar26 * 0x28 + 0x90) & 1) != 0) ||
        ((long)((ulong)*(byte *)(param_1 + iVar26 * 0x28 + 0x90) << 0x3e) < 0)) ||
       ((long)((ulong)*(byte *)(param_1 + iVar26 * 0x28 + 0x90) << 0x3d) < 0)) {
      iStack_24 = iStack_24 + 1;
      if ((*(byte *)(param_1 + iVar26 * 0x28 + 0x90) & 1) != 0) {
        iVar14 = strlen(param_1 + iVar26 * 0x28 + 0x94);
        iStack_24 = iStack_24 + iVar14 * 4 + 6;
      }
      if ((long)((ulong)*(byte *)(param_1 + iVar26 * 0x28 + 0x90) << 0x3d) < 0) {
        iStack_24 = iStack_24 + 0x1e;
      }
      if ((long)((ulong)*(byte *)(param_1 + iVar26 * 0x28 + 0x90) << 0x3e) < 0) {
        iVar14 = strlen(param_1 + iVar26 * 0x28 + 0xa4);
        iStack_24 = iStack_24 + iVar14 * 4 + 6;
      }
    }
  }
  bVar1 = (*(byte *)(param_1 + 0x40) & 1) == 0;
  uStack_14 = (uint)bVar1;
  if ((*(int *)(param_1 + uStack_14 * 4 + 0x18) != 0) &&
     ((*(int *)(param_1 + uStack_14 * 4 + 0x88) != iStack_24 ||
      (CONCAT44(*(short *)(param_1 + 0x5c) >> 0xf,(int)*(short *)(param_1 + 0x5c)) != 0)))) {
    __dla__FPv(*(undefined4 *)(param_1 + uStack_14 * 4 + 0x18));
    *(undefined4 *)(param_1 + uStack_14 * 4 + 0x18) = 0;
    *(undefined4 *)(param_1 + uStack_14 * 4 + 0x88) = 0;
  }
  if (*(short *)(param_1 + 0x5c) == 0) {
    if (*(int *)(param_1 + uStack_14 * 4 + 0x18) == 0) {
      uVar9 = __nwa__FUi(iStack_24 << 4);
      *(undefined4 *)(param_1 + uStack_14 * 4 + 0x18) = uVar9;
      *(int *)(param_1 + uStack_14 * 4 + 0x88) = iStack_24;
      puVar7 = *(undefined4 **)(param_1 + uStack_14 * 4 + 0x18);
      *puVar7 = 0x50000000;
      puVar7[1] = *(undefined4 *)
                   (*(int *)(iGpffff86b4 + 0x4264) +
                    (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x4264) + 10) * 4 + 0xc);
      puVar7[2] = 0;
      puVar7[3] = 0;
      puVar7[4] = 0x1000000d;
      puVar7[5] = 0;
      puVar7[6] = 0;
      puVar7[7] = 0x5000000d;
      *(undefined8 *)(puVar7 + 8) = 0x6000000000000001;
      *(undefined8 *)(puVar7 + 10) = 0xe6e8ee;
      *(undefined8 *)(puVar7 + 0xc) = 1;
      *(undefined8 *)(puVar7 + 0xe) = 0x3f;
      *(undefined8 *)(puVar7 + 0x10) = 0x60;
      *(undefined8 *)(puVar7 + 0x12) = 0x14;
      *(undefined8 *)(puVar7 + 0x14) = 5;
      *(undefined8 *)(puVar7 + 0x16) = 0;
      *(undefined8 *)(puVar7 + 0x18) = 0x23003;
      *(undefined8 *)(puVar7 + 0x1a) = 0x47;
      uVar12 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x4264),1);
      *(undefined8 *)(puVar7 + 0x1c) = uVar12;
      *(undefined8 *)(puVar7 + 0x1e) = 0;
      *(undefined8 *)(puVar7 + 0x20) = 0x44;
      *(undefined8 *)(puVar7 + 0x22) = 0x42;
      auVar16._8_4_ = in_v0_udw;
      auVar16._0_8_ = 0xa400000000008001;
      auVar16._12_4_ = in_register_0000002c;
      auVar16 = _pcpyld(in_zero_qw,auVar16);
      *(long *)(puVar7 + 0x24) = auVar16._0_8_;
      uVar12 = auVar16._8_8_;
      *(undefined8 *)(puVar7 + 0x26) = 0x4343c3c310;
      *(undefined8 *)(puVar7 + 0x28) = 0x154;
      *(undefined8 *)(puVar7 + 0x2a) = 0x80808080;
      *(undefined8 *)(puVar7 + 0x2c) = 0x460;
      *(undefined8 *)(puVar7 + 0x30) = 0x1900460;
      *(undefined8 *)(puVar7 + 0x34) = 0x6c0;
      *(undefined8 *)(puVar7 + 0x38) = 0x19006c0;
      puVar7[0x3c] = 0x50000000;
      if ((*(byte *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0xb4) & 1) == 0) {
        if (*(short *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x120) < 8) {
          puVar7[0x3d] = *(undefined4 *)
                          (*(int *)(iGpffff86b4 + 0x42c4) +
                           (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42c4) + 10) * 4 + 0xc);
        }
        else {
          sVar3 = *(short *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x120);
          if (CONCAT44((int)(((long)sVar3 << 0x30) >> 0x3f),(int)sVar3) < 0xb) {
            puVar7[0x3d] = *(undefined4 *)
                            (*(int *)(iGpffff86b4 + 0x42c8) +
                             (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42c8) + 10) * 4 + 0xc);
          }
          else {
            puVar7[0x3d] = *(undefined4 *)
                            (*(int *)(iGpffff86b4 + 0x42cc) +
                             (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42cc) + 10) * 4 + 0xc);
          }
        }
      }
      else {
        puVar7[0x3d] = *(undefined4 *)
                        (*(int *)(iGpffff86b4 + 0x42d0) +
                         (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x42d0) + 10) * 4 + 0xc);
      }
      puVar7[0x3e] = 0;
      puVar7[0x3f] = 0;
      puVar7[0x40] = 0x10000009;
      puVar7[0x41] = 0;
      puVar7[0x42] = 0;
      puVar7[0x43] = 0x50000009;
      *(undefined8 *)(puVar7 + 0x44) = 0x2000000000000001;
      *(undefined8 *)(puVar7 + 0x46) = 0x6e;
      *(undefined8 *)(puVar7 + 0x48) = 1;
      *(undefined8 *)(puVar7 + 0x4a) = 0x3f;
      if ((*(byte *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0xb4) & 1) == 0) {
        if (*(short *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x120) < 8) {
          auVar24._8_8_ = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x42c4),1);
          *(undefined8 *)(puVar7 + 0x4c) = auVar24._8_8_;
          if ((*(byte *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0xb1) & 1) == 0) {
            uVar19 = (ulong)*(short *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x18c);
            if (uVar19 == 0x51) {
              uVar19 = 5;
            }
            if (uVar19 == 0x54) {
              uVar19 = 3;
            }
            if (uVar19 == 0x57) {
              uVar19 = 4;
            }
          }
          else {
            uVar19 = (ulong)*(ushort *)
                             (ourBtlSaveDat +
                              *(short *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x120) *
                              0xc0 + 0x48);
          }
          if ((long)uVar19 < 6) {
            unaff_s4 = 0;
            unaff_s2 = (ulong)((int)uVar19 * 0x18);
          }
          else {
            unaff_s4 = 0x24;
            unaff_s2 = (ulong)(((int)uVar19 + -6) * 0x18);
          }
        }
        else if (*(short *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x120) < 0xb) {
          uVar12 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x42c8),1);
          *(undefined8 *)(puVar7 + 0x4c) = uVar12;
          unaff_s4 = 0;
          uVar12 = CONCAT44(in_register_0000002c,in_v0_udw);
          unaff_s2 = (ulong)((*(short *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x120) +
                             -8) * 0x18);
        }
        else {
          auVar24._8_8_ = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x42cc),1);
          *(undefined8 *)(puVar7 + 0x4c) = auVar24._8_8_;
          unaff_s4 = 0;
          unaff_s2 = 0;
        }
      }
      else {
        auVar24._8_8_ = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x42d0),1);
        *(undefined8 *)(puVar7 + 0x4c) = auVar24._8_8_;
        if ((long)((ulong)*(byte *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0xb0) << 0x3b)
            < 0) {
          unaff_s4 = 0x48;
          unaff_s2 = 0;
        }
        else if (*(short *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x120) < 4) {
          unaff_s4 = 0;
          unaff_s2 = (ulong)(*(short *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x120) *
                            0x18);
        }
        else {
          unaff_s4 = 0x24;
          unaff_s2 = (ulong)((*(short *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x120) +
                             -4) * 0x18);
        }
      }
      *(undefined8 *)(puVar7 + 0x4e) = 0;
      auVar20._8_8_ = in_a2_udw;
      auVar20._0_8_ = 0xa400000000008001;
      auVar16 = _pcpyld(in_zero_qw,auVar20);
      *(long *)(puVar7 + 0x50) = auVar16._0_8_;
      auVar24._8_8_ = auVar16._8_8_;
      *(undefined8 *)(puVar7 + 0x52) = 0x4343c3c310;
      *(undefined8 *)(puVar7 + 0x54) = 0x154;
      *(undefined8 *)(puVar7 + 0x56) = 0x80808080;
      iVar14 = (int)unaff_s4;
      iVar26 = (int)unaff_s2;
      *(long *)(puVar7 + 0x58) = (long)(iVar14 << 4) | (long)(iVar26 << 4) << 0x10;
      *(ulong *)(puVar7 + 0x5c) =
           (long)(iVar14 << 4) |
           CONCAT44((int)(short)((uint)((iVar26 + 0x17) * 0x10) >> 0x10),(iVar26 + 0x17) * 0x100000)
      ;
      *(long *)(puVar7 + 0x60) = (long)((iVar14 + 0x24) * 0x10) | (long)(iVar26 << 4) << 0x10;
      *(ulong *)(puVar7 + 100) =
           (long)((iVar14 + 0x24) * 0x10) |
           CONCAT44((int)(short)((uint)((iVar26 + 0x17) * 0x10) >> 0x10),(iVar26 + 0x17) * 0x100000)
      ;
      puVar7[0x68] = 0x50000000;
      puVar7[0x69] = *(undefined4 *)
                      (*(int *)(iGpffff86b4 + 0x4224) +
                       (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x4224) + 10) * 4 + 0xc);
      puVar7[0x6a] = 0;
      puVar7[0x6b] = 0;
      puVar7[0x6c] = 0x10000002;
      puVar7[0x6d] = 0;
      puVar7[0x6e] = 0;
      puVar7[0x6f] = 0x50000002;
      *(undefined8 *)(puVar7 + 0x70) = 0x1000000000000001;
      *(undefined8 *)(puVar7 + 0x72) = 0xe;
      *(undefined8 *)(puVar7 + 0x74) = 1;
      *(undefined8 *)(puVar7 + 0x76) = 0x3f;
      iVar26 = 0x1e;
      for (iVar14 = 0; iVar14 < 0x10; iVar14 = iVar14 + 1) {
        if ((((*(byte *)(param_1 + iVar14 * 0x28 + 0x90) & 1) != 0) ||
            ((long)((ulong)*(byte *)(param_1 + iVar14 * 0x28 + 0x90) << 0x3e) < 0)) ||
           ((long)((ulong)*(byte *)(param_1 + iVar14 * 0x28 + 0x90) << 0x3d) < 0)) {
          iVar15 = 0;
          if ((*(byte *)(param_1 + iVar14 * 0x28 + 0x90) & 1) != 0) {
            iVar15 = strlen(param_1 + iVar14 * 0x28 + 0x94);
            iVar15 = iVar15 * 4 + 6;
          }
          if ((long)((ulong)*(byte *)(param_1 + iVar14 * 0x28 + 0x90) << 0x3d) < 0) {
            iVar15 = iVar15 + 0x1e;
          }
          if ((long)((ulong)*(byte *)(param_1 + iVar14 * 0x28 + 0x90) << 0x3e) < 0) {
            iVar13 = strlen(param_1 + iVar14 * 0x28 + 0xa4);
            iVar15 = iVar15 + iVar13 * 4 + 6;
          }
          puVar7[iVar26 * 4] = iVar15 + 0x10000000;
          puVar7[iVar26 * 4 + 1] = 0;
          puVar7[iVar26 * 4 + 2] = 0;
          puVar7[iVar26 * 4 + 3] = iVar15 + 0x50000000;
          iVar15 = iVar26 + 1;
          auVar23._0_8_ = (long)param_1;
          auVar23._8_8_ = auVar24._8_8_;
          if ((*(byte *)(param_1 + iVar14 * 0x28 + 0x90) & 1) != 0) {
            iVar13 = strlen(param_1 + iVar14 * 0x28 + 0x94);
            uVar12 = CONCAT44(in_register_0000002c,in_v0_udw);
            *(undefined8 *)(puVar7 + iVar15 * 4) = 0x2000000000000001;
            *(undefined8 *)(puVar7 + iVar15 * 4 + 2) = 0x6e;
            uVar19 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x4224),1);
            *(ulong *)(puVar7 + (iVar26 + 2) * 4) = uVar19 & 0xfffffffc0fffff | 0x2000000001300000;
            *(undefined8 *)(puVar7 + (iVar26 + 2) * 4 + 2) = 0x16;
            *(ulong *)(puVar7 + (iVar26 + 3) * 4) =
                 uVar19 & 0xffffffffffffff | (long)*(char *)(param_1 + iVar14 * 0x28 + 0x91) << 0x38
            ;
            *(undefined8 *)(puVar7 + (iVar26 + 3) * 4 + 2) = 0;
            *(undefined8 *)(puVar7 + (iVar26 + 4) * 4) = 0x2400000000000001;
            *(undefined8 *)(puVar7 + (iVar26 + 4) * 4 + 2) = 0x10;
            *(undefined8 *)(puVar7 + (iVar26 + 5) * 4) = 0x154;
            *(undefined8 *)(puVar7 + (iVar26 + 5) * 4 + 2) = 0x80808080;
            iVar15 = iVar26 + 6;
            if (((long)((ulong)*(byte *)(param_1 + iVar14 * 0x28 + 0x90) << 0x3d) < 0) ||
               ((long)((ulong)*(byte *)(param_1 + iVar14 * 0x28 + 0x90) << 0x3e) < 0)) {
              auVar23._8_8_ = auVar24._8_8_;
              auVar23._0_8_ = 0x8000000000000000;
              auVar16 = _pcpyld(in_zero_qw,auVar23);
              *(ulong *)(puVar7 + iVar15 * 4) = (long)iVar13 | 0x400000000000000U | auVar16._0_8_;
            }
            else {
              auVar23._8_8_ = auVar24._8_8_;
              auVar23._0_8_ = 0xffffffff80000000;
              auVar17._8_8_ = uVar12;
              auVar17._0_8_ = 0x8000000000000000;
              auVar16 = _pcpyld(in_zero_qw,auVar17);
              *(ulong *)(puVar7 + iVar15 * 4) = (long)iVar13 | 0x400000000008000U | auVar16._0_8_;
            }
            *(undefined8 *)(puVar7 + iVar15 * 4 + 2) = 0x4343c3c3;
            iVar15 = iVar26 + 7 + iVar13 * 4;
          }
          auVar24._8_8_ = auVar23._8_8_;
          auVar24._0_8_ = (long)(iVar14 * 4);
          iVar26 = iVar15;
          if ((long)((ulong)*(byte *)(param_1 + iVar14 * 0x28 + 0x90) << 0x3d) < 0) {
            *(undefined8 *)(puVar7 + iVar15 * 4) = 0x2000000000000001;
            *(undefined8 *)(puVar7 + iVar15 * 4 + 2) = 0x6e;
            uVar19 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x4224),1);
            *(ulong *)(puVar7 + (iVar15 + 1) * 4) = uVar19 & 0xfffffffc0fffff | 0x2000000001300000;
            *(undefined8 *)(puVar7 + (iVar15 + 1) * 4 + 2) = 0x16;
            *(ulong *)(puVar7 + (iVar15 + 2) * 4) =
                 uVar19 & 0xffffffffffffff |
                 (ulong)(uint)(int)*(char *)(param_1 + iVar14 * 0x28 + 0x93) << 0x38;
            *(undefined8 *)(puVar7 + (iVar15 + 2) * 4 + 2) = 0;
            *(undefined8 *)(puVar7 + (iVar15 + 3) * 4) = 0x2400000000000001;
            *(undefined8 *)(puVar7 + (iVar15 + 3) * 4 + 2) = 0x10;
            *(undefined8 *)(puVar7 + (iVar15 + 4) * 4) = 0x154;
            *(undefined8 *)(puVar7 + (iVar15 + 4) * 4 + 2) = 0x80808080;
            iVar26 = iVar15 + 5;
            if ((long)((ulong)*(byte *)(param_1 + iVar14 * 0x28 + 0x90) << 0x3e) < 0) {
              auVar18._8_8_ = uVar12;
              auVar18._0_8_ = 0x8400000000000006;
              auVar21 = _pcpyld(in_zero_qw,auVar18);
              auVar24._0_8_ = (long)(int)(puVar7 + iVar26 * 4);
              *(long *)(puVar7 + iVar26 * 4) = auVar21._0_8_;
            }
            else {
              auVar8._8_4_ = in_s3_udw;
              auVar8._0_8_ = 0x8400000000008006;
              auVar8._12_4_ = in_register_0000013c;
              auVar24 = _pcpyld(in_zero_qw,auVar8);
              auVar21._0_8_ = (long)(iVar26 * 0x10);
              auVar21._8_8_ = in_a2_udw;
              *(long *)(puVar7 + iVar26 * 4) = auVar24._0_8_;
            }
            in_a2_udw = auVar21._8_8_;
            *(undefined8 *)(puVar7 + iVar26 * 4 + 2) = 0x4343c3c3;
            iVar26 = iVar15 + 0x1e;
          }
          if ((long)((ulong)*(byte *)(param_1 + iVar14 * 0x28 + 0x90) << 0x3e) < 0) {
            iVar15 = strlen(param_1 + iVar14 * 0x28 + 0xa4);
            *(undefined8 *)(puVar7 + iVar26 * 4) = 0x2000000000000001;
            *(undefined8 *)(puVar7 + iVar26 * 4 + 2) = 0x6e;
            uVar19 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x4224),1);
            *(ulong *)(puVar7 + (iVar26 + 1) * 4) = uVar19 & 0xfffffffc0fffff | 0x2000000001300000;
            *(undefined8 *)(puVar7 + (iVar26 + 1) * 4 + 2) = 0x16;
            *(ulong *)(puVar7 + (iVar26 + 2) * 4) =
                 uVar19 & 0xffffffffffffff | (long)*(char *)(param_1 + iVar14 * 0x28 + 0x92) << 0x38
            ;
            *(undefined8 *)(puVar7 + (iVar26 + 2) * 4 + 2) = 0;
            *(undefined8 *)(puVar7 + (iVar26 + 3) * 4) = 0x2400000000000001;
            *(undefined8 *)(puVar7 + (iVar26 + 3) * 4 + 2) = 0x10;
            *(undefined8 *)(puVar7 + (iVar26 + 4) * 4) = 0x154;
            *(undefined8 *)(puVar7 + (iVar26 + 4) * 4 + 2) = 0x80808080;
            auVar22._8_8_ = in_a2_udw;
            auVar22._0_8_ = 0x8000000000000000;
            auVar16 = _pcpyld(in_zero_qw,auVar22);
            *(ulong *)(puVar7 + (iVar26 + 5) * 4) =
                 (long)iVar15 | 0x400000000008000U | auVar16._0_8_;
            uVar12 = auVar16._8_8_;
            *(undefined8 *)(puVar7 + (iVar26 + 5) * 4 + 2) = 0x4343c3c3;
            iVar26 = iVar26 + 6 + iVar15 * 4;
          }
        }
      }
    }
    iVar26 = *(int *)(param_1 + uStack_14 * 4 + 0x18);
    uVar19 = __fixunssfdi(fStack_90 * 16.0);
    lVar25 = __fixunssfdi(fVar35 * 16.0);
    *(ulong *)(iVar26 + 0xb8) = uVar19 | lVar25 << 0x10;
    uVar12 = __fixunssfdi((fVar35 + *(float *)(param_1 + 0x84) * 25.0) * 16.0);
    uVar19 = __fixunssfdi(fStack_90 * 16.0);
    *(ulong *)(iVar26 + 200) = uVar19 | CONCAT44((int)((ulong)uVar12 >> 0x10),(int)uVar12 << 0x10);
    uVar19 = __fixunssfdi((fStack_90 + *(float *)(param_1 + 0x80) * 38.0) * 16.0);
    lVar25 = __fixunssfdi(fVar35 * 16.0);
    *(ulong *)(iVar26 + 0xd8) = lVar25 << 0x10 | uVar19;
    uVar19 = __fixunssfdi((fStack_90 + *(float *)(param_1 + 0x80) * 38.0) * 16.0);
    uVar12 = __fixunssfdi((fVar35 + *(float *)(param_1 + 0x84) * 25.0) * 16.0);
    *(ulong *)(iVar26 + 0xe8) = uVar19 | CONCAT44((int)((ulong)uVar12 >> 0x10),(int)uVar12 << 0x10);
    uVar19 = __fixunssfdi((fStack_90 + *(float *)(param_1 + 0x80)) * 16.0);
    uVar12 = __fixunssfdi(fVar35 * 16.0);
    *(ulong *)(iVar26 + 0x168) = CONCAT44((int)((ulong)uVar12 >> 0x10),(int)uVar12 << 0x10) | uVar19
    ;
    uVar12 = __fixunssfdi((fVar35 + *(float *)(param_1 + 0x84) * 23.0) * 16.0);
    uVar19 = __fixunssfdi((fStack_90 + *(float *)(param_1 + 0x80)) * 16.0);
    *(ulong *)(iVar26 + 0x178) = uVar19 | CONCAT44((int)((ulong)uVar12 >> 0x10),(int)uVar12 << 0x10)
    ;
    uVar19 = __fixunssfdi((fStack_90 + *(float *)(param_1 + 0x80) * 37.0) * 16.0);
    lVar25 = __fixunssfdi(fVar35 * 16.0);
    *(ulong *)(iVar26 + 0x188) = lVar25 << 0x10 | uVar19;
    uVar19 = __fixunssfdi((fStack_90 + *(float *)(param_1 + 0x80) * 37.0) * 16.0);
    lVar25 = __fixunssfdi((fVar35 + *(float *)(param_1 + 0x84) * 23.0) * 16.0);
    *(ulong *)(iVar26 + 0x198) = uVar19 | lVar25 << 0x10;
    fStack_90 = fStack_90 + *(float *)(param_1 + 0x80) * 46.0;
    fVar35 = fVar35 + 1.0;
    iVar14 = 0x1e;
    for (iVar15 = 0; iVar15 < 0x10; iVar15 = iVar15 + 1) {
      if ((((*(byte *)(param_1 + iVar15 * 0x28 + 0x90) & 1) != 0) ||
          ((long)((ulong)*(byte *)(param_1 + iVar15 * 0x28 + 0x90) << 0x3e) < 0)) ||
         (iVar13 = iVar14, (long)((ulong)*(byte *)(param_1 + iVar15 * 0x28 + 0x90) << 0x3d) < 0)) {
        iVar13 = iVar14 + 1;
        if ((*(byte *)(param_1 + iVar15 * 0x28 + 0x90) & 1) != 0) {
          iVar13 = iVar14 + 7;
          for (iVar14 = 0; *(char *)(param_1 + iVar15 * 0x28 + iVar14 + 0x94) != '\0';
              iVar14 = iVar14 + 1) {
            cVar2 = *(char *)(param_1 + iVar15 * 0x28 + iVar14 + 0x94);
            iVar27 = (int)cVar2;
            iVar28 = (int)(((long)cVar2 << 0x38) >> 0x3f);
            if (CONCAT44(iVar28,iVar27) == 0x20) {
              unaff_s4 = 0xffffffffffffffff;
              unaff_s2 = 0xffffffffffffffff;
              unaff_s7 = 0xffffffffffffffff;
              unaff_s6 = 0xffffffffffffffff;
            }
            else if ((CONCAT44(iVar28,iVar27) < 0x41) || (0x5a < CONCAT44(iVar28,iVar27))) {
              if ((CONCAT44(iVar28,iVar27) < 0x61) || (0x7a < CONCAT44(iVar28,iVar27))) {
                if ((CONCAT44(iVar28,iVar27) < 0x30) || (0x39 < CONCAT44(iVar28,iVar27))) {
                  if (CONCAT44(iVar28,iVar27) == 0x21) {
                    unaff_s4 = (ulong)uRam00651d80;
                    unaff_s2 = (ulong)uRam00651d82;
                    unaff_s7 = (ulong)uRam00651d84;
                    unaff_s6 = (ulong)uRam00651d86;
                  }
                  else if (CONCAT44(iVar28,iVar27) == 0x3f) {
                    unaff_s4 = (ulong)uRam00651d88;
                    unaff_s2 = (ulong)uRam00651d8a;
                    unaff_s7 = (ulong)uRam00651d8c;
                    unaff_s6 = (ulong)uRam00651d8e;
                  }
                  else if (CONCAT44(iVar28,iVar27) == 0x2b) {
                    unaff_s4 = (ulong)uRam00651d90;
                    unaff_s2 = (ulong)uRam00651d92;
                    unaff_s7 = (ulong)uRam00651d94;
                    unaff_s6 = (ulong)uRam00651d96;
                  }
                  else if (CONCAT44(iVar28,iVar27) == 0x2d) {
                    unaff_s4 = (ulong)uRam00651d98;
                    unaff_s2 = (ulong)uRam00651d9a;
                    unaff_s7 = (ulong)uRam00651d9c;
                    unaff_s6 = (ulong)uRam00651d9e;
                  }
                  else if (CONCAT44(iVar28,iVar27) == 0x2a) {
                    unaff_s4 = (ulong)uRam00651da0;
                    unaff_s2 = (ulong)uRam00651da2;
                    unaff_s7 = (ulong)uRam00651da4;
                    unaff_s6 = (ulong)uRam00651da6;
                  }
                  else if (CONCAT44(iVar28,iVar27) == 0x25) {
                    unaff_s4 = (ulong)uRam00651da8;
                    unaff_s2 = (ulong)uRam00651daa;
                    unaff_s7 = (ulong)uRam00651dac;
                    unaff_s6 = (ulong)uRam00651dae;
                  }
                  else if (CONCAT44(iVar28,iVar27) == 0x2f) {
                    unaff_s4 = (ulong)uRam00651db0;
                    unaff_s2 = (ulong)uRam00651db2;
                    unaff_s7 = (ulong)uRam00651db4;
                    unaff_s6 = (ulong)uRam00651db6;
                  }
                  else if (CONCAT44(iVar28,iVar27) == 0x27) {
                    unaff_s4 = (ulong)uRam00651dc0;
                    unaff_s2 = (ulong)uRam00651dc2;
                    unaff_s7 = (ulong)uRam00651dc4;
                    unaff_s6 = (ulong)uRam00651dc6;
                  }
                  else if (CONCAT44(iVar28,iVar27) == 0x2e) {
                    unaff_s4 = (ulong)uRam00651dc8;
                    unaff_s2 = (ulong)uRam00651dca;
                    unaff_s7 = (ulong)uRam00651dcc;
                    unaff_s6 = (ulong)uRam00651dce;
                  }
                  else if (CONCAT44(iVar28,iVar27) == 0x2c) {
                    unaff_s4 = (ulong)uRam00651dd0;
                    unaff_s2 = (ulong)uRam00651dd2;
                    unaff_s7 = (ulong)uRam00651dd4;
                    unaff_s6 = (ulong)uRam00651dd6;
                  }
                }
                else {
                  unaff_s4 = (ulong)*(ushort *)((iVar27 + 4) * 8 + 0x651b90);
                  unaff_s2 = (ulong)*(ushort *)((iVar27 + 4) * 8 + 0x651b92);
                  unaff_s7 = (ulong)*(ushort *)((iVar27 + 4) * 8 + 0x651b94);
                  unaff_s6 = (ulong)*(ushort *)((iVar27 + 4) * 8 + 0x651b96);
                }
              }
              else {
                unaff_s4 = (ulong)*(ushort *)((iVar27 + -0x47) * 8 + 0x651b90);
                unaff_s2 = (ulong)*(ushort *)((iVar27 + -0x47) * 8 + 0x651b92);
                unaff_s7 = (ulong)*(ushort *)((iVar27 + -0x47) * 8 + 0x651b94);
                unaff_s6 = (ulong)*(ushort *)((iVar27 + -0x47) * 8 + 0x651b96);
              }
            }
            else {
              unaff_s4 = (ulong)*(ushort *)((iVar27 + -0x41) * 8 + 0x651b90);
              unaff_s2 = (ulong)*(ushort *)((iVar27 + -0x41) * 8 + 0x651b92);
              unaff_s7 = (ulong)*(ushort *)((iVar27 + -0x41) * 8 + 0x651b94);
              unaff_s6 = (ulong)*(ushort *)((iVar27 + -0x41) * 8 + 0x651b96);
            }
            if ((((unaff_s4 == 0xffffffffffffffff) && (unaff_s7 == 0xffffffffffffffff)) &&
                (unaff_s2 == 0xffffffffffffffff)) && (unaff_s6 == 0xffffffffffffffff)) {
              *(undefined8 *)(iVar26 + iVar13 * 0x10 + 8) = 0x71006f00;
              *(undefined8 *)(iVar26 + (iVar13 + 1) * 0x10 + 8) = 0x71006f00;
              *(undefined8 *)(iVar26 + (iVar13 + 2) * 0x10 + 8) = 0x71006f00;
              *(undefined8 *)(iVar26 + (iVar13 + 3) * 0x10 + 8) = 0x71006f00;
              fVar33 = *(float *)(param_1 + 0x80) * 8.0;
            }
            else {
              iVar27 = (int)unaff_s2;
              iVar31 = (int)unaff_s6;
              fVar33 = *(float *)(param_1 + 0x80) * (24.0 / (float)((iVar31 - iVar27) + -5));
              fStack_1c = *(float *)(param_1 + 0x84) * (24.0 / (float)((iVar31 - iVar27) + -5));
              iVar28 = (int)unaff_s4;
              *(long *)(iVar26 + iVar13 * 0x10) = (long)(iVar28 << 4) | (long)(iVar27 << 4) << 0x10;
              uVar19 = __fixunssfdi(fStack_90 * 16.0);
              lVar25 = __fixunssfdi(fVar35 * 16.0);
              *(ulong *)(iVar26 + iVar13 * 0x10 + 8) = uVar19 | lVar25 << 0x10;
              *(long *)(iVar26 + (iVar13 + 1) * 0x10) =
                   (long)(iVar28 << 4) | (long)(iVar31 << 4) << 0x10;
              uVar12 = __fixunssfdi((fVar35 + fStack_1c * (float)(iVar31 - iVar27)) * 16.0);
              uVar19 = __fixunssfdi(fStack_90 * 16.0);
              *(ulong *)(iVar26 + (iVar13 + 1) * 0x10 + 8) =
                   uVar19 | CONCAT44((int)((ulong)uVar12 >> 0x10),(int)uVar12 << 0x10);
              iVar32 = (int)unaff_s7;
              *(long *)(iVar26 + (iVar13 + 2) * 0x10) =
                   (long)(iVar32 << 4) | (long)(iVar27 << 4) << 0x10;
              uVar19 = __fixunssfdi((fStack_90 + fVar33 * (float)(iVar32 - iVar28)) * 16.0);
              lVar25 = __fixunssfdi(fVar35 * 16.0);
              *(ulong *)(iVar26 + (iVar13 + 2) * 0x10 + 8) = lVar25 << 0x10 | uVar19;
              *(long *)(iVar26 + (iVar13 + 3) * 0x10) =
                   (long)(iVar32 << 4) | (long)(iVar31 << 4) << 0x10;
              uVar19 = __fixunssfdi((fStack_90 + fVar33 * (float)(iVar32 - iVar28)) * 16.0);
              uVar12 = __fixunssfdi((fVar35 + fStack_1c * (float)(iVar31 - iVar27)) * 16.0);
              *(ulong *)(iVar26 + (iVar13 + 3) * 0x10 + 8) =
                   uVar19 | CONCAT44((int)((ulong)uVar12 >> 0x10),(int)uVar12 << 0x10);
              fVar33 = fVar33 * (float)((iVar32 - iVar28) + -2);
            }
            fStack_90 = fStack_90 + fVar33;
            iVar13 = iVar13 + 4;
          }
        }
        uVar6 = uRam00651d9c;
        uVar5 = uRam00651d94;
        uVar4 = uRam00651d90;
        if ((long)((ulong)*(byte *)(param_1 + iVar15 * 0x28 + 0x90) << 0x3d) < 0) {
          iVar14 = iVar13 + 6;
          if (((long)((ulong)*(byte *)(param_1 + iVar15 * 0x28 + 0x90) << 0x3c) < 0) &&
             (-1 < *(int *)(param_1 + iVar15 * 0x28 + 0xb4))) {
            unaff_s4 = (ulong)uRam00651d90;
            unaff_s2 = (ulong)uRam00651d92;
            unaff_s7 = (ulong)uRam00651d94;
            unaff_s6 = (ulong)uRam00651d96;
            uVar10 = (uint)uRam00651d92;
            uVar29 = (uint)uRam00651d96;
            fVar33 = *(float *)(param_1 + 0x80) * (24.0 / (float)(int)((uVar29 - uVar10) + -5));
            fStack_1c = *(float *)(param_1 + 0x84) * (24.0 / (float)(int)((uVar29 - uVar10) + -5));
            uVar11 = (uint)uRam00651d90;
            *(long *)(iVar26 + iVar14 * 0x10) =
                 (long)(int)(uVar11 << 4) | (long)(int)(uVar10 << 4) << 0x10;
            uVar19 = __fixunssfdi(fStack_90 * 16.0);
            lVar25 = __fixunssfdi(fVar35 * 16.0);
            *(ulong *)(iVar26 + iVar14 * 0x10 + 8) = uVar19 | lVar25 << 0x10;
            *(ulong *)(iVar26 + (iVar13 + 7) * 0x10) =
                 (ulong)uVar4 << 4 | (long)(int)(uVar29 << 4) << 0x10;
            uVar12 = __fixunssfdi((fVar35 + fStack_1c * (float)(int)(uVar29 - uVar10)) * 16.0);
            uVar19 = __fixunssfdi(fStack_90 * 16.0);
            *(ulong *)(iVar26 + (iVar13 + 7) * 0x10 + 8) =
                 uVar19 | CONCAT44((int)((ulong)uVar12 >> 0x10),(int)uVar12 << 0x10);
            uVar30 = (uint)uVar5;
            *(long *)(iVar26 + (iVar13 + 8) * 0x10) =
                 (long)(int)(uVar30 << 4) | (long)(int)(uVar10 << 4) << 0x10;
            uVar19 = __fixunssfdi((fStack_90 + fVar33 * (float)(int)(uVar30 - uVar11)) * 16.0);
            lVar25 = __fixunssfdi(fVar35 * 16.0);
            *(ulong *)(iVar26 + (iVar13 + 8) * 0x10 + 8) = lVar25 << 0x10 | uVar19;
            *(ulong *)(iVar26 + (iVar13 + 9) * 0x10) =
                 CONCAT44((int)(short)((uVar29 << 4) >> 0x10),uVar30 << 4 | uVar29 << 0x14);
            uVar19 = __fixunssfdi((fStack_90 + fVar33 * (float)(int)(uVar30 - uVar11)) * 16.0);
            lVar25 = __fixunssfdi((fVar35 + fStack_1c * (float)(int)(uVar29 - uVar10)) * 16.0);
            *(ulong *)(iVar26 + (iVar13 + 9) * 0x10 + 8) = uVar19 | lVar25 << 0x10;
            fStack_90 = fStack_90 + fVar33 * (float)(int)((uVar30 - uVar11) + -2);
          }
          else if (((long)((ulong)*(byte *)(param_1 + iVar15 * 0x28 + 0x90) << 0x3b) < 0) &&
                  (*(int *)(param_1 + iVar15 * 0x28 + 0xb4) < 0)) {
            uVar10 = (uint)uRam00651d98;
            unaff_s4 = (ulong)uVar10;
            uVar11 = (uint)uRam00651d9a;
            unaff_s2 = (ulong)uVar11;
            unaff_s7 = (ulong)uRam00651d9c;
            unaff_s6 = (ulong)uRam00651d9e;
            uVar29 = (uint)uRam00651d9e;
            fVar33 = *(float *)(param_1 + 0x80) * (24.0 / (float)(int)((uVar29 - uVar11) + -5));
            fStack_1c = *(float *)(param_1 + 0x84) * (24.0 / (float)(int)((uVar29 - uVar11) + -5));
            *(ulong *)(iVar26 + iVar14 * 0x10) =
                 CONCAT44((int)(short)((uVar11 << 4) >> 0x10),uVar10 << 4 | uVar11 << 0x14);
            uVar19 = __fixunssfdi(fStack_90 * 16.0);
            lVar25 = __fixunssfdi(fVar35 * 16.0);
            *(ulong *)(iVar26 + iVar14 * 0x10 + 8) = uVar19 | lVar25 << 0x10;
            *(long *)(iVar26 + (iVar13 + 7) * 0x10) =
                 (long)(int)(uVar10 << 4) | (long)(int)(uVar29 << 4) << 0x10;
            uVar12 = __fixunssfdi((fVar35 + fStack_1c * (float)(int)(uVar29 - uVar11)) * 16.0);
            uVar19 = __fixunssfdi(fStack_90 * 16.0);
            *(ulong *)(iVar26 + (iVar13 + 7) * 0x10 + 8) =
                 uVar19 | CONCAT44((int)((ulong)uVar12 >> 0x10),(int)uVar12 << 0x10);
            uVar30 = (uint)uVar6;
            *(long *)(iVar26 + (iVar13 + 8) * 0x10) =
                 (long)(int)(uVar30 << 4) | (long)(int)(uVar11 << 4) << 0x10;
            uVar19 = __fixunssfdi((fStack_90 + fVar33 * (float)(int)(uVar30 - uVar10)) * 16.0);
            lVar25 = __fixunssfdi(fVar35 * 16.0);
            *(ulong *)(iVar26 + (iVar13 + 8) * 0x10 + 8) = lVar25 << 0x10 | uVar19;
            *(long *)(iVar26 + (iVar13 + 9) * 0x10) =
                 (long)(int)(uVar30 << 4) | (long)(int)(uVar29 << 4) << 0x10;
            uVar19 = __fixunssfdi((fStack_90 + fVar33 * (float)(int)(uVar30 - uVar10)) * 16.0);
            lVar25 = __fixunssfdi((fVar35 + fStack_1c * (float)(int)(uVar29 - uVar11)) * 16.0);
            *(ulong *)(iVar26 + (iVar13 + 9) * 0x10 + 8) = uVar19 | lVar25 << 0x10;
            fStack_90 = fStack_90 + fVar33 * (float)(int)((uVar30 - uVar10) + -2);
          }
          else {
            *(undefined8 *)(iVar26 + iVar14 * 0x10 + 8) = 0x71006f00;
            *(undefined8 *)(iVar26 + (iVar13 + 7) * 0x10 + 8) = 0x71006f00;
            *(undefined8 *)(iVar26 + (iVar13 + 8) * 0x10 + 8) = 0x71006f00;
            *(undefined8 *)(iVar26 + (iVar13 + 9) * 0x10 + 8) = 0x71006f00;
          }
          fVar33 = fStack_90;
          iVar13 = iVar13 + 10;
          lVar25 = 10000;
          while (lVar25 != 0) {
            iVar14 = *(int *)(param_1 + iVar15 * 0x28 + 0xb4);
            iVar27 = iVar14 >> 0x1f;
            if (iVar27 < 0) {
              iVar14 = -*(int *)(param_1 + iVar15 * 0x28 + 0xb4);
              iVar27 = iVar14 >> 0x1f;
            }
            iVar28 = (int)lVar25;
            if ((CONCAT44(iVar27,iVar14) < lVar25) && (lVar25 != 1)) {
              *(undefined8 *)(iVar26 + iVar13 * 0x10 + 8) = 0x71006f00;
              *(undefined8 *)(iVar26 + (iVar13 + 1) * 0x10 + 8) = 0x71006f00;
              *(undefined8 *)(iVar26 + (iVar13 + 2) * 0x10 + 8) = 0x71006f00;
              *(undefined8 *)(iVar26 + (iVar13 + 3) * 0x10 + 8) = 0x71006f00;
            }
            else {
              if (lVar25 == 0) {
                trap(7);
              }
              iVar14 = (iVar14 / iVar28) % 10;
              uVar4 = *(ushort *)((iVar14 + 0x34) * 8 + 0x651b90);
              unaff_s4 = (ulong)uVar4;
              uVar5 = *(ushort *)((iVar14 + 0x34) * 8 + 0x651b92);
              unaff_s2 = (ulong)uVar5;
              uVar10 = (uint)*(ushort *)((iVar14 + 0x34) * 8 + 0x651b94);
              unaff_s7 = (ulong)uVar10;
              uVar6 = *(ushort *)((iVar14 + 0x34) * 8 + 0x651b96);
              unaff_s6 = (ulong)uVar6;
              uVar11 = (uint)uVar5;
              uVar30 = (uint)uVar6;
              fVar34 = *(float *)(param_1 + 0x80) * (24.0 / (float)(int)((uVar30 - uVar11) + -5));
              fStack_1c = *(float *)(param_1 + 0x84) * (24.0 / (float)(int)((uVar30 - uVar11) + -5))
              ;
              uVar29 = (uint)uVar4;
              *(ulong *)(iVar26 + iVar13 * 0x10) = (ulong)uVar4 << 4 | (ulong)uVar5 << 0x14;
              uVar19 = __fixunssfdi(fStack_90 * 16.0);
              lVar25 = __fixunssfdi(fVar35 * 16.0);
              *(ulong *)(iVar26 + iVar13 * 0x10 + 8) = uVar19 | lVar25 << 0x10;
              *(ulong *)(iVar26 + (iVar13 + 1) * 0x10) =
                   CONCAT44((int)(short)((uVar30 << 4) >> 0x10),(uint)uVar4 << 4 | uVar30 << 0x14);
              uVar12 = __fixunssfdi((fVar35 + fStack_1c * (float)(int)(uVar30 - uVar11)) * 16.0);
              uVar19 = __fixunssfdi(fStack_90 * 16.0);
              *(ulong *)(iVar26 + (iVar13 + 1) * 0x10 + 8) =
                   uVar19 | CONCAT44((int)((ulong)uVar12 >> 0x10),(int)uVar12 << 0x10);
              *(ulong *)(iVar26 + (iVar13 + 2) * 0x10) =
                   CONCAT44((int)(short)((uVar11 << 4) >> 0x10),uVar10 << 4 | uVar11 << 0x14);
              uVar19 = __fixunssfdi((fStack_90 + fVar34 * (float)(int)(uVar10 - uVar29)) * 16.0);
              lVar25 = __fixunssfdi(fVar35 * 16.0);
              *(ulong *)(iVar26 + (iVar13 + 2) * 0x10 + 8) = lVar25 << 0x10 | uVar19;
              *(long *)(iVar26 + (iVar13 + 3) * 0x10) =
                   (long)(int)(uVar10 << 4) | (long)(int)(uVar30 << 4) << 0x10;
              uVar19 = __fixunssfdi((fStack_90 + fVar34 * (float)(int)(uVar10 - uVar29)) * 16.0);
              lVar25 = __fixunssfdi((fVar35 + fStack_1c * (float)(int)(uVar30 - uVar11)) * 16.0);
              *(ulong *)(iVar26 + (iVar13 + 3) * 0x10 + 8) = uVar19 | lVar25 << 0x10;
              fStack_90 = fStack_90 + fVar34 * (float)(int)((uVar10 - uVar29) + -2);
            }
            iVar13 = iVar13 + 4;
            lVar25 = (long)(iVar28 / 10 + (iVar28 >> 0x1f));
          }
          if (((long)((ulong)*(byte *)(param_1 + iVar15 * 0x28 + 0x90) << 0x3e) < 0) &&
             (lVar25 = strcmp(param_1 + iVar15 * 0x28 + 0xa4,
                                       *(undefined4 *)(iRam0040ab20 + 0x9c)), lVar25 == 0)) {
            *(float *)(param_1 + 0x310) = (fStack_90 + fVar33) / 2.0;
            *(float *)(param_1 + 0x314) =
                 fVar35 + (fStack_1c * (float)((int)unaff_s6 - (int)unaff_s2)) / 2.0;
          }
        }
        if ((long)((ulong)*(byte *)(param_1 + iVar15 * 0x28 + 0x90) << 0x3e) < 0) {
          iVar13 = iVar13 + 6;
          for (iVar14 = 0; *(char *)(param_1 + iVar15 * 0x28 + iVar14 + 0xa4) != '\0';
              iVar14 = iVar14 + 1) {
            cVar2 = *(char *)(param_1 + iVar15 * 0x28 + iVar14 + 0xa4);
            iVar27 = (int)cVar2;
            if (cVar2 == ' ') {
              unaff_s4 = 0xffffffffffffffff;
              unaff_s2 = 0xffffffffffffffff;
              unaff_s7 = 0xffffffffffffffff;
              unaff_s6 = 0xffffffffffffffff;
            }
            else if ((cVar2 < 'A') || ('Z' < cVar2)) {
              if ((cVar2 < 'a') || ('z' < cVar2)) {
                if ((cVar2 < '0') || ('9' < cVar2)) {
                  if (cVar2 == '!') {
                    unaff_s4 = (ulong)uRam00651d80;
                    unaff_s2 = (ulong)uRam00651d82;
                    unaff_s7 = (ulong)uRam00651d84;
                    unaff_s6 = (ulong)uRam00651d86;
                  }
                  else if (cVar2 == '?') {
                    unaff_s4 = (ulong)uRam00651d88;
                    unaff_s2 = (ulong)uRam00651d8a;
                    unaff_s7 = (ulong)uRam00651d8c;
                    unaff_s6 = (ulong)uRam00651d8e;
                  }
                  else if (cVar2 == '+') {
                    unaff_s4 = (ulong)uRam00651d90;
                    unaff_s2 = (ulong)uRam00651d92;
                    unaff_s7 = (ulong)uRam00651d94;
                    unaff_s6 = (ulong)uRam00651d96;
                  }
                  else if (cVar2 == '-') {
                    unaff_s4 = (ulong)uRam00651d98;
                    unaff_s2 = (ulong)uRam00651d9a;
                    unaff_s7 = (ulong)uRam00651d9c;
                    unaff_s6 = (ulong)uRam00651d9e;
                  }
                  else if (cVar2 == '*') {
                    unaff_s4 = (ulong)uRam00651da0;
                    unaff_s2 = (ulong)uRam00651da2;
                    unaff_s7 = (ulong)uRam00651da4;
                    unaff_s6 = (ulong)uRam00651da6;
                  }
                  else if (cVar2 == '%') {
                    unaff_s4 = (ulong)uRam00651da8;
                    unaff_s2 = (ulong)uRam00651daa;
                    unaff_s7 = (ulong)uRam00651dac;
                    unaff_s6 = (ulong)uRam00651dae;
                  }
                  else if (cVar2 == '/') {
                    unaff_s4 = (ulong)uRam00651db0;
                    unaff_s2 = (ulong)uRam00651db2;
                    unaff_s7 = (ulong)uRam00651db4;
                    unaff_s6 = (ulong)uRam00651db6;
                  }
                  else if (cVar2 == '\'') {
                    unaff_s4 = (ulong)uRam00651dc0;
                    unaff_s2 = (ulong)uRam00651dc2;
                    unaff_s7 = (ulong)uRam00651dc4;
                    unaff_s6 = (ulong)uRam00651dc6;
                  }
                  else if (cVar2 == '.') {
                    unaff_s4 = (ulong)uRam00651dc8;
                    unaff_s2 = (ulong)uRam00651dca;
                    unaff_s7 = (ulong)uRam00651dcc;
                    unaff_s6 = (ulong)uRam00651dce;
                  }
                  else if (cVar2 == ',') {
                    unaff_s4 = (ulong)uRam00651dd0;
                    unaff_s2 = (ulong)uRam00651dd2;
                    unaff_s7 = (ulong)uRam00651dd4;
                    unaff_s6 = (ulong)uRam00651dd6;
                  }
                }
                else {
                  unaff_s4 = (ulong)*(ushort *)((iVar27 + 4) * 8 + 0x651b90);
                  unaff_s2 = (ulong)*(ushort *)((iVar27 + 4) * 8 + 0x651b92);
                  unaff_s7 = (ulong)*(ushort *)((iVar27 + 4) * 8 + 0x651b94);
                  unaff_s6 = (ulong)*(ushort *)((iVar27 + 4) * 8 + 0x651b96);
                }
              }
              else {
                unaff_s4 = (ulong)*(ushort *)((iVar27 + -0x47) * 8 + 0x651b90);
                unaff_s2 = (ulong)*(ushort *)((iVar27 + -0x47) * 8 + 0x651b92);
                unaff_s7 = (ulong)*(ushort *)((iVar27 + -0x47) * 8 + 0x651b94);
                unaff_s6 = (ulong)*(ushort *)((iVar27 + -0x47) * 8 + 0x651b96);
              }
            }
            else {
              unaff_s4 = (ulong)*(ushort *)((iVar27 + -0x41) * 8 + 0x651b90);
              unaff_s2 = (ulong)*(ushort *)((iVar27 + -0x41) * 8 + 0x651b92);
              unaff_s7 = (ulong)*(ushort *)((iVar27 + -0x41) * 8 + 0x651b94);
              unaff_s6 = (ulong)*(ushort *)((iVar27 + -0x41) * 8 + 0x651b96);
            }
            if ((((unaff_s4 == 0xffffffffffffffff) && (unaff_s7 == 0xffffffffffffffff)) &&
                (unaff_s2 == 0xffffffffffffffff)) && (unaff_s6 == 0xffffffffffffffff)) {
              *(undefined8 *)(iVar26 + iVar13 * 0x10 + 8) = 0x71006f00;
              *(undefined8 *)(iVar26 + (iVar13 + 1) * 0x10 + 8) = 0x71006f00;
              *(undefined8 *)(iVar26 + (iVar13 + 2) * 0x10 + 8) = 0x71006f00;
              *(undefined8 *)(iVar26 + (iVar13 + 3) * 0x10 + 8) = 0x71006f00;
              fVar33 = *(float *)(param_1 + 0x80) * 8.0;
            }
            else {
              iVar27 = (int)unaff_s2;
              iVar31 = (int)unaff_s6;
              fVar33 = *(float *)(param_1 + 0x80) * (24.0 / (float)((iVar31 - iVar27) + -5));
              fStack_1c = *(float *)(param_1 + 0x84) * (24.0 / (float)((iVar31 - iVar27) + -5));
              iVar28 = (int)unaff_s4;
              *(ulong *)(iVar26 + iVar13 * 0x10) =
                   (long)(iVar28 << 4) |
                   CONCAT44((int)(short)((uint)(iVar27 << 4) >> 0x10),iVar27 << 0x14);
              uVar19 = __fixunssfdi(fStack_90 * 16.0);
              lVar25 = __fixunssfdi(fVar35 * 16.0);
              *(ulong *)(iVar26 + iVar13 * 0x10 + 8) = uVar19 | lVar25 << 0x10;
              *(long *)(iVar26 + (iVar13 + 1) * 0x10) =
                   (long)(iVar28 << 4) | (long)(iVar31 << 4) << 0x10;
              uVar12 = __fixunssfdi((fVar35 + fStack_1c * (float)(iVar31 - iVar27)) * 16.0);
              uVar19 = __fixunssfdi(fStack_90 * 16.0);
              *(ulong *)(iVar26 + (iVar13 + 1) * 0x10 + 8) =
                   uVar19 | CONCAT44((int)((ulong)uVar12 >> 0x10),(int)uVar12 << 0x10);
              iVar32 = (int)unaff_s7;
              *(long *)(iVar26 + (iVar13 + 2) * 0x10) =
                   (long)(iVar32 << 4) | (long)(iVar27 << 4) << 0x10;
              uVar19 = __fixunssfdi((fStack_90 + fVar33 * (float)(iVar32 - iVar28)) * 16.0);
              lVar25 = __fixunssfdi(fVar35 * 16.0);
              *(ulong *)(iVar26 + (iVar13 + 2) * 0x10 + 8) = lVar25 << 0x10 | uVar19;
              *(long *)(iVar26 + (iVar13 + 3) * 0x10) =
                   (long)(iVar32 << 4) | (long)(iVar31 << 4) << 0x10;
              uVar19 = __fixunssfdi((fStack_90 + fVar33 * (float)(iVar32 - iVar28)) * 16.0);
              lVar25 = __fixunssfdi((fVar35 + fStack_1c * (float)(iVar31 - iVar27)) * 16.0);
              *(ulong *)(iVar26 + (iVar13 + 3) * 0x10 + 8) = uVar19 | lVar25 << 0x10;
              fVar33 = fVar33 * (float)((iVar32 - iVar28) + -2);
            }
            fStack_90 = fStack_90 + fVar33;
            iVar13 = iVar13 + 4;
          }
        }
        fStack_90 = fStack_90 + *(float *)(param_1 + 0x80) * 8.0;
      }
      iVar14 = iVar13;
    }
    *(int *)(param_1 + 0x54) = iVar26 + iVar14 * 0x10;
    *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfe | bVar1;
  }
  else {
    *(undefined4 *)(param_1 + 0x54) = 0;
    *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfe | bVar1;
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x004faca0  Reset__12TotalHitInfoFv
 * C++: TotalHitInfo::Reset()
 * size: 0xb4 bytes
 * --------------------------------------------------------------------------- */
void Reset__12TotalHitInfoFv(int param_1)

{
  int iVar1;
  
  *(undefined2 *)(param_1 + 0x5c) = 0;
  *(undefined2 *)(param_1 + 0x5e) = 0;
  *(undefined4 *)(param_1 + 0x60) = 0;
  *(undefined4 *)(param_1 + 0x8c) = 0;
  *(undefined4 *)(param_1 + 0x88) = 0;
  for (iVar1 = 0; iVar1 < 0x10; iVar1 = iVar1 + 1) {
    *(undefined1 *)(param_1 + iVar1 * 0x28 + 0x90) = 0;
    *(undefined1 *)(param_1 + iVar1 * 0x28 + 0x94) = 0;
    *(undefined1 *)(param_1 + iVar1 * 0x28 + 0xa4) = 0;
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x004fad60  SetDispData__12TotalHitInfoFPccPccbicbb
 * C++: TotalHitInfo::SetDispData(char *, char, char *, char, bool, int, char, bool, bool)
 * size: 0x2c4 bytes
 * --------------------------------------------------------------------------- */
void SetDispData__12TotalHitInfoFPccPccbicbb
               (int param_1,int param_2,undefined1 param_3,int param_4,undefined1 param_5,
               char param_6,undefined4 param_7,undefined1 param_8,byte param_9,byte param_10)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  while( true ) {
    if (0xf < iVar2) {
      return;
    }
    if ((((*(byte *)(param_1 + iVar2 * 0x28 + 0x90) & 1) == 0) &&
        (-1 < (long)((ulong)*(byte *)(param_1 + iVar2 * 0x28 + 0x90) << 0x3e))) &&
       (-1 < (long)((ulong)*(byte *)(param_1 + iVar2 * 0x28 + 0x90) << 0x3d))) break;
    iVar2 = iVar2 + 1;
  }
  if (param_2 != 0) {
    iVar1 = param_1 + iVar2 * 0x28;
    *(byte *)(iVar1 + 0x90) = *(byte *)(iVar1 + 0x90) & 0xfe | 1;
    strcpy(param_1 + iVar2 * 0x28 + 0x94,param_2);
    *(undefined1 *)(param_1 + iVar2 * 0x28 + 0x91) = param_3;
  }
  if (param_6 == '\x01') {
    iVar1 = param_1 + iVar2 * 0x28;
    *(byte *)(iVar1 + 0x90) = *(byte *)(iVar1 + 0x90) & 0xfb | 4;
    *(undefined4 *)(param_1 + iVar2 * 0x28 + 0xb4) = param_7;
    *(undefined1 *)(param_1 + iVar2 * 0x28 + 0x93) = param_8;
    iVar1 = param_1 + iVar2 * 0x28;
    *(byte *)(iVar1 + 0x90) = *(byte *)(iVar1 + 0x90) & 0xf7 | (param_9 & 1) << 3;
    iVar1 = param_1 + iVar2 * 0x28;
    *(byte *)(iVar1 + 0x90) = *(byte *)(iVar1 + 0x90) & 0xef | (param_10 & 1) << 4;
  }
  if (param_4 == 0) {
    return;
  }
  iVar1 = param_1 + iVar2 * 0x28;
  *(byte *)(iVar1 + 0x90) = *(byte *)(iVar1 + 0x90) & 0xfd | 2;
  strcpy(param_1 + iVar2 * 0x28 + 0xa4,param_4);
  *(undefined1 *)(param_1 + iVar2 * 0x28 + 0x92) = param_5;
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b320  EndSet__12TotalHitInfoFv
 * C++: TotalHitInfo::EndSet()
 * size: 0x30 bytes
 * --------------------------------------------------------------------------- */
void EndSet__12TotalHitInfoFv(int param_1)

{
  (**(code **)(*(int *)(param_1 + 0x14) + 0x30))();
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b460  @24@__dt__12TotalHitInfoFv
 * C++: @24@__dt__12TotalHitInfoFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int * _24___dt__12TotalHitInfoFv(int *param_1,short param_2)

{
  int *piVar1;
  
  piVar1 = param_1 + -6;
  if (piVar1 != (int *)0x0) {
    param_1[-1] = 0x40a4d0;
    param_1[4] = 0x40a4e0;
    param_1[7] = 0x40a4f0;
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
 * JP: 0x0054b470  @44@__dt__12TotalHitInfoFv
 * C++: @44@__dt__12TotalHitInfoFv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int _44___dt__12TotalHitInfoFv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x2c;
  if (iVar1 != 0) {
    *(undefined4 *)(param_1 + -0x18) = 0x40a4d0;
    *(undefined4 *)(param_1 + -4) = 0x40a4e0;
    *(undefined4 *)(param_1 + 8) = 0x40a4f0;
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

