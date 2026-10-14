/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: pageScrollMark   functions: 7
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/pageScrollMark.md).
 */

/* JP: 0x00500f20  pageScrollMark::pageScrollMark()   [__ct__14pageScrollMarkFv]  size=0x44 */
int __ct__14pageScrollMarkFv(int param_1)

{
  __ct__7CPolObjFv(param_1);
  *(undefined1 **)(param_1 + 0x14) = &__vt__14pageScrollMark;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  return param_1;
}

/* JP: 0x00500f70  pageScrollMark::~pageScrollMark()   [__dt__14pageScrollMarkFv]  size=0xac */
int __dt__14pageScrollMarkFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 0x14) = &__vt__14pageScrollMark;
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

/* JP: 0x00501020  pageScrollMark::initialize(primTex*, int, int, int)   [initialize__14pageScrollMarkFP7primTexiii]  size=0xa4 */
void initialize__14pageScrollMarkFP7primTexiii
               (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
               undefined4 param_5)

{
  *(undefined1 *)(param_1 + 0x32) = 1;
  *(undefined4 *)(param_1 + 0x28) = param_4;
  *(undefined4 *)(param_1 + 0x2c) = param_5;
  *(undefined4 *)(param_1 + 0x18) = param_2;
  mSetupScrollMark__14pageScrollMarkFv(param_1);
  select__14pageScrollMarkFiii(param_1,param_3,param_4,param_5);
  *(undefined4 *)(param_1 + 0x20) = 0;
  Entry__7CPollerFP7CPolObjib(app__4CApp + 0x48,param_1,0x80,0);
  return;
}

/* JP: 0x005010d0  pageScrollMark::setDisp(bool)   [setDisp__14pageScrollMarkFb]  size=0xdc */
void setDisp__14pageScrollMarkFb(int param_1,undefined1 param_2)

{
  undefined4 uVar1;
  
  *(undefined1 *)(param_1 + 0x32) = param_2;
  if (*(char *)(param_1 + 0x32) == '\0') {
    if (*(int *)(param_1 + 0x1c) != 0) {
      uVar1 = *(undefined4 *)(param_1 + 0x1c);
      setPolyAlpha__7primWinFii(uVar1,0,0);
      setPolyAlpha__7primWinFii(uVar1,1,0);
      setPolyAlpha__7primWinFii(uVar1,2,0);
      setPolyAlpha__7primWinFii(uVar1,3,0);
    }
  }
  else {
    select__14pageScrollMarkFiii
              (param_1,*(undefined4 *)(param_1 + 0x24),*(undefined4 *)(param_1 + 0x28),
               *(undefined4 *)(param_1 + 0x2c));
  }
  return;
}

/* JP: 0x005011b0  pageScrollMark::Polling()   [Polling__14pageScrollMarkFv]  size=0x260 */
undefined8 Polling__14pageScrollMarkFv(int param_1)

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
      if (*(char *)(param_1 + 0x30) != '\0') {
        setPolyPos__7primWinFiff((float)(0x15c - (iVar2 >> 2)),0x42840000,uVar1,0);
        setPolyPos__7primWinFiff(0x43ae0000,0x429c0000,uVar1,2);
      }
      if (*(char *)(param_1 + 0x31) != '\0') {
        setPolyPos__7primWinFiff((float)((iVar2 >> 2) + 0x1ce),0x42840000,uVar1,1);
        setPolyPos__7primWinFiff(0x43e90000,0x429c0000,uVar1,3);
      }
    }
    else if (*(int *)(param_1 + 0x20) < 0x3e) {
      iVar2 = *(int *)(param_1 + 0x20);
      if (iVar2 < 0) {
        iVar2 = iVar2 + 3;
      }
      if (*(char *)(param_1 + 0x30) != '\0') {
        setPolyPos__7primWinFiff((float)(0x15c - (-(iVar2 >> 2) + 0xf)),0x42840000,uVar1,0);
        setPolyPos__7primWinFiff(0x43ae0000,0x429c0000,uVar1,2);
      }
      if (*(char *)(param_1 + 0x31) != '\0') {
        setPolyPos__7primWinFiff((float)(-(iVar2 >> 2) + 0x1dd),0x42840000,uVar1,1);
        setPolyPos__7primWinFiff(0x43e90000,0x429c0000,uVar1,3);
      }
    }
    *(int *)(param_1 + 0x20) = *(int *)(param_1 + 0x20) + 1;
    if (0x3d < *(int *)(param_1 + 0x20)) {
      *(undefined4 *)(param_1 + 0x20) = 0;
    }
  }
  return 0;
}

/* JP: 0x00501410  pageScrollMark::select(int, int, int)   [select__14pageScrollMarkFiii]  size=0x15c */
void select__14pageScrollMarkFiii(int param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  undefined4 uVar1;
  
  *(undefined4 *)(param_1 + 0x24) = param_2;
  *(undefined4 *)(param_1 + 0x28) = param_3;
  *(int *)(param_1 + 0x2c) = param_4;
  if ((*(int *)(param_1 + 0x1c) != 0) && (*(char *)(param_1 + 0x32) != '\0')) {
    uVar1 = *(undefined4 *)(param_1 + 0x1c);
    if (param_4 < 2) {
      *(undefined1 *)(param_1 + 0x30) = 0;
      setPolyAlpha__7primWinFii(uVar1,0,0);
      setPolyAlpha__7primWinFii(uVar1,2,0);
      *(undefined1 *)(param_1 + 0x31) = 0;
      setPolyAlpha__7primWinFii(uVar1,1,0);
      setPolyAlpha__7primWinFii(uVar1,3,0);
    }
    else {
      *(undefined1 *)(param_1 + 0x30) = 1;
      setPolyAlpha__7primWinFii(uVar1,0,0x80);
      setPolyAlpha__7primWinFii(uVar1,2,0x80);
      *(undefined1 *)(param_1 + 0x31) = 1;
      setPolyAlpha__7primWinFii(uVar1,1,0x80);
      setPolyAlpha__7primWinFii(uVar1,3,0x80);
    }
  }
  return;
}

/* JP: 0x00501570  pageScrollMark::mSetupScrollMark()   [mSetupScrollMark__14pageScrollMarkFv]  size=0x1b0 */
void mSetupScrollMark__14pageScrollMarkFv(int param_1)

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
    setItem__7primWinFiii(uVar1,2,4,0);
    setMenuTex__7primWinFP11MenuTextureiii(uVar1,0x421718,0,0x14,0x16);
    setMenuTex__7primWinFP11MenuTextureiii(uVar1,0x4219d8,1,0x10,0x14);
    createTexPoly__7primWinFiiiiii(uVar1,0,0,0,0,0,2);
    createTexPoly__7primWinFiiiiii(uVar1,1,0,0,0,0,3);
    createTexPoly__7primWinFiiiiii(uVar1,2,1,0,0,0,0);
    createTexPoly__7primWinFiiiiii(uVar1,3,1,0,0,0,1);
    buildWin__7primWinFiiiiii(uVar1,3,0,0,0,0,0);
    setDisp__14pageScrollMarkFb(param_1,*(undefined1 *)(param_1 + 0x32));
  }
  return;
}
