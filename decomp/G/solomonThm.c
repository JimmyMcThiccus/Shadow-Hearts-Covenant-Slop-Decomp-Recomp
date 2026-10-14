/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: solomonThm   functions: 22
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/solomonThm.md).
 */

/* JP: 0x00503da0  solomonThm::solomonThm()   [__ct__10solomonThmFv]  size=0x9c */
int __ct__10solomonThmFv(int param_1)

{
  __ct__7CPolObjFv(param_1);
  *(undefined1 **)(param_1 + 0x14) = &__vt__10solomonThm;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  *(undefined4 *)(param_1 + 0x20) = 0;
  *(undefined4 *)(param_1 + 0x24) = 0;
  *(undefined4 *)(param_1 + 0x28) = 0;
  *(undefined4 *)(param_1 + 0x2c) = 0;
  *(undefined4 *)(param_1 + 0x30) = 0;
  *(undefined4 *)(param_1 + 0x34) = 0;
  *(undefined4 *)(param_1 + 0x44) = 0;
  *(undefined4 *)(param_1 + 0x3c) = 0;
  *(undefined4 *)(param_1 + 0x60) = 0;
  *(undefined4 *)(param_1 + 100) = 0;
  *(undefined4 *)(param_1 + 0x90) = 0;
  return param_1;
}

/* JP: 0x00503e40  solomonThm::~solomonThm()   [__dt__10solomonThmFv]  size=0x94 */
int __dt__10solomonThmFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 0x14) = &__vt__10solomonThm;
    Dispose__7CPollerFP7CPolObj(app__4CApp + 0x48,param_1);
    mReleaseThmBaseWin__10solomonThmFv(param_1);
    __dt__7CPolObjFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x00503ee0  solomonThm::initialize(primTex*, bool, int, int)   [initialize__10solomonThmFP7primTexbii]  size=0xbc */
void initialize__10solomonThmFP7primTexbii
               (int param_1,undefined4 param_2,char param_3,undefined4 param_4,undefined4 param_5)

{
  *(undefined4 *)(param_1 + 0x18) = param_2;
  *(undefined4 *)(param_1 + 0x8c) = param_4;
  *(undefined4 *)(param_1 + 0x94) = param_5;
  if (param_3 == '\0') {
    *(undefined4 *)(param_1 + 0x54) = 0;
  }
  else {
    *(undefined4 *)(param_1 + 0x54) = 0x110;
  }
  *(undefined4 *)(param_1 + 0x54) = 0;
  mSetupThmBaseWin__10solomonThmFv(param_1);
  Entry__7CPollerFP7CPolObjib(app__4CApp + 0x48,param_1,0x80,0);
  return;
}

/* JP: 0x00503fa0  solomonThm::fadein(int)   [fadein__10solomonThmFi]  size=0x3c0 */
void fadein__10solomonThmFi(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  *(undefined4 *)(param_1 + 0x3c) = 0;
  if (param_2 == 0) {
    *(undefined4 *)(param_1 + 0x44) = 0;
    uVar1 = *(undefined4 *)(param_1 + 0x1c);
    iVar2 = getPP__7primWinFi(uVar1,0);
    (**(code **)(*(int *)(iVar2 + 8) + 0x28))
              (0x435e0000,(float)(*(int *)(param_1 + 0x44) * 0xd + 0x2a));
    iVar2 = getPP__7primWinFi(uVar1,4);
    (**(code **)(*(int *)(iVar2 + 8) + 0x28))
              (0x42600000,(float)(*(int *)(param_1 + 0x44) * 0xd + 2));
    iVar2 = getPP__7primWinFi(uVar1,7);
    (**(code **)(*(int *)(iVar2 + 8) + 0x28))
              (0x42600000,(float)(*(int *)(param_1 + 0x44) * 0xd + 2));
    iVar2 = getPP__7primWinFi(uVar1,5);
    (**(code **)(*(int *)(iVar2 + 8) + 0x24))
              (0x433c0000,(float)(*(int *)(param_1 + 0x44) * 0xd + 0xc6));
    iVar2 = getPP__7primWinFi(uVar1,6);
    (**(code **)(*(int *)(iVar2 + 8) + 0x24))
              (0xc1000000,(float)(*(int *)(param_1 + 0x44) * 0xd + 0xbe));
    setPolyAlpha__7primWinFii(uVar1,0,0);
    for (iVar2 = 0; iVar2 < 8; iVar2 = iVar2 + 1) {
      setPolyAlpha__7primWinFii(uVar1,iVar2 + 3,0);
    }
    if (*(int *)(param_1 + 0x24) != 0) {
      if (*(int *)(param_1 + 0x24) != 0) {
        DelayDeleteRequest__7primWinFv(*(undefined4 *)(param_1 + 0x24));
        *(undefined4 *)(param_1 + 0x24) = 0;
      }
      *(uint *)(param_1 + 0x3c) = *(uint *)(param_1 + 0x3c) & 0xfffffffd;
      mSetupDemonWin__10solomonThmFv(param_1);
      fadein__7primWinFi(*(undefined4 *)(param_1 + 0x24),0x10);
    }
    if ((*(int *)(param_1 + 0x28) != 0) && (*(int *)(param_1 + 0x28) != 0)) {
      DelayDeleteRequest__7primWinFv(*(undefined4 *)(param_1 + 0x28));
      *(undefined4 *)(param_1 + 0x28) = 0;
    }
  }
  else {
    *(undefined4 *)(param_1 + 0x60) = 0;
    if (*(int *)(param_1 + 0x30) != 0) {
      DelayDeleteRequest__7primWinFv(*(undefined4 *)(param_1 + 0x30));
      *(undefined4 *)(param_1 + 0x30) = 0;
    }
    mSetupHintWin__10solomonThmFv(param_1);
    fadein__7primWinFi(*(undefined4 *)(param_1 + 0x30),0x10);
  }
  if (*(int *)(param_1 + 0x2c) != 0) {
    fadein__7primWinFi(*(undefined4 *)(param_1 + 0x2c),0x10);
  }
  if (*(int *)(param_1 + 0x1c) != 0) {
    fadein__7primWinFi(*(undefined4 *)(param_1 + 0x1c),0x10);
  }
  if (*(int *)(param_1 + 0x20) != 0) {
    fadein__7primWinFi(*(undefined4 *)(param_1 + 0x20),0x10);
  }
  return;
}

/* JP: 0x00504360  solomonThm::setDemon(int)   [setDemon__10solomonThmFi]  size=0xb0 */
void setDemon__10solomonThmFi(int param_1,int param_2)

{
  if ((*(int *)(param_1 + 0x94) != param_2) || (param_2 == -1)) {
    *(int *)(param_1 + 0x94) = param_2;
    *(uint *)(param_1 + 0x3c) = *(uint *)(param_1 + 0x3c) | 2;
    if (*(int *)(param_1 + 0x24) == 0) {
      mSetupDemonWin__10solomonThmFv(param_1);
    }
    else {
      fadeout__7primWinFi(*(undefined4 *)(param_1 + 0x24),2);
    }
    closeInfo__10solomonThmFv(param_1);
  }
  return;
}

/* JP: 0x00504410  solomonThm::setArea(int)   [setArea__10solomonThmFi]  size=0x68 */
void setArea__10solomonThmFi(int param_1,int param_2)

{
  if (param_2 != *(int *)(param_1 + 0x8c)) {
    *(int *)(param_1 + 0x8c) = param_2;
    *(uint *)(param_1 + 0x3c) = *(uint *)(param_1 + 0x3c) | 1;
    fadeout__7primWinFi(*(undefined4 *)(param_1 + 0x20),8);
  }
  return;
}

/* JP: 0x00504480  solomonThm::setTitle(int)   [setTitle__10solomonThmFi]  size=0x54 */
void setTitle__10solomonThmFi(int param_1,int param_2)

{
  if (param_2 != *(int *)(param_1 + 0x90)) {
    *(int *)(param_1 + 0x90) = param_2;
    *(undefined4 *)(param_1 + 0x50) = 0;
    *(uint *)(param_1 + 0x3c) = *(uint *)(param_1 + 0x3c) | 0x100;
  }
  return;
}

/* JP: 0x005044e0  solomonThm::closeInfo()   [closeInfo__10solomonThmFv]  size=0x70 */
void closeInfo__10solomonThmFv(int param_1)

{
  if ((*(int *)(param_1 + 0x44) == 0) && (*(int *)(param_1 + 0x28) != 0)) {
    *(uint *)(param_1 + 0x3c) = *(uint *)(param_1 + 0x3c) | 8;
    *(undefined4 *)(param_1 + 0x44) = 0x10;
    fadeout__7primWinFi(*(undefined4 *)(param_1 + 0x28),8);
  }
  return;
}

/* JP: 0x00504550  solomonThm::moveRight()   [moveRight__10solomonThmFv]  size=0x10 */
void moveRight__10solomonThmFv(void)

{
  return;
}

/* JP: 0x00504560  solomonThm::moveLeft()   [moveLeft__10solomonThmFv]  size=0x10 */
void moveLeft__10solomonThmFv(void)

{
  return;
}

/* JP: 0x00504570  solomonThm::isMove()   [isMove__10solomonThmFv]  size=0x3c */
bool isMove__10solomonThmFv(int param_1)

{
  return (*(uint *)(param_1 + 0x3c) & 0x30) != 0;
}

/* JP: 0x005045b0  solomonThm::Polling()   [Polling__10solomonThmFv]  size=0xe10 */
undefined8 Polling__10solomonThmFv(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  float fVar5;
  
  if (((*(uint *)(param_1 + 0x3c) & 1) != 0) &&
     (*(char *)(*(int *)(param_1 + 0x20) + 0x102) != '\0')) {
    if (*(int *)(param_1 + 0x20) != 0) {
      DelayDeleteRequest__7primWinFv(*(undefined4 *)(param_1 + 0x20));
      *(undefined4 *)(param_1 + 0x20) = 0;
    }
    mSetupAreaWin__10solomonThmFv(param_1);
    *(uint *)(param_1 + 0x3c) = *(uint *)(param_1 + 0x3c) & 0xfffffffe;
  }
  if (((*(uint *)(param_1 + 0x3c) & 2) != 0) &&
     (*(char *)(*(int *)(param_1 + 0x24) + 0x102) != '\0')) {
    *(uint *)(param_1 + 0x3c) = *(uint *)(param_1 + 0x3c) & 0xffffffbf;
    if (*(int *)(param_1 + 0x24) != 0) {
      DelayDeleteRequest__7primWinFv(*(undefined4 *)(param_1 + 0x24));
      *(undefined4 *)(param_1 + 0x24) = 0;
    }
    mSetupDemonWin__10solomonThmFv(param_1);
    *(uint *)(param_1 + 0x3c) = *(uint *)(param_1 + 0x3c) & 0xfffffffd;
  }
  if ((*(uint *)(param_1 + 0x3c) & 4) != 0) {
    *(int *)(param_1 + 0x44) = *(int *)(param_1 + 0x44) + 1;
    uVar1 = *(undefined4 *)(param_1 + 0x1c);
    iVar2 = getPP__7primWinFi(uVar1,0);
    (**(code **)(*(int *)(iVar2 + 8) + 0x28))
              (0x435e0000,(float)(*(int *)(param_1 + 0x44) * 0xd + 0x2a));
    iVar2 = getPP__7primWinFi(uVar1,4);
    (**(code **)(*(int *)(iVar2 + 8) + 0x28))
              (0x42600000,(float)(*(int *)(param_1 + 0x44) * 0xd + 2));
    iVar2 = getPP__7primWinFi(uVar1,7);
    (**(code **)(*(int *)(iVar2 + 8) + 0x28))
              (0x42600000,(float)(*(int *)(param_1 + 0x44) * 0xd + 2));
    iVar2 = getPP__7primWinFi(uVar1,5);
    (**(code **)(*(int *)(iVar2 + 8) + 0x24))
              (0x433c0000,(float)(*(int *)(param_1 + 0x44) * 0xd + 0xc6));
    iVar2 = getPP__7primWinFi(uVar1,6);
    (**(code **)(*(int *)(iVar2 + 8) + 0x24))
              (0xc1000000,(float)(*(int *)(param_1 + 0x44) * 0xd + 0xbe));
    iVar2 = *(int *)(param_1 + 0x44) * 0x80;
    if (iVar2 < 0) {
      iVar2 = iVar2 + 0xf;
    }
    setPolyAlpha__7primWinFii(uVar1,0,((iVar2 >> 4) * 0x3c) / 0x50);
    for (iVar4 = 0; iVar4 < *(int *)(param_1 + 100); iVar4 = iVar4 + 1) {
      setPolyAlpha__7primWinFii(uVar1,iVar4 + 3,iVar2 >> 4);
    }
    if (*(int *)(param_1 + 0x44) == 0x10) {
      *(uint *)(param_1 + 0x3c) = *(uint *)(param_1 + 0x3c) & 0xfffffffb;
      *(undefined4 *)(param_1 + 0x44) = 0;
      mSetupInfoWin__10solomonThmFv(param_1);
    }
  }
  if ((*(uint *)(param_1 + 0x3c) & 8) != 0) {
    *(int *)(param_1 + 0x44) = *(int *)(param_1 + 0x44) + -1;
    uVar1 = *(undefined4 *)(param_1 + 0x1c);
    iVar2 = getPP__7primWinFi(uVar1,0);
    (**(code **)(*(int *)(iVar2 + 8) + 0x28))
              (0x435e0000,(float)(*(int *)(param_1 + 0x44) * 0xd + 0x2a));
    iVar2 = getPP__7primWinFi(uVar1,4);
    (**(code **)(*(int *)(iVar2 + 8) + 0x28))
              (0x42600000,(float)(*(int *)(param_1 + 0x44) * 0xd + 2));
    iVar2 = getPP__7primWinFi(uVar1,7);
    (**(code **)(*(int *)(iVar2 + 8) + 0x28))
              (0x42600000,(float)(*(int *)(param_1 + 0x44) * 0xd + 2));
    iVar2 = getPP__7primWinFi(uVar1,5);
    (**(code **)(*(int *)(iVar2 + 8) + 0x24))
              (0x433c0000,(float)(*(int *)(param_1 + 0x44) * 0xd + 0xc6));
    iVar2 = getPP__7primWinFi(uVar1,6);
    (**(code **)(*(int *)(iVar2 + 8) + 0x24))
              (0xc1000000,(float)(*(int *)(param_1 + 0x44) * 0xd + 0xbe));
    iVar2 = *(int *)(param_1 + 0x44) * 0x80;
    if (iVar2 < 0) {
      iVar2 = iVar2 + 0xf;
    }
    setPolyAlpha__7primWinFii(uVar1,0,((iVar2 >> 4) * 0x3c) / 0x50);
    for (iVar4 = 0; iVar4 < *(int *)(param_1 + 100); iVar4 = iVar4 + 1) {
      setPolyAlpha__7primWinFii(uVar1,iVar4 + 3,iVar2 >> 4);
    }
    if (*(int *)(param_1 + 0x44) == 0) {
      *(uint *)(param_1 + 0x3c) = *(uint *)(param_1 + 0x3c) & 0xffffff77;
      if (*(int *)(param_1 + 0x28) != 0) {
        DelayDeleteRequest__7primWinFv(*(undefined4 *)(param_1 + 0x28));
        *(undefined4 *)(param_1 + 0x28) = 0;
      }
      if (*(int *)(param_1 + 0x30) != 0) {
        DelayDeleteRequest__7primWinFv(*(undefined4 *)(param_1 + 0x30));
        *(undefined4 *)(param_1 + 0x30) = 0;
      }
    }
  }
  if ((*(uint *)(param_1 + 0x3c) & 0x10) != 0) {
    *(int *)(param_1 + 0x48) = *(int *)(param_1 + 0x48) + 1;
    if (*(int *)(param_1 + 0x48) < 0x10) {
      iVar2 = *(int *)(param_1 + 0x48) * -0x100;
      if (iVar2 < 0) {
        iVar2 = iVar2 + 0xf;
      }
      mThmScroll__10solomonThmFf((float)(iVar2 >> 4),param_1);
    }
    else if (*(int *)(param_1 + 0x48) < 0x20) {
      iVar2 = (*(int *)(param_1 + 0x48) + -0x10) * 0x100;
      if (iVar2 < 0) {
        iVar2 = iVar2 + 0xf;
      }
      mThmScroll__10solomonThmFf((float)(0x200 - (iVar2 >> 4)),param_1);
    }
    else {
      mThmScroll__10solomonThmFf(0x43880000,param_1);
      *(undefined4 *)(param_1 + 0x54) = 0x110;
      *(uint *)(param_1 + 0x3c) = *(uint *)(param_1 + 0x3c) & 0xffffffef;
    }
  }
  if ((*(uint *)(param_1 + 0x3c) & 0x20) != 0) {
    *(int *)(param_1 + 0x48) = *(int *)(param_1 + 0x48) + 1;
    if (*(int *)(param_1 + 0x48) < 0x10) {
      iVar2 = *(int *)(param_1 + 0x48) * 0x100;
      if (iVar2 < 0) {
        iVar2 = iVar2 + 0xf;
      }
      mThmScroll__10solomonThmFf((float)((iVar2 >> 4) + 0x100),param_1);
    }
    else if (*(int *)(param_1 + 0x48) < 0x20) {
      iVar2 = (*(int *)(param_1 + 0x48) + -0x10) * 0x100;
      if (iVar2 < 0) {
        iVar2 = iVar2 + 0xf;
      }
      mThmScroll__10solomonThmFf((float)((iVar2 >> 4) + -0x100),param_1);
    }
    else {
      mThmScroll__10solomonThmFf(0,param_1);
      *(undefined4 *)(param_1 + 0x54) = 0;
      *(uint *)(param_1 + 0x3c) = *(uint *)(param_1 + 0x3c) & 0xffffffdf;
    }
  }
  if ((*(uint *)(param_1 + 0x3c) & 0x40) != 0) {
    *(int *)(param_1 + 0x4c) = *(int *)(param_1 + 0x4c) + 1;
    if (*(int *)(param_1 + 0x4c) < 0x78) {
      iVar2 = *(uint *)(param_1 + 0x4c) * 0x40;
      setPolyAlpha__7primWinFii(*(undefined4 *)(param_1 + 0x24),0,
                      iVar2 / 0x78 + (iVar2 >> 0x1f) +
                      ((*(uint *)(param_1 + 0x4c) & 0x3ffffff) >> 0x19) + 0x40);
    }
    else if (*(int *)(param_1 + 0x4c) < 0xf0) {
      uVar3 = 0xf0 - *(int *)(param_1 + 0x4c);
      iVar2 = uVar3 * 0x40;
      setPolyAlpha__7primWinFii(*(undefined4 *)(param_1 + 0x24),0,
                      iVar2 / 0x78 + (iVar2 >> 0x1f) + ((uVar3 & 0x3ffffff) >> 0x19) + 0x40);
    }
    else {
      *(undefined4 *)(param_1 + 0x4c) = 0;
    }
  }
  if ((*(uint *)(param_1 + 0x3c) & 0x80) != 0) {
    *(int *)(param_1 + 0x4c) = *(int *)(param_1 + 0x4c) + 1;
    if (*(int *)(param_1 + 0x4c) < 0x78) {
      iVar2 = *(uint *)(param_1 + 0x4c) * 0x40;
      setPolyAlpha__7primWinFii(*(undefined4 *)(param_1 + 0x30),0,
                      iVar2 / 0x78 + (iVar2 >> 0x1f) +
                      ((*(uint *)(param_1 + 0x4c) & 0x3ffffff) >> 0x19) + 0x40);
    }
    else if (*(int *)(param_1 + 0x4c) < 0xf0) {
      uVar3 = 0xf0 - *(int *)(param_1 + 0x4c);
      iVar2 = uVar3 * 0x40;
      setPolyAlpha__7primWinFii(*(undefined4 *)(param_1 + 0x30),0,
                      iVar2 / 0x78 + (iVar2 >> 0x1f) + ((uVar3 & 0x3ffffff) >> 0x19) + 0x40);
    }
    else {
      *(undefined4 *)(param_1 + 0x4c) = 0;
    }
  }
  if ((*(uint *)(param_1 + 0x3c) & 0x100) != 0) {
    *(int *)(param_1 + 0x50) = *(int *)(param_1 + 0x50) + 1;
    if (*(int *)(param_1 + 0x50) < 8) {
      iVar2 = (8 - *(int *)(param_1 + 0x50)) * 0x80;
      if (iVar2 < 0) {
        iVar2 = iVar2 + 7;
      }
      setTextAlpha__7primWinFii(*(undefined4 *)(param_1 + 0x1c),0,iVar2 >> 3);
    }
    else if (*(int *)(param_1 + 0x50) == 8) {
      if (*(int *)(param_1 + 0x90) < 4) {
        changeTextString__7primWinFiPc(*(undefined4 *)(param_1 + 0x1c),0,
                        (&solomonMess_title_J)[*(int *)(param_1 + 0x90)]);
      }
      else {
        changeTextString__7primWinFiPc(*(undefined4 *)(param_1 + 0x1c),0,
                        (&solomonMess_areaName_J)[*(int *)(param_1 + 0x90) + -4]);
      }
      iVar2 = getPT__7primWinFi(*(undefined4 *)(param_1 + 0x1c),0);
      fVar5 = *(float *)(iVar2 + 0x2c);
      iVar2 = getPT__7primWinFi(*(undefined4 *)(param_1 + 0x1c),0);
      (**(code **)(*(int *)(iVar2 + 8) + 0x24))((float)(int)(416.0 - fVar5 / 2.0),0x42580000);
    }
    else if (*(int *)(param_1 + 0x50) < 0x10) {
      iVar2 = (*(int *)(param_1 + 0x50) + -8) * 0x80;
      if (iVar2 < 0) {
        iVar2 = iVar2 + 7;
      }
      setTextAlpha__7primWinFii(*(undefined4 *)(param_1 + 0x1c),0,iVar2 >> 3);
    }
    else {
      *(uint *)(param_1 + 0x3c) = *(uint *)(param_1 + 0x3c) & 0xfffffeff;
      *(undefined4 *)(param_1 + 0x50) = 0;
    }
  }
  return 0;
}

/* JP: 0x005053c0  solomonThm::mThmScroll(float)   [mThmScroll__10solomonThmFf]  size=0x24c */
void mThmScroll__10solomonThmFf(float param_1,int param_2)

{
  undefined4 uStack_10;
  
  if (*(int *)(param_2 + 0x1c) != 0) {
    SetPosition__10MenuWindowFff(param_1,*(undefined4 *)(*(int *)(param_2 + 0x1c) + 0xa4),
                    *(int *)(param_2 + 0x1c) + 0x3c);
  }
  if (*(int *)(param_2 + 0x20) != 0) {
    SetPosition__10MenuWindowFff(param_1,*(undefined4 *)(*(int *)(param_2 + 0x20) + 0xa4),
                    *(int *)(param_2 + 0x20) + 0x3c);
  }
  if (*(int *)(param_2 + 0x24) != 0) {
    SetPosition__10MenuWindowFff(param_1,*(undefined4 *)(*(int *)(param_2 + 0x24) + 0xa4),
                    *(int *)(param_2 + 0x24) + 0x3c);
  }
  if (*(int *)(param_2 + 0x28) != 0) {
    SetPosition__10MenuWindowFff(param_1,*(undefined4 *)(*(int *)(param_2 + 0x28) + 0xa4),
                    *(int *)(param_2 + 0x28) + 0x3c);
  }
  if (*(int *)(param_2 + 0x2c) != 0) {
    uStack_10 = param_1;
    if (256.0 <= param_1) {
      uStack_10 = param_1 + 104.0;
    }
    SetPosition__10MenuWindowFff(uStack_10,*(undefined4 *)(*(int *)(param_2 + 0x2c) + 0xa4),
                    *(int *)(param_2 + 0x2c) + 0x3c);
  }
  return;
}

/* JP: 0x00505610  solomonThm::mSetupThmBaseWin()   [mSetupThmBaseWin__10solomonThmFv]  size=0x6ac */
void mSetupThmBaseWin__10solomonThmFv(int param_1)

{
  undefined8 uVar1;
  long lVar2;
  undefined8 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  int iVar8;
  undefined8 *puVar9;
  undefined8 *puVar10;
  undefined8 uStack_190;
  uint auStack_188 [90];
  float fStack_20;
  float fStack_1c;
  int iStack_18;
  int iStack_14;
  int iStack_10;
  
  puVar10 = (undefined8 *)&_6500;
  puVar9 = &uStack_190;
  iVar8 = 0xb;
  do {
    uVar3 = *puVar10;
    uVar6 = *(undefined4 *)(puVar10 + 1);
    uVar7 = *(undefined4 *)((int)puVar10 + 0xc);
    uVar1 = puVar10[2];
    uVar4 = *(undefined4 *)(puVar10 + 3);
    uVar5 = *(undefined4 *)((int)puVar10 + 0x1c);
    puVar10 = puVar10 + 4;
    iVar8 = iVar8 + -1;
    *(int *)puVar9 = (int)uVar3;
    *(int *)((int)puVar9 + 4) = (int)((ulong)uVar3 >> 0x20);
    *(undefined4 *)(puVar9 + 1) = uVar6;
    *(undefined4 *)((int)puVar9 + 0xc) = uVar7;
    *(int *)(puVar9 + 2) = (int)uVar1;
    *(int *)((int)puVar9 + 0x14) = (int)((ulong)uVar1 >> 0x20);
    *(undefined4 *)(puVar9 + 3) = uVar4;
    *(undefined4 *)((int)puVar9 + 0x1c) = uVar5;
    puVar9 = puVar9 + 4;
  } while (0 < iVar8);
  *puVar9 = *puVar10;
  iStack_10 = param_1;
  if (*(int *)(param_1 + 0x1c) == 0) {
    lVar2 = __nw__FUi(0x148);
    uVar4 = 0;
    if (lVar2 != 0) {
      uVar4 = __ct__7primWinFv(lVar2);
    }
    *(undefined4 *)(iStack_10 + 0x1c) = uVar4;
    uVar4 = *(undefined4 *)(iStack_10 + 0x1c);
    initialize__7primWinFP7primTex(uVar4,*(undefined4 *)(iStack_10 + 0x18));
    setItem__7primWinFiii(uVar4,8,0x12,1);
    setTex__7primWinFiiii(uVar4,0x1b,0,0,0);
    setTex__7primWinFiiii(uVar4,0x18,1,0,0);
    setTex__7primWinFiiii(uVar4,0x1a,2,0,0);
    setTex__7primWinFiiii(uVar4,10,3,0,0);
    setTex__7primWinFiiii(uVar4,0x15,4,0,0);
    setTex__7primWinFiiii(uVar4,0x19,5,0,0);
    setTex__7primWinFiiii(uVar4,4,7,0,0);
    createPoly__7primWinFiiiiii(uVar4,0,0,0,0x197,0x200,0x20);
    setPolyRGBA__7primWinFiiiii(uVar4,0,0x1a,0x1a,0x1a,0x80);
    createPoly__7primWinFiiiiii(uVar4,1,0,0,0x13f,0x200,0x58);
    setPolyRGBA__7primWinFiiiii(uVar4,1,0,0,0,0x80);
    createPoly__7primWinFiiiiii(uVar4,2,0,0x148,0xfffffffffffffff6,0xb8,0x14a);
    setPolyRGBA__7primWinFiiiii(uVar4,2,0,0,0,0x80);
    createPoly__7primWinFiiiiii(uVar4,0xe,1,0x40,0x142,0x1ac,0x50);
    setPolyRGBA__7primWinFiiiiii(uVar4,0xe,0,0x41,0x41,0x4e,0x50);
    setPolyRGBA__7primWinFiiiiii(uVar4,0xe,2,0x41,0x41,0x4e,0x50);
    setPolyRGBA__7primWinFiiiiii(uVar4,0xe,1,10,8,10,0x50);
    setPolyRGBA__7primWinFiiiiii(uVar4,0xe,3,10,8,10,0x50);
    for (iVar8 = 0; iVar8 < 10; iVar8 = iVar8 + 1) {
      createTexPoly__7primWinFiiiiii(uVar4,iVar8 + 3,*(undefined4 *)((int)&uStack_190 + iVar8 * 0x24),
                      auStack_188[iVar8 * 9 + -1],auStack_188[iVar8 * 9],0,0);
      uVar3 = getPP__7primWinFi(uVar4,iVar8 + 3);
      (**(code **)(*(int *)((int)uVar3 + 8) + 0x28))
                ((float)(int)auStack_188[iVar8 * 9 + 1],(float)(int)auStack_188[iVar8 * 9 + 2]);
      SetUV__11MenuPolygonFUsUsUsUs(uVar3,auStack_188[iVar8 * 9 + 3] & 0xffff,auStack_188[iVar8 * 9 + 4] & 0xffff,
                      auStack_188[iVar8 * 9 + 5] & 0xffff,auStack_188[iVar8 * 9 + 6] & 0xffff);
    }
    iVar8 = getPP__7primWinFi(uVar4,4);
    **(undefined2 **)(iVar8 + 0x80) = 0xa7;
    *(undefined2 *)(*(int *)(iVar8 + 0x80) + 2) = 1;
    iVar8 = getPP__7primWinFi(uVar4,4);
    *(undefined2 *)(*(int *)(iVar8 + 0x80) + 4) = 0;
    *(undefined2 *)(*(int *)(iVar8 + 0x80) + 6) = 1;
    iVar8 = getPP__7primWinFi(uVar4,4);
    *(undefined2 *)(*(int *)(iVar8 + 0x80) + 8) = 0xa7;
    *(undefined2 *)(*(int *)(iVar8 + 0x80) + 10) = 0x18;
    iVar8 = getPP__7primWinFi(uVar4,4);
    *(undefined2 *)(*(int *)(iVar8 + 0x80) + 0xc) = 0;
    *(undefined2 *)(*(int *)(iVar8 + 0x80) + 0xe) = 0x18;
    createTexPoly__7primWinFiiiiii(uVar4,0xf,7,0x149,0xfffffffffffffff8,0,0);
    createTexPoly__7primWinFiiiiii(uVar4,0x10,4,0xfffffffffffffff4,0x124,0,0);
    createTexPoly__7primWinFiiiiii(uVar4,0x11,5,0x1e0,0x13f,0,0);
    setTextArea__7primWinFiiib(uVar4,6,0x100,0x40,1);
    createText__7primWinFiiiiPciib(uVar4,0,6,0,0,(&solomonMess_title_J)[*(int *)(iStack_10 + 0x90)],0x20,1);
    iStack_18 = getPT__7primWinFi(uVar4,0);
    fStack_20 = *(float *)(iStack_18 + 0x2c);
    iStack_14 = (int)(416.0 - fStack_20 / 2.0);
    fStack_1c = fStack_20;
    iVar8 = getPT__7primWinFi(uVar4,0);
    (**(code **)(*(int *)(iVar8 + 8) + 0x24))((float)iStack_14,0x42580000);
    buildWin__7primWinFiiiiii(uVar4,2,*(undefined4 *)(iStack_10 + 0x54),0xc,0,0,0);
    fadein__7primWinFi(*(undefined4 *)(iStack_10 + 0x1c),0x10);
  }
  *(undefined4 *)(iStack_10 + 100) = 6;
  mSetupKeyWin__10solomonThmFv(iStack_10);
  mSetupAreaWin__10solomonThmFv(iStack_10);
  mSetupDemonWin__10solomonThmFv(iStack_10);
  return;
}

/* JP: 0x00505cc0  solomonThm::mSetupInfoWin()   [mSetupInfoWin__10solomonThmFv]  size=0x140 */
void mSetupInfoWin__10solomonThmFv(int param_1)

{
  undefined4 uVar1;
  long lVar2;
  
  if (*(int *)(param_1 + 0x28) == 0) {
    lVar2 = __nw__FUi(0x148);
    uVar1 = 0;
    if (lVar2 != 0) {
      uVar1 = __ct__7primWinFv(lVar2);
    }
    *(undefined4 *)(param_1 + 0x28) = uVar1;
    uVar1 = *(undefined4 *)(param_1 + 0x28);
    initialize__7primWinFP7primTex(uVar1,*(undefined4 *)(param_1 + 0x18));
    setItem__7primWinFiii(uVar1,1,0,1);
    setTextArea__7primWinFiiib(uVar1,0,0x13e,0x204,1);
    createText__7primWinFiiiiPciib(uVar1,0,0,0x1e,0xb2,(&solomonMess_demonNote_J)[*(int *)(param_1 + 0x94)],0,0);
    buildWin__7primWinFiiiiii(uVar1,3,*(undefined4 *)(param_1 + 0x54),0xc,0,0,0);
    fadein__7primWinFi(*(undefined4 *)(param_1 + 0x28),8);
  }
  return;
}

/* JP: 0x00505e00  solomonThm::mReleaseThmBaseWin()   [mReleaseThmBaseWin__10solomonThmFv]  size=0x140 */
void mReleaseThmBaseWin__10solomonThmFv(int param_1)

{
  if (*(int *)(param_1 + 0x28) != 0) {
    DelayDeleteRequest__7primWinFv(*(undefined4 *)(param_1 + 0x28));
    *(undefined4 *)(param_1 + 0x28) = 0;
  }
  if (*(int *)(param_1 + 0x20) != 0) {
    DelayDeleteRequest__7primWinFv(*(undefined4 *)(param_1 + 0x20));
    *(undefined4 *)(param_1 + 0x20) = 0;
  }
  if (*(int *)(param_1 + 0x24) != 0) {
    DelayDeleteRequest__7primWinFv(*(undefined4 *)(param_1 + 0x24));
    *(undefined4 *)(param_1 + 0x24) = 0;
  }
  if (*(int *)(param_1 + 0x1c) != 0) {
    DelayDeleteRequest__7primWinFv(*(undefined4 *)(param_1 + 0x1c));
    *(undefined4 *)(param_1 + 0x1c) = 0;
  }
  if (*(int *)(param_1 + 0x2c) != 0) {
    DelayDeleteRequest__7primWinFv(*(undefined4 *)(param_1 + 0x2c));
    *(undefined4 *)(param_1 + 0x2c) = 0;
  }
  if (*(int *)(param_1 + 0x30) != 0) {
    DelayDeleteRequest__7primWinFv(*(undefined4 *)(param_1 + 0x30));
    *(undefined4 *)(param_1 + 0x30) = 0;
  }
  if (*(int *)(param_1 + 0x34) != 0) {
    DelayDeleteRequest__7primWinFv(*(undefined4 *)(param_1 + 0x34));
    *(undefined4 *)(param_1 + 0x34) = 0;
  }
  *(undefined4 *)(param_1 + 0x3c) = 0;
  return;
}

/* JP: 0x00505f40  solomonThm::mSetupAreaWin()   [mSetupAreaWin__10solomonThmFv]  size=0x1a8 */
void mSetupAreaWin__10solomonThmFv(int param_1)

{
  undefined4 uVar1;
  long lVar2;
  
  if (*(int *)(param_1 + 0x20) == 0) {
    lVar2 = __nw__FUi(0x148);
    uVar1 = 0;
    if (lVar2 != 0) {
      uVar1 = __ct__7primWinFv(lVar2);
    }
    *(undefined4 *)(param_1 + 0x20) = uVar1;
    uVar1 = *(undefined4 *)(param_1 + 0x20);
    initialize__7primWinFP7primTex(uVar1,*(undefined4 *)(param_1 + 0x18));
    setItem__7primWinFiii(uVar1,3,2,1);
    setTex__7primWinFiiii(uVar1,0x17,2,0,0);
    createTexPoly__7primWinFiiiiii(uVar1,1,2,7,0x14c,0,0);
    setPolyRGBA__7primWinFiiiii(uVar1,1,(&mAREASLOTBASECOLORTbl)[*(int *)(param_1 + 0x8c) * 3],
                    (&DAT_00554431)[*(int *)(param_1 + 0x8c) * 3],
                    (&DAT_00554432)[*(int *)(param_1 + 0x8c) * 3],0x7f);
    buildWin__7primWinFiiiiii(uVar1,3,0,0,0,0,0);
    fadein__7primWinFi(*(undefined4 *)(param_1 + 0x20),8);
  }
  return;
}

/* JP: 0x005060f0  solomonThm::mSetupDemonWin()   [mSetupDemonWin__10solomonThmFv]  size=0x278 */
void mSetupDemonWin__10solomonThmFv(int param_1)

{
  undefined4 uVar1;
  long lVar2;
  
  if (*(int *)(param_1 + 0x24) == 0) {
    lVar2 = __nw__FUi(0x148);
    uVar1 = 0;
    if (lVar2 != 0) {
      uVar1 = __ct__7primWinFv(lVar2);
    }
    *(undefined4 *)(param_1 + 0x24) = uVar1;
    uVar1 = *(undefined4 *)(param_1 + 0x24);
    initialize__7primWinFP7primTex(uVar1,*(undefined4 *)(param_1 + 0x18));
    setItem__7primWinFiii(uVar1,3,2,2);
    if (*(int *)(param_1 + 0x94) == -2) {
      setTex__7primWinFiiii(uVar1,0x1d,0,0,0);
      createTexPoly__7primWinFiiiiii(uVar1,0,0,10,0x143,0,0);
      setPolyRGBA__7primWinFiiiii(uVar1,0,0x7f,0x73,0x41,0x7f);
    }
    else {
      setTex__7primWinFiiii(uVar1,*(int *)(param_1 + 0x94) + 0x1e,0,0,0);
      createTexPoly__7primWinFiiiiii(uVar1,0,0,10,0x143,0,0);
      setPolyRGBA__7primWinFiiiii(uVar1,0,(&mAREACOLORTbl)[*(int *)(param_1 + 0x8c) * 3],
                      (&DAT_00554411)[*(int *)(param_1 + 0x8c) * 3],
                      (&DAT_00554412)[*(int *)(param_1 + 0x8c) * 3],0x7f);
    }
    *(uint *)(param_1 + 0x3c) = *(uint *)(param_1 + 0x3c) | 0x40;
    *(undefined4 *)(param_1 + 0x4c) = 0;
    if (-1 < *(int *)(param_1 + 0x94)) {
      setTextArea__7primWinFiiib(uVar1,2,0x200,0x100,1);
    }
    buildWin__7primWinFiiiiii(uVar1,3,*(undefined4 *)(param_1 + 0x54),0xc,0,0,0);
    fadein__7primWinFi(*(undefined4 *)(param_1 + 0x24),8);
  }
  return;
}

/* JP: 0x00506370  solomonThm::mSetupKeyWin()   [mSetupKeyWin__10solomonThmFv]  size=0x224 */
void mSetupKeyWin__10solomonThmFv(int param_1)

{
  undefined4 uVar1;
  long lVar2;
  int iVar3;
  
  if (*(int *)(param_1 + 0x2c) == 0) {
    lVar2 = __nw__FUi(0x148);
    uVar1 = 0;
    if (lVar2 != 0) {
      uVar1 = __ct__7primWinFv(lVar2);
    }
    *(undefined4 *)(param_1 + 0x2c) = uVar1;
    uVar1 = *(undefined4 *)(param_1 + 0x2c);
    initialize__7primWinFP7primTex(uVar1,*(undefined4 *)(param_1 + 0x18));
    setItem__7primWinFiii(uVar1,2,6,6);
    setMenuTex__7primWinFP11MenuTextureiii(uVar1,0x421658,0,0x10,0x14);
    setTextArea__7primWinFiiib(uVar1,1,0x100,0x100,1);
    for (iVar3 = 0; iVar3 < 2; iVar3 = iVar3 + 1) {
      createText__7primWinFiiiiPciib(uVar1,iVar3,1,0x17c,iVar3 * 0x18 + 0x10e,
                      *(undefined4 *)(&solomonMess_keyAssign_J + iVar3 * 4),0,0);
    }
    createTexPoly__7primWinFiiiiii(uVar1,0,0,0x15c,0x10e,0,1);
    createTexPoly__7primWinFiiiiii(uVar1,1,0,0x16c,0x10e,1,1);
    createTexPoly__7primWinFiiiiii(uVar1,2,0,0x16c,0x126,2,0);
    buildWin__7primWinFiiiiii(uVar1,3,0,0,0,0,0);
    fadein__7primWinFi(*(undefined4 *)(param_1 + 0x2c),8);
  }
  return;
}

/* JP: 0x005065a0  solomonThm::setHintData(int, int)   [setHintData__10solomonThmFii]  size=0x34 */
void setHintData__10solomonThmFii(int param_1,undefined4 param_2,undefined4 param_3)

{
  *(undefined4 *)(param_1 + 0x58) = param_2;
  *(undefined4 *)(param_1 + 0x5c) = param_3;
  return;
}

/* JP: 0x005065e0  solomonThm::mSetupHintWin()   [mSetupHintWin__10solomonThmFv]  size=0x2c4 */
void mSetupHintWin__10solomonThmFv(int param_1)

{
  undefined4 uVar1;
  long lVar2;
  undefined8 uVar3;
  int iVar4;
  uint uVar5;
  
  if (*(int *)(param_1 + 0x30) == 0) {
    lVar2 = __nw__FUi(0x148);
    uVar1 = 0;
    if (lVar2 != 0) {
      uVar1 = __ct__7primWinFv(lVar2);
    }
    *(undefined4 *)(param_1 + 0x30) = uVar1;
    uVar1 = *(undefined4 *)(param_1 + 0x30);
    initialize__7primWinFP7primTex(uVar1,*(undefined4 *)(param_1 + 0x18));
    setItem__7primWinFiii(uVar1,3,2,0xb);
    setTex__7primWinFiiii(uVar1,0x1d,2,0,0);
    setTex__7primWinFiiii(uVar1,0x17,0,0,0);
    createTexPoly__7primWinFiiiiii(uVar1,1,0,7,0x140,0,0);
    setPolyRGBA__7primWinFiiiii(uVar1,1,0x7f,0x30,0,0x7f);
    createTexPoly__7primWinFiiiiii(uVar1,0,2,10,0x144,0,0);
    setPolyRGBA__7primWinFiiiii(uVar1,0,0x7f,0x73,0x41,0x7f);
    *(uint *)(param_1 + 0x3c) = *(uint *)(param_1 + 0x3c) | 0x80;
    *(undefined4 *)(param_1 + 0x4c) = 0;
    setTextArea__7primWinFiiib(uVar1,1,0x200,0x180,1);
    iVar4 = 0;
    uVar5 = 0;
    while (iVar4 < *(int *)(param_1 + 0x58)) {
      if ((*(uint *)(param_1 + 0x5c) & 1 << (uVar5 & 0x1f)) != 0) {
        uVar3 = GetRegDat__9RegDatApiFiii(10,uVar5 + 0xac,0xffffffffffffffff);
        createText__7primWinFiiiiPciib(uVar1,iVar4,1,0x15c,iVar4 * 0x16 + 0x60,uVar3,0,0);
        iVar4 = iVar4 + 1;
      }
      uVar5 = uVar5 + 1;
    }
    setMenuWindow__7primWinFiiiii(uVar1,*(undefined4 *)(param_1 + 0x58),*(undefined4 *)(param_1 + 0x60),0,
                    0xffffffffffffffff,0xffffff);
    buildWin__7primWinFiiiiii(uVar1,3,*(undefined4 *)(param_1 + 0x54),0xc,0,0,0);
    fadein__7primWinFi(*(undefined4 *)(param_1 + 0x30),8);
  }
  return;
}

/* JP: 0x005068b0  solomonThm::dispHint(int)   [dispHint__10solomonThmFi]  size=0x318 */
void dispHint__10solomonThmFi(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  long lVar2;
  undefined8 uVar3;
  uint uVar4;
  int iVar5;
  float fVar6;
  
  if (*(int *)(param_1 + 0x30) != 0) {
    DelayDeleteRequest__7primWinFv(*(undefined4 *)(param_1 + 0x30));
    *(undefined4 *)(param_1 + 0x30) = 0;
  }
  *(undefined4 *)(param_1 + 0x60) = param_2;
  uVar4 = 0;
  iVar5 = 0;
  do {
    if ((*(uint *)(param_1 + 0x5c) & 1 << (uVar4 & 0x1f)) != 0) {
      if (iVar5 == *(int *)(param_1 + 0x60)) {
        lVar2 = __nw__FUi(0x148);
        uVar1 = 0;
        if (lVar2 != 0) {
          uVar1 = __ct__7primWinFv(lVar2);
        }
        *(undefined4 *)(param_1 + 0x30) = uVar1;
        uVar1 = *(undefined4 *)(param_1 + 0x30);
        initialize__7primWinFP7primTex(uVar1,*(undefined4 *)(param_1 + 0x18));
        setItem__7primWinFiii(uVar1,2,1,2);
        setTex__7primWinFiiii(uVar1,0x1d,0,0,0);
        createTexPoly__7primWinFiiiiii(uVar1,0,0,0x10,0x4f,0,0);
        setPolyRGBA__7primWinFiiiii(uVar1,0,0x7f,0x73,0x41,0x7f);
        *(uint *)(param_1 + 0x3c) = *(uint *)(param_1 + 0x3c) | 0x80;
        *(undefined4 *)(param_1 + 0x4c) = 0;
        setTextArea__7primWinFiiib(uVar1,1,0x140,0x200,1);
        uVar3 = GetRegDat__9RegDatApiFiii(10,uVar4 + 0xac,0xffffffffffffffff);
        createText__7primWinFiiiiPciib(uVar1,0,1,0x40,0xd0,uVar3,0,1);
        iVar5 = getPT__7primWinFi(uVar1,0);
        fVar6 = *(float *)(iVar5 + 0x2c);
        iVar5 = getPT__7primWinFi(uVar1,0);
        (**(code **)(*(int *)(iVar5 + 8) + 0x24))((float)(int)(120.0 - fVar6 / 2.0),0x43300000);
        createText__7primWinFiiiiPciib(uVar1,1,1,0x14,0xd0,(&solomonMess_hintNote_J)[uVar4],0,0);
        buildWin__7primWinFiiiiii(uVar1,3,*(undefined4 *)(param_1 + 0x54),0xc,0,0,0);
        fadein__7primWinFi(*(undefined4 *)(param_1 + 0x30),8);
        return;
      }
      iVar5 = iVar5 + 1;
    }
    uVar4 = uVar4 + 1;
  } while( true );
}
