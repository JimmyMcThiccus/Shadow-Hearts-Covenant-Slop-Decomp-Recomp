/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CScriptEx   functions: 1
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/_OverlayCopies_CScriptEx.md).
 */

/* JP: 0x004a2cf0  CScriptEx::~CScriptEx()   [__dt__9CScriptExFv]  size=0x74 */
int __dt__9CScriptExFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 0x14) = &__vt__9CScriptEx;
    __dt__7CPolObjFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}
