/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: worldMap   functions: 35
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/worldMap.md).
 */

/* JP: 0x00506be0  worldMap::DVD_CBFunc(int, BufMemory*, int, char*, void*)   [DVD_CBFunc__8worldMapFiP9BufMemoryiPcPv]  size=0xb8 */
undefined8
DVD_CBFunc__8worldMapFiP9BufMemoryiPcPv
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

/* JP: 0x00506ca0  worldMap::CMN(int, void*, CmdMenu*)   [CMN__8worldMapFiPvP7CmdMenu]  size=0x38 */
undefined4 CMN__8worldMapFiPvP7CmdMenu(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  m_MenuNum = param_1;
  m_pUserData = param_2;
  m_pCM = param_3;
  return m_FadeReady;
}

/* JP: 0x00506ce0  worldMap::worldMap()   [__ct__8worldMapFv]  size=0x128 */
int __ct__8worldMapFv(int param_1)

{
  __ct__7CPolObjFv(param_1);
  *(undefined4 *)(param_1 + 0x18) = 0;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  *(undefined1 **)(param_1 + 0x20) = &__vt__17DelayDeleteObject;
  *(undefined1 **)(param_1 + 0x14) = &__vt__8worldMap;
  *(undefined4 *)(param_1 + 0x20) = 0x4098e0;
  __ct__4FontFv(param_1 + 0x28);
  *(undefined1 *)(param_1 + 0xdc) = 0;
  *(undefined4 *)(param_1 + 0x44) = 0;
  *(undefined4 *)(param_1 + 0xac) = 0;
  *(undefined4 *)(param_1 + 0x48) = 0;
  *(undefined4 *)(param_1 + 0x40) = 0;
  *(undefined1 *)(param_1 + 0x8c) = 0;
  *(undefined4 *)(param_1 + 200) = 0;
  *(undefined4 *)(param_1 + 0xcc) = 0;
  *(undefined4 *)(param_1 + 0xd0) = 0;
  *(undefined4 *)(param_1 + 0x68) = 0;
  *(undefined4 *)(param_1 + 0x6c) = 0;
  *(undefined4 *)(param_1 + 0xb0) = 0;
  *(undefined4 *)(param_1 + 0x90) = 0;
  *(undefined4 *)(param_1 + 0x30) = 0;
  *(undefined4 *)(param_1 + 0x34) = 0;
  *(undefined4 *)(param_1 + 0x2c) = 0;
  *(undefined4 *)(param_1 + 0x60) = 0;
  *(undefined4 *)(param_1 + 100) = 0;
  *(undefined4 *)(param_1 + 0x920) = 0;
  *(undefined4 *)(param_1 + 0x924) = 0;
  *(undefined4 *)(param_1 + 0x928) = 0;
  return param_1;
}

/* JP: 0x00506e10  worldMap::~worldMap()   [__dt__8worldMapFv]  size=0x13c */
int __dt__8worldMapFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 0x14) = &__vt__8worldMap;
    *(undefined4 *)(param_1 + 0x20) = 0x4098e0;
    Dispose__7CPollerFP7CPolObj(app__4CApp + 0x48,param_1);
    if (*(int *)(param_1 + 0x2c) != 0) {
      __dt__7primTexFv(*(undefined4 *)(param_1 + 0x2c),1);
      *(undefined4 *)(param_1 + 0x2c) = 0;
    }
    if (*(int *)(param_1 + 0x60) != 0) {
      DelayDeleteRequest__9primSoundFv(*(undefined4 *)(param_1 + 0x60));
      *(undefined4 *)(param_1 + 0x60) = 0;
    }
    ReleaseField__7MenuObjFv();
    ReleaseCmdMenu__7MenuObjFv();
    __dt__4FontFv(param_1 + 0x28,0xffffffffffffffff);
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

/* JP: 0x00506f50  worldMap::initialize(int, int, int)   [initialize__8worldMapFiii]  size=0x178 */
void initialize__8worldMapFiii(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  long lVar2;
  int iVar3;
  
  *(undefined4 *)(param_1 + 0x8d8) = param_2;
  *(undefined4 *)(param_1 + 0x8e4) = param_3;
  *(undefined4 *)(param_1 + 0x8e8) = param_4;
  *(undefined4 *)(param_1 + 0x91c) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x8e8) = 0;
  for (iVar3 = 0; iVar3 < 4; iVar3 = iVar3 + 1) {
    *(undefined1 *)(param_1 + iVar3 + 0x8ed) = (&gp0xffff8210)[iVar3];
  }
  mReadDataRequest__8worldMapFv(param_1);
  Entry__7CPollerFP7CPolObjib(app__4CApp + 0x48,param_1,0x80,0);
  *(undefined4 *)(param_1 + 0xd4) = 0;
  lVar2 = __nw__FUi(0x30);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = __ct__9primSoundFv(lVar2);
  }
  *(undefined4 *)(param_1 + 0x60) = uVar1;
  initialize__9primSoundFv(*(undefined4 *)(param_1 + 0x60));
  lVar2 = __nw__FUi(0x38);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = __ct__9primMusicFv(lVar2);
  }
  *(undefined4 *)(param_1 + 100) = uVar1;
  initialize__9primMusicFi(*(undefined4 *)(param_1 + 100),0);
  CreateField__7MenuObjFv();
  CreateCmdMenu__7MenuObjFv();
  return;
}

/* JP: 0x005070d0  worldMap::start()   [start__8worldMapFv]  size=0x74 */
void start__8worldMapFv(int param_1)

{
  undefined4 uVar1;
  long lVar2;
  
  *(undefined1 *)(param_1 + 0xdc) = 1;
  lVar2 = __nw__FUi(0x34);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = __ct__12worldMapFadeFv(lVar2);
  }
  *(undefined4 *)(param_1 + 0x44) = uVar1;
  initialize__12worldMapFadeFv(*(undefined4 *)(param_1 + 0x44));
  return;
}

/* JP: 0x00507150  worldMap::mReadDataRequest()   [mReadDataRequest__8worldMapFv]  size=0x80 */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void mReadDataRequest__8worldMapFv(int param_1)

{
  undefined8 uVar1;
  undefined1 auStack_130 [256];
  undefined *apuStack_30 [4];
  undefined *puStack_20;
  int iStack_10;
  
  iStack_10 = param_1;
  apuStack_30[0] = (undefined *)__5386;
  apuStack_30[1] = (undefined *)(int)((ulong)__5386 >> 0x20);
  apuStack_30[2] = PTR__5383_005555b8;
  apuStack_30[3] = PTR__5384_005555bc;
  puStack_20 = PTR__5385_005555c0;
  m_TexRead = 0;
  uVar1 = SetPathname__7SysToolFPcPCc(auStack_130,apuStack_30[*(int *)(param_1 + 0x8d8)]);
  ReadOrder__11DvdromOrderFPCcPFiP9BufMemoryiPcPv_iiPvi(Dvdromour__11DvdromOrder,uVar1,0x506be0,0,iStack_10,0);
  return;
}

/* JP: 0x005071d0  worldMap::Polling()   [Polling__8worldMapFv]  size=0xc84 */
undefined8 Polling__8worldMapFv(int param_1)

{
  ushort uVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  undefined2 *puVar5;
  long lVar6;
  
  iVar3 = GetActive__4CPadFi(0);
  uVar1 = *(ushort *)(*(int *)(&m_pCoreArray__4CPad + *(int *)(iVar3 + 4) * 4) + 0x6c);
  switch(*(undefined4 *)(param_1 + 0xd4)) {
  case 0:
    if (m_TexRead != '\0') {
      if (*(int *)(param_1 + 0x2c) != 0) {
        __dt__7primTexFv(*(undefined4 *)(param_1 + 0x2c),1);
        *(undefined4 *)(param_1 + 0x2c) = 0;
      }
      *(undefined4 *)(param_1 + 0x2c) = m_pPT;
      m_pPT = 0;
      mSetupFont__8worldMapFv(param_1);
      *(undefined4 *)(param_1 + 0xd4) = 1;
      lVar6 = __nw__FUi(0x18);
      uVar4 = 0;
      if (lVar6 != 0) {
        uVar4 = __ct__11worldMapThmFv(lVar6);
      }
      *(undefined4 *)(param_1 + 0xac) = uVar4;
      initialize__11worldMapThmFP7primTex
                (*(undefined4 *)(param_1 + 0xac),*(undefined4 *)(param_1 + 0x2c));
      play__9primMusicFPc(*(undefined4 *)(param_1 + 100),0x55f0b8);
    }
    break;
  case 1:
    if ((*(char *)(param_1 + 0xdc) != '\0') && (lVar6 = IsReadyField__7MenuObjFv(), lVar6 != 0)) {
      fadeIn__12worldMapFadeFi(*(undefined4 *)(param_1 + 0x44),0x1e);
      *(undefined4 *)(param_1 + 0xd4) = 2;
    }
    break;
  case 2:
    mScriptFilter__8worldMapFPQ28worldMap11SUBMAP_DATA(param_1,0x554e40);
    mSetupWorldMap__8worldMapFv(param_1);
    mSetupMenuWin__8worldMapFv(param_1);
    if (*(int *)(param_1 + 0x8cc) == 0) {
      *(undefined4 *)(param_1 + 0xd4) = 9;
    }
    else {
      *(undefined4 *)(param_1 + 0xd4) = 6;
      *(undefined4 *)(param_1 + 0xd8) = 0;
      *(undefined4 *)(param_1 + 0x8d4) = 0;
    }
    break;
  case 6:
    if ((*(char *)(*(int *)(param_1 + 0x44) + 0x2c) == '\0') &&
       (cVar2 = mNewPointDemo__8worldMapFv(param_1), cVar2 == '\0')) {
      *(undefined4 *)(param_1 + 0xd4) = 8;
    }
    break;
  case 8:
    *(undefined4 *)(param_1 + 0xd4) = 9;
    break;
  case 9:
    if (*(int *)(param_1 + 0x91c) == -1) {
      *(undefined4 *)(param_1 + 0xd4) = 0x10;
    }
    else if (*(int *)(param_1 + 0x88) == 0) {
      mSetupTutorialWin__8worldMapFv(param_1);
      *(undefined4 *)(param_1 + 0xd4) = 10;
    }
    break;
  case 10:
    if (*(ushort *)(*(int *)(param_1 + 0x924) + 0x80) <
        *(ushort *)(*(int *)(param_1 + 0x924) + 0x76)) {
      if ((uVar1 & 0x2000) != 0) {
        Finish__11MenuMessageFv(*(undefined4 *)(param_1 + 0x924));
      }
    }
    else {
      *(byte *)(*(int *)(param_1 + 0x928) + 0x12) =
           *(byte *)(*(int *)(param_1 + 0x928) + 0x12) & 0xfe | 1;
      if ((uVar1 & 0x2000) != 0) {
        play__9primSoundFi(*(undefined4 *)(param_1 + 0x60),2);
        if (*(int *)(param_1 + 0x920) != 0) {
          DelayDeleteRequest__7primWinFv(*(undefined4 *)(param_1 + 0x920));
          *(undefined4 *)(param_1 + 0x920) = 0;
        }
        *(undefined4 *)(param_1 + 0xd4) = 0x10;
      }
    }
    break;
  case 0xb:
    mIsMenuFade__8worldMapFv(param_1);
    if (*(char *)(*(int *)(param_1 + 0x44) + 0x2c) == '\0') {
      kill__11worldMapThmFv(*(undefined4 *)(param_1 + 0xac));
      mReleaseSelectWin__8worldMapFv(param_1);
      mReleaseMenuWin__8worldMapFv(param_1);
      mReleaseWorldMap__8worldMapFv(param_1);
      *(undefined4 *)(param_1 + 0xd4) = 0;
      mReleaseFont__8worldMapFv(param_1);
      if (*(int *)(param_1 + 0xac) != 0) {
        __dt__11worldMapThmFv(*(undefined4 *)(param_1 + 0xac),1);
        *(undefined4 *)(param_1 + 0xac) = 0;
      }
      if (*(int *)(param_1 + 0x48) != 0) {
        iVar3 = *(int *)(param_1 + 0x48);
        if (iVar3 != 0) {
          (**(code **)(*(int *)(iVar3 + 0x14) + 8))(iVar3,1);
        }
        *(undefined4 *)(param_1 + 0x48) = 0;
      }
    }
    break;
  case 0xc:
    lVar6 = mIsMenuFade__8worldMapFv(param_1);
    if (lVar6 == 0) {
      m_FadeReady = 1;
      *(undefined1 *)(*(int *)(param_1 + 0x40) + 0x3d) = 0x11;
      *(undefined4 *)(param_1 + 0xd4) = 0xd;
    }
    break;
  case 0xd:
    if (m_MenuNum == 1) {
      mReleaseSelectWin__8worldMapFv(param_1);
      mReleaseMenuWin__8worldMapFv(param_1);
      mReleaseWorldMap__8worldMapFv(param_1);
      *(undefined4 *)(param_1 + 0xd4) = 0xe;
    }
    break;
  case 0xe:
    if (m_MenuNum == 4) {
      mReleaseFont__8worldMapFv(param_1);
      if (*(int *)(param_1 + 0x44) != 0) {
        iVar3 = *(int *)(param_1 + 0x44);
        if (iVar3 != 0) {
          (**(code **)(*(int *)(iVar3 + 0x14) + 8))(iVar3,1);
        }
        *(undefined4 *)(param_1 + 0x44) = 0;
      }
      if (*(int *)(param_1 + 0xac) != 0) {
        __dt__11worldMapThmFv(*(undefined4 *)(param_1 + 0xac),1);
        *(undefined4 *)(param_1 + 0xac) = 0;
      }
      if (*(int *)(param_1 + 0x48) != 0) {
        iVar3 = *(int *)(param_1 + 0x48);
        if (iVar3 != 0) {
          (**(code **)(*(int *)(iVar3 + 0x14) + 8))(iVar3,1);
        }
        *(undefined4 *)(param_1 + 0x48) = 0;
      }
      if (*(int *)(param_1 + 100) != 0) {
        DelayDeleteRequest__9primMusicFv(*(undefined4 *)(param_1 + 100));
        *(undefined4 *)(param_1 + 100) = 0;
      }
      (**(code **)(*(int *)(param_1 + 0x20) + 0xc))();
    }
    else if (m_MenuNum == 2) {
      *(undefined4 *)(param_1 + 0xd4) = 0xf;
    }
    break;
  case 0xf:
    mSetupWorldMap__8worldMapFv(param_1);
    mSetupMenuWin__8worldMapFv(param_1);
    mSetupSelectWin__8worldMapFv(param_1);
    mSetupMenuFadeIn__8worldMapFv(param_1);
    *(undefined4 *)(param_1 + 0xd4) = 0x11;
    break;
  case 0x10:
    mSetupSelectWin__8worldMapFv(param_1);
    mSetupMenuFadeIn__8worldMapFv(param_1);
    *(undefined4 *)(param_1 + 0xd4) = 0x11;
    break;
  case 0x11:
    lVar6 = mIsMenuFade__8worldMapFv(param_1);
    if ((lVar6 == 0) && (*(int *)(param_1 + 0x88) == 0)) {
      mSetupSelectWinCursor__8worldMapFv(param_1);
      *(undefined4 *)(param_1 + 0xd4) = 0x12;
    }
    break;
  case 0x12:
    if (*(char *)(*(int *)(param_1 + 0x44) + 0x2c) == '\0') {
      uVar4 = mCheckKey__8worldMapFi
                        (param_1,*(ushort *)
                                  (*(int *)(&m_pCoreArray__4CPad + *(int *)(iVar3 + 4) * 4) + 0x70)
                                 & 0xf0 | uVar1);
      *(undefined4 *)(param_1 + 0xd4) = uVar4;
      iVar3 = *(int *)(param_1 + 0xd4);
      if (iVar3 == 0xc) {
        m_MenuNum = 0;
        m_FadeReady = 0;
        lVar6 = __nw__FUi(0x17f8);
        uVar4 = 0;
        if (lVar6 != 0) {
          uVar4 = __ct__7CmdMenuFsPFiPvP7CmdMenu_iPv(lVar6,0,0x506ca0,param_1 + 0x24);
        }
        *(undefined4 *)(param_1 + 0x40) = uVar4;
        iVar3 = GraveYardEnable__Fi(0xffffffffffffffff);
        if (iVar3 == 0) {
          *(undefined2 *)(*(int *)(param_1 + 0x40) + 0x4a) = 2;
        }
        *(undefined4 *)(param_1 + 0x8e4) = *(undefined4 *)(param_1 + 0x8d4);
        fadeout__11worldMapThmFv(*(undefined4 *)(param_1 + 0xac));
        mSetupMenuFadeOut__8worldMapFv(param_1);
        *(undefined4 *)(param_1 + 0xb4) = 6;
        puVar5 = (undefined2 *)GetWorldMapInfo__Fv();
        *puVar5 = (short)*(undefined4 *)(param_1 + 0x8d8);
        puVar5[1] = (short)*(char *)(param_1 + *(int *)(param_1 + 0x8d4) + 0x8ae);
        *(undefined4 *)(puVar5 + 2) = *(undefined4 *)(param_1 + 0x8e8);
      }
      else if (iVar3 == 0xb) {
        mSetupMenuFadeOut__8worldMapFv(param_1);
        mReadDataRequest__8worldMapFv(param_1);
        fadeOut__12worldMapFadeFi(*(undefined4 *)(param_1 + 0x44),0x1e);
      }
      else if (iVar3 == 0x13) {
        mSetupMenuFadeOut__8worldMapFv(param_1);
        fadeOut__12worldMapFadeFi(*(undefined4 *)(param_1 + 0x44),0x1e);
      }
    }
    break;
  case 0x13:
    mIsMenuFade__8worldMapFv(param_1);
    if (*(char *)(*(int *)(param_1 + 0x44) + 0x2c) == '\0') {
      kill__11worldMapThmFv(*(undefined4 *)(param_1 + 0xac));
      mReleaseSelectWin__8worldMapFv(param_1);
      mReleaseMenuWin__8worldMapFv(param_1);
      mReleaseWorldMap__8worldMapFv(param_1);
      mReleaseFont__8worldMapFv(param_1);
      if (*(int *)(param_1 + 0x44) != 0) {
        iVar3 = *(int *)(param_1 + 0x44);
        if (iVar3 != 0) {
          (**(code **)(*(int *)(iVar3 + 0x14) + 8))(iVar3,1);
        }
        *(undefined4 *)(param_1 + 0x44) = 0;
      }
      if (*(int *)(param_1 + 0xac) != 0) {
        __dt__11worldMapThmFv(*(undefined4 *)(param_1 + 0xac),1);
        *(undefined4 *)(param_1 + 0xac) = 0;
      }
      if (*(int *)(param_1 + 0x48) != 0) {
        iVar3 = *(int *)(param_1 + 0x48);
        if (iVar3 != 0) {
          (**(code **)(*(int *)(iVar3 + 0x14) + 8))(iVar3,1);
        }
        *(undefined4 *)(param_1 + 0x48) = 0;
      }
      if (*(int *)(param_1 + 100) != 0) {
        DelayDeleteRequest__9primMusicFv(*(undefined4 *)(param_1 + 100));
        *(undefined4 *)(param_1 + 100) = 0;
      }
      *(undefined4 *)(param_1 + 0xd4) = 0x14;
    }
    break;
  case 0x14:
    if (sys__6CMusic == 0) {
      if (*(int *)(param_1 + 0x8d4) == -1) {
        opening__Fv();
      }
      else {
        lVar6 = __nw__FUi(1);
        iVar3 = 0;
        if (lVar6 != 0) {
          iVar3 = (int)lVar6;
        }
        initializeGameData__11newGameInitFv(iVar3);
        if ((iVar3 != 0) && (iVar3 != 0)) {
          __dl__FPv(iVar3);
        }
        SetSceneInit__10BtlSaveSecFib(*(undefined4 *)(param_1 + 0x8d4),0);
        FieldMapJump__FPCci(param_1 + *(int *)(param_1 + 0x8d4) * 0x50 + 0x11e,1);
      }
      (**(code **)(*(int *)(param_1 + 0x20) + 0xc))();
    }
  }
  mWorldMapPolling__8worldMapFv(param_1);
  return 0;
}

/* JP: 0x00507e60  worldMap::mCheckKey(int)   [mCheckKey__8worldMapFi]  size=0x25c */
undefined4 mCheckKey__8worldMapFi(int param_1,uint param_2)

{
  int iVar1;
  undefined8 uVar2;
  int iVar3;
  
  if (*(int *)(param_1 + 0x9c) != 0) {
    *(int *)(param_1 + 0xa8) = *(int *)(param_1 + 0xa8) + *(int *)(param_1 + 0xa0);
    for (iVar3 = 0; iVar3 < *(int *)(param_1 + 0x8c8); iVar3 = iVar3 + 1) {
      iVar1 = getPT__7primWinFi(*(undefined4 *)(param_1 + 0x90),iVar3);
      (**(code **)(*(int *)(iVar1 + 8) + 0x24))
                ((float)*(int *)(param_1 + 0xa4),(float)(*(int *)(param_1 + 0xa8) + iVar3 * 0x16));
    }
    *(int *)(param_1 + 0x9c) = *(int *)(param_1 + 0x9c) + -1;
    return 0x12;
  }
  if (*(int *)(param_1 + 0x88) == 0) {
    if ((param_2 & 0x2000) == 0) {
      if ((param_2 & 0x4000) != 0) {
        play__9primSoundFi(*(undefined4 *)(param_1 + 0x60),3);
        *(undefined4 *)(param_1 + 0x8d4) = 0xffffffff;
        return 0x13;
      }
    }
    else {
      play__9primSoundFi(*(undefined4 *)(param_1 + 0x60),2);
      if (*(char *)(param_1 + *(int *)(param_1 + 0x8d4) * 0x50 + 0x128) == -1) {
        return 0x13;
      }
    }
  }
  if (1 < *(int *)(param_1 + 0x8d0)) {
    if ((param_2 & 0x40) == 0) {
      if ((param_2 & 0x10) != 0) {
        play__9primSoundFi(*(undefined4 *)(param_1 + 0x60),0);
        uVar2 = mSearchPrev__8worldMapFv(param_1);
        mSetTextScroll__8worldMapFi(param_1,uVar2);
      }
    }
    else {
      play__9primSoundFi(*(undefined4 *)(param_1 + 0x60),0);
      uVar2 = mSearchNext__8worldMapFv(param_1);
      mSetTextScroll__8worldMapFi(param_1,uVar2);
    }
  }
  return 0x12;
}

/* JP: 0x005080c0  worldMap::mSearchNext()   [mSearchNext__8worldMapFv]  size=0xa0 */
int mSearchNext__8worldMapFv(int param_1)

{
  int iVar1;
  
  iVar1 = (*(int *)(param_1 + 0x8d4) + 1) % *(int *)(param_1 + 0x8c8);
  if (*(int *)(param_1 + 0x8c8) == 0) {
    trap(7);
  }
  while (*(char *)(param_1 + iVar1 * 0x50 + 0x129) == '\x03') {
    iVar1 = (iVar1 + 1) % *(int *)(param_1 + 0x8c8);
    if (*(int *)(param_1 + 0x8c8) == 0) {
      trap(7);
    }
  }
  return iVar1;
}

/* JP: 0x00508160  worldMap::mSearchPrev()   [mSearchPrev__8worldMapFv]  size=0xb8 */
int mSearchPrev__8worldMapFv(int param_1)

{
  int iVar1;
  
  iVar1 = (*(int *)(param_1 + 0x8d4) + *(int *)(param_1 + 0x8c8) + -1) % *(int *)(param_1 + 0x8c8);
  if (*(int *)(param_1 + 0x8c8) == 0) {
    trap(7);
  }
  while (*(char *)(param_1 + iVar1 * 0x50 + 0x129) == '\x03') {
    iVar1 = (iVar1 + *(int *)(param_1 + 0x8c8) + -1) % *(int *)(param_1 + 0x8c8);
    if (*(int *)(param_1 + 0x8c8) == 0) {
      trap(7);
    }
  }
  return iVar1;
}

/* JP: 0x00508220  worldMap::mSetTextScroll(int)   [mSetTextScroll__8worldMapFi]  size=0x400 */
void mSetTextScroll__8worldMapFi(int param_1,int param_2)

{
  int iVar1;
  undefined8 uVar2;
  ulong uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  if (*(int *)(param_1 + 0x88) == 0) {
    fadeout__11worldMapThmFv(*(undefined4 *)(param_1 + 0xac));
  }
  mSetNormalTextColor__8worldMapFv(param_1);
  iVar6 = param_2 - *(int *)(param_1 + 0x8d4);
  if (iVar6 < 1) {
    if (iVar6 < 0) {
      if (iVar6 + *(int *)(param_1 + 0x94) < 0) {
        iVar1 = *(int *)(param_1 + 0x94);
        *(undefined4 *)(param_1 + 0x9c) = 0xb;
        iVar4 = iVar6 + *(int *)(param_1 + 0x94);
        iVar5 = iVar4 * -0x16;
        *(uint *)(param_1 + 0xa0) =
             iVar5 / 0xb + (iVar5 >> 0x1f) + ((iVar4 * -0xb & 0x7fffffffU) >> 0x1e);
        *(int *)(param_1 + 0x98) = *(int *)(param_1 + 0x98) + iVar6 + *(int *)(param_1 + 0x94);
        *(undefined4 *)(param_1 + 0x94) = 0;
        setItem__10primCursorFP7primWini(*(undefined4 *)(param_1 + 0xcc),*(undefined4 *)(param_1 + 0x90),
                        *(int *)(param_1 + 0x8d4) - iVar1);
        select__12udScrollMarkFi(*(undefined4 *)(param_1 + 200),*(undefined4 *)(param_1 + 0x98));
      }
      else {
        *(int *)(param_1 + 0x94) = *(int *)(param_1 + 0x94) + iVar6;
        setItem__10primCursorFP7primWini(*(undefined4 *)(param_1 + 0xcc),*(undefined4 *)(param_1 + 0x90),param_2);
      }
    }
  }
  else if (iVar6 + *(int *)(param_1 + 0x94) < 5) {
    *(int *)(param_1 + 0x94) = *(int *)(param_1 + 0x94) + iVar6;
    setItem__10primCursorFP7primWini(*(undefined4 *)(param_1 + 0xcc),*(undefined4 *)(param_1 + 0x90),param_2);
  }
  else {
    iVar1 = *(int *)(param_1 + 0x94);
    *(undefined4 *)(param_1 + 0x9c) = 0xb;
    iVar4 = iVar6 + *(int *)(param_1 + 0x94) + -4;
    iVar5 = iVar4 * -0x16;
    *(uint *)(param_1 + 0xa0) =
         iVar5 / 0xb + (iVar5 >> 0x1f) + ((iVar4 * -0xb & 0x7fffffffU) >> 0x1e);
    *(int *)(param_1 + 0x98) = *(int *)(param_1 + 0x98) + iVar6 + *(int *)(param_1 + 0x94) + -4;
    *(undefined4 *)(param_1 + 0x94) = 4;
    setItem__10primCursorFP7primWini(*(undefined4 *)(param_1 + 0xcc),*(undefined4 *)(param_1 + 0x90),
                    (*(int *)(param_1 + 0x8d4) + 4) - iVar1);
    select__12udScrollMarkFi(*(undefined4 *)(param_1 + 200),*(undefined4 *)(param_1 + 0x98));
  }
  *(int *)(param_1 + 0x8d4) = param_2;
  uVar2 = getPT__7primWinFi(*(undefined4 *)(param_1 + 0x90),*(undefined4 *)(param_1 + 0x8d4));
  SetCSA__8FontItemFUc(uVar2,1);
  iVar6 = (int)uVar2;
  *(undefined1 *)(iVar6 + 0x5c) = 0;
  uVar3 = (ulong)*(byte *)(iVar6 + 0x11) & 0xfffffffffffffffd | 2;
  *(char *)(iVar6 + 0x11) = (char)uVar3;
  *(byte *)(iVar6 + 0x10) =
       *(byte *)(iVar6 + 0x10) & 0xfd | (byte)((uint)((uVar3 << 0x3e) >> 0x3f) << 1);
  *(undefined4 *)(param_1 + 0x8dc) = 0;
  *(undefined4 *)(param_1 + 0x8e0) = *(undefined4 *)(param_1 + 0x8d4);
  mSetWorldScroll__8worldMapFv(param_1);
  setItem__10primCursorFP7primWini(*(undefined4 *)(param_1 + 0xd0),*(undefined4 *)(param_1 + 0x68),0);
  for (iVar6 = 0; iVar6 < 4; iVar6 = iVar6 + 1) {
    if (iVar6 == *(int *)(param_1 + 0x8d4)) {
      setTextAlpha__7primWinFii(*(undefined4 *)(param_1 + 0xb0),iVar6 + 2,0x80);
    }
    else {
      setTextAlpha__7primWinFii(*(undefined4 *)(param_1 + 0xb0),iVar6 + 2,0);
    }
  }
  return;
}

/* JP: 0x00508620  worldMap::mWorldMapPolling()   [mWorldMapPolling__8worldMapFv]  size=0x38 */
void mWorldMapPolling__8worldMapFv(int param_1)

{
  if (*(char *)(param_1 + 0x8c) != '\0') {
    mWorldScroll__8worldMapFv(param_1);
  }
  return;
}

/* JP: 0x00508660  worldMap::mSetupWorldMap()   [mSetupWorldMap__8worldMapFv]  size=0x620 */
void mSetupWorldMap__8worldMapFv(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  long lVar3;
  ulong uVar4;
  
  *(undefined4 *)(param_1 + 0x8d4) = *(undefined4 *)(param_1 + 0x8e4);
  lVar3 = __nw__FUi(0x3c);
  uVar1 = 0;
  if (lVar3 != 0) {
    uVar1 = __ct__9primLayerFv(lVar3);
  }
  *(undefined4 *)(param_1 + 0x30) = uVar1;
  initialize__9primLayerFPUci(*(undefined4 *)(param_1 + 0x30),m_pTex,4);
  setTex__9primLayerFiii(*(undefined4 *)(param_1 + 0x30),0,4,0);
  setTex__9primLayerFiiiii(*(undefined4 *)(param_1 + 0x30),1,3,0x10,0x10,0);
  setTex__9primLayerFiii(*(undefined4 *)(param_1 + 0x30),2,2,0);
  setTex__9primLayerFiii(*(undefined4 *)(param_1 + 0x30),3,1,0);
  lVar3 = __nw__FUi(0x150);
  uVar1 = 0;
  if (lVar3 != 0) {
    uVar1 = __ct__10primSpriteFb(lVar3,1);
  }
  *(undefined4 *)(param_1 + 0x34) = uVar1;
  setDisp__10primPacketFP9primLayeriffff(0,0,0x3f800000,0x3f800000,*(undefined4 *)(param_1 + 0x34),
                  *(undefined4 *)(param_1 + 0x30),0);
  lVar3 = __nw__FUi(0x148);
  uVar1 = 0;
  if (lVar3 != 0) {
    uVar1 = __ct__7primWinFv(lVar3);
  }
  *(undefined4 *)(param_1 + 0x68) = uVar1;
  uVar1 = *(undefined4 *)(param_1 + 0x68);
  initialize__7primWinFP7primTex(uVar1,*(undefined4 *)(param_1 + 0x2c));
  setItem__7primWinFiii(uVar1,1,6,0);
  createPoly__7primWinFiiiiii(uVar1,0,0,*(short *)(param_1 + *(int *)(param_1 + 0x8e4) * 0x50 + 0x12a) + -8,
                  *(short *)(param_1 + *(int *)(param_1 + 0x8e4) * 0x50 + 300) + -8,0x10,0x10);
  iVar2 = getPP__7primWinFi(uVar1,0);
  *(undefined2 *)(iVar2 + 0x1c) = 0;
  *(undefined2 *)(iVar2 + 0x1e) = 0;
  setPolyAlpha__7primWinFii(uVar1,0,0);
  createPoly__7primWinFiiiiii(uVar1,1,0,0,0,0xa0,0x1c0);
  setPolyRGBA__7primWinFiiiii(uVar1,1,0,0,0,0x80);
  createPoly__7primWinFiiiiii(uVar1,2,0,0xa0,0,0x50,0x1c0);
  setPolyRGBA__7primWinFiiiii(uVar1,2,0,0,0,0x80);
  iVar2 = getPP__7primWinFi(uVar1,2);
  *(undefined4 *)(iVar2 + 0x84) = 0xffffffff;
  *(undefined4 *)(iVar2 + 0x90) = 0;
  *(undefined1 *)(iVar2 + 0x7b) = 0;
  uVar4 = (ulong)*(byte *)(iVar2 + 0x11) & 0xffffffffffffffef | 0x10;
  *(char *)(iVar2 + 0x11) = (char)uVar4;
  *(byte *)(iVar2 + 0x10) =
       *(byte *)(iVar2 + 0x10) & 0xef | (byte)((uint)((uVar4 << 0x3b) >> 0x3f) << 4);
  iVar2 = getPP__7primWinFi(uVar1,2);
  *(undefined4 *)(iVar2 + 0x84) = 0xffffffff;
  *(undefined4 *)(iVar2 + 0x94) = 0;
  *(undefined1 *)(iVar2 + 0x7f) = 0;
  uVar4 = (ulong)*(byte *)(iVar2 + 0x11) & 0xffffffffffffffef | 0x10;
  *(char *)(iVar2 + 0x11) = (char)uVar4;
  *(byte *)(iVar2 + 0x10) =
       *(byte *)(iVar2 + 0x10) & 0xef | (byte)((uint)((uVar4 << 0x3b) >> 0x3f) << 4);
  buildWin__7primWinFiiiiii(uVar1,1,0,0,0,0,0);
  lVar3 = __nw__FUi(0x80);
  uVar1 = 0;
  if (lVar3 != 0) {
    uVar1 = __ct__13worldMapPointFv(lVar3);
  }
  *(undefined4 *)(param_1 + 0x38) = uVar1;
  initialize__13worldMapPointFP9primLayeriPQ28worldMap11SUBMAP_DATAi
            (*(undefined4 *)(param_1 + 0x38),*(undefined4 *)(param_1 + 0x30),
             *(undefined4 *)(param_1 + 0x8c8),param_1 + 0xde,1);
  *(undefined4 *)(param_1 + 0x8e0) = *(undefined4 *)(param_1 + 0x8e4);
  *(undefined4 *)(param_1 + 0x8dc) = 0;
  *(undefined4 *)(param_1 + 0x9c) = 0;
  if (*(int *)(param_1 + 0x8cc) == 0) {
    dispThm__11worldMapThmFiPUcPUc
              (*(undefined4 *)(param_1 + 0xac),
               *(undefined1 *)(param_1 + *(int *)(param_1 + 0x8d4) * 0x50 + 0x127),
               param_1 + *(int *)(param_1 + 0x8d4) * 0x50 + 0xde,
               param_1 + *(int *)(param_1 + 0x8d4) * 0x50 + 0xfe);
  }
  mSetWorldPos__8worldMapFv(param_1);
  lVar3 = __nw__FUi(0x94);
  uVar1 = 0;
  if (lVar3 != 0) {
    uVar1 = __ct__13worldMapLightFv(lVar3);
  }
  *(undefined4 *)(param_1 + 0x3c) = uVar1;
  initialize__13worldMapLightFP9primLayerii
            (*(undefined4 *)(param_1 + 0x3c),*(undefined4 *)(param_1 + 0x30),1,3);
  setPos__13worldMapLightFff
            ((float)(int)*(short *)(param_1 + *(int *)(param_1 + 0x8d4) * 0x50 + 0x12a) +
             *(float *)(param_1 + 0x78),
             (float)(int)*(short *)(param_1 + *(int *)(param_1 + 0x8d4) * 0x50 + 300) +
             *(float *)(param_1 + 0x7c),*(undefined4 *)(param_1 + 0x3c));
  *(undefined1 *)(param_1 + 0x8c) = 1;
  return;
}

/* JP: 0x00508c80  worldMap::mReleaseWorldMap()   [mReleaseWorldMap__8worldMapFv]  size=0x114 */
void mReleaseWorldMap__8worldMapFv(int param_1)

{
  int iVar1;
  
  if (*(int *)(param_1 + 0x68) != 0) {
    DelayDeleteRequest__7primWinFv(*(undefined4 *)(param_1 + 0x68));
    *(undefined4 *)(param_1 + 0x68) = 0;
  }
  if (*(int *)(param_1 + 0x34) != 0) {
    DelayDeleteRequest__10primPacketFv(*(undefined4 *)(param_1 + 0x34));
    *(undefined4 *)(param_1 + 0x34) = 0;
  }
  if (*(int *)(param_1 + 0x3c) != 0) {
    iVar1 = *(int *)(param_1 + 0x3c);
    if (iVar1 != 0) {
      (**(code **)(*(int *)(iVar1 + 0x14) + 8))(iVar1,1);
    }
    *(undefined4 *)(param_1 + 0x3c) = 0;
  }
  if (*(int *)(param_1 + 0x38) != 0) {
    __dt__13worldMapPointFv(*(undefined4 *)(param_1 + 0x38),1);
    *(undefined4 *)(param_1 + 0x38) = 0;
  }
  if (*(int *)(param_1 + 0x30) != 0) {
    DelayDeleteRequest__9primLayerFv(*(undefined4 *)(param_1 + 0x30));
    *(undefined4 *)(param_1 + 0x30) = 0;
  }
  *(undefined1 *)(param_1 + 0x8c) = 0;
  return;
}

/* JP: 0x00508da0  worldMap::mSetupMenuFadeIn()   [mSetupMenuFadeIn__8worldMapFv]  size=0x10 */
void mSetupMenuFadeIn__8worldMapFv(void)

{
  return;
}

/* JP: 0x00508db0  worldMap::mSetupMenuFadeOut()   [mSetupMenuFadeOut__8worldMapFv]  size=0x74 */
void mSetupMenuFadeOut__8worldMapFv(int param_1)

{
  mReleaseSelectWinCursor__8worldMapFv(param_1);
  fadeout__11worldMapThmFv(*(undefined4 *)(param_1 + 0xac));
  fadeout__7primWinFi(*(undefined4 *)(param_1 + 0x90),0x10);
  fadeout__7primWinFi(*(undefined4 *)(param_1 + 0xb0),0x10);
  fadeout__7primWinFi(*(undefined4 *)(param_1 + 0x6c),0x10);
  return;
}

/* JP: 0x00508e30  worldMap::mIsMenuFade()   [mIsMenuFade__8worldMapFv]  size=0x2c */
void mIsMenuFade__8worldMapFv(int param_1)

{
  isFade__7primWinFv(*(undefined4 *)(param_1 + 0x90));
  return;
}

/* JP: 0x00508e60  worldMap::mSetupSelectWin()   [mSetupSelectWin__8worldMapFv]  size=0x348 */
void mSetupSelectWin__8worldMapFv(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  long lVar3;
  undefined8 uVar4;
  ulong uVar5;
  int iVar6;
  int iVar7;
  
  if (*(int *)(param_1 + 0x8e4) < 5) {
    *(undefined4 *)(param_1 + 0x94) = *(undefined4 *)(param_1 + 0x8e4);
    *(undefined4 *)(param_1 + 0x98) = 0;
  }
  else {
    *(int *)(param_1 + 0x98) = *(int *)(param_1 + 0x8e4) + -4;
    *(undefined4 *)(param_1 + 0x94) = 4;
  }
  *(undefined4 *)(param_1 + 0xa4) = 0;
  *(int *)(param_1 + 0xa8) = *(int *)(param_1 + 0x98) * -0x16;
  lVar3 = __nw__FUi(0x148);
  uVar2 = 0;
  if (lVar3 != 0) {
    uVar2 = __ct__7primWinFv(lVar3);
  }
  *(undefined4 *)(param_1 + 0x90) = uVar2;
  iVar1 = *(int *)(param_1 + 0x90);
  initialize__7primWinFP7primTex(iVar1,*(undefined4 *)(param_1 + 0x2c));
  setItem__7primWinFiii(iVar1,1,0,0x19);
  setTextArea__7primWinFiiib(iVar1,0,0x280,0x180,1);
  for (iVar6 = 0; iVar6 < *(int *)(param_1 + 0x8c8); iVar6 = iVar6 + 1) {
    createText__7primWinFiiiiPciib(iVar1,iVar6,0,0xffffffffffffff00,(iVar6 - *(int *)(param_1 + 0x98)) * 0x16,
                    param_1 + iVar6 * 0x50 + 0xde,0,0);
    setTextFadeScroll__7primWinFiii(iVar1,iVar6,1,0x10);
    if (*(char *)(param_1 + iVar6 * 0x50 + 0x129) == '\x03') {
      uVar4 = getPT__7primWinFi(iVar1,iVar6);
      SetCSA__8FontItemFUc(uVar4,2);
      iVar7 = (int)uVar4;
      *(undefined1 *)(iVar7 + 0x5c) = 0;
      uVar5 = (ulong)*(byte *)(iVar7 + 0x11) & 0xfffffffffffffffd | 2;
      *(char *)(iVar7 + 0x11) = (char)uVar5;
      *(byte *)(iVar7 + 0x10) =
           *(byte *)(iVar7 + 0x10) & 0xfd | (byte)((uint)((uVar5 << 0x3e) >> 0x3f) << 1);
    }
  }
  uVar4 = getPT__7primWinFi(*(undefined4 *)(param_1 + 0x90),*(undefined4 *)(param_1 + 0x8d4));
  SetCSA__8FontItemFUc(uVar4,1);
  iVar6 = (int)uVar4;
  *(undefined1 *)(iVar6 + 0x5c) = 0;
  uVar5 = (ulong)*(byte *)(iVar6 + 0x11) & 0xfffffffffffffffd | 2;
  *(char *)(iVar6 + 0x11) = (char)uVar5;
  *(byte *)(iVar6 + 0x10) =
       *(byte *)(iVar6 + 0x10) & 0xfd | (byte)((uint)((uVar5 << 0x3e) >> 0x3f) << 1);
  buildWin__7primWinFiiiiii(iVar1,5,0x34,0x10c,0x100,0x6c,0);
  SetClip__10MenuWindowFUc(iVar1 + 0x3c,1);
  fadein__7primWinFi(iVar1,0x10);
  return;
}

/* JP: 0x005091b0  worldMap::mReleaseSelectWin()   [mReleaseSelectWin__8worldMapFv]  size=0x48 */
void mReleaseSelectWin__8worldMapFv(int param_1)

{
  if (*(int *)(param_1 + 0x90) != 0) {
    DelayDeleteRequest__7primWinFv(*(undefined4 *)(param_1 + 0x90));
    *(undefined4 *)(param_1 + 0x90) = 0;
  }
  return;
}

/* JP: 0x00509200  worldMap::mSetupSelectWinCursor()   [mSetupSelectWinCursor__8worldMapFv]  size=0x1bc */
void mSetupSelectWinCursor__8worldMapFv(int param_1)

{
  undefined4 uVar1;
  long lVar2;
  
  lVar2 = __nw__FUi(0x3c);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = __ct__12udScrollMarkFv(lVar2);
  }
  *(undefined4 *)(param_1 + 200) = uVar1;
  initialize__12udScrollMarkFP7primTexiiiii(*(undefined4 *)(param_1 + 200),*(undefined4 *)(param_1 + 0x2c),
                  *(undefined4 *)(param_1 + 0x98),*(int *)(param_1 + 0x8c8) + -4,0x76,0xf6,0x17a);
  if (*(int *)(param_1 + 0xcc) == 0) {
    lVar2 = __nw__FUi(0x10c);
    uVar1 = 0;
    if (lVar2 != 0) {
      uVar1 = __ct__10primCursorFv(lVar2);
    }
    *(undefined4 *)(param_1 + 0xcc) = uVar1;
    createCursor__10primCursorFiiii(*(undefined4 *)(param_1 + 0xcc),0,2,8,10);
    setItem__10primCursorFP7primWini(*(undefined4 *)(param_1 + 0xcc),*(undefined4 *)(param_1 + 0x90),
                    *(undefined4 *)(param_1 + 0x8e4));
    qMove__10primCursorFv(*(undefined4 *)(param_1 + 0xcc));
  }
  if (*(int *)(param_1 + 0xd0) == 0) {
    lVar2 = __nw__FUi(0x10c);
    uVar1 = 0;
    if (lVar2 != 0) {
      uVar1 = __ct__10primCursorFv(lVar2);
    }
    *(undefined4 *)(param_1 + 0xd0) = uVar1;
    createCursor__10primCursorFiiii(*(undefined4 *)(param_1 + 0xd0),1,1,8,10);
    setItem__10primCursorFP7primWini(*(undefined4 *)(param_1 + 0xd0),*(undefined4 *)(param_1 + 0x68),0);
    qMove__10primCursorFv(*(undefined4 *)(param_1 + 0xd0));
  }
  return;
}

/* JP: 0x005093c0  worldMap::mReleaseSelectWinCursor()   [mReleaseSelectWinCursor__8worldMapFv]  size=0xb4 */
void mReleaseSelectWinCursor__8worldMapFv(int param_1)

{
  int iVar1;
  
  if (*(int *)(param_1 + 0xcc) != 0) {
    DelayDeleteRequest__10primCursorFv(*(undefined4 *)(param_1 + 0xcc));
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  if (*(int *)(param_1 + 0xd0) != 0) {
    DelayDeleteRequest__10primCursorFv(*(undefined4 *)(param_1 + 0xd0));
    *(undefined4 *)(param_1 + 0xd0) = 0;
  }
  if (*(int *)(param_1 + 200) != 0) {
    iVar1 = *(int *)(param_1 + 200);
    if (iVar1 != 0) {
      (**(code **)(*(int *)(iVar1 + 0x14) + 8))(iVar1,1);
    }
    *(undefined4 *)(param_1 + 200) = 0;
  }
  return;
}

/* JP: 0x00509480  worldMap::mSetupFont()   [mSetupFont__8worldMapFv]  size=0x68 */
void mSetupFont__8worldMapFv(void)

{
  undefined8 uVar1;
  
  uVar1 = GetFileEntry(m_pTex,9);
  (*(code *)&CreateFont__4FontFiPUc)(3,uVar1);
  return;
}

/* JP: 0x005094f0  worldMap::mReleaseFont()   [mReleaseFont__8worldMapFv]  size=0x3c */
void mReleaseFont__8worldMapFv(void)

{
  (*(code *)&ClearFont__4FontFi)(3);
  return;
}

/* JP: 0x00509530  worldMap::mScriptFilter(worldMap::SUBMAP_DATA*)   [mScriptFilter__8worldMapFPQ28worldMap11SUBMAP_DATA]  size=0x344 */
void mScriptFilter__8worldMapFPQ28worldMap11SUBMAP_DATA(int param_1,char *param_2)

{
  char cVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  char *pcVar6;
  undefined4 uVar7;
  char *pcStack_10;
  
  uVar7 = 0xffffffff;
  *(undefined4 *)(param_1 + 0x8c8) = 0;
  *(undefined4 *)(param_1 + 0x8cc) = 0;
  *(undefined4 *)(param_1 + 0x8d0) = 0;
  pcStack_10 = param_2;
  do {
    if (*pcStack_10 == '\0') {
      *(undefined4 *)(param_1 + 0x8e4) = uVar7;
      *(undefined1 *)(param_1 + 0x8ec) = 0;
      if (((long)*(int *)(param_1 + 0x8e8) &
          (long)(char)(&DAT_005555a8)[*(int *)(param_1 + 0x8d8) * 0x30]) != 0) {
        *(undefined1 *)(param_1 + 0x8ec) = 1;
      }
      return;
    }
    if ((long)pcStack_10[0x4b] == (long)*(int *)(param_1 + 0x8e4)) {
      uVar7 = *(undefined4 *)(param_1 + 0x8c8);
    }
    *(char *)(param_1 + *(int *)(param_1 + 0x8c8) + 0x8ae) = pcStack_10[0x4b];
    iVar3 = param_1 + *(int *)(param_1 + 0x8c8) * 0x50;
    pcVar6 = (char *)(iVar3 + 0xde);
    iVar4 = 0x10;
    pcVar5 = pcStack_10;
    do {
      cVar1 = *pcVar5;
      cVar2 = pcVar5[1];
      pcVar5 = pcVar5 + 2;
      iVar4 = iVar4 + -1;
      *pcVar6 = cVar1;
      pcVar6[1] = cVar2;
      pcVar6 = pcVar6 + 2;
    } while (0 < iVar4);
    pcVar6 = pcStack_10 + 0x20;
    pcVar5 = (char *)(iVar3 + 0xfe);
    iVar4 = 0x10;
    do {
      cVar1 = *pcVar6;
      cVar2 = pcVar6[1];
      pcVar6 = pcVar6 + 2;
      iVar4 = iVar4 + -1;
      *pcVar5 = cVar1;
      pcVar5[1] = cVar2;
      pcVar5 = pcVar5 + 2;
    } while (0 < iVar4);
    pcVar6 = pcStack_10 + 0x40;
    pcVar5 = (char *)(iVar3 + 0x11e);
    iVar4 = 4;
    do {
      cVar1 = *pcVar6;
      cVar2 = pcVar6[1];
      pcVar6 = pcVar6 + 2;
      iVar4 = iVar4 + -1;
      *pcVar5 = cVar1;
      pcVar5[1] = cVar2;
      pcVar5 = pcVar5 + 2;
    } while (0 < iVar4);
    *(char *)(iVar3 + 0x126) = pcStack_10[0x48];
    *(char *)(iVar3 + 0x127) = pcStack_10[0x49];
    *(char *)(iVar3 + 0x128) = pcStack_10[0x4a];
    *(char *)(iVar3 + 0x129) = pcStack_10[0x4b];
    *(undefined2 *)(iVar3 + 0x12a) = *(undefined2 *)(pcStack_10 + 0x4c);
    *(undefined2 *)(iVar3 + 300) = *(undefined2 *)(pcStack_10 + 0x4e);
    *(undefined1 *)(param_1 + *(int *)(param_1 + 0x8c8) * 0x50 + 0x129) =
         *(undefined1 *)(param_1 + pcStack_10[0x4b] + 0x8ed);
    cVar1 = *(char *)(param_1 + *(int *)(param_1 + 0x8c8) * 0x50 + 0x129);
    if (cVar1 == '\x03') {
      *(int *)(param_1 + 0x8c8) = *(int *)(param_1 + 0x8c8) + 1;
    }
    else {
      if (cVar1 != '\x01') {
        if (cVar1 != '\x02') goto LAB_005097e0;
        *(undefined1 *)(param_1 + pcStack_10[0x4b] + 0x8ed) = 1;
        *(undefined1 *)(param_1 + *(int *)(param_1 + 0x8c8) * 0x50 + 0x129) = 2;
        *(int *)(param_1 + 0x8cc) = *(int *)(param_1 + 0x8cc) + 1;
      }
      *(int *)(param_1 + 0x8d0) = *(int *)(param_1 + 0x8d0) + 1;
      *(int *)(param_1 + 0x8c8) = *(int *)(param_1 + 0x8c8) + 1;
    }
LAB_005097e0:
    pcStack_10 = pcStack_10 + 0x50;
  } while( true );
}

/* JP: 0x00509880  worldMap::mSetNormalTextColor()   [mSetNormalTextColor__8worldMapFv]  size=0x158 */
void mSetNormalTextColor__8worldMapFv(int param_1)

{
  undefined8 uVar1;
  ulong uVar2;
  int iVar3;
  
  if (*(char *)(param_1 + *(int *)(param_1 + 0x8d4) * 0x50 + 0x129) == '\x03') {
    uVar1 = getPT__7primWinFi(*(undefined4 *)(param_1 + 0x90),*(undefined4 *)(param_1 + 0x8d4));
    SetCSA__8FontItemFUc(uVar1,2);
    iVar3 = (int)uVar1;
    *(undefined1 *)(iVar3 + 0x5c) = 0;
    uVar2 = (ulong)*(byte *)(iVar3 + 0x11) & 0xfffffffffffffffd | 2;
    *(char *)(iVar3 + 0x11) = (char)uVar2;
    *(byte *)(iVar3 + 0x10) =
         *(byte *)(iVar3 + 0x10) & 0xfd | (byte)((uint)((uVar2 << 0x3e) >> 0x3f) << 1);
  }
  else {
    uVar1 = getPT__7primWinFi(*(undefined4 *)(param_1 + 0x90),*(undefined4 *)(param_1 + 0x8d4));
    SetCSA__8FontItemFUc(uVar1,0);
    iVar3 = (int)uVar1;
    *(undefined1 *)(iVar3 + 0x5c) = 0;
    uVar2 = (ulong)*(byte *)(iVar3 + 0x11) & 0xfffffffffffffffd | 2;
    *(char *)(iVar3 + 0x11) = (char)uVar2;
    *(byte *)(iVar3 + 0x10) =
         *(byte *)(iVar3 + 0x10) & 0xfd | (byte)((uint)((uVar2 << 0x3e) >> 0x3f) << 1);
  }
  return;
}

/* JP: 0x005099e0  worldMap::mSetupMenuWin()   [mSetupMenuWin__8worldMapFv]  size=0x604 */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void mSetupMenuWin__8worldMapFv(int param_1)

{
  undefined4 uVar1;
  long lVar2;
  undefined8 uVar3;
  int iVar4;
  
  lVar2 = __nw__FUi(0x148);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = __ct__7primWinFv(lVar2);
  }
  *(undefined4 *)(param_1 + 0x6c) = uVar1;
  uVar1 = *(undefined4 *)(param_1 + 0x6c);
  initialize__7primWinFP7primTex(uVar1,*(undefined4 *)(param_1 + 0x2c));
  setItem__7primWinFiii(uVar1,1,2,0);
  createPoly__7primWinFiiiiii(uVar1,0,0,0x35,0x35,0x94,0x86);
  setPolyRGBA__7primWinFiiiii(uVar1,0,0,0,0,0x80);
  createPoly__7primWinFiiiiii(uVar1,1,0,0x28,0xfa,0xb4,0x8a);
  setPolyRGBA__7primWinFiiiiii(uVar1,1,0,0x41,0x41,0x4e,0x4c);
  setPolyRGBA__7primWinFiiiiii(uVar1,1,2,0x41,0x41,0x4e,0x4c);
  setPolyRGBA__7primWinFiiiiii(uVar1,1,1,10,8,10,0x4c);
  setPolyRGBA__7primWinFiiiiii(uVar1,1,3,10,8,10,0x4c);
  buildWin__7primWinFiiiiii(uVar1,1,0,0,0,0,0);
  fadein__7primWinFi(uVar1,0x10);
  lVar2 = __nw__FUi(0x148);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = __ct__7primWinFv(lVar2);
  }
  *(undefined4 *)(param_1 + 0xb0) = uVar1;
  uVar1 = *(undefined4 *)(param_1 + 0xb0);
  initialize__7primWinFP7primTex(uVar1,*(undefined4 *)(param_1 + 0x2c));
  setItem__7primWinFiii(uVar1,6,10,6);
  setTex__7primWinFiiii(uVar1,7,1,0,0);
  createTexPoly__7primWinFiiiiii(uVar1,2,1,0x80,0,0,0);
  createTexPoly__7primWinFiiiiii(uVar1,3,1,0,0,0,0);
  uVar3 = getPP__7primWinFi(uVar1,2);
  SetUV__11MenuPolygonFUsUsUsUs(uVar3,2,1,0x7f,0x198);
  uVar3 = getPP__7primWinFi(uVar1,3);
  SetUV__11MenuPolygonFUsUsUsUs(uVar3,0x7f,1,1,0x198);
  setTex__7primWinFiiii(uVar1,8,2,0,0);
  createTexPoly__7primWinFiiiiii(uVar1,4,2,0x40,0x18,0,0);
  setMenuTex__7primWinFP11MenuTextureiii(uVar1,0x421658,3,0x10,0x14);
  createTexPoly__7primWinFiiiiii(uVar1,6,3,0x18a,0x172,5,1);
  createTexPoly__7primWinFiiiiii(uVar1,7,3,0x18a,0x188,6,1);
  createPoly__7primWinFiiiiii(uVar1,8,0,0,0x19e,0x200,0x20);
  setPolyRGBA__7primWinFiiiii(uVar1,8,0,0,0,0x40);
  *(undefined4 *)(param_1 + 0xb8) = 9;
  setTextArea__7primWinFiiib(uVar1,4,0x200,0x180,1);
  createText__7primWinFiiiiPciib(uVar1,0,4,0x19a,0x172,mMapMenuTbl,0,0);
  createText__7primWinFiiiiPciib(uVar1,1,4,0x19a,0x188,mMapMenuTbl+0x4,0,0);
  createText__7primWinFiiiiPciib(uVar1,2,4,0x10,0x1a2,worldMap_trialNote_J,0,0);
  createText__7primWinFiiiiPciib(uVar1,3,4,0x10,0x1a2,PTR__5282_00555574,0,0);
  createText__7primWinFiiiiPciib(uVar1,4,4,0x10,0x1a2,PTR__5283_00555578,0,0);
  createText__7primWinFiiiiPciib(uVar1,5,4,0x10,0x1a2,PTR__5284_0055557c,0,0);
  for (iVar4 = 0; iVar4 < 4; iVar4 = iVar4 + 1) {
    if (iVar4 != *(int *)(param_1 + 0x8d4)) {
      setTextAlpha__7primWinFii(*(undefined4 *)(param_1 + 0xb0),iVar4 + 2,0);
    }
  }
  *(undefined4 *)(param_1 + 0xbc) = 1;
  buildWin__7primWinFiiiiii(uVar1,3,0,0,0,0,0);
  fadein__7primWinFi(uVar1,0x10);
  return;
}

/* JP: 0x00509ff0  worldMap::mReleaseMenuWin()   [mReleaseMenuWin__8worldMapFv]  size=0x70 */
void mReleaseMenuWin__8worldMapFv(int param_1)

{
  if (*(int *)(param_1 + 0xb0) != 0) {
    DelayDeleteRequest__7primWinFv(*(undefined4 *)(param_1 + 0xb0));
    *(undefined4 *)(param_1 + 0xb0) = 0;
  }
  if (*(int *)(param_1 + 0x6c) != 0) {
    DelayDeleteRequest__7primWinFv(*(undefined4 *)(param_1 + 0x6c));
    *(undefined4 *)(param_1 + 0x6c) = 0;
  }
  return;
}

/* JP: 0x0050a060  worldMap::mSetWorldScroll()   [mSetWorldScroll__8worldMapFv]  size=0x1bc */
void mSetWorldScroll__8worldMapFv(int param_1)

{
  int iVar1;
  
  mSetWorldDest__8worldMapFv(param_1);
  setDest__13worldMapLightFff
            ((float)(int)*(short *)(param_1 + *(int *)(param_1 + 0x8d4) * 0x50 + 0x12a) +
             *(float *)(param_1 + 0x70),
             (float)(int)*(short *)(param_1 + *(int *)(param_1 + 0x8d4) * 0x50 + 300) +
             *(float *)(param_1 + 0x74),*(undefined4 *)(param_1 + 0x3c));
  *(float *)(param_1 + 0x80) = (*(float *)(param_1 + 0x70) - *(float *)(param_1 + 0x78)) / 24.0;
  *(float *)(param_1 + 0x84) = (*(float *)(param_1 + 0x74) - *(float *)(param_1 + 0x7c)) / 24.0;
  *(undefined4 *)(param_1 + 0x88) = 0x18;
  iVar1 = getPP__7primWinFi(*(undefined4 *)(param_1 + 0x68),0);
  (**(code **)(*(int *)(iVar1 + 8) + 0x24))
            ((float)(*(short *)(param_1 + *(int *)(param_1 + 0x8d4) * 0x50 + 0x12a) + -8) +
             *(float *)(param_1 + 0x70),
             (float)(*(short *)(param_1 + *(int *)(param_1 + 0x8d4) * 0x50 + 300) + -8) +
             *(float *)(param_1 + 0x74));
  return;
}

/* JP: 0x0050a220  worldMap::mSetWorldPos()   [mSetWorldPos__8worldMapFv]  size=0x140 */
void mSetWorldPos__8worldMapFv(int param_1)

{
  int iVar1;
  
  *(undefined4 *)(param_1 + 0x88) = 0;
  mSetWorldDest__8worldMapFv(param_1);
  *(undefined4 *)(param_1 + 0x78) = *(undefined4 *)(param_1 + 0x70);
  *(undefined4 *)(param_1 + 0x7c) = *(undefined4 *)(param_1 + 0x74);
  iVar1 = getPP__7primWinFi(*(undefined4 *)(param_1 + 0x68),0);
  (**(code **)(*(int *)(iVar1 + 8) + 0x24))
            ((float)(*(short *)(param_1 + *(int *)(param_1 + 0x8d4) * 0x50 + 0x12a) + -8) +
             *(float *)(param_1 + 0x78),
             (float)(*(short *)(param_1 + *(int *)(param_1 + 0x8d4) * 0x50 + 300) + -8) +
             *(float *)(param_1 + 0x7c));
  setPos__10primPacketFff(*(undefined4 *)(param_1 + 0x78),*(undefined4 *)(param_1 + 0x7c),
                  *(undefined4 *)(param_1 + 0x34));
  setPos__13worldMapPointFff
            (*(undefined4 *)(param_1 + 0x78),*(undefined4 *)(param_1 + 0x7c),
             *(undefined4 *)(param_1 + 0x38));
  return;
}

/* JP: 0x0050a360  worldMap::mSetWorldDest()   [mSetWorldDest__8worldMapFv]  size=0x224 */
void mSetWorldDest__8worldMapFv(int param_1)

{
  short sVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  
  sVar1 = 0x170 - *(short *)(param_1 + *(int *)(param_1 + 0x8d4) * 0x50 + 0x12a);
  iVar4 = (int)sVar1;
  sVar2 = 0xe0 - *(short *)(param_1 + *(int *)(param_1 + 0x8d4) * 0x50 + 300);
  iVar3 = (int)sVar2;
  if ((long)sVar1 < (long)-(int)*(short *)(&DAT_005555aa + *(int *)(param_1 + 0x8d8) * 0x30)) {
    iVar4 = (int)-*(short *)(&DAT_005555aa + *(int *)(param_1 + 0x8d8) * 0x30);
  }
  else if (0xa0 < sVar1) {
    iVar4 = 0xa0;
  }
  if ((long)sVar2 < (long)-(int)*(short *)(&DAT_005555ac + *(int *)(param_1 + 0x8d8) * 0x30)) {
    iVar3 = (int)-*(short *)(&DAT_005555ac + *(int *)(param_1 + 0x8d8) * 0x30);
  }
  else if (0 < sVar2) {
    iVar3 = 0;
  }
  *(float *)(param_1 + 0x70) = (float)iVar4;
  *(float *)(param_1 + 0x74) = (float)iVar3;
  return;
}

/* JP: 0x0050a590  worldMap::mWorldScroll()   [mWorldScroll__8worldMapFv]  size=0x210 */
void mWorldScroll__8worldMapFv(int param_1)

{
  int iVar1;
  
  if (*(int *)(param_1 + 0x88) != 0) {
    *(int *)(param_1 + 0x88) = *(int *)(param_1 + 0x88) + -1;
    if (*(int *)(param_1 + 0x88) == 0) {
      *(undefined4 *)(param_1 + 0x78) = *(undefined4 *)(param_1 + 0x70);
      *(undefined4 *)(param_1 + 0x7c) = *(undefined4 *)(param_1 + 0x74);
      dispThm__11worldMapThmFiPUcPUc
                (*(undefined4 *)(param_1 + 0xac),
                 *(undefined1 *)(param_1 + *(int *)(param_1 + 0x8d4) * 0x50 + 0x127),
                 param_1 + *(int *)(param_1 + 0x8d4) * 0x50 + 0xde,
                 param_1 + *(int *)(param_1 + 0x8d4) * 0x50 + 0xfe);
    }
    else {
      *(float *)(param_1 + 0x78) = *(float *)(param_1 + 0x78) + *(float *)(param_1 + 0x80);
      *(float *)(param_1 + 0x7c) = *(float *)(param_1 + 0x7c) + *(float *)(param_1 + 0x84);
    }
  }
  iVar1 = getPP__7primWinFi(*(undefined4 *)(param_1 + 0x68),0);
  (**(code **)(*(int *)(iVar1 + 8) + 0x24))
            ((float)(*(short *)(param_1 + *(int *)(param_1 + 0x8d4) * 0x50 + 0x12a) + -8) +
             *(float *)(param_1 + 0x78),
             (float)(*(short *)(param_1 + *(int *)(param_1 + 0x8d4) * 0x50 + 300) + -8) +
             *(float *)(param_1 + 0x7c));
  setPos__10primPacketFff(*(undefined4 *)(param_1 + 0x78),*(undefined4 *)(param_1 + 0x7c),
                  *(undefined4 *)(param_1 + 0x34));
  setPos__13worldMapPointFff
            (*(undefined4 *)(param_1 + 0x78),*(undefined4 *)(param_1 + 0x7c),
             *(undefined4 *)(param_1 + 0x38));
  return;
}

/* JP: 0x0050a7a0  worldMap::mNewPointDemo()   [mNewPointDemo__8worldMapFv]  size=0x7cc */
undefined4 mNewPointDemo__8worldMapFv(int param_1)

{
  undefined4 uVar1;
  long lVar2;
  int iVar3;
  float fVar4;
  
  iVar3 = *(int *)(param_1 + 0xd8);
  if (iVar3 == 4) {
    if (*(int *)(param_1 + 0x8d4) != *(int *)(param_1 + 0x8e4)) {
      *(undefined4 *)(param_1 + 0x8d4) = *(undefined4 *)(param_1 + 0x8e4);
      fadeout__11worldMapThmFv(*(undefined4 *)(param_1 + 0xac));
      mSetWorldScroll__8worldMapFv(param_1);
    }
    uVar1 = 0;
  }
  else {
    if (iVar3 == 3) {
      if (*(int *)(param_1 + 0x5c) < 0x20) {
        for (iVar3 = 0; iVar3 < 4; iVar3 = iVar3 + 1) {
          fVar4 = ((float)*(int *)(param_1 + 0x5c) * 0.5) / 32.0 + 0.5;
          setScale__6prim2DFff(fVar4,fVar4,*(undefined4 *)(param_1 + iVar3 * 4 + 0x4c));
          setRot__6prim2DFf(((float)*(int *)(param_1 + 0x5c) * 0.05) / 32.0 + 0.01,
                          *(undefined4 *)(param_1 + iVar3 * 4 + 0x4c));
        }
      }
      else if (*(int *)(param_1 + 0x5c) < 0x40) {
        for (iVar3 = 0; iVar3 < 4; iVar3 = iVar3 + 1) {
          fVar4 = 1.0 - (float)(*(int *)(param_1 + 0x5c) + -0x20) / 32.0;
          setScale__6prim2DFff(fVar4,fVar4,*(undefined4 *)(param_1 + iVar3 * 4 + 0x4c));
          setRot__6prim2DFf(0.060000002 - ((float)(*(int *)(param_1 + 0x5c) + -0x20) * 0.05) / 32.0,
                          *(undefined4 *)(param_1 + iVar3 * 4 + 0x4c));
        }
      }
      else {
        for (iVar3 = 0; iVar3 < 4; iVar3 = iVar3 + 1) {
          if (*(int *)(param_1 + iVar3 * 4 + 0x4c) != 0) {
            DelayDeleteRequest__6prim2DFv(*(undefined4 *)(param_1 + iVar3 * 4 + 0x4c));
            *(undefined4 *)(param_1 + iVar3 * 4 + 0x4c) = 0;
          }
        }
        if (*(int *)(param_1 + 0x8cc) == 0) {
          *(undefined4 *)(param_1 + 0xd8) = 4;
        }
        else {
          *(int *)(param_1 + 0x8d4) = *(int *)(param_1 + 0x8d4) + 1;
          *(undefined4 *)(param_1 + 0xd8) = 0;
        }
      }
      *(int *)(param_1 + 0x5c) = *(int *)(param_1 + 0x5c) + 1;
    }
    else if (iVar3 == 2) {
      play__9primSoundFi(*(undefined4 *)(param_1 + 0x60),0x1007);
      for (iVar3 = 0; iVar3 < 4; iVar3 = iVar3 + 1) {
        lVar2 = __nw__FUi(0x260);
        uVar1 = 0;
        if (lVar2 != 0) {
          uVar1 = __ct__6prim2DFi(lVar2,6);
        }
        *(undefined4 *)(param_1 + iVar3 * 4 + 0x4c) = uVar1;
        *(undefined4 *)(*(int *)(param_1 + iVar3 * 4 + 0x4c) + 0x30) = m_pTex;
        setDisp__6prim2DFiffff((float)(int)*(short *)(param_1 + *(int *)(param_1 + 0x8d4) * 0x50 + 0x12a) +
                        *(float *)(param_1 + 0x78),
                        (float)(int)*(short *)(param_1 + *(int *)(param_1 + 0x8d4) * 0x50 + 300) +
                        *(float *)(param_1 + 0x7c),0x3f000000,0x3f000000,
                        *(undefined4 *)(param_1 + iVar3 * 4 + 0x4c),2);
        setRotOffset__6prim2DFf(((float)iVar3 * 3.1415927) / 2.0,*(undefined4 *)(param_1 + iVar3 * 4 + 0x4c)
                       );
        setRot__6prim2DFf(0x3c23d70a,*(undefined4 *)(param_1 + iVar3 * 4 + 0x4c));
        setRGBA__6prim2DFiiii(*(undefined4 *)(param_1 + iVar3 * 4 + 0x4c),0x7f,0x7f,0x7f,0x80);
        setBlendMode__6prim2DFi(*(undefined4 *)(param_1 + iVar3 * 4 + 0x4c),0);
        setCenterMode__6prim2DFi(*(undefined4 *)(param_1 + iVar3 * 4 + 0x4c),4);
        if (iVar3 != 0) {
          setTexTrans__6prim2DFb(*(undefined4 *)(param_1 + iVar3 * 4 + 0x4c),0);
        }
      }
      *(undefined4 *)(param_1 + 0x5c) = 0;
      *(undefined4 *)(param_1 + 0xd8) = 3;
    }
    else if (iVar3 == 1) {
      if (*(int *)(param_1 + 0x88) == 0) {
        *(undefined4 *)(param_1 + 0xd8) = 2;
      }
      else {
        mWorldScroll__8worldMapFv(param_1);
      }
    }
    else if (iVar3 == 0) {
      if (*(int *)(param_1 + 0x8cc) == 0) {
        *(undefined4 *)(param_1 + 0xd8) = 4;
      }
      else {
        *(int *)(param_1 + 0x8cc) = *(int *)(param_1 + 0x8cc) + -1;
        while (*(char *)(param_1 + *(int *)(param_1 + 0x8d4) * 0x50 + 0x129) != '\x02') {
          *(int *)(param_1 + 0x8d4) = *(int *)(param_1 + 0x8d4) + 1;
        }
        *(undefined1 *)(param_1 + *(int *)(param_1 + 0x8d4) * 0x50 + 0x129) = 1;
        if (*(int *)(param_1 + 0x8e4) == *(int *)(param_1 + 0x8d4)) {
          dispThm__11worldMapThmFiPUcPUc
                    (*(undefined4 *)(param_1 + 0xac),
                     *(undefined1 *)(param_1 + *(int *)(param_1 + 0x8d4) * 0x50 + 0x127),
                     param_1 + *(int *)(param_1 + 0x8d4) * 0x50 + 0xde,
                     param_1 + *(int *)(param_1 + 0x8d4) * 0x50 + 0xfe);
          *(undefined4 *)(param_1 + 0xd8) = 2;
        }
        else {
          mSetWorldScroll__8worldMapFv(param_1);
          fadeout__11worldMapThmFv(*(undefined4 *)(param_1 + 0xac));
          *(undefined4 *)(param_1 + 0xd8) = 1;
        }
      }
    }
    uVar1 = 1;
  }
  return uVar1;
}

/* JP: 0x0050af70  worldMap::mSetupTutorialWin()   [mSetupTutorialWin__8worldMapFv]  size=0x134 */
void mSetupTutorialWin__8worldMapFv(int param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  long lVar3;
  
  lVar3 = __nw__FUi(0x148);
  uVar1 = 0;
  if (lVar3 != 0) {
    uVar1 = __ct__7primWinFv(lVar3);
  }
  *(undefined4 *)(param_1 + 0x920) = uVar1;
  uVar1 = *(undefined4 *)(param_1 + 0x920);
  initialize__7primWinFP7primTex(uVar1,*(undefined4 *)(param_1 + 0x2c));
  setItem__7primWinFiii(uVar1,2,0,1);
  setTextArea__7primWinFiiib(uVar1,1,0x200,0x100,1);
  uVar2 = addMessage__7primWinFiiPcib(uVar1,0,0xfffffffffffffffc,worldMapMess_tutorial_J,1,1);
  *(undefined4 *)(param_1 + 0x924) = uVar2;
  buildWin__7primWinFiiiiii(uVar1,5,0x80,0xc0,0x100,0x40,6);
  uVar1 = addKeyWait__7primWinFv(uVar1);
  *(undefined4 *)(param_1 + 0x928) = uVar1;
  *(byte *)(*(int *)(param_1 + 0x928) + 0x12) = *(byte *)(*(int *)(param_1 + 0x928) + 0x12) & 0xfe;
  return;
}

/* JP: 0x0050b0b0  worldMap::~worldMap()   [@24@__dt__8worldMapFv]  size=0x8 */
int _24___dt__8worldMapFv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x18;
  if (iVar1 != 0) {
    *(undefined1 **)(param_1 + -4) = &__vt__8worldMap;
    *(undefined4 *)(param_1 + 8) = 0x4098e0;
    Dispose__7CPollerFP7CPolObj(app__4CApp + 0x48,iVar1);
    if (*(int *)(param_1 + 0x14) != 0) {
      __dt__7primTexFv(*(undefined4 *)(param_1 + 0x14),1);
      *(undefined4 *)(param_1 + 0x14) = 0;
    }
    if (*(int *)(param_1 + 0x48) != 0) {
      DelayDeleteRequest__9primSoundFv(*(undefined4 *)(param_1 + 0x48));
      *(undefined4 *)(param_1 + 0x48) = 0;
    }
    ReleaseField__7MenuObjFv();
    ReleaseCmdMenu__7MenuObjFv();
    __dt__4FontFv(param_1 + 0x10,0xffffffffffffffff);
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
