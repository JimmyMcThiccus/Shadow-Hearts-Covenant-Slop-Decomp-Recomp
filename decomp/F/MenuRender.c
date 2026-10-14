/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x00265ac0  __ct__10MenuRenderFv  size 0xa0
// MenuRender::MenuRender()
void * __ct__10MenuRenderFv(MenuRender *this)
{
  __ct__8VIF1PrimFv(this);
  __ct__7CPolObjFv((int)this + 0x14);
  __ct__12MenuObjTableFv((int)this + 0x2c);
  *(u8 **)((int)this + 0x10) = __vt__10MenuRender;
  *(u32 *)((int)this + 0x28) = 0x404f90;
  *(u32 *)((int)this + 0x2c) = 0x404fa0;
  ClearTable__12MenuObjTableFv((int)this + 0x2c);
  memset(this,0,8);
  return this;
}

// JP: 0x00265b60  __dt__10MenuRenderFv  size 0xc4
// MenuRender::~MenuRender()
int __dt__10MenuRenderFv(MenuRender *this,short param_2)
{
  if (this != 0) {
    this->f_10 /*u8 **/ = __vt__10MenuRender;
    this->f_28 /*u32 **/ = 0x404f90;
    this->f_2c /*u32 **/ = 0x404fa0;
    Release__10MenuRenderFv(this);
    __dt__12MenuObjTableFv(this + 0x2c,0);
    __dt__7CPolObjFv(this + 0x14,0);
    __dt__8VIF1PrimFv(this,0);
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

// JP: 0x00265c30  Create__10MenuRenderFv  size 0x14c
// MenuRender::Create()
void * Create__10MenuRenderFv(MenuRender *this)
{
  u32 *puVar1;
  int iVar2;
  void *pvVar3;
  iVar2 = __nwa__FUi(0x140);
  *this = iVar2;
  this[1] = *this + 0xa0;
  memset((void *)*this,0,0xa0);
  puVar1 = (u32 *)*this;
  *puVar1 = 0x10000006;
  puVar1[2] = 0x10000000;
  puVar1[3] = 0x50000006;
  *(u64 *)(puVar1 + 4) = 0x1000000000008005;
  *(u64 *)(puVar1 + 6) = 0xe;
  *(u64 *)(puVar1 + 8) = 0x3000d;
  *(u64 *)(puVar1 + 10) = 0x47;
  *(u64 *)(puVar1 + 0xc) = 0x44;
  *(u64 *)(puVar1 + 0xe) = 0x42;
  *(u64 *)(puVar1 + 0x12) = 0x4e;
  *(u64 *)(puVar1 + 0x14) = 5;
  *(u64 *)(puVar1 + 0x16) = 8;
  *(u64 *)(puVar1 + 0x18) = 0x61;
  *(u64 *)(puVar1 + 0x1a) = 0x14;
  puVar1[0x1c] = 0x20000000;
  puVar1[0x20] = 0x50000000;
  puVar1[0x24] = 0x60000000;
  pvVar3 = memcpy((void *)this[1],(void *)*this,0xa0);
  return pvVar3;
}

// JP: 0x00265d80  Release__10MenuRenderFv  size 0x50
// MenuRender::Release()
void Release__10MenuRenderFv(MenuRender *this)
{
  Dispose__10MenuRenderFv(this);
  if (*this != 0) {
    __dla__FPv(*this);
    *this = 0;
  }
  return;
}

// JP: 0x00265dd0  Entry__10MenuRenderFi  size 0x94
// MenuRender::Entry(int)
void Entry__10MenuRenderFi(MenuRender *this,int param_2)
{
  int iVar1;
  u32 uStack_10;
  uStack_10 = param_2;
  if (param_2 < 0) {
    uStack_10 = this->f_38 /*int **/;
  }
  iVar1 = this;
  if (this != 0) {
    iVar1 = this + 0x14;
  }
  Entry__7CPollerFP7CPolObjib(app__4CApp + 0x54,iVar1,0x80,0);
  AddOT__5WorldFiP8VIF1Prim(0x42bf10,uStack_10,this);
  this->f_38 /*int **/ = uStack_10;
  return;
}

// JP: 0x00265e70  Dispose__10MenuRenderFv  size 0x5c
// MenuRender::Dispose()
void Dispose__10MenuRenderFv(MenuRender *this)
{
  int iVar1;
  iVar1 = this;
  if (this != 0) {
    iVar1 = this + 0x14;
  }
  Dispose__7CPollerFP7CPolObj(app__4CApp + 0x54,iVar1);
  ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,this);
  return;
}

// JP: 0x00265ed0  ChengeLayer__10MenuRenderFi  size 0x4c
// MenuRender::ChengeLayer(int)
void ChengeLayer__10MenuRenderFi(MenuRender *this,u32 param_2)
{
  ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,this);
  AddOT__5WorldFiP8VIF1Prim(0x42bf10,param_2,this);
  return;
}

// JP: 0x00265f20  Polling__10MenuRenderFv  size 0x30
// MenuRender::Polling()
u64 Polling__10MenuRenderFv(MenuRender *this)
{
  TracePolling__12MenuObjTableFv(this + 0x2c);
  return 0;
}

// JP: 0x00265f50  getPacket__10MenuRenderFv  size 0x1b8
// MenuRender::getPacket()
u32 getPacket__10MenuRenderFv(MenuRender *this)
{
  int iVar1;
  int iVar2;
  u32 *puVar3;
  u32 uVar4;
  if (this == &sm_menuRender__7MenuObj) {
    UpdateTimer__7MenuObjFv();
  }
  if (this->f_30 /*int **/ == 0) {
    uVar4 = 0;
  }
  else {
    iVar1 = *(int *)(this + (m_Env__8VIF1Prim & 1) * 4);
    if (camera__4CApp != 0) {
      iVar2 = *(int *)(this + (m_Env__8VIF1Prim & 1) * 4);
      *(u64 *)(iVar2 + 0x40) = *(u64 *)(camera__4CApp + 0x60);
      *(u8 *)(iVar2 + 0x44) = *(u8 *)(iVar2 + 0x44) & 0xfe | 1;
      *(int *)(iVar2 + 0x84) = camera__4CApp + 0x1c0;
    }
    TraceUpdate__12MenuObjTableFiiUs(this + 0x2c,0x7000,0x7200,0x8000);
    puVar3 = (u32 *)TraceConnect__12MenuObjTableFP4_QWD(this + 0x2c,iVar1 + 0x70);
    *puVar3 = 0x20000000;
    puVar3[1] = *(int *)(this + (m_Env__8VIF1Prim & 1) * 4) + 0x80;
    uVar4 = *(u32 *)(this + (m_Env__8VIF1Prim & 1) * 4);
  }
  return uVar4;
}

// JP: 0x00266110  @20@Polling__10MenuRenderFv  size 0x8
// @20@Polling__10MenuRenderFv
u64 _20_Polling__10MenuRenderFv(MenuRender *this)
{
  TracePolling__12MenuObjTableFv(this + 0x18);
  return 0;
}

// JP: 0x00266120  @20@__dt__10MenuRenderFv  size 0x8
// @20@__dt__10MenuRenderFv
int _20___dt__10MenuRenderFv(MenuRender *this,short param_2)
{
  int iVar1;
  iVar1 = this + -0x14;
  if (iVar1 != 0) {
    *(u8 **)(this + -4) = __vt__10MenuRender;
    this->f_14 /*u32 **/ = 0x404f90;
    this->f_18 /*u32 **/ = 0x404fa0;
    Release__10MenuRenderFv(iVar1);
    __dt__12MenuObjTableFv(this + 0x18,0);
    __dt__7CPolObjFv(this,0);
    __dt__8VIF1PrimFv(iVar1,0);
    if (0 < param_2) {
      __dl__FPv(iVar1);
    }
  }
  return iVar1;
}

// JP: 0x00266130  @44@__dt__10MenuRenderFv  size 0x8
// @44@__dt__10MenuRenderFv
u32 * _44___dt__10MenuRenderFv(MenuRender *this,short param_2)
{
  u32 *puVar1;
  puVar1 = this + -0xb;
  if (puVar1 != (u32 *)0x0) {
    this[-7] = __vt__10MenuRender;
    this[-1] = 0x404f90;
    *this = 0x404fa0;
    Release__10MenuRenderFv(puVar1);
    __dt__12MenuObjTableFv(this,0);
    __dt__7CPolObjFv(this + -6,0);
    __dt__8VIF1PrimFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}
