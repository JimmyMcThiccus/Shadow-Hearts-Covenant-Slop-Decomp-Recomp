/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: FldTimer   functions: 5
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/FldTimer.md).
 */

/* JP: 0x004a3d80  FldTimer::Mask(int)   [Mask__8FldTimerFi]  size=0x40 */
void Mask__8FldTimerFi(int param_1,byte param_2)

{
  *(byte *)(param_1 + 0x61) = *(byte *)(param_1 + 0x61) & 0xf7 | (param_2 & 1) << 3;
  return;
}

/* JP: 0x004a80f0  FldTimer::ClrAlerm()   [ClrAlerm__8FldTimerFv]  size=0x34 */
void ClrAlerm__8FldTimerFv(int param_1)

{
  *(byte *)(param_1 + 0x61) = *(byte *)(param_1 + 0x61) & 0xfd;
  return;
}

/* JP: 0x004a8130  FldTimer::isAlerm()   [isAlerm__8FldTimerFv]  size=0x24 */
ulong isAlerm__8FldTimerFv(int param_1)

{
  return ((ulong)*(byte *)(param_1 + 0x61) & 3) >> 1;
}

/* JP: 0x004b0440  FldTimer::GetCount()   [GetCount__8FldTimerFv]  size=0x1c */
undefined4 GetCount__8FldTimerFv(int param_1)

{
  return *(undefined4 *)(param_1 + 0x58);
}

/* JP: 0x004b0460  FldTimer::SetPos(int, int)   [SetPos__8FldTimerFii]  size=0x44 */
void SetPos__8FldTimerFii(int param_1,undefined2 param_2,undefined2 param_3)

{
  *(undefined2 *)(param_1 + 100) = param_2;
  *(undefined2 *)(param_1 + 0x66) = param_3;
  return;
}
