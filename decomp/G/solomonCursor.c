/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: solomonCursor   functions: 10
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/solomonCursor.md).
 */

/* JP: 0x00501720  solomonCursor::solomonCursor()   [__ct__13solomonCursorFv]  size=0x54 */
int __ct__13solomonCursorFv(int param_1)

{
  __ct__7CPolObjFv(param_1);
  *(undefined1 **)(param_1 + 0x14) = &__vt__13solomonCursor;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  *(undefined4 *)(param_1 + 0x20) = 0;
  *(undefined4 *)(param_1 + 0x24) = 0;
  return param_1;
}

/* JP: 0x00501780  solomonCursor::~solomonCursor()   [__dt__13solomonCursorFv]  size=0xd4 */
int __dt__13solomonCursorFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 0x14) = &__vt__13solomonCursor;
    Dispose__7CPollerFP7CPolObj(app__4CApp + 0x48,param_1);
    if (*(int *)(param_1 + 0x1c) != 0) {
      DelayDeleteRequest__10primPacketFv(*(undefined4 *)(param_1 + 0x1c));
      *(undefined4 *)(param_1 + 0x1c) = 0;
    }
    if (*(int *)(param_1 + 0x20) != 0) {
      DelayDeleteRequest__7primWinFv(*(undefined4 *)(param_1 + 0x20));
      *(undefined4 *)(param_1 + 0x20) = 0;
    }
    __dt__7CPolObjFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x00501860  solomonCursor::initialize(Matrix*, float, float, primLayer*)   [initialize__13solomonCursorFP6MatrixffP9primLayer]  size=0x2d4 */
void initialize__13solomonCursorFP6MatrixffP9primLayer
               (float param_1,float param_2,int param_3,undefined4 param_4,undefined4 param_5)

{
  undefined4 uVar1;
  int iVar2;
  long lVar3;
  
  *(undefined4 *)(param_3 + 0x18) = param_5;
  *(undefined4 *)(param_3 + 0x48) = param_4;
  lVar3 = __nw__FUi(0x150);
  uVar1 = 0;
  if (lVar3 != 0) {
    uVar1 = __ct__10primSpriteFb(lVar3,1);
  }
  *(undefined4 *)(param_3 + 0x1c) = uVar1;
  setDisp__10primPacketFP9primLayeriffff(param_1,param_2,0x3f800000,0x3f800000,*(undefined4 *)(param_3 + 0x1c),
                  *(undefined4 *)(param_3 + 0x18),0xe);
  setUV__10primPacketFiiii(*(undefined4 *)(param_3 + 0x1c),0x28,0,0x50,0x2a);
  setSize__10primPacketFii(*(undefined4 *)(param_3 + 0x1c),0x28,0x2a);
  setCenterMode__10primPacketFi(*(undefined4 *)(param_3 + 0x1c),2);
  setRGBA__10primPacketFiiii(*(undefined4 *)(param_3 + 0x1c),10,0x7f,0x7f,0x80);
  setParent__10primPacketFP6Matrix(*(undefined4 *)(param_3 + 0x1c),param_4);
  fadein__8primFadeFi(*(int *)(param_3 + 0x1c) + 0xc,0x10);
  lVar3 = __nw__FUi(0x148);
  uVar1 = 0;
  if (lVar3 != 0) {
    uVar1 = __ct__7primWinFv(lVar3);
  }
  *(undefined4 *)(param_3 + 0x20) = uVar1;
  uVar1 = *(undefined4 *)(param_3 + 0x20);
  initialize__7primWinFP7primTex(uVar1,0);
  setItem__7primWinFiii(uVar1,1,1,0);
  createPoly__7primWinFiiiiii(uVar1,0,0,(int)(param_1 - 20.0),(int)(param_2 - 4.0),8,8);
  setPolyRGBA__7primWinFiiiii(uVar1,0,0,0,0,0);
  iVar2 = getPP__7primWinFi(uVar1,0);
  *(undefined2 *)(iVar2 + 0x1c) = 1;
  *(undefined2 *)(iVar2 + 0x1e) = 0;
  buildWin__7primWinFiiiiii(uVar1,10,0,0,0,0,0);
  *(float *)(param_3 + 0x4c) = param_1;
  *(float *)(param_3 + 0x54) = param_1;
  *(float *)(param_3 + 0x50) = param_2;
  *(float *)(param_3 + 0x58) = param_2;
  *(undefined4 *)(param_3 + 0x38) = 0;
  *(undefined4 *)(param_3 + 0x3c) = 0;
  Entry__7CPollerFP7CPolObjib(app__4CApp + 0x48,param_3,0x80,0);
  return;
}

/* JP: 0x00501b40  solomonCursor::fadeout()   [fadeout__13solomonCursorFv]  size=0x34 */
void fadeout__13solomonCursorFv(int param_1)

{
  fadeout__8primFadeFi(*(int *)(param_1 + 0x1c) + 0xc,0x10);
  return;
}

/* JP: 0x00501b80  solomonCursor::setRGBA(int, int, int, int)   [setRGBA__13solomonCursorFiiii]  size=0x54 */
void setRGBA__13solomonCursorFiiii
               (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
               undefined4 param_5)

{
  *(undefined4 *)(param_1 + 0x28) = param_2;
  *(undefined4 *)(param_1 + 0x2c) = param_3;
  *(undefined4 *)(param_1 + 0x30) = param_4;
  *(undefined4 *)(param_1 + 0x34) = param_5;
  return;
}

/* JP: 0x00501be0  solomonCursor::setCurrentDemon(int)   [setCurrentDemon__13solomonCursorFi]  size=0x24 */
void setCurrentDemon__13solomonCursorFi(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 0x40) = param_2;
  return;
}

/* JP: 0x00501c10  solomonCursor::setPos(float, float)   [setPos__13solomonCursorFff]  size=0x1a8 */
void setPos__13solomonCursorFff(undefined4 param_1,undefined4 param_2,int param_3)

{
  float fVar1;
  
  fVar1 = **(float **)(param_3 + 0x48);
  *(undefined4 *)(param_3 + 0x38) = 1;
  setPos__10primPacketFff(param_1,param_2,*(undefined4 *)(param_3 + 0x1c));
  setPolyPos__7primWinFiff(*(float *)(*(int *)(param_3 + 0x48) + 0x30) +
                  (*(float *)(param_3 + 0x54) - 20.0) * fVar1,
                  *(float *)(*(int *)(param_3 + 0x48) + 0x34) +
                  (*(float *)(param_3 + 0x58) - 4.0) * fVar1,*(undefined4 *)(param_3 + 0x20),0);
  *(undefined4 *)(param_3 + 0x54) = param_1;
  *(undefined4 *)(param_3 + 0x58) = param_2;
  if (*(int *)(param_3 + 0x24) != 0) {
    if (*(int *)(param_3 + 0x44) == 0) {
      setPolyItem__10primCursorFP7primWini(*(undefined4 *)(param_3 + 0x24),*(undefined4 *)(param_3 + 0x20),0);
      qMove__10primCursorFv(*(undefined4 *)(param_3 + 0x24));
    }
    else {
      *(int *)(param_3 + 0x44) = *(int *)(param_3 + 0x44) + -1;
      setPolyItem__10primCursorFP7primWini(*(undefined4 *)(param_3 + 0x24),*(undefined4 *)(param_3 + 0x20),0);
      if ((*(int *)(param_3 + 0x44) < 0x11) && (*(int *)(param_3 + 0x44) == 10)) {
        changePri__10primCursorFi(*(undefined4 *)(param_3 + 0x24),0);
      }
    }
  }
  return;
}

/* JP: 0x00501dc0  solomonCursor::Polling()   [Polling__13solomonCursorFv]  size=0x3a0 */
undefined8 Polling__13solomonCursorFv(int param_1)

{
  int iVar1;
  int iVar2;
  
  if (*(int *)(param_1 + 0x24) == 0) {
    setRGBA__10primPacketFiiii(*(undefined4 *)(param_1 + 0x1c),0x7f,0x7f,0x7f,0x40);
  }
  else {
    *(int *)(param_1 + 0x3c) = *(int *)(param_1 + 0x3c) + 1;
    if (*(int *)(param_1 + 0x3c) < 0x1e) {
      iVar1 = *(int *)(param_1 + 0x3c) * 10;
      iVar2 = *(int *)(param_1 + 0x3c) * 0x50;
      setRGBA__10primPacketFiiii(*(undefined4 *)(param_1 + 0x1c),
                      iVar1 / 0x1e + (iVar1 >> 0x1f) +
                      ((*(int *)(param_1 + 0x3c) * 5 & 0x7fffffffU) >> 0x1e),
                      ((0x1e - *(int *)(param_1 + 0x3c)) * 0x7f) / 0x1e +
                      (*(int *)(param_1 + 0x3c) * 0x1e) / 0x1e,
                      ((0x1e - *(int *)(param_1 + 0x3c)) * 0x7f) / 0x1e +
                      iVar2 / 0x1e + (iVar2 >> 0x1f) +
                      ((*(int *)(param_1 + 0x3c) * 5 & 0xfffffffU) >> 0x1b),0x80);
    }
    else if (*(int *)(param_1 + 0x3c) < 0x3c) {
      iVar1 = 0x3c - *(int *)(param_1 + 0x3c);
      setRGBA__10primPacketFiiii(*(undefined4 *)(param_1 + 0x1c),
                      (iVar1 * 10) / 0x1e + (iVar1 * 10 >> 0x1f) +
                      ((iVar1 * 5 & 0x7fffffffU) >> 0x1e),
                      ((0x1e - iVar1) * 0x7f) / 0x1e + (iVar1 * 0x1e) / 0x1e,
                      ((0x1e - iVar1) * 0x7f) / 0x1e +
                      (iVar1 * 0x50) / 0x1e + (iVar1 * 0x50 >> 0x1f) +
                      ((iVar1 * 5 & 0xfffffffU) >> 0x1b),0x80);
    }
    else {
      *(undefined4 *)(param_1 + 0x3c) = 0;
    }
  }
  return 0;
}

/* JP: 0x00502160  solomonCursor::setCursor(primCursor*)   [setCursor__13solomonCursorFP10primCursor]  size=0x54 */
void setCursor__13solomonCursorFP10primCursor(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 0x24) = param_2;
  setPolyItem__10primCursorFP7primWini(*(undefined4 *)(param_1 + 0x24),*(undefined4 *)(param_1 + 0x20),0);
  *(undefined4 *)(param_1 + 0x44) = 0x14;
  return;
}

/* JP: 0x005021c0  solomonCursor::removeCursor()   [removeCursor__13solomonCursorFv]  size=0x58 */
void removeCursor__13solomonCursorFv(int param_1)

{
  changePri__10primCursorFi(*(undefined4 *)(param_1 + 0x24),10);
  leaveWin__10primCursorFv(*(undefined4 *)(param_1 + 0x24));
  *(undefined4 *)(param_1 + 0x24) = 0;
  setCurrentDemon__13solomonCursorFi(param_1,0xffffffffffffffff);
  return;
}
