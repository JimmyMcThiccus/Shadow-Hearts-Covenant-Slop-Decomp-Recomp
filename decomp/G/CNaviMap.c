/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CNaviMap   functions: 32
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CNaviMap.md).
 */

/* JP: 0x004b0660  CNaviMap::AttachFrame(int, Frame*)   [AttachFrame__8CNaviMapFiP5Frame]  size=0x44 */
void AttachFrame__8CNaviMapFiP5Frame(int param_1,int param_2,undefined4 param_3)

{
  if (param_2 < 4) {
    *(undefined4 *)(param_1 + param_2 * 4 + 0x6c) = param_3;
  }
  return;
}

/* JP: 0x004cf1a0  CNaviMap::CNaviMap()   [__ct__8CNaviMapFv]  size=0x140 */
int __ct__8CNaviMapFv(int param_1)

{
  __ct__17DelayDeleteObjectFv(param_1);
  *(undefined1 **)(param_1 + 8) = &__vt__8CNaviMap;
  __ct__9_NaviWorkFv(param_1 + 0x10);
  __ct__6MatrixFv(param_1 + 0xd0);
  __ct__6CImageFv(param_1 + 0x110);
  memset(param_1 + 0x10,0,0xc0);
  *(undefined4 *)(param_1 + 0x8c) = 0x3fc00000;
  *(undefined4 *)(param_1 + 0x94) = 0x40000000;
  *(undefined4 *)(param_1 + 0x9c) = 0x10;
  *(undefined4 *)(param_1 + 0xa0) = 0x10;
  *(undefined4 *)(param_1 + 0xa4) = 0x6c;
  *(undefined4 *)(param_1 + 0xa8) = 0x6c;
  *(undefined1 *)(param_1 + 0xc1) = 0xb;
  *(byte *)(param_1 + 0xc0) = *(byte *)(param_1 + 0xc0) & 0xfc | 2;
  *(undefined4 *)(param_1 + 0x54) = 0x80f0f0f0;
  *(undefined4 *)(param_1 + 100) = 0x80000080;
  *(undefined4 *)(param_1 + 0x68) = 0x800040f0;
  *(undefined4 *)(param_1 + 0x98) = 0x42480000;
  return param_1;
}

/* JP: 0x004cf340  CNaviMap::Release()   [Release__8CNaviMapFv]  size=0xbc */
void Release__8CNaviMapFv(int param_1)

{
  int iVar1;
  
  if (*(int *)(param_1 + 0xac) != 0) {
    iVar1 = *(int *)(param_1 + 0xac);
    if (iVar1 != 0) {
      (**(code **)(*(int *)(iVar1 + 0x10) + 8))(iVar1,1);
    }
    *(undefined4 *)(param_1 + 0xac) = 0;
  }
  if (*(int *)(param_1 + 0x7c) != 0) {
    __dt__9BufMemoryFv(*(undefined4 *)(param_1 + 0x7c),1);
    *(undefined4 *)(param_1 + 0x7c) = 0;
  }
  if (*(int *)(param_1 + 0xb4) != 0) {
    __dl__FPv(*(undefined4 *)(param_1 + 0xb4));
    *(undefined4 *)(param_1 + 0xb4) = 0;
  }
  return;
}

/* JP: 0x004cf400  CNaviMap::Delete()   [Delete__8CNaviMapFv]  size=0x40 */
void Delete__8CNaviMapFv(int param_1)

{
  Clr__8CNaviMapFi(param_1,1);
  (**(code **)(*(int *)(param_1 + 8) + 0xc))();
  return;
}

/* JP: 0x004cf440  CNaviMap::SetData(_NaviMapDataHdr*)   [SetData__8CNaviMapFP15_NaviMapDataHdr]  size=0x2e4 */
/* WARNING: Removing unreachable block (ram,0x004cf5f4) */

void SetData__8CNaviMapFP15_NaviMapDataHdr(int param_1,int param_2)

{
  ushort uVar1;
  undefined1 uVar2;
  undefined2 *puVar3;
  float fStack_24;
  
  maxPkt = 0;
  *(int *)(param_1 + 0x80) = param_2;
  *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(param_2 + 0x2c);
  *(undefined4 *)(param_1 + 0x58) = *(undefined4 *)(param_2 + 0x28);
  *(undefined4 *)(param_1 + 0x5c) = *(undefined4 *)(param_2 + 0x24);
  *(undefined4 *)(param_1 + 0x60) = *(undefined4 *)(param_2 + 0x20);
  puVar3 = (undefined2 *)
           ((uint)*(ushort *)(param_2 + 0x1c) * 0x10 + param_2 + (uint)*(ushort *)(param_2 + 6));
  uVar1 = puVar3[1];
  *(byte *)(param_1 + 0xc0) =
       *(byte *)(param_1 + 0xc0) & 0xdf |
       (byte)((uint)(((ulong)*(byte *)(param_2 + 0x1f) << 0x3b) >> 0x3f) << 5);
  *(byte *)(param_1 + 0xc0) =
       *(byte *)(param_1 + 0xc0) & 0xf7 |
       (byte)((uint)(((ulong)*(byte *)(param_2 + 0x1f) << 0x3a) >> 0x3f) << 3);
  *(byte *)(param_1 + 0xc3) = (byte)(((ulong)*(byte *)(param_2 + 0x1f) << 0x3c) >> 0x3e);
  Release__6CImageFv(param_1 + 0x110);
  Create__6CImageFiiiPUc(param_1 + 0x110,puVar3[2],puVar3[3],*puVar3,puVar3 + 8 + (uint)uVar1 * 2);
  CreatePal__6CImageFiPv(param_1 + 0x110,0,puVar3 + 8);
  uVar2 = GetPktSize__7P2ImageFP6CImage(param_1 + 0x110);
  *(undefined1 *)(param_1 + 0xc2) = uVar2;
  fStack_24 = (float)*(byte *)(param_2 + 0x34) * 0.0625;
  if (fStack_24 == 0.0) {
    fStack_24 = 1.5;
  }
  *(float *)(param_1 + 0x90) = fStack_24;
  *(float *)(param_1 + 0x8c) = fStack_24;
  *(undefined4 *)(param_1 + 0x50) = 0x30808080;
  *(float *)(param_1 + 0x40) =
       *(float *)(param_2 + 0x10) + (float)(*(ushort *)(param_2 + 0xc) + 1) * 5.0;
  *(float *)(param_1 + 0x48) =
       *(float *)(param_2 + 0x14) + (float)(*(ushort *)(param_2 + 0xe) + 1) * 5.0;
  *(undefined4 *)(param_1 + 0x44) = 0;
  *(undefined4 *)(param_1 + 0x4c) = 0x3f800000;
  return;
}

/* JP: 0x004cf730  CNaviMap::DspMesh(int, int)   [DspMesh__8CNaviMapFii]  size=0xf0 */
void DspMesh__8CNaviMapFii(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = *(int *)(param_1 + 0x80);
  if ((iVar1 != 0) && (*(short *)(iVar1 + 4) != 0)) {
    iVar2 = iVar1 + (uint)*(ushort *)(iVar1 + 6);
    for (iVar3 = 0; iVar3 < (int)(uint)*(ushort *)(iVar1 + 0x18); iVar3 = iVar3 + 1) {
      if (param_2 == iVar3) {
        *(byte *)(iVar2 + 7) = *(byte *)(iVar2 + 7) & 0xfe | 1;
      }
      if (param_3 == iVar3) {
        *(byte *)(iVar2 + 7) = *(byte *)(iVar2 + 7) & 0xfe;
      }
      iVar2 = iVar2 + (uint)((ulong)((long)*(int *)(iVar2 + 4) << 0x28) >> 0x28) * 0x10;
    }
  }
  return;
}

/* JP: 0x004cf820  CNaviMap::isDsp()   [isDsp__8CNaviMapFv]  size=0x4c */
bool isDsp__8CNaviMapFv(int param_1)

{
  bool bVar1;
  
  if (*(int *)(param_1 + 0x80) == 0) {
    bVar1 = false;
  }
  else {
    bVar1 = (*(byte *)(param_1 + 0xc0) & 3) == 3;
  }
  return bVar1;
}

/* JP: 0x004cf870  CNaviMap::DspClr(int)   [DspClr__8CNaviMapFi]  size=0xbc */
void DspClr__8CNaviMapFi(int param_1,int param_2)

{
  byte bVar1;
  
  bVar1 = *(byte *)(param_1 + 0xc0);
  *(byte *)(param_1 + 0xc0) = *(byte *)(param_1 + 0xc0) & 0xfc | (byte)param_2 & 3;
  if ((((bVar1 & 3) == 3) && (param_2 != 3)) &&
     ((long)((ulong)*(byte *)(param_1 + 0xc0) << 0x3d) < 0)) {
    Clr__5P2PktFv(*(undefined4 *)(param_1 + 0xac));
    *(byte *)(param_1 + 0xc0) = *(byte *)(param_1 + 0xc0) & 0xfb;
  }
  return;
}

/* JP: 0x004cf930  CNaviMap::Dsp(int)   [Dsp__8CNaviMapFi]  size=0x48 */
void Dsp__8CNaviMapFi(int param_1,byte param_2)

{
  *(byte *)(param_1 + 0xc0) =
       *(byte *)(param_1 + 0xc0) & 0xfc | *(byte *)(param_1 + 0xc0) & 3 | param_2 & 3;
  return;
}

/* JP: 0x004cf980  CNaviMap::Clr(int)   [Clr__8CNaviMapFi]  size=0xcc */
void Clr__8CNaviMapFi(int param_1,int param_2)

{
  byte bVar1;
  
  bVar1 = *(byte *)(param_1 + 0xc0);
  *(byte *)(param_1 + 0xc0) =
       *(byte *)(param_1 + 0xc0) & 0xfc | *(byte *)(param_1 + 0xc0) & 3 & ~(byte)param_2;
  if ((((bVar1 & 3) == 3) && (param_2 != 0)) &&
     ((long)((ulong)*(byte *)(param_1 + 0xc0) << 0x3d) < 0)) {
    Clr__5P2PktFv(*(undefined4 *)(param_1 + 0xac));
    *(byte *)(param_1 + 0xc0) = *(byte *)(param_1 + 0xc0) & 0xfb;
  }
  return;
}

/* JP: 0x004cfa50  CNaviMap::Update(float, FVector*, float)   [Update__8CNaviMapFfP7FVectorf]  size=0x984 */
/* WARNING: Removing unreachable block (ram,0x004cfc58) */
/* WARNING: Removing unreachable block (ram,0x004cfeb4) */

void Update__8CNaviMapFfP7FVectorf(float param_1,undefined4 param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  long lVar4;
  undefined8 uVar5;
  int iVar6;
  int iVar7;
  undefined1 auStack_120 [16];
  undefined1 auStack_110 [16];
  undefined1 auStack_100 [16];
  undefined1 auStack_f0 [16];
  undefined1 auStack_e0 [16];
  float afStack_d0 [2];
  float fStack_c8;
  undefined1 auStack_c0 [12];
  undefined4 uStack_b4;
  undefined1 auStack_b0 [76];
  float fStack_64;
  float fStack_60;
  float fStack_5c;
  float fStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  float fStack_4c;
  float fStack_48;
  float fStack_44;
  int iStack_40;
  float fStack_30;
  undefined4 uStack_20;
  undefined4 uStack_10;
  
  iStack_40 = param_3;
  fStack_30 = param_1;
  uStack_20 = param_4;
  uStack_10 = param_2;
  __as__7FVectorFRC7FVector(param_3 + 0x30,param_4);
  *(undefined4 *)(iStack_40 + 0x88) = uStack_10;
  if (-1 < (long)((ulong)*(byte *)(iStack_40 + 0xc0) << 0x3b)) {
    *(undefined4 *)(iStack_40 + 0x84) = uStack_10;
  }
  __apl__7FVectorFRC7FVector(iStack_40 + 0x30,iStack_40 + 0x10);
  lVar4 = isDsp__8CNaviMapFv(iStack_40);
  if (lVar4 != 0) {
    *(float *)(iStack_40 + 0xbc) = *(float *)(iStack_40 + 0xbc) + fStack_30;
    if (1.0 < *(float *)(iStack_40 + 0xbc)) {
      *(float *)(iStack_40 + 0xbc) = *(float *)(iStack_40 + 0xbc) - 1.0;
    }
    __as__7FVectorFRC7FVector(iStack_40 + 0x20,iStack_40 + 0x30);
    *(undefined4 *)(iStack_40 + 0x24) = 0;
    iVar1 = *(int *)(iStack_40 + 0x80);
    UnitMatrix__6MatrixFv(iStack_40 + 0xd0);
    __ct__6MatrixFv(auStack_b0);
    UnitMatrix__6MatrixFv(auStack_b0);
    __ct__7FVectorFv(auStack_c0);
    uVar5 = __ct__7IVectorFiiii(auStack_f0,(int)*(float *)(iStack_40 + 0x24),0,0,0);
    __as__7FVectorFRC7IVector(auStack_c0,uVar5);
    uVar5 = __ct__7IVectorFiiii(auStack_100,0xffffffffffffffff,0,0,0);
    __as__7FVectorFRC7IVector(auStack_c0,uVar5);
    uStack_b4 = 0x3f800000;
    SetPos__6MatrixFRC7FVector(auStack_b0,auStack_c0);
    fStack_44 = (float)*(byte *)(iStack_40 + 0xc3) * 1.570796;
    if ((long)((ulong)*(byte *)(iStack_40 + 0xc0) << 0x3b) < 0) {
      fStack_44 = -*(float *)(iStack_40 + 0x84);
    }
    if ((3.141592 <= fStack_44) && (fStack_44 = fStack_44 - 6.283184, 3.141592 <= fStack_44)) {
      fStack_44 = fStack_44 - 6.283184;
    }
    if ((fStack_44 <= -3.141592) && (fStack_44 = fStack_44 + 6.283184, fStack_44 <= -3.141592)) {
      fStack_44 = fStack_44 + 6.283184;
    }
    RotYMatrix__6MatrixFf(fStack_44,iStack_40 + 0xd0);
    RotXMatrix__6MatrixFf(0x3fc90fd8,iStack_40 + 0xd0);
    if (-1 < (long)((ulong)*(byte *)(iStack_40 + 0xc0) << 0x3b)) {
      fStack_48 = (float)(*(ushort *)(iVar1 + 0xc) + 1) * 10.0;
      fStack_4c = (float)(*(ushort *)(iVar1 + 0xe) + 1) * 10.0;
      uStack_50 = *(undefined4 *)(*(int *)(iStack_40 + 0x80) + 0x10);
      uStack_54 = *(undefined4 *)(*(int *)(iStack_40 + 0x80) + 0x14);
      fStack_58 = fStack_48 * 0.5;
      fStack_5c = fStack_4c * 0.5;
      fStack_44 = (float)*(byte *)(iStack_40 + 0xc3) * 1.570796;
      if (3.141592 <= fStack_44) {
        fStack_44 = fStack_44 - 6.283184;
      }
      UnitMatrix__6MatrixFv(auStack_b0);
      RotYMatrix__6MatrixFf(fStack_44,auStack_b0);
      __ct__7FVectorFv(afStack_d0);
      __mi__7FVectorCFRC7FVector(auStack_110,iStack_40 + 0x20,iStack_40 + 0x40);
      __as__7FVectorFRC7FVector(afStack_d0,auStack_110);
      iVar6 = (int)((float)(*(int *)(iStack_40 + 0xa4) + -0x30) * *(float *)(iStack_40 + 0x8c));
      iVar7 = (int)((float)(*(int *)(iStack_40 + 0xa8) + -0x30) * *(float *)(iStack_40 + 0x8c));
      if (fStack_48 < (float)iVar6) {
        afStack_d0[0] = 0.0;
      }
      else {
        fStack_60 = (float)iVar6 * 0.5;
        if (afStack_d0[0] - fStack_60 < -fStack_58) {
          afStack_d0[0] = fStack_60 - fStack_58;
        }
        else if (fStack_58 < afStack_d0[0] + fStack_60) {
          afStack_d0[0] = fStack_58 - fStack_60;
        }
      }
      if (fStack_4c < (float)iVar7) {
        fStack_c8 = 0.0;
      }
      else {
        fStack_64 = (float)iVar7 * 0.5;
        if (fStack_c8 - fStack_64 < -fStack_5c) {
          fStack_c8 = fStack_64 - fStack_5c;
        }
        else if (fStack_5c < fStack_c8 + fStack_64) {
          fStack_c8 = fStack_5c - fStack_64;
        }
      }
      ApplyMatrix__6MatrixCFRC7FVector(auStack_120,auStack_b0,afStack_d0);
      __as__7FVectorFRC7FVector(afStack_d0,auStack_120);
      *(float *)(iStack_40 + 0x20) = afStack_d0[0];
      *(float *)(iStack_40 + 0x24) = -fStack_c8;
      *(undefined4 *)(iStack_40 + 0x28) = 0;
    }
    iVar6 = *(int *)(iStack_40 + 0xac);
    if (iVar6 == 0) {
      uVar2 = 0;
      if (*(short *)(iVar1 + 4) == 0) {
        uVar2 = (uint)*(ushort *)(iVar1 + 0x1a);
      }
      else {
        iVar6 = iVar1 + (uint)*(ushort *)(iVar1 + 6);
        for (iVar7 = 0; iVar7 < (int)(uint)*(ushort *)(iVar1 + 0x18); iVar7 = iVar7 + 1) {
          if ((*(byte *)(iVar6 + 7) & 1) != 0) {
            uVar2 = uVar2 + *(ushort *)(iVar6 + 2);
          }
          iVar6 = iVar6 + (uint)((ulong)((long)*(int *)(iVar6 + 4) << 0x28) >> 0x28) * 0x10;
        }
      }
      lVar4 = __nw__FUi(0x2c);
      iVar6 = 0;
      if (lVar4 != 0) {
        iVar6 = __ct__5P2PktFv(lVar4);
      }
      *(int *)(iStack_40 + 0xac) = iVar6;
      Create__5P2PktFii(iVar6,uVar2 * 3 + 0x200,1);
      SetOwner__5P2PktFPFPv_vPv(iVar6,0x4d0530,iStack_40);
      __ct__11GsxFrameBufFv(auStack_e0);
      *(undefined4 *)(iStack_40 + 0xb0) = 0;
      lVar4 = Create__11GsxFrameBufFb6GS_PSMUiUi(auStack_e0,1,1,0x200,0x1c0);
      if (lVar4 != 0) {
        uVar3 = GetBufEntry__11GsxFrameBufFv(auStack_e0);
        *(undefined4 *)(iStack_40 + 0xb0) = uVar3;
        Release__11GsxFrameBufFv(auStack_e0);
      }
      __dt__11GsxFrameBufFv(auStack_e0,0xffffffffffffffff);
    }
    if (((*(byte *)(iStack_40 + 0xc0) & 3) == 3) &&
       (-1 < (long)((ulong)*(byte *)(iStack_40 + 0xc0) << 0x3d))) {
      *(byte *)(iVar6 + 0x1c) =
           *(byte *)(iVar6 + 0x1c) & 0x83 | (*(byte *)(iStack_40 + 0xc1) & 0x1f) << 2;
      Dsp__5P2PktFv(iVar6);
      *(byte *)(iStack_40 + 0xc0) = *(byte *)(iStack_40 + 0xc0) & 0xfb | 4;
    }
  }
  return;
}

/* JP: 0x004d0530  CNaviMap::MakePacketS(void*)   [MakePacketS__8CNaviMapFPv]  size=0x28 */
void MakePacketS__8CNaviMapFPv(undefined4 param_1)

{
  MakePacket__8CNaviMapFv(param_1);
  return;
}

/* JP: 0x004d06b0  CNaviMap::GetPolyColor(FVector*)   [GetPolyColor__8CNaviMapFP7FVector]  size=0x360 */
uint GetPolyColor__8CNaviMapFP7FVector(int param_1,undefined4 param_2)

{
  int iVar1;
  uint uVar2;
  undefined1 auStack_a0 [16];
  undefined1 auStack_90 [16];
  undefined1 auStack_80 [16];
  undefined1 auStack_70 [16];
  undefined1 auStack_60 [12];
  float fStack_54;
  float fStack_50;
  float fStack_4c;
  float fStack_48;
  float fStack_44;
  undefined1 auStack_40 [4];
  float fStack_3c;
  float fStack_34;
  float fStack_28;
  float fStack_24;
  int iStack_20;
  undefined4 uStack_10;
  
  iStack_20 = param_1;
  uStack_10 = param_2;
  __ct__7FVectorFv(auStack_40);
  __ct__7FVectorFv(&fStack_50);
  __ct__7FVectorFv(auStack_60);
  __mi__7FVectorCFRC7FVector(auStack_70,uStack_10,iStack_20 + 0x30);
  __as__7FVectorFRC7FVector(auStack_40,auStack_70);
  fStack_24 = fStack_3c * 0.05;
  if (fStack_24 < -1.0) {
    fStack_24 = -1.0;
  }
  if (1.0 < fStack_24) {
    fStack_24 = 1.0;
  }
  if ((long)((ulong)*(byte *)(iStack_20 + 0xc0) << 0x3a) < 0) {
    fStack_24 = 0.0;
  }
  fStack_28 = (float)sinf(fStack_24 * 1.570796);
  iVar1 = 2;
  if (fStack_24 < 0.0) {
    iVar1 = 0;
    fStack_24 = -fStack_24;
    fStack_28 = -fStack_28;
  }
  else {
    fStack_28 = fStack_24;
  }
  GetColVector__FP7FVectorUi(auStack_40,*(undefined4 *)(iStack_20 + 0x5c));
  GetColVector__FP7FVectorUi(&fStack_50,*(undefined4 *)(iStack_20 + iVar1 * 4 + 0x58));
  __mi__7FVectorCFRC7FVector(auStack_90,&fStack_50,auStack_40);
  __ml__7FVectorCFf(fStack_28,auStack_80,auStack_90);
  __as__7FVectorFRC7FVector(auStack_60,auStack_80);
  fStack_54 = fStack_24 * (fStack_44 - fStack_34);
  __pl__7FVectorCFRC7FVector(auStack_a0,auStack_40,auStack_60);
  __as__7FVectorFRC7FVector(&fStack_50,auStack_a0);
  if (fStack_50 < 2.1474836e+09) {
    uVar2 = (uint)fStack_50;
  }
  else {
    uVar2 = (int)(fStack_50 - 2.1474836e+09) | 0x80000000;
  }
  if (2.1474836e+09 <= fStack_4c) {
    fStack_4c = fStack_4c - 2.1474836e+09;
  }
  if (2.1474836e+09 <= fStack_48) {
    fStack_48 = fStack_48 - 2.1474836e+09;
  }
  fStack_34 = fStack_34 + fStack_54;
  if (2.1474836e+09 <= fStack_34) {
    fStack_34 = fStack_34 - 2.1474836e+09;
  }
  return uVar2 | (int)fStack_4c << 8 | (int)fStack_34 << 0x18 | (int)fStack_48 << 0x10;
}

/* JP: 0x004d0a10  CNaviMap::MakePacket()   [MakePacket__8CNaviMapFv]  size=0xb44 */
void MakePacket__8CNaviMapFv(int param_1)

{
  undefined4 uVar1;
  undefined8 *puVar2;
  int iVar3;
  int iVar4;
  undefined8 uVar5;
  ulong uVar6;
  uint uVar7;
  undefined2 uVar8;
  short sVar9;
  undefined2 uVar10;
  short sVar11;
  int iStack_40;
  uint uStack_3c;
  int iStack_38;
  int iStack_34;
  int iStack_30;
  int iStack_2c;
  int iStack_28;
  int iStack_24;
  int iStack_20;
  int iStack_1c;
  undefined4 uStack_18;
  undefined8 *puStack_14;
  int iStack_10;
  
  uVar1 = *(undefined4 *)(param_1 + 0xac);
  iStack_10 = param_1;
  uStack_18 = GetActiveCamera__9GsxCameraFv();
  Init__5P2PktFv(uVar1);
  puStack_14 = (undefined8 *)Add__5P2PktFi(uVar1,0);
  uVar5 = GetRenderTargPkt__9GsxCameraFP4_QWD(uStack_18,puStack_14);
  *(ushort *)(puStack_14 + 4) =
       *(ushort *)(puStack_14 + 4) & 0xfe00 | (ushort)(*(uint *)(iStack_10 + 0xb0) >> 5) & 0x1ff;
  Add__5P2PktFi(uVar1,uVar5);
  if (*(char *)(iStack_10 + 0xc2) != '\0') {
    puStack_14 = (undefined8 *)Add__5P2PktFi(uVar1,*(undefined1 *)(iStack_10 + 0xc2));
    SetPacket__7P2ImageFP4_QWDP6CImageiii(puStack_14,iStack_10 + 0x110,0,0,8);
  }
  puVar2 = (undefined8 *)AddCnt__5P2PktFi(uVar1,10);
  *puVar2 = 0x1003400000008009;
  puVar2[1] = 0xe;
  puStack_14 = puVar2 + 2;
  *puStack_14 = 0x44;
  puVar2[3] = 0x42;
  puVar2[4] = 0;
  puVar2[5] = 0x3f;
  iVar3 = pix2tex(*(undefined2 *)(iStack_10 + 0x114));
  iVar4 = pix2tex(*(undefined2 *)(iStack_10 + 0x116));
  uVar6 = (long)iVar3 << 0x1a | 0x2c20000U | (long)iVar4 << 0x1e;
  iVar3 = GetEntry__6P2ClutFi(0);
  iVar4 = GetPSM__6P2ClutFv();
  puStack_14[4] =
       (long)iVar4 << 0x33 |
       CONCAT44((uint)((ulong)((long)iVar3 << 0x25) >> 0x20) | (uint)(uVar6 >> 0x20) | 4,(int)uVar6)
       | 0x2000000000000000;
  puStack_14[5] = 6;
  puStack_14[6] = 0x60;
  puStack_14[7] = 0x14;
  puStack_14[8] = 0x33001;
  puStack_14[9] = 0x47;
  puStack_14[10] = 0x7c0010007c0010;
  puStack_14[0xb] = 0x40;
  puStack_14[0xc] = 0x80000000;
  puStack_14[0xd] = 1;
  puStack_14[0xf] = 4;
  puStack_14[0x11] = 4;
  for (uVar7 = 0; uVar7 < 2; uVar7 = uVar7 + 1) {
    iStack_1c = 0x710;
    iStack_20 = 0x730;
    if ((uVar7 & 1) != 0) {
      iStack_1c = 0x77c;
      iStack_20 = 0x79c;
    }
    puStack_14[(uVar7 + 7) * 2] = (ulong)CONCAT22((short)(iStack_20 << 4),(short)(iStack_1c << 4));
  }
  puStack_14 = puStack_14 + 0x12;
  MakeMapPacket__8CNaviMapFv(iStack_10);
  uVar5 = Add__5P2PktFi(uVar1,0);
  uVar5 = GetRenderTargPkt__9GsxCameraFP4_QWD(uStack_18,uVar5);
  puStack_14 = (undefined8 *)Add__5P2PktFi(uVar1,uVar5);
  iStack_24 = *(int *)(iStack_10 + 0x9c);
  iStack_28 = *(int *)(iStack_10 + 0xa0);
  iStack_2c = *(int *)(iStack_10 + 0xa4);
  iStack_30 = *(int *)(iStack_10 + 0xa8);
  iStack_34 = iStack_24 + 10;
  iStack_38 = iStack_28 + 0x11;
  uVar5 = GetPktSize__8P2GraTexFPv(0x556270);
  puStack_14 = (undefined8 *)Add__5P2PktFi(uVar1,uVar5);
  SetPacket__8P2GraTexFP4_QWDPvi(puStack_14,0x556270,0);
  *(undefined **)((int)puStack_14 + 0x74) = &naviClut2;
  puVar2 = (undefined8 *)AddCnt__5P2PktFi(uVar1,0x12);
  *puVar2 = 0x10ab400000000004;
  puVar2[1] = 0xe;
  puStack_14 = puVar2 + 2;
  *puStack_14 = 0;
  puVar2[3] = 0x3f;
  iVar3 = GetEntry__6P2ClutFi(0);
  iVar4 = GetPSM__6P2ClutFv();
  puStack_14[2] =
       CONCAT44((int)((ulong)((long)iVar3 << 0x25) >> 0x20),0x99b20000) | 0x500000000 |
       (long)iVar4 << 0x33 | 0x2000000000000000;
  puStack_14[3] = 6;
  puStack_14[4] = 0x44;
  puStack_14[5] = 0x42;
  puStack_14[6] = 0x33001;
  puStack_14[7] = 0x47;
  puStack_14[8] = 0x6400000000008004;
  puStack_14[9] = 0x43431f;
  puStack_14 = puStack_14 + 10;
  Set4Sprite__8CNaviMapFRP4_QWDiiiiiii
            (iStack_10,&puStack_14,iStack_34 + -5,iStack_38 + -5,(iStack_2c >> 1) + 5,
             (iStack_30 >> 1) + 6,0x3f,0x3f);
  puStack_14 = (undefined8 *)AddCnt__5P2PktFi(uVar1,0xb);
  *puStack_14 = 0x10ab40000000800a;
  puStack_14[1] = 0xe;
  puVar2 = puStack_14 + 2;
  *puVar2 = 0;
  puStack_14[3] = 0x3f;
  puStack_14[4] = (ulong)*(uint *)(iStack_10 + 0xb0) | 0x664120000;
  puStack_14[5] = 6;
  puStack_14[6] = 0x8000000068;
  puStack_14[7] = 0x42;
  puStack_14[8] = 0;
  puStack_14[9] = 0x14;
  puStack_14[10] = 0x33001;
  puStack_14[0xb] = 0x47;
  puStack_14[0xc] = 0x50808080;
  puStack_14[0xd] = 1;
  puStack_14[0xf] = 3;
  puStack_14[0x11] = 4;
  puStack_14[0x13] = 3;
  puStack_14[0x15] = 4;
  for (uVar7 = 0; uVar7 < 2; uVar7 = uVar7 + 1) {
    uVar10 = 0x100;
    uVar8 = 0x100;
    if ((uVar7 & 1) != 0) {
      uVar10 = 0x7c0;
      uVar8 = 0x7c0;
    }
    puVar2[(uVar7 * 2 + 6) * 2] = (ulong)CONCAT22(uVar8,uVar10);
    sVar11 = (short)iStack_34;
    sVar9 = (short)iStack_38;
    if ((uVar7 & 1) != 0) {
      sVar11 = sVar11 + (short)iStack_2c;
      sVar9 = sVar9 + (short)iStack_30;
    }
    puVar2[(uVar7 * 2 + 7) * 2] = (ulong)CONCAT22((sVar9 + 0x720) * 0x10,(sVar11 + 0x700) * 0x10);
  }
  puStack_14 = puStack_14 + 0x16;
  uVar5 = GetPktSize__8P2GraTexFPv(0x557680);
  uVar5 = Add__5P2PktFi(uVar1,uVar5);
  SetPacket__8P2GraTexFP4_QWDPvi(uVar5,0x557680,0);
  uVar8 = DAT_00557682;
  uStack_3c = (uint)naviFrame;
  puVar2 = (undefined8 *)AddCnt__5P2PktFi(uVar1,0x11);
  *puVar2 = 0x10ab400000000003;
  puVar2[1] = 0xe;
  puStack_14 = puVar2 + 2;
  *puStack_14 = 0;
  puVar2[3] = 0x3f;
  iVar3 = pix2tex(uStack_3c);
  iVar4 = pix2tex(uVar8);
  uVar6 = (long)iVar3 << 0x1a | 0x1b20000U | (long)iVar4 << 0x1e;
  iVar3 = GetEntry__6P2ClutFi(0);
  iVar4 = GetPSM__6P2ClutFv();
  puStack_14[2] =
       (long)iVar4 << 0x33 |
       CONCAT44((uint)((ulong)((long)iVar3 << 0x25) >> 0x20) | (uint)(uVar6 >> 0x20) | 4,(int)uVar6)
       | 0x2000000000000000;
  puStack_14[3] = 6;
  puStack_14[4] = 0x44;
  puStack_14[5] = 0x42;
  puStack_14[6] = 0x6400000000008004;
  puStack_14[7] = 0x43431f;
  puStack_14 = puStack_14 + 8;
  Set4Sprite__8CNaviMapFRP4_QWDiiiiiii
            (iStack_10,&puStack_14,iStack_24,iStack_28,uStack_3c,uVar8,uStack_3c,uVar8);
  GetPktSize__5P2PktFRi(uVar1,&iStack_40);
  if (maxPkt < iStack_40) {
    maxPkt = iStack_40;
  }
  SetCursor__8CNaviMapFv(iStack_10);
  Terminate__5P2PktFv(uVar1);
  return;
}

/* JP: 0x004d1670  CNaviMap::MakeMapPacket()   [MakeMapPacket__8CNaviMapFv]  size=0x8b4 */
void MakeMapPacket__8CNaviMapFv(int param_1)

{
  int iVar1;
  uint uVar2;
  short *psVar3;
  uint uVar4;
  undefined8 *puVar5;
  ulong *puVar6;
  int iVar7;
  int iVar8;
  undefined8 uVar9;
  uint uVar10;
  int iVar11;
  int iVar12;
  short *psVar13;
  undefined1 auStack_290 [16];
  undefined1 auStack_280 [16];
  undefined1 auStack_270 [16];
  undefined1 auStack_260 [64];
  undefined1 auStack_220 [64];
  undefined1 auStack_1e0 [12];
  float fStack_1d4;
  undefined1 auStack_1d0 [12];
  float fStack_1c4;
  float fStack_1c0;
  float fStack_1bc;
  undefined4 uStack_1b8;
  float fStack_1b4;
  undefined1 auStack_1b0 [16];
  undefined1 auStack_1a0 [12];
  float fStack_194;
  undefined1 auStack_190 [12];
  float fStack_184;
  undefined1 auStack_180 [48];
  undefined1 auStack_150 [192];
  undefined1 auStack_90 [16];
  undefined1 auStack_80 [16];
  undefined1 auStack_70 [28];
  short *psStack_54;
  undefined1 *puStack_50;
  int iStack_4c;
  undefined4 uStack_48;
  int iStack_44;
  float fStack_40;
  float fStack_3c;
  uint uStack_38;
  uint uStack_34;
  undefined1 *puStack_30;
  uint uStack_2c;
  uint uStack_28;
  int iStack_24;
  int iStack_20;
  int *piStack_1c;
  ulong *puStack_18;
  undefined4 uStack_14;
  int iStack_10;
  
  uStack_14 = *(undefined4 *)(param_1 + 0xac);
  iVar7 = *(int *)(param_1 + 0x80);
  uVar4 = 0;
  if (*(short *)(iVar7 + 4) == 0) {
    uVar4 = (uint)*(ushort *)(iVar7 + 0x1a);
  }
  else {
    iVar8 = iVar7 + (uint)*(ushort *)(iVar7 + 6);
    for (iStack_20 = 0; iStack_20 < (int)(uint)*(ushort *)(iVar7 + 0x18); iStack_20 = iStack_20 + 1)
    {
      if ((*(byte *)(iVar8 + 7) & 1) != 0) {
        uVar4 = uVar4 + *(ushort *)(iVar8 + 2);
      }
      iVar8 = iVar8 + (uint)((ulong)((long)*(int *)(iVar8 + 4) << 0x28) >> 0x28) * 0x10;
    }
  }
  iStack_10 = param_1;
  puVar5 = (undefined8 *)AddCnt__5P2PktFi(uStack_14,1);
  piStack_1c = (int *)(puVar5 + -2);
  *puVar5 = 0x302dc00000008000;
  puVar5[1] = 0x412;
  puStack_18 = puVar5 + 2;
  iVar8 = 0;
  __ct__7FVectorFv(auStack_90);
  __ct__7FVectorFv(auStack_80);
  __ct__7FVectorFv(auStack_70);
  puStack_50 = auStack_1b0;
  do {
    __ct__7FVectorFv(puStack_50);
    puStack_50 = puStack_50 + 0x10;
  } while (puStack_50 != auStack_90);
  __ct__7FVectorFv(&fStack_1c0);
  __ct__7FVectorFv(auStack_1d0);
  __ct__7FVectorFv(auStack_1e0);
  iVar11 = iVar7 + (uint)*(ushort *)(iVar7 + 6);
  uStack_2c = 1;
  if (*(short *)(iVar7 + 4) != 0) {
    uStack_2c = (uint)*(ushort *)(iVar7 + 0x18);
  }
  __ct__6MatrixFv(auStack_220);
  for (iVar12 = 0; iVar12 < (int)uStack_2c; iVar12 = iVar12 + 1) {
    if (*(short *)(iVar7 + 4) == 0) {
      iStack_24 = iVar7 + (uint)*(ushort *)(iVar7 + 6);
LAB_004d18b0:
      uStack_28 = uVar4 / 3;
      psVar13 = (short *)(iStack_24 + uVar4 * 8 + 0xf & 0xfffffff0);
      puStack_30 = (undefined1 *)0x0;
      if ((iVar12 < 4) && (*(int *)(iStack_10 + iVar12 * 4 + 0x6c) != 0)) {
        getWorldRot__5FrameFi(auStack_260,*(undefined4 *)(iStack_10 + iVar12 * 4 + 0x6c),m_Env__8VIF1Prim & 1);
        __as__6MatrixFRC6Matrix(auStack_220,auStack_260);
        puStack_30 = auStack_220;
      }
      for (uStack_34 = 0; uStack_34 < uStack_28; uStack_34 = uStack_34 + 1) {
        uVar10 = 0;
        psVar3 = psVar13;
        for (uStack_38 = 0; psVar13 = psVar3, uVar2 = uStack_38, uStack_38 < 3;
            uStack_38 = uStack_38 + 1) {
          iVar1 = uStack_38 * 0x30;
          fStack_40 = (float)GetNavVector__8CNaviMapFP7FVectorP10_NavVertex
                                       (iStack_10,auStack_190 + iVar1,iStack_24);
          fStack_3c = (float)sinf(fStack_40 * 1.570796);
          iStack_44 = 2;
          if (fStack_40 < 0.0) {
            iStack_44 = 0;
            fStack_40 = -fStack_40;
            fStack_3c = -fStack_3c;
          }
          else {
            fStack_3c = fStack_40;
          }
          GetColVector__FP7FVectorUi(&fStack_1c0,*(undefined4 *)(iStack_10 + 0x5c));
          GetColVector__FP7FVectorUi(auStack_1d0,*(undefined4 *)(iStack_10 + iStack_44 * 4 + 0x58));
          __mi__7FVectorCFRC7FVector(auStack_280,auStack_1d0,&fStack_1c0);
          __ml__7FVectorCFf(fStack_3c,auStack_270,auStack_280);
          __as__7FVectorFRC7FVector(auStack_1e0,auStack_270);
          fStack_1d4 = fStack_40 * (fStack_1c4 - fStack_1b4);
          __pl__7FVectorCFRC7FVector(auStack_290,&fStack_1c0,auStack_1e0);
          __as__7FVectorFRC7FVector(auStack_1a0 + iVar1,auStack_290);
          (&fStack_194)[uVar2 * 0xc] = fStack_1b4 + fStack_1d4;
          fStack_3c = (&fStack_184)[uVar2 * 0xc];
          if (fStack_3c < 1.0) {
            uVar10 = uVar10 | 0x100;
          }
          if ((0.0 < (&fStack_194)[uVar2 * 0xc]) && (0.0 < fStack_3c)) {
            uVar10 = uVar10 + 1;
          }
          fStack_1c0 = (float)(int)*psVar13 / 4096.0;
          fStack_1bc = (float)(int)psVar13[1] / 4096.0;
          uStack_1b8 = 0x3f800000;
          __as__7FVectorFRC7FVector(auStack_1b0 + iVar1,&fStack_1c0);
          iStack_24 = iStack_24 + 8;
          psVar3 = psVar13 + 2;
          psStack_54 = psVar13;
        }
        if ((uVar10 & 0xf) == 0) {
          uVar10 = 0;
        }
        if (uVar10 != 0) {
          CnvVertex__8CNaviMapFP4_QWDP7FVectorP6Matrix(iStack_10,puStack_18,auStack_1b0,puStack_30);
          CnvVertex__8CNaviMapFP4_QWDP7FVectorP6Matrix
                    (iStack_10,puStack_18 + 6,auStack_180,puStack_30);
          CnvVertex__8CNaviMapFP4_QWDP7FVectorP6Matrix
                    (iStack_10,puStack_18 + 0xc,auStack_150,puStack_30);
          puStack_18 = puStack_18 + 0x12;
          iVar8 = iVar8 + 3;
        }
      }
      if (*(short *)(iVar7 + 4) == 0) break;
    }
    else {
      iStack_24 = iVar11 + 0x10;
      uVar4 = (uint)*(ushort *)(iVar11 + 2);
      if ((*(byte *)(iVar11 + 7) & 1) != 0) goto LAB_004d18b0;
    }
    iVar11 = iVar11 + (uint)((ulong)((long)*(int *)(iVar11 + 4) << 0x28) >> 0x28) * 0x10;
  }
  if (iVar8 != 0) {
    *(short *)(piStack_1c + 4) = (short)iVar8 + -0x8000;
    iVar8 = iVar8 * 3;
    *piStack_1c = *piStack_1c + iVar8;
    piStack_1c[3] = piStack_1c[3] + iVar8;
    Add__5P2PktFi(uStack_14,iVar8);
  }
  MakeItemPacket__8CNaviMapFv(iStack_10);
  uStack_48 = GetPktSize__8P2GraTexFPv(0x556270);
  uVar9 = Add__5P2PktFi(uStack_14,uStack_48);
  SetPacket__8P2GraTexFP4_QWDPvi(uVar9,0x556270,0);
  iStack_4c = 3;
  puVar6 = (ulong *)AddCnt__5P2PktFi(uStack_14,0x11);
  *puVar6 = (long)iStack_4c | 0x10ab400000000000;
  puVar6[1] = 0xe;
  puStack_18 = puVar6 + 2;
  *puStack_18 = 0;
  puVar6[3] = 0x3f;
  iVar7 = GetEntry__6P2ClutFi(0);
  iVar8 = GetPSM__6P2ClutFv();
  puStack_18[2] = (long)iVar7 << 0x25 | 0x599b20000U | (long)iVar8 << 0x33 | 0x2000000000000000;
  puStack_18[3] = 6;
  puStack_18[4] = 0x44;
  puStack_18[5] = 0x42;
  puStack_18 = puStack_18 + iStack_4c * 2;
  *puStack_18 = 0x6400000000008004;
  puStack_18[1] = 0x43431f;
  puStack_18 = puStack_18 + 2;
  Set4Sprite__8CNaviMapFRP4_QWDiiiiiii(iStack_10,&puStack_18,0xb,0xc,0x3a,0x3a,0x3f,0x3f);
  if ((long)((ulong)*(byte *)(iStack_10 + 0xc0) << 0x3c) < 0) {
    MakeMaskPacket__8CNaviMapFv(iStack_10);
  }
  return;
}

/* JP: 0x004d1f30  CNaviMap::MakeMaskPacket()   [MakeMaskPacket__8CNaviMapFv]  size=0xa80 */
/* WARNING: Removing unreachable block (ram,0x004d1fcc) */

void MakeMaskPacket__8CNaviMapFv(int param_1)

{
  undefined2 uVar1;
  undefined2 uVar2;
  short sVar3;
  short sVar4;
  undefined8 *puVar5;
  ulong *puVar6;
  long *plVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  float fVar12;
  float fVar13;
  undefined1 auStack_c0 [16];
  undefined1 auStack_b0 [16];
  undefined1 auStack_a0 [64];
  float fStack_60;
  float fStack_5c;
  float fStack_58;
  float fStack_54;
  short sStack_48;
  short sStack_46;
  uint uStack_44;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  int iStack_2c;
  int iStack_28;
  float fStack_24;
  float fStack_20;
  int iStack_1c;
  int iStack_18;
  undefined4 uStack_14;
  int iStack_10;
  
  uStack_14 = *(undefined4 *)(param_1 + 0xac);
  iVar11 = *(int *)(param_1 + 0x9c) + 0x700;
  iVar10 = *(int *)(param_1 + 0xa0) + 0x720;
  iStack_18 = *(int *)(param_1 + 0xa4);
  iStack_1c = *(int *)(param_1 + 0xa8);
  iStack_10 = param_1;
  __ct__7FVectorFv(&fStack_60);
  fStack_20 = (float)*(byte *)(iStack_10 + 0xc3) * 1.570796;
  if (3.141592 < fStack_20) {
    fStack_20 = fStack_20 - 6.283184;
  }
  if (fStack_20 < -3.141592) {
    fStack_20 = fStack_20 + 6.283184;
  }
  __ct__6MatrixFv(auStack_a0);
  UnitMatrix__6MatrixFv(auStack_a0);
  RotYMatrix__6MatrixFf(fStack_20,auStack_a0);
  __mi__7FVectorCFRC7FVector(auStack_b0,iStack_10 + 0x30,iStack_10 + 0x40);
  __as__7FVectorFRC7FVector(&fStack_60,auStack_b0);
  ApplyMatrix__6MatrixCFRC7FVector(auStack_c0,auStack_a0,&fStack_60);
  __as__7FVectorFRC7FVector(&fStack_60,auStack_c0);
  fStack_60 = (fStack_60 - *(float *)(iStack_10 + 0x20)) * 0.9;
  fStack_58 = -(fStack_58 + *(float *)(iStack_10 + 0x24));
  __adv__7FVectorFf(*(undefined4 *)(iStack_10 + 0x8c),&fStack_60);
  fVar12 = fStack_60 + (float)(iVar11 + (iStack_18 >> 1));
  fVar13 = fStack_58 + (float)(iVar10 + (iStack_1c >> 1));
  fStack_24 = (*(float *)(iStack_10 + 0x98) * 1.5) / *(float *)(iStack_10 + 0x8c);
  fStack_60 = (fVar12 - fStack_24) * 16.0;
  fStack_5c = (fVar12 + fStack_24) * 16.0;
  fStack_58 = (fVar13 - fStack_24) * 16.0;
  fStack_54 = (fVar13 + fStack_24) * 16.0;
  puVar5 = (undefined8 *)AddCnt__5P2PktFi(uStack_14,0xb);
  *puVar5 = 0x10ab400000000001;
  puVar5[1] = 0xe;
  *(undefined4 *)(puVar5 + 2) = 0x80ffffff;
  *(undefined4 *)((int)puVar5 + 0x14) = 0;
  puVar5[3] = 1;
  puVar5[4] = 0x4400000000008004;
  puVar5[5] = 0x4343;
  puVar6 = puVar5 + 6;
  uStack_44 = 0;
  iStack_28 = (int)(fStack_60 + (fStack_5c - fStack_60) * 0.5);
  iStack_2c = (int)(fStack_58 + (fStack_54 - fStack_58) * 0.5);
  for (uVar8 = 0; (int)uVar8 < 4; uVar8 = uVar8 + 1) {
    if ((uVar8 & 1) == 0) {
      uStack_30 = 0x40;
    }
    else {
      uStack_30 = 0x3f0;
    }
    if ((uVar8 & 2) == 0) {
      uStack_34 = 0x40;
    }
    else {
      uStack_34 = 0x3f0;
    }
    *puVar6 = (ulong)CONCAT22((short)uStack_34,(short)uStack_30);
    if ((uVar8 & 1) == 0) {
      uStack_38 = 0x3f0;
    }
    else {
      uStack_38 = 0x40;
    }
    if ((uVar8 & 2) == 0) {
      uStack_3c = 0x3f0;
    }
    else {
      uStack_3c = 0x40;
    }
    puVar6[2] = (ulong)CONCAT22((short)uStack_3c,(short)uStack_38);
    sStack_48 = (short)iStack_28;
    uVar1 = sStack_48;
    if ((uVar8 & 1) == 0) {
      fVar12 = fStack_60;
      if (2.1474836e+09 <= fStack_60) {
        fVar12 = fStack_60 - 2.1474836e+09;
      }
      uVar1 = (short)(int)fVar12;
    }
    sStack_46 = (short)iStack_2c;
    uVar2 = sStack_46;
    if ((uVar8 & 2) == 0) {
      fVar12 = fStack_58;
      if (2.1474836e+09 <= fStack_58) {
        fVar12 = fStack_58 - 2.1474836e+09;
      }
      uVar2 = (short)(int)fVar12;
    }
    puVar6[1] = (ulong)CONCAT22(uVar2,uVar1);
    if ((uVar8 & 1) != 0) {
      fVar12 = fStack_5c;
      if (2.1474836e+09 <= fStack_5c) {
        fVar12 = fStack_5c - 2.1474836e+09;
      }
      sStack_48 = (short)(int)fVar12;
    }
    if ((uVar8 & 2) != 0) {
      fVar12 = fStack_54;
      if (2.1474836e+09 <= fStack_54) {
        fVar12 = fStack_54 - 2.1474836e+09;
      }
      sStack_46 = (short)(int)fVar12;
    }
    puVar6[3] = (ulong)CONCAT22(sStack_46,sStack_48);
    puVar6 = puVar6 + 4;
  }
  puVar5 = (undefined8 *)AddCnt__5P2PktFi(uStack_14,0xb);
  *puVar5 = 0x10a3400000000001;
  puVar5[1] = 0xe;
  *(undefined4 *)(puVar5 + 2) = 0x80000000;
  *(undefined4 *)((int)puVar5 + 0x14) = 0;
  puVar5[3] = 1;
  puVar5[4] = 0x4400000000008004;
  puVar5[5] = 0x4343;
  plVar7 = puVar5 + 6;
  for (iVar9 = 0; iVar9 < 4; iVar9 = iVar9 + 1) {
    plVar7[2] = (ulong)uStack_44 << 0x20;
    *plVar7 = (ulong)uStack_44 << 0x20;
    sVar3 = (short)iVar11;
    sStack_48 = sVar3 * 0x10;
    if (iVar9 == 2) {
      if (fStack_5c < 2.1474836e+09) {
        sStack_48 = (short)(int)fStack_5c;
      }
      else {
        sStack_48 = (short)(int)(fStack_5c - 2.1474836e+09);
      }
    }
    sVar4 = (short)iVar10;
    if (iVar9 == 3) {
      if (fStack_54 < 2.1474836e+09) {
        sStack_46 = (short)(int)fStack_54;
      }
      else {
        sStack_46 = (short)(int)(fStack_54 - 2.1474836e+09);
      }
    }
    else if (iVar9 == 0) {
      sStack_46 = sVar4 * 0x10;
    }
    else if (fStack_58 < 2.1474836e+09) {
      sStack_46 = (short)(int)fStack_58;
    }
    else {
      sStack_46 = (short)(int)(fStack_58 - 2.1474836e+09);
    }
    plVar7[1] = CONCAT44(uStack_44,CONCAT22(sStack_46,sStack_48));
    sStack_48 = (sVar3 + (short)iStack_18) * 0x10;
    if (iVar9 == 1) {
      if (fStack_60 < 2.1474836e+09) {
        sStack_48 = (short)(int)fStack_60;
      }
      else {
        sStack_48 = (short)(int)(fStack_60 - 2.1474836e+09);
      }
    }
    if (iVar9 == 3) {
      sStack_46 = (sVar4 + (short)iStack_1c) * 0x10;
    }
    else if (iVar9 == 0) {
      if (fStack_58 < 2.1474836e+09) {
        sStack_46 = (short)(int)fStack_58;
      }
      else {
        sStack_46 = (short)(int)(fStack_58 - 2.1474836e+09);
      }
    }
    else if (fStack_54 < 2.1474836e+09) {
      sStack_46 = (short)(int)fStack_54;
    }
    else {
      sStack_46 = (short)(int)(fStack_54 - 2.1474836e+09);
    }
    plVar7[3] = CONCAT44(uStack_44,CONCAT22(sStack_46,sStack_48));
    plVar7 = plVar7 + 4;
  }
  return;
}

/* JP: 0x004d29b0  CNaviMap::Set4Sprite(_QWD&*, int, int, int, int, int, int, int)   [Set4Sprite__8CNaviMapFRP4_QWDiiiiiii]  size=0x2fc */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void Set4Sprite__8CNaviMapFRP4_QWDiiiiiii
               (int param_1,int *param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,
               undefined4 param_6,int param_7,int param_8,int param_9)

{
  short sVar1;
  short sVar2;
  ulong uVar3;
  char *pcVar4;
  undefined2 uVar5;
  undefined2 uVar6;
  undefined2 uVar7;
  uint uVar8;
  undefined4 uStack_b0;
  undefined4 uStack_ac;
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  undefined4 uStack_a0;
  undefined4 uStack_9c;
  undefined4 uStack_98;
  undefined4 uStack_94;
  short sStack_88;
  short sStack_86;
  undefined4 uStack_84;
  int iStack_80;
  int *piStack_70;
  undefined4 uStack_60;
  undefined4 uStack_50;
  undefined4 uStack_40;
  undefined4 uStack_30;
  int iStack_20;
  int iStack_10;
  
  iStack_80 = param_1;
  piStack_70 = param_2;
  uStack_60 = param_3;
  uStack_50 = param_4;
  uStack_40 = param_5;
  uStack_30 = param_6;
  uStack_a0 = (int)__2733;
  uStack_9c = (int)((ulong)__2733 >> 0x20);
  uStack_98 = DAT_00553e38;
  uStack_94 = DAT_00553e3c;
  uStack_b0 = (int)__2735;
  uStack_ac = (int)((ulong)__2735 >> 0x20);
  uStack_a8 = DAT_00553e48;
  uStack_a4 = DAT_00553e4c;
  if (param_9 == 1) {
    uVar7 = 0x10;
    iStack_20 = param_7 * 0x10 + -0x10;
    iStack_10 = param_8 * 0x10 + -0x10;
  }
  else {
    uVar7 = 8;
    iStack_20 = param_7 * 0x10 + -8;
    iStack_10 = param_8 * 0x10 + -8;
  }
  pcVar4 = (char *)&uStack_a0;
  uVar3 = 0xffffffff80800000;
  if (param_9 == 2) {
    pcVar4 = (char *)&uStack_b0;
    uVar3 = 0x40800000;
  }
  uVar3 = uVar3 | 0x8080;
  if (param_9 == 3) {
    uVar3 = (ulong)*(int *)(param_1 + 0x50);
  }
  uStack_84 = 0;
  for (uVar8 = 0; uVar8 < 4; uVar8 = uVar8 + 1) {
    *(undefined8 *)*param_2 = 0;
    *(ulong *)(*param_2 + 8) = uVar3 & 0xffffffff;
    uVar6 = (undefined2)iStack_20;
    sStack_88 = uVar6;
    if (*pcVar4 == '\0') {
      sStack_88 = uVar7;
    }
    uVar5 = (undefined2)iStack_10;
    sStack_86 = uVar5;
    if (pcVar4[1] == '\0') {
      sStack_86 = uVar7;
    }
    *(ulong *)(*param_2 + 0x10) = (ulong)CONCAT22(sStack_86,sStack_88);
    if (pcVar4[2] == '\0') {
      uVar6 = uVar7;
    }
    if (pcVar4[3] == '\0') {
      uVar5 = uVar7;
    }
    *(ulong *)(*param_2 + 0x20) = (ulong)CONCAT22(uVar5,uVar6);
    sVar1 = (short)param_3 + ((ushort)uVar8 & 1) * (short)param_5 + 0x700;
    sVar2 = (short)param_4 + (short)(uVar8 >> 1) * (short)param_6 + 0x720;
    *(ulong *)(*param_2 + 0x18) = (ulong)CONCAT22(sVar2 * 0x10,sVar1 * 0x10);
    sStack_88 = (sVar1 + (short)param_5) * 0x10;
    sStack_86 = (sVar2 + (short)param_6) * 0x10;
    *(ulong *)(*param_2 + 0x28) = (ulong)CONCAT22(sStack_86,sStack_88);
    *param_2 = *param_2 + 0x30;
    pcVar4 = pcVar4 + 4;
  }
  return;
}

/* JP: 0x004d2cb0  CNaviMap::SetCursor()   [SetCursor__8CNaviMapFv]  size=0x594 */
/* WARNING: Removing unreachable block (ram,0x004d2d7c) */

void SetCursor__8CNaviMapFv(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined1 in_zero_qw [16];
  undefined8 *puVar6;
  undefined8 extraout_v0_udw;
  undefined1 auVar7 [16];
  int iVar8;
  int iVar9;
  undefined2 uVar10;
  undefined2 uVar11;
  uint uVar12;
  float *pfVar13;
  float *pfVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  undefined1 auStack_b0 [16];
  undefined1 auStack_a0 [16];
  undefined1 auStack_90 [64];
  float afStack_50 [2];
  float fStack_48;
  float fStack_1c;
  float fStack_14;
  int iStack_10;
  
  uVar1 = *(undefined4 *)(param_1 + 0xac);
  iStack_10 = param_1;
  __ct__7FVectorFv(afStack_50);
  iVar2 = *(int *)(iStack_10 + 0x9c);
  iVar3 = *(int *)(iStack_10 + 0xa0);
  iVar4 = *(int *)(iStack_10 + 0xa4);
  iVar5 = *(int *)(iStack_10 + 0xa8);
  puVar6 = (undefined8 *)AddCnt__5P2PktFi(uVar1,5);
  auVar7._8_8_ = extraout_v0_udw;
  auVar7._0_8_ = 0x8400000000008001;
  auVar7 = _pcpyld(in_zero_qw,auVar7);
  *puVar6 = auVar7._0_8_;
  puVar6[1] = 0x41c1c1f0;
  puVar6[2] = 0x1cb;
  puVar6[3] = 0;
  puVar6 = puVar6 + 4;
  fStack_1c = (float)*(byte *)(iStack_10 + 0xc3) * 1.570796;
  if (3.141592 < fStack_1c) {
    fStack_1c = fStack_1c - 6.283184;
  }
  if (fStack_1c < -3.141592) {
    fStack_1c = fStack_1c + 6.283184;
  }
  __ct__6MatrixFv(auStack_90);
  UnitMatrix__6MatrixFv(auStack_90);
  RotYMatrix__6MatrixFf(fStack_1c,auStack_90);
  __mi__7FVectorCFRC7FVector(auStack_a0,iStack_10 + 0x30,iStack_10 + 0x40);
  __as__7FVectorFRC7FVector(afStack_50,auStack_a0);
  ApplyMatrix__6MatrixCFRC7FVector(auStack_b0,auStack_90,afStack_50);
  __as__7FVectorFRC7FVector(afStack_50,auStack_b0);
  afStack_50[0] = (afStack_50[0] - *(float *)(iStack_10 + 0x20)) * 0.9;
  fStack_48 = -(fStack_48 + *(float *)(iStack_10 + 0x24));
  __adv__7FVectorFf(*(undefined4 *)(iStack_10 + 0x8c),afStack_50);
  if ((long)((ulong)*(byte *)(iStack_10 + 0xc0) << 0x3b) < 0) {
    fVar15 = *(float *)(iStack_10 + 0x88) - *(float *)(iStack_10 + 0x84);
  }
  else {
    fVar15 = *(float *)(iStack_10 + 0x88);
  }
  fStack_1c = fStack_1c + fVar15;
  if (3.141592 < fStack_1c) {
    fStack_1c = fStack_1c - 6.283184;
  }
  if (fStack_1c < 3.141592) {
    fStack_1c = fStack_1c + 6.283184;
  }
  fStack_14 = (float)cosf(fStack_1c);
  fVar15 = (float)sinf(fStack_1c);
  pfVar13 = (float *)&csrPos_2786;
  for (uVar12 = 0; uVar12 < 3; uVar12 = uVar12 + 1) {
    pfVar14 = pfVar13 + 1;
    fVar17 = *pfVar13;
    pfVar13 = pfVar13 + 2;
    iVar8 = iVar4;
    if (iVar4 < 0) {
      iVar8 = iVar4 + 1;
    }
    iVar9 = iVar5;
    if (iVar5 < 0) {
      iVar9 = iVar5 + 1;
    }
    fVar16 = (-(fVar17 * fStack_14 - *pfVar14 * fVar15) * *(float *)(iStack_10 + 0x94) * 1.1 +
             afStack_50[0] + (float)(iVar2 + 0x70a + (iVar8 >> 1))) * 16.0;
    if (fVar16 < 2.1474836e+09) {
      uVar10 = (undefined2)(int)fVar16;
    }
    else {
      uVar10 = (undefined2)(int)(fVar16 - 2.1474836e+09);
    }
    fVar17 = (-(fVar17 * fVar15 + *pfVar14 * fStack_14) * *(float *)(iStack_10 + 0x94) +
             fStack_48 + (float)(iVar3 + 0x731 + (iVar9 >> 1))) * 16.0;
    if (fVar17 < 2.1474836e+09) {
      uVar11 = (undefined2)(int)fVar17;
    }
    else {
      uVar11 = (undefined2)(int)(fVar17 - 2.1474836e+09);
    }
    *(undefined4 *)puVar6 = *(undefined4 *)(&csrCol_2787 + uVar12 * 4);
    puVar6[1] = (ulong)CONCAT22(uVar11,uVar10);
    puVar6 = puVar6 + 2;
  }
  return;
}

/* JP: 0x004d3250  CNaviMap::GetNavVector(FVector*, _NavVertex*)   [GetNavVector__8CNaviMapFP7FVectorP10_NavVertex]  size=0x164 */
float GetNavVector__8CNaviMapFP7FVectorP10_NavVertex(int param_1,int param_2,short *param_3)

{
  float fStack_50;
  float fStack_4c;
  float fStack_48;
  float fStack_34;
  int iStack_30;
  int iStack_20;
  short *psStack_10;
  
  iStack_30 = param_1;
  iStack_20 = param_2;
  psStack_10 = param_3;
  __ct__7FVectorFv(&fStack_50);
  fStack_50 = (float)(int)*psStack_10;
  fStack_4c = (float)(int)psStack_10[1];
  fStack_48 = (float)(int)psStack_10[2];
  __amu__7FVectorFf(0x3d800000,&fStack_50);
  __as__7FVectorFRC7FVector(iStack_20,&fStack_50);
  __ami__7FVectorFRC7FVector(&fStack_50,iStack_30 + 0x30);
  *(undefined4 *)(iStack_20 + 0xc) = 0x3f800000;
  fStack_34 = fStack_4c * 0.05;
  if (fStack_34 < -1.0) {
    fStack_34 = -1.0;
  }
  if (1.0 < fStack_34) {
    fStack_34 = 1.0;
  }
  if ((long)((ulong)*(byte *)(iStack_30 + 0xc0) << 0x3a) < 0) {
    fStack_34 = 0.0;
  }
  return fStack_34;
}

/* JP: 0x004d33c0  CNaviMap::CnvVertex(_QWD*, FVector*, Matrix*)   [CnvVertex__8CNaviMapFP4_QWDP7FVectorP6Matrix]  size=0x2e8 */
void CnvVertex__8CNaviMapFP4_QWDP7FVectorP6Matrix(int param_1,int param_2,int param_3,int param_4)

{
  float fVar1;
  uint uVar2;
  float fVar3;
  undefined1 auStack_80 [16];
  undefined1 auStack_70 [16];
  float fStack_60;
  float fStack_5c;
  float fStack_58;
  float fStack_54;
  float fStack_44;
  int iStack_40;
  int iStack_30;
  int iStack_20;
  int iStack_10;
  
  fStack_44 = *(float *)(param_3 + 0x2c);
  iStack_40 = param_1;
  iStack_30 = param_2;
  iStack_20 = param_3;
  iStack_10 = param_4;
  __ct__7FVectorFv(&fStack_60);
  __as__7FVectorFRC7FVector(iStack_30,iStack_20);
  __as__7FVectorFRC7FVector(&fStack_60,iStack_20 + 0x10);
  *(int *)(iStack_30 + 0x10) = (int)fStack_60;
  *(int *)(iStack_30 + 0x14) = (int)fStack_5c;
  *(int *)(iStack_30 + 0x18) = (int)fStack_58;
  fVar1 = (float)(int)fStack_54 * fStack_44;
  if (fVar1 < 2.1474836e+09) {
    uVar2 = (uint)fVar1;
  }
  else {
    uVar2 = (int)(fVar1 - 2.1474836e+09) | 0x80000000;
  }
  *(uint *)(iStack_30 + 0x1c) = uVar2;
  __as__7FVectorFRC7FVector(&fStack_60,iStack_20 + 0x20);
  if (iStack_10 != 0) {
    ApplyMatrix__6MatrixCFRC7FVector(auStack_70,iStack_10,&fStack_60);
    __as__7FVectorFRC7FVector(&fStack_60,auStack_70);
  }
  __ami__7FVectorFRC7FVector(&fStack_60,iStack_40 + 0x40);
  fStack_54 = 1.0;
  ApplyMatrix__6MatrixCFRC7FVector(auStack_80,iStack_40 + 0xd0,&fStack_60);
  __as__7FVectorFRC7FVector(&fStack_60,auStack_80);
  __ami__7FVectorFRC7FVector(&fStack_60,iStack_40 + 0x20);
  fStack_60 = fStack_60 * 0.9;
  __adv__7FVectorFf(*(undefined4 *)(iStack_40 + 0x8c),&fStack_60);
  fVar1 = (fStack_60 + 1862.0) * 16.0;
  fVar3 = (fStack_5c + 1894.0) * 16.0;
  if (2.1474836e+09 <= fVar1) {
    fVar1 = fVar1 - 2.1474836e+09;
  }
  *(uint *)(iStack_30 + 0x20) = (int)fVar1 & 0xffff;
  if (2.1474836e+09 <= fVar3) {
    fVar3 = fVar3 - 2.1474836e+09;
  }
  *(uint *)(iStack_30 + 0x24) = (int)fVar3 & 0xffff;
  *(undefined4 *)(iStack_30 + 0x28) = 1;
  *(undefined4 *)(iStack_30 + 0x2c) = 0;
  return;
}

/* JP: 0x004d36f0  CNaviMap::MakeItemPacket()   [MakeItemPacket__8CNaviMapFv]  size=0xa3c */
/* WARNING: Removing unreachable block (ram,0x004d3d04) */
/* WARNING: Removing unreachable block (ram,0x004d3afc) */
/* WARNING: Removing unreachable block (ram,0x004d3dd0) */
/* WARNING: Removing unreachable block (ram,0x004d3b4c) */

void MakeItemPacket__8CNaviMapFv(int param_1)

{
  undefined8 *puVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined8 uVar5;
  long lVar6;
  undefined8 *puVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  uint uVar11;
  float fVar12;
  undefined1 auStack_60 [4];
  float fStack_5c;
  undefined1 auStack_50 [20];
  int iStack_3c;
  float fStack_38;
  float fStack_34;
  float fStack_30;
  uint uStack_2c;
  float fStack_28;
  float fStack_24;
  float fStack_20;
  uint uStack_1c;
  uint uStack_18;
  undefined4 uStack_14;
  int iStack_10;
  
  uStack_14 = *(undefined4 *)(param_1 + 0xac);
  iStack_10 = param_1;
  uVar5 = GetPktSize__8P2GraTexFPv(0x558c90);
  uVar5 = Add__5P2PktFi(uStack_14,uVar5);
  uVar5 = SetPacket__8P2GraTexFP4_QWDPvi(uVar5,0x558c90,0);
  puVar1 = (undefined8 *)AddCnt__5P2PktFi(uStack_14,3,uVar5);
  *puVar1 = 0x2000000000008001;
  puVar1[1] = 0xee;
  puVar1[2] = 0;
  puVar1[3] = 0x3f;
  iVar2 = GetEntry__6P2ClutFi(0);
  puVar1[4] = (long)iVar2 << 0x25 | 0x2000000592c20000;
  puVar1[5] = 6;
  puVar7 = puVar1 + 6;
  iVar8 = 0;
  for (iVar2 = 0; iVar2 < 2; iVar2 = iVar2 + 1) {
    if (iVar2 == 0) {
      iVar10 = *(int *)(iStack_10 + 0x80);
      if (*(short *)(iVar10 + 0x30) != 0) {
        iVar9 = (uint)*(ushort *)(iVar10 + 0x32) * 0x10 + iVar10 + (uint)*(ushort *)(iVar10 + 6);
        uStack_18 = (uint)*(ushort *)(iVar10 + 0x30);
        goto LAB_004d3888;
      }
    }
    else {
      iVar9 = *(int *)(iStack_10 + 0xb4);
      if (iVar9 == 0) break;
      uStack_18 = 0x20;
LAB_004d3888:
      for (uVar11 = 0; iVar10 = iVar9, (int)uVar11 < (int)uStack_18; uVar11 = uVar11 + 1) {
        if ((iVar2 != 1) ||
           ((*(uint *)(iStack_10 + ((int)uVar11 >> 5) * 4 + 0xb8) & 1 << (uVar11 & 0x1f)) != 0)) {
          uStack_1c = *(byte *)(iVar10 + 0xe) & 0x1f;
          __ct__7FVectorFv(auStack_50);
          GetShortPos__FP7FVectorPs(auStack_50,iVar10);
          if (((ulong)*(byte *)(iVar10 + 7) & 0x1f) >> 1 < 8) {
            uVar3 = *(uint *)(&colTbl + (uint)(((ulong)*(byte *)(iVar10 + 7) << 0x3b) >> 0x3c) * 4);
          }
          else {
            uVar3 = GetPolyColor__8CNaviMapFP7FVector(iStack_10,auStack_50);
          }
          __mi__7FVectorCFRC7FVector(auStack_60,auStack_50,iStack_10 + 0x30);
          fStack_20 = fStack_5c * 0.05;
          if (fStack_20 < 0.0) {
            fStack_20 = -fStack_20;
          }
          if (1.0 < fStack_20) {
            fStack_20 = 1.0;
          }
          fStack_20 = 1.0 - fStack_20;
          if ((long)((ulong)*(byte *)(iStack_10 + 0xc0) << 0x3a) < 0) {
            fStack_20 = 1.0;
          }
          fVar12 = fStack_20 * 128.0;
          if (2.1474836e+09 <= fVar12) {
            fVar12 = fVar12 - 2.1474836e+09;
          }
          uVar3 = uVar3 | (int)fVar12 << 0x18;
          GetCenterPos__8CNaviMapFR7FVector(iStack_10,auStack_50);
          switch(uStack_1c) {
          case 0:
            *puVar7 = 0x6400000000008001;
            puVar7[1] = 0x44cc10;
            puVar7[2] = 0x44;
            *(uint *)(puVar7 + 3) = uVar3;
            *(undefined4 *)((int)puVar7 + 0x1c) = 0;
            fStack_24 = (float)*(ushort *)(iVar10 + 8) * 0.03125;
            fStack_28 = (float)*(ushort *)(iVar10 + 10) * 0.03125;
            GetRectVertex__8CNaviMapFP4_DWDP7FVectoriff
                      (fStack_24,fStack_28,iStack_10,puVar7 + 4,auStack_50,
                       *(ushort *)(iVar10 + 6) & 0x1ff);
            puVar7 = puVar7 + 8;
            iVar8 = iVar8 + 4;
            break;
          case 1:
            *puVar7 = 0x6400000000008001;
            puVar7[1] = 0x43c310;
            puVar7[2] = 0x156;
            uVar4 = HalfCol__FUi(uVar3);
            *(undefined4 *)(puVar7 + 3) = uVar4;
            *(undefined4 *)((int)puVar7 + 0x1c) = 0x3f800000;
            GetSprVertex__8CNaviMapFP4_DWDP7FVectorifii
                      (0x41c00000,iStack_10,puVar7 + 4,auStack_50,1,0,0);
            puVar7 = puVar7 + 8;
            iVar8 = iVar8 + 4;
            break;
          case 2:
            *puVar7 = 0x5400000000008001;
            puVar7[1] = 0xf4cc10;
            puVar7[2] = 0x43;
            *(uint *)(puVar7 + 3) = uVar3;
            *(undefined4 *)((int)puVar7 + 0x1c) = 0;
            GetArrowVertex__8CNaviMapFP4_DWDP7FVectori
                      (iStack_10,puVar7 + 4,auStack_50,*(ushort *)(iVar10 + 6) & 0x1ff);
            puVar7 = puVar7 + 8;
            iVar8 = iVar8 + 4;
            break;
          case 3:
            lVar6 = HalfCol__FUi(uVar3);
            uVar3 = (uint)lVar6;
            fStack_30 = *(float *)(iStack_10 + 0xbc);
            fStack_34 = (fStack_30 * 2.0 + 1.0) * 10.0;
            fStack_38 = (float)(uVar3 >> 0x18);
            uStack_2c = uVar3;
            fVar12 = (float)sinf((1.0 - fStack_30) * 1.570796);
            fStack_38 = fStack_38 * fVar12;
            if (2.1474836e+09 <= fStack_38) {
              fStack_38 = fStack_38 - 2.1474836e+09;
            }
            uStack_2c = (uint)((ulong)((long)(int)uStack_2c << 0x28) >> 0x28) +
                        (int)fStack_38 * 0x1000000;
            fStack_38 = (float)(uVar3 >> 0x18);
            fVar12 = (float)cosf(fStack_30 * 1.570796);
            fStack_38 = fStack_38 * (1.0 - fVar12);
            fVar12 = fStack_38;
            if (2.1474836e+09 <= fStack_38) {
              fVar12 = fStack_38 - 2.1474836e+09;
            }
            *puVar7 = 0x6400000000008002;
            puVar7[1] = 0x43c310;
            puVar7[8] = 0x156;
            puVar7[2] = 0x156;
            *(uint *)(puVar7 + 3) = uStack_2c;
            *(undefined4 *)((int)puVar7 + 0x4c) = 0x3f800000;
            *(undefined4 *)((int)puVar7 + 0x1c) = 0x3f800000;
            GetSprVertex__8CNaviMapFP4_DWDP7FVectorifii
                      (fStack_34 * 1.5,iStack_10,puVar7 + 4,auStack_50,1,0,0x20);
            *(uint *)(puVar7 + 9) = (uint)((ulong)(lVar6 << 0x28) >> 0x28) + (int)fVar12 * 0x1000000
            ;
            fVar12 = (float)cosf(fStack_30 * 1.570796);
            GetSprVertex__8CNaviMapFP4_DWDP7FVectorifii
                      ((1.0 - fVar12) * 15.0,iStack_10,puVar7 + 10,auStack_50,1,0,0x20);
            puVar7 = puVar7 + 0xe;
            iVar8 = iVar8 + 7;
            break;
          case 4:
            uVar4 = HalfCol__FUi(uVar3);
            *puVar7 = 0x6400000000008001;
            puVar7[1] = 0x4343c3c310;
            puVar7[2] = 0x154;
            *(undefined4 *)(puVar7 + 3) = uVar4;
            *(undefined4 *)((int)puVar7 + 0x1c) = 0x3f800000;
            GetFT4Vertex__8CNaviMapFP4_DWDP7FVectorifii
                      (0x40c00000,iStack_10,puVar7 + 4,auStack_50,*(ushort *)(iVar10 + 6) & 0x1ff,0,
                       0x10);
            puVar7 = puVar7 + 0xc;
            iVar8 = iVar8 + 6;
            break;
          case 5:
            *puVar7 = 0x6400000000008001;
            puVar7[1] = 0x43c310;
            puVar7[2] = 0x156;
            uVar4 = HalfCol__FUi(uVar3);
            *(undefined4 *)(puVar7 + 3) = uVar4;
            *(undefined4 *)((int)puVar7 + 0x1c) = 0x3f800000;
            GetSprVertex__8CNaviMapFP4_DWDP7FVectorifii
                      (0x41c80000,iStack_10,puVar7 + 4,auStack_50,1,0,0x30);
            puVar7 = puVar7 + 8;
            iVar8 = iVar8 + 4;
          }
        }
        iVar9 = iVar10 + 0x10;
        iStack_3c = iVar10;
      }
    }
  }
  if (iVar8 != 0) {
    *(int *)(puVar1 + -2) = *(int *)(puVar1 + -2) + iVar8;
    *(int *)((int)puVar1 + -4) = *(int *)((int)puVar1 + -4) + iVar8;
    Add__5P2PktFi(uStack_14,iVar8);
  }
  return;
}

/* JP: 0x004d41c0  CNaviMap::GetCenterPos(FVector&)   [GetCenterPos__8CNaviMapFR7FVector]  size=0xa0 */
void GetCenterPos__8CNaviMapFR7FVector(int param_1,float *param_2)

{
  undefined1 auStack_30 [16];
  int iStack_20;
  float *pfStack_10;
  
  iStack_20 = param_1;
  pfStack_10 = param_2;
  __ami__7FVectorFRC7FVector(param_2,param_1 + 0x40);
  pfStack_10[3] = 1.0;
  ApplyMatrix__6MatrixCFRC7FVector(auStack_30,iStack_20 + 0xd0,pfStack_10);
  __as__7FVectorFRC7FVector(pfStack_10,auStack_30);
  __ami__7FVectorFRC7FVector(pfStack_10,iStack_20 + 0x20);
  *pfStack_10 = *pfStack_10 * 0.9;
  return;
}

/* JP: 0x004d4260  CNaviMap::GetRectVertex(_DWD*, FVector*, int, float, float)   [GetRectVertex__8CNaviMapFP4_DWDP7FVectoriff]  size=0x330 */
void GetRectVertex__8CNaviMapFP4_DWDP7FVectoriff
               (float param_1,float param_2,int param_3,undefined2 *param_4,undefined4 param_5,
               undefined4 param_6)

{
  int iVar1;
  undefined2 uVar2;
  float fVar3;
  undefined1 auStack_110 [16];
  undefined1 auStack_100 [64];
  float afStack_c0 [5];
  float fStack_ac;
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  float fStack_a0;
  float fStack_9c;
  undefined4 uStack_98;
  undefined4 uStack_94;
  float fStack_90;
  float fStack_8c;
  undefined4 uStack_88;
  undefined4 uStack_84;
  undefined1 auStack_80 [24];
  float fStack_68;
  float fStack_64;
  int iStack_60;
  undefined2 *puStack_50;
  undefined4 uStack_40;
  undefined4 uStack_30;
  float fStack_20;
  float fStack_10;
  
  iStack_60 = param_3;
  puStack_50 = param_4;
  uStack_40 = param_5;
  uStack_30 = param_6;
  fStack_20 = param_1;
  fStack_10 = param_2;
  __ct__7FVectorFv(auStack_80);
  __ct__7FVectorFv(afStack_c0);
  __ct__7FVectorFv(afStack_c0 + 4);
  __ct__7FVectorFv(&fStack_a0);
  __ct__7FVectorFv(&fStack_90);
  __as__7FVectorFRC7FVector(auStack_80,uStack_40);
  uStack_84 = 0x3f800000;
  uStack_94 = 0x3f800000;
  uStack_a4 = 0x3f800000;
  afStack_c0[3] = 1.0;
  uStack_88 = 0;
  uStack_98 = 0;
  uStack_a8 = 0;
  afStack_c0[2] = 0.0;
  afStack_c0[0] = -fStack_20;
  fStack_90 = fStack_20;
  afStack_c0[4] = fStack_20;
  afStack_c0[1] = -fStack_10;
  fStack_8c = fStack_10;
  fStack_9c = fStack_10;
  fStack_ac = afStack_c0[1];
  fStack_a0 = afStack_c0[0];
  __ct__6MatrixFv(auStack_100);
  GetRotMatrix__FR6Matrixi(auStack_100,uStack_30);
  SetPos__6MatrixFRC7FVector(auStack_100,auStack_80);
  iVar1 = *(int *)(iStack_60 + 0xa4);
  if (iVar1 < 0) {
    iVar1 = iVar1 + 1;
  }
  fStack_64 = (float)(*(int *)(iStack_60 + 0x9c) + 0x700 + (iVar1 >> 1));
  iVar1 = *(int *)(iStack_60 + 0xa8);
  if (iVar1 < 0) {
    iVar1 = iVar1 + 1;
  }
  fStack_68 = (float)(*(int *)(iStack_60 + 0xa0) + 0x720 + (iVar1 >> 1));
  for (iVar1 = 0; iVar1 < 4; iVar1 = iVar1 + 1) {
    ApplyMatrix__6MatrixCFRC7FVector(auStack_110,auStack_100,afStack_c0 + iVar1 * 4);
    __as__7FVectorFRC7FVector(afStack_c0 + iVar1 * 4,auStack_110);
    __adv__7FVectorFf(*(undefined4 *)(iStack_60 + 0x8c),afStack_c0 + iVar1 * 4);
    afStack_c0[iVar1 * 4] = afStack_c0[iVar1 * 4] + fStack_64;
    afStack_c0[iVar1 * 4 + 1] = afStack_c0[iVar1 * 4 + 1] + fStack_68;
    afStack_c0[iVar1 * 4] = afStack_c0[iVar1 * 4] * 16.0;
    afStack_c0[iVar1 * 4 + 1] = afStack_c0[iVar1 * 4 + 1] * 16.0;
    fVar3 = afStack_c0[iVar1 * 4];
    if (fVar3 < 2.1474836e+09) {
      uVar2 = (undefined2)(int)fVar3;
    }
    else {
      uVar2 = (undefined2)(int)(fVar3 - 2.1474836e+09);
    }
    *puStack_50 = uVar2;
    fVar3 = afStack_c0[iVar1 * 4 + 1];
    if (fVar3 < 2.1474836e+09) {
      uVar2 = (undefined2)(int)fVar3;
    }
    else {
      uVar2 = (undefined2)(int)(fVar3 - 2.1474836e+09);
    }
    puStack_50[1] = uVar2;
    *(undefined4 *)(puStack_50 + 2) = 1;
    puStack_50 = puStack_50 + 4;
  }
  return;
}

/* JP: 0x004d4590  CNaviMap::GetArrowVertex(_DWD*, FVector*, int)   [GetArrowVertex__8CNaviMapFP4_DWDP7FVectori]  size=0x2c8 */
void GetArrowVertex__8CNaviMapFP4_DWDP7FVectori
               (int param_1,undefined2 *param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  float *pfVar2;
  undefined2 uVar3;
  undefined1 auStack_c0 [16];
  float fStack_b0;
  float fStack_ac;
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  float afStack_a0 [5];
  float fStack_8c;
  float fStack_78;
  undefined1 auStack_60 [24];
  float fStack_48;
  float fStack_44;
  int iStack_40;
  undefined2 *puStack_30;
  undefined4 uStack_20;
  undefined4 uStack_10;
  
  iStack_40 = param_1;
  puStack_30 = param_2;
  uStack_20 = param_3;
  uStack_10 = param_4;
  __ct__7FVectorFRC7FVector(auStack_60,param_3);
  __adv__7FVectorFf(*(undefined4 *)(iStack_40 + 0x8c),auStack_60);
  __ct__6MatrixFv(afStack_a0);
  GetRotMatrix__FR6Matrixi(afStack_a0,uStack_10);
  afStack_a0[0] = afStack_a0[0] * *(float *)(iStack_40 + 0x94);
  fStack_8c = fStack_8c * *(float *)(iStack_40 + 0x94);
  fStack_78 = fStack_78 * *(float *)(iStack_40 + 0x94);
  SetPos__6MatrixFRC7FVector(afStack_a0,auStack_60);
  iVar1 = *(int *)(iStack_40 + 0xa4);
  if (iVar1 < 0) {
    iVar1 = iVar1 + 1;
  }
  fStack_44 = (float)(*(int *)(iStack_40 + 0x9c) + 0x700 + (iVar1 >> 1));
  iVar1 = *(int *)(iStack_40 + 0xa8);
  if (iVar1 < 0) {
    iVar1 = iVar1 + 1;
  }
  fStack_48 = (float)(*(int *)(iStack_40 + 0xa0) + 0x720 + (iVar1 >> 1));
  pfVar2 = (float *)&csrPos_2986;
  for (iVar1 = 0; iVar1 < 3; iVar1 = iVar1 + 1) {
    __ct__7FVectorFv(&fStack_b0);
    fStack_b0 = *pfVar2;
    fStack_ac = pfVar2[1];
    uStack_a8 = 0;
    uStack_a4 = 0x3f800000;
    ApplyMatrix__6MatrixCFRC7FVector(auStack_c0,afStack_a0,&fStack_b0);
    __as__7FVectorFRC7FVector(&fStack_b0,auStack_c0);
    fStack_b0 = (fStack_b0 + fStack_44) * 16.0;
    fStack_ac = (fStack_ac + fStack_48) * 16.0;
    if (fStack_b0 < 2.1474836e+09) {
      uVar3 = (undefined2)(int)fStack_b0;
    }
    else {
      uVar3 = (undefined2)(int)(fStack_b0 - 2.1474836e+09);
    }
    *puStack_30 = uVar3;
    if (fStack_ac < 2.1474836e+09) {
      uVar3 = (undefined2)(int)fStack_ac;
    }
    else {
      uVar3 = (undefined2)(int)(fStack_ac - 2.1474836e+09);
    }
    puStack_30[1] = uVar3;
    *(undefined4 *)(puStack_30 + 2) = 1;
    puStack_30 = puStack_30 + 4;
    pfVar2 = pfVar2 + 2;
  }
  return;
}

/* JP: 0x004d4860  CNaviMap::GetSprVertex(_DWD*, FVector*, int, float, int, int)   [GetSprVertex__8CNaviMapFP4_DWDP7FVectorifii]  size=0x3e0 */
void GetSprVertex__8CNaviMapFP4_DWDP7FVectorifii
               (float param_1,int param_2,short *param_3,undefined4 param_4,int param_5,int param_6,
               int param_7)

{
  int iVar1;
  float *pfVar2;
  short sVar3;
  undefined1 auStack_f0 [16];
  float fStack_e0;
  float fStack_dc;
  undefined4 uStack_d8;
  undefined4 uStack_d4;
  float afStack_d0 [5];
  float fStack_bc;
  float fStack_a8;
  undefined1 auStack_90 [20];
  undefined4 uStack_7c;
  float fStack_78;
  float fStack_74;
  int iStack_70;
  short *psStack_60;
  undefined4 uStack_50;
  int iStack_40;
  float fStack_30;
  int iStack_20;
  int iStack_10;
  
  iStack_70 = param_2;
  psStack_60 = param_3;
  uStack_50 = param_4;
  iStack_40 = param_5;
  fStack_30 = param_1;
  iStack_20 = param_6;
  iStack_10 = param_7;
  __ct__7FVectorFRC7FVector(auStack_90,param_4);
  __adv__7FVectorFf(*(undefined4 *)(iStack_70 + 0x8c),auStack_90);
  fStack_30 = fStack_30 / *(float *)(iStack_70 + 0x8c);
  __ct__6MatrixFv(afStack_d0);
  UnitMatrix__6MatrixFv(afStack_d0);
  afStack_d0[0] = afStack_d0[0] * fStack_30;
  fStack_bc = fStack_bc * fStack_30;
  fStack_a8 = fStack_a8 * fStack_30;
  SetPos__6MatrixFRC7FVector(afStack_d0,auStack_90);
  iVar1 = *(int *)(iStack_70 + 0xa4);
  if (iVar1 < 0) {
    iVar1 = iVar1 + 1;
  }
  fStack_74 = (float)(*(int *)(iStack_70 + 0x9c) + 0x700 + (iVar1 >> 1));
  iVar1 = *(int *)(iStack_70 + 0xa8);
  if (iVar1 < 0) {
    iVar1 = iVar1 + 1;
  }
  fStack_78 = (float)(*(int *)(iStack_70 + 0xa0) + 0x720 + (iVar1 >> 1));
  pfVar2 = (float *)&csrPos_3016;
  for (iVar1 = 0; iVar1 < 2; iVar1 = iVar1 + 1) {
    if (iStack_40 == 1) {
      if (iVar1 == 0) {
        sVar3 = 0;
      }
      else {
        sVar3 = 0x100;
      }
      *psStack_60 = sVar3 + (short)(iStack_20 << 4);
      psStack_60[1] = sVar3 + (short)(iStack_10 << 4);
      psStack_60[2] = 0;
      psStack_60[3] = 0;
      psStack_60 = psStack_60 + 4;
    }
    else if (iStack_40 == 2) {
      if (iVar1 == 0) {
        uStack_7c = 0x3d4ccccd;
      }
      else {
        uStack_7c = 0x3f733333;
      }
      *(undefined4 *)(psStack_60 + 2) = uStack_7c;
      *(undefined4 *)psStack_60 = uStack_7c;
      psStack_60 = psStack_60 + 4;
    }
    __ct__7FVectorFv(&fStack_e0);
    fStack_e0 = *pfVar2;
    fStack_dc = pfVar2[1];
    uStack_d8 = 0;
    uStack_d4 = 0x3f800000;
    ApplyMatrix__6MatrixCFRC7FVector(auStack_f0,afStack_d0,&fStack_e0);
    __as__7FVectorFRC7FVector(&fStack_e0,auStack_f0);
    fStack_e0 = (fStack_e0 + fStack_74) * 16.0;
    fStack_dc = (fStack_dc + fStack_78) * 16.0;
    if (fStack_e0 < 2.1474836e+09) {
      sVar3 = (short)(int)fStack_e0;
    }
    else {
      sVar3 = (short)(int)(fStack_e0 - 2.1474836e+09);
    }
    *psStack_60 = sVar3;
    if (fStack_dc < 2.1474836e+09) {
      sVar3 = (short)(int)fStack_dc;
    }
    else {
      sVar3 = (short)(int)(fStack_dc - 2.1474836e+09);
    }
    psStack_60[1] = sVar3;
    psStack_60[2] = 1;
    psStack_60[3] = 0;
    psStack_60 = psStack_60 + 4;
    pfVar2 = pfVar2 + 2;
  }
  return;
}

/* JP: 0x004d4c40  CNaviMap::GetFT4Vertex(_DWD*, FVector*, int, float, int, int)   [GetFT4Vertex__8CNaviMapFP4_DWDP7FVectorifii]  size=0x3f0 */
void GetFT4Vertex__8CNaviMapFP4_DWDP7FVectorifii
               (float param_1,int param_2,short *param_3,undefined4 param_4,undefined4 param_5,
               int param_6,int param_7)

{
  int iVar1;
  uint uVar2;
  short sVar3;
  short sVar4;
  float fVar5;
  undefined1 auStack_120 [16];
  undefined1 auStack_110 [64];
  float afStack_d0 [5];
  float fStack_bc;
  undefined4 uStack_b8;
  undefined4 uStack_b4;
  float fStack_b0;
  float fStack_ac;
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  float fStack_a0;
  float fStack_9c;
  undefined4 uStack_98;
  undefined4 uStack_94;
  undefined1 auStack_90 [24];
  float fStack_78;
  float fStack_74;
  int iStack_70;
  short *psStack_60;
  undefined4 uStack_50;
  undefined4 uStack_40;
  float fStack_30;
  int iStack_20;
  int iStack_10;
  
  iStack_70 = param_2;
  psStack_60 = param_3;
  uStack_50 = param_4;
  uStack_40 = param_5;
  fStack_30 = param_1;
  iStack_20 = param_6;
  iStack_10 = param_7;
  __ct__7FVectorFv(auStack_90);
  __ct__7FVectorFv(afStack_d0);
  __ct__7FVectorFv(afStack_d0 + 4);
  __ct__7FVectorFv(&fStack_b0);
  __ct__7FVectorFv(&fStack_a0);
  __as__7FVectorFRC7FVector(auStack_90,uStack_50);
  uStack_94 = 0x3f800000;
  uStack_a4 = 0x3f800000;
  uStack_b4 = 0x3f800000;
  afStack_d0[3] = 1.0;
  uStack_98 = 0;
  uStack_a8 = 0;
  uStack_b8 = 0;
  afStack_d0[2] = 0.0;
  afStack_d0[0] = -fStack_30;
  afStack_d0[1] = -fStack_30;
  fStack_a0 = fStack_30;
  afStack_d0[4] = fStack_30;
  fStack_9c = fStack_30;
  fStack_ac = fStack_30;
  fStack_bc = afStack_d0[1];
  fStack_b0 = afStack_d0[0];
  __ct__6MatrixFv(auStack_110);
  GetRotMatrix__FR6Matrixi(auStack_110,uStack_40);
  SetPos__6MatrixFRC7FVector(auStack_110,auStack_90);
  iVar1 = *(int *)(iStack_70 + 0xa4);
  if (iVar1 < 0) {
    iVar1 = iVar1 + 1;
  }
  fStack_74 = (float)(*(int *)(iStack_70 + 0x9c) + 0x700 + (iVar1 >> 1));
  iVar1 = *(int *)(iStack_70 + 0xa8);
  if (iVar1 < 0) {
    iVar1 = iVar1 + 1;
  }
  fStack_78 = (float)(*(int *)(iStack_70 + 0xa0) + 0x720 + (iVar1 >> 1));
  iStack_20 = iStack_20 << 4;
  iStack_10 = iStack_10 << 4;
  for (uVar2 = 0; (int)uVar2 < 4; uVar2 = uVar2 + 1) {
    if ((uVar2 & 1) == 0) {
      sVar4 = 0;
    }
    else {
      sVar4 = 0x100;
    }
    if ((uVar2 & 2) == 0) {
      sVar3 = 0;
    }
    else {
      sVar3 = 0x100;
    }
    *psStack_60 = sVar4 + (short)iStack_20;
    psStack_60[1] = sVar3 + (short)iStack_10;
    psStack_60[2] = 0;
    psStack_60[3] = 0;
    psStack_60 = psStack_60 + 4;
    ApplyMatrix__6MatrixCFRC7FVector(auStack_120,auStack_110,afStack_d0 + uVar2 * 4);
    __as__7FVectorFRC7FVector(afStack_d0 + uVar2 * 4,auStack_120);
    __adv__7FVectorFf(*(undefined4 *)(iStack_70 + 0x8c),afStack_d0 + uVar2 * 4);
    afStack_d0[uVar2 * 4] = afStack_d0[uVar2 * 4] + fStack_74;
    afStack_d0[uVar2 * 4 + 1] = afStack_d0[uVar2 * 4 + 1] + fStack_78;
    afStack_d0[uVar2 * 4] = afStack_d0[uVar2 * 4] * 16.0;
    afStack_d0[uVar2 * 4 + 1] = afStack_d0[uVar2 * 4 + 1] * 16.0;
    fVar5 = afStack_d0[uVar2 * 4];
    if (fVar5 < 2.1474836e+09) {
      sVar4 = (short)(int)fVar5;
    }
    else {
      sVar4 = (short)(int)(fVar5 - 2.1474836e+09);
    }
    *psStack_60 = sVar4;
    fVar5 = afStack_d0[uVar2 * 4 + 1];
    if (fVar5 < 2.1474836e+09) {
      sVar4 = (short)(int)fVar5;
    }
    else {
      sVar4 = (short)(int)(fVar5 - 2.1474836e+09);
    }
    psStack_60[1] = sVar4;
    psStack_60[2] = 1;
    psStack_60[3] = 0;
    psStack_60 = psStack_60 + 4;
  }
  return;
}

/* JP: 0x004d5030  CNaviMap::AddItem(int, FVector&, int, int, bool, unsigned int)   [AddItem__8CNaviMapFiR7FVectoriibUi]  size=0x184 */
uint AddItem__8CNaviMapFiR7FVectoriibUi
               (int param_1,uint param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,
               undefined1 param_6,undefined4 param_7)

{
  uint uVar1;
  uint uVar2;
  uint uStack_60;
  
  if ((param_2 & 0x10000) == 0) {
    uVar1 = 0;
    while ((uVar2 = 0xffffffff, uStack_60 = param_2, (int)uVar1 < 0x20 &&
           (uVar2 = uVar1,
           (*(uint *)(param_1 + ((int)uVar1 >> 5) * 4 + 0xb8) & 1 << (uVar1 & 0x1f) & 0x1fU) != 0)))
    {
      uVar1 = uVar1 + 1;
    }
  }
  else {
    uStack_60 = param_2 & 0xffff;
    for (uVar1 = 0; uVar2 = 0xffffffff, (int)uVar1 < 0x20; uVar1 = uVar1 + 1) {
      if ((*(uint *)(param_1 + ((int)(0x1f - uVar1) >> 5) * 4 + 0xb8) & 1 << (uVar1 & 0x1f) & 0x1fU)
          == 0) {
        uVar2 = 0x1f - uVar1;
        break;
      }
    }
  }
  if (-1 < (int)uVar2) {
    SetItem__8CNaviMapFiiR7FVectoriibUi
              (param_1,uVar2,uStack_60,param_3,param_4,param_5,param_6,param_7);
  }
  return uVar2;
}

/* JP: 0x004d51c0  CNaviMap::SetItem(int, int, FVector&, int, int, bool, unsigned int)   [SetItem__8CNaviMapFiiR7FVectoriibUi]  size=0x1c4 */
void SetItem__8CNaviMapFiiR7FVectoriibUi
               (int param_1,uint param_2,int param_3,undefined4 param_4,ushort param_5,byte param_6,
               char param_7,undefined4 param_8)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  
  if ((int)param_2 < 0x20) {
    if (*(int *)(param_1 + 0xb4) == 0) {
      uVar1 = __nwa__FUi(0x200);
      *(undefined4 *)(param_1 + 0xb4) = uVar1;
      memset(*(undefined4 *)(param_1 + 0xb4),0,0x200);
    }
    iVar3 = *(int *)(param_1 + 0xb4) + param_2 * 0x10;
    iVar2 = param_1 + ((int)param_2 >> 5) * 4;
    *(uint *)(iVar2 + 0xb8) = *(uint *)(iVar2 + 0xb8) | 1 << (param_2 & 0x1f);
    SetShortPos__FPsP7FVector(iVar3,param_4);
    *(ushort *)(iVar3 + 6) = *(ushort *)(iVar3 + 6) & 0xfe00 | param_5 & 0x1ff;
    *(byte *)(iVar3 + 7) = *(byte *)(iVar3 + 7) & 0xe1 | (param_6 & 0xf) << 1;
    *(byte *)(iVar3 + 7) = *(byte *)(iVar3 + 7) & 0x7f | param_7 << 7;
    *(byte *)(iVar3 + 0xe) = *(byte *)(iVar3 + 0xe) & 0xe0 | (byte)param_3 & 0x1f;
    if (param_3 == 0) {
      *(short *)(iVar3 + 8) = (short)param_8;
      *(short *)(iVar3 + 10) = (short)((uint)param_8 >> 0x10);
    }
    param_1 = param_1 + ((int)param_2 >> 5) * 4;
    *(uint *)(param_1 + 0xb8) = *(uint *)(param_1 + 0xb8) | 1 << (param_2 & 0x1f);
  }
  return;
}

/* JP: 0x004d5390  CNaviMap::RemoveItem(int)   [RemoveItem__8CNaviMapFi]  size=0xbc */
void RemoveItem__8CNaviMapFi(int param_1,uint param_2)

{
  int iVar1;
  
  if ((*(uint *)(param_1 + ((int)param_2 >> 5) * 4 + 0xb8) & 1 << (param_2 & 0x1f)) != 0) {
    iVar1 = param_1 + ((int)param_2 >> 5) * 4;
    *(uint *)(iVar1 + 0xb8) = *(uint *)(iVar1 + 0xb8) & ~(1 << (param_2 & 0x1f));
    memset(*(int *)(param_1 + 0xb4) + param_2 * 0x10,0,0x10);
  }
  return;
}

/* JP: 0x004d5450  CNaviMap::DspItem(int, bool)   [DspItem__8CNaviMapFib]  size=0x90 */
void DspItem__8CNaviMapFib(undefined4 param_1,undefined4 param_2,char param_3)

{
  long lVar1;
  
  lVar1 = GetItem__8CNaviMapFi(param_1,param_2);
  if (lVar1 != 0) {
    *(byte *)((int)lVar1 + 7) = *(byte *)((int)lVar1 + 7) & 0x7f | (param_3 != '\0') << 7;
  }
  return;
}

/* JP: 0x004d54e0  CNaviMap::GetItem(int)   [GetItem__8CNaviMapFi]  size=0x74 */
int GetItem__8CNaviMapFi(int param_1,uint param_2)

{
  int iVar1;
  
  if ((*(uint *)(param_1 + ((int)param_2 >> 5) * 4 + 0xb8) & 1 << (param_2 & 0x1f)) == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = *(int *)(param_1 + 0xb4) + param_2 * 0x10;
  }
  return iVar1;
}

/* JP: 0x004d5560  CNaviMap::~CNaviMap()   [__dt__8CNaviMapFv]  size=0x94 */
int __dt__8CNaviMapFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 8) = &__vt__8CNaviMap;
    Release__8CNaviMapFv(param_1);
    __dt__6CImageFv(param_1 + 0x110,0xffffffffffffffff);
    __dt__17DelayDeleteObjectFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}
