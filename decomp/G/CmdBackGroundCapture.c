/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdBackGroundCapture   functions: 4
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdBackGroundCapture.md).
 */

/* JP: 0x00437e50  CmdBackGroundCapture::CmdBackGroundCapture(MenuCapture*)   [__ct__20CmdBackGroundCaptureFP11MenuCapture]  size=0xc4 */
int __ct__20CmdBackGroundCaptureFP11MenuCapture(int param_1,undefined4 param_2)

{
  __ct__13CmdBackGroundFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__20CmdBackGroundCapture;
  __ct__11MenuTextureFv(param_1 + 0x1e8);
  __ct__11SendOnLocalFv(param_1 + 0x228);
  __ct__11SendOnLocalFv(param_1 + 600);
  __construct_array(param_1 + 0x288,0x266140,0x2661a0,0x60,2);
  __ct__12MenuRegisterFv(param_1 + 0x348);
  __ct__12MenuRegisterFv(param_1 + 0x370);
  *(undefined4 *)(param_1 + 0x1e0) = param_2;
  return param_1;
}

/* JP: 0x00437f20  CmdBackGroundCapture::~CmdBackGroundCapture()   [__dt__20CmdBackGroundCaptureFv]  size=0xf4 */
int __dt__20CmdBackGroundCaptureFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__20CmdBackGroundCapture;
    __dt__12MenuRegisterFv(param_1 + 0x370,0xffffffffffffffff);
    __dt__12MenuRegisterFv(param_1 + 0x348,0xffffffffffffffff);
    __destroy_arr(param_1 + 0x288,0x2661a0,0x60,2);
    __dt__11SendOnLocalFv(param_1 + 600,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x228,0xffffffffffffffff);
    __dt__11MenuTextureFv(param_1 + 0x1e8,0xffffffffffffffff);
    __dt__13CmdBackGroundFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x00438020  CmdBackGroundCapture::GetReady()   [GetReady__20CmdBackGroundCaptureFv]  size=0x3ac */
undefined4 GetReady__20CmdBackGroundCaptureFv(int param_1)

{
  Create__11MenuTextureFPUc6GS_PSMUii(param_1 + 0x110,*(undefined4 *)(*(int *)(param_1 + 0x54) + 0x10),0x30,0,0);
  Create__11MenuTextureFPUc6GS_PSMUii(param_1 + 0x1e8,*(undefined4 *)(*(int *)(param_1 + 0x54) + 0x1c),0x30,0,0);
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(param_1 + 0x150,*(int *)(param_1 + 0x1e0) + 0x30,0,1,0xffffffffffffffff);
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(param_1 + 600,param_1 + 0x128,*(undefined4 *)(param_1 + 0x124),1,
                  0xffffffffffffffff);
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(param_1 + 0x228,param_1 + 0x200,*(undefined4 *)(param_1 + 0x1fc),1,
                  0xffffffffffffffff);
  *(int *)(param_1 + 0x1dc) = param_1 + 0x150;
  *(byte *)(param_1 + 0x192) = *(byte *)(param_1 + 0x192) & 0xdf;
  *(int *)(param_1 + 0x2e4) = param_1 + 0x228;
  *(byte *)(param_1 + 0x29a) = *(byte *)(param_1 + 0x29a) & 0xdf;
  *(int *)(param_1 + 0x344) = param_1 + 600;
  *(byte *)(param_1 + 0x2fa) = *(byte *)(param_1 + 0x2fa) & 0xdf;
  SetData__9MenuSceneFUsP10MenuSprite(param_1,0,param_1 + 0x180);
  SetData__9MenuSceneFUsP10MenuSprite(param_1,1,param_1 + 0x288);
  SetData__9MenuSceneFUsP10MenuSprite(param_1,2,param_1 + 0x2e8);
  SetData__9MenuSceneFUsP10MenuWindow(param_1,0,param_1 + 0x5c);
  CreatePacket__10MenuPacketFUs(param_1 + 0x388,4);
  SetRegister__12MenuRegisterFiUlUl(param_1 + 0x370,0,8,0);
  *(short *)(param_1 + 900) = *(short *)(param_1 + 0x2fc) + -1;
  CreatePacket__10MenuPacketFUs(param_1 + 0x360,4);
  SetRegister__12MenuRegisterFiUlUl(param_1 + 0x348,0,8,5);
  *(short *)(param_1 + 0x35c) = *(short *)(param_1 + 0x2fc) + 1;
  AddPlace__10MenuWindowFP9MenuPlace(param_1 + 0x5c,param_1 + 0x180);
  AddPlace__10MenuWindowFP9MenuPlace(param_1 + 0x5c,param_1 + 0x288);
  AddPlace__10MenuWindowFP9MenuPlace(param_1 + 0x5c,param_1 + 0x2e8);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x74,param_1 + 0x370);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x74,param_1 + 0x348);
  AddPriority__12MenuObjTableFP7MenuObj(*(int *)(param_1 + 0x58) + 0x2c,param_1 + 0x5c);
  return 1;
}

/* JP: 0x004383d0  CmdBackGroundCapture::Release()   [Release__20CmdBackGroundCaptureFv]  size=0x74 */
void Release__20CmdBackGroundCaptureFv(int param_1)

{
  RemoveObj__12MenuObjTableFP7MenuObj(*(int *)(param_1 + 0x58) + 0x2c,param_1 + 0x5c);
  Release__13CmdBackGroundFv(param_1);
  Release__7MenuObjFv(param_1 + 600);
  Release__7MenuObjFv(param_1 + 0x288);
  Release__7MenuObjFv(param_1 + 0x2e8);
  return;
}
