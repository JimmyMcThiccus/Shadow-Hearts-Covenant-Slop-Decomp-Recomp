/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdGoodsPad   functions: 2
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdGoodsPad.md).
 */

/* JP: 0x00479f60  CmdGoodsPad::~CmdGoodsPad()   [__dt__11CmdGoodsPadFv]  size=0xac */
int __dt__11CmdGoodsPadFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    __destroy_arr(param_1 + 0x110,0x2661a0,0x60,3);
    __dt__10MenuSpriteFv(param_1 + 0xb0,0xffffffffffffffff);
    __dt__10MenuSpriteFv(param_1 + 0x50,0xffffffffffffffff);
    __dt__9MenuGroupFv(param_1,0xffffffffffffffff);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x0047a010  CmdGoodsPad::CmdGoodsPad()   [__ct__11CmdGoodsPadFv]  size=0x74 */
int __ct__11CmdGoodsPadFv(int param_1)

{
  __ct__9MenuGroupFv(param_1);
  __ct__10MenuSpriteFv(param_1 + 0x50);
  __ct__10MenuSpriteFv(param_1 + 0xb0);
  __construct_array(param_1 + 0x110,0x266140,0x2661a0,0x60,3);
  return param_1;
}
