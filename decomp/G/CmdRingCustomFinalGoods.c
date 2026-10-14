/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdRingCustomFinalGoods   functions: 8
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdRingCustomFinalGoods.md).
 */

/* JP: 0x0046d520  CmdRingCustomFinalGoods::CmdRingCustomFinalGoods()   [__ct__23CmdRingCustomFinalGoodsFv]  size=0x84 */
int __ct__23CmdRingCustomFinalGoodsFv(int param_1)

{
  __ct__9CmdWindowFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__23CmdRingCustomFinalGoods;
  *(undefined4 *)(param_1 + 0x18) = 0x408944;
  *(undefined4 *)(param_1 + 0x24) = 0x408950;
  __ct__8FontDrawFv(param_1 + 0xb4);
  __ct__11SendOnLocalFv(param_1 + 0xf4);
  *(undefined4 *)(param_1 + 0x124) = 0;
  return param_1;
}

/* JP: 0x0046d5b0  CmdRingCustomFinalGoods::~CmdRingCustomFinalGoods()   [__dt__23CmdRingCustomFinalGoodsFv]  size=0xe4 */
int __dt__23CmdRingCustomFinalGoodsFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__23CmdRingCustomFinalGoods;
    *(undefined4 *)(param_1 + 0x18) = 0x408944;
    *(undefined4 *)(param_1 + 0x24) = 0x408950;
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

/* JP: 0x0046d6a0  CmdRingCustomFinalGoods::CreateScene(CmdRingCustom*)   [CreateScene__23CmdRingCustomFinalGoodsFP13CmdRingCustom]  size=0x350 */
void CreateScene__23CmdRingCustomFinalGoodsFP13CmdRingCustom(int param_1,int param_2)

{
  short sVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  int iVar4;
  short sVar5;
  undefined4 uStack_2c;
  
  sVar1 = (*(short *)(param_2 + 0x21a) - (short)*(char *)(param_2 + 0x21f)) + 1;
  uVar3 = __nwa__FUi(sVar1 * 0x1b0 + 0x10);
  uVar2 = __construct_new_array(uVar3,0x450610,0x4502f0,0x1b0,sVar1);
  *(undefined4 *)(param_1 + 0x124) = uVar2;
  iVar4 = *(int *)(param_1 + 0x124);
  uStack_2c = 0.0;
  for (sVar5 = 0; sVar5 < sVar1; sVar5 = sVar5 + 1) {
    SetData__9MenuSceneFUsP10MenuSprite(param_2,0,iVar4 + 0x150);
    SetData__9MenuSceneFUsP8MenuText(param_2,3,iVar4 + 0x50);
    SetData__9MenuSceneFUsP8MenuText(param_2,4,iVar4 + 0xd0);
    SetIcon__10MenuCommonFcP10MenuSprite((char)*(undefined2 *)(iVar4 + 0x172),iVar4 + 0x150);
    AddPlace__9MenuGroupFP9MenuPlace(iVar4,iVar4 + 0x150);
    AddPlace__9MenuGroupFP9MenuPlace(iVar4,iVar4 + 0x50);
    AddPlace__9MenuGroupFP9MenuPlace(iVar4,iVar4 + 0xd0);
    SetData__9MenuSceneFUsP9MenuGroup(param_2,1,iVar4);
    *(undefined2 *)(iVar4 + 0x1c) = 0;
    *(short *)(iVar4 + 0x1e) = sVar5;
    (**(code **)(*(int *)(iVar4 + 8) + 0x24))(0,uStack_2c);
    uStack_2c = uStack_2c + *(float *)(iVar4 + 0x30);
    iVar4 = iVar4 + 0x1b0;
  }
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(param_1 + 0xf4,0x4216b0,uRam004216ac,1,0xffffffffffffffff);
  *(short *)(param_1 + 0x108) = *(short *)(*(int *)(param_1 + 0x124) + 0x164) + -1;
  SetData__9MenuSceneFUsP8FontDraw(param_2,2,param_1 + 0xb4);
  AddPlace__10MenuWindowFP9MenuPlace(param_1,*(int *)(param_1 + 0x124) + 0x1b0);
  SetData__9MenuSceneFUsP10MenuWindow(param_2,2,param_1);
  if (*(int *)(param_1 + 0x3c) != 0) {
    (**(code **)(*(int *)(*(int *)(param_1 + 0x3c) + 8) + 0x2c))
              (*(int *)(param_1 + 0x3c),0x20,0x20,0x20);
  }
  SetAlpha__10MenuWindowFUc(param_1,0x60);
  AddOT__7MenuObjFv(param_1);
  return;
}

/* JP: 0x0046d9f0  CmdRingCustomFinalGoods::UpdateScene(CmdRingCustom*, short)   [UpdateScene__23CmdRingCustomFinalGoodsFP13CmdRingCustoms]  size=0x374 */
void UpdateScene__23CmdRingCustomFinalGoodsFP13CmdRingCustoms(int param_1,int param_2,short param_3)

{
  short sVar1;
  int iVar2;
  short sVar3;
  undefined1 auStack_50 [8];
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  short sStack_38;
  ushort uStack_36;
  short sStack_34;
  char cStack_32;
  char cStack_31;
  int iStack_30;
  int iStack_20;
  short sStack_10;
  
  cStack_32 = *(char *)(param_2 + 0x21f);
  sVar1 = (short)cStack_32;
  sStack_38 = *(short *)(param_2 + 0x21a);
  uStack_3c = *(undefined4 *)(param_2 + 0x5c);
  cStack_31 = *(char *)(**(int **)(param_2 + 0x70) + 100);
  iVar2 = *(int *)(param_1 + 0x124);
  sStack_34 = sStack_38;
  iStack_30 = param_1;
  iStack_20 = param_2;
  sStack_10 = param_3;
  ClearPlace__10MenuWindowFv(param_1);
  if (sStack_10 != 0) {
    SetMessage__23CmdRingCustomFinalGoodsFP13CmdRingCustomsP12CmdGoodsIcon
              (iStack_30,iStack_20,0,iVar2);
    iVar2 = iVar2 + 0x1b0;
  }
  *(byte *)(iVar2 + 0x162) = *(byte *)(iVar2 + 0x162) & 0xfe | 1;
  *(byte *)(iVar2 + 0xe2) = *(byte *)(iVar2 + 0xe2) & 0xfe | 1;
  uStack_44 = *(undefined4 *)(iVar2 + 0x78);
  uStack_48 = *(undefined4 *)(iVar2 + 0x224);
  (**(code **)(*(int *)(iVar2 + 0x58) + 0x24))(uStack_48,uStack_44);
  sVar3 = 0;
  while( true ) {
    if (sStack_34 <= sVar1) break;
    if ((long)sVar1 != (long)cStack_31) {
      uStack_36 = GetRestRingItem__8CmdPartyFs(uStack_3c,sVar1);
      uStack_36 = uStack_36 & 0xff;
      if (uStack_36 != 0) {
        SetCSA__8FontItemFUc(iVar2 + 0x50,0);
        SetCSA__8FontItemFUc(iVar2 + 0xd0,0);
        *(byte *)(iVar2 + 0x21) = *(byte *)(iVar2 + 0x21) & 0xf7 | 8;
        uStack_40 = GetRegDat__9RegDatApiFiii(0x11,sVar1,0xffffffffffffffff);
        SetMessage__8MenuTextFPcUiUcUc(iVar2 + 0x50,uStack_40,*(byte *)(iVar2 + 0xa8) & 7,0,0);
        sprintf(auStack_50,*(undefined4 *)(*(int *)(iStack_20 + 0x24) + 0x40),uStack_36);
        SetMessage__8MenuTextFPcUiUcUc(iVar2 + 0xd0,auStack_50,*(byte *)(iVar2 + 0x128) & 7,1,0);
        *(short *)(iVar2 + 0x16) = sVar1;
        AddPlace__10MenuWindowFP9MenuPlace(iStack_30,iVar2);
        iVar2 = iVar2 + 0x1b0;
        sVar3 = sVar3 + 1;
      }
    }
    sVar1 = sVar1 + 1;
  }
  *(short *)(iStack_30 + 0xae) = sVar3;
  if (*(int *)(iStack_30 + 0x124) == iVar2) {
    SetMessage__23CmdRingCustomFinalGoodsFP13CmdRingCustomsP12CmdGoodsIcon
              (iStack_30,iStack_20,1,iVar2);
  }
  else {
    AddPriority__12MenuObjTableFP7MenuObj(iStack_30 + 0x18,iStack_30 + 0xf4);
  }
  AddPriority__12MenuObjTableFP7MenuObj(iStack_30 + 0x18,iStack_30 + 0xb4);
  *(int *)(*(int *)(iStack_30 + 0x40) + 0x38) = iStack_30 + 0xb4;
  SetScroll__10MenuWindowFss(iStack_30,0,0);
  return;
}

/* JP: 0x0046dd70  CmdRingCustomFinalGoods::Select(CmdRingCustom*, MenuGroup*, MenuGroup*, short)   [Select__23CmdRingCustomFinalGoodsFP13CmdRingCustomP9MenuGroupP9MenuGroups]  size=0x18c */
void Select__23CmdRingCustomFinalGoodsFP13CmdRingCustomP9MenuGroupP9MenuGroups
               (undefined8 param_1,int param_2,int param_3,int param_4,short param_5)

{
  short sVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  
  if (param_4 != 0) {
    uVar3 = FindPlace__9MenuGroupFs(param_4,10);
    SetCSA__8FontItemFUc(uVar3,0);
    uVar3 = FindPlace__9MenuGroupFs(param_4,0x14);
    SetCSA__8FontItemFUc(uVar3,0);
  }
  if (param_3 != 0) {
    sVar1 = *(short *)(param_3 + 0x16);
    uVar2 = *(undefined4 *)(param_2 + 100);
    if ((long)((ulong)*(byte *)(param_3 + 0x21) << 0x3c) < 0) {
      uVar3 = FindPlace__9MenuGroupFs(param_3,10);
      SetCSA__8FontItemFUc(uVar3,1);
      uVar3 = FindPlace__9MenuGroupFs(param_3,0x14);
      SetCSA__8FontItemFUc(uVar3,1);
    }
    if (param_5 != 0) {
      if (sVar1 < 0) {
        SetExplanation__7CmdNoteFPCce(uVar2,*(undefined4 *)(*(int *)(param_2 + 0x28) + 0x128));
      }
      else {
        uVar3 = GetRegDat__9RegDatApiFiii(0x22,sVar1,0xffffffffffffffff);
        SetExplanation__7CmdNoteFPCce(uVar2,uVar3);
      }
    }
  }
  return;
}

/* JP: 0x0046df00  CmdRingCustomFinalGoods::SetMessage(CmdRingCustom*, short, CmdGoodsIcon*)   [SetMessage__23CmdRingCustomFinalGoodsFP13CmdRingCustomsP12CmdGoodsIcon]  size=0x170 */
void SetMessage__23CmdRingCustomFinalGoodsFP13CmdRingCustomsP12CmdGoodsIcon
               (undefined4 param_1,int param_2,short param_3,int param_4)

{
  SetCSA__8FontItemFUc(param_4 + 0x50,0);
  SetCSA__8FontItemFUc(param_4 + 0xd0,0);
  *(byte *)(param_4 + 0x21) = *(byte *)(param_4 + 0x21) & 0xf7 | 8;
  (**(code **)(*(int *)(param_4 + 0x58) + 0x24))
            (*(undefined4 *)(param_4 + 0x174),*(undefined4 *)(param_4 + 0x78));
  SetMessage__8MenuTextFPcUiUcUc(param_4 + 0x50,
                  *(undefined4 *)
                   (((int)param_3 + 0x17U & 0xffff) * 0xc + *(int *)(param_2 + 0x28) + 0x10),
                  *(byte *)(param_4 + 0xa8) & 7,0,0);
  *(byte *)(param_4 + 0x162) = *(byte *)(param_4 + 0x162) & 0xfe;
  *(byte *)(param_4 + 0xe2) = *(byte *)(param_4 + 0xe2) & 0xfe;
  *(undefined2 *)(param_4 + 0x16) = 0xffff;
  AddPlace__10MenuWindowFP9MenuPlace(param_1,param_4);
  return;
}

/* JP: 0x0046e070  CmdRingCustomFinalGoods::~CmdRingCustomFinalGoods()   [@24@__dt__23CmdRingCustomFinalGoodsFv]  size=0x8 */
undefined4 * _24___dt__23CmdRingCustomFinalGoodsFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -6;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-4] = &__vt__23CmdRingCustomFinalGoods;
    *param_1 = 0x408944;
    param_1[3] = 0x408950;
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

/* JP: 0x0046e080  CmdRingCustomFinalGoods::~CmdRingCustomFinalGoods()   [@36@__dt__23CmdRingCustomFinalGoodsFv]  size=0x8 */
undefined4 * _36___dt__23CmdRingCustomFinalGoodsFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -9;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-7] = &__vt__23CmdRingCustomFinalGoods;
    param_1[-3] = 0x408944;
    *param_1 = 0x408950;
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
