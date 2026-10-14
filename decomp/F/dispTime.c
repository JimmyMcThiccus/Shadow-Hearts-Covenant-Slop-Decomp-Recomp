/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x003a59b0  __ct__8dispTimeFv  size 0x5c
// dispTime::dispTime()
int __ct__8dispTimeFv(dispTime *this)
{
  __ct__7CPolObjFv(this);
  this->f_14 /*u8 **/ = __vt__8dispTime;
  this->win = 0;
  this->x = 0;
  this->y = 0;
  return this;
}

// JP: 0x003a5a10  __dt__8dispTimeFv  size 0xc4
// dispTime::~dispTime()
int __dt__8dispTimeFv(dispTime *this,short param_2)
{
  if (this != 0) {
    this->f_14 /*u8 **/ = __vt__8dispTime;
    if (this->win != 0) {
      DelayDeleteRequest__7primWinFv(this->win);
      this->win = 0;
    }
    if (this->autostart != '\0') {
      Dispose__7CPollerFP7CPolObj(app__4CApp + 0x48,this);
    }
    __dt__7CPolObjFv(this,0);
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

// JP: 0x003a5ae0  initialize__8dispTimeFP7primTexiiib  size 0xbc
// dispTime::initialize(primTex*, int, int, int, bool)
void initialize__8dispTimeFP7primTexiiib
               (dispTime *this,u32 param_2,u32 param_3,u32 param_4,
               u32 param_5,u8 param_6)
{
  this->tex0 = param_2;
  this->tex1 = param_3;
  this->f_24 /*u32 **/ = param_4;
  this->ms = param_5;
  this->autostart = param_6;
  this->running = 0;
  if (this->autostart != '\0') {
    this->running = 1;
    Entry__7CPollerFP7CPolObjib(app__4CApp + 0x48,this,0x80,0);
  }
  mSetupTime__8dispTimeFv(this);
  return;
}

// JP: 0x003a5ba0  setPos__8dispTimeFff  size 0x94
// dispTime::setPos(float, float)
void setPos__8dispTimeFff(u32 param_1,u32 param_2,int this)
{
  this->x = param_1;
  this->y = param_2;
  if (this->win != 0) {
    SetPosition__10MenuWindowFff
              (this->x,this->y,
               this->win + 0x3c);
  }
  return;
}

// JP: 0x003a5c40  getPW__8dispTimeFv  size 0x1c
// dispTime::getPW()
u32 getPW__8dispTimeFv(dispTime *this)
{
  return this->win;
}

// JP: 0x003a5c60  mSetupTime__8dispTimeFv  size 0x1b4
// dispTime::mSetupTime()
void mSetupTime__8dispTimeFv(dispTime *this)
{
  u32 uVar1;
  long lVar2;
  int iVar3;
  if (this->win == 0) {
    lVar2 = __nw__FUi(0x148);
    uVar1 = 0;
    if (lVar2 != 0) {
      uVar1 = __ct__7primWinFv(lVar2);
    }
    this->win = uVar1;
    uVar1 = this->win;
    initialize__7primWinFP7primTex(uVar1,this->tex0);
    setItem__7primWinFiii(uVar1,2,0xb,0);
    setTex__7primWinFiiii(uVar1,this->tex1,0,0x10,0x14);
    setTex__7primWinFiiii(uVar1,this->f_24 /*u32 **/,1,0x30,0x18);
    for (iVar3 = 0; iVar3 < 10; iVar3 = iVar3 + 1) {
      createTexPoly__7primWinFiiiiii(uVar1,iVar3,0,iVar3 * 10 + 0x30,0,0,0);
    }
    createTexPoly__7primWinFiiiiii(uVar1,10,1,0,0,1,0);
    buildWin__7primWinFiiiiii
              (uVar1,7,(int)this->x,(int)this->y,0,0,0);
  }
  mCalcTime__8dispTimeFv(this);
  return;
}

// JP: 0x003a5e20  mCalcTime__8dispTimeFv  size 0x354
// dispTime::mCalcTime()
void mCalcTime__8dispTimeFv(dispTime *this)
{
  int iVar1;
  u64 uVar2;
  u8 *puVar3;
  int iVar4;
  int iVar5;
  iVar4 = (this->ms / 1000) % 0x3c;
  iVar1 = (this->ms / 60000) % 0x3c;
  iVar5 = this->ms / 3600000;
  this->f_3f /*char **/ = (char)(iVar4 % 10);
  this->f_3e /*char **/ = (char)(iVar4 / 10);
  this->f_3d /*u8 **/ = 0xb;
  this->f_3c /*char **/ = (char)(iVar1 % 10);
  this->f_3b /*char **/ = (char)(iVar1 / 10);
  puVar3 = (u8 *)(this + 0x39);
  this->f_3a /*u8 **/ = 0xb;
  for (iVar4 = 0; iVar4 < 4; iVar4 = iVar4 + 1) {
    if ((iVar4 == 0) || (iVar5 != 0)) {
      *puVar3 = (char)(iVar5 % 10);
      iVar5 = iVar5 / 10;
    }
    else {
      *puVar3 = 0xc;
    }
    puVar3 = puVar3 + -1;
  }
  for (iVar4 = 0; iVar4 < 10; iVar4 = iVar4 + 1) {
    uVar2 = getPP__7primWinFi(this->win,iVar4);
    SetUV__11MenuPolygonFUsUsUsUs
              (uVar2,*(char *)(this + iVar4 + 0x36) * 0x10 + 1,1,
               (*(char *)(this + iVar4 + 0x36) + 1) * 0x10,0x14);
    setPolyAlpha__7primWinFii(this->win,iVar4,0x80);
    if (*(char *)(this + iVar4 + 0x36) == '\f') {
      setPolyAlpha__7primWinFii(this->win,iVar4,0);
    }
  }
  return;
}

// JP: 0x003a6180  Polling__8dispTimeFv  size 0x68
// dispTime::Polling()
u64 Polling__8dispTimeFv(dispTime *this)
{
  if ((*(char *)(this->win + 0x102) == '\0') && (this->running != '\0'))
  {
    this->ms = this->ms + 0x10;
    mCalcTime__8dispTimeFv(this);
  }
  return 0;
}
