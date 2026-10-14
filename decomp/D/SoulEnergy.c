// decomp/D/SoulEnergy.c — cleaned Ghidra output (SLPM_602.19, Metrowerks MIPS), Shadow Hearts: Covenant JP demo.
// Field accesses are shown as this->T_off (T = u8/u16/u32/f32/i32/p, off = hex offset);
// JRing fields are named from the recovered struct. See notes/D/*.md for layouts.
// CAVEAT: when the base pointer is a float*/int*/short*, the number in `T_off` is an ELEMENT offset (byte offset = off*sizeof(elem)).
// `this` is the C++ this pointer (param_1); the Metrowerks ABI passes it in a0.

// JP: 0x0028b3d0  __ct__10SoulEnergyFv  =  SoulEnergy::SoulEnergy
int SoulEnergy::SoulEnergy(int this)

{
  MenuPlace::MenuPlace(this);
  MenuPacket::MenuPacket(this + 0x3c);
  *(undefined1 **)(this + 8) = SoulEnergy::__vt;
  this->u32_3c = 0x4059a4;
  __construct_array(this + 0x58,0x277820,0x277890,0x30,3);
  MenuSprite::MenuSprite(this + 0xe8);
  this->u16_154 = 9999;
  this->u16_156 = 4;
  this->u16_158 = 0xb4;
  this->u16_15a = 0xff79;
  this->u32_15c = 0x43160000;
  this->u32_160 = 0x43160000;
  this->u32_164 = 0x42c80000;
  this->u16_168 = 0x74;
  this->u16_16a = 0x6c;
  (**(code **)(this->i32_8 + 0x20))();
  return this;
}

// JP: 0x0028b4f0  __dt__10SoulEnergyFv  =  SoulEnergy::~SoulEnergy
int SoulEnergy::~SoulEnergy(int this,short param_2)

{
  if (this != 0) {
    *(undefined1 **)(this + 8) = SoulEnergy::__vt;
    this->u32_3c = 0x4059a4;
    (**(code **)(this->i32_8 + 0x1c))();
    MenuSprite::~MenuSprite(this + 0xe8,0xffffffffffffffff);
    __destroy_arr(this + 0x58,0x277890,0x30,3);
    MenuPacket::~MenuPacket(this + 0x3c,0);
    MenuPlace::~MenuPlace(this,0);
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x0028b5d0  Create__10SoulEnergyFP11MenuTextureP11MenuTextureP11MenuTexture  =  SoulEnergy::Create
/* WARNING: Removing unreachable block (ram,0x0028b7f0) */
/* WARNING: Removing unreachable block (ram,0x0028b828) */

void SoulEnergy::Create
               (int this,int param_2,int param_3,int param_4)

{
  ulong uVar1;
  
  MenuPacket::CreatePacket(this + 0x3c,0x1b);
  SendOnLocal::Create
            (this + 0x58,param_2 + 0x18,param_2->u32_14,0,0xffffffffffffffff);
  SendOnLocal::Create
            (this + 0x88,param_3 + 0x18,param_3->u32_14,0,0xffffffffffffffff);
  SendOnLocal::Create
            (this + 0xb8,param_4 + 0x18,param_4->u32_14,1,0xffffffffffffffff);
  SendOnLocal::UpdatePacket(this + 0x58);
  SendOnLocal::UpdatePacket(this + 0x88);
  SendOnLocal::UpdatePacket(this + 0xb8);
  this->i32_4c = param_2;
  this->i32_50 = param_3;
  this->i32_54 = param_4;
  MenuSprite::Create(this + 0xe8,1);
  this->u8_109 = this->u8_109 & 0xbf | 0x40;
  uVar1 = (ulong)this->u8_f9 & 0xfffffffffffffffd | 2;
  this->i8_f9 = (char)uVar1;
  this->u8_f8 =
       this->u8_f8 & 0xfd | (byte)((uint)((uVar1 << 0x3e) >> 0x3f) << 1);
  (**(code **)(this->i32_f0 + 0x24))(0x42fc0000,0x43020000);
  (**(code **)(this->i32_f0 + 0x28))
            ((float)**(ushort **)(param_4 + 0x10),(float)*(ushort *)(param_4->i32_10 + 2));
  MenuSprite::SetUV
            (this + 0xe8,0,0,**(undefined2 **)(param_4 + 0x10),
             *(undefined2 *)(param_4->i32_10 + 2));
  this->u8_10 = this->u8_10 | 0x3f;
  this->u8_11 = this->u8_11 | 0x3f;
  uVar1 = (ulong)this->u8_11 & 0xffffffffffffff7f | 0x80;
  this->i8_11 = (char)uVar1;
  this->u8_10 =
       this->u8_10 & 0x7f | (byte)((uint)((uVar1 << 0x38) >> 0x3f) << 7);
  return;
}

// JP: 0x0028b940  SetMeter__10SoulEnergyFf  =  SoulEnergy::SetMeter
void SoulEnergy::SetMeter(float this,int param_2)

{
  ulong uVar1;
  undefined1 uVar2;
  float fVar3;
  float fVar4;
  undefined4 uStack_10;
  
  uStack_10 = this;
  if (this < 0.0) {
    uStack_10 = 0.0;
  }
  fVar3 = uStack_10 /
          ((float)(int)param_2->i16_154 / (float)(int)param_2->i16_156);
  if (fVar3 < 2.1474836e+09) {
    uVar2 = (undefined1)(int)fVar3;
  }
  else {
    uVar2 = (undefined1)(int)(fVar3 - 2.1474836e+09);
  }
  param_2->u8_149 = uVar2;
  fVar3 = fRadian * ((float)(int)param_2->i16_15a +
                    (uStack_10 * (float)(int)param_2->i16_158) /
                    (float)(int)param_2->i16_154);
  fVar4 = cosf(fVar3);
  param_2->i32_14c =
       (int)(param_2->f32_15c + param_2->f32_164 * fVar4) << 4;
  fVar3 = sinf(fVar3);
  param_2->i32_150 =
       (int)(param_2->f32_160 + param_2->f32_164 * -fVar3) << 4;
  uVar1 = (ulong)param_2->u8_11 & 0xfffffffffffffffb | 4;
  param_2->i8_11 = (char)uVar1;
  param_2->u8_10 =
       param_2->u8_10 & 0xfb | (byte)((uint)((uVar1 << 0x3d) >> 0x3f) << 2);
  uVar1 = (ulong)param_2->u8_11 & 0xffffffffffffffdf | 0x20;
  param_2->i8_11 = (char)uVar1;
  param_2->u8_10 =
       param_2->u8_10 & 0xdf | (byte)((uint)((uVar1 << 0x3a) >> 0x3f) << 5);
  uVar1 = (ulong)param_2->u8_11 & 0xfffffffffffffff7 | 8;
  param_2->i8_11 = (char)uVar1;
  param_2->u8_10 =
       param_2->u8_10 & 0xf7 | (byte)((uint)((uVar1 << 0x3c) >> 0x3f) << 3);
  return;
}

// JP: 0x0028bbd0  SetAlpha__10SoulEnergyFUc  =  SoulEnergy::SetAlpha
void SoulEnergy::SetAlpha(int this,undefined1 param_2)

{
  ulong uVar1;
  
  this->u8_148 = param_2;
  (**(code **)(this->i32_f0 + 0x2c))(this + 0xe8,param_2);
  uVar1 = (ulong)this->u8_11 & 0xffffffffffffffef | 0x10;
  this->i8_11 = (char)uVar1;
  this->u8_10 =
       this->u8_10 & 0xef | (byte)((uint)((uVar1 << 0x3b) >> 0x3f) << 4);
  return;
}

// JP: 0x0028bc70  SetOwner__10SoulEnergyFP10MenuWindow  =  SoulEnergy::SetOwner
void SoulEnergy::SetOwner(int this,undefined4 param_2)

{
  this->u32_18 = param_2;
  (**(code **)(this->i32_f0 + 0x38))(this + 0xe8,param_2);
  return;
}

// JP: 0x0028bcc0  Polling__10SoulEnergyFv  =  SoulEnergy::Polling
void SoulEnergy::Polling(int this)

{
  this->i16_14a = this->i16_14a + (short)MenuObj::sm_iPassTime;
  if (0x3c0 < this->i16_14a) {
    this->i16_14a = this->i16_14a + -0x780;
  }
  return;
}

// JP: 0x0028bd20  Update__10SoulEnergyFiiUs  =  SoulEnergy::Update
void SoulEnergy::Update(int this,int param_2,int param_3,ushort param_4)

{
  char cVar1;
  undefined4 *puVar2;
  short sVar3;
  undefined1 auVar4 [16];
  undefined1 auVar5 [16];
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  undefined1 auVar8 [16];
  undefined1 auVar9 [16];
  undefined1 auVar10 [16];
  undefined1 auVar11 [16];
  undefined1 auVar12 [16];
  short sVar13;
  undefined1 in_zero_qw [16];
  byte bVar14;
  byte *pbVar15;
  uint uVar16;
  int iVar17;
  undefined8 uVar18;
  undefined1 auVar19 [16];
  undefined1 auVar20 [16];
  undefined1 auVar21 [16];
  undefined1 auVar22 [16];
  undefined1 auVar23 [16];
  undefined1 uVar24;
  undefined1 uVar25;
  short sVar26;
  undefined8 in_v1_udw;
  char cVar27;
  undefined8 in_a0_udw;
  undefined8 *puVar28;
  undefined1 auVar29 [16];
  ulong *puVar30;
  ulong *puVar31;
  float fVar32;
  float fVar33;
  float fStack_6c;
  int iStack_30;
  int iStack_20;
  
  cVar27 = (char)this;
  puVar2 = *(undefined4 **)(this + (VIF1Prim::m_Env & 1) * 4 + 0x40);
  pbVar15 = (byte *)(this + (uint)(VIF1Prim::m_Env & 1) + 0x10);
  if (this->i16_14a < 0) {
    uVar16 = -(int)this->i16_14a / 0x14;
  }
  else {
    sVar26 = this->i16_14a;
    uVar16 = (int)sVar26 / 0x14 + ((int)sVar26 >> 0x1f) + (uint)(byte)((byte)(sVar26 >> 0xf) >> 7);
  }
  uVar16 = 0x80 - (uVar16 & 0xff) & 0xff;
  bVar14 = *pbVar15;
  this->u8_f8 = this->u8_f8 | bVar14;
  this->u8_f9 = this->u8_f9 | bVar14;
  (**(code **)(this->i32_f0 + 0x30))(cVar27 + -0x18,uVar16,uVar16,uVar16);
  if ((*pbVar15 & 1) != 0) {
    *puVar2 = &DAT_10000019;
    puVar2[3] = 0x50000019;
    puVar2->u64_4 = 0x1000000000000003;
    puVar2->u64_6 = 0xe;
    puVar2->u64_a = 0x3f;
    puVar2->u64_e = 0x4e;
    puVar28 = (undefined8 *)(puVar2 + 0x10);
    uVar18 = SendOnLocal::GetTex0(cVar27 + 'X');
    *puVar28 = uVar18;
    puVar28[1] = 6;
    puVar28[2] = 0x6400000000000001;
    puVar28[3] = 0x53d310;
    puVar28[4] = 0x156;
    *(undefined2 *)((int)puVar28 + 0x32) = 8;
    puVar28->u16_6 = 8;
    puVar28->i16_8 = **(short **)(this->i32_4c + 0x10) * 0x10 + 8;
    *(short *)((int)puVar28 + 0x42) =
         *(short *)(*(int *)(this->i32_4c + 0x10) + 2) * 0x10 + 8;
    puVar28[10] = 0x1000000000000001;
    puVar28[0xb] = 0xe;
    puVar28[0xc] = 0x3200d;
    puVar28[0xd] = 0x47;
    auVar19._8_8_ = in_a0_udw;
    auVar19._0_8_ = 0x8400000000000001;
    auVar19 = _pcpyld(in_zero_qw,auVar19);
    puVar28[0xe] = auVar19._0_8_;
    puVar28[0x10] = 0x45;
    *(undefined1 *)((int)puVar28 + 0x8b) = 0;
    *(undefined1 *)((int)puVar28 + 0x8a) = 0;
    *(undefined1 *)((int)puVar28 + 0x89) = 0;
    puVar28->u8_11 = 0;
    puVar28[0x18] = 0x1000000000000002;
    puVar28[0x19] = 0xe;
    puVar28[0x1a] = 0x70003;
    puVar28[0x1b] = 0x47;
    puVar28 = puVar28 + 0x1c;
    uVar18 = SendOnLocal::GetTex0(cVar27 + -0x78);
    *puVar28 = uVar18;
    puVar28[1] = 6;
    puVar28[2] = 0x6400000000000001;
    puVar28[3] = 0x53d310;
    puVar28[4] = 0x156;
    *(undefined2 *)((int)puVar28 + 0x32) = 8;
    puVar28->u16_6 = 8;
    puVar28->i16_8 = **(short **)(this->i32_50 + 0x10) * 0x10 + 8;
    *(short *)((int)puVar28 + 0x42) =
         *(short *)(*(int *)(this->i32_50 + 0x10) + 2) * 0x10 + 8;
    puVar28[10] = 0x1000000000008002;
    puVar28[0xb] = 0xe;
    puVar28[0xc] = 0x3000c;
    puVar28[0xd] = 0x47;
    puVar28[0xf] = 0x4e;
  }
  if ((long)((ulong)*pbVar15 << 0x3d) < 0) {
    cVar1 = this->i8_149;
    sVar26 = (short)(((long)cVar1 << 0x38) >> 0x3f);
    iVar17 = (int)(((long)cVar1 << 0x38) >> 0x3f);
    if (CONCAT44(iVar17,CONCAT22(sVar26,(short)cVar1)) == 3) {
      puVar2->u64_2e = 0x5dfffd10;
    }
    else if (CONCAT44(iVar17,CONCAT22(sVar26,(short)cVar1)) == 2) {
      puVar2->u64_2e = 0x55dffd10;
    }
    else if (CONCAT44(iVar17,CONCAT22(sVar26,(short)cVar1)) == 1) {
      puVar2->u64_2e = 0x555dfd10;
    }
    else if (CONCAT44(iVar17,CONCAT22(sVar26,(short)cVar1)) == 0) {
      puVar2->u64_2e = 0x5555dd10;
    }
    else {
      puVar2->u64_2e = 0xffffff10;
    }
  }
  if ((long)((ulong)*pbVar15 << 0x3b) < 0) {
    uVar24 = (undefined1)((uint)this->u8_148 * (uint)param_4 >> 0xf);
    *(undefined1 *)((int)puVar2 + 0x14a) = uVar24;
    *(undefined1 *)((int)puVar2 + 0x149) = uVar24;
    puVar2->u8_52 = uVar24;
    *(undefined1 *)((int)puVar2 + 0x6a) = uVar24;
    *(undefined1 *)((int)puVar2 + 0x69) = uVar24;
    puVar2->u8_1a = uVar24;
    *(undefined1 *)((int)puVar2 + 0x14b) = uVar24;
    *(undefined1 *)((int)puVar2 + 0x6b) = uVar24;
  }
  iStack_30 = param_2;
  iStack_20 = param_3;
  if ((long)((ulong)*pbVar15 << 0x3c) < 0) {
    iStack_30 = param_2 + (int)(this->f32_24 * 16.0);
    iStack_20 = param_3 + (int)(this->f32_28 * 16.0);
    puVar30 = (ulong *)(puVar2 + 0x1e);
    puVar31 = (ulong *)(puVar2 + 0x22);
    sVar13 = (short)iStack_30;
    *(short *)puVar30 = sVar13;
    sVar3 = (short)iStack_20;
    *(short *)((int)puVar2 + 0x7a) = sVar3;
    auVar4._8_8_ = in_v1_udw;
    auVar4._0_8_ = 0xffffffff;
    auVar11._8_8_ = in_a0_udw;
    auVar11._0_8_ = 0xffffffffffffffff;
    auVar19 = _pcpyld(auVar11,auVar4);
    auVar20._8_8_ = auVar19._8_8_;
    *puVar30 = *puVar30 & auVar19._0_8_ | 0x100000000;
    *(short *)puVar31 = sVar13 + **(short **)(this->i32_4c + 0x10) * 0x10;
    *(short *)((int)puVar2 + 0x8a) =
         sVar3 + *(short *)(*(int *)(this->i32_4c + 0x10) + 2) * 0x10;
    auVar20._0_8_ = 0xffffffff;
    auVar5._8_8_ = in_v1_udw;
    auVar5._0_8_ = 0xffffffffffffffff;
    auVar19 = _pcpyld(auVar5,auVar20);
    auVar21._8_8_ = auVar19._8_8_;
    *puVar31 = *puVar31 & auVar19._0_8_ | 0x100000000;
    puVar30 = (ulong *)(puVar2 + 0x56);
    puVar31 = (ulong *)(puVar2 + 0x5a);
    *(short *)puVar30 = sVar13 + this->i16_168 * 0x10;
    *(short *)((int)puVar2 + 0x15a) = sVar3 + this->i16_16a * 0x10;
    auVar21._0_8_ = 0xffffffff;
    auVar6._8_8_ = in_v1_udw;
    auVar6._0_8_ = 0xffffffffffffffff;
    auVar19 = _pcpyld(auVar6,auVar21);
    auVar22._8_8_ = auVar19._8_8_;
    *puVar30 = *puVar30 & auVar19._0_8_ | 0x200000000;
    *(short *)puVar31 = (short)*puVar30 + **(short **)(this->i32_50 + 0x10) * 0x10;
    *(short *)((int)puVar2 + 0x16a) =
         *(short *)((int)puVar2 + 0x15a) +
         *(short *)(*(int *)(this->i32_50 + 0x10) + 2) * 0x10;
    auVar22._0_8_ = 0xffffffff;
    auVar7._8_8_ = in_v1_udw;
    auVar7._0_8_ = 0xffffffffffffffff;
    auVar19 = _pcpyld(auVar7,auVar22);
    auVar23._8_8_ = auVar19._8_8_;
    *puVar31 = *puVar31 & auVar19._0_8_ | 0x200000000;
    puVar30 = (ulong *)(puVar2 + 0x34);
    *(short *)puVar30 = (short)((int)this->f32_15c << 4) + sVar13;
    *(short *)((int)puVar2 + 0xd2) = (short)(int)this->f32_160 * 0x10 + sVar3;
    auVar23._0_8_ = 0xffffffff;
    auVar8._8_8_ = in_v1_udw;
    auVar8._0_8_ = 0xffffffffffffffff;
    auVar19 = _pcpyld(auVar8,auVar23);
    *puVar30 = *puVar30 & auVar19._0_8_ | 0x500000000;
    auVar29._8_8_ = auVar19._8_8_;
    puVar30 = puVar30 + this->i8_149 + 1;
    *(short *)puVar30 = (short)this->u32_14c + sVar13;
    *(short *)((int)puVar30 + 2) = (short)this->u32_150 + sVar3;
    auVar29._0_8_ = 0xffffffff;
    auVar9._8_8_ = in_v1_udw;
    auVar9._0_8_ = 0xffffffffffffffff;
    auVar19 = _pcpyld(auVar9,auVar29);
    *puVar30 = *puVar30 & auVar19._0_8_ | 0x500000000;
    sVar26 = this->i16_158;
    iVar17 = (int)sVar26;
    if ((int)(((long)sVar26 << 0x30) >> 0x3f) < 0) {
      iVar17 = sVar26 + 3;
    }
    fVar32 = (float)(iVar17 >> 2) * fRadian;
    fStack_6c = (float)(int)this->i16_15a * fRadian +
                fVar32 * (float)(this->i8_149 + 1);
    bVar14 = this->u8_149;
    while( true ) {
      puVar31 = puVar30 + 1;
      if (3 < bVar14) break;
      fVar33 = cosf(fStack_6c);
      fVar33 = this->f32_15c + this->f32_164 * fVar33;
      if (fVar33 < 2.1474836e+09) {
        uVar24 = (undefined1)(int)fVar33;
        uVar25 = (undefined1)((uint)(int)fVar33 >> 8);
      }
      else {
        uVar16 = (int)(fVar33 - 2.1474836e+09) & 0xffff;
        uVar24 = (undefined1)uVar16;
        uVar25 = (undefined1)(uVar16 >> 8);
      }
      *(short *)puVar31 = sVar13 + CONCAT11(uVar25,uVar24) * 0x10;
      fVar33 = sinf(fStack_6c);
      fVar33 = this->f32_160 + this->f32_164 * -fVar33;
      if (fVar33 < 2.1474836e+09) {
        uVar24 = (undefined1)(int)fVar33;
        uVar25 = (undefined1)((uint)(int)fVar33 >> 8);
      }
      else {
        uVar16 = (int)(fVar33 - 2.1474836e+09) & 0xffff;
        uVar24 = (undefined1)uVar16;
        uVar25 = (undefined1)(uVar16 >> 8);
      }
      *(short *)((int)puVar30 + 10) = sVar3 + CONCAT11(uVar25,uVar24) * 0x10;
      auVar10._8_8_ = in_v1_udw;
      auVar10._0_8_ = 0xffffffff;
      auVar12._8_8_ = in_a0_udw;
      auVar12._0_8_ = 0xffffffffffffffff;
      auVar19 = _pcpyld(auVar12,auVar10);
      *puVar31 = *puVar31 & auVar19._0_8_ | 0x500000000;
      fStack_6c = fStack_6c + fVar32;
      bVar14 = bVar14 + 1;
      puVar30 = puVar31;
    }
  }
  if (CApp::camera != 0) {
    uVar18 = CApp::camera->u64_60;
    puVar2->u64_64 = uVar18;
    puVar2->u64_c = uVar18;
  }
  (**(code **)(this->i32_f0 + 0x14))(cVar27 + -0x18,iStack_30,iStack_20,param_4);
  *pbVar15 = *pbVar15 & 0x80;
  return;
}

// JP: 0x0028c950  Connect__10SoulEnergyFP4_QWD  =  SoulEnergy::Connect
void SoulEnergy::Connect(int this,undefined4 param_2)

{
  undefined4 uVar1;
  
  uVar1 = (**(code **)(this->i32_60 + 0x18))(this + 0x58,param_2);
  uVar1 = (**(code **)(this->i32_90 + 0x18))(this + 0x88,uVar1);
  uVar1 = MenuPacket::ConnectPacket(this + 0x3c,uVar1);
  uVar1 = (**(code **)(this->i32_c0 + 0x18))(this + 0xb8,uVar1);
  MenuPacket::ConnectPacket(this + 0x124,uVar1);
  return;
}

// JP: 0x0028ca00  Destroy__10SoulEnergyFv  =  SoulEnergy::Destroy
void SoulEnergy::Destroy(int this)

{
  MenuPacket::DestroyPacket(this + 0x3c);
  (**(code **)(this->i32_60 + 0x1c))();
  (**(code **)(this->i32_90 + 0x1c))();
  (**(code **)(this->i32_c0 + 0x1c))();
  (**(code **)(this->i32_f0 + 0x1c))();
  return;
}

// JP: 0x0028ca90  Clear__10SoulEnergyFv  =  SoulEnergy::Clear
void SoulEnergy::Clear(int this)

{
  MenuPlace::Clear(this);
  MenuPacket::ClearPacket(this + 0x3c);
  (**(code **)(this->i32_60 + 0x20))();
  (**(code **)(this->i32_90 + 0x20))();
  (**(code **)(this->i32_c0 + 0x20))();
  (**(code **)(this->i32_f0 + 0x20))();
  this->u8_149 = 0;
  this->u8_148 = 0x80;
  this->u32_14c = 0;
  this->u32_150 = 0;
  this->u16_14a = 0;
  return;
}
