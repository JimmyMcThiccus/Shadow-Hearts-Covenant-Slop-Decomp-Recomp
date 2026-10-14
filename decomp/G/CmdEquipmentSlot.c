/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdEquipmentSlot   functions: 7
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdEquipmentSlot.md).
 */

/* JP: 0x0044f6d0  CmdEquipmentSlot::CmdEquipmentSlot()   [__ct__16CmdEquipmentSlotFv]  size=0x10c */
int __ct__16CmdEquipmentSlotFv(int param_1)

{
  __ct__9CmdWindowFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__16CmdEquipmentSlot;
  *(undefined4 *)(param_1 + 0x18) = 0x408094;
  *(undefined4 *)(param_1 + 0x24) = 0x4080a0;
  __ct__8FontDrawFv(param_1 + 0xb4);
  __ct__11SendOnLocalFv(param_1 + 0xf4);
  __ct__9MenuGroupFv(param_1 + 0x124);
  __ct__10MenuSpriteFv(param_1 + 0x174);
  __ct__8MenuTextFv(param_1 + 0x1d4);
  __ct__9MenuGroupFv(param_1 + 0x254);
  __ct__10MenuSpriteFv(param_1 + 0x2a4);
  __ct__8MenuTextFv(param_1 + 0x304);
  __construct_array(param_1 + 900,0x44f870,0x44f7e0,0x130,3);
  return param_1;
}

/* JP: 0x0044f8c0  CmdEquipmentSlot::~CmdEquipmentSlot()   [__dt__16CmdEquipmentSlotFv]  size=0x174 */
int __dt__16CmdEquipmentSlotFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__16CmdEquipmentSlot;
    *(undefined4 *)(param_1 + 0x18) = 0x408094;
    *(undefined4 *)(param_1 + 0x24) = 0x4080a0;
    __destroy_arr(param_1 + 900,0x44f7e0,0x130,3);
    if (param_1 != -0x254) {
      __dt__8MenuTextFv(param_1 + 0x304,0xffffffffffffffff);
      __dt__10MenuSpriteFv(param_1 + 0x2a4,0xffffffffffffffff);
      __dt__9MenuGroupFv(param_1 + 0x254,0xffffffffffffffff);
    }
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

/* JP: 0x0044fa40  CmdEquipmentSlot::CreateScene(CmdEquipment*)   [CreateScene__16CmdEquipmentSlotFP12CmdEquipment]  size=0x2f0 */
void CreateScene__16CmdEquipmentSlotFP12CmdEquipment(int param_1,undefined4 param_2)

{
  short sVar1;
  int iVar2;
  int iVar3;
  undefined4 uStack_24;
  
  SetData__9MenuSceneFUsP8FontDraw(param_2,0,param_1 + 0xb4);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0xb4);
  iVar2 = param_1 + 0x124;
  for (iVar3 = 0; iVar3 < 5; iVar3 = iVar3 + 1) {
    SetData__9MenuSceneFUsP10MenuSprite(param_2,0,iVar2 + 0x50);
    SetData__9MenuSceneFUsP8MenuText(param_2,0,iVar2 + 0xb0);
    AddPlace__9MenuGroupFP9MenuPlace(iVar2,iVar2 + 0x50);
    AddPlace__9MenuGroupFP9MenuPlace(iVar2,iVar2 + 0xb0);
    SetData__9MenuSceneFUsP9MenuGroup(param_2,0,iVar2);
    *(undefined2 *)(iVar2 + 0x1c) = 0;
    *(short *)(iVar2 + 0x1e) = (short)iVar3;
    AddPlace__10MenuWindowFP9MenuPlace(param_1,iVar2);
    iVar2 = iVar2 + 0x130;
  }
  iVar2 = param_1 + 0x124;
  uStack_24 = 0.0;
  sVar1 = *(short *)(param_1 + 0x146);
  for (iVar3 = 0; iVar3 < 2; iVar3 = iVar3 + 1) {
    (**(code **)(*(int *)(iVar2 + 8) + 0x24))
              (*(undefined4 *)(iVar2 + 0x24),uStack_24 + *(float *)(iVar2 + 0x28));
    *(short *)(iVar2 + 0x22) = (short)iVar3;
    uStack_24 = uStack_24 + (float)(int)sVar1;
    iVar2 = iVar2 + 0x130;
  }
  for (iVar3 = 0; iVar3 < 3; iVar3 = iVar3 + 1) {
    (**(code **)(*(int *)(iVar2 + 8) + 0x24))
              (*(undefined4 *)(iVar2 + 0x24),uStack_24 + *(float *)(iVar2 + 0x28));
    *(undefined2 *)(iVar2 + 0x22) = 2;
    uStack_24 = uStack_24 + *(float *)(iVar2 + 0x30);
    iVar2 = iVar2 + 0x130;
  }
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(param_1 + 0xf4,0x4216b0,uRam004216ac,1,0xffffffffffffffff);
  *(short *)(param_1 + 0x108) = *(short *)(param_1 + 0x188) + -1;
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0xf4);
  SetData__9MenuSceneFUsP10MenuWindow(param_2,0,param_1);
  AddOT__7MenuObjFv(param_1);
  return;
}

/* JP: 0x0044fd30  CmdEquipmentSlot::UpdateScene(CmdEquipment*)   [UpdateScene__16CmdEquipmentSlotFP12CmdEquipment]  size=0x2b0 */
void UpdateScene__16CmdEquipmentSlotFP12CmdEquipment(int param_1,int param_2)

{
  char cVar1;
  int *piVar2;
  int iVar3;
  undefined4 uVar4;
  short sVar5;
  char *pcVar6;
  int iVar7;
  short sVar8;
  float fStack_2c;
  
  piVar2 = *(int **)(param_2 + 0x70);
  iVar3 = *(int *)(param_2 + 0x44);
  ClearImage__8FontDrawFv(param_1 + 0xb4);
  iVar7 = param_1 + 0x124;
  pcVar6 = (char *)(*piVar2 + 0x2d);
  sVar8 = 0;
  for (sVar5 = 0; sVar5 < 5; sVar5 = sVar5 + 1) {
    cVar1 = *pcVar6;
    if (-1 < cVar1) {
      SetIcon__10MenuCommonFcP10MenuSprite(*(undefined1 *)
                       (*(int *)(param_2 + (char)sVar8 * 4 + 0xb4) +
                        (uint)(ushort)(short)*pcVar6 * 0xc + 8),iVar7 + 0x50);
      uVar4 = GetRegDat__9RegDatApiFiii(sVar8 + 6,*pcVar6,0xffffffffffffffff);
      fStack_2c = (float)(int)*(short *)(iVar3 + 0x14);
    }
    else {
      fStack_2c = *(float *)(iVar7 + 0x74);
      uVar4 = *(undefined4 *)(*(int *)(param_2 + 0x28) + 0x28);
    }
    (**(code **)(*(int *)(iVar7 + 0xb8) + 0x24))(fStack_2c,*(undefined4 *)(iVar7 + 0xd8));
    SetMessage__8MenuTextFPcUiUcUc(iVar7 + 0xb0,uVar4,*(byte *)(iVar7 + 0x108) & 7,0,1);
    OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(param_1 + 0xb4,iVar7 + 0xb0,((ulong)*(byte *)(iVar7 + 0x108) & 0xf) >> 3,0);
    *(byte *)(iVar7 + 0x62) = *(byte *)(iVar7 + 0x62) & 0xfe | -1 < cVar1;
    *(short *)(iVar7 + 0x16) = (short)*pcVar6;
    if (sVar5 < 2) {
      sVar8 = sVar8 + 1;
    }
    iVar7 = iVar7 + 0x130;
    pcVar6 = pcVar6 + 1;
  }
  return;
}

/* JP: 0x0044ffe0  CmdEquipmentSlot::Select(CmdEquipment*, MenuGroup*, MenuGroup*)   [Select__16CmdEquipmentSlotFP12CmdEquipmentP9MenuGroupP9MenuGroup]  size=0x16c */
void Select__16CmdEquipmentSlotFP12CmdEquipmentP9MenuGroupP9MenuGroup
               (undefined8 param_1,int param_2,int param_3,int param_4)

{
  short sVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  
  if (param_4 != 0) {
    uVar3 = FindPlace__9MenuGroupFs(param_4,10);
    SetCSA__8FontItemFUc(uVar3,0);
  }
  if (param_3 != 0) {
    sVar1 = *(short *)(param_3 + 0x16);
    uVar3 = FindPlace__9MenuGroupFs(param_3,10);
    SetCSA__8FontItemFUc(uVar3,1);
    if (sVar1 < 0) {
      uVar2 = *(undefined4 *)(*(int *)(param_2 + 0x28) + 0x2c);
    }
    else {
      uVar2 = GetRegDat__9RegDatApiFiii(*(char *)(param_2 + 0xa4) + 0x17,sVar1,0xffffffffffffffff);
    }
    SetExplanation__7CmdNoteFPCce(*(undefined4 *)(param_2 + 100),uVar2);
    SetButtonReport__12CmdEquipmentFss(param_2,0,*(undefined2 *)(param_3 + 0x16));
  }
  return;
}

/* JP: 0x00450150  CmdEquipmentSlot::~CmdEquipmentSlot()   [@24@__dt__16CmdEquipmentSlotFv]  size=0x8 */
undefined4 * _24___dt__16CmdEquipmentSlotFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -6;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-4] = &__vt__16CmdEquipmentSlot;
    *param_1 = 0x408094;
    param_1[3] = 0x4080a0;
    __destroy_arr(param_1 + 0xdb,0x44f7e0,0x130,3);
    if (puVar1 != (undefined4 *)0xfffffdac) {
      __dt__8MenuTextFv(param_1 + 0xbb,0xffffffffffffffff);
      __dt__10MenuSpriteFv(param_1 + 0xa3,0xffffffffffffffff);
      __dt__9MenuGroupFv(param_1 + 0x8f,0xffffffffffffffff);
    }
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

/* JP: 0x00450160  CmdEquipmentSlot::~CmdEquipmentSlot()   [@36@__dt__16CmdEquipmentSlotFv]  size=0x8 */
undefined4 * _36___dt__16CmdEquipmentSlotFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -9;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-7] = &__vt__16CmdEquipmentSlot;
    param_1[-3] = 0x408094;
    *param_1 = 0x4080a0;
    __destroy_arr(param_1 + 0xd8,0x44f7e0,0x130,3);
    if (puVar1 != (undefined4 *)0xfffffdac) {
      __dt__8MenuTextFv(param_1 + 0xb8,0xffffffffffffffff);
      __dt__10MenuSpriteFv(param_1 + 0xa0,0xffffffffffffffff);
      __dt__9MenuGroupFv(param_1 + 0x8c,0xffffffffffffffff);
    }
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
