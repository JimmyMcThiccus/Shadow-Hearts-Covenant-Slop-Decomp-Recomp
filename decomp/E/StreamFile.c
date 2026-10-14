/*
 * StreamFile.c -- Ghidra decompiler output (SLPM_602.19, JP Furokuban), tidied by tools/E_gen_decomp.py
 * 8 functions. Types: u8/u16/u32/u64 = undefined1/2/4/8. Addresses in comments are JP main-exe addresses.
 */

/* ---- 0x0022f770 size 0x18c  StreamFile::StreamFile(PcUlUi)
 *      mangled: __ct__10StreamFileFPcUlUi */
int __ct__10StreamFileFPcUlUi(int param_1,char *param_2,u64 param_3,u32 param_4)

{
  u32 uVar1;
  long lVar2;
  
  __ct__10RingBufferFUlUi(param_1,param_3,0);
  __ct__7CPolObjFv(param_1 + 0x2c);
  *(u8 **)(param_1 + 0x28) = __vt__10StreamFile;
  *(u32 *)(param_1 + 0x40) = 0x404a5c;
  *(u32 *)(param_1 + 0x4c) = 0;
  *(u32 *)(param_1 + 0x50) = 0;
  *(u32 *)(param_1 + 0x58) = 0;
  *(u32 *)(param_1 + 0x44) = 0;
  *(u32 *)(param_1 + 0x5c) = param_4;
  lVar2 = __nw__FUi(0x10);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = __ct__9BufMemoryFUlUi(lVar2,*(u32 *)(param_1 + 0x5c),0x80);
  }
  *(u32 *)(param_1 + 0x48) = uVar1;
  *(u32 *)(param_1 + 300) = 0;
  *(u32 *)(param_1 + 0x130) = 0;
  *(u32 *)(param_1 + 0x134) = 0;
  if (param_2 == (char *)0x0) {
    memset((void *)(param_1 + 0x8c),0,0xa0);
  }
  else {
    strcpy((char *)(param_1 + 0x8c),param_2);
  }
  *(u32 *)(param_1 + 100) = 1;
  *(u32 *)(param_1 + 0x68) = 1;
  *(u32 *)(param_1 + 0x6c) = 1;
  uVar1 = CreateSema(param_1 + 100);
  *(u32 *)(param_1 + 0x7c) = uVar1;
  *(u32 *)(param_1 + 0x80) = 0;
  *(u32 *)(param_1 + 0x84) = 0;
  return param_1;
}

/* ---- 0x0022f900 size 0xcc  StreamFile::~StreamFile(v)
 *      mangled: __dt__10StreamFileFv */
int __dt__10StreamFileFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(u8 **)(param_1 + 0x28) = __vt__10StreamFile;
    *(u32 *)(param_1 + 0x40) = 0x404a5c;
    Remove__7CPolObjFv(param_1 + 0x2c);
    DeleteSema(*(u32 *)(param_1 + 0x7c));
    __dt__9BufMemoryFv(*(u32 *)(param_1 + 0x48),1);
    __dt__7CPolObjFv(param_1 + 0x2c,0);
    __dt__10RingBufferFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* ---- 0x0022f9d0 size 0xb4  StreamFile::stopStream(v)
 *      mangled: stopStream__10StreamFileFv */
u32 stopStream__10StreamFileFv(int param_1)

{
  WaitSema(*(u32 *)(param_1 + 0x7c));
  if ((*(int *)(param_1 + 0x44) != 0) && (*(int *)(param_1 + 300) == 1)) {
    *(u32 *)(param_1 + 300) = 2;
    close__9FileIOLibFP7_FIOHND(ourFio__9FileIOLib,*(u32 *)(param_1 + 0x44));
    init__10RingBufferFv(param_1);
    *(u32 *)(param_1 + 0x44) = 0;
    *(u32 *)(param_1 + 300) = 0;
    *(u32 *)(param_1 + 0x58) = 0;
    *(u32 *)(param_1 + 0x4c) = 0;
  }
  SignalSema(*(u32 *)(param_1 + 0x7c));
  return 1;
}

/* ---- 0x0022fa90 size 0x2f0  StreamFile::Polling(v)
 *      mangled: Polling__10StreamFileFv */
u64 Polling__10StreamFileFv(int param_1)

{
  int iVar1;
  u32 uVar2;
  long lVar3;
  u64 uVar4;
  
  WaitSema(*(u32 *)(param_1 + 0x7c));
  if (((*(int *)(param_1 + 0x44) != 0) && (*(int *)(param_1 + 0x58) == 0)) &&
     (lVar3 = getStatus__9FileIOLibFP7_FIOHND(ourFio__9FileIOLib,*(u32 *)(param_1 + 0x44)),
     lVar3 == 0)) {
    if (*(int *)(*(int *)(param_1 + 0x44) + 0x94) != *(int *)(param_1 + 0x4c)) {
      iVar1 = GetTimer__7SysToolFv();
      *(int *)(param_1 + 0x80) = *(int *)(param_1 + 0x80) + (iVar1 - *(int *)(param_1 + 0x88));
      *(int *)(param_1 + 0x84) =
           *(int *)(param_1 + 0x84) +
           (*(int *)(*(int *)(param_1 + 0x44) + 0x94) - *(int *)(param_1 + 0x4c));
      uVar4 = getBuffer__9BufMemoryFv(*(u32 *)(param_1 + 0x48));
      writeData__10RingBufferFPUclUi
                (param_1,uVar4,*(int *)(*(int *)(param_1 + 0x44) + 0x94) - *(int *)(param_1 + 0x4c),
                 (uint)(*(int *)(*(int *)(param_1 + 0x44) + 0x94) - *(int *)(param_1 + 0x60)) >> 0xb
                );
      *(u32 *)(param_1 + 0x4c) = *(u32 *)(*(int *)(param_1 + 0x44) + 0x94);
    }
    iVar1 = getEmptySize__10RingBufferFv(param_1);
    if (*(int *)(param_1 + 0x5c) <= iVar1) {
      if ((*(uint *)(*(int *)(param_1 + 0x44) + 0x90) <= *(uint *)(*(int *)(param_1 + 0x44) + 0x94))
         && (*(int *)(param_1 + 0x50) != 0)) {
        *(u32 *)(*(int *)(param_1 + 0x44) + 0x94) = *(u32 *)(param_1 + 0x54);
        *(u32 *)(param_1 + 0x4c) = *(u32 *)(param_1 + 0x54);
      }
      if (*(uint *)(*(int *)(param_1 + 0x44) + 0x94) < *(uint *)(*(int *)(param_1 + 0x44) + 0x90)) {
        if ((uint)(*(int *)(*(int *)(param_1 + 0x44) + 0x90) -
                  *(int *)(*(int *)(param_1 + 0x44) + 0x94)) < *(uint *)(param_1 + 0x5c)) {
          iVar1 = *(int *)(*(int *)(param_1 + 0x44) + 0x90) -
                  *(int *)(*(int *)(param_1 + 0x44) + 0x94);
        }
        else {
          iVar1 = *(int *)(param_1 + 0x5c);
        }
        *(int *)(param_1 + 0x60) = iVar1;
        read__9FileIOLibFP7_FIOHNDP9BufMemoryi
                  (ourFio__9FileIOLib,*(u32 *)(param_1 + 0x44),
                   *(u32 *)(param_1 + 0x48),*(u32 *)(param_1 + 0x60));
        uVar2 = GetTimer__7SysToolFv();
        *(u32 *)(param_1 + 0x88) = uVar2;
      }
      else {
        *(u32 *)(param_1 + 0x58) = 1;
      }
    }
  }
  SignalSema(*(u32 *)(param_1 + 0x7c));
  if (*(int *)(param_1 + 0x130) != 0) {
    (**(code **)(param_1 + 0x130))(*(u32 *)(param_1 + 0x134));
  }
  return 0;
}

/* ---- 0x0022fd80 size 0xf0  StreamFile::startStream(v)
 *      mangled: startStream__10StreamFileFv */
u32 startStream__10StreamFileFv(int param_1)

{
  u32 uVar1;
  long lVar2;
  
  WaitSema(*(u32 *)(param_1 + 0x7c));
  if (*(int *)(param_1 + 300) == 0) {
    do {
      lVar2 = open__9FileIOLibFPcib(ourFio__9FileIOLib,param_1 + 0x8c,0x20000000,1);
      *(int *)(param_1 + 0x44) = (int)lVar2;
    } while (lVar2 == 0);
    do {
      lVar2 = getStatus__9FileIOLibFP7_FIOHND(ourFio__9FileIOLib,*(u32 *)(param_1 + 0x44));
    } while (lVar2 != 0);
    *(u32 *)(param_1 + 300) = 1;
    *(u32 *)(*(int *)(param_1 + 0x44) + 0xb8) = 0;
    *(u32 *)(param_1 + 0x80) = 0;
    *(u32 *)(param_1 + 0x84) = 0;
    SignalSema(*(u32 *)(param_1 + 0x7c));
    uVar1 = 1;
  }
  else {
    SignalSema(*(u32 *)(param_1 + 0x7c));
    uVar1 = 0;
  }
  return uVar1;
}

/* ---- 0x0022fe70 size 0x58  StreamFile::setStreamName(PCc)
 *      mangled: setStreamName__10StreamFileFPCc */
u32 setStreamName__10StreamFileFPCc(int param_1,char *param_2)

{
  WaitSema(*(u32 *)(param_1 + 0x7c));
  strcpy((char *)(param_1 + 0x8c),param_2);
  SignalSema(*(u32 *)(param_1 + 0x7c));
  return 1;
}

/* ---- 0x0022fed0 size 0x8  StreamFile::@44@Polling(v)
 *      mangled: @44@Polling__10StreamFileFv */
u64 _44_Polling__10StreamFileFv(int param_1)

{
  int iVar1;
  u32 uVar2;
  long lVar3;
  u64 uVar4;
  
  WaitSema(*(u32 *)(param_1 + 0x50));
  if (((*(int *)(param_1 + 0x18) != 0) && (*(int *)(param_1 + 0x2c) == 0)) &&
     (lVar3 = getStatus__9FileIOLibFP7_FIOHND(ourFio__9FileIOLib,*(u32 *)(param_1 + 0x18)),
     lVar3 == 0)) {
    if (*(int *)(*(int *)(param_1 + 0x18) + 0x94) != *(int *)(param_1 + 0x20)) {
      iVar1 = GetTimer__7SysToolFv();
      *(int *)(param_1 + 0x54) = *(int *)(param_1 + 0x54) + (iVar1 - *(int *)(param_1 + 0x5c));
      *(int *)(param_1 + 0x58) =
           *(int *)(param_1 + 0x58) +
           (*(int *)(*(int *)(param_1 + 0x18) + 0x94) - *(int *)(param_1 + 0x20));
      uVar4 = getBuffer__9BufMemoryFv(*(u32 *)(param_1 + 0x1c));
      writeData__10RingBufferFPUclUi
                (param_1 + -0x2c,uVar4,
                 *(int *)(*(int *)(param_1 + 0x18) + 0x94) - *(int *)(param_1 + 0x20),
                 (uint)(*(int *)(*(int *)(param_1 + 0x18) + 0x94) - *(int *)(param_1 + 0x34)) >> 0xb
                );
      *(u32 *)(param_1 + 0x20) = *(u32 *)(*(int *)(param_1 + 0x18) + 0x94);
    }
    iVar1 = getEmptySize__10RingBufferFv(param_1 + -0x2c);
    if (*(int *)(param_1 + 0x30) <= iVar1) {
      if ((*(uint *)(*(int *)(param_1 + 0x18) + 0x90) <= *(uint *)(*(int *)(param_1 + 0x18) + 0x94))
         && (*(int *)(param_1 + 0x24) != 0)) {
        *(u32 *)(*(int *)(param_1 + 0x18) + 0x94) = *(u32 *)(param_1 + 0x28);
        *(u32 *)(param_1 + 0x20) = *(u32 *)(param_1 + 0x28);
      }
      if (*(uint *)(*(int *)(param_1 + 0x18) + 0x94) < *(uint *)(*(int *)(param_1 + 0x18) + 0x90)) {
        if ((uint)(*(int *)(*(int *)(param_1 + 0x18) + 0x90) -
                  *(int *)(*(int *)(param_1 + 0x18) + 0x94)) < *(uint *)(param_1 + 0x30)) {
          iVar1 = *(int *)(*(int *)(param_1 + 0x18) + 0x90) -
                  *(int *)(*(int *)(param_1 + 0x18) + 0x94);
        }
        else {
          iVar1 = *(int *)(param_1 + 0x30);
        }
        *(int *)(param_1 + 0x34) = iVar1;
        read__9FileIOLibFP7_FIOHNDP9BufMemoryi
                  (ourFio__9FileIOLib,*(u32 *)(param_1 + 0x18),
                   *(u32 *)(param_1 + 0x1c),*(u32 *)(param_1 + 0x34));
        uVar2 = GetTimer__7SysToolFv();
        *(u32 *)(param_1 + 0x5c) = uVar2;
      }
      else {
        *(u32 *)(param_1 + 0x2c) = 1;
      }
    }
  }
  SignalSema(*(u32 *)(param_1 + 0x50));
  if (*(int *)(param_1 + 0x104) != 0) {
    (**(code **)(param_1 + 0x104))(*(u32 *)(param_1 + 0x108));
  }
  return 0;
}

/* ---- 0x0022fee0 size 0x8  StreamFile::@44@__dt(v)
 *      mangled: @44@__dt__10StreamFileFv */
int _44___dt__10StreamFileFv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x2c;
  if (iVar1 != 0) {
    *(u8 **)(param_1 + -4) = __vt__10StreamFile;
    *(u32 *)(param_1 + 0x14) = 0x404a5c;
    Remove__7CPolObjFv(param_1);
    DeleteSema(*(u32 *)(param_1 + 0x50));
    __dt__9BufMemoryFv(*(u32 *)(param_1 + 0x1c),1);
    __dt__7CPolObjFv(param_1,0);
    __dt__10RingBufferFv(iVar1,0);
    if (0 < param_2) {
      __dl__FPv(iVar1);
    }
  }
  return iVar1;
}

