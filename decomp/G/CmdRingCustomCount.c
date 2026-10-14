/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdRingCustomCount   functions: 8
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdRingCustomCount.md).
 */

/* JP: 0x0049f210  CmdRingCustomCount::CmdRingCustomCount()   [__ct__18CmdRingCustomCountFv]  size=0x94 */
int __ct__18CmdRingCustomCountFv(int param_1)

{
  __ct__9CmdWindowFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__18CmdRingCustomCount;
  *(undefined4 *)(param_1 + 0x18) = 0x409584;
  *(undefined4 *)(param_1 + 0x24) = 0x409590;
  __ct__8FontDrawFv(param_1 + 0xb4);
  __construct_array(param_1 + 0xf4,0x454640,0x450670,0x150,5);
  return param_1;
}

/* JP: 0x0049f2b0  CmdRingCustomCount::~CmdRingCustomCount()   [__dt__18CmdRingCustomCountFv]  size=0xc4 */
int __dt__18CmdRingCustomCountFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__18CmdRingCustomCount;
    *(undefined4 *)(param_1 + 0x18) = 0x409584;
    *(undefined4 *)(param_1 + 0x24) = 0x409590;
    __destroy_arr(param_1 + 0xf4,0x450670,0x150,5);
    __dt__8FontDrawFv(param_1 + 0xb4,0xffffffffffffffff);
    __dt__9CmdWindowFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x0049f380  CmdRingCustomCount::CreateScene(CmdRingCustom*)   [CreateScene__18CmdRingCustomCountFP13CmdRingCustom]  size=0x144 */
void CreateScene__18CmdRingCustomCountFP13CmdRingCustom(int param_1,undefined4 param_2)

{
  int iVar1;
  short sVar2;
  undefined4 uStack_24;
  
  SetData__9MenuSceneFUsP8FontDraw(param_2,3,param_1 + 0xb4);
  iVar1 = param_1 + 0xf4;
  uStack_24 = 0.0;
  for (sVar2 = 0; sVar2 < 5; sVar2 = sVar2 + 1) {
    SetData__9MenuSceneFUsP8MenuText(param_2,10,iVar1 + 0x50);
    SetData__9MenuSceneFUsP8MenuText(param_2,0xb,iVar1 + 0xd0);
    AddPlace__9MenuGroupFP9MenuPlace(iVar1,iVar1 + 0x50);
    AddPlace__9MenuGroupFP9MenuPlace(iVar1,iVar1 + 0xd0);
    SetData__9MenuSceneFUsP9MenuGroup(param_2,1,iVar1);
    *(undefined2 *)(iVar1 + 0x1c) = 0;
    *(short *)(iVar1 + 0x1e) = sVar2;
    (**(code **)(*(int *)(iVar1 + 8) + 0x24))(0,uStack_24);
    uStack_24 = uStack_24 + *(float *)(iVar1 + 0x30);
    iVar1 = iVar1 + 0x150;
  }
  SetData__9MenuSceneFUsP10MenuWindow(param_2,3,param_1);
  AddOT__7MenuObjFv(param_1);
  return;
}

/* JP: 0x0049f4d0  CmdRingCustomCount::UpdateScene(CmdRingCustom*)   [UpdateScene__18CmdRingCustomCountFP13CmdRingCustom]  size=0x434 */
void UpdateScene__18CmdRingCustomCountFP13CmdRingCustom(int param_1,int param_2)

{
  bool bVar1;
  undefined4 uVar2;
  int *piVar3;
  ushort uVar4;
  ushort uVar5;
  short sVar6;
  ushort uVar7;
  ushort uVar8;
  short sVar9;
  int iVar10;
  
  ClearPlace__10MenuWindowFv(param_1);
  ClearImage__8FontDrawFv(param_1 + 0xb4);
  uVar2 = *(undefined4 *)(param_2 + 0x5c);
  piVar3 = *(int **)(param_2 + 0x70);
  uVar4 = *(byte *)(*piVar3 + 0x58) & 7;
  uVar5 = (ushort)(((ulong)*(byte *)(*piVar3 + 0x58) << 0x3a) >> 0x3d);
  sVar6 = GetExpansionRingItem__5CmdPCFv(piVar3);
  uVar7 = GetRestRingItem__8CmdPartyFs(uVar2,0);
  uVar7 = uVar4 + (uVar7 & 0xff);
  uVar8 = uVar4 + 2;
  if (*(char *)(*piVar3 + 2) == '\v') {
    uVar8 = uVar4 + 1;
  }
  if (uVar8 < uVar7) {
    uVar7 = uVar8;
  }
  if (uVar7 < uVar5) {
    uVar7 = uVar5;
  }
  iVar10 = param_1 + 0xf4;
  for (; 0 < (short)uVar7; uVar7 = uVar7 - 1) {
    sVar9 = -sVar6;
    *(byte *)(iVar10 + 0xe2) = *(byte *)(iVar10 + 0xe2) & 0xfe;
    bVar1 = uVar7 == uVar5;
    if (bVar1) {
      *(int *)(param_1 + 0x784) = iVar10;
    }
    SetMessage__8MenuTextFPcUiUcUc(iVar10 + 0x50,
                    *(undefined4 *)
                     (((int)(short)uVar7 + 0xeU & 0xffff) * 0xc + *(int *)(param_2 + 0x28) + 0x10),
                    *(byte *)(iVar10 + 0xa8) & 7,0,1);
    OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(param_1 + 0xb4,iVar10 + 0x50,((ulong)*(byte *)(iVar10 + 0xa8) & 0xf) >> 3,0);
    if ((short)uVar4 < (short)uVar7) {
      SetMessage__8MenuTextFPcUiUcUc(iVar10 + 0xd0,
                      *(undefined4 *)
                       (((int)(short)(uVar7 - uVar4) + 2U & 0xffff) * 8 + *(int *)(param_2 + 0x24) +
                       0x10),*(byte *)(iVar10 + 0x128) & 7,0,1);
      OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(param_1 + 0xb4,iVar10 + 0xd0,((ulong)*(byte *)(iVar10 + 0x128) & 0xf) >> 3,0);
      *(byte *)(iVar10 + 0xe2) = *(byte *)(iVar10 + 0xe2) & 0xfe | 1;
      sVar9 = (uVar7 - uVar4) - sVar6;
    }
    *(ushort *)(iVar10 + 0x16) = uVar7;
    *(short *)(iVar10 + 0x22) = sVar9;
    *(ushort *)(iVar10 + 0xce) = (ushort)bVar1;
    SetCSA__8FontItemFUc(iVar10 + 0x50,bVar1);
    *(ushort *)(iVar10 + 0x14e) = (ushort)bVar1;
    SetCSA__8FontItemFUc(iVar10 + 0xd0,bVar1);
    AddPlace__10MenuWindowFP9MenuPlace(param_1,iVar10);
    iVar10 = iVar10 + 0x150;
  }
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0xb4);
  return;
}

/* JP: 0x0049f910  CmdRingCustomCount::Select(CmdRingCustom*, MenuPlace*, MenuPlace*, short)   [Select__18CmdRingCustomCountFP13CmdRingCustomP9MenuPlaceP9MenuPlaces]  size=0x234 */
void Select__18CmdRingCustomCountFP13CmdRingCustomP9MenuPlaceP9MenuPlaces
               (int param_1,int param_2,int param_3,int param_4,short param_5)

{
  short sVar1;
  undefined4 uVar2;
  int *piVar3;
  int iVar4;
  
  if (param_4 != 0) {
    iVar4 = param_1 + *(short *)(param_4 + 0x1e) * 0x150;
    SetCSA__8FontItemFUc(iVar4 + 0x144,*(ushort *)(iVar4 + 0x1c2) & 0xff);
    SetCSA__8FontItemFUc(iVar4 + 0x1c4,*(ushort *)(iVar4 + 0x242) & 0xff);
  }
  if (param_3 != 0) {
    uVar2 = *(undefined4 *)(param_2 + 100);
    piVar3 = *(int **)(param_2 + 0x70);
    sVar1 = *(short *)(param_3 + 0x16);
    param_1 = param_1 + *(short *)(param_3 + 0x1e) * 0x150;
    SetCSA__8FontItemFUc(param_1 + 0x144,1);
    SetCSA__8FontItemFUc(param_1 + 0x1c4,1);
    if (param_5 != 0) {
      SetExplanation__7CmdNoteFPCce
                (uVar2,*(undefined4 *)
                        (((int)sVar1 + 0xeU & 0xffff) * 0xc + *(int *)(param_2 + 0x28) + 0x14));
    }
    *(byte *)(*piVar3 + 0x58) = *(byte *)(*piVar3 + 0x58) & 199 | (byte)(((int)sVar1 & 7U) << 3);
    UpdateInfo__13CmdRingCustomFssss(param_2,0,0,1,-*(short *)(param_3 + 0x22));
  }
  return;
}

/* JP: 0x0049fb50  CmdRingCustomCount::SetClut(short)   [SetClut__18CmdRingCustomCountFs]  size=0xbc */
void SetClut__18CmdRingCustomCountFs(int param_1,ushort param_2)

{
  param_1 = param_1 + *(short *)(*(int *)(param_1 + 0x784) + 0x1e) * 0x150;
  *(ushort *)(param_1 + 0x1c2) = param_2;
  SetCSA__8FontItemFUc(param_1 + 0x144,param_2 & 0xff);
  *(ushort *)(param_1 + 0x242) = param_2;
  SetCSA__8FontItemFUc(param_1 + 0x1c4,param_2 & 0xff);
  return;
}

/* JP: 0x0049fc10  CmdRingCustomCount::~CmdRingCustomCount()   [@24@__dt__18CmdRingCustomCountFv]  size=0x8 */
undefined4 * _24___dt__18CmdRingCustomCountFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -6;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-4] = &__vt__18CmdRingCustomCount;
    *param_1 = 0x409584;
    param_1[3] = 0x409590;
    __destroy_arr(param_1 + 0x37,0x450670,0x150,5);
    __dt__8FontDrawFv(param_1 + 0x27,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}

/* JP: 0x0049fc20  CmdRingCustomCount::~CmdRingCustomCount()   [@36@__dt__18CmdRingCustomCountFv]  size=0x8 */
undefined4 * _36___dt__18CmdRingCustomCountFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -9;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-7] = &__vt__18CmdRingCustomCount;
    param_1[-3] = 0x409584;
    *param_1 = 0x409590;
    __destroy_arr(param_1 + 0x34,0x450670,0x150,5);
    __dt__8FontDrawFv(param_1 + 0x24,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}
