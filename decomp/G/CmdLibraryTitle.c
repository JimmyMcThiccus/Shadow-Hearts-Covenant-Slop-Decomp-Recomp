/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdLibraryTitle   functions: 4
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdLibraryTitle.md).
 */

/* JP: 0x0047b7c0  CmdLibraryTitle::CmdLibraryTitle()   [__ct__15CmdLibraryTitleFv]  size=0x4c */
int __ct__15CmdLibraryTitleFv(int param_1)

{
  __ct__11CmdSubTitleFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__15CmdLibraryTitle;
  __ct__8MenuTextFv(param_1 + 0x1c8);
  return param_1;
}

/* JP: 0x0047b810  CmdLibraryTitle::~CmdLibraryTitle()   [__dt__15CmdLibraryTitleFv]  size=0x84 */
int __dt__15CmdLibraryTitleFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__15CmdLibraryTitle;
    __dt__8MenuTextFv(param_1 + 0x1c8,0xffffffffffffffff);
    __dt__11CmdSubTitleFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x0047b8a0  CmdLibraryTitle::CreateNumber()   [CreateNumber__15CmdLibraryTitleFv]  size=0x7c */
void CreateNumber__15CmdLibraryTitleFv(int param_1)

{
  SetData__9MenuSceneFUsP8MenuText(param_1,1,param_1 + 0x1c8);
  SetMessage__8MenuTextFPcUiUcUc(param_1 + 0x1c8,*(undefined4 *)(*(int *)(param_1 + 0x24) + 0x28),
                  *(byte *)(param_1 + 0x220) & 7,0,0);
  return;
}

/* JP: 0x0047b920  CmdLibraryTitle::SetNumber()   [SetNumber__15CmdLibraryTitleFv]  size=0x60 */
void SetNumber__15CmdLibraryTitleFv(int param_1)

{
  OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(param_1 + 0x180,param_1 + 0x1c8,((ulong)*(byte *)(param_1 + 0x220) & 0xf) >> 3,0);
  AddPlace__10MenuWindowFP9MenuPlace(param_1 + 0x58,param_1 + 0x1c8);
  return;
}
