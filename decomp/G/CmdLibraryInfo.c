/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdLibraryInfo   functions: 6
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdLibraryInfo.md).
 */

/* JP: 0x0047b2e0  CmdLibraryInfo::CmdLibraryInfo()   [__ct__14CmdLibraryInfoFv]  size=0xcc */
int __ct__14CmdLibraryInfoFv(int param_1)

{
  __ct__9CmdWindowFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__14CmdLibraryInfo;
  *(undefined4 *)(param_1 + 0x18) = 0x408ce4;
  *(undefined4 *)(param_1 + 0x24) = 0x408cf0;
  __ct__11MenuTextureFv(param_1 + 0xb8);
  __ct__11SendOnLocalFv(param_1 + 0xf8);
  __ct__10MenuSpriteFv(param_1 + 0x128);
  __ct__8FontDrawFv(param_1 + 0x188);
  __ct__8FontDrawFv(param_1 + 0x1c8);
  __ct__8MenuTextFv(param_1 + 0x208);
  __ct__8MenuTextFv(param_1 + 0x288);
  return param_1;
}

/* JP: 0x0047b3b0  CmdLibraryInfo::~CmdLibraryInfo()   [__dt__14CmdLibraryInfoFv]  size=0x11c */
int __dt__14CmdLibraryInfoFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__14CmdLibraryInfo;
    *(undefined4 *)(param_1 + 0x18) = 0x408ce4;
    *(undefined4 *)(param_1 + 0x24) = 0x408cf0;
    __dt__8MenuTextFv(param_1 + 0x288,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1 + 0x208,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x1c8,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x188,0xffffffffffffffff);
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

/* JP: 0x0047b4d0  CmdLibraryInfo::CreateScene(CmdLibrary*, short)   [CreateScene__14CmdLibraryInfoFP10CmdLibrarys]  size=0x1c0 */
void CreateScene__14CmdLibraryInfoFP10CmdLibrarys(int param_1,int param_2,short param_3)

{
  SetData__9MenuSceneFUsP8FontDraw(param_2,0,param_1 + 0x188);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0x188);
  SetData__9MenuSceneFUsP8MenuText(param_2,0,param_1 + 0x288);
  AddPlace__10MenuWindowFP9MenuPlace(param_1,param_1 + 0x288);
  SetData__9MenuSceneFUsP10MenuSprite(param_2,param_3,param_1 + 0x128);
  *(int *)(param_1 + 0x184) = param_1 + 0xf8;
  *(byte *)(param_1 + 0x13a) = *(byte *)(param_1 + 0x13a) & 0xdf;
  if (param_3 == 0) {
    Create__11MenuTextureFPUc6GS_PSMUii(param_1 + 0xb8,*(undefined4 *)(*(int *)(param_2 + 0x54) + 0x1c),0x30,0,0);
    Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(param_1 + 0xf8,param_1 + 0xd0,*(undefined4 *)(param_1 + 0xcc),1,
                    0xffffffffffffffff);
    AddPlace__10MenuWindowFP9MenuPlace(param_1,param_1 + 0x128);
  }
  else {
    Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(param_1 + 0xf8,0x4218f0,uRam004218ec,1,0xffffffffffffffff);
  }
  SetData__9MenuSceneFUsP10MenuWindow(param_2,0,param_1);
  AddOT__7MenuObjFv(param_1);
  return;
}

/* JP: 0x0047b690  CmdLibraryInfo::UpdateScene(CmdLibrary*, short)   [UpdateScene__14CmdLibraryInfoFP10CmdLibrarys]  size=0x104 */
void UpdateScene__14CmdLibraryInfoFP10CmdLibrarys(int param_1,int param_2,short param_3)

{
  undefined1 auStack_34 [4];
  int iStack_30;
  int iStack_20;
  short sStack_10;
  
  *(byte *)(param_1 + 0x29a) = *(byte *)(param_1 + 0x29a) & 0xfe;
  if (param_3 != 0) {
    iStack_30 = param_1;
    iStack_20 = param_2;
    sStack_10 = param_3;
    ClearImage__8FontDrawFv(param_1 + 0x188);
    sprintf(auStack_34,*(undefined4 *)(*(int *)(iStack_20 + 0x24) + 0x148),sStack_10);
    SetMessage__8MenuTextFPcUiUcUc(iStack_30 + 0x288,auStack_34,*(byte *)(iStack_30 + 0x2e0) & 7,0,1);
    OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_30 + 0x188,iStack_30 + 0x288,
                    ((ulong)*(byte *)(iStack_30 + 0x2e0) & 0xf) >> 3,0);
    *(byte *)(iStack_30 + 0x29a) = *(byte *)(iStack_30 + 0x29a) & 0xfe | 1;
  }
  return;
}

/* JP: 0x0047b7a0  CmdLibraryInfo::~CmdLibraryInfo()   [@24@__dt__14CmdLibraryInfoFv]  size=0x8 */
undefined4 * _24___dt__14CmdLibraryInfoFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -6;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-4] = &__vt__14CmdLibraryInfo;
    *param_1 = 0x408ce4;
    param_1[3] = 0x408cf0;
    __dt__8MenuTextFv(param_1 + 0x9c,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1 + 0x7c,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x6c,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x5c,0xffffffffffffffff);
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

/* JP: 0x0047b7b0  CmdLibraryInfo::~CmdLibraryInfo()   [@36@__dt__14CmdLibraryInfoFv]  size=0x8 */
undefined4 * _36___dt__14CmdLibraryInfoFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -9;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-7] = &__vt__14CmdLibraryInfo;
    param_1[-3] = 0x408ce4;
    *param_1 = 0x408cf0;
    __dt__8MenuTextFv(param_1 + 0x99,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1 + 0x79,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x69,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x59,0xffffffffffffffff);
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
