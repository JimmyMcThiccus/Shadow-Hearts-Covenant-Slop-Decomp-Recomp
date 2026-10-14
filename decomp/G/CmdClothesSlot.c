/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdClothesSlot   functions: 6
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdClothesSlot.md).
 */

/* JP: 0x00458bf0  CmdClothesSlot::CmdClothesSlot()   [__ct__14CmdClothesSlotFv]  size=0xb0 */
int __ct__14CmdClothesSlotFv(int param_1)

{
  __ct__9CmdWindowFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__14CmdClothesSlot;
  *(undefined4 *)(param_1 + 0x18) = 0x4084d4;
  *(undefined4 *)(param_1 + 0x24) = 0x4084e0;
  __ct__8FontDrawFv(param_1 + 0xb4);
  __ct__11SendOnLocalFv(param_1 + 0xf4);
  __ct__9MenuGroupFv(param_1 + 0x124);
  __ct__10MenuSpriteFv(param_1 + 0x174);
  __ct__8MenuTextFv(param_1 + 0x1d4);
  return param_1;
}

/* JP: 0x00458ca0  CmdClothesSlot::~CmdClothesSlot()   [__dt__14CmdClothesSlotFv]  size=0x104 */
int __dt__14CmdClothesSlotFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__14CmdClothesSlot;
    *(undefined4 *)(param_1 + 0x18) = 0x4084d4;
    *(undefined4 *)(param_1 + 0x24) = 0x4084e0;
    if (param_1 != -0x124) {
      __dt__8MenuTextFv(param_1 + 0x1d4,0xffffffffffffffff);
      __dt__10MenuSpriteFv(param_1 + 0x174,0xffffffffffffffff);
      __dt__9MenuGroupFv(param_1 + 0x124,0xffffffffffffffff);
    }
    __dt__11SendOnLocalFv(param_1 + 0xf4,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0xb4,0xffffffffffffffff);
    __dt__9CmdWindowFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x00458db0  CmdClothesSlot::CreateScene(CmdClothes*)   [CreateScene__14CmdClothesSlotFP10CmdClothes]  size=0x1d0 */
void CreateScene__14CmdClothesSlotFP10CmdClothes(int param_1,undefined4 param_2)

{
  SetData__9MenuSceneFUsP8FontDraw(param_2,0,param_1 + 0xb4);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0xb4);
  SetData__9MenuSceneFUsP10MenuSprite(param_2,0,param_1 + 0x174);
  SetData__9MenuSceneFUsP8MenuText(param_2,0,param_1 + 0x1d4);
  AddPlace__9MenuGroupFP9MenuPlace(param_1 + 0x124,param_1 + 0x174);
  AddPlace__9MenuGroupFP9MenuPlace(param_1 + 0x124,param_1 + 0x1d4);
  SetIcon__10MenuCommonFcP10MenuSprite((char)*(undefined2 *)(param_1 + 0x196),param_1 + 0x174);
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(param_1 + 0xf4,0x4216b0,uRam004216ac,1,0xffffffffffffffff);
  *(short *)(param_1 + 0x108) = *(short *)(param_1 + 0x188) + -1;
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0xf4);
  SetData__9MenuSceneFUsP9MenuGroup(param_2,0,param_1 + 0x124);
  AddPlace__10MenuWindowFP9MenuPlace(param_1,param_1 + 0x124);
  SetData__9MenuSceneFUsP10MenuWindow(param_2,0,param_1);
  AddOT__7MenuObjFv(param_1);
  return;
}

/* JP: 0x00458f80  CmdClothesSlot::UpdateScene(CmdClothes*)   [UpdateScene__14CmdClothesSlotFP10CmdClothes]  size=0x124 */
void UpdateScene__14CmdClothesSlotFP10CmdClothes(int param_1,int param_2)

{
  ushort uVar1;
  undefined8 uVar2;
  
  uVar1 = (ushort)*(byte *)(*(int *)(*(int *)(*(int *)(param_2 + 0x58) + 0x5c) + 4) + 0xdaa);
  ClearImage__8FontDrawFv(param_1 + 0xb4);
  uVar2 = GetRegDat__9RegDatApiFiii(0xb,uVar1,0xffffffffffffffff);
  SetMessage__8MenuTextFPcUiUcUc(param_1 + 0x1d4,uVar2,*(byte *)(param_1 + 0x22c) & 7,0,1);
  OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(param_1 + 0xb4,param_1 + 0x1d4,((ulong)*(byte *)(param_1 + 0x22c) & 0xf) >> 3,0);
  *(ushort *)(param_1 + 0x13a) = uVar1;
  return;
}

/* JP: 0x004590b0  CmdClothesSlot::~CmdClothesSlot()   [@24@__dt__14CmdClothesSlotFv]  size=0x8 */
undefined4 * _24___dt__14CmdClothesSlotFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -6;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-4] = &__vt__14CmdClothesSlot;
    *param_1 = 0x4084d4;
    param_1[3] = 0x4084e0;
    if (puVar1 != (undefined4 *)0xfffffedc) {
      __dt__8MenuTextFv(param_1 + 0x6f,0xffffffffffffffff);
      __dt__10MenuSpriteFv(param_1 + 0x57,0xffffffffffffffff);
      __dt__9MenuGroupFv(param_1 + 0x43,0xffffffffffffffff);
    }
    __dt__11SendOnLocalFv(param_1 + 0x37,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x27,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}

/* JP: 0x004590c0  CmdClothesSlot::~CmdClothesSlot()   [@36@__dt__14CmdClothesSlotFv]  size=0x8 */
undefined4 * _36___dt__14CmdClothesSlotFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -9;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-7] = &__vt__14CmdClothesSlot;
    param_1[-3] = 0x4084d4;
    *param_1 = 0x4084e0;
    if (puVar1 != (undefined4 *)0xfffffedc) {
      __dt__8MenuTextFv(param_1 + 0x6c,0xffffffffffffffff);
      __dt__10MenuSpriteFv(param_1 + 0x54,0xffffffffffffffff);
      __dt__9MenuGroupFv(param_1 + 0x40,0xffffffffffffffff);
    }
    __dt__11SendOnLocalFv(param_1 + 0x34,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x24,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}
