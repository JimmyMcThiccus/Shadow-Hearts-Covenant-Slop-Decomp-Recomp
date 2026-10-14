/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdEquipmentGoods   functions: 7
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdEquipmentGoods.md).
 */

/* JP: 0x00450170  CmdEquipmentGoods::CmdEquipmentGoods()   [__ct__17CmdEquipmentGoodsFv]  size=0x84 */
int __ct__17CmdEquipmentGoodsFv(int param_1)

{
  __ct__9CmdWindowFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__17CmdEquipmentGoods;
  *(undefined4 *)(param_1 + 0x18) = 0x4080d4;
  *(undefined4 *)(param_1 + 0x24) = 0x4080e0;
  __ct__11SendOnLocalFv(param_1 + 0xb4);
  __ct__8FontDrawFv(param_1 + 0xe4);
  *(undefined4 *)(param_1 + 0x124) = 0;
  return param_1;
}

/* JP: 0x00450200  CmdEquipmentGoods::~CmdEquipmentGoods()   [__dt__17CmdEquipmentGoodsFv]  size=0xec */
int __dt__17CmdEquipmentGoodsFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__17CmdEquipmentGoods;
    *(undefined4 *)(param_1 + 0x18) = 0x4080d4;
    *(undefined4 *)(param_1 + 0x24) = 0x4080e0;
    if (*(int *)(param_1 + 0x124) != 0) {
      __destroy_new_array(*(undefined4 *)(param_1 + 0x124),0x4502f0);
      *(undefined4 *)(param_1 + 0x124) = 0;
    }
    __dt__8FontDrawFv(param_1 + 0xe4,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0xb4,0xffffffffffffffff);
    __dt__9CmdWindowFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x004503a0  CmdEquipmentGoods::CreateScene(CmdEquipment*, unsigned short)   [CreateScene__17CmdEquipmentGoodsFP12CmdEquipmentUs]  size=0x270 */
void CreateScene__17CmdEquipmentGoodsFP12CmdEquipmentUs
               (int param_1,undefined4 param_2,ushort param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  uint uVar4;
  
  uVar3 = __nwa__FUi((uint)param_3 * 0x1b0 + 0x10);
  uVar2 = __construct_new_array(uVar3,0x450610,0x4502f0,0x1b0,param_3);
  *(undefined4 *)(param_1 + 0x124) = uVar2;
  iVar1 = *(int *)(param_1 + 0x124);
  for (uVar4 = *(uint *)(param_1 + 0x124); uVar4 < iVar1 + (uint)param_3 * 0x1b0;
      uVar4 = uVar4 + 0x1b0) {
    SetData__9MenuSceneFUsP10MenuSprite(param_2,1,uVar4 + 0x150);
    SetData__9MenuSceneFUsP8MenuText(param_2,1,uVar4 + 0x50);
    SetData__9MenuSceneFUsP8MenuText(param_2,2,uVar4 + 0xd0);
    AddPlace__9MenuGroupFP9MenuPlace(uVar4,uVar4 + 0x150);
    AddPlace__9MenuGroupFP9MenuPlace(uVar4,uVar4 + 0x50);
    AddPlace__9MenuGroupFP9MenuPlace(uVar4,uVar4 + 0xd0);
    SetData__9MenuSceneFUsP9MenuGroup(param_2,1,uVar4);
  }
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(param_1 + 0xb4,0x4216b0,uRam004216ac,1,0xffffffffffffffff);
  *(short *)(param_1 + 200) = *(short *)(*(int *)(param_1 + 0x124) + 0x164) + -1;
  SetData__9MenuSceneFUsP8FontDraw(param_2,1,param_1 + 0xe4);
  iVar1 = *(int *)(param_1 + 0x124);
  *(undefined2 *)(iVar1 + 0x1c) = 0;
  *(undefined2 *)(iVar1 + 0x1e) = 1;
  AddPlace__10MenuWindowFP9MenuPlace(param_1,*(undefined4 *)(param_1 + 0x124));
  SetData__9MenuSceneFUsP10MenuWindow(param_2,1,param_1);
  AddOT__7MenuObjFv(param_1);
  return;
}

/* JP: 0x00450700  CmdEquipmentGoods::UpdateScene(CmdEquipment*, short)   [UpdateScene__17CmdEquipmentGoodsFP12CmdEquipments]  size=0x4c8 */
void UpdateScene__17CmdEquipmentGoodsFP12CmdEquipments(int param_1,int param_2,short param_3)

{
  bool bVar1;
  undefined4 uVar2;
  undefined1 uVar3;
  int iVar4;
  uint uVar5;
  ushort uVar6;
  undefined1 auStack_60 [8];
  float fStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  float fStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  float fStack_34;
  int iStack_30;
  int iStack_20;
  short sStack_10;
  
  fStack_34 = 0.0;
  iVar4 = *(int *)(param_1 + 0x124);
  *(undefined2 *)(param_1 + 0x128) = 0;
  iStack_30 = param_1;
  iStack_20 = param_2;
  sStack_10 = param_3;
  ClearPlace__10MenuWindowFv(param_1);
  bVar1 = sStack_10 == 1;
  if (bVar1) {
    *(byte *)(iVar4 + 0x162) = *(byte *)(iVar4 + 0x162) & 0xfe | 1;
    *(byte *)(iVar4 + 0xe2) = *(byte *)(iVar4 + 0xe2) & 0xfe | 1;
    uStack_50 = *(undefined4 *)(iVar4 + 0x78);
    (**(code **)(*(int *)(iVar4 + 0x58) + 0x24))
              ((float)(int)*(short *)(*(int *)(iStack_20 + 0x44) + 0x14),uStack_50);
  }
  else {
    uStack_40 = *(undefined4 *)(iVar4 + 0x78);
    uStack_44 = *(undefined4 *)(iVar4 + 0x174);
    (**(code **)(*(int *)(iVar4 + 0x58) + 0x24))(uStack_44,uStack_40);
    uStack_38 = *(undefined4 *)
                 (((int)sStack_10 + 4U & 0xffff) * 0xc + *(int *)(iStack_20 + 0x28) + 0x10);
    SetMessage__8MenuTextFPcUiUcUc(iVar4 + 0x50,uStack_38,*(byte *)(iVar4 + 0xa8) & 7,0,0);
    *(byte *)(iVar4 + 0x162) = *(byte *)(iVar4 + 0x162) & 0xfe;
    *(byte *)(iVar4 + 0xe2) = *(byte *)(iVar4 + 0xe2) & 0xfe;
    *(short *)(iVar4 + 0x16) = sStack_10;
    *(undefined2 *)(iVar4 + 0x1c) = 0;
    *(undefined2 *)(iVar4 + 0x1e) = 0;
    uStack_48 = *(undefined4 *)(iVar4 + 0x24);
    (**(code **)(*(int *)(iVar4 + 8) + 0x24))(uStack_48,fStack_34);
    AddPlace__10MenuWindowFP9MenuPlace(iStack_30,iVar4);
    fStack_4c = *(float *)(iVar4 + 0x1e0);
    fStack_34 = fStack_34 + fStack_4c;
    iVar4 = iVar4 + 0x1b0;
  }
  uVar6 = (ushort)!bVar1;
  if (sStack_10 != 0) {
    for (uVar5 = 0;
        uVar5 < *(uint *)(*(int *)(iStack_20 + *(char *)(iStack_20 + 0xa4) * 4 + 0xa8) + 8);
        uVar5 = uVar5 + 1 & 0xffff) {
      if (*(char *)(*(int *)(iStack_20 + *(char *)(iStack_20 + 0xa4) * 4 + 0xb4) + uVar5 * 0xc + 9)
          != '\0') {
        SetIcon__10MenuCommonFcP10MenuSprite(*(undefined1 *)
                         (*(int *)(iStack_20 + *(char *)(iStack_20 + 0xa4) * 4 + 0xb4) + uVar5 * 0xc
                         + 8),iVar4 + 0x150);
        uStack_3c = GetRegDat__9RegDatApiFiii(*(char *)(iStack_20 + 0xa4) + 6,uVar5,0xffffffffffffffff);
        SetMessage__8MenuTextFPcUiUcUc(iVar4 + 0x50,uStack_3c,*(byte *)(iVar4 + 0xa8) & 7,0,0);
        uVar2 = *(undefined4 *)(*(int *)(iStack_20 + 0x24) + 0x78);
        uVar3 = GetPropertyCount__12CmdEquipmentFc(iStack_20,(char)uVar5);
        sprintf(auStack_60,uVar2,uVar3);
        SetMessage__8MenuTextFPcUiUcUc(iVar4 + 0xd0,auStack_60,*(byte *)(iVar4 + 0x128) & 7,1,0);
        *(short *)(iVar4 + 0x16) = (short)uVar5;
        *(undefined2 *)(iVar4 + 0x1c) = 0;
        *(ushort *)(iVar4 + 0x1e) = uVar6;
        uStack_54 = *(undefined4 *)(iVar4 + 0x24);
        (**(code **)(*(int *)(iVar4 + 8) + 0x24))(uStack_54,fStack_34);
        AddPlace__10MenuWindowFP9MenuPlace(iStack_30,iVar4);
        *(short *)(iStack_30 + 0x128) = *(short *)(iStack_30 + 0x128) + 1;
        uVar6 = uVar6 + 1;
        fStack_58 = *(float *)(iVar4 + 0x1e0);
        fStack_34 = fStack_34 + fStack_58;
        iVar4 = iVar4 + 0x1b0;
      }
    }
    AddPriority__12MenuObjTableFP7MenuObj(iStack_30 + 0x18,iStack_30 + 0xb4);
  }
  AddPriority__12MenuObjTableFP7MenuObj(iStack_30 + 0x18,iStack_30 + 0xe4);
  *(int *)(*(int *)(iStack_30 + 0x40) + 0x38) = iStack_30 + 0xe4;
  SetScroll__10MenuWindowFss(iStack_30,0,0);
  *(short *)(iStack_30 + 0x12a) = sStack_10;
  *(ushort *)(iStack_30 + 0xae) = uVar6;
  return;
}

/* JP: 0x00450bd0  CmdEquipmentGoods::Select(CmdEquipment*, MenuGroup*, MenuGroup*)   [Select__17CmdEquipmentGoodsFP12CmdEquipmentP9MenuGroupP9MenuGroup]  size=0x21c */
void Select__17CmdEquipmentGoodsFP12CmdEquipmentP9MenuGroupP9MenuGroup
               (undefined8 param_1,int param_2,int param_3,int param_4)

{
  short sVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  undefined1 auStack_70 [32];
  undefined4 uStack_50;
  undefined4 uStack_4c;
  int iStack_48;
  short sStack_42;
  int iStack_30;
  int iStack_20;
  int iStack_10;
  
  iStack_30 = param_2;
  iStack_20 = param_3;
  iStack_10 = param_4;
  if (param_4 != 0) {
    uVar3 = FindPlace__9MenuGroupFs(param_4,10);
    SetCSA__8FontItemFUc(uVar3,0);
    uVar3 = FindPlace__9MenuGroupFs(iStack_10,0x14);
    SetCSA__8FontItemFUc(uVar3,0);
  }
  if (iStack_20 != 0) {
    sVar1 = *(short *)(iStack_20 + 0x16);
    sStack_42 = sVar1;
    uVar3 = FindPlace__9MenuGroupFs(iStack_20,10);
    SetCSA__8FontItemFUc(uVar3,1);
    uVar3 = FindPlace__9MenuGroupFs(iStack_20,0x14);
    SetCSA__8FontItemFUc(uVar3,1);
    if (sVar1 < 0) {
      uVar2 = *(undefined4 *)(*(int *)(iStack_30 + 0x28) + 0x38);
    }
    else {
      uVar2 = GetRegDat__9RegDatApiFiii(*(char *)(iStack_30 + 0xa4) + 0x17,sVar1,0xffffffffffffffff);
      uStack_4c = uVar2;
    }
    uStack_50 = *(undefined4 *)(iStack_30 + 100);
    SetExplanation__7CmdNoteFPCce(uStack_50,uVar2);
    iStack_48 = *(int *)(iStack_30 + 0x9c);
    if (iStack_48 != 0) {
      GetRealStatus__5CmdPCFP11CmdPCStatuscc
                (*(undefined4 *)(iStack_30 + 0x70),auStack_70,
                 (char)*(undefined2 *)(*(int *)(iStack_30 + 0x94) + 0x16),(char)sVar1);
      UpdatePCInfo__10CmdPCSceneFsP11CmdPCStatus(iStack_30,0,auStack_70);
      UpdateScene__18CmdEquipmentStatusFP12CmdEquipmentP11CmdPCStatus
                (iStack_48,iStack_30,auStack_70);
    }
  }
  return;
}

/* JP: 0x00450df0  CmdEquipmentGoods::~CmdEquipmentGoods()   [@24@__dt__17CmdEquipmentGoodsFv]  size=0x8 */
undefined4 * _24___dt__17CmdEquipmentGoodsFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -6;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-4] = &__vt__17CmdEquipmentGoods;
    *param_1 = 0x4080d4;
    param_1[3] = 0x4080e0;
    if (param_1[0x43] != 0) {
      __destroy_new_array(param_1[0x43],0x4502f0);
      param_1[0x43] = 0;
    }
    __dt__8FontDrawFv(param_1 + 0x33,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x27,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}

/* JP: 0x00450e00  CmdEquipmentGoods::~CmdEquipmentGoods()   [@36@__dt__17CmdEquipmentGoodsFv]  size=0x8 */
undefined4 * _36___dt__17CmdEquipmentGoodsFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -9;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-7] = &__vt__17CmdEquipmentGoods;
    param_1[-3] = 0x4080d4;
    *param_1 = 0x4080e0;
    if (param_1[0x40] != 0) {
      __destroy_new_array(param_1[0x40],0x4502f0);
      param_1[0x40] = 0;
    }
    __dt__8FontDrawFv(param_1 + 0x30,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x24,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}
