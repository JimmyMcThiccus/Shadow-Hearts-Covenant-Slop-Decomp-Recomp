/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: SSHSys   functions: 2
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/_OverlayCopies_SSHSys.md).
 */

/* JP: 0x004a4d00  SSHSys::SetPauserType(int)   [SetPauserType__6SSHSysFi]  size=0x40 */
void SetPauserType__6SSHSysFi(int param_1,byte param_2)

{
  *(byte *)(param_1 + 0x3c) = *(byte *)(param_1 + 0x3c) & 0xbf | (param_2 & 1) << 6;
  return;
}

/* JP: 0x004a83a0  SSHSys::GetFrameDelta()   [GetFrameDelta__6SSHSysFv]  size=0x1c */
undefined4 GetFrameDelta__6SSHSysFv(int param_1)

{
  return *(undefined4 *)(param_1 + 0x20);
}
