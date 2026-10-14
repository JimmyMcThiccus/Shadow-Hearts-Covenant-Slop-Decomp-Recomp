/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: BufMemory   functions: 1
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/_OverlayCopies_BufMemory.md).
 */

/* JP: 0x004312d0  BufMemory::getBuffer()   [getBuffer__9BufMemoryFv]  size=0x1c */
undefined4 getBuffer__9BufMemoryFv(int param_1)

{
  return *(undefined4 *)(param_1 + 4);
}
