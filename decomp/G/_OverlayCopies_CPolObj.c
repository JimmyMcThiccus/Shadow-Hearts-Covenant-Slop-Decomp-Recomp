/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CPolObj   functions: 1
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/_OverlayCopies_CPolObj.md).
 */

/* JP: 0x00432000  CPolObj::SetAutoDelete(bool)   [SetAutoDelete__7CPolObjFb]  size=0x2c */
void SetAutoDelete__7CPolObjFb(int param_1,undefined1 param_2)

{
  *(undefined1 *)(param_1 + 0xc) = param_2;
  *(undefined1 *)(param_1 + 0xe) = 0;
  return;
}
