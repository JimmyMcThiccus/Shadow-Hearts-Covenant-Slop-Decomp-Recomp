/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdHelpMenuData   functions: 2
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdHelpMenuData.md).
 */

/* JP: 0x0045a8c0  CmdHelpMenuData::~CmdHelpMenuData()   [__dt__15CmdHelpMenuDataFv]  size=0x74 */
int __dt__15CmdHelpMenuDataFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    __dt__10MenuSpriteFv(param_1 + 0x80,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1,0xffffffffffffffff);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x0045ae50  CmdHelpMenuData::CmdHelpMenuData()   [__ct__15CmdHelpMenuDataFv]  size=0x3c */
int __ct__15CmdHelpMenuDataFv(int param_1)

{
  __ct__8MenuTextFv(param_1);
  __ct__10MenuSpriteFv(param_1 + 0x80);
  return param_1;
}
