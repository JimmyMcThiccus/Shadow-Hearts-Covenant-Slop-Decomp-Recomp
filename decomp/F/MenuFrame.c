/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x002781f0  __ct__9MenuFrameFv  size 0x70
// MenuFrame::MenuFrame()
int __ct__9MenuFrameFv(MenuFrame *this)
{
  __ct__7MenuObjFv(this);
  __ct__10MenuPacketFv(this + 0x18);
  this->f_8 /*u8 **/ = __vt__9MenuFrame;
  this->f_18 /*u32 **/ = 0x4052b4;
  (**(code **)(this->f_8 /*int **/ + 0x20))();
  return this;
}

// JP: 0x00278260  __dt__9MenuFrameFv  size 0xac
// MenuFrame::~MenuFrame()
int __dt__9MenuFrameFv(MenuFrame *this,short param_2)
{
  if (this != 0) {
    this->f_8 /*u8 **/ = __vt__9MenuFrame;
    this->f_18 /*u32 **/ = 0x4052b4;
    (**(code **)(this->f_8 /*int **/ + 0x1c))();
    __dt__10MenuPacketFv(this + 0x18,0);
    __dt__7MenuObjFv(this,0);
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

// JP: 0x00278310  Destroy__9MenuFrameFv  size 0x2c
// MenuFrame::Destroy()
void Destroy__9MenuFrameFv(MenuFrame *this)
{
  DestroyPacket__10MenuPacketFv(this + 0x18);
  return;
}

// JP: 0x00278340  Create__9MenuFrameFP10MenuWindowP8DrawRect  size 0x70
// MenuFrame::Create(MenuWindow*, DrawRect*)
void Create__9MenuFrameFP10MenuWindowP8DrawRect(MenuFrame *this,u32 menuWindow,u32 param_3)
{
  CreatePacket__10MenuPacketFUs(this + 0x18,0xe);
  this->f_10 /*u8 **/ = this->f_10 /*u8 **/ | 0x3f;
  this->f_11 /*u8 **/ = this->f_11 /*u8 **/ | 0x3f;
  this->f_2c /*u32 **/ = param_3;
  this->f_28 /*u32 **/ = menuWindow;
  return;
}

// JP: 0x002783b0  SetAlpha__9MenuFrameFUc  size 0x70
// MenuFrame::SetAlpha(unsigned char)
void SetAlpha__9MenuFrameFUc(MenuFrame *this,u8 param_2)
{
  ulong uVar1;
  this->f_33 /*u8 **/ = param_2;
  uVar1 = (ulong)this->f_11 /*u8 **/ & 0xffffffffffffffef | 0x10;
  this->f_11 /*char **/ = (char)uVar1;
  this->f_10 /*u8 **/ =
       this->f_10 /*u8 **/ & 0xef | (u8)((uint)((uVar1 << 0x3b) >> 0x3f) << 4);
  return;
}

// JP: 0x00278420  Update__9MenuFrameFiiUs  size 0x77c
// MenuFrame::Update(int, int, unsigned short)
void Update__9MenuFrameFiiUs(MenuFrame *this,short param_2,short param_3,u16 param_4)
{
  u32 *puVar1;
  u8 auVar2 [16];
  u8 auVar3 [16];
  u8 auVar4 [16];
  u8 auVar5 [16];
  u8 auVar6 [16];
  u8 auVar7 [16];
  u8 auVar8 [16];
  u8 auVar9 [16];
  u8 auVar10 [16];
  u8 auVar11 [16];
  u8 auVar12 [16];
  u8 auVar13 [16];
  u8 auVar14 [16];
  short sVar15;
  u8 in_zero_qw [16];
  short sVar16;
  ulong *puVar17;
  u64 in_v1_udw;
  u8 auVar18 [16];
  u8 auVar19 [16];
  u8 auVar20 [16];
  u64 in_a0_udw;
  u8 auVar21 [16];
  u8 auVar22 [16];
  u8 auVar23 [16];
  u8 auVar24 [16];
  u8 auVar25 [16];
  u8 *pbVar26;
  u64 in_a1_udw;
  u8 auVar27 [16];
  u8 auVar28 [16];
  u8 auVar29 [16];
  u8 auVar30 [16];
  u8 auVar31 [16];
  u8 auVar32 [16];
  u8 auVar33 [16];
  u8 auVar34 [16];
  u8 auVar35 [16];
  u8 auVar36 [16];
  u8 auVar37 [16];
  u64 in_a2_udw;
  u64 in_a3_udw;
  u64 in_t0_udw;
  u8 auVar38 [16];
  u8 auVar39 [16];
  u32 in_s0_udw;
  u32 in_register_0000010c;
  u8 bVar40;
  u32 in_s6_udw;
  u32 in_register_0000016c;
  puVar1 = *(u32 **)(this + (m_Env__8VIF1Prim & 1) * 4 + 0x1c);
  pbVar26 = (u8 *)(this + (m_Env__8VIF1Prim & 1) + 0x10);
  if ((*pbVar26 & 1) != 0) {
    *puVar1 = &DAT_1000000c;
    puVar1[3] = 0x5000000c;
    auVar21._8_8_ = in_a0_udw;
    auVar21._0_8_ = 0xa400000000000001;
    auVar18 = _pcpyld(in_zero_qw,auVar21);
    *(long *)(puVar1 + 4) = auVar18._0_8_;
    *(u64 *)(puVar1 + 6) = 0x5d5d5d5d10;
    auVar18._8_4_ = in_s0_udw;
    auVar18._0_8_ = 0x9400000000008001;
    auVar18._12_4_ = in_register_0000010c;
    auVar18 = _pcpyld(in_zero_qw,auVar18);
    *(long *)(puVar1 + 0x1c) = auVar18._0_8_;
    in_v1_udw = auVar18._8_8_;
    *(u64 *)(puVar1 + 0x1e) = 0x5d5d5d5d1;
    *(u64 *)(puVar1 + 8) = 0x146;
  }
  if ((long)((ulong)*pbVar26 << 0x3b) < 0) {
    bVar40 = this->f_33 /*u8 **/;
    if (this->f_28 /*int **/ != 0) {
      bVar40 = (u8)((uint)bVar40 * (uint)param_4 >> 0xf);
    }
    *(u8 *)(puVar1 + 10) = this->f_30 /*u8 **/;
    *(u8 *)((int)puVar1 + 0x29) = this->f_31 /*u8 **/;
    *(u8 *)((int)puVar1 + 0x2a) = this->f_32 /*u8 **/;
    *(u8 *)((int)puVar1 + 0x2b) = bVar40;
    *(u8 *)(puVar1 + 0x20) = this->f_34 /*u8 **/;
    *(u8 *)((int)puVar1 + 0x81) = this->f_35 /*u8 **/;
    *(u8 *)((int)puVar1 + 0x82) = this->f_36 /*u8 **/;
    *(u8 *)((int)puVar1 + 0x83) = bVar40;
  }
  if ((long)((ulong)*pbVar26 << 0x3c) < 0) {
    param_2 = (short)(int)(*this->f_2c /*float **/ * 16.0) + param_2;
    param_3 = (short)(int)(*(float *)(this->f_2c /*int **/ + 4) * 16.0) + param_3;
    sVar16 = (short)(int)(*(float *)(this->f_2c /*int **/ + 8) * 16.0) + param_2;
    sVar15 = (short)(int)(*(float *)(this->f_2c /*int **/ + 0xc) * 16.0) + param_3;
    puVar17 = (ulong *)(puVar1 + 0xc);
    *(short *)puVar17 = param_2 + -0x30;
    *(short *)((int)puVar1 + 0x32) = param_3 + -0x30;
    auVar19._8_8_ = in_v1_udw;
    auVar19._0_8_ = 0xffffffffffffffff;
    auVar38._8_8_ = in_t0_udw;
    auVar38._0_8_ = 0xffffffff;
    auVar18 = _pcpyld(auVar19,auVar38);
    auVar20._8_8_ = auVar18._8_8_;
    *puVar17 = *puVar17 & auVar18._0_8_ | 0x100000000;
    puVar17 = (ulong *)(puVar1 + 0xe);
    *(short *)puVar17 = param_2 + -0x10;
    *(short *)((int)puVar1 + 0x3a) = sVar15 + 0x20;
    auVar27._8_8_ = in_a1_udw;
    auVar27._0_8_ = 0xffffffff;
    auVar2._8_8_ = in_a2_udw;
    auVar2._0_8_ = 0xffffffffffffffff;
    auVar18 = _pcpyld(auVar2,auVar27);
    *puVar17 = *puVar17 & auVar18._0_8_ | 0x100000000;
    puVar17 = (ulong *)(puVar1 + 0x10);
    *(short *)puVar17 = sVar16;
    *(short *)((int)puVar1 + 0x42) = param_3 + -0x30;
    auVar28._8_8_ = auVar18._8_8_;
    auVar28._0_8_ = 0xffffffff;
    auVar3._8_8_ = in_a2_udw;
    auVar3._0_8_ = 0xffffffffffffffff;
    auVar18 = _pcpyld(auVar3,auVar28);
    *puVar17 = *puVar17 & auVar18._0_8_ | 0x100000000;
    puVar17 = (ulong *)(puVar1 + 0x12);
    *(short *)puVar17 = sVar16 + 0x20;
    *(short *)((int)puVar1 + 0x4a) = sVar15 + 0x20;
    auVar29._8_8_ = auVar18._8_8_;
    auVar29._0_8_ = 0xffffffff;
    auVar4._8_8_ = in_a2_udw;
    auVar4._0_8_ = 0xffffffffffffffff;
    auVar18 = _pcpyld(auVar4,auVar29);
    *puVar17 = *puVar17 & auVar18._0_8_ | 0x100000000;
    puVar17 = (ulong *)(puVar1 + 0x14);
    *(short *)puVar17 = param_2 + -0x10;
    *(short *)((int)puVar1 + 0x52) = param_3 + -0x30;
    auVar30._8_8_ = auVar18._8_8_;
    auVar30._0_8_ = 0xffffffff;
    auVar5._8_8_ = in_a2_udw;
    auVar5._0_8_ = 0xffffffffffffffff;
    auVar18 = _pcpyld(auVar5,auVar30);
    *puVar17 = *puVar17 & auVar18._0_8_ | 0x100000000;
    puVar17 = (ulong *)(puVar1 + 0x16);
    *(short *)puVar17 = sVar16;
    *(short *)((int)puVar1 + 0x5a) = param_3 + -0x10;
    auVar31._8_8_ = auVar18._8_8_;
    auVar31._0_8_ = 0xffffffff;
    auVar6._8_8_ = in_a2_udw;
    auVar6._0_8_ = 0xffffffffffffffff;
    auVar18 = _pcpyld(auVar6,auVar31);
    *puVar17 = *puVar17 & auVar18._0_8_ | 0x100000000;
    puVar17 = (ulong *)(puVar1 + 0x18);
    *(short *)puVar17 = param_2 + -0x10;
    *(short *)((int)puVar1 + 0x62) = sVar15;
    auVar32._8_8_ = auVar18._8_8_;
    auVar32._0_8_ = 0xffffffff;
    auVar7._8_8_ = in_a2_udw;
    auVar7._0_8_ = 0xffffffffffffffff;
    auVar18 = _pcpyld(auVar7,auVar32);
    *puVar17 = *puVar17 & auVar18._0_8_ | 0x100000000;
    puVar17 = (ulong *)(puVar1 + 0x1a);
    *(short *)puVar17 = sVar16;
    *(short *)((int)puVar1 + 0x6a) = sVar15 + 0x20;
    auVar33._8_8_ = auVar18._8_8_;
    auVar33._0_8_ = 0xffffffff;
    auVar8._8_8_ = in_a2_udw;
    auVar8._0_8_ = 0xffffffffffffffff;
    auVar18 = _pcpyld(auVar8,auVar33);
    *puVar17 = *puVar17 & auVar18._0_8_ | 0x100000000;
    puVar17 = (ulong *)(puVar1 + 0x22);
    *(short *)puVar17 = param_2 + -0x10;
    *(short *)((int)puVar1 + 0x8a) = param_3 + -0x10;
    auVar34._8_8_ = auVar18._8_8_;
    auVar22._8_8_ = in_a0_udw;
    auVar22._0_8_ = 0xffffffffffffffff;
    auVar20._0_8_ = 0xffffffff;
    auVar18 = _pcpyld(auVar22,auVar20);
    *puVar17 = *puVar17 & auVar18._0_8_ | 0x100000000;
    puVar17 = (ulong *)(puVar1 + 0x24);
    *(short *)puVar17 = param_2;
    *(short *)((int)puVar1 + 0x92) = sVar15;
    auVar34._0_8_ = 0xffffffff;
    auVar9._8_8_ = in_a2_udw;
    auVar9._0_8_ = 0xffffffffffffffff;
    auVar18 = _pcpyld(auVar9,auVar34);
    *puVar17 = *puVar17 & auVar18._0_8_ | 0x100000000;
    puVar17 = (ulong *)(puVar1 + 0x26);
    *(short *)puVar17 = sVar16 + 0x20;
    *(short *)((int)puVar1 + 0x9a) = param_3 + -0x20;
    auVar35._8_8_ = auVar18._8_8_;
    auVar35._0_8_ = 0xffffffff;
    auVar10._8_8_ = in_a2_udw;
    auVar10._0_8_ = 0xffffffffffffffff;
    auVar18 = _pcpyld(auVar10,auVar35);
    *puVar17 = *puVar17 & auVar18._0_8_ | 0x100000000;
    puVar17 = (ulong *)(puVar1 + 0x28);
    *(short *)puVar17 = sVar16 + 0x40;
    auVar36._8_8_ = auVar18._8_8_;
    *(short *)((int)puVar1 + 0xa2) = sVar15 + 0x30;
    auVar36._0_8_ = 0xffffffff;
    auVar11._8_8_ = in_a2_udw;
    auVar11._0_8_ = 0xffffffffffffffff;
    auVar18 = _pcpyld(auVar11,auVar36);
    *puVar17 = *puVar17 & auVar18._0_8_ | 0x100000000;
    puVar17 = (ulong *)(puVar1 + 0x2a);
    *(short *)puVar17 = param_2;
    *(short *)((int)puVar1 + 0xaa) = param_3 + -0x10;
    auVar23._8_8_ = in_a0_udw;
    auVar23._0_8_ = 0xffffffff;
    auVar14._8_4_ = in_s6_udw;
    auVar14._0_8_ = 0xffffffffffffffff;
    auVar14._12_4_ = in_register_0000016c;
    auVar18 = _pcpyld(auVar14,auVar23);
    *puVar17 = *puVar17 & auVar18._0_8_ | 0x100000000;
    puVar17 = (ulong *)(puVar1 + 0x2c);
    *(short *)puVar17 = sVar16;
    *(short *)((int)puVar1 + 0xb2) = param_3;
    auVar24._8_8_ = auVar18._8_8_;
    auVar12._8_8_ = in_a2_udw;
    auVar12._0_8_ = 0xffffffff;
    auVar13._8_8_ = in_a3_udw;
    auVar13._0_8_ = 0xffffffffffffffff;
    auVar18 = _pcpyld(auVar13,auVar12);
    *puVar17 = *puVar17 & auVar18._0_8_ | 0x100000000;
    puVar17 = (ulong *)(puVar1 + 0x2e);
    *(short *)puVar17 = param_2 + -0x20;
    *(short *)((int)puVar1 + 0xba) = sVar15 + 0x20;
    auVar37._8_8_ = auVar18._8_8_;
    auVar37._0_8_ = 0xffffffffffffffff;
    auVar24._0_8_ = 0xffffffff;
    auVar18 = _pcpyld(auVar37,auVar24);
    *puVar17 = *puVar17 & auVar18._0_8_ | 0x100000000;
    puVar17 = (ulong *)(puVar1 + 0x30);
    *(short *)puVar17 = sVar16 + 0x30;
    *(short *)((int)puVar1 + 0xc2) = sVar15 + 0x40;
    auVar25._8_8_ = auVar24._8_8_;
    auVar25._0_8_ = 0xffffffffffffffff;
    auVar39._8_8_ = in_t0_udw;
    auVar39._0_8_ = 0xffffffff;
    auVar18 = _pcpyld(auVar25,auVar39);
    *puVar17 = *puVar17 & auVar18._0_8_ | 0x100000000;
  }
  *pbVar26 = *pbVar26 & 0x80;
  return;
}

// JP: 0x00278ba0  Connect__9MenuFrameFP4_QWD  size 0x34
// MenuFrame::Connect(_QWD*)
void Connect__9MenuFrameFP4_QWD(MenuFrame *this,u32 param_2)
{
  ConnectPacket__10MenuPacketFP4_QWD(this + 0x18,param_2);
  return;
}

// JP: 0x00278be0  Clear__9MenuFrameFv  size 0xa8
// MenuFrame::Clear()
void Clear__9MenuFrameFv(MenuFrame *this)
{
  Clear__7MenuObjFv(this);
  ClearPacket__10MenuPacketFv(this + 0x18);
  this->f_28 /*u32 **/ = 0;
  this->f_2c /*u32 **/ = 0;
  this->f_32 /*u8 **/ = 100;
  this->f_31 /*u8 **/ = 100;
  this->f_30 /*u8 **/ = 100;
  this->f_36 /*u8 **/ = 0x1e;
  this->f_35 /*u8 **/ = 0x1e;
  this->f_34 /*u8 **/ = 0x1e;
  this->f_37 /*u8 **/ = 0x80;
  this->f_33 /*u8 **/ = 0x80;
  return;
}

// JP: 0x00278c90  @24@__dt__9MenuFrameFv  size 0x8
// @24@__dt__9MenuFrameFv
u32 * _24___dt__9MenuFrameFv(MenuFrame *this,short param_2)
{
  u32 *puVar1;
  puVar1 = this + -6;
  if (puVar1 != (u32 *)0x0) {
    this[-4] = __vt__9MenuFrame;
    *this = 0x4052b4;
    (**(code **)(this[-4] + 0x1c))();
    __dt__10MenuPacketFv(this,0);
    __dt__7MenuObjFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}
