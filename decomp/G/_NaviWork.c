/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: _NaviWork   functions: 1
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/_NaviWork.md).
 */

/* JP: 0x004cf2e0  _NaviWork::_NaviWork()   [__ct__9_NaviWorkFv]  size=0x5c */
int __ct__9_NaviWorkFv(int param_1)

{
  __ct__7FVectorFv(param_1);
  __ct__7FVectorFv(param_1 + 0x10);
  __ct__7FVectorFv(param_1 + 0x20);
  __ct__7FVectorFv(param_1 + 0x30);
  return param_1;
}
