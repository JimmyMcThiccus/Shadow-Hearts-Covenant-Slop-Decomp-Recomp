/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdAromaBaseOil   functions: 6
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdAromaBaseOil.md).
 */

/* JP: 0x00460580  CmdAromaBaseOil::CmdAromaBaseOil()   [__ct__15CmdAromaBaseOilFv]  size=0xf4 */
int __ct__15CmdAromaBaseOilFv(int param_1)

{
  __ct__9CmdWindowFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__15CmdAromaBaseOil;
  *(undefined4 *)(param_1 + 0x18) = 0x408734;
  *(undefined4 *)(param_1 + 0x24) = 0x408740;
  __ct__8FontDrawFv(param_1 + 0xb4);
  __ct__8FontDrawFv(param_1 + 0xf4);
  __ct__11SendOnLocalFv(param_1 + 0x134);
  __ct__11MenuTextureFv(param_1 + 0x168);
  __ct__11SendOnLocalFv(param_1 + 0x1a8);
  __ct__8MenuTextFv(param_1 + 0x1d8);
  __construct_array(param_1 + 600,0x266140,0x2661a0,0x60,3);
  *(undefined4 *)(param_1 + 0x378) = 0;
  return param_1;
}

/* JP: 0x00460680  CmdAromaBaseOil::~CmdAromaBaseOil()   [__dt__15CmdAromaBaseOilFv]  size=0x174 */
int __dt__15CmdAromaBaseOilFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__15CmdAromaBaseOil;
    *(undefined4 *)(param_1 + 0x18) = 0x408734;
    *(undefined4 *)(param_1 + 0x24) = 0x408740;
    if (*(int *)(param_1 + 0x378) != 0) {
      __destroy_new_array(*(undefined4 *)(param_1 + 0x378),0x44f7e0);
      *(undefined4 *)(param_1 + 0x378) = 0;
    }
    if (param_1 != -0x1d8) {
      __destroy_arr(param_1 + 600,0x2661a0,0x60,3);
      __dt__8MenuTextFv(param_1 + 0x1d8,0xffffffffffffffff);
    }
    __dt__11SendOnLocalFv(param_1 + 0x1a8,0xffffffffffffffff);
    __dt__11MenuTextureFv(param_1 + 0x168,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x134,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0xf4,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0xb4,0xffffffffffffffff);
    __dt__9CmdWindowFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x00460800  CmdAromaBaseOil::CreateScene(CmdAroma*)   [CreateScene__15CmdAromaBaseOilFP8CmdAroma]  size=0x62c */
void CreateScene__15CmdAromaBaseOilFP8CmdAroma(int param_1,int param_2)

{
  byte bVar1;
  undefined2 uVar2;
  short sVar3;
  undefined2 uVar4;
  undefined4 uVar5;
  undefined8 uVar6;
  ulong uVar7;
  short sVar8;
  int iVar9;
  float fVar10;
  undefined4 uStack_3c;
  
  sVar3 = *(short *)(param_2 + 0x518);
  uVar4 = *(undefined2 *)(*(int *)(param_2 + 0x51c) + 4);
  bVar1 = *(byte *)(*(int *)(*(int *)(*(int *)(param_2 + 0x58) + 0x5c) + 4) + 0xdae);
  SetData__9MenuSceneFUsP8FontDraw(param_2,0,param_1 + 0xb4);
  SetData__9MenuSceneFUsP8FontDraw(param_2,1,param_1 + 0xf4);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0xb4);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0xf4);
  SetData__9MenuSceneFUsP8MenuText(param_2,0,param_1 + 0x1d8);
  SetMessage__8MenuTextFPcUiUcUc(param_1 + 0x1d8,*(undefined4 *)(*(int *)(param_2 + 0x24) + 0x10),
                  *(byte *)(param_1 + 0x230) & 7,0,1);
  OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(param_1 + 0xb4,param_1 + 0x1d8,((ulong)*(byte *)(param_1 + 0x230) & 0xf) >> 3,0);
  AddPlace__10MenuWindowFP9MenuPlace(param_1,param_1 + 0x1d8);
  iVar9 = param_1 + 600;
  for (sVar8 = 0; sVar8 < 3; sVar8 = sVar8 + 1) {
    SetData__9MenuSceneFUsP10MenuSprite(param_2,sVar8,iVar9);
    AddPlace__10MenuWindowFP9MenuPlace(param_1,iVar9);
    iVar9 = iVar9 + 0x60;
  }
  uVar6 = __nwa__FUi((sVar3 * 0x12 + (int)sVar3) * 0x10 + 0x10);
  uVar5 = __construct_new_array(uVar6,0x44f870,0x44f7e0,0x130,sVar3);
  *(undefined4 *)(param_1 + 0x378) = uVar5;
  iVar9 = *(int *)(param_1 + 0x378);
  uStack_3c = 0.0;
  *(undefined2 *)(param_1 + 0xae) = 0;
  for (sVar8 = 0; sVar8 < sVar3; sVar8 = sVar8 + 1) {
    if (((uint)bVar1 & 1 << ((int)sVar8 & 0x1fU)) != 0) {
      SetData__9MenuSceneFUsP10MenuSprite(param_2,3,iVar9 + 0x50);
      SetIcon__10MenuCommonFcP10MenuSprite((char)uVar4,iVar9 + 0x50);
      AddPlace__9MenuGroupFP9MenuPlace(iVar9,iVar9 + 0x50);
      SetData__9MenuSceneFUsP8MenuText(param_2,1,iVar9 + 0xb0);
      uVar5 = GetRegDat__9RegDatApiFiii(0x10,sVar8,0xffffffffffffffff);
      SetMessage__8MenuTextFPcUiUcUc(iVar9 + 0xb0,uVar5,*(byte *)(iVar9 + 0x108) & 7,0,1);
      OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(param_1 + 0xf4,iVar9 + 0xb0,((ulong)*(byte *)(iVar9 + 0x108) & 0xf) >> 3,0);
      AddPlace__9MenuGroupFP9MenuPlace(iVar9,iVar9 + 0xb0);
      SetData__9MenuSceneFUsP9MenuGroup(param_2,0,iVar9);
      *(short *)(iVar9 + 0x16) = sVar8;
      uVar2 = *(undefined2 *)(param_1 + 0xae);
      *(undefined2 *)(iVar9 + 0x1c) = 0;
      *(undefined2 *)(iVar9 + 0x1e) = uVar2;
      (**(code **)(*(int *)(iVar9 + 8) + 0x24))
                (*(undefined4 *)(iVar9 + 0x24),uStack_3c + *(float *)(iVar9 + 0x28));
      AddPlace__10MenuWindowFP9MenuPlace(param_1,iVar9);
      uVar7 = GetRealHeight__8FontItemCFv(iVar9 + 0xb0);
      if ((long)uVar7 < 0) {
        fVar10 = (float)(uVar7 & 0xffffffff);
      }
      else {
        fVar10 = (float)(int)uVar7;
      }
      uStack_3c = uStack_3c + fVar10;
      iVar9 = iVar9 + 0x130;
      *(short *)(param_1 + 0xae) = *(short *)(param_1 + 0xae) + 1;
    }
  }
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(param_1 + 0x134,0x4216b0,uRam004216ac,1,0xffffffffffffffff);
  *(short *)(param_1 + 0x148) = *(short *)(*(int *)(param_1 + 0x378) + 100) + -1;
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0x134);
  Create__11MenuTextureFPUc6GS_PSMUii(param_1 + 0x168,*(undefined4 *)(*(int *)(*(int *)(param_2 + 0x58) + 0x54) + 0x10),
                  0x30,0,0);
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(param_1 + 0x1a8,param_1 + 0x180,*(undefined4 *)(param_1 + 0x17c),1,
                  0xffffffffffffffff);
  *(short *)(param_1 + 0x1bc) = *(short *)(param_1 + 0x26c) + -1;
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0x1a8);
  SetData__9MenuSceneFUsP10MenuWindow(param_2,0,param_1);
  AddOT__7MenuObjFv(param_1);
  return;
}

/* JP: 0x00460e30  CmdAromaBaseOil::Select(CmdAroma*, MenuGroup*, MenuGroup*)   [Select__15CmdAromaBaseOilFP8CmdAromaP9MenuGroupP9MenuGroup]  size=0xf4 */
void Select__15CmdAromaBaseOilFP8CmdAromaP9MenuGroupP9MenuGroup
               (undefined8 param_1,int param_2,int param_3,int param_4)

{
  undefined4 uVar1;
  undefined8 uVar2;
  
  if (param_4 != 0) {
    uVar2 = FindPlace__9MenuGroupFs(param_4,10);
    SetCSA__8FontItemFUc(uVar2,0);
  }
  if (param_3 != 0) {
    uVar2 = FindPlace__9MenuGroupFs(param_3,10);
    SetCSA__8FontItemFUc(uVar2,1);
    uVar1 = *(undefined4 *)(*(int *)(param_2 + 0x58) + 100);
    uVar2 = GetRegDat__9RegDatApiFiii(0x21,*(undefined2 *)(param_3 + 0x16),0xffffffffffffffff);
    SetExplanation__7CmdNoteFPCce(uVar1,uVar2);
  }
  return;
}

/* JP: 0x00460f30  CmdAromaBaseOil::~CmdAromaBaseOil()   [@24@__dt__15CmdAromaBaseOilFv]  size=0x8 */
undefined4 * _24___dt__15CmdAromaBaseOilFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -6;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-4] = &__vt__15CmdAromaBaseOil;
    *param_1 = 0x408734;
    param_1[3] = 0x408740;
    if (param_1[0xd8] != 0) {
      __destroy_new_array(param_1[0xd8],0x44f7e0);
      param_1[0xd8] = 0;
    }
    if (puVar1 != (undefined4 *)0xfffffe28) {
      __destroy_arr(param_1 + 0x90,0x2661a0,0x60,3);
      __dt__8MenuTextFv(param_1 + 0x70,0xffffffffffffffff);
    }
    __dt__11SendOnLocalFv(param_1 + 100,0xffffffffffffffff);
    __dt__11MenuTextureFv(param_1 + 0x54,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x47,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x37,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x27,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}

/* JP: 0x00460f40  CmdAromaBaseOil::~CmdAromaBaseOil()   [@36@__dt__15CmdAromaBaseOilFv]  size=0x8 */
undefined4 * _36___dt__15CmdAromaBaseOilFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -9;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-7] = &__vt__15CmdAromaBaseOil;
    param_1[-3] = 0x408734;
    *param_1 = 0x408740;
    if (param_1[0xd5] != 0) {
      __destroy_new_array(param_1[0xd5],0x44f7e0);
      param_1[0xd5] = 0;
    }
    if (puVar1 != (undefined4 *)0xfffffe28) {
      __destroy_arr(param_1 + 0x8d,0x2661a0,0x60,3);
      __dt__8MenuTextFv(param_1 + 0x6d,0xffffffffffffffff);
    }
    __dt__11SendOnLocalFv(param_1 + 0x61,0xffffffffffffffff);
    __dt__11MenuTextureFv(param_1 + 0x51,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x44,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x34,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x24,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}
