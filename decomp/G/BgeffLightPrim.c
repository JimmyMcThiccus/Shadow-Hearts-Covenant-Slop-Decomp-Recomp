/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: BgeffLightPrim   functions: 4
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/BgeffLightPrim.md).
 */

/* JP: 0x004ce040  BgeffLightPrim::BgeffLightPrim(void*)   [__ct__14BgeffLightPrimFPv]  size=0x11c */
int __ct__14BgeffLightPrimFPv(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  long lVar2;
  undefined8 uVar3;
  
  __ct__8PutiPrimFi(param_1,100);
  *(undefined1 **)(param_1 + 0x10) = &__vt__14BgeffLightPrim;
  *(undefined4 *)(param_1 + 0x1c) = 0x409750;
  lVar2 = __nw__FUi(0x200);
  uVar3 = 0;
  if (lVar2 != 0) {
    uVar3 = __ct__10BgeffLightFiPv(lVar2,0x2a,param_2);
  }
  AddObject__8PutiPrimFP10PutiObject(param_1,uVar3);
  lVar2 = __nw__FUi(0x10);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = __ct__11PutiTexAnimFiiP11tagPAnimSeq(lVar2,1,1,0x553e10);
  }
  *(undefined4 *)(param_1 + 0x30) = uVar1;
  *(byte *)(*(int *)(param_1 + 0x30) + 0xc) = *(byte *)(*(int *)(param_1 + 0x30) + 0xc) & 0xfe;
  SetTexture__8PutiPrimFP12tagPTexParamUc(param_1,*(undefined4 *)(eff__11BgEffectMan + 0x1c),0);
  return param_1;
}

/* JP: 0x004ce160  BgeffLightPrim::~BgeffLightPrim()   [__dt__14BgeffLightPrimFv]  size=0x84 */
int __dt__14BgeffLightPrimFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 0x10) = &__vt__14BgeffLightPrim;
    *(undefined4 *)(param_1 + 0x1c) = 0x409750;
    __dt__8PutiPrimFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x004ce1f0  BgeffLightPrim::OnDelete()   [OnDelete__14BgeffLightPrimFv]  size=0x44 */
undefined4 OnDelete__14BgeffLightPrimFv(int param_1)

{
  if (*(int *)(param_1 + 0x28) != 0) {
    DeleteLight__10BgeffLightFv(*(undefined4 *)(param_1 + 0x28));
  }
  return 1;
}

/* JP: 0x004cf0e0  BgeffLightPrim::~BgeffLightPrim()   [@20@__dt__14BgeffLightPrimFv]  size=0x8 */
int _20___dt__14BgeffLightPrimFv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x14;
  if (iVar1 != 0) {
    *(undefined1 **)(param_1 + -4) = &__vt__14BgeffLightPrim;
    *(undefined4 *)(param_1 + 8) = 0x409750;
    __dt__8PutiPrimFv(iVar1,0);
    if (0 < param_2) {
      __dl__FPv(iVar1);
    }
  }
  return iVar1;
}
