/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdTechniqueGoods   functions: 7
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdTechniqueGoods.md).
 */

/* JP: 0x004540d0  CmdTechniqueGoods::CmdTechniqueGoods()   [__ct__17CmdTechniqueGoodsFv]  size=0x74 */
int __ct__17CmdTechniqueGoodsFv(int param_1)

{
  __ct__9CmdWindowFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__17CmdTechniqueGoods;
  *(undefined4 *)(param_1 + 0x18) = 0x408214;
  *(undefined4 *)(param_1 + 0x24) = 0x408220;
  __ct__8FontDrawFv(param_1 + 0xb4);
  *(undefined4 *)(param_1 + 0xf4) = 0;
  return param_1;
}

/* JP: 0x00454150  CmdTechniqueGoods::~CmdTechniqueGoods()   [__dt__17CmdTechniqueGoodsFv]  size=0xd4 */
int __dt__17CmdTechniqueGoodsFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__17CmdTechniqueGoods;
    *(undefined4 *)(param_1 + 0x18) = 0x408214;
    *(undefined4 *)(param_1 + 0x24) = 0x408220;
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

/* JP: 0x00454230  CmdTechniqueGoods::CreateScene(MenuScene*, short, CmdPC*, PCSKILLParam*)   [CreateScene__17CmdTechniqueGoodsFP9MenuScenesP5CmdPCP12PCSKILLParam]  size=0x410 */
void CreateScene__17CmdTechniqueGoodsFP9MenuScenesP5CmdPCP12PCSKILLParam
               (int param_1,int param_2,short param_3,int *param_4,int param_5)

{
  undefined4 uVar1;
  undefined8 uVar2;
  int iVar3;
  short sVar4;
  short sVar5;
  undefined1 auStack_78 [12];
  float fStack_6c;
  undefined4 uStack_68;
  uint uStack_64;
  undefined4 uStack_60;
  float fStack_5c;
  uint uStack_58;
  ushort uStack_54;
  short sStack_52;
  int iStack_50;
  int iStack_40;
  short sStack_30;
  int *piStack_20;
  int iStack_10;
  
  uStack_64 = param_4[10];
  sStack_52 = (short)param_4[3];
  uStack_58 = uStack_64;
  iStack_50 = param_1;
  iStack_40 = param_2;
  sStack_30 = param_3;
  piStack_20 = param_4;
  iStack_10 = param_5;
  uVar2 = __nwa__FUi(param_3 * 0x150 + 0x10);
  uVar1 = __construct_new_array(uVar2,0x454640,0x450670,0x150,param_3);
  *(undefined4 *)(iStack_50 + 0xf4) = uVar1;
  iVar3 = *(int *)(iStack_50 + 0xf4);
  fStack_5c = 0.0;
  sVar5 = 0;
  for (sVar4 = 0; sVar4 < sStack_30; sVar4 = sVar4 + 1) {
    if ((uStack_58 & 1 << ((int)sVar4 & 0x1fU)) != 0) {
      SetData__9MenuSceneFUsP8MenuText(iStack_40,0,iVar3 + 0x50);
      uStack_60 = GetRegDat__9RegDatApiFiii(0xc,*(undefined1 *)(*piStack_20 + 2),sVar4);
      SetMessage__8MenuTextFPcUiUcUc(iVar3 + 0x50,uStack_60,*(byte *)(iVar3 + 0xa8) & 7,0,0);
      SetData__9MenuSceneFUsP8MenuText(iStack_40,1,iVar3 + 0xd0);
      sprintf(auStack_78,*(undefined4 *)(*(int *)(iStack_40 + 0x24) + 0x10),
                      *(undefined2 *)(iStack_10 + 0x1e));
      SetMessage__8MenuTextFPcUiUcUc(iVar3 + 0xd0,auStack_78,*(byte *)(iVar3 + 0x128) & 7,1,0);
      AddPlace__9MenuGroupFP9MenuPlace(iVar3,iVar3 + 0x50);
      AddPlace__9MenuGroupFP9MenuPlace(iVar3,iVar3 + 0xd0);
      SetData__9MenuSceneFUsP9MenuGroup(iStack_40,0,iVar3);
      *(short *)(iVar3 + 0x16) = sVar4;
      *(undefined2 *)(iVar3 + 0x1c) = 0;
      *(short *)(iVar3 + 0x1e) = sVar5;
      uStack_68 = *(undefined4 *)(iVar3 + 0x24);
      (**(code **)(*(int *)(iVar3 + 8) + 0x24))(uStack_68,fStack_5c);
      AddPlace__10MenuWindowFP9MenuPlace(iStack_50,iVar3);
      if (((*(byte *)(iStack_40 + 0x23) >> 6 != 0) &&
          (((ulong)*(byte *)(iStack_10 + 4) & 0x1f) >> 3 == 1)) ||
         (sStack_52 < *(short *)(iStack_10 + 0x1e))) {
        *(byte *)(iVar3 + 0x21) = *(byte *)(iVar3 + 0x21) & 0xf7;
        (**(code **)(*(int *)(iVar3 + 8) + 0x34))(0x3f000000);
      }
      fStack_6c = *(float *)(iVar3 + 0x30);
      fStack_5c = fStack_5c + fStack_6c;
      iVar3 = iVar3 + 0x150;
      sVar5 = sVar5 + 1;
    }
    iStack_10 = iStack_10 + 0x40;
  }
  SetData__9MenuSceneFUsP8FontDraw(iStack_40,0,iStack_50 + 0xb4);
  AddPriority__12MenuObjTableFP7MenuObj(iStack_50 + 0x18,iStack_50 + 0xb4);
  SetData__9MenuSceneFUsP10MenuWindow(iStack_40,0,iStack_50);
  *(int *)(*(int *)(iStack_50 + 0x40) + 0x38) = iStack_50 + 0xb4;
  SetScroll__10MenuWindowFss(iStack_50,0,0);
  uStack_54 = (ushort)*(byte *)(*piStack_20 + 2);
  *(ushort *)(iStack_50 + 0x16) = uStack_54;
  AddOT__7MenuObjFv(iStack_50);
  *(short *)(iStack_50 + 0xae) = sVar5;
  return;
}

/* JP: 0x00454690  CmdTechniqueGoods::UpdateScene(PCSKILLParam*, short, short)   [UpdateScene__17CmdTechniqueGoodsFP12PCSKILLParamss]  size=0x16c */
undefined4
UpdateScene__17CmdTechniqueGoodsFP12PCSKILLParamss
          (int param_1,int param_2,short param_3,short param_4)

{
  short sVar1;
  short sVar2;
  int iVar3;
  uint uVar4;
  undefined4 uVar5;
  
  sVar1 = *(short *)(param_1 + 0xae);
  iVar3 = *(int *)(param_1 + 0xf4);
  uVar5 = 1;
  for (uVar4 = *(uint *)(param_1 + 0xf4); uVar4 < (uint)(iVar3 + sVar1 * 0x150);
      uVar4 = uVar4 + 0x150) {
    sVar2 = *(short *)(uVar4 + 0x16);
    if (((long)((ulong)*(byte *)(uVar4 + 0x21) << 0x3c) < 0) &&
       (param_3 < *(short *)(param_2 + sVar2 * 0x40 + 0x1e))) {
      *(byte *)(uVar4 + 0x21) = *(byte *)(uVar4 + 0x21) & 0xf7;
      (**(code **)(*(int *)(uVar4 + 8) + 0x34))(0x3f000000);
      if (sVar2 == param_4) {
        uVar5 = 0;
      }
    }
  }
  return uVar5;
}

/* JP: 0x00454800  CmdTechniqueGoods::Select(CmdNote*, CmdElement*, PCSKILLParam*, MenuGroup*, MenuGroup*)   [Select__17CmdTechniqueGoodsFP7CmdNoteP10CmdElementP12PCSKILLParamP9MenuGroupP9MenuGroup]  size=0x1b0 */
void Select__17CmdTechniqueGoodsFP7CmdNoteP10CmdElementP12PCSKILLParamP9MenuGroupP9MenuGroup
               (int param_1,undefined4 param_2,undefined4 param_3,int param_4,int param_5,
               int param_6)

{
  undefined8 uVar1;
  int iVar2;
  
  if (param_6 != 0) {
    iVar2 = *(int *)(param_1 + 0xf4) + *(short *)(param_6 + 0x1e) * 0x150;
    SetCSA__8FontItemFUc(iVar2 + 0x50,0);
    SetCSA__8FontItemFUc(iVar2 + 0xd0,0);
  }
  if (param_5 != 0) {
    iVar2 = *(int *)(param_1 + 0xf4) + *(short *)(param_5 + 0x1e) * 0x150;
    SetCSA__8FontItemFUc(iVar2 + 0x50,1);
    SetCSA__8FontItemFUc(iVar2 + 0xd0,1);
    uVar1 = GetRegDat__9RegDatApiFiii(0x1d,*(undefined2 *)(param_1 + 0x16),*(undefined2 *)(param_5 + 0x16));
    SetExplanation__7CmdNoteFPCce(param_2,uVar1);
    Create__10CmdElementFUc(param_3,*(byte *)(param_4 + *(short *)(param_5 + 0x16) * 0x40 + 4) & 7);
  }
  return;
}

/* JP: 0x004549b0  CmdTechniqueGoods::~CmdTechniqueGoods()   [@24@__dt__17CmdTechniqueGoodsFv]  size=0x8 */
undefined4 * _24___dt__17CmdTechniqueGoodsFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -6;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-4] = &__vt__17CmdTechniqueGoods;
    *param_1 = 0x408214;
    param_1[3] = 0x408220;
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

/* JP: 0x004549c0  CmdTechniqueGoods::~CmdTechniqueGoods()   [@36@__dt__17CmdTechniqueGoodsFv]  size=0x8 */
undefined4 * _36___dt__17CmdTechniqueGoodsFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -9;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-7] = &__vt__17CmdTechniqueGoods;
    param_1[-3] = 0x408214;
    *param_1 = 0x408220;
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
