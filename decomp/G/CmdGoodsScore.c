/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdGoodsScore   functions: 2
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdGoodsScore.md).
 */

/* JP: 0x00476010  CmdGoodsScore::~CmdGoodsScore()   [__dt__13CmdGoodsScoreFv]  size=0x9c */
int __dt__13CmdGoodsScoreFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    __dt__8MenuTextFv(param_1 + 0x150,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1 + 0xd0,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1 + 0x50,0xffffffffffffffff);
    __dt__9MenuGroupFv(param_1,0xffffffffffffffff);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x004760b0  CmdGoodsScore::CmdGoodsScore()   [__ct__13CmdGoodsScoreFv]  size=0x5c */
int __ct__13CmdGoodsScoreFv(int param_1)

{
  __ct__9MenuGroupFv(param_1);
  __ct__8MenuTextFv(param_1 + 0x50);
  __ct__8MenuTextFv(param_1 + 0xd0);
  __ct__8MenuTextFv(param_1 + 0x150);
  return param_1;
}
