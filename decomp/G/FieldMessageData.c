/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: FieldMessageData   functions: 2
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/FieldMessageData.md).
 */

/* JP: 0x004a0bb0  FieldMessageData::FieldMessageData()   [__ct__16FieldMessageDataFv]  size=0xa0 */
undefined4 * __ct__16FieldMessageDataFv(undefined4 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = &__vt__17DelayDeleteObject;
  param_1[2] = &__vt__16FieldMessageData;
  __ct__10MenuWindowFv(param_1 + 4);
  __ct__8FontDrawFv(param_1 + 0x31);
  __ct__11MenuMessageFv(param_1 + 0x41);
  __ct__7KeyWaitFv(param_1 + 0x67);
  __ct__6CursorFv(param_1 + 0x9e);
  return param_1;
}

/* JP: 0x004a0c50  FieldMessageData::~FieldMessageData()   [__dt__16FieldMessageDataFv]  size=0x130 */
int __dt__16FieldMessageDataFv(int param_1,short param_2)

{
  int iVar1;
  
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__16FieldMessageData;
    if ((long)((ulong)*(byte *)(param_1 + 0x37d) << 0x3d) < 0) {
      iVar1 = *(int *)(param_1 + 0xc);
      if (iVar1 != 0) {
        (**(code **)(*(int *)(iVar1 + 0x10) + 8))(iVar1,1);
      }
    }
    __dt__6CursorFv(param_1 + 0x278,0xffffffffffffffff);
    __dt__7KeyWaitFv(param_1 + 0x19c,0xffffffffffffffff);
    __dt__11MenuMessageFv(param_1 + 0x104,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0xc4,0xffffffffffffffff);
    __dt__10MenuWindowFv(param_1 + 0x10,0xffffffffffffffff);
    if (param_1 != 0) {
      *(undefined1 **)(param_1 + 8) = &__vt__17DelayDeleteObject;
    }
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}
