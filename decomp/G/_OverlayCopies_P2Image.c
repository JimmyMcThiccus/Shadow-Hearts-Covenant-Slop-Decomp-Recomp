/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: P2Image   functions: 1
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/_OverlayCopies_P2Image.md).
 */

/* JP: 0x004dd170  P2Image::GetPktSize(int)   [GetPktSize__7P2ImageFi]  size=0x44 */
int GetPktSize__7P2ImageFi(int param_1)

{
  int iVar1;
  
  if (param_1 < 9) {
    iVar1 = 8;
  }
  else {
    iVar1 = 0;
  }
  return iVar1 + 8;
}
