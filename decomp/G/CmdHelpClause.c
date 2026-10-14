/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdHelpClause   functions: 7
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdHelpClause.md).
 */

/* JP: 0x0045b2e0  CmdHelpClause::CmdHelpClause()   [__ct__13CmdHelpClauseFv]  size=0x74 */
int __ct__13CmdHelpClauseFv(int param_1)

{
  __ct__9CmdWindowFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__13CmdHelpClause;
  *(undefined4 *)(param_1 + 0x18) = 0x408584;
  *(undefined4 *)(param_1 + 0x24) = 0x408590;
  __ct__8FontDrawFv(param_1 + 0xb4);
  *(undefined4 *)(param_1 + 0xf4) = 0;
  return param_1;
}

/* JP: 0x0045b360  CmdHelpClause::~CmdHelpClause()   [__dt__13CmdHelpClauseFv]  size=0xd4 */
int __dt__13CmdHelpClauseFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__13CmdHelpClause;
    *(undefined4 *)(param_1 + 0x18) = 0x408584;
    *(undefined4 *)(param_1 + 0x24) = 0x408590;
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

/* JP: 0x0045b4c0  CmdHelpClause::CreateScene(CmdHelp*)   [CreateScene__13CmdHelpClauseFP7CmdHelp]  size=0x1d0 */
void CreateScene__13CmdHelpClauseFP7CmdHelp(int param_1,undefined4 param_2)

{
  short sVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  int iVar4;
  short sVar5;
  undefined4 uStack_24;
  
  sVar1 = GetMaxClause__7CmdHelpFv(param_2);
  uVar3 = __nwa__FUi((sVar1 * 0xc + (int)sVar1) * 0x10 + 0x10);
  uVar2 = __construct_new_array(uVar3,0x45b690,0x45b440,0xd0,sVar1);
  *(undefined4 *)(param_1 + 0xf4) = uVar2;
  iVar4 = *(int *)(param_1 + 0xf4);
  uStack_24 = 0.0;
  for (sVar5 = 0; sVar5 < sVar1; sVar5 = sVar5 + 1) {
    SetData__9MenuSceneFUsP8MenuText(param_2,1,iVar4 + 0x50);
    AddPlace__9MenuGroupFP9MenuPlace(iVar4,iVar4 + 0x50);
    SetData__9MenuSceneFUsP9MenuGroup(param_2,0,iVar4);
    *(undefined2 *)(iVar4 + 0x1c) = 0;
    *(short *)(iVar4 + 0x1e) = sVar5;
    (**(code **)(*(int *)(iVar4 + 8) + 0x24))(0,uStack_24);
    uStack_24 = uStack_24 + *(float *)(iVar4 + 0x30);
    iVar4 = iVar4 + 0xd0;
  }
  SetData__9MenuSceneFUsP8FontDraw(param_2,1,param_1 + 0xb4);
  AddPlace__10MenuWindowFP9MenuPlace(param_1,*(int *)(param_1 + 0xf4) + 0xd0);
  SetData__9MenuSceneFUsP10MenuWindow(param_2,1,param_1);
  AddOT__7MenuObjFv(param_1);
  return;
}

/* JP: 0x0045b6d0  CmdHelpClause::UpdateScene(CmdHelp*, short)   [UpdateScene__13CmdHelpClauseFP7CmdHelps]  size=0x320 */
void UpdateScene__13CmdHelpClauseFP7CmdHelps(int param_1,int param_2,short param_3)

{
  short sVar1;
  short *psVar2;
  uint uVar3;
  ulong uVar4;
  int iVar5;
  short *psVar6;
  int iVar7;
  undefined4 *puVar8;
  
  iVar7 = *(int *)(param_2 + 0x2d4) + param_3 * 0xc;
  iVar5 = *(int *)(param_1 + 0xf4);
  ClearPlace__10MenuWindowFv(param_1);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0xb4);
  *(undefined4 *)(param_1 + 0xf8) = 0;
  psVar6 = *(short **)(iVar7 + 4);
  psVar2 = psVar6 + *(short *)(iVar7 + 8);
  do {
    if (psVar2 <= psVar6) {
      *(int *)(*(int *)(param_1 + 0x40) + 0x38) = param_1 + 0xb4;
      SetScroll__10MenuWindowFss(param_1,0,0);
      *(short *)(param_1 + 0xae) = param_3;
      return;
    }
    puVar8 = (undefined4 *)(*(int *)(param_2 + 0x2d8) + *psVar6 * 0x24);
    if ((long)((ulong)*(byte *)((int)puVar8 + 0x1d) << 0x38) < 0) {
LAB_0045b858:
      SetMessage__8MenuTextFPcUiUcUc(iVar5 + 0x50,*puVar8,*(byte *)(iVar5 + 0xa8) & 7,0,0);
      *(short *)(iVar5 + 0x16) = *psVar6;
      AddPlace__10MenuWindowFP9MenuPlace(param_1,iVar5);
      sVar1 = *psVar6;
      iVar7 = (int)sVar1;
      if (sVar1 < 0) {
        iVar7 = iVar7 + 7;
      }
      uVar4 = (long)sVar1 & 7;
      uVar3 = (uint)uVar4;
      if (((long)sVar1 < 0) && (uVar4 != 0)) {
        uVar3 = uVar3 - 8;
      }
      if ((1 << (uVar3 & 0x1f) & (uint)*(byte *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + (iVar7 >> 3) + 0x1d0)
          ) == 0) {
        *(undefined2 *)(iVar5 + 0xce) = 10;
        SetCSA__8FontItemFUc(iVar5 + 0x50,10);
      }
      else {
        *(undefined2 *)(iVar5 + 0xce) = 0;
        SetCSA__8FontItemFUc(iVar5 + 0x50,0);
      }
      iVar5 = iVar5 + 0xd0;
      *(int *)(param_1 + 0xf8) = *(int *)(param_1 + 0xf8) + 1;
    }
    else {
      sVar1 = *psVar6;
      uVar4 = (long)sVar1 & 7;
      uVar3 = (uint)uVar4;
      if (((long)sVar1 < 0) && (uVar4 != 0)) {
        uVar3 = uVar3 - 8;
      }
      iVar7 = (int)sVar1;
      if (sVar1 < 0) {
        iVar7 = iVar7 + 7;
      }
      if ((1 << (uVar3 & 0x1f) & (uint)*(byte *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x180 + (iVar7 >> 3))
          ) != 0) goto LAB_0045b858;
    }
    psVar6 = psVar6 + 1;
  } while( true );
}

/* JP: 0x0045b9f0  CmdHelpClause::Select(CmdHelp*, MenuGroup*, MenuGroup*)   [Select__13CmdHelpClauseFP7CmdHelpP9MenuGroupP9MenuGroup]  size=0x14c */
void Select__13CmdHelpClauseFP7CmdHelpP9MenuGroupP9MenuGroup
               (int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  
  if (param_4 != 0) {
    iVar1 = *(int *)(param_1 + 0xf4) +
            (*(short *)(param_4 + 0x1e) * 0xc + (int)*(short *)(param_4 + 0x1e)) * 0x10;
    SetCSA__8FontItemFUc(iVar1 + 0x50,*(ushort *)(iVar1 + 0xce) & 0xff);
  }
  if (param_3 != 0) {
    iVar1 = *(int *)(param_1 + 0xf4) +
            (*(short *)(param_3 + 0x1e) * 0xc + (int)*(short *)(param_3 + 0x1e)) * 0x10;
    SetCSA__8FontItemFUc(iVar1 + 0x50,1);
    SetExplanation__7CmdNoteFPCce
              (*(undefined4 *)(param_2 + 0x2e0),*(undefined4 *)(*(int *)(param_2 + 0x28) + 0x20),
               *(undefined4 *)(iVar1 + 0xb0));
  }
  return;
}

/* JP: 0x0045bb40  CmdHelpClause::~CmdHelpClause()   [@24@__dt__13CmdHelpClauseFv]  size=0x8 */
undefined4 * _24___dt__13CmdHelpClauseFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -6;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-4] = &__vt__13CmdHelpClause;
    *param_1 = 0x408584;
    param_1[3] = 0x408590;
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

/* JP: 0x0045bb50  CmdHelpClause::~CmdHelpClause()   [@36@__dt__13CmdHelpClauseFv]  size=0x8 */
undefined4 * _36___dt__13CmdHelpClauseFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -9;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-7] = &__vt__13CmdHelpClause;
    param_1[-3] = 0x408584;
    *param_1 = 0x408590;
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
