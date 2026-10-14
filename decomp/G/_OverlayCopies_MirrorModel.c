/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: MirrorModel   functions: 2
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/_OverlayCopies_MirrorModel.md).
 */

/* JP: 0x004c2f20  MirrorModel::setMirror(bool, bool, bool)   [setMirror__11MirrorModelFbbb]  size=0x44 */
void setMirror__11MirrorModelFbbb
               (int param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4)

{
  *(undefined1 *)(param_1 + 0x4b4) = param_2;
  *(undefined1 *)(param_1 + 0x4b5) = param_3;
  *(undefined1 *)(param_1 + 0x4b6) = param_4;
  return;
}

/* JP: 0x004c2f70  MirrorModel::setOffset(float, float, float)   [setOffset__11MirrorModelFfff]  size=0x44 */
void setOffset__11MirrorModelFfff
               (undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  *(undefined4 *)(param_4 + 0x4b8) = param_1;
  *(undefined4 *)(param_4 + 0x4bc) = param_2;
  *(undefined4 *)(param_4 + 0x4c0) = param_3;
  return;
}
