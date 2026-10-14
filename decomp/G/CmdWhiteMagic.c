/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdWhiteMagic   functions: 8
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdWhiteMagic.md).
 */

/* JP: 0x00496330  CmdWhiteMagic::CmdWhiteMagic()   [__ct__13CmdWhiteMagicFv]  size=0x5c */
int __ct__13CmdWhiteMagicFv(int param_1)

{
  __ct__10CmdPCSceneFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__13CmdWhiteMagic;
  __ct__17CmdTechniqueGoodsFv(param_1 + 0x88);
  __ct__11CmdSubTitleFv(param_1 + 0x180);
  return param_1;
}

/* JP: 0x00496390  CmdWhiteMagic::~CmdWhiteMagic()   [__dt__13CmdWhiteMagicFv]  size=0xb4 */
int __dt__13CmdWhiteMagicFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__13CmdWhiteMagic;
    (**(code **)(*(int *)(*(int *)(param_1 + 0x348) + 8) + 0xc))();
    __dt__11CmdSubTitleFv(param_1 + 0x180,0xffffffffffffffff);
    __dt__17CmdTechniqueGoodsFv(param_1 + 0x88,0xffffffffffffffff);
    __dt__10CmdPCSceneFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x00496450  CmdWhiteMagic::GetReady()   [GetReady__13CmdWhiteMagicFv]  size=0x388 */
undefined4 GetReady__13CmdWhiteMagicFv(int param_1)

{
  undefined1 uVar1;
  int *piVar2;
  undefined *puVar3;
  ushort uVar4;
  short sVar5;
  undefined2 uVar6;
  undefined4 uVar7;
  long lVar8;
  undefined1 auStack_80 [88];
  int iStack_28;
  int *piStack_24;
  undefined4 uStack_20;
  int iStack_1c;
  int iStack_18;
  undefined1 uStack_12;
  undefined1 uStack_11;
  int iStack_10;
  
  iStack_18 = *(int *)(param_1 + 0x10);
  iStack_10 = param_1;
  __ct__9MenuSceneFv(auStack_80);
  for (uVar4 = 1; (short)uVar4 < 5; uVar4 = uVar4 + 1) {
    Convert__13MenuDataTableFPUci(*(undefined4 *)((uint)uVar4 * 0xc + *(int *)(iStack_10 + 0x54) + 0x10),0);
  }
  CreatePCInfo__10CmdPCSceneFPUc(iStack_10,*(undefined4 *)(*(int *)(iStack_10 + 0x54) + 0x1c));
  *(undefined2 *)(*(int *)(iStack_10 + 0x18) + 0x32) = 0;
  sVar5 = GetLayerCount__10CmdPCSceneFs(iStack_10,0);
  if (sVar5 < 2) {
    *(byte *)(iStack_10 + 0x23) = *(byte *)(iStack_10 + 0x23) & 0xfe;
  }
  SetChengePCMode__10CmdPCSceneFUc(iStack_10,0);
  piVar2 = *(int **)(iStack_10 + 0x70);
  uVar1 = *(undefined1 *)(*piVar2 + 2);
  piStack_24 = piVar2;
  uStack_11 = uVar1;
  uVar6 = GetRegCnt__9RegDatApiFii(0x36,uVar1);
  *(undefined2 *)(iStack_10 + 0x358) = uVar6;
  uVar7 = GetRegDat__9RegDatApiFiii(0x36,uVar1,0);
  *(undefined4 *)(iStack_10 + 0x350) = uVar7;
  uStack_12 = (undefined1)*(undefined2 *)(piVar2[1] + 0x28);
  iStack_28 = iStack_18 + 0x28;
  lVar8 = Find__13MenuDataTableFs(iStack_28,uStack_12);
  iStack_1c = (int)lVar8;
  if (lVar8 != 0) {
    *(int *)(iStack_10 + 0x354) = iStack_1c + 0x10;
  }
  *(byte *)(iStack_10 + 0x23) = *(byte *)(iStack_10 + 0x23) & 0x3f | 0x40;
  Initialize__9MenuSceneFPUcP9BufMemory(iStack_10 + 0x180,*(undefined4 *)(*(int *)(iStack_10 + 0x54) + 0x28),0);
  Create__11CmdSubTitleFi(iStack_10 + 0x180,1);
  Reset__11CmdSubTitleFv(iStack_10 + 0x180);
  SetTitle__11CmdSubTitleFii(iStack_10 + 0x180,0,0);
  Initialize__9MenuSceneFPUcP9BufMemory(auStack_80,*(undefined4 *)(*(int *)(iStack_10 + 0x54) + 0x40),0);
  lVar8 = __nw__FUi(0x178);
  uVar7 = 0;
  if (lVar8 != 0) {
    uVar7 = __ct__8CmdFenceFv(lVar8);
  }
  *(undefined4 *)(iStack_10 + 0x348) = uVar7;
  CreateFence__8CmdFenceFP9MenuScenePUc(*(undefined4 *)(iStack_10 + 0x348),auStack_80,0);
  CreateScene__17CmdTechniqueGoodsFP9MenuScenesP5CmdPCP12PCSKILLParam
            (iStack_10 + 0x88,iStack_10,*(undefined2 *)(iStack_10 + 0x358),piVar2,
             *(undefined4 *)(iStack_10 + 0x350));
  puVar3 = PTR_Enter__13CmdWhiteMagicFv_0050dcc8;
  uVar7 = DAT_0050dcc4;
  *(undefined4 *)(iStack_10 + 0x7c) = _5055;
  *(undefined4 *)(iStack_10 + 0x80) = uVar7;
  *(undefined **)(iStack_10 + 0x84) = puVar3;
  uStack_20 = 1;
  __dt__9MenuSceneFv(auStack_80,0xffffffffffffffff);
  return uStack_20;
}

/* JP: 0x004967e0  CmdWhiteMagic::Run()   [Run__13CmdWhiteMagicFv]  size=0xe4 */
undefined4 Run__13CmdWhiteMagicFv(int param_1)

{
  bool bVar1;
  undefined4 uVar2;
  long lVar3;
  
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
  lVar3 = __ptmf_test(param_1 + 0x7c);
  if ((lVar3 == 0) || (lVar3 = __ptmf_scall(param_1), lVar3 != 0)) {
    uVar2 = 1;
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

/* JP: 0x004968d0  CmdWhiteMagic::Enter()   [Enter__13CmdWhiteMagicFv]  size=0x2d0 */
undefined8 Enter__13CmdWhiteMagicFv(int param_1)

{
  int iVar1;
  bool bVar2;
  undefined4 uVar3;
  undefined *puVar4;
  undefined1 uVar5;
  undefined8 uVar6;
  
  if (*(char *)(param_1 + 0x21) == '\0') {
    uVar6 = GetPlace__10MenuWindowFss(param_1 + 0x88,0,0);
    Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),uVar6);
    Select__17CmdTechniqueGoodsFP7CmdNoteP10CmdElementP12PCSKILLParamP9MenuGroupP9MenuGroup
              (param_1 + 0x88,*(undefined4 *)(param_1 + 100),*(undefined4 *)(param_1 + 0x6c),
               *(undefined4 *)(param_1 + 0x350),uVar6,0);
    iVar1 = *(int *)(param_1 + 0x78);
    Open__10MenuWindowFUci(iVar1 + 0x58,*(byte *)(iVar1 + 0x108) & 7,
                    *(undefined4 *)(*(int *)(iVar1 + 0x8c) + 0x10));
    Open__10MenuWindowFUci(param_1 + 0x1d8,*(byte *)(param_1 + 0x288) & 7,
                    *(undefined4 *)(*(int *)(param_1 + 0x20c) + 0x10));
    Open__10MenuWindowFUci(param_1 + 0x88,*(byte *)(param_1 + 0x138) & 7,
                    *(undefined4 *)(*(int *)(param_1 + 0xbc) + 0x10));
    Open__10CmdElementFv(*(undefined4 *)(param_1 + 0x6c));
    iVar1 = *(int *)(param_1 + 0x348);
    Open__10MenuWindowFUci(iVar1,*(byte *)(iVar1 + 0xb0) & 7,*(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x10)
                   );
    SetTitle__11CmdTitleLogFPUci
              (*(undefined4 *)(param_1 + 0x60),*(undefined4 *)(*(int *)(param_1 + 0x54) + 0x10),0x1c
              );
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
      puVar4 = PTR_SelectGoods__13CmdWhiteMagicFv_0050dcd8;
      uVar3 = DAT_0050dcd4;
      *(undefined4 *)(param_1 + 0x7c) = _5114;
      *(undefined4 *)(param_1 + 0x80) = uVar3;
      *(undefined **)(param_1 + 0x84) = puVar4;
    }
  }
  return 0;
}

/* JP: 0x00496ba0  CmdWhiteMagic::Exit()   [Exit__13CmdWhiteMagicFv]  size=0x24c */
undefined8 Exit__13CmdWhiteMagicFv(int param_1)

{
  int iVar1;
  bool bVar2;
  
  if (*(char *)(param_1 + 0x21) == '\0') {
    (**(code **)(*(int *)(*(int *)(param_1 + 0x10) + 0x14) + 0x28))(*(int *)(param_1 + 0x10),0,0,1);
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

/* JP: 0x00496df0  CmdWhiteMagic::SelectGoods()   [SelectGoods__13CmdWhiteMagicFv]  size=0x418 */
undefined8 SelectGoods__13CmdWhiteMagicFv(int param_1)

{
  short sVar1;
  ushort uVar2;
  int iVar3;
  bool bVar4;
  undefined *puVar5;
  undefined4 uVar6;
  int iVar7;
  long lVar8;
  undefined4 *puVar9;
  int iVar10;
  
  puVar5 = PTR_Exit__13CmdWhiteMagicFv_0050dcf8;
  uVar6 = DAT_0050dcf4;
  uVar2 = *(ushort *)(*(int *)(param_1 + 0x10) + 0x48);
  iVar3 = *(int *)(*(int *)(param_1 + 0x18) + 0xec);
  if ((uVar2 & 0x2000) != 0) {
    if ((*(char *)(param_1 + 0x130) == '\x01') || (*(char *)(param_1 + 0x130) == '\0')) {
      bVar4 = true;
    }
    else {
      bVar4 = false;
    }
    if (bVar4) {
      uVar6 = 4;
      if ((long)((ulong)*(byte *)(iVar3 + 0x21) << 0x3c) < 0) {
        lVar8 = __nw__FUi(0xaa0);
        uVar6 = 0;
        if (lVar8 != 0) {
          uVar6 = __ct__15CmdSelectTargetFv(lVar8);
        }
        *(undefined4 *)(param_1 + 0x34c) = uVar6;
        sVar1 = *(short *)(iVar3 + 0x16);
        iVar7 = *(int *)(param_1 + 0x34c);
        iVar10 = *(int *)(param_1 + 0x350) + sVar1 * 0x40;
        puVar9 = (undefined4 *)(*(int *)(param_1 + 0x354) + sVar1 * 8);
        *(short *)(iVar7 + 0x5c) = sVar1;
        *(undefined2 *)(iVar7 + 0x5e) = 1;
        *(byte *)(iVar7 + 0x61) = (byte)(((ulong)*(byte *)(iVar10 + 5) << 0x3c) >> 0x3d);
        *(byte *)(iVar7 + 0x60) = (byte)(((ulong)*(ushort *)(iVar10 + 4) << 0x37) >> 0x3e);
        *(undefined2 *)(iVar7 + 0x62) = 0;
        *(int *)(iVar7 + 100) = iVar10 + 8;
        *(undefined4 *)(iVar7 + 0x68) = *puVar9;
        *(undefined4 *)(iVar7 + 0x6c) = puVar9[1];
        *(int *)(iVar7 + 0x70) = iVar3;
        *(undefined4 *)(*(int *)(param_1 + 0x34c) + 0x10) = *(undefined4 *)(param_1 + 0x10);
        Initialize__9MenuSceneFPUcP9BufMemory(*(undefined4 *)(param_1 + 0x34c),
                        *(undefined4 *)(*(int *)(param_1 + 0x54) + 0x34),0);
        *(byte *)(*(int *)(param_1 + 0xcc) + 0x12) =
             *(byte *)(*(int *)(param_1 + 0xcc) + 0x12) & 0xfe;
        SetChengePCMode__10CmdPCSceneFUc(param_1,0);
        Shutdown__4MenuFv(*(undefined4 *)(param_1 + 0x10));
        Close__10CmdElementFv(*(undefined4 *)(param_1 + 0x6c));
        puVar5 = PTR_ExecSelectTarget__13CmdWhiteMagicFv_0050dce8;
        uVar6 = DAT_0050dce4;
        *(undefined4 *)(param_1 + 0x7c) = _5187;
        *(undefined4 *)(param_1 + 0x80) = uVar6;
        *(undefined **)(param_1 + 0x84) = puVar5;
        uVar6 = 2;
      }
      PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),uVar6,0,0);
      return 0;
    }
  }
  if ((uVar2 & 0x4000) == 0) {
    iVar7 = MoveVertical__9MenuSceneFi(param_1,1);
    if (iVar3 == iVar7) {
      ChengePC__10CmdPCSceneFv(param_1);
    }
    else {
      Select__17CmdTechniqueGoodsFP7CmdNoteP10CmdElementP12PCSKILLParamP9MenuGroupP9MenuGroup
                (param_1 + 0x88,*(undefined4 *)(param_1 + 100),*(undefined4 *)(param_1 + 0x6c),
                 *(undefined4 *)(param_1 + 0x350),iVar7,iVar3);
      PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),0,0,0);
    }
  }
  else {
    *(undefined4 *)(param_1 + 0x7c) = _5192;
    *(undefined4 *)(param_1 + 0x80) = uVar6;
    *(undefined **)(param_1 + 0x84) = puVar5;
    PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x58),3,0,0);
  }
  return 0;
}

/* JP: 0x00497210  CmdWhiteMagic::ExecSelectTarget()   [ExecSelectTarget__13CmdWhiteMagicFv]  size=0x280 */
undefined8 ExecSelectTarget__13CmdWhiteMagicFv(int param_1)

{
  char cVar1;
  short sVar2;
  short sVar3;
  int *piVar4;
  undefined4 uVar5;
  undefined *puVar6;
  long lVar7;
  
  lVar7 = (**(code **)(*(int *)(*(int *)(param_1 + 0x34c) + 8) + 0x1c))();
  if (lVar7 != 0) {
    cVar1 = *(char *)(*(int *)(param_1 + 0x34c) + 0x20);
    if (cVar1 == '\x04') {
      (**(code **)(*(int *)(*(int *)(param_1 + 0x34c) + 8) + 0xc))();
      *(undefined4 *)(param_1 + 0x34c) = 0;
      puVar6 = PTR_SelectGoods__13CmdWhiteMagicFv_0050dd08;
      uVar5 = DAT_0050dd04;
      *(undefined4 *)(param_1 + 0x7c) = _5256;
      *(undefined4 *)(param_1 + 0x80) = uVar5;
      *(undefined **)(param_1 + 0x84) = puVar6;
    }
    else {
      if (cVar1 != '\r') {
        if (cVar1 != '\x10') {
          return 0;
        }
        sVar2 = *(short *)(*(int *)(*(int *)(param_1 + 0x34c) + 0x70) + 0x16);
        sVar3 = *(short *)(*(int *)(param_1 + 0x350) + sVar2 * 0x40 + 0x1e);
        piVar4 = *(int **)(param_1 + 0x70);
        *(short *)(*piVar4 + 0x22) = *(short *)(*piVar4 + 0x22) - sVar3;
        *(short *)(piVar4 + 3) = (short)piVar4[3] - sVar3;
        UpdatePCInfo__10CmdPCSceneFsP11CmdPCStatus(param_1,0,0);
        lVar7 = UpdateScene__17CmdTechniqueGoodsFP12PCSKILLParamss
                          (param_1 + 0x88,*(undefined4 *)(param_1 + 0x350),
                           *(undefined2 *)(*(int *)(param_1 + 0x70) + 0xc),sVar2);
        if (lVar7 != 0) {
          return 0;
        }
        *(undefined1 *)(*(int *)(param_1 + 0x34c) + 0x20) = 0xd;
      }
      *(byte *)(*(int *)(param_1 + 0xcc) + 0x12) =
           *(byte *)(*(int *)(param_1 + 0xcc) + 0x12) & 0xfe | 1;
      SetChengePCMode__10CmdPCSceneFUc(param_1,1);
      Restore__4MenuFv(*(undefined4 *)(param_1 + 0x10));
      Open__10CmdElementFv(*(undefined4 *)(param_1 + 0x6c));
    }
  }
  return 0;
}
