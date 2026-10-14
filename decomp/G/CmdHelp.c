/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdHelp   functions: 15
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdHelp.md).
 */

/* JP: 0x004590d0  CmdHelp::CmdHelp()   [__ct__7CmdHelpFv]  size=0x9c */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __ct__7CmdHelpFv(int param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  __ct__9MenuSceneFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__7CmdHelp;
  uVar2 = uRam004236d0;
  uVar1 = uRam004236cc;
  *(undefined4 *)(param_1 + 0x58) = ___ptmf_null;
  *(undefined4 *)(param_1 + 0x5c) = uVar1;
  *(undefined4 *)(param_1 + 0x60) = uVar2;
  __ct__11MenuTextureFv(param_1 + 0x68);
  __ct__11CmdHelpMenuFv(param_1 + 0xa8);
  __ct__13CmdHelpClauseFv(param_1 + 0x1d0);
  *(undefined4 *)(param_1 + 0x2cc) = 0;
  return param_1;
}

/* JP: 0x00459170  CmdHelp::~CmdHelp()   [__dt__7CmdHelpFv]  size=0xac */
int __dt__7CmdHelpFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__7CmdHelp;
    __dt__13CmdHelpClauseFv(param_1 + 0x1d0,0xffffffffffffffff);
    __dt__11CmdHelpMenuFv(param_1 + 0xa8,0xffffffffffffffff);
    __dt__11MenuTextureFv(param_1 + 0x68,0xffffffffffffffff);
    __dt__9MenuSceneFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x00459220  CmdHelp::GetReady()   [GetReady__7CmdHelpFv]  size=0x200 */
undefined4 GetReady__7CmdHelpFv(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined *puVar3;
  int iVar4;
  
  iVar1 = *(int *)(param_1 + 0x10);
  *(int *)(param_1 + 0x2dc) = iVar1 + 0xb8;
  *(int *)(param_1 + 0x2e0) = iVar1 + 0x4e0;
  *(int *)(param_1 + 0x2e8) = iVar1 + 0xa60;
  *(int *)(param_1 + 0x2e4) = iVar1 + 0x780;
  iVar4 = Find__13MenuDataTableFs(iVar1 + 0x28,0x10);
  *(short *)(param_1 + 0x2d0) = (short)*(undefined4 *)(iVar4 + 8);
  *(int *)(param_1 + 0x2d4) = iVar4 + 0x10;
  iVar4 = Find__13MenuDataTableFs(iVar1 + 0x28,0x11);
  *(short *)(param_1 + 0x2d2) = (short)*(undefined4 *)(iVar4 + 8);
  *(int *)(param_1 + 0x2d8) = iVar4 + 0x10;
  *(int *)(param_1 + 0x18) = iVar1 + 0x3a0;
  *(undefined4 *)(param_1 + 100) = sm_pSound__7MenuObj;
  Create__11MenuTextureFPUc6GS_PSMUii(param_1 + 0x68,*(undefined4 *)(*(int *)(param_1 + 0x54) + 0x1c),0x30,0,0);
  CreateScene__11CmdHelpMenuFP7CmdHelp(param_1 + 0xa8,param_1);
  CreateScene__13CmdHelpClauseFP7CmdHelp(param_1 + 0x1d0,param_1);
  if (-1 < (long)((ulong)*(byte *)(*(int *)(param_1 + 0x18) + 0x12) << 0x3d)) {
    AddOT__7MenuObjFv(*(undefined4 *)(param_1 + 0x18));
  }
  puVar3 = PTR_Enter__7CmdHelpFv_0050d4d0;
  uVar2 = DAT_0050d4cc;
  *(undefined4 *)(param_1 + 0x58) = _4944;
  *(undefined4 *)(param_1 + 0x5c) = uVar2;
  *(undefined **)(param_1 + 0x60) = puVar3;
  return 1;
}

/* JP: 0x00459420  CmdHelp::Run()   [Run__7CmdHelpFv]  size=0x5c */
undefined8 Run__7CmdHelpFv(int param_1)

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

/* JP: 0x00459480  CmdHelp::UpdateClause(short)   [UpdateClause__7CmdHelpFs]  size=0xf0 */
void UpdateClause__7CmdHelpFs(int param_1,short param_2)

{
  UpdateScene__13CmdHelpClauseFP7CmdHelps
            (param_1 + 0x1d0,param_1,
             *(undefined2 *)(*(int *)(*(int *)(param_1 + 0x18) + 0xec) + 0x16));
  if (param_2 == 0) {
    *(byte *)(param_1 + 0x1e2) = *(byte *)(param_1 + 0x1e2) & 0xfe | 1;
  }
  else {
    Open__10MenuWindowFUci(param_1 + 0x1d0,*(byte *)(param_1 + 0x280) & 7,
                    *(undefined4 *)(*(int *)(param_1 + 0x204) + 0x10));
  }
  return;
}

/* JP: 0x00459570  CmdHelp::LinkJump(short)   [LinkJump__7CmdHelpFs]  size=0x104 */
void LinkJump__7CmdHelpFs(int param_1,short param_2)

{
  undefined2 uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  int iVar4;
  
  iVar4 = *(int *)(param_1 + 0x2d8) + param_2 * 0x24;
  uVar1 = *(undefined2 *)(param_1 + 0x27e);
  uVar2 = GetPlace__10MenuWindowFs(param_1 + 0xa8,*(undefined1 *)(iVar4 + 0x1c));
  uVar3 = GetPlace__10MenuWindowFs(param_1 + 0xa8,uVar1);
  Select__11CmdHelpMenuFP7CmdHelpP8MenuTextP8MenuText(param_1 + 0xa8,param_1,uVar2,uVar3);
  UpdateScene__13CmdHelpClauseFP7CmdHelps(param_1 + 0x1d0,param_1,*(undefined1 *)(iVar4 + 0x1c));
  uVar2 = GetPlace__10MenuWindowFs(param_1 + 0x1d0,param_2);
  Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),uVar2);
  return;
}

/* JP: 0x00459680  CmdHelp::SetButtonReport(short)   [SetButtonReport__7CmdHelpFs]  size=0xe0 */
void SetButtonReport__7CmdHelpFs(int param_1,short param_2)

{
  short sVar1;
  
  sVar1 = 0;
  ClearReport__15CmdButtonReportFv(*(undefined4 *)(param_1 + 0x2e8));
  if ((*(int *)(param_1 + 0x2cc) != 0) && (*(byte *)(*(int *)(param_1 + 0x2cc) + 0x3ff) >> 3 != 0))
  {
    SetReport__15CmdButtonReportFii(*(undefined4 *)(param_1 + 0x2e8),1,0x10);
    sVar1 = 1;
  }
  if (param_2 != 0) {
    SetReport__15CmdButtonReportFii(*(undefined4 *)(param_1 + 0x2e8),sVar1,0xe);
    SetReport__15CmdButtonReportFii(*(undefined4 *)(param_1 + 0x2e8),sVar1 + 1,0xf);
  }
  return;
}

/* JP: 0x00459760  CmdHelp::GetMaxClause()   [GetMaxClause__7CmdHelpFv]  size=0xa0 */
short GetMaxClause__7CmdHelpFv(int param_1)

{
  uint uVar1;
  short sVar2;
  uint uVar3;
  
  sVar2 = 0;
  uVar1 = *(uint *)(param_1 + 0x2d4);
  uVar3 = uVar1 + (uint)*(ushort *)(param_1 + 0x2d0) * 0xc;
  for (; uVar1 < uVar3; uVar1 = uVar1 + 0xc) {
    if (sVar2 < *(short *)(uVar1 + 8)) {
      sVar2 = *(short *)(uVar1 + 8);
    }
  }
  return sVar2;
}

/* JP: 0x00459800  CmdHelp::Enter()   [Enter__7CmdHelpFv]  size=0x238 */
undefined8 Enter__7CmdHelpFv(int param_1)

{
  bool bVar1;
  undefined4 uVar2;
  undefined *puVar3;
  undefined1 uVar4;
  undefined8 uVar5;
  
  if (*(char *)(param_1 + 0x21) == '\0') {
    uVar5 = GetMenu__11CmdHelpMenuFP7CmdHelp(param_1 + 0xa8,param_1);
    Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),uVar5);
    Select__11CmdHelpMenuFP7CmdHelpP8MenuTextP8MenuText
              (param_1 + 0xa8,param_1,*(undefined4 *)(*(int *)(param_1 + 0x18) + 0xec),0);
    Open__10MenuWindowFUci(param_1 + 0xa8,*(byte *)(param_1 + 0x158) & 7,
                    *(undefined4 *)(*(int *)(param_1 + 0xdc) + 0x10));
    SetTitle__11CmdTitleLogFPUci
              (*(undefined4 *)(param_1 + 0x2e4),*(undefined4 *)(*(int *)(param_1 + 0x54) + 0x10),5);
    Open__11CmdTitleLogFv(*(undefined4 *)(param_1 + 0x2e4));
    UpdateClause__7CmdHelpFs(param_1,1);
    uVar4 = CreateBackGround__7CmdMenuFs(*(undefined4 *)(param_1 + 0x10),9);
    *(undefined1 *)(param_1 + 0x20) = uVar4;
    *(char *)(param_1 + 0x21) = *(char *)(param_1 + 0x21) + '\x01';
  }
  else if (*(char *)(param_1 + 0x21) == '\x01') {
    if ((*(char *)(param_1 + 0x278) == '\x01') || (*(char *)(param_1 + 0x278) == '\0')) {
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
      puVar3 = PTR_SelectMenu__7CmdHelpFv_0050d4e0;
      uVar2 = DAT_0050d4dc;
      *(undefined4 *)(param_1 + 0x58) = _5055;
      *(undefined4 *)(param_1 + 0x5c) = uVar2;
      *(undefined **)(param_1 + 0x60) = puVar3;
      *(undefined1 *)(param_1 + 0x21) = 0;
    }
  }
  return 0;
}

/* JP: 0x00459a40  CmdHelp::Exit()   [Exit__7CmdHelpFv]  size=0x210 */
undefined8 Exit__7CmdHelpFv(int param_1)

{
  int iVar1;
  bool bVar2;
  
  if (*(char *)(param_1 + 0x21) == '\0') {
    (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x14) + 0x28))
              (*(int *)(param_1 + 0x10),*(undefined2 *)(*(int *)(param_1 + 0x10) + 0x42),0,0xf);
    Shutdown__6CursorFv(*(undefined4 *)(param_1 + 0x18));
    Close__10MenuWindowFUci(param_1 + 0xa8,((ulong)*(byte *)(param_1 + 0x158) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(param_1 + 0xdc) + 0x14));
    Close__10MenuWindowFUci(param_1 + 0x1d0,((ulong)*(byte *)(param_1 + 0x280) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(param_1 + 0x204) + 0x14));
    iVar1 = *(int *)(param_1 + 0x2e4);
    Close__10MenuWindowFUci(iVar1 + 0x58,((ulong)*(byte *)(iVar1 + 0x108) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar1 + 0x8c) + 0x14));
    *(char *)(param_1 + 0x21) = *(char *)(param_1 + 0x21) + '\x01';
  }
  else if (*(char *)(param_1 + 0x21) == '\x01') {
    if ((*(char *)(param_1 + 0x278) == '\x01') || (*(char *)(param_1 + 0x278) == '\0')) {
      bVar2 = true;
    }
    else {
      bVar2 = false;
    }
    if (bVar2) {
      ReleaseOT__7MenuObjFv(param_1 + 0xa8);
      ReleaseOT__7MenuObjFv(param_1 + 0x1d0);
      (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x14) + 0x24))(*(int *)(param_1 + 0x10),0);
      DestroyScene__4MenuFP9MenuSceneb(*(undefined4 *)(param_1 + 0x10),param_1,1);
    }
  }
  return 0;
}

/* JP: 0x00459c50  CmdHelp::SelectMenu()   [SelectMenu__7CmdHelpFv]  size=0x288 */
undefined8 SelectMenu__7CmdHelpFv(int param_1)

{
  ushort uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined *puVar4;
  int iVar5;
  undefined8 uVar6;
  ulong uVar7;
  
  puVar4 = PTR_Exit__7CmdHelpFv_0050d500;
  uVar3 = DAT_0050d4fc;
  uVar1 = *(ushort *)(*(int *)(param_1 + 0x10) + 0x48);
  iVar2 = *(int *)(*(int *)(param_1 + 0x18) + 0xec);
  if ((uVar1 & 0x2000) == 0) {
    if ((uVar1 & 0x4000) == 0) {
      iVar5 = MoveVertical__9MenuSceneFi(param_1,0);
      if (iVar2 != iVar5) {
        Select__11CmdHelpMenuFP7CmdHelpP8MenuTextP8MenuText(param_1 + 0xa8,param_1,iVar5,iVar2);
        UpdateClause__7CmdHelpFs(param_1,1);
        PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 100),0,0,0);
      }
    }
    else {
      *(undefined4 *)(param_1 + 0x58) = _5116;
      *(undefined4 *)(param_1 + 0x5c) = uVar3;
      *(undefined **)(param_1 + 0x60) = puVar4;
      PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 100),3,0,0);
    }
  }
  else {
    uVar6 = GetPlace__10MenuWindowFss(param_1 + 0x1d0,0,0);
    Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),uVar6);
    Select__13CmdHelpClauseFP7CmdHelpP9MenuGroupP9MenuGroup(param_1 + 0x1d0,param_1,uVar6,0);
    ClearReport__15CmdButtonReportFv(*(undefined4 *)(param_1 + 0x2e8));
    if (*(int *)(param_1 + 0x214) == 0) {
      uVar7 = 0;
    }
    else {
      uVar7 = ((ulong)*(ushort *)(param_1 + 0x282) & 0x3ff) >> 2;
    }
    if (uVar7 != 0) {
      SetReport__15CmdButtonReportFii(*(undefined4 *)(param_1 + 0x2e8),0,0xd);
    }
    Open__15CmdButtonReportFv(*(undefined4 *)(param_1 + 0x2e8));
    puVar4 = PTR_SelectClause__7CmdHelpFv_0050d4f0;
    uVar3 = DAT_0050d4ec;
    *(undefined4 *)(param_1 + 0x58) = _5111;
    *(undefined4 *)(param_1 + 0x5c) = uVar3;
    *(undefined **)(param_1 + 0x60) = puVar4;
    PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 100),2,0,0);
  }
  return 0;
}

/* JP: 0x00459ee0  CmdHelp::SelectClause()   [SelectClause__7CmdHelpFv]  size=0x270 */
undefined8 SelectClause__7CmdHelpFv(int param_1)

{
  ushort uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined *puVar4;
  int iVar5;
  undefined8 uVar6;
  
  puVar4 = PTR_EnterExplain__7CmdHelpFv_0050d510;
  uVar3 = DAT_0050d50c;
  uVar1 = *(ushort *)(*(int *)(param_1 + 0x10) + 0x48);
  iVar2 = *(int *)(*(int *)(param_1 + 0x18) + 0xec);
  if ((uVar1 & 0x2000) == 0) {
    if ((uVar1 & 0x4000) == 0) {
      iVar5 = MoveVertical__9MenuSceneFi(param_1,1);
      if (iVar2 != iVar5) {
        Select__13CmdHelpClauseFP7CmdHelpP9MenuGroupP9MenuGroup(param_1 + 0x1d0,param_1,iVar5,iVar2)
        ;
        PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 100),0,0,0);
      }
    }
    else {
      Select__13CmdHelpClauseFP7CmdHelpP9MenuGroupP9MenuGroup(param_1 + 0x1d0,param_1,0,iVar2);
      uVar6 = GetPlace__10MenuWindowFs(param_1 + 0xa8,*(undefined2 *)(param_1 + 0x27e));
      Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),uVar6);
      Select__11CmdHelpMenuFP7CmdHelpP8MenuTextP8MenuText
                (param_1 + 0xa8,param_1,*(undefined4 *)(*(int *)(param_1 + 0x18) + 0xec),0);
      SetScroll__10MenuWindowFss(param_1 + 0x1d0,0,0);
      iVar2 = *(int *)(param_1 + 0x2e8);
      Close__10MenuWindowFUci(iVar2 + 0x58,((ulong)*(byte *)(iVar2 + 0x108) & 0x3f) >> 3,
                      *(undefined4 *)(*(int *)(iVar2 + 0x8c) + 0x14));
      puVar4 = PTR_SelectMenu__7CmdHelpFv_0050d520;
      uVar3 = DAT_0050d51c;
      *(undefined4 *)(param_1 + 0x58) = _5152;
      *(undefined4 *)(param_1 + 0x5c) = uVar3;
      *(undefined **)(param_1 + 0x60) = puVar4;
      PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 100),3,0,0);
    }
  }
  else {
    *(undefined4 *)(param_1 + 0x58) = _5147;
    *(undefined4 *)(param_1 + 0x5c) = uVar3;
    *(undefined **)(param_1 + 0x60) = puVar4;
    PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 100),2,0,0);
  }
  return 0;
}

/* JP: 0x0045a150  CmdHelp::EnterExplain()   [EnterExplain__7CmdHelpFv]  size=0x248 */
undefined8 EnterExplain__7CmdHelpFv(int param_1)

{
  bool bVar1;
  undefined *puVar2;
  undefined4 uVar3;
  long lVar4;
  
  if (*(char *)(param_1 + 0x21) == '\0') {
    *(byte *)(*(int *)(param_1 + 0x18) + 0x12) = *(byte *)(*(int *)(param_1 + 0x18) + 0x12) & 0xfe;
    Close__10MenuWindowFUci(param_1 + 0x1d0,((ulong)*(byte *)(param_1 + 0x280) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(param_1 + 0x204) + 0x14));
    *(char *)(param_1 + 0x21) = *(char *)(param_1 + 0x21) + '\x01';
  }
  else if (*(char *)(param_1 + 0x21) == '\x01') {
    if ((*(char *)(param_1 + 0x278) == '\x01') || (*(char *)(param_1 + 0x278) == '\0')) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
    if (bVar1) {
      lVar4 = __nw__FUi(0x428);
      uVar3 = 0;
      if (lVar4 != 0) {
        uVar3 = __ct__14CmdHelpExplainFv(lVar4);
      }
      *(undefined4 *)(param_1 + 0x2cc) = uVar3;
      CreateScene__14CmdHelpExplainFP7CmdHelp(*(undefined4 *)(param_1 + 0x2cc),param_1);
      UpdateScene__14CmdHelpExplainFP7CmdHelps
                (*(undefined4 *)(param_1 + 0x2cc),param_1,
                 *(undefined2 *)(*(int *)(*(int *)(param_1 + 0x18) + 0xec) + 0x16));
      Select__13CmdHelpClauseFP7CmdHelpP9MenuGroupP9MenuGroup
                (param_1 + 0x1d0,param_1,0,*(undefined4 *)(*(int *)(param_1 + 0x18) + 0xec));
      puVar2 = PTR_ExecExplain__7CmdHelpFv_0050d530;
      uVar3 = DAT_0050d52c;
      *(undefined4 *)(param_1 + 0x58) = _5191;
      *(undefined4 *)(param_1 + 0x5c) = uVar3;
      *(undefined **)(param_1 + 0x60) = puVar2;
      *(undefined1 *)(param_1 + 0x21) = 0;
    }
  }
  return 0;
}

/* JP: 0x0045a3a0  CmdHelp::ExecExplain()   [ExecExplain__7CmdHelpFv]  size=0x64 */
undefined8 ExecExplain__7CmdHelpFv(int param_1)

{
  undefined4 uVar1;
  undefined *puVar2;
  long lVar3;
  
  lVar3 = Run__14CmdHelpExplainFP7CmdHelp(*(undefined4 *)(param_1 + 0x2cc),param_1);
  puVar2 = PTR_ExitExplain__7CmdHelpFv_0050d540;
  uVar1 = DAT_0050d53c;
  if (lVar3 != 0) {
    *(undefined4 *)(param_1 + 0x58) = _5231;
    *(undefined4 *)(param_1 + 0x5c) = uVar1;
    *(undefined **)(param_1 + 0x60) = puVar2;
  }
  return 0;
}

/* JP: 0x0045a410  CmdHelp::ExitExplain()   [ExitExplain__7CmdHelpFv]  size=0x330 */
undefined8 ExitExplain__7CmdHelpFv(int param_1)

{
  int iVar1;
  bool bVar2;
  undefined4 uVar3;
  undefined *puVar4;
  undefined8 uVar5;
  ulong uVar6;
  float fVar7;
  
  puVar4 = PTR_SelectClause__7CmdHelpFv_0050d550;
  uVar3 = DAT_0050d54c;
  if (*(char *)(param_1 + 0x21) == '\0') {
    iVar1 = *(int *)(param_1 + 0x2cc);
    if (iVar1 != 0) {
      (**(code **)(*(int *)(iVar1 + 8) + 8))(iVar1,1);
    }
    *(undefined4 *)(param_1 + 0x2cc) = 0;
    *(undefined2 *)(param_1 + 0x2ee) =
         *(undefined2 *)(*(int *)(*(int *)(param_1 + 0x18) + 0xec) + 0x16);
    fVar7 = (float)GetTargetY__10MenuWindowCFv(param_1 + 0x1d0);
    *(short *)(param_1 + 0x2ec) =
         (short)(int)(-fVar7 / *(float *)(*(int *)(param_1 + 0x210) + 0x20));
    UpdateScene__13CmdHelpClauseFP7CmdHelps
              (param_1 + 0x1d0,param_1,*(undefined2 *)(param_1 + 0x27e));
    SetScroll__10MenuWindowFss(param_1 + 0x1d0,0,*(undefined2 *)(param_1 + 0x2ec));
    Finish__10MenuWindowFv(param_1 + 0x1d0);
    uVar5 = GetPlace__10MenuWindowFs(param_1 + 0x1d0,*(undefined2 *)(param_1 + 0x2ee));
    Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),uVar5);
    Restore__6CursorFv(*(undefined4 *)(param_1 + 0x18));
    Select__13CmdHelpClauseFP7CmdHelpP9MenuGroupP9MenuGroup
              (param_1 + 0x1d0,param_1,*(undefined4 *)(*(int *)(param_1 + 0x18) + 0xec),0);
    ClearReport__15CmdButtonReportFv(*(undefined4 *)(param_1 + 0x2e8));
    if (*(int *)(param_1 + 0x214) == 0) {
      uVar6 = 0;
    }
    else {
      uVar6 = ((ulong)*(ushort *)(param_1 + 0x282) & 0x3ff) >> 2;
    }
    if (uVar6 != 0) {
      SetReport__15CmdButtonReportFii(*(undefined4 *)(param_1 + 0x2e8),0,0xd);
    }
    Open__10MenuWindowFUci(param_1 + 0x1d0,*(byte *)(param_1 + 0x280) & 7,
                    *(undefined4 *)(*(int *)(param_1 + 0x204) + 0x10));
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
      *(undefined4 *)(param_1 + 0x58) = _5242;
      *(undefined4 *)(param_1 + 0x5c) = uVar3;
      *(undefined **)(param_1 + 0x60) = puVar4;
      *(undefined1 *)(param_1 + 0x21) = 0;
    }
  }
  return 0;
}
