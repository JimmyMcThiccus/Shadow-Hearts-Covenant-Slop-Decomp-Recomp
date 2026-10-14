/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: Menu   functions: 1
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/_OverlayCopies_Menu.md).
 */

/* JP: 0x00474210  Menu::ReadData(int, BufMemory*, int, char*, void*)   [ReadData__4MenuFiP9BufMemoryiPcPv]  size=0x38 */
void ReadData__4MenuFiP9BufMemoryiPcPv
               (undefined8 param_1,undefined4 param_2,undefined8 param_3,undefined8 param_4,
               int param_5)

{
  (**(code **)(*(int *)(param_5 + 0x14) + 0x20))(param_5,param_2);
  return;
}
