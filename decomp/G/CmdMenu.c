/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CmdMenu   functions: 20
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CmdMenu.md).
 */

/* JP: 0x00435610  CmdMenu::DataEvent(int, void*)   [DataEvent__7CmdMenuFiPv]  size=0x12c */
void DataEvent__7CmdMenuFiPv(int param_1,int param_2)

{
  undefined8 uVar1;
  
  if (param_1 == 5) {
    MapJump__7CmdMenuFs(param_2,0);
    (**(code **)(*(int *)(param_2 + 0x14) + 0x24))(param_2,0x17);
  }
  else if (param_1 == 4) {
    uVar1 = GetScene__4MenuFs(param_2,0);
    DataAccessEvent__6CmdTopFv(uVar1);
  }
  else if (param_1 == 3) {
    AddPriority__12MenuObjTableFP7MenuObj(*(int *)(*(int *)(param_2 + 0xb0) + 0x58) + 0x2c,*(int *)(param_2 + 0xb0) + 0x5c
                   );
  }
  else if (param_1 == 1) {
    RemoveObj__12MenuObjTableFP7MenuObj(*(int *)(*(int *)(param_2 + 0xb0) + 0x58) + 0x2c,*(int *)(param_2 + 0xb0) + 0x5c
                   );
  }
  return;
}

/* JP: 0x00435740  CmdMenu::SolomonEvent(int, void*)   [SolomonEvent__7CmdMenuFiPv]  size=0x4c */
void SolomonEvent__7CmdMenuFiPv(int param_1,int param_2)

{
  if (param_1 == 3) {
    *(undefined4 *)(param_2 + 0x6c) = 0;
    *(undefined2 *)(param_2 + 0x3e) = 9;
  }
  return;
}

/* JP: 0x00435790  CmdMenu::SetParameter(MenuText*, short, short)   [SetParameter__7CmdMenuFP8MenuTextss]  size=0xc8 */
void SetParameter__7CmdMenuFP8MenuTextss(undefined4 param_1,short param_2,short param_3)

{
  if ((float)(int)param_2 / (float)(int)param_3 <= 0.25) {
    SetCSA__8FontItemFUc(param_1,9);
  }
  else if ((float)(int)param_2 / (float)(int)param_3 <= 0.5) {
    SetCSA__8FontItemFUc(param_1,0xd);
  }
  else {
    SetCSA__8FontItemFUc(param_1,0);
  }
  return;
}

/* JP: 0x00435860  CmdMenu::CmdMenu(short, int(*)(int, void*, CmdMenu*)*, void*)   [__ct__7CmdMenuFsPFiPvP7CmdMenu_iPv]  size=0x104 */
int __ct__7CmdMenuFsPFiPvP7CmdMenu_iPv
              (int param_1,short param_2,undefined4 param_3,undefined4 param_4)

{
  __ct__4MenuFv(param_1);
  *(undefined1 **)(param_1 + 0x14) = &__vt__7CmdMenu;
  *(undefined4 *)(param_1 + 0x20) = 0x407c50;
  __ct__10MenuRenderFv(param_1 + 0x70);
  __ct__8CmdPartyFv(param_1 + 0xb8);
  __ct__9CmdCommonFv(param_1 + 0x348);
  __ct__7CmdNoteFv(param_1 + 0x4e0);
  __ct__11CmdTitleLogFv(param_1 + 0x780);
  __ct__15CmdButtonReportFv(param_1 + 0xa60);
  __ct__10CmdElementFv(param_1 + 0x10f0);
  __ct__9MenuSceneFv(param_1 + 0x17a0);
  if (-1 < param_2) {
    Initialize__7CmdMenuFsPFiPvP7CmdMenu_iPv(param_1,param_2,param_3,param_4);
  }
  return param_1;
}

/* JP: 0x00435970  CmdMenu::~CmdMenu()   [__dt__7CmdMenuFv]  size=0x12c */
int __dt__7CmdMenuFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 0x14) = &__vt__7CmdMenu;
    *(undefined4 *)(param_1 + 0x20) = 0x407c50;
    Release__7CmdMenuFv(param_1);
    __dt__9MenuSceneFv(param_1 + 0x17a0,0xffffffffffffffff);
    __dt__10CmdElementFv(param_1 + 0x10f0,0xffffffffffffffff);
    __dt__15CmdButtonReportFv(param_1 + 0xa60,0xffffffffffffffff);
    __dt__11CmdTitleLogFv(param_1 + 0x780,0xffffffffffffffff);
    __dt__7CmdNoteFv(param_1 + 0x4e0,0xffffffffffffffff);
    __dt__9CmdCommonFv(param_1 + 0x348,0xffffffffffffffff);
    __dt__8CmdPartyFv(param_1 + 0xb8,0xffffffffffffffff);
    __dt__10MenuRenderFv(param_1 + 0x70,0xffffffffffffffff);
    __dt__4MenuFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x00435aa0  CmdMenu::Polling()   [Polling__7CmdMenuFv]  size=0x7b4 */
undefined4 Polling__7CmdMenuFv(undefined8 param_1)

{
  bool bVar1;
  int iVar2;
  long lVar3;
  int iVar4;
  
  iVar4 = (int)param_1;
  switch(*(undefined2 *)(iVar4 + 0x3e)) {
  case 0:
    lVar3 = GetScene__4MenuFs(param_1,*(undefined2 *)(iVar4 + 0x40));
    if (((lVar3 != 0) &&
        (iVar2 = GetScene__4MenuFs(param_1,*(undefined2 *)(iVar4 + 0x40)),
        (long)((ulong)*(byte *)(iVar2 + 0x23) << 0x3b) < 0)) &&
       ((*(int *)(iVar4 + 0x50) == 0 ||
        (lVar3 = (**(code **)(iVar4 + 0x50))(6,*(undefined4 *)(iVar4 + 0x54),param_1), lVar3 != 0)))
       ) {
      DisablePause__6CPauseFv(*(undefined4 *)(app__4CApp + 0x78));
      if (*(int *)(iVar4 + 0xac) == 0) {
        *(undefined2 *)(iVar4 + 0x3e) = 1;
      }
      else {
        Capture__11MenuCaptureFiss6GS_PSMUc(*(undefined4 *)(iVar4 + 0xac),0xd,0x200,0xe0,1,0x80);
        *(undefined2 *)(iVar4 + 0x3e) = 2;
      }
    }
    break;
  case 1:
    if (*(char *)(iVar4 + 0x3d) != '\0') {
      if (*(int *)(iVar4 + 0xac) == 0) {
        CreateBackGround__7CmdMenuFs(param_1,8);
      }
      else {
        CreateBackGround__7CmdMenuFs(param_1,7);
      }
      if (*(int *)(iVar4 + 0x50) != 0) {
        (**(code **)(iVar4 + 0x50))(0,*(undefined4 *)(iVar4 + 0x54),param_1);
      }
      *(undefined2 *)(iVar4 + 0x3e) = 3;
    }
    break;
  case 2:
    if (*(char *)(*(int *)(iVar4 + 0xac) + 0x5e) != '\0') {
      *(undefined2 *)(iVar4 + 0x3e) = 1;
    }
    break;
  case 3:
    if ((*(char *)(*(int *)(iVar4 + 0xb0) + 0x104) == '\x01') ||
       (*(char *)(*(int *)(iVar4 + 0xb0) + 0x104) == '\0')) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
    if (bVar1) {
      if (*(int *)(iVar4 + 0x50) != 0) {
        (**(code **)(iVar4 + 0x50))(1,*(undefined4 *)(iVar4 + 0x54),param_1);
      }
      *(undefined4 *)(*(int *)(iVar4 + 100) + 0x180) = 0;
      *(char *)(iVar4 + 0x3c) = (char)m_syncCount__3Gsx;
      SetFFMode__3GsxFibi(0,1,1);
      if (*(short *)(*(int *)(iVar4 + 0xb0) + 0x1c) == 7) {
        CreateLight__7CmdMenuFv(param_1);
        iVar2 = *(int *)(iVar4 + 100);
        *(undefined4 *)(iVar2 + 0x380) = 0x3f800000;
        *(undefined4 *)(iVar2 + 900) = 0x447a0000;
        *(undefined4 *)(iVar2 + 0x360) = 0;
        *(undefined4 *)(iVar2 + 0x364) = *(undefined4 *)(iVar2 + 0x380);
        *(float *)(iVar2 + 0x368) = 256.0 / (*(float *)(iVar2 + 900) - *(float *)(iVar2 + 0x380));
        *(undefined4 *)(iVar2 + 0x36c) = 0x437f0000;
        SetViewMatrix__9GsxCameraFfffff(0x44000000,0x3f4ccccd,0x3f6eeeef,0x3f800000,0x4b7fff28,
                        *(undefined4 *)(iVar4 + 100));
      }
      ChengeLayer__10MenuRenderFi(iVar4 + 0x70,1);
      (**(code **)(*(int *)(iVar4 + 0x14) + 0x24))(param_1,*(undefined2 *)(iVar4 + 0x40));
      Open__10MenuWindowFUci(iVar4 + 0x538,*(byte *)(iVar4 + 0x5e8) & 7,
                      *(undefined4 *)(*(int *)(iVar4 + 0x56c) + 0x10));
      PlaySE__9MenuSoundFUiUcP8_SeParam(sm_pSound__7MenuObj,5,0,0);
      *(undefined2 *)(iVar4 + 0x3e) = 4;
    }
    break;
  case 4:
    Run__4MenuFv(param_1);
    break;
  case 5:
    if (*(char *)(iVar4 + 0x4d) == '\0') {
      if ((*(int *)(iVar4 + 0xb0) != 0) &&
         ((long)((ulong)*(byte *)(*(int *)(iVar4 + 0xb0) + 0x6e) << 0x3d) < 0)) {
        if ((*(char *)(*(int *)(iVar4 + 0xb0) + 0x104) == '\x01') ||
           (*(char *)(*(int *)(iVar4 + 0xb0) + 0x104) == '\0')) {
          bVar1 = true;
        }
        else {
          bVar1 = false;
        }
        if (!bVar1) {
          return 0;
        }
      }
      DestroyBackGround__7CmdMenuFs(param_1,0);
      Dispose__10MenuRenderFv(iVar4 + 0x70);
      EnablePause__6CPauseFi(*(undefined4 *)(app__4CApp + 0x78),1);
      if (*(int *)(iVar4 + 0x50) != 0) {
        (**(code **)(iVar4 + 0x50))(3,*(undefined4 *)(iVar4 + 0x54),param_1);
      }
      (**(code **)(*(int *)(iVar4 + 0x20) + 0xc))();
      return 1;
    }
    break;
  case 6:
    if ((*(int *)(iVar4 + 0x50) == 0) ||
       (lVar3 = (**(code **)(iVar4 + 0x50))(2,*(undefined4 *)(iVar4 + 0x54),param_1), lVar3 != 0)) {
      ChengeLayer__10MenuRenderFi(iVar4 + 0x70,0xe);
      if ((*(int *)(iVar4 + 0xb0) != 0) &&
         ((long)((ulong)*(byte *)(*(int *)(iVar4 + 0xb0) + 0x6e) << 0x3d) < 0)) {
        if ((*(char *)(*(int *)(iVar4 + 0xb0) + 0x104) == '\x01') ||
           (*(char *)(*(int *)(iVar4 + 0xb0) + 0x104) == '\0')) {
          bVar1 = true;
        }
        else {
          bVar1 = false;
        }
        if (bVar1) {
          iVar2 = *(int *)(iVar4 + 0xb0);
          Close__10MenuWindowFUci(iVar2 + 0x5c,((ulong)*(byte *)(iVar2 + 0x10c) & 0x3f) >> 3,
                          *(undefined4 *)(*(int *)(iVar2 + 0x90) + 0x14));
        }
      }
      *(undefined2 *)(iVar4 + 0x3e) = 5;
    }
    break;
  case 7:
    ReleaseScene__7CmdMenuFv(param_1);
    DestroyBackGround__7CmdMenuFs(param_1,0);
    *(undefined2 *)(iVar4 + 0x40) = 0;
    *(undefined2 *)(iVar4 + 0x42) = 0x17;
    *(undefined2 *)(iVar4 + 0x44) = 0xc;
    start__7solomonFv(*(undefined4 *)(iVar4 + 0x6c));
    *(undefined2 *)(iVar4 + 0x3e) = 8;
    break;
  case 9:
    *(undefined2 *)(iVar4 + 0x3e) = 10;
    break;
  case 10:
    CreateScene__7CmdMenuFv(param_1);
    (**(code **)(*(int *)(iVar4 + 0x14) + 0x24))(param_1,0);
    CreateBackGround__7CmdMenuFs(param_1,7);
    *(undefined2 *)(iVar4 + 0x3e) = 4;
    break;
  case 0xb:
    if ((long)((ulong)*(byte *)(sm_pCmdMenu__7MenuObj + 0x23) << 0x3b) < 0) {
      CreateFont__4FontFiPUc(3,*(undefined4 *)(*(int *)(sm_pCmdMenu__7MenuObj + 0x54) + 0x10));
      CreateFont__4FontFiPUc(2,*(undefined4 *)(*(int *)(sm_pCmdMenu__7MenuObj + 0x54) + 0x1c));
      Create__11MenuTextureFPUc6GS_PSMUii(0x421ab0,*(undefined4 *)(*(int *)(sm_pCmdMenu__7MenuObj + 0x54) + 0x28),0x30,0,0);
      Create__11MenuTextureFPUc6GS_PSMUii(0x421af0,*(undefined4 *)(*(int *)(sm_pCmdMenu__7MenuObj + 0x54) + 0x34),0x30,0,0);
      Create__13MenuDataTableFPUcP9BufMemory(iVar4 + 0x28,*(undefined4 *)(*(int *)(sm_pCmdMenu__7MenuObj + 0x54) + 0x94),0);
      Create__8CmdPartyFP13MenuDataTable(iVar4 + 0xb8,iVar4 + 0x28);
      CreateScene__7CmdMenuFv(param_1);
      Create__10MenuRenderFv(iVar4 + 0x70);
      Entry__10MenuRenderFi(iVar4 + 0x70,0xe);
      *(undefined4 *)(iVar4 + 0xb4) = 0;
      *(undefined4 *)(iVar4 + 0xb0) = 0;
      *(undefined2 *)(iVar4 + 0x3e) = 0;
    }
  }
  return 0;
}

/* JP: 0x00436260  CmdMenu::Active(short)   [Active__7CmdMenuFs]  size=0x12c */
void Active__7CmdMenuFs(int param_1,short param_2)

{
  long lVar1;
  
  lVar1 = GetScene__4MenuFs(param_1,param_2);
  *(int *)(param_1 + 0x34) = (int)lVar1;
  if (lVar1 == 0) {
    ReleaseOT__7MenuObjFv(param_1 + 0x3a0);
    ReleaseOT__7MenuObjFv(param_1 + 0x538);
    ReleaseOT__7MenuObjFv(param_1 + 0x7d8);
    ReleaseOT__7MenuObjFv(param_1 + 0xab8);
    ReleaseOT__7MenuObjFv(param_1 + 0x1148);
    if (param_2 == 0x15) {
      *(undefined2 *)(param_1 + 0x3e) = 7;
    }
    else {
      if (-1 < *(char *)(param_1 + 0x3c)) {
        SetFFMode__3GsxFibi(0,1,*(undefined1 *)(param_1 + 0x3c));
      }
      ReleaseLight__7CmdMenuFv(param_1);
      *(undefined2 *)(param_1 + 0x3e) = 6;
      *(undefined2 *)(param_1 + 0x40) = 0;
    }
  }
  return;
}

/* JP: 0x00436390  CmdMenu::Ready(short, short, short)   [Ready__7CmdMenuFsss]  size=0x6e4 */
int Ready__7CmdMenuFsss(int param_1,ushort param_2,undefined2 param_3,undefined2 param_4)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  long lVar4;
  
  *(ushort *)(param_1 + 0x40) = param_2;
  *(undefined2 *)(param_1 + 0x42) = param_3;
  *(undefined2 *)(param_1 + 0x44) = param_4;
  iVar1 = GetScene__4MenuFs(param_1,param_2);
  if (iVar1 == 0) {
    switch(param_2) {
    case 0:
      iVar2 = __nw__FUi(0x90);
      iVar1 = 0;
      if (iVar2 != 0) {
        iVar1 = __ct__6CmdTopFv(iVar2);
      }
      break;
    case 1:
      iVar2 = __nw__FUi(0xa0);
      iVar1 = 0;
      if (iVar2 != 0) {
        iVar1 = __ct__7CmdItemFv(iVar2);
      }
      break;
    case 2:
      iVar2 = __nw__FUi(0x360);
      iVar1 = 0;
      if (iVar2 != 0) {
        iVar1 = __ct__13CmdWhiteMagicFv(iVar2);
      }
      break;
    case 3:
      iVar2 = __nw__FUi(0x368);
      iVar1 = 0;
      if (iVar2 != 0) {
        iVar1 = __ct__8CmdMagicFv(iVar2);
      }
      break;
    case 4:
      iVar2 = __nw__FUi(0x9c0);
      iVar1 = 0;
      if (iVar2 != 0) {
        iVar1 = __ct__8CmdCrestFv(iVar2);
      }
      break;
    case 5:
      iVar2 = __nw__FUi(0xd0);
      iVar1 = 0;
      if (iVar2 != 0) {
        iVar1 = __ct__12CmdEquipmentFv(iVar2);
      }
      break;
    case 6:
      iVar2 = __nw__FUi(0x220);
      iVar1 = 0;
      if (iVar2 != 0) {
        iVar1 = __ct__13CmdRingCustomFv(iVar2);
      }
      break;
    case 7:
      iVar2 = __nw__FUi(0x98);
      iVar1 = 0;
      if (iVar2 != 0) {
        iVar1 = __ct__10CmdPrivateFv(iVar2);
      }
      break;
    case 8:
      lVar4 = __nw__FUi(0xe58);
      iVar1 = 0;
      if (lVar4 != 0) {
        iVar1 = __ct__12CmdFormationFv(lVar4);
      }
      break;
    case 9:
      lVar4 = __nw__FUi(0x31c);
      iVar1 = 0;
      if (lVar4 != 0) {
        iVar1 = __ct__12CmdGraveyardFv(lVar4);
      }
      break;
    case 10:
      lVar4 = __nw__FUi(0xcc0);
      iVar1 = 0;
      if (lVar4 != 0) {
        iVar1 = __ct__11CmdComboKeyFv(lVar4);
      }
      break;
    case 0xb:
      iVar2 = __nw__FUi(0x188);
      iVar1 = 0;
      if (iVar2 != 0) {
        iVar1 = __ct__13CmdComboMagicFv(iVar2);
      }
      break;
    case 0xc:
      iVar2 = __nw__FUi(0x2f0);
      iVar1 = 0;
      if (iVar2 != 0) {
        iVar1 = __ct__7CmdHelpFv(iVar2);
      }
      break;
    case 0xd:
      lVar4 = __nw__FUi(0x2dc);
      iVar1 = 0;
      if (lVar4 != 0) {
        iVar1 = __ct__8CmdScoreFv(lVar4);
      }
      break;
    case 0xe:
      lVar4 = __nw__FUi(0x208);
      iVar1 = 0;
      if (lVar4 != 0) {
        iVar1 = __ct__10CmdLibraryFv(lVar4);
      }
      break;
    case 0xf:
      lVar4 = __nw__FUi(0x16c);
      iVar1 = 0;
      if (lVar4 != 0) {
        iVar1 = __ct__15CmdPropertyListFv(lVar4);
      }
      break;
    case 0x10:
      iVar2 = __nw__FUi(0x2640);
      iVar1 = 0;
      if (iVar2 != 0) {
        iVar1 = __ct__9CmdOptionFv(iVar2);
      }
      break;
    case 0x11:
      lVar4 = __nw__FUi(0x1c10);
      iVar1 = 0;
      if (lVar4 != 0) {
        iVar1 = __ct__12CmdKeyCustomFv(lVar4);
      }
      break;
    case 0x15:
      lVar4 = __nw__FUi(0xbd0);
      uVar3 = 0;
      if (lVar4 != 0) {
        uVar3 = __ct__7solomonFv(lVar4);
      }
      *(undefined4 *)(param_1 + 0x6c) = uVar3;
      initialize__7solomonFPFiPv_vPv(*(undefined4 *)(param_1 + 0x6c),0x435740,param_1);
    default:
      if (*(char *)(param_1 + 0x5e0) != '\0') {
        Close__10MenuWindowFUci(param_1 + 0x538,((ulong)*(byte *)(param_1 + 0x5e8) & 0x3f) >> 3,
                        *(undefined4 *)(*(int *)(param_1 + 0x56c) + 0x14));
      }
      return 0;
    }
    *(ushort *)(iVar1 + 0x1c) = param_2;
    if (param_2 == 0) {
      *(int *)(iVar1 + 0x10) = param_1;
      Initialize__9MenuSceneFPUcP9BufMemory(iVar1,*(undefined4 *)(*(int *)(sm_pCmdMenu__7MenuObj + 0x54) + 0x70),0);
    }
    else {
      OrderFile__9MenuSceneFPCcP4Menu(iVar1,*(undefined4 *)((uint)param_2 * 8 + *(int *)(param_1 + 0x36c) + 0x10),
                      param_1);
    }
    AddScene__4MenuFP9MenuScene(param_1,iVar1);
  }
  else {
    (**(code **)(*(int *)(iVar1 + 8) + 0x14))();
  }
  *(undefined1 *)(param_1 + 0x4e) = 0;
  return iVar1;
}

/* JP: 0x00436a80  CmdMenu::Initialize(short, int(*)(int, void*, CmdMenu*)*, void*)   [Initialize__7CmdMenuFsPFiPvP7CmdMenu_iPv]  size=0x180 */
void Initialize__7CmdMenuFsPFiPvP7CmdMenu_iPv
               (int param_1,short param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  long lVar2;
  
  *(undefined4 *)(param_1 + 100) = camera__4CApp;
  *(undefined2 *)(param_1 + 0x4a) = 3;
  *(undefined4 *)(param_1 + 0xac) = 0;
  *(undefined4 *)(param_1 + 0x5c) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x58) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x68) = 0;
  if (param_2 == 0) {
    lVar2 = __nw__FUi(0x60);
    uVar1 = 0;
    if (lVar2 != 0) {
      uVar1 = __ct__11MenuCaptureFv(lVar2);
    }
    *(undefined4 *)(param_1 + 0xac) = uVar1;
    *(undefined2 *)(param_1 + 0x44) = 0;
  }
  else {
    *(undefined1 *)(param_1 + 0x4f) = 1;
  }
  *(short *)(param_1 + 0x40) = param_2;
  *(undefined2 *)(param_1 + 0x42) = 0x17;
  *(undefined4 *)(param_1 + 0x50) = param_3;
  *(undefined4 *)(param_1 + 0x54) = param_4;
  *(undefined1 *)(param_1 + 0x3d) = 0;
  *(undefined2 *)(param_1 + 0x3e) = 0xb;
  lVar2 = __nw__FUi(0x70);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = __ct__16MenuModelManegerFv(lVar2);
  }
  *(undefined4 *)(param_1 + 0x68) = uVar1;
  Create__16MenuModelManegerFPCc(*(undefined4 *)(param_1 + 0x68),0);
  Entry__7CPollerFP7CPolObjib(app__4CApp + 0x48,param_1,0x40,0);
  return;
}

/* JP: 0x00436c00  CmdMenu::Release()   [Release__7CmdMenuFv]  size=0x170 */
void Release__7CmdMenuFv(int param_1)

{
  int iVar1;
  
  FlushData__8CmdPartyFv(param_1 + 0xb8);
  ClearFont__4FontFi(3);
  ClearFont__4FontFi(2);
  ReleaseImage__8MenuFontFv();
  DestroyList__4MenuFv(param_1);
  if (*(int *)(param_1 + 0x24) != 0) {
    __dt__9BufMemoryFv(*(undefined4 *)(param_1 + 0x24),1);
    *(undefined4 *)(param_1 + 0x24) = 0;
  }
  if (*(int *)(param_1 + 0xac) != 0) {
    iVar1 = *(int *)(param_1 + 0xac);
    if (iVar1 != 0) {
      (**(code **)(*(int *)(iVar1 + 0x10) + 8))(iVar1,1);
    }
    *(undefined4 *)(param_1 + 0xac) = 0;
  }
  if (*(int *)(param_1 + 0x68) != 0) {
    iVar1 = *(int *)(param_1 + 0x68);
    *(undefined1 *)(iVar1 + 0xc) = 1;
    *(undefined1 *)(iVar1 + 0xe) = 0;
    Destroy__16MenuModelManegerFUc(*(undefined4 *)(param_1 + 0x68),1);
  }
  if (*(int *)(param_1 + 0x50) != 0) {
    (**(code **)(param_1 + 0x50))(5,*(undefined4 *)(param_1 + 0x54),param_1);
  }
  if ((*(short *)(param_1 + 0x40) != 0) && (*(char *)(param_1 + 0x4f) == '\0')) {
    FieldMapJumpGY__FPCc(0x555798);
  }
  return;
}

/* JP: 0x00436d70  CmdMenu::CreateScene()   [CreateScene__7CmdMenuFv]  size=0x1a4 */
void CreateScene__7CmdMenuFv(int param_1)

{
  *(int *)(param_1 + 0x358) = param_1;
  Initialize__9MenuSceneFPUcP9BufMemory(param_1 + 0x348,*(undefined4 *)(*(int *)(sm_pCmdMenu__7MenuObj + 0x54) + 0x40),0);
  *(int *)(param_1 + 0x4f0) = param_1;
  Initialize__9MenuSceneFPUcP9BufMemory(param_1 + 0x4e0,*(undefined4 *)(*(int *)(sm_pCmdMenu__7MenuObj + 0x54) + 0x4c),0);
  *(int *)(param_1 + 0x790) = param_1;
  Initialize__9MenuSceneFPUcP9BufMemory(param_1 + 0x780,*(undefined4 *)(*(int *)(sm_pCmdMenu__7MenuObj + 0x54) + 0x58),0);
  OrderFile__9MenuSceneFPCcP4Menu(param_1 + 0x10f0,*(undefined4 *)(*(int *)(param_1 + 0x36c) + 0xa0),param_1);
  OrderFile__9MenuSceneFPCcP4Menu(param_1 + 0xa60,*(undefined4 *)(*(int *)(param_1 + 0x36c) + 0xa8),param_1);
  OrderFile__9MenuSceneFPCcP4Menu(param_1 + 0x17a0,*(undefined4 *)(*(int *)(param_1 + 0x36c) + 0xb0),param_1);
  (**(code **)(*(int *)(param_1 + 0x14) + 0x28))
            (param_1,*(undefined2 *)(param_1 + 0x40),*(undefined2 *)(param_1 + 0x42),
             *(undefined2 *)(param_1 + 0x44));
  return;
}

/* JP: 0x00436f20  CmdMenu::ReleaseScene()   [ReleaseScene__7CmdMenuFv]  size=0xac */
void ReleaseScene__7CmdMenuFv(int param_1)

{
  (**(code **)(*(int *)(param_1 + 0x350) + 0x18))();
  (**(code **)(*(int *)(param_1 + 0x4e8) + 0x18))();
  (**(code **)(*(int *)(param_1 + 0x788) + 0x18))();
  (**(code **)(*(int *)(param_1 + 0x10f8) + 0x18))();
  (**(code **)(*(int *)(param_1 + 0xa68) + 0x18))();
  (**(code **)(*(int *)(param_1 + 0x17a8) + 0x18))();
  return;
}

/* JP: 0x00436fd0  CmdMenu::MapJump(short)   [MapJump__7CmdMenuFs]  size=0x70 */
void MapJump__7CmdMenuFs(int param_1,undefined2 param_2)

{
  if (*(int *)(param_1 + 0x50) != 0) {
    (**(code **)(param_1 + 0x50))(4,*(undefined4 *)(param_1 + 0x54),param_1);
  }
  *(undefined1 *)(param_1 + 0x3c) = 0xff;
  *(undefined4 *)(param_1 + 0x50) = 0;
  *(undefined2 *)(param_1 + 0x40) = param_2;
  return;
}

/* JP: 0x00437040  CmdMenu::CreateBackGround(short)   [CreateBackGround__7CmdMenuFs]  size=0x304 */
undefined4 CreateBackGround__7CmdMenuFs(int param_1,short param_2)

{
  int iVar1;
  undefined4 uVar2;
  long lVar3;
  
  if (*(int *)(param_1 + 0xb0) != 0) {
    if (param_2 == *(short *)(*(int *)(param_1 + 0xb0) + 0x1c)) {
      if (*(char *)(*(int *)(param_1 + 0xb0) + 0x104) == '\0') {
        iVar1 = *(int *)(param_1 + 0xb0);
        Open__10MenuWindowFUci(iVar1 + 0x5c,*(byte *)(iVar1 + 0x10c) & 7,
                        *(undefined4 *)(*(int *)(iVar1 + 0x90) + 0x10));
      }
      return 0;
    }
    DestroyBackGround__7CmdMenuFs(param_1,1);
    *(undefined4 *)(param_1 + 0xb4) = *(undefined4 *)(param_1 + 0xb0);
  }
  if ((param_2 == 9) || (param_2 == 8)) {
    lVar3 = __nw__FUi(0x1e0);
    uVar2 = 0;
    if (lVar3 != 0) {
      uVar2 = __ct__13CmdBackGroundFv(lVar3);
    }
    *(undefined4 *)(param_1 + 0xb0) = uVar2;
    *(short *)(*(int *)(param_1 + 0xb0) + 0x10a) = param_2 + -8;
    *(int *)(*(int *)(param_1 + 0xb0) + 0x58) = param_1 + 0x70;
    Initialize__9MenuSceneFPUcP9BufMemory(*(undefined4 *)(param_1 + 0xb0),*(undefined4 *)(*(int *)(param_1 + 0x17ac) + 4),
                    0);
  }
  else if (param_2 == 7) {
    lVar3 = __nw__FUi(0x398);
    uVar2 = 0;
    if (lVar3 != 0) {
      uVar2 = __ct__20CmdBackGroundCaptureFP11MenuCapture(lVar3,*(undefined4 *)(param_1 + 0xac));
    }
    *(undefined4 *)(param_1 + 0xb0) = uVar2;
    *(int *)(*(int *)(param_1 + 0xb0) + 0x58) = param_1 + 0x70;
    Initialize__9MenuSceneFPUcP9BufMemory(*(undefined4 *)(param_1 + 0xb0),
                    *(undefined4 *)(*(int *)(sm_pCmdMenu__7MenuObj + 0x54) + 100),0);
  }
  *(short *)(*(int *)(param_1 + 0xb0) + 0x1c) = param_2;
  iVar1 = *(int *)(param_1 + 0xb0);
  Open__10MenuWindowFUci(iVar1 + 0x5c,*(byte *)(iVar1 + 0x10c) & 7,
                  *(undefined4 *)(*(int *)(iVar1 + 0x90) + 0x10));
  return 1;
}

/* JP: 0x00437350  CmdMenu::DestroyBackGround(short)   [DestroyBackGround__7CmdMenuFs]  size=0x94 */
void DestroyBackGround__7CmdMenuFs(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + param_2 * 4 + 0xb0);
  *(undefined4 *)(param_1 + param_2 * 4 + 0xb0) = 0;
  if (iVar1 != 0) {
    RemoveObj__12MenuObjTableFP7MenuObj(*(int *)(iVar1 + 0x58) + 0x2c,iVar1 + 0x5c);
    (**(code **)(*(int *)(iVar1 + 8) + 0xc))();
  }
  return;
}

/* JP: 0x004373f0  CmdMenu::SetCamera(MenuDataModel*)   [SetCamera__7CmdMenuFP13MenuDataModel]  size=0xdc */
void SetCamera__7CmdMenuFP13MenuDataModel(int param_1,undefined4 *param_2)

{
  int iVar1;
  undefined1 auVar2 [16];
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined1 in_vf0 [16];
  undefined1 auVar7 [16];
  undefined1 auVar8 [16];
  undefined1 auVar9 [16];
  
  iVar1 = *(int *)(*(int *)(param_1 + 0x68) + 0x18);
  uVar4 = *param_2;
  uVar5 = param_2[1];
  uVar6 = param_2[2];
  iVar3 = *(int *)(param_1 + 100);
  auVar7 = _vmr32(in_vf0);
  auVar8 = _vmr32(auVar7);
  auVar9 = _vmr32(auVar8);
  auVar2 = _sqc2(in_vf0);
  *(undefined1 (*) [16])(iVar3 + 0x270) = auVar2;
  auVar2 = _sqc2(auVar7);
  *(undefined1 (*) [16])(iVar3 + 0x260) = auVar2;
  auVar2 = _sqc2(auVar8);
  *(undefined1 (*) [16])(iVar3 + 0x250) = auVar2;
  auVar2 = _sqc2(auVar9);
  *(undefined1 (*) [16])(iVar3 + 0x240) = auVar2;
  iVar3 = *(int *)(param_1 + 100) + 0x240;
  sceVu0RotMatrixX(param_2[3],iVar3,iVar3);
  iVar3 = *(int *)(param_1 + 100);
  *(undefined4 *)(iVar3 + 0x270) = uVar4;
  *(undefined4 *)(iVar3 + 0x274) = uVar5;
  *(undefined4 *)(iVar3 + 0x278) = uVar6;
  *(undefined4 *)(iVar3 + 0x27c) = 0x3f800000;
  ApplyFrame__9GsxCameraFv(*(undefined4 *)(param_1 + 100));
  SetAngle__9MenuModelFf(param_2[4],*(undefined4 *)(iVar1 + 0x20));
  return;
}

/* JP: 0x004374d0  CmdMenu::IsSetupScene()   [IsSetupScene__7CmdMenuFv]  size=0x74 */
undefined4 IsSetupScene__7CmdMenuFv(int param_1)

{
  undefined4 uVar1;
  
  if ((((long)((ulong)*(byte *)(param_1 + 0x1113) << 0x3b) < 0) &&
      ((long)((ulong)*(byte *)(param_1 + 0xa83) << 0x3b) < 0)) &&
     ((long)((ulong)*(byte *)(param_1 + 0x17c3) << 0x3b) < 0)) {
    uVar1 = 1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

/* JP: 0x00437550  CmdMenu::CreateLight()   [CreateLight__7CmdMenuFv]  size=0x168 */
void CreateLight__7CmdMenuFv(int param_1)

{
  undefined4 uVar1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined1 auStack_70 [16];
  undefined1 auStack_60 [16];
  undefined1 auStack_50 [16];
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  int iStack_10;
  
  uStack_20 = 0x3e4ccccd;
  uStack_1c = 0x3e4ccccd;
  uStack_18 = 0x3e4ccccd;
  uStack_14 = 0x3f800000;
  uStack_30 = 0xbe4511a4;
  uStack_2c = 0xbe4511a4;
  uStack_28 = 0x3f76560c;
  uStack_24 = 0x3f800000;
  uStack_40 = 0x3f666666;
  uStack_3c = 0x3f666666;
  uStack_38 = 0x3f666666;
  uStack_34 = 0x3f800000;
  iStack_10 = param_1;
  uVar2 = __ct__7FVectorFRC7FVector(auStack_50,&uStack_20);
  uVar1 = CreateAmbient__12LightControlF7FVector(uVar2);
  *(undefined4 *)(iStack_10 + 0x58) = uVar1;
  uVar2 = __ct__7FVectorFRC7FVector(auStack_60,&uStack_30);
  uVar3 = __ct__7FVectorFRC7FVector(auStack_70,&uStack_40);
  uVar1 = CreateDirectional__12LightControlF7FVector7FVector(uVar2,uVar3);
  *(undefined4 *)(iStack_10 + 0x5c) = uVar1;
  return;
}

/* JP: 0x004376c0  CmdMenu::ReleaseLight()   [ReleaseLight__7CmdMenuFv]  size=0x68 */
void ReleaseLight__7CmdMenuFv(int param_1)

{
  if (-1 < *(int *)(param_1 + 0x58)) {
    release__12LightControlFi(*(undefined4 *)(param_1 + 0x58));
    release__12LightControlFi(*(undefined4 *)(param_1 + 0x5c));
    *(undefined4 *)(param_1 + 0x58) = 0xffffffff;
    *(undefined4 *)(param_1 + 0x5c) = 0xffffffff;
  }
  return;
}

/* JP: 0x00437730  CmdMenu::~CmdMenu()   [@24@__dt__7CmdMenuFv]  size=0x8 */
int _24___dt__7CmdMenuFv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x18;
  if (iVar1 != 0) {
    *(undefined1 **)(param_1 + -4) = &__vt__7CmdMenu;
    *(undefined4 *)(param_1 + 8) = 0x407c50;
    Release__7CmdMenuFv(iVar1);
    __dt__9MenuSceneFv(param_1 + 0x1788,0xffffffffffffffff);
    __dt__10CmdElementFv(param_1 + 0x10d8,0xffffffffffffffff);
    __dt__15CmdButtonReportFv(param_1 + 0xa48,0xffffffffffffffff);
    __dt__11CmdTitleLogFv(param_1 + 0x768,0xffffffffffffffff);
    __dt__7CmdNoteFv(param_1 + 0x4c8,0xffffffffffffffff);
    __dt__9CmdCommonFv(param_1 + 0x330,0xffffffffffffffff);
    __dt__8CmdPartyFv(param_1 + 0xa0,0xffffffffffffffff);
    __dt__10MenuRenderFv(param_1 + 0x58,0xffffffffffffffff);
    __dt__4MenuFv(iVar1,0);
    if (0 < param_2) {
      __dl__FPv(iVar1);
    }
  }
  return iVar1;
}
