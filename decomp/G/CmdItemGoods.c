/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdItemGoods   functions: 8
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdItemGoods.md).
 */

/* JP: 0x0045d540  CmdItemGoods::CmdItemGoods()   [__ct__12CmdItemGoodsFv]  size=0x84 */
int __ct__12CmdItemGoodsFv(int param_1)

{
  __ct__9CmdWindowFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__12CmdItemGoods;
  *(undefined4 *)(param_1 + 0x18) = 0x408604;
  *(undefined4 *)(param_1 + 0x24) = 0x408610;
  __ct__8FontDrawFv(param_1 + 0xb4);
  __ct__11SendOnLocalFv(param_1 + 0xf4);
  *(undefined4 *)(param_1 + 0x124) = 0;
  return param_1;
}

/* JP: 0x0045d5d0  CmdItemGoods::~CmdItemGoods()   [__dt__12CmdItemGoodsFv]  size=0xe4 */
int __dt__12CmdItemGoodsFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__12CmdItemGoods;
    *(undefined4 *)(param_1 + 0x18) = 0x408604;
    *(undefined4 *)(param_1 + 0x24) = 0x408610;
    if (*(int *)(param_1 + 0x124) != 0) {
      __destroy_new_array(*(undefined4 *)(param_1 + 0x124),0x4502f0);
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

/* JP: 0x0045d6c0  CmdItemGoods::CreateScene(CmdItem*)   [CreateScene__12CmdItemGoodsFP7CmdItem]  size=0x4ec */
void CreateScene__12CmdItemGoodsFP7CmdItem(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined8 uVar4;
  long lVar5;
  int iVar6;
  uint uVar7;
  int unaff_s2_lo;
  undefined1 auStack_68 [12];
  undefined4 uStack_5c;
  int iStack_58;
  undefined4 uStack_54;
  undefined1 *puStack_50;
  char *pcStack_4c;
  undefined4 uStack_48;
  int iStack_44;
  int iStack_40;
  int iStack_3c;
  int iStack_38;
  undefined4 uStack_34;
  int iStack_30;
  ushort uStack_2c;
  ushort uStack_2a;
  undefined2 uStack_28;
  ushort uStack_26;
  short sStack_24;
  undefined1 uStack_21;
  int iStack_20;
  int iStack_10;
  
  iVar1 = *(int *)(param_2 + 0x8c);
  iStack_40 = *(int *)(param_2 + 0x84);
  iVar2 = *(int *)(param_2 + 0x88);
  uStack_26 = *(ushort *)(param_2 + 0x82);
  uVar3 = (uint)uStack_26;
  iStack_44 = iVar2;
  iStack_3c = iVar1;
  iStack_30 = iStack_40;
  iStack_20 = param_1;
  iStack_10 = param_2;
  uVar4 = __nwa__FUi((uint)uStack_26 * 0x1b0 + 0x10);
  uStack_48 = __construct_new_array(uVar4,0x450610,0x4502f0,0x1b0,uVar3);
  *(undefined4 *)(iStack_20 + 0x124) = uStack_48;
  iVar6 = *(int *)(iStack_20 + 0x124);
  uVar7 = 0;
  do {
    if (uVar3 <= uVar7) {
      SetData__9MenuSceneFUsP8FontDraw(iStack_10,0,iStack_20 + 0xb4);
      uStack_5c = uRam004216ac;
      Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(iStack_20 + 0xf4,0x4216b0,uRam004216ac,1,0xffffffffffffffff);
      sStack_24 = *(short *)(*(int *)(iStack_10 + 0x3c) + 0x12) + -1;
      *(short *)(iStack_20 + 0x108) = sStack_24;
      *(undefined2 *)(unaff_s2_lo + 0x1c) = 0;
      *(undefined2 *)(unaff_s2_lo + 0x1e) = 1;
      AddPlace__10MenuWindowFP9MenuPlace(iStack_20,unaff_s2_lo);
      SetData__9MenuSceneFUsP10MenuWindow(iStack_10,0,iStack_20);
      *(int *)(*(int *)(iStack_20 + 0x40) + 0x38) = iStack_20 + 0xb4;
      SetScroll__10MenuWindowFss(iStack_20,0,0);
      AddOT__7MenuObjFv(iStack_20);
      uStack_21 = *(undefined1 *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x28c);
      Order__12CmdItemGoodsFP7CmdItemUc(iStack_20,iStack_10,uStack_21);
      return;
    }
    pcStack_4c = (char *)(*(int *)(iVar1 + 8) + uVar7);
    if (*pcStack_4c != '\0') {
      SetData__9MenuSceneFUsP10MenuSprite(iStack_10,0,iVar6 + 0x150);
      uStack_28 = *(undefined2 *)(iVar6 + 0x172);
      SetIcon__10MenuCommonFcP10MenuSprite((char)uStack_28,iVar6 + 0x150);
      SetData__9MenuSceneFUsP8MenuText(iStack_10,0,iVar6 + 0x50);
      uStack_34 = GetRegDat__9RegDatApiFiii(9,uVar7,0xffffffffffffffff);
      SetMessage__8MenuTextFPcUiUcUc(iVar6 + 0x50,uStack_34,*(byte *)(iVar6 + 0xa8) & 7,0,0);
      SetData__9MenuSceneFUsP8MenuText(iStack_10,1,iVar6 + 0xd0);
      puStack_50 = (undefined1 *)(*(int *)(iVar1 + 8) + uVar7);
      uStack_54 = *(undefined4 *)(*(int *)(iStack_10 + 0x24) + 0x10);
      sprintf(auStack_68,uStack_54,*puStack_50);
      SetMessage__8MenuTextFPcUiUcUc(iVar6 + 0xd0,auStack_68,*(byte *)(iVar6 + 0x128) & 7,1,0);
      AddPlace__9MenuGroupFP9MenuPlace(iVar6,iVar6 + 0x150);
      AddPlace__9MenuGroupFP9MenuPlace(iVar6,iVar6 + 0x50);
      AddPlace__9MenuGroupFP9MenuPlace(iVar6,iVar6 + 0xd0);
      SetData__9MenuSceneFUsP9MenuGroup(iStack_10,0,iVar6);
      *(short *)(iVar6 + 0x16) = (short)uVar7;
      unaff_s2_lo = iVar6;
      if (((((ulong)*(byte *)(iVar2 + uVar7 * 0x30 + 4) & 0x1f) >> 3 == 1) ||
          (((ulong)*(byte *)(iVar2 + uVar7 * 0x30 + 4) & 0x1f) >> 3 == 3)) ||
         ((((ulong)*(ushort *)(iVar2 + uVar7 * 0x30 + 4) & 0x1ff) >> 7 == 0 &&
          (lVar5 = FindPC__8CmdPartyFUs(iVar1,*(undefined2 *)(iStack_30 + uVar7 * 0x1c + 0x10)),
          lVar5 == 0)))) {
LAB_0045da10:
        *(byte *)(iVar6 + 0x21) = *(byte *)(iVar6 + 0x21) & 0xf7;
        (**(code **)(*(int *)(iVar6 + 8) + 0x34))(0x3f000000);
      }
      else if (uVar7 == 0x20) {
        iStack_58 = *(int *)(iStack_10 + 0x10);
        uStack_2c = *(ushort *)(iStack_58 + 0x4a);
        iStack_38 = iStack_58;
        uStack_2a = uStack_2c;
        if ((uStack_2c & 2) == 0) goto LAB_0045da10;
      }
    }
    uVar7 = uVar7 + 1 & 0xffff;
    iVar6 = iVar6 + 0x1b0;
  } while( true );
}

/* JP: 0x0045dbb0  CmdItemGoods::UpdateCount(CmdItem*, short, short)   [UpdateCount__12CmdItemGoodsFP7CmdItemss]  size=0x20c */
bool UpdateCount__12CmdItemGoodsFP7CmdItemss(int param_1,int param_2,short param_3,short param_4)

{
  short sVar1;
  int iVar2;
  undefined1 auStack_80 [40];
  undefined4 uStack_58;
  undefined4 uStack_54;
  byte *pbStack_50;
  int iStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  int iStack_40;
  int iStack_30;
  short sStack_20;
  short sStack_10;
  
  iStack_4c = *(int *)(param_2 + 0x8c);
  pbStack_50 = (byte *)(*(int *)(iStack_4c + 8) + (int)param_3);
  sVar1 = (ushort)*pbStack_50 + param_4;
  iStack_40 = param_1;
  iStack_30 = param_2;
  sStack_20 = param_3;
  sStack_10 = param_4;
  if (0 < sVar1) {
    *pbStack_50 = (byte)sVar1;
    sprintf(auStack_80,*(undefined4 *)(*(int *)(param_2 + 0x24) + 0x10),sVar1);
    iVar2 = *(int *)(iStack_40 + 0x124) + sStack_20 * 0x1b0;
    SetMessage__8MenuTextFPcUiUcUc(iVar2 + 0xd0,auStack_80,*(byte *)(iVar2 + 0x128) & 7,1,0);
  }
  else {
    *pbStack_50 = 0;
    *(undefined2 *)(*(int *)(param_1 + 0x124) + param_3 * 0x1b0 + 0x16) = 0xffff;
  }
  uStack_54 = *(undefined4 *)(iStack_40 + 0x8c);
  uStack_58 = *(undefined4 *)(iStack_40 + 0x90);
  uStack_48 = uStack_58;
  uStack_44 = uStack_54;
  Order__12CmdItemGoodsFP7CmdItemUc
            (iStack_40,iStack_30,*(undefined1 *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x28c));
  SetOffset__10MenuWindowFff(uStack_44,uStack_48,iStack_40);
  return 0 >= sVar1;
}

/* JP: 0x0045ddc0  CmdItemGoods::Order(CmdItem*, unsigned char)   [Order__12CmdItemGoodsFP7CmdItemUc]  size=0x29c */
void Order__12CmdItemGoodsFP7CmdItemUc(int param_1,int param_2,byte param_3)

{
  ushort uVar1;
  int iVar2;
  ushort uVar3;
  ulong uVar4;
  int iVar5;
  short sVar6;
  int iVar7;
  int iVar8;
  
  iVar8 = *(int *)(param_2 + 0x84);
  uVar1 = *(ushort *)(param_2 + 0x82);
  iVar2 = *(int *)(param_2 + 0x98);
  ClearPlace__10MenuWindowFv(param_1);
  iVar7 = 0;
  for (uVar3 = 0; sVar6 = (short)iVar7, uVar3 < uVar1; uVar3 = uVar3 + 1) {
    iVar5 = *(int *)(param_1 + 0x124) + *(short *)(iVar8 + (uint)param_3 * 2 + 0x12) * 0x1b0;
    if (-1 < *(short *)(iVar5 + 0x16)) {
      *(undefined2 *)(iVar5 + 0x1c) = 0;
      *(short *)(iVar5 + 0x1e) = sVar6;
      (**(code **)(*(int *)(iVar5 + 8) + 0x24))(0,(float)iVar7 * *(float *)(iVar5 + 0x30));
      AddPlace__10MenuWindowFP9MenuPlace(param_1,iVar5);
      iVar7 = (int)(short)(sVar6 + 1);
    }
    iVar8 = iVar8 + 0x1c;
  }
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0xb4);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0xf4);
  *(byte *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x28c) = param_3;
  *(short *)(param_1 + 0xae) = sVar6;
  SetScroll__10MenuWindowFss(param_1,0,0);
  ClearReport__15CmdButtonReportFv(iVar2);
  if (*(int *)(param_1 + 0x44) == 0) {
    uVar4 = 0;
  }
  else {
    uVar4 = ((ulong)*(ushort *)(param_1 + 0xb2) & 0x3ff) >> 2;
  }
  if (uVar4 != 0) {
    SetReport__15CmdButtonReportFii(iVar2,*(undefined1 *)(iVar2 + 0x20),0xd);
  }
  SetReport__15CmdButtonReportFii(iVar2,*(undefined1 *)(iVar2 + 0x20),6);
  SetReport__15CmdButtonReportFii(iVar2,*(undefined1 *)(iVar2 + 0x20),4);
  return;
}

/* JP: 0x0045e060  CmdItemGoods::Select(CmdNote*, MenuGroup*, MenuGroup*)   [Select__12CmdItemGoodsFP7CmdNoteP9MenuGroupP9MenuGroup]  size=0x15c */
int Select__12CmdItemGoodsFP7CmdNoteP9MenuGroupP9MenuGroup
              (int param_1,int param_2,int param_3,int param_4)

{
  undefined8 uVar1;
  int iVar2;
  
  if (param_4 != 0) {
    iVar2 = *(int *)(param_1 + 0x124) + *(short *)(param_4 + 0x16) * 0x1b0;
    SetCSA__8FontItemFUc(iVar2 + 0x50,0);
    SetCSA__8FontItemFUc(iVar2 + 0xd0,0);
  }
  if (param_3 != 0) {
    iVar2 = *(int *)(param_1 + 0x124) + *(short *)(param_3 + 0x16) * 0x1b0;
    SetCSA__8FontItemFUc(iVar2 + 0x50,1);
    SetCSA__8FontItemFUc(iVar2 + 0xd0,1);
    if (param_2 != 0) {
      uVar1 = GetRegDat__9RegDatApiFiii(0x1a,*(undefined2 *)(param_3 + 0x16),0xffffffffffffffff);
      SetExplanation__7CmdNoteFPCce(param_2,uVar1);
    }
  }
  return param_3;
}

/* JP: 0x0045e1c0  CmdItemGoods::~CmdItemGoods()   [@24@__dt__12CmdItemGoodsFv]  size=0x8 */
undefined4 * _24___dt__12CmdItemGoodsFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -6;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-4] = &__vt__12CmdItemGoods;
    *param_1 = 0x408604;
    param_1[3] = 0x408610;
    if (param_1[0x43] != 0) {
      __destroy_new_array(param_1[0x43],0x4502f0);
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

/* JP: 0x0045e1d0  CmdItemGoods::~CmdItemGoods()   [@36@__dt__12CmdItemGoodsFv]  size=0x8 */
undefined4 * _36___dt__12CmdItemGoodsFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -9;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-7] = &__vt__12CmdItemGoods;
    param_1[-3] = 0x408604;
    *param_1 = 0x408610;
    if (param_1[0x40] != 0) {
      __destroy_new_array(param_1[0x40],0x4502f0);
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
