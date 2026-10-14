/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x003a61f0  __ct__8dispCashFv  size 0x38
// dispCash::dispCash()
u32 * __ct__8dispCashFv(dispCash *this)
{
  *this = 0;
  this[3] = 0;
  this[4] = 0;
  return this;
}

// JP: 0x003a6230  __dt__8dispCashFv  size 0x7c
// dispCash::~dispCash()
int * __dt__8dispCashFv(dispCash *this,short param_2)
{
  if (this != (int *)0x0) {
    if (*this != 0) {
      DelayDeleteRequest__7primWinFv(*this);
      *this = 0;
    }
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

// JP: 0x003a62b0  initialize__8dispCashFP7primTexiii  size 0x68
// dispCash::initialize(primTex*, int, int, int)
void initialize__8dispCashFP7primTexiii
               (dispCash *this,u32 param_2,u32 param_3,u32 param_4,
               u32 param_5)
{
  this->f_14 /*u32 **/ = param_2;
  this->link_next = param_3;
  this->vptr = param_4;
  this->cash = param_5;
  mSetupCash__8dispCashFv(this);
  return;
}

// JP: 0x003a6320  setPos__8dispCashFff  size 0x94
// dispCash::setPos(float, float)
void setPos__8dispCashFff(dispCash *this,int param_2,int *param_3)
{
  param_3[3] = this;
  param_3[4] = param_2;
  if (*param_3 != 0) {
    SetPosition__10MenuWindowFff(param_3[3],param_3[4],*param_3 + 0x3c);
  }
  return;
}

// JP: 0x003a63c0  getPW__8dispCashFv  size 0x1c
// dispCash::getPW()
u32 getPW__8dispCashFv(dispCash *this)
{
  return *this;
}

// JP: 0x003a63e0  mSetupCash__8dispCashFv  size 0x1b0
// dispCash::mSetupCash()
void mSetupCash__8dispCashFv(dispCash *this)
{
  int iVar1;
  long lVar2;
  int iVar3;
  if (*this == 0) {
    lVar2 = __nw__FUi(0x148);
    iVar1 = 0;
    if (lVar2 != 0) {
      iVar1 = __ct__7primWinFv(lVar2);
    }
    *this = iVar1;
    iVar1 = *this;
    initialize__7primWinFP7primTex(iVar1,this[5]);
    setItem__7primWinFiii(iVar1,2,0xb,0);
    setTex__7primWinFiiii(iVar1,this[1],0,0x10,0x14);
    setTex__7primWinFiiii(iVar1,this[2],1,0x30,0x18);
    for (iVar3 = 0; iVar3 < 10; iVar3 = iVar3 + 1) {
      createTexPoly__7primWinFiiiiii(iVar1,iVar3,0,iVar3 * 10 + 0x30,0,0,0);
    }
    createTexPoly__7primWinFiiiiii(iVar1,10,1,0,0,0,0);
    buildWin__7primWinFiiiiii(iVar1,8,(int)(float)this[3],(int)(float)this[4],0,0,0);
    mCalcCash__8dispCashFv(this);
  }
  return;
}

// JP: 0x003a6590  mCalcCash__8dispCashFv  size 0x1fc
// dispCash::mCalcCash()
void mCalcCash__8dispCashFv(dispCash *this)
{
  u64 uVar1;
  int iVar2;
  int iVar3;
  u8 *puVar4;
  u8 *puVar5;
  int iVar6;
  puVar4 = (u8 *)((int)this + 0x25);
  iVar2 = this[6];
  iVar6 = 9;
  do {
    iVar3 = iVar2 % 10;
    iVar2 = iVar2 / 10;
    puVar5 = puVar4 + -1;
    *puVar4 = (char)iVar3;
    iVar3 = iVar6 + -1;
    if (((iVar3 == 6) || (iVar3 == 2)) && (iVar2 != 0)) {
      *puVar5 = 10;
      puVar5 = puVar4 + -2;
      iVar3 = iVar6 + -2;
    }
    iVar6 = iVar3;
    puVar4 = puVar5;
  } while (0 < iVar2);
  for (; -1 < iVar6; iVar6 = iVar6 + -1) {
    *puVar4 = 0xc;
    puVar4 = puVar4 + -1;
  }
  for (iVar2 = 0; iVar2 < 10; iVar2 = iVar2 + 1) {
    uVar1 = getPP__7primWinFi(*this,iVar2);
    SetUV__11MenuPolygonFUsUsUsUs
              (uVar1,*(char *)((int)this + iVar2 + 0x1c) * 0x10 + 1,1,
               (*(char *)((int)this + iVar2 + 0x1c) + 1) * 0x10,0x14);
    setPolyAlpha__7primWinFii(*this,iVar2,0x80);
    if (*(char *)((int)this + iVar2 + 0x1c) == '\f') {
      setPolyAlpha__7primWinFii(*this,iVar2,0);
    }
  }
  return;
}
