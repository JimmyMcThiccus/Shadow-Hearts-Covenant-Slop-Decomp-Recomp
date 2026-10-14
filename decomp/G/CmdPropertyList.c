/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdPropertyList   functions: 16
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdPropertyList.md).
 */

/* JP: 0x0049b890  CmdPropertyList::CmdPropertyList()   [__ct__15CmdPropertyListFv]  size=0x94 */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __ct__15CmdPropertyListFv(int param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  __ct__9MenuSceneFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__15CmdPropertyList;
  uVar2 = uRam004236d0;
  uVar1 = uRam004236cc;
  *(undefined4 *)(param_1 + 0x58) = ___ptmf_null;
  *(undefined4 *)(param_1 + 0x5c) = uVar1;
  *(undefined4 *)(param_1 + 0x60) = uVar2;
  __ct__9MenuSceneFv(param_1 + 0x78);
  __ct__9MenuSceneFv(param_1 + 0xd0);
  *(undefined4 *)(param_1 + 300) = 0;
  *(undefined4 *)(param_1 + 0x13c) = 0;
  return param_1;
}

/* JP: 0x0049b930  CmdPropertyList::~CmdPropertyList()   [__dt__15CmdPropertyListFv]  size=0xe4 */
int __dt__15CmdPropertyListFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__15CmdPropertyList;
    (**(code **)(*(int *)(*(int *)(param_1 + 0x128) + 8) + 0xc))();
    (**(code **)(*(int *)(*(int *)(param_1 + 300) + 8) + 0xc))();
    (**(code **)(*(int *)(*(int *)(param_1 + 0x13c) + 8) + 0xc))();
    __dt__9MenuSceneFv(param_1 + 0xd0,0xffffffffffffffff);
    __dt__9MenuSceneFv(param_1 + 0x78,0xffffffffffffffff);
    __dt__9MenuSceneFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x0049ba20  CmdPropertyList::GetReady()   [GetReady__15CmdPropertyListFv]  size=0x6f8 */
undefined4 GetReady__15CmdPropertyListFv(int param_1)

{
  undefined *puVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  long lVar6;
  ushort uVar7;
  uint uVar8;
  short sVar9;
  undefined1 auStack_f0 [96];
  int iStack_90;
  int iStack_8c;
  int iStack_88;
  int iStack_84;
  int iStack_80;
  int iStack_7c;
  undefined4 *puStack_78;
  undefined4 *puStack_74;
  undefined4 *puStack_70;
  undefined4 *puStack_6c;
  int iStack_68;
  int iStack_64;
  int iStack_60;
  int iStack_5c;
  int iStack_58;
  int iStack_54;
  int iStack_50;
  int iStack_4c;
  undefined4 uStack_48;
  int iStack_44;
  int iStack_40;
  int iStack_3c;
  int iStack_38;
  int iStack_34;
  int iStack_30;
  int iStack_2c;
  int iStack_28;
  int iStack_24;
  int iStack_20;
  int iStack_1c;
  undefined4 uStack_18;
  undefined2 uStack_14;
  char cStack_12;
  char cStack_11;
  int iStack_10;
  
  iStack_10 = param_1;
  __ct__9MenuSceneFv(auStack_f0);
  iVar3 = *(int *)(iStack_10 + 0x10);
  uStack_48 = sm_pSound__7MenuObj;
  *(undefined4 *)(iStack_10 + 100) = sm_pSound__7MenuObj;
  iStack_4c = iVar3 + 0x348;
  iStack_54 = iVar3 + 0x3a0;
  *(int *)(iStack_10 + 0x18) = iStack_54;
  iStack_58 = iVar3 + 0xb8;
  *(int *)(iStack_10 + 0x68) = iStack_58;
  iStack_5c = iVar3 + 0x4e0;
  *(int *)(iStack_10 + 0x6c) = iStack_5c;
  iStack_60 = iVar3 + 0xa60;
  *(int *)(iStack_10 + 0x74) = iStack_60;
  iStack_64 = iVar3 + 0x780;
  *(int *)(iStack_10 + 0x70) = iStack_64;
  iVar3 = iVar3 + 0x28;
  iStack_68 = iVar3;
  iStack_50 = iStack_54;
  iStack_1c = iStack_4c;
  iVar4 = Find__13MenuDataTableFs(iVar3,0x16);
  *(int *)(iStack_10 + 0x140) = iVar4 + 0x10;
  iVar4 = Find__13MenuDataTableFs(iVar3,0xb);
  *(int *)(iStack_10 + 0x144) = iVar4 + 0x10;
  iVar4 = Find__13MenuDataTableFs(iVar3,8);
  *(int *)(iStack_10 + 0x148) = iVar4 + 0x10;
  iVar4 = Find__13MenuDataTableFs(iVar3,9);
  *(int *)(iStack_10 + 0x14c) = iVar4 + 0x10;
  iVar4 = Find__13MenuDataTableFs(iVar3,10);
  *(int *)(iStack_10 + 0x150) = iVar4 + 0x10;
  iVar4 = Find__13MenuDataTableFs(iVar3,0x15);
  *(int *)(iStack_10 + 0x154) = iVar4 + 0x10;
  iVar4 = Find__13MenuDataTableFs(iVar3,0x19);
  *(int *)(iStack_10 + 0x158) = iVar4 + 0x10;
  iVar4 = Find__13MenuDataTableFs(iVar3,0x17);
  *(int *)(iStack_10 + 0x15c) = iVar4 + 0x10;
  iVar3 = Find__13MenuDataTableFs(iVar3,0xc);
  *(int *)(iStack_10 + 0x160) = iVar3 + 0x10;
  for (uVar8 = 1; uVar8 < 7; uVar8 = uVar8 + 1 & 0xffff) {
    puStack_6c = (undefined4 *)(uVar8 * 0xc + *(int *)(iStack_10 + 0x54) + 0x10);
    Convert__13MenuDataTableFPUci(*puStack_6c,0);
  }
  puStack_70 = (undefined4 *)(*(int *)(iStack_10 + 0x54) + 0x28);
  Initialize__9MenuSceneFPUcP9BufMemory(iStack_10 + 0x78,*puStack_70,0);
  puStack_74 = (undefined4 *)(*(int *)(iStack_10 + 0x54) + 0x58);
  Initialize__9MenuSceneFPUcP9BufMemory(iStack_10 + 0xd0,*puStack_74,0);
  lVar6 = __nw__FUi(0x154);
  uVar5 = 0;
  if (lVar6 != 0) {
    uVar5 = __ct__10CmdSubMenuFv(lVar6);
  }
  *(undefined4 *)(iStack_10 + 0x128) = uVar5;
  puStack_78 = (undefined4 *)(*(int *)(iStack_10 + 0x54) + 0x1c);
  Initialize__9MenuSceneFPUcP9BufMemory(*(undefined4 *)(iStack_10 + 0x128),*puStack_78,0);
  iStack_7c = *(int *)(iStack_10 + 0x28) + 0x10;
  CreateScene__10CmdSubMenuFsP9MSDSystem(*(undefined4 *)(iStack_10 + 0x128),7,iStack_7c);
  cStack_11 = *(char *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x303);
  if (cStack_11 == '\x01') {
    iStack_24 = *(int *)(iStack_10 + 0x128);
    DisableFontItem__8FontItemFv(*(undefined4 *)(iStack_24 + 0x14c));
  }
  else if (cStack_11 == '\0') {
    iStack_20 = *(int *)(iStack_10 + 0x128);
    iStack_38 = *(int *)(iStack_20 + 0x14c);
    *(byte *)(iStack_38 + 0x12) = *(byte *)(iStack_38 + 0x12) & 0xfe;
  }
  cStack_12 = *(char *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x305);
  if (cStack_12 == '\x01') {
    iStack_2c = *(int *)(iStack_10 + 0x128);
    DisableFontItem__8FontItemFv(*(int *)(iStack_2c + 0x14c) + 0x300);
  }
  else if (cStack_12 == '\0') {
    iStack_28 = *(int *)(iStack_10 + 0x128);
    iVar3 = *(int *)(iStack_28 + 0x14c);
    iStack_3c = iVar3 + 0x300;
    *(byte *)(iVar3 + 0x312) = *(byte *)(iVar3 + 0x312) & 0xfe;
  }
  sVar9 = 0;
  iVar3 = *(int *)(iStack_10 + 0x24) + 0x10;
  iStack_80 = iVar3;
  for (uVar7 = 0; uVar7 < 7; uVar7 = uVar7 + 1) {
    iStack_40 = *(int *)(iStack_10 + 0x128);
    iStack_88 = *(int *)(iStack_40 + 0x14c) + (short)uVar7 * 0x80;
    iStack_84 = iStack_88;
    iStack_30 = iStack_88;
    if ((*(byte *)(iStack_88 + 0x12) & 1) != 0) {
      if (*(short *)(iVar3 + 4) == 9) {
        sVar2 = 0x90;
      }
      else {
        sVar2 = GetRegCnt__9RegDatApiFii(*(undefined2 *)
                                 (*(int *)(iStack_10 + 0x140) + *(short *)(iVar3 + 4) * 0xc + 8),
                                0xffffffffffffffff);
      }
      if (sVar9 < sVar2) {
        sVar9 = sVar2;
      }
      uStack_14 = *(undefined2 *)(iVar3 + 4);
      iStack_44 = *(int *)(iStack_10 + 0x128);
      iStack_90 = *(int *)(iStack_44 + 0x14c) + (short)uVar7 * 0x80;
      *(undefined2 *)(iStack_90 + 0x16) = uStack_14;
      iStack_8c = iStack_90;
      iStack_34 = iStack_90;
    }
    iVar3 = iVar3 + 8;
  }
  lVar6 = __nw__FUi(0x178);
  uVar5 = 0;
  if (lVar6 != 0) {
    uVar5 = __ct__8CmdFenceFv(lVar6);
  }
  *(undefined4 *)(iStack_10 + 300) = uVar5;
  CreateFence__8CmdFenceFP9MenuScenePUc(*(undefined4 *)(iStack_10 + 300),iStack_10 + 0x78,0);
  lVar6 = __nw__FUi(300);
  uVar5 = 0;
  if (lVar6 != 0) {
    uVar5 = __ct__16CmdPropertyGoodsFv(lVar6);
  }
  *(undefined4 *)(iStack_10 + 0x13c) = uVar5;
  CreateScene__16CmdPropertyGoodsFP15CmdPropertyLists
            (*(undefined4 *)(iStack_10 + 0x13c),iStack_10,sVar9);
  puVar1 = PTR_Enter__15CmdPropertyListFv_0050dd18;
  uVar5 = DAT_0050dd14;
  *(undefined4 *)(iStack_10 + 0x58) = _5139;
  *(undefined4 *)(iStack_10 + 0x5c) = uVar5;
  *(undefined **)(iStack_10 + 0x60) = puVar1;
  uStack_18 = 1;
  __dt__9MenuSceneFv(auStack_f0,0xffffffffffffffff);
  return uStack_18;
}

/* JP: 0x0049c120  CmdPropertyList::Run()   [Run__15CmdPropertyListFv]  size=0x5c */
undefined8 Run__15CmdPropertyListFv(int param_1)

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

/* JP: 0x0049c180  CmdPropertyList::UpdateGoods(short, short)   [UpdateGoods__15CmdPropertyListFss]  size=0xc4 */
void UpdateGoods__15CmdPropertyListFss(int param_1,short param_2,undefined2 param_3)

{
  UpdateScene__16CmdPropertyGoodsFP15CmdPropertyListss
            (*(undefined4 *)(param_1 + 0x13c),param_1,param_2,param_3);
  SetTitle__8CmdFenceFP9MenuScenes
            (*(undefined4 *)(param_1 + 300),param_1 + 0x78,
             *(undefined2 *)(*(int *)(param_1 + 0x140) + param_2 * 0xc + 6));
  *(short *)(param_1 + 0x16a) = param_2;
  *(undefined2 *)(param_1 + 0x168) = param_3;
  *(int *)(param_1 + 0x164) = *(int *)(param_1 + 0x140) + param_2 * 0xc;
  return;
}

/* JP: 0x0049c250  CmdPropertyList::SetExplanation()   [SetExplanation__15CmdPropertyListFv]  size=0x370 */
void SetExplanation__15CmdPropertyListFv(int param_1)

{
  ushort uVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  undefined8 uVar6;
  
  iVar3 = *(int *)(param_1 + 0x134);
  memset(iVar3 + 0x5c,0,0x10);
  iVar4 = *(int *)(*(int *)(param_1 + 0x18) + 0xec);
  uVar1 = *(ushort *)(iVar4 + 0x16);
  *(ushort *)(iVar3 + 0x5c) = uVar1;
  *(char *)(iVar3 + 0x5e) = (char)*(undefined2 *)(iVar4 + 0x22);
  uVar5 = GetRegDat__9RegDatApiFiii(*(undefined2 *)(*(int *)(param_1 + 0x164) + 2),uVar1,0xffffffffffffffff);
  *(undefined4 *)(iVar3 + 0x60) = uVar5;
  sVar2 = *(short *)(param_1 + 0x16a);
  if (sVar2 == 5) {
    *(undefined4 *)(iVar3 + 100) = *(undefined4 *)(*(int *)(param_1 + 0x158) + (uint)uVar1 * 8);
    *(uint *)(iVar3 + 0x68) = *(int *)(param_1 + 0x158) + (uint)uVar1 * 8 + 4;
  }
  else if (sVar2 == 3) {
    *(undefined4 *)(iVar3 + 100) = *(undefined4 *)(*(int *)(param_1 + 0x150) + (uint)uVar1 * 0xc);
    *(uint *)(iVar3 + 0x68) = *(int *)(param_1 + 0x150) + (uint)uVar1 * 0xc + 4;
  }
  else if (sVar2 == 2) {
    *(undefined4 *)(iVar3 + 100) = *(undefined4 *)(*(int *)(param_1 + 0x14c) + (uint)uVar1 * 0xc);
    *(uint *)(iVar3 + 0x68) = *(int *)(param_1 + 0x14c) + (uint)uVar1 * 0xc + 4;
  }
  else if (sVar2 == 1) {
    *(undefined4 *)(iVar3 + 100) = *(undefined4 *)(*(int *)(param_1 + 0x148) + (uint)uVar1 * 0xc);
    *(uint *)(iVar3 + 0x68) = *(int *)(param_1 + 0x148) + (uint)uVar1 * 0xc + 4;
  }
  else if (sVar2 == 0) {
    *(undefined4 *)(iVar3 + 100) = *(undefined4 *)(*(int *)(param_1 + 0x144) + (uint)uVar1 * 0x1c);
    *(uint *)(iVar3 + 0x68) = *(int *)(param_1 + 0x144) + (uint)uVar1 * 0x1c + 4;
  }
  else if (sVar2 == 9) {
    *(undefined4 *)(iVar3 + 100) = *(undefined4 *)(*(int *)(param_1 + 0x154) + (uint)uVar1 * 8);
    *(uint *)(iVar3 + 0x68) = *(int *)(param_1 + 0x154) + (uint)uVar1 * 8 + 4;
  }
  uVar6 = 0;
  if (-1 < (long)((ulong)*(byte *)(iVar4 + 0x21) << 0x3c)) {
    uVar6 = 2;
  }
  SetCSA__8FontItemFUc(iVar3 + 0x314,uVar6);
  SetCSA__8FontItemFUc(iVar3 + 0x394,uVar6);
  Open__10CmdExplainFv(iVar3);
  return;
}

/* JP: 0x0049c5c0  CmdPropertyList::Enter()   [Enter__15CmdPropertyListFv]  size=0x2c0 */
undefined8 Enter__15CmdPropertyListFv(int param_1)

{
  bool bVar1;
  undefined4 uVar2;
  undefined *puVar3;
  undefined1 uVar4;
  int iVar5;
  
  if (*(char *)(param_1 + 0x21) == '\0') {
    UpdateScene__10CmdSubMenuFs(*(undefined4 *)(param_1 + 0x128),0);
    iVar5 = GetPlace__10MenuWindowFiss(*(int *)(param_1 + 0x128) + 0x58,2,0,0xffffffffffffffff);
    Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),iVar5);
    Select__10CmdSubMenuFP7CmdNoteP9MenuPlaceP9MenuPlace
              (*(undefined4 *)(param_1 + 0x128),*(undefined4 *)(param_1 + 0x6c),iVar5,0);
    UpdateGoods__15CmdPropertyListFss
              (param_1,*(undefined2 *)(iVar5 + 0x16),*(undefined2 *)(iVar5 + 0x1e));
    iVar5 = *(int *)(param_1 + 0x13c);
    Open__10MenuWindowFUci(iVar5,*(byte *)(iVar5 + 0xb0) & 7,*(undefined4 *)(*(int *)(iVar5 + 0x34) + 0x10)
                   );
    iVar5 = *(int *)(param_1 + 300);
    Open__10MenuWindowFUci(iVar5,*(byte *)(iVar5 + 0xb0) & 7,*(undefined4 *)(*(int *)(iVar5 + 0x34) + 0x10)
                   );
    SetTitle__11CmdTitleLogFPUci
              (*(undefined4 *)(param_1 + 0x70),*(undefined4 *)(*(int *)(param_1 + 0x54) + 0x10),0x22
              );
    Open__11CmdTitleLogFv(*(undefined4 *)(param_1 + 0x70));
    uVar4 = CreateBackGround__7CmdMenuFs(*(undefined4 *)(param_1 + 0x10),8);
    *(undefined1 *)(param_1 + 0x20) = uVar4;
    *(char *)(param_1 + 0x21) = *(char *)(param_1 + 0x21) + '\x01';
  }
  else if (*(char *)(param_1 + 0x21) == '\x01') {
    if ((*(char *)(*(int *)(param_1 + 0x13c) + 0xa8) == '\x01') ||
       (*(char *)(*(int *)(param_1 + 0x13c) + 0xa8) == '\0')) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
    if (bVar1) {
      if (*(char *)(param_1 + 0x20) != '\0') {
        DestroyBackGround__7CmdMenuFs(*(undefined4 *)(param_1 + 0x10),1);
        *(undefined1 *)(param_1 + 0x20) = 0;
      }
      Restore__6CursorFv(*(undefined4 *)(param_1 + 0x18));
      puVar3 = PTR_SelectMenu__15CmdPropertyListFv_0050dd28;
      uVar2 = DAT_0050dd24;
      *(undefined4 *)(param_1 + 0x58) = _5292;
      *(undefined4 *)(param_1 + 0x5c) = uVar2;
      *(undefined **)(param_1 + 0x60) = puVar3;
      *(undefined1 *)(param_1 + 0x21) = 0;
    }
  }
  return 0;
}

/* JP: 0x0049c880  CmdPropertyList::Exit()   [Exit__15CmdPropertyListFv]  size=0x1d0 */
undefined8 Exit__15CmdPropertyListFv(int param_1)

{
  int iVar1;
  bool bVar2;
  
  if (*(char *)(param_1 + 0x21) == '\0') {
    (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x14) + 0x28))
              (*(int *)(param_1 + 0x10),0,0,0x12);
    Shutdown__6CursorFv(*(undefined4 *)(param_1 + 0x18));
    iVar1 = *(int *)(param_1 + 0x13c);
    Close__10MenuWindowFUci(iVar1,((ulong)*(byte *)(iVar1 + 0xb0) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x14));
    iVar1 = *(int *)(param_1 + 300);
    Close__10MenuWindowFUci(iVar1,((ulong)*(byte *)(iVar1 + 0xb0) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x14));
    iVar1 = *(int *)(param_1 + 0x128);
    Close__10MenuWindowFUci(iVar1 + 0x58,((ulong)*(byte *)(iVar1 + 0x108) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar1 + 0x8c) + 0x14));
    *(char *)(param_1 + 0x21) = *(char *)(param_1 + 0x21) + '\x01';
  }
  else if (*(char *)(param_1 + 0x21) == '\x01') {
    if ((*(char *)(*(int *)(param_1 + 0x13c) + 0xa8) == '\x01') ||
       (*(char *)(*(int *)(param_1 + 0x13c) + 0xa8) == '\0')) {
      bVar2 = true;
    }
    else {
      bVar2 = false;
    }
    if (bVar2) {
      (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x14) + 0x24))(*(int *)(param_1 + 0x10),0);
      DestroyScene__4MenuFP9MenuSceneb(*(undefined4 *)(param_1 + 0x10),param_1,1);
    }
  }
  return 0;
}

/* JP: 0x0049ca50  CmdPropertyList::SelectMenu()   [SelectMenu__15CmdPropertyListFv]  size=0x378 */
undefined8 SelectMenu__15CmdPropertyListFv(int param_1)

{
  ushort uVar1;
  int iVar2;
  undefined *puVar3;
  int iVar4;
  undefined8 uVar5;
  ulong uVar6;
  undefined4 uVar7;
  
  puVar3 = PTR_Exit__15CmdPropertyListFv_0050dd48;
  uVar7 = DAT_0050dd44;
  uVar1 = *(ushort *)(*(int *)(param_1 + 0x10) + 0x48);
  iVar2 = *(int *)(*(int *)(param_1 + 0x18) + 0xec);
  if ((uVar1 & 0x2000) == 0) {
    if ((uVar1 & 0x4000) == 0) {
      iVar4 = MoveVertical__9MenuSceneFi(param_1,0);
      if (iVar2 != iVar4) {
        Select__10CmdSubMenuFP7CmdNoteP9MenuPlaceP9MenuPlace
                  (*(undefined4 *)(param_1 + 0x128),*(undefined4 *)(param_1 + 0x6c),iVar4,iVar2);
        UpdateGoods__15CmdPropertyListFss
                  (param_1,*(undefined2 *)(iVar4 + 0x16),*(undefined2 *)(iVar4 + 0x1e));
        PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 100),0,0,0);
      }
    }
    else {
      *(undefined4 *)(param_1 + 0x58) = _5373;
      *(undefined4 *)(param_1 + 0x5c) = uVar7;
      *(undefined **)(param_1 + 0x60) = puVar3;
      PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 100),3,0,0);
    }
  }
  else {
    uVar7 = 4;
    if (*(short *)(*(int *)(param_1 + 0x13c) + 0x12a) != 0) {
      iVar2 = *(int *)(param_1 + 0x74);
      uVar5 = GetPlace__10MenuWindowFss(*(undefined4 *)(param_1 + 0x13c),0,0);
      Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),uVar5);
      Select__16CmdPropertyGoodsFP7CmdNoteP9MenuGroupP9MenuGroup
                (*(undefined4 *)(param_1 + 0x13c),*(undefined4 *)(param_1 + 0x6c),uVar5,0);
      ClearReport__15CmdButtonReportFv(iVar2);
      if (*(int *)(*(int *)(param_1 + 0x13c) + 0x44) == 0) {
        uVar6 = 0;
      }
      else {
        uVar6 = ((ulong)*(ushort *)(*(int *)(param_1 + 0x13c) + 0xb2) & 0x3ff) >> 2;
      }
      if (uVar6 != 0) {
        SetReport__15CmdButtonReportFii(iVar2,*(undefined1 *)(iVar2 + 0x20),0xd);
      }
      if (-1 < *(char *)(*(int *)(param_1 + 0x164) + 0xb)) {
        SetReport__15CmdButtonReportFii(iVar2,*(undefined1 *)(iVar2 + 0x20),6);
      }
      if (*(short *)(param_1 + 0x16a) == 4) {
        SetReport__15CmdButtonReportFii(iVar2,*(undefined1 *)(iVar2 + 0x20),0x11);
      }
      else {
        SetReport__15CmdButtonReportFii(iVar2,*(undefined1 *)(iVar2 + 0x20),4);
      }
      Open__15CmdButtonReportFv(*(undefined4 *)(param_1 + 0x74));
      puVar3 = PTR_SelectGoods__15CmdPropertyListFv_0050dd38;
      uVar7 = DAT_0050dd34;
      *(undefined4 *)(param_1 + 0x58) = _5368;
      *(undefined4 *)(param_1 + 0x5c) = uVar7;
      *(undefined **)(param_1 + 0x60) = puVar3;
      uVar7 = 2;
    }
    PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 100),uVar7,0,0);
  }
  return 0;
}

/* JP: 0x0049cdd0  CmdPropertyList::SelectGoods()   [SelectGoods__15CmdPropertyListFv]  size=0x728 */
undefined8 SelectGoods__15CmdPropertyListFv(int param_1)

{
  char cVar1;
  ushort uVar2;
  undefined *puVar3;
  int iVar4;
  undefined4 uVar5;
  long lVar6;
  undefined8 uVar7;
  int iVar8;
  
  uVar2 = *(ushort *)(*(int *)(param_1 + 0x10) + 0x48);
  iVar8 = *(int *)(*(int *)(param_1 + 0x18) + 0xec);
  if (((uVar2 & 0x8000) != 0) && (cVar1 = *(char *)(*(int *)(param_1 + 0x164) + 0xb), -1 < cVar1)) {
    lVar6 = __nw__FUi(0x160);
    uVar7 = 0;
    if (lVar6 != 0) {
      uVar7 = __ct__7CmdSortFv(lVar6);
    }
    iVar8 = (int)uVar7;
    *(int *)(param_1 + 0x130) = iVar8;
    *(ushort *)(iVar8 + 0x15a) =
         (ushort)*(byte *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x28c + (int)(short)cVar1);
    *(undefined4 *)(iVar8 + 0x15c) = *(undefined4 *)(*(int *)(param_1 + 0x18) + 0xec);
    *(undefined4 *)(iVar8 + 0x10) = *(undefined4 *)(param_1 + 0x10);
    Initialize__9MenuSceneFPUcP9BufMemory(uVar7,*(undefined4 *)
                           (((int)(short)cVar1 + 3U & 0xffff) * 0xc + *(int *)(param_1 + 0x54) +
                           0x10),0);
    iVar8 = *(int *)(*(int *)(param_1 + 0x13c) + 0x44);
    *(byte *)(iVar8 + 0x12) = *(byte *)(iVar8 + 0x12) & 0xfe;
    iVar8 = *(int *)(param_1 + 0x74);
    Close__10MenuWindowFUci(iVar8 + 0x58,((ulong)*(byte *)(iVar8 + 0x108) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar8 + 0x8c) + 0x14));
    puVar3 = PTR_ExecSort__15CmdPropertyListFv_0050dd58;
    uVar5 = DAT_0050dd54;
    *(undefined4 *)(param_1 + 0x58) = _5421;
    *(undefined4 *)(param_1 + 0x5c) = uVar5;
    *(undefined **)(param_1 + 0x60) = puVar3;
    PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 100),2,0,0);
    return 0;
  }
  if ((uVar2 & 0x1000) == 0) {
    if ((uVar2 & 0x4000) == 0) {
      iVar4 = MoveVertical__9MenuSceneFi(param_1,1);
      if (iVar8 != iVar4) {
        Select__16CmdPropertyGoodsFP7CmdNoteP9MenuGroupP9MenuGroup
                  (*(undefined4 *)(param_1 + 0x13c),*(undefined4 *)(param_1 + 0x6c),iVar4,iVar8);
        PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 100),0,0,0);
      }
    }
    else {
      uVar5 = GetPlace__10MenuWindowFs(*(int *)(param_1 + 0x128) + 0x58,*(undefined2 *)(param_1 + 0x16a));
      Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),uVar5);
      Select__10CmdSubMenuFP7CmdNoteP9MenuPlaceP9MenuPlace
                (*(undefined4 *)(param_1 + 0x128),*(undefined4 *)(param_1 + 0x6c),uVar5,0);
      SetScroll__10MenuWindowFss(*(undefined4 *)(param_1 + 0x13c),0,0);
      Select__16CmdPropertyGoodsFP7CmdNoteP9MenuGroupP9MenuGroup
                (*(undefined4 *)(param_1 + 0x13c),0,0,iVar8);
      iVar8 = *(int *)(param_1 + 0x74);
      Close__10MenuWindowFUci(iVar8 + 0x58,((ulong)*(byte *)(iVar8 + 0x108) & 0x3f) >> 3,
                      *(undefined4 *)(*(int *)(iVar8 + 0x8c) + 0x14));
      puVar3 = PTR_SelectMenu__15CmdPropertyListFv_0050dd88;
      uVar5 = DAT_0050dd84;
      *(undefined4 *)(param_1 + 0x58) = _5439;
      *(undefined4 *)(param_1 + 0x5c) = uVar5;
      *(undefined **)(param_1 + 0x60) = puVar3;
      PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 100),3,0,0);
    }
  }
  else {
    iVar4 = (uint)(ushort)(*(short *)(param_1 + 0x168) + 7) * 0xc + *(int *)(param_1 + 0x28);
    Select__16CmdPropertyGoodsFP7CmdNoteP9MenuGroupP9MenuGroup
              (*(undefined4 *)(param_1 + 0x13c),0,0,iVar8);
    SetExplanation__7CmdNoteFPCce(*(undefined4 *)(param_1 + 0x6c),*(undefined4 *)(iVar4 + 0x14));
    puVar3 = PTR_EnterDetail__15CmdPropertyListFv_0050dd68;
    uVar5 = DAT_0050dd64;
    if (*(short *)(param_1 + 0x16a) == 4) {
      *(undefined4 *)(param_1 + 0x58) = _5429;
      *(undefined4 *)(param_1 + 0x5c) = uVar5;
      *(undefined **)(param_1 + 0x60) = puVar3;
    }
    else {
      lVar6 = __nw__FUi(0x52c);
      uVar7 = 0;
      if (lVar6 != 0) {
        uVar7 = __ct__10CmdExplainFv(lVar6);
      }
      *(int *)(param_1 + 0x134) = (int)uVar7;
      Initialize__9MenuSceneFPUcP9BufMemory(uVar7,*(undefined4 *)(*(int *)(param_1 + 0x54) + 0x4c),0);
      SetInfo__10CmdExplainFP4MenusUcUc
                (uVar7,*(undefined4 *)(param_1 + 0x10),
                 *(undefined2 *)(*(int *)(param_1 + 0x13c) + 0x12a),3,0);
      SetIcon__10CmdExplainFP11MenuTexture(uVar7,0x421698);
      SetImage__10CmdExplainFPcss(uVar7,*(undefined4 *)(iVar4 + 0x10),1,0);
      puVar3 = PTR_ShiftExplain__15CmdPropertyListFv_0050dd78;
      uVar5 = DAT_0050dd74;
      *(undefined4 *)(param_1 + 0x58) = _5434;
      *(undefined4 *)(param_1 + 0x5c) = uVar5;
      *(undefined **)(param_1 + 0x60) = puVar3;
    }
    iVar8 = *(int *)(param_1 + 0x13c);
    Close__10MenuWindowFUci(iVar8,((ulong)*(byte *)(iVar8 + 0xb0) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar8 + 0x34) + 0x14));
    iVar8 = *(int *)(param_1 + 300);
    Close__10MenuWindowFUci(iVar8,((ulong)*(byte *)(iVar8 + 0xb0) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar8 + 0x34) + 0x14));
    iVar8 = *(int *)(param_1 + 0x74);
    Close__10MenuWindowFUci(iVar8 + 0x58,((ulong)*(byte *)(iVar8 + 0x108) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar8 + 0x8c) + 0x14));
    *(byte *)(*(int *)(param_1 + 0x18) + 0x12) = *(byte *)(*(int *)(param_1 + 0x18) + 0x12) & 0xfe;
    PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 100),2,0,0);
  }
  return 0;
}

/* JP: 0x0049d500  CmdPropertyList::ExecSort()   [ExecSort__15CmdPropertyListFv]  size=0x258 */
undefined8 ExecSort__15CmdPropertyListFv(int param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined *puVar5;
  long lVar6;
  undefined8 uVar7;
  
  iVar2 = *(int *)(param_1 + 0x130);
  iVar3 = *(int *)(param_1 + 0x13c);
  lVar6 = (**(code **)(*(int *)(iVar2 + 8) + 0x1c))();
  if (lVar6 != 0) {
    cVar1 = *(char *)(iVar2 + 0x20);
    if (cVar1 == '\x04') {
      Select__16CmdPropertyGoodsFP7CmdNoteP9MenuGroupP9MenuGroup
                (*(undefined4 *)(param_1 + 0x13c),*(undefined4 *)(param_1 + 0x6c),
                 *(undefined4 *)(iVar2 + 0x15c),0);
      *(byte *)(*(int *)(iVar3 + 0x44) + 0x12) = *(byte *)(*(int *)(iVar3 + 0x44) + 0x12) & 0xfe | 1
      ;
      (**(code **)(*(int *)(iVar2 + 8) + 0xc))();
      *(undefined4 *)(param_1 + 0x130) = 0;
      puVar5 = PTR_SelectGoods__15CmdPropertyListFv_0050dd98;
      uVar4 = DAT_0050dd94;
      *(undefined4 *)(param_1 + 0x58) = _5552;
      *(undefined4 *)(param_1 + 0x5c) = uVar4;
      *(undefined **)(param_1 + 0x60) = puVar5;
    }
    else if (cVar1 == '\r') {
      Open__15CmdButtonReportFv(*(undefined4 *)(param_1 + 0x74));
    }
    else if (cVar1 == '\x0f') {
      *(char *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x28c +
               (int)*(char *)(*(int *)(param_1 + 0x164) + 0xb)) =
           (char)*(undefined2 *)(iVar2 + 0x15a);
      UpdateScene__16CmdPropertyGoodsFP15CmdPropertyListss
                (*(undefined4 *)(param_1 + 0x13c),param_1,*(undefined2 *)(param_1 + 0x16a),
                 *(undefined2 *)(param_1 + 0x168));
      uVar7 = GetPlace__10MenuWindowFss(iVar3,0,0);
      Select__16CmdPropertyGoodsFP7CmdNoteP9MenuGroupP9MenuGroup
                (iVar3,0,uVar7,*(undefined4 *)(iVar2 + 0x15c));
      *(int *)(iVar2 + 0x15c) = (int)uVar7;
      Open__10MenuWindowFUci(iVar3,*(byte *)(iVar3 + 0xb0) & 7,
                      *(undefined4 *)(*(int *)(iVar3 + 0x34) + 0x10));
    }
  }
  return 0;
}

/* JP: 0x0049d760  CmdPropertyList::ShiftExplain()   [ShiftExplain__15CmdPropertyListFv]  size=0x134 */
undefined8 ShiftExplain__15CmdPropertyListFv(int param_1)

{
  bool bVar1;
  undefined4 uVar2;
  undefined *puVar3;
  
  puVar3 = PTR_SelectGoods__15CmdPropertyListFv_0050ddb8;
  uVar2 = DAT_0050ddb4;
  if ((*(char *)(*(int *)(param_1 + 0x13c) + 0xa8) == '\x01') ||
     (*(char *)(*(int *)(param_1 + 0x13c) + 0xa8) == '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if (bVar1) {
    if (*(char *)(*(int *)(param_1 + 0x13c) + 0xa8) == '\0') {
      SetExplanation__15CmdPropertyListFv(param_1);
      puVar3 = PTR_ExecExplain__15CmdPropertyListFv_0050dda8;
      uVar2 = DAT_0050dda4;
      *(undefined4 *)(param_1 + 0x58) = _5588;
      *(undefined4 *)(param_1 + 0x5c) = uVar2;
      *(undefined **)(param_1 + 0x60) = puVar3;
    }
    else {
      *(undefined4 *)(param_1 + 0x58) = _5591;
      *(undefined4 *)(param_1 + 0x5c) = uVar2;
      *(undefined **)(param_1 + 0x60) = puVar3;
    }
  }
  return 0;
}

/* JP: 0x0049d8a0  CmdPropertyList::ExecExplain()   [ExecExplain__15CmdPropertyListFv]  size=0x238 */
undefined8 ExecExplain__15CmdPropertyListFv(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined *puVar4;
  long lVar5;
  
  iVar1 = *(int *)(param_1 + 0x134);
  lVar5 = Exec__10CmdExplainFUs(iVar1,*(undefined2 *)(*(int *)(param_1 + 0x10) + 0x48));
  if ((lVar5 != 0) && ((int)lVar5 == 4)) {
    if ((long)((ulong)*(byte *)(iVar1 + 0x525) << 0x3d) < 0) {
      uVar2 = *(undefined4 *)(*(int *)(param_1 + 0x18) + 0xec);
      FinishScroll__10MenuWindowFv(*(undefined4 *)(param_1 + 0x13c));
      Select__16CmdPropertyGoodsFP7CmdNoteP9MenuGroupP9MenuGroup
                (*(undefined4 *)(param_1 + 0x13c),*(undefined4 *)(param_1 + 0x6c),uVar2,0);
      QuickMove__6CursorFv(*(undefined4 *)(param_1 + 0x18));
      ClearAfter__6CursorFv(*(undefined4 *)(param_1 + 0x18));
      *(byte *)(*(int *)(param_1 + 0x18) + 0x12) =
           *(byte *)(*(int *)(param_1 + 0x18) + 0x12) & 0xfe | 1;
      iVar3 = *(int *)(param_1 + 300);
      Open__10MenuWindowFUci(iVar3,*(byte *)(iVar3 + 0xb0) & 7,
                      *(undefined4 *)(*(int *)(iVar3 + 0x34) + 0x10));
      iVar3 = *(int *)(param_1 + 0x13c);
      Open__10MenuWindowFUci(iVar3,*(byte *)(iVar3 + 0xb0) & 7,
                      *(undefined4 *)(*(int *)(iVar3 + 0x34) + 0x10));
      Open__15CmdButtonReportFv(*(undefined4 *)(param_1 + 0x74));
      (**(code **)(*(int *)(iVar1 + 8) + 0xc))();
      *(undefined4 *)(param_1 + 0x134) = 0;
      puVar4 = PTR_ShiftExplain__15CmdPropertyListFv_0050ddc8;
      uVar2 = DAT_0050ddc4;
      *(undefined4 *)(param_1 + 0x58) = _5620;
      *(undefined4 *)(param_1 + 0x5c) = uVar2;
      *(undefined **)(param_1 + 0x60) = puVar4;
    }
    else {
      MoveCursor__6CursorFi(*(undefined4 *)(param_1 + 0x18),*(byte *)(iVar1 + 0x524) >> 4);
      SetExplanation__15CmdPropertyListFv(param_1);
    }
  }
  return 0;
}

/* JP: 0x0049dae0  CmdPropertyList::EnterDetail()   [EnterDetail__15CmdPropertyListFv]  size=0x250 */
undefined8 EnterDetail__15CmdPropertyListFv(int param_1)

{
  int iVar1;
  bool bVar2;
  undefined4 uVar3;
  undefined *puVar4;
  long lVar5;
  undefined8 uVar6;
  int iVar7;
  
  if ((*(char *)(*(int *)(param_1 + 0x13c) + 0xa8) == '\x01') ||
     (*(char *)(*(int *)(param_1 + 0x13c) + 0xa8) == '\0')) {
    bVar2 = true;
  }
  else {
    bVar2 = false;
  }
  if (bVar2) {
    iVar1 = *(int *)(*(int *)(param_1 + 0x18) + 0xec);
    lVar5 = __nw__FUi(0x1d68);
    uVar6 = 0;
    if (lVar5 != 0) {
      uVar6 = __ct__14CmdCrestDetailFv(lVar5);
    }
    iVar7 = (int)uVar6;
    *(int *)(param_1 + 0x138) = iVar7;
    CreateScene__14CmdCrestDetailFP9MenuSceneP11MenuTexture
              (uVar6,param_1 + 0xd0,*(int *)(param_1 + 300) + 0xb8);
    if (1 < *(short *)(*(int *)(param_1 + 0x13c) + 0x12a)) {
      CreateScrollMark__10MenuWindowFUc(uVar6,3);
      SetArea__10ScrollMarkFUcffff(0xbf800000,0xbf800000,*(float *)(iVar7 + 0x6c) + 2.0,
                      *(float *)(iVar7 + 0x70) + 2.0,*(undefined4 *)(iVar7 + 0x44),
                      *(undefined1 *)(iVar7 + 0xa9));
    }
    UpdateScene__14CmdCrestDetailFP9MenuSceneP8CmdPartyP13MenuDataMagics
              (uVar6,param_1 + 0xd0,*(undefined4 *)(param_1 + 0x68),*(undefined4 *)(param_1 + 0x160)
               ,*(undefined2 *)(iVar1 + 0x16));
    Open__10MenuWindowFUci(uVar6,*(byte *)(iVar7 + 0xb0) & 7,*(undefined4 *)(*(int *)(iVar7 + 0x34) + 0x10)
                   );
    puVar4 = PTR_ExecDetail__15CmdPropertyListFv_0050ddd8;
    uVar3 = DAT_0050ddd4;
    *(undefined4 *)(param_1 + 0x58) = _5659;
    *(undefined4 *)(param_1 + 0x5c) = uVar3;
    *(undefined **)(param_1 + 0x60) = puVar4;
  }
  return 0;
}

/* JP: 0x0049dd30  CmdPropertyList::ExitDetail()   [ExitDetail__15CmdPropertyListFv]  size=0x298 */
undefined8 ExitDetail__15CmdPropertyListFv(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  bool bVar3;
  undefined *puVar4;
  
  puVar4 = PTR_SelectGoods__15CmdPropertyListFv_0050dde8;
  uVar1 = DAT_0050dde4;
  if (*(char *)(param_1 + 0x21) == '\0') {
    if ((*(char *)(*(int *)(param_1 + 0x138) + 0xa8) == '\x01') ||
       (*(char *)(*(int *)(param_1 + 0x138) + 0xa8) == '\0')) {
      bVar3 = true;
    }
    else {
      bVar3 = false;
    }
    if (bVar3) {
      uVar1 = *(undefined4 *)(*(int *)(param_1 + 0x18) + 0xec);
      (**(code **)(*(int *)(*(int *)(param_1 + 0x138) + 8) + 0xc))();
      *(undefined4 *)(param_1 + 0x138) = 0;
      FinishScroll__10MenuWindowFv(*(undefined4 *)(param_1 + 0x13c));
      Select__16CmdPropertyGoodsFP7CmdNoteP9MenuGroupP9MenuGroup
                (*(undefined4 *)(param_1 + 0x13c),*(undefined4 *)(param_1 + 0x6c),uVar1,0);
      QuickMove__6CursorFv(*(undefined4 *)(param_1 + 0x18));
      ClearAfter__6CursorFv(*(undefined4 *)(param_1 + 0x18));
      *(byte *)(*(int *)(param_1 + 0x18) + 0x12) =
           *(byte *)(*(int *)(param_1 + 0x18) + 0x12) & 0xfe | 1;
      iVar2 = *(int *)(param_1 + 300);
      Open__10MenuWindowFUci(iVar2,*(byte *)(iVar2 + 0xb0) & 7,
                      *(undefined4 *)(*(int *)(iVar2 + 0x34) + 0x10));
      iVar2 = *(int *)(param_1 + 0x13c);
      Open__10MenuWindowFUci(iVar2,*(byte *)(iVar2 + 0xb0) & 7,
                      *(undefined4 *)(*(int *)(iVar2 + 0x34) + 0x10));
      Open__15CmdButtonReportFv(*(undefined4 *)(param_1 + 0x74));
      *(char *)(param_1 + 0x21) = *(char *)(param_1 + 0x21) + '\x01';
    }
  }
  else if (*(char *)(param_1 + 0x21) == '\x01') {
    if ((*(char *)(*(int *)(param_1 + 300) + 0xa8) == '\x01') ||
       (*(char *)(*(int *)(param_1 + 300) + 0xa8) == '\0')) {
      bVar3 = true;
    }
    else {
      bVar3 = false;
    }
    if (bVar3) {
      *(undefined4 *)(param_1 + 0x58) = _5702;
      *(undefined4 *)(param_1 + 0x5c) = uVar1;
      *(undefined **)(param_1 + 0x60) = puVar4;
      *(undefined1 *)(param_1 + 0x21) = 0;
    }
  }
  return 0;
}

/* JP: 0x0049dfd0  CmdPropertyList::ExecDetail()   [ExecDetail__15CmdPropertyListFv]  size=0x230 */
undefined8 ExecDetail__15CmdPropertyListFv(int param_1)

{
  int iVar1;
  bool bVar2;
  undefined4 uVar3;
  undefined *puVar4;
  int iVar5;
  
  if ((*(ushort *)(*(int *)(param_1 + 0x10) + 0x48) & 0x5000) == 0) {
    if (*(int *)(*(int *)(param_1 + 0x138) + 0x44) != 0) {
      if ((*(char *)(*(int *)(param_1 + 0x138) + 0xa8) == '\x01') ||
         (*(char *)(*(int *)(param_1 + 0x138) + 0xa8) == '\0')) {
        bVar2 = true;
      }
      else {
        bVar2 = false;
      }
      if (bVar2) {
        iVar1 = *(int *)(*(int *)(param_1 + 0x18) + 0xec);
        iVar5 = MoveVertical__9MenuSceneFi(param_1,0);
        if (iVar1 != iVar5) {
          UpdateScene__14CmdCrestDetailFP9MenuSceneP8CmdPartyP13MenuDataMagics
                    (*(undefined4 *)(param_1 + 0x138),param_1 + 0xd0,*(undefined4 *)(param_1 + 0x68)
                     ,*(undefined4 *)(param_1 + 0x160),*(undefined2 *)(iVar5 + 0x16));
          iVar1 = *(int *)(param_1 + 0x138);
          Open__10MenuWindowFUci(iVar1,*(byte *)(iVar1 + 0xb0) & 7,
                          *(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x10));
          PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 100),6,0,0);
        }
      }
    }
  }
  else {
    iVar1 = *(int *)(param_1 + 0x138);
    Close__10MenuWindowFUci(iVar1,((ulong)*(byte *)(iVar1 + 0xb0) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x14));
    puVar4 = PTR_ExitDetail__15CmdPropertyListFv_0050ddf8;
    uVar3 = DAT_0050ddf4;
    *(undefined4 *)(param_1 + 0x58) = _5745;
    *(undefined4 *)(param_1 + 0x5c) = uVar3;
    *(undefined **)(param_1 + 0x60) = puVar4;
    PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 100),3,0,0);
  }
  return 0;
}
