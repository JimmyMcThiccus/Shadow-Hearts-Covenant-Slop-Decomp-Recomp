/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdCrestDetailData   functions: 2
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdCrestDetailData.md).
 */

/* JP: 0x004982c0  CmdCrestDetailData::~CmdCrestDetailData()   [__dt__18CmdCrestDetailDataFv]  size=0xd4 */
int __dt__18CmdCrestDetailDataFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    __dt__8MenuTextFv(param_1 + 0x550,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1 + 0x4d0,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1 + 0x450,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x410,0xffffffffffffffff);
    __destroy_arr(param_1 + 0x50,0x2661a0,0x60,10);
    __dt__9MenuGroupFv(param_1,0xffffffffffffffff);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x004983a0  CmdCrestDetailData::CmdCrestDetailData()   [__ct__18CmdCrestDetailDataFv]  size=0x94 */
int __ct__18CmdCrestDetailDataFv(int param_1)

{
  __ct__9MenuGroupFv(param_1);
  __construct_array(param_1 + 0x50,0x266140,0x2661a0,0x60,10);
  __ct__8FontDrawFv(param_1 + 0x410);
  __ct__8MenuTextFv(param_1 + 0x450);
  __ct__8MenuTextFv(param_1 + 0x4d0);
  __ct__8MenuTextFv(param_1 + 0x550);
  return param_1;
}
