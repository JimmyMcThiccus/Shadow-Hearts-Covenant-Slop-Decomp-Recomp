/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdGoodsCrestData   functions: 2
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdGoodsCrestData.md).
 */

/* JP: 0x00495300  CmdGoodsCrestData::~CmdGoodsCrestData()   [__dt__17CmdGoodsCrestDataFv]  size=0x12c */
int __dt__17CmdGoodsCrestDataFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    __dt__7MenuBarFv(param_1 + 0x5f4,0xffffffffffffffff);
    __dt__10MenuSpriteFv(param_1 + 0x594,0xffffffffffffffff);
    __dt__10MenuSpriteFv(param_1 + 0x534,0xffffffffffffffff);
    __destroy_arr(param_1 + 0x414,0x2661a0,0x60,3);
    __destroy_arr(param_1 + 0x234,0x2661a0,0x60,5);
    __dt__10MenuSpriteFv(param_1 + 0x1d4,0xffffffffffffffff);
    __dt__11MenuPolygonFv(param_1 + 0x150,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1 + 0xd0,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1 + 0x50,0xffffffffffffffff);
    __dt__9MenuGroupFv(param_1,0xffffffffffffffff);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x004958c0  CmdGoodsCrestData::CmdGoodsCrestData()   [__ct__17CmdGoodsCrestDataFv]  size=0xec */
int __ct__17CmdGoodsCrestDataFv(int param_1)

{
  __ct__9MenuGroupFv(param_1);
  __ct__8MenuTextFv(param_1 + 0x50);
  __ct__8MenuTextFv(param_1 + 0xd0);
  __ct__11MenuPolygonFv(param_1 + 0x150);
  __ct__10MenuSpriteFv(param_1 + 0x1d4);
  __construct_array(param_1 + 0x234,0x266140,0x2661a0,0x60,5);
  __construct_array(param_1 + 0x414,0x266140,0x2661a0,0x60,3);
  __ct__10MenuSpriteFv(param_1 + 0x534);
  __ct__10MenuSpriteFv(param_1 + 0x594);
  __ct__7MenuBarFv(param_1 + 0x5f4);
  return param_1;
}
