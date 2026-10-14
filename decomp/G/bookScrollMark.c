/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: bookScrollMark   functions: 7
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/bookScrollMark.md).
 */

/* JP: 0x004f1240  bookScrollMark::bookScrollMark()   [__ct__14bookScrollMarkFv]  size=0x44 */
int __ct__14bookScrollMarkFv(int param_1)

{
  __ct__7CPolObjFv(param_1);
  *(undefined1 **)(param_1 + 0x14) = &__vt__14bookScrollMark;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  return param_1;
}

/* JP: 0x004f1290  bookScrollMark::~bookScrollMark()   [__dt__14bookScrollMarkFv]  size=0xac */
int __dt__14bookScrollMarkFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 0x14) = &__vt__14bookScrollMark;
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

/* JP: 0x004f1340  bookScrollMark::initialize(primTex*, int, int)   [initialize__14bookScrollMarkFP7primTexii]  size=0x8c */
void initialize__14bookScrollMarkFP7primTexii
               (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  *(undefined1 *)(param_1 + 0x2e) = 1;
  *(undefined4 *)(param_1 + 0x28) = param_4;
  *(undefined4 *)(param_1 + 0x18) = param_2;
  mSetupScrollMark__14bookScrollMarkFv(param_1);
  select__14bookScrollMarkFi(param_1,param_3);
  *(undefined4 *)(param_1 + 0x20) = 0;
  Entry__7CPollerFP7CPolObjib(app__4CApp + 0x48,param_1,0x80,0);
  return;
}

/* JP: 0x004f13d0  bookScrollMark::setDisp(bool)   [setDisp__14bookScrollMarkFb]  size=0xa4 */
void setDisp__14bookScrollMarkFb(int param_1,undefined1 param_2)

{
  undefined4 uVar1;
  
  *(undefined1 *)(param_1 + 0x2e) = param_2;
  if (*(char *)(param_1 + 0x2e) == '\0') {
    if (*(int *)(param_1 + 0x1c) != 0) {
      uVar1 = *(undefined4 *)(param_1 + 0x1c);
      setPolyAlpha__7primWinFii(uVar1,0,0);
      setPolyAlpha__7primWinFii(uVar1,1,0);
    }
  }
  else {
    select__14bookScrollMarkFi(param_1,*(undefined4 *)(param_1 + 0x24));
  }
  return;
}

/* JP: 0x004f1480  bookScrollMark::Polling()   [Polling__14bookScrollMarkFv]  size=0x1e0 */
undefined8 Polling__14bookScrollMarkFv(int param_1)

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
      if (*(char *)(param_1 + 0x2c) != '\0') {
        setPolyPos__7primWinFiff((float)(0x132 - (iVar2 >> 2)),0x43700000,uVar1,0);
      }
      if (*(char *)(param_1 + 0x2d) != '\0') {
        setPolyPos__7primWinFiff((float)((iVar2 >> 2) + 0x1e6),0x43700000,uVar1,1);
      }
    }
    else if (*(int *)(param_1 + 0x20) < 0x3e) {
      iVar2 = *(int *)(param_1 + 0x20);
      if (iVar2 < 0) {
        iVar2 = iVar2 + 3;
      }
      if (*(char *)(param_1 + 0x2c) != '\0') {
        setPolyPos__7primWinFiff((float)(0x132 - (-(iVar2 >> 2) + 0xf)),0x43700000,uVar1,0);
      }
      if (*(char *)(param_1 + 0x2d) != '\0') {
        setPolyPos__7primWinFiff((float)(-(iVar2 >> 2) + 0x1f5),0x43700000,uVar1,1);
      }
    }
    *(int *)(param_1 + 0x20) = *(int *)(param_1 + 0x20) + 1;
    if (0x3d < *(int *)(param_1 + 0x20)) {
      *(undefined4 *)(param_1 + 0x20) = 0;
    }
  }
  return 0;
}

/* JP: 0x004f1660  bookScrollMark::select(int)   [select__14bookScrollMarkFi]  size=0x10c */
void select__14bookScrollMarkFi(int param_1,int param_2)

{
  undefined4 uVar1;
  
  *(int *)(param_1 + 0x24) = param_2;
  if ((*(int *)(param_1 + 0x1c) != 0) && (*(char *)(param_1 + 0x2e) != '\0')) {
    uVar1 = *(undefined4 *)(param_1 + 0x1c);
    if (param_2 == 0) {
      *(undefined1 *)(param_1 + 0x2c) = 0;
      setPolyAlpha__7primWinFii(uVar1,0,0);
    }
    else {
      *(undefined1 *)(param_1 + 0x2c) = 1;
      setPolyAlpha__7primWinFii(uVar1,0,0x80);
    }
    if (param_2 < *(int *)(param_1 + 0x28) + -1) {
      *(undefined1 *)(param_1 + 0x2d) = 1;
      setPolyAlpha__7primWinFii(uVar1,1,0x80);
    }
    else {
      *(undefined1 *)(param_1 + 0x2d) = 0;
      setPolyAlpha__7primWinFii(uVar1,1,0);
    }
  }
  return;
}

/* JP: 0x004f1770  bookScrollMark::mSetupScrollMark()   [mSetupScrollMark__14bookScrollMarkFv]  size=0x148 */
void mSetupScrollMark__14bookScrollMarkFv(int param_1)

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
    setMenuTex__7primWinFP11MenuTextureiii(uVar1,0x421718,0,0x14,0x16);
    createTexPoly__7primWinFiiiiii(uVar1,0,0,0,0,0,2);
    createTexPoly__7primWinFiiiiii(uVar1,1,0,0,0,0,3);
    buildWin__7primWinFiiiiii(uVar1,3,0,0,0,0,0);
    setDisp__14bookScrollMarkFb(param_1,*(undefined1 *)(param_1 + 0x2e));
  }
  return;
}
