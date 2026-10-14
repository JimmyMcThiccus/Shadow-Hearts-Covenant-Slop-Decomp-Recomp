/*
 * GenericDataHandler.c -- Ghidra decompiler output (SLPM_602.19, JP Furokuban), tidied by tools/E_gen_decomp.py
 * 12 functions. Types: u8/u16/u32/u64 = undefined1/2/4/8. Addresses in comments are JP main-exe addresses.
 */

/* ---- 0x003cc010 size 0x3c  GenericDataHandler::GenericDataHandler(v)
 *      mangled: __ct__18GenericDataHandlerFv */
int __ct__18GenericDataHandlerFv(int param_1)

{
  __ct__16LSDDeviceHandlerFv(param_1);
  *(u8 **)(param_1 + 0x10) = __vt__18GenericDataHandler;
  return param_1;
}

/* ---- 0x003cc050 size 0x74  GenericDataHandler::~GenericDataHandler(v)
 *      mangled: __dt__18GenericDataHandlerFv */
int __dt__18GenericDataHandlerFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(u8 **)(param_1 + 0x10) = __vt__18GenericDataHandler;
    __dt__16LSDDeviceHandlerFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* ---- 0x003cc0d0 size 0x2c  GenericDataHandler::CheckData(P12_LSDTrackHdr)
 *      mangled: CheckData__18GenericDataHandlerFP12_LSDTrackHdr */
bool CheckData__18GenericDataHandlerFP12_LSDTrackHdr(u64 param_1,int *param_2)

{
  return *param_2 == 0x5444474c;
}

/* ---- 0x003cc100 size 0xf0  GenericDataHandler::Open(P10RingBuffer)
 *      mangled: Open__18GenericDataHandlerFP10RingBuffer */
u64 Open__18GenericDataHandlerFP10RingBuffer(u32 param_1,u32 param_2)

{
  u64 uVar1;
  u32 *__s;
  u8 auStack_60 [16];
  byte bStack_50;
  u32 auStack_40 [2];
  u32 uStack_38;
  u32 uStack_34;
  int iStack_28;
  u32 uStack_20;
  u32 uStack_10;
  
  uStack_20 = param_1;
  uStack_10 = param_2;
  getReadData__10RingBufferFPvUlUl(param_2,auStack_40,0x20,0);
  getReadData__10RingBufferFPvUlUl(uStack_10,auStack_60,0x20,0x20);
  uVar1 = __nw__FUi(0x40);
  __s = (u32 *)uVar1;
  memset(__s,0,0x40);
  memcpy(__s + 4,auStack_60,0x10);
  *(byte *)(__s + 0xe) = *(byte *)(__s + 0xe) & 0xf0 | bStack_50 >> 4;
  *__s = auStack_40[0];
  __s[2] = uStack_20;
  __s[9] = uStack_38;
  __s[10] = uStack_34;
  __s[0xd] = iStack_28 << 4;
  AddData__18GenericDataHandlerFP16_GenericDataInfo(uVar1);
  return uVar1;
}

/* ---- 0x003cc1f0 size 0x30  GenericDataHandler::Close(P10_LSDHANDLE)
 *      mangled: Close__18GenericDataHandlerFP10_LSDHANDLE */
u32 Close__18GenericDataHandlerFP10_LSDHANDLE(u64 param_1,u32 param_2)

{
  RemoveData__18GenericDataHandlerFP16_GenericDataInfob(param_2,1);
  return 1;
}

/* ---- 0x003cc220 size 0x1b8  GenericDataHandler::Read(P10_LSDHANDLEP10RingBuffer)
 *      mangled: Read__18GenericDataHandlerFP10_LSDHANDLEP10RingBuffer */
int Read__18GenericDataHandlerFP10_LSDHANDLEP10RingBuffer
              (u64 param_1,int param_2,int *param_3)

{
  u32 uVar1;
  long lVar2;
  u64 uVar3;
  int iVar4;
  
  if (param_3[4] == 0) {
    iVar4 = 0;
  }
  else {
    iVar4 = *param_3;
  }
  if (*(int *)(param_2 + 0x2c) == 0) {
    if ((*(byte *)(param_2 + 0x38) & 0xf) == 0) {
      lVar2 = __nw__FUi(0x10);
      uVar1 = 0;
      if (lVar2 != 0) {
        uVar1 = __ct__9BufMemoryFUlUi(lVar2,*(u32 *)(param_2 + 0x34),0x80);
      }
      *(u32 *)(param_2 + 0x2c) = uVar1;
    }
    else {
      lVar2 = __nw__FUi(0x10);
      uVar1 = 0;
      if (lVar2 != 0) {
        uVar1 = __ct__9BufMemoryFv(lVar2);
      }
      *(u32 *)(param_2 + 0x2c) = uVar1;
      uVar3 = GetSoundMemory__4SdrvFiUi(sys__4Sdrv,0,*(u32 *)(param_2 + 0x34));
      SetBuffer__9BufMemoryFUlPUc
                (*(u32 *)(param_2 + 0x2c),*(u32 *)(param_2 + 0x34),uVar3);
    }
    *(u32 *)(param_2 + 0x30) = *(u32 *)(*(int *)(param_2 + 0x2c) + 4);
  }
  iVar4 = *(int *)(iVar4 + 8) * 0x10;
  getReadData__10RingBufferFPvUlUl(param_3,*(u32 *)(param_2 + 0x30),iVar4,0x10);
  *(int *)(param_2 + 0x30) = *(int *)(param_2 + 0x30) + iVar4;
  return iVar4 + 0x10;
}

/* ---- 0x003cc3e0 size 0x40  GenericDataHandler::Event(P10_LSDHANDLEiff)
 *      mangled: Event__18GenericDataHandlerFP10_LSDHANDLEiff */
void Event__18GenericDataHandlerFP10_LSDHANDLEiff(u64 param_1,u32 param_2,int param_3)

{
  if (param_3 == 4) {
    RemoveData__18GenericDataHandlerFP16_GenericDataInfob(param_2,0);
  }
  return;
}

/* ---- 0x003cc420 size 0x60  GenericDataHandler::Find(PCc)
 *      mangled: Find__18GenericDataHandlerFPCc */
int Find__18GenericDataHandlerFPCc(char *param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = m_pData__18GenericDataHandler;
  while ((iVar1 != 0 && (iVar2 = strcmp((char *)(iVar1 + 0x10),param_1), iVar2 != 0))) {
    iVar1 = *(int *)(iVar1 + 0x20);
  }
  return iVar1;
}

/* ---- 0x003cc480 size 0x58  GenericDataHandler::Find(P16_GenericDataInfo)
 *      mangled: Find__18GenericDataHandlerFP16_GenericDataInfo */
u32 Find__18GenericDataHandlerFP16_GenericDataInfo(int param_1)

{
  int iVar1;
  
  iVar1 = m_pData__18GenericDataHandler;
  while( true ) {
    if (iVar1 == 0) {
      return 0;
    }
    if (iVar1 == param_1) break;
    iVar1 = *(int *)(iVar1 + 0x20);
  }
  return 1;
}

/* ---- 0x003cc4e0 size 0xa4  GenericDataHandler::AddData(P16_GenericDataInfo)
 *      mangled: AddData__18GenericDataHandlerFP16_GenericDataInfo */
void AddData__18GenericDataHandlerFP16_GenericDataInfo(int param_1)

{
  long lVar1;
  int iVar2;
  
  lVar1 = Find__18GenericDataHandlerFP16_GenericDataInfo(param_1);
  if (lVar1 == 0) {
    iVar2 = m_pData__18GenericDataHandler;
    if (m_pData__18GenericDataHandler == 0) {
      m_pData__18GenericDataHandler = param_1;
      Clear__12CSndBufCacheFv();
    }
    else {
      for (; *(int *)(iVar2 + 0x20) != 0; iVar2 = *(int *)(iVar2 + 0x20)) {
      }
      *(int *)(iVar2 + 0x20) = param_1;
    }
  }
  *(short *)(param_1 + 0x3a) = *(short *)(param_1 + 0x3a) + 1;
  return;
}

/* ---- 0x003cc590 size 0x110  GenericDataHandler::RemoveData(P16_GenericDataInfob)
 *      mangled: RemoveData__18GenericDataHandlerFP16_GenericDataInfob */
void RemoveData__18GenericDataHandlerFP16_GenericDataInfob(int param_1,char param_2)

{
  int iVar1;
  long lVar2;
  short sVar3;
  int iVar4;
  
  lVar2 = Find__18GenericDataHandlerFP16_GenericDataInfo(param_1);
  if (lVar2 != 0) {
    if ((0 < *(short *)(param_1 + 0x3a)) &&
       (sVar3 = *(short *)(param_1 + 0x3a) + -1, *(short *)(param_1 + 0x3a) = sVar3, sVar3 == 0)) {
      ReleaseData__18GenericDataHandlerFP16_GenericDataInfo(param_1);
    }
    if (param_2 != '\0') {
      ReleaseData__18GenericDataHandlerFP16_GenericDataInfo(param_1);
      iVar4 = 0;
      for (iVar1 = m_pData__18GenericDataHandler; iVar1 != param_1; iVar1 = *(int *)(iVar1 + 0x20))
      {
        iVar4 = iVar1;
      }
      if (iVar4 == 0) {
        m_pData__18GenericDataHandler = *(int *)(param_1 + 0x20);
      }
      else {
        *(u32 *)(iVar4 + 0x20) = *(u32 *)(param_1 + 0x20);
      }
      __dl__FPv(param_1);
    }
  }
  return;
}

/* ---- 0x003cc6a0 size 0x9c  GenericDataHandler::ReleaseData(P16_GenericDataInfo)
 *      mangled: ReleaseData__18GenericDataHandlerFP16_GenericDataInfo */
void ReleaseData__18GenericDataHandlerFP16_GenericDataInfo(int param_1)

{
  if (*(int *)(param_1 + 0x2c) != 0) {
    if ((*(byte *)(param_1 + 0x38) & 0xf) == 1) {
      FreeSoundMemory__4SdrvFPv(sys__4Sdrv,*(u32 *)(*(int *)(param_1 + 0x2c) + 4));
    }
    __dt__9BufMemoryFv(*(u32 *)(param_1 + 0x2c),1);
    *(u32 *)(param_1 + 0x2c) = 0;
  }
  return;
}

