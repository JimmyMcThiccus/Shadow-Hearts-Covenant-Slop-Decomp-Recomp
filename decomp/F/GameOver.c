/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x003abe10  ReceiveEvent__8GameOverFiPv  size 0x8c
// GameOver::ReceiveEvent(int, void*)
void ReceiveEvent__8GameOverFiPv(int param_1,int this)
{
  u64 uVar1;
  if (param_1 != 5) {
    if (param_1 != 4) {
      return;
    }
    uVar1 = GetScene__4MenuFs(this,0);
    ShiftTitle__13GameOverSceneFv(uVar1);
  }
  (**(code **)(this->f_14 /*int **/ + 0x30))();
  return;
}

// JP: 0x003abea0  __ct__8GameOverFv  size 0x298
// GameOver::GameOver()
u64 __ct__8GameOverFv(GameOver *this)
{
  int iVar1;
  u32 uVar2;
  long lVar3;
  u64 uVar4;
  int iVar5;
  __ct__4MenuFv(this);
  iVar5 = (int)this;
  *(u8 **)(iVar5 + 0x14) = __vt__8GameOver;
  *(u32 *)(iVar5 + 0x20) = 0x4074d0;
  lVar3 = __nw__FUi(0x70);
  uVar4 = 0;
  if (lVar3 != 0) {
    uVar4 = __ct__13GameOverSceneFv(lVar3);
  }
  *(u16 *)((int)uVar4 + 0x1c) = 0;
  OrderFile__9MenuSceneFPCcP4Menu(uVar4,0x4014d0,this);
  AddScene__4MenuFP9MenuScene(this,uVar4);
  Entry__7CPollerFP7CPolObjib(app__4CApp + 0x48,this,0x80,0);
  iVar1 = camera__4CApp;
  *(int *)(iVar5 + 0x50) = camera__4CApp;
  if (iVar1 == 0) {
    lVar3 = __nw__FUi(0x3a0);
    uVar2 = 0;
    if (lVar3 != 0) {
      uVar2 = __ct__9GsxCameraFUiUiUiUiUi(lVar3,0,0,0,0x18,0);
    }
    *(u32 *)(iVar5 + 0x50) = uVar2;
    iVar1 = *(int *)(iVar5 + 0x50);
    *(u8 *)(iVar1 + 0x388) = 0xff;
    *(u8 *)(iVar1 + 0x389) = 0xff;
    *(u8 *)(iVar1 + 0x38a) = 0xff;
    *(u8 *)(iVar1 + 0x38b) = 0x80;
    *(u64 *)(iVar1 + 0x150) = 0xffffff;
    iVar1 = *(int *)(iVar5 + 0x50);
    *(u32 *)(iVar1 + 0x380) = 0x3f800000;
    *(u32 *)(iVar1 + 900) = 0x447a0000;
    *(u32 *)(iVar1 + 0x360) = 0;
    *(u32 *)(iVar1 + 0x364) = *(u32 *)(iVar1 + 0x380);
    *(float *)(iVar1 + 0x368) = 256.0 / (*(float *)(iVar1 + 900) - *(float *)(iVar1 + 0x380));
    *(u32 *)(iVar1 + 0x36c) = 0x437f0000;
    *(u32 *)(*(int *)(iVar5 + 0x50) + 0x374) = 0x46fa0000;
    *(u32 *)(*(int *)(iVar5 + 0x50) + 0x370) = 0x3dcccccd;
    SetViewMatrix__9GsxCameraFfffff
              (0x44960000,0x3f4ccccd,0x3f6eeeef,0x3f800000,0x4b7fff28,*(u32 *)(iVar5 + 0x50))
    ;
    camera__4CApp = *(int *)(iVar5 + 0x50);
    SetCamera__5WorldFUiiP9GsxCamera(0x42bf10,0,0);
  }
  *(u32 *)(*(int *)(iVar5 + 0x50) + 0x180) = 0;
  return this;
}

// JP: 0x003ac140  __dt__8GameOverFv  size 0x84
// GameOver::~GameOver()
int __dt__8GameOverFv(GameOver *this,short param_2)
{
  if (this != 0) {
    this->f_14 /*u8 **/ = __vt__8GameOver;
    this->vptr_dd = 0x4074d0;
    __dt__4MenuFv(this,0);
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

// JP: 0x003ac1d0  Polling__8GameOverFv  size 0x2c
// GameOver::Polling()
u64 Polling__8GameOverFv(GameOver *this)
{
  Run__4MenuFv(this);
  return 0;
}

// JP: 0x003ac200  DelayDelete__8GameOverFv  size 0x4c
// GameOver::DelayDelete()
void DelayDelete__8GameOverFv(GameOver *this)
{
  Dispose__7CPollerFP7CPolObj(app__4CApp + 0x48,this);
  DestroyList__4MenuFv(this);
  DelayDelete__17DelayDeleteObjectFv(this + 0x18);
  return;
}

// JP: 0x003ac250  @24@DelayDelete__8GameOverFv  size 0x8
// @24@DelayDelete__8GameOverFv
void _24_DelayDelete__8GameOverFv(GameOver *this)
{
  Dispose__7CPollerFP7CPolObj(app__4CApp + 0x48,this + -0x18);
  DestroyList__4MenuFv(this + -0x18);
  DelayDelete__17DelayDeleteObjectFv(this);
  return;
}

// JP: 0x003ac260  @24@__dt__8GameOverFv  size 0x8
// @24@__dt__8GameOverFv
int _24___dt__8GameOverFv(GameOver *this,short param_2)
{
  int iVar1;
  iVar1 = this + -0x18;
  if (iVar1 != 0) {
    *(u8 **)(this + -4) = __vt__8GameOver;
    this->vptr = 0x4074d0;
    __dt__4MenuFv(iVar1,0);
    if (0 < param_2) {
      __dl__FPv(iVar1);
    }
  }
  return iVar1;
}
