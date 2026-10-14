/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdFusionStatus   functions: 6
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdFusionStatus.md).
 */

/* JP: 0x0047c370  CmdFusionStatus::CmdFusionStatus()   [__ct__15CmdFusionStatusFv]  size=0xcc */
int __ct__15CmdFusionStatusFv(int param_1)

{
  __ct__9CmdWindowFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__15CmdFusionStatus;
  *(undefined4 *)(param_1 + 0x18) = 0x408d94;
  *(undefined4 *)(param_1 + 0x24) = 0x408da0;
  __ct__8FontDrawFv(param_1 + 0xb4);
  __ct__8FontDrawFv(param_1 + 0xf4);
  __construct_array(param_1 + 0x134,0x27bfd0,0x27c030,0x80,8);
  __construct_array(param_1 + 0x534,0x27bfd0,0x27c030,0x80,8);
  return param_1;
}

/* JP: 0x0047c440  CmdFusionStatus::~CmdFusionStatus()   [__dt__15CmdFusionStatusFv]  size=0xfc */
int __dt__15CmdFusionStatusFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__15CmdFusionStatus;
    *(undefined4 *)(param_1 + 0x18) = 0x408d94;
    *(undefined4 *)(param_1 + 0x24) = 0x408da0;
    __destroy_arr(param_1 + 0x534,0x27c030,0x80,8);
    __destroy_arr(param_1 + 0x134,0x27c030,0x80,8);
    __dt__8FontDrawFv(param_1 + 0xf4,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0xb4,0xffffffffffffffff);
    __dt__9CmdWindowFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x0047c540  CmdFusionStatus::CreateScene(CmdFusion*)   [CreateScene__15CmdFusionStatusFP9CmdFusion]  size=0x1a8 */
void CreateScene__15CmdFusionStatusFP9CmdFusion(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  
  SetData__9MenuSceneFUsP8FontDraw(param_2,3,param_1 + 0xb4);
  SetData__9MenuSceneFUsP8FontDraw(param_2,4,param_1 + 0xf4);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0xb4);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0xf4);
  iVar1 = param_1 + 0x134;
  uVar2 = 10;
  while( true ) {
    if (0x19 < (int)uVar2) break;
    SetData__9MenuSceneFUsP8MenuText(param_2,uVar2 & 0xffff,iVar1);
    AddPlace__10MenuWindowFP9MenuPlace(param_1,iVar1);
    if ((int)uVar2 < 0x12) {
      SetMessage__8MenuTextFPcUiUcUc(iVar1,*(undefined4 *)
                             ((uint)*(ushort *)(iVar1 + 0x22) * 8 + *(int *)(param_2 + 0x24) + 0x10)
                      ,*(byte *)(iVar1 + 0x58) & 7,0,1);
      OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(param_1 + 0xb4,iVar1,((ulong)*(byte *)(iVar1 + 0x58) & 0xf) >> 3,0);
    }
    uVar2 = uVar2 + 1;
    iVar1 = iVar1 + 0x80;
  }
  SetData__9MenuSceneFUsP10MenuWindow(param_2,2,param_1);
  AddOT__7MenuObjFv(param_1);
  return;
}

/* JP: 0x0047c6f0  CmdFusionStatus::UpdateScene(CmdFusion*)   [UpdateScene__15CmdFusionStatusFP9CmdFusion]  size=0x3ec */
void UpdateScene__15CmdFusionStatusFP9CmdFusion(int param_1,int param_2)

{
  short sVar1;
  char *pcVar2;
  uint uVar3;
  byte *pbVar4;
  undefined1 auStack_78 [8];
  undefined4 uStack_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  int iStack_5c;
  int iStack_58;
  int iStack_54;
  int iStack_50;
  int iStack_4c;
  int iStack_48;
  int iStack_44;
  int iStack_40;
  int iStack_3c;
  undefined4 uStack_38;
  int iStack_34;
  uint uStack_30;
  ushort uStack_2c;
  ushort uStack_2a;
  short sStack_28;
  ushort uStack_26;
  ushort uStack_24;
  undefined1 uStack_22;
  byte bStack_21;
  int iStack_20;
  int iStack_10;
  
  iStack_44 = *(int *)(*(int *)(param_2 + 0x58) + 0x5c);
  sStack_28 = *(short *)(param_2 + 0xbc);
  iStack_50 = *(int *)(*(int *)(param_2 + 0x58) + 0x70);
  iStack_58 = iStack_50 + 8;
  pbVar4 = (byte *)(iStack_50 + 0x1e);
  uStack_22 = *(undefined1 *)(*(int *)(iStack_44 + 4) + (int)sStack_28 + 0xd94);
  iStack_54 = iStack_58;
  iStack_4c = iStack_50;
  iStack_48 = iStack_50;
  iStack_40 = iStack_44;
  iStack_3c = iStack_44;
  iStack_34 = iStack_50;
  iStack_20 = param_1;
  iStack_10 = param_2;
  pcVar2 = (char *)GetRegDat__9RegDatApiFiii(0x2d,sStack_28,uStack_22);
  iStack_5c = *(int *)(iStack_10 + 0xb8);
  bStack_21 = (byte)(((ulong)*(byte *)(iStack_5c + 4) << 0x3a) >> 0x3d);
  ClearImage__8FontDrawFv(iStack_20 + 0xf4);
  uStack_30 = iStack_20 + 0x834;
  for (uVar3 = iStack_20 + 0x534; uVar3 < uStack_30; uVar3 = uVar3 + 0x80) {
    sVar1 = (ushort)*pbVar4 + (short)*pcVar2;
    if (99 < sVar1) {
      sVar1 = 99;
    }
    uStack_2a = *(ushort *)(uVar3 + 0x22);
    uStack_64 = *(undefined4 *)((uint)uStack_2a * 8 + *(int *)(iStack_10 + 0x24) + 0x10);
    uStack_60 = uStack_64;
    uStack_24 = uStack_2a;
    sprintf(auStack_78,uStack_64,sVar1);
    SetMessage__8MenuTextFPcUiUcUc(uVar3,auStack_78,*(byte *)(uVar3 + 0x58) & 7,0,1);
    OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_20 + 0xf4,uVar3,((ulong)*(byte *)(uVar3 + 0x58) & 0xf) >> 3,0);
    SetCSA__8FontItemFUc(uVar3,7);
    if (*pcVar2 < '\0') {
      SetCSA__8FontItemFUc(uVar3,9);
    }
    else if (*pcVar2 != '\0') {
      SetCSA__8FontItemFUc(uVar3,8);
    }
    pbVar4 = pbVar4 + 1;
    pcVar2 = pcVar2 + 1;
  }
  uStack_2c = *(ushort *)(uVar3 + 0x22);
  uStack_6c = *(undefined4 *)((uint)uStack_2c * 8 + *(int *)(iStack_10 + 0x24) + 0x10);
  uStack_68 = uStack_6c;
  uStack_26 = uStack_2c;
  sprintf(auStack_78,uStack_6c,*(undefined1 *)(*(int *)(iStack_10 + 0xb8) + 5));
  SetMessage__8MenuTextFPcUiUcUc(uVar3,auStack_78,*(byte *)(uVar3 + 0x58) & 7,0,1);
  OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_20 + 0xf4,uVar3,((ulong)*(byte *)(uVar3 + 0x58) & 0xf) >> 3,0);
  uStack_70 = *(undefined4 *)((bStack_21 + 0x13) * 8 + *(int *)(iStack_10 + 0x24) + 0x10);
  uStack_38 = uStack_70;
  SetMessage__8MenuTextFPcUiUcUc(uVar3 + 0x80,uStack_70,*(byte *)(uVar3 + 0xd8) & 7,0,1);
  OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_20 + 0xf4,uVar3 + 0x80,((ulong)*(byte *)(uVar3 + 0xd8) & 0xf) >> 3,0);
  return;
}

/* JP: 0x0047cae0  CmdFusionStatus::~CmdFusionStatus()   [@24@__dt__15CmdFusionStatusFv]  size=0x8 */
undefined4 * _24___dt__15CmdFusionStatusFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -6;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-4] = &__vt__15CmdFusionStatus;
    *param_1 = 0x408d94;
    param_1[3] = 0x408da0;
    __destroy_arr(param_1 + 0x147,0x27c030,0x80,8);
    __destroy_arr(param_1 + 0x47,0x27c030,0x80,8);
    __dt__8FontDrawFv(param_1 + 0x37,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x27,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}

/* JP: 0x0047caf0  CmdFusionStatus::~CmdFusionStatus()   [@36@__dt__15CmdFusionStatusFv]  size=0x8 */
undefined4 * _36___dt__15CmdFusionStatusFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -9;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-7] = &__vt__15CmdFusionStatus;
    param_1[-3] = 0x408d94;
    *param_1 = 0x408da0;
    __destroy_arr(param_1 + 0x144,0x27c030,0x80,8);
    __destroy_arr(param_1 + 0x44,0x27c030,0x80,8);
    __dt__8FontDrawFv(param_1 + 0x34,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x24,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}
