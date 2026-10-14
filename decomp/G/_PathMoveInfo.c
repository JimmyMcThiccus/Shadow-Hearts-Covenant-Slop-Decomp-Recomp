/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: _PathMoveInfo   functions: 1
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/_PathMoveInfo.md).
 */

/* JP: 0x004c8490  _PathMoveInfo::clear()   [clear__13_PathMoveInfoFv]  size=0x30 */
void clear__13_PathMoveInfoFv(undefined4 param_1)

{
  memset(param_1,0,0x14);
  return;
}
