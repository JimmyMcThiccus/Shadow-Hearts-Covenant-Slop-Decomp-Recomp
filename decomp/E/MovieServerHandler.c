/*
 * MovieServerHandler.c -- Ghidra decompiler output (SLPM_602.19, JP Furokuban), tidied by tools/E_gen_decomp.py
 * 17 functions. Types: u8/u16/u32/u64 = undefined1/2/4/8. Addresses in comments are JP main-exe addresses.
 */

/* ---- 0x0038b920 size 0xa0  MovieServerHandler::~MovieServerHandler(v)
 *      mangled: __dt__18MovieServerHandlerFv */
long __dt__18MovieServerHandlerFv(long param_1,short param_2)

{
  int iVar1;
  
  if (param_1 != 0) {
    iVar1 = (int)param_1;
    *(u8 **)(iVar1 + 0x10) = __vt__18MovieServerHandler;
    *(u32 *)(iVar1 + 0x24) = 0x40702c;
    *(u32 *)(iVar1 + 0x30) = 0x40703c;
    if (iVar1 != -0x28) {
      *(u8 **)(iVar1 + 0x30) = __vt__17DelayDeleteObject;
    }
    __dt__8VIF1PrimFv(iVar1 + 0x14,0);
    __dt__16LSDDeviceHandlerFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* ---- 0x0038b9c0 size 0x18  MovieServerHandler::CheckData(P12_LSDTrackHdr)
 *      mangled: CheckData__18MovieServerHandlerFP12_LSDTrackHdr */
bool CheckData__18MovieServerHandlerFP12_LSDTrackHdr(u64 param_1,int *param_2)

{
  return *param_2 == 0x53564f4d;
}

/* ---- 0x0038b9e0 size 0x340  MovieServerHandler::Open(P10RingBuffer)
 *      mangled: Open__18MovieServerHandlerFP10RingBuffer */
int Open__18MovieServerHandlerFP10RingBuffer(u64 param_1,u64 param_2)

{
  ushort uVar1;
  ushort uVar2;
  u32 uVar3;
  int iVar4;
  long lVar5;
  int iVar6;
  int *piVar7;
  int iVar8;
  
  iVar6 = (int)param_1;
  *(u32 *)(iVar6 + 0x7e60) = 0;
  *(int *)(iVar6 + 0x7c) = iVar6;
  *(int *)(iVar6 + 0x80) = iVar6;
  getReadData__10RingBufferFPvUlUl(param_2,iVar6 + 0x34,0x40,0);
  sceMpegInit();
  *(u32 *)(iVar6 + 0xc4) = 1;
  *(u32 *)(iVar6 + 200) = 1;
  *(u32 *)(iVar6 + 0xcc) = 1;
  uVar3 = CreateSema(iVar6 + 0xc4);
  *(u32 *)(iVar6 + 0xdc) = uVar3;
  *(u32 *)(iVar6 + 0x7e50) = 0;
  uVar1 = *(ushort *)(iVar6 + 0x5c);
  uVar2 = *(ushort *)(iVar6 + 0x5e);
  *(int *)(iVar6 + 0x7e58) = (int)(uint)uVar1 >> 4;
  *(int *)(iVar6 + 0x7e5c) = (int)(uint)uVar2 >> 4;
  if ((long)((ulong)*(byte *)(iVar6 + 0x54) << 0x3b) < 0) {
    *(u32 *)(iVar6 + 0x7e78) = 4;
  }
  else {
    *(u32 *)(iVar6 + 0x7e78) = 2;
  }
  uVar3 = __nwa__FUi(*(int *)(iVar6 + 0x7e78) << 3);
  *(u32 *)(iVar6 + 0x134) = uVar3;
  uVar3 = __nwa__FUi((*(int *)(iVar6 + 0x7e78) *
                      *(int *)(iVar6 + 0x7e5c) * *(int *)(iVar6 + 0x7e58) * 0x40 + 0x10) * 0x10);
  *(u32 *)(iVar6 + 0x128) = uVar3;
  **(int **)(iVar6 + 0x134) = *(int *)(iVar6 + 0x128) + 0xf0;
  **(uint **)(iVar6 + 0x134) = **(uint **)(iVar6 + 0x134) & 0xffffffc0;
  *(u32 *)(*(int *)(iVar6 + 0x134) + 4) = 0;
  iVar4 = 1;
  if (1 < *(int *)(iVar6 + 0x7e78)) {
    iVar8 = 8;
    do {
      iVar4 = iVar4 + 1;
      piVar7 = (int *)(*(int *)(iVar6 + 0x134) + iVar8);
      *piVar7 = piVar7[-2] + *(int *)(iVar6 + 0x7e58) * *(int *)(iVar6 + 0x7e5c) * 0x400;
      *(u32 *)(*(int *)(iVar6 + 0x134) + iVar8 + 4) = 0;
      iVar8 = iVar8 + 8;
    } while (iVar4 < *(int *)(iVar6 + 0x7e78));
  }
  *(u32 *)(iVar6 + 0x138) = 0;
  *(u32 *)(iVar6 + 0x7e44) = 0;
  *(u32 *)(iVar6 + 0x7e68) = 0;
  *(u32 *)(iVar6 + 0x13c) = 0;
  *(u32 *)(iVar6 + 0x140) = 0;
  *(u32 *)(iVar6 + 0x7e48) = 0;
  iVar4 = (uint)uVar1 * (uint)uVar2 * 9;
  *(u32 *)(iVar6 + 0x88) = 0;
  *(u32 *)(iVar6 + 0x7e4c) = 0;
  if (iVar4 < 0) {
    iVar4 = iVar4 + 1;
  }
  *(int *)(iVar6 + 0x130) = (iVar4 >> 1) + 0x176c;
  uVar3 = __nwa__FUi(*(u32 *)(iVar6 + 0x130));
  *(u32 *)(iVar6 + 300) = uVar3;
  sceMpegCreate(iVar6 + 0xe0,*(u32 *)(iVar6 + 300),*(u32 *)(iVar6 + 0x130));
  *(u32 *)(iVar6 + 0x7e64) = 0;
  lVar5 = __nw__FUi(0x34);
  iVar4 = (int)lVar5;
  if (lVar5 != 0) {
    __ct__11CVif1PacketFii(lVar5,1000,0x10);
    *(u8 **)(iVar4 + 0xc) = __vt__12TransePacket;
    *(u32 *)(iVar4 + 0x30) = 0xffffffff;
  }
  *(int *)(iVar6 + 0x7e6c) = iVar4;
  lVar5 = __nw__FUi(0x34);
  iVar4 = (int)lVar5;
  if (lVar5 != 0) {
    __ct__11CVif1PacketFii(lVar5,1000,0x10);
    *(u8 **)(iVar4 + 0xc) = __vt__12TransePacket;
    *(u32 *)(iVar4 + 0x30) = 0xffffffff;
  }
  *(int *)(iVar6 + 0x7e70) = iVar4;
  *(u32 *)(iVar6 + 0x7e74) = 0;
  lVar5 = __nw__FUi(0x2c);
  uVar3 = 0;
  if (lVar5 != 0) {
    uVar3 = __ct__10RingBufferFUlUi(lVar5,*(int *)(iVar6 + 0x4c) << 4,0);
  }
  *(u32 *)(iVar6 + 0x84) = uVar3;
  sceMpegAddCallback(iVar6 + 0xe0,1,0x38c900,param_1);
  sceMpegAddCallback(iVar6 + 0xe0,0,0x38cb00,param_1);
  sceMpegAddCallback(iVar6 + 0xe0,2,0x38cb50,param_1);
  sceMpegAddCallback(iVar6 + 0xe0,3,0x38cb90,param_1);
  sceMpegAddCallback(iVar6 + 0xe0,5,0x38cbd0,param_1);
  sceMpegAddCallback(iVar6 + 0xe0,4,0x38cc20,param_1);
  return iVar6 + 0x74;
}

/* ---- 0x0038bd20 size 0xf4  MovieServerHandler::Read(P10_LSDHANDLEP10RingBuffer)
 *      mangled: Read__18MovieServerHandlerFP10_LSDHANDLEP10RingBuffer */
int Read__18MovieServerHandlerFP10_LSDHANDLEP10RingBuffer
              (int param_1,u64 param_2,u64 param_3)

{
  long lVar1;
  u64 uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  
  WaitSema(*(u32 *)(param_1 + 0xdc));
  iVar3 = 0;
  if (((int *)param_3)[4] == 0) {
    iVar4 = 0;
  }
  else {
    iVar4 = *(int *)param_3;
  }
  uVar5 = *(int *)(iVar4 + 8) << 4;
  lVar1 = getEmptySize__10RingBufferFv(*(u32 *)(param_1 + 0x84));
  if ((long)(ulong)uVar5 <= lVar1) {
    uVar2 = __nwa__FUi(uVar5);
    getReadData__10RingBufferFPvUlUl(param_3,uVar2,*(int *)(iVar4 + 8) << 4,0x10);
    writeData__10RingBufferFPUclUi(*(u32 *)(param_1 + 0x84),uVar2,*(int *)(iVar4 + 8) << 4,0)
    ;
    iVar3 = *(int *)(iVar4 + 8) * 0x10 + 0x10;
    __dla__FPv(uVar2);
  }
  SignalSema(*(u32 *)(param_1 + 0xdc));
  return iVar3;
}

/* ---- 0x0038be20 size 0x188  MovieServerHandler::Event(P10_LSDHANDLEiff)
 *      mangled: Event__18MovieServerHandlerFP10_LSDHANDLEiff */
void Event__18MovieServerHandlerFP10_LSDHANDLEiff(VIF1Prim *param_1,u64 param_2,long param_3)

{
  int iVar1;
  int iVar2;
  long lVar3;
  uint uVar4;
  u32 *puVar5;
  
  if (param_3 == 1) {
    param_1[0x10].dw_unk0 = 1;
    if (param_1 != (VIF1Prim *)0x0) {
      param_1 = param_1 + 1;
    }
    AddOT__5WorldFiP8VIF1Prim((World *)&m_World__4CApp,0,param_1);
  }
  else if ((param_1[0x10].dw_unk0 == 0) || (param_3 != 0)) {
    if (param_3 == 4) {
      param_1[0x10].dw_unk0 = 0;
      if (param_1[0x652].dw_unk0 == 0) {
        param_1[0x652].dw_unk0 = 1;
        EndProcess__18MovieServerHandlerFv(param_1);
      }
    }
    else if (param_3 == 5) {
      param_1[0x650].bFlags = 1;
      param_1[0x650].b_pad0d = 0;
      param_1[0x650].nZvolume = 0;
    }
    else if (param_3 == 6) {
      param_1[0x650].bFlags = 0;
      param_1[0x650].b_pad0d = 0;
      param_1[0x650].nZvolume = 0;
    }
  }
  else {
    iVar1._0_1_ = param_1[0x651].bFlags;
    iVar1._1_1_ = param_1[0x651].b_pad0d;
    iVar1._2_2_ = param_1[0x651].nZvolume;
    if ((iVar1 == 0) && (lVar3 = sceMpegIsEnd(&param_1[0xb].dw_unk4), lVar3 == 0)) {
      puVar5 = (u32 *)(*(int *)&param_1[0xf].bFlags * 8 + param_1[0xf].dwEnv);
      if ((puVar5[1] == 0) &&
         (sceMpegGetPicture(&param_1[0xb].dw_unk4,*puVar5,
                            param_1[0x651].dw_unk4 * param_1[0x651].dwEnv),
         iVar2._0_1_ = param_1[0x651].bFlags, iVar2._1_1_ = param_1[0x651].b_pad0d,
         iVar2._2_2_ = param_1[0x651].nZvolume, iVar2 == 0)) {
        *(u32 *)(*(int *)&param_1[0xf].bFlags * 8 + param_1[0xf].dwEnv + 4) = 1;
        uVar4 = *(int *)&param_1[0xf].bFlags + 1U & (int)param_1[0x652].pVptr - 1U;
        param_1[0xf].bFlags = (char)uVar4;
        param_1[0xf].b_pad0d = (char)(uVar4 >> 8);
        param_1[0xf].nZvolume = (short)(uVar4 >> 0x10);
      }
    }
    else if (param_1[0x652].dw_unk0 == 0) {
      param_1[0x652].dw_unk0 = 1;
      EndProcess__18MovieServerHandlerFv(param_1);
    }
  }
  return;
}

/* ---- 0x0038bfb0 size 0x50  MovieServerHandler::EndProcess(v)
 *      mangled: EndProcess__18MovieServerHandlerFv */
int EndProcess__18MovieServerHandlerFv(VIF1Prim *param_1)

{
  int iVar1;
  
  sceMpegDelete(&param_1[0xb].dw_unk4);
  DeleteSema(param_1[0xb].dw_unk0);
  if (param_1 != (VIF1Prim *)0x0) {
    param_1 = param_1 + 1;
  }
  iVar1 = ReleaseOT__5WorldFP8VIF1Prim((World *)&m_World__4CApp,param_1);
  return iVar1;
}

/* ---- 0x0038c000 size 0x79c  MovieServerHandler::getPacket(v)
 *      mangled: getPacket__18MovieServerHandlerFv */
u32 getPacket__18MovieServerHandlerFv(int param_1)

{
  ushort uVar1;
  u32 *puVar2;
  u32 uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  
  uVar1 = *(ushort *)(param_1 + 0x5e);
  uVar6 = (uint)*(ushort *)(param_1 + 0x5c);
  uVar4 = (uint)*(ushort *)(camera__4CApp + 0x348);
  uVar9 = (uint)(uVar1 >> 4);
  uVar8 = uVar4;
  if (uVar6 < uVar4) {
    uVar8 = uVar6;
  }
  uVar8 = uVar8 >> 4;
  if (uVar4 <= uVar6) {
    uVar6 = uVar4;
  }
  if (*(ushort *)(camera__4CApp + 0x34a) <= uVar1) {
    uVar1 = *(ushort *)(camera__4CApp + 0x34a);
  }
  uVar4 = (uint)uVar1;
  iVar7 = 0;
  if ((long)((ulong)*(byte *)(param_1 + 0x54) << 0x3b) < 0) {
    iVar5 = *(int *)(param_1 + 0x134) + 4;
    if ((*(int *)(iVar5 + *(int *)(param_1 + 0x13c) * 8) != 0) &&
       (iVar10 = (*(int *)(param_1 + 0x13c) + 1U & *(int *)(param_1 + 0x7e78) - 1U) * 8,
       *(int *)(iVar5 + iVar10) != 0)) {
      iVar7 = *(int *)(*(int *)(param_1 + 0x7e74) * 4 + param_1 + 0x7e6c);
      *(u32 *)(iVar7 + 0x10) = *(u32 *)(iVar7 + 0x14);
      *(u32 *)(iVar7 + 0x18) = 0;
      if (*(int *)(iVar7 + 0x30) != -1) {
        *(u32 *)(*(int *)(iVar7 + 0x30) * 8 + *(int *)(param_1 + 0x134) + 4) = 0;
        *(u32 *)
         ((*(int *)(iVar7 + 0x30) + 1U & *(int *)(param_1 + 0x7e78) - 1U) * 8 +
          *(int *)(param_1 + 0x134) + 4) = 0;
        *(u32 *)(iVar7 + 0x30) = 0xffffffff;
      }
      iVar5 = 0;
      if (uVar8 != 0) {
        iVar11 = 0;
        iVar12 = 0;
        do {
          RefLoadImage__11CVif1PacketFUsUcUsP1UiUiUiUiUi
                    (iVar7,(*(ushort *)
                             (camera__4CApp + (*(byte *)(camera__4CApp + 0x394) ^ 1) * 2 + 0x38c) &
                           0x7ff) << 5,0,*(ushort *)(camera__4CApp + 0x348) >> 6,
                     *(int *)(*(int *)(param_1 + 0x134) + *(int *)(param_1 + 0x13c) * 8) +
                     iVar12 * 0x400,(int)(uVar4 * 0x40) >> 4,iVar11,0);
          iVar5 = iVar5 + 1;
          iVar11 = iVar11 + 0x10;
          iVar12 = iVar12 + uVar9;
        } while (iVar5 < (int)uVar8);
      }
      iVar5 = 0;
      if (uVar8 != 0) {
        iVar11 = 0;
        do {
          RefLoadImage__11CVif1PacketFUsUcUsP1UiUiUiUiUi
                    (iVar7,(*(ushort *)
                             (camera__4CApp + (*(byte *)(camera__4CApp + 0x394) ^ 1) * 2 + 0x38c) &
                           0x7ff) << 5,0,*(ushort *)(camera__4CApp + 0x348) >> 6,
                     *(int *)(iVar10 + *(int *)(param_1 + 0x134)) + iVar11 * 0x400,
                     (int)(uVar4 * 0x40) >> 4,uVar6,0);
          iVar5 = iVar5 + 1;
          uVar6 = uVar6 + 0x10;
          iVar11 = iVar11 + uVar9;
        } while (iVar5 < (int)uVar8);
      }
      if (*(int *)(iVar7 + 0x18) != 0) {
        uVar6 = *(uint *)(iVar7 + 0x10);
        while ((uVar6 & 0xf) != 0) {
          puVar2 = *(u32 **)(iVar7 + 0x10);
          *(u32 **)(iVar7 + 0x10) = puVar2 + 1;
          *puVar2 = 0;
          uVar6 = *(uint *)(iVar7 + 0x10);
        }
        **(short **)(iVar7 + 0x18) = (short)(uVar6 - (int)*(short **)(iVar7 + 0x18) >> 4) + -1;
      }
      *(u32 *)(iVar7 + 0x18) = *(u32 *)(iVar7 + 0x10);
      puVar2 = *(u32 **)(iVar7 + 0x10);
      *(u32 **)(iVar7 + 0x10) = puVar2 + 1;
      *puVar2 = 0x60000000;
      puVar2 = *(u32 **)(iVar7 + 0x10);
      *(u32 **)(iVar7 + 0x10) = puVar2 + 1;
      *puVar2 = 0;
      sceVif1PkTerminate(iVar7 + 0x10);
      *(uint *)(param_1 + 0x7e74) = *(uint *)(param_1 + 0x7e74) ^ 1;
      iVar5 = *(int *)(param_1 + 0x7e50) + 1;
      *(int *)(param_1 + 0x7e50) = iVar5;
      if (1 < iVar5) {
        if (*(int *)(param_1 + 0x7e4c) == 0) {
          *(u32 *)(iVar7 + 0x30) = *(u32 *)(param_1 + 0x13c);
          *(uint *)(param_1 + 0x13c) =
               *(int *)(param_1 + 0x13c) + 2U & *(int *)(param_1 + 0x7e78) - 1U;
          *(u32 *)(param_1 + 0x7e50) = 0;
        }
        else {
          *(u32 *)(iVar7 + 0x30) = 0xffffffff;
        }
      }
    }
  }
  else {
    iVar5 = *(int *)(param_1 + 0x134) + 4;
    if (*(int *)(iVar5 + *(int *)(param_1 + 0x13c) * 8) == 0) {
      uVar6 = *(uint *)(param_1 + 0x7e74);
      if (uVar6 != 0xffffffff) {
        iVar7 = *(int *)(uVar6 * 4 + param_1 + 0x7e6c);
        iVar10 = *(int *)(*(int *)((uVar6 ^ 1) * 4 + param_1 + 0x7e6c) + 0x30);
        if (iVar10 == -1) {
          iVar7 = 0;
        }
        else {
          iVar11 = *(int *)(iVar7 + 0x30);
          if (iVar11 != iVar10) {
            if (iVar11 != -1) {
              *(u32 *)(iVar5 + iVar11 * 8) = 0;
            }
            *(u32 *)(iVar7 + 0x30) =
                 *(u32 *)
                  (*(int *)((*(uint *)(param_1 + 0x7e74) ^ 1) * 4 + param_1 + 0x7e6c) + 0x30);
          }
          iVar5 = 0;
          *(u32 *)(iVar7 + 0x10) = *(u32 *)(iVar7 + 0x14);
          *(u32 *)(iVar7 + 0x18) = 0;
          if (uVar8 != 0) {
            iVar10 = 0;
            iVar11 = 0;
            do {
              RefLoadImage__11CVif1PacketFUsUcUsP1UiUiUiUiUi
                        (iVar7,(*(ushort *)
                                 (camera__4CApp + (*(byte *)(camera__4CApp + 0x394) ^ 1) * 2 + 0x38c
                                 ) & 0x7ff) << 5,0,*(ushort *)(camera__4CApp + 0x348) >> 6,
                         *(int *)(*(int *)(param_1 + 0x134) + *(int *)(iVar7 + 0x30) * 8) +
                         iVar11 * 0x400,(int)(uVar4 * 0x40) >> 4,iVar10,0);
              iVar5 = iVar5 + 1;
              iVar10 = iVar10 + 0x10;
              iVar11 = iVar11 + uVar9;
            } while (iVar5 < (int)uVar8);
          }
          if (*(int *)(iVar7 + 0x18) != 0) {
            uVar6 = *(uint *)(iVar7 + 0x10);
            while ((uVar6 & 0xf) != 0) {
              puVar2 = *(u32 **)(iVar7 + 0x10);
              *(u32 **)(iVar7 + 0x10) = puVar2 + 1;
              *puVar2 = 0;
              uVar6 = *(uint *)(iVar7 + 0x10);
            }
            **(short **)(iVar7 + 0x18) = (short)(uVar6 - (int)*(short **)(iVar7 + 0x18) >> 4) + -1;
          }
          *(u32 *)(iVar7 + 0x18) = *(u32 *)(iVar7 + 0x10);
          puVar2 = *(u32 **)(iVar7 + 0x10);
          *(u32 **)(iVar7 + 0x10) = puVar2 + 1;
          *puVar2 = 0x60000000;
          puVar2 = *(u32 **)(iVar7 + 0x10);
          *(u32 **)(iVar7 + 0x10) = puVar2 + 1;
          *puVar2 = 0;
          sceVif1PkTerminate(iVar7 + 0x10);
          *(uint *)(param_1 + 0x7e74) = *(uint *)(param_1 + 0x7e74) ^ 1;
        }
      }
    }
    else {
      iVar7 = *(int *)(*(int *)(param_1 + 0x7e74) * 4 + param_1 + 0x7e6c);
      *(u32 *)(iVar7 + 0x10) = *(u32 *)(iVar7 + 0x14);
      *(u32 *)(iVar7 + 0x18) = 0;
      if (*(int *)(iVar7 + 0x30) != -1) {
        *(u32 *)(*(int *)(iVar7 + 0x30) * 8 + *(int *)(param_1 + 0x134) + 4) = 0;
        *(u32 *)(iVar7 + 0x30) = 0xffffffff;
      }
      iVar5 = 0;
      if (uVar8 != 0) {
        iVar10 = 0;
        iVar11 = 0;
        do {
          RefLoadImage__11CVif1PacketFUsUcUsP1UiUiUiUiUi
                    (iVar7,(*(ushort *)
                             (camera__4CApp + (*(byte *)(camera__4CApp + 0x394) ^ 1) * 2 + 0x38c) &
                           0x7ff) << 5,0,*(ushort *)(camera__4CApp + 0x348) >> 6,
                     *(int *)(*(int *)(param_1 + 0x134) + *(int *)(param_1 + 0x13c) * 8) +
                     iVar11 * 0x400,(int)(uVar4 * 0x40) >> 4,iVar10,0);
          iVar5 = iVar5 + 1;
          iVar10 = iVar10 + 0x10;
          iVar11 = iVar11 + uVar9;
        } while (iVar5 < (int)uVar8);
      }
      if (*(int *)(iVar7 + 0x18) != 0) {
        uVar6 = *(uint *)(iVar7 + 0x10);
        while ((uVar6 & 0xf) != 0) {
          puVar2 = *(u32 **)(iVar7 + 0x10);
          *(u32 **)(iVar7 + 0x10) = puVar2 + 1;
          *puVar2 = 0;
          uVar6 = *(uint *)(iVar7 + 0x10);
        }
        **(short **)(iVar7 + 0x18) = (short)(uVar6 - (int)*(short **)(iVar7 + 0x18) >> 4) + -1;
      }
      *(u32 *)(iVar7 + 0x18) = *(u32 *)(iVar7 + 0x10);
      puVar2 = *(u32 **)(iVar7 + 0x10);
      *(u32 **)(iVar7 + 0x10) = puVar2 + 1;
      *puVar2 = 0x60000000;
      puVar2 = *(u32 **)(iVar7 + 0x10);
      *(u32 **)(iVar7 + 0x10) = puVar2 + 1;
      *puVar2 = 0;
      sceVif1PkTerminate(iVar7 + 0x10);
      if (*(int *)(param_1 + 0x7e4c) == 0) {
        *(u32 *)(*(int *)((*(uint *)(param_1 + 0x7e74) ^ 1) * 4 + param_1 + 0x7e6c) + 0x30) =
             *(u32 *)(param_1 + 0x13c);
        *(uint *)(param_1 + 0x13c) =
             *(int *)(param_1 + 0x13c) + 1U & *(int *)(param_1 + 0x7e78) - 1U;
      }
      else {
        *(u32 *)(iVar7 + 0x30) = 0xffffffff;
      }
      *(uint *)(param_1 + 0x7e74) = *(uint *)(param_1 + 0x7e74) ^ 1;
    }
  }
  uVar3 = 0;
  if (iVar7 != 0) {
    uVar3 = *(u32 *)(iVar7 + 4);
  }
  return uVar3;
}

/* ---- 0x0038c7a0 size 0xfc  MovieServerHandler::Close(P10_LSDHANDLE)
 *      mangled: Close__18MovieServerHandlerFP10_LSDHANDLE */
u32 Close__18MovieServerHandlerFP10_LSDHANDLE(int param_1)

{
  int iVar1;
  
  if (*(int *)(param_1 + 0x128) != 0) {
    __dla__FPv();
    *(u32 *)(param_1 + 0x128) = 0;
  }
  if (*(int *)(param_1 + 300) != 0) {
    __dla__FPv();
    *(u32 *)(param_1 + 300) = 0;
  }
  if (*(int *)(param_1 + 0x134) != 0) {
    __dla__FPv();
    *(u32 *)(param_1 + 0x134) = 0;
  }
  iVar1 = *(int *)(param_1 + 0x7e6c);
  if (iVar1 != 0) {
    if (iVar1 != 0) {
      (**(code **)(*(int *)(iVar1 + 0xc) + 8))(iVar1,1);
    }
    *(u32 *)(param_1 + 0x7e6c) = 0;
  }
  iVar1 = *(int *)(param_1 + 0x7e70);
  if (iVar1 != 0) {
    if (iVar1 != 0) {
      (**(code **)(*(int *)(iVar1 + 0xc) + 8))(iVar1,1);
    }
    *(u32 *)(param_1 + 0x7e70) = 0;
  }
  iVar1 = *(int *)(param_1 + 0x84);
  if (iVar1 != 0) {
    if (iVar1 != 0) {
      (**(code **)(*(int *)(iVar1 + 0x28) + 8))(iVar1,1);
    }
    *(u32 *)(param_1 + 0x84) = 0;
  }
  return 1;
}

/* ---- 0x0038c900 size 0x1f8  MovieServerHandler::NoDataCallBack(P7sceMpegP13sceMpegCbDataPv)
 *      mangled: NoDataCallBack__18MovieServerHandlerFP7sceMpegP13sceMpegCbDataPv */
int NoDataCallBack__18MovieServerHandlerFP7sceMpegP13sceMpegCbDataPv
              (u64 param_1,u64 param_2,int param_3)

{
  u32 in_zero_lo;
  u32 in_zero_hi;
  u32 in_zero_udw;
  u32 in_register_0000000c;
  u32 uVar1;
  int iVar2;
  u64 uVar3;
  int iVar4;
  
  iVar4 = 0;
  WaitSema(*(u32 *)(param_3 + 0xdc));
  uVar3 = sceDmaGetChan(4);
  if (*(int *)(param_3 + 0x88) != 0) {
    clearBlock__10RingBufferFl(*(u32 *)(param_3 + 0x84),*(int *)(param_3 + 0x88));
  }
  uVar1 = getBufferSerialSize__10RingBufferFli(*(u32 *)(param_3 + 0x84),0x800,1);
  *(u32 *)(param_3 + 0x88) = uVar1;
  if ((*(uint *)(param_3 + 0x88) == 0) || ((*(uint *)(param_3 + 0x88) & 0xf) != 0)) {
    *(u32 *)(param_3 + 0x88) = 0;
  }
  else {
    *(u32 *)(param_3 + 0x90) = in_zero_lo;
    *(u32 *)(param_3 + 0x94) = in_zero_hi;
    *(u32 *)(param_3 + 0x98) = in_zero_udw;
    *(u32 *)(param_3 + 0x9c) = in_register_0000000c;
    *(uint *)(param_3 + 0x90) = *(uint *)(param_3 + 0x88) >> 4;
    uVar1 = 0;
    if ((*(u32 **)(param_3 + 0x84))[4] != 0) {
      uVar1 = **(u32 **)(param_3 + 0x84);
    }
    *(u32 *)(param_3 + 0x94) = uVar1;
    FlushCache(0);
    sceDmaSend(uVar3,param_3 + 0x90);
    iVar4 = 1;
  }
  if ((*(int *)(param_3 + 0x7e48) != 0) && (*(int *)(param_3 + 0x88) == 0)) {
    iVar2 = 0;
    if ((*(int **)(param_3 + 0x84))[4] != 0) {
      iVar2 = **(int **)(param_3 + 0x84);
    }
    if (iVar2 != 0) {
      *(u32 *)(param_3 + 0x90) = in_zero_lo;
      *(u32 *)(param_3 + 0x94) = in_zero_hi;
      *(u32 *)(param_3 + 0x98) = in_zero_udw;
      *(u32 *)(param_3 + 0x9c) = in_register_0000000c;
      *(u32 *)(param_3 + 0x90) = 0x200;
      uVar1 = 0;
      if ((*(u32 **)(param_3 + 0x84))[4] != 0) {
        uVar1 = **(u32 **)(param_3 + 0x84);
      }
      *(u32 *)(param_3 + 0x94) = uVar1;
      FlushCache(0);
      sceDmaSend(uVar3,param_3 + 0x90);
      iVar4 = 1;
    }
  }
  SignalSema(*(u32 *)(param_3 + 0xdc));
  if ((*(int *)(param_3 + 0x88) == 0) && (*(int *)(*(int *)(param_3 + 0x84) + 0x10) == 0)) {
    if (*(int *)(sys__9LSDPlayer + 0x90) == 0) {
      iVar2 = 0;
    }
    else {
      iVar2 = *(int *)(*(int *)(sys__9LSDPlayer + 0x90) + 0x58);
    }
    if (iVar2 != 0) {
      *(u32 *)(param_3 + 0x7e60) = 1;
      sceMpegGetPictureAbort(param_1);
      iVar4 = 1;
    }
  }
  if (iVar4 == 0) {
    SignalSema(*(u32 *)(sys__9LSDPlayer + 0x80));
    Wait__7CThreadFi(app__4CApp,100);
    WaitSema(*(u32 *)(sys__9LSDPlayer + 0x80));
  }
  return iVar4;
}

/* ---- 0x0038cb00 size 0x50  MovieServerHandler::ErrorCallBack(P7sceMpegP13sceMpegCbDataPv)
 *      mangled: ErrorCallBack__18MovieServerHandlerFP7sceMpegP13sceMpegCbDataPv */
u32
ErrorCallBack__18MovieServerHandlerFP7sceMpegP13sceMpegCbDataPv
          (u64 param_1,int param_2,int param_3)

{
  WaitSema(*(u32 *)(param_3 + 0xdc));
  printf((char *)&_2252,*(u32 *)(param_2 + 4));
  SignalSema(*(u32 *)(param_3 + 0xdc));
  return 1;
}

/* ---- 0x0038cb50 size 0x3c  MovieServerHandler::StopDmaCallBack(P7sceMpegP13sceMpegCbDataPv)
 *      mangled: StopDmaCallBack__18MovieServerHandlerFP7sceMpegP13sceMpegCbDataPv */
u32
StopDmaCallBack__18MovieServerHandlerFP7sceMpegP13sceMpegCbDataPv
          (u64 param_1,u64 param_2,int param_3)

{
  WaitSema(*(u32 *)(param_3 + 0xdc));
  sceIpuStopDMA(param_3 + 0xa0);
  SignalSema(*(u32 *)(param_3 + 0xdc));
  return 1;
}

/* ---- 0x0038cb90 size 0x3c  MovieServerHandler::RestartDmaCallBack(P7sceMpegP13sceMpegCbDataPv)
 *      mangled: RestartDmaCallBack__18MovieServerHandlerFP7sceMpegP13sceMpegCbDataPv */
u32
RestartDmaCallBack__18MovieServerHandlerFP7sceMpegP13sceMpegCbDataPv
          (u64 param_1,u64 param_2,int param_3)

{
  WaitSema(*(u32 *)(param_3 + 0xdc));
  sceIpuRestartDMA(param_3 + 0xa0);
  SignalSema(*(u32 *)(param_3 + 0xdc));
  return 1;
}

/* ---- 0x0038cbd0 size 0x4c  MovieServerHandler::TimeStampCallBack(P7sceMpegP13sceMpegCbDataPv)
 *      mangled: TimeStampCallBack__18MovieServerHandlerFP7sceMpegP13sceMpegCbDataPv */
u32
TimeStampCallBack__18MovieServerHandlerFP7sceMpegP13sceMpegCbDataPv
          (u64 param_1,int param_2,int param_3)

{
  WaitSema(*(u32 *)(param_3 + 0xdc));
  *(u64 *)(param_2 + 8) = 0xffffffffffffffff;
  *(u64 *)(param_2 + 0x10) = 0xffffffffffffffff;
  SignalSema(*(u32 *)(param_3 + 0xdc));
  return 1;
}

/* ---- 0x0038cc20 size 0x8  MovieServerHandler::BackGroundCallBack(P7sceMpegP13sceMpegCbDataPv)
 *      mangled: BackGroundCallBack__18MovieServerHandlerFP7sceMpegP13sceMpegCbDataPv */
u32 BackGroundCallBack__18MovieServerHandlerFP7sceMpegP13sceMpegCbDataPv(void)

{
  return 1;
}

/* ---- 0x0038cc30 size 0x8  MovieServerHandler::@20@getPacket(v)
 *      mangled: @20@getPacket__18MovieServerHandlerFv */
u32 _20_getPacket__18MovieServerHandlerFv(int param_1)

{
  ushort uVar1;
  u32 *puVar2;
  u32 uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  int iVar11;
  int iVar12;
  
  iVar5 = param_1 + -0x14;
  uVar1 = *(ushort *)(param_1 + 0x4a);
  uVar7 = (uint)*(ushort *)(param_1 + 0x48);
  uVar4 = (uint)*(ushort *)(camera__4CApp + 0x348);
  uVar10 = (uint)(uVar1 >> 4);
  uVar9 = uVar4;
  if (uVar7 < uVar4) {
    uVar9 = uVar7;
  }
  uVar9 = uVar9 >> 4;
  if (uVar4 <= uVar7) {
    uVar7 = uVar4;
  }
  if (*(ushort *)(camera__4CApp + 0x34a) <= uVar1) {
    uVar1 = *(ushort *)(camera__4CApp + 0x34a);
  }
  uVar4 = (uint)uVar1;
  iVar8 = 0;
  if ((long)((ulong)*(byte *)(param_1 + 0x40) << 0x3b) < 0) {
    iVar6 = *(int *)(param_1 + 0x120) + 4;
    if ((*(int *)(iVar6 + *(int *)(param_1 + 0x128) * 8) != 0) &&
       (iVar11 = (*(int *)(param_1 + 0x128) + 1U & *(int *)(param_1 + 0x7e64) - 1U) * 8,
       *(int *)(iVar6 + iVar11) != 0)) {
      iVar8 = *(int *)(*(int *)(param_1 + 0x7e60) * 4 + iVar5 + 0x7e6c);
      *(u32 *)(iVar8 + 0x10) = *(u32 *)(iVar8 + 0x14);
      *(u32 *)(iVar8 + 0x18) = 0;
      if (*(int *)(iVar8 + 0x30) != -1) {
        *(u32 *)(*(int *)(iVar8 + 0x30) * 8 + *(int *)(param_1 + 0x120) + 4) = 0;
        *(u32 *)
         ((*(int *)(iVar8 + 0x30) + 1U & *(int *)(param_1 + 0x7e64) - 1U) * 8 +
          *(int *)(param_1 + 0x120) + 4) = 0;
        *(u32 *)(iVar8 + 0x30) = 0xffffffff;
      }
      iVar5 = 0;
      if (uVar9 != 0) {
        iVar6 = 0;
        iVar12 = 0;
        do {
          RefLoadImage__11CVif1PacketFUsUcUsP1UiUiUiUiUi
                    (iVar8,(*(ushort *)
                             (camera__4CApp + (*(byte *)(camera__4CApp + 0x394) ^ 1) * 2 + 0x38c) &
                           0x7ff) << 5,0,*(ushort *)(camera__4CApp + 0x348) >> 6,
                     *(int *)(*(int *)(param_1 + 0x120) + *(int *)(param_1 + 0x128) * 8) +
                     iVar12 * 0x400,(int)(uVar4 * 0x40) >> 4,iVar6,0);
          iVar5 = iVar5 + 1;
          iVar6 = iVar6 + 0x10;
          iVar12 = iVar12 + uVar10;
        } while (iVar5 < (int)uVar9);
      }
      iVar5 = 0;
      if (uVar9 != 0) {
        iVar6 = 0;
        do {
          RefLoadImage__11CVif1PacketFUsUcUsP1UiUiUiUiUi
                    (iVar8,(*(ushort *)
                             (camera__4CApp + (*(byte *)(camera__4CApp + 0x394) ^ 1) * 2 + 0x38c) &
                           0x7ff) << 5,0,*(ushort *)(camera__4CApp + 0x348) >> 6,
                     *(int *)(iVar11 + *(int *)(param_1 + 0x120)) + iVar6 * 0x400,
                     (int)(uVar4 * 0x40) >> 4,uVar7,0);
          iVar5 = iVar5 + 1;
          uVar7 = uVar7 + 0x10;
          iVar6 = iVar6 + uVar10;
        } while (iVar5 < (int)uVar9);
      }
      if (*(int *)(iVar8 + 0x18) != 0) {
        uVar7 = *(uint *)(iVar8 + 0x10);
        while ((uVar7 & 0xf) != 0) {
          puVar2 = *(u32 **)(iVar8 + 0x10);
          *(u32 **)(iVar8 + 0x10) = puVar2 + 1;
          *puVar2 = 0;
          uVar7 = *(uint *)(iVar8 + 0x10);
        }
        **(short **)(iVar8 + 0x18) = (short)(uVar7 - (int)*(short **)(iVar8 + 0x18) >> 4) + -1;
      }
      *(u32 *)(iVar8 + 0x18) = *(u32 *)(iVar8 + 0x10);
      puVar2 = *(u32 **)(iVar8 + 0x10);
      *(u32 **)(iVar8 + 0x10) = puVar2 + 1;
      *puVar2 = 0x60000000;
      puVar2 = *(u32 **)(iVar8 + 0x10);
      *(u32 **)(iVar8 + 0x10) = puVar2 + 1;
      *puVar2 = 0;
      sceVif1PkTerminate(iVar8 + 0x10);
      *(uint *)(param_1 + 0x7e60) = *(uint *)(param_1 + 0x7e60) ^ 1;
      iVar5 = *(int *)(param_1 + 0x7e3c) + 1;
      *(int *)(param_1 + 0x7e3c) = iVar5;
      if (1 < iVar5) {
        if (*(int *)(param_1 + 0x7e38) == 0) {
          *(u32 *)(iVar8 + 0x30) = *(u32 *)(param_1 + 0x128);
          *(uint *)(param_1 + 0x128) =
               *(int *)(param_1 + 0x128) + 2U & *(int *)(param_1 + 0x7e64) - 1U;
          *(u32 *)(param_1 + 0x7e3c) = 0;
        }
        else {
          *(u32 *)(iVar8 + 0x30) = 0xffffffff;
        }
      }
    }
  }
  else {
    iVar6 = *(int *)(param_1 + 0x120) + 4;
    if (*(int *)(iVar6 + *(int *)(param_1 + 0x128) * 8) == 0) {
      uVar7 = *(uint *)(param_1 + 0x7e60);
      if (uVar7 != 0xffffffff) {
        iVar8 = *(int *)(uVar7 * 4 + iVar5 + 0x7e6c);
        iVar11 = *(int *)(*(int *)((uVar7 ^ 1) * 4 + iVar5 + 0x7e6c) + 0x30);
        if (iVar11 == -1) {
          iVar8 = 0;
        }
        else {
          iVar12 = *(int *)(iVar8 + 0x30);
          if (iVar12 != iVar11) {
            if (iVar12 != -1) {
              *(u32 *)(iVar6 + iVar12 * 8) = 0;
            }
            *(u32 *)(iVar8 + 0x30) =
                 *(u32 *)
                  (*(int *)((*(uint *)(param_1 + 0x7e60) ^ 1) * 4 + iVar5 + 0x7e6c) + 0x30);
          }
          iVar5 = 0;
          *(u32 *)(iVar8 + 0x10) = *(u32 *)(iVar8 + 0x14);
          *(u32 *)(iVar8 + 0x18) = 0;
          if (uVar9 != 0) {
            iVar6 = 0;
            iVar11 = 0;
            do {
              RefLoadImage__11CVif1PacketFUsUcUsP1UiUiUiUiUi
                        (iVar8,(*(ushort *)
                                 (camera__4CApp + (*(byte *)(camera__4CApp + 0x394) ^ 1) * 2 + 0x38c
                                 ) & 0x7ff) << 5,0,*(ushort *)(camera__4CApp + 0x348) >> 6,
                         *(int *)(*(int *)(param_1 + 0x120) + *(int *)(iVar8 + 0x30) * 8) +
                         iVar11 * 0x400,(int)(uVar4 * 0x40) >> 4,iVar6,0);
              iVar5 = iVar5 + 1;
              iVar6 = iVar6 + 0x10;
              iVar11 = iVar11 + uVar10;
            } while (iVar5 < (int)uVar9);
          }
          if (*(int *)(iVar8 + 0x18) != 0) {
            uVar7 = *(uint *)(iVar8 + 0x10);
            while ((uVar7 & 0xf) != 0) {
              puVar2 = *(u32 **)(iVar8 + 0x10);
              *(u32 **)(iVar8 + 0x10) = puVar2 + 1;
              *puVar2 = 0;
              uVar7 = *(uint *)(iVar8 + 0x10);
            }
            **(short **)(iVar8 + 0x18) = (short)(uVar7 - (int)*(short **)(iVar8 + 0x18) >> 4) + -1;
          }
          *(u32 *)(iVar8 + 0x18) = *(u32 *)(iVar8 + 0x10);
          puVar2 = *(u32 **)(iVar8 + 0x10);
          *(u32 **)(iVar8 + 0x10) = puVar2 + 1;
          *puVar2 = 0x60000000;
          puVar2 = *(u32 **)(iVar8 + 0x10);
          *(u32 **)(iVar8 + 0x10) = puVar2 + 1;
          *puVar2 = 0;
          sceVif1PkTerminate(iVar8 + 0x10);
          *(uint *)(param_1 + 0x7e60) = *(uint *)(param_1 + 0x7e60) ^ 1;
        }
      }
    }
    else {
      iVar8 = *(int *)(*(int *)(param_1 + 0x7e60) * 4 + iVar5 + 0x7e6c);
      *(u32 *)(iVar8 + 0x10) = *(u32 *)(iVar8 + 0x14);
      *(u32 *)(iVar8 + 0x18) = 0;
      if (*(int *)(iVar8 + 0x30) != -1) {
        *(u32 *)(*(int *)(iVar8 + 0x30) * 8 + *(int *)(param_1 + 0x120) + 4) = 0;
        *(u32 *)(iVar8 + 0x30) = 0xffffffff;
      }
      iVar6 = 0;
      if (uVar9 != 0) {
        iVar11 = 0;
        iVar12 = 0;
        do {
          RefLoadImage__11CVif1PacketFUsUcUsP1UiUiUiUiUi
                    (iVar8,(*(ushort *)
                             (camera__4CApp + (*(byte *)(camera__4CApp + 0x394) ^ 1) * 2 + 0x38c) &
                           0x7ff) << 5,0,*(ushort *)(camera__4CApp + 0x348) >> 6,
                     *(int *)(*(int *)(param_1 + 0x120) + *(int *)(param_1 + 0x128) * 8) +
                     iVar12 * 0x400,(int)(uVar4 * 0x40) >> 4,iVar11,0);
          iVar6 = iVar6 + 1;
          iVar11 = iVar11 + 0x10;
          iVar12 = iVar12 + uVar10;
        } while (iVar6 < (int)uVar9);
      }
      if (*(int *)(iVar8 + 0x18) != 0) {
        uVar7 = *(uint *)(iVar8 + 0x10);
        while ((uVar7 & 0xf) != 0) {
          puVar2 = *(u32 **)(iVar8 + 0x10);
          *(u32 **)(iVar8 + 0x10) = puVar2 + 1;
          *puVar2 = 0;
          uVar7 = *(uint *)(iVar8 + 0x10);
        }
        **(short **)(iVar8 + 0x18) = (short)(uVar7 - (int)*(short **)(iVar8 + 0x18) >> 4) + -1;
      }
      *(u32 *)(iVar8 + 0x18) = *(u32 *)(iVar8 + 0x10);
      puVar2 = *(u32 **)(iVar8 + 0x10);
      *(u32 **)(iVar8 + 0x10) = puVar2 + 1;
      *puVar2 = 0x60000000;
      puVar2 = *(u32 **)(iVar8 + 0x10);
      *(u32 **)(iVar8 + 0x10) = puVar2 + 1;
      *puVar2 = 0;
      sceVif1PkTerminate(iVar8 + 0x10);
      if (*(int *)(param_1 + 0x7e38) == 0) {
        *(u32 *)(*(int *)((*(uint *)(param_1 + 0x7e60) ^ 1) * 4 + iVar5 + 0x7e6c) + 0x30) =
             *(u32 *)(param_1 + 0x128);
        *(uint *)(param_1 + 0x128) =
             *(int *)(param_1 + 0x128) + 1U & *(int *)(param_1 + 0x7e64) - 1U;
      }
      else {
        *(u32 *)(iVar8 + 0x30) = 0xffffffff;
      }
      *(uint *)(param_1 + 0x7e60) = *(uint *)(param_1 + 0x7e60) ^ 1;
    }
  }
  uVar3 = 0;
  if (iVar8 != 0) {
    uVar3 = *(u32 *)(iVar8 + 4);
  }
  return uVar3;
}

/* ---- 0x0038cc40 size 0x8  MovieServerHandler::@20@__dt(v)
 *      mangled: @20@__dt__18MovieServerHandlerFv */
int _20___dt__18MovieServerHandlerFv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x14;
  if (iVar1 != 0) {
    *(u8 **)(param_1 + -4) = __vt__18MovieServerHandler;
    *(u32 *)(param_1 + 0x10) = 0x40702c;
    *(u32 *)(param_1 + 0x1c) = 0x40703c;
    if (iVar1 != -0x28) {
      *(u8 **)(param_1 + 0x1c) = __vt__17DelayDeleteObject;
    }
    __dt__8VIF1PrimFv(param_1,0);
    __dt__16LSDDeviceHandlerFv(iVar1,0);
    if (0 < param_2) {
      __dl__FPv(iVar1);
    }
  }
  return iVar1;
}

/* ---- 0x0038cc50 size 0x8  MovieServerHandler::@40@__dt(v)
 *      mangled: @40@__dt__18MovieServerHandlerFv */
int _40___dt__18MovieServerHandlerFv(int param_1,short param_2)

{
  int iVar1;
  
  iVar1 = param_1 + -0x28;
  if (iVar1 != 0) {
    *(u8 **)(param_1 + -0x18) = __vt__18MovieServerHandler;
    *(u32 *)(param_1 + -4) = 0x40702c;
    *(u32 *)(param_1 + 8) = 0x40703c;
    if (iVar1 != -0x28) {
      *(u8 **)(param_1 + 8) = __vt__17DelayDeleteObject;
    }
    __dt__8VIF1PrimFv(param_1 + -0x14,0);
    __dt__16LSDDeviceHandlerFv(iVar1,0);
    if (0 < param_2) {
      __dl__FPv(iVar1);
    }
  }
  return iVar1;
}

