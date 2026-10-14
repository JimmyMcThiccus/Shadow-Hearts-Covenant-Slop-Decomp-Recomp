/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdTopMenu   functions: 6
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdTopMenu.md).
 */

/* JP: 0x00450e10  CmdTopMenu::CmdTopMenu()   [__ct__10CmdTopMenuFv]  size=0xa4 */
int __ct__10CmdTopMenuFv(int param_1)

{
  __ct__9CmdWindowFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__10CmdTopMenu;
  *(undefined4 *)(param_1 + 0x18) = 0x408114;
  *(undefined4 *)(param_1 + 0x24) = 0x408120;
  __ct__8FontDrawFv(param_1 + 0xb4);
  __construct_array(param_1 + 0xf4,0x27bfd0,0x27c030,0x80,9);
  __ct__8MenuTextFv(param_1 + 0x574);
  return param_1;
}

/* JP: 0x00450ec0  CmdTopMenu::~CmdTopMenu()   [__dt__10CmdTopMenuFv]  size=0xdc */
int __dt__10CmdTopMenuFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__10CmdTopMenu;
    *(undefined4 *)(param_1 + 0x18) = 0x408114;
    *(undefined4 *)(param_1 + 0x24) = 0x408120;
    __dt__8MenuTextFv(param_1 + 0x574,0xffffffffffffffff);
    __destroy_arr(param_1 + 0xf4,0x27c030,0x80,9);
    __dt__8FontDrawFv(param_1 + 0xb4,0xffffffffffffffff);
    __dt__9CmdWindowFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x00450fa0  CmdTopMenu::CreateScene(CmdTop*)   [CreateScene__10CmdTopMenuFP6CmdTop]  size=0x15c */
void CreateScene__10CmdTopMenuFP6CmdTop(int param_1,undefined4 param_2)

{
  ulong uVar1;
  int iVar2;
  short sVar3;
  float fVar4;
  undefined4 uStack_24;
  
  iVar2 = param_1 + 0xf4;
  uStack_24 = 0.0;
  for (sVar3 = 0; sVar3 < 9; sVar3 = sVar3 + 1) {
    SetData__9MenuSceneFUsP8MenuText(param_2,0,iVar2);
    *(undefined2 *)(iVar2 + 0x1c) = 0;
    *(short *)(iVar2 + 0x1e) = sVar3;
    (**(code **)(*(int *)(iVar2 + 8) + 0x24))(0,uStack_24);
    uVar1 = GetRealHeight__8FontItemCFv(iVar2);
    if ((long)uVar1 < 0) {
      fVar4 = (float)(uVar1 & 0xffffffff);
    }
    else {
      fVar4 = (float)(int)uVar1;
    }
    uStack_24 = uStack_24 + fVar4;
    iVar2 = iVar2 + 0x80;
  }
  SetData__9MenuSceneFUsP8MenuText(param_2,1,param_1 + 0x574);
  SetData__9MenuSceneFUsP8FontDraw(param_2,0,param_1 + 0xb4);
  SetData__9MenuSceneFUsP10MenuWindow(param_2,0,param_1);
  CreateScrollMark__10MenuWindowFUc(param_1,0xc);
  AddOT__7MenuObjFv(param_1);
  return;
}

/* JP: 0x00451100  CmdTopMenu::UpdateScene(CmdTop*, short)   [UpdateScene__10CmdTopMenuFP6CmdTops]  size=0x340 */
void UpdateScene__10CmdTopMenuFP6CmdTops(int param_1,int param_2,short param_3)

{
  ushort uVar1;
  uint uVar2;
  int iVar3;
  char *pcVar4;
  undefined1 auStack_48 [8];
  int iStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  short sStack_32;
  int iStack_30;
  int iStack_20;
  short sStack_10;
  
  uVar1 = param_3 * 0xc;
  sStack_32 = uVar1 + 0xc;
  iStack_40 = *(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x300;
  pcVar4 = (char *)(iStack_40 + (short)uVar1);
  iStack_30 = param_1;
  iStack_20 = param_2;
  sStack_10 = param_3;
  ClearPlace__10MenuWindowFv(param_1);
  ClearImage__8FontDrawFv(iStack_30 + 0xb4);
  iVar3 = iStack_30 + 0xf4;
  for (; (short)uVar1 < sStack_32; uVar1 = uVar1 + 1) {
    if (*pcVar4 != '\0') {
      uStack_38 = *(undefined4 *)((uint)uVar1 * 0xc + *(int *)(iStack_20 + 0x28) + 0x10);
      SetMessage__8MenuTextFPcUiUcUc(iVar3,uStack_38,*(byte *)(iVar3 + 0x58) & 7,0,1);
      OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_30 + 0xb4,iVar3,((ulong)*(byte *)(iVar3 + 0x58) & 0xf) >> 3,0);
      *(ushort *)(iVar3 + 0x16) = uVar1;
      *(ushort *)(iVar3 + 0x22) = uVar1;
      EnableFontItem__8FontItemFv(iVar3);
      if (*pcVar4 == '\x01') {
        DisableFontItem__8FontItemFv(iVar3);
      }
      AddPlace__10MenuWindowFP9MenuPlace(iStack_30,iVar3);
      iVar3 = iVar3 + 0x80;
    }
    pcVar4 = pcVar4 + 1;
  }
  sprintf(auStack_48,*(undefined4 *)(*(int *)(iStack_20 + 0x24) + 0xa0),
                  *(undefined4 *)
                   (((int)sStack_10 + 0x13U & 0xffff) * 8 + *(int *)(iStack_20 + 0x24) + 0x10));
  SetMessage__8MenuTextFPcUiUcUc(iStack_30 + 0x574,auStack_48,*(byte *)(iStack_30 + 0x5cc) & 7,0,1);
  OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_30 + 0xb4,iStack_30 + 0x574,
                  ((ulong)*(byte *)(iStack_30 + 0x5cc) & 0xf) >> 3,0);
  AddPlace__10MenuWindowFP9MenuPlace(iStack_30,iStack_30 + 0x574);
  uVar2 = (((int)sStack_10 ^ 1U) + 1) * 4 & 0xff;
  SetMark__10ScrollMarkFUc(*(undefined4 *)(iStack_30 + 0x44),uVar2);
  uStack_3c = *(undefined4 *)(iStack_30 + 0x44);
  SetArea__10ScrollMarkFUcffff(*(undefined4 *)(iStack_30 + 0x598),*(undefined4 *)(iStack_30 + 0x59c),
                  *(undefined4 *)(iStack_30 + 0x5a0),*(undefined4 *)(iStack_30 + 0x5a4),uStack_3c,
                  uVar2);
  AddPriority__12MenuObjTableFP7MenuObj(iStack_30 + 0x18,iStack_30 + 0xb4);
  *(short *)(iStack_30 + 0xae) = sStack_10;
  return;
}

/* JP: 0x00451440  CmdTopMenu::~CmdTopMenu()   [@24@__dt__10CmdTopMenuFv]  size=0x8 */
undefined4 * _24___dt__10CmdTopMenuFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -6;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-4] = &__vt__10CmdTopMenu;
    *param_1 = 0x408114;
    param_1[3] = 0x408120;
    __dt__8MenuTextFv(param_1 + 0x157,0xffffffffffffffff);
    __destroy_arr(param_1 + 0x37,0x27c030,0x80,9);
    __dt__8FontDrawFv(param_1 + 0x27,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}

/* JP: 0x00451450  CmdTopMenu::~CmdTopMenu()   [@36@__dt__10CmdTopMenuFv]  size=0x8 */
undefined4 * _36___dt__10CmdTopMenuFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -9;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-7] = &__vt__10CmdTopMenu;
    param_1[-3] = 0x408114;
    *param_1 = 0x408120;
    __dt__8MenuTextFv(param_1 + 0x154,0xffffffffffffffff);
    __destroy_arr(param_1 + 0x34,0x27c030,0x80,9);
    __dt__8FontDrawFv(param_1 + 0x24,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}
