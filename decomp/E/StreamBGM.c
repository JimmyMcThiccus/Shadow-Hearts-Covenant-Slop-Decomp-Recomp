/*
 * StreamBGM.c -- Ghidra decompiler output (SLPM_602.19, JP Furokuban), tidied by tools/E_gen_decomp.py
 * 15 functions. Types: u8/u16/u32/u64 = undefined1/2/4/8. Addresses in comments are JP main-exe addresses.
 */

/* ---- 0x003cdfe0 size 0x60  StreamBGM::StreamBGM(v)
 *      mangled: __ct__9StreamBGMFv */
int __ct__9StreamBGMFv(int param_1)

{
  __ct__7CPolObjFv(param_1);
  *(u8 **)(param_1 + 0x14) = __vt__9StreamBGM;
  memset((void *)(param_1 + 0x18),0,100);
  *(u8 *)(param_1 + 0x78) = 0x3f;
  return param_1;
}

/* ---- 0x003ce040 size 0x34  StreamBGM::Create(PCc)
 *      mangled: Create__9StreamBGMFPCc */
char * Create__9StreamBGMFPCc(int param_1,char *param_2)

{
  char *pcVar1;
  
  pcVar1 = strcpy((char *)(param_1 + 0x7c),param_2);
  return pcVar1;
}

/* ---- 0x003ce080 size 0x8c  StreamBGM::Release(v)
 *      mangled: Release__9StreamBGMFv */
void Release__9StreamBGMFv(int param_1)

{
  int iVar1;
  
  if (*(int *)(param_1 + 0x38) != 0) {
    iVar1 = *(int *)(param_1 + 0x38);
    if (iVar1 != 0) {
      (**(code **)(*(int *)(iVar1 + 0x28) + 8))(iVar1,1);
    }
    *(u32 *)(param_1 + 0x38) = 0;
  }
  if (*(int *)(param_1 + 0x3c) != 0) {
    __dla__FPv(*(u32 *)(param_1 + 0x3c));
    *(u32 *)(param_1 + 0x3c) = 0;
  }
  return;
}

/* ---- 0x003ce110 size 0xbc  StreamBGM::Delete(v)
 *      mangled: Delete__9StreamBGMFv */
void Delete__9StreamBGMFv(int param_1)

{
  long lVar1;
  
  lVar1 = isPlay__9StreamBGMFv(param_1);
  if (lVar1 == 0) {
    Dispose__9StreamBGMFv(param_1);
    if (param_1 != 0) {
      (**(code **)(*(int *)(param_1 + 0x14) + 8))(param_1,1);
    }
  }
  else {
    *(byte *)(param_1 + 0x76) = *(byte *)(param_1 + 0x76) & 0xfb | 4;
    *(byte *)(param_1 + 0x76) = *(byte *)(param_1 + 0x76) & 0xfd | 2;
  }
  return;
}

/* ---- 0x003ce1d0 size 0x7c  StreamBGM::~StreamBGM(v)
 *      mangled: __dt__9StreamBGMFv */
int __dt__9StreamBGMFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(u8 **)(param_1 + 0x14) = __vt__9StreamBGM;
    Release__9StreamBGMFv(param_1);
    __dt__7CPolObjFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* ---- 0x003ce250 size 0x28  StreamBGM::isPlay(v)
 *      mangled: isPlay__9StreamBGMFv */
bool isPlay__9StreamBGMFv(int param_1)

{
  return *(char *)(param_1 + 0x72) != '\0';
}

/* ---- 0x003ce280 size 0x2c  StreamBGM::isReady(v)
 *      mangled: isReady__9StreamBGMFv */
bool isReady__9StreamBGMFv(int param_1)

{
  return *(char *)(param_1 + 0x72) == ' ';
}

/* ---- 0x003ce2b0 size 0xe8  StreamBGM::Play(v)
 *      mangled: Play__9StreamBGMFv */
void Play__9StreamBGMFv(int param_1)

{
  long lVar1;
  
  lVar1 = isPlay__9StreamBGMFv(param_1);
  if (lVar1 == 0) {
    *(byte *)(param_1 + 0x76) = *(byte *)(param_1 + 0x76) & 0xfd;
    *(u8 *)(param_1 + 0x72) = 0x10;
    Entry__9StreamBGMFv(param_1);
  }
  else if (((long)((ulong)*(byte *)(param_1 + 0x77) << 0x3c) < 0) &&
          (*(byte *)(param_1 + 0x77) = *(byte *)(param_1 + 0x77) & 0xf7,
          *(char *)(param_1 + 0x72) == ' ')) {
    StreamStart__4SdrvFUiUi(sys__4Sdrv,*(u32 *)(param_1 + 0x44),0);
    *(u8 *)(param_1 + 0x72) = 0x30;
  }
  return;
}

/* ---- 0x003ce3a0 size 0x4c  StreamBGM::Preload(v)
 *      mangled: Preload__9StreamBGMFv */
void Preload__9StreamBGMFv(int param_1)

{
  Play__9StreamBGMFv(param_1);
  *(byte *)(param_1 + 0x77) = *(byte *)(param_1 + 0x77) & 0xf7 | 8;
  return;
}

/* ---- 0x003ce3f0 size 0x118  StreamBGM::Stop(ib)
 *      mangled: Stop__9StreamBGMFib */
void Stop__9StreamBGMFib(int param_1,int param_2,char param_3)

{
  long lVar1;
  
  lVar1 = isPlay__9StreamBGMFv(param_1);
  if (lVar1 == 0) {
    if (param_3 != '\0') {
      Delete__9StreamBGMFv(param_1);
    }
  }
  else {
    if (param_3 != '\0') {
      *(byte *)(param_1 + 0x76) = *(byte *)(param_1 + 0x76) & 0xf7 | 8;
    }
    if (param_2 < 1) {
      *(byte *)(param_1 + 0x76) = *(byte *)(param_1 + 0x76) & 0xfd | 2;
    }
    else {
      *(int *)(param_1 + 0x5c) = param_2;
      *(u8 *)(param_1 + 0x79) = *(u8 *)(param_1 + 0x78);
      *(u8 *)(param_1 + 0x7a) = 0;
      *(u32 *)(param_1 + 0x60) = 0;
      *(byte *)(param_1 + 0x76) = *(byte *)(param_1 + 0x76) & 0x9f | 0x40;
    }
  }
  return;
}

/* ---- 0x003ce510 size 0x4c  StreamBGM::SetVolume(i)
 *      mangled: SetVolume__9StreamBGMFi */
void SetVolume__9StreamBGMFi(int param_1,u8 param_2)

{
  *(u8 *)(param_1 + 0x78) = param_2;
  *(byte *)(param_1 + 0x76) = *(byte *)(param_1 + 0x76) & 0x7f | 0x80;
  return;
}

/* ---- 0x003ce560 size 0x78  StreamBGM::Entry(v)
 *      mangled: Entry__9StreamBGMFv */
void Entry__9StreamBGMFv(int param_1)

{
  if (-1 < (long)((ulong)*(byte *)(param_1 + 0x76) << 0x3b)) {
    *(byte *)(param_1 + 0x76) = *(byte *)(param_1 + 0x76) & 0xef | 0x10;
    Entry__7CPollerFP7CPolObjib(app__4CApp + 0x48,param_1,0x80,0);
  }
  return;
}

/* ---- 0x003ce5e0 size 0x68  StreamBGM::Dispose(v)
 *      mangled: Dispose__9StreamBGMFv */
void Dispose__9StreamBGMFv(int param_1)

{
  if ((long)((ulong)*(byte *)(param_1 + 0x76) << 0x3b) < 0) {
    *(byte *)(param_1 + 0x76) = *(byte *)(param_1 + 0x76) & 0xef;
    Dispose__7CPollerFP7CPolObj(app__4CApp + 0x48,param_1);
  }
  return;
}

/* ---- 0x003ce650 size 0x448  StreamBGM::Polling(v)
 *      mangled: Polling__9StreamBGMFv */
u32 Polling__9StreamBGMFv(int param_1)

{
  bool bVar1;
  u32 uVar2;
  long lVar3;
  uint uVar4;
  float fStack_14;
  
  PollingStream__9StreamBGMFv(param_1);
  if (((ulong)*(byte *)(param_1 + 0x76) & 0x7f) >> 5 != 0) {
    *(int *)(param_1 + 0x60) = *(int *)(param_1 + 0x60) + *(int *)(sys__6SSHSys + 0x20);
    fStack_14 = (float)*(uint *)(param_1 + 0x60) / (float)*(uint *)(param_1 + 0x5c);
    bVar1 = 1.0 <= fStack_14;
    if (bVar1) {
      fStack_14 = 1.0;
    }
    uVar4 = (uint)((float)*(byte *)(param_1 + 0x79) +
                  fStack_14 *
                  (float)(int)((uint)*(byte *)(param_1 + 0x7a) - (uint)*(byte *)(param_1 + 0x79)));
    if (uVar4 != *(byte *)(param_1 + 0x78)) {
      *(char *)(param_1 + 0x78) = (char)uVar4;
      *(byte *)(param_1 + 0x76) = *(byte *)(param_1 + 0x76) & 0x7f | 0x80;
    }
    if (bVar1) {
      if ((((ulong)*(byte *)(param_1 + 0x76) & 0x7f) >> 5 == 2) &&
         (*(byte *)(param_1 + 0x76) = *(byte *)(param_1 + 0x76) & 0xfd | 2,
         (long)((ulong)*(byte *)(param_1 + 0x76) << 0x3c) < 0)) {
        *(byte *)(param_1 + 0x76) = *(byte *)(param_1 + 0x76) & 0xfb | 4;
      }
      *(byte *)(param_1 + 0x76) = *(byte *)(param_1 + 0x76) & 0x9f;
    }
  }
  lVar3 = isPlay__9StreamBGMFv(param_1);
  if ((lVar3 != 0) && ((long)((ulong)*(byte *)(param_1 + 0x76) << 0x38) < 0)) {
    if (*(char *)(param_1 + 0x73) == '\x01') {
      uVar2 = *(u32 *)(param_1 + 0x58);
      lVar3 = GetStatus__4SdrvFUi(sys__4Sdrv,uVar2);
      if (lVar3 == 3) {
        CloseHandle__4SdrvFUi(sys__4Sdrv,uVar2);
        *(u8 *)(param_1 + 0x73) = 0;
        *(byte *)(param_1 + 0x76) = *(byte *)(param_1 + 0x76) & 0x7f;
      }
    }
    else if ((*(char *)(param_1 + 0x73) == '\0') &&
            (uVar4 = (*(byte *)(param_1 + 0x78) + 1) * 0x80 - 1,
            lVar3 = StreamSetParam__4SdrvFUiUiUi
                              (sys__4Sdrv,*(u32 *)(param_1 + 0x44),uVar4 * 0x10000 | uVar4,
                               0x1000), lVar3 != -1)) {
      *(int *)(param_1 + 0x58) = (int)lVar3;
      *(char *)(param_1 + 0x73) = *(char *)(param_1 + 0x73) + '\x01';
    }
  }
  if (((long)((ulong)*(byte *)(param_1 + 0x76) << 0x3d) < 0) &&
     (lVar3 = isPlay__9StreamBGMFv(param_1), lVar3 == 0)) {
    *(u8 *)(param_1 + 0xc) = 1;
    *(u8 *)(param_1 + 0xe) = 0;
    uVar2 = 1;
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

/* ---- 0x003ceaa0 size 0xb8c  StreamBGM::PollingStream(v)
 *      mangled: PollingStream__9StreamBGMFv */
void PollingStream__9StreamBGMFv(int param_1)

{
  char cVar1;
  bool bVar2;
  u32 uVar3;
  int iVar4;
  int iVar5;
  long lVar6;
  uint uVar7;
  void *__s1;
  uint uVar8;
  int iVar9;
  int iStack_50;
  uint uStack_44;
  uint uStack_3c;
  uint uStack_30;
  u32 uStack_2c;
  u32 uStack_28;
  uint uStack_24;
  uint uStack_1c;
  uint uStack_18;
  uint uStack_14;
  int iStack_10;
  
  iVar4 = *(int *)(param_1 + 0x38);
  iStack_10 = param_1;
  if (((long)((ulong)*(byte *)(param_1 + 0x76) << 0x3e) < 0) &&
     ((uStack_14 = *(byte *)(param_1 + 0x72) & 0xf0, uStack_14 == 0x30 || (uStack_14 == 0x20)))) {
    StreamStop__4SdrvFUiUi(sys__4Sdrv,*(u32 *)(param_1 + 0x44),1);
    stopStream__10StreamFileFv(iVar4);
    *(u8 *)(iStack_10 + 0x72) = 0x40;
  }
  while( true ) {
    iVar9 = iStack_10;
    cVar1 = *(char *)(iStack_10 + 0x72);
    if (cVar1 == '@') {
      iVar4 = StreamGetStat__4SdrvFUiUi(sys__4Sdrv,*(u32 *)(iStack_10 + 0x44),0);
      if (iVar4 != -1) {
        iVar9 = GetOption__4SdrvFUi(sys__4Sdrv,iVar4);
        CloseHandle__4SdrvFUi(sys__4Sdrv,iVar4);
        if (iVar9 == 3) {
          *(byte *)(iStack_10 + 0x74) = *(byte *)(iStack_10 + 0x74) | 1;
          StreamClose__4SdrvFUi(sys__4Sdrv,*(u32 *)(iStack_10 + 0x44));
          *(u32 *)(iStack_10 + 0x44) = 0;
          *(u8 *)(iStack_10 + 0x72) = 0;
          if (*(char *)(iStack_10 + 0x75) == '\x01') {
            SetMode__4SdrvFi(sys__4Sdrv,0x2000);
          }
          *(u32 *)(iStack_10 + 0x4c) = 0;
          Release__9StreamBGMFv(iStack_10);
        }
      }
      return;
    }
    if (cVar1 != '1') {
      if (cVar1 != '0') {
        if (cVar1 == '\x14') {
          uStack_28 = *(u32 *)(iStack_10 + 0x54);
          lVar6 = GetStatus__4SdrvFUi(sys__4Sdrv,uStack_28);
          if (lVar6 != 3) {
            return;
          }
          CloseHandle__4SdrvFUi(sys__4Sdrv,uStack_28);
          StreamSetBuf__4SdrvFUiPvUi
                    (sys__4Sdrv,*(u32 *)(iStack_10 + 0x44),*(u32 *)(iStack_10 + 0x3c),
                     0x10000);
          if (-1 < (long)((ulong)*(byte *)(iStack_10 + 0x77) << 0x3c)) {
            StreamStart__4SdrvFUiUi(sys__4Sdrv,*(u32 *)(iStack_10 + 0x44),1);
          }
          *(u8 *)(iStack_10 + 0x72) = 0x30;
          return;
        }
        if (cVar1 == '\x13') {
          uVar3 = *(u32 *)(iStack_10 + 0x54);
          lVar6 = GetStatus__4SdrvFUi(sys__4Sdrv,uVar3);
          if (lVar6 != 3) {
            return;
          }
          CloseHandle__4SdrvFUi(sys__4Sdrv,uVar3);
          uStack_24 = (*(byte *)(iStack_10 + 0x78) + 1) * 0x80 - 1;
          uStack_24 = uStack_24 * 0x10000 | uStack_24;
          lVar6 = StreamSetParam__4SdrvFUiUiUi
                            (sys__4Sdrv,*(u32 *)(iStack_10 + 0x44),uStack_24,0x1000);
          if (lVar6 == -1) {
            return;
          }
          *(int *)(iStack_10 + 0x54) = (int)lVar6;
          *(char *)(iStack_10 + 0x72) = *(char *)(iStack_10 + 0x72) + '\x01';
          return;
        }
        if (cVar1 != '\x12') {
          if (cVar1 != '\x11') {
            if (cVar1 != '\x10') {
              return;
            }
            loopCt = 0;
            if (*(int *)(iStack_10 + 0x3c) == 0) {
              uVar3 = __nwa__FUi(0x10000);
              *(u32 *)(iStack_10 + 0x3c) = uVar3;
            }
            if (iVar4 == 0) {
              lVar6 = __nw__FUi(0x138);
              iVar4 = 0;
              if (lVar6 != 0) {
                iVar4 = __ct__10StreamFileFPcUlUi(lVar6,iStack_10 + 0x7c,0x80000,0x2000);
              }
              *(int *)(iStack_10 + 0x38) = iVar4;
            }
            startStream__10StreamFileFv(iVar4);
            iVar9 = 0;
            if (iVar4 != 0) {
              iVar9 = iVar4 + 0x2c;
            }
            Entry__7CPollerFP7CPolObjib(ourFio__9FileIOLib + 0x1395c,iVar9,0x80,0);
            *(char *)(iStack_10 + 0x72) = *(char *)(iStack_10 + 0x72) + '\x01';
            return;
          }
          __s1 = (void *)(iStack_10 + 0x18);
          uStack_18 = getBufferSerialSize__10RingBufferFli(iVar4,0x20,0);
          if (uStack_18 < 0x20) {
            return;
          }
          getReadData__10RingBufferFPvUlUl(iVar4,__s1,uStack_18,0);
          iVar5 = memcmp(__s1,&_1844,2);
          if (iVar5 == 0) {
            *(uint *)(iStack_10 + 0x4c) = uStack_18;
            *(u16 *)(iStack_10 + 0x6c) = 0x8000;
            *(u16 *)(iStack_10 + 0x6e) = 0;
            iVar5 = (*(uint *)(iVar9 + 0x28) >> 0xc) * (uint)*(byte *)(iVar9 + 0x21) * 0x200;
            uStack_1c = *(uint *)(iVar9 + 0x28) & 0xfff;
            if (((ulong)*(byte *)(iVar9 + 0x20) & 0xf) >> 2 == 2) {
              iVar5 = iVar5 * 2;
            }
            uVar8 = iVar5 + (uint)*(ushort *)(iVar9 + 0x1a) * 0x10;
            *(byte *)(iStack_10 + 0x76) =
                 *(byte *)(iStack_10 + 0x76) & 0xfe |
                 (byte)(((ulong)*(byte *)(iVar9 + 0x20) << 0x3c) >> 0x3e) & 1;
            *(uint *)(iStack_10 + 0x50) = uVar8;
            *(ushort *)(iStack_10 + 0x70) = (ushort)uStack_1c | 0x8000;
            clearBlock__10RingBufferFl(iVar4,uStack_18);
            *(u32 *)(iVar4 + 0x50) = 1;
            *(uint *)(iVar4 + 0x54) = uVar8 & 0xfffff800;
          }
          else {
            *(u8 *)(iStack_10 + 0x75) = 1;
          }
          *(char *)(iStack_10 + 0x72) = *(char *)(iStack_10 + 0x72) + '\x01';
        }
        if (*(char *)(iStack_10 + 0x75) == '\x01') {
          SetMode__4SdrvFi(sys__4Sdrv,0x2010);
        }
        uVar3 = StreamOpen__4SdrvFUi(sys__4Sdrv,*(u8 *)(iStack_10 + 0x75));
        *(u32 *)(iStack_10 + 0x44) = uVar3;
        iVar4 = StreamCreate__4SdrvFUiUiUi
                          (sys__4Sdrv,*(u32 *)(iStack_10 + 0x44),
                           ((ulong)*(byte *)(iStack_10 + 0x20) & 0xf) >> 2,2);
        if (iVar4 == -1) {
          return;
        }
        *(int *)(iStack_10 + 0x54) = iVar4;
        *(char *)(iStack_10 + 0x72) = *(char *)(iStack_10 + 0x72) + '\x01';
        return;
      }
      uStack_30 = StreamGetWriteInfo__4SdrvFUiRPUc
                            (sys__4Sdrv,*(u32 *)(iStack_10 + 0x44),&uStack_2c);
      if (uStack_30 == 0) {
        return;
      }
      if (0xffff < uStack_30) {
        uStack_30 = 0x10000;
      }
      *(uint *)(iStack_10 + 0x48) = uStack_30;
      *(u32 *)(iStack_10 + 0x40) = uStack_2c;
      *(char *)(iStack_10 + 0x72) = *(char *)(iStack_10 + 0x72) + '\x01';
    }
    if ((*(byte *)(iStack_10 + 0x77) & 1) != 0) {
      if ((((ulong)*(byte *)(iStack_10 + 0x77) & 7) >> 1 == 0) && (*(int *)(iVar4 + 0x10) < 0x8000))
      {
        *(byte *)(iStack_10 + 0x77) =
             *(byte *)(iStack_10 + 0x77) & 0xf9 |
             (byte)(((uint)(((ulong)*(byte *)(iStack_10 + 0x77) << 0x3d) >> 0x3e) | 2) << 1);
        StreamPause__4SdrvFUiUi(sys__4Sdrv,*(u32 *)(iStack_10 + 0x44),0);
      }
      else if ((((ulong)*(byte *)(iStack_10 + 0x77) & 7) >> 1 != 0) &&
              ((0x1ffff < *(int *)(iVar4 + 0x10) &&
               (*(byte *)(iStack_10 + 0x77) =
                     *(byte *)(iStack_10 + 0x77) & 0xf9 |
                     (byte)(((uint)(((ulong)*(byte *)(iStack_10 + 0x77) << 0x3d) >> 0x3e) & 1) << 1)
               , ((ulong)*(byte *)(iStack_10 + 0x77) & 7) >> 1 == 0)))) {
        StreamPause__4SdrvFUiUi(sys__4Sdrv,*(u32 *)(iStack_10 + 0x44),1);
      }
      if (((ulong)*(byte *)(iStack_10 + 0x77) & 7) >> 1 != 0) {
        return;
      }
    }
    iVar9 = (uint)*(ushort *)(iStack_10 + 0x6e) + *(int *)(iStack_10 + 0x48);
    iStack_50 = iVar9;
    if ((*(byte *)(iStack_10 + 0x77) & 1) == 0) {
      iStack_50 = 0x20000;
    }
    iVar5 = getBufferSerialSize__10RingBufferFli(iVar4,iStack_50,0);
    if (iVar5 < iStack_50) {
      return;
    }
    getReadData__10RingBufferFPvUlUl
              (iVar4,*(u32 *)(iStack_10 + 0x40),*(u32 *)(iStack_10 + 0x48),
               *(u16 *)(iStack_10 + 0x6e));
    clearBlock__10RingBufferFl(iVar4,iVar9);
    uStack_3c = 0;
    bVar2 = false;
    uVar8 = (uint)*(ushort *)(iStack_10 + 0x6c);
    *(u16 *)(iStack_10 + 0x6e) = 0;
    *(u16 *)(iStack_10 + 0x6c) = 0x8000;
    if (*(char *)(iStack_10 + 0x75) == '\0') {
      uStack_44 = (*(int *)(iStack_10 + 0x4c) + iVar9) - 0x20;
      if (((ulong)*(byte *)(iStack_10 + 0x20) & 0xf) >> 2 == 2) {
        uStack_44 = (int)uStack_44 >> 1;
      }
      bVar2 = *(uint *)(iStack_10 + 0x24) <= uStack_44;
      if (*(uint *)(iStack_10 + 0x24) < uStack_44) {
        uStack_3c = (uint)(((ulong)*(byte *)(iStack_10 + 0x20) << 0x3b) >> 0x3f);
        uVar7 = *(uint *)(iStack_10 + 0x24) & 0x7f0;
        uVar8 = uVar7 << 4;
        if (uVar7 == 0) {
          uVar8 = 0x8000;
        }
      }
    }
    StreamWriteData__4SdrvFUiUiUi
              (sys__4Sdrv,*(u32 *)(iStack_10 + 0x44),*(u32 *)(iStack_10 + 0x48),uVar8)
    ;
    *(int *)(iStack_10 + 0x4c) = *(int *)(iStack_10 + 0x4c) + iVar9;
    *(u8 *)(iStack_10 + 0x72) = 0x30;
    *(int *)(iStack_10 + 0x68) = *(int *)(iStack_10 + 0x68) + iVar9;
    if (((long)((ulong)*(byte *)(iStack_10 + 0x77) << 0x3c) < 0) &&
       (0x1fff < *(uint *)(iStack_10 + 0x68))) break;
    *(byte *)(iStack_10 + 0x77) = *(byte *)(iStack_10 + 0x77) & 0xfe | 1;
    if (uStack_3c == 0) {
      if (bVar2) {
        StreamStop__4SdrvFUiUi(sys__4Sdrv,*(u32 *)(iStack_10 + 0x44),2);
        stopStream__10StreamFileFv(iVar4);
        *(u8 *)(iStack_10 + 0x72) = 0x40;
      }
    }
    else {
      *(uint *)(iStack_10 + 0x4c) = *(uint *)(iStack_10 + 0x50) & 0xfffff800;
      *(u16 *)(iStack_10 + 0x6c) = *(u16 *)(iStack_10 + 0x70);
      *(ushort *)(iStack_10 + 0x6e) = (ushort)*(u32 *)(iStack_10 + 0x50) & 0x7ff;
    }
  }
  *(u8 *)(iStack_10 + 0x72) = 0x20;
  return;
}

