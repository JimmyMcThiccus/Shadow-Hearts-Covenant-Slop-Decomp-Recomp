/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdFormation   functions: 12
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdFormation.md).
 */

/* JP: 0x0047dd70  CmdFormation::CmdFormation()   [__ct__12CmdFormationFv]  size=0x74 */
int __ct__12CmdFormationFv(int param_1)

{
  __ct__9MenuSceneFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__12CmdFormation;
  __ct__6CursorFv(param_1 + 0x74);
  *(undefined4 *)(param_1 + 0x170) = 0;
  __ct__18CmdFormationMemberFv(param_1 + 0x178);
  __ct__16CmdFormationTeamFv(param_1 + 0x728);
  return param_1;
}

/* JP: 0x0047ddf0  CmdFormation::~CmdFormation()   [__dt__12CmdFormationFv]  size=0xac */
int __dt__12CmdFormationFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__12CmdFormation;
    __dt__16CmdFormationTeamFv(param_1 + 0x728,0xffffffffffffffff);
    __dt__18CmdFormationMemberFv(param_1 + 0x178,0xffffffffffffffff);
    __dt__6CursorFv(param_1 + 0x74,0xffffffffffffffff);
    __dt__9MenuSceneFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x0047dea0  CmdFormation::GetReady()   [GetReady__12CmdFormationFv]  size=0x250 */
undefined4 GetReady__12CmdFormationFv(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined *puVar3;
  short sVar4;
  short sVar5;
  undefined2 uVar6;
  
  iVar1 = *(int *)(param_1 + 0x10);
  *(int *)(param_1 + 0x6c) = iVar1 + 0x4e0;
  *(int *)(param_1 + 0x68) = iVar1 + 0xa60;
  *(int *)(param_1 + 0x70) = iVar1 + 0x780;
  *(undefined4 *)(param_1 + 100) = sm_pSound__7MenuObj;
  *(int *)(param_1 + 0x18) = iVar1 + 0x3a0;
  sVar5 = (short)*(char *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x80);
  uVar6 = 1;
  if (sVar5 < 3) {
    uVar6 = 3;
    sVar4 = 0;
  }
  else {
    sVar4 = sVar5;
    if (4 < sVar5) {
      sVar4 = 3;
      uVar6 = 2;
      sVar5 = 3;
      *(byte *)(param_1 + 0x23) = *(byte *)(param_1 + 0x23) & 0x3f | 0x40;
    }
  }
  *(short *)(param_1 + 0xe50) = sVar4;
  *(undefined2 *)(param_1 + 0xe52) = uVar6;
  *(char *)(param_1 + 0x22) = (char)sVar5 - (char)*(undefined2 *)(param_1 + 0xe50);
  CreateScene__16CmdFormationTeamFP12CmdFormation(param_1 + 0x728,param_1);
  CreateScene__18CmdFormationMemberFP12CmdFormation(param_1 + 0x178,param_1);
  UpdateName__16CmdFormationTeamFP12CmdFormation(param_1 + 0x728,param_1);
  UpdateScene__18CmdFormationMemberFP12CmdFormations(param_1 + 0x178,param_1,sVar5);
  puVar3 = PTR_Enter__12CmdFormationFv_0050d968;
  uVar2 = DAT_0050d964;
  *(undefined4 *)(param_1 + 0x58) = _4956;
  *(undefined4 *)(param_1 + 0x5c) = uVar2;
  *(undefined **)(param_1 + 0x60) = puVar3;
  return 1;
}

/* JP: 0x0047e0f0  CmdFormation::Run()   [Run__12CmdFormationFv]  size=0x5c */
undefined8 Run__12CmdFormationFv(int param_1)

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

/* JP: 0x0047e150  CmdFormation::CreateMessage(int)   [CreateMessage__12CmdFormationFi]  size=0x158 */
void CreateMessage__12CmdFormationFi(int param_1,int param_2)

{
  int iVar1;
  undefined *puVar2;
  undefined4 uVar3;
  long lVar4;
  undefined1 auStack_80 [96];
  int iStack_20;
  int iStack_10;
  
  iStack_20 = param_1;
  iStack_10 = param_2;
  __ct__9MenuSceneFv(auStack_80);
  Initialize__9MenuSceneFPUcP9BufMemory(auStack_80,*(undefined4 *)(*(int *)(iStack_20 + 0x54) + 0xe8),0);
  lVar4 = __nw__FUi(0x2b0);
  uVar3 = 0;
  if (lVar4 != 0) {
    uVar3 = __ct__14CmdNoteMessageFv(lVar4);
  }
  *(undefined4 *)(iStack_20 + 0x170) = uVar3;
  CreateScene__14CmdNoteMessageFP9MenuScenePci
            (*(undefined4 *)(iStack_20 + 0x170),auStack_80,
             *(undefined4 *)((iStack_10 + 10U & 0xffff) * 8 + *(int *)(iStack_20 + 0x24) + 0x10),1);
  iVar1 = *(int *)(iStack_20 + 0x170);
  Open__10MenuWindowFUci(iVar1,*(byte *)(iVar1 + 0xb0) & 7,*(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x10));
  PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(iStack_20 + 100),4,0,0);
  puVar2 = PTR_DisplayMessage__12CmdFormationFv_0050d978;
  uVar3 = DAT_0050d974;
  *(undefined4 *)(iStack_20 + 0x58) = _4995;
  *(undefined4 *)(iStack_20 + 0x5c) = uVar3;
  *(undefined **)(iStack_20 + 0x60) = puVar2;
  __dt__9MenuSceneFv(auStack_80,0xffffffffffffffff);
  return;
}

/* JP: 0x0047e2b0  CmdFormation::SetButtonReport(int)   [SetButtonReport__12CmdFormationFi]  size=0xf4 */
void SetButtonReport__12CmdFormationFi(int param_1,int param_2)

{
  ClearReport__15CmdButtonReportFv(*(undefined4 *)(param_1 + 0x68));
  if (param_2 < 2) {
    if (*(short *)(param_1 + 0xe50) < 3) {
      SetReport__15CmdButtonReportFii
                (*(int *)(param_1 + 0x68),*(undefined1 *)(*(int *)(param_1 + 0x68) + 0x20),10);
    }
    SetReport__15CmdButtonReportFii
              (*(int *)(param_1 + 0x68),*(undefined1 *)(*(int *)(param_1 + 0x68) + 0x20),5);
    if (param_2 == 0) {
      SetReport__15CmdButtonReportFii
                (*(int *)(param_1 + 0x68),*(undefined1 *)(*(int *)(param_1 + 0x68) + 0x20),0);
    }
  }
  return;
}

/* JP: 0x0047e3b0  CmdFormation::Enter()   [Enter__12CmdFormationFv]  size=0x254 */
undefined8 Enter__12CmdFormationFv(int param_1)

{
  undefined4 uVar1;
  bool bVar2;
  undefined *puVar3;
  undefined1 uVar4;
  undefined8 uVar5;
  
  uVar1 = *(undefined4 *)(param_1 + 0x10);
  if (*(char *)(param_1 + 0x21) == '\0') {
    SetTitle__11CmdTitleLogFPUci
              (*(undefined4 *)(param_1 + 0x70),*(undefined4 *)(*(int *)(param_1 + 0x54) + 0x10),2);
    Open__11CmdTitleLogFv(*(undefined4 *)(param_1 + 0x70));
    SetButtonReport__12CmdFormationFi(param_1,0);
    Open__15CmdButtonReportFv(*(undefined4 *)(param_1 + 0x68));
    Open__10MenuWindowFUci(param_1 + 0x178,*(byte *)(param_1 + 0x228) & 7,
                    *(undefined4 *)(*(int *)(param_1 + 0x1ac) + 0x10));
    Open__10MenuWindowFUci(param_1 + 0x728,*(byte *)(param_1 + 0x7d8) & 7,
                    *(undefined4 *)(*(int *)(param_1 + 0x75c) + 0x10));
    uVar4 = CreateBackGround__7CmdMenuFs(uVar1,9);
    *(undefined1 *)(param_1 + 0x20) = uVar4;
    *(char *)(param_1 + 0x21) = *(char *)(param_1 + 0x21) + '\x01';
  }
  else if (*(char *)(param_1 + 0x21) == '\x01') {
    if ((*(char *)(param_1 + 0x220) == '\x01') || (*(char *)(param_1 + 0x220) == '\0')) {
      bVar2 = true;
    }
    else {
      bVar2 = false;
    }
    if (bVar2) {
      if (*(char *)(param_1 + 0x20) != '\0') {
        DestroyBackGround__7CmdMenuFs(uVar1,1);
        *(undefined1 *)(param_1 + 0x20) = 0;
      }
      uVar5 = GetPlace__10MenuWindowFss(param_1 + 0x728,0,*(undefined1 *)(param_1 + 0x22));
      Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),uVar5);
      Select__16CmdFormationTeamFP12CmdFormationP9MenuPlaceP9MenuPlace
                (param_1 + 0x728,param_1,uVar5,0);
      puVar3 = PTR_SelectTeam__12CmdFormationFv_0050d988;
      uVar1 = DAT_0050d984;
      *(undefined4 *)(param_1 + 0x58) = _5041;
      *(undefined4 *)(param_1 + 0x5c) = uVar1;
      *(undefined **)(param_1 + 0x60) = puVar3;
      *(undefined1 *)(param_1 + 0x21) = 0;
    }
  }
  return 0;
}

/* JP: 0x0047e610  CmdFormation::Exit()   [Exit__12CmdFormationFv]  size=0x110 */
undefined8 Exit__12CmdFormationFv(int param_1)

{
  bool bVar1;
  undefined8 uVar2;
  
  if ((*(char *)(param_1 + 2000) == '\x01') || (*(char *)(param_1 + 2000) == '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if (bVar1) {
    ReleaseOT__7MenuObjFv(param_1 + 0x728);
    ReleaseOT__7MenuObjFv(param_1 + 0x178);
    uVar2 = 0;
    if (*(char *)(*(int *)(param_1 + 0x10) + 0x4f) != '\0') {
      uVar2 = 0x17;
    }
    (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x14) + 0x24))(*(int *)(param_1 + 0x10),uVar2);
    DestroyScene__4MenuFP9MenuSceneb(*(undefined4 *)(param_1 + 0x10),param_1,1);
  }
  return 0;
}

/* JP: 0x0047e720  CmdFormation::SelectTeam()   [SelectTeam__12CmdFormationFv]  size=0x4ec */
undefined8 SelectTeam__12CmdFormationFv(int param_1)

{
  short sVar1;
  ushort uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined *puVar5;
  int iVar6;
  long lVar7;
  short sVar8;
  undefined8 uVar9;
  
  uVar2 = *(ushort *)(*(int *)(param_1 + 0x10) + 0x48);
  iVar3 = *(int *)(*(int *)(param_1 + 0x18) + 0xec);
  if ((uVar2 & 0x2000) == 0) {
    if ((uVar2 & 0x4000) == 0) {
      if ((uVar2 & 0x1000) == 0) {
        iVar6 = MoveVertical__9MenuSceneFi(param_1,0);
        if (iVar3 != iVar6) {
          Select__16CmdFormationTeamFP12CmdFormationP9MenuPlaceP9MenuPlace
                    (param_1 + 0x728,param_1,iVar6,iVar3);
          PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 100),0,0,0);
        }
      }
      else {
        ResetTeam__16CmdFormationTeamFP12CmdFormation(param_1 + 0x728,param_1);
      }
    }
    else {
      lVar7 = IsBlank__16CmdFormationTeamFP12CmdFormationss
                        (param_1 + 0x728,param_1,0,*(undefined2 *)(param_1 + 0xe52));
      if (lVar7 == 0) {
        if ((*(byte *)(param_1 + 0x23) >> 6 == 0) ||
           (lVar7 = IsFull__16CmdFormationTeamFP12CmdFormation(param_1 + 0x728,param_1), lVar7 != 0)
           ) {
          sVar8 = *(short *)(iVar3 + 0x1e);
          sVar1 = *(short *)(param_1 + 0xe52);
          while (lVar7 = IsBlank__16CmdFormationTeamFP12CmdFormationss
                                   (param_1 + 0x728,param_1,sVar8,1), lVar7 != 0) {
            sVar8 = sVar8 + 1;
            if (sVar1 <= sVar8) {
              sVar8 = 0;
            }
          }
          *(char *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x80) =
               (char)sVar8 + (char)*(undefined2 *)(param_1 + 0xe50);
          SortPC__8CmdPartyFPc
                    (*(int *)(param_1 + 0x10) + 0xb8,
                     *(int *)(sm_pSubstance__15SaveMenuSection + 0xc) +
                     *(char *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x80) * 0x20 + 0x96);
          uVar9 = 0;
          if (*(char *)(*(int *)(param_1 + 0x10) + 0x4f) != '\0') {
            uVar9 = 0x17;
          }
          (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x14) + 0x28))
                    (*(int *)(param_1 + 0x10),uVar9,0,7);
          Leave__6CursorFv(*(undefined4 *)(param_1 + 0x18));
          iVar3 = *(int *)(param_1 + 0x68);
          Close__10MenuWindowFUci(iVar3 + 0x58,((ulong)*(byte *)(iVar3 + 0x108) & 0x3f) >> 3,
                          *(undefined4 *)(*(int *)(iVar3 + 0x8c) + 0x14));
          iVar3 = *(int *)(param_1 + 0x70);
          Close__10MenuWindowFUci(iVar3 + 0x58,((ulong)*(byte *)(iVar3 + 0x108) & 0x3f) >> 3,
                          *(undefined4 *)(*(int *)(iVar3 + 0x8c) + 0x14));
          Close__10MenuWindowFUci(param_1 + 0x728,((ulong)*(byte *)(param_1 + 0x7d8) & 0x3f) >> 3,
                          *(undefined4 *)(*(int *)(param_1 + 0x75c) + 0x14));
          Close__10MenuWindowFUci(param_1 + 0x178,((ulong)*(byte *)(param_1 + 0x228) & 0x3f) >> 3,
                          *(undefined4 *)(*(int *)(param_1 + 0x1ac) + 0x14));
          puVar5 = PTR_Exit__12CmdFormationFv_0050d9a8;
          uVar4 = DAT_0050d9a4;
          *(undefined4 *)(param_1 + 0x58) = _5102;
          *(undefined4 *)(param_1 + 0x5c) = uVar4;
          *(undefined **)(param_1 + 0x60) = puVar5;
          PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 100),3,0,0);
        }
        else {
          CreateMessage__12CmdFormationFi(param_1,1);
        }
      }
      else {
        CreateMessage__12CmdFormationFi(param_1,0);
      }
    }
  }
  else {
    *(undefined2 *)(param_1 + 0xdca) = *(undefined2 *)(iVar3 + 0x1e);
    *(undefined2 *)(param_1 + 0xdc8) = 0xffff;
    MoveSlot__16CmdFormationTeamFP12CmdFormationi(param_1 + 0x728,param_1,1);
    SetButtonReport__12CmdFormationFi(param_1,1);
    puVar5 = PTR_SelectSlot__12CmdFormationFv_0050d998;
    uVar4 = DAT_0050d994;
    *(undefined4 *)(param_1 + 0x58) = _5080;
    *(undefined4 *)(param_1 + 0x5c) = uVar4;
    *(undefined **)(param_1 + 0x60) = puVar5;
    PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 100),2,0,0);
  }
  return 0;
}

/* JP: 0x0047ec10  CmdFormation::SelectSlot()   [SelectSlot__12CmdFormationFv]  size=0x430 */
undefined8 SelectSlot__12CmdFormationFv(int param_1)

{
  short sVar1;
  ushort uVar2;
  undefined *puVar3;
  long lVar4;
  undefined4 uVar5;
  
  uVar2 = *(ushort *)(*(int *)(param_1 + 0x10) + 0x48);
  if ((uVar2 & 0x2000) == 0) {
    if ((uVar2 & 0x4000) == 0) {
      if ((uVar2 & 0x1000) == 0) {
        lVar4 = 0;
        if ((uVar2 & 0x20) == 0) {
          if ((uVar2 & 0x80) != 0) {
            lVar4 = -1;
          }
        }
        else {
          lVar4 = 1;
        }
        if (lVar4 != 0) {
          MoveSlot__16CmdFormationTeamFP12CmdFormationi(param_1 + 0x728,param_1,lVar4);
          PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 100),0,0,0);
        }
      }
      else {
        ResetTeam__16CmdFormationTeamFP12CmdFormation(param_1 + 0x728,param_1);
      }
    }
    else {
      MoveSlot__16CmdFormationTeamFP12CmdFormationi(param_1 + 0x728,param_1,0);
      Blackout__18CmdFormationMemberFP12CmdFormationiPcPc
                (param_1 + 0x178,param_1,0xffffffffffffffff,0,0);
      SetButtonReport__12CmdFormationFi(param_1,0);
      puVar3 = PTR_SelectTeam__12CmdFormationFv_0050d9c8;
      uVar5 = DAT_0050d9c4;
      *(undefined4 *)(param_1 + 0x58) = _5177;
      *(undefined4 *)(param_1 + 0x5c) = uVar5;
      *(undefined **)(param_1 + 0x60) = puVar3;
      PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 100),3,0,0);
    }
  }
  else {
    uVar5 = 4;
    sVar1 = *(short *)(*(int *)(param_1 + 0xd30) + *(short *)(param_1 + 0xdca) * 0x598 +
                       *(short *)(param_1 + 0xdc8) * 0x60 + 0x326);
    if (sVar1 < 0) {
      lVar4 = GetPlace__10MenuWindowFiss(param_1 + 0x178,2,0,
                              *(char *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) +
                                        (char)*(undefined2 *)
                                               (*(int *)(param_1 + 0xd30) +
                                                *(short *)(param_1 + 0xdca) * 0x598 + 0x16) * 0x20 +
                                       0x95) + -1);
    }
    else {
      lVar4 = GetPlace__10MenuWindowFs(param_1 + 0x178,sVar1);
      if (-1 < (long)((ulong)*(byte *)((int)lVar4 + 0x21) << 0x3e)) {
        lVar4 = 0;
      }
    }
    if ((lVar4 != 0) ||
       (lVar4 = GetPlace__10MenuWindowFiss(param_1 + 0x178,2,0,0xffffffffffffffff), lVar4 != 0)) {
      Select__6CursorFP9MenuPlace(param_1 + 0x74,lVar4);
      Select__18CmdFormationMemberFP9MenuPlaceP9MenuPlace(param_1 + 0x178,lVar4,0);
      SetButtonReport__12CmdFormationFi(param_1,2);
      SetExplanation__7CmdNoteFPCce
                (*(undefined4 *)(param_1 + 0x6c),*(undefined4 *)(*(int *)(param_1 + 0x24) + 0x58));
      puVar3 = PTR_SelectMember__12CmdFormationFv_0050d9b8;
      uVar5 = DAT_0050d9b4;
      *(undefined4 *)(param_1 + 0x58) = _5172;
      *(undefined4 *)(param_1 + 0x5c) = uVar5;
      *(undefined **)(param_1 + 0x60) = puVar3;
      uVar5 = 2;
    }
    PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 100),uVar5,0,0);
  }
  return 0;
}

/* JP: 0x0047f040  CmdFormation::SelectMember()   [SelectMember__12CmdFormationFv]  size=0x250 */
undefined8 SelectMember__12CmdFormationFv(int param_1)

{
  ushort uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined *puVar4;
  undefined4 uVar5;
  
  uVar1 = *(ushort *)(*(int *)(param_1 + 0x10) + 0x48);
  iVar2 = *(int *)(param_1 + 0x160);
  if ((uVar1 & 0x6000) == 0) {
    if ((uVar1 & 0x10) == 0) {
      if ((uVar1 & 0x40) != 0) {
        MoveCursor__6CursorFi(param_1 + 0x74,2);
      }
    }
    else {
      MoveCursor__6CursorFi(param_1 + 0x74,1);
    }
    if (iVar2 != *(int *)(param_1 + 0x160)) {
      Select__18CmdFormationMemberFP9MenuPlaceP9MenuPlace
                (param_1 + 0x178,*(int *)(param_1 + 0x160),iVar2);
      PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 100),0,0,0);
    }
  }
  else {
    uVar5 = 3;
    if ((uVar1 & 0x2000) != 0) {
      UpdateSlot__16CmdFormationTeamFP12CmdFormations
                (param_1 + 0x728,param_1,*(undefined2 *)(iVar2 + 0x16));
      uVar5 = 2;
    }
    Select__18CmdFormationMemberFP9MenuPlaceP9MenuPlace(param_1 + 0x178,0,iVar2);
    UpdateScene__18CmdFormationMemberFP12CmdFormations
              (param_1 + 0x178,param_1,*(short *)(param_1 + 0xe50) + *(short *)(param_1 + 0xdca));
    ChoiceMember__16CmdFormationTeamFP12CmdFormation(param_1 + 0x728,param_1);
    SetButtonReport__12CmdFormationFi(param_1,1);
    puVar4 = PTR_SelectSlot__12CmdFormationFv_0050d9d8;
    uVar3 = DAT_0050d9d4;
    *(undefined4 *)(param_1 + 0x58) = _5234;
    *(undefined4 *)(param_1 + 0x5c) = uVar3;
    *(undefined **)(param_1 + 0x60) = puVar4;
    PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 100),uVar5,0,0);
  }
  return 0;
}

/* JP: 0x0047f290  CmdFormation::DisplayMessage()   [DisplayMessage__12CmdFormationFv]  size=0x1a8 */
undefined8 DisplayMessage__12CmdFormationFv(int param_1)

{
  int iVar1;
  bool bVar2;
  undefined4 uVar3;
  undefined *puVar4;
  long lVar5;
  
  if (*(char *)(param_1 + 0x21) == '\x01') {
    if ((*(char *)(*(int *)(param_1 + 0x170) + 0xa8) == '\x01') ||
       (*(char *)(*(int *)(param_1 + 0x170) + 0xa8) == '\0')) {
      bVar2 = true;
    }
    else {
      bVar2 = false;
    }
    if (bVar2) {
      (**(code **)(*(int *)(*(int *)(param_1 + 0x170) + 8) + 0xc))();
      *(undefined4 *)(param_1 + 0x170) = 0;
      *(undefined1 *)(param_1 + 0x21) = 0;
      puVar4 = PTR_SelectTeam__12CmdFormationFv_0050d9e8;
      uVar3 = DAT_0050d9e4;
      *(undefined4 *)(param_1 + 0x58) = _5273;
      *(undefined4 *)(param_1 + 0x5c) = uVar3;
      *(undefined **)(param_1 + 0x60) = puVar4;
    }
  }
  else if ((*(char *)(param_1 + 0x21) == '\0') &&
          (lVar5 = Run__14CmdNoteMessageFUs
                             (*(undefined4 *)(param_1 + 0x170),
                              *(undefined2 *)(*(int *)(param_1 + 0x10) + 0x48)), lVar5 != 0)) {
    iVar1 = *(int *)(param_1 + 0x170);
    Close__10MenuWindowFUci(iVar1,((ulong)*(byte *)(iVar1 + 0xb0) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x14));
    *(char *)(param_1 + 0x21) = *(char *)(param_1 + 0x21) + '\x01';
  }
  return 0;
}
