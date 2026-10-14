// decomp/D/EffectBarin.c — cleaned Ghidra output (SLPM_602.19, Metrowerks MIPS), Shadow Hearts: Covenant JP demo.
// Field accesses are shown as this->T_off (T = u8/u16/u32/f32/i32/p, off = hex offset);
// JRing fields are named from the recovered struct. See notes/D/*.md for layouts.
// CAVEAT: when the base pointer is a float*/int*/short*, the number in `T_off` is an ELEMENT offset (byte offset = off*sizeof(elem)).
// `this` is the C++ this pointer (param_1); the Metrowerks ABI passes it in a0.

// JP: 0x00321e20  __ct__11EffectBarinFv  =  EffectBarin::EffectBarin
/* WARNING: Removing unreachable block (ram,0x003221b4) */

VIF1Prim * EffectBarin::EffectBarin(VIF1Prim *this)

{
  uint uVar1;
  undefined8 uVar2;
  uint *puVar3;
  float fVar4;
  void *pvVar5;
  float fVar6;
  float fVar7;
  
  VIF1Prim::VIF1Prim(this);
  DelayDeleteObject::DelayDeleteObject(this + 1);
  FBufTex::FBufTex(&this[1].bFlags,1);
  this->pVptr = EffectBarin::__vt;
  this[1].dwEnv = 0x406be0;
  this[0xd].bFlags = 0xf0;
  this[0xd].b_pad0d = 0x6b;
  this[0xd].nZvolume = 0x40;
  LocalHostImage::LocalHostImage(&this[0xf].dw_unk4);
  puVar3 = &this[0x42].dwEnv;
  do {
    _QWD::_QWD(puVar3);
    puVar3 = puVar3 + 4;
  } while (puVar3 != &this[0x47].dw_unk4);
  Matrix::Matrix(this + 0x48);
  uVar2 = GsxCamera::GetViewMatrix(CApp::camera);
  Matrix::__as(this + 0x48,uVar2);
  this[0x41].bFlags = 0;
  this[0x41].b_pad0d = 0;
  this[0x41].nZvolume = 0;
  Init__Q211EffectBarin23_class_1589EffBarin_cppFv(&this[0xe].dwEnv);
  this[0x47].dw_unk4 =
       (uint)(((*(float *)&this[0x49].bFlags + (float)this[0x4a].dwEnv) - 1792.0) /
             -(float)this[0x48].dw_unk0);
  fVar4 = *(float *)&this[0x49].bFlags;
  fVar6 = (float)this[0x48].dw_unk0;
  this[0x47].dwEnv =
       (uint)((((float)this[0x49].pVptr + *(float *)&this[0x4a].bFlags) - 1824.0) /
             -(float)this[0x49].dw_unk0);
  pvVar5 = this[0x49].pVptr;
  fVar7 = (float)this[0x49].dw_unk0;
  *(float *)&this[0x47].bFlags =
       (((fVar4 + (float)this[0x4a].dwEnv) - 2304.0) / -fVar6 - (float)this[0x47].dw_unk4) /
       512.0;
  this[0x47].pVptr =
       (void *)(((((float)pvVar5 + *(float *)&this[0x4a].bFlags) - 2272.0) / -fVar7 -
                (float)this[0x47].dwEnv) / 448.0);
  uVar1 = __nwa(0x670);
  this->dw_unk0 = uVar1;
  uVar1 = __nwa(0x670);
  this->dw_unk4 = uVar1;
  memset((void *)this->dw_unk0,0,0x670);
  memset((void *)this->dw_unk4,0,0x670);
  memset(&this[0x42].dwEnv,0,0x60);
  this[0x42].dwEnv = 0x60000005;
  this[0x43].dw_unk0 = 0x50000005;
  this[0x43].dw_unk4 = 4;
  this[0x43].dwEnv = 0x10000000;
  this[0x43].bFlags = 0xe;
  this[0x43].b_pad0d = 0;
  this[0x43].nZvolume = 0;
  this[0x43].pVptr = (void *)0x0;
  this[0x44].dw_unk0 = 0x50000;
  this[0x44].dw_unk4 = 0;
  this[0x44].dwEnv = 0x47;
  this[0x44].bFlags = 0;
  this[0x44].b_pad0d = 0;
  this[0x44].nZvolume = 0;
  *(undefined8 *)&this[0x44].pVptr = 1;
  this[0x45].dw_unk4 = 0x14;
  this[0x45].dwEnv = 0;
  this[0x45].bFlags = 5;
  this[0x45].b_pad0d = 0;
  this[0x45].nZvolume = 0;
  this[0x45].pVptr = (void *)0x0;
  this[0x46].dw_unk0 = 8;
  this[0x46].dw_unk4 = 0;
  this[0x46].dwEnv = 0x44;
  this[0x46].bFlags = 0;
  this[0x46].b_pad0d = 0;
  this[0x46].nZvolume = 0;
  *(undefined8 *)&this[0x46].pVptr = 0x42;
  LocalHostImage::Create
            (&this[0xf].dw_unk4,
             (int)((uint)*(ushort *)
                          (CApp::camera + (uint)(CApp::camera->i8_394 == '\0') * 2 +
                          0x38c) * 0x800) >> 6,0x200,1,0,0,0x200,0x1c0);
  LocalHostImage::StoreImage(&this[0xf].dw_unk4);
  uVar2 = GetBekijo(0x200);
  LocalHostImage::CreateLoadImagePacket(&this[0xf].dw_unk4,0x2a00,uVar2,uVar2);
  return this;
}

// JP: 0x00322280  __dt__11EffectBarinFv  =  EffectBarin::~EffectBarin
int * EffectBarin::~EffectBarin(int *this,short param_2)

{
  int iVar1;
  
  if (this != (int *)0x0) {
    this[4] = (int)EffectBarin::__vt;
    this[7] = 0x406be0;
    this[0x44] = 0x406bf0;
    if (*this != 0) {
      __dla(*this);
      *this = 0;
    }
    if (this[1] != 0) {
      __dla(this[1]);
      this[1] = 0;
    }
    if (this[0x148] != 0) {
      iVar1 = this[0x148];
      if (iVar1 != 0) {
        (**(code **)(iVar1->i32_a8 + 0xc))(iVar1,1);
      }
      this[0x148] = 0;
    }
    LocalHostImage::~LocalHostImage(this + 0x4c,0xffffffffffffffff);
    FBufTex::~FBufTex(this + 8,0);
    DelayDeleteObject::~DelayDeleteObject(this + 5,0);
    VIF1Prim::~VIF1Prim(this,0);
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x003223f0  getPacket__11EffectBarinFv  =  EffectBarin::getPacket
undefined4 EffectBarin::getPacket(int this)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  
  puVar3 = *(undefined4 **)(this + (VIF1Prim::m_Env & 1) * 4);
  *puVar3 = 0x50000000;
  puVar3[1] = this + 0x1c0;
  puVar3[3] = 0x13000000;
  puVar3[4] = 0x50000000;
  puVar3[5] = this + 0x530;
  puVar3 = puVar3 + 8;
  for (iVar2 = this->i32_520; iVar2 != 0; iVar2 = CList::GetNext(iVar2)) {
    *puVar3 = 0x50000000;
    uVar1 = FreePol::GetPacket(iVar2,this + 0x5a0);
    puVar3[1] = uVar1;
    puVar3 = puVar3 + 4;
  }
  *puVar3 = 0x60000000;
  return *(undefined4 *)(this + (VIF1Prim::m_Env & 1) * 4);
}

// JP: 0x003224e0  PixelTo3D__11EffectBarinFff  =  EffectBarin::PixelTo3D
void EffectBarin::PixelTo3D(float this,float param_2,undefined4 param_3,int param_4)

{
  undefined1 auStack_50 [16];
  undefined4 uStack_40;
  int iStack_30;
  float fStack_20;
  float fStack_10;
  
  uStack_40 = param_3;
  iStack_30 = param_4;
  fStack_20 = this;
  fStack_10 = param_2;
  FVector::FVector(param_4->f32_590 + this * param_4->f32_598,
                      param_4->f32_594 + param_2 * param_4->f32_59c,0x3f800000
                      ,0x3f800000,auStack_50);
  FVector::FVector(uStack_40,auStack_50);
  return;
}

// JP: 0x00322570  AddPolygon__11EffectBarinFP7FreePol  =  EffectBarin::AddPolygon
void EffectBarin::AddPolygon(int this,int param_2)

{
  float *pfVar1;
  undefined4 *puVar2;
  int iVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  
  for (iVar3 = 0; iVar3 < param_2->i32_8; iVar3 = iVar3 + 1) {
    pfVar1 = (float *)FVector::vx(param_2->i32_10 + iVar3 * 0x10);
    fVar4 = *pfVar1;
    fVar5 = this->f32_590;
    fVar6 = this->f32_598;
    pfVar1 = (float *)FVector::vx(param_2->i32_14 + iVar3 * 0x10);
    *pfVar1 = ((fVar4 - fVar5) / fVar6) / 512.0;
    pfVar1 = (float *)FVector::vy(param_2->i32_10 + iVar3 * 0x10);
    fVar4 = *pfVar1;
    fVar5 = this->f32_594;
    fVar6 = this->f32_59c;
    pfVar1 = (float *)FVector::vy(param_2->i32_14 + iVar3 * 0x10);
    *pfVar1 = (((fVar4 - fVar5) / fVar6) / 448.0) * 0.875;
    puVar2 = (undefined4 *)FVector::vz(param_2->i32_14 + iVar3 * 0x10);
    *puVar2 = 0x3f800000;
  }
  FreePol::CalcCenter(param_2);
  FreePol::CalcOffset(param_2);
  if (this->i32_520 == 0) {
    this->i32_520 = param_2;
  }
  else {
    CList::Add(this->u32_520,param_2);
  }
  return;
}

// JP: 0x00322710  AddTime__11EffectBarinFf  =  EffectBarin::AddTime
void EffectBarin::AddTime(int this)

{
  int iVar1;
  
  if ((this->u8_120 & 1) != 0) {
    for (iVar1 = this->i32_520; iVar1 != 0; iVar1 = CList::GetNext(iVar1)) {
      (**(code **)(iVar1->i32_a8 + 8))();
    }
  }
  return;
}
