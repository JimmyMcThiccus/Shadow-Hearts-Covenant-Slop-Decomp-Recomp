// decomp/D/EffectModel.c — cleaned Ghidra output (SLPM_602.19, Metrowerks MIPS), Shadow Hearts: Covenant JP demo.
// Field accesses are shown as this->T_off (T = u8/u16/u32/f32/i32/p, off = hex offset);
// JRing fields are named from the recovered struct. See notes/D/*.md for layouts.
// CAVEAT: when the base pointer is a float*/int*/short*, the number in `T_off` is an ELEMENT offset (byte offset = off*sizeof(elem)).
// `this` is the C++ this pointer (param_1); the Metrowerks ABI passes it in a0.

// JP: 0x00305030  __ct__11EffectModelFP10EffectCore  =  EffectModel::EffectModel
int EffectModel::EffectModel(int this,undefined4 param_2)

{
  ExModel::ExModel(this);
  *(undefined1 **)(this + 0x10) = EffectModel::__vt;
  this->u32_1c = 0x4068a0;
  Matrix::Matrix(this + 0x520);
  Matrix::Matrix(this + 0x560);
  this->u32_518 = 0;
  this->u32_514 = 0;
  this->u8_5a0 = 0;
  this->u32_5a4 = 0;
  this->u32_51c = 0;
  this->u32_510 = param_2;
  tagEMFlag::Init(this + 0x5a8);
  return this;
}

// JP: 0x00305110  __dt__11EffectModelFv  =  EffectModel::~EffectModel
int EffectModel::~EffectModel(int this,short param_2)

{
  int iVar1;
  
  if (this != 0) {
    *(undefined1 **)(this + 0x10) = EffectModel::__vt;
    this->u32_1c = 0x4068a0;
    if (this->i32_514 != 0) {
      iVar1 = this->i32_514;
      if (iVar1 != 0) {
        (**(code **)(iVar1->i32_c + 0xc))(iVar1,1);
      }
      this->u32_514 = 0;
    }
    EffectModel::UnChain(this);
    ExModel::~ExModel(this,0);
    if (0 < param_2) {
      __dl(this);
    }
  }
  return this;
}

// JP: 0x003051f0  MotionEndCallBack__11EffectModelFPCc  =  EffectModel::MotionEndCallBack
void EffectModel::MotionEndCallBack(int this,undefined4 param_2)

{
  if (this->i32_5a4 != 0) {
    (**(code **)(this + 0x5a4))(this,param_2);
  }
  return;
}

// JP: 0x00305240  UnChain__11EffectModelFv  =  EffectModel::UnChain
void EffectModel::UnChain(int this)

{
  int iVar1;
  
  for (iVar1 = 0; iVar1 < (int)(uint)*(ushort *)(this->i32_58 + 4); iVar1 = iVar1 + 1) {
    if (*(int *)(this->i32_30 + iVar1 * 0x1f0 + 0x1e0) != 0) {
      Frame::unChainModel(*(undefined4 *)(this->i32_30 + iVar1 * 0x1f0 + 0x1e0));
    }
  }
  return;
}

// JP: 0x003052e0  TranseCallBack__11EffectModelFRC7FVector7FVector  =  EffectModel::TranseCallBack
void EffectModel::TranseCallBack
               (undefined4 this,int param_2,float *param_3,float *param_4)

{
  float *pfVar1;
  undefined4 *puVar2;
  undefined8 uVar3;
  float fVar4;
  float fVar5;
  undefined1 auStack_a0 [16];
  undefined1 auStack_90 [16];
  undefined1 auStack_80 [64];
  undefined4 uStack_40;
  int iStack_30;
  float *pfStack_20;
  float *pfStack_10;
  
  uStack_40 = this;
  iStack_30 = param_2;
  pfStack_20 = param_3;
  pfStack_10 = param_4;
  if ((long)((ulong)param_2->u8_5a8 << 0x3e) < 0) {
    Matrix::Matrix(auStack_80,param_2 + 0x560);
    uVar3 = Matrix::GetPos(auStack_80);
    FVector::Origin(uVar3);
    Matrix::ApplyMatrix(auStack_a0,auStack_80,pfStack_10);
    FVector::__as(pfStack_10,auStack_a0);
    FVector::FVector(auStack_90);
    fVar4 = *pfStack_20;
    fVar5 = *pfStack_10;
    pfVar1 = (float *)FVector::vx(auStack_90);
    *pfVar1 = fVar4 + fVar5;
    fVar4 = pfStack_20[1];
    fVar5 = pfStack_10[1];
    pfVar1 = (float *)FVector::vy(auStack_90);
    *pfVar1 = fVar4 + fVar5;
    fVar4 = pfStack_20[2];
    fVar5 = pfStack_10[2];
    pfVar1 = (float *)FVector::vz(auStack_90);
    *pfVar1 = fVar4 + fVar5;
    puVar2 = (undefined4 *)FVector::vw(auStack_90);
    *puVar2 = 0x3f800000;
    uVar3 = Matrix::GetPos(iStack_30 + 0x560);
    FVector::__as(uVar3,auStack_90);
  }
  FVector::FVector(uStack_40,pfStack_10);
  return;
}

// JP: 0x00305480  create__11EffectModelFPUc  =  EffectModel::create
undefined1 EffectModel::create(undefined4 this,undefined4 param_2)

{
  undefined1 uVar1;
  
  uVar1 = ExModel::create(this,param_2);
  Model::setAlwayDrawFlg(this,1);
  EffectModel::SetEffectTestReg(this);
  return uVar1;
}

// JP: 0x00305520  create__11EffectModelFP9BufMemory  =  EffectModel::create
undefined1 EffectModel::create(undefined4 this,undefined4 param_2)

{
  undefined1 uVar1;
  
  uVar1 = ExModel::create(this,param_2);
  Model::setAlwayDrawFlg(this,1);
  EffectModel::SetEffectTestReg(this);
  return uVar1;
}

// JP: 0x00305580  SetEffectTestReg__11EffectModelFv  =  EffectModel::SetEffectTestReg
void EffectModel::SetEffectTestReg(int this)

{
  byte bVar1;
  ulong uVar2;
  int iVar3;
  
  for (iVar3 = 0; iVar3 < (int)(uint)*(ushort *)(this->i32_5c + 4); iVar3 = iVar3 + 1) {
    uVar2 = ((ulong)*(byte *)(**(int **)(this->i32_48 + iVar3 * 4) + 0x15) & 0xf) >> 1;
    if (uVar2 == 5) {
      bVar1 = *(byte *)(**(int **)(this->i32_48 + iVar3 * 4) + 0x12);
      Texture::changeGSTest
                (this->i32_4c + ((uint)bVar1 * 0x12 + (uint)bVar1) * 4,1,0,0x70,3,0,0,1)
      ;
    }
    else if ((uVar2 == 6) || (uVar2 == 4)) {
      bVar1 = *(byte *)(**(int **)(this->i32_48 + iVar3 * 4) + 0x12);
      Texture::changeGSTest
                (this->i32_4c + ((uint)bVar1 * 0x12 + (uint)bVar1) * 4,1,0,0x70,3,0,0,1)
      ;
    }
  }
  return;
}

// JP: 0x00305710  AddCustom__11EffectModelFP11CustomModelPc  =  EffectModel::AddCustom
void EffectModel::AddCustom(int this,int param_2,undefined4 param_3)

{
  undefined4 uVar1;
  long lVar2;
  undefined8 uVar3;
  
  if (this->i32_514 == 0) {
    lVar2 = __nw(0x10);
    uVar1 = 0;
    if (lVar2 != 0) {
      uVar1 = CustomList::CustomList(lVar2,param_2);
    }
    this->u32_514 = uVar1;
  }
  else {
    lVar2 = __nw(0x10);
    uVar3 = 0;
    if (lVar2 != 0) {
      uVar3 = CustomList::CustomList(lVar2,param_2);
    }
    CList::Add(this->u32_514,uVar3);
  }
  uVar1 = Frame::searchFrame(this->u32_30,param_3);
  param_2->u32_20 = uVar1;
  return;
}

// JP: 0x00305810  calcMatrix__11EffectModelFP6Matrix  =  EffectModel::calcMatrix
void EffectModel::calcMatrix(int this,undefined4 param_2)

{
  int iVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined1 auStack_130 [16];
  undefined1 auStack_120 [16];
  undefined1 auStack_110 [64];
  undefined1 auStack_d0 [16];
  undefined1 auStack_c0 [16];
  undefined1 auStack_b0 [64];
  undefined1 auStack_70 [16];
  undefined1 auStack_60 [64];
  int iStack_20;
  undefined4 uStack_10;
  
  iStack_20 = this;
  uStack_10 = param_2;
  Matrix::Matrix(auStack_60);
  Matrix::__as(auStack_60,iStack_20 + 0x560);
  uVar2 = Matrix::GetPos(auStack_60);
  FVector::Origin(uVar2);
  uVar2 = Matrix::GetPos(iStack_20 + 0x560);
  FVector::FVector(auStack_70,uVar2);
  if (iStack_20->i32_518 == 0) {
    Matrix::__as(iStack_20->i32_30 + 0x160,iStack_20 + 0x560);
  }
  else {
    Matrix::__as
              (iStack_20->i32_30 + 0x160,
               *(int *)(iStack_20->i32_518 + 0x90) + 0x160);
    uVar2 = Matrix::GetPos(iStack_20->i32_30 + 0x160);
    uVar3 = FVector::FVector(0,0,0,0x3f800000,auStack_d0);
    FVector::__as(uVar2,uVar3);
    Matrix::MulMatrix(auStack_110,auStack_60,iStack_20->i32_30 + 0x160);
    Matrix::__as(iStack_20->i32_30 + 0x160,auStack_110);
    Matrix::Matrix(auStack_b0,*(int *)(iStack_20->i32_518 + 0x90) + 0x160);
    uVar2 = Matrix::GetPos(auStack_b0);
    FVector::Origin(uVar2);
    Matrix::ApplyMatrix(auStack_c0,auStack_b0,auStack_70);
    uVar2 = Matrix::GetPos(iStack_20->i32_30 + 0x160);
    Frame::getWorldPos(auStack_130,iStack_20->u32_518,VIF1Prim::m_Env & 1);
    FVector::__pl(auStack_120,auStack_c0,auStack_130);
    FVector::__as(uVar2,auStack_120);
  }
  Frame::myMatrixUpdate(iStack_20->u32_30);
  ExModel::calcMatrix(iStack_20,uStack_10);
  for (iVar1 = iStack_20->i32_514; iVar1 != 0; iVar1 = CList::GetNext(iVar1)) {
    (**(code **)(*(int *)(iVar1->i32_8 + 0x10) + 0x24))();
  }
  return;
}

// JP: 0x00305ae0  addTime__11EffectModelFf  =  EffectModel::addTime
void EffectModel::addTime(undefined4 this,int param_2)

{
  int iVar1;
  
  Model::addTime(this,param_2);
  for (iVar1 = param_2->i32_514; iVar1 != 0; iVar1 = CList::GetNext(iVar1)) {
    (**(code **)(*(int *)(iVar1->i32_8 + 0x10) + 0x20))(this);
  }
  return;
}

// JP: 0x00305b60  getPacket__11EffectModelFv  =  EffectModel::getPacket
undefined8 EffectModel::getPacket(int this)

{
  undefined8 uVar1;
  
  if (this->i8_5a0 == '\0') {
    this->u8_5a0 = 1;
    uVar1 = 0;
  }
  else {
    uVar1 = ExModel::getPacket(this);
  }
  return uVar1;
}

// JP: 0x00305bb0  SetTrans__11EffectModelFP7FVector  =  EffectModel::SetTrans
void EffectModel::SetTrans(int this,undefined4 param_2)

{
  undefined8 uVar1;
  
  uVar1 = Matrix::GetPos(this + 0x560);
  FVector::__as(uVar1,param_2);
  return;
}

// JP: 0x00305bf0  SetRot__11EffectModelFP7FVector  =  EffectModel::SetRot
void EffectModel::SetRot(int this,undefined4 param_2)

{
  undefined8 uVar1;
  undefined8 uVar2;
  undefined1 auStack_70 [16];
  undefined1 auStack_60 [64];
  int iStack_20;
  undefined4 uStack_10;
  
  iStack_20 = this;
  uStack_10 = param_2;
  Matrix::Matrix(auStack_60);
  uVar1 = FVector::FVector(auStack_70,uStack_10);
  Matrix::RotMatrix(auStack_60,uVar1);
  uVar1 = Matrix::GetRight(iStack_20 + 0x560);
  uVar2 = Matrix::GetRight(auStack_60);
  FVector::__as(uVar1,uVar2);
  uVar1 = Matrix::GetUp(iStack_20 + 0x560);
  uVar2 = Matrix::GetUp(auStack_60);
  FVector::__as(uVar1,uVar2);
  uVar1 = Matrix::GetAt(iStack_20 + 0x560);
  uVar2 = Matrix::GetAt(auStack_60);
  FVector::__as(uVar1,uVar2);
  return;
}

// JP: 0x0030d900  SetMatrix__11EffectModelFP6Matrix  =  EffectModel::SetMatrix
void EffectModel::SetMatrix(int this,undefined4 param_2)

{
  undefined8 uVar1;
  undefined1 auStack_60 [64];
  int iStack_20;
  undefined4 uStack_10;
  
  iStack_20 = this;
  uStack_10 = param_2;
  uVar1 = Matrix::Matrix(auStack_60,param_2);
  Matrix::__as(iStack_20 + 0x560,uVar1);
  return;
}
