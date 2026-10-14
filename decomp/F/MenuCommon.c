/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x0028d440  SetIcon__10MenuCommonFcP10MenuSprite  size 0x190
// MenuCommon::SetIcon(char, MenuSprite*)
void SetIcon__10MenuCommonFcP10MenuSprite(char param_1,int this)
{
  int iVar1;
  uint uVar2;
  uint uVar3;
  float fVar4;
  float fVar5;
  fVar4 = this->f_2c /*float **/;
  if (2.1474836e+09 <= fVar4) {
    fVar4 = fVar4 - 2.1474836e+09;
  }
  fVar5 = this->f_30 /*float **/;
  if (2.1474836e+09 <= fVar5) {
    fVar5 = fVar5 - 2.1474836e+09;
  }
  iVar1 = (int)param_1;
  if (param_1 < '\0') {
    iVar1 = iVar1 + 7;
  }
  uVar2 = ((int)fVar4 & 0xffffU) * ((int)param_1 + (iVar1 >> 3 & 0xffffU) * -8) & 0xffff;
  uVar3 = (iVar1 >> 3 & 0xffffU) * ((int)fVar5 & 0xffffU) & 0xffff;
  SetUV__10MenuSpriteFUsUsUsUs
            (this,uVar2,uVar3,uVar2 + ((int)fVar4 & 0xffffU) & 0xffff,
             uVar3 + ((int)fVar5 & 0xffffU) & 0xffff);
  this->f_10 /*u8 **/ = this->f_10 /*u8 **/ | 0x3f;
  this->f_11 /*u8 **/ = this->f_11 /*u8 **/ | 0x3f;
  return;
}

// JP: 0x0028d5d0  __ct__10MenuCommonFv  size 0x134
// MenuCommon::MenuCommon()
int __ct__10MenuCommonFv(MenuCommon *this)
{
  __ct__9MenuSceneFv(this);
  this->f_8 /*u8 **/ = __vt__10MenuCommon;
  __construct_array(this + 0x58,0x2676b0,0x2677a0,0x40,3);
  __construct_array(this + 0x118,0x2676b0,0x2677a0,0x40,2);
  __construct_array(this + 0x198,0x2676b0,0x2677a0,0x40,2);
  __ct__11MenuTextureFv(this + 0x218);
  __ct__11MenuTextureFv(this + 600);
  __ct__11MenuTextureFv(this + 0x298);
  __ct__11MenuTextureFv(this + 0x2d8);
  __ct__11MenuTextureFv(this + 0x318);
  __ct__11MenuTextureFv(this + 0x358);
  __ct__11MenuTextureFv(this + 0x398);
  __ct__11MenuTextureFv(this + 0x3d8);
  return this;
}

// JP: 0x0028d710  __dt__10MenuCommonFv  size 0x174
// MenuCommon::~MenuCommon()
int __dt__10MenuCommonFv(MenuCommon *this,short param_2)
{
  if (this != 0) {
    this->f_8 /*u8 **/ = __vt__10MenuCommon;
    __dt__11MenuTextureFv(this + 0x3d8,0xffffffffffffffff);
    __dt__11MenuTextureFv(this + 0x398,0xffffffffffffffff);
    __dt__11MenuTextureFv(this + 0x358,0xffffffffffffffff);
    __dt__11MenuTextureFv(this + 0x318,0xffffffffffffffff);
    __dt__11MenuTextureFv(this + 0x2d8,0xffffffffffffffff);
    __dt__11MenuTextureFv(this + 0x298,0xffffffffffffffff);
    __dt__11MenuTextureFv(this + 600,0xffffffffffffffff);
    __dt__11MenuTextureFv(this + 0x218,0xffffffffffffffff);
    __destroy_arr(this + 0x198,0x2677a0,0x40,2);
    __destroy_arr(this + 0x118,0x2677a0,0x40,2);
    __destroy_arr(this + 0x58,0x2677a0,0x40,3);
    __dt__9MenuSceneFv(this,0);
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

// JP: 0x0028d890  GetReady__10MenuCommonFv  size 0x320
// MenuCommon::GetReady()
u32 GetReady__10MenuCommonFv(MenuCommon *this)
{
  CreateFont__4FontFiPUc(0,*(u32 *)(this->f_54 /*int **/ + 0x10));
  Create__11MenuTextureFPUc6GS_PSMUii
            (this + 0x198,*(u32 *)(this->f_54 /*int **/ + 0x1c),0x30,0,0);
  Create__11MenuTextureFPUc6GS_PSMUii
            (this + 0x1d8,*(u32 *)(this->f_54 /*int **/ + 0x28),0x30,0,0);
  Create__11MenuTextureFPUc6GS_PSMUii
            (this + 0x218,*(u32 *)(this->f_54 /*int **/ + 0x34),0x30,0,0);
  Create__11MenuTextureFPUc6GS_PSMUii
            (this + 0x118,*(u32 *)(this->f_54 /*int **/ + 0x40),0x30,0,0);
  Create__11MenuTextureFPUc6GS_PSMUii
            (this + 0x158,*(u32 *)(this->f_54 /*int **/ + 0xa0),0x30,0,0);
  Create__11MenuTextureFPUc6GS_PSMUii
            (this + 0x3d8,*(u32 *)(this->f_54 /*int **/ + 0xac),0x30,0,0);
  Create__11MenuTextureFPUc6GS_PSMUii
            (this + 0x98,*(u32 *)(this->f_54 /*int **/ + 0x4c),0x30,
             sm_freeBlock__7MenuObj,8);
  Create__11MenuTextureFPUc6GS_PSMUii
            (this + 0x58,*(u32 *)(this->f_54 /*int **/ + 0x58),0x30,
             sm_freeBlock__7MenuObj,8);
  Create__11MenuTextureFPUc6GS_PSMUii
            (this + 0xd8,*(u32 *)(this->f_54 /*int **/ + 100),0x30,
             sm_freeBlock__7MenuObj,8);
  Create__11MenuTextureFPUc6GS_PSMUii
            (this + 0x298,*(u32 *)(this->f_54 /*int **/ + 0x70),0x30,0,0);
  Create__11MenuTextureFPUc6GS_PSMUii
            (this + 0x318,*(u32 *)(this->f_54 /*int **/ + 0x7c),0x30,0,0);
  Create__11MenuTextureFPUc6GS_PSMUii
            (this + 0x2d8,*(u32 *)(this->f_54 /*int **/ + 0x88),0x30,0,0);
  Create__11MenuTextureFPUc6GS_PSMUii
            (this + 0x358,*(u32 *)(this->f_54 /*int **/ + 0x94),0x30,0,0);
  Create__11MenuTextureFPUc6GS_PSMUii
            (this + 600,*(u32 *)(this->f_54 /*int **/ + 0xb8),0x30,0,0);
  return 1;
}
