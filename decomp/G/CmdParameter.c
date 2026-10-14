/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdParameter   functions: 2
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdParameter.md).
 */

/* JP: 0x0044abc0  CmdParameter::~CmdParameter()   [__dt__12CmdParameterFv]  size=0x74 */
int __dt__12CmdParameterFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    __dt__8MenuTextFv(param_1 + 0x80,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1,0xffffffffffffffff);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x0044ac40  CmdParameter::CmdParameter()   [__ct__12CmdParameterFv]  size=0x3c */
int __ct__12CmdParameterFv(int param_1)

{
  __ct__8MenuTextFv(param_1);
  __ct__8MenuTextFv(param_1 + 0x80);
  return param_1;
}
