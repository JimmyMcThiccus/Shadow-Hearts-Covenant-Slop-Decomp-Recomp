/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdStatus   functions: 7
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdStatus.md).
 */

/* JP: 0x0044aab0  CmdStatus::CmdStatus()   [__ct__9CmdStatusFv]  size=0x10c */
int __ct__9CmdStatusFv(int param_1)

{
  __ct__15CmdPrivateSceneFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__9CmdStatus;
  __ct__10MenuWindowFv(param_1 + 0x5c);
  __ct__8FontDrawFv(param_1 + 0x110);
  __construct_array(param_1 + 0x150,0x44ac40,0x44abc0,0x100,9);
  __ct__8MenuTextFv(param_1 + 0xa50);
  __ct__8MenuTextFv(param_1 + 0xad0);
  __ct__8MenuTextFv(param_1 + 0xb50);
  __ct__8MenuTextFv(param_1 + 0xbd0);
  __construct_array(param_1 + 0xc50,0x276640,0x2766d0,0x84,2);
  __ct__11CmdSubTitleFv(param_1 + 0xd58);
  return param_1;
}

/* JP: 0x0044ac80  CmdStatus::~CmdStatus()   [__dt__9CmdStatusFv]  size=0x15c */
int __dt__9CmdStatusFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__9CmdStatus;
    __dt__11CmdSubTitleFv(param_1 + 0xd58,0xffffffffffffffff);
    __destroy_arr(param_1 + 0xc50,0x2766d0,0x84,2);
    if (param_1 != -0xb50) {
      __dt__8MenuTextFv(param_1 + 0xbd0,0xffffffffffffffff);
      __dt__8MenuTextFv(param_1 + 0xb50,0xffffffffffffffff);
    }
    if (param_1 != -0xa50) {
      __dt__8MenuTextFv(param_1 + 0xad0,0xffffffffffffffff);
      __dt__8MenuTextFv(param_1 + 0xa50,0xffffffffffffffff);
    }
    __destroy_arr(param_1 + 0x150,0x44abc0,0x100,9);
    __dt__8FontDrawFv(param_1 + 0x110,0xffffffffffffffff);
    __dt__10MenuWindowFv(param_1 + 0x5c,0xffffffffffffffff);
    __dt__15CmdPrivateSceneFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x0044ade0  CmdStatus::GetReady()   [GetReady__9CmdStatusFv]  size=0x31c */
undefined4 GetReady__9CmdStatusFv(int param_1)

{
  int iVar1;
  uint uVar2;
  
  *(undefined4 *)(param_1 + 0xf20) = *(undefined4 *)(*(int *)(param_1 + 0x58) + 0x60);
  *(undefined4 *)(param_1 + 0x18) = *(undefined4 *)(*(int *)(param_1 + 0x58) + 0x18);
  SetData__9MenuSceneFUsP8FontDraw(param_1,0,param_1 + 0x110);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x74,param_1 + 0x110);
  iVar1 = param_1 + 0x150;
  for (uVar2 = 0; (int)uVar2 < 0x14; uVar2 = uVar2 + 2) {
    SetData__9MenuSceneFUsP8MenuText(param_1,uVar2 & 0xffff,iVar1);
    SetData__9MenuSceneFUsP8MenuText(param_1,uVar2 + 1 & 0xffff,iVar1 + 0x80);
    SetMessage__8MenuTextFPcUiUcUc(iVar1,*(undefined4 *)
                           ((uint)*(ushort *)(iVar1 + 0x22) * 8 + *(int *)(param_1 + 0x24) + 0x10),
                    *(byte *)(iVar1 + 0x58) & 7,0,0);
    AddPlace__10MenuWindowFP9MenuPlace(param_1 + 0x5c,iVar1);
    AddPlace__10MenuWindowFP9MenuPlace(param_1 + 0x5c,iVar1 + 0x80);
    iVar1 = iVar1 + 0x100;
  }
  SetData__9MenuSceneFUsP11MenuPolygon(param_1,0,param_1 + 0xc50);
  SetData__9MenuSceneFUsP11MenuPolygon(param_1,1,param_1 + 0xcd4);
  AddPlace__10MenuWindowFP9MenuPlace(param_1 + 0x5c,param_1 + 0xc50);
  AddPlace__10MenuWindowFP9MenuPlace(param_1 + 0x5c,param_1 + 0xcd4);
  SetData__9MenuSceneFUsP10MenuWindow(param_1,0,param_1 + 0x5c);
  AddOT__7MenuObjFv(param_1 + 0x5c);
  Initialize__9MenuSceneFPUcP9BufMemory(param_1 + 0xd58,*(undefined4 *)(*(int *)(*(int *)(param_1 + 0x58) + 0x54) + 100),0
                 );
  Create__11CmdSubTitleFi(param_1 + 0xd58,1);
  Reset__11CmdSubTitleFv(param_1 + 0xd58);
  SetTitle__11CmdSubTitleFii(param_1 + 0xd58,0,0xd);
  Open__10MenuWindowFUci(param_1 + 0xdb0,*(byte *)(param_1 + 0xe60) & 7,
                  *(undefined4 *)(*(int *)(param_1 + 0xde4) + 0x10));
  SetTitle__11CmdTitleLogFPUci
            (*(undefined4 *)(param_1 + 0xf20),*(undefined4 *)(*(int *)(param_1 + 0x54) + 0x10),0xb);
  Open__11CmdTitleLogFv(*(undefined4 *)(param_1 + 0xf20));
  return 1;
}

/* JP: 0x0044b100  CmdStatus::SafeDelayDelete()   [SafeDelayDelete__9CmdStatusFv]  size=0x50 */
void SafeDelayDelete__9CmdStatusFv(int param_1)

{
  ReleaseOT__7MenuObjFv(param_1 + 0x5c);
  ReleaseOT__7MenuObjFv(param_1 + 0xdb0);
  (**(code **)(*(int *)(param_1 + 8) + 0xc))();
  return;
}

/* JP: 0x0044b150  CmdStatus::Close()   [Close__9CmdStatusFv]  size=0x74 */
void Close__9CmdStatusFv(int param_1)

{
  Close__10MenuWindowFUci(param_1 + 0x5c,((ulong)*(byte *)(param_1 + 0x10c) & 0x3f) >> 3,
                  *(undefined4 *)(*(int *)(param_1 + 0x90) + 0x14));
  Close__10MenuWindowFUci(param_1 + 0xdb0,((ulong)*(byte *)(param_1 + 0xe60) & 0x3f) >> 3,
                  *(undefined4 *)(*(int *)(param_1 + 0xde4) + 0x14));
  return;
}

/* JP: 0x0044b1d0  CmdStatus::Update(short)   [Update__9CmdStatusFs]  size=0x514 */
void Update__9CmdStatusFs(int param_1,short param_2)

{
  int *piVar1;
  undefined4 uVar2;
  undefined1 uVar3;
  uint uVar4;
  uint uVar5;
  undefined1 auStack_c0 [72];
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  int *piStack_5c;
  int *piStack_58;
  int iStack_54;
  int iStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  int iStack_44;
  int iStack_40;
  ushort uStack_3a;
  ushort uStack_38;
  short sStack_36;
  ushort uStack_34;
  short sStack_32;
  short sStack_30;
  ushort uStack_2e;
  ushort uStack_2c;
  short sStack_2a;
  ushort uStack_28;
  ushort uStack_26;
  undefined1 uStack_23;
  undefined1 uStack_22;
  undefined1 uStack_21;
  int iStack_20;
  short sStack_10;
  
  sStack_32 = *(short *)(*(int *)(param_1 + 0x18) + 0x16);
  iStack_44 = (int)sStack_32;
  iStack_40 = *(int *)(param_1 + 0x10);
  iStack_54 = iStack_40 + 0xb8;
  piVar1 = *(int **)(iStack_54 + iStack_44 * 4 + 0x10);
  piStack_5c = piVar1;
  piStack_58 = piVar1;
  iStack_50 = iStack_54;
  sStack_30 = sStack_32;
  iStack_20 = param_1;
  sStack_10 = param_2;
  ClearImage__8FontDrawFv(param_1 + 0x110);
  uVar5 = iStack_20 + 0xb50;
  for (uVar4 = iStack_20 + 0x150; uVar4 < uVar5; uVar4 = uVar4 + 0x100) {
    OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_20 + 0x110,uVar4,((ulong)*(byte *)(uVar4 + 0x58) & 0xf) >> 3,0);
  }
  uStack_60 = *(undefined4 *)(*piVar1 + 0x3c);
  uStack_34 = *(ushort *)(iStack_20 + 0x1f2);
  uStack_68 = *(undefined4 *)((uint)uStack_34 * 8 + *(int *)(iStack_20 + 0x24) + 0x10);
  uStack_64 = uStack_68;
  uStack_26 = uStack_34;
  sprintf(auStack_c0,uStack_68,uStack_60);
  SetMessage__8MenuTextFPcUiUcUc(iStack_20 + 0x1d0,auStack_c0,*(byte *)(iStack_20 + 0x228) & 7,0,1);
  OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_20 + 0x110,iStack_20 + 0x1d0,
                  ((ulong)*(byte *)(iStack_20 + 0x228) & 0xf) >> 3,0);
  uStack_6c = *(undefined4 *)(*(int *)(iStack_20 + 0x24) + 0xa8);
  uStack_48 = uStack_6c;
  SetMessage__8MenuTextFPcUiUcUc(iStack_20 + 0x2d0,uStack_6c,*(byte *)(iStack_20 + 0x328) & 7,0,1);
  OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_20 + 0x110,iStack_20 + 0x2d0,
                  ((ulong)*(byte *)(iStack_20 + 0x328) & 0xf) >> 3,0);
  uVar5 = iStack_20 + 0x950;
  for (uVar4 = iStack_20 + 0x350; uVar4 < uVar5; uVar4 = uVar4 + 0x100) {
    sStack_36 = *(short *)(uVar4 + 0x96);
    uStack_22 = *(undefined1 *)((int)piVar1 + sStack_36 + 0x1e);
    uStack_38 = *(ushort *)(uVar4 + 0xa2);
    uStack_74 = *(undefined4 *)((uint)uStack_38 * 8 + *(int *)(iStack_20 + 0x24) + 0x10);
    uStack_70 = uStack_74;
    sStack_2a = sStack_36;
    uStack_28 = uStack_38;
    uStack_21 = uStack_22;
    sprintf(auStack_c0,uStack_74,uStack_22);
    SetMessage__8MenuTextFPcUiUcUc(uVar4 + 0x80,auStack_c0,*(byte *)(uVar4 + 0xd8) & 7,0,1);
    OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_20 + 0x110,uVar4 + 0x80,((ulong)*(byte *)(uVar4 + 0xd8) & 0xf) >> 3,0);
  }
  uStack_23 = *(undefined1 *)(*piVar1 + 0x2c);
  uStack_3a = *(ushort *)(uVar4 + 0xa2);
  uVar2 = *(undefined4 *)((uint)uStack_3a * 8 + *(int *)(iStack_20 + 0x24) + 0x10);
  uStack_78 = uVar2;
  uStack_2c = uStack_3a;
  uVar3 = GetRestCrestSlot__5CmdPCFv(piVar1);
  sprintf(auStack_c0,uVar2,uVar3,uStack_23);
  SetMessage__8MenuTextFPcUiUcUc(uVar4 + 0x80,auStack_c0,*(byte *)(uVar4 + 0xd8) & 7,0,1);
  OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_20 + 0x110,uVar4 + 0x80,((ulong)*(byte *)(uVar4 + 0xd8) & 0xf) >> 3,0);
  uStack_2e = (ushort)(*(byte *)*piVar1 >> 5);
  uStack_4c = *(undefined4 *)((uint)uStack_2e * 8 + *(int *)(iStack_20 + 0x24) + 0x10);
  SetMessage__8MenuTextFPcUiUcUc(uVar4 + 0x180,uStack_4c,*(byte *)(uVar4 + 0x1d8) & 7,0,1);
  OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_20 + 0x110,uVar4 + 0x180,((ulong)*(byte *)(uVar4 + 0x1d8) & 0xf) >> 3,0);
  if (sStack_10 == 0) {
    *(byte *)(iStack_20 + 0x6e) = *(byte *)(iStack_20 + 0x6e) & 0xfe | 1;
    *(byte *)(iStack_20 + 0xdc2) = *(byte *)(iStack_20 + 0xdc2) & 0xfe | 1;
  }
  else {
    Open__10MenuWindowFUci(iStack_20 + 0x5c,*(byte *)(iStack_20 + 0x10c) & 7,
                    *(undefined4 *)(*(int *)(iStack_20 + 0x90) + 0x10));
    Open__10MenuWindowFUci(iStack_20 + 0xdb0,*(byte *)(iStack_20 + 0xe60) & 7,
                    *(undefined4 *)(*(int *)(iStack_20 + 0xde4) + 0x10));
  }
  return;
}

/* JP: 0x0044b6f0  CmdStatus::Release()   [Release__9CmdStatusFv]  size=0x10 */
void Release__9CmdStatusFv(void)

{
  return;
}
