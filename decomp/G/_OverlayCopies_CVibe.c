/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CVibe   functions: 1
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/_OverlayCopies_CVibe.md).
 */

/* JP: 0x004b8bb0  CVibe::isPlay()   [isPlay__5CVibeFv]  size=0x24 */
bool isPlay__5CVibeFv(int param_1)

{
  return (*(byte *)(param_1 + 0x14) & 3) != 0;
}
