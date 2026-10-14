/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdFusionCharge   functions: 6
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdFusionCharge.md).
 */

/* JP: 0x0047d2d0  CmdFusionCharge::CmdFusionCharge()   [__ct__15CmdFusionChargeFv]  size=0x10c */
int __ct__15CmdFusionChargeFv(int param_1)

{
  __ct__9CmdWindowFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__15CmdFusionCharge;
  *(undefined4 *)(param_1 + 0x18) = 0x408e14;
  *(undefined4 *)(param_1 + 0x24) = 0x408e20;
  __ct__11MenuTextureFv(param_1 + 0xb8);
  *(undefined4 *)(param_1 + 0xf8) = 0;
  __ct__11SendOnLocalFv(param_1 + 0xfc);
  __ct__11SendOnLocalFv(param_1 + 300);
  __ct__11SendOnLocalFv(param_1 + 0x15c);
  __ct__11SendOnLocalFv(param_1 + 0x18c);
  __ct__10MenuSpriteFv(param_1 + 0x1bc);
  __ct__10MenuSpriteFv(param_1 + 0x21c);
  __construct_array(param_1 + 0x27c,0x266140,0x2661a0,0x60,2);
  __ct__7MenuBarFv(param_1 + 0x33c);
  return param_1;
}

/* JP: 0x0047d3e0  CmdFusionCharge::~CmdFusionCharge()   [__dt__15CmdFusionChargeFv]  size=0x190 */
int __dt__15CmdFusionChargeFv(int param_1,short param_2)

{
  int iVar1;
  
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__15CmdFusionCharge;
    *(undefined4 *)(param_1 + 0x18) = 0x408e14;
    *(undefined4 *)(param_1 + 0x24) = 0x408e20;
    if (*(int *)(param_1 + 0xf8) != 0) {
      iVar1 = *(int *)(param_1 + 0xf8);
      if (iVar1 != 0) {
        (**(code **)(*(int *)(iVar1 + 8) + 8))(iVar1,1);
      }
    }
    __dt__7MenuBarFv(param_1 + 0x33c,0xffffffffffffffff);
    __destroy_arr(param_1 + 0x27c,0x2661a0,0x60,2);
    __dt__10MenuSpriteFv(param_1 + 0x21c,0xffffffffffffffff);
    __dt__10MenuSpriteFv(param_1 + 0x1bc,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x18c,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x15c,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 300,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0xfc,0xffffffffffffffff);
    __dt__11MenuTextureFv(param_1 + 0xb8,0xffffffffffffffff);
    __dt__9CmdWindowFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x0047d570  CmdFusionCharge::CreateScene(CmdFusion*)   [CreateScene__15CmdFusionChargeFP9CmdFusion]  size=0x2e8 */
void CreateScene__15CmdFusionChargeFP9CmdFusion(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  
  iVar1 = *(int *)(*(int *)(param_2 + 0x58) + 0x6c);
  Create__11MenuTextureFPUc6GS_PSMUii(param_1 + 0xb8,*(undefined4 *)(*(int *)(param_2 + 0x54) + 0x1c),0x30,0,0);
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(param_1 + 0xfc,param_1 + 0xd0,*(undefined4 *)(param_1 + 0xcc),1,0xffffffffffffffff
                 );
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(param_1 + 0x15c,iVar1 + 0x128,*(undefined4 *)(iVar1 + 0x124),1,0xffffffffffffffff)
  ;
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(param_1 + 300,iVar1 + 0x168,*(undefined4 *)(iVar1 + 0x164),1,0);
  iVar1 = param_1 + 0x1bc;
  iVar3 = param_1 + 0xfc;
  uVar2 = 1;
  while( true ) {
    if (4 < (int)uVar2) break;
    SetData__9MenuSceneFUsP10MenuSprite(param_2,uVar2 & 0xffff,iVar1);
    AddPlace__10MenuWindowFP9MenuPlace(param_1,iVar1);
    if ((int)uVar2 < 4) {
      *(short *)(iVar3 + 0x14) = *(short *)(iVar1 + 0x14) + -1;
      AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,iVar3);
    }
    uVar2 = uVar2 + 1;
    iVar1 = iVar1 + 0x60;
    iVar3 = iVar3 + 0x30;
  }
  SetData__9MenuSceneFUsP10MenuSprite(param_2,5,param_1 + 0x33c);
  SetBar__7MenuBarFv(param_1 + 0x33c);
  AddPlace__10MenuWindowFP9MenuPlace(param_1,param_1 + 0x33c);
  *(short *)(param_1 + 0x1a0) = *(short *)(param_1 + 0x350) + -1;
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0x18c);
  SetBlink__8MenuItemFUcUc(param_1 + 0x21c,0x20,0);
  SetBlink__8MenuItemFUcUc(param_1 + 0x2dc,0x20,0);
  SetData__9MenuSceneFUsP10MenuWindow(param_2,2,param_1);
  AddOT__7MenuObjFv(param_1);
  return;
}

/* JP: 0x0047d860  CmdFusionCharge::UpdateScene(CmdFusion*)   [UpdateScene__15CmdFusionChargeFP9CmdFusion]  size=0x254 */
void UpdateScene__15CmdFusionChargeFP9CmdFusion(int param_1,int param_2)

{
  undefined1 uVar1;
  short sVar2;
  undefined4 uVar3;
  int iVar4;
  byte bVar5;
  undefined4 *puVar6;
  int iVar7;
  int iVar8;
  long lVar9;
  undefined8 uVar10;
  
  uVar3 = *(undefined4 *)(*(int *)(param_2 + 0x58) + 0x6c);
  iVar4 = *(int *)(*(int *)(param_2 + 0x58) + 0x5c);
  bVar5 = *(byte *)(*(int *)(param_2 + 0xb8) + 4) & 7;
  sVar2 = *(short *)(param_2 + 0xbc);
  uVar1 = *(undefined1 *)(*(int *)(iVar4 + 4) + (int)sVar2 + 0xd94);
  if (*(int *)(param_1 + 0xf8) != 0) {
    (**(code **)(*(int *)(*(int *)(param_1 + 0xf8) + 8) + 0xc))();
  }
  lVar9 = __nw__FUi(0x40);
  uVar10 = 0;
  if (lVar9 != 0) {
    uVar10 = __ct__11MenuTextureFv(lVar9);
  }
  iVar7 = (int)uVar10;
  *(int *)(param_1 + 0xf8) = iVar7;
  puVar6 = (undefined4 *)FindAttachFile__9MenuSceneCFs(param_2,bVar5);
  Create__11MenuTextureFPUc6GS_PSMUii(uVar10,*puVar6,0x30,0,0);
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(param_1 + 0x18c,iVar7 + 0x18,*(undefined4 *)(iVar7 + 0x14),1,0xffffffffffffffff);
  iVar4 = *(int *)(*(int *)(iVar4 + 4) + sVar2 * 4 + 0xd50);
  iVar7 = GetNextExp__9CmdFusionFs(param_2,0);
  iVar8 = GetRegDat__9RegDatApiFiii(0x2d,sVar2,uVar1);
  SetRange__7MenuBarFii(param_1 + 0x33c,iVar4 - iVar7,*(undefined2 *)(iVar8 + 0xe));
  SetInfo__10CmdElementFUcP11SendOnLocalP10MenuSpriteP10MenuSprite
            (uVar3,bVar5,param_1 + 300,param_1 + 0x21c,param_1 + 0x2dc);
  return;
}

/* JP: 0x0047dac0  CmdFusionCharge::~CmdFusionCharge()   [@24@__dt__15CmdFusionChargeFv]  size=0x8 */
undefined4 * _24___dt__15CmdFusionChargeFv(undefined4 *param_1,short param_2)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = param_1 + -6;
  if (puVar2 != (undefined4 *)0x0) {
    param_1[-4] = &__vt__15CmdFusionCharge;
    *param_1 = 0x408e14;
    param_1[3] = 0x408e20;
    if (param_1[0x38] != 0) {
      iVar1 = param_1[0x38];
      if (iVar1 != 0) {
        (**(code **)(*(int *)(iVar1 + 8) + 8))(iVar1,1);
      }
    }
    __dt__7MenuBarFv(param_1 + 0xc9,0xffffffffffffffff);
    __destroy_arr(param_1 + 0x99,0x2661a0,0x60,2);
    __dt__10MenuSpriteFv(param_1 + 0x81,0xffffffffffffffff);
    __dt__10MenuSpriteFv(param_1 + 0x69,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x5d,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x51,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x45,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x39,0xffffffffffffffff);
    __dt__11MenuTextureFv(param_1 + 0x28,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar2,0);
    if (0 < param_2) {
      __dl__FPv(puVar2);
    }
  }
  return puVar2;
}

/* JP: 0x0047dad0  CmdFusionCharge::~CmdFusionCharge()   [@36@__dt__15CmdFusionChargeFv]  size=0x8 */
undefined4 * _36___dt__15CmdFusionChargeFv(undefined4 *param_1,short param_2)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = param_1 + -9;
  if (puVar2 != (undefined4 *)0x0) {
    param_1[-7] = &__vt__15CmdFusionCharge;
    param_1[-3] = 0x408e14;
    *param_1 = 0x408e20;
    if (param_1[0x35] != 0) {
      iVar1 = param_1[0x35];
      if (iVar1 != 0) {
        (**(code **)(*(int *)(iVar1 + 8) + 8))(iVar1,1);
      }
    }
    __dt__7MenuBarFv(param_1 + 0xc6,0xffffffffffffffff);
    __destroy_arr(param_1 + 0x96,0x2661a0,0x60,2);
    __dt__10MenuSpriteFv(param_1 + 0x7e,0xffffffffffffffff);
    __dt__10MenuSpriteFv(param_1 + 0x66,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x5a,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x4e,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x42,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x36,0xffffffffffffffff);
    __dt__11MenuTextureFv(param_1 + 0x25,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar2,0);
    if (0 < param_2) {
      __dl__FPv(puVar2);
    }
  }
  return puVar2;
}
