/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdScoreData   functions: 6
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdScoreData.md).
 */

/* JP: 0x00475f50  CmdScoreData::CmdScoreData()   [__ct__12CmdScoreDataFv]  size=0xbc */
int __ct__12CmdScoreDataFv(int param_1)

{
  __ct__9CmdWindowFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__12CmdScoreData;
  *(undefined4 *)(param_1 + 0x18) = 0x408ad4;
  *(undefined4 *)(param_1 + 0x24) = 0x408ae0;
  __ct__8FontDrawFv(param_1 + 0xb4);
  __construct_array(param_1 + 0xf4,0x27bfd0,0x27c030,0x80,2);
  __construct_array(param_1 + 500,0x4760b0,0x476010,0x1d0,10);
  return param_1;
}

/* JP: 0x00476110  CmdScoreData::~CmdScoreData()   [__dt__12CmdScoreDataFv]  size=0xe4 */
int __dt__12CmdScoreDataFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__12CmdScoreData;
    *(undefined4 *)(param_1 + 0x18) = 0x408ad4;
    *(undefined4 *)(param_1 + 0x24) = 0x408ae0;
    __destroy_arr(param_1 + 500,0x476010,0x1d0,10);
    __destroy_arr(param_1 + 0xf4,0x27c030,0x80,2);
    __dt__8FontDrawFv(param_1 + 0xb4,0xffffffffffffffff);
    __dt__9CmdWindowFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x00476200  CmdScoreData::CreateScene(CmdScore*)   [CreateScene__12CmdScoreDataFP8CmdScore]  size=0x1f0 */
void CreateScene__12CmdScoreDataFP8CmdScore(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uStack_24;
  
  SetData__9MenuSceneFUsP8MenuText(param_2,1,param_1 + 0xf4);
  SetData__9MenuSceneFUsP8MenuText(param_2,2,param_1 + 0x174);
  AddPlace__10MenuWindowFP9MenuPlace(param_1,param_1 + 0xf4);
  AddPlace__10MenuWindowFP9MenuPlace(param_1,param_1 + 0x174);
  uStack_24 = 0.0;
  iVar1 = param_1 + 500;
  for (iVar2 = 0; iVar2 < 10; iVar2 = iVar2 + 1) {
    SetData__9MenuSceneFUsP8MenuText(param_2,5,iVar1 + 0x50);
    SetData__9MenuSceneFUsP8MenuText(param_2,6,iVar1 + 0xd0);
    SetData__9MenuSceneFUsP8MenuText(param_2,7,iVar1 + 0x150);
    AddPlace__9MenuGroupFP9MenuPlace(iVar1,iVar1 + 0x50);
    AddPlace__9MenuGroupFP9MenuPlace(iVar1,iVar1 + 0xd0);
    AddPlace__9MenuGroupFP9MenuPlace(iVar1,iVar1 + 0x150);
    SetData__9MenuSceneFUsP9MenuGroup(param_2,0,iVar1);
    (**(code **)(*(int *)(iVar1 + 8) + 0x24))(0,uStack_24 + *(float *)(iVar1 + 0x28));
    AddPlace__10MenuWindowFP9MenuPlace(param_1,iVar1);
    uStack_24 = uStack_24 + *(float *)(iVar1 + 0x30);
    iVar1 = iVar1 + 0x1d0;
  }
  SetData__9MenuSceneFUsP8FontDraw(param_2,1,param_1 + 0xb4);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0xb4);
  SetData__9MenuSceneFUsP10MenuWindow(param_2,1,param_1);
  AddOT__7MenuObjFv(param_1);
  return;
}

/* JP: 0x004763f0  CmdScoreData::UpdateScene(CmdScore*, short, short)   [UpdateScene__12CmdScoreDataFP8CmdScoress]  size=0x464 */
void UpdateScene__12CmdScoreDataFP8CmdScoress(int param_1,int param_2,short param_3,short param_4)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  undefined1 auStack_a0 [40];
  float fStack_78;
  undefined4 uStack_74;
  float fStack_70;
  undefined4 uStack_6c;
  undefined4 *puStack_68;
  float fStack_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  uint uStack_50;
  undefined4 uStack_4c;
  int iStack_48;
  undefined4 *puStack_44;
  int iStack_40;
  int iStack_30;
  short sStack_20;
  short sStack_10;
  
  iStack_40 = param_1;
  iStack_30 = param_2;
  sStack_20 = param_3;
  sStack_10 = param_4;
  ClearImage__8FontDrawFv(param_1 + 0xb4);
  iStack_48 = ((int)sStack_20 >> 8 & 0xffU) + sStack_10 * 2;
  iVar2 = iStack_40 + 0xf4;
  for (iVar3 = 0; iVar3 < 2; iVar3 = iVar3 + 1) {
    uStack_54 = *(undefined4 *)
                 ((iStack_48 + iVar3 & 0xffffU) * 0xc + *(int *)(iStack_30 + 0x28) + 0x10);
    SetMessage__8MenuTextFPcUiUcUc(iVar2,uStack_54,*(byte *)(iVar2 + 0x58) & 7,0,1);
    OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_40 + 0xb4,iVar2,((ulong)*(byte *)(iVar2 + 0x58) & 0xf) >> 3,0);
    uStack_60 = *(undefined4 *)(iVar2 + 0x28);
    fStack_64 = *(float *)(iVar2 + 0x2c);
    (**(code **)(*(int *)(iVar2 + 8) + 0x24))
              ((float)(int)*(short *)((iVar3 + 1U & 0xffff) * 0x1c + *(int *)(iStack_30 + 0x44) +
                                     0x14) - fStack_64 / 2.0,uStack_60);
    iVar2 = iVar2 + 0x80;
  }
  puVar1 = (undefined4 *)(((int)sStack_20 & 0xfU) * 0xc + *(int *)(iStack_30 + 0x28) + 0x10);
  puStack_44 = puVar1 + ((int)sStack_20 >> 4 & 0xfU) * 3;
  iVar3 = ((int)sStack_20 & 0xfU) - 4;
  iVar2 = iStack_40 + 500;
  puStack_68 = puVar1;
  for (; puVar1 < puStack_44; puVar1 = puVar1 + 3) {
    uStack_58 = *puVar1;
    SetMessage__8MenuTextFPcUiUcUc(iVar2 + 0x50,uStack_58,*(byte *)(iVar2 + 0xa8) & 7,0,1);
    OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_40 + 0xb4,iVar2 + 0x50,((ulong)*(byte *)(iVar2 + 0xa8) & 0xf) >> 3,0);
    uStack_6c = *(undefined4 *)(iVar2 + 0x78);
    fStack_70 = *(float *)(iVar2 + 0x7c);
    (**(code **)(*(int *)(iVar2 + 0x58) + 0x24))
              ((float)(int)*(short *)(*(int *)(iStack_30 + 0x44) + 0xa0) - fStack_70,uStack_6c);
    uStack_4c = GetScore__8CmdScoreFsPcPc(iStack_30,(short)iVar3,puVar1[1],auStack_a0);
    SetMessage__8MenuTextFPcUiUcUc(iVar2 + 0xd0,auStack_a0,*(byte *)(iVar2 + 0x128) & 7,0,1);
    OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_40 + 0xb4,iVar2 + 0xd0,((ulong)*(byte *)(iVar2 + 0x128) & 0xf) >> 3,0);
    uStack_74 = *(undefined4 *)(iVar2 + 0xf8);
    fStack_78 = *(float *)(iVar2 + 0xfc);
    (**(code **)(*(int *)(iVar2 + 0xd8) + 0x24))
              ((float)(int)*(short *)(*(int *)(iStack_30 + 0x44) + 0xbc) - fStack_78,uStack_74);
    *(byte *)(iVar2 + 0x162) = *(byte *)(iVar2 + 0x162) & 0xfe;
    uStack_50 = (int)*(short *)(puVar1 + 2) & 0xff;
    if (uStack_50 != 0) {
      *(byte *)(iVar2 + 0x162) = *(byte *)(iVar2 + 0x162) & 0xfe | 1;
      uStack_5c = GetComment__8CmdScoreFsi(iStack_30,(short)uStack_50,uStack_4c);
      SetMessage__8MenuTextFPcUiUcUc(iVar2 + 0x150,uStack_5c,*(byte *)(iVar2 + 0x1a8) & 7,0,1);
      OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_40 + 0xb4,iVar2 + 0x150,((ulong)*(byte *)(iVar2 + 0x1a8) & 0xf) >> 3,0)
      ;
    }
    iVar3 = iVar3 + 1;
    iVar2 = iVar2 + 0x1d0;
  }
  return;
}

/* JP: 0x00476860  CmdScoreData::~CmdScoreData()   [@24@__dt__12CmdScoreDataFv]  size=0x8 */
undefined4 * _24___dt__12CmdScoreDataFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -6;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-4] = &__vt__12CmdScoreData;
    *param_1 = 0x408ad4;
    param_1[3] = 0x408ae0;
    __destroy_arr(param_1 + 0x77,0x476010,0x1d0,10);
    __destroy_arr(param_1 + 0x37,0x27c030,0x80,2);
    __dt__8FontDrawFv(param_1 + 0x27,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}

/* JP: 0x00476870  CmdScoreData::~CmdScoreData()   [@36@__dt__12CmdScoreDataFv]  size=0x8 */
undefined4 * _36___dt__12CmdScoreDataFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -9;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-7] = &__vt__12CmdScoreData;
    param_1[-3] = 0x408ad4;
    *param_1 = 0x408ae0;
    __destroy_arr(param_1 + 0x74,0x476010,0x1d0,10);
    __destroy_arr(param_1 + 0x34,0x27c030,0x80,2);
    __dt__8FontDrawFv(param_1 + 0x24,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}
