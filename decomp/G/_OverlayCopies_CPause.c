/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CPause   functions: 1
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/_OverlayCopies_CPause.md).
 */

/* JP: 0x00431f90  CPause::isPaused()   [isPaused__6CPauseFv]  size=0x2c */
bool isPaused__6CPauseFv(byte *param_1)

{
  return (*param_1 & 1) != 0;
}
