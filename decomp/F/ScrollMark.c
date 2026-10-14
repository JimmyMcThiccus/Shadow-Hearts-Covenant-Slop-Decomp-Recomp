/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x0027b330  __ct__10ScrollMarkFv  size 0x70
// ScrollMark::ScrollMark()
int __ct__10ScrollMarkFv(ScrollMark *this)
{
  __ct__7MenuObjFv(this);
  this->f_8 /*u8 **/ = __vt__10ScrollMark;
  __ct__11SendOnLocalFv(this + 0x18);
  __ct__11SendOnLocalFv(this + 0x48);
  (**(code **)(this->f_8 /*int **/ + 0x20))();
  return this;
}

// JP: 0x0027b3a0  __dt__10ScrollMarkFv  size 0xac
// ScrollMark::~ScrollMark()
int __dt__10ScrollMarkFv(ScrollMark *this,short param_2)
{
  if (this != 0) {
    this->f_8 /*u8 **/ = __vt__10ScrollMark;
    (**(code **)(this->f_8 /*int **/ + 0x1c))();
    __dt__11SendOnLocalFv(this + 0x48,0xffffffffffffffff);
    __dt__11SendOnLocalFv(this + 0x18,0xffffffffffffffff);
    __dt__7MenuObjFv(this,0);
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

// JP: 0x0027b450  Create__10ScrollMarkFUcP10MenuWindowUc  size 0x3a0
// ScrollMark::Create(unsigned char, MenuWindow*, unsigned char)
void Create__10ScrollMarkFUcP10MenuWindowUc
               (ScrollMark *this,u8 param_2,u32 menuWindow,u8 param_4)
{
  u8 bVar1;
  short sVar2;
  int iVar3;
  u64 uVar4;
  ulong uVar5;
  uint uVar6;
  uint uVar7;
  u16 uVar8;
  bVar1 = *(u8 *)((int)&markMask + (uint)param_4);
  param_2 = param_2 & bVar1;
  uVar7 = 0;
  for (uVar6 = 0; uVar6 < 4; uVar6 = uVar6 + 1 & 0xff) {
    if (((uint)param_2 & 1 << (uVar6 & 0x1f)) != 0) {
      uVar7 = uVar7 + 1 & 0xff;
    }
  }
  if (uVar7 != 0) {
    uVar4 = __nwa__FUi(uVar7 * 0x60 + 0x10);
    iVar3 = __construct_new_array(uVar4,0x266140,0x2661a0,0x60,uVar7);
    this->f_78 /*int **/ = iVar3;
    uVar8 = 0;
    for (uVar6 = 0; uVar6 < 4; uVar6 = uVar6 + 1 & 0xff) {
      if (((uint)param_2 & 1 << (uVar6 & 0x1f)) != 0) {
        SetData__9MenuSceneFUsP10MenuSprite(0x421600,param_4 + 0x1e,iVar3);
        sVar2 = uVar8 * *(short *)(iVar3 + 0x22);
        *(short *)(iVar3 + 0x56) = *(short *)(iVar3 + 0x56) + sVar2;
        *(short *)(iVar3 + 0x5a) = *(short *)(iVar3 + 0x5a) + sVar2;
        VCALL(iVar3, 0x38 /*SetOwner*/)(iVar3,menuWindow);
        iVar3 = iVar3 + 0x60;
      }
      if (((uint)bVar1 & 1 << (uVar6 & 0x1f)) != 0) {
        uVar8 = uVar8 + 1 & 0xff;
      }
    }
    Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi
              (this + 0x18,(uint)param_4 * 0x40 + 0x421730,
               *(u32 *)(&DAT_0042172c + (uint)param_4 * 0x40),1,0xffffffffffffffff);
    UpdatePacket__11SendOnLocalFv(this + 0x18);
  }
  this->f_83 /*u8 **/ = this->f_83 /*u8 **/ & 0xf0 | param_2 & 0xf;
  this->f_83 /*u8 **/ = this->f_83 /*u8 **/ & 0xf | (u8)((uVar7 & 0xf) << 4);
  this->f_12 /*u16 **/ = this->f_12 /*u16 **/ & 0xfc3f | (param_4 & 0xf) << 6;
  this->f_82 /*u8 **/ = *(u8 *)((int)&markMargin + (uint)param_4);
  this->f_10 /*u8 **/ = this->f_10 /*u8 **/ | 0x3f;
  this->f_11 /*u8 **/ = this->f_11 /*u8 **/ | 0x3f;
  uVar5 = (ulong)this->f_11 /*u8 **/ & 0xffffffffffffff7f | 0x80;
  this->f_11 /*char **/ = (char)uVar5;
  this->f_10 /*u8 **/ =
       this->f_10 /*u8 **/ & 0x7f | (u8)((uint)((uVar5 << 0x38) >> 0x3f) << 7);
  return;
}

// JP: 0x0027b7f0  SetMark__10ScrollMarkFUc  size 0x104
// ScrollMark::SetMark(unsigned char)
void SetMark__10ScrollMarkFUc(ScrollMark *this,u8 param_2)
{
  uint uVar1;
  int iVar2;
  iVar2 = this->f_78 /*int **/;
  if (iVar2 != 0) {
    for (uVar1 = 0; uVar1 < 4; uVar1 = uVar1 + 1 & 0xff) {
      if ((this->f_83 /*u8 **/ & 0xf & 1 << (uVar1 & 0x1f)) != 0) {
        if (((uint)param_2 & 1 << (uVar1 & 0x1f)) == 0) {
          *(u8 *)(iVar2 + 0x12) = *(u8 *)(iVar2 + 0x12) & 0xfe;
        }
        else {
          *(u8 *)(iVar2 + 0x12) = *(u8 *)(iVar2 + 0x12) & 0xfe | 1;
        }
        iVar2 = iVar2 + 0x60;
      }
    }
    this->f_10 /*u8 **/ = this->f_10 /*u8 **/ | 0x3f;
    this->f_11 /*u8 **/ = this->f_11 /*u8 **/ | 0x3f;
  }
  return;
}

// JP: 0x0027b900  SetArea__10ScrollMarkFUcffff  size 0x254
// ScrollMark::SetArea(unsigned char, float, float, float, float)
void SetArea__10ScrollMarkFUcffff
               (float param_1,float param_2,float param_3,float param_4,int this,u8 param_6)
{
  int iVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  iVar1 = this->f_78 /*int **/;
  if (iVar1 != 0) {
    fVar2 = *(float *)(iVar1 + 0x2c);
    fVar3 = *(float *)(iVar1 + 0x30);
    fVar4 = param_1 + param_3 / 2.0;
    fVar5 = param_2 + param_4 / 2.0;
    if ((this->f_83 /*u8 **/ & 1) != 0) {
      if ((param_6 & 1) != 0) {
        VCALL(iVar1, 0x24 /*SetPosition*/)(fVar4 - fVar2 / 2.0,param_2 - fVar3);
      }
      iVar1 = iVar1 + 0x60;
    }
    if ((this->f_83 /*u8 **/ & 2) != 0) {
      if ((param_6 & 2) != 0) {
        VCALL(iVar1, 0x24 /*SetPosition*/)(fVar4 - fVar2 / 2.0,param_2 + param_4);
      }
      iVar1 = iVar1 + 0x60;
    }
    if ((this->f_83 /*u8 **/ & 4) != 0) {
      if ((param_6 & 4) != 0) {
        VCALL(iVar1, 0x24 /*SetPosition*/)(param_1 - fVar2,fVar5 - fVar3 / 2.0);
      }
      iVar1 = iVar1 + 0x60;
    }
    if (((this->f_83 /*u8 **/ & 8) != 0) && ((param_6 & 8) != 0)) {
      VCALL(iVar1, 0x24 /*SetPosition*/)(param_1 + param_3,fVar5 - fVar3 / 2.0);
    }
  }
  return;
}

// JP: 0x0027bb60  Polling__10ScrollMarkFv  size 0x5c
// ScrollMark::Polling()
void Polling__10ScrollMarkFv(ScrollMark *this)
{
  this->f_80 /*short **/ = this->f_80 /*short **/ + (short)sm_iPassTime__7MenuObj;
  if (500 < this->f_80 /*short **/) {
    this->f_80 /*short **/ = this->f_80 /*short **/ + -1000;
  }
  return;
}

// JP: 0x0027bbc0  Update__10ScrollMarkFiiUs  size 0x254
// ScrollMark::Update(int, int, unsigned short)
void Update__10ScrollMarkFiiUs(ScrollMark *this,int param_2,int param_3,u16 param_4)
{
  u8 bVar1;
  ulong uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  u8 *pbVar6;
  int aiStack_60 [4];
  int aiStack_50 [4];
  int iStack_40;
  int iStack_30;
  int iStack_20;
  u16 uStack_10;
  iStack_40 = this;
  iStack_30 = param_2;
  iStack_20 = param_3;
  uStack_10 = param_4;
  iVar4 = this->f_78 /*int **/;
  if (iVar4 != 0) {
    pbVar6 = (u8 *)(this + (m_Env__8VIF1Prim & 1) + 0x10);
    iVar3 = (int)this->f_80 /*short **/ / 100;
    if (iVar3 < 0) {
      iVar3 = -iVar3;
    }
    iVar3 = iVar3 + this->f_82 /*char **/;
    aiStack_50[1] = param_2;
    aiStack_50[0] = param_2;
    aiStack_60[3] = param_3;
    aiStack_60[2] = param_3;
    aiStack_60[0] = param_3 + iVar3 * -0x10;
    aiStack_60[1] = param_3 + iVar3 * 0x10;
    aiStack_50[2] = param_2 + iVar3 * -0x10;
    aiStack_50[3] = param_2 + iVar3 * 0x10;
    for (uVar5 = 0; (int)uVar5 < 4; uVar5 = uVar5 + 1) {
      if ((*(u8 *)(iStack_40 + 0x83) & 0xf & 1 << (uVar5 & 0x1f)) != 0) {
        if ((*(u8 *)(iVar4 + 0x12) & 1) != 0) {
          bVar1 = *(u8 *)(iStack_40 + (m_Env__8VIF1Prim & 1) + 0x10);
          *(u8 *)(iVar4 + 0x10) = *(u8 *)(iVar4 + 0x10) | bVar1;
          *(u8 *)(iVar4 + 0x11) = *(u8 *)(iVar4 + 0x11) | bVar1;
          uVar2 = (ulong)*(u8 *)(iVar4 + 0x11) & 0xfffffffffffffff7 | 8;
          *(char *)(iVar4 + 0x11) = (char)uVar2;
          *(u8 *)(iVar4 + 0x10) =
               *(u8 *)(iVar4 + 0x10) & 0xf7 | (u8)((uint)((uVar2 << 0x3c) >> 0x3f) << 3);
          VCALL(iVar4, 0x14 /*Update*/)
                    (iVar4,aiStack_50[uVar5],aiStack_60[uVar5],uStack_10);
        }
        iVar4 = iVar4 + 0x60;
      }
    }
    *pbVar6 = *pbVar6 & 0x80;
  }
  return;
}

// JP: 0x0027be20  Connect__10ScrollMarkFP4_QWD  size 0xcc
// ScrollMark::Connect(_QWD*)
u32 Connect__10ScrollMarkFP4_QWD(ScrollMark *this,u32 param_2)
{
  u8 bVar1;
  int iVar2;
  u32 uStack_10;
  iVar2 = this->f_78 /*int **/;
  uStack_10 = param_2;
  if (iVar2 != 0) {
    uStack_10 = (**(code **)(this->f_20 /*int **/ + 0x18))(this + 0x18,param_2);
    for (bVar1 = 0; bVar1 < this->f_83 /*u8 **/ >> 4; bVar1 = bVar1 + 1) {
      if ((*(u8 *)(iVar2 + 0x12) & 1) != 0) {
        uStack_10 = ConnectPacket__10MenuPacketFP4_QWD(iVar2 + 0x3c,uStack_10);
      }
      iVar2 = iVar2 + 0x60;
    }
  }
  return uStack_10;
}

// JP: 0x0027bef0  Destroy__10ScrollMarkFv  size 0x68
// ScrollMark::Destroy()
void Destroy__10ScrollMarkFv(ScrollMark *this)
{
  (**(code **)(this->f_20 /*int **/ + 0x1c))();
  if (this->f_78 /*int **/ != 0) {
    __destroy_new_array(this->f_78 /*u32 **/,0x2661a0);
    this->f_78 /*u32 **/ = 0;
  }
  return;
}

// JP: 0x0027bf60  Clear__10ScrollMarkFv  size 0x6c
// ScrollMark::Clear()
void Clear__10ScrollMarkFv(ScrollMark *this)
{
  Clear__7MenuObjFv(this);
  this->f_78 /*u32 **/ = 0;
  this->f_7c /*u32 **/ = 0;
  this->f_80 /*u16 **/ = 0;
  this->f_82 /*u8 **/ = 2;
  this->f_83 /*u8 **/ = 0;
  (**(code **)(this->f_20 /*int **/ + 0x20))();
  return;
}
