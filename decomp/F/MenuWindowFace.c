/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x002871b0  __ct__14MenuWindowFaceFv  size 0x70
// MenuWindowFace::MenuWindowFace()
int __ct__14MenuWindowFaceFv(MenuWindowFace *this)
{
  __ct__16MenuWindowObjectFv(this);
  this->f_8 /*u8 **/ = __vt__14MenuWindowFace;
  __ct__11SendOnLocalFv(this + 0x1c);
  __ct__10MenuSpriteFv(this + 0x4c);
  (**(code **)(this->f_8 /*int **/ + 0x20))();
  return this;
}

// JP: 0x00287220  __dt__14MenuWindowFaceFv  size 0xac
// MenuWindowFace::~MenuWindowFace()
int __dt__14MenuWindowFaceFv(MenuWindowFace *this,short param_2)
{
  if (this != 0) {
    this->f_8 /*u8 **/ = __vt__14MenuWindowFace;
    (**(code **)(this->f_8 /*int **/ + 0x1c))();
    __dt__10MenuSpriteFv(this + 0x4c,0xffffffffffffffff);
    __dt__11SendOnLocalFv(this + 0x1c,0xffffffffffffffff);
    __dt__16MenuWindowObjectFv(this,0);
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

// JP: 0x002872d0  Create__14MenuWindowFaceFP10MenuWindow  size 0xa8
// MenuWindowFace::Create(MenuWindow*)
void Create__14MenuWindowFaceFP10MenuWindow(MenuWindowFace *this,u32 menuWindow)
{
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi
            (this + 0x1c,0x4218f0,DAT_004218ec,1,0xffffffffffffffff);
  UpdatePacket__11SendOnLocalFv(this + 0x1c);
  SetData__9MenuSceneFUsP10MenuSprite(0x421600,0x13,this + 0x4c);
  (**(code **)(this->f_54 /*int **/ + 0x38))(this + 0x4c,menuWindow);
  this->f_18 /*u32 **/ = menuWindow;
  return;
}

// JP: 0x00287380  SetColor__14MenuWindowFaceFUcUcUc  size 0x4c
// MenuWindowFace::SetColor(unsigned char, unsigned char, unsigned char)
void SetColor__14MenuWindowFaceFUcUcUc
               (MenuWindowFace *this,u8 param_2,u8 param_3,u8 param_4)
{
  (**(code **)(this->f_54 /*int **/ + 0x30))(this + 0x4c,param_2,param_3,param_4);
  return;
}

// JP: 0x002873d0  SetAlpha__14MenuWindowFaceFUc  size 0x3c
// MenuWindowFace::SetAlpha(unsigned char)
void SetAlpha__14MenuWindowFaceFUc(MenuWindowFace *this,u8 param_2)
{
  (**(code **)(this->f_54 /*int **/ + 0x2c))(this + 0x4c,param_2);
  return;
}

// JP: 0x00287410  Update__14MenuWindowFaceFiiUs  size 0xb0
// MenuWindowFace::Update(int, int, unsigned short)
void Update__14MenuWindowFaceFiiUs
               (MenuWindowFace *this,u32 param_2,u32 param_3,u16 param_4)
{
  u8 bVar1;
  u8 *pbVar2;
  pbVar2 = (u8 *)(this + (m_Env__8VIF1Prim & 1) + 0x10);
  bVar1 = *pbVar2;
  this->f_5c /*u8 **/ = this->f_5c /*u8 **/ | bVar1;
  this->f_5d /*u8 **/ = this->f_5d /*u8 **/ | bVar1;
  (**(code **)(this->f_54 /*int **/ + 0x14))(this + 0x4c,param_2,param_3,param_4);
  *pbVar2 = *pbVar2 & 0x80;
  return;
}

// JP: 0x002874c0  Connect__14MenuWindowFaceFP4_QWD  size 0x4c
// MenuWindowFace::Connect(_QWD*)
void Connect__14MenuWindowFaceFP4_QWD(MenuWindowFace *this,u32 param_2)
{
  u32 uVar1;
  uVar1 = ConnectPacket__10MenuPacketFP4_QWD(this + 0x34,param_2);
  ConnectPacket__10MenuPacketFP4_QWD(this + 0x88,uVar1);
  return;
}

// JP: 0x00287510  Destroy__14MenuWindowFaceFv  size 0x4c
// MenuWindowFace::Destroy()
void Destroy__14MenuWindowFaceFv(MenuWindowFace *this)
{
  (**(code **)(this->f_24 /*int **/ + 0x1c))();
  (**(code **)(this->f_54 /*int **/ + 0x1c))();
  return;
}

// JP: 0x00287560  Clear__14MenuWindowFaceFv  size 0x60
// MenuWindowFace::Clear()
void Clear__14MenuWindowFaceFv(MenuWindowFace *this)
{
  Clear__7MenuObjFv(this);
  this->f_18 /*u32 **/ = 0;
  (**(code **)(this->f_24 /*int **/ + 0x20))();
  (**(code **)(this->f_54 /*int **/ + 0x20))();
  return;
}
