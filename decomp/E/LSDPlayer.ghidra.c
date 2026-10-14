/*
 * LSDPlayer.ghidra.c -- Ghidra decompiler output (SLPM_602.19, JP Furokuban), tidied by tools/E_gen_decomp.py
 * 24 functions. Types: u8/u16/u32/u64 = undefined1/2/4/8. Addresses in comments are JP main-exe addresses.
 */

/* ---- 0x00387370 size 0x110  LSDPlayer::LSDPlayer(v)
 *      mangled: __ct__9LSDPlayerFv */
u64 __ct__9LSDPlayerFv(u64 param_1)

{
  u32 uVar1;
  long lVar2;
  int iVar3;
  float fVar4;
  
  __ct__7CPolObjFv();
  iVar3 = (int)param_1;
  *(u8 **)(iVar3 + 0x14) = __vt__9LSDPlayer;
  sys__9LSDPlayer = iVar3;
  *(u32 *)(iVar3 + 0x90) = 0;
  *(u8 *)(iVar3 + 0x98) = 0;
  *(u32 *)(iVar3 + 0x94) = 0;
  *(u32 *)(iVar3 + 0x9c) = 0;
  *(u32 *)(iVar3 + 0x78) = 0;
  *(u32 *)(iVar3 + 0x1c) = 0;
  *(u32 *)(iVar3 + 0x70) = 0xffffffff;
  *(u32 *)(iVar3 + 0x74) = 0xffffffff;
  *(u32 *)(iVar3 + 0x24) = 0;
  *(u32 *)(iVar3 + 0x7c) = 0;
  *(u32 *)(iVar3 + 0xa0) = 0;
  *(u32 *)(iVar3 + 0x84) = 0;
  *(u32 *)(iVar3 + 0x88) = 0;
  *(u32 *)(iVar3 + 0x28) = 0x3f800000;
  Entry__7CPollerFP7CPolObjib(app__4CApp + 0x48,param_1,0x80,0);
  lVar2 = __nw__FUi(0x2c);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = __ct__10RingBufferFUlUi(lVar2,0x5000,0);
  }
  *(u32 *)(iVar3 + 0x18) = uVar1;
  fVar4 = 1.0 / (60.0 / (float)(1 - (int)((long)((ulong)m_flags__3Gsx << 0x3c) >> 0x3f)));
  *(float *)(iVar3 + 0x20) = fVar4;
  *(float *)(iVar3 + 0x20) = fVar4 * *(float *)(iVar3 + 0x28);
  *(u32 *)(iVar3 + 0xa4) = 1;
  *(u32 *)(iVar3 + 0xa8) = 1;
  *(u32 *)(iVar3 + 0xac) = 1;
  uVar1 = CreateSema(iVar3 + 0xa4);
  *(u32 *)(iVar3 + 0x80) = uVar1;
  return param_1;
}

/* ---- 0x00387480 size 0xf8  LSDPlayer::~LSDPlayer(v)
 *      mangled: __dt__9LSDPlayerFv */
long __dt__9LSDPlayerFv(long param_1,short param_2)

{
  int iVar1;
  int iVar2;
  
  if (param_1 != 0) {
    iVar2 = (int)param_1;
    *(u8 **)(iVar2 + 0x14) = __vt__9LSDPlayer;
    Dispose__7CPollerFP7CPolObj(app__4CApp + 0x48,param_1);
    DeleteSema(*(u32 *)(iVar2 + 0x80));
    sys__9LSDPlayer = 0;
    iVar1 = *(int *)(iVar2 + 0x90);
    if (iVar1 != 0) {
      if (iVar1 != 0) {
        (**(code **)(*(int *)(iVar1 + 0x28) + 8))(iVar1,1);
      }
      *(u32 *)(iVar2 + 0x90) = 0;
    }
    iVar1 = *(int *)(iVar2 + 0x18);
    if (iVar1 != 0) {
      if (iVar1 != 0) {
        (**(code **)(*(int *)(iVar1 + 0x28) + 8))(iVar1,1);
      }
      *(u32 *)(iVar2 + 0x18) = 0;
    }
    if (*(int *)(iVar2 + 0x94) != 0) {
      __dla__FPv();
      *(u32 *)(iVar2 + 0x94) = 0;
    }
    __dt__7CPolObjFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* ---- 0x00387580 size 0x8  LSDPlayer::InitialReset(v)
 *      mangled: InitialReset__9LSDPlayerFv */
void InitialReset__9LSDPlayerFv(void)

{
  return;
}

/* ---- 0x00387590 size 0x34  LSDPlayer::StreamPolling(Pv)
 *      mangled: StreamPolling__9LSDPlayerFPv */
void StreamPolling__9LSDPlayerFPv(int param_1)

{
  if ((*(int *)(param_1 + 0x90) != 0) && (*(int *)(*(int *)(param_1 + 0x90) + 0x10) != 0)) {
    dataCheck__9LSDPlayerFv();
  }
  return;
}

/* ---- 0x003875d0 size 0x50  LSDPlayer::PlugDevice(P16LSDDeviceHandler)
 *      mangled: PlugDevice__9LSDPlayerFP16LSDDeviceHandler */
u32 PlugDevice__9LSDPlayerFP16LSDDeviceHandler(int *param_1)

{
  u32 uVar1;
  
  if ((*param_1 == 0) && (param_1[1] == 0)) {
    if (List__9LSDPlayer != (int *)0x0) {
      *param_1 = (int)List__9LSDPlayer;
      List__9LSDPlayer[1] = (int)param_1;
    }
    uVar1 = 1;
    List__9LSDPlayer = param_1;
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

/* ---- 0x00387620 size 0x36c  LSDPlayer::Polling(v)
 *      mangled: Polling__9LSDPlayerFv */
/* WARNING: Function: litodp replaced with injection: inttodp */
/* WARNING: Function: dpmul replaced with injection: dpmul */
/* WARNING: Function: dpsub replaced with injection: dpsub */

u64 Polling__9LSDPlayerFv(u64 param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  long lVar4;
  int iVar5;
  int iVar6;
  u64 uVar7;
  int iVar8;
  float fVar9;
  
  iVar5 = (int)param_1;
  WaitSema(*(u32 *)(iVar5 + 0x80));
  checkEvent__9LSDPlayerFv(param_1);
  if ((*(int *)(iVar5 + 0xa0) == 0) && (*(int *)(iVar5 + 0x70) == 1)) {
    iVar8 = 0;
    if (*(short *)(iVar5 + 0x3a) != 0) {
      iVar6 = 0;
      do {
        iVar1 = *(int *)(*(int *)(iVar5 + 0x94) + iVar6);
        if (iVar1 != 0) {
          (**(code **)(*(int *)(*(int *)(iVar1 + 8) + 0x10) + 0x18))
                    (*(u32 *)(iVar5 + 0x1c),*(u32 *)(iVar5 + 0x24),*(int *)(iVar1 + 8)
                     ,iVar1,0);
        }
        iVar8 = iVar8 + 1;
        iVar6 = iVar6 + 4;
      } while (iVar8 < (int)(uint)*(ushort *)(iVar5 + 0x3a));
    }
    uVar2 = __fixunssfdi((float)*(ushort *)(iVar5 + 0x3e) *
                         (*(float *)(iVar5 + 0x1c) + *(float *)(iVar5 + 0x20)));
    if ((*(uint *)(iVar5 + 0x2c) < uVar2) && (*(int *)(*(int *)(iVar5 + 0x90) + 0x58) == 0)) {
      *(u32 *)(iVar5 + 0x24) = 0;
      if (*(int *)(iVar5 + 0x84) == 0) {
        *(u32 *)(iVar5 + 0x20) = 0;
        iVar8 = *(int *)(iVar5 + 0x90);
        iVar6 = 0;
        if (*(int *)(iVar8 + 0x10) == 0) {
          uVar7 = 0x412f400000000000;
          lVar4 = _dpflt(0x412f400000000000,0);
          if (lVar4 != 0) {
            uVar7 = 0;
          }
          iVar6 = dptoli(uVar7);
        }
        uVar2 = *(uint *)(*(int *)(iVar8 + 0x44) + 0x90);
        uVar3 = *(int *)(iVar8 + 0x4c) + iVar6;
        if (uVar3 <= uVar2) {
          uVar2 = uVar3;
        }
        *(uint *)(iVar5 + 0x8c) = uVar2;
        *(u32 *)(iVar5 + 0x84) = 1;
        if (*(int *)(iVar5 + 0x8c) == 0) {
          *(u32 *)(iVar5 + 0x84) = 2;
        }
        if ((*(int *)(iVar5 + 0x88) == 0) && (iVar8 = 0, *(short *)(iVar5 + 0x3a) != 0)) {
          iVar6 = 0;
          do {
            iVar1 = *(int *)(*(int *)(iVar5 + 0x94) + iVar6);
            if (iVar1 != 0) {
              (**(code **)(*(int *)(*(int *)(iVar1 + 8) + 0x10) + 0x18))
                        (0,0,*(int *)(iVar1 + 8),iVar1,5);
            }
            iVar8 = iVar8 + 1;
            iVar6 = iVar6 + 4;
          } while (iVar8 < (int)(uint)*(ushort *)(iVar5 + 0x3a));
        }
      }
    }
    else {
      if (((*(int *)(iVar5 + 0x84) == 2) &&
          (((*(int *)(iVar5 + 0x90) != 0 &&
            (iVar8 = *(int *)(*(int *)(iVar5 + 0x90) + 0x44), iVar8 != 0)) &&
           (*(uint *)(iVar5 + 0x8c) <= *(uint *)(iVar8 + 0x94))))) &&
         (*(u32 *)(iVar5 + 0x84) = 0, *(int *)(iVar5 + 0x88) == 0)) {
        fVar9 = 1.0 / (60.0 / (float)m_syncCount__3Gsx);
        *(float *)(iVar5 + 0x20) = fVar9;
        *(float *)(iVar5 + 0x20) = fVar9 * *(float *)(iVar5 + 0x28);
        iVar8 = 0;
        if (*(short *)(iVar5 + 0x3a) != 0) {
          iVar6 = 0;
          do {
            iVar1 = *(int *)(*(int *)(iVar5 + 0x94) + iVar6);
            if (iVar1 != 0) {
              (**(code **)(*(int *)(*(int *)(iVar1 + 8) + 0x10) + 0x18))
                        (0,0,*(int *)(iVar1 + 8),iVar1,6);
            }
            iVar8 = iVar8 + 1;
            iVar6 = iVar6 + 4;
          } while (iVar8 < (int)(uint)*(ushort *)(iVar5 + 0x3a));
        }
      }
      *(float *)(iVar5 + 0x24) = *(float *)(iVar5 + 0x20);
      *(float *)(iVar5 + 0x1c) = *(float *)(iVar5 + 0x1c) + *(float *)(iVar5 + 0x20);
    }
  }
  SignalSema(*(u32 *)(iVar5 + 0x80));
  return 0;
}

/* ---- 0x00387990 size 0xb0  LSDPlayer::Pause(v)
 *      mangled: Pause__9LSDPlayerFv */
void Pause__9LSDPlayerFv(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if (*(int *)(param_1 + 0x88) == 0) {
    *(u32 *)(param_1 + 0x20) = 0;
    *(u32 *)(param_1 + 0x88) = 1;
    if ((*(int *)(param_1 + 0x84) == 0) && (iVar2 = 0, *(short *)(param_1 + 0x3a) != 0)) {
      iVar3 = 0;
      do {
        iVar1 = *(int *)(*(int *)(param_1 + 0x94) + iVar3);
        if (iVar1 != 0) {
          (**(code **)(*(int *)(*(int *)(iVar1 + 8) + 0x10) + 0x18))
                    (0,0,*(int *)(iVar1 + 8),iVar1,5);
        }
        iVar2 = iVar2 + 1;
        iVar3 = iVar3 + 4;
      } while (iVar2 < (int)(uint)*(ushort *)(param_1 + 0x3a));
    }
  }
  return;
}

/* ---- 0x00387a40 size 0x108  LSDPlayer::Release(v)
 *      mangled: Release__9LSDPlayerFv */
void Release__9LSDPlayerFv(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  float fVar4;
  
  if ((*(int *)(param_1 + 0x88) != 0) &&
     (*(u32 *)(param_1 + 0x88) = 0, *(int *)(param_1 + 0x84) == 0)) {
    fVar4 = 1.0 / (60.0 / (float)m_syncCount__3Gsx);
    *(float *)(param_1 + 0x20) = fVar4;
    *(float *)(param_1 + 0x20) = fVar4 * *(float *)(param_1 + 0x28);
    iVar2 = 0;
    if (*(short *)(param_1 + 0x3a) != 0) {
      iVar3 = 0;
      do {
        iVar1 = *(int *)(*(int *)(param_1 + 0x94) + iVar3);
        if (iVar1 != 0) {
          (**(code **)(*(int *)(*(int *)(iVar1 + 8) + 0x10) + 0x18))
                    (0,0,*(int *)(iVar1 + 8),iVar1,6);
        }
        iVar2 = iVar2 + 1;
        iVar3 = iVar3 + 4;
      } while (iVar2 < (int)(uint)*(ushort *)(param_1 + 0x3a));
    }
  }
  return;
}

/* ---- 0x00387b50 size 0x2f8  LSDPlayer::checkEvent(v)
 *      mangled: checkEvent__9LSDPlayerFv */
void checkEvent__9LSDPlayerFv(int param_1)

{
  int iVar1;
  long lVar2;
  int iVar3;
  int iVar4;
  int iStack_8;
  ushort uStack_4;
  ushort uStack_2;
  
  if ((*(int *)(param_1 + 0x70) == 1) && (iVar4 = 0, *(short *)(param_1 + 0x3a) != 0)) {
    iVar3 = 0;
    do {
      if ((((*(int *)(param_1 + 0x94) != 0) &&
           (iVar1 = *(int *)(*(int *)(param_1 + 0x94) + iVar3), iVar1 != 0)) &&
          (*(int *)(iVar1 + 4) != 0)) &&
         (lVar2 = (**(code **)(*(int *)(*(int *)(iVar1 + 8) + 0x10) + 0x14))(), lVar2 != 0)) {
        *(u32 *)(*(int *)(param_1 + 0x94) + iVar3) = 0;
        *(int *)(param_1 + 0x78) = *(int *)(param_1 + 0x78) + -1;
        if (*(int *)(param_1 + 0x78) == 0) {
          *(u32 *)(param_1 + 0x70) = 2;
        }
      }
      iVar4 = iVar4 + 1;
      iVar3 = iVar3 + 4;
    } while (iVar4 < (int)(uint)*(ushort *)(param_1 + 0x3a));
  }
  if (*(int *)(param_1 + 0xa0) == 1) {
    iVar4 = 0;
    if (*(short *)(param_1 + 0x3a) != 0) {
      iVar3 = 0;
      do {
        iVar1 = *(int *)(*(int *)(param_1 + 0x94) + iVar3);
        if (iVar1 != 0) {
          (**(code **)(*(int *)(*(int *)(iVar1 + 8) + 0x10) + 0x18))
                    (0,0,*(int *)(iVar1 + 8),iVar1,4);
          *(u32 *)(*(int *)(*(int *)(param_1 + 0x94) + iVar3) + 4) = 1;
        }
        iVar4 = iVar4 + 1;
        iVar3 = iVar3 + 4;
      } while (iVar4 < (int)(uint)*(ushort *)(param_1 + 0x3a));
    }
    *(u32 *)(param_1 + 0xa0) = 2;
  }
  iVar4 = *(int *)(param_1 + 0x18);
  if ((*(int *)(iVar4 + 0x10) != 0) && (*(int *)(param_1 + 0xa0) == 0)) {
    do {
      getReadData__10RingBufferFPvUlUl(iVar4,&iStack_8,4,0);
      getReadData__10RingBufferFPvUlUl(*(u32 *)(param_1 + 0x18),&uStack_4,4,4);
      if (*(int *)(param_1 + 0x70) == 0) {
        if ((*(code **)(param_1 + 0x7c) != (code *)0x0) &&
           (lVar2 = (**(code **)(param_1 + 0x7c))(), lVar2 == 0)) {
          return;
        }
        if (*(ushort *)(sys__9LSDPlayer + 0x3e) == 0) {
          trap(7);
        }
        *(float *)(param_1 + 0x1c) =
             (float)(iStack_8 / (int)(uint)*(ushort *)(sys__9LSDPlayer + 0x3e));
        *(u32 *)(param_1 + 0x70) = 1;
      }
      if ((int)(*(float *)(param_1 + 0x1c) * (float)*(ushort *)(sys__9LSDPlayer + 0x3e)) < iStack_8)
      {
        return;
      }
      iVar4 = *(int *)(*(int *)(param_1 + 0x94) + (uint)uStack_2 * 4);
      if ((iVar4 != 0) &&
         ((**(code **)(*(int *)(*(int *)(iVar4 + 8) + 0x10) + 0x18))
                    (*(float *)(param_1 + 0x1c),*(u32 *)(param_1 + 0x24),*(int *)(iVar4 + 8),
                     iVar4,uStack_4 & 0xfff), (uStack_4 & 0xfff) == 4)) {
        *(u32 *)(*(int *)(*(int *)(param_1 + 0x94) + (uint)uStack_2 * 4) + 4) = 1;
      }
      clearBlock__10RingBufferFl(*(u32 *)(param_1 + 0x18),8);
      iVar4 = *(int *)(param_1 + 0x18);
    } while (7 < *(uint *)(iVar4 + 0x10));
  }
  return;
}

/* ---- 0x00387e50 size 0x154  LSDPlayer::dataCheck(v)
 *      mangled: dataCheck__9LSDPlayerFv */
void dataCheck__9LSDPlayerFv(u64 param_1)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  long lVar5;
  
  iVar4 = (int)param_1;
  WaitSema(*(u32 *)(iVar4 + 0x80));
  do {
    cVar1 = *(char *)(iVar4 + 0x98);
    lVar5 = 0;
    if (cVar1 == '\x02') {
      uVar2 = (*(int **)(iVar4 + 0x90))[4];
      if (0xf < uVar2) {
        iVar3 = 0;
        if (uVar2 != 0) {
          iVar3 = **(int **)(iVar4 + 0x90);
        }
        if (*(int *)(iVar3 + 8) * 0x10 + 0x10U <= uVar2) {
          lVar5 = recivePacket__9LSDPlayerFP10RingBuffer(param_1);
        }
      }
    }
    else if (cVar1 == '\x01') {
      if (0x1f < *(uint *)(*(int *)(iVar4 + 0x90) + 0x10)) {
        lVar5 = reciveTrackHdr__9LSDPlayerFP10RingBuffer(param_1);
        *(int *)(iVar4 + 0x9c) = *(int *)(iVar4 + 0x9c) + 1;
        if ((int)(uint)*(ushort *)(iVar4 + 0x3a) <= *(int *)(iVar4 + 0x9c)) {
          *(u8 *)(iVar4 + 0x98) = 2;
        }
      }
    }
    else if (((cVar1 == '\0') && (0x3f < *(uint *)(*(int *)(iVar4 + 0x90) + 0x10))) &&
            (lVar5 = reciveInit__9LSDPlayerFP10RingBuffer(param_1), lVar5 != 0)) {
      *(u8 *)(iVar4 + 0x98) = 1;
    }
    clearBlock__10RingBufferFl(*(u32 *)(iVar4 + 0x90),(int)lVar5);
  } while (lVar5 != 0);
  SignalSema(*(u32 *)(iVar4 + 0x80));
  return;
}

/* ---- 0x00387fb0 size 0x7c  LSDPlayer::reciveInit(P10RingBuffer)
 *      mangled: reciveInit__9LSDPlayerFP10RingBuffer */
u32 reciveInit__9LSDPlayerFP10RingBuffer(int param_1,u64 param_2)

{
  u32 uVar1;
  int iVar2;
  int iVar3;
  
  getReadData__10RingBufferFPvUlUl(param_2,param_1 + 0x30,0x40,0);
  uVar1 = __nwa__FUi((uint)*(ushort *)(param_1 + 0x3a) << 2);
  *(u32 *)(param_1 + 0x94) = uVar1;
  iVar3 = 0;
  if (*(short *)(param_1 + 0x3a) != 0) {
    iVar2 = 0;
    do {
      iVar3 = iVar3 + 1;
      *(u32 *)(*(int *)(param_1 + 0x94) + iVar2) = 0;
      iVar2 = iVar2 + 4;
    } while (iVar3 < (int)(uint)*(ushort *)(param_1 + 0x3a));
  }
  return 0x40;
}

/* ---- 0x00388030 size 0x134  LSDPlayer::reciveTrackHdr(P10RingBuffer)
 *      mangled: reciveTrackHdr__9LSDPlayerFP10RingBuffer */
int reciveTrackHdr__9LSDPlayerFP10RingBuffer(int param_1,u64 param_2)

{
  bool bVar1;
  u32 uVar2;
  long lVar3;
  u32 *puVar4;
  int iVar5;
  int iVar6;
  
  if (((int *)param_2)[4] == 0) {
    iVar6 = 0;
  }
  else {
    iVar6 = *(int *)param_2;
  }
  bVar1 = true;
  for (iVar5 = 0;
      (bVar1 && (puVar4 = List__9LSDPlayer, iVar5 < (int)(uint)*(ushort *)(param_1 + 0x3a)));
      iVar5 = iVar5 + 1) {
    while (puVar4 != (u32 *)0x0) {
      lVar3 = (**(code **)(puVar4[4] + 8))(puVar4,iVar6);
      if (lVar3 == 0) {
        puVar4 = (u32 *)*puVar4;
      }
      else {
        uVar2 = (**(code **)(puVar4[4] + 0xc))(puVar4,param_2);
        puVar4 = (u32 *)0x0;
        bVar1 = false;
        *(u32 *)(*(int *)(param_1 + 0x94) + *(int *)(param_1 + 0x9c) * 4) = uVar2;
        *(u32 *)(*(int *)(*(int *)(param_1 + 0x94) + *(int *)(param_1 + 0x9c) * 4) + 4) = 0;
        *(int *)(param_1 + 0x78) = *(int *)(param_1 + 0x78) + 1;
      }
    }
  }
  return (uint)*(ushort *)(iVar6 + 0x10) << 4;
}

/* ---- 0x00388170 size 0xa4  LSDPlayer::recivePacket(P10RingBuffer)
 *      mangled: recivePacket__9LSDPlayerFP10RingBuffer */
int recivePacket__9LSDPlayerFP10RingBuffer(int param_1,u32 *param_2)

{
  int iVar1;
  ushort *puVar2;
  
  if (param_2[4] == 0) {
    puVar2 = (ushort *)0x0;
  }
  else {
    puVar2 = (ushort *)*param_2;
  }
  if ((*puVar2 < *(ushort *)(param_1 + 0x3a)) &&
     (iVar1 = *(int *)(*(int *)(param_1 + 0x94) + (uint)*puVar2 * 4), iVar1 != 0)) {
    iVar1 = (**(code **)(*(int *)(*(int *)(iVar1 + 8) + 0x10) + 0x10))();
    if (iVar1 != 0) {
      return iVar1;
    }
    *(uint *)(param_1 + 0x74) = (uint)*puVar2;
    return 0;
  }
  return *(int *)(puVar2 + 4) * 0x10 + 0x10;
}

/* ---- 0x00388220 size 0xe4  LSDPlayer::startStream(Pc)
 *      mangled: startStream__9LSDPlayerFPc */
u8 startStream__9LSDPlayerFPc(int param_1,u64 param_2)

{
  u8 uVar1;
  u32 uVar2;
  long lVar3;
  int iVar4;
  
  if (*(int *)(param_1 + 0x90) == 0) {
    lVar3 = __nw__FUi(0x138);
    uVar2 = 0;
    if (lVar3 != 0) {
      uVar2 = __ct__10StreamFileFPcUlUi(lVar3,param_2,0x177000,0xc800);
    }
    *(u32 *)(param_1 + 0x90) = uVar2;
    iVar4 = *(int *)(param_1 + 0x90);
    if (iVar4 != 0) {
      iVar4 = iVar4 + 0x2c;
    }
    Entry__7CPollerFP7CPolObjib(ourFio__9FileIOLib + 0x1395c,iVar4,0x80,0);
  }
  else {
    setStreamName__10StreamFileFPCc();
  }
  if (*(int *)(param_1 + 0x90) == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = startStream__10StreamFileFv();
    iVar4 = *(int *)(param_1 + 0x90);
    *(code **)(iVar4 + 0x130) = StreamPolling__9LSDPlayerFPv;
    *(int *)(iVar4 + 0x134) = param_1;
    *(u32 *)(param_1 + 0x70) = 0;
  }
  return uVar1;
}

/* ---- 0x00388310 size 0xc0  LSDPlayer::Exit(v)
 *      mangled: Exit__9LSDPlayerFv */
void Exit__9LSDPlayerFv(int param_1)

{
  int iVar1;
  char cVar2;
  float fVar3;
  
  iVar1 = *(int *)(param_1 + 0x90);
  if (iVar1 == 0) {
    cVar2 = '\0';
  }
  else {
    *(u32 *)(iVar1 + 0x130) = 0;
    *(u32 *)(iVar1 + 0x134) = 0;
    cVar2 = stopStream__10StreamFileFv(*(u32 *)(param_1 + 0x90));
  }
  if (((cVar2 != '\0') && (*(float *)(param_1 + 0x20) == 0.0)) && (*(int *)(param_1 + 0xa0) == 0)) {
    *(u32 *)(param_1 + 0xa0) = 1;
    fVar3 = 1.0 / (60.0 / (float)(1 - (int)((long)((ulong)m_flags__3Gsx << 0x3c) >> 0x3f)));
    *(float *)(param_1 + 0x20) = fVar3;
    *(float *)(param_1 + 0x20) = fVar3 * *(float *)(param_1 + 0x28);
  }
  return;
}

/* ---- 0x003883d0 size 0x110  LSDPlayer::Reset(v)
 *      mangled: Reset__9LSDPlayerFv */
u32 Reset__9LSDPlayerFv(int param_1)

{
  int iVar1;
  u32 uVar2;
  float fVar3;
  
  if ((*(int *)(param_1 + 0x70) == 2) || (*(int *)(param_1 + 0x70) == -1)) {
    *(u16 *)(param_1 + 0x3a) = 0;
    iVar1 = *(int *)(param_1 + 0x90);
    if (iVar1 != 0) {
      *(u32 *)(iVar1 + 0x130) = 0;
      *(u32 *)(iVar1 + 0x134) = 0;
      stopStream__10StreamFileFv(*(u32 *)(param_1 + 0x90));
    }
    *(u32 *)(param_1 + 0x70) = 0xffffffff;
    *(u32 *)(param_1 + 0x74) = 0xffffffff;
    *(u32 *)(param_1 + 0xa0) = 0;
    if (*(int *)(param_1 + 0x94) != 0) {
      __dla__FPv();
      *(u32 *)(param_1 + 0x94) = 0;
    }
    *(u32 *)(param_1 + 0x28) = 0x3f800000;
    *(u32 *)(param_1 + 0x94) = 0;
    *(u32 *)(param_1 + 0x9c) = 0;
    *(u32 *)(param_1 + 0x78) = 0;
    *(u32 *)(param_1 + 0x1c) = 0;
    *(u32 *)(param_1 + 0x84) = 0;
    *(u32 *)(param_1 + 0x88) = 0;
    fVar3 = 1.0 / (60.0 / (float)(1 - (int)((long)((ulong)m_flags__3Gsx << 0x3c) >> 0x3f)));
    *(float *)(param_1 + 0x20) = fVar3;
    *(float *)(param_1 + 0x20) = fVar3 * *(float *)(param_1 + 0x28);
    *(u8 *)(param_1 + 0x98) = 0;
    iVar1 = *(int *)(*(int *)(param_1 + 0x18) + 0x10);
    if (iVar1 != 0) {
      clearBlock__10RingBufferFl(*(int *)(param_1 + 0x18),iVar1);
    }
    uVar2 = 1;
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

/* ---- 0x003884e0 size 0x1c  LSDDeviceHandler::LSDDeviceHandler(v)
 *      mangled: __ct__16LSDDeviceHandlerFv */
u64 __ct__16LSDDeviceHandlerFv(u64 param_1)

{
  u32 *puVar1;
  
  puVar1 = (u32 *)param_1;
  puVar1[4] = __vt__16LSDDeviceHandler;
  *puVar1 = 0;
  puVar1[1] = 0;
  return param_1;
}

/* ---- 0x00388500 size 0x4c  LSDDeviceHandler::~LSDDeviceHandler(v)
 *      mangled: __dt__16LSDDeviceHandlerFv */
long __dt__16LSDDeviceHandlerFv(long param_1,short param_2)

{
  if ((param_1 != 0) &&
     (*(u8 **)((int)param_1 + 0x10) = __vt__16LSDDeviceHandler, 0 < param_2)) {
    __dl__FPv();
  }
  return param_1;
}

/* ---- 0x00388550 size 0x5c  LSDPlayerHandler::~LSDPlayerHandler(v)
 *      mangled: __dt__16LSDPlayerHandlerFv */
long __dt__16LSDPlayerHandlerFv(long param_1,short param_2)

{
  if (param_1 != 0) {
    *(u8 **)((int)param_1 + 0x10) = __vt__16LSDPlayerHandler;
    if (param_1 != 0) {
      *(u8 **)((int)param_1 + 0x10) = __vt__16LSDDeviceHandler;
    }
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* ---- 0x003885b0 size 0x18  LSDPlayerHandler::CheckData(P12_LSDTrackHdr)
 *      mangled: CheckData__16LSDPlayerHandlerFP12_LSDTrackHdr */
bool CheckData__16LSDPlayerHandlerFP12_LSDTrackHdr(u64 param_1,int *param_2)

{
  return *param_2 == 0x4344534c;
}

/* ---- 0x003885d0 size 0x84  LSDPlayerHandler::Open(P10RingBuffer)
 *      mangled: Open__16LSDPlayerHandlerFP10RingBuffer */
int Open__16LSDPlayerHandlerFP10RingBuffer(int param_1)

{
  u32 uVar1;
  
  *(int *)(param_1 + 0x20) = sys__9LSDPlayer;
  uVar1 = SetInter30__3GsxFi(1);
  *(u32 *)(param_1 + 8) = uVar1;
  if (*(int *)(param_1 + 8) == 0) {
    *(u32 *)(param_1 + 0xc) = 1;
  }
  else {
    *(u32 *)(param_1 + 0xc) = 2;
  }
  if (*(ushort *)(sys__9LSDPlayer + 0x3e) == 0) {
    trap(7);
  }
  SetFFMode__3GsxFibi(0,1,0x3c / *(ushort *)(sys__9LSDPlayer + 0x3e));
  return param_1 + 0x14;
}

/* ---- 0x00388660 size 0x1ec  LSDPlayerHandler::Read(P10_LSDHANDLEP10RingBuffer)
 *      mangled: Read__16LSDPlayerHandlerFP10_LSDHANDLEP10RingBuffer */
int Read__16LSDPlayerHandlerFP10_LSDHANDLEP10RingBuffer
              (u64 param_1,u64 param_2,u64 param_3)

{
  long lVar1;
  u64 uVar2;
  int iVar3;
  long lVar4;
  uint uVar5;
  long lVar6;
  int iVar7;
  byte abStack_20 [4];
  u32 uStack_1c;
  uint uStack_18;
  short asStack_8 [2];
  ushort uStack_4;
  
  iVar7 = 0;
  uVar5 = ((int *)param_3)[4];
  if (uVar5 == 0) {
    iVar3 = 0;
  }
  else {
    iVar3 = *(int *)param_3;
  }
  if (*(int *)(iVar3 + 8) * 0x10 + 0x10U <= uVar5) {
    getReadData__10RingBufferFPvUlUl(param_3,abStack_20,0x10,0x10);
    lVar6 = 0x20;
    uVar5 = 0;
    iVar7 = *(int *)(iVar3 + 8) * 0x10 + 0x10;
    if (uStack_18 != 0) {
      do {
        getReadData__10RingBufferFPvUlUl(param_3,asStack_8,8,lVar6);
        lVar6 = lVar6 + 8;
        if (asStack_8[0] == 1) {
          lVar4 = (long)(int)((uint)uStack_4 << 3);
          lVar1 = getEmptySize__10RingBufferFv(*(u32 *)(sys__9LSDPlayer + 0x18));
          if (lVar1 < lVar4) {
            printf(_2253);
            iVar7 = 0;
          }
          else {
            uVar2 = __nwa__FUi(lVar4);
            getReadData__10RingBufferFPvUlUl(param_3,uVar2,lVar4,lVar6);
            writeData__10RingBufferFPUclUi(*(u32 *)(sys__9LSDPlayer + 0x18),uVar2,lVar4,0);
            lVar6 = lVar6 + lVar4;
            __dla__FPv(uVar2);
          }
        }
        else {
          printf(_2254);
        }
        uVar5 = uVar5 + 1;
      } while (uVar5 < uStack_18);
    }
    *(u32 *)(sys__9LSDPlayer + 0x2c) = uStack_1c;
    if (*(int *)(sys__9LSDPlayer + 0x84) == 1) {
      *(u32 *)(sys__9LSDPlayer + 0x84) = 2;
    }
    if ((abStack_20[0] & 1) != 0) {
      printf(_2255);
    }
  }
  return iVar7;
}

/* ---- 0x00388850 size 0x8  LSDPlayerHandler::Event(P10_LSDHANDLEiff)
 *      mangled: Event__16LSDPlayerHandlerFP10_LSDHANDLEiff */
void Event__16LSDPlayerHandlerFP10_LSDHANDLEiff(void)

{
  return;
}

/* ---- 0x00388860 size 0x3c  LSDPlayerHandler::Close(P10_LSDHANDLE)
 *      mangled: Close__16LSDPlayerHandlerFP10_LSDHANDLE */
u32 Close__16LSDPlayerHandlerFP10_LSDHANDLE(int param_1)

{
  SetInter30__3GsxFi(*(u32 *)(param_1 + 8));
  SetFFMode__3GsxFibi(0,1,*(u32 *)(param_1 + 0xc));
  return 1;
}

