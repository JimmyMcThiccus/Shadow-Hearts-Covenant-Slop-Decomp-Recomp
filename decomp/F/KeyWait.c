/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x002808a0  __ct__7KeyWaitFv  size 0x80
// KeyWait::KeyWait()
int __ct__7KeyWaitFv(KeyWait *this)
{
  __ct__7MenuObjFv(this);
  this->f_8 /*u8 **/ = __vt__7KeyWait;
  __ct__11SendOnLocalFv(this + 0x24);
  __ct__10MenuSpriteFv(this + 0x54);
  __ct__12MenuRegisterFv(this + 0xb4);
  (**(code **)(this->f_8 /*int **/ + 0x20))();
  return this;
}

// JP: 0x00280920  __dt__7KeyWaitFv  size 0xc4
// KeyWait::~KeyWait()
int __dt__7KeyWaitFv(KeyWait *this,short param_2)
{
  if (this != 0) {
    this->f_8 /*u8 **/ = __vt__7KeyWait;
    (**(code **)(this->f_8 /*int **/ + 0x1c))();
    __dt__12MenuRegisterFv(this + 0xb4,0xffffffffffffffff);
    __dt__10MenuSpriteFv(this + 0x54,0xffffffffffffffff);
    __dt__11SendOnLocalFv(this + 0x24,0xffffffffffffffff);
    __dt__7MenuObjFv(this,0);
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

// JP: 0x002809f0  Create__7KeyWaitFv  size 0xfc
// KeyWait::Create()
void Create__7KeyWaitFv(KeyWait *this)
{
  SetData__9MenuSceneFUsP10MenuSprite(0x421600,0x1d,this + 0x54);
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi
            (this + 0x24,0x421970,DAT_0042196c,1,0xffffffffffffffff);
  UpdatePacket__11SendOnLocalFv(this + 0x24);
  this->f_b0 /*int **/ = this + 0x24;
  this->f_66 /*u8 **/ = this->f_66 /*u8 **/ & 0xdf;
  CreatePacket__10MenuPacketFUs(this + 0xcc,4);
  SetRegister__12MenuRegisterFiUlUl(this + 0xb4,0,0x42,0x44);
  this->f_10 /*u8 **/ = this->f_10 /*u8 **/ | 0x3f;
  this->f_11 /*u8 **/ = this->f_11 /*u8 **/ | 0x3f;
  return;
}

// JP: 0x00280af0  SetPosition__7KeyWaitFi  size 0xf8
// KeyWait::SetPosition(int)
void SetPosition__7KeyWaitFi(KeyWait *this,int param_2)
{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  if (param_2 == 1) {
    fVar1 = this->f_84 /*float **/;
    fVar2 = *(float *)(this->f_18 /*int **/ + 0x70);
    fVar3 = (float)GetTargetY__10MenuWindowCFv(this->f_18 /*u32 **/);
    fVar4 = this->f_80 /*float **/;
    fVar5 = *(float *)(this->f_18 /*int **/ + 0x6c);
    fVar6 = (float)GetTargetX__10MenuWindowCFv(this->f_18 /*u32 **/);
    (**(code **)(this->f_5c /*int **/ + 0x24))((fVar5 - fVar4) - fVar6,(fVar2 - fVar1) - fVar3);
  }
  return;
}

// JP: 0x00280bf0  Polling__7KeyWaitFv  size 0x1c0
// KeyWait::Polling()
void Polling__7KeyWaitFv(KeyWait *this)
{
  short sVar1;
  int iVar2;
  sVar1 = this->f_1e /*short **/;
  if (sVar1 == 10) {
    this->f_1e /*u16 **/ = 0xb;
  }
  else if (sVar1 == 0xc) {
    iVar2 = GetActive__4CPadFi(((ulong)this->f_22 /*u8 **/ & 0x3f) >> 5);
    if ((this->f_20 /*u16 **/ &
        *(u16 *)((&m_pCoreArray__4CPad)[*(int *)(iVar2 + 4)] + 0x6e)) != 0) {
      this->f_1e /*u16 **/ = 0xd;
    }
  }
  else if ((sVar1 == 0xb) &&
          (iVar2 = GetActive__4CPadFi(((ulong)this->f_22 /*u8 **/ & 0x3f) >> 5),
          (this->f_20 /*u16 **/ &
          *(u16 *)((&m_pCoreArray__4CPad)[*(int *)(iVar2 + 4)] + 0x6c)) != 0)) {
    this->f_1e /*u16 **/ = 0xc;
  }
  this->f_1c /*short **/ = this->f_1c /*short **/ + (short)sm_iPassTime__7MenuObj;
  if (0x3c0 < this->f_1c /*short **/) {
    this->f_1c /*short **/ = this->f_1c /*short **/ + -0x780;
  }
  return;
}

// JP: 0x00280db0  Update__7KeyWaitFiiUs  size 0x17c
// KeyWait::Update(int, int, unsigned short)
void Update__7KeyWaitFiiUs(KeyWait *this,u32 param_2,u32 param_3,u16 param_4)
{
  u8 bVar1;
  short sVar2;
  u8 *pbVar3;
  pbVar3 = (u8 *)(this + (m_Env__8VIF1Prim & 1) + 0x10);
  sVar2 = this->f_1c /*short **/ / 10;
  if (sVar2 < 0) {
    sVar2 = -sVar2;
  }
  (**(code **)(this->f_5c /*int **/ + 0x2c))(this + 0x54,0x80 - ((int)sVar2 & 0xffU) & 0xff);
  (**(code **)(this->f_5c /*int **/ + 0x14))(this + 0x54,param_2,param_3,param_4);
  bVar1 = *pbVar3;
  this->f_c4 /*u8 **/ = this->f_c4 /*u8 **/ | bVar1;
  this->f_c5 /*u8 **/ = this->f_c5 /*u8 **/ | bVar1;
  (**(code **)(this->f_bc /*int **/ + 0x14))(this + 0xb4,param_2,param_3,param_4);
  *pbVar3 = *pbVar3 & 0x80;
  return;
}

// JP: 0x00280f30  Connect__7KeyWaitFP4_QWD  size 0x54
// KeyWait::Connect(_QWD*)
void Connect__7KeyWaitFP4_QWD(KeyWait *this,u32 param_2)
{
  u32 uVar1;
  uVar1 = (**(code **)(this->f_5c /*int **/ + 0x18))(this + 0x54,param_2);
  ConnectPacket__10MenuPacketFP4_QWD(this + 0xcc,uVar1);
  return;
}

// JP: 0x00280f90  Destroy__7KeyWaitFv  size 0x64
// KeyWait::Destroy()
void Destroy__7KeyWaitFv(KeyWait *this)
{
  (**(code **)(this->f_5c /*int **/ + 0x1c))();
  (**(code **)(this->f_2c /*int **/ + 0x1c))();
  (**(code **)(this->f_bc /*int **/ + 0x1c))();
  return;
}

// JP: 0x00281000  Clear__7KeyWaitFv  size 0xe4
// KeyWait::Clear()
void Clear__7KeyWaitFv(KeyWait *this)
{
  ulong uVar1;
  Clear__7MenuObjFv(this);
  (**(code **)(this->f_5c /*int **/ + 0x20))();
  (**(code **)(this->f_2c /*int **/ + 0x20))();
  (**(code **)(this->f_bc /*int **/ + 0x20))();
  this->f_1c /*u16 **/ = 0;
  this->f_1e /*u16 **/ = 0;
  this->f_20 /*u16 **/ = 0x2000;
  this->f_22 /*u16 **/ = 1;
  uVar1 = (ulong)this->f_11 /*u8 **/ & 0xffffffffffffff7f | 0x80;
  this->f_11 /*char **/ = (char)uVar1;
  this->f_10 /*u8 **/ =
       this->f_10 /*u8 **/ & 0x7f | (u8)((uint)((uVar1 << 0x38) >> 0x3f) << 7);
  return;
}
