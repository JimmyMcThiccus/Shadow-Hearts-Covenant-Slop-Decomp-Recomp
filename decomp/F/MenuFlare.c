/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x00286570  __ct__9MenuFlareFv  size 0x88
// MenuFlare::MenuFlare()
int __ct__9MenuFlareFv(MenuFlare *this)
{
  __ct__7MenuObjFv(this);
  this->f_8 /*u8 **/ = __vt__9MenuFlare;
  __ct__11SendOnLocalFv(this + 0x18);
  __construct_array(this + 0x48,0x266140,0x2661a0,0x60,8);
  (**(code **)(this->f_8 /*int **/ + 0x20))();
  return this;
}

// JP: 0x00286600  __dt__9MenuFlareFv  size 0xbc
// MenuFlare::~MenuFlare()
int __dt__9MenuFlareFv(MenuFlare *this,short param_2)
{
  if (this != 0) {
    this->f_8 /*u8 **/ = __vt__9MenuFlare;
    (**(code **)(this->f_8 /*int **/ + 0x1c))();
    __destroy_arr(this + 0x48,0x2661a0,0x60,8);
    __dt__11SendOnLocalFv(this + 0x18,0xffffffffffffffff);
    __dt__7MenuObjFv(this,0);
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

// JP: 0x002866c0  Create__9MenuFlareFv  size 0x35c
// MenuFlare::Create()
/* WARNING: Removing unreachable block (ram,0x00286714) */
/* WARNING: Removing unreachable block (ram,0x00286760) */
void Create__9MenuFlareFv(MenuFlare *this)
{
  ulong uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  float fStack_18;
  float fStack_14;
  fStack_18 = (float)*DAT_00421828;
  fStack_14 = (float)DAT_00421828[1];
  uVar4 = 100;
  for (iVar3 = 0; iVar3 < 8; iVar3 = iVar3 + 1) {
    Create__10MenuSpriteFUc(this + iVar3 * 0x60 + 0x48,1);
    iVar2 = this + iVar3 * 0x60;
    *(u8 *)(iVar2 + 0x69) = *(u8 *)(iVar2 + 0x69) & 0xbf | 0x40;
    iVar2 = this + iVar3 * 0x60;
    uVar1 = (ulong)*(u8 *)(iVar2 + 0x59) & 0xfffffffffffffffd | 2;
    *(char *)(iVar2 + 0x59) = (char)uVar1;
    iVar2 = this + iVar3 * 0x60;
    *(u8 *)(iVar2 + 0x58) =
         *(u8 *)(iVar2 + 0x58) & 0xfd | (u8)((uint)((uVar1 << 0x3e) >> 0x3f) << 1);
    (**(code **)(*(int *)(this + iVar3 * 0x60 + 0x50) + 0x28))(fStack_18,fStack_14);
    SetUV__10MenuSpriteFUsUsUsUs
              (this + iVar3 * 0x60 + 0x48,1,1,*DAT_00421828 - 1,DAT_00421828[1] - 1);
    iVar2 = this + iVar3 * 0x60;
    (**(code **)(*(int *)(iVar2 + 0x50) + 0x2c))(iVar2 + 0x48,uVar4 & 0xff);
    iVar2 = this + iVar3 * 0x60;
    *(u8 *)(iVar2 + 0x5a) = *(u8 *)(iVar2 + 0x5a) & 0xfe;
    fStack_18 = fStack_18 * 0.75;
    fStack_14 = fStack_14 * 0.75;
    uVar4 = uVar4 - 0x19;
    if ((int)uVar4 < 1) {
      uVar4 = 5;
    }
  }
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi
            (this + 0x18,0x421830,DAT_0042182c,1,0xffffffffffffffff);
  UpdatePacket__11SendOnLocalFv(this + 0x18);
  this->f_5a /*u8 **/ = this->f_5a /*u8 **/ & 0xfe | 1;
  this->f_348 /*u16 **/ = 0;
  return;
}

// JP: 0x00286a20  SetOffset__9MenuFlareFffff  size 0x160
// MenuFlare::SetOffset(float, float, float, float)
void SetOffset__9MenuFlareFffff(float param_1,float param_2,float param_3,float param_4,int this)
{
  int iVar1;
  for (iVar1 = 0; iVar1 < 8; iVar1 = iVar1 + 1) {
    (**(code **)(*(int *)(this + iVar1 * 0x60 + 0x50) + 0x24))
              (((float)(int)param_1 + param_3 * 0.5) -
               *(float *)(this + iVar1 * 0x60 + 0x74) * 0.5,
               ((float)(int)param_2 + param_4 * 0.5) -
               *(float *)(this + iVar1 * 0x60 + 0x78) * 0.5);
  }
  return;
}

// JP: 0x00286b80  ClearAfter__9MenuFlareFv  size 0x6c
// MenuFlare::ClearAfter()
void ClearAfter__9MenuFlareFv(MenuFlare *this)
{
  int iVar1;
  int iVar2;
  for (iVar2 = 1; iVar2 < 8; iVar2 = iVar2 + 1) {
    iVar1 = this + iVar2 * 0x60;
    *(u8 *)(iVar1 + 0x5a) = *(u8 *)(iVar1 + 0x5a) & 0xfe;
  }
  this->f_348 /*u16 **/ = 0;
  return;
}

// JP: 0x00286bf0  Polling__9MenuFlareFv  size 0x80
// MenuFlare::Polling()
void Polling__9MenuFlareFv(MenuFlare *this)
{
  this->f_34a /*short **/ = this->f_34a /*short **/ + (short)sm_iPassTime__7MenuObj;
  if (0x1e0 < this->f_34a /*short **/) {
    this->f_34a /*short **/ = this->f_34a /*short **/ + -0x3c0;
  }
  this->f_12 /*u8 **/ = this->f_12 /*u8 **/ & 0xdf | 0x20;
  return;
}

// JP: 0x00286c70  Update__9MenuFlareFiiUs  size 0x370
// MenuFlare::Update(int, int, unsigned short)
void Update__9MenuFlareFiiUs(MenuFlare *this,u32 param_2,u32 param_3,u16 param_4)
{
  short sVar1;
  ulong uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  u32 *puVar6;
  u32 *puVar7;
  if (this->f_34a /*short **/ < 0) {
    iVar3 = -(int)this->f_34a /*short **/;
  }
  else {
    iVar3 = (int)this->f_34a /*short **/;
  }
  uVar4 = 0x80 - (iVar3 / 0x14 & 0xffU) & 0xff;
  iVar3 = this + 0x48;
  sVar1 = this->f_348 /*short **/;
  (**(code **)(this->f_50 /*int **/ + 0x30))(iVar3,uVar4,uVar4,uVar4);
  uVar2 = (ulong)this->f_59 /*u8 **/ & 0xfffffffffffffff7 | 8;
  this->f_59 /*char **/ = (char)uVar2;
  this->f_58 /*u8 **/ =
       this->f_58 /*u8 **/ & 0xf7 | (u8)((uint)((uVar2 << 0x3c) >> 0x3f) << 3);
  (**(code **)(this->f_50 /*int **/ + 0x14))(iVar3,param_2,param_3,param_4);
  puVar7 = (u32 *)(this + 0x34c);
  puVar6 = (u32 *)(this + 0x368);
  for (uVar4 = this + 0xa8; uVar4 < (uint)(iVar3 + sVar1 * 0x60); uVar4 = uVar4 + 0x60) {
    uVar2 = (ulong)*(u8 *)(uVar4 + 0x11) & 0xfffffffffffffff7 | 8;
    *(char *)(uVar4 + 0x11) = (char)uVar2;
    *(u8 *)(uVar4 + 0x10) =
         *(u8 *)(uVar4 + 0x10) & 0xf7 | (u8)((uint)((uVar2 << 0x3c) >> 0x3f) << 3);
    VCALL(uVar4, 0x14 /*Update*/)(uVar4,*puVar7,*puVar6,param_4);
    *(u8 *)(uVar4 + 0x12) = *(u8 *)(uVar4 + 0x12) & 0xfe | 1;
    puVar7 = puVar7 + 1;
    puVar6 = puVar6 + 1;
  }
  if ((long)((ulong)this->f_12 /*u8 **/ << 0x3a) < 0) {
    iVar3 = (int)this->f_348 /*short **/;
    while (iVar5 = iVar3 + -1, 0 < iVar5) {
      *(u32 *)(this + iVar5 * 4 + 0x34c) =
           *(u32 *)(this + (iVar3 + -2) * 4 + 0x34c);
      *(u32 *)(this + iVar5 * 4 + 0x368) =
           *(u32 *)(this + (iVar3 + -2) * 4 + 0x368);
      iVar3 = iVar5;
    }
    this->f_34c /*u32 **/ = param_2;
    this->f_368 /*u32 **/ = param_3;
    this->f_348 /*short **/ = this->f_348 /*short **/ + 1;
    if (7 < this->f_348 /*short **/) {
      this->f_348 /*u16 **/ = 7;
    }
    this->f_12 /*u8 **/ = this->f_12 /*u8 **/ & 0xdf;
  }
  return;
}

// JP: 0x00286fe0  Connect__9MenuFlareFP4_QWD  size 0xb0
// MenuFlare::Connect(_QWD*)
u32 Connect__9MenuFlareFP4_QWD(MenuFlare *this,u32 param_2)
{
  uint uVar1;
  u32 uStack_10;
  uStack_10 = (**(code **)(this->f_20 /*int **/ + 0x18))(this + 0x18,param_2);
  for (uVar1 = this + 0x48; uVar1 < this + 0x348U; uVar1 = uVar1 + 0x60) {
    if ((*(u8 *)(uVar1 + 0x12) & 1) != 0) {
      uStack_10 = VCALL(uVar1, 0x18 /*Connect*/)(uVar1,uStack_10);
    }
  }
  return uStack_10;
}

// JP: 0x00287090  Destroy__9MenuFlareFv  size 0x7c
// MenuFlare::Destroy()
void Destroy__9MenuFlareFv(MenuFlare *this)
{
  uint uVar1;
  for (uVar1 = this + 0x48; uVar1 < this + 0x348U; uVar1 = uVar1 + 0x60) {
    VCALL(uVar1, 0x1c /*Destroy*/)();
  }
  (**(code **)(this->f_20 /*int **/ + 0x1c))();
  return;
}

// JP: 0x00287110  Clear__9MenuFlareFv  size 0xa0
// MenuFlare::Clear()
void Clear__9MenuFlareFv(MenuFlare *this)
{
  int iVar1;
  Clear__7MenuObjFv(this);
  this->f_348 /*u16 **/ = 0;
  this->f_34a /*u16 **/ = 0;
  for (iVar1 = 0; iVar1 < 8; iVar1 = iVar1 + 1) {
    (**(code **)(*(int *)(this + iVar1 * 0x60 + 0x50) + 0x20))();
  }
  (**(code **)(this->f_20 /*int **/ + 0x20))();
  return;
}
