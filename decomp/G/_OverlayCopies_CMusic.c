/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CMusic   functions: 1
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/_OverlayCopies_CMusic.md).
 */

/* JP: 0x004a2d70  CMusic::SetCallback(void(*)(unsigned char, unsigned int, unsigned int)*, unsigned int)   [SetCallback__6CMusicFPFUcUiUi_vUi]  size=0x34 */
void SetCallback__6CMusicFPFUcUiUi_vUi(int param_1,undefined4 param_2,undefined4 param_3)

{
  *(undefined4 *)(param_1 + 0x84) = param_2;
  *(undefined4 *)(param_1 + 0x88) = param_3;
  return;
}
