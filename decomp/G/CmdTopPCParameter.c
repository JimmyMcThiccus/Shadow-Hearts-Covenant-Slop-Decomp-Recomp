/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdTopPCParameter   functions: 2
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdTopPCParameter.md).
 */

/* JP: 0x00451d30  CmdTopPCParameter::~CmdTopPCParameter()   [__dt__17CmdTopPCParameterFv]  size=0x264 */
int __dt__17CmdTopPCParameterFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    __destroy_arr(param_1 + 0xad8,0x2766d0,0x84,5);
    if (param_1 != -0x8b0) {
      __dt__7MenuBarFv(param_1 + 0xa70,0xffffffffffffffff);
      __dt__10MenuSpriteFv(param_1 + 0xa10,0xffffffffffffffff);
      __dt__8MenuFontFv(param_1 + 0x960,0xffffffffffffffff);
      __dt__8MenuFontFv(param_1 + 0x8b0,0xffffffffffffffff);
    }
    if (param_1 != -0x688) {
      __dt__7MenuBarFv(param_1 + 0x848,0xffffffffffffffff);
      __dt__10MenuSpriteFv(param_1 + 0x7e8,0xffffffffffffffff);
      __dt__8MenuFontFv(param_1 + 0x738,0xffffffffffffffff);
      __dt__8MenuFontFv(param_1 + 0x688,0xffffffffffffffff);
    }
    if (param_1 != -0x460) {
      __dt__7MenuBarFv(param_1 + 0x620,0xffffffffffffffff);
      __dt__10MenuSpriteFv(param_1 + 0x5c0,0xffffffffffffffff);
      __dt__8MenuFontFv(param_1 + 0x510,0xffffffffffffffff);
      __dt__8MenuFontFv(param_1 + 0x460,0xffffffffffffffff);
    }
    if (param_1 != -0x300) {
      __dt__8MenuFontFv(param_1 + 0x3b0,0xffffffffffffffff);
      __dt__8MenuFontFv(param_1 + 0x300,0xffffffffffffffff);
    }
    if (param_1 != -0x1a0) {
      __dt__8MenuFontFv(param_1 + 0x250,0xffffffffffffffff);
      __dt__8MenuFontFv(param_1 + 0x1a0,0xffffffffffffffff);
    }
    __dt__8MenuTextFv(param_1 + 0x120,0xffffffffffffffff);
    __dt__10MenuSpriteFv(param_1 + 0xc0,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x90,0xffffffffffffffff);
    __dt__11MenuTextureFv(param_1 + 0x50,0xffffffffffffffff);
    __dt__9MenuGroupFv(param_1,0xffffffffffffffff);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x00451fa0  CmdTopPCParameter::CmdTopPCParameter()   [__ct__17CmdTopPCParameterFv]  size=0x1a4 */
int __ct__17CmdTopPCParameterFv(int param_1)

{
  __ct__9MenuGroupFv(param_1);
  __ct__11MenuTextureFv(param_1 + 0x50);
  __ct__11SendOnLocalFv(param_1 + 0x90);
  __ct__10MenuSpriteFv(param_1 + 0xc0);
  __ct__8MenuTextFv(param_1 + 0x120);
  __ct__8MenuFontFv(param_1 + 0x1a0);
  __ct__8MenuFontFv(param_1 + 0x250);
  __ct__8MenuFontFv(param_1 + 0x300);
  __ct__8MenuFontFv(param_1 + 0x3b0);
  __ct__8MenuFontFv(param_1 + 0x460);
  __ct__8MenuFontFv(param_1 + 0x510);
  __ct__10MenuSpriteFv(param_1 + 0x5c0);
  __ct__7MenuBarFv(param_1 + 0x620);
  __ct__8MenuFontFv(param_1 + 0x688);
  __ct__8MenuFontFv(param_1 + 0x738);
  __ct__10MenuSpriteFv(param_1 + 0x7e8);
  __ct__7MenuBarFv(param_1 + 0x848);
  __ct__8MenuFontFv(param_1 + 0x8b0);
  __ct__8MenuFontFv(param_1 + 0x960);
  __ct__10MenuSpriteFv(param_1 + 0xa10);
  __ct__7MenuBarFv(param_1 + 0xa70);
  __construct_array(param_1 + 0xad8,0x276640,0x2766d0,0x84,5);
  return param_1;
}
