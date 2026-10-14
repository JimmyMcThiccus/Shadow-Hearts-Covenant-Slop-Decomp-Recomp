/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: Model   functions: 2
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/_OverlayCopies_Model.md).
 */

/* JP: 0x004cdf80  Model::GetTexture(int)   [GetTexture__5ModelFi]  size=0x3c */
int GetTexture__5ModelFi(int param_1,int param_2)

{
  return *(int *)(param_1 + 0x4c) + param_2 * 0x4c;
}

/* JP: 0x004cdfc0  Model::GetTextureCount()   [GetTextureCount__5ModelFv]  size=0x54 */
undefined2 GetTextureCount__5ModelFv(int param_1)

{
  undefined2 uVar1;
  
  if (*(int *)(param_1 + 100) == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = *(undefined2 *)(*(int *)(param_1 + 100) + 4);
  }
  return uVar1;
}
