/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdLibraryDetail   functions: 6
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdLibraryDetail.md).
 */

/* JP: 0x004649a0  CmdLibraryDetail::CmdLibraryDetail()   [__ct__16CmdLibraryDetailFv]  size=0x1b4 */
int __ct__16CmdLibraryDetailFv(int param_1)

{
  __ct__9CmdWindowFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__16CmdLibraryDetail;
  *(undefined4 *)(param_1 + 0x18) = 0x4087e4;
  *(undefined4 *)(param_1 + 0x24) = 0x4087f0;
  __ct__8FontDrawFv(param_1 + 0xb4);
  __ct__8FontDrawFv(param_1 + 0xf4);
  __ct__11SendOnLocalFv(param_1 + 0x134);
  __construct_array(param_1 + 0x164,0x27bfd0,0x27c030,0x80,7);
  __ct__8MenuTextFv(param_1 + 0x4e4);
  __ct__8MenuTextFv(param_1 + 0x564);
  __ct__8MenuTextFv(param_1 + 0x5e4);
  __ct__8MenuTextFv(param_1 + 0x664);
  __ct__8MenuTextFv(param_1 + 0x6e4);
  __ct__8MenuTextFv(param_1 + 0x764);
  __construct_array(param_1 + 0x7e4,0x27bfd0,0x27c030,0x80,2);
  __construct_array(param_1 + 0x8e4,0x266140,0x2661a0,0x60,2);
  __construct_array(param_1 + 0x9a4,0x27bfd0,0x27c030,0x80,3);
  __construct_array(param_1 + 0xb24,0x27bfd0,0x27c030,0x80,0x12);
  return param_1;
}

/* JP: 0x00464b60  CmdLibraryDetail::~CmdLibraryDetail()   [__dt__16CmdLibraryDetailFv]  size=0x1e4 */
int __dt__16CmdLibraryDetailFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__16CmdLibraryDetail;
    *(undefined4 *)(param_1 + 0x18) = 0x4087e4;
    *(undefined4 *)(param_1 + 0x24) = 0x4087f0;
    __destroy_arr(param_1 + 0xb24,0x27c030,0x80,0x12);
    __destroy_arr(param_1 + 0x9a4,0x27c030,0x80,3);
    __destroy_arr(param_1 + 0x8e4,0x2661a0,0x60,2);
    __destroy_arr(param_1 + 0x7e4,0x27c030,0x80,2);
    __dt__8MenuTextFv(param_1 + 0x764,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1 + 0x6e4,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1 + 0x664,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1 + 0x5e4,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1 + 0x564,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1 + 0x4e4,0xffffffffffffffff);
    __destroy_arr(param_1 + 0x164,0x27c030,0x80,7);
    __dt__11SendOnLocalFv(param_1 + 0x134,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0xf4,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0xb4,0xffffffffffffffff);
    __dt__9CmdWindowFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x00464d50  CmdLibraryDetail::CreateScene(CmdLibrary*)   [CreateScene__16CmdLibraryDetailFP10CmdLibrary]  size=0x448 */
void CreateScene__16CmdLibraryDetailFP10CmdLibrary(int param_1,int param_2)

{
  ulong uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  float fVar6;
  float fVar7;
  undefined4 uVar8;
  
  SetData__9MenuSceneFUsP8FontDraw(param_2,1,param_1 + 0xb4);
  SetData__9MenuSceneFUsP8FontDraw(param_2,2,param_1 + 0xf4);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0xb4);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0xf4);
  iVar2 = param_1 + 0x164;
  uVar3 = 1;
  while( true ) {
    if (0xe < (int)uVar3) break;
    SetData__9MenuSceneFUsP8MenuText(param_2,uVar3 & 0xffff,iVar2);
    AddPlace__10MenuWindowFP9MenuPlace(param_1,iVar2);
    if ((int)uVar3 < 8) {
      SetMessage__8MenuTextFPcUiUcUc(iVar2,*(undefined4 *)
                             ((uint)*(ushort *)(iVar2 + 0x22) * 8 + *(int *)(param_2 + 0x24) + 0x10)
                      ,*(byte *)(iVar2 + 0x58) & 7,0,1);
      OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(param_1 + 0xb4,iVar2,((ulong)*(byte *)(iVar2 + 0x58) & 0xf) >> 3,0);
    }
    uVar3 = uVar3 + 1;
    iVar2 = iVar2 + 0x80;
  }
  SetData__9MenuSceneFUsP8MenuText(param_2,0xe,iVar2);
  fVar7 = *(float *)(iVar2 + 0x28);
  uVar8 = *(undefined4 *)(iVar2 + 0x24);
  uVar1 = GetRealHeight__8FontItemCFv(iVar2);
  if ((long)uVar1 < 0) {
    fVar6 = (float)(uVar1 & 0xffffffff);
  }
  else {
    fVar6 = (float)(int)uVar1;
  }
  (**(code **)(*(int *)(iVar2 + 8) + 0x24))(uVar8,fVar7 + fVar6);
  AddPlace__10MenuWindowFP9MenuPlace(param_1,iVar2);
  iVar5 = param_1 + 0x8e4;
  for (iVar4 = 0; iVar4 < 2; iVar4 = iVar4 + 1) {
    SetData__9MenuSceneFUsP10MenuSprite(param_2,1,iVar5);
    AddPlace__10MenuWindowFP9MenuPlace(param_1,iVar5);
    iVar5 = iVar5 + 0x60;
  }
  (**(code **)(*(int *)(param_1 + 0x94c) + 0x24))
            (*(undefined4 *)(param_1 + 0x968),*(undefined4 *)(iVar2 + 0x28));
  iVar2 = param_1 + 0x9a4;
  for (iVar4 = 0; iVar4 < 3; iVar4 = iVar4 + 1) {
    SetData__9MenuSceneFUsP8MenuText(param_2,0xf,iVar2);
    SetMessage__8MenuTextFPcUiUcUc(iVar2,*(undefined4 *)
                           ((uint)(ushort)((short)iVar4 + *(short *)(iVar2 + 0x22)) * 8 +
                            *(int *)(param_2 + 0x24) + 0x10),*(byte *)(iVar2 + 0x58) & 7,0,1);
    OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(param_1 + 0xb4,iVar2,((ulong)*(byte *)(iVar2 + 0x58) & 0xf) >> 3,0);
    AddPlace__10MenuWindowFP9MenuPlace(param_1,iVar2);
    iVar2 = iVar2 + 0x80;
  }
  for (uVar3 = param_1 + 0xb24; uVar3 < param_1 + 0x1424U; uVar3 = uVar3 + 0x80) {
    SetData__9MenuSceneFUsP8MenuText(param_2,0x10,uVar3);
    AddPlace__10MenuWindowFP9MenuPlace(param_1,uVar3);
  }
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(param_1 + 0x134,0x4216b0,uRam004216ac,1,0xffffffffffffffff);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0x134);
  SetData__9MenuSceneFUsP10MenuWindow(param_2,0,param_1);
  AddOT__7MenuObjFv(param_1);
  return;
}

/* JP: 0x004651a0  CmdLibraryDetail::UpdateScene(CmdLibrary*, short, unsigned char)   [UpdateScene__16CmdLibraryDetailFP10CmdLibrarysUc]  size=0xa9c */
void UpdateScene__16CmdLibraryDetailFP10CmdLibrarysUc
               (int param_1,int param_2,undefined2 param_3,byte param_4)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  ulong uVar5;
  byte bVar6;
  short sVar7;
  uint uVar8;
  uint *puVar9;
  short *psVar10;
  int iVar11;
  short sVar12;
  uint auStack_120 [4];
  uint uStack_110;
  undefined1 auStack_100 [24];
  short asStack_e8 [4];
  float afStack_e0 [2];
  uint auStack_d8 [4];
  undefined4 uStack_c8;
  undefined4 uStack_c4;
  int iStack_c0;
  int iStack_bc;
  int iStack_b8;
  undefined4 uStack_b4;
  undefined4 uStack_b0;
  undefined4 uStack_ac;
  undefined4 uStack_a8;
  int iStack_a4;
  undefined4 uStack_a0;
  int iStack_9c;
  int iStack_98;
  int iStack_94;
  undefined4 uStack_90;
  undefined4 uStack_8c;
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  undefined4 uStack_78;
  int iStack_74;
  undefined4 uStack_70;
  int iStack_6c;
  int iStack_68;
  float fStack_64;
  float fStack_60;
  uint uStack_5c;
  uint uStack_58;
  ushort uStack_54;
  short sStack_52;
  ushort uStack_50;
  ushort uStack_4e;
  ushort uStack_4c;
  ushort uStack_4a;
  ushort uStack_48;
  short sStack_46;
  short sStack_44;
  short sStack_42;
  int iStack_40;
  int iStack_30;
  undefined2 uStack_20;
  byte bStack_10;
  
  iStack_40 = param_1;
  iStack_30 = param_2;
  uStack_20 = param_3;
  bStack_10 = param_4;
  iVar2 = GetRegDat__9RegDatApiFiii(0x2e,param_3,0xffffffffffffffff);
  ClearImage__8FontDrawFv(iStack_40 + 0xf4);
  auStack_120[0] = (uint)*(ushort *)(iVar2 + 6);
  auStack_120[1] = (uint)*(ushort *)(iVar2 + 8);
  auStack_120[2] = *(undefined4 *)(iVar2 + 0x24);
  auStack_120[3] = *(undefined4 *)(iVar2 + 0x28);
  uStack_110 = (uint)*(ushort *)(iVar2 + 0x2c);
  puVar9 = auStack_120;
  uStack_5c = iStack_40 + 0x764;
  for (uVar8 = iStack_40 + 0x4e4; uVar8 < uStack_5c; uVar8 = uVar8 + 0x80) {
    uStack_50 = *(ushort *)(uVar8 + 0x22);
    uStack_48 = uStack_50;
    uStack_84 = *(undefined4 *)((uint)uStack_50 * 8 + *(int *)(iStack_30 + 0x24) + 0x10);
    uStack_88 = uStack_84;
    sprintf(auStack_100,uStack_84,*puVar9);
    SetMessage__8MenuTextFPcUiUcUc(uVar8,auStack_100,*(byte *)(uVar8 + 0x58) & 7,0,1);
    OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_40 + 0xf4,uVar8,((ulong)*(byte *)(uVar8 + 0x58) & 0xf) >> 3,0);
    puVar9 = puVar9 + 1;
  }
  sStack_52 = *(short *)(iStack_40 + 0x786);
  uStack_4a = (ushort)(((ulong)*(byte *)(iVar2 + 0x14) << 0x3a) >> 0x3d) + sStack_52;
  uStack_90 = *(undefined4 *)((uint)uStack_4a * 8 + *(int *)(iStack_30 + 0x24) + 0x10);
  uStack_8c = uStack_90;
  uStack_70 = uStack_90;
  SetMessage__8MenuTextFPcUiUcUc(iStack_40 + 0x764,uStack_90,*(byte *)(iStack_40 + 0x7bc) & 7,0,1);
  OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_40 + 0xf4,iStack_40 + 0x764,
                  ((ulong)*(byte *)(iStack_40 + 0x7bc) & 0xf) >> 3,0);
  iVar11 = iStack_40 + 0x8e4;
  iVar3 = iStack_40 + 0x7e4;
  psVar10 = (short *)(iVar2 + 0x1a);
  for (sVar7 = 0; sVar7 < 2; sVar7 = sVar7 + 1) {
    *(byte *)(iVar3 + 0x12) = *(byte *)(iVar3 + 0x12) & 0xfe;
    *(byte *)(iVar11 + 0x12) = *(byte *)(iVar11 + 0x12) & 0xfe;
    if (-1 < *psVar10) {
      if (((uint)bStack_10 & 1 << ((int)sVar7 & 0x1fU)) == 0) {
        uStack_54 = *(ushort *)(iVar3 + 0x22);
        uStack_ac = *(undefined4 *)((uint)uStack_54 * 8 + *(int *)(iStack_30 + 0x24) + 0x10);
        uStack_a8 = uStack_ac;
        uStack_7c = uStack_ac;
        uStack_4c = uStack_54;
        SetMessage__8MenuTextFPcUiUcUc(iVar3,uStack_ac,*(byte *)(iVar3 + 0x58) & 7,0,1);
        uStack_b0 = *(undefined4 *)(iVar3 + 0x28);
        uStack_b4 = *(undefined4 *)(iVar11 + 0x24);
        (**(code **)(*(int *)(iVar3 + 8) + 0x24))(uStack_b4,uStack_b0);
      }
      else {
        iStack_94 = *(int *)(iStack_30 + 0x10);
        iStack_9c = iStack_94 + 0x28;
        sStack_42 = *psVar10 / 100;
        sStack_44 = *psVar10 + sStack_42 * -100;
        iStack_98 = iStack_9c;
        iStack_74 = iStack_94;
        iStack_68 = iStack_9c;
        iVar4 = Find__13MenuDataTableFs(iStack_9c,0x16);
        iVar4 = sStack_42 * 0xc + iVar4;
        iStack_6c = iVar4 + 0x10;
        cVar1 = *(char *)(iVar4 + 0x1a);
        sStack_46 = (short)cVar1;
        if (cVar1 < '\0') {
          iVar4 = Find__13MenuDataTableFs(iStack_68,8);
          sStack_46 = (short)*(char *)(sStack_44 * 0xc + iVar4 + 0x18);
        }
        uStack_78 = GetRegDat__9RegDatApiFiii(*(undefined2 *)(iStack_6c + 2),sStack_44,0xffffffffffffffff);
        SetMessage__8MenuTextFPcUiUcUc(iVar3,uStack_78,*(byte *)(iVar3 + 0x58) & 7,0,1);
        uStack_a0 = *(undefined4 *)(iVar3 + 0x28);
        iStack_a4 = *(int *)(iStack_30 + 0x44) + 0x198;
        (**(code **)(*(int *)(iVar3 + 8) + 0x24))
                  ((float)(int)*(short *)(*(int *)(iStack_30 + 0x44) + 0x19c),uStack_a0);
        SetIcon__10MenuCommonFcP10MenuSprite((char)sStack_46,iVar11);
        *(byte *)(iVar11 + 0x12) = *(byte *)(iVar11 + 0x12) & 0xfe | 1;
      }
      OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_40 + 0xf4,iVar3,((ulong)*(byte *)(iVar3 + 0x58) & 0xf) >> 3,0);
      *(byte *)(iVar3 + 0x12) = *(byte *)(iVar3 + 0x12) & 0xfe | 1;
    }
    iVar3 = iVar3 + 0x80;
    psVar10 = psVar10 + 1;
    iVar11 = iVar11 + 0x60;
  }
  memset(auStack_d8,0,0xc);
  uStack_58 = 0;
  iStack_b8 = *(int *)(iStack_30 + 0x44) + 0x1b4;
  fStack_60 = (float)(int)*(short *)(*(int *)(iStack_30 + 0x44) + 0x1ba);
  iVar3 = *(int *)(iStack_30 + 0x44);
  iStack_bc = iVar3 + 0x1d0;
  afStack_e0[0] = (float)(int)*(short *)(iVar3 + 0x1d4);
  asStack_e8[0] = *(short *)(iVar3 + 0x1dc);
  iVar3 = *(int *)(iStack_30 + 0x44);
  iStack_c0 = iVar3 + 0x1ec;
  afStack_e0[1] = (float)(int)*(short *)(iVar3 + 0x1f0);
  asStack_e8[1] = *(undefined2 *)(iVar3 + 0x1f8);
  asStack_e8[2] = asStack_e8[1];
  uVar5 = GetRealHeight__8FontItemCFv(iStack_40 + 0xb24);
  if ((long)uVar5 < 0) {
    fStack_64 = (float)(uVar5 & 0xffffffff);
  }
  else {
    fStack_64 = (float)(int)uVar5;
  }
  auStack_120[0] = (uint)*(ushort *)(iVar2 + 0x32);
  auStack_d8[0] = (uint)*(byte *)(iVar2 + 0x34) | (auStack_120[0] & 0x3ff0) << 4;
  bVar6 = *(byte *)(iVar2 + 0x32) & 3;
  if (bVar6 == 3) {
    auStack_d8[2] = 1;
  }
  else if (bVar6 == 2) {
    auStack_d8[1] = 1;
  }
  else if (bVar6 == 1) {
    auStack_d8[0] = auStack_d8[0] | 0x80;
  }
  uVar5 = ((ulong)*(byte *)(iVar2 + 0x32) & 0xf) >> 2;
  if (uVar5 == 3) {
    auStack_d8[2] = auStack_d8[2] | 4;
  }
  else if (uVar5 == 2) {
    auStack_d8[1] = auStack_d8[1] | 4;
  }
  else if (uVar5 == 1) {
    auStack_d8[0] = auStack_d8[0] | 0x100;
  }
  puVar9 = auStack_d8;
  iVar2 = iStack_40 + 0x9a4;
  uVar8 = iStack_40 + 0xb24;
  for (sVar7 = 0; sVar7 < 3; sVar7 = sVar7 + 1) {
    *(byte *)(iVar2 + 0x12) = *(byte *)(iVar2 + 0x12) & 0xfe;
    if (*puVar9 != 0) {
      *(byte *)(iVar2 + 0x12) = *(byte *)(iVar2 + 0x12) & 0xfe | 1;
      uStack_c4 = *(undefined4 *)(iVar2 + 0x24);
      (**(code **)(*(int *)(iVar2 + 8) + 0x24))(uStack_c4,fStack_60);
      fStack_60 = fStack_60 + fStack_64;
      for (sVar12 = 0; sVar12 < 0x12; sVar12 = sVar12 + 1) {
        if ((*puVar9 & 1 << ((int)sVar12 & 0x1fU)) != 0) {
          uStack_4e = sVar12 + asStack_e8[sVar7];
          auStack_d8[3] = *(undefined4 *)((uint)uStack_4e * 8 + *(int *)(iStack_30 + 0x24) + 0x10);
          uStack_c8 = auStack_d8[3];
          uStack_80 = auStack_d8[3];
          SetMessage__8MenuTextFPcUiUcUc(uVar8,auStack_d8[3],*(byte *)(uVar8 + 0x58) & 7,0,1);
          OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_40 + 0xf4,uVar8,((ulong)*(byte *)(uVar8 + 0x58) & 0xf) >> 3,0);
          (**(code **)(*(int *)(uVar8 + 8) + 0x24))(afStack_e0[uStack_58],fStack_60);
          *(byte *)(uVar8 + 0x12) = *(byte *)(uVar8 + 0x12) & 0xfe | 1;
          uStack_58 = uStack_58 ^ 1;
          if (uStack_58 == 0) {
            fStack_60 = fStack_60 + fStack_64;
          }
          uVar8 = uVar8 + 0x80;
        }
      }
      uStack_58 = 0;
      fStack_60 = fStack_60 + fStack_64;
    }
    iVar2 = iVar2 + 0x80;
    puVar9 = puVar9 + 1;
  }
  for (; uVar8 < iStack_40 + 0x1424U; uVar8 = uVar8 + 0x80) {
    *(byte *)(uVar8 + 0x12) = *(byte *)(uVar8 + 0x12) & 0xfe;
  }
  return;
}

/* JP: 0x00465c40  CmdLibraryDetail::~CmdLibraryDetail()   [@24@__dt__16CmdLibraryDetailFv]  size=0x8 */
undefined4 * _24___dt__16CmdLibraryDetailFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -6;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-4] = &__vt__16CmdLibraryDetail;
    *param_1 = 0x4087e4;
    param_1[3] = 0x4087f0;
    __destroy_arr(param_1 + 0x2c3,0x27c030,0x80,0x12);
    __destroy_arr(param_1 + 0x263,0x27c030,0x80,3);
    __destroy_arr(param_1 + 0x233,0x2661a0,0x60,2);
    __destroy_arr(param_1 + 499,0x27c030,0x80,2);
    __dt__8MenuTextFv(param_1 + 0x1d3,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1 + 0x1b3,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1 + 0x193,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1 + 0x173,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1 + 0x153,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1 + 0x133,0xffffffffffffffff);
    __destroy_arr(param_1 + 0x53,0x27c030,0x80,7);
    __dt__11SendOnLocalFv(param_1 + 0x47,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x37,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x27,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}

/* JP: 0x00465c50  CmdLibraryDetail::~CmdLibraryDetail()   [@36@__dt__16CmdLibraryDetailFv]  size=0x8 */
undefined4 * _36___dt__16CmdLibraryDetailFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -9;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-7] = &__vt__16CmdLibraryDetail;
    param_1[-3] = 0x4087e4;
    *param_1 = 0x4087f0;
    __destroy_arr(param_1 + 0x2c0,0x27c030,0x80,0x12);
    __destroy_arr(param_1 + 0x260,0x27c030,0x80,3);
    __destroy_arr(param_1 + 0x230,0x2661a0,0x60,2);
    __destroy_arr(param_1 + 0x1f0,0x27c030,0x80,2);
    __dt__8MenuTextFv(param_1 + 0x1d0,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1 + 0x1b0,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1 + 400,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1 + 0x170,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1 + 0x150,0xffffffffffffffff);
    __dt__8MenuTextFv(param_1 + 0x130,0xffffffffffffffff);
    __destroy_arr(param_1 + 0x50,0x27c030,0x80,7);
    __dt__11SendOnLocalFv(param_1 + 0x44,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x34,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x24,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}
