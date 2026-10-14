/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: CFieldBG   functions: 24
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/CFieldBG.md).
 */

/* JP: 0x004a3900  CFieldBG::~CFieldBG()   [__dt__8CFieldBGFv]  size=0x5c */
int __dt__8CFieldBGFv(CFieldBG *this,short flag)

{
  if ((this != (CFieldBG *)0x0) && (Release__8CFieldBGFv(this), 0 < flag)) {
    __dl__FPv(this);
  }
  return (int)this;
}

/* JP: 0x004da620  CFieldBG::CFieldBG()   [__ct__8CFieldBGFv]  size=0x28 */
undefined4 * __ct__8CFieldBGFv(CFieldBG *this)

{
  this->pImpl = (void *)0x0;
  this->pSdb = (void *)0x0;
  return &this->pImpl;
}

/* JP: 0x004da650  CFieldBG::Create(BufMemory*, int)   [Create__8CFieldBGFP9BufMemoryi]  size=0xf4 */
long Create__8CFieldBGFP9BufMemoryi(CFieldBG *this,void *a0,int a1)

{
  void *pvVar1;
  int iVar2;
  long lVar3;
  
  if (this->pImpl == (void *)0x0) {
    pvVar1 = (void *)__nw__FUi(0x1d4);
    this->pImpl = pvVar1;
  }
  memset(this->pImpl,0,0x1d4);
  *(undefined4 *)((int)this->pImpl + 0x1b0) = 0xffffffff;
  lVar3 = __nw__FUi(0x24);
  pvVar1 = (void *)0x0;
  if (lVar3 != 0) {
    pvVar1 = (void *)__ct__6CSTGDBFv(lVar3);
  }
  this->pSdb = pvVar1;
  lVar3 = LoadCB__6CSTGDBFP9BufMemoryi(this->pSdb,a0,0);
  if (lVar3 == 0) {
    lVar3 = 0;
  }
  else {
    iVar2 = Create__8CFieldBGFP6CSTGDBi(this,this->pSdb,a1);
    lVar3 = (long)iVar2;
  }
  return lVar3;
}

/* JP: 0x004da750  CFieldBG::Create(CSTGDB*, int)   [Create__8CFieldBGFP6CSTGDBi]  size=0x6a4 */
undefined4 Create__8CFieldBGFP6CSTGDBi(CFieldBG *this,CSTGDB *a0,int a1)

{
  char cVar1;
  short sVar2;
  void *pvVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  long lVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  int iVar11;
  int iVar12;
  undefined1 auStack_70 [16];
  undefined1 auStack_60 [16];
  undefined8 uStack_50;
  int iStack_44;
  int iStack_40;
  int iStack_3c;
  int iStack_38;
  int iStack_34;
  CFieldBG *pCStack_30;
  CSTGDB *pCStack_20;
  int iStack_10;
  
  uStack_50 = 0;
  pCStack_30 = this;
  pCStack_20 = a0;
  iStack_10 = a1;
  LayerMan_Init__Fv();
  if (pCStack_30->pImpl == (void *)0x0) {
    pvVar3 = (void *)__nw__FUi(0x1d4);
    pCStack_30->pImpl = pvVar3;
  }
  memset(pCStack_30->pImpl,0,0x1d4);
  *(undefined4 *)((int)pCStack_30->pImpl + 0x1b0) = 0xffffffff;
  pCStack_30->pSdb = pCStack_20;
  *(short *)((int)pCStack_30->pImpl + 0x1c6) = (short)iStack_10;
  lVar7 = Find__6CSTGDBFUl(pCStack_20,0x202020444c454946);
  if (lVar7 != 0) {
    iVar4 = (int)lVar7;
    uStack_50 = *(undefined8 *)(iVar4 + 8);
    *(byte *)((int)pCStack_30->pImpl + 0x1c4) =
         *(byte *)((int)pCStack_30->pImpl + 0x1c4) & 0xfd |
         (byte)((*(ushort *)(iVar4 + 0x12) & 1) << 1);
    *(char *)((int)pCStack_30->pImpl + 0x1ce) = (char)*(undefined2 *)(iVar4 + 0x10);
    if (*(char *)(iVar4 + 0x14) != '\0') {
      LayerMan_LoadLayer__FPCUc(0x558ff0);
    }
    uVar8 = LayerMan_GetLayer__Fi(7);
    changeLayer__16ExpansionTextureFi(uVar8);
  }
  lVar7 = Find__6CSTGDBFUl(pCStack_20,0x2020204c45444f4d);
  if (lVar7 != 0) {
    iVar4 = GetDataAddr__6CSTGDBFPQ23SDB9tagHEADER(pCStack_20,lVar7);
    iStack_38 = GetDataNum__6CSTGDBFPQ23SDB9tagHEADER(pCStack_20,lVar7);
    if (iStack_38 == 0) {
      return 0;
    }
    uVar8 = __nwa__FUi(iStack_38 << 2);
    for (iStack_34 = 0; iStack_34 < iStack_38; iStack_34 = iStack_34 + 1) {
      *(int *)((int)uVar8 + iStack_34 * 4) = (int)*(short *)((int)pCStack_30->pImpl + 0x1c8);
      iVar11 = iVar4 + *(int *)(iVar4 + 0x14);
      cVar1 = *(char *)(iVar4 + 0x10);
      if (cVar1 == '\x03') {
        iStack_40 = *(int *)((int)uVar8 + *(int *)(iVar4 + 0x1c) * 4);
        iStack_44 = GetModel__11CFieldModelFv
                              (*(undefined4 *)((int)pCStack_30->pImpl + iStack_40 * 4 + 0x140));
        if ((iStack_44 != 0) && (lVar7 = createMotion__5ModelFPUc(iStack_44,iVar11), lVar7 != 0)) {
          *(short *)((int)pCStack_30->pImpl + *(short *)((int)pCStack_30->pImpl + 0x1ca) * 8) =
               (short)iStack_40;
          uVar5 = GetAnmName__11CFieldModelFPUc
                            (*(undefined4 *)((int)pCStack_30->pImpl + iStack_40 * 4 + 0x140),iVar11)
          ;
          *(undefined4 *)
           ((int)pCStack_30->pImpl + *(short *)((int)pCStack_30->pImpl + 0x1ca) * 8 + 4) = uVar5;
          *(short *)((int)pCStack_30->pImpl + 0x1ca) =
               *(short *)((int)pCStack_30->pImpl + 0x1ca) + 1;
        }
      }
      else if (((cVar1 == '\x02') || (cVar1 == '\x01')) || (cVar1 == '\0')) {
        lVar7 = __nw__FUi(0x2e0);
        uVar9 = 0;
        if (lVar7 != 0) {
          uVar9 = __ct__11CFieldModelFv(lVar7);
        }
        sVar2 = *(short *)((int)pCStack_30->pImpl + 0x1c8);
        *(short *)((int)pCStack_30->pImpl + 0x1c8) = sVar2 + 1;
        iVar12 = (int)uVar9;
        *(int *)((int)pCStack_30->pImpl + sVar2 * 4 + 0x140) = iVar12;
        SetExModel__11CFieldModelFi(uVar9,((ulong)*(byte *)(iVar4 + 0x11) & 7) >> 2);
        iStack_3c = 0;
        if (*(char *)(iVar4 + 0x10) == '\x01') {
          iStack_3c = 2;
        }
        else if (*(char *)(iVar4 + 0x10) == '\0') {
          iStack_3c = 1;
        }
        SetModel__11CFieldModelFPUci(uVar9,iVar11,iStack_3c + 0x80);
        uVar10 = __ct__7FVectorFPC7FVector(auStack_60,iVar4 + 0x20);
        SetPos__11CFieldModelF7FVectorb(uVar9,uVar10,0);
        uVar10 = __ct__7FVectorFPC7FVector(auStack_70,iVar4 + 0x30);
        SetRot__11CFieldModelF7FVector(uVar9,uVar10);
        *(byte *)(iVar12 + 0x80) = *(byte *)(iVar12 + 0x80) & 0xfc | 3;
      }
      iVar4 = iVar4 + 0x40;
    }
    __dla__FPv(uVar8);
  }
  if (*(short *)((int)pCStack_30->pImpl + 0x1c8) != 0) {
    GetShadowCtrl__8CFieldBGFb(pCStack_30,true);
  }
  lVar7 = __nw__FUi(0x288);
  uVar5 = 0;
  if (lVar7 != 0) {
    uVar5 = __ct__10CBgElementFv(lVar7);
  }
  *(undefined4 *)((int)pCStack_30->pImpl + 0x168) = uVar5;
  Create__10CBgElementFPUcb(*(undefined4 *)((int)pCStack_30->pImpl + 0x168),
                  *(undefined4 *)((int)pCStack_30->pSdb + 0x18),
                  (*(ushort *)((int)pCStack_30->pImpl + 0x1c6) & 0xf) != 0);
  Clr__10CBgElementFv(*(undefined4 *)((int)pCStack_30->pImpl + 0x168));
  *(undefined4 *)((int)pCStack_30->pImpl + 0x1b8) = 0x41200000;
  *(undefined4 *)((int)pCStack_30->pImpl + 0x1bc) = 0x4b7fe3d0;
  lVar7 = Find__6CSTGDBFUl(pCStack_20,0x2020202020474f46);
  if (lVar7 != 0) {
    puVar6 = (undefined4 *)GetDataAddr__6CSTGDBFPQ23SDB9tagHEADER(pCStack_20,lVar7);
    *(undefined4 *)((int)pCStack_30->pImpl + 0x1b8) = *puVar6;
    *(undefined4 *)((int)pCStack_30->pImpl + 0x1bc) = puVar6[1];
    *(undefined4 *)((int)pCStack_30->pImpl + 0x1c0) = puVar6[2];
  }
  lVar7 = Find__6CSTGDBFUl(pCStack_20,0x2020524f5252494d);
  if (lVar7 != 0) {
    *(int *)((int)pCStack_30->pImpl + 0x16c) = (int)lVar7 + 0x20;
    *(short *)((int)pCStack_30->pImpl + 0x1cc) = (short)*(undefined4 *)((int)lVar7 + 8);
  }
  return 1;
}

/* JP: 0x004dae80  CFieldBG::GetMirrorInfo(int&)   [GetMirrorInfo__8CFieldBGFRi]  size=0x40 */
undefined4 GetMirrorInfo__8CFieldBGFRi(CFieldBG *this,int *a0)

{
  *a0 = (int)*(short *)((int)this->pImpl + 0x1cc);
  return *(undefined4 *)((int)this->pImpl + 0x16c);
}

/* JP: 0x004dafb0  CFieldBG::CheckMirror(GsxCamera*, FVector&)   [CheckMirror__8CFieldBGFP9GsxCameraR7FVector]  size=0xac4 */
long CheckMirror__8CFieldBGFP9GsxCameraR7FVector(CFieldBG *this,void *a0,FVector *a1)

{
  int iVar1;
  undefined8 uVar2;
  ulong uVar3;
  int iVar4;
  long lVar5;
  long lVar6;
  float fVar7;
  float fVar8;
  undefined4 uVar9;
  undefined1 auStack_1c0 [16];
  undefined1 auStack_1b0 [16];
  undefined1 auStack_1a0 [16];
  undefined1 auStack_190 [16];
  undefined1 auStack_180 [16];
  undefined1 auStack_170 [16];
  undefined1 auStack_160 [16];
  undefined1 auStack_150 [16];
  undefined1 auStack_140 [16];
  undefined1 auStack_130 [16];
  undefined1 auStack_120 [16];
  undefined1 auStack_110 [16];
  undefined1 auStack_100 [16];
  undefined1 auStack_f0 [4];
  undefined4 uStack_ec;
  undefined4 uStack_e8;
  undefined1 auStack_e0 [4];
  undefined4 uStack_dc;
  undefined4 uStack_d8;
  float fStack_d0;
  float fStack_cc;
  float fStack_c8;
  undefined4 uStack_c4;
  float fStack_c0;
  float fStack_bc;
  float fStack_b8;
  undefined4 uStack_b4;
  undefined1 auStack_b0 [12];
  undefined4 uStack_a4;
  undefined1 auStack_a0 [16];
  undefined1 auStack_90 [16];
  undefined1 auStack_80 [16];
  undefined1 auStack_70 [24];
  float fStack_58;
  float fStack_54;
  float fStack_50;
  float fStack_4c;
  float fStack_48;
  float fStack_44;
  float fStack_40;
  float fStack_3c;
  float fStack_38;
  float fStack_34;
  CFieldBG *pCStack_30;
  void *pvStack_20;
  FVector *pFStack_10;
  
  pCStack_30 = this;
  pvStack_20 = a0;
  pFStack_10 = a1;
  __ct__7FVectorFv(auStack_70);
  __ct__7FVectorFv(auStack_80);
  __ct__7FVectorFv(auStack_90);
  __ct__7FVectorFv(auStack_a0);
  __ct__7FVectorFv(auStack_b0);
  __ct__7FVectorFv(&fStack_c0);
  __ct__7FVectorFv(&fStack_d0);
  __ct__7FVectorFv(auStack_e0);
  __ct__7FVectorFv(auStack_f0);
  lVar6 = (long)*(short *)((int)pCStack_30->pImpl + 0x1cc);
  iVar1 = *(int *)((int)pCStack_30->pImpl + 0x16c);
  if (lVar6 != 0) {
    uVar2 = GetFrame__9GsxCameraFv(pvStack_20);
    uVar2 = GetPos__6MatrixFv(uVar2);
    __as__7FVectorFRC7FVector(auStack_70,uVar2);
    uVar2 = GetFrame__9GsxCameraFv(pvStack_20);
    uVar2 = GetAt__6MatrixFv(uVar2);
    __as__7FVectorFRC7FVector(auStack_80,uVar2);
    for (lVar5 = 0; lVar5 < lVar6; lVar5 = (long)((int)lVar5 + 1)) {
      memcpy(auStack_b0,iVar1,0xc);
      memcpy(&fStack_c0,iVar1 + 0x10,0xc);
      memcpy(&fStack_d0,iVar1 + 0x20,0xc);
      uStack_c4 = 0x3f800000;
      uStack_b4 = 0x3f800000;
      uStack_a4 = 0x3f800000;
      __ami__7FVectorFRC7FVector(&fStack_c0,auStack_b0);
      __ami__7FVectorFRC7FVector(&fStack_d0,auStack_b0);
      Normalize__7FVectorFv(&fStack_c0);
      Normalize__7FVectorFv(&fStack_d0);
      OuterProduct__7FVectorCFRC7FVector(auStack_100,&fStack_d0,&fStack_c0);
      __as__7FVectorFRC7FVector(auStack_90,auStack_100);
      Normalize__7FVectorFv(auStack_90);
      uVar3 = CheckMirrorNormal__FR7FVector(auStack_90);
      __mi__7FVectorCFRC7FVector(auStack_110,auStack_70,auStack_b0);
      __as__7FVectorFRC7FVector(auStack_a0,auStack_110);
      Normalize__7FVectorFv(auStack_a0);
      fVar7 = (float)InnerProduct__7FVectorCFRC7FVector(auStack_90,auStack_a0);
      if (0.0 <= fVar7) {
        __ml__7FVectorCFf(0xbf800000,auStack_120,auStack_90);
        __as__7FVectorFRC7FVector(auStack_a0,auStack_120);
        fVar7 = (float)InnerProduct__7FVectorCFRC7FVector(auStack_80,auStack_a0);
        if (-0.8 <= fVar7) {
          fStack_58 = 99999.0;
          fStack_50 = 99999.0;
          fStack_54 = -99999.0;
          fStack_4c = -99999.0;
          if ((uVar3 & 1) == 0) {
            for (iVar4 = 0; iVar4 < 3; iVar4 = iVar4 + 1) {
              fVar8 = *(float *)(iVar1 + iVar4 * 0x10);
              fVar7 = fVar8;
              if (fStack_50 <= fVar8) {
                fVar7 = fStack_50;
              }
              fStack_50 = fVar7;
              if (fVar8 <= fStack_4c) {
                fVar8 = fStack_4c;
              }
              fStack_4c = fVar8;
              fStack_34 = *(float *)(iVar1 + iVar4 * 0x10 + 8);
              fVar7 = fStack_34;
              if (fStack_58 <= fStack_34) {
                fVar7 = fStack_58;
              }
              fStack_58 = fVar7;
              fVar7 = fStack_34;
              if (fStack_34 <= fStack_54) {
                fVar7 = fStack_54;
              }
              fStack_54 = fVar7;
            }
            fStack_c0 = fStack_50;
            fStack_b8 = fStack_58;
            fStack_d0 = fStack_4c;
            fStack_c8 = fStack_54;
            if (uVar3 == 0) {
              fStack_b8 = fStack_58 - 10.0;
              fStack_c8 = fStack_54 + 10.0;
            }
            else {
              fStack_c0 = fStack_50 - 10.0;
              fStack_d0 = fStack_4c + 10.0;
            }
            __mi__7FVectorCFRC7FVector(auStack_130,pFStack_10,&fStack_c0);
            __as__7FVectorFRC7FVector(auStack_e0,auStack_130);
            __mi__7FVectorCFRC7FVector(auStack_140,pFStack_10,&fStack_d0);
            __as__7FVectorFRC7FVector(auStack_f0,auStack_140);
            __mi__7FVectorCFRC7FVector(auStack_150,auStack_70,&fStack_c0);
            __as__7FVectorFRC7FVector(&fStack_c0,auStack_150);
            __mi__7FVectorCFRC7FVector(auStack_160,auStack_70,&fStack_d0);
            __as__7FVectorFRC7FVector(&fStack_d0,auStack_160);
            if (uVar3 == 0) {
              fStack_b8 = fStack_b8 * -1.0;
              fStack_c8 = fStack_c8 * -1.0;
            }
            else {
              fStack_c0 = fStack_c0 * -1.0;
              fStack_d0 = fStack_d0 * -1.0;
            }
            fStack_cc = 0.0;
            fStack_bc = 0.0;
            __mi__7FVectorCFRC7FVector(auStack_170,&fStack_d0,&fStack_c0);
            __as__7FVectorFRC7FVector(auStack_b0,auStack_170);
            Normalize__7FVectorFv(&fStack_c0);
            Normalize__7FVectorFv(&fStack_d0);
            uStack_ec = 0;
            uStack_dc = 0;
            Normalize__7FVectorFv(auStack_b0);
            Normalize__7FVectorFv(auStack_e0);
            Normalize__7FVectorFv(auStack_f0);
            uVar9 = InnerProduct__7FVectorCFRC7FVector(auStack_b0,&fStack_c0);
            fStack_38 = (float)acosf(uVar9);
            uVar9 = InnerProduct__7FVectorCFRC7FVector(auStack_b0,auStack_e0);
            fStack_3c = (float)acosf(uVar9);
            if (fStack_3c <= fStack_38) {
              __amu__7FVectorFf(0xbf800000,auStack_b0);
              uVar9 = InnerProduct__7FVectorCFRC7FVector(auStack_b0,&fStack_d0);
              fStack_38 = (float)acosf(uVar9);
              uVar9 = InnerProduct__7FVectorCFRC7FVector(auStack_b0,auStack_f0);
              fStack_3c = (float)acosf(uVar9);
              if (fStack_3c <= fStack_38) {
                if (uVar3 == 0) {
                  pFStack_10->flX = (fStack_50 + fStack_4c) * -1.0;
                  pFStack_10->flZ = 0.0;
                  pFStack_10->flY = 0.0;
                }
                else {
                  pFStack_10->flZ = (fStack_58 + fStack_54) * -1.0;
                  pFStack_10->flY = 0.0;
                  pFStack_10->flX = 0.0;
                }
                pFStack_10->flW = 1.0;
                return uVar3;
              }
            }
          }
          else {
            for (iVar4 = 0; iVar4 < 3; iVar4 = iVar4 + 1) {
              fVar8 = *(float *)(iVar1 + iVar4 * 0x10);
              fVar7 = fVar8;
              if (fStack_50 <= fVar8) {
                fVar7 = fStack_50;
              }
              fStack_50 = fVar7;
              if (fVar8 <= fStack_4c) {
                fVar8 = fStack_4c;
              }
              fStack_4c = fVar8;
              fStack_40 = *(float *)(iVar1 + iVar4 * 0x10 + 4);
              fVar7 = fStack_40;
              if (fStack_58 <= fStack_40) {
                fVar7 = fStack_58;
              }
              fStack_58 = fVar7;
              fVar7 = fStack_40;
              if (fStack_40 <= fStack_54) {
                fVar7 = fStack_54;
              }
              fStack_54 = fVar7;
            }
            fStack_bc = fStack_58;
            fStack_cc = fStack_54;
            fStack_c0 = fStack_50 - 10.0;
            fStack_d0 = fStack_4c + 10.0;
            __mi__7FVectorCFRC7FVector(auStack_180,pFStack_10,&fStack_c0);
            __as__7FVectorFRC7FVector(auStack_e0,auStack_180);
            __mi__7FVectorCFRC7FVector(auStack_190,pFStack_10,&fStack_d0);
            __as__7FVectorFRC7FVector(auStack_f0,auStack_190);
            __mi__7FVectorCFRC7FVector(auStack_1a0,auStack_70,&fStack_c0);
            __as__7FVectorFRC7FVector(&fStack_c0,auStack_1a0);
            __mi__7FVectorCFRC7FVector(auStack_1b0,auStack_70,&fStack_d0);
            __as__7FVectorFRC7FVector(&fStack_d0,auStack_1b0);
            fStack_c0 = fStack_c0 * -1.0;
            fStack_d0 = fStack_d0 * -1.0;
            fStack_c8 = 0.0;
            fStack_b8 = 0.0;
            __mi__7FVectorCFRC7FVector(auStack_1c0,&fStack_d0,&fStack_c0);
            __as__7FVectorFRC7FVector(auStack_b0,auStack_1c0);
            Normalize__7FVectorFv(&fStack_c0);
            Normalize__7FVectorFv(&fStack_d0);
            uStack_e8 = 0;
            uStack_d8 = 0;
            Normalize__7FVectorFv(auStack_b0);
            Normalize__7FVectorFv(auStack_e0);
            Normalize__7FVectorFv(auStack_f0);
            uVar9 = InnerProduct__7FVectorCFRC7FVector(auStack_b0,&fStack_c0);
            fStack_44 = (float)acosf(uVar9);
            uVar9 = InnerProduct__7FVectorCFRC7FVector(auStack_b0,auStack_e0);
            fStack_48 = (float)acosf(uVar9);
            if (fStack_48 <= fStack_44) {
              __amu__7FVectorFf(0xbf800000,auStack_b0);
              uVar9 = InnerProduct__7FVectorCFRC7FVector(auStack_b0,&fStack_d0);
              fStack_44 = (float)acosf(uVar9);
              uVar9 = InnerProduct__7FVectorCFRC7FVector(auStack_b0,auStack_f0);
              fStack_48 = (float)acosf(uVar9);
              if (fStack_48 <= fStack_44) {
                pFStack_10->flY = (fStack_58 + fStack_54) * -1.0;
                pFStack_10->flZ = 0.0;
                pFStack_10->flX = 0.0;
                pFStack_10->flW = 1.0;
                return uVar3;
              }
            }
          }
        }
      }
      iVar1 = iVar1 + 0x30;
    }
  }
  return -1;
}

/* JP: 0x004dba80  CFieldBG::Release()   [Release__8CFieldBGFv]  size=0x134 */
void Release__8CFieldBGFv(CFieldBG *this)

{
  int iVar1;
  long lVar2;
  
  if (this->pImpl != (void *)0x0) {
    Clr__8CFieldBGFv(this);
    lVar2 = 0;
    while (lVar2 < *(short *)((int)this->pImpl + 0x1c8)) {
      iVar1 = (int)lVar2;
      if (*(int *)((int)this->pImpl + iVar1 * 4 + 0x140) != 0) {
        Delete__11CFieldModelFv(*(undefined4 *)((int)this->pImpl + iVar1 * 4 + 0x140));
      }
      lVar2 = (long)(iVar1 + 1);
    }
    *(undefined2 *)((int)this->pImpl + 0x1c8) = 0;
    *(undefined2 *)((int)this->pImpl + 0x1ca) = 0;
    (**(code **)(*(int *)((int)this->pSdb + 8) + 0xc))();
    ReleaseShadow__8CFieldBGFv(this);
    Clear__10CBgElementFv(*(undefined4 *)((int)this->pImpl + 0x168));
    __dt__10CBgElementFv(*(undefined4 *)((int)this->pImpl + 0x168),1);
    __dl__FPv(this->pImpl);
    this->pImpl = (void *)0x0;
    this->pSdb = (void *)0x0;
  }
  return;
}

/* JP: 0x004dbbc0  CFieldBG::Dsp()   [Dsp__8CFieldBGFv]  size=0x408 */
void Dsp__8CFieldBGFv(CFieldBG *this)

{
  short sVar1;
  int iVar2;
  undefined4 *puVar3;
  int iVar4;
  long lVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined4 uVar8;
  undefined1 auStack_1c [4];
  undefined1 auStack_18 [4];
  undefined1 auStack_14 [4];
  CFieldBG *pCStack_10;
  
  if ((this->pImpl != (void *)0x0) && ((*(byte *)((int)this->pImpl + 0x1c4) & 1) == 0)) {
    *(byte *)((int)this->pImpl + 0x1c4) = *(byte *)((int)this->pImpl + 0x1c4) & 0xfe | 1;
    pCGpffff8604 = this;
    pCStack_10 = this;
    __ct__7_rgba32FUi(auStack_14,0);
    lVar5 = Find__6CSTGDBFUl(pCStack_10->pSdb,0x20524f4c4f434742);
    if (lVar5 != 0) {
      puVar3 = (undefined4 *)GetDataAddr__6CSTGDBFPQ23SDB9tagHEADER(pCStack_10->pSdb,lVar5);
      uVar6 = __ct__7_rgba32FUi(auStack_18,*puVar3);
      __as__7_rgba32FRC7_rgba32(auStack_14,uVar6);
    }
    uVar6 = GetActiveCamera__9GsxCameraFv();
    SetBgColor__9GsxCameraFRC7_rgba32(uVar6,auStack_14);
    m_bgDspCount__8CFieldBG = m_bgDspCount__8CFieldBG + 1;
    SetFogParam__9GsxCameraFff
              (*(undefined4 *)((int)pCStack_10->pImpl + 0x1b8),
               *(undefined4 *)((int)pCStack_10->pImpl + 0x1bc),uVar6);
    uVar7 = __ct__7_rgba32FUi(auStack_1c,*(undefined4 *)((int)pCStack_10->pImpl + 0x1c0));
    SetFogColor__9GsxCameraFRC7_rgba32(uVar6,uVar7);
    iVar4 = GetShadowCtrl__8CFieldBGFb(pCStack_10,true);
    for (lVar5 = 0; lVar5 < *(short *)((int)pCStack_10->pImpl + 0x1c8);
        lVar5 = (long)((int)lVar5 + 1)) {
      iVar2 = *(int *)((int)pCStack_10->pImpl + (int)lVar5 * 4 + 0x140);
      sVar1 = *(short *)(iVar2 + 0x98);
      if (sVar1 == 2) {
        uVar6 = LayerMan_GetLayer__Fi(0);
        uVar7 = LayerMan_GetLayer__Fi(1);
        DispModel__11CFieldModelFiii(iVar2,uVar6,uVar7,0);
      }
      else if (sVar1 == 0) {
        uVar6 = LayerMan_GetLayer__Fi(8);
        uVar7 = LayerMan_GetLayer__Fi(9);
        DispModel__11CFieldModelFiii(iVar2,uVar6,uVar7,0);
      }
      else if (sVar1 == 1) {
        uVar6 = GetModel__11CFieldModelFv(iVar2);
        setReciveShadow__13ShadowControlFP5Model(iVar4,uVar6);
        if ((long)((ulong)*(byte *)((int)pCStack_10->pImpl + 0x1c4) << 0x3e) < 0) {
          uVar8 = 6;
        }
        else {
          uVar8 = 5;
        }
        uVar6 = LayerMan_GetLayer__Fi(2);
        uVar7 = LayerMan_GetLayer__Fi(uVar8);
        DispModel__11CFieldModelFiii(iVar2,uVar6,uVar7,0);
      }
    }
    if ((iVar4 != 0) && (lVar5 = FindOT__5WorldFP8VIF1Prim(0x42bf10,iVar4), lVar5 == 0)) {
      if ((long)((ulong)*(byte *)((int)pCStack_10->pImpl + 0x1c4) << 0x3e) < 0) {
        uVar8 = 5;
      }
      else {
        uVar8 = 6;
      }
      uVar6 = LayerMan_GetLayer__Fi(uVar8);
      AddOT__5WorldFiP8VIF1Prim(0x42bf10,uVar6,iVar4);
    }
    Dsp__10CBgElementFv(*(undefined4 *)((int)pCStack_10->pImpl + 0x168));
    if ((long)((ulong)*(byte *)((int)pCStack_10->pImpl + 0x1c4) << 0x3d) < 0) {
      RecreateExLight__8CFieldBGFv(pCStack_10);
    }
  }
  return;
}

/* JP: 0x004dc170  CFieldBG::Clr()   [Clr__8CFieldBGFv]  size=0x1f8 */
void Clr__8CFieldBGFv(CFieldBG *this)

{
  int iVar1;
  int iVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  long lVar5;
  undefined1 auStack_14 [4];
  CFieldBG *pCStack_10;
  
  if ((this->pImpl != (void *)0x0) && ((*(byte *)((int)this->pImpl + 0x1c4) & 1) != 0)) {
    pCStack_10 = this;
    iVar2 = GetShadowCtrl__8CFieldBGFb(this,false);
    m_bgDspCount__8CFieldBG = m_bgDspCount__8CFieldBG + -1;
    if (m_bgDspCount__8CFieldBG < 1) {
      if ((iVar2 != 0) && (m_ourShadowControl__8CFieldBG != 0)) {
        ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,iVar2);
      }
      uVar3 = GetActiveCamera__9GsxCameraFv();
      uVar4 = __ct__7_rgba32FUi(auStack_14,0);
      SetBgColor__9GsxCameraFRC7_rgba32(uVar3,uVar4);
    }
    Clr__10CBgElementFv(*(undefined4 *)((int)pCStack_10->pImpl + 0x168));
    RemoveExLight__8CFieldBGFv(pCStack_10);
    *(byte *)((int)pCStack_10->pImpl + 0x1c4) = *(byte *)((int)pCStack_10->pImpl + 0x1c4) & 0xfe;
    for (lVar5 = 0; lVar5 < *(short *)((int)pCStack_10->pImpl + 0x1c8);
        lVar5 = (long)((int)lVar5 + 1)) {
      iVar1 = *(int *)((int)pCStack_10->pImpl + (int)lVar5 * 4 + 0x140);
      if (*(short *)(iVar1 + 0x98) == 0) {
        ClearShadow__11CFieldModelFv(iVar1);
      }
      else if ((*(short *)(iVar1 + 0x98) == 1) && (iVar2 != 0)) {
        uVar3 = GetModel__11CFieldModelFv(iVar1);
        releaseShadow__13ShadowControlFP5Model(iVar2,uVar3);
      }
      ClearModel__11CFieldModelFv(iVar1);
    }
  }
  return;
}

/* JP: 0x004dc370  CFieldBG::SaveRestoreMotion(int, char*)   [SaveRestoreMotion__8CFieldBGFiPc]  size=0x128 */
void SaveRestoreMotion__8CFieldBGFiPc(CFieldBG *this,int a0,char *a1)

{
  undefined4 uVar1;
  undefined8 uVar2;
  long lVar3;
  long lVar4;
  char *pcStack_10;
  
  if ((this->pImpl != (void *)0x0) && ((*(byte *)((int)this->pImpl + 0x1c4) & 1) == 0)) {
    lVar4 = (long)*(short *)((int)this->pImpl + 0x1c8);
    if (8 < lVar4) {
      lVar4 = 8;
    }
    pcStack_10 = a1;
    for (lVar3 = 0; lVar3 < lVar4; lVar3 = (long)((int)lVar3 + 1)) {
      uVar1 = *(undefined4 *)((int)this->pImpl + (int)lVar3 * 4 + 0x140);
      if (a0 == 0) {
        uVar2 = GetLastMotion__11CFieldModelCFv(uVar1);
        strcpy(pcStack_10,uVar2);
      }
      else {
        SetLastMotion__11CFieldModelFPCc(uVar1,pcStack_10);
      }
      pcStack_10 = pcStack_10 + 0x10;
    }
  }
  return;
}

/* JP: 0x004dc4c0  CFieldBG::Update(float)   [Update__8CFieldBGFf]  size=0x94 */
void Update__8CFieldBGFf(CFieldBG *this,float a0)

{
  long lVar1;
  
  for (lVar1 = 0; lVar1 < *(short *)((int)this->pImpl + 0x1c8); lVar1 = (long)((int)lVar1 + 1)) {
    Update__11CFieldModelFf(a0,*(undefined4 *)((int)this->pImpl + (int)lVar1 * 4 + 0x140));
  }
  UpdateLight__10CBgElementFf(a0,*(undefined4 *)((int)this->pImpl + 0x168));
  return;
}

/* JP: 0x004dc560  CFieldBG::LgtAttachFrame(int, Frame*)   [LgtAttachFrame__8CFieldBGFiP5Frame]  size=0x40 */
void LgtAttachFrame__8CFieldBGFiP5Frame(CFieldBG *this,int a0,void *a1)

{
  LgtAttachFrame__10CBgElementFiP5Frame(*(undefined4 *)((int)this->pImpl + 0x168),a0,a1);
  return;
}

/* JP: 0x004dc5a0  CFieldBG::FindFrame(int, const char*)   [FindFrame__8CFieldBGFiPCc]  size=0x80 */
undefined8 FindFrame__8CFieldBGFiPCc(CFieldBG *this,int a0,char *a1)

{
  undefined8 uVar1;
  
  if ((long)a0 < (long)*(short *)((int)this->pImpl + 0x1c8)) {
    uVar1 = SearchFrame__11CFieldModelFPCc(*(undefined4 *)((int)this->pImpl + a0 * 4 + 0x140),a1);
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

/* JP: 0x004dc620  CFieldBG::GetModel(int)   [GetModel__8CFieldBGFi]  size=0x5c */
undefined4 GetModel__8CFieldBGFi(CFieldBG *this,int a0)

{
  undefined4 uVar1;
  
  if (this->pImpl == (void *)0x0) {
    uVar1 = 0;
  }
  else {
    uVar1 = *(undefined4 *)((int)this->pImpl + a0 * 4 + 0x140);
  }
  return uVar1;
}

/* JP: 0x004dc680  CFieldBG::GetModelCount()   [GetModelCount__8CFieldBGFv]  size=0x54 */
undefined2 GetModelCount__8CFieldBGFv(CFieldBG *this)

{
  undefined2 uVar1;
  
  if (this->pImpl == (void *)0x0) {
    uVar1 = 0;
  }
  else {
    uVar1 = *(undefined2 *)((int)this->pImpl + 0x1c8);
  }
  return uVar1;
}

/* JP: 0x004dc6e0  CFieldBG::GetShadowCtrl(bool)   [GetShadowCtrl__8CFieldBGFb]  size=0xcc */
int GetShadowCtrl__8CFieldBGFb(CFieldBG *this,bool a0)

{
  int iVar1;
  int iVar2;
  long lVar3;
  
  iVar2 = m_pOur__13ShadowControl;
  if ((m_pOur__13ShadowControl == 0) && (a0)) {
    iVar1 = m_ourShadowControl__8CFieldBG;
    if (m_ourShadowControl__8CFieldBG == 0) {
      lVar3 = __nw__FUi(0x3520);
      iVar2 = 0;
      iVar1 = 0;
      if (lVar3 != 0) {
        iVar2 = __ct__13ShadowControlFv(lVar3);
        iVar1 = iVar2;
      }
    }
    m_ourShadowControl__8CFieldBG = iVar1;
    m_pOur__13ShadowControl = iVar2;
    m_ShadowCreateCount__8CFieldBG = m_ShadowCreateCount__8CFieldBG + 1;
    *(byte *)((int)this->pImpl + 0x1c4) = *(byte *)((int)this->pImpl + 0x1c4) & 0xf7 | 8;
    iVar2 = m_ourShadowControl__8CFieldBG;
  }
  return iVar2;
}

/* JP: 0x004dc7b0  CFieldBG::ReleaseShadow()   [ReleaseShadow__8CFieldBGFv]  size=0x90 */
void ReleaseShadow__8CFieldBGFv(CFieldBG *this)

{
  if (((this->pImpl != (void *)0x0) &&
      ((long)((ulong)*(byte *)((int)this->pImpl + 0x1c4) << 0x3c) < 0)) &&
     (m_ShadowCreateCount__8CFieldBG = m_ShadowCreateCount__8CFieldBG + -1, m_ShadowCreateCount__8CFieldBG == 0)) {
    (**(code **)(*(int *)(m_ourShadowControl__8CFieldBG + 0x1c) + 0xc))();
    m_ourShadowControl__8CFieldBG = 0;
    m_pOur__13ShadowControl = 0;
  }
  return;
}

/* JP: 0x004dc840  CFieldBG::StartEffect(int)   [StartEffect__8CFieldBGFi]  size=0x160 */
void StartEffect__8CFieldBGFi(CFieldBG *this,int a0)

{
  undefined2 uVar1;
  short *psVar2;
  int iVar3;
  long lVar4;
  int iVar5;
  
  lVar4 = Find__6CSTGDBFUl(this->pSdb,0x2020544345464645);
  if (lVar4 != 0) {
    psVar2 = (short *)GetDataAddr__6CSTGDBFPQ23SDB9tagHEADER(this->pSdb,lVar4);
    uVar1 = *(undefined2 *)(*(int *)((int)this->pImpl + 0x168) + 0x282);
    iVar3 = GetDataNum__6CSTGDBFPQ23SDB9tagHEADER(this->pSdb,lVar4);
    for (iVar5 = 0; iVar5 < iVar3; iVar5 = iVar5 + 1) {
      if (((long)*psVar2 == (long)a0) && ((*(byte *)(psVar2 + 2) & 1) == 0)) {
        CreateEffect__11BgEffectManFiiiPv(eff__11BgEffectMan,uVar1,iVar5,psVar2[1],(int)psVar2 + *(int *)(psVar2 + 4));
        *(byte *)(psVar2 + 2) = *(byte *)(psVar2 + 2) & 0xfe | 1;
      }
      psVar2 = psVar2 + 8;
    }
  }
  return;
}

/* JP: 0x004dc9a0  CFieldBG::StopEffect(int)   [StopEffect__8CFieldBGFi]  size=0x144 */
void StopEffect__8CFieldBGFi(CFieldBG *this,int a0)

{
  undefined2 uVar1;
  short *psVar2;
  int iVar3;
  long lVar4;
  int iVar5;
  
  lVar4 = Find__6CSTGDBFUl(this->pSdb,0x2020544345464645);
  if (lVar4 != 0) {
    psVar2 = (short *)GetDataAddr__6CSTGDBFPQ23SDB9tagHEADER(this->pSdb,lVar4);
    uVar1 = *(undefined2 *)(*(int *)((int)this->pImpl + 0x168) + 0x282);
    iVar3 = GetDataNum__6CSTGDBFPQ23SDB9tagHEADER(this->pSdb,lVar4);
    for (iVar5 = 0; iVar5 < iVar3; iVar5 = iVar5 + 1) {
      if (((long)*psVar2 == (long)a0) && ((*(byte *)(psVar2 + 2) & 1) == 1)) {
        ClearEffect__11BgEffectManFii(eff__11BgEffectMan,uVar1,iVar5);
        *(byte *)(psVar2 + 2) = *(byte *)(psVar2 + 2) & 0xfe;
      }
      psVar2 = psVar2 + 8;
    }
  }
  return;
}

/* JP: 0x004dcaf0  CFieldBG::EffectAlpha(int, float, int)   [EffectAlpha__8CFieldBGFifi]  size=0x13c */
void EffectAlpha__8CFieldBGFifi(CFieldBG *this,int a0,float a1,int a2)

{
  undefined2 uVar1;
  short *psVar2;
  int iVar3;
  long lVar4;
  int iVar5;
  
  lVar4 = Find__6CSTGDBFUl(this->pSdb,0x2020544345464645);
  if (lVar4 != 0) {
    psVar2 = (short *)GetDataAddr__6CSTGDBFPQ23SDB9tagHEADER(this->pSdb,lVar4);
    uVar1 = *(undefined2 *)(*(int *)((int)this->pImpl + 0x168) + 0x282);
    iVar3 = GetDataNum__6CSTGDBFPQ23SDB9tagHEADER(this->pSdb,lVar4);
    for (iVar5 = 0; iVar5 < iVar3; iVar5 = iVar5 + 1) {
      if (((long)*psVar2 == (long)a0) && ((*(byte *)(psVar2 + 2) & 1) == 1)) {
        EffectAlpha__11BgEffectManFiifi(a1,eff__11BgEffectMan,uVar1,iVar5,a2);
      }
      psVar2 = psVar2 + 8;
    }
  }
  return;
}

/* JP: 0x004dcc30  CFieldBG::AddExLight(void*)   [AddExLight__8CFieldBGFPv]  size=0x7c */
void AddExLight__8CFieldBGFPv(CFieldBG *this,void *a0)

{
  memcpy((int)this->pImpl + 0x170,a0,0x40);
  *(byte *)((int)this->pImpl + 0x1c4) = *(byte *)((int)this->pImpl + 0x1c4) & 0xfb | 4;
  RecreateExLight__8CFieldBGFv(this);
  return;
}

/* JP: 0x004dccb0  CFieldBG::RecreateExLight()   [RecreateExLight__8CFieldBGFv]  size=0x3a4 */
/* WARNING: Removing unreachable block (ram,0x004dcedc) */

long RecreateExLight__8CFieldBGFv(CFieldBG *this)

{
  byte bVar1;
  void *pvVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined8 uVar5;
  long lVar6;
  byte bVar7;
  long lVar8;
  undefined1 auStack_100 [16];
  undefined1 auStack_f0 [16];
  undefined1 auStack_e0 [16];
  undefined1 auStack_d0 [16];
  undefined1 auStack_c0 [16];
  undefined1 auStack_b0 [16];
  undefined1 auStack_a0 [16];
  undefined1 auStack_90 [16];
  undefined1 auStack_80 [16];
  undefined1 auStack_70 [16];
  undefined1 auStack_60 [16];
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [16];
  undefined1 auStack_20 [16];
  CFieldBG *pCStack_10;
  
  pvVar2 = this->pImpl;
  pCStack_10 = this;
  __ct__7FVectorFv(auStack_20);
  __ct__7FVectorFv(auStack_30);
  __ct__7FVectorFv(auStack_40);
  uVar3 = __ct__7FVectorFPC7FVector(auStack_60,(int)pvVar2 + 0x180);
  __as__7FVectorFRC7FVector(auStack_20,uVar3);
  uVar3 = __ct__7FVectorFPC7FVector(auStack_70,(int)pvVar2 + 400);
  __as__7FVectorFRC7FVector(auStack_30,uVar3);
  uVar3 = __ct__7FVectorFPC7FVector(auStack_80,(int)pvVar2 + 0x1a0);
  __as__7FVectorFRC7FVector(auStack_40,uVar3);
  lVar8 = -1;
  bVar1 = *(byte *)((int)pvVar2 + 0x170);
  bVar7 = bVar1 & 7;
  if (bVar7 == 3) {
    uVar3 = __ct__7FVectorFRC7FVector(auStack_e0,auStack_30);
    uVar4 = __ct__7FVectorFRC7FVector(auStack_f0,auStack_40);
    uVar5 = __ct__7FVectorFRC7FVector(auStack_100,auStack_20);
    lVar8 = CreateSpot__12LightControlF7FVector7FVector7FVector(uVar3,uVar4,uVar5);
    changeAngle__12LightControlFif(*(undefined4 *)((int)pvVar2 + 0x178),lVar8);
    changeDropOff__12LightControlFif(*(undefined4 *)((int)pvVar2 + 0x17c),lVar8);
  }
  else if (bVar7 == 2) {
    uVar3 = __ct__7FVectorFRC7FVector(auStack_c0,auStack_30);
    uVar4 = __ct__7FVectorFRC7FVector(auStack_d0,auStack_20);
    lVar8 = CreatePoint__12LightControlF7FVector7FVector(uVar3,uVar4);
  }
  else if (bVar7 == 1) {
    uVar3 = __ct__7FVectorFRC7FVector(auStack_a0,auStack_40);
    uVar4 = __ct__7FVectorFRC7FVector(auStack_b0,auStack_20);
    lVar8 = CreateDirectional__12LightControlF7FVector7FVector(uVar3,uVar4);
  }
  else if ((bVar1 & 7) == 0) {
    uVar3 = __ct__7FVectorFRC7FVector(auStack_90,auStack_20);
    lVar8 = CreateAmbient__12LightControlF7FVector(uVar3);
  }
  if (-1 < lVar8) {
    changeDeclineType__12LightControlFiQ29LightData11DeclineType(lVar8,((ulong)*(byte *)((int)pvVar2 + 0x170) & 0x1f) >> 3);
    changeShadowFlg__12LightControlFib(lVar8,1);
    changeActive__12LightControlFib(lVar8,1);
    changeStrength__12LightControlFif(*(undefined4 *)((int)pvVar2 + 0x174),lVar8);
  }
  *(int *)((int)pCStack_10->pImpl + 0x1b0) = (int)lVar8;
  uVar3 = 0;
  uStack_50 = 0x8026596e;
  uStack_4c = 0x40d00000;
  lVar6 = Find__6CSTGDBFUl(pCStack_10->pSdb,0x2020544345464645);
  if (lVar6 != 0) {
    uVar3 = GetDataNum__6CSTGDBFPQ23SDB9tagHEADER(pCStack_10->pSdb,lVar6);
  }
  *(int *)((int)pCStack_10->pImpl + 0x1b4) = (int)uVar3;
  CreateEffect__11BgEffectManFiiiPv(eff__11BgEffectMan,*(undefined2 *)(*(int *)((int)pCStack_10->pImpl + 0x168) + 0x282),
                  uVar3,0x100,&uStack_50);
  return lVar8;
}

/* JP: 0x004dd060  CFieldBG::GetExLight()   [GetExLight__8CFieldBGFv]  size=0x20 */
undefined4 GetExLight__8CFieldBGFv(CFieldBG *this)

{
  return *(undefined4 *)((int)this->pImpl + 0x1b0);
}

/* JP: 0x004dd080  CFieldBG::RemoveExLight()   [RemoveExLight__8CFieldBGFv]  size=0x88 */
void RemoveExLight__8CFieldBGFv(CFieldBG *this)

{
  if (-1 < *(int *)((int)this->pImpl + 0x1b0)) {
    release__12LightControlFi(*(undefined4 *)((int)this->pImpl + 0x1b0));
    *(undefined4 *)((int)this->pImpl + 0x1b0) = 0xffffffff;
    ClearEffect__11BgEffectManFii(eff__11BgEffectMan,*(undefined2 *)(*(int *)((int)this->pImpl + 0x168) + 0x282),
                    *(undefined4 *)((int)this->pImpl + 0x1b4));
  }
  return;
}
