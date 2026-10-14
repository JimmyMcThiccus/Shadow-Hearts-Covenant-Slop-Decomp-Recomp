/*
 * BGMServerHandler.c -- Ghidra decompiler output (SLPM_602.19, JP Furokuban), tidied by tools/E_gen_decomp.py
 * 9 functions. Types: u8/u16/u32/u64 = undefined1/2/4/8. Addresses in comments are JP main-exe addresses.
 */

/* ---- 0x003897b0 size 0x80  BGMServerHandler::~BGMServerHandler(v)
 *      mangled: __dt__16BGMServerHandlerFv */
long __dt__16BGMServerHandlerFv(long param_1,short param_2)

{
  int iVar1;
  
  if (param_1 != 0) {
    iVar1 = (int)param_1;
    *(u8 **)(iVar1 + 0x10) = __vt__16BGMServerHandler;
    *(u32 *)(iVar1 + 0x28) = 0x406fac;
    __dt__7CPolObjFv(iVar1 + 0x14,0);
    __dt__16LSDDeviceHandlerFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* ---- 0x00389830 size 0x48  BGMServerHandler::CheckData(P12_LSDTrackHdr)
 *      mangled: CheckData__16BGMServerHandlerFP12_LSDTrackHdr */
u32 CheckData__16BGMServerHandlerFP12_LSDTrackHdr(int param_1,int *param_2)

{
  u32 uVar1;
  
  uVar1 = 1;
  if (*param_2 != 0x534d4350) {
    uVar1 = 1;
    if (*param_2 == 0x59424c44) {
      *(u8 *)(param_1 + 0x30) = 1;
    }
    else {
      uVar1 = 0;
    }
  }
  return uVar1;
}

/* ---- 0x00389880 size 0x214  BGMServerHandler::Open(P10RingBuffer)
 *      mangled: Open__16BGMServerHandlerFP10RingBuffer */
int Open__16BGMServerHandlerFP10RingBuffer(int param_1,u64 param_2)

{
  char cVar1;
  u32 uVar2;
  long lVar3;
  float fVar4;
  uint uVar5;
  
  *(u32 *)(param_1 + 0x84) = 1;
  *(u32 *)(param_1 + 0x88) = 1;
  *(u32 *)(param_1 + 0x8c) = 1;
  uVar2 = CreateSema(param_1 + 0x84);
  *(u32 *)(param_1 + 0x9c) = uVar2;
  *(int *)(param_1 + 0x3c) = param_1;
  *(int *)(param_1 + 0x40) = param_1;
  *(byte *)(param_1 + 0xb8) = *(byte *)(param_1 + 0xb8) & 0xf8;
  getReadData__10RingBufferFPvUlUl(param_2,param_1 + 0x44,0x40,0);
  if (*(char *)(param_1 + 0x30) == '\0') {
    if ((*(byte *)(param_1 + 100) & 0xf) == 0) {
      *(u8 *)(param_1 + 0x30) = 2;
    }
    else {
      *(u8 *)(param_1 + 0x30) = 3;
    }
  }
  *(u32 *)(param_1 + 0xa4) = 0;
  cVar1 = *(char *)(param_1 + 0x30);
  if (cVar1 == '\x02') {
    *(u32 *)(param_1 + 0x34) = 0x534d4350;
  }
  else if (cVar1 == '\x01') {
    *(u32 *)(param_1 + 0x34) = 0x59424c44;
  }
  else if (cVar1 == '\x03') {
    *(u32 *)(param_1 + 0x34) = 0x534d4350;
  }
  lVar3 = __nw__FUi(0x2c);
  uVar2 = 0;
  if (lVar3 != 0) {
    uVar2 = __ct__10RingBufferFUlUi
                      (lVar3,(uint)*(ushort *)(param_1 + 0x58) * *(int *)(param_1 + 0x5c) * 0x10,0);
  }
  *(u32 *)(param_1 + 0x2c) = uVar2;
  uVar2 = StreamOpen__4SdrvFUi(sys__4Sdrv,0);
  *(u32 *)(param_1 + 0xa8) = uVar2;
  StreamAllocBuf__4SdrvFUiUi(sys__4Sdrv,*(u32 *)(param_1 + 0xa8),0x20000);
  uVar2 = StreamCreate__4SdrvFUiUiUi(sys__4Sdrv,*(u32 *)(param_1 + 0xa8),2,2);
  *(u32 *)(param_1 + 0xac) = uVar2;
  fVar4 = ((float)*(ushort *)(param_1 + 0x6a) / 48000.0) * 4096.0;
  if (fVar4 < 2.1474836e+09) {
    uVar5 = (uint)fVar4;
  }
  else {
    uVar5 = (int)(fVar4 - 2.1474836e+09) | 0x80000000;
  }
  uVar2 = StreamSetParam__4SdrvFUiUiUi(sys__4Sdrv,*(u32 *)(param_1 + 0xa8),0x3fff3fff,uVar5);
  *(u32 *)(param_1 + 0xb0) = uVar2;
  return param_1 + 0x34;
}

/* ---- 0x00389aa0 size 0xf4  BGMServerHandler::Read(P10_LSDHANDLEP10RingBuffer)
 *      mangled: Read__16BGMServerHandlerFP10_LSDHANDLEP10RingBuffer */
int Read__16BGMServerHandlerFP10_LSDHANDLEP10RingBuffer
              (int param_1,u64 param_2,u64 param_3)

{
  long lVar1;
  u64 uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  
  WaitSema(*(u32 *)(param_1 + 0x9c));
  iVar3 = 0;
  if (((int *)param_3)[4] == 0) {
    iVar4 = 0;
  }
  else {
    iVar4 = *(int *)param_3;
  }
  uVar5 = *(int *)(iVar4 + 8) << 4;
  lVar1 = getEmptySize__10RingBufferFv(*(u32 *)(param_1 + 0x2c));
  if ((long)(ulong)uVar5 <= lVar1) {
    uVar2 = __nwa__FUi(uVar5);
    getReadData__10RingBufferFPvUlUl(param_3,uVar2,*(int *)(iVar4 + 8) << 4,0x10);
    writeData__10RingBufferFPUclUi(*(u32 *)(param_1 + 0x2c),uVar2,*(int *)(iVar4 + 8) << 4,0)
    ;
    iVar3 = *(int *)(iVar4 + 8) * 0x10 + 0x10;
    __dla__FPv(uVar2);
  }
  SignalSema(*(u32 *)(param_1 + 0x9c));
  return iVar3;
}

/* ---- 0x00389ba0 size 0x148  BGMServerHandler::Event(P10_LSDHANDLEiff)
 *      mangled: Event__16BGMServerHandlerFP10_LSDHANDLEiff */
void Event__16BGMServerHandlerFP10_LSDHANDLEiff
               (float param_1,int param_2,u64 param_3,long param_4)

{
  int iVar1;
  
  WaitSema(*(u32 *)(param_2 + 0x9c));
  if (param_4 == 1) {
    *(u8 *)(param_2 + 0x31) = 1;
    iVar1 = param_2;
    if (param_2 != 0) {
      iVar1 = param_2 + 0x14;
    }
    Entry__7CPollerFP7CPolObjib(ourFio__9FileIOLib + 0x1395c,iVar1,0x80,0);
  }
  else if (param_4 == 4) {
    if (param_1 == 0.0) {
      StreamStop__4SdrvFUiUi(sys__4Sdrv,*(u32 *)(param_2 + 0xa8));
    }
    else {
      StreamStop__4SdrvFUiUi(sys__4Sdrv,*(u32 *)(param_2 + 0xa8),2);
    }
  }
  else if ((param_4 == 5) && (*(char *)(param_2 + 0x32) == '\0')) {
    StreamPause__4SdrvFUiUi(sys__4Sdrv,*(u32 *)(param_2 + 0xa8),0);
    *(u8 *)(param_2 + 0x32) = 1;
  }
  else if ((param_4 == 6) && (*(char *)(param_2 + 0x32) != '\0')) {
    StreamPause__4SdrvFUiUi(sys__4Sdrv,*(u32 *)(param_2 + 0xa8),1);
    *(u8 *)(param_2 + 0x32) = 0;
  }
  SignalSema(*(u32 *)(param_2 + 0x9c));
  return;
}

/* ---- 0x00389cf0 size 0x138  BGMServerHandler::Close(P10_LSDHANDLE)
 *      mangled: Close__16BGMServerHandlerFP10_LSDHANDLE */
u32 Close__16BGMServerHandlerFP10_LSDHANDLE(int param_1)

{
  long lVar1;
  long lVar2;
  int iVar3;
  
  if (*(int *)(param_1 + 0xa4) == 0) {
    WaitSema(*(u32 *)(param_1 + 0x9c));
    iVar3 = param_1;
    if (param_1 != 0) {
      iVar3 = param_1 + 0x14;
    }
    Dispose__7CPollerFP7CPolObj(ourFio__9FileIOLib + 0x1395c,iVar3);
    SignalSema(*(u32 *)(param_1 + 0x9c));
    *(u32 *)(param_1 + 0xa4) = 1;
  }
  else if ((*(int *)(param_1 + 0xa4) == 1) &&
          (lVar1 = StreamGetStat__4SdrvFUiUi(sys__4Sdrv,*(u32 *)(param_1 + 0xa8),0),
          lVar1 != -1)) {
    lVar2 = GetOption__4SdrvFUi(sys__4Sdrv,lVar1);
    CloseHandle__4SdrvFUi(sys__4Sdrv,lVar1);
    if (lVar2 == 3) {
      StreamClose__4SdrvFUi(sys__4Sdrv,*(u32 *)(param_1 + 0xa8));
      DeleteSema(*(u32 *)(param_1 + 0x9c));
      iVar3 = *(int *)(param_1 + 0x2c);
      if (iVar3 != 0) {
        if (iVar3 != 0) {
          (**(code **)(*(int *)(iVar3 + 0x28) + 8))(iVar3,1);
        }
        *(u32 *)(param_1 + 0x2c) = 0;
      }
      *(u32 *)(param_1 + 0xa0) = 0;
      *(u32 *)(param_1 + 0xa4) = 0;
      *(u8 *)(param_1 + 0x32) = 0;
      *(u8 *)(param_1 + 0x31) = 0;
      return 1;
    }
  }
  return 0;
}

/* ---- 0x00389e30 size 0x258  BGMServerHandler::Polling(v)
 *      mangled: Polling__16BGMServerHandlerFv */
u64 Polling__16BGMServerHandlerFv(int param_1)

{
  int iVar1;
  long lVar2;
  ulong uVar3;
  void *__src;
  void *pvStack_4;
  
  WaitSema(*(u32 *)(param_1 + 0x9c));
  pvStack_4 = (void *)0x0;
  DIntr();
  if (((sys__4Sdrv != 0) && ((*(byte *)(param_1 + 0xb8) & 1) == 0)) &&
     (lVar2 = GetStatus__4SdrvFUi(sys__4Sdrv,*(u32 *)(param_1 + 0xac)), lVar2 == 3)) {
    CloseHandle__4SdrvFUi(sys__4Sdrv,*(u32 *)(param_1 + 0xac));
    *(byte *)(param_1 + 0xb8) = *(byte *)(param_1 + 0xb8) & 0xf8 | *(byte *)(param_1 + 0xb8) & 7 | 1
    ;
  }
  if (((sys__4Sdrv != 0) && ((*(byte *)(param_1 + 0xb8) & 2) == 0)) &&
     (lVar2 = GetStatus__4SdrvFUi(sys__4Sdrv,*(u32 *)(param_1 + 0xb0)), lVar2 == 3)) {
    CloseHandle__4SdrvFUi(sys__4Sdrv,*(u32 *)(param_1 + 0xb0));
    *(byte *)(param_1 + 0xb8) = *(byte *)(param_1 + 0xb8) & 0xf8 | *(byte *)(param_1 + 0xb8) & 7 | 2
    ;
  }
  if (((sys__4Sdrv != 0) && ((*(byte *)(param_1 + 0xb8) & 7) == 3)) &&
     (*(char *)(param_1 + 0x31) != '\0')) {
    StreamStart__4SdrvFUiUi(sys__4Sdrv,*(u32 *)(param_1 + 0xa8),1);
    *(byte *)(param_1 + 0xb8) = *(byte *)(param_1 + 0xb8) & 0xf8 | *(byte *)(param_1 + 0xb8) & 7 | 4
    ;
  }
  if ((((sys__4Sdrv != 0) && ((*(byte *)(param_1 + 0xb8) & 7) == 7)) &&
      (uVar3 = StreamGetWriteInfo__4SdrvFUiRPUc
                         (sys__4Sdrv,*(u32 *)(param_1 + 0xa8),&pvStack_4),
      *(char *)(param_1 + 0x32) == '\0')) && (uVar3 != 0)) {
    if (*(int *)(param_1 + 0xa0) != 0) {
      clearBlock__10RingBufferFl(*(u32 *)(param_1 + 0x2c),*(int *)(param_1 + 0xa0));
      SendSize_1509 = SendSize_1509 + *(int *)(param_1 + 0xa0);
      *(u32 *)(param_1 + 0xa0) = 0;
    }
    iVar1 = getBufferSerialSize__10RingBufferFli
                      (*(u32 *)(param_1 + 0x2c),uVar3 & 0xffffffff,1);
    if (iVar1 == 0x1000) {
      *(u32 *)(param_1 + 0xa0) = 0x1000;
      __src = (void *)0x0;
      if ((*(u32 **)(param_1 + 0x2c))[4] != 0) {
        __src = (void *)**(u32 **)(param_1 + 0x2c);
      }
      memcpy(pvStack_4,__src,(long)*(int *)(param_1 + 0xa0));
      StreamWriteData__4SdrvFUiUiUi
                (sys__4Sdrv,*(u32 *)(param_1 + 0xa8),*(u32 *)(param_1 + 0xa0),0x8000);
    }
  }
  EIntr();
  SignalSema(*(u32 *)(param_1 + 0x9c));
  return 0;
}

/* ---- 0x0038a090 size 0x8  BGMServerHandler::@20@Polling(v)
 *      mangled: @20@Polling__16BGMServerHandlerFv */
u64 _20_Polling__16BGMServerHandlerFv(int param_1)

{
  int iVar1;
  long lVar2;
  ulong uVar3;
  void *__src;
  void *pvStack_4;
  
  WaitSema(*(u32 *)(param_1 + 0x88));
  pvStack_4 = (void *)0x0;
  DIntr();
  if (((sys__4Sdrv != 0) && ((*(byte *)(param_1 + 0xa4) & 1) == 0)) &&
     (lVar2 = GetStatus__4SdrvFUi(sys__4Sdrv,*(u32 *)(param_1 + 0x98)), lVar2 == 3)) {
    CloseHandle__4SdrvFUi(sys__4Sdrv,*(u32 *)(param_1 + 0x98));
    *(byte *)(param_1 + 0xa4) = *(byte *)(param_1 + 0xa4) & 0xf8 | *(byte *)(param_1 + 0xa4) & 7 | 1
    ;
  }
  if (((sys__4Sdrv != 0) && ((*(byte *)(param_1 + 0xa4) & 2) == 0)) &&
     (lVar2 = GetStatus__4SdrvFUi(sys__4Sdrv,*(u32 *)(param_1 + 0x9c)), lVar2 == 3)) {
    CloseHandle__4SdrvFUi(sys__4Sdrv,*(u32 *)(param_1 + 0x9c));
    *(byte *)(param_1 + 0xa4) = *(byte *)(param_1 + 0xa4) & 0xf8 | *(byte *)(param_1 + 0xa4) & 7 | 2
    ;
  }
  if (((sys__4Sdrv != 0) && ((*(byte *)(param_1 + 0xa4) & 7) == 3)) &&
     (*(char *)(param_1 + 0x1d) != '\0')) {
    StreamStart__4SdrvFUiUi(sys__4Sdrv,*(u32 *)(param_1 + 0x94),1);
    *(byte *)(param_1 + 0xa4) = *(byte *)(param_1 + 0xa4) & 0xf8 | *(byte *)(param_1 + 0xa4) & 7 | 4
    ;
  }
  if ((((sys__4Sdrv != 0) && ((*(byte *)(param_1 + 0xa4) & 7) == 7)) &&
      (uVar3 = StreamGetWriteInfo__4SdrvFUiRPUc
                         (sys__4Sdrv,*(u32 *)(param_1 + 0x94),&pvStack_4),
      *(char *)(param_1 + 0x1e) == '\0')) && (uVar3 != 0)) {
    if (*(int *)(param_1 + 0x8c) != 0) {
      clearBlock__10RingBufferFl(*(u32 *)(param_1 + 0x18),*(int *)(param_1 + 0x8c));
      SendSize_1509 = SendSize_1509 + *(int *)(param_1 + 0x8c);
      *(u32 *)(param_1 + 0x8c) = 0;
    }
    iVar1 = getBufferSerialSize__10RingBufferFli
                      (*(u32 *)(param_1 + 0x18),uVar3 & 0xffffffff,1);
    if (iVar1 == 0x1000) {
      *(u32 *)(param_1 + 0x8c) = 0x1000;
      __src = (void *)0x0;
      if ((*(u32 **)(param_1 + 0x18))[4] != 0) {
        __src = (void *)**(u32 **)(param_1 + 0x18);
      }
      memcpy(pvStack_4,__src,(long)*(int *)(param_1 + 0x8c));
      StreamWriteData__4SdrvFUiUiUi
                (sys__4Sdrv,*(u32 *)(param_1 + 0x94),*(u32 *)(param_1 + 0x8c),0x8000);
    }
  }
  EIntr();
  SignalSema(*(u32 *)(param_1 + 0x88));
  return 0;
}

/* ---- 0x0038a0a0 size 0x8  BGMServerHandler::@20@__dt(v)
 *      mangled: @20@__dt__16BGMServerHandlerFv */
int _20___dt__16BGMServerHandlerFv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x14;
  if (iVar1 != 0) {
    *(u8 **)(param_1 + -4) = __vt__16BGMServerHandler;
    *(u32 *)(param_1 + 0x14) = 0x406fac;
    __dt__7CPolObjFv(param_1,0);
    __dt__16LSDDeviceHandlerFv(iVar1,0);
    if (0 < param_2) {
      __dl__FPv(iVar1);
    }
  }
  return iVar1;
}

