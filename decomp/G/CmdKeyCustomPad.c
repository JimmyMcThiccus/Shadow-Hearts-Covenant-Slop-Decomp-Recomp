/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdKeyCustomPad   functions: 6
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdKeyCustomPad.md).
 */

/* JP: 0x00479e50  CmdKeyCustomPad::CmdKeyCustomPad()   [__ct__15CmdKeyCustomPadFv]  size=0x10c */
int __ct__15CmdKeyCustomPadFv(int param_1)

{
  __ct__9CmdWindowFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__15CmdKeyCustomPad;
  *(undefined4 *)(param_1 + 0x18) = 0x408c34;
  *(undefined4 *)(param_1 + 0x24) = 0x408c40;
  __ct__11SendOnLocalFv(param_1 + 0xb4);
  __ct__11SendOnLocalFv(param_1 + 0xe4);
  __ct__11SendOnLocalFv(param_1 + 0x114);
  __ct__11SendOnLocalFv(param_1 + 0x144);
  __ct__8FontDrawFv(param_1 + 0x174);
  __construct_array(param_1 + 0x1b4,0x47a010,0x479f60,0x230,4);
  __ct__10MenuSpriteFv(param_1 + 0xa74);
  __construct_array(param_1 + 0xad4,0x276640,0x2766d0,0x84,8);
  return param_1;
}

/* JP: 0x0047a090  CmdKeyCustomPad::~CmdKeyCustomPad()   [__dt__15CmdKeyCustomPadFv]  size=0x14c */
int __dt__15CmdKeyCustomPadFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__15CmdKeyCustomPad;
    *(undefined4 *)(param_1 + 0x18) = 0x408c34;
    *(undefined4 *)(param_1 + 0x24) = 0x408c40;
    __destroy_arr(param_1 + 0xad4,0x2766d0,0x84,8);
    __dt__10MenuSpriteFv(param_1 + 0xa74,0xffffffffffffffff);
    __destroy_arr(param_1 + 0x1b4,0x479f60,0x230,4);
    __dt__8FontDrawFv(param_1 + 0x174,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x144,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x114,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0xe4,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0xb4,0xffffffffffffffff);
    __dt__9CmdWindowFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x0047a1e0  CmdKeyCustomPad::CreateScene(CmdKeyCustom*)   [CreateScene__15CmdKeyCustomPadFP12CmdKeyCustom]  size=0x40c */
void CreateScene__15CmdKeyCustomPadFP12CmdKeyCustom(int param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  
  SetData__9MenuSceneFUsP8FontDraw(param_2,1,param_1 + 0x174);
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0x174);
  iVar2 = param_1 + 0x1b4;
  for (uVar1 = 0; (int)uVar1 < 4; uVar1 = uVar1 + 1) {
    iVar4 = iVar2 + 0x50;
    uVar3 = 1;
    while( true ) {
      if (5 < (int)uVar3) break;
      SetData__9MenuSceneFUsP10MenuSprite(param_2,uVar3 & 0xffff,iVar4);
      AddPlace__9MenuGroupFP9MenuPlace(iVar2,iVar4);
      uVar3 = uVar3 + 1;
      iVar4 = iVar4 + 0x60;
    }
    SetData__9MenuSceneFUsP9MenuGroup(param_2,uVar1 & 0xffff,iVar2);
    AddPlace__10MenuWindowFP9MenuPlace(param_1,iVar2);
    SetIcon__10MenuCommonFcP10MenuSprite((char)*(undefined2 *)(iVar2 + 0x22),iVar2 + 0xb0);
    iVar2 = iVar2 + 0x230;
  }
  iVar2 = param_1 + 0xad4;
  for (uVar1 = 0; (int)uVar1 < 8; uVar1 = uVar1 + 1) {
    SetData__9MenuSceneFUsP11MenuPolygon(param_2,uVar1 & 0xffff,iVar2);
    AddPlace__10MenuWindowFP9MenuPlace(param_1,iVar2);
    iVar2 = iVar2 + 0x84;
  }
  SetData__9MenuSceneFUsP10MenuSprite(param_2,0,param_1 + 0xa74);
  AddPlace__10MenuWindowFP9MenuPlace(param_1,param_1 + 0xa74);
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(param_1 + 0xb4,param_2 + 0x1c0,*(undefined4 *)(param_2 + 0x1bc),1,
                  0xffffffffffffffff);
  *(short *)(param_1 + 200) = *(short *)(param_1 + 0xa88) + -1;
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0xb4);
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(param_1 + 0xe4,0x421670,uRam0042166c,1,0xffffffffffffffff);
  *(short *)(param_1 + 0xf8) = *(short *)(param_1 + 0x278) + -1;
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0xe4);
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(param_1 + 0x144,param_2 + 0x180,*(undefined4 *)(param_2 + 0x17c),1,
                  0xffffffffffffffff);
  *(short *)(param_1 + 0x158) = *(short *)(param_1 + 0x218) + -1;
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0x144);
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(param_1 + 0x114,param_2 + 0x200,*(undefined4 *)(param_2 + 0x1fc),1,
                  0xffffffffffffffff);
  *(short *)(param_1 + 0x128) = *(short *)(param_1 + 0x2d8) + -1;
  AddPriority__12MenuObjTableFP7MenuObj(param_1 + 0x18,param_1 + 0x114);
  SetData__9MenuSceneFUsP10MenuWindow(param_2,1,param_1);
  AddOT__7MenuObjFv(param_1);
  return;
}

/* JP: 0x0047a5f0  CmdKeyCustomPad::SetLineColor(int, int)   [SetLineColor__15CmdKeyCustomPadFii]  size=0x104 */
void SetLineColor__15CmdKeyCustomPadFii(int param_1,int param_2,int param_3)

{
  int iVar1;
  undefined8 uStack_40;
  undefined2 auStack_34 [2];
  int iStack_30;
  int iStack_20;
  int iStack_10;
  
  iStack_30 = param_1;
  iStack_20 = param_2;
  iStack_10 = param_3;
  param_1 = param_1 + param_2 * 0x108;
  uStack_40 = @3375;
  auStack_34[0] = @3377;
  (**(code **)(*(int *)(param_1 + 0xadc) + 0x34))(*(undefined4 *)((int)&uStack_40 + param_3 * 4));
  (**(code **)(*(int *)(param_1 + 0xb60) + 0x34))(*(undefined4 *)((int)&uStack_40 + iStack_10 * 4));
  iVar1 = iStack_30 + iStack_20 * 0x230;
  (**(code **)(*(int *)(iVar1 + 0x20c) + 0x30))
            (iVar1 + 0x204,*(undefined1 *)((int)auStack_34 + iStack_10),
             *(undefined1 *)((int)auStack_34 + iStack_10),
             *(undefined1 *)((int)auStack_34 + iStack_10));
  return;
}

/* JP: 0x0047a700  CmdKeyCustomPad::~CmdKeyCustomPad()   [@24@__dt__15CmdKeyCustomPadFv]  size=0x8 */
undefined4 * _24___dt__15CmdKeyCustomPadFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -6;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-4] = &__vt__15CmdKeyCustomPad;
    *param_1 = 0x408c34;
    param_1[3] = 0x408c40;
    __destroy_arr(param_1 + 0x2af,0x2766d0,0x84,8);
    __dt__10MenuSpriteFv(param_1 + 0x297,0xffffffffffffffff);
    __destroy_arr(param_1 + 0x67,0x479f60,0x230,4);
    __dt__8FontDrawFv(param_1 + 0x57,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x4b,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x3f,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x33,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x27,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}

/* JP: 0x0047a710  CmdKeyCustomPad::~CmdKeyCustomPad()   [@36@__dt__15CmdKeyCustomPadFv]  size=0x8 */
undefined4 * _36___dt__15CmdKeyCustomPadFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -9;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-7] = &__vt__15CmdKeyCustomPad;
    param_1[-3] = 0x408c34;
    *param_1 = 0x408c40;
    __destroy_arr(param_1 + 0x2ac,0x2766d0,0x84,8);
    __dt__10MenuSpriteFv(param_1 + 0x294,0xffffffffffffffff);
    __destroy_arr(param_1 + 100,0x479f60,0x230,4);
    __dt__8FontDrawFv(param_1 + 0x54,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x48,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x3c,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x30,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x24,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}
