/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CGhostEfx   functions: 1
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/_OverlayCopies_CGhostEfx.md).
 */

/* JP: 0x004c2950  CGhostEfx::AttachModel(Model*)   [AttachModel__9CGhostEfxFP5Model]  size=0x24 */
void AttachModel__9CGhostEfxFP5Model(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 2000) = param_2;
  return;
}
