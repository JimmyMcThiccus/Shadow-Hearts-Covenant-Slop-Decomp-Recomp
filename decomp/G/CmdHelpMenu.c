/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdHelpMenu   functions: 8
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdHelpMenu.md).
 */

/* JP: 0x0045a740  CmdHelpMenu::CmdHelpMenu()   [__ct__11CmdHelpMenuFv]  size=0x84 */
int __ct__11CmdHelpMenuFv(int param_1)

{
  __ct__9CmdWindowFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__11CmdHelpMenu;
  *(undefined4 *)(param_1 + 0x18) = 0x408544;
  *(undefined4 *)(param_1 + 0x24) = 0x408550;
  __ct__8FontDrawFv(param_1 + 0xb4);
  __ct__11SendOnLocalFv(param_1 + 0xf4);
  *(undefined4 *)(param_1 + 0x124) = 0;
  return param_1;
}

/* JP: 0x0045a7d0  CmdHelpMenu::~CmdHelpMenu()   [__dt__11CmdHelpMenuFv]  size=0xe4 */
int __dt__11CmdHelpMenuFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__11CmdHelpMenu;
    *(undefined4 *)(param_1 + 0x18) = 0x408544;
    *(undefined4 *)(param_1 + 0x24) = 0x408550;
    if (*(int *)(param_1 + 0x124) != 0) {
      __destroy_new_array(*(undefined4 *)(param_1 + 0x124),0x45a8c0);
    }
    __dt__11SendOnLocalFv(param_1 + 0xf4,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0xb4,0xffffffffffffffff);
    __dt__9CmdWindowFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x0045a940  CmdHelpMenu::CreateScene(CmdHelp*)   [CreateScene__11CmdHelpMenuFP7CmdHelp]  size=0x50c */
void CreateScene__11CmdHelpMenuFP7CmdHelp(int param_1,int param_2)

{
  short sVar1;
  int iVar2;
  undefined4 uVar3;
  short *psVar4;
  undefined8 uVar5;
  ulong uVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  short *psVar10;
  undefined4 *puVar11;
  short sVar12;
  float fVar13;
  float fStack_30;
  
  iVar2 = *(int *)(sm_pSubstance__15SaveMenuSection + 0xc);
  puVar11 = *(undefined4 **)(param_2 + 0x2d4);
  sVar1 = *(short *)(param_2 + 0x2d0);
  SetData__9MenuSceneFUsP8FontDraw(param_2,0,param_1 + 0xb4);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0xb4);
  uVar5 = __nwa__FUi(sVar1 * 0xe0 + 0x10);
  uVar3 = __construct_new_array(uVar5,0x45ae50,0x45a8c0,0xe0,sVar1);
  *(undefined4 *)(param_1 + 0x124) = uVar3;
  iVar9 = *(int *)(param_1 + 0x124);
  fStack_30 = 0.0;
  sVar12 = 0;
  do {
    if (sVar1 <= sVar12) {
      Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(param_1 + 0xf4,param_2 + 0x80,*(undefined4 *)(param_2 + 0x7c),1,
                      0xffffffffffffffff);
      *(short *)(param_1 + 0x108) = *(short *)(*(int *)(param_1 + 0x124) + 0x94) + -1;
      AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0xf4);
      SetNewIcon__11CmdHelpMenuFP7CmdHelp(param_1,param_2);
      SetData__9MenuSceneFUsP10MenuWindow(param_2,0,param_1);
      AddOT__7MenuObjFv(param_1);
      return;
    }
    SetData__9MenuSceneFUsP8MenuText(param_2,0,iVar9);
    *(short *)(iVar9 + 0x16) = sVar12;
    *(undefined2 *)(iVar9 + 0x1c) = 0;
    *(short *)(iVar9 + 0x1e) = sVar12;
    (**(code **)(*(int *)(iVar9 + 8) + 0x24))(0,fStack_30);
    SetMessage__8MenuTextFPcUiUcUc(iVar9,*puVar11,*(byte *)(iVar9 + 0x58) & 7,0,0);
    OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(param_1 + 0xb4,iVar9,((ulong)*(byte *)(iVar9 + 0x58) & 0xf) >> 3,0);
    AddPlace__10MenuWindowFP9MenuPlace(param_1,iVar9);
    SetData__9MenuSceneFUsP10MenuSprite(param_2,0,iVar9 + 0x80);
    (**(code **)(*(int *)(iVar9 + 0x88) + 0x24))
              (*(float *)(iVar9 + 0xa4) + *(float *)(iVar9 + 0x2c),fStack_30);
    AddPlace__10MenuWindowFP9MenuPlace(param_1,iVar9 + 0x80);
    psVar10 = (short *)puVar11[1];
    psVar4 = psVar10 + *(short *)(puVar11 + 2);
    for (; psVar10 < psVar4; psVar10 = psVar10 + 1) {
      if ((long)((ulong)*(byte *)(*(int *)(param_2 + 0x2d8) + *psVar10 * 0x24 + 0x1d) << 0x38) < 0)
      {
LAB_0045ac30:
        SetCSA__8FontItemFUc(iVar9,0);
        *(undefined1 *)(iVar9 + 0x5c) = 0;
        uVar6 = (ulong)*(byte *)(iVar9 + 0x11) & 0xfffffffffffffffd | 2;
        *(char *)(iVar9 + 0x11) = (char)uVar6;
        *(byte *)(iVar9 + 0x10) =
             *(byte *)(iVar9 + 0x10) & 0xfd | (byte)((uint)((uVar6 << 0x3e) >> 0x3f) << 1);
        *(byte *)(iVar9 + 0x21) = *(byte *)(iVar9 + 0x21) & 0xfd | 2;
        break;
      }
      uVar6 = (long)*psVar10 & 7;
      uVar7 = (uint)uVar6;
      if (((long)*psVar10 < 0) && (uVar6 != 0)) {
        uVar7 = uVar7 - 8;
      }
      iVar8 = (int)*psVar10;
      if (*psVar10 < 0) {
        iVar8 = iVar8 + 7;
      }
      if ((1 << (uVar7 & 0x1f) & (uint)*(byte *)(iVar2 + 0x180 + (iVar8 >> 3))) != 0)
      goto LAB_0045ac30;
    }
    uVar6 = GetRealHeight__8FontItemCFv(iVar9);
    if ((long)uVar6 < 0) {
      fVar13 = (float)(uVar6 & 0xffffffff);
    }
    else {
      fVar13 = (float)(int)uVar6;
    }
    fStack_30 = fStack_30 + fVar13;
    sVar12 = sVar12 + 1;
    iVar9 = iVar9 + 0xe0;
    puVar11 = puVar11 + 3;
  } while( true );
}

/* JP: 0x0045ae90  CmdHelpMenu::SetNewIcon(CmdHelp*)   [SetNewIcon__11CmdHelpMenuFP7CmdHelp]  size=0x2d0 */
void SetNewIcon__11CmdHelpMenuFP7CmdHelp(int param_1,int param_2)

{
  short sVar1;
  int iVar2;
  uint uVar3;
  short *psVar4;
  uint uVar5;
  int iVar6;
  ulong uVar7;
  short *psVar8;
  uint uVar9;
  int iVar10;
  
  iVar10 = *(int *)(param_2 + 0x2d4);
  iVar2 = *(int *)(param_2 + 0x2d8);
  uVar9 = *(uint *)(param_1 + 0x124);
  uVar3 = uVar9 + (uint)*(ushort *)(param_2 + 0x2d0) * 0xe0;
  do {
    if (uVar3 <= uVar9) {
      return;
    }
    psVar8 = *(short **)(iVar10 + 4);
    psVar4 = psVar8 + *(short *)(iVar10 + 8);
    *(byte *)(uVar9 + 0x92) = *(byte *)(uVar9 + 0x92) & 0xfe;
    for (; psVar8 < psVar4; psVar8 = psVar8 + 1) {
      if ((long)((ulong)*(byte *)(iVar2 + *psVar8 * 0x24 + 0x1d) << 0x38) < 0) {
LAB_0045b058:
        sVar1 = *psVar8;
        iVar6 = (int)sVar1;
        if (sVar1 < 0) {
          iVar6 = iVar6 + 7;
        }
        uVar7 = (long)sVar1 & 7;
        uVar5 = (uint)uVar7;
        if (((long)sVar1 < 0) && (uVar7 != 0)) {
          uVar5 = uVar5 - 8;
        }
        if ((1 << (uVar5 & 0x1f) &
            (uint)*(byte *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + (iVar6 >> 3) + 0x1d0)) == 0) {
          *(byte *)(uVar9 + 0x92) = *(byte *)(uVar9 + 0x92) & 0xfe | 1;
          break;
        }
      }
      else {
        sVar1 = *psVar8;
        uVar7 = (long)sVar1 & 7;
        uVar5 = (uint)uVar7;
        if (((long)sVar1 < 0) && (uVar7 != 0)) {
          uVar5 = uVar5 - 8;
        }
        iVar6 = (int)sVar1;
        if (sVar1 < 0) {
          iVar6 = iVar6 + 7;
        }
        if ((1 << (uVar5 & 0x1f) &
            (uint)*(byte *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x180 + (iVar6 >> 3))) != 0)
        goto LAB_0045b058;
      }
    }
    uVar9 = uVar9 + 0xe0;
    iVar10 = iVar10 + 0xc;
  } while( true );
}

/* JP: 0x0045b160  CmdHelpMenu::GetMenu(CmdHelp*)   [GetMenu__11CmdHelpMenuFP7CmdHelp]  size=0xb0 */
undefined4 GetMenu__11CmdHelpMenuFP7CmdHelp(int param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = *(uint *)(param_1 + 0x124);
  uVar2 = uVar1 + (uint)*(ushort *)(param_2 + 0x2d0) * 0xe0;
  while( true ) {
    if (uVar2 <= uVar1) {
      return 0;
    }
    if ((long)((ulong)*(byte *)(uVar1 + 0x21) << 0x3e) < 0) break;
    uVar1 = uVar1 + 0xe0;
  }
  return *(undefined4 *)(param_1 + 0x124);
}

/* JP: 0x0045b210  CmdHelpMenu::Select(CmdHelp*, MenuText*, MenuText*)   [Select__11CmdHelpMenuFP7CmdHelpP8MenuTextP8MenuText]  size=0xac */
void Select__11CmdHelpMenuFP7CmdHelpP8MenuTextP8MenuText
               (undefined8 param_1,int param_2,int param_3,int param_4)

{
  if (param_4 != 0) {
    SetCSA__8FontItemFUc(param_4,0);
  }
  if (param_3 != 0) {
    SetCSA__8FontItemFUc(param_3,1);
    SetExplanation__7CmdNoteFPCce
              (*(undefined4 *)(param_2 + 0x2e0),*(undefined4 *)(*(int *)(param_2 + 0x28) + 0x14),
               *(undefined4 *)(param_3 + 0x60));
  }
  return;
}

/* JP: 0x0045b2c0  CmdHelpMenu::~CmdHelpMenu()   [@24@__dt__11CmdHelpMenuFv]  size=0x8 */
undefined4 * _24___dt__11CmdHelpMenuFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -6;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-4] = &__vt__11CmdHelpMenu;
    *param_1 = 0x408544;
    param_1[3] = 0x408550;
    if (param_1[0x43] != 0) {
      __destroy_new_array(param_1[0x43],0x45a8c0);
    }
    __dt__11SendOnLocalFv(param_1 + 0x37,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x27,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}

/* JP: 0x0045b2d0  CmdHelpMenu::~CmdHelpMenu()   [@36@__dt__11CmdHelpMenuFv]  size=0x8 */
undefined4 * _36___dt__11CmdHelpMenuFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -9;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-7] = &__vt__11CmdHelpMenu;
    param_1[-3] = 0x408544;
    *param_1 = 0x408550;
    if (param_1[0x40] != 0) {
      __destroy_new_array(param_1[0x40],0x45a8c0);
    }
    __dt__11SendOnLocalFv(param_1 + 0x34,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x24,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}
