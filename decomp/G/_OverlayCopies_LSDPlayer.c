/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: LSDPlayer   functions: 1
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/_OverlayCopies_LSDPlayer.md).
 */

/* JP: 0x004a5920  LSDPlayer::setStartCallBack(bool(*)(void)*)   [setStartCallBack__9LSDPlayerFPFv_b]  size=0x24 */
void setStartCallBack__9LSDPlayerFPFv_b(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 0x7c) = param_2;
  return;
}
