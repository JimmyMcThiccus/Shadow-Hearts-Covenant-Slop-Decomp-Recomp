/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: shopCash   functions: 8
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/shopCash.md).
 */

/* JP: 0x004e8490  shopCash::shopCash()   [__ct__8shopCashFv]  size=0x20 */
undefined4 * __ct__8shopCashFv(undefined4 *param_1)

{
  *param_1 = 0;
  return param_1;
}

/* JP: 0x004e84b0  shopCash::~shopCash()   [__dt__8shopCashFv]  size=0x7c */
int * __dt__8shopCashFv(int *param_1,short param_2)

{
  if (param_1 != (int *)0x0) {
    if (*param_1 != 0) {
      DelayDeleteRequest__7primWinFv(*param_1);
      *param_1 = 0;
    }
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x004e8530  shopCash::initialize(primTex*)   [initialize__8shopCashFP7primTex]  size=0x40 */
void initialize__8shopCashFP7primTex(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 4) = param_2;
  *(undefined4 *)(param_1 + 8) = 0;
  mSetupCash__8shopCashFv(param_1);
  return;
}

/* JP: 0x004e8570  shopCash::setCash(int)   [setCash__8shopCashFi]  size=0x38 */
void setCash__8shopCashFi(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 8) = param_2;
  mCalcCash__8shopCashFv(param_1);
  return;
}

/* JP: 0x004e85b0  shopCash::fadein()   [fadein__8shopCashFv]  size=0x30 */
void fadein__8shopCashFv(undefined4 *param_1)

{
  fadein__7primWinFi(*param_1,0x10);
  return;
}

/* JP: 0x004e85e0  shopCash::fadeout()   [fadeout__8shopCashFv]  size=0x30 */
void fadeout__8shopCashFv(undefined4 *param_1)

{
  fadeout__7primWinFi(*param_1,0x10);
  return;
}

/* JP: 0x004e8610  shopCash::mSetupCash()   [mSetupCash__8shopCashFv]  size=0x190 */
void mSetupCash__8shopCashFv(int *param_1)

{
  int iVar1;
  long lVar2;
  int iVar3;
  
  if (*param_1 == 0) {
    lVar2 = __nw__FUi(0x148);
    iVar1 = 0;
    if (lVar2 != 0) {
      iVar1 = __ct__7primWinFv(lVar2);
    }
    *param_1 = iVar1;
    iVar1 = *param_1;
    initialize__7primWinFP7primTex(iVar1,param_1[1]);
    setItem__7primWinFiii(iVar1,2,0xb,0);
    setTex__7primWinFiiii(iVar1,4,0,0x10,0x14);
    setTex__7primWinFiiii(iVar1,5,1,0x30,0x18);
    for (iVar3 = 0; iVar3 < 10; iVar3 = iVar3 + 1) {
      createTexPoly__7primWinFiiiiii(iVar1,iVar3,0,iVar3 * 10 + 0x30,0,0,0);
    }
    createTexPoly__7primWinFiiiiii(iVar1,10,1,0,0,0,0);
    buildWin__7primWinFiiiiii(iVar1,8,0x14a,0x188,0,0,0);
    mCalcCash__8shopCashFv(param_1);
  }
  return;
}

/* JP: 0x004e87a0  shopCash::mCalcCash()   [mCalcCash__8shopCashFv]  size=0x1fc */
void mCalcCash__8shopCashFv(undefined4 *param_1)

{
  undefined8 uVar1;
  int iVar2;
  int iVar3;
  undefined1 *puVar4;
  undefined1 *puVar5;
  int iVar6;
  
  puVar4 = (undefined1 *)((int)param_1 + 0x15);
  iVar2 = param_1[2];
  iVar6 = 9;
  do {
    iVar3 = iVar2 % 10;
    iVar2 = iVar2 / 10;
    puVar5 = puVar4 + -1;
    *puVar4 = (char)iVar3;
    iVar3 = iVar6 + -1;
    if (((iVar3 == 6) || (iVar3 == 2)) && (iVar2 != 0)) {
      *puVar5 = 10;
      puVar5 = puVar4 + -2;
      iVar3 = iVar6 + -2;
    }
    iVar6 = iVar3;
    puVar4 = puVar5;
  } while (0 < iVar2);
  for (; -1 < iVar6; iVar6 = iVar6 + -1) {
    *puVar4 = 0xc;
    puVar4 = puVar4 + -1;
  }
  for (iVar2 = 0; iVar2 < 10; iVar2 = iVar2 + 1) {
    uVar1 = getPP__7primWinFi(*param_1,iVar2);
    SetUV__11MenuPolygonFUsUsUsUs(uVar1,*(char *)((int)param_1 + iVar2 + 0xc) * 0x10 + 1,1,
                    (*(char *)((int)param_1 + iVar2 + 0xc) + 1) * 0x10,0x14);
    setPolyAlpha__7primWinFii(*param_1,iVar2,0x80);
    if (*(char *)((int)param_1 + iVar2 + 0xc) == '\f') {
      setPolyAlpha__7primWinFii(*param_1,iVar2,0);
    }
  }
  return;
}
