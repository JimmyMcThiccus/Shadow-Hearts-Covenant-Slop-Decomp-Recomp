/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdPrivateMenu   functions: 6
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdPrivateMenu.md).
 */

/* JP: 0x0044ed20  CmdPrivateMenu::CmdPrivateMenu()   [__ct__14CmdPrivateMenuFv]  size=0x94 */
int __ct__14CmdPrivateMenuFv(int param_1)

{
  __ct__9CmdWindowFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__14CmdPrivateMenu;
  *(undefined4 *)(param_1 + 0x18) = 0x408014;
  *(undefined4 *)(param_1 + 0x24) = 0x408020;
  __ct__8FontDrawFv(param_1 + 0xb4);
  __construct_array(param_1 + 0xf4,0x27bfd0,0x27c030,0x80,5);
  return param_1;
}

/* JP: 0x0044edc0  CmdPrivateMenu::~CmdPrivateMenu()   [__dt__14CmdPrivateMenuFv]  size=0xc4 */
int __dt__14CmdPrivateMenuFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__14CmdPrivateMenu;
    *(undefined4 *)(param_1 + 0x18) = 0x408014;
    *(undefined4 *)(param_1 + 0x24) = 0x408020;
    __destroy_arr(param_1 + 0xf4,0x27c030,0x80,5);
    __dt__8FontDrawFv(param_1 + 0xb4,0xffffffffffffffff);
    __dt__9CmdWindowFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x0044ee90  CmdPrivateMenu::CreateScene(CmdPrivate*)   [CreateScene__14CmdPrivateMenuFP10CmdPrivate]  size=0xec */
void CreateScene__14CmdPrivateMenuFP10CmdPrivate(int param_1,undefined4 param_2)

{
  int iVar1;
  short sVar2;
  
  SetData__9MenuSceneFUsP8FontDraw(param_2,0,param_1 + 0xb4);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0xb4);
  iVar1 = param_1 + 0xf4;
  for (sVar2 = 0; sVar2 < 5; sVar2 = sVar2 + 1) {
    SetData__9MenuSceneFUsP8MenuText(param_2,0,iVar1);
    *(short *)(iVar1 + 0x16) = sVar2;
    *(undefined2 *)(iVar1 + 0x1c) = 0;
    *(short *)(iVar1 + 0x1e) = sVar2;
    AddPlace__10MenuWindowFP9MenuPlace(param_1,iVar1);
    iVar1 = iVar1 + 0x80;
  }
  SetData__9MenuSceneFUsP10MenuWindow(param_2,0,param_1);
  AddOT__7MenuObjFv(param_1);
  return;
}

/* JP: 0x0044ef80  CmdPrivateMenu::UpdateScene(CmdPrivate*)   [UpdateScene__14CmdPrivateMenuFP10CmdPrivate]  size=0x32c */
void UpdateScene__14CmdPrivateMenuFP10CmdPrivate(int param_1,int param_2)

{
  char cVar1;
  uint uVar2;
  char *pcVar3;
  float fStack_3c;
  
  ClearImage__8FontDrawFv(param_1 + 0xb4);
  pcVar3 = *(char **)(*(int *)(param_2 + 0x70) + 0x34);
  fStack_3c = 0.0;
  cVar1 = -2;
  for (uVar2 = param_1 + 0xf4; uVar2 < param_1 + 0x374U; uVar2 = uVar2 + 0x80) {
    if ((*pcVar3 == -1) || (cVar1 == *pcVar3)) {
      *(byte *)(uVar2 + 0x21) = *(byte *)(uVar2 + 0x21) & 0xfd;
      *(byte *)(uVar2 + 0x12) = *(byte *)(uVar2 + 0x12) & 0xfe;
    }
    else {
      *(short *)(uVar2 + 0x22) = (short)*pcVar3;
      *(byte *)(uVar2 + 0x12) = *(byte *)(uVar2 + 0x12) & 0xfe | 1;
      (**(code **)(*(int *)(uVar2 + 8) + 0x24))(0,fStack_3c);
      SetMessage__8MenuTextFPcUiUcUc(uVar2,*(undefined4 *)
                             ((uint)(ushort)(short)*pcVar3 * 0xc + *(int *)(param_2 + 0x28) + 0x10),
                      *(byte *)(uVar2 + 0x58) & 7,0,1);
      OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(param_1 + 0xb4,uVar2,((ulong)*(byte *)(uVar2 + 0x58) & 0xf) >> 3,0);
      EnableFontItem__8FontItemFv(uVar2);
      if (*(char *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + (int)(short)(*pcVar3 + 0x18) + 0x300) == '\x01') {
        DisableFontItem__8FontItemFv(uVar2);
      }
      fStack_3c = fStack_3c + *(float *)(uVar2 + 0x30);
    }
    cVar1 = *pcVar3;
    pcVar3 = pcVar3 + 1;
  }
  return;
}

/* JP: 0x0044f2b0  CmdPrivateMenu::~CmdPrivateMenu()   [@24@__dt__14CmdPrivateMenuFv]  size=0x8 */
undefined4 * _24___dt__14CmdPrivateMenuFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -6;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-4] = &__vt__14CmdPrivateMenu;
    *param_1 = 0x408014;
    param_1[3] = 0x408020;
    __destroy_arr(param_1 + 0x37,0x27c030,0x80,5);
    __dt__8FontDrawFv(param_1 + 0x27,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}

/* JP: 0x0044f2c0  CmdPrivateMenu::~CmdPrivateMenu()   [@36@__dt__14CmdPrivateMenuFv]  size=0x8 */
undefined4 * _36___dt__14CmdPrivateMenuFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -9;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-7] = &__vt__14CmdPrivateMenu;
    param_1[-3] = 0x408014;
    *param_1 = 0x408020;
    __destroy_arr(param_1 + 0x34,0x27c030,0x80,5);
    __dt__8FontDrawFv(param_1 + 0x24,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}
