/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdComboKeyCharacter   functions: 7
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdComboKeyCharacter.md).
 */

/* JP: 0x004898b0  CmdComboKeyCharacter::CmdComboKeyCharacter()   [__ct__20CmdComboKeyCharacterFv]  size=0x74 */
int __ct__20CmdComboKeyCharacterFv(int param_1)

{
  __ct__9CmdWindowFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__20CmdComboKeyCharacter;
  *(undefined4 *)(param_1 + 0x18) = 0x4090f4;
  *(undefined4 *)(param_1 + 0x24) = 0x409100;
  __ct__8FontDrawFv(param_1 + 0xb4);
  *(undefined4 *)(param_1 + 0xf4) = 0;
  return param_1;
}

/* JP: 0x00489930  CmdComboKeyCharacter::~CmdComboKeyCharacter()   [__dt__20CmdComboKeyCharacterFv]  size=0xd4 */
int __dt__20CmdComboKeyCharacterFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__20CmdComboKeyCharacter;
    *(undefined4 *)(param_1 + 0x18) = 0x4090f4;
    *(undefined4 *)(param_1 + 0x24) = 0x409100;
    if (*(int *)(param_1 + 0xf4) != 0) {
      __destroy_new_array(*(undefined4 *)(param_1 + 0xf4),0x45b440);
    }
    __dt__8FontDrawFv(param_1 + 0xb4,0xffffffffffffffff);
    __dt__9CmdWindowFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x00489a10  CmdComboKeyCharacter::CreateScene(CmdComboKey*)   [CreateScene__20CmdComboKeyCharacterFP11CmdComboKey]  size=0x1ec */
void CreateScene__20CmdComboKeyCharacterFP11CmdComboKey(int param_1,int param_2)

{
  short sVar1;
  int iVar2;
  undefined8 uVar3;
  short sVar4;
  float fStack_24;
  
  sVar1 = *(short *)(param_2 + 0xcb4);
  uVar3 = __nwa__FUi((sVar1 * 0xc + (int)sVar1) * 0x10 + 0x10);
  iVar2 = __construct_new_array(uVar3,0x45b690,0x45b440,0xd0,sVar1);
  *(int *)(param_1 + 0xf4) = iVar2;
  SetData__9MenuSceneFUsP8FontDraw(param_2,2,param_1 + 0xb4);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0xb4);
  fStack_24 = 0.0;
  for (sVar4 = 0; sVar4 < sVar1; sVar4 = sVar4 + 1) {
    SetData__9MenuSceneFUsP8MenuText(param_2,3,iVar2 + 0x50);
    AddPlace__9MenuGroupFP9MenuPlace(iVar2,iVar2 + 0x50);
    SetData__9MenuSceneFUsP9MenuGroup(param_2,2,iVar2);
    *(undefined2 *)(iVar2 + 0x1c) = 0;
    *(short *)(iVar2 + 0x1e) = sVar4;
    (**(code **)(*(int *)(iVar2 + 8) + 0x24))(0,fStack_24);
    fStack_24 = fStack_24 + *(float *)(iVar2 + 0x30);
    iVar2 = iVar2 + 0xd0;
  }
  AddPlace__10MenuWindowFP9MenuPlace(param_1,*(int *)(param_1 + 0xf4) + 0xd0);
  SetData__9MenuSceneFUsP10MenuWindow(param_2,2,param_1);
  AddOT__7MenuObjFv(param_1);
  return;
}

/* JP: 0x00489c00  CmdComboKeyCharacter::UpdateScene(CmdComboKey*)   [UpdateScene__20CmdComboKeyCharacterFP11CmdComboKey]  size=0x23c */
void UpdateScene__20CmdComboKeyCharacterFP11CmdComboKey(int param_1,int param_2)

{
  byte bVar1;
  short sVar2;
  int *piVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  short sVar7;
  int iVar8;
  
  piVar3 = *(int **)(param_2 + 0x70);
  iVar6 = piVar3[1];
  iVar4 = piVar3[0xb];
  bVar1 = *(byte *)(iVar6 + 0x33);
  sVar7 = *(short *)(iVar6 + 0x34);
  sVar2 = *(short *)(iVar6 + 0x36);
  iVar6 = *(int *)(param_1 + 0xf4);
  ClearPlace__10MenuWindowFv(param_1);
  SetMessage__8MenuTextFPcUiUcUc(iVar6 + 0x50,*piVar3 + 10,*(byte *)(iVar6 + 0xa8) & 7,0,0);
  *(ushort *)(iVar6 + 0x16) = (ushort)*(byte *)(*piVar3 + 2);
  AddPlace__10MenuWindowFP9MenuPlace(param_1,iVar6);
  iVar6 = iVar6 + 0xd0;
  iVar8 = *(int *)(param_2 + 0xcac) + sVar7 * 0xc;
  for (; sVar7 < sVar2; sVar7 = sVar7 + 1) {
    if ((iVar4 << (bVar1 & 0x1f) & 1 << ((int)sVar7 & 0x1fU)) != 0) {
      uVar5 = GetRegDat__9RegDatApiFiii(*(undefined2 *)(iVar8 + 4),*(undefined2 *)(iVar8 + 8),
                              0xffffffffffffffff);
      SetMessage__8MenuTextFPcUiUcUc(iVar6 + 0x50,uVar5,*(byte *)(iVar6 + 0xa8) & 7,0,0);
      *(short *)(iVar6 + 0x16) = sVar7;
      AddPlace__10MenuWindowFP9MenuPlace(param_1,iVar6);
      iVar6 = iVar6 + 0xd0;
    }
    iVar8 = iVar8 + 0xc;
  }
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0xb4);
  *(int *)(*(int *)(param_1 + 0x40) + 0x38) = param_1 + 0xb4;
  SetScroll__10MenuWindowFss(param_1,0,0);
  return;
}

/* JP: 0x00489e40  CmdComboKeyCharacter::Select(CmdComboKey*, MenuPlace*, MenuPlace*)   [Select__20CmdComboKeyCharacterFP11CmdComboKeyP9MenuPlaceP9MenuPlace]  size=0x130 */
void Select__20CmdComboKeyCharacterFP11CmdComboKeyP9MenuPlaceP9MenuPlace
               (int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  
  if (param_4 != 0) {
    SetCSA__8FontItemFUc(*(int *)(param_1 + 0xf4) +
                    (*(short *)(param_4 + 0x1e) * 0xc + (int)*(short *)(param_4 + 0x1e)) * 0x10 +
                    0x50,0);
  }
  if (param_3 != 0) {
    iVar1 = *(int *)(param_1 + 0xf4) +
            (*(short *)(param_3 + 0x1e) * 0xc + (int)*(short *)(param_3 + 0x1e)) * 0x10;
    SetCSA__8FontItemFUc(iVar1 + 0x50,1);
    SetExplanation__7CmdNoteFPCce
              (*(undefined4 *)(param_2 + 100),*(undefined4 *)(*(int *)(param_2 + 0x28) + 0x5c),
               *(undefined4 *)(iVar1 + 0xb0));
  }
  return;
}

/* JP: 0x00489f70  CmdComboKeyCharacter::~CmdComboKeyCharacter()   [@24@__dt__20CmdComboKeyCharacterFv]  size=0x8 */
undefined4 * _24___dt__20CmdComboKeyCharacterFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -6;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-4] = &__vt__20CmdComboKeyCharacter;
    *param_1 = 0x4090f4;
    param_1[3] = 0x409100;
    if (param_1[0x37] != 0) {
      __destroy_new_array(param_1[0x37],0x45b440);
    }
    __dt__8FontDrawFv(param_1 + 0x27,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}

/* JP: 0x00489f80  CmdComboKeyCharacter::~CmdComboKeyCharacter()   [@36@__dt__20CmdComboKeyCharacterFv]  size=0x8 */
undefined4 * _36___dt__20CmdComboKeyCharacterFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -9;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-7] = &__vt__20CmdComboKeyCharacter;
    param_1[-3] = 0x4090f4;
    *param_1 = 0x409100;
    if (param_1[0x34] != 0) {
      __destroy_new_array(param_1[0x34],0x45b440);
    }
    __dt__8FontDrawFv(param_1 + 0x24,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}
