/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdRingCustomInfo   functions: 6
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdRingCustomInfo.md).
 */

/* JP: 0x0046cab0  CmdRingCustomInfo::CmdRingCustomInfo()   [__ct__17CmdRingCustomInfoFv]  size=0x134 */
int __ct__17CmdRingCustomInfoFv(int param_1)

{
  __ct__9CmdWindowFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__17CmdRingCustomInfo;
  *(undefined4 *)(param_1 + 0x18) = 0x408904;
  *(undefined4 *)(param_1 + 0x24) = 0x408910;
  __ct__11MenuTextureFv(param_1 + 0xb8);
  __ct__11SendOnLocalFv(param_1 + 0xf8);
  __ct__11SendOnLocalFv(param_1 + 0x128);
  __ct__8FontDrawFv(param_1 + 0x158);
  __ct__8FontDrawFv(param_1 + 0x198);
  __construct_array(param_1 + 0x1d8,0x27bfd0,0x27c030,0x80,2);
  __construct_array(param_1 + 0x2d8,0x450610,0x4502f0,0x1b0,2);
  __ct__11MenuPolygonFv(param_1 + 0x638);
  __construct_array(param_1 + 0x6bc,0x266140,0x2661a0,0x60,10);
  return param_1;
}

/* JP: 0x0046cbf0  CmdRingCustomInfo::~CmdRingCustomInfo()   [__dt__17CmdRingCustomInfoFv]  size=0x16c */
int __dt__17CmdRingCustomInfoFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__17CmdRingCustomInfo;
    *(undefined4 *)(param_1 + 0x18) = 0x408904;
    *(undefined4 *)(param_1 + 0x24) = 0x408910;
    __destroy_arr(param_1 + 0x6bc,0x2661a0,0x60,10);
    __dt__11MenuPolygonFv(param_1 + 0x638,0xffffffffffffffff);
    __destroy_arr(param_1 + 0x2d8,0x4502f0,0x1b0,2);
    __destroy_arr(param_1 + 0x1d8,0x27c030,0x80,2);
    __dt__8FontDrawFv(param_1 + 0x198,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x158,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x128,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0xf8,0xffffffffffffffff);
    __dt__11MenuTextureFv(param_1 + 0xb8,0xffffffffffffffff);
    __dt__9CmdWindowFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x0046cd60  CmdRingCustomInfo::CreateScene(CmdRingCustom*)   [CreateScene__17CmdRingCustomInfoFP13CmdRingCustom]  size=0x4c0 */
void CreateScene__17CmdRingCustomInfoFP13CmdRingCustom(int param_1,int param_2)

{
  short sVar1;
  uint uVar2;
  int iVar3;
  undefined4 uStack_34;
  
  SetData__9MenuSceneFUsP8FontDraw(param_2,4,param_1 + 0x158);
  SetData__9MenuSceneFUsP8FontDraw(param_2,5,param_1 + 0x198);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0x158);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0x198);
  SetData__9MenuSceneFUsP11MenuPolygon(param_2,0,param_1 + 0x638);
  AddPlace__10MenuWindowFP9MenuPlace(param_1,param_1 + 0x638);
  iVar3 = param_1 + 0x6bc;
  sVar1 = 2;
  while( true ) {
    if (0xb < sVar1) break;
    SetData__9MenuSceneFUsP10MenuSprite(param_2,sVar1,iVar3);
    AddPlace__10MenuWindowFP9MenuPlace(param_1,iVar3);
    sVar1 = sVar1 + 1;
    iVar3 = iVar3 + 0x60;
  }
  iVar3 = param_1 + 0x1d8;
  sVar1 = 6;
  while( true ) {
    if (7 < sVar1) break;
    SetData__9MenuSceneFUsP8MenuText(param_2,sVar1,iVar3);
    SetMessage__8MenuTextFPcUiUcUc(iVar3,*(undefined4 *)
                           ((uint)*(ushort *)(iVar3 + 0x22) * 8 + *(int *)(param_2 + 0x24) + 0x10),
                    *(byte *)(iVar3 + 0x58) & 7,0,1);
    OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(param_1 + 0x158,iVar3,((ulong)*(byte *)(iVar3 + 0x58) & 0xf) >> 3,0);
    AddPlace__10MenuWindowFP9MenuPlace(param_1,iVar3);
    sVar1 = sVar1 + 1;
    iVar3 = iVar3 + 0x80;
  }
  uStack_34 = 0.0;
  for (uVar2 = param_1 + 0x2d8; uVar2 < param_1 + 0x638U; uVar2 = uVar2 + 0x1b0) {
    SetData__9MenuSceneFUsP10MenuSprite(param_2,1,uVar2 + 0x150);
    SetData__9MenuSceneFUsP8MenuText(param_2,8,uVar2 + 0x50);
    SetData__9MenuSceneFUsP8MenuText(param_2,9,uVar2 + 0xd0);
    AddPlace__9MenuGroupFP9MenuPlace(uVar2,uVar2 + 0x150);
    AddPlace__9MenuGroupFP9MenuPlace(uVar2,uVar2 + 0x50);
    AddPlace__9MenuGroupFP9MenuPlace(uVar2,uVar2 + 0xd0);
    SetIcon__10MenuCommonFcP10MenuSprite((char)*(undefined2 *)(uVar2 + 0x172),uVar2 + 0x150);
    SetData__9MenuSceneFUsP9MenuGroup(param_2,2,uVar2);
    (**(code **)(*(int *)(uVar2 + 8) + 0x24))
              (*(undefined4 *)(uVar2 + 0x24),uStack_34 + *(float *)(uVar2 + 0x28));
    AddPlace__10MenuWindowFP9MenuPlace(param_1,uVar2);
    uStack_34 = uStack_34 + *(float *)(uVar2 + 0x30);
  }
  Create__11MenuTextureFPUc6GS_PSMUii(param_1 + 0xb8,*(undefined4 *)(*(int *)(param_2 + 0x54) + 0x1c),0x30,0,0);
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(param_1 + 0xf8,param_1 + 0xd0,*(undefined4 *)(param_1 + 0xcc),1,0xffffffffffffffff
                 );
  *(short *)(param_1 + 0x10c) = *(short *)(param_1 + 0x6d0) + -1;
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0xf8);
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(param_1 + 0x128,0x4216b0,uRam004216ac,1,0xffffffffffffffff);
  *(short *)(param_1 + 0x13c) = *(short *)(param_1 + 0x43c) + -1;
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0x128);
  SetData__9MenuSceneFUsP10MenuWindow(param_2,4,param_1);
  AddOT__7MenuObjFv(param_1);
  return;
}

/* JP: 0x0046d220  CmdRingCustomInfo::UpdateScene(CmdRingCustom*, short, short, short)   [UpdateScene__17CmdRingCustomInfoFP13CmdRingCustomsss]  size=0x2d4 */
void UpdateScene__17CmdRingCustomInfoFP13CmdRingCustomsss
               (int param_1,int param_2,short param_3,short param_4,short param_5)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined1 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  uint uVar6;
  uint uVar7;
  undefined1 auStack_58 [8];
  int iStack_50;
  int iStack_40;
  short sStack_30;
  short sStack_20;
  short sStack_10;
  
  uVar1 = *(undefined4 *)(param_2 + 0x5c);
  uVar4 = 7;
  if (param_5 < 1) {
    if (param_5 < 0) {
      uVar4 = 9;
    }
  }
  else {
    uVar4 = 8;
  }
  iStack_50 = param_1;
  iStack_40 = param_2;
  sStack_30 = param_3;
  sStack_20 = param_4;
  sStack_10 = param_5;
  ClearImage__8FontDrawFv(param_1 + 0x198);
  uVar6 = iStack_50 + 0x2d8;
  uVar7 = uVar6 + sStack_20 * 0x1b0;
  for (; uVar6 < uVar7; uVar6 = uVar6 + 0x1b0) {
    uVar5 = GetRegDat__9RegDatApiFiii(0x11,sStack_30,0xffffffffffffffff);
    SetMessage__8MenuTextFPcUiUcUc(uVar6 + 0x50,uVar5,*(byte *)(uVar6 + 0xa8) & 7,0,1);
    OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_50 + 0x198,uVar6 + 0x50,((ulong)*(byte *)(uVar6 + 0xa8) & 0xf) >> 3,0);
    uVar2 = *(undefined4 *)(*(int *)(iStack_40 + 0x24) + 0x40);
    uVar3 = GetRestRingItem__8CmdPartyFs(uVar1,sStack_30);
    sprintf(auStack_58,uVar2,uVar3);
    SetMessage__8MenuTextFPcUiUcUc(uVar6 + 0xd0,auStack_58,*(byte *)(uVar6 + 0x128) & 7,0,1);
    OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_50 + 0x198,uVar6 + 0xd0,((ulong)*(byte *)(uVar6 + 0x128) & 0xf) >> 3,0);
    SetCSA__8FontItemFUc(uVar6 + 0xd0,uVar4);
    sStack_30 = sStack_30 + 1;
  }
  *(byte *)(iStack_50 + 0x4ea) = *(byte *)(iStack_50 + 0x4ea) & 0xfe | 1;
  *(byte *)(iStack_50 + 0x5ea) = *(byte *)(iStack_50 + 0x5ea) & 0xfe | 1;
  *(byte *)(iStack_50 + 0x56a) = *(byte *)(iStack_50 + 0x56a) & 0xfe | 1;
  if (sStack_20 < 2) {
    *(byte *)(iStack_50 + 0x4ea) = *(byte *)(iStack_50 + 0x4ea) & 0xfe;
    *(byte *)(iStack_50 + 0x5ea) = *(byte *)(iStack_50 + 0x5ea) & 0xfe;
    *(byte *)(iStack_50 + 0x56a) = *(byte *)(iStack_50 + 0x56a) & 0xfe;
  }
  return;
}

/* JP: 0x0046d500  CmdRingCustomInfo::~CmdRingCustomInfo()   [@24@__dt__17CmdRingCustomInfoFv]  size=0x8 */
undefined4 * _24___dt__17CmdRingCustomInfoFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -6;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-4] = &__vt__17CmdRingCustomInfo;
    *param_1 = 0x408904;
    param_1[3] = 0x408910;
    __destroy_arr(param_1 + 0x1a9,0x2661a0,0x60,10);
    __dt__11MenuPolygonFv(param_1 + 0x188,0xffffffffffffffff);
    __destroy_arr(param_1 + 0xb0,0x4502f0,0x1b0,2);
    __destroy_arr(param_1 + 0x70,0x27c030,0x80,2);
    __dt__8FontDrawFv(param_1 + 0x60,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x50,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x44,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x38,0xffffffffffffffff);
    __dt__11MenuTextureFv(param_1 + 0x28,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}

/* JP: 0x0046d510  CmdRingCustomInfo::~CmdRingCustomInfo()   [@36@__dt__17CmdRingCustomInfoFv]  size=0x8 */
undefined4 * _36___dt__17CmdRingCustomInfoFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -9;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-7] = &__vt__17CmdRingCustomInfo;
    param_1[-3] = 0x408904;
    *param_1 = 0x408910;
    __destroy_arr(param_1 + 0x1a6,0x2661a0,0x60,10);
    __dt__11MenuPolygonFv(param_1 + 0x185,0xffffffffffffffff);
    __destroy_arr(param_1 + 0xad,0x4502f0,0x1b0,2);
    __destroy_arr(param_1 + 0x6d,0x27c030,0x80,2);
    __dt__8FontDrawFv(param_1 + 0x5d,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x4d,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x41,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x35,0xffffffffffffffff);
    __dt__11MenuTextureFv(param_1 + 0x25,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}
