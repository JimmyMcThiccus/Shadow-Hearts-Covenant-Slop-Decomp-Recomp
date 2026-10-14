/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdPCInfo   functions: 5
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdPCInfo.md).
 */

/* JP: 0x0048a930  CmdPCInfo::CmdPCInfo()   [__ct__9CmdPCInfoFv]  size=0x14c */
int __ct__9CmdPCInfoFv(int param_1)

{
  __ct__9MenuSceneFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__9CmdPCInfo;
  __ct__10MenuWindowFv(param_1 + 0x58);
  __ct__8FontDrawFv(param_1 + 0x10c);
  __ct__8FontDrawFv(param_1 + 0x14c);
  __construct_array(param_1 + 0x18c,0x27bfd0,0x27c030,0x80,4);
  __ct__8MenuTextFv(param_1 + 0x38c);
  __ct__8MenuTextFv(param_1 + 0x40c);
  __construct_array(param_1 + 0x48c,0x27bfd0,0x27c030,0x80,6);
  __construct_array(param_1 + 0x78c,0x27bfd0,0x27c030,0x80,3);
  __construct_array(param_1 + 0x90c,0x276640,0x2766d0,0x84,2);
  __ct__11SendOnLocalFv(param_1 + 0xa14);
  __ct__10MenuSpriteFv(param_1 + 0xa44);
  return param_1;
}

/* JP: 0x0048aa80  CmdPCInfo::~CmdPCInfo()   [__dt__9CmdPCInfoFv]  size=0x17c */
int __dt__9CmdPCInfoFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__9CmdPCInfo;
    __dt__10MenuSpriteFv(param_1 + 0xa44,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0xa14,0xffffffffffffffff);
    __destroy_arr(param_1 + 0x90c,0x2766d0,0x84,2);
    __destroy_arr(param_1 + 0x78c,0x27c030,0x80,3);
    __destroy_arr(param_1 + 0x48c,0x27c030,0x80,6);
    __dt__8MenuTextFv(param_1 + 0x40c,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1 + 0x38c,0xffffffffffffffff);
    __destroy_arr(param_1 + 0x18c,0x27c030,0x80,4);
    __dt__8FontDrawFv(param_1 + 0x14c,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x10c,0xffffffffffffffff);
    __dt__10MenuWindowFv(param_1 + 0x58,0xffffffffffffffff);
    __dt__9MenuSceneFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x0048ac00  CmdPCInfo::GetReady()   [GetReady__9CmdPCInfoFv]  size=0x560 */
undefined4 GetReady__9CmdPCInfoFv(int param_1)

{
  int iVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  
  SetData__9MenuSceneFUsP8FontDraw(param_1,0,param_1 + 0x10c);
  SetData__9MenuSceneFUsP8FontDraw(param_1,1,param_1 + 0x14c);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x70,param_1 + 0x10c);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x70,param_1 + 0x14c);
  SetData__9MenuSceneFUsP8MenuText(param_1,4,param_1 + 0x38c);
  AddPlace__10MenuWindowFP9MenuPlace(param_1 + 0x58,param_1 + 0x38c);
  SetData__9MenuSceneFUsP8MenuText(param_1,5,param_1 + 0x40c);
  AddPlace__10MenuWindowFP9MenuPlace(param_1 + 0x58,param_1 + 0x40c);
  iVar1 = param_1 + 0x18c;
  for (sVar2 = 0; sVar2 < 4; sVar2 = sVar2 + 1) {
    SetData__9MenuSceneFUsP8MenuText(param_1,sVar2,iVar1);
    SetMessage__8MenuTextFPcUiUcUc(iVar1,*(undefined4 *)
                           ((uint)*(ushort *)(iVar1 + 0x22) * 8 + *(int *)(param_1 + 0x24) + 0x10),
                    *(byte *)(iVar1 + 0x58) & 7,0,1);
    OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(param_1 + 0x10c,iVar1,((ulong)*(byte *)(iVar1 + 0x58) & 0xf) >> 3,0);
    AddPlace__10MenuWindowFP9MenuPlace(param_1 + 0x58,iVar1);
    iVar1 = iVar1 + 0x80;
  }
  iVar3 = param_1 + 0x48c;
  iVar4 = param_1 + 0x60c;
  iVar1 = param_1 + 0x78c;
  sVar2 = 1;
  while( true ) {
    if (3 < sVar2) break;
    uVar5 = *(undefined4 *)(param_1 + sVar2 * 0x80 + 0x1b4);
    SetData__9MenuSceneFUsP8MenuText(param_1,7,iVar1);
    SetMessage__8MenuTextFPcUiUcUc(iVar1,*(undefined4 *)
                           ((uint)*(ushort *)(iVar1 + 0x22) * 8 + *(int *)(param_1 + 0x24) + 0x10),
                    *(byte *)(iVar1 + 0x58) & 7,0,1);
    OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(param_1 + 0x10c,iVar1,((ulong)*(byte *)(iVar1 + 0x58) & 0xf) >> 3,0);
    (**(code **)(*(int *)(iVar1 + 8) + 0x24))(*(undefined4 *)(iVar1 + 0x24),uVar5);
    SetData__9MenuSceneFUsP8MenuText(param_1,6,iVar3);
    (**(code **)(*(int *)(iVar3 + 8) + 0x24))(*(undefined4 *)(iVar3 + 0x24),uVar5);
    SetData__9MenuSceneFUsP8MenuText(param_1,6,iVar4);
    (**(code **)(*(int *)(iVar4 + 8) + 0x24))
              (*(float *)(iVar1 + 0x24) + *(float *)(iVar1 + 0x2c) + 2.0,uVar5);
    AddPlace__10MenuWindowFP9MenuPlace(param_1 + 0x58,iVar3);
    AddPlace__10MenuWindowFP9MenuPlace(param_1 + 0x58,iVar4);
    AddPlace__10MenuWindowFP9MenuPlace(param_1 + 0x58,iVar1);
    iVar3 = iVar3 + 0x80;
    iVar4 = iVar4 + 0x80;
    iVar1 = iVar1 + 0x80;
    sVar2 = sVar2 + 1;
  }
  SetData__9MenuSceneFUsP11MenuPolygon(param_1,0,param_1 + 0x90c);
  SetData__9MenuSceneFUsP11MenuPolygon(param_1,1,param_1 + 0x990);
  AddPlace__10MenuWindowFP9MenuPlace(param_1 + 0x58,param_1 + 0x90c);
  AddPlace__10MenuWindowFP9MenuPlace(param_1 + 0x58,param_1 + 0x990);
  SetData__9MenuSceneFUsP10MenuSprite(param_1,0,param_1 + 0xa44);
  *(int *)(param_1 + 0xaa0) = param_1 + 0xa14;
  *(byte *)(param_1 + 0xa56) = *(byte *)(param_1 + 0xa56) & 0xdf;
  AddPlace__10MenuWindowFP9MenuPlace(param_1 + 0x58,param_1 + 0xa44);
  SetData__9MenuSceneFUsP10MenuWindow(param_1,0,param_1 + 0x58);
  AddOT__7MenuObjFv(param_1 + 0x58);
  if (1 < *(short *)(*(int *)(param_1 + 0x10) + 0xc6)) {
    CreateScrollMark__10MenuWindowFUc(param_1 + 0x58,0xc);
  }
  return 1;
}

/* JP: 0x0048b160  CmdPCInfo::DelayDelete()   [DelayDelete__9CmdPCInfoFv]  size=0x38 */
void DelayDelete__9CmdPCInfoFv(int param_1)

{
  ReleaseOT__7MenuObjFv(param_1 + 0x58);
  DelayDelete__17DelayDeleteObjectFv(param_1);
  return;
}

/* JP: 0x0048b1a0  CmdPCInfo::UpdateScene(CmdPC*, CmdPCStatus*)   [UpdateScene__9CmdPCInfoFP5CmdPCP11CmdPCStatus]  size=0x39c */
void UpdateScene__9CmdPCInfoFP5CmdPCP11CmdPCStatus(int param_1,int *param_2,undefined2 *param_3)

{
  int iVar1;
  short sVar2;
  undefined2 *puVar3;
  undefined1 auStack_80 [24];
  undefined4 uStack_68;
  int iStack_64;
  int iStack_60;
  int iStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  int iStack_48;
  int iStack_44;
  int iStack_40;
  ushort uStack_3a;
  ushort uStack_38;
  ushort uStack_36;
  ushort uStack_34;
  undefined1 uStack_32;
  byte bStack_31;
  int iStack_30;
  int *piStack_20;
  undefined2 *puStack_10;
  
  iStack_30 = param_1;
  piStack_20 = param_2;
  puStack_10 = param_3;
  ClearImage__8FontDrawFv(param_1 + 0x14c);
  iStack_48 = *piStack_20 + 10;
  iStack_40 = iStack_48;
  SetMessage__8MenuTextFPcUiUcUc(iStack_30 + 0x38c,iStack_48,*(byte *)(iStack_30 + 0x3e4) & 7,0,1);
  OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_30 + 0x14c,iStack_30 + 0x38c,
                  ((ulong)*(byte *)(iStack_30 + 0x3e4) & 0xf) >> 3,0);
  uStack_32 = *(undefined1 *)(*piStack_20 + 3);
  uStack_38 = *(ushort *)(iStack_30 + 0x42e);
  uStack_50 = *(undefined4 *)((uint)uStack_38 * 8 + *(int *)(iStack_30 + 0x24) + 0x10);
  uStack_4c = uStack_50;
  uStack_34 = uStack_38;
  sprintf(auStack_80,uStack_50,uStack_32);
  SetMessage__8MenuTextFPcUiUcUc(iStack_30 + 0x40c,auStack_80,*(byte *)(iStack_30 + 0x464) & 7,0,1);
  OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_30 + 0x14c,iStack_30 + 0x40c,
                  ((ulong)*(byte *)(iStack_30 + 0x464) & 0xf) >> 3,0);
  iVar1 = iStack_30 + 0x48c;
  sVar2 = 0;
  puVar3 = puStack_10;
  while( true ) {
    puVar3 = puVar3 + 1;
    if (5 < sVar2) break;
    uStack_3a = *(ushort *)(iVar1 + 0x22);
    uStack_58 = *(undefined4 *)((uint)uStack_3a * 8 + *(int *)(iStack_30 + 0x24) + 0x10);
    uStack_54 = uStack_58;
    uStack_36 = uStack_3a;
    sprintf(auStack_80,uStack_58,*puVar3);
    SetMessage__8MenuTextFPcUiUcUc(iVar1,auStack_80,*(byte *)(iVar1 + 0x58) & 7,0,1);
    OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_30 + 0x14c,iVar1,((ulong)*(byte *)(iVar1 + 0x58) & 0xf) >> 3,0);
    SetCSA__8FontItemFUc(iVar1,(*(uint *)(puStack_10 + 0xe) >> (((int)sVar2 & 0xfU) << 1) & 3) + 7);
    sVar2 = sVar2 + 1;
    iVar1 = iVar1 + 0x80;
  }
  SetParameter__7CmdMenuFP8MenuTextss(iStack_30 + 0x48c,puStack_10[1],puStack_10[4]);
  SetParameter__7CmdMenuFP8MenuTextss(iStack_30 + 0x50c,puStack_10[2],puStack_10[5]);
  iStack_44 = piStack_20[0xc];
  iStack_64 = iStack_44 + 0x20;
  uStack_68 = *(undefined4 *)(iStack_44 + 0x34);
  iStack_60 = iStack_64;
  iStack_5c = iStack_64;
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(iStack_30 + 0xa14,iStack_44 + 0x38,uStack_68,1,0xffffffffffffffff);
  if (*(int *)(iStack_30 + 0x9c) != 0) {
    bStack_31 = *(byte *)(*(int *)(iStack_30 + 0x9c) + 0x83) & 0xf;
    SetArea__10ScrollMarkFUcffff(*(undefined4 *)(iStack_30 + 0x3b0),*(undefined4 *)(iStack_30 + 0x3b4),
                    *(undefined4 *)(iStack_30 + 0x3b8),*(undefined4 *)(iStack_30 + 0x3bc),
                    *(int *)(iStack_30 + 0x9c),bStack_31);
  }
  return;
}
