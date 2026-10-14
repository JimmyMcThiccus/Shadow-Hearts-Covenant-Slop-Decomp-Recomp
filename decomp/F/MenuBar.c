/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x002861a0  __ct__7MenuBarFv  size 0x60
// MenuBar::MenuBar()
int __ct__7MenuBarFv(MenuBar *this)
{
  __ct__10MenuSpriteFv(this);
  this->f_8 /*u8 **/ = __vt__7MenuBar;
  this->f_3c /*u32 **/ = 0x405744;
  (**(code **)(this->f_8 /*int **/ + 0x20))();
  return this;
}

// JP: 0x00286200  __dt__7MenuBarFv  size 0x94
// MenuBar::~MenuBar()
int __dt__7MenuBarFv(MenuBar *this,short param_2)
{
  if (this != 0) {
    this->f_8 /*u8 **/ = __vt__7MenuBar;
    this->f_3c /*u32 **/ = 0x405744;
    (**(code **)(this->f_8 /*int **/ + 0x1c))();
    __dt__10MenuSpriteFv(this,0);
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

// JP: 0x002862a0  SetBar__7MenuBarFv  size 0x54
// MenuBar::SetBar()
void SetBar__7MenuBarFv(MenuBar *this)
{
  this->f_60 /*u32 **/ = this->f_2c /*u32 **/;
  this->f_64 /*short **/ = this->f_58 /*short **/ - this->f_54 /*short **/;
  return;
}

// JP: 0x00286300  SetRange__7MenuBarFii  size 0x198
// MenuBar::SetRange(int, int)
/* WARNING: Removing unreachable block (ram,0x002863c8) */
void SetRange__7MenuBarFii(MenuBar *this,int param_2,int param_3)
{
  float fVar1;
  if (param_3 < 1) {
    this->f_12 /*u8 **/ = this->f_12 /*u8 **/ & 0xfe;
  }
  else {
    (**(code **)(this->f_8 /*int **/ + 0x28))
              (this->f_60 /*float **/ * ((float)param_2 / (float)param_3),
               this->f_30 /*u32 **/);
    fVar1 = (float)this->f_64 /*u16 **/ * ((float)param_2 / (float)param_3);
    if (2.1474836e+09 <= fVar1) {
      fVar1 = fVar1 - 2.1474836e+09;
    }
    SetUV__10MenuSpriteFUsUsUsUs
              (this,this->f_54 /*u16 **/,this->f_56 /*u16 **/,
               (uint)this->f_54 /*u16 **/ + ((int)fVar1 & 0xffffU) & 0xffff,
               this->f_5a /*u16 **/);
    this->f_12 /*u8 **/ = this->f_12 /*u8 **/ & 0xfe | 1;
  }
  return;
}

// JP: 0x002864a0  Round__7MenuBarFv  size 0x74
// MenuBar::Round()
void Round__7MenuBarFv(MenuBar *this)
{
  int iVar1;
  iVar1 = (int)this->f_2c /*float **/;
  if (0.5 <= this->f_2c /*float **/ - (float)iVar1) {
    iVar1 = iVar1 + 1;
  }
  this->f_2c /*float **/ = (float)iVar1;
  return;
}

// JP: 0x00286520  Clear__7MenuBarFv  size 0x3c
// MenuBar::Clear()
void Clear__7MenuBarFv(MenuBar *this)
{
  Clear__10MenuSpriteFv(this);
  this->f_60 /*u32 **/ = sm_fZero__7MenuObj;
  this->f_64 /*u16 **/ = 0;
  return;
}

// JP: 0x00286560  @60@__dt__7MenuBarFv  size 0x8
// @60@__dt__7MenuBarFv
u32 * _60___dt__7MenuBarFv(MenuBar *this,short param_2)
{
  u32 *puVar1;
  puVar1 = this + -0xf;
  if (puVar1 != (u32 *)0x0) {
    this[-0xd] = __vt__7MenuBar;
    *this = 0x405744;
    (**(code **)(this[-0xd] + 0x1c))();
    __dt__10MenuSpriteFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}
