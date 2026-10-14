/*
 * CMusic.c -- Ghidra decompiler output (SLPM_602.19, JP Furokuban), tidied by tools/E_gen_decomp.py
 * 16 functions. Types: u8/u16/u32/u64 = undefined1/2/4/8. Addresses in comments are JP main-exe addresses.
 */

/* ---- 0x003c5620 size 0x6c  CMusic::CMusic(v)
 *      mangled: __ct__6CMusicFv */
int __ct__6CMusicFv(int param_1)

{
  __ct__7CPolObjFv(param_1);
  *(u8 **)(param_1 + 0x14) = __vt__6CMusic;
  memset((void *)(param_1 + 0x18),0,0x7c);
  *(u8 *)(param_1 + 0x7c) = 0x7f;
  Entry__6CMusicFv(param_1);
  return param_1;
}

/* ---- 0x003c5690 size 0x94  CMusic::~CMusic(v)
 *      mangled: __dt__6CMusicFv */
int __dt__6CMusicFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(u8 **)(param_1 + 0x14) = __vt__6CMusic;
    if ((long)((ulong)*(byte *)(param_1 + 0x7a) << 0x3b) < 0) {
      Dispose__6CMusicFv(param_1);
    }
    __dt__7CPolObjFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* ---- 0x003c5730 size 0x5c  CMusic::isRelease(v)
 *      mangled: isRelease__6CMusicFv */
u32 isRelease__6CMusicFv(int param_1)

{
  u32 uVar1;
  
  if ((((ulong)*(byte *)(param_1 + 0x7a) & 0xf) >> 2 == 0) && ((*(byte *)(param_1 + 0x7a) & 3) == 0)
     ) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}

/* ---- 0x003c5790 size 0xc0  CMusic::Release(v)
 *      mangled: Release__6CMusicFv */
u32 Release__6CMusicFv(int param_1)

{
  u32 uVar1;
  ulong uVar2;
  
  uVar2 = ((ulong)*(byte *)(param_1 + 0x7a) & 0xf) >> 2;
  if (uVar2 == 2) {
    uVar1 = 1;
  }
  else if (uVar2 == 0) {
    *(u32 *)(param_1 + 0x8c) = 0;
    *(u32 *)(param_1 + 0x84) = 0;
    ReleaseBGM__6CMusicFUi(param_1,0);
    ReleaseBGM__6CMusicFUi(param_1,1);
    *(byte *)(param_1 + 0x7a) = *(byte *)(param_1 + 0x7a) & 0xf3 | 4;
    uVar1 = 0;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

/* ---- 0x003c5850 size 0x4c  CMusic::SetVolume(i)
 *      mangled: SetVolume__6CMusicFi */
u8 SetVolume__6CMusicFi(int param_1,int param_2)

{
  u8 uVar1;
  
  uVar1 = *(u8 *)(param_1 + 0x7c);
  if (-1 < param_2) {
    *(char *)(param_1 + 0x7c) = (char)param_2;
  }
  return uVar1;
}

/* ---- 0x003c58a0 size 0xa4  CMusic::PlayBGM(UiUiPUc)
 *      mangled: PlayBGM__6CMusicFUiUiPUc */
void PlayBGM__6CMusicFUiUiPUc(int param_1,u16 param_2,u16 param_3,u32 param_4)

{
  long lVar1;
  
  lVar1 = isRelease__6CMusicFv(param_1);
  if (lVar1 == 0) {
    *(u32 *)(param_1 + 0x8c) = param_4;
    *(u16 *)(param_1 + 0x90) = param_2;
    *(u16 *)(param_1 + 0x92) = param_3;
    PlayBGMA__6CMusicFP8_BgmWork(param_1,param_1 + (uint)*(byte *)(param_1 + 0x78) * 0x30 + 0x18);
  }
  return;
}

/* ---- 0x003c5950 size 0x1dc  CMusic::PlayBGMA(P8_BgmWork)
 *      mangled: PlayBGMA__6CMusicFP8_BgmWork */
void PlayBGMA__6CMusicFP8_BgmWork(int param_1,byte *param_2)

{
  uint uVar1;
  
  if ((*param_2 & 0x80) != 0) {
    if ((param_2[1] & 0x31) != 0) {
      param_2[1] = param_2[1] | 0x20;
      return;
    }
    if ((*param_2 & 3) == 2) {
      uVar1 = (*(ushort *)(param_1 + 0x92) & 0x3f) / 7;
      if ((uVar1 != 0) && (uVar1 != 1)) {
        StopBGMA__6CMusicFP8_BgmWorki(param_1,param_2,uVar1);
        return;
      }
      param_2[1] = param_2[1] | 0x20;
      return;
    }
  }
  if (*(int *)(param_2 + 0x10) == 0) {
    param_2[2] = 0;
    param_2[1] = param_2[1] | 1;
    *param_2 = *param_2 | 0x80;
    param_2[5] = (byte)((uint)*(ushort *)(param_1 + 0x92) % 7);
    param_2[4] = (byte)*(u16 *)(param_1 + 0x90);
    param_2[7] = 0;
    if (*(int *)(param_1 + 0x8c) != 0) {
      *(u32 *)(param_2 + 0xc) = *(u32 *)(param_1 + 0x8c);
    }
    *(u32 *)(param_1 + 0x8c) = 0;
  }
  else {
    param_2[1] = param_2[1] | 0x20;
  }
  return;
}

/* ---- 0x003c5b30 size 0x78  CMusic::Entry(v)
 *      mangled: Entry__6CMusicFv */
void Entry__6CMusicFv(int param_1)

{
  if (-1 < (long)((ulong)*(byte *)(param_1 + 0x7a) << 0x3b)) {
    *(byte *)(param_1 + 0x7a) = *(byte *)(param_1 + 0x7a) & 0xef | 0x10;
    Entry__7CPollerFP7CPolObjib(app__4CApp + 0x48,param_1,0x81,0);
  }
  return;
}

/* ---- 0x003c5bb0 size 0x68  CMusic::Dispose(v)
 *      mangled: Dispose__6CMusicFv */
void Dispose__6CMusicFv(int param_1)

{
  if ((long)((ulong)*(byte *)(param_1 + 0x7a) << 0x3b) < 0) {
    *(byte *)(param_1 + 0x7a) = *(byte *)(param_1 + 0x7a) & 0xef;
    Dispose__7CPollerFP7CPolObj(app__4CApp + 0x48,param_1);
  }
  return;
}

/* ---- 0x003c5c20 size 0xe0  CMusic::StopBGMA(P8_BgmWorki)
 *      mangled: StopBGMA__6CMusicFP8_BgmWorki */
void StopBGMA__6CMusicFP8_BgmWorki(u64 param_1,int param_2,int param_3)

{
  u16 uVar1;
  u32 uStack_10;
  
  *(byte *)(param_2 + 1) = *(byte *)(param_2 + 1) | 0x10;
  *(char *)(param_2 + 3) = (char)param_3;
  uStack_10 = param_3;
  if (param_3 != 0) {
    uStack_10 = (param_3 + -1) % 3;
  }
  if (uStack_10 == 0) {
    *(byte *)(param_2 + 1) = *(byte *)(param_2 + 1) & 0xfd;
  }
  else {
    *(byte *)(param_2 + 1) = *(byte *)(param_2 + 1) | 2;
    *(u8 *)(param_2 + 6) = 0;
    if (uStack_10 == 1) {
      uVar1 = 2000;
    }
    else {
      uVar1 = 1000;
    }
    *(u16 *)(param_2 + 10) = uVar1;
  }
  return;
}

/* ---- 0x003c5d00 size 0xd8  CMusic::StopBGM(Ui)
 *      mangled: StopBGM__6CMusicFUi */
void StopBGM__6CMusicFUi(int param_1,uint param_2)

{
  long lVar1;
  byte *pbVar2;
  byte bVar3;
  
  lVar1 = isRelease__6CMusicFv(param_1);
  if (lVar1 == 0) {
    pbVar2 = (byte *)(param_1 + (uint)*(byte *)(param_1 + 0x78) * 0x30 + 0x18);
    bVar3 = *pbVar2 & 0x8f;
    if ((bVar3 == 0x82) || (bVar3 == 0x86)) {
      StopBGMA__6CMusicFP8_BgmWorki(param_1,pbVar2,(param_2 & 0x3f) / 7);
    }
  }
  return;
}

/* ---- 0x003c5de0 size 0x100  CMusic::FadeBGM(UiUi)
 *      mangled: FadeBGM__6CMusicFUiUi */
void FadeBGM__6CMusicFUiUi(int param_1,int param_2,int param_3)

{
  long lVar1;
  byte bVar2;
  
  lVar1 = isRelease__6CMusicFv(param_1);
  if (lVar1 == 0) {
    if ((param_2 == 0) && (param_3 == 0)) {
      StopBGM__6CMusicFUi(param_1,7);
    }
    else {
      param_1 = param_1 + (uint)*(byte *)(param_1 + 0x78) * 0x30;
      bVar2 = *(byte *)(param_1 + 0x18) & 0x8f;
      if ((bVar2 == 0x82) || (bVar2 == 0x86)) {
        *(char *)(param_1 + 0x1e) = (char)param_2;
        *(short *)(param_1 + 0x22) = (short)param_3;
        *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) | 2;
        if (param_2 == 0) {
          *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) | 0x10;
        }
      }
    }
  }
  return;
}

/* ---- 0x003c5ee0 size 0x60  CMusic::ReleaseBGM(Ui)
 *      mangled: ReleaseBGM__6CMusicFUi */
void ReleaseBGM__6CMusicFUi(int param_1)

{
  param_1 = param_1 + (uint)*(byte *)(param_1 + 0x78) * 0x30;
  if ((*(byte *)(param_1 + 0x18) & 0x80) != 0) {
    *(byte *)(param_1 + 0x19) = *(byte *)(param_1 + 0x19) | 0x20;
  }
  return;
}

/* ---- 0x003c5f40 size 0x224  CMusic::Polling(v)
 *      mangled: Polling__6CMusicFv */
u32 Polling__6CMusicFv(int param_1)

{
  int iVar1;
  u32 uVar2;
  long lVar3;
  byte *pbVar4;
  int iVar5;
  
  if (((((ulong)*(byte *)(param_1 + 0x7a) & 0xf) >> 2 == 1) && (*(char *)(param_1 + 0x18) == '\0'))
     && (*(char *)(param_1 + 0x48) == '\0')) {
    *(byte *)(param_1 + 0x7a) = *(byte *)(param_1 + 0x7a) & 0xf3 | 8;
  }
  for (iVar5 = 0; iVar5 < 2; iVar5 = iVar5 + 1) {
    iVar1 = param_1 + iVar5 * 0x30;
    pbVar4 = (byte *)(iVar1 + 0x18);
    if (*(char *)(iVar1 + 0x19) != '\0') {
      HandleReq__6CMusicFP8_BgmWork(param_1,pbVar4);
    }
    if ((((*pbVar4 & 0x83) == 0x83) && (*(char *)(iVar1 + 0x1f) == '\0')) &&
       (*(u8 *)(iVar1 + 0x1f) = 1, *(int *)(param_1 + 0x84) != 0)) {
      (**(code **)(param_1 + 0x84))(3,0,*(u32 *)(param_1 + 0x88));
    }
    if (((*(char *)(iVar1 + 0x19) == '\0') && (*(int *)(param_1 + 0x8c) != 0)) &&
       (lVar3 = isRelease__6CMusicFv(param_1), lVar3 == 0)) {
      PlayBGMA__6CMusicFP8_BgmWork(param_1,pbVar4);
    }
  }
  if ((*(byte *)(param_1 + 0x7a) & 3) == 0) {
    uVar2 = 0;
  }
  else if (((ulong)*(byte *)(param_1 + 0x7a) & 0xf) >> 2 == 1) {
    uVar2 = 0;
  }
  else {
    *(byte *)(param_1 + 0x7a) = *(byte *)(param_1 + 0x7a) & 0xef;
    *(u8 *)(param_1 + 0xc) = 1;
    *(u8 *)(param_1 + 0xe) = 0;
    uVar2 = 1;
  }
  return uVar2;
}

/* ---- 0x003c6170 size 0x2c  CMusic::CancelPlay(P8_BgmWork)
 *      mangled: CancelPlay__6CMusicFP8_BgmWork */
void CancelPlay__6CMusicFP8_BgmWork(u64 param_1,int param_2)

{
  *(byte *)(param_2 + 1) = *(byte *)(param_2 + 1) & 0xfe;
  *(u8 *)(param_2 + 2) = 0;
  return;
}

/* ---- 0x003c61a0 size 0x7ec  CMusic::HandleReq(P8_BgmWork)
 *      mangled: HandleReq__6CMusicFP8_BgmWork */
u32 HandleReq__6CMusicFP8_BgmWork(int param_1,byte *param_2)

{
  byte bVar1;
  u32 uVar2;
  u32 uVar3;
  int iVar4;
  long lVar5;
  byte bVar6;
  
  bVar1 = param_2[1];
  if ((bVar1 & 1) != 0) {
    bVar6 = param_2[2];
    if (bVar6 == 4) {
      uVar3 = *(u32 *)(param_2 + 0x18);
      lVar5 = GetStatus__4SdrvFUi(sys__4Sdrv,uVar3);
      if (lVar5 == -2) {
        CloseHandle__4SdrvFUi(sys__4Sdrv,uVar3);
        CancelPlay__6CMusicFP8_BgmWork(param_1,param_2);
      }
      else {
        if (lVar5 != 3) {
          return 0;
        }
        uVar2 = GetOption__4SdrvFUi(sys__4Sdrv,uVar3);
        *(u32 *)(param_2 + 0x14) = uVar2;
        CloseHandle__4SdrvFUi(sys__4Sdrv,uVar3);
        iVar4 = 0;
        if (param_2[5] != 0) {
          iVar4 = (int)(param_2[5] - 1) % 3;
        }
        if (iVar4 != 0) {
          if (iVar4 == 1) {
            uVar3 = 1000;
          }
          else {
            uVar3 = 500;
          }
          SetBGMParam__4SdrvFUiiii
                    (sys__4Sdrv,*(u32 *)(param_2 + 0x14),0,*(u8 *)(param_1 + 0x7c),
                     uVar3);
        }
        CancelPlay__6CMusicFP8_BgmWork(param_1,param_2);
        if (*(int *)(param_1 + 0x84) != 0) {
          (**(code **)(param_1 + 0x84))(2,0,*(u32 *)(param_1 + 0x88));
        }
      }
    }
    else {
      if (bVar6 != 3) {
        if (bVar6 != 2) {
          if (bVar6 != 1) {
            if (bVar6 == 0) {
              if ((bVar1 & 0x30) == 0) {
                lVar5 = AutoLoad__4SdrvFPvPv(sys__4Sdrv,*(u32 *)(param_2 + 0xc),0);
                if (lVar5 != -1) {
                  *(int *)(param_2 + 0x18) = (int)lVar5;
                  *param_2 = *param_2 & 0xc0;
                  param_2[2] = param_2[2] + 1;
                }
                return 0;
              }
              CancelPlay__6CMusicFP8_BgmWork(param_1,param_2);
            }
            goto LAB_003c6680;
          }
          lVar5 = GetStatus__4SdrvFUi(sys__4Sdrv,*(u32 *)(param_2 + 0x18));
          if (lVar5 == -2) {
            CloseHandle__4SdrvFUi(sys__4Sdrv,*(u32 *)(param_2 + 0x18));
            CancelPlay__6CMusicFP8_BgmWork(param_1,param_2);
            return 1;
          }
          if (lVar5 != 3) {
            return 0;
          }
          uVar3 = GetOption__4SdrvFUi(sys__4Sdrv,*(u32 *)(param_2 + 0x18));
          *(u32 *)(param_2 + 0x10) = uVar3;
          CloseHandle__4SdrvFUi(sys__4Sdrv,*(u32 *)(param_2 + 0x18));
          if (*(int *)(param_1 + 0x84) != 0) {
            (**(code **)(param_1 + 0x84))(1,0,*(u32 *)(param_1 + 0x88));
          }
          if (((bVar1 & 0x30) != 0) || (lVar5 = isRelease__6CMusicFv(param_1), lVar5 != 0)) {
            CancelPlay__6CMusicFP8_BgmWork(param_1,param_2);
            goto LAB_003c6680;
          }
          param_2[2] = param_2[2] + 1;
        }
        InitBgmParam__4SdrvFP9_BgmParamiPvUi(sys__4Sdrv,param_2 + 0x20,9,param_2,param_1);
        bVar6 = *(byte *)(param_1 + 0x7c);
        if ((param_2[5] != 0) && ((int)(param_2[5] - 1) % 3 != 0)) {
          bVar6 = 0x20;
        }
        param_2[0x20] = bVar6;
        param_2[2] = param_2[2] + 1;
      }
      if (((bVar1 & 0x30) == 0) && (lVar5 = isRelease__6CMusicFv(param_1), lVar5 == 0)) {
        lVar5 = PlayBGM__4SdrvFUiiiP9_BgmParam
                          (sys__4Sdrv,*(u32 *)(param_2 + 0x10),param_2[4],0x2180,
                           param_2 + 0x20);
        if (lVar5 != -1) {
          *(int *)(param_2 + 0x18) = (int)lVar5;
          *param_2 = *param_2 | 0x82;
          param_2[2] = param_2[2] + 1;
        }
        return 0;
      }
      CancelPlay__6CMusicFP8_BgmWork(param_1,param_2);
    }
  }
LAB_003c6680:
  if ((bVar1 & 0x20) == 0) {
    if ((bVar1 & 2) != 0) {
      if (param_2[2] == 1) {
        iVar4 = GetTimer__7SysToolFv();
        if ((uint)(iVar4 - *(int *)(param_2 + 0x1c)) < (uint)*(ushort *)(param_2 + 10)) {
          return 0;
        }
        param_2[2] = 0;
        param_2[1] = param_2[1] & 0xfd;
      }
      else if (param_2[2] == 0) {
        if ((*param_2 == 0x82) &&
           (SetBGMParam__4SdrvFUiiii
                      (sys__4Sdrv,*(u32 *)(param_2 + 0x14),0,param_2[6],
                       *(u16 *)(param_2 + 10)), *(short *)(param_2 + 10) != 0)) {
          param_2[2] = param_2[2] + 1;
          uVar3 = GetTimer__7SysToolFv();
          *(u32 *)(param_2 + 0x1c) = uVar3;
          return 0;
        }
        param_2[1] = param_2[1] & 0xfd;
        return 1;
      }
    }
    if (((bVar1 & 0x10) != 0) &&
       (lVar5 = StopBGM__4SdrvFUiii(sys__4Sdrv,*(u32 *)(param_2 + 0x14),0,0), lVar5 != -1)) {
      param_2[1] = param_2[1] & 0xef;
    }
    if ((bVar1 & 4) != 0) {
      if (((*param_2 & 0x8f) == 0x82) || ((*param_2 & 0x8f) == 0x86)) {
        SetBGMParam__4SdrvFUiP9_BgmParam(sys__4Sdrv,*(u32 *)(param_2 + 0x14),param_2 + 0x20);
      }
      param_2[1] = param_2[1] & 0xfb;
    }
  }
  else {
    if ((*param_2 & 3) == 2) {
      lVar5 = ReleaseBGM__4SdrvFUii(sys__4Sdrv,*(u32 *)(param_2 + 0x14),1);
      if (lVar5 == -1) {
        return 0;
      }
    }
    else if ((*(int *)(param_2 + 0x10) != 0) &&
            (lVar5 = ReleaseSDH__4SdrvFUi(sys__4Sdrv,*(u32 *)(param_2 + 0x10)), lVar5 == -1))
    {
      return 0;
    }
    param_2[0x10] = 0;
    param_2[0x11] = 0;
    param_2[0x12] = 0;
    param_2[0x13] = 0;
    *param_2 = 0;
    param_2[1] = 0;
  }
  return 1;
}

