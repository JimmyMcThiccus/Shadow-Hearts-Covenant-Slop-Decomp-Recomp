// decomp/D/Puti.c — cleaned Ghidra output (SLPM_602.19, Metrowerks MIPS), Shadow Hearts: Covenant JP demo.
// Field accesses are shown as this->T_off (T = u8/u16/u32/f32/i32/p, off = hex offset);
// JRing fields are named from the recovered struct. See notes/D/*.md for layouts.
// CAVEAT: when the base pointer is a float*/int*/short*, the number in `T_off` is an ELEMENT offset (byte offset = off*sizeof(elem)).
// `this` is the C++ this pointer (param_1); the Metrowerks ABI passes it in a0.

// JP: 0x0025ca60  __ct__10PutiObjectFiPv  =  PutiObject::PutiObject
int PutiObject::PutiObject(int this,undefined4 param_2)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  int iVar4;
  undefined1 auStack_60 [16];
  undefined1 auStack_50 [16];
  undefined1 auStack_40 [16];
  int iStack_30;
  undefined4 uStack_20;
  
  iStack_30 = this;
  uStack_20 = param_2;
  CList::CList(this);
  *(undefined1 **)(iStack_30 + 0x1e4) = PutiObject::__vt;
  iVar4 = iStack_30 + 0x20;
  do {
    tagPutiEnv::tagPutiEnv(iVar4);
    iVar4 = iVar4 + 0x30;
  } while (iVar4 != iStack_30 + 0x80);
  FVector::FVector(iStack_30 + 0xa0);
  FVector::FVector(iStack_30 + 0xb0);
  FVector::FVector(iStack_30 + 0xe0);
  FVector::FVector(iStack_30 + 0xf0);
  FVector::FVector(iStack_30 + 0x100);
  FVector::FVector(iStack_30 + 0x110);
  FVector::FVector(iStack_30 + 0x120);
  FVector::FVector(iStack_30 + 0x130);
  iVar4 = iStack_30 + 0x140;
  do {
    FVector::FVector(iVar4);
    iVar4 = iVar4 + 0x10;
  } while (iVar4 != iStack_30 + 0x180);
  FVector::FVector(iStack_30 + 0x180);
  FVector::FVector(iStack_30 + 400);
  FVector::FVector(iStack_30 + 0x1a0);
  FVector::FVector(iStack_30 + 0x1b0);
  FVector::FVector(iStack_30 + 0x1c0);
  FVector::FVector(iStack_30 + 0x1d0);
  iStack_30->u32_8c = uStack_20;
  iVar4 = iStack_30->i32_8c;
  uVar3 = __nwa(iVar4 * 0x10 + 0x10);
  uVar2 = __construct_new_array(uVar3,0x224b30,0,0x10,iVar4);
  iStack_30->u32_c = uVar2;
  iVar4 = iStack_30->i32_8c;
  uVar3 = __nwa(iVar4 * 0x10 + 0x10);
  uVar2 = __construct_new_array(uVar3,0x224b30,0,0x10,iVar4);
  iStack_30->u32_10 = uVar2;
  memset(*(void **)(iStack_30 + 0xc),0,(long)(iStack_30->i32_8c << 4));
  memset(*(void **)(iStack_30 + 0x10),0,(long)(iStack_30->i32_8c << 4));
  **(undefined4 **)(iStack_30 + 0x10) = 0x60000000;
  **(undefined4 **)(iStack_30 + 0xc) = 0x60000000;
  tagPutiFlags::Init(iStack_30 + 0x14);
  iStack_30->u32_90 = 0;
  iStack_30->u32_1e0 = 100;
  iStack_30->u32_94 = 0;
  iStack_30->u32_c4 = 0;
  iStack_30->u32_c0 = 0;
  uVar3 = tagPutiUV::__as(iStack_30 + 0xd8,iStack_30 + 0xc0);
  uVar3 = tagPutiUV::__as(iStack_30 + 0xd0,uVar3);
  tagPutiUV::__as(iStack_30 + 200,uVar3);
  uVar3 = FVector::FVector(0x43000000,0x43000000,0x43000000,0x43000000,auStack_40);
  FVector::__as(iStack_30 + 0x1d0,uVar3);
  uVar3 = FVector::FVector(0x3f800000,0x3f800000,0x3f800000,0x3f800000,auStack_50);
  FVector::__as(iStack_30 + 0x120,uVar3);
  uVar3 = FVector::FVector(0,0,0,0x3f800000,auStack_60);
  FVector::__as(iStack_30 + 0x130,uVar3);
  iStack_30->u64_20 = 0x1000000000000002;
  iStack_30->u64_28 = 0xe;
  iStack_30->u64_30 = 0x48;
  iStack_30->u64_38 = 0x42;
  iStack_30->u64_40 = 0x73001;
  iStack_30->u64_48 = 0x47;
  tagPutiEnv::__as(iStack_30 + 0x50,iStack_30 + 0x20);
  puVar1 = *(undefined4 **)(iStack_30 + 0xc);
  iVar4 = iStack_30->i32_10;
  *puVar1 = 0x30000003;
  puVar1[1] = iStack_30 + 0x20;
  puVar1[3] = 0x50000003;
  _QWD::__as(iVar4,puVar1);
  iVar4->i32_4 = iStack_30 + 0x50;
  *(undefined4 **)(iStack_30 + 0x80) = puVar1 + 4;
  iStack_30->i32_84 = iVar4 + 0x10;
  return iStack_30;
}

// JP: 0x0025cf40  __as__10tagPutiEnvFRC10tagPutiEnv  =  tagPutiEnv::__as
int tagPutiEnv::__as(int this,int param_2)

{
  _QWD::__as(this,param_2);
  _QWD::__as(this + 0x10,param_2 + 0x10);
  _QWD::__as(this + 0x20,param_2 + 0x20);
  return this;
}

// JP: 0x0025d0c0  __as__9tagPutiUVFRC9tagPutiUV  =  tagPutiUV::__as
undefined4 * tagPutiUV::__as(undefined4 *this,undefined4 *param_2)

{
  *this = *param_2;
  this[1] = param_2[1];
  return this;
}

// JP: 0x0025d100  Init__12tagPutiFlagsFv  =  tagPutiFlags::Init
void tagPutiFlags::Init(ushort *this)

{
  *(byte *)this = (byte)*this & 0xef;
  *(byte *)this = (byte)*this & 0xf7;
  *(byte *)this = (byte)*this & 0xfb;
  *(byte *)this = (byte)*this & 0xfd;
  *(byte *)this = (byte)*this & 0xfe;
  *this = *this & 0xe01f | 0x1fe0;
  return;
}

// JP: 0x0025d200  __ct__10tagPutiEnvFv  =  tagPutiEnv::tagPutiEnv
int tagPutiEnv::tagPutiEnv(int this)

{
  _QWD::_QWD(this);
  _QWD::_QWD(this + 0x10);
  _QWD::_QWD(this + 0x20);
  return this;
}

// JP: 0x0025d250  __dt__10PutiObjectFv  =  PutiObject::~PutiObject
int * PutiObject::~PutiObject(int *this,short param_2)

{
  int iVar1;
  
  if (this != (int *)0x0) {
    this[0x79] = (int)PutiObject::__vt;
    if (this[3] != 0) {
      if (this[3] != 0) {
        __dla(this[3] + -0x10);
      }
      this[3] = 0;
    }
    if (this[4] != 0) {
      if (this[4] != 0) {
        __dla(this[4] + -0x10);
      }
      this[4] = 0;
    }
    if (*this != 0) {
      iVar1 = *this;
      if (iVar1 != 0) {
        (**(code **)(iVar1->i32_1e4 + 0x34))(iVar1,1);
      }
    }
    CList::~CList(this,0);
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x0025d380  getPacket__10PutiObjectFv  =  PutiObject::getPacket
undefined4 PutiObject::getPacket(int this)

{
  return *(undefined4 *)(this + (VIF1Prim::m_Env & 1) * 4 + 0xc);
}

// JP: 0x0025d3b0  UpdateFrame__10PutiObjectFv  =  PutiObject::UpdateFrame
undefined4 PutiObject::UpdateFrame(int this)

{
  undefined4 uVar1;
  
  this->i32_90 = this->i32_90 + 1;
  if ((this->i32_1e0 == -1) || (this->i32_90 < this->i32_1e0)) {
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

// JP: 0x0025d420  Calculate__10PutiObjectFv  =  PutiObject::Calculate
bool PutiObject::Calculate(int this)

{
  long lVar1;
  
  lVar1 = (**(code **)(this->i32_1e4 + 8))();
  if (lVar1 != 0) {
    (**(code **)(this->i32_1e4 + 0x20))();
    (**(code **)(this->i32_1e4 + 0x10))();
    (**(code **)(this->i32_1e4 + 0x14))();
    (**(code **)(this->i32_1e4 + 0xc))();
    (**(code **)(this->i32_1e4 + 0x18))();
    (**(code **)(this->i32_1e4 + 0x1c))();
  }
  return lVar1 != 0;
}

// JP: 0x0025d4f0  CalcColor__10PutiObjectFv  =  PutiObject::CalcColor
void PutiObject::CalcColor(void)

{
  return;
}

// JP: 0x0025d500  CalcUv__10PutiObjectFv  =  PutiObject::CalcUv
void PutiObject::CalcUv(int this)

{
  int iVar1;
  int iVar2;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  int iStack_10;
  
  if ((long)((ulong)this->u8_14 << 0x3d) < 0) {
    for (iVar2 = 0; iVar2 < 4; iVar2 = iVar2 + 1) {
      iVar1 = this + iVar2 * 8;
      iVar1->f32_c0 = iVar1->f32_c0 + this->f32_1a0;
      iVar1 = this + iVar2 * 8;
      iVar1->f32_c4 = iVar1->f32_c4 + this->f32_1a4;
    }
    if ((1.0 < this->f32_c0) && (1.0 < this->f32_d8)) {
      this->f32_c0 = this->f32_c0 - 1.0;
      this->f32_c8 = this->f32_c8 - 1.0;
      this->f32_d0 = this->f32_d0 - 1.0;
      this->f32_d8 = this->f32_d8 - 1.0;
    }
    if ((1.0 < this->f32_c4) && (1.0 < this->f32_dc)) {
      this->f32_c4 = this->f32_c4 - 1.0;
      this->f32_cc = this->f32_cc - 1.0;
      this->f32_d4 = this->f32_d4 - 1.0;
      this->f32_dc = this->f32_dc - 1.0;
    }
    if ((this->f32_c0 < 0.0) && (this->f32_d8 < 0.0)) {
      this->f32_c0 = this->f32_c0 + 1.0;
      this->f32_c8 = this->f32_c8 + 1.0;
      this->f32_d0 = this->f32_d0 + 1.0;
      this->f32_d8 = this->f32_d8 + 1.0;
    }
    if ((this->f32_c4 < 0.0) && (this->f32_dc < 0.0)) {
      this->f32_c4 = this->f32_c4 + 1.0;
      this->f32_cc = this->f32_cc + 1.0;
      this->f32_d4 = this->f32_d4 + 1.0;
      this->f32_dc = this->f32_dc + 1.0;
    }
  }
  if ((long)((ulong)this->u8_14 << 0x3c) < 0) {
    iStack_10 = this;
    PutiTexAnim::GetUVA
              (*(undefined4 *)(this->i32_8 + 0x30),this->u32_90,
               &uStack_14,&uStack_18,&uStack_1c,&uStack_20,this + 0x1dc);
    iStack_10->u32_c0 = uStack_14;
    iStack_10->u32_c4 = uStack_18;
    iStack_10->u32_c8 = uStack_14;
    iStack_10->u32_cc = uStack_20;
    iStack_10->u32_d0 = uStack_1c;
    iStack_10->u32_d4 = uStack_18;
    iStack_10->u32_d8 = uStack_1c;
    iStack_10->u32_dc = uStack_20;
  }
  return;
}

// JP: 0x0025d910  CalcGravity__10PutiObjectFv  =  PutiObject::CalcGravity
void PutiObject::CalcGravity(int this)

{
  if ((long)((ulong)this->u8_14 << 0x3e) < 0) {
    FVector::__apl(this + 0xf0,this + 0x1b0);
    if (((0.0 <= this->f32_1c0) &&
        (this->f32_1c0 < this->f32_f0)) ||
       ((this->f32_1c0 < 0.0 &&
        (this->f32_f0 < this->f32_1c0)))) {
      this->u32_f0 = this->u32_1c0;
    }
    if (((0.0 <= this->f32_1c4) &&
        (this->f32_1c4 < this->f32_f4)) ||
       ((this->f32_1c4 < 0.0 &&
        (this->f32_f4 < this->f32_1c4)))) {
      this->u32_f4 = this->u32_1c4;
    }
    if (((0.0 <= this->f32_1c8) &&
        (this->f32_1c8 < this->f32_f8)) ||
       ((this->f32_1c8 < 0.0 &&
        (this->f32_f8 < this->f32_1c8)))) {
      this->u32_f8 = this->u32_1c8;
    }
    FVector::__apl(this + 0xe0,this + 0xf0);
  }
  return;
}

// JP: 0x0025db20  CalcSpeed__10PutiObjectFv  =  PutiObject::CalcSpeed
void PutiObject::CalcSpeed(int this)

{
  FVector::__apl(this + 0xb0,this + 0x180);
  if (((0.0 <= this->f32_190) &&
      (this->f32_190 < this->f32_b0)) ||
     ((this->f32_190 < 0.0 && (this->f32_b0 < this->f32_190)))
     ) {
    this->u32_b0 = this->u32_190;
  }
  if (((0.0 <= this->f32_194) &&
      (this->f32_194 < this->f32_b4)) ||
     ((this->f32_194 < 0.0 &&
      (this->f32_b4 < this->f32_194)))) {
    this->u32_b4 = this->u32_194;
  }
  if (((0.0 <= this->f32_198) &&
      (this->f32_198 < this->f32_b8)) ||
     ((this->f32_198 < 0.0 &&
      (this->f32_b8 < this->f32_198)))) {
    this->u32_b8 = this->u32_198;
  }
  FVector::__apl(this + 0xa0,this + 0xb0);
  return;
}

// JP: 0x0025dcf0  CalcPos__10PutiObjectFv  =  PutiObject::CalcPos
void PutiObject::CalcPos(int this)

{
  this->f32_100 =
       this->f32_100 + this->f32_a0 + this->f32_e0;
  this->f32_104 =
       this->f32_104 + this->f32_a4 + this->f32_e4;
  this->f32_108 =
       this->f32_108 + this->f32_a8 + this->f32_e8;
  return;
}

// JP: 0x0025dd70  CalcVertex__10PutiObjectFv  =  PutiObject::CalcVertex
void PutiObject::CalcVertex(int this)

{
  undefined8 uVar1;
  int iVar2;
  undefined1 auStack_e0 [16];
  undefined1 auStack_d0 [16];
  undefined1 auStack_c0 [16];
  undefined1 auStack_b0 [16];
  undefined1 auStack_a0 [16];
  undefined1 auStack_90 [16];
  undefined1 auStack_80 [16];
  undefined1 auStack_70 [64];
  undefined1 auStack_30 [12];
  undefined4 uStack_24;
  float fStack_1c;
  float fStack_18;
  float fStack_14;
  int iStack_10;
  
  fStack_14 = (this->f32_110 / 2.0) * this->f32_120;
  fStack_18 = (this->f32_114 / 2.0) * this->f32_124;
  fStack_1c = (this->f32_118 / 2.0) * this->f32_128;
  iStack_10 = this;
  uVar1 = FVector::FVector(-fStack_14,-fStack_18,fStack_1c,0x3f800000,auStack_80);
  FVector::__as(iStack_10 + 0x140,uVar1);
  uVar1 = FVector::FVector(-fStack_14,fStack_18,-fStack_1c,0x3f800000,auStack_90);
  FVector::__as(iStack_10 + 0x150,uVar1);
  uVar1 = FVector::FVector(fStack_14,-fStack_18,fStack_1c,0x3f800000,auStack_a0);
  FVector::__as(iStack_10 + 0x160,uVar1);
  uVar1 = FVector::FVector(fStack_14,fStack_18,-fStack_1c,0x3f800000,auStack_b0);
  FVector::__as(iStack_10 + 0x170,uVar1);
  FVector::FVector(auStack_30,iStack_10 + 0x100);
  Matrix::Matrix(auStack_70);
  Matrix::RotMatrix(auStack_70,iStack_10 + 0x130);
  uStack_24 = 0;
  if ((iStack_10->u8_14 & 1) == 0) {
    for (iVar2 = 0; iVar2 < 4; iVar2 = iVar2 + 1) {
      Matrix::ApplyMatrix(auStack_e0,auStack_70,iStack_10 + iVar2 * 0x10 + 0x140);
      FVector::__as(iStack_10 + iVar2 * 0x10 + 0x140,auStack_e0);
      FVector::__apl(iStack_10 + iVar2 * 0x10 + 0x140,auStack_30);
    }
  }
  else {
    for (iVar2 = 0; iVar2 < 4; iVar2 = iVar2 + 1) {
      Matrix::ApplyMatrix(auStack_c0,auStack_70,iStack_10 + iVar2 * 0x10 + 0x140);
      FVector::__as(iStack_10 + iVar2 * 0x10 + 0x140,auStack_c0);
      Matrix::ApplyMatrix(auStack_d0,0x4213c0,iStack_10 + iVar2 * 0x10 + 0x140);
      FVector::__as(iStack_10 + iVar2 * 0x10 + 0x140,auStack_d0);
      FVector::__apl(iStack_10 + iVar2 * 0x10 + 0x140,auStack_30);
    }
  }
  return;
}

// JP: 0x0025e130  GetPos__10PutiObjectFfffR7FVector  =  PutiObject::GetPos
void PutiObject::GetPos
               (float this,float param_2,float param_3,undefined4 param_4,undefined4 param_5)

{
  float fVar1;
  float fStack_60;
  float fStack_5c;
  float fStack_58;
  undefined4 uStack_50;
  float fStack_40;
  float fStack_30;
  float fStack_20;
  undefined4 uStack_10;
  
  uStack_50 = param_4;
  fStack_40 = this;
  fStack_30 = param_2;
  fStack_20 = param_3;
  uStack_10 = param_5;
  FVector::FVector(&fStack_60,param_5);
  fVar1 = (float)Rand1();
  fStack_60 = fStack_60 + fStack_40 * fVar1;
  fVar1 = (float)Rand1();
  fStack_5c = fStack_5c + fStack_30 * fVar1;
  fVar1 = (float)Rand1();
  fStack_58 = fStack_58 + fStack_20 * fVar1;
  FVector::FVector(uStack_50,&fStack_60);
  return;
}

// JP: 0x0025e230  SetRegAlpha__10PutiObjectFUl  =  PutiObject::SetRegAlpha
void PutiObject::SetRegAlpha(int this,undefined8 param_2)

{
  this->u64_60 = param_2;
  this->u64_30 = param_2;
  return;
}

// JP: 0x0025e260  SetRegTest__10PutiObjectFUl  =  PutiObject::SetRegTest
void PutiObject::SetRegTest(int this,undefined8 param_2)

{
  this->u64_70 = param_2;
  this->u64_40 = param_2;
  return;
}

// JP: 0x0025e290  RotTransPer__10PutiObjectFP7FVectorP4_QWD  =  PutiObject::RotTransPer
undefined4
PutiObject::RotTransPer
          (undefined8 this,undefined1 (*param_2) [16],undefined1 (*param_3) [16])

{
  undefined8 uVar1;
  undefined1 in_vf0 [16];
  undefined1 auVar2 [16];
  undefined1 auVar3 [16];
  undefined1 auVar4 [16];
  undefined1 auVar5 [16];
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  undefined1 auVar8 [16];
  undefined4 uVar9;
  undefined1 auStack_80 [16];
  undefined1 auStack_70 [16];
  undefined1 auStack_60 [16];
  undefined1 auStack_50 [16];
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [16];
  undefined1 auStack_20 [16];
  undefined1 auStack_10 [16];
  
  GsxCamera::GetViewScreenMatrix(auStack_40,CApp::camera);
  FVector::FVector(auStack_60);
  FVector::FVector(auStack_50);
  uVar1 = FVector::FVector(0x45000000,0x45000000,0x4affe3d0,0,auStack_70);
  FVector::__as(auStack_60,uVar1);
  uVar1 = FVector::FVector(0,0,0x39800000,0x44ffe000,auStack_80);
  FVector::__as(auStack_50,uVar1);
  auVar7 = _lqc2(auStack_60);
  auVar8 = _lqc2(auStack_50);
  auVar2 = _lqc2(auStack_40);
  auVar3 = _lqc2(auStack_30);
  auVar4 = _lqc2(auStack_20);
  auVar5 = _lqc2(auStack_10);
  auVar6 = _lqc2(*param_2);
  _vmulabc(auVar2,auVar6);
  _vmaddabc(auVar3,auVar6);
  _vmaddabc(auVar4,auVar6);
  auVar2 = _vmaddbc(auVar5,auVar6);
  _vdiv(in_vf0,0,auVar2,0);
  uVar9 = _vwaitq();
  auVar2 = _vmulq(auVar2,uVar9);
  auVar3 = _vsub(auVar2,auVar7);
  auVar3 = _vmul(auVar3,auVar8);
  _vclip(auVar3,auVar8);
  _vftoi4(auVar2);
  auVar2 = _vmulq(in_vf0,uVar9);
  _vnop();
  _vnop();
  _vnop();
  auVar2 = _sqc2(auVar2);
  *param_3 = auVar2;
  uVar9 = *(undefined4 *)(*param_3 + 0xc);
  *(undefined4 *)(*param_3 + 0xc) = 0;
  return uVar9;
}

// JP: 0x0025e3d0  ClipFlag__10PutiObjectFv  =  PutiObject::ClipFlag
undefined4 PutiObject::ClipFlag(void)

{
  undefined8 uVar1;
  undefined4 in_vc2;
  
  uVar1 = _cfc2(in_vc2);
  return (int)uVar1;
}

// JP: 0x0025e3f0  SetPacket__10PutiObjectFv  =  PutiObject::SetPacket
void PutiObject::SetPacket(int this)

{
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  undefined4 *puVar1;
  undefined8 *puVar2;
  float *pfVar3;
  uint *puVar4;
  ulong uVar5;
  undefined8 uVar6;
  int iVar7;
  float fVar8;
  uint uVar9;
  undefined1 auStack_30 [12];
  undefined4 uStack_24;
  float fStack_14;
  int iStack_10;
  
  iStack_10 = this;
  puVar1 = (undefined4 *)PutiObject::GetAddress(this);
  *puVar1 = in_zero_lo;
  puVar1[1] = in_zero_hi;
  puVar1[2] = in_zero_udw;
  puVar1[3] = in_register_0000000c;
  *puVar1 = &DAT_1000000d;
  puVar1[3] = 0x5000000d;
  puVar2 = (undefined8 *)PutiObject::AddAddress(iStack_10);
  *puVar2 = 0x302a400000008004;
  puVar2[1] = 0x512;
  pfVar3 = (float *)PutiObject::AddAddress(iStack_10);
  _QWD::_QWD(auStack_30);
  for (iVar7 = 0; iVar7 < 4; iVar7 = iVar7 + 1) {
    fStack_14 = (float)PutiObject::RotTransPer
                                 (iStack_10,iStack_10 + iVar7 * 0x10 + 0x140,auStack_30);
    uVar5 = PutiObject::ClipFlag(iStack_10);
    *pfVar3 = *(float *)(iStack_10 + iVar7 * 8 + 0xc0) * fStack_14;
    pfVar3[1] = *(float *)(iStack_10 + iVar7 * 8 + 0xc4) * fStack_14;
    pfVar3[2] = fStack_14;
    puVar4 = (uint *)PutiObject::AddAddress(iStack_10);
    fVar8 = iStack_10->f32_1d0;
    if (fVar8 < 2.1474836e+09) {
      uVar9 = (uint)fVar8;
    }
    else {
      uVar9 = (int)(fVar8 - 2.1474836e+09) | 0x80000000;
    }
    *puVar4 = uVar9;
    fVar8 = iStack_10->f32_1d4;
    if (fVar8 < 2.1474836e+09) {
      uVar9 = (uint)fVar8;
    }
    else {
      uVar9 = (int)(fVar8 - 2.1474836e+09) | 0x80000000;
    }
    puVar4[1] = uVar9;
    fVar8 = iStack_10->f32_1d8;
    if (fVar8 < 2.1474836e+09) {
      uVar9 = (uint)fVar8;
    }
    else {
      uVar9 = (int)(fVar8 - 2.1474836e+09) | 0x80000000;
    }
    puVar4[2] = uVar9;
    fVar8 = iStack_10->f32_1dc;
    if (fVar8 < 2.1474836e+09) {
      uVar9 = (uint)fVar8;
    }
    else {
      uVar9 = (int)(fVar8 - 2.1474836e+09) | 0x80000000;
    }
    puVar4[3] = uVar9;
    uVar6 = PutiObject::AddAddress(iStack_10);
    if ((uVar5 & 0x3ffff) != 0) {
      uStack_24 = 0x8000;
    }
    _QWD::__as(uVar6,auStack_30);
    pfVar3 = (float *)PutiObject::AddAddress(iStack_10);
  }
  return;
}

// JP: 0x0025e6c0  AddAddress__10PutiObjectFv  =  PutiObject::AddAddress
undefined4 PutiObject::AddAddress(int this)

{
  this->i32_88 = this->i32_88 + 0x10;
  return this->u32_88;
}

// JP: 0x0025e6f0  GetAddress__10PutiObjectFv  =  PutiObject::GetAddress
undefined4 PutiObject::GetAddress(int this)

{
  return this->u32_88;
}

// JP: 0x0025e7c0  __ct__8PutiPrimFi  =  PutiPrim::PutiPrim
VIF1Prim * PutiPrim::PutiPrim(VIF1Prim *this,int param_2)

{
  uint uVar1;
  
  VIF1Prim::VIF1Prim(this);
  DelayDeleteObject::DelayDeleteObject(this + 1);
  this->pVptr = PutiPrim::__vt;
  this[1].dwEnv = 0x404e00;
  this[2].dw_unk0 = 0;
  this[2].dw_unk4 = 0;
  this[2].dwEnv = 0;
  this[2].bFlags = 0;
  this[2].b_pad0d = 0;
  this[2].nZvolume = 0;
  this[2].pVptr = (void *)0x0;
  this[3].dw_unk0 = 0xffffffff;
  this[3].dw_unk4 = 0;
  uVar1 = __nwa((param_2 + 10) * 0x10);
  this->dw_unk0 = uVar1;
  uVar1 = __nwa((param_2 + 10) * 0x10);
  this->dw_unk4 = uVar1;
  sceGsZbuf::__as(&this[1].bFlags,CApp::camera + 0x60);
  return this;
}

// JP: 0x0025e8e0  __dt__8PutiPrimFv  =  PutiPrim::~PutiPrim
int * PutiPrim::~PutiPrim(int *this,short param_2)

{
  int iVar1;
  
  if (this != (int *)0x0) {
    this[4] = (int)PutiPrim::__vt;
    this[7] = 0x404e00;
    if (this[10] != 0) {
      iVar1 = this[10];
      if (iVar1 != 0) {
        (**(code **)(iVar1->i32_1e4 + 0x34))(iVar1,1);
      }
      this[10] = 0;
    }
    if (this[0xb] != 0) {
      PutiTexture::~PutiTexture(this[0xb],1);
      this[0xb] = 0;
    }
    if (this[0xc] != 0) {
      PutiTexAnim::~PutiTexAnim(this[0xc],1);
      this[0xc] = 0;
    }
    if (this[0xd] != 0) {
      DelayPutiObject::~DelayPutiObject(this[0xd],1);
      this[0xd] = 0;
    }
    if (*this != 0) {
      __dla(*this);
      *this = 0;
    }
    if (this[1] != 0) {
      __dla(this[1]);
      this[1] = 0;
    }
    DelayDeleteObject::~DelayDeleteObject(this + 5,0);
    VIF1Prim::~VIF1Prim(this,0);
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x0025eaa0  SetTexture__8PutiPrimFP12tagPTexParamUc  =  PutiPrim::SetTexture
undefined8
PutiPrim::SetTexture(int this,undefined4 param_2,undefined1 param_3)

{
  long lVar1;
  undefined8 uVar2;
  
  lVar1 = __nw(0x70);
  uVar2 = 0;
  if (lVar1 != 0) {
    uVar2 = PutiTexture::PutiTexture(lVar1);
  }
  PutiTexture::Create(uVar2,param_3,param_2);
  if (this->i32_2c == 0) {
    this->i32_2c = (int)uVar2;
  }
  else {
    CList::Add(this->u32_2c,uVar2);
  }
  return uVar2;
}

// JP: 0x0025eb90  SetState__8PutiPrimFi  =  PutiPrim::SetState
void PutiPrim::SetState(int this,undefined4 param_2)

{
  int iVar1;
  
  for (iVar1 = this->i32_28; iVar1 != 0; iVar1 = CList::GetNext(iVar1)) {
    (**(code **)(iVar1->i32_1e4 + 0x2c))(iVar1,param_2);
  }
  return;
}

// JP: 0x0025ec20  OnChangeState__10PutiObjectFi  =  PutiObject::OnChangeState
void PutiObject::OnChangeState(int this,undefined4 param_2)

{
  this->u32_94 = param_2;
  return;
}

// JP: 0x0025ec50  getPacket__8PutiPrimFv  =  PutiPrim::getPacket
undefined4 PutiPrim::getPacket(int this)

{
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  ulong uVar4;
  undefined4 *puVar5;
  
  iVar3 = this->i32_28;
  puVar5 = *(undefined4 **)(this + (VIF1Prim::m_Env & 1) * 4);
  *puVar5 = in_zero_lo;
  puVar5[1] = in_zero_hi;
  puVar5[2] = in_zero_udw;
  puVar5[3] = in_register_0000000c;
  *puVar5 = &DAT_10000002;
  puVar5[3] = 0x50000002;
  puVar5->u64_4 = 0x1000000000008001;
  puVar5->u64_6 = 0xe;
  puVar5->u64_8 = this->u64_20;
  puVar5->u64_a = 0x4e;
  puVar5 = puVar5 + 0xc;
  uVar4 = 0xff;
  for (; iVar3 != 0; iVar3 = CList::GetNext(iVar3)) {
    if ((uVar4 != ((ulong)iVar3->u16_14 & 0x1fff) >> 5) &&
       (this->i32_2c != 0)) {
      uVar4 = ((ulong)iVar3->u16_14 & 0x1fff) >> 5;
      iVar1 = PutiTexture::FindTexture
                        (this->u32_2c,
                         ((ulong)iVar3->u16_14 & 0x1fff) >> 5);
      *puVar5 = in_zero_lo;
      puVar5[1] = in_zero_hi;
      puVar5[2] = in_zero_udw;
      puVar5[3] = in_register_0000000c;
      *puVar5 = 0x50000000;
      uVar2 = CPacket::GetBuffer(iVar1->u32_8);
      puVar5[1] = uVar2;
      puVar5[3] = 0x13000000;
      puVar5 = puVar5 + 4;
    }
    PutiObject::OpenPacket(iVar3);
    (**(code **)(iVar3->i32_1e4 + 0x28))();
    PutiObject::ClosePacket(iVar3);
    *puVar5 = in_zero_lo;
    puVar5[1] = in_zero_hi;
    puVar5[2] = in_zero_udw;
    puVar5[3] = in_register_0000000c;
    *puVar5 = 0x50000000;
    uVar2 = (**(code **)(iVar3->i32_1e4 + 0x30))();
    puVar5[1] = uVar2;
    puVar5 = puVar5 + 4;
  }
  *puVar5 = in_zero_lo;
  puVar5[1] = in_zero_hi;
  puVar5[2] = in_zero_udw;
  puVar5[3] = in_register_0000000c;
  *puVar5 = 0x60000002;
  puVar5[3] = 0x50000002;
  puVar5->u64_4 = 0x1000000000008001;
  puVar5->u64_6 = 0xe;
  puVar5->u64_8 = CApp::camera->u64_60;
  puVar5->u64_a = 0x4e;
  return *(undefined4 *)(this + (VIF1Prim::m_Env & 1) * 4);
}

// JP: 0x0025ee80  ClosePacket__10PutiObjectFv  =  PutiObject::ClosePacket
void PutiObject::ClosePacket(int this)

{
  **(undefined4 **)(this + 0x88) = 0x60000000;
  return;
}

// JP: 0x0025eeb0  OpenPacket__10PutiObjectFv  =  PutiObject::OpenPacket
void PutiObject::OpenPacket(int this)

{
  this->u32_88 = *(undefined4 *)(this + (VIF1Prim::m_Env & 1) * 4 + 0x80);
  return;
}

// JP: 0x0025ef10  Delete__8PutiPrimFv  =  PutiPrim::Delete
void PutiPrim::Delete(int this)

{
  PutiManager::RemovePrim(PutiManager::ourManager,this);
  (**(code **)(this->i32_1c + 0xc))();
  return;
}

// JP: 0x0025ef60  Update__8PutiPrimFv  =  PutiPrim::Update
void PutiPrim::Update(int this)

{
  int iVar1;
  long lVar2;
  int iVar3;
  
  PutiPrim::DelayAdd(this);
  if ((this->i32_3c != -1) &&
     (this->i32_40 = this->i32_40 + 1,
     this->i32_3c <= this->i32_40)) {
    (**(code **)(this->i32_10 + 0x20))();
    this->u32_40 = 0;
  }
  iVar1 = this->i32_28;
  while (iVar3 = iVar1, iVar3 != 0) {
    lVar2 = (**(code **)(iVar3->i32_1e4 + 0x24))();
    if ((lVar2 == 0) && (lVar2 = (**(code **)(this->i32_10 + 0x24))(), lVar2 != 0)) {
      iVar1 = CList::GetNext(iVar3);
      PutiPrim::RemoveObject(this,iVar3);
      if (iVar3 != 0) {
        (**(code **)(iVar3->i32_1e4 + 0x34))(iVar3,1);
      }
    }
    else {
      iVar1 = CList::GetNext(iVar3);
    }
  }
  return;
}

// JP: 0x0025f0b0  OnDelete__8PutiPrimFv  =  PutiPrim::OnDelete
undefined4 PutiPrim::OnDelete(void)

{
  return 1;
}

// JP: 0x0025f0d0  TimeCall__8PutiPrimFv  =  PutiPrim::TimeCall
void PutiPrim::TimeCall(void)

{
  return;
}

// JP: 0x0025f0e0  AddObject__8PutiPrimFP10PutiObject  =  PutiPrim::AddObject
void PutiPrim::AddObject(int this,int param_2)

{
  int iVar1;
  
  param_2->i32_8 = this;
  if (this->i32_28 == 0) {
    this->i32_28 = param_2;
  }
  else {
    for (iVar1 = this->i32_28; iVar1 != 0; iVar1 = CList::GetNext(iVar1)) {
      if (((ulong)param_2->u16_14 & 0x1fff) >> 5 <
          ((ulong)iVar1->u16_14 & 0x1fff) >> 5) {
        CList::InsertAfter(iVar1,param_2);
        return;
      }
    }
    CList::AddTail(this->u32_28,param_2);
  }
  return;
}

// JP: 0x0025f230  RemoveObject__8PutiPrimFP10PutiObject  =  PutiPrim::RemoveObject
void PutiPrim::RemoveObject(int this,undefined4 param_2)

{
  undefined4 uVar1;
  
  if (this->i32_28 != 0) {
    uVar1 = CList::Remove(param_2);
    this->u32_28 = uVar1;
  }
  return;
}

// JP: 0x0025f280  DelayAdd__8PutiPrimFv  =  PutiPrim::DelayAdd
void PutiPrim::DelayAdd(int this)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  this->i32_38 = this->i32_38 + 1;
  iVar3 = this->i32_34;
  while (iVar3 != 0) {
    if (this->i32_38 < iVar3->i32_c) {
      iVar3 = CList::GetNext(iVar3);
    }
    else {
      iVar1 = CList::GetNext(iVar3);
      uVar2 = CList::Remove(iVar3);
      this->u32_34 = uVar2;
      PutiPrim::AddObject(this,iVar3->u32_8);
      iVar3->u32_8 = 0;
      DelayPutiObject::~DelayPutiObject(iVar3,1);
      iVar3 = iVar1;
    }
  }
  return;
}

// JP: 0x0025f360  __ct__11PutiManagerFv  =  PutiManager::PutiManager
int PutiManager::PutiManager(int this)

{
  int iVar1;
  
  CPolObj::CPolObj(this);
  *(undefined1 **)(this + 0x14) = PutiManager::__vt;
  for (iVar1 = 0; iVar1 < 0x10; iVar1 = iVar1 + 1) {
    *(undefined4 *)(&PutiManager::ourLayer + iVar1 * 4) = 0;
  }
  PutiManager::ourManager = this;
  this->u8_18 = 1;
  return this;
}

// JP: 0x0025f3f0  __dt__11PutiManagerFv  =  PutiManager::~PutiManager
int PutiManager::~PutiManager(int this,short param_2)

{
  long lVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  if (this != 0) {
    *(undefined1 **)(this + 0x14) = PutiManager::__vt;
    for (iVar2 = 0; iVar2 < 0x10; iVar2 = iVar2 + 1) {
      iVar4 = *(int *)(&PutiManager::ourLayer + iVar2 * 4);
      while (iVar4 != 0) {
        lVar1 = CList::Remove(iVar4 + 0x14);
        iVar3 = 0;
        if (lVar1 != 0) {
          iVar3 = (int)lVar1 + -0x14;
        }
        PutiPrim::Delete(iVar4);
        iVar4 = iVar3;
      }
      *(undefined4 *)(&PutiManager::ourLayer + iVar2 * 4) = 0;
    }
    PutiManager::ourManager = 0;
    CPolObj::~CPolObj(this,0);
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x0025f510  Init__11PutiManagerFv  =  PutiManager::Init
void PutiManager::Init(undefined4 this)

{
  CPoller::Entry(CApp::app + 0x48,this,0xc0,0);
  return;
}

// JP: 0x0025f550  AddPrim__11PutiManagerFiP8PutiPrim  =  PutiManager::AddPrim
int PutiManager::AddPrim(undefined8 this,int param_2,VIF1Prim *param_3)

{
  int iVar1;
  VIF1Prim *pVVar2;
  
  if (*(int *)(&PutiManager::ourLayer + param_2 * 4) == 0) {
    *(VIF1Prim **)(&PutiManager::ourLayer + param_2 * 4) = param_3;
  }
  else {
    pVVar2 = param_3;
    if (param_3 != (VIF1Prim *)0x0) {
      pVVar2 = param_3 + 1;
    }
    CList::Add(*(int *)(&PutiManager::ourLayer + param_2 * 4) + 0x14,pVVar2);
  }
  iVar1 = World::AddOT((World *)&CApp::m_World,param_2,param_3);
  return iVar1;
}

// JP: 0x0025f620  RemovePrim__11PutiManagerFP8PutiPrim  =  PutiManager::RemovePrim
void PutiManager::RemovePrim(undefined4 this,VIF1Prim *param_2)

{
  long lVar1;
  int iVar2;
  int iVar3;
  
  for (iVar2 = 0; iVar2 < 0x10; iVar2 = iVar2 + 1) {
    if ((*(int *)(&PutiManager::ourLayer + iVar2 * 4) != 0) &&
       (lVar1 = PutiManager::FindPrim(this,iVar2,param_2), lVar1 != 0)) {
      lVar1 = CList::Remove(param_2 + 1);
      iVar3 = 0;
      if (lVar1 != 0) {
        iVar3 = (int)lVar1 + -0x14;
      }
      *(int *)(&PutiManager::ourLayer + iVar2 * 4) = iVar3;
      World::ReleaseOT((World *)&CApp::m_World,param_2);
    }
  }
  return;
}

// JP: 0x0025f700  FindPrim__11PutiManagerFiP8PutiPrim  =  PutiManager::FindPrim
int PutiManager::FindPrim(undefined8 this,int param_2,int param_3)

{
  long lVar1;
  int iVar2;
  
  iVar2 = *(int *)(&PutiManager::ourLayer + param_2 * 4);
  while( true ) {
    if (iVar2 == 0) {
      return 0;
    }
    if (iVar2 == param_3) break;
    lVar1 = CList::GetNext(iVar2 + 0x14);
    iVar2 = 0;
    if (lVar1 != 0) {
      iVar2 = (int)lVar1 + -0x14;
    }
  }
  return param_3;
}

// JP: 0x0025f7a0  DeleteAll__11PutiManagerFv  =  PutiManager::DeleteAll
void PutiManager::DeleteAll(void)

{
  long lVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  for (iVar4 = 0; iVar4 < 0x10; iVar4 = iVar4 + 1) {
    iVar3 = *(int *)(&PutiManager::ourLayer + iVar4 * 4);
    while (iVar3 != 0) {
      lVar1 = CList::GetNext(iVar3 + 0x14);
      iVar2 = 0;
      if (lVar1 != 0) {
        iVar2 = (int)lVar1 + -0x14;
      }
      PutiPrim::Delete(iVar3);
      iVar3 = iVar2;
    }
  }
  return;
}

// JP: 0x0025f860  Polling__11PutiManagerFv  =  PutiManager::Polling
undefined8 PutiManager::Polling(int this)

{
  undefined8 uVar1;
  undefined8 uVar2;
  long lVar3;
  int iVar4;
  int iVar5;
  undefined1 auStack_20 [16];
  int iStack_10;
  
  if (CApp::camera != 0) {
    iStack_10 = this;
    uVar1 = GsxCamera::GetMatrix(CApp::camera);
    Matrix::__as(0x4213c0,uVar1);
    uVar1 = Matrix::GetPos(0x4213c0);
    uVar2 = FVector::FVector(0,0,0,0x3f800000,auStack_20);
    FVector::__as(uVar1,uVar2);
    Matrix::Invers(0x4213c0);
    if (iStack_10->i8_18 != '\0') {
      for (iVar5 = 0; iVar5 < 0x10; iVar5 = iVar5 + 1) {
        iVar4 = *(int *)(&PutiManager::ourLayer + iVar5 * 4);
        while (iVar4 != 0) {
          PutiPrim::Update(iVar4);
          lVar3 = CList::GetNext(iVar4 + 0x14);
          iVar4 = 0;
          if (lVar3 != 0) {
            iVar4 = (int)lVar3 + -0x14;
          }
        }
      }
    }
  }
  return 0;
}

// JP: 0x0025faf0  __ct__11PutiTextureFv  =  PutiTexture::PutiTexture
int PutiTexture::PutiTexture(int this)

{
  CList::CList(this);
  __ct__Q211PutiTexture26_class_1573PutiTexture_cppFv(this + 0x10);
  this->u32_8 = 0;
  return this;
}

// JP: 0x0025fb80  __dt__11PutiTextureFv  =  PutiTexture::~PutiTexture
int * PutiTexture::~PutiTexture(int *this,short param_2)

{
  int iVar1;
  
  if (this != (int *)0x0) {
    if (this[2] != 0) {
      iVar1 = this[2];
      if (iVar1 != 0) {
        (**(code **)(iVar1->i32_c + 8))(iVar1,1);
      }
      this[2] = 0;
    }
    if (*this != 0) {
      PutiTexture::~PutiTexture(*this,1);
    }
    CList::~CList(this,0);
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x0025fc50  Create__11PutiTextureFUcP12tagPTexParam  =  PutiTexture::Create
void PutiTexture::Create(int this,undefined1 param_2,undefined4 *param_3)

{
  byte bVar1;
  undefined2 uVar2;
  ushort uVar3;
  undefined4 uVar4;
  uint uVar5;
  long lVar6;
  ulong uVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  undefined1 auStack_50 [31];
  byte bStack_31;
  int iStack_30;
  undefined1 uStack_20;
  undefined4 *puStack_10;
  
  iStack_30 = this;
  uStack_20 = param_2;
  puStack_10 = param_3;
  _QWD::_QWD(auStack_50);
  iStack_30->u8_60 = uStack_20;
  if (puStack_10->i8_4 == '\x04') {
    bStack_31 = 0x2c;
  }
  else {
    bStack_31 = 0x1b;
  }
  if (puStack_10->i8_4 == '\x04') {
    iVar10 = 8;
  }
  else {
    iVar10 = 0x10;
  }
  if (puStack_10->i8_4 == '\x04') {
    iVar9 = 2;
  }
  else {
    iVar9 = 0x10;
  }
  lVar6 = __nw(0x30);
  uVar4 = 0;
  if (lVar6 != 0) {
    uVar4 = CVif1Packet::CVif1Packet(lVar6,0x28,0x10);
  }
  iStack_30->u32_8 = uVar4;
  if ((uint)puStack_10[2] >> 6 == 0) {
    uVar5 = 1;
  }
  else {
    uVar5 = (uint)puStack_10[2] >> 6;
  }
  uVar2 = GsxFrameBuf::GetBufEntry(CApp::camera->u32_340);
  CVif1Packet::RefLoadImage
            (iStack_30->u32_8,uVar2,bStack_31,uVar5 & 0xffff,puStack_10[1],
             (uint)(puStack_10[2] * puStack_10[3]) >> 4,0,0);
  uVar5 = ClutAdressControl::getAdress(CApp::app + 0x80,10);
  CVif1Packet::RefLoadImage
            (iStack_30->u32_8,uVar5 & 0xffff,0,1,*puStack_10,
             (uint)(iVar10 * iVar9) >> 2,0,0);
  memset((void *)(iStack_30 + 0x10),0,0x50);
  iStack_30->u64_10 = 0x1000000000008004;
  iStack_30->u64_18 = 0xe;
  iStack_30->u64_28 = 0x3f;
  uVar3 = GsxFrameBuf::GetBufEntry(CApp::camera->u32_340);
  iStack_30->u16_30 = iStack_30->u16_30 & 0xc000 | uVar3 & 0x3fff;
  if ((uint)puStack_10[2] >> 6 == 0) {
    uVar8 = 1;
  }
  else {
    uVar8 = (uint)puStack_10[2] >> 6;
  }
  iStack_30->u64_30 =
       iStack_30->u64_30 & 0xfffffffffff03fff | ((long)(int)uVar8 & 0x3fU) << 0xe;
  iStack_30->u16_32 = iStack_30->u16_32 & 0xfc0f | (bStack_31 & 0x3f) << 4;
  bVar1 = GetBekijo(puStack_10[2]);
  iStack_30->u8_33 = iStack_30->u8_33 & 0xc3 | (bVar1 & 0xf) << 2;
  uVar7 = GetBekijo(puStack_10[3]);
  iStack_30->u64_30 =
       iStack_30->u64_30 & 0xfffffffc3fffffff | (uVar7 & 0xf) << 0x1e;
  iStack_30->u8_34 = iStack_30->u8_34 & 0xfb | 4;
  iStack_30->u8_34 = iStack_30->u8_34 & 0xe7;
  iStack_30->u64_30 =
       iStack_30->u64_30 & 0xfff8001fffffffff | ((long)(int)uVar5 & 0x3fffU) << 0x25;
  iStack_30->u8_36 = iStack_30->u8_36 & 0x87;
  iStack_30->u8_36 = iStack_30->u8_36 & 0x7f;
  iStack_30->u8_37 = iStack_30->u8_37 & 0xe0;
  iStack_30->u8_37 = iStack_30->u8_37 & 0x1f | 0x20;
  iStack_30->u64_38 = 6;
  iStack_30->u8_40 = iStack_30->u8_40 & 0xdf | 0x20;
  iStack_30->u16_40 = iStack_30->u16_40 & 0xfe3f | 0x40;
  iStack_30->u64_48 = 0x14;
  iStack_30->u8_50 = iStack_30->u8_50 & 0xfc;
  iStack_30->u8_50 = iStack_30->u8_50 & 0xf3;
  iStack_30->u16_50 = iStack_30->u16_50 & 0xc00f;
  iStack_30->u64_50 = iStack_30->u64_50 & 0xffffffffff003fff;
  iStack_30->u64_50 = iStack_30->u64_50 & 0xfffffffc00ffffff;
  iStack_30->u16_54 = iStack_30->u16_54 & 0xf003;
  iStack_30->u64_58 = 8;
  CVif1Packet::Ref(iStack_30->u32_8,iStack_30 + 0x10,5,0,0x50000005,0);
  CVif1Packet::Ret(iStack_30->u32_8,0);
  CVif1Packet::Terminate(iStack_30->u32_8);
  return;
}

// JP: 0x00260510  FindTexture__11PutiTextureFUc  =  PutiTexture::FindTexture
int * PutiTexture::FindTexture(int *this,char param_2)

{
  if ((char)this[0x18] != param_2) {
    if (*this == 0) {
      this = (int *)0x0;
    }
    else {
      this = (int *)PutiTexture::FindTexture(*this,param_2);
    }
  }
  return this;
}

// JP: 0x00260590  __ct__11PutiTexAnimFiiP11tagPAnimSeq  =  PutiTexAnim::PutiTexAnim
undefined4 *
PutiTexAnim::PutiTexAnim
          (undefined4 *this,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  *this = param_2;
  this[1] = param_3;
  this[2] = param_4;
  this->u8_3 = this->u8_3 & 0xfe | 1;
  return this;
}

// JP: 0x00260600  __dt__11PutiTexAnimFv  =  PutiTexAnim::~PutiTexAnim
int PutiTexAnim::~PutiTexAnim(int this,short param_2)

{
  if ((this != 0) && (0 < param_2)) {
    __dl(this);
  }
  return this;
}

// JP: 0x00260660  GetUVA__11PutiTexAnimFiPfPfPfPfPf  =  PutiTexAnim::GetUVA
/* WARNING: Removing unreachable block (ram,0x002607e0) */
/* WARNING: Removing unreachable block (ram,0x00260a1c) */
/* WARNING: Removing unreachable block (ram,0x00260b38) */

void PutiTexAnim::GetUVA
               (int *this,int param_2,undefined4 *param_3,undefined4 *param_4,undefined4 *param_5
               ,undefined4 *param_6,float *param_7)

{
  int iVar1;
  int iStack_60;
  
  iStack_60 = param_2;
  if ((((this->u8_3 & 1) != 0) && (*this < param_2)) &&
     (iStack_60 = param_2 % *this, *this == 0)) {
    trap(7);
  }
  iVar1 = 0;
  while( true ) {
    if (this[1] <= iVar1) {
      iVar1 = iVar1 + -1;
      *param_3 = *(undefined4 *)(this[2] + iVar1 * 0x14 + 4);
      *param_4 = *(undefined4 *)(this[2] + iVar1 * 0x14 + 8);
      *param_5 = *(undefined4 *)(this[2] + iVar1 * 0x14 + 0xc);
      *param_6 = *(undefined4 *)(this[2] + iVar1 * 0x14 + 0x10);
      *param_7 = (float)*(byte *)(this[2] + iVar1 * 0x14 + 2);
      return;
    }
    if ((long)iStack_60 == (long)*(short *)(this[2] + iVar1 * 0x14)) break;
    if ((long)iStack_60 < (long)*(short *)(this[2] + iVar1 * 0x14)) {
      *param_3 = *(undefined4 *)(this[2] + (iVar1 + -1) * 0x14 + 4);
      *param_4 = *(undefined4 *)(this[2] + (iVar1 + -1) * 0x14 + 8);
      *param_5 = *(undefined4 *)(this[2] + (iVar1 + -1) * 0x14 + 0xc);
      *param_6 = *(undefined4 *)(this[2] + (iVar1 + -1) * 0x14 + 0x10);
      *param_7 = (float)*(byte *)(this[2] + (iVar1 + -1) * 0x14 + 2) +
                 ((float)(int)((uint)*(byte *)(this[2] + iVar1 * 0x14 + 2) -
                              (uint)*(byte *)(this[2] + (iVar1 + -1) * 0x14 + 2)) *
                 (float)(iStack_60 - *(short *)(this[2] + (iVar1 + -1) * 0x14))) /
                 (float)((int)*(short *)(this[2] + iVar1 * 0x14) -
                        (int)*(short *)(this[2] + (iVar1 + -1) * 0x14));
      return;
    }
    iVar1 = iVar1 + 1;
  }
  *param_3 = *(undefined4 *)(this[2] + iVar1 * 0x14 + 4);
  *param_4 = *(undefined4 *)(this[2] + iVar1 * 0x14 + 8);
  *param_5 = *(undefined4 *)(this[2] + iVar1 * 0x14 + 0xc);
  *param_6 = *(undefined4 *)(this[2] + iVar1 * 0x14 + 0x10);
  *param_7 = (float)*(byte *)(this[2] + iVar1 * 0x14 + 2);
  return;
}
