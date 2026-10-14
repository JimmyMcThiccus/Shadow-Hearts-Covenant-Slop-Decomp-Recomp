/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x0027bfd0  __ct__8MenuTextFv  size 0x60
// MenuText::MenuText()
int __ct__8MenuTextFv(MenuText *this)
{
  __ct__8FontItemFv(this);
  this->vptr = __vt__8MenuText;
  this->packet = 0x4053e4;
  VCALL(this, 0x20 /*Clear*/)();
  return this;
}

// JP: 0x0027c030  __dt__8MenuTextFv  size 0x94
// MenuText::~MenuText()
int __dt__8MenuTextFv(MenuText *this,short param_2)
{
  if (this != 0) {
    this->vptr = __vt__8MenuText;
    this->packet = 0x4053e4;
    VCALL(this, 0x1c /*Destroy*/)();
    __dt__8FontItemFv(this,0);
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

// JP: 0x0027c0d0  Create__8MenuTextFUcUc  size 0xec
// MenuText::Create(unsigned char, unsigned char)
u32 Create__8MenuTextFUcUc(MenuText *this,char param_2,u8 param_3)
{
  if (param_3 == 2) {
    this->qwc = 0x12;
  }
  else if (param_3 == 1) {
    this->qwc = 10;
  }
  else if ((param_3 == 3) || (param_3 == 0)) {
    this->qwc = 8;
  }
  if (param_2 != '\0') {
    CreatePacket__10MenuPacketFUs(this + 0x3c,this->qwc);
  }
  this->fflags2 = this->fflags2 & 0xf8 | param_3 & 7;
  return 1;
}

// JP: 0x0027c1c0  SetMessage__8MenuTextFPcUiUcUc  size 0x178
// MenuText::SetMessage(char*, unsigned int, unsigned char, unsigned char)
u32
SetMessage__8MenuTextFPcUiUcUc
          (MenuText *this,void *param_2,u32 param_3,u8 param_4,u8 param_5)
{
  u32 uVar1;
  long lVar2;
  int iStack_54;
  int iStack_50;
  void *pvStack_40;
  u32 uStack_30;
  u8 bStack_20;
  u8 bStack_10;
  iStack_50 = this;
  pvStack_40 = param_2;
  uStack_30 = param_3;
  bStack_20 = param_4;
  bStack_10 = param_5;
  DeleteString__8FontItemFv(this);
  *(u16 *)(iStack_50 + 0x7c) = 0;
  *(u32 *)(iStack_50 + 0x30) = 0;
  *(u32 *)(iStack_50 + 0x2c) = 0;
  memset((void *)(iStack_50 + 0x74),0,8);
  *(u8 *)(iStack_50 + 0x10) = *(u8 *)(iStack_50 + 0x10) | 0x3f;
  *(u8 *)(iStack_50 + 0x11) = *(u8 *)(iStack_50 + 0x11) | 0x3f;
  lVar2 = StrLen__FPUcPi(pvStack_40,&iStack_54);
  if (lVar2 == 0) {
    uVar1 = 0;
  }
  else {
    if (bStack_20 == 0) {
      *(void **)(iStack_50 + 0x60) = pvStack_40;
    }
    else {
      uVar1 = __nwa__FUi(iStack_54 + 1);
      *(u32 *)(iStack_50 + 0x60) = uVar1;
      memcpy(*(void **)(iStack_50 + 0x60),pvStack_40,(long)(iStack_54 + 1));
    }
    *(u8 *)(iStack_50 + 0x58) = *(u8 *)(iStack_50 + 0x58) & 0xf8 | (u8)uStack_30 & 7;
    *(u8 *)(iStack_50 + 0x5f) = *(u8 *)(iStack_50 + 0x5f) & 0xfe | bStack_20 & 1;
    *(u8 *)(iStack_50 + 0x5f) = *(u8 *)(iStack_50 + 0x5f) & 0xfd | (bStack_10 & 1) << 1;
    uVar1 = 1;
  }
  return uVar1;
}

// JP: 0x0027c340  AllotPacket__8MenuTextFP4_QWDP4_QWD  size 0xec
// MenuText::AllotPacket(_QWD*, _QWD*)
void AllotPacket__8MenuTextFP4_QWDP4_QWD(MenuText *this,int param_2,u32 param_3)
{
  if (param_2 != 0) {
    if (this->owner->scroll->font_draw != 0) {
      OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_
                (this->owner->scroll->font_draw,this,
                 ((ulong)this->fflags & 0xf) >> 3,0);
    }
    this->dirty0 = this->dirty0 | 0x3f;
    this->dirty1 = this->dirty1 | 0x3f;
  }
  SetPacket__10MenuPacketFUsP4_QWDP4_QWD
            (this + 0x3c,this->qwc,param_2,param_3);
  return;
}

// JP: 0x0027c430  Update__8MenuTextFiiUs  size 0xf78
// MenuText::Update(int, int, unsigned short)
void Update__8MenuTextFiiUs(MenuText *this,int param_2,int param_3,u16 param_4)
{
  u32 *puVar1;
  u8 auVar2 [16];
  u8 auVar3 [16];
  u8 auVar4 [16];
  short sVar5;
  short sVar6;
  short sVar7;
  u16 uVar8;
  ulong uVar9;
  int iVar10;
  ulong *puVar11;
  ulong uVar12;
  u64 in_v1_udw;
  u8 auVar13 [16];
  u8 auVar14 [16];
  u8 auVar15 [16];
  u8 auVar16 [16];
  u8 auVar17 [16];
  u8 auVar18 [16];
  u8 auVar19 [16];
  u8 auVar20 [16];
  u8 auVar21 [16];
  u8 auVar22 [16];
  u8 auVar23 [16];
  u64 in_a0_udw;
  u8 auVar24 [16];
  u8 auVar25 [16];
  u8 auVar26 [16];
  u8 auVar27 [16];
  u8 auVar28 [16];
  u8 auVar29 [16];
  u8 auVar30 [16];
  u64 in_a1_udw;
  u8 auVar31 [16];
  u8 auVar32 [16];
  u8 auVar33 [16];
  u8 bVar34;
  u64 in_a2_udw;
  u8 auVar35 [16];
  u8 auVar36 [16];
  u8 auVar37 [16];
  u8 auVar38 [16];
  u64 in_a3_udw;
  u8 *pbVar39;
  u64 in_t0_udw;
  u8 auVar40 [16];
  u8 auVar41 [16];
  u8 auVar42 [16];
  u64 in_t1_udw;
  u8 in_t2_qw [16];
  u64 uVar44;
  u8 auVar43 [16];
  u32 *puVar45;
  u16 *puVar46;
  u32 in_s3_udw;
  u32 in_register_0000013c;
  int unaff_s6_lo;
  int unaff_s7_lo;
  short unaff_s8_lo;
  short sStack_54;
  uint uStack_4c;
  u8 bStack_41;
  puVar1 = *(u32 **)(this + (m_Env__8VIF1Prim & 1) * 4 + 0x40);
  pbVar39 = (u8 *)(this + (m_Env__8VIF1Prim & 1) + 0x10);
  iVar10 = this->nchars * 0x10;
  param_2 = param_2 + iVar10 + (int)this->x * 0x10;
  param_3 = param_3 + iVar10 + (int)this->y * 0x10;
  bVar34 = this->a;
  TraceAddUpdate__12MenuObjTableFUc(this + 0x68,*pbVar39);
  TraceUpdate__12MenuObjTableFiiUs
            (this + 0x68,param_2,param_3,(short)((uint)bVar34 * 0x100 * (uint)param_4 >> 0xf));
  CleanPacket__8MenuItemFv(this);
  uVar44 = in_t2_qw._8_8_;
  if (((long)((ulong)*pbVar39 << 0x3b) < 0) &&
     (bStack_41 = this->a, (long)((ulong)this->pflags << 0x3a) < 0))
  {
    bStack_41 = (u8)((uint)bStack_41 * (uint)param_4 >> 0xf);
  }
  if ((long)((ulong)*pbVar39 << 0x3c) < 0) {
    sStack_54 = (short)param_2 + (short)(int)this->w * 0x10;
    unaff_s8_lo = (short)param_3 + (short)(int)this->h * 0x10;
    unaff_s7_lo = param_2;
    unaff_s6_lo = param_3;
  }
  if (this->font_draw != 0) {
    iVar10 = this->font_draw;
    uVar12 = *(ulong *)(*(int *)(iVar10 + 0x2c) +
                       (int)((long)((ulong)*(u8 *)(iVar10 + 0x3e) << 0x3e) >> 0x3f) * -0x20);
    uVar9 = GetClutFlag__10ClutRasterFUcUc
                      (*(u32 *)(iVar10 + 0x30),this->csa,0);
    uVar44 = in_t2_qw._8_8_;
    *(ulong *)(puVar1 + 8) = uVar12 & 0x7ffffffff | uVar9;
  }
  bVar34 = this->fflags2 & 7;
  sVar6 = (short)unaff_s7_lo;
  sVar5 = (short)unaff_s6_lo;
  if (bVar34 == 2) {
    if ((*pbVar39 & 1) != 0) {
      *puVar1 = 0x10000010;
      puVar1[3] = 0x50000010;
      *(u64 *)(puVar1 + 4) = 0x10ab400000000001;
      *(u64 *)(puVar1 + 6) = 0xe;
      *(u64 *)(puVar1 + 0xc) = 0x5400000000008005;
      *(u64 *)(puVar1 + 0xe) = 0x53d31;
      *(u64 *)(puVar1 + 10) = 6;
    }
    if ((long)((ulong)*pbVar39 << 0x3b) < 0) {
      puVar45 = puVar1 + 0x10;
      for (uStack_4c = 0; uStack_4c < 4; uStack_4c = uStack_4c + 1) {
        *(u8 *)puVar45 = this->color2_r;
        *(u8 *)((int)puVar45 + 1) = this->color2_g;
        *(u8 *)((int)puVar45 + 2) = this->color2_b;
        *(u8 *)((int)puVar45 + 3) = bStack_41;
        puVar45 = puVar45 + 10;
      }
      *(u8 *)puVar45 = this->r;
      *(u8 *)((int)puVar45 + 1) = this->g;
      *(u8 *)((int)puVar45 + 2) = this->b;
      *(u8 *)((int)puVar45 + 3) = bStack_41;
    }
    if ((long)((ulong)*pbVar39 << 0x3a) < 0) {
      puVar46 = (u16 *)(puVar1 + 0x12);
      for (uStack_4c = 0; uStack_4c < 5; uStack_4c = uStack_4c + 1) {
        *puVar46 = *puVar46 & 0xc000 | this->rx0 * 0x10 + 8U & 0x3fff;
        puVar46[1] = puVar46[1] & 0xc000 | this->ry0 * 0x10 + 8U & 0x3fff;
        puVar46[8] = puVar46[8] & 0xc000 | this->rx1 * 0x10 + 8U & 0x3fff;
        puVar46[9] = puVar46[9] & 0xc000 | this->ry1 * 0x10 + 8U & 0x3fff;
        puVar46 = puVar46 + 0x14;
      }
    }
    if ((long)((ulong)*pbVar39 << 0x3c) < 0) {
      uVar8 = (u16)(((ulong)this->fflags2 << 0x3a) >> 0x30);
      sVar7 = (uVar8 >> 0xd) * 0x10;
      puVar11 = (ulong *)(puVar1 + 0x14);
      *(short *)puVar11 = sVar6 + sVar7;
      *(short *)((int)puVar1 + 0x52) = sVar5;
      auVar26._8_8_ = in_a0_udw;
      auVar26._0_8_ = 0xffffffffffffffff;
      auVar14._8_8_ = in_a3_udw;
      auVar14._0_8_ = 0xffffffff;
      auVar14 = _pcpyld(auVar26,auVar14);
      *puVar11 = *puVar11 & auVar14._0_8_ | 0x100000000;
      puVar11 = (ulong *)(puVar1 + 0x18);
      auVar19._8_8_ = auVar14._8_8_;
      *(short *)puVar11 = sStack_54 + sVar7;
      *(short *)((int)puVar1 + 0x62) = unaff_s8_lo;
      auVar31._8_8_ = in_a1_udw;
      auVar31._0_8_ = 0xffffffff;
      auVar4._8_4_ = in_s3_udw;
      auVar4._0_8_ = 0xffffffffffffffff;
      auVar4._12_4_ = in_register_0000013c;
      auVar14 = _pcpyld(auVar4,auVar31);
      *puVar11 = *puVar11 & auVar14._0_8_ | 0x100000000;
      puVar11 = (ulong *)(puVar1 + 0x1e);
      auVar32._8_8_ = auVar14._8_8_;
      *(u16 *)puVar11 = sVar6 + (uVar8 >> 0xd) * -0x10;
      *(short *)((int)puVar1 + 0x7a) = sVar5;
      auVar19._0_8_ = 0xffffffffffffffff;
      auVar27._8_8_ = in_a0_udw;
      auVar27._0_8_ = 0xffffffff;
      auVar14 = _pcpyld(auVar19,auVar27);
      *puVar11 = *puVar11 & auVar14._0_8_ | 0x100000000;
      puVar11 = (ulong *)(puVar1 + 0x22);
      auVar20._8_8_ = auVar14._8_8_;
      *(u16 *)puVar11 = sStack_54 + (uVar8 >> 0xd) * -0x10;
      *(short *)((int)puVar1 + 0x8a) = unaff_s8_lo;
      auVar37._8_8_ = in_a2_udw;
      auVar37._0_8_ = 0xffffffffffffffff;
      auVar32._0_8_ = 0xffffffff;
      auVar14 = _pcpyld(auVar37,auVar32);
      *puVar11 = *puVar11 & auVar14._0_8_ | 0x100000000;
      puVar11 = (ulong *)(puVar1 + 0x28);
      *(short *)puVar11 = sVar6;
      auVar33._8_8_ = auVar14._8_8_;
      *(short *)((int)puVar1 + 0xa2) = sVar5 + sVar7;
      auVar42._8_8_ = in_t0_udw;
      auVar42._0_8_ = 0xffffffffffffffff;
      auVar28._8_8_ = in_a0_udw;
      auVar28._0_8_ = 0xffffffff;
      auVar14 = _pcpyld(auVar42,auVar28);
      auVar29._8_8_ = auVar14._8_8_;
      *puVar11 = *puVar11 & auVar14._0_8_ | 0x100000000;
      puVar11 = (ulong *)(puVar1 + 0x2c);
      *(short *)puVar11 = sStack_54;
      *(short *)((int)puVar1 + 0xb2) = unaff_s8_lo + sVar7;
      auVar20._0_8_ = 0xffffffffffffffff;
      auVar38._8_8_ = in_a2_udw;
      auVar38._0_8_ = 0xffffffff;
      auVar14 = _pcpyld(auVar20,auVar38);
      *puVar11 = *puVar11 & auVar14._0_8_ | 0x100000000;
      puVar11 = (ulong *)(puVar1 + 0x32);
      *(short *)puVar11 = sVar6;
      *(u16 *)((int)puVar1 + 0xca) = sVar5 + (uVar8 >> 0xd) * -0x10;
      auVar21._8_8_ = auVar20._8_8_;
      auVar21._0_8_ = 0xffffffffffffffff;
      auVar43._8_8_ = uVar44;
      auVar43._0_8_ = 0xffffffff;
      auVar14 = _pcpyld(auVar21,auVar43);
      auVar22._8_8_ = auVar14._8_8_;
      *puVar11 = *puVar11 & auVar14._0_8_ | 0x100000000;
      puVar11 = (ulong *)(puVar1 + 0x36);
      *(short *)puVar11 = sStack_54;
      *(u16 *)((int)puVar1 + 0xda) = unaff_s8_lo + (uVar8 >> 0xd) * -0x10;
      auVar29._0_8_ = 0xffffffffffffffff;
      auVar22._0_8_ = 0xffffffff;
      auVar14 = _pcpyld(auVar29,auVar22);
      auVar23._8_8_ = auVar14._8_8_;
      *puVar11 = *puVar11 & auVar14._0_8_ | 0x100000000;
      puVar11 = (ulong *)(puVar1 + 0x3c);
      *(short *)puVar11 = sVar6;
      *(short *)((int)puVar1 + 0xf2) = sVar5;
      auVar30._8_8_ = auVar29._8_8_;
      auVar30._0_8_ = 0xffffffffffffffff;
      auVar3._8_8_ = in_t1_udw;
      auVar3._0_8_ = 0xffffffff;
      auVar14 = _pcpyld(auVar30,auVar3);
      *puVar11 = *puVar11 & auVar14._0_8_ | 0x100000000;
      puVar11 = (ulong *)(puVar1 + 0x40);
      *(short *)puVar11 = sStack_54;
      *(short *)((int)puVar1 + 0x102) = unaff_s8_lo;
      auVar33._0_8_ = 0xffffffffffffffff;
      auVar23._0_8_ = 0xffffffff;
      auVar14 = _pcpyld(auVar33,auVar23);
      *puVar11 = *puVar11 & auVar14._0_8_ | 0x100000000;
    }
  }
  else if (bVar34 == 1) {
    if ((*pbVar39 & 1) != 0) {
      *puVar1 = &DAT_10000008;
      puVar1[3] = 0x50000008;
      *(u64 *)(puVar1 + 4) = 0x10ab400000000001;
      *(u64 *)(puVar1 + 6) = 0xe;
      *(u64 *)(puVar1 + 0xc) = 0x5400000000008002;
      *(u64 *)(puVar1 + 0xe) = 0x53d31;
      *(u64 *)(puVar1 + 10) = 6;
    }
    if ((long)((ulong)*pbVar39 << 0x3b) < 0) {
      *(u8 *)(puVar1 + 0x10) = this->color2_r;
      *(u8 *)((int)puVar1 + 0x41) = this->color2_g;
      *(u8 *)((int)puVar1 + 0x42) = this->color2_b;
      *(u8 *)((int)puVar1 + 0x43) = bStack_41;
      *(u8 *)(puVar1 + 0x1a) = this->r;
      *(u8 *)((int)puVar1 + 0x69) = this->g;
      *(u8 *)((int)puVar1 + 0x6a) = this->b;
      *(u8 *)((int)puVar1 + 0x6b) = bStack_41;
    }
    if ((long)((ulong)*pbVar39 << 0x3a) < 0) {
      *(u16 *)(puVar1 + 0x12) =
           *(u16 *)(puVar1 + 0x12) & 0xc000 | this->rx0 * 0x10 + 8U & 0x3fff;
      *(u16 *)((int)puVar1 + 0x4a) =
           *(u16 *)((int)puVar1 + 0x4a) & 0xc000 |
           this->ry0 * 0x10 + 8U & 0x3fff;
      *(u16 *)(puVar1 + 0x16) =
           *(u16 *)(puVar1 + 0x16) & 0xc000 | this->rx1 * 0x10 + 8U & 0x3fff;
      *(u16 *)((int)puVar1 + 0x5a) =
           *(u16 *)((int)puVar1 + 0x5a) & 0xc000 |
           this->ry1 * 0x10 + 8U & 0x3fff;
      *(u16 *)(puVar1 + 0x1c) =
           *(u16 *)(puVar1 + 0x1c) & 0xc000 | this->rx0 * 0x10 + 8U & 0x3fff;
      *(u16 *)((int)puVar1 + 0x72) =
           *(u16 *)((int)puVar1 + 0x72) & 0xc000 |
           this->ry0 * 0x10 + 8U & 0x3fff;
      *(u16 *)(puVar1 + 0x20) =
           *(u16 *)(puVar1 + 0x20) & 0xc000 | this->rx1 * 0x10 + 8U & 0x3fff;
      *(u16 *)((int)puVar1 + 0x82) =
           *(u16 *)((int)puVar1 + 0x82) & 0xc000 |
           this->ry1 * 0x10 + 8U & 0x3fff;
    }
    if ((long)((ulong)*pbVar39 << 0x3c) < 0) {
      puVar11 = (ulong *)(puVar1 + 0x14);
      sVar7 = (short)((uint)(((ulong)this->fflags2 << 0x3a) >> 0x3d) << 4);
      *(short *)puVar11 = sVar6 + sVar7;
      *(short *)((int)puVar1 + 0x52) = sVar5 + sVar7;
      auVar16._8_8_ = in_v1_udw;
      auVar16._0_8_ = 0xffffffffffffffff;
      auVar41._8_8_ = in_t0_udw;
      auVar41._0_8_ = 0xffffffff;
      auVar14 = _pcpyld(auVar16,auVar41);
      *puVar11 = *puVar11 & auVar14._0_8_ | 0x100000000;
      puVar11 = (ulong *)(puVar1 + 0x18);
      *(short *)puVar11 = sStack_54 + sVar7;
      *(short *)((int)puVar1 + 0x62) = unaff_s8_lo + sVar7;
      auVar17._8_8_ = in_v1_udw;
      auVar17._0_8_ = 0xffffffffffffffff;
      auVar35._8_8_ = auVar14._8_8_;
      auVar35._0_8_ = 0xffffffff;
      auVar14 = _pcpyld(auVar17,auVar35);
      *puVar11 = *puVar11 & auVar14._0_8_ | 0x100000000;
      puVar11 = (ulong *)(puVar1 + 0x1e);
      *(short *)puVar11 = sVar6;
      *(short *)((int)puVar1 + 0x7a) = sVar5;
      auVar36._8_8_ = auVar14._8_8_;
      auVar25._8_8_ = in_a0_udw;
      auVar25._0_8_ = 0xffffffffffffffff;
      auVar2._8_8_ = in_t1_udw;
      auVar2._0_8_ = 0xffffffff;
      auVar14 = _pcpyld(auVar25,auVar2);
      *puVar11 = *puVar11 & auVar14._0_8_ | 0x100000000;
      puVar11 = (ulong *)(puVar1 + 0x22);
      *(short *)puVar11 = sStack_54;
      *(short *)((int)puVar1 + 0x8a) = unaff_s8_lo;
      auVar36._0_8_ = 0xffffffffffffffff;
      auVar18._8_8_ = in_v1_udw;
      auVar18._0_8_ = 0xffffffff;
      auVar14 = _pcpyld(auVar36,auVar18);
      *puVar11 = *puVar11 & auVar14._0_8_ | 0x100000000;
    }
  }
  else if ((bVar34 == 3) || ((this->fflags2 & 7) == 0)) {
    if ((*pbVar39 & 1) != 0) {
      *puVar1 = 0x10000006;
      puVar1[3] = 0x50000006;
      *(u64 *)(puVar1 + 4) = 0x20ab400000000001;
      *(u64 *)(puVar1 + 6) = 0x1e;
      *(u64 *)(puVar1 + 0x10) = 0x4400000000008001;
      *(u64 *)(puVar1 + 0x12) = 0x53d3;
      *(u64 *)(puVar1 + 10) = 6;
    }
    if ((long)((ulong)*pbVar39 << 0x3b) < 0) {
      puVar1[0xc] = (uint)this->r;
      puVar1[0xd] = (uint)this->g;
      puVar1[0xe] = (uint)this->b;
      puVar1[0xf] = (uint)bStack_41;
    }
    if ((long)((ulong)*pbVar39 << 0x3a) < 0) {
      *(u16 *)(puVar1 + 0x14) =
           *(u16 *)(puVar1 + 0x14) & 0xc000 | this->rx0 * 0x10 + 8U & 0x3fff;
      *(u16 *)((int)puVar1 + 0x52) =
           *(u16 *)((int)puVar1 + 0x52) & 0xc000 |
           this->ry0 * 0x10 + 8U & 0x3fff;
      *(u16 *)(puVar1 + 0x18) =
           *(u16 *)(puVar1 + 0x18) & 0xc000 | this->rx1 * 0x10 + 8U & 0x3fff;
      *(u16 *)((int)puVar1 + 0x62) =
           *(u16 *)((int)puVar1 + 0x62) & 0xc000 |
           this->ry1 * 0x10 + 8U & 0x3fff;
    }
    if ((long)((ulong)*pbVar39 << 0x3c) < 0) {
      puVar11 = (ulong *)(puVar1 + 0x16);
      *(short *)puVar11 = sVar6;
      *(short *)((int)puVar1 + 0x5a) = sVar5;
      auVar24._8_8_ = in_a0_udw;
      auVar24._0_8_ = 0xffffffffffffffff;
      auVar13._8_8_ = in_v1_udw;
      auVar13._0_8_ = 0xffffffff;
      auVar14 = _pcpyld(auVar24,auVar13);
      auVar15._8_8_ = auVar14._8_8_;
      *puVar11 = *puVar11 & auVar14._0_8_ | 0x100000000;
      puVar11 = (ulong *)(puVar1 + 0x1a);
      *(short *)puVar11 = sStack_54;
      *(short *)((int)puVar1 + 0x6a) = unaff_s8_lo;
      auVar15._0_8_ = 0xffffffffffffffff;
      auVar40._8_8_ = in_t0_udw;
      auVar40._0_8_ = 0xffffffff;
      auVar14 = _pcpyld(auVar15,auVar40);
      *puVar11 = *puVar11 & auVar14._0_8_ | 0x100000000;
    }
  }
  *pbVar39 = *pbVar39 & 0x80;
  return;
}

// JP: 0x0027d3b0  Connect__8MenuTextFP4_QWD  size 0x7c
// MenuText::Connect(_QWD*)
void Connect__8MenuTextFP4_QWD(MenuText *this,u32 param_2)
{
  u32 uVar1;
  u32 uStack_10;
  uStack_10 = param_2;
  if (this->attached != 0) {
    uStack_10 = VCALL(this->attached, 0x18 /*Connect*/)
                          (this->attached,param_2);
  }
  uVar1 = ConnectPacket__10MenuPacketFP4_QWD(this + 0x3c,uStack_10);
  TraceConnect__12MenuObjTableFP4_QWD(this + 0x68,uVar1);
  return;
}

// JP: 0x0027d430  Clear__8MenuTextFv  size 0x50
// MenuText::Clear()
void * Clear__8MenuTextFv(MenuText *this)
{
  void *pvVar1;
  Clear__8FontItemFv(this);
  this->f_7e /*u16 **/ = 0;
  this->nchars = 0;
  pvVar1 = memset((void *)(this + 0x74),0,8);
  return pvVar1;
}

// JP: 0x0027d480  @60@__dt__8MenuTextFv  size 0x8
// @60@__dt__8MenuTextFv
u32 * _60___dt__8MenuTextFv(MenuText *this,short param_2)
{
  u32 *puVar1;
  puVar1 = this + -0xf;
  if (puVar1 != (u32 *)0x0) {
    this[-0xd] = __vt__8MenuText;
    *this = 0x4053e4;
    (**(code **)(this[-0xd] + 0x1c))();
    __dt__8FontItemFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}
