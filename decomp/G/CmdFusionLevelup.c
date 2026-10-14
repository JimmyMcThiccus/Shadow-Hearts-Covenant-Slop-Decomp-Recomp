/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdFusionLevelup   functions: 5
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdFusionLevelup.md).
 */

/* JP: 0x0047dae0  CmdFusionLevelup::CmdFusionLevelup()   [__ct__16CmdFusionLevelupFv]  size=0x8c */
int __ct__16CmdFusionLevelupFv(int param_1)

{
  __ct__9CmdWindowFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__16CmdFusionLevelup;
  *(undefined4 *)(param_1 + 0x18) = 0x408e54;
  *(undefined4 *)(param_1 + 0x24) = 0x408e60;
  __ct__11MenuTextureFv(param_1 + 0xb8);
  __ct__11SendOnLocalFv(param_1 + 0xf8);
  __ct__10MenuSpriteFv(param_1 + 0x128);
  return param_1;
}

/* JP: 0x0047db70  CmdFusionLevelup::~CmdFusionLevelup()   [__dt__16CmdFusionLevelupFv]  size=0xcc */
int __dt__16CmdFusionLevelupFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__16CmdFusionLevelup;
    *(undefined4 *)(param_1 + 0x18) = 0x408e54;
    *(undefined4 *)(param_1 + 0x24) = 0x408e60;
    __dt__10MenuSpriteFv(param_1 + 0x128,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0xf8,0xffffffffffffffff);
    __dt__11MenuTextureFv(param_1 + 0xb8,0xffffffffffffffff);
    __dt__9CmdWindowFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x0047dc40  CmdFusionLevelup::CreateScene(CmdFusion*)   [CreateScene__16CmdFusionLevelupFP9CmdFusion]  size=0x110 */
void CreateScene__16CmdFusionLevelupFP9CmdFusion(int param_1,int param_2)

{
  Create__11MenuTextureFPUc6GS_PSMUii(param_1 + 0xb8,*(undefined4 *)(*(int *)(param_2 + 0x54) + 0x28),0x30,0,0);
  Create__11SendOnLocalFP12RasterPacketP10ClutRasterbi(param_1 + 0xf8,param_1 + 0xd0,*(undefined4 *)(param_1 + 0xcc),1,0xffffffffffffffff
                 );
  SetData__9MenuSceneFUsP10MenuSprite(param_2,0,param_1 + 0x128);
  *(int *)(param_1 + 0x184) = param_1 + 0xf8;
  *(byte *)(param_1 + 0x13a) = *(byte *)(param_1 + 0x13a) & 0xdf;
  AddPlace__10MenuWindowFP9MenuPlace(param_1,param_1 + 0x128);
  SetData__9MenuSceneFUsP10MenuWindow(param_2,3,param_1);
  AddOT__7MenuObjFv(param_1);
  return;
}

/* JP: 0x0047dd50  CmdFusionLevelup::~CmdFusionLevelup()   [@24@__dt__16CmdFusionLevelupFv]  size=0x8 */
undefined4 * _24___dt__16CmdFusionLevelupFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -6;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-4] = &__vt__16CmdFusionLevelup;
    *param_1 = 0x408e54;
    param_1[3] = 0x408e60;
    __dt__10MenuSpriteFv(param_1 + 0x44,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x38,0xffffffffffffffff);
    __dt__11MenuTextureFv(param_1 + 0x28,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}

/* JP: 0x0047dd60  CmdFusionLevelup::~CmdFusionLevelup()   [@36@__dt__16CmdFusionLevelupFv]  size=0x8 */
undefined4 * _36___dt__16CmdFusionLevelupFv(undefined4 *param_1,short param_2)

{
  undefined4 *puVar1;
  
  puVar1 = param_1 + -9;
  if (puVar1 != (undefined4 *)0x0) {
    param_1[-7] = &__vt__16CmdFusionLevelup;
    param_1[-3] = 0x408e54;
    *param_1 = 0x408e60;
    __dt__10MenuSpriteFv(param_1 + 0x41,0xffffffffffffffff);
    __dt__11SendOnLocalFv(param_1 + 0x35,0xffffffffffffffff);
    __dt__11MenuTextureFv(param_1 + 0x25,0xffffffffffffffff);
    __dt__9CmdWindowFv(puVar1,0);
    if (0 < param_2) {
      __dl__FPv(puVar1);
    }
  }
  return puVar1;
}
