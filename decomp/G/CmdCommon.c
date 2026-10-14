/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdCommon   functions: 4
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdCommon.md).
 */

/* JP: 0x00437740  CmdCommon::CmdCommon()   [__ct__9CmdCommonFv]  size=0x5c */
int __ct__9CmdCommonFv(int param_1)

{
  __ct__9MenuSceneFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__9CmdCommon;
  __ct__6CursorFv(param_1 + 0x58);
  __ct__11MenuTextureFv(param_1 + 0x158);
  return param_1;
}

/* JP: 0x004377a0  CmdCommon::~CmdCommon()   [__dt__9CmdCommonFv]  size=0xac */
int __dt__9CmdCommonFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__9CmdCommon;
    (**(code **)(*(int *)(param_1 + 8) + 0x18))();
    __dt__11MenuTextureFv(param_1 + 0x158,0xffffffffffffffff);
    __dt__6CursorFv(param_1 + 0x58,0xffffffffffffffff);
    __dt__9MenuSceneFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x00437850  CmdCommon::GetReady()   [GetReady__9CmdCommonFv]  size=0xb0 */
undefined4 GetReady__9CmdCommonFv(int param_1)

{
  Create__11MenuTextureFPUc6GS_PSMUii(param_1 + 0x158,*(undefined4 *)(*(int *)(param_1 + 0x54) + 0x10),0x30,0,0);
  SetData__9MenuSceneFUsP6Cursor(param_1,0,param_1 + 0x58);
  *(byte *)(param_1 + 0x153) = *(byte *)(param_1 + 0x153) & 0xef | 0x10;
  *(byte *)(param_1 + 0x6a) = *(byte *)(param_1 + 0x6a) & 0xfe;
  return 1;
}

/* JP: 0x00437900  CmdCommon::Release()   [Release__9CmdCommonFv]  size=0x68 */
void Release__9CmdCommonFv(int param_1)

{
  if (*(int *)(param_1 + 0xc) != 0) {
    __dt__9BufMemoryFv(*(undefined4 *)(param_1 + 0xc),1);
    *(undefined4 *)(param_1 + 0xc) = 0;
  }
  Release__11MenuTextureFv(param_1 + 0x158);
  Release__7MenuObjFv(param_1 + 0x58);
  return;
}
