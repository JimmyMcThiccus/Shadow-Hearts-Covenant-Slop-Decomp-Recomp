/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdRingCustomFinalSlot   functions: 7
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdRingCustomFinalSlot.md).
 */

/* JP: 0x0046e090  CmdRingCustomFinalSlot::CmdRingCustomFinalSlot()   [__ct__22CmdRingCustomFinalSlotFv]  size=0xb0 */
int __ct__22CmdRingCustomFinalSlotFv(int param_1)

{
  __ct__9CmdWindowFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__22CmdRingCustomFinalSlot;
  *(undefined4 *)(param_1 + 0x18) = 0x408984;
  *(undefined4 *)(param_1 + 0x24) = 0x408990;
  __ct__8FontDrawFv(param_1 + 0xb4);
  __ct__11SendOnLocalFv(param_1 + 0xf4);
  __ct__9MenuGroupFv(param_1 + 0x124);
  __ct__10MenuSpriteFv(param_1 + 0x174);
  __ct__8MenuTextFv(param_1 + 0x1d4);
  return param_1;
}

/* JP: 0x0046e140  CmdRingCustomFinalSlot::~CmdRingCustomFinalSlot()   [__dt__22CmdRingCustomFinalSlotFv]  size=0x104 */
int __dt__22CmdRingCustomFinalSlotFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__22CmdRingCustomFinalSlot;
    *(undefined4 *)(param_1 + 0x18) = 0x408984;
    *(undefined4 *)(param_1 + 0x24) = 0x408990;
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

/* JP: 0x0046e250  CmdRingCustomFinalSlot::CreateScene(CmdRingCustom*)   [CreateScene__22CmdRingCustomFinalSlotFP13CmdRingCustom]  size=0x1bc */
void CreateScene__22CmdRingCustomFinalSlotFP13CmdRingCustom(int param_1,undefined4 param_2)

{
  SetData__9MenuSceneFUsP8FontDraw(param_2,1,param_1 + 0xb4);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0xb4);
  SetData__9MenuSceneFUsP10MenuSprite(param_2,1,param_1 + 0x174);
  SetData__9MenuSceneFUsP8MenuText(param_2,2,param_1 + 0x1d4);
  AddPlace__9MenuGroupFP9MenuPlace(param_1 + 0x124,param_1 + 0x174);
  AddPlace__9MenuGroupFP9MenuPlace(param_1 + 0x124,param_1 + 0x1d4);
  SetIcon__10MenuCommonFcP10MenuSprite((char)*(undefined2 *)(param_1 + 0x196),param_1 + 0x174);
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(param_1 + 0xf4,0x4216b0,uRam004216ac,1,0xffffffffffffffff);
  *(short *)(param_1 + 0x108) = *(short *)(param_1 + 0x188) + -1;
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0xf4);
  SetData__9MenuSceneFUsP9MenuGroup(param_2,0,param_1 + 0x124);
  AddPlace__10MenuWindowFP9MenuPlace(param_1,param_1 + 0x124);
  SetData__9MenuSceneFUsP10MenuWindow(param_2,1,param_1);
  AddOT__7MenuObjFv(param_1);
  return;
}

/* JP: 0x0046e410  CmdRingCustomFinalSlot::UpdateScene(CmdRingCustom*)   [UpdateScene__22CmdRingCustomFinalSlotFP13CmdRingCustom]  size=0x1f8 */
void UpdateScene__22CmdRingCustomFinalSlotFP13CmdRingCustom(int param_1,int param_2)

{
  bool bVar1;
  undefined4 uVar2;
  short sVar3;
  float fStack_24;
  
  sVar3 = (short)*(char *)(**(int **)(param_2 + 0x70) + 100);
  ClearImage__8FontDrawFv(param_1 + 0xb4);
  bVar1 = (long)*(char *)(param_2 + 0x21f) <= (long)sVar3;
  if (bVar1) {
    uVar2 = GetRegDat__9RegDatApiFiii(0x11,sVar3,0xffffffffffffffff);
    fStack_24 = (float)(int)*(short *)(*(int *)(param_2 + 0x44) + 0x4c);
  }
  else {
    uVar2 = *(undefined4 *)(*(int *)(param_2 + 0x28) + 0x118);
    fStack_24 = *(float *)(param_1 + 0x198);
  }
  SetMessage__8MenuTextFPcUiUcUc(param_1 + 0x1d4,uVar2,*(byte *)(param_1 + 0x22c) & 7,0,1);
  (**(code **)(*(int *)(param_1 + 0x1dc) + 0x24))(fStack_24,*(undefined4 *)(param_1 + 0x1fc));
  *(byte *)(param_1 + 0x186) = *(byte *)(param_1 + 0x186) & 0xfe | bVar1;
  OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(param_1 + 0xb4,param_1 + 0x1d4,((ulong)*(byte *)(param_1 + 0x22c) & 0xf) >> 3,0);
  *(short *)(param_1 + 0x13a) = sVar3;
  return;
}

/* JP: 0x0046e610  CmdRingCustomFinalSlot::Select(CmdRingCustom*)   [Select__22CmdRingCustomFinalSlotFP13CmdRingCustom]  size=0xdc */
void Select__22CmdRingCustomFinalSlotFP13CmdRingCustom(int param_1,int param_2)

{
  short sVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  
  sVar1 = *(short *)(param_1 + 0x13a);
  uVar2 = *(undefined4 *)(param_2 + 100);
  SetCSA__8FontItemFUc(param_1 + 0x1d4,1);
  if (sVar1 < 0) {
    SetExplanation__7CmdNoteFPCce(uVar2,*(undefined4 *)(*(int *)(param_2 + 0x28) + 0x11c));
  }
  else {
    uVar3 = GetRegDat__9RegDatApiFiii(0x22,sVar1,0xffffffffffffffff);
    SetExplanation__7CmdNoteFPCce(uVar2,uVar3);
  }
  return;
}

/* JP: 0x0046e6f0  CmdRingCustomFinalSlot::~CmdRingCustomFinalSlot()   [@24@__dt__22CmdRingCustomFinalSlotFv]  size=0x8 */
undefined4 * _24___dt__22CmdRingCustomFinalSlotFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -6;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-4] = &__vt__22CmdRingCustomFinalSlot;
    *param_1 = 0x408984;
    param_1[3] = 0x408990;
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

/* JP: 0x0046e700  CmdRingCustomFinalSlot::~CmdRingCustomFinalSlot()   [@36@__dt__22CmdRingCustomFinalSlotFv]  size=0x8 */
undefined4 * _36___dt__22CmdRingCustomFinalSlotFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -9;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-7] = &__vt__22CmdRingCustomFinalSlot;
    param_1[-3] = 0x408984;
    *param_1 = 0x408990;
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
