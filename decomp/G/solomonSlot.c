/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: solomonSlot   functions: 11
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/solomonSlot.md).
 */

/* JP: 0x00502220  solomonSlot::solomonSlot(primLayer*)   [__ct__11solomonSlotFP9primLayer]  size=0x64 */
int __ct__11solomonSlotFP9primLayer(int param_1,undefined4 param_2)

{
  __ct__7CPolObjFv(param_1);
  *(undefined1 **)(param_1 + 0x14) = &__vt__11solomonSlot;
  *(undefined4 *)(param_1 + 0x18) = 0;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  *(undefined4 *)(param_1 + 0x38) = 0;
  *(undefined4 *)(param_1 + 0x60) = param_2;
  return param_1;
}

/* JP: 0x00502290  solomonSlot::~solomonSlot()   [__dt__11solomonSlotFv]  size=0xfc */
int __dt__11solomonSlotFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 0x14) = &__vt__11solomonSlot;
    Dispose__7CPollerFP7CPolObj(app__4CApp + 0x48,param_1);
    if (*(int *)(param_1 + 0x18) != 0) {
      DelayDeleteRequest__10primPacketFv(*(undefined4 *)(param_1 + 0x18));
      *(undefined4 *)(param_1 + 0x18) = 0;
    }
    if (*(int *)(param_1 + 0x1c) != 0) {
      DelayDeleteRequest__10primPacketFv(*(undefined4 *)(param_1 + 0x1c));
      *(undefined4 *)(param_1 + 0x1c) = 0;
    }
    if (*(int *)(param_1 + 0x38) != 0) {
      DelayDeleteRequest__10primPacketFv(*(undefined4 *)(param_1 + 0x38));
      *(undefined4 *)(param_1 + 0x38) = 0;
    }
    __dt__7CPolObjFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x00502390  solomonSlot::initialize(Matrix*, float, float, bool)   [initialize__11solomonSlotFP6Matrixffb]  size=0x274 */
void initialize__11solomonSlotFP6Matrixffb
               (undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4,char param_5)

{
  undefined4 uVar1;
  long lVar2;
  
  *(undefined4 *)(param_3 + 0x5c) = param_4;
  lVar2 = __nw__FUi(0x150);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = __ct__10primSpriteFb(lVar2,1);
  }
  *(undefined4 *)(param_3 + 0x18) = uVar1;
  setDisp__10primPacketFP9primLayeriffff(param_1,param_2,0x3f800000,0x3f800000,*(undefined4 *)(param_3 + 0x18),
                  *(undefined4 *)(param_3 + 0x60),0xe);
  setUV__10primPacketFiiii(*(undefined4 *)(param_3 + 0x18),0x4f,0,0x78,0x2a);
  setSize__10primPacketFii(*(undefined4 *)(param_3 + 0x18),0x28,0x2a);
  setCenterMode__10primPacketFi(*(undefined4 *)(param_3 + 0x18),2);
  setBlendMode__10primPacketFi(*(undefined4 *)(param_3 + 0x18),1);
  setParent__10primPacketFP6Matrix(*(undefined4 *)(param_3 + 0x18),param_4);
  lVar2 = __nw__FUi(0x150);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = __ct__10primSpriteFb(lVar2,1);
  }
  *(undefined4 *)(param_3 + 0x1c) = uVar1;
  setDisp__10primPacketFP9primLayeriffff(param_1,param_2,0x3f800000,0x3f800000,*(undefined4 *)(param_3 + 0x1c),
                  *(undefined4 *)(param_3 + 0x60),0xf);
  setUV__10primPacketFiiii(*(undefined4 *)(param_3 + 0x1c),0,0,0x18,0x20);
  setSize__10primPacketFii(*(undefined4 *)(param_3 + 0x1c),0x18,0x20);
  setCenterMode__10primPacketFi(*(undefined4 *)(param_3 + 0x1c),2);
  setParent__10primPacketFP6Matrix(*(undefined4 *)(param_3 + 0x1c),param_4);
  *(undefined4 *)(param_3 + 100) = param_1;
  *(undefined4 *)(param_3 + 0x68) = param_2;
  *(undefined4 *)(param_3 + 0x5c) = param_4;
  *(undefined1 *)(param_3 + 0x48) = 0;
  *(undefined4 *)(param_3 + 0x44) = 0xffffffff;
  *(undefined4 *)(param_3 + 0x3c) = 0;
  *(undefined4 *)(param_3 + 0x40) = 0;
  if (param_5 != '\0') {
    setFixEffect__11solomonSlotFv(param_3);
  }
  Entry__7CPollerFP7CPolObjib(app__4CApp + 0x48,param_3,0x80,0);
  return;
}

/* JP: 0x00502610  solomonSlot::setRGBA(int, int, int, int)   [setRGBA__11solomonSlotFiiii]  size=0x118 */
void setRGBA__11solomonSlotFiiii(int param_1,int param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  
  *(int *)(param_1 + 0x4c) = param_2;
  *(int *)(param_1 + 0x50) = param_3;
  *(int *)(param_1 + 0x54) = param_4;
  *(int *)(param_1 + 0x58) = param_5;
  iVar1 = param_5 << 1;
  if (*(char *)(param_1 + 0x48) != '\0') {
    param_5 = iVar1;
  }
  setRGBA__10primPacketFiiii(*(undefined4 *)(param_1 + 0x18),param_2,param_3,param_4,param_5);
  if (*(char *)(param_1 + 0x48) == '\0') {
    iVar1 = 0;
  }
  setRGBA__10primPacketFiiii(*(undefined4 *)(param_1 + 0x1c),param_2 << 1,param_3 << 1,param_4 << 1,iVar1);
  return;
}

/* JP: 0x00502730  solomonSlot::setAlpha(int)   [setAlpha__11solomonSlotFi]  size=0x90 */
void setAlpha__11solomonSlotFi(int param_1,int param_2)

{
  if (*(char *)(param_1 + 0x48) == '\0') {
    if (param_2 == 0x40) {
      *(undefined4 *)(param_1 + 0x3c) = 2;
    }
    else {
      setUV__10primPacketFiiii(*(undefined4 *)(param_1 + 0x18),0x4f,0,0x78,0x2a);
      *(undefined4 *)(param_1 + 0x3c) = 3;
    }
    *(undefined4 *)(param_1 + 0x40) = 0;
  }
  return;
}

/* JP: 0x005027c0  solomonSlot::setFixEffect()   [setFixEffect__11solomonSlotFv]  size=0x208 */
void setFixEffect__11solomonSlotFv(int param_1)

{
  undefined4 uVar1;
  long lVar2;
  int iVar3;
  
  if (*(int *)(param_1 + 0x38) == 0) {
    lVar2 = __nw__FUi(0x150);
    uVar1 = 0;
    if (lVar2 != 0) {
      uVar1 = __ct__11primSpritesFi(lVar2,5);
    }
    *(undefined4 *)(param_1 + 0x38) = uVar1;
    setDisp__10primPacketFP9primLayeriffff(*(undefined4 *)(param_1 + 100),*(undefined4 *)(param_1 + 0x68),0x3f800000,
                    0x3f800000,*(undefined4 *)(param_1 + 0x38),*(undefined4 *)(param_1 + 0x60),0xf);
    setUV__10primPacketFiiii(*(undefined4 *)(param_1 + 0x38),1,1,0x18,0x20);
    setSize__10primPacketFii(*(undefined4 *)(param_1 + 0x38),0x18,0x20);
    setCenterMode__10primPacketFi(*(undefined4 *)(param_1 + 0x38),2);
    setRGBA__10primPacketFiiii(*(undefined4 *)(param_1 + 0x38),0x7f,0x7f,0x7f,0x18);
    setParent__10primPacketFP6Matrix(*(undefined4 *)(param_1 + 0x38),*(undefined4 *)(param_1 + 0x5c));
    setBlendMode__10primPacketFi(*(undefined4 *)(param_1 + 0x38),1);
    for (iVar3 = 0; iVar3 < 5; iVar3 = iVar3 + 1) {
      setPos__11primSpritesFiff(*(undefined4 *)(param_1 + 100),*(undefined4 *)(param_1 + 0x68),
                      *(undefined4 *)(param_1 + 0x38),iVar3);
      setScale__11primSpritesFiff((float)iVar3 * 0.2 + 1.0,(float)iVar3 * 0.2 + 1.0,
                      *(undefined4 *)(param_1 + 0x38),iVar3);
    }
    *(undefined4 *)(param_1 + 0x3c) = 1;
    *(undefined4 *)(param_1 + 0x40) = 0;
  }
  return;
}

/* JP: 0x005029d0  solomonSlot::Polling()   [Polling__11solomonSlotFv]  size=0x3f8 */
undefined8 Polling__11solomonSlotFv(int param_1)

{
  uint uVar1;
  int iVar2;
  
  if (*(int *)(param_1 + 0x3c) == 1) {
    *(int *)(param_1 + 0x40) = *(int *)(param_1 + 0x40) + 1;
    if (*(int *)(param_1 + 0x40) < 0x5a) {
      iVar2 = *(uint *)(param_1 + 0x40) * 0x20;
      setRGBA__10primPacketFiiii(*(undefined4 *)(param_1 + 0x38),0x80,0x80,0x80,
                      iVar2 / 0x5a + (iVar2 >> 0x1f) +
                      ((*(uint *)(param_1 + 0x40) & 0x7ffffff) >> 0x1a) + 8);
    }
    else if (*(int *)(param_1 + 0x40) < 0xb4) {
      uVar1 = 0xb4 - *(int *)(param_1 + 0x40);
      iVar2 = uVar1 * 0x20;
      setRGBA__10primPacketFiiii(*(undefined4 *)(param_1 + 0x38),0x80,0x80,0x80,
                      iVar2 / 0x5a + (iVar2 >> 0x1f) + ((uVar1 & 0x7ffffff) >> 0x1a) + 8);
    }
    else {
      *(undefined4 *)(param_1 + 0x40) = 0;
    }
  }
  else if (*(char *)(param_1 + 0x48) == '\0') {
    if (*(int *)(param_1 + 0x3c) == 2) {
      *(int *)(param_1 + 0x40) = *(int *)(param_1 + 0x40) + 1;
      if (*(int *)(param_1 + 0x40) == 0x18) {
        *(undefined4 *)(param_1 + 0x3c) = 0;
      }
      iVar2 = *(uint *)(param_1 + 0x40) << 6;
      setRGBA__10primPacketFiiii(*(undefined4 *)(param_1 + 0x18),*(undefined4 *)(param_1 + 0x4c),
                      *(undefined4 *)(param_1 + 0x50),*(undefined4 *)(param_1 + 0x54),
                      iVar2 / 0x18 + (iVar2 >> 0x1f) +
                      ((*(uint *)(param_1 + 0x40) & 0x3ffffff) >> 0x19) + 0x20);
    }
    else if (*(int *)(param_1 + 0x3c) == 3) {
      *(int *)(param_1 + 0x40) = *(int *)(param_1 + 0x40) + 1;
      if (*(int *)(param_1 + 0x40) == 0x18) {
        *(undefined4 *)(param_1 + 0x3c) = 0;
      }
      uVar1 = 0x18 - *(int *)(param_1 + 0x40);
      iVar2 = uVar1 * 0x40;
      setRGBA__10primPacketFiiii(*(undefined4 *)(param_1 + 0x18),*(undefined4 *)(param_1 + 0x4c),
                      *(undefined4 *)(param_1 + 0x50),*(undefined4 *)(param_1 + 0x54),
                      iVar2 / 0x18 + (iVar2 >> 0x1f) + ((uVar1 & 0x3ffffff) >> 0x19) + 0x20);
    }
  }
  else {
    *(int *)(param_1 + 0x40) = *(int *)(param_1 + 0x40) + 1;
    if (*(int *)(param_1 + 0x40) < 0x5a) {
      iVar2 = *(uint *)(param_1 + 0x40) * 0x20;
      setRGBA__10primPacketFiiii(*(undefined4 *)(param_1 + 0x18),
                      *(int *)(param_1 + 0x4c) + *(int *)(param_1 + 0x40),
                      *(int *)(param_1 + 0x50) + *(int *)(param_1 + 0x40),
                      *(int *)(param_1 + 0x54) + *(int *)(param_1 + 0x40),
                      iVar2 / 0x5a + (iVar2 >> 0x1f) +
                      ((*(uint *)(param_1 + 0x40) & 0x7ffffff) >> 0x1a) + 0x40);
    }
    else if (*(int *)(param_1 + 0x40) < 0xb4) {
      uVar1 = 0xb4 - *(int *)(param_1 + 0x40);
      setRGBA__10primPacketFiiii(*(undefined4 *)(param_1 + 0x18),*(int *)(param_1 + 0x4c) + uVar1,
                      *(int *)(param_1 + 0x50) + uVar1,*(int *)(param_1 + 0x54) + uVar1,
                      (int)(uVar1 * 0x20) / 0x5a + ((int)(uVar1 * 0x20) >> 0x1f) +
                      ((uVar1 & 0x7ffffff) >> 0x1a) + 0x40);
    }
    else {
      *(undefined4 *)(param_1 + 0x40) = 0;
    }
  }
  return 0;
}

/* JP: 0x00502dd0  solomonSlot::fadein(int)   [fadein__11solomonSlotFi]  size=0x78 */
void fadein__11solomonSlotFi(int param_1,undefined4 param_2)

{
  fadein__8primFadeFi(*(int *)(param_1 + 0x18) + 0xc,param_2);
  fadein__8primFadeFi(*(int *)(param_1 + 0x1c) + 0xc,param_2);
  if (*(int *)(param_1 + 0x38) != 0) {
    fadein__8primFadeFi(*(int *)(param_1 + 0x38) + 0xc,param_2);
  }
  return;
}

/* JP: 0x00502e50  solomonSlot::fadeout(int)   [fadeout__11solomonSlotFi]  size=0x78 */
void fadeout__11solomonSlotFi(int param_1,undefined4 param_2)

{
  fadeout__8primFadeFi(*(int *)(param_1 + 0x18) + 0xc,param_2);
  fadeout__8primFadeFi(*(int *)(param_1 + 0x1c) + 0xc,param_2);
  if (*(int *)(param_1 + 0x38) != 0) {
    fadeout__8primFadeFi(*(int *)(param_1 + 0x38) + 0xc,param_2);
  }
  return;
}

/* JP: 0x00502ed0  solomonSlot::setDemon(int)   [setDemon__11solomonSlotFi]  size=0x218 */
undefined4 setDemon__11solomonSlotFi(int param_1,uint param_2)

{
  undefined4 uVar1;
  uint uVar2;
  uint uVar3;
  
  uVar1 = *(undefined4 *)(param_1 + 0x44);
  *(uint *)(param_1 + 0x44) = param_2;
  if (param_2 == 0xffffffff) {
    setUV__10primPacketFiiii(*(undefined4 *)(param_1 + 0x18),0x4f,0,0x78,0x2a);
    setRGBA__10primPacketFiiii(*(undefined4 *)(param_1 + 0x18),*(undefined4 *)(param_1 + 0x4c),
                    *(undefined4 *)(param_1 + 0x50),*(undefined4 *)(param_1 + 0x54),0x24);
    setBlendMode__10primPacketFi(*(undefined4 *)(param_1 + 0x18),1);
    setRGBA__10primPacketFiiii(*(undefined4 *)(param_1 + 0x1c),0,0,0,0);
    *(undefined1 *)(param_1 + 0x48) = 0;
  }
  else {
    uVar2 = param_2;
    if ((int)param_2 < 0) {
      uVar2 = param_2 + 7;
    }
    uVar3 = param_2 & 7;
    if (((int)param_2 < 0) && (uVar3 != 0)) {
      uVar3 = uVar3 - 8;
    }
    setUV__10primPacketFiiii(*(undefined4 *)(param_1 + 0x1c),uVar3 * 0x18 + 1,((int)uVar2 >> 3) << 5,
                    (uVar3 + 1) * 0x18,(((int)uVar2 >> 3) + 1) * 0x20);
    setRGBA__10primPacketFiiii(*(undefined4 *)(param_1 + 0x1c),*(int *)(param_1 + 0x4c) << 1,
                    *(int *)(param_1 + 0x50) << 1,*(int *)(param_1 + 0x54) << 1,0x40);
    setUV__10primPacketFiiii(*(undefined4 *)(param_1 + 0x18),0,0,0x28,0x2a);
    setRGBA__10primPacketFiiii(*(undefined4 *)(param_1 + 0x18),*(undefined4 *)(param_1 + 0x4c),
                    *(undefined4 *)(param_1 + 0x50),*(undefined4 *)(param_1 + 0x54),0x40);
    setBlendMode__10primPacketFi(*(undefined4 *)(param_1 + 0x18),0);
    *(undefined1 *)(param_1 + 0x48) = 1;
  }
  *(undefined4 *)(param_1 + 0x40) = 0;
  return uVar1;
}

/* JP: 0x005030f0  solomonSlot::isDemon()   [isDemon__11solomonSlotFv]  size=0x1c */
undefined1 isDemon__11solomonSlotFv(int param_1)

{
  return *(undefined1 *)(param_1 + 0x48);
}
