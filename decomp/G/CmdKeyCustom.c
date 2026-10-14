/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdKeyCustom   functions: 11
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdKeyCustom.md).
 */

/* JP: 0x00478840  CmdKeyCustom::CmdKeyCustom()   [__ct__12CmdKeyCustomFv]  size=0xec */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __ct__12CmdKeyCustomFv(int param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  __ct__9MenuSceneFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__12CmdKeyCustom;
  uVar2 = uRam004236d0;
  uVar1 = uRam004236cc;
  *(undefined4 *)(param_1 + 0x58) = ___ptmf_null;
  *(undefined4 *)(param_1 + 0x5c) = uVar1;
  *(undefined4 *)(param_1 + 0x60) = uVar2;
  __ct__6CursorFv(param_1 + 0x68);
  __ct__11MenuTextureFv(param_1 + 0x168);
  __ct__11MenuTextureFv(param_1 + 0x1a8);
  __ct__11MenuTextureFv(param_1 + 0x1e8);
  __ct__15CmdKeyCustomPadFv(param_1 + 0x228);
  __ct__16CmdKeyCustomMenuFv(param_1 + 0x111c);
  __construct_array(param_1 + 0x1800,0x4789b0,0x478930,0x100,4);
  return param_1;
}

/* JP: 0x004789f0  CmdKeyCustom::~CmdKeyCustom()   [__dt__12CmdKeyCustomFv]  size=0x10c */
int __dt__12CmdKeyCustomFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__12CmdKeyCustom;
    __destroy_arr(param_1 + 0x1800,0x478930,0x100,4);
    __dt__16CmdKeyCustomMenuFv(param_1 + 0x111c,0xffffffffffffffff);
    __dt__15CmdKeyCustomPadFv(param_1 + 0x228,0xffffffffffffffff);
    __dt__11MenuTextureFv(param_1 + 0x1e8,0xffffffffffffffff);
    __dt__11MenuTextureFv(param_1 + 0x1a8,0xffffffffffffffff);
    __dt__11MenuTextureFv(param_1 + 0x168,0xffffffffffffffff);
    __dt__6CursorFv(param_1 + 0x68,0xffffffffffffffff);
    __dt__9MenuSceneFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x00478b00  CmdKeyCustom::GetReady()   [GetReady__12CmdKeyCustomFv]  size=0x30c */
undefined4 GetReady__12CmdKeyCustomFv(int param_1)

{
  undefined4 uVar1;
  undefined *puVar2;
  undefined4 *puVar3;
  int iVar4;
  int iVar5;
  
  iVar4 = *(int *)(param_1 + 0x10);
  *(int *)(param_1 + 0x18) = iVar4 + 0x3a0;
  *(undefined4 *)(param_1 + 100) = sm_pSound__7MenuObj;
  *(int *)(param_1 + 0x1c08) = iVar4 + 0x780;
  *(int *)(param_1 + 0x1c0c) = iVar4 + 0x4e0;
  Create__11MenuTextureFPUc6GS_PSMUii(param_1 + 0x1a8,*(undefined4 *)(*(int *)(param_1 + 0x54) + 0x1c),0x30,0,0);
  Create__11MenuTextureFPUc6GS_PSMUii(param_1 + 0x1e8,*(undefined4 *)(*(int *)(param_1 + 0x54) + 0x28),0x30,0,0);
  Create__11MenuTextureFPUc6GS_PSMUii(param_1 + 0x168,*(undefined4 *)(*(int *)(param_1 + 0x54) + 0x34),0x30,0,0);
  CreateScene__15CmdKeyCustomPadFP12CmdKeyCustom(param_1 + 0x228,param_1);
  CreateScene__16CmdKeyCustomMenuFP12CmdKeyCustom(param_1 + 0x111c,param_1);
  iVar4 = param_1 + 0x1800;
  puVar3 = (undefined4 *)(*(int *)(param_1 + 0x28) + 0x10);
  for (iVar5 = 0; iVar5 < 4; iVar5 = iVar5 + 1) {
    SetData__9MenuSceneFUsP8MenuText(param_1,0,iVar4);
    SetMessage__8MenuTextFPcUiUcUc(iVar4,*puVar3,*(byte *)(iVar4 + 0x58) & 7,0,1);
    OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(param_1 + 0x39c,iVar4,((ulong)*(byte *)(iVar4 + 0x58) & 0xf) >> 3,0);
    SetData__9MenuSceneFUsP8MenuText(param_1,1,iVar4 + 0x80);
    SetMessage__8MenuTextFPcUiUcUc(iVar4 + 0x80,*puVar3,*(byte *)(iVar4 + 0xd8) & 7,0,1);
    OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(param_1 + 0x11d0,iVar4 + 0x80,((ulong)*(byte *)(iVar4 + 0xd8) & 0xf) >> 3,0);
    *(short *)(iVar4 + 0xa2) = (short)iVar5;
    iVar4 = iVar4 + 0x100;
    puVar3 = puVar3 + 3;
  }
  SetAssign__12CmdKeyCustomFi(param_1,0);
  SetButton__12CmdKeyCustomFi(param_1,1);
  SetData__9MenuSceneFUsP6Cursor(param_1,0,param_1 + 0x68);
  puVar2 = PTR_Enter__12CmdKeyCustomFv_0050d8f8;
  uVar1 = DAT_0050d8f4;
  *(undefined4 *)(param_1 + 0x58) = _4942;
  *(undefined4 *)(param_1 + 0x5c) = uVar1;
  *(undefined **)(param_1 + 0x60) = puVar2;
  return 1;
}

/* JP: 0x00478e10  CmdKeyCustom::Run()   [Run__12CmdKeyCustomFv]  size=0x5c */
undefined8 Run__12CmdKeyCustomFv(int param_1)

{
  long lVar1;
  
  do {
    lVar1 = __ptmf_test(param_1 + 0x58);
    if (lVar1 == 0) {
      return 0;
    }
    lVar1 = __ptmf_scall(param_1);
  } while (lVar1 != 0);
  return 0;
}

/* JP: 0x00478e70  CmdKeyCustom::SetButton(int)   [SetButton__12CmdKeyCustomFi]  size=0x170 */
void SetButton__12CmdKeyCustomFi(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  ushort *puVar3;
  
  puVar3 = (ushort *)(param_1 + 0x1c00);
  for (iVar2 = 0; iVar2 < 4; iVar2 = iVar2 + 1) {
    iVar1 = param_1 + (uint)*puVar3 * 0x100;
    if (param_2 == 0) {
      RemovePlace__9MenuGroupFP9MenuPlace(iVar2 * 0x230 + param_1 + 0x3dc,iVar1 + 0x1800);
      RemovePlace__9MenuGroupFP9MenuPlace(iVar2 * 0x130 + param_1 + 0x1240,iVar1 + 0x1880);
    }
    else {
      AddPlace__9MenuGroupFP9MenuPlace(iVar2 * 0x230 + param_1 + 0x3dc,iVar1 + 0x1800);
      AddPlace__9MenuGroupFP9MenuPlace(iVar2 * 0x130 + param_1 + 0x1240,iVar1 + 0x1880);
    }
    puVar3 = puVar3 + 1;
  }
  return;
}

/* JP: 0x00478fe0  CmdKeyCustom::SetAssign(int)   [SetAssign__12CmdKeyCustomFi]  size=0x11c */
void SetAssign__12CmdKeyCustomFi(int param_1,int param_2)

{
  int iVar1;
  ushort *puVar2;
  undefined8 uStack_28;
  int iStack_20;
  int iStack_10;
  
  iStack_20 = param_1;
  iStack_10 = param_2;
  uStack_28 = @5026;
  puVar2 = (ushort *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x26c);
  iVar1 = 0;
  if (param_2 == 0) {
    for (; iVar1 < 4; iVar1 = iVar1 + 1) {
      *(short *)(param_1 + *(short *)((int)&uStack_28 + (*puVar2 - 0xc) * 2) * 2 + 0x1c00) =
           (short)iVar1;
      puVar2 = puVar2 + 1;
    }
  }
  else {
    for (; iVar1 < 4; iVar1 = iVar1 + 1) {
      puVar2[*(ushort *)(param_1 + *(short *)((int)&uStack_28 + iVar1 * 2) * 2 + 0x1c00)] =
           (short)iVar1 + 0xc;
    }
    UpdatePad__15SaveMenuSectionFv();
  }
  return;
}

/* JP: 0x00479100  CmdKeyCustom::Select(MenuPlace*, MenuPlace*, short)   [Select__12CmdKeyCustomFP9MenuPlaceP9MenuPlaces]  size=0x2ec */
void Select__12CmdKeyCustomFP9MenuPlaceP9MenuPlaces
               (int param_1,int param_2,int param_3,short param_4)

{
  short sVar1;
  int iVar2;
  undefined8 uStack_60;
  undefined4 uStack_58;
  int iStack_50;
  short sStack_4a;
  short sStack_48;
  short sStack_46;
  short sStack_44;
  ushort uStack_42;
  int iStack_40;
  int iStack_30;
  int iStack_20;
  short sStack_10;
  
  iStack_40 = param_1;
  iStack_30 = param_2;
  iStack_20 = param_3;
  sStack_10 = param_4;
  if (param_3 != 0) {
    sStack_44 = *(short *)(param_3 + 0x1e);
    if (sStack_44 < 4) {
      SetLineColor__15CmdKeyCustomPadFii(param_1 + 0x228,sStack_44,0);
      iVar2 = FindPlace__9MenuGroupFs(iStack_20,100);
      sStack_48 = *(short *)(iVar2 + 0x22);
      iVar2 = iStack_40 + sStack_48 * 0x100;
      sStack_46 = sStack_48;
      SetCSA__8FontItemFUc(iVar2 + 0x1800,2);
      SetCSA__8FontItemFUc(iVar2 + 0x1880,0);
    }
    else {
      iStack_50 = (short)(sStack_44 + -4) * 0x80 + param_1 + 0x1700;
      SetCSA__8FontItemFUc(iStack_50,0);
    }
  }
  if (iStack_30 != 0) {
    sVar1 = *(short *)(iStack_30 + 0x1e);
    sStack_4a = sVar1;
    if (sVar1 < 4) {
      SetLineColor__15CmdKeyCustomPadFii(iStack_40 + 0x228,sVar1,1);
      iVar2 = FindPlace__9MenuGroupFs(iStack_30,100);
      iVar2 = iStack_40 + *(short *)(iVar2 + 0x22) * 0x100;
      SetCSA__8FontItemFUc(iVar2 + 0x1800,1);
      SetCSA__8FontItemFUc(iVar2 + 0x1880,1);
    }
    else {
      SetCSA__8FontItemFUc((short)(sVar1 + -4) * 0x80 + iStack_40 + 0x1700,1);
    }
    if (sStack_10 != 0) {
      uStack_60 = _5066;
      uStack_58 = DAT_0050d908;
      uStack_42 = *(ushort *)((int)&uStack_60 + sVar1 * 2);
      SetExplanation__7CmdNoteFPCce
                (*(undefined4 *)(iStack_40 + 0x1c0c),
                 *(undefined4 *)((uint)uStack_42 * 0xc + *(int *)(iStack_40 + 0x28) + 0x14));
    }
  }
  return;
}

/* JP: 0x004793f0  CmdKeyCustom::Enter()   [Enter__12CmdKeyCustomFv]  size=0x1e4 */
undefined8 Enter__12CmdKeyCustomFv(int param_1)

{
  bool bVar1;
  undefined4 uVar2;
  undefined *puVar3;
  undefined8 uVar4;
  
  if (*(char *)(param_1 + 0x21) == '\0') {
    Open__10MenuWindowFUci(param_1 + 0x228,*(byte *)(param_1 + 0x2d8) & 7,
                    *(undefined4 *)(*(int *)(param_1 + 0x25c) + 0x10));
    Open__10MenuWindowFUci(param_1 + 0x111c,*(byte *)(param_1 + 0x11cc) & 7,
                    *(undefined4 *)(*(int *)(param_1 + 0x1150) + 0x10));
    SetTitle__11CmdTitleLogFPUci
              (*(undefined4 *)(param_1 + 0x1c08),*(undefined4 *)(*(int *)(param_1 + 0x54) + 0x10),9)
    ;
    Open__11CmdTitleLogFv(*(undefined4 *)(param_1 + 0x1c08));
    *(char *)(param_1 + 0x21) = *(char *)(param_1 + 0x21) + '\x01';
  }
  else if (*(char *)(param_1 + 0x21) == '\x01') {
    if ((*(char *)(param_1 + 0x11c4) == '\x01') || (*(char *)(param_1 + 0x11c4) == '\0')) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
    if (bVar1) {
      uVar4 = GetPlace__10MenuWindowFss(param_1 + 0x111c,0,0);
      Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),uVar4);
      Select__12CmdKeyCustomFP9MenuPlaceP9MenuPlaces(param_1,uVar4,0,1);
      puVar3 = PTR_SelectButton__12CmdKeyCustomFv_0050d918;
      uVar2 = DAT_0050d914;
      *(undefined4 *)(param_1 + 0x58) = _5105;
      *(undefined4 *)(param_1 + 0x5c) = uVar2;
      *(undefined **)(param_1 + 0x60) = puVar3;
      *(undefined1 *)(param_1 + 0x21) = 0;
    }
  }
  return 0;
}

/* JP: 0x004795e0  CmdKeyCustom::Exit()   [Exit__12CmdKeyCustomFv]  size=0x1dc */
undefined8 Exit__12CmdKeyCustomFv(int param_1)

{
  int iVar1;
  bool bVar2;
  
  if (*(char *)(param_1 + 0x21) == '\0') {
    Leave__6CursorFv(*(undefined4 *)(param_1 + 0x18));
    (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x14) + 0x28))
              (*(int *)(param_1 + 0x10),0x10,0x11,0);
    Close__10MenuWindowFUci(param_1 + 0x228,((ulong)*(byte *)(param_1 + 0x2d8) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(param_1 + 0x25c) + 0x14));
    Close__10MenuWindowFUci(param_1 + 0x111c,((ulong)*(byte *)(param_1 + 0x11cc) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(param_1 + 0x1150) + 0x14));
    iVar1 = *(int *)(param_1 + 0x1c08);
    Close__10MenuWindowFUci(iVar1 + 0x58,((ulong)*(byte *)(iVar1 + 0x108) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar1 + 0x8c) + 0x14));
    *(char *)(param_1 + 0x21) = *(char *)(param_1 + 0x21) + '\x01';
  }
  else if (*(char *)(param_1 + 0x21) == '\x01') {
    if ((*(char *)(param_1 + 0x2d0) == '\x01') || (*(char *)(param_1 + 0x2d0) == '\0')) {
      bVar2 = true;
    }
    else {
      bVar2 = false;
    }
    if (bVar2) {
      ReleaseOT__7MenuObjFv(param_1 + 0x228);
      ReleaseOT__7MenuObjFv(param_1 + 0x111c);
      (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x14) + 0x24))(*(int *)(param_1 + 0x10),0x10)
      ;
      DestroyScene__4MenuFP9MenuSceneb(*(undefined4 *)(param_1 + 0x10),param_1,1);
    }
  }
  return 0;
}

/* JP: 0x004797c0  CmdKeyCustom::SelectButton()   [SelectButton__12CmdKeyCustomFv]  size=0x3b0 */
undefined8 SelectButton__12CmdKeyCustomFv(int param_1)

{
  ushort uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined *puVar4;
  int iVar5;
  undefined8 uVar6;
  short sVar7;
  
  puVar4 = PTR_Exit__12CmdKeyCustomFv_0050d948;
  uVar3 = DAT_0050d944;
  uVar1 = *(ushort *)(*(int *)(param_1 + 0x10) + 0x48);
  iVar2 = *(int *)(*(int *)(param_1 + 0x18) + 0xec);
  if ((uVar1 & 0x2000) == 0) {
    if ((uVar1 & 0x4000) == 0) {
      iVar2 = *(int *)(*(int *)(param_1 + 0x18) + 0xec);
      iVar5 = MoveVertical__9MenuSceneFi(param_1,0);
      if (iVar2 != iVar5) {
        Select__12CmdKeyCustomFP9MenuPlaceP9MenuPlaces(param_1,iVar5,iVar2,1);
        PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 100),0,0,0);
      }
    }
    else {
      *(undefined4 *)(param_1 + 0x58) = _5162;
      *(undefined4 *)(param_1 + 0x5c) = uVar3;
      *(undefined **)(param_1 + 0x60) = puVar4;
      PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 100),3,0,0);
    }
  }
  else {
    sVar7 = *(short *)(iVar2 + 0x1e);
    if (sVar7 == 5) {
      SetAssign__12CmdKeyCustomFi(param_1,1);
      UpdatePad__15SaveMenuSectionFv();
      puVar4 = PTR_Exit__12CmdKeyCustomFv_0050d928;
      uVar3 = DAT_0050d924;
      *(undefined4 *)(param_1 + 0x58) = _5152;
      *(undefined4 *)(param_1 + 0x5c) = uVar3;
      *(undefined **)(param_1 + 0x60) = puVar4;
    }
    else if (sVar7 == 4) {
      SetButton__12CmdKeyCustomFi(param_1,0);
      SetDefaultButton__15SaveMenuSectionFv();
      SetAssign__12CmdKeyCustomFi(param_1,0);
      SetButton__12CmdKeyCustomFi(param_1,1);
    }
    else {
      Select__6CursorFP9MenuPlace(param_1 + 0x68,iVar2);
      QuickMove__6CursorFv(param_1 + 0x68);
      AddOT__7MenuObjFv(param_1 + 0x68);
      *(byte *)(iVar2 + 0x21) = *(byte *)(iVar2 + 0x21) & 0xfd;
      sVar7 = sVar7 + 1;
      if (3 < sVar7) {
        sVar7 = 0;
      }
      uVar6 = GetPlace__10MenuWindowFss(param_1 + 0x111c,0,sVar7);
      Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),uVar6);
      Select__12CmdKeyCustomFP9MenuPlaceP9MenuPlaces(param_1,uVar6,0,0);
      DisableFontItem__8FontItemFv(param_1 + 0x1700);
      DisableFontItem__8FontItemFv(param_1 + 0x1780);
      SetExplanation__7CmdNoteFPCce
                (*(undefined4 *)(param_1 + 0x1c0c),*(undefined4 *)(*(int *)(param_1 + 0x28) + 0x5c))
      ;
      puVar4 = PTR_SwapButton__12CmdKeyCustomFv_0050d938;
      uVar3 = DAT_0050d934;
      *(undefined4 *)(param_1 + 0x58) = _5157;
      *(undefined4 *)(param_1 + 0x5c) = uVar3;
      *(undefined **)(param_1 + 0x60) = puVar4;
    }
    PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 100),2,0,0);
  }
  return 0;
}

/* JP: 0x00479b70  CmdKeyCustom::SwapButton()   [SwapButton__12CmdKeyCustomFv]  size=0x2e0 */
undefined8 SwapButton__12CmdKeyCustomFv(int param_1)

{
  ushort uVar1;
  undefined2 uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined *puVar5;
  int iVar6;
  
  uVar1 = *(ushort *)(*(int *)(param_1 + 0x10) + 0x48);
  iVar3 = *(int *)(*(int *)(param_1 + 0x18) + 0xec);
  if ((uVar1 & 0x6000) == 0) {
    iVar3 = *(int *)(*(int *)(param_1 + 0x18) + 0xec);
    iVar6 = MoveVertical__9MenuSceneFi(param_1,0);
    if (iVar3 != iVar6) {
      Select__12CmdKeyCustomFP9MenuPlaceP9MenuPlaces(param_1,iVar6,iVar3,0);
      PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 100),0,0,0);
    }
  }
  else {
    iVar6 = *(int *)(param_1 + 0x154);
    if ((uVar1 & 0x2000) == 0) {
      PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 100),3,0,0);
    }
    else {
      SetButton__12CmdKeyCustomFi(param_1,0);
      uVar1 = *(ushort *)(iVar6 + 0x1e);
      uVar2 = *(undefined2 *)(param_1 + (uint)*(ushort *)(iVar3 + 0x1e) * 2 + 0x1c00);
      *(undefined2 *)(param_1 + (uint)*(ushort *)(iVar3 + 0x1e) * 2 + 0x1c00) =
           *(undefined2 *)(param_1 + (uint)uVar1 * 2 + 0x1c00);
      *(undefined2 *)(param_1 + (uint)uVar1 * 2 + 0x1c00) = uVar2;
      SetButton__12CmdKeyCustomFi(param_1,1);
      Select__12CmdKeyCustomFP9MenuPlaceP9MenuPlaces(param_1,0,iVar3,1);
      PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 100),2,0,0);
    }
    Select__12CmdKeyCustomFP9MenuPlaceP9MenuPlaces(param_1,iVar3,iVar6,1);
    *(byte *)(iVar6 + 0x21) = *(byte *)(iVar6 + 0x21) & 0xfd | 2;
    EnableFontItem__8FontItemFv(param_1 + 0x1700);
    EnableFontItem__8FontItemFv(param_1 + 0x1780);
    ReleaseOT__7MenuObjFv(param_1 + 0x68);
    puVar5 = PTR_SelectButton__12CmdKeyCustomFv_0050d958;
    uVar4 = DAT_0050d954;
    *(undefined4 *)(param_1 + 0x58) = _5210;
    *(undefined4 *)(param_1 + 0x5c) = uVar4;
    *(undefined **)(param_1 + 0x60) = puVar5;
  }
  return 0;
}
