/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdGoods   functions: 2
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdGoods.md).
 */

/* JP: 0x00450670  CmdGoods::~CmdGoods()   [__dt__8CmdGoodsFv]  size=0x8c */
int __dt__8CmdGoodsFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    __dt__8MenuTextFv(param_1 + 0xd0,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1 + 0x50,0xffffffffffffffff);
    __dt__9MenuGroupFv(param_1,0xffffffffffffffff);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x00454640  CmdGoods::CmdGoods()   [__ct__8CmdGoodsFv]  size=0x4c */
int __ct__8CmdGoodsFv(int param_1)

{
  __ct__9MenuGroupFv(param_1);
  __ct__8MenuTextFv(param_1 + 0x50);
  __ct__8MenuTextFv(param_1 + 0xd0);
  return param_1;
}
