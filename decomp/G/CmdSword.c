/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdSword   functions: 8
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdSword.md).
 */

/* JP: 0x00456f30  CmdSword::CmdSword()   [__ct__8CmdSwordFv]  size=0x3c */
int __ct__8CmdSwordFv(int param_1)

{
  __ct__15CmdPrivateSceneFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__8CmdSword;
  return param_1;
}

/* JP: 0x00456f70  CmdSword::~CmdSword()   [__dt__8CmdSwordFv]  size=0x74 */
int __dt__8CmdSwordFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__8CmdSword;
    __dt__15CmdPrivateSceneFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x00456ff0  CmdSword::GetReady()   [GetReady__8CmdSwordFv]  size=0x3e8 */
undefined4 GetReady__8CmdSwordFv(int param_1)

{
  int iVar1;
  undefined2 uVar2;
  undefined4 uVar3;
  long lVar4;
  undefined1 auStack_c0 [92];
  undefined4 *puStack_64;
  undefined4 *puStack_60;
  undefined4 *puStack_5c;
  undefined4 *puStack_58;
  undefined4 *puStack_54;
  undefined4 *puStack_50;
  undefined4 *puStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  int iStack_3c;
  undefined4 uStack_38;
  int iStack_34;
  int iStack_30;
  int iStack_2c;
  int iStack_28;
  int iStack_24;
  int iStack_20;
  int iStack_1c;
  int iStack_18;
  undefined4 uStack_14;
  int iStack_10;
  
  iVar1 = *(int *)(param_1 + 0x10);
  iStack_10 = param_1;
  __ct__9MenuSceneFv(auStack_c0);
  iStack_2c = iVar1 + 0x348;
  iStack_34 = iVar1 + 0x3a0;
  *(int *)(iStack_10 + 0x18) = iStack_34;
  uStack_38 = sm_pSound__7MenuObj;
  *(undefined4 *)(iStack_10 + 0x68) = sm_pSound__7MenuObj;
  iStack_30 = iStack_34;
  iStack_18 = iStack_2c;
  uVar2 = GetRegCnt__9RegDatApiFii(0x36,5);
  *(undefined2 *)(iStack_10 + 0x78) = uVar2;
  uVar3 = GetRegDat__9RegDatApiFiii(0x36,5,0);
  *(undefined4 *)(iStack_10 + 0x80) = uVar3;
  iStack_3c = iVar1 + 0x28;
  uVar3 = Find__13MenuDataTableFs(iStack_3c,0x33);
  *(undefined4 *)(iStack_10 + 0x7c) = uVar3;
  iStack_28 = *(int *)(iStack_10 + 0x58);
  uVar3 = *(undefined4 *)(iStack_28 + 0x60);
  puStack_4c = (undefined4 *)(*(int *)(iStack_10 + 0x54) + 0x10);
  uStack_48 = uVar3;
  uStack_44 = uVar3;
  uStack_40 = uVar3;
  SetTitle__11CmdTitleLogFPUci(uVar3,*puStack_4c,0x11);
  Open__11CmdTitleLogFv(uVar3);
  lVar4 = __nw__FUi(0xf8);
  uVar3 = 0;
  if (lVar4 != 0) {
    uVar3 = __ct__13CmdSwordGoodsFv(lVar4);
  }
  *(undefined4 *)(iStack_10 + 0x74) = uVar3;
  CreateScene__13CmdSwordGoodsFP8CmdSword(*(undefined4 *)(iStack_10 + 0x74),iStack_10);
  iVar1 = *(int *)(iStack_10 + 0x74);
  Open__10MenuWindowFUci(iVar1,*(byte *)(iVar1 + 0xb0) & 7,*(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x10));
  lVar4 = __nw__FUi(0x1c8);
  uVar3 = 0;
  if (lVar4 != 0) {
    uVar3 = __ct__11CmdSubTitleFv(lVar4);
  }
  *(undefined4 *)(iStack_10 + 0x70) = uVar3;
  iStack_1c = *(int *)(iStack_10 + 0x58);
  puStack_54 = (undefined4 *)(*(int *)(iStack_1c + 0x54) + 100);
  puStack_50 = puStack_54;
  Initialize__9MenuSceneFPUcP9BufMemory(*(undefined4 *)(iStack_10 + 0x70),*puStack_54,0);
  Create__11CmdSubTitleFi(*(undefined4 *)(iStack_10 + 0x70),1);
  Reset__11CmdSubTitleFv(*(undefined4 *)(iStack_10 + 0x70));
  SetTitle__11CmdSubTitleFii(*(undefined4 *)(iStack_10 + 0x70),0,0x17);
  iStack_20 = *(int *)(iStack_10 + 0x58);
  puStack_5c = (undefined4 *)(*(int *)(iStack_20 + 0x54) + 0x88);
  puStack_58 = puStack_5c;
  Initialize__9MenuSceneFPUcP9BufMemory(auStack_c0,*puStack_5c,0);
  lVar4 = __nw__FUi(0x178);
  uVar3 = 0;
  if (lVar4 != 0) {
    uVar3 = __ct__8CmdFenceFv(lVar4);
  }
  *(undefined4 *)(iStack_10 + 0x6c) = uVar3;
  iStack_24 = *(int *)(iStack_10 + 0x58);
  puStack_64 = (undefined4 *)(*(int *)(iStack_24 + 0x54) + 0x1c);
  puStack_60 = puStack_64;
  CreateFence__8CmdFenceFP9MenuScenePUc(*(undefined4 *)(iStack_10 + 0x6c),auStack_c0,*puStack_64);
  iVar1 = *(int *)(iStack_10 + 0x74);
  Open__10MenuWindowFUci(iVar1,*(byte *)(iVar1 + 0xb0) & 7,*(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x10));
  iVar1 = *(int *)(iStack_10 + 0x70);
  Open__10MenuWindowFUci(iVar1 + 0x58,*(byte *)(iVar1 + 0x108) & 7,
                  *(undefined4 *)(*(int *)(iVar1 + 0x8c) + 0x10));
  iVar1 = *(int *)(iStack_10 + 0x6c);
  Open__10MenuWindowFUci(iVar1,*(byte *)(iVar1 + 0xb0) & 7,*(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x10));
  *(byte *)(iStack_10 + 0x23) = *(byte *)(iStack_10 + 0x23) & 0xdf | 0x20;
  uStack_14 = 1;
  __dt__9MenuSceneFv(auStack_c0,0xffffffffffffffff);
  return uStack_14;
}

/* JP: 0x004573e0  CmdSword::Run()   [Run__8CmdSwordFv]  size=0x68 */
undefined4 Run__8CmdSwordFv(int param_1)

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

/* JP: 0x00457450  CmdSword::SafeDelayDelete()   [SafeDelayDelete__8CmdSwordFv]  size=0x78 */
void SafeDelayDelete__8CmdSwordFv(int param_1)

{
  (**(code **)(*(int *)(*(int *)(param_1 + 0x74) + 8) + 0xc))();
  (**(code **)(*(int *)(*(int *)(param_1 + 0x6c) + 8) + 0xc))();
  (**(code **)(*(int *)(*(int *)(param_1 + 0x70) + 8) + 0xc))();
  (**(code **)(*(int *)(param_1 + 8) + 0xc))();
  return;
}

/* JP: 0x004574d0  CmdSword::Close()   [Close__8CmdSwordFv]  size=0xac */
void Close__8CmdSwordFv(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x74);
  Close__10MenuWindowFUci(iVar1,((ulong)*(byte *)(iVar1 + 0xb0) & 0x3f) >> 3,
                  *(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x14));
  iVar1 = *(int *)(param_1 + 0x6c);
  Close__10MenuWindowFUci(iVar1,((ulong)*(byte *)(iVar1 + 0xb0) & 0x3f) >> 3,
                  *(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x14));
  iVar1 = *(int *)(param_1 + 0x70);
  Close__10MenuWindowFUci(iVar1 + 0x58,((ulong)*(byte *)(iVar1 + 0x108) & 0x3f) >> 3,
                  *(undefined4 *)(*(int *)(iVar1 + 0x8c) + 0x14));
  return;
}

/* JP: 0x00457580  CmdSword::ReadyScene()   [ReadyScene__8CmdSwordFv]  size=0xb0 */
undefined4 ReadyScene__8CmdSwordFv(int param_1)

{
  undefined4 uVar1;
  undefined *puVar2;
  undefined8 uVar3;
  
  uVar3 = GetPlace__10MenuWindowFss(*(undefined4 *)(param_1 + 0x74),0,0);
  Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),uVar3);
  Select__13CmdSwordGoodsFP8CmdSwordP9MenuGroupP9MenuGroup
            (*(undefined4 *)(param_1 + 0x74),param_1,uVar3,0);
  SetChengePCMode__10CmdPCSceneFUc(*(undefined4 *)(param_1 + 0x58),0);
  puVar2 = PTR_SelectGoods__8CmdSwordFv_0050d4a0;
  uVar1 = DAT_0050d49c;
  *(undefined4 *)(param_1 + 0x5c) = _5205;
  *(undefined4 *)(param_1 + 0x60) = uVar1;
  *(undefined **)(param_1 + 100) = puVar2;
  return 1;
}

/* JP: 0x00457630  CmdSword::SelectGoods()   [SelectGoods__8CmdSwordFv]  size=0x154 */
undefined4 SelectGoods__8CmdSwordFv(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  iVar1 = *(int *)(*(int *)(param_1 + 0x18) + 0xec);
  if ((*(ushort *)(*(int *)(param_1 + 0x10) + 0x48) & 0x4000) == 0) {
    iVar3 = MoveVertical__9MenuSceneFi(param_1,0);
    if (iVar1 != iVar3) {
      Select__13CmdSwordGoodsFP8CmdSwordP9MenuGroupP9MenuGroup
                (*(undefined4 *)(param_1 + 0x74),param_1,iVar3,iVar1);
      PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x68),0,0,0);
    }
    uVar2 = 0;
  }
  else {
    Select__13CmdSwordGoodsFP8CmdSwordP9MenuGroupP9MenuGroup
              (*(undefined4 *)(param_1 + 0x74),param_1,0,iVar1);
    Leave__6CursorFv(*(undefined4 *)(param_1 + 0x18));
    PlaySE__9MenuSoundFUiUcP8_SeParam(*(undefined4 *)(param_1 + 0x68),3,0,0);
    uVar2 = 1;
  }
  return uVar2;
}
