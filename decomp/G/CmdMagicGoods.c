/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdMagicGoods   functions: 7
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdMagicGoods.md).
 */

/* JP: 0x0048e9e0  CmdMagicGoods::CmdMagicGoods()   [__ct__13CmdMagicGoodsFv]  size=0x74 */
int __ct__13CmdMagicGoodsFv(int param_1)

{
  __ct__9CmdWindowFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__13CmdMagicGoods;
  *(undefined4 *)(param_1 + 0x18) = 0x409274;
  *(undefined4 *)(param_1 + 0x24) = 0x409280;
  __ct__8FontDrawFv(param_1 + 0xb4);
  *(undefined4 *)(param_1 + 0xf4) = 0;
  return param_1;
}

/* JP: 0x0048ea60  CmdMagicGoods::~CmdMagicGoods()   [__dt__13CmdMagicGoodsFv]  size=0xd4 */
int __dt__13CmdMagicGoodsFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__13CmdMagicGoods;
    *(undefined4 *)(param_1 + 0x18) = 0x409274;
    *(undefined4 *)(param_1 + 0x24) = 0x409280;
    if (*(int *)(param_1 + 0xf4) != 0) {
      __destroy_new_array(*(undefined4 *)(param_1 + 0xf4),0x450670);
    }
    __dt__8FontDrawFv(param_1 + 0xb4,0xffffffffffffffff);
    __dt__9CmdWindowFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x0048eb40  CmdMagicGoods::CreateScene(CmdMagic*)   [CreateScene__13CmdMagicGoodsFP8CmdMagic]  size=0x1fc */
void CreateScene__13CmdMagicGoodsFP8CmdMagic(int param_1,int param_2)

{
  short sVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  int iVar4;
  short sVar5;
  undefined4 uStack_24;
  
  sVar1 = *(short *)(param_2 + 0x362);
  uVar3 = __nwa__FUi(sVar1 * 0x150 + 0x10);
  uVar2 = __construct_new_array(uVar3,0x454640,0x450670,0x150,sVar1);
  *(undefined4 *)(param_1 + 0xf4) = uVar2;
  iVar4 = *(int *)(param_1 + 0xf4);
  uStack_24 = 0.0;
  for (sVar5 = 0; sVar5 < sVar1; sVar5 = sVar5 + 1) {
    SetData__9MenuSceneFUsP8MenuText(param_2,0,iVar4 + 0x50);
    SetData__9MenuSceneFUsP8MenuText(param_2,1,iVar4 + 0xd0);
    AddPlace__9MenuGroupFP9MenuPlace(iVar4,iVar4 + 0x50);
    AddPlace__9MenuGroupFP9MenuPlace(iVar4,iVar4 + 0xd0);
    SetData__9MenuSceneFUsP9MenuGroup(param_2,0,iVar4);
    *(undefined2 *)(iVar4 + 0x1c) = 0;
    *(short *)(iVar4 + 0x1e) = sVar5;
    (**(code **)(*(int *)(iVar4 + 8) + 0x24))(0,uStack_24);
    uStack_24 = uStack_24 + *(float *)(iVar4 + 0x30);
    iVar4 = iVar4 + 0x150;
  }
  SetData__9MenuSceneFUsP8FontDraw(param_2,0,param_1 + 0xb4);
  AddPlace__10MenuWindowFP9MenuPlace(param_1,*(int *)(param_1 + 0xf4) + 0x150);
  SetData__9MenuSceneFUsP10MenuWindow(param_2,0,param_1);
  *(undefined2 *)(param_1 + 0x16) = 0;
  AddOT__7MenuObjFv(param_1);
  return;
}

/* JP: 0x0048ed40  CmdMagicGoods::UpdateScene(CmdMagic*, char*)   [UpdateScene__13CmdMagicGoodsFP8CmdMagicPc]  size=0x41c */
void UpdateScene__13CmdMagicGoodsFP8CmdMagicPc(int param_1,int param_2,int param_3)

{
  short sVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  short sVar6;
  short sVar7;
  undefined1 auStack_60 [8];
  undefined4 uStack_58;
  int iStack_54;
  int iStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  int iStack_44;
  short sStack_3e;
  short sStack_3c;
  short sStack_3a;
  ushort uStack_38;
  short sStack_36;
  short sStack_34;
  byte bStack_32;
  byte bStack_31;
  int iStack_30;
  int iStack_20;
  int iStack_10;
  
  uStack_4c = *(undefined4 *)(param_2 + 0x5c);
  bStack_32 = *(byte *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x28e);
  uStack_38 = (ushort)bStack_32;
  sStack_3a = *(short *)(param_2 + 0x360);
  iVar5 = *(int *)(param_2 + 0x35c);
  iVar4 = *(int *)(param_1 + 0xf4);
  iStack_54 = *(int *)(param_2 + 0x70);
  sStack_3e = *(short *)(iStack_54 + 0xc);
  iStack_50 = iVar5;
  sStack_3c = sStack_3e;
  sStack_36 = sStack_3e;
  sStack_34 = sStack_3a;
  bStack_31 = bStack_32;
  iStack_30 = param_1;
  iStack_20 = param_2;
  iStack_10 = param_3;
  ClearPlace__10MenuWindowFv(param_1);
  iVar3 = *(int *)(iStack_30 + 0xf4);
  iStack_44 = iVar3 + 0xd0;
  *(byte *)(iVar3 + 0xe2) = *(byte *)(iVar3 + 0xe2) & 0xfe | 1;
  sVar6 = 0;
  for (sVar7 = 0; sVar7 < sStack_34; sVar7 = sVar7 + 1) {
    sVar1 = *(short *)(iVar5 + (short)uStack_38 * 2 + 0xc);
    if ((-1 < sVar1) && (*(char *)(iStack_10 + sVar1) != '\0')) {
      iVar3 = GetRegDat__9RegDatApiFiii(0x38,sVar1,0xffffffffffffffff);
      if (-1 < (long)((ulong)*(byte *)(iVar4 + 0x21) << 0x3c)) {
        (**(code **)(*(int *)(iVar4 + 8) + 0x34))(0x40000000);
        *(byte *)(iVar4 + 0x21) = *(byte *)(iVar4 + 0x21) & 0xf7 | 8;
      }
      SetCSA__8FontItemFUc(iVar4 + 0x50,0);
      SetCSA__8FontItemFUc(iVar4 + 0xd0,0);
      sVar2 = *(short *)(iVar3 + 0x1e) / (short)*(char *)(iStack_10 + sVar1);
      if (*(char *)(iStack_10 + sVar1) == '\0') {
        trap(7);
      }
      if (sVar2 < 1) {
        sVar2 = 1;
      }
      if ((((ulong)*(byte *)(iVar3 + 4) & 0x1f) >> 3 == 1) || (sStack_36 < sVar2)) {
        (**(code **)(*(int *)(iVar4 + 8) + 0x34))(0x3f000000);
        *(byte *)(iVar4 + 0x21) = *(byte *)(iVar4 + 0x21) & 0xf7;
      }
      uStack_48 = GetRegDat__9RegDatApiFiii(0xe,sVar1,0xffffffffffffffff);
      SetMessage__8MenuTextFPcUiUcUc(iVar4 + 0x50,uStack_48,*(byte *)(iVar4 + 0xa8) & 7,0,0);
      uStack_58 = *(undefined4 *)(*(int *)(iStack_20 + 0x24) + 0x10);
      sprintf(auStack_60,uStack_58,sVar2);
      SetMessage__8MenuTextFPcUiUcUc(iVar4 + 0xd0,auStack_60,*(byte *)(iVar4 + 0x128) & 7,1,0);
      *(short *)(iVar4 + 0x16) = sVar1;
      *(short *)(iVar4 + 0x22) = sVar2;
      AddPlace__10MenuWindowFP9MenuPlace(iStack_30,iVar4);
      iVar4 = iVar4 + 0x150;
      sVar6 = sVar6 + 1;
    }
    iVar5 = iVar5 + 0x14;
  }
  AddPriority__12MenuObjTableFP7MenuObj(iStack_30 + 0x18,iStack_30 + 0xb4);
  *(int *)(*(int *)(iStack_30 + 0x40) + 0x38) = iStack_30 + 0xb4;
  SetScroll__10MenuWindowFss(iStack_30,0,0);
  *(short *)(iStack_30 + 0xae) = sVar6;
  return;
}

/* JP: 0x0048f160  CmdMagicGoods::Select(CmdMagic*, MenuGroup*, MenuGroup*, short)   [Select__13CmdMagicGoodsFP8CmdMagicP9MenuGroupP9MenuGroups]  size=0x1c8 */
void Select__13CmdMagicGoodsFP8CmdMagicP9MenuGroupP9MenuGroups
               (int param_1,int param_2,int param_3,int param_4,short param_5)

{
  undefined2 uVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  int iVar4;
  int iVar5;
  
  if (param_4 != 0) {
    iVar4 = *(int *)(param_1 + 0xf4) + *(short *)(param_4 + 0x1e) * 0x150;
    SetCSA__8FontItemFUc(iVar4 + 0x50,0);
    SetCSA__8FontItemFUc(iVar4 + 0xd0,0);
  }
  if (param_3 != 0) {
    uVar1 = *(undefined2 *)(param_3 + 0x16);
    iVar4 = GetRegDat__9RegDatApiFiii(0x38,uVar1,0xffffffffffffffff);
    iVar5 = *(int *)(param_1 + 0xf4) + *(short *)(param_3 + 0x1e) * 0x150;
    SetCSA__8FontItemFUc(iVar5 + 0x50,1);
    SetCSA__8FontItemFUc(iVar5 + 0xd0,1);
    if (param_5 != 0) {
      uVar2 = *(undefined4 *)(param_2 + 100);
      uVar3 = GetRegDat__9RegDatApiFiii(0x1f,uVar1,0xffffffffffffffff);
      SetExplanation__7CmdNoteFPCce(uVar2,uVar3);
    }
    Create__10CmdElementFUc(*(undefined4 *)(param_2 + 0x6c),*(byte *)(iVar4 + 4) & 7);
  }
  return;
}

/* JP: 0x0048f330  CmdMagicGoods::~CmdMagicGoods()   [@24@__dt__13CmdMagicGoodsFv]  size=0x8 */
undefined4 * _24___dt__13CmdMagicGoodsFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -6;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-4] = &__vt__13CmdMagicGoods;
    *param_1 = 0x409274;
    param_1[3] = 0x409280;
    if (param_1[0x37] != 0) {
      __destroy_new_array(param_1[0x37],0x450670);
    }
    __dt__8FontDrawFv(param_1 + 0x27,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}

/* JP: 0x0048f340  CmdMagicGoods::~CmdMagicGoods()   [@36@__dt__13CmdMagicGoodsFv]  size=0x8 */
undefined4 * _36___dt__13CmdMagicGoodsFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -9;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-7] = &__vt__13CmdMagicGoods;
    param_1[-3] = 0x409274;
    *param_1 = 0x409280;
    if (param_1[0x34] != 0) {
      __destroy_new_array(param_1[0x34],0x450670);
    }
    __dt__8FontDrawFv(param_1 + 0x24,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}
