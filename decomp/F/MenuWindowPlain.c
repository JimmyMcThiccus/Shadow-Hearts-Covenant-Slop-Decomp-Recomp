/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x00288bf0  __ct__15MenuWindowPlainFv  size 0x60
// MenuWindowPlain::MenuWindowPlain()
int __ct__15MenuWindowPlainFv(MenuWindowPlain *this)
{
  __ct__16MenuWindowObjectFv(this);
  this->f_8 /*u8 **/ = __vt__15MenuWindowPlain;
  __ct__11MenuPolygonFv(this + 0x1c);
  (**(code **)(this->f_8 /*int **/ + 0x20))();
  return this;
}

// JP: 0x00288c50  __dt__15MenuWindowPlainFv  size 0x9c
// MenuWindowPlain::~MenuWindowPlain()
int __dt__15MenuWindowPlainFv(MenuWindowPlain *this,short param_2)
{
  if (this != 0) {
    this->f_8 /*u8 **/ = __vt__15MenuWindowPlain;
    (**(code **)(this->f_8 /*int **/ + 0x1c))();
    __dt__11MenuPolygonFv(this + 0x1c,0xffffffffffffffff);
    __dt__16MenuWindowObjectFv(this,0);
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

// JP: 0x00288cf0  Create__15MenuWindowPlainFP10MenuWindow  size 0x11c
// MenuWindowPlain::Create(MenuWindow*)
void Create__15MenuWindowPlainFP10MenuWindow(MenuWindowPlain *this,u32 menuWindow)
{
  if (-1 < (long)((ulong)this->f_12 /*u8 **/ << 0x3b)) {
    Create__11MenuPolygonFUcUc(this + 0x1c,0,1);
    (**(code **)(this->f_24 /*int **/ + 0x38))(this + 0x1c,menuWindow);
    SetColor__11MenuPolygonFiUcUcUc(this + 0x1c,0,0x30,0x30,0x60);
    SetColor__11MenuPolygonFiUcUcUc(this + 0x1c,1,0x30,0x30,0x60);
    SetColor__11MenuPolygonFiUcUcUc(this + 0x1c,2,0x20,0x20,0x40);
    SetColor__11MenuPolygonFiUcUcUc(this + 0x1c,3,0x20,0x20,0x40);
    this->f_12 /*u8 **/ = this->f_12 /*u8 **/ & 0xef | 0x10;
  }
  this->f_18 /*u32 **/ = menuWindow;
  return;
}

// JP: 0x00288e10  SetForm__15MenuWindowPlainFffff  size 0xb8
// MenuWindowPlain::SetForm(float, float, float, float)
void SetForm__15MenuWindowPlainFffff
               (u32 param_1,u32 param_2,u32 param_3,u32 param_4,
               int this)
{
  ulong uVar1;
  (**(code **)(this->f_24 /*int **/ + 0x24))(param_1,param_2);
  (**(code **)(this->f_24 /*int **/ + 0x28))(param_3,param_4);
  uVar1 = (ulong)this->f_11 /*u8 **/ & 0xfffffffffffffff7 | 8;
  this->f_11 /*char **/ = (char)uVar1;
  this->f_10 /*u8 **/ =
       this->f_10 /*u8 **/ & 0xf7 | (u8)((uint)((uVar1 << 0x3c) >> 0x3f) << 3);
  return;
}

// JP: 0x00288ed0  SetColor__15MenuWindowPlainFUcUcUc  size 0x4c
// MenuWindowPlain::SetColor(unsigned char, unsigned char, unsigned char)
void SetColor__15MenuWindowPlainFUcUcUc
               (MenuWindowPlain *this,u8 param_2,u8 param_3,u8 param_4)
{
  (**(code **)(this->f_24 /*int **/ + 0x30))(this + 0x1c,param_2,param_3,param_4);
  return;
}

// JP: 0x00288f20  SetAlpha__15MenuWindowPlainFUc  size 0x3c
// MenuWindowPlain::SetAlpha(unsigned char)
void SetAlpha__15MenuWindowPlainFUc(MenuWindowPlain *this,u8 param_2)
{
  (**(code **)(this->f_24 /*int **/ + 0x2c))(this + 0x1c,param_2);
  return;
}

// JP: 0x00288f60  Update__15MenuWindowPlainFiiUs  size 0xb0
// MenuWindowPlain::Update(int, int, unsigned short)
void Update__15MenuWindowPlainFiiUs
               (MenuWindowPlain *this,u32 param_2,u32 param_3,u16 param_4)
{
  u8 bVar1;
  u8 *pbVar2;
  pbVar2 = (u8 *)(this + (m_Env__8VIF1Prim & 1) + 0x10);
  bVar1 = *pbVar2;
  this->f_2c /*u8 **/ = this->f_2c /*u8 **/ | bVar1;
  this->f_2d /*u8 **/ = this->f_2d /*u8 **/ | bVar1;
  (**(code **)(this->f_24 /*int **/ + 0x14))(this + 0x1c,param_2,param_3,param_4);
  *pbVar2 = *pbVar2 & 0x80;
  return;
}

// JP: 0x00289010  Connect__15MenuWindowPlainFP4_QWD  size 0x3c
// MenuWindowPlain::Connect(_QWD*)
void Connect__15MenuWindowPlainFP4_QWD(MenuWindowPlain *this,u32 param_2)
{
  (**(code **)(this->f_24 /*int **/ + 0x18))(this + 0x1c,param_2);
  return;
}

// JP: 0x00289050  Destroy__15MenuWindowPlainFv  size 0x34
// MenuWindowPlain::Destroy()
void Destroy__15MenuWindowPlainFv(MenuWindowPlain *this)
{
  (**(code **)(this->f_24 /*int **/ + 0x1c))();
  return;
}

// JP: 0x00289090  Clear__15MenuWindowPlainFv  size 0x48
// MenuWindowPlain::Clear()
void Clear__15MenuWindowPlainFv(MenuWindowPlain *this)
{
  Clear__7MenuObjFv(this);
  this->f_18 /*u32 **/ = 0;
  (**(code **)(this->f_24 /*int **/ + 0x20))();
  return;
}
