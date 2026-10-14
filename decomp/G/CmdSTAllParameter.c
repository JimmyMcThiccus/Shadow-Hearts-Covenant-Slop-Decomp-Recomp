/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdSTAllParameter   functions: 2
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdSTAllParameter.md).
 */

/* JP: 0x004430b0  CmdSTAllParameter::~CmdSTAllParameter()   [__dt__17CmdSTAllParameterFv]  size=0xe4 */
int __dt__17CmdSTAllParameterFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    __destroy_arr(param_1 + 0x250,0x2766d0,0x84,2);
    if (param_1 != -0xd0) {
      __dt__8MenuTextFv(param_1 + 0x1d0,0xffffffffffffffff);
      __dt__8MenuTextFv(param_1 + 0x150,0xffffffffffffffff);
      __dt__8MenuTextFv(param_1 + 0xd0,0xffffffffffffffff);
    }
    __dt__8MenuTextFv(param_1 + 0x50,0xffffffffffffffff);
    __dt__9MenuGroupFv(param_1,0xffffffffffffffff);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x00443970  CmdSTAllParameter::CmdSTAllParameter()   [__ct__17CmdSTAllParameterFv]  size=0x98 */
int __ct__17CmdSTAllParameterFv(int param_1)

{
  __ct__9MenuGroupFv(param_1);
  __ct__8MenuTextFv(param_1 + 0x50);
  __ct__8MenuTextFv(param_1 + 0xd0);
  __ct__8MenuTextFv(param_1 + 0x150);
  __ct__8MenuTextFv(param_1 + 0x1d0);
  __construct_array(param_1 + 0x250,0x276640,0x2766d0,0x84,2);
  return param_1;
}
