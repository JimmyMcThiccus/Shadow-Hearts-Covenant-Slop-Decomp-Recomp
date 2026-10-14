/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x00283b70  __ct__14PluralFontItemFv  size 0x4c
// PluralFontItem::PluralFontItem()
int __ct__14PluralFontItemFv(PluralFontItem *this)
{
  __ct__8FontItemFv(this);
  this->vptr = __vt__14PluralFontItem;
  this->packet = 0x4055f4;
  return this;
}

// JP: 0x00283bc0  __dt__14PluralFontItemFv  size 0x84
// PluralFontItem::~PluralFontItem()
int __dt__14PluralFontItemFv(PluralFontItem *this,short param_2)
{
  if (this != 0) {
    this->vptr = __vt__14PluralFontItem;
    this->packet = 0x4055f4;
    __dt__8FontItemFv(this,0);
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

// JP: 0x00283c50  Create__14PluralFontItemFUsUc  size 0x168
// PluralFontItem::Create(unsigned short, unsigned char)
bool Create__14PluralFontItemFUsUc(PluralFontItem *this,short param_2,u8 param_3)
{
  bool bVar1;
  if (param_3 == 2) {
    this->qwc = param_2 * 3 + 0x17;
  }
  else if (param_3 == 1) {
    this->qwc = param_2 * 3 + 0xb;
  }
  else if ((param_3 == 3) || (param_3 == 0)) {
    this->qwc = param_2 * 3 + 5;
  }
  bVar1 = this->qwc != 0;
  if (bVar1) {
    CreatePacket__10MenuPacketFUs(this + 0x3c,this->qwc);
    this->f_74 /*short **/ = param_2;
    this->fflags2 = this->fflags2 & 0xf8 | param_3 & 7;
    SetFontColor__14PluralFontItemFUsUsUcUcUc
              (this,0,this->f_74 /*u16 **/,this->r,
               this->g,this->b);
  }
  return bVar1;
}

// JP: 0x00283dc0  GetFontPacket__14PluralFontItemCFUc  size 0x144
// PluralFontItem::GetFontPacket(unsigned char) const
int GetFontPacket__14PluralFontItemCFUc(PluralFontItem *this,u8 param_2)
{
  int iVar1;
  u8 bVar2;
  bVar2 = this->fflags2 & 7;
  if (bVar2 == 4) {
    iVar1 = *(int *)((uint)param_2 * 4 + this + 0x40) +
            ((uint)this->f_74 /*u16 **/ * 3 + 7) * 0x10;
  }
  else if (bVar2 == 2) {
    iVar1 = *(int *)((uint)param_2 * 4 + this + 0x40) + 0x50;
  }
  else if (bVar2 == 1) {
    iVar1 = *(int *)((uint)param_2 * 4 + this + 0x40) + 0x50;
  }
  else if ((bVar2 == 3) || ((this->fflags2 & 7) == 0)) {
    iVar1 = *(int *)((uint)param_2 * 4 + this + 0x40) + 0x40;
  }
  else {
    iVar1 = 0;
  }
  return iVar1;
}

// JP: 0x00283f10  GetUpdatePacket__14PluralFontItemFv  size 0x100
// PluralFontItem::GetUpdatePacket()
void GetUpdatePacket__14PluralFontItemFv(PluralFontItem *this)
{
  u16 uVar1;
  u16 uVar2;
  int iVar3;
  uVar1 = (u16)m_Env__8VIF1Prim;
  uVar2 = uVar1 & 1;
  if ((long)((ulong)*(u8 *)(this + (short)uVar2 + 0x10) << 0x39) < 0) {
    SetUV__14PluralFontItemFss(this,uVar2 ^ 1,uVar2);
    *(u8 *)(this + (short)uVar2 + 0x10) = *(u8 *)(this + (short)uVar2 + 0x10) & 0xbf;
  }
  iVar3 = this + (short)(uVar2 ^ 1);
  *(u8 *)(iVar3 + 0x10) = *(u8 *)(iVar3 + 0x10) & 0xbf | 0x40;
  GetFontPacket__14PluralFontItemCFUc(this,uVar1 & 1);
  return;
}

// JP: 0x00284010  SetFontColor__14PluralFontItemFUsUsUcUcUc  size 0x10c
// PluralFontItem::SetFontColor(unsigned short, unsigned short, unsigned char, unsigned char, unsigned char)
void SetFontColor__14PluralFontItemFUsUsUcUcUc
               (PluralFontItem *this,u16 param_2,u16 param_3,u8 param_4,u8 param_5,
               u8 param_6)
{
  int iVar1;
  ulong uVar2;
  uint uVar3;
  uint uVar4;
  iVar1 = GetFontPacket__14PluralFontItemCFUc(this,0);
  uVar3 = iVar1 + (uint)param_2 * 0x30;
  uVar4 = uVar3 + (uint)param_3 * 0x30;
  for (; uVar3 < uVar4; uVar3 = uVar3 + 0x30) {
    *(u8 *)(uVar3 + 0x14) = param_4;
    *(u8 *)(uVar3 + 0x15) = param_5;
    *(u8 *)(uVar3 + 0x16) = param_6;
  }
  uVar2 = (ulong)this->dirty1 & 0xffffffffffffffef | 0x10;
  this->dirty1 = (char)uVar2;
  this->dirty0 =
       this->dirty0 & 0xef | (u8)((uint)((uVar2 << 0x3b) >> 0x3f) << 4);
  return;
}

// JP: 0x00284120  SetUV__14PluralFontItemFss  size 0x128
// PluralFontItem::SetUV(short, short)
void SetUV__14PluralFontItemFss(PluralFontItem *this,u8 param_2,u8 param_3)
{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uVar1 = GetFontPacket__14PluralFontItemCFUc(this,param_2);
  iVar2 = GetFontPacket__14PluralFontItemCFUc(this,param_3);
  uVar3 = uVar1 + (uint)this->f_7e /*u16 **/ * 0x30;
  for (; uVar1 < uVar3; uVar1 = uVar1 + 0x30) {
    *(u16 *)(iVar2 + 0x10) =
         *(u16 *)(iVar2 + 0x10) & 0xc000 | *(u16 *)(uVar1 + 0x10) & 0x3fff;
    *(u16 *)(iVar2 + 0x12) =
         *(u16 *)(iVar2 + 0x12) & 0xc000 | *(u16 *)(uVar1 + 0x12) & 0x3fff;
    *(u16 *)(iVar2 + 0x20) =
         *(u16 *)(iVar2 + 0x20) & 0xc000 | *(u16 *)(uVar1 + 0x20) & 0x3fff;
    *(u16 *)(iVar2 + 0x22) =
         *(u16 *)(iVar2 + 0x22) & 0xc000 | *(u16 *)(uVar1 + 0x22) & 0x3fff;
    iVar2 = iVar2 + 0x30;
  }
  return;
}

// JP: 0x00284250  GetFontEnv__14PluralFontItemFv  size 0xb4
// PluralFontItem::GetFontEnv()
ulong GetFontEnv__14PluralFontItemFv(PluralFontItem *this)
{
  int iVar1;
  ulong uVar2;
  ulong uVar3;
  iVar1 = this->font_draw;
  uVar3 = *(ulong *)(*(int *)(iVar1 + 0x2c) +
                    (int)((long)((ulong)*(u8 *)(iVar1 + 0x3e) << 0x3e) >> 0x3f) * -0x20);
  uVar2 = GetClutFlag__10ClutRasterFUcUc
                    (*(u32 *)(iVar1 + 0x30),this->csa,0);
  return uVar3 & 0x7ffffffff | uVar2;
}

// JP: 0x00284310  SetBright__14PluralFontItemFf  size 0xf4
// PluralFontItem::SetBright(float)
void SetBright__14PluralFontItemFf(u32 param_1,int this)
{
  uint uVar1;
  ulong uVar2;
  uint uVar3;
  uVar1 = GetFontPacket__14PluralFontItemCFUc(this,0);
  uVar3 = uVar1 + (uint)this->f_7e /*u16 **/ * 0x30;
  for (; uVar1 < uVar3; uVar1 = uVar1 + 0x30) {
    if (*(char *)(uVar1 + 0xc) != '\0') {
      SetBright__7MenuObjFP7_rgba32f(param_1,uVar1 + 0x14);
    }
  }
  uVar2 = (ulong)this->dirty1 & 0xffffffffffffffef | 0x10;
  this->dirty1 = (char)uVar2;
  this->dirty0 =
       this->dirty0 & 0xef | (u8)((uint)((uVar2 << 0x3b) >> 0x3f) << 4);
  return;
}

// JP: 0x00284410  AllotPacket__14PluralFontItemFP4_QWDP4_QWD  size 0x10
// PluralFontItem::AllotPacket(_QWD*, _QWD*)
void AllotPacket__14PluralFontItemFP4_QWDP4_QWD(void)
{
  return;
}

// JP: 0x00284420  GetAllotCount__14PluralFontItemFv  size 0x14
// PluralFontItem::GetAllotCount()
u64 GetAllotCount__14PluralFontItemFv(void)
{
  return 0;
}

// JP: 0x00284440  Update__14PluralFontItemFiiUs  size 0xce0
// PluralFontItem::Update(int, int, unsigned short)
void Update__14PluralFontItemFiiUs(PluralFontItem *this,int param_2,int param_3,u16 param_4)
{
  u16 uVar1;
  u32 *puVar2;
  u8 auVar3 [16];
  u8 auVar4 [16];
  u8 *puVar5;
  int iVar6;
  u64 uVar7;
  u16 uVar8;
  u8 *puVar9;
  u8 *pbVar10;
  uint uVar11;
  u32 *puVar12;
  u8 *puVar13;
  int iVar14;
  u8 bVar15;
  u8 auVar16 [16];
  u8 auVar17 [16];
  u64 in_a2_udw;
  u64 in_a3_udw;
  uVar8 = m_Env__8VIF1Prim & 1;
  puVar5 = (u8 *)GetFontPacket__14PluralFontItemCFUc(this,m_Env__8VIF1Prim & 1);
  iVar6 = GetFontPacket__14PluralFontItemCFUc(this,0);
  puVar9 = puVar5 + (uint)this->f_7e /*u16 **/ * 0x30;
  uVar1 = this->f_78 /*u16 **/;
  puVar2 = *(u32 **)((short)uVar8 * 4 + this + 0x40);
  pbVar10 = (u8 *)(this + (short)uVar8 + 0x10);
  param_2 = param_2 + (int)this->x * 0x10;
  param_3 = param_3 + (int)this->y * 0x10;
  bVar15 = this->a;
  TraceAddUpdate__12MenuObjTableFUc(this + 0x68,*pbVar10);
  TraceUpdate__12MenuObjTableFiiUs
            (this + 0x68,param_2,param_3,(short)((uint)bVar15 * 0x100 * (uint)param_4 >> 0xf));
  iVar14 = iVar6;
  puVar13 = puVar5;
  if ((long)((ulong)*pbVar10 << 0x3c) < 0) {
    for (; puVar13 < puVar5 + (uint)uVar1 * 0x30; puVar13 = puVar13 + 0x30) {
      for (; *(char *)(iVar14 + 0xc) == '\0'; iVar14 = iVar14 + 0x30) {
      }
      *(short *)(puVar13 + 0x18) = (short)param_2 + *(short *)(iVar14 + 4) * 0x10;
      *(short *)(puVar13 + 0x1a) = (short)param_3 + *(short *)(iVar14 + 6) * 0x10;
      auVar16._8_8_ = in_a2_udw;
      auVar16._0_8_ = 0xffffffff;
      auVar4._8_8_ = in_a3_udw;
      auVar4._0_8_ = 0xffffffffffffffff;
      auVar16 = _pcpyld(auVar4,auVar16);
      *(ulong *)(puVar13 + 0x18) = *(ulong *)(puVar13 + 0x18) & auVar16._0_8_ | 0x100000000;
      *(u16 *)(puVar13 + 0x28) =
           *(short *)(puVar13 + 0x18) + (u16)*(u8 *)(iVar14 + 0xc) * 0x10;
      *(u16 *)(puVar13 + 0x2a) =
           *(short *)(puVar13 + 0x1a) + (u16)*(u8 *)(iVar14 + 0xd) * 0x10;
      auVar17._8_8_ = auVar16._8_8_;
      auVar17._0_8_ = 0xffffffff;
      auVar3._8_8_ = in_a2_udw;
      auVar3._0_8_ = 0xffffffffffffffff;
      auVar16 = _pcpyld(auVar3,auVar17);
      *(ulong *)(puVar13 + 0x28) = *(ulong *)(puVar13 + 0x28) & auVar16._0_8_ | 0x100000000;
      iVar14 = iVar14 + 0x30;
    }
  }
  if ((long)((ulong)*pbVar10 << 0x3b) < 0) {
    uVar11 = 0x8000;
    puVar13 = puVar5;
    if ((long)((ulong)this->pflags << 0x3a) < 0) {
      uVar11 = (uint)param_4;
    }
    for (; puVar13 < puVar5 + (uint)uVar1 * 0x30; puVar13 = puVar13 + 0x30) {
      for (; *(char *)(iVar6 + 0xc) == '\0'; iVar6 = iVar6 + 0x30) {
      }
      *puVar13 = *(u8 *)(iVar6 + 0x14);
      puVar13[1] = *(u8 *)(iVar6 + 0x15);
      puVar13[2] = *(u8 *)(iVar6 + 0x16);
      puVar13[3] = (char)(*(u8 *)(iVar6 + 0x17) * uVar11 >> 0xf);
      puVar13[8] = this->color2_r;
      puVar13[9] = this->color2_g;
      puVar13[10] = this->color2_b;
      puVar13[0xb] = puVar13[3];
      iVar6 = iVar6 + 0x30;
    }
  }
  if ((long)((ulong)*pbVar10 << 0x39) < 0) {
    SetUV__14PluralFontItemFss(this,uVar8 ^ 1,uVar8);
  }
  bVar15 = this->fflags2 & 7;
  if (bVar15 == 2) {
    puVar12 = puVar2 + ((uint)this->f_74 /*u16 **/ * 3 + 5) * 4;
    if ((*pbVar10 & 1) != 0) {
      puVar12[0x20] = &DAT_10000002;
      puVar12[0x10] = &DAT_10000002;
      *puVar12 = &DAT_10000002;
      puVar12[0x23] = 0x50000002;
      puVar12[0x13] = 0x50000002;
      puVar12[3] = 0x50000002;
      puVar12[0x30] = &DAT_10000003;
      puVar12[0x33] = 0x50000003;
      puVar13 = puVar5 + -0x10;
      puVar12[0x2d] = puVar13;
      puVar12[0x1d] = puVar13;
      puVar12[0xd] = puVar13;
      puVar12[0x41] = puVar5;
      *(u64 *)(puVar2 + 4) = 0x10ab400000000002;
      *(u64 *)(puVar2 + 6) = 0xe;
      *(u64 *)(puVar12 + 0x34) = 0x1000000000000001;
      *(u64 *)(puVar12 + 0x24) = 0x1000000000000001;
      *(u64 *)(puVar12 + 0x14) = 0x1000000000000001;
      *(u64 *)(puVar12 + 4) = 0x1000000000000001;
      *(u64 *)(puVar12 + 0x36) = 0xe;
      *(u64 *)(puVar12 + 0x26) = 0xe;
      *(u64 *)(puVar12 + 0x16) = 0xe;
      *(u64 *)(puVar12 + 6) = 0xe;
      *(u64 *)(puVar2 + 0x12) = 0x53d31f;
      *(u64 *)(puVar12 + 0x3e) = 0x53d3f1;
      *(u64 *)(puVar2 + 10) = 6;
      *(u64 *)(puVar12 + 0x3a) = 0x18;
      *(u64 *)(puVar12 + 0x2a) = 0x18;
      *(u64 *)(puVar12 + 0x1a) = 0x18;
      *(u64 *)(puVar12 + 10) = 0x18;
      *(u64 *)(puVar2 + 0xe) = 0x18;
      for (; puVar5 < puVar9; puVar5 = puVar5 + 0x30) {
        puVar5[10] = 0;
        puVar5[9] = 0;
        puVar5[8] = 0;
      }
    }
    if ((long)((ulong)*pbVar10 << 0x3d) < 0) {
      if (this->f_78 /*short **/ == 0) {
        *puVar2 = 0x20000000;
        puVar2[1] = puVar2 + (this->qwc - 1) * 4;
        puVar2[3] = 0;
      }
      else {
        *puVar2 = &UNK_20000004 + (uint)this->f_78 /*u16 **/ * 3;
        puVar2[1] = puVar12;
        puVar2[3] = (uint)this->f_78 /*u16 **/ * 3 + 0x50000004;
        iVar14 = (uint)this->f_78 /*u16 **/ * 3 + 0x30000001;
        puVar12[0x2c] = iVar14;
        puVar12[0x1c] = iVar14;
        puVar12[0xc] = iVar14;
        iVar14 = (uint)this->f_78 /*u16 **/ * 3 + 0x50000001;
        puVar12[0x2f] = iVar14;
        puVar12[0x1f] = iVar14;
        puVar12[0xf] = iVar14;
        puVar12[0x40] = (uint)this->f_78 /*u16 **/ * 3 + 0x30000000;
        puVar12[0x43] = (uint)this->f_78 /*u16 **/ * 3 + 0x50000000;
        *(ulong *)(puVar2 + 0x10) = (ulong)this->f_78 /*u16 **/ | 0x6400000000000000;
        *(ulong *)(puVar12 + 0x3c) = (ulong)this->f_78 /*u16 **/ | 0x6400000000008000;
      }
    }
    if ((long)((ulong)*pbVar10 << 0x3e) < 0) {
      uVar7 = VCALL(this, 0x64 /*slot_64*/)();
      *(u64 *)(puVar2 + 8) = uVar7;
      *(u16 *)(puVar2 + 0xc) =
           (0x700 - (u16)(((ulong)this->fflags2 << 0x3a) >> 0x3d)) * 0x10;
      *(u16 *)(puVar2 + 0xd) = 0x7200;
      *(u16 *)(puVar12 + 8) =
           ((u16)(((ulong)this->fflags2 << 0x3a) >> 0x3d) + 0x700) * 0x10;
      *(u16 *)(puVar12 + 9) = 0x7200;
      *(u16 *)(puVar12 + 0x18) = 0x7000;
      *(u16 *)(puVar12 + 0x19) =
           (0x720 - (u16)(((ulong)this->fflags2 << 0x3a) >> 0x3d)) * 0x10;
      *(u16 *)(puVar12 + 0x28) = 0x7000;
      *(u16 *)(puVar12 + 0x29) =
           ((u16)(((ulong)this->fflags2 << 0x3a) >> 0x3d) + 0x720) * 0x10;
      *(u16 *)(puVar12 + 0x38) = 0x7000;
      *(u16 *)(puVar12 + 0x39) = 0x7200;
    }
  }
  else if (bVar15 == 1) {
    puVar12 = puVar2 + ((uint)this->f_74 /*u16 **/ * 3 + 5) * 4;
    if ((*pbVar10 & 1) != 0) {
      *puVar12 = &DAT_10000003;
      puVar12[3] = 0x50000003;
      puVar12[0x11] = puVar5;
      *(u64 *)(puVar2 + 4) = 0x10ab400000000002;
      *(u64 *)(puVar2 + 6) = 0xe;
      *(u64 *)(puVar2 + 0x12) = 0x53d31f;
      *(u64 *)(puVar12 + 4) = 0x1000000000000001;
      *(u64 *)(puVar12 + 6) = 0xe;
      *(u64 *)(puVar12 + 0xe) = 0x53d3f1;
      *(u64 *)(puVar2 + 10) = 6;
      *(u64 *)(puVar12 + 10) = 0x18;
      *(u64 *)(puVar2 + 0xe) = 0x18;
      for (; puVar5 < puVar9; puVar5 = puVar5 + 0x30) {
        puVar5[10] = 0;
        puVar5[9] = 0;
        puVar5[8] = 0;
      }
    }
    if ((long)((ulong)*pbVar10 << 0x3d) < 0) {
      if (this->f_78 /*short **/ == 0) {
        *puVar2 = 0x20000000;
        puVar2[1] = puVar2 + (this->qwc - 1) * 4;
        puVar2[3] = 0;
      }
      else {
        *puVar2 = &UNK_20000004 + (uint)this->f_78 /*u16 **/ * 3;
        puVar2[1] = puVar12;
        puVar2[3] = (uint)this->f_78 /*u16 **/ * 3 + 0x50000004;
        puVar12[0x10] = (uint)this->f_78 /*u16 **/ * 3 + 0x30000000;
        puVar12[0x13] = (uint)this->f_78 /*u16 **/ * 3 + 0x50000000;
        *(ulong *)(puVar2 + 0x10) = (ulong)this->f_78 /*u16 **/ | 0x6400000000000000;
        *(ulong *)(puVar12 + 0xc) = (ulong)this->f_78 /*u16 **/ | 0x6400000000008000;
      }
    }
    if ((long)((ulong)*pbVar10 << 0x3e) < 0) {
      uVar7 = VCALL(this, 0x64 /*slot_64*/)();
      *(u64 *)(puVar2 + 8) = uVar7;
      *(u16 *)(puVar2 + 0xc) =
           (0x700 - (u16)(((ulong)this->fflags2 << 0x3a) >> 0x3d)) * 0x10;
      *(u16 *)(puVar2 + 0xd) =
           (0x720 - (u16)(((ulong)this->fflags2 << 0x3a) >> 0x3d)) * 0x10;
      *(u16 *)(puVar12 + 8) = 0x7000;
      *(u16 *)(puVar12 + 9) = 0x7200;
    }
  }
  else if ((bVar15 == 3) || ((this->fflags2 & 7) == 0)) {
    if ((*pbVar10 & 1) != 0) {
      *(u64 *)(puVar2 + 4) = 0x10ab400000000001;
      *(u64 *)(puVar2 + 6) = 0xe;
      *(u64 *)(puVar2 + 0xe) = 0x53d3f1;
      *(u64 *)(puVar2 + 10) = 6;
    }
    if ((long)((ulong)*pbVar10 << 0x3d) < 0) {
      if (this->f_78 /*short **/ == 0) {
        *puVar2 = 0x20000000;
        puVar2[1] = puVar2 + (this->qwc - 1) * 4;
        puVar2[3] = 0;
      }
      else {
        *puVar2 = &UNK_20000003 + (uint)this->f_78 /*u16 **/ * 3;
        puVar2[1] = puVar2 + ((uint)this->f_74 /*u16 **/ * 3 + 4) * 4;
        puVar2[3] = (uint)this->f_78 /*u16 **/ * 3 + 0x50000003;
        *(ulong *)(puVar2 + 0xc) = (ulong)this->f_78 /*u16 **/ | 0x6400000000008000;
      }
    }
    if ((long)((ulong)*pbVar10 << 0x3e) < 0) {
      uVar7 = VCALL(this, 0x64 /*slot_64*/)();
      *(u64 *)(puVar2 + 8) = uVar7;
    }
  }
  *pbVar10 = *pbVar10 & 0x80;
  return;
}

// JP: 0x00285120  Clear__14PluralFontItemFv  size 0x6c
// PluralFontItem::Clear()
void Clear__14PluralFontItemFv(PluralFontItem *this)
{
  Clear__8FontItemFv(this);
  this->f_7e /*u16 **/ = 0;
  this->f_7c /*u16 **/ = 0;
  this->f_7a /*u16 **/ = 0;
  this->f_78 /*u16 **/ = 0;
  this->f_76 /*u16 **/ = 0;
  this->f_74 /*u16 **/ = 0;
  return;
}

// JP: 0x00285190  @60@__dt__14PluralFontItemFv  size 0x8
// @60@__dt__14PluralFontItemFv
u32 * _60___dt__14PluralFontItemFv(PluralFontItem *this,short param_2)
{
  u32 *puVar1;
  puVar1 = this + -0xf;
  if (puVar1 != (u32 *)0x0) {
    this[-0xd] = __vt__14PluralFontItem;
    *this = 0x4055f4;
    __dt__8FontItemFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}
