/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x00285a70  SetImage__14MenuFontItalicFPUc  size 0x5c
// MenuFontItalic::SetImage(unsigned char*)
void SetImage__14MenuFontItalicFPUc(MenuFontItalic *this)
{
  if (sm_reference__14MenuFontItalic == 0) {
    Create__11MenuTextureFPUc6GS_PSMUii(0x421b40,this,0x30,0,0);
  }
  sm_reference__14MenuFontItalic = sm_reference__14MenuFontItalic + 1;
  return;
}

// JP: 0x00285ad0  ReleaseImage__14MenuFontItalicFv  size 0x48
// MenuFontItalic::ReleaseImage()
void ReleaseImage__14MenuFontItalicFv(void)
{
  sm_reference__14MenuFontItalic = sm_reference__14MenuFontItalic + -1;
  if (sm_reference__14MenuFontItalic == 0) {
    Release__11MenuTextureFv(0x421b40);
  }
  return;
}

// JP: 0x00285b20  __ct__14MenuFontItalicFv  size 0x60
// MenuFontItalic::MenuFontItalic()
int __ct__14MenuFontItalicFv(MenuFontItalic *this)
{
  __ct__8MenuFontFv(this);
  this->f_8 /*u8 **/ = __vt__14MenuFontItalic;
  this->f_3c /*u32 **/ = 0x4056d4;
  (**(code **)(this->f_8 /*int **/ + 0x20))();
  return this;
}

// JP: 0x00285b80  __dt__14MenuFontItalicFv  size 0x94
// MenuFontItalic::~MenuFontItalic()
int __dt__14MenuFontItalicFv(MenuFontItalic *this,short param_2)
{
  if (this != 0) {
    this->f_8 /*u8 **/ = __vt__14MenuFontItalic;
    this->f_3c /*u32 **/ = 0x4056d4;
    (**(code **)(this->f_8 /*int **/ + 0x1c))();
    __dt__8MenuFontFv(this,0);
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

// JP: 0x00285c20  CreateItalic__14MenuFontItalicFPc  size 0x298
// MenuFontItalic::CreateItalic(char*)
u32 CreateItalic__14MenuFontItalicFPc(MenuFontItalic *this,char *param_2)
{
  int iVar1;
  u32 uVar2;
  long lVar3;
  char *pcVar4;
  int iVar5;
  u8 *unaff_s3_lo;
  short sVar6;
  sVar6 = 0;
  for (pcVar4 = param_2; *pcVar4 != '\0'; pcVar4 = pcVar4 + 1) {
    lVar3 = 0;
    while ((lVar3 < sm_dataCount__14MenuFontItalic &&
           (*pcVar4 != sm_data__14MenuFontItalic[(int)lVar3 * 8]))) {
      lVar3 = (long)((int)lVar3 + 1);
    }
    if (lVar3 == sm_dataCount__14MenuFontItalic) {
      return 0;
    }
    sVar6 = sVar6 + 1;
  }
  lVar3 = (**(code **)(this->f_8 /*int **/ + 0x60))(this,sVar6,0);
  if (lVar3 == 0) {
    uVar2 = 0;
  }
  else {
    this->f_78 /*short **/ = sVar6;
    this->f_7e /*short **/ = sVar6;
    iVar1 = GetFontPacket__14PluralFontItemCFUc(this,0);
    sVar6 = 0;
    for (; *param_2 != '\0'; param_2 = param_2 + 1) {
      lVar3 = 0;
      while (lVar3 < sm_dataCount__14MenuFontItalic) {
        iVar5 = (int)lVar3;
        if (*param_2 == sm_data__14MenuFontItalic[iVar5 * 8]) {
          unaff_s3_lo = sm_data__14MenuFontItalic + iVar5 * 8;
          break;
        }
        lVar3 = (long)(iVar5 + 1);
      }
      *(short *)(iVar1 + 4) = sVar6;
      *(u16 *)(iVar1 + 6) = 0;
      *(u8 *)(iVar1 + 0xc) = unaff_s3_lo[1];
      *(u8 *)(iVar1 + 0xd) = unaff_s3_lo[2];
      sVar6 = sVar6 + (short)(char)unaff_s3_lo[1] + (short)(char)unaff_s3_lo[3];
      iVar1 = iVar1 + 0x30;
    }
    Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi
              (this + 0x80,0x421b58,DAT_00421b54,1,0xffffffffffffffff);
    UpdatePacket__11SendOnLocalFv(this + 0x80);
    uVar2 = 1;
  }
  return uVar2;
}

// JP: 0x00285ec0  Order__14MenuFontItalicFPve  size 0x2c4
// MenuFontItalic::Order(void*, e)
/* WARNING: Removing unreachable block (ram,0x00285f18) */
u32
Order__14MenuFontItalicFPve
          (MenuFontItalic *this,char *param_2,u64 param_3,u64 param_4,u64 param_5,
          u64 param_6,u64 param_7,u64 param_8)
{
  int iVar1;
  int iVar2;
  ulong uVar3;
  u8 *puVar4;
  char *pcVar5;
  int iVar6;
  long lVar7;
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
  pcVar5 = acStack_90;
  iVar1 = GetUpdatePacket__14PluralFontItemFv(iStack_50);
  iVar2 = GetFontPacket__14PluralFontItemCFUc(iStack_50,0);
  do {
    if (*pcVar5 == '\0') {
      uVar3 = (ulong)*(u8 *)(iStack_50 + 0x11) & 0xffffffffffffffef | 0x10;
      *(char *)(iStack_50 + 0x11) = (char)uVar3;
      *(u8 *)(iStack_50 + 0x10) =
           *(u8 *)(iStack_50 + 0x10) & 0xef | (u8)((uint)((uVar3 << 0x3b) >> 0x3f) << 4);
      return 1;
    }
    puVar4 = (u8 *)0x0;
    lVar7 = 0;
    while (lVar7 < sm_dataCount__14MenuFontItalic) {
      iVar6 = (int)lVar7;
      if (*pcVar5 == sm_data__14MenuFontItalic[iVar6 * 8]) {
        puVar4 = sm_data__14MenuFontItalic + iVar6 * 8;
        break;
      }
      lVar7 = (long)(iVar6 + 1);
    }
    if (puVar4 == (u8 *)0x0) {
      *(u8 *)(iVar2 + 0x17) = 0;
    }
    else {
      *(u16 *)(iVar1 + 0x10) =
           *(u16 *)(iVar1 + 0x10) & 0xc000 | (*(u16 *)(puVar4 + 4) & 0x3ff) << 4;
      *(u16 *)(iVar1 + 0x12) =
           *(u16 *)(iVar1 + 0x12) & 0xc000 | (*(u16 *)(puVar4 + 6) & 0x3ff) << 4;
      *(u16 *)(iVar1 + 0x20) =
           *(u16 *)(iVar1 + 0x20) & 0xc000 |
           (*(u16 *)(iVar1 + 0x10) & 0x3fff) + (char)puVar4[1] * 0x10 & 0x3fff;
      *(u16 *)(iVar1 + 0x22) =
           *(u16 *)(iVar1 + 0x22) & 0xc000 |
           (*(u16 *)(iVar1 + 0x12) & 0x3fff) + (char)puVar4[2] * 0x10 & 0x3fff;
      *(u8 *)(iVar2 + 0x17) = 0x80;
    }
    pcVar5 = pcVar5 + 1;
    iVar2 = iVar2 + 0x30;
    iVar1 = iVar1 + 0x30;
  } while( true );
}

// JP: 0x00286190  @60@__dt__14MenuFontItalicFv  size 0x8
// @60@__dt__14MenuFontItalicFv
u32 * _60___dt__14MenuFontItalicFv(MenuFontItalic *this,short param_2)
{
  u32 *puVar1;
  puVar1 = this + -0xf;
  if (puVar1 != (u32 *)0x0) {
    this[-0xd] = __vt__14MenuFontItalic;
    *this = 0x4056d4;
    (**(code **)(this[-0xd] + 0x1c))();
    __dt__8MenuFontFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}
