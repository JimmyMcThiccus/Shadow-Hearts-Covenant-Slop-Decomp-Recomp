/* Section F (menu toolkit / save / title) -- cleaned Ghidra output from SLPM_602.19 (JP demo).
 * Names recovered from the symbol table; `this->field` names come from tools/F/fields.py
 * (f_XX = offset not yet identified). VCALL(obj, slot) is the C++ virtual call through obj->vptr
 * (vtable pointer at +8 for MenuObj-derived objects, +0x14 for CPolObj-derived objects).
 * Types: u8/u16/u32/u64 = unsigned, undefined N reduced to these. This is analysis output, not
 * compilable source; see port/crates/sh2_menu for the Rust translation. */

// JP: 0x003ac270  __ct__13GameOverSceneFv  size 0x44
// GameOverScene::GameOverScene()
int __ct__13GameOverSceneFv(GameOverScene *this)
{
  __ct__9MenuSceneFv(this);
  this->vptr = __vt__13GameOverScene;
  this->data_access = 0;
  return this;
}

// JP: 0x003ac2c0  __dt__13GameOverSceneFv  size 0x74
// GameOverScene::~GameOverScene()
int __dt__13GameOverSceneFv(GameOverScene *this,short param_2)
{
  if (this != 0) {
    this->vptr = __vt__13GameOverScene;
    __dt__9MenuSceneFv(this,0);
    if (0 < param_2) {
      __dl__FPv(this);
    }
  }
  return this;
}

// JP: 0x003ac340  GetReady__13GameOverSceneFv  size 0x278
// GameOverScene::GetReady()
u32 GetReady__13GameOverSceneFv(GameOverScene *this)
{
  undefined *puVar1;
  undefined *puVar2;
  short *psVar3;
  int iVar4;
  long lVar5;
  u32 *puVar6;
  short sVar7;
  short sVar8;
  short asStack_100c0 [32760];
  short asStack_c0 [16];
  char acStack_a0 [136];
  short *psStack_18;
  u32 *puStack_14;
  int iStack_10;
  iVar4 = *(int *)(sm_pSubstance__15SaveMenuSection + 0xc);
  psVar3 = (short *)(iVar4 + 0x29c);
  psStack_18 = psVar3;
  iStack_10 = this;
  lVar5 = __nw__FUi(400);
  puVar6 = (u32 *)0x0;
  if (lVar5 != 0) {
    puVar6 = (u32 *)lVar5;
    *puVar6 = 0;
    puVar6[1] = 0;
    puVar6[2] = __vt__17DelayDeleteObject;
    puVar6[2] = __vt__15GameOverRealize;
    __ct__10MenuWindowFv(puVar6 + 3);
    __ct__11MenuTextureFv(puVar6 + 0x30);
    __ct__11SendOnLocalFv(puVar6 + 0x40);
    __ct__10MenuSpriteFv(puVar6 + 0x4c);
    puStack_14 = puVar6;
  }
  *(u32 **)(iStack_10 + 100) = puVar6;
  sVar7 = *psVar3;
  if (sVar7 < 0) {
    sVar8 = 0;
    for (sVar7 = 0; sVar7 < 0x10; sVar7 = sVar7 + 1) {
      if (((uint)*(u16 *)(iVar4 + 0x29e) & 1 << ((int)sVar7 & 0x1fU)) != 0) {
        asStack_c0[sVar8] = sVar7;
        sVar8 = sVar8 + 1;
      }
    }
    iVar4 = rand();
    if (sVar8 == 0) {
      trap(7);
    }
    sVar7 = asStack_c0[iVar4 % (int)sVar8];
  }
  sprintf(acStack_a0,*(char **)(*(int *)(iStack_10 + 0x24) + 0x10),sVar7);
  OrderFile__11MenuTextureFPCc6GS_PSMUii(*(int *)(iStack_10 + 100) + 0xc0,acStack_a0,0x30,0,0);
  puVar2 = PTR_ReadData__13GameOverSceneFv_003fa5b8;
  puVar1 = PTR_003fa5b4;
  *(u32 *)(iStack_10 + 0x58) = _7384;
  *(undefined **)(iStack_10 + 0x5c) = puVar1;
  *(undefined **)(iStack_10 + 0x60) = puVar2;
  (**(code **)(*(int *)(*(int *)(iStack_10 + 0x10) + 0x14) + 0x24))
            (*(int *)(iStack_10 + 0x10),*(u16 *)(iStack_10 + 0x1c));
  return 1;
}

// JP: 0x003ac5c0  Run__13GameOverSceneFv  size 0x5c
// GameOverScene::Run()
u64 Run__13GameOverSceneFv(GameOverScene *this)
{
  long lVar1;
  do {
    lVar1 = __ptmf_test(this + 0x58);
    if (lVar1 == 0) {
      return 0;
    }
    lVar1 = __ptmf_scall(this);
  } while (lVar1 != 0);
  return 0;
}

// JP: 0x003ac620  ShiftTitle__13GameOverSceneFv  size 0x20
// GameOverScene::ShiftTitle()
void ShiftTitle__13GameOverSceneFv(void)
{
  opening__Fv();
  return;
}

// JP: 0x003ac640  ReadData__13GameOverSceneFv  size 0x174
// GameOverScene::ReadData()
u64 ReadData__13GameOverSceneFv(GameOverScene *this)
{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined *puVar4;
  undefined *puVar5;
  int iVar6;
  int iVar7;
  iVar1 = this->realize;
  if ((*(u8 *)(iVar1 + 0xfa) & 1) != 0) {
    iVar2 = this->realize;
    iVar6 = iVar2 + 0xc;
    iVar3 = this->realize;
    iVar7 = this->realize + 0x100;
    SetFFMode__3GsxFibi(0,1,1);
    Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi
              (iVar7,iVar1 + 0xd8,*(u32 *)(iVar1 + 0xd4),1,0xffffffffffffffff);
    SetData__9MenuSceneFUsP10MenuSprite(this,0,iVar3 + 0x130);
    *(int *)(iVar3 + 0x18c) = iVar7;
    *(u8 *)(iVar3 + 0x142) = *(u8 *)(iVar3 + 0x142) & 0xdf;
    AddPlace__10MenuWindowFP9MenuPlace(iVar6,iVar3 + 0x130);
    SetData__9MenuSceneFUsP10MenuWindow(this,0,iVar6);
    *(u16 *)(iVar2 + 0xba) = 0;
    AddOT__7MenuObjFv(iVar6);
    Open__10MenuWindowFUci
              (iVar6,*(u8 *)(iVar2 + 0xbc) & 7,*(u32 *)(*(int *)(iVar2 + 0x40) + 0x10));
    puVar5 = PTR_Realize__13GameOverSceneFv_003fa5c8;
    puVar4 = PTR_003fa5c4;
    this->state_fn = _7449;
    this->f_5c /*undefined **/ = puVar4;
    this->f_60 /*undefined **/ = puVar5;
  }
  return 0;
}

// JP: 0x003ac7c0  Realize__13GameOverSceneFv  size 0x168
// GameOverScene::Realize()
u64 Realize__13GameOverSceneFv(GameOverScene *this)
{
  int iVar1;
  bool bVar2;
  undefined *puVar3;
  undefined *puVar4;
  short sVar5;
  iVar1 = this->realize;
  sVar5 = *(short *)(iVar1 + 0xba) + (short)sm_iPassTime__7MenuObj;
  *(short *)(iVar1 + 0xba) = sVar5;
  if ((*(char *)(iVar1 + 0xb4) == '\x01') || (*(char *)(iVar1 + 0xb4) == '\0')) {
    bVar2 = true;
  }
  else {
    bVar2 = false;
  }
  if (((bVar2) && ((this->menu->keys & 0x2000) != 0)) || (5000 < sVar5))
  {
    Close__10MenuWindowFUci
              (iVar1 + 0xc,((ulong)*(u8 *)(iVar1 + 0xbc) & 0x3f) >> 3,
               *(u32 *)(*(int *)(iVar1 + 0x40) + 0x14));
    puVar4 = PTR_ExitRealize__13GameOverSceneFv_003fa5d8;
    puVar3 = PTR_003fa5d4;
    this->state_fn = _7470;
    this->f_5c /*undefined **/ = puVar3;
    this->f_60 /*undefined **/ = puVar4;
  }
  return 0;
}

// JP: 0x003ac930  ExitRealize__13GameOverSceneFv  size 0x3d0
// GameOverScene::ExitRealize()
u64 ExitRealize__13GameOverSceneFv(GameOverScene *this)
{
  int iVar1;
  int iVar2;
  bool bVar3;
  undefined *puVar4;
  undefined *puVar5;
  u16 uVar6;
  long lVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  u32 *puVar11;
  int iVar12;
  iVar1 = this->realize;
  if ((*(char *)(iVar1 + 0xb4) == '\x01') || (*(char *)(iVar1 + 0xb4) == '\0')) {
    bVar3 = true;
  }
  else {
    bVar3 = false;
  }
  if (bVar3) {
    ReleaseOT__7MenuObjFv(iVar1 + 0xc);
    VCALL(this->realize, 0xc /*DelayDelete*/)();
    if (*(char *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x308) == '\0') {
      ShiftTitle__13GameOverSceneFv(this);
      (**(code **)(this->menu->vptr_dd + 0xc))();
    }
    else {
      lVar7 = __nw__FUi(0x37c);
      puVar11 = (u32 *)0x0;
      if (lVar7 != 0) {
        puVar11 = (u32 *)lVar7;
        *puVar11 = 0;
        puVar11[1] = 0;
        puVar11[2] = __vt__17DelayDeleteObject;
        puVar11[2] = __vt__14GameOverSelect;
        __ct__10MenuWindowFv(puVar11 + 3);
        __ct__6CursorFv(puVar11 + 0x30);
        __ct__8FontDrawFv(puVar11 + 0x6f);
        __construct_array(puVar11 + 0x7f,0x27bfd0,0x27c030,0x80,3);
      }
      this->select = puVar11;
      iVar1 = this->select;
      iVar8 = iVar1 + 0xc;
      iVar12 = this->select + 0x1bc;
      iVar9 = this->select + 0x1fc;
      iVar2 = this->select;
      iVar10 = iVar2 + 0xc0;
      SetData__9MenuSceneFUsP8FontDraw(this,0,iVar12);
      AddPriority__12MenuObjTableFP7MenuObj(iVar1 + 0x24,iVar12);
      for (uVar6 = 0; uVar6 < 3; uVar6 = uVar6 + 1) {
        SetData__9MenuSceneFUsP8MenuText(this,uVar6,iVar9);
        SetMessage__8MenuTextFPcUiUcUc
                  (iVar9,*(u32 *)
                          ((uint)*(u16 *)(iVar9 + 0x22) * 0xc + this->tab_text + 0x10),
                   *(u8 *)(iVar9 + 0x58) & 7,0,1);
        OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_
                  (iVar12,iVar9,((ulong)*(u8 *)(iVar9 + 0x58) & 0xf) >> 3,0);
        AddPlace__10MenuWindowFP9MenuPlace(iVar8,iVar9);
        iVar9 = iVar9 + 0x80;
      }
      SetData__9MenuSceneFUsP10MenuWindow(this,1,iVar8);
      AddOT__7MenuObjFv(iVar8);
      SetData__9MenuSceneFUsP6Cursor(this,0,iVar10);
      *(u8 *)(iVar2 + 0x1bb) = *(u8 *)(iVar2 + 0x1bb) & 0xef | 0x10;
      Select__6CursorFP9MenuPlace(iVar10,this->select + 0x27c);
      SetCSA__8FontItemFUc(*(u32 *)(iVar2 + 0x1ac),1);
      QuickMove__6CursorFv(iVar10);
      AddOT__7MenuObjFv(iVar10);
      Open__10MenuWindowFUci
                (iVar8,*(u8 *)(iVar1 + 0xbc) & 7,*(u32 *)(*(int *)(iVar1 + 0x40) + 0x10));
      puVar5 = PTR_SelectLoad__13GameOverSceneFv_003fa5e8;
      puVar4 = PTR_003fa5e4;
      this->state_fn = _7507;
      this->f_5c /*undefined **/ = puVar4;
      this->f_60 /*undefined **/ = puVar5;
    }
  }
  return 0;
}

// JP: 0x003acd00  SelectLoad__13GameOverSceneFv  size 0x260
// GameOverScene::SelectLoad()
u64 SelectLoad__13GameOverSceneFv(GameOverScene *this)
{
  u16 uVar1;
  int iVar2;
  int iVar3;
  bool bVar4;
  undefined *puVar5;
  undefined *puVar6;
  u32 uVar7;
  long lVar8;
  iVar2 = this->select;
  iVar3 = *(int *)(iVar2 + 0x1ac);
  uVar1 = this->menu->keys;
  if ((*(char *)(this->select + 0xb4) == '\x01') ||
     (*(char *)(this->select + 0xb4) == '\0')) {
    bVar4 = true;
  }
  else {
    bVar4 = false;
  }
  if (bVar4) {
    if ((uVar1 & 0x2000) == 0) {
      if ((uVar1 & 0x10) == 0) {
        if ((uVar1 & 0x40) != 0) {
          MoveCursor__6CursorFi(iVar2 + 0xc0,2);
        }
      }
      else {
        MoveCursor__6CursorFi(iVar2 + 0xc0,1);
      }
      if (iVar3 != *(int *)(iVar2 + 0x1ac)) {
        SetCSA__8FontItemFUc(iVar3,0);
        SetCSA__8FontItemFUc(*(u32 *)(iVar2 + 0x1ac),1);
      }
    }
    else {
      if (*(short *)(iVar3 + 0x16) == 0) {
        lVar8 = __nw__FUi(0x184);
        uVar7 = 0;
        if (lVar8 != 0) {
          uVar7 = __ct__10dataAccessFv(lVar8);
        }
        this->data_access = uVar7;
        initialize__10dataAccessFQ210dataAccess10ACCESSMODEPFiPv_vPv
                  (this->data_access,1,0x3abe10,this->menu);
      }
      iVar2 = this->select;
      Close__10MenuWindowFUci
                (iVar2 + 0xc,((ulong)*(u8 *)(iVar2 + 0xbc) & 0x3f) >> 3,
                 *(u32 *)(*(int *)(iVar2 + 0x40) + 0x14));
      puVar6 = PTR_ExitSelectLoad__13GameOverSceneFv_003fa5f8;
      puVar5 = PTR_003fa5f4;
      this->state_fn = _7571;
      this->f_5c /*undefined **/ = puVar5;
      this->f_60 /*undefined **/ = puVar6;
    }
  }
  return 0;
}

// JP: 0x003acf60  ExitSelectLoad__13GameOverSceneFv  size 0x188
// GameOverScene::ExitSelectLoad()
u64 ExitSelectLoad__13GameOverSceneFv(GameOverScene *this)
{
  int iVar1;
  int iVar2;
  bool bVar3;
  u32 uVar4;
  u32 uVar5;
  iVar1 = this->select;
  if ((*(char *)(iVar1 + 0xb4) == '\x01') || (*(char *)(iVar1 + 0xb4) == '\0')) {
    bVar3 = true;
  }
  else {
    bVar3 = false;
  }
  if (bVar3) {
    iVar2 = this->select;
    if (this->data_access == 0) {
      ShiftTitle__13GameOverSceneFv(this);
      (**(code **)(this->menu->vptr_dd + 0xc))();
    }
    else {
      Leave__6CursorFv(iVar2 + 0xc0);
      start__10dataAccessFQ210dataAccess9STARTMODEii
                (this->data_access,0,(int)**(float **)(iVar2 + 0x198),
                 (int)*(float *)(*(int *)(iVar2 + 0x198) + 4));
      uVar5 = DAT_004236d0;
      uVar4 = DAT_004236cc;
      this->state_fn = __ptmf_null;
      this->f_5c /*u32 **/ = uVar4;
      this->f_60 /*u32 **/ = uVar5;
    }
    ReleaseOT__7MenuObjFv(iVar1 + 0xc);
    ReleaseOT__7MenuObjFv(iVar2 + 0xc0);
    VCALL(this->select, 0xc /*DelayDelete*/)();
  }
  return 0;
}

// JP: 0x003ad2b0  Release__13GameOverSceneFv  size 0x10
// GameOverScene::Release()
void Release__13GameOverSceneFv(void)
{
  return;
}
