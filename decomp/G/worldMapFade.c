/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: worldMapFade   functions: 7
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/worldMapFade.md).
 */

/* JP: 0x0050b0c0  worldMapFade::worldMapFade()   [__ct__12worldMapFadeFv]  size=0x3c */
int __ct__12worldMapFadeFv(int param_1)

{
  __ct__7CPolObjFv(param_1);
  *(undefined1 **)(param_1 + 0x14) = &__vt__12worldMapFade;
  return param_1;
}

/* JP: 0x0050b100  worldMapFade::~worldMapFade()   [__dt__12worldMapFadeFv]  size=0xb4 */
int __dt__12worldMapFadeFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 0x14) = &__vt__12worldMapFade;
    if (*(int *)(param_1 + 0x30) != 0) {
      DelayDeleteRequest__7primWinFv(*(undefined4 *)(param_1 + 0x30));
      *(undefined4 *)(param_1 + 0x30) = 0;
    }
    Dispose__7CPollerFP7CPolObj(app__4CApp + 0x48,param_1);
    __dt__7CPolObjFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x0050b1c0  worldMapFade::initialize()   [initialize__12worldMapFadeFv]  size=0x4c */
void initialize__12worldMapFadeFv(int param_1)

{
  *(undefined4 *)(param_1 + 0x18) = 0;
  Entry__7CPollerFP7CPolObjib(app__4CApp + 0x48,param_1,0x80,0);
  mSetFadeWin__12worldMapFadeFv(param_1);
  return;
}

/* JP: 0x0050b210  worldMapFade::fadeIn(int)   [fadeIn__12worldMapFadeFi]  size=0x80 */
void fadeIn__12worldMapFadeFi(int param_1,int param_2)

{
  *(undefined4 *)(param_1 + 0x18) = 1;
  *(int *)(param_1 + 0x1c) = param_2;
  *(undefined4 *)(param_1 + 0x20) = 0;
  *(undefined1 *)(param_1 + 0x2c) = 1;
  if (param_2 == 0) {
    trap(7);
  }
  *(float *)(param_1 + 0x28) = (float)(-0x1c0 / param_2);
  *(undefined4 *)(param_1 + 0x24) = 0;
  return;
}

/* JP: 0x0050b290  worldMapFade::fadeOut(int)   [fadeOut__12worldMapFadeFi]  size=0x84 */
void fadeOut__12worldMapFadeFi(int param_1,int param_2)

{
  *(undefined4 *)(param_1 + 0x18) = 2;
  *(int *)(param_1 + 0x1c) = param_2;
  *(undefined4 *)(param_1 + 0x20) = 0;
  if (param_2 == 0) {
    trap(7);
  }
  *(float *)(param_1 + 0x28) = (float)(0x1c0 / param_2);
  *(undefined4 *)(param_1 + 0x24) = 0xc3e00000;
  *(undefined1 *)(param_1 + 0x2c) = 1;
  return;
}

/* JP: 0x0050b320  worldMapFade::Polling()   [Polling__12worldMapFadeFv]  size=0x17c */
undefined8 Polling__12worldMapFadeFv(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x18);
  if (iVar1 == 3) {
    *(undefined1 *)(param_1 + 0x2c) = 0;
    *(undefined4 *)(param_1 + 0x18) = 0;
  }
  else if ((iVar1 == 2) || (iVar1 == 1)) {
    *(float *)(param_1 + 0x24) = *(float *)(param_1 + 0x24) + *(float *)(param_1 + 0x28);
    setPolyPos__7primWinFiff(0,*(undefined4 *)(param_1 + 0x24),*(undefined4 *)(param_1 + 0x30),0);
    setPolyPos__7primWinFiff(0,*(float *)(param_1 + 0x24) + 224.0,*(undefined4 *)(param_1 + 0x30),1);
    setPolyPos__7primWinFiff(0,-*(float *)(param_1 + 0x24) + 224.0,*(undefined4 *)(param_1 + 0x30),2);
    setPolyPos__7primWinFiff(0,-*(float *)(param_1 + 0x24) + 112.0,*(undefined4 *)(param_1 + 0x30),3);
    *(int *)(param_1 + 0x20) = *(int *)(param_1 + 0x20) + 1;
    if (*(int *)(param_1 + 0x20) == *(int *)(param_1 + 0x1c)) {
      *(undefined4 *)(param_1 + 0x18) = 3;
    }
  }
  return 0;
}

/* JP: 0x0050b4a0  worldMapFade::mSetFadeWin()   [mSetFadeWin__12worldMapFadeFv]  size=0x368 */
void mSetFadeWin__12worldMapFadeFv(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  long lVar3;
  ulong uVar4;
  
  lVar3 = __nw__FUi(0x148);
  uVar1 = 0;
  if (lVar3 != 0) {
    uVar1 = __ct__7primWinFv(lVar3);
  }
  *(undefined4 *)(param_1 + 0x30) = uVar1;
  uVar1 = *(undefined4 *)(param_1 + 0x30);
  initialize__7primWinFP7primTex(uVar1,0);
  setItem__7primWinFiii(uVar1,1,4,0);
  createPoly__7primWinFiiiiii(uVar1,0,0,0,0,0x200,0xe0);
  setPolyRGBA__7primWinFiiiii(uVar1,0,0,0,0,0x80);
  createPoly__7primWinFiiiiii(uVar1,1,0,0,0xe0,0x200,0x70);
  setPolyRGBA__7primWinFiiiii(uVar1,1,0,0,0,0x80);
  iVar2 = getPP__7primWinFi(uVar1,1);
  *(undefined1 *)(iVar2 + 0x77) = 0x18;
  uVar4 = (ulong)*(byte *)(iVar2 + 0x11) & 0xffffffffffffffef | 0x10;
  *(char *)(iVar2 + 0x11) = (char)uVar4;
  *(byte *)(iVar2 + 0x10) =
       *(byte *)(iVar2 + 0x10) & 0xef | (byte)((uint)((uVar4 << 0x3b) >> 0x3f) << 4);
  iVar2 = getPP__7primWinFi(uVar1,1);
  *(undefined1 *)(iVar2 + 0x7f) = 0x18;
  uVar4 = (ulong)*(byte *)(iVar2 + 0x11) & 0xffffffffffffffef | 0x10;
  *(char *)(iVar2 + 0x11) = (char)uVar4;
  *(byte *)(iVar2 + 0x10) =
       *(byte *)(iVar2 + 0x10) & 0xef | (byte)((uint)((uVar4 << 0x3b) >> 0x3f) << 4);
  createPoly__7primWinFiiiiii(uVar1,2,0,0,0xe0,0x200,0xe0);
  setPolyRGBA__7primWinFiiiii(uVar1,2,0,0,0,0x80);
  createPoly__7primWinFiiiiii(uVar1,3,0,0,0x70,0x200,0x70);
  setPolyRGBA__7primWinFiiiii(uVar1,3,0,0,0,0x80);
  iVar2 = getPP__7primWinFi(uVar1,3);
  *(undefined1 *)(iVar2 + 0x4f) = 0x18;
  uVar4 = (ulong)*(byte *)(iVar2 + 0x11) & 0xffffffffffffffef | 0x10;
  *(char *)(iVar2 + 0x11) = (char)uVar4;
  *(byte *)(iVar2 + 0x10) =
       *(byte *)(iVar2 + 0x10) & 0xef | (byte)((uint)((uVar4 << 0x3b) >> 0x3f) << 4);
  iVar2 = getPP__7primWinFi(uVar1,3);
  *(undefined1 *)(iVar2 + 0x7b) = 0x18;
  uVar4 = (ulong)*(byte *)(iVar2 + 0x11) & 0xffffffffffffffef | 0x10;
  *(char *)(iVar2 + 0x11) = (char)uVar4;
  *(byte *)(iVar2 + 0x10) =
       *(byte *)(iVar2 + 0x10) & 0xef | (byte)((uint)((uVar4 << 0x3b) >> 0x3f) << 4);
  buildWin__7primWinFiiiiii(uVar1,0x14,0,0,0,0,0);
  return;
}
