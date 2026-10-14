/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: P2Clut   functions: 3
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/_OverlayCopies_P2Clut.md).
 */

/* JP: 0x004a3e00  P2Clut::isCreate()   [isCreate__6P2ClutFv]  size=0x14 */
bool isCreate__6P2ClutFv(void)

{
  return 0 < m_refCount__6P2Clut;
}

/* JP: 0x004d1560  P2Clut::GetEntry(int)   [GetEntry__6P2ClutFi]  size=0x60 */
int GetEntry__6P2ClutFi(int param_1)

{
  int iVar1;
  
  if (m_refCount__6P2Clut == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = GetBufEntry__11GsxFrameBufFv(0x42be80);
    iVar1 = param_1 * 4 + iVar1;
  }
  return iVar1;
}

/* JP: 0x004d15c0  P2Clut::GetPSM()   [GetPSM__6P2ClutFv]  size=0xc */
undefined8 GetPSM__6P2ClutFv(void)

{
  return 0;
}
