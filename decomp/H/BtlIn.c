/*
 * BtlIn.c -- Ghidra decompiler output (SLPM_602.19, JP Furokuban), tidied by tools/E_gen_decomp.py
 * 15 functions. Types: u8/u16/u32/u64 = undefined1/2/4/8. Addresses in comments are JP main-exe addresses.
 */

/* ---- 0x003ad2c0 size 0x574  BtlIn::BtlIn(v)
 *      mangled: __ct__5BtlInFv */
VIF1Prim * __ct__5BtlInFv(VIF1Prim *param_1)

{
  u32 uVar1;
  u32 uVar2;
  u64 uVar3;
  u32 uVar4;
  u8 uVar5;
  u8 uVar7;
  u16 uVar9;
  u32 uVar10;
  u32 uVar11;
  u32 uVar12;
  u32 uVar13;
  VIF1Prim *pVVar14;
  int iVar15;
  u64 uVar16;
  void *pvVar17;
  void *pvVar18;
  void *pvVar19;
  uint uVar20;
  u32 uVar21;
  uint uVar22;
  uint uVar23;
  uint uVar24;
  uint uVar25;
  byte *pbVar26;
  VIF1Prim *pVVar27;
  uint *puVar28;
  u32 uStack_30;
  u32 uStack_2c;
  u32 uStack_28;
  u32 uStack_24;
  float fStack_18;
  float fStack_14;
  VIF1Prim *pVStack_10;
  u32 uVar6;
  undefined3 uVar8;
  
  pVStack_10 = param_1;
  __ct__8VIF1PrimFv(param_1);
  __ct__17DelayDeleteObjectFv(pVStack_10 + 1);
  __ct__7CPolObjFv(&pVStack_10[1].bFlags);
  pVStack_10->pVptr = __vt__5BtlIn;
  pVStack_10[1].dwEnv = 0x407590;
  pVStack_10[2].bFlags = 0xa0;
  pVStack_10[2].b_pad0d = 0x75;
  pVStack_10[2].nZvolume = 0x40;
  puVar28 = &pVStack_10[3].dw_unk4;
  do {
    __ct__4_QWDFv(puVar28);
    puVar28 = puVar28 + 4;
  } while ((VIF1Prim *)puVar28 != pVStack_10 + 8);
  pVVar27 = pVStack_10 + 8;
  do {
    __ct__4_QWDFv(pVVar27);
    pVVar27 = (VIF1Prim *)&pVVar27->pVptr;
  } while (pVVar27 != (VIF1Prim *)&pVStack_10[0x11].bFlags);
  pbVar26 = &pVStack_10[0x11].bFlags;
  do {
    __ct__4_QWDFv(pbVar26);
    pbVar26 = (byte *)((int)pbVar26 + 0x10);
  } while ((VIF1Prim *)pbVar26 != pVStack_10 + 0x14);
  __ct__6MatrixFv(&pVStack_10[0x14].pVptr);
  __ct__12FrameTextureFv(&pVStack_10[0x1a].dwEnv);
  uVar16 = GetViewMatrix__9GsxCameraFv(camera__4CApp);
  __as__6MatrixFRC6Matrix(&pVStack_10[0x14].pVptr,uVar16);
  pVStack_10[0x14].dw_unk0 = 0;
  SetFase__7tagFaseFi(pVStack_10 + 0x19,0);
  SetFase__7tagFaseFi(&pVStack_10[0x19].dwEnv,0);
  pVVar14 = pVStack_10;
  pVStack_10[0x18].dw_unk0 =
       (uint)((((float)pVStack_10[0x16].dwEnv + (float)pVStack_10[0x17].dw_unk4) - 1792.0) /
             -(float)pVStack_10[0x14].pVptr);
  fStack_14 = (((float)pVStack_10[0x16].dwEnv + (float)pVStack_10[0x17].dw_unk4) - 2304.0) /
              -(float)pVStack_10[0x14].pVptr;
  pVStack_10[0x18].dw_unk4 =
       (uint)(((*(float *)&pVStack_10[0x16].bFlags + (float)pVStack_10[0x17].dwEnv) - 1824.0) /
             -(float)pVStack_10[0x15].pVptr);
  fStack_18 = ((*(float *)&pVStack_10[0x16].bFlags + (float)pVStack_10[0x17].dwEnv) - 2272.0) /
              -(float)pVStack_10[0x15].pVptr;
  pVStack_10[0x18].dwEnv = (uint)((fStack_14 - (float)pVStack_10[0x18].dw_unk0) / 512.0);
  *(float *)&pVStack_10[0x18].bFlags = (fStack_18 - (float)pVStack_10[0x18].dw_unk4) / 448.0;
  *(u16 *)&pVStack_10[0x14].dw_unk4 = 0x80;
  pVVar27 = pVStack_10 + 3;
  memset(&pVVar27->dw_unk4,0,0x60);
  pVVar27->dw_unk4 = 0x60000005;
  pVVar14[3].pVptr = (void *)0x50000005;
  pVVar14[4].dw_unk0 = 0x8004;
  pVVar14[4].dw_unk4 = 0x10000000;
  pVVar14[4].dwEnv = 0xe;
  pVVar14[4].bFlags = 0;
  pVVar14[4].b_pad0d = 0;
  pVVar14[4].nZvolume = 0;
  *(u64 *)&pVVar14[4].pVptr = 0x30000;
  pVVar14[5].dw_unk4 = 0x47;
  pVVar14[5].dwEnv = 0;
  pVVar14[5].bFlags = 1;
  pVVar14[5].b_pad0d = 0;
  pVVar14[5].nZvolume = 0;
  pVVar14[5].pVptr = (void *)0x0;
  pVVar14[6].dw_unk0 = 0x14;
  pVVar14[6].dw_unk4 = 0;
  pVVar14[6].dwEnv = 5;
  pVVar14[6].bFlags = 0;
  pVVar14[6].b_pad0d = 0;
  pVVar14[6].nZvolume = 0;
  *(u64 *)&pVVar14[6].pVptr = 8;
  pVVar14[7].dw_unk4 = 0x44;
  pVVar14[7].dwEnv = 0;
  pVVar14[7].bFlags = 0x42;
  pVVar14[7].b_pad0d = 0;
  pVVar14[7].nZvolume = 0;
  pVVar14[7].pVptr = (void *)0x0;
  memset(pVStack_10 + 8,0,0x60);
  memset(&pVStack_10[0xc].pVptr,0,0x60);
  pVStack_10[8].dw_unk0 = 0x60000005;
  pVStack_10[8].bFlags = 5;
  pVStack_10[8].b_pad0d = 0;
  pVStack_10[8].nZvolume = 0x5000;
  *(u64 *)&pVStack_10[8].pVptr = 0x4023400000008001;
  pVStack_10[9].dw_unk4 = 0x5151;
  pVStack_10[9].dwEnv = 0;
  pVStack_10[9].bFlags = 0;
  pVStack_10[9].b_pad0d = 0;
  pVStack_10[9].nZvolume = 0;
  pVStack_10[9].pVptr = (void *)0x0;
  pVStack_10[10].dw_unk0 = 0;
  pVStack_10[10].dw_unk4 = (int)(short)pVStack_10[0x14].dw_unk4;
  pVStack_10[10].dwEnv = 0x7000;
  pVStack_10[10].bFlags = 0;
  pVStack_10[10].b_pad0d = 0x72;
  pVStack_10[10].nZvolume = 0;
  pVStack_10[10].pVptr = (void *)0x0;
  pVStack_10[0xb].dw_unk0 = 0;
  pVStack_10[0xb].dw_unk4 = 0;
  pVStack_10[0xb].dwEnv = 0;
  pVStack_10[0xb].bFlags = 0;
  pVStack_10[0xb].b_pad0d = 0;
  pVStack_10[0xb].nZvolume = 0;
  pVStack_10[0xb].pVptr = (void *)(int)(short)pVStack_10[0x14].dw_unk4;
  pVStack_10[0xc].dw_unk0 = 0x9000;
  pVStack_10[0xc].dw_unk4 = 0x8e00;
  pVStack_10[0xc].dwEnv = 0;
  pVStack_10[0xc].bFlags = 0;
  pVStack_10[0xc].b_pad0d = 0;
  pVStack_10[0xc].nZvolume = 0;
  uVar1 = pVStack_10[8].dw_unk0;
  uVar2 = pVStack_10[8].dw_unk4;
  uVar24 = pVStack_10[8].dwEnv;
  uVar25 = *(uint *)&pVStack_10[8].bFlags;
  uVar16 = *(u64 *)&pVStack_10[8].pVptr;
  uVar22 = pVStack_10[9].dw_unk4;
  uVar23 = pVStack_10[9].dwEnv;
  uVar3._0_1_ = pVStack_10[9].bFlags;
  uVar3._1_1_ = pVStack_10[9].b_pad0d;
  uVar3._2_2_ = pVStack_10[9].nZvolume;
  uVar3._4_4_ = pVStack_10[9].pVptr;
  pvVar19 = (void *)pVStack_10[10].dw_unk0;
  uVar20 = pVStack_10[10].dw_unk4;
  uVar4 = pVStack_10[10].dwEnv;
  uVar5 = pVStack_10[10].bFlags;
  uVar7 = pVStack_10[10].b_pad0d;
  uVar9 = pVStack_10[10].nZvolume;
  uVar8 = CONCAT21(uVar9,uVar7);
  uVar6 = CONCAT31(uVar8,uVar5);
  pvVar17 = pVStack_10[10].pVptr;
  pvVar18 = (void *)pVStack_10[0xb].dw_unk0;
  pVStack_10[0xc].pVptr = (void *)uVar1;
  pVStack_10[0xd].dw_unk0 = uVar2;
  pVStack_10[0xd].dw_unk4 = uVar24;
  pVStack_10[0xd].dwEnv = uVar25;
  uVar21 = (u32)uVar16;
  pVStack_10[0xd].bFlags = (char)uVar21;
  pVStack_10[0xd].b_pad0d = (char)((uint)uVar21 >> 8);
  pVStack_10[0xd].nZvolume = (short)((uint)uVar21 >> 0x10);
  pVStack_10[0xd].pVptr = (void *)((ulong)uVar16 >> 0x20);
  pVStack_10[0xe].dw_unk0 = uVar22;
  pVStack_10[0xe].dw_unk4 = uVar23;
  pVStack_10[0xe].dwEnv = (uint)uVar3;
  pVStack_10[0xe].bFlags = (char)uVar3._4_4_;
  pVStack_10[0xe].b_pad0d = (char)((uint)uVar3._4_4_ >> 8);
  pVStack_10[0xe].nZvolume = (short)((uint)uVar3._4_4_ >> 0x10);
  pVStack_10[0xe].pVptr = pvVar19;
  pVStack_10[0xf].dw_unk0 = uVar20;
  pVStack_10[0xf].dw_unk4 = uVar4;
  pVStack_10[0xf].dwEnv = uVar6;
  *(void **)&pVStack_10[0xf].bFlags = pvVar17;
  pVStack_10[0xf].pVptr = pvVar18;
  uVar10 = pVStack_10[0xb].dw_unk4;
  uVar11 = pVStack_10[0xb].dwEnv;
  uVar23 = *(uint *)&pVStack_10[0xb].bFlags;
  pvVar17 = pVStack_10[0xb].pVptr;
  uVar12 = pVStack_10[0xc].dw_unk0;
  uVar13 = pVStack_10[0xc].dw_unk4;
  uVar20 = pVStack_10[0xc].dwEnv;
  uVar22 = *(uint *)&pVStack_10[0xc].bFlags;
  pVStack_10[0x10].dw_unk0 = uVar10;
  pVStack_10[0x10].dw_unk4 = uVar11;
  pVStack_10[0x10].dwEnv = uVar23;
  *(void **)&pVStack_10[0x10].bFlags = pvVar17;
  pVStack_10[0x10].pVptr = (void *)uVar12;
  pVStack_10[0x11].dw_unk0 = uVar13;
  pVStack_10[0x11].dw_unk4 = uVar20;
  pVStack_10[0x11].dwEnv = uVar22;
  __ct__4_QWDFv(&uStack_30);
  uStack_28 = 0x80;
  uStack_2c = 0x80;
  uStack_30 = 0x80;
  uStack_24 = 0;
  iVar15 = CreatePolygon__5BtlInFv(pVStack_10);
  iVar15 = iVar15 + 0x17;
  uVar20 = __nwa__FUi(iVar15 * 0x10);
  pVStack_10->dw_unk0 = uVar20;
  uVar20 = __nwa__FUi(iVar15 * 0x10);
  pVStack_10->dw_unk4 = uVar20;
  memset((void *)pVStack_10->dw_unk0,0,(long)(iVar15 * 0x10));
  memset((void *)pVStack_10->dw_unk4,0,(long)(iVar15 * 0x10));
  return pVStack_10;
}

/* ---- 0x003ad870 size 0x194  BtlIn::~BtlIn(v)
 *      mangled: __dt__5BtlInFv */
int * __dt__5BtlInFv(int *param_1,short param_2)

{
  int iVar1;
  int *piVar2;
  
  if (param_1 != (int *)0x0) {
    param_1[4] = (int)__vt__5BtlIn;
    param_1[7] = 0x407590;
    param_1[0xd] = 0x4075a0;
    ourBtlIn__5BtlIn = 0;
    if (*param_1 != 0) {
      __dla__FPv(*param_1);
      *param_1 = 0;
    }
    if (param_1[1] != 0) {
      __dla__FPv(param_1[1]);
      param_1[1] = 0;
    }
    if (param_1[100] != 0) {
      iVar1 = param_1[100];
      if (iVar1 != 0) {
        (**(code **)(*(int *)(iVar1 + 0xd4) + 8))(iVar1,1);
      }
      param_1[100] = 0;
    }
    piVar2 = param_1;
    if (param_1 != (int *)0x0) {
      piVar2 = param_1 + 8;
    }
    Dispose__7CPollerFP7CPolObj(app__4CApp + 0x48,piVar2);
    __dt__12FrameTextureFv(param_1 + 0x84,0xffffffffffffffff);
    __dt__7CPolObjFv(param_1 + 8,0);
    __dt__17DelayDeleteObjectFv(param_1 + 5,0);
    __dt__8VIF1PrimFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* ---- 0x003ada10 size 0x828  BtlIn::CreatePolygon(v)
 *      mangled: CreatePolygon__5BtlInFv */
int CreatePolygon__5BtlInFv(int param_1)

{
  uint uVar1;
  int iVar2;
  u32 *puVar3;
  u32 uVar4;
  float *pfVar5;
  u64 uVar6;
  u64 uVar7;
  long lVar8;
  uint uVar9;
  int iVar10;
  ushort *puVar11;
  long lVar12;
  float fVar13;
  u8 auStack_60 [16];
  u8 auStack_50 [20];
  float fStack_3c;
  float fStack_38;
  u32 uStack_34;
  u32 uStack_30;
  u32 uStack_2c;
  u32 uStack_28;
  float fStack_24;
  float fStack_20;
  int iStack_1c;
  int iStack_18;
  int iStack_14;
  int iStack_10;
  
  puVar11 = &_BI_Pol_Data;
  iStack_14 = 0;
  iStack_10 = param_1;
  uVar1 = rand();
  uVar9 = uVar1 & 7;
  if (((int)uVar1 < 0) && (uVar9 != 0)) {
    uVar9 = uVar9 - 8;
  }
  iVar2 = rand();
  iStack_18 = (int)*(short *)(offgrp + uVar9 * 8) +
              (int)*(short *)(offgrp + uVar9 * 8 + 4) * (iVar2 % 0x28);
  iVar2 = rand();
  iStack_1c = (int)*(short *)(offgrp + uVar9 * 8 + 2) +
              (int)*(short *)(offgrp + uVar9 * 8 + 6) * (iVar2 % 0x28);
  fStack_20 = (float)(iStack_18 + -0x100);
  fStack_24 = (float)(iStack_1c + -0xe0);
  Create__12FrameTextureF6GS_PSMUsUs(iStack_10 + 0x210,2,0x200,0x1c0);
  Capture__12FrameTextureFv(iStack_10 + 0x210);
  uVar6 = GetRleLength__FPv(0x54694e);
  uStack_28 = GetRleLength__FPv(0x546952);
  uVar6 = RleUnCompress__FPvii(0x524748,uStack_28,uVar6);
  uVar7 = getBuffer__9BufMemoryFv(uVar6);
  RenderOffscreen__12FrameTextureFiPcPcssssUsUsUl
            (iStack_10 + 0x210,0x2c,0x524708,uVar7,(short)(int)fStack_20 + -0x80,
             (short)(int)fStack_24 + -0x70,0x300,0x2a0);
  __dt__9BufMemoryFv(uVar6,1);
  uVar6 = GetRleLength__FPv(0x5246ee);
  uStack_28 = GetRleLength__FPv(0x5246f2);
  uVar6 = RleUnCompress__FPvii(0x50de50,uStack_28,uVar6);
  uVar7 = getBuffer__9BufMemoryFv(uVar6);
  RenderOffscreen__12FrameTextureFiPcPcssssUsUsUl
            (iStack_10 + 0x210,0x2c,0x50de10,uVar7,(short)(int)fStack_20 + -0x80,
             (short)(int)fStack_24 + -0x70,0x300,0x2a0);
  __dt__9BufMemoryFv(uVar6,1);
  StoreImage__12FrameTextureFiiiiii(iStack_10 + 0x210,0x200,0x1c0,100,100,0x400,0x400);
  uStack_2c = 0x3a800000;
  uStack_30 = 0x3a800000;
  PixelTo3D__5BtlInFff((float)iStack_18,(float)iStack_1c,auStack_50,iStack_10);
  puVar3 = (u32 *)vx__7FVectorFv(auStack_50);
  *(u32 *)(iStack_10 + 0x1f0) = *puVar3;
  lVar12 = 0;
  for (; *puVar11 != 0xffff; puVar11 = puVar11 + 5) {
    if (*puVar11 == 0x7000) {
      lVar12 = (long)(short)puVar11[1];
      puVar11 = puVar11 + 5;
    }
    lVar8 = __nw__FUi(0xe0);
    uVar4 = 0;
    if (lVar8 != 0) {
      uVar4 = __ct__9BI_PolGrpFUi(lVar8,lVar12);
    }
    for (; uStack_34 = uVar4, *puVar11 != 0x8000; puVar11 = puVar11 + 5) {
      lVar8 = __nw__FUi(0xa0);
      uVar6 = 0;
      if (lVar8 != 0) {
        uVar6 = __ct__6BI_PolFv(lVar8);
      }
      Create__6BI_PolFi(uVar6,*puVar11);
      for (iVar2 = 0; iVar10 = (int)uVar6, iVar2 < (int)(uint)*puVar11; iVar2 = iVar2 + 1) {
        fStack_38 = fStack_20 + (float)(int)*(short *)(_shareVtx + (short)puVar11[iVar2 + 1] * 4);
        fStack_3c = fStack_24 +
                    (float)(int)*(short *)(_shareVtx + (short)puVar11[iVar2 + 1] * 4 + 2);
        PixelTo3D__5BtlInFff((float)(int)fStack_38,(float)(int)fStack_3c,auStack_60,iStack_10);
        __as__7FVectorFRC7FVector(*(int *)(iVar10 + 0x10) + iVar2 * 0x10,auStack_60);
        fVar13 = fStack_38 + 100.0;
        pfVar5 = (float *)vx__7FVectorFv(*(int *)(iVar10 + 0x14) + iVar2 * 0x10);
        *pfVar5 = fVar13;
        fVar13 = fStack_3c + 100.0;
        pfVar5 = (float *)vy__7FVectorFv(*(int *)(iVar10 + 0x14) + iVar2 * 0x10);
        *pfVar5 = fVar13;
        puVar3 = (u32 *)vz__7FVectorFv(*(int *)(iVar10 + 0x14) + iVar2 * 0x10);
        *puVar3 = 0x3f800000;
        pfVar5 = (float *)vx__7FVectorFv(*(int *)(iVar10 + 0x14) + iVar2 * 0x10);
        if (*pfVar5 < 0.0) {
          puVar3 = (u32 *)vx__7FVectorFv(*(int *)(iVar10 + 0x14) + iVar2 * 0x10);
          *puVar3 = 0;
        }
        pfVar5 = (float *)vx__7FVectorFv(*(int *)(iVar10 + 0x14) + iVar2 * 0x10);
        if (1024.0 < *pfVar5) {
          puVar3 = (u32 *)vx__7FVectorFv(*(int *)(iVar10 + 0x14) + iVar2 * 0x10);
          *puVar3 = 0x447fe000;
        }
        pfVar5 = (float *)vy__7FVectorFv(*(int *)(iVar10 + 0x14) + iVar2 * 0x10);
        if (*pfVar5 < 0.0) {
          puVar3 = (u32 *)vy__7FVectorFv(*(int *)(iVar10 + 0x14) + iVar2 * 0x10);
          *puVar3 = 0;
        }
        pfVar5 = (float *)vy__7FVectorFv(*(int *)(iVar10 + 0x14) + iVar2 * 0x10);
        if (648.0 < *pfVar5) {
          puVar3 = (u32 *)vy__7FVectorFv(*(int *)(iVar10 + 0x14) + iVar2 * 0x10);
          *puVar3 = 0x44220000;
        }
      }
      *(u32 *)(iVar10 + 0xc) = 0x3c23d70a;
      CalcCenter__6BI_PolFv(uVar6);
      CalcOffset__6BI_PolFv(uVar6);
      AddPol__9BI_PolGrpFP6BI_Pol(uStack_34,uVar6);
      iStack_14 = iStack_14 + 1;
      uVar4 = uStack_34;
    }
    AddGroup__5BtlInFP9BI_PolGrp(iStack_10,uStack_34);
    lVar12 = (long)((int)lVar12 + 1);
  }
  return iStack_14;
}

/* ---- 0x003ae240 size 0x60  BtlIn::AddGroup(P9BI_PolGrp)
 *      mangled: AddGroup__5BtlInFP9BI_PolGrp */
void AddGroup__5BtlInFP9BI_PolGrp(int param_1,u32 param_2)

{
  if (*(int *)(param_1 + 400) == 0) {
    *(u32 *)(param_1 + 400) = param_2;
  }
  else {
    Add__5CListFP5CList(*(u32 *)(param_1 + 400),param_2);
  }
  return;
}

/* ---- 0x003ae2a0 size 0x30  BtlIn::getPacket(v)
 *      mangled: getPacket__5BtlInFv */
void getPacket__5BtlInFv(u32 param_1)

{
  GetDrawPacket__5BtlInFi(param_1,m_Env__8VIF1Prim & 1);
  return;
}

/* ---- 0x003ae2d0 size 0x1f8  BtlIn::GetDrawPacket(i)
 *      mangled: GetDrawPacket__5BtlInFi */
u32 GetDrawPacket__5BtlInFi(int param_1,int param_2)

{
  u32 *puVar1;
  int iVar2;
  u32 uVar3;
  u32 *puVar4;
  
  puVar1 = *(u32 **)(param_1 + param_2 * 4);
  *puVar1 = 0x50000000;
  puVar1[1] = param_1 + 0x230;
  puVar1[3] = 0x13000000;
  puVar1[4] = 0x50000000;
  uVar3 = GetBuffer__7CPacketCFv(*(u32 *)(param_1 + 0x414));
  puVar1[5] = uVar3;
  puVar1[8] = 0x50000000;
  puVar1[9] = param_1 + 0x40;
  puVar4 = puVar1 + 0xc;
  iVar2 = *(int *)(param_1 + 500);
  if (iVar2 == 9999) {
    *puVar4 = 0x50000000;
    puVar1[0xd] = param_1 + param_2 * 0x60 + 0xa0;
    puVar4 = puVar1 + 0x10;
  }
  else if ((((iVar2 == 10) || (iVar2 == 5)) || (iVar2 == 4)) ||
          (((iVar2 == 3 || (iVar2 == 2)) || ((iVar2 == 1 || (iVar2 == 0)))))) {
    *puVar4 = 0x50000000;
    puVar1[0xd] = param_1 + param_2 * 0x60 + 0xa0;
    puVar4 = (u32 *)
             SetPacket__9BI_PolGrpFP4_QWD(*(u32 *)(param_1 + 400),puVar1 + 0x10);
  }
  *puVar4 = 0x60000000;
  *(int *)(param_1 + param_2 * 0x60 + 0xcc) = (int)*(short *)(param_1 + 0x194);
  *(int *)(param_1 + param_2 * 0x60 + 0xec) = (int)*(short *)(param_1 + 0x194);
  return *(u32 *)(param_1 + param_2 * 4);
}

/* ---- 0x003ae4d0 size 0x8c4  BtlIn::Polling(v)
 *      mangled: Polling__5BtlInFv */
u64 Polling__5BtlInFv(VIF1Prim *param_1)

{
  u16 uVar1;
  uint uVar2;
  float *pfVar3;
  u32 *puVar4;
  int iVar5;
  long lVar6;
  byte *pbVar7;
  u32 uVar8;
  int iStack_1c;
  int iStack_18;
  
  lVar6 = isPaused__4CAppFv(app__4CApp);
  if (lVar6 == 0) {
    AddTime__9BI_PolGrpFf(0x3d08882f,param_1[0x14].dw_unk0);
  }
  CalcMatrix__9BI_PolGrpFv(param_1[0x14].dw_unk0);
  uVar2 = param_1[0x19].dw_unk0;
  if (uVar2 != 9999) {
    if (uVar2 == 4) {
      uVar2 = param_1[0x19].dw_unk4 + 1;
      param_1[0x19].dw_unk4 = uVar2;
      if ((int)uVar2 < 0x41) {
        for (uVar2 = param_1[0x14].dw_unk0; uVar2 != 0; uVar2 = GetNext__5CListCFv(uVar2)) {
          *(float *)(uVar2 + 0xd0) = *(float *)(uVar2 + 0xd0) + 0.0003;
          for (iStack_1c = *(int *)(uVar2 + 0xc); iStack_1c != 0;
              iStack_1c = GetNext__5CListCFv(iStack_1c)) {
            pfVar3 = (float *)vw__7FVectorFv(iStack_1c + 0x80);
            *pfVar3 = *pfVar3 - 6.4;
          }
        }
      }
      else {
        SetFase__7tagFaseFi(param_1 + 0x19,9999);
      }
    }
    else if (uVar2 == 3) {
      uVar2 = param_1[0x19].dw_unk4 + 1;
      param_1[0x19].dw_unk4 = uVar2;
      if ((int)uVar2 < 0x41) {
        for (uVar2 = param_1[0x14].dw_unk0; uVar2 != 0; uVar2 = GetNext__5CListCFv(uVar2)) {
          *(float *)(uVar2 + 0xd0) = *(float *)(uVar2 + 0xd0) + 0.0003;
          for (iStack_18 = *(int *)(uVar2 + 0xc); iStack_18 != 0;
              iStack_18 = GetNext__5CListCFv(iStack_18)) {
            pfVar3 = (float *)vw__7FVectorFv(iStack_18 + 0x80);
            *pfVar3 = *pfVar3 - 2.0;
          }
        }
      }
      else {
        SetFase__7tagFaseFi(param_1 + 0x19,9999);
      }
    }
    else if (uVar2 == 2) {
      param_1[0x19].dw_unk4 = param_1[0x19].dw_unk4 + 1;
      if (param_1[0x19].dwEnv == 1) {
        uVar2 = param_1[0x19].dw_unk4;
        SetFase__7tagFaseFi(param_1 + 0x19,3);
        if (0x50 < (int)uVar2) {
          param_1[0x19].dw_unk0 = 4;
          param_1[0x19].dw_unk4 = 0x2c;
        }
      }
      else {
        for (uVar2 = param_1[0x14].dw_unk0; uVar2 != 0; uVar2 = GetNext__5CListCFv(uVar2)) {
          *(float *)(uVar2 + 0xd0) = *(float *)(uVar2 + 0xd0) + 0.0003;
        }
      }
    }
    else if (uVar2 == 1) {
      SetFase__7tagFaseFi(param_1 + 0x19,2);
      for (uVar2 = param_1[0x14].dw_unk0; uVar2 != 0; uVar2 = GetNext__5CListCFv(uVar2)) {
        pfVar3 = (float *)vx__7FVectorFv(uVar2 + 0xb0);
        if (*pfVar3 <= (float)param_1[0x18].pVptr) {
          iVar5 = rand();
          *(float *)(uVar2 + 200) = -((float)iVar5 / 4.2949673e+09);
        }
        else {
          iVar5 = rand();
          *(float *)(uVar2 + 200) = (float)iVar5 / 4.2949673e+09;
        }
        iVar5 = rand();
        *(float *)(uVar2 + 0xcc) = (float)(iVar5 + -0x3fffffff) / 1.0737418e+09;
        *(float *)(uVar2 + 200) = *(float *)(uVar2 + 200) * 0.5;
        *(float *)(uVar2 + 0xcc) = *(float *)(uVar2 + 0xcc) * 0.5;
        iVar5 = rand();
        uVar8 = GetRad((float)(iVar5 % 7));
        puVar4 = (u32 *)vx__7FVectorFv(uVar2 + 0xa0);
        *puVar4 = uVar8;
        iVar5 = rand();
        uVar8 = GetRad((float)(iVar5 % 7));
        puVar4 = (u32 *)vy__7FVectorFv(uVar2 + 0xa0);
        *puVar4 = uVar8;
      }
    }
    else if (uVar2 == 10) {
      uVar2 = param_1[0x19].dw_unk4 + 1;
      param_1[0x19].dw_unk4 = uVar2;
      if ((int)uVar2 < 9) {
        for (uVar2 = param_1[0x14].dw_unk0; uVar2 != 0; uVar2 = GetNext__5CListCFv(uVar2)) {
          for (iVar5 = *(int *)(uVar2 + 0xc); iVar5 != 0; iVar5 = GetNext__5CListCFv(iVar5)) {
            pfVar3 = (float *)vx__7FVectorFv(iVar5 + 0x80);
            *pfVar3 = *pfVar3 - 16.0;
            pfVar3 = (float *)vy__7FVectorFv(iVar5 + 0x80);
            *pfVar3 = *pfVar3 - 16.0;
            pfVar3 = (float *)vz__7FVectorFv(iVar5 + 0x80);
            *pfVar3 = *pfVar3 - 16.0;
          }
        }
      }
      else {
        SetFase__7tagFaseFi(param_1 + 0x19,1);
      }
    }
    else if (uVar2 == 0) {
      uVar2 = param_1[0x19].dw_unk4 + 1;
      param_1[0x19].dw_unk4 = uVar2;
      if ((int)uVar2 < 9) {
        for (uVar2 = param_1[0x14].dw_unk0; uVar2 != 0; uVar2 = GetNext__5CListCFv(uVar2)) {
          for (iVar5 = *(int *)(uVar2 + 0xc); iVar5 != 0; iVar5 = GetNext__5CListCFv(iVar5)) {
            pfVar3 = (float *)vx__7FVectorFv(iVar5 + 0x80);
            *pfVar3 = *pfVar3 + 16.0;
            pfVar3 = (float *)vy__7FVectorFv(iVar5 + 0x80);
            *pfVar3 = *pfVar3 + 16.0;
            pfVar3 = (float *)vz__7FVectorFv(iVar5 + 0x80);
            *pfVar3 = *pfVar3 + 16.0;
            pfVar3 = (float *)vw__7FVectorFv(iVar5 + 0x80);
            *pfVar3 = *pfVar3 + 8.0;
          }
        }
      }
      else {
        SetFase__7tagFaseFi(param_1 + 0x19,10);
      }
    }
  }
  if (param_1[0x19].dwEnv == 2) {
    if (param_1[0x19].dw_unk0 == 9999) {
      ReleaseOT__5WorldFP8VIF1Prim((World *)&m_World__4CApp,param_1);
      pbVar7 = (byte *)0x0;
      if (param_1 != (VIF1Prim *)0x0) {
        pbVar7 = &param_1[1].bFlags;
      }
      Dispose__7CPollerFP7CPolObj(app__4CApp + 0x48,pbVar7);
      (**(code **)(param_1[1].dwEnv + 0xc))();
      SetFase__7tagFaseFi(param_1 + 0x19,10000);
    }
  }
  else if (param_1[0x19].dwEnv == 1) {
    iVar5 = *(int *)&param_1[0x19].bFlags + 1;
    *(int *)&param_1[0x19].bFlags = iVar5;
    if (iVar5 < 9) {
      *(short *)&param_1[0x14].dw_unk4 = (short)param_1[0x14].dw_unk4 + -0x10;
      if ((short)param_1[0x14].dw_unk4 < 0) {
        uVar1 = 0;
      }
      else {
        uVar1 = (u16)param_1[0x14].dw_unk4;
      }
      *(u16 *)&param_1[0x14].dw_unk4 = uVar1;
    }
    else {
      SetFase__7tagFaseFi(&param_1[0x19].dwEnv,2);
    }
  }
  return 0;
}

/* ---- 0x003aeda0 size 0x104  BtlIn::OnlyDraw(v)
 *      mangled: OnlyDraw__5BtlInFv */
void OnlyDraw__5BtlInFv(int param_1)

{
  u32 uVar1;
  
  (**(code **)(*(int *)(ourBtlIn__5BtlIn + 0x10) + 0x30))();
  sceDmaSync(dmaVif1__6DmaMan,0,0);
  sceGsSyncPath(0,0);
  memset((void *)(param_1 + 0x160),0,0x30);
  *(u32 *)(param_1 + 0x160) = 0x50000000;
  uVar1 = GetDrawPacket__5BtlInFi(param_1,(m_Env__8VIF1Prim & 1) == 0);
  *(u32 *)(param_1 + 0x164) = uVar1;
  *(u32 *)(param_1 + 0x170) = 0x70000000;
  FlushCache(0);
  REG_DMAC_1_VIF1_CHCR = 0x41;
  sceDmaSend(dmaVif1__6DmaMan,param_1 + 0x160);
  DrawSync__3GsxFii(0,0);
  return;
}

/* ---- 0x003aeeb0 size 0x8c  BtlIn::PixelTo3D(ff)
 *      mangled: PixelTo3D__5BtlInFff */
void PixelTo3D__5BtlInFff(float param_1,float param_2,u32 param_3,int param_4)

{
  u8 auStack_50 [16];
  u32 uStack_40;
  int iStack_30;
  float fStack_20;
  float fStack_10;
  
  uStack_40 = param_3;
  iStack_30 = param_4;
  fStack_20 = param_1;
  fStack_10 = param_2;
  __ct__7FVectorFffff(*(float *)(param_4 + 0x1e0) + param_1 * *(float *)(param_4 + 0x1e8),
                      *(float *)(param_4 + 0x1e4) + param_2 * *(float *)(param_4 + 0x1ec),0x3f800000
                      ,0x3f800000,auStack_50);
  __ct__7FVectorFRC7FVector(uStack_40,auStack_50);
  return;
}

/* ---- 0x003aef40 size 0x50  BtlIn::CaptureBtlIn(v)
 *      mangled: CaptureBtlIn__5BtlInFv */
void CaptureBtlIn__5BtlInFv(void)

{
  u32 uVar1;
  long lVar2;
  
  lVar2 = __nw__FUi(0x430);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = __ct__5BtlInFv(lVar2);
  }
  ourBtlIn__5BtlIn = uVar1;
  return;
}

/* ---- 0x003aef90 size 0x7c  BtlIn::StartBtlIn(v)
 *      mangled: StartBtlIn__5BtlInFv */
void StartBtlIn__5BtlInFv(void)

{
  byte *pbVar1;
  
  if (ourBtlIn__5BtlIn != (VIF1Prim *)0x0) {
    pbVar1 = (byte *)0x0;
    if (ourBtlIn__5BtlIn != (VIF1Prim *)0x0) {
      pbVar1 = &ourBtlIn__5BtlIn[1].bFlags;
    }
    Entry__7CPollerFP7CPolObjib(app__4CApp + 0x48,pbVar1,0x80,0);
    AddOT__5WorldFiP8VIF1Prim((World *)&m_World__4CApp,0xe,ourBtlIn__5BtlIn);
    OnlyDraw__5BtlInFv(ourBtlIn__5BtlIn);
  }
  return;
}

/* ---- 0x003af010 size 0x38  BtlIn::StopBtlIn(v)
 *      mangled: StopBtlIn__5BtlInFv */
void StopBtlIn__5BtlInFv(void)

{
  if (ourBtlIn__5BtlIn != 0) {
    SetFase__7tagFaseFi(ourBtlIn__5BtlIn + 0x1fc,1);
  }
  return;
}

/* ---- 0x003b2580 size 0x8  BtlIn::@20@__dt(v)
 *      mangled: @20@__dt__5BtlInFv */
int * _20___dt__5BtlInFv(int param_1,short param_2)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)(param_1 + -0x14);
  if (piVar1 != (int *)0x0) {
    *(u8 **)(param_1 + -4) = __vt__5BtlIn;
    *(u32 *)(param_1 + 8) = 0x407590;
    *(u32 *)(param_1 + 0x20) = 0x4075a0;
    ourBtlIn__5BtlIn = 0;
    if (*piVar1 != 0) {
      __dla__FPv(*piVar1);
      *piVar1 = 0;
    }
    if (*(int *)(param_1 + -0x10) != 0) {
      __dla__FPv(*(u32 *)(param_1 + -0x10));
      *(u32 *)(param_1 + -0x10) = 0;
    }
    if (*(int *)(param_1 + 0x17c) != 0) {
      iVar2 = *(int *)(param_1 + 0x17c);
      if (iVar2 != 0) {
        (**(code **)(*(int *)(iVar2 + 0xd4) + 8))(iVar2,1);
      }
      *(u32 *)(param_1 + 0x17c) = 0;
    }
    iVar2 = 0;
    if (piVar1 != (int *)0x0) {
      iVar2 = param_1 + 0xc;
    }
    Dispose__7CPollerFP7CPolObj(app__4CApp + 0x48,iVar2);
    __dt__12FrameTextureFv(param_1 + 0x1fc,0xffffffffffffffff);
    __dt__7CPolObjFv(param_1 + 0xc,0);
    __dt__17DelayDeleteObjectFv(param_1,0);
    __dt__8VIF1PrimFv(piVar1,0);
    if (0 < param_2) {
      __dl__FPv(piVar1);
    }
  }
  return piVar1;
}

/* ---- 0x003b2590 size 0x8  BtlIn::@32@Polling(v)
 *      mangled: @32@Polling__5BtlInFv */
u64 _32_Polling__5BtlInFv(int param_1)

{
  u16 uVar1;
  float *pfVar2;
  int iVar3;
  u32 *puVar4;
  int iVar5;
  long lVar6;
  u32 uVar7;
  int iStack_1c;
  int iStack_18;
  
  lVar6 = isPaused__4CAppFv(app__4CApp);
  if (lVar6 == 0) {
    AddTime__9BI_PolGrpFf(0x3d08882f,*(u32 *)(param_1 + 0x170));
  }
  CalcMatrix__9BI_PolGrpFv(*(u32 *)(param_1 + 0x170));
  iVar5 = *(int *)(param_1 + 0x1d4);
  if (iVar5 != 9999) {
    if (iVar5 == 4) {
      iVar5 = *(int *)(param_1 + 0x1d8) + 1;
      *(int *)(param_1 + 0x1d8) = iVar5;
      if (iVar5 < 0x41) {
        for (iVar5 = *(int *)(param_1 + 0x170); iVar5 != 0; iVar5 = GetNext__5CListCFv(iVar5)) {
          *(float *)(iVar5 + 0xd0) = *(float *)(iVar5 + 0xd0) + 0.0003;
          for (iStack_1c = *(int *)(iVar5 + 0xc); iStack_1c != 0;
              iStack_1c = GetNext__5CListCFv(iStack_1c)) {
            pfVar2 = (float *)vw__7FVectorFv(iStack_1c + 0x80);
            *pfVar2 = *pfVar2 - 6.4;
          }
        }
      }
      else {
        SetFase__7tagFaseFi(param_1 + 0x1d4,9999);
      }
    }
    else if (iVar5 == 3) {
      iVar5 = *(int *)(param_1 + 0x1d8) + 1;
      *(int *)(param_1 + 0x1d8) = iVar5;
      if (iVar5 < 0x41) {
        for (iVar5 = *(int *)(param_1 + 0x170); iVar5 != 0; iVar5 = GetNext__5CListCFv(iVar5)) {
          *(float *)(iVar5 + 0xd0) = *(float *)(iVar5 + 0xd0) + 0.0003;
          for (iStack_18 = *(int *)(iVar5 + 0xc); iStack_18 != 0;
              iStack_18 = GetNext__5CListCFv(iStack_18)) {
            pfVar2 = (float *)vw__7FVectorFv(iStack_18 + 0x80);
            *pfVar2 = *pfVar2 - 2.0;
          }
        }
      }
      else {
        SetFase__7tagFaseFi(param_1 + 0x1d4,9999);
      }
    }
    else if (iVar5 == 2) {
      *(int *)(param_1 + 0x1d8) = *(int *)(param_1 + 0x1d8) + 1;
      if (*(int *)(param_1 + 0x1dc) == 1) {
        iVar5 = *(int *)(param_1 + 0x1d8);
        SetFase__7tagFaseFi(param_1 + 0x1d4,3);
        if (0x50 < iVar5) {
          *(u32 *)(param_1 + 0x1d4) = 4;
          *(u32 *)(param_1 + 0x1d8) = 0x2c;
        }
      }
      else {
        for (iVar5 = *(int *)(param_1 + 0x170); iVar5 != 0; iVar5 = GetNext__5CListCFv(iVar5)) {
          *(float *)(iVar5 + 0xd0) = *(float *)(iVar5 + 0xd0) + 0.0003;
        }
      }
    }
    else if (iVar5 == 1) {
      SetFase__7tagFaseFi(param_1 + 0x1d4,2);
      for (iVar5 = *(int *)(param_1 + 0x170); iVar5 != 0; iVar5 = GetNext__5CListCFv(iVar5)) {
        pfVar2 = (float *)vx__7FVectorFv(iVar5 + 0xb0);
        if (*pfVar2 <= *(float *)(param_1 + 0x1d0)) {
          iVar3 = rand();
          *(float *)(iVar5 + 200) = -((float)iVar3 / 4.2949673e+09);
        }
        else {
          iVar3 = rand();
          *(float *)(iVar5 + 200) = (float)iVar3 / 4.2949673e+09;
        }
        iVar3 = rand();
        *(float *)(iVar5 + 0xcc) = (float)(iVar3 + -0x3fffffff) / 1.0737418e+09;
        *(float *)(iVar5 + 200) = *(float *)(iVar5 + 200) * 0.5;
        *(float *)(iVar5 + 0xcc) = *(float *)(iVar5 + 0xcc) * 0.5;
        iVar3 = rand();
        uVar7 = GetRad((float)(iVar3 % 7));
        puVar4 = (u32 *)vx__7FVectorFv(iVar5 + 0xa0);
        *puVar4 = uVar7;
        iVar3 = rand();
        uVar7 = GetRad((float)(iVar3 % 7));
        puVar4 = (u32 *)vy__7FVectorFv(iVar5 + 0xa0);
        *puVar4 = uVar7;
      }
    }
    else if (iVar5 == 10) {
      iVar5 = *(int *)(param_1 + 0x1d8) + 1;
      *(int *)(param_1 + 0x1d8) = iVar5;
      if (iVar5 < 9) {
        for (iVar5 = *(int *)(param_1 + 0x170); iVar5 != 0; iVar5 = GetNext__5CListCFv(iVar5)) {
          for (iVar3 = *(int *)(iVar5 + 0xc); iVar3 != 0; iVar3 = GetNext__5CListCFv(iVar3)) {
            pfVar2 = (float *)vx__7FVectorFv(iVar3 + 0x80);
            *pfVar2 = *pfVar2 - 16.0;
            pfVar2 = (float *)vy__7FVectorFv(iVar3 + 0x80);
            *pfVar2 = *pfVar2 - 16.0;
            pfVar2 = (float *)vz__7FVectorFv(iVar3 + 0x80);
            *pfVar2 = *pfVar2 - 16.0;
          }
        }
      }
      else {
        SetFase__7tagFaseFi(param_1 + 0x1d4,1);
      }
    }
    else if (iVar5 == 0) {
      iVar5 = *(int *)(param_1 + 0x1d8) + 1;
      *(int *)(param_1 + 0x1d8) = iVar5;
      if (iVar5 < 9) {
        for (iVar5 = *(int *)(param_1 + 0x170); iVar5 != 0; iVar5 = GetNext__5CListCFv(iVar5)) {
          for (iVar3 = *(int *)(iVar5 + 0xc); iVar3 != 0; iVar3 = GetNext__5CListCFv(iVar3)) {
            pfVar2 = (float *)vx__7FVectorFv(iVar3 + 0x80);
            *pfVar2 = *pfVar2 + 16.0;
            pfVar2 = (float *)vy__7FVectorFv(iVar3 + 0x80);
            *pfVar2 = *pfVar2 + 16.0;
            pfVar2 = (float *)vz__7FVectorFv(iVar3 + 0x80);
            *pfVar2 = *pfVar2 + 16.0;
            pfVar2 = (float *)vw__7FVectorFv(iVar3 + 0x80);
            *pfVar2 = *pfVar2 + 8.0;
          }
        }
      }
      else {
        SetFase__7tagFaseFi(param_1 + 0x1d4,10);
      }
    }
  }
  if (*(int *)(param_1 + 0x1dc) == 2) {
    if (*(int *)(param_1 + 0x1d4) == 9999) {
      ReleaseOT__5WorldFP8VIF1Prim((World *)&m_World__4CApp,(VIF1Prim *)(param_1 + -0x20));
      iVar5 = 0;
      if ((VIF1Prim *)(param_1 + -0x20) != (VIF1Prim *)0x0) {
        iVar5 = param_1;
      }
      Dispose__7CPollerFP7CPolObj(app__4CApp + 0x48,iVar5);
      (**(code **)(*(int *)(param_1 + -4) + 0xc))();
      SetFase__7tagFaseFi(param_1 + 0x1d4,10000);
    }
  }
  else if (*(int *)(param_1 + 0x1dc) == 1) {
    iVar5 = *(int *)(param_1 + 0x1e0) + 1;
    *(int *)(param_1 + 0x1e0) = iVar5;
    if (iVar5 < 9) {
      *(short *)(param_1 + 0x174) = *(short *)(param_1 + 0x174) + -0x10;
      if (*(short *)(param_1 + 0x174) < 0) {
        uVar1 = 0;
      }
      else {
        uVar1 = *(u16 *)(param_1 + 0x174);
      }
      *(u16 *)(param_1 + 0x174) = uVar1;
    }
    else {
      SetFase__7tagFaseFi(param_1 + 0x1dc,2);
    }
  }
  return 0;
}

/* ---- 0x003b25a0 size 0x8  BtlIn::@32@__dt(v)
 *      mangled: @32@__dt__5BtlInFv */
int * _32___dt__5BtlInFv(int param_1,short param_2)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)(param_1 + -0x20);
  if (piVar1 != (int *)0x0) {
    *(u8 **)(param_1 + -0x10) = __vt__5BtlIn;
    *(u32 *)(param_1 + -4) = 0x407590;
    *(u32 *)(param_1 + 0x14) = 0x4075a0;
    ourBtlIn__5BtlIn = 0;
    if (*piVar1 != 0) {
      __dla__FPv(*piVar1);
      *piVar1 = 0;
    }
    if (*(int *)(param_1 + -0x1c) != 0) {
      __dla__FPv(*(u32 *)(param_1 + -0x1c));
      *(u32 *)(param_1 + -0x1c) = 0;
    }
    if (*(int *)(param_1 + 0x170) != 0) {
      iVar2 = *(int *)(param_1 + 0x170);
      if (iVar2 != 0) {
        (**(code **)(*(int *)(iVar2 + 0xd4) + 8))(iVar2,1);
      }
      *(u32 *)(param_1 + 0x170) = 0;
    }
    iVar2 = 0;
    if (piVar1 != (int *)0x0) {
      iVar2 = param_1;
    }
    Dispose__7CPollerFP7CPolObj(app__4CApp + 0x48,iVar2);
    __dt__12FrameTextureFv(param_1 + 0x1f0,0xffffffffffffffff);
    __dt__7CPolObjFv(param_1,0);
    __dt__17DelayDeleteObjectFv(param_1 + -0xc,0);
    __dt__8VIF1PrimFv(piVar1,0);
    if (0 < param_2) {
      __dl__FPv(piVar1);
    }
  }
  return piVar1;
}

