/*
 * BtlSocket.c -- Ghidra decompiler output (SLPM_602.19, JP Furokuban), tidied by tools/E_gen_decomp.py
 * 18 functions. Types: u8/u16/u32/u64 = undefined1/2/4/8. Addresses in comments are JP main-exe addresses.
 */

/* ---- 0x0032d610 size 0x1dc  BtlSocket::BtlSocket(v)
 *      mangled: __ct__9BtlSocketFv */
int __ct__9BtlSocketFv(int param_1)

{
  u32 uVar1;
  long lVar2;
  int iVar3;
  
  *(u8 **)(param_1 + 4) = __vt__6SSHApi;
  __ct__7CPolObjFv(param_1 + 8);
  *(u8 **)(param_1 + 4) = __vt__9BtlSocket;
  *(u32 *)(param_1 + 0x1c) = 0x406db0;
  ourBtlSocket__9BtlSocket = param_1;
  *(u32 *)(param_1 + 0x20) = 0;
  *(u32 *)(param_1 + 0x28) = 0;
  *(u32 *)(param_1 + 0x24) = 0;
  *(u32 *)(param_1 + 0x164) = 0;
  *(u32 *)(param_1 + 0x160) = 0;
  *(u8 *)(param_1 + 0x47) = 0;
  *(u8 *)(param_1 + 0x49) = 0;
  *(u32 *)(param_1 + 0x58) = 0;
  *(u8 *)(param_1 + 0x600) = 0;
  *(u8 *)(param_1 + 0x601) = 0;
  *(u16 *)(param_1 + 0x602) = 0xffff;
  for (iVar3 = 0; iVar3 < 0x20; iVar3 = iVar3 + 1) {
    *(u32 *)(param_1 + iVar3 * 4 + 0x604) = 0;
  }
  *(u32 *)(param_1 + 0x684) = 0;
  *(u32 *)(param_1 + 0x688) = 0;
  uVar1 = GetYoahism__10BtlSaveSecFv();
  *(u32 *)(param_1 + 0x698) = uVar1;
  lVar2 = __nw__FUi(0x38);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = __ct__12SmoothFilterFv(lVar2);
  }
  *(u32 *)(param_1 + 0x68c) = uVar1;
  FilterLevel__12SmoothFilterFf(0x3f800000,*(u32 *)(param_1 + 0x68c));
  FilterAlpha__12SmoothFilterFi(*(u32 *)(param_1 + 0x68c),0x40);
  lVar2 = __nw__FUi(0x30);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = __ct__10BlurFilterFv(lVar2);
  }
  *(u32 *)(param_1 + 0x690) = uVar1;
  FilterAlpha__10BlurFilterFi(*(u32 *)(param_1 + 0x690),0x14);
  *(u8 *)(param_1 + 0x168) = 0;
  return param_1;
}

/* ---- 0x0032d860 size 0x1dc  BtlSocket::~BtlSocket(v)
 *      mangled: __dt__9BtlSocketFv */
int __dt__9BtlSocketFv(int param_1,short param_2)

{
  int iVar1;
  int iVar2;
  
  if (param_1 != 0) {
    *(u8 **)(param_1 + 4) = __vt__9BtlSocket;
    *(u32 *)(param_1 + 0x1c) = 0x406db0;
    for (iVar2 = 0; iVar2 < 0x20; iVar2 = iVar2 + 1) {
      if (*(int *)(param_1 + iVar2 * 4 + 0x604) != 0) {
        iVar1 = *(int *)(param_1 + iVar2 * 4 + 0x604);
        if (iVar1 != 0) {
          (**(code **)(*(int *)(iVar1 + 0x84) + 8))(iVar1,1);
        }
      }
    }
    if (-1 < *(short *)(param_1 + 0x602)) {
      ReleaseImage__8MenuFontFv();
      DataGetCall__6HNMApiFi(*(u16 *)(param_1 + 0x602));
    }
    if (*(int *)(param_1 + 0x690) != 0) {
      iVar2 = *(int *)(param_1 + 0x690);
      if (iVar2 != 0) {
        (**(code **)(*(int *)(iVar2 + 0x10) + 8))(iVar2,1);
      }
    }
    if (*(int *)(param_1 + 0x68c) != 0) {
      iVar2 = *(int *)(param_1 + 0x68c);
      if (iVar2 != 0) {
        (**(code **)(*(int *)(iVar2 + 0x10) + 8))(iVar2,1);
      }
    }
    ourBtlSocket__9BtlSocket = 0;
    __dt__7CPolObjFv(param_1 + 8,0);
    if (param_1 != 0) {
      *(u8 **)(param_1 + 4) = __vt__6SSHApi;
    }
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* ---- 0x0032da40 size 0x20  BtlSocket::btlLoadCB(ibi)
 *      mangled: btlLoadCB__9BtlSocketFibi */
void btlLoadCB__9BtlSocketFibi(int param_1)

{
  *(u32 *)(param_1 + 0x24) = 2;
  return;
}

/* ---- 0x0032da60 size 0x144  BtlSocket::preLoad(v)
 *      mangled: preLoad__9BtlSocketFv */
u32 preLoad__9BtlSocketFv(int param_1)

{
  int iVar1;
  long lVar2;
  
  if (-1 < (long)((ulong)*(byte *)(param_1 + 0x20) << 0x3d)) {
    if (*(char *)(param_1 + 0x168) == '\0') {
      PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd,0x2000,1,0);
    }
    *(byte *)(param_1 + 0x20) = *(byte *)(param_1 + 0x20) & 0xfb | 4;
  }
  iVar1 = *(int *)(param_1 + 0x24);
  if (iVar1 != 2) {
    if (iVar1 == 1) {
      return 0;
    }
    if (iVar1 == 0) {
      lVar2 = Load__7OverlayFPCcPFibiPv_viPv(sys__6SSHSys + 0x68,0x3ff1e0,0x32d5d0,0,param_1);
      if (lVar2 == 0) {
        *(u32 *)(param_1 + 0x24) = 1;
      }
      else if (lVar2 == 3) {
        *(u32 *)(param_1 + 0x24) = 2;
      }
      return 0;
    }
  }
  return 1;
}

/* ---- 0x0032dbb0 size 0x14c  BtlSocket::Start(v)
 *      mangled: Start__9BtlSocketFv */
u32 Start__9BtlSocketFv(int param_1)

{
  long lVar1;
  int iVar2;
  
  iVar2 = param_1;
  if (param_1 != 0) {
    iVar2 = param_1 + 8;
  }
  lVar1 = Find__7CPollerCFPC7CPolObj(app__4CApp + 0x48,iVar2);
  if (lVar1 == 0) {
    iVar2 = param_1;
    if (param_1 != 0) {
      iVar2 = param_1 + 8;
    }
    Entry__7CPollerFP7CPolObjib(app__4CApp + 0x48,iVar2,0x80,0);
  }
  *(u32 *)(param_1 + 0x28) = 1;
  *(u32 *)(param_1 + 0x2c) = 0;
  *(u32 *)(param_1 + 0x30) = 0;
  *(u32 *)(param_1 + 0x34) = 0;
  *(u16 *)(param_1 + 0x16c) = 0;
  *(u8 *)(param_1 + 0x16e) = 0;
  *(u8 *)(param_1 + 0x526) = 0;
  *(u8 *)(param_1 + 0x16f) = 0;
  *(u32 *)(param_1 + 0x290) = 0;
  *(u32 *)(param_1 + 0x294) = 0;
  *(u32 *)(param_1 + 0x298) = 0;
  for (iVar2 = 0; iVar2 < 0xc; iVar2 = iVar2 + 1) {
    *(u32 *)(param_1 + iVar2 * 4 + 0x29c) = 0;
  }
  EnablePause__6CPauseFi(*(u32 *)(app__4CApp + 0x78),1);
  EnableReset__6CPauseFi(*(u32 *)(app__4CApp + 0x78),1);
  return 1;
}

/* ---- 0x0032dd00 size 0xd44  BtlSocket::Polling(v)
 *      mangled: Polling__9BtlSocketFv */
u32 Polling__9BtlSocketFv(int param_1)

{
  int iVar1;
  char cVar2;
  u16 uVar3;
  int iVar4;
  u32 uVar5;
  u32 uVar6;
  long lVar7;
  int p3;
  uint uVar8;
  
  if (-1 < (long)((ulong)*(byte *)(param_1 + 0x20) << 0x3d)) {
    if (*(char *)(param_1 + 0x168) == '\0') {
      PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd,0x2000,1,0);
    }
    *(byte *)(param_1 + 0x20) = *(byte *)(param_1 + 0x20) & 0xfb | 4;
  }
  cVar2 = *(char *)(param_1 + 0x600);
  if (cVar2 == '\x04') {
    if (*(char *)(param_1 + 0x601) != '\0') {
      for (iVar4 = 0; iVar4 < 0x20; iVar4 = iVar4 + 1) {
        if ((*(int *)(param_1 + iVar4 * 4 + 0x604) != 0) &&
           (iVar1 = *(int *)(param_1 + iVar4 * 4 + 0x604), iVar1 != 0)) {
          (**(code **)(*(int *)(iVar1 + 0x84) + 8))(iVar1,1);
        }
      }
      ReleaseImage__8MenuFontFv();
      DataGetCall__6HNMApiFi(*(u16 *)(param_1 + 0x602));
      *(u8 *)(param_1 + 0x600) = 0;
      *(u8 *)(param_1 + 0x601) = 0;
      *(u16 *)(param_1 + 0x602) = 0xffff;
      *(u32 *)(param_1 + 0x684) = 0;
      *(u32 *)(param_1 + 0x688) = 0;
    }
  }
  else if (cVar2 == '\x03') {
LAB_0032def0:
    uVar6 = *(u32 *)(*(int *)(&FRMem__6HNMApi + *(short *)(param_1 + 0x602) * 4) + 4);
    for (uVar8 = 2; (int)uVar8 < 0x1d; uVar8 = uVar8 + 1) {
      iVar4 = GetFileEntry(uVar6,uVar8);
      lVar7 = __nw__FUi(0x88);
      uVar5 = 0;
      if (lVar7 != 0) {
        uVar5 = __ct__6JRCTexFUs(lVar7,uVar8 & 0xffff);
      }
      *(u32 *)(param_1 + uVar8 * 4 + 0x604) = uVar5;
      if ((*(byte *)(iVar4 + 8) & 7) == 1) {
        RasterCreate__6JRCTexF6GS_PSMUiUi
                  (*(u32 *)(param_1 + uVar8 * 4 + 0x604),0x1b,*(u16 *)(iVar4 + 4),
                   *(u16 *)(iVar4 + 6));
      }
      else {
        RasterCreate__6JRCTexF6GS_PSMUiUi
                  (*(u32 *)(param_1 + uVar8 * 4 + 0x604),0x2c,*(u16 *)(iVar4 + 4),
                   *(u16 *)(iVar4 + 6));
      }
      ClutCreate__6JRCTexF6GS_PSMUiUi(*(u32 *)(param_1 + uVar8 * 4 + 0x604),0,0x10,0x10);
      Create__6JRCTexFPvUsUsUs(*(u32 *)(param_1 + uVar8 * 4 + 0x604),iVar4,0,0,0);
    }
    uVar5 = GetFileEntry(uVar6,1);
    *(u32 *)(param_1 + 0x684) = uVar5;
    uVar6 = GetFileEntry(uVar6,0);
    *(u32 *)(param_1 + 0x688) = uVar6;
    Convert__13MenuDataTableFPUci(*(MenuDataTable **)(param_1 + 0x688),(void *)0x0,p3);
    Create__11MenuTextureFPUc6GS_PSMUii(0x421af0,*(u32 *)(param_1 + 0x684),0x30,0,0);
    *(u8 *)(param_1 + 0x600) = 4;
  }
  else if (cVar2 == '\x02') {
LAB_0032de68:
    if (*(int *)(&FRMem__6HNMApi + *(short *)(param_1 + 0x602) * 4) != 0) {
      if (*(char *)(param_1 + 0x601) == '\0') {
        *(u8 *)(param_1 + 0x600) = 3;
        goto LAB_0032def0;
      }
      DataGetCall__6HNMApiFi(*(u16 *)(param_1 + 0x602));
      *(u8 *)(param_1 + 0x600) = 0;
      *(u8 *)(param_1 + 0x601) = 0;
      *(u16 *)(param_1 + 0x602) = 0xffff;
    }
  }
  else if (cVar2 == '\x01') {
    if (*(char *)(param_1 + 0x601) == '\0') {
      uVar3 = FileReadEntry__6HNMApiFPc(0x3ff1f0);
      *(u16 *)(param_1 + 0x602) = uVar3;
      if (-1 < *(short *)(param_1 + 0x602)) {
        *(u8 *)(param_1 + 0x600) = 2;
        goto LAB_0032de68;
      }
    }
    else {
      *(u8 *)(param_1 + 0x600) = 0;
      *(u8 *)(param_1 + 0x601) = 0;
      *(u16 *)(param_1 + 0x602) = 0xffff;
    }
  }
  switch(*(u32 *)(param_1 + 0x28)) {
  case 1:
    if ((long)((ulong)*(byte *)(sys__6HNMSnd + 0x3c1) << 0x3d) < 0) {
      FilterOn__9BtlSocketFbb(param_1,1,1);
      if (*(char *)(param_1 + 0x168) != '\0') {
        SetMute__8CVibeManFi(sys__8CVibeMan,1);
      }
      if ((*(int *)(param_1 + 0x698) == 3) || (*(int *)(param_1 + 0x698) == 4)) {
        if ((long)((ulong)*(byte *)(ourBtlSaveDat__10BtlSaveSec + 0xd48) << 0x3e) < 0) {
          *(u32 *)(param_1 + 0x698) = 4;
        }
        else {
          *(u32 *)(param_1 + 0x698) = 3;
        }
      }
      *(byte *)(ourBtlSaveDat__10BtlSaveSec + 3) =
           *(byte *)(ourBtlSaveDat__10BtlSaveSec + 3) & 0xfd |
           ((*(byte *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x276) & 3) != 0) << 1;
      *(byte *)(sys__6HNMSnd + 0x3c0) = *(byte *)(sys__6HNMSnd + 0x3c0) & 0xfd | 2;
      lVar7 = __nw__FUi(0x4660);
      iVar4 = 0;
      if (lVar7 != 0) {
        iVar4 = cbSvpCallback__FiP9BufMemoryiPcPv(lVar7);
      }
      Sys__7CBattle = iVar4;
      *(code **)(iVar4 + 0x98) = BtlCallBack__FiiPvPv;
      *(int *)(iVar4 + 0x94) = param_1;
      *(byte *)(Sys__7CBattle + 0x24) =
           *(byte *)(Sys__7CBattle + 0x24) & 0xdf | (*(char *)(param_1 + 0x168) == '\x01') << 5;
      SetBtlBG__7CBattleFi(Sys__7CBattle,*(u32 *)(param_1 + 0x15c));
      if (*(char *)(param_1 + 0x49) != '\0') {
        PCSet__7CBattleFiPc(Sys__7CBattle,*(u8 *)(param_1 + 0x49),param_1 + 0x4a);
      }
      if (*(int *)(param_1 + 0x58) != 0) {
        MonsterSet__7CBattleFP9MONSETTbl
                  (Sys__7CBattle,param_1 + *(int *)(param_1 + 0x34) * 0x10 + 0x5c);
      }
      Start__7CBattleFv(Sys__7CBattle);
      *(u32 *)(param_1 + 0x28) = 2;
    }
    break;
  case 4:
    cVar2 = ReleaseCheck__6HNMSndFv(sys__6HNMSnd);
    if (cVar2 != '\0') {
      if (*(char *)(param_1 + 0x168) != '\0') {
        SetMute__8CVibeManFi(sys__8CVibeMan,0xfffffffffffffffe);
      }
      FilterOff__9BtlSocketFbb(param_1,1,1);
      *(int *)(param_1 + 0x34) = *(int *)(param_1 + 0x34) + 1;
      lVar7 = 0;
      while ((lVar7 < *(char *)(param_1 + 0x49) &&
             (*(char *)(param_1 + (int)lVar7 + 0x4a) != '\x06'))) {
        lVar7 = (long)((int)lVar7 + 1);
      }
      if (((long)((ulong)*(byte *)(ourBtlSaveDat__10BtlSaveSec + 0xd48) << 0x3d) < 0) &&
         (lVar7 < *(char *)(param_1 + 0x49))) {
        *(int *)(ourBtlSaveDat__10BtlSaveSec + 0xe38) =
             *(int *)(ourBtlSaveDat__10BtlSaveSec + 0xe38) + 1;
      }
      if ((*(int *)(param_1 + 0x34) < *(int *)(param_1 + 0x58)) &&
         ((*(byte *)(param_1 + 0x16c) & 3) == 0)) {
        *(u32 *)(param_1 + 0x28) = 1;
      }
      else if (((*(byte *)(param_1 + 0x16c) & 3) == 0) && (*(char *)(param_1 + 0x168) == '\0')) {
        *(u32 *)(param_1 + 0x28) = 6;
        DisablePause__6CPauseFv(*(u32 *)(app__4CApp + 0x78));
        *(u32 *)(camera__4CApp + 0x180) = 0;
        lVar7 = __nw__FUi(0xddc);
        if (lVar7 != 0) {
          __ct__9BtlResultFv(lVar7);
        }
        if ((*(int *)(param_1 + 0x164) != 0) && ((*(byte *)(param_1 + 0x16c) & 3) != 1)) {
          (**(code **)(param_1 + 0x164))(1,0,*(u32 *)(param_1 + 0x160));
        }
      }
      else {
        *(u32 *)(param_1 + 0x28) = 5;
        DisablePause__6CPauseFv(*(u32 *)(app__4CApp + 0x78));
        *(u32 *)(camera__4CApp + 0x180) = 0;
        if ((*(int *)(param_1 + 0x164) != 0) && ((*(byte *)(param_1 + 0x16c) & 3) != 1)) {
          (**(code **)(param_1 + 0x164))(1,0,*(u32 *)(param_1 + 0x160));
        }
      }
    }
    break;
  case 5:
    if (ourBtlBonus__8BtlBonus == 0) {
      *(u32 *)(param_1 + 0x28) = 7;
      *(byte *)(sys__6HNMSnd + 0x3c0) = *(byte *)(sys__6HNMSnd + 0x3c0) & 0xf7 | 8;
    }
    break;
  case 6:
    if (ourBtlResult__9BtlResult == 0) {
      *(u32 *)(param_1 + 0x28) = 7;
      *(byte *)(sys__6HNMSnd + 0x3c0) = *(byte *)(sys__6HNMSnd + 0x3c0) & 0xf7 | 8;
    }
    break;
  case 7:
    if (*(char *)(sys__6HNMSnd + 0x3f0) != '\0') {
      if ((*(char *)(sys__6HNMSnd + 0x3f0) != '\t') && (*(char *)(sys__6HNMSnd + 0x3f0) != '\n')) {
        *(byte *)(sys__6HNMSnd + 0x3c0) = *(byte *)(sys__6HNMSnd + 0x3c0) & 0xf7 | 8;
      }
      break;
    }
    if (*(char *)(sys__6HNMSnd + 0x3fc) != '\0') {
      if ((*(char *)(sys__6HNMSnd + 0x3fc) != '\x06') && (*(char *)(sys__6HNMSnd + 0x3fc) != '\a'))
      {
        SetBtlResultBGMFadeOut__6HNMSndFi(sys__6HNMSnd,0x14d);
      }
      break;
    }
    Destruct__8BtlFaderFv();
    *(u32 *)(param_1 + 0x28) = 8;
  case 8:
    cVar2 = ReleaseCheck__6HNMSndFv(sys__6HNMSnd);
    if (cVar2 != '\0') {
      *(u32 *)(param_1 + 0x28) = 0;
      if (*(int *)(param_1 + 0x164) != 0) {
        (**(code **)(param_1 + 0x164))(0,0,*(u32 *)(param_1 + 0x160));
      }
      EnablePause__6CPauseFi(*(u32 *)(app__4CApp + 0x78),1);
      return 1;
    }
  }
  uVar6 = GetActive__4CPadFi(0);
  if (Sys__7CBattle != 0) {
    uVar6 = Pad__7CBattle;
  }
  if (*(char *)(param_1 + 0x168) == '\0') {
    ChkResetPause__6SSHSysFP4CPadbb(sys__6SSHSys,uVar6,1,1);
  }
  else {
    ChkResetPause__6SSHSysFP4CPadbb(sys__6SSHSys,uVar6,0,1);
  }
  return 0;
}

/* ---- 0x0032ea50 size 0x68  BtlSocket::closeInquiry(v)
 *      mangled: closeInquiry__9BtlSocketFv */
bool closeInquiry__9BtlSocketFv(int param_1)

{
  bool bVar1;
  
  bVar1 = *(int *)(param_1 + 0x24) != 2;
  if (!bVar1) {
    Unload__7OverlayFPFibiPv_v(sys__6SSHSys + 0x68,0);
    *(u32 *)(param_1 + 0x24) = 0;
    *(u32 *)(param_1 + 0x28) = 0;
  }
  return bVar1;
}

/* ---- 0x0032eac0 size 0x51c  BtlSocket::BtlCBFunc(iiPv)
 *      mangled: BtlCBFunc__9BtlSocketFiiPv */
u32 BtlCBFunc__9BtlSocketFiiPv(int param_1,int param_2,u64 param_3,byte *param_4)

{
  int iVar1;
  int iVar2;
  
  if (param_2 == 0) {
    *(u32 *)(param_1 + 0x28) = 4;
  }
  else if (param_2 == 1) {
    *(byte *)(param_1 + 0x16c) =
         *(byte *)(param_1 + 0x16c) & 0x83 |
         (byte)(((uint)(((ulong)*(byte *)(param_1 + 0x16c) << 0x39) >> 0x3b) + 1 & 0x1f) << 2);
    *(byte *)(param_1 + 0x16c) = *(byte *)(param_1 + 0x16c) & 0xfc | *param_4 & 3;
    if ((*(byte *)(param_1 + 0x16c) & 3) == 0) {
      *(int *)(param_1 + 0x290) = *(int *)(param_1 + 0x290) + *(int *)(param_4 + 0x124);
      *(int *)(param_1 + 0x294) = *(int *)(param_1 + 0x294) + *(int *)(param_4 + 0x128);
      *(int *)(param_1 + 0x298) = *(int *)(param_1 + 0x298) + *(int *)(param_4 + 300);
      for (iVar2 = 0; iVar2 < (int)(uint)param_4[2]; iVar2 = iVar2 + 1) {
        iVar1 = 0;
        while ((iVar1 < (int)(uint)*(byte *)(param_1 + 0x16e) &&
               (*(short *)(param_1 + iVar1 * 2 + 0x170) != *(short *)(param_4 + iVar2 * 2 + 4)))) {
          iVar1 = iVar1 + 1;
        }
        if (iVar1 < (int)(uint)*(byte *)(param_1 + 0x16e)) {
          *(byte *)(param_1 + iVar1 + 0x230) =
               *(char *)(param_1 + iVar1 + 0x230) + param_4[iVar2 + 0xc4];
        }
        else {
          *(u16 *)(param_1 + (uint)*(byte *)(param_1 + 0x16e) * 2 + 0x170) =
               *(u16 *)(param_4 + iVar2 * 2 + 4);
          *(byte *)(param_1 + (uint)*(byte *)(param_1 + 0x16e) + 0x230) = param_4[iVar2 + 0xc4];
          *(char *)(param_1 + 0x16e) = *(char *)(param_1 + 0x16e) + '\x01';
        }
      }
      for (iVar2 = 0; iVar2 < (int)(uint)param_4[0x3ba]; iVar2 = iVar2 + 1) {
        for (iVar1 = 0;
            (iVar1 < (int)(uint)*(byte *)(param_1 + 0x526) &&
            ((*(byte *)(param_1 + iVar1 + 0x540) != param_4[iVar2 + 0x3d4] ||
             (*(byte *)(param_1 + iVar1 + 0x5a0) != param_4[iVar2 + 0x434])))); iVar1 = iVar1 + 1) {
        }
        if ((int)(uint)*(byte *)(param_1 + 0x526) <= iVar1) {
          *(byte *)(param_1 + (uint)*(byte *)(param_1 + 0x526) + 0x540) = param_4[iVar2 + 0x3d4];
          *(byte *)(param_1 + (uint)*(byte *)(param_1 + 0x526) + 0x5a0) = param_4[iVar2 + 0x434];
          *(char *)(param_1 + 0x526) = *(char *)(param_1 + 0x526) + '\x01';
        }
      }
      for (iVar2 = 0; iVar2 < (int)(uint)param_4[3]; iVar2 = iVar2 + 1) {
        iVar1 = 0;
        while ((iVar1 < (int)(uint)*(byte *)(param_1 + 0x16f) &&
               (*(short *)(param_1 + iVar1 * 2 + 0x2cc) != *(short *)(param_4 + iVar2 * 2 + 0x160)))
              ) {
          iVar1 = iVar1 + 1;
        }
        if (iVar1 < (int)(uint)*(byte *)(param_1 + 0x16f)) {
          *(byte *)(param_1 + iVar1 + 0x44c) =
               *(char *)(param_1 + iVar1 + 0x44c) + param_4[iVar2 + 0x2e0];
        }
        else {
          *(u16 *)(param_1 + (uint)*(byte *)(param_1 + 0x16f) * 2 + 0x2cc) =
               *(u16 *)(param_4 + iVar2 * 2 + 0x160);
          *(byte *)(param_1 + (uint)*(byte *)(param_1 + 0x16f) + 0x44c) = param_4[iVar2 + 0x2e0];
          *(char *)(param_1 + 0x16f) = *(char *)(param_1 + 0x16f) + '\x01';
        }
      }
      for (iVar2 = 0; iVar2 < 0xc; iVar2 = iVar2 + 1) {
        iVar1 = param_1 + iVar2 * 4;
        *(int *)(iVar1 + 0x29c) = *(int *)(iVar1 + 0x29c) + *(int *)(param_4 + iVar2 * 4 + 0x130);
      }
    }
    else {
      *(u32 *)(param_1 + 0x290) = 0;
      *(u32 *)(param_1 + 0x294) = 0;
      *(u32 *)(param_1 + 0x298) = 0;
      *(u8 *)(param_1 + 0x16e) = 0;
      *(u8 *)(param_1 + 0x526) = 0;
      *(u8 *)(param_1 + 0x16f) = 0;
      for (iVar2 = 0; iVar2 < 0xc; iVar2 = iVar2 + 1) {
        *(u32 *)(param_1 + iVar2 * 4 + 0x29c) = 0;
      }
    }
    *(u16 *)(param_1 + 0x50c) = 0;
  }
  return 1;
}

/* ---- 0x0032efe0 size 0x100  BtlSocket::SetPC(iPc)
 *      mangled: SetPC__9BtlSocketFiPc */
void SetPC__9BtlSocketFiPc(int param_1,int param_2,u32 param_3)

{
  long lVar1;
  int iVar2;
  
  if (*(char *)(param_1 + 0x49) < *(char *)(param_1 + 0x47)) {
    iVar2 = 0;
    for (lVar1 = (long)*(char *)(param_1 + 0x49); lVar1 < *(char *)(param_1 + 0x47);
        lVar1 = (long)((int)lVar1 + 1)) {
      *(u8 *)(param_1 + iVar2 + 0x4a) = *(u8 *)(param_1 + (int)lVar1 + 0x4a);
      iVar2 = iVar2 + 1;
    }
  }
  *(char *)(param_1 + 0x47) = *(char *)(param_1 + 0x47) - *(char *)(param_1 + 0x49);
  *(u8 *)(param_1 + 0x49) = 0;
  if (param_2 != 0) {
    AddPC__9BtlSocketFiPc(param_1,param_2,param_3);
  }
  return;
}

/* ---- 0x0032f0e0 size 0x17c  BtlSocket::AddPC(iPc)
 *      mangled: AddPC__9BtlSocketFiPc */
void AddPC__9BtlSocketFiPc(int param_1,int param_2,int param_3)

{
  int iVar1;
  long lVar2;
  int iVar3;
  
  for (iVar3 = 0; iVar3 < param_2; iVar3 = iVar3 + 1) {
    if (*(char *)(param_1 + 0x49) < '\x04') {
      if (*(char *)(param_1 + 0x49) < *(char *)(param_1 + 0x47)) {
        lVar2 = (long)(*(char *)(param_1 + 0x47) + -1);
        if (6 < lVar2) {
          lVar2 = 6;
        }
        while (*(char *)(param_1 + 0x49) <= lVar2) {
          iVar1 = (int)lVar2;
          *(u8 *)(param_1 + iVar1 + 0x4b) = *(u8 *)(param_1 + iVar1 + 0x4a);
          lVar2 = (long)(iVar1 + -1);
        }
      }
      *(u8 *)(param_1 + *(char *)(param_1 + 0x49) + 0x4a) = *(u8 *)(param_3 + iVar3)
      ;
      *(char *)(param_1 + 0x49) = *(char *)(param_1 + 0x49) + '\x01';
      *(char *)(param_1 + 0x47) = *(char *)(param_1 + 0x47) + '\x01';
      if ('\b' < *(char *)(param_1 + 0x47)) {
        *(u8 *)(param_1 + 0x47) = 8;
      }
    }
  }
  return;
}

/* ---- 0x0032f260 size 0x50  BtlSocket::SetMonsterSet(iP9MONSETTbl)
 *      mangled: SetMonsterSet__9BtlSocketFiP9MONSETTbl */
void SetMonsterSet__9BtlSocketFiP9MONSETTbl(int param_1,int param_2,u32 param_3)

{
  *(u32 *)(param_1 + 0x58) = 0;
  if (param_2 != 0) {
    AddMonsterSet__9BtlSocketFiP9MONSETTbl(param_1,param_2,param_3);
  }
  return;
}

/* ---- 0x0032f2b0 size 0x210  BtlSocket::AddMonsterSet(iP9MONSETTbl)
 *      mangled: AddMonsterSet__9BtlSocketFiP9MONSETTbl */
void AddMonsterSet__9BtlSocketFiP9MONSETTbl(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  
  for (iVar2 = 0; iVar2 < param_2; iVar2 = iVar2 + 1) {
    if (*(int *)(param_1 + 0x58) < 0x10) {
      *(u16 *)(param_1 + *(int *)(param_1 + 0x58) * 0x10 + 0x5c) =
           *(u16 *)(param_3 + iVar2 * 0x10);
      *(u16 *)(param_1 + *(int *)(param_1 + 0x58) * 0x10 + 0x5e) =
           *(u16 *)(param_3 + iVar2 * 0x10 + 2);
      *(u16 *)(param_1 + *(int *)(param_1 + 0x58) * 0x10 + 0x60) =
           *(u16 *)(param_3 + iVar2 * 0x10 + 4);
      *(u16 *)(param_1 + *(int *)(param_1 + 0x58) * 0x10 + 0x62) =
           *(u16 *)(param_3 + iVar2 * 0x10 + 6);
      *(u16 *)(param_1 + *(int *)(param_1 + 0x58) * 0x10 + 100) =
           *(u16 *)(param_3 + iVar2 * 0x10 + 8);
      *(u16 *)(param_1 + *(int *)(param_1 + 0x58) * 0x10 + 0x66) =
           *(u16 *)(param_3 + iVar2 * 0x10 + 10);
      *(u16 *)(param_1 + *(int *)(param_1 + 0x58) * 0x10 + 0x68) =
           *(u16 *)(param_3 + iVar2 * 0x10 + 0xc);
      iVar1 = param_1 + *(int *)(param_1 + 0x58) * 0x10;
      *(byte *)(iVar1 + 0x6a) =
           *(byte *)(iVar1 + 0x6a) & 0xfc | *(byte *)(param_3 + iVar2 * 0x10 + 0xe) & 3;
      iVar1 = param_1 + *(int *)(param_1 + 0x58) * 0x10;
      *(ushort *)(iVar1 + 0x6a) =
           *(ushort *)(iVar1 + 0x6a) & 3 |
           (ushort)((uint)(((ulong)*(ushort *)(param_3 + iVar2 * 0x10 + 0xe) << 0x30) >> 0x32) << 2)
      ;
      *(int *)(param_1 + 0x58) = *(int *)(param_1 + 0x58) + 1;
    }
  }
  return;
}

/* ---- 0x0032f4c0 size 0x3c  BtlSocket::SetBtlBGMNumber(i)
 *      mangled: SetBtlBGMNumber__9BtlSocketFi */
void SetBtlBGMNumber__9BtlSocketFi(int param_1,u32 param_2)

{
  *(u32 *)(param_1 + 0x694) = param_2;
  SetBtlBGMNumber__6HNMSndFi(sys__6HNMSnd,param_2);
  return;
}

/* ---- 0x0032f500 size 0x60  BtlSocket::BattleEnd(v)
 *      mangled: BattleEnd__9BtlSocketFv */
bool BattleEnd__9BtlSocketFv(int param_1)

{
  bool bVar1;
  
  bVar1 = *(int *)(param_1 + 0x28) == 2;
  if (bVar1) {
    End__7CBattleFv(Sys__7CBattle);
    *(u32 *)(param_1 + 0x28) = 3;
  }
  return bVar1;
}

/* ---- 0x0032f560 size 0xd8  BtlSocket::FilterOn(bb)
 *      mangled: FilterOn__9BtlSocketFbb */
void FilterOn__9BtlSocketFbb(int param_1,char param_2,char param_3)

{
  if (((*(byte *)(param_1 + 0x20) & 1) == 0) && (param_2 != '\0')) {
    LayerSetUp__12SmoothFilterFi(*(u32 *)(param_1 + 0x68c),0xb);
    *(byte *)(param_1 + 0x20) = *(byte *)(param_1 + 0x20) & 0xfe | 1;
  }
  if ((-1 < (long)((ulong)*(byte *)(param_1 + 0x20) << 0x3e)) && (param_3 != '\0')) {
    LayerSetUp__10BlurFilterFi(*(u32 *)(param_1 + 0x690),0xb);
    *(byte *)(param_1 + 0x20) = *(byte *)(param_1 + 0x20) & 0xfd | 2;
  }
  return;
}

/* ---- 0x0032f640 size 0xc8  BtlSocket::FilterOff(bb)
 *      mangled: FilterOff__9BtlSocketFbb */
void FilterOff__9BtlSocketFbb(int param_1,char param_2,char param_3)

{
  if (((*(byte *)(param_1 + 0x20) & 1) != 0) && (param_2 != '\0')) {
    LayerRelease__12SmoothFilterFv(*(u32 *)(param_1 + 0x68c));
    *(byte *)(param_1 + 0x20) = *(byte *)(param_1 + 0x20) & 0xfe;
  }
  if (((long)((ulong)*(byte *)(param_1 + 0x20) << 0x3e) < 0) && (param_3 != '\0')) {
    LayerRelease__10BlurFilterFv(*(u32 *)(param_1 + 0x690));
    *(byte *)(param_1 + 0x20) = *(byte *)(param_1 + 0x20) & 0xfd;
  }
  return;
}

/* ---- 0x0032f710 size 0x8  BtlSocket::@8@Polling(v)
 *      mangled: @8@Polling__9BtlSocketFv */
u32 _8_Polling__9BtlSocketFv(int param_1)

{
  int iVar1;
  char cVar2;
  u16 uVar3;
  int iVar4;
  u32 uVar5;
  u32 uVar6;
  long lVar7;
  int iVar8;
  int p3;
  uint uVar9;
  
  iVar8 = param_1 + -8;
  if (-1 < (long)((ulong)*(byte *)(param_1 + 0x18) << 0x3d)) {
    if (*(char *)(param_1 + 0x160) == '\0') {
      PlaySE__6HNMSndFUibP7FVector(sys__6HNMSnd,0x2000,1,0);
    }
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfb | 4;
  }
  cVar2 = *(char *)(param_1 + 0x5f8);
  if (cVar2 == '\x04') {
    if (*(char *)(param_1 + 0x5f9) != '\0') {
      for (iVar4 = 0; iVar4 < 0x20; iVar4 = iVar4 + 1) {
        if ((*(int *)(iVar8 + iVar4 * 4 + 0x604) != 0) &&
           (iVar1 = *(int *)(iVar8 + iVar4 * 4 + 0x604), iVar1 != 0)) {
          (**(code **)(*(int *)(iVar1 + 0x84) + 8))(iVar1,1);
        }
      }
      ReleaseImage__8MenuFontFv();
      DataGetCall__6HNMApiFi(*(u16 *)(param_1 + 0x5fa));
      *(u8 *)(param_1 + 0x5f8) = 0;
      *(u8 *)(param_1 + 0x5f9) = 0;
      *(u16 *)(param_1 + 0x5fa) = 0xffff;
      *(u32 *)(param_1 + 0x67c) = 0;
      *(u32 *)(param_1 + 0x680) = 0;
    }
  }
  else if (cVar2 == '\x03') {
LAB_0032def0:
    uVar6 = *(u32 *)(*(int *)(&FRMem__6HNMApi + *(short *)(param_1 + 0x5fa) * 4) + 4);
    for (uVar9 = 2; (int)uVar9 < 0x1d; uVar9 = uVar9 + 1) {
      iVar4 = GetFileEntry(uVar6,uVar9);
      lVar7 = __nw__FUi(0x88);
      uVar5 = 0;
      if (lVar7 != 0) {
        uVar5 = __ct__6JRCTexFUs(lVar7,uVar9 & 0xffff);
      }
      *(u32 *)(iVar8 + uVar9 * 4 + 0x604) = uVar5;
      if ((*(byte *)(iVar4 + 8) & 7) == 1) {
        RasterCreate__6JRCTexF6GS_PSMUiUi
                  (*(u32 *)(iVar8 + uVar9 * 4 + 0x604),0x1b,*(u16 *)(iVar4 + 4),
                   *(u16 *)(iVar4 + 6));
      }
      else {
        RasterCreate__6JRCTexF6GS_PSMUiUi
                  (*(u32 *)(iVar8 + uVar9 * 4 + 0x604),0x2c,*(u16 *)(iVar4 + 4),
                   *(u16 *)(iVar4 + 6));
      }
      ClutCreate__6JRCTexF6GS_PSMUiUi(*(u32 *)(iVar8 + uVar9 * 4 + 0x604),0,0x10,0x10);
      Create__6JRCTexFPvUsUsUs(*(u32 *)(iVar8 + uVar9 * 4 + 0x604),iVar4,0,0,0);
    }
    uVar5 = GetFileEntry(uVar6,1);
    *(u32 *)(param_1 + 0x67c) = uVar5;
    uVar6 = GetFileEntry(uVar6,0);
    *(u32 *)(param_1 + 0x680) = uVar6;
    Convert__13MenuDataTableFPUci(*(MenuDataTable **)(param_1 + 0x680),(void *)0x0,p3);
    Create__11MenuTextureFPUc6GS_PSMUii(0x421af0,*(u32 *)(param_1 + 0x67c),0x30,0,0);
    *(u8 *)(param_1 + 0x5f8) = 4;
  }
  else if (cVar2 == '\x02') {
LAB_0032de68:
    if (*(int *)(&FRMem__6HNMApi + *(short *)(param_1 + 0x5fa) * 4) != 0) {
      if (*(char *)(param_1 + 0x5f9) == '\0') {
        *(u8 *)(param_1 + 0x5f8) = 3;
        goto LAB_0032def0;
      }
      DataGetCall__6HNMApiFi(*(u16 *)(param_1 + 0x5fa));
      *(u8 *)(param_1 + 0x5f8) = 0;
      *(u8 *)(param_1 + 0x5f9) = 0;
      *(u16 *)(param_1 + 0x5fa) = 0xffff;
    }
  }
  else if (cVar2 == '\x01') {
    if (*(char *)(param_1 + 0x5f9) == '\0') {
      uVar3 = FileReadEntry__6HNMApiFPc(0x3ff1f0);
      *(u16 *)(param_1 + 0x5fa) = uVar3;
      if (-1 < *(short *)(param_1 + 0x5fa)) {
        *(u8 *)(param_1 + 0x5f8) = 2;
        goto LAB_0032de68;
      }
    }
    else {
      *(u8 *)(param_1 + 0x5f8) = 0;
      *(u8 *)(param_1 + 0x5f9) = 0;
      *(u16 *)(param_1 + 0x5fa) = 0xffff;
    }
  }
  switch(*(u32 *)(param_1 + 0x20)) {
  case 1:
    if ((long)((ulong)*(byte *)(sys__6HNMSnd + 0x3c1) << 0x3d) < 0) {
      FilterOn__9BtlSocketFbb(iVar8,1,1);
      if (*(char *)(param_1 + 0x160) != '\0') {
        SetMute__8CVibeManFi(sys__8CVibeMan,1);
      }
      if ((*(int *)(param_1 + 0x690) == 3) || (*(int *)(param_1 + 0x690) == 4)) {
        if ((long)((ulong)*(byte *)(ourBtlSaveDat__10BtlSaveSec + 0xd48) << 0x3e) < 0) {
          *(u32 *)(param_1 + 0x690) = 4;
        }
        else {
          *(u32 *)(param_1 + 0x690) = 3;
        }
      }
      *(byte *)(ourBtlSaveDat__10BtlSaveSec + 3) =
           *(byte *)(ourBtlSaveDat__10BtlSaveSec + 3) & 0xfd |
           ((*(byte *)(*(int *)(sm_pSubstance__15SaveMenuSection + 0xc) + 0x276) & 3) != 0) << 1;
      *(byte *)(sys__6HNMSnd + 0x3c0) = *(byte *)(sys__6HNMSnd + 0x3c0) & 0xfd | 2;
      lVar7 = __nw__FUi(0x4660);
      iVar4 = 0;
      if (lVar7 != 0) {
        iVar4 = cbSvpCallback__FiP9BufMemoryiPcPv(lVar7);
      }
      Sys__7CBattle = iVar4;
      *(code **)(iVar4 + 0x98) = BtlCallBack__FiiPvPv;
      *(int *)(iVar4 + 0x94) = iVar8;
      *(byte *)(Sys__7CBattle + 0x24) =
           *(byte *)(Sys__7CBattle + 0x24) & 0xdf | (*(char *)(param_1 + 0x160) == '\x01') << 5;
      SetBtlBG__7CBattleFi(Sys__7CBattle,*(u32 *)(param_1 + 0x154));
      if (*(char *)(param_1 + 0x41) != '\0') {
        PCSet__7CBattleFiPc(Sys__7CBattle,*(u8 *)(param_1 + 0x41),param_1 + 0x42);
      }
      if (*(int *)(param_1 + 0x50) != 0) {
        MonsterSet__7CBattleFP9MONSETTbl
                  (Sys__7CBattle,iVar8 + *(int *)(param_1 + 0x2c) * 0x10 + 0x5c);
      }
      Start__7CBattleFv(Sys__7CBattle);
      *(u32 *)(param_1 + 0x20) = 2;
    }
    break;
  case 4:
    cVar2 = ReleaseCheck__6HNMSndFv(sys__6HNMSnd);
    if (cVar2 != '\0') {
      if (*(char *)(param_1 + 0x160) != '\0') {
        SetMute__8CVibeManFi(sys__8CVibeMan,0xfffffffffffffffe);
      }
      FilterOff__9BtlSocketFbb(iVar8,1,1);
      *(int *)(param_1 + 0x2c) = *(int *)(param_1 + 0x2c) + 1;
      lVar7 = 0;
      while ((lVar7 < *(char *)(param_1 + 0x41) && (*(char *)(iVar8 + (int)lVar7 + 0x4a) != '\x06'))
            ) {
        lVar7 = (long)((int)lVar7 + 1);
      }
      if (((long)((ulong)*(byte *)(ourBtlSaveDat__10BtlSaveSec + 0xd48) << 0x3d) < 0) &&
         (lVar7 < *(char *)(param_1 + 0x41))) {
        *(int *)(ourBtlSaveDat__10BtlSaveSec + 0xe38) =
             *(int *)(ourBtlSaveDat__10BtlSaveSec + 0xe38) + 1;
      }
      if ((*(int *)(param_1 + 0x2c) < *(int *)(param_1 + 0x50)) &&
         ((*(byte *)(param_1 + 0x164) & 3) == 0)) {
        *(u32 *)(param_1 + 0x20) = 1;
      }
      else if (((*(byte *)(param_1 + 0x164) & 3) == 0) && (*(char *)(param_1 + 0x160) == '\0')) {
        *(u32 *)(param_1 + 0x20) = 6;
        DisablePause__6CPauseFv(*(u32 *)(app__4CApp + 0x78));
        *(u32 *)(camera__4CApp + 0x180) = 0;
        lVar7 = __nw__FUi(0xddc);
        if (lVar7 != 0) {
          __ct__9BtlResultFv(lVar7);
        }
        if ((*(int *)(param_1 + 0x15c) != 0) && ((*(byte *)(param_1 + 0x164) & 3) != 1)) {
          (**(code **)(param_1 + 0x15c))(1,0,*(u32 *)(param_1 + 0x158));
        }
      }
      else {
        *(u32 *)(param_1 + 0x20) = 5;
        DisablePause__6CPauseFv(*(u32 *)(app__4CApp + 0x78));
        *(u32 *)(camera__4CApp + 0x180) = 0;
        if ((*(int *)(param_1 + 0x15c) != 0) && ((*(byte *)(param_1 + 0x164) & 3) != 1)) {
          (**(code **)(param_1 + 0x15c))(1,0,*(u32 *)(param_1 + 0x158));
        }
      }
    }
    break;
  case 5:
    if (ourBtlBonus__8BtlBonus == 0) {
      *(u32 *)(param_1 + 0x20) = 7;
      *(byte *)(sys__6HNMSnd + 0x3c0) = *(byte *)(sys__6HNMSnd + 0x3c0) & 0xf7 | 8;
    }
    break;
  case 6:
    if (ourBtlResult__9BtlResult == 0) {
      *(u32 *)(param_1 + 0x20) = 7;
      *(byte *)(sys__6HNMSnd + 0x3c0) = *(byte *)(sys__6HNMSnd + 0x3c0) & 0xf7 | 8;
    }
    break;
  case 7:
    if (*(char *)(sys__6HNMSnd + 0x3f0) != '\0') {
      if ((*(char *)(sys__6HNMSnd + 0x3f0) != '\t') && (*(char *)(sys__6HNMSnd + 0x3f0) != '\n')) {
        *(byte *)(sys__6HNMSnd + 0x3c0) = *(byte *)(sys__6HNMSnd + 0x3c0) & 0xf7 | 8;
      }
      break;
    }
    if (*(char *)(sys__6HNMSnd + 0x3fc) != '\0') {
      if ((*(char *)(sys__6HNMSnd + 0x3fc) != '\x06') && (*(char *)(sys__6HNMSnd + 0x3fc) != '\a'))
      {
        SetBtlResultBGMFadeOut__6HNMSndFi(sys__6HNMSnd,0x14d);
      }
      break;
    }
    Destruct__8BtlFaderFv();
    *(u32 *)(param_1 + 0x20) = 8;
  case 8:
    cVar2 = ReleaseCheck__6HNMSndFv(sys__6HNMSnd);
    if (cVar2 != '\0') {
      *(u32 *)(param_1 + 0x20) = 0;
      if (*(int *)(param_1 + 0x15c) != 0) {
        (**(code **)(param_1 + 0x15c))(0,0,*(u32 *)(param_1 + 0x158));
      }
      EnablePause__6CPauseFi(*(u32 *)(app__4CApp + 0x78),1);
      return 1;
    }
  }
  uVar6 = GetActive__4CPadFi(0);
  if (Sys__7CBattle != 0) {
    uVar6 = Pad__7CBattle;
  }
  if (*(char *)(param_1 + 0x160) == '\0') {
    ChkResetPause__6SSHSysFP4CPadbb(sys__6SSHSys,uVar6,1,1);
  }
  else {
    ChkResetPause__6SSHSysFP4CPadbb(sys__6SSHSys,uVar6,0,1);
  }
  return 0;
}

/* ---- 0x0032f720 size 0x8  BtlSocket::@8@__dt(v)
 *      mangled: @8@__dt__9BtlSocketFv */
int _8___dt__9BtlSocketFv(int param_1,short param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = param_1 + -8;
  if (iVar2 != 0) {
    *(u8 **)(param_1 + -4) = __vt__9BtlSocket;
    *(u32 *)(param_1 + 0x14) = 0x406db0;
    for (iVar3 = 0; iVar3 < 0x20; iVar3 = iVar3 + 1) {
      if (*(int *)(iVar2 + iVar3 * 4 + 0x604) != 0) {
        iVar1 = *(int *)(iVar2 + iVar3 * 4 + 0x604);
        if (iVar1 != 0) {
          (**(code **)(*(int *)(iVar1 + 0x84) + 8))(iVar1,1);
        }
      }
    }
    if (-1 < *(short *)(param_1 + 0x5fa)) {
      ReleaseImage__8MenuFontFv();
      DataGetCall__6HNMApiFi(*(u16 *)(param_1 + 0x5fa));
    }
    if (*(int *)(param_1 + 0x688) != 0) {
      iVar3 = *(int *)(param_1 + 0x688);
      if (iVar3 != 0) {
        (**(code **)(*(int *)(iVar3 + 0x10) + 8))(iVar3,1);
      }
    }
    if (*(int *)(param_1 + 0x684) != 0) {
      iVar3 = *(int *)(param_1 + 0x684);
      if (iVar3 != 0) {
        (**(code **)(*(int *)(iVar3 + 0x10) + 8))(iVar3,1);
      }
    }
    ourBtlSocket__9BtlSocket = 0;
    __dt__7CPolObjFv(param_1,0);
    if (iVar2 != 0) {
      *(u8 **)(param_1 + -4) = __vt__6SSHApi;
    }
    if (0 < param_2) {
      __dl__FPv(iVar2);
    }
  }
  return iVar2;
}

