/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: _rgba32   functions: 4
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/_OverlayCopies__rgba32.md).
 */

/* JP: 0x0049a300  _rgba32::__as(const _rgba32&)   [__as__7_rgba32FRC7_rgba32]  size=0x5c */
undefined1 * __as__7_rgba32FRC7_rgba32(undefined1 *param_1,undefined1 *param_2)

{
  *param_1 = *param_2;
  param_1[1] = param_2[1];
  param_1[2] = param_2[2];
  param_1[3] = param_2[3];
  return param_1;
}

/* JP: 0x0049a360  _rgba32::_rgba32(unsigned char, unsigned char, unsigned char, unsigned char)   [__ct__7_rgba32FUcUcUcUc]  size=0x58 */
undefined1 *
__ct__7_rgba32FUcUcUcUc
          (undefined1 *param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4,
          undefined1 param_5)

{
  *param_1 = param_2;
  param_1[1] = param_3;
  param_1[2] = param_4;
  param_1[3] = param_5;
  return param_1;
}

/* JP: 0x004dc120  _rgba32::GetVal   [GetVal__7_rgba32CFv]  size=0x1c */
undefined4 GetVal__7_rgba32CFv(undefined4 *param_1)

{
  return *param_1;
}

/* JP: 0x004dc140  _rgba32::_rgba32(unsigned int)   [__ct__7_rgba32FUi]  size=0x28 */
undefined4 * __ct__7_rgba32FUi(undefined4 *param_1,undefined4 param_2)

{
  *param_1 = param_2;
  return param_1;
}
