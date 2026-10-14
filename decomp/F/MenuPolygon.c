/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x00276640  __ct__11MenuPolygonFv  size 0x90
// MenuPolygon::MenuPolygon()
int __ct__11MenuPolygonFv(MenuPolygon *this)
{
  int iVar1;
  __ct__8MenuItemFv(this);
  this->vptr = __vt__11MenuPolygon;
  this->packet = 0x405254;
  iVar1 = this + 0x74;
  do {
    iVar1 = iVar1 + 4;
  } while (iVar1 != this + 0x80);
  VCALL(this, 0x20 /*Clear*/)();
  return this;
}

// JP: 0x002766d0  __dt__11MenuPolygonFv  size 0x94
// MenuPolygon::~MenuPolygon()
int __dt__11MenuPolygonFv(MenuPolygon *this,short param_2)
{
  if (this != 0) {
    this->vptr = __vt__11MenuPolygon;
    this->packet = 0x405254;
    VCALL(this, 0x1c /*Destroy*/)();
    __dt__8MenuItemFv(this,0);
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

// JP: 0x00276770  Create__11MenuPolygonFUcUc  size 0x158
// MenuPolygon::Create(unsigned char, unsigned char)
u32 Create__11MenuPolygonFUcUc(MenuPolygon *this,char param_2,char param_3)
{
  u32 uVar1;
  if ((long)((ulong)this->flags << 0x3b) < 0) {
    uVar1 = 0;
  }
  else {
    if (param_2 == '\0') {
      this->qwc = 8;
      if (this->uv != 0) {
        __dla__FPv(this->uv);
      }
      this->pflags = this->pflags & 0xbf;
    }
    else {
      this->qwc = 10;
      if (this->uv == 0) {
        uVar1 = __nwa__FUi(0x10);
        this->uv = uVar1;
      }
      this->pflags = this->pflags & 0xbf | 0x40;
    }
    if (param_3 != '\0') {
      CreatePacket__10MenuPacketFUs(this + 0x3c,this->qwc);
    }
    this->flags = this->flags & 0xef | 0x10;
    uVar1 = 1;
  }
  return uVar1;
}

// JP: 0x002768d0  SetRect__11MenuPolygonFv  size 0x18c
// MenuPolygon::SetRect()
void SetRect__11MenuPolygonFv(MenuPolygon *this)
{
  int iVar1;
  u32 uStack_20;
  u32 uStack_1c;
  u32 uStack_18;
  u32 uStack_14;
  uStack_1c = this->vx0;
  uStack_20 = this->vy0;
  uStack_18 = uStack_20;
  uStack_14 = uStack_1c;
  for (iVar1 = 1; iVar1 < 4; iVar1 = iVar1 + 1) {
    if (*(float *)(this + iVar1 * 8 + 0x54) < uStack_14) {
      uStack_14 = *(float *)(this + iVar1 * 8 + 0x54);
    }
    else if (uStack_1c < *(float *)(this + iVar1 * 8 + 0x54)) {
      uStack_1c = *(float *)(this + iVar1 * 8 + 0x54);
    }
    if (*(float *)(this + iVar1 * 8 + 0x58) < uStack_18) {
      uStack_18 = *(float *)(this + iVar1 * 8 + 0x58);
    }
    else if (uStack_20 < *(float *)(this + iVar1 * 8 + 0x58)) {
      uStack_20 = *(float *)(this + iVar1 * 8 + 0x58);
    }
  }
  this->x = uStack_14;
  this->y = uStack_18;
  this->w = uStack_1c - uStack_14;
  this->h = uStack_20 - uStack_18;
  return;
}

// JP: 0x00276a60  SetVertex__11MenuPolygonFiffb  size 0xc4
// MenuPolygon::SetVertex(int, float, float, bool)
void SetVertex__11MenuPolygonFiffb
               (u32 param_1,u32 param_2,int this,int param_4,char param_5)
{
  ulong uVar1;
  *(u32 *)(this + param_4 * 8 + 0x54) = param_1;
  *(u32 *)(this + param_4 * 8 + 0x58) = param_2;
  if (param_5 != '\0') {
    SetRect__11MenuPolygonFv(this);
  }
  uVar1 = (ulong)this->dirty1 & 0xfffffffffffffff7 | 8;
  this->dirty1 = (char)uVar1;
  this->dirty0 =
       this->dirty0 & 0xf7 | (u8)((uint)((uVar1 << 0x3c) >> 0x3f) << 3);
  return;
}

// JP: 0x00276b30  SetUV__11MenuPolygonFUsUsUsUs  size 0xf4
// MenuPolygon::SetUV(unsigned short, unsigned short, unsigned short, unsigned short)
void SetUV__11MenuPolygonFUsUsUsUs
               (MenuPolygon *this,u16 param_2,u16 param_3,u16 param_4,
               u16 param_5)
{
  ulong uVar1;
  if (this->uv != 0) {
    *(u16 *)(this->uv + 4) = param_2;
    *this->uv = param_2;
    *(u16 *)(this->uv + 10) = param_3;
    *(u16 *)(this->uv + 2) = param_3;
    *(u16 *)(this->uv + 0xc) = param_4;
    *(u16 *)(this->uv + 8) = param_4;
    *(u16 *)(this->uv + 0xe) = param_5;
    *(u16 *)(this->uv + 6) = param_5;
    uVar1 = (ulong)this->dirty1 & 0xffffffffffffffdf | 0x20;
    this->dirty1 = (char)uVar1;
    this->dirty0 =
         this->dirty0 & 0xdf | (u8)((uint)((uVar1 << 0x3a) >> 0x3f) << 5);
  }
  return;
}

// JP: 0x00276c30  SetColor__11MenuPolygonFiUcUcUc  size 0xc4
// MenuPolygon::SetColor(int, unsigned char, unsigned char, unsigned char)
void SetColor__11MenuPolygonFiUcUcUc
               (MenuPolygon *this,int param_2,u8 param_3,u8 param_4,u8 param_5)
{
  ulong uVar1;
  u8 *puVar2;
  if (param_2 == 0) {
    puVar2 = (u8 *)(this + 0x4c);
  }
  else {
    puVar2 = (u8 *)(this + (param_2 + -1) * 4 + 0x74);
  }
  *puVar2 = param_3;
  puVar2[1] = param_4;
  puVar2[2] = param_5;
  uVar1 = (ulong)this->dirty1 & 0xffffffffffffffef | 0x10;
  this->dirty1 = (char)uVar1;
  this->dirty0 =
       this->dirty0 & 0xef | (u8)((uint)((uVar1 << 0x3b) >> 0x3f) << 4);
  return;
}

// JP: 0x00276d00  SetPosition__11MenuPolygonFff  size 0x130
// MenuPolygon::SetPosition(float, float)
void SetPosition__11MenuPolygonFff(u32 param_1,u32 param_2,int this)
{
  ulong uVar1;
  float fVar2;
  this->x = param_1;
  this->y = param_2;
  this->vx1 = this->x;
  this->vx0 = this->x;
  fVar2 = this->x + this->w;
  this->vx3 = fVar2;
  this->vx2 = fVar2;
  this->vy2 = this->y;
  this->vy0 = this->y;
  fVar2 = this->y + this->h;
  this->vy3 = fVar2;
  this->vy1 = fVar2;
  uVar1 = (ulong)this->dirty1 & 0xfffffffffffffff7 | 8;
  this->dirty1 = (char)uVar1;
  this->dirty0 =
       this->dirty0 & 0xf7 | (u8)((uint)((uVar1 << 0x3c) >> 0x3f) << 3);
  if (this->attached != 0) {
    VCALL(this, 0x24 /*SetPosition*/)(param_1,param_2);
  }
  return;
}

// JP: 0x00276e30  SetSize__11MenuPolygonFff  size 0x130
// MenuPolygon::SetSize(float, float)
void SetSize__11MenuPolygonFff(u32 param_1,u32 param_2,int this)
{
  ulong uVar1;
  float fVar2;
  this->w = param_1;
  this->h = param_2;
  this->vx1 = this->x;
  this->vx0 = this->x;
  fVar2 = this->x + this->w;
  this->vx3 = fVar2;
  this->vx2 = fVar2;
  this->vy2 = this->y;
  this->vy0 = this->y;
  fVar2 = this->y + this->h;
  this->vy3 = fVar2;
  this->vy1 = fVar2;
  uVar1 = (ulong)this->dirty1 & 0xfffffffffffffff7 | 8;
  this->dirty1 = (char)uVar1;
  this->dirty0 =
       this->dirty0 & 0xf7 | (u8)((uint)((uVar1 << 0x3c) >> 0x3f) << 3);
  if (this->attached != 0) {
    VCALL(this, 0x28 /*SetSize*/)(param_1,param_2);
  }
  return;
}

// JP: 0x00276f60  SetColor__11MenuPolygonFUcUcUc  size 0xf0
// MenuPolygon::SetColor(unsigned char, unsigned char, unsigned char)
void SetColor__11MenuPolygonFUcUcUc
               (MenuPolygon *this,u8 param_2,u8 param_3,u8 param_4)
{
  ulong uVar1;
  this->col3 = param_2;
  this->col2 = param_2;
  this->col1 = param_2;
  this->r = param_2;
  this->f_7d /*u8 **/ = param_3;
  this->f_79 /*u8 **/ = param_3;
  this->f_75 /*u8 **/ = param_3;
  this->g = param_3;
  this->f_7e /*u8 **/ = param_4;
  this->f_7a /*u8 **/ = param_4;
  this->f_76 /*u8 **/ = param_4;
  this->b = param_4;
  uVar1 = (ulong)this->dirty1 & 0xffffffffffffffef | 0x10;
  this->dirty1 = (char)uVar1;
  this->dirty0 =
       this->dirty0 & 0xef | (u8)((uint)((uVar1 << 0x3b) >> 0x3f) << 4);
  return;
}

// JP: 0x00277050  SetAlpha__11MenuPolygonFUc  size 0x90
// MenuPolygon::SetAlpha(unsigned char)
void SetAlpha__11MenuPolygonFUc(MenuPolygon *this,u8 param_2)
{
  ulong uVar1;
  this->f_7f /*u8 **/ = param_2;
  this->f_7b /*u8 **/ = param_2;
  this->f_77 /*u8 **/ = param_2;
  this->a = param_2;
  uVar1 = (ulong)this->dirty1 & 0xffffffffffffffef | 0x10;
  this->dirty1 = (char)uVar1;
  this->dirty0 =
       this->dirty0 & 0xef | (u8)((uint)((uVar1 << 0x3b) >> 0x3f) << 4);
  return;
}

// JP: 0x002770e0  SetBright__11MenuPolygonFf  size 0xc4
// MenuPolygon::SetBright(float)
void SetBright__11MenuPolygonFf(u32 param_1,int this)
{
  ulong uVar1;
  int iVar2;
  SetBright__7MenuObjFP7_rgba32f(param_1,this + 0x4c);
  for (iVar2 = 0; iVar2 < 3; iVar2 = iVar2 + 1) {
    SetBright__7MenuObjFP7_rgba32f(param_1,this + iVar2 * 4 + 0x74);
  }
  uVar1 = (ulong)this->dirty1 & 0xffffffffffffffef | 0x10;
  this->dirty1 = (char)uVar1;
  this->dirty0 =
       this->dirty0 & 0xef | (u8)((uint)((uVar1 << 0x3b) >> 0x3f) << 4);
  return;
}

// JP: 0x002771b0  Update__11MenuPolygonFiiUs  size 0x518
// MenuPolygon::Update(int, int, unsigned short)
void Update__11MenuPolygonFiiUs(MenuPolygon *this,short param_2,short param_3,u16 param_4)
{
  u32 *puVar1;
  u8 auVar2 [16];
  u8 in_zero_qw [16];
  u16 uVar3;
  int iVar4;
  u64 in_v1_udw;
  u8 auVar5 [16];
  u8 auVar6 [16];
  u8 auVar7 [16];
  u64 in_a0_udw;
  u32 *puVar8;
  uint uVar9;
  u8 *puVar10;
  ulong *puVar11;
  u8 *pbVar12;
  u16 *puVar13;
  u16 *puStack_4c;
  puVar1 = *(u32 **)(this + (m_Env__8VIF1Prim & 1) * 4 + 0x40);
  CleanPacket__8MenuItemFv(this);
  pbVar12 = (u8 *)(this + (m_Env__8VIF1Prim & 1) + 0x10);
  if ((*pbVar12 & 1) != 0) {
    if (this->qwc == 8) {
      *puVar1 = 0x10000006;
      puVar1[3] = 0x50000006;
      auVar5._8_8_ = in_v1_udw;
      auVar5._0_8_ = 0x9400000000008001;
      auVar6 = _pcpyld(in_zero_qw,auVar5);
      *(long *)(puVar1 + 4) = auVar6._0_8_;
      in_v1_udw = auVar6._8_8_;
      *(u64 *)(puVar1 + 6) = 0x5151d1d10;
      *(u64 *)(puVar1 + 8) = 0x14c;
    }
    else {
      *puVar1 = &DAT_10000008;
      puVar1[3] = 0x50000008;
      auVar6._8_8_ = in_v1_udw;
      auVar6._0_8_ = 0xe400000000008001;
      auVar6 = _pcpyld(in_zero_qw,auVar6);
      *(long *)(puVar1 + 4) = auVar6._0_8_;
      in_v1_udw = auVar6._8_8_;
      *(u64 *)(puVar1 + 6) = 0xf531531d31d310;
      *(u64 *)(puVar1 + 8) = 0x15c;
    }
  }
  if ((long)((ulong)*pbVar12 << 0x3b) < 0) {
    iVar4 = 3;
    if (this->qwc == 8) {
      iVar4 = 2;
    }
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
    puVar8 = puVar1 + 10 + iVar4 * 2;
    puVar10 = (u8 *)(this + 0x74);
    for (uVar3 = 0; uVar3 < 3; uVar3 = uVar3 + 1) {
      *(u8 *)puVar8 = *puVar10;
      *(u8 *)((int)puVar8 + 1) = puVar10[1];
      *(u8 *)((int)puVar8 + 2) = puVar10[2];
      if ((long)((ulong)this->pflags << 0x3a) < 0) {
        *(char *)((int)puVar8 + 3) = (char)((uint)(u8)puVar10[3] * (uint)param_4 >> 0xf);
      }
      else {
        *(u8 *)((int)puVar8 + 3) = puVar10[3];
      }
      puVar8 = puVar8 + iVar4 * 2;
      puVar10 = puVar10 + 4;
    }
  }
  if ((this->qwc == 10) && ((long)((ulong)*pbVar12 << 0x3a) < 0)) {
    puStack_4c = (u16 *)(puVar1 + 0xc);
    puVar13 = this->uv;
    for (uVar3 = 0; uVar3 < 4; uVar3 = uVar3 + 1) {
      *puStack_4c = *puStack_4c & 0xc000 | (*puVar13 & 0x3ff) << 4;
      puStack_4c[1] = puStack_4c[1] & 0xc000 | (puVar13[1] & 0x3ff) << 4;
      puStack_4c = puStack_4c + 0xc;
      puVar13 = puVar13 + 2;
    }
  }
  if ((long)((ulong)*pbVar12 << 0x3c) < 0) {
    if (this->qwc == 8) {
      puVar11 = (ulong *)(puVar1 + 0xc);
      iVar4 = 2;
    }
    else {
      puVar11 = (ulong *)(puVar1 + 0xe);
      iVar4 = 3;
    }
    for (uVar9 = 0; uVar9 < 4; uVar9 = uVar9 + 1 & 0xffff) {
      *(short *)puVar11 = (short)(int)*(float *)(this + uVar9 * 8 + 0x54) * 0x10 + param_2;
      *(short *)((int)puVar11 + 2) =
           (short)(int)*(float *)(this + uVar9 * 8 + 0x58) * 0x10 + param_3;
      auVar7._8_8_ = in_v1_udw;
      auVar7._0_8_ = 0xffffffff;
      auVar2._8_8_ = in_a0_udw;
      auVar2._0_8_ = 0xffffffffffffffff;
      auVar6 = _pcpyld(auVar2,auVar7);
      in_v1_udw = auVar6._8_8_;
      *puVar11 = *puVar11 & auVar6._0_8_ | 0x100000000;
      puVar11 = puVar11 + iVar4;
    }
  }
  *pbVar12 = *pbVar12 & 0x80;
  return;
}

// JP: 0x002776d0  Destroy__11MenuPolygonFv  size 0x58
// MenuPolygon::Destroy()
void Destroy__11MenuPolygonFv(MenuPolygon *this)
{
  DestroyPacket__10MenuPacketFv(this + 0x3c);
  if (this->uv != 0) {
    __dla__FPv(this->uv);
    this->uv = 0;
  }
  return;
}

// JP: 0x00277730  Clear__11MenuPolygonFv  size 0xd8
// MenuPolygon::Clear()
void * Clear__11MenuPolygonFv(MenuPolygon *this)
{
  void *pvVar1;
  Clear__8MenuItemFv(this);
  this->uv = 0;
  this->f_7f /*u8 **/ = 0x80;
  this->f_7b /*u8 **/ = 0x80;
  this->f_77 /*u8 **/ = 0x80;
  this->f_7e /*u8 **/ = 0x80;
  this->f_7a /*u8 **/ = 0x80;
  this->f_76 /*u8 **/ = 0x80;
  this->f_7d /*u8 **/ = 0x80;
  this->f_79 /*u8 **/ = 0x80;
  this->f_75 /*u8 **/ = 0x80;
  this->col3 = 0x80;
  this->col2 = 0x80;
  this->col1 = 0x80;
  pvVar1 = memset((void *)(this + 0x54),0,0x20);
  return pvVar1;
}

// JP: 0x00277810  @60@__dt__11MenuPolygonFv  size 0x8
// @60@__dt__11MenuPolygonFv
u32 * _60___dt__11MenuPolygonFv(MenuPolygon *this,short param_2)
{
  u32 *puVar1;
  puVar1 = this + -0xf;
  if (puVar1 != (u32 *)0x0) {
    this[-0xd] = __vt__11MenuPolygon;
    *this = 0x405254;
    (**(code **)(this[-0xd] + 0x1c))();
    __dt__8MenuItemFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}
