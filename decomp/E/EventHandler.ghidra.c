/*
 * EventHandler.ghidra.c -- Ghidra decompiler output (SLPM_602.19, JP Furokuban), tidied by tools/E_gen_decomp.py
 * 8 functions. Types: u8/u16/u32/u64 = undefined1/2/4/8. Addresses in comments are JP main-exe addresses.
 */

/* ---- 0x003cc740 size 0x3c  EventHandler::EventHandler(v)
 *      mangled: __ct__12EventHandlerFv */
int __ct__12EventHandlerFv(int param_1)

{
  __ct__16LSDDeviceHandlerFv(param_1);
  *(u8 **)(param_1 + 0x10) = __vt__12EventHandler;
  return param_1;
}

/* ---- 0x003cc780 size 0x74  EventHandler::~EventHandler(v)
 *      mangled: __dt__12EventHandlerFv */
int __dt__12EventHandlerFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(u8 **)(param_1 + 0x10) = __vt__12EventHandler;
    __dt__16LSDDeviceHandlerFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* ---- 0x003cc800 size 0x2c  EventHandler::CheckData(P12_LSDTrackHdr)
 *      mangled: CheckData__12EventHandlerFP12_LSDTrackHdr */
bool CheckData__12EventHandlerFP12_LSDTrackHdr(u64 param_1,int *param_2)

{
  return *param_2 == 0x5243534c;
}

/* ---- 0x003cc830 size 0x258  EventHandler::Open(P10RingBuffer)
 *      mangled: Open__12EventHandlerFP10RingBuffer */
u64 Open__12EventHandlerFP10RingBuffer(u32 param_1,u32 param_2)

{
  int iVar1;
  u64 uVar2;
  long lVar3;
  u64 uVar4;
  u32 *__s;
  int *piVar5;
  u32 auStack_50 [4];
  ushort uStack_40;
  int *piStack_28;
  uint uStack_24;
  u32 uStack_20;
  u32 uStack_10;
  
  uStack_20 = param_1;
  uStack_10 = param_2;
  getReadData__10RingBufferFPvUlUl(param_2,auStack_50,0x20,0);
  uStack_24 = (uint)uStack_40 * 0x10 + 3 >> 2;
  uVar2 = __nwa__FUi(uStack_24 << 2);
  __s = (u32 *)uVar2;
  memset(__s,0,0x20);
  *__s = auStack_50[0];
  __s[2] = uStack_20;
  getReadData__10RingBufferFPvUlUl(uStack_10,__s + 8,(uint)uStack_40 * 0x10 + -0x20,0x20);
  if (*(short *)((int)__s + 0x26) != 0) {
    piVar5 = __s + 8 + (uint)*(byte *)((int)__s + 0x21) * 4;
    piStack_28 = piVar5 + (uint)*(ushort *)((int)__s + 0x26) * 4;
    for (; piVar5 < piStack_28; piVar5 = piVar5 + (uint)*(ushort *)((int)piVar5 + 6) * 4) {
      if ((*piVar5 == 0x544e5645) && ((short)piVar5[2] == 1)) {
        __s[6] = piVar5 + 3;
        *(u16 *)(__s + 7) = *(u16 *)((int)piVar5 + 10);
        break;
      }
    }
  }
  iVar1 = sys__8LSDScrEx;
  if (sys__8LSDScrEx == 0) {
    lVar3 = __nw__FUi(0x6c);
    iVar1 = 0;
    if (lVar3 != 0) {
      iVar1 = __ct__8LSDScrExFv(lVar3);
    }
  }
  sys__8LSDScrEx = iVar1;
  iVar1 = sys__8LSDScrEx;
  lVar3 = __nw__FUi(0x28);
  uVar4 = 0;
  if (lVar3 != 0) {
    uVar4 = __ct__7CScriptFv(lVar3);
  }
  __s[4] = (int)uVar4;
  Create__7CScriptFPUciii(uVar4,0,0x10,0x200,5);
  InitScript__7CScriptFPcPUc(uVar4,0x402b60,__s + 8);
  LinkA__8LSDScrExFP10_EventWork(iVar1,uVar2);
  StartScript__7CScriptFv(uVar4);
  return uVar2;
}

/* ---- 0x003cca90 size 0x140  EventHandlerUpdate(P10_EventWork)
 *      mangled: EventHandlerUpdate__FP10_EventWork */
void EventHandlerUpdate__FP10_EventWork(int param_1)

{
  uint *puVar1;
  float fVar2;
  uint uVar3;
  
  if (*(short *)(param_1 + 0x1e) < *(short *)(param_1 + 0x1c)) {
    fVar2 = *(float *)(sys__9LSDPlayer + 0x1c) * (float)*(ushort *)(sys__9LSDPlayer + 0x3e);
    if (fVar2 < 2.1474836e+09) {
      uVar3 = (uint)fVar2;
    }
    else {
      uVar3 = (int)(fVar2 - 2.1474836e+09) | 0x80000000;
    }
    puVar1 = (uint *)(*(int *)(param_1 + 0x18) + *(short *)(param_1 + 0x1e) * 8);
    if (*puVar1 <= uVar3) {
      *(short *)(param_1 + 0x1e) = *(short *)(param_1 + 0x1e) + 1;
      CallEventT__7CScriptFUiiP9_ParStackPi(*(u32 *)(param_1 + 0x10),*puVar1,0,0,0);
    }
  }
  return;
}

/* ---- 0x003ccbd0 size 0x6c  EventHandler::Read(P10_LSDHANDLEP10RingBuffer)
 *      mangled: Read__12EventHandlerFP10_LSDHANDLEP10RingBuffer */
int Read__12EventHandlerFP10_LSDHANDLEP10RingBuffer
              (u64 param_1,u64 param_2,int *param_3)

{
  int iVar1;
  
  if (param_3[4] == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = *param_3;
  }
  return *(int *)(iVar1 + 8) * 0x10 + 0x10;
}

/* ---- 0x003ccc40 size 0x6c  EventHandler::Close(P10_LSDHANDLE)
 *      mangled: Close__12EventHandlerFP10_LSDHANDLE */
u32 Close__12EventHandlerFP10_LSDHANDLE(u64 param_1,int param_2)

{
  if (sys__8LSDScrEx != 0) {
    Delete__8LSDScrExFv(sys__8LSDScrEx);
  }
  if (*(int *)(param_2 + 0x10) != 0) {
    Delete__7CScriptFv(*(u32 *)(param_2 + 0x10));
  }
  __dla__FPv(param_2);
  return 1;
}

/* ---- 0x003cccb0 size 0xc0  EventHandler::Event(P10_LSDHANDLEiff)
 *      mangled: Event__12EventHandlerFP10_LSDHANDLEiff */
void Event__12EventHandlerFP10_LSDHANDLEiff(u64 param_1,int param_2,int param_3)

{
  if (param_3 != 6) {
    if (param_3 != 4) {
      if (param_3 == 5) {
        PauseFader__12CFieldSocketFi(m_socket__12CFieldSocket,0);
        return;
      }
      if (param_3 != 1) {
        return;
      }
      Init__8LSDScrExFv(sys__8LSDScrEx);
      return;
    }
    EndScene__7CScriptFv(*(u32 *)(param_2 + 0x10));
  }
  PauseFader__12CFieldSocketFi(m_socket__12CFieldSocket,1);
  return;
}

