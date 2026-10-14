/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: SavePoint   functions: 14
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/SavePoint.md).
 */

/* JP: 0x00430b80  SavePoint::SavePoint()   [__ct__9SavePointFv]  size=0xb0 */
int __ct__9SavePointFv(int param_1)

{
  __ct__7CPolObjFv(param_1);
  *(undefined1 **)(param_1 + 0x14) = &__vt__9SavePoint;
  __ct__8SvpLightFv(param_1 + 0x30);
  __ct__7FVectorFv(param_1 + 0xb0);
  Init__Q29SavePoint18_class_2151SVP_cppFv(param_1 + 0x94);
  *(undefined4 *)(param_1 + 0x98) = 0;
  *(undefined4 *)(param_1 + 0x9c) = 0;
  *(undefined4 *)(param_1 + 0x20) = 0;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  *(undefined4 *)(param_1 + 0x18) = 0;
  *(undefined4 *)(param_1 + 0x24) = 0;
  *(undefined4 *)(param_1 + 0x90) = 0;
  *(int *)(param_1 + 0x80) = param_1;
  return param_1;
}

/* JP: 0x00430c70  SavePoint::~SavePoint()   [__dt__9SavePointFv]  size=0x208 */
int __dt__9SavePointFv(int param_1,short param_2)

{
  int iVar1;
  
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 0x14) = &__vt__9SavePoint;
    m_SvpRefer__9SavePoint = m_SvpRefer__9SavePoint + -1;
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
    if ((m_Buffer__9SavePoint != 0) && (m_SvpRefer__9SavePoint == 0)) {
      Reserve__7DeleterFP9BufMemory(m_Buffer__9SavePoint);
      m_Buffer__9SavePoint = 0;
    }
    if ((*(int *)(param_1 + 0x90) != 0) &&
       (Hide__9AnimLightFv(*(undefined4 *)(param_1 + 0x90)), *(int *)(param_1 + 0x90) != 0)) {
      iVar1 = *(int *)(param_1 + 0x90);
      if (iVar1 != 0) {
        (**(code **)(*(int *)(iVar1 + 0x14) + 8))(iVar1,1);
      }
      *(undefined4 *)(param_1 + 0x90) = 0;
    }
    Dispose__7CPollerFP7CPolObj(app__4CApp + 0x60,param_1);
    __dt__8SvpLightFv(param_1 + 0x30,0xffffffffffffffff);
    __dt__7CPolObjFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x00430e80  SavePoint::Create()   [Create__9SavePointFv]  size=0xa8 */
void Create__9SavePointFv(int param_1)

{
  undefined1 auStack_90 [128];
  int iStack_10;
  
  iStack_10 = param_1;
  if (m_Buffer__9SavePoint == 0) {
    *(byte *)(param_1 + 0x94) = *(byte *)(param_1 + 0x94) & 0xfe;
    SetPathname__7SysToolFPcPCc(auStack_90,0x555600);
    ReadOrder__11DvdromOrderFPCcPFiP9BufMemoryiPcPv_iiPvi(Dvdromour__11DvdromOrder,auStack_90,0x430a80,0,iStack_10,0);
  }
  else {
    cbSvpCallback__FiP9BufMemoryiPcPv(0,m_Buffer__9SavePoint,0,0,param_1);
  }
  return;
}

/* JP: 0x00430f30  SavePoint::CreateDirect(BufMemory*)   [CreateDirect__9SavePointFP9BufMemory]  size=0x394 */
void CreateDirect__9SavePointFP9BufMemory(int param_1,int param_2)

{
  undefined4 uVar1;
  undefined8 uVar2;
  long lVar3;
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [16];
  int iStack_20;
  int iStack_10;
  
  iStack_20 = param_1;
  iStack_10 = param_2;
  __ct__7FVectorFv(auStack_30);
  __ct__7FVectorFffff(0x3f4ccccd,0x3f4ccccd,0x3f4ccccd,0x3f800000,auStack_40);
  Origin__7FVectorFv(auStack_30);
  uVar2 = getBuffer__9BufMemoryFv(iStack_10);
  uVar2 = GetFileEntry(uVar2,0);
  lVar3 = __nw__FUi(0x510);
  uVar1 = 0;
  if (lVar3 != 0) {
    uVar1 = __ct__7ExModelFPUc(lVar3,uVar2);
  }
  *(undefined4 *)(iStack_20 + 0x18) = uVar1;
  uVar2 = getBuffer__9BufMemoryFv(iStack_10);
  uVar2 = GetFileEntry(uVar2,1);
  createMotion__5ModelFPUc(*(undefined4 *)(iStack_20 + 0x18),uVar2);
  (**(code **)(*(int *)(*(int *)(iStack_20 + 0x18) + 0x10) + 0x28))(*(int *)(iStack_20 + 0x18),0);
  SetTransform__7ExModelFR7FVectorR7FVectorR7FVector(*(undefined4 *)(iStack_20 + 0x18),iStack_20 + 0xb0,auStack_30,auStack_40);
  uVar2 = getBuffer__9BufMemoryFv(iStack_10);
  uVar2 = GetFileEntry(uVar2,2);
  lVar3 = __nw__FUi(0x510);
  uVar1 = 0;
  if (lVar3 != 0) {
    uVar1 = __ct__7ExModelFPUc(lVar3,uVar2);
  }
  *(undefined4 *)(iStack_20 + 0x1c) = uVar1;
  uVar2 = getBuffer__9BufMemoryFv(iStack_10);
  uVar2 = GetFileEntry(uVar2,3);
  SetTransform__7ExModelFR7FVectorR7FVectorR7FVector(*(undefined4 *)(iStack_20 + 0x1c),iStack_20 + 0xb0,auStack_30,auStack_40);
  createMotion__5ModelFPUc(*(undefined4 *)(iStack_20 + 0x1c),uVar2);
  (**(code **)(*(int *)(*(int *)(iStack_20 + 0x1c) + 0x10) + 0x28))(*(int *)(iStack_20 + 0x1c),0);
  uVar2 = getBuffer__9BufMemoryFv(iStack_10);
  uVar2 = GetFileEntry(uVar2,4);
  lVar3 = __nw__FUi(0x510);
  uVar1 = 0;
  if (lVar3 != 0) {
    uVar1 = __ct__7ExModelFPUc(lVar3,uVar2);
  }
  *(undefined4 *)(iStack_20 + 0x20) = uVar1;
  uVar2 = getBuffer__9BufMemoryFv(iStack_10);
  uVar2 = GetFileEntry(uVar2,5);
  SetTransform__7ExModelFR7FVectorR7FVectorR7FVector(*(undefined4 *)(iStack_20 + 0x20),iStack_20 + 0xb0,auStack_30,auStack_40);
  createMotion__5ModelFPUc(*(undefined4 *)(iStack_20 + 0x20),uVar2);
  (**(code **)(*(int *)(*(int *)(iStack_20 + 0x20) + 0x10) + 0x28))(*(int *)(iStack_20 + 0x20),0);
  uVar2 = getBuffer__9BufMemoryFv(iStack_10);
  uVar2 = GetFileEntry(uVar2,6);
  createMotion__5ModelFPUc(*(undefined4 *)(iStack_20 + 0x20),uVar2);
  (**(code **)(*(int *)(*(int *)(iStack_20 + 0x20) + 0x10) + 0x28))(*(int *)(iStack_20 + 0x20),0);
  *(byte *)(iStack_20 + 0x94) = *(byte *)(iStack_20 + 0x94) & 0xfe | 1;
  m_SvpRefer__9SavePoint = m_SvpRefer__9SavePoint + 1;
  if (m_Buffer__9SavePoint == 0) {
    m_Buffer__9SavePoint = iStack_10;
  }
  Entry__7CPollerFP7CPolObjib(app__4CApp + 0x60,iStack_20,0x80,0);
  return;
}

/* JP: 0x00431440  SavePoint::Show(int, int)   [Show__9SavePointFii]  size=0x110 */
void Show__9SavePointFii(int param_1,undefined4 param_2,undefined4 param_3)

{
  if (-1 < (long)((ulong)*(byte *)(param_1 + 0x94) << 0x3e)) {
    *(undefined4 *)(param_1 + 0xa0) = param_2;
    *(undefined4 *)(param_1 + 0xa4) = param_3;
    *(byte *)(param_1 + 0x94) = *(byte *)(param_1 + 0x94) & 0xfd | 2;
    if ((*(byte *)(param_1 + 0x94) & 1) == 0) {
      *(byte *)(param_1 + 0x94) = *(byte *)(param_1 + 0x94) & 0xfb | 4;
    }
    else {
      AddDoubleOT__5WorldFiiP8VIF1Prim(0x42bf10,*(undefined4 *)(param_1 + 0xa0),*(undefined4 *)(param_1 + 0xa4),
                      *(undefined4 *)(param_1 + 0x18));
      setMotion__7ExModelFPCc(*(undefined4 *)(param_1 + 0x18),0x555610);
      Show__9AnimLightFv(param_1 + 0x30);
    }
  }
  return;
}

/* JP: 0x00431550  SavePoint::Hide()   [Hide__9SavePointFv]  size=0x15c */
void Hide__9SavePointFv(int param_1)

{
  int iVar1;
  
  *(byte *)(param_1 + 0x94) = *(byte *)(param_1 + 0x94) & 0xfd;
  *(byte *)(param_1 + 0x94) = *(byte *)(param_1 + 0x94) & 0xfb;
  *(undefined4 *)(param_1 + 0x98) = 0;
  *(undefined4 *)(param_1 + 0x9c) = 0;
  if (*(int *)(param_1 + 0x18) != 0) {
    ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,*(undefined4 *)(param_1 + 0x18));
  }
  if (*(int *)(param_1 + 0x20) != 0) {
    ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,*(undefined4 *)(param_1 + 0x20));
  }
  if (*(int *)(param_1 + 0x1c) != 0) {
    ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,*(undefined4 *)(param_1 + 0x1c));
  }
  Hide__9AnimLightFv(param_1 + 0x30);
  if ((*(int *)(param_1 + 0x90) != 0) &&
     (Hide__9AnimLightFv(*(undefined4 *)(param_1 + 0x90)), *(int *)(param_1 + 0x90) != 0)) {
    iVar1 = *(int *)(param_1 + 0x90);
    if (iVar1 != 0) {
      (**(code **)(*(int *)(iVar1 + 0x14) + 8))(iVar1,1);
    }
    *(undefined4 *)(param_1 + 0x90) = 0;
  }
  return;
}

/* JP: 0x004316b0  SavePoint::cbOff_1()   [cbOff_1__9SavePointFv]  size=0x34 */
void cbOff_1__9SavePointFv(int param_1)

{
  ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,*(undefined4 *)(param_1 + 0x1c));
  return;
}

/* JP: 0x004316f0  SavePoint::cbOff_2()   [cbOff_2__9SavePointFv]  size=0x120 */
void cbOff_2__9SavePointFv(int param_1)

{
  int iVar1;
  long lVar2;
  
  iVar1 = *(int *)(param_1 + 0x9c);
  if (iVar1 == 3) {
    *(undefined4 *)(param_1 + 0x9c) = 0;
    lVar2 = FindOT__5WorldFP8VIF1Prim(0x42bf10,*(undefined4 *)(param_1 + 0x20));
    if (lVar2 != 0) {
      ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,*(undefined4 *)(param_1 + 0x20));
    }
  }
  else if (iVar1 == 2) {
    *(undefined4 *)(param_1 + 0x9c) = 3;
    setMotion__7ExModelFPCc(*(undefined4 *)(param_1 + 0x20),0x555620);
    (**(code **)(*(int *)(*(int *)(param_1 + 0x20) + 0x10) + 0x28))(*(int *)(param_1 + 0x20),0);
  }
  else if (iVar1 == 1) {
    *(undefined4 *)(param_1 + 0x9c) = 0;
    setMotion__7ExModelFPCc(*(undefined4 *)(param_1 + 0x20),0x555618);
    (**(code **)(*(int *)(*(int *)(param_1 + 0x20) + 0x10) + 0x28))(*(int *)(param_1 + 0x20),0);
  }
  return;
}

/* JP: 0x00431810  SavePoint::cbOn()   [cbOn__9SavePointFv]  size=0x40 */
void cbOn__9SavePointFv(int param_1)

{
  *(undefined4 *)(param_1 + 0x98) = 2;
  ReleaseOT__5WorldFP8VIF1Prim(0x42bf10,*(undefined4 *)(param_1 + 0x1c));
  return;
}

/* JP: 0x00431850  SavePoint::Polling()   [Polling__9SavePointFv]  size=0x740 */
undefined8 Polling__9SavePointFv(int param_1)

{
  int iVar1;
  float *pfVar2;
  undefined4 uVar3;
  long lVar4;
  undefined8 uVar5;
  undefined1 auStack_40 [16];
  undefined1 auStack_30 [16];
  undefined1 auStack_20 [16];
  int iStack_10;
  
  if (((long)((ulong)*(byte *)(param_1 + 0x94) << 0x3e) < 0) &&
     ((*(byte *)(param_1 + 0x94) & 1) != 0)) {
    iStack_10 = param_1;
    if ((long)((ulong)*(byte *)(param_1 + 0x94) << 0x3d) < 0) {
      AddDoubleOT__5WorldFiiP8VIF1Prim(0x42bf10,*(undefined4 *)(param_1 + 0xa0),*(undefined4 *)(param_1 + 0xa4),
                      *(undefined4 *)(param_1 + 0x18));
      setMotion__7ExModelFPCc(*(undefined4 *)(iStack_10 + 0x18),0x555610);
      Show__9AnimLightFv(iStack_10 + 0x30);
      *(byte *)(iStack_10 + 0x94) = *(byte *)(iStack_10 + 0x94) & 0xfb;
    }
    if (*(int *)(iStack_10 + 0x24) != 0) {
      getWorldPos__5FrameFi(auStack_20,*(undefined4 *)(*(int *)(iStack_10 + 0x24) + 0x30),m_Env__8VIF1Prim & 1)
      ;
      lVar4 = CheckOnPoint__9SavePointFR7FVector(iStack_10,auStack_20);
      if (lVar4 == 0) {
        if (*(int *)(iStack_10 + 0x98) == 2) {
          *(undefined4 *)(iStack_10 + 0x98) = 0;
          *(undefined4 *)(iStack_10 + 0x9c) = 2;
          setMotionEndCallBack2__5ModelFPFPcPv_vfPv(0x3727c5ac,*(undefined4 *)(iStack_10 + 0x20),0x430b40,iStack_10);
        }
        else if (*(int *)(iStack_10 + 0x98) == 1) {
          *(undefined4 *)(iStack_10 + 0x98) = 0;
          setMotionEndCallBack2__5ModelFPFPcPv_vfPv(0x3727c5ac,*(undefined4 *)(iStack_10 + 0x1c),0x430b00,iStack_10);
          *(undefined4 *)(iStack_10 + 0x9c) = 2;
        }
      }
      else {
        iVar1 = *(int *)(iStack_10 + 0x98);
        if (((iVar1 != 2) && (iVar1 != 1)) && (iVar1 == 0)) {
          lVar4 = FindOT__5WorldFP8VIF1Prim(0x42bf10,*(undefined4 *)(iStack_10 + 0x1c));
          if (lVar4 == 0) {
            *(undefined4 *)(iStack_10 + 0x98) = 1;
            AddDoubleOT__5WorldFiiP8VIF1Prim(0x42bf10,*(undefined4 *)(iStack_10 + 0xa0),
                            *(undefined4 *)(iStack_10 + 0xa4),*(undefined4 *)(iStack_10 + 0x1c));
            setMotion__7ExModelFPCc(*(undefined4 *)(iStack_10 + 0x1c),0x555628);
            (**(code **)(*(int *)(*(int *)(iStack_10 + 0x1c) + 0x10) + 0x28))
                      (*(int *)(iStack_10 + 0x1c),0);
            setMotionEndCallBack2__5ModelFPFPcPv_vfPv(0x3727c5ac,*(undefined4 *)(iStack_10 + 0x1c),0x430ac0,iStack_10);
            if ((*(int *)(iStack_10 + 0x90) != 0) &&
               (Hide__9AnimLightFv(*(undefined4 *)(iStack_10 + 0x90)), *(int *)(iStack_10 + 0x90) != 0)
               ) {
              iVar1 = *(int *)(iStack_10 + 0x90);
              if (iVar1 != 0) {
                (**(code **)(*(int *)(iVar1 + 0x14) + 8))(iVar1,1);
              }
              *(undefined4 *)(iStack_10 + 0x90) = 0;
            }
            __ct__7FVectorFffff(0x3f666666,0x3f666666,0x3f666666,0x3f800000,auStack_30);
            __ct__7FVectorFRC7FVector(auStack_40,iStack_10 + 0xb0);
            pfVar2 = (float *)vy__7FVectorFv(auStack_40);
            *pfVar2 = *pfVar2 - 5.0;
            lVar4 = __nw__FUi(0x60);
            uVar3 = 0;
            if (lVar4 != 0) {
              uVar3 = __ct__10DelayLightFR7FVectorR7FVector(lVar4,auStack_40,auStack_30);
            }
            *(undefined4 *)(iStack_10 + 0x90) = uVar3;
            Show__9AnimLightFv(*(undefined4 *)(iStack_10 + 0x90));
            SetAutoDelete__7CPolObjFb(*(undefined4 *)(iStack_10 + 0x90),0);
          }
          else {
            *(undefined4 *)(iStack_10 + 0x98) = 2;
          }
          lVar4 = FindOT__5WorldFP8VIF1Prim(0x42bf10,*(undefined4 *)(iStack_10 + 0x20));
          if (lVar4 == 0) {
            AddDoubleOT__5WorldFiiP8VIF1Prim(0x42bf10,*(undefined4 *)(iStack_10 + 0xa0),
                            *(undefined4 *)(iStack_10 + 0xa4),*(undefined4 *)(iStack_10 + 0x20));
            setMotion__7ExModelFPCc(*(undefined4 *)(iStack_10 + 0x20),0x555618);
            (**(code **)(*(int *)(*(int *)(iStack_10 + 0x20) + 0x10) + 0x28))
                      (*(int *)(iStack_10 + 0x20),0);
            setMotionEndCallBack2__5ModelFPFPcPv_vfPv(0x3727c5ac,*(undefined4 *)(iStack_10 + 0x20),0x430b40,iStack_10);
          }
          else if (*(int *)(iStack_10 + 0x9c) == 0) {
            setMotion__7ExModelFPCc(*(undefined4 *)(iStack_10 + 0x20),0x555618);
            (**(code **)(*(int *)(*(int *)(iStack_10 + 0x20) + 0x10) + 0x28))
                      (*(int *)(iStack_10 + 0x20),0);
            setMotionEndCallBack2__5ModelFPFPcPv_vfPv(0x3727c5ac,*(undefined4 *)(iStack_10 + 0x20),0x430b40,iStack_10);
          }
          else {
            *(undefined4 *)(iStack_10 + 0x9c) = 1;
          }
        }
      }
    }
    setMotionEndCallBack2__5ModelFPFPcPv_vfPv(0x3727c5ac,*(undefined4 *)(iStack_10 + 0x20),0x430b40,iStack_10);
    uVar5 = GetPos__6MatrixFv(*(int *)(*(int *)(iStack_10 + 0x18) + 0x30) + 0x160);
    __as__7FVectorFRC7FVector(uVar5,iStack_10 + 0xb0);
    uVar5 = GetPos__6MatrixFv(*(int *)(*(int *)(iStack_10 + 0x1c) + 0x30) + 0x160);
    __as__7FVectorFRC7FVector(uVar5,iStack_10 + 0xb0);
    uVar5 = GetPos__6MatrixFv(*(int *)(*(int *)(iStack_10 + 0x20) + 0x30) + 0x160);
    __as__7FVectorFRC7FVector(uVar5,iStack_10 + 0xb0);
    myMatrixUpdate__5FrameFv(*(undefined4 *)(*(int *)(iStack_10 + 0x18) + 0x30));
    myMatrixUpdate__5FrameFv(*(undefined4 *)(*(int *)(iStack_10 + 0x1c) + 0x30));
    myMatrixUpdate__5FrameFv(*(undefined4 *)(*(int *)(iStack_10 + 0x20) + 0x30));
    lVar4 = isPaused__6CPauseFv(*(undefined4 *)(app__4CApp + 0x78));
    if (lVar4 == 0) {
      (**(code **)(*(int *)(*(int *)(iStack_10 + 0x18) + 0x10) + 0x2c))(0x3d088880);
      (**(code **)(*(int *)(*(int *)(iStack_10 + 0x1c) + 0x10) + 0x2c))(0x3d088880);
      (**(code **)(*(int *)(*(int *)(iStack_10 + 0x20) + 0x10) + 0x2c))(0x3d088880);
    }
    (**(code **)(*(int *)(*(int *)(iStack_10 + 0x18) + 0x10) + 0x28))(*(int *)(iStack_10 + 0x18),0);
    (**(code **)(*(int *)(*(int *)(iStack_10 + 0x1c) + 0x10) + 0x28))(*(int *)(iStack_10 + 0x1c),0);
    (**(code **)(*(int *)(*(int *)(iStack_10 + 0x20) + 0x10) + 0x28))(*(int *)(iStack_10 + 0x20),0);
  }
  return 0;
}

/* JP: 0x00432030  SavePoint::CheckOnPoint(FVector&)   [CheckOnPoint__9SavePointFR7FVector]  size=0x130 */
undefined4 CheckOnPoint__9SavePointFR7FVector(int param_1,undefined4 param_2)

{
  float *pfVar1;
  float *pfVar2;
  undefined4 uVar3;
  float fVar4;
  float fVar5;
  undefined1 auStack_30 [16];
  int iStack_20;
  undefined4 uStack_10;
  
  iStack_20 = param_1;
  uStack_10 = param_2;
  __mi__7FVectorCFRC7FVector(auStack_30,param_1 + 0xb0,param_2);
  pfVar1 = (float *)vy__7FVectorFv(auStack_30);
  if ((*pfVar1 < -5.0) || (pfVar1 = (float *)vy__7FVectorFv(auStack_30), 5.0 < *pfVar1)) {
    uVar3 = 0;
  }
  else {
    pfVar1 = (float *)vx__7FVectorFv(auStack_30);
    pfVar2 = (float *)vx__7FVectorFv(auStack_30);
    fVar4 = *pfVar1;
    fVar5 = *pfVar2;
    pfVar1 = (float *)vz__7FVectorFv(auStack_30);
    pfVar2 = (float *)vz__7FVectorFv(auStack_30);
    if (8.5 < SQRT(fVar4 * fVar5 + *pfVar1 * *pfVar2)) {
      uVar3 = 0;
    }
    else {
      uVar3 = 1;
    }
  }
  return uVar3;
}

/* JP: 0x004321d0  SavePoint::SetPos(FVector&)   [SetPos__9SavePointFR7FVector]  size=0x34 */
void SetPos__9SavePointFR7FVector(int param_1,undefined4 param_2)

{
  __as__7FVectorFRC7FVector(param_1 + 0xb0,param_2);
  return;
}

/* JP: 0x004b71c0  SavePoint::SetCheckModel(Model*)   [SetCheckModel__9SavePointFP5Model]  size=0x24 */
void SetCheckModel__9SavePointFP5Model(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 0x24) = param_2;
  return;
}

/* JP: 0x004b7860  SavePoint::IsOn()   [IsOn__9SavePointFv]  size=0x44 */
bool IsOn__9SavePointFv(int param_1)

{
  return *(int *)(param_1 + 0x98) != 0;
}
