/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x003a4650  __ct__12dispSaveFileFiiiQ210dataAccess10ACCESSMODEP7primTexPPc  size 0xa4
// dispSaveFile::dispSaveFile(int, int, int, dataAccess::ACCESSMODE, primTex*, char**)
u32 *
__ct__12dispSaveFileFiiiQ210dataAccess10ACCESSMODEP7primTexPPc
          (dispSaveFile *this,u32 param_2,u32 param_3,u32 param_4,
          u32 param_5,u32 param_6,u32 param_7)
{
  this[0xb] = 0;
  this[0xc] = 0;
  *this = param_2;
  this[1] = param_3;
  this[2] = param_4;
  this[3] = param_5;
  this[8] = param_6;
  this[9] = 0;
  this[10] = param_7;
  mSetupDispFile__12dispSaveFileFv(this);
  return this;
}

// JP: 0x003a4700  __dt__12dispSaveFileFv  size 0xf0
// dispSaveFile::~dispSaveFile()
int __dt__12dispSaveFileFv(dispSaveFile *this,short param_2)
{
  int iVar1;
  if (this != 0) {
    if (this->f_2c /*int **/ != 0) {
      iVar1 = this->f_2c /*int **/;
      if (iVar1 != 0) {
        VCALL14(iVar1, 8)(iVar1,1);
      }
      this->f_2c /*u32 **/ = 0;
    }
    if (this->f_30 /*int **/ != 0) {
      __dt__8dispCashFv(this->f_30 /*u32 **/,1);
      this->f_30 /*u32 **/ = 0;
    }
    if (this->f_24 /*int **/ != 0) {
      DelayDeleteRequest__7primWinFv(this->f_24 /*u32 **/);
      this->f_24 /*u32 **/ = 0;
    }
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

// JP: 0x003a47f0  mSetupDispFile__12dispSaveFileFv  size 0xb0c
// dispSaveFile::mSetupDispFile()
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
void mSetupDispFile__12dispSaveFileFv(dispSaveFile *this)
{
  char cVar1;
  u64 uVar2;
  u64 uVar3;
  char *pcVar4;
  long lVar5;
  uint uVar6;
  uint uVar7;
  uint *puVar8;
  uint *puVar9;
  int iVar10;
  uint uVar11;
  uint uVar12;
  char acStack_3d0 [256];
  u32 uStack_2d0;
  u32 uStack_2cc;
  u32 uStack_2c8;
  u32 uStack_2c4;
  u64 uStack_2c0;
  u16 uStack_2b8;
  uint auStack_2b0 [154];
  uint uStack_48;
  char *pcStack_44;
  char *pcStack_40;
  char *pcStack_3c;
  char *pcStack_38;
  int iStack_34;
  int iStack_30;
  u32 uStack_2c;
  u32 uStack_28;
  uint uStack_24;
  int iStack_20;
  int iStack_1c;
  uint uStack_18;
  u8 uStack_11;
  uint *puStack_10;
  puVar8 = &_5355;
  puVar9 = auStack_2b0;
  iVar10 = 0x13;
  puStack_10 = this;
  do {
    uVar2 = *(u64 *)puVar8;
    uVar11 = puVar8[2];
    uVar12 = puVar8[3];
    uVar3 = *(u64 *)(puVar8 + 4);
    uVar6 = puVar8[6];
    uVar7 = puVar8[7];
    puVar8 = puVar8 + 8;
    iVar10 = iVar10 + -1;
    *puVar9 = (uint)uVar2;
    puVar9[1] = (uint)((ulong)uVar2 >> 0x20);
    puVar9[2] = uVar11;
    puVar9[3] = uVar12;
    puVar9[4] = (uint)uVar3;
    puVar9[5] = (uint)((ulong)uVar3 >> 0x20);
    puVar9[6] = uVar6;
    puVar9[7] = uVar7;
    puVar9 = puVar9 + 8;
  } while (0 < iVar10);
  *puVar9 = *puVar8;
  uStack_2d0 = (u32)__5357;
  uStack_2cc = (u32)((ulong)__5357 >> 0x20);
  uStack_2c8 = DAT_003fa518;
  uStack_2c4 = DAT_003fa51c;
  uStack_2c0 = DAT_003fa520;
  uStack_2b8 = DAT_003fa528;
  uStack_11 = (u8)*puStack_10;
  iStack_34 = DAT_00421e90;
  pcVar4 = (char *)(*(int *)(DAT_00421e90 + 0x1c) + *(int *)(*(int *)(DAT_00421e90 + 0x1c) + 0x1c) +
                   (*puStack_10 & 0xff) * 0x60);
  uStack_18 = (uint)*(u16 *)(pcVar4 + 2);
  if (99 < uStack_18) {
    uStack_18 = 99;
  }
  iStack_1c = *(int *)(pcVar4 + 8);
  if (99999999 < iStack_1c) {
    iStack_1c = 99999999;
  }
  iStack_20 = *(int *)(pcVar4 + 4);
  if (35999999 < iStack_20) {
    iStack_20 = 35999999;
  }
  uStack_24 = (uint)(u8)pcVar4[1];
  if (99 < uStack_24) {
    uStack_24 = 99;
  }
  uStack_28 = 0;
  uStack_2c = 0x19;
  puStack_10[4] = 0;
  puStack_10[5] = (puStack_10[1] - 1) * 0x6c + 0x4e;
  puStack_10[6] = 0x80;
  pcStack_44 = pcVar4;
  pcStack_40 = pcVar4;
  pcStack_3c = pcVar4;
  pcStack_38 = pcVar4;
  uStack_48 = __nw__FUi(0x148);
  if (uStack_48 != 0) {
    uStack_48 = __ct__7primWinFv(uStack_48);
  }
  puStack_10[9] = uStack_48;
  uVar6 = puStack_10[9];
  initialize__7primWinFP7primTex(uVar6,puStack_10[8]);
  setItem__7primWinFiii(uVar6,0xc,uStack_2c,0xd);
  setTex__7primWinFiiii(uVar6,10,0,0,0);
  setTex__7primWinFiiii(uVar6,6,1,0,0);
  setTex__7primWinFiiii(uVar6,9,2,0,0);
  setMenuTex__7primWinFP11MenuTextureiii(uVar6,0x421898,0xb,0,0);
  for (iVar10 = 0; iVar10 < 0x11; iVar10 = iVar10 + 1) {
    createTexPoly__7primWinFiiiiii
              (uVar6,iVar10,auStack_2b0[iVar10 * 9],auStack_2b0[iVar10 * 9 + 1],
               auStack_2b0[iVar10 * 9 + 2],0,0);
    iStack_30 = getPP__7primWinFi(uVar6,iVar10);
    VCALL(iStack_30, 0x28 /*SetSize*/)
              ((float)(int)auStack_2b0[iVar10 * 9 + 3],(float)(int)auStack_2b0[iVar10 * 9 + 4]);
    SetUV__11MenuPolygonFUsUsUsUs
              (iStack_30,auStack_2b0[iVar10 * 9 + 5] & 0xffff,auStack_2b0[iVar10 * 9 + 6] & 0xffff,
               auStack_2b0[iVar10 * 9 + 7] & 0xffff,auStack_2b0[iVar10 * 9 + 8] & 0xffff);
  }
  setTextArea__7primWinFiiib(uVar6,10,0x200,0x100,1);
  createText__7primWinFiiiiPciib(uVar6,0,10,0x22,0xf,*(u32 *)puStack_10[10],0x34,2);
  sprintf(acStack_3d0,*(char **)(puStack_10[10] + 4),*puStack_10 + 1);
  createText__7primWinFiiiiPciib(uVar6,1,10,0x4f,0xf,acStack_3d0,0x20,2);
  if (*pcVar4 == -1) {
    iVar10 = getPP__7primWinFi(uVar6,5);
    VCALL(iVar10, 0x24 /*SetPosition*/)(0x41b00000,0x427c0000);
    iVar10 = getPP__7primWinFi(uVar6,6);
    VCALL(iVar10, 0x24 /*SetPosition*/)(0x42bc0000,0x427c0000);
    createText__7primWinFiiiiPciib
              (uVar6,2,10,0x90,0x36,*(u32 *)(puStack_10[10] + (puStack_10[3] + 0xc) * 4),0,0)
    ;
  }
  else {
    sprintf(acStack_3d0,*(char **)(puStack_10[10] + 8),pcVar4 + 0x38);
    createText__7primWinFiiiiPciib(uVar6,2,10,0x82,0xf,acStack_3d0,0,0);
    if (uStack_18 != 0) {
      sprintf(acStack_3d0,*(char **)(puStack_10[10] + 0xc),uStack_18 + 1);
      createText__7primWinFiiiiPciib(uVar6,3,10,0x148,0xf,acStack_3d0,0,0);
    }
    sprintf(acStack_3d0,*(char **)(puStack_10[10] + 0x10),pcVar4 + 0x28);
    createText__7primWinFiiiiPciib(uVar6,4,10,0x76,0x29,acStack_3d0,0,0);
    sprintf(acStack_3d0,*(char **)(puStack_10[10] + 0x1c),pcVar4 + 0x16);
    createText__7primWinFiiiiPciib(uVar6,7,10,0x76,0x43,acStack_3d0,0,0);
    createText__7primWinFiiiiPciib
              (uVar6,8,10,0x22,0x36,*(u32 *)(puStack_10[10] + 0x20),0x1c,0);
    sprintf(acStack_3d0,*(char **)(puStack_10[10] + 0x24),uStack_24);
    createText__7primWinFiiiiPciib(uVar6,9,10,0x4e,0x36,acStack_3d0,0x20,0);
    setTex__7primWinFiiii(uVar6,0xe,3,0,0);
    setTex__7primWinFiiii(uVar6,0xf,4,0x20,0x2e);
    setTex__7primWinFiiii(uVar6,0x10,5,0x20,0x2e);
    setTex__7primWinFiiii(uVar6,0x11,6,0x20,0x2e);
    for (iVar10 = 0; iVar10 < 4; iVar10 = iVar10 + 1) {
      if (*(short *)(pcVar4 + iVar10 * 2 + 0xe) != -1) {
        cVar1 = *(char *)((int)&uStack_2d0 + (uint)*(u16 *)(pcVar4 + iVar10 * 2 + 0xe));
        createTexPoly__7primWinFiiiiii(uVar6,iVar10 * 2 + 0x11,3,iVar10 * 0x1a + 0xd6,0x28,0,0);
        if (cVar1 < '\n') {
          createTexPoly__7primWinFiiiiii
                    (uVar6,iVar10 * 2 + 0x12,4,iVar10 * 0x1a + 0xd6,0x28,0,cVar1);
        }
        else if (cVar1 < '\x0e') {
          createTexPoly__7primWinFiiiiii
                    (uVar6,iVar10 * 2 + 0x12,5,iVar10 * 0x1a + 0xd6,0x28,0,cVar1 + -10);
        }
        else {
          createTexPoly__7primWinFiiiiii
                    (uVar6,iVar10 * 2 + 0x12,6,iVar10 * 0x1a + 0xd6,0x28,0,cVar1 + -0xe);
        }
      }
    }
    lVar5 = __nw__FUi(0x28);
    uVar7 = 0;
    if (lVar5 != 0) {
      uVar7 = __ct__8dispCashFv(lVar5);
    }
    puStack_10[0xc] = uVar7;
    initialize__8dispCashFP7primTexiii(puStack_10[0xc],puStack_10[8],0xc,0xd,iStack_1c);
    setPos__8dispCashFff
              ((float)(int)(puStack_10[4] + 0x14a),(float)(int)(puStack_10[5] + 0x28),
               puStack_10[0xc]);
    lVar5 = __nw__FUi(0x40);
    uVar7 = 0;
    if (lVar5 != 0) {
      uVar7 = __ct__8dispTimeFv(lVar5);
    }
    puStack_10[0xb] = uVar7;
    initialize__8dispTimeFP7primTexiiib(puStack_10[0xb],puStack_10[8],0xc,0xd,iStack_20,0);
    setPos__8dispTimeFff
              ((float)(int)(puStack_10[4] + 0x14a),(float)(int)(puStack_10[5] + 0x40),
               puStack_10[0xb]);
  }
  buildWin__7primWinFiiiiii(uVar6,2,puStack_10[4],puStack_10[5],0,0,0);
  if (puStack_10[1] == 2) {
    fade__7primWinFffi(0,0x3f000000,uVar6,1);
  }
  return;
}

// JP: 0x003a5300  setMove__12dispSaveFileFi  size 0x3d4
// dispSaveFile::setMove(int)
void setMove__12dispSaveFileFi(dispSaveFile *this,int param_2)
{
  u32 uVar1;
  u64 uVar2;
  uVar1 = this->f_24 /*u32 **/;
  if (param_2 == 0x10) {
    this->f_4 /*int **/ = this->f_4 /*int **/ + -1;
    if (this->f_4 /*int **/ == 0) {
      fadeout__7primWinFi(uVar1,0xc);
      if (this->f_30 /*int **/ != 0) {
        uVar2 = getPW__8dispCashFv(this->f_30 /*u32 **/);
        fadeout__7primWinFi(uVar2,0xc);
        uVar2 = getPW__8dispTimeFv(this->f_2c /*u32 **/);
        fadeout__7primWinFi(uVar2,0xc);
      }
    }
    else if (this->f_4 /*int **/ == 1) {
      fade__7primWinFffi(0x3f000000,0x3f800000,uVar1,0xc);
      if (this->f_30 /*int **/ != 0) {
        uVar2 = getPW__8dispCashFv(this->f_30 /*u32 **/);
        fade__7primWinFffi(0x3f000000,0x3f800000,uVar2,0xc);
        uVar2 = getPW__8dispTimeFv(this->f_2c /*u32 **/);
        fade__7primWinFffi(0x3f000000,0x3f800000,uVar2,0xc);
      }
    }
    else {
      fade__7primWinFffi(0,0x3f000000,uVar1,0xc);
      if (this->f_30 /*int **/ != 0) {
        uVar2 = getPW__8dispCashFv(this->f_30 /*u32 **/);
        fade__7primWinFffi(0,0x3f000000,uVar2,0xc);
        uVar2 = getPW__8dispTimeFv(this->f_2c /*u32 **/);
        fade__7primWinFffi(0,0x3f000000,uVar2,0xc);
      }
    }
  }
  else {
    this->f_4 /*int **/ = this->f_4 /*int **/ + 1;
    if (this->f_4 /*int **/ == 1) {
      fadein__7primWinFi(uVar1,0xc);
      if (this->f_30 /*int **/ != 0) {
        uVar2 = getPW__8dispCashFv(this->f_30 /*u32 **/);
        fadein__7primWinFi(uVar2,0xc);
        uVar2 = getPW__8dispTimeFv(this->f_2c /*u32 **/);
        fadein__7primWinFi(uVar2,0xc);
      }
    }
    else if (this->f_4 /*int **/ == 2) {
      fade__7primWinFffi(0x3f800000,0x3f000000,uVar1,0xc);
      if (this->f_30 /*int **/ != 0) {
        uVar2 = getPW__8dispCashFv(this->f_30 /*u32 **/);
        fade__7primWinFffi(0x3f800000,0x3f000000,uVar2,0xc);
        uVar2 = getPW__8dispTimeFv(this->f_2c /*u32 **/);
        fade__7primWinFffi(0x3f800000,0x3f000000,uVar2,0xc);
      }
    }
    else {
      fade__7primWinFffi(0x3f000000,0,uVar1,0xc);
      if (this->f_30 /*int **/ != 0) {
        uVar2 = getPW__8dispCashFv(this->f_30 /*u32 **/);
        fade__7primWinFffi(0x3f000000,0,uVar2,0xc);
        uVar2 = getPW__8dispTimeFv(this->f_2c /*u32 **/);
        fade__7primWinFffi(0x3f000000,0,uVar2,0xc);
      }
    }
  }
  return;
}

// JP: 0x003a56e0  move__12dispSaveFileFiii  size 0x164
// dispSaveFile::move(int, int, int)
void move__12dispSaveFileFiii(dispSaveFile *this,int param_2,int param_3,int param_4)
{
  this->f_10 /*int **/ = this->f_10 /*int **/ + param_2;
  this->f_14 /*int **/ = this->f_14 /*int **/ + param_3;
  this->f_18 /*int **/ = this->f_18 /*int **/ + param_4;
  if ((this->f_24 /*int **/ != 0) &&
     (SetPosition__10MenuWindowFff
                ((float)this->f_10 /*int **/,(float)this->f_14 /*int **/,
                 this->f_24 /*int **/ + 0x3c), this->f_30 /*int **/ != 0)) {
    setPos__8dispCashFff
              ((float)(this->f_10 /*int **/ + 0x14a),(float)(this->f_14 /*int **/ + 0x28),
               this->f_30 /*u32 **/);
    setPos__8dispTimeFff
              ((float)(this->f_10 /*int **/ + 0x14a),(float)(this->f_14 /*int **/ + 0x40),
               this->f_2c /*u32 **/);
  }
  return;
}

// JP: 0x003a5850  setDisp__12dispSaveFileFb  size 0x154
// dispSaveFile::setDisp(bool)
void setDisp__12dispSaveFileFb(dispSaveFile *this,char param_2)
{
  u64 uVar1;
  if (param_2 == '\0') {
    fade__7primWinFffi(0x3f000000,0,this->f_24 /*u32 **/,0xc);
    if (this->f_30 /*int **/ != 0) {
      uVar1 = getPW__8dispCashFv(this->f_30 /*u32 **/);
      fade__7primWinFffi(0x3f000000,0,uVar1,0xc);
      uVar1 = getPW__8dispTimeFv(this->f_2c /*u32 **/);
      fade__7primWinFffi(0x3f000000,0,uVar1,0xc);
    }
  }
  else {
    fade__7primWinFffi(0,0x3f000000,this->f_24 /*u32 **/,0xc);
    if (this->f_30 /*int **/ != 0) {
      uVar1 = getPW__8dispCashFv(this->f_30 /*u32 **/);
      fade__7primWinFffi(0,0x3f000000,uVar1,0xc);
      uVar1 = getPW__8dispTimeFv(this->f_2c /*u32 **/);
      fade__7primWinFffi(0,0x3f000000,uVar1,0xc);
    }
  }
  return;
}
