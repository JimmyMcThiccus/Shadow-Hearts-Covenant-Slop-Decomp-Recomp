/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: PutiObject   functions: 4
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/_OverlayCopies_PutiObject.md).
 */

/* JP: 0x004cefe0  PutiObject::AddAddress()   [AddAddress__10PutiObjectFv]  size=0x2c */
undefined4 AddAddress__10PutiObjectFv(int param_1)

{
  *(int *)(param_1 + 0x88) = *(int *)(param_1 + 0x88) + 0x10;
  return *(undefined4 *)(param_1 + 0x88);
}

/* JP: 0x004cf010  PutiObject::GetAddress()   [GetAddress__10PutiObjectFv]  size=0x1c */
undefined4 GetAddress__10PutiObjectFv(int param_1)

{
  return *(undefined4 *)(param_1 + 0x88);
}

/* JP: 0x004cf090  PutiObject::CalcColor()   [CalcColor__10PutiObjectFv]  size=0x10 */
void CalcColor__10PutiObjectFv(void)

{
  return;
}

/* JP: 0x004cf0a0  PutiObject::OnChangeState(int)   [OnChangeState__10PutiObjectFi]  size=0x24 */
void OnChangeState__10PutiObjectFi(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 0x94) = param_2;
  return;
}
