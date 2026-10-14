/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: FldSprite   functions: 4
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/FldSprite.md).
 */

/* JP: 0x004ccc60  FldSprite::Set3D(int)   [Set3D__9FldSpriteFi]  size=0x40 */
void Set3D__9FldSpriteFi(int param_1,byte param_2)

{
  *(byte *)(param_1 + 0xa1) = *(byte *)(param_1 + 0xa1) & 0xcf | (param_2 & 3) << 4;
  return;
}

/* JP: 0x004ccdd0  FldSprite::SetFilter(int)   [SetFilter__9FldSpriteFi]  size=0x34 */
void SetFilter__9FldSpriteFi(int param_1,undefined4 param_2)

{
  SetFilter__8P2SpriteFi(param_1 + 0x18,param_2);
  return;
}

/* JP: 0x004cdb40  FldSprite::isDsp()   [isDsp__9FldSpriteFv]  size=0x24 */
ulong isDsp__9FldSpriteFv(int param_1)

{
  return ((ulong)*(byte *)(param_1 + 0xa1) & 7) >> 2;
}

/* JP: 0x004cdb70  FldSprite::SetOffset(float, float)   [SetOffset__9FldSpriteFff]  size=0x34 */
void SetOffset__9FldSpriteFff(undefined4 param_1,undefined4 param_2,int param_3)

{
  *(undefined4 *)(param_3 + 0xa8) = param_1;
  *(undefined4 *)(param_3 + 0xac) = param_2;
  return;
}
