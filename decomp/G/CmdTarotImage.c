/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdTarotImage   functions: 6
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdTarotImage.md).
 */

/* JP: 0x00456390  CmdTarotImage::CmdTarotImage()   [__ct__13CmdTarotImageFv]  size=0x8c */
int __ct__13CmdTarotImageFv(int param_1)

{
  __ct__9CmdWindowFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__13CmdTarotImage;
  *(undefined4 *)(param_1 + 0x18) = 0x408354;
  *(undefined4 *)(param_1 + 0x24) = 0x408360;
  __ct__11MenuTextureFv(param_1 + 0xb8);
  __ct__11SendOnLocalFv(param_1 + 0xf8);
  __ct__10MenuSpriteFv(param_1 + 0x128);
  return param_1;
}

/* JP: 0x00456420  CmdTarotImage::~CmdTarotImage()   [__dt__13CmdTarotImageFv]  size=0xcc */
int __dt__13CmdTarotImageFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__13CmdTarotImage;
    *(undefined4 *)(param_1 + 0x18) = 0x408354;
    *(undefined4 *)(param_1 + 0x24) = 0x408360;
    __dt__10MenuSpriteFv(param_1 + 0x128,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0xf8,0xffffffffffffffff);
    __dt__11MenuTextureFv(param_1 + 0xb8,0xffffffffffffffff);
    __dt__9CmdWindowFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x004564f0  CmdTarotImage::CreateScene(CmdTarot*)   [CreateScene__13CmdTarotImageFP8CmdTarot]  size=0x9c */
void CreateScene__13CmdTarotImageFP8CmdTarot(int param_1,undefined4 param_2)

{
  SetData__9MenuSceneFUsP10MenuSprite(param_2,0,param_1 + 0x128);
  *(int *)(param_1 + 0x184) = param_1 + 0xf8;
  *(byte *)(param_1 + 0x13a) = *(byte *)(param_1 + 0x13a) & 0xdf;
  AddPlace__10MenuWindowFP9MenuPlace(param_1,param_1 + 0x128);
  SetData__9MenuSceneFUsP10MenuWindow(param_2,1,param_1);
  AddOT__7MenuObjFv(param_1);
  return;
}

/* JP: 0x00456590  CmdTarotImage::UpdateScene(CmdTarot*)   [UpdateScene__13CmdTarotImageFP8CmdTarot]  size=0x178 */
void UpdateScene__13CmdTarotImageFP8CmdTarot(int param_1,int param_2)

{
  undefined1 auStack_60 [64];
  int iStack_20;
  int iStack_10;
  
  if (-1 < (long)((ulong)*(byte *)(param_1 + 0xf2) << 0x3d)) {
    iStack_20 = param_1;
    iStack_10 = param_2;
    if (*(short *)(param_1 + 0xf0) < 0) {
      if ((*(byte *)(param_1 + 0x12) & 1) == 0) {
        Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(param_1 + 0xf8,param_1 + 0xd0,*(undefined4 *)(param_1 + 0xcc),1,
                        0xffffffffffffffff);
        UpdatePacket__11SendOnLocalFv(iStack_20 + 0xf8);
        Open__10MenuWindowFUci(iStack_20,*(byte *)(iStack_20 + 0xb0) & 7,
                        *(undefined4 *)(*(int *)(iStack_20 + 0x34) + 0x10));
      }
    }
    else {
      sprintf(auStack_60,*(undefined4 *)(*(int *)(param_2 + 0x24) + 0x10),
                      *(undefined2 *)(param_1 + 0xf0));
      OrderFile__11MenuTextureFPCc6GS_PSMUii(iStack_20 + 0xb8,auStack_60,0x30,0,0);
      *(undefined2 *)(iStack_20 + 0xf0) = 0xffff;
    }
  }
  return;
}

/* JP: 0x00456710  CmdTarotImage::~CmdTarotImage()   [@24@__dt__13CmdTarotImageFv]  size=0x8 */
undefined4 * _24___dt__13CmdTarotImageFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -6;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-4] = &__vt__13CmdTarotImage;
    *param_1 = 0x408354;
    param_1[3] = 0x408360;
    __dt__10MenuSpriteFv(param_1 + 0x44,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x38,0xffffffffffffffff);
    __dt__11MenuTextureFv(param_1 + 0x28,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}

/* JP: 0x00456720  CmdTarotImage::~CmdTarotImage()   [@36@__dt__13CmdTarotImageFv]  size=0x8 */
undefined4 * _36___dt__13CmdTarotImageFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -9;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-7] = &__vt__13CmdTarotImage;
    param_1[-3] = 0x408354;
    *param_1 = 0x408360;
    __dt__10MenuSpriteFv(param_1 + 0x41,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x35,0xffffffffffffffff);
    __dt__11MenuTextureFv(param_1 + 0x25,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}
