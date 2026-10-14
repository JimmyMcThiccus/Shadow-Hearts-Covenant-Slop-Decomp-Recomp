// decomp/D/EffectLight.c — cleaned Ghidra output (SLPM_602.19, Metrowerks MIPS), Shadow Hearts: Covenant JP demo.
// Field accesses are shown as this->T_off (T = u8/u16/u32/f32/i32/p, off = hex offset);
// JRing fields are named from the recovered struct. See notes/D/*.md for layouts.
// CAVEAT: when the base pointer is a float*/int*/short*, the number in `T_off` is an ELEMENT offset (byte offset = off*sizeof(elem)).
// `this` is the C++ this pointer (param_1); the Metrowerks ABI passes it in a0.

// JP: 0x003194f0  __ct__17EffectLightMotionFv  =  EffectLightMotion::EffectLightMotion
undefined4 * EffectLightMotion::EffectLightMotion(undefined4 *this)

{
  this[3] = EffectLightMotion::__vt;
  *this = 0;
  this[1] = 0;
  this[2] = 0;
  return this;
}

// JP: 0x00319540  __dt__17EffectLightMotionFv  =  EffectLightMotion::~EffectLightMotion
int EffectLightMotion::~EffectLightMotion(int this,short param_2)

{
  if ((this != 0) && (*(undefined1 **)(this + 0xc) = EffectLightMotion::__vt, 0 < param_2))
  {
    __dl(this);
  }
  return this;
}

// JP: 0x003195b0  Create__17EffectLightMotionFPc  =  EffectLightMotion::Create
void EffectLightMotion::Create(int *this,int param_2)

{
  *this = param_2;
  this[1] = *this + 0x10;
  return;
}

// JP: 0x003195f0  AddTime__17EffectLightMotionFf  =  EffectLightMotion::AddTime
void EffectLightMotion::AddTime(float this,int param_2)

{
  param_2->f32_8 = param_2->f32_8 + this;
  return;
}

// JP: 0x00319620  GetData__17EffectLightMotionFP17tagEFLTMotionData  =  EffectLightMotion::GetData
undefined4 EffectLightMotion::GetData(int *this,int param_2)

{
  int iVar1;
  undefined1 auStack_60 [16];
  undefined1 auStack_50 [16];
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [16];
  int *piStack_20;
  int iStack_10;
  
  iVar1 = 0;
  while( true ) {
    piStack_20 = this;
    iStack_10 = param_2;
    if ((int)(*(ushort *)(*this + 4) - 1) <= iVar1) {
      tagEFLTMotionData::__as
                (param_2,this[1] + (*(ushort *)(*this + 4) - 1) * 0x40);
      return 1;
    }
    if ((float)this[2] == *(float *)(this[1] + iVar1 * 0x40 + 0x30)) break;
    if ((*(float *)(this[1] + iVar1 * 0x40 + 0x30) < (float)this[2]) &&
       ((float)this[2] < *(float *)(this[1] + (iVar1 + 1) * 0x40 + 0x30))) {
      tagEFLTMotionData::__as(param_2,this[1] + iVar1 * 0x40);
      iStack_10->f32_30 =
           ((float)piStack_20[2] - *(float *)(piStack_20[1] + iVar1 * 0x40 + 0x30)) /
           (*(float *)(piStack_20[1] + (iVar1 + 1) * 0x40 + 0x30) -
           *(float *)(piStack_20[1] + iVar1 * 0x40 + 0x30));
      FVector::__mi
                (auStack_40,piStack_20[1] + (iVar1 + 1) * 0x40,piStack_20[1] + iVar1 * 0x40);
      FVector::__ml(iStack_10->u32_30,auStack_30,auStack_40);
      FVector::__apl(iStack_10,auStack_30);
      FVector::Origin(iStack_10 + 0x10);
      FVector::__mi
                (auStack_60,piStack_20[1] + (iVar1 + 1) * 0x40 + 0x20,
                 piStack_20[1] + iVar1 * 0x40 + 0x20);
      FVector::__ml(iStack_10->u32_30,auStack_50,auStack_60);
      FVector::__apl(iStack_10 + 0x20,auStack_50);
      return 0;
    }
    iVar1 = iVar1 + 1;
  }
  tagEFLTMotionData::__as(param_2,this[1] + iVar1 * 0x40);
  return 0;
}

// JP: 0x00319950  __ct__11EffectLightFv  =  EffectLight::EffectLight
undefined4 * EffectLight::EffectLight(undefined4 *this)

{
  this[8] = EffectLight::__vt;
  FVector::FVector(this + 4);
  *this = 0;
  this[1] = 0;
  this[3] = 0;
  this[2] = 0xffffffff;
  FVector::Origin(this + 4);
  return this;
}

// JP: 0x003199d0  __dt__11EffectLightFv  =  EffectLight::~EffectLight
int * EffectLight::~EffectLight(int *this,short param_2)

{
  int iVar1;
  
  if (this != (int *)0x0) {
    this[8] = (int)EffectLight::__vt;
    if (*this != 0) {
      iVar1 = *this;
      if (iVar1 != 0) {
        (**(code **)(iVar1->i32_c + 0x10))(iVar1,1);
      }
      *this = 0;
    }
    if (this[2] != -1) {
      LightControl::release(this[2]);
    }
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x00319aa0  Create__11EffectLightFPc  =  EffectLight::Create
void EffectLight::Create(int *this,int param_2)

{
  int iVar1;
  long lVar2;
  
  this[1] = param_2;
  lVar2 = __nw(0x10);
  iVar1 = 0;
  if (lVar2 != 0) {
    iVar1 = EffectLightMotion::EffectLightMotion(lVar2);
  }
  *this = iVar1;
  (**(code **)(*(int *)(*this + 0xc) + 0xc))
            (*this,this[1] + (uint)*(ushort *)(this[1] + 0xc) * 0x10);
  return;
}

// JP: 0x00319b40  LightOn__11EffectLightFb  =  EffectLight::LightOn
void EffectLight::LightOn(undefined4 *this,char param_2)

{
  undefined4 uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  byte bVar5;
  undefined1 auStack_100 [16];
  undefined1 auStack_f0 [16];
  undefined1 auStack_e0 [16];
  undefined1 auStack_d0 [16];
  undefined1 auStack_c0 [16];
  undefined1 auStack_b0 [16];
  undefined1 auStack_a0 [16];
  undefined1 auStack_90 [16];
  undefined1 auStack_80 [16];
  undefined1 auStack_70 [16];
  undefined1 auStack_60 [32];
  undefined1 auStack_40 [32];
  undefined4 *puStack_20;
  char cStack_10;
  
  puStack_20 = this;
  cStack_10 = param_2;
  tagEFLTMotionData::tagEFLTMotionData(auStack_60);
  EffectLightMotion::GetData(*puStack_20,auStack_60);
  if (cStack_10 == '\0') {
    LightControl::release(puStack_20[2]);
    puStack_20[2] = 0xffffffff;
  }
  else {
    FVector::FVector(auStack_70);
    if (puStack_20[3] == 0) {
      FVector::Origin(auStack_70);
    }
    else {
      Frame::getWorldPos(auStack_80,puStack_20[3],VIF1Prim::m_Env & 1);
      FVector::__as(auStack_70,auStack_80);
    }
    FVector::__apl(auStack_70,puStack_20 + 4);
    bVar5 = *(byte *)(puStack_20[1] + 8) & 7;
    if (bVar5 == 3) {
      uVar2 = FVector::FVector(auStack_100,auStack_60);
      uVar1 = LightControl::CreateAmbient(uVar2);
      puStack_20[2] = uVar1;
    }
    else if (bVar5 == 2) {
      uVar2 = FVector::FVector(auStack_d0,auStack_70);
      uVar3 = FVector::FVector(auStack_e0,auStack_40);
      uVar4 = FVector::FVector(auStack_f0,auStack_60);
      uVar1 = LightControl::CreateSpot(uVar2,uVar3,uVar4);
      puStack_20[2] = uVar1;
    }
    else if (bVar5 == 1) {
      uVar2 = FVector::FVector(auStack_b0,auStack_40);
      uVar3 = FVector::FVector(auStack_c0,auStack_60);
      uVar1 = LightControl::CreateDirectional(uVar2,uVar3);
      puStack_20[2] = uVar1;
    }
    else if ((*(byte *)(puStack_20[1] + 8) & 7) == 0) {
      uVar2 = FVector::FVector(auStack_90,auStack_70);
      uVar3 = FVector::FVector(auStack_a0,auStack_60);
      uVar1 = LightControl::CreatePoint(uVar2,uVar3);
      puStack_20[2] = uVar1;
    }
  }
  return;
}

// JP: 0x00319da0  AddTime__11EffectLightFf  =  EffectLight::AddTime
void EffectLight::AddTime(undefined4 this,int *param_2)

{
  if (param_2[2] != -1) {
    (**(code **)(*(int *)(*param_2 + 0xc) + 8))(this);
  }
  return;
}

// JP: 0x00319df0  GetData__11EffectLightFP17tagEFLTMotionData  =  EffectLight::GetData
undefined1 EffectLight::GetData(undefined4 *this,int param_2)

{
  undefined1 uVar1;
  undefined8 uVar2;
  undefined1 auStack_90 [16];
  undefined1 auStack_80 [16];
  undefined1 auStack_70 [64];
  undefined1 auStack_30 [16];
  undefined4 *puStack_20;
  int iStack_10;
  
  puStack_20 = this;
  iStack_10 = param_2;
  uVar1 = EffectLightMotion::GetData(*this,param_2);
  FVector::FVector(auStack_30,puStack_20 + 4);
  if (puStack_20[3] != 0) {
    Matrix::Matrix(auStack_70,*(int *)(puStack_20[3] + 0x90) + 0x160);
    uVar2 = Matrix::GetPos(auStack_70);
    FVector::Origin(uVar2);
    Matrix::ApplyMatrix(auStack_80,auStack_70,auStack_30);
    FVector::__as(auStack_30,auStack_80);
    Frame::getWorldPos(auStack_90,puStack_20[3],VIF1Prim::m_Env & 1);
    FVector::__apl(auStack_30,auStack_90);
  }
  FVector::__apl(iStack_10 + 0x10,auStack_30);
  return uVar1;
}

// JP: 0x00319f00  ChangeLight__11EffectLightFP17tagEFLTMotionData  =  EffectLight::ChangeLight
void EffectLight::ChangeLight(int this,int param_2)

{
  byte bVar1;
  undefined8 uVar2;
  byte bVar3;
  undefined1 auStack_70 [16];
  undefined1 auStack_60 [16];
  undefined1 auStack_50 [16];
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [16];
  int iStack_20;
  int iStack_10;
  
  bVar1 = *(byte *)(this->i32_4 + 8);
  bVar3 = bVar1 & 7;
  iStack_20 = this;
  iStack_10 = param_2;
  if (bVar3 != 3) {
    if (bVar3 == 2) {
      uVar2 = FVector::FVector(auStack_50,param_2 + 0x10);
      LightControl::changePos(iStack_20->u32_8,uVar2);
      uVar2 = FVector::FVector(auStack_60,iStack_10 + 0x20);
      LightControl::changeDir(iStack_20->u32_8,uVar2);
    }
    else if (bVar3 == 1) {
      uVar2 = FVector::FVector(auStack_40,param_2 + 0x20);
      LightControl::changeDir(iStack_20->u32_8,uVar2);
    }
    else if ((bVar1 & 7) == 0) {
      uVar2 = FVector::FVector(auStack_30,param_2 + 0x10);
      LightControl::changePos(iStack_20->u32_8,uVar2);
    }
  }
  uVar2 = FVector::FVector(auStack_70,iStack_10);
  LightControl::changeCol(iStack_20->u32_8,uVar2);
  return;
}
