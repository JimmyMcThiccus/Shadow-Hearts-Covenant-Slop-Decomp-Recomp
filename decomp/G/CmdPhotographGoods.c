/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdPhotographGoods   functions: 5
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdPhotographGoods.md).
 */

/* JP: 0x00456ae0  CmdPhotographGoods::CmdPhotographGoods()   [__ct__18CmdPhotographGoodsFv]  size=0x94 */
int __ct__18CmdPhotographGoodsFv(int param_1)

{
  __ct__9CmdWindowFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__18CmdPhotographGoods;
  *(undefined4 *)(param_1 + 0x18) = 0x4083d4;
  *(undefined4 *)(param_1 + 0x24) = 0x4083e0;
  __ct__8FontDrawFv(param_1 + 0xb4);
  __construct_array(param_1 + 0xf4,0x27bfd0,0x27c030,0x80,4);
  return param_1;
}

/* JP: 0x00456b80  CmdPhotographGoods::~CmdPhotographGoods()   [__dt__18CmdPhotographGoodsFv]  size=0xc4 */
int __dt__18CmdPhotographGoodsFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__18CmdPhotographGoods;
    *(undefined4 *)(param_1 + 0x18) = 0x4083d4;
    *(undefined4 *)(param_1 + 0x24) = 0x4083e0;
    __destroy_arr(param_1 + 0xf4,0x27c030,0x80,4);
    __dt__8FontDrawFv(param_1 + 0xb4,0xffffffffffffffff);
    __dt__9CmdWindowFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x00456c50  CmdPhotographGoods::CreateScene(CmdPhotograph*)   [CreateScene__18CmdPhotographGoodsFP13CmdPhotograph]  size=0x2bc */
void CreateScene__18CmdPhotographGoodsFP13CmdPhotograph(int param_1,int param_2)

{
  int iVar1;
  ushort uVar2;
  undefined1 auStack_70 [72];
  undefined4 uStack_28;
  undefined2 uStack_24;
  undefined2 uStack_22;
  int iStack_20;
  int iStack_10;
  
  iStack_20 = param_1;
  iStack_10 = param_2;
  GetLibraryMonster__8CmdPartyFPsPs
            (*(undefined4 *)(*(int *)(param_2 + 0x58) + 0x5c),&uStack_22,&uStack_24);
  SetData__9MenuSceneFUsP8FontDraw(iStack_10,0,iStack_20 + 0xb4);
  AddPriority__12MenuObjTableFP7MenuObj(iStack_20 + 0x18,iStack_20 + 0xb4);
  iVar1 = iStack_20 + 0xf4;
  uVar2 = 0;
  while( true ) {
    if (3 < (short)uVar2) break;
    SetData__9MenuSceneFUsP8MenuText(iStack_10,uVar2,iVar1);
    AddPlace__10MenuWindowFP9MenuPlace(iStack_20,iVar1);
    if ((short)uVar2 < 2) {
      uStack_28 = *(undefined4 *)((uint)uVar2 * 0xc + *(int *)(iStack_10 + 0x28) + 0x10);
      SetMessage__8MenuTextFPcUiUcUc(iVar1,uStack_28,*(byte *)(iVar1 + 0x58) & 7,0,1);
      OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_20 + 0xb4,iVar1,((ulong)*(byte *)(iVar1 + 0x58) & 0xf) >> 3,0);
    }
    uVar2 = uVar2 + 1;
    iVar1 = iVar1 + 0x80;
  }
  sprintf(auStack_70,*(undefined4 *)(*(int *)(iStack_10 + 0x28) + 0x14),uStack_22);
  SetMessage__8MenuTextFPcUiUcUc(iStack_20 + 500,auStack_70,*(byte *)(iStack_20 + 0x24c) & 7,0,1);
  OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_20 + 0xb4,iStack_20 + 500,((ulong)*(byte *)(iStack_20 + 0x24c) & 0xf) >> 3,
                  0);
  sprintf(auStack_70,*(undefined4 *)(*(int *)(iStack_10 + 0x28) + 0x20),uStack_24);
  SetMessage__8MenuTextFPcUiUcUc(iStack_20 + 0x274,auStack_70,*(byte *)(iStack_20 + 0x2cc) & 7,0,1);
  OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_20 + 0xb4,iStack_20 + 0x274,
                  ((ulong)*(byte *)(iStack_20 + 0x2cc) & 0xf) >> 3,0);
  SetData__9MenuSceneFUsP10MenuWindow(iStack_10,0,iStack_20);
  AddOT__7MenuObjFv(iStack_20);
  return;
}

/* JP: 0x00456f10  CmdPhotographGoods::~CmdPhotographGoods()   [@24@__dt__18CmdPhotographGoodsFv]  size=0x8 */
undefined4 * _24___dt__18CmdPhotographGoodsFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -6;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-4] = &__vt__18CmdPhotographGoods;
    *param_1 = 0x4083d4;
    param_1[3] = 0x4083e0;
    __destroy_arr(param_1 + 0x37,0x27c030,0x80,4);
    __dt__8FontDrawFv(param_1 + 0x27,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}

/* JP: 0x00456f20  CmdPhotographGoods::~CmdPhotographGoods()   [@36@__dt__18CmdPhotographGoodsFv]  size=0x8 */
undefined4 * _36___dt__18CmdPhotographGoodsFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -9;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-7] = &__vt__18CmdPhotographGoods;
    param_1[-3] = 0x4083d4;
    *param_1 = 0x4083e0;
    __destroy_arr(param_1 + 0x34,0x27c030,0x80,4);
    __dt__8FontDrawFv(param_1 + 0x24,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}
