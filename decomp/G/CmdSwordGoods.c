/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdSwordGoods   functions: 6
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdSwordGoods.md).
 */

/* JP: 0x00457790  CmdSwordGoods::CmdSwordGoods()   [__ct__13CmdSwordGoodsFv]  size=0x74 */
int __ct__13CmdSwordGoodsFv(int param_1)

{
  __ct__9CmdWindowFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__13CmdSwordGoods;
  *(undefined4 *)(param_1 + 0x18) = 0x408454;
  *(undefined4 *)(param_1 + 0x24) = 0x408460;
  __ct__8FontDrawFv(param_1 + 0xb4);
  *(undefined4 *)(param_1 + 0xf4) = 0;
  return param_1;
}

/* JP: 0x00457810  CmdSwordGoods::~CmdSwordGoods()   [__dt__13CmdSwordGoodsFv]  size=0xdc */
int __dt__13CmdSwordGoodsFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__13CmdSwordGoods;
    *(undefined4 *)(param_1 + 0x18) = 0x408454;
    *(undefined4 *)(param_1 + 0x24) = 0x408460;
    if (*(int *)(param_1 + 0xf4) != 0) {
      __destroy_new_array(*(undefined4 *)(param_1 + 0xf4),0x4578f0);
      *(undefined4 *)(param_1 + 0xf4) = 0;
    }
    __dt__8FontDrawFv(param_1 + 0xb4,0xffffffffffffffff);
    __dt__9CmdWindowFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x00457990  CmdSwordGoods::CreateScene(CmdSword*)   [CreateScene__13CmdSwordGoodsFP8CmdSword]  size=0x438 */
void CreateScene__13CmdSwordGoodsFP8CmdSword(int param_1,int param_2)

{
  short *psVar1;
  uint uVar2;
  int iVar3;
  undefined8 uVar4;
  int iVar5;
  uint uVar6;
  short sVar7;
  undefined1 auStack_68 [12];
  float fStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  int iStack_4c;
  undefined4 uStack_48;
  short *psStack_44;
  uint uStack_40;
  int iStack_3c;
  int iStack_38;
  int iStack_34;
  undefined4 uStack_30;
  float fStack_2c;
  uint uStack_28;
  ushort uStack_22;
  int iStack_20;
  int iStack_10;
  
  iStack_3c = *(int *)(*(int *)(param_2 + 0x58) + 0x70);
  uStack_40 = *(uint *)(iStack_3c + 0x28);
  psVar1 = (short *)(*(int *)(param_2 + 0x7c) + 0x10);
  uStack_22 = *(ushort *)(param_2 + 0x78);
  uVar2 = (uint)uStack_22;
  psStack_44 = psVar1;
  iStack_38 = iStack_3c;
  iStack_34 = iStack_3c;
  uStack_28 = uStack_40;
  iStack_20 = param_1;
  iStack_10 = param_2;
  uVar4 = __nwa__FUi(((uint)uStack_22 * 0x1c + (uint)uStack_22) * 0x10 + 0x10);
  uStack_48 = __construct_new_array(uVar4,0x457dd0,0x4578f0,0x1d0,uVar2);
  *(undefined4 *)(iStack_20 + 0xf4) = uStack_48;
  iVar5 = *(int *)(iStack_20 + 0xf4);
  SetData__9MenuSceneFUsP8FontDraw(iStack_10,0,iStack_20 + 0xb4);
  AddPriority__12MenuObjTableFP7MenuObj(iStack_20 + 0x18,iStack_20 + 0xb4);
  fStack_2c = 0.0;
  sVar7 = 0;
  for (uVar6 = 0; uVar6 < uVar2; uVar6 = uVar6 + 1 & 0xffff) {
    if ((uStack_28 & 1 << (uVar6 & 0x1f)) != 0) {
      iVar3 = *(int *)(iStack_10 + 0x80) + uVar6 * 0x40;
      iStack_4c = iVar3;
      SetData__9MenuSceneFUsP8MenuText(iStack_10,0,iVar5 + 0x50);
      uStack_30 = GetRegDat__9RegDatApiFiii(0xc,5,uVar6);
      SetMessage__8MenuTextFPcUiUcUc(iVar5 + 0x50,uStack_30,*(byte *)(iVar5 + 0xa8) & 7,0,1);
      OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_20 + 0xb4,iVar5 + 0x50,((ulong)*(byte *)(iVar5 + 0xa8) & 0xf) >> 3,0);
      AddPlace__9MenuGroupFP9MenuPlace(iVar5,iVar5 + 0x50);
      if (-1 < *psVar1) {
        uStack_50 = *(undefined4 *)(*(int *)(iStack_10 + 0x24) + 0x10);
        sprintf(auStack_68,uStack_50,*psVar1);
        SetData__9MenuSceneFUsP8MenuText(iStack_10,1,iVar5 + 0xd0);
        SetMessage__8MenuTextFPcUiUcUc(iVar5 + 0xd0,auStack_68,*(byte *)(iVar5 + 0x128) & 7,0,1);
        OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_20 + 0xb4,iVar5 + 0xd0,((ulong)*(byte *)(iVar5 + 0x128) & 0xf) >> 3,0
                       );
        AddPlace__9MenuGroupFP9MenuPlace(iVar5,iVar5 + 0xd0);
      }
      uStack_54 = *(undefined4 *)(*(int *)(iStack_10 + 0x24) + 0x18);
      sprintf(auStack_68,uStack_54,*(undefined2 *)(iVar3 + 0x1e));
      SetData__9MenuSceneFUsP8MenuText(iStack_10,2,iVar5 + 0x150);
      SetMessage__8MenuTextFPcUiUcUc(iVar5 + 0x150,auStack_68,*(byte *)(iVar5 + 0x1a8) & 7,0,1);
      OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_20 + 0xb4,iVar5 + 0x150,((ulong)*(byte *)(iVar5 + 0x1a8) & 0xf) >> 3,0)
      ;
      AddPlace__9MenuGroupFP9MenuPlace(iVar5,iVar5 + 0x150);
      SetData__9MenuSceneFUsP9MenuGroup(iStack_10,0,iVar5);
      *(short *)(iVar5 + 0x16) = (short)uVar6;
      *(undefined2 *)(iVar5 + 0x1c) = 0;
      *(short *)(iVar5 + 0x1e) = sVar7;
      uStack_58 = *(undefined4 *)(iVar5 + 0x24);
      (**(code **)(*(int *)(iVar5 + 8) + 0x24))(uStack_58,fStack_2c);
      AddPlace__10MenuWindowFP9MenuPlace(iStack_20,iVar5);
      fStack_5c = *(float *)(iVar5 + 0x30);
      fStack_2c = fStack_2c + fStack_5c;
      iVar5 = iVar5 + 0x1d0;
      sVar7 = sVar7 + 1;
    }
    psVar1 = psVar1 + 2;
  }
  SetData__9MenuSceneFUsP10MenuWindow(iStack_10,0,iStack_20);
  AddOT__7MenuObjFv(iStack_20);
  *(short *)(iStack_20 + 0xae) = sVar7;
  return;
}

/* JP: 0x00457e30  CmdSwordGoods::Select(CmdSword*, MenuGroup*, MenuGroup*)   [Select__13CmdSwordGoodsFP8CmdSwordP9MenuGroupP9MenuGroup]  size=0x1cc */
void Select__13CmdSwordGoodsFP8CmdSwordP9MenuGroupP9MenuGroup
               (undefined8 param_1,int param_2,int param_3,int param_4)

{
  ushort uVar1;
  undefined4 uVar2;
  long lVar3;
  undefined8 uVar4;
  int iVar5;
  
  if (param_4 != 0) {
    for (iVar5 = 10; iVar5 < 0x28; iVar5 = iVar5 + 10) {
      lVar3 = FindPlace__9MenuGroupFs(param_4,(short)iVar5);
      if (lVar3 != 0) {
        SetCSA__8FontItemFUc(lVar3,0);
      }
    }
  }
  if (param_3 != 0) {
    uVar1 = *(ushort *)(param_3 + 0x16);
    for (iVar5 = 10; iVar5 < 0x28; iVar5 = iVar5 + 10) {
      lVar3 = FindPlace__9MenuGroupFs(param_3,(short)iVar5);
      if (lVar3 != 0) {
        SetCSA__8FontItemFUc(lVar3,1);
      }
    }
    uVar2 = *(undefined4 *)(*(int *)(param_2 + 0x58) + 100);
    uVar4 = GetRegDat__9RegDatApiFiii(0x1d,5,uVar1);
    SetExplanation__7CmdNoteFPCce(uVar2,uVar4);
    Create__10CmdElementFUc
              (*(undefined4 *)(*(int *)(param_2 + 0x58) + 0x6c),
               *(byte *)(*(int *)(param_2 + 0x80) + (uint)uVar1 * 0x40 + 4) & 7);
  }
  return;
}

/* JP: 0x00458000  CmdSwordGoods::~CmdSwordGoods()   [@24@__dt__13CmdSwordGoodsFv]  size=0x8 */
undefined4 * _24___dt__13CmdSwordGoodsFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -6;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-4] = &__vt__13CmdSwordGoods;
    *param_1 = 0x408454;
    param_1[3] = 0x408460;
    if (param_1[0x37] != 0) {
      __destroy_new_array(param_1[0x37],0x4578f0);
      param_1[0x37] = 0;
    }
    __dt__8FontDrawFv(param_1 + 0x27,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}

/* JP: 0x00458010  CmdSwordGoods::~CmdSwordGoods()   [@36@__dt__13CmdSwordGoodsFv]  size=0x8 */
undefined4 * _36___dt__13CmdSwordGoodsFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -9;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-7] = &__vt__13CmdSwordGoods;
    param_1[-3] = 0x408454;
    *param_1 = 0x408460;
    if (param_1[0x34] != 0) {
      __destroy_new_array(param_1[0x34],0x4578f0);
      param_1[0x34] = 0;
    }
    __dt__8FontDrawFv(param_1 + 0x24,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}
