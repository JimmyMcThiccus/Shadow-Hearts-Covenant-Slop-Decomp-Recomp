/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdMagic   functions: 10
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdMagic.md).
 */

/* JP: 0x0048d2b0  CmdMagic::CmdMagic()   [__ct__8CmdMagicFv]  size=0x6c */
int __ct__8CmdMagicFv(int param_1)

{
  __ct__10CmdPCSceneFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__8CmdMagic;
  __ct__13CmdMagicGoodsFv(param_1 + 0x88);
  __ct__11CmdSubTitleFv(param_1 + 0x180);
  *(undefined4 *)(param_1 + 0x354) = 0;
  *(undefined4 *)(param_1 + 0x364) = 0;
  return param_1;
}

/* JP: 0x0048d320  CmdMagic::~CmdMagic()   [__dt__8CmdMagicFv]  size=0xe4 */
int __dt__8CmdMagicFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__8CmdMagic;
    if (*(int *)(param_1 + 0x364) != 0) {
      __dla__FPv(*(undefined4 *)(param_1 + 0x364));
    }
    if (*(int *)(param_1 + 0x354) != 0) {
      (**(code **)(*(int *)(*(int *)(param_1 + 0x354) + 8) + 0xc))();
    }
    __dt__11CmdSubTitleFv(param_1 + 0x180,0xffffffffffffffff);
    __dt__13CmdMagicGoodsFv(param_1 + 0x88,0xffffffffffffffff);
    __dt__10CmdPCSceneFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x0048d410  CmdMagic::GetReady()   [GetReady__8CmdMagicFv]  size=0x308 */
undefined4 GetReady__8CmdMagicFv(int param_1)

{
  int iVar1;
  undefined *puVar2;
  undefined2 uVar3;
  short sVar4;
  undefined4 uVar5;
  int iVar6;
  long lVar7;
  uint uVar8;
  undefined1 auStack_80 [100];
  int iStack_1c;
  int iStack_18;
  undefined4 uStack_14;
  int iStack_10;
  
  iVar1 = *(int *)(param_1 + 0x10);
  iStack_10 = param_1;
  __ct__9MenuSceneFv(auStack_80);
  uVar3 = GetRegCnt__9RegDatApiFii(0x38,0xffffffffffffffff);
  *(undefined2 *)(iStack_10 + 0x360) = uVar3;
  uVar5 = GetRegDat__9RegDatApiFiii(0x38,0,0xffffffffffffffff);
  *(undefined4 *)(iStack_10 + 0x358) = uVar5;
  iStack_18 = iVar1 + 0x28;
  iVar6 = Find__13MenuDataTableFs(iStack_18,0xc);
  *(undefined2 *)(iStack_10 + 0x362) = *(undefined2 *)(iVar6 + 4);
  *(int *)(iStack_10 + 0x35c) = iVar6 + 0x10;
  uVar5 = __nwa__FUi(*(undefined2 *)(iStack_10 + 0x360));
  *(undefined4 *)(iStack_10 + 0x364) = uVar5;
  iStack_1c = iVar1 + 0xa60;
  *(int *)(iStack_10 + 0x348) = iStack_1c;
  for (uVar8 = 1; (int)uVar8 < 6; uVar8 = uVar8 + 1) {
    Convert__13MenuDataTableFPUci(*(undefined4 *)((uVar8 & 0xffff) * 0xc + *(int *)(iStack_10 + 0x54) + 0x10),0);
  }
  CreatePCInfo__10CmdPCSceneFPUc(iStack_10,*(undefined4 *)(*(int *)(iStack_10 + 0x54) + 0x1c));
  *(undefined2 *)(*(int *)(iStack_10 + 0x18) + 0x32) = 0;
  sVar4 = GetLayerCount__10CmdPCSceneFs(iStack_10,0);
  if (sVar4 < 2) {
    *(byte *)(iStack_10 + 0x23) = *(byte *)(iStack_10 + 0x23) & 0xfe;
  }
  SetChengePCMode__10CmdPCSceneFUc(iStack_10,0);
  CreateScene__13CmdMagicGoodsFP8CmdMagic(iStack_10 + 0x88,iStack_10);
  Initialize__9MenuSceneFPUcP9BufMemory(iStack_10 + 0x180,*(undefined4 *)(*(int *)(iStack_10 + 0x54) + 0x28),0);
  Create__11CmdSubTitleFi(iStack_10 + 0x180,1);
  Reset__11CmdSubTitleFv(iStack_10 + 0x180);
  SetTitle__11CmdSubTitleFii(iStack_10 + 0x180,0,0);
  Initialize__9MenuSceneFPUcP9BufMemory(auStack_80,*(undefined4 *)(*(int *)(iStack_10 + 0x54) + 0x4c),0);
  lVar7 = __nw__FUi(0x178);
  uVar5 = 0;
  if (lVar7 != 0) {
    uVar5 = __ct__8CmdFenceFv(lVar7);
  }
  *(undefined4 *)(iStack_10 + 0x354) = uVar5;
  CreateFence__8CmdFenceFP9MenuScenePUc(*(undefined4 *)(iStack_10 + 0x354),auStack_80,0);
  puVar2 = PTR_Enter__8CmdMagicFv_0050db48;
  uVar5 = DAT_0050db44;
  *(undefined4 *)(iStack_10 + 0x7c) = _5077;
  *(undefined4 *)(iStack_10 + 0x80) = uVar5;
  *(undefined **)(iStack_10 + 0x84) = puVar2;
  uStack_14 = 1;
  __dt__9MenuSceneFv(auStack_80,0xffffffffffffffff);
  return uStack_14;
}

/* JP: 0x0048d720  CmdMagic::Run()   [Run__8CmdMagicFv]  size=0x104 */
undefined4 Run__8CmdMagicFv(int param_1)

{
  bool bVar1;
  long lVar2;
  
  lVar2 = ChengePC__10CmdPCSceneFv(param_1);
  if (lVar2 == 0) {
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
    lVar2 = __ptmf_test(param_1 + 0x7c);
    if ((lVar2 != 0) && (lVar2 = __ptmf_scall(param_1), lVar2 == 0)) {
      return 0;
    }
  }
  return 1;
}

/* JP: 0x0048d830  CmdMagic::Update(short)   [Update__8CmdMagicFs]  size=0x20c */
void Update__8CmdMagicFs(int param_1)

{
  int iVar1;
  ulong uVar2;
  
  iVar1 = *(int *)(*(int *)(param_1 + 0x18) + 0xec);
  Leave__6CursorFv(*(undefined4 *)(param_1 + 0x18));
  CreateMagic__5CmdPCFP8CmdPartysPc
            (*(undefined4 *)(param_1 + 0x70),*(undefined4 *)(param_1 + 0x5c),
             *(undefined2 *)(param_1 + 0x360),*(undefined4 *)(param_1 + 0x364));
  UpdateScene__13CmdMagicGoodsFP8CmdMagicPc(param_1 + 0x88,param_1,*(undefined4 *)(param_1 + 0x364))
  ;
  Open__10MenuWindowFUci(param_1 + 0x88,*(byte *)(param_1 + 0x138) & 7,
                  *(undefined4 *)(*(int *)(param_1 + 0xbc) + 0x10));
  UpdatePCInfo__10CmdPCSceneFsP11CmdPCStatus(param_1,1,0);
  ClearReport__15CmdButtonReportFv(*(undefined4 *)(param_1 + 0x348));
  if (*(int *)(param_1 + 0xcc) == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = ((ulong)*(ushort *)(param_1 + 0x13a) & 0x3ff) >> 2;
  }
  if (uVar2 != 0) {
    SetReport__15CmdButtonReportFii
              (*(int *)(param_1 + 0x348),*(undefined1 *)(*(int *)(param_1 + 0x348) + 0x20),0xd);
  }
  SetReport__15CmdButtonReportFii
            (*(int *)(param_1 + 0x348),*(undefined1 *)(*(int *)(param_1 + 0x348) + 0x20),6);
  if (iVar1 != 0) {
    SetCursor__10MenuWindowFP6Cursori(param_1 + 0x88,*(undefined4 *)(param_1 + 0x18),2);
    Select__13CmdMagicGoodsFP8CmdMagicP9MenuGroupP9MenuGroups
              (param_1 + 0x88,param_1,*(undefined4 *)(*(int *)(param_1 + 0x18) + 0xec),0,1);
  }
  return;
}

/* JP: 0x0048da40  CmdMagic::Enter()   [Enter__8CmdMagicFv]  size=0x274 */
undefined8 Enter__8CmdMagicFv(int param_1)

{
  int iVar1;
  bool bVar2;
  undefined4 uVar3;
  undefined *puVar4;
  undefined1 uVar5;
  undefined8 uVar6;
  
  if (*(char *)(param_1 + 0x21) == '\0') {
    (**(code **)(*(int *)(param_1 + 8) + 0x28))(param_1,1);
    uVar6 = GetPlace__10MenuWindowFss(param_1 + 0x88,0,0);
    Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),uVar6);
    Select__13CmdMagicGoodsFP8CmdMagicP9MenuGroupP9MenuGroups(param_1 + 0x88,param_1,uVar6,0,1);
    Open__10MenuWindowFUci(param_1 + 0x1d8,*(byte *)(param_1 + 0x288) & 7,
                    *(undefined4 *)(*(int *)(param_1 + 0x20c) + 0x10));
    Open__10CmdElementFv(*(undefined4 *)(param_1 + 0x6c));
    Open__15CmdButtonReportFv(*(undefined4 *)(param_1 + 0x348));
    iVar1 = *(int *)(param_1 + 0x354);
    Open__10MenuWindowFUci(iVar1,*(byte *)(iVar1 + 0xb0) & 7,*(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x10)
                   );
    SetTitle__11CmdTitleLogFPUci
              (*(undefined4 *)(param_1 + 0x60),*(undefined4 *)(*(int *)(param_1 + 0x54) + 0x10),0xd)
    ;
    Open__11CmdTitleLogFv(*(undefined4 *)(param_1 + 0x60));
    uVar5 = CreateBackGround__7CmdMenuFs(*(undefined4 *)(param_1 + 0x10),8);
    *(undefined1 *)(param_1 + 0x20) = uVar5;
    *(char *)(param_1 + 0x21) = *(char *)(param_1 + 0x21) + '\x01';
  }
  else if (*(char *)(param_1 + 0x21) == '\x01') {
    if ((*(char *)(param_1 + 0x130) == '\x01') || (*(char *)(param_1 + 0x130) == '\0')) {
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
      SetChengePCMode__10CmdPCSceneFUc(param_1,1);
      *(undefined1 *)(param_1 + 0x21) = 0;
      puVar4 = PTR_SelectGoods__8CmdMagicFv_0050db58;
      uVar3 = DAT_0050db54;
      *(undefined4 *)(param_1 + 0x7c) = _5169;
      *(undefined4 *)(param_1 + 0x80) = uVar3;
      *(undefined **)(param_1 + 0x84) = puVar4;
    }
  }
  return 0;
}

/* JP: 0x0048dcc0  CmdMagic::Exit()   [Exit__8CmdMagicFv]  size=0x280 */
undefined8 Exit__8CmdMagicFv(int param_1)

{
  int iVar1;
  bool bVar2;
  
  if (*(char *)(param_1 + 0x21) == '\0') {
    (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x14) + 0x28))(*(int *)(param_1 + 0x10),0,0,2);
    Leave__6CursorFv(*(undefined4 *)(param_1 + 0x18));
    Close__10MenuWindowFUci(param_1 + 0x88,((ulong)*(byte *)(param_1 + 0x138) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(param_1 + 0xbc) + 0x14));
    Close__10MenuWindowFUci(param_1 + 0x1d8,((ulong)*(byte *)(param_1 + 0x288) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(param_1 + 0x20c) + 0x14));
    iVar1 = *(int *)(param_1 + 0x60);
    Close__10MenuWindowFUci(iVar1 + 0x58,((ulong)*(byte *)(iVar1 + 0x108) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar1 + 0x8c) + 0x14));
    iVar1 = *(int *)(param_1 + 0x78);
    Close__10MenuWindowFUci(iVar1 + 0x58,((ulong)*(byte *)(iVar1 + 0x108) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar1 + 0x8c) + 0x14));
    Close__10CmdElementFv(*(undefined4 *)(param_1 + 0x6c));
    iVar1 = *(int *)(param_1 + 0x348);
    Close__10MenuWindowFUci(iVar1 + 0x58,((ulong)*(byte *)(iVar1 + 0x108) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar1 + 0x8c) + 0x14));
    iVar1 = *(int *)(param_1 + 0x354);
    Close__10MenuWindowFUci(iVar1,((ulong)*(byte *)(iVar1 + 0xb0) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x14));
    *(char *)(param_1 + 0x21) = *(char *)(param_1 + 0x21) + '\x01';
  }
  else if (*(char *)(param_1 + 0x21) == '\x01') {
    if ((*(char *)(param_1 + 0x130) == '\x01') || (*(char *)(param_1 + 0x130) == '\0')) {
      bVar2 = true;
    }
    else {
      bVar2 = false;
    }
    if (bVar2) {
      ReleaseOT__7MenuObjFv(param_1 + 0x88);
      ReleaseOT__7MenuObjFv(param_1 + 0x1d8);
      (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x14) + 0x24))(*(int *)(param_1 + 0x10),0);
      DestroyScene__4MenuFP9MenuSceneb(*(undefined4 *)(param_1 + 0x10),param_1,1);
    }
  }
  return 0;
}

/* JP: 0x0048df40  CmdMagic::SelectGoods()   [SelectGoods__8CmdMagicFv]  size=0x600 */
undefined8 SelectGoods__8CmdMagicFv(int param_1)

{
  short sVar1;
  ushort uVar2;
  int iVar3;
  bool bVar4;
  undefined4 uVar5;
  undefined *puVar6;
  int iVar7;
  int iVar8;
  long lVar9;
  undefined8 uVar10;
  int iVar11;
  int iVar12;
  undefined4 uStack_24;
  
  uVar2 = *(ushort *)(*(int *)(param_1 + 0x10) + 0x48);
  iVar11 = *(int *)(*(int *)(param_1 + 0x18) + 0xec);
  if ((uVar2 & 0x2000) != 0) {
    if ((*(char *)(param_1 + 0x130) == '\x01') || (*(char *)(param_1 + 0x130) == '\0')) {
      bVar4 = true;
    }
    else {
      bVar4 = false;
    }
    if (bVar4) {
      uStack_24 = 4;
      if ((long)((ulong)*(byte *)(iVar11 + 0x21) << 0x3c) < 0) {
        lVar9 = __nw__FUi(0xaa0);
        iVar7 = 0;
        if (lVar9 != 0) {
          iVar7 = __ct__15CmdSelectTargetFv(lVar9);
        }
        *(int *)(param_1 + 0x34c) = iVar7;
        sVar1 = *(short *)(iVar11 + 0x16);
        iVar3 = *(int *)(param_1 + 0x34c);
        iVar8 = *(int *)(param_1 + 0x358) + sVar1 * 0x44;
        iVar12 = *(int *)(param_1 + 0x35c) + sVar1 * 0x14;
        *(short *)(iVar3 + 0x5c) = sVar1;
        *(undefined2 *)(iVar3 + 0x5e) = 2;
        *(byte *)(iVar3 + 0x61) = (byte)(((ulong)*(byte *)(iVar8 + 5) << 0x3c) >> 0x3d);
        *(byte *)(iVar3 + 0x60) = (byte)(((ulong)*(ushort *)(iVar8 + 4) << 0x37) >> 0x3e);
        *(undefined2 *)(iVar3 + 0x62) = 0;
        *(int *)(iVar3 + 100) = iVar8 + 8;
        *(undefined4 *)(iVar3 + 0x68) = *(undefined4 *)(iVar12 + 4);
        *(undefined4 *)(iVar3 + 0x6c) = *(undefined4 *)(iVar12 + 8);
        *(int *)(iVar3 + 0x70) = iVar11;
        *(undefined4 *)(iVar7 + 0x10) = *(undefined4 *)(param_1 + 0x10);
        Initialize__9MenuSceneFPUcP9BufMemory(iVar7,*(undefined4 *)(*(int *)(param_1 + 0x54) + 0x34),0);
        *(byte *)(*(int *)(param_1 + 0xcc) + 0x12) =
             *(byte *)(*(int *)(param_1 + 0xcc) + 0x12) & 0xfe;
        SetChengePCMode__10CmdPCSceneFUc(param_1,0);
        Shutdown__4MenuFv(*(undefined4 *)(param_1 + 0x10));
        Close__10CmdElementFv(*(undefined4 *)(param_1 + 0x6c));
        iVar11 = *(int *)(param_1 + 0x348);
        Close__10MenuWindowFUci(iVar11 + 0x58,((ulong)*(byte *)(iVar11 + 0x108) & 0x3f) >> 3,
                        *(undefined4 *)(*(int *)(iVar11 + 0x8c) + 0x14));
        puVar6 = PTR_ExecSelectTarget__8CmdMagicFv_0050db68;
        uVar5 = DAT_0050db64;
        *(undefined4 *)(param_1 + 0x7c) = _5238;
        *(undefined4 *)(param_1 + 0x80) = uVar5;
        *(undefined **)(param_1 + 0x84) = puVar6;
        uStack_24 = 2;
      }
      PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),uStack_24,0,0);
      return 0;
    }
  }
  if ((uVar2 & 0x4000) == 0) {
    if ((uVar2 & 0x8000) == 0) {
      iVar7 = MoveVertical__9MenuSceneFi(param_1,1);
      if (iVar11 == iVar7) {
        ChengePC__10CmdPCSceneFv(param_1);
      }
      else {
        Select__13CmdMagicGoodsFP8CmdMagicP9MenuGroupP9MenuGroups
                  (param_1 + 0x88,param_1,iVar7,iVar11,1);
        PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),0,0,0);
      }
    }
    else {
      lVar9 = __nw__FUi(0x160);
      uVar10 = 0;
      if (lVar9 != 0) {
        uVar10 = __ct__7CmdSortFv(lVar9);
      }
      iVar11 = (int)uVar10;
      *(int *)(param_1 + 0x350) = iVar11;
      *(ushort *)(iVar11 + 0x15a) = (ushort)*(byte *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x28e);
      *(undefined4 *)(iVar11 + 0x15c) = *(undefined4 *)(*(int *)(param_1 + 0x18) + 0xec);
      *(undefined4 *)(iVar11 + 0x10) = *(undefined4 *)(param_1 + 0x10);
      Initialize__9MenuSceneFPUcP9BufMemory(uVar10,*(undefined4 *)(*(int *)(param_1 + 0x54) + 0x40),0);
      *(byte *)(*(int *)(param_1 + 0xcc) + 0x12) = *(byte *)(*(int *)(param_1 + 0xcc) + 0x12) & 0xfe
      ;
      iVar11 = *(int *)(param_1 + 0x348);
      Close__10MenuWindowFUci(iVar11 + 0x58,((ulong)*(byte *)(iVar11 + 0x108) & 0x3f) >> 3,
                      *(undefined4 *)(*(int *)(iVar11 + 0x8c) + 0x14));
      SetChengePCMode__10CmdPCSceneFUc(param_1,0);
      puVar6 = PTR_ExecSort__8CmdMagicFv_0050db88;
      uVar5 = DAT_0050db84;
      *(undefined4 *)(param_1 + 0x7c) = _5250;
      *(undefined4 *)(param_1 + 0x80) = uVar5;
      *(undefined **)(param_1 + 0x84) = puVar6;
      PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),2,0,0);
    }
  }
  else {
    SetChengePCMode__10CmdPCSceneFUc(param_1,0);
    puVar6 = PTR_Exit__8CmdMagicFv_0050db78;
    uVar5 = DAT_0050db74;
    *(undefined4 *)(param_1 + 0x7c) = _5243;
    *(undefined4 *)(param_1 + 0x80) = uVar5;
    *(undefined **)(param_1 + 0x84) = puVar6;
    PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),3,0,0);
  }
  return 0;
}

/* JP: 0x0048e540  CmdMagic::ExecSelectTarget()   [ExecSelectTarget__8CmdMagicFv]  size=0x278 */
undefined8 ExecSelectTarget__8CmdMagicFv(int param_1)

{
  char cVar1;
  short sVar2;
  short sVar3;
  int iVar4;
  int *piVar5;
  undefined4 uVar6;
  undefined *puVar7;
  int iVar8;
  long lVar9;
  
  iVar4 = *(int *)(param_1 + 0x34c);
  lVar9 = (**(code **)(*(int *)(iVar4 + 8) + 0x1c))();
  if (lVar9 != 0) {
    cVar1 = *(char *)(iVar4 + 0x20);
    if (cVar1 == '\x04') {
      (**(code **)(*(int *)(iVar4 + 8) + 0xc))();
      *(undefined4 *)(param_1 + 0x34c) = 0;
      puVar7 = PTR_SelectGoods__8CmdMagicFv_0050db98;
      uVar6 = DAT_0050db94;
      *(undefined4 *)(param_1 + 0x7c) = _5348;
      *(undefined4 *)(param_1 + 0x80) = uVar6;
      *(undefined **)(param_1 + 0x84) = puVar7;
    }
    else {
      if (cVar1 != '\r') {
        if (cVar1 != '\x10') {
          return 0;
        }
        sVar2 = *(short *)(*(int *)(iVar4 + 0x70) + 0x16);
        sVar3 = *(short *)(*(int *)(param_1 + 0x358) + sVar2 * 0x44 + 0x1e);
        piVar5 = *(int **)(param_1 + 0x70);
        *(short *)(*piVar5 + 0x22) = *(short *)(*piVar5 + 0x22) - sVar3;
        *(short *)(piVar5 + 3) = (short)piVar5[3] - sVar3;
        UpdatePCInfo__10CmdPCSceneFsP11CmdPCStatus(param_1,0,0);
        UpdateScene__13CmdMagicGoodsFP8CmdMagicPc
                  (param_1 + 0x88,param_1,*(undefined4 *)(param_1 + 0x364));
        iVar8 = GetPlace__10MenuWindowFs(param_1 + 0x88,sVar2);
        if ((long)((ulong)*(byte *)(iVar8 + 0x21) << 0x3c) < 0) {
          return 0;
        }
        *(undefined1 *)(iVar4 + 0x20) = 0xd;
      }
      *(byte *)(*(int *)(param_1 + 0xcc) + 0x12) =
           *(byte *)(*(int *)(param_1 + 0xcc) + 0x12) & 0xfe | 1;
      Open__15CmdButtonReportFv(*(undefined4 *)(param_1 + 0x348));
      SetChengePCMode__10CmdPCSceneFUc(param_1,1);
      Restore__4MenuFv(*(undefined4 *)(param_1 + 0x10));
      Open__10CmdElementFv(*(undefined4 *)(param_1 + 0x6c));
    }
  }
  return 0;
}

/* JP: 0x0048e7c0  CmdMagic::ExecSort()   [ExecSort__8CmdMagicFv]  size=0x218 */
undefined8 ExecSort__8CmdMagicFv(int param_1)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  undefined *puVar4;
  long lVar5;
  undefined8 uVar6;
  int iVar7;
  
  iVar2 = *(int *)(param_1 + 0x350);
  lVar5 = (**(code **)(*(int *)(iVar2 + 8) + 0x1c))();
  if (lVar5 != 0) {
    iVar7 = param_1 + 0x88;
    cVar1 = *(char *)(iVar2 + 0x20);
    if (cVar1 == '\x04') {
      Select__13CmdMagicGoodsFP8CmdMagicP9MenuGroupP9MenuGroups
                (iVar7,param_1,*(undefined4 *)(iVar2 + 0x15c),0,1);
      *(byte *)(*(int *)(param_1 + 0xcc) + 0x12) =
           *(byte *)(*(int *)(param_1 + 0xcc) + 0x12) & 0xfe | 1;
      SetChengePCMode__10CmdPCSceneFUc(param_1,1);
      (**(code **)(*(int *)(iVar2 + 8) + 0xc))();
      *(undefined4 *)(param_1 + 0x350) = 0;
      puVar4 = PTR_SelectGoods__8CmdMagicFv_0050dba8;
      uVar3 = DAT_0050dba4;
      *(undefined4 *)(param_1 + 0x7c) = _5389;
      *(undefined4 *)(param_1 + 0x80) = uVar3;
      *(undefined **)(param_1 + 0x84) = puVar4;
    }
    else if (cVar1 == '\r') {
      Open__15CmdButtonReportFv(*(undefined4 *)(param_1 + 0x348));
    }
    else if (cVar1 == '\x0f') {
      *(char *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x28e) = (char)*(undefined2 *)(iVar2 + 0x15a);
      UpdateScene__13CmdMagicGoodsFP8CmdMagicPc(iVar7,param_1,*(undefined4 *)(param_1 + 0x364));
      uVar6 = GetPlace__10MenuWindowFss(iVar7,0,0);
      Select__13CmdMagicGoodsFP8CmdMagicP9MenuGroupP9MenuGroups
                (iVar7,param_1,uVar6,*(undefined4 *)(iVar2 + 0x15c),0);
      *(int *)(iVar2 + 0x15c) = (int)uVar6;
    }
  }
  return 0;
}
