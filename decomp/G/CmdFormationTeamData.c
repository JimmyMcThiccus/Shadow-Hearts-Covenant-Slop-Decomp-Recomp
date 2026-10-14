/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdFormationTeamData   functions: 2
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdFormationTeamData.md).
 */

/* JP: 0x00481000  CmdFormationTeamData::~CmdFormationTeamData()   [__dt__20CmdFormationTeamDataFv]  size=0xf4 */
int __dt__20CmdFormationTeamDataFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    __destroy_arr(param_1 + 0x490,0x2766d0,0x84,2);
    __destroy_arr(param_1 + 0x310,0x2661a0,0x60,4);
    __destroy_arr(param_1 + 400,0x2661a0,0x60,4);
    __destroy_arr(param_1 + 0xd0,0x277890,0x30,4);
    __dt__8MenuTextFv(param_1 + 0x50,0xffffffffffffffff);
    __dt__9MenuGroupFv(param_1,0xffffffffffffffff);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x00481b20  CmdFormationTeamData::CmdFormationTeamData()   [__ct__20CmdFormationTeamDataFv]  size=0xdc */
int __ct__20CmdFormationTeamDataFv(int param_1)

{
  __ct__9MenuGroupFv(param_1);
  __ct__8MenuTextFv(param_1 + 0x50);
  __construct_array(param_1 + 0xd0,0x277820,0x277890,0x30,4);
  __construct_array(param_1 + 400,0x266140,0x2661a0,0x60,4);
  __construct_array(param_1 + 0x310,0x266140,0x2661a0,0x60,4);
  __construct_array(param_1 + 0x490,0x276640,0x2766d0,0x84,2);
  return param_1;
}
