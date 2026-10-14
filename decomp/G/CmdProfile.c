/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdProfile   functions: 8
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdProfile.md).
 */

/* JP: 0x00455310  CmdProfile::CmdProfile()   [__ct__10CmdProfileFv]  size=0x4c */
int __ct__10CmdProfileFv(int param_1)

{
  __ct__15CmdPrivateSceneFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__10CmdProfile;
  __ct__10CmdExplainFv(param_1 + 0x60);
  return param_1;
}

/* JP: 0x00455360  CmdProfile::~CmdProfile()   [__dt__10CmdProfileFv]  size=0x84 */
int __dt__10CmdProfileFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__10CmdProfile;
    __dt__10CmdExplainFv(param_1 + 0x60,0xffffffffffffffff);
    __dt__15CmdPrivateSceneFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x004553f0  CmdProfile::GetReady()   [GetReady__10CmdProfileFv]  size=0x12c */
undefined4 GetReady__10CmdProfileFv(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = *(undefined4 *)(*(int *)(param_1 + 0x54) + 0x1c);
  Convert__13MenuDataTableFPUci(uVar1,0);
  Initialize__9MenuSceneFPUcP9BufMemory(param_1 + 0x60,uVar1,0);
  SetInfo__10CmdExplainFP4MenusUcUc(param_1 + 0x60,*(undefined4 *)(param_1 + 0x10),0,0,0);
  *(undefined2 *)(param_1 + 0x586) = 0;
  SetTitle__11CmdTitleLogFPUci
            (*(undefined4 *)(*(int *)(param_1 + 0x58) + 0x60),
             *(undefined4 *)(*(int *)(param_1 + 0x54) + 0x10),0x1e);
  Open__11CmdTitleLogFv(*(undefined4 *)(*(int *)(param_1 + 0x58) + 0x60));
  return 1;
}

/* JP: 0x00455520  CmdProfile::SafeDelayDelete()   [SafeDelayDelete__10CmdProfileFv]  size=0x40 */
void SafeDelayDelete__10CmdProfileFv(int param_1)

{
  ReleaseOT__7MenuObjFv(param_1 + 0xcc);
  (**(code **)(*(int *)(param_1 + 8) + 0xc))();
  return;
}

/* JP: 0x00455560  CmdProfile::Close()   [Close__10CmdProfileFv]  size=0x40 */
void Close__10CmdProfileFv(int param_1)

{
  Close__10CmdExplainFv(param_1 + 0x60);
  Exec__10CmdExplainFUs(param_1 + 0x60,0);
  return;
}

/* JP: 0x004555a0  CmdProfile::Update(short)   [Update__10CmdProfileFs]  size=0x108 */
void Update__10CmdProfileFs(int param_1)

{
  int *piVar1;
  undefined1 uVar2;
  
  piVar1 = *(int **)(*(int *)(param_1 + 0x58) + 0x70);
  memset(param_1 + 0xbc,0,0x10);
  *(int *)(param_1 + 0x5c) = piVar1[1];
  uVar2 = FieldNpcLibrary__Fii(*(undefined1 *)(*piVar1 + 2),0);
  *(undefined1 *)(param_1 + 0xbf) = uVar2;
  *(undefined4 *)(param_1 + 0xc0) = **(undefined4 **)(param_1 + 0x5c);
  *(int *)(param_1 + 200) = *(int *)(param_1 + 0x5c) + 8;
  Open__10CmdExplainFv(param_1 + 0x60);
  return;
}

/* JP: 0x004556b0  CmdProfile::BackGroundRun()   [BackGroundRun__10CmdProfileFv]  size=0x5c */
void BackGroundRun__10CmdProfileFv(int param_1)

{
  Exec__10CmdExplainFUs(param_1 + 0x60,*(undefined2 *)(*(int *)(param_1 + 0x10) + 0x48));
  return;
}

/* JP: 0x00455710  CmdProfile::Release()   [Release__10CmdProfileFv]  size=0x10 */
void Release__10CmdProfileFv(void)

{
  return;
}
