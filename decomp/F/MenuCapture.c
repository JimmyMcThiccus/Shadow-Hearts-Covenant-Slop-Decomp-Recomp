/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x002810f0  __ct__11MenuCaptureFv  size 0xa4
// MenuCapture::MenuCapture()
int __ct__11MenuCaptureFv(MenuCapture *this)
{
  __ct__8VIF1PrimFv(this);
  __ct__7CPolObjFv(this + 0x14);
  this->f_10 /*u8 **/ = __vt__11MenuCapture;
  this->f_28 /*u32 **/ = 0x405510;
  __ct__12RasterPacketFv(this + 0x30);
  this->f_50 /*u32 **/ = 0;
  this->f_54 /*u16 **/ = 0;
  this->f_56 /*u16 **/ = 0;
  this->f_58 /*u32 **/ = 0;
  this->f_5c /*u8 **/ = 0;
  this->f_5d /*u8 **/ = 0;
  this->f_5e /*u8 **/ = 0;
  return this;
}

// JP: 0x002811a0  __dt__11MenuCaptureFv  size 0xb4
// MenuCapture::~MenuCapture()
int __dt__11MenuCaptureFv(MenuCapture *this,short param_2)
{
  if (this != 0) {
    this->f_10 /*u8 **/ = __vt__11MenuCapture;
    this->f_28 /*u32 **/ = 0x405510;
    Release__11MenuCaptureFv(this);
    __dt__12RasterPacketFv(this + 0x30,0xffffffffffffffff);
    __dt__7CPolObjFv(this + 0x14,0);
    __dt__8VIF1PrimFv(this,0);
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

// JP: 0x00281260  Capture__11MenuCaptureFiss6GS_PSMUc  size 0x11c
// MenuCapture::Capture(int, short, short, GS_PSM, unsigned char)
void Capture__11MenuCaptureFiss6GS_PSMUc
               (MenuCapture *this,u32 param_2,short param_3,short param_4,u32 param_5,
               u8 param_6)
{
  int iVar1;
  u32 uVar2;
  iVar1 = GetBitCount__F6GS_PSM(param_5);
  iVar1 = (int)param_3 * (int)param_4 * iVar1;
  if (iVar1 < 0) {
    iVar1 = iVar1 + 7;
  }
  uVar2 = __nwa__FUi(iVar1 >> 3);
  this->f_50 /*u32 **/ = uVar2;
  this->f_54 /*short **/ = param_3;
  this->f_56 /*short **/ = param_4;
  this->f_58 /*u32 **/ = param_5;
  this->f_5c /*u8 **/ = param_6;
  SetRaster__12RasterPacketF6GS_PSMUiUiUiUi
            (this + 0x30,param_5,param_3,param_4,this->f_50 /*u32 **/,
             sm_freeBlock__7MenuObj);
  AddOT__5WorldFiP8VIF1Prim(0x42bf10,param_2,this);
  this->f_5e /*u8 **/ = 1;
  return;
}

// JP: 0x00281380  Release__11MenuCaptureFv  size 0xc4
// MenuCapture::Release()
void Release__11MenuCaptureFv(MenuCapture *this)
{
  if (*this != 0) {
    __dla__FPv(*this);
    *this = 0;
  }
  if (this[0x14] != 0) {
    __dla__FPv(this[0x14]);
    this[0x14] = 0;
  }
  Destroy__12RasterPacketFv(this + 0xc);
  *(u16 *)((int)this + 0x56) = 0;
  this->f_15 /*u16 **/ = 0;
  this[0x16] = 0x31;
  this->f_17 /*u8 **/ = 0x80;
  *(u8 *)((int)this + 0x5e) = 0;
  *(u8 *)((int)this + 0x5d) = 0;
  return;
}

// JP: 0x00281450  getPacket__11MenuCaptureFv  size 0x320
// MenuCapture::getPacket()
u32 getPacket__11MenuCaptureFv(MenuCapture *this)
{
  u8 uVar1;
  u32 uVar2;
  int iVar3;
  int iVar4;
  u32 *puVar5;
  ulong uVar6;
  if (*(char *)(camera__4CApp + 0x394) == '\0') {
    uVar6 = 0xe00;
  }
  else {
    uVar6 = 0;
  }
  uVar2 = __nwa__FUi(0xc0);
  *this = uVar2;
  memset((void *)*this,0,0xc0);
  puVar5 = (u32 *)*this;
  *puVar5 = &DAT_10000009;
  puVar5[2] = 0x10000000;
  puVar5[3] = 0x50000009;
  *(u64 *)(puVar5 + 4) = 0x1000000000000003;
  *(u64 *)(puVar5 + 6) = 0xe;
  iVar3 = (int)this->f_15 /*short **/;
  if (this->f_15 /*short **/ < 0) {
    iVar3 = iVar3 + 0x3f;
  }
  *(ulong *)(puVar5 + 8) = (long)(iVar3 >> 6) << 0x10 | 0x150U | (long)(int)this[0x16] << 0x18;
  *(u64 *)(puVar5 + 10) = 0x4c;
  *(u64 *)(puVar5 + 0xc) = 0x3000c;
  *(u64 *)(puVar5 + 0xe) = 0x47;
  iVar3 = GetCoefficient__Fi(0x200);
  iVar4 = GetCoefficient__Fi(0x1c0);
  *(ulong *)(puVar5 + 0x10) = uVar6 | 0x120000 | (long)iVar3 << 0x1a | (long)iVar4 << 0x1e;
  *(u64 *)(puVar5 + 0x12) = 6;
  *(u64 *)(puVar5 + 0x14) = 0x6400000000000001;
  *(u64 *)(puVar5 + 0x16) = 0x53d310;
  *(u64 *)(puVar5 + 0x18) = 0x116;
  uVar1 = this->f_17 /*u8 **/;
  *(u8 *)((int)puVar5 + 0x6a) = uVar1;
  *(u8 *)((int)puVar5 + 0x69) = uVar1;
  *(u8 *)(puVar5 + 0x1a) = uVar1;
  *(u8 *)((int)puVar5 + 0x6b) = 0x80;
  *(u16 *)(puVar5 + 0x1c) = 8;
  *(u16 *)((int)puVar5 + 0x72) = 8;
  *(u16 *)(puVar5 + 0x1e) = 0x7000;
  *(u16 *)((int)puVar5 + 0x7a) = 0x7200;
  puVar5[0x1f] = 1;
  *(u16 *)(puVar5 + 0x20) = 0x2008;
  *(u16 *)((int)puVar5 + 0x82) = 0x1c08;
  *(short *)(puVar5 + 0x22) = (this->f_15 /*short **/ + 0x700) * 0x10;
  *(short *)((int)puVar5 + 0x8a) = (*(short *)((int)this + 0x56) + 0x720) * 0x10;
  puVar5[0x23] = 1;
  *(u64 *)(puVar5 + 0x24) = 0x1000000000008001;
  *(u64 *)(puVar5 + 0x26) = 0xe;
  puVar5[0x28] = 0x30000001;
  puVar5[0x29] = camera__4CApp + 0x50;
  puVar5[0x2b] = 0x50000001;
  puVar5[0x2c] = 0x70000000;
  puVar5[0x2e] = &DAT_11000000;
  puVar5 = this;
  if (this != (u32 *)0x0) {
    puVar5 = this + 5;
  }
  Entry__7CPollerFP7CPolObjib(app__4CApp + 0x60,puVar5,0xc0,0);
  *(u8 *)((int)this + 0x5e) = 1;
  return *this;
}

// JP: 0x00281770  Polling__11MenuCaptureFv  size 0x2f0
// MenuCapture::Polling()
u32 Polling__11MenuCaptureFv(MenuCapture *this)
{
  uint uVar1;
  u32 uVar2;
  short sVar3;
  short sVar4;
  short sVar5;
  int iVar6;
  short sVar7;
  int iVar8;
  u8 auStack_80 [112];
  int *piStack_10;
  piStack_10 = this;
  GetTimer__7SysToolFv();
  sVar7 = 0;
  iVar8 = piStack_10[0x14];
  iVar6 = GetBitCount__F6GS_PSM(piStack_10[0x16]);
  iVar6 = (short)piStack_10[0x15] * iVar6;
  if (iVar6 < 0) {
    iVar6 = iVar6 + 7;
  }
  sVar3 = (short)(iVar6 >> 3);
  if (sVar3 == 0) {
    trap(7);
  }
  sVar4 = (short)(0x7fff0 / (int)sVar3);
  DmaSync__6DmaManFii(1,0);
  uVar2 = REG_DMAC_1_VIF1_ASR0;
  uVar1 = REG_DMAC_1_VIF1_CHCR;
  REG_DMAC_1_VIF1_CHCR = 0;
  for (; sVar7 < *(short *)((int)piStack_10 + 0x56); sVar7 = sVar7 + sVar5) {
    sVar5 = sVar4;
    if ((long)((int)*(short *)((int)piStack_10 + 0x56) - (int)sVar7) < (long)sVar4) {
      sVar5 = *(short *)((int)piStack_10 + 0x56) - sVar7;
    }
    iVar6 = (int)(short)piStack_10[0x15];
    if ((short)piStack_10[0x15] < 0) {
      iVar6 = iVar6 + 0x3f;
    }
    sceGsSetDefStoreImage
              (auStack_80,0x2a00,(short)(iVar6 >> 6),(short)piStack_10[0x16],0,sVar7,
               (short)piStack_10[0x15],sVar5);
    FlushCache(0);
    sceGsExecStoreImage(auStack_80,iVar8);
    iVar8 = iVar8 + (int)sVar3 * (int)sVar5;
  }
  REG_DMAC_1_VIF1_CHCR = 0x41;
  DmaSync__6DmaManFii(1,0);
  if ((uVar1 & 0x30) != 0) {
    DmaSend__6DmaManFiPv(1,uVar2);
  }
  if (*piStack_10 != 0) {
    __dla__FPv(*piStack_10);
    *piStack_10 = 0;
  }
  ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,piStack_10);
  return 1;
}

// JP: 0x00281a60  @20@Polling__11MenuCaptureFv  size 0x8
// @20@Polling__11MenuCaptureFv
u32 _20_Polling__11MenuCaptureFv(MenuCapture *this)
{
  uint uVar1;
  u32 uVar2;
  short sVar3;
  short sVar4;
  short sVar5;
  int iVar6;
  short sVar7;
  int iVar8;
  u8 auStack_80 [112];
  int *piStack_10;
  piStack_10 = (int *)(this + -0x14);
  GetTimer__7SysToolFv();
  sVar7 = 0;
  iVar8 = piStack_10[0x14];
  iVar6 = GetBitCount__F6GS_PSM(piStack_10[0x16]);
  iVar6 = (short)piStack_10[0x15] * iVar6;
  if (iVar6 < 0) {
    iVar6 = iVar6 + 7;
  }
  sVar3 = (short)(iVar6 >> 3);
  if (sVar3 == 0) {
    trap(7);
  }
  sVar4 = (short)(0x7fff0 / (int)sVar3);
  DmaSync__6DmaManFii(1,0);
  uVar2 = REG_DMAC_1_VIF1_ASR0;
  uVar1 = REG_DMAC_1_VIF1_CHCR;
  REG_DMAC_1_VIF1_CHCR = 0;
  for (; sVar7 < *(short *)((int)piStack_10 + 0x56); sVar7 = sVar7 + sVar5) {
    sVar5 = sVar4;
    if ((long)((int)*(short *)((int)piStack_10 + 0x56) - (int)sVar7) < (long)sVar4) {
      sVar5 = *(short *)((int)piStack_10 + 0x56) - sVar7;
    }
    iVar6 = (int)(short)piStack_10[0x15];
    if ((short)piStack_10[0x15] < 0) {
      iVar6 = iVar6 + 0x3f;
    }
    sceGsSetDefStoreImage
              (auStack_80,0x2a00,(short)(iVar6 >> 6),(short)piStack_10[0x16],0,sVar7,
               (short)piStack_10[0x15],sVar5);
    FlushCache(0);
    sceGsExecStoreImage(auStack_80,iVar8);
    iVar8 = iVar8 + (int)sVar3 * (int)sVar5;
  }
  REG_DMAC_1_VIF1_CHCR = 0x41;
  DmaSync__6DmaManFii(1,0);
  if ((uVar1 & 0x30) != 0) {
    DmaSend__6DmaManFiPv(1,uVar2);
  }
  if (*piStack_10 != 0) {
    __dla__FPv(*piStack_10);
    *piStack_10 = 0;
  }
  ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,piStack_10);
  return 1;
}

// JP: 0x00281a70  @20@__dt__11MenuCaptureFv  size 0x8
// @20@__dt__11MenuCaptureFv
int _20___dt__11MenuCaptureFv(MenuCapture *this,short param_2)
{
  int iVar1;
  iVar1 = this + -0x14;
  if (iVar1 != 0) {
    *(u8 **)(this + -4) = __vt__11MenuCapture;
    this->f_14 /*u32 **/ = 0x405510;
    Release__11MenuCaptureFv(iVar1);
    __dt__12RasterPacketFv(this + 0x1c,0xffffffffffffffff);
    __dt__7CPolObjFv(this,0);
    __dt__8VIF1PrimFv(iVar1,0);
    if (0 < param_2) {
      __dl__FPv(iVar1);
    }
  }
  return iVar1;
}
