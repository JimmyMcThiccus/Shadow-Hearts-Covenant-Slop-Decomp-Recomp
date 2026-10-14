/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x00273dc0  __ct__8MenuItemFv  size 0x5c
// MenuItem::MenuItem()
int __ct__8MenuItemFv(MenuItem *this)
{
  __ct__9MenuPlaceFv(this);
  __ct__10MenuPacketFv(this + 0x3c);
  this->vptr = __vt__8MenuItem;
  this->packet = 0x405154;
  return this;
}

// JP: 0x00273e20  __dt__8MenuItemFv  size 0x94
// MenuItem::~MenuItem()
int __dt__8MenuItemFv(MenuItem *this,short param_2)
{
  if (this != 0) {
    this->vptr = __vt__8MenuItem;
    this->packet = 0x405154;
    __dt__10MenuPacketFv(this + 0x3c,0);
    __dt__9MenuPlaceFv(this,0);
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

// JP: 0x00273ec0  SetBlink__8MenuItemFUcUc  size 0x58
// MenuItem::SetBlink(unsigned char, unsigned char)
void SetBlink__8MenuItemFUcUc(MenuItem *this,u8 param_2,u8 param_3)
{
  this->blink_period = param_2;
  this->blink_base = param_3;
  this->flags = this->flags & 0xfd | 2;
  return;
}

// JP: 0x00273f20  CleanPacket__8MenuItemFv  size 0xe8
// MenuItem::CleanPacket()
void CleanPacket__8MenuItemFv(MenuItem *this)
{
  int iVar1;
  u8 *pbVar2;
  iVar1 = (m_Env__8VIF1Prim & 1) + 1;
  if ((((ulong)this->pktflags & 0x1f) >> 3 & (long)iVar1) != 0) {
    memset(*(void **)(this + (m_Env__8VIF1Prim & 1) * 4 + 0x40),0,
           (long)(int)((uint)this->qwc << 4));
    this->pktflags =
         this->pktflags & 0xe7 |
         (u8)(((uint)(((ulong)this->pktflags << 0x3b) >> 0x3e) - iVar1 & 3) << 3);
    pbVar2 = (u8 *)(this + (m_Env__8VIF1Prim & 1) + 0x10);
    *pbVar2 = *pbVar2 | 0x3f;
  }
  return;
}

// JP: 0x00274010  SetAlpha__8MenuItemFUc  size 0x70
// MenuItem::SetAlpha(unsigned char)
void SetAlpha__8MenuItemFUc(MenuItem *this,u8 param_2)
{
  ulong uVar1;
  this->a = param_2;
  uVar1 = (ulong)this->dirty1 & 0xffffffffffffffef | 0x10;
  this->dirty1 = (char)uVar1;
  this->dirty0 =
       this->dirty0 & 0xef | (u8)((uint)((uVar1 << 0x3b) >> 0x3f) << 4);
  return;
}

// JP: 0x00274080  SetBright__8MenuItemFf  size 0x80
// MenuItem::SetBright(float)
void SetBright__8MenuItemFf(u32 param_1,int this)
{
  ulong uVar1;
  SetBright__7MenuObjFP7_rgba32f(param_1,this + 0x4c);
  uVar1 = (ulong)this->dirty1 & 0xffffffffffffffef | 0x10;
  this->dirty1 = (char)uVar1;
  this->dirty0 =
       this->dirty0 & 0xef | (u8)((uint)((uVar1 << 0x3b) >> 0x3f) << 4);
  return;
}

// JP: 0x00274100  AllotPacket__8MenuItemFP4_QWDP4_QWD  size 0x64
// MenuItem::AllotPacket(_QWD*, _QWD*)
void AllotPacket__8MenuItemFP4_QWDP4_QWD(MenuItem *this,u32 param_2,u32 param_3)
{
  SetPacket__10MenuPacketFUsP4_QWDP4_QWD
            (this + 0x3c,this->qwc,param_2,param_3);
  this->dirty0 = this->dirty0 | 0x3f;
  this->dirty1 = this->dirty1 | 0x3f;
  return;
}

// JP: 0x00274170  GetAllotCount__8MenuItemFv  size 0x2c
// MenuItem::GetAllotCount()
u16 GetAllotCount__8MenuItemFv(MenuItem *this)
{
  return this->qwc;
}

// JP: 0x002741a0  SetColor__8MenuItemFUcUcUc  size 0x90
// MenuItem::SetColor(unsigned char, unsigned char, unsigned char)
void SetColor__8MenuItemFUcUcUc
               (MenuItem *this,u8 param_2,u8 param_3,u8 param_4)
{
  ulong uVar1;
  this->r = param_2;
  this->g = param_3;
  this->b = param_4;
  uVar1 = (ulong)this->dirty1 & 0xffffffffffffffef | 0x10;
  this->dirty1 = (char)uVar1;
  this->dirty0 =
       this->dirty0 & 0xef | (u8)((uint)((uVar1 << 0x3b) >> 0x3f) << 4);
  return;
}

// JP: 0x00274230  Polling__8MenuItemFv  size 0x178
// MenuItem::Polling()
void Polling__8MenuItemFv(MenuItem *this)
{
  short sVar1;
  if (this->blink_period != '\0') {
    this->blink_phase = this->blink_phase + (short)sm_iPassTime__7MenuObj;
    if ((short)((u16)this->blink_period * 0x14) <= this->blink_phase) {
      this->blink_phase =
           this->blink_phase + (u16)this->blink_period * -0x28;
    }
    sVar1 = this->blink_phase / 0x14;
    if (sVar1 < 0) {
      sVar1 = -sVar1;
    }
    VCALL(this, 0x2c /*SetAlpha*/)
              (this,0x80 - (((int)sVar1 & 0xffU) + (uint)this->blink_base) & 0xff);
  }
  return;
}

// JP: 0x002743b0  Connect__8MenuItemFP4_QWD  size 0x64
// MenuItem::Connect(_QWD*)
void Connect__8MenuItemFP4_QWD(MenuItem *this,u32 param_2)
{
  u32 uStack_10;
  uStack_10 = param_2;
  if (this->attached != 0) {
    uStack_10 = VCALL(this->attached, 0x18 /*Connect*/)
                          (this->attached,param_2);
  }
  ConnectPacket__10MenuPacketFP4_QWD(this + 0x3c,uStack_10);
  return;
}

// JP: 0x00274420  Clear__8MenuItemFv  size 0x78
// MenuItem::Clear()
void Clear__8MenuItemFv(MenuItem *this)
{
  Clear__9MenuPlaceFv(this);
  ClearPacket__10MenuPacketFv(this + 0x3c);
  this->a = 0x80;
  this->b = 0x80;
  this->g = 0x80;
  this->r = 0x80;
  this->blink_phase = 0;
  this->blink_period = 0;
  return;
}

// JP: 0x002744a0  @60@__dt__8MenuItemFv  size 0x8
// @60@__dt__8MenuItemFv
u32 * _60___dt__8MenuItemFv(MenuItem *this,short param_2)
{
  u32 *puVar1;
  puVar1 = this + -0xf;
  if (puVar1 != (u32 *)0x0) {
    this[-0xd] = __vt__8MenuItem;
    *this = 0x405154;
    __dt__10MenuPacketFv(this,0);
    __dt__9MenuPlaceFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}
