/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x00265630  __ct__10MenuPacketFv  size 0x3c
// MenuPacket::MenuPacket()
u32 * __ct__10MenuPacketFv(MenuPacket *this)
{
  *this = __vt__10MenuPacket;
  ClearPacket__10MenuPacketFv(this);
  return this;
}

// JP: 0x00265670  __dt__10MenuPacketFv  size 0x6c
// MenuPacket::~MenuPacket()
u32 * __dt__10MenuPacketFv(MenuPacket *this,short param_2)
{
  if (this != (u32 *)0x0) {
    *this = __vt__10MenuPacket;
    DestroyPacket__10MenuPacketFv(this);
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

// JP: 0x002656e0  ConnectPacket__10MenuPacketFP4_QWD  size 0x7c
// MenuPacket::ConnectPacket(_QWD*)
int ConnectPacket__10MenuPacketFP4_QWD(MenuPacket *this,u32 *param_2)
{
  *param_2 = 0x20000000;
  param_2[1] = *(u32 *)(this + (m_Env__8VIF1Prim & 1) * 4 + 4);
  param_2[3] = 0;
  return *(int *)(this + (m_Env__8VIF1Prim & 1) * 4 + 4) +
         (this->qwc - 1) * 0x10;
}

// JP: 0x00265760  CreatePacket__10MenuPacketFUs  size 0x100
// MenuPacket::CreatePacket(unsigned short)
void CreatePacket__10MenuPacketFUs(MenuPacket *this,u16 param_2)
{
  u32 uVar1;
  u64 uVar2;
  if ((this->pflags & 1) == 0) {
    uVar2 = __nwa__FUi((uint)param_2 * 0x20 + 0x10);
    uVar1 = __construct_new_array(uVar2,0x224b30,0,0x10,(uint)param_2 << 1);
    this->pkt0 = uVar1;
    this->pkt1 = this->pkt0 + (uint)param_2 * 0x10;
    memset(this->pkt0,0,(long)(int)((uint)param_2 << 5));
    this->qwc = param_2;
    this->pflags = this->pflags & 0xfe | 1;
  }
  return;
}

// JP: 0x00265860  CreateSinglePacket__10MenuPacketFUs  size 0x110
// MenuPacket::CreateSinglePacket(unsigned short)
void CreateSinglePacket__10MenuPacketFUs(MenuPacket *this,u16 param_2)
{
  u32 uVar1;
  u64 uVar2;
  ulong uVar3;
  if ((this->pflags & 1) == 0) {
    uVar2 = __nwa__FUi((uint)param_2 * 0x10 + 0x10);
    uVar1 = __construct_new_array(uVar2,0x224b30,0,0x10,param_2);
    this->pkt0 = uVar1;
    this->pkt1 = this->pkt0;
    memset(this->pkt0,0,(long)(int)((uint)param_2 << 4));
    this->qwc = param_2;
    uVar3 = (ulong)this->pflags & 0xffffffffffffffdf | 0x20;
    this->pflags = (char)uVar3;
    this->pflags = this->pflags & 0xfe | (u8)((uVar3 << 0x3a) >> 0x3f);
  }
  return;
}

// JP: 0x00265970  SetPacket__10MenuPacketFUsP4_QWDP4_QWD  size 0x84
// MenuPacket::SetPacket(unsigned short, _QWD*, _QWD*)
void SetPacket__10MenuPacketFUsP4_QWDP4_QWD
               (MenuPacket *this,u16 param_2,u32 param_3,u32 param_4)
{
  this->pkt0 = param_3;
  this->pkt1 = param_4;
  this->qwc = param_2;
  this->pflags = this->pflags & 0xfe;
  this->pflags = this->pflags & 0xe7 | 0x18;
  return;
}

// JP: 0x00265a00  DestroyPacket__10MenuPacketFv  size 0x74
// MenuPacket::DestroyPacket()
void DestroyPacket__10MenuPacketFv(MenuPacket *this)
{
  if (((this->pflags & 1) != 0) && (this->pkt0 != 0)) {
    if (this->pkt0 != 0) {
      __dla__FPv(this->pkt0 + -0x10);
    }
    ClearPacket__10MenuPacketFv(this);
  }
  return;
}

// JP: 0x00265a80  ClearPacket__10MenuPacketFv  size 0x34
// MenuPacket::ClearPacket()
void ClearPacket__10MenuPacketFv(MenuPacket *this)
{
  this->pkt1 = 0;
  this->pkt0 = 0;
  this->qwc = 0;
  this->pflags = 0;
  return;
}
