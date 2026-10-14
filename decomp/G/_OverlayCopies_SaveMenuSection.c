/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: SaveMenuSection   functions: 9
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/_OverlayCopies_SaveMenuSection.md).
 */

/* JP: 0x004a8210  SaveMenuSection::GetOption()   [GetOption__15SaveMenuSectionFv]  size=0x14 */
int GetOption__15SaveMenuSectionFv(void)

{
  return *(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x26c;
}

/* JP: 0x004b0950  SaveMenuSection::SetMenuFlag(char, char)   [SetMenuFlag__15SaveMenuSectionFcc]  size=0x38 */
void SetMenuFlag__15SaveMenuSectionFcc(char param_1,undefined1 param_2)

{
  *(undefined1 *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + (int)param_1 + 0x300) = param_2;
  return;
}

/* JP: 0x004b0990  SaveMenuSection::SetHelp(short)   [SetHelp__15SaveMenuSectionFs]  size=0x84 */
void SetHelp__15SaveMenuSectionFs(short param_1)

{
  int iVar1;
  uint uVar2;
  ulong uVar3;
  
  uVar3 = (long)param_1 & 7;
  uVar2 = (uint)uVar3;
  if (((long)param_1 < 0) && (uVar3 != 0)) {
    uVar2 = uVar2 - 8;
  }
  iVar1 = (int)param_1;
  if (param_1 < 0) {
    iVar1 = iVar1 + 7;
  }
  iVar1 = *(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + (iVar1 >> 3);
  *(byte *)(iVar1 + 0x180) = *(byte *)(iVar1 + 0x180) | (byte)(1 << (uVar2 & 0x1f));
  return;
}

/* JP: 0x004b23d0  SaveMenuSection::SetSaveID(unsigned int)   [SetSaveID__15SaveMenuSectionFUi]  size=0x24 */
void SetSaveID__15SaveMenuSectionFUi(undefined4 param_1)

{
  *(undefined4 *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x10) = param_1;
  return;
}

/* JP: 0x004b2480  SaveMenuSection::SetCurrentPartySet(char)   [SetCurrentPartySet__15SaveMenuSectionFc]  size=0x24 */
void SetCurrentPartySet__15SaveMenuSectionFc(undefined1 param_1)

{
  *(undefined1 *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x80) = param_1;
  return;
}

/* JP: 0x004b24b0  SaveMenuSection::SetLockParty(unsigned char)   [SetLockParty__15SaveMenuSectionFUc]  size=0x24 */
void SetLockParty__15SaveMenuSectionFUc(undefined1 param_1)

{
  *(undefined1 *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x81) = param_1;
  return;
}

/* JP: 0x004b2850  SaveMenuSection::GetPartySet(char)   [GetPartySet__15SaveMenuSectionFc]  size=0x34 */
int GetPartySet__15SaveMenuSectionFc(char param_1)

{
  return *(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + param_1 * 0x20 + 0x84;
}

/* JP: 0x004b2890  SaveMenuSection::GetSaveID()   [GetSaveID__15SaveMenuSectionFv]  size=0x14 */
undefined4 GetSaveID__15SaveMenuSectionFv(void)

{
  return *(undefined4 *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x10);
}

/* JP: 0x004b9530  SaveMenuSection::GetParty()   [GetParty__15SaveMenuSectionFv]  size=0x14 */
int GetParty__15SaveMenuSectionFv(void)

{
  return *(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x80;
}
