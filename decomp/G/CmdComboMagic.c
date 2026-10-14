/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdComboMagic   functions: 8
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdComboMagic.md).
 */

/* JP: 0x0048c130  CmdComboMagic::CmdComboMagic()   [__ct__13CmdComboMagicFv]  size=0x94 */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __ct__13CmdComboMagicFv(int param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  __ct__9MenuSceneFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__13CmdComboMagic;
  uVar2 = uRam004236d0;
  uVar1 = uRam004236cc;
  *(undefined4 *)(param_1 + 0x58) = ___ptmf_null;
  *(undefined4 *)(param_1 + 0x5c) = uVar1;
  *(undefined4 *)(param_1 + 0x60) = uVar2;
  __ct__8FontDrawFv(param_1 + 0x68);
  __ct__10MenuWindowFv(param_1 + 0xa8);
  *(undefined4 *)(param_1 + 0x15c) = 0;
  *(undefined4 *)(param_1 + 0x160) = 0;
  return param_1;
}

/* JP: 0x0048c1d0  CmdComboMagic::~CmdComboMagic()   [__dt__13CmdComboMagicFv]  size=0xec */
int __dt__13CmdComboMagicFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__13CmdComboMagic;
    if (*(int *)(param_1 + 0x15c) != 0) {
      __destroy_new_array(*(undefined4 *)(param_1 + 0x15c),0x450670);
    }
    if (*(int *)(param_1 + 0x160) != 0) {
      (**(code **)(*(int *)(*(int *)(param_1 + 0x160) + 8) + 0xc))();
    }
    __dt__10MenuWindowFv(param_1 + 0xa8,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x68,0xffffffffffffffff);
    __dt__9MenuSceneFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x0048c2c0  CmdComboMagic::GetReady()   [GetReady__13CmdComboMagicFv]  size=0x7b0 */
undefined4 GetReady__13CmdComboMagicFv(int param_1)

{
  bool bVar1;
  ushort uVar2;
  undefined *puVar3;
  undefined2 uVar4;
  undefined4 uVar5;
  undefined8 uVar6;
  long lVar7;
  int iVar8;
  uint uVar9;
  short sVar10;
  char *pcVar11;
  undefined1 auStack_120 [32];
  undefined1 auStack_100 [96];
  undefined4 *puStack_a0;
  int iStack_9c;
  int iStack_98;
  int iStack_94;
  int iStack_90;
  float fStack_8c;
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined4 uStack_80;
  uint uStack_7c;
  uint uStack_78;
  int iStack_74;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  int iStack_68;
  int iStack_64;
  int iStack_60;
  int iStack_5c;
  int iStack_58;
  int iStack_54;
  int iStack_50;
  int iStack_4c;
  undefined4 *puStack_48;
  undefined4 *puStack_44;
  int iStack_40;
  int iStack_3c;
  int iStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  int iStack_28;
  int iStack_24;
  undefined4 uStack_20;
  float fStack_1c;
  uint uStack_18;
  int iStack_14;
  int iStack_10;
  
  iStack_10 = param_1;
  __ct__9MenuSceneFv(auStack_100);
  puStack_44 = (undefined4 *)(*(int *)(iStack_10 + 0x54) + 0x1c);
  Convert__13MenuDataTableFPUci(*puStack_44,0);
  puStack_48 = (undefined4 *)(*(int *)(iStack_10 + 0x54) + 0x28);
  Convert__13MenuDataTableFPUci(*puStack_48,0);
  iStack_60 = *(int *)(iStack_10 + 0x10);
  iStack_4c = iStack_60 + 0xb8;
  *(int *)(iStack_10 + 0x174) = iStack_4c;
  iStack_50 = iStack_60 + 0x4e0;
  *(int *)(iStack_10 + 0x178) = iStack_50;
  iStack_54 = iStack_60 + 0xa60;
  *(int *)(iStack_10 + 0x180) = iStack_54;
  iStack_58 = iStack_60 + 0x780;
  *(int *)(iStack_10 + 0x17c) = iStack_58;
  iStack_5c = iStack_60 + 0x10f0;
  *(int *)(iStack_10 + 0x184) = iStack_5c;
  iStack_60 = iStack_60 + 0x28;
  iStack_24 = iStack_60;
  iStack_68 = Find__13MenuDataTableFs(iStack_60,0xd);
  iStack_64 = iStack_68;
  iStack_14 = iStack_68;
  uVar4 = GetRegCnt__9RegDatApiFii(0x39,0xffffffffffffffff);
  *(undefined2 *)(iStack_10 + 0x16a) = uVar4;
  *(int *)(iStack_10 + 0x16c) = iStack_14 + 0x10;
  uVar5 = GetRegDat__9RegDatApiFiii(0x39,0,0xffffffffffffffff);
  *(undefined4 *)(iStack_10 + 0x170) = uVar5;
  uStack_6c = sm_pSound__7MenuObj;
  *(undefined4 *)(iStack_10 + 100) = sm_pSound__7MenuObj;
  uVar2 = *(ushort *)(iStack_10 + 0x16a);
  uVar6 = __nwa__FUi((uint)uVar2 * 0x150 + 0x10);
  uStack_70 = __construct_new_array(uVar6,0x454640,0x450670,0x150,uVar2);
  *(undefined4 *)(iStack_10 + 0x15c) = uStack_70;
  SetData__9MenuSceneFUsP8FontDraw(iStack_10,0,iStack_10 + 0x68);
  AddPriority__12MenuObjTableFP7MenuObj(iStack_10 + 0xc0,iStack_10 + 0x68);
  iVar8 = *(int *)(iStack_10 + 0x15c);
  iStack_74 = *(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x300;
  pcVar11 = (char *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x340);
  iStack_28 = *(int *)(iStack_10 + 0x174);
  uStack_7c = *(uint *)(*(int *)(iStack_28 + 4) + 0xd44);
  fStack_1c = 0.0;
  sVar10 = 0;
  uStack_78 = uStack_7c;
  uStack_18 = uStack_7c;
  for (uVar9 = 0; uVar9 < *(ushort *)(iStack_10 + 0x16a); uVar9 = uVar9 + 1 & 0xffff) {
    if (*pcVar11 != '\0') {
      SetData__9MenuSceneFUsP8MenuText(iStack_10,0,iVar8 + 0x50);
      SetData__9MenuSceneFUsP8MenuText(iStack_10,1,iVar8 + 0xd0);
      AddPlace__9MenuGroupFP9MenuPlace(iVar8,iVar8 + 0x50);
      AddPlace__9MenuGroupFP9MenuPlace(iVar8,iVar8 + 0xd0);
      bVar1 = (uStack_18 & 1 << (uVar9 & 0x1f)) == 0;
      if (bVar1) {
        uStack_84 = *(undefined4 *)(*(int *)(iStack_10 + 0x24) + 0x10);
        uStack_30 = uStack_84;
        SetMessage__8MenuTextFPcUiUcUc(iVar8 + 0x50,uStack_84,*(byte *)(iVar8 + 0xa8) & 7,0,1);
        OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_10 + 0x68,iVar8 + 0x50,((ulong)*(byte *)(iVar8 + 0xa8) & 0xf) >> 3,0)
        ;
        uStack_88 = *(undefined4 *)(*(int *)(iStack_10 + 0x24) + 0x18);
        uStack_34 = uStack_88;
        SetMessage__8MenuTextFPcUiUcUc(iVar8 + 0xd0,uStack_88,*(byte *)(iVar8 + 0x128) & 7,0,1);
        OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_10 + 0x68,iVar8 + 0xd0,((ulong)*(byte *)(iVar8 + 0x128) & 0xf) >> 3,0
                       );
      }
      else {
        uStack_2c = GetRegDat__9RegDatApiFiii(0xf,uVar9,0xffffffffffffffff);
        SetMessage__8MenuTextFPcUiUcUc(iVar8 + 0x50,uStack_2c,*(byte *)(iVar8 + 0xa8) & 7,0,1);
        OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_10 + 0x68,iVar8 + 0x50,((ulong)*(byte *)(iVar8 + 0xa8) & 0xf) >> 3,0)
        ;
        uStack_80 = *(undefined4 *)(*(int *)(iStack_10 + 0x24) + 0x28);
        sprintf(auStack_120,uStack_80,
                        *(undefined2 *)(*(int *)(iStack_10 + 0x170) + uVar9 * 0x40 + 0x1e));
        SetMessage__8MenuTextFPcUiUcUc(iVar8 + 0xd0,auStack_120,*(byte *)(iVar8 + 0x128) & 7,0,1);
        OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_10 + 0x68,iVar8 + 0xd0,((ulong)*(byte *)(iVar8 + 0x128) & 0xf) >> 3,0
                       );
      }
      SetData__9MenuSceneFUsP9MenuGroup(iStack_10,0,iVar8);
      *(short *)(iVar8 + 0x16) = (short)uVar9;
      *(ushort *)(iVar8 + 0x22) = (ushort)bVar1;
      *(undefined2 *)(iVar8 + 0x1c) = 0;
      *(short *)(iVar8 + 0x1e) = sVar10;
      (**(code **)(*(int *)(iVar8 + 8) + 0x24))(0,fStack_1c);
      AddPlace__10MenuWindowFP9MenuPlace(iStack_10 + 0xa8,iVar8);
      sVar10 = sVar10 + 1;
      fStack_8c = *(float *)(iVar8 + 0x30);
      fStack_1c = fStack_1c + fStack_8c;
    }
    iVar8 = iVar8 + 0x150;
    pcVar11 = pcVar11 + 1;
  }
  ClearReport__15CmdButtonReportFv(*(undefined4 *)(iStack_10 + 0x180));
  *(byte *)(iStack_10 + 0x23) = *(byte *)(iStack_10 + 0x23) & 0x3f;
  if (1 < sVar10) {
    *(byte *)(iStack_10 + 0x23) = *(byte *)(iStack_10 + 0x23) & 0x3f | 0x80;
  }
  SetData__9MenuSceneFUsP10MenuWindow(iStack_10,0,iStack_10 + 0xa8);
  AddOT__7MenuObjFv(iStack_10 + 0xa8);
  iStack_38 = *(int *)(iStack_10 + 0x10);
  iStack_94 = iStack_38 + 0x348;
  iStack_9c = iStack_38 + 0x3a0;
  *(int *)(iStack_10 + 0x18) = iStack_9c;
  iStack_40 = *(int *)(iStack_10 + 0x18);
  iStack_98 = iStack_9c;
  iStack_90 = iStack_94;
  iStack_3c = iStack_94;
  if (-1 < (long)((ulong)*(byte *)(iStack_40 + 0x12) << 0x3d)) {
    AddOT__7MenuObjFv(*(undefined4 *)(iStack_10 + 0x18));
  }
  uVar6 = GetPlace__10MenuWindowFss(iStack_10 + 0xa8,0,0);
  Select__6CursorFP9MenuPlace(*(undefined4 *)(iStack_10 + 0x18),uVar6);
  SelectGoods__13CmdComboMagicFP9MenuGroupP9MenuGroupb(iStack_10,uVar6,0,1);
  puStack_a0 = (undefined4 *)(*(int *)(iStack_10 + 0x54) + 0x1c);
  Initialize__9MenuSceneFPUcP9BufMemory(auStack_100,*puStack_a0,0);
  lVar7 = __nw__FUi(0x178);
  uVar5 = 0;
  if (lVar7 != 0) {
    uVar5 = __ct__8CmdFenceFv(lVar7);
  }
  *(undefined4 *)(iStack_10 + 0x160) = uVar5;
  CreateFence__8CmdFenceFP9MenuScenePUc(*(undefined4 *)(iStack_10 + 0x160),auStack_100,0);
  puVar3 = PTR_Enter__13CmdComboMagicFv_0050db18;
  uVar5 = DAT_0050db14;
  *(undefined4 *)(iStack_10 + 0x58) = _5005;
  *(undefined4 *)(iStack_10 + 0x5c) = uVar5;
  *(undefined **)(iStack_10 + 0x60) = puVar3;
  uStack_20 = 1;
  __dt__9MenuSceneFv(auStack_100,0xffffffffffffffff);
  return uStack_20;
}

/* JP: 0x0048ca70  CmdComboMagic::Run()   [Run__13CmdComboMagicFv]  size=0x5c */
undefined8 Run__13CmdComboMagicFv(int param_1)

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

/* JP: 0x0048cad0  CmdComboMagic::Enter()   [Enter__13CmdComboMagicFv]  size=0x1f4 */
undefined4 Enter__13CmdComboMagicFv(int param_1)

{
  int iVar1;
  bool bVar2;
  undefined4 uVar3;
  undefined *puVar4;
  undefined1 uVar5;
  
  if (*(char *)(param_1 + 0x21) == '\0') {
    Open__10MenuWindowFUci(param_1 + 0xa8,*(byte *)(param_1 + 0x158) & 7,
                    *(undefined4 *)(*(int *)(param_1 + 0xdc) + 0x10));
    iVar1 = *(int *)(param_1 + 0x160);
    Open__10MenuWindowFUci(iVar1,*(byte *)(iVar1 + 0xb0) & 7,*(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x10)
                   );
    Open__15CmdButtonReportFv(*(undefined4 *)(param_1 + 0x180));
    SetTitle__11CmdTitleLogFPUci
              (*(undefined4 *)(param_1 + 0x17c),*(undefined4 *)(*(int *)(param_1 + 0x54) + 0x10),4);
    Open__11CmdTitleLogFv(*(undefined4 *)(param_1 + 0x17c));
    uVar5 = CreateBackGround__7CmdMenuFs(*(undefined4 *)(param_1 + 0x10),8);
    *(undefined1 *)(param_1 + 0x20) = uVar5;
    *(char *)(param_1 + 0x21) = *(char *)(param_1 + 0x21) + '\x01';
  }
  else if (*(char *)(param_1 + 0x21) == '\x01') {
    if ((*(char *)(param_1 + 0x150) == '\x01') || (*(char *)(param_1 + 0x150) == '\0')) {
      bVar2 = true;
    }
    else {
      bVar2 = false;
    }
    if (bVar2) {
      if (*(char *)(param_1 + 0x20) != '\0') {
        DestroyBackGround__7CmdMenuFs(*(undefined4 *)(param_1 + 0x10),1);
        *(undefined1 *)(param_1 + 0x20) = 0;
      }
      puVar4 = PTR_Exec__13CmdComboMagicFv_0050db28;
      uVar3 = DAT_0050db24;
      *(undefined4 *)(param_1 + 0x58) = _5125;
      *(undefined4 *)(param_1 + 0x5c) = uVar3;
      *(undefined **)(param_1 + 0x60) = puVar4;
      *(undefined1 *)(param_1 + 0x21) = 0;
      return 1;
    }
  }
  return 0;
}

/* JP: 0x0048ccd0  CmdComboMagic::Exit()   [Exit__13CmdComboMagicFv]  size=0x238 */
undefined8 Exit__13CmdComboMagicFv(int param_1)

{
  int iVar1;
  bool bVar2;
  
  if (*(char *)(param_1 + 0x21) == '\0') {
    (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x14) + 0x28))
              (*(int *)(param_1 + 0x10),0,0,0xe);
    Close__10MenuWindowFUci(param_1 + 0xa8,((ulong)*(byte *)(param_1 + 0x158) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(param_1 + 0xdc) + 0x14));
    iVar1 = *(int *)(param_1 + 0x160);
    Close__10MenuWindowFUci(iVar1,((ulong)*(byte *)(iVar1 + 0xb0) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x14));
    iVar1 = *(int *)(param_1 + 0x17c);
    Close__10MenuWindowFUci(iVar1 + 0x58,((ulong)*(byte *)(iVar1 + 0x108) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar1 + 0x8c) + 0x14));
    iVar1 = *(int *)(param_1 + 0x180);
    Close__10MenuWindowFUci(iVar1 + 0x58,((ulong)*(byte *)(iVar1 + 0x108) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar1 + 0x8c) + 0x14));
    Close__10CmdElementFv(*(undefined4 *)(param_1 + 0x184));
    Leave__6CursorFv(*(undefined4 *)(param_1 + 0x18));
    *(undefined1 *)(*(int *)(param_1 + 0x18) + 0xf8) = 1;
    *(char *)(param_1 + 0x21) = *(char *)(param_1 + 0x21) + '\x01';
  }
  else if (*(char *)(param_1 + 0x21) == '\x01') {
    if ((*(char *)(param_1 + 0x150) == '\x01') || (*(char *)(param_1 + 0x150) == '\0')) {
      bVar2 = true;
    }
    else {
      bVar2 = false;
    }
    if (bVar2) {
      ReleaseOT__7MenuObjFv(param_1 + 0xa8);
      ClearReport__15CmdButtonReportFv(*(undefined4 *)(param_1 + 0x180));
      (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x14) + 0x24))(*(int *)(param_1 + 0x10),0);
      DestroyScene__4MenuFP9MenuSceneb(*(undefined4 *)(param_1 + 0x10),param_1,1);
    }
  }
  return 0;
}

/* JP: 0x0048cf10  CmdComboMagic::Exec()   [Exec__13CmdComboMagicFv]  size=0x140 */
undefined8 Exec__13CmdComboMagicFv(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined *puVar3;
  int iVar4;
  
  puVar3 = PTR_Exit__13CmdComboMagicFv_0050db38;
  uVar2 = DAT_0050db34;
  iVar1 = *(int *)(*(int *)(param_1 + 0x18) + 0xec);
  if ((*(ushort *)(*(int *)(param_1 + 0x10) + 0x48) & 0x4000) == 0) {
    iVar4 = MoveVertical__9MenuSceneFi(param_1,1);
    if (iVar1 != iVar4) {
      SelectGoods__13CmdComboMagicFP9MenuGroupP9MenuGroupb(param_1,iVar4,iVar1,1);
      PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 100),0,0,0);
    }
  }
  else {
    *(undefined4 *)(param_1 + 0x58) = _5178;
    *(undefined4 *)(param_1 + 0x5c) = uVar2;
    *(undefined **)(param_1 + 0x60) = puVar3;
    PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 100),3,0,0);
  }
  return 0;
}

/* JP: 0x0048d050  CmdComboMagic::SelectGoods(MenuGroup*, MenuGroup*, bool)   [SelectGoods__13CmdComboMagicFP9MenuGroupP9MenuGroupb]  size=0x258 */
int SelectGoods__13CmdComboMagicFP9MenuGroupP9MenuGroupb
              (int param_1,int param_2,int param_3,char param_4)

{
  short sVar1;
  short sVar2;
  undefined4 uVar3;
  int iVar4;
  
  if (param_3 != 0) {
    iVar4 = *(int *)(param_1 + 0x15c) + *(short *)(param_3 + 0x16) * 0x150;
    SetCSA__8FontItemFUc(iVar4 + 0x50,0);
    SetCSA__8FontItemFUc(iVar4 + 0xd0,0);
  }
  if (param_2 != 0) {
    sVar1 = *(short *)(param_2 + 0x16);
    sVar2 = *(short *)(param_2 + 0x22);
    iVar4 = *(int *)(param_1 + 0x15c) + sVar1 * 0x150;
    SetCSA__8FontItemFUc(iVar4 + 0x50,1);
    SetCSA__8FontItemFUc(iVar4 + 0xd0,1);
    if (param_4 != '\0') {
      if (sVar2 == 0) {
        uVar3 = GetRegDat__9RegDatApiFiii(0x20,sVar1,0xffffffffffffffff);
      }
      else {
        uVar3 = *(undefined4 *)(*(int *)(param_1 + 0x24) + 0x10);
      }
      SetExplanation__7CmdNoteFPCce(*(undefined4 *)(param_1 + 0x178),uVar3);
    }
    if (sVar2 == 0) {
      Create__10CmdElementFUc
                (*(undefined4 *)(param_1 + 0x184),
                 *(byte *)(*(int *)(param_1 + 0x170) + sVar1 * 0x40 + 4) & 7);
      if ((*(byte *)(*(int *)(param_1 + 0x184) + 0x6a) & 1) == 0) {
        Open__10CmdElementFv(*(undefined4 *)(param_1 + 0x184));
      }
    }
    else {
      *(byte *)(*(int *)(param_1 + 0x184) + 0x6a) =
           *(byte *)(*(int *)(param_1 + 0x184) + 0x6a) & 0xfe;
    }
  }
  return param_2;
}
