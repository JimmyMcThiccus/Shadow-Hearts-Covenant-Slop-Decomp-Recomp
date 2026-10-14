/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdFusionParameter   functions: 6
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdFusionParameter.md).
 */

/* JP: 0x0047b980  CmdFusionParameter::CmdFusionParameter()   [__ct__18CmdFusionParameterFv]  size=0x10c */
int __ct__18CmdFusionParameterFv(int param_1)

{
  __ct__9CmdWindowFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__18CmdFusionParameter;
  *(undefined4 *)(param_1 + 0x18) = 0x408d54;
  *(undefined4 *)(param_1 + 0x24) = 0x408d60;
  __ct__8FontDrawFv(param_1 + 0xb4);
  __ct__8FontDrawFv(param_1 + 0xf4);
  __construct_array(param_1 + 0x134,0x27bfd0,0x27c030,0x80,3);
  __ct__8MenuTextFv(param_1 + 0x2b4);
  __ct__8MenuTextFv(param_1 + 0x334);
  __ct__8MenuTextFv(param_1 + 0x3b4);
  __ct__8MenuTextFv(param_1 + 0x434);
  __construct_array(param_1 + 0x4b4,0x276640,0x2766d0,0x84,4);
  return param_1;
}

/* JP: 0x0047ba90  CmdFusionParameter::~CmdFusionParameter()   [__dt__18CmdFusionParameterFv]  size=0x14c */
int __dt__18CmdFusionParameterFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__18CmdFusionParameter;
    *(undefined4 *)(param_1 + 0x18) = 0x408d54;
    *(undefined4 *)(param_1 + 0x24) = 0x408d60;
    __destroy_arr(param_1 + 0x4b4,0x2766d0,0x84,4);
    __dt__8MenuTextFv(param_1 + 0x434,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1 + 0x3b4,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1 + 0x334,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1 + 0x2b4,0xffffffffffffffff);
    __destroy_arr(param_1 + 0x134,0x27c030,0x80,3);
    __dt__8FontDrawFv(param_1 + 0xf4,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0xb4,0xffffffffffffffff);
    __dt__9CmdWindowFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x0047bbe0  CmdFusionParameter::CreateScene(CmdFusion*)   [CreateScene__18CmdFusionParameterFP9CmdFusion]  size=0x33c */
void CreateScene__18CmdFusionParameterFP9CmdFusion(int param_1,int param_2)

{
  short sVar1;
  short sVar2;
  int iVar3;
  
  SetData__9MenuSceneFUsP8FontDraw(param_2,1,param_1 + 0xb4);
  SetData__9MenuSceneFUsP8FontDraw(param_2,2,param_1 + 0xf4);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0xb4);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0xf4);
  iVar3 = param_1 + 0x134;
  sVar1 = 3;
  while( true ) {
    if (9 < sVar1) break;
    SetData__9MenuSceneFUsP8MenuText(param_2,sVar1,iVar3);
    AddPlace__10MenuWindowFP9MenuPlace(param_1,iVar3);
    if (sVar1 < 6) {
      SetMessage__8MenuTextFPcUiUcUc(iVar3,*(undefined4 *)
                             ((uint)*(ushort *)(iVar3 + 0x22) * 8 + *(int *)(param_2 + 0x24) + 0x10)
                      ,*(byte *)(iVar3 + 0x58) & 7,0,1);
      OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(param_1 + 0xb4,iVar3,((ulong)*(byte *)(iVar3 + 0x58) & 0xf) >> 3,0);
    }
    sVar1 = sVar1 + 1;
    iVar3 = iVar3 + 0x80;
  }
  iVar3 = param_1 + 0x4b4;
  for (sVar1 = 0; sVar1 < 2; sVar1 = sVar1 + 1) {
    SetData__9MenuSceneFUsP11MenuPolygon(param_2,sVar1,iVar3);
    AddPlace__10MenuWindowFP9MenuPlace(param_1,iVar3);
    iVar3 = iVar3 + 0x84;
  }
  sVar1 = *(short *)(param_1 + 0x4d6);
  iVar3 = param_1 + 0x5bc;
  for (sVar2 = 0; sVar2 < 2; sVar2 = sVar2 + 1) {
    SetData__9MenuSceneFUsP11MenuPolygon(param_2,sVar2,iVar3);
    (**(code **)(*(int *)(iVar3 + 8) + 0x24))
              (*(undefined4 *)(iVar3 + 0x24),(float)(int)sVar1 + *(float *)(iVar3 + 0x28));
    AddPlace__10MenuWindowFP9MenuPlace(param_1,iVar3);
    iVar3 = iVar3 + 0x84;
  }
  SetData__9MenuSceneFUsP10MenuWindow(param_2,1,param_1);
  AddOT__7MenuObjFv(param_1);
  if (1 < *(short *)(*(int *)(param_2 + 0x78) + 0xae)) {
    CreateScrollMark__10MenuWindowFUc(param_1,0xc);
  }
  return;
}

/* JP: 0x0047bf20  CmdFusionParameter::UpdateScene(CmdFusion*)   [UpdateScene__18CmdFusionParameterFP9CmdFusion]  size=0x424 */
void UpdateScene__18CmdFusionParameterFP9CmdFusion(int param_1,int param_2)

{
  byte bVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  undefined1 auStack_90 [28];
  undefined4 uStack_74;
  undefined4 uStack_70;
  uint uStack_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  int iStack_50;
  undefined4 uStack_4c;
  int iStack_48;
  int iStack_44;
  int iStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  ushort uStack_30;
  ushort uStack_2e;
  ushort uStack_2c;
  short sStack_2a;
  ushort uStack_28;
  ushort uStack_26;
  ushort uStack_24;
  byte bStack_22;
  byte bStack_21;
  int iStack_20;
  int iStack_10;
  
  iStack_48 = *(int *)(*(int *)(param_2 + 0x58) + 0x5c);
  uStack_4c = *(undefined4 *)(param_2 + 0xb8);
  sVar2 = *(short *)(param_2 + 0xbc);
  bVar1 = *(byte *)(*(int *)(iStack_48 + 4) + (int)sVar2 + 0xd94);
  iVar3 = *(int *)(*(int *)(iStack_48 + 4) + sVar2 * 4 + 0xd50);
  iStack_50 = iVar3;
  iStack_44 = iStack_48;
  iStack_40 = iStack_48;
  uStack_34 = uStack_4c;
  sStack_2a = sVar2;
  bStack_22 = bVar1;
  iStack_20 = param_1;
  iStack_10 = param_2;
  ClearImage__8FontDrawFv(param_1 + 0xf4);
  uStack_54 = *(undefined4 *)(iStack_10 + 0xb4);
  uStack_38 = uStack_54;
  SetMessage__8MenuTextFPcUiUcUc(iStack_20 + 0x2b4,uStack_54,*(byte *)(iStack_20 + 0x30c) & 7,0,1);
  OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_20 + 0xf4,iStack_20 + 0x2b4,
                  ((ulong)*(byte *)(iStack_20 + 0x30c) & 0xf) >> 3,0);
  uStack_2c = *(ushort *)(iStack_20 + 0x356);
  uStack_5c = *(undefined4 *)((uint)uStack_2c * 8 + *(int *)(iStack_10 + 0x24) + 0x10);
  uStack_58 = uStack_5c;
  uStack_24 = uStack_2c;
  sprintf(auStack_90,uStack_5c,bVar1 + 1);
  SetMessage__8MenuTextFPcUiUcUc(iStack_20 + 0x334,auStack_90,*(byte *)(iStack_20 + 0x38c) & 7,0,1);
  OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_20 + 0xf4,iStack_20 + 0x334,
                  ((ulong)*(byte *)(iStack_20 + 0x38c) & 0xf) >> 3,0);
  uStack_2e = *(ushort *)(iStack_20 + 0x3d6);
  uStack_64 = *(undefined4 *)((uint)uStack_2e * 8 + *(int *)(iStack_10 + 0x24) + 0x10);
  uStack_60 = uStack_64;
  uStack_26 = uStack_2e;
  sprintf(auStack_90,uStack_64,iVar3);
  SetMessage__8MenuTextFPcUiUcUc(iStack_20 + 0x3b4,auStack_90,*(byte *)(iStack_20 + 0x40c) & 7,0,1);
  OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_20 + 0xf4,iStack_20 + 0x3b4,
                  ((ulong)*(byte *)(iStack_20 + 0x40c) & 0xf) >> 3,0);
  uStack_68 = *(undefined4 *)(*(int *)(iStack_10 + 0x24) + 0xa0);
  uStack_3c = uStack_68;
  SetMessage__8MenuTextFPcUiUcUc(iStack_20 + 0x434,uStack_68,*(byte *)(iStack_20 + 0x48c) & 7,0,1);
  uStack_6c = *(uint *)(iStack_10 + 0xc0);
  if (bVar1 < uStack_6c) {
    uStack_30 = *(ushort *)(iStack_20 + 0x456);
    uStack_74 = *(undefined4 *)((uint)uStack_30 * 8 + *(int *)(iStack_10 + 0x24) + 0x10);
    uStack_70 = uStack_74;
    uStack_28 = uStack_30;
    iVar4 = GetNextExp__9CmdFusionFs(iStack_10,1);
    sprintf(auStack_90,uStack_74,iVar4 - iVar3);
    SetMessage__8MenuTextFPcUiUcUc(iStack_20 + 0x434,auStack_90,*(byte *)(iStack_20 + 0x48c) & 7,0,1);
  }
  OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_20 + 0xf4,iStack_20 + 0x434,
                  ((ulong)*(byte *)(iStack_20 + 0x48c) & 0xf) >> 3,0);
  if (*(int *)(iStack_20 + 0x44) != 0) {
    bStack_21 = *(byte *)(*(int *)(iStack_20 + 0x44) + 0x83) & 0xf;
    SetArea__10ScrollMarkFUcffff(*(undefined4 *)(iStack_20 + 0x2d8),*(undefined4 *)(iStack_20 + 0x2dc),
                    *(undefined4 *)(iStack_20 + 0x2e0),*(undefined4 *)(iStack_20 + 0x2e4),
                    *(int *)(iStack_20 + 0x44),bStack_21);
  }
  *(short *)(iStack_20 + 0x16) = sVar2;
  return;
}

/* JP: 0x0047c350  CmdFusionParameter::~CmdFusionParameter()   [@24@__dt__18CmdFusionParameterFv]  size=0x8 */
undefined4 * _24___dt__18CmdFusionParameterFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -6;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-4] = &__vt__18CmdFusionParameter;
    *param_1 = 0x408d54;
    param_1[3] = 0x408d60;
    __destroy_arr(param_1 + 0x127,0x2766d0,0x84,4);
    __dt__8MenuTextFv(param_1 + 0x107,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1 + 0xe7,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1 + 199,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1 + 0xa7,0xffffffffffffffff);
    __destroy_arr(param_1 + 0x47,0x27c030,0x80,3);
    __dt__8FontDrawFv(param_1 + 0x37,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x27,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}

/* JP: 0x0047c360  CmdFusionParameter::~CmdFusionParameter()   [@36@__dt__18CmdFusionParameterFv]  size=0x8 */
undefined4 * _36___dt__18CmdFusionParameterFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -9;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-7] = &__vt__18CmdFusionParameter;
    param_1[-3] = 0x408d54;
    *param_1 = 0x408d60;
    __destroy_arr(param_1 + 0x124,0x2766d0,0x84,4);
    __dt__8MenuTextFv(param_1 + 0x104,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1 + 0xe4,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1 + 0xc4,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1 + 0xa4,0xffffffffffffffff);
    __destroy_arr(param_1 + 0x44,0x27c030,0x80,3);
    __dt__8FontDrawFv(param_1 + 0x34,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x24,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}
