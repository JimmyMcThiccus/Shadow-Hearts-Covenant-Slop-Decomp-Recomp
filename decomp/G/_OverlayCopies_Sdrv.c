/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: Sdrv   functions: 1
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/_OverlayCopies_Sdrv.md).
 */

/* JP: 0x004a5470  Sdrv::Unpause()   [Unpause__4SdrvFv]  size=0x2c */
void Unpause__4SdrvFv(undefined4 param_1)

{
  Pause__4SdrvFUi(param_1,1);
  return;
}
