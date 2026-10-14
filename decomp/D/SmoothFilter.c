// decomp/D/SmoothFilter.c — cleaned Ghidra output (SLPM_602.19, Metrowerks MIPS), Shadow Hearts: Covenant JP demo.
// Field accesses are shown as this->T_off (T = u8/u16/u32/f32/i32/p, off = hex offset);
// JRing fields are named from the recovered struct. See notes/D/*.md for layouts.
// CAVEAT: when the base pointer is a float*/int*/short*, the number in `T_off` is an ELEMENT offset (byte offset = off*sizeof(elem)).
// `this` is the C++ this pointer (param_1); the Metrowerks ABI passes it in a0.

// JP: 0x0038e4e0  __ct__12SmoothFilterFv  =  SmoothFilter::SmoothFilter
VIF1Prim * SmoothFilter::SmoothFilter(VIF1Prim *this)

{
  undefined4 uVar1;
  void *pvVar2;
  uint uVar3;
  long lVar4;
  
  VIF1Prim::VIF1Prim(this);
  DelayDeleteObject::DelayDeleteObject(this + 1);
  this->pVptr = SmoothFilter::__vt;
  this[1].dwEnv = 0x407100;
  uVar1 = __nwa(0x140);
  this[1].bFlags = (char)uVar1;
  this[1].b_pad0d = (char)((uint)uVar1 >> 8);
  this[1].nZvolume = (short)((uint)uVar1 >> 0x10);
  pvVar2 = (void *)__nwa(0x140);
  this[1].pVptr = pvVar2;
  uVar1._0_1_ = this[1].bFlags;
  uVar1._1_1_ = this[1].b_pad0d;
  uVar1._2_2_ = this[1].nZvolume;
  Memset128(uVar1,0,0x14);
  Memset128(this[1].pVptr,0,0x14);
  lVar4 = __nw(0x80);
  uVar3 = 0;
  if (lVar4 != 0) {
    uVar3 = gTexture::gTexture(lVar4,0x200,0x1c0);
  }
  this[2].dw_unk0 = uVar3;
  Texture::createRegsterPacket((Texture *)this[2].dw_unk0,1,0,0,0x200,9,9,1);
  lVar4 = __nw(0xb0);
  uVar3 = 0;
  if (lVar4 != 0) {
    uVar3 = ScreenTexture::ScreenTexture(lVar4);
  }
  this[2].dw_unk4 = uVar3;
  ScreenTexture::Init(this[2].dw_unk4,0x200,0x1c0);
  Texture::createRegsterPacket
            ((Texture *)this[2].dw_unk4,1,0,0,*(int *)(this[2].dw_unk4 + 0x68),9,9,0);
  this[2].dwEnv = 0x80;
  this[2].bFlags = 0xd0;
  this[2].b_pad0d = 0xe3;
  this[2].nZvolume = 0x4b7f;
  return this;
}

// JP: 0x0038e710  LayerSetUp__12SmoothFilterFi  =  SmoothFilter::LayerSetUp
int SmoothFilter::LayerSetUp(VIF1Prim *this,int param_2)

{
  int iVar1;
  VIF1Prim *prim;
  
  prim = (VIF1Prim *)0x0;
  if (this[2].dw_unk4 != 0) {
    prim = (VIF1Prim *)(this[2].dw_unk4 + 0x80);
  }
  World::AddOT((World *)&CApp::m_World,param_2,prim);
  iVar1 = World::AddOT((World *)&CApp::m_World,param_2,this);
  return iVar1;
}

// JP: 0x0038e780  LayerRelease__12SmoothFilterFv  =  SmoothFilter::LayerRelease
int SmoothFilter::LayerRelease(VIF1Prim *this)

{
  int iVar1;
  VIF1Prim *prim;
  
  prim = (VIF1Prim *)0x0;
  if (this[2].dw_unk4 != 0) {
    prim = (VIF1Prim *)(this[2].dw_unk4 + 0x80);
  }
  World::ReleaseOT((World *)&CApp::m_World,prim);
  iVar1 = World::ReleaseOT((World *)&CApp::m_World,this);
  return iVar1;
}

// JP: 0x0038e7f0  __dt__12SmoothFilterFv  =  SmoothFilter::~SmoothFilter
int SmoothFilter::~SmoothFilter(int this,short param_2)

{
  int iVar1;
  
  if (this != 0) {
    *(undefined1 **)(this + 0x10) = SmoothFilter::__vt;
    this->u32_1c = 0x407100;
    if (this->i32_20 != 0) {
      __dla(this->u32_20);
      this->u32_20 = 0;
    }
    if (this->i32_24 != 0) {
      __dla(this->u32_24);
      this->u32_24 = 0;
    }
    if (this->i32_28 != 0) {
      gTexture::~gTexture(this->u32_28,1);
      this->u32_28 = 0;
    }
    if (this->i32_2c != 0) {
      iVar1 = this->i32_2c;
      if (iVar1 != 0) {
        (**(code **)(iVar1->i32_a0 + 0x28))(iVar1,1);
      }
      this->u32_2c = 0;
    }
    DelayDeleteObject::~DelayDeleteObject(this + 0x14,0);
    VIF1Prim::~VIF1Prim(this,0);
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x0038e950  FilterLevel__12SmoothFilterFf  =  SmoothFilter::FilterLevel
void SmoothFilter::FilterLevel(undefined4 this,int param_2)

{
  ScreenTexture::setValue(this,param_2->u32_2c);
  return;
}

// JP: 0x0038e990  FilterAlpha__12SmoothFilterFi  =  SmoothFilter::FilterAlpha
void SmoothFilter::FilterAlpha(int this,undefined4 param_2)

{
  this->u32_30 = param_2;
  return;
}

// JP: 0x0038e9c0  getPacket__12SmoothFilterFv  =  SmoothFilter::getPacket
undefined4 SmoothFilter::getPacket(int this)

{
  undefined4 uVar1;
  long lVar2;
  ulong uVar3;
  int iVar4;
  float fVar5;
  int aiStack_18 [6];
  
  aiStack_18[0] = this->i32_20;
  aiStack_18[1] = this->u32_24;
  aiStack_18[2] = this;
  Memset128(*(undefined4 *)(this + (VIF1Prim::m_Env & 1) * 4 + 0x20),0,0x14);
  *(undefined4 *)aiStack_18[VIF1Prim::m_Env & 1] = 0x50000000;
  *(undefined4 *)(aiStack_18[VIF1Prim::m_Env & 1] + 4) =
       *(undefined4 *)(*(int *)(aiStack_18[2] + 0x28) + 0x18);
  *(undefined4 *)(aiStack_18[VIF1Prim::m_Env & 1] + 8) = 0x13000000;
  aiStack_18[VIF1Prim::m_Env & 1] = aiStack_18[VIF1Prim::m_Env & 1] + 0x10;
  *(undefined4 *)aiStack_18[VIF1Prim::m_Env & 1] = 0x30000003;
  uVar1 = Texture::getTex0GsPacket
                    (*(undefined4 *)(aiStack_18[2] + 0x28),0,0x2a00,0xffffffffffffffff,
                     0xffffffffffffffff);
  *(undefined4 *)(aiStack_18[VIF1Prim::m_Env & 1] + 4) = uVar1;
  *(undefined4 *)(aiStack_18[VIF1Prim::m_Env & 1] + 0xc) = 0x50000003;
  aiStack_18[VIF1Prim::m_Env & 1] = aiStack_18[VIF1Prim::m_Env & 1] + 0x10;
  *(undefined4 *)aiStack_18[VIF1Prim::m_Env & 1] = 0x10000005;
  *(undefined4 *)(aiStack_18[VIF1Prim::m_Env & 1] + 0xc) = 0x50000005;
  aiStack_18[VIF1Prim::m_Env & 1] = aiStack_18[VIF1Prim::m_Env & 1] + 0x10;
  *(undefined8 *)aiStack_18[VIF1Prim::m_Env & 1] = 0x1000000000000004;
  *(undefined8 *)(aiStack_18[VIF1Prim::m_Env & 1] + 8) = 0xe;
  aiStack_18[VIF1Prim::m_Env & 1] = aiStack_18[VIF1Prim::m_Env & 1] + 0x10;
  *(undefined8 *)(aiStack_18[VIF1Prim::m_Env & 1] + 8) = 0x43;
  *(undefined8 *)aiStack_18[VIF1Prim::m_Env & 1] = 0x44;
  aiStack_18[VIF1Prim::m_Env & 1] = aiStack_18[VIF1Prim::m_Env & 1] + 0x10;
  *(undefined8 *)(aiStack_18[VIF1Prim::m_Env & 1] + 8) = 0x48;
  *(undefined8 *)aiStack_18[VIF1Prim::m_Env & 1] = 0x53001;
  aiStack_18[VIF1Prim::m_Env & 1] = aiStack_18[VIF1Prim::m_Env & 1] + 0x10;
  *(undefined8 *)(aiStack_18[VIF1Prim::m_Env & 1] + 8) = 0x19;
  *(undefined8 *)aiStack_18[VIF1Prim::m_Env & 1] = 0x720000007000;
  aiStack_18[VIF1Prim::m_Env & 1] = aiStack_18[VIF1Prim::m_Env & 1] + 0x10;
  *(undefined8 *)(aiStack_18[VIF1Prim::m_Env & 1] + 8) = 0;
  *(undefined8 *)aiStack_18[VIF1Prim::m_Env & 1] = 0x356;
  aiStack_18[VIF1Prim::m_Env & 1] = aiStack_18[VIF1Prim::m_Env & 1] + 0x10;
  for (iVar4 = 0; iVar4 < 1; iVar4 = iVar4 + 1) {
    *(undefined4 **)aiStack_18[VIF1Prim::m_Env & 1] = &DAT_10000004;
    *(undefined4 *)(aiStack_18[VIF1Prim::m_Env & 1] + 0xc) = 0x50000004;
    aiStack_18[VIF1Prim::m_Env & 1] = aiStack_18[VIF1Prim::m_Env & 1] + 0x10;
    *(undefined8 *)aiStack_18[VIF1Prim::m_Env & 1] = 0x3400000000008002;
    *(undefined8 *)(aiStack_18[VIF1Prim::m_Env & 1] + 8) = 0x513;
    aiStack_18[VIF1Prim::m_Env & 1] = aiStack_18[VIF1Prim::m_Env & 1] + 0x10;
    *(undefined8 *)aiStack_18[VIF1Prim::m_Env & 1] = 0x80008;
    *(undefined8 *)(aiStack_18[VIF1Prim::m_Env & 1] + 8) = 0x3f80000040808080;
    aiStack_18[VIF1Prim::m_Env & 1] = aiStack_18[VIF1Prim::m_Env & 1] + 0x10;
    lVar2 = __fixunssfdi(*(undefined4 *)(aiStack_18[2] + 0x34));
    *(ulong *)aiStack_18[VIF1Prim::m_Env & 1] = lVar2 << 0x20 | 0x72007000;
    fVar5 = (float)ScreenTexture::getW(*(undefined4 *)(aiStack_18[2] + 0x2c));
    uVar3 = __fixunssfdi((fVar5 + 0.5) * 16.0);
    fVar5 = (float)ScreenTexture::getH(*(undefined4 *)(aiStack_18[2] + 0x2c));
    lVar2 = __fixunssfdi((fVar5 + 0.5) * 16.0);
    *(ulong *)(aiStack_18[VIF1Prim::m_Env & 1] + 8) = uVar3 | lVar2 << 0x10;
    aiStack_18[VIF1Prim::m_Env & 1] = aiStack_18[VIF1Prim::m_Env & 1] + 0x10;
    *(ulong *)aiStack_18[VIF1Prim::m_Env & 1] =
         (long)*(int *)(aiStack_18[2] + 0x30) << 0x18 | 0x3f80000000808080;
    lVar2 = __fixunssfdi(*(undefined4 *)(aiStack_18[2] + 0x34));
    *(ulong *)(aiStack_18[VIF1Prim::m_Env & 1] + 8) = lVar2 << 0x20 | 0x8e009000;
    aiStack_18[VIF1Prim::m_Env & 1] = aiStack_18[VIF1Prim::m_Env & 1] + 0x10;
  }
  *(undefined4 *)aiStack_18[VIF1Prim::m_Env & 1] = 0x60000000;
  aiStack_18[VIF1Prim::m_Env & 1] = aiStack_18[VIF1Prim::m_Env & 1] + 0x10;
  return *(undefined4 *)(aiStack_18[2] + (VIF1Prim::m_Env & 1) * 4 + 0x20);
}
