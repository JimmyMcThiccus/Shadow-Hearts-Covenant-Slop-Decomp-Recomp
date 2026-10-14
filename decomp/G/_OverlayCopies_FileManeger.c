/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: FileManeger   functions: 1
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/_OverlayCopies_FileManeger.md).
 */

/* JP: 0x004a2ec0  FileManeger::ReleaseHandle()   [ReleaseHandle__11FileManegerFv]  size=0x30 */
void ReleaseHandle__11FileManegerFv(int param_1)

{
  Release__11FileManegerFPP10FileHandle(param_1,param_1 + 4);
  return;
}
