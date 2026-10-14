/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdTopPlayInfo   functions: 6
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdTopPlayInfo.md).
 */

/* JP: 0x00451460  CmdTopPlayInfo::CmdTopPlayInfo()   [__ct__14CmdTopPlayInfoFv]  size=0xcc */
int __ct__14CmdTopPlayInfoFv(int param_1)

{
  __ct__9CmdWindowFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__14CmdTopPlayInfo;
  *(undefined4 *)(param_1 + 0x18) = 0x408154;
  *(undefined4 *)(param_1 + 0x24) = 0x408160;
  __ct__11MenuTextureFv(param_1 + 0xb8);
  __ct__11SendOnLocalFv(param_1 + 0xf8);
  __ct__10MenuSpriteFv(param_1 + 0x128);
  __ct__14MenuFontItalicFv(param_1 + 0x188);
  __ct__10MenuSpriteFv(param_1 + 0x238);
  __ct__14MenuFontItalicFv(param_1 + 0x298);
  return param_1;
}

/* JP: 0x00451530  CmdTopPlayInfo::~CmdTopPlayInfo()   [__dt__14CmdTopPlayInfoFv]  size=0x134 */
int __dt__14CmdTopPlayInfoFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__14CmdTopPlayInfo;
    *(undefined4 *)(param_1 + 0x18) = 0x408154;
    *(undefined4 *)(param_1 + 0x24) = 0x408160;
    ReleaseImage__14MenuFontItalicFv();
    if (param_1 != -0x238) {
      __dt__14MenuFontItalicFv(param_1 + 0x298,0xffffffffffffffff);
      __dt__10MenuSpriteFv(param_1 + 0x238,0xffffffffffffffff);
    }
    if (param_1 != -0x128) {
      __dt__14MenuFontItalicFv(param_1 + 0x188,0xffffffffffffffff);
      __dt__10MenuSpriteFv(param_1 + 0x128,0xffffffffffffffff);
    }
    __dt__11SendOnLocalFv(param_1 + 0xf8,0xffffffffffffffff);
    __dt__11MenuTextureFv(param_1 + 0xb8,0xffffffffffffffff);
    __dt__9CmdWindowFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x00451670  CmdTopPlayInfo::CreateScene(CmdTop*)   [CreateScene__14CmdTopPlayInfoFP6CmdTop]  size=0x3b4 */
void CreateScene__14CmdTopPlayInfoFP6CmdTop(int param_1,int param_2)

{
  uint uVar1;
  
  SetImage__14MenuFontItalicFPUc(*(undefined4 *)(*(int *)(param_2 + 0x54) + 0x34));
  uVar1 = *(uint *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + (uint)*(byte *)(ourBtlSaveDat__10BtlSaveSec + 2) * 4 + 4);
  Create__11MenuTextureFPUc6GS_PSMUii(param_1 + 0xb8,*(undefined4 *)(*(int *)(param_2 + 0x54) + 0x28),0x30,0,0);
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(param_1 + 0xf8,param_1 + 0xd0,*(undefined4 *)(param_1 + 0xcc),1,0xffffffffffffffff
                 );
  SetData__9MenuSceneFUsP10MenuSprite(param_2,0,param_1 + 0x128);
  SetData__9MenuSceneFUsP14MenuFontItalic(param_2,0,param_1 + 0x188);
  if (uVar1 / 1000000 == 0) {
    if (uVar1 / 1000 == 0) {
      (**(code **)(*(int *)(param_1 + 400) + 0x68))
                (param_1 + 0x188,*(undefined4 *)(*(int *)(param_2 + 0x24) + 0x90),uVar1);
    }
    else {
      (**(code **)(*(int *)(param_1 + 400) + 0x68))
                (param_1 + 0x188,*(undefined4 *)(*(int *)(param_2 + 0x24) + 0x88),
                 (uVar1 / 1000) % 1000,(int)uVar1 % 1000);
    }
  }
  else {
    (**(code **)(*(int *)(param_1 + 400) + 0x68))
              (param_1 + 0x188,*(undefined4 *)(*(int *)(param_2 + 0x24) + 0x80),uVar1 / 1000000,
               (uVar1 / 1000) % 1000,(int)uVar1 % 1000);
  }
  SetData__9MenuSceneFUsP10MenuSprite(param_2,1,param_1 + 0x238);
  SetData__9MenuSceneFUsP14MenuFontItalic(param_2,1,param_1 + 0x298);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0xf8);
  AddPlace__10MenuWindowFP9MenuPlace(param_1,param_1 + 0x128);
  AddPlace__10MenuWindowFP9MenuPlace(param_1,param_1 + 0x188);
  AddPlace__10MenuWindowFP9MenuPlace(param_1,param_1 + 0x238);
  AddPlace__10MenuWindowFP9MenuPlace(param_1,param_1 + 0x298);
  SetData__9MenuSceneFUsP10MenuWindow(param_2,1,param_1);
  AddOT__7MenuObjFv(param_1);
  return;
}

/* JP: 0x00451a30  CmdTopPlayInfo::UpdateScene(CmdTop*)   [UpdateScene__14CmdTopPlayInfoFP6CmdTop]  size=0x16c */
void UpdateScene__14CmdTopPlayInfoFP6CmdTop(int param_1,int param_2)

{
  uint uVar1;
  
  uVar1 = *(uint *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0xc);
  (**(code **)(*(int *)(param_1 + 0x2a0) + 0x68))
            (param_1 + 0x298,
             *(undefined4 *)
              ((uint)*(ushort *)(param_1 + 0x2ba) * 8 + *(int *)(param_2 + 0x24) + 0x10),
             uVar1 / 3600000,(uVar1 / 60000) % 0x3c,(uVar1 / 1000) % 0x3c);
  return;
}

/* JP: 0x00451ba0  CmdTopPlayInfo::~CmdTopPlayInfo()   [@24@__dt__14CmdTopPlayInfoFv]  size=0x8 */
undefined4 * _24___dt__14CmdTopPlayInfoFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -6;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-4] = &__vt__14CmdTopPlayInfo;
    *param_1 = 0x408154;
    param_1[3] = 0x408160;
    ReleaseImage__14MenuFontItalicFv();
    if (puVar1 != (undefined4 *)0xfffffdc8) {
      __dt__14MenuFontItalicFv(param_1 + 0xa0,0xffffffffffffffff);
      __dt__10MenuSpriteFv(param_1 + 0x88,0xffffffffffffffff);
    }
    if (puVar1 != (undefined4 *)0xfffffed8) {
      __dt__14MenuFontItalicFv(param_1 + 0x5c,0xffffffffffffffff);
      __dt__10MenuSpriteFv(param_1 + 0x44,0xffffffffffffffff);
    }
    __dt__11SendOnLocalFv(param_1 + 0x38,0xffffffffffffffff);
    __dt__11MenuTextureFv(param_1 + 0x28,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}

/* JP: 0x00451bb0  CmdTopPlayInfo::~CmdTopPlayInfo()   [@36@__dt__14CmdTopPlayInfoFv]  size=0x8 */
undefined4 * _36___dt__14CmdTopPlayInfoFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -9;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-7] = &__vt__14CmdTopPlayInfo;
    param_1[-3] = 0x408154;
    *param_1 = 0x408160;
    ReleaseImage__14MenuFontItalicFv();
    if (puVar1 != (undefined4 *)0xfffffdc8) {
      __dt__14MenuFontItalicFv(param_1 + 0x9d,0xffffffffffffffff);
      __dt__10MenuSpriteFv(param_1 + 0x85,0xffffffffffffffff);
    }
    if (puVar1 != (undefined4 *)0xfffffed8) {
      __dt__14MenuFontItalicFv(param_1 + 0x59,0xffffffffffffffff);
      __dt__10MenuSpriteFv(param_1 + 0x41,0xffffffffffffffff);
    }
    __dt__11SendOnLocalFv(param_1 + 0x35,0xffffffffffffffff);
    __dt__11MenuTextureFv(param_1 + 0x25,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}
