/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdPhotograph   functions: 5
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdPhotograph.md).
 */

/* JP: 0x00456730  CmdPhotograph::CmdPhotograph()   [__ct__13CmdPhotographFv]  size=0x4c */
int __ct__13CmdPhotographFv(int param_1)

{
  __ct__15CmdPrivateSceneFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__13CmdPhotograph;
  __ct__18CmdPhotographGoodsFv(param_1 + 0x5c);
  return param_1;
}

/* JP: 0x00456780  CmdPhotograph::~CmdPhotograph()   [__dt__13CmdPhotographFv]  size=0x84 */
int __dt__13CmdPhotographFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__13CmdPhotograph;
    __dt__18CmdPhotographGoodsFv(param_1 + 0x5c,0xffffffffffffffff);
    __dt__15CmdPrivateSceneFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x00456810  CmdPhotograph::GetReady()   [GetReady__13CmdPhotographFv]  size=0x1ec */
undefined4 GetReady__13CmdPhotographFv(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  long lVar3;
  undefined1 auStack_90 [92];
  undefined4 *puStack_34;
  undefined4 *puStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  int iStack_10;
  
  iStack_10 = param_1;
  __ct__9MenuSceneFv(auStack_90);
  uStack_20 = *(undefined4 *)(*(int *)(iStack_10 + 0x58) + 0x60);
  uStack_1c = uStack_20;
  uStack_18 = uStack_20;
  SetTitle__11CmdTitleLogFPUci(uStack_20,*(undefined4 *)(*(int *)(iStack_10 + 0x54) + 0x10),0x1f);
  uStack_2c = *(undefined4 *)(*(int *)(iStack_10 + 0x58) + 0x60);
  uStack_28 = uStack_2c;
  uStack_24 = uStack_2c;
  Open__11CmdTitleLogFv(uStack_2c);
  CreateScene__18CmdPhotographGoodsFP13CmdPhotograph(iStack_10 + 0x5c,iStack_10);
  Open__10MenuWindowFUci(iStack_10 + 0x5c,*(byte *)(iStack_10 + 0x10c) & 7,
                  *(undefined4 *)(*(int *)(iStack_10 + 0x90) + 0x10));
  puStack_30 = (undefined4 *)(*(int *)(*(int *)(iStack_10 + 0x58) + 0x54) + 0xa0);
  Initialize__9MenuSceneFPUcP9BufMemory(auStack_90,*puStack_30,0);
  lVar3 = __nw__FUi(0x178);
  uVar2 = 0;
  if (lVar3 != 0) {
    uVar2 = __ct__8CmdFenceFv(lVar3);
  }
  *(undefined4 *)(iStack_10 + 0x350) = uVar2;
  puStack_34 = (undefined4 *)(*(int *)(*(int *)(iStack_10 + 0x58) + 0x54) + 0x1c);
  CreateFence__8CmdFenceFP9MenuScenePUc(*(undefined4 *)(iStack_10 + 0x350),auStack_90,*puStack_34);
  iVar1 = *(int *)(iStack_10 + 0x350);
  Open__10MenuWindowFUci(iVar1,*(byte *)(iVar1 + 0xb0) & 7,*(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x10));
  uStack_14 = 1;
  __dt__9MenuSceneFv(auStack_90,0xffffffffffffffff);
  return uStack_14;
}

/* JP: 0x00456a00  CmdPhotograph::SafeDelayDelete()   [SafeDelayDelete__13CmdPhotographFv]  size=0x58 */
void SafeDelayDelete__13CmdPhotographFv(int param_1)

{
  ReleaseOT__7MenuObjFv(param_1 + 0x5c);
  (**(code **)(*(int *)(*(int *)(param_1 + 0x350) + 8) + 0xc))();
  (**(code **)(*(int *)(param_1 + 8) + 0xc))();
  return;
}

/* JP: 0x00456a60  CmdPhotograph::Close()   [Close__13CmdPhotographFv]  size=0x78 */
void Close__13CmdPhotographFv(int param_1)

{
  int iVar1;
  
  Close__10MenuWindowFUci(param_1 + 0x5c,((ulong)*(byte *)(param_1 + 0x10c) & 0x3f) >> 3,
                  *(undefined4 *)(*(int *)(param_1 + 0x90) + 0x14));
  iVar1 = *(int *)(param_1 + 0x350);
  Close__10MenuWindowFUci(iVar1,((ulong)*(byte *)(iVar1 + 0xb0) & 0x3f) >> 3,
                  *(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x14));
  return;
}
