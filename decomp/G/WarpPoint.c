/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: WarpPoint   functions: 18
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/WarpPoint.md).
 */

/* JP: 0x00432a30  WarpPoint::WarpPoint()   [__ct__9WarpPointFv]  size=0x174 */
int __ct__9WarpPointFv(int param_1)

{
  undefined8 uVar1;
  undefined1 auStack_20 [16];
  int iStack_10;
  
  iStack_10 = param_1;
  __ct__7CPolObjFv(param_1);
  *(undefined1 **)(iStack_10 + 0x14) = &__vt__9WarpPoint;
  __ct__7FVectorFv(iStack_10 + 0x30);
  __ct__7FVectorFv(iStack_10 + 0x40);
  __ct__Q29WarpPoint17_class_2140WP_cppFv(iStack_10 + 0x60);
  __ct__7FVectorFv(iStack_10 + 0xa0);
  __ct__7FVectorFv(iStack_10 + 0xb0);
  __ct__7FVectorFv(iStack_10 + 0xc0);
  Init__Q29WarpPoint17_class_2141WP_cppFv(iStack_10 + 0x90);
  *(undefined4 *)(iStack_10 + 0x24) = 0;
  *(undefined4 *)(iStack_10 + 0x20) = 0;
  *(undefined4 *)(iStack_10 + 0x1c) = 0;
  *(undefined4 *)(iStack_10 + 0x18) = 0;
  *(undefined4 *)(iStack_10 + 0x28) = 0;
  *(undefined4 *)(iStack_10 + 0x5c) = 0;
  uVar1 = __ct__7FVectorFffff(0x3f800000,0x3f800000,0x3f800000,0x3f800000,auStack_20);
  __as__7FVectorFRC7FVector(iStack_10 + 0xb0,uVar1);
  *(undefined4 *)(iStack_10 + 0x58) = 0xffffffff;
  *(undefined4 *)(iStack_10 + 0xd0) = 0;
  *(undefined4 *)(iStack_10 + 0xd4) = 0;
  *(undefined4 *)(iStack_10 + 0xd8) = 0;
  *(undefined4 *)(iStack_10 + 0x54) = 0x42800000;
  Origin__7FVectorFv(iStack_10 + 0xa0);
  Origin__7FVectorFv(iStack_10 + 0xc0);
  return iStack_10;
}

/* JP: 0x00432c10  WarpPoint::~WarpPoint()   [__dt__9WarpPointFv]  size=0x244 */
int __dt__9WarpPointFv(int param_1,short param_2)

{
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 0x14) = &__vt__9WarpPoint;
    printf(0x555630);
    m_WpRefer__9WarpPoint = m_WpRefer__9WarpPoint + -1;
    if (*(int *)(param_1 + 0x18) != 0) {
      ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,*(undefined4 *)(param_1 + 0x18));
      (**(code **)(*(int *)(*(int *)(param_1 + 0x18) + 0x1c) + 0xc))();
    }
    if (*(int *)(param_1 + 0x1c) != 0) {
      ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,*(undefined4 *)(param_1 + 0x1c));
      (**(code **)(*(int *)(*(int *)(param_1 + 0x1c) + 0x1c) + 0xc))();
    }
    if (*(int *)(param_1 + 0x20) != 0) {
      ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,*(undefined4 *)(param_1 + 0x20));
      (**(code **)(*(int *)(*(int *)(param_1 + 0x20) + 0x1c) + 0xc))();
    }
    if (*(int *)(param_1 + 0x24) != 0) {
      ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,*(undefined4 *)(param_1 + 0x24));
      (**(code **)(*(int *)(*(int *)(param_1 + 0x24) + 0x1c) + 0xc))();
    }
    if (*(int *)(param_1 + 0x28) != 0) {
      ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,*(undefined4 *)(param_1 + 0x28));
      (**(code **)(*(int *)(*(int *)(param_1 + 0x28) + 0x1c) + 0xc))();
    }
    if ((m_Buffer__9WarpPoint != 0) && (m_WpRefer__9WarpPoint == 0)) {
      Reserve__7DeleterFP9BufMemory(m_Buffer__9WarpPoint);
      m_Buffer__9WarpPoint = 0;
    }
    release__12LightControlFi(*(undefined4 *)(param_1 + 0x58));
    Dispose__7CPollerFP7CPolObj(app__4CApp + 0x60,param_1);
    __dt__7CPolObjFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x00432e60  WarpPoint::Create(short)   [Create__9WarpPointFs]  size=0x1c8 */
void Create__9WarpPointFs(int param_1,ushort param_2)

{
  undefined1 auStack_a0 [128];
  int iStack_20;
  ushort uStack_10;
  
  *(ushort *)(param_1 + 0x90) = *(ushort *)(param_1 + 0x90) & 0xfe1f | (param_2 & 0xf) << 5;
  iStack_20 = param_1;
  uStack_10 = param_2;
  if (m_Buffer__9WarpPoint == 0) {
    *(byte *)(param_1 + 0x90) = *(byte *)(param_1 + 0x90) & 0xfe;
    switch(param_2) {
    case 0:
      SetPathname__7SysToolFPcPCc(auStack_a0,0x555660);
      break;
    case 1:
      SetPathname__7SysToolFPcPCc(auStack_a0,0x555640);
      break;
    case 2:
      SetPathname__7SysToolFPcPCc(auStack_a0,0x555650);
      break;
    case 3:
    case 4:
    case 5:
      SetPathname__7SysToolFPcPCc(auStack_a0,0x555670);
      break;
    case 6:
      SetPathname__7SysToolFPcPCc(auStack_a0,0x555680);
    }
    if (-1 < (long)((ulong)*(byte *)(iStack_20 + 0x91) << 0x3a)) {
      ReadOrder__11DvdromOrderFPCcPFiP9BufMemoryiPcPv_iiPvi(Dvdromour__11DvdromOrder,auStack_a0,0x4329f0,0,iStack_20,0);
    }
    *(byte *)(iStack_20 + 0x91) = *(byte *)(iStack_20 + 0x91) & 0xdf | 0x20;
  }
  else {
    cbWpCallback__FiP9BufMemoryiPcPv(0,m_Buffer__9WarpPoint,0,0,param_1);
  }
  return;
}

/* JP: 0x00433030  WarpPoint::CreateDirect(BufMemory*)   [CreateDirect__9WarpPointFP9BufMemory]  size=0x410 */
void CreateDirect__9WarpPointFP9BufMemory(int param_1,int param_2)

{
  undefined4 uVar1;
  undefined8 uVar2;
  long lVar3;
  
  printf(0x5556b0);
  if (((ulong)*(ushort *)(param_1 + 0x90) & 0x1ff) >> 5 < 7) {
                    /* WARNING: Could not recover jumptable at 0x0043309c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*(code *)(&_2285)[(uint)(((ulong)*(ushort *)(param_1 + 0x90) << 0x37) >> 0x3c)])();
    return;
  }
  uVar2 = getBuffer__9BufMemoryFv(param_2);
  uVar2 = GetFileEntry(uVar2,0);
  lVar3 = __nw__FUi(0x510);
  uVar1 = 0;
  if (lVar3 != 0) {
    uVar1 = __ct__7ExModelFPUc(lVar3,uVar2);
  }
  *(undefined4 *)(param_1 + 0x18) = uVar1;
  uVar2 = getBuffer__9BufMemoryFv(param_2);
  uVar2 = GetFileEntry(uVar2,1);
  createMotion__5ModelFPUc(*(undefined4 *)(param_1 + 0x18),uVar2);
  (**(code **)(*(int *)(*(int *)(param_1 + 0x18) + 0x10) + 0x28))(*(int *)(param_1 + 0x18),0);
  uVar2 = getBuffer__9BufMemoryFv(param_2);
  uVar2 = GetFileEntry(uVar2,2);
  lVar3 = __nw__FUi(0x510);
  uVar1 = 0;
  if (lVar3 != 0) {
    uVar1 = __ct__7ExModelFPUc(lVar3,uVar2);
  }
  *(undefined4 *)(param_1 + 0x1c) = uVar1;
  uVar2 = getBuffer__9BufMemoryFv(param_2);
  uVar2 = GetFileEntry(uVar2,3);
  createMotion__5ModelFPUc(*(undefined4 *)(param_1 + 0x1c),uVar2);
  (**(code **)(*(int *)(*(int *)(param_1 + 0x1c) + 0x10) + 0x28))(*(int *)(param_1 + 0x1c),0);
  uVar2 = getBuffer__9BufMemoryFv(param_2);
  uVar2 = GetFileEntry(uVar2,4);
  lVar3 = __nw__FUi(0x510);
  uVar1 = 0;
  if (lVar3 != 0) {
    uVar1 = __ct__7ExModelFPUc(lVar3,uVar2);
  }
  *(undefined4 *)(param_1 + 0x20) = uVar1;
  uVar2 = getBuffer__9BufMemoryFv(param_2);
  uVar2 = GetFileEntry(uVar2,5);
  createMotion__5ModelFPUc(*(undefined4 *)(param_1 + 0x20),uVar2);
  (**(code **)(*(int *)(*(int *)(param_1 + 0x20) + 0x10) + 0x28))(*(int *)(param_1 + 0x20),0);
  if (((ulong)*(ushort *)(param_1 + 0x90) & 0x1ff) >> 5 == 1) {
    uVar2 = getBuffer__9BufMemoryFv(param_2);
    uVar2 = GetFileEntry(uVar2,6);
    lVar3 = __nw__FUi(0x510);
    uVar1 = 0;
    if (lVar3 != 0) {
      uVar1 = __ct__7ExModelFPUc(lVar3,uVar2);
    }
    *(undefined4 *)(param_1 + 0x24) = uVar1;
    uVar2 = getBuffer__9BufMemoryFv(param_2);
    uVar2 = GetFileEntry(uVar2,7);
    createMotion__5ModelFPUc(*(undefined4 *)(param_1 + 0x24),uVar2);
    (**(code **)(*(int *)(*(int *)(param_1 + 0x24) + 0x10) + 0x28))(*(int *)(param_1 + 0x24),0);
  }
  *(byte *)(param_1 + 0x90) = *(byte *)(param_1 + 0x90) & 0xfe | 1;
  m_WpRefer__9WarpPoint = m_WpRefer__9WarpPoint + 1;
  SetAlpha__9WarpPointFf(0x42c80000,param_1);
  if (m_Buffer__9WarpPoint == 0) {
    m_Buffer__9WarpPoint = param_2;
  }
  lVar3 = Find__7CPollerCFPC7CPolObj(app__4CApp + 0x60,param_1);
  if (lVar3 == 0) {
    Entry__7CPollerFP7CPolObjib(app__4CApp + 0x60,param_1,0x80,0);
  }
  return;
}

/* JP: 0x00433440  WarpPoint::Show(int, int, bool)   [Show__9WarpPointFiib]  size=0x248 */
void Show__9WarpPointFiib(int param_1,undefined4 param_2,undefined4 param_3,byte param_4)

{
  ulong uVar1;
  
  if (-1 < (long)((ulong)*(byte *)(param_1 + 0x90) << 0x3e)) {
    *(undefined4 *)(param_1 + 0x94) = param_2;
    *(undefined4 *)(param_1 + 0x98) = param_3;
    *(byte *)(param_1 + 0x90) = *(byte *)(param_1 + 0x90) & 0xfd | 2;
    *(byte *)(param_1 + 0x91) = *(byte *)(param_1 + 0x91) & 0xbf | (param_4 & 1) << 6;
    if ((*(byte *)(param_1 + 0x90) & 1) == 0) {
      *(byte *)(param_1 + 0x90) = *(byte *)(param_1 + 0x90) & 0xfb | 4;
    }
    else {
      if (((ulong)*(ushort *)(param_1 + 0x90) & 0x1ff) >> 5 == 1) {
        AddDoubleOT__5WorldFiiP8VIF1Prim(0x42bf10,*(undefined4 *)(param_1 + 0x94),*(undefined4 *)(param_1 + 0x98),
                        *(undefined4 *)(param_1 + 0x24));
        setMotion__7ExModelFPCc(*(undefined4 *)(param_1 + 0x24),0x5556f0);
      }
      if (param_4 == 0) {
        uVar1 = ((ulong)*(ushort *)(param_1 + 0x90) & 0x1ff) >> 5;
        if (((uVar1 != 5) && (uVar1 != 4)) && (uVar1 != 3)) {
          AddDoubleOT__5WorldFiiP8VIF1Prim(0x42bf10,*(undefined4 *)(param_1 + 0x94),*(undefined4 *)(param_1 + 0x98),
                          *(undefined4 *)(param_1 + 0x18));
          setMotion__7ExModelFPCc(*(undefined4 *)(param_1 + 0x18),0x5556f8);
          SetLight__9WarpPointFv(param_1);
        }
      }
      else {
        AddDoubleOT__5WorldFiiP8VIF1Prim(0x42bf10,*(undefined4 *)(param_1 + 0x94),*(undefined4 *)(param_1 + 0x98),
                        *(undefined4 *)(param_1 + 0x18));
        setMotion__7ExModelFPCc(*(undefined4 *)(param_1 + 0x18),0x5556f8);
        SetLight__9WarpPointFv(param_1);
        *(undefined4 *)(param_1 + 0xd0) = 2;
        *(undefined4 *)(param_1 + 0xd8) = 0x3f800000;
      }
    }
  }
  return;
}

/* JP: 0x00433690  WarpPoint::Hide()   [Hide__9WarpPointFv]  size=0x17c */
void Hide__9WarpPointFv(int param_1)

{
  *(byte *)(param_1 + 0x90) = *(byte *)(param_1 + 0x90) & 0xfd;
  *(byte *)(param_1 + 0x91) = *(byte *)(param_1 + 0x91) & 0xe7;
  *(byte *)(param_1 + 0x90) = *(byte *)(param_1 + 0x90) & 0xfb;
  if (*(int *)(param_1 + 0x18) != 0) {
    ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,*(undefined4 *)(param_1 + 0x18));
  }
  if (*(int *)(param_1 + 0x1c) != 0) {
    ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,*(undefined4 *)(param_1 + 0x1c));
  }
  if (*(int *)(param_1 + 0x20) != 0) {
    ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,*(undefined4 *)(param_1 + 0x20));
  }
  if (*(int *)(param_1 + 0x24) != 0) {
    ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,*(undefined4 *)(param_1 + 0x24));
  }
  if (*(int *)(param_1 + 0x28) != 0) {
    ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,*(undefined4 *)(param_1 + 0x28));
  }
  if (*(int *)(param_1 + 0x58) != -1) {
    release__12LightControlFi(*(undefined4 *)(param_1 + 0x58));
  }
  *(undefined4 *)(param_1 + 0x58) = 0xffffffff;
  return;
}

/* JP: 0x00433810  WarpPoint::Polling()   [Polling__9WarpPointFv]  size=0x120c */
undefined8 Polling__9WarpPointFv(int param_1)

{
  float *pfVar1;
  int iVar2;
  undefined4 *puVar3;
  long lVar4;
  undefined8 uVar5;
  ulong uVar6;
  float fVar7;
  undefined1 auStack_160 [64];
  undefined1 auStack_120 [64];
  undefined1 auStack_e0 [64];
  undefined1 auStack_a0 [16];
  undefined1 auStack_90 [16];
  undefined1 auStack_80 [16];
  undefined1 auStack_70 [16];
  undefined1 auStack_60 [16];
  undefined1 auStack_50 [64];
  int iStack_10;
  
  if ((long)((ulong)*(byte *)(param_1 + 0x90) << 0x3e) < 0) {
    iStack_10 = param_1;
    lVar4 = isPaused__6CPauseFv(*(undefined4 *)(app__4CApp + 0x78));
    if (((lVar4 == 0) && (*(int *)(iStack_10 + 0x28) != 0)) &&
       (-1 < (long)((ulong)*(byte *)(iStack_10 + 0x90) << 0x3b))) {
      pfVar1 = (float *)vx__7FVectorFv(iStack_10 + 0x40);
      fVar7 = *pfVar1;
      pfVar1 = (float *)vx__7FVectorFv(iStack_10 + 0x30);
      *pfVar1 = *pfVar1 + fVar7;
      pfVar1 = (float *)vy__7FVectorFv(iStack_10 + 0x40);
      fVar7 = *pfVar1;
      pfVar1 = (float *)vy__7FVectorFv(iStack_10 + 0x30);
      *pfVar1 = *pfVar1 + fVar7;
      pfVar1 = (float *)vz__7FVectorFv(iStack_10 + 0x40);
      fVar7 = *pfVar1;
      pfVar1 = (float *)vz__7FVectorFv(iStack_10 + 0x30);
      *pfVar1 = *pfVar1 + fVar7;
      pfVar1 = (float *)vw__7FVectorFv(iStack_10 + 0x40);
      fVar7 = *pfVar1;
      pfVar1 = (float *)vw__7FVectorFv(iStack_10 + 0x30);
      *pfVar1 = *pfVar1 + fVar7;
      pfVar1 = (float *)vx__7FVectorFv(iStack_10 + 0x30);
      if (255.0 < *pfVar1) {
        puVar3 = (undefined4 *)vx__7FVectorFv(iStack_10 + 0x30);
        *puVar3 = 0x437f0000;
      }
      pfVar1 = (float *)vy__7FVectorFv(iStack_10 + 0x30);
      if (255.0 < *pfVar1) {
        puVar3 = (undefined4 *)vy__7FVectorFv(iStack_10 + 0x30);
        *puVar3 = 0x437f0000;
      }
      pfVar1 = (float *)vz__7FVectorFv(iStack_10 + 0x30);
      if (255.0 < *pfVar1) {
        puVar3 = (undefined4 *)vz__7FVectorFv(iStack_10 + 0x30);
        *puVar3 = 0x437f0000;
      }
      pfVar1 = (float *)vw__7FVectorFv(iStack_10 + 0x30);
      if (255.0 < *pfVar1) {
        puVar3 = (undefined4 *)vw__7FVectorFv(iStack_10 + 0x30);
        *puVar3 = 0x437f0000;
      }
      pfVar1 = (float *)vx__7FVectorFv(iStack_10 + 0x30);
      if (*pfVar1 < 0.0) {
        puVar3 = (undefined4 *)vx__7FVectorFv(iStack_10 + 0x30);
        *puVar3 = 0;
      }
      pfVar1 = (float *)vy__7FVectorFv(iStack_10 + 0x30);
      if (*pfVar1 < 0.0) {
        puVar3 = (undefined4 *)vy__7FVectorFv(iStack_10 + 0x30);
        *puVar3 = 0;
      }
      pfVar1 = (float *)vz__7FVectorFv(iStack_10 + 0x30);
      if (*pfVar1 < 0.0) {
        puVar3 = (undefined4 *)vz__7FVectorFv(iStack_10 + 0x30);
        *puVar3 = 0;
      }
      pfVar1 = (float *)vw__7FVectorFv(iStack_10 + 0x30);
      if (*pfVar1 < 0.0) {
        puVar3 = (undefined4 *)vw__7FVectorFv(iStack_10 + 0x30);
        *puVar3 = 0;
      }
      __as__7FVectorFRC7FVector(*(int *)(iStack_10 + 0x28) + 0x40,iStack_10 + 0x30);
      *(float *)(iStack_10 + 0x50) = *(float *)(iStack_10 + 0x50) - 1.0;
      if (*(float *)(iStack_10 + 0x50) < 0.0) {
        if ((long)((ulong)*(byte *)(iStack_10 + 0x90) << 0x3c) < 0) {
          *(byte *)(iStack_10 + 0x90) = *(byte *)(iStack_10 + 0x90) & 0xef | 0x10;
        }
        else {
          ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,*(undefined4 *)(iStack_10 + 0x28));
          (**(code **)(*(int *)(*(int *)(iStack_10 + 0x28) + 0x1c) + 0xc))();
          *(undefined4 *)(iStack_10 + 0x28) = 0;
        }
      }
    }
    if ((*(byte *)(iStack_10 + 0x90) & 1) != 0) {
      if ((long)((ulong)*(byte *)(iStack_10 + 0x90) << 0x3d) < 0) {
        if (((ulong)*(ushort *)(iStack_10 + 0x90) & 0x1ff) >> 5 == 1) {
          AddDoubleOT__5WorldFiiP8VIF1Prim(0x42bf10,*(undefined4 *)(iStack_10 + 0x94),
                          *(undefined4 *)(iStack_10 + 0x98),*(undefined4 *)(iStack_10 + 0x24));
          setMotion__7ExModelFPCc(*(undefined4 *)(iStack_10 + 0x24),0x5556f0);
        }
        if ((long)((ulong)*(byte *)(iStack_10 + 0x91) << 0x39) < 0) {
          AddDoubleOT__5WorldFiiP8VIF1Prim(0x42bf10,*(undefined4 *)(iStack_10 + 0x94),
                          *(undefined4 *)(iStack_10 + 0x98),*(undefined4 *)(iStack_10 + 0x18));
          setMotion__7ExModelFPCc(*(undefined4 *)(iStack_10 + 0x18),0x5556f8);
          *(byte *)(iStack_10 + 0x90) = *(byte *)(iStack_10 + 0x90) & 0xfb;
          SetLight__9WarpPointFv(iStack_10);
          *(undefined4 *)(iStack_10 + 0xd0) = 2;
          *(undefined4 *)(iStack_10 + 0xd8) = 0x3f800000;
        }
        else {
          uVar6 = ((ulong)*(ushort *)(iStack_10 + 0x90) & 0x1ff) >> 5;
          if (((uVar6 != 5) && (uVar6 != 4)) && (uVar6 != 3)) {
            AddDoubleOT__5WorldFiiP8VIF1Prim(0x42bf10,*(undefined4 *)(iStack_10 + 0x94),
                            *(undefined4 *)(iStack_10 + 0x98),*(undefined4 *)(iStack_10 + 0x18));
            setMotion__7ExModelFPCc(*(undefined4 *)(iStack_10 + 0x18),0x5556f8);
            *(byte *)(iStack_10 + 0x90) = *(byte *)(iStack_10 + 0x90) & 0xfb;
            SetLight__9WarpPointFv(iStack_10);
          }
        }
      }
      if (((((ulong)*(ushort *)(iStack_10 + 0x90) & 0x1ff) >> 5 == 3) ||
          (((ulong)*(ushort *)(iStack_10 + 0x90) & 0x1ff) >> 5 == 4)) ||
         (((ulong)*(ushort *)(iStack_10 + 0x90) & 0x1ff) >> 5 == 5)) {
        if (*(int *)(iStack_10 + 0xd0) == 3) {
          iVar2 = *(int *)(iStack_10 + 0xd4) + 1;
          *(int *)(iStack_10 + 0xd4) = iVar2;
          if (iVar2 < 0x1a) {
            *(float *)(iStack_10 + 0xd8) = *(float *)(iStack_10 + 0xd8) - 0.04;
            if (*(float *)(iStack_10 + 0xd8) < 0.0) {
              *(undefined4 *)(iStack_10 + 0xd8) = 0;
            }
            SetAlphaWeight__7ExModelFf
                      (*(undefined4 *)(iStack_10 + 0xd8),*(undefined4 *)(iStack_10 + 0x18));
          }
          else {
            *(undefined4 *)(iStack_10 + 0xd0) = 0;
            ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,*(undefined4 *)(iStack_10 + 0x18));
            SetAlphaWeight__7ExModelFf(0,*(undefined4 *)(iStack_10 + 0x18));
          }
        }
        else if (*(int *)(iStack_10 + 0xd0) == 1) {
          iVar2 = *(int *)(iStack_10 + 0xd4) + 1;
          *(int *)(iStack_10 + 0xd4) = iVar2;
          if (iVar2 < 0x1a) {
            *(float *)(iStack_10 + 0xd8) = *(float *)(iStack_10 + 0xd8) + 0.04;
            if (1.0 < *(float *)(iStack_10 + 0xd8)) {
              *(undefined4 *)(iStack_10 + 0xd8) = 0x3f800000;
            }
            SetAlphaWeight__7ExModelFf
                      (*(undefined4 *)(iStack_10 + 0xd8),*(undefined4 *)(iStack_10 + 0x18));
          }
          else {
            *(undefined4 *)(iStack_10 + 0xd0) = 2;
            SetAlphaWeight__7ExModelFf(0x3f800000,*(undefined4 *)(iStack_10 + 0x18));
          }
        }
      }
      uVar6 = ((ulong)*(byte *)(iStack_10 + 0x91) & 7) >> 1;
      if (uVar6 == 2) {
        WarpOut__9WarpPointFR7FVectorR7FVectorsb
                  (iStack_10,iStack_10 + 0x60,iStack_10 + 0x70,*(undefined2 *)(iStack_10 + 0x80),
                   *(undefined1 *)(iStack_10 + 0x82));
        *(byte *)(iStack_10 + 0x91) = *(byte *)(iStack_10 + 0x91) & 0xf9;
      }
      else if (uVar6 == 1) {
        WarpIn__9WarpPointFR7FVectorR7FVectorsb
                  (iStack_10,iStack_10 + 0x60,iStack_10 + 0x70,*(undefined2 *)(iStack_10 + 0x80),
                   *(undefined1 *)(iStack_10 + 0x82));
        *(byte *)(iStack_10 + 0x91) = *(byte *)(iStack_10 + 0x91) & 0xf9;
      }
      if (((ulong)*(ushort *)(iStack_10 + 0x90) & 0x1ff) >> 5 == 1) {
        __ct__6MatrixFv(auStack_50);
        __ct__7FVectorFRC7FVector(auStack_60,iStack_10 + 0xa0);
        __ct__7FVectorFRC7FVector(auStack_70,iStack_10 + 0xb0);
        __ct__7FVectorFffff(0xbdcccccd,0,0xc06ccccd,0x3f800000,auStack_80);
        pfVar1 = (float *)vx__7FVectorFv(auStack_70);
        *pfVar1 = *pfVar1 * 1.3;
        pfVar1 = (float *)vy__7FVectorFv(auStack_70);
        *pfVar1 = *pfVar1 * 1.3;
        pfVar1 = (float *)vz__7FVectorFv(auStack_70);
        *pfVar1 = *pfVar1 * 1.3;
        SetScale__7ExModelFR7FVector(*(undefined4 *)(iStack_10 + 0x24),auStack_70);
        RotMatrix__6MatrixFRC7FVector(auStack_50,iStack_10 + 0xc0);
        RotYMatrix__6MatrixFf(0x40490fd8,auStack_50);
        ApplyMatrix__6MatrixCFRC7FVector(auStack_a0,auStack_50,auStack_80);
        __as__7FVectorFRC7FVector(auStack_80,auStack_a0);
        __apl__7FVectorFRC7FVector(auStack_60,auStack_80);
        UnitMatrix__6MatrixFv(*(int *)(*(int *)(iStack_10 + 0x18) + 0x30) + 0x160);
        puVar3 = (undefined4 *)vx__7FVectorFv(auStack_70);
        *(undefined4 *)(*(int *)(*(int *)(iStack_10 + 0x18) + 0x30) + 0x160) = *puVar3;
        puVar3 = (undefined4 *)vy__7FVectorFv(auStack_70);
        *(undefined4 *)(*(int *)(*(int *)(iStack_10 + 0x18) + 0x30) + 0x174) = *puVar3;
        puVar3 = (undefined4 *)vz__7FVectorFv(auStack_70);
        *(undefined4 *)(*(int *)(*(int *)(iStack_10 + 0x18) + 0x30) + 0x188) = *puVar3;
        MulMatrix__6MatrixCFRC6Matrix(auStack_e0,*(int *)(*(int *)(iStack_10 + 0x18) + 0x30) + 0x160,auStack_50);
        __as__6MatrixFRC6Matrix(*(int *)(*(int *)(iStack_10 + 0x18) + 0x30) + 0x160,auStack_e0);
        uVar5 = GetPos__6MatrixFv(*(int *)(*(int *)(iStack_10 + 0x18) + 0x30) + 0x160);
        __as__7FVectorFRC7FVector(uVar5,auStack_60);
        myMatrixUpdate__5FrameFv(*(undefined4 *)(*(int *)(iStack_10 + 0x18) + 0x30));
        UnitMatrix__6MatrixFv(*(int *)(*(int *)(iStack_10 + 0x1c) + 0x30) + 0x160);
        puVar3 = (undefined4 *)vx__7FVectorFv(auStack_70);
        *(undefined4 *)(*(int *)(*(int *)(iStack_10 + 0x1c) + 0x30) + 0x160) = *puVar3;
        puVar3 = (undefined4 *)vy__7FVectorFv(auStack_70);
        *(undefined4 *)(*(int *)(*(int *)(iStack_10 + 0x1c) + 0x30) + 0x174) = *puVar3;
        puVar3 = (undefined4 *)vz__7FVectorFv(auStack_70);
        *(undefined4 *)(*(int *)(*(int *)(iStack_10 + 0x1c) + 0x30) + 0x188) = *puVar3;
        MulMatrix__6MatrixCFRC6Matrix(auStack_120,*(int *)(*(int *)(iStack_10 + 0x1c) + 0x30) + 0x160,auStack_50);
        __as__6MatrixFRC6Matrix(*(int *)(*(int *)(iStack_10 + 0x1c) + 0x30) + 0x160,auStack_120);
        uVar5 = GetPos__6MatrixFv(*(int *)(*(int *)(iStack_10 + 0x1c) + 0x30) + 0x160);
        __as__7FVectorFRC7FVector(uVar5,auStack_60);
        myMatrixUpdate__5FrameFv(*(undefined4 *)(*(int *)(iStack_10 + 0x1c) + 0x30));
        UnitMatrix__6MatrixFv(*(int *)(*(int *)(iStack_10 + 0x20) + 0x30) + 0x160);
        puVar3 = (undefined4 *)vx__7FVectorFv(iStack_10 + 0xb0);
        *(undefined4 *)(*(int *)(*(int *)(iStack_10 + 0x20) + 0x30) + 0x160) = *puVar3;
        puVar3 = (undefined4 *)vy__7FVectorFv(iStack_10 + 0xb0);
        *(undefined4 *)(*(int *)(*(int *)(iStack_10 + 0x20) + 0x30) + 0x174) = *puVar3;
        puVar3 = (undefined4 *)vz__7FVectorFv(iStack_10 + 0xb0);
        *(undefined4 *)(*(int *)(*(int *)(iStack_10 + 0x20) + 0x30) + 0x188) = *puVar3;
        MulMatrix__6MatrixCFRC6Matrix(auStack_160,*(int *)(*(int *)(iStack_10 + 0x20) + 0x30) + 0x160,auStack_50);
        uVar5 = __as__6MatrixFRC6Matrix
                          (*(int *)(*(int *)(iStack_10 + 0x20) + 0x30) + 0x160,auStack_160);
        uVar5 = GetPos__6MatrixFv(*(int *)(*(int *)(iStack_10 + 0x20) + 0x30) + 0x160,uVar5);
        __as__7FVectorFRC7FVector(uVar5,auStack_60);
        myMatrixUpdate__5FrameFv(*(undefined4 *)(*(int *)(iStack_10 + 0x20) + 0x30));
        SetTransform__7ExModelFR7FVectorR7FVectorR7FVector(*(undefined4 *)(iStack_10 + 0x24),iStack_10 + 0xa0,iStack_10 + 0xc0,
                        iStack_10 + 0xb0);
      }
      else {
        SetTransform__7ExModelFR7FVectorR7FVectorR7FVector(*(undefined4 *)(iStack_10 + 0x18),iStack_10 + 0xa0,iStack_10 + 0xc0,
                        iStack_10 + 0xb0);
        SetTransform__7ExModelFR7FVectorR7FVectorR7FVector(*(undefined4 *)(iStack_10 + 0x1c),iStack_10 + 0xa0,iStack_10 + 0xc0,
                        iStack_10 + 0xb0);
        SetTransform__7ExModelFR7FVectorR7FVectorR7FVector(*(undefined4 *)(iStack_10 + 0x20),iStack_10 + 0xa0,iStack_10 + 0xc0,
                        iStack_10 + 0xb0);
      }
      lVar4 = isPaused__6CPauseFv(*(undefined4 *)(app__4CApp + 0x78));
      if (lVar4 == 0) {
        (**(code **)(*(int *)(*(int *)(iStack_10 + 0x18) + 0x10) + 0x2c))(0x3d088880);
        if (((ulong)*(byte *)(iStack_10 + 0x91) & 0x1f) >> 3 == 2) {
          (**(code **)(*(int *)(*(int *)(iStack_10 + 0x1c) + 0x10) + 0x2c))(0x3d088880);
        }
        if (((ulong)*(byte *)(iStack_10 + 0x91) & 0x1f) >> 3 == 1) {
          (**(code **)(*(int *)(*(int *)(iStack_10 + 0x20) + 0x10) + 0x2c))(0x3d088880);
        }
        if (((ulong)*(ushort *)(iStack_10 + 0x90) & 0x1ff) >> 5 == 1) {
          (**(code **)(*(int *)(*(int *)(iStack_10 + 0x24) + 0x10) + 0x2c))(0x3d088880);
        }
        if (*(int *)(iStack_10 + 0x5c) != 0) {
          getWorldPos__5FrameFi(auStack_90,*(undefined4 *)(*(int *)(iStack_10 + 0x5c) + 0x30),
                          m_Env__8VIF1Prim & 1);
          lVar4 = CheckOnPoint__9WarpPointFR7FVector(iStack_10,auStack_90);
          if (lVar4 == 0) {
            *(float *)(iStack_10 + 0x54) = *(float *)(iStack_10 + 0x54) - 3.0;
            if (*(float *)(iStack_10 + 0x54) < 64.0) {
              *(undefined4 *)(iStack_10 + 0x54) = 0x42800000;
            }
          }
          else {
            *(float *)(iStack_10 + 0x54) = *(float *)(iStack_10 + 0x54) + 3.0;
            if (128.0 < *(float *)(iStack_10 + 0x54)) {
              *(undefined4 *)(iStack_10 + 0x54) = 0x43000000;
            }
          }
        }
        SetAlpha__9WarpPointFf(*(undefined4 *)(iStack_10 + 0x54),iStack_10);
      }
      (**(code **)(*(int *)(*(int *)(iStack_10 + 0x18) + 0x10) + 0x28))
                (*(int *)(iStack_10 + 0x18),0);
      uVar5 = (**(code **)(*(int *)(*(int *)(iStack_10 + 0x1c) + 0x10) + 0x28))
                        (*(int *)(iStack_10 + 0x1c),0);
      (**(code **)(*(int *)(*(int *)(iStack_10 + 0x20) + 0x10) + 0x28))
                (*(int *)(iStack_10 + 0x20),0,uVar5);
      if (((ulong)*(ushort *)(iStack_10 + 0x90) & 0x1ff) >> 5 == 1) {
        (**(code **)(*(int *)(*(int *)(iStack_10 + 0x24) + 0x10) + 0x28))
                  (*(int *)(iStack_10 + 0x24),0);
      }
    }
  }
  return 0;
}

/* JP: 0x00434b50  WarpPoint::CheckOnPoint(FVector&)   [CheckOnPoint__9WarpPointFR7FVector]  size=0x168 */
undefined4 CheckOnPoint__9WarpPointFR7FVector(int param_1,undefined4 param_2)

{
  float *pfVar1;
  float *pfVar2;
  undefined4 uVar3;
  float fVar4;
  float fVar5;
  undefined1 auStack_40 [28];
  float fStack_24;
  int iStack_20;
  undefined4 uStack_10;
  
  iStack_20 = param_1;
  uStack_10 = param_2;
  __mi__7FVectorCFRC7FVector(auStack_40,param_1 + 0xa0,param_2);
  pfVar1 = (float *)vy__7FVectorFv(auStack_40);
  if ((*pfVar1 < -5.0) || (pfVar1 = (float *)vy__7FVectorFv(auStack_40), 5.0 < *pfVar1)) {
    uVar3 = 0;
  }
  else {
    fStack_24 = 8.5;
    if (((ulong)*(ushort *)(iStack_20 + 0x90) & 0x1ff) >> 5 == 1) {
      fStack_24 = 28.0;
    }
    pfVar1 = (float *)vx__7FVectorFv(auStack_40);
    pfVar2 = (float *)vx__7FVectorFv(auStack_40);
    fVar4 = *pfVar1;
    fVar5 = *pfVar2;
    pfVar1 = (float *)vz__7FVectorFv(auStack_40);
    pfVar2 = (float *)vz__7FVectorFv(auStack_40);
    if (fStack_24 < SQRT(fVar4 * fVar5 + *pfVar1 * *pfVar2)) {
      uVar3 = 0;
    }
    else {
      uVar3 = 1;
    }
  }
  return uVar3;
}

/* JP: 0x00434cc0  WarpPoint::StartShowEffect()   [StartShowEffect__9WarpPointFv]  size=0x98 */
void StartShowEffect__9WarpPointFv(int param_1)

{
  AddDoubleOT__5WorldFiiP8VIF1Prim(0x42bf10,*(undefined4 *)(param_1 + 0x94),*(undefined4 *)(param_1 + 0x98),
                  *(undefined4 *)(param_1 + 0x18));
  setMotion__7ExModelFPCc(*(undefined4 *)(param_1 + 0x18),0x5556f8);
  SetAlpha__9WarpPointFf(0,param_1);
  *(undefined4 *)(param_1 + 0xd0) = 1;
  *(undefined4 *)(param_1 + 0xd4) = 0;
  *(undefined4 *)(param_1 + 0xd8) = 0;
  SetLight__9WarpPointFv(param_1);
  return;
}

/* JP: 0x00434d60  WarpPoint::StartHideEffect()   [StartHideEffect__9WarpPointFv]  size=0x38 */
void StartHideEffect__9WarpPointFv(int param_1)

{
  *(undefined4 *)(param_1 + 0xd0) = 3;
  *(undefined4 *)(param_1 + 0xd4) = 0;
  *(undefined4 *)(param_1 + 0xd8) = 0x3f800000;
  return;
}

/* JP: 0x00434da0  WarpPoint::SetAlpha(float)   [SetAlpha__9WarpPointFf]  size=0x90 */
void SetAlpha__9WarpPointFf(undefined4 param_1,int param_2)

{
  undefined1 auStack_30 [16];
  int iStack_20;
  undefined4 uStack_10;
  
  iStack_20 = param_2;
  uStack_10 = param_1;
  __ct__7FVectorFffff(0x43000000,0x43000000,0x43000000,param_1,auStack_30);
  setModelColor__5ModelFR7FVector(*(undefined4 *)(iStack_20 + 0x18),auStack_30);
  if (((ulong)*(ushort *)(iStack_20 + 0x90) & 0x1ff) >> 5 == 1) {
    setModelColor__5ModelFR7FVector(*(undefined4 *)(iStack_20 + 0x24),auStack_30);
  }
  return;
}

/* JP: 0x00434e30  WarpPoint::WarpIn(FVector&, FVector&, short, bool)   [WarpIn__9WarpPointFR7FVectorR7FVectorsb]  size=0x200 */
void WarpIn__9WarpPointFR7FVectorR7FVectorsb
               (int param_1,undefined4 param_2,undefined4 param_3,undefined2 param_4,
               undefined1 param_5)

{
  long lVar1;
  
  lVar1 = Find__7CPollerCFPC7CPolObj(app__4CApp + 0x60,param_1);
  if (lVar1 == 0) {
    Entry__7CPollerFP7CPolObjib(app__4CApp + 0x60,param_1,0x80,0);
  }
  if ((*(int *)(param_1 + 0x1c) == 0) || (*(int *)(param_1 + 0x20) == 0)) {
    *(byte *)(param_1 + 0x91) = *(byte *)(param_1 + 0x91) & 0xf9 | 2;
    __as__7FVectorFRC7FVector(param_1 + 0x60,param_2);
    __as__7FVectorFRC7FVector(param_1 + 0x70,param_3);
    *(undefined2 *)(param_1 + 0x80) = param_4;
    *(undefined1 *)(param_1 + 0x82) = param_5;
    ShowFader__9WarpPointFR7FVectorR7FVectorsb(param_1,param_2,param_3,param_4,param_5);
  }
  else {
    lVar1 = FindOT__5WorldFP8VIF1Prim(0x42bf10,*(undefined4 *)(param_1 + 0x20));
    if (lVar1 == 0) {
      ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,*(undefined4 *)(param_1 + 0x1c));
      AddDoubleOT__5WorldFiiP8VIF1Prim(0x42bf10,*(undefined4 *)(param_1 + 0x94),*(undefined4 *)(param_1 + 0x98),
                      *(undefined4 *)(param_1 + 0x20));
      setMotion__7ExModelFPCc(*(undefined4 *)(param_1 + 0x20),0x555700);
      (**(code **)(*(int *)(*(int *)(param_1 + 0x20) + 0x10) + 0x2c))(0);
      (**(code **)(*(int *)(*(int *)(param_1 + 0x20) + 0x10) + 0x28))(*(int *)(param_1 + 0x20),0);
      ShowFader__9WarpPointFR7FVectorR7FVectorsb(param_1,param_2,param_3,param_4,param_5);
      *(byte *)(param_1 + 0x91) = *(byte *)(param_1 + 0x91) & 0xe7 | 8;
    }
  }
  return;
}

/* JP: 0x00435030  WarpPoint::WarpOut(FVector&, FVector&, short, bool)   [WarpOut__9WarpPointFR7FVectorR7FVectorsb]  size=0x1e8 */
void WarpOut__9WarpPointFR7FVectorR7FVectorsb
               (int param_1,undefined4 param_2,undefined4 param_3,undefined2 param_4,
               undefined1 param_5)

{
  long lVar1;
  
  lVar1 = Find__7CPollerCFPC7CPolObj(app__4CApp + 0x60,param_1);
  if (lVar1 == 0) {
    Entry__7CPollerFP7CPolObjib(app__4CApp + 0x60,param_1,0x80,0);
  }
  if ((*(int *)(param_1 + 0x1c) == 0) || (*(int *)(param_1 + 0x20) == 0)) {
    *(byte *)(param_1 + 0x91) = *(byte *)(param_1 + 0x91) & 0xf9 | 4;
    __as__7FVectorFRC7FVector(param_1 + 0x60,param_2);
    __as__7FVectorFRC7FVector(param_1 + 0x70,param_3);
    *(undefined2 *)(param_1 + 0x80) = param_4;
    *(undefined1 *)(param_1 + 0x82) = param_5;
  }
  else {
    lVar1 = FindOT__5WorldFP8VIF1Prim(0x42bf10,*(undefined4 *)(param_1 + 0x1c));
    if (lVar1 == 0) {
      ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,*(undefined4 *)(param_1 + 0x20));
      AddDoubleOT__5WorldFiiP8VIF1Prim(0x42bf10,*(undefined4 *)(param_1 + 0x94),*(undefined4 *)(param_1 + 0x98),
                      *(undefined4 *)(param_1 + 0x1c));
      setMotion__7ExModelFPCc(*(undefined4 *)(param_1 + 0x1c),0x555708);
      (**(code **)(*(int *)(*(int *)(param_1 + 0x1c) + 0x10) + 0x2c))(0);
      (**(code **)(*(int *)(*(int *)(param_1 + 0x1c) + 0x10) + 0x28))(*(int *)(param_1 + 0x1c),0);
      ShowFader__9WarpPointFR7FVectorR7FVectorsb(param_1,param_2,param_3,param_4,param_5);
      *(byte *)(param_1 + 0x91) = *(byte *)(param_1 + 0x91) & 0xe7 | 0x10;
    }
  }
  return;
}

/* JP: 0x00435220  WarpPoint::ShowFader(FVector&, FVector&, short, bool)   [ShowFader__9WarpPointFR7FVectorR7FVectorsb]  size=0x300 */
void ShowFader__9WarpPointFR7FVectorR7FVectorsb
               (int param_1,undefined4 param_2,undefined4 param_3,short param_4,byte param_5)

{
  undefined4 uVar1;
  float *pfVar2;
  long lVar3;
  float fVar4;
  undefined1 auStack_90 [16];
  undefined1 auStack_80 [16];
  undefined1 auStack_70 [28];
  float fStack_54;
  int iStack_50;
  undefined4 uStack_40;
  undefined4 uStack_30;
  short sStack_20;
  byte bStack_10;
  
  if (param_4 != 0) {
    iStack_50 = param_1;
    uStack_40 = param_2;
    uStack_30 = param_3;
    sStack_20 = param_4;
    bStack_10 = param_5;
    if (*(int *)(param_1 + 0x28) != 0) {
      ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,*(undefined4 *)(param_1 + 0x28));
      (**(code **)(*(int *)(*(int *)(iStack_50 + 0x28) + 0x1c) + 0xc))();
      *(undefined4 *)(iStack_50 + 0x28) = 0;
    }
    *(byte *)(iStack_50 + 0x90) = *(byte *)(iStack_50 + 0x90) & 0xf7 | (bStack_10 & 1) << 3;
    *(byte *)(iStack_50 + 0x90) = *(byte *)(iStack_50 + 0x90) & 0xef;
    *(float *)(iStack_50 + 0x50) = ((float)(int)sStack_20 * 30.0) / 1000.0;
    fStack_54 = 1.0 / *(float *)(iStack_50 + 0x50);
    __as__7FVectorFRC7FVector(iStack_50 + 0x30,uStack_40);
    __ct__7FVectorFv(auStack_70);
    __ct__7FVectorFffff(0,0,0,0x3f800000,auStack_80);
    __ct__7FVectorFffff(0x44000000,0x43e00000,0,0x3f800000,auStack_90);
    lVar3 = __nw__FUi(0x90);
    uVar1 = 0;
    if (lVar3 != 0) {
      uVar1 = __ct__12EffectSpriteFP7FVectorP7FVectorP7FVectorP7FVectorP7FVectori(lVar3,auStack_80,auStack_90,iStack_50 + 0x30,auStack_70,auStack_70,0);
    }
    *(undefined4 *)(iStack_50 + 0x28) = uVar1;
    pfVar2 = (float *)vx__7FVectorFv(uStack_30);
    fVar4 = *pfVar2;
    pfVar2 = (float *)vx__7FVectorFv(uStack_40);
    fVar4 = fStack_54 * (fVar4 - *pfVar2);
    pfVar2 = (float *)vx__7FVectorFv(iStack_50 + 0x40);
    *pfVar2 = fVar4;
    pfVar2 = (float *)vy__7FVectorFv(uStack_30);
    fVar4 = *pfVar2;
    pfVar2 = (float *)vy__7FVectorFv(uStack_40);
    fVar4 = fStack_54 * (fVar4 - *pfVar2);
    pfVar2 = (float *)vy__7FVectorFv(iStack_50 + 0x40);
    *pfVar2 = fVar4;
    pfVar2 = (float *)vz__7FVectorFv(uStack_30);
    fVar4 = *pfVar2;
    pfVar2 = (float *)vz__7FVectorFv(uStack_40);
    fVar4 = fStack_54 * (fVar4 - *pfVar2);
    pfVar2 = (float *)vz__7FVectorFv(iStack_50 + 0x40);
    *pfVar2 = fVar4;
    pfVar2 = (float *)vw__7FVectorFv(uStack_30);
    fVar4 = *pfVar2;
    pfVar2 = (float *)vw__7FVectorFv(uStack_40);
    fVar4 = fStack_54 * (fVar4 - *pfVar2);
    pfVar2 = (float *)vw__7FVectorFv(iStack_50 + 0x40);
    *pfVar2 = fVar4;
    AddOT__5WorldFiP8VIF1Prim(0x42bf10,0xe,*(undefined4 *)(iStack_50 + 0x28));
  }
  return;
}

/* JP: 0x00435520  WarpPoint::SetLight()   [SetLight__9WarpPointFv]  size=0xec */
void SetLight__9WarpPointFv(int param_1)

{
  float *pfVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  undefined1 auStack_50 [16];
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [16];
  undefined1 auStack_20 [16];
  int iStack_10;
  
  if (*(int *)(param_1 + 0x58) == -1) {
    iStack_10 = param_1;
    __ct__7FVectorFffff(0,0,0x3f000000,0x43000000,auStack_20);
    __ct__7FVectorFRC7FVector(auStack_30,iStack_10 + 0xa0);
    pfVar1 = (float *)vy__7FVectorFv(auStack_30);
    *pfVar1 = *pfVar1 - 10.0;
    uVar3 = __ct__7FVectorFRC7FVector(auStack_40,auStack_30);
    uVar4 = __ct__7FVectorFRC7FVector(auStack_50,auStack_20);
    uVar2 = CreatePoint__12LightControlF7FVector7FVector(uVar3,uVar4);
    *(undefined4 *)(iStack_10 + 0x58) = uVar2;
    changeStrength__12LightControlFif(0x3f800000,*(undefined4 *)(iStack_10 + 0x58));
  }
  return;
}

/* JP: 0x004b7a80  WarpPoint::SetPos(FVector&)   [SetPos__9WarpPointFR7FVector]  size=0x34 */
void SetPos__9WarpPointFR7FVector(int param_1,undefined4 param_2)

{
  __as__7FVectorFRC7FVector(param_1 + 0xa0,param_2);
  return;
}

/* JP: 0x004b7e60  WarpPoint::SetCheckModel(Model*)   [SetCheckModel__9WarpPointFP5Model]  size=0x24 */
void SetCheckModel__9WarpPointFP5Model(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 0x5c) = param_2;
  return;
}

/* JP: 0x004b8610  WarpPoint::IsWarpEnded()   [IsWarpEnded__9WarpPointFv]  size=0x54 */
bool IsWarpEnded__9WarpPointFv(int param_1)

{
  return *(float *)(param_1 + 0x50) < 0.0;
}
