/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: Cursor   functions: 1
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/_OverlayCopies_Cursor.md).
 */

/* JP: 0x004b61b0  Cursor::SetCancel(unsigned char)   [SetCancel__6CursorFUc]  size=0x3c */
void SetCancel__6CursorFUc(int param_1,byte param_2)

{
  *(byte *)(param_1 + 0xfb) = *(byte *)(param_1 + 0xfb) & 0xdf | (param_2 & 1) << 5;
  return;
}
