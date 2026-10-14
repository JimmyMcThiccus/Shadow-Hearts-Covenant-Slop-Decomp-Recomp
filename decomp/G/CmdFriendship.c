/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdFriendship   functions: 7
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdFriendship.md).
 */

/* JP: 0x004549d0  CmdFriendship::CmdFriendship()   [__ct__13CmdFriendshipFv]  size=0x5c */
int __ct__13CmdFriendshipFv(int param_1)

{
  __ct__15CmdPrivateSceneFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__13CmdFriendship;
  __ct__10MenuWindowFv(param_1 + 0x5c);
  __ct__8FontDrawFv(param_1 + 0x110);
  return param_1;
}

/* JP: 0x00454a30  CmdFriendship::~CmdFriendship()   [__dt__13CmdFriendshipFv]  size=0xc4 */
int __dt__13CmdFriendshipFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__13CmdFriendship;
    if (*(int *)(param_1 + 0x150) != 0) {
      __destroy_new_array(*(undefined4 *)(param_1 + 0x150),0x450670);
    }
    __dt__8FontDrawFv(param_1 + 0x110,0xffffffffffffffff);
    __dt__10MenuWindowFv(param_1 + 0x5c,0xffffffffffffffff);
    __dt__15CmdPrivateSceneFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x00454b00  CmdFriendship::GetReady()   [GetReady__13CmdFriendshipFv]  size=0x424 */
undefined4 GetReady__13CmdFriendshipFv(int param_1)

{
  undefined4 uVar1;
  undefined8 uVar2;
  long lVar3;
  int iVar4;
  short sVar5;
  undefined1 auStack_e0 [100];
  undefined4 uStack_7c;
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  undefined4 *puStack_64;
  undefined4 *puStack_60;
  undefined4 *puStack_5c;
  float fStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  int iStack_4c;
  int iStack_48;
  int iStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  int iStack_34;
  int iStack_30;
  int iStack_2c;
  int iStack_28;
  int iStack_24;
  int iStack_20;
  undefined4 uStack_1c;
  float fStack_18;
  short sStack_14;
  short sStack_12;
  int iStack_10;
  
  iStack_10 = param_1;
  __ct__9MenuSceneFv(auStack_e0);
  iStack_28 = *(int *)(iStack_10 + 0x58);
  uStack_40 = *(undefined4 *)(iStack_28 + 0x18);
  *(undefined4 *)(iStack_10 + 0x18) = uStack_40;
  iStack_2c = *(int *)(iStack_10 + 0x58);
  iStack_4c = *(int *)(iStack_2c + 0x5c);
  sStack_12 = *(short *)(iStack_4c + 0xe);
  *(short *)(iStack_10 + 0x158) = sStack_12 + -1;
  sStack_14 = *(short *)(iStack_4c + 0xe);
  iVar4 = (int)sStack_14;
  iStack_48 = iStack_4c;
  iStack_44 = iStack_4c;
  uStack_3c = uStack_40;
  uStack_38 = uStack_40;
  uVar2 = __nwa__FUi((iVar4 + -1) * 0x150 + 0x10);
  uStack_50 = __construct_new_array(uVar2,0x454640,0x450670,0x150,iVar4 + -1);
  *(undefined4 *)(iStack_10 + 0x150) = uStack_50;
  SetData__9MenuSceneFUsP8FontDraw(iStack_10,0,iStack_10 + 0x110);
  AddPriority__12MenuObjTableFP7MenuObj(iStack_10 + 0x74,iStack_10 + 0x110);
  iVar4 = *(int *)(iStack_10 + 0x150);
  fStack_18 = 0.0;
  for (sVar5 = 0; sVar5 < *(short *)(iStack_10 + 0x158); sVar5 = sVar5 + 1) {
    SetData__9MenuSceneFUsP8MenuText(iStack_10,0,iVar4 + 0x50);
    SetData__9MenuSceneFUsP8MenuText(iStack_10,1,iVar4 + 0xd0);
    AddPlace__9MenuGroupFP9MenuPlace(iVar4,iVar4 + 0x50);
    AddPlace__9MenuGroupFP9MenuPlace(iVar4,iVar4 + 0xd0);
    SetData__9MenuSceneFUsP9MenuGroup(iStack_10,0,iVar4);
    uStack_54 = *(undefined4 *)(iVar4 + 0x24);
    (**(code **)(*(int *)(iVar4 + 8) + 0x24))(uStack_54,fStack_18);
    AddPlace__10MenuWindowFP9MenuPlace(iStack_10 + 0x5c,iVar4);
    fStack_58 = *(float *)(iVar4 + 0x30);
    fStack_18 = fStack_18 + fStack_58;
    iVar4 = iVar4 + 0x150;
  }
  SetData__9MenuSceneFUsP10MenuWindow(iStack_10,0,iStack_10 + 0x5c);
  AddOT__7MenuObjFv(iStack_10 + 0x5c);
  iStack_20 = *(int *)(iStack_10 + 0x58);
  puStack_60 = (undefined4 *)(*(int *)(iStack_20 + 0x54) + 0x94);
  puStack_5c = puStack_60;
  Initialize__9MenuSceneFPUcP9BufMemory(auStack_e0,*puStack_60,0);
  lVar3 = __nw__FUi(0x178);
  uVar1 = 0;
  if (lVar3 != 0) {
    uVar1 = __ct__8CmdFenceFv(lVar3);
  }
  *(undefined4 *)(iStack_10 + 0x154) = uVar1;
  iStack_24 = *(int *)(iStack_10 + 0x58);
  puStack_64 = (undefined4 *)(*(int *)(iStack_24 + 0x54) + 0x1c);
  CreateFence__8CmdFenceFP9MenuScenePUc(*(undefined4 *)(iStack_10 + 0x154),auStack_e0,*puStack_64);
  iVar4 = *(int *)(iStack_10 + 0x154);
  Open__10MenuWindowFUci(iVar4,*(byte *)(iVar4 + 0xb0) & 7,*(undefined4 *)(*(int *)(iVar4 + 0x34) + 0x10));
  iStack_30 = *(int *)(iStack_10 + 0x58);
  uStack_70 = *(undefined4 *)(iStack_30 + 0x60);
  uStack_6c = uStack_70;
  uStack_68 = uStack_70;
  SetTitle__11CmdTitleLogFPUci(uStack_70,*(undefined4 *)(*(int *)(iStack_10 + 0x54) + 0x10),0x1d);
  iStack_34 = *(int *)(iStack_10 + 0x58);
  uStack_7c = *(undefined4 *)(iStack_34 + 0x60);
  uStack_78 = uStack_7c;
  uStack_74 = uStack_7c;
  Open__11CmdTitleLogFv(uStack_7c);
  uStack_1c = 1;
  __dt__9MenuSceneFv(auStack_e0,0xffffffffffffffff);
  return uStack_1c;
}

/* JP: 0x00454f30  CmdFriendship::SafeDelayDelete()   [SafeDelayDelete__13CmdFriendshipFv]  size=0x58 */
void SafeDelayDelete__13CmdFriendshipFv(int param_1)

{
  ReleaseOT__7MenuObjFv(param_1 + 0x5c);
  (**(code **)(*(int *)(*(int *)(param_1 + 0x154) + 8) + 0xc))();
  (**(code **)(*(int *)(param_1 + 8) + 0xc))();
  return;
}

/* JP: 0x00454f90  CmdFriendship::Close()   [Close__13CmdFriendshipFv]  size=0x78 */
void Close__13CmdFriendshipFv(int param_1)

{
  int iVar1;
  
  Close__10MenuWindowFUci(param_1 + 0x5c,((ulong)*(byte *)(param_1 + 0x10c) & 0x3f) >> 3,
                  *(undefined4 *)(*(int *)(param_1 + 0x90) + 0x14));
  iVar1 = *(int *)(param_1 + 0x154);
  Close__10MenuWindowFUci(iVar1,((ulong)*(byte *)(iVar1 + 0xb0) & 0x3f) >> 3,
                  *(undefined4 *)(*(int *)(iVar1 + 0x34) + 0x14));
  return;
}

/* JP: 0x00455010  CmdFriendship::Update(short)   [Update__13CmdFriendshipFs]  size=0x2e4 */
void Update__13CmdFriendshipFs(int param_1,short param_2)

{
  int *piVar1;
  int *piVar2;
  uint uVar3;
  undefined1 auStack_68 [12];
  int iStack_5c;
  int iStack_58;
  int *piStack_54;
  int *piStack_50;
  int *piStack_4c;
  int *piStack_48;
  int *piStack_44;
  int iStack_40;
  int iStack_3c;
  int iStack_38;
  int iStack_34;
  int iStack_30;
  uint uStack_2c;
  short sStack_26;
  byte bStack_23;
  byte bStack_22;
  byte bStack_21;
  int iStack_20;
  short sStack_10;
  
  iStack_40 = *(int *)(*(int *)(param_1 + 0x58) + 0x5c);
  piVar2 = (int *)(iStack_40 + 0x10);
  piVar1 = *(int **)(*(int *)(param_1 + 0x58) + 0x70);
  piStack_54 = piVar1;
  piStack_50 = piVar1;
  piStack_4c = piVar1;
  piStack_48 = piVar2;
  piStack_44 = piVar2;
  iStack_3c = iStack_40;
  iStack_38 = iStack_40;
  iStack_30 = iStack_40;
  iStack_20 = param_1;
  sStack_10 = param_2;
  ClearImage__8FontDrawFv(param_1 + 0x110);
  uVar3 = *(uint *)(iStack_20 + 0x150);
  uStack_2c = uVar3 + *(short *)(iStack_20 + 0x158) * 0x150;
  while (uVar3 < uStack_2c) {
    if ((int *)*piVar2 != piVar1) {
      iStack_5c = *(int *)*piVar2 + 10;
      iStack_58 = iStack_5c;
      iStack_34 = iStack_5c;
      SetMessage__8MenuTextFPcUiUcUc(uVar3 + 0x50,iStack_5c,*(byte *)(uVar3 + 0xa8) & 7,0,1);
      OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_20 + 0x110,uVar3 + 0x50,((ulong)*(byte *)(uVar3 + 0xa8) & 0xf) >> 3,0);
      bStack_23 = *(byte *)(*(int *)*piVar2 + 2);
      sStack_26 = *(short *)(*piVar1 + (uint)bStack_23 * 2 + 0x40);
      bStack_22 = bStack_23;
      bStack_21 = bStack_23;
      sprintf(auStack_68,*(undefined4 *)(*(int *)(iStack_20 + 0x24) + 0x10),
                      (int)sStack_26 / 100);
      SetMessage__8MenuTextFPcUiUcUc(uVar3 + 0xd0,auStack_68,*(byte *)(uVar3 + 0x128) & 7,0,1);
      OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_20 + 0x110,uVar3 + 0xd0,((ulong)*(byte *)(uVar3 + 0x128) & 0xf) >> 3,0)
      ;
      uVar3 = uVar3 + 0x150;
    }
    piVar2 = piVar2 + 1;
  }
  if (sStack_10 == 0) {
    *(byte *)(iStack_20 + 0x6e) = *(byte *)(iStack_20 + 0x6e) & 0xfe | 1;
  }
  else {
    Open__10MenuWindowFUci(iStack_20 + 0x5c,*(byte *)(iStack_20 + 0x10c) & 7,
                    *(undefined4 *)(*(int *)(iStack_20 + 0x90) + 0x10));
  }
  return;
}

/* JP: 0x00455300  CmdFriendship::Release()   [Release__13CmdFriendshipFv]  size=0x10 */
void Release__13CmdFriendshipFv(void)

{
  return;
}
