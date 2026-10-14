/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x0027fda0  __ct__8FontItemFv  size 0x5c
// FontItem::FontItem()
int __ct__8FontItemFv(FontItem *this)
{
  __ct__8MenuItemFv(this);
  this->vptr = __vt__8FontItem;
  this->packet = 0x4054c4;
  __ct__8MenuIconFv(this + 0x68);
  return this;
}

// JP: 0x0027fe00  __dt__8FontItemFv  size 0x94
// FontItem::~FontItem()
int __dt__8FontItemFv(FontItem *this,short param_2)
{
  if (this != 0) {
    this->vptr = __vt__8FontItem;
    this->packet = 0x4054c4;
    __dt__8MenuIconFv(this + 0x68,0xffffffffffffffff);
    __dt__8MenuItemFv(this,0);
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

// JP: 0x0027fea0  DeleteString__8FontItemFv  size 0x94
// FontItem::DeleteString()
void DeleteString__8FontItemFv(FontItem *this)
{
  if ((this->string != 0) && ((this->fflags3 & 1) != 0)) {
    __dla__FPv(this->string);
  }
  this->string = 0;
  this->fflags3 = this->fflags3 & 0xfe;
  this->fflags3 = this->fflags3 & 0xfd;
  return;
}

// JP: 0x0027ff40  GetRealWidth__8FontItemCFv  size 0x1ac
// FontItem::GetRealWidth() const
/* WARNING: Removing unreachable block (ram,0x00280048) */
uint GetRealWidth__8FontItemCFv(FontItem *this)
{
  uint uVar1;
  u8 bVar2;
  float fVar3;
  u32 *puStack_14;
  int iStack_10;
  iStack_10 = this;
  __ct__4FontFUc(&puStack_14,this->fflags & 7);
  uVar1 = (uint)*(u8 *)*puStack_14;
  if ((long)((ulong)*(u8 *)(iStack_10 + 0x5e) << 0x39) < 0) {
    bVar2 = *(u8 *)(iStack_10 + 0x5e) & 7;
    if (bVar2 == 1) {
      uVar1 = uVar1 + (uint)(((ulong)*(u8 *)(iStack_10 + 0x5e) << 0x3a) >> 0x3d) & 0xff;
    }
    else if (bVar2 == 2) {
      uVar1 = uVar1 + (uint)(((ulong)*(u8 *)(iStack_10 + 0x5e) << 0x3a) >> 0x3d) * 2 & 0xff;
    }
  }
  if ((long)((ulong)*(u8 *)(iStack_10 + 0x58) << 0x3b) < 0) {
    fVar3 = (float)uVar1 * 0.8;
    if (2.1474836e+09 <= fVar3) {
      fVar3 = fVar3 - 2.1474836e+09;
    }
    uVar1 = (int)fVar3 & 0xff;
  }
  bVar2 = *(u8 *)(iStack_10 + 0x5a);
  __dt__4FontFv(&puStack_14,0xffffffffffffffff);
  return uVar1 + bVar2 & 0xff;
}

// JP: 0x002800f0  GetRealHeight__8FontItemCFv  size 0x10c
// FontItem::GetRealHeight() const
uint GetRealHeight__8FontItemCFv(FontItem *this)
{
  u8 bVar1;
  uint uVar2;
  int *piStack_14;
  int iStack_10;
  iStack_10 = this;
  __ct__4FontFUc(&piStack_14,this->fflags & 7);
  uVar2 = (uint)*(u8 *)(*piStack_14 + 1) + (uint)*(u8 *)(iStack_10 + 0x5b) & 0xff;
  if ((long)((ulong)*(u8 *)(iStack_10 + 0x5e) << 0x39) < 0) {
    bVar1 = *(u8 *)(iStack_10 + 0x5e) & 7;
    if (bVar1 == 1) {
      uVar2 = uVar2 + (uint)(((ulong)*(u8 *)(iStack_10 + 0x5e) << 0x3a) >> 0x3d) & 0xff;
    }
    else if (bVar1 == 2) {
      uVar2 = uVar2 + (uint)(((ulong)*(u8 *)(iStack_10 + 0x5e) << 0x3a) >> 0x3d) * 2 & 0xff;
    }
  }
  __dt__4FontFv(&piStack_14,0xffffffffffffffff);
  return uVar2;
}

// JP: 0x00280200  GetOrderInfo__8FontItemFP9OrderInfo  size 0x24c
// FontItem::GetOrderInfo(OrderInfo*)
void * GetOrderInfo__8FontItemFP9OrderInfo(FontItem *this,short *param_2)
{
  void *pvVar1;
  short sVar2;
  u8 bVar3;
  pvVar1 = memset(param_2,0,0xc);
  if ((long)((ulong)this->fflags2 << 0x39) < 0) {
    bVar3 = this->fflags2 & 7;
    if (bVar3 == 1) {
      bVar3 = this->fflags2;
      param_2[1] = (u16)(((ulong)bVar3 << 0x3a) >> 0x3d);
      *param_2 = (short)(((ulong)bVar3 & 0x3f) >> 3);
    }
    else {
      if (bVar3 != 3) {
        if (bVar3 != 2) goto LAB_00280350;
        param_2[2] = (u16)(((ulong)this->fflags2 << 0x3a) >> 0x3d);
      }
      sVar2 = (u16)(((ulong)this->fflags2 << 0x3a) >> 0x3d) << 1;
      param_2[1] = sVar2;
      *param_2 = sVar2;
    }
  }
  else if ((this->fflags2 & 7) == 3) {
    param_2[2] = -(u16)(((ulong)this->fflags2 << 0x3a) >> 0x3d);
  }
LAB_00280350:
  *param_2 = *param_2 + (u16)this->shadow_x;
  param_2[1] = param_2[1] + (u16)this->shadow_y;
  if ((this->fflags2 & 7) == 3) {
    param_2[3] = (short)((uint)(((ulong)this->fflags2 << 0x3a) >> 0x3d) << 1);
  }
  if (((long)((ulong)this->fflags3 << 0x3d) < 0) && (this->owner != 0)) {
    param_2[4] = (short)(int)this->owner->w;
  }
  else {
    param_2[4] = 0x7fff;
  }
  return pvVar1;
}

// JP: 0x00280450  CreateIcon__8FontItemFs  size 0x68
// FontItem::CreateIcon(short)
u64 CreateIcon__8FontItemFs(FontItem *this,u8 param_2)
{
  u64 uVar1;
  uVar1 = Create__8MenuIconFc(this + 0x68,param_2);
  (**(code **)(*(int *)((int)uVar1 + 8) + 0x38))(uVar1,this->owner);
  return uVar1;
}

// JP: 0x002804c0  EnableFontItem__8FontItemFv  size 0x74
// FontItem::EnableFontItem()
void EnableFontItem__8FontItemFv(FontItem *this)
{
  SetCSA__8FontItemFUc(this,0);
  this->pflags = this->pflags & 0xf7 | 8;
  this->pflags = this->pflags & 0xfd | 2;
  return;
}

// JP: 0x00280540  DisableFontItem__8FontItemFv  size 0x6c
// FontItem::DisableFontItem()
void DisableFontItem__8FontItemFv(FontItem *this)
{
  SetCSA__8FontItemFUc(this,2);
  this->pflags = this->pflags & 0xf7;
  this->pflags = this->pflags & 0xfd;
  return;
}

// JP: 0x002805b0  SetCSA__8FontItemFUc  size 0x12c
// FontItem::SetCSA(unsigned char)
void SetCSA__8FontItemFUc(FontItem *this,char param_2)
{
  ulong uVar1;
  this->csa = param_2;
  if (param_2 == '\x01') {
    this->color2_r = 8;
    this->color2_g = 0x18;
    this->color2_b = 0x4c;
  }
  else if (param_2 != '\f') {
    this->color2_r = 0;
    this->color2_g = 0;
    this->color2_b = 0;
  }
  uVar1 = (ulong)this->dirty1 & 0xfffffffffffffffd | 2;
  this->dirty1 = (char)uVar1;
  this->dirty0 =
       this->dirty0 & 0xfd | (u8)((uint)((uVar1 << 0x3e) >> 0x3f) << 1);
  uVar1 = (ulong)this->dirty1 & 0xffffffffffffffef | 0x10;
  this->dirty1 = (char)uVar1;
  this->dirty0 =
       this->dirty0 & 0xef | (u8)((uint)((uVar1 << 0x3b) >> 0x3f) << 4);
  return;
}

// JP: 0x002806e0  SetFontNumber__8FontItemFUc  size 0x80
// FontItem::SetFontNumber(unsigned char)
void SetFontNumber__8FontItemFUc(FontItem *this,u8 param_2)
{
  int *piStack_24;
  int iStack_20;
  u8 bStack_10;
  iStack_20 = this;
  bStack_10 = param_2;
  __ct__4FontFUc(&piStack_24,param_2);
  *(u8 *)(iStack_20 + 0x58) = *(u8 *)(iStack_20 + 0x58) & 0xf8 | bStack_10 & 7;
  *(u8 *)(iStack_20 + 0x59) = *(u8 *)(*piStack_24 + 1);
  __dt__4FontFv(&piStack_24,0xffffffffffffffff);
  return;
}

// JP: 0x00280760  SetOwner__8FontItemFP10MenuWindow  size 0x40
// FontItem::SetOwner(MenuWindow*)
void SetOwner__8FontItemFP10MenuWindow(FontItem *this,u32 menuWindow)
{
  this->owner = menuWindow;
  SetOwner__8MenuIconFP10MenuWindow(this + 0x68,menuWindow);
  return;
}

// JP: 0x002807a0  Destroy__8FontItemFv  size 0x48
// FontItem::Destroy()
void Destroy__8FontItemFv(FontItem *this)
{
  DestroyPacket__10MenuPacketFv(this + 0x3c);
  DeleteString__8FontItemFv(this);
  Destroy__8MenuIconFv(this + 0x68);
  return;
}

// JP: 0x002807f0  Clear__8FontItemFv  size 0xa0
// FontItem::Clear()
void Clear__8FontItemFv(FontItem *this)
{
  Clear__8MenuItemFv(this);
  this->font_draw = 0;
  this->string = 0;
  this->shadow_y = 1;
  this->shadow_x = 1;
  this->csa = 0;
  this->spacing = 0;
  this->color2_r = 0;
  this->color2_g = 0;
  this->color2_b = 0;
  this->fflags = 0x18;
  this->fflags2 = 9;
  this->fflags3 = 0x1c;
  return;
}

// JP: 0x00280890  @60@__dt__8FontItemFv  size 0x8
// @60@__dt__8FontItemFv
u32 * _60___dt__8FontItemFv(FontItem *this,short param_2)
{
  u32 *puVar1;
  puVar1 = this + -0xf;
  if (puVar1 != (u32 *)0x0) {
    this[-0xd] = __vt__8FontItem;
    *this = 0x4054c4;
    __dt__8MenuIconFv(this + 0xb,0xffffffffffffffff);
    __dt__8MenuItemFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}
