/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdBackGround   functions: 4
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdBackGround.md).
 */

/* JP: 0x00438450  CmdBackGround::CmdBackGround()   [__ct__13CmdBackGroundFv]  size=0x84 */
int __ct__13CmdBackGroundFv(int param_1)

{
  __ct__9MenuSceneFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__13CmdBackGround;
  *(undefined4 *)(param_1 + 0x58) = 0;
  __ct__10MenuWindowFv(param_1 + 0x5c);
  __ct__11MenuTextureFv(param_1 + 0x110);
  __ct__11SendOnLocalFv(param_1 + 0x150);
  __ct__10MenuSpriteFv(param_1 + 0x180);
  return param_1;
}

/* JP: 0x004384e0  CmdBackGround::~CmdBackGround()   [__dt__13CmdBackGroundFv]  size=0xc4 */
int __dt__13CmdBackGroundFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__13CmdBackGround;
    __dt__10MenuSpriteFv(param_1 + 0x180,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x150,0xffffffffffffffff);
    __dt__11MenuTextureFv(param_1 + 0x110,0xffffffffffffffff);
    __dt__10MenuWindowFv(param_1 + 0x5c,0xffffffffffffffff);
    __dt__9MenuSceneFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x004385b0  CmdBackGround::GetReady()   [GetReady__13CmdBackGroundFv]  size=0x16c */
undefined4 GetReady__13CmdBackGroundFv(int param_1)

{
  Create__11MenuTextureFPUc6GS_PSMUii(param_1 + 0x110,
                  *(undefined4 *)
                   ((uint)*(ushort *)(param_1 + 0x10a) * 0xc + *(int *)(param_1 + 0x54) + 0x10),0x30
                  ,0,0);
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(param_1 + 0x150,param_1 + 0x128,*(undefined4 *)(param_1 + 0x124),1,
                  0xffffffffffffffff);
  *(int *)(param_1 + 0x1dc) = param_1 + 0x150;
  *(byte *)(param_1 + 0x192) = *(byte *)(param_1 + 0x192) & 0xdf;
  SetData__9MenuSceneFUsP10MenuSprite(param_1,0,param_1 + 0x180);
  AddPlace__10MenuWindowFP9MenuPlace(param_1 + 0x5c,param_1 + 0x180);
  SetData__9MenuSceneFUsP10MenuWindow(param_1,0,param_1 + 0x5c);
  AddPriority__12MenuObjTableFP7MenuObj(*(int *)(param_1 + 0x58) + 0x2c,param_1 + 0x5c);
  return 1;
}

/* JP: 0x00438720  CmdBackGround::Release()   [Release__13CmdBackGroundFv]  size=0x68 */
void Release__13CmdBackGroundFv(int param_1)

{
  Release__9MenuSceneFv(param_1);
  Release__7MenuObjFv(param_1 + 0x5c);
  Release__11MenuTextureFv(param_1 + 0x110);
  Release__7MenuObjFv(param_1 + 0x150);
  Release__7MenuObjFv(param_1 + 0x180);
  return;
}
