// decomp/D/JRing_Hit.c — cleaned Ghidra output (SLPM_602.19, Metrowerks MIPS), Shadow Hearts: Covenant JP demo.
// Field accesses are shown as this->T_off (T = u8/u16/u32/f32/i32/p, off = hex offset);
// JRing fields are named from the recovered struct. See notes/D/*.md for layouts.
// CAVEAT: when the base pointer is a float*/int*/short*, the number in `T_off` is an ELEMENT offset (byte offset = off*sizeof(elem)).
// `this` is the C++ this pointer (param_1); the Metrowerks ABI passes it in a0.

// JP: 0x002c97a0  getPacket__6HitMesFv  =  HitMes::getPacket
undefined4 HitMes::getPacket(int this)

{
  HitMes::MakePacket(this);
  return *(undefined4 *)(this + (this->u8_44 & 3) * 4 + 0x18);
}

// JP: 0x002c97f0  getPacket__6HitBarFv  =  HitBar::getPacket
undefined4 HitBar::getPacket(int this)

{
  HitBar::MakePacket(this);
  return *(undefined4 *)(this + (this->u8_50 & 3) * 4 + 0x18);
}

// JP: 0x002c9840  getPacket__7HitAreaFv  =  HitArea::getPacket
undefined4 HitArea::getPacket(int this)

{
  HitArea::MakePacket(this);
  return *(undefined4 *)(this + (this->u8_44 & 3) * 4 + 0x18);
}

// JP: 0x002e4040  __ct__6HitMesFP5JRingP6JRAREAs  =  HitMes::HitMes
int HitMes::HitMes
              (int this,undefined4 param_2,undefined4 param_3,undefined2 param_4)

{
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  undefined4 uVar1;
  
  CPolObj::CPolObj(this);
  VIF1Prim::VIF1Prim((VIF1Prim *)(this + 0x18));
  this->u32_2c = 0;
  this->u32_30 = 0;
  *(undefined1 **)(this + 0x34) = DelayDeleteObject::__vt;
  *(undefined1 **)(this + 0x14) = HitMes::__vt;
  this->u32_28 = 0x406790;
  this->u32_34 = 0x4067a0;
  this->u32_60 = in_zero_lo;
  this->u32_64 = in_zero_hi;
  this->u32_68 = in_zero_udw;
  this->u32_6c = in_register_0000000c;
  this->u32_70 = in_zero_lo;
  this->u32_74 = in_zero_hi;
  this->u32_78 = in_zero_udw;
  this->u32_7c = in_register_0000000c;
  this->u32_40 = param_2;
  this->u16_44 = 0;
  this->u16_46 = param_4;
  this->u32_a4 = 0;
  this->u32_9c = 0;
  uVar1 = SysTool::GetTimer();
  this->u32_a0 = uVar1;
  this->u32_1c = 0;
  this->u32_18 = 0;
  this->u32_98 = 0;
  HitMes::Initialize(this,param_2,param_3);
  CPoller::Entry(CApp::app + 0x48,this,0x80,0);
  JRing::HitMesEntry(this->u32_40,this);
  return this;
}

// JP: 0x002e4190  __dt__6HitMesFv  =  HitMes::~HitMes
int HitMes::~HitMes(int this,short param_2)

{
  if (this != 0) {
    *(undefined1 **)(this + 0x14) = HitMes::__vt;
    this->u32_28 = 0x406790;
    this->u32_34 = 0x4067a0;
    if (this->i32_18 != 0) {
      __dla(this->u32_18);
    }
    if (this->i32_1c != 0) {
      __dla(this->u32_1c);
    }
    if (this != -0x2c) {
      *(undefined1 **)(this + 0x34) = DelayDeleteObject::__vt;
    }
    VIF1Prim::~VIF1Prim(this + 0x18,0);
    CPolObj::~CPolObj(this,0);
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x002e42b0  Destruct__6HitMesFv  =  HitMes::Destruct
void HitMes::Destruct(int this)

{
  JRing::HitMesRelease(this->u32_40,this);
  CPoller::Dispose(CApp::app + 0x48,this);
  (**(code **)(this->i32_34 + 0xc))();
  return;
}

// JP: 0x002e4310  Polling__6HitMesFv  =  HitMes::Polling
undefined4 HitMes::Polling(int this)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  float fStack_18;
  
  if ((long)((ulong)this->u8_44 << 0x3c) < 0) {
    (**(code **)(this->i32_34 + 0xc))();
    uVar2 = 1;
  }
  else {
    iVar3 = SysTool::GetTimer();
    iVar1 = this->i32_a0;
    this->i32_a0 = iVar3;
    this->f32_a4 = this->f32_a4 + (float)(uint)(iVar3 - iVar1) * 0.001;
    fStack_18 = this->f32_a4 * 6.2831855 * 4.0;
    if (6.2831855 < fStack_18) {
      fStack_18 = 6.2831855;
    }
    this->f32_74 = 6.2831855 - fStack_18;
    if (this->f32_a4 < 0.2) {
      this->f32_84 = this->f32_a4 * 5.0;
    }
    else if (this->f32_a4 < 0.7) {
      this->u32_84 = 0x3f800000;
    }
    else {
      this->f32_84 = 1.0 - (this->f32_a4 - 0.7) * 5.0;
    }
    if ((this->i16_46 != 3) && (this->i16_46 != 4)) {
      this->f32_58 = 3.0 - this->f32_a4 * 5.5;
      if (this->f32_58 < 0.0) {
        this->u32_58 = 0;
      }
      this->f32_54 = this->f32_54 + this->f32_58;
    }
    this->f32_80 = this->f32_a4 * 5.0;
    if (1.0 < this->f32_80) {
      this->u32_80 = 0x3f800000;
    }
    if (0.9 <= this->f32_a4) {
      JRing::HitMesRelease(this->u32_40,this);
      this->u8_44 = this->u8_44 & 0xf7 | 8;
    }
    uVar2 = 0;
  }
  return uVar2;
}

// JP: 0x002e46b0  MakePacket__6HitMesFv  =  HitMes::MakePacket
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void HitMes::MakePacket(int this)

{
  bool bVar1;
  undefined4 *puVar2;
  bool bVar3;
  float in_zero_lo;
  float in_zero_hi;
  float in_zero_udw;
  float in_register_0000000c;
  int iVar4;
  undefined4 uVar5;
  ulong uVar6;
  long lVar7;
  float *pfVar8;
  undefined8 uVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  uint uVar13;
  float fVar14;
  float fVar15;
  undefined1 in_vf0 [16];
  undefined1 auVar16 [16];
  undefined1 auVar17 [16];
  undefined1 auVar18 [16];
  int aiStack_3d0 [4];
  undefined4 uStack_3c0;
  undefined4 uStack_3bc;
  undefined4 uStack_3b8;
  undefined4 uStack_3b4;
  undefined4 uStack_3b0;
  undefined4 uStack_3ac;
  int iStack_3a8;
  int iStack_3a4;
  int aiStack_3a0 [16];
  undefined1 auStack_360 [16];
  undefined1 auStack_350 [16];
  undefined1 auStack_340 [16];
  undefined1 auStack_330 [16];
  int aiStack_320 [64];
  float afStack_220 [132];
  float fStack_10;
  float fStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  pfVar8 = afStack_220 + 0x40;
  afStack_220[0x80] = in_zero_lo;
  afStack_220[0x81] = in_zero_hi;
  do {
    *pfVar8 = in_zero_lo;
    pfVar8[1] = in_zero_hi;
    pfVar8[2] = in_zero_udw;
    pfVar8[3] = in_register_0000000c;
    pfVar8 = pfVar8 + 4;
  } while (pfVar8 != afStack_220 + 0x80);
  pfVar8 = afStack_220;
  do {
    *pfVar8 = in_zero_lo;
    pfVar8[1] = in_zero_hi;
    pfVar8[2] = in_zero_udw;
    pfVar8[3] = in_register_0000000c;
    pfVar8 = pfVar8 + 4;
  } while (pfVar8 != afStack_220 + 0x40);
  auVar16 = _vmr32(in_vf0);
  auVar17 = _vmr32(auVar16);
  auVar18 = _vmr32(auVar17);
  auStack_330 = _sqc2(in_vf0);
  auStack_340 = _sqc2(auVar16);
  auStack_350 = _sqc2(auVar17);
  auStack_360 = _sqc2(auVar18);
  uVar9 = CONCAT44(DAT_003f899c,DAT_003f8998);
  aiStack_3d0[0] = (int)__2568;
  aiStack_3d0[1] = (int)((ulong)__2568 >> 0x20);
  aiStack_3d0[2] = DAT_003f8988;
  aiStack_3d0[3] = DAT_003f898c;
  uStack_3c0 = (undefined4)_DAT_003f8990;
  uStack_3bc = (undefined4)((ulong)_DAT_003f8990 >> 0x20);
  uStack_3b8 = DAT_003f8998;
  uStack_3b4 = DAT_003f899c;
  uStack_3b0 = DAT_003f89a0;
  uStack_3ac = DAT_003f89a4;
  iStack_3a8 = DAT_003f89a8;
  iStack_3a4 = DAT_003f89ac;
  if ((this->i16_46 == 3) || (this->i16_46 == 4)) {
    fStack_10 = 0.0;
    fStack_c = 0.0;
  }
  else {
    fVar15 = sinf(this->f32_50);
    fVar14 = this->f32_54;
    fStack_10 = cosf(this->f32_50);
    fStack_10 = this->f32_54 * fStack_10;
    fStack_c = fVar14 * -fVar15;
  }
  uStack_4 = 0;
  uStack_8 = 0;
  auVar16 = _vmr32(in_vf0);
  auVar17 = _vmr32(auVar16);
  auVar18 = _vmr32(auVar17);
  auStack_330 = _sqc2(in_vf0);
  auStack_340 = _sqc2(auVar16);
  auStack_350 = _sqc2(auVar17);
  auStack_360 = _sqc2(auVar18);
  sceVu0RotMatrixZ(this->u32_68,auStack_360,auStack_360);
  sceVu0RotMatrixX(this->u32_60,auStack_360,auStack_360);
  sceVu0RotMatrixY(this->u32_64,auStack_360,auStack_360);
  RotTransVector(afStack_220 + 0x80,&fStack_10,auStack_360,1);
  if (this->i32_a8 < 0) {
    afStack_220[0x41] = ((float)-(int)this->i16_8e * this->f32_80) / 2.0
    ;
    afStack_220[0x40] = ((float)-(int)this->i16_8c * this->f32_80) / 2.0
    ;
    afStack_220[0x42] = 0.0;
    afStack_220[0x43] = 1.0;
    afStack_220[0x45] = ((float)(int)this->i16_8e * this->f32_80) / 2.0;
    afStack_220[0x44] = ((float)-(int)this->i16_8c * this->f32_80) / 2.0
    ;
    afStack_220[0x46] = 0.0;
    afStack_220[0x47] = 1.0;
    afStack_220[0x49] = ((float)-(int)this->i16_8e * this->f32_80) / 2.0
    ;
    afStack_220[0x48] = ((float)(int)this->i16_8c * this->f32_80) / 2.0;
    afStack_220[0x4a] = 0.0;
    afStack_220[0x4b] = 1.0;
    afStack_220[0x4d] = ((float)(int)this->i16_8e * this->f32_80) / 2.0;
    afStack_220[0x4c] = ((float)(int)this->i16_8c * this->f32_80) / 2.0;
    afStack_220[0x4e] = 0.0;
    afStack_220[0x4f] = 1.0;
    aiStack_3a0[0] = (int)this->i16_88;
    aiStack_3a0[1] = (int)this->i16_8a;
    aiStack_3a0[2] = (int)this->i16_88 + (int)this->i16_8c;
    aiStack_3a0[3] = (int)this->i16_8a + (int)this->i16_8e;
    iVar12 = 1;
  }
  else {
    for (iVar11 = 0; iVar11 < 4; iVar11 = iVar11 + 1) {
      aiStack_3a0[iVar11 * 4] = -1;
    }
    iVar10 = 0;
    iVar11 = 0;
    for (iVar12 = 100; iVar12 != 0; iVar12 = iVar12 / 10 + (iVar12 >> 0x1f)) {
      if (iVar12 <= this->i32_a8) {
        if (iVar12 == 0) {
          trap(7);
        }
        iVar4 = (this->i32_a8 / iVar12) % 10;
        aiStack_3a0[iVar10 * 4] = aiStack_3d0[iVar4];
        aiStack_3a0[iVar10 * 4 + 1] = 0x31;
        aiStack_3a0[iVar10 * 4 + 2] = aiStack_3d0[iVar4 + 1];
        aiStack_3a0[iVar10 * 4 + 3] = 0x47;
        iVar11 = iVar11 + (aiStack_3a0[iVar10 * 4 + 2] - aiStack_3a0[iVar10 * 4]) + -2;
        iVar10 = iVar10 + 1;
      }
    }
    aiStack_3a0[iVar10 * 4] = iStack_3a8;
    aiStack_3a0[iVar10 * 4 + 1] = 0x31;
    aiStack_3a0[iVar10 * 4 + 2] = iStack_3a4;
    aiStack_3a0[iVar10 * 4 + 3] = 0x47;
    iVar12 = iVar10 + 1;
    iVar11 = -(iVar11 + (aiStack_3a0[iVar10 * 4 + 2] - aiStack_3a0[iVar10 * 4]));
    if (iVar11 < 0) {
      iVar11 = iVar11 + 1;
    }
    iVar11 = iVar11 >> 1;
    for (iVar10 = 0; iVar10 < iVar12; iVar10 = iVar10 + 1) {
      fVar15 = this->f32_80;
      afStack_220[iVar10 * 0x10 + 0x40] = (float)iVar11 * this->f32_80;
      afStack_220[iVar10 * 0x10 + 0x41] = fVar15 * -11.0;
      afStack_220[iVar10 * 0x10 + 0x42] = 0.0;
      afStack_220[iVar10 * 0x10 + 0x43] = 1.0;
      fVar15 = this->f32_80;
      iVar4 = iVar10 * 4 + 1;
      afStack_220[iVar4 * 4 + 0x40] = (float)iVar11 * this->f32_80;
      afStack_220[iVar4 * 4 + 0x41] = fVar15 * 11.0;
      afStack_220[iVar4 * 4 + 0x42] = 0.0;
      afStack_220[iVar4 * 4 + 0x43] = 1.0;
      fVar15 = this->f32_80;
      iVar4 = iVar10 * 4 + 2;
      afStack_220[iVar4 * 4 + 0x40] =
           this->f32_80 *
           (float)((iVar11 + aiStack_3a0[iVar10 * 4 + 2]) - aiStack_3a0[iVar10 * 4]);
      afStack_220[iVar4 * 4 + 0x41] = fVar15 * -11.0;
      afStack_220[iVar4 * 4 + 0x42] = 0.0;
      afStack_220[iVar4 * 4 + 0x43] = 1.0;
      fVar15 = this->f32_80;
      iVar4 = iVar10 * 4 + 3;
      afStack_220[iVar4 * 4 + 0x40] =
           this->f32_80 *
           (float)((iVar11 + aiStack_3a0[iVar10 * 4 + 2]) - aiStack_3a0[iVar10 * 4]);
      afStack_220[iVar4 * 4 + 0x41] = fVar15 * 11.0;
      afStack_220[iVar4 * 4 + 0x42] = 0.0;
      afStack_220[iVar4 * 4 + 0x43] = 1.0;
      iVar11 = iVar11 + (aiStack_3a0[iVar10 * 4 + 2] - aiStack_3a0[iVar10 * 4]) + -2;
    }
  }
  auVar16 = _vmr32(in_vf0);
  auVar17 = _vmr32(auVar16);
  auVar18 = _vmr32(auVar17);
  auStack_330 = _sqc2(in_vf0);
  auStack_340 = _sqc2(auVar16);
  auStack_350 = _sqc2(auVar17);
  auStack_360 = _sqc2(auVar18);
  sceVu0RotMatrixZ(this->u32_78,auStack_360,auStack_360);
  sceVu0RotMatrixX(this->u32_70,auStack_360,auStack_360);
  sceVu0RotMatrixY(this->u32_74,auStack_360,auStack_360);
  RotTransVector(afStack_220,afStack_220 + 0x40,auStack_360,iVar12 << 2);
  bVar3 = false;
  for (iVar11 = 0; iVar11 < iVar12 << 2; iVar11 = iVar11 + 1) {
    aiStack_320[iVar11 * 4] =
         (int)((this->f32_48 + afStack_220[0x80] + afStack_220[iVar11 * 4]) * 16.0 +
              28672.0);
    aiStack_320[iVar11 * 4 + 1] =
         (int)((this->f32_4c + afStack_220[0x81] + afStack_220[iVar11 * 4 + 1]) * 16.0
              + 29184.0);
    if ((aiStack_320[iVar11 * 4] < 0) || (0x10000 < aiStack_320[iVar11 * 4])) {
      bVar3 = true;
    }
    if ((aiStack_320[iVar11 * 4 + 1] < 0) || (0x10000 < aiStack_320[iVar11 * 4 + 1])) {
      bVar3 = true;
    }
  }
  bVar1 = (this->u8_44 & 3) == 0;
  this->i32_94 = iVar12 * 4 + 0xc;
  uVar13 = (uint)bVar1;
  if (*(int *)(this + uVar13 * 4 + 0x18) == 0) {
    uVar5 = __nwa(this->i32_94 << 4);
    *(undefined4 *)(this + uVar13 * 4 + 0x18) = uVar5;
    iVar11 = *(int *)(this + uVar13 * 4 + 0x18);
    iVar11->i32_10 = this->i32_94 + 0xffffffd;
    iVar11->u32_14 = 0;
    iVar11->u32_18 = 0;
    iVar11->i32_1c = this->i32_94 + 0x4ffffffd;
    iVar11->u64_20 = 0x5000000000000001;
    iVar11->u64_28 = 0xee6ee;
    iVar11->u64_30 = 1;
    iVar11->u64_38 = 0x3f;
    uVar6 = JRCTex::GetTex0(JRing::JRTex,1);
    iVar11->u64_40 = uVar6 & 0xfffffffc0fffff | 0x2000000001300000;
    iVar11->u64_48 = 0x16;
    iVar11->u64_50 = uVar6 & 0xffffffffffffff | (long)this->i32_90 << 0x38;
    iVar11->u64_58 = 0;
    iVar11->u64_60 = 0x23001;
    iVar11->u64_68 = 0x47;
    iVar11->u64_70 = 0x44;
    iVar11->u64_78 = 0x42;
    iVar11->u64_80 = 0x2400000000000001;
    iVar11->u64_88 = 0x10;
    iVar11->u64_90 = 0x154;
    auVar17._8_8_ = uVar9;
    auVar17._0_8_ = 0x8000000000000000;
    auVar16._4_4_ = in_zero_hi;
    auVar16._0_4_ = in_zero_lo;
    auVar16._8_4_ = in_zero_udw;
    auVar16._12_4_ = in_register_0000000c;
    auVar16 = _pcpyld(auVar16,auVar17);
    iVar11->u64_a0 = (long)iVar12 | 0x400000000008000U | auVar16._0_8_;
    iVar11->u64_a8 = 0x4343c3c3;
  }
  this->u8_44 = this->u8_44 & 0xfb | 4;
  puVar2 = *(undefined4 **)(this + uVar13 * 4 + 0x18);
  if (bVar3) {
    *(undefined4 **)(this + 0x98) = puVar2;
    this->u8_44 = this->u8_44 & 0xfc | bVar1;
  }
  else {
    *puVar2 = 0x50000000;
    puVar2[1] = *(undefined4 *)(JRing::JRTex + (uint)JRing::JRTex->u16_a * 4 + 0xc);
    puVar2[2] = 0;
    puVar2[3] = 0;
    lVar7 = __fixunssfdi(this->f32_84 * 128.0);
    puVar2->u64_26 = lVar7 << 0x18 | 0x808080;
    for (iVar11 = 0; iVar11 < iVar12; iVar11 = iVar11 + 1) {
      if (aiStack_3a0[iVar11 * 4] < 0) {
        *(undefined8 *)(puVar2 + (iVar11 * 4 + 0xb) * 4 + 2) = 0x71006f00;
        *(undefined8 *)(puVar2 + (iVar11 * 4 + 0xc) * 4 + 2) = 0x71006f00;
        *(undefined8 *)(puVar2 + (iVar11 * 4 + 0xd) * 4 + 2) = 0x71006f00;
        *(undefined8 *)(puVar2 + (iVar11 * 4 + 0xe) * 4 + 2) = 0x71006f00;
      }
      else {
        *(long *)(puVar2 + (iVar11 * 4 + 0xb) * 4) =
             (long)(aiStack_3a0[iVar11 * 4] << 4) | (long)(aiStack_3a0[iVar11 * 4 + 1] << 4) << 0x10
        ;
        *(long *)(puVar2 + (iVar11 * 4 + 0xb) * 4 + 2) =
             (long)aiStack_320[iVar11 * 0x10] | (long)aiStack_320[iVar11 * 0x10 + 1] << 0x10;
        *(long *)(puVar2 + (iVar11 * 4 + 0xc) * 4) =
             (long)(aiStack_3a0[iVar11 * 4] << 4) | (long)(aiStack_3a0[iVar11 * 4 + 3] << 4) << 0x10
        ;
        *(long *)(puVar2 + (iVar11 * 4 + 0xc) * 4 + 2) =
             (long)aiStack_320[(iVar11 * 4 + 1) * 4] |
             (long)aiStack_320[(iVar11 * 4 + 1) * 4 + 1] << 0x10;
        *(long *)(puVar2 + (iVar11 * 4 + 0xd) * 4) =
             (long)(aiStack_3a0[iVar11 * 4 + 2] << 4) |
             (long)(aiStack_3a0[iVar11 * 4 + 1] << 4) << 0x10;
        *(long *)(puVar2 + (iVar11 * 4 + 0xd) * 4 + 2) =
             (long)aiStack_320[(iVar11 * 4 + 2) * 4] |
             (long)aiStack_320[(iVar11 * 4 + 2) * 4 + 1] << 0x10;
        *(long *)(puVar2 + (iVar11 * 4 + 0xe) * 4) =
             (long)(aiStack_3a0[iVar11 * 4 + 2] << 4) |
             (long)(aiStack_3a0[iVar11 * 4 + 3] << 4) << 0x10;
        *(long *)(puVar2 + (iVar11 * 4 + 0xe) * 4 + 2) =
             (long)aiStack_320[(iVar11 * 4 + 3) * 4] |
             (long)aiStack_320[(iVar11 * 4 + 3) * 4 + 1] << 0x10;
      }
    }
    *(undefined4 **)(this + 0x98) = puVar2 + (iVar12 * 4 + 0xb) * 4;
    this->u8_44 = this->u8_44 & 0xfc | bVar1;
  }
  return;
}

// JP: 0x002e5740  Initialize__6HitMesFP5JRingP6JRAREA  =  HitMes::Initialize
void HitMes::Initialize(int this,int param_2,long param_3)

{
  char cVar1;
  short sVar2;
  undefined8 uVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 uVar6;
  
  this->u32_48 = param_2->u32_68;
  this->u32_4c = param_2->u32_6c;
  uVar6 = GetRad(90.0 - param_2->f32_4ac);
  this->u32_50 = uVar6;
  uVar3 = param_2->u64_70;
  uVar6 = param_2->u32_78;
  uVar4 = param_2->u32_7c;
  this->i32_60 = (int)uVar3;
  this->i32_64 = (int)((ulong)uVar3 >> 0x20);
  this->u32_68 = uVar6;
  this->u32_6c = uVar4;
  this->f32_54 = param_2->f32_84 * 101.0;
  this->u32_58 = 0x40400000;
  this->u32_70 = 0;
  this->u32_74 = 0x40c90fdb;
  this->u32_78 = 0;
  this->u32_7c = 0;
  this->u32_80 = 0;
  this->u32_84 = 0;
  this->u32_a4 = 0;
  if (param_3 == 0) {
    sVar2 = this->i16_46;
    if (sVar2 == 4) {
      this->u16_88 = 0;
      this->u16_8a = 0x18;
      this->u16_8c = 0x62;
      this->u16_8e = 0x18;
      this->u32_90 = 0;
      this->u32_a8 = 0xffffffff;
    }
    else if (sVar2 == 3) {
      this->u16_88 = 0x70;
      this->u16_8a = 0x18;
      this->u16_8c = 0x46;
      this->u16_8e = 0x18;
      this->u32_90 = 2;
      this->u32_a8 = 0xffffffff;
    }
    else if (sVar2 == 2) {
      this->u16_88 = 0;
      this->u16_8a = 0;
      this->u16_8c = 0x4b;
      this->u16_8e = 0x18;
      this->u32_90 = 4;
      this->u32_a8 = 0xffffffff;
    }
    else if (sVar2 == 1) {
      this->u16_88 = 0x70;
      this->u16_8a = 0x18;
      this->u16_8c = 0x46;
      this->u16_8e = 0x18;
      this->u32_90 = 2;
      this->u32_a8 = 0xffffffff;
    }
    else if (sVar2 == 0) {
      this->u16_88 = 0;
      this->u16_8a = 0x18;
      this->u16_8c = 0x62;
      this->u16_8e = 0x18;
      this->u32_90 = 0;
      this->u32_a8 = 0xffffffff;
    }
  }
  else {
    iVar5 = (int)param_3;
    cVar1 = iVar5->i8_2;
    if (cVar1 == '\x02') {
      if (((ulong)param_2->u8_41 & 0xf) >> 2 == 1) {
        iVar5 = ((int)iVar5->i16_1a * param_2->i32_524) / 10000;
        if (iVar5 == 100) {
          this->u16_88 = 0;
          this->u16_8a = 0;
          this->u16_8c = 0x4b;
          this->u16_8e = 0x18;
          this->u32_90 = 4;
          this->u32_a8 = 0xffffffff;
        }
        else {
          this->u16_88 = 0;
          this->u16_8a = 0;
          this->u16_8c = 0x4b;
          this->u16_8e = 0x18;
          this->u32_90 = 4;
          this->i32_a8 = iVar5;
        }
      }
      else if (this->i16_46 == 0) {
        if ((iVar5->i16_8 == 0) || (iVar5->i16_1a != 0x78)) {
          if (iVar5->i16_1a == 100) {
            this->u16_88 = 0;
            this->u16_8a = 0;
            this->u16_8c = 0x4b;
            this->u16_8e = 0x18;
            this->u32_90 = 4;
            this->u32_a8 = 0xffffffff;
          }
          else {
            this->u16_88 = 0;
            this->u16_8a = 0;
            this->u16_8c = 0x4b;
            this->u16_8e = 0x18;
            this->u32_90 = 4;
            this->i32_a8 = (int)iVar5->i16_1a;
          }
        }
        else {
          this->u16_88 = 0x70;
          this->u16_8a = 0;
          this->u16_8c = 0x5a;
          this->u16_8e = 0x18;
          this->u32_90 = 0;
          this->u32_a8 = 0xffffffff;
        }
      }
      else {
        this->u16_88 = 0;
        this->u16_8a = 0x18;
        this->u16_8c = 0x62;
        this->u16_8e = 0x18;
        this->u32_90 = 0;
        this->u32_a8 = 0xffffffff;
      }
    }
    else if (cVar1 == '\x01') {
      if (this->i16_46 == 0) {
        if ((iVar5->i16_8 == 0) || (iVar5->i16_1a != 0x78)) {
          this->u16_88 = 0;
          this->u16_8a = 0;
          this->u16_8c = 0x4b;
          this->u16_8e = 0x18;
          this->u32_90 = 4;
          this->u32_a8 = 0xffffffff;
        }
        else {
          this->u16_88 = 0x70;
          this->u16_8a = 0;
          this->u16_8c = 0x5a;
          this->u16_8e = 0x18;
          this->u32_90 = 0;
          this->u32_a8 = 0xffffffff;
        }
      }
      else {
        this->u16_88 = 0;
        this->u16_8a = 0x18;
        this->u16_8c = 0x62;
        this->u16_8e = 0x18;
        this->u32_90 = 0;
        this->u32_a8 = 0xffffffff;
      }
    }
    else if (cVar1 == '\0') {
      this->u16_88 = 0;
      this->u16_8a = 0;
      this->u16_8c = 0x4b;
      this->u16_8e = 0x18;
      this->u32_90 = 4;
      this->u32_a8 = 0xffffffff;
    }
    else if (cVar1 == -1) {
      this->u16_88 = 0x70;
      this->u16_8a = 0x18;
      this->u16_8c = 0x46;
      this->u16_8e = 0x18;
      this->u32_90 = 2;
      this->u32_a8 = 0xffffffff;
    }
  }
  return;
}

// JP: 0x002e5cf0  __ct__6HitBarFP5JRingf  =  HitBar::HitBar
int HitBar::HitBar(undefined4 this,int param_2,undefined4 param_3)

{
  undefined4 uVar1;
  
  CPolObj::CPolObj(param_2);
  VIF1Prim::VIF1Prim((VIF1Prim *)(param_2 + 0x18));
  param_2->u32_2c = 0;
  param_2->u32_30 = 0;
  *(undefined1 **)(param_2 + 0x34) = DelayDeleteObject::__vt;
  *(undefined1 **)(param_2 + 0x14) = HitBar::__vt;
  param_2->u32_28 = 0x406750;
  param_2->u32_34 = 0x406760;
  param_2->u32_40 = param_3;
  uVar1 = GetRad(this);
  param_2->u32_48 = uVar1;
  param_2->u32_44 = 0;
  param_2->u32_4c = 0x3f800000;
  param_2->u32_50 = 0;
  param_2->u32_54 = 0;
  uVar1 = SysTool::GetTimer();
  param_2->u32_58 = uVar1;
  param_2->u32_1c = 0;
  param_2->u32_18 = 0;
  param_2->u32_5c = 0;
  CPoller::Entry(CApp::app + 0x48,param_2,0x80,0);
  JRing::HitBarEntry(param_2->u32_40,param_2);
  return param_2;
}

// JP: 0x002e5e30  __dt__6HitBarFv  =  HitBar::~HitBar
int HitBar::~HitBar(int this,short param_2)

{
  if (this != 0) {
    *(undefined1 **)(this + 0x14) = HitBar::__vt;
    this->u32_28 = 0x406750;
    this->u32_34 = 0x406760;
    if (this->i32_18 != 0) {
      __dla(this->u32_18);
    }
    if (this->i32_1c != 0) {
      __dla(this->u32_1c);
    }
    if (this != -0x2c) {
      *(undefined1 **)(this + 0x34) = DelayDeleteObject::__vt;
    }
    VIF1Prim::~VIF1Prim(this + 0x18,0);
    CPolObj::~CPolObj(this,0);
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x002e5f50  Destruct__6HitBarFv  =  HitBar::Destruct
void HitBar::Destruct(int this)

{
  JRing::HitBarRelease(this->u32_40,this);
  CPoller::Dispose(CApp::app + 0x48,this);
  (**(code **)(this->i32_34 + 0xc))();
  return;
}

// JP: 0x002e5fb0  Polling__6HitBarFv  =  HitBar::Polling
undefined4 HitBar::Polling(int this)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  if ((long)((ulong)this->u8_50 << 0x3c) < 0) {
    (**(code **)(this->i32_34 + 0xc))();
    uVar2 = 1;
  }
  else {
    iVar3 = SysTool::GetTimer();
    iVar1 = this->i32_58;
    this->i32_58 = iVar3;
    this->f32_44 = this->f32_44 + (float)(uint)(iVar3 - iVar1) * 0.001;
    if (this->f32_44 < 0.7) {
      this->u32_4c = 0x3f800000;
    }
    else {
      this->f32_4c = 1.0 - (this->f32_44 - 0.5) * 5.0;
    }
    if (0.7 <= this->f32_44) {
      JRing::HitBarRelease(this->u32_40,this);
      this->u8_50 = this->u8_50 & 0xf7 | 8;
    }
    uVar2 = 0;
  }
  return uVar2;
}

// JP: 0x002e6180  MakePacket__6HitBarFv  =  HitBar::MakePacket
void HitBar::MakePacket(int this)

{
  bool bVar1;
  undefined4 *puVar2;
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  undefined4 uVar3;
  undefined8 in_a0_udw;
  int iVar4;
  uint uVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  undefined1 in_vf0 [16];
  undefined1 auVar11 [16];
  undefined1 auVar12 [16];
  undefined1 auVar13 [16];
  undefined1 auStack_110 [16];
  undefined1 auStack_100 [16];
  undefined1 auStack_f0 [16];
  undefined1 auStack_e0 [16];
  int aiStack_d0 [6];
  int iStack_b8;
  int iStack_b4;
  int iStack_b0;
  int iStack_ac;
  int iStack_a8;
  int iStack_a4;
  int iStack_a0;
  int iStack_9c;
  int iStack_98;
  int iStack_94;
  undefined1 auStack_90 [64];
  float fStack_50;
  float fStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  float fStack_40;
  float fStack_3c;
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
  
  auVar11 = _vmr32(in_vf0);
  auVar12 = _vmr32(auVar11);
  auVar13 = _vmr32(auVar12);
  auStack_e0 = _sqc2(in_vf0);
  auStack_f0 = _sqc2(auVar11);
  auStack_100 = _sqc2(auVar12);
  auStack_110 = _sqc2(auVar13);
  fVar6 = sinf((1.5707964 - this->f32_48) - 1.5707964);
  fStack_50 = cosf((1.5707964 - this->f32_48) - 1.5707964);
  fStack_50 = fStack_50 * 1.5;
  uStack_48 = 0;
  uStack_44 = 0x3f800000;
  fStack_4c = -fVar6 * 1.5;
  fVar6 = sinf((1.5707964 - this->f32_48) + 1.5707964);
  fStack_40 = cosf((1.5707964 - this->f32_48) + 1.5707964);
  fStack_40 = fStack_40 * 1.5;
  uStack_38 = 0;
  uStack_34 = 0x3f800000;
  fStack_3c = -fVar6 * 1.5;
  fVar6 = sinf(1.5707964 - this->f32_48);
  fVar7 = *(float *)(this->i32_40 + 0x84);
  fVar8 = sinf((1.5707964 - this->f32_48) - 1.5707964);
  fVar9 = cosf(1.5707964 - this->f32_48);
  fVar10 = *(float *)(this->i32_40 + 0x84) * fVar9 * 103.0;
  fVar9 = cosf((1.5707964 - this->f32_48) - 1.5707964);
  fStack_30 = fVar10 + fVar9 * 1.5;
  uStack_28 = 0;
  uStack_24 = 0x3f800000;
  fStack_2c = fVar7 * -fVar6 * 103.0 + -fVar8 * 1.5;
  fVar6 = sinf(1.5707964 - this->f32_48);
  fVar7 = *(float *)(this->i32_40 + 0x84);
  fVar8 = sinf((1.5707964 - this->f32_48) + 1.5707964);
  fVar9 = cosf(1.5707964 - this->f32_48);
  fVar10 = *(float *)(this->i32_40 + 0x84) * fVar9 * 103.0;
  fVar9 = cosf((1.5707964 - this->f32_48) + 1.5707964);
  fStack_20 = fVar10 + fVar9 * 1.5;
  uStack_18 = 0;
  uStack_14 = 0x3f800000;
  auVar11 = _vmr32(in_vf0);
  auVar12 = _vmr32(auVar11);
  auVar13 = _vmr32(auVar12);
  auStack_e0 = _sqc2(in_vf0);
  auStack_f0 = _sqc2(auVar11);
  auStack_100 = _sqc2(auVar12);
  auStack_110 = _sqc2(auVar13);
  fStack_1c = fVar7 * -fVar6 * 103.0 + -fVar8 * 1.5;
  sceVu0RotMatrixZ(*(undefined4 *)(this->i32_40 + 0x78),auStack_110,auStack_110);
  sceVu0RotMatrixX(*(undefined4 *)(this->i32_40 + 0x70),auStack_110,auStack_110);
  sceVu0RotMatrixY(*(undefined4 *)(this->i32_40 + 0x74),auStack_110,auStack_110);
  RotTransVector(auStack_90,&fStack_50,auStack_110,4);
  sceVu0RotTransPersN(aiStack_d0,this->i32_40 + 0x590,auStack_90,4,0);
  for (iVar4 = 0; iVar4 < 4; iVar4 = iVar4 + 1) {
    aiStack_d0[iVar4 * 4] =
         (int)((float)aiStack_d0[iVar4 * 4] +
              (*(float *)(this->i32_40 + 0x68) - 256.0) * 16.0);
    aiStack_d0[iVar4 * 4 + 1] =
         (int)((float)aiStack_d0[iVar4 * 4 + 1] +
              (*(float *)(this->i32_40 + 0x6c) - 224.0) * 16.0);
    aiStack_d0[iVar4 * 4 + 2] = (int)((float)aiStack_d0[iVar4 * 4 + 2] / 16.0);
  }
  bVar1 = (this->u8_50 & 3) == 0;
  uVar5 = (uint)bVar1;
  if (*(int *)(this + uVar5 * 4 + 0x18) == 0) {
    uVar3 = __nwa(0xa0);
    *(undefined4 *)(this + uVar5 * 4 + 0x18) = uVar3;
    puVar2 = *(undefined4 **)(this + uVar5 * 4 + 0x18);
    *puVar2 = &DAT_10000008;
    puVar2[1] = 0;
    puVar2[2] = 0;
    puVar2[3] = 0x50000008;
    puVar2->u64_4 = 0x1000000000000001;
    puVar2->u64_6 = 0xe;
    puVar2->u64_8 = 0x44;
    puVar2->u64_a = 0x42;
    auVar12._8_8_ = in_a0_udw;
    auVar12._0_8_ = 0xa400000000008001;
    auVar11._4_4_ = in_zero_hi;
    auVar11._0_4_ = in_zero_lo;
    auVar11._8_4_ = in_zero_udw;
    auVar11._12_4_ = in_register_0000000c;
    auVar11 = _pcpyld(auVar11,auVar12);
    puVar2->i64_c = auVar11._0_8_;
    puVar2->u64_e = 0x4141c1c1f0;
    puVar2->u64_10 = 0x4c;
    puVar2->u64_12 = 0;
  }
  this->u8_50 = this->u8_50 & 0xfb | 4;
  iVar4 = *(int *)(this + uVar5 * 4 + 0x18);
  fVar6 = this->f32_4c * 128.0;
  if (2.1474836e+09 <= fVar6) {
    fVar6 = fVar6 - 2.1474836e+09;
  }
  iVar4->u64_50 =
       ((long)(int)fVar6 & 0xffU) << 0x18 | 0xf3fff |
       (ulong)(uint)(16.0 / (float)aiStack_d0[3]) << 0x20;
  iVar4->i64_58 =
       (long)aiStack_d0[2] << 0x20 | (long)aiStack_d0[0] | (long)aiStack_d0[1] << 0x10;
  fVar6 = this->f32_4c * 128.0;
  if (2.1474836e+09 <= fVar6) {
    fVar6 = fVar6 - 2.1474836e+09;
  }
  iVar4->u64_60 =
       ((long)(int)fVar6 & 0xffU) << 0x18 | 0xf3fff | (ulong)(uint)(16.0 / (float)iStack_b4) << 0x20
  ;
  iVar4->i64_68 =
       (long)iStack_b8 << 0x20 | (long)aiStack_d0[4] | (long)aiStack_d0[5] << 0x10;
  fVar6 = this->f32_4c * 128.0;
  if (2.1474836e+09 <= fVar6) {
    fVar6 = fVar6 - 2.1474836e+09;
  }
  iVar4->u64_70 =
       ((long)(int)fVar6 & 0xffU) << 0x18 | 0xbfefff |
       (ulong)(uint)(16.0 / (float)iStack_a4) << 0x20;
  iVar4->i64_78 = (long)iStack_a8 << 0x20 | (long)iStack_b0 | (long)iStack_ac << 0x10;
  fVar6 = this->f32_4c * 128.0;
  if (2.1474836e+09 <= fVar6) {
    fVar6 = fVar6 - 2.1474836e+09;
  }
  iVar4->u64_80 =
       ((long)(int)fVar6 & 0xffU) << 0x18 | 0xbfefff |
       (ulong)(uint)(16.0 / (float)iStack_94) << 0x20;
  iVar4->i64_88 = (long)iStack_98 << 0x20 | (long)iStack_a0 | (long)iStack_9c << 0x10;
  this->i32_5c = iVar4 + 0x90;
  this->u8_50 = this->u8_50 & 0xfc | bVar1;
  return;
}

// JP: 0x002e6c20  __ct__7HitAreaFP5JRingffP7_rgba32  =  HitArea::HitArea
int HitArea::HitArea
              (undefined4 this,undefined4 param_2,int param_3,int param_4,undefined1 *param_5)

{
  undefined4 uVar1;
  int iVar2;
  
  CPolObj::CPolObj(param_3);
  VIF1Prim::VIF1Prim((VIF1Prim *)(param_3 + 0x18));
  param_3->u32_2c = 0;
  param_3->u32_30 = 0;
  *(undefined1 **)(param_3 + 0x34) = DelayDeleteObject::__vt;
  *(undefined1 **)(param_3 + 0x14) = HitArea::__vt;
  param_3->u32_28 = 0x406710;
  param_3->u32_34 = 0x406720;
  iVar2 = param_3 + 0x60;
  do {
    iVar2 = iVar2 + 4;
  } while (iVar2 != param_3 + 0x68);
  param_3->i32_40 = param_4;
  param_3->u32_44 = 0;
  param_3->u32_48 = this;
  param_3->u32_4c = param_2;
  param_3->u32_50 = 0x3f400000;
  param_3->u8_60 = *param_5;
  param_3->u8_61 = param_5[1];
  param_3->u8_62 = param_5[2];
  param_3->u8_66 = 0xff;
  param_3->u8_65 = 0xff;
  param_3->u8_64 = 0xff;
  param_3->u32_68 = 0;
  param_3->u32_6c = param_4->u32_84;
  param_3->u32_54 = 0;
  uVar1 = SysTool::GetTimer();
  param_3->u32_58 = uVar1;
  param_3->u32_1c = 0;
  param_3->u32_18 = 0;
  param_3->u32_5c = 0;
  CPoller::Entry(CApp::app + 0x48,param_3,0x80,0);
  JRing::HitAreaEffEntry(param_3->u32_40,param_3);
  return param_3;
}

// JP: 0x002e6e00  __dt__7HitAreaFv  =  HitArea::~HitArea
int HitArea::~HitArea(int this,short param_2)

{
  if (this != 0) {
    *(undefined1 **)(this + 0x14) = HitArea::__vt;
    this->u32_28 = 0x406710;
    this->u32_34 = 0x406720;
    if (this->i32_18 != 0) {
      __dla(this->u32_18);
    }
    if (this->i32_1c != 0) {
      __dla(this->u32_1c);
    }
    if (this != -0x2c) {
      *(undefined1 **)(this + 0x34) = DelayDeleteObject::__vt;
    }
    VIF1Prim::~VIF1Prim(this + 0x18,0);
    CPolObj::~CPolObj(this,0);
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x002e6f20  Destruct__7HitAreaFv  =  HitArea::Destruct
void HitArea::Destruct(int this)

{
  JRing::HitAreaEffRelease(this->u32_40,this);
  CPoller::Dispose(CApp::app + 0x48,this);
  (**(code **)(this->i32_34 + 0xc))();
  return;
}

// JP: 0x002e6f80  Polling__7HitAreaFv  =  HitArea::Polling
/* WARNING: Removing unreachable block (ram,0x002e722c) */
/* WARNING: Removing unreachable block (ram,0x002e717c) */
/* WARNING: Removing unreachable block (ram,0x002e72dc) */

undefined4 HitArea::Polling(int this)

{
  undefined4 uVar1;
  int iVar2;
  undefined1 uVar3;
  float fVar4;
  float fVar5;
  
  if ((long)((ulong)this->u8_44 << 0x3c) < 0) {
    (**(code **)(this->i32_34 + 0xc))();
    uVar1 = 1;
  }
  else {
    iVar2 = SysTool::GetTimer();
    fVar5 = (float)(uint)(iVar2 - this->i32_58) * 0.001;
    this->i32_58 = iVar2;
    if ((long)((ulong)this->u8_44 << 0x3b) < 0) {
      fVar4 = this->f32_54;
      this->f32_54 = this->f32_54 + fVar5;
      this->f32_6c =
           this->f32_6c + fVar5 * 8.0 * ((0.15 - fVar4) / 0.15);
      if (this->f32_54 < 0.075) {
        fVar4 = (0.075 - this->f32_54) / 0.075;
        fVar5 = (float)this->u8_60 +
                (float)(int)(0xff - (uint)this->u8_60) * fVar4;
        if (fVar5 < 2.1474836e+09) {
          uVar3 = (undefined1)(int)fVar5;
        }
        else {
          uVar3 = (undefined1)(int)(fVar5 - 2.1474836e+09);
        }
        this->u8_64 = uVar3;
        fVar5 = (float)this->u8_61 +
                (float)(int)(0xff - (uint)this->u8_61) * fVar4;
        if (fVar5 < 2.1474836e+09) {
          uVar3 = (undefined1)(int)fVar5;
        }
        else {
          uVar3 = (undefined1)(int)(fVar5 - 2.1474836e+09);
        }
        this->u8_65 = uVar3;
        fVar5 = (float)this->u8_62 +
                (float)(int)(0xff - (uint)this->u8_62) * fVar4;
        if (fVar5 < 2.1474836e+09) {
          uVar3 = (undefined1)(int)fVar5;
        }
        else {
          uVar3 = (undefined1)(int)(fVar5 - 2.1474836e+09);
        }
        this->u8_66 = uVar3;
      }
      else {
        this->u8_64 = this->u8_60;
        this->u8_65 = this->u8_61;
        this->u8_66 = this->u8_62;
      }
      this->f32_50 = (0.15 - this->f32_54) / 0.15;
      if (0.15 <= this->f32_54) {
        JRing::HitAreaEffRelease(this->u32_40,this);
        this->u8_44 = this->u8_44 & 0xf7 | 8;
      }
      uVar1 = 0;
    }
    else {
      uVar1 = 0;
    }
  }
  return uVar1;
}

// JP: 0x002e7430  MakePacket__7HitAreaFv  =  HitArea::MakePacket
void HitArea::MakePacket(int this)

{
  bool bVar1;
  undefined4 *puVar2;
  float in_zero_lo;
  float in_zero_hi;
  float in_zero_udw;
  float in_register_0000000c;
  int iVar3;
  undefined4 uVar4;
  float *pfVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  undefined1 in_vf0 [16];
  undefined1 auVar15 [16];
  undefined1 auVar16 [16];
  undefined1 auVar17 [16];
  undefined1 auStack_cb0 [16];
  undefined1 auStack_ca0 [16];
  undefined1 auStack_c90 [16];
  undefined1 auStack_c80 [16];
  int aiStack_c70 [6];
  int iStack_c58;
  int iStack_c54;
  int aiStack_c50 [256];
  float afStack_850 [528];
  float afStack_10 [3];
  float fStack_4;
  
  pfVar5 = afStack_850 + 0x108;
  do {
    *pfVar5 = in_zero_lo;
    pfVar5[1] = in_zero_hi;
    pfVar5[2] = in_zero_udw;
    pfVar5[3] = in_register_0000000c;
    pfVar5 = pfVar5 + 4;
  } while (pfVar5 != afStack_10);
  pfVar5 = afStack_850;
  do {
    *pfVar5 = in_zero_lo;
    pfVar5[1] = in_zero_hi;
    pfVar5[2] = in_zero_udw;
    pfVar5[3] = in_register_0000000c;
    pfVar5 = pfVar5 + 4;
  } while (pfVar5 != afStack_850 + 0x108);
  auVar15 = _vmr32(in_vf0);
  auVar16 = _vmr32(auVar15);
  auVar17 = _vmr32(auVar16);
  auStack_c80 = _sqc2(in_vf0);
  auStack_c90 = _sqc2(auVar15);
  auStack_ca0 = _sqc2(auVar16);
  auStack_cb0 = _sqc2(auVar17);
  iVar8 = 0;
  for (fVar13 = this->f32_48 + this->f32_4c;
      this->f32_48 < fVar13; fVar13 = fVar13 - 11.25) {
    for (fVar14 = 90.0 - fVar13; fVar14 < -180.0; fVar14 = fVar14 + 360.0) {
    }
    for (; 180.0 <= fVar14; fVar14 = fVar14 - 360.0) {
    }
    fVar10 = (float)GetRad(fVar14);
    fVar10 = sinf(fVar10);
    fVar11 = this->f32_68;
    fVar12 = (float)GetRad(fVar14);
    fVar12 = cosf(fVar12);
    afStack_850[iVar8 * 4 + 0x108] = this->f32_68 * fVar12 * 101.0;
    afStack_850[iVar8 * 4 + 0x109] = fVar11 * -fVar10 * 101.0;
    afStack_850[iVar8 * 4 + 0x10a] = 0.0;
    afStack_850[iVar8 * 4 + 0x10b] = 1.0;
    fVar10 = (float)GetRad(fVar14);
    fVar10 = sinf(fVar10);
    fVar11 = this->f32_6c;
    fVar14 = (float)GetRad(fVar14);
    fVar14 = cosf(fVar14);
    iVar3 = iVar8 + 1;
    afStack_850[iVar3 * 4 + 0x108] = this->f32_6c * fVar14 * 101.0;
    afStack_850[iVar3 * 4 + 0x109] = fVar11 * -fVar10 * 101.0;
    afStack_850[iVar3 * 4 + 0x10a] = 0.0;
    afStack_850[iVar3 * 4 + 0x10b] = 1.0;
    iVar8 = iVar8 + 2;
  }
  for (fVar13 = 90.0 - this->f32_48; fVar13 < -180.0; fVar13 = fVar13 + 360.0) {
  }
  for (; 180.0 <= fVar13; fVar13 = fVar13 - 360.0) {
  }
  fVar14 = (float)GetRad(fVar13);
  fVar14 = sinf(fVar14);
  fVar10 = this->f32_68 * -fVar14 * 101.0;
  fVar14 = (float)GetRad(fVar13);
  fVar14 = cosf(fVar14);
  afStack_850[iVar8 * 4 + 0x108] = this->f32_68 * fVar14 * 101.0;
  afStack_850[iVar8 * 4 + 0x109] = fVar10;
  afStack_850[iVar8 * 4 + 0x10a] = 0.0;
  afStack_850[iVar8 * 4 + 0x10b] = 1.0;
  fVar14 = (float)GetRad(fVar13);
  fVar14 = sinf(fVar14);
  fVar14 = this->f32_6c * -fVar14 * 101.0;
  fVar13 = (float)GetRad(fVar13);
  fVar13 = cosf(fVar13);
  iVar3 = iVar8 + 1;
  afStack_850[iVar3 * 4 + 0x108] = this->f32_6c * fVar13 * 101.0;
  afStack_850[iVar3 * 4 + 0x109] = fVar14;
  afStack_850[iVar3 * 4 + 0x10a] = 0.0;
  afStack_850[iVar3 * 4 + 0x10b] = 1.0;
  iVar9 = iVar8 + 2;
  auVar15 = _vmr32(in_vf0);
  auVar16 = _vmr32(auVar15);
  auVar17 = _vmr32(auVar16);
  auStack_c80 = _sqc2(in_vf0);
  auStack_c90 = _sqc2(auVar15);
  auStack_ca0 = _sqc2(auVar16);
  auStack_cb0 = _sqc2(auVar17);
  sceVu0RotMatrixZ(*(undefined4 *)(this->i32_40 + 0x78),auStack_cb0,auStack_cb0);
  sceVu0RotMatrixX(*(undefined4 *)(this->i32_40 + 0x70),auStack_cb0,auStack_cb0);
  sceVu0RotMatrixY(*(undefined4 *)(this->i32_40 + 0x74),auStack_cb0,auStack_cb0);
  RotTransVector(afStack_850,afStack_850 + 0x108,auStack_cb0,iVar9);
  sceVu0RotTransPersN(aiStack_c70,this->i32_40 + 0x590,afStack_850,iVar9,0);
  for (iVar3 = 0; iVar3 < iVar9; iVar3 = iVar3 + 1) {
    aiStack_c70[iVar3 * 4] =
         (int)((float)aiStack_c70[iVar3 * 4] +
              (*(float *)(this->i32_40 + 0x68) - 256.0) * 16.0);
    aiStack_c70[iVar3 * 4 + 1] =
         (int)((float)aiStack_c70[iVar3 * 4 + 1] +
              (*(float *)(this->i32_40 + 0x6c) - 224.0) * 16.0);
    aiStack_c70[iVar3 * 4 + 2] = (int)((float)aiStack_c70[iVar3 * 4 + 2] / 16.0);
  }
  bVar1 = (this->u8_44 & 3) == 0;
  uVar7 = (uint)bVar1;
  if (*(int *)(this + uVar7 * 4 + 0x18) == 0) {
    iVar3 = iVar8;
    if (iVar8 < 0) {
      iVar3 = iVar8 + 1;
    }
    uVar4 = __nwa(((iVar3 >> 1) * 2 + 10) * 0x10);
    *(undefined4 *)(this + uVar7 * 4 + 0x18) = uVar4;
    puVar2 = *(undefined4 **)(this + uVar7 * 4 + 0x18);
    iVar3 = iVar8;
    if (iVar8 < 0) {
      iVar3 = iVar8 + 1;
    }
    *puVar2 = &DAT_10000008 + (iVar3 >> 1) * 2;
    puVar2[1] = 0;
    puVar2[2] = 0;
    iVar3 = iVar8;
    if (iVar8 < 0) {
      iVar3 = iVar8 + 1;
    }
    puVar2[3] = (iVar3 >> 1) * 2 + 0x50000008;
    puVar2->u64_4 = 0x2000000000000001;
    puVar2->u64_6 = 0xee;
    puVar2->u64_8 = 0x23001;
    puVar2->u64_a = 0x47;
    puVar2->u64_c = 0x48;
    puVar2->u64_e = 0x42;
    puVar2->u64_10 = 0x6400000000000001;
    puVar2->u64_12 = 0xc1c1f0;
    puVar2->u64_14 = 0x4c;
    puVar2->u64_16 = 0;
    if (iVar8 < 0) {
      iVar8 = iVar8 + 1;
    }
    puVar2->u64_20 = (long)(iVar8 >> 1) | 0x4400000000008000;
    puVar2->u64_22 = 0x4141;
  }
  this->u8_44 = this->u8_44 & 0xfb | 4;
  iVar8 = *(int *)(this + uVar7 * 4 + 0x18);
  fVar13 = this->f32_50 * 31.0;
  if (2.1474836e+09 <= fVar13) {
    fVar13 = fVar13 - 2.1474836e+09;
  }
  iVar8->u64_60 =
       (ulong)(uint)(16.0 / (float)aiStack_c70[3]) << 0x20 |
       ((long)(int)fVar13 & 0xffU) << 0x18 | (ulong)this->uint3_64;
  iVar8->i64_68 =
       (long)aiStack_c70[2] << 0x20 | (long)aiStack_c70[0] | (long)aiStack_c70[1] << 0x10;
  fStack_4 = 16.0 / (float)iStack_c54;
  fVar13 = this->f32_50 * 128.0;
  if (2.1474836e+09 <= fVar13) {
    fVar13 = fVar13 - 2.1474836e+09;
  }
  iVar8->u64_70 =
       (ulong)(uint)(16.0 / (float)iStack_c54) << 0x20 |
       ((long)(int)fVar13 & 0xffU) << 0x18 | (ulong)this->uint3_64;
  iVar8->i64_78 =
       (long)iStack_c58 << 0x20 | (long)aiStack_c70[4] | (long)aiStack_c70[5] << 0x10;
  iVar3 = 9;
  for (iVar6 = 2; iVar6 < iVar9; iVar6 = iVar6 + 2) {
    fStack_4 = 16.0 / (float)aiStack_c70[iVar6 * 4 + 3];
    fVar13 = this->f32_50 * 31.0;
    if (2.1474836e+09 <= fVar13) {
      fVar13 = fVar13 - 2.1474836e+09;
    }
    *(ulong *)(iVar8 + iVar3 * 0x10) =
         (ulong)(uint)(16.0 / (float)aiStack_c70[iVar6 * 4 + 3]) << 0x20 |
         ((long)(int)fVar13 & 0xffU) << 0x18 | (ulong)this->uint3_64;
    *(long *)(iVar8 + iVar3 * 0x10 + 8) =
         (long)aiStack_c70[iVar6 * 4 + 2] << 0x20 |
         (long)aiStack_c70[iVar6 * 4] | (long)aiStack_c70[iVar6 * 4 + 1] << 0x10;
    fStack_4 = 16.0 / (float)aiStack_c70[(iVar6 + 1) * 4 + 3];
    fVar13 = this->f32_50 * 128.0;
    if (2.1474836e+09 <= fVar13) {
      fVar13 = fVar13 - 2.1474836e+09;
    }
    *(ulong *)(iVar8 + (iVar3 + 1) * 0x10) =
         (ulong)(uint)(16.0 / (float)aiStack_c70[(iVar6 + 1) * 4 + 3]) << 0x20 |
         ((long)(int)fVar13 & 0xffU) << 0x18 | (ulong)this->uint3_64;
    *(long *)(iVar8 + (iVar3 + 1) * 0x10 + 8) =
         (long)aiStack_c70[(iVar6 + 1) * 4 + 2] << 0x20 |
         (long)aiStack_c70[(iVar6 + 1) * 4] | (long)aiStack_c70[(iVar6 + 1) * 4 + 1] << 0x10;
    iVar3 = iVar3 + 2;
  }
  this->i32_5c = iVar8 + iVar3 * 0x10;
  this->u8_44 = this->u8_44 & 0xfc | bVar1;
  return;
}
