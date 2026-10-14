/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: _AutoMoveInfo   functions: 3
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/_AutoMoveInfo.md).
 */

/* JP: 0x004c07a0  _AutoMoveInfo::_AutoMoveInfo()   [__ct__13_AutoMoveInfoFv]  size=0x30 */
int __ct__13_AutoMoveInfoFv(int param_1)

{
  __ct__7FVectorFv(param_1 + 0x10);
  return param_1;
}

/* JP: 0x004c8370  _AutoMoveInfo::clear()   [clear__13_AutoMoveInfoFv]  size=0x30 */
void clear__13_AutoMoveInfoFv(undefined4 param_1)

{
  memset(param_1,0,0x120);
  return;
}

/* JP: 0x004c83a0  _AutoMoveInfo::FixNode()   [FixNode__13_AutoMoveInfoFv]  size=0xe4 */
void FixNode__13_AutoMoveInfoFv(int param_1)

{
  int iVar1;
  
  if (*(ushort *)(param_1 + 8) == (ushort)*(byte *)(param_1 + 0xc)) {
    if (*(short *)(param_1 + 8) != 0) {
      *(undefined1 *)(param_1 + 0xc) = 0;
      *(undefined2 *)(param_1 + 8) = 0;
    }
  }
  else {
    iVar1 = (uint)*(byte *)(param_1 + 0xc) - (uint)*(ushort *)(param_1 + 8);
    if (*(short *)(param_1 + 8) != 0) {
      memcpy(param_1 + 0x20,param_1 + (uint)*(ushort *)(param_1 + 8) * 0x10 + 0x20,
                      iVar1 * 0x10);
      *(undefined2 *)(param_1 + 8) = 0;
      *(char *)(param_1 + 0xc) = (char)iVar1;
    }
  }
  return;
}
