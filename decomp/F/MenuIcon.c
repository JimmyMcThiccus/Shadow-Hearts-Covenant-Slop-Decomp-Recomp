/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x0028e640  __ct__8MenuIconFv  size 0x3c
// MenuIcon::MenuIcon()
u32 * __ct__8MenuIconFv(MenuIcon *this)
{
  __ct__12MenuObjTableFv(this);
  *this = __vt__8MenuIcon;
  return this;
}

// JP: 0x0028e680  __dt__8MenuIconFv  size 0x74
// MenuIcon::~MenuIcon()
u32 * __dt__8MenuIconFv(MenuIcon *this,short param_2)
{
  if (this != (u32 *)0x0) {
    *this = __vt__8MenuIcon;
    __dt__12MenuObjTableFv(this,0);
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

// JP: 0x0028e700  Create__8MenuIconFc  size 0x2d0
// MenuIcon::Create(char)
u64 Create__8MenuIconFc(u32 param_1,char this)
{
  short sVar1;
  long lVar2;
  u64 uVar3;
  u64 uVar4;
  int iVar5;
  u8 uStack_10;
  lVar2 = __nw__FUi(0x30);
  uVar3 = 0;
  if (lVar2 != 0) {
    uVar3 = __ct__11SendOnLocalFv(lVar2);
  }
  lVar2 = __nw__FUi(0x60);
  uVar4 = 0;
  if (lVar2 != 0) {
    uVar4 = __ct__10MenuSpriteFv(lVar2);
  }
  iVar5 = -1;
  sVar1 = (short)((int)this >> 5);
  if (2 < sVar1) {
    sVar1 = 2;
  }
  if (sVar1 == 2) {
    iVar5 = (int)(char)(this + -0x40) / 5;
    uStack_10 = (char)(this + -0x40) % '\x05';
  }
  else if (sVar1 == 0) {
    uStack_10 = this;
    if ('\x0f' < this) {
      uStack_10 = (char)*(u16 *)
                         (*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x26c +
                         (this + -0x10) * 2);
    }
  }
  else {
    uStack_10 = this + -0x20;
  }
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi
            (uVar3,sVar1 * 0x40 + 0x421670,*(u32 *)(sVar1 * 0x40 + 0x42166c),1,iVar5);
  SetData__9MenuSceneFUsP10MenuSprite(0x421600,0x12,uVar4);
  SetIcon__10MenuCommonFcP10MenuSprite(uStack_10,uVar4);
  iVar5 = (int)uVar4;
  *(int *)(iVar5 + 0x5c) = (int)uVar3;
  *(u8 *)(iVar5 + 0x12) = *(u8 *)(iVar5 + 0x12) & 0xdf | 0x20;
  AddPriority__12MenuObjTableFP7MenuObj(param_1,uVar4);
  return uVar4;
}

// JP: 0x0028e9d0  Destroy__8MenuIconFv  size 0x70
// MenuIcon::Destroy()
void Destroy__8MenuIconFv(MenuIcon *this)
{
  int iVar1;
  for (iVar1 = this->f_4 /*int **/; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0xc)) {
    VCALL(iVar1, 0xc /*DelayDelete*/)();
  }
  this->f_4 /*u32 **/ = 0;
  return;
}

// JP: 0x0028ea40  SetOwner__8MenuIconFP10MenuWindow  size 0x68
// MenuIcon::SetOwner(MenuWindow*)
void SetOwner__8MenuIconFP10MenuWindow(MenuIcon *this,u32 menuWindow)
{
  int iVar1;
  for (iVar1 = this->f_4 /*int **/; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0xc)) {
    VCALL(iVar1, 0x38 /*SetOwner*/)(iVar1,menuWindow);
  }
  return;
}

// JP: 0x0028eab0  Finish__8MenuIconFv  size 0x88
// MenuIcon::Finish()
void Finish__8MenuIconFv(MenuIcon *this)
{
  int iVar1;
  for (iVar1 = this->f_4 /*int **/; iVar1 != 0; iVar1 = *(int *)(iVar1 + 0xc)) {
    VCALL(iVar1, 0x2c /*SetAlpha*/)(iVar1,0x80);
    *(u8 *)(iVar1 + 0x12) = *(u8 *)(iVar1 + 0x12) & 0xfe | 1;
  }
  return;
}
