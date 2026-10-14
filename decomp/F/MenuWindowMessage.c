/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x00287bc0  __ct__17MenuWindowMessageFv  size 0x98
// MenuWindowMessage::MenuWindowMessage()
int __ct__17MenuWindowMessageFv(MenuWindowMessage *this)
{
  __ct__16MenuWindowObjectFv(this);
  this->f_8 /*u8 **/ = __vt__17MenuWindowMessage;
  __ct__11SendOnLocalFv(this + 0x1c);
  __construct_array(this + 0x4c,0x266140,0x2661a0,0x60,4);
  __ct__11MenuPolygonFv(this + 0x1cc);
  (**(code **)(this->f_8 /*int **/ + 0x20))();
  return this;
}

// JP: 0x00287c60  __dt__17MenuWindowMessageFv  size 0xcc
// MenuWindowMessage::~MenuWindowMessage()
int __dt__17MenuWindowMessageFv(MenuWindowMessage *this,short param_2)
{
  if (this != 0) {
    this->f_8 /*u8 **/ = __vt__17MenuWindowMessage;
    (**(code **)(this->f_8 /*int **/ + 0x1c))();
    __dt__11MenuPolygonFv(this + 0x1cc,0xffffffffffffffff);
    __destroy_arr(this + 0x4c,0x2661a0,0x60,4);
    __dt__11SendOnLocalFv(this + 0x1c,0xffffffffffffffff);
    __dt__16MenuWindowObjectFv(this,0);
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

// JP: 0x00287d30  Create__17MenuWindowMessageFP10MenuWindow  size 0x114
// MenuWindowMessage::Create(MenuWindow*)
void Create__17MenuWindowMessageFP10MenuWindow(MenuWindowMessage *this,u32 menuWindow)
{
  uint uVar1;
  int iVar2;
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi
            (this + 0x1c,0x421930,DAT_0042192c,1,0xffffffffffffffff);
  UpdatePacket__11SendOnLocalFv(this + 0x1c);
  iVar2 = this + 0x4c;
  uVar1 = 0x14;
  while( true ) {
    if (0x17 < (int)uVar1) break;
    SetData__9MenuSceneFUsP10MenuSprite(0x421600,uVar1 & 0xffff,iVar2);
    VCALL(iVar2, 0x38 /*SetOwner*/)(iVar2,menuWindow);
    uVar1 = uVar1 + 1;
    iVar2 = iVar2 + 0x60;
  }
  SetData__9MenuSceneFUsP11MenuPolygon(0x421600,0,this + 0x1cc);
  (**(code **)(this->f_1d4 /*int **/ + 0x38))(this + 0x1cc,menuWindow);
  this->f_18 /*u32 **/ = menuWindow;
  return;
}

// JP: 0x00287e50  SetAlpha__17MenuWindowMessageFUc  size 0x90
// MenuWindowMessage::SetAlpha(unsigned char)
void SetAlpha__17MenuWindowMessageFUc(MenuWindowMessage *this,u8 param_2)
{
  uint uVar1;
  for (uVar1 = this + 0x4c; uVar1 < this + 0x1ccU; uVar1 = uVar1 + 0x60) {
    VCALL(uVar1, 0x2c /*SetAlpha*/)(uVar1,param_2);
  }
  (**(code **)(this->f_1d4 /*int **/ + 0x2c))(this + 0x1cc,param_2);
  return;
}

// JP: 0x00287ee0  Update__17MenuWindowMessageFiiUs  size 0x2b4
// MenuWindowMessage::Update(int, int, unsigned short)
void Update__17MenuWindowMessageFiiUs
               (MenuWindowMessage *this,u32 param_2,u32 param_3,u16 param_4)
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
    (**(code **)(this->f_1d4 /*int **/ + 0x28))
              (uStack_48 + (float)(int)this->f_1ee /*short **/,this->f_1fc /*u32 **/)
    ;
    (**(code **)(this->f_b4 /*int **/ + 0x24))
              (uStack_48 + (float)(int)*(short *)(DAT_0042163c + 0x2b4),
               this->f_d4 /*u32 **/);
    for (uVar2 = this + 0x10c; uVar2 < this + 0x1ccU; uVar2 = uVar2 + 0x60) {
      VCALL(uVar2, 0x28 /*SetSize*/)(uStack_48,*(u32 *)(uVar2 + 0x30));
    }
  }
  for (uVar2 = this + 0x4c; uVar2 < this + 0x1ccU; uVar2 = uVar2 + 0x60) {
    bVar1 = *pbVar3;
    *(u8 *)(uVar2 + 0x10) = *(u8 *)(uVar2 + 0x10) | bVar1;
    *(u8 *)(uVar2 + 0x11) = *(u8 *)(uVar2 + 0x11) | bVar1;
    VCALL(uVar2, 0x14 /*Update*/)(uVar2,param_2,param_3,param_4);
  }
  bVar1 = *pbVar3;
  this->f_1dc /*u8 **/ = this->f_1dc /*u8 **/ | bVar1;
  this->f_1dd /*u8 **/ = this->f_1dd /*u8 **/ | bVar1;
  (**(code **)(this->f_1d4 /*int **/ + 0x14))(this + 0x1cc,param_2,param_3,param_4);
  *pbVar3 = *pbVar3 & 0x80;
  return;
}

// JP: 0x002881a0  Connect__17MenuWindowMessageFP4_QWD  size 0xa0
// MenuWindowMessage::Connect(_QWD*)
u32 Connect__17MenuWindowMessageFP4_QWD(MenuWindowMessage *this,u32 param_2)
{
  u32 uVar1;
  uint uVar2;
  u32 uStack_10;
  uVar1 = ConnectPacket__10MenuPacketFP4_QWD(this + 0x208,param_2);
  uStack_10 = ConnectPacket__10MenuPacketFP4_QWD(this + 0x34,uVar1);
  for (uVar2 = this + 0x4c; uVar2 < this + 0x1ccU; uVar2 = uVar2 + 0x60) {
    uStack_10 = ConnectPacket__10MenuPacketFP4_QWD(uVar2 + 0x3c,uStack_10);
  }
  return uStack_10;
}

// JP: 0x00288240  Destroy__17MenuWindowMessageFv  size 0x94
// MenuWindowMessage::Destroy()
void Destroy__17MenuWindowMessageFv(MenuWindowMessage *this)
{
  uint uVar1;
  (**(code **)(this->f_24 /*int **/ + 0x1c))();
  for (uVar1 = this + 0x4c; uVar1 < this + 0x1ccU; uVar1 = uVar1 + 0x60) {
    VCALL(uVar1, 0x1c /*Destroy*/)();
  }
  (**(code **)(this->f_1d4 /*int **/ + 0x1c))();
  return;
}

// JP: 0x002882e0  Clear__17MenuWindowMessageFv  size 0xac
// MenuWindowMessage::Clear()
void Clear__17MenuWindowMessageFv(MenuWindowMessage *this)
{
  uint uVar1;
  Clear__7MenuObjFv(this);
  this->f_18 /*u32 **/ = 0;
  (**(code **)(this->f_24 /*int **/ + 0x20))();
  for (uVar1 = this + 0x4c; uVar1 < this + 0x1ccU; uVar1 = uVar1 + 0x60) {
    VCALL(uVar1, 0x20 /*Clear*/)();
  }
  (**(code **)(this->f_1d4 /*int **/ + 0x20))();
  return;
}
