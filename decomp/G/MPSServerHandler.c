/* SECTION G  main-executable side: MPSServerHandler / MPSModel
 * JP SLPM_602.19 (Furokuban). Ghidra decompile with symbols/gp globals resolved. */

/* JP: 0x0038e030  MPSServerHandler::~MPSServerHandler()   [__dt__16MPSServerHandlerFv]  size=0x60 */
long __dt__16MPSServerHandlerFv(long param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)((int)param_1 + 0x10) = __vt__16MPSServerHandler;
    __dt__16LSDDeviceHandlerFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x0038e090  MPSServerHandler::CheckData(_LSDTrackHdr*)   [CheckData__16MPSServerHandlerFP12_LSDTrackHdr]  size=0x18 */
bool CheckData__16MPSServerHandlerFP12_LSDTrackHdr(undefined8 param_1,undefined4 *param_2)

{
  return (undefined *)*param_2 == &UNK_2053504d;
}

/* JP: 0x0038e0b0  MPSServerHandler::Open(RingBuffer*)   [Open__16MPSServerHandlerFP10RingBuffer]  size=0x130 */
int Open__16MPSServerHandlerFP10RingBuffer(undefined4 param_1,undefined8 param_2)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  long lVar4;
  undefined8 uVar5;
  
  lVar4 = __nw__FUi(0xb0);
  iVar1 = 0;
  if (lVar4 != 0) {
    iVar1 = __ct__8MPSModelFv(lVar4);
  }
  getReadData__10RingBufferFPvUlUl(param_2,iVar1 + 0x20,0x32,0);
  *(undefined4 *)(iVar1 + 0xc) = *(undefined4 *)(iVar1 + 0x20);
  *(undefined4 *)(iVar1 + 0x14) = param_1;
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
    *(undefined4 *)(iVar1 + 0x1c) = uVar2;
    iVar3 = iVar1 + 0xc;
  }
  return iVar3;
}

/* JP: 0x0038e1e0  MPSServerHandler::Read(_LSDHANDLE*, RingBuffer*)   [Read__16MPSServerHandlerFP10_LSDHANDLEP10RingBuffer]  size=0x100 */
int Read__16MPSServerHandlerFP10_LSDHANDLEP10RingBuffer
              (undefined8 param_1,int param_2,undefined8 param_3)

{
  int iVar1;
  undefined4 uVar2;
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
    *(undefined4 *)(iVar1 + 8) = uVar2;
    Create__8CFieldBGFP9BufMemoryi(*(undefined4 *)(iVar1 + 8),*(undefined4 *)(iVar1 + 0x1c),1);
    *(undefined4 *)(iVar1 + 0x1c) = 0;
    iVar3 = GetModel__8CFieldBGFi(*(undefined4 *)(iVar1 + 8),0);
    *(undefined4 *)(iVar1 + 0x60) = *(undefined4 *)(iVar3 + 0x70);
  }
  return *(int *)(iVar5 + 8) * 0x10 + 0x10;
}

/* JP: 0x0038e2e0  MPSServerHandler::Event(_LSDHANDLE*, int, float, float)   [Event__16MPSServerHandlerFP10_LSDHANDLEiff]  size=0xc4 */
void Event__16MPSServerHandlerFP10_LSDHANDLEiff
               (undefined4 param_1,undefined4 param_2,undefined8 param_3,int param_4,long param_5)

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

/* JP: 0x0038e3b0  MPSServerHandler::Close(_LSDHANDLE*)   [Close__16MPSServerHandlerFP10_LSDHANDLE]  size=0x24 */
undefined4 Close__16MPSServerHandlerFP10_LSDHANDLE(undefined8 param_1,int param_2)

{
  __dt__8MPSModelFv(*(undefined4 *)(param_2 + 0xc),1);
  return 1;
}

/* JP: 0x0038e3e0  MPSModel::MPSModel()   [__ct__8MPSModelFv]  size=0x44 */
undefined8 __ct__8MPSModelFv(undefined8 param_1)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)param_1;
  *puVar1 = 0;
  puVar1[1] = 0;
  __ct__8LSDModelFv(puVar1 + 0x16);
  puVar1[2] = 0;
  puVar1[7] = 0;
  puVar1[6] = puVar1;
  puVar1[0x15] = 0;
  return param_1;
}

/* JP: 0x0038e430  MPSModel::~MPSModel()   [__dt__8MPSModelFv]  size=0xac */
long __dt__8MPSModelFv(long param_1,short param_2)

{
  int iVar1;
  int iVar2;
  
  if (param_1 != 0) {
    iVar2 = (int)param_1;
    *(undefined4 *)(iVar2 + 0x60) = 0;
    iVar1 = *(int *)(iVar2 + 8);
    if (iVar1 != 0) {
      if (iVar1 != 0) {
        Release__8CFieldBGFv(iVar1);
        __dl__FPv(iVar1);
      }
      *(undefined4 *)(iVar2 + 8) = 0;
    }
    if (*(int *)(iVar2 + 0x1c) != 0) {
      __dt__9BufMemoryFv(*(int *)(iVar2 + 0x1c),1);
      *(undefined4 *)(iVar2 + 0x1c) = 0;
    }
    __dt__8LSDModelFv(iVar2 + 0x58,0xffffffffffffffff);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}
