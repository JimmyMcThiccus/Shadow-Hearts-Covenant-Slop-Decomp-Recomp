/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x00288390  __ct__14MenuWindowNoteFv  size 0x88
// MenuWindowNote::MenuWindowNote()
int __ct__14MenuWindowNoteFv(MenuWindowNote *this)
{
  __ct__16MenuWindowObjectFv(this);
  this->f_8 /*u8 **/ = __vt__14MenuWindowNote;
  __ct__11SendOnLocalFv(this + 0x1c);
  __construct_array(this + 0x4c,0x266140,0x2661a0,0x60,7);
  (**(code **)(this->f_8 /*int **/ + 0x20))();
  return this;
}

// JP: 0x00288420  __dt__14MenuWindowNoteFv  size 0xbc
// MenuWindowNote::~MenuWindowNote()
int __dt__14MenuWindowNoteFv(MenuWindowNote *this,short param_2)
{
  if (this != 0) {
    this->f_8 /*u8 **/ = __vt__14MenuWindowNote;
    (**(code **)(this->f_8 /*int **/ + 0x1c))();
    __destroy_arr(this + 0x4c,0x2661a0,0x60,7);
    __dt__11SendOnLocalFv(this + 0x1c,0xffffffffffffffff);
    __dt__16MenuWindowObjectFv(this,0);
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

// JP: 0x002884e0  Create__14MenuWindowNoteFP10MenuWindow  size 0xdc
// MenuWindowNote::Create(MenuWindow*)
void Create__14MenuWindowNoteFP10MenuWindow(MenuWindowNote *this,u32 menuWindow)
{
  uint uVar1;
  int iVar2;
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi
            (this + 0x1c,0x4218b0,DAT_004218ac,1,0xffffffffffffffff);
  UpdatePacket__11SendOnLocalFv(this + 0x1c);
  iVar2 = this + 0x4c;
  for (uVar1 = 0; (int)uVar1 < 7; uVar1 = uVar1 + 1) {
    SetData__9MenuSceneFUsP10MenuSprite(0x421600,uVar1 & 0xffff,iVar2);
    VCALL(iVar2, 0x38 /*SetOwner*/)(iVar2,menuWindow);
    iVar2 = iVar2 + 0x60;
  }
  this->f_18 /*u32 **/ = menuWindow;
  return;
}

// JP: 0x002885c0  SetAlpha__14MenuWindowNoteFUc  size 0x74
// MenuWindowNote::SetAlpha(unsigned char)
void SetAlpha__14MenuWindowNoteFUc(MenuWindowNote *this,u8 param_2)
{
  uint uVar1;
  for (uVar1 = this + 0x4c; uVar1 < this + 0x2ecU; uVar1 = uVar1 + 0x60) {
    VCALL(uVar1, 0x2c /*SetAlpha*/)(uVar1,param_2);
  }
  return;
}

// JP: 0x00288640  Update__14MenuWindowNoteFiiUs  size 0x2c4
// MenuWindowNote::Update(int, int, unsigned short)
/* WARNING: Removing unreachable block (ram,0x0028874c) */
void Update__14MenuWindowNoteFiiUs
               (MenuWindowNote *this,u32 param_2,u32 param_3,u16 param_4)
{
  u8 bVar1;
  int iVar2;
  uint uVar3;
  u8 *pbVar4;
  u32 uStack_48;
  pbVar4 = (u8 *)(this + (m_Env__8VIF1Prim & 1) + 0x10);
  if ((long)((ulong)*pbVar4 << 0x3c) < 0) {
    uStack_48 = *(float *)(this->f_18 /*int **/ + 0x6c) + (float)(int)this->f_60 /*short **/
    ;
    if (uStack_48 < 1.0) {
      uStack_48 = 0.0;
    }
    (**(code **)(this->f_54 /*int **/ + 0x28))
              (uStack_48 + (float)*(u16 *)(DAT_0042163c + 0x18),this->f_7c /*u32 **/);
    iVar2 = this + 0x16c;
    for (uVar3 = 3; (int)uVar3 < 5; uVar3 = uVar3 + 1) {
      VCALL(iVar2, 0x24 /*SetPosition*/)
                (uStack_48 + (float)(int)*(short *)((uVar3 & 0xffff) * 0x20 + DAT_0042163c + 0x14),
                 *(u32 *)(iVar2 + 0x28));
      iVar2 = iVar2 + 0x60;
    }
    for (uVar3 = this + 0x22c; uVar3 < this + 0x2ecU; uVar3 = uVar3 + 0x60) {
      VCALL(uVar3, 0x28 /*SetSize*/)(uStack_48,*(u32 *)(uVar3 + 0x30));
    }
  }
  for (uVar3 = this + 0x4c; uVar3 < this + 0x2ecU; uVar3 = uVar3 + 0x60) {
    bVar1 = *pbVar4;
    *(u8 *)(uVar3 + 0x10) = *(u8 *)(uVar3 + 0x10) | bVar1;
    *(u8 *)(uVar3 + 0x11) = *(u8 *)(uVar3 + 0x11) | bVar1;
    VCALL(uVar3, 0x14 /*Update*/)(uVar3,param_2,param_3,param_4);
  }
  *pbVar4 = *pbVar4 & 0x80;
  return;
}

// JP: 0x00288910  Connect__14MenuWindowNoteFP4_QWD  size 0x88
// MenuWindowNote::Connect(_QWD*)
u32 Connect__14MenuWindowNoteFP4_QWD(MenuWindowNote *this,u32 param_2)
{
  uint uVar1;
  u32 uStack_10;
  uStack_10 = ConnectPacket__10MenuPacketFP4_QWD(this + 0x34,param_2);
  for (uVar1 = this + 0x4c; uVar1 < this + 0x2ecU; uVar1 = uVar1 + 0x60) {
    uStack_10 = ConnectPacket__10MenuPacketFP4_QWD(uVar1 + 0x3c,uStack_10);
  }
  return uStack_10;
}

// JP: 0x002889a0  Destroy__14MenuWindowNoteFv  size 0x7c
// MenuWindowNote::Destroy()
void Destroy__14MenuWindowNoteFv(MenuWindowNote *this)
{
  uint uVar1;
  (**(code **)(this->f_24 /*int **/ + 0x1c))();
  for (uVar1 = this + 0x4c; uVar1 < this + 0x2ecU; uVar1 = uVar1 + 0x60) {
    VCALL(uVar1, 0x1c /*Destroy*/)();
  }
  return;
}

// JP: 0x00288a20  Clear__14MenuWindowNoteFv  size 0x94
// MenuWindowNote::Clear()
void Clear__14MenuWindowNoteFv(MenuWindowNote *this)
{
  uint uVar1;
  Clear__7MenuObjFv(this);
  this->f_18 /*u32 **/ = 0;
  (**(code **)(this->f_24 /*int **/ + 0x20))();
  for (uVar1 = this + 0x4c; uVar1 < this + 0x2ecU; uVar1 = uVar1 + 0x60) {
    VCALL(uVar1, 0x20 /*Clear*/)();
  }
  return;
}
