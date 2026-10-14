/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdFormationParameter   functions: 2
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdFormationParameter.md).
 */

/* JP: 0x0047f6b0  CmdFormationParameter::~CmdFormationParameter()   [__dt__21CmdFormationParameterFv]  size=0x164 */
int __dt__21CmdFormationParameterFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    __dt__10MenuSpriteFv(param_1 + 0x960,0xffffffffffffffff);
    __destroy_arr(param_1 + 0x750,0x2766d0,0x84,4);
    __destroy_arr(param_1 + 0x680,0x286200,0x68,2);
    __destroy_arr(param_1 + 0x5c0,0x2661a0,0x60,2);
    __destroy_arr(param_1 + 0x3b0,0x285270,0xb0,3);
    __destroy_arr(param_1 + 0x1a0,0x285270,0xb0,3);
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

/* JP: 0x004802f0  CmdFormationParameter::CmdFormationParameter()   [__ct__21CmdFormationParameterFv]  size=0x144 */
int __ct__21CmdFormationParameterFv(int param_1)

{
  __ct__9MenuGroupFv(param_1);
  __ct__11MenuTextureFv(param_1 + 0x50);
  __ct__11SendOnLocalFv(param_1 + 0x90);
  __ct__10MenuSpriteFv(param_1 + 0xc0);
  __ct__8MenuTextFv(param_1 + 0x120);
  __construct_array(param_1 + 0x1a0,0x285200,0x285270,0xb0,3);
  __construct_array(param_1 + 0x3b0,0x285200,0x285270,0xb0,3);
  __construct_array(param_1 + 0x5c0,0x266140,0x2661a0,0x60,2);
  __construct_array(param_1 + 0x680,0x2861a0,0x286200,0x68,2);
  __construct_array(param_1 + 0x750,0x276640,0x2766d0,0x84,4);
  __ct__10MenuSpriteFv(param_1 + 0x960);
  return param_1;
}
