/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x00266140  __ct__10MenuSpriteFv  size 0x60
// MenuSprite::MenuSprite()
int __ct__10MenuSpriteFv(MenuSprite *this)
{
  __ct__8MenuItemFv(this);
  this->vptr = __vt__10MenuSprite;
  this->packet = 0x405004;
  VCALL(this, 0x20 /*Clear*/)();
  return this;
}

// JP: 0x002661a0  __dt__10MenuSpriteFv  size 0x94
// MenuSprite::~MenuSprite()
int __dt__10MenuSpriteFv(MenuSprite *this,short param_2)
{
  if (this != 0) {
    this->vptr = __vt__10MenuSprite;
    this->packet = 0x405004;
    VCALL(this, 0x1c /*Destroy*/)();
    __dt__8MenuItemFv(this,0);
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

// JP: 0x00266240  Create__10MenuSpriteFUc  size 0x68
// MenuSprite::Create(unsigned char)
void Create__10MenuSpriteFUc(MenuSprite *this,char param_2)
{
  if (param_2 != '\0') {
    CreatePacket__10MenuPacketFUs(this + 0x3c,this->qwc);
  }
  this->dirty0 = this->dirty0 | 0x3f;
  this->dirty1 = this->dirty1 | 0x3f;
  return;
}

// JP: 0x002662b0  SetUV__10MenuSpriteFUsUsUsUs  size 0xa0
// MenuSprite::SetUV(unsigned short, unsigned short, unsigned short, unsigned short)
void SetUV__10MenuSpriteFUsUsUsUs
               (MenuSprite *this,u16 param_2,u16 param_3,u16 param_4,
               u16 param_5)
{
  ulong uVar1;
  this->u0 = param_2;
  this->v0 = param_3;
  this->u1 = param_4;
  this->v1 = param_5;
  uVar1 = (ulong)this->dirty1 & 0xffffffffffffffdf | 0x20;
  this->dirty1 = (char)uVar1;
  this->dirty0 =
       this->dirty0 & 0xdf | (u8)((uint)((uVar1 << 0x3a) >> 0x3f) << 5);
  return;
}

// JP: 0x00266350  SetScale__10MenuSpriteFf  size 0xc8
// MenuSprite::SetScale(float)
void SetScale__10MenuSpriteFf(float param_1,int this)
{
  ulong uVar1;
  this->w = this->w + param_1;
  this->h = this->h + param_1;
  this->x = this->x - param_1 * 0.5;
  this->y = this->y - param_1 * 0.5;
  uVar1 = (ulong)this->dirty1 & 0xfffffffffffffff7 | 8;
  this->dirty1 = (char)uVar1;
  this->dirty0 =
       this->dirty0 & 0xf7 | (u8)((uint)((uVar1 << 0x3c) >> 0x3f) << 3);
  return;
}

// JP: 0x00266420  Update__10MenuSpriteFiiUs  size 0x4d4
// MenuSprite::Update(int, int, unsigned short)
void Update__10MenuSpriteFiiUs(MenuSprite *this,u32 param_2,u32 param_3,u16 param_4)
{
  u32 *puVar1;
  u8 auVar2 [16];
  u16 uVar3;
  u64 in_v1_udw;
  u8 auVar4 [16];
  u8 auVar5 [16];
  u8 auVar6 [16];
  u64 in_a0_udw;
  u16 *puVar7;
  ulong *puVar8;
  u8 *pbVar9;
  ulong *puVar10;
  CleanPacket__8MenuItemFv(this);
  puVar1 = *(u32 **)(this + (m_Env__8VIF1Prim & 1) * 4 + 0x40);
  pbVar9 = (u8 *)(this + (m_Env__8VIF1Prim & 1) + 0x10);
  if ((*pbVar9 & 1) != 0) {
    *puVar1 = &DAT_10000004;
    puVar1[3] = 0x50000004;
    *(u64 *)(puVar1 + 4) = 0x6400000000008001;
  }
  if ((long)((ulong)*pbVar9 << 0x3e) < 0) {
    if ((long)((ulong)this->pflags << 0x39) < 0) {
      *(u64 *)(puVar1 + 6) = 0x53d310;
      *(u64 *)(puVar1 + 8) = 0x156;
    }
    else {
      *(u64 *)(puVar1 + 6) = 0x5fdf10;
      *(u64 *)(puVar1 + 8) = 0x146;
    }
  }
  if ((long)((ulong)*pbVar9 << 0x3b) < 0) {
    *(u8 *)(puVar1 + 10) = this->r;
    *(u8 *)((int)puVar1 + 0x29) = this->g;
    *(u8 *)((int)puVar1 + 0x2a) = this->b;
    if ((long)((ulong)this->pflags << 0x3a) < 0) {
      *(char *)((int)puVar1 + 0x2b) = (char)((uint)this->a * (uint)param_4 >> 0xf)
      ;
    }
    else {
      *(u8 *)((int)puVar1 + 0x2b) = this->a;
    }
    puVar1[0xb] = 0;
  }
  if ((this->qwc == 6) && ((long)((ulong)*pbVar9 << 0x3a) < 0)) {
    puVar7 = (u16 *)(puVar1 + 0xc);
    uVar3 = (u16)(((ulong)this->flags << 0x36) >> 0x30);
    *puVar7 = *puVar7 & 0xc000 | this->u0 * 0x10 + (uVar3 >> 0xc) & 0x3fff;
    *(u16 *)((int)puVar1 + 0x32) =
         *(u16 *)((int)puVar1 + 0x32) & 0xc000 |
         this->v0 * 0x10 + (uVar3 >> 0xc) & 0x3fff;
    if ((*puVar7 & 0x3fff) == 0) {
      *puVar7 = *puVar7 & 0xc000 | 1;
    }
    *(u16 *)(puVar1 + 0x10) =
         *(u16 *)(puVar1 + 0x10) & 0xc000 |
         this->u1 * 0x10 + (uVar3 >> 0xc) & 0x3fff;
    *(u16 *)((int)puVar1 + 0x42) =
         *(u16 *)((int)puVar1 + 0x42) & 0xc000 |
         this->v1 * 0x10 + (uVar3 >> 0xc) & 0x3fff;
  }
  if ((long)((ulong)*pbVar9 << 0x3c) < 0) {
    puVar8 = (ulong *)(puVar1 + 0xe);
    puVar10 = (ulong *)(puVar1 + 0x12);
    *(short *)puVar8 = (short)param_2 + (short)(int)this->x * 0x10;
    *(short *)((int)puVar1 + 0x3a) = (short)param_3 + (short)(int)this->y * 0x10;
    auVar4._8_8_ = in_v1_udw;
    auVar4._0_8_ = 0xffffffff;
    auVar5._8_8_ = in_a0_udw;
    auVar5._0_8_ = 0xffffffffffffffff;
    auVar5 = _pcpyld(auVar5,auVar4);
    auVar6._8_8_ = auVar5._8_8_;
    *puVar8 = *puVar8 & auVar5._0_8_ | 0x100000000;
    *(short *)puVar10 = (short)*puVar8 + (short)(int)this->w * 0x10;
    *(short *)((int)puVar1 + 0x4a) =
         *(short *)((int)puVar1 + 0x3a) + (short)(int)this->h * 0x10;
    auVar6._0_8_ = 0xffffffff;
    auVar2._8_8_ = in_a0_udw;
    auVar2._0_8_ = 0xffffffffffffffff;
    auVar5 = _pcpyld(auVar2,auVar6);
    *puVar10 = *puVar10 & auVar5._0_8_ | 0x100000000;
  }
  *pbVar9 = *pbVar9 & 0x80;
  if (this->linked != 0) {
    if (*(char *)(this->linked + (m_Env__8VIF1Prim & 1) + 0x10) != '\0') {
      VCALL(this->linked, 0x14 /*Update*/)
                (this->linked,param_2,param_3,0);
    }
  }
  return;
}

// JP: 0x00266900  Connect__10MenuSpriteFP4_QWD  size 0x94
// MenuSprite::Connect(_QWD*)
void Connect__10MenuSpriteFP4_QWD(MenuSprite *this,u32 param_2)
{
  u32 uStack_10;
  uStack_10 = param_2;
  if (this->attached != 0) {
    uStack_10 = VCALL(this->attached, 0x18 /*Connect*/)
                          (this->attached,param_2);
  }
  if (this->linked != 0) {
    uStack_10 = VCALL(this->linked, 0x18 /*Connect*/)
                          (this->linked,uStack_10);
  }
  ConnectPacket__10MenuPacketFP4_QWD(this + 0x3c,uStack_10);
  return;
}

// JP: 0x002669a0  Destroy__10MenuSpriteFv  size 0x84
// MenuSprite::Destroy()
void Destroy__10MenuSpriteFv(MenuSprite *this)
{
  int iVar1;
  DestroyPacket__10MenuPacketFv(this + 0x3c);
  if ((this->linked != 0) && ((long)((ulong)this->flags << 0x3a) < 0)) {
    iVar1 = this->linked;
    if (iVar1 != 0) {
      VCALL(iVar1, 0x8 /*dtor*/)(iVar1,1);
    }
  }
  return;
}

// JP: 0x00266a30  Clear__10MenuSpriteFv  size 0x78
// MenuSprite::Clear()
void * Clear__10MenuSpriteFv(MenuSprite *this)
{
  void *pvVar1;
  Clear__8MenuItemFv(this);
  this->linked = 0;
  pvVar1 = memset((void *)(this + 0x54),0,8);
  this->qwc = 6;
  this->flags = this->flags & 0xfc3f | 0x200;
  return pvVar1;
}

// JP: 0x00266ab0  @60@__dt__10MenuSpriteFv  size 0x8
// @60@__dt__10MenuSpriteFv
u32 * _60___dt__10MenuSpriteFv(MenuSprite *this,short param_2)
{
  u32 *puVar1;
  puVar1 = this + -0xf;
  if (puVar1 != (u32 *)0x0) {
    this[-0xd] = __vt__10MenuSprite;
    *this = 0x405004;
    (**(code **)(this[-0xd] + 0x1c))();
    __dt__8MenuItemFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}
