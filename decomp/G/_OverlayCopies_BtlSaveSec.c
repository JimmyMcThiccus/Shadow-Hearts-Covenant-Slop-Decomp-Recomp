/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: BtlSaveSec   functions: 2
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/_OverlayCopies_BtlSaveSec.md).
 */

/* JP: 0x004b2400  BtlSaveSec::SetGranHatenaMode(bool)   [SetGranHatenaMode__10BtlSaveSecFb]  size=0x38 */
void SetGranHatenaMode__10BtlSaveSecFb(byte param_1)

{
  *(byte *)(ourBtlSaveDat__10BtlSaveSec + 0xd48) = *(byte *)(ourBtlSaveDat__10BtlSaveSec + 0xd48) & 0xfd | (param_1 & 1) << 1;
  return;
}

/* JP: 0x004b2440  BtlSaveSec::SetYoahismMode(bool)   [SetYoahismMode__10BtlSaveSecFb]  size=0x38 */
void SetYoahismMode__10BtlSaveSecFb(byte param_1)

{
  *(byte *)(ourBtlSaveDat__10BtlSaveSec + 0xd48) = *(byte *)(ourBtlSaveDat__10BtlSaveSec + 0xd48) & 0xfb | (param_1 & 1) << 2;
  return;
}
