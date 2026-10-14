/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: _FieldSaveInfo   functions: 1
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/_OverlayCopies__FieldSaveInfo.md).
 */

/* JP: 0x004a40e0  _FieldSaveInfo::FindFileTbl(char*)   [FindFileTbl__14_FieldSaveInfoFPc]  size=0xf4 */
int FindFileTbl__14_FieldSaveInfoFPc(int param_1,undefined4 param_2)

{
  long lVar1;
  int iVar2;
  
  iVar2 = 0;
  while( true ) {
    if (*(int *)(param_1 + 4) <= iVar2) {
      if (*(int *)(param_1 + 4) < 0x40) {
        strcpy(param_1 + *(int *)(param_1 + 4) * 0x10 + 0x990,param_2);
        iVar2 = *(int *)(param_1 + 4);
        *(int *)(param_1 + 4) = iVar2 + 1;
      }
      else {
        iVar2 = -1;
      }
      return iVar2;
    }
    lVar1 = strcmp(param_1 + iVar2 * 0x10 + 0x990,param_2);
    if (lVar1 == 0) break;
    iVar2 = iVar2 + 1;
  }
  return iVar2;
}
