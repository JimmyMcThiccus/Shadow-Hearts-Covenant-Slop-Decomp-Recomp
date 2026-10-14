/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CPad   functions: 4
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/_OverlayCopies_CPad.md).
 */

/* JP: 0x004a3360  CPad::SetPriority(const CPad::Priority&)   [SetPriority__4CPadFRCQ24CPad8Priority]  size=0x28 */
void SetPriority__4CPadFRCQ24CPad8Priority(int param_1,undefined4 *param_2)

{
  *(undefined4 *)(param_1 + 8) = *param_2;
  return;
}

/* JP: 0x004a5950  CPad::GetReal   [GetReal__4CPadCFv]  size=0x34 */
undefined2 GetReal__4CPadCFv(int param_1)

{
  return *(undefined2 *)(*(int *)(&m_pCoreArray__4CPad + *(int *)(param_1 + 4) * 4) + 0x6a);
}

/* JP: 0x004a61e0  CPad::GetAnalogStickL   [GetAnalogStickL__4CPadCFv]  size=0x34 */
int GetAnalogStickL__4CPadCFv(int param_1)

{
  return *(int *)(&m_pCoreArray__4CPad + *(int *)(param_1 + 4) * 4) + 0x78;
}

/* JP: 0x004a6220  CPad::GetPress   [GetPress__4CPadCFv]  size=0x34 */
undefined2 GetPress__4CPadCFv(int param_1)

{
  return *(undefined2 *)(*(int *)(&m_pCoreArray__4CPad + *(int *)(param_1 + 4) * 4) + 0x6c);
}
