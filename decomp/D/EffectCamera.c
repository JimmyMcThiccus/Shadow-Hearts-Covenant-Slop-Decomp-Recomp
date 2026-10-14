// decomp/D/EffectCamera.c — cleaned Ghidra output (SLPM_602.19, Metrowerks MIPS), Shadow Hearts: Covenant JP demo.
// Field accesses are shown as this->T_off (T = u8/u16/u32/f32/i32/p, off = hex offset);
// JRing fields are named from the recovered struct. See notes/D/*.md for layouts.
// CAVEAT: when the base pointer is a float*/int*/short*, the number in `T_off` is an ELEMENT offset (byte offset = off*sizeof(elem)).
// `this` is the C++ this pointer (param_1); the Metrowerks ABI passes it in a0.

// JP: 0x00307ba0  __ct__12EffectCameraFv  =  EffectCamera::EffectCamera
undefined4 * EffectCamera::EffectCamera(undefined4 *this)

{
  undefined8 uVar1;
  undefined1 auStack_20 [16];
  undefined4 *puStack_10;
  
  this[0x3d] = EffectCamera::__vt;
  puStack_10 = this;
  FVector::FVector(this + 4);
  Matrix::Matrix(puStack_10 + 8);
  FVector::FVector(puStack_10 + 0x18);
  FVector::FVector(puStack_10 + 0x1c);
  FVector::FVector(puStack_10 + 0x20);
  FVector::FVector(puStack_10 + 0x24);
  FVector::FVector(puStack_10 + 0x28);
  FVector::FVector(puStack_10 + 0x2c);
  FVector::FVector(puStack_10 + 0x30);
  FVector::FVector(puStack_10 + 0x34);
  *puStack_10 = 0;
  puStack_10[1] = 0;
  puStack_10[2] = 0;
  uVar1 = FVector::FVector(0x3fc90fd8,0x3fc90fd8,0x3fc90fd8,0,auStack_20);
  FVector::__as(puStack_10 + 0x2c,uVar1);
  puStack_10[0x38] = 0;
  puStack_10[0x39] = 0x3f800000;
  FVector::Origin(puStack_10 + 0x34);
  FVector::Origin(puStack_10 + 0x24);
  FVector::Origin(puStack_10 + 0x30);
  puStack_10[0x3c] = 0;
  tagEcFlag::Init(puStack_10 + 3);
  return puStack_10;
}

// JP: 0x00307e50  __dt__12EffectCameraFv  =  EffectCamera::~EffectCamera
int * EffectCamera::~EffectCamera(int *this,short param_2)

{
  int iVar1;
  
  if (this != (int *)0x0) {
    this[0x3d] = (int)EffectCamera::__vt;
    if (*this != 0) {
      iVar1 = *this;
      if (iVar1 != 0) {
        (**(code **)(iVar1->i32_c + 0x10))(iVar1,1);
      }
      *this = 0;
    }
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x00307f00  Create__12EffectCameraFPc  =  EffectCamera::Create
void EffectCamera::Create(int *this,int param_2)

{
  int iVar1;
  long lVar2;
  
  this[1] = param_2;
  lVar2 = __nw(0x10);
  iVar1 = 0;
  if (lVar2 != 0) {
    iVar1 = EffectCameraMotion::EffectCameraMotion(lVar2);
  }
  *this = iVar1;
  (**(code **)(*(int *)(*this + 0xc) + 0xc))
            (*this,this[1] + (uint)*(ushort *)(this[1] + 8) * 0x10);
  return;
}

// JP: 0x00307fa0  CreateVector__12EffectCameraFP7FVectorP7FVectorf  =  EffectCamera::CreateVector
void EffectCamera::CreateVector
               (undefined4 this,int param_2,undefined4 param_3,undefined4 param_4)

{
  FVector::__as(param_2 + 0x60,param_3);
  FVector::__as(param_2 + 0x70,param_4);
  param_2->u32_e8 = this;
  param_2->u32_ec = 0;
  param_2->u8_c = param_2->u8_c & 0xf7 | 8;
  return;
}

// JP: 0x00308030  AddTime__12EffectCameraFf  =  EffectCamera::AddTime
void EffectCamera::AddTime(undefined4 this,int *param_2)

{
  (**(code **)(*(int *)(*param_2 + 0xc) + 8))(this);
  return;
}

// JP: 0x00308070  GetData__12EffectCameraFP17tagEFCMMotionData  =  EffectCamera::GetData
void EffectCamera::GetData(undefined4 *this,undefined4 param_2)

{
  EffectCameraMotion::GetData(*this,param_2);
  return;
}

// JP: 0x003080b0  LookAt__12EffectCameraFP17tagEFCMMotionData  =  EffectCamera::LookAt
/* WARNING: Removing unreachable block (ram,0x00308348) */

void EffectCamera::LookAt(int this,int param_2)

{
  undefined8 uVar1;
  float fVar2;
  undefined1 auStack_160 [64];
  undefined1 auStack_120 [16];
  undefined1 auStack_110 [16];
  undefined1 auStack_100 [16];
  undefined1 auStack_f0 [16];
  undefined1 auStack_e0 [64];
  undefined1 auStack_a0 [16];
  undefined1 auStack_90 [16];
  undefined1 auStack_80 [16];
  undefined1 auStack_70 [16];
  undefined1 auStack_60 [16];
  undefined1 auStack_50 [16];
  undefined1 auStack_40 [28];
  undefined4 uStack_24;
  int iStack_20;
  int iStack_10;
  
  iStack_20 = this;
  iStack_10 = param_2;
  FVector::FVector(0,0,0,0x3f800000,auStack_40);
  FVector::FVector(auStack_50);
  EffectCamera::GetInter(auStack_60,iStack_20,iStack_10);
  EffectCamera::GetPos(auStack_70,iStack_20,iStack_10 + 0x10);
  EffectCamera::GetVibPower(auStack_80,iStack_20,auStack_70);
  FVector::__apl(auStack_70,auStack_80);
  FVector::__apl(auStack_60,auStack_80);
  FVector::__mi(auStack_f0,auStack_60,auStack_70);
  FVector::__as(auStack_50,auStack_f0);
  uStack_24 = FVector::Length(auStack_50);
  FVector::Normalize(auStack_50);
  uVar1 = FVector::FVector(0,0xbf800000,0,0x3f800000,auStack_100);
  FVector::OuterProduct(auStack_90,auStack_50,uVar1);
  FVector::Normalize(auStack_90);
  fVar2 = (float)FVector::Length(auStack_90);
  if (fVar2 <= 0.0) {
    uVar1 = FVector::FVector(0x3f800000,0,0,0x3f800000,auStack_110);
    FVector::__as(auStack_90,uVar1);
    uStack_24 = 0x42200000;
  }
  FVector::OuterProduct(auStack_a0,auStack_50,auStack_90);
  FVector::Normalize(auStack_a0);
  Matrix::UnitMatrix(&CApp::camera->frame);
  Matrix::SetAt(&CApp::camera->frame,auStack_50);
  Matrix::SetUp(&CApp::camera->frame,auStack_a0);
  Matrix::SetRight(&CApp::camera->frame,auStack_90);
  FVector::__pl(auStack_120,auStack_70,auStack_40);
  Matrix::SetPos(&CApp::camera->frame,auStack_120);
  Matrix::Matrix(auStack_e0);
  Matrix::RotZMatrix(iStack_10->u32_2c,auStack_e0);
  Matrix::MulMatrix(auStack_160,&CApp::camera->frame,auStack_e0);
  Matrix::__as(&CApp::camera->frame,auStack_160);
  GsxCamera::ApplyFrame(CApp::camera);
  GsxCamera::SetScreenZ((float)iStack_10->u16_24,CApp::camera);
  if (-1 < (long)((ulong)iStack_20->u8_c << 0x39)) {
    CameraCutChange();
    iStack_20->u8_c = iStack_20->u8_c & 0xbf | 0x40;
  }
  return;
}

// JP: 0x003085c0  GetInter__12EffectCameraFR7FVector  =  EffectCamera::GetInter
void EffectCamera::GetInter(undefined4 this,int param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  byte bVar4;
  undefined1 auStack_150 [16];
  undefined1 auStack_140 [16];
  undefined1 auStack_130 [16];
  undefined1 auStack_120 [16];
  undefined1 auStack_110 [16];
  undefined1 auStack_100 [16];
  undefined1 auStack_f0 [16];
  undefined1 auStack_e0 [16];
  undefined1 auStack_d0 [16];
  undefined1 auStack_c0 [16];
  undefined1 auStack_b0 [16];
  undefined1 auStack_a0 [16];
  undefined1 auStack_90 [16];
  undefined1 auStack_80 [64];
  undefined1 auStack_40 [16];
  undefined4 uStack_30;
  int iStack_20;
  undefined4 uStack_10;
  
  uStack_30 = this;
  iStack_20 = param_2;
  uStack_10 = param_3;
  if ((long)((ulong)param_2->u8_c << 0x3c) < 0) {
    EffectCamera::GetVecInter(this,param_2,param_3);
  }
  else if ((long)((ulong)param_2->u8_c << 0x3a) < 0) {
    EffectCamera::GetBoxInter(this,param_2,param_3);
  }
  else {
    FVector::FVector(auStack_40,param_3);
    bVar4 = iStack_20->u8_c & 3;
    if (bVar4 == 2) {
      if ((-1 < (long)((ulong)iStack_20->u8_c << 0x3d)) && (iStack_20->i32_8 != 0)
         ) {
        Matrix::__as(iStack_20 + 0x20,*(int *)(iStack_20->i32_8 + 0x90) + 0x160);
        uVar2 = Matrix::GetPos(iStack_20 + 0x20);
        FVector::Origin(uVar2);
        Frame::getWorldPos(auStack_110,iStack_20->u32_8,VIF1Prim::m_Env & 1);
        FVector::__as(iStack_20 + 0x10,auStack_110);
        puVar1 = (undefined4 *)FVector::vz(iStack_20 + 0x10);
        *puVar1 = 0;
        puVar1 = (undefined4 *)FVector::vx(iStack_20 + 0x10);
        *puVar1 = 0;
        iStack_20->u8_c = iStack_20->u8_c & 0xfb | 4;
      }
      FVector::FVector(auStack_90);
      if (iStack_20->i32_8 != 0) {
        Frame::getWorldPos(auStack_120,iStack_20->u32_8,VIF1Prim::m_Env & 1);
        FVector::__as(auStack_90,auStack_120);
        puVar1 = (undefined4 *)FVector::vy(auStack_90);
        *puVar1 = 0;
      }
      Matrix::ApplyMatrix(auStack_150,iStack_20 + 0x20,uStack_10);
      FVector::__pl(auStack_140,auStack_150,iStack_20 + 0x10);
      FVector::__pl(auStack_130,auStack_140,auStack_90);
      FVector::__as(auStack_40,auStack_130);
    }
    else if (bVar4 == 1) {
      if (iStack_20->i32_8 != 0) {
        Matrix::Matrix(auStack_80,*(int *)(iStack_20->i32_8 + 0x90) + 0x160);
        uVar2 = Matrix::GetPos(auStack_80);
        uVar3 = FVector::FVector(0,0,0,0x3f800000,auStack_d0);
        FVector::__as(uVar2,uVar3);
        Matrix::ApplyMatrix(auStack_f0,auStack_80,uStack_10);
        Frame::getWorldPos(auStack_100,iStack_20->u32_8,VIF1Prim::m_Env & 1);
        FVector::__pl(auStack_e0,auStack_f0,auStack_100);
        FVector::__as(auStack_40,auStack_e0);
      }
    }
    else if ((iStack_20->u8_c & 3) == 0) {
      if ((-1 < (long)((ulong)iStack_20->u8_c << 0x3d)) && (iStack_20->i32_8 != 0)
         ) {
        Matrix::__as(iStack_20 + 0x20,*(int *)(iStack_20->i32_8 + 0x90) + 0x160);
        uVar2 = Matrix::GetPos(iStack_20 + 0x20);
        FVector::Origin(uVar2);
        Frame::getWorldPos(auStack_a0,iStack_20->u32_8,VIF1Prim::m_Env & 1);
        FVector::__as(iStack_20 + 0x10,auStack_a0);
        iStack_20->u8_c = iStack_20->u8_c & 0xfb | 4;
      }
      Matrix::ApplyMatrix(auStack_c0,iStack_20 + 0x20,uStack_10);
      FVector::__pl(auStack_b0,auStack_c0,iStack_20 + 0x10);
      FVector::__as(auStack_40,auStack_b0);
    }
    FVector::FVector(uStack_30,auStack_40);
  }
  return;
}

// JP: 0x00308a30  GetPos__12EffectCameraFR7FVector  =  EffectCamera::GetPos
void EffectCamera::GetPos(undefined4 this,int param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  byte bVar4;
  undefined1 auStack_150 [16];
  undefined1 auStack_140 [16];
  undefined1 auStack_130 [16];
  undefined1 auStack_120 [16];
  undefined1 auStack_110 [16];
  undefined1 auStack_100 [16];
  undefined1 auStack_f0 [16];
  undefined1 auStack_e0 [16];
  undefined1 auStack_d0 [16];
  undefined1 auStack_c0 [16];
  undefined1 auStack_b0 [16];
  undefined1 auStack_a0 [16];
  undefined1 auStack_90 [16];
  undefined1 auStack_80 [64];
  undefined1 auStack_40 [16];
  undefined4 uStack_30;
  int iStack_20;
  undefined4 uStack_10;
  
  uStack_30 = this;
  iStack_20 = param_2;
  uStack_10 = param_3;
  if ((long)((ulong)param_2->u8_c << 0x3c) < 0) {
    EffectCamera::GetVecPos(this,param_2,param_3);
  }
  else if ((long)((ulong)param_2->u8_c << 0x3a) < 0) {
    EffectCamera::GetBoxPos(this,param_2,param_3);
  }
  else {
    FVector::FVector(auStack_40,param_3);
    bVar4 = iStack_20->u8_c & 3;
    if (bVar4 == 2) {
      if ((-1 < (long)((ulong)iStack_20->u8_c << 0x3d)) && (iStack_20->i32_8 != 0)
         ) {
        Matrix::__as(iStack_20 + 0x20,*(int *)(iStack_20->i32_8 + 0x90) + 0x160);
        uVar2 = Matrix::GetPos(iStack_20 + 0x20);
        FVector::Origin(uVar2);
        Frame::getWorldPos(auStack_110,iStack_20->u32_8,VIF1Prim::m_Env & 1);
        FVector::__as(iStack_20 + 0x10,auStack_110);
        puVar1 = (undefined4 *)FVector::vz(iStack_20 + 0x10);
        *puVar1 = 0;
        puVar1 = (undefined4 *)FVector::vx(iStack_20 + 0x10);
        *puVar1 = 0;
        iStack_20->u8_c = iStack_20->u8_c & 0xfb | 4;
      }
      FVector::FVector(auStack_90);
      if (iStack_20->i32_8 != 0) {
        Frame::getWorldPos(auStack_120,iStack_20->u32_8,VIF1Prim::m_Env & 1);
        FVector::__as(auStack_90,auStack_120);
        puVar1 = (undefined4 *)FVector::vy(auStack_90);
        *puVar1 = 0;
      }
      Matrix::ApplyMatrix(auStack_150,iStack_20 + 0x20,uStack_10);
      FVector::__pl(auStack_140,auStack_150,iStack_20 + 0x10);
      FVector::__pl(auStack_130,auStack_140,auStack_90);
      FVector::__as(auStack_40,auStack_130);
    }
    else if (bVar4 == 1) {
      if (iStack_20->i32_8 != 0) {
        Matrix::Matrix(auStack_80,*(int *)(iStack_20->i32_8 + 0x90) + 0x160);
        uVar2 = Matrix::GetPos(auStack_80);
        uVar3 = FVector::FVector(0,0,0,0x3f800000,auStack_d0);
        FVector::__as(uVar2,uVar3);
        Matrix::ApplyMatrix(auStack_f0,auStack_80,uStack_10);
        Frame::getWorldPos(auStack_100,iStack_20->u32_8,VIF1Prim::m_Env & 1);
        FVector::__pl(auStack_e0,auStack_f0,auStack_100);
        FVector::__as(auStack_40,auStack_e0);
      }
    }
    else if ((iStack_20->u8_c & 3) == 0) {
      if ((-1 < (long)((ulong)iStack_20->u8_c << 0x3d)) && (iStack_20->i32_8 != 0)
         ) {
        Matrix::__as(iStack_20 + 0x20,*(int *)(iStack_20->i32_8 + 0x90) + 0x160);
        uVar2 = Matrix::GetPos(iStack_20 + 0x20);
        FVector::Origin(uVar2);
        Frame::getWorldPos(auStack_a0,iStack_20->u32_8,VIF1Prim::m_Env & 1);
        FVector::__as(iStack_20 + 0x10,auStack_a0);
        iStack_20->u8_c = iStack_20->u8_c & 0xfb | 4;
      }
      Matrix::ApplyMatrix(auStack_c0,iStack_20 + 0x20,uStack_10);
      FVector::__pl(auStack_b0,auStack_c0,iStack_20 + 0x10);
      FVector::__as(auStack_40,auStack_b0);
    }
    FVector::FVector(uStack_30,auStack_40);
  }
  return;
}

// JP: 0x00308ea0  GetBoxInter__12EffectCameraFR7FVector  =  EffectCamera::GetBoxInter
void EffectCamera::GetBoxInter(undefined4 this,int param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 *puVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  byte bVar5;
  undefined1 auStack_1d0 [16];
  undefined1 auStack_1c0 [16];
  undefined1 auStack_1b0 [16];
  undefined1 auStack_1a0 [16];
  undefined1 auStack_190 [16];
  undefined1 auStack_180 [16];
  undefined1 auStack_170 [16];
  undefined1 auStack_160 [16];
  undefined1 auStack_150 [16];
  undefined1 auStack_140 [16];
  undefined1 auStack_130 [16];
  undefined1 auStack_120 [16];
  undefined1 auStack_110 [16];
  undefined1 auStack_100 [16];
  undefined1 auStack_f0 [16];
  undefined1 auStack_e0 [16];
  undefined1 auStack_d0 [16];
  undefined1 auStack_c0 [16];
  undefined1 auStack_b0 [16];
  undefined1 auStack_a0 [16];
  undefined1 auStack_90 [64];
  undefined1 auStack_50 [16];
  undefined1 auStack_40 [16];
  undefined4 uStack_30;
  int iStack_20;
  undefined4 uStack_10;
  
  uStack_30 = this;
  iStack_20 = param_2;
  uStack_10 = param_3;
  FVector::FVector(auStack_40);
  FVector::FVector(auStack_50);
  iVar1 = iStack_20->i32_f0;
  FVector::__as(auStack_50,iVar1->i32_8 + 0x2a0);
  bVar5 = iStack_20->u8_c & 3;
  if (bVar5 == 2) {
    if (-1 < (long)((ulong)iStack_20->u8_c << 0x3d)) {
      Matrix::__as(iStack_20 + 0x20,*(int *)(iVar1->i32_4 + 0x30) + 0x160);
      uVar3 = Matrix::GetPos(iStack_20 + 0x20);
      FVector::Origin(uVar3);
      Frame::getWorldPos
                (auStack_170,*(undefined4 *)(iVar1->i32_4 + 0x30),VIF1Prim::m_Env & 1);
      FVector::__as(iStack_20 + 0x10,auStack_170);
      puVar2 = (undefined4 *)FVector::vz(iStack_20 + 0x10);
      *puVar2 = 0;
      puVar2 = (undefined4 *)FVector::vx(iStack_20 + 0x10);
      *puVar2 = 0;
      iStack_20->u8_c = iStack_20->u8_c & 0xfb | 4;
    }
    Frame::getWorldPos
              (auStack_a0,*(undefined4 *)(iVar1->i32_4 + 0x30),VIF1Prim::m_Env & 1);
    puVar2 = (undefined4 *)FVector::vy(auStack_a0);
    *puVar2 = 0;
    Matrix::ApplyMatrix(auStack_1c0,iStack_20 + 0x20,uStack_10);
    Matrix::ApplyMatrix(auStack_1d0,iStack_20 + 0x20,iStack_20 + 0xc0);
    FVector::__pl(auStack_1b0,auStack_1c0,auStack_1d0);
    FVector::__pl(auStack_1a0,auStack_1b0,iStack_20 + 0x10);
    FVector::__pl(auStack_190,auStack_1a0,auStack_50);
    FVector::__pl(auStack_180,auStack_190,auStack_a0);
    FVector::__as(auStack_40,auStack_180);
  }
  else if (bVar5 == 1) {
    Matrix::Matrix(auStack_90,*(int *)(iVar1->i32_4 + 0x30) + 0x160);
    uVar3 = Matrix::GetPos(auStack_90);
    uVar4 = FVector::FVector(0,0,0,0x3f800000,auStack_110);
    FVector::__as(uVar3,uVar4);
    Frame::getWorldPos
              (auStack_120,*(undefined4 *)(iVar1->i32_4 + 0x30),VIF1Prim::m_Env & 1);
    FVector::__apl(auStack_50,auStack_120);
    Matrix::ApplyMatrix(auStack_150,auStack_90,uStack_10);
    Matrix::ApplyMatrix(auStack_160,auStack_90,iStack_20 + 0xc0);
    FVector::__pl(auStack_140,auStack_150,auStack_160);
    FVector::__pl(auStack_130,auStack_140,auStack_50);
    FVector::__as(auStack_40,auStack_130);
  }
  else if ((iStack_20->u8_c & 3) == 0) {
    if (-1 < (long)((ulong)iStack_20->u8_c << 0x3d)) {
      Matrix::__as(iStack_20 + 0x20,*(int *)(iVar1->i32_4 + 0x30) + 0x160);
      uVar3 = Matrix::GetPos(iStack_20 + 0x20);
      FVector::Origin(uVar3);
      Frame::getWorldPos
                (auStack_c0,*(undefined4 *)(iVar1->i32_4 + 0x30),VIF1Prim::m_Env & 1);
      FVector::__pl(auStack_b0,auStack_c0,auStack_50);
      FVector::__as(iStack_20 + 0x10,auStack_b0);
      iStack_20->u8_c = iStack_20->u8_c & 0xfb | 4;
    }
    Matrix::ApplyMatrix(auStack_f0,iStack_20 + 0x20,uStack_10);
    Matrix::ApplyMatrix(auStack_100,iStack_20 + 0x20,iStack_20 + 0xc0);
    FVector::__pl(auStack_e0,auStack_f0,auStack_100);
    FVector::__pl(auStack_d0,auStack_e0,iStack_20 + 0x10);
    FVector::__as(auStack_40,auStack_d0);
  }
  FVector::FVector(uStack_30,auStack_40);
  return;
}

// JP: 0x00309320  GetBoxPos__12EffectCameraFR7FVector  =  EffectCamera::GetBoxPos
void EffectCamera::GetBoxPos(undefined4 this,int param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 *puVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  byte bVar5;
  undefined1 auStack_1d0 [16];
  undefined1 auStack_1c0 [16];
  undefined1 auStack_1b0 [16];
  undefined1 auStack_1a0 [16];
  undefined1 auStack_190 [16];
  undefined1 auStack_180 [16];
  undefined1 auStack_170 [16];
  undefined1 auStack_160 [16];
  undefined1 auStack_150 [16];
  undefined1 auStack_140 [16];
  undefined1 auStack_130 [16];
  undefined1 auStack_120 [16];
  undefined1 auStack_110 [16];
  undefined1 auStack_100 [16];
  undefined1 auStack_f0 [16];
  undefined1 auStack_e0 [16];
  undefined1 auStack_d0 [16];
  undefined1 auStack_c0 [16];
  undefined1 auStack_b0 [16];
  undefined1 auStack_a0 [16];
  undefined1 auStack_90 [64];
  undefined1 auStack_50 [16];
  undefined1 auStack_40 [16];
  undefined4 uStack_30;
  int iStack_20;
  undefined4 uStack_10;
  
  uStack_30 = this;
  iStack_20 = param_2;
  uStack_10 = param_3;
  FVector::FVector(auStack_40);
  FVector::FVector(auStack_50);
  iVar1 = iStack_20->i32_f0;
  FVector::__as(auStack_50,iVar1->i32_8 + 0x2a0);
  bVar5 = iStack_20->u8_c & 3;
  if (bVar5 == 2) {
    if (-1 < (long)((ulong)iStack_20->u8_c << 0x3d)) {
      Matrix::__as(iStack_20 + 0x20,*(int *)(iVar1->i32_4 + 0x30) + 0x160);
      uVar3 = Matrix::GetPos(iStack_20 + 0x20);
      FVector::Origin(uVar3);
      Frame::getWorldPos
                (auStack_170,*(undefined4 *)(iVar1->i32_4 + 0x30),VIF1Prim::m_Env & 1);
      FVector::__as(iStack_20 + 0x10,auStack_170);
      puVar2 = (undefined4 *)FVector::vz(iStack_20 + 0x10);
      *puVar2 = 0;
      puVar2 = (undefined4 *)FVector::vx(iStack_20 + 0x10);
      *puVar2 = 0;
      iStack_20->u8_c = iStack_20->u8_c & 0xfb | 4;
    }
    Frame::getWorldPos
              (auStack_a0,*(undefined4 *)(iVar1->i32_4 + 0x30),VIF1Prim::m_Env & 1);
    puVar2 = (undefined4 *)FVector::vy(auStack_a0);
    *puVar2 = 0;
    Matrix::ApplyMatrix(auStack_1c0,iStack_20 + 0x20,uStack_10);
    Matrix::ApplyMatrix(auStack_1d0,iStack_20 + 0x20,iStack_20 + 0xc0);
    FVector::__pl(auStack_1b0,auStack_1c0,auStack_1d0);
    FVector::__pl(auStack_1a0,auStack_1b0,iStack_20 + 0x10);
    FVector::__pl(auStack_190,auStack_1a0,auStack_50);
    FVector::__pl(auStack_180,auStack_190,auStack_a0);
    FVector::__as(auStack_40,auStack_180);
  }
  else if (bVar5 == 1) {
    Matrix::Matrix(auStack_90,*(int *)(iVar1->i32_4 + 0x30) + 0x160);
    uVar3 = Matrix::GetPos(auStack_90);
    uVar4 = FVector::FVector(0,0,0,0x3f800000,auStack_110);
    FVector::__as(uVar3,uVar4);
    Frame::getWorldPos
              (auStack_120,*(undefined4 *)(iVar1->i32_4 + 0x30),VIF1Prim::m_Env & 1);
    FVector::__apl(auStack_50,auStack_120);
    Matrix::ApplyMatrix(auStack_150,auStack_90,uStack_10);
    Matrix::ApplyMatrix(auStack_160,auStack_90,iStack_20 + 0xc0);
    FVector::__pl(auStack_140,auStack_150,auStack_160);
    FVector::__pl(auStack_130,auStack_140,auStack_50);
    FVector::__as(auStack_40,auStack_130);
  }
  else if ((iStack_20->u8_c & 3) == 0) {
    if (-1 < (long)((ulong)iStack_20->u8_c << 0x3d)) {
      Matrix::__as(iStack_20 + 0x20,*(int *)(iVar1->i32_4 + 0x30) + 0x160);
      uVar3 = Matrix::GetPos(iStack_20 + 0x20);
      FVector::Origin(uVar3);
      Frame::getWorldPos
                (auStack_c0,*(undefined4 *)(iVar1->i32_4 + 0x30),VIF1Prim::m_Env & 1);
      FVector::__pl(auStack_b0,auStack_c0,auStack_50);
      FVector::__as(iStack_20 + 0x10,auStack_b0);
      iStack_20->u8_c = iStack_20->u8_c & 0xfb | 4;
    }
    Matrix::ApplyMatrix(auStack_f0,iStack_20 + 0x20,uStack_10);
    Matrix::ApplyMatrix(auStack_100,iStack_20 + 0x20,iStack_20 + 0xc0);
    FVector::__pl(auStack_e0,auStack_f0,auStack_100);
    FVector::__pl(auStack_d0,auStack_e0,iStack_20 + 0x10);
    FVector::__as(auStack_40,auStack_d0);
  }
  FVector::FVector(uStack_30,auStack_40);
  return;
}

// JP: 0x003097a0  SetInterFrame__12EffectCameraFP5ModelPc  =  EffectCamera::SetInterFrame
void EffectCamera::SetInterFrame(int this,int param_2,int param_3)

{
  undefined4 uVar1;
  
  if ((*(byte *)(this->i32_4 + 10) & 3) != 0) {
    if (param_3 == 0) {
      uVar1 = Frame::searchFrame(param_2->u32_30,this->i32_4 + 0xc);
      this->u32_8 = uVar1;
    }
    else {
      uVar1 = Frame::searchFrame(param_2->u32_30,param_3);
      this->u32_8 = uVar1;
    }
  }
  return;
}

// JP: 0x00309840  GetVecInter__12EffectCameraFR7FVector  =  EffectCamera::GetVecInter
void EffectCamera::GetVecInter(undefined4 this,int param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  float *pfVar2;
  float *pfVar3;
  float fVar4;
  undefined1 auStack_c0 [16];
  undefined1 auStack_b0 [16];
  undefined1 auStack_a0 [16];
  undefined1 auStack_90 [64];
  undefined1 auStack_50 [28];
  float fStack_34;
  undefined4 uStack_30;
  int iStack_20;
  undefined4 uStack_10;
  
  uStack_30 = this;
  iStack_20 = param_2;
  uStack_10 = param_3;
  FVector::__mi(auStack_50,param_2 + 0x70,param_2 + 0x60);
  puVar1 = (undefined4 *)FVector::vw(auStack_50);
  *puVar1 = 0x3f800000;
  pfVar2 = (float *)FVector::vz(auStack_50);
  pfVar3 = (float *)FVector::vx(auStack_50);
  fStack_34 = atanf(*pfVar2 / *pfVar3);
  fStack_34 = fStack_34 + 1.571;
  Matrix::Matrix(auStack_90);
  Matrix::RotYMatrix(fStack_34,auStack_90);
  Matrix::ApplyMatrix(auStack_a0,auStack_90,uStack_10);
  FVector::__ml(iStack_20->u32_e8,auStack_c0,auStack_50);
  FVector::__pl(auStack_b0,iStack_20 + 0x60,auStack_c0);
  FVector::__apl(auStack_a0,auStack_b0);
  fVar4 = iStack_20->f32_ec;
  pfVar2 = (float *)FVector::vy(auStack_a0);
  *pfVar2 = *pfVar2 + fVar4;
  FVector::FVector(uStack_30,auStack_a0);
  return;
}

// JP: 0x00309a60  GetVecPos__12EffectCameraFR7FVector  =  EffectCamera::GetVecPos
void EffectCamera::GetVecPos(undefined4 this,int param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  float *pfVar2;
  float *pfVar3;
  float fVar4;
  undefined1 auStack_c0 [16];
  undefined1 auStack_b0 [16];
  undefined1 auStack_a0 [16];
  undefined1 auStack_90 [64];
  undefined1 auStack_50 [28];
  float fStack_34;
  undefined4 uStack_30;
  int iStack_20;
  undefined4 uStack_10;
  
  uStack_30 = this;
  iStack_20 = param_2;
  uStack_10 = param_3;
  FVector::__mi(auStack_50,param_2 + 0x70,param_2 + 0x60);
  puVar1 = (undefined4 *)FVector::vw(auStack_50);
  *puVar1 = 0x3f800000;
  pfVar2 = (float *)FVector::vz(auStack_50);
  pfVar3 = (float *)FVector::vx(auStack_50);
  fStack_34 = atanf(*pfVar2 / *pfVar3);
  fStack_34 = fStack_34 + 1.571;
  Matrix::Matrix(auStack_90);
  Matrix::RotYMatrix(fStack_34,auStack_90);
  Matrix::ApplyMatrix(auStack_a0,auStack_90,uStack_10);
  FVector::__ml(iStack_20->u32_e8,auStack_c0,auStack_50);
  FVector::__pl(auStack_b0,iStack_20 + 0x60,auStack_c0);
  FVector::__apl(auStack_a0,auStack_b0);
  fVar4 = iStack_20->f32_ec;
  pfVar2 = (float *)FVector::vy(auStack_a0);
  *pfVar2 = *pfVar2 + fVar4;
  FVector::FVector(uStack_30,auStack_a0);
  return;
}

// JP: 0x00309bc0  SetVibratePower__12EffectCameraFP7FVector7FVector7FVectorif  =  EffectCamera::SetVibratePower
void EffectCamera::SetVibratePower
               (undefined4 this,int param_2,undefined4 param_3,undefined4 param_4,
               undefined4 param_5,int param_6)

{
  undefined8 uVar1;
  undefined1 auStack_70 [16];
  int iStack_60;
  undefined4 uStack_50;
  undefined4 uStack_40;
  undefined4 uStack_30;
  int iStack_20;
  undefined4 uStack_10;
  
  param_2->f32_e0 = (float)param_6;
  iStack_60 = param_2;
  uStack_50 = param_3;
  uStack_40 = param_4;
  uStack_30 = param_5;
  iStack_20 = param_6;
  uStack_10 = this;
  uVar1 = FVector::__as(param_2 + 0x90,param_4);
  FVector::__as(iStack_60 + 0xa0,uVar1);
  FVector::__as(iStack_60 + 0x80,uStack_50);
  uVar1 = FVector::FVector(0x3fc90fd8,0x3fc90fd8,0x3fc90fd8,0,auStack_70);
  FVector::__as(iStack_60 + 0xb0,uVar1);
  FVector::__as(iStack_60 + 0xd0,uStack_30);
  iStack_60->u32_e4 = uStack_10;
  return;
}

// JP: 0x00309cb0  GetVibPower__12EffectCameraFR7FVector  =  EffectCamera::GetVibPower
void EffectCamera::GetVibPower(undefined4 this,int param_2,undefined4 param_3)

{
  float *pfVar1;
  undefined4 *puVar2;
  int iVar3;
  float fVar4;
  undefined1 auStack_70 [16];
  undefined1 auStack_60 [16];
  undefined1 auStack_50 [24];
  float fStack_38;
  float fStack_34;
  undefined4 uStack_30;
  int iStack_20;
  undefined4 uStack_10;
  
  uStack_30 = this;
  iStack_20 = param_2;
  uStack_10 = param_3;
  FVector::__dv(param_2->u32_e0,auStack_70,param_2 + 0x90);
  FVector::__ami(iStack_20 + 0xa0,auStack_70);
  pfVar1 = (float *)FVector::vx(iStack_20 + 0xa0);
  if (*pfVar1 < 0.0) {
    puVar2 = (undefined4 *)FVector::vx(iStack_20 + 0xa0);
    *puVar2 = 0;
  }
  pfVar1 = (float *)FVector::vy(iStack_20 + 0xa0);
  if (*pfVar1 < 0.0) {
    puVar2 = (undefined4 *)FVector::vy(iStack_20 + 0xa0);
    *puVar2 = 0;
  }
  pfVar1 = (float *)FVector::vz(iStack_20 + 0xa0);
  if (*pfVar1 < 0.0) {
    puVar2 = (undefined4 *)FVector::vz(iStack_20 + 0xa0);
    *puVar2 = 0;
  }
  pfVar1 = (float *)FVector::vx(iStack_20 + 0xa0);
  if (((*pfVar1 == 0.0) && (pfVar1 = (float *)FVector::vy(iStack_20 + 0xa0), *pfVar1 == 0.0)) &&
     (pfVar1 = (float *)FVector::vz(iStack_20 + 0xa0), *pfVar1 == 0.0)) {
    FVector::FVector(uStack_30,iStack_20 + 0xa0);
  }
  else {
    FVector::__mi(auStack_50,uStack_10,iStack_20 + 0x80);
    fStack_34 = (float)FVector::Length(auStack_50);
    fStack_34 = fStack_34 * fStack_34 * iStack_20->f32_e4;
    FVector::__apl(iStack_20 + 0xb0,iStack_20 + 0xd0);
    pfVar1 = (float *)FVector::vx(iStack_20 + 0xb0);
    if (6.2839 < *pfVar1) {
      pfVar1 = (float *)FVector::vx(iStack_20 + 0xb0);
      *pfVar1 = *pfVar1 - 6.2839;
    }
    pfVar1 = (float *)FVector::vy(iStack_20 + 0xb0);
    if (6.2839 < *pfVar1) {
      pfVar1 = (float *)FVector::vy(iStack_20 + 0xb0);
      *pfVar1 = *pfVar1 - 6.2839;
    }
    pfVar1 = (float *)FVector::vz(iStack_20 + 0xb0);
    if (6.2839 < *pfVar1) {
      pfVar1 = (float *)FVector::vz(iStack_20 + 0xb0);
      *pfVar1 = *pfVar1 - 6.2839;
    }
    if ((long)((ulong)iStack_20->u8_c << 0x3b) < 0) {
      iVar3 = rand();
      fStack_38 = (float)iVar3 / 2.1474836e+09;
    }
    else {
      fStack_38 = 1.0;
    }
    if (fStack_34 == 0.0) {
      fStack_34 = 1.0;
    }
    FVector::FVector(auStack_60);
    pfVar1 = (float *)FVector::vx(iStack_20 + 0xb0);
    fVar4 = sinf(*pfVar1);
    pfVar1 = (float *)FVector::vx(iStack_20 + 0xa0);
    fVar4 = (fStack_38 * fVar4 * *pfVar1 * 100.0) / fStack_34;
    pfVar1 = (float *)FVector::vx(auStack_60);
    *pfVar1 = fVar4;
    pfVar1 = (float *)FVector::vy(iStack_20 + 0xb0);
    fVar4 = sinf(*pfVar1);
    pfVar1 = (float *)FVector::vy(iStack_20 + 0xa0);
    fVar4 = (fStack_38 * fVar4 * *pfVar1 * 100.0) / fStack_34;
    pfVar1 = (float *)FVector::vy(auStack_60);
    *pfVar1 = fVar4;
    pfVar1 = (float *)FVector::vz(iStack_20 + 0xb0);
    fVar4 = sinf(*pfVar1);
    pfVar1 = (float *)FVector::vz(iStack_20 + 0xa0);
    fVar4 = (fStack_38 * fVar4 * *pfVar1 * 100.0) / fStack_34;
    pfVar1 = (float *)FVector::vz(auStack_60);
    *pfVar1 = fVar4;
    FVector::FVector(uStack_30,auStack_60);
  }
  return;
}

// JP: 0x0030a280  SetBoxCamera__12EffectCameraFPvP7FVector  =  EffectCamera::SetBoxCamera
void EffectCamera::SetBoxCamera(int this,undefined4 param_2,undefined4 param_3)

{
  this->u32_f0 = param_2;
  this->u8_c = this->u8_c & 0xdf | 0x20;
  FVector::__as(this + 0xc0,param_3);
  return;
}

// JP: 0x0030a2f0  __ct__18EffectCameraMotionFv  =  EffectCameraMotion::EffectCameraMotion
undefined4 * EffectCameraMotion::EffectCameraMotion(undefined4 *this)

{
  this[3] = EffectCameraMotion::__vt;
  *this = 0;
  this[1] = 0;
  this[2] = 0;
  return this;
}

// JP: 0x0030a340  __dt__18EffectCameraMotionFv  =  EffectCameraMotion::~EffectCameraMotion
int EffectCameraMotion::~EffectCameraMotion(int this,short param_2)

{
  if ((this != 0) && (*(undefined1 **)(this + 0xc) = EffectCameraMotion::__vt, 0 < param_2))
  {
    __dl(this);
  }
  return this;
}

// JP: 0x0030a3b0  Create__18EffectCameraMotionFPc  =  EffectCameraMotion::Create
void EffectCameraMotion::Create(int *this,int param_2)

{
  *this = param_2;
  this[1] = *this + 0x10;
  return;
}

// JP: 0x0030a3f0  AddTime__18EffectCameraMotionFf  =  EffectCameraMotion::AddTime
void EffectCameraMotion::AddTime(float this,int param_2)

{
  param_2->f32_8 = param_2->f32_8 + this;
  return;
}

// JP: 0x0030a420  GetData__18EffectCameraMotionFP17tagEFCMMotionData  =  EffectCameraMotion::GetData
/* WARNING: Removing unreachable block (ram,0x0030a68c) */

undefined4 EffectCameraMotion::GetData(int *this,int param_2)

{
  undefined2 uVar1;
  int iVar2;
  float fVar3;
  undefined1 auStack_60 [16];
  undefined1 auStack_50 [16];
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [16];
  int *piStack_20;
  int iStack_10;
  
  iVar2 = 0;
  while( true ) {
    piStack_20 = this;
    iStack_10 = param_2;
    if ((int)(*(ushort *)(*this + 4) - 1) <= iVar2) {
      tagEFCMMotionData::__as
                (param_2,this[1] + (*(ushort *)(*this + 4) - 1) * 0x40);
      return 1;
    }
    if ((float)this[2] == *(float *)(this[1] + iVar2 * 0x40 + 0x20)) break;
    if ((*(float *)(this[1] + iVar2 * 0x40 + 0x20) < (float)this[2]) &&
       ((float)this[2] < *(float *)(this[1] + (iVar2 + 1) * 0x40 + 0x20))) {
      tagEFCMMotionData::__as(param_2,this[1] + iVar2 * 0x40);
      iStack_10->f32_20 =
           ((float)piStack_20[2] - *(float *)(piStack_20[1] + iVar2 * 0x40 + 0x20)) /
           (*(float *)(piStack_20[1] + (iVar2 + 1) * 0x40 + 0x20) -
           *(float *)(piStack_20[1] + iVar2 * 0x40 + 0x20));
      FVector::__mi
                (auStack_40,piStack_20[1] + (iVar2 + 1) * 0x40,piStack_20[1] + iVar2 * 0x40);
      FVector::__ml(iStack_10->u32_20,auStack_30,auStack_40);
      FVector::__apl(iStack_10,auStack_30);
      FVector::__mi
                (auStack_60,piStack_20[1] + (iVar2 + 1) * 0x40 + 0x10,
                 piStack_20[1] + iVar2 * 0x40 + 0x10);
      FVector::__ml(iStack_10->u32_20,auStack_50,auStack_60);
      FVector::__apl(iStack_10 + 0x10,auStack_50);
      fVar3 = (float)iStack_10->u16_24 +
              iStack_10->f32_20 *
              (float)(int)((uint)*(ushort *)(piStack_20[1] + (iVar2 + 1) * 0x40 + 0x24) -
                          (uint)*(ushort *)(piStack_20[1] + iVar2 * 0x40 + 0x24));
      if (fVar3 < 2.1474836e+09) {
        uVar1 = (undefined2)(int)fVar3;
      }
      else {
        uVar1 = (undefined2)(int)(fVar3 - 2.1474836e+09);
      }
      iStack_10->u16_24 = uVar1;
      iStack_10->f32_2c =
           iStack_10->f32_2c +
           iStack_10->f32_20 *
           (*(float *)(piStack_20[1] + (iVar2 + 1) * 0x40 + 0x2c) -
           *(float *)(piStack_20[1] + iVar2 * 0x40 + 0x2c));
      return 0;
    }
    iVar2 = iVar2 + 1;
  }
  tagEFCMMotionData::__as(param_2,this[1] + iVar2 * 0x40);
  return 0;
}
