/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdScoreRank   functions: 6
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdScoreRank.md).
 */

/* JP: 0x00476880  CmdScoreRank::CmdScoreRank()   [__ct__12CmdScoreRankFv]  size=0x6c */
int __ct__12CmdScoreRankFv(int param_1)

{
  __ct__9CmdWindowFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__12CmdScoreRank;
  *(undefined4 *)(param_1 + 0x18) = 0x408b14;
  *(undefined4 *)(param_1 + 0x24) = 0x408b20;
  __ct__8FontDrawFv(param_1 + 0xb4);
  return param_1;
}

/* JP: 0x004768f0  CmdScoreRank::~CmdScoreRank()   [__dt__12CmdScoreRankFv]  size=0xd4 */
int __dt__12CmdScoreRankFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__12CmdScoreRank;
    *(undefined4 *)(param_1 + 0x18) = 0x408b14;
    *(undefined4 *)(param_1 + 0x24) = 0x408b20;
    if (*(int *)(param_1 + 0xf4) != 0) {
      __destroy_new_array(*(undefined4 *)(param_1 + 0xf4),0x4769d0);
    }
    __dt__8FontDrawFv(param_1 + 0xb4,0xffffffffffffffff);
    __dt__9CmdWindowFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x00476a60  CmdScoreRank::CreateScene(CmdScore*)   [CreateScene__12CmdScoreRankFP8CmdScore]  size=0x4c8 */
void CreateScene__12CmdScoreRankFP8CmdScore(int param_1,int param_2)

{
  short sVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined8 uVar5;
  undefined4 *puVar6;
  short sVar7;
  undefined4 uStack_90;
  undefined2 uStack_8c;
  undefined2 uStack_8a;
  short sStack_88;
  undefined1 uStack_84;
  undefined1 uStack_83;
  undefined1 uStack_82;
  undefined1 uStack_81;
  undefined1 auStack_80 [36];
  float fStack_5c;
  undefined4 uStack_58;
  float fStack_54;
  undefined4 uStack_50;
  float fStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  int iStack_40;
  int iStack_3c;
  int iStack_38;
  float fStack_34;
  undefined4 uStack_30;
  int iStack_2c;
  float fStack_28;
  byte bStack_21;
  int iStack_20;
  int iStack_10;
  
  uStack_90 = 0;
  uStack_8c = 0;
  uStack_8a = 0;
  uStack_84 = 0;
  uStack_83 = 0;
  uStack_82 = 0;
  uStack_81 = 0;
  iStack_20 = param_1;
  iStack_10 = param_2;
  iVar2 = GetRank__12CmdScoreRankFP8CmdScore(param_1,param_2);
  iStack_38 = *(int *)(iStack_10 + 0x10);
  iStack_40 = iStack_38 + 0x28;
  iStack_3c = iStack_40;
  iStack_2c = iStack_38;
  iVar3 = Find__13MenuDataTableFs(iStack_40,0x2b);
  puVar6 = (undefined4 *)(iVar3 + 0x10);
  sVar1 = (short)*(undefined4 *)(iVar3 + 8);
  uVar5 = __nwa__FUi(sVar1 * 0x150 + 0x10);
  uStack_44 = __construct_new_array(uVar5,0x476f30,0x4769d0,0x150,sVar1);
  *(undefined4 *)(iStack_20 + 0xf4) = uStack_44;
  iVar3 = *(int *)(iStack_20 + 0xf4);
  SetData__9MenuSceneFUsP8FontDraw(iStack_10,2,iStack_20 + 0xb4);
  AddPriority__12MenuObjTableFP7MenuObj(iStack_20 + 0x18,iStack_20 + 0xb4);
  fStack_28 = 0.0;
  for (sVar7 = 0; sVar7 < sVar1; sVar7 = sVar7 + 1) {
    SetData__9MenuSceneFUsP8MenuText(iStack_10,8,iVar3 + 0x50);
    sprintf(auStack_80,*(undefined4 *)(*(int *)(iStack_10 + 0x28) + 0x134),puVar6[1]);
    SetMessage__8MenuTextFPcUiUcUc(iVar3 + 0x50,auStack_80,*(byte *)(iVar3 + 0xa8) & 7,1,0);
    bStack_21 = (byte)(((ulong)*(byte *)(iVar3 + 0xa8) << 0x3c) >> 0x3f);
    OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_20 + 0xb4,iVar3 + 0x50,bStack_21,&uStack_90);
    uStack_48 = *(undefined4 *)(iVar3 + 0x78);
    fStack_4c = *(float *)(iVar3 + 0x74);
    (**(code **)(*(int *)(iVar3 + 0x58) + 0x24))(fStack_4c - (float)(int)sStack_88,uStack_48);
    SetData__9MenuSceneFUsP8MenuText(iStack_10,9,iVar3 + 0xd0);
    uStack_30 = *puVar6;
    SetMessage__8MenuTextFPcUiUcUc(iVar3 + 0xd0,uStack_30,*(byte *)(iVar3 + 0x128) & 7,0,0);
    OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_20 + 0xb4,iVar3 + 0xd0,((ulong)*(byte *)(iVar3 + 0x128) & 0xf) >> 3,
                    &uStack_90);
    uStack_50 = *(undefined4 *)(iVar3 + 0xf8);
    fStack_54 = *(float *)(iVar3 + 0xf4);
    iVar4 = (int)sStack_88;
    if (sStack_88 < 0) {
      iVar4 = iVar4 + 1;
    }
    (**(code **)(*(int *)(iVar3 + 0xd8) + 0x24))(fStack_54 - (float)(iVar4 >> 1),uStack_50);
    AddPlace__9MenuGroupFP9MenuPlace(iVar3,iVar3 + 0x50);
    AddPlace__9MenuGroupFP9MenuPlace(iVar3,iVar3 + 0xd0);
    if (iVar2 == puVar6[1]) {
      *(undefined4 **)(iStack_20 + 0xf8) = puVar6;
    }
    else {
      DisableFontItem__8FontItemFv(iVar3 + 0x50);
      DisableFontItem__8FontItemFv(iVar3 + 0xd0);
    }
    SetData__9MenuSceneFUsP9MenuGroup(iStack_10,1,iVar3);
    *(undefined2 *)(iVar3 + 0x1c) = 0;
    *(short *)(iVar3 + 0x1e) = sVar7;
    uStack_58 = *(undefined4 *)(iVar3 + 0x24);
    (**(code **)(*(int *)(iVar3 + 8) + 0x24))(uStack_58,fStack_28);
    AddPlace__10MenuWindowFP9MenuPlace(iStack_20,iVar3);
    fStack_5c = *(float *)(iVar3 + 0x30);
    fStack_28 = fStack_28 + fStack_5c;
    puVar6 = puVar6 + 2;
    iVar3 = iVar3 + 0x150;
  }
  SetData__9MenuSceneFUsP10MenuWindow(iStack_10,3,iStack_20);
  fStack_34 = *(float *)(*(int *)(iStack_20 + 0x40) + 0x20) * 0.25;
  *(undefined2 *)(*(int *)(iStack_20 + 0x40) + 0x34) = 2;
  *(undefined4 *)(*(int *)(iStack_20 + 0x40) + 0x2c) = 0;
  *(float *)(*(int *)(iStack_20 + 0x40) + 0x30) = fStack_34;
  *(int *)(*(int *)(iStack_20 + 0x40) + 0x38) = iStack_20 + 0xb4;
  SetScroll__10MenuWindowFss(iStack_20,0,sVar1);
  Scroll__10MenuWindowFss(iStack_20,0,(short)iVar2 + -2);
  AddOT__7MenuObjFv(iStack_20);
  return;
}

/* JP: 0x00476f80  CmdScoreRank::GetRank(CmdScore*)   [GetRank__12CmdScoreRankFP8CmdScore]  size=0x9c8 */
int GetRank__12CmdScoreRankFP8CmdScore(undefined8 param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  int iVar6;
  int iStack_60;
  int iStack_54;
  uint uStack_50;
  float fStack_4c;
  float fStack_48;
  float fStack_44;
  float fStack_40;
  float fStack_3c;
  float fStack_34;
  float fStack_30;
  
  piVar1 = *(int **)(param_2 + 0x70);
  iVar6 = *piVar1;
  fVar3 = (float)iVar6;
  iVar5 = *(int *)(param_2 + 0x88);
  iVar2 = iVar6;
  if (iVar5 < iVar6) {
    iVar2 = iVar5;
  }
  fVar4 = (float)iVar2;
  fStack_30 = 0.0;
  if (iVar5 != 0) {
    fStack_30 = ((float)*(uint *)(param_2 + 0x90) / (float)iVar5) * 100.0;
    fStack_30 = fStack_30 * fStack_30;
  }
  if (iVar2 < 0x70) {
    fStack_3c = (fVar4 * fStack_30 * fVar4) / 1e+06;
  }
  else if (iVar2 < 0x1204) {
    fStack_3c = fStack_30 / (82.12 - fVar4 / 100.0);
  }
  else {
    fStack_3c = fStack_30 / 36.0;
  }
  iVar5 = *(int *)(param_2 + 0x8c);
  iVar2 = iVar6;
  if (iVar5 < iVar6) {
    iVar2 = iVar5;
  }
  fVar4 = (float)iVar2;
  fStack_30 = 0.0;
  if (iVar5 != 0) {
    fStack_30 = ((float)*(uint *)(param_2 + 0x94) / (float)iVar5) * 100.0;
    fStack_30 = fStack_30 * fStack_30;
  }
  if (iVar2 < 200) {
    fStack_40 = (fVar4 * fStack_30 * fVar4) / 1e+06;
  }
  else if (iVar2 < 0x19c8) {
    fStack_40 = fStack_30 / (27.0 - fVar4 / 300.0);
  }
  else {
    fStack_40 = fStack_30 / 9.0;
  }
  iVar5 = *(int *)(param_2 + 0x98);
  iVar2 = iVar6;
  if (iVar5 < iVar6) {
    iVar2 = iVar5;
  }
  fVar4 = (float)iVar2;
  fStack_30 = 0.0;
  if (iVar5 != 0) {
    fStack_30 = ((float)*(uint *)(param_2 + 0x9c) / (float)iVar5) * 100.0;
    fStack_30 = fStack_30 * fStack_30;
  }
  if (iVar2 < 0x7d) {
    fStack_44 = (fVar4 * fStack_30 * fVar4) / 1e+06;
  }
  else if (iVar2 < 0xfb9) {
    fStack_44 = fStack_30 / (64.25 - fVar4 / 100.0);
  }
  else {
    fStack_44 = fStack_30 / 25.0;
  }
  fStack_34 = 0.0;
  if (iVar6 != 0) {
    fStack_34 = (float)*(uint *)(param_2 + 0xa0) / fVar3;
  }
  if (iVar6 < 0xc9) {
    fVar4 = 9.0 - fVar3 * 0.03;
    fStack_48 = (fStack_34 * 900.0) / (fVar4 * fVar4);
  }
  else if (iVar6 < 0x1451) {
    fStack_48 = fStack_34 * (fVar3 * 0.02 + 96.0);
  }
  else {
    fStack_48 = fStack_34 * 200.0;
  }
  iVar5 = **(int **)(param_2 + 0x74);
  fVar4 = (float)iVar5;
  fStack_30 = 0.0;
  if (iVar5 != 0) {
    fStack_30 = ((float)(*(int **)(param_2 + 0x74))[1] / (float)iVar5) * 100.0;
    fStack_30 = fStack_30 * fStack_30;
  }
  if (iVar5 < 100) {
    fStack_4c = (fVar4 * fStack_30 * fVar4) / 250000.0;
  }
  else if (iVar5 < 0x6a4) {
    fStack_4c = fStack_30 / (26.0 - fVar4 / 100.0);
  }
  else {
    fStack_4c = fStack_30 / 9.0;
  }
  iVar5 = (int)(fStack_4c + fStack_48 * 2.0 + fStack_44 * 2.0 + fStack_3c * 2.0 + fStack_40 * 3.0);
  if (iVar5 < 0x3e9) {
    uStack_50 = iVar5 / 10;
    iStack_54 = 0;
  }
  else {
    uStack_50 = 100;
    iStack_54 = (iVar5 + -1000) / 0x14;
  }
  if ((uint)piVar1[2] < uStack_50) {
    uStack_50 = piVar1[2];
  }
  if (100 < (int)uStack_50) {
    uStack_50 = 100;
  }
  iStack_54 = (0x65 - uStack_50) - iStack_54;
  if (iStack_54 < 1) {
    iStack_54 = 1;
  }
  else if (99 < iStack_54) {
    iStack_54 = 99;
  }
  iStack_60 = 0;
  if (iVar6 != 0) {
    if (iVar6 == 0) {
      trap(7);
    }
    if (iVar6 == 0) {
      trap(7);
    }
    if (iVar6 == 0) {
      trap(7);
    }
    iStack_60 = (*(int *)(param_2 + 0x84) * 0x14) / iVar6 +
                (piVar1[1] * 0x32) / iVar6 + (*(int *)(param_2 + 0x80) * 0x14) / iVar6;
  }
  fVar3 = (fVar3 / 1000.0) * (fVar3 / 1000.0);
  iVar6 = (int)fVar3;
  fVar4 = (float)floorf(fVar3);
  if (fVar3 - fVar4 != 0.0) {
    iVar6 = iVar6 + 1;
  }
  iVar6 = 0x65 - iVar6;
  if (iVar6 < 1) {
    iVar6 = 1;
  }
  if (iStack_54 + iStack_60 < iVar6) {
    iVar6 = iStack_54 + iStack_60;
  }
  if (iVar6 < 1) {
    iVar6 = 1;
  }
  else if (99 < iVar6) {
    iVar6 = 99;
  }
  return iVar6;
}

/* JP: 0x00477950  CmdScoreRank::~CmdScoreRank()   [@24@__dt__12CmdScoreRankFv]  size=0x8 */
undefined4 * _24___dt__12CmdScoreRankFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -6;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-4] = &__vt__12CmdScoreRank;
    *param_1 = 0x408b14;
    param_1[3] = 0x408b20;
    if (param_1[0x37] != 0) {
      __destroy_new_array(param_1[0x37],0x4769d0);
    }
    __dt__8FontDrawFv(param_1 + 0x27,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}

/* JP: 0x00477960  CmdScoreRank::~CmdScoreRank()   [@36@__dt__12CmdScoreRankFv]  size=0x8 */
undefined4 * _36___dt__12CmdScoreRankFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -9;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-7] = &__vt__12CmdScoreRank;
    param_1[-3] = 0x408b14;
    *param_1 = 0x408b20;
    if (param_1[0x34] != 0) {
      __destroy_new_array(param_1[0x34],0x4769d0);
    }
    __dt__8FontDrawFv(param_1 + 0x24,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}
