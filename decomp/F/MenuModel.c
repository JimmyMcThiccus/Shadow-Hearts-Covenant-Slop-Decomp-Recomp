/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x00281a80  __ct__9MenuModelFv  size 0xc4
// MenuModel::MenuModel()
int __ct__9MenuModelFv(MenuModel *this)
{
  __ct__5ModelFv(this);
  this->f_10 /*u8 **/ = __vt__9MenuModel;
  this->f_1c /*u32 **/ = 0x405540;
  this->f_4b0 /*u32 **/ = 0;
  this->f_4b4 /*u32 **/ = 0;
  this->f_4b8 /*u32 **/ = 0;
  this->f_4bc /*u32 **/ = 0x3f800000;
  this->f_4c0 /*u16 **/ = 0;
  this->f_4c2 /*u16 **/ = 0;
  this->f_4d0 /*u32 **/ = 1;
  memset((void *)(this + 0x4c4),0,4);
  memset((void *)(this + 0x4c8),0,8);
  return this;
}

// JP: 0x00281b50  __dt__9MenuModelFv  size 0xc0
// MenuModel::~MenuModel()
int __dt__9MenuModelFv(MenuModel *this,short param_2)
{
  if (this != 0) {
    this->f_10 /*u8 **/ = __vt__9MenuModel;
    this->f_1c /*u32 **/ = 0x405540;
    if (this->f_4b4 /*int **/ != 0) {
      if (this->f_4b4 /*int **/ != 0) {
        __dla__FPv(this->f_4b4 /*int **/ + -0x10);
      }
      this->f_4b4 /*u32 **/ = 0;
    }
    __dt__5ModelFv(this,0);
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

// JP: 0x00281c10  Order__9MenuModelFP13MenuModelPackii  size 0x6c
// MenuModel::Order(MenuModelPack*, int, int)
void Order__9MenuModelFP13MenuModelPackii
               (MenuModel *this,u32 param_2,u32 param_3,u32 param_4)
{
  EnableAlpha__9MenuModelFv(this);
  SetAlpha__9MenuModelFUc(this,0);
  AddDoubleOT__5WorldFiiP8VIF1Prim(0x42bf10,param_3,param_4,this);
  this->f_4b0 /*u32 **/ = param_2;
  return;
}

// JP: 0x00281c80  CalcMatrix__9MenuModelFv  size 0x140
// MenuModel::CalcMatrix()
void CalcMatrix__9MenuModelFv(MenuModel *this)
{
  int iVar1;
  int iVar2;
  u8 in_vf0 [16];
  u8 auVar3 [16];
  u8 auVar4 [16];
  u8 auVar5 [16];
  u8 auVar6 [16];
  u8 auVar7 [16];
  u8 auVar8 [16];
  u8 auVar9 [16];
  u8 auVar10 [16];
  u8 auStack_40 [16];
  u8 auStack_30 [16];
  u8 auStack_20 [16];
  auVar3 = _vmr32(in_vf0);
  auVar4 = _vmr32(auVar3);
  auVar5 = _vmr32(auVar4);
  _sqc2(in_vf0);
  _sqc2(auVar3);
  _sqc2(auVar4);
  _sqc2(auVar5);
  auVar4 = _vmr32(in_vf0);
  auVar5 = _vmr32(auVar4);
  auVar6 = _vmr32(auVar5);
  auVar3 = _sqc2(in_vf0);
  auVar4 = _sqc2(auVar4);
  auVar5 = _sqc2(auVar5);
  auVar6 = _sqc2(auVar6);
  auStack_20._8_4_ = this->f_4bc /*u32 **/;
  auStack_20._12_4_ = auVar4._12_4_;
  auStack_20._0_8_ = auVar4._0_8_;
  auStack_30._8_8_ = auVar5._8_8_;
  auStack_30._0_4_ = auVar5._0_4_;
  auStack_30._4_4_ = auStack_20._8_4_;
  auStack_40._4_12_ = auVar6._4_12_;
  auStack_40._0_4_ = auStack_20._8_4_;
  iVar2 = this->f_30 /*int **/;
  auVar5 = _vmr32(in_vf0);
  auVar6 = _vmr32(auVar5);
  auVar7 = _vmr32(auVar6);
  auVar4 = _sqc2(in_vf0);
  *(u8 (*) [16])(iVar2 + 400) = auVar4;
  auVar4 = _sqc2(auVar5);
  *(u8 (*) [16])(iVar2 + 0x180) = auVar4;
  auVar4 = _sqc2(auVar6);
  *(u8 (*) [16])(iVar2 + 0x170) = auVar4;
  auVar4 = _sqc2(auVar7);
  *(u8 (*) [16])(iVar2 + 0x160) = auVar4;
  iVar2 = this->f_30 /*int **/ + 0x160;
  sceVu0RotMatrixY(this->f_4b8 /*u32 **/,iVar2,iVar2);
  iVar2 = this->f_30 /*int **/;
  iVar1 = this->f_30 /*int **/;
  auVar4 = _lqc2(auStack_40);
  auVar5 = _lqc2(auStack_30);
  auVar6 = _lqc2(auStack_20);
  auVar3 = _lqc2(auVar3);
  auVar7 = _lqc2(*(u8 (*) [16])(iVar2 + 0x160));
  _vmulabc(auVar4,auVar7);
  _vmaddabc(auVar5,auVar7);
  _vmaddabc(auVar6,auVar7);
  auVar8 = _vmaddbc(auVar3,auVar7);
  auVar7 = _lqc2(*(u8 (*) [16])(iVar2 + 0x170));
  _vmulabc(auVar4,auVar7);
  _vmaddabc(auVar5,auVar7);
  _vmaddabc(auVar6,auVar7);
  auVar9 = _vmaddbc(auVar3,auVar7);
  auVar7 = _lqc2(*(u8 (*) [16])(iVar2 + 0x180));
  _vmulabc(auVar4,auVar7);
  _vmaddabc(auVar5,auVar7);
  _vmaddabc(auVar6,auVar7);
  auVar10 = _vmaddbc(auVar3,auVar7);
  auVar7 = _lqc2(*(u8 (*) [16])(iVar2 + 400));
  _vmulabc(auVar4,auVar7);
  _vmaddabc(auVar5,auVar7);
  _vmaddabc(auVar6,auVar7);
  auVar4 = _vmaddbc(auVar3,auVar7);
  auVar3 = _sqc2(auVar8);
  *(u8 (*) [16])(iVar1 + 0x160) = auVar3;
  auVar3 = _sqc2(auVar9);
  *(u8 (*) [16])(iVar1 + 0x170) = auVar3;
  auVar3 = _sqc2(auVar10);
  *(u8 (*) [16])(iVar1 + 0x180) = auVar3;
  auVar3 = _sqc2(auVar4);
  *(u8 (*) [16])(iVar1 + 400) = auVar3;
  myMatrixUpdate__5FrameFv(this->f_30 /*u32 **/);
  return;
}

// JP: 0x00281dc0  EnableAlpha__9MenuModelFv  size 0xac
// MenuModel::EnableAlpha()
void EnableAlpha__9MenuModelFv(MenuModel *this)
{
  uint uVar1;
  for (uVar1 = 0; uVar1 < *(u16 *)(this->f_64 /*int **/ + 4); uVar1 = uVar1 + 1 & 0xffff) {
    changeGSTest__7TextureFiiiiiiii(this->f_4c /*int **/ + uVar1 * 0x4c,0,0,0,0,0,0,1);
  }
  return;
}

// JP: 0x00281e70  DisableAlpha__9MenuModelFv  size 0xac
// MenuModel::DisableAlpha()
void DisableAlpha__9MenuModelFv(MenuModel *this)
{
  uint uVar1;
  for (uVar1 = 0; uVar1 < *(u16 *)(this->f_64 /*int **/ + 4); uVar1 = uVar1 + 1 & 0xffff) {
    changeGSTest__7TextureFiiiiiiii(this->f_4c /*int **/ + uVar1 * 0x4c,1,5,0x70,3,0,0,1);
  }
  return;
}

// JP: 0x00281f20  SetAlpha__9MenuModelFUc  size 0xcc
// MenuModel::SetAlpha(unsigned char)
void SetAlpha__9MenuModelFUc(MenuModel *this,u8 param_2)
{
  int iVar1;
  uint uVar2;
  this->f_29c /*uint **/ = (uint)param_2;
  this->f_28c /*uint **/ = (uint)param_2;
  for (uVar2 = 0; uVar2 < *(u16 *)(this->f_5c /*int **/ + 4); uVar2 = uVar2 + 1 & 0xffff) {
    iVar1 = *(int *)(this->f_48 /*int **/ + uVar2 * 4);
    (**(code **)(*(int *)(iVar1 + 0x370) + 0x24))(iVar1,param_2);
    setAtomicAlpha__6AtomicFUc(*(u32 *)(this->f_48 /*int **/ + uVar2 * 4),param_2);
  }
  return;
}

// JP: 0x00281ff0  SetAngle__9MenuModelFf  size 0x88
// MenuModel::SetAngle(float)
void SetAngle__9MenuModelFf(float param_1,int this)
{
  u32 uStack_10;
  if (halfAngle__9MenuModel <= param_1) {
    uStack_10 = param_1 - allAngle__9MenuModel;
  }
  else {
    uStack_10 = param_1;
    if (param_1 <= -halfAngle__9MenuModel) {
      uStack_10 = param_1 + allAngle__9MenuModel;
    }
  }
  this->f_4b8 /*float **/ = uStack_10;
  return;
}

// JP: 0x00282080  SetSingleColor__9MenuModelFUcUcUc  size 0x1c0
// MenuModel::SetSingleColor(unsigned char, unsigned char, unsigned char)
void SetSingleColor__9MenuModelFUcUcUc
               (MenuModel *this,u8 param_2,u8 param_3,u8 param_4)
{
  u16 uVar1;
  uint uVar2;
  u64 uVar3;
  int *piVar4;
  u8 *puVar5;
  int *piVar6;
  int iVar7;
  uint uVar8;
  u8 *puVar9;
  uint uVar10;
  uVar1 = *(u16 *)(this->f_64 /*int **/ + 4);
  uVar10 = (uint)uVar1;
  if (this->f_4b4 /*int **/ == 0) {
    uVar3 = __nwa__FUi(uVar10 * 0x400 + 0x10);
    uVar2 = __construct_new_array(uVar3,0x282240,0,4,uVar10 << 8);
    this->f_4b4 /*uint **/ = uVar2;
    piVar6 = this->f_4c /*int **/;
    piVar4 = piVar6 + (uVar10 * 8 + (uint)uVar1) * 2 + (uint)uVar1;
    for (; piVar6 < piVar4; piVar6 = piVar6 + 0x13) {
      iVar7 = *(int *)piVar6[3];
      *(uint *)piVar6[3] = uVar2;
      *(uint *)(*piVar6 + 0xf4) = uVar2;
      *(uint *)(piVar6[1] + 0xf4) = uVar2;
      uVar8 = uVar2 + 0x400;
      for (; uVar2 < uVar8; uVar2 = uVar2 + 4) {
        *(u8 *)(uVar2 + 3) = *(u8 *)(iVar7 + 3);
        if (*(char *)(uVar2 + 3) != '\0') {
          *(u8 *)(uVar2 + 3) = 0x80;
        }
        iVar7 = iVar7 + 4;
      }
    }
  }
  puVar5 = this->f_4b4 /*u8 **/;
  puVar9 = puVar5 + uVar10 * 0x400;
  for (; puVar5 < puVar9; puVar5 = puVar5 + 4) {
    *puVar5 = param_2;
    puVar5[1] = param_3;
    puVar5[2] = param_4;
  }
  return;
}

// JP: 0x00282260  DeleteSetUp__9MenuModelFv  size 0x3c
// MenuModel::DeleteSetUp()
void DeleteSetUp__9MenuModelFv(MenuModel *this)
{
  DeleteSetUp__5ModelFv(this);
  ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,this);
  return;
}

// JP: 0x002822a0  TranseCallBack__9MenuModelFRC7FVector7FVector  size 0x4c
// MenuModel::TranseCallBack(const FVector&, FVector)
void TranseCallBack__9MenuModelFRC7FVector7FVector
               (MenuModel *this,u64 param_2,u64 param_3,u32 *param_4)
{
  param_4[2] = 0;
  param_4[1] = 0;
  *param_4 = 0;
  __ct__7FVectorFRC7FVector(this,param_4);
  return;
}

// JP: 0x002822f0  EventCallBack__9MenuModelFPCcPCciiUi  size 0xb0
// MenuModel::EventCallBack(const char*, const char*, int, int, unsigned int)
void EventCallBack__9MenuModelFPCcPCciiUi
               (MenuModel *this,u32 param_2,char *param_3,u32 param_4,u32 param_5,
               u32 param_6)
{
  int iVar1;
  if (((this->f_4d0 /*int **/ != 0) || (iVar1 = strncmp(param_3,(char *)&_3087,3), iVar1 != 0))
     && (EventCallBack__5ModelFPCcPCciiUi(this,param_2,param_3,param_4,param_5,param_6),
        this->f_4b0 /*int **/ != 0)) {
    Event__13MenuModelPackFP9MenuModelPCcPCc
              (this->f_4b0 /*u32 **/,this,param_3,param_2);
  }
  return;
}

// JP: 0x002823a0  MotionEndCallBack__9MenuModelFPCc  size 0x58
// MenuModel::MotionEndCallBack(const char*)
void MotionEndCallBack__9MenuModelFPCc(MenuModel *this,u32 param_2)
{
  MotionEndCallBack__5ModelFPCc(this,param_2);
  if (this->f_4b0 /*int **/ != 0) {
    FinishMotion__13MenuModelPackFP9MenuModelPCc(this->f_4b0 /*u32 **/,this,param_2);
  }
  return;
}

// JP: 0x00282400  getPacket__9MenuModelFv  size 0x38
// MenuModel::getPacket()
void getPacket__9MenuModelFv(MenuModel *this)
{
  GetPacket__9MenuModelFUc(this,((ulong)this->f_c /*u8 **/ & 7) >> 1);
  return;
}

// JP: 0x00282440  GetPacket__9MenuModelFUc  size 0x138
// MenuModel::GetPacket(unsigned char)
u32 GetPacket__9MenuModelFUc(MenuModel *this,u8 param_2)
{
  u32 uVar1;
  int iVar2;
  if (this->f_4c2 /*short **/ == 0) {
    uVar1 = getPacket__5ModelFv(this);
    *(u32 *)(this + (uint)param_2 * 4 + 0x4c8) = uVar1;
  }
  else {
    if (this->f_4c2 /*short **/ < *(short *)(this + (uint)param_2 * 2 + 0x4c4)) {
      *(u16 *)(this + (uint)param_2 * 2 + 0x4c4) = 0;
    }
    if (*(short *)(this + (uint)param_2 * 2 + 0x4c4) == 0) {
      uVar1 = getPacket__5ModelFv(this);
      *(u32 *)(this + (uint)param_2 * 4 + 0x4c8) = uVar1;
    }
    iVar2 = this + (uint)param_2 * 2;
    *(short *)(iVar2 + 0x4c4) = *(short *)(iVar2 + 0x4c4) + 1;
  }
  return *(u32 *)(this + (uint)param_2 * 4 + 0x4c8);
}

// JP: 0x00282580  @20@__dt__9MenuModelFv  size 0x8
// @20@__dt__9MenuModelFv
int _20___dt__9MenuModelFv(MenuModel *this,short param_2)
{
  int iVar1;
  iVar1 = this + -0x14;
  if (iVar1 != 0) {
    *(u8 **)(this + -4) = __vt__9MenuModel;
    this->f_8 /*u32 **/ = 0x405540;
    if (this->f_4a0 /*int **/ != 0) {
      if (this->f_4a0 /*int **/ != 0) {
        __dla__FPv(this->f_4a0 /*int **/ + -0x10);
      }
      this->f_4a0 /*u32 **/ = 0;
    }
    __dt__5ModelFv(iVar1,0);
    if (0 < param_2) {
      __dl__FPv(iVar1);
    }
  }
  return iVar1;
}
