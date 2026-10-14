/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdWolfBoutProfile   functions: 6
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdWolfBoutProfile.md).
 */

/* JP: 0x00485b20  CmdWolfBoutProfile::CmdWolfBoutProfile()   [__ct__18CmdWolfBoutProfileFv]  size=0x8c */
int __ct__18CmdWolfBoutProfileFv(int param_1)

{
  __ct__9CmdWindowFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__18CmdWolfBoutProfile;
  *(undefined4 *)(param_1 + 0x18) = 0x409004;
  *(undefined4 *)(param_1 + 0x24) = 0x409010;
  __ct__8FontDrawFv(param_1 + 0xb4);
  __ct__8MenuTextFv(param_1 + 0xf4);
  __ct__8MenuTextFv(param_1 + 0x174);
  return param_1;
}

/* JP: 0x00485bb0  CmdWolfBoutProfile::~CmdWolfBoutProfile()   [__dt__18CmdWolfBoutProfileFv]  size=0xcc */
int __dt__18CmdWolfBoutProfileFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__18CmdWolfBoutProfile;
    *(undefined4 *)(param_1 + 0x18) = 0x409004;
    *(undefined4 *)(param_1 + 0x24) = 0x409010;
    __dt__8MenuTextFv(param_1 + 0x174,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1 + 0xf4,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0xb4,0xffffffffffffffff);
    __dt__9CmdWindowFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x00485c80  CmdWolfBoutProfile::CreateScene(CmdWolfBout*)   [CreateScene__18CmdWolfBoutProfileFP11CmdWolfBout]  size=0xc8 */
void CreateScene__18CmdWolfBoutProfileFP11CmdWolfBout(int param_1,undefined4 param_2)

{
  SetData__9MenuSceneFUsP8FontDraw(param_2,0,param_1 + 0xb4);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0xb4);
  SetData__9MenuSceneFUsP8MenuText(param_2,0,param_1 + 0xf4);
  SetData__9MenuSceneFUsP8MenuText(param_2,1,param_1 + 0x174);
  AddPlace__10MenuWindowFP9MenuPlace(param_1,param_1 + 0xf4);
  AddPlace__10MenuWindowFP9MenuPlace(param_1,param_1 + 0x174);
  SetData__9MenuSceneFUsP10MenuWindow(param_2,2,param_1);
  AddOT__7MenuObjFv(param_1);
  return;
}

/* JP: 0x00485d50  CmdWolfBoutProfile::UpdateScene(CmdWolfBout*)   [UpdateScene__18CmdWolfBoutProfileFP11CmdWolfBout]  size=0x17c */
void UpdateScene__18CmdWolfBoutProfileFP11CmdWolfBout(int param_1,int param_2)

{
  int iVar1;
  undefined8 uVar2;
  
  iVar1 = (*(short *)(param_2 + 0x88) * 0xc + (int)*(short *)(param_2 + 0x88)) * 4 +
          *(int *)(param_2 + 0x8c);
  uVar2 = GetRegDat__9RegDatApiFiii(5,*(undefined2 *)(iVar1 + *(short *)(param_2 + 0x8a) * 2 + 0x3c),
                          0xffffffffffffffff);
  SetMessage__8MenuTextFPcUiUcUc(param_1 + 0xf4,uVar2,*(byte *)(param_1 + 0x14c) & 7,0,1);
  SetMessage__8MenuTextFPcUiUcUc(param_1 + 0x174,*(undefined4 *)(iVar1 + 0x18),*(byte *)(param_1 + 0x1cc) & 7,0,1);
  ClearImage__8FontDrawFv(param_1 + 0xb4);
  OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(param_1 + 0xb4,param_1 + 0xf4,((ulong)*(byte *)(param_1 + 0x14c) & 0xf) >> 3,0);
  OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(param_1 + 0xb4,param_1 + 0x174,((ulong)*(byte *)(param_1 + 0x1cc) & 0xf) >> 3,0);
  return;
}

/* JP: 0x00485ed0  CmdWolfBoutProfile::~CmdWolfBoutProfile()   [@24@__dt__18CmdWolfBoutProfileFv]  size=0x8 */
undefined4 * _24___dt__18CmdWolfBoutProfileFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -6;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-4] = &__vt__18CmdWolfBoutProfile;
    *param_1 = 0x409004;
    param_1[3] = 0x409010;
    __dt__8MenuTextFv(param_1 + 0x57,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1 + 0x37,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x27,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}

/* JP: 0x00485ee0  CmdWolfBoutProfile::~CmdWolfBoutProfile()   [@36@__dt__18CmdWolfBoutProfileFv]  size=0x8 */
undefined4 * _36___dt__18CmdWolfBoutProfileFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -9;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-7] = &__vt__18CmdWolfBoutProfile;
    param_1[-3] = 0x409004;
    *param_1 = 0x409010;
    __dt__8MenuTextFv(param_1 + 0x54,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1 + 0x34,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x24,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}
