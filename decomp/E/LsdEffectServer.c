/*
 * LsdEffectServer.c -- Ghidra decompiler output (SLPM_602.19, JP Furokuban), tidied by tools/E_gen_decomp.py
 * 9 functions. Types: u8/u16/u32/u64 = undefined1/2/4/8. Addresses in comments are JP main-exe addresses.
 */

/* ---- 0x00324b00 size 0x3c  LsdEffectServer::LsdEffectServer(v)
 *      mangled: __ct__15LsdEffectServerFv */
int __ct__15LsdEffectServerFv(int param_1)

{
  __ct__16LSDDeviceHandlerFv(param_1);
  *(u8 **)(param_1 + 0x10) = __vt__15LsdEffectServer;
  return param_1;
}

/* ---- 0x00324b40 size 0x74  LsdEffectServer::~LsdEffectServer(v)
 *      mangled: __dt__15LsdEffectServerFv */
int __dt__15LsdEffectServerFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(u8 **)(param_1 + 0x10) = __vt__15LsdEffectServer;
    __dt__16LSDDeviceHandlerFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* ---- 0x00324bc0 size 0x44  LsdEffectServer::CheckData(P12_LSDTrackHdr)
 *      mangled: CheckData__15LsdEffectServerFP12_LSDTrackHdr */
bool CheckData__15LsdEffectServerFP12_LSDTrackHdr(u64 param_1,int *param_2)

{
  return *param_2 == 0x4446452e;
}

/* ---- 0x00324c10 size 0xdc  LsdEffectServer::Open(P10RingBuffer)
 *      mangled: Open__15LsdEffectServerFP10RingBuffer */
u64 Open__15LsdEffectServerFP10RingBuffer(u32 param_1,u32 param_2)

{
  u32 uVar1;
  long lVar2;
  u64 uVar3;
  u32 *puVar4;
  
  lVar2 = __nw__FUi(0x40);
  uVar3 = 0;
  if (lVar2 != 0) {
    uVar3 = __ct__9LsdEffectFv(lVar2);
  }
  puVar4 = (u32 *)uVar3;
  getReadData__10RingBufferFPvUlUl(param_2,puVar4 + 4,0x20,0);
  *puVar4 = puVar4[4];
  puVar4[2] = param_1;
  puVar4[3] = puVar4;
  lVar2 = __nw__FUi(0x10);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = __ct__9BufMemoryFUlUi(lVar2,puVar4[10] << 4,0x80);
  }
  puVar4[0xd] = uVar1;
  return uVar3;
}

/* ---- 0x00324cf0 size 0x108  LsdEffectServer::Read(P10_LSDHANDLEP10RingBuffer)
 *      mangled: Read__15LsdEffectServerFP10_LSDHANDLEP10RingBuffer */
int Read__15LsdEffectServerFP10_LSDHANDLEP10RingBuffer
              (u64 param_1,int param_2,u32 param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  u32 uVar4;
  long lVar5;
  
  iVar2 = getReadTopAdress__10RingBufferFv(param_3);
  iVar1 = *(int *)(param_2 + 0xc);
  iVar3 = getBuffer__9BufMemoryFv(*(u32 *)(iVar1 + 0x34));
  getReadData__10RingBufferFPvUlUl
            (param_3,iVar3 + *(int *)(iVar1 + 0x38),*(int *)(iVar2 + 8) << 4,0x10);
  *(int *)(iVar1 + 0x38) = *(int *)(iVar1 + 0x38) + *(int *)(iVar2 + 8) * 0x10;
  if ((uint)(*(int *)(iVar1 + 0x28) << 4) <= *(uint *)(iVar1 + 0x38)) {
    lVar5 = __nw__FUi(0x48);
    uVar4 = 0;
    if (lVar5 != 0) {
      uVar4 = __ct__6EffectFPFPvi_vPvi(lVar5,0,0,0);
    }
    *(u32 *)(iVar1 + 0x30) = uVar4;
    Create__6EffectFP9BufMemory(*(u32 *)(iVar1 + 0x30),*(u32 *)(iVar1 + 0x34));
  }
  return *(int *)(iVar2 + 8) * 0x10 + 0x10;
}

/* ---- 0x00324e50 size 0xf4  LsdEffectServer::Event(P10_LSDHANDLEiff)
 *      mangled: Event__15LsdEffectServerFP10_LSDHANDLEiff */
void Event__15LsdEffectServerFP10_LSDHANDLEiff(u64 param_1,int param_2,u32 param_3)

{
  int iVar1;
  
  iVar1 = *(int *)(param_2 + 0xc);
  if (*(int *)(iVar1 + 0x30) != 0) {
    switch(param_3) {
    case 1:
      Run__6EffectFv(*(u32 *)(iVar1 + 0x30));
      break;
    case 2:
      Stop__6EffectFv(*(u32 *)(iVar1 + 0x30));
      break;
    case 3:
      Continue__6EffectFv(*(u32 *)(iVar1 + 0x30));
      break;
    case 4:
      Stop__6EffectFv(*(u32 *)(iVar1 + 0x30));
      break;
    case 5:
      Stop__6EffectFv(*(u32 *)(iVar1 + 0x30));
      break;
    case 6:
      Continue__6EffectFv(*(u32 *)(iVar1 + 0x30));
    }
  }
  return;
}

/* ---- 0x00324f50 size 0x5c  LsdEffectServer::Close(P10_LSDHANDLE)
 *      mangled: Close__15LsdEffectServerFP10_LSDHANDLE */
u32 Close__15LsdEffectServerFP10_LSDHANDLE(u64 param_1,int param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(param_2 + 0xc);
  if (iVar1 != 0) {
    (**(code **)(*(int *)(iVar1 + 0x3c) + 8))(iVar1,1);
  }
  return 1;
}

/* ---- 0x00324fb0 size 0x40  LsdEffect::LsdEffect(v)
 *      mangled: __ct__9LsdEffectFv */
int __ct__9LsdEffectFv(int param_1)

{
  *(u8 **)(param_1 + 0x3c) = __vt__9LsdEffect;
  *(u32 *)(param_1 + 0x30) = 0;
  *(u32 *)(param_1 + 0x34) = 0;
  *(u32 *)(param_1 + 0x38) = 0;
  return param_1;
}

/* ---- 0x00324ff0 size 0xa8  LsdEffect::~LsdEffect(v)
 *      mangled: __dt__9LsdEffectFv */
int __dt__9LsdEffectFv(int param_1,short param_2)

{
  int iVar1;
  
  if (param_1 != 0) {
    *(u8 **)(param_1 + 0x3c) = __vt__9LsdEffect;
    if (*(int *)(param_1 + 0x30) != 0) {
      iVar1 = *(int *)(param_1 + 0x30);
      if (iVar1 != 0) {
        (**(code **)(*(int *)(iVar1 + 0x14) + 8))(iVar1,1);
      }
      *(u32 *)(param_1 + 0x30) = 0;
    }
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

