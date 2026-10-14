/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: FontItem   functions: 1
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/_OverlayCopies_FontItem.md).
 */

/* JP: 0x004b5260  FontItem::SetVariable(unsigned char)   [SetVariable__8FontItemFUc]  size=0x3c */
void SetVariable__8FontItemFUc(int param_1,byte param_2)

{
  *(byte *)(param_1 + 0x58) = *(byte *)(param_1 + 0x58) & 0xf7 | (param_2 & 1) << 3;
  return;
}
