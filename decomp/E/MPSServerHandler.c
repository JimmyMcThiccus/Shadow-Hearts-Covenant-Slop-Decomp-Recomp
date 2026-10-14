/*
 * MPSServerHandler.c -- Ghidra decompiler output (SLPM_602.19, JP Furokuban), tidied by tools/E_gen_decomp.py
 * 6 functions. Types: u8/u16/u32/u64 = undefined1/2/4/8. Addresses in comments are JP main-exe addresses.
 */

/* ---- 0x0038e030 size 0x60  MPSServerHandler::~MPSServerHandler(v)
 *      mangled: __dt__16MPSServerHandlerFv */
long __dt__16MPSServerHandlerFv(long param_1,short param_2)

{
  if (param_1 != 0) {
    *(u8 **)((int)param_1 + 0x10) = __vt__16MPSServerHandler;
    __dt__16LSDDeviceHandlerFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* ---- 0x0038e090 size 0x18  MPSServerHandler::CheckData(P12_LSDTrackHdr)
 *      mangled: CheckData__16MPSServerHandlerFP12_LSDTrackHdr */
bool CheckData__16MPSServerHandlerFP12_LSDTrackHdr(u64 param_1,u32 *param_2)

{
  return (u8 *)*param_2 == &UNK_2053504d;
}

/* ---- 0x0038e0b0 size 0x130  MPSServerHandler::Open(P10RingBuffer)
 *      mangled: Open__16MPSServerHandlerFP10RingBuffer */
int Open__16MPSServerHandlerFP10RingBuffer(u32 param_1,u64 param_2)

{
  int iVar1;
  u32 uVar2;
  int iVar3;
  long lVar4;
  u64 uVar5;
  
  lVar4 = __nw__FUi(0xb0);
  iVar1 = 0;
  if (lVar4 != 0) {
    iVar1 = __ct__8MPSModelFv(lVar4);
  }
  getReadData__10RingBufferFPvUlUl(param_2,iVar1 + 0x20,0x32,0);
  *(u32 *)(iVar1 + 0xc) = *(u32 *)(iVar1 + 0x20);
  *(u32 *)(iVar1 + 0x14) = param_1;
  *(int *)(iVar1 + 0x18) = iVar1;
  if (-1 < (long)((ulong)*(byte *)(iVar1 + 0x50) << 0x3a)) {
    if ((sys__11ModelServer == 0) && (lVar4 = __nw__FUi(0xb0), lVar4 != 0)) {
      __ct__11ModelServerFv(lVar4);
    }
    memcpy((void *)(iVar1 + 0x98),(void *)(iVar1 + 0x40),0x12);
    uVar5 = GetTail__5CListFv(sys__11ModelServer);
    InsertAfter__5CListFP5CList(uVar5,iVar1 + 0x58);
  }
  iVar3 = 0;
  if (*(short *)(iVar1 + 0x32) == 0) {
    lVar4 = __nw__FUi(0x10);
    uVar2 = 0;
    if (lVar4 != 0) {
      uVar2 = __ct__9BufMemoryFUlUi(lVar4,*(int *)(iVar1 + 0x38) << 4,0x80);
    }
    *(u32 *)(iVar1 + 0x1c) = uVar2;
    iVar3 = iVar1 + 0xc;
  }
  return iVar3;
}

/* ---- 0x0038e1e0 size 0x100  MPSServerHandler::Read(P10_LSDHANDLEP10RingBuffer)
 *      mangled: Read__16MPSServerHandlerFP10_LSDHANDLEP10RingBuffer */
int Read__16MPSServerHandlerFP10_LSDHANDLEP10RingBuffer
              (u64 param_1,int param_2,u64 param_3)

{
  int iVar1;
  u32 uVar2;
  int iVar3;
  long lVar4;
  int iVar5;
  
  if (((int *)param_3)[4] == 0) {
    iVar5 = 0;
  }
  else {
    iVar5 = *(int *)param_3;
  }
  iVar1 = *(int *)(param_2 + 0xc);
  getReadData__10RingBufferFPvUlUl
            (param_3,*(int *)(*(int *)(iVar1 + 0x1c) + 4) + *(int *)(iVar1 + 0x54),
             *(int *)(iVar5 + 8) << 4,0x10);
  *(int *)(iVar1 + 0x54) = *(int *)(iVar1 + 0x54) + *(int *)(iVar5 + 8) * 0x10;
  if (((uint)(*(int *)(iVar1 + 0x38) << 4) <= *(uint *)(iVar1 + 0x54)) &&
     (-1 < (long)((ulong)*(byte *)(iVar1 + 0x50) << 0x3a))) {
    lVar4 = __nw__FUi(8);
    uVar2 = 0;
    if (lVar4 != 0) {
      uVar2 = __ct__8CFieldBGFv(lVar4);
    }
    *(u32 *)(iVar1 + 8) = uVar2;
    Create__8CFieldBGFP9BufMemoryi(*(u32 *)(iVar1 + 8),*(u32 *)(iVar1 + 0x1c),1);
    *(u32 *)(iVar1 + 0x1c) = 0;
    iVar3 = GetModel__8CFieldBGFi(*(u32 *)(iVar1 + 8),0);
    *(u32 *)(iVar1 + 0x60) = *(u32 *)(iVar3 + 0x70);
  }
  return *(int *)(iVar5 + 8) * 0x10 + 0x10;
}

/* ---- 0x0038e2e0 size 0xc4  MPSServerHandler::Event(P10_LSDHANDLEiff)
 *      mangled: Event__16MPSServerHandlerFP10_LSDHANDLEiff */
void Event__16MPSServerHandlerFP10_LSDHANDLEiff
               (u32 param_1,u32 param_2,u64 param_3,int param_4,long param_5)

{
  int iVar1;
  
  if ((*(int *)(param_4 + 0xc) != 0) && (iVar1 = *(int *)(*(int *)(param_4 + 0xc) + 8), iVar1 != 0))
  {
    if (param_5 == 1) {
      Dsp__8CFieldBGFv();
    }
    else if (param_5 == 2) {
      Clr__8CFieldBGFv();
    }
    else if (param_5 == 3) {
      Dsp__8CFieldBGFv();
    }
    else if (param_5 == 4) {
      Clr__8CFieldBGFv();
    }
    else if ((param_5 == 0) && (iVar1 != 0)) {
      Update__8CFieldBGFf(param_2);
    }
  }
  return;
}

/* ---- 0x0038e3b0 size 0x24  MPSServerHandler::Close(P10_LSDHANDLE)
 *      mangled: Close__16MPSServerHandlerFP10_LSDHANDLE */
u32 Close__16MPSServerHandlerFP10_LSDHANDLE(u64 param_1,int param_2)

{
  __dt__8MPSModelFv(*(u32 *)(param_2 + 0xc),1);
  return 1;
}

