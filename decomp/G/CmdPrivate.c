/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdPrivate   functions: 17
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdPrivate.md).
 */

/* JP: 0x00448b40  CmdPrivate::CmdPrivate()   [__ct__10CmdPrivateFv]  size=0x4c */
int __ct__10CmdPrivateFv(int param_1)

{
  __ct__10CmdPCSceneFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__10CmdPrivate;
  *(undefined4 *)(param_1 + 0x88) = 0;
  *(undefined4 *)(param_1 + 0x8c) = 0;
  return param_1;
}

/* JP: 0x00448b90  CmdPrivate::~CmdPrivate()   [__dt__10CmdPrivateFv]  size=0xc4 */
int __dt__10CmdPrivateFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__10CmdPrivate;
    if (*(int *)(param_1 + 0x88) != 0) {
      (**(code **)(*(int *)(*(int *)(param_1 + 0x88) + 8) + 0x28))();
    }
    if (*(int *)(param_1 + 0x8c) != 0) {
      (**(code **)(*(int *)(*(int *)(param_1 + 0x8c) + 8) + 0xc))();
    }
    __dt__10CmdPCSceneFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x00448c60  CmdPrivate::GetReady()   [GetReady__10CmdPrivateFv]  size=0x30c */
undefined4 GetReady__10CmdPrivateFv(int param_1)

{
  short sVar1;
  int iVar2;
  undefined4 uVar3;
  undefined *puVar4;
  ushort uVar5;
  int iVar6;
  
  iVar2 = *(int *)(param_1 + 0x10);
  *(int *)(param_1 + 0x5c) = iVar2 + 0xb8;
  *(int *)(param_1 + 0x60) = iVar2 + 0x780;
  *(int *)(param_1 + 100) = iVar2 + 0x4e0;
  *(int *)(param_1 + 0x68) = iVar2 + 0xa60;
  *(int *)(param_1 + 0x6c) = iVar2 + 0x10f0;
  *(undefined4 *)(param_1 + 0x90) = *(undefined4 *)(iVar2 + 0x68);
  *(undefined4 *)(param_1 + 0x58) = sm_pSound__7MenuObj;
  iVar6 = Find__13MenuDataTableFs(iVar2 + 0x28,0x2e);
  *(int *)(param_1 + 0x94) = iVar6 + 0x10;
  sVar1 = *(short *)(iVar2 + 0x44);
  for (uVar5 = 2; (short)uVar5 < 0x18; uVar5 = uVar5 + 1) {
    Convert__13MenuDataTableFPUci(*(undefined4 *)((uint)uVar5 * 0xc + *(int *)(param_1 + 0x54) + 0x10),0);
  }
  *(undefined4 *)(param_1 + 0x74) = *(undefined4 *)(*(int *)(param_1 + 0x54) + 0x70);
  SetCommand__8CmdPartyFc(*(undefined4 *)(param_1 + 0x5c),0xfffffffffffffffe);
  *(int *)(param_1 + 0x18) = iVar2 + 0x3a0;
  *(undefined2 *)(*(int *)(param_1 + 0x18) + 0x32) = 0;
  *(short *)(*(int *)(param_1 + 0x18) + 0x16) = sVar1;
  *(undefined4 *)(param_1 + 0x70) = *(undefined4 *)(*(int *)(param_1 + 0x5c) + sVar1 * 4 + 0x10);
  UpdatePCInfo__10CmdPCSceneFsP11CmdPCStatus(param_1,1,0);
  UpdateMenu__10CmdPrivateFs(param_1,1);
  UpdateModel__10CmdPrivateFv(param_1);
  SetButtonReport__10CmdPrivateFv(param_1);
  *(byte *)(*(int *)(param_1 + 0x78) + 0x6a) = *(byte *)(*(int *)(param_1 + 0x78) + 0x6a) & 0xfe;
  *(byte *)(*(int *)(param_1 + 0x8c) + 0x12) = *(byte *)(*(int *)(param_1 + 0x8c) + 0x12) & 0xfe;
  puVar4 = PTR_Enter__10CmdPrivateFv_0050d350;
  uVar3 = DAT_0050d34c;
  *(undefined4 *)(param_1 + 0x7c) = _6260;
  *(undefined4 *)(param_1 + 0x80) = uVar3;
  *(undefined **)(param_1 + 0x84) = puVar4;
  *(byte *)(param_1 + 0x23) = *(byte *)(param_1 + 0x23) & 0x3f | 0x40;
  return 1;
}

/* JP: 0x00448f70  CmdPrivate::Run()   [Run__10CmdPrivateFv]  size=0x5c */
undefined8 Run__10CmdPrivateFv(int param_1)

{
  long lVar1;
  
  do {
    lVar1 = __ptmf_test(param_1 + 0x7c);
    if (lVar1 == 0) {
      return 0;
    }
    lVar1 = __ptmf_scall(param_1);
  } while (lVar1 != 0);
  return 0;
}

/* JP: 0x00448fd0  CmdPrivate::Enter()   [Enter__10CmdPrivateFv]  size=0x2f8 */
undefined8 Enter__10CmdPrivateFv(int param_1)

{
  char cVar1;
  int iVar2;
  bool bVar3;
  undefined4 uVar4;
  undefined *puVar5;
  undefined1 uVar6;
  undefined8 uVar7;
  
  cVar1 = *(char *)(param_1 + 0x21);
  if (cVar1 == '\0') {
    uVar7 = GetPlace__10MenuWindowFss(*(undefined4 *)(param_1 + 0x8c),0,0);
    SelectMenu__10CmdPrivateFP8MenuTextP8MenuText(param_1,uVar7,0);
    iVar2 = *(int *)(param_1 + 0x78);
    Open__10MenuWindowFUci(iVar2 + 0x58,*(byte *)(iVar2 + 0x108) & 7,
                    *(undefined4 *)(*(int *)(iVar2 + 0x8c) + 0x10));
    iVar2 = *(int *)(param_1 + 0x8c);
    Open__10MenuWindowFUci(iVar2,*(byte *)(iVar2 + 0xb0) & 7,*(undefined4 *)(*(int *)(iVar2 + 0x34) + 0x10)
                   );
    uVar6 = CreateBackGround__7CmdMenuFs(*(undefined4 *)(param_1 + 0x10),8);
    *(undefined1 *)(param_1 + 0x20) = uVar6;
    *(char *)(param_1 + 0x21) = *(char *)(param_1 + 0x21) + '\x01';
  }
  else if (cVar1 == '\x01') {
    if ((*(char *)(*(int *)(param_1 + 0x8c) + 0xa8) == '\x01') ||
       (*(char *)(*(int *)(param_1 + 0x8c) + 0xa8) == '\0')) {
      bVar3 = true;
    }
    else {
      bVar3 = false;
    }
    if (bVar3) {
      SetCursor__10CmdPrivateFc(param_1,0);
      *(char *)(param_1 + 0x21) = *(char *)(param_1 + 0x21) + '\x01';
    }
  }
  else if (cVar1 == '\x02') {
    if ((*(char *)(*(int *)(param_1 + 0x78) + 0x100) == '\x01') ||
       (*(char *)(*(int *)(param_1 + 0x78) + 0x100) == '\0')) {
      bVar3 = true;
    }
    else {
      bVar3 = false;
    }
    if (bVar3) {
      if ((*(char *)(*(int *)(param_1 + 0x8c) + 0xa8) == '\x01') ||
         (*(char *)(*(int *)(param_1 + 0x8c) + 0xa8) == '\0')) {
        bVar3 = true;
      }
      else {
        bVar3 = false;
      }
      if (bVar3) {
        if (*(char *)(param_1 + 0x20) != '\0') {
          DestroyBackGround__7CmdMenuFs(*(undefined4 *)(param_1 + 0x10),1);
          *(undefined1 *)(param_1 + 0x20) = 0;
        }
        Open__15CmdButtonReportFv(*(undefined4 *)(param_1 + 0x68));
        puVar5 = PTR_Exec__10CmdPrivateFv_0050d360;
        uVar4 = DAT_0050d35c;
        *(undefined4 *)(param_1 + 0x7c) = _6332;
        *(undefined4 *)(param_1 + 0x80) = uVar4;
        *(undefined **)(param_1 + 0x84) = puVar5;
        *(undefined1 *)(param_1 + 0x21) = 0;
        *(undefined1 *)(*(int *)(param_1 + 0x10) + 0x4e) = 1;
      }
    }
  }
  return 0;
}

/* JP: 0x004492d0  CmdPrivate::Exit()   [Exit__10CmdPrivateFv]  size=0x2bc */
undefined8 Exit__10CmdPrivateFv(int param_1)

{
  int iVar1;
  bool bVar2;
  
  if (*(char *)(param_1 + 0x21) == '\0') {
    (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x14) + 0x28))(*(int *)(param_1 + 0x10),0,0,6);
    Shutdown__6CursorFv(*(undefined4 *)(param_1 + 0x18));
    iVar1 = *(int *)(param_1 + 0x78);
    Close__10MenuWindowFUci(iVar1 + 0x58,((ulong)*(byte *)(iVar1 + 0x108) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar1 + 0x8c) + 0x14));
    iVar1 = *(int *)(param_1 + 0x8c);
    Close__10MenuWindowFUci(iVar1,((ulong)*(byte *)(iVar1 + 0xb0) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x14));
    iVar1 = *(int *)(param_1 + 0x68);
    Close__10MenuWindowFUci(iVar1 + 0x58,((ulong)*(byte *)(iVar1 + 0x108) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar1 + 0x8c) + 0x14));
    Close__10CmdElementFv(*(undefined4 *)(param_1 + 0x6c));
    iVar1 = *(int *)(param_1 + 0x60);
    Close__10MenuWindowFUci(iVar1 + 0x58,((ulong)*(byte *)(iVar1 + 0x108) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar1 + 0x8c) + 0x14));
    Destroy__16MenuModelManegerFUc(*(undefined4 *)(param_1 + 0x90),0);
    if (*(int *)(param_1 + 0x88) != 0) {
      (**(code **)(*(int *)(*(int *)(param_1 + 0x88) + 8) + 0x2c))();
    }
    *(char *)(param_1 + 0x21) = *(char *)(param_1 + 0x21) + '\x01';
  }
  else if (*(char *)(param_1 + 0x21) == '\x01') {
    if ((*(char *)(*(int *)(param_1 + 0x78) + 0x100) == '\x01') ||
       (*(char *)(*(int *)(param_1 + 0x78) + 0x100) == '\0')) {
      bVar2 = true;
    }
    else {
      bVar2 = false;
    }
    if (bVar2) {
      (**(code **)(*(int *)(*(int *)(param_1 + 0x78) + 8) + 0xc))();
      *(undefined4 *)(param_1 + 0x78) = 0;
      (**(code **)(*(int *)(*(int *)(param_1 + 0x8c) + 8) + 0xc))();
      *(undefined4 *)(param_1 + 0x8c) = 0;
      if (*(int *)(param_1 + 0x88) != 0) {
        (**(code **)(*(int *)(*(int *)(param_1 + 0x88) + 8) + 0x28))();
        *(undefined4 *)(param_1 + 0x88) = 0;
      }
      (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x14) + 0x24))(*(int *)(param_1 + 0x10),0);
      DestroyScene__4MenuFP9MenuSceneb(*(undefined4 *)(param_1 + 0x10),param_1,1);
    }
  }
  return 0;
}

/* JP: 0x00449590  CmdPrivate::Exec()   [Exec__10CmdPrivateFv]  size=0x4a4 */
undefined8 Exec__10CmdPrivateFv(int param_1)

{
  ushort uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined *puVar4;
  short sVar5;
  int iVar6;
  long lVar7;
  undefined4 uVar8;
  
  puVar4 = PTR_Exit__10CmdPrivateFv_0050d380;
  uVar8 = DAT_0050d37c;
  uVar1 = *(ushort *)(*(int *)(param_1 + 0x10) + 0x48);
  iVar2 = *(int *)(*(int *)(param_1 + 0x18) + 0xec);
  if ((uVar1 & 0x2000) == 0) {
    if ((uVar1 & 0x8000) == 0) {
      if ((uVar1 & 0x4000) != 0) {
        *(undefined4 *)(param_1 + 0x7c) = _6431;
        *(undefined4 *)(param_1 + 0x80) = uVar8;
        *(undefined **)(param_1 + 0x84) = puVar4;
        PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),3,0,0);
        return 0;
      }
      iVar6 = MoveVertical__9MenuSceneFi(param_1,0);
      if (iVar2 == iVar6) {
        lVar7 = ChengePC__10CmdPCSceneFv(param_1);
        if (lVar7 != 0) {
          SetCursor__10CmdPrivateFc
                    (param_1,*(undefined1 *)
                              (*(int *)(*(int *)(param_1 + 0x70) + 0x34) +
                              (int)*(short *)(*(int *)(param_1 + 0x18) + 0x32)));
          SelectMenu__10CmdPrivateFP8MenuTextP8MenuText
                    (param_1,*(undefined4 *)(*(int *)(param_1 + 0x18) + 0xec),iVar2);
          iVar2 = *(int *)(param_1 + 0x78);
          Open__10MenuWindowFUci(iVar2 + 0x58,*(byte *)(iVar2 + 0x108) & 7,
                          *(undefined4 *)(*(int *)(iVar2 + 0x8c) + 0x10));
          Open__10MenuWindowFUci(*(undefined4 *)(param_1 + 0x8c),
                          *(byte *)(*(int *)(param_1 + 0x78) + 0x108) & 7,
                          *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x78) + 0x8c) + 0x10));
        }
      }
      else {
        SelectMenu__10CmdPrivateFP8MenuTextP8MenuText(param_1,iVar6,iVar2);
        *(undefined2 *)(*(int *)(param_1 + 0x18) + 0x32) =
             *(undefined2 *)(*(int *)(*(int *)(param_1 + 0x18) + 0xec) + 0x16);
        PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),0,0,0);
      }
    }
    else {
      SetAction__13MenuModelPackFv(*(undefined4 *)(*(int *)(param_1 + 0x90) + 0x18));
    }
  }
  else if ((long)((ulong)*(byte *)(*(int *)(param_1 + 0x88) + 0x23) << 0x3a) < 0) {
    uVar8 = 4;
    sVar5 = (**(code **)(*(int *)(*(int *)(param_1 + 0x88) + 8) + 0x34))();
    *(short *)(param_1 + 0x1e) = sVar5;
    if (sVar5 != 0) {
      iVar2 = *(int *)(param_1 + 0x68);
      Close__10MenuWindowFUci(iVar2 + 0x58,((ulong)*(byte *)(iVar2 + 0x108) & 0x3f) >> 3,
                      *(undefined4 *)(*(int *)(iVar2 + 0x8c) + 0x14));
      if (*(short *)(param_1 + 0x1e) != 2) {
        Destroy__16MenuModelManegerFUc(*(undefined4 *)(param_1 + 0x90),0);
      }
      *(byte *)(*(int *)(param_1 + 0x90) + 0x46) = *(byte *)(*(int *)(param_1 + 0x90) + 0x46) & 0xfe
      ;
      uVar8 = 2;
    }
    puVar4 = PTR_EnterSubScene__10CmdPrivateFv_0050d370;
    uVar3 = DAT_0050d36c;
    *(undefined4 *)(param_1 + 0x7c) = _6423;
    *(undefined4 *)(param_1 + 0x80) = uVar3;
    *(undefined **)(param_1 + 0x84) = puVar4;
    PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),uVar8,0,0);
  }
  if (*(int *)(param_1 + 0x88) != 0) {
    (**(code **)(*(int *)(*(int *)(param_1 + 0x88) + 8) + 0x3c))();
  }
  return 0;
}

/* JP: 0x00449a40  CmdPrivate::EnterSubScene()   [EnterSubScene__10CmdPrivateFv]  size=0x114 */
undefined8 EnterSubScene__10CmdPrivateFv(int param_1)

{
  bool bVar1;
  undefined4 uVar2;
  undefined *puVar3;
  
  if ((*(char *)(*(int *)(param_1 + 0x8c) + 0xa8) == '\x01') ||
     (*(char *)(*(int *)(param_1 + 0x8c) + 0xa8) == '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if (bVar1) {
    if (*(char *)(*(int *)(param_1 + 0x8c) + 0xa8) == '\0') {
      (**(code **)(*(int *)(*(int *)(param_1 + 0x8c) + 8) + 0xc))();
      *(undefined4 *)(param_1 + 0x8c) = 0;
    }
    puVar3 = PTR_ExecSubScene__10CmdPrivateFv_0050d390;
    uVar2 = DAT_0050d38c;
    *(undefined4 *)(param_1 + 0x7c) = _6531;
    *(undefined4 *)(param_1 + 0x80) = uVar2;
    *(undefined **)(param_1 + 0x84) = puVar3;
  }
  return 0;
}

/* JP: 0x00449b60  CmdPrivate::ExitSubScene()   [ExitSubScene__10CmdPrivateFv]  size=0x138 */
undefined8 ExitSubScene__10CmdPrivateFv(int param_1)

{
  bool bVar1;
  undefined4 uVar2;
  undefined *puVar3;
  
  if ((*(char *)(*(int *)(param_1 + 0x8c) + 0xa8) == '\x01') ||
     (*(char *)(*(int *)(param_1 + 0x8c) + 0xa8) == '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if (bVar1) {
    if (*(short *)(param_1 + 0x1e) != 0) {
      Restore__6CursorFv(*(undefined4 *)(param_1 + 0x18));
      SetButtonReport__10CmdPrivateFv(param_1);
      Open__15CmdButtonReportFv(*(undefined4 *)(param_1 + 0x68));
      UpdateModel__10CmdPrivateFv(param_1);
      *(byte *)(*(int *)(param_1 + 0x90) + 0x46) =
           *(byte *)(*(int *)(param_1 + 0x90) + 0x46) & 0xfe | 1;
    }
    SetChengePCMode__10CmdPCSceneFUc(param_1,1);
    puVar3 = PTR_Exec__10CmdPrivateFv_0050d3a0;
    uVar2 = DAT_0050d39c;
    *(undefined4 *)(param_1 + 0x7c) = _6555;
    *(undefined4 *)(param_1 + 0x80) = uVar2;
    *(undefined **)(param_1 + 0x84) = puVar3;
  }
  return 0;
}

/* JP: 0x00449ca0  CmdPrivate::ExecSubScene()   [ExecSubScene__10CmdPrivateFv]  size=0x1d0 */
undefined8 ExecSubScene__10CmdPrivateFv(int param_1)

{
  bool bVar1;
  undefined4 uVar2;
  undefined *puVar3;
  long lVar4;
  
  if ((*(byte *)(param_1 + 0x23) >> 6 == 0) ||
     (lVar4 = ChengePC__10CmdPCSceneFv(param_1), lVar4 == 0)) {
    if (*(int *)(param_1 + 0x78) != 0) {
      if ((*(char *)(*(int *)(param_1 + 0x78) + 0x100) == '\x01') ||
         (*(char *)(*(int *)(param_1 + 0x78) + 0x100) == '\0')) {
        bVar1 = true;
      }
      else {
        bVar1 = false;
      }
      if (!bVar1) {
        *(undefined2 *)(*(int *)(param_1 + 0x10) + 0x48) = 0;
      }
    }
    lVar4 = (**(code **)(*(int *)(*(int *)(param_1 + 0x88) + 8) + 0x1c))();
    if (lVar4 != 0) {
      (**(code **)(*(int *)(*(int *)(param_1 + 0x88) + 8) + 0x38))();
      SetCursor__10CmdPrivateFc
                (param_1,*(undefined1 *)
                          (*(int *)(*(int *)(param_1 + 0x70) + 0x34) +
                          (int)*(short *)(*(int *)(param_1 + 0x18) + 0x32)));
      puVar3 = PTR_ExitSubScene__10CmdPrivateFv_0050d3b0;
      uVar2 = DAT_0050d3ac;
      *(undefined4 *)(param_1 + 0x7c) = _6580;
      *(undefined4 *)(param_1 + 0x80) = uVar2;
      *(undefined **)(param_1 + 0x84) = puVar3;
    }
  }
  return 0;
}

/* JP: 0x00449e70  CmdPrivate::CreateScene(short)   [CreateScene__10CmdPrivateFs]  size=0x45c */
undefined4 CreateScene__10CmdPrivateFs(int param_1,ushort param_2)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  long lVar5;
  
  iVar3 = *(int *)(param_1 + 0x88);
  if (iVar3 != 0) {
    if (param_2 == *(ushort *)(iVar3 + 0x1c)) {
      return 1;
    }
    (**(code **)(*(int *)(iVar3 + 8) + 0x28))();
    *(undefined4 *)(param_1 + 0x88) = 0;
  }
  iVar3 = *(int *)(param_1 + 0x88);
  if (iVar3 == 0) {
    uVar1 = *(ushort *)((uint)param_2 * 0xc + *(int *)(param_1 + 0x28) + 0x18) & 0xff;
    switch(uVar1) {
    case 0:
      iVar2 = __nw__FUi(0xf28);
      iVar3 = 0;
      if (iVar2 != 0) {
        iVar3 = __ct__9CmdStatusFv(iVar2);
      }
      break;
    case 1:
      lVar5 = __nw__FUi(200);
      iVar3 = 0;
      if (lVar5 != 0) {
        iVar3 = __ct__9CmdFusionFv(lVar5);
      }
      break;
    case 2:
      lVar5 = __nw__FUi(0x84);
      iVar3 = 0;
      if (lVar5 != 0) {
        iVar3 = __ct__8CmdSwordFv(lVar5);
      }
      break;
    case 3:
      lVar5 = __nw__FUi(0x78);
      iVar3 = 0;
      if (lVar5 != 0) {
        iVar3 = __ct__10CmdClothesFv(lVar5);
      }
      break;
    case 4:
      lVar5 = __nw__FUi(0x90);
      iVar3 = 0;
      if (lVar5 != 0) {
        iVar3 = __ct__11CmdWolfBoutFv(lVar5);
      }
      break;
    case 5:
      lVar5 = __nw__FUi(0x318);
      iVar3 = 0;
      if (lVar5 != 0) {
        iVar3 = __ct__8CmdTarotFv(lVar5);
      }
      break;
    case 6:
      lVar5 = __nw__FUi(0x520);
      iVar3 = 0;
      if (lVar5 != 0) {
        iVar3 = __ct__8CmdAromaFv(lVar5);
      }
      break;
    default:
      return 0;
    case 8:
      lVar5 = __nw__FUi(0x354);
      iVar3 = 0;
      if (lVar5 != 0) {
        iVar3 = __ct__13CmdPhotographFv(lVar5);
      }
      break;
    case 9:
      iVar2 = __nw__FUi(0x8c);
      iVar3 = 0;
      if (iVar2 != 0) {
        iVar3 = __ct__12CmdTechniqueFv(iVar2);
      }
      break;
    case 10:
      iVar2 = __nw__FUi(0x15c);
      iVar3 = 0;
      if (iVar2 != 0) {
        iVar3 = __ct__13CmdFriendshipFv(iVar2);
      }
      break;
    case 0xb:
      lVar5 = __nw__FUi(0x58c);
      iVar3 = 0;
      if (lVar5 != 0) {
        iVar3 = __ct__10CmdProfileFv(lVar5);
      }
    }
    *(ushort *)(iVar3 + 0x1c) = param_2;
    *(undefined4 *)(iVar3 + 0x10) = *(undefined4 *)(param_1 + 0x10);
    *(int *)(iVar3 + 0x58) = param_1;
    puVar4 = (undefined4 *)FindAttachFile__9MenuSceneCFs(param_1,uVar1);
    Initialize__9MenuSceneFPUcP9BufMemory(iVar3,*puVar4,0);
    *(int *)(param_1 + 0x88) = iVar3;
  }
  (**(code **)(*(int *)(iVar3 + 8) + 0x30))(iVar3,1);
  return 1;
}

/* JP: 0x0044a2d0  CmdPrivate::UpdateMenu(short)   [UpdateMenu__10CmdPrivateFs]  size=0x10c */
void UpdateMenu__10CmdPrivateFs(int param_1,short param_2)

{
  int iVar1;
  undefined4 uVar2;
  long lVar3;
  
  if (*(int *)(param_1 + 0x8c) == 0) {
    lVar3 = __nw__FUi(0x374);
    uVar2 = 0;
    if (lVar3 != 0) {
      uVar2 = __ct__14CmdPrivateMenuFv(lVar3);
    }
    *(undefined4 *)(param_1 + 0x8c) = uVar2;
    CreateScene__14CmdPrivateMenuFP10CmdPrivate(*(undefined4 *)(param_1 + 0x8c),param_1);
  }
  UpdateScene__14CmdPrivateMenuFP10CmdPrivate(*(undefined4 *)(param_1 + 0x8c),param_1);
  if (param_2 == 0) {
    *(byte *)(*(int *)(param_1 + 0x8c) + 0x12) =
         *(byte *)(*(int *)(param_1 + 0x8c) + 0x12) & 0xfe | 1;
  }
  else {
    iVar1 = *(int *)(param_1 + 0x8c);
    Open__10MenuWindowFUci(iVar1,*(byte *)(iVar1 + 0xb0) & 7,*(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x10)
                   );
  }
  return;
}

/* JP: 0x0044a3e0  CmdPrivate::UpdateModel()   [UpdateModel__10CmdPrivateFv]  size=0x354 */
void UpdateModel__10CmdPrivateFv(int param_1)

{
  undefined2 uVar1;
  int *piVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  short sVar6;
  ulong unaff_s6;
  
  piVar2 = *(int **)(param_1 + 0x70);
  uVar1 = *(undefined2 *)((int)piVar2 + 0x42);
  iVar3 = *(int *)(param_1 + 0x90);
  Reset__16MenuModelManegerFv(iVar3);
  *(undefined2 *)(iVar3 + 0x68) = uVar1;
  iVar5 = *(int *)(iVar3 + 0x18);
  *(undefined4 *)(iVar5 + 0x10) = *(undefined4 *)(param_1 + 0x94);
  *(int *)(iVar5 + 0x14) = *(int *)(param_1 + 0x94) + 0x10;
  if (-1 < *(char *)(*piVar2 + 0x2d)) {
    *(byte *)(iVar5 + 0x66) = (byte)(((ulong)*(byte *)(*piVar2 + 0x58) << 0x3a) >> 0x3d);
    uVar4 = *(undefined4 *)(*(int *)(param_1 + 0x24) + 0x20);
    *(undefined2 *)(iVar3 + 0x3c) = uVar1;
    *(undefined4 *)(iVar3 + 0x24) = uVar4;
    uVar4 = *(undefined4 *)(*(int *)(param_1 + 0x24) + 0x28);
    *(undefined2 *)(iVar3 + 0x3e) = uVar1;
    *(undefined4 *)(iVar3 + 0x28) = uVar4;
    if (*(char *)(*piVar2 + 2) == '\x02') {
      iVar5 = GetRegDat__9RegDatApiFiii(0x35,*(undefined1 *)(*(int *)(*(int *)(param_1 + 0x5c) + 4) + 0xdaa),
                              0xffffffffffffffff);
      uVar1 = *(undefined2 *)(iVar5 + 4);
      uVar4 = *(undefined4 *)(*(int *)(param_1 + 0x24) + 0x40);
      *(undefined2 *)(iVar3 + 0x38) = uVar1;
      *(undefined4 *)(iVar3 + 0x1c) = uVar4;
      uVar4 = *(undefined4 *)(*(int *)(param_1 + 0x24) + 0x48);
      *(undefined2 *)(iVar3 + 0x3a) = uVar1;
      *(undefined4 *)(iVar3 + 0x20) = uVar4;
      unaff_s6 = (ulong)*(byte *)(iVar5 + 6) & 7;
    }
    else {
      iVar5 = GetRegDat__9RegDatApiFiii(0x30,*(undefined1 *)(*piVar2 + 0x2d),0xffffffffffffffff);
      sVar6 = *(short *)(iVar5 + 4);
      if (99 < sVar6) {
        sVar6 = sVar6 + -100;
        uVar4 = *(undefined4 *)(*(int *)(param_1 + 0x24) + 0x38);
        *(short *)(iVar3 + 0x3a) = sVar6;
        *(undefined4 *)(iVar3 + 0x20) = uVar4;
      }
      uVar4 = *(undefined4 *)(*(int *)(param_1 + 0x24) + 0x30);
      *(short *)(iVar3 + 0x38) = sVar6;
      *(undefined4 *)(iVar3 + 0x1c) = uVar4;
      unaff_s6 = ((ulong)*(byte *)*piVar2 & 0x1f) >> 2;
    }
  }
  SetCamera__7CmdMenuFP13MenuDataModel
            (*(undefined4 *)(param_1 + 0x10),*(undefined4 *)(piVar2[1] + 0x24));
  Create__10CmdElementFUc(*(undefined4 *)(param_1 + 0x6c),unaff_s6);
  Open__10CmdElementFv(*(undefined4 *)(param_1 + 0x6c));
  Access__16MenuModelManegerFv(iVar3);
  return;
}

/* JP: 0x0044a740  CmdPrivate::SelectMenu(MenuText*, MenuText*)   [SelectMenu__10CmdPrivateFP8MenuTextP8MenuText]  size=0x16c */
void SelectMenu__10CmdPrivateFP8MenuTextP8MenuText(int param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
  
  if (param_3 != 0) {
    SetCSA__8FontItemFUc(param_3,0);
  }
  if (param_2 != 0) {
    iVar2 = (uint)*(ushort *)(param_2 + 0x22) * 0xc + *(int *)(param_1 + 0x28);
    uVar1 = *(undefined4 *)(param_1 + 100);
    SetCSA__8FontItemFUc(param_2,1);
    if (((long)*(short *)(iVar2 + 0x18) & 0xff00U) == 0) {
      SetExplanation__7CmdNoteFPCce(uVar1,*(undefined4 *)(iVar2 + 0x14));
    }
    else {
      SetExplanation__7CmdNoteFPCce
                (uVar1,*(undefined4 *)(iVar2 + 0x14),**(int **)(param_1 + 0x70) + 10);
    }
    CreateScene__10CmdPrivateFs(param_1,*(undefined2 *)(param_2 + 0x22));
  }
  return;
}

/* JP: 0x0044a8b0  CmdPrivate::Update(short)   [Update__10CmdPrivateFs]  size=0xc4 */
void Update__10CmdPrivateFs(int param_1,undefined2 param_2)

{
  if (*(int *)(param_1 + 0x78) != 0) {
    UpdatePCInfo__10CmdPCSceneFsP11CmdPCStatus(param_1,param_2,0);
  }
  if (*(int *)(param_1 + 0x8c) != 0) {
    UpdateMenu__10CmdPrivateFs(param_1,param_2);
  }
  if (*(int *)(param_1 + 0x88) != 0) {
    (**(code **)(*(int *)(*(int *)(param_1 + 0x88) + 8) + 0x30))(*(int *)(param_1 + 0x88),param_2);
  }
  if ((*(byte *)(*(int *)(param_1 + 0x90) + 0x46) & 1) != 0) {
    UpdateModel__10CmdPrivateFv(param_1);
  }
  return;
}

/* JP: 0x0044a980  CmdPrivate::SetCursor(char)   [SetCursor__10CmdPrivateFc]  size=0xcc */
void SetCursor__10CmdPrivateFc(int param_1,char param_2)

{
  uint uVar1;
  
  for (uVar1 = *(int *)(param_1 + 0x8c) + 0xf4;
      (uVar1 < *(int *)(param_1 + 0x8c) + 0x374U &&
      (((*(byte *)(uVar1 + 0x12) & 1) == 0 || ((long)param_2 != (long)*(short *)(uVar1 + 0x22)))));
      uVar1 = uVar1 + 0x80) {
  }
  Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),uVar1);
  SelectMenu__10CmdPrivateFP8MenuTextP8MenuText(param_1,uVar1,0);
  return;
}

/* JP: 0x0044aa50  CmdPrivate::SetButtonReport()   [SetButtonReport__10CmdPrivateFv]  size=0x5c */
void SetButtonReport__10CmdPrivateFv(int param_1)

{
  ClearReport__15CmdButtonReportFv(*(undefined4 *)(param_1 + 0x68));
  SetReport__15CmdButtonReportFii(*(undefined4 *)(param_1 + 0x68),0,0xc);
  SetReport__15CmdButtonReportFii(*(undefined4 *)(param_1 + 0x68),1,7);
  return;
}
