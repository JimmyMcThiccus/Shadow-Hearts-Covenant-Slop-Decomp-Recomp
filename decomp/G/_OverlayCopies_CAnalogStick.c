/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CAnalogStick   functions: 3
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/_OverlayCopies_CAnalogStick.md).
 */

/* JP: 0x004a6110  CAnalogStick::GetDegree   [GetDegree__12CAnalogStickCFv]  size=0x1c */
undefined4 GetDegree__12CAnalogStickCFv(int param_1)

{
  return *(undefined4 *)(param_1 + 0xc);
}

/* JP: 0x004a6130  CAnalogStick::GetGauge   [GetGauge__12CAnalogStickCFv]  size=0x1c */
undefined4 GetGauge__12CAnalogStickCFv(int param_1)

{
  return *(undefined4 *)(param_1 + 4);
}

/* JP: 0x004a6150  CAnalogStick::CAnalogStick(const CAnalogStick&)   [__ct__12CAnalogStickFRC12CAnalogStick]  size=0x8c */
undefined1 * __ct__12CAnalogStickFRC12CAnalogStick(undefined1 *param_1,undefined1 *param_2)

{
  *param_1 = *param_2;
  param_1[1] = param_2[1];
  param_1[2] = param_2[2];
  param_1[3] = param_2[3];
  *(undefined4 *)(param_1 + 4) = *(undefined4 *)(param_2 + 4);
  *(undefined4 *)(param_1 + 8) = *(undefined4 *)(param_2 + 8);
  *(undefined4 *)(param_1 + 0xc) = *(undefined4 *)(param_2 + 0xc);
  return param_1;
}
