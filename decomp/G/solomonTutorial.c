/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: solomonTutorial   functions: 5
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/solomonTutorial.md).
 */

/* JP: 0x004ffa00  solomonTutorial::solomonTutorial()   [__ct__15solomonTutorialFv]  size=0x6c */
int __ct__15solomonTutorialFv(int param_1)

{
  __ct__7CPolObjFv(param_1);
  *(undefined1 **)(param_1 + 0x14) = &__vt__15solomonTutorial;
  *(undefined4 *)(param_1 + 0x18) = 0;
  *(undefined4 *)(param_1 + 0x20) = 0;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  *(undefined4 *)(param_1 + 0x24) = 0;
  *(undefined4 *)(param_1 + 0x28) = 0;
  *(undefined1 *)(param_1 + 0x40) = 0;
  return param_1;
}

/* JP: 0x004ffa70  solomonTutorial::~solomonTutorial()   [__dt__15solomonTutorialFv]  size=0xfc */
int __dt__15solomonTutorialFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 0x14) = &__vt__15solomonTutorial;
    Dispose__7CPollerFP7CPolObj(app__4CApp + 0x48,param_1);
    if (*(int *)(param_1 + 0x18) != 0) {
      DelayDeleteRequest__7primWinFv(*(undefined4 *)(param_1 + 0x18));
      *(undefined4 *)(param_1 + 0x18) = 0;
    }
    if (*(int *)(param_1 + 0x20) != 0) {
      DelayDeleteRequest__7primWinFv(*(undefined4 *)(param_1 + 0x20));
      *(undefined4 *)(param_1 + 0x20) = 0;
    }
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

/* JP: 0x004ffb70  solomonTutorial::initialize(primTex*)   [initialize__15solomonTutorialFP7primTex]  size=0x50 */
void initialize__15solomonTutorialFP7primTex(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 0x44) = param_2;
  *(undefined4 *)(param_1 + 0x2c) = 0;
  Entry__7CPollerFP7CPolObjib(app__4CApp + 0x48,param_1,0x80,0);
  return;
}

/* JP: 0x004ffbc0  solomonTutorial::Polling()   [Polling__15solomonTutorialFv]  size=0xa00 */
undefined8 Polling__15solomonTutorialFv(int param_1)

{
  ushort uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  long lVar5;
  
  iVar2 = GetActive__4CPadFi(0);
  uVar1 = *(ushort *)(*(int *)(&m_pCoreArray__4CPad + *(int *)(iVar2 + 4) * 4) + 0x6c);
  switch(*(undefined4 *)(param_1 + 0x2c)) {
  case 0:
    lVar5 = __nw__FUi(0x148);
    uVar3 = 0;
    if (lVar5 != 0) {
      uVar3 = __ct__7primWinFv(lVar5);
    }
    *(undefined4 *)(param_1 + 0x18) = uVar3;
    uVar3 = *(undefined4 *)(param_1 + 0x18);
    initialize__7primWinFP7primTex(uVar3,*(undefined4 *)(param_1 + 0x44));
    setItem__7primWinFiii(uVar3,1,1,0);
    createPoly__7primWinFiiiiii(uVar3,0,0,0,0,0x200,0x1c0);
    setPolyRGBA__7primWinFiiiii(uVar3,0,0,0,0,0x40);
    buildWin__7primWinFiiiiii(uVar3,4,0,0,0,0,0);
    fadein__7primWinFi(uVar3,0x18);
    *(undefined4 *)(param_1 + 0x2c) = 1;
    break;
  case 1:
    lVar5 = isFade__7primWinFv(*(undefined4 *)(param_1 + 0x18));
    if (lVar5 == 0) {
      lVar5 = __nw__FUi(0x148);
      uVar3 = 0;
      if (lVar5 != 0) {
        uVar3 = __ct__7primWinFv(lVar5);
      }
      *(undefined4 *)(param_1 + 0x20) = uVar3;
      uVar3 = *(undefined4 *)(param_1 + 0x20);
      initialize__7primWinFP7primTex(uVar3,*(undefined4 *)(param_1 + 0x44));
      setItem__7primWinFiii(uVar3,0,0,0);
      buildWin__7primWinFiiiiii(uVar3,5,0x40,0xb0,0x180,0x60,6);
      uVar3 = addKeyWait__7primWinFv(uVar3);
      *(undefined4 *)(param_1 + 0x28) = uVar3;
      *(byte *)(*(int *)(param_1 + 0x28) + 0x12) = *(byte *)(*(int *)(param_1 + 0x28) + 0x12) & 0xfe
      ;
      lVar5 = __nw__FUi(0x148);
      uVar3 = 0;
      if (lVar5 != 0) {
        uVar3 = __ct__7primWinFv(lVar5);
      }
      *(undefined4 *)(param_1 + 0x1c) = uVar3;
      uVar3 = *(undefined4 *)(param_1 + 0x1c);
      initialize__7primWinFP7primTex(uVar3,*(undefined4 *)(param_1 + 0x44));
      setItem__7primWinFiii(uVar3,2,0,1);
      setTextArea__7primWinFiiib(uVar3,1,0x200,0x100,1);
      uVar4 = addMessage__7primWinFiiPcib(uVar3,0x48,0xb0,solomonMess_tutorial_J,1,1);
      *(undefined4 *)(param_1 + 0x24) = uVar4;
      buildWin__7primWinFiiiiii(uVar3,6,0,0,0,0,0);
      fadein__7primWinFi(uVar3,0x10);
      *(undefined4 *)(param_1 + 0x3c) = 1;
      *(undefined4 *)(param_1 + 0x2c) = 2;
    }
    break;
  case 2:
    lVar5 = isFade__7primWinFv(*(undefined4 *)(param_1 + 0x1c));
    if (lVar5 == 0) {
      if ((uVar1 & 0x2000) == 0) {
        if (*(ushort *)(*(int *)(param_1 + 0x24) + 0x76) <=
            *(ushort *)(*(int *)(param_1 + 0x24) + 0x80)) {
          *(byte *)(*(int *)(param_1 + 0x28) + 0x12) =
               *(byte *)(*(int *)(param_1 + 0x28) + 0x12) & 0xfe | 1;
        }
      }
      else if (*(ushort *)(*(int *)(param_1 + 0x24) + 0x80) <
               *(ushort *)(*(int *)(param_1 + 0x24) + 0x76)) {
        Finish__11MenuMessageFv(*(undefined4 *)(param_1 + 0x24));
      }
      else {
        if (*(int *)(param_1 + 0x28) != 0) {
          *(byte *)(*(int *)(param_1 + 0x28) + 0x12) =
               *(byte *)(*(int *)(param_1 + 0x28) + 0x12) & 0xfe;
        }
        if (*(int *)(param_1 + 0x3c) == 5) {
          *(undefined4 *)(param_1 + 0x2c) = 3;
          if (*(int *)(param_1 + 0x1c) != 0) {
            DelayDeleteRequest__7primWinFv(*(undefined4 *)(param_1 + 0x1c));
            *(undefined4 *)(param_1 + 0x1c) = 0;
          }
          if (*(int *)(param_1 + 0x20) != 0) {
            DelayDeleteRequest__7primWinFv(*(undefined4 *)(param_1 + 0x20));
            *(undefined4 *)(param_1 + 0x20) = 0;
          }
          lVar5 = __nw__FUi(0x148);
          uVar3 = 0;
          if (lVar5 != 0) {
            uVar3 = __ct__7primWinFv(lVar5);
          }
          *(undefined4 *)(param_1 + 0x20) = uVar3;
          uVar3 = *(undefined4 *)(param_1 + 0x20);
          initialize__7primWinFP7primTex(uVar3,*(undefined4 *)(param_1 + 0x44));
          setItem__7primWinFiii(uVar3,0,0,0);
          buildWin__7primWinFiiiiii(uVar3,5,0x40,0x77,0x180,0xd2,6);
          uVar3 = addKeyWait__7primWinFv(uVar3);
          *(undefined4 *)(param_1 + 0x28) = uVar3;
          *(byte *)(*(int *)(param_1 + 0x28) + 0x12) =
               *(byte *)(*(int *)(param_1 + 0x28) + 0x12) & 0xfe;
          lVar5 = __nw__FUi(0x148);
          uVar3 = 0;
          if (lVar5 != 0) {
            uVar3 = __ct__7primWinFv(lVar5);
          }
          *(undefined4 *)(param_1 + 0x1c) = uVar3;
          uVar3 = *(undefined4 *)(param_1 + 0x1c);
          initialize__7primWinFP7primTex(uVar3,*(undefined4 *)(param_1 + 0x44));
          setItem__7primWinFiii(uVar3,2,0,1);
          setTextArea__7primWinFiiib(uVar3,1,0x200,0x200,1);
          uVar4 = addMessage__7primWinFiiPcib(uVar3,0x48,0x77,PTR__5018_005547c4,1,1);
          *(undefined4 *)(param_1 + 0x24) = uVar4;
          Finish__11MenuMessageFv(*(undefined4 *)(param_1 + 0x24));
          buildWin__7primWinFiiiiii(uVar3,6,0,0,0,0,0);
          fadein__7primWinFi(uVar3,0x10);
        }
        else {
          if (*(int *)(param_1 + 0x1c) != 0) {
            DelayDeleteRequest__7primWinFv(*(undefined4 *)(param_1 + 0x1c));
            *(undefined4 *)(param_1 + 0x1c) = 0;
          }
          lVar5 = __nw__FUi(0x148);
          uVar3 = 0;
          if (lVar5 != 0) {
            uVar3 = __ct__7primWinFv(lVar5);
          }
          *(undefined4 *)(param_1 + 0x1c) = uVar3;
          uVar3 = *(undefined4 *)(param_1 + 0x1c);
          initialize__7primWinFP7primTex(uVar3,*(undefined4 *)(param_1 + 0x44));
          setItem__7primWinFiii(uVar3,2,0,1);
          setTextArea__7primWinFiiib(uVar3,1,0x200,0x100,1);
          uVar4 = addMessage__7primWinFiiPcib(uVar3,0x48,0xb0,
                                  (&solomonMess_tutorial_J)[*(int *)(param_1 + 0x3c)],1,1);
          *(undefined4 *)(param_1 + 0x24) = uVar4;
          buildWin__7primWinFiiiiii(uVar3,6,0,0,0,0,0);
          *(int *)(param_1 + 0x3c) = *(int *)(param_1 + 0x3c) + 1;
        }
      }
    }
    break;
  case 3:
    lVar5 = isFade__7primWinFv(*(undefined4 *)(param_1 + 0x1c));
    if ((lVar5 == 0) &&
       (*(byte *)(*(int *)(param_1 + 0x28) + 0x12) =
             *(byte *)(*(int *)(param_1 + 0x28) + 0x12) & 0xfe | 1, (uVar1 & 0x2000) != 0)) {
      *(undefined4 *)(param_1 + 0x2c) = 4;
      fadeout__7primWinFi(*(undefined4 *)(param_1 + 0x1c),0x10);
    }
    break;
  case 4:
    if (*(char *)(*(int *)(param_1 + 0x1c) + 0x102) != '\0') {
      if (*(int *)(param_1 + 0x1c) != 0) {
        DelayDeleteRequest__7primWinFv(*(undefined4 *)(param_1 + 0x1c));
        *(undefined4 *)(param_1 + 0x1c) = 0;
      }
      if (*(int *)(param_1 + 0x20) != 0) {
        DelayDeleteRequest__7primWinFv(*(undefined4 *)(param_1 + 0x20));
        *(undefined4 *)(param_1 + 0x20) = 0;
      }
      fadeout__7primWinFi(*(undefined4 *)(param_1 + 0x18),0x18);
      *(undefined4 *)(param_1 + 0x2c) = 5;
    }
    break;
  case 5:
    if (*(char *)(*(int *)(param_1 + 0x18) + 0x102) != '\0') {
      *(undefined1 *)(param_1 + 0x40) = 1;
    }
  }
  return 0;
}

/* JP: 0x005005c0  solomonTutorial::isFinish()   [isFinish__15solomonTutorialFv]  size=0x1c */
undefined1 isFinish__15solomonTutorialFv(int param_1)

{
  return *(undefined1 *)(param_1 + 0x40);
}
