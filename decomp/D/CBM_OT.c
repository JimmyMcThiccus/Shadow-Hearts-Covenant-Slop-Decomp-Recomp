// decomp/D/CBM_OT.c — cleaned Ghidra output (SLPM_602.19, Metrowerks MIPS), Shadow Hearts: Covenant JP demo.
// Field accesses are shown as this->T_off (T = u8/u16/u32/f32/i32/p, off = hex offset);
// JRing fields are named from the recovered struct. See notes/D/*.md for layouts.
// CAVEAT: when the base pointer is a float*/int*/short*, the number in `T_off` is an ELEMENT offset (byte offset = off*sizeof(elem)).
// `this` is the C++ this pointer (param_1); the Metrowerks ABI passes it in a0.

// JP: 0x003da6e0  AddTime__12CBRingSoulOTFf  =  CBRingSoulOT::AddTime
void CBRingSoulOT::AddTime(float this,undefined8 param_2)

{
  int iVar1;
  int iVar2;
  undefined1 (*pauVar3) [16];
  int iVar4;
  float *pfVar5;
  int iVar6;
  float fVar7;
  undefined1 in_vf0 [16];
  undefined1 auVar8 [16];
  undefined1 auVar9 [16];
  undefined1 auVar10 [16];
  undefined1 auStack_50 [8];
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [16];
  undefined1 auStack_20 [16];
  undefined1 auStack_10 [16];
  
  auVar8 = _vmr32(in_vf0);
  auVar9 = _vmr32(auVar8);
  auVar10 = _vmr32(auVar9);
  _sqc2(in_vf0);
  _sqc2(auVar8);
  _sqc2(auVar9);
  _sqc2(auVar10);
  auVar8 = _vmr32(in_vf0);
  auVar9 = _vmr32(auVar8);
  auVar10 = _vmr32(auVar9);
  auStack_10 = _sqc2(in_vf0);
  auStack_20 = _sqc2(auVar8);
  auStack_30 = _sqc2(auVar9);
  auStack_40 = _sqc2(auVar10);
  sceVu0RotMatrixZ(0x3ca3d70a,auStack_40,auStack_40);
  iVar6 = (int)param_2;
  pfVar5 = *(float **)(iVar6 + 0x10);
  for (iVar4 = 0; iVar4 < iVar6->i32_8; iVar4 = iVar4 + 1) {
    fVar7 = *pfVar5;
    iVar1 = *(int *)(iVar6->i32_c + 0x24);
    iVar2 = iVar1->i32_c;
    pauVar3 = (undefined1 (*) [16])(iVar1->i32_4 + iVar4 * 0x20);
    *pfVar5 = fVar7 + this;
    iVar2 = iVar2 + iVar4 * 0x20;
    if (pfVar5[1] < fVar7 + this) {
      (**(code **)(iVar6->i32_7e4 + 0x24))(param_2,iVar4);
    }
    auVar9 = _lqc2(*(undefined1 (*) [16])(pfVar5 + 4));
    auVar8 = _lqc2(*pauVar3);
    auVar8 = _vadd(auVar8,auVar9);
    auVar8 = _sqc2(auVar8);
    *pauVar3 = auVar8;
    Matrix::ApplyMatrix(auStack_50,auStack_40,pauVar3 + 1);
    *(int *)pauVar3[1] = auStack_50._0_4_;
    *(int *)(pauVar3[1] + 4) = auStack_50._4_4_;
    *(undefined4 *)(pauVar3[1] + 8) = uStack_48;
    *(undefined4 *)(pauVar3[1] + 0xc) = uStack_44;
    SequenceBase::getKeyFrame(*pfVar5,pfVar5[1],iVar6 + 0x20,iVar2);
    pfVar5 = pfVar5 + 8;
    iVar2->u32_10 = 0x3fb9999a;
    iVar2->u32_14 = 0x3fb9999a;
    iVar2->u32_18 = 0x3fb9999a;
    iVar2->u32_1c = 0;
  }
  return;
}

// JP: 0x003da880  Initialization__12CBRingSoulOTFv  =  CBRingSoulOT::Initialization
void CBRingSoulOT::Initialization(undefined8 this)

{
  undefined4 uVar1;
  long lVar2;
  int this;
  int iVar4;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  
  BackScreenTexture::Init(this->u32_7f0,0x200,0x1c0);
  Texture::createRegsterPacket(*(Texture **)(this + 0x7f0),1,0,0,0x200,9,9,0);
  lVar2 = __nw(0xa4);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = LayeredTexture::LayeredTexture(lVar2);
  }
  this->u32_7f4 = uVar1;
  *(undefined4 *)(this->i32_7f4 + 0x68) = 0x200;
  *(undefined4 *)(this->i32_7f4 + 0x6c) = 0x1c0;
  Texture::createRegsterPacket(*(Texture **)(this + 0x7f4),0,0,0x2a00,0x200,9,9,1);
  *(undefined4 *)(this->i32_c + 0x230) = this->u32_7f4;
  PolyBase::initPacket(this->u32_c);
  *(undefined **)(this->i32_c + 8) = &_dma_460;
  uStack_10 = 0x3fb9999a;
  uStack_c = 0x3fb9999a;
  uStack_8 = 0x3fb9999a;
  uStack_4 = 0;
  SequenceBase::setKeyFrame(0,this + 0x20,&uStack_10);
  uStack_14 = 0x3f800000;
  uStack_20 = 0x3fb9999a;
  uStack_1c = 0x3fb9999a;
  uStack_18 = 0x3fb9999a;
  SequenceBase::setKeyFrame(0x3dcccccd,this + 0x20,&uStack_20);
  uStack_24 = 0x3f800000;
  uStack_30 = 0x3fb9999a;
  uStack_2c = 0x3fb9999a;
  uStack_28 = 0x3fb9999a;
  SequenceBase::setKeyFrame(0x3f4ccccd,this + 0x20,&uStack_30);
  uStack_40 = 0x3fb9999a;
  uStack_3c = 0x3fb9999a;
  uStack_38 = 0x3fb9999a;
  uStack_34 = 0;
  SequenceBase::setKeyFrame(0x3f800000,this + 0x20,&uStack_40);
  iVar4 = 0;
  if (0 < this->i32_8) {
    do {
      (**(code **)(this->i32_7e4 + 0x24))(this,iVar4);
      iVar4 = iVar4 + 1;
    } while (iVar4 < this->i32_8);
  }
  return;
}

// JP: 0x003daa50  NewLifeMake__12CBRingSoulOTFi  =  CBRingSoulOT::NewLifeMake
/* WARNING: Function: fptodp replaced with injection: fptodp */
/* WARNING: Function: dpdiv replaced with injection: dpdiv */
/* WARNING: Function: dptofp replaced with injection: dptofp */

void CBRingSoulOT::NewLifeMake(int this,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  float fVar4;
  float fVar5;
  undefined1 in_vf0 [16];
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  undefined1 auVar8 [16];
  undefined1 auStack_80 [8];
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined4 uStack_70;
  undefined4 uStack_6c;
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
  
  puVar2 = (undefined4 *)(this->i32_10 + param_2 * 0x20);
  iVar1 = *(int *)(*(int *)(this->i32_c + 0x24) + 4);
  *puVar2 = 0;
  puVar3 = (undefined4 *)(iVar1 + param_2 * 0x20);
  if (this->i32_7d4 == 0) {
    uStack_54 = 0x3f800000;
    uStack_60 = 0;
    uStack_5c = 0;
    uStack_58 = 0;
    *puVar3 = 0;
    puVar3[1] = 0;
    puVar3[2] = 0;
    puVar3[3] = 0x3f800000;
  }
  else {
    Frame::getWorldPos(auStack_50,this->i32_7d4,VIF1Prim::m_Env & 1);
    *puVar3 = auStack_50._0_4_;
    puVar3[1] = auStack_50._4_4_;
    puVar3[2] = uStack_48;
    puVar3[3] = uStack_44;
  }
  auVar6 = _vmr32(in_vf0);
  auVar7 = _vmr32(auVar6);
  auVar8 = _vmr32(auVar7);
  _sqc2(in_vf0);
  _sqc2(auVar6);
  _sqc2(auVar7);
  _sqc2(auVar8);
  auVar6 = _vmr32(in_vf0);
  auVar7 = _vmr32(auVar6);
  auVar8 = _vmr32(auVar7);
  auStack_10 = _sqc2(in_vf0);
  auStack_20 = _sqc2(auVar6);
  auStack_30 = _sqc2(auVar7);
  auStack_40 = _sqc2(auVar8);
  iVar1 = rand();
  fVar5 = ((float)iVar1 / 2.1474836e+09) * 0.392699 + -0.1963495;
  iVar1 = rand();
  fVar4 = ((float)iVar1 / 2.1474836e+09) * 0.392699 + -0.1963495;
  sceVu0RotMatrixX(fVar5,auStack_40,auStack_40);
  sceVu0RotMatrixZ(fVar4,auStack_40,auStack_40);
  uStack_6c = 0xbe4ccccd;
  uStack_70 = 0;
  uStack_64 = 0x3f800000;
  uStack_68 = 0;
  puVar2[4] = 0;
  puVar2[5] = 0xbe4ccccd;
  puVar2[6] = 0;
  puVar2[7] = 0x3f800000;
  Matrix::ApplyMatrix(auStack_80,auStack_40,puVar2 + 4);
  puVar2[4] = auStack_80._0_4_;
  puVar2[5] = auStack_80._4_4_;
  puVar2[6] = uStack_78;
  puVar2[7] = uStack_74;
  fabs((double)fVar5);
  fabs((double)fVar4);
  iVar1 = rand();
  puVar2[1] = (float)iVar1 / 2.1474836e+09 + 0.5;
  return;
}

// JP: 0x003dacd0  __dt__12CBRingSoulOTFv  =  CBRingSoulOT::~CBRingSoulOT
long CBRingSoulOT::~CBRingSoulOT(long this,short param_2)

{
  int this;
  
  if (this != 0) {
    
    *(undefined1 **)(this + 0x7e4) = CBRingSoulOT::__vt;
    (**(code **)(*(int *)(this->i32_7f0 + 0x9c) + 0xc))(this->i32_7f0 + 0x94);
    (**(code **)(*(int *)(this->i32_7f4 + 0x9c) + 0xc))(this->i32_7f4 + 0x94);
    CBBPolygon::~CBBPolygon(this,0);
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x003dad60  dip__12CBRingSoulOTFi  =  CBRingSoulOT::dip
void CBRingSoulOT::dip(undefined8 this,undefined8 param_2)

{
  int iVar1;
  VIF1Prim *prim;
  
  iVar1 = *(int *)((int)this + 0x7f0);
  prim = (VIF1Prim *)0x0;
  if (iVar1 != 0) {
    prim = (VIF1Prim *)(iVar1 + 0x80);
  }
  World::AddOT((World *)&CApp::m_World,(int)param_2,prim);
  CBBPolygon::dip(this,param_2);
  return;
}

// JP: 0x003dadc0  Clr__12CBRingSoulOTFv  =  CBRingSoulOT::Clr
void CBRingSoulOT::Clr(undefined8 this)

{
  int iVar1;
  VIF1Prim *prim;
  
  iVar1 = *(int *)((int)this + 0x7f0);
  prim = (VIF1Prim *)0x0;
  if (iVar1 != 0) {
    prim = (VIF1Prim *)(iVar1 + 0x80);
  }
  World::ReleaseOT((World *)&CApp::m_World,prim);
  CBBPolygon::Clr(this);
  return;
}

// JP: 0x003dae10  __ct__12CBRingSoulOTFiPc  =  CBRingSoulOT::CBRingSoulOT
undefined8 CBRingSoulOT::CBRingSoulOT(undefined8 this,undefined8 param_2)

{
  long lVar1;
  undefined8 uVar2;
  
  lVar1 = __nw(0xb0);
  uVar2 = 0;
  if (lVar1 != 0) {
    uVar2 = BackScreenTexture::BackScreenTexture(lVar1);
  }
  *(int *)((int)this + 0x7f0) = (int)uVar2;
  CBBPolygon::CBBPolygon(this,param_2,uVar2);
  *(undefined1 **)((int)this + 0x7e4) = CBRingSoulOT::__vt;
  return this;
}

// JP: 0x003dd870  AddTime__8CBM412OTFf  =  CBM412OT::AddTime
void CBM412OT::AddTime(float this,undefined8 param_2)

{
  int iVar1;
  int iVar2;
  undefined1 (*pauVar3) [16];
  int iVar4;
  float *pfVar5;
  int iVar6;
  float fVar7;
  undefined1 in_vf0 [16];
  undefined1 auVar8 [16];
  undefined1 auVar9 [16];
  undefined1 auVar10 [16];
  undefined1 auStack_50 [8];
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [16];
  undefined1 auStack_20 [16];
  undefined1 auStack_10 [16];
  
  auVar8 = _vmr32(in_vf0);
  auVar9 = _vmr32(auVar8);
  auVar10 = _vmr32(auVar9);
  _sqc2(in_vf0);
  _sqc2(auVar8);
  _sqc2(auVar9);
  _sqc2(auVar10);
  auVar8 = _vmr32(in_vf0);
  auVar9 = _vmr32(auVar8);
  auVar10 = _vmr32(auVar9);
  auStack_10 = _sqc2(in_vf0);
  auStack_20 = _sqc2(auVar8);
  auStack_30 = _sqc2(auVar9);
  auStack_40 = _sqc2(auVar10);
  sceVu0RotMatrixZ(0x3ca3d70a,auStack_40,auStack_40);
  iVar6 = (int)param_2;
  pfVar5 = *(float **)(iVar6 + 0x10);
  for (iVar4 = 0; iVar4 < iVar6->i32_8; iVar4 = iVar4 + 1) {
    fVar7 = *pfVar5;
    iVar1 = *(int *)(iVar6->i32_c + 0x24);
    iVar2 = iVar1->i32_c;
    pauVar3 = (undefined1 (*) [16])(iVar1->i32_4 + iVar4 * 0x20);
    *pfVar5 = fVar7 + this;
    iVar2 = iVar2 + iVar4 * 0x20;
    if (pfVar5[1] < fVar7 + this) {
      (**(code **)(iVar6->i32_7e4 + 0x24))(param_2,iVar4);
    }
    auVar9 = _lqc2(*(undefined1 (*) [16])(pfVar5 + 4));
    auVar8 = _lqc2(*pauVar3);
    auVar8 = _vadd(auVar8,auVar9);
    auVar8 = _sqc2(auVar8);
    *pauVar3 = auVar8;
    Matrix::ApplyMatrix(auStack_50,auStack_40,pauVar3 + 1);
    *(int *)pauVar3[1] = auStack_50._0_4_;
    *(int *)(pauVar3[1] + 4) = auStack_50._4_4_;
    *(undefined4 *)(pauVar3[1] + 8) = uStack_48;
    *(undefined4 *)(pauVar3[1] + 0xc) = uStack_44;
    SequenceBase::getKeyFrame(*pfVar5,pfVar5[1],iVar6 + 0x20,iVar2);
    pfVar5 = pfVar5 + 8;
    iVar2->u32_10 = 0x3fb9999a;
    iVar2->u32_14 = 0x3fb9999a;
    iVar2->u32_18 = 0x3fb9999a;
    iVar2->u32_1c = 0;
  }
  return;
}

// JP: 0x003dda10  Initialization__8CBM412OTFv  =  CBM412OT::Initialization
void CBM412OT::Initialization(undefined8 this)

{
  undefined4 uVar1;
  long lVar2;
  int this;
  int iVar4;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  
  BackScreenTexture::Init(this->u32_7f0,0x200,0x1c0);
  Texture::createRegsterPacket(*(Texture **)(this + 0x7f0),1,0,0,0x200,9,9,0);
  lVar2 = __nw(0xa4);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = LayeredTexture::LayeredTexture(lVar2);
  }
  this->u32_7f4 = uVar1;
  *(undefined4 *)(this->i32_7f4 + 0x68) = 0x200;
  *(undefined4 *)(this->i32_7f4 + 0x6c) = 0x1c0;
  Texture::createRegsterPacket(*(Texture **)(this + 0x7f4),0,0,0x2a00,0x200,9,9,1);
  *(undefined4 *)(this->i32_c + 0x230) = this->u32_7f4;
  PolyBase::initPacket(this->u32_c);
  *(undefined **)(this->i32_c + 8) = &_dma_460;
  uStack_10 = 0x3fb9999a;
  uStack_c = 0x3fb33333;
  uStack_8 = 0x3fb33333;
  uStack_4 = 0;
  SequenceBase::setKeyFrame(0,this + 0x20,&uStack_10);
  uStack_20 = 0x3fb9999a;
  uStack_1c = 0x3fb33333;
  uStack_14 = 0x3f800000;
  uStack_18 = 0x3fb33333;
  SequenceBase::setKeyFrame(0x3dcccccd,this + 0x20,&uStack_20);
  uStack_30 = 0x3fb9999a;
  uStack_2c = 0x3fb33333;
  uStack_24 = 0x3f800000;
  uStack_28 = 0x3fb33333;
  SequenceBase::setKeyFrame(0x3f4ccccd,this + 0x20,&uStack_30);
  uStack_40 = 0x3fb9999a;
  uStack_34 = 0;
  uStack_3c = 0x3fb33333;
  uStack_38 = 0x3fb33333;
  SequenceBase::setKeyFrame(0x3f800000,this + 0x20,&uStack_40);
  iVar4 = 0;
  if (0 < this->i32_8) {
    do {
      (**(code **)(this->i32_7e4 + 0x24))(this,iVar4);
      iVar4 = iVar4 + 1;
    } while (iVar4 < this->i32_8);
  }
  return;
}

// JP: 0x003ddc00  NewLifeMake__8CBM412OTFi  =  CBM412OT::NewLifeMake
/* WARNING: Function: fptodp replaced with injection: fptodp */
/* WARNING: Function: dpdiv replaced with injection: dpdiv */
/* WARNING: Function: dptofp replaced with injection: dptofp */

void CBM412OT::NewLifeMake(int this,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  float fVar4;
  float fVar5;
  undefined1 in_vf0 [16];
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  undefined1 auVar8 [16];
  undefined1 auStack_80 [8];
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined4 uStack_70;
  undefined4 uStack_6c;
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
  
  puVar2 = (undefined4 *)(this->i32_10 + param_2 * 0x20);
  iVar1 = *(int *)(*(int *)(this->i32_c + 0x24) + 4);
  *puVar2 = 0;
  puVar3 = (undefined4 *)(iVar1 + param_2 * 0x20);
  if (this->i32_7d4 == 0) {
    uStack_54 = 0x3f800000;
    uStack_60 = 0;
    uStack_5c = 0;
    uStack_58 = 0;
    *puVar3 = 0;
    puVar3[1] = 0;
    puVar3[2] = 0;
    puVar3[3] = 0x3f800000;
  }
  else {
    Frame::getWorldPos(auStack_50,this->i32_7d4,VIF1Prim::m_Env & 1);
    *puVar3 = auStack_50._0_4_;
    puVar3[1] = auStack_50._4_4_;
    puVar3[2] = uStack_48;
    puVar3[3] = uStack_44;
  }
  auVar6 = _vmr32(in_vf0);
  auVar7 = _vmr32(auVar6);
  auVar8 = _vmr32(auVar7);
  _sqc2(in_vf0);
  _sqc2(auVar6);
  _sqc2(auVar7);
  _sqc2(auVar8);
  auVar6 = _vmr32(in_vf0);
  auVar7 = _vmr32(auVar6);
  auVar8 = _vmr32(auVar7);
  auStack_10 = _sqc2(in_vf0);
  auStack_20 = _sqc2(auVar6);
  auStack_30 = _sqc2(auVar7);
  auStack_40 = _sqc2(auVar8);
  iVar1 = rand();
  fVar5 = ((float)iVar1 / 2.1474836e+09) * 3.141592 + -1.570796;
  iVar1 = rand();
  fVar4 = ((float)iVar1 / 2.1474836e+09) * 3.141592 + -1.570796;
  sceVu0RotMatrixX(fVar5,auStack_40,auStack_40);
  sceVu0RotMatrixZ(fVar4,auStack_40,auStack_40);
  uStack_6c = 0xbf000000;
  uStack_70 = 0;
  uStack_64 = 0x3f800000;
  uStack_68 = 0;
  puVar2[4] = 0;
  puVar2[5] = 0xbf000000;
  puVar2[6] = 0;
  puVar2[7] = 0x3f800000;
  Matrix::ApplyMatrix(auStack_80,auStack_40,puVar2 + 4);
  puVar2[4] = auStack_80._0_4_;
  puVar2[5] = auStack_80._4_4_;
  puVar2[6] = uStack_78;
  puVar2[7] = uStack_74;
  fabs((double)fVar5);
  fabs((double)fVar4);
  iVar1 = rand();
  puVar2[1] = ((float)iVar1 / 2.1474836e+09) * 0.5 + 0.75;
  puVar3[4] = 0xc0a00000;
  puVar3[5] = 0xc0a00000;
  puVar3[6] = 0;
  puVar3[7] = 0x3f800000;
  return;
}

// JP: 0x003ddec0  __dt__8CBM412OTFv  =  CBM412OT::~CBM412OT
long CBM412OT::~CBM412OT(long this,short param_2)

{
  int this;
  
  if (this != 0) {
    
    *(undefined1 **)(this + 0x7e4) = CBM412OT::__vt;
    (**(code **)(*(int *)(this->i32_7f0 + 0x9c) + 0xc))(this->i32_7f0 + 0x94);
    (**(code **)(*(int *)(this->i32_7f4 + 0x9c) + 0xc))(this->i32_7f4 + 0x94);
    CBBPolygon::~CBBPolygon(this,0);
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x003ddf50  dip__8CBM412OTFi  =  CBM412OT::dip
void CBM412OT::dip(undefined8 this,undefined8 param_2)

{
  int iVar1;
  VIF1Prim *prim;
  
  iVar1 = *(int *)((int)this + 0x7f0);
  prim = (VIF1Prim *)0x0;
  if (iVar1 != 0) {
    prim = (VIF1Prim *)(iVar1 + 0x80);
  }
  World::AddOT((World *)&CApp::m_World,(int)param_2,prim);
  CBBPolygon::dip(this,param_2);
  return;
}

// JP: 0x003ddfb0  Clr__8CBM412OTFv  =  CBM412OT::Clr
void CBM412OT::Clr(undefined8 this)

{
  int iVar1;
  VIF1Prim *prim;
  
  iVar1 = *(int *)((int)this + 0x7f0);
  prim = (VIF1Prim *)0x0;
  if (iVar1 != 0) {
    prim = (VIF1Prim *)(iVar1 + 0x80);
  }
  World::ReleaseOT((World *)&CApp::m_World,prim);
  CBBPolygon::Clr(this);
  return;
}

// JP: 0x003de000  __ct__8CBM412OTFiPc  =  CBM412OT::CBM412OT
undefined8 CBM412OT::CBM412OT(undefined8 this,undefined8 param_2)

{
  long lVar1;
  undefined8 uVar2;
  
  lVar1 = __nw(0xb0);
  uVar2 = 0;
  if (lVar1 != 0) {
    uVar2 = BackScreenTexture::BackScreenTexture(lVar1);
  }
  *(int *)((int)this + 0x7f0) = (int)uVar2;
  CBBPolygon::CBBPolygon(this,param_2,uVar2);
  *(undefined1 **)((int)this + 0x7e4) = CBM412OT::__vt;
  return this;
}

// JP: 0x003de7e0  AddTime__8CBM413OTFf  =  CBM413OT::AddTime
void CBM413OT::AddTime(float this,undefined8 param_2)

{
  int iVar1;
  int iVar2;
  undefined1 (*pauVar3) [16];
  int iVar4;
  float *pfVar5;
  int iVar6;
  float fVar7;
  undefined1 in_vf0 [16];
  undefined1 auVar8 [16];
  undefined1 auVar9 [16];
  undefined1 auVar10 [16];
  undefined1 auStack_50 [8];
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [16];
  undefined1 auStack_20 [16];
  undefined1 auStack_10 [16];
  
  auVar8 = _vmr32(in_vf0);
  auVar9 = _vmr32(auVar8);
  auVar10 = _vmr32(auVar9);
  _sqc2(in_vf0);
  _sqc2(auVar8);
  _sqc2(auVar9);
  _sqc2(auVar10);
  auVar8 = _vmr32(in_vf0);
  auVar9 = _vmr32(auVar8);
  auVar10 = _vmr32(auVar9);
  auStack_10 = _sqc2(in_vf0);
  auStack_20 = _sqc2(auVar8);
  auStack_30 = _sqc2(auVar9);
  auStack_40 = _sqc2(auVar10);
  sceVu0RotMatrixZ(0x3ca3d70a,auStack_40,auStack_40);
  iVar6 = (int)param_2;
  pfVar5 = *(float **)(iVar6 + 0x10);
  for (iVar4 = 0; iVar4 < iVar6->i32_8; iVar4 = iVar4 + 1) {
    fVar7 = *pfVar5;
    iVar1 = *(int *)(iVar6->i32_c + 0x24);
    iVar2 = iVar1->i32_c;
    pauVar3 = (undefined1 (*) [16])(iVar1->i32_4 + iVar4 * 0x20);
    *pfVar5 = fVar7 + this;
    iVar2 = iVar2 + iVar4 * 0x20;
    if (pfVar5[1] < fVar7 + this) {
      (**(code **)(iVar6->i32_7e4 + 0x24))(param_2,iVar4);
    }
    auVar9 = _lqc2(*(undefined1 (*) [16])(pfVar5 + 4));
    auVar8 = _lqc2(*pauVar3);
    auVar8 = _vadd(auVar8,auVar9);
    auVar8 = _sqc2(auVar8);
    *pauVar3 = auVar8;
    Matrix::ApplyMatrix(auStack_50,auStack_40,pauVar3 + 1);
    *(int *)pauVar3[1] = auStack_50._0_4_;
    *(int *)(pauVar3[1] + 4) = auStack_50._4_4_;
    *(undefined4 *)(pauVar3[1] + 8) = uStack_48;
    *(undefined4 *)(pauVar3[1] + 0xc) = uStack_44;
    SequenceBase::getKeyFrame(*pfVar5,pfVar5[1],iVar6 + 0x20,iVar2);
    pfVar5 = pfVar5 + 8;
    iVar2->u32_10 = 0x3fb9999a;
    iVar2->u32_14 = 0x3fb9999a;
    iVar2->u32_18 = 0x3fb9999a;
    iVar2->u32_1c = 0;
  }
  return;
}

// JP: 0x003de980  Initialization__8CBM413OTFv  =  CBM413OT::Initialization
void CBM413OT::Initialization(undefined8 this)

{
  undefined4 uVar1;
  long lVar2;
  int this;
  int iVar4;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  
  BackScreenTexture::Init(this->u32_7f0,0x200,0x1c0);
  Texture::createRegsterPacket(*(Texture **)(this + 0x7f0),1,0,0,0x200,9,9,0);
  lVar2 = __nw(0xa4);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = LayeredTexture::LayeredTexture(lVar2);
  }
  this->u32_7f4 = uVar1;
  *(undefined4 *)(this->i32_7f4 + 0x68) = 0x200;
  *(undefined4 *)(this->i32_7f4 + 0x6c) = 0x1c0;
  Texture::createRegsterPacket(*(Texture **)(this + 0x7f4),0,0,0x2a00,0x200,9,9,1);
  *(undefined4 *)(this->i32_c + 0x230) = this->u32_7f4;
  PolyBase::initPacket(this->u32_c);
  *(undefined **)(this->i32_c + 8) = &_dma_460;
  uStack_8 = 0x3fb9999a;
  uStack_10 = 0x3fb33333;
  uStack_c = 0x3fb33333;
  uStack_4 = 0;
  SequenceBase::setKeyFrame(0,this + 0x20,&uStack_10);
  uStack_18 = 0x3fb9999a;
  uStack_20 = 0x3fb33333;
  uStack_14 = 0x3f800000;
  uStack_1c = 0x3fb33333;
  SequenceBase::setKeyFrame(0x3dcccccd,this + 0x20,&uStack_20);
  uStack_28 = 0x3fb9999a;
  uStack_30 = 0x3fb33333;
  uStack_24 = 0x3f800000;
  uStack_2c = 0x3fb33333;
  SequenceBase::setKeyFrame(0x3f4ccccd,this + 0x20,&uStack_30);
  uStack_34 = 0;
  uStack_40 = 0x3fb33333;
  uStack_3c = 0x3fb33333;
  uStack_38 = 0x3fb9999a;
  SequenceBase::setKeyFrame(0x3f800000,this + 0x20,&uStack_40);
  iVar4 = 0;
  if (0 < this->i32_8) {
    do {
      (**(code **)(this->i32_7e4 + 0x24))(this,iVar4);
      iVar4 = iVar4 + 1;
    } while (iVar4 < this->i32_8);
  }
  return;
}

// JP: 0x003deb70  NewLifeMake__8CBM413OTFi  =  CBM413OT::NewLifeMake
/* WARNING: Function: fptodp replaced with injection: fptodp */
/* WARNING: Function: dpdiv replaced with injection: dpdiv */
/* WARNING: Function: dptofp replaced with injection: dptofp */

void CBM413OT::NewLifeMake(int this,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  float fVar4;
  float fVar5;
  undefined1 in_vf0 [16];
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  undefined1 auVar8 [16];
  undefined1 auStack_80 [8];
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined4 uStack_70;
  undefined4 uStack_6c;
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
  
  puVar2 = (undefined4 *)(this->i32_10 + param_2 * 0x20);
  iVar1 = *(int *)(*(int *)(this->i32_c + 0x24) + 4);
  *puVar2 = 0;
  puVar3 = (undefined4 *)(iVar1 + param_2 * 0x20);
  if (this->i32_7d4 == 0) {
    uStack_54 = 0x3f800000;
    uStack_60 = 0;
    uStack_5c = 0;
    uStack_58 = 0;
    *puVar3 = 0;
    puVar3[1] = 0;
    puVar3[2] = 0;
    puVar3[3] = 0x3f800000;
  }
  else {
    Frame::getWorldPos(auStack_50,this->i32_7d4,VIF1Prim::m_Env & 1);
    *puVar3 = auStack_50._0_4_;
    puVar3[1] = auStack_50._4_4_;
    puVar3[2] = uStack_48;
    puVar3[3] = uStack_44;
  }
  auVar6 = _vmr32(in_vf0);
  auVar7 = _vmr32(auVar6);
  auVar8 = _vmr32(auVar7);
  _sqc2(in_vf0);
  _sqc2(auVar6);
  _sqc2(auVar7);
  _sqc2(auVar8);
  auVar6 = _vmr32(in_vf0);
  auVar7 = _vmr32(auVar6);
  auVar8 = _vmr32(auVar7);
  auStack_10 = _sqc2(in_vf0);
  auStack_20 = _sqc2(auVar6);
  auStack_30 = _sqc2(auVar7);
  auStack_40 = _sqc2(auVar8);
  iVar1 = rand();
  fVar5 = ((float)iVar1 / 2.1474836e+09) * 3.141592 + -1.570796;
  iVar1 = rand();
  fVar4 = ((float)iVar1 / 2.1474836e+09) * 3.141592 + -1.570796;
  sceVu0RotMatrixX(fVar5,auStack_40,auStack_40);
  sceVu0RotMatrixZ(fVar4,auStack_40,auStack_40);
  uStack_6c = 0xbf000000;
  uStack_70 = 0;
  uStack_64 = 0x3f800000;
  uStack_68 = 0;
  puVar2[4] = 0;
  puVar2[5] = 0xbf000000;
  puVar2[6] = 0;
  puVar2[7] = 0x3f800000;
  Matrix::ApplyMatrix(auStack_80,auStack_40,puVar2 + 4);
  puVar2[4] = auStack_80._0_4_;
  puVar2[5] = auStack_80._4_4_;
  puVar2[6] = uStack_78;
  puVar2[7] = uStack_74;
  fabs((double)fVar5);
  fabs((double)fVar4);
  iVar1 = rand();
  puVar2[1] = ((float)iVar1 / 2.1474836e+09) * 0.5 + 0.75;
  puVar3[4] = 0xc0a00000;
  puVar3[5] = 0xc0a00000;
  puVar3[6] = 0;
  puVar3[7] = 0x3f800000;
  return;
}

// JP: 0x003dee30  __dt__8CBM413OTFv  =  CBM413OT::~CBM413OT
long CBM413OT::~CBM413OT(long this,short param_2)

{
  int this;
  
  if (this != 0) {
    
    *(undefined1 **)(this + 0x7e4) = CBM413OT::__vt;
    (**(code **)(*(int *)(this->i32_7f0 + 0x9c) + 0xc))(this->i32_7f0 + 0x94);
    (**(code **)(*(int *)(this->i32_7f4 + 0x9c) + 0xc))(this->i32_7f4 + 0x94);
    CBBPolygon::~CBBPolygon(this,0);
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x003deec0  dip__8CBM413OTFi  =  CBM413OT::dip
void CBM413OT::dip(undefined8 this,undefined8 param_2)

{
  int iVar1;
  VIF1Prim *prim;
  
  iVar1 = *(int *)((int)this + 0x7f0);
  prim = (VIF1Prim *)0x0;
  if (iVar1 != 0) {
    prim = (VIF1Prim *)(iVar1 + 0x80);
  }
  World::AddOT((World *)&CApp::m_World,(int)param_2,prim);
  CBBPolygon::dip(this,param_2);
  return;
}

// JP: 0x003def20  Clr__8CBM413OTFv  =  CBM413OT::Clr
void CBM413OT::Clr(undefined8 this)

{
  int iVar1;
  VIF1Prim *prim;
  
  iVar1 = *(int *)((int)this + 0x7f0);
  prim = (VIF1Prim *)0x0;
  if (iVar1 != 0) {
    prim = (VIF1Prim *)(iVar1 + 0x80);
  }
  World::ReleaseOT((World *)&CApp::m_World,prim);
  CBBPolygon::Clr(this);
  return;
}

// JP: 0x003def70  __ct__8CBM413OTFiPc  =  CBM413OT::CBM413OT
undefined8 CBM413OT::CBM413OT(undefined8 this,undefined8 param_2)

{
  long lVar1;
  undefined8 uVar2;
  
  lVar1 = __nw(0xb0);
  uVar2 = 0;
  if (lVar1 != 0) {
    uVar2 = BackScreenTexture::BackScreenTexture(lVar1);
  }
  *(int *)((int)this + 0x7f0) = (int)uVar2;
  CBBPolygon::CBBPolygon(this,param_2,uVar2);
  *(undefined1 **)((int)this + 0x7e4) = CBM413OT::__vt;
  return this;
}

// JP: 0x003df2a0  __dt__6CBM524Fv  =  CBM524::~CBM524
long CBM524::~CBM524(long this,short param_2)

{
  int iVar1;
  int this;
  
  if (this != 0) {
    
    *(undefined1 **)(this + 0x7e4) = CBM524::__vt;
    iVar1 = this->i32_7fc;
    if (iVar1 != 0) {
      (**(code **)(iVar1->i32_1c + 0xc))(iVar1 + 0x14);
    }
    iVar1 = this->i32_800;
    if (iVar1 != 0) {
      (**(code **)(iVar1->i32_1c + 0xc))(iVar1 + 0x14);
    }
    iVar1 = this->i32_804;
    if (iVar1 != 0) {
      (**(code **)(iVar1->i32_1c + 0xc))(iVar1 + 0x14);
    }
    iVar1 = this->i32_808;
    if (iVar1 != 0) {
      (**(code **)(iVar1->i32_1c + 0xc))(iVar1 + 0x14);
    }
    iVar1 = this->i32_7f4;
    if (iVar1 != 0) {
      (**(code **)(iVar1->i32_1c + 0xc))(iVar1 + 0x14);
    }
    iVar1 = this->i32_7f8;
    if (iVar1 != 0) {
      (**(code **)(iVar1->i32_9c + 0xc))(iVar1 + 0x94);
    }
    CBBPolygon::~CBBPolygon(this,0);
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x003df3d0  dip__6CBM524Fi  =  CBM524::dip
void CBM524::dip(undefined8 this,undefined8 param_2)

{
  int this;
  int layer;
  VIF1Prim *prim;
  
  
  *(byte *)(this->i32_7d0 + 0xc) = *(byte *)(this->i32_7d0 + 0xc) & 0xef | 0x10;
  World::AddOTBefor
            ((World *)&CApp::m_World,*(VIF1Prim **)(this + 2000),*(VIF1Prim **)(this + 0x7f4));
  prim = (VIF1Prim *)0x0;
  if (this->i32_7f8 != 0) {
    prim = (VIF1Prim *)(this->i32_7f8 + 0x80);
  }
  World::AddOTAfter
            ((World *)&CApp::m_World,*(VIF1Prim **)(this + 2000),prim);
  layer = (int)param_2;
  World::AddOT((World *)&CApp::m_World,layer,*(VIF1Prim **)(this + 0x7fc));
  World::AddOT((World *)&CApp::m_World,layer,*(VIF1Prim **)(this + 0x800));
  World::AddOT((World *)&CApp::m_World,layer,*(VIF1Prim **)(this + 0x804));
  World::AddOT((World *)&CApp::m_World,layer,*(VIF1Prim **)(this + 0x808));
  CBBPolygon::dip(this,param_2);
  return;
}

// JP: 0x003df4b0  Clr__6CBM524Fv  =  CBM524::Clr
void CBM524::Clr(undefined8 this)

{
  VIF1Prim *prim;
  int this;
  
  
  World::ReleaseOT((World *)&CApp::m_World,*(VIF1Prim **)(this + 0x7f4));
  prim = (VIF1Prim *)0x0;
  if (this->i32_7f8 != 0) {
    prim = (VIF1Prim *)(this->i32_7f8 + 0x80);
  }
  World::ReleaseOT((World *)&CApp::m_World,prim);
  World::ReleaseOT((World *)&CApp::m_World,*(VIF1Prim **)(this + 0x7fc));
  World::ReleaseOT((World *)&CApp::m_World,*(VIF1Prim **)(this + 0x800));
  World::ReleaseOT((World *)&CApp::m_World,*(VIF1Prim **)(this + 0x804));
  World::ReleaseOT((World *)&CApp::m_World,*(VIF1Prim **)(this + 0x808));
  CBBPolygon::Clr(this);
  return;
}

// JP: 0x003df550  SetColor__6CBM524FUcUcUc  =  CBM524::SetColor
void CBM524::SetColor(int this,ulong param_2,ulong param_3,ulong param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  float *pfVar6;
  float fVar7;
  
  iVar4 = (int)param_4;
  iVar3 = (int)param_3;
  iVar2 = (int)param_2;
  iVar5 = 0;
  if (0 < this->i32_8) {
    iVar1 = 0;
    do {
      pfVar6 = (float *)(*(int *)(*(int *)(this->i32_c + 0x24) + 0xc) + iVar1);
      if ((long)param_2 < 0) {
        fVar7 = (float)(param_2 & 0xffffffff);
      }
      else {
        fVar7 = (float)iVar2;
      }
      *pfVar6 = fVar7;
      if ((long)param_3 < 0) {
        fVar7 = (float)(param_3 & 0xffffffff);
      }
      else {
        fVar7 = (float)iVar3;
      }
      pfVar6[1] = fVar7;
      if ((long)param_4 < 0) {
        fVar7 = (float)(param_4 & 0xffffffff);
      }
      else {
        fVar7 = (float)iVar4;
      }
      pfVar6[2] = fVar7;
      pfVar6[3] = 128.0;
      if ((long)param_2 < 0) {
        fVar7 = (float)(param_2 & 0xffffffff);
      }
      else {
        fVar7 = (float)iVar2;
      }
      pfVar6[4] = fVar7;
      if ((long)param_3 < 0) {
        fVar7 = (float)(param_3 & 0xffffffff);
      }
      else {
        fVar7 = (float)iVar3;
      }
      pfVar6[5] = fVar7;
      if ((long)param_4 < 0) {
        fVar7 = (float)(param_4 & 0xffffffff);
      }
      else {
        fVar7 = (float)iVar4;
      }
      pfVar6[6] = fVar7;
      pfVar6[7] = 128.0;
      if ((long)param_2 < 0) {
        fVar7 = (float)(param_2 & 0xffffffff);
      }
      else {
        fVar7 = (float)iVar2;
      }
      *(float *)(this->i32_c + 0x1f0) = fVar7;
      if ((long)param_3 < 0) {
        fVar7 = (float)(param_3 & 0xffffffff);
      }
      else {
        fVar7 = (float)iVar3;
      }
      *(float *)(this->i32_c + 500) = fVar7;
      if ((long)param_4 < 0) {
        fVar7 = (float)(param_4 & 0xffffffff);
      }
      else {
        fVar7 = (float)iVar4;
      }
      iVar5 = iVar5 + 1;
      *(float *)(this->i32_c + 0x1f8) = fVar7;
      iVar1 = iVar1 + 0x20;
    } while (iVar5 < this->i32_8);
  }
  return;
}

// JP: 0x003df730  AddTime__6CBM524Ff  =  CBM524::AddTime
void CBM524::AddTime(float this,int param_2)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 auStack_140 [8];
  undefined4 uStack_138;
  undefined4 uStack_134;
  undefined1 auStack_130 [8];
  undefined4 uStack_128;
  undefined4 uStack_124;
  undefined1 auStack_120 [8];
  undefined4 uStack_118;
  undefined4 uStack_114;
  undefined4 uStack_110;
  undefined4 uStack_10c;
  undefined4 uStack_108;
  undefined4 uStack_104;
  undefined1 auStack_100 [8];
  undefined4 uStack_f8;
  undefined4 uStack_f4;
  undefined1 auStack_f0 [8];
  undefined4 uStack_e8;
  undefined4 uStack_e4;
  undefined4 uStack_e0;
  undefined4 uStack_dc;
  undefined4 uStack_d8;
  undefined4 uStack_d4;
  undefined1 auStack_d0 [8];
  undefined4 uStack_c8;
  undefined4 uStack_c4;
  undefined4 uStack_c0;
  undefined4 uStack_bc;
  undefined4 uStack_b8;
  undefined4 uStack_b4;
  undefined1 auStack_b0 [64];
  undefined1 auStack_70 [16];
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined1 auStack_50 [64];
  undefined1 auStack_10 [16];
  
  if (param_2->i32_7d4 == 0) {
    uVar3 = Frame::searchFrame(*(undefined4 *)(param_2->i32_7d0 + 0x30),0x403e28);
    param_2->u32_7d4 = uVar3;
  }
  if ((param_2->i32_7d4 != 0) && (this != 0.0)) {
    Frame::getWorldPos(auStack_10,param_2->i32_7d4,VIF1Prim::m_Env & 1);
    Frame::getWorldRot(auStack_50,param_2->u32_7d4,VIF1Prim::m_Env & 1);
    uStack_60 = 0x3f666666;
    uStack_5c = 0;
    uStack_54 = 0x3f800000;
    uStack_58 = 0;
    Matrix::ApplyMatrix(auStack_d0,auStack_50,&uStack_60);
    uStack_60 = auStack_d0._0_4_;
    uStack_5c = auStack_d0._4_4_;
    uStack_58 = uStack_c8;
    uStack_54 = uStack_c4;
    CPathControl::AddPath
              (param_2->u32_7fc,auStack_10,&uStack_60);
    CPathControl::AddTime(this,param_2->u32_7fc);
    uStack_dc = 0x3f666666;
    uStack_e0 = 0;
    uStack_d4 = 0x3f800000;
    uStack_d8 = 0;
    uStack_60 = 0;
    uStack_5c = 0x3f666666;
    uStack_58 = 0;
    uStack_54 = 0x3f800000;
    Matrix::ApplyMatrix(auStack_f0,auStack_50,&uStack_60);
    uStack_60 = auStack_f0._0_4_;
    uStack_5c = auStack_f0._4_4_;
    uStack_58 = uStack_e8;
    uStack_54 = uStack_e4;
    CPathControl::AddPath
              (param_2->u32_804,auStack_10,&uStack_60);
    CPathControl::AddTime(this,param_2->u32_804);
  }
  if (param_2->i32_7d8 == 0) {
    uVar3 = Frame::searchFrame(*(undefined4 *)(param_2->i32_7d0 + 0x30),0x403e30);
    param_2->u32_7d8 = uVar3;
  }
  if ((param_2->i32_7d8 != 0) && (this != 0.0)) {
    Frame::getWorldPos(auStack_70,param_2->i32_7d8,VIF1Prim::m_Env & 1);
    Frame::getWorldRot(auStack_b0,param_2->u32_7d8,VIF1Prim::m_Env & 1);
    uStack_c0 = 0x3f666666;
    uStack_bc = 0;
    uStack_b4 = 0x3f800000;
    uStack_b8 = 0;
    Matrix::ApplyMatrix(auStack_100,auStack_b0,&uStack_c0);
    uStack_c0 = auStack_100._0_4_;
    uStack_bc = auStack_100._4_4_;
    uStack_b8 = uStack_f8;
    uStack_b4 = uStack_f4;
    CPathControl::AddPath
              (param_2->u32_800,auStack_70,&uStack_c0);
    CPathControl::AddTime(this,param_2->u32_800);
    uStack_10c = 0x3f666666;
    uStack_110 = 0;
    uStack_104 = 0x3f800000;
    uStack_108 = 0;
    uStack_c0 = 0;
    uStack_bc = 0x3f666666;
    uStack_b8 = 0;
    uStack_b4 = 0x3f800000;
    Matrix::ApplyMatrix(auStack_120,auStack_b0,&uStack_c0);
    uStack_c0 = auStack_120._0_4_;
    uStack_bc = auStack_120._4_4_;
    uStack_b8 = uStack_118;
    uStack_b4 = uStack_114;
    CPathControl::AddPath
              (param_2->u32_808,auStack_70,&uStack_c0);
    CPathControl::AddTime(this,param_2->u32_808);
  }
  puVar1 = *(undefined4 **)(*(int *)(param_2->i32_c + 0x24) + 4);
  if (param_2->i32_7d4 != 0) {
    Frame::getWorldPos(auStack_130,param_2->i32_7d4,VIF1Prim::m_Env & 1);
    *puVar1 = auStack_130._0_4_;
    puVar1[1] = auStack_130._4_4_;
    puVar1[2] = uStack_128;
    puVar1[3] = uStack_124;
  }
  iVar2 = *(int *)(*(int *)(param_2->i32_c + 0x24) + 4);
  if (param_2->i32_7d8 != 0) {
    Frame::getWorldPos(auStack_140,param_2->i32_7d8,VIF1Prim::m_Env & 1);
    iVar2->i32_20 = auStack_140._0_4_;
    iVar2->i32_24 = auStack_140._4_4_;
    iVar2->u32_28 = uStack_138;
    iVar2->u32_2c = uStack_134;
  }
  return;
}

// JP: 0x003dfa60  Reset__6CBM524Fv  =  CBM524::Reset
void CBM524::Reset(int this)

{
  CPathControl::ClearPath(this->u32_7fc);
  CPathControl::ClearPath(this->u32_800);
  CPathControl::ClearPath(this->u32_804);
  CPathControl::ClearPath(this->u32_808);
  return;
}

// JP: 0x003dfaa0  Initialization__6CBM524Fv  =  CBM524::Initialization
void CBM524::Initialization(undefined8 this)

{
  undefined4 uVar1;
  long lVar2;
  undefined8 uVar3;
  int this;
  int iVar5;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  
  GetFileCount(this->u32_7f0);
  lVar2 = __nw(0x28);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = FrameChange::FrameChange(lVar2);
  }
  this->u32_7f4 = uVar1;
  lVar2 = __nw(0xb0);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = WriteTexture::WriteTexture(lVar2);
  }
  this->u32_7f8 = uVar1;
  lVar2 = __nw(0x5b0);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = CPathControl::CPathControl(lVar2);
  }
  this->u32_7fc = uVar1;
  CPathControl::Create(0x3f000000,this->u32_7fc,0x28);
  uVar3 = GetFileEntry(this->u32_7f0,0);
  CPathControl::CreateTexture(this->u32_7fc,uVar3);
  CPathControl::changeGSAlpha(this->u32_7fc,0,2,0,1,0);
  lVar2 = __nw(0x5b0);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = CPathControl::CPathControl(lVar2);
  }
  this->u32_800 = uVar1;
  CPathControl::Create(0x3f000000,this->u32_800,0x28);
  uVar3 = GetFileEntry(this->u32_7f0,0);
  CPathControl::CreateTexture(this->u32_800,uVar3);
  CPathControl::changeGSAlpha(this->u32_800,0,2,0,1,0);
  lVar2 = __nw(0x5b0);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = CPathControl::CPathControl(lVar2);
  }
  this->u32_804 = uVar1;
  CPathControl::Create(0x3f000000,this->u32_804,0x28);
  uVar3 = GetFileEntry(this->u32_7f0,0);
  CPathControl::CreateTexture(this->u32_804,uVar3);
  CPathControl::changeGSAlpha(this->u32_804,0,2,0,1,0);
  lVar2 = __nw(0x5b0);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = CPathControl::CPathControl(lVar2);
  }
  this->u32_808 = uVar1;
  CPathControl::Create(0x3f000000,this->u32_808,0x28);
  uVar3 = GetFileEntry(this->u32_7f0,0);
  CPathControl::CreateTexture(this->u32_808,uVar3);
  CPathControl::changeGSAlpha(this->u32_808,0,2,0,1,0);
  uStack_10 = 0x43000000;
  uStack_c = 0x43000000;
  uStack_8 = 0x43000000;
  uStack_4 = 0x43000000;
  CPathControl::AddColorKey(0,this->u32_7fc);
  CPathControl::AddColorKey(0,this->u32_800,&uStack_10);
  CPathControl::AddColorKey(0,this->u32_804,&uStack_10);
  CPathControl::AddColorKey(0,this->u32_808,&uStack_10);
  uStack_10 = 0x43000000;
  uStack_c = 0x43000000;
  uStack_8 = 0x43000000;
  uStack_4 = 0x43000000;
  CPathControl::AddColorKey(0x3f000000,this->u32_7fc);
  CPathControl::AddColorKey(0x3f000000,this->u32_800,&uStack_10);
  CPathControl::AddColorKey(0x3f000000,this->u32_804,&uStack_10);
  CPathControl::AddColorKey(0x3f000000,this->u32_808,&uStack_10);
  uStack_20 = 0;
  uStack_1c = 0;
  uStack_18 = 0;
  uStack_14 = 0x3f800000;
  CPathControl::AddSTKey(0,this->u32_7fc,&uStack_20);
  CPathControl::AddSTKey(0,this->u32_800,&uStack_20);
  CPathControl::AddSTKey(0,this->u32_804,&uStack_20);
  CPathControl::AddSTKey(0,this->u32_808,&uStack_20);
  uStack_20 = 0x3f800000;
  uStack_1c = 0;
  uStack_18 = 0x3f800000;
  uStack_14 = 0x3f800000;
  CPathControl::AddSTKey(0x3f000000,this->u32_7fc,&uStack_20);
  CPathControl::AddSTKey(0x3f000000,this->u32_800,&uStack_20);
  CPathControl::AddSTKey(0x3f000000,this->u32_804,&uStack_20);
  CPathControl::AddSTKey(0x3f000000,this->u32_808,&uStack_20);
  WriteTexture::Init(this->u32_7f8,0x200,0x1c0);
  Texture::createRegsterPacket
            (*(Texture **)(this + 0x7f8),1,0,0x2a00,(*(Texture **)(this + 0x7f8))[1].dwRegPkt1,9,9
             ,0);
  WriteTexture::setValue(0x3ecccccd,this->u32_7f8);
  PolyBase::initPacket(this->u32_c);
  iVar5 = *(int *)(this->i32_c + 0x230);
  if (iVar5 != 0) {
    Texture::changeGSAlpha(iVar5,0,2,0,1,0);
    Texture::changeGSTest(*(undefined4 *)(this->i32_c + 0x230),1,0,0,3,0,0,1);
  }
  for (iVar5 = 0; iVar5 < this->i32_8; iVar5 = iVar5 + 1) {
    (**(code **)(this->i32_7e4 + 0x24))(this,iVar5);
  }
  return;
}

// JP: 0x003dff50  NewLifeMake__6CBM524Fi  =  CBM524::NewLifeMake
void CBM524::NewLifeMake(int this,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = (undefined4 *)(this->i32_10 + param_2 * 0x20);
  iVar1 = *(int *)(*(int *)(this->i32_c + 0x24) + 4);
  *puVar2 = 0;
  iVar1 = iVar1 + param_2 * 0x20;
  puVar2[4] = 0;
  puVar2[5] = 0;
  puVar2[6] = 0;
  puVar2[7] = 0x3f800000;
  puVar2[1] = 0x447a0000;
  iVar1->u32_10 = 0xbf666666;
  iVar1->u32_14 = 0xbf666666;
  iVar1->u32_18 = 0;
  iVar1->u32_1c = 0x3f800000;
  return;
}
