/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdGoodsScoreRank   functions: 2
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdGoodsScoreRank.md).
 */

/* JP: 0x004769d0  CmdGoodsScoreRank::~CmdGoodsScoreRank()   [__dt__17CmdGoodsScoreRankFv]  size=0x8c */
int __dt__17CmdGoodsScoreRankFv(int param_1,short param_2)

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

/* JP: 0x00476f30  CmdGoodsScoreRank::CmdGoodsScoreRank()   [__ct__17CmdGoodsScoreRankFv]  size=0x4c */
int __ct__17CmdGoodsScoreRankFv(int param_1)

{
  __ct__9MenuGroupFv(param_1);
  __ct__8MenuTextFv(param_1 + 0x50);
  __ct__8MenuTextFv(param_1 + 0xd0);
  return param_1;
}
