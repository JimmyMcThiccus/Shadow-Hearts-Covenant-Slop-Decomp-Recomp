/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x00290cb0  __ct__17MenuWindowCompactFv  size 0x88
// MenuWindowCompact::MenuWindowCompact()
int __ct__17MenuWindowCompactFv(MenuWindowCompact *this)
{
  __ct__16MenuWindowObjectFv(this);
  this->f_8 /*u8 **/ = __vt__17MenuWindowCompact;
  __ct__11SendOnLocalFv(this + 0x1c);
  __construct_array(this + 0x4c,0x266140,0x2661a0,0x60,5);
  (**(code **)(this->f_8 /*int **/ + 0x20))();
  return this;
}

// JP: 0x00290d40  __dt__17MenuWindowCompactFv  size 0xbc
// MenuWindowCompact::~MenuWindowCompact()
int __dt__17MenuWindowCompactFv(MenuWindowCompact *this,short param_2)
{
  if (this != 0) {
    this->f_8 /*u8 **/ = __vt__17MenuWindowCompact;
    (**(code **)(this->f_8 /*int **/ + 0x1c))();
    __destroy_arr(this + 0x4c,0x2661a0,0x60,5);
    __dt__11SendOnLocalFv(this + 0x1c,0xffffffffffffffff);
    __dt__16MenuWindowObjectFv(this,0);
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

// JP: 0x00290e00  Create__17MenuWindowCompactFP10MenuWindow  size 0xe4
// MenuWindowCompact::Create(MenuWindow*)
void Create__17MenuWindowCompactFP10MenuWindow(MenuWindowCompact *this,u32 menuWindow)
{
  int iVar1;
  int iVar2;
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi
            (this + 0x1c,0x4218b0,DAT_004218ac,1,0xffffffffffffffff);
  UpdatePacket__11SendOnLocalFv(this + 0x1c);
  iVar2 = this + 0x4c;
  for (iVar1 = 0; iVar1 < 5; iVar1 = iVar1 + 1) {
    SetData__9MenuSceneFUsP10MenuSprite(0x421600,iVar1 + 0x18U & 0xffff,iVar2);
    VCALL(iVar2, 0x38 /*SetOwner*/)(iVar2,menuWindow);
    iVar2 = iVar2 + 0x60;
  }
  this->f_18 /*u32 **/ = menuWindow;
  return;
}

// JP: 0x00290ef0  SetAlpha__17MenuWindowCompactFUc  size 0x74
// MenuWindowCompact::SetAlpha(unsigned char)
void SetAlpha__17MenuWindowCompactFUc(MenuWindowCompact *this,u8 param_2)
{
  uint uVar1;
  for (uVar1 = this + 0x4c; uVar1 < this + 0x22cU; uVar1 = uVar1 + 0x60) {
    VCALL(uVar1, 0x2c /*SetAlpha*/)(uVar1,param_2);
  }
  return;
}

// JP: 0x00290f70  Update__17MenuWindowCompactFiiUs  size 0x284
// MenuWindowCompact::Update(int, int, unsigned short)
/* WARNING: Removing unreachable block (ram,0x00291070) */
void Update__17MenuWindowCompactFiiUs
               (MenuWindowCompact *this,u32 param_2,u32 param_3,u16 param_4)
{
  u8 bVar1;
  uint uVar2;
  u8 *pbVar3;
  u32 uStack_48;
  pbVar3 = (u8 *)(this + (m_Env__8VIF1Prim & 1) + 0x10);
  if ((long)((ulong)*pbVar3 << 0x3c) < 0) {
    uStack_48 = *(float *)(this->f_18 /*int **/ + 0x6c) + (float)(int)this->f_60 /*short **/
    ;
    if (uStack_48 < 1.0) {
      uStack_48 = 0.0;
    }
    (**(code **)(this->f_54 /*int **/ + 0x28))
              (uStack_48 + (float)*(u16 *)(DAT_0042163c + 0x318),this->f_7c /*u32 **/)
    ;
    (**(code **)(this->f_114 /*int **/ + 0x24))
              (uStack_48 + (float)(int)*(short *)(DAT_0042163c + 0x354),
               this->f_134 /*u32 **/);
    for (uVar2 = this + 0x16c; uVar2 < this + 0x22cU; uVar2 = uVar2 + 0x60) {
      VCALL(uVar2, 0x28 /*SetSize*/)(uStack_48,*(u32 *)(uVar2 + 0x30));
    }
  }
  for (uVar2 = this + 0x4c; uVar2 < this + 0x22cU; uVar2 = uVar2 + 0x60) {
    bVar1 = *pbVar3;
    *(u8 *)(uVar2 + 0x10) = *(u8 *)(uVar2 + 0x10) | bVar1;
    *(u8 *)(uVar2 + 0x11) = *(u8 *)(uVar2 + 0x11) | bVar1;
    VCALL(uVar2, 0x14 /*Update*/)(uVar2,param_2,param_3,param_4);
  }
  *pbVar3 = *pbVar3 & 0x80;
  return;
}

// JP: 0x00291200  Connect__17MenuWindowCompactFP4_QWD  size 0x88
// MenuWindowCompact::Connect(_QWD*)
u32 Connect__17MenuWindowCompactFP4_QWD(MenuWindowCompact *this,u32 param_2)
{
  uint uVar1;
  u32 uStack_10;
  uStack_10 = ConnectPacket__10MenuPacketFP4_QWD(this + 0x34,param_2);
  for (uVar1 = this + 0x4c; uVar1 < this + 0x22cU; uVar1 = uVar1 + 0x60) {
    uStack_10 = ConnectPacket__10MenuPacketFP4_QWD(uVar1 + 0x3c,uStack_10);
  }
  return uStack_10;
}

// JP: 0x00291290  Destroy__17MenuWindowCompactFv  size 0x7c
// MenuWindowCompact::Destroy()
void Destroy__17MenuWindowCompactFv(MenuWindowCompact *this)
{
  uint uVar1;
  (**(code **)(this->f_24 /*int **/ + 0x1c))();
  for (uVar1 = this + 0x4c; uVar1 < this + 0x22cU; uVar1 = uVar1 + 0x60) {
    VCALL(uVar1, 0x1c /*Destroy*/)();
  }
  return;
}

// JP: 0x00291310  Clear__17MenuWindowCompactFv  size 0x94
// MenuWindowCompact::Clear()
void Clear__17MenuWindowCompactFv(MenuWindowCompact *this)
{
  uint uVar1;
  Clear__7MenuObjFv(this);
  this->f_18 /*u32 **/ = 0;
  (**(code **)(this->f_24 /*int **/ + 0x20))();
  for (uVar1 = this + 0x4c; uVar1 < this + 0x22cU; uVar1 = uVar1 + 0x60) {
    VCALL(uVar1, 0x20 /*Clear*/)();
  }
  return;
}
