/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: ExModel   functions: 2
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/_OverlayCopies_ExModel.md).
 */

/* JP: 0x00434ae0  ExModel::SetScale(FVector&)   [SetScale__7ExModelFR7FVector]  size=0x34 */
void SetScale__7ExModelFR7FVector(int param_1,undefined4 param_2)

{
  __as__7FVectorFRC7FVector(param_1 + 0x4e0,param_2);
  return;
}

/* JP: 0x00434b20  ExModel::SetAlphaWeight(float)   [SetAlphaWeight__7ExModelFf]  size=0x24 */
void SetAlphaWeight__7ExModelFf(undefined4 param_1,int param_2)

{
  *(undefined4 *)(param_2 + 0x4f0) = param_1;
  return;
}
