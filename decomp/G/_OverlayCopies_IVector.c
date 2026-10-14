/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: IVector   functions: 1
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/_OverlayCopies_IVector.md).
 */

/* JP: 0x004d04d0  IVector::IVector(int, int, int, int)   [__ct__7IVectorFiiii]  size=0x58 */
undefined4 *
__ct__7IVectorFiiii(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                   undefined4 param_5)

{
  *param_1 = param_2;
  param_1[1] = param_3;
  param_1[2] = param_4;
  param_1[3] = param_5;
  return param_1;
}
