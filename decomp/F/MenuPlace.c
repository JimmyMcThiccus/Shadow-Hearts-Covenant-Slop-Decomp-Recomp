/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x00278ca0  __ct__9MenuPlaceFv  size 0x3c
// MenuPlace::MenuPlace()
int __ct__9MenuPlaceFv(MenuPlace *this)
{
  __ct__7MenuObjFv(this);
  this->vptr = __vt__9MenuPlace;
  return this;
}

// JP: 0x00278ce0  __dt__9MenuPlaceFv  size 0x74
// MenuPlace::~MenuPlace()
int __dt__9MenuPlaceFv(MenuPlace *this,short param_2)
{
  if (this != 0) {
    this->vptr = __vt__9MenuPlace;
    __dt__7MenuObjFv(this,0);
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

// JP: 0x00278d60  IsSelected__9MenuPlaceFP6Cursor  size 0x198
// MenuPlace::IsSelected(Cursor*)
u32 IsSelected__9MenuPlaceFP6Cursor(int param_1,int this)
{
  int iVar1;
  u32 uVar2;
  u8 auStack_40 [24];
  u32 uStack_28;
  u32 uStack_24;
  int iStack_20;
  int iStack_10;
  if ((long)((ulong)*(u8 *)(param_1 + 0x21) << 0x3e) < 0) {
    iStack_20 = param_1;
    iStack_10 = this;
    if (this->f_ec /*int **/ != 0) {
      IsCanceled__9MenuPlaceFP6Cursor(this->f_ec /*int **/,this);
    }
    *(u8 *)(iStack_20 + 0x21) = *(u8 *)(iStack_20 + 0x21) & 0xfb | 4;
    VCALL(iStack_20, 0x40 /*GetKeyRect*/)(iStack_20,auStack_40);
    GetTarget__6CursorFP8DrawRectPfPf(iStack_10,auStack_40,&uStack_24,&uStack_28);
    SetTarget__6CursorFff(uStack_24,uStack_28,iStack_10);
    *(int *)(iStack_10 + 0xec) = iStack_20;
    iVar1 = *(int *)(iStack_10 + 0xf0);
    *(int *)(iStack_20 + 0x34) = iVar1;
    if (iVar1 != 0) {
      (**(code **)(*(int *)(*(int *)(iStack_20 + 0x34) + 8) + 0x24))
                (*(u32 *)(iStack_20 + 0x24),*(u32 *)(iStack_20 + 0x28));
      (**(code **)(*(int *)(*(int *)(iStack_20 + 0x34) + 8) + 0x28))
                (*(u32 *)(iStack_20 + 0x2c),*(u32 *)(iStack_20 + 0x30));
      iVar1 = *(int *)(iStack_20 + 0x34);
      *(u8 *)(iVar1 + 0x10) = *(u8 *)(iVar1 + 0x10) | 0x3f;
      *(u8 *)(iVar1 + 0x11) = *(u8 *)(iVar1 + 0x11) | 0x3f;
    }
    uVar2 = 1;
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

// JP: 0x00278f00  IsCanceled__9MenuPlaceFP6Cursor  size 0x68
// MenuPlace::IsCanceled(Cursor*)
u32 IsCanceled__9MenuPlaceFP6Cursor(MenuPlace *this,Cursor *cursor)
{
  if ((long)((ulong)this->pflags << 0x3d) < 0) {
    this->attached = 0;
    this->pflags = this->pflags & 0xfb;
    cursor->place = 0;
  }
  return 1;
}

// JP: 0x00278f70  SetPosition__9MenuPlaceFff  size 0xb8
// MenuPlace::SetPosition(float, float)
void SetPosition__9MenuPlaceFff(u32 param_1,u32 param_2,int this)
{
  ulong uVar1;
  this->x = param_1;
  this->y = param_2;
  uVar1 = (ulong)this->dirty1 & 0xfffffffffffffff7 | 8;
  this->dirty1 = (char)uVar1;
  this->dirty0 =
       this->dirty0 & 0xf7 | (u8)((uint)((uVar1 << 0x3c) >> 0x3f) << 3);
  if (this->attached != 0) {
    VCALL(this, 0x24 /*SetPosition*/)(param_1,param_2);
  }
  return;
}

// JP: 0x00279030  SetSize__9MenuPlaceFff  size 0xb8
// MenuPlace::SetSize(float, float)
void SetSize__9MenuPlaceFff(u32 param_1,u32 param_2,int this)
{
  ulong uVar1;
  this->w = param_1;
  this->h = param_2;
  uVar1 = (ulong)this->dirty1 & 0xfffffffffffffff7 | 8;
  this->dirty1 = (char)uVar1;
  this->dirty0 =
       this->dirty0 & 0xf7 | (u8)((uint)((uVar1 << 0x3c) >> 0x3f) << 3);
  if (this->attached != 0) {
    VCALL(this, 0x28 /*SetSize*/)(param_1,param_2);
  }
  return;
}

// JP: 0x002790f0  SetAlpha__9MenuPlaceFUc  size 0x10
// MenuPlace::SetAlpha(unsigned char)
void SetAlpha__9MenuPlaceFUc(void)
{
  return;
}

// JP: 0x00279100  SetColor__9MenuPlaceFUcUcUc  size 0x10
// MenuPlace::SetColor(unsigned char, unsigned char, unsigned char)
void SetColor__9MenuPlaceFUcUcUc(void)
{
  return;
}

// JP: 0x00279110  SetBright__9MenuPlaceFf  size 0x10
// MenuPlace::SetBright(float)
void SetBright__9MenuPlaceFf(void)
{
  return;
}

// JP: 0x00279120  SetOwner__9MenuPlaceFP10MenuWindow  size 0x24
// MenuPlace::SetOwner(MenuWindow*)
void SetOwner__9MenuPlaceFP10MenuWindow(MenuPlace *this,u32 menuWindow)
{
  this->owner = menuWindow;
  return;
}

// JP: 0x00279150  GetKeyPlace__9MenuPlaceFv  size 0x18
// MenuPlace::GetKeyPlace()
u32 GetKeyPlace__9MenuPlaceFv(MenuPlace *this)
{
  return this;
}

// JP: 0x00279170  GetKeyRect__9MenuPlaceFP8DrawRect  size 0x58
// MenuPlace::GetKeyRect(DrawRect*)
void GetKeyRect__9MenuPlaceFP8DrawRect(MenuPlace *this,u32 *param_2)
{
  *param_2 = this->x;
  param_2[1] = this->y;
  param_2[2] = this->w;
  param_2[3] = this->h;
  return;
}

// JP: 0x002791d0  AllotPacket__9MenuPlaceFP4_QWDP4_QWD  size 0x10
// MenuPlace::AllotPacket(_QWD*, _QWD*)
void AllotPacket__9MenuPlaceFP4_QWDP4_QWD(void)
{
  return;
}

// JP: 0x002791e0  GetAllotCount__9MenuPlaceFv  size 0x14
// MenuPlace::GetAllotCount()
u64 GetAllotCount__9MenuPlaceFv(void)
{
  return 0;
}

// JP: 0x00279200  Attach__9MenuPlaceFP10MenuWindow  size 0x34
// MenuPlace::Attach(MenuWindow*)
void Attach__9MenuPlaceFP10MenuWindow(u32 param_1,int this)
{
  AddPriority__12MenuObjTableFP7MenuObj(this + 0x18,param_1);
  return;
}

// JP: 0x00279240  Detach__9MenuPlaceFv  size 0x48
// MenuPlace::Detach()
void Detach__9MenuPlaceFv(MenuPlace *this)
{
  if (this->owner != 0) {
    RemoveObj__12MenuObjTableFP7MenuObj(this->owner + 0x18,this);
  }
  return;
}

// JP: 0x00279290  Clear__9MenuPlaceFv  size 0x90
// MenuPlace::Clear()
void * Clear__9MenuPlaceFv(MenuPlace *this)
{
  void *pvVar1;
  Clear__7MenuObjFv(this);
  this->owner = 0;
  this->row = 0xffff;
  this->col = 0xffff;
  this->state = 0;
  this->label = 0;
  this->attached = 0;
  this->next_place = 0;
  this->pflags = 0x2a;
  pvVar1 = memset((void *)(this + 0x24),0,0x10);
  return pvVar1;
}
