/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdFusionSkillList   functions: 7
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdFusionSkillList.md).
 */

/* JP: 0x0047cb00  CmdFusionSkillList::CmdFusionSkillList()   [__ct__18CmdFusionSkillListFv]  size=0x94 */
int __ct__18CmdFusionSkillListFv(int param_1)

{
  __ct__9CmdWindowFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__18CmdFusionSkillList;
  *(undefined4 *)(param_1 + 0x18) = 0x408dd4;
  *(undefined4 *)(param_1 + 0x24) = 0x408de0;
  __ct__8FontDrawFv(param_1 + 0xb4);
  __construct_array(param_1 + 0xf4,0x454640,0x450670,0x150,7);
  return param_1;
}

/* JP: 0x0047cba0  CmdFusionSkillList::~CmdFusionSkillList()   [__dt__18CmdFusionSkillListFv]  size=0xc4 */
int __dt__18CmdFusionSkillListFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__18CmdFusionSkillList;
    *(undefined4 *)(param_1 + 0x18) = 0x408dd4;
    *(undefined4 *)(param_1 + 0x24) = 0x408de0;
    __destroy_arr(param_1 + 0xf4,0x450670,0x150,7);
    __dt__8FontDrawFv(param_1 + 0xb4,0xffffffffffffffff);
    __dt__9CmdWindowFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x0047cc70  CmdFusionSkillList::CreateScene(CmdFusion*)   [CreateScene__18CmdFusionSkillListFP9CmdFusion]  size=0x14c */
void CreateScene__18CmdFusionSkillListFP9CmdFusion(int param_1,undefined4 param_2)

{
  int iVar1;
  short sVar2;
  undefined4 uStack_24;
  
  iVar1 = param_1 + 0xf4;
  uStack_24 = 0.0;
  for (sVar2 = 0; sVar2 < 7; sVar2 = sVar2 + 1) {
    SetData__9MenuSceneFUsP8MenuText(param_2,0x1a,iVar1 + 0x50);
    SetData__9MenuSceneFUsP8MenuText(param_2,0x1b,iVar1 + 0xd0);
    AddPlace__9MenuGroupFP9MenuPlace(iVar1,iVar1 + 0x50);
    AddPlace__9MenuGroupFP9MenuPlace(iVar1,iVar1 + 0xd0);
    SetData__9MenuSceneFUsP9MenuGroup(param_2,1,iVar1);
    *(undefined2 *)(iVar1 + 0x1c) = 0;
    *(short *)(iVar1 + 0x1e) = sVar2;
    (**(code **)(*(int *)(iVar1 + 8) + 0x24))(*(undefined4 *)(iVar1 + 0x24),uStack_24);
    uStack_24 = uStack_24 + *(float *)(iVar1 + 0x30);
    iVar1 = iVar1 + 0x150;
  }
  SetData__9MenuSceneFUsP8FontDraw(param_2,5,param_1 + 0xb4);
  SetData__9MenuSceneFUsP10MenuWindow(param_2,2,param_1);
  AddOT__7MenuObjFv(param_1);
  return;
}

/* JP: 0x0047cdc0  CmdFusionSkillList::UpdateScene(CmdFusion*)   [UpdateScene__18CmdFusionSkillListFP9CmdFusion]  size=0x348 */
void UpdateScene__18CmdFusionSkillListFP9CmdFusion(int param_1,int param_2)

{
  undefined2 uVar1;
  int iVar2;
  short *psVar3;
  char *pcVar4;
  short sVar5;
  undefined1 auStack_58 [8];
  undefined4 uStack_50;
  undefined4 uStack_4c;
  int iStack_48;
  int iStack_44;
  int iStack_40;
  int iStack_3c;
  undefined4 uStack_38;
  int iStack_34;
  ushort uStack_2e;
  short sStack_2c;
  short sStack_2a;
  ushort uStack_28;
  short sStack_26;
  char cStack_23;
  char cStack_22;
  char cStack_21;
  int iStack_20;
  int iStack_10;
  
  uVar1 = *(undefined2 *)(*(int *)(param_2 + 0xac) + *(short *)(param_2 + 0xbc) * 0x54 + 0x4a);
  iStack_20 = param_1;
  iStack_10 = param_2;
  iStack_34 = GetRegDat__9RegDatApiFiii(0x36,uVar1,0);
  iStack_3c = *(int *)(iStack_10 + 0xb8);
  psVar3 = (short *)(iStack_3c + 8);
  pcVar4 = (char *)(iStack_3c + 0x16);
  sStack_2c = *(short *)(iStack_10 + 0xbc);
  iStack_48 = *(int *)(*(int *)(iStack_10 + 0x58) + 0x5c);
  cStack_23 = *(char *)(*(int *)(iStack_48 + 4) + (int)sStack_2c + 0xd94);
  cStack_21 = cStack_23 + '\x01';
  iStack_44 = iStack_48;
  iStack_40 = iStack_48;
  sStack_26 = sStack_2c;
  cStack_22 = cStack_23;
  ClearPlace__10MenuWindowFv(iStack_20);
  ClearImage__8FontDrawFv(iStack_20 + 0xb4);
  iVar2 = iStack_20 + 0xf4;
  for (sVar5 = 0; sVar5 < 7; sVar5 = sVar5 + 1) {
    if ((-1 < *psVar3) && (*pcVar4 <= cStack_21)) {
      uStack_38 = GetRegDat__9RegDatApiFiii(0xc,uVar1,*psVar3);
      SetMessage__8MenuTextFPcUiUcUc(iVar2 + 0x50,uStack_38,*(byte *)(iVar2 + 0xa8) & 7,0,1);
      OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_20 + 0xb4,iVar2 + 0x50,((ulong)*(byte *)(iVar2 + 0xa8) & 0xf) >> 3,0);
      uStack_2e = *(ushort *)(iVar2 + 0xf2);
      uStack_50 = *(undefined4 *)((uint)uStack_2e * 8 + *(int *)(iStack_10 + 0x24) + 0x10);
      uStack_4c = uStack_50;
      uStack_28 = uStack_2e;
      sprintf(auStack_58,uStack_50,*(undefined2 *)(iStack_34 + *psVar3 * 0x40 + 0x1e));
      SetMessage__8MenuTextFPcUiUcUc(iVar2 + 0xd0,auStack_58,*(byte *)(iVar2 + 0x128) & 7,0,1);
      OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_20 + 0xb4,iVar2 + 0xd0,((ulong)*(byte *)(iVar2 + 0x128) & 0xf) >> 3,0);
      sStack_2a = *psVar3;
      *(short *)(iVar2 + 0x16) = sStack_2a;
      *(undefined2 *)(iVar2 + 0x22) = uVar1;
      AddPlace__10MenuWindowFP9MenuPlace(iStack_20,iVar2);
      iVar2 = iVar2 + 0x150;
    }
    psVar3 = psVar3 + 1;
    pcVar4 = pcVar4 + 1;
  }
  AddPriority__12MenuObjTableFP7MenuObj(iStack_20 + 0x18,iStack_20 + 0xb4);
  return;
}

/* JP: 0x0047d110  CmdFusionSkillList::Select(CmdFusion*, MenuPlace*, MenuPlace*)   [Select__18CmdFusionSkillListFP9CmdFusionP9MenuPlaceP9MenuPlace]  size=0x19c */
void Select__18CmdFusionSkillListFP9CmdFusionP9MenuPlaceP9MenuPlace
               (int param_1,int param_2,int param_3,int param_4)

{
  undefined4 uVar1;
  int iVar2;
  undefined8 uVar3;
  
  if (param_4 != 0) {
    iVar2 = param_1 + *(short *)(param_4 + 0x1e) * 0x150;
    SetCSA__8FontItemFUc(iVar2 + 0x144,0);
    SetCSA__8FontItemFUc(iVar2 + 0x1c4,0);
  }
  if (param_3 != 0) {
    param_1 = param_1 + *(short *)(param_3 + 0x1e) * 0x150;
    SetCSA__8FontItemFUc(param_1 + 0x144,1);
    SetCSA__8FontItemFUc(param_1 + 0x1c4,1);
    uVar1 = *(undefined4 *)(*(int *)(param_2 + 0x58) + 100);
    uVar3 = GetRegDat__9RegDatApiFiii(0x1d,*(undefined2 *)(param_3 + 0x22),*(undefined2 *)(param_3 + 0x16));
    SetExplanation__7CmdNoteFPCce(uVar1,uVar3);
  }
  return;
}

/* JP: 0x0047d2b0  CmdFusionSkillList::~CmdFusionSkillList()   [@24@__dt__18CmdFusionSkillListFv]  size=0x8 */
undefined4 * _24___dt__18CmdFusionSkillListFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -6;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-4] = &__vt__18CmdFusionSkillList;
    *param_1 = 0x408dd4;
    param_1[3] = 0x408de0;
    __destroy_arr(param_1 + 0x37,0x450670,0x150,7);
    __dt__8FontDrawFv(param_1 + 0x27,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}

/* JP: 0x0047d2c0  CmdFusionSkillList::~CmdFusionSkillList()   [@36@__dt__18CmdFusionSkillListFv]  size=0x8 */
undefined4 * _36___dt__18CmdFusionSkillListFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -9;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-7] = &__vt__18CmdFusionSkillList;
    param_1[-3] = 0x408dd4;
    *param_1 = 0x408de0;
    __destroy_arr(param_1 + 0x34,0x450670,0x150,7);
    __dt__8FontDrawFv(param_1 + 0x24,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}
