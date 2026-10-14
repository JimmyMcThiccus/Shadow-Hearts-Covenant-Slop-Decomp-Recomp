/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdGoodsSubTitle   functions: 2
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdGoodsSubTitle.md).
 */

/* JP: 0x004781d0  CmdGoodsSubTitle::~CmdGoodsSubTitle()   [__dt__16CmdGoodsSubTitleFv]  size=0x94 */
int __dt__16CmdGoodsSubTitleFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    __dt__8MenuTextFv(param_1 + 0x170,0xffffffffffffffff);
    __destroy_arr(param_1 + 0x50,0x2661a0,0x60,3);
    __dt__9MenuGroupFv(param_1,0xffffffffffffffff);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x00478510  CmdGoodsSubTitle::CmdGoodsSubTitle()   [__ct__16CmdGoodsSubTitleFv]  size=0x64 */
int __ct__16CmdGoodsSubTitleFv(int param_1)

{
  __ct__9MenuGroupFv(param_1);
  __construct_array(param_1 + 0x50,0x266140,0x2661a0,0x60,3);
  __ct__8MenuTextFv(param_1 + 0x170);
  return param_1;
}
