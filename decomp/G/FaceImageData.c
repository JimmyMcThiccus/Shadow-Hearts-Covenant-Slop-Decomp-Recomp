/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: FaceImageData   functions: 2
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/FaceImageData.md).
 */

/* JP: 0x004a0250  FaceImageData::FaceImageData()   [__ct__13FaceImageDataFv]  size=0x80 */
undefined4 * __ct__13FaceImageDataFv(undefined4 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = &__vt__17DelayDeleteObject;
  param_1[2] = &__vt__13FaceImageData;
  __ct__10MenuWindowFv(param_1 + 6);
  __ct__11SendOnLocalFv(param_1 + 0x33);
  __ct__11MenuPolygonFv(param_1 + 0x3f);
  return param_1;
}

/* JP: 0x004a0340  FaceImageData::~FaceImageData()   [__dt__13FaceImageDataFv]  size=0x100 */
int __dt__13FaceImageDataFv(int param_1,short param_2)

{
  int iVar1;
  
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__13FaceImageData;
    if (*(short *)(param_1 + 0xe) != 0) {
      iVar1 = *(int *)(param_1 + 0x180);
      if (iVar1 != 0) {
        (**(code **)(*(int *)(iVar1 + 0x10) + 8))(iVar1,1);
      }
    }
    __dt__11MenuPolygonFv(param_1 + 0xfc,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0xcc,0xffffffffffffffff);
    __dt__10MenuWindowFv(param_1 + 0x18,0xffffffffffffffff);
    if (param_1 != 0) {
      *(undefined1 **)(param_1 + 8) = &__vt__17DelayDeleteObject;
    }
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}
