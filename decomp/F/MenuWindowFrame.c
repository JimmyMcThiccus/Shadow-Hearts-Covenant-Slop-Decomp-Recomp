/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x002875c0  __ct__15MenuWindowFrameFv  size 0x70
// MenuWindowFrame::MenuWindowFrame()
int __ct__15MenuWindowFrameFv(MenuWindowFrame *this)
{
  __ct__16MenuWindowObjectFv(this);
  this->f_8 /*u8 **/ = __vt__15MenuWindowFrame;
  __ct__11MenuPolygonFv(this + 0x1c);
  __ct__9MenuFrameFv(this + 0xa0);
  (**(code **)(this->f_8 /*int **/ + 0x20))();
  return this;
}

// JP: 0x00287630  __dt__15MenuWindowFrameFv  size 0xac
// MenuWindowFrame::~MenuWindowFrame()
int __dt__15MenuWindowFrameFv(MenuWindowFrame *this,short param_2)
{
  if (this != 0) {
    this->f_8 /*u8 **/ = __vt__15MenuWindowFrame;
    (**(code **)(this->f_8 /*int **/ + 0x1c))();
    __dt__9MenuFrameFv(this + 0xa0,0xffffffffffffffff);
    __dt__11MenuPolygonFv(this + 0x1c,0xffffffffffffffff);
    __dt__16MenuWindowObjectFv(this,0);
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

// JP: 0x002876e0  Create__15MenuWindowFrameFP10MenuWindow  size 0x150
// MenuWindowFrame::Create(MenuWindow*)
void Create__15MenuWindowFrameFP10MenuWindow(MenuWindowFrame *this,u32 menuWindow)
{
  if (-1 < (long)((ulong)this->f_12 /*u8 **/ << 0x3b)) {
    Create__11MenuPolygonFUcUc(this + 0x1c,0,1);
    (**(code **)(this->f_24 /*int **/ + 0x38))(this + 0x1c,menuWindow);
    SetColor__11MenuPolygonFiUcUcUc(this + 0x1c,0,0x30,0x30,0x60);
    SetColor__11MenuPolygonFiUcUcUc(this + 0x1c,1,0x30,0x30,0x60);
    SetColor__11MenuPolygonFiUcUcUc(this + 0x1c,2,0x20,0x20,0x40);
    SetColor__11MenuPolygonFiUcUcUc(this + 0x1c,3,0x20,0x20,0x40);
    (**(code **)(this->f_a8 /*int **/ + 0x30))(this + 0xa0,menuWindow,this + 0x40);
    this->f_12 /*u8 **/ = this->f_12 /*u8 **/ & 0xef | 0x10;
  }
  this->f_18 /*u32 **/ = menuWindow;
  return;
}

// JP: 0x00287830  SetForm__15MenuWindowFrameFffff  size 0xb8
// MenuWindowFrame::SetForm(float, float, float, float)
void SetForm__15MenuWindowFrameFffff
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

// JP: 0x002878f0  SetColor__15MenuWindowFrameFUcUcUc  size 0x4c
// MenuWindowFrame::SetColor(unsigned char, unsigned char, unsigned char)
void SetColor__15MenuWindowFrameFUcUcUc
               (MenuWindowFrame *this,u8 param_2,u8 param_3,u8 param_4)
{
  (**(code **)(this->f_24 /*int **/ + 0x30))(this + 0x1c,param_2,param_3,param_4);
  return;
}

// JP: 0x00287940  SetAlpha__15MenuWindowFrameFUc  size 0x58
// MenuWindowFrame::SetAlpha(unsigned char)
void SetAlpha__15MenuWindowFrameFUc(MenuWindowFrame *this,u8 param_2)
{
  (**(code **)(this->f_a8 /*int **/ + 0x34))(this + 0xa0,param_2);
  (**(code **)(this->f_24 /*int **/ + 0x2c))(this + 0x1c,param_2);
  return;
}

// JP: 0x002879a0  Update__15MenuWindowFrameFiiUs  size 0x110
// MenuWindowFrame::Update(int, int, unsigned short)
void Update__15MenuWindowFrameFiiUs
               (MenuWindowFrame *this,u32 param_2,u32 param_3,u16 param_4)
{
  u8 bVar1;
  u8 *pbVar2;
  pbVar2 = (u8 *)(this + (m_Env__8VIF1Prim & 1) + 0x10);
  bVar1 = *pbVar2;
  this->f_b0 /*u8 **/ = this->f_b0 /*u8 **/ | bVar1;
  this->f_b1 /*u8 **/ = this->f_b1 /*u8 **/ | bVar1;
  bVar1 = *pbVar2;
  this->f_2c /*u8 **/ = this->f_2c /*u8 **/ | bVar1;
  this->f_2d /*u8 **/ = this->f_2d /*u8 **/ | bVar1;
  (**(code **)(this->f_a8 /*int **/ + 0x14))(this + 0xa0,param_2,param_3,param_4);
  (**(code **)(this->f_24 /*int **/ + 0x14))(this + 0x1c,param_2,param_3,param_4);
  *pbVar2 = *pbVar2 & 0x80;
  return;
}

// JP: 0x00287ab0  Connect__15MenuWindowFrameFP4_QWD  size 0x5c
// MenuWindowFrame::Connect(_QWD*)
void Connect__15MenuWindowFrameFP4_QWD(MenuWindowFrame *this,u32 param_2)
{
  u32 uVar1;
  uVar1 = (**(code **)(this->f_a8 /*int **/ + 0x18))(this + 0xa0,param_2);
  (**(code **)(this->f_24 /*int **/ + 0x18))(this + 0x1c,uVar1);
  return;
}

// JP: 0x00287b10  Destroy__15MenuWindowFrameFv  size 0x4c
// MenuWindowFrame::Destroy()
void Destroy__15MenuWindowFrameFv(MenuWindowFrame *this)
{
  (**(code **)(this->f_a8 /*int **/ + 0x1c))();
  (**(code **)(this->f_24 /*int **/ + 0x1c))();
  return;
}

// JP: 0x00287b60  Clear__15MenuWindowFrameFv  size 0x60
// MenuWindowFrame::Clear()
void Clear__15MenuWindowFrameFv(MenuWindowFrame *this)
{
  Clear__7MenuObjFv(this);
  this->f_18 /*u32 **/ = 0;
  (**(code **)(this->f_a8 /*int **/ + 0x20))();
  (**(code **)(this->f_24 /*int **/ + 0x20))();
  return;
}
