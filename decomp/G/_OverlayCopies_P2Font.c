/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: P2Font   functions: 1
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/_OverlayCopies_P2Font.md).
 */

/* JP: 0x004dd110  P2Font::~P2Font()   [__dt__6P2FontFv]  size=0x54 */
int __dt__6P2FontFv(int param_1,short param_2)

{
  if ((param_1 != 0) && (0 < param_2)) {
    __dl__FPv(param_1);
  }
  return param_1;
}
