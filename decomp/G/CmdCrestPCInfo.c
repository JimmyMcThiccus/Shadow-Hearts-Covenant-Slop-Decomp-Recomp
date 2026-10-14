/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdCrestPCInfo   functions: 6
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdCrestPCInfo.md).
 */

/* JP: 0x004900e0  CmdCrestPCInfo::CmdCrestPCInfo()   [__ct__14CmdCrestPCInfoFv]  size=0x14c */
int __ct__14CmdCrestPCInfoFv(int param_1)

{
  __ct__9CmdWindowFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__14CmdCrestPCInfo;
  *(undefined4 *)(param_1 + 0x18) = 0x409334;
  *(undefined4 *)(param_1 + 0x24) = 0x409340;
  __ct__11MenuTextureFv(param_1 + 0xb8);
  __ct__11SendOnLocalFv(param_1 + 0xf8);
  __ct__11SendOnLocalFv(param_1 + 0x128);
  __ct__10MenuSpriteFv(param_1 + 0x158);
  __ct__7MenuBarFv(param_1 + 0x1b8);
  __ct__7MenuBarFv(param_1 + 0x220);
  __ct__7MenuBarFv(param_1 + 0x288);
  __ct__8FontDrawFv(param_1 + 0x2f0);
  __ct__8MenuTextFv(param_1 + 0x330);
  __ct__8MenuTextFv(param_1 + 0x3b0);
  __ct__8MenuTextFv(param_1 + 0x430);
  __ct__8MenuTextFv(param_1 + 0x4b0);
  __construct_array(param_1 + 0x530,0x276640,0x2766d0,0x84,2);
  *(undefined4 *)(param_1 + 0x638) = 0;
  return param_1;
}

/* JP: 0x00490230  CmdCrestPCInfo::~CmdCrestPCInfo()   [__dt__14CmdCrestPCInfoFv]  size=0x1a4 */
int __dt__14CmdCrestPCInfoFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__14CmdCrestPCInfo;
    *(undefined4 *)(param_1 + 0x18) = 0x409334;
    *(undefined4 *)(param_1 + 0x24) = 0x409340;
    __destroy_arr(param_1 + 0x530,0x2766d0,0x84,2);
    __dt__8MenuTextFv(param_1 + 0x4b0,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1 + 0x430,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1 + 0x3b0,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1 + 0x330,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x2f0,0xffffffffffffffff);
    __dt__7MenuBarFv(param_1 + 0x288,0xffffffffffffffff);
    __dt__7MenuBarFv(param_1 + 0x220,0xffffffffffffffff);
    __dt__7MenuBarFv(param_1 + 0x1b8,0xffffffffffffffff);
    __dt__10MenuSpriteFv(param_1 + 0x158,0xffffffffffffffff);
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

/* JP: 0x004903e0  CmdCrestPCInfo::CreateScene(CmdCrest*)   [CreateScene__14CmdCrestPCInfoFP8CmdCrest]  size=0x348 */
void CreateScene__14CmdCrestPCInfoFP8CmdCrest(int param_1,int param_2)

{
  short sVar1;
  int iVar2;
  
  iVar2 = param_1 + 0x1b8;
  sVar1 = 1;
  while( true ) {
    if (3 < sVar1) break;
    SetData__9MenuSceneFUsP10MenuSprite(param_2,sVar1,iVar2);
    SetBar__7MenuBarFv(iVar2);
    AddPlace__10MenuWindowFP9MenuPlace(param_1,iVar2);
    sVar1 = sVar1 + 1;
    iVar2 = iVar2 + 0x68;
  }
  SetData__9MenuSceneFUsP10MenuSprite(param_2,0,param_1 + 0x158);
  AddPlace__10MenuWindowFP9MenuPlace(param_1,param_1 + 0x158);
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(param_1 + 0x128,param_2 + 400,*(undefined4 *)(param_2 + 0x18c),1,
                  0xffffffffffffffff);
  *(short *)(param_1 + 0x13c) = *(short *)(param_1 + 0x1cc) + -1;
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0x128);
  Create__11MenuTextureFPUc6GS_PSMUii(param_1 + 0xb8,*(undefined4 *)(*(int *)(param_2 + 0x54) + 0x1c),0x30,0,0);
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(param_1 + 0xf8,param_1 + 0xd0,*(undefined4 *)(param_1 + 0xcc),1,0xffffffffffffffff
                 );
  *(short *)(param_1 + 0x10c) = *(short *)(param_1 + 0x16c) + -1;
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0xf8);
  SetData__9MenuSceneFUsP8FontDraw(param_2,0,param_1 + 0x2f0);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0x2f0);
  iVar2 = param_1 + 0x330;
  for (sVar1 = 0; sVar1 < 4; sVar1 = sVar1 + 1) {
    SetData__9MenuSceneFUsP8MenuText(param_2,sVar1,iVar2);
    AddPlace__10MenuWindowFP9MenuPlace(param_1,iVar2);
    iVar2 = iVar2 + 0x80;
  }
  SetData__9MenuSceneFUsP11MenuPolygon(param_2,0,param_1 + 0x530);
  SetData__9MenuSceneFUsP11MenuPolygon(param_2,1,param_1 + 0x5b4);
  AddPlace__10MenuWindowFP9MenuPlace(param_1,param_1 + 0x530);
  AddPlace__10MenuWindowFP9MenuPlace(param_1,param_1 + 0x5b4);
  SetData__9MenuSceneFUsP10MenuWindow(param_2,0,param_1);
  AddOT__7MenuObjFv(param_1);
  return;
}

/* JP: 0x00490730  CmdCrestPCInfo::UpdateScene(CmdCrest*, short)   [UpdateScene__14CmdCrestPCInfoFP8CmdCrests]  size=0x54c */
void UpdateScene__14CmdCrestPCInfoFP8CmdCrests(int param_1,int param_2,short param_3)

{
  undefined1 uVar1;
  int *piVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  undefined8 uVar7;
  uint uVar8;
  undefined1 auStack_98 [8];
  float fStack_90;
  float fStack_8c;
  undefined4 uStack_88;
  float fStack_84;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  float fStack_5c;
  int *piStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  float fStack_4c;
  ushort uStack_46;
  ushort uStack_44;
  ushort uStack_42;
  ushort uStack_40;
  short sStack_3e;
  short sStack_3c;
  ushort uStack_3a;
  ushort uStack_38;
  ushort uStack_36;
  ushort uStack_34;
  undefined1 uStack_31;
  int iStack_30;
  int iStack_20;
  short sStack_10;
  
  piVar2 = *(int **)(param_2 + 0x70);
  piStack_58 = piVar2;
  iStack_30 = param_1;
  iStack_20 = param_2;
  sStack_10 = param_3;
  uVar3 = GetRestCrestSlot__5CmdPCFv(piVar2);
  uVar3 = uVar3 & 0xff;
  uVar1 = *(undefined1 *)(*piVar2 + 0x2c);
  uStack_31 = uVar1;
  SetRange__7MenuBarFii(iStack_30 + 0x1b8,uVar3,uVar1);
  fStack_5c = *(float *)(iStack_30 + 0x1e4);
  *(byte *)(iStack_30 + 0x232) = *(byte *)(iStack_30 + 0x232) & 0xfe;
  *(byte *)(iStack_30 + 0x29a) = *(byte *)(iStack_30 + 0x29a) & 0xfe;
  iVar4 = 0;
  uVar7 = 7;
  uVar6 = uVar3;
  if (-1 < sStack_10) {
    sStack_3e = *(short *)(*(int *)(iStack_30 + 0x638) + 0x22);
    iVar4 = (int)sStack_3e - (int)sStack_10;
    uVar8 = uVar3 + iVar4;
    sStack_3c = sStack_3e;
    if (-1 < (int)uVar8) {
      uVar6 = uVar8;
      if (iVar4 < 1) {
        uVar7 = 7;
        if (iVar4 < 0) {
          uVar3 = uVar3 + iVar4;
          uVar7 = 9;
        }
      }
      else {
        uVar7 = 8;
      }
    }
  }
  fStack_4c = fStack_5c;
  ClearImage__8FontDrawFv(iStack_30 + 0x2f0);
  uStack_40 = *(ushort *)(iStack_30 + 0x352);
  uStack_64 = *(undefined4 *)((uint)uStack_40 * 8 + *(int *)(iStack_20 + 0x24) + 0x10);
  uStack_60 = uStack_64;
  uStack_50 = uStack_64;
  uStack_38 = uStack_40;
  SetMessage__8MenuTextFPcUiUcUc(iStack_30 + 0x330,uStack_64,*(byte *)(iStack_30 + 0x388) & 7,0,1);
  OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_30 + 0x2f0,iStack_30 + 0x330,
                  ((ulong)*(byte *)(iStack_30 + 0x388) & 0xf) >> 3,0);
  uStack_42 = *(ushort *)(iStack_30 + 0x3d2);
  uStack_6c = *(undefined4 *)((uint)uStack_42 * 8 + *(int *)(iStack_20 + 0x24) + 0x10);
  uStack_68 = uStack_6c;
  uStack_54 = uStack_6c;
  uStack_3a = uStack_42;
  SetMessage__8MenuTextFPcUiUcUc(iStack_30 + 0x3b0,uStack_6c,*(byte *)(iStack_30 + 0x408) & 7,0,1);
  OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_30 + 0x2f0,iStack_30 + 0x3b0,
                  ((ulong)*(byte *)(iStack_30 + 0x408) & 0xf) >> 3,0);
  uStack_44 = *(ushort *)(iStack_30 + 0x452);
  uStack_74 = *(undefined4 *)((uint)uStack_44 * 8 + *(int *)(iStack_20 + 0x24) + 0x10);
  uStack_70 = uStack_74;
  uStack_34 = uStack_44;
  sprintf(auStack_98,uStack_74,uVar6);
  SetMessage__8MenuTextFPcUiUcUc(iStack_30 + 0x430,auStack_98,*(byte *)(iStack_30 + 0x488) & 7,0,1);
  OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_30 + 0x2f0,iStack_30 + 0x430,
                  ((ulong)*(byte *)(iStack_30 + 0x488) & 0xf) >> 3,0);
  SetCSA__8FontItemFUc(iStack_30 + 0x430,uVar7);
  uStack_46 = *(ushort *)(iStack_30 + 0x4d2);
  uStack_7c = *(undefined4 *)((uint)uStack_46 * 8 + *(int *)(iStack_20 + 0x24) + 0x10);
  uStack_78 = uStack_7c;
  uStack_36 = uStack_46;
  sprintf(auStack_98,uStack_7c,uVar1);
  SetMessage__8MenuTextFPcUiUcUc(iStack_30 + 0x4b0,auStack_98,*(byte *)(iStack_30 + 0x508) & 7,0,1);
  OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_30 + 0x2f0,iStack_30 + 0x4b0,
                  ((ulong)*(byte *)(iStack_30 + 0x508) & 0xf) >> 3,0);
  SetRange__7MenuBarFii(iStack_30 + 0x1b8,uVar3,uVar1);
  Round__7MenuBarFv(iStack_30 + 0x1b8);
  if ((iVar4 != 0) && (-1 < (int)uVar6)) {
    iVar5 = iStack_30 + 0x220;
    if (iVar4 < 1) {
      if (iVar4 < 0) {
        iVar5 = iStack_30 + 0x288;
        uStack_80 = *(undefined4 *)(iStack_30 + 0x2b8);
        fStack_84 = *(float *)(iStack_30 + 0x1e4);
        (**(code **)(*(int *)(iStack_30 + 0x290) + 0x28))(fStack_4c - fStack_84,uStack_80);
      }
    }
    else {
      SetRange__7MenuBarFii(iVar5,iVar4,uVar1);
    }
    uStack_88 = *(undefined4 *)(iStack_30 + 0x1e0);
    fStack_8c = *(float *)(iStack_30 + 0x1e4);
    fStack_90 = *(float *)(iStack_30 + 0x1dc);
    (**(code **)(*(int *)(iVar5 + 8) + 0x24))(fStack_90 + fStack_8c,uStack_88);
    *(byte *)(iVar5 + 0x12) = *(byte *)(iVar5 + 0x12) & 0xfe | 1;
  }
  return;
}

/* JP: 0x00490c80  CmdCrestPCInfo::~CmdCrestPCInfo()   [@24@__dt__14CmdCrestPCInfoFv]  size=0x8 */
undefined4 * _24___dt__14CmdCrestPCInfoFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -6;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-4] = &__vt__14CmdCrestPCInfo;
    *param_1 = 0x409334;
    param_1[3] = 0x409340;
    __destroy_arr(param_1 + 0x146,0x2766d0,0x84,2);
    __dt__8MenuTextFv(param_1 + 0x126,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1 + 0x106,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1 + 0xe6,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1 + 0xc6,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0xb6,0xffffffffffffffff);
    __dt__7MenuBarFv(param_1 + 0x9c,0xffffffffffffffff);
    __dt__7MenuBarFv(param_1 + 0x82,0xffffffffffffffff);
    __dt__7MenuBarFv(param_1 + 0x68,0xffffffffffffffff);
    __dt__10MenuSpriteFv(param_1 + 0x50,0xffffffffffffffff);
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

/* JP: 0x00490c90  CmdCrestPCInfo::~CmdCrestPCInfo()   [@36@__dt__14CmdCrestPCInfoFv]  size=0x8 */
undefined4 * _36___dt__14CmdCrestPCInfoFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -9;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-7] = &__vt__14CmdCrestPCInfo;
    param_1[-3] = 0x409334;
    *param_1 = 0x409340;
    __destroy_arr(param_1 + 0x143,0x2766d0,0x84,2);
    __dt__8MenuTextFv(param_1 + 0x123,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1 + 0x103,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1 + 0xe3,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1 + 0xc3,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0xb3,0xffffffffffffffff);
    __dt__7MenuBarFv(param_1 + 0x99,0xffffffffffffffff);
    __dt__7MenuBarFv(param_1 + 0x7f,0xffffffffffffffff);
    __dt__7MenuBarFv(param_1 + 0x65,0xffffffffffffffff);
    __dt__10MenuSpriteFv(param_1 + 0x4d,0xffffffffffffffff);
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
