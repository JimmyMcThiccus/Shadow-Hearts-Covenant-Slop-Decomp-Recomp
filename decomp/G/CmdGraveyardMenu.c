/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdGraveyardMenu   functions: 5
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdGraveyardMenu.md).
 */

/* JP: 0x0045f060  CmdGraveyardMenu::CmdGraveyardMenu()   [__ct__16CmdGraveyardMenuFv]  size=0xa4 */
int __ct__16CmdGraveyardMenuFv(int param_1)

{
  __ct__9CmdWindowFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__16CmdGraveyardMenu;
  *(undefined4 *)(param_1 + 0x18) = 0x4086b4;
  *(undefined4 *)(param_1 + 0x24) = 0x4086c0;
  __ct__8FontDrawFv(param_1 + 0xb4);
  __ct__8MenuTextFv(param_1 + 0xf4);
  __construct_array(param_1 + 0x174,0x27bfd0,0x27c030,0x80,2);
  return param_1;
}

/* JP: 0x0045f110  CmdGraveyardMenu::~CmdGraveyardMenu()   [__dt__16CmdGraveyardMenuFv]  size=0xdc */
int __dt__16CmdGraveyardMenuFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__16CmdGraveyardMenu;
    *(undefined4 *)(param_1 + 0x18) = 0x4086b4;
    *(undefined4 *)(param_1 + 0x24) = 0x4086c0;
    __destroy_arr(param_1 + 0x174,0x27c030,0x80,2);
    __dt__8MenuTextFv(param_1 + 0xf4,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0xb4,0xffffffffffffffff);
    __dt__9CmdWindowFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x0045f1f0  CmdGraveyardMenu::CreateScene(CmdGraveyard*)   [CreateScene__16CmdGraveyardMenuFP12CmdGraveyard]  size=0x2d0 */
void CreateScene__16CmdGraveyardMenuFP12CmdGraveyard(int param_1,int param_2)

{
  ulong uVar1;
  int iVar2;
  int iVar3;
  float fVar4;
  undefined4 uStack_24;
  
  SetData__9MenuSceneFUsP8FontDraw(param_2,0,param_1 + 0xb4);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0xb4);
  SetData__9MenuSceneFUsP8MenuText(param_2,0,param_1 + 0xf4);
  SetMessage__8MenuTextFPcUiUcUc(param_1 + 0xf4,*(undefined4 *)(*(int *)(param_2 + 0x28) + 0x10),
                  *(byte *)(param_1 + 0x14c) & 7,0,1);
  OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(param_1 + 0xb4,param_1 + 0xf4,((ulong)*(byte *)(param_1 + 0x14c) & 0xf) >> 3,0);
  AddPlace__10MenuWindowFP9MenuPlace(param_1,param_1 + 0xf4);
  uStack_24 = 0.0;
  iVar2 = param_1 + 0x174;
  for (iVar3 = 0; iVar3 < 2; iVar3 = iVar3 + 1) {
    SetData__9MenuSceneFUsP8MenuText(param_2,1,iVar2);
    *(short *)(iVar2 + 0x16) = (short)iVar3;
    *(undefined2 *)(iVar2 + 0x1c) = 0;
    *(short *)(iVar2 + 0x1e) = (short)iVar3;
    (**(code **)(*(int *)(iVar2 + 8) + 0x24))
              (*(undefined4 *)(iVar2 + 0x24),uStack_24 + *(float *)(iVar2 + 0x28));
    SetMessage__8MenuTextFPcUiUcUc(iVar2,*(undefined4 *)
                           ((iVar3 + *(short *)(iVar2 + 0x22) & 0xffffU) * 0xc +
                            *(int *)(param_2 + 0x28) + 0x10),*(byte *)(iVar2 + 0x58) & 7,0,1);
    OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(param_1 + 0xb4,iVar2,((ulong)*(byte *)(iVar2 + 0x58) & 0xf) >> 3,0);
    AddPlace__10MenuWindowFP9MenuPlace(param_1,iVar2);
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
  SetData__9MenuSceneFUsP10MenuWindow(param_2,0,param_1);
  AddOT__7MenuObjFv(param_1);
  return;
}

/* JP: 0x0045f4c0  CmdGraveyardMenu::~CmdGraveyardMenu()   [@24@__dt__16CmdGraveyardMenuFv]  size=0x8 */
undefined4 * _24___dt__16CmdGraveyardMenuFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -6;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-4] = &__vt__16CmdGraveyardMenu;
    *param_1 = 0x4086b4;
    param_1[3] = 0x4086c0;
    __destroy_arr(param_1 + 0x57,0x27c030,0x80,2);
    __dt__8MenuTextFv(param_1 + 0x37,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x27,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}

/* JP: 0x0045f4d0  CmdGraveyardMenu::~CmdGraveyardMenu()   [@36@__dt__16CmdGraveyardMenuFv]  size=0x8 */
undefined4 * _36___dt__16CmdGraveyardMenuFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -9;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-7] = &__vt__16CmdGraveyardMenu;
    param_1[-3] = 0x4086b4;
    *param_1 = 0x4086c0;
    __destroy_arr(param_1 + 0x54,0x27c030,0x80,2);
    __dt__8MenuTextFv(param_1 + 0x34,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x24,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}
