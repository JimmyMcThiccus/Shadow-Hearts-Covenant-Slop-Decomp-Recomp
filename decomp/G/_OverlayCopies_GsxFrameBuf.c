/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: GsxFrameBuf   functions: 1
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/_OverlayCopies_GsxFrameBuf.md).
 */

/* JP: 0x004d03e0  GsxFrameBuf::GetBufEntry()   [GetBufEntry__11GsxFrameBufFv]  size=0x20 */
ushort GetBufEntry__11GsxFrameBufFv(ushort *param_1)

{
  return *param_1 & 0x3fff;
}
