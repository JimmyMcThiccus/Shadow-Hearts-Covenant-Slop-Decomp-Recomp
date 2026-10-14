/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: solomonEffect   functions: 12
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/solomonEffect.md).
 */

/* JP: 0x004fe990  solomonEffect::DVD_CBFunc(int, BufMemory*, int, char*, void*)   [DVD_CBFunc__13solomonEffectFiP9BufMemoryiPcPv]  size=0x84 */
undefined8 DVD_CBFunc__13solomonEffectFiP9BufMemoryiPcPv(undefined8 param_1,int param_2)

{
  undefined4 uVar1;
  long lVar2;
  
  m_TexRead = 1;
  lVar2 = __nw__FUi(0x52c);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = __ct__7primTexFv(lVar2);
  }
  m_pPT = uVar1;
  initialize__7primTexFP9BufMemory(m_pPT,param_2);
  m_pBuffer = *(undefined4 *)(param_2 + 4);
  return 0;
}

/* JP: 0x004fea20  solomonEffect::solomonEffect()   [__ct__13solomonEffectFv]  size=0x94 */
int __ct__13solomonEffectFv(int param_1)

{
  __ct__7CPolObjFv(param_1);
  *(undefined4 *)(param_1 + 0x18) = 0;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  *(undefined1 **)(param_1 + 0x20) = &__vt__17DelayDeleteObject;
  *(undefined1 **)(param_1 + 0x14) = &__vt__13solomonEffect;
  *(undefined4 *)(param_1 + 0x20) = 0x4098c0;
  *(undefined4 *)(param_1 + 0x24) = 0;
  *(undefined4 *)(param_1 + 0x28) = 0;
  *(undefined1 *)(param_1 + 0x44) = 0;
  *(undefined1 *)(param_1 + 0x45) = 0;
  m_TexRead = 0;
  return param_1;
}

/* JP: 0x004feac0  solomonEffect::~solomonEffect()   [__dt__13solomonEffectFv]  size=0x128 */
int __dt__13solomonEffectFv(int param_1,short param_2)

{
  int iVar1;
  
  if (param_1 != 0) {
    *(undefined1 **)(param_1 + 0x14) = &__vt__13solomonEffect;
    *(undefined4 *)(param_1 + 0x20) = 0x4098c0;
    if (*(int *)(param_1 + 0x24) != 0) {
      iVar1 = *(int *)(param_1 + 0x24);
      if (iVar1 != 0) {
        (**(code **)(*(int *)(iVar1 + 0x10) + 8))(iVar1,1);
      }
      *(undefined4 *)(param_1 + 0x24) = 0;
    }
    Dispose__7CPollerFP7CPolObj(app__4CApp + 0x48,param_1);
    if (m_pPT != 0) {
      __dt__7primTexFv(m_pPT,1);
      m_pPT = 0;
    }
    if (param_1 != -0x18) {
      *(undefined1 **)(param_1 + 0x20) = &__vt__17DelayDeleteObject;
    }
    __dt__7CPolObjFv(param_1,0);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

/* JP: 0x004febf0  solomonEffect::DelayDeleteRequest()   [DelayDeleteRequest__13solomonEffectFv]  size=0x60 */
void DelayDeleteRequest__13solomonEffectFv(int param_1)

{
  if (*(int *)(param_1 + 0x24) != 0) {
    (**(code **)(*(int *)(*(int *)(param_1 + 0x24) + 0x10) + 0x40))();
  }
  (**(code **)(*(int *)(param_1 + 0x20) + 0xc))();
  return;
}

/* JP: 0x004fec50  solomonEffect::fadein()   [fadein__13solomonEffectFv]  size=0x34 */
void fadein__13solomonEffectFv(int param_1)

{
  *(undefined4 *)(param_1 + 0x34) = 5;
  *(undefined4 *)(param_1 + 0x4c) = 0x10;
  *(undefined4 *)(param_1 + 0x50) = 0;
  return;
}

/* JP: 0x004fec90  solomonEffect::fadeout()   [fadeout__13solomonEffectFv]  size=0x38 */
void fadeout__13solomonEffectFv(int param_1)

{
  *(undefined4 *)(param_1 + 0x34) = 6;
  *(undefined4 *)(param_1 + 0x4c) = 0x10;
  *(undefined4 *)(param_1 + 0x50) = 0x10;
  return;
}

/* JP: 0x004fecd0  solomonEffect::initialize(Matrix*)   [initialize__13solomonEffectFP6Matrix]  size=0x94 */
void initialize__13solomonEffectFP6Matrix(int param_1,undefined4 param_2)

{
  undefined8 uVar1;
  undefined1 auStack_120 [256];
  int iStack_20;
  undefined4 uStack_10;
  
  *(undefined4 *)(param_1 + 0x2c) = param_2;
  m_TexRead = 0;
  *(undefined4 *)(param_1 + 0x30) = 0;
  *(undefined4 *)(param_1 + 0x34) = 0;
  iStack_20 = param_1;
  uStack_10 = param_2;
  Entry__7CPollerFP7CPolObjib(app__4CApp + 0x48,param_1,0x80,0);
  uVar1 = SetPathname__7SysToolFPcPCc(auStack_120,0x55ee80);
  ReadOrder__11DvdromOrderFPCcPFiP9BufMemoryiPcPv_iiPvi(Dvdromour__11DvdromOrder,uVar1,0x4fe990,0,iStack_20,0);
  return;
}

/* JP: 0x004fed70  solomonEffect::start(bool)   [start__13solomonEffectFb]  size=0x5c */
void start__13solomonEffectFb(int param_1,char param_2)

{
  *(undefined1 *)(param_1 + 0x45) = 1;
  if (param_2 == '\0') {
    *(undefined4 *)(param_1 + 0x30) = 3;
  }
  else {
    *(undefined4 *)(param_1 + 0x30) = 1;
    *(undefined4 *)(param_1 + 0x34) = 0;
  }
  return;
}

/* JP: 0x004fedd0  solomonEffect::isFinish()   [isFinish__13solomonEffectFv]  size=0x1c */
undefined1 isFinish__13solomonEffectFv(int param_1)

{
  return *(undefined1 *)(param_1 + 0x44);
}

/* JP: 0x004fedf0  solomonEffect::isReady()   [isReady__13solomonEffectFv]  size=0x14 */
undefined1 isReady__13solomonEffectFv(void)

{
  return m_TexRead;
}

/* JP: 0x004fee10  solomonEffect::Polling()   [Polling__13solomonEffectFv]  size=0xbec */
undefined8 Polling__13solomonEffectFv(int param_1)

{
  undefined1 auVar1 [16];
  undefined4 uVar2;
  long lVar3;
  undefined8 uVar4;
  int iVar5;
  float fVar6;
  float fVar7;
  undefined1 in_vf0 [16];
  undefined1 auVar8 [16];
  undefined1 auVar9 [16];
  undefined1 auVar10 [16];
  
  GetActive__4CPadFi(0);
  iVar5 = *(int *)(param_1 + 0x30);
  if (iVar5 == 4) {
    fVar7 = **(float **)(param_1 + 0x2c);
    iVar5 = *(int *)(*(int *)(param_1 + 0x24) + 0x30);
    auVar8 = _vmr32(in_vf0);
    auVar9 = _vmr32(auVar8);
    auVar10 = _vmr32(auVar9);
    auVar1 = _sqc2(in_vf0);
    *(undefined1 (*) [16])(iVar5 + 400) = auVar1;
    auVar1 = _sqc2(auVar8);
    *(undefined1 (*) [16])(iVar5 + 0x180) = auVar1;
    auVar1 = _sqc2(auVar9);
    *(undefined1 (*) [16])(iVar5 + 0x170) = auVar1;
    auVar1 = _sqc2(auVar10);
    *(undefined1 (*) [16])(iVar5 + 0x160) = auVar1;
    *(float *)(*(int *)(*(int *)(param_1 + 0x24) + 0x30) + 0x160) = fVar7;
    *(float *)(*(int *)(*(int *)(param_1 + 0x24) + 0x30) + 0x174) = fVar7;
    *(float *)(*(int *)(*(int *)(param_1 + 0x24) + 0x30) + 0x188) = fVar7;
    iVar5 = *(int *)(*(int *)(param_1 + 0x24) + 0x30) + 0x160;
    sceVu0RotMatrixX(0x3fc90fd8,iVar5,iVar5);
    fVar6 = *(float *)(*(int *)(param_1 + 0x2c) + 0x34);
    iVar5 = *(int *)(*(int *)(param_1 + 0x24) + 0x30);
    *(float *)(iVar5 + 400) =
         (((*(float *)(*(int *)(param_1 + 0x2c) + 0x30) + fVar7 * 512.0) - 160.0) - 96.0) / 13.7;
    *(float *)(iVar5 + 0x194) = (((fVar6 + fVar7 * 448.0) - 160.0) - 64.0) / 16.0;
    *(undefined4 *)(iVar5 + 0x198) = 0;
    *(undefined4 *)(iVar5 + 0x19c) = 0x3f800000;
    myMatrixUpdate__5FrameFv(*(undefined4 *)(*(int *)(param_1 + 0x24) + 0x30));
    calcMatrix__7ExModelFP6Matrix(*(undefined4 *)(param_1 + 0x24),0);
    addTime__5ModelFf(0x3c8b4396,*(undefined4 *)(param_1 + 0x24));
  }
  else if (iVar5 == 3) {
    if ((m_TexRead != '\0') && (*(char *)(param_1 + 0x45) != '\0')) {
      if (*(int *)(param_1 + 0x24) == 0) {
        lVar3 = __nw__FUi(0x510);
        uVar2 = 0;
        if (lVar3 != 0) {
          uVar2 = __ct__7ExModelFv(lVar3);
        }
        *(undefined4 *)(param_1 + 0x24) = uVar2;
        uVar4 = getData__7primTexFi(m_pPT,2);
        create__7ExModelFPUc(*(undefined4 *)(param_1 + 0x24),uVar4);
        AddDoubleOT__5WorldFiiP8VIF1Prim(0x42bf10,0xc,0xc,*(undefined4 *)(param_1 + 0x24));
        uVar4 = getData__7primTexFi(m_pPT,3);
        createMotion__5ModelFPUc(*(undefined4 *)(param_1 + 0x24),uVar4);
      }
      *(undefined4 *)(param_1 + 0x48) = 0x3f800000;
      iVar5 = *(int *)(*(int *)(param_1 + 0x24) + 0x30);
      auVar8 = _vmr32(in_vf0);
      auVar9 = _vmr32(auVar8);
      auVar10 = _vmr32(auVar9);
      auVar1 = _sqc2(in_vf0);
      *(undefined1 (*) [16])(iVar5 + 400) = auVar1;
      auVar1 = _sqc2(auVar8);
      *(undefined1 (*) [16])(iVar5 + 0x180) = auVar1;
      auVar1 = _sqc2(auVar9);
      *(undefined1 (*) [16])(iVar5 + 0x170) = auVar1;
      auVar1 = _sqc2(auVar10);
      *(undefined1 (*) [16])(iVar5 + 0x160) = auVar1;
      *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x24) + 0x30) + 0x160) =
           *(undefined4 *)(param_1 + 0x48);
      *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x24) + 0x30) + 0x174) =
           *(undefined4 *)(param_1 + 0x48);
      *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x24) + 0x30) + 0x188) =
           *(undefined4 *)(param_1 + 0x48);
      iVar5 = *(int *)(*(int *)(param_1 + 0x24) + 0x30) + 0x160;
      sceVu0RotMatrixX(0x3fc90fd8,iVar5,iVar5);
      iVar5 = *(int *)(*(int *)(param_1 + 0x24) + 0x30);
      *(undefined4 *)(iVar5 + 400) = 0x80000000;
      *(undefined4 *)(iVar5 + 0x194) = 0x80000000;
      *(undefined4 *)(iVar5 + 0x198) = 0;
      *(undefined4 *)(iVar5 + 0x19c) = 0x3f800000;
      myMatrixUpdate__5FrameFv(*(undefined4 *)(*(int *)(param_1 + 0x24) + 0x30));
      setMotion__7ExModelFPCc(*(undefined4 *)(param_1 + 0x24),0x55eea0);
      calcMatrix__7ExModelFP6Matrix(*(undefined4 *)(param_1 + 0x24),0);
      addTime__5ModelFf(0x3c8b4396,*(undefined4 *)(param_1 + 0x24));
      *(undefined4 *)(camera__4CApp + 0x380) = 0x3f800000;
      *(undefined4 *)(camera__4CApp + 900) = 0x447a0000;
      *(undefined4 *)(camera__4CApp + 0x360) = 0;
      *(undefined4 *)(camera__4CApp + 0x364) = *(undefined4 *)(camera__4CApp + 0x380);
      *(float *)(camera__4CApp + 0x368) =
           256.0 / (*(float *)(camera__4CApp + 900) - *(float *)(camera__4CApp + 0x380));
      *(undefined4 *)(camera__4CApp + 0x36c) = 0x437f0000;
      SetViewMatrix__9GsxCameraFfffff(0x44000000,0x3f4ccccd,0x3f6eeeef,0x3f800000,0x4b7fff28,camera__4CApp);
      auVar8 = _vmr32(in_vf0);
      auVar9 = _vmr32(auVar8);
      auVar10 = _vmr32(auVar9);
      auVar1 = _sqc2(in_vf0);
      *(undefined1 (*) [16])(camera__4CApp + 0x270) = auVar1;
      auVar1 = _sqc2(auVar8);
      *(undefined1 (*) [16])(camera__4CApp + 0x260) = auVar1;
      auVar1 = _sqc2(auVar9);
      *(undefined1 (*) [16])(camera__4CApp + 0x250) = auVar1;
      auVar1 = _sqc2(auVar10);
      *(undefined1 (*) [16])(camera__4CApp + 0x240) = auVar1;
      *(undefined4 *)(camera__4CApp + 0x270) = 0;
      *(undefined4 *)(camera__4CApp + 0x274) = 0;
      *(undefined4 *)(camera__4CApp + 0x278) = 0xc1f00000;
      *(undefined4 *)(camera__4CApp + 0x27c) = 0x3f800000;
      ApplyFrame__9GsxCameraFv(camera__4CApp);
      *(undefined4 *)(param_1 + 0x30) = 4;
      *(undefined4 *)(param_1 + 0x38) = 0;
    }
  }
  else if (iVar5 == 2) {
    calcMatrix__7ExModelFP6Matrix(*(undefined4 *)(param_1 + 0x24),0);
    addTime__5ModelFf(0x3c8b4396,*(undefined4 *)(param_1 + 0x24));
    *(int *)(param_1 + 0x38) = *(int *)(param_1 + 0x38) + 1;
    if (*(int *)(param_1 + 0x38) == 0xf0) {
      *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x24);
      (**(code **)(*(int *)(*(int *)(param_1 + 0x28) + 0x10) + 0x40))();
      lVar3 = __nw__FUi(0x510);
      uVar2 = 0;
      if (lVar3 != 0) {
        uVar2 = __ct__7ExModelFv(lVar3);
      }
      *(undefined4 *)(param_1 + 0x24) = uVar2;
      uVar4 = getData__7primTexFi(m_pPT,2);
      create__7ExModelFPUc(*(undefined4 *)(param_1 + 0x24),uVar4);
      AddDoubleOT__5WorldFiiP8VIF1Prim(0x42bf10,0xc,0xc,*(undefined4 *)(param_1 + 0x24));
      uVar4 = getData__7primTexFi(m_pPT,3);
      createMotion__5ModelFPUc(*(undefined4 *)(param_1 + 0x24),uVar4);
      *(undefined4 *)(param_1 + 0x48) = 0x3f800000;
      iVar5 = *(int *)(*(int *)(param_1 + 0x24) + 0x30);
      auVar8 = _vmr32(in_vf0);
      auVar9 = _vmr32(auVar8);
      auVar10 = _vmr32(auVar9);
      auVar1 = _sqc2(in_vf0);
      *(undefined1 (*) [16])(iVar5 + 400) = auVar1;
      auVar1 = _sqc2(auVar8);
      *(undefined1 (*) [16])(iVar5 + 0x180) = auVar1;
      auVar1 = _sqc2(auVar9);
      *(undefined1 (*) [16])(iVar5 + 0x170) = auVar1;
      auVar1 = _sqc2(auVar10);
      *(undefined1 (*) [16])(iVar5 + 0x160) = auVar1;
      *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x24) + 0x30) + 0x160) =
           *(undefined4 *)(param_1 + 0x48);
      *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x24) + 0x30) + 0x174) =
           *(undefined4 *)(param_1 + 0x48);
      *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x24) + 0x30) + 0x188) =
           *(undefined4 *)(param_1 + 0x48);
      iVar5 = *(int *)(*(int *)(param_1 + 0x24) + 0x30) + 0x160;
      sceVu0RotMatrixX(0x3fc90fd8,iVar5,iVar5);
      iVar5 = *(int *)(*(int *)(param_1 + 0x24) + 0x30);
      *(undefined4 *)(iVar5 + 400) = 0x80000000;
      *(undefined4 *)(iVar5 + 0x194) = 0x80000000;
      *(undefined4 *)(iVar5 + 0x198) = 0;
      *(undefined4 *)(iVar5 + 0x19c) = 0x3f800000;
      myMatrixUpdate__5FrameFv(*(undefined4 *)(*(int *)(param_1 + 0x24) + 0x30));
      setMotion__7ExModelFPCc(*(undefined4 *)(param_1 + 0x24),0x55eea0);
      calcMatrix__7ExModelFP6Matrix(*(undefined4 *)(param_1 + 0x24),0);
      addTime__5ModelFf(0x3c8b4396,*(undefined4 *)(param_1 + 0x24));
    }
    if (*(int *)(param_1 + 0x38) == 400) {
      if (*(int *)(param_1 + 0x28) != 0) {
        iVar5 = *(int *)(param_1 + 0x28);
        if (iVar5 != 0) {
          (**(code **)(*(int *)(iVar5 + 0x10) + 8))(iVar5,1);
        }
        *(undefined4 *)(param_1 + 0x28) = 0;
      }
      *(undefined1 *)(param_1 + 0x44) = 1;
    }
  }
  else if (((iVar5 == 1) && (m_TexRead != '\0')) && (*(char *)(param_1 + 0x45) != '\0')) {
    if (*(int *)(param_1 + 0x24) == 0) {
      lVar3 = __nw__FUi(0x510);
      uVar2 = 0;
      if (lVar3 != 0) {
        uVar2 = __ct__7ExModelFv(lVar3);
      }
      *(undefined4 *)(param_1 + 0x24) = uVar2;
      uVar4 = getData__7primTexFi(m_pPT,0);
      create__7ExModelFPUc(*(undefined4 *)(param_1 + 0x24),uVar4);
      AddDoubleOT__5WorldFiiP8VIF1Prim(0x42bf10,0xc,0xc,*(undefined4 *)(param_1 + 0x24));
      uVar4 = getData__7primTexFi(m_pPT,1);
      createMotion__5ModelFPUc(*(undefined4 *)(param_1 + 0x24),uVar4);
    }
    *(undefined4 *)(param_1 + 0x48) = 0x3f800000;
    iVar5 = *(int *)(*(int *)(param_1 + 0x24) + 0x30);
    auVar8 = _vmr32(in_vf0);
    auVar9 = _vmr32(auVar8);
    auVar10 = _vmr32(auVar9);
    auVar1 = _sqc2(in_vf0);
    *(undefined1 (*) [16])(iVar5 + 400) = auVar1;
    auVar1 = _sqc2(auVar8);
    *(undefined1 (*) [16])(iVar5 + 0x180) = auVar1;
    auVar1 = _sqc2(auVar9);
    *(undefined1 (*) [16])(iVar5 + 0x170) = auVar1;
    auVar1 = _sqc2(auVar10);
    *(undefined1 (*) [16])(iVar5 + 0x160) = auVar1;
    *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x24) + 0x30) + 0x160) =
         *(undefined4 *)(param_1 + 0x48);
    *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x24) + 0x30) + 0x174) =
         *(undefined4 *)(param_1 + 0x48);
    *(undefined4 *)(*(int *)(*(int *)(param_1 + 0x24) + 0x30) + 0x188) =
         *(undefined4 *)(param_1 + 0x48);
    iVar5 = *(int *)(*(int *)(param_1 + 0x24) + 0x30) + 0x160;
    sceVu0RotMatrixX(0x3fc90fd8,iVar5,iVar5);
    iVar5 = *(int *)(*(int *)(param_1 + 0x24) + 0x30);
    *(undefined4 *)(iVar5 + 400) = 0x80000000;
    *(undefined4 *)(iVar5 + 0x194) = 0x80000000;
    *(undefined4 *)(iVar5 + 0x198) = 0;
    *(undefined4 *)(iVar5 + 0x19c) = 0x3f800000;
    myMatrixUpdate__5FrameFv(*(undefined4 *)(*(int *)(param_1 + 0x24) + 0x30));
    setMotion__7ExModelFPCc(*(undefined4 *)(param_1 + 0x24),0x55ee98);
    calcMatrix__7ExModelFP6Matrix(*(undefined4 *)(param_1 + 0x24),0);
    addTime__5ModelFf(0x3c8b4396,*(undefined4 *)(param_1 + 0x24));
    *(undefined4 *)(camera__4CApp + 0x380) = 0x3f800000;
    *(undefined4 *)(camera__4CApp + 900) = 0x447a0000;
    *(undefined4 *)(camera__4CApp + 0x360) = 0;
    *(undefined4 *)(camera__4CApp + 0x364) = *(undefined4 *)(camera__4CApp + 0x380);
    *(float *)(camera__4CApp + 0x368) =
         256.0 / (*(float *)(camera__4CApp + 900) - *(float *)(camera__4CApp + 0x380));
    *(undefined4 *)(camera__4CApp + 0x36c) = 0x437f0000;
    SetViewMatrix__9GsxCameraFfffff(0x44000000,0x3f4ccccd,0x3f6eeeef,0x3f800000,0x4b7fff28,camera__4CApp);
    auVar8 = _vmr32(in_vf0);
    auVar9 = _vmr32(auVar8);
    auVar10 = _vmr32(auVar9);
    auVar1 = _sqc2(in_vf0);
    *(undefined1 (*) [16])(camera__4CApp + 0x270) = auVar1;
    auVar1 = _sqc2(auVar8);
    *(undefined1 (*) [16])(camera__4CApp + 0x260) = auVar1;
    auVar1 = _sqc2(auVar9);
    *(undefined1 (*) [16])(camera__4CApp + 0x250) = auVar1;
    auVar1 = _sqc2(auVar10);
    *(undefined1 (*) [16])(camera__4CApp + 0x240) = auVar1;
    *(undefined4 *)(camera__4CApp + 0x270) = 0;
    *(undefined4 *)(camera__4CApp + 0x274) = 0;
    *(undefined4 *)(camera__4CApp + 0x278) = 0xc1f00000;
    *(undefined4 *)(camera__4CApp + 0x27c) = 0x3f800000;
    ApplyFrame__9GsxCameraFv(camera__4CApp);
    *(undefined4 *)(param_1 + 0x30) = 2;
    *(undefined4 *)(param_1 + 0x38) = 0;
  }
  if (*(int *)(param_1 + 0x24) != 0) {
    if (*(int *)(param_1 + 0x34) == 6) {
      *(int *)(param_1 + 0x50) = *(int *)(param_1 + 0x50) + -1;
      *(float *)(*(int *)(param_1 + 0x24) + 0x4f0) =
           (float)*(int *)(param_1 + 0x50) / (float)*(int *)(param_1 + 0x4c);
      if (*(int *)(param_1 + 0x50) == 0) {
        *(undefined4 *)(param_1 + 0x34) = 0;
      }
    }
    else if (*(int *)(param_1 + 0x34) == 5) {
      *(int *)(param_1 + 0x50) = *(int *)(param_1 + 0x50) + 1;
      *(float *)(*(int *)(param_1 + 0x24) + 0x4f0) =
           (float)*(int *)(param_1 + 0x50) / (float)*(int *)(param_1 + 0x4c);
      if (*(int *)(param_1 + 0x50) == *(int *)(param_1 + 0x4c)) {
        *(undefined4 *)(param_1 + 0x34) = 0;
      }
    }
  }
  return 0;
}

/* JP: 0x00506bd0  solomonEffect::~solomonEffect()   [@24@__dt__13solomonEffectFv]  size=0x8 */
int _24___dt__13solomonEffectFv(int param_1,short param_2)

{
  int iVar1;
  int iVar2;
  
  iVar2 = param_1 + -0x18;
  if (iVar2 != 0) {
    *(undefined1 **)(param_1 + -4) = &__vt__13solomonEffect;
    *(undefined4 *)(param_1 + 8) = 0x4098c0;
    if (*(int *)(param_1 + 0xc) != 0) {
      iVar1 = *(int *)(param_1 + 0xc);
      if (iVar1 != 0) {
        (**(code **)(*(int *)(iVar1 + 0x10) + 8))(iVar1,1);
      }
      *(undefined4 *)(param_1 + 0xc) = 0;
    }
    Dispose__7CPollerFP7CPolObj(app__4CApp + 0x48,iVar2);
    if (m_pPT != 0) {
      __dt__7primTexFv(m_pPT,1);
      m_pPT = 0;
    }
    if (iVar2 != -0x18) {
      *(undefined1 **)(param_1 + 8) = &__vt__17DelayDeleteObject;
    }
    __dt__7CPolObjFv(iVar2,0);
    if (0 < param_2) {
      __dl__FPv(iVar2);
    }
  }
  return iVar2;
}
