/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: shopScrollMark   functions: 6
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/shopScrollMark.md).
 */

/* JP: 0x004e89a0  shopScrollMark::shopScrollMark()   [__ct__14shopScrollMarkFv]  size=0x44 */
int __ct__14shopScrollMarkFv(int param_1)

{
  __ct__7CPolObjFv(param_1);
  *(undefined1 **)(param_1 + 0x14) = &__vt__14shopScrollMark;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  return param_1;
}

/* JP: 0x004e89f0  shopScrollMark::~shopScrollMark()   [__dt__14shopScrollMarkFv]  size=0xac */
int __dt__14shopScrollMarkFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 0x14) = &__vt__14shopScrollMark;
    Dispose__7CPollerFP7CPolObj(app__4CApp + 0x48,param_1);
    if (*(int *)(param_1 + 0x1c) != 0) {
      DelayDeleteRequest__7primWinFv(*(undefined4 *)(param_1 + 0x1c));
      *(undefined4 *)(param_1 + 0x1c) = 0;
    }
    __dt__7CPolObjFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x004e8aa0  shopScrollMark::initialize(primTex*, int, int, int)   [initialize__14shopScrollMarkFP7primTexiii]  size=0x80 */
void initialize__14shopScrollMarkFP7primTexiii
               (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
               undefined4 param_5)

{
  *(undefined4 *)(param_1 + 0x18) = param_2;
  mSetupScrollMark__14shopScrollMarkFv(param_1);
  select__14shopScrollMarkFiii(param_1,param_3,param_4,param_5);
  *(undefined4 *)(param_1 + 0x20) = 0;
  Entry__7CPollerFP7CPolObjib(app__4CApp + 0x48,param_1,0x80,0);
  return;
}

/* JP: 0x004e8b20  shopScrollMark::Polling()   [Polling__14shopScrollMarkFv]  size=0x260 */
undefined8 Polling__14shopScrollMarkFv(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  if (*(int *)(param_1 + 0x1c) != 0) {
    uVar1 = *(undefined4 *)(param_1 + 0x1c);
    if (*(int *)(param_1 + 0x20) < 0x1f) {
      iVar2 = *(int *)(param_1 + 0x20);
      if (iVar2 < 0) {
        iVar2 = iVar2 + 3;
      }
      if (*(char *)(param_1 + 0x28) != '\0') {
        setPolyPos__7primWinFiff((float)(0x112 - (iVar2 >> 2)),
                        (float)(*(int *)(param_1 + 0x24) * 0x15 + 0x47),uVar1,0);
      }
      if (*(char *)(param_1 + 0x29) != '\0') {
        setPolyPos__7primWinFiff((float)((iVar2 >> 2) + 0x134),
                        (float)(*(int *)(param_1 + 0x24) * 0x15 + 0x47),uVar1,1);
      }
    }
    else if (*(int *)(param_1 + 0x20) < 0x3e) {
      iVar2 = *(int *)(param_1 + 0x20);
      if (iVar2 < 0) {
        iVar2 = iVar2 + 3;
      }
      if (*(char *)(param_1 + 0x28) != '\0') {
        setPolyPos__7primWinFiff((float)(0x112 - (-(iVar2 >> 2) + 0xf)),
                        (float)(*(int *)(param_1 + 0x24) * 0x15 + 0x47),uVar1,0);
      }
      if (*(char *)(param_1 + 0x29) != '\0') {
        setPolyPos__7primWinFiff((float)(-(iVar2 >> 2) + 0x143),
                        (float)(*(int *)(param_1 + 0x24) * 0x15 + 0x47),uVar1,1);
      }
    }
    *(int *)(param_1 + 0x20) = *(int *)(param_1 + 0x20) + 1;
    if (0x3d < *(int *)(param_1 + 0x20)) {
      *(undefined4 *)(param_1 + 0x20) = 0;
    }
  }
  return 0;
}

/* JP: 0x004e8d80  shopScrollMark::select(int, int, int)   [select__14shopScrollMarkFiii]  size=0x104 */
void select__14shopScrollMarkFiii(int param_1,undefined4 param_2,int param_3,int param_4)

{
  undefined4 uVar1;
  
  *(undefined4 *)(param_1 + 0x24) = param_2;
  if (*(int *)(param_1 + 0x1c) != 0) {
    uVar1 = *(undefined4 *)(param_1 + 0x1c);
    if (param_3 == 0) {
      *(undefined1 *)(param_1 + 0x28) = 0;
      setPolyAlpha__7primWinFii(uVar1,0,0);
    }
    else {
      *(undefined1 *)(param_1 + 0x28) = 1;
      setPolyAlpha__7primWinFii(uVar1,0,0x80);
    }
    if (param_3 < param_4 + -1) {
      *(undefined1 *)(param_1 + 0x29) = 1;
      setPolyAlpha__7primWinFii(uVar1,1,0x80);
    }
    else {
      *(undefined1 *)(param_1 + 0x29) = 0;
      setPolyAlpha__7primWinFii(uVar1,1,0);
    }
  }
  return;
}

/* JP: 0x004e8e90  shopScrollMark::mSetupScrollMark()   [mSetupScrollMark__14shopScrollMarkFv]  size=0x130 */
void mSetupScrollMark__14shopScrollMarkFv(int param_1)

{
  undefined4 uVar1;
  long lVar2;
  
  if (*(int *)(param_1 + 0x1c) == 0) {
    lVar2 = __nw__FUi(0x148);
    uVar1 = 0;
    if (lVar2 != 0) {
      uVar1 = __ct__7primWinFv(lVar2);
    }
    *(undefined4 *)(param_1 + 0x1c) = uVar1;
    uVar1 = *(undefined4 *)(param_1 + 0x1c);
    initialize__7primWinFP7primTex(uVar1,*(undefined4 *)(param_1 + 0x18));
    setItem__7primWinFiii(uVar1,1,2,0);
    setMenuTex__7primWinFP11MenuTextureiii(uVar1,0x421758,0,0x10,0x14);
    createTexPoly__7primWinFiiiiii(uVar1,0,0,0,0,0,0);
    createTexPoly__7primWinFiiiiii(uVar1,1,0,0,0,0,1);
    buildWin__7primWinFiiiiii(uVar1,3,0,0,0,0,0);
  }
  return;
}
