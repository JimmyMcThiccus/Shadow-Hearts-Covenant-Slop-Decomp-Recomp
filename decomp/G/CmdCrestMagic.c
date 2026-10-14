/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdCrestMagic   functions: 6
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdCrestMagic.md).
 */

/* JP: 0x00497490  CmdCrestMagic::CmdCrestMagic()   [__ct__13CmdCrestMagicFv]  size=0x15c */
int __ct__13CmdCrestMagicFv(int param_1)

{
  __ct__9CmdWindowFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__13CmdCrestMagic;
  *(undefined4 *)(param_1 + 0x18) = 0x409414;
  *(undefined4 *)(param_1 + 0x24) = 0x409420;
  __ct__11MenuTextureFv(param_1 + 0xb8);
  __ct__11SendOnLocalFv(param_1 + 0xf8);
  __ct__11SendOnLocalFv(param_1 + 0x128);
  __construct_array(param_1 + 0x158,0x266140,0x2661a0,0x60,10);
  __ct__11MenuPolygonFv(param_1 + 0x518);
  __ct__8FontDrawFv(param_1 + 0x59c);
  __ct__8FontDrawFv(param_1 + 0x5dc);
  __construct_array(param_1 + 0x61c,0x27bfd0,0x27c030,0x80,2);
  __construct_array(param_1 + 0x71c,0x27bfd0,0x27c030,0x80,8);
  __construct_array(param_1 + 0xb1c,0x266140,0x2661a0,0x60,4);
  return param_1;
}

/* JP: 0x004975f0  CmdCrestMagic::~CmdCrestMagic()   [__dt__13CmdCrestMagicFv]  size=0x18c */
int __dt__13CmdCrestMagicFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__13CmdCrestMagic;
    *(undefined4 *)(param_1 + 0x18) = 0x409414;
    *(undefined4 *)(param_1 + 0x24) = 0x409420;
    __destroy_arr(param_1 + 0xb1c,0x2661a0,0x60,4);
    __destroy_arr(param_1 + 0x71c,0x27c030,0x80,8);
    __destroy_arr(param_1 + 0x61c,0x27c030,0x80,2);
    __dt__8FontDrawFv(param_1 + 0x5dc,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x59c,0xffffffffffffffff);
    __dt__11MenuPolygonFv(param_1 + 0x518,0xffffffffffffffff);
    __destroy_arr(param_1 + 0x158,0x2661a0,0x60,10);
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

/* JP: 0x00497780  CmdCrestMagic::CreateScene(CmdCrest*, MenuTexture*)   [CreateScene__13CmdCrestMagicFP8CmdCrestP11MenuTexture]  size=0x504 */
void CreateScene__13CmdCrestMagicFP8CmdCrestP11MenuTexture(int param_1,int param_2,int param_3)

{
  ulong uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  float fVar5;
  undefined4 uStack_40;
  
  SetData__9MenuSceneFUsP8FontDraw(param_2,1,param_1 + 0x59c);
  SetData__9MenuSceneFUsP8FontDraw(param_2,2,param_1 + 0x5dc);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0x59c);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0x5dc);
  SetData__9MenuSceneFUsP11MenuPolygon(param_2,2,param_1 + 0x518);
  AddPlace__10MenuWindowFP9MenuPlace(param_1,param_1 + 0x518);
  iVar4 = param_1 + 0x158;
  uVar2 = 4;
  while( true ) {
    if (0xd < (int)uVar2) break;
    SetData__9MenuSceneFUsP10MenuSprite(param_2,uVar2 & 0xffff,iVar4);
    AddPlace__10MenuWindowFP9MenuPlace(param_1,iVar4);
    iVar4 = iVar4 + 0x60;
    uVar2 = uVar2 + 1;
  }
  iVar4 = param_1 + 0x61c;
  uVar2 = 4;
  while( true ) {
    if (5 < (int)uVar2) break;
    SetData__9MenuSceneFUsP8MenuText(param_2,uVar2 & 0xffff,iVar4);
    SetMessage__8MenuTextFPcUiUcUc(iVar4,*(undefined4 *)
                           ((uint)*(ushort *)(iVar4 + 0x22) * 8 + *(int *)(param_2 + 0x24) + 0x10),
                    *(byte *)(iVar4 + 0x58) & 7,0,1);
    OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(param_1 + 0x59c,iVar4,((ulong)*(byte *)(iVar4 + 0x58) & 0xf) >> 3,0);
    AddPlace__10MenuWindowFP9MenuPlace(param_1,iVar4);
    iVar4 = iVar4 + 0x80;
    uVar2 = uVar2 + 1;
  }
  uStack_40 = 0.0;
  iVar4 = param_1 + 0xb1c;
  uVar2 = param_1 + 0x71c;
  while( true ) {
    if (param_1 + 0xb1cU <= uVar2) break;
    SetData__9MenuSceneFUsP8MenuText(param_2,6,uVar2);
    (**(code **)(*(int *)(uVar2 + 8) + 0x24))
              (*(undefined4 *)(uVar2 + 0x24),uStack_40 + *(float *)(uVar2 + 0x28));
    AddPlace__10MenuWindowFP9MenuPlace(param_1,uVar2);
    iVar3 = uVar2 + 0x80;
    SetData__9MenuSceneFUsP8MenuText(param_2,7,iVar3);
    (**(code **)(*(int *)(uVar2 + 0x88) + 0x24))
              (*(undefined4 *)(uVar2 + 0xa4),uStack_40 + *(float *)(uVar2 + 0xa8));
    AddPlace__10MenuWindowFP9MenuPlace(param_1,iVar3);
    SetData__9MenuSceneFUsP10MenuSprite(param_2,0xe,iVar4);
    (**(code **)(*(int *)(iVar4 + 8) + 0x24))
              (*(undefined4 *)(iVar4 + 0x24),uStack_40 + *(float *)(iVar4 + 0x28));
    AddPlace__10MenuWindowFP9MenuPlace(param_1,iVar4);
    uVar1 = GetRealHeight__8FontItemCFv(iVar3);
    if ((long)uVar1 < 0) {
      fVar5 = (float)(uVar1 & 0xffffffff);
    }
    else {
      fVar5 = (float)(int)uVar1;
    }
    uStack_40 = uStack_40 + fVar5;
    uVar2 = uVar2 + 0x100;
    iVar4 = iVar4 + 0x60;
  }
  Create__11MenuTextureFPUc6GS_PSMUii(param_1 + 0xb8,*(undefined4 *)(*(int *)(param_2 + 0x54) + 0x28),0x30,0,0);
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(param_1 + 0xf8,param_1 + 0xd0,*(undefined4 *)(param_1 + 0xcc),1,0xffffffffffffffff
                 );
  *(short *)(param_1 + 0x10c) = *(short *)(param_1 + 0xb30) + -1;
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0xf8);
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(param_1 + 0x128,param_3 + 0x18,*(undefined4 *)(param_3 + 0x14),1,
                  0xffffffffffffffff);
  *(short *)(param_1 + 0x13c) = *(short *)(param_1 + 0x16c) + -1;
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0x128);
  SetData__9MenuSceneFUsP10MenuWindow(param_2,1,param_1);
  AddOT__7MenuObjFv(param_1);
  return;
}

/* JP: 0x00497c90  CmdCrestMagic::UpdateScene(CmdCrest*, short, char)   [UpdateScene__13CmdCrestMagicFP8CmdCrestsc]  size=0x4b4 */
void UpdateScene__13CmdCrestMagicFP8CmdCrestsc(int param_1,int param_2,short param_3,char param_4)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  long lVar5;
  int iVar6;
  uint uVar7;
  ulong uVar8;
  uint uVar9;
  short *psVar10;
  char cVar11;
  undefined4 uVar12;
  undefined1 auStack_78 [12];
  undefined4 uStack_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  int iStack_60;
  int iStack_5c;
  undefined4 uStack_58;
  int iStack_54;
  uint uStack_50;
  undefined4 uStack_4c;
  ushort uStack_48;
  ushort uStack_46;
  ushort uStack_44;
  byte bStack_42;
  byte bStack_41;
  int iStack_40;
  int iStack_30;
  short sStack_20;
  char cStack_10;
  
  iVar2 = *(int *)(param_2 + 0x5c);
  iStack_60 = *(int *)(param_2 + 0x9b0);
  uStack_64 = *(undefined4 *)(param_2 + 0x70);
  uVar9 = param_1 + 0x71c;
  uStack_50 = param_1 + 0xb1c;
  for (iVar6 = 0; iVar6 < 4; iVar6 = iVar6 + 1) {
    iVar3 = param_1 + iVar6 * 0x60;
    *(byte *)(iVar3 + 0xb2e) = *(byte *)(iVar3 + 0xb2e) & 0xfe;
  }
  if (-1 < param_3) {
    iStack_5c = iVar2;
    iStack_54 = iStack_60;
    uStack_4c = uStack_64;
    iStack_40 = param_1;
    iStack_30 = param_2;
    sStack_20 = param_3;
    cStack_10 = param_4;
    ClearImage__8FontDrawFv(param_1 + 0x5dc);
    iVar3 = GetRegDat__9RegDatApiFiii(0x37,sStack_20,0xffffffffffffffff);
    psVar10 = (short *)(iVar3 + 8);
    iVar6 = (int)sStack_20;
    if (sStack_20 < 0) {
      iVar6 = iVar6 + 7;
    }
    uVar8 = (long)sStack_20 & 7;
    uVar7 = (uint)uVar8;
    if (((long)sStack_20 < 0) && (uVar8 != 0)) {
      uVar7 = uVar7 - 8;
    }
    bStack_42 = (byte)((int)(uint)*(byte *)(*(int *)(iVar2 + 8) + (iVar6 >> 3) + 0x16a) >>
                      (uVar7 & 0x1f)) & 1;
    uStack_44 = *(ushort *)(iVar3 + 6);
    iVar6 = iStack_40 + 0xb1c;
    bStack_41 = bStack_42;
    for (uVar7 = 0; (int)uVar7 < 4; uVar7 = uVar7 + 1) {
      if ((-1 < *psVar10) && ((((uint)uStack_44 & 1 << (uVar7 & 0x1f)) == 0 || (bStack_41 != 0)))) {
        iVar3 = GetRegDat__9RegDatApiFiii(0x38,*psVar10,0xffffffffffffffff);
        uVar4 = (uint)*(ushort *)(iVar3 + 0x1e);
        uVar12 = 7;
        cVar11 = cStack_10 + *(char *)(iStack_54 + *psVar10);
        if ('\x01' < cVar11) {
          uVar1 = (int)(uint)*(ushort *)(iVar3 + 0x1e) / (int)cVar11;
          if (cVar11 == '\0') {
            trap(7);
          }
          uVar4 = uVar1 & 0xffff;
          if ((uVar1 & 0xffff) == 0) {
            uVar4 = 1;
          }
          uVar12 = 8;
        }
        uStack_58 = GetRegDat__9RegDatApiFiii(0xe,*psVar10,0xffffffffffffffff);
        SetMessage__8MenuTextFPcUiUcUc(uVar9,uStack_58,*(byte *)(uVar9 + 0x58) & 7,0,1);
        OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_40 + 0x5dc,uVar9,((ulong)*(byte *)(uVar9 + 0x58) & 0xf) >> 3,0);
        *(byte *)(uVar9 + 0x12) = *(byte *)(uVar9 + 0x12) & 0xfe | 1;
        iVar3 = uVar9 + 0x80;
        uStack_48 = *(ushort *)(uVar9 + 0xa2);
        uStack_6c = *(undefined4 *)((uint)uStack_48 * 8 + *(int *)(iStack_30 + 0x24) + 0x10);
        uStack_68 = uStack_6c;
        uStack_46 = uStack_48;
        sprintf(auStack_78,uStack_6c,uVar4);
        SetMessage__8MenuTextFPcUiUcUc(iVar3,auStack_78,*(byte *)(uVar9 + 0xd8) & 7,0,1);
        OrderMessage__8FontDrawFP8MenuTextUcP11RasterData_(iStack_40 + 0x5dc,iVar3,((ulong)*(byte *)(uVar9 + 0xd8) & 0xf) >> 3,0);
        SetCSA__8FontItemFUc(iVar3,uVar12);
        *(byte *)(uVar9 + 0x92) = *(byte *)(uVar9 + 0x92) & 0xfe | 1;
        uVar9 = uVar9 + 0x100;
        lVar5 = IsSetComboKey__5CmdPCFP8CmdPartycs(uStack_4c,iVar2,2,*psVar10);
        if (lVar5 != 0) {
          *(byte *)(iVar6 + 0x12) = *(byte *)(iVar6 + 0x12) & 0xfe | 1;
        }
        iVar6 = iVar6 + 0x60;
      }
      psVar10 = psVar10 + 1;
    }
  }
  for (; uVar9 < uStack_50; uVar9 = uVar9 + 0x80) {
    *(byte *)(uVar9 + 0x12) = *(byte *)(uVar9 + 0x12) & 0xfe;
  }
  return;
}

/* JP: 0x00498150  CmdCrestMagic::~CmdCrestMagic()   [@24@__dt__13CmdCrestMagicFv]  size=0x8 */
undefined4 * _24___dt__13CmdCrestMagicFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -6;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-4] = &__vt__13CmdCrestMagic;
    *param_1 = 0x409414;
    param_1[3] = 0x409420;
    __destroy_arr(param_1 + 0x2c1,0x2661a0,0x60,4);
    __destroy_arr(param_1 + 0x1c1,0x27c030,0x80,8);
    __destroy_arr(param_1 + 0x181,0x27c030,0x80,2);
    __dt__8FontDrawFv(param_1 + 0x171,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x161,0xffffffffffffffff);
    __dt__11MenuPolygonFv(param_1 + 0x140,0xffffffffffffffff);
    __destroy_arr(param_1 + 0x50,0x2661a0,0x60,10);
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

/* JP: 0x00498160  CmdCrestMagic::~CmdCrestMagic()   [@36@__dt__13CmdCrestMagicFv]  size=0x8 */
undefined4 * _36___dt__13CmdCrestMagicFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -9;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-7] = &__vt__13CmdCrestMagic;
    param_1[-3] = 0x409414;
    *param_1 = 0x409420;
    __destroy_arr(param_1 + 0x2be,0x2661a0,0x60,4);
    __destroy_arr(param_1 + 0x1be,0x27c030,0x80,8);
    __destroy_arr(param_1 + 0x17e,0x27c030,0x80,2);
    __dt__8FontDrawFv(param_1 + 0x16e,0xffffffffffffffff);
    __dt__8FontDrawFv(param_1 + 0x15e,0xffffffffffffffff);
    __dt__11MenuPolygonFv(param_1 + 0x13d,0xffffffffffffffff);
    __destroy_arr(param_1 + 0x4d,0x2661a0,0x60,10);
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
