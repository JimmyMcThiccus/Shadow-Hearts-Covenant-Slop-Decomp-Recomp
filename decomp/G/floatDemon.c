/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: floatDemon   functions: 10
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/floatDemon.md).
 */

/* JP: 0x005005e0  floatDemon::floatDemon()   [__ct__10floatDemonFv]  size=0x4c */
int __ct__10floatDemonFv(int param_1)

{
  __ct__7CPolObjFv(param_1);
  *(undefined1 **)(param_1 + 0x14) = &__vt__10floatDemon;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  *(undefined4 *)(param_1 + 0x20) = 0;
  return param_1;
}

/* JP: 0x00500630  floatDemon::~floatDemon()   [__dt__10floatDemonFv]  size=0xac */
int __dt__10floatDemonFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 0x14) = &__vt__10floatDemon;
    Dispose__7CPollerFP7CPolObj(app__4CApp + 0x48,param_1);
    if (*(int *)(param_1 + 0x1c) != 0) {
      DelayDeleteRequest__10primPacketFv(*(undefined4 *)(param_1 + 0x1c));
      *(undefined4 *)(param_1 + 0x1c) = 0;
    }
    __dt__7CPolObjFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x005006e0  floatDemon::initialize(Matrix*, float, float, primLayer*)   [initialize__10floatDemonFP6MatrixffP9primLayer]  size=0x178 */
void initialize__10floatDemonFP6MatrixffP9primLayer
               (undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4,
               undefined4 param_5)

{
  undefined4 uVar1;
  long lVar2;
  
  *(undefined4 *)(param_3 + 0x18) = param_5;
  *(undefined4 *)(param_3 + 0x44) = param_4;
  *(undefined4 *)(param_3 + 0x58) = 0x3f800000;
  lVar2 = __nw__FUi(0x150);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = __ct__10primSpriteFb(lVar2,1);
  }
  *(undefined4 *)(param_3 + 0x1c) = uVar1;
  setDisp__10primPacketFP9primLayeriffff(param_1,param_2,*(undefined4 *)(param_3 + 0x58),*(undefined4 *)(param_3 + 0x58),
                  *(undefined4 *)(param_3 + 0x1c),*(undefined4 *)(param_3 + 0x18),0xf);
  setUV__10primPacketFiiii(*(undefined4 *)(param_3 + 0x1c),0,0,0x18,0x20);
  setSize__10primPacketFii(*(undefined4 *)(param_3 + 0x1c),0x18,0x20);
  setCenterMode__10primPacketFi(*(undefined4 *)(param_3 + 0x1c),2);
  setRGBA__10primPacketFiiii(*(undefined4 *)(param_3 + 0x1c),0,0,0,0);
  *(undefined4 *)(param_3 + 0x48) = param_1;
  *(undefined4 *)(param_3 + 0x4c) = param_2;
  *(undefined4 *)(param_3 + 0x34) = 0;
  *(undefined4 *)(param_3 + 0x38) = 0;
  Entry__7CPollerFP7CPolObjib(app__4CApp + 0x48,param_3,0x80,0);
  return;
}

/* JP: 0x00500860  floatDemon::setRGBA(int, int, int, int)   [setRGBA__10floatDemonFiiii]  size=0x7c */
void setRGBA__10floatDemonFiiii
               (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
               undefined4 param_5)

{
  *(undefined4 *)(param_1 + 0x24) = param_2;
  *(undefined4 *)(param_1 + 0x28) = param_3;
  *(undefined4 *)(param_1 + 0x2c) = param_4;
  *(undefined4 *)(param_1 + 0x30) = param_5;
  setRGBA__10primPacketFiiii(*(undefined4 *)(param_1 + 0x1c),param_2,param_3,param_4,param_5);
  return;
}

/* JP: 0x005008e0  floatDemon::setCurrentDemon(int)   [setCurrentDemon__10floatDemonFi]  size=0x148 */
void setCurrentDemon__10floatDemonFi(int param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  
  *(uint *)(param_1 + 0x3c) = param_2;
  if (param_2 == 0xffffffff) {
    setRGBA__10primPacketFiiii(*(undefined4 *)(param_1 + 0x1c),0xff,0xff,0xff,0x80);
    fadeout__8primFadeFi(*(int *)(param_1 + 0x1c) + 0xc,0x10);
  }
  else {
    uVar1 = param_2;
    if ((int)param_2 < 0) {
      uVar1 = param_2 + 7;
    }
    uVar2 = param_2 & 7;
    if (((int)param_2 < 0) && (uVar2 != 0)) {
      uVar2 = uVar2 - 8;
    }
    setUV__10primPacketFiiii(*(undefined4 *)(param_1 + 0x1c),uVar2 * 0x18,((int)uVar1 >> 3) << 5,
                    (uVar2 + 1) * 0x18 + 1,(((int)uVar1 >> 3) + 1) * 0x20);
    setRGBA__10primPacketFiiii(*(undefined4 *)(param_1 + 0x1c),*(undefined4 *)(param_1 + 0x24),
                    *(undefined4 *)(param_1 + 0x28),*(undefined4 *)(param_1 + 0x2c),0x80);
    fadein__8primFadeFi(*(int *)(param_1 + 0x1c) + 0xc,0x10);
  }
  return;
}

/* JP: 0x00500a30  floatDemon::Polling()   [Polling__10floatDemonFv]  size=0x35c */
undefined8 Polling__10floatDemonFv(int param_1)

{
  int iVar1;
  
  if (*(int *)(param_1 + 0x34) == 2) {
    *(int *)(param_1 + 0x38) = *(int *)(param_1 + 0x38) + 1;
    if (*(int *)(param_1 + 0x38) < 0x14) {
      setPos__10primPacketFff(((float)(*(int *)(param_1 + 0x38) * 0x1c0) +
                      (float)(0x14 - *(int *)(param_1 + 0x38)) * *(float *)(param_1 + 0x48)) / 20.0,
                      ((float)(*(int *)(param_1 + 0x38) << 7) +
                      (float)(0x14 - *(int *)(param_1 + 0x38)) * *(float *)(param_1 + 0x4c)) / 20.0,
                      *(undefined4 *)(param_1 + 0x1c));
    }
    else {
      *(undefined4 *)(param_1 + 0x34) = 0;
    }
  }
  else if (*(int *)(param_1 + 0x34) == 1) {
    *(int *)(param_1 + 0x38) = *(int *)(param_1 + 0x38) + 1;
    if (*(int *)(param_1 + 0x38) < 10) {
      *(float *)(param_1 + 0x58) = *(float *)(param_1 + 0x58) + *(float *)(param_1 + 0x5c);
      setScale__10primPacketFff(*(undefined4 *)(param_1 + 0x58),*(undefined4 *)(param_1 + 0x58),
                      *(undefined4 *)(param_1 + 0x1c));
      iVar1 = *(int *)(param_1 + 0x38);
      if (iVar1 < 0) {
        iVar1 = iVar1 + 3;
      }
      setPos__10primPacketFff(*(float *)(param_1 + 0x48) +
                      **(float **)(param_1 + 0x44) * (float)*(int *)(param_1 + 0x38) * 2.0,
                      *(float *)(param_1 + 0x4c) +
                      (**(float **)(param_1 + 0x44) - 1.0) * (float)(iVar1 >> 2),
                      *(undefined4 *)(param_1 + 0x1c));
    }
    else {
      setScale__10primPacketFff(**(undefined4 **)(param_1 + 0x44),**(undefined4 **)(param_1 + 0x44),
                      *(undefined4 *)(param_1 + 0x1c));
      setRGBA__10primPacketFiiii(*(undefined4 *)(param_1 + 0x1c),0xff,0xff,0xff,0x80);
      fadeout__8primFadeFi(*(int *)(param_1 + 0x1c) + 0xc,0x10);
      *(undefined4 *)(param_1 + 0x34) = 0;
    }
  }
  if (*(int *)(param_1 + 0x20) != 0) {
    getPos__10primCursorFPfPf(*(undefined4 *)(param_1 + 0x20),param_1 + 0x48,param_1 + 0x4c);
    *(float *)(param_1 + 0x48) = *(float *)(param_1 + 0x48) + 30.0;
    *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x4c) + 10.0;
    setPos__10primPacketFff(*(undefined4 *)(param_1 + 0x48),*(undefined4 *)(param_1 + 0x4c),
                    *(undefined4 *)(param_1 + 0x1c));
  }
  return 0;
}

/* JP: 0x00500d90  floatDemon::setCursor(primCursor*)   [setCursor__10floatDemonFP10primCursor]  size=0x30 */
void setCursor__10floatDemonFP10primCursor(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 0x20) = param_2;
  *(undefined4 *)(param_1 + 0x40) = 0x12;
  return;
}

/* JP: 0x00500dc0  floatDemon::removeCursor()   [removeCursor__10floatDemonFv]  size=0x1c */
void removeCursor__10floatDemonFv(int param_1)

{
  *(undefined4 *)(param_1 + 0x20) = 0;
  return;
}

/* JP: 0x00500de0  floatDemon::setSlot()   [setSlot__10floatDemonFv]  size=0x60 */
void setSlot__10floatDemonFv(int param_1)

{
  *(float *)(param_1 + 0x5c) = (**(float **)(param_1 + 0x44) - *(float *)(param_1 + 0x58)) / 10.0;
  *(undefined4 *)(param_1 + 0x20) = 0;
  *(undefined4 *)(param_1 + 0x34) = 1;
  *(undefined4 *)(param_1 + 0x38) = 0;
  return;
}

/* JP: 0x00500e40  floatDemon::eraseSlot(float, float)   [eraseSlot__10floatDemonFff]  size=0xd8 */
void eraseSlot__10floatDemonFff(undefined4 param_1,undefined4 param_2,int param_3)

{
  *(undefined4 *)(param_3 + 0x48) = param_1;
  *(undefined4 *)(param_3 + 0x4c) = param_2;
  *(undefined4 *)(param_3 + 0x20) = 0;
  *(undefined4 *)(param_3 + 0x34) = 2;
  setScale__10primPacketFff(**(undefined4 **)(param_3 + 0x44),**(undefined4 **)(param_3 + 0x44),
                  *(undefined4 *)(param_3 + 0x1c));
  setRGBA__10primPacketFiiii(*(undefined4 *)(param_3 + 0x1c),0xff,0xff,0xff,0x80);
  fadeout__8primFadeFi(*(int *)(param_3 + 0x1c) + 0xc,0x20);
  *(undefined4 *)(param_3 + 0x38) = 0;
  setPos__10primPacketFff(*(undefined4 *)(param_3 + 0x48),*(undefined4 *)(param_3 + 0x4c),
                  *(undefined4 *)(param_3 + 0x1c));
  return;
}
