/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdTopMenuData   functions: 5
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdTopMenuData.md).
 */

/* JP: 0x0048bd70  CmdTopMenuData::CmdTopMenuData()   [__ct__14CmdTopMenuDataFv]  size=0x94 */
int __ct__14CmdTopMenuDataFv(int param_1)

{
  __ct__9CmdWindowFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__14CmdTopMenuData;
  *(undefined4 *)(param_1 + 0x18) = 0x4091d4;
  *(undefined4 *)(param_1 + 0x24) = 0x4091e0;
  __ct__8FontDrawFv(param_1 + 0xb4);
  __construct_array(param_1 + 0xf4,0x27bfd0,0x27c030,0x80,2);
  return param_1;
}

/* JP: 0x0048be10  CmdTopMenuData::~CmdTopMenuData()   [__dt__14CmdTopMenuDataFv]  size=0xc4 */
int __dt__14CmdTopMenuDataFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__14CmdTopMenuData;
    *(undefined4 *)(param_1 + 0x18) = 0x4091d4;
    *(undefined4 *)(param_1 + 0x24) = 0x4091e0;
    __destroy_arr(param_1 + 0xf4,0x27c030,0x80,2);
    __dt__8FontDrawFv(param_1 + 0xb4,0xffffffffffffffff);
    __dt__9CmdWindowFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x0048bee0  CmdTopMenuData::CreateScene(CmdTop*)   [CreateScene__14CmdTopMenuDataFP6CmdTop]  size=0x224 */
void CreateScene__14CmdTopMenuDataFP6CmdTop(int param_1,int param_2)

{
  ushort uVar1;
  int iVar2;
  short sVar3;
  undefined4 uStack_24;
  
  SetData__9MenuSceneFUsP8FontDraw(param_2,1,param_1 + 0xb4);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0xb4);
  iVar2 = param_1 + 0xf4;
  uStack_24 = 0.0;
  uVar1 = 0x18;
  sVar3 = 0;
  while( true ) {
    if (1 < sVar3) break;
    SetData__9MenuSceneFUsP8MenuText(param_2,0,iVar2);
    *(ushort *)(iVar2 + 0x22) = uVar1;
    *(undefined2 *)(iVar2 + 0x1c) = 0;
    *(short *)(iVar2 + 0x1e) = sVar3;
    (**(code **)(*(int *)(iVar2 + 8) + 0x24))(0,uStack_24);
    SetMessage__8MenuTextFPcUiUcUc(iVar2,*(undefined4 *)((uint)uVar1 * 0xc + *(int *)(param_2 + 0x28) + 0x10),
                    *(byte *)(iVar2 + 0x58) & 7,0,1);
    OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(param_1 + 0xb4,iVar2,((ulong)*(byte *)(iVar2 + 0x58) & 0xf) >> 3,0);
    AddPlace__10MenuWindowFP9MenuPlace(param_1,iVar2);
    uStack_24 = uStack_24 + *(float *)(iVar2 + 0x30);
    sVar3 = sVar3 + 1;
    uVar1 = uVar1 + 1;
    iVar2 = iVar2 + 0x80;
  }
  if ((*(ushort *)(*(int *)(param_2 + 0x10) + 0x4a) & 2) == 0) {
    DisableFontItem__8FontItemFv(param_1 + 0xf4);
  }
  SetData__9MenuSceneFUsP10MenuWindow(param_2,0,param_1);
  AddOT__7MenuObjFv(param_1);
  return;
}

/* JP: 0x0048c110  CmdTopMenuData::~CmdTopMenuData()   [@24@__dt__14CmdTopMenuDataFv]  size=0x8 */
undefined4 * _24___dt__14CmdTopMenuDataFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -6;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-4] = &__vt__14CmdTopMenuData;
    *param_1 = 0x4091d4;
    param_1[3] = 0x4091e0;
    __destroy_arr(param_1 + 0x37,0x27c030,0x80,2);
    __dt__8FontDrawFv(param_1 + 0x27,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}

/* JP: 0x0048c120  CmdTopMenuData::~CmdTopMenuData()   [@36@__dt__14CmdTopMenuDataFv]  size=0x8 */
undefined4 * _36___dt__14CmdTopMenuDataFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -9;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-7] = &__vt__14CmdTopMenuData;
    param_1[-3] = 0x4091d4;
    *param_1 = 0x4091e0;
    __destroy_arr(param_1 + 0x34,0x27c030,0x80,2);
    __dt__8FontDrawFv(param_1 + 0x24,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}
