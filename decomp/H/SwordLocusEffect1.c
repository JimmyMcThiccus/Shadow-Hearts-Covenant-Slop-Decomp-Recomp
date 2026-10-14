/* decomp/H/SwordLocusEffect1.c — cleaned Ghidra output (SH2JP_BATTLE.BIN, JP Furokuban, base 0x00430a00).
 * 9 function(s). Types: see types.h. Names/gp globals resolved from symbols/SLPM_602.19.syms. */
#include "types.h"

/* ---------------------------------------------------------------------------
 * JP: 0x0050c2c0  __ct__17SwordLocusEffect1Fiiib
 * C++: SwordLocusEffect1::__ct(int, int, int, bool)
 * size: 0x980 bytes
 * --------------------------------------------------------------------------- */
undefined8
__ct__17SwordLocusEffect1Fiiib
          (undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined4 param_4,char param_5)

{
  undefined8 uVar1;
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  undefined1 (*pauVar7) [16];
  int iVar8;
  int iVar9;
  undefined1 in_vf0 [16];
  undefined1 auVar10 [16];
  undefined1 auVar11 [16];
  undefined1 auVar12 [16];
  undefined4 uStack_80;
  undefined4 uStack_7c;
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined1 auStack_70 [8];
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined1 auStack_50 [8];
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [16];
  undefined1 auStack_20 [16];
  undefined1 auStack_10 [16];
  
  __ct__6BtlEffFii(param_1,param_2,param_3);
  iVar9 = (int)param_1;
  *(undefined4 *)(iVar9 + 0x14) = 0x40a1c0;
  *(undefined4 *)(iVar9 + 0x28) = 0x40a1d0;
  *(undefined4 *)(iVar9 + 0x34) = 0x40a1e0;
  puVar6 = (undefined4 *)(iVar9 + 0x80);
  do {
    *puVar6 = in_zero_lo;
    puVar6[1] = in_zero_hi;
    puVar6[2] = in_zero_udw;
    puVar6[3] = in_register_0000000c;
    puVar6 = puVar6 + 4;
  } while (puVar6 != (undefined4 *)(iVar9 + 0x180));
  puVar6 = (undefined4 *)(iVar9 + 0x180);
  do {
    *puVar6 = in_zero_lo;
    puVar6[1] = in_zero_hi;
    puVar6[2] = in_zero_udw;
    puVar6[3] = in_register_0000000c;
    puVar6 = puVar6 + 4;
  } while (puVar6 != (undefined4 *)(iVar9 + 0x980));
  *(undefined4 *)(iVar9 + 0x5c) = 0;
  *(undefined4 *)(iVar9 + 0x60) = 0;
  *(undefined4 *)(iVar9 + 100) = 0;
  *(undefined4 *)(iVar9 + 0x40) = 0;
  *(int *)(iVar9 + 0x44) = (int)param_2;
  *(int *)(iVar9 + 0x48) = (int)param_3;
  *(undefined4 *)(iVar9 + 0x4c) = 8;
  *(undefined4 *)(iVar9 + 0x6c) = 0;
  *(undefined4 *)(iVar9 + 0x68) = 0;
  *(undefined4 *)(iVar9 + 0x70) = 0;
  *(undefined4 *)(iVar9 + 0x1c) = 0;
  *(undefined4 *)(iVar9 + 0x18) = 0;
  *(undefined4 *)(iVar9 + 0x54) = 0;
  *(undefined4 *)(iVar9 + 0x984) = 0;
  *(undefined4 *)(iVar9 + 0x980) = 0;
  *(undefined4 *)(iVar9 + 0x98c) = param_4;
  *(char *)(iVar9 + 0x990) = param_5;
  *(undefined4 *)(iVar9 + 0x994) = 0;
  if (*(int *)(iGpffff86b4 + *(int *)(iVar9 + 0x48) * 0x4f0 + 0x500) != 0) {
    *(int *)(iVar9 + 0x994) =
         *(char *)(*(int *)(iGpffff86b4 + *(int *)(iVar9 + 0x48) * 0x4f0 + 0x500) + 4) + -0x30;
  }
  if (param_5 == '\0') {
    iVar2 = GetRegDat__9RegDatApiFiii(0x3a,*(undefined4 *)
                                  (iGpffff86b4 + *(int *)(iVar9 + 0x48) * 0x4f0 + 0x55c),
                            0xffffffffffffffff);
    iVar2 = *(int *)(*(short *)(iVar2 + 0x14) * 4 + 0x651180);
    iVar8 = *(int *)(iVar9 + 0x994);
    if (-1 < *(short *)(iGpffff86b4 + *(int *)(iVar9 + 0x48) * 0x4f0 + 400)) {
      iVar8 = iVar8 + *(short *)(iGpffff86b4 + *(int *)(iVar9 + 0x48) * 0x4f0 + 400);
    }
    auVar10 = _vmr32(in_vf0);
    auVar11 = _vmr32(auVar10);
    auVar12 = _vmr32(auVar11);
    auStack_10 = _sqc2(in_vf0);
    auStack_20 = _sqc2(auVar10);
    auStack_30 = _sqc2(auVar11);
    auStack_40 = _sqc2(auVar12);
    switch(*(undefined2 *)(iVar2 + iVar8 * 0x1c)) {
    case 0:
      pauVar7 = (undefined1 (*) [16])
                (*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar9 + 0x48) * 0x4f0 + 0x144) + 0x30) +
                 (uint)*(ushort *)(iVar2 + iVar8 * 0x1c + 2) * 0x1f0 + (bGpffff8340 & 1) * 0x40);
      auStack_40 = *pauVar7;
      auStack_30 = pauVar7[1];
      auStack_20 = pauVar7[2];
      auStack_10 = pauVar7[3];
      break;
    case 1:
      pauVar7 = (undefined1 (*) [16])
                (*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar9 + 0x48) * 0x4f0 + 0x144) +
                                  0x52c) + 0x30) +
                 (uint)*(ushort *)(iVar2 + iVar8 * 0x1c + 2) * 0x1f0 + (bGpffff8340 & 1) * 0x40);
      auStack_40 = *pauVar7;
      auStack_30 = pauVar7[1];
      auStack_20 = pauVar7[2];
      auStack_10 = pauVar7[3];
      break;
    case 2:
      pauVar7 = (undefined1 (*) [16])
                (*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar9 + 0x48) * 0x4f0 + 0x144) +
                                  0x530) + 0x30) +
                 (uint)*(ushort *)(iVar2 + iVar8 * 0x1c + 2) * 0x1f0 + (bGpffff8340 & 1) * 0x40);
      auStack_40 = *pauVar7;
      auStack_30 = pauVar7[1];
      auStack_20 = pauVar7[2];
      auStack_10 = pauVar7[3];
      break;
    case 3:
      pauVar7 = (undefined1 (*) [16])
                (*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar9 + 0x48) * 0x4f0 + 0x144) + 0x30) +
                 (uint)*(byte *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar9 + 0x48) * 0x4f0 +
                                                  0x144) + 0xe4) +
                                (uint)*(ushort *)(iVar2 + iVar8 * 0x1c + 2) * 0x110) * 0x1f0 +
                (bGpffff8340 & 1) * 0x40);
      auStack_40 = *pauVar7;
      auStack_30 = pauVar7[1];
      auStack_20 = pauVar7[2];
      auStack_10 = pauVar7[3];
      break;
    case 4:
      pauVar7 = (undefined1 (*) [16])
                (*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar9 + 0x48) * 0x4f0 + 0x144) +
                                  0x52c) + 0x30) +
                 (uint)*(byte *)(*(int *)(*(int *)(*(int *)(iGpffff86b4 +
                                                            *(int *)(iVar9 + 0x48) * 0x4f0 + 0x144)
                                                  + 0x52c) + 0xe4) +
                                (uint)*(ushort *)(iVar2 + iVar8 * 0x1c + 2) * 0x110) * 0x1f0 +
                (bGpffff8340 & 1) * 0x40);
      auStack_40 = *pauVar7;
      auStack_30 = pauVar7[1];
      auStack_20 = pauVar7[2];
      auStack_10 = pauVar7[3];
      break;
    case 5:
      pauVar7 = (undefined1 (*) [16])
                (*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(iVar9 + 0x48) * 0x4f0 + 0x144) +
                                  0x530) + 0x30) +
                 (uint)*(byte *)(*(int *)(*(int *)(*(int *)(iGpffff86b4 +
                                                            *(int *)(iVar9 + 0x48) * 0x4f0 + 0x144)
                                                  + 0x530) + 0xe4) +
                                (uint)*(ushort *)(iVar2 + iVar8 * 0x1c + 2) * 0x110) * 0x1f0 +
                (bGpffff8340 & 1) * 0x40);
      auStack_40 = *pauVar7;
      auStack_30 = pauVar7[1];
      auStack_20 = pauVar7[2];
      auStack_10 = pauVar7[3];
    }
    uStack_58 = *(undefined4 *)(iVar2 + iVar8 * 0x1c + 0xc);
    uStack_5c = *(undefined4 *)(iVar2 + iVar8 * 0x1c + 8);
    uStack_60 = *(undefined4 *)(iVar2 + iVar8 * 0x1c + 4);
    uStack_54 = 0x3f800000;
    ApplyMatrix__6MatrixCFRC7FVector(auStack_50,auStack_40,&uStack_60);
    iVar3 = iVar9 + *(int *)(iVar9 + 0x6c) * 0x20;
    *(int *)(iVar3 + 0x80) = auStack_50._0_4_;
    *(int *)(iVar3 + 0x84) = auStack_50._4_4_;
    *(undefined4 *)(iVar3 + 0x88) = uStack_48;
    *(undefined4 *)(iVar3 + 0x8c) = uStack_44;
    uStack_78 = *(undefined4 *)(iVar2 + iVar8 * 0x1c + 0x18);
    uStack_7c = *(undefined4 *)(iVar2 + iVar8 * 0x1c + 0x14);
    uStack_80 = *(undefined4 *)(iVar2 + iVar8 * 0x1c + 0x10);
    uStack_74 = 0x3f800000;
    ApplyMatrix__6MatrixCFRC7FVector(auStack_70,auStack_40,&uStack_80);
    iVar2 = iVar9 + *(int *)(iVar9 + 0x6c) * 0x20;
    *(int *)(iVar2 + 0x90) = auStack_70._0_4_;
    *(int *)(iVar2 + 0x94) = auStack_70._4_4_;
    *(undefined4 *)(iVar2 + 0x98) = uStack_68;
    *(undefined4 *)(iVar2 + 0x9c) = uStack_64;
  }
  else {
    iVar2 = iGpffff86b4 + *(int *)(iVar9 + 0x48) * 0x4f0;
    iVar8 = iVar9 + *(int *)(iVar9 + 0x6c) * 0x20;
    uVar1 = *(undefined8 *)(iVar2 + 0x460);
    uVar4 = *(undefined4 *)(iVar2 + 0x468);
    uVar5 = *(undefined4 *)(iVar2 + 0x46c);
    *(int *)(iVar8 + 0x80) = (int)uVar1;
    *(int *)(iVar8 + 0x84) = (int)((ulong)uVar1 >> 0x20);
    *(undefined4 *)(iVar8 + 0x88) = uVar4;
    *(undefined4 *)(iVar8 + 0x8c) = uVar5;
    iVar2 = iGpffff86b4 + *(int *)(iVar9 + 0x48) * 0x4f0;
    iVar8 = iVar9 + *(int *)(iVar9 + 0x6c) * 0x20;
    uVar1 = *(undefined8 *)(iVar2 + 0x470);
    uVar4 = *(undefined4 *)(iVar2 + 0x478);
    uVar5 = *(undefined4 *)(iVar2 + 0x47c);
    *(int *)(iVar8 + 0x90) = (int)uVar1;
    *(int *)(iVar8 + 0x94) = (int)((ulong)uVar1 >> 0x20);
    *(undefined4 *)(iVar8 + 0x98) = uVar4;
    *(undefined4 *)(iVar8 + 0x9c) = uVar5;
  }
  *(int *)(iVar9 + 0x6c) = *(int *)(iVar9 + 0x6c) + 1;
  *(int *)(iVar9 + 0x68) = *(int *)(iVar9 + 0x68) + 1;
  Entry__7CPollerFP7CPolObjib(iGpffff858c + 0x48,param_1,0x80,0);
  BtlEffEntry__7CBattleFiP6BtlEff(iGpffff86b4,*(undefined4 *)(iVar9 + 0x48),param_1);
  return param_1;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0050cc40  __dt__17SwordLocusEffect1Fv
 * C++: SwordLocusEffect1::__dt()
 * size: 0x154 bytes
 * --------------------------------------------------------------------------- */
int __dt__17SwordLocusEffect1Fv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 0x14) = 0x40a1c0;
    *(undefined4 *)(param_1 + 0x28) = 0x40a1d0;
    *(undefined4 *)(param_1 + 0x34) = 0x40a1e0;
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
 * JP: 0x0050cda0  Destruct__17SwordLocusEffect1Fv
 * C++: SwordLocusEffect1::Destruct()
 * size: 0xc8 bytes
 * --------------------------------------------------------------------------- */
void Destruct__17SwordLocusEffect1Fv(int param_1)

{
  int iVar1;
  
  BtlEffRelease__7CBattleFiP6BtlEff(uGpffff86b4,*(undefined4 *)(param_1 + 0x48),param_1);
  if ((long)((ulong)*(byte *)(param_1 + 0x40) << 0x3e) < 0) {
    iVar1 = param_1;
    if (param_1 != 0) {
      iVar1 = param_1 + 0x18;
    }
    ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,iVar1);
  }
  *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfd;
  Dispose__7CPollerFP7CPolObj(iGpffff858c + 0x48,param_1);
  (**(code **)(*(int *)(param_1 + 0x34) + 0xc))();
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0050ce70  Polling__17SwordLocusEffect1Fv
 * C++: SwordLocusEffect1::Polling()
 * size: 0xdc8 bytes
 * --------------------------------------------------------------------------- */
undefined4 Polling__17SwordLocusEffect1Fv(int param_1)

{
  undefined8 uVar1;
  undefined1 auVar2 [16];
  undefined1 auVar3 [16];
  undefined1 auVar4 [16];
  undefined1 auVar5 [16];
  undefined1 auVar6 [16];
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  int iVar7;
  int iVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined1 (*pauVar11) [16];
  int iVar12;
  float fVar13;
  undefined1 in_vf0 [16];
  undefined1 auVar14 [16];
  undefined1 auVar15 [16];
  undefined1 auVar16 [16];
  undefined1 auStack_280 [16];
  undefined1 auStack_270 [16];
  undefined1 auStack_260 [16];
  undefined1 auStack_250 [16];
  undefined1 auStack_240 [16];
  undefined1 auStack_230 [16];
  undefined1 auStack_220 [8];
  undefined4 uStack_218;
  undefined4 uStack_214;
  undefined1 auStack_210 [8];
  undefined4 uStack_208;
  undefined4 uStack_204;
  undefined1 auStack_200 [16];
  undefined1 auStack_1f0 [8];
  undefined4 uStack_1e8;
  undefined4 uStack_1e4;
  undefined1 auStack_1e0 [8];
  undefined4 uStack_1d8;
  undefined4 uStack_1d4;
  undefined1 auStack_1d0 [16];
  undefined1 auStack_1c0 [8];
  undefined4 uStack_1b8;
  undefined4 uStack_1b4;
  undefined1 auStack_1b0 [8];
  undefined4 uStack_1a8;
  undefined4 uStack_1a4;
  undefined4 uStack_1a0;
  undefined4 uStack_19c;
  undefined4 uStack_198;
  undefined4 uStack_194;
  undefined1 auStack_190 [8];
  undefined4 uStack_188;
  undefined4 uStack_184;
  undefined4 uStack_180;
  undefined4 uStack_17c;
  undefined4 uStack_178;
  undefined4 uStack_174;
  undefined1 auStack_170 [8];
  undefined4 uStack_168;
  undefined4 uStack_164;
  undefined4 auStack_160 [7];
  undefined4 uStack_144;
  undefined4 auStack_e0 [7];
  undefined4 uStack_c4;
  undefined1 auStack_60 [16];
  undefined1 auStack_50 [16];
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [16];
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined1 auStack_10 [8];
  undefined1 auStack_8 [8];
  
  fVar13 = *(float *)(iGpffff86b4 + 0x38);
  if ((*(byte *)(iGpffff86b4 + 0x24) & 1) != 0) {
    fVar13 = 0.0;
  }
  if (fVar13 != 0.0) {
    iVar12 = GetRegDat__9RegDatApiFiii(0x3a,*(undefined4 *)
                                   (iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x55c),
                             0xffffffffffffffff);
    iVar12 = *(int *)(*(short *)(iVar12 + 0x14) * 4 + 0x651180);
    iVar7 = *(int *)(param_1 + 0x994);
    if (-1 < *(short *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 400)) {
      iVar7 = iVar7 + *(short *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 400);
    }
    auVar14 = _vmr32(in_vf0);
    auVar15 = _vmr32(auVar14);
    auVar16 = _vmr32(auVar15);
    auStack_30 = _sqc2(in_vf0);
    auStack_40 = _sqc2(auVar14);
    auStack_50 = _sqc2(auVar15);
    auStack_60 = _sqc2(auVar16);
    switch(*(undefined2 *)(iVar12 + iVar7 * 0x1c)) {
    case 0:
      pauVar11 = (undefined1 (*) [16])
                 (*(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x144) + 0x30)
                  + (uint)*(ushort *)(iVar12 + iVar7 * 0x1c + 2) * 0x1f0 + (bGpffff8340 & 1) * 0x40)
      ;
      auStack_60 = *pauVar11;
      auStack_50 = pauVar11[1];
      auStack_40 = pauVar11[2];
      auStack_30 = pauVar11[3];
      break;
    case 1:
      pauVar11 = (undefined1 (*) [16])
                 (*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x144)
                                   + 0x52c) + 0x30) +
                  (uint)*(ushort *)(iVar12 + iVar7 * 0x1c + 2) * 0x1f0 + (bGpffff8340 & 1) * 0x40);
      auStack_60 = *pauVar11;
      auStack_50 = pauVar11[1];
      auStack_40 = pauVar11[2];
      auStack_30 = pauVar11[3];
      break;
    case 2:
      pauVar11 = (undefined1 (*) [16])
                 (*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x144)
                                   + 0x530) + 0x30) +
                  (uint)*(ushort *)(iVar12 + iVar7 * 0x1c + 2) * 0x1f0 + (bGpffff8340 & 1) * 0x40);
      auStack_60 = *pauVar11;
      auStack_50 = pauVar11[1];
      auStack_40 = pauVar11[2];
      auStack_30 = pauVar11[3];
      break;
    case 3:
      pauVar11 = (undefined1 (*) [16])
                 (*(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x144) + 0x30)
                  + (uint)*(byte *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0
                                                     + 0x144) + 0xe4) +
                                   (uint)*(ushort *)(iVar12 + iVar7 * 0x1c + 2) * 0x110) * 0x1f0 +
                 (bGpffff8340 & 1) * 0x40);
      auStack_60 = *pauVar11;
      auStack_50 = pauVar11[1];
      auStack_40 = pauVar11[2];
      auStack_30 = pauVar11[3];
      break;
    case 4:
      pauVar11 = (undefined1 (*) [16])
                 (*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x144)
                                   + 0x52c) + 0x30) +
                  (uint)*(byte *)(*(int *)(*(int *)(*(int *)(iGpffff86b4 +
                                                             *(int *)(param_1 + 0x48) * 0x4f0 +
                                                            0x144) + 0x52c) + 0xe4) +
                                 (uint)*(ushort *)(iVar12 + iVar7 * 0x1c + 2) * 0x110) * 0x1f0 +
                 (bGpffff8340 & 1) * 0x40);
      auStack_60 = *pauVar11;
      auStack_50 = pauVar11[1];
      auStack_40 = pauVar11[2];
      auStack_30 = pauVar11[3];
      break;
    case 5:
      pauVar11 = (undefined1 (*) [16])
                 (*(int *)(*(int *)(*(int *)(iGpffff86b4 + *(int *)(param_1 + 0x48) * 0x4f0 + 0x144)
                                   + 0x530) + 0x30) +
                  (uint)*(byte *)(*(int *)(*(int *)(*(int *)(iGpffff86b4 +
                                                             *(int *)(param_1 + 0x48) * 0x4f0 +
                                                            0x144) + 0x530) + 0xe4) +
                                 (uint)*(ushort *)(iVar12 + iVar7 * 0x1c + 2) * 0x110) * 0x1f0 +
                 (bGpffff8340 & 1) * 0x40);
      auStack_60 = *pauVar11;
      auStack_50 = pauVar11[1];
      auStack_40 = pauVar11[2];
      auStack_30 = pauVar11[3];
    }
    uStack_178 = *(undefined4 *)(iVar12 + iVar7 * 0x1c + 0xc);
    uStack_17c = *(undefined4 *)(iVar12 + iVar7 * 0x1c + 8);
    uStack_180 = *(undefined4 *)(iVar12 + iVar7 * 0x1c + 4);
    uStack_174 = 0x3f800000;
    ApplyMatrix__6MatrixCFRC7FVector(auStack_170,auStack_60,&uStack_180);
    iVar8 = param_1 + *(int *)(param_1 + 0x6c) * 0x20;
    *(int *)(iVar8 + 0x80) = auStack_170._0_4_;
    *(int *)(iVar8 + 0x84) = auStack_170._4_4_;
    *(undefined4 *)(iVar8 + 0x88) = uStack_168;
    *(undefined4 *)(iVar8 + 0x8c) = uStack_164;
    uStack_198 = *(undefined4 *)(iVar12 + iVar7 * 0x1c + 0x18);
    uStack_19c = *(undefined4 *)(iVar12 + iVar7 * 0x1c + 0x14);
    uStack_1a0 = *(undefined4 *)(iVar12 + iVar7 * 0x1c + 0x10);
    uStack_194 = 0x3f800000;
    ApplyMatrix__6MatrixCFRC7FVector(auStack_190,auStack_60,&uStack_1a0);
    iVar12 = param_1 + *(int *)(param_1 + 0x6c) * 0x20;
    *(int *)(iVar12 + 0x90) = auStack_190._0_4_;
    *(int *)(iVar12 + 0x94) = auStack_190._4_4_;
    *(undefined4 *)(iVar12 + 0x98) = uStack_188;
    *(undefined4 *)(iVar12 + 0x9c) = uStack_184;
    *(int *)(param_1 + 0x6c) = *(int *)(param_1 + 0x6c) + 1;
    if (7 < *(int *)(param_1 + 0x6c)) {
      *(undefined4 *)(param_1 + 0x6c) = 0;
    }
    *(int *)(param_1 + 0x68) = *(int *)(param_1 + 0x68) + 1;
    if (8 < *(int *)(param_1 + 0x68)) {
      *(undefined4 *)(param_1 + 0x68) = 8;
    }
  }
  iVar12 = *(int *)(param_1 + 0x6c);
  auStack_160[0] = in_zero_lo;
  auStack_160[1] = in_zero_hi;
  auStack_160[2] = in_zero_udw;
  auStack_160[3] = in_register_0000000c;
  auStack_160[4] = in_zero_lo;
  auStack_160[5] = in_zero_hi;
  auStack_160[6] = in_zero_udw;
  uStack_144 = in_register_0000000c;
  auStack_e0[0] = in_zero_lo;
  auStack_e0[1] = in_zero_hi;
  auStack_e0[2] = in_zero_udw;
  auStack_e0[3] = in_register_0000000c;
  auStack_e0[4] = in_zero_lo;
  auStack_e0[5] = in_zero_hi;
  auStack_e0[6] = in_zero_udw;
  uStack_c4 = in_register_0000000c;
  for (iVar7 = 0; iVar7 < *(int *)(param_1 + 0x68); iVar7 = iVar7 + 1) {
    iVar12 = iVar12 + -1;
    if (iVar12 < 0) {
      iVar12 = 7;
    }
    iVar8 = param_1 + iVar12 * 0x20;
    uVar1 = *(undefined8 *)(iVar8 + 0x80);
    uVar9 = *(undefined4 *)(iVar8 + 0x88);
    uVar10 = *(undefined4 *)(iVar8 + 0x8c);
    auStack_e0[iVar7 * 4] = (int)uVar1;
    auStack_e0[iVar7 * 4 + 1] = (int)((ulong)uVar1 >> 0x20);
    auStack_e0[iVar7 * 4 + 2] = uVar9;
    auStack_e0[iVar7 * 4 + 3] = uVar10;
    iVar8 = param_1 + iVar12 * 0x20;
    uVar1 = *(undefined8 *)(iVar8 + 0x90);
    uVar9 = *(undefined4 *)(iVar8 + 0x98);
    uVar10 = *(undefined4 *)(iVar8 + 0x9c);
    auStack_160[iVar7 * 4] = (int)uVar1;
    auStack_160[iVar7 * 4 + 1] = (int)((ulong)uVar1 >> 0x20);
    auStack_160[iVar7 * 4 + 2] = uVar9;
    auStack_160[iVar7 * 4 + 3] = uVar10;
  }
  if (*(int *)(param_1 + 0x5c) == 0) {
    iVar12 = (*(int *)(param_1 + 0x68) + -1) * 8 + 1;
    *(int *)(param_1 + 0x70) = iVar12;
  }
  else {
    *(float *)(param_1 + 0x988) = *(float *)(param_1 + 0x988) + fVar13;
    while ((1 < *(int *)(param_1 + 100) && (0.004166667 < *(float *)(param_1 + 0x988)))) {
      *(float *)(param_1 + 0x988) = *(float *)(param_1 + 0x988) - 0.004166667;
      *(int *)(param_1 + 100) = *(int *)(param_1 + 100) + -1;
    }
    if (*(int *)(param_1 + 100) < 2) {
      BtlEffRelease__7CBattleFiP6BtlEff(iGpffff86b4,*(undefined4 *)(param_1 + 0x48),param_1);
      if ((long)((ulong)*(byte *)(param_1 + 0x40) << 0x3e) < 0) {
        iVar12 = param_1;
        if (param_1 != 0) {
          iVar12 = param_1 + 0x18;
        }
        ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,iVar12);
      }
      *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfd;
      (**(code **)(*(int *)(param_1 + 0x34) + 0xc))();
      return 1;
    }
    iVar12 = (*(int *)(param_1 + 0x68) + -1) * 8 + 1;
    *(undefined4 *)(param_1 + 0x70) = *(undefined4 *)(param_1 + 100);
  }
  if (*(int *)(param_1 + 0x68) == 1) {
    *(undefined4 *)(param_1 + 0x180) = auStack_e0[0];
    *(undefined4 *)(param_1 + 0x184) = auStack_e0[1];
    *(undefined4 *)(param_1 + 0x188) = auStack_e0[2];
    *(undefined4 *)(param_1 + 0x18c) = auStack_e0[3];
    *(undefined4 *)(param_1 + 400) = auStack_160[0];
    *(undefined4 *)(param_1 + 0x194) = auStack_160[1];
    *(undefined4 *)(param_1 + 0x198) = auStack_160[2];
    *(undefined4 *)(param_1 + 0x19c) = auStack_160[3];
  }
  else if (*(int *)(param_1 + 0x68) == 2) {
    *(undefined4 *)(param_1 + 0x180) = auStack_e0[0];
    *(undefined4 *)(param_1 + 0x184) = auStack_e0[1];
    *(undefined4 *)(param_1 + 0x188) = auStack_e0[2];
    *(undefined4 *)(param_1 + 0x18c) = auStack_e0[3];
    *(undefined4 *)(param_1 + 400) = auStack_160[0];
    *(undefined4 *)(param_1 + 0x194) = auStack_160[1];
    *(undefined4 *)(param_1 + 0x198) = auStack_160[2];
    *(undefined4 *)(param_1 + 0x19c) = auStack_160[3];
    auVar14._4_4_ = auStack_e0[1];
    auVar14._0_4_ = auStack_e0[0];
    auVar14._8_4_ = auStack_e0[2];
    auVar14._12_4_ = auStack_e0[3];
    auVar14 = _lqc2(auVar14);
    auVar15._4_4_ = auStack_e0[5];
    auVar15._0_4_ = auStack_e0[4];
    auVar15._8_4_ = auStack_e0[6];
    auVar15._12_4_ = uStack_c4;
    auVar15 = _lqc2(auVar15);
    auVar14 = _vsub(auVar14,auVar15);
    auStack_230 = _sqc2(auVar14);
    __ct__7FVectorFRC7FVector(auStack_1b0,auStack_230);
    uStack_20 = auStack_1b0._0_4_;
    uStack_1c = auStack_1b0._4_4_;
    uStack_18 = uStack_1a8;
    uStack_14 = uStack_1a4;
    for (iVar12 = 1; iVar12 < 8; iVar12 = iVar12 + 1) {
      iVar7 = iVar12;
      if (iVar12 < 0) {
        iVar7 = iVar12 + 7;
      }
      auVar5._4_4_ = uStack_1c;
      auVar5._0_4_ = uStack_20;
      auVar5._8_4_ = uStack_18;
      auVar5._12_4_ = uStack_14;
      auVar14 = _lqc2(auVar5);
      auVar15 = _qmtc2((float)(iVar7 >> 3));
      auVar14 = _vmulbc(auVar14,auVar15);
      auStack_270 = _sqc2(auVar14);
      __ct__7FVectorFRC7FVector(auStack_1d0,auStack_270);
      auVar16._4_4_ = auStack_e0[5];
      auVar16._0_4_ = auStack_e0[4];
      auVar16._8_4_ = auStack_e0[6];
      auVar16._12_4_ = uStack_c4;
      auVar14 = _lqc2(auVar16);
      auVar15 = _lqc2(auStack_1d0);
      auVar14 = _vadd(auVar14,auVar15);
      auStack_240 = _sqc2(auVar14);
      __ct__7FVectorFRC7FVector(auStack_1c0,auStack_240);
      iVar7 = param_1 + iVar12 * 0x20;
      *(int *)(iVar7 + 0x180) = auStack_1c0._0_4_;
      *(int *)(iVar7 + 0x184) = auStack_1c0._4_4_;
      *(undefined4 *)(iVar7 + 0x188) = uStack_1b8;
      *(undefined4 *)(iVar7 + 0x18c) = uStack_1b4;
    }
    auVar2._4_4_ = auStack_160[1];
    auVar2._0_4_ = auStack_160[0];
    auVar2._8_4_ = auStack_160[2];
    auVar2._12_4_ = auStack_160[3];
    auVar14 = _lqc2(auVar2);
    auVar3._4_4_ = auStack_160[5];
    auVar3._0_4_ = auStack_160[4];
    auVar3._8_4_ = auStack_160[6];
    auVar3._12_4_ = uStack_144;
    auVar15 = _lqc2(auVar3);
    auVar14 = _vsub(auVar14,auVar15);
    auStack_250 = _sqc2(auVar14);
    __ct__7FVectorFRC7FVector(auStack_1e0,auStack_250);
    uStack_20 = auStack_1e0._0_4_;
    uStack_1c = auStack_1e0._4_4_;
    uStack_18 = uStack_1d8;
    uStack_14 = uStack_1d4;
    for (iVar12 = 1; iVar12 < 8; iVar12 = iVar12 + 1) {
      iVar7 = iVar12;
      if (iVar12 < 0) {
        iVar7 = iVar12 + 7;
      }
      auVar6._4_4_ = uStack_1c;
      auVar6._0_4_ = uStack_20;
      auVar6._8_4_ = uStack_18;
      auVar6._12_4_ = uStack_14;
      auVar14 = _lqc2(auVar6);
      auVar15 = _qmtc2((float)(iVar7 >> 3));
      auVar14 = _vmulbc(auVar14,auVar15);
      auStack_280 = _sqc2(auVar14);
      __ct__7FVectorFRC7FVector(auStack_200,auStack_280);
      auVar4._4_4_ = auStack_e0[5];
      auVar4._0_4_ = auStack_e0[4];
      auVar4._8_4_ = auStack_e0[6];
      auVar4._12_4_ = uStack_c4;
      auVar14 = _lqc2(auVar4);
      auVar15 = _lqc2(auStack_200);
      auVar14 = _vadd(auVar14,auVar15);
      auStack_260 = _sqc2(auVar14);
      __ct__7FVectorFRC7FVector(auStack_1f0,auStack_260);
      iVar7 = param_1 + iVar12 * 0x20;
      *(int *)(iVar7 + 400) = auStack_1f0._0_4_;
      *(int *)(iVar7 + 0x194) = auStack_1f0._4_4_;
      *(undefined4 *)(iVar7 + 0x198) = uStack_1e8;
      *(undefined4 *)(iVar7 + 0x19c) = uStack_1e4;
    }
    *(undefined4 *)(param_1 + 0x280) = auStack_e0[4];
    *(undefined4 *)(param_1 + 0x284) = auStack_e0[5];
    *(undefined4 *)(param_1 + 0x288) = auStack_e0[6];
    *(undefined4 *)(param_1 + 0x28c) = uStack_c4;
    *(undefined4 *)(param_1 + 0x290) = auStack_160[4];
    *(undefined4 *)(param_1 + 0x294) = auStack_160[5];
    *(undefined4 *)(param_1 + 0x298) = auStack_160[6];
    *(undefined4 *)(param_1 + 0x29c) = uStack_144;
  }
  else {
    __ct__9GsxSplineFv(auStack_8);
    __ct__9GsxSplineFv(auStack_10);
    Create__9GsxSplineFUiUiP7FVector(auStack_8,*(undefined4 *)(param_1 + 0x68),0,auStack_e0);
    Create__9GsxSplineFUiUiP7FVector(auStack_10,*(undefined4 *)(param_1 + 0x68),0,auStack_160);
    fVar13 = 0.0;
    for (iVar7 = 0; iVar7 < *(int *)(param_1 + 0x70); iVar7 = iVar7 + 1) {
      GetPosition__9GsxSplineFf(fVar13,auStack_210,auStack_8);
      iVar8 = param_1 + iVar7 * 0x20;
      *(int *)(iVar8 + 0x180) = auStack_210._0_4_;
      *(int *)(iVar8 + 0x184) = auStack_210._4_4_;
      *(undefined4 *)(iVar8 + 0x188) = uStack_208;
      *(undefined4 *)(iVar8 + 0x18c) = uStack_204;
      GetPosition__9GsxSplineFf(fVar13,auStack_220,auStack_10);
      iVar8 = param_1 + iVar7 * 0x20;
      *(int *)(iVar8 + 400) = auStack_220._0_4_;
      *(int *)(iVar8 + 0x194) = auStack_220._4_4_;
      *(undefined4 *)(iVar8 + 0x198) = uStack_218;
      *(undefined4 *)(iVar8 + 0x19c) = uStack_214;
      fVar13 = fVar13 + 1.0 / (float)(iVar12 + -1);
      if (1.0 < fVar13) {
        fVar13 = 1.0;
      }
    }
    Release__9GsxSplineFv(auStack_8);
    Release__9GsxSplineFv(auStack_10);
    __dt__9GsxSplineFv(auStack_10,0xffffffffffffffff);
    __dt__9GsxSplineFv(auStack_8,0xffffffffffffffff);
  }
  return 0;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0050dc40  MakePacket__17SwordLocusEffect1Fv
 * C++: SwordLocusEffect1::MakePacket()
 * size: 0x1004 bytes
 * --------------------------------------------------------------------------- */
/* WARNING: Removing unreachable block (ram,0x0050e0a0) */
/* WARNING: Removing unreachable block (ram,0x0050df7c) */
/* WARNING: Removing unreachable block (ram,0x0050de08) */
/* WARNING: Removing unreachable block (ram,0x0050e000) */
/* WARNING: Removing unreachable block (ram,0x0050e174) */
/* WARNING: Removing unreachable block (ram,0x0050dea8) */

void MakePacket__17SwordLocusEffect1Fv(int param_1)

{
  bool bVar1;
  undefined4 *puVar2;
  bool bVar3;
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  undefined4 uVar4;
  undefined8 uVar5;
  long lVar6;
  long lVar7;
  undefined8 in_a1_udw;
  undefined8 uVar10;
  undefined1 auVar8 [16];
  undefined1 auVar9 [16];
  ulong *puVar11;
  uint uVar12;
  int iVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  undefined1 auVar18 [16];
  undefined1 auStack_14e0 [16];
  undefined1 auStack_14d0 [16];
  undefined1 auStack_14c0 [8];
  undefined4 uStack_14b8;
  undefined4 uStack_14b4;
  undefined1 auStack_14b0 [8];
  undefined4 uStack_14a8;
  undefined4 uStack_14a4;
  int aiStack_14a0 [6];
  int iStack_1488;
  int iStack_1484;
  int aiStack_1480 [504];
  undefined4 auStack_ca0 [512];
  undefined4 auStack_4a0 [16];
  undefined4 auStack_460 [16];
  undefined4 uStack_420;
  undefined4 uStack_41c;
  undefined4 uStack_418;
  undefined4 uStack_414;
  float afStack_410 [64];
  float afStack_310 [64];
  float afStack_210 [64];
  float afStack_110 [65];
  float fStack_c;
  float fStack_8;
  float fStack_4;
  
  fVar16 = 0.0;
  fVar17 = 0.0;
  uStack_420 = in_zero_lo;
  uStack_41c = in_zero_hi;
  uStack_418 = in_zero_udw;
  uStack_414 = in_register_0000000c;
  for (iVar13 = 0; iVar13 < *(int *)(param_1 + 0x70) + -1; iVar13 = iVar13 + 1) {
    auVar9 = _lqc2(*(undefined1 (*) [16])(param_1 + (iVar13 + 1) * 0x20 + 0x180));
    auVar18 = _lqc2(*(undefined1 (*) [16])(param_1 + iVar13 * 0x20 + 0x180));
    auVar9 = _vsub(auVar9,auVar18);
    auStack_14d0 = _sqc2(auVar9);
    __ct__7FVectorFRC7FVector(auStack_14b0,auStack_14d0);
    uStack_420 = auStack_14b0._0_4_;
    uStack_41c = auStack_14b0._4_4_;
    uStack_418 = uStack_14a8;
    uStack_414 = uStack_14a4;
    fVar14 = (float)Length__7FVectorCFv(&uStack_420);
    afStack_110[iVar13] = fVar14;
    fVar16 = fVar16 + afStack_110[iVar13];
    auVar9 = _lqc2(*(undefined1 (*) [16])(param_1 + (iVar13 + 1) * 0x20 + 400));
    auVar18 = _lqc2(*(undefined1 (*) [16])(param_1 + iVar13 * 0x20 + 400));
    auVar9 = _vsub(auVar9,auVar18);
    auStack_14e0 = _sqc2(auVar9);
    __ct__7FVectorFRC7FVector(auStack_14c0,auStack_14e0);
    uStack_420 = auStack_14c0._0_4_;
    uStack_41c = auStack_14c0._4_4_;
    uStack_418 = uStack_14b8;
    uStack_414 = uStack_14b4;
    fVar14 = (float)Length__7FVectorCFv(&uStack_420);
    afStack_210[iVar13] = fVar14;
    fVar17 = fVar17 + afStack_210[iVar13];
  }
  afStack_310[0] = 0.0;
  afStack_410[0] = 0.0;
  fVar14 = 0.0;
  fVar15 = 0.0;
  if (*(int *)(param_1 + 0x98c) == 0) {
    for (iVar13 = 0; iVar13 < *(int *)(param_1 + 0x70) + -1; iVar13 = iVar13 + 1) {
      fVar14 = fVar14 + afStack_110[iVar13];
      afStack_310[iVar13 + 1] =
           ((float)*(ushort *)(*(int *)(iGpffff86b4 + 0x4254) + 2) * (fVar14 / fVar16)) /
           (float)(1 << (uint)(((ulong)*(byte *)(*(int *)(iGpffff86b4 + 0x4254) + 0x53) << 0x3a) >>
                              0x3c));
      fVar15 = fVar15 + afStack_210[iVar13];
      afStack_410[iVar13 + 1] =
           ((float)*(ushort *)(*(int *)(iGpffff86b4 + 0x4254) + 2) * (fVar15 / fVar17)) /
           (float)(1 << (uint)(((ulong)*(byte *)(*(int *)(iGpffff86b4 + 0x4254) + 0x53) << 0x3a) >>
                              0x3c));
    }
    fVar16 = (float)*(ushort *)(*(int *)(iGpffff86b4 + 0x4254) + 4) /
             (float)(1 << (uint)((ulong)(*(long *)(*(int *)(iGpffff86b4 + 0x4254) + 0x50) << 0x1e)
                                >> 0x3c));
  }
  else {
    for (iVar13 = 0; iVar13 < *(int *)(param_1 + 0x70) + -1; iVar13 = iVar13 + 1) {
      fVar14 = fVar14 + afStack_110[iVar13];
      afStack_310[iVar13 + 1] =
           ((float)*(ushort *)(*(int *)(iGpffff86b4 + 0x4300) + 2) * (fVar14 / fVar16)) /
           (float)(1 << (uint)(((ulong)*(byte *)(*(int *)(iGpffff86b4 + 0x4300) + 0x53) << 0x3a) >>
                              0x3c));
      fVar15 = fVar15 + afStack_210[iVar13];
      afStack_410[iVar13 + 1] =
           ((float)*(ushort *)(*(int *)(iGpffff86b4 + 0x4300) + 2) * (fVar15 / fVar17)) /
           (float)(1 << (uint)(((ulong)*(byte *)(*(int *)(iGpffff86b4 + 0x4300) + 0x53) << 0x3a) >>
                              0x3c));
    }
    fVar16 = (float)*(ushort *)(*(int *)(iGpffff86b4 + 0x4300) + 4) /
             (float)(1 << (uint)((ulong)(*(long *)(*(int *)(iGpffff86b4 + 0x4300) + 0x50) << 0x1e)
                                >> 0x3c));
  }
  GetViewScreenMatrix__9GsxCameraFv(auStack_460,uGpffff8598);
  for (iVar13 = 0; iVar13 < 4; iVar13 = iVar13 + 1) {
    auStack_4a0[iVar13 * 4] = auStack_460[iVar13 * 4];
    auStack_4a0[iVar13 * 4 + 1] = auStack_460[iVar13 * 4 + 1];
    auStack_4a0[iVar13 * 4 + 2] = auStack_460[iVar13 * 4 + 2];
    auStack_4a0[iVar13 * 4 + 3] = auStack_460[iVar13 * 4 + 3];
  }
  for (iVar13 = 0; iVar13 < *(int *)(param_1 + 0x70); iVar13 = iVar13 + 1) {
    auStack_ca0[iVar13 * 8] = *(undefined4 *)(param_1 + iVar13 * 0x20 + 0x180);
    auStack_ca0[iVar13 * 8 + 1] = *(undefined4 *)(param_1 + iVar13 * 0x20 + 0x184);
    auStack_ca0[iVar13 * 8 + 2] = *(undefined4 *)(param_1 + iVar13 * 0x20 + 0x188);
    auStack_ca0[iVar13 * 8 + 3] = 0x3f800000;
    auStack_ca0[(iVar13 * 2 + 1) * 4] = *(undefined4 *)(param_1 + iVar13 * 0x20 + 400);
    auStack_ca0[(iVar13 * 2 + 1) * 4 + 1] = *(undefined4 *)(param_1 + iVar13 * 0x20 + 0x194);
    auStack_ca0[(iVar13 * 2 + 1) * 4 + 2] = *(undefined4 *)(param_1 + iVar13 * 0x20 + 0x198);
    auStack_ca0[(iVar13 * 2 + 1) * 4 + 3] = 0x3f800000;
  }
  auVar9._0_8_ = (long)(int)auStack_4a0;
  auVar9._8_8_ = in_a1_udw;
  sceVu0RotTransPersN(aiStack_14a0,auVar9._0_8_,auStack_ca0,*(int *)(param_1 + 0x70) << 1,0);
  bVar3 = false;
  for (iVar13 = 0; iVar13 < *(int *)(param_1 + 0x70) << 1; iVar13 = iVar13 + 1) {
    if ((((aiStack_14a0[iVar13 * 4] < 0) || (0x10000 < aiStack_14a0[iVar13 * 4])) ||
        (aiStack_14a0[iVar13 * 4 + 1] < 0)) ||
       ((0x10000 < aiStack_14a0[iVar13 * 4 + 1] || (aiStack_14a0[iVar13 * 4 + 2] < 0)))) {
      bVar3 = true;
    }
    aiStack_14a0[iVar13 * 4 + 2] = (int)((float)aiStack_14a0[iVar13 * 4 + 2] / 16.0);
  }
  if (*(int *)(param_1 + 0x70) < 2) {
    bVar3 = true;
  }
  bVar1 = (*(byte *)(param_1 + 0x40) & 1) == 0;
  uVar12 = (uint)bVar1;
  iVar13 = *(int *)(param_1 + 0x70) * 3;
  if (*(int *)(param_1 + uVar12 * 4 + 0x980) != iVar13 + 0xd) {
    __dla__FPv(*(undefined4 *)(param_1 + uVar12 * 4 + 0x18));
    *(undefined4 *)(param_1 + uVar12 * 4 + 0x18) = 0;
    *(undefined4 *)(param_1 + uVar12 * 4 + 0x980) = 0;
  }
  uVar10 = auVar9._8_8_;
  if (*(int *)(param_1 + uVar12 * 4 + 0x18) == 0) {
    uVar4 = __nwa__FUi((iVar13 + 0xd) * 0x10);
    uVar10 = auVar9._8_8_;
    *(undefined4 *)(param_1 + uVar12 * 4 + 0x18) = uVar4;
    *(int *)(param_1 + uVar12 * 4 + 0x980) = iVar13 + 0xd;
  }
  puVar2 = *(undefined4 **)(param_1 + uVar12 * 4 + 0x18);
  if (bVar3) {
    *(undefined4 **)(param_1 + 0x54) = puVar2;
    *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfe | bVar1;
  }
  else {
    if (*(int *)(param_1 + 0x98c) != 0) {
      ChangeClut__6JRCTexFUs(*(undefined4 *)(iGpffff86b4 + 0x4300),*(int *)(param_1 + 0x98c) - 1U & 0xffff)
      ;
    }
    *puVar2 = 0x50000000;
    if (*(int *)(param_1 + 0x98c) == 0) {
      puVar2[1] = *(undefined4 *)
                   (*(int *)(iGpffff86b4 + 0x4254) +
                    (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x4254) + 10) * 4 + 0xc);
    }
    else {
      puVar2[1] = *(undefined4 *)
                   (*(int *)(iGpffff86b4 + 0x4300) +
                    (uint)*(ushort *)(*(int *)(iGpffff86b4 + 0x4300) + 10) * 4 + 0xc);
    }
    puVar2[2] = 0;
    puVar2[3] = 0;
    puVar2[4] = iVar13 + 0x1000000a;
    puVar2[5] = 0;
    puVar2[6] = 0;
    puVar2[7] = iVar13 + 0x5000000a;
    *(undefined8 *)(puVar2 + 8) = 0x6000000000000001;
    *(undefined8 *)(puVar2 + 10) = 0xe6e8ee;
    *(undefined8 *)(puVar2 + 0xc) = 1;
    *(undefined8 *)(puVar2 + 0xe) = 0x3f;
    *(undefined8 *)(puVar2 + 0x10) = 0x60;
    *(undefined8 *)(puVar2 + 0x12) = 0x14;
    *(undefined8 *)(puVar2 + 0x14) = 5;
    *(undefined8 *)(puVar2 + 0x16) = 0;
    *(undefined8 *)(puVar2 + 0x18) = 0x73001;
    *(undefined8 *)(puVar2 + 0x1a) = 0x47;
    if (*(int *)(param_1 + 0x98c) == 0) {
      uVar5 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x4254),1);
      *(undefined8 *)(puVar2 + 0x1c) = uVar5;
    }
    else {
      uVar5 = GetTex0__6JRCTexFb(*(undefined4 *)(iGpffff86b4 + 0x4300),1);
      *(undefined8 *)(puVar2 + 0x1c) = uVar5;
    }
    *(undefined8 *)(puVar2 + 0x1e) = 0;
    *(undefined8 *)(puVar2 + 0x20) = 0x48;
    *(undefined8 *)(puVar2 + 0x22) = 0x42;
    if (*(int *)(param_1 + 0x98c) == 0) {
      lVar6 = 0;
      lVar7 = 0x30;
    }
    else {
      lVar6 = 0x80;
      lVar7 = lVar6;
    }
    auVar8._8_8_ = uVar10;
    auVar8._0_8_ = 0x8400000000000001;
    auVar18._4_4_ = in_zero_hi;
    auVar18._0_4_ = in_zero_lo;
    auVar18._8_4_ = in_zero_udw;
    auVar18._12_4_ = in_register_0000000c;
    auVar9 = _pcpyld(auVar18,auVar8);
    *(long *)(puVar2 + 0x24) = auVar9._0_8_;
    *(undefined8 *)(puVar2 + 0x26) = 0xc12c12f0;
    *(undefined8 *)(puVar2 + 0x28) = 0x5c;
    *(undefined8 *)(puVar2 + 0x2a) = 0;
    *(ulong *)(puVar2 + 0x2c) = (ulong)(uint)(afStack_310[0] * (16.0 / (float)aiStack_14a0[3]));
    *(ulong *)(puVar2 + 0x2e) =
         lVar7 << 0x18 | 0x808080U | (ulong)(uint)(16.0 / (float)aiStack_14a0[3]) << 0x20;
    *(long *)(puVar2 + 0x30) =
         (long)aiStack_14a0[2] << 0x20 | (long)aiStack_14a0[0] | (long)aiStack_14a0[1] << 0x10;
    fVar17 = 16.0 / (float)iStack_1484;
    fStack_8 = afStack_410[0] * fVar17;
    fStack_c = fVar16 * fVar17;
    *(ulong *)(puVar2 + 0x32) = CONCAT44(fVar16 * fVar17,afStack_410[0] * fVar17);
    *(ulong *)(puVar2 + 0x34) = lVar7 << 0x18 | 0x808080U | (ulong)(uint)fVar17 << 0x20;
    *(long *)(puVar2 + 0x36) =
         (long)iStack_1488 << 0x20 | (long)aiStack_14a0[4] | (long)aiStack_14a0[5] << 0x10;
    *(ulong *)(puVar2 + 0x38) = (long)(*(int *)(param_1 + 0x70) + -1) | 0x6400000000008000;
    *(undefined8 *)(puVar2 + 0x3a) = 0x412412;
    puVar11 = (ulong *)(puVar2 + 0x3c);
    for (iVar13 = 1; iVar13 < *(int *)(param_1 + 0x70); iVar13 = iVar13 + 1) {
      fStack_4 = 16.0 / (float)aiStack_14a0[iVar13 * 8 + 3];
      fStack_8 = fStack_4 * afStack_310[iVar13];
      fStack_c = 0.0;
      *puVar11 = (ulong)(uint)(fStack_4 * afStack_310[iVar13]);
      if (iVar13 == *(int *)(param_1 + 0x70) + -1) {
        puVar11[1] = lVar6 << 0x18 | 0x808080U | (ulong)(uint)fStack_4 << 0x20;
      }
      else {
        puVar11[1] = lVar7 << 0x18 | 0x808080U | (ulong)(uint)fStack_4 << 0x20;
      }
      puVar11[2] = (long)aiStack_14a0[iVar13 * 8 + 2] << 0x20 |
                   (long)aiStack_14a0[iVar13 * 8] | (long)aiStack_14a0[iVar13 * 8 + 1] << 0x10;
      fStack_4 = 16.0 / (float)aiStack_14a0[(iVar13 * 2 + 1) * 4 + 3];
      fStack_8 = fStack_4 * afStack_410[iVar13];
      fStack_c = fVar16 * fStack_4;
      puVar11[3] = CONCAT44(fVar16 * fStack_4,fStack_4 * afStack_410[iVar13]);
      if (iVar13 == *(int *)(param_1 + 0x70) + -1) {
        puVar11[4] = lVar6 << 0x18 | 0x808080U | (ulong)(uint)fStack_4 << 0x20;
      }
      else {
        puVar11[4] = lVar7 << 0x18 | 0x808080U | (ulong)(uint)fStack_4 << 0x20;
      }
      puVar11[5] = (long)aiStack_14a0[(iVar13 * 2 + 1) * 4 + 2] << 0x20 |
                   (long)aiStack_14a0[(iVar13 * 2 + 1) * 4] |
                   (long)aiStack_14a0[(iVar13 * 2 + 1) * 4 + 1] << 0x10;
      puVar11 = puVar11 + 6;
    }
    *(ulong **)(param_1 + 0x54) = puVar11;
    *(byte *)(param_1 + 0x40) = *(byte *)(param_1 + 0x40) & 0xfe | bVar1;
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0050ec50  EndSet__17SwordLocusEffect1Fv
 * C++: SwordLocusEffect1::EndSet()
 * size: 0x6c bytes
 * --------------------------------------------------------------------------- */
void EndSet__17SwordLocusEffect1Fv(int param_1)

{
  if ((*(int *)(param_1 + 0x5c) == 0) && (*(char *)(param_1 + 0x990) == '\x01')) {
    *(undefined4 *)(param_1 + 0x5c) = 1;
    *(undefined4 *)(param_1 + 0x60) = 0;
    *(undefined4 *)(param_1 + 100) = *(undefined4 *)(param_1 + 0x70);
    *(undefined4 *)(param_1 + 0x988) = 0;
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0050ecc0  ForceEndSet__17SwordLocusEffect1Fv
 * C++: SwordLocusEffect1::ForceEndSet()
 * size: 0x54 bytes
 * --------------------------------------------------------------------------- */
void ForceEndSet__17SwordLocusEffect1Fv(int param_1)

{
  if (*(int *)(param_1 + 0x5c) == 0) {
    *(undefined4 *)(param_1 + 0x5c) = 1;
    *(undefined4 *)(param_1 + 0x60) = 0;
    *(undefined4 *)(param_1 + 100) = *(undefined4 *)(param_1 + 0x70);
    *(undefined4 *)(param_1 + 0x988) = 0;
  }
  return;
}

/* ---------------------------------------------------------------------------
 * JP: 0x0054b5d0  @24@__dt__17SwordLocusEffect1Fv
 * C++: @24@__dt__17SwordLocusEffect1Fv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int * _24___dt__17SwordLocusEffect1Fv(int *param_1,short param_2)

{
  int *piVar1;
  
  piVar1 = param_1 + -6;
  if (piVar1 != (int *)0x0) {
    param_1[-1] = 0x40a1c0;
    param_1[4] = 0x40a1d0;
    param_1[7] = 0x40a1e0;
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
 * JP: 0x0054b5e0  @44@__dt__17SwordLocusEffect1Fv
 * C++: @44@__dt__17SwordLocusEffect1Fv
 * size: 0x8 bytes
 * --------------------------------------------------------------------------- */
int _44___dt__17SwordLocusEffect1Fv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x2c;
  if (iVar1 != 0) {
    *(undefined4 *)(param_1 + -0x18) = 0x40a1c0;
    *(undefined4 *)(param_1 + -4) = 0x40a1d0;
    *(undefined4 *)(param_1 + 8) = 0x40a1e0;
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

