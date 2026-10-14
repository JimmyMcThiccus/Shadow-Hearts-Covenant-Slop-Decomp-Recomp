/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CScrCapture   functions: 1
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/_OverlayCopies_CScrCapture.md).
 */

/* JP: 0x004a5210  CScrCapture::SetLayer(int)   [SetLayer__11CScrCaptureFi]  size=0x40 */
void SetLayer__11CScrCaptureFi(int param_1,byte param_2)

{
  *(byte *)(param_1 + 0x1c) = *(byte *)(param_1 + 0x1c) & 0xc3 | (param_2 & 0xf) << 2;
  return;
}
