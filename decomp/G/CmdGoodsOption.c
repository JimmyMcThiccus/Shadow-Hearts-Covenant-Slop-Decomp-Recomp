/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdGoodsOption   functions: 2
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdGoodsOption.md).
 */

/* JP: 0x00446da0  CmdGoodsOption::~CmdGoodsOption()   [__dt__14CmdGoodsOptionFv]  size=0x74 */
int __dt__14CmdGoodsOptionFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    __dt__8MenuTextFv(param_1 + 0x60,0xffffffffffffffff);
    __dt__10MenuSpriteFv(param_1,0xffffffffffffffff);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x00446e20  CmdGoodsOption::CmdGoodsOption()   [__ct__14CmdGoodsOptionFv]  size=0x3c */
int __ct__14CmdGoodsOptionFv(int param_1)

{
  __ct__10MenuSpriteFv(param_1);
  __ct__8MenuTextFv(param_1 + 0x60);
  return param_1;
}
