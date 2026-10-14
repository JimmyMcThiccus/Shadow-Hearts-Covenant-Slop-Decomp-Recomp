/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdTechnique   functions: 10
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdTechnique.md).
 */

/* JP: 0x00453540  CmdTechnique::CmdTechnique()   [__ct__12CmdTechniqueFv]  size=0x44 */
int __ct__12CmdTechniqueFv(int param_1)

{
  __ct__15CmdPrivateSceneFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__12CmdTechnique;
  *(undefined4 *)(param_1 + 0x80) = 0;
  return param_1;
}

/* JP: 0x00453590  CmdTechnique::~CmdTechnique()   [__dt__12CmdTechniqueFv]  size=0x74 */
int __dt__12CmdTechniqueFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__12CmdTechnique;
    __dt__15CmdPrivateSceneFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x00453610  CmdTechnique::GetReady()   [GetReady__12CmdTechniqueFv]  size=0x4a8 */
undefined4 GetReady__12CmdTechniqueFv(int param_1)

{
  undefined1 uVar1;
  int iVar2;
  int *piVar3;
  undefined2 uVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  long lVar7;
  undefined1 auStack_f0 [100];
  undefined4 *puStack_8c;
  undefined4 *puStack_88;
  undefined4 *puStack_84;
  undefined4 *puStack_80;
  undefined4 *puStack_7c;
  undefined4 *puStack_78;
  undefined4 uStack_74;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  int iStack_5c;
  int iStack_58;
  undefined4 uStack_54;
  int iStack_50;
  int iStack_4c;
  int iStack_48;
  int *piStack_44;
  int *piStack_40;
  int *piStack_3c;
  int iStack_38;
  int iStack_34;
  int iStack_30;
  int iStack_2c;
  int iStack_28;
  int iStack_24;
  int iStack_20;
  undefined4 uStack_1c;
  int iStack_18;
  short sStack_14;
  char cStack_12;
  undefined1 uStack_11;
  int iStack_10;
  
  iVar2 = *(int *)(param_1 + 0x10);
  iStack_10 = param_1;
  __ct__9MenuSceneFv(auStack_f0);
  iStack_30 = *(int *)(iStack_10 + 0x58);
  piVar3 = *(int **)(iStack_30 + 0x70);
  iStack_48 = iVar2 + 0x348;
  iStack_50 = iVar2 + 0x3a0;
  *(int *)(iStack_10 + 0x18) = iStack_50;
  uStack_54 = sm_pSound__7MenuObj;
  *(undefined4 *)(iStack_10 + 0x78) = sm_pSound__7MenuObj;
  iStack_58 = iVar2 + 0xa60;
  *(int *)(iStack_10 + 0x88) = iStack_58;
  uVar1 = *(undefined1 *)(*piVar3 + 2);
  cStack_12 = (char)*(undefined2 *)(piVar3[1] + 0x28);
  sStack_14 = (short)cStack_12;
  iStack_4c = iStack_50;
  piStack_44 = piVar3;
  piStack_40 = piVar3;
  piStack_3c = piVar3;
  iStack_20 = iStack_48;
  uStack_11 = uVar1;
  uVar4 = GetRegCnt__9RegDatApiFii(0x36,uVar1);
  *(undefined2 *)(iStack_10 + 0x7c) = uVar4;
  uVar5 = GetRegDat__9RegDatApiFiii(0x36,uVar1,0);
  *(undefined4 *)(iStack_10 + 0x84) = uVar5;
  iStack_5c = iVar2 + 0x28;
  lVar7 = Find__13MenuDataTableFs(iStack_5c,sStack_14);
  iStack_18 = (int)lVar7;
  if (lVar7 != 0) {
    *(int *)(iStack_10 + 0x80) = iStack_18 + 0x10;
  }
  iStack_34 = *(int *)(iStack_10 + 0x58);
  uStack_68 = *(undefined4 *)(iStack_34 + 0x60);
  uStack_64 = uStack_68;
  uStack_60 = uStack_68;
  puVar6 = (undefined4 *)FindAttachFile__9MenuSceneCFs(iStack_10,uVar1);
  SetTitle__11CmdTitleLogFPUci(uStack_68,*puVar6,sStack_14 + 0x16);
  iStack_38 = *(int *)(iStack_10 + 0x58);
  uStack_74 = *(undefined4 *)(iStack_38 + 0x60);
  uStack_70 = uStack_74;
  uStack_6c = uStack_74;
  Open__11CmdTitleLogFv(uStack_74);
  lVar7 = __nw__FUi(0xf8);
  uVar5 = 0;
  if (lVar7 != 0) {
    uVar5 = __ct__17CmdTechniqueGoodsFv(lVar7);
  }
  *(undefined4 *)(iStack_10 + 0x70) = uVar5;
  CreateScene__17CmdTechniqueGoodsFP9MenuScenesP5CmdPCP12PCSKILLParam
            (*(undefined4 *)(iStack_10 + 0x70),iStack_10,*(undefined2 *)(iStack_10 + 0x7c),piVar3,
             *(undefined4 *)(iStack_10 + 0x84));
  lVar7 = __nw__FUi(0x1c8);
  uVar5 = 0;
  if (lVar7 != 0) {
    uVar5 = __ct__11CmdSubTitleFv(lVar7);
  }
  *(undefined4 *)(iStack_10 + 0x68) = uVar5;
  iStack_24 = *(int *)(iStack_10 + 0x58);
  puStack_7c = (undefined4 *)(*(int *)(iStack_24 + 0x54) + 100);
  puStack_78 = puStack_7c;
  Initialize__9MenuSceneFPUcP9BufMemory(*(undefined4 *)(iStack_10 + 0x68),*puStack_7c,0);
  Create__11CmdSubTitleFi(*(undefined4 *)(iStack_10 + 0x68),1);
  Reset__11CmdSubTitleFv(*(undefined4 *)(iStack_10 + 0x68));
  SetTitle__11CmdSubTitleFii(*(undefined4 *)(iStack_10 + 0x68),0,0x17);
  iStack_28 = *(int *)(iStack_10 + 0x58);
  puStack_84 = (undefined4 *)(*(int *)(iStack_28 + 0x54) + 0x7c);
  puStack_80 = puStack_84;
  Initialize__9MenuSceneFPUcP9BufMemory(auStack_f0,*puStack_84,0);
  lVar7 = __nw__FUi(0x178);
  uVar5 = 0;
  if (lVar7 != 0) {
    uVar5 = __ct__8CmdFenceFv(lVar7);
  }
  *(undefined4 *)(iStack_10 + 0x6c) = uVar5;
  iStack_2c = *(int *)(iStack_10 + 0x58);
  puStack_8c = (undefined4 *)(*(int *)(iStack_2c + 0x54) + 0x1c);
  puStack_88 = puStack_8c;
  CreateFence__8CmdFenceFP9MenuScenePUc(*(undefined4 *)(iStack_10 + 0x6c),auStack_f0,*puStack_8c);
  iVar2 = *(int *)(iStack_10 + 0x70);
  Open__10MenuWindowFUci(iVar2,*(byte *)(iVar2 + 0xb0) & 7,*(undefined4 *)(*(int *)(iVar2 + 0x34) + 0x10));
  iVar2 = *(int *)(iStack_10 + 0x68);
  Open__10MenuWindowFUci(iVar2 + 0x58,*(byte *)(iVar2 + 0x108) & 7,
                  *(undefined4 *)(*(int *)(iVar2 + 0x8c) + 0x10));
  iVar2 = *(int *)(iStack_10 + 0x6c);
  Open__10MenuWindowFUci(iVar2,*(byte *)(iVar2 + 0xb0) & 7,*(undefined4 *)(*(int *)(iVar2 + 0x34) + 0x10));
  *(byte *)(iStack_10 + 0x23) = *(byte *)(iStack_10 + 0x23) & 0xdf | 0x20;
  uStack_1c = 1;
  __dt__9MenuSceneFv(auStack_f0,0xffffffffffffffff);
  return uStack_1c;
}

/* JP: 0x00453ac0  CmdTechnique::Run()   [Run__12CmdTechniqueFv]  size=0x68 */
undefined4 Run__12CmdTechniqueFv(int param_1)

{
  undefined4 uVar1;
  long lVar2;
  
  lVar2 = __ptmf_test(param_1 + 0x5c);
  if ((lVar2 == 0) || (lVar2 = __ptmf_scall(param_1), lVar2 != 0)) {
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

/* JP: 0x00453b30  CmdTechnique::SafeDelayDelete()   [SafeDelayDelete__12CmdTechniqueFv]  size=0x78 */
void SafeDelayDelete__12CmdTechniqueFv(int param_1)

{
  (**(code **)(*(int *)(*(int *)(param_1 + 0x70) + 8) + 0xc))();
  (**(code **)(*(int *)(*(int *)(param_1 + 0x6c) + 8) + 0xc))();
  (**(code **)(*(int *)(*(int *)(param_1 + 0x68) + 8) + 0xc))();
  (**(code **)(*(int *)(param_1 + 8) + 0xc))();
  return;
}

/* JP: 0x00453bb0  CmdTechnique::Close()   [Close__12CmdTechniqueFv]  size=0xac */
void Close__12CmdTechniqueFv(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x70);
  Close__10MenuWindowFUci(iVar1,((ulong)*(byte *)(iVar1 + 0xb0) & 0x3f) >> 3,
                  *(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x14));
  iVar1 = *(int *)(param_1 + 0x6c);
  Close__10MenuWindowFUci(iVar1,((ulong)*(byte *)(iVar1 + 0xb0) & 0x3f) >> 3,
                  *(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x14));
  iVar1 = *(int *)(param_1 + 0x68);
  Close__10MenuWindowFUci(iVar1 + 0x58,((ulong)*(byte *)(iVar1 + 0x108) & 0x3f) >> 3,
                  *(undefined4 *)(*(int *)(iVar1 + 0x8c) + 0x14));
  return;
}

/* JP: 0x00453c60  CmdTechnique::ReadyScene()   [ReadyScene__12CmdTechniqueFv]  size=0x124 */
undefined4 ReadyScene__12CmdTechniqueFv(int param_1)

{
  undefined4 uVar1;
  undefined *puVar2;
  undefined8 uVar3;
  
  uVar3 = GetPlace__10MenuWindowFss(*(undefined4 *)(param_1 + 0x70),0,0);
  Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),uVar3);
  Select__17CmdTechniqueGoodsFP7CmdNoteP10CmdElementP12PCSKILLParamP9MenuGroupP9MenuGroup
            (*(undefined4 *)(param_1 + 0x70),*(undefined4 *)(*(int *)(param_1 + 0x58) + 100),
             *(undefined4 *)(*(int *)(param_1 + 0x58) + 0x6c),*(undefined4 *)(param_1 + 0x84),uVar3,
             0);
  SetChengePCMode__10CmdPCSceneFUc(*(undefined4 *)(param_1 + 0x58),0);
  puVar2 = PTR_Enter__12CmdTechniqueFv_0050d480;
  uVar1 = DAT_0050d47c;
  *(undefined4 *)(param_1 + 0x5c) = _5244;
  *(undefined4 *)(param_1 + 0x60) = uVar1;
  *(undefined **)(param_1 + 100) = puVar2;
  return 1;
}

/* JP: 0x00453d90  CmdTechnique::Enter()   [Enter__12CmdTechniqueFv]  size=0x144 */
undefined8 Enter__12CmdTechniqueFv(int param_1)

{
  undefined4 uVar1;
  undefined *puVar2;
  ulong uVar3;
  
  if (*(char *)(*(int *)(param_1 + 0x88) + 0x100) == '\0') {
    ClearReport__15CmdButtonReportFv(*(undefined4 *)(param_1 + 0x88));
    if (*(int *)(*(int *)(param_1 + 0x70) + 0x44) == 0) {
      uVar3 = 0;
    }
    else {
      uVar3 = ((ulong)*(ushort *)(*(int *)(param_1 + 0x70) + 0xb2) & 0x3ff) >> 2;
    }
    if (uVar3 != 0) {
      SetReport__15CmdButtonReportFii
                (*(int *)(param_1 + 0x88),*(undefined1 *)(*(int *)(param_1 + 0x88) + 0x20),0xd);
    }
    Open__15CmdButtonReportFv(*(undefined4 *)(param_1 + 0x88));
    puVar2 = PTR_SelectGoods__12CmdTechniqueFv_0050d490;
    uVar1 = DAT_0050d48c;
    *(undefined4 *)(param_1 + 0x5c) = _5271;
    *(undefined4 *)(param_1 + 0x60) = uVar1;
    *(undefined **)(param_1 + 100) = puVar2;
  }
  return 0;
}

/* JP: 0x00453ee0  CmdTechnique::SelectGoods()   [SelectGoods__12CmdTechniqueFv]  size=0x1d4 */
undefined4 SelectGoods__12CmdTechniqueFv(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  iVar1 = *(int *)(*(int *)(param_1 + 0x18) + 0xec);
  if ((*(ushort *)(*(int *)(param_1 + 0x10) + 0x48) & 0x4000) == 0) {
    iVar3 = MoveVertical__9MenuSceneFi(param_1,1);
    if (iVar1 != iVar3) {
      Select__17CmdTechniqueGoodsFP7CmdNoteP10CmdElementP12PCSKILLParamP9MenuGroupP9MenuGroup
                (*(undefined4 *)(param_1 + 0x70),*(undefined4 *)(*(int *)(param_1 + 0x58) + 100),
                 *(undefined4 *)(*(int *)(param_1 + 0x58) + 0x6c),*(undefined4 *)(param_1 + 0x84),
                 iVar3,iVar1);
      PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x78),0,0,0);
    }
    uVar2 = 0;
  }
  else {
    Leave__6CursorFv(*(undefined4 *)(param_1 + 0x18));
    iVar1 = *(int *)(param_1 + 0x70);
    SetClutGoods__9CmdWindowFP8CmdGoodss
              (iVar1,*(undefined4 *)(iVar1 + 0xf4),*(undefined2 *)(iVar1 + 0xae));
    SetScroll__10MenuWindowFss(*(undefined4 *)(param_1 + 0x70),0,0);
    Finish__10MenuWindowFv(*(undefined4 *)(param_1 + 0x70));
    PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x78),3,0,0);
    uVar2 = 1;
  }
  return uVar2;
}

/* JP: 0x004540c0  CmdTechnique::Release()   [Release__12CmdTechniqueFv]  size=0x10 */
void Release__12CmdTechniqueFv(void)

{
  return;
}
