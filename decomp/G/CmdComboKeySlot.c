/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdComboKeySlot   functions: 7
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdComboKeySlot.md).
 */

/* JP: 0x00488610  CmdComboKeySlot::CmdComboKeySlot()   [__ct__15CmdComboKeySlotFv]  size=0xec */
int __ct__15CmdComboKeySlotFv(int param_1)

{
  __ct__9CmdWindowFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__15CmdComboKeySlot;
  *(undefined4 *)(param_1 + 0x18) = 0x409074;
  *(undefined4 *)(param_1 + 0x24) = 0x409080;
  __ct__8FontDrawFv(param_1 + 0xb4);
  __ct__8MenuTextFv(param_1 + 0xf4);
  __ct__11SendOnLocalFv(param_1 + 0x174);
  __ct__11SendOnLocalFv(param_1 + 0x1a4);
  __construct_array(param_1 + 0x1d4,0x266140,0x2661a0,0x60,4);
  __construct_array(param_1 + 0x354,0x4887a0,0x488700,0x1bc,4);
  return param_1;
}

/* JP: 0x00488800  CmdComboKeySlot::~CmdComboKeySlot()   [__dt__15CmdComboKeySlotFv]  size=0x124 */
int __dt__15CmdComboKeySlotFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__15CmdComboKeySlot;
    *(undefined4 *)(param_1 + 0x18) = 0x409074;
    *(undefined4 *)(param_1 + 0x24) = 0x409080;
    __destroy_arr(param_1 + 0x354,0x488700,0x1bc,4);
    __destroy_arr(param_1 + 0x1d4,0x2661a0,0x60,4);
    __dt__11SendOnLocalFv(param_1 + 0x1a4,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x174,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1 + 0xf4,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0xb4,0xffffffffffffffff);
    __dt__9CmdWindowFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x00488930  CmdComboKeySlot::CreateScene(CmdComboKey*)   [CreateScene__15CmdComboKeySlotFP11CmdComboKey]  size=0x340 */
void CreateScene__15CmdComboKeySlotFP11CmdComboKey(int param_1,undefined4 param_2)

{
  int iVar1;
  short sVar2;
  int iVar3;
  undefined4 uStack_24;
  
  SetData__9MenuSceneFUsP8FontDraw(param_2,0,param_1 + 0xb4);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0xb4);
  SetData__9MenuSceneFUsP8MenuText(param_2,0,param_1 + 0xf4);
  AddPlace__10MenuWindowFP9MenuPlace(param_1,param_1 + 0xf4);
  uStack_24 = 0.0;
  sVar2 = 0;
  iVar3 = param_1 + 0x1d4;
  iVar1 = param_1 + 0x354;
  while( true ) {
    if (3 < sVar2) break;
    SetData__9MenuSceneFUsP10MenuSprite(param_2,sVar2,iVar3);
    AddPlace__10MenuWindowFP9MenuPlace(param_1,iVar3);
    SetData__9MenuSceneFUsP8MenuText(param_2,1,iVar1 + 0x50);
    SetData__9MenuSceneFUsP8MenuText(param_2,2,iVar1 + 0xd0);
    SetData__9MenuSceneFUsP10MenuSprite(param_2,4,iVar1 + 0x150);
    AddPlace__9MenuGroupFP9MenuPlace(iVar1,iVar1 + 0x50);
    AddPlace__9MenuGroupFP9MenuPlace(iVar1,iVar1 + 0xd0);
    AddPlace__9MenuGroupFP9MenuPlace(iVar1,iVar1 + 0x150);
    SetData__9MenuSceneFUsP9MenuGroup(param_2,0,iVar1);
    (**(code **)(*(int *)(iVar1 + 8) + 0x24))
              (*(undefined4 *)(iVar1 + 0x24),uStack_24 + *(float *)(iVar1 + 0x28));
    *(undefined2 *)(iVar1 + 0x1c) = 0;
    *(short *)(iVar1 + 0x1e) = sVar2 + 1;
    AddPlace__10MenuWindowFP9MenuPlace(param_1,iVar1);
    uStack_24 = uStack_24 + *(float *)(iVar1 + 0x30);
    sVar2 = sVar2 + 1;
    iVar1 = iVar1 + 0x1bc;
    iVar3 = iVar3 + 0x60;
  }
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(param_1 + 0x174,0x421670,uRam0042166c,1,0xffffffffffffffff);
  *(short *)(param_1 + 0x188) = *(short *)(param_1 + 0x1e8) + -1;
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0x174);
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(param_1 + 0x1a4,0x4216f0,uRam004216ec,1,6);
  *(short *)(param_1 + 0x1b8) = *(short *)(param_1 + 0x4b8) + -1;
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0x1a4);
  SetData__9MenuSceneFUsP10MenuWindow(param_2,0,param_1);
  AddOT__7MenuObjFv(param_1);
  return;
}

/* JP: 0x00488c70  CmdComboKeySlot::UpdateScene(CmdComboKey*, short, short)   [UpdateScene__15CmdComboKeySlotFP11CmdComboKeyss]  size=0x384 */
void UpdateScene__15CmdComboKeySlotFP11CmdComboKeyss
               (int param_1,int param_2,short param_3,short param_4)

{
  undefined4 uVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  long lVar7;
  uint uVar8;
  char *pcVar9;
  
  uVar1 = *(undefined4 *)(param_2 + 0xcb0);
  iVar5 = *(int *)(param_2 + 0xcac) + param_3 * 0xc;
  iVar2 = *(int *)(param_2 + 0x5c);
  piVar3 = *(int **)(param_2 + 0x70);
  pcVar9 = (char *)(*(int *)(iVar2 + 4) + param_3 * 0x10 + 0xf44);
  iVar4 = *(int *)(param_2 + 0x28);
  ClearImage__8FontDrawFv(param_1 + 0xb4);
  if (param_4 != 0) {
    if (param_3 < 0xc) {
      SetMessage__8MenuTextFPcUiUcUc(param_1 + 0xf4,*piVar3 + 10,*(byte *)(param_1 + 0x14c) & 7,0,0);
    }
    else {
      uVar6 = GetRegDat__9RegDatApiFiii(*(undefined2 *)(iVar5 + 4),*(undefined2 *)(iVar5 + 8),
                              0xffffffffffffffff);
      SetMessage__8MenuTextFPcUiUcUc(param_1 + 0xf4,uVar6,*(byte *)(param_1 + 0x14c) & 7,0,0);
    }
    DisableFontItem__8FontItemFv(param_1 + 0xf4);
    if (piVar3[0xb] != 0) {
      EnableFontItem__8FontItemFv(param_1 + 0xf4);
    }
  }
  OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(param_1 + 0xb4,param_1 + 0xf4,((ulong)*(byte *)(param_1 + 0x14c) & 0xf) >> 3,0);
  for (uVar8 = param_1 + 0x354; uVar8 < param_1 + 0xa44U; uVar8 = uVar8 + 0x1bc) {
    *(byte *)(uVar8 + 0xe2) = *(byte *)(uVar8 + 0xe2) & 0xfe;
    *(byte *)(uVar8 + 0x162) = *(byte *)(uVar8 + 0x162) & 0xfe;
    lVar7 = GetComboKeyData__8CmdPartyFsP15SHORTCUTCommandPcP15CmdComboKeyData
                      (iVar2,param_3,pcVar9,uVar1,uVar8 + 0x1b0);
    if (lVar7 == 0) {
      SetMessage__8MenuTextFPcUiUcUc(uVar8 + 0x50,*(undefined4 *)(iVar4 + 0x4c),*(byte *)(uVar8 + 0xa8) & 7,0,1);
      *(undefined4 *)(uVar8 + 0x1b4) = *(undefined4 *)(iVar4 + 0x50);
      *(undefined2 *)(uVar8 + 0x16) = 0;
    }
    else {
      SetMessage__8MenuTextFPcUiUcUc(uVar8 + 0x50,*(undefined4 *)(uVar8 + 0x1b0),*(byte *)(uVar8 + 0xa8) & 7,0,1);
      if (*pcVar9 == '\x01') {
        SetIcon__10MenuCommonFcP10MenuSprite(pcVar9[1],uVar8 + 0x150);
        *(byte *)(uVar8 + 0x162) = *(byte *)(uVar8 + 0x162) & 0xfe | 1;
      }
      *(undefined2 *)(uVar8 + 0x16) = 1;
    }
    OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(param_1 + 0xb4,uVar8 + 0x50,((ulong)*(byte *)(uVar8 + 0xa8) & 0xf) >> 3,0);
    pcVar9 = pcVar9 + 4;
  }
  return;
}

/* JP: 0x00489000  CmdComboKeySlot::Select(CmdComboKey*, MenuPlace*, MenuPlace*)   [Select__15CmdComboKeySlotFP11CmdComboKeyP9MenuPlaceP9MenuPlace]  size=0x1e8 */
void Select__15CmdComboKeySlotFP11CmdComboKeyP9MenuPlaceP9MenuPlace
               (int param_1,int param_2,int param_3,int param_4)

{
  undefined4 uVar1;
  int iVar2;
  
  if ((param_4 != 0) && ((long)((ulong)*(byte *)(param_4 + 0x21) << 0x3c) < 0)) {
    if (*(short *)(param_4 + 0x1e) == 0) {
      SetCSA__8FontItemFUc(param_4,0);
    }
    else {
      iVar2 = param_1 + (*(short *)(param_4 + 0x1e) + -1) * 0x1bc;
      SetCSA__8FontItemFUc(iVar2 + 0x3a4,0);
      SetCSA__8FontItemFUc(iVar2 + 0x424,0);
    }
  }
  if (param_3 != 0) {
    uVar1 = *(undefined4 *)(param_2 + 100);
    if (*(short *)(param_3 + 0x1e) == 0) {
      SetCSA__8FontItemFUc(param_3,1);
      SetExplanation__7CmdNoteFPCce
                (uVar1,*(undefined4 *)(*(int *)(param_2 + 0x28) + 0x5c),
                 *(undefined4 *)(param_1 + 0x154));
    }
    else {
      param_1 = param_1 + (*(short *)(param_3 + 0x1e) + -1) * 0x1bc;
      SetCSA__8FontItemFUc(param_1 + 0x3a4,1);
      SetCSA__8FontItemFUc(param_1 + 0x424,1);
      SetExplanation__7CmdNoteFPCce(uVar1,*(undefined4 *)(param_1 + 0x508));
    }
  }
  return;
}

/* JP: 0x004891f0  CmdComboKeySlot::~CmdComboKeySlot()   [@24@__dt__15CmdComboKeySlotFv]  size=0x8 */
undefined4 * _24___dt__15CmdComboKeySlotFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -6;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-4] = &__vt__15CmdComboKeySlot;
    *param_1 = 0x409074;
    param_1[3] = 0x409080;
    __destroy_arr(param_1 + 0xcf,0x488700,0x1bc,4);
    __destroy_arr(param_1 + 0x6f,0x2661a0,0x60,4);
    __dt__11SendOnLocalFv(param_1 + 99,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x57,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1 + 0x37,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x27,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}

/* JP: 0x00489200  CmdComboKeySlot::~CmdComboKeySlot()   [@36@__dt__15CmdComboKeySlotFv]  size=0x8 */
undefined4 * _36___dt__15CmdComboKeySlotFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -9;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-7] = &__vt__15CmdComboKeySlot;
    param_1[-3] = 0x409074;
    *param_1 = 0x409080;
    __destroy_arr(param_1 + 0xcc,0x488700,0x1bc,4);
    __destroy_arr(param_1 + 0x6c,0x2661a0,0x60,4);
    __dt__11SendOnLocalFv(param_1 + 0x60,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x54,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1 + 0x34,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x24,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}
