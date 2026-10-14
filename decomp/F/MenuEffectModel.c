/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x00291780  __ct__15MenuEffectModelFv  size 0x5c
// MenuEffectModel::MenuEffectModel()
int __ct__15MenuEffectModelFv(MenuEffectModel *this)
{
  __ct__7ExModelFv(this);
  this->f_10 /*u8 **/ = __vt__15MenuEffectModel;
  this->f_1c /*u32 **/ = 0x405b60;
  this->f_510 /*u32 **/ = 0;
  this->f_514 /*u8 **/ = 0;
  return this;
}

// JP: 0x002917e0  __dt__15MenuEffectModelFv  size 0x84
// MenuEffectModel::~MenuEffectModel()
int __dt__15MenuEffectModelFv(MenuEffectModel *this,short param_2)
{
  if (this != 0) {
    this->f_10 /*u8 **/ = __vt__15MenuEffectModel;
    this->f_1c /*u32 **/ = 0x405b60;
    __dt__7ExModelFv(this,0);
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

// JP: 0x00291870  Order__15MenuEffectModelFv  size 0x58
// MenuEffectModel::Order()
void Order__15MenuEffectModelFv(MenuEffectModel *this)
{
  if (this->f_514 /*char **/ == '\0') {
    AddDoubleOT__5WorldFiiP8VIF1Prim(0x42bf10,4,5,this);
    this->f_514 /*u8 **/ = 1;
  }
  return;
}

// JP: 0x002918d0  Release__15MenuEffectModelFv  size 0x60
// MenuEffectModel::Release()
void Release__15MenuEffectModelFv(MenuEffectModel *this)
{
  if (this->f_514 /*char **/ != '\0') {
    ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,this);
    ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,this);
    this->f_514 /*u8 **/ = 0;
  }
  return;
}

// JP: 0x00291930  SetTest__15MenuEffectModelFi  size 0xac
// MenuEffectModel::SetTest(int)
void SetTest__15MenuEffectModelFi(MenuEffectModel *this,u32 param_2)
{
  uint uVar1;
  for (uVar1 = 0; uVar1 < *(u16 *)(this->f_64 /*int **/ + 4); uVar1 = uVar1 + 1 & 0xffff) {
    changeGSTest__7TextureFiiiiiiii(this->f_4c /*int **/ + uVar1 * 0x4c,1,0,0x70,3,0,0,param_2);
  }
  return;
}

// JP: 0x002919e0  DeleteSetUp__15MenuEffectModelFv  size 0x3c
// MenuEffectModel::DeleteSetUp()
void DeleteSetUp__15MenuEffectModelFv(MenuEffectModel *this)
{
  DeleteSetUp__5ModelFv(this);
  ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,this);
  return;
}

// JP: 0x00291a20  MotionEndCallBack__15MenuEffectModelFPCc  size 0x58
// MenuEffectModel::MotionEndCallBack(const char*)
void MotionEndCallBack__15MenuEffectModelFPCc(MenuEffectModel *this,u32 param_2)
{
  MotionEndCallBack__5ModelFPCc(this,param_2);
  if (this->f_510 /*int **/ != 0) {
    FinishEffect__13MenuModelPackFP15MenuEffectModelPCc
              (this->f_510 /*u32 **/,this,param_2);
  }
  return;
}

// JP: 0x00291a80  @20@__dt__15MenuEffectModelFv  size 0x8
// @20@__dt__15MenuEffectModelFv
int _20___dt__15MenuEffectModelFv(MenuEffectModel *this,short param_2)
{
  int iVar1;
  iVar1 = this + -0x14;
  if (iVar1 != 0) {
    *(u8 **)(this + -4) = __vt__15MenuEffectModel;
    this->f_8 /*u32 **/ = 0x405b60;
    __dt__7ExModelFv(iVar1,0);
    if (0 < param_2) {
      __dl__FPv(iVar1);
    }
  }
  return iVar1;
}
