/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x002851a0  ReleaseImage__8MenuFontFv  size 0x58
// MenuFont::ReleaseImage()
void ReleaseImage__8MenuFontFv(void)
{
  int iVar1;
  for (iVar1 = 0; iVar1 < 2; iVar1 = iVar1 + 1) {
    Release__11MenuTextureFv(&sm_image__8MenuFont + iVar1 * 0x40);
  }
  return;
}

// JP: 0x00285200  __ct__8MenuFontFv  size 0x70
// MenuFont::MenuFont()
int __ct__8MenuFontFv(MenuFont *this)
{
  __ct__14PluralFontItemFv(this);
  this->f_8 /*u8 **/ = __vt__8MenuFont;
  this->f_3c /*u32 **/ = 0x405664;
  __ct__11SendOnLocalFv(this + 0x80);
  (**(code **)(this->f_8 /*int **/ + 0x20))();
  return this;
}

// JP: 0x00285270  __dt__8MenuFontFv  size 0xac
// MenuFont::~MenuFont()
int __dt__8MenuFontFv(MenuFont *this,short param_2)
{
  if (this != 0) {
    this->f_8 /*u8 **/ = __vt__8MenuFont;
    this->f_3c /*u32 **/ = 0x405664;
    (**(code **)(this->f_8 /*int **/ + 0x1c))();
    __dt__11SendOnLocalFv(this + 0x80,0xffffffffffffffff);
    __dt__14PluralFontItemFv(this,0);
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

// JP: 0x00285320  CreateFont__8MenuFontFiUsUc  size 0x204
// MenuFont::CreateFont(int, unsigned short, unsigned char)
u32
CreateFont__8MenuFontFiUsUc(MenuFont *this,int param_2,u16 param_3,u8 param_4)
{
  u16 uVar1;
  int iVar2;
  u32 uVar3;
  long lVar4;
  int iVar5;
  short sVar6;
  if ((((&DAT_00421aea)[param_2 * 0x40] & 1) == 0) ||
     (lVar4 = (**(code **)(this->f_8 /*int **/ + 0x60))(this,param_3,param_4), lVar4 == 0)) {
    uVar3 = 0;
  }
  else {
    this->f_78 /*u16 **/ = param_3;
    this->f_7e /*u16 **/ = param_3;
    iVar5 = param_2 * 0xc;
    iVar2 = GetFontPacket__14PluralFontItemCFUc(this,0);
    sVar6 = 0;
    for (uVar1 = 0; uVar1 < this->f_74 /*u16 **/; uVar1 = uVar1 + 1) {
      *(short *)(iVar2 + 4) = sVar6;
      *(u16 *)(iVar2 + 6) = 0;
      *(char *)(iVar2 + 0xc) = (char)*(u16 *)(sm_data__8MenuFont + iVar5 + 4);
      *(char *)(iVar2 + 0xd) = (char)*(u16 *)(sm_data__8MenuFont + iVar5 + 6);
      sVar6 = sVar6 + *(short *)(sm_data__8MenuFont + iVar5 + 4);
      iVar2 = iVar2 + 0x30;
    }
    Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi
              (this + 0x80,param_2 * 0x40 + 0x421ac8,
               *(u32 *)(&DAT_00421ac4 + param_2 * 0x40),1,0);
    UpdatePacket__11SendOnLocalFv(this + 0x80);
    this->f_58 /*u8 **/ = this->f_58 /*u8 **/ & 0xf8 | (u8)param_2 & 7;
    uVar3 = 1;
  }
  return uVar3;
}

// JP: 0x00285530  Order__8MenuFontFPve  size 0x338
// MenuFont::Order(void*, e)
/* WARNING: Removing unreachable block (ram,0x0028558c) */
u32
Order__8MenuFontFPve
          (MenuFont *this,char *param_2,u64 param_3,u64 param_4,u64 param_5,
          u64 param_6,u64 param_7,u64 param_8)
{
  u16 uVar1;
  int iVar2;
  int iVar3;
  ulong uVar4;
  int iVar5;
  uint uVar6;
  char *pcVar7;
  char acStack_90 [64];
  int iStack_50;
  char *pcStack_40;
  u64 uStack_30;
  u64 uStack_28;
  u64 uStack_20;
  u64 uStack_18;
  u64 uStack_10;
  u64 uStack_8;
  iStack_50 = this;
  pcStack_40 = param_2;
  uStack_30 = param_3;
  uStack_28 = param_4;
  uStack_20 = param_5;
  uStack_18 = param_6;
  uStack_10 = param_7;
  uStack_8 = param_8;
  vsprintf(acStack_90,param_2,&uStack_30);
  iVar5 = (*(u8 *)(iStack_50 + 0x58) & 7) * 0xc;
  iVar2 = GetUpdatePacket__14PluralFontItemFv(iStack_50);
  iVar3 = GetFontPacket__14PluralFontItemCFUc(iStack_50,0);
  for (pcVar7 = acStack_90; *pcVar7 != '\0'; pcVar7 = pcVar7 + 1) {
    for (uVar6 = 0;
        (uVar6 < (u8)sm_data__8MenuFont[iVar5 + 10] &&
        (*pcVar7 != *(char *)(*(int *)(sm_data__8MenuFont + iVar5) + uVar6)));
        uVar6 = uVar6 + 1 & 0xffff) {
    }
    if (uVar6 == (u8)sm_data__8MenuFont[iVar5 + 10]) {
      *(u8 *)(iVar3 + 0x17) = 0;
    }
    else {
      uVar1 = *(u16 *)(sm_data__8MenuFont + iVar5 + 8);
      if (uVar1 == 0) {
        trap(7);
      }
      if (*(u16 *)(sm_data__8MenuFont + iVar5 + 8) == 0) {
        trap(7);
      }
      *(u16 *)(iVar2 + 0x10) =
           *(u16 *)(iVar2 + 0x10) & 0xc000 |
           (short)(uVar6 % (uint)*(u16 *)(sm_data__8MenuFont + iVar5 + 8)) *
           *(short *)(sm_data__8MenuFont + iVar5 + 4) * 0x10 & 0x3fffU;
      *(u16 *)(iVar2 + 0x12) =
           *(u16 *)(iVar2 + 0x12) & 0xc000 |
           (short)(uVar6 / uVar1) * *(short *)(sm_data__8MenuFont + iVar5 + 6) * 0x10 & 0x3fffU;
      *(u16 *)(iVar2 + 0x20) =
           *(u16 *)(iVar2 + 0x20) & 0xc000 |
           (*(u16 *)(iVar2 + 0x10) & 0x3fff) + *(short *)(sm_data__8MenuFont + iVar5 + 4) * 0x10
           & 0x3fff;
      *(u16 *)(iVar2 + 0x22) =
           *(u16 *)(iVar2 + 0x22) & 0xc000 |
           (*(u16 *)(iVar2 + 0x12) & 0x3fff) + *(short *)(sm_data__8MenuFont + iVar5 + 6) * 0x10
           & 0x3fff;
      *(u8 *)(iVar3 + 0x17) = 0x80;
    }
    iVar3 = iVar3 + 0x30;
    iVar2 = iVar2 + 0x30;
  }
  uVar4 = (ulong)*(u8 *)(iStack_50 + 0x11) & 0xffffffffffffffef | 0x10;
  *(char *)(iStack_50 + 0x11) = (char)uVar4;
  *(u8 *)(iStack_50 + 0x10) =
       *(u8 *)(iStack_50 + 0x10) & 0xef | (u8)((uint)((uVar4 << 0x3b) >> 0x3f) << 4);
  return 1;
}

// JP: 0x00285870  GetFontEnv__8MenuFontFv  size 0xa0
// MenuFont::GetFontEnv()
ulong GetFontEnv__8MenuFontFv(MenuFont *this)
{
  ulong uVar1;
  ulong uVar2;
  uVar2 = *this->f_a8 /*ulong **/;
  uVar1 = GetClutFlag__10ClutRasterFUcUc
                    (this->f_ac /*u32 **/,this->f_5d /*u8 **/,0);
  return uVar2 & 0x7ffffffff | uVar1;
}

// JP: 0x00285910  Connect__8MenuFontFP4_QWD  size 0x84
// MenuFont::Connect(_QWD*)
void Connect__8MenuFontFP4_QWD(MenuFont *this,u32 param_2)
{
  u32 uVar1;
  u32 uStack_10;
  uStack_10 = param_2;
  if (this->f_34 /*int **/ != 0) {
    uStack_10 = (**(code **)(*(int *)(this->f_34 /*int **/ + 8) + 0x18))
                          (this->f_34 /*int **/,param_2);
  }
  uVar1 = (**(code **)(this->f_88 /*int **/ + 0x18))(this + 0x80,uStack_10);
  ConnectPacket__10MenuPacketFP4_QWD(this + 0x3c,uVar1);
  return;
}

// JP: 0x002859a0  Destroy__8MenuFontFv  size 0x40
// MenuFont::Destroy()
void Destroy__8MenuFontFv(MenuFont *this)
{
  Destroy__8FontItemFv(this);
  (**(code **)(this->f_88 /*int **/ + 0x1c))();
  return;
}

// JP: 0x002859e0  Clear__8MenuFontFv  size 0x40
// MenuFont::Clear()
void Clear__8MenuFontFv(MenuFont *this)
{
  Clear__14PluralFontItemFv(this);
  (**(code **)(this->f_88 /*int **/ + 0x20))();
  return;
}

// JP: 0x00285a60  @60@__dt__8MenuFontFv  size 0x8
// @60@__dt__8MenuFontFv
u32 * _60___dt__8MenuFontFv(MenuFont *this,short param_2)
{
  u32 *puVar1;
  puVar1 = this + -0xf;
  if (puVar1 != (u32 *)0x0) {
    this[-0xd] = __vt__8MenuFont;
    *this = 0x405664;
    (**(code **)(this[-0xd] + 0x1c))();
    __dt__11SendOnLocalFv(this + 0x11,0xffffffffffffffff);
    __dt__14PluralFontItemFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}
