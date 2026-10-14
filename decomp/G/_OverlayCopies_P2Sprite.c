/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: P2Sprite   functions: 7
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/_OverlayCopies_P2Sprite.md).
 */

/* JP: 0x004ccc20  P2Sprite::SetHotSpot(float, float)   [SetHotSpot__8P2SpriteFff]  size=0x34 */
void SetHotSpot__8P2SpriteFff(undefined4 param_1,undefined4 param_2,int param_3)

{
  *(undefined4 *)(param_3 + 0x30) = param_1;
  *(undefined4 *)(param_3 + 0x34) = param_2;
  return;
}

/* JP: 0x004ccca0  P2Sprite::SetSize(float, float)   [SetSize__8P2SpriteFff]  size=0x48 */
void SetSize__8P2SpriteFff(undefined4 param_1,undefined4 param_2,int param_3)

{
  *(undefined4 *)(param_3 + 0x18) = param_1;
  *(undefined4 *)(param_3 + 0x1c) = param_2;
  SetDirty__8P2SpriteFv(param_3);
  return;
}

/* JP: 0x004cccf0  P2Sprite::SetDirty()   [SetDirty__8P2SpriteFv]  size=0x34 */
void SetDirty__8P2SpriteFv(int param_1)

{
  *(byte *)(param_1 + 2) = *(byte *)(param_1 + 2) & 0xfe | 1;
  return;
}

/* JP: 0x004ccd30  P2Sprite::SetTexSize(float, float)   [SetTexSize__8P2SpriteFff]  size=0x48 */
void SetTexSize__8P2SpriteFff(undefined4 param_1,undefined4 param_2,int param_3)

{
  *(undefined4 *)(param_3 + 0x28) = param_1;
  *(undefined4 *)(param_3 + 0x2c) = param_2;
  SetDirty__8P2SpriteFv(param_3);
  return;
}

/* JP: 0x004ccd80  P2Sprite::SetTexPos(float, float)   [SetTexPos__8P2SpriteFff]  size=0x48 */
void SetTexPos__8P2SpriteFff(undefined4 param_1,undefined4 param_2,int param_3)

{
  *(undefined4 *)(param_3 + 0x20) = param_1;
  *(undefined4 *)(param_3 + 0x24) = param_2;
  SetDirty__8P2SpriteFv(param_3);
  return;
}

/* JP: 0x004cce10  P2Sprite::SetFilter(int)   [SetFilter__8P2SpriteFi]  size=0x40 */
void SetFilter__8P2SpriteFi(int param_1,byte param_2)

{
  *(byte *)(param_1 + 2) = *(byte *)(param_1 + 2) & 0xf7 | (param_2 & 1) << 3;
  return;
}

/* JP: 0x004cdbb0  P2Sprite::SetScale(float, float)   [SetScale__8P2SpriteFff]  size=0x48 */
void SetScale__8P2SpriteFff(undefined4 param_1,undefined4 param_2,int param_3)

{
  *(undefined4 *)(param_3 + 0x38) = param_1;
  *(undefined4 *)(param_3 + 0x3c) = param_2;
  SetDirty__8P2SpriteFv(param_3);
  return;
}
