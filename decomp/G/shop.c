/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: shop   functions: 39
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/shop.md).
 */

/* JP: 0x004ded30  shop::CMN(int, void*, CmdMenu*)   [CMN__4shopFiPvP7CmdMenu]  size=0x38 */
undefined4 CMN__4shopFiPvP7CmdMenu(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  m_MenuNum = param_1;
  m_pUserData = param_2;
  m_pTM = param_3;
  return 1;
}

/* JP: 0x004ded70  shop::DVD_CBFunc(int, BufMemory*, int, char*, void*)   [DVD_CBFunc__4shopFiP9BufMemoryiPcPv]  size=0xb8 */
undefined8
DVD_CBFunc__4shopFiP9BufMemoryiPcPv
          (undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5)

{
  undefined4 uVar1;
  long lVar2;
  
  m_pTex = *(undefined4 *)(param_2 + 4);
  m_TexRead = 1;
  mpData = param_2;
  m_type = param_1;
  m_size = param_3;
  m_filename = param_4;
  m_data = param_5;
  lVar2 = __nw__FUi(0x52c);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = __ct__7primTexFv(lVar2);
  }
  m_pPT = uVar1;
  initialize__7primTexFP9BufMemory(m_pPT,param_2);
  return 0;
}

/* JP: 0x004dee30  shop::shop()   [__ct__4shopFv]  size=0x114 */
int __ct__4shopFv(int param_1)

{
  __ct__7CPolObjFv(param_1);
  *(undefined4 *)(param_1 + 0x18) = 0;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  *(undefined1 **)(param_1 + 0x20) = &__vt__17DelayDeleteObject;
  *(undefined1 **)(param_1 + 0x14) = &__vt__4shop;
  *(undefined4 *)(param_1 + 0x20) = 0x409790;
  __ct__4FontFv(param_1 + 0x40);
  __ct__4FontFv(param_1 + 0x44);
  m_pPT = 0;
  *(undefined4 *)(param_1 + 0x50) = 0;
  *(undefined4 *)(param_1 + 0x54) = 0;
  *(undefined4 *)(param_1 + 0x58) = 0;
  *(undefined4 *)(param_1 + 100) = 0;
  *(undefined4 *)(param_1 + 0x68) = 0;
  *(undefined4 *)(param_1 + 0x6c) = 0;
  *(undefined4 *)(param_1 + 0x70) = 0;
  *(undefined4 *)(param_1 + 0x4c) = 0;
  *(undefined4 *)(param_1 + 0x100) = 0;
  *(undefined4 *)(param_1 + 0x8c) = 0;
  *(undefined4 *)(param_1 + 0x94) = 0;
  *(undefined4 *)(param_1 + 0x98) = 0;
  *(undefined4 *)(param_1 + 0x128) = 0;
  *(undefined4 *)(param_1 + 0x130) = 0;
  *(undefined4 *)(param_1 + 300) = 0;
  *(undefined4 *)(param_1 + 0x48) = 0;
  return param_1;
}

/* JP: 0x004def50  shop::~shop()   [__dt__4shopFv]  size=0x1bc */
int __dt__4shopFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 0x14) = &__vt__4shop;
    *(undefined4 *)(param_1 + 0x20) = 0x409790;
    *(undefined4 *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 700) = *(undefined4 *)(param_1 + 0x10c);
    SetCurrentCash__15SaveMenuSectionFi(*(undefined4 *)(param_1 + 0x104));
    if (*(int *)(param_1 + 0x100) != 0) {
      __dla__FPv(*(undefined4 *)(param_1 + 0x100));
      *(undefined4 *)(param_1 + 0x100) = 0;
    }
    if (*(int *)(param_1 + 0x130) != 0) {
      DelayDeleteRequest__11shopCaptureFv(*(undefined4 *)(param_1 + 0x130));
      *(undefined4 *)(param_1 + 0x130) = 0;
    }
    if (m_pPT != 0) {
      __dt__7primTexFv(m_pPT,1);
      m_pPT = 0;
    }
    Dispose__7CPollerFP7CPolObj(app__4CApp + 0x48,param_1);
    if (*(int *)(param_1 + 0x48) != 0) {
      DelayDeleteRequest__9primSoundFv(*(undefined4 *)(param_1 + 0x48));
      *(undefined4 *)(param_1 + 0x48) = 0;
    }
    __dt__4FontFv(param_1 + 0x44,0xffffffffffffffff);
    __dt__4FontFv(param_1 + 0x40,0xffffffffffffffff);
    if (param_1 != -0x18) {
      *(undefined1 **)(param_1 + 0x20) = &__vt__17DelayDeleteObject;
    }
    __dt__7CPolObjFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x004df110  shop::initialize(int, void(*)(int, void*)*, void*)   [initialize__4shopFiPFiPv_vPv]  size=0x128 */
void initialize__4shopFiPFiPv_vPv
               (int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined8 uVar2;
  long lVar3;
  undefined1 auStack_140 [256];
  int iStack_40;
  undefined4 uStack_30;
  undefined4 uStack_20;
  undefined4 uStack_10;
  
  iStack_40 = param_1;
  uStack_30 = param_2;
  uStack_20 = param_3;
  uStack_10 = param_4;
  uVar2 = SetPathname__7SysToolFPcPCc(auStack_140,0x55a6b0);
  ReadOrder__11DvdromOrderFPCcPFiP9BufMemoryiPcPv_iiPvi(Dvdromour__11DvdromOrder,uVar2,0x4ded70,0,iStack_40,0);
  Entry__7CPollerFP7CPolObjib(app__4CApp + 0x48,iStack_40,0x80,0);
  *(undefined4 *)(iStack_40 + 0x24) = uStack_20;
  *(undefined4 *)(iStack_40 + 0x28) = uStack_10;
  *(undefined1 *)(iStack_40 + 0x3c) = 0;
  m_TexRead = 0;
  *(undefined4 *)(iStack_40 + 0x30) = 0;
  *(undefined4 *)(iStack_40 + 0xb0) = uStack_30;
  *(uint *)(iStack_40 + 0x120) = ourBtlSaveDat__10BtlSaveSec + (uint)*(byte *)(ourBtlSaveDat__10BtlSaveSec + 2) * 0x200 + 0x944;
  lVar3 = __nw__FUi(0x30);
  uVar1 = 0;
  if (lVar3 != 0) {
    uVar1 = __ct__9primSoundFv(lVar3);
  }
  *(undefined4 *)(iStack_40 + 0x48) = uVar1;
  initialize__9primSoundFv(*(undefined4 *)(iStack_40 + 0x48));
  return;
}

/* JP: 0x004df240  shop::start()   [start__4shopFv]  size=0xe0 */
void start__4shopFv(int param_1)

{
  undefined4 uVar1;
  long lVar2;
  
  *(undefined1 *)(param_1 + 0x3c) = 1;
  lVar2 = __nw__FUi(0x280);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = __ct__11shopCaptureFi(lVar2,0xe);
  }
  *(undefined4 *)(param_1 + 0x130) = uVar1;
  startCapture__11shopCaptureFv(*(undefined4 *)(param_1 + 0x130));
  setDisp__11shopCaptureFiffff
            (0xbf000000,0xbf000000,0x3f800000,0x3f800000,*(undefined4 *)(param_1 + 0x130),0);
  fadein__8primFadeFi(*(int *)(param_1 + 0x130) + 0x20,0x10);
  setRGBA__11shopCaptureFiiii(*(undefined4 *)(param_1 + 0x130),0x40,0x40,0x40,0x80);
  return;
}

/* JP: 0x004df320  shop::mShopInit()   [mShopInit__4shopFv]  size=0xf8 */
void mShopInit__4shopFv(int param_1)

{
  long lVar1;
  
  *(int *)(param_1 + 0x11c) =
       (int)*(char *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) +
                      *(char *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x80) * 0x20 + 0x93);
  *(undefined4 *)(param_1 + 0x104) =
       *(undefined4 *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + (uint)*(byte *)(ourBtlSaveDat__10BtlSaveSec + 2) * 4 + 4);
  *(undefined4 *)(param_1 + 0x10c) = *(undefined4 *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 700);
  *(undefined4 *)(param_1 + 0xb8) = 0;
  do {
    lVar1 = mCalcPoint__4shopFb(param_1,1);
  } while (lVar1 != 0);
  return;
}

/* JP: 0x004df420  shop::Polling()   [Polling__4shopFv]  size=0x2068 */
undefined8 Polling__4shopFv(int param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  ushort uVar3;
  short sVar4;
  int iVar5;
  undefined4 uVar6;
  long lVar7;
  undefined8 uVar8;
  ushort uVar9;
  int iVar10;
  undefined1 *puVar11;
  undefined1 *puVar12;
  
  iVar5 = GetActive__4CPadFi(0);
  uVar3 = *(ushort *)(*(int *)(&m_pCoreArray__4CPad + *(int *)(iVar5 + 4) * 4) + 0x6c);
  uVar9 = *(ushort *)(*(int *)(&m_pCoreArray__4CPad + *(int *)(iVar5 + 4) * 4) + 0x70) & 0xf0 |
          uVar3;
  switch(*(undefined4 *)(param_1 + 0x30)) {
  case 0:
    mShopInit__4shopFv(param_1);
    *(undefined4 *)(param_1 + 0x30) = 1;
    break;
  case 1:
    if ((m_TexRead != '\0') && (*(char *)(param_1 + 0x3c) != '\0')) {
      *(undefined4 *)(param_1 + 0x30) = 2;
      *(undefined4 *)(param_1 + 0x38) = 0;
      (**(code **)(param_1 + 0x24))(*(undefined4 *)(param_1 + 0x38),*(undefined4 *)(param_1 + 0x28))
      ;
    }
    break;
  case 2:
    if (*(int *)(param_1 + 0x4c) == 0) {
      lVar7 = isFade__8primFadeFv(*(int *)(param_1 + 0x130) + 0x20);
      if (lVar7 == 0) {
        *(undefined4 *)(param_1 + 0x38) = 1;
        (**(code **)(param_1 + 0x24))
                  (*(undefined4 *)(param_1 + 0x38),*(undefined4 *)(param_1 + 0x28));
        changeLayer__11shopCaptureFi(*(undefined4 *)(param_1 + 0x130),0xb);
        *(undefined4 *)(param_1 + 0x84) = 0;
        mSetupBG__4shopFv(param_1);
        SetFFMode__3GsxFibi(0,1,1);
      }
    }
    else {
      lVar7 = isFade__7primWinFv(*(undefined4 *)(param_1 + 0x4c));
      if (lVar7 == 0) {
        *(undefined4 *)(param_1 + 0x30) = 3;
        mSetupMainCursor__4shopFb(param_1,1);
      }
    }
    break;
  case 3:
    if ((uVar3 & 0x2000) == 0) {
      if ((uVar3 & 0x4000) == 0) {
        iVar5 = *(int *)(param_1 + 0x84);
        uVar6 = menuCheckKey__7primWinFiP10primCursor(*(undefined4 *)(param_1 + 0x4c),uVar9,
                                *(undefined4 *)(param_1 + 0x8c));
        *(undefined4 *)(param_1 + 0x84) = uVar6;
        if (iVar5 != *(int *)(param_1 + 0x84)) {
          play__9primSoundFi(*(undefined4 *)(param_1 + 0x48),0);
        }
      }
      else {
        play__9primSoundFi(*(undefined4 *)(param_1 + 0x48),3);
        mReleaseMainCursor__4shopFv(param_1);
        fadeout__7primWinFi(*(undefined4 *)(param_1 + 0x4c),0x10);
        fadeout__7primWinFi(*(undefined4 *)(param_1 + 0x50),0x10);
        fadeout__8shopCashFv(*(undefined4 *)(param_1 + 0x128));
        fadeout__8primFadeFi(*(int *)(param_1 + 0x130) + 0x20,0x10);
        *(undefined4 *)(param_1 + 0x38) = 2;
        (**(code **)(param_1 + 0x24))
                  (*(undefined4 *)(param_1 + 0x38),*(undefined4 *)(param_1 + 0x28));
        *(undefined4 *)(param_1 + 0x30) = 0x1c;
      }
    }
    else {
      play__9primSoundFi(*(undefined4 *)(param_1 + 0x48),2);
      iVar5 = *(int *)(param_1 + 0x84);
      if (iVar5 == 3) {
        mReleaseMainCursor__4shopFv(param_1);
        fadeout__7primWinFi(*(undefined4 *)(param_1 + 0x4c),0x10);
        fadeout__7primWinFi(*(undefined4 *)(param_1 + 0x50),0x10);
        fadeout__8shopCashFv(*(undefined4 *)(param_1 + 0x128));
        fadeout__8primFadeFi(*(int *)(param_1 + 0x130) + 0x20,0x10);
        *(undefined4 *)(param_1 + 0x38) = 2;
        (**(code **)(param_1 + 0x24))
                  (*(undefined4 *)(param_1 + 0x38),*(undefined4 *)(param_1 + 0x28));
        *(undefined4 *)(param_1 + 0x30) = 0x1c;
      }
      else if (iVar5 == 2) {
        mReleaseMainCursor__4shopFv(param_1);
        fadeout__7primWinFi(*(undefined4 *)(param_1 + 0x4c),0x10);
        fadeout__7primWinFi(*(undefined4 *)(param_1 + 0x50),0x10);
        fadeout__8primFadeFi(*(int *)(param_1 + 0x130) + 0x20,0x10);
        fadeout__8shopCashFv(*(undefined4 *)(param_1 + 0x128));
        *(undefined4 *)(param_1 + 0x30) = 0x1a;
        lVar7 = __nw__FUi(0x17f8);
        uVar6 = 0;
        if (lVar7 != 0) {
          uVar6 = __ct__7CmdMenuFsPFiPvP7CmdMenu_iPv(lVar7,0x10,0x4ded30,param_1 + 0x2c);
        }
        *(undefined4 *)(param_1 + 0x124) = uVar6;
      }
      else if (iVar5 == 1) {
        mMakeSellList__4shopFv(param_1);
        if (*(int *)(param_1 + 0xa4) != 0) {
          mReleaseMainCursor__4shopFv(param_1);
          fadeout__7primWinFi(*(undefined4 *)(param_1 + 0x4c),0x10);
          *(undefined4 *)(param_1 + 0x30) = 5;
          *(undefined1 *)(param_1 + 0xc4) = 0;
        }
      }
      else if ((iVar5 == 0) && (mMakeBuyList__4shopFv(param_1), *(int *)(param_1 + 0xa4) != 0)) {
        mReleaseMainCursor__4shopFv(param_1);
        fadeout__7primWinFi(*(undefined4 *)(param_1 + 0x4c),0x10);
        *(undefined4 *)(param_1 + 0x30) = 5;
        *(undefined1 *)(param_1 + 0xc4) = 1;
      }
    }
    break;
  case 5:
    if (*(int *)(param_1 + 0x58) == 0) {
      if (*(int *)(param_1 + 0x54) == 0) {
        mSetupBuySellWin__4shopFv(param_1);
      }
      else if (*(char *)(*(int *)(param_1 + 0x54) + 0x102) != '\0') {
        mReleaseMainMenuWin__4shopFv(param_1);
      }
    }
    else {
      lVar7 = isFade__7primWinFv(*(undefined4 *)(param_1 + 0x58));
      if (lVar7 == 0) {
        *(undefined4 *)(param_1 + 0x30) = 6;
        mSetupMainCursor__4shopFb(param_1,0);
        lVar7 = __nw__FUi(0x2c);
        uVar6 = 0;
        if (lVar7 != 0) {
          uVar6 = __ct__14shopScrollMarkFv(lVar7);
        }
        *(undefined4 *)(param_1 + 0x94) = uVar6;
        mCalcCurrentMax__4shopFv(param_1);
        initialize__14shopScrollMarkFP7primTexiii
                  (*(undefined4 *)(param_1 + 0x94),m_pPT,*(undefined4 *)(param_1 + 0x9c),
                   *(undefined4 *)
                    (*(int *)(param_1 + 0x100) + *(int *)(param_1 + 0x84) * 0x1c + 0xc),
                   *(undefined4 *)(param_1 + 0x110));
        setItem__10primCursorFP7primWini(*(undefined4 *)(param_1 + 0x8c),*(undefined4 *)(param_1 + 0x78),
                        *(undefined4 *)(param_1 + 0x84));
        qMove__10primCursorFv(*(undefined4 *)(param_1 + 0x8c));
        initScroll__7primWinFii(*(undefined4 *)(param_1 + 0x78),0,
                        *(int *)(param_1 + 0x84) - *(int *)(param_1 + 0x9c));
      }
    }
    break;
  case 6:
    if ((uVar3 & 0x2000) == 0) {
      if ((uVar3 & 0x4000) == 0) {
        mCheckSelector__4shopFi(param_1,uVar9);
      }
      else {
        play__9primSoundFi(*(undefined4 *)(param_1 + 0x48),3);
        mReleaseMainCursor__4shopFv(param_1);
        if (*(int *)(param_1 + 0x94) != 0) {
          iVar5 = *(int *)(param_1 + 0x94);
          if (iVar5 != 0) {
            (**(code **)(*(int *)(iVar5 + 0x14) + 8))(iVar5,1);
          }
          *(undefined4 *)(param_1 + 0x94) = 0;
        }
        fadeout__7primWinFi(*(undefined4 *)(param_1 + 0x58),0x10);
        fadeout__7primWinFi(*(undefined4 *)(param_1 + 0x7c),0x10);
        fadeout__7primWinFi(*(undefined4 *)(param_1 + 0x78),0x10);
        *(undefined4 *)(param_1 + 0x30) = 7;
      }
    }
    else if (*(int *)(*(int *)(param_1 + 0x100) + *(int *)(param_1 + 0x84) * 0x1c) == -1) {
      play__9primSoundFi(*(undefined4 *)(param_1 + 0x48),4);
      *(undefined4 *)(param_1 + 0x88) = *(undefined4 *)(param_1 + 0x84);
      mReleaseMainCursor__4shopFv(param_1);
      if (*(int *)(param_1 + 0x94) != 0) {
        iVar5 = *(int *)(param_1 + 0x94);
        if (iVar5 != 0) {
          (**(code **)(*(int *)(iVar5 + 0x14) + 8))(iVar5,1);
        }
        *(undefined4 *)(param_1 + 0x94) = 0;
      }
      SetMark__10ScrollMarkFUc(*(undefined4 *)(*(int *)(param_1 + 0x78) + 0x80),0);
      mSetupWarningWin__4shopFv(param_1);
      *(undefined4 *)(param_1 + 0x30) = 0x17;
    }
    else if (*(int *)(param_1 + 0x108) == 0) {
      play__9primSoundFi(*(undefined4 *)(param_1 + 0x48),4);
    }
    else {
      play__9primSoundFi(*(undefined4 *)(param_1 + 0x48),2);
      *(undefined4 *)(param_1 + 0x88) = *(undefined4 *)(param_1 + 0x84);
      mReleaseMainCursor__4shopFv(param_1);
      if (*(int *)(param_1 + 0x94) != 0) {
        iVar5 = *(int *)(param_1 + 0x94);
        if (iVar5 != 0) {
          (**(code **)(*(int *)(iVar5 + 0x14) + 8))(iVar5,1);
        }
        *(undefined4 *)(param_1 + 0x94) = 0;
      }
      SetMark__10ScrollMarkFUc(*(undefined4 *)(*(int *)(param_1 + 0x78) + 0x80),0);
      setTextAlpha__7primWinFii(*(undefined4 *)(param_1 + 0x7c),6,0);
      mSetupBuyQueryWin__4shopFv(param_1);
      *(undefined4 *)(param_1 + 0x30) = 8;
    }
    break;
  case 7:
    if (*(int *)(param_1 + 0x58) == 0) {
      if (*(char *)(param_1 + 0xc4) == '\0') {
        *(undefined4 *)(param_1 + 0x84) = 1;
      }
      else {
        *(undefined4 *)(param_1 + 0x84) = 0;
      }
      mSetupMainMenuWin__4shopFv(param_1);
      *(undefined4 *)(param_1 + 0x30) = 2;
    }
    else if (*(char *)(*(int *)(param_1 + 0x58) + 0x102) != '\0') {
      mReleaseBuySellWin__4shopFv(param_1);
    }
    break;
  case 8:
    lVar7 = isFade__7primWinFv(*(undefined4 *)(param_1 + 0x4c));
    if (lVar7 != 0) {
      mSetupMainCursor__4shopFb(param_1,1);
      *(undefined4 *)(param_1 + 0x30) = 9;
    }
    break;
  case 9:
    if (((uVar3 & 0x2000) == 0) || (*(int *)(param_1 + 0x84) != 0)) {
      if (((uVar3 & 0x2000) == 0) || (*(int *)(param_1 + 0x84) != 1)) {
        if ((uVar3 & 0x6000) == 0) {
          iVar5 = *(int *)(param_1 + 0x84);
          uVar6 = menuCheckKey__7primWinFiP10primCursor(*(undefined4 *)(param_1 + 0x4c),uVar9,
                                  *(undefined4 *)(param_1 + 0x8c));
          *(undefined4 *)(param_1 + 0x84) = uVar6;
          if (iVar5 != *(int *)(param_1 + 0x84)) {
            play__9primSoundFi(*(undefined4 *)(param_1 + 0x48),0);
          }
        }
        else {
          if ((uVar3 & 0x2000) == 0) {
            play__9primSoundFi(*(undefined4 *)(param_1 + 0x48),3);
          }
          else {
            play__9primSoundFi(*(undefined4 *)(param_1 + 0x48),2);
          }
          mReleaseMainCursor__4shopFv(param_1);
          setTextAlpha__7primWinFii(*(undefined4 *)(param_1 + 0x7c),6,0x80);
          fadeout__7primWinFi(*(undefined4 *)(param_1 + 100),0x10);
          fadeout__7primWinFi(*(undefined4 *)(param_1 + 0x6c),0x10);
          *(undefined4 *)(param_1 + 0x30) = 10;
          *(undefined4 *)(param_1 + 0x34) = 5;
        }
      }
      else {
        play__9primSoundFi(*(undefined4 *)(param_1 + 0x48),2);
        *(undefined4 *)(param_1 + 0x30) = 10;
        *(undefined4 *)(param_1 + 0x34) = 0x14;
        mReleaseMainCursor__4shopFv(param_1);
        fadeout__7primWinFi(*(undefined4 *)(param_1 + 0x6c),0x10);
        fadeout__7primWinFi(*(undefined4 *)(param_1 + 100),0x10);
        *(undefined1 *)(param_1 + 0xc5) = 0;
      }
    }
    else {
      play__9primSoundFi(*(undefined4 *)(param_1 + 0x48),2);
      *(undefined4 *)(param_1 + 0x30) = 10;
      *(undefined4 *)(param_1 + 0x34) = 0xb;
      mReleaseMainCursor__4shopFv(param_1);
      fadeout__7primWinFi(*(undefined4 *)(param_1 + 0x6c),0x10);
      fadeout__7primWinFi(*(undefined4 *)(param_1 + 100),0x10);
      *(undefined1 *)(param_1 + 0xc5) = 1;
    }
    break;
  case 10:
    if (*(char *)(*(int *)(param_1 + 100) + 0x102) != '\0') {
      mReleaseBuyQueryWin__4shopFv(param_1);
      *(undefined4 *)(param_1 + 0x30) = *(undefined4 *)(param_1 + 0x34);
      *(undefined4 *)(param_1 + 0x84) = *(undefined4 *)(param_1 + 0x88);
    }
    break;
  case 0xb:
    if (*(int *)(param_1 + 100) == 0) {
      mSetupBuySelectDiscWin__4shopFv(param_1);
    }
    else {
      lVar7 = isFade__7primWinFv(*(undefined4 *)(param_1 + 100));
      if (lVar7 == 0) {
        mSetupMainCursor__4shopFb(param_1,1);
        *(undefined4 *)(param_1 + 0x30) = 0xc;
      }
    }
    break;
  case 0xc:
    if ((uVar3 & 0x2000) == 0) {
      if ((uVar3 & 0x4000) == 0) {
        iVar5 = *(int *)(param_1 + 0x84);
        uVar6 = menuCheckKey__7primWinFiP10primCursor(*(undefined4 *)(param_1 + 0x4c),uVar9,
                                *(undefined4 *)(param_1 + 0x8c));
        *(undefined4 *)(param_1 + 0x84) = uVar6;
        if (iVar5 != *(int *)(param_1 + 0x84)) {
          play__9primSoundFi(*(undefined4 *)(param_1 + 0x48),0);
        }
      }
      else {
        play__9primSoundFi(*(undefined4 *)(param_1 + 0x48),3);
        *(undefined4 *)(param_1 + 0x30) = 0xd;
        *(undefined4 *)(param_1 + 0x34) = 8;
        fadeout__7primWinFi(*(undefined4 *)(param_1 + 0x6c),0x10);
        fadeout__7primWinFi(*(undefined4 *)(param_1 + 100),0x10);
        mReleaseMainCursor__4shopFv(param_1);
      }
    }
    else {
      play__9primSoundFi(*(undefined4 *)(param_1 + 0x48),2);
      *(int *)(param_1 + 0xc0) = *(int *)(param_1 + 0xb8) - *(int *)(param_1 + 0x84);
      *(undefined4 *)(param_1 + 0x30) = 0xd;
      *(undefined4 *)(param_1 + 0x34) = 0xe;
      fadeout__7primWinFi(*(undefined4 *)(param_1 + 0x6c),0x10);
      fadeout__7primWinFi(*(undefined4 *)(param_1 + 100),0x10);
      mReleaseMainCursor__4shopFv(param_1);
    }
    break;
  case 0xd:
    if (*(char *)(*(int *)(param_1 + 100) + 0x102) != '\0') {
      mReleaseBuySelectDiscWin__4shopFv(param_1);
      *(undefined4 *)(param_1 + 0x30) = *(undefined4 *)(param_1 + 0x34);
      if (*(int *)(param_1 + 0x30) == 8) {
        mSetupBuyQueryWin__4shopFv(param_1);
      }
    }
    break;
  case 0xe:
    if (*(int *)(param_1 + 0x68) == 0) {
      mSetupBuyDispDiscWin__4shopFv(param_1);
    }
    else {
      lVar7 = isFade__7primWinFv(*(undefined4 *)(param_1 + 0x68));
      if (lVar7 == 0) {
        *(undefined4 *)(param_1 + 0x30) = 0xf;
      }
    }
    break;
  case 0xf:
    if ((uVar3 & 0x6000) == 0) {
      mCheckEndMessage__4shopFv(param_1);
    }
    else if (*(ushort *)(*(int *)(param_1 + 0x74) + 0x80) <
             *(ushort *)(*(int *)(param_1 + 0x74) + 0x76)) {
      Finish__11MenuMessageFv(*(undefined4 *)(param_1 + 0x74));
    }
    else {
      *(undefined4 *)(param_1 + 0x30) = 0x10;
      *(undefined4 *)(param_1 + 0x34) = 0x11;
      fadeout__7primWinFi(*(undefined4 *)(param_1 + 0x68),0x10);
      *(byte *)(*(int *)(param_1 + 0x80) + 0x12) = *(byte *)(*(int *)(param_1 + 0x80) + 0x12) & 0xfe
      ;
      *(undefined4 *)(param_1 + 0x80) = 0;
    }
    break;
  case 0x10:
    if (*(char *)(*(int *)(param_1 + 0x68) + 0x102) != '\0') {
      mReleaseBuyDispDiscWin__4shopFv(param_1);
      *(undefined4 *)(param_1 + 0x30) = *(undefined4 *)(param_1 + 0x34);
    }
    break;
  case 0x11:
    if (*(int *)(param_1 + 300) == 0) {
      for (iVar10 = 0; iVar10 < *(int *)(param_1 + 0x11c); iVar10 = iVar10 + 1) {
        setPolyAlpha__7primWinFii(*(undefined4 *)(param_1 + 0x58),iVar10 << 1,0);
        setPolyAlpha__7primWinFii(*(undefined4 *)(param_1 + 0x58),iVar10 * 2 + 1,0);
        setTextAlpha__7primWinFii(*(undefined4 *)(param_1 + 0x58),iVar10,0);
        setTextAlpha__7primWinFii(*(undefined4 *)(param_1 + 0x7c),iVar10 * 4 + 8,0);
        setTextAlpha__7primWinFii(*(undefined4 *)(param_1 + 0x7c),iVar10 * 4 + 9,0);
        setTextAlpha__7primWinFii(*(undefined4 *)(param_1 + 0x7c),iVar10 * 4 + 10,0);
        setTextAlpha__7primWinFii(*(undefined4 *)(param_1 + 0x7c),iVar10 * 4 + 0xb,0);
      }
      lVar7 = __nw__FUi(0x5d0);
      uVar6 = 0;
      if (lVar7 != 0) {
        uVar6 = __ct__5JRingFsi(lVar7,0,0xc);
      }
      *(undefined4 *)(param_1 + 300) = uVar6;
      SetPad__5JRingFP4CPad(iVar5);
      AutoLoadSet__5JRingFv(*(undefined4 *)(param_1 + 300));
    }
    else {
      lVar7 = AutoLoadEndCheck__5JRingFv(*(undefined4 *)(param_1 + 300));
      if (lVar7 != 0) {
        iVar5 = rand();
        iVar10 = (iVar5 % 5) * 8;
        iVar5 = (*(int *)(param_1 + 0xc0) + 1) * -5 + 0x1e;
        SetRingPos__5JRingFff(0x43800000,0x43900000,*(undefined4 *)(param_1 + 300));
        SetRotSpeed__5JRingFfff(1.6 - (float)*(int *)(param_1 + 0xc0) * 0.1,0,0x3f800000,
                        *(undefined4 *)(param_1 + 300));
        sVar4 = (short)iVar5;
        AddStepArea__5JRingFssP7_rgba32s(*(undefined4 *)(param_1 + 300),*(short *)(&shopJRingTbl + iVar10) - sVar4,
                        (int)((float)iVar5 * 2.5),0,0);
        AddStepArea__5JRingFssP7_rgba32s(*(undefined4 *)(param_1 + 300),*(short *)(&DAT_0055a622 + iVar10) - sVar4,
                        (int)((float)iVar5 * 2.5),0,0);
        AddStepArea__5JRingFssP7_rgba32s(*(undefined4 *)(param_1 + 300),*(short *)(&DAT_0055a624 + iVar10) - sVar4,
                        (int)((float)iVar5 * 2.5),0,0);
        SetMode__5JRingFsssss(*(undefined4 *)(param_1 + 300),5,1,1,3,3);
        RingActive__5JRingFv(*(undefined4 *)(param_1 + 300));
        *(undefined4 *)(param_1 + 0x30) = 0x12;
      }
    }
    break;
  case 0x12:
    lVar7 = RingSleepCheck__5JRingFv(*(undefined4 *)(param_1 + 300));
    if (lVar7 != 0) {
      iVar5 = *(int *)(param_1 + 300);
      *(undefined2 *)(param_1 + 200) = *(undefined2 *)(iVar5 + 0x510);
      *(undefined2 *)(param_1 + 0xca) = *(undefined2 *)(iVar5 + 0x512);
      *(undefined2 *)(param_1 + 0xcc) = *(undefined2 *)(iVar5 + 0x514);
      *(undefined2 *)(param_1 + 0xce) = *(undefined2 *)(iVar5 + 0x516);
      *(undefined4 *)(param_1 + 0xd0) = *(undefined4 *)(iVar5 + 0x518);
      *(undefined4 *)(param_1 + 0xd4) = *(undefined4 *)(iVar5 + 0x51c);
      *(undefined4 *)(param_1 + 0xd8) = *(undefined4 *)(iVar5 + 0x520);
      *(undefined4 *)(param_1 + 0xdc) = *(undefined4 *)(iVar5 + 0x524);
      puVar11 = (undefined1 *)(iVar5 + 0x528);
      puVar12 = (undefined1 *)(param_1 + 0xe0);
      iVar5 = 0x10;
      do {
        uVar1 = *puVar11;
        uVar2 = puVar11[1];
        puVar11 = puVar11 + 2;
        iVar5 = iVar5 + -1;
        *puVar12 = uVar1;
        puVar12[1] = uVar2;
        puVar12 = puVar12 + 2;
      } while (0 < iVar5);
      Destruct__5JRingFb(*(undefined4 *)(param_1 + 300),0);
      *(undefined4 *)(param_1 + 300) = 0;
      *(undefined4 *)(param_1 + 0x30) = 0x13;
    }
    break;
  case 0x13:
    iVar5 = *(int *)(sm_pSubstance__15SaveMenuSection + 0xc);
    *(int *)(iVar5 + 0x2cc) = *(int *)(iVar5 + 0x2cc) + 1;
    if (1 < ((ulong)*(byte *)(param_1 + 0xca) & 7) >> 1) {
      *(int *)(iVar5 + 0x2d0) = *(int *)(iVar5 + 0x2d0) + 1;
    }
    for (iVar5 = 0; iVar5 < *(int *)(param_1 + 0x11c); iVar5 = iVar5 + 1) {
      setPolyAlpha__7primWinFii(*(undefined4 *)(param_1 + 0x58),iVar5 << 1,0x80);
      setPolyAlpha__7primWinFii(*(undefined4 *)(param_1 + 0x58),iVar5 * 2 + 1,0x80);
      setTextAlpha__7primWinFii(*(undefined4 *)(param_1 + 0x7c),iVar5 * 4 + 8,0x80);
      setTextAlpha__7primWinFii(*(undefined4 *)(param_1 + 0x7c),iVar5 * 4 + 9,0x80);
      setTextAlpha__7primWinFii(*(undefined4 *)(param_1 + 0x7c),iVar5 * 4 + 10,0x80);
      setTextAlpha__7primWinFii(*(undefined4 *)(param_1 + 0x7c),iVar5 * 4 + 0xb,0x80);
    }
    *(undefined4 *)(param_1 + 0x30) = 0x14;
    break;
  case 0x14:
    if (*(int *)(param_1 + 0x68) == 0) {
      mSetupBuyResultWin__4shopFv(param_1);
    }
    else {
      lVar7 = isFade__7primWinFv(*(undefined4 *)(param_1 + 0x68));
      if (lVar7 == 0) {
        *(undefined4 *)(param_1 + 0x30) = 0x15;
      }
    }
    break;
  case 0x15:
    if ((uVar3 & 0x6000) == 0) {
      mCheckEndMessage__4shopFv(param_1);
    }
    else if (*(ushort *)(*(int *)(param_1 + 0x74) + 0x80) <
             *(ushort *)(*(int *)(param_1 + 0x74) + 0x76)) {
      Finish__11MenuMessageFv(*(undefined4 *)(param_1 + 0x74));
    }
    else {
      play__9primSoundFi(*(undefined4 *)(param_1 + 0x48),2);
      fadeout__7primWinFi(*(undefined4 *)(param_1 + 0x68),0x10);
      fadeout__7primWinFi(*(undefined4 *)(param_1 + 0x58),0x10);
      fadeout__7primWinFi(*(undefined4 *)(param_1 + 0x7c),0x10);
      uVar8 = fadeout__7primWinFi(*(undefined4 *)(param_1 + 0x6c),0x10);
      fadeout__7primWinFi(*(undefined4 *)(param_1 + 0x78),0x10,uVar8);
      *(undefined4 *)(param_1 + 0x30) = 0x16;
      *(byte *)(*(int *)(param_1 + 0x80) + 0x12) = *(byte *)(*(int *)(param_1 + 0x80) + 0x12) & 0xfe
      ;
      *(undefined4 *)(param_1 + 0x80) = 0;
    }
    break;
  case 0x16:
    if (*(char *)(*(int *)(param_1 + 0x68) + 0x102) != '\0') {
      uVar8 = mReleaseBuyResultWin__4shopFv(param_1);
      mReleaseBuySellWin__4shopFv(param_1,uVar8);
      *(undefined4 *)(param_1 + 0x84) = 0;
      if (*(char *)(param_1 + 0xc4) == '\0') {
        mMakeSellList__4shopFv(param_1);
      }
      else {
        mMakeBuyList__4shopFv(param_1);
      }
      if (*(int *)(param_1 + 0xa4) == 0) {
        if (*(char *)(param_1 + 0xc4) == '\0') {
          *(undefined4 *)(param_1 + 0x84) = 1;
        }
        else {
          *(undefined4 *)(param_1 + 0x84) = 0;
        }
        mSetupMainMenuWin__4shopFv(param_1);
        *(undefined4 *)(param_1 + 0x30) = 2;
      }
      else {
        *(undefined4 *)(param_1 + 0x30) = 5;
      }
    }
    break;
  case 0x17:
    lVar7 = isFade__7primWinFv(*(undefined4 *)(param_1 + 0x4c));
    if (lVar7 != 0) {
      *(undefined4 *)(param_1 + 0x30) = 0x18;
    }
    break;
  case 0x18:
    if ((uVar3 & 0x6000) == 0) {
      mCheckEndMessage__4shopFv(param_1);
    }
    else if (*(ushort *)(*(int *)(param_1 + 0x74) + 0x80) <
             *(ushort *)(*(int *)(param_1 + 0x74) + 0x76)) {
      Finish__11MenuMessageFv(*(undefined4 *)(param_1 + 0x74));
    }
    else {
      mReleaseMainCursor__4shopFv(param_1);
      fadeout__7primWinFi(*(undefined4 *)(param_1 + 0x68),0x10);
      *(undefined4 *)(param_1 + 0x30) = 0x19;
      *(undefined4 *)(param_1 + 0x34) = 5;
      *(byte *)(*(int *)(param_1 + 0x80) + 0x12) = *(byte *)(*(int *)(param_1 + 0x80) + 0x12) & 0xfe
      ;
      *(undefined4 *)(param_1 + 0x80) = 0;
    }
    break;
  case 0x19:
    if (*(char *)(*(int *)(param_1 + 0x68) + 0x102) != '\0') {
      mReleaseWarningWin__4shopFv(param_1);
      *(undefined4 *)(param_1 + 0x30) = *(undefined4 *)(param_1 + 0x34);
      *(undefined4 *)(param_1 + 0x84) = *(undefined4 *)(param_1 + 0x88);
    }
    break;
  case 0x1a:
    if (*(char *)(*(int *)(param_1 + 0x4c) + 0x102) != '\0') {
      *(undefined4 *)(param_1 + 0x30) = 0x1b;
      *(undefined1 *)(*(int *)(param_1 + 0x124) + 0x3d) = 0x11;
    }
    break;
  case 0x1b:
    if (m_MenuNum == 2) {
      fadein__8primFadeFi(*(int *)(param_1 + 0x130) + 0x20,0x10);
      fadein__8shopCashFv(*(undefined4 *)(param_1 + 0x128));
      fadein__7primWinFi(*(undefined4 *)(param_1 + 0x4c),0x10);
      fadein__7primWinFi(*(undefined4 *)(param_1 + 0x50),0x10);
      *(undefined4 *)(param_1 + 0x30) = 2;
    }
    break;
  case 0x1c:
    if (*(char *)(*(int *)(param_1 + 0x4c) + 0x102) != '\0') {
      uVar8 = mReleaseMainMenuWin__4shopFv(param_1);
      mReleaseBG__4shopFv(param_1,uVar8);
      *(undefined4 *)(param_1 + 0x38) = 3;
      (**(code **)(param_1 + 0x24))(*(undefined4 *)(param_1 + 0x38),*(undefined4 *)(param_1 + 0x28))
      ;
      (**(code **)(*(int *)(param_1 + 0x20) + 0xc))();
      *(undefined4 *)(param_1 + 0x30) = 0x1d;
    }
  }
  return 0;
}

/* JP: 0x004e1490  shop::mSetupBG()   [mSetupBG__4shopFv]  size=0x2f8 */
void mSetupBG__4shopFv(int param_1)

{
  undefined4 uVar1;
  undefined8 uVar2;
  long lVar3;
  
  uVar1 = m_pTex;
  uVar2 = GetFileEntry(m_pTex,0x1a);
  (*(code *)&CreateFont__4FontFiPUc)(3,uVar2);
  uVar2 = GetFileEntry(uVar1,0x1b);
  (*(code *)&CreateFont__4FontFiPUc)(2,uVar2);
  lVar3 = __nw__FUi(0x148);
  uVar1 = 0;
  if (lVar3 != 0) {
    uVar1 = __ct__7primWinFv(lVar3);
  }
  *(undefined4 *)(param_1 + 0x50) = uVar1;
  uVar1 = *(undefined4 *)(param_1 + 0x50);
  initialize__7primWinFP7primTex(uVar1,m_pPT);
  setItem__7primWinFiii(uVar1,3,2,1);
  setTex__7primWinFiiii(uVar1,6,0,0,0);
  setTex__7primWinFiiii(uVar1,1,1,0,0);
  createTexPoly__7primWinFiiiiii(uVar1,0,1,0xffffffffffffffc8,0x10,0,0);
  setPolyFadeScroll__7primWinFiii(uVar1,0,1,4);
  createPoly__7primWinFiiiiii(uVar1,1,1,0,0x1a0,0x200,0x20);
  setPolyRGBA__7primWinFiiiii(uVar1,1,0,0,0,0x30);
  setTextArea__7primWinFiiib(uVar1,2,0x100,0x20,1);
  createText__7primWinFiiiiPciib(uVar1,0,2,0,0x18,shopMess_title_J,0,3);
  setTextFadeScroll__7primWinFiii(uVar1,0,1,4);
  buildWin__7primWinFiiiiii(uVar1,0,0,0,0,0,0);
  fadein__7primWinFi(*(undefined4 *)(param_1 + 0x50),0x10);
  lVar3 = __nw__FUi(0x18);
  uVar1 = 0;
  if (lVar3 != 0) {
    uVar1 = __ct__8shopCashFv(lVar3);
  }
  *(undefined4 *)(param_1 + 0x128) = uVar1;
  initialize__8shopCashFP7primTex(*(undefined4 *)(param_1 + 0x128),m_pPT);
  setCash__8shopCashFi(*(undefined4 *)(param_1 + 0x128),*(undefined4 *)(param_1 + 0x104));
  fadein__8shopCashFv(*(undefined4 *)(param_1 + 0x128));
  mSetupMainMenuWin__4shopFv(param_1);
  return;
}

/* JP: 0x004e1790  shop::mReleaseBG()   [mReleaseBG__4shopFv]  size=0xb0 */
void mReleaseBG__4shopFv(int param_1)

{
  if (*(int *)(param_1 + 0x128) != 0) {
    __dt__8shopCashFv(*(undefined4 *)(param_1 + 0x128),1);
    *(undefined4 *)(param_1 + 0x128) = 0;
  }
  if (*(int *)(param_1 + 0x50) != 0) {
    DelayDeleteRequest__7primWinFv(*(undefined4 *)(param_1 + 0x50));
    *(undefined4 *)(param_1 + 0x50) = 0;
  }
  (*(code *)&ClearFont__4FontFi)(3);
  (*(code *)&ClearFont__4FontFi)(2);
  return;
}

/* JP: 0x004e1840  shop::mSetupMainMenuWin()   [mSetupMainMenuWin__4shopFv]  size=0x3ac */
void mSetupMainMenuWin__4shopFv(int param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  long lVar3;
  int iVar4;
  undefined8 uVar5;
  
  uVar5 = 9;
  lVar3 = __nw__FUi(0x148);
  uVar1 = 0;
  if (lVar3 != 0) {
    uVar1 = __ct__7primWinFv(lVar3);
  }
  *(undefined4 *)(param_1 + 0x54) = uVar1;
  uVar1 = *(undefined4 *)(param_1 + 0x54);
  initialize__7primWinFP7primTex(uVar1,m_pPT);
  setItem__7primWinFiii(uVar1,3,0,6);
  setTextArea__7primWinFiiib(uVar1,2,0x280,0x200,1);
  for (iVar4 = 0; iVar4 < 4; iVar4 = iVar4 + 1) {
    createText__7primWinFiiiiPciib(uVar1,iVar4,2,0xbe,iVar4 * 0x1a + 0x78,(&shopMess_mainMenu_J)[iVar4],0,0);
  }
  createText__7primWinFiiiiPciib(uVar1,4,2,0x60,0x4c,(&shopMess_shopName_J)[*(int *)(param_1 + 0xb0) * 2],0,1);
  createText__7primWinFiiiiPciib(uVar1,5,2,0x60,0x62,(&shopMess_shopName_J)[*(int *)(param_1 + 0xb0) * 2 + 1],0,3);
  lVar3 = mCheckSellItem__4shopFv(param_1);
  if (lVar3 != 0) {
    uVar5 = 0xb;
  }
  setMenuWindow__7primWinFiiiii(uVar1,4,*(undefined4 *)(param_1 + 0x84),0,0xffffffffffffffff,uVar5);
  buildWin__7primWinFiiiiii(uVar1,1,0,0,0,0,0);
  fadein__7primWinFi(*(undefined4 *)(param_1 + 0x54),0x10);
  *(undefined4 *)(param_1 + 0x4c) = uVar1;
  lVar3 = __nw__FUi(0x148);
  uVar1 = 0;
  if (lVar3 != 0) {
    uVar1 = __ct__7primWinFv(lVar3);
  }
  *(undefined4 *)(param_1 + 0x6c) = uVar1;
  uVar1 = *(undefined4 *)(param_1 + 0x6c);
  initialize__7primWinFP7primTex(uVar1,m_pPT);
  setItem__7primWinFiii(uVar1,1,0,1);
  setTextArea__7primWinFiiib(uVar1,0,0x280,0x40,0);
  createText__7primWinFiiiiPciib(uVar1,0,0,0x66,0,
                  *(undefined4 *)(&gp0xffff81c8 + (uint)(*(int *)(param_1 + 0xb8) == 4) * 4),0x40,1)
  ;
  uVar2 = addMessage__7primWinFiiPcib(uVar1,0xc,0x1c,(&shopMess_mainMenuPopup_J)[*(int *)(param_1 + 0xb8)],0,1);
  *(undefined4 *)(param_1 + 0x74) = uVar2;
  buildWin__7primWinFiiiiii(uVar1,2,0x60,0x110,0x140,0x50,6);
  fadein__7primWinFi(uVar1,0x10);
  return;
}

/* JP: 0x004e1bf0  shop::mReleaseMainMenuWin()   [mReleaseMainMenuWin__4shopFv]  size=0x70 */
void mReleaseMainMenuWin__4shopFv(int param_1)

{
  if (*(int *)(param_1 + 0x6c) != 0) {
    DelayDeleteRequest__7primWinFv(*(undefined4 *)(param_1 + 0x6c));
    *(undefined4 *)(param_1 + 0x6c) = 0;
  }
  if (*(int *)(param_1 + 0x54) != 0) {
    DelayDeleteRequest__7primWinFv(*(undefined4 *)(param_1 + 0x54));
    *(undefined4 *)(param_1 + 0x54) = 0;
  }
  return;
}

/* JP: 0x004e1c60  shop::mSetupBuySellWin()   [mSetupBuySellWin__4shopFv]  size=0x1a5c */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void mSetupBuySellWin__4shopFv(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined8 uVar4;
  ulong uVar5;
  int iVar6;
  int *piVar7;
  int aiStack_200 [21];
  undefined4 uStack_1ac;
  undefined4 uStack_1a8;
  undefined4 uStack_1a4;
  undefined1 auStack_1a0 [260];
  int iStack_9c;
  int iStack_98;
  int iStack_94;
  int iStack_90;
  int iStack_8c;
  int iStack_88;
  int iStack_84;
  int iStack_80;
  int iStack_7c;
  int iStack_78;
  int iStack_74;
  int iStack_70;
  int iStack_6c;
  int iStack_68;
  int iStack_64;
  int iStack_60;
  int iStack_5c;
  int iStack_58;
  int iStack_54;
  int iStack_50;
  int iStack_4c;
  int iStack_48;
  int iStack_44;
  int iStack_40;
  int iStack_3c;
  int iStack_38;
  int iStack_34;
  int iStack_30;
  int iStack_2c;
  int iStack_28;
  int iStack_24;
  int iStack_20;
  int iStack_1c;
  int iStack_18;
  int iStack_14;
  int iStack_10;
  
  *(undefined4 *)(param_1 + 0x84) = 0;
  *(undefined4 *)(param_1 + 0x9c) = 0;
  *(undefined4 *)(param_1 + 0xa0) = 0;
  *(undefined4 *)(param_1 + 0xa8) = 5;
  *(undefined4 *)(param_1 + 0xac) = 0;
  if (*(int *)(param_1 + 0xa8) < *(int *)(param_1 + 0xa4)) {
    iVar2 = *(int *)(param_1 + 0xa8) + -1;
    if (iVar2 == 0) {
      trap(7);
    }
    *(int *)(param_1 + 0xac) = (*(int *)(param_1 + 0xa4) + -1) / iVar2;
    iVar2 = *(int *)(param_1 + 0xa8) + -1;
    if (iVar2 == 0) {
      trap(7);
    }
    if ((*(int *)(param_1 + 0xa4) + -1) % iVar2 != 0) {
      *(int *)(param_1 + 0xac) = *(int *)(param_1 + 0xac) + 1;
    }
  }
  iStack_10 = param_1;
  iStack_68 = __nw__FUi(0x148);
  if (iStack_68 != 0) {
    iStack_68 = __ct__7primWinFv(iStack_68);
  }
  *(int *)(iStack_10 + 0x58) = iStack_68;
  uVar1 = *(undefined4 *)(iStack_10 + 0x58);
  initialize__7primWinFP7primTex(uVar1,m_pPT);
  setItem__7primWinFiii(uVar1,0xe,0x16,0x13);
  setTex__7primWinFiiii(uVar1,3,0,0,0);
  for (iVar2 = 0; iVar2 < *(int *)(iStack_10 + 0x11c); iVar2 = iVar2 + 1) {
    createTexPoly__7primWinFiiiiii(uVar1,iVar2 << 1,0,iVar2 * 0x36 + 0x3e,0xe4,0,0);
    iStack_6c = *(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + *(char *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x80) * 0x20 +
                0x84;
    iStack_58 = (int)*(char *)(iStack_6c + iVar2 + 0x12);
    iVar6 = ourBtlSaveDat__10BtlSaveSec + iStack_58 * 0xc0;
    iStack_74 = iVar6 + 0x44;
    iStack_70 = iStack_74;
    iStack_18 = iStack_74;
    iStack_14 = iStack_6c;
    setTex__7primWinFiiii(uVar1,*(ushort *)(iVar6 + 0x4c) + 6,iVar2 + 1,0,0);
    createTexPoly__7primWinFiiiiii(uVar1,iVar2 * 2 + 1,iVar2 + 1,iVar2 * 0x36 + 0x3e,0xd6,0,0);
  }
  setTex__7primWinFiiii(uVar1,2,0xb,0,0);
  createTexPoly__7primWinFiiiiii(uVar1,0x10,0xb,8,0x188,0,0);
  setTex__7primWinFiiii(uVar1,0,0xc,0,0);
  createTexPoly__7primWinFiiiiii(uVar1,0x11,0xc,0x140,0x58,0,0);
  iVar2 = getPP__7primWinFi(uVar1,0x11);
  (**(code **)(*(int *)(iVar2 + 8) + 0x28))(0x42d00000,0x40800000);
  uVar4 = getPP__7primWinFi(uVar1,0x11);
  SetUV__11MenuPolygonFUsUsUsUs(uVar4,1,1,0x48,8);
  createTexPoly__7primWinFiiiiii(uVar1,0x12,0xc,0x1a8,0x58,0,0);
  iVar2 = getPP__7primWinFi(uVar1,0x12);
  (**(code **)(*(int *)(iVar2 + 8) + 0x28))(0x42c00000,0x40800000);
  uVar4 = getPP__7primWinFi(uVar1,0x12);
  SetUV__11MenuPolygonFUsUsUsUs(uVar4,0x51,1,0x58,8);
  createTexPoly__7primWinFiiiiii(uVar1,0x13,0xc,0x140,0x94,0,0);
  iVar2 = getPP__7primWinFi(uVar1,0x13);
  (**(code **)(*(int *)(iVar2 + 8) + 0x28))(0x42d00000,0x40800000);
  uVar4 = getPP__7primWinFi(uVar1,0x13);
  SetUV__11MenuPolygonFUsUsUsUs(uVar4,1,1,0x48,8);
  createTexPoly__7primWinFiiiiii(uVar1,0x14,0xc,0x1a8,0x94,0,0);
  iVar2 = getPP__7primWinFi(uVar1,0x14);
  (**(code **)(*(int *)(iVar2 + 8) + 0x28))(0x42c00000,0x40800000);
  uVar4 = getPP__7primWinFi(uVar1,0x14);
  SetUV__11MenuPolygonFUsUsUsUs(uVar4,0x51,1,0x58,8);
  setTextArea__7primWinFiiib(uVar1,10,0x280,0x180,1);
  for (iVar2 = 0; iVar2 < *(int *)(iStack_10 + 0x11c); iVar2 = iVar2 + 1) {
    createText__7primWinFiiiiPciib(uVar1,iVar2,10,iVar2 * 0x36 + 0x68,0xd4,shopMess_equipMark_J,0,1);
    setTextAlpha__7primWinFii(uVar1,iVar2,0);
  }
  for (iVar2 = 0; iVar2 < 4; iVar2 = iVar2 + 1) {
    createText__7primWinFiiiiPciib(uVar1,iVar2 + 8,10,8,iVar2 * 0x14 + 0x124,(&shopMess_status_J)[iVar2],0x34,2);
  }
  createText__7primWinFiiiiPciib(uVar1,0xf,10,0x14c,100,PTR__7050_00553f34,0,0);
  if (*(int *)(iStack_10 + 0xb8) == 3) {
    createText__7primWinFiiiiPciib(uVar1,0x12,10,0x1c0,0x7a,PTR__7053_00553f40,0,0);
  }
  createText__7primWinFiiiiPciib(uVar1,0x10,10,0x180,0xa0,PTR__7051_00553f38,0,0);
  if (*(int *)(iStack_10 + 0xa8) < *(int *)(iStack_10 + 0xa4)) {
    setMenuTex__7primWinFP11MenuTextureiii(uVar1,0x421658,0xd,0x20,0x14);
    createTexPoly__7primWinFiiiiii(uVar1,0x15,0xd,0x17c,0x174,0,1);
    createText__7primWinFiiiiPciib(uVar1,0x11,10,0x19c,0x174,PTR__7052_00553f3c,0,0);
  }
  buildWin__7primWinFiiiiii(uVar1,1,0,0,0,0,0);
  fadein__7primWinFi(*(undefined4 *)(iStack_10 + 0x58),0x10);
  *(undefined4 *)(iStack_10 + 0x4c) = uVar1;
  iStack_78 = __nw__FUi(0x148);
  if (iStack_78 != 0) {
    iStack_78 = __ct__7primWinFv(iStack_78);
  }
  *(int *)(iStack_10 + 0x70) = iStack_78;
  uVar1 = *(undefined4 *)(iStack_10 + 0x70);
  initialize__7primWinFP7primTex(uVar1,m_pPT);
  setItem__7primWinFiii(uVar1,1,0,1);
  setTextArea__7primWinFiiib(uVar1,0,0x100,0x20,1);
  if (*(char *)(iStack_10 + 0xc4) == '\0') {
    uVar3 = addMessage__7primWinFiiPcib(uVar1,8,0,(&shopMess_titleSellRank_J)[*(int *)(iStack_10 + 0xb8)],1,1);
    *(undefined4 *)(iStack_10 + 0x74) = uVar3;
  }
  else {
    uVar3 = addMessage__7primWinFiiPcib(uVar1,0,0,(&shopMess_titleBuyRank_J)[*(int *)(iStack_10 + 0xb8)],1,1);
    *(undefined4 *)(iStack_10 + 0x74) = uVar3;
  }
  Finish__11MenuMessageFv(*(undefined4 *)(iStack_10 + 0x74));
  buildWin__7primWinFiiiiii(uVar1,1,0x90,0x20,0xb8,0x20,3);
  fadein__7primWinFi(*(undefined4 *)(iStack_10 + 0x70),0x10);
  iStack_7c = __nw__FUi(0x148);
  if (iStack_7c != 0) {
    iStack_7c = __ct__7primWinFv(iStack_7c);
  }
  *(int *)(iStack_10 + 0x78) = iStack_7c;
  uVar1 = *(undefined4 *)(iStack_10 + 0x78);
  initialize__7primWinFP7primTex(uVar1,m_pPT);
  createGroup__7primWinFi(uVar1,*(undefined4 *)(iStack_10 + 0xa4));
  setItem__7primWinFiii(uVar1,0xd,*(undefined4 *)(iStack_10 + 0xa4),*(int *)(iStack_10 + 0xa4) * 3);
  setMenuTex__7primWinFP11MenuTextureiii(uVar1,0x421698,2,0x10,0x14);
  setTextArea__7primWinFiiib(uVar1,10,0x200,0x180,1);
  for (iVar2 = 0; iVar2 < *(int *)(iStack_10 + 0xa4); iVar2 = iVar2 + 1) {
    piVar7 = (int *)(*(int *)(iStack_10 + 0x100) + iVar2 * 0x1c);
    setGroup__7primWinFiffff(0,(float)(iVar2 * 0x15),0x43a00000,0x41a80000,uVar1,iVar2);
    createTexPoly__7primWinFiiiiii(uVar1,iVar2,2,0,0,0x10,0x14);
    switch(piVar7[1]) {
    case 1:
      setTexBlock__7primWinFiii(uVar1,iVar2,4,1);
      iStack_1c = GetRegDat__9RegDatApiFiii(0x33,piVar7[2],0xffffffffffffffff);
      if (*(char *)(iStack_10 + 0xc4) == '\0') {
        *piVar7 = *(int *)(iStack_1c + 0x28);
      }
      else {
        *piVar7 = *(int *)(iStack_1c + 0x24);
      }
      uVar4 = GetRegDat__9RegDatApiFiii(9,piVar7[2],0xffffffffffffffff);
      sprintf(auStack_1a0,0x55a738,uVar4);
      break;
    case 2:
      iStack_20 = GetRegDat__9RegDatApiFiii(0x30,piVar7[2],0xffffffffffffffff);
      mSetWeaponIcon__4shopFP7primWinP11WEAPONParami(iStack_10,uVar1,iStack_20,iVar2);
      if (*(char *)(iStack_10 + 0xc4) == '\0') {
        *piVar7 = *(int *)(iStack_20 + 0xc);
      }
      else {
        *piVar7 = *(int *)(iStack_20 + 0xc);
      }
      uVar4 = GetRegDat__9RegDatApiFiii(6,piVar7[2],0xffffffffffffffff);
      sprintf(auStack_1a0,0x55a738,uVar4);
      break;
    case 3:
      uVar4 = setTexBlock__7primWinFiii(uVar1,iVar2,7,1);
      iStack_24 = GetRegDat__9RegDatApiFiii(0x31,piVar7[2],0xffffffffffffffff,uVar4);
      if (*(char *)(iStack_10 + 0xc4) == '\0') {
        *piVar7 = *(int *)(iStack_24 + 0x10);
      }
      else {
        *piVar7 = *(int *)(iStack_24 + 0xc);
      }
      uVar4 = GetRegDat__9RegDatApiFiii(7,piVar7[2],0xffffffffffffffff);
      sprintf(auStack_1a0,0x55a738,uVar4);
      break;
    case 4:
      setTexBlock__7primWinFiii(uVar1,iVar2,0,2);
      iStack_28 = GetRegDat__9RegDatApiFiii(0x32,piVar7[2],0xffffffffffffffff);
      if (*(char *)(iStack_10 + 0xc4) == '\0') {
        *piVar7 = *(int *)(iStack_28 + 0x24);
      }
      else {
        *piVar7 = *(int *)(iStack_28 + 0x20);
      }
      uVar4 = GetRegDat__9RegDatApiFiii(8,piVar7[2],0xffffffffffffffff);
      sprintf(auStack_1a0,0x55a738,uVar4);
      break;
    case 5:
      uVar4 = setTexBlock__7primWinFiii(uVar1,iVar2,5,2);
      iStack_2c = GetRegDat__9RegDatApiFiii(0x37,piVar7[2],0xffffffffffffffff,uVar4);
      if (*(char *)(iStack_10 + 0xc4) == '\0') {
        *piVar7 = *(int *)(iStack_2c + 0x14);
      }
      else {
        *piVar7 = *(int *)(iStack_2c + 0x10);
      }
      uVar4 = GetRegDat__9RegDatApiFiii(0xd,piVar7[2],0xffffffffffffffff);
      sprintf(auStack_1a0,0x55a738,uVar4);
      break;
    case 6:
      setTexBlock__7primWinFiii(uVar1,iVar2,6,1);
      iStack_30 = GetRegDat__9RegDatApiFiii(0x3e,piVar7[2],0xffffffffffffffff);
      if (*(char *)(iStack_10 + 0xc4) == '\0') {
        *piVar7 = *(int *)(iStack_30 + 0x18);
      }
      else {
        *piVar7 = *(int *)(iStack_30 + 0x14);
      }
      uVar4 = GetRegDat__9RegDatApiFiii(0x11,piVar7[2],0xffffffffffffffff);
      sprintf(auStack_1a0,0x55a738,uVar4);
    }
    uVar4 = createText__7primWinFiiiiPciib(uVar1,iVar2,10,0x12,0,auStack_1a0,0,0);
    if (*piVar7 == -1) {
      sprintf(auStack_1a0,0x55a748);
    }
    else {
      sprintf(auStack_1a0,0x55a740,*piVar7,uVar4);
    }
    createText__7primWinFiiiiPciib(uVar1,*(int *)(iStack_10 + 0xa4) + iVar2,10,0xa0,0,auStack_1a0,0,0);
    piVar7[3] = 0;
    sprintf(auStack_1a0,0x55a750,piVar7[3]);
    createText__7primWinFiiiiPciib(uVar1,iVar2 + *(int *)(iStack_10 + 0xa4) * 2,10,0xe0,0,auStack_1a0,0,0);
    iStack_80 = *(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + *(char *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x80) * 0x20 +
                0x84;
    switch(piVar7[1]) {
    case 1:
      piVar7[6] = (uint)*(byte *)(*(int *)(iStack_10 + 0x120) + piVar7[2]);
      piVar7[5] = 0;
      break;
    case 2:
      piVar7[6] = (uint)*(byte *)(*(int *)(iStack_10 + 0x120) + piVar7[2] + 0x80);
      piVar7[5] = 0;
      for (iStack_38 = 0; iStack_38 < *(int *)(iStack_10 + 0x11c); iStack_38 = iStack_38 + 1) {
        iStack_5c = (int)*(char *)(iStack_80 + iStack_38 + 0x12);
        iVar6 = ourBtlSaveDat__10BtlSaveSec + iStack_5c * 0xc0;
        iStack_88 = iVar6 + 0x44;
        if ((long)*(char *)(iVar6 + 0x71) == (long)piVar7[2]) {
          piVar7[5] = piVar7[5] + 1;
        }
        iStack_84 = iStack_88;
        iStack_3c = iStack_88;
      }
      break;
    case 3:
      piVar7[6] = (uint)*(byte *)(*(int *)(iStack_10 + 0x120) + piVar7[2] + 0xe0);
      piVar7[5] = 0;
      for (iStack_40 = 0; iStack_40 < *(int *)(iStack_10 + 0x11c); iStack_40 = iStack_40 + 1) {
        iStack_60 = (int)*(char *)(iStack_80 + iStack_40 + 0x12);
        iVar6 = ourBtlSaveDat__10BtlSaveSec + iStack_60 * 0xc0;
        iStack_90 = iVar6 + 0x44;
        if ((long)*(char *)(iVar6 + 0x72) == (long)piVar7[2]) {
          piVar7[5] = piVar7[5] + 1;
        }
        iStack_8c = iStack_90;
        iStack_44 = iStack_90;
      }
      break;
    case 4:
      piVar7[6] = (uint)*(byte *)(*(int *)(iStack_10 + 0x120) + piVar7[2] + 0x110);
      piVar7[5] = 0;
      for (iStack_48 = 0; iStack_48 < *(int *)(iStack_10 + 0x11c); iStack_48 = iStack_48 + 1) {
        iStack_64 = (int)*(char *)(iStack_80 + iStack_48 + 0x12);
        iStack_98 = ourBtlSaveDat__10BtlSaveSec + iStack_64 * 0xc0 + 0x44;
        for (iStack_50 = 0; iStack_50 < 3; iStack_50 = iStack_50 + 1) {
          if ((long)*(char *)(iStack_98 + iStack_50 + 0x2f) == (long)piVar7[2]) {
            piVar7[5] = piVar7[5] + 1;
          }
        }
        iStack_94 = iStack_98;
        iStack_4c = iStack_98;
      }
      break;
    case 5:
      piVar7[6] = 0;
      piVar7[5] = 0;
      break;
    case 6:
      piVar7[6] = (uint)*(byte *)(*(int *)(iStack_10 + 0x120) + piVar7[2] + 0x174);
      piVar7[5] = 0;
    }
    if (*(char *)(iStack_10 + 0xc4) == '\0') {
      if (*piVar7 == -1) {
        piVar7[4] = 1;
      }
      else {
        piVar7[4] = (piVar7[6] + 1) - piVar7[5];
      }
    }
    else {
      piVar7[4] = 100 - piVar7[6];
    }
    iStack_34 = iStack_80;
    if (piVar7[4] == 1) {
      setTextClut__7primWinFii(uVar1,iVar2,0x20);
      setTextClut__7primWinFii(uVar1,*(int *)(iStack_10 + 0xa4) + iVar2,0x20);
      setTextClut__7primWinFii(uVar1,iVar2 + *(int *)(iStack_10 + 0xa4) * 2,0x20);
    }
  }
  buildWin__7primWinFiiiiii(uVar1,3,0x28,0x48,0xe0,0x69,0);
  setScrollWin__7primWinFii(uVar1,1,5);
  initScroll__7primWinFii(uVar1,0,0);
  mSelectSelectorItem__4shopFv(iStack_10);
  aiStack_200[0] = (int)__7977;
  aiStack_200[1] = (int)((ulong)__7977 >> 0x20);
  aiStack_200[2] = DAT_005540d8;
  aiStack_200[3] = DAT_005540dc;
  aiStack_200[4] = DAT_005540e0;
  aiStack_200[5] = DAT_005540e4;
  aiStack_200[6] = DAT_005540e8;
  aiStack_200[7] = DAT_005540ec;
  aiStack_200[8] = DAT_005540f0;
  aiStack_200[9] = DAT_005540f4;
  aiStack_200[10] = DAT_005540f8;
  aiStack_200[0xb] = DAT_005540fc;
  aiStack_200[0xc] = DAT_00554100;
  aiStack_200[0xd] = DAT_00554104;
  aiStack_200[0xe] = DAT_00554108;
  aiStack_200[0xf] = DAT_0055410c;
  aiStack_200[0x10] = DAT_00554110;
  aiStack_200[0x11] = DAT_00554114;
  aiStack_200[0x12] = DAT_00554118;
  aiStack_200[0x13] = DAT_0055411c;
  aiStack_200[0x14] = DAT_00554120;
  uStack_1ac = DAT_00554124;
  uStack_1a8 = DAT_00554128;
  uStack_1a4 = DAT_0055412c;
  *(undefined4 *)(iStack_10 + 0x108) = 0;
  *(undefined1 *)(iStack_10 + 0x118) = 1;
  iStack_9c = __nw__FUi(0x148);
  if (iStack_9c != 0) {
    iStack_9c = __ct__7primWinFv(iStack_9c);
  }
  *(int *)(iStack_10 + 0x7c) = iStack_9c;
  uVar1 = *(undefined4 *)(iStack_10 + 0x7c);
  initialize__7primWinFP7primTex(uVar1,m_pPT);
  createGroup__7primWinFi(uVar1,1);
  setGroup__7primWinFiffff(0,0,0x44000000,0x43e00000,uVar1,0);
  setItem__7primWinFiii(uVar1,3,0,*(int *)(iStack_10 + 0x11c) * 4 + 8);
  setTextArea__7primWinFiiib(uVar1,1,0x280,0x1c0,1);
  for (iVar2 = 0; iVar2 < 8; iVar2 = iVar2 + 1) {
    createText__7primWinFiiiiPciib(uVar1,iVar2,1,aiStack_200[iVar2 * 2],aiStack_200[iVar2 * 2 + 1],0x55a758,0,0);
  }
  for (iStack_54 = 0; iStack_54 < *(int *)(iStack_10 + 0x11c); iStack_54 = iStack_54 + 1) {
    for (iVar2 = 0; iVar2 < 4; iVar2 = iVar2 + 1) {
      createText__7primWinFiiiiPciib(uVar1,iVar2 + iStack_54 * 4 + 8,1,
                      iStack_54 * 0x36 + aiStack_200[(iVar2 + 8) * 2],
                      aiStack_200[(iVar2 + 8) * 2 + 1],0x55a760,0,0);
    }
  }
  setTextAlpha__7primWinFii(uVar1,1,0);
  setTextAlpha__7primWinFii(uVar1,0,0);
  uVar4 = getPT__7primWinFi(uVar1,0);
  SetCSA__8FontItemFUc(uVar4,0);
  iVar2 = (int)uVar4;
  *(undefined1 *)(iVar2 + 0x5c) = 4;
  uVar5 = (ulong)*(byte *)(iVar2 + 0x11) & 0xfffffffffffffffd | 2;
  *(char *)(iVar2 + 0x11) = (char)uVar5;
  *(byte *)(iVar2 + 0x10) =
       *(byte *)(iVar2 + 0x10) & 0xfd | (byte)((uint)((uVar5 << 0x3e) >> 0x3f) << 1);
  if (*(int *)(iStack_10 + 0xa4) <= *(int *)(iStack_10 + 0xa8)) {
    setTextAlpha__7primWinFii(uVar1,7,0);
  }
  if (*(int *)(iStack_10 + 0xb8) == 3) {
    setTextAlpha__7primWinFii(uVar1,3,0);
  }
  buildWin__7primWinFiiiiii(uVar1,4,0,0,0,0,0);
  uVar4 = setScrollWin__7primWinFii(uVar1,1,1);
  initScroll__7primWinFii(uVar1,0,0,uVar4);
  uVar4 = fadein__7primWinFi(uVar1,0x10);
  mSetSelectorNote__4shopFv(iStack_10,uVar4);
  mUpdateNoteWin__4shopFv(iStack_10);
  return;
}

/* JP: 0x004e36c0  shop::mReleaseBuySellWin()   [mReleaseBuySellWin__4shopFv]  size=0xe8 */
void mReleaseBuySellWin__4shopFv(int param_1)

{
  if (*(int *)(param_1 + 0x7c) != 0) {
    DelayDeleteRequest__7primWinFv(*(undefined4 *)(param_1 + 0x7c));
    *(undefined4 *)(param_1 + 0x7c) = 0;
  }
  if (*(int *)(param_1 + 0x78) != 0) {
    DelayDeleteRequest__7primWinFv(*(undefined4 *)(param_1 + 0x78));
    *(undefined4 *)(param_1 + 0x78) = 0;
  }
  if (*(int *)(param_1 + 0x100) != 0) {
    __dla__FPv(*(undefined4 *)(param_1 + 0x100));
    *(undefined4 *)(param_1 + 0x100) = 0;
  }
  if (*(int *)(param_1 + 0x70) != 0) {
    DelayDeleteRequest__7primWinFv(*(undefined4 *)(param_1 + 0x70));
    *(undefined4 *)(param_1 + 0x70) = 0;
  }
  if (*(int *)(param_1 + 0x58) != 0) {
    DelayDeleteRequest__7primWinFv(*(undefined4 *)(param_1 + 0x58));
    *(undefined4 *)(param_1 + 0x58) = 0;
  }
  return;
}

/* JP: 0x004e37b0  shop::mSetupWarningWin()   [mSetupWarningWin__4shopFv]  size=0x298 */
void mSetupWarningWin__4shopFv(int param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  long lVar3;
  undefined1 auStack_120 [256];
  float fStack_20;
  float fStack_1c;
  float fStack_18;
  float fStack_14;
  int iStack_10;
  
  iStack_10 = param_1;
  lVar3 = __nw__FUi(0x148);
  uVar1 = 0;
  if (lVar3 != 0) {
    uVar1 = __ct__7primWinFv(lVar3);
  }
  *(undefined4 *)(iStack_10 + 0x68) = uVar1;
  uVar1 = *(undefined4 *)(iStack_10 + 0x68);
  initialize__7primWinFP7primTex(uVar1,m_pPT);
  setItem__7primWinFiii(uVar1,2,0,1);
  if (*(char *)(iStack_10 + 0xc4) == '\0') {
    sprintf(auStack_120,shopMess_doNotSell_J,
                    (&shopMess_itemKindTbl_J)
                    [*(int *)(*(int *)(iStack_10 + 0x100) + *(int *)(iStack_10 + 0x84) * 0x1c + 4) +
                     -1]);
  }
  else {
    sprintf(auStack_120,shopMess_doNotSell_J,
                    (&shopMess_itemKindTbl_J)
                    [*(int *)(*(int *)(iStack_10 + 0x100) + *(int *)(iStack_10 + 0x84) * 0x1c + 4) +
                     -1]);
  }
  setTextArea__7primWinFiiib(uVar1,1,0x280,0x40,0);
  uVar2 = addMessage__7primWinFiiPcib(uVar1,0,0,auStack_120,1,1);
  *(undefined4 *)(iStack_10 + 0x74) = uVar2;
  fStack_18 = *(float *)(*(int *)(iStack_10 + 0x74) + 0x2c);
  fStack_20 = *(float *)(*(int *)(iStack_10 + 0x74) + 0x2c);
  fStack_1c = fStack_20;
  fStack_14 = fStack_18;
  buildWin__7primWinFiiiiii(uVar1,5,(int)(256.0 - fStack_18 / 2.0),0xd4,(int)(fStack_20 + 20.0),0x14,3);
  fadein__7primWinFi(*(undefined4 *)(iStack_10 + 0x68),0x10);
  *(undefined4 *)(iStack_10 + 0x4c) = uVar1;
  *(undefined4 *)(iStack_10 + 0x90) = 0xec;
  uVar1 = addKeyWait__7primWinFv(uVar1);
  *(undefined4 *)(iStack_10 + 0x80) = uVar1;
  *(byte *)(*(int *)(iStack_10 + 0x80) + 0x12) = *(byte *)(*(int *)(iStack_10 + 0x80) + 0x12) & 0xfe
  ;
  return;
}

/* JP: 0x004e3a50  shop::mReleaseWarningWin()   [mReleaseWarningWin__4shopFv]  size=0x48 */
void mReleaseWarningWin__4shopFv(int param_1)

{
  if (*(int *)(param_1 + 0x68) != 0) {
    DelayDeleteRequest__7primWinFv(*(undefined4 *)(param_1 + 0x68));
    *(undefined4 *)(param_1 + 0x68) = 0;
  }
  return;
}

/* JP: 0x004e3aa0  shop::mSetupBuyQueryWin()   [mSetupBuyQueryWin__4shopFv]  size=0x39c */
void mSetupBuyQueryWin__4shopFv(int param_1)

{
  undefined4 uVar1;
  long lVar2;
  int iVar3;
  undefined8 uVar4;
  undefined **ppuVar5;
  undefined **ppuVar6;
  
  *(undefined4 *)(param_1 + 0x84) = 2;
  uVar4 = 4;
  if (*(char *)(param_1 + 0xc4) == '\0') {
    *(undefined4 *)(param_1 + 0x84) = 0;
    uVar4 = 7;
    ppuVar5 = &shopMess_querySell_J;
    ppuVar6 = &shopMess_querySellNote_J;
  }
  else {
    if (*(int *)(param_1 + 0x108) -
        (*(int *)(param_1 + 0x108) * (*(int *)(param_1 + 0xb8) + 1)) / 10 <=
        *(int *)(param_1 + 0x104)) {
      *(undefined4 *)(param_1 + 0x84) = 0;
      uVar4 = 5;
      if (*(int *)(param_1 + 0x108) <= *(int *)(param_1 + 0x104)) {
        uVar4 = 7;
      }
    }
    ppuVar5 = &shopMess_queryBuy_J;
    ppuVar6 = &shopMess_queryBuyNote_J;
  }
  lVar2 = __nw__FUi(0x148);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = __ct__7primWinFv(lVar2);
  }
  *(undefined4 *)(param_1 + 0x6c) = uVar1;
  uVar1 = *(undefined4 *)(param_1 + 0x6c);
  initialize__7primWinFP7primTex(uVar1,m_pPT);
  setItem__7primWinFiii(uVar1,0,0,0);
  buildWin__7primWinFiiiiii(uVar1,4,0x70,0xcc,0x120,100,6);
  fadein__7primWinFi(uVar1,0x10);
  lVar2 = __nw__FUi(0x148);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = __ct__7primWinFv(lVar2);
  }
  *(undefined4 *)(param_1 + 100) = uVar1;
  uVar1 = *(undefined4 *)(param_1 + 100);
  initialize__7primWinFP7primTex(uVar1,m_pPT);
  setItem__7primWinFiii(uVar1,2,0,7);
  setTextArea__7primWinFiiib(uVar1,1,0x280,0x180,1);
  for (iVar3 = 0; iVar3 < 3; iVar3 = iVar3 + 1) {
    createText__7primWinFiiiiPciib(uVar1,iVar3,1,0xa0,iVar3 * 0x16 + 0xec,ppuVar5[iVar3],0,0);
    createText__7primWinFiiiiPciib(uVar1,iVar3 + 3,1,8,0x1a2,ppuVar6[iVar3],0,0);
  }
  createText__7primWinFiiiiPciib(uVar1,6,1,0x80,0xd4,ppuVar5[3],0,0);
  setMenuWindow__7primWinFiiiii(uVar1,3,*(undefined4 *)(param_1 + 0x84),0,3,uVar4);
  buildWin__7primWinFiiiiii(uVar1,5,0,0,0,0,0);
  fadein__7primWinFi(*(undefined4 *)(param_1 + 100),0x10);
  *(undefined4 *)(param_1 + 0x4c) = uVar1;
  return;
}

/* JP: 0x004e3e40  shop::mReleaseBuyQueryWin()   [mReleaseBuyQueryWin__4shopFv]  size=0x70 */
void mReleaseBuyQueryWin__4shopFv(int param_1)

{
  if (*(int *)(param_1 + 100) != 0) {
    DelayDeleteRequest__7primWinFv(*(undefined4 *)(param_1 + 100));
    *(undefined4 *)(param_1 + 100) = 0;
  }
  if (*(int *)(param_1 + 0x6c) != 0) {
    DelayDeleteRequest__7primWinFv(*(undefined4 *)(param_1 + 0x6c));
    *(undefined4 *)(param_1 + 0x6c) = 0;
  }
  return;
}

/* JP: 0x004e3eb0  shop::mSetupBuySelectDiscWin()   [mSetupBuySelectDiscWin__4shopFv]  size=0x3b4 */
void mSetupBuySelectDiscWin__4shopFv(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  long lVar4;
  int iVar5;
  uint uVar6;
  undefined **ppuVar7;
  uint uVar8;
  undefined1 auStack_110 [256];
  int iStack_10;
  
  *(undefined4 *)(param_1 + 0x84) = 0;
  iVar1 = *(int *)(param_1 + 0xb8);
  iVar5 = iVar1 + 1;
  uVar8 = 1;
  iStack_10 = param_1;
  lVar4 = __nw__FUi(0x148);
  uVar3 = 0;
  if (lVar4 != 0) {
    uVar3 = __ct__7primWinFv(lVar4);
  }
  *(undefined4 *)(iStack_10 + 0x6c) = uVar3;
  uVar3 = *(undefined4 *)(iStack_10 + 0x6c);
  initialize__7primWinFP7primTex(uVar3,m_pPT);
  setItem__7primWinFiii(uVar3,0,0,0);
  buildWin__7primWinFiiiiii(uVar3,4,0x40,0xcc,0x180,iVar5 * 0x16 + 0x30,6);
  fadein__7primWinFi(uVar3,0x10);
  lVar4 = __nw__FUi(0x148);
  uVar3 = 0;
  if (lVar4 != 0) {
    uVar3 = __ct__7primWinFv(lVar4);
  }
  *(undefined4 *)(iStack_10 + 100) = uVar3;
  uVar3 = *(undefined4 *)(iStack_10 + 100);
  initialize__7primWinFP7primTex(uVar3,m_pPT);
  setItem__7primWinFiii(uVar3,2,0,iVar5 * 2 + 1);
  if (*(char *)(iStack_10 + 0xc4) == '\0') {
    ppuVar7 = &shopMess_priceupSelect_J;
    uVar2 = shopMess_priceupSelectNote_J;
  }
  else {
    ppuVar7 = &shopMess_discountSelect_J;
    uVar2 = shopMess_discountSelectNote_J;
  }
  setTextArea__7primWinFiiib(uVar3,1,0x280,0x180,1);
  for (uVar6 = 0; (int)uVar6 < iVar5; uVar6 = uVar6 + 1) {
    sprintf(auStack_110,ppuVar7[iVar1 - uVar6]);
    createText__7primWinFiiiiPciib(uVar3,uVar6,1,0x78,uVar6 * 0x16 + 0xec,auStack_110,0,0);
    sprintf(auStack_110,uVar2,ppuVar7[iVar1 - uVar6]);
    createText__7primWinFiiiiPciib(uVar3,iVar5 + uVar6,1,8,0x1a2,auStack_110,0,0);
    if ((*(char *)(iStack_10 + 0xc4) == '\0') ||
       ((int)(*(int *)(iStack_10 + 0x108) * (10 - (iVar5 - uVar6))) / 10 <=
        *(int *)(iStack_10 + 0x104))) {
      uVar8 = uVar8 | 1 << (uVar6 & 0x1f);
    }
  }
  createText__7primWinFiiiiPciib(uVar3,iVar5 * 2,1,0x50,0xd4,ppuVar7[5],0,0);
  setMenuWindow__7primWinFiiiii(uVar3,iVar5,*(undefined4 *)(iStack_10 + 0x84),0,iVar5,uVar8);
  buildWin__7primWinFiiiiii(uVar3,5,0,0,0,0,0);
  fadein__7primWinFi(*(undefined4 *)(iStack_10 + 100),0x10);
  *(undefined4 *)(iStack_10 + 0x4c) = uVar3;
  return;
}

/* JP: 0x004e4270  shop::mReleaseBuySelectDiscWin()   [mReleaseBuySelectDiscWin__4shopFv]  size=0x70 */
void mReleaseBuySelectDiscWin__4shopFv(int param_1)

{
  if (*(int *)(param_1 + 100) != 0) {
    DelayDeleteRequest__7primWinFv(*(undefined4 *)(param_1 + 100));
    *(undefined4 *)(param_1 + 100) = 0;
  }
  if (*(int *)(param_1 + 0x6c) != 0) {
    DelayDeleteRequest__7primWinFv(*(undefined4 *)(param_1 + 0x6c));
    *(undefined4 *)(param_1 + 0x6c) = 0;
  }
  return;
}

/* JP: 0x004e42e0  shop::mSetupBuyDispDiscWin()   [mSetupBuyDispDiscWin__4shopFv]  size=0x258 */
void mSetupBuyDispDiscWin__4shopFv(int param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  long lVar3;
  undefined1 auStack_120 [256];
  float fStack_20;
  float fStack_1c;
  float fStack_18;
  float fStack_14;
  int iStack_10;
  
  iStack_10 = param_1;
  lVar3 = __nw__FUi(0x148);
  uVar1 = 0;
  if (lVar3 != 0) {
    uVar1 = __ct__7primWinFv(lVar3);
  }
  *(undefined4 *)(iStack_10 + 0x68) = uVar1;
  uVar1 = *(undefined4 *)(iStack_10 + 0x68);
  initialize__7primWinFP7primTex(uVar1,m_pPT);
  setItem__7primWinFiii(uVar1,2,0,1);
  if (*(char *)(iStack_10 + 0xc4) == '\0') {
    sprintf(auStack_120,shopMess_priceupSelectNote_J,(&shopMess_upRank_J)[*(int *)(iStack_10 + 0xc0)]);
  }
  else {
    sprintf(auStack_120,shopMess_discountSelectNote_J,(&shopMess_discRank_J)[*(int *)(iStack_10 + 0xc0)]);
  }
  setTextArea__7primWinFiiib(uVar1,1,0x280,0x40,0);
  uVar2 = addMessage__7primWinFiiPcib(uVar1,0,0,auStack_120,1,1);
  *(undefined4 *)(iStack_10 + 0x74) = uVar2;
  fStack_18 = *(float *)(*(int *)(iStack_10 + 0x74) + 0x2c);
  fStack_20 = *(float *)(*(int *)(iStack_10 + 0x74) + 0x2c);
  fStack_1c = fStack_20;
  fStack_14 = fStack_18;
  buildWin__7primWinFiiiiii(uVar1,5,(int)(256.0 - fStack_18 / 2.0),0xd4,(int)(fStack_20 + 20.0),0x14,3);
  fadein__7primWinFi(*(undefined4 *)(iStack_10 + 0x68),0x10);
  *(undefined4 *)(iStack_10 + 0x4c) = uVar1;
  *(undefined4 *)(iStack_10 + 0x90) = 0xec;
  uVar1 = addKeyWait__7primWinFv(uVar1);
  *(undefined4 *)(iStack_10 + 0x80) = uVar1;
  *(byte *)(*(int *)(iStack_10 + 0x80) + 0x12) = *(byte *)(*(int *)(iStack_10 + 0x80) + 0x12) & 0xfe
  ;
  return;
}

/* JP: 0x004e4540  shop::mReleaseBuyDispDiscWin()   [mReleaseBuyDispDiscWin__4shopFv]  size=0x48 */
void mReleaseBuyDispDiscWin__4shopFv(int param_1)

{
  if (*(int *)(param_1 + 0x68) != 0) {
    DelayDeleteRequest__7primWinFv(*(undefined4 *)(param_1 + 0x68));
    *(undefined4 *)(param_1 + 0x68) = 0;
  }
  return;
}

/* JP: 0x004e4590  shop::mSetupBuyResultWin()   [mSetupBuyResultWin__4shopFv]  size=0xaf8 */
void mSetupBuyResultWin__4shopFv(int param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  long lVar3;
  int iVar4;
  char *pcVar5;
  int iVar6;
  undefined *puVar7;
  int iVar8;
  undefined1 auStack_130 [264];
  int iStack_28;
  int iStack_24;
  undefined *puStack_20;
  undefined *puStack_1c;
  undefined *puStack_18;
  char cStack_11;
  int iStack_10;
  
  iStack_10 = param_1;
  lVar3 = __nw__FUi(0x148);
  uVar1 = 0;
  if (lVar3 != 0) {
    uVar1 = __ct__7primWinFv(lVar3);
  }
  *(undefined4 *)(iStack_10 + 0x6c) = uVar1;
  uVar1 = *(undefined4 *)(iStack_10 + 0x6c);
  initialize__7primWinFP7primTex(uVar1,m_pPT);
  setItem__7primWinFiii(uVar1,0,0,0);
  if (*(char *)(iStack_10 + 0xc4) == '\0') {
    buildWin__7primWinFiiiiii(uVar1,4,0x70,0xcc,0x120,0x40,6);
  }
  else {
    buildWin__7primWinFiiiiii(uVar1,4,0x70,0xcc,0x120,0x70,6);
  }
  fadein__7primWinFi(uVar1,0x10);
  uVar1 = addKeyWait__7primWinFv(uVar1);
  *(undefined4 *)(iStack_10 + 0x80) = uVar1;
  iStack_28 = *(int *)(iStack_10 + 0x80);
  *(byte *)(iStack_28 + 0x12) = *(byte *)(iStack_28 + 0x12) & 0xfe;
  lVar3 = __nw__FUi(0x148);
  uVar1 = 0;
  if (lVar3 != 0) {
    uVar1 = __ct__7primWinFv(lVar3);
  }
  *(undefined4 *)(iStack_10 + 0x68) = uVar1;
  uVar1 = *(undefined4 *)(iStack_10 + 0x68);
  initialize__7primWinFP7primTex(uVar1,m_pPT);
  setItem__7primWinFiii(uVar1,2,0,1);
  puStack_18 = shopMess_buyPoint_J;
  puStack_1c = shopMess_normalBuy_J+0x4;
  puStack_20 = shopMess_normalBuy_J+0x4;
  iVar8 = *(int *)(iStack_10 + 0x108);
  if (*(char *)(iStack_10 + 0xc4) == '\0') {
    puVar7 = shopMess_normalSell_J;
    if (*(char *)(iStack_10 + 0xc5) != '\0') {
      if (((ulong)*(byte *)(iStack_10 + 0xca) & 7) >> 1 < 2) {
        puVar7 = (&shopMess_priceupMiss_J)[*(int *)(iStack_10 + 0xc0)];
      }
      else {
        iVar8 = *(int *)(iStack_10 + 0x108) +
                (*(int *)(iStack_10 + 0x108) * (*(int *)(iStack_10 + 0xc0) + 1)) / 0x14;
        puVar7 = (&shopMess_priceupSell_J)[*(int *)(iStack_10 + 0xc0)];
      }
    }
    *(int *)(iStack_10 + 0x104) = *(int *)(iStack_10 + 0x104) + iVar8;
    setCash__8shopCashFi(*(undefined4 *)(iStack_10 + 0x128),*(undefined4 *)(iStack_10 + 0x104));
    *(undefined4 *)(iStack_10 + 0x108) = 0;
    for (iVar8 = 0; iVar8 < *(int *)(iStack_10 + 0xa4); iVar8 = iVar8 + 1) {
      iVar6 = *(int *)(iStack_10 + 0x100) + iVar8 * 0x1c;
      if (*(int *)(iVar6 + 0xc) != 0) {
        iVar4 = *(int *)(iVar6 + 4);
        if (iVar4 == 6) {
          iVar4 = *(int *)(iStack_10 + 0x120) + *(int *)(iVar6 + 8);
          *(char *)(iVar4 + 0x174) = *(char *)(iVar4 + 0x174) - (char)*(undefined4 *)(iVar6 + 0xc);
        }
        else if (iVar4 == 4) {
          iVar4 = *(int *)(iStack_10 + 0x120) + *(int *)(iVar6 + 8);
          *(char *)(iVar4 + 0x110) = *(char *)(iVar4 + 0x110) - (char)*(undefined4 *)(iVar6 + 0xc);
        }
        else if (iVar4 == 3) {
          iVar4 = *(int *)(iStack_10 + 0x120) + *(int *)(iVar6 + 8);
          *(char *)(iVar4 + 0xe0) = *(char *)(iVar4 + 0xe0) - (char)*(undefined4 *)(iVar6 + 0xc);
        }
        else if (iVar4 == 2) {
          iVar4 = *(int *)(iStack_10 + 0x120) + *(int *)(iVar6 + 8);
          *(char *)(iVar4 + 0x80) = *(char *)(iVar4 + 0x80) - (char)*(undefined4 *)(iVar6 + 0xc);
        }
        else if (iVar4 == 1) {
          pcVar5 = (char *)(*(int *)(iStack_10 + 0x120) + *(int *)(iVar6 + 8));
          *pcVar5 = *pcVar5 - (char)*(undefined4 *)(iVar6 + 0xc);
        }
      }
    }
    sprintf(auStack_130,0x55a738,puVar7);
    *(undefined4 *)(iStack_10 + 0x90) = 0x10e;
  }
  else {
    cStack_11 = '\x01';
    puVar7 = shopMess_normalBuy_J;
    if (*(char *)(iStack_10 + 0xc5) != '\0') {
      if (((ulong)*(byte *)(iStack_10 + 0xca) & 7) >> 1 < 2) {
        if (*(int *)(iStack_10 + 0x104) < *(int *)(iStack_10 + 0x108)) {
          cStack_11 = '\0';
          puVar7 = (&shopMess_discountPenalty_J)[*(int *)(iStack_10 + 0xc0)];
        }
        else {
          puVar7 = (&shopMess_discountMiss_J)[*(int *)(iStack_10 + 0xc0)];
        }
      }
      else {
        iVar8 = *(int *)(iStack_10 + 0x108) -
                (*(int *)(iStack_10 + 0x108) * (*(int *)(iStack_10 + 0xc0) + 1)) / 10;
        puVar7 = (&shopMess_discountBuy_J)[*(int *)(iStack_10 + 0xc0)];
      }
    }
    if (cStack_11 == '\0') {
      if (*(int *)(iStack_10 + 0xb8) == 3) {
        iVar6 = 0;
      }
      else {
        iVar6 = (((*(int *)(iStack_10 + 0x108) -
                  (*(int *)(iStack_10 + 0x108) * (*(int *)(iStack_10 + 0xc0) + 1)) / 10) -
                 *(int *)(iStack_10 + 0x104)) + 9) / 10;
        *(int *)(iStack_10 + 0x10c) = *(int *)(iStack_10 + 0x10c) + iVar6;
        if (*(int *)(iStack_10 + 0x10c) < 0) {
          *(undefined4 *)(iStack_10 + 0x10c) = 0;
        }
        lVar3 = mCalcPoint__4shopFb(iStack_10,0);
        if (lVar3 != 0) {
          do {
            lVar3 = mCalcPoint__4shopFb(iStack_10,0);
          } while (lVar3 != 0);
          puStack_1c = (&shopMess_rank_J)[*(int *)(iStack_10 + 0xb8)];
          puStack_20 = PTR__7099_0055401c;
        }
      }
      puStack_18 = PTR__7098_00554018;
    }
    else {
      iVar6 = (iVar8 + 99) / 100;
      *(int *)(iStack_10 + 0x10c) = *(int *)(iStack_10 + 0x10c) + iVar6;
      if (999999 < *(int *)(iStack_10 + 0x10c)) {
        *(undefined4 *)(iStack_10 + 0x10c) = 999999;
      }
      lVar3 = mCalcPoint__4shopFb(iStack_10,1);
      if (lVar3 != 0) {
        do {
          lVar3 = mCalcPoint__4shopFb(iStack_10,1);
        } while (lVar3 != 0);
        puStack_1c = (&shopMess_rank_J)[*(int *)(iStack_10 + 0xb8)];
        puStack_20 = PTR__7097_00554014;
        if (*(int *)(iStack_10 + 0xb8) == 4) {
          *(byte *)(*(int *)(iStack_10 + 0x120) + 0x60) =
               *(byte *)(*(int *)(iStack_10 + 0x120) + 0x60) | 0x20;
          *(byte *)(*(int *)(iStack_10 + 0x120) + 0x40) =
               *(byte *)(*(int *)(iStack_10 + 0x120) + 0x40) | 0x40;
        }
      }
      *(int *)(iStack_10 + 0x104) = *(int *)(iStack_10 + 0x104) - iVar8;
      setCash__8shopCashFi(*(undefined4 *)(iStack_10 + 0x128),*(undefined4 *)(iStack_10 + 0x104));
      *(undefined4 *)(iStack_10 + 0x108) = 0;
      for (iStack_24 = 0; iStack_24 < *(int *)(iStack_10 + 0xa4); iStack_24 = iStack_24 + 1) {
        iVar8 = *(int *)(iStack_10 + 0x100) + iStack_24 * 0x1c;
        if (*(int *)(iVar8 + 0xc) != 0) {
          switch(*(undefined4 *)(iVar8 + 4)) {
          case 1:
            pcVar5 = (char *)(*(int *)(iStack_10 + 0x120) + *(int *)(iVar8 + 8));
            *pcVar5 = *pcVar5 + (char)*(undefined4 *)(iVar8 + 0xc);
            break;
          case 2:
            iVar4 = *(int *)(iStack_10 + 0x120) + *(int *)(iVar8 + 8);
            *(char *)(iVar4 + 0x80) = *(char *)(iVar4 + 0x80) + (char)*(undefined4 *)(iVar8 + 0xc);
            break;
          case 3:
            iVar4 = *(int *)(iStack_10 + 0x120) + *(int *)(iVar8 + 8);
            *(char *)(iVar4 + 0xe0) = *(char *)(iVar4 + 0xe0) + (char)*(undefined4 *)(iVar8 + 0xc);
            break;
          case 4:
            iVar4 = *(int *)(iStack_10 + 0x120) + *(int *)(iVar8 + 8);
            *(char *)(iVar4 + 0x110) = *(char *)(iVar4 + 0x110) + (char)*(undefined4 *)(iVar8 + 0xc)
            ;
            break;
          case 5:
            iVar4 = *(int *)(iVar8 + 8);
            if (iVar4 < 0) {
              iVar4 = iVar4 + 7;
            }
            iVar4 = *(int *)(iStack_10 + 0x120) + (iVar4 >> 3);
            *(byte *)(iVar4 + 0x160) =
                 *(byte *)(iVar4 + 0x160) | (byte)(1 << (*(uint *)(iVar8 + 8) & 7));
            break;
          case 6:
            iVar4 = *(int *)(iStack_10 + 0x120) + *(int *)(iVar8 + 8);
            *(char *)(iVar4 + 0x174) = *(char *)(iVar4 + 0x174) + (char)*(undefined4 *)(iVar8 + 0xc)
            ;
          }
        }
      }
    }
    sprintf(auStack_130,0x55a7b0,puVar7,puStack_18,iVar6,puStack_1c,puStack_20);
    *(undefined4 *)(iStack_10 + 0x90) = 0x13e;
  }
  setTextArea__7primWinFiiib(uVar1,1,0x280,0x180,0);
  uVar2 = addMessage__7primWinFiiPcib(uVar1,0x7a,0xd4,auStack_130,0,1);
  *(undefined4 *)(iStack_10 + 0x74) = uVar2;
  buildWin__7primWinFiiiiii(uVar1,5,0,0,0,0,0);
  fadein__7primWinFi(*(undefined4 *)(iStack_10 + 0x68),0x10);
  *(undefined4 *)(iStack_10 + 0x4c) = uVar1;
  return;
}

/* JP: 0x004e5090  shop::mReleaseBuyResultWin()   [mReleaseBuyResultWin__4shopFv]  size=0x70 */
void mReleaseBuyResultWin__4shopFv(int param_1)

{
  if (*(int *)(param_1 + 0x68) != 0) {
    DelayDeleteRequest__7primWinFv(*(undefined4 *)(param_1 + 0x68));
    *(undefined4 *)(param_1 + 0x68) = 0;
  }
  if (*(int *)(param_1 + 0x6c) != 0) {
    DelayDeleteRequest__7primWinFv(*(undefined4 *)(param_1 + 0x6c));
    *(undefined4 *)(param_1 + 0x6c) = 0;
  }
  return;
}

/* JP: 0x004e5100  shop::mCheckEndMessage()   [mCheckEndMessage__4shopFv]  size=0xa8 */
void mCheckEndMessage__4shopFv(int param_1)

{
  if ((*(int *)(param_1 + 0x80) != 0) &&
     (*(ushort *)(*(int *)(param_1 + 0x74) + 0x76) <= *(ushort *)(*(int *)(param_1 + 0x74) + 0x80)))
  {
    *(byte *)(*(int *)(param_1 + 0x80) + 0x12) =
         *(byte *)(*(int *)(param_1 + 0x80) + 0x12) & 0xfe | 1;
  }
  return;
}

/* JP: 0x004e51b0  shop::mSetupMainCursor(bool)   [mSetupMainCursor__4shopFb]  size=0xcc */
void mSetupMainCursor__4shopFb(int param_1,char param_2)

{
  undefined4 uVar1;
  long lVar2;
  
  if (*(int *)(param_1 + 0x8c) == 0) {
    lVar2 = __nw__FUi(0x10c);
    uVar1 = 0;
    if (lVar2 != 0) {
      uVar1 = __ct__10primCursorFv(lVar2);
    }
    *(undefined4 *)(param_1 + 0x8c) = uVar1;
    createCursor__10primCursorFiiii(*(undefined4 *)(param_1 + 0x8c),0,2,8,10);
    if (param_2 != '\0') {
      setItem__10primCursorFP7primWini(*(undefined4 *)(param_1 + 0x8c),*(undefined4 *)(param_1 + 0x4c),
                      *(undefined4 *)(param_1 + 0x84));
      qMove__10primCursorFv(*(undefined4 *)(param_1 + 0x8c));
    }
  }
  return;
}

/* JP: 0x004e5280  shop::mReleaseMainCursor()   [mReleaseMainCursor__4shopFv]  size=0x48 */
void mReleaseMainCursor__4shopFv(int param_1)

{
  if (*(int *)(param_1 + 0x8c) != 0) {
    DelayDeleteRequest__10primCursorFv(*(undefined4 *)(param_1 + 0x8c));
    *(undefined4 *)(param_1 + 0x8c) = 0;
  }
  return;
}

/* JP: 0x004e52d0  shop::mCheckSelector(int)   [mCheckSelector__4shopFi]  size=0x9fc */
void mCheckSelector__4shopFi(int param_1,uint param_2)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  undefined1 auStack_240 [256];
  undefined1 auStack_140 [256];
  int iStack_40;
  int iStack_3c;
  int iStack_38;
  int iStack_34;
  int iStack_30;
  int iStack_2c;
  int iStack_28;
  int iStack_24;
  int iStack_20;
  uint uStack_10;
  
  iStack_20 = param_1;
  uStack_10 = param_2;
  if (((param_2 & 0x100) == 0) || (*(int *)(param_1 + 0xa4) <= *(int *)(param_1 + 0xa8))) {
    if (((param_2 & 0x200) == 0) || (*(int *)(param_1 + 0xa4) <= *(int *)(param_1 + 0xa8))) {
      if ((param_2 & 0x10) == 0) {
        if ((param_2 & 0x40) == 0) {
          if ((param_2 & 0x20) == 0) {
            if ((param_2 & 0x80) != 0) {
              play__9primSoundFi(*(undefined4 *)(param_1 + 0x48),1);
              piVar2 = (int *)(*(int *)(iStack_20 + 0x100) + *(int *)(iStack_20 + 0x84) * 0x1c);
              if (piVar2[3] < 1) {
                if (1 < *(int *)(iStack_20 + 0x110)) {
                  *(undefined1 *)(iStack_20 + 0x118) = 1;
                  *(int *)(iStack_20 + 0x108) =
                       *(int *)(iStack_20 + 0x108) + *piVar2 * (*(int *)(iStack_20 + 0x110) + -1);
                  piVar2[3] = *(int *)(iStack_20 + 0x110) + -1;
                }
              }
              else {
                piVar2[3] = piVar2[3] + -1;
                *(int *)(iStack_20 + 0x108) = *(int *)(iStack_20 + 0x108) - *piVar2;
              }
              sprintf(auStack_240,0x55a750,piVar2[3]);
              setTextString__7primWinFiPc(*(undefined4 *)(iStack_20 + 0x78),
                              *(int *)(iStack_20 + 0x84) + *(int *)(iStack_20 + 0xa4) * 2,
                              auStack_240);
              initScroll__7primWinFii(*(undefined4 *)(iStack_20 + 0x78),0,
                              *(int *)(iStack_20 + 0x84) - *(int *)(iStack_20 + 0x9c));
            }
          }
          else {
            piVar2 = (int *)(*(int *)(param_1 + 0x100) + *(int *)(param_1 + 0x84) * 0x1c);
            iStack_24 = *piVar2 + *(int *)(param_1 + 0x108);
            iStack_24 = iStack_24 - (iStack_24 * (*(int *)(param_1 + 0xb8) + 1)) / 10;
            if (piVar2[3] < *(int *)(param_1 + 0x110) + -1) {
              play__9primSoundFi(*(undefined4 *)(param_1 + 0x48),1);
              if (piVar2[3] == 0) {
                *(undefined1 *)(iStack_20 + 0x118) = 0;
              }
              piVar2[3] = piVar2[3] + 1;
              *(int *)(iStack_20 + 0x108) = *(int *)(iStack_20 + 0x108) + *piVar2;
            }
            else if (*(char *)(param_1 + 0x118) == '\0') {
              play__9primSoundFi(*(undefined4 *)(param_1 + 0x48),4);
            }
            else {
              *(int *)(param_1 + 0x108) = *(int *)(param_1 + 0x108) - *piVar2 * piVar2[3];
              piVar2[3] = 0;
              play__9primSoundFi(*(undefined4 *)(param_1 + 0x48),1);
            }
            sprintf(auStack_140,0x55a750,piVar2[3]);
            setTextString__7primWinFiPc(*(undefined4 *)(iStack_20 + 0x78),
                            *(int *)(iStack_20 + 0x84) + *(int *)(iStack_20 + 0xa4) * 2,auStack_140)
            ;
            initScroll__7primWinFii(*(undefined4 *)(iStack_20 + 0x78),0,
                            *(int *)(iStack_20 + 0x84) - *(int *)(iStack_20 + 0x9c));
          }
        }
        else if (*(int *)(param_1 + 0x84) < *(int *)(param_1 + 0xa4) + -1) {
          play__9primSoundFi(*(undefined4 *)(param_1 + 0x48),0);
          *(undefined1 *)(iStack_20 + 0x118) = 1;
          mUnselectSelectorItem__4shopFv(iStack_20);
          *(int *)(iStack_20 + 0x9c) = *(int *)(iStack_20 + 0x9c) + 1;
          if (*(int *)(iStack_20 + 0x9c) < *(int *)(iStack_20 + 0xa8)) {
            *(int *)(iStack_20 + 0x84) = *(int *)(iStack_20 + 0x84) + 1;
            setItem__10primCursorFP7primWini(*(undefined4 *)(iStack_20 + 0x8c),*(undefined4 *)(iStack_20 + 0x78),
                            *(undefined4 *)(iStack_20 + 0x84));
          }
          else {
            *(int *)(iStack_20 + 0xa0) = *(int *)(iStack_20 + 0xa0) + 1;
            *(undefined4 *)(iStack_20 + 0x9c) = 0;
            iStack_34 = *(int *)(iStack_20 + 0x78);
            Scroll__10MenuWindowFss(iStack_34 + 0x3c,0,(short)*(undefined4 *)(iStack_20 + 0x84));
          }
          mSelectSelectorItem__4shopFv(iStack_20);
        }
      }
      else if (0 < *(int *)(param_1 + 0x84)) {
        play__9primSoundFi(*(undefined4 *)(param_1 + 0x48),0);
        *(undefined1 *)(iStack_20 + 0x118) = 1;
        mUnselectSelectorItem__4shopFv(iStack_20);
        *(int *)(iStack_20 + 0x9c) = *(int *)(iStack_20 + 0x9c) + -1;
        if (*(int *)(iStack_20 + 0x9c) < 0) {
          *(int *)(iStack_20 + 0xa0) = *(int *)(iStack_20 + 0xa0) + -1;
          *(int *)(iStack_20 + 0x9c) = *(int *)(iStack_20 + 0xa8) + -1;
          iStack_30 = *(int *)(iStack_20 + 0x78);
          Scroll__10MenuWindowFss(iStack_30 + 0x3c,0,
                          (short)*(undefined4 *)(iStack_20 + 0x84) -
                          (short)*(undefined4 *)(iStack_20 + 0x9c));
        }
        else {
          *(int *)(iStack_20 + 0x84) = *(int *)(iStack_20 + 0x84) + -1;
          setItem__10primCursorFP7primWini(*(undefined4 *)(iStack_20 + 0x8c),*(undefined4 *)(iStack_20 + 0x78),
                          *(undefined4 *)(iStack_20 + 0x84));
        }
        mSelectSelectorItem__4shopFv(iStack_20);
      }
    }
    else {
      play__9primSoundFi(*(undefined4 *)(param_1 + 0x48),6);
      if (*(int *)(iStack_20 + 0xa0) < *(int *)(iStack_20 + 0xac) + -1) {
        mUnselectSelectorItem__4shopFv(iStack_20);
        *(int *)(iStack_20 + 0xa0) = *(int *)(iStack_20 + 0xa0) + 1;
        *(int *)(iStack_20 + 0x84) = *(int *)(iStack_20 + 0x84) + *(int *)(iStack_20 + 0xa8) + -1;
        if (*(int *)(iStack_20 + 0xa4) <= *(int *)(iStack_20 + 0x84)) {
          *(int *)(iStack_20 + 0x84) = *(int *)(iStack_20 + 0xa4) + -1;
          iVar3 = *(int *)(iStack_20 + 0xa8) + -1;
          if (iVar3 == 0) {
            trap(7);
          }
          *(int *)(iStack_20 + 0x9c) = *(int *)(iStack_20 + 0x84) % iVar3;
        }
        setItem__10primCursorFP7primWini(*(undefined4 *)(iStack_20 + 0x8c),*(undefined4 *)(iStack_20 + 0x78),
                        *(undefined4 *)(iStack_20 + 0x84));
        iStack_2c = *(int *)(iStack_20 + 0x78);
        iStack_40 = iStack_2c + 0x3c;
        Scroll__10MenuWindowFss(iStack_40,0,
                        (short)*(undefined4 *)(iStack_20 + 0x84) -
                        (short)*(undefined4 *)(iStack_20 + 0x9c));
        mSelectSelectorItem__4shopFv(iStack_20);
      }
      else if (*(int *)(iStack_20 + 0x84) < *(int *)(iStack_20 + 0xa4) + -1) {
        mUnselectSelectorItem__4shopFv(iStack_20);
        *(int *)(iStack_20 + 0x84) = *(int *)(iStack_20 + 0xa4) + -1;
        *(int *)(iStack_20 + 0x9c) =
             *(int *)(iStack_20 + 0x84) -
             *(int *)(iStack_20 + 0xa0) * (*(int *)(iStack_20 + 0xa8) + -1);
        setItem__10primCursorFP7primWini(*(undefined4 *)(iStack_20 + 0x8c),*(undefined4 *)(iStack_20 + 0x78),
                        *(undefined4 *)(iStack_20 + 0x84));
        mSelectSelectorItem__4shopFv(iStack_20);
      }
    }
  }
  else {
    play__9primSoundFi(*(undefined4 *)(param_1 + 0x48),7);
    if (*(int *)(iStack_20 + 0xa0) == 0) {
      if (*(int *)(iStack_20 + 0x9c) != 0) {
        mUnselectSelectorItem__4shopFv(iStack_20);
        *(undefined4 *)(iStack_20 + 0x84) = 0;
        *(undefined4 *)(iStack_20 + 0x9c) = 0;
        setItem__10primCursorFP7primWini(*(undefined4 *)(iStack_20 + 0x8c),*(undefined4 *)(iStack_20 + 0x78),
                        *(undefined4 *)(iStack_20 + 0x84));
        mSelectSelectorItem__4shopFv(iStack_20);
      }
    }
    else {
      mUnselectSelectorItem__4shopFv(iStack_20);
      *(int *)(iStack_20 + 0xa0) = *(int *)(iStack_20 + 0xa0) + -1;
      *(int *)(iStack_20 + 0x84) = *(int *)(iStack_20 + 0x84) - (*(int *)(iStack_20 + 0xa8) + -1);
      setItem__10primCursorFP7primWini(*(undefined4 *)(iStack_20 + 0x8c),*(undefined4 *)(iStack_20 + 0x78),
                      *(undefined4 *)(iStack_20 + 0x84));
      iStack_28 = *(int *)(iStack_20 + 0x78);
      iStack_3c = iStack_28 + 0x3c;
      iStack_38 = iStack_3c;
      Scroll__10MenuWindowFss(iStack_3c,0,
                      (short)*(undefined4 *)(iStack_20 + 0x84) -
                      (short)*(undefined4 *)(iStack_20 + 0x9c));
      mSelectSelectorItem__4shopFv(iStack_20);
    }
  }
  if (uStack_10 != 0) {
    iVar3 = *(int *)(iStack_20 + 0x84);
    iVar1 = *(int *)(iStack_20 + 0x100);
    mCalcCurrentMax__4shopFv(iStack_20);
    select__14shopScrollMarkFiii
              (*(undefined4 *)(iStack_20 + 0x94),*(undefined4 *)(iStack_20 + 0x9c),
               *(undefined4 *)(iVar1 + iVar3 * 0x1c + 0xc),*(undefined4 *)(iStack_20 + 0x110));
    mSetSelectorNote__4shopFv(iStack_20);
    mUpdateNoteWin__4shopFv(iStack_20);
  }
  return;
}

/* JP: 0x004e5cd0  shop::mUnselectSelectorItem()   [mUnselectSelectorItem__4shopFv]  size=0x204 */
void mUnselectSelectorItem__4shopFv(int param_1)

{
  undefined8 uVar1;
  
  if (*(int *)(*(int *)(param_1 + 0x100) + *(int *)(param_1 + 0x84) * 0x1c + 0x10) < 2) {
    setTextClut__7primWinFii(*(undefined4 *)(param_1 + 0x78),*(undefined4 *)(param_1 + 0x84),0x20);
    setTextClut__7primWinFii(*(undefined4 *)(param_1 + 0x78),
                    *(int *)(param_1 + 0xa4) + *(int *)(param_1 + 0x84),0x20);
    setTextClut__7primWinFii(*(undefined4 *)(param_1 + 0x78),
                    *(int *)(param_1 + 0x84) + *(int *)(param_1 + 0xa4) * 2,0x20);
    uVar1 = getPT__7primWinFi(*(undefined4 *)(param_1 + 0x78),*(undefined4 *)(param_1 + 0x84));
    (**(code **)(*(int *)((int)uVar1 + 8) + 0x30))(uVar1,0x7f,0x7f,0x7f);
    uVar1 = getPT__7primWinFi(*(undefined4 *)(param_1 + 0x78),
                            *(int *)(param_1 + 0xa4) + *(int *)(param_1 + 0x84));
    (**(code **)(*(int *)((int)uVar1 + 8) + 0x30))(uVar1,0x7f,0x7f,0x7f);
    uVar1 = getPT__7primWinFi(*(undefined4 *)(param_1 + 0x78),
                            *(int *)(param_1 + 0x84) + *(int *)(param_1 + 0xa4) * 2);
    (**(code **)(*(int *)((int)uVar1 + 8) + 0x30))(uVar1,0x7f,0x7f,0x7f);
  }
  else {
    setTextClut__7primWinFii(*(undefined4 *)(param_1 + 0x78),*(undefined4 *)(param_1 + 0x84),0);
    setTextClut__7primWinFii(*(undefined4 *)(param_1 + 0x78),
                    *(int *)(param_1 + 0xa4) + *(int *)(param_1 + 0x84),0);
    setTextClut__7primWinFii(*(undefined4 *)(param_1 + 0x78),
                    *(int *)(param_1 + 0x84) + *(int *)(param_1 + 0xa4) * 2,0);
  }
  return;
}

/* JP: 0x004e5ee0  shop::mSelectSelectorItem()   [mSelectSelectorItem__4shopFv]  size=0x18c */
void mSelectSelectorItem__4shopFv(int param_1)

{
  int iVar1;
  int iVar2;
  undefined8 uVar3;
  
  iVar1 = *(int *)(param_1 + 0x84);
  iVar2 = *(int *)(param_1 + 0x100);
  setTextClut__7primWinFii(*(undefined4 *)(param_1 + 0x78),*(undefined4 *)(param_1 + 0x84),0x10);
  setTextClut__7primWinFii(*(undefined4 *)(param_1 + 0x78),
                  *(int *)(param_1 + 0xa4) + *(int *)(param_1 + 0x84),0x10);
  setTextClut__7primWinFii(*(undefined4 *)(param_1 + 0x78),
                  *(int *)(param_1 + 0x84) + *(int *)(param_1 + 0xa4) * 2,0x10);
  if (*(int *)(iVar2 + iVar1 * 0x1c + 0x10) < 2) {
    uVar3 = getPT__7primWinFi(*(undefined4 *)(param_1 + 0x78),*(undefined4 *)(param_1 + 0x84));
    (**(code **)(*(int *)((int)uVar3 + 8) + 0x30))(uVar3,0x40,0x40,0x40);
    uVar3 = getPT__7primWinFi(*(undefined4 *)(param_1 + 0x78),
                            *(int *)(param_1 + 0xa4) + *(int *)(param_1 + 0x84));
    (**(code **)(*(int *)((int)uVar3 + 8) + 0x30))(uVar3,0x40,0x40,0x40);
    uVar3 = getPT__7primWinFi(*(undefined4 *)(param_1 + 0x78),
                            *(int *)(param_1 + 0x84) + *(int *)(param_1 + 0xa4) * 2);
    (**(code **)(*(int *)((int)uVar3 + 8) + 0x30))(uVar3,0x40,0x40,0x40);
  }
  return;
}

/* JP: 0x004e6070  shop::mSetSelectorNote()   [mSetSelectorNote__4shopFv]  size=0x1c4 */
void mSetSelectorNote__4shopFv(int param_1)

{
  undefined8 uVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0x100) + *(int *)(param_1 + 0x84) * 0x1c;
  switch(*(undefined4 *)(iVar2 + 4)) {
  case 1:
    uVar1 = GetRegDat__9RegDatApiFiii(0x1a,*(undefined4 *)(iVar2 + 8),0xffffffffffffffff);
    setTextString__7primWinFiPc(*(undefined4 *)(param_1 + 0x7c),6,uVar1);
    break;
  case 2:
    uVar1 = GetRegDat__9RegDatApiFiii(0x17,*(undefined4 *)(iVar2 + 8),0xffffffffffffffff);
    setTextString__7primWinFiPc(*(undefined4 *)(param_1 + 0x7c),6,uVar1);
    break;
  case 3:
    uVar1 = GetRegDat__9RegDatApiFiii(0x18,*(undefined4 *)(iVar2 + 8),0xffffffffffffffff);
    setTextString__7primWinFiPc(*(undefined4 *)(param_1 + 0x7c),6,uVar1);
    break;
  case 4:
    uVar1 = GetRegDat__9RegDatApiFiii(0x19,*(undefined4 *)(iVar2 + 8),0xffffffffffffffff);
    setTextString__7primWinFiPc(*(undefined4 *)(param_1 + 0x7c),6,uVar1);
    break;
  case 5:
    uVar1 = GetRegDat__9RegDatApiFiii(0x1e,*(undefined4 *)(iVar2 + 8),0xffffffffffffffff);
    setTextString__7primWinFiPc(*(undefined4 *)(param_1 + 0x7c),6,uVar1);
    break;
  case 6:
    uVar1 = GetRegDat__9RegDatApiFiii(0x22,*(undefined4 *)(iVar2 + 8),0xffffffffffffffff);
    setTextString__7primWinFiPc(*(undefined4 *)(param_1 + 0x7c),6,uVar1);
  }
  return;
}

/* JP: 0x004e6240  shop::mUpdateNoteWin()   [mUpdateNoteWin__4shopFv]  size=0x1630 */
void mUpdateNoteWin__4shopFv(int param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  undefined8 uVar6;
  ulong uVar7;
  int iVar8;
  int iVar9;
  undefined1 auStack_28e0 [8];
  undefined1 auStack_28d8 [8];
  undefined1 auStack_28d0 [8];
  undefined1 auStack_28c8 [8];
  uint auStack_28c0 [4];
  int aiStack_28b0 [4];
  int aiStack_28a0 [4];
  undefined1 auStack_2890 [256];
  undefined1 auStack_2790 [256];
  undefined1 auStack_2690 [256];
  undefined1 auStack_2590 [256];
  undefined1 auStack_2490 [256];
  undefined1 auStack_2390 [512];
  undefined1 auStack_2190 [8456];
  int aiStack_88 [4];
  int iStack_78;
  int iStack_74;
  undefined4 uStack_70;
  uint uStack_6c;
  int iStack_68;
  uint uStack_64;
  int iStack_60;
  uint uStack_5c;
  int iStack_58;
  int iStack_54;
  char acStack_50 [4];
  int iStack_4c;
  int iStack_48;
  int iStack_44;
  int iStack_40;
  int iStack_3c;
  uint uStack_38;
  int iStack_34;
  int iStack_30;
  char acStack_2c [4];
  char acStack_28 [4];
  int iStack_24;
  int iStack_20;
  int iStack_1c;
  int iStack_18;
  bool bStack_13;
  char cStack_12;
  char cStack_11;
  int iStack_10;
  
  iStack_10 = param_1;
  sprintf(auStack_2690,0x55a800,*(undefined4 *)(param_1 + 0x10c));
  setTextString__7primWinFiPc(*(undefined4 *)(iStack_10 + 0x7c),2,auStack_2690);
  sprintf(auStack_2590,0x55a800,*(undefined4 *)(iStack_10 + 0x114));
  setTextString__7primWinFiPc(*(undefined4 *)(iStack_10 + 0x7c),3,auStack_2590);
  sprintf(auStack_2490,0x55a808,
                  *(undefined4 *)
                   (*(int *)(iStack_10 + 0x100) + *(int *)(iStack_10 + 0x84) * 0x1c + 0x14));
  setTextString__7primWinFiPc(*(undefined4 *)(iStack_10 + 0x7c),4,auStack_2490);
  sprintf(auStack_2390,0x55a808,
                  *(undefined4 *)
                   (*(int *)(iStack_10 + 0x100) + *(int *)(iStack_10 + 0x84) * 0x1c + 0x18));
  setTextString__7primWinFiPc(*(undefined4 *)(iStack_10 + 0x7c),5,auStack_2390);
  if (*(char *)(iStack_10 + 0xc4) == '\0') {
    iVar9 = *(int *)(iStack_10 + 0x108) +
            (*(int *)(iStack_10 + 0x108) * (*(int *)(iStack_10 + 0xb8) + 1)) / 0x14;
  }
  else {
    iVar9 = *(int *)(iStack_10 + 0x108) -
            (*(int *)(iStack_10 + 0x108) * (*(int *)(iStack_10 + 0xb8) + 1)) / 10;
  }
  if (iVar9 == 0) {
    setTextAlpha__7primWinFii(*(undefined4 *)(iStack_10 + 0x7c),1,0);
    setTextAlpha__7primWinFii(*(undefined4 *)(iStack_10 + 0x7c),0,0);
  }
  else {
    setTextAlpha__7primWinFii(*(undefined4 *)(iStack_10 + 0x7c),1,0x80);
    setTextAlpha__7primWinFii(*(undefined4 *)(iStack_10 + 0x7c),0,0x80);
    if (*(int *)(iStack_10 + 0x108) < 1000) {
      sprintf(auStack_2790,0x55a810,shopMess_shopInfo_J,*(undefined4 *)(iStack_10 + 0x108));
    }
    else if (*(int *)(iStack_10 + 0x108) < 1000000) {
      sprintf(auStack_2790,0x55a820,shopMess_shopInfo_J,*(int *)(iStack_10 + 0x108) / 1000,
                      *(int *)(iStack_10 + 0x108) % 1000);
    }
    else {
      sprintf(auStack_2790,0x55a830,shopMess_shopInfo_J,
                      *(int *)(iStack_10 + 0x108) / 1000000,
                      (*(int *)(iStack_10 + 0x108) / 1000) % 1000,*(int *)(iStack_10 + 0x108) % 1000
                     );
    }
    if (*(char *)(iStack_10 + 0xc4) == '\0') {
      iStack_18 = 6;
      uStack_70 = 6;
    }
    else {
      iStack_18 = 5;
      uStack_70 = 5;
    }
    if (iVar9 < 1000) {
      sprintf(auStack_2890,0x55a810,(&shopMess_shopInfo_J)[iStack_18],iVar9);
    }
    else if (iVar9 < 1000000) {
      sprintf(auStack_2890,0x55a820,(&shopMess_shopInfo_J)[iStack_18],iVar9 / 1000,
                      iVar9 % 1000);
    }
    else {
      sprintf(auStack_2890,0x55a830,(&shopMess_shopInfo_J)[iStack_18],iVar9 / 1000000,
                      (iVar9 / 1000) % 1000,iVar9 % 1000);
    }
    setTextString__7primWinFiPc(*(undefined4 *)(iStack_10 + 0x7c),1,auStack_2790);
    setTextString__7primWinFiPc(*(undefined4 *)(iStack_10 + 0x7c),0,auStack_2890);
  }
  if (*(int *)(iStack_10 + 0xa8) < *(int *)(iStack_10 + 0xa4)) {
    sprintf(auStack_2190,0x55a840,*(int *)(iStack_10 + 0xa0) + 1,
                    *(undefined4 *)(iStack_10 + 0xac));
    setTextString__7primWinFiPc(*(undefined4 *)(iStack_10 + 0x7c),7,auStack_2190);
  }
  iVar9 = 0;
  do {
    if (*(int *)(iStack_10 + 0x11c) <= iVar9) {
      initScroll__7primWinFii(*(undefined4 *)(iStack_10 + 0x7c),0,0);
      return;
    }
    setTextAlpha__7primWinFii(*(undefined4 *)(iStack_10 + 0x58),iVar9,0);
    iStack_74 = *(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + *(char *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x80) * 0x20 +
                0x84;
    cVar1 = *(char *)(iStack_74 + iVar9 + 0x12);
    iVar2 = ourBtlSaveDat__10BtlSaveSec + cVar1 * 0xc0;
    iVar3 = iVar2 + 0x44;
    iVar4 = *(int *)(iStack_10 + 0x100) + *(int *)(iStack_10 + 0x84) * 0x1c;
    iStack_78 = iVar3;
    iStack_1c = iStack_74;
    aiStack_28b0[0] = GetRealPAtk__10BtlSaveSecFiPcPc(cVar1,0,0);
    aiStack_28b0[1] = GetRealPDef__10BtlSaveSecFiPcPc(cVar1,0,0);
    aiStack_28b0[2] = GetRealSAtk__10BtlSaveSecFiPcPc(cVar1,0,0);
    aiStack_28b0[3] = GetRealSDef__10BtlSaveSecFiPcPc(cVar1,0,0);
    iVar8 = *(int *)(iVar4 + 4);
    if (iVar8 == 4) {
      iStack_30 = -1;
      iStack_34 = GetRegDat__9RegDatApiFiii(0x32,*(undefined4 *)(iVar4 + 8),0xffffffffffffffff);
      uStack_38 = (uint)*(ushort *)(iStack_34 + 0x2a);
      acStack_2c[0] = '\x01';
      acStack_2c[1] = 1;
      acStack_2c[2] = 1;
      if (uStack_38 != 0) {
        cStack_12 = '\0';
        for (iStack_3c = 0; iStack_3c < 3; iStack_3c = iStack_3c + 1) {
          if ((*(char *)(iVar3 + iStack_3c + 0x2f) != -1) &&
             (iStack_40 = GetRegDat__9RegDatApiFiii(0x32,*(undefined1 *)(iVar3 + iStack_3c + 0x2f),
                                          0xffffffffffffffff),
             (uStack_38 & *(ushort *)(iStack_40 + 0x2a)) != 0)) {
            cStack_12 = '\x01';
            break;
          }
        }
        if (cStack_12 != '\0') {
          for (iVar8 = 0; iVar8 < 3; iVar8 = iVar8 + 1) {
            if (*(char *)(iVar3 + iVar8 + 0x2f) == -1) {
              acStack_2c[iVar8] = '\0';
            }
            else {
              iStack_44 = GetRegDat__9RegDatApiFiii(0x32,*(undefined1 *)(iVar3 + iVar8 + 0x2f),
                                          0xffffffffffffffff);
              if ((uStack_38 & *(ushort *)(iStack_44 + 0x2a)) == 0) {
                acStack_2c[iVar8] = '\0';
              }
            }
          }
        }
      }
      for (iStack_48 = 0; iStack_48 < 3; iStack_48 = iStack_48 + 1) {
        acStack_28[iStack_48] = *(char *)(iVar3 + iStack_48 + 0x2f);
        if ((long)acStack_28[iStack_48] == (long)*(int *)(iVar4 + 8)) {
          setTextAlpha__7primWinFii(*(undefined4 *)(iStack_10 + 0x58),iVar9,0x80);
          for (iStack_4c = 0; iStack_4c < 3; iStack_4c = iStack_4c + 1) {
            if (iStack_4c != iStack_48) {
              acStack_2c[iStack_4c] = '\0';
              bStack_13 = false;
            }
            else {
              acStack_2c[iStack_4c] = '\x01';
              bStack_13 = true;
            }
            bStack_13 = iStack_4c == iStack_48;
          }
        }
      }
      for (iVar8 = 0; iVar8 < 3; iVar8 = iVar8 + 1) {
        if (acStack_2c[iVar8] != '\0') {
          for (iVar3 = 0; iVar3 < 3; iVar3 = iVar3 + 1) {
            if (iVar3 == iVar8) {
              acStack_50[iVar3] = (char)*(undefined4 *)(iVar4 + 8);
            }
            else {
              acStack_50[iVar3] = acStack_28[iVar3];
            }
          }
          iVar3 = GetRealPAtk__10BtlSaveSecFiPcPc(cVar1,0,acStack_50);
          aiStack_88[iVar8] = iVar3;
          iVar3 = GetRealPDef__10BtlSaveSecFiPcPc(cVar1,0,acStack_50);
          aiStack_88[iVar8] = aiStack_88[iVar8] + iVar3;
          iVar3 = GetRealSAtk__10BtlSaveSecFiPcPc(cVar1,0,acStack_50);
          aiStack_88[iVar8] = aiStack_88[iVar8] + iVar3;
          iVar3 = GetRealSDef__10BtlSaveSecFiPcPc(cVar1,0,acStack_50);
          aiStack_88[iVar8] = aiStack_88[iVar8] + iVar3;
          if ((iStack_30 == -1) || (aiStack_88[iStack_30] < aiStack_88[iVar8])) {
            iStack_30 = iVar8;
            aiStack_28a0[0] = GetRealPAtk__10BtlSaveSecFiPcPc(cVar1,0,acStack_50);
            aiStack_28a0[1] = GetRealPDef__10BtlSaveSecFiPcPc(cVar1,0,acStack_50);
            aiStack_28a0[2] = GetRealSAtk__10BtlSaveSecFiPcPc(cVar1,0,acStack_50);
            aiStack_28a0[3] = GetRealSDef__10BtlSaveSecFiPcPc(cVar1,0,acStack_50);
          }
        }
      }
      cStack_11 = ((uint)*(ushort *)(iStack_34 + 4) & 1 << (*(byte *)(iVar2 + 0x46) & 0x1f)) != 0;
    }
    else if (iVar8 == 3) {
      if ((long)*(char *)(iVar2 + 0x72) == (long)*(int *)(iVar4 + 8)) {
        setTextAlpha__7primWinFii(*(undefined4 *)(iStack_10 + 0x58),iVar9,0x80);
      }
      iStack_24 = GetRegDat__9RegDatApiFiii(0x31,*(undefined4 *)(iVar4 + 8),0xffffffffffffffff);
      aiStack_28a0[0] = aiStack_28b0[0];
      aiStack_28a0[1] = GetRealPDef__10BtlSaveSecFiPcPc(cVar1,iStack_24,0);
      aiStack_28a0[2] = aiStack_28b0[2];
      aiStack_28a0[3] = GetRealSDef__10BtlSaveSecFiPcPc(cVar1,iStack_24,0);
      cStack_11 = ((uint)*(ushort *)(iStack_24 + 4) & 1 << (*(byte *)(iVar2 + 0x46) & 0x1f)) != 0;
    }
    else if (iVar8 == 2) {
      if ((long)*(char *)(iVar2 + 0x71) == (long)*(int *)(iVar4 + 8)) {
        setTextAlpha__7primWinFii(*(undefined4 *)(iStack_10 + 0x58),iVar9,0x80);
      }
      iStack_20 = GetRegDat__9RegDatApiFiii(0x30,*(undefined4 *)(iVar4 + 8),0xffffffffffffffff);
      aiStack_28a0[0] = GetRealPAtk__10BtlSaveSecFiPcPc(cVar1,iStack_20,0);
      aiStack_28a0[1] = aiStack_28b0[1];
      aiStack_28a0[2] = GetRealSAtk__10BtlSaveSecFiPcPc(cVar1,iStack_20,0);
      aiStack_28a0[3] = aiStack_28b0[3];
      cStack_11 = ((uint)*(ushort *)(iStack_20 + 6) & 1 << (*(byte *)(iVar2 + 0x46) & 0x1f)) != 0;
    }
    setPolyRGBA__7primWinFiiiii(*(undefined4 *)(iStack_10 + 0x58),iVar9 << 1,0x80,0x80,0x80,0x80);
    setPolyRGBA__7primWinFiiiii(*(undefined4 *)(iStack_10 + 0x58),iVar9 * 2 + 1,0x80,0x80,0x80,0x80);
    for (iVar8 = 0; iVar8 < 4; iVar8 = iVar8 + 1) {
      if (((*(int *)(iVar4 + 4) == 2) || (*(int *)(iVar4 + 4) == 3)) || (*(int *)(iVar4 + 4) == 4))
      {
        if (cStack_11 == '\0') {
          if (iVar8 == 0) {
            setPolyRGBA__7primWinFiiiii(*(undefined4 *)(iStack_10 + 0x58),iVar9 << 1,0x40,0x40,0x40,0x80);
            setPolyRGBA__7primWinFiiiii(*(undefined4 *)(iStack_10 + 0x58),iVar9 * 2 + 1,0x40,0x40,0x40,0x80);
          }
          auStack_28c0[iVar8] = 0x20;
          sprintf(auStack_28e0 + iVar8 * 8,0x559860);
        }
        else if (aiStack_28b0[iVar8] < aiStack_28a0[iVar8]) {
          aiStack_28b0[iVar8] = aiStack_28a0[iVar8];
          auStack_28c0[iVar8] = 0x80;
          sprintf(auStack_28e0 + iVar8 * 8,0x55a738,0x55a848);
        }
        else {
          if (aiStack_28b0[iVar8] <= aiStack_28a0[iVar8]) goto LAB_004e72b8;
          aiStack_28b0[iVar8] = aiStack_28a0[iVar8];
          auStack_28c0[iVar8] = 0x90;
          sprintf(auStack_28e0 + iVar8 * 8,0x55a738,0x55a850);
        }
      }
      else {
LAB_004e72b8:
        auStack_28c0[iVar8] = 0;
        sprintf(auStack_28e0 + iVar8 * 8,0x559860);
      }
    }
    sprintf(auStack_2890 + (iVar9 * 4 + 8) * 0x100,0x55a858,aiStack_28b0[0],auStack_28e0);
    setTextString__7primWinFiPc(*(undefined4 *)(iStack_10 + 0x7c),iVar9 * 4 + 8,
                    auStack_2890 + (iVar9 * 4 + 8) * 0x100);
    iStack_54 = getPT__7primWinFi(*(undefined4 *)(iStack_10 + 0x7c),iVar9 * 4 + 8);
    uVar5 = auStack_28c0[0];
    if ((int)auStack_28c0[0] < 0) {
      uVar5 = auStack_28c0[0] + 0xf;
    }
    SetCSA__8FontItemFUc(iStack_54,(int)uVar5 >> 4 & 0xff);
    cVar1 = (char)(auStack_28c0[0] & 0xf);
    if (((int)auStack_28c0[0] < 0) && ((auStack_28c0[0] & 0xf) != 0)) {
      cVar1 = cVar1 + -0x10;
    }
    *(char *)(iStack_54 + 0x5c) = cVar1;
    uVar7 = (ulong)*(byte *)(iStack_54 + 0x11) & 0xfffffffffffffffd | 2;
    *(char *)(iStack_54 + 0x11) = (char)uVar7;
    *(byte *)(iStack_54 + 0x10) =
         *(byte *)(iStack_54 + 0x10) & 0xfd | (byte)((uint)((uVar7 << 0x3e) >> 0x3f) << 1);
    uVar6 = sprintf(auStack_2890 + (iVar9 * 4 + 9) * 0x100,0x55a858,aiStack_28b0[1],
                            auStack_28d8);
    setTextString__7primWinFiPc(*(undefined4 *)(iStack_10 + 0x7c),iVar9 * 4 + 9,
                    auStack_2890 + (iVar9 * 4 + 9) * 0x100,uVar6);
    uStack_5c = auStack_28c0[1];
    iStack_58 = getPT__7primWinFi(*(undefined4 *)(iStack_10 + 0x7c),iVar9 * 4 + 9);
    uVar5 = uStack_5c;
    if ((int)uStack_5c < 0) {
      uVar5 = uStack_5c + 0xf;
    }
    SetCSA__8FontItemFUc(iStack_58,(int)uVar5 >> 4 & 0xff);
    cVar1 = (char)(uStack_5c & 0xf);
    if (((int)uStack_5c < 0) && ((uStack_5c & 0xf) != 0)) {
      cVar1 = cVar1 + -0x10;
    }
    *(char *)(iStack_58 + 0x5c) = cVar1;
    uVar7 = (ulong)*(byte *)(iStack_58 + 0x11) & 0xfffffffffffffffd | 2;
    *(char *)(iStack_58 + 0x11) = (char)uVar7;
    *(byte *)(iStack_58 + 0x10) =
         *(byte *)(iStack_58 + 0x10) & 0xfd | (byte)((uint)((uVar7 << 0x3e) >> 0x3f) << 1);
    sprintf(auStack_2890 + (iVar9 * 4 + 10) * 0x100,0x55a858,aiStack_28b0[2],auStack_28d0);
    setTextString__7primWinFiPc(*(undefined4 *)(iStack_10 + 0x7c),iVar9 * 4 + 10,
                    auStack_2890 + (iVar9 * 4 + 10) * 0x100);
    uStack_64 = auStack_28c0[2];
    iStack_60 = getPT__7primWinFi(*(undefined4 *)(iStack_10 + 0x7c),iVar9 * 4 + 10);
    uVar5 = uStack_64;
    if ((int)uStack_64 < 0) {
      uVar5 = uStack_64 + 0xf;
    }
    SetCSA__8FontItemFUc(iStack_60,(int)uVar5 >> 4 & 0xff);
    cVar1 = (char)(uStack_64 & 0xf);
    if (((int)uStack_64 < 0) && ((uStack_64 & 0xf) != 0)) {
      cVar1 = cVar1 + -0x10;
    }
    *(char *)(iStack_60 + 0x5c) = cVar1;
    uVar7 = (ulong)*(byte *)(iStack_60 + 0x11) & 0xfffffffffffffffd | 2;
    *(char *)(iStack_60 + 0x11) = (char)uVar7;
    *(byte *)(iStack_60 + 0x10) =
         *(byte *)(iStack_60 + 0x10) & 0xfd | (byte)((uint)((uVar7 << 0x3e) >> 0x3f) << 1);
    sprintf(auStack_2890 + (iVar9 * 4 + 0xb) * 0x100,0x55a858,aiStack_28b0[3],auStack_28c8);
    setTextString__7primWinFiPc(*(undefined4 *)(iStack_10 + 0x7c),iVar9 * 4 + 0xb,
                    auStack_2890 + (iVar9 * 4 + 0xb) * 0x100);
    uStack_6c = auStack_28c0[3];
    iStack_68 = getPT__7primWinFi(*(undefined4 *)(iStack_10 + 0x7c),iVar9 * 4 + 0xb);
    uVar5 = uStack_6c;
    if ((int)uStack_6c < 0) {
      uVar5 = uStack_6c + 0xf;
    }
    SetCSA__8FontItemFUc(iStack_68,(int)uVar5 >> 4 & 0xff);
    cVar1 = (char)(uStack_6c & 0xf);
    if (((int)uStack_6c < 0) && ((uStack_6c & 0xf) != 0)) {
      cVar1 = cVar1 + -0x10;
    }
    *(char *)(iStack_68 + 0x5c) = cVar1;
    uVar7 = (ulong)*(byte *)(iStack_68 + 0x11) & 0xfffffffffffffffd | 2;
    *(char *)(iStack_68 + 0x11) = (char)uVar7;
    *(byte *)(iStack_68 + 0x10) =
         *(byte *)(iStack_68 + 0x10) & 0xfd | (byte)((uint)((uVar7 << 0x3e) >> 0x3f) << 1);
    iVar9 = iVar9 + 1;
  } while( true );
}

/* JP: 0x004e7870  shop::mCalcPoint(bool)   [mCalcPoint__4shopFb]  size=0x138 */
undefined4 mCalcPoint__4shopFb(int param_1,char param_2)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (*(int *)(param_1 + 0xb8) == 3) {
    uVar1 = 0;
  }
  else {
    if (param_2 == '\0') {
      if ((*(int *)(param_1 + 0xb8) != 0) &&
         (*(int *)(param_1 + 0x10c) < *(int *)(&shopPointTbl + *(int *)(param_1 + 0xb8) * 4))) {
        *(int *)(param_1 + 0xb8) = *(int *)(param_1 + 0xb8) + -1;
        uVar1 = 1;
      }
    }
    else if (*(int *)(&shopPointTbl + *(int *)(param_1 + 0xb8) * 4) <= *(int *)(param_1 + 0x10c)) {
      *(int *)(param_1 + 0xb8) = *(int *)(param_1 + 0xb8) + 1;
      uVar1 = 1;
    }
    *(int *)(param_1 + 0x114) =
         *(int *)(&shopPointTbl + *(int *)(param_1 + 0xb8) * 4) - *(int *)(param_1 + 0x10c);
  }
  return uVar1;
}

/* JP: 0x004e79b0  shop::mSetWeaponIcon(primWin*, WEAPONParam*, int)   [mSetWeaponIcon__4shopFP7primWinP11WEAPONParami]  size=0xf0 */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void mSetWeaponIcon__4shopFP7primWinP11WEAPONParami
               (undefined8 param_1,undefined4 param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  ushort uVar2;
  undefined4 auStack_a0 [28];
  undefined4 uStack_30;
  int iStack_20;
  undefined4 uStack_10;
  
  auStack_a0[0] = (int)__8729;
  auStack_a0[1] = (int)((ulong)__8729 >> 0x20);
  auStack_a0[2] = DAT_00554138;
  auStack_a0[3] = DAT_0055413c;
  auStack_a0[4] = (int)_DAT_00554140;
  auStack_a0[5] = (int)((ulong)_DAT_00554140 >> 0x20);
  auStack_a0[6] = DAT_00554148;
  auStack_a0[7] = DAT_0055414c;
  auStack_a0[8] = (int)_DAT_00554150;
  auStack_a0[9] = (int)((ulong)_DAT_00554150 >> 0x20);
  auStack_a0[10] = DAT_00554158;
  auStack_a0[0xb] = DAT_0055415c;
  auStack_a0[0xc] = (int)_DAT_00554160;
  auStack_a0[0xd] = (int)((ulong)_DAT_00554160 >> 0x20);
  auStack_a0[0xe] = DAT_00554168;
  auStack_a0[0xf] = DAT_0055416c;
  auStack_a0[0x10] = (int)_DAT_00554170;
  auStack_a0[0x11] = (int)((ulong)_DAT_00554170 >> 0x20);
  auStack_a0[0x12] = DAT_00554178;
  auStack_a0[0x13] = DAT_0055417c;
  auStack_a0[0x14] = (int)_DAT_00554180;
  auStack_a0[0x15] = (int)((ulong)_DAT_00554180 >> 0x20);
  auStack_a0[0x16] = DAT_00554188;
  auStack_a0[0x17] = DAT_0055418c;
  iVar1 = 0;
  uVar2 = 1;
  while( true ) {
    if (0xb < iVar1) {
      return;
    }
    if ((uVar2 & *(ushort *)(param_3 + 6)) != 0) break;
    iVar1 = iVar1 + 1;
    uVar2 = uVar2 << 1;
  }
  uStack_30 = param_2;
  iStack_20 = param_3;
  uStack_10 = param_4;
  setTexBlock__7primWinFiii(param_2,param_4,auStack_a0[iVar1 * 2],auStack_a0[iVar1 * 2 + 1]);
  return;
}

/* JP: 0x004e7aa0  shop::mMakeBuyList()   [mMakeBuyList__4shopFv]  size=0x154 */
void mMakeBuyList__4shopFv(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  char *pcVar3;
  char *pcVar4;
  int iVar5;
  
  uVar1 = __nwa__FUi(0x700);
  *(undefined4 *)(param_1 + 0x100) = uVar1;
  iVar5 = *(int *)(param_1 + 0x100);
  *(undefined4 *)(param_1 + 0xa4) = 0;
  pcVar3 = (&shopTbl)[*(int *)(param_1 + 0xb0)];
LAB_004e7bc8:
  do {
    if (*pcVar3 == '\0') {
      return;
    }
    if (*pcVar3 == '\x05') {
      iVar2 = (int)pcVar3[1];
      if (pcVar3[1] < '\0') {
        iVar2 = iVar2 + 7;
      }
      if (((uint)*(byte *)(*(int *)(param_1 + 0x120) + (iVar2 >> 3) + 0x160) &
          1 << ((int)pcVar3[1] & 7U)) != 0) {
        pcVar3 = pcVar3 + 2;
        goto LAB_004e7bc8;
      }
    }
    pcVar4 = pcVar3 + 1;
    *(int *)(iVar5 + 4) = (int)*pcVar3;
    pcVar3 = pcVar3 + 2;
    *(int *)(iVar5 + 8) = (int)*pcVar4;
    iVar5 = iVar5 + 0x1c;
    *(int *)(param_1 + 0xa4) = *(int *)(param_1 + 0xa4) + 1;
  } while( true );
}

/* JP: 0x004e7c00  shop::mMakeSellList()   [mMakeSellList__4shopFv]  size=0x570 */
void mMakeSellList__4shopFv(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  long lVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined4 uStack_1c;
  undefined4 uStack_14;
  
  if (*(int *)(param_1 + 0x100) != 0) {
    __dla__FPv(*(undefined4 *)(param_1 + 0x100));
    *(undefined4 *)(param_1 + 0x100) = 0;
  }
  uVar2 = __nwa__FUi(0x1f80);
  *(undefined4 *)(param_1 + 0x100) = uVar2;
  iVar4 = *(int *)(param_1 + 0x100);
  *(undefined4 *)(param_1 + 0xa4) = 0;
  iVar3 = *(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + *(char *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x80) * 0x20 + 0x84;
  for (iVar6 = 0; iVar6 < 0x40; iVar6 = iVar6 + 1) {
    if (*(char *)(*(int *)(param_1 + 0x120) + iVar6) != '\0') {
      *(undefined4 *)(iVar4 + 4) = 1;
      *(int *)(iVar4 + 8) = iVar6;
      *(uint *)(iVar4 + 0x18) = (uint)*(byte *)(*(int *)(param_1 + 0x120) + iVar6);
      *(undefined4 *)(iVar4 + 0x14) = 0;
      iVar4 = iVar4 + 0x1c;
      *(int *)(param_1 + 0xa4) = *(int *)(param_1 + 0xa4) + 1;
    }
  }
  lVar5 = 0;
  while (lVar5 < 0x60) {
    iVar6 = (int)lVar5;
    if (*(char *)(*(int *)(param_1 + 0x120) + iVar6 + 0x80) != '\0') {
      *(undefined4 *)(iVar4 + 4) = 2;
      *(int *)(iVar4 + 8) = iVar6;
      *(uint *)(iVar4 + 0x18) = (uint)*(byte *)(*(int *)(param_1 + 0x120) + iVar6 + 0x80);
      *(undefined4 *)(iVar4 + 0x14) = 0;
      for (uStack_14 = 0; uStack_14 < *(int *)(param_1 + 0x11c); uStack_14 = uStack_14 + 1) {
        if (*(char *)(ourBtlSaveDat__10BtlSaveSec + *(char *)(iVar3 + uStack_14 + 0x12) * 0xc0 + 0x71) == lVar5) {
          *(int *)(iVar4 + 0x14) = *(int *)(iVar4 + 0x14) + 1;
        }
      }
      if (*(int *)(iVar4 + 0x14) < *(int *)(iVar4 + 0x18)) {
        iVar4 = iVar4 + 0x1c;
        *(int *)(param_1 + 0xa4) = *(int *)(param_1 + 0xa4) + 1;
      }
    }
    lVar5 = (long)(iVar6 + 1);
  }
  lVar5 = 0;
  while (lVar5 < 0x30) {
    iVar6 = (int)lVar5;
    if (*(char *)(*(int *)(param_1 + 0x120) + iVar6 + 0xe0) != '\0') {
      *(undefined4 *)(iVar4 + 4) = 3;
      *(int *)(iVar4 + 8) = iVar6;
      *(uint *)(iVar4 + 0x18) = (uint)*(byte *)(*(int *)(param_1 + 0x120) + iVar6 + 0x80);
      *(undefined4 *)(iVar4 + 0x14) = 0;
      for (uStack_1c = 0; uStack_1c < *(int *)(param_1 + 0x11c); uStack_1c = uStack_1c + 1) {
        if (*(char *)(ourBtlSaveDat__10BtlSaveSec + *(char *)(iVar3 + uStack_1c + 0x12) * 0xc0 + 0x72) == lVar5) {
          *(int *)(iVar4 + 0x14) = *(int *)(iVar4 + 0x14) + 1;
        }
      }
      if (*(int *)(iVar4 + 0x14) < *(int *)(iVar4 + 0x18)) {
        iVar4 = iVar4 + 0x1c;
        *(int *)(param_1 + 0xa4) = *(int *)(param_1 + 0xa4) + 1;
      }
    }
    lVar5 = (long)(iVar6 + 1);
  }
  lVar5 = 0;
  while (lVar5 < 0x50) {
    iVar6 = (int)lVar5;
    if (*(char *)(*(int *)(param_1 + 0x120) + iVar6 + 0x110) != '\0') {
      *(undefined4 *)(iVar4 + 4) = 4;
      *(int *)(iVar4 + 8) = iVar6;
      *(uint *)(iVar4 + 0x18) = (uint)*(byte *)(*(int *)(param_1 + 0x120) + iVar6 + 0x110);
      *(undefined4 *)(iVar4 + 0x14) = 0;
      for (iVar8 = 0; iVar8 < *(int *)(param_1 + 0x11c); iVar8 = iVar8 + 1) {
        cVar1 = *(char *)(iVar3 + iVar8 + 0x12);
        for (iVar7 = 0; iVar7 < 3; iVar7 = iVar7 + 1) {
          if (*(char *)(ourBtlSaveDat__10BtlSaveSec + cVar1 * 0xc0 + iVar7 + 0x73) == lVar5) {
            *(int *)(iVar4 + 0x14) = *(int *)(iVar4 + 0x14) + 1;
          }
        }
      }
      if (*(int *)(iVar4 + 0x14) < *(int *)(iVar4 + 0x18)) {
        iVar4 = iVar4 + 0x1c;
        *(int *)(param_1 + 0xa4) = *(int *)(param_1 + 0xa4) + 1;
      }
    }
    lVar5 = (long)(iVar6 + 1);
  }
  for (iVar3 = 0; iVar3 < 0x50; iVar3 = iVar3 + 1) {
    if (*(char *)(*(int *)(param_1 + 0x120) + iVar3 + 0x174) != '\0') {
      *(undefined4 *)(iVar4 + 4) = 6;
      *(int *)(iVar4 + 8) = iVar3;
      *(uint *)(iVar4 + 0x18) = (uint)*(byte *)(*(int *)(param_1 + 0x120) + iVar3);
      *(undefined4 *)(iVar4 + 0x14) = 0;
      iVar4 = iVar4 + 0x1c;
      *(int *)(param_1 + 0xa4) = *(int *)(param_1 + 0xa4) + 1;
    }
  }
  return;
}

/* JP: 0x004e8170  shop::mCheckSellItem()   [mCheckSellItem__4shopFv]  size=0x1a8 */
undefined4 mCheckSellItem__4shopFv(int param_1)

{
  int iVar1;
  
  for (iVar1 = 0; iVar1 < 0x40; iVar1 = iVar1 + 1) {
    if (*(char *)(*(int *)(param_1 + 0x120) + iVar1) != '\0') {
      return 1;
    }
  }
  for (iVar1 = 0; iVar1 < 0x60; iVar1 = iVar1 + 1) {
    if (*(char *)(*(int *)(param_1 + 0x120) + iVar1 + 0x80) != '\0') {
      return 1;
    }
  }
  for (iVar1 = 0; iVar1 < 0x30; iVar1 = iVar1 + 1) {
    if (*(char *)(*(int *)(param_1 + 0x120) + iVar1 + 0xe0) != '\0') {
      return 1;
    }
  }
  for (iVar1 = 0; iVar1 < 0x50; iVar1 = iVar1 + 1) {
    if (*(char *)(*(int *)(param_1 + 0x120) + iVar1 + 0x110) != '\0') {
      return 1;
    }
  }
  iVar1 = 0;
  while( true ) {
    if (0x4f < iVar1) {
      return 0;
    }
    if (*(char *)(*(int *)(param_1 + 0x120) + iVar1 + 0x174) != '\0') break;
    iVar1 = iVar1 + 1;
  }
  return 1;
}

/* JP: 0x004e8320  shop::mCalcCurrentMax()   [mCalcCurrentMax__4shopFv]  size=0x158 */
void mCalcCurrentMax__4shopFv(int param_1)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)(*(int *)(param_1 + 0x100) + *(int *)(param_1 + 0x84) * 0x1c);
  if (*(char *)(param_1 + 0xc4) == '\0') {
    *(int *)(param_1 + 0x110) = piVar1[4];
  }
  else {
    iVar2 = *piVar1 - (*piVar1 * (*(int *)(param_1 + 0xb8) + 1)) / 10;
    if (iVar2 == 0) {
      trap(7);
    }
    iVar2 = piVar1[3] +
            (*(int *)(param_1 + 0x104) -
            (*(int *)(param_1 + 0x108) -
            (*(int *)(param_1 + 0x108) * (*(int *)(param_1 + 0xb8) + 1)) / 10)) / iVar2 + 1;
    if (piVar1[4] < iVar2) {
      iVar2 = piVar1[4];
    }
    *(int *)(param_1 + 0x110) = iVar2;
  }
  return;
}

/* JP: 0x004e8480  shop::~shop()   [@24@__dt__4shopFv]  size=0x8 */
int _24___dt__4shopFv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x18;
  if (iVar1 != 0) {
    *(undefined1 **)(param_1 + -4) = &__vt__4shop;
    *(undefined4 *)(param_1 + 8) = 0x409790;
    *(undefined4 *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 700) = *(undefined4 *)(param_1 + 0xf4);
    SetCurrentCash__15SaveMenuSectionFi(*(undefined4 *)(param_1 + 0xec));
    if (*(int *)(param_1 + 0xe8) != 0) {
      __dla__FPv(*(undefined4 *)(param_1 + 0xe8));
      *(undefined4 *)(param_1 + 0xe8) = 0;
    }
    if (*(int *)(param_1 + 0x118) != 0) {
      DelayDeleteRequest__11shopCaptureFv(*(undefined4 *)(param_1 + 0x118));
      *(undefined4 *)(param_1 + 0x118) = 0;
    }
    if (m_pPT != 0) {
      __dt__7primTexFv(m_pPT,1);
      m_pPT = 0;
    }
    Dispose__7CPollerFP7CPolObj(app__4CApp + 0x48,iVar1);
    if (*(int *)(param_1 + 0x30) != 0) {
      DelayDeleteRequest__9primSoundFv(*(undefined4 *)(param_1 + 0x30));
      *(undefined4 *)(param_1 + 0x30) = 0;
    }
    __dt__4FontFv(param_1 + 0x2c,0xffffffffffffffff);
    __dt__4FontFv(param_1 + 0x28,0xffffffffffffffff);
    if (iVar1 != -0x18) {
      *(undefined1 **)(param_1 + 8) = &__vt__17DelayDeleteObject;
    }
    __dt__7CPolObjFv(iVar1,0);
    if (0 < param_2) {
      __dl__FPv(iVar1);
    }
  }
  return iVar1;
}
