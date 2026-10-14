/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdGoodsButton   functions: 2
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdGoodsButton.md).
 */

/* JP: 0x0043df10  CmdGoodsButton::~CmdGoodsButton()   [__dt__14CmdGoodsButtonFv]  size=0x8c */
int __dt__14CmdGoodsButtonFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    __dt__8MenuTextFv(param_1 + 0xc0,0xffffffffffffffff);
    __dt__10MenuSpriteFv(param_1 + 0x60,0xffffffffffffffff);
    __dt__10MenuSpriteFv(param_1,0xffffffffffffffff);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x0043dfa0  CmdGoodsButton::CmdGoodsButton()   [__ct__14CmdGoodsButtonFv]  size=0x4c */
int __ct__14CmdGoodsButtonFv(int param_1)

{
  __ct__10MenuSpriteFv(param_1);
  __ct__10MenuSpriteFv(param_1 + 0x60);
  __ct__8MenuTextFv(param_1 + 0xc0);
  return param_1;
}
