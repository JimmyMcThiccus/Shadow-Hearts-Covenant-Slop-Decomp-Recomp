/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CScript   functions: 1
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/_OverlayCopies_CScript.md).
 */

/* JP: 0x004a3b80  CScript::Pause(int)   [Pause__7CScriptFi]  size=0x40 */
void Pause__7CScriptFi(int param_1,byte param_2)

{
  *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xdf | (param_2 & 1) << 5;
  return;
}
