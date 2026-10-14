/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x0028d000  __ct__12MenuRegisterFv  size 0x70
// MenuRegister::MenuRegister()
int __ct__12MenuRegisterFv(MenuRegister *this)
{
  __ct__7MenuObjFv(this);
  __ct__10MenuPacketFv(this + 0x18);
  this->f_8 /*u8 **/ = __vt__12MenuRegister;
  this->f_18 /*u32 **/ = 0x405a04;
  (**(code **)(this->f_8 /*int **/ + 0x20))();
  return this;
}

// JP: 0x0028d070  __dt__12MenuRegisterFv  size 0xac
// MenuRegister::~MenuRegister()
int __dt__12MenuRegisterFv(MenuRegister *this,short param_2)
{
  if (this != 0) {
    this->f_8 /*u8 **/ = __vt__12MenuRegister;
    this->f_18 /*u32 **/ = 0x405a04;
    (**(code **)(this->f_8 /*int **/ + 0x1c))();
    __dt__10MenuPacketFv(this + 0x18,0);
    __dt__7MenuObjFv(this,0);
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

// JP: 0x0028d120  SetRegister__12MenuRegisterFiUlUl  size 0xc0
// MenuRegister::SetRegister(int, unsigned long, unsigned long)
void SetRegister__12MenuRegisterFiUlUl
               (MenuRegister *this,int param_2,u64 param_3,u64 param_4)
{
  int iVar1;
  u64 *puVar2;
  puVar2 = (u64 *)
           (*(int *)(this + (m_Env__8VIF1Prim & 1) * 4 + 0x1c) + (param_2 + 2) * 0x10);
  puVar2[1] = param_3;
  *puVar2 = param_4;
  iVar1 = this + (m_Env__8VIF1Prim & 1);
  *(u8 *)(iVar1 + 0x10) = *(u8 *)(iVar1 + 0x10) & 0xbf;
  this = this + (m_Env__8VIF1Prim & 1 ^ 1);
  this->f_10 /*u8 **/ = this->f_10 /*u8 **/ & 0xbf | 0x40;
  return;
}

// JP: 0x0028d1e0  Update__12MenuRegisterFiiUs  size 0x1a0
// MenuRegister::Update(int, int, unsigned short)
void Update__12MenuRegisterFiiUs(MenuRegister *this)
{
  int *piVar1;
  u64 uVar2;
  u32 uVar3;
  u32 uVar4;
  u32 *puVar5;
  int iVar6;
  uint uVar7;
  u64 *puVar8;
  u8 *pbVar9;
  u32 *puVar10;
  uVar7 = (uint)this->f_24 /*u16 **/;
  iVar6 = uVar7 - 3;
  pbVar9 = (u8 *)(this + (m_Env__8VIF1Prim & 1) + 0x10);
  if ((*pbVar9 & 1) != 0) {
    piVar1 = *(int **)(this + (m_Env__8VIF1Prim & 1) * 4 + 0x1c);
    *piVar1 = uVar7 + 0xffffffe;
    piVar1[3] = uVar7 + 0x4ffffffe;
    *(ulong *)(piVar1 + 4) = (long)iVar6 << 0x3c | 0x8001;
    piVar1[6] = 0;
    piVar1[7] = 0;
    for (uVar7 = 0; (int)uVar7 < iVar6; uVar7 = uVar7 + 1) {
      *(ulong *)(piVar1 + 6) = *(ulong *)(piVar1 + 6) | (long)(0xe << ((uVar7 & 7) << 2));
    }
  }
  if ((long)((ulong)*pbVar9 << 0x39) < 0) {
    puVar8 = (u64 *)(*(int *)(this + (m_Env__8VIF1Prim & 1 ^ 1) * 4 + 0x1c) + 0x20);
    puVar5 = (u32 *)(*(int *)(this + (m_Env__8VIF1Prim & 1) * 4 + 0x1c) + 0x20);
    puVar10 = puVar5 + iVar6 * 4;
    for (; puVar5 < puVar10; puVar5 = puVar5 + 4) {
      uVar2 = *puVar8;
      uVar3 = *(u32 *)(puVar8 + 1);
      uVar4 = *(u32 *)((int)puVar8 + 0xc);
      *puVar5 = (int)uVar2;
      puVar5[1] = (int)((ulong)uVar2 >> 0x20);
      puVar5[2] = uVar3;
      puVar5[3] = uVar4;
      puVar8 = puVar8 + 2;
    }
  }
  *pbVar9 = *pbVar9 & 0x80;
  return;
}

// JP: 0x0028d380  Connect__12MenuRegisterFP4_QWD  size 0x34
// MenuRegister::Connect(_QWD*)
void Connect__12MenuRegisterFP4_QWD(MenuRegister *this,u32 param_2)
{
  ConnectPacket__10MenuPacketFP4_QWD(this + 0x18,param_2);
  return;
}

// JP: 0x0028d3c0  Destroy__12MenuRegisterFv  size 0x2c
// MenuRegister::Destroy()
void Destroy__12MenuRegisterFv(MenuRegister *this)
{
  DestroyPacket__10MenuPacketFv(this + 0x18);
  return;
}

// JP: 0x0028d3f0  Clear__12MenuRegisterFv  size 0x38
// MenuRegister::Clear()
void Clear__12MenuRegisterFv(MenuRegister *this)
{
  Clear__7MenuObjFv(this);
  ClearPacket__10MenuPacketFv(this + 0x18);
  return;
}

// JP: 0x0028d430  @24@__dt__12MenuRegisterFv  size 0x8
// @24@__dt__12MenuRegisterFv
u32 * _24___dt__12MenuRegisterFv(MenuRegister *this,short param_2)
{
  u32 *puVar1;
  puVar1 = this + -6;
  if (puVar1 != (u32 *)0x0) {
    this[-4] = __vt__12MenuRegister;
    *this = 0x405a04;
    (**(code **)(this[-4] + 0x1c))();
    __dt__10MenuPacketFv(this,0);
    __dt__7MenuObjFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}
