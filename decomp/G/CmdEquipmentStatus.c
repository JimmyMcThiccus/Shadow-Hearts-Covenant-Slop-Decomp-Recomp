/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdEquipmentStatus   functions: 6
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdEquipmentStatus.md).
 */

/* JP: 0x0048f350  CmdEquipmentStatus::CmdEquipmentStatus()   [__ct__18CmdEquipmentStatusFv]  size=0xa4 */
int __ct__18CmdEquipmentStatusFv(int param_1)

{
  __ct__9CmdWindowFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__18CmdEquipmentStatus;
  *(undefined4 *)(param_1 + 0x18) = 0x4092b4;
  *(undefined4 *)(param_1 + 0x24) = 0x4092c0;
  __ct__8FontDrawFv(param_1 + 0xb4);
  __ct__8FontDrawFv(param_1 + 0xf4);
  __construct_array(param_1 + 0x134,0x44ac40,0x44abc0,0x100,10);
  return param_1;
}

/* JP: 0x0048f400  CmdEquipmentStatus::~CmdEquipmentStatus()   [__dt__18CmdEquipmentStatusFv]  size=0xdc */
int __dt__18CmdEquipmentStatusFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__18CmdEquipmentStatus;
    *(undefined4 *)(param_1 + 0x18) = 0x4092b4;
    *(undefined4 *)(param_1 + 0x24) = 0x4092c0;
    __destroy_arr(param_1 + 0x134,0x44abc0,0x100,10);
    __dt__8FontDrawFv(param_1 + 0xf4,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0xb4,0xffffffffffffffff);
    __dt__9CmdWindowFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x0048f4e0  CmdEquipmentStatus::CreateScene(CmdEquipment*)   [CreateScene__18CmdEquipmentStatusFP12CmdEquipment]  size=0x338 */
void CreateScene__18CmdEquipmentStatusFP12CmdEquipment(int param_1,int param_2)

{
  short sVar1;
  ulong uVar2;
  int iVar3;
  short sVar4;
  short sVar5;
  float fVar6;
  undefined4 uStack_24;
  
  SetData__9MenuSceneFUsP8FontDraw(param_2,2,param_1 + 0xb4);
  SetData__9MenuSceneFUsP8FontDraw(param_2,3,param_1 + 0xf4);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0xb4);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0xf4);
  iVar3 = param_1 + 0x134;
  for (sVar4 = 0; sVar4 < 4; sVar4 = sVar4 + 1) {
    if (sVar4 < 2) {
      sVar1 = 3;
    }
    else {
      sVar1 = 2;
    }
    uStack_24 = 0.0;
    for (sVar5 = 0; sVar5 < sVar1; sVar5 = sVar5 + 1) {
      SetData__9MenuSceneFUsP8MenuText(param_2,sVar4 + 3,iVar3);
      (**(code **)(*(int *)(iVar3 + 8) + 0x24))
                (*(undefined4 *)(iVar3 + 0x24),uStack_24 + *(float *)(iVar3 + 0x28));
      SetMessage__8MenuTextFPcUiUcUc(iVar3,*(undefined4 *)
                             (((int)sVar5 + (int)*(short *)(iVar3 + 0x22) & 0xffffU) * 8 +
                              *(int *)(param_2 + 0x24) + 0x10),*(byte *)(iVar3 + 0x58) & 7,0,1);
      OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(param_1 + 0xb4,iVar3,((ulong)*(byte *)(iVar3 + 0x58) & 0xf) >> 3,0);
      SetData__9MenuSceneFUsP8MenuText(param_2,sVar4 + 7,iVar3 + 0x80);
      (**(code **)(*(int *)(iVar3 + 0x88) + 0x24))
                (*(undefined4 *)(iVar3 + 0xa4),*(undefined4 *)(iVar3 + 0x28));
      AddPlace__10MenuWindowFP9MenuPlace(param_1,iVar3);
      AddPlace__10MenuWindowFP9MenuPlace(param_1,iVar3 + 0x80);
      uVar2 = GetRealHeight__8FontItemCFv(iVar3);
      if ((long)uVar2 < 0) {
        fVar6 = (float)(uVar2 & 0xffffffff);
      }
      else {
        fVar6 = (float)(int)uVar2;
      }
      uStack_24 = uStack_24 + fVar6;
      iVar3 = iVar3 + 0x100;
    }
  }
  SetData__9MenuSceneFUsP10MenuWindow(param_2,2,param_1);
  AddOT__7MenuObjFv(param_1);
  return;
}

/* JP: 0x0048f820  CmdEquipmentStatus::UpdateScene(CmdEquipment*, CmdPCStatus*)   [UpdateScene__18CmdEquipmentStatusFP12CmdEquipmentP11CmdPCStatus]  size=0x2b0 */
void UpdateScene__18CmdEquipmentStatusFP12CmdEquipmentP11CmdPCStatus
               (int param_1,int param_2,int param_3)

{
  short sVar1;
  int iVar2;
  short sVar3;
  undefined2 *puVar4;
  undefined1 *puVar5;
  undefined1 auStack_48 [12];
  undefined4 uStack_3c;
  ushort uStack_36;
  ushort uStack_34;
  ushort uStack_32;
  int iStack_30;
  int iStack_20;
  int iStack_10;
  
  iStack_30 = param_1;
  iStack_20 = param_2;
  iStack_10 = param_3;
  ClearImage__8FontDrawFv(param_1 + 0xf4);
  iVar2 = iStack_30 + 0x134;
  puVar5 = (undefined1 *)(iStack_10 + 0x16);
  puVar4 = (undefined2 *)(iStack_10 + 0xe);
  sVar1 = 0x14;
  for (sVar3 = 0; sVar3 < 6; sVar3 = sVar3 + 1) {
    uStack_36 = *(ushort *)(iVar2 + 0xa2);
    uStack_3c = *(undefined4 *)((uint)uStack_36 * 8 + *(int *)(iStack_20 + 0x24) + 0x10);
    uStack_32 = uStack_36;
    sprintf(auStack_48,uStack_3c,*puVar5);
    SetMessage__8MenuTextFPcUiUcUc(iVar2 + 0x80,auStack_48,*(byte *)(iVar2 + 0xd8) & 7,0,1);
    OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_30 + 0xf4,iVar2 + 0x80,((ulong)*(byte *)(iVar2 + 0xd8) & 0xf) >> 3,0);
    SetCSA__8FontItemFUc(iVar2 + 0x80,(*(uint *)(iStack_10 + 0x1c) >> ((int)sVar1 & 0x1fU) & 3) + 7);
    iVar2 = iVar2 + 0x100;
    puVar5 = puVar5 + 1;
    sVar1 = sVar1 + 2;
  }
  sVar1 = 0xc;
  for (sVar3 = 0; sVar3 < 4; sVar3 = sVar3 + 1) {
    uStack_34 = *(ushort *)(iVar2 + 0xa2);
    sprintf(auStack_48,
                    *(undefined4 *)((uint)uStack_34 * 8 + *(int *)(iStack_20 + 0x24) + 0x10),*puVar4
                   );
    SetMessage__8MenuTextFPcUiUcUc(iVar2 + 0x80,auStack_48,*(byte *)(iVar2 + 0xd8) & 7,0,1);
    OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_30 + 0xf4,iVar2 + 0x80,((ulong)*(byte *)(iVar2 + 0xd8) & 0xf) >> 3,0);
    SetCSA__8FontItemFUc(iVar2 + 0x80,(*(uint *)(iStack_10 + 0x1c) >> ((int)sVar1 & 0x1fU) & 3) + 7);
    iVar2 = iVar2 + 0x100;
    puVar4 = puVar4 + 1;
    sVar1 = sVar1 + 2;
  }
  return;
}

/* JP: 0x0048fad0  CmdEquipmentStatus::~CmdEquipmentStatus()   [@24@__dt__18CmdEquipmentStatusFv]  size=0x8 */
undefined4 * _24___dt__18CmdEquipmentStatusFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -6;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-4] = &__vt__18CmdEquipmentStatus;
    *param_1 = 0x4092b4;
    param_1[3] = 0x4092c0;
    __destroy_arr(param_1 + 0x47,0x44abc0,0x100,10);
    __dt__8FontDrawFv(param_1 + 0x37,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x27,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}

/* JP: 0x0048fae0  CmdEquipmentStatus::~CmdEquipmentStatus()   [@36@__dt__18CmdEquipmentStatusFv]  size=0x8 */
undefined4 * _36___dt__18CmdEquipmentStatusFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -9;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-7] = &__vt__18CmdEquipmentStatus;
    param_1[-3] = 0x4092b4;
    *param_1 = 0x4092c0;
    __destroy_arr(param_1 + 0x44,0x44abc0,0x100,10);
    __dt__8FontDrawFv(param_1 + 0x34,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x24,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}
