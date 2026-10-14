/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdKeyCustomMenu   functions: 5
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdKeyCustomMenu.md).
 */

/* JP: 0x0047a720  CmdKeyCustomMenu::CmdKeyCustomMenu()   [__ct__16CmdKeyCustomMenuFv]  size=0xcc */
int __ct__16CmdKeyCustomMenuFv(int param_1)

{
  __ct__9CmdWindowFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__16CmdKeyCustomMenu;
  *(undefined4 *)(param_1 + 0x18) = 0x408c74;
  *(undefined4 *)(param_1 + 0x24) = 0x408c80;
  __ct__8FontDrawFv(param_1 + 0xb4);
  __ct__11SendOnLocalFv(param_1 + 0xf4);
  __construct_array(param_1 + 0x124,0x47a880,0x47a7f0,0x130,4);
  __construct_array(param_1 + 0x5e4,0x27bfd0,0x27c030,0x80,2);
  return param_1;
}

/* JP: 0x0047a8d0  CmdKeyCustomMenu::~CmdKeyCustomMenu()   [__dt__16CmdKeyCustomMenuFv]  size=0xfc */
int __dt__16CmdKeyCustomMenuFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__16CmdKeyCustomMenu;
    *(undefined4 *)(param_1 + 0x18) = 0x408c74;
    *(undefined4 *)(param_1 + 0x24) = 0x408c80;
    __destroy_arr(param_1 + 0x5e4,0x27c030,0x80,2);
    __destroy_arr(param_1 + 0x124,0x47a7f0,0x130,4);
    __dt__11SendOnLocalFv(param_1 + 0xf4,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0xb4,0xffffffffffffffff);
    __dt__9CmdWindowFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x0047a9d0  CmdKeyCustomMenu::CreateScene(CmdKeyCustom*)   [CreateScene__16CmdKeyCustomMenuFP12CmdKeyCustom]  size=0x310 */
void CreateScene__16CmdKeyCustomMenuFP12CmdKeyCustom(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  
  SetData__9MenuSceneFUsP8FontDraw(param_2,0,param_1 + 0xb4);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0xb4);
  iVar1 = param_1 + 0x124;
  uVar2 = 4;
  while( true ) {
    if (7 < (int)uVar2) break;
    SetData__9MenuSceneFUsP10MenuSprite(param_2,6,iVar1 + 0x50);
    AddPlace__9MenuGroupFP9MenuPlace(iVar1,iVar1 + 0x50);
    SetData__9MenuSceneFUsP8MenuText(param_2,4,iVar1 + 0xb0);
    SetMessage__8MenuTextFPcUiUcUc(iVar1 + 0xb0,*(undefined4 *)(*(int *)(param_2 + 0x28) + 0x58),
                    *(byte *)(iVar1 + 0x108) & 7,0,1);
    OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(param_1 + 0xb4,iVar1 + 0xb0,((ulong)*(byte *)(iVar1 + 0x108) & 0xf) >> 3,0);
    AddPlace__9MenuGroupFP9MenuPlace(iVar1,iVar1 + 0xb0);
    SetData__9MenuSceneFUsP9MenuGroup(param_2,uVar2 & 0xffff,iVar1);
    AddPlace__10MenuWindowFP9MenuPlace(param_1,iVar1);
    SetIcon__10MenuCommonFcP10MenuSprite((char)*(undefined2 *)(iVar1 + 0x22),iVar1 + 0x50);
    uVar2 = uVar2 + 1;
    iVar1 = iVar1 + 0x130;
  }
  iVar1 = param_1 + 0x5e4;
  uVar2 = 2;
  while( true ) {
    if (3 < (int)uVar2) break;
    SetData__9MenuSceneFUsP8MenuText(param_2,uVar2 & 0xffff,iVar1);
    SetMessage__8MenuTextFPcUiUcUc(iVar1,*(undefined4 *)
                           ((uint)*(ushort *)(iVar1 + 0x16) * 0xc + *(int *)(param_2 + 0x28) + 0x10)
                    ,*(byte *)(iVar1 + 0x58) & 7,0,1);
    OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(param_1 + 0xb4,iVar1,((ulong)*(byte *)(iVar1 + 0x58) & 0xf) >> 3,0);
    AddPlace__10MenuWindowFP9MenuPlace(param_1,iVar1);
    uVar2 = uVar2 + 1;
    iVar1 = iVar1 + 0x80;
  }
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(param_1 + 0xf4,0x421670,uRam0042166c,1,0xffffffffffffffff);
  *(short *)(param_1 + 0x108) = *(short *)(param_1 + 0x188) + -1;
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0xf4);
  SetData__9MenuSceneFUsP10MenuWindow(param_2,0,param_1);
  AddOT__7MenuObjFv(param_1);
  return;
}

/* JP: 0x0047ace0  CmdKeyCustomMenu::~CmdKeyCustomMenu()   [@24@__dt__16CmdKeyCustomMenuFv]  size=0x8 */
undefined4 * _24___dt__16CmdKeyCustomMenuFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -6;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-4] = &__vt__16CmdKeyCustomMenu;
    *param_1 = 0x408c74;
    param_1[3] = 0x408c80;
    __destroy_arr(param_1 + 0x173,0x27c030,0x80,2);
    __destroy_arr(param_1 + 0x43,0x47a7f0,0x130,4);
    __dt__11SendOnLocalFv(param_1 + 0x37,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x27,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}

/* JP: 0x0047acf0  CmdKeyCustomMenu::~CmdKeyCustomMenu()   [@36@__dt__16CmdKeyCustomMenuFv]  size=0x8 */
undefined4 * _36___dt__16CmdKeyCustomMenuFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -9;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-7] = &__vt__16CmdKeyCustomMenu;
    param_1[-3] = 0x408c74;
    *param_1 = 0x408c80;
    __destroy_arr(param_1 + 0x170,0x27c030,0x80,2);
    __destroy_arr(param_1 + 0x40,0x47a7f0,0x130,4);
    __dt__11SendOnLocalFv(param_1 + 0x34,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x24,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}
