/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdCrestDetail   functions: 6
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdCrestDetail.md).
 */

/* JP: 0x00498170  CmdCrestDetail::CmdCrestDetail()   [__ct__14CmdCrestDetailFv]  size=0x148 */
int __ct__14CmdCrestDetailFv(int param_1)

{
  __ct__9CmdWindowFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__14CmdCrestDetail;
  *(undefined4 *)(param_1 + 0x18) = 0x409454;
  *(undefined4 *)(param_1 + 0x24) = 0x409460;
  __ct__11SendOnLocalFv(param_1 + 0xb4);
  __ct__11SendOnLocalFv(param_1 + 0xe4);
  __ct__8FontDrawFv(param_1 + 0x114);
  __ct__8FontDrawFv(param_1 + 0x154);
  __ct__10MenuSpriteFv(param_1 + 0x194);
  __ct__8MenuTextFv(param_1 + 500);
  __ct__9MenuGroupFv(param_1 + 0x274);
  __construct_array(param_1 + 0x2c4,0x266140,0x2661a0,0x60,5);
  __ct__11MenuPolygonFv(param_1 + 0x4a4);
  __ct__8MenuTextFv(param_1 + 0x528);
  __ct__8MenuTextFv(param_1 + 0x5a8);
  __construct_array(param_1 + 0x628,0x4983a0,0x4982c0,0x5d0,4);
  return param_1;
}

/* JP: 0x00498440  CmdCrestDetail::~CmdCrestDetail()   [__dt__14CmdCrestDetailFv]  size=0x1ac */
int __dt__14CmdCrestDetailFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__14CmdCrestDetail;
    *(undefined4 *)(param_1 + 0x18) = 0x409454;
    *(undefined4 *)(param_1 + 0x24) = 0x409460;
    __destroy_arr(param_1 + 0x628,0x4982c0,0x5d0,4);
    if (param_1 != -0x274) {
      __dt__8MenuTextFv(param_1 + 0x5a8,0xffffffffffffffff);
      __dt__8MenuTextFv(param_1 + 0x528,0xffffffffffffffff);
      __dt__11MenuPolygonFv(param_1 + 0x4a4,0xffffffffffffffff);
      __destroy_arr(param_1 + 0x2c4,0x2661a0,0x60,5);
      __dt__9MenuGroupFv(param_1 + 0x274,0xffffffffffffffff);
    }
    __dt__8MenuTextFv(param_1 + 500,0xffffffffffffffff);
    __dt__10MenuSpriteFv(param_1 + 0x194,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x154,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x114,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0xe4,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0xb4,0xffffffffffffffff);
    __dt__9CmdWindowFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x004985f0  CmdCrestDetail::CreateScene(MenuScene*, MenuTexture*)   [CreateScene__14CmdCrestDetailFP9MenuSceneP11MenuTexture]  size=0x55c */
void CreateScene__14CmdCrestDetailFP9MenuSceneP11MenuTexture(int param_1,int param_2,int param_3)

{
  short sVar1;
  uint uVar2;
  int iVar3;
  short sVar4;
  undefined4 uStack_48;
  
  SetData__9MenuSceneFUsP8FontDraw(param_2,0,param_1 + 0x114);
  SetData__9MenuSceneFUsP8FontDraw(param_2,1,param_1 + 0x154);
  SetData__9MenuSceneFUsP10MenuSprite(param_2,0,param_1 + 0x194);
  SetData__9MenuSceneFUsP8MenuText(param_2,0,param_1 + 500);
  SetData__9MenuSceneFUsP11MenuPolygon(param_2,0,param_1 + 0x4a4);
  AddPlace__9MenuGroupFP9MenuPlace(param_1 + 0x274,param_1 + 0x4a4);
  iVar3 = param_1 + 0x2c4;
  sVar4 = 1;
  while( true ) {
    if (5 < sVar4) break;
    SetData__9MenuSceneFUsP10MenuSprite(param_2,sVar4,iVar3);
    AddPlace__9MenuGroupFP9MenuPlace(param_1 + 0x274,iVar3);
    sVar4 = sVar4 + 1;
    iVar3 = iVar3 + 0x60;
  }
  iVar3 = param_1 + 0x528;
  sVar4 = 1;
  while( true ) {
    if (2 < sVar4) break;
    SetData__9MenuSceneFUsP8MenuText(param_2,sVar4,iVar3);
    SetMessage__8MenuTextFPcUiUcUc(iVar3,*(undefined4 *)
                           ((uint)*(ushort *)(iVar3 + 0x22) * 8 + *(int *)(param_2 + 0x24) + 0x10),
                    *(byte *)(iVar3 + 0x58) & 7,0,1);
    OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(param_1 + 0x114,iVar3,((ulong)*(byte *)(iVar3 + 0x58) & 0xf) >> 3,0);
    AddPlace__9MenuGroupFP9MenuPlace(param_1 + 0x274,iVar3);
    sVar4 = sVar4 + 1;
    iVar3 = iVar3 + 0x80;
  }
  SetData__9MenuSceneFUsP9MenuGroup(param_2,0,param_1 + 0x274);
  sVar4 = 0;
  uStack_48 = 0.0;
  for (uVar2 = param_1 + 0x628; uVar2 < param_1 + 0x1d68U; uVar2 = uVar2 + 0x5d0) {
    iVar3 = uVar2 + 0x50;
    sVar1 = 1;
    while( true ) {
      if (10 < sVar1) break;
      SetData__9MenuSceneFUsP10MenuSprite(param_2,sVar1,iVar3);
      AddPlace__9MenuGroupFP9MenuPlace(uVar2,iVar3);
      sVar1 = sVar1 + 1;
      iVar3 = iVar3 + 0x60;
    }
    iVar3 = uVar2 + 0x450;
    sVar1 = 3;
    while( true ) {
      if (5 < sVar1) break;
      SetData__9MenuSceneFUsP8MenuText(param_2,sVar1,iVar3);
      AddPlace__9MenuGroupFP9MenuPlace(uVar2,iVar3);
      sVar1 = sVar1 + 1;
      iVar3 = iVar3 + 0x80;
    }
    SetData__9MenuSceneFUsP8FontDraw(param_2,2,uVar2 + 0x410);
    *(short *)(uVar2 + 0x424) = sVar4 + *(short *)(uVar2 + 0x424);
    *(short *)(uVar2 + 0x564) = sVar4 + *(short *)(uVar2 + 0x564) + 1;
    SetData__9MenuSceneFUsP9MenuGroup(param_2,1,uVar2);
    (**(code **)(*(int *)(uVar2 + 8) + 0x24))(0,uStack_48 + *(float *)(uVar2 + 0x28));
    AddPlace__10MenuWindowFP9MenuPlace(param_1,uVar2);
    uStack_48 = uStack_48 + *(float *)(uVar2 + 0x30);
    sVar4 = sVar4 + 2;
  }
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(param_1 + 0xb4,param_3 + 0x18,*(undefined4 *)(param_3 + 0x14),1,0xffffffffffffffff
                 );
  *(short *)(param_1 + 200) = *(short *)(param_1 + 0x2d8) + -1;
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(param_1 + 0xe4,0x4216b0,uRam004216ac,1,0xffffffffffffffff);
  *(short *)(param_1 + 0xf8) = *(short *)(param_1 + 0x1a8) + -1;
  SetData__9MenuSceneFUsP10MenuWindow(param_2,0,param_1);
  AddOT__7MenuObjFv(param_1);
  return;
}

/* JP: 0x00498b50  CmdCrestDetail::UpdateScene(MenuScene*, CmdParty*, MenuDataMagic*, short)   [UpdateScene__14CmdCrestDetailFP9MenuSceneP8CmdPartyP13MenuDataMagics]  size=0x464 */
void UpdateScene__14CmdCrestDetailFP9MenuSceneP8CmdPartyP13MenuDataMagics
               (int param_1,int param_2,int param_3,undefined8 param_4,short param_5)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  ulong uVar5;
  undefined8 uVar6;
  short *psVar7;
  undefined1 auStack_68 [8];
  undefined4 uStack_60;
  undefined4 uStack_5c;
  ushort uStack_56;
  ushort uStack_54;
  byte bStack_51;
  int iStack_50;
  int iStack_40;
  int iStack_30;
  short sStack_10;
  
  if (-1 < param_5) {
    iStack_50 = param_1;
    iStack_40 = param_2;
    iStack_30 = param_3;
    sStack_10 = param_5;
    ClearImage__8FontDrawFv(param_1 + 0x154);
    ClearPlace__10MenuWindowFv(iStack_50);
    iVar2 = GetRegDat__9RegDatApiFiii(0x37,sStack_10,0xffffffffffffffff);
    psVar7 = (short *)(iVar2 + 8);
    iVar3 = (int)sStack_10;
    if (sStack_10 < 0) {
      iVar3 = iVar3 + 7;
    }
    uVar5 = (long)sStack_10 & 7;
    uVar4 = (uint)uVar5;
    if (((long)sStack_10 < 0) && (uVar5 != 0)) {
      uVar4 = uVar4 - 8;
    }
    bStack_51 = (byte)((int)(uint)*(byte *)(*(int *)(iStack_30 + 8) + (iVar3 >> 3) + 0x16a) >>
                      (uVar4 & 0x1f)) & 1;
    uStack_54 = *(ushort *)(iVar2 + 6);
    uStack_5c = GetRegDat__9RegDatApiFiii(0xd,sStack_10,0xffffffffffffffff);
    SetMessage__8MenuTextFPcUiUcUc(iStack_50 + 500,uStack_5c,*(byte *)(iStack_50 + 0x24c) & 7,0,1);
    OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_50 + 0x154,iStack_50 + 500,
                    ((ulong)*(byte *)(iStack_50 + 0x24c) & 0xf) >> 3,0);
    AddPlace__10MenuWindowFP9MenuPlace(iStack_50,iStack_50 + 500);
    AddPlace__10MenuWindowFP9MenuPlace(iStack_50,iStack_50 + 0x194);
    iVar3 = iStack_50 + 0x628;
    for (uVar4 = 0; (int)uVar4 < 4; uVar4 = uVar4 + 1) {
      if ((-1 < *psVar7) && ((((uint)uStack_54 & 1 << (uVar4 & 0x1f)) == 0 || (bStack_51 != 0)))) {
        uStack_56 = *(ushort *)(iVar3 + 0x4f2);
        uVar1 = *(undefined4 *)((uint)uStack_56 * 8 + *(int *)(iStack_40 + 0x24) + 0x10);
        iVar2 = GetRegDat__9RegDatApiFiii(0x38,*psVar7,0xffffffffffffffff);
        sprintf(auStack_68,uVar1,*(undefined2 *)(iVar2 + 0x1e));
        uStack_60 = GetRegDat__9RegDatApiFiii(0xe,*psVar7,0xffffffffffffffff);
        SetMessage__8MenuTextFPcUiUcUc(iVar3 + 0x450,uStack_60,*(byte *)(iVar3 + 0x4a8) & 7,0,1);
        OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_50 + 0x154,iVar3 + 0x450,((ulong)*(byte *)(iVar3 + 0x4a8) & 0xf) >> 3
                        ,0);
        SetMessage__8MenuTextFPcUiUcUc(iVar3 + 0x4d0,auStack_68,*(byte *)(iVar3 + 0x528) & 7,0,1);
        OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_50 + 0x154,iVar3 + 0x4d0,((ulong)*(byte *)(iVar3 + 0x528) & 0xf) >> 3
                        ,0);
        ClearImage__8FontDrawFv(iVar3 + 0x410);
        uVar6 = GetRegDat__9RegDatApiFiii(0x1f,*psVar7,0xffffffffffffffff);
        SetMessage__8MenuTextFPcUiUcUc(iVar3 + 0x550,uVar6,*(byte *)(iVar3 + 0x5a8) & 7,0,1);
        OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iVar3 + 0x410,iVar3 + 0x550,((ulong)*(byte *)(iVar3 + 0x5a8) & 0xf) >> 3,0);
        AddPlace__10MenuWindowFP9MenuPlace(iStack_50,iVar3);
        AddPriority__12MenuObjTableFP7MenuObj(iStack_50 + 0x18,iVar3 + 0x410);
        iVar3 = iVar3 + 0x5d0;
      }
      psVar7 = psVar7 + 1;
    }
    AddPriority__12MenuObjTableFP7MenuObj(iStack_50 + 0x18,iStack_50 + 0x114);
    AddPriority__12MenuObjTableFP7MenuObj(iStack_50 + 0x18,iStack_50 + 0x154);
    AddPlace__10MenuWindowFP9MenuPlace(iStack_50,iStack_50 + 0x274);
    AddPriority__12MenuObjTableFP7MenuObj(iStack_50 + 0x18,iStack_50 + 0xb4);
    AddPriority__12MenuObjTableFP7MenuObj(iStack_50 + 0x18,iStack_50 + 0xe4);
  }
  return;
}

/* JP: 0x00498fc0  CmdCrestDetail::~CmdCrestDetail()   [@24@__dt__14CmdCrestDetailFv]  size=0x8 */
undefined4 * _24___dt__14CmdCrestDetailFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -6;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-4] = &__vt__14CmdCrestDetail;
    *param_1 = 0x409454;
    param_1[3] = 0x409460;
    __destroy_arr(param_1 + 0x184,0x4982c0,0x5d0,4);
    if (puVar1 != (undefined4 *)0xfffffd8c) {
      __dt__8MenuTextFv(param_1 + 0x164,0xffffffffffffffff);
      __dt__8MenuTextFv(param_1 + 0x144,0xffffffffffffffff);
      __dt__11MenuPolygonFv(param_1 + 0x123,0xffffffffffffffff);
      __destroy_arr(param_1 + 0xab,0x2661a0,0x60,5);
      __dt__9MenuGroupFv(param_1 + 0x97,0xffffffffffffffff);
    }
    __dt__8MenuTextFv(param_1 + 0x77,0xffffffffffffffff);
    __dt__10MenuSpriteFv(param_1 + 0x5f,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x4f,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x3f,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x33,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x27,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}

/* JP: 0x00498fd0  CmdCrestDetail::~CmdCrestDetail()   [@36@__dt__14CmdCrestDetailFv]  size=0x8 */
undefined4 * _36___dt__14CmdCrestDetailFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -9;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-7] = &__vt__14CmdCrestDetail;
    param_1[-3] = 0x409454;
    *param_1 = 0x409460;
    __destroy_arr(param_1 + 0x181,0x4982c0,0x5d0,4);
    if (puVar1 != (undefined4 *)0xfffffd8c) {
      __dt__8MenuTextFv(param_1 + 0x161,0xffffffffffffffff);
      __dt__8MenuTextFv(param_1 + 0x141,0xffffffffffffffff);
      __dt__11MenuPolygonFv(param_1 + 0x120,0xffffffffffffffff);
      __destroy_arr(param_1 + 0xa8,0x2661a0,0x60,5);
      __dt__9MenuGroupFv(param_1 + 0x94,0xffffffffffffffff);
    }
    __dt__8MenuTextFv(param_1 + 0x74,0xffffffffffffffff);
    __dt__10MenuSpriteFv(param_1 + 0x5c,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x4c,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x3c,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x30,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x24,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}
