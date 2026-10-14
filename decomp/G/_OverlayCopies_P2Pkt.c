/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: P2Pkt   functions: 3
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/_OverlayCopies_P2Pkt.md).
 */

/* JP: 0x004d0400  P2Pkt::SetOwner(void(*)(void*)*, void*)   [SetOwner__5P2PktFPFPv_vPv]  size=0x34 */
void SetOwner__5P2PktFPFPv_vPv(int param_1,undefined4 param_2,undefined4 param_3)

{
  *(undefined4 *)(param_1 + 0x24) = param_2;
  *(undefined4 *)(param_1 + 0x28) = param_3;
  return;
}

/* JP: 0x004d15d0  P2Pkt::Init()   [Init__5P2PktFv]  size=0x38 */
void Init__5P2PktFv(int param_1)

{
  int iVar1;
  
  iVar1 = GetFace__5P2PktFv(param_1);
  *(undefined2 *)(param_1 + iVar1 * 2 + 0x20) = 0;
  return;
}

/* JP: 0x004d1610  P2Pkt::GetFace()   [GetFace__5P2PktFv]  size=0x54 */
byte GetFace__5P2PktFv(int param_1)

{
  byte bVar1;
  
  if ((long)((ulong)*(byte *)(param_1 + 0x1c) << 0x3e) < 0) {
    bVar1 = m_Env__8VIF1Prim & 1;
  }
  else {
    bVar1 = 0;
  }
  return bVar1;
}
