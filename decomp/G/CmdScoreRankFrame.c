/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdScoreRankFrame   functions: 5
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdScoreRankFrame.md).
 */

/* JP: 0x00477970  CmdScoreRankFrame::CmdScoreRankFrame()   [__ct__17CmdScoreRankFrameFv]  size=0xac */
int __ct__17CmdScoreRankFrameFv(int param_1)

{
  __ct__9CmdWindowFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__17CmdScoreRankFrame;
  *(undefined4 *)(param_1 + 0x18) = 0x408b54;
  *(undefined4 *)(param_1 + 0x24) = 0x408b60;
  __ct__11MenuTextureFv(param_1 + 0xb8);
  __ct__11SendOnLocalFv(param_1 + 0xf8);
  __ct__10MenuSpriteFv(param_1 + 0x128);
  __ct__8MenuTextFv(param_1 + 0x188);
  __ct__8FontDrawFv(param_1 + 0x208);
  return param_1;
}

/* JP: 0x00477a20  CmdScoreRankFrame::~CmdScoreRankFrame()   [__dt__17CmdScoreRankFrameFv]  size=0xf4 */
int __dt__17CmdScoreRankFrameFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__17CmdScoreRankFrame;
    *(undefined4 *)(param_1 + 0x18) = 0x408b54;
    *(undefined4 *)(param_1 + 0x24) = 0x408b60;
    __dt__8FontDrawFv(param_1 + 0x208,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1 + 0x188,0xffffffffffffffff);
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

/* JP: 0x00477b20  CmdScoreRankFrame::CreateScene(CmdScore*)   [CreateScene__17CmdScoreRankFrameFP8CmdScore]  size=0x20c */
void CreateScene__17CmdScoreRankFrameFP8CmdScore(int param_1,int param_2)

{
  SetData__9MenuSceneFUsP8FontDraw(param_2,3,param_1 + 0x208);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0x208);
  SetData__9MenuSceneFUsP8MenuText(param_2,10,param_1 + 0x188);
  SetMessage__8MenuTextFPcUiUcUc(param_1 + 0x188,*(undefined4 *)(*(int *)(param_2 + 0x28) + 0x130),
                  *(byte *)(param_1 + 0x1e0) & 7,0,1);
  OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(param_1 + 0x208,param_1 + 0x188,((ulong)*(byte *)(param_1 + 0x1e0) & 0xf) >> 3,0);
  AddPlace__10MenuWindowFP9MenuPlace(param_1,param_1 + 0x188);
  SetData__9MenuSceneFUsP10MenuSprite(param_2,0,param_1 + 0x128);
  AddPlace__10MenuWindowFP9MenuPlace(param_1,param_1 + 0x128);
  Create__11MenuTextureFPUc6GS_PSMUii(param_1 + 0xb8,*(undefined4 *)(*(int *)(param_2 + 0x54) + 0x1c),0x30,0,0);
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(param_1 + 0xf8,param_1 + 0xd0,*(undefined4 *)(param_1 + 0xcc),1,0xffffffffffffffff
                 );
  *(short *)(param_1 + 0x10c) = *(short *)(param_1 + 0x13c) + -1;
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0xf8);
  SetData__9MenuSceneFUsP10MenuWindow(param_2,4,param_1);
  AddOT__7MenuObjFv(param_1);
  return;
}

/* JP: 0x00477d30  CmdScoreRankFrame::~CmdScoreRankFrame()   [@24@__dt__17CmdScoreRankFrameFv]  size=0x8 */
undefined4 * _24___dt__17CmdScoreRankFrameFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -6;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-4] = &__vt__17CmdScoreRankFrame;
    *param_1 = 0x408b54;
    param_1[3] = 0x408b60;
    __dt__8FontDrawFv(param_1 + 0x7c,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1 + 0x5c,0xffffffffffffffff);
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

/* JP: 0x00477d40  CmdScoreRankFrame::~CmdScoreRankFrame()   [@36@__dt__17CmdScoreRankFrameFv]  size=0x8 */
undefined4 * _36___dt__17CmdScoreRankFrameFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -9;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-7] = &__vt__17CmdScoreRankFrame;
    param_1[-3] = 0x408b54;
    *param_1 = 0x408b60;
    __dt__8FontDrawFv(param_1 + 0x79,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1 + 0x59,0xffffffffffffffff);
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
