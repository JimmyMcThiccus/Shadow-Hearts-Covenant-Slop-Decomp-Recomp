/*
 * Sdrv.c -- Ghidra decompiler output (SLPM_602.19, JP Furokuban), tidied by tools/E_gen_decomp.py
 * 45 functions. Types: u8/u16/u32/u64 = undefined1/2/4/8. Addresses in comments are JP main-exe addresses.
 */

/* ---- 0x00372400 size 0x12c  Sdrv::Reset(i)
 *      mangled: Reset__4SdrvFi */
long Reset__4SdrvFi(int param_1)

{
  int iVar1;
  long lVar2;
  
  if (param_1 == 0) {
    Init__6SifCmdFv();
    if (sys__4Sdrv == 0) {
      lVar2 = __nw__FUi(0x24);
      iVar1 = 0;
      if (lVar2 != 0) {
        iVar1 = __ct__4SdrvFv(lVar2);
      }
      sys__4Sdrv = iVar1;
      Start__4SdrvFv(sys__4Sdrv);
    }
  }
  else if (sys__4Sdrv != 0) {
    while( true ) {
      lVar2 = Reset__6SdrvEEFv(*(u32 *)(sys__4Sdrv + 0x18));
      if (lVar2 < 0) {
        return lVar2;
      }
      if (lVar2 != 0) break;
      if (param_1 == 1) {
        return 0;
      }
    }
    if (sys__4Sdrv != 0) {
      (**(code **)(*(int *)(sys__4Sdrv + 0x14) + 8))(sys__4Sdrv,1);
    }
    sys__4Sdrv = 0;
  }
  return 1;
}

/* ---- 0x00372530 size 0x7c  Sdrv::~Sdrv(v)
 *      mangled: __dt__4SdrvFv */
int __dt__4SdrvFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(u8 **)(param_1 + 0x14) = __vt__4Sdrv;
    Release__4SdrvFv(param_1);
    __dt__7CPolObjFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* ---- 0x003725b0 size 0x78  Sdrv::Start(v)
 *      mangled: Start__4SdrvFv */
void Start__4SdrvFv(int param_1)

{
  if ((**(byte **)(param_1 + 0x18) & 1) == 0) {
    Entry__7CPollerFP7CPolObjib(app__4CApp + 0x60,sys__4Sdrv,0x8a,0);
    **(byte **)(param_1 + 0x18) = **(byte **)(param_1 + 0x18) & 0xfe | 1;
  }
  return;
}

/* ---- 0x00372630 size 0x110  Sdrv::Sdrv(v)
 *      mangled: __ct__4SdrvFv */
int __ct__4SdrvFv(int param_1)

{
  u32 uVar1;
  long lVar2;
  u64 uVar3;
  u64 uVar4;
  
  __ct__7CPolObjFv(param_1);
  *(u8 **)(param_1 + 0x14) = __vt__4Sdrv;
  *(u32 *)(param_1 + 0x1c) = 0;
  *(u32 *)(param_1 + 0x20) = 0;
  lVar2 = __nw__FUi(0x39c);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = __ct__6SdrvEEFv(lVar2);
  }
  *(u32 *)(param_1 + 0x18) = uVar1;
  uVar3 = CheckID__6SifCmdFPCc(0x3ff580);
  uVar4 = GetBuffer__6SifCmdFi(2);
  SetID__6SdrvEEFii(*(u32 *)(param_1 + 0x18),uVar3,uVar4);
  DIntr();
  sceSifAddCmdHandler(uVar4,0x376cf0,*(u32 *)(param_1 + 0x18));
  EIntr();
  Init__6SdrvEEFv(*(u32 *)(param_1 + 0x18));
  return param_1;
}

/* ---- 0x00372780 size 0x48  Sdrv::Release(v)
 *      mangled: Release__4SdrvFv */
void Release__4SdrvFv(int param_1)

{
  if (*(int *)(param_1 + 0x18) != 0) {
    __dt__6SdrvEEFv(*(u32 *)(param_1 + 0x18),1);
    *(u32 *)(param_1 + 0x18) = 0;
  }
  return;
}

/* ---- 0x00372830 size 0x10c  Sdrv::Polling(v)
 *      mangled: Polling__4SdrvFv */
u64 Polling__4SdrvFv(int param_1)

{
  if (logWp != &logBuf2) {
    logWp = &logBuf2;
  }
  if (**(byte **)(param_1 + 0x18) >> 6 == 0) {
    DelayReleaseSE__6SdrvEEFv(*(u32 *)(param_1 + 0x18));
    DelayReleaseBGM__6SdrvEEFv(*(u32 *)(param_1 + 0x18));
    if ((long)((ulong)**(byte **)(param_1 + 0x18) << 0x3e) < 0) {
      CmdHandler__6SdrvEEFv(*(u32 *)(param_1 + 0x18));
    }
    if (((ulong)**(byte **)(param_1 + 0x18) & 0xf) >> 2 != 0) {
      CmdHandlerA__6SdrvEEFv(*(u32 *)(param_1 + 0x18));
    }
    UpdateEEStream__6SdrvEEFv(*(u32 *)(param_1 + 0x18));
  }
  else {
    CmdReset__6SdrvEEFv(*(u32 *)(param_1 + 0x18));
  }
  return 0;
}

/* ---- 0x00372940 size 0x78  Sdrv::InitSeParam(P8_SeParamiPv)
 *      mangled: InitSeParam__4SdrvFP8_SeParamiPv */
void * InitSeParam__4SdrvFP8_SeParamiPv
                 (u64 param_1,u8 *param_2,u16 param_3,u32 param_4)

{
  void *pvVar1;
  
  pvVar1 = memset(param_2,0,0xc);
  *param_2 = 0x7f;
  param_2[1] = 0x40;
  *(u16 *)(param_2 + 4) = 1000;
  *(u16 *)(param_2 + 6) = param_3;
  *(u32 *)(param_2 + 8) = param_4;
  return pvVar1;
}

/* ---- 0x003729c0 size 0x34  Sdrv::GetStatus(Ui)
 *      mangled: GetStatus__4SdrvFUi */
void GetStatus__4SdrvFUi(int param_1,u32 param_2)

{
  GetStatus__6SdrvEEFUi(*(u32 *)(param_1 + 0x18),param_2);
  return;
}

/* ---- 0x00372a00 size 0x34  Sdrv::GetOption(Ui)
 *      mangled: GetOption__4SdrvFUi */
void GetOption__4SdrvFUi(int param_1,u32 param_2)

{
  GetOption__6SdrvEEFUi(*(u32 *)(param_1 + 0x18),param_2);
  return;
}

/* ---- 0x00372a40 size 0x34  Sdrv::CloseHandle(Ui)
 *      mangled: CloseHandle__4SdrvFUi */
void CloseHandle__4SdrvFUi(int param_1,u32 param_2)

{
  CloseHandle__6SdrvEEFUi(*(u32 *)(param_1 + 0x18),param_2);
  return;
}

/* ---- 0x00372a80 size 0x3c  Sdrv::AutoLoad(PvPv)
 *      mangled: AutoLoad__4SdrvFPvPv */
void AutoLoad__4SdrvFPvPv(int param_1,u32 param_2,u32 param_3)

{
  AutoLoad__6SdrvEEFPvPv(*(u32 *)(param_1 + 0x18),param_2,param_3);
  return;
}

/* ---- 0x00372ac0 size 0x34  Sdrv::ReleaseSDH(Ui)
 *      mangled: ReleaseSDH__4SdrvFUi */
void ReleaseSDH__4SdrvFUi(int param_1,u32 param_2)

{
  ReleaseSDH__6SdrvEEFUi(*(u32 *)(param_1 + 0x18),param_2);
  return;
}

/* ---- 0x00372b00 size 0x3c  Sdrv::PlaySE(UiP8_SeParam)
 *      mangled: PlaySE__4SdrvFUiP8_SeParam */
void PlaySE__4SdrvFUiP8_SeParam(int param_1,u32 param_2,u32 param_3)

{
  PlaySE__6SdrvEEFUiP8_SeParam(*(u32 *)(param_1 + 0x18),param_2,param_3);
  return;
}

/* ---- 0x00372b40 size 0x34  Sdrv::GetSEStat(Ui)
 *      mangled: GetSEStat__4SdrvFUi */
void GetSEStat__4SdrvFUi(int param_1,u32 param_2)

{
  GetSEStat__6SdrvEEFUi(*(u32 *)(param_1 + 0x18),param_2);
  return;
}

/* ---- 0x00372b80 size 0x3c  Sdrv::ReleaseSE(Uii)
 *      mangled: ReleaseSE__4SdrvFUii */
void ReleaseSE__4SdrvFUii(int param_1,u32 param_2,u32 param_3)

{
  ReleaseSE__6SdrvEEFUii(*(u32 *)(param_1 + 0x18),param_2,param_3);
  return;
}

/* ---- 0x00372bc0 size 0x34  Sdrv::SetMode(i)
 *      mangled: SetMode__4SdrvFi */
void SetMode__4SdrvFi(int param_1,u32 param_2)

{
  SetMode__6SdrvEEFi(*(u32 *)(param_1 + 0x18),param_2);
  return;
}

/* ---- 0x00372c00 size 0x54  Sdrv::SetReverb(iiiii)
 *      mangled: SetReverb__4SdrvFiiiii */
void SetReverb__4SdrvFiiiii
               (int param_1,u32 param_2,u32 param_3,u32 param_4,
               u32 param_5,u32 param_6)

{
  SetReverb__6SdrvEEFiiiii(*(u32 *)(param_1 + 0x18),param_2,param_3,param_4,param_5,param_6);
  return;
}

/* ---- 0x00372c60 size 0x54  Sdrv::StreamOpen(Ui)
 *      mangled: StreamOpen__4SdrvFUi */
void StreamOpen__4SdrvFUi(int param_1,u32 param_2)

{
  StreamCtrl__6SdrvEEFiUiUiUiUi(*(u32 *)(param_1 + 0x18),0,0,param_2,0,0);
  StreamGetValue__6SdrvEEFv(*(u32 *)(param_1 + 0x18));
  return;
}

/* ---- 0x00372ce0 size 0x44  Sdrv::StreamClose(Ui)
 *      mangled: StreamClose__4SdrvFUi */
void StreamClose__4SdrvFUi(int param_1,u32 param_2)

{
  StreamCtrl__6SdrvEEFiUiUiUiUi(*(u32 *)(param_1 + 0x18),1,param_2,0,0,0);
  return;
}

/* ---- 0x00372d30 size 0x4c  Sdrv::StreamCreate(UiUiUi)
 *      mangled: StreamCreate__4SdrvFUiUiUi */
void StreamCreate__4SdrvFUiUiUi
               (int param_1,u32 param_2,u32 param_3,u32 param_4)

{
  StreamCtrl__6SdrvEEFiUiUiUiUi(*(u32 *)(param_1 + 0x18),2,param_2,param_3,param_4,0);
  return;
}

/* ---- 0x00372d80 size 0x4c  Sdrv::StreamSetParam(UiUiUi)
 *      mangled: StreamSetParam__4SdrvFUiUiUi */
void StreamSetParam__4SdrvFUiUiUi
               (int param_1,u32 param_2,u32 param_3,u32 param_4)

{
  StreamCtrl__6SdrvEEFiUiUiUiUi(*(u32 *)(param_1 + 0x18),3,param_2,param_3,param_4,0);
  return;
}

/* ---- 0x00372dd0 size 0x48  Sdrv::StreamGetStat(UiUi)
 *      mangled: StreamGetStat__4SdrvFUiUi */
void StreamGetStat__4SdrvFUiUi(int param_1,u32 param_2,u32 param_3)

{
  StreamCtrl__6SdrvEEFiUiUiUiUi(*(u32 *)(param_1 + 0x18),4,param_2,param_3,0,0);
  return;
}

/* ---- 0x00372e20 size 0x58  Sdrv::StreamAllocBuf(UiUi)
 *      mangled: StreamAllocBuf__4SdrvFUiUi */
void StreamAllocBuf__4SdrvFUiUi(int param_1,u32 param_2,u32 param_3)

{
  StreamCtrl__6SdrvEEFiUiUiUiUi(*(u32 *)(param_1 + 0x18),5,param_2,param_3,0,0);
  StreamGetValue__6SdrvEEFv(*(u32 *)(param_1 + 0x18));
  return;
}

/* ---- 0x00372e80 size 0x5c  Sdrv::StreamSetBuf(UiPvUi)
 *      mangled: StreamSetBuf__4SdrvFUiPvUi */
void StreamSetBuf__4SdrvFUiPvUi
               (int param_1,u32 param_2,u32 param_3,u32 param_4)

{
  StreamCtrl__6SdrvEEFiUiUiUiUi(*(u32 *)(param_1 + 0x18),6,param_2,param_3,param_4,0);
  StreamGetValue__6SdrvEEFv(*(u32 *)(param_1 + 0x18));
  return;
}

/* ---- 0x00372ee0 size 0x64  Sdrv::StreamGetWriteInfo(UiRPUc)
 *      mangled: StreamGetWriteInfo__4SdrvFUiRPUc */
void StreamGetWriteInfo__4SdrvFUiRPUc(int param_1,u32 param_2,u32 *param_3)

{
  u32 uStack_34;
  int iStack_30;
  u32 uStack_20;
  u32 *puStack_10;
  
  iStack_30 = param_1;
  uStack_20 = param_2;
  puStack_10 = param_3;
  StreamCtrl__6SdrvEEFiUiUiUiUi(*(u32 *)(param_1 + 0x18),7,param_2,&uStack_34,0,0);
  *puStack_10 = uStack_34;
  StreamGetValue__6SdrvEEFv(*(u32 *)(iStack_30 + 0x18));
  return;
}

/* ---- 0x00372f50 size 0x5c  Sdrv::StreamWriteData(UiUiUi)
 *      mangled: StreamWriteData__4SdrvFUiUiUi */
void StreamWriteData__4SdrvFUiUiUi
               (int param_1,u32 param_2,u32 param_3,u32 param_4)

{
  StreamCtrl__6SdrvEEFiUiUiUiUi(*(u32 *)(param_1 + 0x18),8,param_2,param_3,param_4,0);
  StreamGetValue__6SdrvEEFv(*(u32 *)(param_1 + 0x18));
  return;
}

/* ---- 0x00372fb0 size 0x58  Sdrv::StreamStart(UiUi)
 *      mangled: StreamStart__4SdrvFUiUi */
void StreamStart__4SdrvFUiUi(int param_1,u32 param_2,u32 param_3)

{
  StreamCtrl__6SdrvEEFiUiUiUiUi(*(u32 *)(param_1 + 0x18),9,param_2,param_3,0,0);
  StreamGetValue__6SdrvEEFv(*(u32 *)(param_1 + 0x18));
  return;
}

/* ---- 0x00373010 size 0x58  Sdrv::StreamStop(UiUi)
 *      mangled: StreamStop__4SdrvFUiUi */
void StreamStop__4SdrvFUiUi(int param_1,u32 param_2,u32 param_3)

{
  StreamCtrl__6SdrvEEFiUiUiUiUi(*(u32 *)(param_1 + 0x18),10,param_2,param_3,0,0);
  StreamGetValue__6SdrvEEFv(*(u32 *)(param_1 + 0x18));
  return;
}

/* ---- 0x00373070 size 0x58  Sdrv::StreamPause(UiUi)
 *      mangled: StreamPause__4SdrvFUiUi */
void StreamPause__4SdrvFUiUi(int param_1,u32 param_2,u32 param_3)

{
  StreamCtrl__6SdrvEEFiUiUiUiUi(*(u32 *)(param_1 + 0x18),0xb,param_2,param_3,0,0);
  StreamGetValue__6SdrvEEFv(*(u32 *)(param_1 + 0x18));
  return;
}

/* ---- 0x003730d0 size 0x34  Sdrv::Pause(Ui)
 *      mangled: Pause__4SdrvFUi */
void Pause__4SdrvFUi(int param_1,u32 param_2)

{
  Pause__6SdrvEEFUi(*(u32 *)(param_1 + 0x18),param_2);
  return;
}

/* ---- 0x00373110 size 0x88  Sdrv::InitBgmParam(P9_BgmParamiPvUi)
 *      mangled: InitBgmParam__4SdrvFP9_BgmParamiPvUi */
void * InitBgmParam__4SdrvFP9_BgmParamiPvUi
                 (u64 param_1,u8 *param_2,u16 param_3,u32 param_4,
                 u32 param_5)

{
  void *pvVar1;
  
  pvVar1 = memset(param_2,0,0x10);
  *param_2 = 0x7f;
  param_2[1] = 0x40;
  *(u16 *)(param_2 + 4) = 1000;
  *(u16 *)(param_2 + 6) = param_3;
  *(u32 *)(param_2 + 8) = param_4;
  *(u32 *)(param_2 + 0xc) = param_5;
  return pvVar1;
}

/* ---- 0x003731a0 size 0x4c  Sdrv::PlayBGM(UiiiP9_BgmParam)
 *      mangled: PlayBGM__4SdrvFUiiiP9_BgmParam */
void PlayBGM__4SdrvFUiiiP9_BgmParam
               (int param_1,u32 param_2,u32 param_3,u32 param_4,
               u32 param_5)

{
  PlayBGM__6SdrvEEFUiiiP9_BgmParam(*(u32 *)(param_1 + 0x18),param_2,param_3,param_4,param_5);
  return;
}

/* ---- 0x003731f0 size 0x44  Sdrv::StopBGM(Uiii)
 *      mangled: StopBGM__4SdrvFUiii */
void StopBGM__4SdrvFUiii(int param_1,u32 param_2,u32 param_3,u32 param_4)

{
  StopBGM__6SdrvEEFUiii(*(u32 *)(param_1 + 0x18),param_2,param_3,param_4);
  return;
}

/* ---- 0x00373240 size 0x3c  Sdrv::ReleaseBGM(Uii)
 *      mangled: ReleaseBGM__4SdrvFUii */
void ReleaseBGM__4SdrvFUii(int param_1,u32 param_2,u32 param_3)

{
  ReleaseBGM__6SdrvEEFUii(*(u32 *)(param_1 + 0x18),param_2,param_3);
  return;
}

/* ---- 0x00373280 size 0x3c  Sdrv::SetSEParam(UiP8_SeParam)
 *      mangled: SetSEParam__4SdrvFUiP8_SeParam */
void SetSEParam__4SdrvFUiP8_SeParam(int param_1,u32 param_2,u32 param_3)

{
  SetSEParam__6SdrvEEFUiP8_SeParam(*(u32 *)(param_1 + 0x18),param_2,param_3);
  return;
}

/* ---- 0x003732c0 size 0x4c  Sdrv::SetSEParam(Uiiii)
 *      mangled: SetSEParam__4SdrvFUiiii */
void SetSEParam__4SdrvFUiiii
               (int param_1,u32 param_2,u32 param_3,u32 param_4,
               u32 param_5)

{
  SetSEParam__6SdrvEEFUiiii(*(u32 *)(param_1 + 0x18),param_2,param_3,param_4,param_5);
  return;
}

/* ---- 0x00373310 size 0x3c  Sdrv::SetBGMParam(UiP9_BgmParam)
 *      mangled: SetBGMParam__4SdrvFUiP9_BgmParam */
void SetBGMParam__4SdrvFUiP9_BgmParam(int param_1,u32 param_2,u32 param_3)

{
  SetBGMParam__6SdrvEEFUiP9_BgmParam(*(u32 *)(param_1 + 0x18),param_2,param_3);
  return;
}

/* ---- 0x00373350 size 0x4c  Sdrv::SetBGMParam(Uiiii)
 *      mangled: SetBGMParam__4SdrvFUiiii */
void SetBGMParam__4SdrvFUiiii
               (int param_1,u32 param_2,u32 param_3,u32 param_4,
               u32 param_5)

{
  SetBGMParam__6SdrvEEFUiiii(*(u32 *)(param_1 + 0x18),param_2,param_3,param_4,param_5);
  return;
}

/* ---- 0x003733a0 size 0x34  Sdrv::GetWaveBank(Pv)
 *      mangled: GetWaveBank__4SdrvFPv */
void GetWaveBank__4SdrvFPv(int param_1,u32 param_2)

{
  GetWaveBank__6SdrvEEFPv(*(u32 *)(param_1 + 0x18),param_2);
  return;
}

/* ---- 0x003733e0 size 0x10  Sdrv::Report(v)
 *      mangled: Report__4SdrvFv */
void Report__4SdrvFv(void)

{
  return;
}

/* ---- 0x0037a470 size 0xec  Sdrv::CreateSoundBuffer(Ui)
 *      mangled: CreateSoundBuffer__4SdrvFUi */
void CreateSoundBuffer__4SdrvFUi(int param_1,int param_2)

{
  uint *__s;
  
  if (*(int *)(param_1 + 0x1c) != 0) {
    __dla__FPv(*(u32 *)(param_1 + 0x1c));
    *(u32 *)(param_1 + 0x1c) = 0;
  }
  *(u32 *)(param_1 + 0x20) = 0;
  if (param_2 != 0) {
    *(int *)(param_1 + 0x20) = param_2;
    __s = (uint *)__nwa__FUi(param_2);
    *(uint **)(param_1 + 0x1c) = __s;
    memset(__s,0,0x10);
    *__s = *__s & 0xff000000 | (uint)((ulong)((long)(param_2 + -0x10) << 0x28) >> 0x28);
    *(byte *)((int)__s + 3) = *(byte *)((int)__s + 3) & 0xfd | 2;
    __s[1] = 0xffffffff;
  }
  return;
}

/* ---- 0x0037a560 size 0xf4  Sdrv::ResetSoundBuffer(i)
 *      mangled: ResetSoundBuffer__4SdrvFi */
void ResetSoundBuffer__4SdrvFi(int param_1,int param_2)

{
  uint *__s;
  
  if (param_2 == 1) {
    if (*(int *)(param_1 + 0x1c) != 0) {
      __dla__FPv(*(u32 *)(param_1 + 0x1c));
      *(u32 *)(param_1 + 0x1c) = 0;
    }
    *(u32 *)(param_1 + 0x20) = 0;
  }
  else if (*(int *)(param_1 + 0x1c) != 0) {
    __s = *(uint **)(param_1 + 0x1c);
    memset(__s,0,0x10);
    *__s = *__s & 0xff000000 |
           (uint)((ulong)((long)(*(int *)(param_1 + 0x20) + -0x10) << 0x28) >> 0x28);
    *(byte *)((int)__s + 3) = *(byte *)((int)__s + 3) & 0xfd | 2;
    __s[1] = 0xffffffff;
  }
  return;
}

/* ---- 0x0037a660 size 0x2dc  Sdrv::GetSoundMemory(iUi)
 *      mangled: GetSoundMemory__4SdrvFiUi */
uint * GetSoundMemory__4SdrvFiUi(int param_1,int param_2,uint param_3)

{
  uint uVar1;
  uint *puVar2;
  uint *puVar3;
  uint *puVar4;
  uint uVar5;
  uint uStack_10;
  
  uVar1 = param_3 + 0xf & 0xfffffff0;
  puVar2 = (uint *)0x0;
  puVar4 = *(uint **)(param_1 + 0x1c);
  if (param_2 == 1) {
    while (-1 < (long)((ulong)*(byte *)((int)puVar4 + 3) << 0x3e)) {
      puVar4 = (uint *)puVar4[2];
    }
  }
  uVar5 = 0;
  do {
    if (((*puVar4 & 0x1000000) == 0) && (uVar1 <= (*puVar4 & 0xffffff))) {
      puVar3 = puVar4;
      if (param_3 != 0) {
LAB_0037a7b8:
        if (puVar3 == (uint *)0x0) {
          puVar3 = (uint *)0x0;
        }
        else {
          uStack_10 = param_3;
          if (param_3 == 0) {
            uVar1 = (uint)((ulong)((long)(int)*puVar3 << 0x28) >> 0x28);
            uStack_10 = uVar1;
          }
          uVar5 = (uint)((ulong)((long)(int)*puVar3 << 0x28) >> 0x28) - uVar1;
          *puVar3 = *puVar3 & 0xff000000 | (uint)((ulong)((long)(int)uStack_10 << 0x28) >> 0x28);
          *(byte *)((int)puVar3 + 3) = *(byte *)((int)puVar3 + 3) & 0xfe | 1;
          if (0xf < uVar5) {
            puVar4 = (uint *)((int)puVar3 + uVar1 + 0x10);
            memset(puVar4,0,0x10);
            *puVar4 = *puVar4 & 0xff000000 |
                      (uint)((ulong)((long)(int)(uVar5 - 0x10) << 0x28) >> 0x28);
            *(uint **)((int)puVar3 + uVar1 + 0x14) = puVar3;
            if ((long)((ulong)*(byte *)((int)puVar3 + 3) << 0x3e) < 0) {
              *(byte *)((int)puVar3 + uVar1 + 0x13) =
                   *(byte *)((int)puVar3 + uVar1 + 0x13) & 0xfd | 2;
              *(byte *)((int)puVar3 + 3) = *(byte *)((int)puVar3 + 3) & 0xfd;
            }
            else {
              uVar5 = puVar3[2];
              *(uint **)(uVar5 + 4) = puVar4;
              *(uint *)((int)puVar3 + uVar1 + 0x18) = uVar5;
            }
            puVar3[2] = (uint)puVar4;
          }
          *(u8 *)((int)puVar3 + 0xf) = 0x10;
          puVar3 = puVar3 + 4;
        }
        return puVar3;
      }
      if (uVar5 < (*puVar4 & 0xffffff)) {
        uVar5 = *puVar4 & 0xffffff;
        puVar2 = puVar4;
      }
    }
    puVar3 = puVar2;
    if (param_2 == 0) {
      if ((long)((ulong)*(byte *)((int)puVar4 + 3) << 0x3e) < 0) goto LAB_0037a7b8;
      puVar4 = (uint *)puVar4[2];
    }
    else {
      if (puVar4[1] == 0xffffffff) goto LAB_0037a7b8;
      puVar4 = (uint *)puVar4[1];
    }
  } while( true );
}

/* ---- 0x0037a940 size 0x1bc  Sdrv::FreeSoundMemory(Pv)
 *      mangled: FreeSoundMemory__4SdrvFPv */
void FreeSoundMemory__4SdrvFPv(int param_1,int param_2)

{
  uint *puVar1;
  uint *puVar2;
  uint unaff_s1_lo;
  int iVar3;
  long lVar4;
  
  puVar1 = (uint *)(param_2 - (uint)*(byte *)(param_2 + -1));
  for (puVar2 = *(uint **)(param_1 + 0x1c); puVar2 != puVar1; puVar2 = (uint *)puVar2[2]) {
    if ((long)((ulong)*(byte *)((int)puVar2 + 3) << 0x3e) < 0) {
      return;
    }
  }
  if ((long)((ulong)*(byte *)((int)puVar2 + 3) << 0x3e) < 0) {
    lVar4 = (long)(*(int *)(param_1 + 0x20) - ((int)puVar1 - *(int *)(param_1 + 0x1c)));
  }
  else {
    iVar3 = puVar2[2] - (int)puVar1;
    unaff_s1_lo = puVar2[2];
    while (lVar4 = (long)iVar3, (*(byte *)(unaff_s1_lo + 3) & 1) == 0) {
      if ((long)((ulong)*(byte *)(unaff_s1_lo + 3) << 0x3e) < 0) {
        lVar4 = (long)(int)(iVar3 + (*(int *)(param_1 + 0x20) -
                                    (unaff_s1_lo - *(int *)(param_1 + 0x1c))));
        *(byte *)((int)puVar2 + 3) = *(byte *)((int)puVar2 + 3) & 0xfd | 2;
        break;
      }
      iVar3 = iVar3 + (*(uint *)(unaff_s1_lo + 8) - unaff_s1_lo);
      unaff_s1_lo = *(uint *)(unaff_s1_lo + 8);
    }
  }
  if ((long)((ulong)*(byte *)((int)puVar2 + 3) << 0x3e) < 0) {
    puVar2[2] = 0;
  }
  else {
    puVar2[2] = unaff_s1_lo;
    *(uint **)(unaff_s1_lo + 4) = puVar2;
  }
  *(byte *)((int)puVar2 + 3) = *(byte *)((int)puVar2 + 3) & 0xfe;
  *puVar2 = *puVar2 & 0xff000000 | (uint)((ulong)(lVar4 << 0x28) >> 0x28);
  return;
}

/* ---- 0x0037ab00 size 0x234  Sdrv::ResizeSoundMemory(PvUi)
 *      mangled: ResizeSoundMemory__4SdrvFPvUi */
u32 ResizeSoundMemory__4SdrvFPvUi(int param_1,int param_2,int param_3)

{
  uint *puVar1;
  uint *__s;
  uint uVar2;
  uint uVar3;
  
  puVar1 = *(uint **)(param_1 + 0x1c);
  while( true ) {
    if (puVar1 == (uint *)0x0) {
      return 0;
    }
    if (puVar1 == (uint *)(param_2 - (uint)*(byte *)(param_2 + -1))) break;
    puVar1 = (uint *)puVar1[2];
  }
  if ((*puVar1 & 0x1000000) == 0) {
    return 0;
  }
  if ((long)((ulong)*(byte *)((int)puVar1 + 3) << 0x3e) < 0) {
    uVar3 = *(int *)(param_1 + 0x20) - (param_2 - *(int *)(param_1 + 0x1c));
  }
  else {
    uVar3 = puVar1[2] - param_2;
  }
  uVar2 = param_3 + 0xfU & 0xfffffff0;
  if (uVar3 < uVar2) {
    return 0;
  }
  if (uVar3 == uVar2) {
    return 1;
  }
  *puVar1 = *puVar1 & 0xff000000 | (uint)((ulong)((long)param_3 << 0x28) >> 0x28);
  if (0xf < uVar3 - uVar2) {
    __s = (uint *)(param_2 + uVar2);
    memset(__s,0,0x10);
    *__s = *__s & 0xff000000 | (uint)((ulong)((long)(int)((uVar3 - uVar2) - 0x10) << 0x28) >> 0x28);
    __s[1] = (uint)puVar1;
    if ((long)((ulong)*(byte *)((int)puVar1 + 3) << 0x3e) < 0) {
      *(byte *)((int)__s + 3) = *(byte *)((int)__s + 3) & 0xfd | 2;
      *(byte *)((int)puVar1 + 3) = *(byte *)((int)puVar1 + 3) & 0xfd;
    }
    else {
      uVar3 = puVar1[2];
      *(uint **)(uVar3 + 4) = __s;
      __s[2] = uVar3;
    }
    puVar1[2] = (uint)__s;
  }
  return 1;
}

