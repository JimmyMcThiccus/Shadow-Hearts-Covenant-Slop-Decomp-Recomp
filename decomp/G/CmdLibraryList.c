/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdLibraryList   functions: 6
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdLibraryList.md).
 */

/* JP: 0x00465c60  CmdLibraryList::CmdLibraryList()   [__ct__14CmdLibraryListFv]  size=0x74 */
int __ct__14CmdLibraryListFv(int param_1)

{
  __ct__9CmdWindowFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__14CmdLibraryList;
  *(undefined4 *)(param_1 + 0x18) = 0x408824;
  *(undefined4 *)(param_1 + 0x24) = 0x408830;
  __ct__8FontDrawFv(param_1 + 0xb4);
  *(undefined4 *)(param_1 + 0xf4) = 0;
  return param_1;
}

/* JP: 0x00465ce0  CmdLibraryList::~CmdLibraryList()   [__dt__14CmdLibraryListFv]  size=0xd4 */
int __dt__14CmdLibraryListFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__14CmdLibraryList;
    *(undefined4 *)(param_1 + 0x18) = 0x408824;
    *(undefined4 *)(param_1 + 0x24) = 0x408830;
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

/* JP: 0x00465dc0  CmdLibraryList::CreateScene(CmdLibrary*, short)   [CreateScene__14CmdLibraryListFP10CmdLibrarys]  size=0x550 */
void CreateScene__14CmdLibraryListFP10CmdLibrarys(int param_1,int param_2,short param_3)

{
  int iVar1;
  short sVar2;
  int iVar3;
  short *psVar4;
  int iVar5;
  undefined4 uVar6;
  undefined8 uVar7;
  long lVar8;
  uint uVar9;
  ulong uVar10;
  short sVar11;
  short sVar12;
  int iVar13;
  short *psVar14;
  int iVar15;
  undefined4 *puVar16;
  
  iVar3 = *(int *)(param_2 + param_3 * 4 + 0x1fc);
  iVar1 = *(int *)(param_2 + 0x1e4);
  iVar13 = 0;
  SetData__9MenuSceneFUsP8FontDraw(param_2,3,param_1 + 0xb4);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0xb4);
  if (param_3 == 0) {
    iVar15 = iVar3 + 0x10;
    sVar2 = (short)*(undefined4 *)(iVar3 + 8);
    uVar7 = __nwa__FUi(sVar2 * 0xd0 + 0x10);
    iVar3 = __construct_new_array(uVar7,0x45b690,0x45b440,0xd0,(int)sVar2);
    *(int *)(param_1 + 0xf4) = iVar3;
    for (sVar11 = 0; sVar11 < sVar2; sVar11 = sVar11 + 1) {
      psVar14 = (short *)(iVar15 + 0x12);
      psVar4 = psVar14 + *(char *)(iVar15 + 0x11);
      for (; psVar14 < psVar4; psVar14 = psVar14 + 1) {
        sVar12 = *psVar14;
        iVar5 = (int)sVar12;
        if (sVar12 < 0) {
          iVar5 = iVar5 + 7;
        }
        uVar10 = (long)sVar12 & 7;
        uVar9 = (uint)uVar10;
        if (((long)sVar12 < 0) && (uVar10 != 0)) {
          uVar9 = uVar9 - 8;
        }
        if (((uint)*(byte *)(*(int *)(iVar1 + 4) + (iVar5 >> 3) + 0xdaf) & 1 << (uVar9 & 0x1f)) != 0
           ) {
          SetData__9MenuSceneFUsP8MenuText(param_2,0x12,iVar3 + 0x50);
          uVar6 = GetRegDat__9RegDatApiFiii(5,*psVar14,0xffffffffffffffff);
          SetMessage__8MenuTextFPcUiUcUc(iVar3 + 0x50,uVar6,*(byte *)(iVar3 + 0xa8) & 7,0,0);
          AddPlace__9MenuGroupFP9MenuPlace(iVar3,iVar3 + 0x50);
          SetData__9MenuSceneFUsP9MenuGroup(param_2,0,iVar3);
          *(short *)(iVar3 + 0x16) = sVar11;
          *(undefined2 *)(iVar3 + 0x1c) = 0;
          *(short *)(iVar3 + 0x1e) = (short)iVar13;
          (**(code **)(*(int *)(iVar3 + 8) + 0x24))(0,(float)iVar13 * *(float *)(iVar3 + 0x30));
          AddPlace__10MenuWindowFP9MenuPlace(param_1,iVar3);
          iVar3 = iVar3 + 0xd0;
          iVar13 = (int)(short)((short)iVar13 + 1);
          break;
        }
      }
      iVar15 = iVar15 + 0x20;
    }
  }
  else {
    puVar16 = (undefined4 *)(iVar3 + 0x10);
    sVar2 = *(short *)(iVar3 + 4);
    sVar11 = (short)*(undefined4 *)(iVar3 + 8);
    uVar7 = __nwa__FUi(sVar11 * 0xd0 + 0x10);
    iVar3 = __construct_new_array(uVar7,0x45b690,0x45b440,0xd0,(int)sVar11);
    *(int *)(param_1 + 0xf4) = iVar3;
    for (sVar12 = 0; sVar12 < sVar11; sVar12 = sVar12 + 1) {
      lVar8 = FieldNpcLibrary__Fii((int)sVar12 + (int)sVar2,0);
      if (lVar8 != 0) {
        SetData__9MenuSceneFUsP8MenuText(param_2,0x12,iVar3 + 0x50);
        SetMessage__8MenuTextFPcUiUcUc(iVar3 + 0x50,*puVar16,*(byte *)(iVar3 + 0xa8) & 7,0,0);
        AddPlace__9MenuGroupFP9MenuPlace(iVar3,iVar3 + 0x50);
        SetData__9MenuSceneFUsP9MenuGroup(param_2,0,iVar3);
        *(short *)(iVar3 + 0x16) = sVar12;
        *(undefined2 *)(iVar3 + 0x1c) = 0;
        *(short *)(iVar3 + 0x1e) = (short)iVar13;
        (**(code **)(*(int *)(iVar3 + 8) + 0x24))(0,(float)iVar13 * *(float *)(iVar3 + 0x30));
        AddPlace__10MenuWindowFP9MenuPlace(param_1,iVar3);
        iVar3 = iVar3 + 0xd0;
        iVar13 = (int)(short)((short)iVar13 + 1);
      }
      puVar16 = puVar16 + 0x1d;
    }
  }
  SetData__9MenuSceneFUsP10MenuWindow(param_2,1,param_1);
  *(int *)(*(int *)(param_1 + 0x40) + 0x38) = param_1 + 0xb4;
  SetScroll__10MenuWindowFss(param_1,0,0);
  AddOT__7MenuObjFv(param_1);
  *(short *)(param_1 + 0xae) = param_3;
  return;
}

/* JP: 0x00466310  CmdLibraryList::Select(CmdLibrary*, MenuGroup*, MenuGroup*)   [Select__14CmdLibraryListFP10CmdLibraryP9MenuGroupP9MenuGroup]  size=0x15c */
void Select__14CmdLibraryListFP10CmdLibraryP9MenuGroupP9MenuGroup
               (int param_1,int param_2,int param_3,int param_4)

{
  short sVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  
  if (param_4 != 0) {
    uVar4 = FindPlace__9MenuGroupFs(param_4,10);
    SetCSA__8FontItemFUc(uVar4,0);
  }
  if (param_3 != 0) {
    uVar2 = *(undefined4 *)(param_2 + 0x1e8);
    sVar1 = *(short *)(param_3 + 0x16);
    uVar4 = FindPlace__9MenuGroupFs(param_3,10);
    SetCSA__8FontItemFUc(uVar4,1);
    if (*(short *)(param_1 + 0xae) == 0) {
      uVar3 = *(undefined4 *)(sVar1 * 0x20 + *(int *)(param_2 + 0x1fc) + 0x14);
    }
    else {
      uVar3 = *(undefined4 *)((sVar1 * 0x1c + (int)sVar1) * 4 + *(int *)(param_2 + 0x200) + 0x18);
    }
    SetExplanation__7CmdNoteFPCce(uVar2,uVar3);
  }
  return;
}

/* JP: 0x00466470  CmdLibraryList::~CmdLibraryList()   [@24@__dt__14CmdLibraryListFv]  size=0x8 */
undefined4 * _24___dt__14CmdLibraryListFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -6;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-4] = &__vt__14CmdLibraryList;
    *param_1 = 0x408824;
    param_1[3] = 0x408830;
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

/* JP: 0x00466480  CmdLibraryList::~CmdLibraryList()   [@36@__dt__14CmdLibraryListFv]  size=0x8 */
undefined4 * _36___dt__14CmdLibraryListFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -9;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-7] = &__vt__14CmdLibraryList;
    param_1[-3] = 0x408824;
    *param_1 = 0x408830;
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
