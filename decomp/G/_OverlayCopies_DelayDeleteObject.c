/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: DelayDeleteObject   functions: 2
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/_OverlayCopies_DelayDeleteObject.md).
 */

/* JP: 0x004a02d0  DelayDeleteObject::~DelayDeleteObject()   [__dt__17DelayDeleteObjectFv]  size=0x64 */
int __dt__17DelayDeleteObjectFv(int param_1,short param_2)

{
  if ((param_1 != 0) && (*(undefined1 **)(param_1 + 8) = &__vt__17DelayDeleteObject, 0 < param_2)) {
    __dl__FPv(param_1);
  }
  return param_1;
}

/* JP: 0x004c07d0  DelayDeleteObject::DelayDeleteObject()   [__ct__17DelayDeleteObjectFv]  size=0x3c */
int __ct__17DelayDeleteObjectFv(int param_1)

{
  __ct__5CListFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__17DelayDeleteObject;
  return param_1;
}
