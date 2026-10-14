/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: _QWD   functions: 2
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/_OverlayCopies__QWD.md).
 */

/* JP: 0x004cef80  _QWD::__as(const _QWD&)   [__as__4_QWDFRC4_QWD]  size=0x2c */
undefined4 * __as__4_QWDFRC4_QWD(undefined4 *param_1,undefined8 *param_2)

{
  undefined8 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  uVar1 = *param_2;
  uVar2 = *(undefined4 *)(param_2 + 1);
  uVar3 = *(undefined4 *)((int)param_2 + 0xc);
  *param_1 = (int)uVar1;
  param_1[1] = (int)((ulong)uVar1 >> 0x20);
  param_1[2] = uVar2;
  param_1[3] = uVar3;
  return param_1;
}

/* JP: 0x004cefb0  _QWD::_QWD()   [__ct__4_QWDFv]  size=0x2c */
undefined4 __ct__4_QWDFv(undefined4 param_1)

{
  __ct__7FVectorFv(param_1);
  return param_1;
}
