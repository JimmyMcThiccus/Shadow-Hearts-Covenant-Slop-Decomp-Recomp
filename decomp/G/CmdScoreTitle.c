/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdScoreTitle   functions: 6
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdScoreTitle.md).
 */

/* JP: 0x00477d50  CmdScoreTitle::CmdScoreTitle()   [__ct__13CmdScoreTitleFv]  size=0x7c */
int __ct__13CmdScoreTitleFv(int param_1)

{
  __ct__9CmdWindowFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__13CmdScoreTitle;
  *(undefined4 *)(param_1 + 0x18) = 0x408b94;
  *(undefined4 *)(param_1 + 0x24) = 0x408ba0;
  __ct__8FontDrawFv(param_1 + 0xb4);
  __ct__8MenuTextFv(param_1 + 0xf4);
  return param_1;
}

/* JP: 0x00477dd0  CmdScoreTitle::~CmdScoreTitle()   [__dt__13CmdScoreTitleFv]  size=0xbc */
int __dt__13CmdScoreTitleFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__13CmdScoreTitle;
    *(undefined4 *)(param_1 + 0x18) = 0x408b94;
    *(undefined4 *)(param_1 + 0x24) = 0x408ba0;
    __dt__8MenuTextFv(param_1 + 0xf4,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0xb4,0xffffffffffffffff);
    __dt__9CmdWindowFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x00477e90  CmdScoreTitle::CreateScene(CmdScore*)   [CreateScene__13CmdScoreTitleFP8CmdScore]  size=0x9c */
void CreateScene__13CmdScoreTitleFP8CmdScore(int param_1,undefined4 param_2)

{
  SetData__9MenuSceneFUsP8FontDraw(param_2,0,param_1 + 0xb4);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0xb4);
  SetData__9MenuSceneFUsP8MenuText(param_2,0,param_1 + 0xf4);
  AddPlace__10MenuWindowFP9MenuPlace(param_1,param_1 + 0xf4);
  SetData__9MenuSceneFUsP10MenuWindow(param_2,0,param_1);
  AddOT__7MenuObjFv(param_1);
  return;
}

/* JP: 0x00477f30  CmdScoreTitle::UpdateScene(CmdScore*, char*)   [UpdateScene__13CmdScoreTitleFP8CmdScorePc]  size=0xf8 */
void UpdateScene__13CmdScoreTitleFP8CmdScorePc(int param_1,int param_2,undefined4 param_3)

{
  ClearImage__8FontDrawFv(param_1 + 0xb4);
  SetMessage__8MenuTextFPcUiUcUc(param_1 + 0xf4,param_3,*(byte *)(param_1 + 0x14c) & 7,0,1);
  OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(param_1 + 0xb4,param_1 + 0xf4,((ulong)*(byte *)(param_1 + 0x14c) & 0xf) >> 3,0);
  (**(code **)(*(int *)(param_1 + 0xfc) + 0x24))
            ((float)(int)*(short *)(*(int *)(param_2 + 0x44) + 0x14) -
             *(float *)(param_1 + 0x120) / 2.0,*(undefined4 *)(param_1 + 0x11c));
  return;
}

/* JP: 0x00478030  CmdScoreTitle::~CmdScoreTitle()   [@24@__dt__13CmdScoreTitleFv]  size=0x8 */
undefined4 * _24___dt__13CmdScoreTitleFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -6;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-4] = &__vt__13CmdScoreTitle;
    *param_1 = 0x408b94;
    param_1[3] = 0x408ba0;
    __dt__8MenuTextFv(param_1 + 0x37,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x27,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}

/* JP: 0x00478040  CmdScoreTitle::~CmdScoreTitle()   [@36@__dt__13CmdScoreTitleFv]  size=0x8 */
undefined4 * _36___dt__13CmdScoreTitleFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -9;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-7] = &__vt__13CmdScoreTitle;
    param_1[-3] = 0x408b94;
    *param_1 = 0x408ba0;
    __dt__8MenuTextFv(param_1 + 0x34,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x24,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}
