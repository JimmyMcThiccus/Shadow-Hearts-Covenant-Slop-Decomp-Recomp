/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdFusionList   functions: 8
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdFusionList.md).
 */

/* JP: 0x004735b0  CmdFusionList::CmdFusionList()   [__ct__13CmdFusionListFv]  size=0x84 */
int __ct__13CmdFusionListFv(int param_1)

{
  __ct__9CmdWindowFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__13CmdFusionList;
  *(undefined4 *)(param_1 + 0x18) = 0x408a34;
  *(undefined4 *)(param_1 + 0x24) = 0x408a40;
  __ct__8FontDrawFv(param_1 + 0xb4);
  *(undefined4 *)(param_1 + 0xf4) = 0;
  __ct__6CursorFv(param_1 + 0xf8);
  return param_1;
}

/* JP: 0x00473640  CmdFusionList::~CmdFusionList()   [__dt__13CmdFusionListFv]  size=0xe4 */
int __dt__13CmdFusionListFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__13CmdFusionList;
    *(undefined4 *)(param_1 + 0x18) = 0x408a34;
    *(undefined4 *)(param_1 + 0x24) = 0x408a40;
    if (*(int *)(param_1 + 0xf4) != 0) {
      __destroy_new_array(*(undefined4 *)(param_1 + 0xf4),0x473730);
    }
    __dt__6CursorFv(param_1 + 0xf8,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0xb4,0xffffffffffffffff);
    __dt__9CmdWindowFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x004737d0  CmdFusionList::CreateScene(CmdFusion*)   [CreateScene__13CmdFusionListFP9CmdFusion]  size=0x21c */
void CreateScene__13CmdFusionListFP9CmdFusion(int param_1,int param_2)

{
  short sVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  int iVar4;
  short sVar5;
  undefined4 uStack_24;
  
  sVar1 = *(short *)(param_2 + 0xaa);
  uVar3 = __nwa__FUi((sVar1 * 0x1c + (int)sVar1) * 0x10 + 0x10);
  uVar2 = __construct_new_array(uVar3,0x4739f0,0x473730,0x1d0,sVar1);
  *(undefined4 *)(param_1 + 0xf4) = uVar2;
  iVar4 = *(int *)(param_1 + 0xf4);
  uStack_24 = 0.0;
  for (sVar5 = 0; sVar5 < sVar1; sVar5 = sVar5 + 1) {
    SetData__9MenuSceneFUsP8MenuText(param_2,0,iVar4 + 0x50);
    SetData__9MenuSceneFUsP8MenuText(param_2,1,iVar4 + 0xd0);
    SetData__9MenuSceneFUsP8MenuText(param_2,2,iVar4 + 0x150);
    AddPlace__9MenuGroupFP9MenuPlace(iVar4,iVar4 + 0x50);
    AddPlace__9MenuGroupFP9MenuPlace(iVar4,iVar4 + 0xd0);
    AddPlace__9MenuGroupFP9MenuPlace(iVar4,iVar4 + 0x150);
    SetData__9MenuSceneFUsP9MenuGroup(param_2,0,iVar4);
    *(undefined2 *)(iVar4 + 0x1c) = 0;
    *(short *)(iVar4 + 0x1e) = sVar5;
    (**(code **)(*(int *)(iVar4 + 8) + 0x24))(0,uStack_24);
    uStack_24 = uStack_24 + *(float *)(iVar4 + 0x30);
    iVar4 = iVar4 + 0x1d0;
  }
  SetData__9MenuSceneFUsP8FontDraw(param_2,0,param_1 + 0xb4);
  AddPlace__10MenuWindowFP9MenuPlace(param_1,*(int *)(param_1 + 0xf4) + 0x1d0);
  SetData__9MenuSceneFUsP10MenuWindow(param_2,0,param_1);
  AddOT__7MenuObjFv(param_1);
  return;
}

/* JP: 0x00473a50  CmdFusionList::UpdateScene(CmdFusion*)   [UpdateScene__13CmdFusionListFP9CmdFusion]  size=0x2fc */
void UpdateScene__13CmdFusionListFP9CmdFusion(int param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  short sVar4;
  short sVar5;
  int iVar6;
  undefined1 auStack_60 [12];
  undefined4 uStack_54;
  undefined4 uStack_50;
  int iStack_4c;
  int iStack_48;
  int iStack_44;
  int iStack_40;
  uint uStack_3c;
  int iStack_38;
  int iStack_34;
  int iStack_30;
  undefined4 uStack_2c;
  short sStack_26;
  short sStack_24;
  byte bStack_22;
  byte bStack_21;
  int iStack_20;
  int iStack_10;
  
  iStack_38 = *(int *)(*(int *)(param_2 + 0x58) + 0x70);
  uVar1 = *(uint *)(iStack_38 + 0x2c);
  sStack_26 = *(short *)(param_2 + 0xa8);
  iVar6 = *(int *)(param_2 + 0xac);
  iStack_40 = iVar6;
  uStack_3c = uVar1;
  iStack_34 = iStack_38;
  iStack_30 = iStack_38;
  sStack_24 = sStack_26;
  iStack_20 = param_1;
  iStack_10 = param_2;
  ClearPlace__10MenuWindowFv(param_1);
  iVar3 = *(int *)(iStack_20 + 0xf4);
  sVar5 = 0;
  for (sVar4 = 0; sVar4 < sStack_24; sVar4 = sVar4 + 1) {
    if ((uVar1 & 1 << ((int)sVar4 & 0x1fU)) != 0) {
      uStack_2c = GetRegDat__9RegDatApiFiii(4,sVar4,0xffffffffffffffff);
      SetMessage__8MenuTextFPcUiUcUc(iVar3 + 0x50,uStack_2c,*(byte *)(iVar3 + 0xa8) & 7,0,0);
      iStack_4c = *(int *)(*(int *)(iStack_10 + 0x58) + 0x5c);
      bStack_22 = *(byte *)(*(int *)(iStack_4c + 4) + (int)sVar4 + 0xd94);
      uStack_50 = *(undefined4 *)(*(int *)(iStack_10 + 0x24) + 0x28);
      iStack_48 = iStack_4c;
      iStack_44 = iStack_4c;
      bStack_21 = bStack_22;
      sprintf(auStack_60,uStack_50,bStack_22 + 1);
      SetMessage__8MenuTextFPcUiUcUc(iVar3 + 0xd0,auStack_60,*(byte *)(iVar3 + 0x128) & 7,1,0);
      uStack_54 = *(undefined4 *)(*(int *)(iStack_10 + 0x24) + 0x30);
      iVar2 = GetRegDat__9RegDatApiFiii(0x2c,sVar4,0xffffffffffffffff);
      sprintf(auStack_60,uStack_54,*(undefined1 *)(iVar2 + 5));
      SetMessage__8MenuTextFPcUiUcUc(iVar3 + 0x150,auStack_60,*(byte *)(iVar3 + 0x1a8) & 7,1,0);
      *(short *)(iVar3 + 0x16) = sVar4;
      *(short *)(iVar3 + 0x22) = sVar5;
      if ((uVar1 & *(uint *)(iVar6 + 0x4c)) != 0) {
        *(byte *)(iVar3 + 0x21) = *(byte *)(iVar3 + 0x21) & 0xf7;
      }
      AddPlace__10MenuWindowFP9MenuPlace(iStack_20,iVar3);
      sVar5 = sVar5 + 1;
      iVar3 = iVar3 + 0x1d0;
    }
    iVar6 = iVar6 + 0x54;
  }
  *(short *)(iStack_20 + 0xae) = sVar5;
  AddPriority__12MenuObjTableFP7MenuObj(iStack_20 + 0x18,iStack_20 + 0xb4);
  *(int *)(*(int *)(iStack_20 + 0x40) + 0x38) = iStack_20 + 0xb4;
  SetScroll__10MenuWindowFss(iStack_20,0,0);
  return;
}

/* JP: 0x00473d50  CmdFusionList::Select(CmdFusion*, MenuGroup*, MenuGroup*, int)   [Select__13CmdFusionListFP9CmdFusionP9MenuGroupP9MenuGroupi]  size=0x1d4 */
void Select__13CmdFusionListFP9CmdFusionP9MenuGroupP9MenuGroupi
               (int param_1,int param_2,int param_3,int param_4,int param_5)

{
  undefined2 uVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  int iVar4;
  
  if (param_4 != 0) {
    iVar4 = *(int *)(param_1 + 0xf4) +
            (*(short *)(param_4 + 0x22) * 0x1c + (int)*(short *)(param_4 + 0x22)) * 0x10;
    SetCSA__8FontItemFUc(iVar4 + 0x50,0);
    SetCSA__8FontItemFUc(iVar4 + 0xd0,0);
    SetCSA__8FontItemFUc(iVar4 + 0x150,0);
  }
  if (param_3 != 0) {
    uVar1 = *(undefined2 *)(param_3 + 0x16);
    iVar4 = *(int *)(param_1 + 0xf4) +
            (*(short *)(param_3 + 0x22) * 0x1c + (int)*(short *)(param_3 + 0x22)) * 0x10;
    SetCSA__8FontItemFUc(iVar4 + 0x50,1);
    SetCSA__8FontItemFUc(iVar4 + 0xd0,1);
    SetCSA__8FontItemFUc(iVar4 + 0x150,1);
    SetFusionMonster__9CmdFusionFs(param_2,uVar1);
    if (param_5 != 0) {
      uVar2 = *(undefined4 *)(*(int *)(param_2 + 0x58) + 100);
      uVar3 = GetRegDat__9RegDatApiFiii(0x16,uVar1,0xffffffffffffffff);
      SetExplanation__7CmdNoteFPCce(uVar2,uVar3);
    }
  }
  return;
}

/* JP: 0x00473f30  CmdFusionList::MoveCursor(int, short)   [MoveCursor__13CmdFusionListFis]  size=0x68 */
undefined8 MoveCursor__13CmdFusionListFis(int param_1,undefined4 param_2,short param_3)

{
  undefined8 uVar1;
  
  do {
    uVar1 = MoveCursor__6CursorFi(param_1 + 0xf8,param_2);
    if (param_3 == 0) {
      return uVar1;
    }
  } while (-1 < (long)((ulong)*(byte *)((int)uVar1 + 0x21) << 0x3c));
  return uVar1;
}

/* JP: 0x00473fa0  CmdFusionList::~CmdFusionList()   [@24@__dt__13CmdFusionListFv]  size=0x8 */
undefined4 * _24___dt__13CmdFusionListFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -6;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-4] = &__vt__13CmdFusionList;
    *param_1 = 0x408a34;
    param_1[3] = 0x408a40;
    if (param_1[0x37] != 0) {
      __destroy_new_array(param_1[0x37],0x473730);
    }
    __dt__6CursorFv(param_1 + 0x38,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x27,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}

/* JP: 0x00473fb0  CmdFusionList::~CmdFusionList()   [@36@__dt__13CmdFusionListFv]  size=0x8 */
undefined4 * _36___dt__13CmdFusionListFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -9;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-7] = &__vt__13CmdFusionList;
    param_1[-3] = 0x408a34;
    *param_1 = 0x408a40;
    if (param_1[0x34] != 0) {
      __destroy_new_array(param_1[0x34],0x473730);
    }
    __dt__6CursorFv(param_1 + 0x35,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x24,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}
