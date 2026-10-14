/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x0028dbb0  __ct__17MenuWindowGeneralFv  size 0x98
// MenuWindowGeneral::MenuWindowGeneral()
int __ct__17MenuWindowGeneralFv(MenuWindowGeneral *this)
{
  __ct__16MenuWindowObjectFv(this);
  this->f_8 /*u8 **/ = __vt__17MenuWindowGeneral;
  __ct__11SendOnLocalFv(this + 0x1c);
  __construct_array(this + 0x4c,0x266140,0x2661a0,0x60,10);
  __ct__11MenuPolygonFv(this + 0x40c);
  (**(code **)(this->f_8 /*int **/ + 0x20))();
  return this;
}

// JP: 0x0028dc50  __dt__17MenuWindowGeneralFv  size 0xcc
// MenuWindowGeneral::~MenuWindowGeneral()
int __dt__17MenuWindowGeneralFv(MenuWindowGeneral *this,short param_2)
{
  if (this != 0) {
    this->f_8 /*u8 **/ = __vt__17MenuWindowGeneral;
    (**(code **)(this->f_8 /*int **/ + 0x1c))();
    __dt__11MenuPolygonFv(this + 0x40c,0xffffffffffffffff);
    __destroy_arr(this + 0x4c,0x2661a0,0x60,10);
    __dt__11SendOnLocalFv(this + 0x1c,0xffffffffffffffff);
    __dt__16MenuWindowObjectFv(this,0);
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

// JP: 0x0028dd20  Create__17MenuWindowGeneralFP10MenuWindow  size 0x134
// MenuWindowGeneral::Create(MenuWindow*)
void Create__17MenuWindowGeneralFP10MenuWindow(MenuWindowGeneral *this,u32 menuWindow)
{
  int iVar1;
  uint uVar2;
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi
            (this + 0x1c,0x4218b0,DAT_004218ac,1,0xffffffffffffffff);
  UpdatePacket__11SendOnLocalFv(this + 0x1c);
  iVar1 = this + 0x4c;
  uVar2 = 8;
  while( true ) {
    if (0x11 < (int)uVar2) break;
    SetData__9MenuSceneFUsP10MenuSprite(0x421600,uVar2 & 0xffff,iVar1);
    VCALL(iVar1, 0x38 /*SetOwner*/)(iVar1,menuWindow);
    *(u16 *)(iVar1 + 0x12) = *(u16 *)(iVar1 + 0x12) & 0xfc3f;
    uVar2 = uVar2 + 1;
    iVar1 = iVar1 + 0x60;
  }
  SetData__9MenuSceneFUsP11MenuPolygon(0x421600,1,this + 0x40c);
  (**(code **)(this->f_414 /*int **/ + 0x38))(this + 0x40c,menuWindow);
  this->f_18 /*u32 **/ = menuWindow;
  return;
}

// JP: 0x0028de60  SetAlpha__17MenuWindowGeneralFUc  size 0x90
// MenuWindowGeneral::SetAlpha(unsigned char)
void SetAlpha__17MenuWindowGeneralFUc(MenuWindowGeneral *this,u8 param_2)
{
  uint uVar1;
  for (uVar1 = this + 0x4c; uVar1 < this + 0x40cU; uVar1 = uVar1 + 0x60) {
    VCALL(uVar1, 0x2c /*SetAlpha*/)(uVar1,param_2);
  }
  (**(code **)(this->f_414 /*int **/ + 0x2c))(this + 0x40c,param_2);
  return;
}

// JP: 0x0028def0  Update__17MenuWindowGeneralFiiUs  size 0x558
// MenuWindowGeneral::Update(int, int, unsigned short)
/* WARNING: Removing unreachable block (ram,0x0028e07c) */
/* WARNING: Removing unreachable block (ram,0x0028e0c0) */
void Update__17MenuWindowGeneralFiiUs
               (MenuWindowGeneral *this,u32 param_2,u32 param_3,u16 param_4)
{
  u8 bVar1;
  int iVar2;
  uint uVar3;
  u8 *pbVar4;
  u32 uStack_4c;
  u32 uStack_48;
  pbVar4 = (u8 *)(this + (m_Env__8VIF1Prim & 1) + 0x10);
  if ((long)((ulong)*pbVar4 << 0x3c) < 0) {
    uStack_48 = *(float *)(this->f_18 /*int **/ + 0x6c) +
                (float)(int)*(short *)(DAT_0042163c + 0xf2);
    if (uStack_48 < 1.0) {
      uStack_48 = 0.0;
    }
    uStack_4c = *(float *)(this->f_18 /*int **/ + 0x70) +
                (float)(int)*(short *)(DAT_0042163c + 0x112);
    if (uStack_4c < 1.0) {
      uStack_4c = 0.0;
    }
    (**(code **)(this->f_414 /*int **/ + 0x28))
              ((float)*(u16 *)(DAT_0042163c + 0xf8) + uStack_48,
               (float)*(u16 *)(DAT_0042163c + 0xfa) + uStack_4c);
    iVar2 = this + 0x4c;
    for (uVar3 = 8; (int)uVar3 < 0xb; uVar3 = uVar3 + 1) {
      VCALL(iVar2, 0x24 /*SetPosition*/)
                (uStack_48 + (float)(int)*(short *)((uVar3 & 0xffff) * 0x20 + DAT_0042163c + 0x14),
                 *(u32 *)(iVar2 + 0x28));
      iVar2 = iVar2 + 0x60;
    }
    iVar2 = this + 0xac;
    for (uVar3 = 9; (int)uVar3 < 0xc; uVar3 = uVar3 + 1) {
      VCALL(iVar2, 0x24 /*SetPosition*/)
                (*(u32 *)(iVar2 + 0x24),
                 uStack_4c + (float)(int)*(short *)((uVar3 & 0xffff) * 0x20 + DAT_0042163c + 0x16));
      iVar2 = iVar2 + 0x60;
    }
    for (uVar3 = this + 0x28c; uVar3 < this + 0x34cU; uVar3 = uVar3 + 0x60) {
      VCALL(uVar3, 0x28 /*SetSize*/)(uStack_48,*(u32 *)(uVar3 + 0x30));
    }
    for (uVar3 = this + 0x34c; uVar3 < this + 0x40cU; uVar3 = uVar3 + 0x60) {
      VCALL(uVar3, 0x28 /*SetSize*/)(*(u32 *)(uVar3 + 0x2c),uStack_4c);
    }
    (**(code **)(this->f_2f4 /*int **/ + 0x24))
              (this->f_310 /*u32 **/,
               uStack_4c + (float)(int)*(short *)(DAT_0042163c + 0x1f6));
    (**(code **)(this->f_3b4 /*int **/ + 0x24))
              (uStack_48 + (float)(int)*(short *)(DAT_0042163c + 0x234),
               this->f_3d4 /*u32 **/);
  }
  for (uVar3 = this + 0x4c; uVar3 < this + 0x40cU; uVar3 = uVar3 + 0x60) {
    bVar1 = *pbVar4;
    *(u8 *)(uVar3 + 0x10) = *(u8 *)(uVar3 + 0x10) | bVar1;
    *(u8 *)(uVar3 + 0x11) = *(u8 *)(uVar3 + 0x11) | bVar1;
    VCALL(uVar3, 0x14 /*Update*/)(uVar3,param_2,param_3,param_4);
  }
  bVar1 = *pbVar4;
  this->f_41c /*u8 **/ = this->f_41c /*u8 **/ | bVar1;
  this->f_41d /*u8 **/ = this->f_41d /*u8 **/ | bVar1;
  (**(code **)(this->f_414 /*int **/ + 0x14))(this + 0x40c,param_2,param_3,param_4);
  *pbVar4 = *pbVar4 & 0x80;
  return;
}

// JP: 0x0028e450  Connect__17MenuWindowGeneralFP4_QWD  size 0xa0
// MenuWindowGeneral::Connect(_QWD*)
u32 Connect__17MenuWindowGeneralFP4_QWD(MenuWindowGeneral *this,u32 param_2)
{
  u32 uVar1;
  uint uVar2;
  u32 uStack_10;
  uVar1 = ConnectPacket__10MenuPacketFP4_QWD(this + 0x34,param_2);
  uStack_10 = ConnectPacket__10MenuPacketFP4_QWD(this + 0x448,uVar1);
  for (uVar2 = this + 0x4c; uVar2 < this + 0x40cU; uVar2 = uVar2 + 0x60) {
    uStack_10 = ConnectPacket__10MenuPacketFP4_QWD(uVar2 + 0x3c,uStack_10);
  }
  return uStack_10;
}

// JP: 0x0028e4f0  Destroy__17MenuWindowGeneralFv  size 0x94
// MenuWindowGeneral::Destroy()
void Destroy__17MenuWindowGeneralFv(MenuWindowGeneral *this)
{
  uint uVar1;
  (**(code **)(this->f_24 /*int **/ + 0x1c))();
  (**(code **)(this->f_414 /*int **/ + 0x1c))();
  for (uVar1 = this + 0x4c; uVar1 < this + 0x40cU; uVar1 = uVar1 + 0x60) {
    VCALL(uVar1, 0x1c /*Destroy*/)();
  }
  return;
}

// JP: 0x0028e590  Clear__17MenuWindowGeneralFv  size 0xac
// MenuWindowGeneral::Clear()
void Clear__17MenuWindowGeneralFv(MenuWindowGeneral *this)
{
  uint uVar1;
  Clear__7MenuObjFv(this);
  this->f_18 /*u32 **/ = 0;
  (**(code **)(this->f_24 /*int **/ + 0x20))();
  (**(code **)(this->f_414 /*int **/ + 0x20))();
  for (uVar1 = this + 0x4c; uVar1 < this + 0x40cU; uVar1 = uVar1 + 0x60) {
    VCALL(uVar1, 0x20 /*Clear*/)();
  }
  return;
}
