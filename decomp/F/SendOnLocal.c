/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x00277820  __ct__11SendOnLocalFv  size 0x70
// SendOnLocal::SendOnLocal()
int __ct__11SendOnLocalFv(SendOnLocal *this)
{
  __ct__7MenuObjFv(this);
  __ct__10MenuPacketFv(this + 0x18);
  this->f_8 /*u8 **/ = __vt__11SendOnLocal;
  this->f_18 /*u32 **/ = 0x405284;
  (**(code **)(this->f_8 /*int **/ + 0x20))();
  return this;
}

// JP: 0x00277890  __dt__11SendOnLocalFv  size 0xac
// SendOnLocal::~SendOnLocal()
int __dt__11SendOnLocalFv(SendOnLocal *this,short param_2)
{
  if (this != 0) {
    this->f_8 /*u8 **/ = __vt__11SendOnLocal;
    this->f_18 /*u32 **/ = 0x405284;
    (**(code **)(this->f_8 /*int **/ + 0x1c))();
    __dt__10MenuPacketFv(this + 0x18,0);
    __dt__7MenuObjFv(this,0);
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

// JP: 0x00277940  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi  size 0x190
// SendOnLocal::Create(RasterPacket*, ClutRaster*, bool, int)
u32
Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi
          (SendOnLocal *this,u32 param_2,u32 param_3,u8 param_4,uint param_5)
{
  ulong uVar1;
  if ((this->f_26 /*u8 **/ & 1) == 0) {
    if (param_4 == 0) {
      CreatePacket__10MenuPacketFUs(this + 0x18,3);
    }
    else {
      CreatePacket__10MenuPacketFUs(this + 0x18,8);
    }
  }
  else if (((ulong)this->f_26 /*u8 **/ & 0x7f) >> 6 != (ulong)param_4) {
    return 0;
  }
  uVar1 = (ulong)this->f_26 /*u8 **/ & 0xffffffffffffffbf | (long)(int)((param_4 & 1) << 6);
  this->f_26 /*char **/ = (char)uVar1;
  if (((long)(uVar1 << 0x39) < 0) && (-1 < (int)param_5)) {
    this->f_12 /*u8 **/ = this->f_12 /*u8 **/ & 0xdf | 0x20;
    this->f_12 /*u16 **/ =
         this->f_12 /*u16 **/ & 0xfc3f | (u16)((param_5 & 0xf) << 6);
  }
  this->f_28 /*u32 **/ = param_2;
  this->f_2c /*u32 **/ = param_3;
  this->f_10 /*u8 **/ = this->f_10 /*u8 **/ | 0x3f;
  this->f_11 /*u8 **/ = this->f_11 /*u8 **/ | 0x3f;
  return 1;
}

// JP: 0x00277ad0  Create__11SendOnLocalFP4_QWDUl  size 0x164
// SendOnLocal::Create(_QWD*, unsigned long)
void * Create__11SendOnLocalFP4_QWDUl(SendOnLocal *this,u32 param_2,u64 param_3)
{
  u32 *puVar1;
  void *pvVar2;
  int iVar3;
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(this,0,0,1,0xffffffffffffffff);
  this->f_10 /*u8 **/ = 0;
  this->f_11 /*u8 **/ = 0;
  iVar3 = this + (m_Env__8VIF1Prim & 1);
  *(u8 *)(iVar3 + 0x10) = *(u8 *)(iVar3 + 0x10) & 0xfd | 2;
  (**(code **)(this->f_8 /*int **/ + 0x14))(this,0,0,0);
  puVar1 = *(u32 **)(this + (m_Env__8VIF1Prim & 1) * 4 + 0x1c);
  *puVar1 = 0x50000000;
  puVar1[1] = param_2;
  puVar1[4] = 0x10000000;
  SetTextureRegister__11SendOnLocalFUlUl(this,6,param_3);
  pvVar2 = memcpy(*(void **)(this + (m_Env__8VIF1Prim & 1 ^ 1) * 4 + 0x1c),
                  *(void **)(this + (m_Env__8VIF1Prim & 1) * 4 + 0x1c),
                  (long)(int)((this->f_24 /*u16 **/ - 1) * 0x10));
  this->f_26 /*u16 **/ = this->f_26 /*u16 **/ & 0xf87f | 0x80;
  return pvVar2;
}

// JP: 0x00277c40  UpdatePacket__11SendOnLocalFv  size 0x8c
// SendOnLocal::UpdatePacket()
void * UpdatePacket__11SendOnLocalFv(SendOnLocal *this)
{
  void *pvVar1;
  (**(code **)(this->f_8 /*int **/ + 0x14))(this,0,0,0);
  pvVar1 = memcpy(*(void **)(this + (m_Env__8VIF1Prim & 1 ^ 1) * 4 + 0x1c),
                  *(void **)(this + (m_Env__8VIF1Prim & 1) * 4 + 0x1c),
                  (long)(int)((this->f_24 /*u16 **/ - 1) * 0x10));
  return pvVar1;
}

// JP: 0x00277cd0  SetTextureRegister__11SendOnLocalFUlUl  size 0x6c
// SendOnLocal::SetTextureRegister(unsigned long, unsigned long)
void SetTextureRegister__11SendOnLocalFUlUl(SendOnLocal *this,u64 param_2,u64 param_3)
{
  if ((long)((ulong)this->f_26 /*u8 **/ << 0x39) < 0) {
    *(u64 *)(this->f_20 /*int **/ + 0x58) = param_2;
    *(u64 *)(this->f_1c /*int **/ + 0x58) = param_2;
    *(u64 *)(this->f_20 /*int **/ + 0x50) = param_3;
    *(u64 *)(this->f_1c /*int **/ + 0x50) = param_3;
  }
  return;
}

// JP: 0x00277d40  GetTex0__11SendOnLocalFv  size 0x100
// SendOnLocal::GetTex0()
ulong GetTex0__11SendOnLocalFv(SendOnLocal *this)
{
  ulong uVar1;
  ulong uVar2;
  if (this->f_28 /*int **/ == 0) {
    uVar1 = *(ulong *)(this->f_1c /*int **/ + 0x50);
  }
  else if (this->f_2c /*int **/ == 0) {
    uVar1 = *this->f_28 /*ulong **/ & 0x7ffffffff;
  }
  else {
    uVar2 = *this->f_28 /*ulong **/;
    uVar1 = GetClutFlag__10ClutRasterFUcUc(this->f_2c /*u32 **/,0,1);
    uVar1 = uVar2 & 0x7ffffffff | uVar1;
  }
  return uVar1;
}

// JP: 0x00277e40  Update__11SendOnLocalFiiUs  size 0x2d4
// SendOnLocal::Update(int, int, unsigned short)
void Update__11SendOnLocalFiiUs(SendOnLocal *this)
{
  u32 *puVar1;
  u64 uVar2;
  ulong uVar3;
  u8 *pbVar4;
  ulong uVar5;
  if (((ulong)this->f_26 /*u16 **/ & 0x7ff) >> 7 == 0) {
    puVar1 = *(u32 **)(this + (m_Env__8VIF1Prim & 1) * 4 + 0x1c);
    pbVar4 = (u8 *)(this + (m_Env__8VIF1Prim & 1) + 0x10);
    if ((long)((ulong)*pbVar4 << 0x3d) < 0) {
      *puVar1 = 0x50000000;
      puVar1[1] = *(u32 *)(this->f_28 /*int **/ + 0x1c);
      if (this->f_2c /*int **/ == 0) {
        puVar1[4] = 0x10000000;
        puVar1[5] = 0;
      }
      else {
        puVar1[4] = 0x50000000;
        puVar1[5] = *(u32 *)(this->f_2c /*int **/ + 0x24);
      }
    }
    if (((long)((ulong)*pbVar4 << 0x3e) < 0) &&
       ((long)((ulong)this->f_26 /*u8 **/ << 0x39) < 0)) {
      puVar1[8] = &DAT_10000004;
      puVar1[10] = 0x13000000;
      puVar1[0xb] = 0x50000004;
      *(u64 *)(puVar1 + 0xc) = 0x3000000000008001;
      *(u64 *)(puVar1 + 0xe) = 0xeee;
      *(u64 *)(puVar1 + 0x12) = 0x3f;
      if ((long)((ulong)this->f_12 /*u8 **/ << 0x3a) < 0) {
        uVar2 = GetTex2__10ClutRasterCF6GS_PSMUcUc(this->f_2c /*u32 **/,0x1b,0,1);
        *(u64 *)(puVar1 + 0x14) = uVar2;
        *(u64 *)(puVar1 + 0x16) = 7;
        uVar5 = *this->f_28 /*ulong **/;
        uVar3 = GetClutFlag__10ClutRasterFUcUc
                          (this->f_2c /*u32 **/,
                           ((ulong)this->f_12 /*u16 **/ & 0x3ff) >> 6,0);
        *(ulong *)(puVar1 + 0x18) = uVar5 & 0x7ffffffff | uVar3;
        *(u64 *)(puVar1 + 0x1a) = 6;
      }
      else {
        uVar2 = GetTex0__11SendOnLocalFv(this);
        *(u64 *)(puVar1 + 0x14) = uVar2;
        *(u64 *)(puVar1 + 0x16) = 6;
        if ((long)((ulong)this->f_13 /*u8 **/ << 0x3d) < 0) {
          *(u64 *)(puVar1 + 0x18) = 0x48;
        }
        else {
          *(u64 *)(puVar1 + 0x18) = 0x44;
        }
        *(u64 *)(puVar1 + 0x1a) = 0x42;
      }
    }
    *pbVar4 = *pbVar4 & 0x80;
  }
  return;
}

// JP: 0x00278120  Connect__11SendOnLocalFP4_QWD  size 0x34
// SendOnLocal::Connect(_QWD*)
void Connect__11SendOnLocalFP4_QWD(SendOnLocal *this,u32 param_2)
{
  ConnectPacket__10MenuPacketFP4_QWD(this + 0x18,param_2);
  return;
}

// JP: 0x00278160  Destroy__11SendOnLocalFv  size 0x2c
// SendOnLocal::Destroy()
void Destroy__11SendOnLocalFv(SendOnLocal *this)
{
  DestroyPacket__10MenuPacketFv(this + 0x18);
  return;
}

// JP: 0x00278190  Clear__11SendOnLocalFv  size 0x48
// SendOnLocal::Clear()
void Clear__11SendOnLocalFv(SendOnLocal *this)
{
  Clear__7MenuObjFv(this);
  ClearPacket__10MenuPacketFv(this + 0x18);
  this->f_28 /*u32 **/ = 0;
  this->f_2c /*u32 **/ = 0;
  return;
}

// JP: 0x002781e0  @24@__dt__11SendOnLocalFv  size 0x8
// @24@__dt__11SendOnLocalFv
u32 * _24___dt__11SendOnLocalFv(SendOnLocal *this,short param_2)
{
  u32 *puVar1;
  puVar1 = this + -6;
  if (puVar1 != (u32 *)0x0) {
    this[-4] = __vt__11SendOnLocal;
    *this = 0x405284;
    (**(code **)(this[-4] + 0x1c))();
    __dt__10MenuPacketFv(this,0);
    __dt__7MenuObjFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}
