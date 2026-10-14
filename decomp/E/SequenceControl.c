/*
 * SequenceControl.c -- Ghidra decompiler output (SLPM_602.19, JP Furokuban), tidied by tools/E_gen_decomp.py
 * 18 functions. Types: u8/u16/u32/u64 = undefined1/2/4/8. Addresses in comments are JP main-exe addresses.
 */

/* ---- 0x00242b40 size 0xc0  RotAnim::Cleate(PUcP15SequenceControl)
 *      mangled: Cleate__7RotAnimFPUcP15SequenceControl */
uint Cleate__7RotAnimFPUcP15SequenceControl(int *param_1,int param_2,int param_3)

{
  uint uVar1;
  
  if (*(int *)(param_3 + 8) == 0) {
    param_1[4] = 0x3c888889;
  }
  else {
    param_1[4] = (int)(1.0 / (float)*(byte *)(*(int *)(param_3 + 8) + 0x15));
  }
  *param_1 = param_2;
  uVar1 = param_2 + (uint)*(ushort *)(param_1 + 3) * 2;
  if ((uVar1 & 0xf) != 0) {
    uVar1 = uVar1 + (0x10 - (uVar1 & 0xf));
  }
  param_1[1] = uVar1;
  uVar1 = uVar1 + (uint)*(ushort *)(param_1 + 3) * 8;
  if ((uVar1 & 0xf) != 0) {
    uVar1 = uVar1 + (0x10 - (uVar1 & 0xf));
  }
  return uVar1;
}

/* ---- 0x00243010 size 0xc0  TranceAnim::Cleate(PUcP15SequenceControl)
 *      mangled: Cleate__10TranceAnimFPUcP15SequenceControl */
uint Cleate__10TranceAnimFPUcP15SequenceControl(int *param_1,int param_2,int param_3)

{
  uint uVar1;
  
  if (*(int *)(param_3 + 8) == 0) {
    param_1[4] = 0x3c888889;
  }
  else {
    param_1[4] = (int)(1.0 / (float)*(byte *)(*(int *)(param_3 + 8) + 0x15));
  }
  *param_1 = param_2;
  uVar1 = param_2 + (uint)*(ushort *)(param_1 + 3) * 2;
  if ((uVar1 & 0xf) != 0) {
    uVar1 = uVar1 + (0x10 - (uVar1 & 0xf));
  }
  param_1[1] = uVar1;
  uVar1 = uVar1 + (uint)*(ushort *)(param_1 + 3) * 8;
  if ((uVar1 & 0xf) != 0) {
    uVar1 = uVar1 + (0x10 - (uVar1 & 0xf));
  }
  return uVar1;
}

/* ---- 0x002442d0 size 0x1c8  InterSequenceControl::InterSequenceControl(P5FrameiPc)
 *      mangled: __ct__20InterSequenceControlFP5FrameiPc */
u64
__ct__20InterSequenceControlFP5FrameiPc(u64 param_1,int param_2,int param_3,char *param_4)

{
  u32 uVar1;
  u64 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  __ct__15SequenceControlFv();
  iVar6 = (int)param_1;
  *(u8 **)(iVar6 + 0x20) = __vt__20InterSequenceControl;
  memset((void *)(iVar6 + 0x24),0,0x20);
  strcpy((char *)(iVar6 + 0x28),param_4);
  *(short *)(iVar6 + 0x36) = (short)param_3;
  *(byte *)(iVar6 + 0x38) = *(byte *)(iVar6 + 0x38) & 0xfe;
  *(u8 *)(iVar6 + 0x39) = 0x1e;
  *(int *)(iVar6 + 8) = iVar6 + 0x24;
  uVar2 = __nwa__FUi(param_3 * 0x24 + 0x10);
  uVar1 = __construct_new_array(uVar2,0x245a30,0x245a60,0x24,param_3);
  *(u32 *)(iVar6 + 0x44) = uVar1;
  uVar1 = __nwa__FUi(param_3 * 0x160);
  *(u32 *)(iVar6 + 0x48) = uVar1;
  *(u32 *)(iVar6 + 0xc) = *(u32 *)(iVar6 + 0x44);
  iVar5 = 0;
  *(float *)(iVar6 + 0x14) = 1.0 / (float)*(byte *)(iVar6 + 0x39);
  if (0 < param_3) {
    iVar4 = 0;
    iVar3 = 0;
    do {
      *(u16 *)(*(int *)(iVar6 + 0x48) + iVar4 + 0x10) = 0x10;
      *(u16 *)(*(int *)(iVar6 + 0x48) + iVar4 + 0x12) = 0x10;
      memcpy((void *)(*(int *)(iVar6 + 0x48) + iVar4),*(void **)(param_2 + 0x80),0xc);
      Cleate__8SequenceFPUcP15SequenceControl
                (*(int *)(iVar6 + 0x44) + iVar3,*(int *)(iVar6 + 0x48) + iVar4,param_1);
      iVar5 = iVar5 + 1;
      iVar4 = iVar4 + 0x160;
      param_2 = param_2 + 0x1f0;
      iVar3 = iVar3 + 0x24;
    } while (iVar5 < param_3);
  }
  return param_1;
}

/* ---- 0x002444a0 size 0x88  InterSequenceControl::~InterSequenceControl(v)
 *      mangled: __dt__20InterSequenceControlFv */
long __dt__20InterSequenceControlFv(long param_1,short param_2)

{
  int iVar1;
  
  if (param_1 != 0) {
    iVar1 = (int)param_1;
    *(u8 **)(iVar1 + 0x20) = __vt__20InterSequenceControl;
    *(u16 *)(iVar1 + 0x3a) = 0;
    *(u32 *)(iVar1 + 0x10) = 0;
    if (*(int *)(iVar1 + 0x48) != 0) {
      __dla__FPv();
    }
    __dt__15SequenceControlFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* ---- 0x00244530 size 0xf8c  InterSequenceControl::setInterData(P5Modelii)
 *      mangled: setInterData__20InterSequenceControlFP5Modelii */
void setInterData__20InterSequenceControlFP5Modelii
               (u64 param_1,int param_2,long param_3,uint param_4)

{
  short sVar1;
  int iVar2;
  bool bVar3;
  u8 auVar4 [16];
  u8 auVar5 [16];
  u8 auVar6 [16];
  u8 auVar7 [16];
  u8 auVar8 [16];
  u8 auVar9 [16];
  u8 auVar10 [16];
  u8 auVar11 [16];
  u8 auVar12 [16];
  u8 auVar13 [16];
  u8 auVar14 [16];
  u8 auVar15 [16];
  u8 auVar16 [16];
  u8 auVar17 [16];
  u8 auVar18 [16];
  u8 auVar19 [16];
  u32 in_zero_lo;
  u32 in_zero_hi;
  u32 in_zero_udw;
  u32 in_register_0000000c;
  int iVar20;
  int iVar21;
  int *piVar22;
  u16 *puVar23;
  int iVar24;
  int iVar25;
  int iVar26;
  int iVar27;
  int iVar28;
  int iVar29;
  int iVar30;
  u16 uVar31;
  float fVar32;
  float fVar33;
  float fVar34;
  float fVar35;
  float fVar36;
  float fVar37;
  float fVar38;
  float fVar39;
  float fVar40;
  float fVar41;
  float fVar42;
  float fVar43;
  u8 auVar44 [16];
  u8 auVar45 [16];
  u8 auStack_350 [16];
  u8 auStack_340 [16];
  u8 auStack_330 [16];
  u8 auStack_320 [16];
  u8 auStack_310 [16];
  u8 auStack_300 [16];
  u8 auStack_2f0 [16];
  u8 auStack_2e0 [16];
  u8 auStack_2d0 [16];
  u8 auStack_2c0 [16];
  u8 auStack_2b0 [16];
  u8 auStack_2a0 [16];
  u8 auStack_290 [16];
  u8 auStack_280 [16];
  u64 uStack_270;
  u32 uStack_268;
  u32 uStack_264;
  u8 auStack_260 [16];
  u8 auStack_250 [16];
  u64 uStack_240;
  u32 uStack_238;
  u32 uStack_234;
  u64 uStack_230;
  u32 uStack_228;
  u32 uStack_224;
  u8 auStack_220 [8];
  u32 uStack_218;
  u32 uStack_214;
  u8 auStack_210 [16];
  u64 uStack_200;
  u32 uStack_1f8;
  u32 uStack_1f4;
  u8 auStack_1f0 [8];
  u32 uStack_1e8;
  u32 uStack_1e4;
  u8 auStack_1e0 [16];
  u64 uStack_1d0;
  u32 uStack_1c8;
  u32 uStack_1c4;
  u8 auStack_1c0 [16];
  u8 auStack_1b0 [16];
  u64 uStack_1a0;
  u32 uStack_198;
  u32 uStack_194;
  u64 uStack_190;
  u32 uStack_188;
  u32 uStack_184;
  u8 auStack_180 [8];
  u32 uStack_178;
  u32 uStack_174;
  u8 auStack_170 [16];
  u64 uStack_160;
  u32 uStack_158;
  u32 uStack_154;
  u8 auStack_150 [8];
  u32 uStack_148;
  u32 uStack_144;
  u8 auStack_140 [16];
  u64 uStack_130;
  u32 uStack_128;
  u32 uStack_124;
  u8 auStack_120 [8];
  u32 uStack_118;
  u32 uStack_114;
  u8 auStack_110 [16];
  u8 auStack_100 [8];
  u32 uStack_f8;
  u32 uStack_f4;
  u8 auStack_f0 [8];
  u32 uStack_e8;
  u32 uStack_e4;
  float fStack_e0;
  float fStack_dc;
  float fStack_d8;
  float fStack_d4;
  u32 uStack_d0;
  u32 uStack_cc;
  u32 uStack_c8;
  u32 uStack_c4;
  u32 uStack_c0;
  u32 uStack_bc;
  u32 uStack_b8;
  u32 uStack_b4;
  u32 uStack_b0;
  u32 uStack_ac;
  u32 uStack_a8;
  u32 uStack_a4;
  u32 uStack_a0;
  u32 uStack_9c;
  u32 uStack_98;
  u32 uStack_94;
  u32 uStack_90;
  u32 uStack_8c;
  u32 uStack_88;
  u32 uStack_84;
  u8 auStack_80 [16];
  u8 auStack_70 [16];
  u8 auStack_60 [8];
  u64 uStack_58;
  u32 uStack_50;
  u32 uStack_4c;
  u32 uStack_48;
  u32 uStack_44;
  u32 uStack_40;
  u32 uStack_3c;
  u32 uStack_38;
  u32 uStack_34;
  u32 uStack_30;
  u32 uStack_2c;
  u32 uStack_28;
  u32 uStack_24;
  u32 uStack_20;
  u32 uStack_1c;
  u32 uStack_18;
  u32 uStack_14;
  u32 uStack_10;
  u32 uStack_c;
  u32 uStack_8;
  u32 uStack_4;
  
  fVar33 = 0.0;
  auStack_60._4_4_ = in_zero_hi;
  auStack_60._0_4_ = in_zero_lo;
  uStack_58._0_4_ = in_zero_udw;
  uStack_58._4_4_ = in_register_0000000c;
  auStack_70._4_4_ = in_zero_hi;
  auStack_70._0_4_ = in_zero_lo;
  auStack_70._8_4_ = in_zero_udw;
  auStack_70._12_4_ = in_register_0000000c;
  auStack_80._4_4_ = in_zero_hi;
  auStack_80._0_4_ = in_zero_lo;
  auStack_80._8_4_ = in_zero_udw;
  auStack_80._12_4_ = in_register_0000000c;
  uStack_c0 = 0;
  uStack_bc = 0;
  uStack_b8 = 0;
  uStack_b4 = 0x3f800000;
  uStack_d0 = 0;
  uStack_cc = 0;
  uStack_c8 = 0;
  uStack_c4 = 0x3f800000;
  fStack_d4 = 1.0;
  fStack_e0 = 0.0;
  fStack_dc = 0.0;
  fStack_d8 = 0.0;
  iVar26 = (int)param_1;
  *(u32 *)(iVar26 + 0x4c) = 0;
  if ((int)param_4 < 6) {
    param_4 = 6;
  }
  if (0xf < (int)param_4) {
    param_4 = 0xf;
  }
  iVar30 = (int)param_3;
  if (((int)param_4 < 7) &&
     (param_4 = (uint)*(ushort *)(*(int *)(*(int *)(iVar30 * 4 + param_2 + 0x40) + 8) + 0x18),
     param_4 == 0)) {
    param_4 = 6;
  }
  fVar43 = (float)(int)param_4;
  fVar42 = fVar43 * *(float *)(iVar26 + 0x14);
  if (fVar43 < 2.1474836e+09) {
    *(short *)(iVar26 + 0x34) = (short)(int)fVar43;
  }
  else {
    *(short *)(iVar26 + 0x34) = (short)(int)(fVar43 - 2.1474836e+09);
  }
  if (param_3 == 0) {
    *(u16 *)(iVar26 + 0x3a) = *(u16 *)(*(int *)(*(int *)(param_2 + 0x40) + 8) + 0x16);
    *(u32 *)(iVar26 + 0x10) = *(u32 *)(*(int *)(param_2 + 0x40) + 0x10);
  }
  else {
    iVar29 = *(int *)(param_2 + 0x38);
    if ((iVar29 != 0) &&
       (sVar1 = *(short *)(*(int *)(*(int *)(param_2 + 0x44) + 8) + 0x10),
       *(short *)(*(int *)(iVar29 + 8) + 0x10) == sVar1)) {
      fVar33 = *(float *)(iVar29 + 0x1c);
      *(float *)(iVar26 + 0x4c) = fVar33;
      if ((*(byte *)(*(int *)(*(int *)(iVar30 * 4 + param_2 + 0x40) + 8) + 0x14) & 1) != 0) {
        fVar32 = (float)(int)sVar1 * *(float *)(iVar26 + 0x14);
        if (fVar32 < fVar33) {
          fVar33 = fVar33 - fVar32;
        }
        fVar32 = (float)(int)sVar1 * *(float *)(iVar26 + 0x14);
        if (fVar32 < fVar33 + fVar42) {
          *(float *)(iVar26 + 0x4c) = *(float *)(iVar26 + 0x4c) - fVar32;
        }
      }
    }
  }
  iVar29 = *(int *)(iVar30 * 4 + param_2 + 0x38);
  fVar32 = 0.0;
  if (iVar29 != 0) {
    fVar32 = *(float *)(iVar29 + 0x1c);
  }
  uStack_b0 = in_zero_lo;
  uStack_ac = in_zero_hi;
  uStack_a8 = in_zero_udw;
  uStack_a4 = in_register_0000000c;
  uStack_a0 = in_zero_lo;
  uStack_9c = in_zero_hi;
  uStack_98 = in_zero_udw;
  uStack_94 = in_register_0000000c;
  uStack_90 = in_zero_lo;
  uStack_8c = in_zero_hi;
  uStack_88 = in_zero_udw;
  uStack_84 = in_register_0000000c;
  for (iVar29 = 0; iVar29 < (int)(uint)*(ushort *)(*(int *)(param_2 + 0x58) + 4);
      iVar29 = iVar29 + 1) {
    uStack_8 = 0;
    uStack_c = 0;
    uStack_10 = 0;
    fVar35 = 0.0;
    uStack_18 = 0;
    uStack_1c = 0;
    uStack_20 = 0;
    uStack_28 = 0;
    uStack_2c = 0;
    uStack_4 = 0x3f800000;
    iVar28 = 0;
    uStack_14 = 0x3f800000;
    bVar3 = false;
    uStack_30 = 0;
    uStack_24 = 0x3f800000;
    uStack_38 = 0;
    uStack_3c = 0;
    uStack_40 = 0;
    uStack_34 = 0x3f800000;
    uStack_44 = 0x3f800000;
    uStack_48 = 0;
    uStack_4c = 0;
    uStack_50 = 0;
    iVar20 = iVar29 * 0x1f0 + *(int *)(param_2 + 0x30);
    iVar25 = *(int *)(iVar20 + 0x88);
    iVar2 = *(int *)(iVar20 + 0x8c);
    fVar34 = fVar33;
    fVar40 = fVar32;
    iVar20 = strcmp(*(char **)(iVar20 + 0x80),(char *)&_2677);
    if (iVar20 == 0) {
      bVar3 = true;
      if (iVar25 != 0) {
        getTranse__8SequenceFf(fVar32,auStack_f0,iVar25);
        uStack_10 = auStack_f0._0_4_;
        uStack_c = auStack_f0._4_4_;
        uStack_8 = uStack_e8;
        uStack_4 = uStack_e4;
      }
      if (iVar2 != 0) {
        getTranse__8SequenceFf(fVar33,auStack_100,iVar2);
        uStack_20 = auStack_100._0_4_;
        uStack_1c = auStack_100._4_4_;
        uStack_18 = uStack_f8;
        uStack_14 = uStack_f4;
      }
    }
    __amu__7FVectorFf(0xbf800000,&uStack_10);
    __amu__7FVectorFf(0xbf800000,&uStack_20);
    iVar20 = SeachSequence__15SequenceControlFPUc
                       (param_1,*(u32 *)(iVar29 * 0x1f0 + *(int *)(param_2 + 0x30) + 0x80));
    iVar21 = SeachSequence__15SequenceControlFPUc
                       (*(u32 *)(iVar30 * 4 + param_2 + 0x40),
                        *(u32 *)(iVar29 * 0x1f0 + *(int *)(param_2 + 0x30) + 0x80));
    if (iVar21 == 0) {
      *(u8 *)(iVar20 + 0x1c) = 0;
    }
    else {
      fVar38 = 0.0;
      *(u8 *)(iVar20 + 0x1c) = 1;
      if (iVar25 != 0) {
        fVar38 = (float)*(ushort *)(*(int *)(*(int *)(iVar25 + 8) + 8) + 0x10) *
                 *(float *)(iVar26 + 0x14);
        if (*(int *)(iVar25 + 0x10) != 0) {
          *(u32 *)(*(int *)(iVar25 + 0x10) + 8) = 0;
        }
        if (*(int *)(iVar25 + 0x14) != 0) {
          *(u32 *)(*(int *)(iVar25 + 0x14) + 8) = 0;
        }
      }
      fVar39 = (float)*(ushort *)(*(int *)(*(int *)(iVar2 + 8) + 8) + 0x10) *
               *(float *)(iVar26 + 0x14);
      if (*(int *)(iVar2 + 0x10) != 0) {
        *(u32 *)(*(int *)(iVar2 + 0x10) + 8) = 0;
      }
      if (*(int *)(iVar2 + 0x14) != 0) {
        *(u32 *)(*(int *)(iVar2 + 0x14) + 8) = 0;
      }
      if ((iVar25 == 0) || (fVar36 = 0.0, iVar2 == 0)) {
        fVar40 = 0.0;
        if (iVar2 != 0) {
          do {
            uStack_b4 = 0x3f800000;
            uStack_b8 = 0;
            uStack_bc = 0;
            uStack_c0 = 0;
            uStack_58._0_4_ = 0;
            uStack_58._4_4_ = 0x3f800000;
            auVar19._8_8_ = 0;
            auVar19._0_8_ = uStack_58;
            _auStack_60 = auVar19 << 0x40;
            auVar18._12_4_ = 0;
            auVar18._0_12_ = stack0xffffffa4;
            _auStack_60 = auVar18 << 0x20;
            auVar45._4_4_ = uStack_c;
            auVar45._0_4_ = uStack_10;
            auVar45._8_4_ = uStack_8;
            auVar45._12_4_ = uStack_4;
            auVar45 = _lqc2(auVar45);
            auVar44 = _lqc2(_auStack_60);
            auVar44 = _vadd(auVar44,auVar45);
            _auStack_60 = _sqc2(auVar44);
            getQuaternion__8SequenceFf(fVar33,auStack_1f0,iVar2);
            uStack_d0 = auStack_1f0._0_4_;
            uStack_cc = auStack_1f0._4_4_;
            uStack_c8 = uStack_1e8;
            uStack_c4 = uStack_1e4;
            __ct__7FVectorFRC7FVector(auStack_1e0,&uStack_d0);
            getTranse__8SequenceFf(fVar33,&uStack_200,iVar2);
            auStack_70._8_4_ = uStack_1f8;
            auStack_70._0_8_ = uStack_200;
            auStack_70._12_4_ = uStack_1f4;
            auVar44._4_4_ = uStack_1c;
            auVar44._0_4_ = uStack_20;
            auVar44._8_4_ = uStack_18;
            auVar44._12_4_ = uStack_14;
            auVar45 = _lqc2(auVar44);
            auVar44 = _lqc2(auStack_70);
            auVar44 = _vadd(auVar44,auVar45);
            auStack_70 = _sqc2(auVar44);
            slerp__10QuaternionFR10QuaternionRC10Quaternionf
                      (fVar35,&uStack_c0,&fStack_e0,&uStack_d0);
            auStack_80 = _auStack_60;
            if (bVar3) {
              auVar44 = _lqc2(_auStack_60);
              auVar15._4_4_ = uStack_2c;
              auVar15._0_4_ = uStack_30;
              auVar15._8_4_ = uStack_28;
              auVar15._12_4_ = uStack_24;
              auVar45 = _lqc2(auVar15);
              auVar44 = _vsub(auVar44,auVar45);
              auStack_2e0 = _sqc2(auVar44);
              __ct__7FVectorFRC7FVector(auStack_220,auStack_2e0);
              uStack_90 = auStack_220._0_4_;
              uStack_8c = auStack_220._4_4_;
              uStack_88 = uStack_218;
              uStack_84 = uStack_214;
              auVar44 = _lqc2(auStack_70);
              auVar13._4_4_ = uStack_3c;
              auVar13._0_4_ = uStack_40;
              auVar13._8_4_ = uStack_38;
              auVar13._12_4_ = uStack_34;
              auVar45 = _lqc2(auVar13);
              auVar44 = _vsub(auVar44,auVar45);
              auStack_2f0 = _sqc2(auVar44);
              __ct__7FVectorFRC7FVector(&uStack_230,auStack_2f0);
              uStack_a0 = (u32)uStack_230;
              uStack_9c = (u32)((ulong)uStack_230 >> 0x20);
              uStack_98 = uStack_228;
              uStack_94 = uStack_224;
              auVar7._8_4_ = uStack_228;
              auVar7._0_8_ = uStack_230;
              auVar7._12_4_ = uStack_224;
              auVar44 = _lqc2(auVar7);
              auVar45 = _qmtc2(fVar35);
              auVar44 = _vmulbc(auVar44,auVar45);
              auStack_340 = _sqc2(auVar44);
              __ct__7FVectorFRC7FVector(auStack_260,auStack_340);
              auVar9._4_4_ = uStack_8c;
              auVar9._0_4_ = uStack_90;
              auVar9._8_4_ = uStack_88;
              auVar9._12_4_ = uStack_84;
              auVar44 = _lqc2(auVar9);
              auVar45 = _qmtc2(1.0 - fVar35);
              auVar44 = _vmulbc(auVar44,auVar45);
              auStack_350 = _sqc2(auVar44);
              __ct__7FVectorFRC7FVector(auStack_250,auStack_350);
              auVar44 = _lqc2(auStack_250);
              auVar45 = _lqc2(auStack_260);
              auVar44 = _vadd(auVar44,auVar45);
              auStack_300 = _sqc2(auVar44);
              __ct__7FVectorFRC7FVector(&uStack_240,auStack_300);
              uStack_b0 = (u32)uStack_240;
              uStack_ac = (u32)((ulong)uStack_240 >> 0x20);
              uStack_a8 = uStack_238;
              uStack_a4 = uStack_234;
              auVar11._4_4_ = uStack_4c;
              auVar11._0_4_ = uStack_50;
              auVar11._8_4_ = uStack_48;
              auVar11._12_4_ = uStack_44;
              auVar44 = _lqc2(auVar11);
              auVar5._8_4_ = uStack_238;
              auVar5._0_8_ = uStack_240;
              auVar5._12_4_ = uStack_234;
              auVar45 = _lqc2(auVar5);
              auVar44 = _vadd(auVar44,auVar45);
              auStack_310 = _sqc2(auVar44);
              __ct__7FVectorFRC7FVector(&uStack_270,auStack_310);
              uStack_50 = (u32)uStack_270;
              uStack_4c = (u32)((ulong)uStack_270 >> 0x20);
              auStack_80._8_4_ = uStack_268;
              auStack_80._0_8_ = uStack_270;
              auStack_80._12_4_ = uStack_264;
              uStack_48 = uStack_268;
              uStack_44 = uStack_264;
              uStack_30 = auStack_60._0_4_;
              uStack_2c = auStack_60._4_4_;
              uStack_28 = (u32)uStack_58;
              uStack_24 = uStack_58._4_4_;
              uStack_40 = auStack_70._0_4_;
              uStack_3c = auStack_70._4_4_;
              uStack_38 = auStack_70._8_4_;
              uStack_34 = auStack_70._12_4_;
            }
            else {
              __amu__7FVectorFf(1.0 - fVar35);
              auVar44 = _lqc2(auStack_70);
              auVar45 = _qmtc2(fVar35);
              auVar44 = _vmulbc(auVar44,auVar45);
              auStack_2d0 = _sqc2(auVar44);
              __ct__7FVectorFRC7FVector(auStack_210,auStack_2d0);
              auVar45 = _lqc2(auStack_210);
              auVar44 = _lqc2(auStack_80);
              auVar44 = _vadd(auVar44,auVar45);
              auStack_80 = _sqc2(auVar44);
            }
            fVar35 = fVar40 * 30.0001;
            if (fVar35 < 2.1474836e+09) {
              uVar31 = (u16)(int)fVar35;
            }
            else {
              uVar31 = (u16)(int)(fVar35 - 2.1474836e+09);
            }
            fVar35 = fVar40 * 30.0001;
            *(u16 *)(**(int **)(iVar20 + 0x10) + iVar28 * 2) = uVar31;
            puVar23 = (u16 *)(*(int *)(*(int *)(iVar20 + 0x10) + 4) + iVar28 * 8);
            *puVar23 = (short)(int)(fStack_e0 * 4096.0);
            puVar23[1] = (short)(int)(fStack_dc * 4096.0);
            puVar23[2] = (short)(int)(fStack_d8 * 4096.0);
            puVar23[3] = (short)(int)(fStack_d4 * 4096.0);
            if (fVar35 < 2.1474836e+09) {
              uVar31 = (u16)(int)fVar35;
              piVar22 = *(int **)(iVar20 + 0x14);
            }
            else {
              uVar31 = (u16)(int)(fVar35 - 2.1474836e+09);
              piVar22 = *(int **)(iVar20 + 0x14);
            }
            iVar24 = iVar28 * 2;
            iVar25 = iVar28 * 8;
            iVar28 = iVar28 + 1;
            *(u16 *)(*piVar22 + iVar24) = uVar31;
            setFloatToShort__7SVectorFPf(*(int *)(*(int *)(iVar20 + 0x14) + 4) + iVar25,auStack_80);
            fVar38 = fVar42 * ((float)iVar28 / fVar43);
            fVar35 = fVar38 / fVar42;
            fVar33 = fVar33 + (fVar38 - fVar40);
            if (fVar39 < fVar33) {
              fVar40 = fVar39;
              if (((*(byte *)(*(int *)(*(int *)(iVar2 + 8) + 8) + 0x14) & 1) != 0) &&
                 (fVar40 = fVar33 - fVar39, bVar3)) {
                uStack_18 = 0;
                uStack_14 = 0x3f800000;
                uStack_1c = 0;
                uStack_20 = 0;
              }
              uStack_38 = 0;
              uStack_3c = 0;
              uStack_34 = 0x3f800000;
              uStack_40 = 0;
              fVar33 = fVar40;
            }
            fVar40 = fVar38;
          } while (fVar35 <= 1.0);
        }
      }
      else {
        do {
          getQuaternion__8SequenceFf(fVar40,auStack_120,iVar25);
          uStack_c0 = auStack_120._0_4_;
          uStack_bc = auStack_120._4_4_;
          uStack_b8 = uStack_118;
          uStack_b4 = uStack_114;
          __ct__7FVectorFRC7FVector(auStack_110,&uStack_c0);
          getTranse__8SequenceFf(fVar40,&uStack_130,iVar25);
          uStack_58._0_4_ = uStack_128;
          auStack_60 = (u8  [8])uStack_130;
          uStack_58._4_4_ = uStack_124;
          auVar17._4_4_ = uStack_c;
          auVar17._0_4_ = uStack_10;
          auVar17._8_4_ = uStack_8;
          auVar17._12_4_ = uStack_4;
          auVar45 = _lqc2(auVar17);
          auVar44 = _lqc2(_auStack_60);
          auVar44 = _vadd(auVar44,auVar45);
          _auStack_60 = _sqc2(auVar44);
          getQuaternion__8SequenceFf(fVar33,auStack_150,iVar2);
          uStack_d0 = auStack_150._0_4_;
          uStack_cc = auStack_150._4_4_;
          uStack_c8 = uStack_148;
          uStack_c4 = uStack_144;
          __ct__7FVectorFRC7FVector(auStack_140,&uStack_d0);
          getTranse__8SequenceFf(fVar33,&uStack_160,iVar2);
          auStack_70._8_4_ = uStack_158;
          auStack_70._0_8_ = uStack_160;
          auStack_70._12_4_ = uStack_154;
          auVar16._4_4_ = uStack_1c;
          auVar16._0_4_ = uStack_20;
          auVar16._8_4_ = uStack_18;
          auVar16._12_4_ = uStack_14;
          auVar45 = _lqc2(auVar16);
          auVar44 = _lqc2(auStack_70);
          auVar44 = _vadd(auVar44,auVar45);
          auStack_70 = _sqc2(auVar44);
          slerp__10QuaternionFR10QuaternionRC10Quaternionf(fVar35,&uStack_c0,&fStack_e0,&uStack_d0);
          auStack_80 = _auStack_60;
          if (bVar3) {
            auVar44 = _lqc2(_auStack_60);
            auVar14._4_4_ = uStack_2c;
            auVar14._0_4_ = uStack_30;
            auVar14._8_4_ = uStack_28;
            auVar14._12_4_ = uStack_24;
            auVar45 = _lqc2(auVar14);
            auVar44 = _vsub(auVar44,auVar45);
            auStack_290 = _sqc2(auVar44);
            __ct__7FVectorFRC7FVector(auStack_180,auStack_290);
            uStack_90 = auStack_180._0_4_;
            uStack_8c = auStack_180._4_4_;
            uStack_88 = uStack_178;
            uStack_84 = uStack_174;
            auVar44 = _lqc2(auStack_70);
            auVar12._4_4_ = uStack_3c;
            auVar12._0_4_ = uStack_40;
            auVar12._8_4_ = uStack_38;
            auVar12._12_4_ = uStack_34;
            auVar45 = _lqc2(auVar12);
            auVar44 = _vsub(auVar44,auVar45);
            auStack_2a0 = _sqc2(auVar44);
            __ct__7FVectorFRC7FVector(&uStack_190,auStack_2a0);
            uStack_a0 = (u32)uStack_190;
            uStack_9c = (u32)((ulong)uStack_190 >> 0x20);
            uStack_98 = uStack_188;
            uStack_94 = uStack_184;
            auVar6._8_4_ = uStack_188;
            auVar6._0_8_ = uStack_190;
            auVar6._12_4_ = uStack_184;
            auVar44 = _lqc2(auVar6);
            auVar45 = _qmtc2(fVar35);
            auVar44 = _vmulbc(auVar44,auVar45);
            auStack_320 = _sqc2(auVar44);
            __ct__7FVectorFRC7FVector(auStack_1c0,auStack_320);
            auVar8._4_4_ = uStack_8c;
            auVar8._0_4_ = uStack_90;
            auVar8._8_4_ = uStack_88;
            auVar8._12_4_ = uStack_84;
            auVar44 = _lqc2(auVar8);
            auVar45 = _qmtc2(1.0 - fVar35);
            auVar44 = _vmulbc(auVar44,auVar45);
            auStack_330 = _sqc2(auVar44);
            __ct__7FVectorFRC7FVector(auStack_1b0,auStack_330);
            auVar44 = _lqc2(auStack_1b0);
            auVar45 = _lqc2(auStack_1c0);
            auVar44 = _vadd(auVar44,auVar45);
            auStack_2b0 = _sqc2(auVar44);
            __ct__7FVectorFRC7FVector(&uStack_1a0,auStack_2b0);
            uStack_b0 = (u32)uStack_1a0;
            uStack_ac = (u32)((ulong)uStack_1a0 >> 0x20);
            uStack_a8 = uStack_198;
            uStack_a4 = uStack_194;
            auVar10._4_4_ = uStack_4c;
            auVar10._0_4_ = uStack_50;
            auVar10._8_4_ = uStack_48;
            auVar10._12_4_ = uStack_44;
            auVar44 = _lqc2(auVar10);
            auVar4._8_4_ = uStack_198;
            auVar4._0_8_ = uStack_1a0;
            auVar4._12_4_ = uStack_194;
            auVar45 = _lqc2(auVar4);
            auVar44 = _vadd(auVar44,auVar45);
            auStack_2c0 = _sqc2(auVar44);
            __ct__7FVectorFRC7FVector(&uStack_1d0,auStack_2c0);
            uStack_50 = (u32)uStack_1d0;
            uStack_4c = (u32)((ulong)uStack_1d0 >> 0x20);
            auStack_80._8_4_ = uStack_1c8;
            auStack_80._0_8_ = uStack_1d0;
            auStack_80._12_4_ = uStack_1c4;
            uStack_48 = uStack_1c8;
            uStack_44 = uStack_1c4;
            uStack_30 = auStack_60._0_4_;
            uStack_2c = auStack_60._4_4_;
            uStack_28 = (u32)uStack_58;
            uStack_24 = uStack_58._4_4_;
            uStack_40 = auStack_70._0_4_;
            uStack_3c = auStack_70._4_4_;
            uStack_38 = auStack_70._8_4_;
            uStack_34 = auStack_70._12_4_;
          }
          else {
            __amu__7FVectorFf(1.0 - fVar35);
            auVar44 = _lqc2(auStack_70);
            auVar45 = _qmtc2(fVar35);
            auVar44 = _vmulbc(auVar44,auVar45);
            auStack_280 = _sqc2(auVar44);
            __ct__7FVectorFRC7FVector(auStack_170,auStack_280);
            auVar45 = _lqc2(auStack_170);
            auVar44 = _lqc2(auStack_80);
            auVar44 = _vadd(auVar44,auVar45);
            auStack_80 = _sqc2(auVar44);
          }
          fVar35 = fVar36 * 30.0001;
          if (fVar35 < 2.1474836e+09) {
            uVar31 = (u16)(int)fVar35;
          }
          else {
            uVar31 = (u16)(int)(fVar35 - 2.1474836e+09);
          }
          fVar35 = fVar36 * 30.0001;
          *(u16 *)(**(int **)(iVar20 + 0x10) + iVar28 * 2) = uVar31;
          puVar23 = (u16 *)(*(int *)(*(int *)(iVar20 + 0x10) + 4) + iVar28 * 8);
          *puVar23 = (short)(int)(fStack_e0 * 4096.0);
          puVar23[1] = (short)(int)(fStack_dc * 4096.0);
          puVar23[2] = (short)(int)(fStack_d8 * 4096.0);
          puVar23[3] = (short)(int)(fStack_d4 * 4096.0);
          if (fVar35 < 2.1474836e+09) {
            uVar31 = (u16)(int)fVar35;
            piVar22 = *(int **)(iVar20 + 0x14);
          }
          else {
            uVar31 = (u16)(int)(fVar35 - 2.1474836e+09);
            piVar22 = *(int **)(iVar20 + 0x14);
          }
          iVar27 = iVar28 * 2;
          iVar24 = iVar28 * 8;
          iVar28 = iVar28 + 1;
          *(u16 *)(*piVar22 + iVar27) = uVar31;
          setFloatToShort__7SVectorFPf(*(int *)(*(int *)(iVar20 + 0x14) + 4) + iVar24,auStack_80);
          fVar37 = fVar42 * ((float)iVar28 / fVar43);
          fVar35 = fVar37 / fVar42;
          fVar40 = fVar40 + (fVar37 - fVar36);
          if (fVar38 < fVar40) {
            fVar41 = fVar38;
            if (((*(byte *)(*(int *)(*(int *)(iVar25 + 8) + 8) + 0x14) & 1) != 0) &&
               (fVar41 = fVar40 - fVar38, bVar3)) {
              uStack_8 = 0;
              uStack_4 = 0x3f800000;
              uStack_c = 0;
              uStack_10 = 0;
            }
            uStack_28 = 0;
            uStack_2c = 0;
            uStack_24 = 0x3f800000;
            uStack_30 = 0;
            fVar40 = fVar41;
          }
          fVar33 = fVar33 + (fVar37 - fVar36);
          if (fVar39 < fVar33) {
            fVar36 = fVar39;
            if (((*(byte *)(*(int *)(*(int *)(iVar2 + 8) + 8) + 0x14) & 1) != 0) &&
               (fVar36 = fVar33 - fVar39, bVar3)) {
              uStack_18 = 0;
              uStack_14 = 0x3f800000;
              uStack_1c = 0;
              uStack_20 = 0;
            }
            uStack_38 = 0;
            uStack_3c = 0;
            uStack_34 = 0x3f800000;
            uStack_40 = 0;
            fVar33 = fVar36;
          }
          fVar36 = fVar37;
        } while (fVar35 <= 1.0);
      }
      if (iVar21 != 0) {
        *(u32 *)(*(int *)(iVar20 + 0x10) + 8) = 0xffffffff;
        *(short *)(*(int *)(iVar20 + 0x10) + 0xc) = (short)iVar28;
        *(u32 *)(*(int *)(iVar20 + 0x14) + 8) = 0xffffffff;
        *(short *)(*(int *)(iVar20 + 0x14) + 0xc) = (short)iVar28;
      }
    }
    fVar33 = fVar34;
  }
  return;
}

/* ---- 0x002454c0 size 0x24  SequenceControl::SequenceControl(v)
 *      mangled: __ct__15SequenceControlFv */
u64 __ct__15SequenceControlFv(u64 param_1)

{
  u32 *puVar1;
  
  puVar1 = (u32 *)param_1;
  *puVar1 = 0;
  puVar1[1] = 0;
  puVar1[8] = __vt__15SequenceControl;
  *(u16 *)(puVar1 + 6) = 0;
  puVar1[4] = 0;
  return param_1;
}

/* ---- 0x002454f0 size 0xb0  SequenceControl::~SequenceControl(v)
 *      mangled: __dt__15SequenceControlFv */
long __dt__15SequenceControlFv(long param_1,short param_2)

{
  int iVar1;
  int *piVar2;
  
  if (param_1 != 0) {
    piVar2 = (int *)param_1;
    piVar2[8] = (int)__vt__15SequenceControl;
    iVar1 = *piVar2;
    if ((iVar1 != 0) && (iVar1 != 0)) {
      (**(code **)(*(int *)(iVar1 + 0x20) + 8))(iVar1,1);
    }
    if (piVar2[3] != 0) {
      __destroy_new_array(piVar2[3],0x245a60);
    }
    if (piVar2[4] != 0) {
      __destroy_new_array(piVar2[4],0x2455a0);
    }
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* ---- 0x002455f0 size 0x54  SequenceControl::getProgress(v)
 *      mangled: getProgress__15SequenceControlFv */
float getProgress__15SequenceControlFv(int param_1)

{
  return *(float *)(param_1 + 0x1c) /
         ((float)*(ushort *)(*(int *)(param_1 + 8) + 0x10) * *(float *)(param_1 + 0x14));
}

/* ---- 0x00245650 size 0xc  SequenceControl::getMotionName(v)
 *      mangled: getMotionName__15SequenceControlFv */
int getMotionName__15SequenceControlFv(int param_1)

{
  return *(int *)(param_1 + 8) + 4;
}

/* ---- 0x00245660 size 0x8  SequenceControl::setInterData(P5Modelii)
 *      mangled: setInterData__15SequenceControlFP5Modelii */
void setInterData__15SequenceControlFP5Modelii(void)

{
  return;
}

/* ---- 0x00245670 size 0xa0  SequenceControl::addTime(f)
 *      mangled: addTime__15SequenceControlFf */
int __thiscall SequenceControl::addTime__15SequenceControlFf(SequenceControl *this,float dt)

{
  int iVar1;
  float fVar2;
  float fVar3;
  
  iVar1 = 0;
  fVar2 = (float)*(ushort *)(this->pHdr + 0x10) * this->flFrameTime;
  if ((short)this->nField18 == 0) {
    fVar3 = this->flCurTime + dt;
    this->flCurTime = fVar3;
    if (fVar2 < fVar3) {
      if ((this->pHdr[0x14] & 1) == 0) {
        this->flCurTime = fVar2;
        *(u16 *)&this->nField18 = 1;
      }
      else {
        this->flCurTime = fVar3 - fVar2;
      }
      iVar1 = 1;
    }
  }
  return iVar1;
}

/* ---- 0x00245710 size 0x9c  SequenceControl::SeachSequence(PUc)
 *      mangled: SeachSequence__15SequenceControlFPUc */
long SeachSequence__15SequenceControlFPUc(int param_1,u64 param_2)

{
  long lVar1;
  int iVar2;
  int iVar3;
  
  if (*(int *)(param_1 + 0xc) == 0) {
    lVar1 = 0;
  }
  else {
    lVar1 = 0;
    iVar3 = 0;
    iVar2 = 0;
    while ((iVar3 < (int)(uint)*(ushort *)(*(int *)(param_1 + 8) + 0x12) && (lVar1 == 0))) {
      lVar1 = SeachSequence__8SequenceFPUc(*(int *)(param_1 + 0xc) + iVar2,param_2);
      iVar2 = iVar2 + 0x24;
      iVar3 = iVar3 + 1;
    }
  }
  return lVar1;
}

/* ---- 0x002457b0 size 0x6c  SequenceControl::SeachSequenceControl(PUc)
 *      mangled: SeachSequenceControl__15SequenceControlFPUc */
u64 SeachSequenceControl__15SequenceControlFPUc(u64 param_1,u64 param_2)

{
  int iVar1;
  
  iVar1 = strncmp((char *)(((int *)param_1)[2] + 4),(char *)param_2,0xc);
  if (iVar1 != 0) {
    iVar1 = *(int *)param_1;
    param_1 = 0;
    if (iVar1 != 0) {
      param_1 = SeachSequenceControl__15SequenceControlFPUc(iVar1,param_2);
    }
  }
  return param_1;
}

/* ---- 0x00245820 size 0x1f8  SequenceControl::Cleate(PUc)
 *      mangled: Cleate__15SequenceControlFPUc */
/* SequenceControl::Cleate: parses "SQHD" motion file: 0x20 header, nSeq bone tracks (rot keys
   s16/4096, trans SVector), nEvent event tracks. See notes/C/motion_format.md */

byte * __thiscall SequenceControl::Cleate__15SequenceControlFPUc(SequenceControl *this,byte *sqhd)

{
  ushort uVar1;
  void *pvVar2;
  u64 uVar3;
  byte *pbVar4;
  int iVar5;
  int iVar6;
  byte *pbVar7;
  
  this->pHdr = sqhd;
  uVar1 = *(ushort *)(this->pHdr + 0x12);
  uVar3 = __nwa__FUi((uint)uVar1 * 0x24 + 0x10);
  pvVar2 = (void *)__construct_new_array(uVar3,0x245a30,0x245a60,0x24,uVar1);
  this->pSequences = pvVar2;
  pbVar7 = sqhd + 0x20;
  pbVar4 = this->pHdr;
  iVar6 = 0;
  if (*(short *)(pbVar4 + 0x12) != 0) {
    iVar5 = 0;
    do {
      pbVar7 = (byte *)Cleate__8SequenceFPUcP15SequenceControl
                                 ((int)this->pSequences + iVar5,pbVar7,this);
      pbVar4 = this->pHdr;
      iVar6 = iVar6 + 1;
      iVar5 = iVar5 + 0x24;
    } while (iVar6 < (int)(uint)*(ushort *)(pbVar4 + 0x12));
  }
  uVar1 = *(ushort *)(pbVar4 + 0x16);
  if (uVar1 != 0) {
    uVar3 = __nwa__FUi((uint)uVar1 * 0x14 + 0x10);
    pvVar2 = (void *)__construct_new_array(uVar3,0x245a20,0x2455a0,0x14,uVar1);
    this->pEvents = pvVar2;
    pbVar4 = this->pHdr;
    iVar6 = 0;
    if (*(short *)(pbVar4 + 0x16) != 0) {
      iVar5 = 0;
      do {
        pbVar7 = (byte *)Cleate__5EventFPUcP15SequenceControl
                                   ((int)this->pEvents + iVar5,pbVar7,this);
        pbVar4 = this->pHdr;
        iVar6 = iVar6 + 1;
        iVar5 = iVar5 + 0x14;
      } while (iVar6 < (int)(uint)*(ushort *)(pbVar4 + 0x16));
    }
  }
  if (pbVar4 == (byte *)0x0) {
    this->flFrameTime = 0.016666668;
  }
  else {
    this->flFrameTime = 1.0 / (float)pbVar4[0x15];
  }
  pbVar4 = this->pHdr;
  if (*(short *)(pbVar4 + 0x1a) == 0) {
    *(short *)(pbVar4 + 0x10) = *(short *)(pbVar4 + 0x10) + -1;
    pbVar4 = this->pHdr;
    pbVar4[0x1a] = 1;
    pbVar4[0x1b] = 0;
  }
  return pbVar7;
}

/* ---- 0x00245af0 size 0xb0  Sequence::Cleate(PUcP15SequenceControl)
 *      mangled: Cleate__8SequenceFPUcP15SequenceControl */
void Cleate__8SequenceFPUcP15SequenceControl(int param_1,int param_2,u64 param_3)

{
  u64 uVar1;
  u32 uVar2;
  long lVar3;
  
  *(int *)(param_1 + 8) = (int)param_3;
  *(int *)(param_1 + 0xc) = param_2;
  lVar3 = __nw__FUi(0x14);
  uVar2 = (u32)lVar3;
  if (lVar3 != 0) {
    uVar2 = __ct__7RotAnimFUs(lVar3,*(u16 *)(*(int *)(param_1 + 0xc) + 0x10));
  }
  *(u32 *)(param_1 + 0x10) = uVar2;
  lVar3 = __nw__FUi(0x14);
  uVar2 = (u32)lVar3;
  if (lVar3 != 0) {
    uVar2 = __ct__10TranceAnimFUs(lVar3,*(u16 *)(*(int *)(param_1 + 0xc) + 0x12));
  }
  *(u32 *)(param_1 + 0x14) = uVar2;
  uVar1 = Cleate__7RotAnimFPUcP15SequenceControl
                    (*(u32 *)(param_1 + 0x10),param_2 + 0x20,param_3);
  Cleate__10TranceAnimFPUcP15SequenceControl(*(u32 *)(param_1 + 0x14),uVar1,param_3);
  return;
}

/* ---- 0x00245d60 size 0xc0  Event::Cleate(PUcP15SequenceControl)
 *      mangled: Cleate__5EventFPUcP15SequenceControl */
int Cleate__5EventFPUcP15SequenceControl(u32 *param_1,int param_2,u32 param_3)

{
  ushort uVar1;
  int iVar2;
  uint uVar3;
  byte bVar4;
  uint uVar5;
  
  *param_1 = param_3;
  param_1[1] = param_2;
  param_2 = param_2 + 0x10;
  param_1[2] = param_2;
  bVar4 = *(byte *)(param_1[1] + 0xc) & 0xf;
  uVar5 = 2;
  if (bVar4 != 3) {
    uVar5 = 4;
  }
  uVar1 = *(ushort *)(param_1[1] + 8);
  if (uVar5 == 0) {
    trap(7);
  }
  if ((uint)uVar1 % uVar5 == 0) {
    uVar3 = uVar1 / uVar5;
    if (uVar5 == 0) {
      trap(7);
    }
  }
  else {
    if (uVar5 == 0) {
      trap(7);
    }
    uVar3 = uVar1 / uVar5 + 1;
  }
  iVar2 = uVar3 * uVar5;
  if (bVar4 == 2) {
    param_2 = param_2 + iVar2 * 8;
  }
  else if (bVar4 == 3) {
    param_2 = param_2 + iVar2 * 8;
  }
  else {
    param_2 = param_2 + iVar2 * 4;
  }
  return param_2;
}

/* ---- 0x00245e20 size 0x98  SequenceControl::eventaddTime(fP5Model)
 *      mangled: eventaddTime__15SequenceControlFfP5Model */
void eventaddTime__15SequenceControlFfP5Model(u32 param_1,int param_2,u64 param_3)

{
  short sVar1;
  int iVar2;
  int iVar3;
  
  sVar1 = *(short *)(*(int *)(param_2 + 8) + 0x16);
  if ((sVar1 != 0) && (iVar2 = 0, sVar1 != 0)) {
    iVar3 = 0;
    do {
      addTime__5EventFfP5Model(param_1,*(int *)(param_2 + 0x10) + iVar3,param_3);
      iVar2 = iVar2 + 1;
      iVar3 = iVar3 + 0x14;
    } while (iVar2 < (int)(uint)*(ushort *)(*(int *)(param_2 + 8) + 0x16));
  }
  return;
}

/* ---- 0x00245ec0 size 0x8c  SequenceControl::setCTime(f)
 *      mangled: setCTime__15SequenceControlFf */
void setCTime__15SequenceControlFf(u32 param_1,int param_2)

{
  short sVar1;
  int iVar2;
  int iVar3;
  
  *(u32 *)(param_2 + 0x1c) = param_1;
  *(u16 *)(param_2 + 0x18) = 0;
  sVar1 = *(short *)(*(int *)(param_2 + 8) + 0x16);
  if ((sVar1 != 0) && (iVar3 = 0, sVar1 != 0)) {
    iVar2 = 0;
    do {
      setIndex__5EventFf(param_1,*(int *)(param_2 + 0x10) + iVar2);
      iVar3 = iVar3 + 1;
      iVar2 = iVar2 + 0x14;
    } while (iVar3 < (int)(uint)*(ushort *)(*(int *)(param_2 + 8) + 0x16));
  }
  return;
}

