// decomp/D/JRing_Shard.c — cleaned Ghidra output (SLPM_602.19, Metrowerks MIPS), Shadow Hearts: Covenant JP demo.
// Field accesses are shown as this->T_off (T = u8/u16/u32/f32/i32/p, off = hex offset);
// JRing fields are named from the recovered struct. See notes/D/*.md for layouts.
// CAVEAT: when the base pointer is a float*/int*/short*, the number in `T_off` is an ELEMENT offset (byte offset = off*sizeof(elem)).
// `this` is the C++ this pointer (param_1); the Metrowerks ABI passes it in a0.

// JP: 0x002e80a0  __ct__10CrackJRingFP5JRingib  =  CrackJRing::CrackJRing
undefined8
CrackJRing::CrackJRing(undefined8 this,undefined4 param_2,undefined4 param_3,char param_4)

{
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = (undefined4 *)this;
  puVar2[0xc] = in_zero_lo;
  puVar2[0xd] = in_zero_hi;
  puVar2[0xe] = in_zero_udw;
  puVar2[0xf] = in_register_0000000c;
  *puVar2 = param_2;
  puVar2[1] = 0;
  puVar2[2] = 0;
  puVar2[3] = 0;
  puVar2[5] = param_3;
  puVar2[6] = 0;
  puVar2[7] = 0x3f800000;
  puVar2[8] = 0;
  puVar2[0xc] = 0;
  puVar2[0xd] = 0;
  puVar2[0xe] = 0;
  puVar2[0xf] = 0x3f800000;
  puVar2[0x10] = 0;
  if (puVar2[5] == 2) {
    puVar2[8] = 0x3e19999a;
    iVar1 = rand();
    puVar2[0xc] = ((float)iVar1 / 2.1474836e+09) * 16.0 - 8.0;
    iVar1 = rand();
    puVar2[0xd] = ((float)iVar1 / 2.1474836e+09) * 16.0 - 8.0;
  }
  if (param_4 == '\x01') {
    CrackJRing::Initialize2(this);
  }
  else {
    CrackJRing::Initialize1(this);
  }
  return this;
}

// JP: 0x002e8260  __dt__10CrackJRingFv  =  CrackJRing::~CrackJRing
int CrackJRing::~CrackJRing(int this,short param_2)

{
  if (this != 0) {
    if ((this->i32_4 != 0) && (this->i32_4 != 0)) {
      __dla(this->i32_4 + -0x10);
    }
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x002e82f0  Update__10CrackJRingFf  =  CrackJRing::Update
void CrackJRing::Update(float this,int *param_2)

{
  int iVar1;
  uint uVar2;
  
  if (param_2[1] != 0) {
    param_2[6] = (int)((float)param_2[6] + this);
    if ((float)param_2[8] != 0.0) {
      param_2[8] = (int)((float)param_2[8] - this);
      if ((float)param_2[8] <= 0.0) {
        param_2[8] = 0;
        param_2[0xc] = 0;
        param_2[0xd] = 0;
      }
      else if (0.1 <= (float)param_2[8]) {
        iVar1 = rand();
        param_2[0xc] = (int)(((float)iVar1 / 2.1474836e+09) * 16.0 - 8.0);
        iVar1 = rand();
        param_2[0xd] = (int)(((float)iVar1 / 2.1474836e+09) * 16.0 - 8.0);
      }
      else {
        iVar1 = rand();
        param_2[0xc] = (int)(((float)param_2[8] / 0.1) *
                            (((float)iVar1 / 2.1474836e+09) * 16.0 - 8.0));
        iVar1 = rand();
        param_2[0xd] = (int)(((float)param_2[8] / 0.1) *
                            (((float)iVar1 / 2.1474836e+09) * 16.0 - 8.0));
      }
    }
    iVar1 = param_2[5];
    if (iVar1 == 2) {
      if (0.33333334 <= (float)param_2[6]) {
        for (uVar2 = 0; uVar2 < (uint)param_2[2]; uVar2 = uVar2 + 1) {
          iVar1 = param_2[1] + uVar2 * 0x80;
          iVar1->f32_10 =
               iVar1->f32_10 +
               (float)param_2[4] * this * (*(float *)(param_2[1] + uVar2 * 0x80 + 0x10) - 128.0);
          iVar1 = param_2[1] + uVar2 * 0x80;
          iVar1->f32_14 =
               iVar1->f32_14 +
               (float)param_2[4] * this * (*(float *)(param_2[1] + uVar2 * 0x80 + 0x14) - 128.0);
          iVar1 = param_2[1] + uVar2 * 0x80;
          iVar1->f32_20 =
               iVar1->f32_20 +
               ((float)param_2[4] + 1.0) * this * *(float *)(param_2[1] + uVar2 * 0x80 + 0x30);
          iVar1 = param_2[1] + uVar2 * 0x80;
          iVar1->f32_24 =
               iVar1->f32_24 +
               ((float)param_2[4] + 1.0) * this * *(float *)(param_2[1] + uVar2 * 0x80 + 0x34);
        }
        param_2[4] = (int)((float)param_2[4] - this * 4.5);
        param_2[3] = (int)((float)param_2[3] - this * 1.5 * *(float *)(*param_2 + 0xb8));
        if ((float)param_2[3] < 0.0) {
          param_2[3] = 0;
        }
      }
    }
    else if (iVar1 == 1) {
      if ((float)param_2[6] < 0.15) {
        for (uVar2 = 0; uVar2 < (uint)param_2[2]; uVar2 = uVar2 + 1) {
          iVar1 = param_2[1] + uVar2 * 0x80;
          iVar1->f32_10 =
               iVar1->f32_10 +
               (float)param_2[4] * this * (*(float *)(param_2[1] + uVar2 * 0x80 + 0x10) - 128.0);
          iVar1 = param_2[1] + uVar2 * 0x80;
          iVar1->f32_14 =
               iVar1->f32_14 +
               (float)param_2[4] * this * (*(float *)(param_2[1] + uVar2 * 0x80 + 0x14) - 128.0);
          iVar1 = param_2[1] + uVar2 * 0x80;
          iVar1->f32_20 =
               iVar1->f32_20 +
               ((float)param_2[4] + 1.0) * this * *(float *)(param_2[1] + uVar2 * 0x80 + 0x30);
          iVar1 = param_2[1] + uVar2 * 0x80;
          iVar1->f32_24 =
               iVar1->f32_24 +
               ((float)param_2[4] + 1.0) * this * *(float *)(param_2[1] + uVar2 * 0x80 + 0x34);
        }
        param_2[4] = (int)((float)param_2[4] - this * 4.5);
        param_2[3] = (int)((float)param_2[3] - this * 1.5 * *(float *)(*param_2 + 0xb8));
        if ((float)param_2[3] < 0.0) {
          param_2[3] = 0;
        }
      }
      else {
        param_2[7] = (int)((float)param_2[7] + this * 60.0);
        for (uVar2 = 0; uVar2 < (uint)param_2[2]; uVar2 = uVar2 + 1) {
          iVar1 = param_2[1] + uVar2 * 0x80;
          iVar1->f32_14 = iVar1->f32_14 + (float)param_2[7];
          iVar1 = param_2[1] + uVar2 * 0x80;
          iVar1->f32_20 =
               iVar1->f32_20 +
               ((float)param_2[4] + 1.0) * this * *(float *)(param_2[1] + uVar2 * 0x80 + 0x30);
          iVar1 = param_2[1] + uVar2 * 0x80;
          iVar1->f32_24 =
               iVar1->f32_24 +
               ((float)param_2[4] + 1.0) * this * *(float *)(param_2[1] + uVar2 * 0x80 + 0x34);
        }
        param_2[4] = (int)((float)param_2[4] - this * 4.5);
        param_2[3] = (int)((float)param_2[3] - this * 1.5 * *(float *)(*param_2 + 0xb8));
        if ((float)param_2[3] < 0.0) {
          param_2[3] = 0;
        }
      }
    }
    else if (iVar1 == 0) {
      for (uVar2 = 0; uVar2 < (uint)param_2[2]; uVar2 = uVar2 + 1) {
        iVar1 = param_2[1] + uVar2 * 0x80;
        iVar1->f32_10 =
             iVar1->f32_10 +
             (float)param_2[4] * this * (*(float *)(param_2[1] + uVar2 * 0x80 + 0x10) - 128.0);
        iVar1 = param_2[1] + uVar2 * 0x80;
        iVar1->f32_14 =
             iVar1->f32_14 +
             (float)param_2[4] * this * (*(float *)(param_2[1] + uVar2 * 0x80 + 0x14) - 128.0);
        iVar1 = param_2[1] + uVar2 * 0x80;
        iVar1->f32_20 =
             iVar1->f32_20 +
             ((float)param_2[4] + 1.0) * this * *(float *)(param_2[1] + uVar2 * 0x80 + 0x30);
        iVar1 = param_2[1] + uVar2 * 0x80;
        iVar1->f32_24 =
             iVar1->f32_24 +
             ((float)param_2[4] + 1.0) * this * *(float *)(param_2[1] + uVar2 * 0x80 + 0x34);
      }
      param_2[4] = (int)((float)param_2[4] - this * 4.5);
      param_2[3] = (int)((float)param_2[3] - this * 1.5 * *(float *)(*param_2 + 0xb8));
      if ((float)param_2[3] < 0.0) {
        param_2[3] = 0;
      }
    }
    param_2[0x10] = param_2[0x10] + 1;
  }
  return;
}

// JP: 0x002e8d60  MakePacket__10CrackJRingFP4_QWD  =  CrackJRing::MakePacket
ulong * CrackJRing::MakePacket(int *this,ulong *param_2)

{
  undefined1 auVar1 [16];
  undefined1 auVar2 [16];
  undefined1 auVar3 [16];
  undefined1 auVar4 [16];
  undefined1 auVar5 [16];
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  undefined1 auVar8 [16];
  undefined1 auVar9 [16];
  undefined1 auVar10 [16];
  undefined1 auVar11 [16];
  undefined1 auVar12 [12];
  undefined1 auVar13 [12];
  float in_zero_lo;
  float in_zero_hi;
  float in_zero_udw;
  float in_register_0000000c;
  int iVar14;
  int iVar15;
  ulong uVar16;
  undefined8 extraout_v0_udw;
  undefined8 extraout_v0_udw_00;
  undefined1 auVar17 [16];
  undefined1 auVar18 [16];
  undefined8 extraout_v0_udw_01;
  undefined8 extraout_v0_udw_02;
  undefined1 auVar19 [16];
  undefined8 extraout_v0_udw_03;
  undefined8 uVar21;
  undefined1 auVar20 [16];
  float *pfVar22;
  uint uVar23;
  long lVar24;
  float fVar25;
  float fVar26;
  undefined1 in_vf0 [16];
  undefined1 auVar27 [16];
  undefined1 auVar28 [16];
  undefined1 auVar29 [16];
  undefined1 auStack_bc0 [16];
  undefined1 auStack_bb0 [16];
  undefined1 auStack_ba0 [16];
  undefined1 auStack_b90 [16];
  undefined1 auStack_b80 [16];
  undefined1 auStack_b70 [16];
  undefined4 uStack_b60;
  undefined4 uStack_b5c;
  float fStack_b58;
  undefined4 uStack_b54;
  float fStack_b50;
  float fStack_b4c;
  float fStack_b48;
  float fStack_b44;
  undefined4 uStack_b40;
  undefined4 uStack_b3c;
  float fStack_b38;
  undefined4 uStack_b34;
  float fStack_b30;
  float fStack_b2c;
  float fStack_b28;
  float fStack_b24;
  undefined4 uStack_b20;
  undefined4 uStack_b1c;
  undefined4 uStack_b18;
  undefined4 uStack_b14;
  float fStack_b10;
  float fStack_b0c;
  float fStack_b08;
  float fStack_b04;
  undefined4 uStack_b00;
  undefined4 uStack_afc;
  undefined4 uStack_af8;
  undefined4 uStack_af4;
  float fStack_af0;
  float fStack_aec;
  float fStack_ae8;
  float fStack_ae4;
  float fStack_ae0;
  float fStack_adc;
  undefined4 uStack_ad8;
  undefined4 uStack_ad4;
  float fStack_ad0;
  float fStack_acc;
  undefined4 uStack_ac8;
  undefined4 uStack_ac4;
  undefined4 uStack_ac0;
  undefined4 uStack_abc;
  undefined4 uStack_ab8;
  undefined4 uStack_ab4;
  float fStack_ab0;
  float fStack_aac;
  undefined4 uStack_aa8;
  undefined4 uStack_aa4;
  float fStack_aa0;
  float fStack_a9c;
  undefined4 uStack_a98;
  undefined4 uStack_a94;
  float fStack_a90;
  float fStack_a8c;
  undefined4 uStack_a88;
  undefined4 uStack_a84;
  float fStack_a80;
  float fStack_a7c;
  undefined4 uStack_a78;
  undefined4 uStack_a74;
  float fStack_a70;
  float fStack_a6c;
  undefined4 uStack_a68;
  undefined4 uStack_a64;
  float fStack_a60;
  float fStack_a5c;
  undefined4 uStack_a58;
  undefined4 uStack_a54;
  float fStack_a50;
  float fStack_a4c;
  undefined4 uStack_a48;
  undefined4 uStack_a44;
  float fStack_a40;
  float fStack_a3c;
  float fStack_a38;
  float fStack_a34;
  float fStack_a30;
  float fStack_a2c;
  undefined4 uStack_a28;
  undefined4 uStack_a24;
  int aiStack_a20 [14];
  int iStack_9e8;
  int iStack_9e4;
  float fStack_9e0;
  float fStack_9dc;
  float fStack_9d8;
  float fStack_9d4;
  float fStack_9d0;
  float fStack_9cc;
  float fStack_9c8;
  float fStack_9c4;
  float fStack_9c0;
  float fStack_9bc;
  float fStack_9b8;
  float fStack_9b4;
  float fStack_9b0;
  float fStack_9ac;
  float fStack_9a8;
  float fStack_9a4;
  float fStack_9a0;
  float fStack_99c;
  float fStack_998;
  float fStack_994;
  undefined1 auStack_990 [16];
  undefined1 auStack_980 [16];
  undefined1 auStack_970 [16];
  undefined1 auStack_960 [16];
  float fStack_950;
  float fStack_94c;
  float fStack_948;
  float fStack_944;
  float fStack_940;
  float fStack_93c;
  float fStack_938;
  float fStack_934;
  float fStack_930;
  float fStack_92c;
  float fStack_928;
  float fStack_924;
  float fStack_920;
  float fStack_91c;
  float fStack_918;
  float fStack_914;
  float afStack_910 [576];
  float fStack_10;
  float fStack_c;
  float fStack_8;
  float fStack_4;
  
  iVar14 = 0;
  for (uVar23 = 0; uVar23 < (uint)this[2]; uVar23 = uVar23 + 1) {
    iVar14 = iVar14 + (uint)*(ushort *)(this[1] + uVar23 * 0x80 + 2);
  }
  if ((this[5] == 2) && ((float)this[6] < 0.5833334)) {
    *(short *)((int)this + 0x46) = (short)(int)(((float)this[6] / 0.33333334) * 80.0);
    if ((short)this[0x11] < *(short *)((int)this + 0x46)) {
      *(short *)((int)this + 0x46) = (short)this[0x11];
    }
    iVar14 = iVar14 + *(short *)((int)this + 0x46) * 4 + 5;
  }
  pfVar22 = afStack_910 + 0x120;
  do {
    *pfVar22 = in_zero_lo;
    pfVar22[1] = in_zero_hi;
    pfVar22[2] = in_zero_udw;
    pfVar22[3] = in_register_0000000c;
    pfVar22 = pfVar22 + 4;
  } while (pfVar22 != &fStack_10);
  pfVar22 = afStack_910;
  do {
    *pfVar22 = in_zero_lo;
    pfVar22[1] = in_zero_hi;
    pfVar22[2] = in_zero_udw;
    pfVar22[3] = in_register_0000000c;
    pfVar22 = pfVar22 + 4;
  } while (pfVar22 != afStack_910 + 0x120);
  auVar27 = _vmr32(in_vf0);
  auVar28 = _vmr32(auVar27);
  auVar29 = _vmr32(auVar28);
  auStack_960 = _sqc2(in_vf0);
  auStack_970 = _sqc2(auVar27);
  auStack_980 = _sqc2(auVar28);
  auStack_990 = _sqc2(auVar29);
  fVar25 = (float)(1 << (uint)(((ulong)*(byte *)((&JRing::JRTex)[*(int *)(*this + 0xe8)] + 0x53)
                               << 0x3a) >> 0x3c)) * 16.0;
  fVar26 = (float)(1 << (uint)((ulong)(*(long *)((&JRing::JRTex)[*(int *)(*this + 0xe8)] + 0x50)
                                      << 0x1e) >> 0x3c)) * 16.0;
  if ((float)this[3] != 0.0) {
    *(int *)param_2 = (int)&DAT_10000004 + iVar14;
    *(undefined4 *)((int)param_2 + 4) = 0;
    param_2->u32_1 = 0;
    *(int *)((int)param_2 + 0xc) = iVar14 + 0x50000004;
    param_2[2] = 0x1000000000000001;
    param_2[3] = 0xe;
    param_2[4] = 0x44;
    param_2[5] = 0x42;
    param_2[6] = 0x2400000000000001;
    param_2[7] = 6;
    fStack_9e0 = in_zero_lo;
    fStack_9dc = in_zero_hi;
    fStack_9d8 = in_zero_udw;
    fStack_9d4 = in_register_0000000c;
    fStack_9d0 = in_zero_lo;
    fStack_9cc = in_zero_hi;
    fStack_9c8 = in_zero_udw;
    fStack_9c4 = in_register_0000000c;
    fStack_9c0 = in_zero_lo;
    fStack_9bc = in_zero_hi;
    fStack_9b8 = in_zero_udw;
    fStack_9b4 = in_register_0000000c;
    fStack_9b0 = in_zero_lo;
    fStack_9ac = in_zero_hi;
    fStack_9a8 = in_zero_udw;
    fStack_9a4 = in_register_0000000c;
    fStack_9a0 = in_zero_lo;
    fStack_99c = in_zero_hi;
    fStack_998 = in_zero_udw;
    fStack_994 = in_register_0000000c;
    fStack_950 = in_zero_lo;
    fStack_94c = in_zero_hi;
    fStack_948 = in_zero_udw;
    fStack_944 = in_register_0000000c;
    fStack_940 = in_zero_lo;
    fStack_93c = in_zero_hi;
    fStack_938 = in_zero_udw;
    fStack_934 = in_register_0000000c;
    fStack_930 = in_zero_lo;
    fStack_92c = in_zero_hi;
    fStack_928 = in_zero_udw;
    fStack_924 = in_register_0000000c;
    fStack_920 = in_zero_lo;
    fStack_91c = in_zero_hi;
    fStack_918 = in_zero_udw;
    fStack_914 = in_register_0000000c;
    uVar16 = JRCTex::GetTex0((&JRing::JRTex)[*(int *)(*this + 0xe8)],1);
    param_2[8] = uVar16;
    param_2[9] = 0x5c;
    param_2 = param_2 + 10;
    for (uVar23 = 0; uVar23 < (uint)this[2]; uVar23 = uVar23 + 1) {
      fStack_a2c = *(float *)(*this + 0x84) *
                   (*(float *)(this[1] + uVar23 * 0x80 + 0x14) - 114.0);
      fStack_a30 = *(float *)(*this + 0x84) *
                   (*(float *)(this[1] + uVar23 * 0x80 + 0x10) - 114.0);
      uStack_a28 = 0;
      uStack_a24 = 0x3f800000;
      afStack_910[uVar23 * 4 + 0x120] = fStack_a30;
      afStack_910[uVar23 * 4 + 0x121] = fStack_a2c;
      afStack_910[uVar23 * 4 + 0x122] = 0.0;
      afStack_910[uVar23 * 4 + 0x123] = 1.0;
    }
    auVar27 = _vmr32(in_vf0);
    auVar28 = _vmr32(auVar27);
    auVar29 = _vmr32(auVar28);
    auStack_960 = _sqc2(in_vf0);
    auStack_970 = _sqc2(auVar27);
    auStack_980 = _sqc2(auVar28);
    auStack_990 = _sqc2(auVar29);
    sceVu0RotMatrixZ(*(undefined4 *)(*this + 0x78),auStack_990,auStack_990);
    sceVu0RotMatrixX(*(undefined4 *)(*this + 0x70),auStack_990,auStack_990);
    sceVu0RotMatrixY(*(undefined4 *)(*this + 0x74),auStack_990,auStack_990);
    RotTransVector(afStack_910,afStack_910 + 0x120,auStack_990,this[2]);
    uVar21 = extraout_v0_udw;
    for (uVar23 = 0; uVar23 < (uint)this[2]; uVar23 = uVar23 + 1) {
      auVar27 = _lqc2(*(undefined1 (*) [16])(this[1] + uVar23 * 0x80 + 0x20));
      auVar28 = _lqc2(*(undefined1 (*) [16])(*this + 0x70));
      auVar27 = _vadd(auVar27,auVar28);
      auStack_b70 = _sqc2(auVar27);
      FVector::FVector(&fStack_a40,auStack_b70);
      fStack_9a0 = fStack_a40;
      fStack_99c = fStack_a3c;
      fStack_998 = fStack_a38;
      fStack_994 = fStack_a34;
      auVar27 = _vmr32(in_vf0);
      auVar28 = _vmr32(auVar27);
      auVar29 = _vmr32(auVar28);
      auStack_960 = _sqc2(in_vf0);
      auStack_970 = _sqc2(auVar27);
      auStack_980 = _sqc2(auVar28);
      auStack_990 = _sqc2(auVar29);
      sceVu0RotMatrixZ(fStack_a38,auStack_990,auStack_990);
      sceVu0RotMatrixX(fStack_9a0,auStack_990,auStack_990);
      sceVu0RotMatrixY(fStack_99c,auStack_990,auStack_990);
      if (*(short *)(this[1] + uVar23 * 0x80) == 0) {
        fStack_a4c = *(float *)(*this + 0x84) * *(float *)(this[1] + uVar23 * 0x80 + 0x44);
        fStack_a50 = *(float *)(*this + 0x84) * *(float *)(this[1] + uVar23 * 0x80 + 0x40);
        uStack_a48 = 0;
        uStack_a44 = 0x3f800000;
        fStack_948 = 0.0;
        fStack_944 = 1.0;
        fStack_a5c = *(float *)(*this + 0x84) * *(float *)(this[1] + uVar23 * 0x80 + 0x54);
        fStack_a60 = *(float *)(*this + 0x84) * *(float *)(this[1] + uVar23 * 0x80 + 0x50);
        uStack_a58 = 0;
        uStack_a54 = 0x3f800000;
        fStack_938 = 0.0;
        fStack_934 = 1.0;
        fStack_a6c = *(float *)(*this + 0x84) * *(float *)(this[1] + uVar23 * 0x80 + 100);
        fStack_a70 = *(float *)(*this + 0x84) * *(float *)(this[1] + uVar23 * 0x80 + 0x60);
        uStack_a68 = 0;
        uStack_a64 = 0x3f800000;
        fStack_928 = 0.0;
        fStack_924 = 1.0;
        fStack_a7c = *(float *)(*this + 0x84) * *(float *)(this[1] + uVar23 * 0x80 + 0x74);
        fStack_a80 = *(float *)(*this + 0x84) * *(float *)(this[1] + uVar23 * 0x80 + 0x70);
        uStack_a78 = 0;
        uStack_a74 = 0x3f800000;
        fStack_918 = 0.0;
        fStack_914 = 1.0;
        fStack_950 = fStack_a50;
        fStack_94c = fStack_a4c;
        fStack_940 = fStack_a60;
        fStack_93c = fStack_a5c;
        fStack_930 = fStack_a70;
        fStack_92c = fStack_a6c;
        fStack_920 = fStack_a80;
        fStack_91c = fStack_a7c;
        RotTransVector(&fStack_9e0,&fStack_950,auStack_990,4);
        for (iVar14 = 0; iVar14 < 4; iVar14 = iVar14 + 1) {
          auVar28 = _lqc2(*(undefined1 (*) [16])(afStack_910 + uVar23 * 4));
          auVar27 = _lqc2(*(undefined1 (*) [16])(&fStack_9e0 + iVar14 * 4));
          auVar27 = _vadd(auVar27,auVar28);
          auVar27 = _sqc2(auVar27);
          *(undefined1 (*) [16])(&fStack_9e0 + iVar14 * 4) = auVar27;
        }
        sceVu0RotTransPersN(aiStack_a20,*this + 0x590,&fStack_9e0,4,0);
        for (iVar14 = 0; iVar14 < 4; iVar14 = iVar14 + 1) {
          aiStack_a20[iVar14 * 4] =
               (int)((float)aiStack_a20[iVar14 * 4] +
                    ((*(float *)(*this + 0x68) + (float)this[0xc]) - 256.0) * 16.0);
          aiStack_a20[iVar14 * 4 + 1] =
               (int)((float)aiStack_a20[iVar14 * 4 + 1] +
                    ((*(float *)(*this + 0x6c) + (float)this[0xd]) - 224.0) * 16.0);
          aiStack_a20[iVar14 * 4 + 2] = (int)((float)aiStack_a20[iVar14 * 4 + 2] / 16.0);
        }
        if ((uVar23 + 1 != this[2]) || ((this[5] == 2 && ((float)this[6] < 0.5833334)))) {
          auVar18._8_8_ = extraout_v0_udw_00;
          auVar18._0_8_ = 0xc400000000000001;
          auVar2._4_4_ = in_zero_hi;
          auVar2._0_4_ = in_zero_lo;
          auVar2._8_4_ = in_zero_udw;
          auVar2._12_4_ = in_register_0000000c;
          auVar27 = _pcpyld(auVar2,auVar18);
          *param_2 = auVar27._0_8_;
        }
        else {
          auVar17._8_8_ = extraout_v0_udw_00;
          auVar17._0_8_ = 0xc400000000008001;
          auVar3._4_4_ = in_zero_hi;
          auVar3._0_4_ = in_zero_lo;
          auVar3._8_4_ = in_zero_udw;
          auVar3._12_4_ = in_register_0000000c;
          auVar27 = _pcpyld(auVar3,auVar17);
          *param_2 = auVar27._0_8_;
        }
        param_2[1] = 0x412412c12c12;
        fStack_4 = 16.0 / (float)aiStack_a20[3];
        fStack_8 = fStack_4 * (*(float *)(this[1] + uVar23 * 0x80 + 0x48) / fVar25);
        fStack_c = fStack_4 * (*(float *)(this[1] + uVar23 * 0x80 + 0x4c) / fVar26);
        param_2[2] = CONCAT44(fStack_c,fStack_8);
        lVar24 = __fixunssfdi((float)this[3] * 128.0);
        param_2[3] = lVar24 << 0x18 | 0x808080U | (ulong)(uint)fStack_4 << 0x20;
        param_2[4] = (long)aiStack_a20[2] << 0x20 |
                     (long)aiStack_a20[0] | (long)aiStack_a20[1] << 0x10;
        fStack_4 = 16.0 / (float)aiStack_a20[7];
        fStack_8 = fStack_4 * (*(float *)(this[1] + uVar23 * 0x80 + 0x58) / fVar25);
        fStack_c = fStack_4 * (*(float *)(this[1] + uVar23 * 0x80 + 0x5c) / fVar26);
        param_2[5] = CONCAT44(fStack_c,fStack_8);
        lVar24 = __fixunssfdi((float)this[3] * 128.0);
        param_2[6] = lVar24 << 0x18 | 0x808080U | (ulong)(uint)fStack_4 << 0x20;
        param_2[7] = (long)aiStack_a20[6] << 0x20 |
                     (long)aiStack_a20[4] | (long)aiStack_a20[5] << 0x10;
        fStack_4 = 16.0 / (float)aiStack_a20[0xb];
        fStack_8 = fStack_4 * (*(float *)(this[1] + uVar23 * 0x80 + 0x68) / fVar25);
        fStack_c = fStack_4 * (*(float *)(this[1] + uVar23 * 0x80 + 0x6c) / fVar26);
        param_2[8] = CONCAT44(fStack_c,fStack_8);
        lVar24 = __fixunssfdi((float)this[3] * 128.0);
        param_2[9] = lVar24 << 0x18 | 0x808080U | (ulong)(uint)fStack_4 << 0x20;
        param_2[10] = (long)aiStack_a20[10] << 0x20 |
                      (long)aiStack_a20[8] | (long)aiStack_a20[9] << 0x10;
        fStack_4 = 16.0 / (float)iStack_9e4;
        fStack_8 = fStack_4 * (*(float *)(this[1] + uVar23 * 0x80 + 0x78) / fVar25);
        fStack_c = fStack_4 * (*(float *)(this[1] + uVar23 * 0x80 + 0x7c) / fVar26);
        param_2[0xb] = CONCAT44(fStack_c,fStack_8);
        lVar24 = __fixunssfdi((float)this[3] * 128.0);
        param_2[0xc] = lVar24 << 0x18 | 0x808080U | (ulong)(uint)fStack_4 << 0x20;
        param_2[0xd] = (long)iStack_9e8 << 0x20 |
                       (long)aiStack_a20[0xc] | (long)aiStack_a20[0xd] << 0x10;
        param_2 = param_2 + 0xe;
        uVar21 = extraout_v0_udw_01;
      }
      else {
        fStack_a8c = *(float *)(*this + 0x84) * *(float *)(this[1] + uVar23 * 0x80 + 0x44);
        fStack_a90 = *(float *)(*this + 0x84) * *(float *)(this[1] + uVar23 * 0x80 + 0x40);
        uStack_a88 = 0;
        uStack_a84 = 0x3f800000;
        fStack_948 = 0.0;
        fStack_944 = 1.0;
        fStack_a9c = *(float *)(*this + 0x84) * *(float *)(this[1] + uVar23 * 0x80 + 0x54);
        fStack_aa0 = *(float *)(*this + 0x84) * *(float *)(this[1] + uVar23 * 0x80 + 0x50);
        uStack_a98 = 0;
        uStack_a94 = 0x3f800000;
        fStack_938 = 0.0;
        fStack_934 = 1.0;
        fStack_aac = *(float *)(*this + 0x84) * *(float *)(this[1] + uVar23 * 0x80 + 100);
        fStack_ab0 = *(float *)(*this + 0x84) * *(float *)(this[1] + uVar23 * 0x80 + 0x60);
        uStack_aa8 = 0;
        uStack_aa4 = 0x3f800000;
        fStack_928 = 0.0;
        fStack_924 = 1.0;
        fStack_950 = fStack_a90;
        fStack_94c = fStack_a8c;
        fStack_940 = fStack_aa0;
        fStack_93c = fStack_a9c;
        fStack_930 = fStack_ab0;
        fStack_92c = fStack_aac;
        RotTransVector(&fStack_9e0,&fStack_950,auStack_990,3);
        for (iVar14 = 0; iVar14 < 3; iVar14 = iVar14 + 1) {
          auVar28 = _lqc2(*(undefined1 (*) [16])(afStack_910 + uVar23 * 4));
          auVar27 = _lqc2(*(undefined1 (*) [16])(&fStack_9e0 + iVar14 * 4));
          auVar27 = _vadd(auVar27,auVar28);
          auVar27 = _sqc2(auVar27);
          *(undefined1 (*) [16])(&fStack_9e0 + iVar14 * 4) = auVar27;
        }
        sceVu0RotTransPersN(aiStack_a20,*this + 0x590,&fStack_9e0,3,0);
        for (iVar14 = 0; iVar14 < 3; iVar14 = iVar14 + 1) {
          aiStack_a20[iVar14 * 4] =
               (int)((float)aiStack_a20[iVar14 * 4] +
                    ((*(float *)(*this + 0x68) + (float)this[0xc]) - 256.0) * 16.0);
          aiStack_a20[iVar14 * 4 + 1] =
               (int)((float)aiStack_a20[iVar14 * 4 + 1] +
                    ((*(float *)(*this + 0x6c) + (float)this[0xd]) - 224.0) * 16.0);
          aiStack_a20[iVar14 * 4 + 2] = (int)((float)aiStack_a20[iVar14 * 4 + 2] / 16.0);
        }
        if ((uVar23 + 1 != this[2]) || ((this[5] == 2 && ((float)this[6] < 0.5833334)))) {
          auVar28._8_8_ = extraout_v0_udw_02;
          auVar28._0_8_ = 0xa400000000000001;
          auVar27._4_4_ = in_zero_hi;
          auVar27._0_4_ = in_zero_lo;
          auVar27._8_4_ = in_zero_udw;
          auVar27._12_4_ = in_register_0000000c;
          auVar27 = _pcpyld(auVar27,auVar28);
          *param_2 = auVar27._0_8_;
        }
        else {
          auVar19._8_8_ = extraout_v0_udw_02;
          auVar19._0_8_ = 0xa400000000008001;
          auVar29._4_4_ = in_zero_hi;
          auVar29._0_4_ = in_zero_lo;
          auVar29._8_4_ = in_zero_udw;
          auVar29._12_4_ = in_register_0000000c;
          auVar27 = _pcpyld(auVar29,auVar19);
          *param_2 = auVar27._0_8_;
        }
        param_2[1] = 0xf412c12c12;
        fStack_4 = 16.0 / (float)aiStack_a20[3];
        fStack_8 = fStack_4 * (*(float *)(this[1] + uVar23 * 0x80 + 0x48) / fVar25);
        fStack_c = fStack_4 * (*(float *)(this[1] + uVar23 * 0x80 + 0x4c) / fVar26);
        param_2[2] = CONCAT44(fStack_c,fStack_8);
        lVar24 = __fixunssfdi((float)this[3] * 128.0);
        param_2[3] = lVar24 << 0x18 | 0x808080U | (ulong)(uint)fStack_4 << 0x20;
        param_2[4] = (long)aiStack_a20[2] << 0x20 |
                     (long)aiStack_a20[0] | (long)aiStack_a20[1] << 0x10;
        fStack_4 = 16.0 / (float)aiStack_a20[7];
        fStack_8 = fStack_4 * (*(float *)(this[1] + uVar23 * 0x80 + 0x58) / fVar25);
        fStack_c = fStack_4 * (*(float *)(this[1] + uVar23 * 0x80 + 0x5c) / fVar26);
        param_2[5] = CONCAT44(fStack_c,fStack_8);
        lVar24 = __fixunssfdi((float)this[3] * 128.0);
        param_2[6] = lVar24 << 0x18 | 0x808080U | (ulong)(uint)fStack_4 << 0x20;
        param_2[7] = (long)aiStack_a20[6] << 0x20 |
                     (long)aiStack_a20[4] | (long)aiStack_a20[5] << 0x10;
        fStack_4 = 16.0 / (float)aiStack_a20[0xb];
        fStack_8 = fStack_4 * (*(float *)(this[1] + uVar23 * 0x80 + 0x68) / fVar25);
        fStack_c = fStack_4 * (*(float *)(this[1] + uVar23 * 0x80 + 0x6c) / fVar26);
        param_2[8] = CONCAT44(fStack_c,fStack_8);
        lVar24 = __fixunssfdi((float)this[3] * 128.0);
        param_2[9] = lVar24 << 0x18 | 0x808080U | (ulong)(uint)fStack_4 << 0x20;
        param_2[10] = (long)aiStack_a20[10] << 0x20 |
                      (long)aiStack_a20[8] | (long)aiStack_a20[9] << 0x10;
        param_2[0xb] = 0;
        param_2 = param_2 + 0xc;
        uVar21 = extraout_v0_udw_03;
      }
    }
    if ((this[5] == 2) && ((float)this[6] < 0.5833334)) {
      *param_2 = 0x1000000000000001;
      param_2[1] = 0xe;
      param_2[2] = 0x48;
      param_2[3] = 0x42;
      param_2[4] = 0x2400000000000001;
      param_2[5] = 0xf0;
      param_2[6] = 0x4c;
      param_2[7] = 0;
      auVar20._8_8_ = uVar21;
      auVar20._0_8_ = 0x8000000000000000;
      auVar1._4_4_ = in_zero_hi;
      auVar1._0_4_ = in_zero_lo;
      auVar1._8_4_ = in_zero_udw;
      auVar1._12_4_ = in_register_0000000c;
      auVar27 = _pcpyld(auVar1,auVar20);
      param_2[8] = (long)*(short *)((int)this + 0x46) | 0x400000000008000U | auVar27._0_8_;
      param_2[9] = 0x4141c1c1;
      param_2 = param_2 + 10;
      auVar27 = _lqc2(*(undefined1 (*) [16])(this[1] + uVar23 * 0x80 + 0x20));
      auVar28 = _lqc2(*(undefined1 (*) [16])(*this + 0x70));
      auVar27 = _vadd(auVar27,auVar28);
      auStack_b80 = _sqc2(auVar27);
      FVector::FVector(&uStack_ac0,auStack_b80);
      fStack_9a0 = (float)uStack_ac0;
      fStack_99c = (float)uStack_abc;
      fStack_998 = (float)uStack_ab8;
      fStack_994 = (float)uStack_ab4;
      auVar27 = _vmr32(in_vf0);
      auVar28 = _vmr32(auVar27);
      auVar29 = _vmr32(auVar28);
      auStack_960 = _sqc2(in_vf0);
      auStack_970 = _sqc2(auVar27);
      auStack_980 = _sqc2(auVar28);
      auStack_990 = _sqc2(auVar29);
      sceVu0RotMatrixZ(*(undefined4 *)(*this + 0x78),auStack_990,auStack_990);
      sceVu0RotMatrixX(*(undefined4 *)(*this + 0x70),auStack_990,auStack_990);
      sceVu0RotMatrixY(*(undefined4 *)(*this + 0x74),auStack_990,auStack_990);
      if ((float)this[6] < 0.25) {
        fVar25 = (float)this[3] * 64.0;
        if (2.1474836e+09 <= fVar25) {
          fVar25 = fVar25 - 2.1474836e+09;
        }
        uVar16 = (long)(int)fVar25 & 0xff;
        fVar25 = 0.0;
      }
      else if ((float)this[6] < 0.4166667) {
        fVar25 = (((float)this[6] - 0.25) / 0.16666667) * 64.0 + 64.0;
        if (2.1474836e+09 <= fVar25) {
          fVar25 = fVar25 - 2.1474836e+09;
        }
        uVar16 = (long)(int)fVar25 & 0xff;
        fVar25 = ((float)this[6] - 0.25) / 0.16666667;
      }
      else {
        fVar25 = ((0.5833334 - (float)this[6]) / 0.16666667) * 128.0;
        if (2.1474836e+09 <= fVar25) {
          fVar25 = fVar25 - 2.1474836e+09;
        }
        uVar16 = (long)(int)fVar25 & 0xff;
        fVar25 = 1.0;
      }
      lVar24 = 0;
      while (lVar24 < *(short *)((int)this + 0x46)) {
        iVar14 = (int)lVar24;
        fStack_acc = (float)this[iVar14 * 4 + 0x13] * *(float *)(*this + 0x84);
        fStack_ad0 = (float)this[iVar14 * 4 + 0x12] * *(float *)(*this + 0x84);
        uStack_ac8 = 0;
        uStack_ac4 = 0x3f800000;
        fStack_948 = 0.0;
        fStack_944 = 1.0;
        fStack_adc = (float)this[iVar14 * 4 + 0x15] * *(float *)(*this + 0x84);
        fStack_ae0 = (float)this[iVar14 * 4 + 0x14] * *(float *)(*this + 0x84);
        uStack_ad8 = 0;
        uStack_ad4 = 0x3f800000;
        fStack_938 = 0.0;
        fStack_934 = 1.0;
        fStack_950 = fStack_ad0;
        fStack_94c = fStack_acc;
        fStack_940 = fStack_ae0;
        fStack_93c = fStack_adc;
        RotTransVector(&fStack_9e0,&fStack_950,auStack_990,2);
        if (fVar25 == 0.0) {
          uStack_b00 = 0;
          uStack_afc = 0;
          uStack_af8 = 0xc2c80000;
          uStack_af4 = 0x3f800000;
          auVar8._4_4_ = fStack_9dc;
          auVar8._0_4_ = fStack_9e0;
          auVar8._8_4_ = fStack_9d8;
          auVar8._12_4_ = fStack_9d4;
          auVar27 = _lqc2(auVar8);
          auVar7._12_4_ = 0x3f800000;
          auVar7._0_12_ = ZEXT412(0xc2c80000) << 0x40;
          auVar28 = _lqc2(auVar7);
          auVar27 = _vadd(auVar27,auVar28);
          auStack_b90 = _sqc2(auVar27);
          FVector::FVector(&fStack_af0,auStack_b90);
          fStack_9c0 = fStack_af0;
          fStack_9bc = fStack_aec;
          fStack_9b8 = fStack_ae8;
          fStack_9b4 = fStack_ae4;
          uStack_b20 = 0;
          uStack_b1c = 0;
          uStack_b18 = 0xc2c80000;
          uStack_b14 = 0x3f800000;
          auVar10._4_4_ = fStack_9cc;
          auVar10._0_4_ = fStack_9d0;
          auVar10._8_4_ = fStack_9c8;
          auVar10._12_4_ = fStack_9c4;
          auVar27 = _lqc2(auVar10);
          auVar6._12_4_ = 0x3f800000;
          auVar6._0_12_ = ZEXT412(0xc2c80000) << 0x40;
          auVar28 = _lqc2(auVar6);
          auVar27 = _vadd(auVar27,auVar28);
          auStack_ba0 = _sqc2(auVar27);
          FVector::FVector(&fStack_b10,auStack_ba0);
          fStack_9b0 = fStack_b10;
          fStack_9ac = fStack_b0c;
          fStack_9a8 = fStack_b08;
          fStack_9a4 = fStack_b04;
        }
        else {
          fStack_b38 = (-462.0 - (fStack_9d8 - 100.0)) * fVar25 - 100.0;
          fStack_94c = (-462.0 - (fStack_9c8 - 100.0)) * fVar25 - 100.0;
          uStack_b40 = 0;
          uStack_b3c = 0;
          uStack_b34 = 0x3f800000;
          auVar9._4_4_ = fStack_9dc;
          auVar9._0_4_ = fStack_9e0;
          auVar9._8_4_ = fStack_9d8;
          auVar9._12_4_ = fStack_9d4;
          auVar27 = _lqc2(auVar9);
          auVar12._4_8_ = 0;
          auVar12._0_4_ = fStack_b38;
          auVar5._12_4_ = 0x3f800000;
          auVar5._0_12_ = auVar12 << 0x40;
          auVar28 = _lqc2(auVar5);
          auVar27 = _vadd(auVar27,auVar28);
          auStack_bb0 = _sqc2(auVar27);
          fStack_950 = fStack_b38;
          FVector::FVector(&fStack_b30,auStack_bb0);
          fStack_9c0 = fStack_b30;
          fStack_9bc = fStack_b2c;
          fStack_9b8 = fStack_b28;
          fStack_9b4 = fStack_b24;
          uStack_b60 = 0;
          uStack_b5c = 0;
          fStack_b58 = fStack_94c;
          uStack_b54 = 0x3f800000;
          auVar11._4_4_ = fStack_9cc;
          auVar11._0_4_ = fStack_9d0;
          auVar11._8_4_ = fStack_9c8;
          auVar11._12_4_ = fStack_9c4;
          auVar27 = _lqc2(auVar11);
          auVar13._4_8_ = 0;
          auVar13._0_4_ = fStack_94c;
          auVar4._12_4_ = 0x3f800000;
          auVar4._0_12_ = auVar13 << 0x40;
          auVar28 = _lqc2(auVar4);
          auVar27 = _vadd(auVar27,auVar28);
          auStack_bc0 = _sqc2(auVar27);
          FVector::FVector(&fStack_b50,auStack_bc0);
          fStack_9b0 = fStack_b50;
          fStack_9ac = fStack_b4c;
          fStack_9a8 = fStack_b48;
          fStack_9a4 = fStack_b44;
        }
        sceVu0RotTransPersN(aiStack_a20,*this + 0x590,&fStack_9e0,4,0);
        for (iVar15 = 0; iVar15 < 4; iVar15 = iVar15 + 1) {
          aiStack_a20[iVar15 * 4] =
               (int)((float)aiStack_a20[iVar15 * 4] +
                    ((*(float *)(*this + 0x68) + (float)this[0xc]) - 256.0) * 16.0);
          aiStack_a20[iVar15 * 4 + 1] =
               (int)((float)aiStack_a20[iVar15 * 4 + 1] +
                    ((*(float *)(*this + 0x6c) + (float)this[0xd]) - 224.0) * 16.0);
          aiStack_a20[iVar15 * 4 + 2] = (int)((float)aiStack_a20[iVar15 * 4 + 2] / 16.0);
        }
        *param_2 = (ulong)(uint)(16.0 / (float)aiStack_a20[0xb]) << 0x20 | 0xffffff;
        param_2[1] = (long)aiStack_a20[10] << 0x20 |
                     (long)aiStack_a20[8] | (long)aiStack_a20[9] << 0x10;
        param_2[2] = uVar16 << 0x18 | 0xffffff | (ulong)(uint)(16.0 / (float)aiStack_a20[3]) << 0x20
        ;
        param_2[3] = (long)aiStack_a20[2] << 0x20 |
                     (long)aiStack_a20[0] | (long)aiStack_a20[1] << 0x10;
        param_2[4] = (ulong)(uint)(16.0 / (float)iStack_9e4) << 0x20 | 0xffffff;
        param_2[5] = (long)iStack_9e8 << 0x20 |
                     (long)aiStack_a20[0xc] | (long)aiStack_a20[0xd] << 0x10;
        fStack_4 = 16.0 / (float)aiStack_a20[7];
        param_2[6] = uVar16 << 0x18 | 0xffffff | (ulong)(uint)fStack_4 << 0x20;
        param_2[7] = (long)aiStack_a20[6] << 0x20 |
                     (long)aiStack_a20[4] | (long)aiStack_a20[5] << 0x10;
        param_2 = param_2 + 8;
        lVar24 = (long)(iVar14 + 1);
      }
    }
  }
  return param_2;
}

// JP: 0x002eab50  GetPacketCnt__10CrackJRingFv  =  CrackJRing::GetPacketCnt
int CrackJRing::GetPacketCnt(int this)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = 5;
  for (uVar2 = 0; uVar2 < this->u32_8; uVar2 = uVar2 + 1) {
    iVar1 = iVar1 + (uint)*(ushort *)(this->i32_4 + uVar2 * 0x80 + 2);
  }
  if ((this->i32_14 == 2) && (this->f32_18 < 0.33333334)) {
    iVar1 = iVar1 + this->i16_44 * 4 + 5;
  }
  return iVar1;
}

// JP: 0x002eac10  Initialize1__10CrackJRingFv  =  CrackJRing::Initialize1
void CrackJRing::Initialize1(int *this)

{
  char cVar1;
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined8 uVar5;
  uint uVar6;
  float *pfVar7;
  uint uVar8;
  int iVar9;
  undefined2 *puVar10;
  float fVar11;
  undefined1 auVar12 [16];
  undefined1 auVar13 [16];
  undefined1 auStack_150 [12];
  undefined4 uStack_144;
  undefined1 auStack_140 [8];
  undefined4 uStack_138;
  undefined4 uStack_134;
  float afStack_130 [16];
  uint auStack_f0 [16];
  int iStack_b0;
  int iStack_ac;
  int iStack_a8;
  int iStack_a4;
  int iStack_a0;
  int iStack_9c;
  int iStack_98;
  int iStack_94;
  float afStack_90 [32];
  char acStack_10 [16];
  
  this[3] = *(int *)(*this + 0xb8);
  this[4] = 0x40400000;
  for (iVar3 = 0; iVar3 < 4; iVar3 = iVar3 + 1) {
    for (iVar9 = 0; iVar9 < 4; iVar9 = iVar9 + 1) {
      afStack_90[(iVar9 + iVar3 * 4) * 2] = (float)iVar9 / 3.0;
      afStack_90[(iVar9 + iVar3 * 4) * 2 + 1] = (float)iVar3 / 3.0;
    }
  }
  for (iVar3 = 1; iVar3 < 3; iVar3 = iVar3 + 1) {
    iVar9 = rand();
    afStack_90[iVar3 * 2] =
         afStack_90[iVar3 * 2] + (((float)iVar9 / 2.1474836e+09) * 0.125 - 0.0625);
    iVar9 = rand();
    afStack_90[(iVar3 + 0xc) * 2] =
         afStack_90[(iVar3 + 0xc) * 2] + (((float)iVar9 / 2.1474836e+09) * 0.125 - 0.0625);
  }
  for (iVar3 = 1; iVar3 < 3; iVar3 = iVar3 + 1) {
    iVar9 = rand();
    iVar4 = iVar3 * 8 + 1;
    afStack_90[iVar4] = afStack_90[iVar4] + (((float)iVar9 / 2.1474836e+09) * 0.125 - 0.0625);
    iVar9 = rand();
    iVar4 = (iVar3 * 4 + 3) * 2 + 1;
    afStack_90[iVar4] = afStack_90[iVar4] + (((float)iVar9 / 2.1474836e+09) * 0.125 - 0.0625);
  }
  for (iVar3 = 1; iVar3 < 3; iVar3 = iVar3 + 1) {
    for (iVar9 = 1; iVar9 < 3; iVar9 = iVar9 + 1) {
      iVar4 = rand();
      iVar2 = iVar9 + iVar3 * 4;
      afStack_90[iVar2 * 2] =
           afStack_90[iVar2 * 2] + (((float)iVar4 / 2.1474836e+09) * 0.1875 - 0.09375);
      iVar4 = rand();
      iVar2 = (iVar9 + iVar3 * 4) * 2 + 1;
      afStack_90[iVar2] = afStack_90[iVar2] + (((float)iVar4 / 2.1474836e+09) * 0.1875 - 0.09375);
    }
  }
  do {
    for (iVar3 = 0; iVar3 < 9; iVar3 = iVar3 + 1) {
      iVar9 = rand();
      acStack_10[iVar3] = (char)(int)(((float)iVar9 / 2.1474836e+09) * 3.0);
    }
    iVar9 = 0;
    for (iVar3 = 0; iVar3 < 9; iVar3 = iVar3 + 1) {
      if (acStack_10[iVar3] != '\0') {
        iVar9 = iVar9 + 1;
      }
    }
  } while ((iVar9 < 2) || (8 < iVar9));
  iVar9 = iVar9 + 9;
  uVar5 = __nwa(iVar9 * 0x80 + 0x10);
  iVar3 = __construct_new_array(uVar5,0x2f0d10,0,0x80,iVar9);
  this[1] = iVar3;
  this[2] = iVar9;
  puVar10 = (undefined2 *)this[1];
  pfVar7 = afStack_90;
  for (iVar3 = 0; iVar3 < 3; iVar3 = iVar3 + 1) {
    for (iVar9 = 0; iVar9 < 3; iVar9 = iVar9 + 1) {
      cVar1 = acStack_10[iVar9 + iVar3 * 3];
      if (cVar1 == '\x02') {
        puVar10[0x40] = 1;
        *puVar10 = 1;
        puVar10[1] = 6;
        puVar10[0x41] = 6;
        puVar10->u32_4c = 0;
        puVar10->u32_c = 0;
        puVar10->u32_50 = 0;
        puVar10->u32_52 = 0;
        puVar10->u32_54 = 0;
        puVar10->u32_56 = 0;
        puVar10->i32_10 = (int)puVar10->u64_50;
        puVar10->i32_12 = (int)((ulong)puVar10->u64_50 >> 0x20);
        puVar10->u32_14 = puVar10->u32_54;
        puVar10->u32_16 = puVar10->u32_56;
        puVar10->u32_5c = 0;
        puVar10->u32_1c = 0;
        fVar11 = ((*pfVar7 - 0.5) * 2.0 * 114.0 + 128.0) * 16.0;
        puVar10->f32_64 = fVar11;
        puVar10->f32_24 = fVar11;
        fVar11 = ((pfVar7[1] - 0.5) * 2.0 * 114.0 + 128.0) * 16.0;
        puVar10->f32_66 = fVar11;
        puVar10->f32_26 = fVar11;
        fVar11 = ((pfVar7[10] - 0.5) * 2.0 * 114.0 + 128.0) * 16.0;
        puVar10->f32_6c = fVar11;
        puVar10->f32_34 = fVar11;
        fVar11 = ((pfVar7[0xb] - 0.5) * 2.0 * 114.0 + 128.0) * 16.0;
        puVar10->f32_6e = fVar11;
        puVar10->f32_36 = fVar11;
        puVar10->f32_8 = ((pfVar7[10] + *pfVar7 + pfVar7[8]) * 114.0 * 2.0) / 3.0;
        puVar10->f32_a = ((pfVar7[0xb] + pfVar7[1] + pfVar7[9]) * 114.0 * 2.0) / 3.0;
        iVar4 = rand();
        puVar10->f32_18 = ((float)iVar4 / 2.1474836e+09) * 4.1887903 - 2.0943952;
        iVar4 = rand();
        puVar10->f32_1a = ((float)iVar4 / 2.1474836e+09) * 4.1887903 - 2.0943952;
        puVar10->f32_20 = *pfVar7 * 114.0 * 2.0 - puVar10->f32_8;
        puVar10->f32_22 = pfVar7[1] * 114.0 * 2.0 - puVar10->f32_a;
        puVar10->f32_28 = pfVar7[8] * 114.0 * 2.0 - puVar10->f32_8;
        puVar10->f32_2a = pfVar7[9] * 114.0 * 2.0 - puVar10->f32_a;
        puVar10->f32_2c = ((pfVar7[8] - 0.5) * 2.0 * 114.0 + 128.0) * 16.0;
        puVar10->f32_2e = ((pfVar7[9] - 0.5) * 2.0 * 114.0 + 128.0) * 16.0;
        puVar10->f32_30 = pfVar7[10] * 114.0 * 2.0 - puVar10->f32_8;
        puVar10->f32_32 = pfVar7[0xb] * 114.0 * 2.0 - puVar10->f32_a;
        puVar10->f32_48 = ((pfVar7[2] + *pfVar7 + pfVar7[10]) * 114.0 * 2.0) / 3.0;
        puVar10->f32_4a = ((pfVar7[3] + pfVar7[1] + pfVar7[0xb]) * 114.0 * 2.0) / 3.0;
        iVar4 = rand();
        puVar10->f32_58 = ((float)iVar4 / 2.1474836e+09) * 4.1887903 - 2.0943952;
        iVar4 = rand();
        puVar10->f32_5a = ((float)iVar4 / 2.1474836e+09) * 4.1887903 - 2.0943952;
        puVar10->f32_60 = *pfVar7 * 114.0 * 2.0 - puVar10->f32_48;
        puVar10->f32_62 = pfVar7[1] * 114.0 * 2.0 - puVar10->f32_4a;
        puVar10->f32_68 = pfVar7[10] * 114.0 * 2.0 - puVar10->f32_48;
        puVar10->f32_6a = pfVar7[0xb] * 114.0 * 2.0 - puVar10->f32_4a;
        puVar10->f32_70 = pfVar7[2] * 114.0 * 2.0 - puVar10->f32_48;
        puVar10->f32_72 = pfVar7[3] * 114.0 * 2.0 - puVar10->f32_4a;
        puVar10->f32_74 = ((pfVar7[2] - 0.5) * 2.0 * 114.0 + 128.0) * 16.0;
        puVar10->f32_76 = ((pfVar7[3] - 0.5) * 2.0 * 114.0 + 128.0) * 16.0;
        puVar10 = puVar10 + 0x80;
      }
      else if (cVar1 == '\x01') {
        puVar10[0x40] = 1;
        *puVar10 = 1;
        puVar10[1] = 6;
        puVar10[0x41] = 6;
        puVar10->u32_4c = 0;
        puVar10->u32_c = 0;
        puVar10->u32_50 = 0;
        puVar10->u32_52 = 0;
        puVar10->u32_54 = 0;
        puVar10->u32_56 = 0;
        puVar10->i32_10 = (int)puVar10->u64_50;
        puVar10->i32_12 = (int)((ulong)puVar10->u64_50 >> 0x20);
        puVar10->u32_14 = puVar10->u32_54;
        puVar10->u32_16 = puVar10->u32_56;
        puVar10->u32_5c = 0;
        puVar10->u32_1c = 0;
        fVar11 = ((pfVar7[8] - 0.5) * 2.0 * 114.0 + 128.0) * 16.0;
        puVar10->f32_6c = fVar11;
        puVar10->f32_2c = fVar11;
        fVar11 = ((pfVar7[9] - 0.5) * 2.0 * 114.0 + 128.0) * 16.0;
        puVar10->f32_6e = fVar11;
        puVar10->f32_2e = fVar11;
        fVar11 = ((pfVar7[2] - 0.5) * 2.0 * 114.0 + 128.0) * 16.0;
        puVar10->f32_64 = fVar11;
        puVar10->f32_34 = fVar11;
        fVar11 = ((pfVar7[3] - 0.5) * 2.0 * 114.0 + 128.0) * 16.0;
        puVar10->f32_66 = fVar11;
        puVar10->f32_36 = fVar11;
        puVar10->f32_8 = ((pfVar7[8] + *pfVar7 + pfVar7[2]) * 114.0 * 2.0) / 3.0;
        puVar10->f32_a = ((pfVar7[9] + pfVar7[1] + pfVar7[3]) * 114.0 * 2.0) / 3.0;
        iVar4 = rand();
        puVar10->f32_18 = ((float)iVar4 / 2.1474836e+09) * 4.1887903 - 2.0943952;
        iVar4 = rand();
        puVar10->f32_1a = ((float)iVar4 / 2.1474836e+09) * 4.1887903 - 2.0943952;
        puVar10->f32_20 = *pfVar7 * 114.0 * 2.0 - puVar10->f32_8;
        puVar10->f32_22 = pfVar7[1] * 114.0 * 2.0 - puVar10->f32_a;
        puVar10->f32_24 = ((*pfVar7 - 0.5) * 2.0 * 114.0 + 128.0) * 16.0;
        puVar10->f32_26 = ((pfVar7[1] - 0.5) * 2.0 * 114.0 + 128.0) * 16.0;
        puVar10->f32_28 = pfVar7[8] * 114.0 * 2.0 - puVar10->f32_8;
        puVar10->f32_2a = pfVar7[9] * 114.0 * 2.0 - puVar10->f32_a;
        puVar10->f32_30 = pfVar7[2] * 114.0 * 2.0 - puVar10->f32_8;
        puVar10->f32_32 = pfVar7[3] * 114.0 * 2.0 - puVar10->f32_a;
        puVar10->f32_48 = ((pfVar7[10] + pfVar7[2] + pfVar7[8]) * 114.0 * 2.0) / 3.0;
        puVar10->f32_4a = ((pfVar7[0xb] + pfVar7[3] + pfVar7[9]) * 114.0 * 2.0) / 3.0;
        iVar4 = rand();
        puVar10->f32_58 = ((float)iVar4 / 2.1474836e+09) * 4.1887903 - 2.0943952;
        iVar4 = rand();
        puVar10->f32_5a = ((float)iVar4 / 2.1474836e+09) * 4.1887903 - 2.0943952;
        puVar10->f32_60 = pfVar7[2] * 114.0 * 2.0 - puVar10->f32_48;
        puVar10->f32_62 = pfVar7[3] * 114.0 * 2.0 - puVar10->f32_4a;
        puVar10->f32_68 = pfVar7[8] * 114.0 * 2.0 - puVar10->f32_48;
        puVar10->f32_6a = pfVar7[9] * 114.0 * 2.0 - puVar10->f32_4a;
        puVar10->f32_70 = pfVar7[10] * 114.0 * 2.0 - puVar10->f32_48;
        puVar10->f32_72 = pfVar7[0xb] * 114.0 * 2.0 - puVar10->f32_4a;
        puVar10->f32_74 = ((pfVar7[10] - 0.5) * 2.0 * 114.0 + 128.0) * 16.0;
        puVar10->f32_76 = ((pfVar7[0xb] - 0.5) * 2.0 * 114.0 + 128.0) * 16.0;
        puVar10 = puVar10 + 0x80;
      }
      else if (cVar1 == '\0') {
        *puVar10 = 0;
        puVar10[1] = 7;
        puVar10->f32_8 =
             ((pfVar7[10] + pfVar7[8] + *pfVar7 + pfVar7[2]) * 114.0 * 2.0) / 4.0;
        puVar10->f32_a =
             ((pfVar7[0xb] + pfVar7[9] + pfVar7[1] + pfVar7[3]) * 114.0 * 2.0) / 4.0;
        puVar10->u32_c = 0;
        puVar10->u32_10 = 0;
        puVar10->u32_12 = 0;
        puVar10->u32_14 = 0;
        puVar10->u32_16 = 0;
        iVar4 = rand();
        puVar10->f32_18 = ((float)iVar4 / 2.1474836e+09) * 4.1887903 - 2.0943952;
        iVar4 = rand();
        puVar10->f32_1a = ((float)iVar4 / 2.1474836e+09) * 4.1887903 - 2.0943952;
        puVar10->u32_1c = 0;
        puVar10->f32_20 = *pfVar7 * 114.0 * 2.0 - puVar10->f32_8;
        puVar10->f32_22 = pfVar7[1] * 114.0 * 2.0 - puVar10->f32_a;
        puVar10->f32_24 = ((*pfVar7 - 0.5) * 2.0 * 114.0 + 128.0) * 16.0;
        puVar10->f32_26 = ((pfVar7[1] - 0.5) * 2.0 * 114.0 + 128.0) * 16.0;
        puVar10->f32_28 = pfVar7[8] * 114.0 * 2.0 - puVar10->f32_8;
        puVar10->f32_2a = pfVar7[9] * 114.0 * 2.0 - puVar10->f32_a;
        puVar10->f32_2c = ((pfVar7[8] - 0.5) * 2.0 * 114.0 + 128.0) * 16.0;
        puVar10->f32_2e = ((pfVar7[9] - 0.5) * 2.0 * 114.0 + 128.0) * 16.0;
        puVar10->f32_30 = pfVar7[2] * 114.0 * 2.0 - puVar10->f32_8;
        puVar10->f32_32 = pfVar7[3] * 114.0 * 2.0 - puVar10->f32_a;
        puVar10->f32_34 = ((pfVar7[2] - 0.5) * 2.0 * 114.0 + 128.0) * 16.0;
        puVar10->f32_36 = ((pfVar7[3] - 0.5) * 2.0 * 114.0 + 128.0) * 16.0;
        puVar10->f32_38 = pfVar7[10] * 114.0 * 2.0 - puVar10->f32_8;
        puVar10->f32_3a = pfVar7[0xb] * 114.0 * 2.0 - puVar10->f32_a;
        puVar10->f32_3c = ((pfVar7[10] - 0.5) * 2.0 * 114.0 + 128.0) * 16.0;
        puVar10->f32_3e = ((pfVar7[0xb] - 0.5) * 2.0 * 114.0 + 128.0) * 16.0;
        puVar10 = puVar10 + 0x40;
      }
      pfVar7 = pfVar7 + 2;
    }
    pfVar7 = pfVar7 + 2;
  }
  auStack_140._4_4_ = in_zero_hi;
  auStack_140._0_4_ = in_zero_lo;
  uStack_138 = in_zero_udw;
  uStack_134 = in_register_0000000c;
  for (uVar6 = 0; (int)uVar6 < 0x10; uVar6 = uVar6 + 1) {
    auStack_f0[uVar6] = uVar6;
    auStack_140._4_4_ = (afStack_90[uVar6 * 2 + 1] - 0.5) * 114.0 * 2.0;
    auStack_140._0_4_ = (afStack_90[uVar6 * 2] - 0.5) * 114.0 * 2.0;
    uStack_138 = 0;
    uStack_134 = 0x3f800000;
    fVar11 = (float)FVector::Length(auStack_140);
    afStack_130[uVar6] = fVar11;
  }
  for (iVar3 = 0; iVar9 = iVar3, iVar3 < 0x10; iVar3 = iVar3 + 1) {
    while (iVar9 = iVar9 + 1, iVar9 < 0x10) {
      if (afStack_130[iVar9] < afStack_130[iVar3]) {
        uVar6 = auStack_f0[iVar3];
        auStack_f0[iVar3] = auStack_f0[iVar9];
        auStack_f0[iVar9] = uVar6;
        fVar11 = afStack_130[iVar3];
        afStack_130[iVar3] = afStack_130[iVar9];
        afStack_130[iVar9] = fVar11;
      }
      else if ((afStack_130[iVar3] == afStack_130[iVar9]) && (iVar4 = rand(), iVar4 % 100 < 0x33)) {
        uVar6 = auStack_f0[iVar3];
        auStack_f0[iVar3] = auStack_f0[iVar9];
        auStack_f0[iVar9] = uVar6;
        fVar11 = afStack_130[iVar3];
        afStack_130[iVar3] = afStack_130[iVar9];
        afStack_130[iVar9] = fVar11;
      }
    }
  }
  *(undefined2 *)((int)this + 0x46) = 0;
  this->u16_11 = 0;
  for (iVar3 = 1; iVar3 < 0x10; iVar3 = iVar3 + 1) {
    iStack_94 = -1;
    iStack_98 = -1;
    iStack_9c = -1;
    iStack_a0 = -1;
    iStack_a4 = -1;
    iStack_a8 = -1;
    iStack_ac = -1;
    iStack_b0 = -1;
    for (iVar9 = 0; iVar9 < iVar3; iVar9 = iVar9 + 1) {
      if (auStack_f0[iVar9] == auStack_f0[iVar3] - 5) {
        iStack_b0 = iVar9;
      }
      if (auStack_f0[iVar9] == auStack_f0[iVar3] - 1) {
        iStack_ac = iVar9;
      }
      if (auStack_f0[iVar9] == auStack_f0[iVar3] + 3) {
        iStack_a8 = iVar9;
      }
      if (auStack_f0[iVar9] == auStack_f0[iVar3] - 4) {
        iStack_a4 = iVar9;
      }
      if (auStack_f0[iVar9] == auStack_f0[iVar3] + 4) {
        iStack_a0 = iVar9;
      }
      if (auStack_f0[iVar9] == auStack_f0[iVar3] - 3) {
        iStack_9c = iVar9;
      }
      if (auStack_f0[iVar9] == auStack_f0[iVar3] + 1) {
        iStack_98 = iVar9;
      }
      if (auStack_f0[iVar9] == auStack_f0[iVar3] + 5) {
        iStack_94 = iVar9;
      }
    }
    if (-1 < iStack_ac) {
      if ((101.0 < afStack_130[iVar3]) || (101.0 < afStack_130[iStack_ac])) {
        if ((101.0 < afStack_130[iVar3]) || (afStack_130[iStack_ac] <= 101.0)) {
          if ((101.0 < afStack_130[iVar3]) && (afStack_130[iStack_ac] <= 101.0)) {
            auStack_140._4_4_ = (afStack_90[auStack_f0[iVar3] * 2 + 1] - 0.5) * 114.0 * 2.0;
            auStack_140._0_4_ = (afStack_90[auStack_f0[iVar3] * 2] - 0.5) * 114.0 * 2.0;
            uStack_138 = 0;
            uStack_134 = 0x3f800000;
            auStack_150._4_4_ = (afStack_90[auStack_f0[iStack_ac] * 2 + 1] - 0.5) * 114.0 * 2.0;
            auStack_150._0_4_ = (afStack_90[auStack_f0[iStack_ac] * 2] - 0.5) * 114.0 * 2.0;
            auStack_150._8_4_ = 0;
            uStack_144 = 0x3f800000;
            auVar13 = _lqc2(_auStack_150);
            auVar12 = _lqc2(_auStack_140);
            auVar12 = _vsub(auVar12,auVar13);
            _auStack_140 = _sqc2(auVar12);
            FVector::__amu((101.0 - afStack_130[iStack_ac]) /
                              ((101.0 - afStack_130[iStack_ac]) + (afStack_130[iVar3] - 101.0)),
                              auStack_140);
            auVar13 = _lqc2(_auStack_150);
            auVar12 = _lqc2(_auStack_140);
            auVar12 = _vadd(auVar12,auVar13);
            auVar12 = _sqc2(auVar12);
            auStack_140._0_4_ = auVar12._0_4_;
            this[(short)this[0x11] * 4 + 0x12] = auStack_140._0_4_;
            auStack_140._4_4_ = auVar12._4_4_;
            this[(short)this[0x11] * 4 + 0x13] = auStack_140._4_4_;
            this[(short)this[0x11] * 4 + 0x14] = auStack_150._0_4_;
            this[(short)this[0x11] * 4 + 0x15] = auStack_150._4_4_;
            this->i16_11 = (short)this[0x11] + 1;
          }
        }
        else {
          auStack_140._4_4_ = (afStack_90[auStack_f0[iVar3] * 2 + 1] - 0.5) * 114.0 * 2.0;
          auStack_140._0_4_ = (afStack_90[auStack_f0[iVar3] * 2] - 0.5) * 114.0 * 2.0;
          uStack_138 = 0;
          uStack_134 = 0x3f800000;
          auStack_150._4_4_ = (afStack_90[auStack_f0[iStack_ac] * 2 + 1] - 0.5) * 114.0 * 2.0;
          auStack_150._0_4_ = (afStack_90[auStack_f0[iStack_ac] * 2] - 0.5) * 114.0 * 2.0;
          auStack_150._8_4_ = 0;
          uStack_144 = 0x3f800000;
          auVar13 = _lqc2(_auStack_140);
          auVar12 = _lqc2(_auStack_150);
          auVar12 = _vsub(auVar12,auVar13);
          _auStack_150 = _sqc2(auVar12);
          FVector::__amu((101.0 - afStack_130[iVar3]) /
                            ((101.0 - afStack_130[iVar3]) + (afStack_130[iStack_ac] - 101.0)),
                            auStack_150);
          auVar13 = _lqc2(_auStack_140);
          auVar12 = _lqc2(_auStack_150);
          auVar12 = _vadd(auVar12,auVar13);
          auVar12 = _sqc2(auVar12);
          this[(short)this[0x11] * 4 + 0x12] = auStack_140._0_4_;
          this[(short)this[0x11] * 4 + 0x13] = auStack_140._4_4_;
          auStack_150._0_4_ = auVar12._0_4_;
          this[(short)this[0x11] * 4 + 0x14] = auStack_150._0_4_;
          auStack_150._4_4_ = auVar12._4_4_;
          this[(short)this[0x11] * 4 + 0x15] = auStack_150._4_4_;
          this->i16_11 = (short)this[0x11] + 1;
        }
      }
      else {
        this[(short)this[0x11] * 4 + 0x12] =
             (int)((afStack_90[auStack_f0[iVar3] * 2] - 0.5) * 114.0 * 2.0);
        this[(short)this[0x11] * 4 + 0x13] =
             (int)((afStack_90[auStack_f0[iVar3] * 2 + 1] - 0.5) * 114.0 * 2.0);
        this[(short)this[0x11] * 4 + 0x14] =
             (int)((afStack_90[auStack_f0[iStack_ac] * 2] - 0.5) * 114.0 * 2.0);
        this[(short)this[0x11] * 4 + 0x15] =
             (int)((afStack_90[auStack_f0[iStack_ac] * 2 + 1] - 0.5) * 114.0 * 2.0);
        this->i16_11 = (short)this[0x11] + 1;
      }
    }
    if (-1 < iStack_a4) {
      if ((101.0 < afStack_130[iVar3]) || (101.0 < afStack_130[iStack_a4])) {
        if ((101.0 < afStack_130[iVar3]) || (afStack_130[iStack_a4] <= 101.0)) {
          if ((101.0 < afStack_130[iVar3]) && (afStack_130[iStack_a4] <= 101.0)) {
            auStack_140._4_4_ = (afStack_90[auStack_f0[iVar3] * 2 + 1] - 0.5) * 114.0 * 2.0;
            auStack_140._0_4_ = (afStack_90[auStack_f0[iVar3] * 2] - 0.5) * 114.0 * 2.0;
            uStack_138 = 0;
            uStack_134 = 0x3f800000;
            auStack_150._4_4_ = (afStack_90[auStack_f0[iStack_a4] * 2 + 1] - 0.5) * 114.0 * 2.0;
            auStack_150._0_4_ = (afStack_90[auStack_f0[iStack_a4] * 2] - 0.5) * 114.0 * 2.0;
            auStack_150._8_4_ = 0;
            uStack_144 = 0x3f800000;
            auVar13 = _lqc2(_auStack_150);
            auVar12 = _lqc2(_auStack_140);
            auVar12 = _vsub(auVar12,auVar13);
            _auStack_140 = _sqc2(auVar12);
            FVector::__amu((101.0 - afStack_130[iStack_a4]) /
                              ((101.0 - afStack_130[iStack_a4]) + (afStack_130[iVar3] - 101.0)),
                              auStack_140);
            auVar13 = _lqc2(_auStack_150);
            auVar12 = _lqc2(_auStack_140);
            auVar12 = _vadd(auVar12,auVar13);
            auVar12 = _sqc2(auVar12);
            auStack_140._0_4_ = auVar12._0_4_;
            this[(short)this[0x11] * 4 + 0x12] = auStack_140._0_4_;
            auStack_140._4_4_ = auVar12._4_4_;
            this[(short)this[0x11] * 4 + 0x13] = auStack_140._4_4_;
            this[(short)this[0x11] * 4 + 0x14] = auStack_150._0_4_;
            this[(short)this[0x11] * 4 + 0x15] = auStack_150._4_4_;
            this->i16_11 = (short)this[0x11] + 1;
          }
        }
        else {
          auStack_140._4_4_ = (afStack_90[auStack_f0[iVar3] * 2 + 1] - 0.5) * 114.0 * 2.0;
          auStack_140._0_4_ = (afStack_90[auStack_f0[iVar3] * 2] - 0.5) * 114.0 * 2.0;
          uStack_138 = 0;
          uStack_134 = 0x3f800000;
          auStack_150._4_4_ = (afStack_90[auStack_f0[iStack_a4] * 2 + 1] - 0.5) * 114.0 * 2.0;
          auStack_150._0_4_ = (afStack_90[auStack_f0[iStack_a4] * 2] - 0.5) * 114.0 * 2.0;
          auStack_150._8_4_ = 0;
          uStack_144 = 0x3f800000;
          auVar13 = _lqc2(_auStack_140);
          auVar12 = _lqc2(_auStack_150);
          auVar12 = _vsub(auVar12,auVar13);
          _auStack_150 = _sqc2(auVar12);
          FVector::__amu((101.0 - afStack_130[iVar3]) /
                            ((101.0 - afStack_130[iVar3]) + (afStack_130[iStack_a4] - 101.0)),
                            auStack_150);
          auVar13 = _lqc2(_auStack_140);
          auVar12 = _lqc2(_auStack_150);
          auVar12 = _vadd(auVar12,auVar13);
          auVar12 = _sqc2(auVar12);
          this[(short)this[0x11] * 4 + 0x12] = auStack_140._0_4_;
          this[(short)this[0x11] * 4 + 0x13] = auStack_140._4_4_;
          auStack_150._0_4_ = auVar12._0_4_;
          this[(short)this[0x11] * 4 + 0x14] = auStack_150._0_4_;
          auStack_150._4_4_ = auVar12._4_4_;
          this[(short)this[0x11] * 4 + 0x15] = auStack_150._4_4_;
          this->i16_11 = (short)this[0x11] + 1;
        }
      }
      else {
        this[(short)this[0x11] * 4 + 0x12] =
             (int)((afStack_90[auStack_f0[iVar3] * 2] - 0.5) * 114.0 * 2.0);
        this[(short)this[0x11] * 4 + 0x13] =
             (int)((afStack_90[auStack_f0[iVar3] * 2 + 1] - 0.5) * 114.0 * 2.0);
        this[(short)this[0x11] * 4 + 0x14] =
             (int)((afStack_90[auStack_f0[iStack_a4] * 2] - 0.5) * 114.0 * 2.0);
        this[(short)this[0x11] * 4 + 0x15] =
             (int)((afStack_90[auStack_f0[iStack_a4] * 2 + 1] - 0.5) * 114.0 * 2.0);
        this->i16_11 = (short)this[0x11] + 1;
      }
    }
    if (-1 < iStack_a0) {
      if ((101.0 < afStack_130[iVar3]) || (101.0 < afStack_130[iStack_a0])) {
        if ((101.0 < afStack_130[iVar3]) || (afStack_130[iStack_a0] <= 101.0)) {
          if ((101.0 < afStack_130[iVar3]) && (afStack_130[iStack_a0] <= 101.0)) {
            auStack_140._4_4_ = (afStack_90[auStack_f0[iVar3] * 2 + 1] - 0.5) * 114.0 * 2.0;
            auStack_140._0_4_ = (afStack_90[auStack_f0[iVar3] * 2] - 0.5) * 114.0 * 2.0;
            uStack_138 = 0;
            uStack_134 = 0x3f800000;
            auStack_150._4_4_ = (afStack_90[auStack_f0[iStack_a0] * 2 + 1] - 0.5) * 114.0 * 2.0;
            auStack_150._0_4_ = (afStack_90[auStack_f0[iStack_a0] * 2] - 0.5) * 114.0 * 2.0;
            auStack_150._8_4_ = 0;
            uStack_144 = 0x3f800000;
            auVar13 = _lqc2(_auStack_150);
            auVar12 = _lqc2(_auStack_140);
            auVar12 = _vsub(auVar12,auVar13);
            _auStack_140 = _sqc2(auVar12);
            FVector::__amu((101.0 - afStack_130[iStack_a0]) /
                              ((101.0 - afStack_130[iStack_a0]) + (afStack_130[iVar3] - 101.0)),
                              auStack_140);
            auVar13 = _lqc2(_auStack_150);
            auVar12 = _lqc2(_auStack_140);
            auVar12 = _vadd(auVar12,auVar13);
            auVar12 = _sqc2(auVar12);
            auStack_140._0_4_ = auVar12._0_4_;
            this[(short)this[0x11] * 4 + 0x12] = auStack_140._0_4_;
            auStack_140._4_4_ = auVar12._4_4_;
            this[(short)this[0x11] * 4 + 0x13] = auStack_140._4_4_;
            this[(short)this[0x11] * 4 + 0x14] = auStack_150._0_4_;
            this[(short)this[0x11] * 4 + 0x15] = auStack_150._4_4_;
            this->i16_11 = (short)this[0x11] + 1;
          }
        }
        else {
          auStack_140._4_4_ = (afStack_90[auStack_f0[iVar3] * 2 + 1] - 0.5) * 114.0 * 2.0;
          auStack_140._0_4_ = (afStack_90[auStack_f0[iVar3] * 2] - 0.5) * 114.0 * 2.0;
          uStack_138 = 0;
          uStack_134 = 0x3f800000;
          auStack_150._4_4_ = (afStack_90[auStack_f0[iStack_a0] * 2 + 1] - 0.5) * 114.0 * 2.0;
          auStack_150._0_4_ = (afStack_90[auStack_f0[iStack_a0] * 2] - 0.5) * 114.0 * 2.0;
          auStack_150._8_4_ = 0;
          uStack_144 = 0x3f800000;
          auVar13 = _lqc2(_auStack_140);
          auVar12 = _lqc2(_auStack_150);
          auVar12 = _vsub(auVar12,auVar13);
          _auStack_150 = _sqc2(auVar12);
          FVector::__amu((101.0 - afStack_130[iVar3]) /
                            ((101.0 - afStack_130[iVar3]) + (afStack_130[iStack_a0] - 101.0)),
                            auStack_150);
          auVar13 = _lqc2(_auStack_140);
          auVar12 = _lqc2(_auStack_150);
          auVar12 = _vadd(auVar12,auVar13);
          auVar12 = _sqc2(auVar12);
          this[(short)this[0x11] * 4 + 0x12] = auStack_140._0_4_;
          this[(short)this[0x11] * 4 + 0x13] = auStack_140._4_4_;
          auStack_150._0_4_ = auVar12._0_4_;
          this[(short)this[0x11] * 4 + 0x14] = auStack_150._0_4_;
          auStack_150._4_4_ = auVar12._4_4_;
          this[(short)this[0x11] * 4 + 0x15] = auStack_150._4_4_;
          this->i16_11 = (short)this[0x11] + 1;
        }
      }
      else {
        this[(short)this[0x11] * 4 + 0x12] =
             (int)((afStack_90[auStack_f0[iVar3] * 2] - 0.5) * 114.0 * 2.0);
        this[(short)this[0x11] * 4 + 0x13] =
             (int)((afStack_90[auStack_f0[iVar3] * 2 + 1] - 0.5) * 114.0 * 2.0);
        this[(short)this[0x11] * 4 + 0x14] =
             (int)((afStack_90[auStack_f0[iStack_a0] * 2] - 0.5) * 114.0 * 2.0);
        this[(short)this[0x11] * 4 + 0x15] =
             (int)((afStack_90[auStack_f0[iStack_a0] * 2 + 1] - 0.5) * 114.0 * 2.0);
        this->i16_11 = (short)this[0x11] + 1;
      }
    }
    if (-1 < iStack_98) {
      if ((101.0 < afStack_130[iVar3]) || (101.0 < afStack_130[iStack_98])) {
        if ((101.0 < afStack_130[iVar3]) || (afStack_130[iStack_98] <= 101.0)) {
          if ((101.0 < afStack_130[iVar3]) && (afStack_130[iStack_98] <= 101.0)) {
            auStack_140._4_4_ = (afStack_90[auStack_f0[iVar3] * 2 + 1] - 0.5) * 114.0 * 2.0;
            auStack_140._0_4_ = (afStack_90[auStack_f0[iVar3] * 2] - 0.5) * 114.0 * 2.0;
            uStack_138 = 0;
            uStack_134 = 0x3f800000;
            auStack_150._4_4_ = (afStack_90[auStack_f0[iStack_98] * 2 + 1] - 0.5) * 114.0 * 2.0;
            auStack_150._0_4_ = (afStack_90[auStack_f0[iStack_98] * 2] - 0.5) * 114.0 * 2.0;
            auStack_150._8_4_ = 0;
            uStack_144 = 0x3f800000;
            auVar13 = _lqc2(_auStack_150);
            auVar12 = _lqc2(_auStack_140);
            auVar12 = _vsub(auVar12,auVar13);
            _auStack_140 = _sqc2(auVar12);
            FVector::__amu((101.0 - afStack_130[iStack_98]) /
                              ((101.0 - afStack_130[iStack_98]) + (afStack_130[iVar3] - 101.0)),
                              auStack_140);
            auVar13 = _lqc2(_auStack_150);
            auVar12 = _lqc2(_auStack_140);
            auVar12 = _vadd(auVar12,auVar13);
            auVar12 = _sqc2(auVar12);
            auStack_140._0_4_ = auVar12._0_4_;
            this[(short)this[0x11] * 4 + 0x12] = auStack_140._0_4_;
            auStack_140._4_4_ = auVar12._4_4_;
            this[(short)this[0x11] * 4 + 0x13] = auStack_140._4_4_;
            this[(short)this[0x11] * 4 + 0x14] = auStack_150._0_4_;
            this[(short)this[0x11] * 4 + 0x15] = auStack_150._4_4_;
            this->i16_11 = (short)this[0x11] + 1;
          }
        }
        else {
          auStack_140._4_4_ = (afStack_90[auStack_f0[iVar3] * 2 + 1] - 0.5) * 114.0 * 2.0;
          auStack_140._0_4_ = (afStack_90[auStack_f0[iVar3] * 2] - 0.5) * 114.0 * 2.0;
          uStack_138 = 0;
          uStack_134 = 0x3f800000;
          auStack_150._4_4_ = (afStack_90[auStack_f0[iStack_98] * 2 + 1] - 0.5) * 114.0 * 2.0;
          auStack_150._0_4_ = (afStack_90[auStack_f0[iStack_98] * 2] - 0.5) * 114.0 * 2.0;
          auStack_150._8_4_ = 0;
          uStack_144 = 0x3f800000;
          auVar13 = _lqc2(_auStack_140);
          auVar12 = _lqc2(_auStack_150);
          auVar12 = _vsub(auVar12,auVar13);
          _auStack_150 = _sqc2(auVar12);
          FVector::__amu((101.0 - afStack_130[iVar3]) /
                            ((101.0 - afStack_130[iVar3]) + (afStack_130[iStack_98] - 101.0)),
                            auStack_150);
          auVar13 = _lqc2(_auStack_140);
          auVar12 = _lqc2(_auStack_150);
          auVar12 = _vadd(auVar12,auVar13);
          auVar12 = _sqc2(auVar12);
          this[(short)this[0x11] * 4 + 0x12] = auStack_140._0_4_;
          this[(short)this[0x11] * 4 + 0x13] = auStack_140._4_4_;
          auStack_150._0_4_ = auVar12._0_4_;
          this[(short)this[0x11] * 4 + 0x14] = auStack_150._0_4_;
          auStack_150._4_4_ = auVar12._4_4_;
          this[(short)this[0x11] * 4 + 0x15] = auStack_150._4_4_;
          this->i16_11 = (short)this[0x11] + 1;
        }
      }
      else {
        this[(short)this[0x11] * 4 + 0x12] =
             (int)((afStack_90[auStack_f0[iVar3] * 2] - 0.5) * 114.0 * 2.0);
        this[(short)this[0x11] * 4 + 0x13] =
             (int)((afStack_90[auStack_f0[iVar3] * 2 + 1] - 0.5) * 114.0 * 2.0);
        this[(short)this[0x11] * 4 + 0x14] =
             (int)((afStack_90[auStack_f0[iStack_98] * 2] - 0.5) * 114.0 * 2.0);
        this[(short)this[0x11] * 4 + 0x15] =
             (int)((afStack_90[auStack_f0[iStack_98] * 2 + 1] - 0.5) * 114.0 * 2.0);
        this->i16_11 = (short)this[0x11] + 1;
      }
    }
    uVar6 = auStack_f0[iVar3];
    if ((int)uVar6 < 0) {
      uVar6 = uVar6 + 3;
    }
    iVar9 = (int)uVar6 >> 2;
    uVar6 = auStack_f0[iVar3] & 3;
    if (((int)auStack_f0[iVar3] < 0) && (uVar6 != 0)) {
      uVar6 = uVar6 - 4;
    }
    if (0 < iVar9) {
      iVar9 = iVar9 + -1;
    }
    if (0 < (int)uVar6) {
      uVar6 = uVar6 - 1;
    }
    if ((-1 < iStack_b0) && (acStack_10[iVar9 * 3 + uVar6] == '\x02')) {
      if ((101.0 < afStack_130[iVar3]) || (101.0 < afStack_130[iStack_b0])) {
        if ((101.0 < afStack_130[iVar3]) || (afStack_130[iStack_b0] <= 101.0)) {
          if ((101.0 < afStack_130[iVar3]) && (afStack_130[iStack_b0] <= 101.0)) {
            auStack_140._4_4_ = (afStack_90[auStack_f0[iVar3] * 2 + 1] - 0.5) * 114.0 * 2.0;
            auStack_140._0_4_ = (afStack_90[auStack_f0[iVar3] * 2] - 0.5) * 114.0 * 2.0;
            uStack_138 = 0;
            uStack_134 = 0x3f800000;
            auStack_150._4_4_ = (afStack_90[auStack_f0[iStack_b0] * 2 + 1] - 0.5) * 114.0 * 2.0;
            auStack_150._0_4_ = (afStack_90[auStack_f0[iStack_b0] * 2] - 0.5) * 114.0 * 2.0;
            auStack_150._8_4_ = 0;
            uStack_144 = 0x3f800000;
            auVar13 = _lqc2(_auStack_150);
            auVar12 = _lqc2(_auStack_140);
            auVar12 = _vsub(auVar12,auVar13);
            _auStack_140 = _sqc2(auVar12);
            FVector::__amu((101.0 - afStack_130[iStack_b0]) /
                              ((101.0 - afStack_130[iStack_b0]) + (afStack_130[iVar3] - 101.0)),
                              auStack_140);
            auVar13 = _lqc2(_auStack_150);
            auVar12 = _lqc2(_auStack_140);
            auVar12 = _vadd(auVar12,auVar13);
            auVar12 = _sqc2(auVar12);
            auStack_140._0_4_ = auVar12._0_4_;
            this[(short)this[0x11] * 4 + 0x12] = auStack_140._0_4_;
            auStack_140._4_4_ = auVar12._4_4_;
            this[(short)this[0x11] * 4 + 0x13] = auStack_140._4_4_;
            this[(short)this[0x11] * 4 + 0x14] = auStack_150._0_4_;
            this[(short)this[0x11] * 4 + 0x15] = auStack_150._4_4_;
            this->i16_11 = (short)this[0x11] + 1;
          }
        }
        else {
          auStack_140._4_4_ = (afStack_90[auStack_f0[iVar3] * 2 + 1] - 0.5) * 114.0 * 2.0;
          auStack_140._0_4_ = (afStack_90[auStack_f0[iVar3] * 2] - 0.5) * 114.0 * 2.0;
          uStack_138 = 0;
          uStack_134 = 0x3f800000;
          auStack_150._4_4_ = (afStack_90[auStack_f0[iStack_b0] * 2 + 1] - 0.5) * 114.0 * 2.0;
          auStack_150._0_4_ = (afStack_90[auStack_f0[iStack_b0] * 2] - 0.5) * 114.0 * 2.0;
          auStack_150._8_4_ = 0;
          uStack_144 = 0x3f800000;
          auVar13 = _lqc2(_auStack_140);
          auVar12 = _lqc2(_auStack_150);
          auVar12 = _vsub(auVar12,auVar13);
          _auStack_150 = _sqc2(auVar12);
          FVector::__amu((101.0 - afStack_130[iVar3]) /
                            ((101.0 - afStack_130[iVar3]) + (afStack_130[iStack_b0] - 101.0)),
                            auStack_150);
          auVar13 = _lqc2(_auStack_140);
          auVar12 = _lqc2(_auStack_150);
          auVar12 = _vadd(auVar12,auVar13);
          auVar12 = _sqc2(auVar12);
          this[(short)this[0x11] * 4 + 0x12] = auStack_140._0_4_;
          this[(short)this[0x11] * 4 + 0x13] = auStack_140._4_4_;
          auStack_150._0_4_ = auVar12._0_4_;
          this[(short)this[0x11] * 4 + 0x14] = auStack_150._0_4_;
          auStack_150._4_4_ = auVar12._4_4_;
          this[(short)this[0x11] * 4 + 0x15] = auStack_150._4_4_;
          this->i16_11 = (short)this[0x11] + 1;
        }
      }
      else {
        this[(short)this[0x11] * 4 + 0x12] =
             (int)((afStack_90[auStack_f0[iVar3] * 2] - 0.5) * 114.0 * 2.0);
        this[(short)this[0x11] * 4 + 0x13] =
             (int)((afStack_90[auStack_f0[iVar3] * 2 + 1] - 0.5) * 114.0 * 2.0);
        this[(short)this[0x11] * 4 + 0x14] =
             (int)((afStack_90[auStack_f0[iStack_b0] * 2] - 0.5) * 114.0 * 2.0);
        this[(short)this[0x11] * 4 + 0x15] =
             (int)((afStack_90[auStack_f0[iStack_b0] * 2 + 1] - 0.5) * 114.0 * 2.0);
        this->i16_11 = (short)this[0x11] + 1;
      }
    }
    uVar6 = auStack_f0[iVar3];
    if ((int)uVar6 < 0) {
      uVar6 = uVar6 + 3;
    }
    uVar8 = auStack_f0[iVar3] & 3;
    if (((int)auStack_f0[iVar3] < 0) && (uVar8 != 0)) {
      uVar8 = uVar8 - 4;
    }
    if (0 < (int)uVar8) {
      uVar8 = uVar8 - 1;
    }
    if ((-1 < iStack_a8) && (acStack_10[((int)uVar6 >> 2) * 3 + uVar8] == '\x01')) {
      if ((101.0 < afStack_130[iVar3]) || (101.0 < afStack_130[iStack_a8])) {
        if ((101.0 < afStack_130[iVar3]) || (afStack_130[iStack_a8] <= 101.0)) {
          if ((101.0 < afStack_130[iVar3]) && (afStack_130[iStack_a8] <= 101.0)) {
            auStack_140._4_4_ = (afStack_90[auStack_f0[iVar3] * 2 + 1] - 0.5) * 114.0 * 2.0;
            auStack_140._0_4_ = (afStack_90[auStack_f0[iVar3] * 2] - 0.5) * 114.0 * 2.0;
            uStack_138 = 0;
            uStack_134 = 0x3f800000;
            auStack_150._4_4_ = (afStack_90[auStack_f0[iStack_a8] * 2 + 1] - 0.5) * 114.0 * 2.0;
            auStack_150._0_4_ = (afStack_90[auStack_f0[iStack_a8] * 2] - 0.5) * 114.0 * 2.0;
            auStack_150._8_4_ = 0;
            uStack_144 = 0x3f800000;
            auVar13 = _lqc2(_auStack_150);
            auVar12 = _lqc2(_auStack_140);
            auVar12 = _vsub(auVar12,auVar13);
            _auStack_140 = _sqc2(auVar12);
            FVector::__amu((101.0 - afStack_130[iStack_a8]) /
                              ((101.0 - afStack_130[iStack_a8]) + (afStack_130[iVar3] - 101.0)),
                              auStack_140);
            auVar13 = _lqc2(_auStack_150);
            auVar12 = _lqc2(_auStack_140);
            auVar12 = _vadd(auVar12,auVar13);
            auVar12 = _sqc2(auVar12);
            auStack_140._0_4_ = auVar12._0_4_;
            this[(short)this[0x11] * 4 + 0x12] = auStack_140._0_4_;
            auStack_140._4_4_ = auVar12._4_4_;
            this[(short)this[0x11] * 4 + 0x13] = auStack_140._4_4_;
            this[(short)this[0x11] * 4 + 0x14] = auStack_150._0_4_;
            this[(short)this[0x11] * 4 + 0x15] = auStack_150._4_4_;
            this->i16_11 = (short)this[0x11] + 1;
          }
        }
        else {
          auStack_140._4_4_ = (afStack_90[auStack_f0[iVar3] * 2 + 1] - 0.5) * 114.0 * 2.0;
          auStack_140._0_4_ = (afStack_90[auStack_f0[iVar3] * 2] - 0.5) * 114.0 * 2.0;
          uStack_138 = 0;
          uStack_134 = 0x3f800000;
          auStack_150._4_4_ = (afStack_90[auStack_f0[iStack_a8] * 2 + 1] - 0.5) * 114.0 * 2.0;
          auStack_150._0_4_ = (afStack_90[auStack_f0[iStack_a8] * 2] - 0.5) * 114.0 * 2.0;
          auStack_150._8_4_ = 0;
          uStack_144 = 0x3f800000;
          auVar13 = _lqc2(_auStack_140);
          auVar12 = _lqc2(_auStack_150);
          auVar12 = _vsub(auVar12,auVar13);
          _auStack_150 = _sqc2(auVar12);
          FVector::__amu((101.0 - afStack_130[iVar3]) /
                            ((101.0 - afStack_130[iVar3]) + (afStack_130[iStack_a8] - 101.0)),
                            auStack_150);
          auVar13 = _lqc2(_auStack_140);
          auVar12 = _lqc2(_auStack_150);
          auVar12 = _vadd(auVar12,auVar13);
          auVar12 = _sqc2(auVar12);
          this[(short)this[0x11] * 4 + 0x12] = auStack_140._0_4_;
          this[(short)this[0x11] * 4 + 0x13] = auStack_140._4_4_;
          auStack_150._0_4_ = auVar12._0_4_;
          this[(short)this[0x11] * 4 + 0x14] = auStack_150._0_4_;
          auStack_150._4_4_ = auVar12._4_4_;
          this[(short)this[0x11] * 4 + 0x15] = auStack_150._4_4_;
          this->i16_11 = (short)this[0x11] + 1;
        }
      }
      else {
        this[(short)this[0x11] * 4 + 0x12] =
             (int)((afStack_90[auStack_f0[iVar3] * 2] - 0.5) * 114.0 * 2.0);
        this[(short)this[0x11] * 4 + 0x13] =
             (int)((afStack_90[auStack_f0[iVar3] * 2 + 1] - 0.5) * 114.0 * 2.0);
        this[(short)this[0x11] * 4 + 0x14] =
             (int)((afStack_90[auStack_f0[iStack_a8] * 2] - 0.5) * 114.0 * 2.0);
        this[(short)this[0x11] * 4 + 0x15] =
             (int)((afStack_90[auStack_f0[iStack_a8] * 2 + 1] - 0.5) * 114.0 * 2.0);
        this->i16_11 = (short)this[0x11] + 1;
      }
    }
    uVar6 = auStack_f0[iVar3];
    if ((int)uVar6 < 0) {
      uVar6 = uVar6 + 3;
    }
    iVar9 = (int)uVar6 >> 2;
    uVar6 = auStack_f0[iVar3] & 3;
    if (((int)auStack_f0[iVar3] < 0) && (uVar6 != 0)) {
      uVar6 = uVar6 - 4;
    }
    if (0 < iVar9) {
      iVar9 = iVar9 + -1;
    }
    if ((-1 < iStack_9c) && (acStack_10[iVar9 * 3 + uVar6] == '\x01')) {
      if ((101.0 < afStack_130[iVar3]) || (101.0 < afStack_130[iStack_9c])) {
        if ((101.0 < afStack_130[iVar3]) || (afStack_130[iStack_9c] <= 101.0)) {
          if ((101.0 < afStack_130[iVar3]) && (afStack_130[iStack_9c] <= 101.0)) {
            auStack_140._4_4_ = (afStack_90[auStack_f0[iVar3] * 2 + 1] - 0.5) * 114.0 * 2.0;
            auStack_140._0_4_ = (afStack_90[auStack_f0[iVar3] * 2] - 0.5) * 114.0 * 2.0;
            uStack_138 = 0;
            uStack_134 = 0x3f800000;
            auStack_150._4_4_ = (afStack_90[auStack_f0[iStack_9c] * 2 + 1] - 0.5) * 114.0 * 2.0;
            auStack_150._0_4_ = (afStack_90[auStack_f0[iStack_9c] * 2] - 0.5) * 114.0 * 2.0;
            auStack_150._8_4_ = 0;
            uStack_144 = 0x3f800000;
            auVar13 = _lqc2(_auStack_150);
            auVar12 = _lqc2(_auStack_140);
            auVar12 = _vsub(auVar12,auVar13);
            _auStack_140 = _sqc2(auVar12);
            FVector::__amu((101.0 - afStack_130[iStack_9c]) /
                              ((101.0 - afStack_130[iStack_9c]) + (afStack_130[iVar3] - 101.0)),
                              auStack_140);
            auVar13 = _lqc2(_auStack_150);
            auVar12 = _lqc2(_auStack_140);
            auVar12 = _vadd(auVar12,auVar13);
            auVar12 = _sqc2(auVar12);
            auStack_140._0_4_ = auVar12._0_4_;
            this[(short)this[0x11] * 4 + 0x12] = auStack_140._0_4_;
            auStack_140._4_4_ = auVar12._4_4_;
            this[(short)this[0x11] * 4 + 0x13] = auStack_140._4_4_;
            this[(short)this[0x11] * 4 + 0x14] = auStack_150._0_4_;
            this[(short)this[0x11] * 4 + 0x15] = auStack_150._4_4_;
            this->i16_11 = (short)this[0x11] + 1;
          }
        }
        else {
          auStack_140._4_4_ = (afStack_90[auStack_f0[iVar3] * 2 + 1] - 0.5) * 114.0 * 2.0;
          auStack_140._0_4_ = (afStack_90[auStack_f0[iVar3] * 2] - 0.5) * 114.0 * 2.0;
          uStack_138 = 0;
          uStack_134 = 0x3f800000;
          auStack_150._4_4_ = (afStack_90[auStack_f0[iStack_9c] * 2 + 1] - 0.5) * 114.0 * 2.0;
          auStack_150._0_4_ = (afStack_90[auStack_f0[iStack_9c] * 2] - 0.5) * 114.0 * 2.0;
          auStack_150._8_4_ = 0;
          uStack_144 = 0x3f800000;
          auVar13 = _lqc2(_auStack_140);
          auVar12 = _lqc2(_auStack_150);
          auVar12 = _vsub(auVar12,auVar13);
          _auStack_150 = _sqc2(auVar12);
          FVector::__amu((101.0 - afStack_130[iVar3]) /
                            ((101.0 - afStack_130[iVar3]) + (afStack_130[iStack_9c] - 101.0)),
                            auStack_150);
          auVar13 = _lqc2(_auStack_140);
          auVar12 = _lqc2(_auStack_150);
          auVar12 = _vadd(auVar12,auVar13);
          auVar12 = _sqc2(auVar12);
          this[(short)this[0x11] * 4 + 0x12] = auStack_140._0_4_;
          this[(short)this[0x11] * 4 + 0x13] = auStack_140._4_4_;
          auStack_150._0_4_ = auVar12._0_4_;
          this[(short)this[0x11] * 4 + 0x14] = auStack_150._0_4_;
          auStack_150._4_4_ = auVar12._4_4_;
          this[(short)this[0x11] * 4 + 0x15] = auStack_150._4_4_;
          this->i16_11 = (short)this[0x11] + 1;
        }
      }
      else {
        this[(short)this[0x11] * 4 + 0x12] =
             (int)((afStack_90[auStack_f0[iVar3] * 2] - 0.5) * 114.0 * 2.0);
        this[(short)this[0x11] * 4 + 0x13] =
             (int)((afStack_90[auStack_f0[iVar3] * 2 + 1] - 0.5) * 114.0 * 2.0);
        this[(short)this[0x11] * 4 + 0x14] =
             (int)((afStack_90[auStack_f0[iStack_9c] * 2] - 0.5) * 114.0 * 2.0);
        this[(short)this[0x11] * 4 + 0x15] =
             (int)((afStack_90[auStack_f0[iStack_9c] * 2 + 1] - 0.5) * 114.0 * 2.0);
        this->i16_11 = (short)this[0x11] + 1;
      }
    }
    uVar6 = auStack_f0[iVar3];
    if ((int)uVar6 < 0) {
      uVar6 = uVar6 + 3;
    }
    uVar8 = auStack_f0[iVar3] & 3;
    if (((int)auStack_f0[iVar3] < 0) && (uVar8 != 0)) {
      uVar8 = uVar8 - 4;
    }
    if ((-1 < iStack_94) && (acStack_10[((int)uVar6 >> 2) * 3 + uVar8] == '\x02')) {
      if ((101.0 < afStack_130[iVar3]) || (101.0 < afStack_130[iStack_94])) {
        if ((101.0 < afStack_130[iVar3]) || (afStack_130[iStack_94] <= 101.0)) {
          if ((101.0 < afStack_130[iVar3]) && (afStack_130[iStack_94] <= 101.0)) {
            auStack_140._4_4_ = (afStack_90[auStack_f0[iVar3] * 2 + 1] - 0.5) * 114.0 * 2.0;
            auStack_140._0_4_ = (afStack_90[auStack_f0[iVar3] * 2] - 0.5) * 114.0 * 2.0;
            uStack_138 = 0;
            uStack_134 = 0x3f800000;
            auStack_150._4_4_ = (afStack_90[auStack_f0[iStack_94] * 2 + 1] - 0.5) * 114.0 * 2.0;
            auStack_150._0_4_ = (afStack_90[auStack_f0[iStack_94] * 2] - 0.5) * 114.0 * 2.0;
            auStack_150._8_4_ = 0;
            uStack_144 = 0x3f800000;
            auVar13 = _lqc2(_auStack_150);
            auVar12 = _lqc2(_auStack_140);
            auVar12 = _vsub(auVar12,auVar13);
            _auStack_140 = _sqc2(auVar12);
            FVector::__amu((101.0 - afStack_130[iStack_94]) /
                              ((101.0 - afStack_130[iStack_94]) + (afStack_130[iVar3] - 101.0)),
                              auStack_140);
            auVar13 = _lqc2(_auStack_150);
            auVar12 = _lqc2(_auStack_140);
            auVar12 = _vadd(auVar12,auVar13);
            auVar12 = _sqc2(auVar12);
            auStack_140._0_4_ = auVar12._0_4_;
            this[(short)this[0x11] * 4 + 0x12] = auStack_140._0_4_;
            auStack_140._4_4_ = auVar12._4_4_;
            this[(short)this[0x11] * 4 + 0x13] = auStack_140._4_4_;
            this[(short)this[0x11] * 4 + 0x14] = auStack_150._0_4_;
            this[(short)this[0x11] * 4 + 0x15] = auStack_150._4_4_;
            this->i16_11 = (short)this[0x11] + 1;
          }
        }
        else {
          auStack_140._4_4_ = (afStack_90[auStack_f0[iVar3] * 2 + 1] - 0.5) * 114.0 * 2.0;
          auStack_140._0_4_ = (afStack_90[auStack_f0[iVar3] * 2] - 0.5) * 114.0 * 2.0;
          uStack_138 = 0;
          uStack_134 = 0x3f800000;
          auStack_150._4_4_ = (afStack_90[auStack_f0[iStack_94] * 2 + 1] - 0.5) * 114.0 * 2.0;
          auStack_150._0_4_ = (afStack_90[auStack_f0[iStack_94] * 2] - 0.5) * 114.0 * 2.0;
          auStack_150._8_4_ = 0;
          uStack_144 = 0x3f800000;
          auVar13 = _lqc2(_auStack_140);
          auVar12 = _lqc2(_auStack_150);
          auVar12 = _vsub(auVar12,auVar13);
          _auStack_150 = _sqc2(auVar12);
          FVector::__amu((101.0 - afStack_130[iVar3]) /
                            ((101.0 - afStack_130[iVar3]) + (afStack_130[iStack_94] - 101.0)),
                            auStack_150);
          auVar13 = _lqc2(_auStack_140);
          auVar12 = _lqc2(_auStack_150);
          auVar12 = _vadd(auVar12,auVar13);
          auVar12 = _sqc2(auVar12);
          this[(short)this[0x11] * 4 + 0x12] = auStack_140._0_4_;
          this[(short)this[0x11] * 4 + 0x13] = auStack_140._4_4_;
          auStack_150._0_4_ = auVar12._0_4_;
          this[(short)this[0x11] * 4 + 0x14] = auStack_150._0_4_;
          auStack_150._4_4_ = auVar12._4_4_;
          this[(short)this[0x11] * 4 + 0x15] = auStack_150._4_4_;
          this->i16_11 = (short)this[0x11] + 1;
        }
      }
      else {
        this[(short)this[0x11] * 4 + 0x12] =
             (int)((afStack_90[auStack_f0[iVar3] * 2] - 0.5) * 114.0 * 2.0);
        this[(short)this[0x11] * 4 + 0x13] =
             (int)((afStack_90[auStack_f0[iVar3] * 2 + 1] - 0.5) * 114.0 * 2.0);
        this[(short)this[0x11] * 4 + 0x14] =
             (int)((afStack_90[auStack_f0[iStack_94] * 2] - 0.5) * 114.0 * 2.0);
        this[(short)this[0x11] * 4 + 0x15] =
             (int)((afStack_90[auStack_f0[iStack_94] * 2 + 1] - 0.5) * 114.0 * 2.0);
        this->i16_11 = (short)this[0x11] + 1;
      }
    }
  }
  return;
}

// JP: 0x002f0d40  Initialize2__10CrackJRingFv  =  CrackJRing::Initialize2
void CrackJRing::Initialize2(int *this)

{
  char cVar1;
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  int iVar2;
  int iVar3;
  undefined8 uVar4;
  int iVar5;
  float *pfVar6;
  int iVar7;
  undefined2 *puVar8;
  float fVar9;
  undefined1 auVar10 [16];
  undefined1 auVar11 [16];
  undefined1 auStack_2a0 [12];
  undefined4 uStack_294;
  undefined1 auStack_290 [8];
  undefined4 uStack_288;
  undefined4 uStack_284;
  float afStack_280 [36];
  int aiStack_1f0 [36];
  int iStack_160;
  int iStack_15c;
  int iStack_158;
  int iStack_154;
  int iStack_150;
  int iStack_14c;
  int iStack_148;
  int iStack_144;
  char acStack_140 [32];
  float afStack_120 [72];
  
  this[3] = *(int *)(*this + 0xb8);
  this[4] = 0x40400000;
  for (iVar3 = 0; iVar3 < 6; iVar3 = iVar3 + 1) {
    for (iVar7 = 0; iVar7 < 6; iVar7 = iVar7 + 1) {
      afStack_120[(iVar7 + iVar3 * 6) * 2] = (float)iVar7 / 5.0;
      afStack_120[(iVar7 + iVar3 * 6) * 2 + 1] = (float)iVar3 / 5.0;
    }
  }
  for (iVar3 = 1; iVar3 < 5; iVar3 = iVar3 + 1) {
    iVar7 = rand();
    afStack_120[iVar3 * 2] =
         afStack_120[iVar3 * 2] + (((float)iVar7 / 2.1474836e+09) * 0.083333336 - 0.041666668);
    iVar7 = rand();
    afStack_120[(iVar3 + 0x1e) * 2] =
         afStack_120[(iVar3 + 0x1e) * 2] +
         (((float)iVar7 / 2.1474836e+09) * 0.083333336 - 0.041666668);
  }
  for (iVar3 = 1; iVar3 < 5; iVar3 = iVar3 + 1) {
    iVar7 = rand();
    iVar5 = iVar3 * 0xc + 1;
    afStack_120[iVar5] =
         afStack_120[iVar5] + (((float)iVar7 / 2.1474836e+09) * 0.083333336 - 0.041666668);
    iVar7 = rand();
    iVar5 = (iVar3 * 6 + 5) * 2 + 1;
    afStack_120[iVar5] =
         afStack_120[iVar5] + (((float)iVar7 / 2.1474836e+09) * 0.083333336 - 0.041666668);
  }
  for (iVar3 = 1; iVar3 < 5; iVar3 = iVar3 + 1) {
    for (iVar7 = 1; iVar7 < 5; iVar7 = iVar7 + 1) {
      iVar5 = rand();
      iVar2 = iVar7 + iVar3 * 6;
      afStack_120[iVar2 * 2] =
           afStack_120[iVar2 * 2] + (((float)iVar5 / 2.1474836e+09) * 0.125 - 0.0625);
      iVar5 = rand();
      iVar2 = (iVar7 + iVar3 * 6) * 2 + 1;
      afStack_120[iVar2] = afStack_120[iVar2] + (((float)iVar5 / 2.1474836e+09) * 0.125 - 0.0625);
    }
  }
  do {
    for (iVar3 = 0; iVar3 < 0x19; iVar3 = iVar3 + 1) {
      iVar7 = rand();
      acStack_140[iVar3] = (char)(int)(((float)iVar7 / 2.1474836e+09) * 3.0);
    }
    iVar7 = 0;
    for (iVar3 = 0; iVar3 < 0x19; iVar3 = iVar3 + 1) {
      if (acStack_140[iVar3] != '\0') {
        iVar7 = iVar7 + 1;
      }
    }
  } while ((iVar7 < 2) || (0x18 < iVar7));
  iVar7 = iVar7 + 0x19;
  uVar4 = __nwa(iVar7 * 0x80 + 0x10);
  iVar3 = __construct_new_array(uVar4,0x2f0d10,0,0x80,iVar7);
  this[1] = iVar3;
  this[2] = iVar7;
  puVar8 = (undefined2 *)this[1];
  pfVar6 = afStack_120;
  for (iVar3 = 0; iVar3 < 5; iVar3 = iVar3 + 1) {
    for (iVar7 = 0; iVar7 < 5; iVar7 = iVar7 + 1) {
      cVar1 = acStack_140[iVar7 + iVar3 * 5];
      if (cVar1 == '\x02') {
        puVar8[0x40] = 1;
        *puVar8 = 1;
        puVar8[1] = 6;
        puVar8[0x41] = 6;
        puVar8->u32_4c = 0;
        puVar8->u32_c = 0;
        puVar8->u32_50 = 0;
        puVar8->u32_52 = 0;
        puVar8->u32_54 = 0;
        puVar8->u32_56 = 0;
        puVar8->i32_10 = (int)puVar8->u64_50;
        puVar8->i32_12 = (int)((ulong)puVar8->u64_50 >> 0x20);
        puVar8->u32_14 = puVar8->u32_54;
        puVar8->u32_16 = puVar8->u32_56;
        puVar8->u32_5c = 0;
        puVar8->u32_1c = 0;
        fVar9 = ((*pfVar6 - 0.5) * 2.0 * 114.0 + 128.0) * 16.0;
        puVar8->f32_64 = fVar9;
        puVar8->f32_24 = fVar9;
        fVar9 = ((pfVar6[1] - 0.5) * 2.0 * 114.0 + 128.0) * 16.0;
        puVar8->f32_66 = fVar9;
        puVar8->f32_26 = fVar9;
        fVar9 = ((pfVar6[0xe] - 0.5) * 2.0 * 114.0 + 128.0) * 16.0;
        puVar8->f32_6c = fVar9;
        puVar8->f32_34 = fVar9;
        fVar9 = ((pfVar6[0xf] - 0.5) * 2.0 * 114.0 + 128.0) * 16.0;
        puVar8->f32_6e = fVar9;
        puVar8->f32_36 = fVar9;
        puVar8->f32_8 = ((pfVar6[0xe] + *pfVar6 + pfVar6[0xc]) * 114.0 * 2.0) / 3.0;
        puVar8->f32_a = ((pfVar6[0xf] + pfVar6[1] + pfVar6[0xd]) * 114.0 * 2.0) / 3.0;
        iVar5 = rand();
        puVar8->f32_18 = ((float)iVar5 / 2.1474836e+09) * 4.1887903 - 2.0943952;
        iVar5 = rand();
        puVar8->f32_1a = ((float)iVar5 / 2.1474836e+09) * 4.1887903 - 2.0943952;
        puVar8->f32_20 = *pfVar6 * 114.0 * 2.0 - puVar8->f32_8;
        puVar8->f32_22 = pfVar6[1] * 114.0 * 2.0 - puVar8->f32_a;
        puVar8->f32_28 = pfVar6[0xc] * 114.0 * 2.0 - puVar8->f32_8;
        puVar8->f32_2a = pfVar6[0xd] * 114.0 * 2.0 - puVar8->f32_a;
        puVar8->f32_2c = ((pfVar6[0xc] - 0.5) * 2.0 * 114.0 + 128.0) * 16.0;
        puVar8->f32_2e = ((pfVar6[0xd] - 0.5) * 2.0 * 114.0 + 128.0) * 16.0;
        puVar8->f32_30 = pfVar6[0xe] * 114.0 * 2.0 - puVar8->f32_8;
        puVar8->f32_32 = pfVar6[0xf] * 114.0 * 2.0 - puVar8->f32_a;
        puVar8->f32_48 = ((pfVar6[2] + *pfVar6 + pfVar6[0xe]) * 114.0 * 2.0) / 3.0;
        puVar8->f32_4a = ((pfVar6[3] + pfVar6[1] + pfVar6[0xf]) * 114.0 * 2.0) / 3.0;
        iVar5 = rand();
        puVar8->f32_58 = ((float)iVar5 / 2.1474836e+09) * 4.1887903 - 2.0943952;
        iVar5 = rand();
        puVar8->f32_5a = ((float)iVar5 / 2.1474836e+09) * 4.1887903 - 2.0943952;
        puVar8->f32_60 = *pfVar6 * 114.0 * 2.0 - puVar8->f32_48;
        puVar8->f32_62 = pfVar6[1] * 114.0 * 2.0 - puVar8->f32_4a;
        puVar8->f32_68 = pfVar6[0xe] * 114.0 * 2.0 - puVar8->f32_48;
        puVar8->f32_6a = pfVar6[0xf] * 114.0 * 2.0 - puVar8->f32_4a;
        puVar8->f32_70 = pfVar6[2] * 114.0 * 2.0 - puVar8->f32_48;
        puVar8->f32_72 = pfVar6[3] * 114.0 * 2.0 - puVar8->f32_4a;
        puVar8->f32_74 = ((pfVar6[2] - 0.5) * 2.0 * 114.0 + 128.0) * 16.0;
        puVar8->f32_76 = ((pfVar6[3] - 0.5) * 2.0 * 114.0 + 128.0) * 16.0;
        puVar8 = puVar8 + 0x80;
      }
      else if (cVar1 == '\x01') {
        puVar8[0x40] = 1;
        *puVar8 = 1;
        puVar8[1] = 6;
        puVar8[0x41] = 6;
        puVar8->u32_4c = 0;
        puVar8->u32_c = 0;
        puVar8->u32_50 = 0;
        puVar8->u32_52 = 0;
        puVar8->u32_54 = 0;
        puVar8->u32_56 = 0;
        puVar8->i32_10 = (int)puVar8->u64_50;
        puVar8->i32_12 = (int)((ulong)puVar8->u64_50 >> 0x20);
        puVar8->u32_14 = puVar8->u32_54;
        puVar8->u32_16 = puVar8->u32_56;
        puVar8->u32_5c = 0;
        puVar8->u32_1c = 0;
        fVar9 = ((pfVar6[0xc] - 0.5) * 2.0 * 114.0 + 128.0) * 16.0;
        puVar8->f32_6c = fVar9;
        puVar8->f32_2c = fVar9;
        fVar9 = ((pfVar6[0xd] - 0.5) * 2.0 * 114.0 + 128.0) * 16.0;
        puVar8->f32_6e = fVar9;
        puVar8->f32_2e = fVar9;
        fVar9 = ((pfVar6[2] - 0.5) * 2.0 * 114.0 + 128.0) * 16.0;
        puVar8->f32_64 = fVar9;
        puVar8->f32_34 = fVar9;
        fVar9 = ((pfVar6[3] - 0.5) * 2.0 * 114.0 + 128.0) * 16.0;
        puVar8->f32_66 = fVar9;
        puVar8->f32_36 = fVar9;
        puVar8->f32_8 = ((pfVar6[0xc] + *pfVar6 + pfVar6[2]) * 114.0 * 2.0) / 3.0;
        puVar8->f32_a = ((pfVar6[0xd] + pfVar6[1] + pfVar6[3]) * 114.0 * 2.0) / 3.0;
        iVar5 = rand();
        puVar8->f32_18 = ((float)iVar5 / 2.1474836e+09) * 4.1887903 - 2.0943952;
        iVar5 = rand();
        puVar8->f32_1a = ((float)iVar5 / 2.1474836e+09) * 4.1887903 - 2.0943952;
        puVar8->f32_20 = *pfVar6 * 114.0 * 2.0 - puVar8->f32_8;
        puVar8->f32_22 = pfVar6[1] * 114.0 * 2.0 - puVar8->f32_a;
        puVar8->f32_24 = ((*pfVar6 - 0.5) * 2.0 * 114.0 + 128.0) * 16.0;
        puVar8->f32_26 = ((pfVar6[1] - 0.5) * 2.0 * 114.0 + 128.0) * 16.0;
        puVar8->f32_28 = pfVar6[0xc] * 114.0 * 2.0 - puVar8->f32_8;
        puVar8->f32_2a = pfVar6[0xd] * 114.0 * 2.0 - puVar8->f32_a;
        puVar8->f32_30 = pfVar6[2] * 114.0 * 2.0 - puVar8->f32_8;
        puVar8->f32_32 = pfVar6[3] * 114.0 * 2.0 - puVar8->f32_a;
        puVar8->f32_48 = ((pfVar6[0xe] + pfVar6[2] + pfVar6[0xc]) * 114.0 * 2.0) / 3.0;
        puVar8->f32_4a = ((pfVar6[0xf] + pfVar6[3] + pfVar6[0xd]) * 114.0 * 2.0) / 3.0;
        iVar5 = rand();
        puVar8->f32_58 = ((float)iVar5 / 2.1474836e+09) * 4.1887903 - 2.0943952;
        iVar5 = rand();
        puVar8->f32_5a = ((float)iVar5 / 2.1474836e+09) * 4.1887903 - 2.0943952;
        puVar8->f32_60 = pfVar6[2] * 114.0 * 2.0 - puVar8->f32_48;
        puVar8->f32_62 = pfVar6[3] * 114.0 * 2.0 - puVar8->f32_4a;
        puVar8->f32_68 = pfVar6[0xc] * 114.0 * 2.0 - puVar8->f32_48;
        puVar8->f32_6a = pfVar6[0xd] * 114.0 * 2.0 - puVar8->f32_4a;
        puVar8->f32_70 = pfVar6[0xe] * 114.0 * 2.0 - puVar8->f32_48;
        puVar8->f32_72 = pfVar6[0xf] * 114.0 * 2.0 - puVar8->f32_4a;
        puVar8->f32_74 = ((pfVar6[0xe] - 0.5) * 2.0 * 114.0 + 128.0) * 16.0;
        puVar8->f32_76 = ((pfVar6[0xf] - 0.5) * 2.0 * 114.0 + 128.0) * 16.0;
        puVar8 = puVar8 + 0x80;
      }
      else if (cVar1 == '\0') {
        *puVar8 = 0;
        puVar8[1] = 7;
        puVar8->f32_8 =
             ((pfVar6[0xe] + pfVar6[0xc] + *pfVar6 + pfVar6[2]) * 114.0 * 2.0) / 4.0;
        puVar8->f32_a =
             ((pfVar6[0xf] + pfVar6[0xd] + pfVar6[1] + pfVar6[3]) * 114.0 * 2.0) / 4.0;
        puVar8->u32_c = 0;
        puVar8->u32_10 = 0;
        puVar8->u32_12 = 0;
        puVar8->u32_14 = 0;
        puVar8->u32_16 = 0;
        iVar5 = rand();
        puVar8->f32_18 = ((float)iVar5 / 2.1474836e+09) * 4.1887903 - 2.0943952;
        iVar5 = rand();
        puVar8->f32_1a = ((float)iVar5 / 2.1474836e+09) * 4.1887903 - 2.0943952;
        puVar8->u32_1c = 0;
        puVar8->f32_20 = *pfVar6 * 114.0 * 2.0 - puVar8->f32_8;
        puVar8->f32_22 = pfVar6[1] * 114.0 * 2.0 - puVar8->f32_a;
        puVar8->f32_24 = ((*pfVar6 - 0.5) * 2.0 * 114.0 + 128.0) * 16.0;
        puVar8->f32_26 = ((pfVar6[1] - 0.5) * 2.0 * 114.0 + 128.0) * 16.0;
        puVar8->f32_28 = pfVar6[0xc] * 114.0 * 2.0 - puVar8->f32_8;
        puVar8->f32_2a = pfVar6[0xd] * 114.0 * 2.0 - puVar8->f32_a;
        puVar8->f32_2c = ((pfVar6[0xc] - 0.5) * 2.0 * 114.0 + 128.0) * 16.0;
        puVar8->f32_2e = ((pfVar6[0xd] - 0.5) * 2.0 * 114.0 + 128.0) * 16.0;
        puVar8->f32_30 = pfVar6[2] * 114.0 * 2.0 - puVar8->f32_8;
        puVar8->f32_32 = pfVar6[3] * 114.0 * 2.0 - puVar8->f32_a;
        puVar8->f32_34 = ((pfVar6[2] - 0.5) * 2.0 * 114.0 + 128.0) * 16.0;
        puVar8->f32_36 = ((pfVar6[3] - 0.5) * 2.0 * 114.0 + 128.0) * 16.0;
        puVar8->f32_38 = pfVar6[0xe] * 114.0 * 2.0 - puVar8->f32_8;
        puVar8->f32_3a = pfVar6[0xf] * 114.0 * 2.0 - puVar8->f32_a;
        puVar8->f32_3c = ((pfVar6[0xe] - 0.5) * 2.0 * 114.0 + 128.0) * 16.0;
        puVar8->f32_3e = ((pfVar6[0xf] - 0.5) * 2.0 * 114.0 + 128.0) * 16.0;
        puVar8 = puVar8 + 0x40;
      }
      pfVar6 = pfVar6 + 2;
    }
    pfVar6 = pfVar6 + 2;
  }
  auStack_290._4_4_ = in_zero_hi;
  auStack_290._0_4_ = in_zero_lo;
  uStack_288 = in_zero_udw;
  uStack_284 = in_register_0000000c;
  for (iVar3 = 0; iVar3 < 0x24; iVar3 = iVar3 + 1) {
    aiStack_1f0[iVar3] = iVar3;
    auStack_290._4_4_ = (afStack_120[iVar3 * 2 + 1] - 0.5) * 114.0 * 2.0;
    auStack_290._0_4_ = (afStack_120[iVar3 * 2] - 0.5) * 114.0 * 2.0;
    uStack_288 = 0;
    uStack_284 = 0x3f800000;
    fVar9 = (float)FVector::Length(auStack_290);
    afStack_280[iVar3] = fVar9;
  }
  for (iVar3 = 0; iVar7 = iVar3, iVar3 < 0x24; iVar3 = iVar3 + 1) {
    while (iVar7 = iVar7 + 1, iVar7 < 0x24) {
      if (afStack_280[iVar7] < afStack_280[iVar3]) {
        iVar5 = aiStack_1f0[iVar3];
        aiStack_1f0[iVar3] = aiStack_1f0[iVar7];
        aiStack_1f0[iVar7] = iVar5;
        fVar9 = afStack_280[iVar3];
        afStack_280[iVar3] = afStack_280[iVar7];
        afStack_280[iVar7] = fVar9;
      }
      else if ((afStack_280[iVar3] == afStack_280[iVar7]) && (iVar5 = rand(), iVar5 % 100 < 0x33)) {
        iVar5 = aiStack_1f0[iVar3];
        aiStack_1f0[iVar3] = aiStack_1f0[iVar7];
        aiStack_1f0[iVar7] = iVar5;
        fVar9 = afStack_280[iVar3];
        afStack_280[iVar3] = afStack_280[iVar7];
        afStack_280[iVar7] = fVar9;
      }
    }
  }
  *(undefined2 *)((int)this + 0x46) = 0;
  this->u16_11 = 0;
  for (iVar3 = 1; iVar3 < 0x24; iVar3 = iVar3 + 1) {
    iStack_144 = -1;
    iStack_148 = -1;
    iStack_14c = -1;
    iStack_150 = -1;
    iStack_154 = -1;
    iStack_158 = -1;
    iStack_15c = -1;
    iStack_160 = -1;
    for (iVar7 = 0; iVar7 < iVar3; iVar7 = iVar7 + 1) {
      if (aiStack_1f0[iVar7] == aiStack_1f0[iVar3] + -7) {
        iStack_160 = iVar7;
      }
      if (aiStack_1f0[iVar7] == aiStack_1f0[iVar3] + -1) {
        iStack_15c = iVar7;
      }
      if (aiStack_1f0[iVar7] == aiStack_1f0[iVar3] + 5) {
        iStack_158 = iVar7;
      }
      if (aiStack_1f0[iVar7] == aiStack_1f0[iVar3] + -6) {
        iStack_154 = iVar7;
      }
      if (aiStack_1f0[iVar7] == aiStack_1f0[iVar3] + 6) {
        iStack_150 = iVar7;
      }
      if (aiStack_1f0[iVar7] == aiStack_1f0[iVar3] + -5) {
        iStack_14c = iVar7;
      }
      if (aiStack_1f0[iVar7] == aiStack_1f0[iVar3] + 1) {
        iStack_148 = iVar7;
      }
      if (aiStack_1f0[iVar7] == aiStack_1f0[iVar3] + 7) {
        iStack_144 = iVar7;
      }
    }
    if (-1 < iStack_15c) {
      if ((101.0 < afStack_280[iVar3]) || (101.0 < afStack_280[iStack_15c])) {
        if ((101.0 < afStack_280[iVar3]) || (afStack_280[iStack_15c] <= 101.0)) {
          if ((101.0 < afStack_280[iVar3]) && (afStack_280[iStack_15c] <= 101.0)) {
            auStack_290._4_4_ = (afStack_120[aiStack_1f0[iVar3] * 2 + 1] - 0.5) * 114.0 * 2.0;
            auStack_290._0_4_ = (afStack_120[aiStack_1f0[iVar3] * 2] - 0.5) * 114.0 * 2.0;
            uStack_288 = 0;
            uStack_284 = 0x3f800000;
            auStack_2a0._4_4_ = (afStack_120[aiStack_1f0[iStack_15c] * 2 + 1] - 0.5) * 114.0 * 2.0;
            auStack_2a0._0_4_ = (afStack_120[aiStack_1f0[iStack_15c] * 2] - 0.5) * 114.0 * 2.0;
            auStack_2a0._8_4_ = 0;
            uStack_294 = 0x3f800000;
            auVar11 = _lqc2(_auStack_2a0);
            auVar10 = _lqc2(_auStack_290);
            auVar10 = _vsub(auVar10,auVar11);
            _auStack_290 = _sqc2(auVar10);
            FVector::__amu((101.0 - afStack_280[iStack_15c]) /
                              ((101.0 - afStack_280[iStack_15c]) + (afStack_280[iVar3] - 101.0)),
                              auStack_290);
            auVar11 = _lqc2(_auStack_2a0);
            auVar10 = _lqc2(_auStack_290);
            auVar10 = _vadd(auVar10,auVar11);
            auVar10 = _sqc2(auVar10);
            auStack_290._0_4_ = auVar10._0_4_;
            this[(short)this[0x11] * 4 + 0x12] = auStack_290._0_4_;
            auStack_290._4_4_ = auVar10._4_4_;
            this[(short)this[0x11] * 4 + 0x13] = auStack_290._4_4_;
            this[(short)this[0x11] * 4 + 0x14] = auStack_2a0._0_4_;
            this[(short)this[0x11] * 4 + 0x15] = auStack_2a0._4_4_;
            this->i16_11 = (short)this[0x11] + 1;
          }
        }
        else {
          auStack_290._4_4_ = (afStack_120[aiStack_1f0[iVar3] * 2 + 1] - 0.5) * 114.0 * 2.0;
          auStack_290._0_4_ = (afStack_120[aiStack_1f0[iVar3] * 2] - 0.5) * 114.0 * 2.0;
          uStack_288 = 0;
          uStack_284 = 0x3f800000;
          auStack_2a0._4_4_ = (afStack_120[aiStack_1f0[iStack_15c] * 2 + 1] - 0.5) * 114.0 * 2.0;
          auStack_2a0._0_4_ = (afStack_120[aiStack_1f0[iStack_15c] * 2] - 0.5) * 114.0 * 2.0;
          auStack_2a0._8_4_ = 0;
          uStack_294 = 0x3f800000;
          auVar11 = _lqc2(_auStack_290);
          auVar10 = _lqc2(_auStack_2a0);
          auVar10 = _vsub(auVar10,auVar11);
          _auStack_2a0 = _sqc2(auVar10);
          FVector::__amu((101.0 - afStack_280[iVar3]) /
                            ((101.0 - afStack_280[iVar3]) + (afStack_280[iStack_15c] - 101.0)),
                            auStack_2a0);
          auVar11 = _lqc2(_auStack_290);
          auVar10 = _lqc2(_auStack_2a0);
          auVar10 = _vadd(auVar10,auVar11);
          auVar10 = _sqc2(auVar10);
          this[(short)this[0x11] * 4 + 0x12] = auStack_290._0_4_;
          this[(short)this[0x11] * 4 + 0x13] = auStack_290._4_4_;
          auStack_2a0._0_4_ = auVar10._0_4_;
          this[(short)this[0x11] * 4 + 0x14] = auStack_2a0._0_4_;
          auStack_2a0._4_4_ = auVar10._4_4_;
          this[(short)this[0x11] * 4 + 0x15] = auStack_2a0._4_4_;
          this->i16_11 = (short)this[0x11] + 1;
        }
      }
      else {
        this[(short)this[0x11] * 4 + 0x12] =
             (int)((afStack_120[aiStack_1f0[iVar3] * 2] - 0.5) * 114.0 * 2.0);
        this[(short)this[0x11] * 4 + 0x13] =
             (int)((afStack_120[aiStack_1f0[iVar3] * 2 + 1] - 0.5) * 114.0 * 2.0);
        this[(short)this[0x11] * 4 + 0x14] =
             (int)((afStack_120[aiStack_1f0[iStack_15c] * 2] - 0.5) * 114.0 * 2.0);
        this[(short)this[0x11] * 4 + 0x15] =
             (int)((afStack_120[aiStack_1f0[iStack_15c] * 2 + 1] - 0.5) * 114.0 * 2.0);
        this->i16_11 = (short)this[0x11] + 1;
      }
    }
    if (-1 < iStack_154) {
      if ((101.0 < afStack_280[iVar3]) || (101.0 < afStack_280[iStack_154])) {
        if ((101.0 < afStack_280[iVar3]) || (afStack_280[iStack_154] <= 101.0)) {
          if ((101.0 < afStack_280[iVar3]) && (afStack_280[iStack_154] <= 101.0)) {
            auStack_290._4_4_ = (afStack_120[aiStack_1f0[iVar3] * 2 + 1] - 0.5) * 114.0 * 2.0;
            auStack_290._0_4_ = (afStack_120[aiStack_1f0[iVar3] * 2] - 0.5) * 114.0 * 2.0;
            uStack_288 = 0;
            uStack_284 = 0x3f800000;
            auStack_2a0._4_4_ = (afStack_120[aiStack_1f0[iStack_154] * 2 + 1] - 0.5) * 114.0 * 2.0;
            auStack_2a0._0_4_ = (afStack_120[aiStack_1f0[iStack_154] * 2] - 0.5) * 114.0 * 2.0;
            auStack_2a0._8_4_ = 0;
            uStack_294 = 0x3f800000;
            auVar11 = _lqc2(_auStack_2a0);
            auVar10 = _lqc2(_auStack_290);
            auVar10 = _vsub(auVar10,auVar11);
            _auStack_290 = _sqc2(auVar10);
            FVector::__amu((101.0 - afStack_280[iStack_154]) /
                              ((101.0 - afStack_280[iStack_154]) + (afStack_280[iVar3] - 101.0)),
                              auStack_290);
            auVar11 = _lqc2(_auStack_2a0);
            auVar10 = _lqc2(_auStack_290);
            auVar10 = _vadd(auVar10,auVar11);
            auVar10 = _sqc2(auVar10);
            auStack_290._0_4_ = auVar10._0_4_;
            this[(short)this[0x11] * 4 + 0x12] = auStack_290._0_4_;
            auStack_290._4_4_ = auVar10._4_4_;
            this[(short)this[0x11] * 4 + 0x13] = auStack_290._4_4_;
            this[(short)this[0x11] * 4 + 0x14] = auStack_2a0._0_4_;
            this[(short)this[0x11] * 4 + 0x15] = auStack_2a0._4_4_;
            this->i16_11 = (short)this[0x11] + 1;
          }
        }
        else {
          auStack_290._4_4_ = (afStack_120[aiStack_1f0[iVar3] * 2 + 1] - 0.5) * 114.0 * 2.0;
          auStack_290._0_4_ = (afStack_120[aiStack_1f0[iVar3] * 2] - 0.5) * 114.0 * 2.0;
          uStack_288 = 0;
          uStack_284 = 0x3f800000;
          auStack_2a0._4_4_ = (afStack_120[aiStack_1f0[iStack_154] * 2 + 1] - 0.5) * 114.0 * 2.0;
          auStack_2a0._0_4_ = (afStack_120[aiStack_1f0[iStack_154] * 2] - 0.5) * 114.0 * 2.0;
          auStack_2a0._8_4_ = 0;
          uStack_294 = 0x3f800000;
          auVar11 = _lqc2(_auStack_290);
          auVar10 = _lqc2(_auStack_2a0);
          auVar10 = _vsub(auVar10,auVar11);
          _auStack_2a0 = _sqc2(auVar10);
          FVector::__amu((101.0 - afStack_280[iVar3]) /
                            ((101.0 - afStack_280[iVar3]) + (afStack_280[iStack_154] - 101.0)),
                            auStack_2a0);
          auVar11 = _lqc2(_auStack_290);
          auVar10 = _lqc2(_auStack_2a0);
          auVar10 = _vadd(auVar10,auVar11);
          auVar10 = _sqc2(auVar10);
          this[(short)this[0x11] * 4 + 0x12] = auStack_290._0_4_;
          this[(short)this[0x11] * 4 + 0x13] = auStack_290._4_4_;
          auStack_2a0._0_4_ = auVar10._0_4_;
          this[(short)this[0x11] * 4 + 0x14] = auStack_2a0._0_4_;
          auStack_2a0._4_4_ = auVar10._4_4_;
          this[(short)this[0x11] * 4 + 0x15] = auStack_2a0._4_4_;
          this->i16_11 = (short)this[0x11] + 1;
        }
      }
      else {
        this[(short)this[0x11] * 4 + 0x12] =
             (int)((afStack_120[aiStack_1f0[iVar3] * 2] - 0.5) * 114.0 * 2.0);
        this[(short)this[0x11] * 4 + 0x13] =
             (int)((afStack_120[aiStack_1f0[iVar3] * 2 + 1] - 0.5) * 114.0 * 2.0);
        this[(short)this[0x11] * 4 + 0x14] =
             (int)((afStack_120[aiStack_1f0[iStack_154] * 2] - 0.5) * 114.0 * 2.0);
        this[(short)this[0x11] * 4 + 0x15] =
             (int)((afStack_120[aiStack_1f0[iStack_154] * 2 + 1] - 0.5) * 114.0 * 2.0);
        this->i16_11 = (short)this[0x11] + 1;
      }
    }
    if (-1 < iStack_150) {
      if ((101.0 < afStack_280[iVar3]) || (101.0 < afStack_280[iStack_150])) {
        if ((101.0 < afStack_280[iVar3]) || (afStack_280[iStack_150] <= 101.0)) {
          if ((101.0 < afStack_280[iVar3]) && (afStack_280[iStack_150] <= 101.0)) {
            auStack_290._4_4_ = (afStack_120[aiStack_1f0[iVar3] * 2 + 1] - 0.5) * 114.0 * 2.0;
            auStack_290._0_4_ = (afStack_120[aiStack_1f0[iVar3] * 2] - 0.5) * 114.0 * 2.0;
            uStack_288 = 0;
            uStack_284 = 0x3f800000;
            auStack_2a0._4_4_ = (afStack_120[aiStack_1f0[iStack_150] * 2 + 1] - 0.5) * 114.0 * 2.0;
            auStack_2a0._0_4_ = (afStack_120[aiStack_1f0[iStack_150] * 2] - 0.5) * 114.0 * 2.0;
            auStack_2a0._8_4_ = 0;
            uStack_294 = 0x3f800000;
            auVar11 = _lqc2(_auStack_2a0);
            auVar10 = _lqc2(_auStack_290);
            auVar10 = _vsub(auVar10,auVar11);
            _auStack_290 = _sqc2(auVar10);
            FVector::__amu((101.0 - afStack_280[iStack_150]) /
                              ((101.0 - afStack_280[iStack_150]) + (afStack_280[iVar3] - 101.0)),
                              auStack_290);
            auVar11 = _lqc2(_auStack_2a0);
            auVar10 = _lqc2(_auStack_290);
            auVar10 = _vadd(auVar10,auVar11);
            auVar10 = _sqc2(auVar10);
            auStack_290._0_4_ = auVar10._0_4_;
            this[(short)this[0x11] * 4 + 0x12] = auStack_290._0_4_;
            auStack_290._4_4_ = auVar10._4_4_;
            this[(short)this[0x11] * 4 + 0x13] = auStack_290._4_4_;
            this[(short)this[0x11] * 4 + 0x14] = auStack_2a0._0_4_;
            this[(short)this[0x11] * 4 + 0x15] = auStack_2a0._4_4_;
            this->i16_11 = (short)this[0x11] + 1;
          }
        }
        else {
          auStack_290._4_4_ = (afStack_120[aiStack_1f0[iVar3] * 2 + 1] - 0.5) * 114.0 * 2.0;
          auStack_290._0_4_ = (afStack_120[aiStack_1f0[iVar3] * 2] - 0.5) * 114.0 * 2.0;
          uStack_288 = 0;
          uStack_284 = 0x3f800000;
          auStack_2a0._4_4_ = (afStack_120[aiStack_1f0[iStack_150] * 2 + 1] - 0.5) * 114.0 * 2.0;
          auStack_2a0._0_4_ = (afStack_120[aiStack_1f0[iStack_150] * 2] - 0.5) * 114.0 * 2.0;
          auStack_2a0._8_4_ = 0;
          uStack_294 = 0x3f800000;
          auVar11 = _lqc2(_auStack_290);
          auVar10 = _lqc2(_auStack_2a0);
          auVar10 = _vsub(auVar10,auVar11);
          _auStack_2a0 = _sqc2(auVar10);
          FVector::__amu((101.0 - afStack_280[iVar3]) /
                            ((101.0 - afStack_280[iVar3]) + (afStack_280[iStack_150] - 101.0)),
                            auStack_2a0);
          auVar11 = _lqc2(_auStack_290);
          auVar10 = _lqc2(_auStack_2a0);
          auVar10 = _vadd(auVar10,auVar11);
          auVar10 = _sqc2(auVar10);
          this[(short)this[0x11] * 4 + 0x12] = auStack_290._0_4_;
          this[(short)this[0x11] * 4 + 0x13] = auStack_290._4_4_;
          auStack_2a0._0_4_ = auVar10._0_4_;
          this[(short)this[0x11] * 4 + 0x14] = auStack_2a0._0_4_;
          auStack_2a0._4_4_ = auVar10._4_4_;
          this[(short)this[0x11] * 4 + 0x15] = auStack_2a0._4_4_;
          this->i16_11 = (short)this[0x11] + 1;
        }
      }
      else {
        this[(short)this[0x11] * 4 + 0x12] =
             (int)((afStack_120[aiStack_1f0[iVar3] * 2] - 0.5) * 114.0 * 2.0);
        this[(short)this[0x11] * 4 + 0x13] =
             (int)((afStack_120[aiStack_1f0[iVar3] * 2 + 1] - 0.5) * 114.0 * 2.0);
        this[(short)this[0x11] * 4 + 0x14] =
             (int)((afStack_120[aiStack_1f0[iStack_150] * 2] - 0.5) * 114.0 * 2.0);
        this[(short)this[0x11] * 4 + 0x15] =
             (int)((afStack_120[aiStack_1f0[iStack_150] * 2 + 1] - 0.5) * 114.0 * 2.0);
        this->i16_11 = (short)this[0x11] + 1;
      }
    }
    if (-1 < iStack_148) {
      if ((101.0 < afStack_280[iVar3]) || (101.0 < afStack_280[iStack_148])) {
        if ((101.0 < afStack_280[iVar3]) || (afStack_280[iStack_148] <= 101.0)) {
          if ((101.0 < afStack_280[iVar3]) && (afStack_280[iStack_148] <= 101.0)) {
            auStack_290._4_4_ = (afStack_120[aiStack_1f0[iVar3] * 2 + 1] - 0.5) * 114.0 * 2.0;
            auStack_290._0_4_ = (afStack_120[aiStack_1f0[iVar3] * 2] - 0.5) * 114.0 * 2.0;
            uStack_288 = 0;
            uStack_284 = 0x3f800000;
            auStack_2a0._4_4_ = (afStack_120[aiStack_1f0[iStack_148] * 2 + 1] - 0.5) * 114.0 * 2.0;
            auStack_2a0._0_4_ = (afStack_120[aiStack_1f0[iStack_148] * 2] - 0.5) * 114.0 * 2.0;
            auStack_2a0._8_4_ = 0;
            uStack_294 = 0x3f800000;
            auVar11 = _lqc2(_auStack_2a0);
            auVar10 = _lqc2(_auStack_290);
            auVar10 = _vsub(auVar10,auVar11);
            _auStack_290 = _sqc2(auVar10);
            FVector::__amu((101.0 - afStack_280[iStack_148]) /
                              ((101.0 - afStack_280[iStack_148]) + (afStack_280[iVar3] - 101.0)),
                              auStack_290);
            auVar11 = _lqc2(_auStack_2a0);
            auVar10 = _lqc2(_auStack_290);
            auVar10 = _vadd(auVar10,auVar11);
            auVar10 = _sqc2(auVar10);
            auStack_290._0_4_ = auVar10._0_4_;
            this[(short)this[0x11] * 4 + 0x12] = auStack_290._0_4_;
            auStack_290._4_4_ = auVar10._4_4_;
            this[(short)this[0x11] * 4 + 0x13] = auStack_290._4_4_;
            this[(short)this[0x11] * 4 + 0x14] = auStack_2a0._0_4_;
            this[(short)this[0x11] * 4 + 0x15] = auStack_2a0._4_4_;
            this->i16_11 = (short)this[0x11] + 1;
          }
        }
        else {
          auStack_290._4_4_ = (afStack_120[aiStack_1f0[iVar3] * 2 + 1] - 0.5) * 114.0 * 2.0;
          auStack_290._0_4_ = (afStack_120[aiStack_1f0[iVar3] * 2] - 0.5) * 114.0 * 2.0;
          uStack_288 = 0;
          uStack_284 = 0x3f800000;
          auStack_2a0._4_4_ = (afStack_120[aiStack_1f0[iStack_148] * 2 + 1] - 0.5) * 114.0 * 2.0;
          auStack_2a0._0_4_ = (afStack_120[aiStack_1f0[iStack_148] * 2] - 0.5) * 114.0 * 2.0;
          auStack_2a0._8_4_ = 0;
          uStack_294 = 0x3f800000;
          auVar11 = _lqc2(_auStack_290);
          auVar10 = _lqc2(_auStack_2a0);
          auVar10 = _vsub(auVar10,auVar11);
          _auStack_2a0 = _sqc2(auVar10);
          FVector::__amu((101.0 - afStack_280[iVar3]) /
                            ((101.0 - afStack_280[iVar3]) + (afStack_280[iStack_148] - 101.0)),
                            auStack_2a0);
          auVar11 = _lqc2(_auStack_290);
          auVar10 = _lqc2(_auStack_2a0);
          auVar10 = _vadd(auVar10,auVar11);
          auVar10 = _sqc2(auVar10);
          this[(short)this[0x11] * 4 + 0x12] = auStack_290._0_4_;
          this[(short)this[0x11] * 4 + 0x13] = auStack_290._4_4_;
          auStack_2a0._0_4_ = auVar10._0_4_;
          this[(short)this[0x11] * 4 + 0x14] = auStack_2a0._0_4_;
          auStack_2a0._4_4_ = auVar10._4_4_;
          this[(short)this[0x11] * 4 + 0x15] = auStack_2a0._4_4_;
          this->i16_11 = (short)this[0x11] + 1;
        }
      }
      else {
        this[(short)this[0x11] * 4 + 0x12] =
             (int)((afStack_120[aiStack_1f0[iVar3] * 2] - 0.5) * 114.0 * 2.0);
        this[(short)this[0x11] * 4 + 0x13] =
             (int)((afStack_120[aiStack_1f0[iVar3] * 2 + 1] - 0.5) * 114.0 * 2.0);
        this[(short)this[0x11] * 4 + 0x14] =
             (int)((afStack_120[aiStack_1f0[iStack_148] * 2] - 0.5) * 114.0 * 2.0);
        this[(short)this[0x11] * 4 + 0x15] =
             (int)((afStack_120[aiStack_1f0[iStack_148] * 2 + 1] - 0.5) * 114.0 * 2.0);
        this->i16_11 = (short)this[0x11] + 1;
      }
    }
    iVar5 = aiStack_1f0[iVar3] / 6;
    iVar7 = aiStack_1f0[iVar3] % 6;
    if (0 < iVar5) {
      iVar5 = iVar5 + -1;
    }
    if (0 < iVar7) {
      iVar7 = iVar7 + -1;
    }
    if ((-1 < iStack_160) && (acStack_140[iVar5 * 5 + iVar7] == '\x02')) {
      if ((101.0 < afStack_280[iVar3]) || (101.0 < afStack_280[iStack_160])) {
        if ((101.0 < afStack_280[iVar3]) || (afStack_280[iStack_160] <= 101.0)) {
          if ((101.0 < afStack_280[iVar3]) && (afStack_280[iStack_160] <= 101.0)) {
            auStack_290._4_4_ = (afStack_120[aiStack_1f0[iVar3] * 2 + 1] - 0.5) * 114.0 * 2.0;
            auStack_290._0_4_ = (afStack_120[aiStack_1f0[iVar3] * 2] - 0.5) * 114.0 * 2.0;
            uStack_288 = 0;
            uStack_284 = 0x3f800000;
            auStack_2a0._4_4_ = (afStack_120[aiStack_1f0[iStack_160] * 2 + 1] - 0.5) * 114.0 * 2.0;
            auStack_2a0._0_4_ = (afStack_120[aiStack_1f0[iStack_160] * 2] - 0.5) * 114.0 * 2.0;
            auStack_2a0._8_4_ = 0;
            uStack_294 = 0x3f800000;
            auVar11 = _lqc2(_auStack_2a0);
            auVar10 = _lqc2(_auStack_290);
            auVar10 = _vsub(auVar10,auVar11);
            _auStack_290 = _sqc2(auVar10);
            FVector::__amu((101.0 - afStack_280[iStack_160]) /
                              ((101.0 - afStack_280[iStack_160]) + (afStack_280[iVar3] - 101.0)),
                              auStack_290);
            auVar11 = _lqc2(_auStack_2a0);
            auVar10 = _lqc2(_auStack_290);
            auVar10 = _vadd(auVar10,auVar11);
            auVar10 = _sqc2(auVar10);
            auStack_290._0_4_ = auVar10._0_4_;
            this[(short)this[0x11] * 4 + 0x12] = auStack_290._0_4_;
            auStack_290._4_4_ = auVar10._4_4_;
            this[(short)this[0x11] * 4 + 0x13] = auStack_290._4_4_;
            this[(short)this[0x11] * 4 + 0x14] = auStack_2a0._0_4_;
            this[(short)this[0x11] * 4 + 0x15] = auStack_2a0._4_4_;
            this->i16_11 = (short)this[0x11] + 1;
          }
        }
        else {
          auStack_290._4_4_ = (afStack_120[aiStack_1f0[iVar3] * 2 + 1] - 0.5) * 114.0 * 2.0;
          auStack_290._0_4_ = (afStack_120[aiStack_1f0[iVar3] * 2] - 0.5) * 114.0 * 2.0;
          uStack_288 = 0;
          uStack_284 = 0x3f800000;
          auStack_2a0._4_4_ = (afStack_120[aiStack_1f0[iStack_160] * 2 + 1] - 0.5) * 114.0 * 2.0;
          auStack_2a0._0_4_ = (afStack_120[aiStack_1f0[iStack_160] * 2] - 0.5) * 114.0 * 2.0;
          auStack_2a0._8_4_ = 0;
          uStack_294 = 0x3f800000;
          auVar11 = _lqc2(_auStack_290);
          auVar10 = _lqc2(_auStack_2a0);
          auVar10 = _vsub(auVar10,auVar11);
          _auStack_2a0 = _sqc2(auVar10);
          FVector::__amu((101.0 - afStack_280[iVar3]) /
                            ((101.0 - afStack_280[iVar3]) + (afStack_280[iStack_160] - 101.0)),
                            auStack_2a0);
          auVar11 = _lqc2(_auStack_290);
          auVar10 = _lqc2(_auStack_2a0);
          auVar10 = _vadd(auVar10,auVar11);
          auVar10 = _sqc2(auVar10);
          this[(short)this[0x11] * 4 + 0x12] = auStack_290._0_4_;
          this[(short)this[0x11] * 4 + 0x13] = auStack_290._4_4_;
          auStack_2a0._0_4_ = auVar10._0_4_;
          this[(short)this[0x11] * 4 + 0x14] = auStack_2a0._0_4_;
          auStack_2a0._4_4_ = auVar10._4_4_;
          this[(short)this[0x11] * 4 + 0x15] = auStack_2a0._4_4_;
          this->i16_11 = (short)this[0x11] + 1;
        }
      }
      else {
        this[(short)this[0x11] * 4 + 0x12] =
             (int)((afStack_120[aiStack_1f0[iVar3] * 2] - 0.5) * 114.0 * 2.0);
        this[(short)this[0x11] * 4 + 0x13] =
             (int)((afStack_120[aiStack_1f0[iVar3] * 2 + 1] - 0.5) * 114.0 * 2.0);
        this[(short)this[0x11] * 4 + 0x14] =
             (int)((afStack_120[aiStack_1f0[iStack_160] * 2] - 0.5) * 114.0 * 2.0);
        this[(short)this[0x11] * 4 + 0x15] =
             (int)((afStack_120[aiStack_1f0[iStack_160] * 2 + 1] - 0.5) * 114.0 * 2.0);
        this->i16_11 = (short)this[0x11] + 1;
      }
    }
    iVar7 = aiStack_1f0[iVar3] % 6;
    if (0 < iVar7) {
      iVar7 = iVar7 + -1;
    }
    if ((-1 < iStack_158) && (acStack_140[(aiStack_1f0[iVar3] / 6) * 5 + iVar7] == '\x01')) {
      if ((101.0 < afStack_280[iVar3]) || (101.0 < afStack_280[iStack_158])) {
        if ((101.0 < afStack_280[iVar3]) || (afStack_280[iStack_158] <= 101.0)) {
          if ((101.0 < afStack_280[iVar3]) && (afStack_280[iStack_158] <= 101.0)) {
            auStack_290._4_4_ = (afStack_120[aiStack_1f0[iVar3] * 2 + 1] - 0.5) * 114.0 * 2.0;
            auStack_290._0_4_ = (afStack_120[aiStack_1f0[iVar3] * 2] - 0.5) * 114.0 * 2.0;
            uStack_288 = 0;
            uStack_284 = 0x3f800000;
            auStack_2a0._4_4_ = (afStack_120[aiStack_1f0[iStack_158] * 2 + 1] - 0.5) * 114.0 * 2.0;
            auStack_2a0._0_4_ = (afStack_120[aiStack_1f0[iStack_158] * 2] - 0.5) * 114.0 * 2.0;
            auStack_2a0._8_4_ = 0;
            uStack_294 = 0x3f800000;
            auVar11 = _lqc2(_auStack_2a0);
            auVar10 = _lqc2(_auStack_290);
            auVar10 = _vsub(auVar10,auVar11);
            _auStack_290 = _sqc2(auVar10);
            FVector::__amu((101.0 - afStack_280[iStack_158]) /
                              ((101.0 - afStack_280[iStack_158]) + (afStack_280[iVar3] - 101.0)),
                              auStack_290);
            auVar11 = _lqc2(_auStack_2a0);
            auVar10 = _lqc2(_auStack_290);
            auVar10 = _vadd(auVar10,auVar11);
            auVar10 = _sqc2(auVar10);
            auStack_290._0_4_ = auVar10._0_4_;
            this[(short)this[0x11] * 4 + 0x12] = auStack_290._0_4_;
            auStack_290._4_4_ = auVar10._4_4_;
            this[(short)this[0x11] * 4 + 0x13] = auStack_290._4_4_;
            this[(short)this[0x11] * 4 + 0x14] = auStack_2a0._0_4_;
            this[(short)this[0x11] * 4 + 0x15] = auStack_2a0._4_4_;
            this->i16_11 = (short)this[0x11] + 1;
          }
        }
        else {
          auStack_290._4_4_ = (afStack_120[aiStack_1f0[iVar3] * 2 + 1] - 0.5) * 114.0 * 2.0;
          auStack_290._0_4_ = (afStack_120[aiStack_1f0[iVar3] * 2] - 0.5) * 114.0 * 2.0;
          uStack_288 = 0;
          uStack_284 = 0x3f800000;
          auStack_2a0._4_4_ = (afStack_120[aiStack_1f0[iStack_158] * 2 + 1] - 0.5) * 114.0 * 2.0;
          auStack_2a0._0_4_ = (afStack_120[aiStack_1f0[iStack_158] * 2] - 0.5) * 114.0 * 2.0;
          auStack_2a0._8_4_ = 0;
          uStack_294 = 0x3f800000;
          auVar11 = _lqc2(_auStack_290);
          auVar10 = _lqc2(_auStack_2a0);
          auVar10 = _vsub(auVar10,auVar11);
          _auStack_2a0 = _sqc2(auVar10);
          FVector::__amu((101.0 - afStack_280[iVar3]) /
                            ((101.0 - afStack_280[iVar3]) + (afStack_280[iStack_158] - 101.0)),
                            auStack_2a0);
          auVar11 = _lqc2(_auStack_290);
          auVar10 = _lqc2(_auStack_2a0);
          auVar10 = _vadd(auVar10,auVar11);
          auVar10 = _sqc2(auVar10);
          this[(short)this[0x11] * 4 + 0x12] = auStack_290._0_4_;
          this[(short)this[0x11] * 4 + 0x13] = auStack_290._4_4_;
          auStack_2a0._0_4_ = auVar10._0_4_;
          this[(short)this[0x11] * 4 + 0x14] = auStack_2a0._0_4_;
          auStack_2a0._4_4_ = auVar10._4_4_;
          this[(short)this[0x11] * 4 + 0x15] = auStack_2a0._4_4_;
          this->i16_11 = (short)this[0x11] + 1;
        }
      }
      else {
        this[(short)this[0x11] * 4 + 0x12] =
             (int)((afStack_120[aiStack_1f0[iVar3] * 2] - 0.5) * 114.0 * 2.0);
        this[(short)this[0x11] * 4 + 0x13] =
             (int)((afStack_120[aiStack_1f0[iVar3] * 2 + 1] - 0.5) * 114.0 * 2.0);
        this[(short)this[0x11] * 4 + 0x14] =
             (int)((afStack_120[aiStack_1f0[iStack_158] * 2] - 0.5) * 114.0 * 2.0);
        this[(short)this[0x11] * 4 + 0x15] =
             (int)((afStack_120[aiStack_1f0[iStack_158] * 2 + 1] - 0.5) * 114.0 * 2.0);
        this->i16_11 = (short)this[0x11] + 1;
      }
    }
    iVar7 = aiStack_1f0[iVar3] / 6;
    if (0 < iVar7) {
      iVar7 = iVar7 + -1;
    }
    if ((-1 < iStack_14c) && (acStack_140[iVar7 * 5 + aiStack_1f0[iVar3] % 6] == '\x01')) {
      if ((101.0 < afStack_280[iVar3]) || (101.0 < afStack_280[iStack_14c])) {
        if ((101.0 < afStack_280[iVar3]) || (afStack_280[iStack_14c] <= 101.0)) {
          if ((101.0 < afStack_280[iVar3]) && (afStack_280[iStack_14c] <= 101.0)) {
            auStack_290._4_4_ = (afStack_120[aiStack_1f0[iVar3] * 2 + 1] - 0.5) * 114.0 * 2.0;
            auStack_290._0_4_ = (afStack_120[aiStack_1f0[iVar3] * 2] - 0.5) * 114.0 * 2.0;
            uStack_288 = 0;
            uStack_284 = 0x3f800000;
            auStack_2a0._4_4_ = (afStack_120[aiStack_1f0[iStack_14c] * 2 + 1] - 0.5) * 114.0 * 2.0;
            auStack_2a0._0_4_ = (afStack_120[aiStack_1f0[iStack_14c] * 2] - 0.5) * 114.0 * 2.0;
            auStack_2a0._8_4_ = 0;
            uStack_294 = 0x3f800000;
            auVar11 = _lqc2(_auStack_2a0);
            auVar10 = _lqc2(_auStack_290);
            auVar10 = _vsub(auVar10,auVar11);
            _auStack_290 = _sqc2(auVar10);
            FVector::__amu((101.0 - afStack_280[iStack_14c]) /
                              ((101.0 - afStack_280[iStack_14c]) + (afStack_280[iVar3] - 101.0)),
                              auStack_290);
            auVar11 = _lqc2(_auStack_2a0);
            auVar10 = _lqc2(_auStack_290);
            auVar10 = _vadd(auVar10,auVar11);
            auVar10 = _sqc2(auVar10);
            auStack_290._0_4_ = auVar10._0_4_;
            this[(short)this[0x11] * 4 + 0x12] = auStack_290._0_4_;
            auStack_290._4_4_ = auVar10._4_4_;
            this[(short)this[0x11] * 4 + 0x13] = auStack_290._4_4_;
            this[(short)this[0x11] * 4 + 0x14] = auStack_2a0._0_4_;
            this[(short)this[0x11] * 4 + 0x15] = auStack_2a0._4_4_;
            this->i16_11 = (short)this[0x11] + 1;
          }
        }
        else {
          auStack_290._4_4_ = (afStack_120[aiStack_1f0[iVar3] * 2 + 1] - 0.5) * 114.0 * 2.0;
          auStack_290._0_4_ = (afStack_120[aiStack_1f0[iVar3] * 2] - 0.5) * 114.0 * 2.0;
          uStack_288 = 0;
          uStack_284 = 0x3f800000;
          auStack_2a0._4_4_ = (afStack_120[aiStack_1f0[iStack_14c] * 2 + 1] - 0.5) * 114.0 * 2.0;
          auStack_2a0._0_4_ = (afStack_120[aiStack_1f0[iStack_14c] * 2] - 0.5) * 114.0 * 2.0;
          auStack_2a0._8_4_ = 0;
          uStack_294 = 0x3f800000;
          auVar11 = _lqc2(_auStack_290);
          auVar10 = _lqc2(_auStack_2a0);
          auVar10 = _vsub(auVar10,auVar11);
          _auStack_2a0 = _sqc2(auVar10);
          FVector::__amu((101.0 - afStack_280[iVar3]) /
                            ((101.0 - afStack_280[iVar3]) + (afStack_280[iStack_14c] - 101.0)),
                            auStack_2a0);
          auVar11 = _lqc2(_auStack_290);
          auVar10 = _lqc2(_auStack_2a0);
          auVar10 = _vadd(auVar10,auVar11);
          auVar10 = _sqc2(auVar10);
          this[(short)this[0x11] * 4 + 0x12] = auStack_290._0_4_;
          this[(short)this[0x11] * 4 + 0x13] = auStack_290._4_4_;
          auStack_2a0._0_4_ = auVar10._0_4_;
          this[(short)this[0x11] * 4 + 0x14] = auStack_2a0._0_4_;
          auStack_2a0._4_4_ = auVar10._4_4_;
          this[(short)this[0x11] * 4 + 0x15] = auStack_2a0._4_4_;
          this->i16_11 = (short)this[0x11] + 1;
        }
      }
      else {
        this[(short)this[0x11] * 4 + 0x12] =
             (int)((afStack_120[aiStack_1f0[iVar3] * 2] - 0.5) * 114.0 * 2.0);
        this[(short)this[0x11] * 4 + 0x13] =
             (int)((afStack_120[aiStack_1f0[iVar3] * 2 + 1] - 0.5) * 114.0 * 2.0);
        this[(short)this[0x11] * 4 + 0x14] =
             (int)((afStack_120[aiStack_1f0[iStack_14c] * 2] - 0.5) * 114.0 * 2.0);
        this[(short)this[0x11] * 4 + 0x15] =
             (int)((afStack_120[aiStack_1f0[iStack_14c] * 2 + 1] - 0.5) * 114.0 * 2.0);
        this->i16_11 = (short)this[0x11] + 1;
      }
    }
    if ((-1 < iStack_144) &&
       (acStack_140[(aiStack_1f0[iVar3] / 6) * 5 + aiStack_1f0[iVar3] % 6] == '\x02')) {
      if ((101.0 < afStack_280[iVar3]) || (101.0 < afStack_280[iStack_144])) {
        if ((101.0 < afStack_280[iVar3]) || (afStack_280[iStack_144] <= 101.0)) {
          if ((101.0 < afStack_280[iVar3]) && (afStack_280[iStack_144] <= 101.0)) {
            auStack_290._4_4_ = (afStack_120[aiStack_1f0[iVar3] * 2 + 1] - 0.5) * 114.0 * 2.0;
            auStack_290._0_4_ = (afStack_120[aiStack_1f0[iVar3] * 2] - 0.5) * 114.0 * 2.0;
            uStack_288 = 0;
            uStack_284 = 0x3f800000;
            auStack_2a0._4_4_ = (afStack_120[aiStack_1f0[iStack_144] * 2 + 1] - 0.5) * 114.0 * 2.0;
            auStack_2a0._0_4_ = (afStack_120[aiStack_1f0[iStack_144] * 2] - 0.5) * 114.0 * 2.0;
            auStack_2a0._8_4_ = 0;
            uStack_294 = 0x3f800000;
            auVar11 = _lqc2(_auStack_2a0);
            auVar10 = _lqc2(_auStack_290);
            auVar10 = _vsub(auVar10,auVar11);
            _auStack_290 = _sqc2(auVar10);
            FVector::__amu((101.0 - afStack_280[iStack_144]) /
                              ((101.0 - afStack_280[iStack_144]) + (afStack_280[iVar3] - 101.0)),
                              auStack_290);
            auVar11 = _lqc2(_auStack_2a0);
            auVar10 = _lqc2(_auStack_290);
            auVar10 = _vadd(auVar10,auVar11);
            auVar10 = _sqc2(auVar10);
            auStack_290._0_4_ = auVar10._0_4_;
            this[(short)this[0x11] * 4 + 0x12] = auStack_290._0_4_;
            auStack_290._4_4_ = auVar10._4_4_;
            this[(short)this[0x11] * 4 + 0x13] = auStack_290._4_4_;
            this[(short)this[0x11] * 4 + 0x14] = auStack_2a0._0_4_;
            this[(short)this[0x11] * 4 + 0x15] = auStack_2a0._4_4_;
            this->i16_11 = (short)this[0x11] + 1;
          }
        }
        else {
          auStack_290._4_4_ = (afStack_120[aiStack_1f0[iVar3] * 2 + 1] - 0.5) * 114.0 * 2.0;
          auStack_290._0_4_ = (afStack_120[aiStack_1f0[iVar3] * 2] - 0.5) * 114.0 * 2.0;
          uStack_288 = 0;
          uStack_284 = 0x3f800000;
          auStack_2a0._4_4_ = (afStack_120[aiStack_1f0[iStack_144] * 2 + 1] - 0.5) * 114.0 * 2.0;
          auStack_2a0._0_4_ = (afStack_120[aiStack_1f0[iStack_144] * 2] - 0.5) * 114.0 * 2.0;
          auStack_2a0._8_4_ = 0;
          uStack_294 = 0x3f800000;
          auVar11 = _lqc2(_auStack_290);
          auVar10 = _lqc2(_auStack_2a0);
          auVar10 = _vsub(auVar10,auVar11);
          _auStack_2a0 = _sqc2(auVar10);
          FVector::__amu((101.0 - afStack_280[iVar3]) /
                            ((101.0 - afStack_280[iVar3]) + (afStack_280[iStack_144] - 101.0)),
                            auStack_2a0);
          auVar11 = _lqc2(_auStack_290);
          auVar10 = _lqc2(_auStack_2a0);
          auVar10 = _vadd(auVar10,auVar11);
          auVar10 = _sqc2(auVar10);
          this[(short)this[0x11] * 4 + 0x12] = auStack_290._0_4_;
          this[(short)this[0x11] * 4 + 0x13] = auStack_290._4_4_;
          auStack_2a0._0_4_ = auVar10._0_4_;
          this[(short)this[0x11] * 4 + 0x14] = auStack_2a0._0_4_;
          auStack_2a0._4_4_ = auVar10._4_4_;
          this[(short)this[0x11] * 4 + 0x15] = auStack_2a0._4_4_;
          this->i16_11 = (short)this[0x11] + 1;
        }
      }
      else {
        this[(short)this[0x11] * 4 + 0x12] =
             (int)((afStack_120[aiStack_1f0[iVar3] * 2] - 0.5) * 114.0 * 2.0);
        this[(short)this[0x11] * 4 + 0x13] =
             (int)((afStack_120[aiStack_1f0[iVar3] * 2 + 1] - 0.5) * 114.0 * 2.0);
        this[(short)this[0x11] * 4 + 0x14] =
             (int)((afStack_120[aiStack_1f0[iStack_144] * 2] - 0.5) * 114.0 * 2.0);
        this[(short)this[0x11] * 4 + 0x15] =
             (int)((afStack_120[aiStack_1f0[iStack_144] * 2 + 1] - 0.5) * 114.0 * 2.0);
        this->i16_11 = (short)this[0x11] + 1;
      }
    }
  }
  return;
}

// JP: 0x002f6e90  __ct__8CutJRingFP5JRingi  =  CutJRing::CutJRing
undefined8 CutJRing::CutJRing(undefined8 this,undefined4 param_2,undefined4 param_3)

{
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  puVar3 = (undefined4 *)this;
  puVar2 = puVar3 + 4;
  do {
    puVar2[4] = in_zero_lo;
    puVar2[5] = in_zero_hi;
    puVar2[6] = in_zero_udw;
    puVar2[7] = in_register_0000000c;
    puVar2 = puVar2 + 0x54;
  } while (puVar2 != puVar3 + 0xac);
  puVar3[0xb4] = in_zero_lo;
  puVar3[0xb5] = in_zero_hi;
  puVar3[0xb6] = in_zero_udw;
  puVar3[0xb7] = in_register_0000000c;
  *puVar3 = param_2;
  puVar3[0xac] = 0;
  puVar3[0xaf] = param_3;
  puVar3[0xb0] = 0;
  puVar3[0xb1] = 0x3f800000;
  puVar3[0xb2] = 0;
  puVar3[0xb4] = 0;
  puVar3[0xb5] = 0;
  puVar3[0xb6] = 0;
  puVar3[0xb7] = 0x3f800000;
  if (puVar3[0xaf] == 2) {
    puVar3[0xb2] = 0x3e19999a;
    iVar1 = rand();
    puVar3[0xb4] = ((float)iVar1 / 2.1474836e+09) * 16.0 - 8.0;
    iVar1 = rand();
    puVar3[0xb5] = ((float)iVar1 / 2.1474836e+09) * 16.0 - 8.0;
  }
  CutJRing::Initialize(this);
  return this;
}

// JP: 0x002f7030  __dt__8CutJRingFv  =  CutJRing::~CutJRing
int CutJRing::~CutJRing(int this,short param_2)

{
  if ((this != 0) && (0 < param_2)) {
    __dl(this);
  }
  return this;
}

// JP: 0x002f7090  Update__8CutJRingFf  =  CutJRing::Update
void CutJRing::Update(float this,int *param_2)

{
  int iVar1;
  
  param_2[0xb0] = (int)((float)param_2[0xb0] + this);
  if ((float)param_2[0xb2] != 0.0) {
    param_2[0xb2] = (int)((float)param_2[0xb2] - this);
    if ((float)param_2[0xb2] <= 0.0) {
      param_2[0xb2] = 0;
      param_2[0xb4] = 0;
      param_2[0xb5] = 0;
    }
    else if (0.1 <= (float)param_2[0xb2]) {
      iVar1 = rand();
      param_2[0xb4] = (int)(((float)iVar1 / 2.1474836e+09) * 16.0 - 8.0);
      iVar1 = rand();
      param_2[0xb5] = (int)(((float)iVar1 / 2.1474836e+09) * 16.0 - 8.0);
    }
    else {
      iVar1 = rand();
      param_2[0xb4] =
           (int)(((float)param_2[0xb2] / 0.1) * (((float)iVar1 / 2.1474836e+09) * 16.0 - 8.0));
      iVar1 = rand();
      param_2[0xb5] =
           (int)(((float)param_2[0xb2] / 0.1) * (((float)iVar1 / 2.1474836e+09) * 16.0 - 8.0));
    }
  }
  iVar1 = param_2[0xaf];
  if (iVar1 == 2) {
    if (0.33333334 <= (float)param_2[0xb0]) {
      for (iVar1 = 0; iVar1 < 2; iVar1 = iVar1 + 1) {
        param_2[iVar1 * 0x54 + 8] =
             (int)((float)param_2[iVar1 * 0x54 + 8] +
                  (float)param_2[0xad] * (float)param_2[iVar1 * 0x54 + 8] * this);
        param_2[iVar1 * 0x54 + 9] =
             (int)((float)param_2[iVar1 * 0x54 + 9] +
                  (float)param_2[0xad] * (float)param_2[iVar1 * 0x54 + 9] * this);
        param_2[iVar1 * 0x54 + 0xc] =
             (int)((float)param_2[iVar1 * 0x54 + 0xc] +
                  (float)param_2[0xae] * (float)param_2[iVar1 * 0x54 + 0xd] * this);
      }
      param_2[0xad] = (int)((float)param_2[0xad] - ((float)param_2[0xad] / 6.0) * this * 60.0);
      if ((float)param_2[0xad] < 0.0) {
        param_2[0xad] = 0;
      }
      param_2[0xae] = (int)((float)param_2[0xae] - this * 4.5);
      if ((float)param_2[0xae] < 0.0) {
        param_2[0xae] = 0;
      }
      param_2[0xac] = (int)((float)param_2[0xac] - this * 1.5 * *(float *)(*param_2 + 0xb8));
      if ((float)param_2[0xac] < 0.0) {
        param_2[0xac] = 0;
      }
    }
  }
  else if (iVar1 == 1) {
    if ((float)param_2[0xb0] < 0.15) {
      for (iVar1 = 0; iVar1 < 2; iVar1 = iVar1 + 1) {
        param_2[iVar1 * 0x54 + 8] =
             (int)((float)param_2[iVar1 * 0x54 + 8] +
                  (float)param_2[0xad] * (float)param_2[iVar1 * 0x54 + 8] * this);
        param_2[iVar1 * 0x54 + 9] =
             (int)((float)param_2[iVar1 * 0x54 + 9] +
                  (float)param_2[0xad] * (float)param_2[iVar1 * 0x54 + 9] * this);
        param_2[iVar1 * 0x54 + 0xc] =
             (int)((float)param_2[iVar1 * 0x54 + 0xc] +
                  (float)param_2[0xae] * (float)param_2[iVar1 * 0x54 + 0xd] * this);
      }
      param_2[0xad] = (int)((float)param_2[0xad] - ((float)param_2[0xad] / 6.0) * this * 60.0);
      if ((float)param_2[0xad] < 0.0) {
        param_2[0xad] = 0;
      }
      param_2[0xae] = (int)((float)param_2[0xae] - this * 4.5);
      if ((float)param_2[0xae] < 0.0) {
        param_2[0xae] = 0;
      }
      param_2[0xac] = (int)((float)param_2[0xac] - this * 1.5 * *(float *)(*param_2 + 0xb8));
      if ((float)param_2[0xac] < 0.0) {
        param_2[0xac] = 0;
      }
    }
    else {
      param_2[0xb1] = (int)((float)param_2[0xb1] + this * 60.0);
      for (iVar1 = 0; iVar1 < 2; iVar1 = iVar1 + 1) {
        param_2[iVar1 * 0x54 + 9] = (int)((float)param_2[iVar1 * 0x54 + 9] + (float)param_2[0xb1]);
        param_2[iVar1 * 0x54 + 0xc] =
             (int)((float)param_2[iVar1 * 0x54 + 0xc] +
                  (float)param_2[0xae] * (float)param_2[iVar1 * 0x54 + 0xd] * this);
      }
      param_2[0xad] = (int)((float)param_2[0xad] - ((float)param_2[0xad] / 6.0) * this * 60.0);
      if ((float)param_2[0xad] < 0.0) {
        param_2[0xad] = 0;
      }
      param_2[0xae] = (int)((float)param_2[0xae] - this * 4.5);
      if ((float)param_2[0xae] < 0.0) {
        param_2[0xae] = 0;
      }
      param_2[0xac] = (int)((float)param_2[0xac] - this * 1.5 * *(float *)(*param_2 + 0xb8));
      if ((float)param_2[0xac] < 0.0) {
        param_2[0xac] = 0;
      }
    }
  }
  else if (iVar1 == 0) {
    for (iVar1 = 0; iVar1 < 2; iVar1 = iVar1 + 1) {
      param_2[iVar1 * 0x54 + 8] =
           (int)((float)param_2[iVar1 * 0x54 + 8] +
                (float)param_2[0xad] * (float)param_2[iVar1 * 0x54 + 8] * this);
      param_2[iVar1 * 0x54 + 9] =
           (int)((float)param_2[iVar1 * 0x54 + 9] +
                (float)param_2[0xad] * (float)param_2[iVar1 * 0x54 + 9] * this);
      param_2[iVar1 * 0x54 + 0xc] =
           (int)((float)param_2[iVar1 * 0x54 + 0xc] +
                (float)param_2[0xae] * (float)param_2[iVar1 * 0x54 + 0xd] * this);
    }
    param_2[0xad] = (int)((float)param_2[0xad] - ((float)param_2[0xad] / 6.0) * this * 60.0);
    if ((float)param_2[0xad] < 0.0) {
      param_2[0xad] = 0;
    }
    param_2[0xae] = (int)((float)param_2[0xae] - this * 4.5);
    if ((float)param_2[0xae] < 0.0) {
      param_2[0xae] = 0;
    }
    param_2[0xac] = (int)((float)param_2[0xac] - this * 1.5 * *(float *)(*param_2 + 0xb8));
    if ((float)param_2[0xac] < 0.0) {
      param_2[0xac] = 0;
    }
  }
  return;
}

// JP: 0x002f7bf0  MakePacket__8CutJRingFP4_QWD  =  CutJRing::MakePacket
ulong * CutJRing::MakePacket(int *this,ulong *param_2)

{
  undefined1 auVar1 [16];
  undefined1 auVar2 [16];
  undefined1 auVar3 [16];
  undefined1 auVar4 [16];
  undefined1 auVar5 [16];
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  undefined1 auVar8 [16];
  undefined1 auVar9 [12];
  float in_zero_lo;
  float in_zero_hi;
  float in_zero_udw;
  float in_register_0000000c;
  int iVar10;
  int iVar11;
  int iVar12;
  ulong uVar13;
  long lVar14;
  undefined8 extraout_v0_udw;
  undefined8 extraout_v0_udw_00;
  undefined1 auVar15 [16];
  float *pfVar16;
  uint uVar17;
  float fVar18;
  float fVar19;
  undefined1 in_vf0 [16];
  undefined1 auVar20 [16];
  undefined1 auVar21 [16];
  undefined1 auVar22 [16];
  undefined4 uVar23;
  undefined1 auStack_530 [16];
  undefined1 auStack_520 [16];
  undefined1 auStack_510 [16];
  undefined1 auStack_500 [16];
  undefined1 auStack_4f0 [16];
  undefined1 auStack_4e0 [16];
  undefined4 uStack_4d0;
  undefined4 uStack_4cc;
  float fStack_4c8;
  undefined4 uStack_4c4;
  float fStack_4c0;
  float fStack_4bc;
  float fStack_4b8;
  float fStack_4b4;
  undefined1 auStack_4b0 [16];
  undefined4 uStack_4a0;
  undefined4 uStack_49c;
  undefined4 uStack_498;
  undefined4 uStack_494;
  undefined4 uStack_490;
  undefined4 uStack_48c;
  undefined4 uStack_488;
  undefined4 uStack_484;
  undefined4 uStack_480;
  undefined4 uStack_47c;
  undefined4 uStack_478;
  undefined4 uStack_474;
  undefined4 uStack_470;
  undefined4 uStack_46c;
  undefined4 uStack_468;
  undefined4 uStack_464;
  undefined4 uStack_460;
  undefined4 uStack_45c;
  undefined4 uStack_458;
  undefined4 uStack_454;
  float fStack_450;
  float fStack_44c;
  undefined4 uStack_448;
  undefined4 uStack_444;
  float fStack_440;
  float fStack_43c;
  undefined4 uStack_438;
  undefined4 uStack_434;
  float fStack_430;
  float fStack_42c;
  undefined4 uStack_428;
  undefined4 uStack_424;
  float fStack_420;
  float fStack_41c;
  undefined4 uStack_418;
  undefined4 uStack_414;
  float fStack_410;
  float fStack_40c;
  undefined4 uStack_408;
  undefined4 uStack_404;
  int aiStack_400 [72];
  float afStack_2e0 [75];
  undefined4 uStack_1b4;
  undefined1 auStack_1b0 [16];
  undefined1 auStack_1a0 [16];
  undefined1 auStack_190 [16];
  undefined1 auStack_180 [16];
  undefined1 auStack_170 [4];
  float afStack_16c [3];
  undefined1 auStack_160 [16];
  undefined1 auStack_150 [16];
  undefined1 auStack_140 [16];
  undefined1 auStack_130 [16];
  undefined1 auStack_120 [12];
  undefined4 uStack_114;
  undefined4 uStack_110;
  undefined4 uStack_10c;
  undefined4 uStack_108;
  undefined4 uStack_104;
  undefined4 uStack_100;
  undefined4 uStack_fc;
  undefined4 uStack_f8;
  undefined4 uStack_f4;
  float afStack_50 [8];
  float fStack_30;
  float fStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  float fStack_20;
  float fStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  float fStack_c;
  float fStack_8;
  float fStack_4;
  
  iVar10 = (uint)*(ushort *)((int)this + 0x12) + (uint)*(ushort *)((int)this + 0x162);
  if ((this[0xaf] == 2) && ((float)this[0xb0] < 0.3)) {
    iVar10 = iVar10 + 0x1b;
  }
  pfVar16 = (float *)auStack_170;
  do {
    *pfVar16 = in_zero_lo;
    pfVar16[1] = in_zero_hi;
    pfVar16[2] = in_zero_udw;
    pfVar16[3] = in_register_0000000c;
    pfVar16 = pfVar16 + 4;
  } while (pfVar16 != afStack_50);
  auVar20 = _vmr32(in_vf0);
  auVar21 = _vmr32(auVar20);
  auVar22 = _vmr32(auVar21);
  _sqc2(in_vf0);
  _sqc2(auVar20);
  _sqc2(auVar21);
  _sqc2(auVar22);
  pfVar16 = afStack_2e0;
  do {
    *pfVar16 = in_zero_lo;
    pfVar16[1] = in_zero_hi;
    pfVar16[2] = in_zero_udw;
    pfVar16[3] = in_register_0000000c;
    pfVar16 = pfVar16 + 4;
  } while (pfVar16 != afStack_2e0 + 0x48);
  fVar18 = (float)(1 << (uint)(((ulong)*(byte *)((&JRing::JRTex)[*(int *)(*this + 0xe8)] + 0x53)
                               << 0x3a) >> 0x3c)) * 16.0;
  fVar19 = (float)(1 << (uint)((ulong)(*(long *)((&JRing::JRTex)[*(int *)(*this + 0xe8)] + 0x50)
                                      << 0x1e) >> 0x3c)) * 16.0;
  if ((float)this[0xac] != 0.0) {
    *(undefined **)param_2 = &DAT_10000002 + iVar10;
    *(undefined4 *)((int)param_2 + 4) = 0;
    param_2->u32_1 = 0;
    *(int *)((int)param_2 + 0xc) = iVar10 + 0x50000002;
    param_2[2] = 0x1000000000000001;
    param_2[3] = 0xe;
    param_2[4] = 0x44;
    param_2[5] = 0x42;
    param_2 = param_2 + 6;
    fStack_40c = (float)this[9] * *(float *)(*this + 0x84);
    fStack_410 = (float)this[8] * *(float *)(*this + 0x84);
    uStack_408 = 0;
    uStack_404 = 0x3f800000;
    uStack_28 = 0;
    uStack_24 = 0x3f800000;
    fStack_41c = (float)this[0x5d] * *(float *)(*this + 0x84);
    fStack_420 = (float)this[0x5c] * *(float *)(*this + 0x84);
    uStack_418 = 0;
    uStack_414 = 0x3f800000;
    uStack_18 = 0;
    uStack_14 = 0x3f800000;
    auVar20 = _vmr32(in_vf0);
    auVar21 = _vmr32(auVar20);
    auVar22 = _vmr32(auVar21);
    auStack_180 = _sqc2(in_vf0);
    auStack_190 = _sqc2(auVar20);
    auStack_1a0 = _sqc2(auVar21);
    auStack_1b0 = _sqc2(auVar22);
    fStack_30 = fStack_410;
    fStack_2c = fStack_40c;
    fStack_20 = fStack_420;
    fStack_1c = fStack_41c;
    sceVu0RotMatrixZ(*(undefined4 *)(*this + 0x78),auStack_1b0,auStack_1b0);
    sceVu0RotMatrixX(*(undefined4 *)(*this + 0x70),auStack_1b0,auStack_1b0);
    sceVu0RotMatrixY(*(undefined4 *)(*this + 0x74),auStack_1b0,auStack_1b0);
    RotTransVector(afStack_50,&fStack_30,auStack_1b0,2);
    for (iVar10 = 0; iVar10 < 2; iVar10 = iVar10 + 1) {
      iVar12 = *this;
      afStack_2e0[0x48] = iVar12->f32_70;
      afStack_2e0[0x49] = iVar12->f32_74;
      uStack_1b4 = iVar12->u32_7c;
      afStack_2e0[0x4a] = iVar12->f32_78 + (float)this[iVar10 * 0x54 + 0xc];
      auVar20 = _vmr32(in_vf0);
      auVar21 = _vmr32(auVar20);
      auVar22 = _vmr32(auVar21);
      auStack_180 = _sqc2(in_vf0);
      auStack_190 = _sqc2(auVar20);
      auStack_1a0 = _sqc2(auVar21);
      auStack_1b0 = _sqc2(auVar22);
      sceVu0RotMatrixZ(afStack_2e0[0x4a],auStack_1b0,auStack_1b0);
      sceVu0RotMatrixX(afStack_2e0[0x48],auStack_1b0,auStack_1b0);
      sceVu0RotMatrixY(afStack_2e0[0x49],auStack_1b0,auStack_1b0);
      for (iVar12 = 0; iVar12 < 0x12; iVar12 = iVar12 + 1) {
        fStack_42c = (float)this[iVar10 * 0x54 + iVar12 * 4 + 0xf] * *(float *)(*this + 0x84);
        fStack_430 = (float)this[iVar10 * 0x54 + iVar12 * 4 + 0xe] * *(float *)(*this + 0x84);
        uStack_428 = 0;
        uStack_424 = 0x3f800000;
        iVar11 = iVar12 * 0x10;
        *(float *)(auStack_170 + iVar11) = fStack_430;
        *(float *)(auStack_170 + iVar11 + 4) = fStack_42c;
        *(undefined4 *)(auStack_170 + iVar11 + 8) = 0;
        *(undefined4 *)(auStack_170 + iVar11 + 0xc) = 0x3f800000;
      }
      RotTransVector(afStack_2e0,auStack_170,auStack_1b0,0x12);
      for (iVar12 = 0; iVar12 < 0x12; iVar12 = iVar12 + 1) {
        auVar21 = _lqc2(*(undefined1 (*) [16])(afStack_50 + iVar10 * 4));
        auVar20 = _lqc2(*(undefined1 (*) [16])(afStack_2e0 + iVar12 * 4));
        auVar20 = _vadd(auVar20,auVar21);
        auVar20 = _sqc2(auVar20);
        *(undefined1 (*) [16])(afStack_2e0 + iVar12 * 4) = auVar20;
      }
      sceVu0RotTransPersN(aiStack_400,*this + 0x590,afStack_2e0,0x12,0);
      for (iVar12 = 0; iVar12 < 0x12; iVar12 = iVar12 + 1) {
        aiStack_400[iVar12 * 4] =
             (int)((float)aiStack_400[iVar12 * 4] +
                  ((*(float *)(*this + 0x68) + (float)this[0xb4]) - 256.0) * 16.0);
        aiStack_400[iVar12 * 4 + 1] =
             (int)((float)aiStack_400[iVar12 * 4 + 1] +
                  ((*(float *)(*this + 0x6c) + (float)this[0xb5]) - 224.0) * 16.0);
        aiStack_400[iVar12 * 4 + 2] = (int)((float)aiStack_400[iVar12 * 4 + 2] / 16.0);
      }
      auVar21._8_8_ = extraout_v0_udw;
      auVar21._0_8_ = 0x8400000000000001;
      auVar20._4_4_ = in_zero_hi;
      auVar20._0_4_ = in_zero_lo;
      auVar20._8_4_ = in_zero_udw;
      auVar20._12_4_ = in_register_0000000c;
      auVar20 = _pcpyld(auVar20,auVar21);
      *param_2 = auVar20._0_8_;
      param_2[1] = 0xc12c1206;
      uVar13 = JRCTex::GetTex0((&JRing::JRTex)[*(int *)(*this + 0xe8)],1);
      param_2[2] = uVar13;
      param_2[3] = 0x5d;
      fStack_4 = 16.0 / (float)aiStack_400[3];
      fStack_8 = fStack_4 * ((float)this[iVar10 * 0x54 + 0x10] / fVar18);
      fStack_c = fStack_4 * ((float)this[iVar10 * 0x54 + 0x11] / fVar19);
      param_2[4] = CONCAT44(fStack_c,fStack_8);
      lVar14 = __fixunssfdi((float)this[0xac] * 128.0);
      param_2[5] = lVar14 << 0x18 | 0x808080U | (ulong)(uint)fStack_4 << 0x20;
      param_2[6] = (long)aiStack_400[2] << 0x20 |
                   (long)aiStack_400[0] | (long)aiStack_400[1] << 0x10;
      fStack_4 = 16.0 / (float)aiStack_400[7];
      fStack_8 = fStack_4 * ((float)this[iVar10 * 0x54 + 0x14] / fVar18);
      fStack_c = fStack_4 * ((float)this[iVar10 * 0x54 + 0x15] / fVar19);
      param_2[7] = CONCAT44(fStack_c,fStack_8);
      lVar14 = __fixunssfdi((float)this[0xac] * 128.0);
      param_2[8] = lVar14 << 0x18 | 0x808080U | (ulong)(uint)fStack_4 << 0x20;
      param_2[9] = (long)aiStack_400[6] << 0x20 |
                   (long)aiStack_400[4] | (long)aiStack_400[5] << 0x10;
      if ((iVar10 == 0) || ((this[0xaf] == 2 && ((float)this[0xb0] < 0.3)))) {
        param_2[10] = 0x3400000000000010;
      }
      else {
        param_2[10] = 0x3400000000008010;
      }
      param_2[0xb] = 0x412;
      param_2 = param_2 + 0xc;
      for (uVar17 = 2; (int)uVar17 < 0x12; uVar17 = uVar17 + 1) {
        fStack_4 = 16.0 / (float)aiStack_400[uVar17 * 4 + 3];
        fStack_8 = fStack_4 * ((float)this[iVar10 * 0x54 + uVar17 * 4 + 0x10] / fVar18);
        fStack_c = fStack_4 * ((float)this[iVar10 * 0x54 + uVar17 * 4 + 0x11] / fVar19);
        if ((uVar17 & 1) == 0) {
          *param_2 = CONCAT44(fStack_c,fStack_8);
          lVar14 = __fixunssfdi((float)this[0xac] * 128.0);
          param_2[1] = lVar14 << 0x18 | 0x808080U | (ulong)(uint)fStack_4 << 0x20;
          param_2 = param_2 + 2;
          *param_2 = (long)aiStack_400[uVar17 * 4 + 2] << 0x20 |
                     (long)aiStack_400[uVar17 * 4] | (long)aiStack_400[uVar17 * 4 + 1] << 0x10;
        }
        else {
          param_2[1] = CONCAT44(fStack_c,fStack_8);
          lVar14 = __fixunssfdi((float)this[0xac] * 128.0);
          param_2[2] = lVar14 << 0x18 | 0x808080U | (ulong)(uint)fStack_4 << 0x20;
          param_2[3] = (long)aiStack_400[uVar17 * 4 + 2] << 0x20 |
                       (long)aiStack_400[uVar17 * 4] | (long)aiStack_400[uVar17 * 4 + 1] << 0x10;
          param_2 = param_2 + 4;
        }
      }
    }
    if ((this[0xaf] == 2) && ((float)this[0xb0] < 0.3)) {
      *param_2 = 0x1000000000000001;
      param_2[1] = 0xe;
      param_2[2] = 0x48;
      param_2[3] = 0x42;
      iVar10 = *this;
      afStack_2e0[0x48] = iVar10->f32_70;
      afStack_2e0[0x49] = iVar10->f32_74;
      afStack_2e0[0x4a] = iVar10->f32_78;
      uStack_1b4 = iVar10->u32_7c;
      fStack_43c = (float)this[0xb9] * *(float *)(*this + 0x84);
      fStack_440 = (float)this[0xb8] * *(float *)(*this + 0x84);
      uStack_438 = 0;
      uStack_434 = 0x3f800000;
      afStack_16c[0] = fStack_43c;
      auStack_170 = (undefined1  [4])fStack_440;
      afStack_16c[1] = 0.0;
      afStack_16c[2] = 1.0;
      fStack_44c = (float)this[0xbb] * *(float *)(*this + 0x84);
      fStack_450 = (float)this[0xba] * *(float *)(*this + 0x84);
      uStack_448 = 0;
      uStack_444 = 0x3f800000;
      auStack_120._4_4_ = fStack_44c;
      auStack_120._0_4_ = fStack_450;
      auStack_120._8_4_ = 0;
      uStack_114 = 0x3f800000;
      if ((float)this[0xb0] < 0.15) {
        auVar21 = _lqc2(_auStack_170);
        auVar20 = _lqc2(_auStack_120);
        auVar20 = _vsub(auVar20,auVar21);
        _auStack_120 = _sqc2(auVar20);
        FVector::__amu((float)this[0xb0] / 0.15,auStack_120);
        auVar21 = _lqc2(_auStack_170);
        auVar20 = _lqc2(_auStack_120);
        auVar20 = _vadd(auVar20,auVar21);
        _auStack_120 = _sqc2(auVar20);
      }
      else {
        auVar21 = _lqc2(_auStack_120);
        auVar20 = _lqc2(_auStack_170);
        auVar20 = _vsub(auVar20,auVar21);
        _auStack_170 = _sqc2(auVar20);
        FVector::__amu((0.3 - (float)this[0xb0]) / 0.15,auStack_170);
        auVar21 = _lqc2(_auStack_120);
        auVar20 = _lqc2(_auStack_170);
        auVar20 = _vadd(auVar20,auVar21);
        _auStack_170 = _sqc2(auVar20);
      }
      auVar20 = _lqc2(_auStack_120);
      auVar21 = _lqc2(_auStack_170);
      auVar20 = _vsub(auVar20,auVar21);
      auStack_4e0 = _sqc2(auVar20);
      FVector::FVector(&uStack_460,auStack_4e0);
      uStack_110 = uStack_460;
      uStack_10c = uStack_45c;
      uStack_108 = uStack_458;
      uStack_104 = uStack_454;
      auVar20 = _qmtc2(0x40400000);
      _vdiv(in_vf0,0,auVar20,0);
      auVar22._4_4_ = uStack_45c;
      auVar22._0_4_ = uStack_460;
      auVar22._8_4_ = uStack_458;
      auVar22._12_4_ = uStack_454;
      auVar20 = _lqc2(auVar22);
      uVar23 = _vwaitq();
      auVar20 = _vmulq(auVar20,uVar23);
      auStack_4f0 = _sqc2(auVar20);
      FVector::FVector(&uStack_470,auStack_4f0);
      uStack_100 = uStack_470;
      uStack_fc = uStack_46c;
      uStack_f8 = uStack_468;
      uStack_f4 = uStack_464;
      auVar20 = _lqc2(_auStack_170);
      auVar3._4_4_ = uStack_46c;
      auVar3._0_4_ = uStack_470;
      auVar3._8_4_ = uStack_468;
      auVar3._12_4_ = uStack_464;
      auVar21 = _lqc2(auVar3);
      auVar20 = _vadd(auVar20,auVar21);
      auStack_500 = _sqc2(auVar20);
      FVector::FVector(&uStack_480,auStack_500);
      auStack_150._4_4_ = uStack_47c;
      auStack_150._0_4_ = uStack_480;
      auStack_150._8_4_ = uStack_478;
      auStack_150._12_4_ = uStack_474;
      auStack_160._8_4_ = uStack_478;
      auStack_160._0_8_ = auStack_150._0_8_;
      auStack_160._12_4_ = uStack_474;
      auVar20 = _lqc2(_auStack_120);
      auVar4._4_4_ = uStack_fc;
      auVar4._0_4_ = uStack_100;
      auVar4._8_4_ = uStack_f8;
      auVar4._12_4_ = uStack_f4;
      auVar21 = _lqc2(auVar4);
      auVar20 = _vsub(auVar20,auVar21);
      auStack_510 = _sqc2(auVar20);
      FVector::FVector(&uStack_490,auStack_510);
      auStack_130._4_4_ = uStack_48c;
      auStack_130._0_4_ = uStack_490;
      auStack_130._8_4_ = uStack_488;
      auStack_130._12_4_ = uStack_484;
      auStack_140._8_4_ = uStack_488;
      auStack_140._0_8_ = auStack_130._0_8_;
      auStack_140._12_4_ = uStack_484;
      FVector::Normalize(&uStack_110);
      auVar20 = _vmr32(in_vf0);
      auVar21 = _vmr32(auVar20);
      auVar22 = _vmr32(auVar21);
      auStack_180 = _sqc2(in_vf0);
      auStack_190 = _sqc2(auVar20);
      auStack_1a0 = _sqc2(auVar21);
      auStack_1b0 = _sqc2(auVar22);
      sceVu0RotMatrixZ(0x3fc90fdb,auStack_1b0,auStack_1b0);
      Matrix::ApplyMatrix(auStack_4b0,auStack_1b0,&uStack_110);
      auVar20 = _lqc2(auStack_4b0);
      auVar21 = _qmtc2(0x40400000);
      auVar20 = _vmulbc(auVar20,auVar21);
      auStack_520 = _sqc2(auVar20);
      FVector::FVector(&uStack_4a0,auStack_520);
      uStack_100 = uStack_4a0;
      uStack_fc = uStack_49c;
      uStack_f8 = uStack_498;
      uStack_f4 = uStack_494;
      auVar5._4_4_ = uStack_49c;
      auVar5._0_4_ = uStack_4a0;
      auVar5._8_4_ = uStack_498;
      auVar5._12_4_ = uStack_494;
      auVar21 = _lqc2(auVar5);
      auVar20 = _lqc2(auStack_160);
      auVar20 = _vsub(auVar20,auVar21);
      auStack_160 = _sqc2(auVar20);
      auVar6._4_4_ = uStack_49c;
      auVar6._0_4_ = uStack_4a0;
      auVar6._8_4_ = uStack_498;
      auVar6._12_4_ = uStack_494;
      auVar21 = _lqc2(auVar6);
      auVar20 = _lqc2(auStack_150);
      auVar20 = _vadd(auVar20,auVar21);
      auStack_150 = _sqc2(auVar20);
      auVar7._4_4_ = uStack_49c;
      auVar7._0_4_ = uStack_4a0;
      auVar7._8_4_ = uStack_498;
      auVar7._12_4_ = uStack_494;
      auVar21 = _lqc2(auVar7);
      auVar20 = _lqc2(auStack_140);
      auVar20 = _vsub(auVar20,auVar21);
      auStack_140 = _sqc2(auVar20);
      auVar8._4_4_ = uStack_49c;
      auVar8._0_4_ = uStack_4a0;
      auVar8._8_4_ = uStack_498;
      auVar8._12_4_ = uStack_494;
      auVar21 = _lqc2(auVar8);
      auVar20 = _lqc2(auStack_130);
      auVar20 = _vadd(auVar20,auVar21);
      auStack_130 = _sqc2(auVar20);
      auVar20 = _vmr32(in_vf0);
      auVar21 = _vmr32(auVar20);
      auVar22 = _vmr32(auVar21);
      auStack_180 = _sqc2(in_vf0);
      auStack_190 = _sqc2(auVar20);
      auStack_1a0 = _sqc2(auVar21);
      auStack_1b0 = _sqc2(auVar22);
      sceVu0RotMatrixZ(afStack_2e0[0x4a],auStack_1b0,auStack_1b0);
      sceVu0RotMatrixX(afStack_2e0[0x48],auStack_1b0,auStack_1b0);
      sceVu0RotMatrixY(afStack_2e0[0x49],auStack_1b0,auStack_1b0);
      RotTransVector(afStack_2e0,auStack_170,auStack_1b0,6);
      for (iVar10 = 0; iVar10 < 6; iVar10 = iVar10 + 1) {
        fStack_4c8 = (-512.0 - afStack_2e0[iVar10 * 4 + 2]) - 50.0;
        uStack_4d0 = 0;
        uStack_4cc = 0;
        uStack_4c4 = 0x3f800000;
        auVar20 = _lqc2(*(undefined1 (*) [16])(afStack_2e0 + iVar10 * 4));
        auVar9._4_8_ = 0;
        auVar9._0_4_ = fStack_4c8;
        auVar2._12_4_ = 0x3f800000;
        auVar2._0_12_ = auVar9 << 0x40;
        auVar21 = _lqc2(auVar2);
        auVar20 = _vadd(auVar20,auVar21);
        auStack_530 = _sqc2(auVar20);
        FVector::FVector(&fStack_4c0,auStack_530);
        iVar12 = iVar10 + 6;
        afStack_2e0[iVar12 * 4] = fStack_4c0;
        afStack_2e0[iVar12 * 4 + 1] = fStack_4bc;
        afStack_2e0[iVar12 * 4 + 2] = fStack_4b8;
        afStack_2e0[iVar12 * 4 + 3] = fStack_4b4;
      }
      sceVu0RotTransPersN(aiStack_400,*this + 0x590,afStack_2e0,0xc,0);
      for (iVar10 = 0; iVar10 < 0xc; iVar10 = iVar10 + 1) {
        aiStack_400[iVar10 * 4] =
             (int)((float)aiStack_400[iVar10 * 4] +
                  ((*(float *)(*this + 0x68) + (float)this[0xb4]) - 256.0) * 16.0);
        aiStack_400[iVar10 * 4 + 1] =
             (int)((float)aiStack_400[iVar10 * 4 + 1] +
                  ((*(float *)(*this + 0x6c) + (float)this[0xb5]) - 224.0) * 16.0);
        aiStack_400[iVar10 * 4 + 2] = (int)((float)aiStack_400[iVar10 * 4 + 2] / 16.0);
      }
      auVar15._8_8_ = extraout_v0_udw_00;
      auVar15._0_8_ = 0xe400000000000001;
      auVar1._4_4_ = in_zero_hi;
      auVar1._0_4_ = in_zero_lo;
      auVar1._8_4_ = in_zero_udw;
      auVar1._12_4_ = in_register_0000000c;
      auVar20 = _pcpyld(auVar1,auVar15);
      param_2[4] = auVar20._0_8_;
      param_2[5] = 0x41414141c1c1f0;
      param_2[6] = 0x4c;
      param_2[7] = 0;
      fStack_4 = 16.0 / (float)aiStack_400[3];
      lVar14 = __fixunssfdi((float)this[0xac] * 128.0);
      param_2[8] = lVar14 << 0x18 | 0xffffffU | (ulong)(uint)fStack_4 << 0x20;
      iVar10 = aiStack_400[2];
      if (aiStack_400[2] < 0) {
        iVar10 = aiStack_400[2] + 0xf;
      }
      param_2[9] = (long)(iVar10 >> 4) << 0x20 | (long)aiStack_400[0] | (long)aiStack_400[1] << 0x10
      ;
      fStack_4 = 16.0 / (float)aiStack_400[7];
      lVar14 = __fixunssfdi((float)this[0xac] * 128.0);
      param_2[10] = lVar14 << 0x18 | 0xffffffU | (ulong)(uint)fStack_4 << 0x20;
      iVar10 = aiStack_400[6];
      if (aiStack_400[6] < 0) {
        iVar10 = aiStack_400[6] + 0xf;
      }
      param_2[0xb] = (long)(iVar10 >> 4) << 0x20 |
                     (long)aiStack_400[4] | (long)aiStack_400[5] << 0x10;
      fStack_4 = 16.0 / (float)aiStack_400[0xb];
      lVar14 = __fixunssfdi((float)this[0xac] * 128.0);
      param_2[0xc] = lVar14 << 0x18 | 0xffffffU | (ulong)(uint)fStack_4 << 0x20;
      iVar10 = aiStack_400[10];
      if (aiStack_400[10] < 0) {
        iVar10 = aiStack_400[10] + 0xf;
      }
      param_2[0xd] = (long)(iVar10 >> 4) << 0x20 |
                     (long)aiStack_400[8] | (long)aiStack_400[9] << 0x10;
      fStack_4 = 16.0 / (float)aiStack_400[0xf];
      lVar14 = __fixunssfdi((float)this[0xac] * 128.0);
      param_2[0xe] = lVar14 << 0x18 | 0xffffffU | (ulong)(uint)fStack_4 << 0x20;
      iVar10 = aiStack_400[0xe];
      if (aiStack_400[0xe] < 0) {
        iVar10 = aiStack_400[0xe] + 0xf;
      }
      param_2[0xf] = (long)(iVar10 >> 4) << 0x20 |
                     (long)aiStack_400[0xc] | (long)aiStack_400[0xd] << 0x10;
      fStack_4 = 16.0 / (float)aiStack_400[0x13];
      lVar14 = __fixunssfdi((float)this[0xac] * 128.0);
      param_2[0x10] = lVar14 << 0x18 | 0xffffffU | (ulong)(uint)fStack_4 << 0x20;
      iVar10 = aiStack_400[0x12];
      if (aiStack_400[0x12] < 0) {
        iVar10 = aiStack_400[0x12] + 0xf;
      }
      param_2[0x11] =
           (long)(iVar10 >> 4) << 0x20 | (long)aiStack_400[0x10] | (long)aiStack_400[0x11] << 0x10;
      fStack_4 = 16.0 / (float)aiStack_400[0x17];
      lVar14 = __fixunssfdi((float)this[0xac] * 128.0);
      param_2[0x12] = lVar14 << 0x18 | 0xffffffU | (ulong)(uint)fStack_4 << 0x20;
      iVar10 = aiStack_400[0x16];
      if (aiStack_400[0x16] < 0) {
        iVar10 = aiStack_400[0x16] + 0xf;
      }
      param_2[0x13] =
           (long)(iVar10 >> 4) << 0x20 | (long)aiStack_400[0x14] | (long)aiStack_400[0x15] << 0x10;
      param_2[0x14] = 0x6400000000000001;
      param_2[0x15] = 0xc1c1f0;
      param_2[0x16] = 0x4c;
      param_2[0x17] = 0;
      param_2[0x18] = (ulong)(uint)(16.0 / (float)aiStack_400[0x1b]) << 0x20 | 0xffffff;
      iVar10 = aiStack_400[0x1a];
      if (aiStack_400[0x1a] < 0) {
        iVar10 = aiStack_400[0x1a] + 0xf;
      }
      param_2[0x19] =
           (long)(iVar10 >> 4) << 0x20 | (long)aiStack_400[0x18] | (long)aiStack_400[0x19] << 0x10;
      fStack_4 = 16.0 / (float)aiStack_400[3];
      lVar14 = __fixunssfdi((float)this[0xac] * 64.0);
      param_2[0x1a] = lVar14 << 0x18 | 0xffffffU | (ulong)(uint)fStack_4 << 0x20;
      iVar10 = aiStack_400[2];
      if (aiStack_400[2] < 0) {
        iVar10 = aiStack_400[2] + 0xf;
      }
      param_2[0x1b] =
           (long)(iVar10 >> 4) << 0x20 | (long)aiStack_400[0] | (long)aiStack_400[1] << 0x10;
      param_2[0x1c] = 0x4400000000008006;
      param_2[0x1d] = 0x4141;
      param_2[0x1e] = (ulong)(uint)(16.0 / (float)aiStack_400[0x1f]) << 0x20 | 0xffffff;
      if (aiStack_400[0x1e] < 0) {
        aiStack_400[0x1e] = aiStack_400[0x1e] + 0xf;
      }
      param_2[0x1f] =
           (long)(aiStack_400[0x1e] >> 4) << 0x20 |
           (long)aiStack_400[0x1c] | (long)aiStack_400[0x1d] << 0x10;
      fStack_4 = 16.0 / (float)aiStack_400[7];
      lVar14 = __fixunssfdi((float)this[0xac] * 64.0);
      param_2[0x20] = lVar14 << 0x18 | 0xffffffU | (ulong)(uint)fStack_4 << 0x20;
      if (aiStack_400[6] < 0) {
        aiStack_400[6] = aiStack_400[6] + 0xf;
      }
      param_2[0x21] =
           (long)(aiStack_400[6] >> 4) << 0x20 | (long)aiStack_400[4] | (long)aiStack_400[5] << 0x10
      ;
      param_2[0x22] = (ulong)(uint)(16.0 / (float)aiStack_400[0x27]) << 0x20 | 0xffffff;
      if (aiStack_400[0x26] < 0) {
        aiStack_400[0x26] = aiStack_400[0x26] + 0xf;
      }
      param_2[0x23] =
           (long)(aiStack_400[0x26] >> 4) << 0x20 |
           (long)aiStack_400[0x24] | (long)aiStack_400[0x25] << 0x10;
      fStack_4 = 16.0 / (float)aiStack_400[0xf];
      lVar14 = __fixunssfdi((float)this[0xac] * 64.0);
      param_2[0x24] = lVar14 << 0x18 | 0xffffffU | (ulong)(uint)fStack_4 << 0x20;
      if (aiStack_400[0xe] < 0) {
        aiStack_400[0xe] = aiStack_400[0xe] + 0xf;
      }
      param_2[0x25] =
           (long)(aiStack_400[0xe] >> 4) << 0x20 |
           (long)aiStack_400[0xc] | (long)aiStack_400[0xd] << 0x10;
      param_2[0x26] = (ulong)(uint)(16.0 / (float)aiStack_400[0x2f]) << 0x20 | 0xffffff;
      if (aiStack_400[0x2e] < 0) {
        aiStack_400[0x2e] = aiStack_400[0x2e] + 0xf;
      }
      param_2[0x27] =
           (long)(aiStack_400[0x2e] >> 4) << 0x20 |
           (long)aiStack_400[0x2c] | (long)aiStack_400[0x2d] << 0x10;
      fStack_4 = 16.0 / (float)aiStack_400[0x17];
      lVar14 = __fixunssfdi((float)this[0xac] * 64.0);
      param_2[0x28] = lVar14 << 0x18 | 0xffffffU | (ulong)(uint)fStack_4 << 0x20;
      if (aiStack_400[0x16] < 0) {
        aiStack_400[0x16] = aiStack_400[0x16] + 0xf;
      }
      param_2[0x29] =
           (long)(aiStack_400[0x16] >> 4) << 0x20 |
           (long)aiStack_400[0x14] | (long)aiStack_400[0x15] << 0x10;
      param_2[0x2a] = (ulong)(uint)(16.0 / (float)aiStack_400[0x2b]) << 0x20 | 0xffffff;
      if (aiStack_400[0x2a] < 0) {
        aiStack_400[0x2a] = aiStack_400[0x2a] + 0xf;
      }
      param_2[0x2b] =
           (long)(aiStack_400[0x2a] >> 4) << 0x20 |
           (long)aiStack_400[0x28] | (long)aiStack_400[0x29] << 0x10;
      fStack_4 = 16.0 / (float)aiStack_400[0x13];
      lVar14 = __fixunssfdi((float)this[0xac] * 64.0);
      param_2[0x2c] = lVar14 << 0x18 | 0xffffffU | (ulong)(uint)fStack_4 << 0x20;
      if (aiStack_400[0x12] < 0) {
        aiStack_400[0x12] = aiStack_400[0x12] + 0xf;
      }
      param_2[0x2d] =
           (long)(aiStack_400[0x12] >> 4) << 0x20 |
           (long)aiStack_400[0x10] | (long)aiStack_400[0x11] << 0x10;
      param_2[0x2e] = (ulong)(uint)(16.0 / (float)aiStack_400[0x23]) << 0x20 | 0xffffff;
      if (aiStack_400[0x22] < 0) {
        aiStack_400[0x22] = aiStack_400[0x22] + 0xf;
      }
      param_2[0x2f] =
           (long)(aiStack_400[0x22] >> 4) << 0x20 |
           (long)aiStack_400[0x20] | (long)aiStack_400[0x21] << 0x10;
      fStack_4 = 16.0 / (float)aiStack_400[0xb];
      lVar14 = __fixunssfdi((float)this[0xac] * 64.0);
      param_2[0x30] = lVar14 << 0x18 | 0xffffffU | (ulong)(uint)fStack_4 << 0x20;
      if (aiStack_400[10] < 0) {
        aiStack_400[10] = aiStack_400[10] + 0xf;
      }
      param_2[0x31] =
           (long)(aiStack_400[10] >> 4) << 0x20 |
           (long)aiStack_400[8] | (long)aiStack_400[9] << 0x10;
      param_2[0x32] = (ulong)(uint)(16.0 / (float)aiStack_400[0x1b]) << 0x20 | 0xffffff;
      if (aiStack_400[0x1a] < 0) {
        aiStack_400[0x1a] = aiStack_400[0x1a] + 0xf;
      }
      param_2[0x33] =
           (long)(aiStack_400[0x1a] >> 4) << 0x20 |
           (long)aiStack_400[0x18] | (long)aiStack_400[0x19] << 0x10;
      fStack_4 = 16.0 / (float)aiStack_400[3];
      lVar14 = __fixunssfdi((float)this[0xac] * 64.0);
      param_2[0x34] = lVar14 << 0x18 | 0xffffffU | (ulong)(uint)fStack_4 << 0x20;
      if (aiStack_400[2] < 0) {
        aiStack_400[2] = aiStack_400[2] + 0xf;
      }
      param_2[0x35] =
           (long)(aiStack_400[2] >> 4) << 0x20 | (long)aiStack_400[0] | (long)aiStack_400[1] << 0x10
      ;
      param_2 = param_2 + 0x36;
    }
  }
  return param_2;
}

// JP: 0x002f9c30  GetPacketCnt__8CutJRingFv  =  CutJRing::GetPacketCnt
int CutJRing::GetPacketCnt(int this)

{
  int iVar1;
  
  iVar1 = this->u16_12 + 3 + (uint)this->u16_162;
  if (this->i32_2bc == 2) {
    iVar1 = iVar1 + 0x1b;
  }
  return iVar1;
}

// JP: 0x002f9c90  Initialize__8CutJRingFv  =  CutJRing::Initialize
void CutJRing::Initialize(int *this)

{
  int iVar1;
  float fVar2;
  float fVar3;
  float __x;
  
  iVar1 = rand();
  __x = ((float)iVar1 / 2.1474836e+09) * 6.2831855;
  this[0xac] = *(int *)(*this + 0xb8);
  this[0xad] = 0x41000000;
  this[0xae] = 0x40400000;
  this->u16_4 = 0;
  *(undefined2 *)((int)this + 0x12) = 0x1e;
  fVar2 = sinf(__x + 1.5707964);
  fVar3 = cosf(__x + 1.5707964);
  this[8] = (int)((fVar3 * 114.0) / 2.0);
  this[9] = (int)((-fVar2 * 114.0) / 2.0);
  this[10] = 0;
  this[0xb] = 0;
  this[0xc] = 0;
  this[0xd] = 0x3e8efa36;
  this[0xe] = (int)-(float)this[8];
  this[0xf] = (int)-(float)this[9];
  this[0x10] = 0x45000000;
  this[0x11] = 0x45000000;
  fVar2 = __x;
  for (iVar1 = 1; iVar1 < 0x12; iVar1 = iVar1 + 1) {
    fVar3 = cosf(fVar2);
    this[iVar1 * 4 + 0xe] = (int)(fVar3 * 114.0 - (float)this[8]);
    fVar3 = sinf(fVar2);
    this[iVar1 * 4 + 0xf] = (int)(-fVar3 * 114.0 - (float)this[9]);
    fVar3 = cosf(fVar2);
    this[iVar1 * 4 + 0x10] = (int)((fVar3 * 114.0 + 128.0) * 16.0);
    fVar3 = sinf(fVar2);
    this[iVar1 * 4 + 0x11] = (int)((-fVar3 * 114.0 + 128.0) * 16.0);
    fVar2 = fVar2 + 0.19634955;
  }
  this->u16_58 = 1;
  *(undefined2 *)((int)this + 0x162) = 0x1e;
  fVar2 = sinf(__x - 1.5707964);
  fVar3 = cosf(__x - 1.5707964);
  this[0x5c] = (int)((fVar3 * 114.0) / 2.0);
  this[0x5d] = (int)((-fVar2 * 114.0) / 2.0);
  this[0x5e] = 0;
  this[0x5f] = 0;
  this[0x60] = 0;
  this[0x61] = -0x417105ca;
  this[0x62] = (int)-(float)this[0x5c];
  this[99] = (int)-(float)this[0x5d];
  this[100] = 0x45000000;
  this[0x65] = 0x45000000;
  fVar2 = __x + 3.1415927;
  for (iVar1 = 1; iVar1 < 0x12; iVar1 = iVar1 + 1) {
    fVar3 = cosf(fVar2);
    this[iVar1 * 4 + 0x62] = (int)(fVar3 * 114.0 - (float)this[0x5c]);
    fVar3 = sinf(fVar2);
    this[iVar1 * 4 + 99] = (int)(-fVar3 * 114.0 - (float)this[0x5d]);
    fVar3 = cosf(fVar2);
    this[iVar1 * 4 + 100] = (int)((fVar3 * 114.0 + 128.0) * 16.0);
    fVar3 = sinf(fVar2);
    this[iVar1 * 4 + 0x65] = (int)((-fVar3 * 114.0 + 128.0) * 16.0);
    fVar2 = fVar2 + 0.19634955;
  }
  fVar2 = cosf(__x);
  this[0xb8] = (int)(fVar2 * 101.0 * 1.1);
  fVar2 = sinf(__x);
  this[0xb9] = (int)(-fVar2 * 101.0 * 1.1);
  fVar2 = cosf(__x + 3.1415927);
  this[0xba] = (int)(fVar2 * 101.0 * 1.1);
  fVar2 = sinf(__x + 3.1415927);
  this[0xbb] = (int)(-fVar2 * 101.0 * 1.1);
  return;
}
