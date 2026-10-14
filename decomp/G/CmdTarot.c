/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdTarot   functions: 8
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdTarot.md).
 */

/* JP: 0x00455720  CmdTarot::CmdTarot()   [__ct__8CmdTarotFv]  size=0x5c */
int __ct__8CmdTarotFv(int param_1)

{
  __ct__15CmdPrivateSceneFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__8CmdTarot;
  __ct__13CmdTarotGoodsFv(param_1 + 0x5c);
  __ct__13CmdTarotImageFv(param_1 + 0x188);
  return param_1;
}

/* JP: 0x00455780  CmdTarot::~CmdTarot()   [__dt__8CmdTarotFv]  size=0x9c */
int __dt__8CmdTarotFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__8CmdTarot;
    __dt__13CmdTarotImageFv(param_1 + 0x188,0xffffffffffffffff);
    __dt__13CmdTarotGoodsFv(param_1 + 0x5c,0xffffffffffffffff);
    __dt__15CmdPrivateSceneFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x00455820  CmdTarot::GetReady()   [GetReady__8CmdTarotFv]  size=0x180 */
undefined4 GetReady__8CmdTarotFv(int param_1)

{
  *(int *)(param_1 + 0x18) = *(int *)(param_1 + 0x10) + 0x3a0;
  *(undefined2 *)(param_1 + 0x312) = 0x17;
  SetTitle__11CmdTitleLogFPUci
            (*(undefined4 *)(*(int *)(param_1 + 0x58) + 0x60),
             *(undefined4 *)(*(int *)(param_1 + 0x54) + 0x10),0x13);
  Open__11CmdTitleLogFv(*(undefined4 *)(*(int *)(param_1 + 0x58) + 0x60));
  CreateScene__13CmdTarotGoodsFP8CmdTarot(param_1 + 0x5c,param_1);
  CreateScene__13CmdTarotImageFP8CmdTarot(param_1 + 0x188,param_1);
  Open__10MenuWindowFUci(param_1 + 0x5c,*(byte *)(param_1 + 0x10c) & 7,
                  *(undefined4 *)(*(int *)(param_1 + 0x90) + 0x10));
  *(byte *)(param_1 + 0x23) = *(byte *)(param_1 + 0x23) & 0xdf | 0x20;
  return 1;
}

/* JP: 0x004559a0  CmdTarot::Run()   [Run__8CmdTarotFv]  size=0x1bc */
undefined4 Run__8CmdTarotFv(int param_1)

{
  ushort uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  
  uVar1 = *(ushort *)(*(int *)(param_1 + 0x10) + 0x48);
  iVar2 = *(int *)(*(int *)(param_1 + 0x18) + 0xec);
  UpdateScene__13CmdTarotImageFP8CmdTarot(param_1 + 0x188,param_1);
  if ((uVar1 & 0x4000) == 0) {
    iVar4 = MoveVertical__9MenuSceneFi(param_1,0);
    if (iVar2 != iVar4) {
      Select__13CmdTarotGoodsFP8CmdTarotP9MenuGroupP9MenuGroup(param_1 + 0x5c,param_1,iVar4,iVar2);
      *(undefined2 *)(param_1 + 0x278) = *(undefined2 *)(iVar4 + 0x16);
      *(byte *)(param_1 + 0x19a) = *(byte *)(param_1 + 0x19a) & 0xfe;
    }
    uVar3 = 0;
  }
  else {
    Leave__6CursorFv(*(undefined4 *)(param_1 + 0x18));
    Select__13CmdTarotGoodsFP8CmdTarotP9MenuGroupP9MenuGroup(param_1 + 0x5c,param_1,0,iVar2);
    SetScroll__10MenuWindowFss(param_1 + 0x5c,0,0);
    Finish__10MenuWindowFv(param_1 + 0x5c);
    Close__10MenuWindowFUci(param_1 + 0x188,((ulong)*(byte *)(param_1 + 0x238) & 0x3f) >> 3,
                    *(undefined4 *)(*(int *)(param_1 + 0x1bc) + 0x14));
    uVar3 = 1;
  }
  return uVar3;
}

/* JP: 0x00455b60  CmdTarot::SafeDelayDelete()   [SafeDelayDelete__8CmdTarotFv]  size=0x50 */
void SafeDelayDelete__8CmdTarotFv(int param_1)

{
  ReleaseOT__7MenuObjFv(param_1 + 0x5c);
  ReleaseOT__7MenuObjFv(param_1 + 0x188);
  (**(code **)(*(int *)(param_1 + 8) + 0xc))();
  return;
}

/* JP: 0x00455bb0  CmdTarot::Close()   [Close__8CmdTarotFv]  size=0x48 */
void Close__8CmdTarotFv(int param_1)

{
  Close__10MenuWindowFUci(param_1 + 0x5c,((ulong)*(byte *)(param_1 + 0x10c) & 0x3f) >> 3,
                  *(undefined4 *)(*(int *)(param_1 + 0x90) + 0x14));
  return;
}

/* JP: 0x00455c00  CmdTarot::ReadyScene()   [ReadyScene__8CmdTarotFv]  size=0xd0 */
undefined4 ReadyScene__8CmdTarotFv(int param_1)

{
  undefined8 uVar1;
  
  uVar1 = GetPlace__10MenuWindowFss(param_1 + 0x5c,0,0);
  Select__6CursorFP9MenuPlace(*(undefined4 *)(param_1 + 0x18),uVar1);
  Select__13CmdTarotGoodsFP8CmdTarotP9MenuGroupP9MenuGroup(param_1 + 0x5c,param_1,uVar1,0);
  *(undefined2 *)(param_1 + 0x278) = *(undefined2 *)((int)uVar1 + 0x16);
  *(byte *)(param_1 + 0x19a) = *(byte *)(param_1 + 0x19a) & 0xfe;
  SetChengePCMode__10CmdPCSceneFUc(*(undefined4 *)(param_1 + 0x58),0);
  return 1;
}

/* JP: 0x00455cd0  CmdTarot::Release()   [Release__8CmdTarotFv]  size=0x10 */
void Release__8CmdTarotFv(void)

{
  return;
}
