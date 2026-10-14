/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdItem   functions: 14
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdItem.md).
 */

/* JP: 0x004402f0  CmdItem::CmdItem()   [__ct__7CmdItemFv]  size=0x7c */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __ct__7CmdItemFv(int param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  __ct__9MenuSceneFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__7CmdItem;
  uVar2 = uRam004236d0;
  uVar1 = uRam004236cc;
  *(undefined4 *)(param_1 + 0x58) = ___ptmf_null;
  *(undefined4 *)(param_1 + 0x5c) = uVar1;
  *(undefined4 *)(param_1 + 0x60) = uVar2;
  *(undefined4 *)(param_1 + 100) = 0;
  *(undefined4 *)(param_1 + 0x68) = 0;
  *(undefined4 *)(param_1 + 0x6c) = 0;
  return param_1;
}

/* JP: 0x00440370  CmdItem::~CmdItem()   [__dt__7CmdItemFv]  size=0xec */
int __dt__7CmdItemFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__7CmdItem;
    if (*(int *)(param_1 + 0x68) != 0) {
      (**(code **)(*(int *)(*(int *)(param_1 + 0x68) + 8) + 0xc))();
    }
    if (*(int *)(param_1 + 100) != 0) {
      (**(code **)(*(int *)(*(int *)(param_1 + 100) + 8) + 0xc))();
    }
    if (*(int *)(param_1 + 0x6c) != 0) {
      (**(code **)(*(int *)(*(int *)(param_1 + 0x6c) + 8) + 0xc))();
    }
    __dt__9MenuSceneFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x00440460  CmdItem::GetReady()   [GetReady__7CmdItemFv]  size=0x430 */
undefined4 GetReady__7CmdItemFv(int param_1)

{
  int iVar1;
  undefined *puVar2;
  undefined4 uVar3;
  long lVar4;
  undefined8 uVar5;
  uint uVar6;
  undefined1 auStack_b0 [88];
  undefined4 *puStack_58;
  char *pcStack_54;
  char *pcStack_50;
  int iStack_4c;
  int iStack_48;
  int iStack_44;
  undefined4 uStack_40;
  int iStack_3c;
  int iStack_38;
  int iStack_34;
  int iStack_30;
  int iStack_2c;
  int iStack_28;
  int iStack_24;
  int iStack_20;
  int iStack_1c;
  int iStack_18;
  int iStack_14;
  int iStack_10;
  
  iVar1 = *(int *)(param_1 + 0x10);
  iStack_24 = iVar1 + 0xb8;
  *(int *)(param_1 + 0x8c) = iStack_24;
  iStack_28 = iVar1 + 0x4e0;
  *(int *)(param_1 + 0x90) = iStack_28;
  iStack_2c = iVar1 + 0xa60;
  *(int *)(param_1 + 0x98) = iStack_2c;
  iStack_30 = iVar1 + 0x780;
  *(int *)(param_1 + 0x94) = iStack_30;
  iStack_34 = iVar1 + 0x28;
  iStack_14 = iStack_34;
  iStack_10 = param_1;
  iStack_3c = Find__13MenuDataTableFs(iStack_34,0xb);
  *(int *)(iStack_10 + 0x84) = iStack_3c + 0x10;
  *(short *)(iStack_10 + 0x82) = (short)*(undefined4 *)(iStack_3c + 8);
  iStack_38 = iStack_3c;
  uVar3 = GetRegDat__9RegDatApiFiii(0x33,0,0xffffffffffffffff);
  *(undefined4 *)(iStack_10 + 0x88) = uVar3;
  uStack_40 = sm_pSound__7MenuObj;
  *(undefined4 *)(iStack_10 + 0x9c) = sm_pSound__7MenuObj;
  iStack_44 = iVar1 + 0x348;
  iStack_4c = iVar1 + 0x3a0;
  *(int *)(iStack_10 + 0x18) = iStack_4c;
  iStack_1c = *(int *)(iStack_10 + 0x18);
  *(byte *)(iStack_1c + 0xfb) = *(byte *)(iStack_1c + 0xfb) & 0xfb;
  for (uVar6 = 0; uVar6 < *(ushort *)(iStack_10 + 0x82); uVar6 = uVar6 + 1 & 0xffff) {
    iStack_20 = *(int *)(iStack_10 + 0x8c);
    pcStack_54 = (char *)(*(int *)(iStack_20 + 8) + uVar6);
    pcStack_50 = pcStack_54;
    if (*pcStack_54 != '\0') break;
  }
  iStack_48 = iStack_4c;
  iStack_18 = iStack_44;
  if (uVar6 == *(ushort *)(iStack_10 + 0x82)) {
    lVar4 = __nw__FUi(0x268);
    uVar3 = 0;
    if (lVar4 != 0) {
      uVar3 = __ct__14CmdItemMessageFv(lVar4);
    }
    *(undefined4 *)(iStack_10 + 0x6c) = uVar3;
    CreateScene__14CmdItemMessageFP7CmdItem(*(undefined4 *)(iStack_10 + 0x6c),iStack_10);
    *(undefined4 *)(iStack_10 + 0x70) = *(undefined4 *)(iStack_10 + 0x6c);
  }
  else {
    __ct__9MenuSceneFv(auStack_b0);
    for (uVar6 = 1; (int)uVar6 < 5; uVar6 = uVar6 + 1) {
      puStack_58 = (undefined4 *)((uVar6 & 0xffff) * 0xc + *(int *)(iStack_10 + 0x54) + 0x10);
      Convert__13MenuDataTableFPUci(*puStack_58,0);
    }
    lVar4 = __nw__FUi(0x128);
    uVar3 = 0;
    if (lVar4 != 0) {
      uVar3 = __ct__12CmdItemGoodsFv(lVar4);
    }
    *(undefined4 *)(iStack_10 + 0x68) = uVar3;
    CreateScene__12CmdItemGoodsFP7CmdItem(*(undefined4 *)(iStack_10 + 0x68),iStack_10);
    *(undefined4 *)(iStack_10 + 0x70) = *(undefined4 *)(iStack_10 + 0x68);
    Initialize__9MenuSceneFPUcP9BufMemory(auStack_b0,*(undefined4 *)(*(int *)(iStack_10 + 0x54) + 0x40),0);
    lVar4 = __nw__FUi(0x178);
    uVar3 = 0;
    if (lVar4 != 0) {
      uVar3 = __ct__8CmdFenceFv(lVar4);
    }
    *(undefined4 *)(iStack_10 + 100) = uVar3;
    CreateFence__8CmdFenceFP9MenuScenePUc(*(undefined4 *)(iStack_10 + 100),auStack_b0,0);
    uVar5 = GetPlace__10MenuWindowFss(*(undefined4 *)(iStack_10 + 0x68),0,0);
    Select__6CursorFP9MenuPlace(*(undefined4 *)(iStack_10 + 0x18),uVar5);
    Select__12CmdItemGoodsFP7CmdNoteP9MenuGroupP9MenuGroup
              (*(undefined4 *)(iStack_10 + 0x68),*(undefined4 *)(iStack_10 + 0x90),uVar5,0);
    __dt__9MenuSceneFv(auStack_b0,0xffffffffffffffff);
  }
  puVar2 = PTR_Enter__7CmdItemFv_0050d218;
  uVar3 = DAT_0050d214;
  *(undefined4 *)(iStack_10 + 0x58) = _5041;
  *(undefined4 *)(iStack_10 + 0x5c) = uVar3;
  *(undefined **)(iStack_10 + 0x60) = puVar2;
  return 1;
}

/* JP: 0x00440890  CmdItem::Run()   [Run__7CmdItemFv]  size=0x5c */
undefined8 Run__7CmdItemFv(int param_1)

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

/* JP: 0x004408f0  CmdItem::Enter()   [Enter__7CmdItemFv]  size=0x28c */
undefined8 Enter__7CmdItemFv(int param_1)

{
  int iVar1;
  bool bVar2;
  undefined4 uVar3;
  undefined *puVar4;
  undefined4 uVar5;
  undefined *puVar6;
  undefined1 uVar7;
  
  if (*(char *)(param_1 + 0x21) == '\0') {
    if (*(int *)(param_1 + 0x68) == 0) {
      Shutdown__6CursorFv(*(undefined4 *)(param_1 + 0x18));
    }
    else {
      Open__15CmdButtonReportFv(*(undefined4 *)(param_1 + 0x98));
      iVar1 = *(int *)(param_1 + 100);
      Open__10MenuWindowFUci(iVar1,*(byte *)(iVar1 + 0xb0) & 7,
                      *(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x10));
    }
    iVar1 = *(int *)(param_1 + 0x70);
    Open__10MenuWindowFUci(iVar1,*(byte *)(iVar1 + 0xb0) & 7,*(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x10)
                   );
    SetTitle__11CmdTitleLogFPUci
              (*(undefined4 *)(param_1 + 0x94),*(undefined4 *)(*(int *)(param_1 + 0x54) + 0x10),1);
    Open__11CmdTitleLogFv(*(undefined4 *)(param_1 + 0x94));
    uVar7 = CreateBackGround__7CmdMenuFs(*(undefined4 *)(param_1 + 0x10),8);
    *(undefined1 *)(param_1 + 0x20) = uVar7;
    *(char *)(param_1 + 0x21) = *(char *)(param_1 + 0x21) + '\x01';
  }
  else if (*(char *)(param_1 + 0x21) == '\x01') {
    if ((*(char *)(*(int *)(param_1 + 0x70) + 0xa8) == '\x01') ||
       (*(char *)(*(int *)(param_1 + 0x70) + 0xa8) == '\0')) {
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
      *(byte *)(*(int *)(param_1 + 0x18) + 0xfb) =
           *(byte *)(*(int *)(param_1 + 0x18) + 0xfb) & 0xfb | 4;
      puVar6 = PTR_ExecMessage__7CmdItemFv_0050d238;
      uVar5 = DAT_0050d234;
      puVar4 = PTR_Exec__7CmdItemFv_0050d228;
      uVar3 = DAT_0050d224;
      if (*(int *)(param_1 + 0x68) == 0) {
        *(undefined4 *)(param_1 + 0x58) = _5118;
        *(undefined4 *)(param_1 + 0x5c) = uVar5;
        *(undefined **)(param_1 + 0x60) = puVar6;
      }
      else {
        *(undefined4 *)(param_1 + 0x58) = _5115;
        *(undefined4 *)(param_1 + 0x5c) = uVar3;
        *(undefined **)(param_1 + 0x60) = puVar4;
      }
      *(undefined1 *)(param_1 + 0x21) = 0;
    }
  }
  return 0;
}

/* JP: 0x00440b80  CmdItem::Exit()   [Exit__7CmdItemFv]  size=0x280 */
undefined8 Exit__7CmdItemFv(int param_1)

{
  int iVar1;
  bool bVar2;
  
  if (*(char *)(param_1 + 0x21) == '\0') {
    (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x14) + 0x28))(*(int *)(param_1 + 0x10),0,0,0);
    iVar1 = *(int *)(param_1 + 0x70);
    Close__10MenuWindowFUci(iVar1,((ulong)*(byte *)(iVar1 + 0xb0) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x14));
    iVar1 = *(int *)(param_1 + 0x94);
    Close__10MenuWindowFUci(iVar1 + 0x58,((ulong)*(byte *)(iVar1 + 0x108) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar1 + 0x8c) + 0x14));
    if (*(int *)(param_1 + 100) != 0) {
      iVar1 = *(int *)(param_1 + 100);
      Close__10MenuWindowFUci(iVar1,((ulong)*(byte *)(iVar1 + 0xb0) & 0x3f) >> 3,
                      *(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x14));
    }
    if (*(char *)(*(int *)(param_1 + 0x98) + 0x100) != '\0') {
      iVar1 = *(int *)(param_1 + 0x98);
      Close__10MenuWindowFUci(iVar1 + 0x58,((ulong)*(byte *)(iVar1 + 0x108) & 0x3f) >> 3,
                      *(undefined4 *)(*(int *)(iVar1 + 0x8c) + 0x14));
    }
    Leave__6CursorFv(*(undefined4 *)(param_1 + 0x18));
    *(undefined1 *)(*(int *)(param_1 + 0x18) + 0xf8) = 1;
    *(char *)(param_1 + 0x21) = *(char *)(param_1 + 0x21) + '\x01';
  }
  else if (*(char *)(param_1 + 0x21) == '\x01') {
    if ((*(char *)(*(int *)(param_1 + 0x70) + 0xa8) == '\x01') ||
       (*(char *)(*(int *)(param_1 + 0x70) + 0xa8) == '\0')) {
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

/* JP: 0x00440e00  CmdItem::Exec()   [Exec__7CmdItemFv]  size=0x668 */
undefined8 Exec__7CmdItemFv(int param_1)

{
  ushort uVar1;
  undefined *puVar2;
  undefined4 uVar3;
  undefined *puVar4;
  undefined2 uVar5;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  long lVar9;
  undefined8 uVar10;
  int iVar11;
  int iVar12;
  
  puVar4 = PTR_Exit__7CmdItemFv_0050d278;
  uVar3 = DAT_0050d274;
  puVar2 = PTR_EnterExplain__7CmdItemFv_0050d268;
  uVar6 = DAT_0050d264;
  iVar12 = *(int *)(*(int *)(param_1 + 0x18) + 0xec);
  uVar1 = *(ushort *)(*(int *)(param_1 + 0x10) + 0x48);
  if ((uVar1 & 0x2000) == 0) {
    if ((uVar1 & 0x8000) == 0) {
      if ((uVar1 & 0x1000) == 0) {
        if ((uVar1 & 0x4000) == 0) {
          iVar8 = MoveVertical__9MenuSceneFi(param_1,1);
          if (iVar12 != iVar8) {
            Select__12CmdItemGoodsFP7CmdNoteP9MenuGroupP9MenuGroup
                      (*(undefined4 *)(param_1 + 0x68),*(undefined4 *)(param_1 + 0x90),iVar8,iVar12)
            ;
            PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x9c),0,0,0);
          }
        }
        else {
          *(undefined4 *)(param_1 + 0x58) = _5221;
          *(undefined4 *)(param_1 + 0x5c) = uVar3;
          *(undefined **)(param_1 + 0x60) = puVar4;
          PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x9c),3,0,0);
        }
      }
      else {
        *(undefined4 *)(param_1 + 0x58) = _5216;
        *(undefined4 *)(param_1 + 0x5c) = uVar6;
        *(undefined **)(param_1 + 0x60) = puVar2;
        PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x9c),2,0,0);
      }
    }
    else {
      lVar9 = __nw__FUi(0x160);
      uVar10 = 0;
      if (lVar9 != 0) {
        uVar10 = __ct__7CmdSortFv(lVar9);
      }
      iVar12 = (int)uVar10;
      *(int *)(param_1 + 0x7c) = iVar12;
      *(ushort *)(iVar12 + 0x15a) = (ushort)*(byte *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x28c);
      *(undefined4 *)(iVar12 + 0x15c) = *(undefined4 *)(*(int *)(param_1 + 0x18) + 0xec);
      *(undefined4 *)(iVar12 + 0x10) = *(undefined4 *)(param_1 + 0x10);
      Initialize__9MenuSceneFPUcP9BufMemory(uVar10,*(undefined4 *)(*(int *)(param_1 + 0x54) + 0x34),0);
      iVar12 = *(int *)(*(int *)(param_1 + 0x68) + 0x44);
      *(byte *)(iVar12 + 0x12) = *(byte *)(iVar12 + 0x12) & 0xfe;
      iVar12 = *(int *)(param_1 + 0x98);
      Close__10MenuWindowFUci(iVar12 + 0x58,((ulong)*(byte *)(iVar12 + 0x108) & 0x3f) >> 3,
                      *(undefined4 *)(*(int *)(iVar12 + 0x8c) + 0x14));
      puVar2 = PTR_ExecSort__7CmdItemFv_0050d258;
      uVar6 = DAT_0050d254;
      *(undefined4 *)(param_1 + 0x58) = _5211;
      *(undefined4 *)(param_1 + 0x5c) = uVar6;
      *(undefined **)(param_1 + 0x60) = puVar2;
      PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x9c),2,0,0);
    }
  }
  else if ((long)((ulong)*(byte *)(*(int *)(*(int *)(param_1 + 0x18) + 0xec) + 0x21) << 0x3c) < 0) {
    lVar9 = __nw__FUi(0xaa0);
    uVar6 = 0;
    if (lVar9 != 0) {
      uVar6 = __ct__15CmdSelectTargetFv(lVar9);
    }
    *(undefined4 *)(param_1 + 0x78) = uVar6;
    iVar8 = *(int *)(param_1 + 0x78);
    iVar7 = *(int *)(param_1 + 0x88) + *(short *)(iVar12 + 0x16) * 0x30;
    iVar11 = *(int *)(param_1 + 0x84) + *(short *)(iVar12 + 0x16) * 0x1c;
    *(undefined2 *)(iVar8 + 0x5c) = *(undefined2 *)(iVar12 + 0x16);
    *(undefined2 *)(iVar8 + 0x5e) = 3;
    *(byte *)(iVar8 + 0x61) = (byte)(((ulong)*(byte *)(iVar7 + 5) << 0x3c) >> 0x3d);
    *(byte *)(iVar8 + 0x60) = (byte)(((ulong)*(ushort *)(iVar7 + 4) << 0x37) >> 0x3e);
    uVar5 = GetPCIndex__8CmdPartyFUs(*(undefined4 *)(param_1 + 0x8c),*(undefined2 *)(iVar11 + 0x10))
    ;
    *(undefined2 *)(iVar8 + 0x62) = uVar5;
    *(int *)(iVar8 + 100) = iVar7 + 8;
    *(undefined4 *)(iVar8 + 0x68) = *(undefined4 *)(iVar11 + 8);
    *(undefined4 *)(iVar8 + 0x6c) = *(undefined4 *)(iVar11 + 0xc);
    *(undefined4 *)(iVar8 + 0x70) = *(undefined4 *)(*(int *)(param_1 + 0x18) + 0xec);
    *(undefined4 *)(*(int *)(param_1 + 0x78) + 0x10) = *(undefined4 *)(param_1 + 0x10);
    Initialize__9MenuSceneFPUcP9BufMemory(*(undefined4 *)(param_1 + 0x78),*(undefined4 *)(*(int *)(param_1 + 0x54) + 0x28)
                    ,0);
    iVar12 = *(int *)(*(int *)(param_1 + 0x68) + 0x44);
    *(byte *)(iVar12 + 0x12) = *(byte *)(iVar12 + 0x12) & 0xfe;
    iVar12 = *(int *)(param_1 + 0x98);
    Close__10MenuWindowFUci(iVar12 + 0x58,((ulong)*(byte *)(iVar12 + 0x108) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar12 + 0x8c) + 0x14));
    Shutdown__4MenuFv(*(undefined4 *)(param_1 + 0x10));
    puVar2 = PTR_ExecSelectTarget__7CmdItemFv_0050d248;
    uVar6 = DAT_0050d244;
    *(undefined4 *)(param_1 + 0x58) = _5203;
    *(undefined4 *)(param_1 + 0x5c) = uVar6;
    *(undefined **)(param_1 + 0x60) = puVar2;
    PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x9c),2,0,0);
  }
  else {
    PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x9c),4,0,0);
  }
  return 0;
}

/* JP: 0x00441470  CmdItem::ExecMessage()   [ExecMessage__7CmdItemFv]  size=0x158 */
undefined8 ExecMessage__7CmdItemFv(int param_1)

{
  bool bVar1;
  undefined4 uVar2;
  undefined *puVar3;
  long lVar4;
  
  if (*(char *)(param_1 + 0x21) == '\x01') {
    lVar4 = Run__14CmdItemMessageFUs
                      (*(undefined4 *)(param_1 + 0x6c),
                       *(undefined2 *)(*(int *)(param_1 + 0x10) + 0x48));
    if (lVar4 != 0) {
      *(undefined4 *)(param_1 + 0x70) = *(undefined4 *)(param_1 + 0x6c);
      puVar3 = PTR_Exit__7CmdItemFv_0050d288;
      uVar2 = DAT_0050d284;
      *(undefined4 *)(param_1 + 0x58) = _5339;
      *(undefined4 *)(param_1 + 0x5c) = uVar2;
      *(undefined **)(param_1 + 0x60) = puVar3;
      *(undefined1 *)(param_1 + 0x21) = 0;
    }
  }
  else if (*(char *)(param_1 + 0x21) == '\0') {
    if ((*(char *)(*(int *)(param_1 + 0x6c) + 0xa8) == '\x01') ||
       (*(char *)(*(int *)(param_1 + 0x6c) + 0xa8) == '\0')) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
    if (bVar1) {
      *(char *)(param_1 + 0x21) = *(char *)(param_1 + 0x21) + '\x01';
    }
  }
  return 0;
}

/* JP: 0x004415d0  CmdItem::ExecSelectTarget()   [ExecSelectTarget__7CmdItemFv]  size=0x498 */
undefined8 ExecSelectTarget__7CmdItemFv(int param_1)

{
  char cVar1;
  int iVar2;
  undefined *puVar3;
  undefined4 uVar4;
  long lVar5;
  
  lVar5 = (**(code **)(*(int *)(*(int *)(param_1 + 0x78) + 8) + 0x1c))();
  if (lVar5 != 0) {
    cVar1 = *(char *)(*(int *)(param_1 + 0x78) + 0x20);
    if (cVar1 == '\x04') {
      (**(code **)(*(int *)(*(int *)(param_1 + 0x78) + 8) + 0xc))();
      *(undefined4 *)(param_1 + 0x78) = 0;
      puVar3 = PTR_Exec__7CmdItemFv_0050d298;
      uVar4 = DAT_0050d294;
      *(undefined4 *)(param_1 + 0x58) = _5372;
      *(undefined4 *)(param_1 + 0x5c) = uVar4;
      *(undefined **)(param_1 + 0x60) = puVar3;
      if (*(short *)(*(int *)(param_1 + 0x68) + 0xae) == 0) {
        lVar5 = __nw__FUi(0x268);
        uVar4 = 0;
        if (lVar5 != 0) {
          uVar4 = __ct__14CmdItemMessageFv(lVar5);
        }
        *(undefined4 *)(param_1 + 0x6c) = uVar4;
        CreateScene__14CmdItemMessageFP7CmdItem(*(undefined4 *)(param_1 + 0x6c),param_1);
        iVar2 = *(int *)(param_1 + 0x6c);
        Open__10MenuWindowFUci(iVar2,*(byte *)(iVar2 + 0xb0) & 7,
                        *(undefined4 *)(*(int *)(iVar2 + 0x34) + 0x10));
        puVar3 = PTR_ExecMessage__7CmdItemFv_0050d2a8;
        uVar4 = DAT_0050d2a4;
        *(undefined4 *)(param_1 + 0x58) = _5377;
        *(undefined4 *)(param_1 + 0x5c) = uVar4;
        *(undefined **)(param_1 + 0x60) = puVar3;
      }
    }
    else {
      if (cVar1 != '\r') {
        if (cVar1 != '\x10') {
          return 0;
        }
        lVar5 = UpdateCount__12CmdItemGoodsFP7CmdItemss
                          (*(undefined4 *)(param_1 + 0x68),param_1,
                           *(undefined2 *)(*(int *)(*(int *)(param_1 + 0x78) + 0x70) + 0x16),
                           0xffffffffffffffff);
        if (lVar5 == 0) {
          return 0;
        }
        *(undefined1 *)(*(int *)(param_1 + 0x78) + 0x20) = 0xd;
        if (*(short *)(*(int *)(param_1 + 0x68) + 0xae) == 0) {
          ReleaseOT__7MenuObjFv(*(undefined4 *)(param_1 + 0x68));
          Shutdown__6CursorFv(*(undefined4 *)(param_1 + 0x18));
          return 0;
        }
        if (*(short *)(*(int *)(*(int *)(param_1 + 0x78) + 0x70) + 0x1e) <
            *(short *)(*(int *)(param_1 + 0x68) + 0xae)) {
          iVar2 = *(int *)(param_1 + 0x78);
          uVar4 = GetPlace__10MenuWindowFss(*(undefined4 *)(param_1 + 0x68),0,
                                  *(undefined2 *)(*(int *)(*(int *)(param_1 + 0x78) + 0x70) + 0x1e))
          ;
          *(undefined4 *)(iVar2 + 0x70) = uVar4;
        }
        else {
          iVar2 = *(int *)(param_1 + 0x78);
          uVar4 = GetPlace__10MenuWindowFss(*(undefined4 *)(param_1 + 0x68),0,
                                  *(short *)(*(int *)(param_1 + 0x68) + 0xae) + -1);
          *(undefined4 *)(iVar2 + 0x70) = uVar4;
        }
        Select__12CmdItemGoodsFP7CmdNoteP9MenuGroupP9MenuGroup
                  (*(undefined4 *)(param_1 + 0x68),*(undefined4 *)(param_1 + 0x90),
                   *(undefined4 *)(*(int *)(param_1 + 0x78) + 0x70),0);
      }
      iVar2 = *(int *)(*(int *)(param_1 + 0x68) + 0x44);
      *(byte *)(iVar2 + 0x12) = *(byte *)(iVar2 + 0x12) & 0xfe | 1;
      Open__15CmdButtonReportFv(*(undefined4 *)(param_1 + 0x98));
      Restore__4MenuFv(*(undefined4 *)(param_1 + 0x10));
    }
  }
  return 0;
}

/* JP: 0x00441a70  CmdItem::ExecSort()   [ExecSort__7CmdItemFv]  size=0x234 */
undefined4 ExecSort__7CmdItemFv(int param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined *puVar4;
  undefined4 uVar5;
  long lVar6;
  undefined8 uVar7;
  
  iVar2 = *(int *)(param_1 + 0x7c);
  iVar3 = *(int *)(param_1 + 0x68);
  lVar6 = (**(code **)(*(int *)(iVar2 + 8) + 0x1c))();
  if (lVar6 != 0) {
    cVar1 = *(char *)(iVar2 + 0x20);
    if (cVar1 == '\x04') {
      uVar7 = GetRegDat__9RegDatApiFiii(0x1a,*(undefined2 *)(*(int *)(iVar2 + 0x15c) + 0x16),
                              0xffffffffffffffff);
      SetExplanation__7CmdNoteFPCce(*(undefined4 *)(param_1 + 0x90),uVar7);
      *(byte *)(*(int *)(iVar3 + 0x44) + 0x12) = *(byte *)(*(int *)(iVar3 + 0x44) + 0x12) & 0xfe | 1
      ;
      (**(code **)(*(int *)(iVar2 + 8) + 0xc))();
      *(undefined4 *)(param_1 + 0x7c) = 0;
      puVar4 = PTR_Exec__7CmdItemFv_0050d2b8;
      uVar5 = DAT_0050d2b4;
      *(undefined4 *)(param_1 + 0x58) = _5486;
      *(undefined4 *)(param_1 + 0x5c) = uVar5;
      *(undefined **)(param_1 + 0x60) = puVar4;
      return 1;
    }
    if (cVar1 == '\r') {
      Open__15CmdButtonReportFv(*(undefined4 *)(param_1 + 0x98));
    }
    else if (cVar1 == '\x0f') {
      Order__12CmdItemGoodsFP7CmdItemUc(iVar3,param_1,*(ushort *)(iVar2 + 0x15a) & 0xff);
      uVar5 = *(undefined4 *)(iVar2 + 0x15c);
      uVar7 = GetPlace__10MenuWindowFss(iVar3,0,0);
      uVar5 = Select__12CmdItemGoodsFP7CmdNoteP9MenuGroupP9MenuGroup(iVar3,0,uVar7,uVar5);
      *(undefined4 *)(iVar2 + 0x15c) = uVar5;
      Open__10MenuWindowFUci(iVar3,*(byte *)(iVar3 + 0xb0) & 7,
                      *(undefined4 *)(*(int *)(iVar3 + 0x34) + 0x10));
    }
  }
  return 0;
}

/* JP: 0x00441cb0  CmdItem::EnterExplain()   [EnterExplain__7CmdItemFv]  size=0x318 */
undefined8 EnterExplain__7CmdItemFv(int param_1)

{
  int iVar1;
  bool bVar2;
  undefined4 uVar3;
  undefined *puVar4;
  long lVar5;
  undefined8 uVar6;
  
  if (*(char *)(param_1 + 0x21) == '\0') {
    *(byte *)(*(int *)(param_1 + 0x18) + 0x12) = *(byte *)(*(int *)(param_1 + 0x18) + 0x12) & 0xfe;
    iVar1 = *(int *)(param_1 + 0x68);
    Close__10MenuWindowFUci(iVar1,((ulong)*(byte *)(iVar1 + 0xb0) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x14));
    iVar1 = *(int *)(param_1 + 100);
    Close__10MenuWindowFUci(iVar1,((ulong)*(byte *)(iVar1 + 0xb0) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x14));
    iVar1 = *(int *)(param_1 + 0x98);
    Close__10MenuWindowFUci(iVar1 + 0x58,((ulong)*(byte *)(iVar1 + 0x108) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar1 + 0x8c) + 0x14));
    SetExplanation__7CmdNoteFPCce
              (*(undefined4 *)(param_1 + 0x90),*(undefined4 *)(*(int *)(param_1 + 0x28) + 0x14));
    *(char *)(param_1 + 0x21) = *(char *)(param_1 + 0x21) + '\x01';
  }
  else if (*(char *)(param_1 + 0x21) == '\x01') {
    if ((*(char *)(*(int *)(param_1 + 0x68) + 0xa8) == '\x01') ||
       (*(char *)(*(int *)(param_1 + 0x68) + 0xa8) == '\0')) {
      bVar2 = true;
    }
    else {
      bVar2 = false;
    }
    if (bVar2) {
      lVar5 = __nw__FUi(0x52c);
      uVar6 = 0;
      if (lVar5 != 0) {
        uVar6 = __ct__10CmdExplainFv(lVar5);
      }
      *(int *)(param_1 + 0x74) = (int)uVar6;
      Initialize__9MenuSceneFPUcP9BufMemory(uVar6,*(undefined4 *)(*(int *)(param_1 + 0x54) + 0x1c),0);
      SetInfo__10CmdExplainFP4MenusUcUc
                (uVar6,*(undefined4 *)(param_1 + 0x10),
                 *(undefined2 *)(*(int *)(param_1 + 0x68) + 0xae),3,0);
      SetIcon__10CmdExplainFP11MenuTexture(uVar6,0x421698);
      SetImage__10CmdExplainFPcss(uVar6,*(undefined4 *)(*(int *)(param_1 + 0x24) + 0x18),1,0);
      SetExplanation__7CmdItemFv(param_1);
      Select__12CmdItemGoodsFP7CmdNoteP9MenuGroupP9MenuGroup
                (*(undefined4 *)(param_1 + 0x68),0,0,
                 *(undefined4 *)(*(int *)(param_1 + 0x18) + 0xec));
      puVar4 = PTR_ExecExplain__7CmdItemFv_0050d2c8;
      uVar3 = DAT_0050d2c4;
      *(undefined4 *)(param_1 + 0x58) = _5522;
      *(undefined4 *)(param_1 + 0x5c) = uVar3;
      *(undefined **)(param_1 + 0x60) = puVar4;
      *(undefined1 *)(param_1 + 0x21) = 0;
    }
  }
  return 0;
}

/* JP: 0x00441fd0  CmdItem::ExecExplain()   [ExecExplain__7CmdItemFv]  size=0x138 */
undefined4 ExecExplain__7CmdItemFv(int param_1)

{
  undefined4 uVar1;
  undefined *puVar2;
  long lVar3;
  
  lVar3 = Exec__10CmdExplainFUs
                    (*(undefined4 *)(param_1 + 0x74),
                     *(undefined2 *)(*(int *)(param_1 + 0x10) + 0x48));
  puVar2 = PTR_ExitExplain__7CmdItemFv_0050d2d8;
  uVar1 = DAT_0050d2d4;
  if ((lVar3 != 0) && (lVar3 == 4)) {
    if ((long)((ulong)*(byte *)(*(int *)(param_1 + 0x74) + 0x525) << 0x3d) < 0) {
      *(undefined4 *)(param_1 + 0x58) = _5578;
      *(undefined4 *)(param_1 + 0x5c) = uVar1;
      *(undefined **)(param_1 + 0x60) = puVar2;
      return 1;
    }
    MoveCursor__6CursorFi(*(undefined4 *)(param_1 + 0x18),*(byte *)(*(int *)(param_1 + 0x74) + 0x524) >> 4
                   );
    SetExplanation__7CmdItemFv(param_1);
  }
  return 0;
}

/* JP: 0x00442110  CmdItem::ExitExplain()   [ExitExplain__7CmdItemFv]  size=0x1fc */
undefined8 ExitExplain__7CmdItemFv(int param_1)

{
  int iVar1;
  bool bVar2;
  undefined4 uVar3;
  undefined *puVar4;
  
  puVar4 = PTR_Exec__7CmdItemFv_0050d2e8;
  uVar3 = DAT_0050d2e4;
  if (*(char *)(param_1 + 0x21) == '\0') {
    iVar1 = *(int *)(param_1 + 0x74);
    if (iVar1 != 0) {
      (**(code **)(*(int *)(iVar1 + 8) + 8))(iVar1,1);
    }
    FinishScroll__10MenuWindowFv(*(undefined4 *)(param_1 + 0x68));
    Select__12CmdItemGoodsFP7CmdNoteP9MenuGroupP9MenuGroup
              (*(undefined4 *)(param_1 + 0x68),*(undefined4 *)(param_1 + 0x90),
               *(undefined4 *)(*(int *)(param_1 + 0x18) + 0xec),0);
    Restore__6CursorFv(*(undefined4 *)(param_1 + 0x18));
    iVar1 = *(int *)(param_1 + 0x68);
    Open__10MenuWindowFUci(iVar1,*(byte *)(iVar1 + 0xb0) & 7,*(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x10)
                   );
    iVar1 = *(int *)(param_1 + 100);
    Open__10MenuWindowFUci(iVar1,*(byte *)(iVar1 + 0xb0) & 7,*(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x10)
                   );
    Open__15CmdButtonReportFv(*(undefined4 *)(param_1 + 0x98));
    *(char *)(param_1 + 0x21) = *(char *)(param_1 + 0x21) + '\x01';
  }
  else if (*(char *)(param_1 + 0x21) == '\x01') {
    if ((*(char *)(*(int *)(param_1 + 0x68) + 0xa8) == '\x01') ||
       (*(char *)(*(int *)(param_1 + 0x68) + 0xa8) == '\0')) {
      bVar2 = true;
    }
    else {
      bVar2 = false;
    }
    if (bVar2) {
      *(undefined4 *)(param_1 + 0x58) = _5604;
      *(undefined4 *)(param_1 + 0x5c) = uVar3;
      *(undefined **)(param_1 + 0x60) = puVar4;
      *(undefined1 *)(param_1 + 0x21) = 0;
    }
  }
  return 0;
}

/* JP: 0x00442310  CmdItem::SetExplanation()   [SetExplanation__7CmdItemFv]  size=0x158 */
void SetExplanation__7CmdItemFv(int param_1)

{
  ushort uVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  
  iVar2 = *(int *)(param_1 + 0x74);
  memset(iVar2 + 0x5c,0,0x10);
  uVar1 = *(ushort *)(*(int *)(*(int *)(param_1 + 0x18) + 0xec) + 0x16);
  *(ushort *)(iVar2 + 0x5c) = uVar1;
  uVar4 = (uint)uVar1;
  *(undefined1 *)(iVar2 + 0x5e) = *(undefined1 *)(*(int *)(param_1 + 0x84) + uVar4 * 0x1c + 0x18);
  uVar3 = GetRegDat__9RegDatApiFiii(9,uVar1,0xffffffffffffffff);
  *(undefined4 *)(iVar2 + 0x60) = uVar3;
  *(undefined4 *)(iVar2 + 100) = *(undefined4 *)(*(int *)(param_1 + 0x84) + uVar4 * 0x1c);
  *(uint *)(iVar2 + 0x68) = *(int *)(param_1 + 0x84) + uVar4 * 0x1c + 4;
  Open__10CmdExplainFv(*(undefined4 *)(param_1 + 0x74));
  return;
}
