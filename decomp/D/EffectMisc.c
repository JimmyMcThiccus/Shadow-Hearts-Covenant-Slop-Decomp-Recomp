// decomp/D/EffectMisc.c — cleaned Ghidra output (SLPM_602.19, Metrowerks MIPS), Shadow Hearts: Covenant JP demo.
// Field accesses are shown as this->T_off (T = u8/u16/u32/f32/i32/p, off = hex offset);
// JRing fields are named from the recovered struct. See notes/D/*.md for layouts.
// CAVEAT: when the base pointer is a float*/int*/short*, the number in `T_off` is an ELEMENT offset (byte offset = off*sizeof(elem)).
// `this` is the C++ this pointer (param_1); the Metrowerks ABI passes it in a0.

// JP: 0x00313a10  __ct__12EffectSpriteFP7FVectorP7FVectorP7FVectorP7FVectorP7FVectori  =  EffectSprite::EffectSprite
VIF1Prim *
EffectSprite::EffectSprite
          (VIF1Prim *this,undefined4 param_2,undefined4 param_3,undefined4 param_4,int param_5,
          undefined4 param_6,undefined4 param_7)

{
  undefined4 *__s;
  void *__s_00;
  uint uVar1;
  
  VIF1Prim::VIF1Prim(this);
  DelayDeleteObject::DelayDeleteObject(this + 1);
  this->pVptr = EffectSprite::__vt;
  this[1].dwEnv = 0x406a00;
  FVector::FVector(&this[1].bFlags);
  FVector::FVector(&this[2].dwEnv);
  FVector::FVector(&this[3].dw_unk4);
  FVector::FVector(this + 4);
  FVector::FVector(&this[4].pVptr);
  *(undefined1 *)&this[5].pVptr = 0;
  FVector::__as(&this[1].bFlags,param_2);
  FVector::__as(&this[2].dwEnv,param_3);
  FVector::__as(&this[3].dw_unk4,param_4);
  this[5].bFlags = (char)param_7;
  this[5].b_pad0d = (char)((uint)param_7 >> 8);
  this[5].nZvolume = (short)((uint)param_7 >> 0x10);
  if (param_5 != 0) {
    FVector::__as(this + 4,param_5);
    FVector::__as(&this[4].pVptr,param_6);
    *(undefined1 *)&this[5].pVptr = 1;
  }
  uVar1 = __nwa(0x70);
  this->dw_unk0 = uVar1;
  uVar1 = __nwa(0x70);
  this->dw_unk4 = uVar1;
  __s = (undefined4 *)this->dw_unk0;
  __s_00 = (void *)this->dw_unk4;
  memset(__s,0,0x70);
  memset(__s_00,0,0x70);
  *__s = 0x60000006;
  __s[2] = 0x13000000;
  __s[3] = 0x50000006;
  _QWD::__as(__s_00,__s);
  __s->u64_4 = 0x5023400000008001;
  __s->u64_6 = 0x551ee;
  _QWD::__as((int)__s_00 + 0x10,__s + 4);
  this[6].dw_unk0 = 0x33001;
  this[6].dw_unk4 = 0;
  __s->u64_8 = this->u64_6;
  __s->u64_a = 0x47;
  _QWD::__as((int)__s_00 + 0x20,__s + 8);
  this[6].dwEnv = 0x44;
  this[6].bFlags = 0;
  this[6].b_pad0d = 0;
  this[6].nZvolume = 0;
  __s->u64_c = *(undefined8 *)&this[6].dwEnv;
  __s->u64_e = 0x42;
  _QWD::__as((int)__s_00 + 0x30,__s + 0xc);
  return this;
}

// JP: 0x00313cc0  __dt__12EffectSpriteFv  =  EffectSprite::~EffectSprite
int * EffectSprite::~EffectSprite(int *this,short param_2)

{
  if (this != (int *)0x0) {
    this[4] = (int)EffectSprite::__vt;
    this[7] = 0x406a00;
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

// JP: 0x00313db0  getPacket__12EffectSpriteFv  =  EffectSprite::getPacket
void EffectSprite::getPacket(undefined4 this)

{
  EffectSprite::GetPacket(this,VIF1Prim::m_Env & 1);
  return;
}

// JP: 0x00313de0  GetPacket__12EffectSpriteFi  =  EffectSprite::GetPacket
undefined4 EffectSprite::GetPacket(int this,int param_2)

{
  int iVar1;
  float *pfVar2;
  float fVar3;
  uint uVar4;
  
  iVar1 = *(int *)(this + param_2 * 4);
  iVar1->u64_20 = this->u64_78;
  iVar1->u64_30 = this->u64_80;
  pfVar2 = (float *)FVector::vx(this + 0x40);
  fVar3 = *pfVar2;
  if (fVar3 < 2.1474836e+09) {
    uVar4 = (uint)fVar3;
  }
  else {
    uVar4 = (int)(fVar3 - 2.1474836e+09) | 0x80000000;
  }
  iVar1->u32_40 = uVar4;
  pfVar2 = (float *)FVector::vy(this + 0x40);
  fVar3 = *pfVar2;
  if (fVar3 < 2.1474836e+09) {
    uVar4 = (uint)fVar3;
  }
  else {
    uVar4 = (int)(fVar3 - 2.1474836e+09) | 0x80000000;
  }
  iVar1->u32_44 = uVar4;
  pfVar2 = (float *)FVector::vz(this + 0x40);
  fVar3 = *pfVar2;
  if (fVar3 < 2.1474836e+09) {
    uVar4 = (uint)fVar3;
  }
  else {
    uVar4 = (int)(fVar3 - 2.1474836e+09) | 0x80000000;
  }
  iVar1->u32_48 = uVar4;
  fVar3 = this->f32_4c;
  if (fVar3 < 2.1474836e+09) {
    uVar4 = (uint)fVar3;
  }
  else {
    uVar4 = (int)(fVar3 - 2.1474836e+09) | 0x80000000;
  }
  iVar1->u32_4c = uVar4;
  pfVar2 = (float *)FVector::vx(this + 0x20);
  fVar3 = *pfVar2;
  if (2.1474836e+09 <= fVar3) {
    fVar3 = fVar3 - 2.1474836e+09;
  }
  iVar1->i32_50 = ((int)fVar3 + 0x700) * 0x10;
  pfVar2 = (float *)FVector::vy(this + 0x20);
  fVar3 = *pfVar2;
  if (2.1474836e+09 <= fVar3) {
    fVar3 = fVar3 - 2.1474836e+09;
  }
  iVar1->i32_54 = ((int)fVar3 + 0x720) * 0x10;
  pfVar2 = (float *)FVector::vx(this + 0x30);
  fVar3 = *pfVar2;
  if (2.1474836e+09 <= fVar3) {
    fVar3 = fVar3 - 2.1474836e+09;
  }
  iVar1->i32_60 = ((int)fVar3 + 0x700) * 0x10;
  pfVar2 = (float *)FVector::vy(this + 0x30);
  fVar3 = *pfVar2;
  if (2.1474836e+09 <= fVar3) {
    fVar3 = fVar3 - 2.1474836e+09;
  }
  iVar1->i32_64 = ((int)fVar3 + 0x720) * 0x10;
  return *(undefined4 *)(this + param_2 * 4);
}

// JP: 0x0031a970  __ct__10EffectBlurFv  =  EffectBlur::EffectBlur
VIF1Prim * EffectBlur::EffectBlur(VIF1Prim *this)

{
  undefined8 uVar1;
  undefined1 auStack_50 [16];
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [28];
  undefined1 auStack_14 [4];
  VIF1Prim *pVStack_10;
  
  pVStack_10 = this;
  VIF1Prim::VIF1Prim(this);
  DelayDeleteObject::DelayDeleteObject(pVStack_10 + 1);
  pVStack_10->pVptr = EffectBlur::__vt;
  pVStack_10[1].dwEnv = 0x406b40;
  FVector::FVector(&pVStack_10[1].bFlags);
  FVector::FVector(&pVStack_10[2].dwEnv);
  FVector::FVector(&pVStack_10[3].dw_unk4);
  FVector::FVector(pVStack_10 + 4);
  _rgba32::_rgba32(&pVStack_10[4].pVptr);
  FVector::Origin(&pVStack_10[1].bFlags);
  uVar1 = FVector::FVector(0x43ff8000,0x43df8000,0,0x3f800000,auStack_30);
  FVector::__as(&pVStack_10[2].dwEnv,uVar1);
  uVar1 = _rgba32::_rgba32(auStack_14,0x92,0x92,0x92,0x48);
  _rgba32::__as(&pVStack_10[4].pVptr,uVar1);
  uVar1 = FVector::FVector(0x3f800000,0x3f800000,0,0,auStack_40);
  FVector::__as(&pVStack_10[3].dw_unk4,uVar1);
  uVar1 = FVector::FVector(0x43ff8000,0x43df8000,0,0x3f800000,auStack_50);
  FVector::__as(pVStack_10 + 4,uVar1);
  EffectBlur::Create(pVStack_10);
  return pVStack_10;
}

// JP: 0x0031ab90  __dt__10EffectBlurFv  =  EffectBlur::~EffectBlur
int * EffectBlur::~EffectBlur(int *this,short param_2)

{
  if (this != (int *)0x0) {
    this[4] = (int)EffectBlur::__vt;
    this[7] = 0x406b40;
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

// JP: 0x0031ac80  Create__10EffectBlurFv  =  EffectBlur::Create
void EffectBlur::Create(undefined4 *this)

{
  undefined4 *__s;
  void *__s_00;
  undefined1 in_zero_qw [16];
  undefined4 uVar1;
  undefined8 extraout_v0_udw;
  undefined1 auVar2 [16];
  
  uVar1 = __nwa(0xd0);
  *this = uVar1;
  uVar1 = __nwa(0xd0);
  this[1] = uVar1;
  __s = (undefined4 *)*this;
  __s_00 = (void *)this[1];
  memset(__s,0,0xd0);
  memset(__s_00,0,0xd0);
  *__s = 0x6000000c;
  __s[2] = 0x13000000;
  __s[3] = 0x5000000c;
  _QWD::__as(__s_00,__s);
  auVar2._8_8_ = extraout_v0_udw;
  auVar2._0_8_ = 0xb0ab400000008001;
  auVar2 = _pcpyld(in_zero_qw,auVar2);
  __s->i64_4 = auVar2._0_8_;
  __s->u64_6 = 0x513513eeeee;
  _QWD::__as((int)__s_00 + 0x10,__s + 4);
  __s->u64_8 = 0x33001;
  __s->u64_a = 0x47;
  _QWD::__as((int)__s_00 + 0x20,__s + 8);
  __s->u64_c = 1;
  __s->u64_e = 0x14;
  _QWD::__as((int)__s_00 + 0x30,__s + 0xc);
  __s->u64_10 = 5;
  __s->u64_12 = 8;
  _QWD::__as((int)__s_00 + 0x40,__s + 0x10);
  __s->u64_14 = 0x44;
  __s->u64_16 = 0x42;
  _QWD::__as((int)__s_00 + 0x50,__s + 0x14);
  return;
}

// JP: 0x0031ae40  getPacket__10EffectBlurFv  =  EffectBlur::getPacket
/* WARNING: Function: fptodp replaced with injection: fptodp */
/* WARNING: Function: dpmul replaced with injection: dpmul */
/* WARNING: Removing unreachable block (ram,0x0031aea4) */

undefined4 EffectBlur::getPacket(int this)

{
  byte bVar1;
  byte bVar2;
  ushort uVar3;
  int iVar4;
  float *pfVar5;
  undefined4 uVar6;
  ulong uVar7;
  ulong uVar8;
  float fVar9;
  
  iVar4 = *(int *)(this + (VIF1Prim::m_Env & 1) * 4);
  uVar3 = *(ushort *)(CApp::camera + (uint)CApp::camera->u8_394 * 2 + 0x38c);
  bVar1 = CApp::camera->u8_52;
  bVar2 = CApp::camera->u8_53;
  uVar7 = GetBekijo(0x200);
  uVar8 = GetBekijo(0x200);
  iVar4->u64_60 =
       ((ulong)bVar2 & 0x3f) << 0x14 |
       ((ulong)bVar1 & 0x3f) << 0xe | (long)((int)((uint)uVar3 * 0x800) >> 6) |
       (uVar7 & 0xffffffff) << 0x1a | (uVar8 & 0xffffffff) << 0x1e;
  iVar4->u64_68 = 6;
  pfVar5 = (float *)FVector::vx(this + 0x40);
  uVar6 = dptoul((double)*pfVar5 * 16.0);
  iVar4->u32_70 = uVar6;
  pfVar5 = (float *)FVector::vy(this + 0x40);
  uVar6 = dptoul((double)*pfVar5 * 16.0);
  iVar4->u32_74 = uVar6;
  iVar4->u32_80 = (uint)this->u8_60;
  iVar4->u32_84 = (uint)this->u8_61;
  iVar4->u32_88 = (uint)this->u8_62;
  iVar4->u32_8c = (uint)this->u8_63;
  pfVar5 = (float *)FVector::vx(this + 0x20);
  fVar9 = *pfVar5;
  if (2.1474836e+09 <= fVar9) {
    fVar9 = fVar9 - 2.1474836e+09;
  }
  iVar4->i32_90 = ((int)fVar9 + 0x700) * 0x10;
  pfVar5 = (float *)FVector::vy(this + 0x20);
  fVar9 = *pfVar5;
  if (2.1474836e+09 <= fVar9) {
    fVar9 = fVar9 - 2.1474836e+09;
  }
  iVar4->i32_94 = ((int)fVar9 + 0x720) * 0x10;
  pfVar5 = (float *)FVector::vx(this + 0x50);
  uVar6 = dptoul((double)*pfVar5 * 16.0);
  iVar4->u32_a0 = uVar6;
  pfVar5 = (float *)FVector::vy(this + 0x50);
  uVar6 = dptoul((double)*pfVar5 * 16.0);
  iVar4->u32_a4 = uVar6;
  iVar4->u32_b0 = (uint)this->u8_60;
  iVar4->u32_b4 = (uint)this->u8_61;
  iVar4->u32_b8 = (uint)this->u8_62;
  iVar4->u32_bc = (uint)this->u8_63;
  pfVar5 = (float *)FVector::vx(this + 0x30);
  fVar9 = *pfVar5;
  if (2.1474836e+09 <= fVar9) {
    fVar9 = fVar9 - 2.1474836e+09;
  }
  iVar4->i32_c0 = ((int)fVar9 + 0x700) * 0x10;
  pfVar5 = (float *)FVector::vy(this + 0x30);
  fVar9 = *pfVar5;
  if (2.1474836e+09 <= fVar9) {
    fVar9 = fVar9 - 2.1474836e+09;
  }
  iVar4->i32_c4 = ((int)fVar9 + 0x720) * 0x10;
  return *(undefined4 *)(this + (VIF1Prim::m_Env & 1) * 4);
}

// JP: 0x0031b260  SetAlpha__10EffectBlurFi  =  EffectBlur::SetAlpha
void EffectBlur::SetAlpha(int this,int param_2)

{
  char cVar1;
  undefined1 uVar2;
  float fVar3;
  
  cVar1 = (char)(int)((float)param_2 * 0.25);
  if (param_2 < 0xc) {
    cVar1 = -0x80 - cVar1;
    this->i8_62 = cVar1;
    this->i8_61 = cVar1;
    this->i8_60 = cVar1;
    fVar3 = 72.0 - 72.0 / (float)param_2;
    if (fVar3 < 2.1474836e+09) {
      uVar2 = (undefined1)(int)fVar3;
    }
    else {
      uVar2 = (undefined1)(int)(fVar3 - 2.1474836e+09);
    }
    this->u8_63 = uVar2;
  }
  else {
    cVar1 = cVar1 + -0x80;
    this->i8_62 = cVar1;
    this->i8_61 = cVar1;
    this->i8_60 = cVar1;
  }
  return;
}
