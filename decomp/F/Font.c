/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x00272c90  CreateFont__4FontFiPUc  size 0x15c
// Font::CreateFont(int, unsigned char*)
void CreateFont__4FontFiPUc(Font *this,int param_2)
{
  int iVar1;
  int *piVar2;
  if (this < 4) {
    iVar1 = this * 0x28;
    piVar2 = (int *)(&fontWork__4Font + iVar1);
    if (*(int *)(&DAT_00421574 + iVar1) == 0) {
      *piVar2 = param_2;
      *(int *)(&DAT_00421554 + iVar1) = *piVar2 + *(int *)(*piVar2 + 0x10);
      *(int *)(&DAT_00421558 + iVar1) = *piVar2 + *(int *)(*piVar2 + 0x18);
      *(int *)(&DAT_0042155c + iVar1) = *piVar2 + *(int *)(*piVar2 + 0x14);
      *(uint *)(&DAT_00421564 + iVar1) =
           *(int *)(&DAT_0042155c + iVar1) +
           (uint)*(u8 *)(*piVar2 + 8) * (uint)*(u16 *)(*piVar2 + 4);
      *(uint *)(&DAT_0042156c + iVar1) =
           *(int *)(&DAT_00421564 + iVar1) +
           (uint)*(u8 *)(*piVar2 + 9) * (uint)*(u16 *)(*piVar2 + 6);
      *(int *)(&DAT_00421560 + iVar1) = *piVar2 + *(int *)(*piVar2 + 0x1c);
      *(uint *)(&DAT_00421568 + iVar1) =
           *(int *)(&DAT_00421560 + iVar1) + (uint)*(u8 *)(*piVar2 + 8) * 2;
      *(uint *)(&DAT_00421570 + iVar1) =
           *(int *)(&DAT_00421568 + iVar1) + (uint)*(u8 *)(*piVar2 + 9) * 2;
      CreateClut__8FontDrawFi(this);
    }
    *(int *)(&DAT_00421574 + iVar1) = *(int *)(&DAT_00421574 + iVar1) + 1;
  }
  return;
}

// JP: 0x00272df0  ClearFont__4FontFi  size 0xc4
// Font::ClearFont(int)
void ClearFont__4FontFi(Font *this)
{
  int iVar1;
  if (((this < 4) && (iVar1 = this * 0x28, *(int *)(&DAT_00421574 + iVar1) != 0)) &&
     (*(int *)(&DAT_00421574 + iVar1) = *(int *)(&DAT_00421574 + iVar1) + -1,
     *(int *)(&DAT_00421574 + iVar1) == 0)) {
    memset(&fontWork__4Font + this * 0x28,0,0x28);
    Release__10ClutRasterFv(&clutRaster__8FontDraw + this * 0x30);
  }
  return;
}

// JP: 0x00272ec0  GetFontCode__4FontFUs  size 0xbc
// Font::GetFontCode(unsigned short)
uint GetFontCode__4FontFUs(Font *this)
{
  uint uVar1;
  uint uVar2;
  uVar1 = (int)(uint)this >> 8;
  if (0xdf < uVar1) {
    uVar1 = uVar1 - 0x40 & 0xffff;
  }
  uVar2 = this & 0xff;
  if (0x7f < uVar2) {
    uVar2 = uVar2 - 1 & 0xffff;
  }
  return ((uVar1 - 0x81 & 0xffff) * 0xbc & 0xffff) + (uVar2 - 0x40 & 0xffff) & 0xffff;
}

// JP: 0x00272f80  __ct__4FontFv  size 0x20
// Font::Font()
u32 * __ct__4FontFv(Font *this)
{
  *this = 0;
  return this;
}

// JP: 0x00272fa0  __ct__4FontFUc  size 0x44
// Font::Font(unsigned char)
u32 * __ct__4FontFUc(Font *this,u8 param_2)
{
  *this = &fontWork__4Font + (uint)param_2 * 0x28;
  return this;
}

// JP: 0x00272ff0  __dt__4FontFv  size 0x54
// Font::~Font()
int __dt__4FontFv(Font *this,short param_2)
{
  if ((this != 0) && (0 < param_2)) {
    __dl__FPv(this);
  }
  return this;
}

// JP: 0x00273050  GetFont__4FontFUsP8FontRect  size 0x418
// Font::GetFont(unsigned short, FontRect*)
int GetFont__4FontFUsP8FontRect(int *param_1,u16 param_2,int this)
{
  u16 uVar1;
  u16 uVar2;
  int iVar3;
  u8 *pbVar4;
  u16 *puVar5;
  pbVar4 = *(u8 **)(*param_1 + 0x10);
  this->f_6 /*u16 **/ = (u16)*(u8 *)(*(int *)*param_1 + 1);
  this->f_a /*u16 **/ = (u16)**(u8 **)*param_1;
  if (param_2 < 0x100) {
    this->f_a /*short **/ = (short)((int)(uint)**(u8 **)*param_1 >> 1);
    if (*(char *)(*(int *)*param_1 + 9) == '\0') {
      this->f_4 /*u16 **/ = this->f_a /*u16 **/;
      iVar3 = *(int *)(*param_1 + 0x14);
    }
    else {
      pbVar4 = (u8 *)(*(int *)(*param_1 + 0x18) + (uint)(u16)(param_2 - 0x20) * 2);
      this->f_8 /*u16 **/ = (u16)*pbVar4;
      this->f_4 /*u16 **/ = (u16)pbVar4[1];
      iVar3 = *(int *)(*param_1 + 0x14) +
              (uint)(u16)(param_2 - 0x20) * (uint)*(u16 *)(*(int *)*param_1 + 6);
    }
  }
  else {
    iVar3 = 0;
    puVar5 = *(u16 **)(*param_1 + 8);
    uVar1 = GetFontCode__4FontFUs(param_2);
    for (uVar2 = 0; uVar2 < *(u16 *)(*(int *)*param_1 + 0xc); uVar2 = uVar2 + 1) {
      if ((*puVar5 <= uVar1) && ((uint)uVar1 < (uint)*puVar5 + (uint)puVar5[1])) {
        if (uVar1 < 0x4c4) {
          pbVar4 = (u8 *)(*(int *)(*param_1 + 0x20) + (iVar3 + ((uint)uVar1 - (uint)*puVar5)) * 2)
          ;
          this->f_8 /*u16 **/ = (u16)*pbVar4;
          this->f_4 /*u16 **/ = (u16)pbVar4[1];
        }
        else {
          this->f_8 /*u16 **/ = 0;
          this->f_4 /*u16 **/ = (u16)**(u8 **)*param_1;
        }
        return *(int *)(*param_1 + 0x1c) +
               (uint)*(u16 *)(*(int *)*param_1 + 4) * (iVar3 + ((uint)uVar1 - (uint)*puVar5));
      }
      iVar3 = iVar3 + (uint)puVar5[1];
      puVar5 = puVar5 + 2;
    }
    this->f_4 /*u16 **/ = (u16)pbVar4[1];
    this->f_8 /*u16 **/ = (u16)*pbVar4;
    if ((uVar1 < 8000) || (0x1f80 < uVar1)) {
      iVar3 = *(int *)(*param_1 + 0xc);
    }
    else {
      uVar1 = (uVar1 & 0xff) - 0x40;
      if (uVar1 < *(u8 *)(*(int *)*param_1 + 8)) {
        iVar3 = *(int *)(*param_1 + 0xc) + (uint)uVar1 * (uint)*(u16 *)(*(int *)*param_1 + 4);
      }
      else {
        iVar3 = *(int *)(*param_1 + 0xc);
      }
    }
  }
  return iVar3;
}

// JP: 0x00273470  SetFont__4FontFP6CImagePUcP8FontRectiUc  size 0x944
// Font::SetFont(CImage*, unsigned char*, FontRect*, int, unsigned char)
u32
SetFont__4FontFP6CImagePUcP8FontRectiUc
          (u64 param_1,char *this,u8 *param_3,u16 *param_4,int param_5,char param_6)
{
  char cVar1;
  int iVar2;
  char *pcVar3;
  uint uVar4;
  uint uVar5;
  u8 *pbVar6;
  uint uVar7;
  char *pcVar8;
  u8 *pbVar9;
  ulong uVar10;
  u8 *pbStack_40;
  uVar4 = (int)(short)param_4[2] >> 2;
  uVar5 = (int)(short)param_4[2] & 3;
  cVar1 = (char)param_5;
  pbStack_40 = param_3;
  if (Font *this == '\b') {
    if (param_6 == '\0') {
      iVar2 = (int)(short)param_4[4] +
              (int)(short)*param_4 + (int)(short)param_4[1] * (uint)this->f_4 /*u16 **/;
    }
    else {
      iVar2 = (int)(short)*param_4 + (int)(short)param_4[1] * (uint)this->f_4 /*u16 **/;
    }
    pcVar8 = (char *)(this->f_8 /*int **/ + iVar2);
    for (uVar10 = 0; (long)uVar10 < (long)(short)param_4[3];
        uVar10 = (long)((int)uVar10 + 1) & 0xffff) {
      pcVar3 = pcVar8;
      for (uVar7 = 0; uVar7 < (uVar4 & 0xffff); uVar7 = uVar7 + 1 & 0xffff) {
        *pcVar3 = (*pbStack_40 & 3) + cVar1;
        pcVar3[1] = ((u8)((int)(uint)*pbStack_40 >> 2) & 3) + cVar1;
        pcVar3[2] = ((u8)((int)(uint)*pbStack_40 >> 4) & 3) + cVar1;
        pcVar3[3] = (char)((int)(uint)*pbStack_40 >> 6) + cVar1;
        pcVar3 = pcVar3 + 4;
        pbStack_40 = pbStack_40 + 1;
      }
      for (uVar7 = 0; uVar7 < uVar5; uVar7 = uVar7 + 1 & 0xffff) {
        pcVar3[uVar7] = cVar1 + ((u8)((int)(uint)*pbStack_40 >> ((uVar7 & 0xf) << 1)) & 3);
      }
      if (uVar7 != 0) {
        pbStack_40 = pbStack_40 + 1;
      }
      pcVar8 = pcVar8 + this->f_4 /*u16 **/;
    }
  }
  else {
    if (param_6 == '\0') {
      iVar2 = ((int)(short)param_4[4] >> 1) +
              ((int)(short)*param_4 >> 1) +
              (int)(short)param_4[1] * ((int)(uint)this->f_4 /*u16 **/ >> 1);
    }
    else {
      iVar2 = ((int)(short)*param_4 >> 1) +
              (int)(short)param_4[1] * ((int)(uint)this->f_4 /*u16 **/ >> 1);
    }
    pbVar9 = (u8 *)(this->f_8 /*int **/ + iVar2);
    for (uVar10 = 0; (long)uVar10 < (long)(short)param_4[3];
        uVar10 = (long)((int)uVar10 + 1) & 0xffff) {
      if ((*param_4 & 1) == 0) {
        pbVar6 = pbVar9;
        for (uVar7 = 0; uVar7 < (uVar4 & 0xffff); uVar7 = uVar7 + 1 & 0xffff) {
          *pbVar6 = (*pbStack_40 & 3) + cVar1 |
                    (u8)((((int)(uint)*pbStack_40 >> 2 & 3U) + param_5 & 0xff) << 4);
          pbVar6[1] = ((u8)((int)(uint)*pbStack_40 >> 4) & 3) + cVar1 |
                      (u8)((((int)(uint)*pbStack_40 >> 6) + param_5 & 0xffU) << 4);
          pbVar6 = pbVar6 + 2;
          pbStack_40 = pbStack_40 + 1;
        }
        if (uVar5 != 2) {
          if (uVar5 != 3) {
            if (uVar5 == 1) {
              *pbVar6 = (*pbVar6 & 0xf0) + (*pbStack_40 & 3) + cVar1;
              pbStack_40 = pbStack_40 + 1;
            }
            goto LAB_00273d20;
          }
          pbVar6[1] = (pbVar6[1] & 0xf0) + ((u8)((int)(uint)*pbStack_40 >> 4) & 3) + cVar1;
        }
        *pbVar6 = (*pbStack_40 & 3) + cVar1 |
                  (u8)((((int)(uint)*pbStack_40 >> 2 & 3U) + param_5 & 0xff) << 4);
        pbStack_40 = pbStack_40 + 1;
      }
      else {
        pbVar6 = pbVar9;
        for (uVar7 = 0; uVar7 < (uVar4 & 0xffff); uVar7 = uVar7 + 1 & 0xffff) {
          *pbVar6 = (*pbVar6 & 0xf) + ((*pbStack_40 & 3) + cVar1) * '\x10';
          pbVar6[1] = ((u8)((int)(uint)*pbStack_40 >> 2) & 3) + cVar1 |
                      (u8)((((int)(uint)*pbStack_40 >> 4 & 3U) + param_5 & 0xff) << 4);
          pbVar6[2] = (pbVar6[2] & 0xf0) + (char)((int)(uint)*pbStack_40 >> 6) + cVar1;
          pbVar6 = pbVar6 + 2;
          pbStack_40 = pbStack_40 + 1;
        }
        if (uVar5 == 3) {
          *pbVar6 = (*pbVar6 & 0xf) + ((*pbStack_40 & 3) + cVar1) * '\x10';
          pbVar6[1] = ((u8)((int)(uint)*pbStack_40 >> 2) & 3) + cVar1 |
                      (u8)((((int)(uint)*pbStack_40 >> 4 & 3U) + param_5 & 0xff) << 4);
          pbStack_40 = pbStack_40 + 1;
        }
        else if (uVar5 == 2) {
          *pbVar6 = (*pbVar6 & 0xf) + ((*pbStack_40 & 3) + cVar1) * '\x10';
          pbVar6[1] = (pbVar6[1] & 0xf0) + ((u8)((int)(uint)*pbStack_40 >> 2) & 3) + cVar1;
          pbStack_40 = pbStack_40 + 1;
        }
        else if (uVar5 == 1) {
          *pbVar6 = (*pbVar6 & 0xf) + ((*pbStack_40 & 3) + cVar1) * '\x10';
          pbStack_40 = pbStack_40 + 1;
        }
      }
LAB_00273d20:
      pbVar9 = pbVar9 + ((int)(uint)this->f_4 /*u16 **/ >> 1);
    }
  }
  if (param_6 == '\0') {
    param_4[2] = param_4[5];
  }
  return 1;
}
