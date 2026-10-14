/*
 * VecHandlers.c -- Ghidra decompiler output (SLPM_602.19, JP Furokuban), tidied by tools/E_gen_decomp.py
 * 269 functions. Types: u8/u16/u32/u64 = undefined1/2/4/8. Addresses in comments are JP main-exe addresses.
 */

/* ---- 0x0030c480 size 0xc4  mdlCreate(iiPPcPv)
 *      mangled: mdlCreate__FiiPPcPv */
u64
mdlCreate__FiiPPcPv(u64 id,u64 argc,u32 *args,uint ctx)

{
  u32 *puVar1;
  int *piVar2;
  u32 *puVar3;
  VIF1Prim *prim;
  u64 uVar4;
  
  puVar1 = (u32 *)*args;
  piVar2 = (int *)args[1];
  puVar3 = (u32 *)args[2];
  uVar4 = GetCore__3VECFv(ctx);
  prim = (VIF1Prim *)CreateWorkModel__10EffectCoreFi(uVar4,*puVar1);
  prim[0x41].dwEnv = ctx;
  prim[0x48].dw_unk4 = (uint)_MotionEndCallback__FPvPCc;
  if (*piVar2 != 0) {
    AddDoubleOT__5WorldFiiP8VIF1Prim((World *)&m_World__4CApp,5,9,prim);
  }
  *puVar3 = prim;
  return 0;
}

/* ---- 0x0030c550 size 0xdc  mdlShow(iiPPcPv)
 *      mangled: mdlShow__FiiPPcPv */
u64
mdlShow__FiiPPcPv(u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 *puVar1;
  int *piVar2;
  VIF1Prim *prim;
  int iVar3;
  u64 uVar4;
  
  puVar1 = (u32 *)*args;
  piVar2 = (int *)args[1];
  uVar4 = GetCore__3VECFv(ctx);
  prim = (VIF1Prim *)FindWorkModel__10EffectCoreFUi(uVar4,*puVar1);
  if (*piVar2 == 0) {
    ReleaseOT__5WorldFP8VIF1Prim((World *)&m_World__4CApp,prim);
  }
  else {
    iVar3 = FindOT__5WorldFP8VIF1Prim((World *)&m_World__4CApp,prim);
    if (iVar3 == 0) {
      AddDoubleOT__5WorldFiiP8VIF1Prim((World *)&m_World__4CApp,5,9,prim);
    }
  }
  return 0;
}

/* ---- 0x0030c630 size 0xb8  mdlSetMotion(iiPPcPv)
 *      mangled: mdlSetMotion__FiiPPcPv */
u64
mdlSetMotion__FiiPPcPv(u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 *puVar1;
  u32 uVar2;
  u64 uVar3;
  
  puVar1 = (u32 *)*args;
  uVar2 = args[1];
  uVar3 = GetCore__3VECFv(ctx);
  uVar3 = FindWorkModel__10EffectCoreFUi(uVar3,*puVar1);
  setMotion__7ExModelFPCc(uVar3,uVar2);
  (**(code **)(*(int *)((int)uVar3 + 0x10) + 0x2c))(0);
  (**(code **)(*(int *)((int)uVar3 + 0x10) + 0x28))(uVar3,0);
  return 0;
}

/* ---- 0x0030c6f0 size 0xa8  mdlSetTrans(iiPPcPv)
 *      mangled: mdlSetTrans__FiiPPcPv */
u64
mdlSetTrans__FiiPPcPv(u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 uVar1;
  u32 *puVar2;
  u64 uVar3;
  
  puVar2 = (u32 *)*args;
  uVar1 = args[1];
  uVar3 = GetCore__3VECFv(ctx);
  uVar3 = FindWorkModel__10EffectCoreFUi(uVar3,*puVar2);
  puVar2 = (u32 *)vw__7FVectorFv(uVar1);
  *puVar2 = 0x3f800000;
  SetTrans__11EffectModelFP7FVector(uVar3,uVar1);
  return 0;
}

/* ---- 0x0030c7a0 size 0x108  mdlSetRot(iiPPcPv)
 *      mangled: mdlSetRot__FiiPPcPv */
u64
mdlSetRot__FiiPPcPv(u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 *puVar1;
  u64 uVar2;
  u32 uVar3;
  u32 uVar4;
  u32 uVar5;
  u8 auStack_50 [48];
  u32 *puStack_20;
  u32 uStack_10;
  
  puVar1 = (u32 *)*args;
  uVar5 = args[1];
  puStack_20 = args;
  uStack_10 = ctx;
  uVar2 = GetCore__3VECFv(ctx);
  uVar2 = FindWorkModel__10EffectCoreFUi(uVar2,*puVar1);
  puVar1 = (u32 *)vx__7FVectorFv(uVar5);
  uVar3 = GetRad(*puVar1);
  puVar1 = (u32 *)vy__7FVectorFv(uVar5);
  uVar4 = GetRad(*puVar1);
  puVar1 = (u32 *)vz__7FVectorFv(uVar5);
  uVar5 = GetRad(*puVar1);
  __ct__7FVectorFffff(uVar3,uVar4,uVar5,0x3f800000,auStack_50);
  SetRot__11EffectModelFP7FVector(uVar2,auStack_50);
  return 0;
}

/* ---- 0x0030c8b0 size 0x88  mdlSetScale(iiPPcPv)
 *      mangled: mdlSetScale__FiiPPcPv */
u64
mdlSetScale__FiiPPcPv(u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 *puVar1;
  u32 uVar2;
  u64 uVar3;
  
  puVar1 = (u32 *)*args;
  uVar2 = args[1];
  uVar3 = GetCore__3VECFv(ctx);
  uVar3 = FindWorkModel__10EffectCoreFUi(uVar3,*puVar1);
  SetScale__7ExModelFR7FVector(uVar3,uVar2);
  return 0;
}

/* ---- 0x0030c980 size 0x98  mdlDelete(iiPPcPv)
 *      mangled: mdlDelete__FiiPPcPv */
u64
mdlDelete__FiiPPcPv(u64 id,u64 argc,u32 *args,u32 ctx)

{
  u64 uVar1;
  u64 uVar2;
  
  args = (u32 *)*args;
  uVar1 = GetCore__3VECFv(ctx);
  uVar1 = FindWorkModel__10EffectCoreFUi(uVar1,*args);
  ReleaseOT__5WorldFP8VIF1Prim((World *)&m_World__4CApp,(VIF1Prim *)uVar1);
  uVar2 = GetCore__3VECFv(ctx);
  DeleteWorkModel__10EffectCoreFP5Model(uVar2,uVar1);
  return 0;
}

/* ---- 0x0030ca20 size 0x14c  mdlAttach(iiPPcPv)
 *      mangled: mdlAttach__FiiPPcPv */
u64
mdlAttach__FiiPPcPv(u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 *puVar1;
  int *piVar2;
  u32 *puVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  u32 uVar7;
  u64 uVar8;
  
  puVar1 = (u32 *)*args;
  piVar2 = (int *)args[1];
  puVar3 = (u32 *)args[2];
  uVar7 = args[3];
  uVar8 = GetCore__3VECFv(ctx);
  iVar5 = FindWorkModel__10EffectCoreFUi(uVar8,*puVar1);
  iVar6 = 0;
  iVar4 = *piVar2;
  if (iVar4 == 2) {
    uVar8 = GetCore__3VECFv(ctx);
    iVar6 = FindWorkModel__10EffectCoreFUi(uVar8,*puVar3);
  }
  else if ((iVar4 == 0) || (iVar4 == 1)) {
    uVar8 = GetCore__3VECFv(ctx);
    iVar6 = GetModel__10EffectCoreFiiii(uVar8,*piVar2,*puVar3,0,0);
  }
  uVar7 = searchFrame__5FrameFPCc(*(u32 *)(iVar6 + 0x30),uVar7);
  *(u32 *)(iVar5 + 0x518) = uVar7;
  return 0;
}

/* ---- 0x0030cb70 size 0x6c  mdlDetach(iiPPcPv)
 *      mangled: mdlDetach__FiiPPcPv */
u64
mdlDetach__FiiPPcPv(u64 id,u64 argc,u32 *args,u32 ctx)

{
  int iVar1;
  u64 uVar2;
  
  args = (u32 *)*args;
  uVar2 = GetCore__3VECFv(ctx);
  iVar1 = FindWorkModel__10EffectCoreFUi(uVar2,*args);
  *(u32 *)(iVar1 + 0x518) = 0;
  return 0;
}

/* ---- 0x0030cbe0 size 0x130  mdlAttach2(iiPPcPv)
 *      mangled: mdlAttach2__FiiPPcPv */
u64
mdlAttach2__FiiPPcPv(u64 id,u64 argc,u32 *args,u32 ctx)

{
  int *piVar1;
  u32 *puVar2;
  u32 uVar3;
  int iVar4;
  int iVar5;
  u64 uVar6;
  u64 uVar7;
  
  piVar1 = (int *)args[1];
  puVar2 = (u32 *)args[2];
  uVar3 = args[3];
  uVar6 = FindWorkModel__10EffectCoreFUi(ctx,*(u32 *)*args);
  iVar5 = 0;
  iVar4 = *piVar1;
  if (iVar4 == 2) {
    iVar5 = FindWorkModel__10EffectCoreFUi(ctx,*puVar2);
  }
  else if ((iVar4 == 0) || (iVar4 == 1)) {
    iVar5 = GetModel__10EffectCoreFiiii(ctx,*piVar1,*puVar2,0,0);
  }
  uVar7 = searchFrame__5FrameFPCc(*(u32 *)(iVar5 + 0x30),uVar3);
  chainModel__5FrameFP5Model(uVar7,uVar6);
  return 0;
}

/* ---- 0x0030cd10 size 0x6c  mdlDetach2(iiPPcPv)
 *      mangled: mdlDetach2__FiiPPcPv */
u64
mdlDetach2__FiiPPcPv(u64 id,u64 argc,u32 *args,u32 ctx)

{
  int iVar1;
  
  iVar1 = FindWorkModel__10EffectCoreFUi(ctx,*(u32 *)*args);
  unChainModel__5FrameFv(*(u32 *)(*(int *)(iVar1 + 0x30) + 0x1e0));
  return 0;
}

/* ---- 0x0030cd80 size 0x1a4  mdlAttach3(iiPPcPv)
 *      mangled: mdlAttach3__FiiPPcPv */
u64
mdlAttach3__FiiPPcPv(u64 id,u64 argc,u32 *args,u32 ctx)

{
  int iVar1;
  int iVar2;
  u32 uVar3;
  u32 uVar4;
  int iVar5;
  u64 uVar6;
  u64 uVar7;
  
  iVar1 = *(int *)*args;
  iVar2 = *(int *)args[2];
  uVar3 = *(u32 *)args[3];
  uVar4 = args[4];
  uVar7 = 0;
  iVar5 = 0;
  if (iVar1 == 2) {
    uVar7 = FindWorkModel__10EffectCoreFUi(ctx,*(u32 *)args[1]);
  }
  else if ((iVar1 == 0) || (iVar1 == 1)) {
    uVar7 = GetModel__10EffectCoreFiiii(ctx,iVar1,*(u32 *)args[1],0,0);
  }
  if (iVar2 == 2) {
    iVar5 = FindWorkModel__10EffectCoreFUi(ctx,uVar3);
  }
  else if ((iVar2 == 0) || (iVar2 == 1)) {
    iVar5 = GetModel__10EffectCoreFiiii(ctx,iVar2,uVar3,0,0);
  }
  uVar6 = searchFrame__5FrameFPCc(*(u32 *)(iVar5 + 0x30),uVar4);
  chainModel__5FrameFP5Model(uVar6,uVar7);
  return 0;
}

/* ---- 0x0030cf30 size 0xdc  mdlDetach3(iiPPcPv)
 *      mangled: mdlDetach3__FiiPPcPv */
u64
mdlDetach3__FiiPPcPv(u64 id,u64 argc,u32 *args,u32 ctx)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)*args;
  iVar2 = 0;
  if (iVar1 == 2) {
    iVar2 = FindWorkModel__10EffectCoreFUi(ctx,*(u32 *)args[1]);
  }
  else if ((iVar1 == 0) || (iVar1 == 1)) {
    iVar2 = GetModel__10EffectCoreFiiii(ctx,iVar1,*(u32 *)args[1],0,0);
  }
  unChainModel__5FrameFv(*(u32 *)(*(int *)(iVar2 + 0x30) + 0x1e0));
  return 0;
}

/* ---- 0x0030d010 size 0x198  mdlAttach4(iiPPcPv)
 *      mangled: mdlAttach4__FiiPPcPv */
u64
mdlAttach4__FiiPPcPv(u64 id,u64 argc,u32 *args,u32 ctx)

{
  int *piVar1;
  u32 *puVar2;
  int *piVar3;
  u32 uVar4;
  u32 uVar5;
  int iVar6;
  int iVar7;
  u64 uVar8;
  
  piVar1 = (int *)args[1];
  puVar2 = (u32 *)args[2];
  piVar3 = (int *)args[3];
  uVar4 = args[4];
  uVar5 = FindWorkModel__10EffectCoreFUi(ctx,*(u32 *)*args);
  iVar6 = 0;
  iVar7 = *piVar1;
  if (iVar7 == 2) {
    iVar6 = FindWorkModel__10EffectCoreFUi(ctx,*puVar2);
  }
  else if ((iVar7 == 0) || (iVar7 == 1)) {
    iVar6 = GetModel__10EffectCoreFiiii(ctx,*piVar1,*puVar2,0,0);
  }
  if (*piVar3 == 0) {
    iVar7 = searchFrame__5FrameFPCc(*(u32 *)(iVar6 + 0x30),0x3fef68);
  }
  else {
    iVar7 = searchFrame__5FrameFPCc(*(u32 *)(iVar6 + 0x30),0x3fef70);
  }
  uVar8 = searchFrame__5FrameFPCc(*(u32 *)(*(int *)(iVar7 + 0x98) + 0x30),uVar4);
  chainModel__5FrameFP5Model(uVar8,uVar5);
  return 0;
}

/* ---- 0x0030d1b0 size 0x6c  mdlDetach4(iiPPcPv)
 *      mangled: mdlDetach4__FiiPPcPv */
u64
mdlDetach4__FiiPPcPv(u64 id,u64 argc,u32 *args,u32 ctx)

{
  int iVar1;
  
  iVar1 = FindWorkModel__10EffectCoreFUi(ctx,*(u32 *)*args);
  unChainModel__5FrameFv(*(u32 *)(*(int *)(iVar1 + 0x30) + 0x1e0));
  return 0;
}

/* ---- 0x0030d220 size 0x170  mdlSetTestReg(iiPPcPv)
 *      mangled: mdlSetTestReg__FiiPPcPv */
u64
mdlSetTestReg__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 *puVar1;
  u32 uVar2;
  u32 uVar3;
  u32 uVar4;
  u32 uVar5;
  u32 uVar6;
  u32 uVar7;
  u32 uVar8;
  int iVar9;
  u64 uVar10;
  int iVar11;
  
  puVar1 = (u32 *)*args;
  uVar2 = *(u32 *)args[1];
  uVar3 = *(u32 *)args[2];
  uVar4 = *(u32 *)args[3];
  uVar5 = *(u32 *)args[4];
  uVar6 = *(u32 *)args[5];
  uVar7 = *(u32 *)args[6];
  uVar8 = *(u32 *)args[7];
  uVar10 = GetCore__3VECFv(ctx);
  iVar9 = FindWorkModel__10EffectCoreFUi(uVar10,*puVar1);
  for (iVar11 = 0; iVar11 < (int)(uint)*(ushort *)(*(int *)(iVar9 + 100) + 4); iVar11 = iVar11 + 1)
  {
    changeGSTest__7TextureFiiiiiiii
              (*(int *)(iVar9 + 0x4c) + iVar11 * 0x4c,uVar2,uVar3,uVar4,uVar5,uVar6,uVar7,uVar8);
  }
  return 0;
}

/* ---- 0x0030d390 size 0x8c  mdlClone(iiPPcPv)
 *      mangled: mdlClone__FiiPPcPv */
u64
mdlClone__FiiPPcPv(u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 *puVar1;
  int *piVar2;
  int iVar3;
  u64 uVar4;
  
  puVar1 = (u32 *)*args;
  piVar2 = (int *)args[1];
  uVar4 = GetCore__3VECFv(ctx);
  iVar3 = CloneWorkModel__10EffectCoreFi(uVar4,*puVar1);
  *(u32 *)(iVar3 + 0x51c) = ctx;
  *(code **)(iVar3 + 0x5a4) = _MotionEndCallback__FPvPCc;
  *piVar2 = iVar3;
  return 0;
}

/* ---- 0x0030d420 size 0x11c  mdlSetAlphaWeight(iiPPcPv)
 *      mangled: mdlSetAlphaWeight__FiiPPcPv */
u64
mdlSetAlphaWeight__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 *puVar1;
  float *pfVar2;
  int iVar3;
  u64 uVar4;
  int iVar5;
  float fVar6;
  
  puVar1 = (u32 *)*args;
  pfVar2 = (float *)args[1];
  uVar4 = GetCore__3VECFv(ctx);
  iVar3 = FindWorkModel__10EffectCoreFUi(uVar4,*puVar1);
  fVar6 = *pfVar2 * 128.0;
  if (2.1474836e+09 <= fVar6) {
    fVar6 = fVar6 - 2.1474836e+09;
  }
  for (iVar5 = 0; iVar5 < (int)(uint)*(ushort *)(*(int *)(iVar3 + 0x5c) + 4); iVar5 = iVar5 + 1) {
    setAtomicAlpha__6AtomicFUc
              (*(u32 *)(*(int *)(iVar3 + 0x48) + iVar5 * 4),(int)fVar6 & 0xff);
  }
  return 0;
}

/* ---- 0x0030d540 size 0xf8  mdlSetDrawLayer(iiPPcPv)
 *      mangled: mdlSetDrawLayer__FiiPPcPv */
u64
mdlSetDrawLayer__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 *puVar1;
  int *piVar2;
  u32 *puVar3;
  VIF1Prim *prim;
  u64 uVar4;
  
  puVar1 = (u32 *)*args;
  piVar2 = (int *)args[1];
  puVar3 = (u32 *)args[2];
  uVar4 = GetCore__3VECFv(ctx);
  prim = (VIF1Prim *)FindWorkModel__10EffectCoreFUi(uVar4,*puVar1);
  ReleaseOT__5WorldFP8VIF1Prim((World *)&m_World__4CApp,prim);
  AddDoubleOT__5WorldFiiP8VIF1Prim
            ((World *)&m_World__4CApp,*(int *)(WkLayer + *piVar2 * 8),
             *(int *)(WkLayer + *piVar2 * 8 + 4),prim);
  setZvolume__8VIF1PrimFs(prim,(short)*puVar3);
  return 0;
}

/* ---- 0x0030d640 size 0x2bc  mdlSetOffsetRotTrans(iiPPcPv)
 *      mangled: mdlSetOffsetRotTrans__FiiPPcPv */
u64
mdlSetOffsetRotTrans__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 *puVar1;
  u32 *puVar2;
  u32 uVar3;
  int iVar4;
  u32 *puVar5;
  u64 uVar6;
  u64 uVar7;
  u32 uVar8;
  u32 uVar9;
  u32 uVar10;
  u8 auStack_1f0 [16];
  u8 auStack_1e0 [64];
  u8 auStack_1a0 [16];
  u8 auStack_190 [64];
  u8 auStack_150 [16];
  u8 auStack_140 [16];
  u8 auStack_130 [16];
  u8 auStack_120 [16];
  u8 auStack_110 [64];
  u8 auStack_d0 [64];
  u8 auStack_90 [76];
  u32 uStack_44;
  u32 *puStack_20;
  u32 uStack_10;
  
  puVar5 = (u32 *)*args;
  puVar1 = (u32 *)args[1];
  puVar2 = (u32 *)args[2];
  uStack_44 = args[3];
  uVar3 = args[4];
  uVar10 = args[5];
  puStack_20 = args;
  uStack_10 = ctx;
  uVar6 = GetCore__3VECFv(ctx);
  uVar6 = FindWorkModel__10EffectCoreFUi(uVar6,*puVar5);
  uVar7 = GetCore__3VECFv(ctx);
  iVar4 = GetModel__10EffectCoreFiiii(uVar7,*puVar1,*puVar2,0,0);
  uVar7 = searchFrame__5FrameFPCc(*(u32 *)(iVar4 + 0x30),uStack_44);
  __ct__6MatrixFv(auStack_90);
  __ct__6MatrixFv(auStack_d0);
  __ct__6MatrixFv(auStack_110);
  __ct__7FVectorFv(auStack_120);
  __ct__7FVectorFv(auStack_130);
  __ct__7FVectorFv(auStack_140);
  getWorldRot__5FrameFi(auStack_190,uVar7,m_Env__8VIF1Prim & 1);
  __as__6MatrixFRC6Matrix(auStack_90,auStack_190);
  getWorldPos__5FrameFi(auStack_1a0,uVar7,m_Env__8VIF1Prim & 1);
  __as__7FVectorFRC7FVector(auStack_120,auStack_1a0);
  puVar5 = (u32 *)vx__7FVectorFv(uVar10);
  uVar8 = GetRad(*puVar5);
  puVar5 = (u32 *)vy__7FVectorFv(uVar10);
  uVar9 = GetRad(*puVar5);
  puVar5 = (u32 *)vz__7FVectorFv(uVar10);
  uVar10 = GetRad(*puVar5);
  __ct__7FVectorFffff(uVar8,uVar9,uVar10,0x3f800000,auStack_150);
  RotMatrix__6MatrixFRC7FVector(auStack_d0,auStack_150);
  MulMatrix__6MatrixCFRC6Matrix(auStack_1e0,auStack_90,auStack_d0);
  __as__6MatrixFRC6Matrix(auStack_110,auStack_1e0);
  puVar5 = (u32 *)vw__7FVectorFv(uVar3);
  *puVar5 = 0x3f800000;
  ApplyMatrix__6MatrixCFRC7FVector(auStack_1f0,auStack_110,uVar3);
  __as__7FVectorFRC7FVector(auStack_130,auStack_1f0);
  __apl__7FVectorFRC7FVector(auStack_130,auStack_120);
  TransMatrix__6MatrixFRC7FVector(auStack_110,auStack_130);
  SetMatrix__11EffectModelFP6Matrix(uVar6,auStack_110);
  return 0;
}

/* ---- 0x0030d970 size 0x84  mdlSetAutoDelete(iiPPcPv)
 *      mangled: mdlSetAutoDelete__FiiPPcPv */
u64
mdlSetAutoDelete__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  int iVar1;
  u64 uVar2;
  
  args = (u32 *)*args;
  uVar2 = GetCore__3VECFv(ctx);
  iVar1 = FindWorkModel__10EffectCoreFUi(uVar2,*args);
  *(byte *)(iVar1 + 0x5a8) = *(byte *)(iVar1 + 0x5a8) & 0xfe | 1;
  return 0;
}

/* ---- 0x0030da00 size 0x78  mdlWaitMotion(iiPPcPv)
 *      mangled: mdlWaitMotion__FiiPPcPv */
u64
mdlWaitMotion__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  u64 uVar1;
  
  args = (u32 *)*args;
  uVar1 = GetCore__3VECFv(ctx);
  uVar1 = FindWorkModel__10EffectCoreFUi(uVar1,*args);
  MotionWait__3VECFP11EffectModel(ctx,uVar1);
  return 0;
}

/* ---- 0x0030da80 size 0xf4  mdlWaitMotionFrame(iiPPcPv)
 *      mangled: mdlWaitMotionFrame__FiiPPcPv */
u64
mdlWaitMotionFrame__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 *puVar1;
  uint uVar2;
  u64 uVar3;
  
  puVar1 = (u32 *)*args;
  uVar2 = *(uint *)args[1];
  uVar3 = GetCore__3VECFv(ctx);
  uVar3 = FindWorkModel__10EffectCoreFUi(uVar3,*puVar1);
  MotionWait__3VECFP11EffectModel(ctx,uVar3);
  setMotionEndCallBack2__5ModelFPFPcPv_vfPv((float)uVar2 * 0.033333,uVar3,0x30c410,uVar3);
  return 0;
}

/* ---- 0x0030db80 size 0x70  mdlManyDelete(iiPPcPv)
 *      mangled: mdlManyDelete__FiiPPcPv */
u64
mdlManyDelete__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 uVar1;
  u64 uVar2;
  
  uVar1 = *(u32 *)*args;
  uVar2 = GetCore__3VECFv(ctx);
  ManyDeleteWorkModel__10EffectCoreFiP3VEC(uVar2,uVar1,ctx);
  return 0;
}

/* ---- 0x0030dbf0 size 0x1f8  mdlCreateMemory(iiPPcPv)
 *      mangled: mdlCreateMemory__FiiPPcPv */
u64
mdlCreateMemory__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 *puVar1;
  u32 *puVar2;
  u32 *puVar3;
  u32 *puVar4;
  int *piVar5;
  u32 *puVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  u32 uVar10;
  u64 uVar11;
  long lVar12;
  int iVar13;
  
  puVar1 = (u32 *)*args;
  puVar2 = (u32 *)args[1];
  puVar3 = (u32 *)args[2];
  puVar4 = (u32 *)args[3];
  piVar5 = (int *)args[4];
  puVar6 = (u32 *)args[5];
  uVar11 = GetCore__3VECFv(ctx);
  iVar8 = GetModel__10EffectCoreFiiii(uVar11,*puVar1,*puVar2,*puVar3,*puVar4);
  iVar9 = FindIndexWorkModel__10EffectCoreFUi(uVar11,0);
  lVar12 = __nw__FUi(0x5b0);
  uVar10 = 0;
  if (lVar12 != 0) {
    uVar10 = __ct__11EffectModelFP10EffectCore(lVar12,uVar11);
  }
  iVar13 = (int)uVar11;
  *(u32 *)(iVar13 + iVar9 * 4 + 0x198) = uVar10;
  iVar7 = *(int *)(iVar13 + iVar9 * 4 + 0x198);
  (**(code **)(*(int *)(iVar7 + 0x10) + 0x24))(iVar7,*(u32 *)(iVar8 + 0x54));
  iVar7 = *(int *)(iVar13 + iVar9 * 4 + 0x198);
  (**(code **)(*(int *)(iVar7 + 0x10) + 0x28))(iVar7,0);
  *(u32 *)(*(int *)(iVar13 + iVar9 * 4 + 0x198) + 0x51c) = ctx;
  *(code **)(*(int *)(iVar13 + iVar9 * 4 + 0x198) + 0x5a4) = _MotionEndCallback__FPvPCc;
  lVar12 = isCreate__11LevelsModelFv(iVar8 + 0xbc);
  if ((lVar12 != 0) && (*piVar5 != 0)) {
    createLevelofDetale__5ModelFPUcUi
              (*(u32 *)(iVar13 + iVar9 * 4 + 0x198),*(u32 *)(iVar8 + 0xd8),2);
    setDropShadow__13ShadowControlFP5Model
              (m_pOur__13ShadowControl,*(u32 *)(iVar13 + iVar9 * 4 + 0x198));
  }
  *puVar6 = *(u32 *)(iVar13 + iVar9 * 4 + 0x198);
  return 0;
}

/* ---- 0x0030ddf0 size 0xbc  mdlCreateMotion(iiPPcPv)
 *      mangled: mdlCreateMotion__FiiPPcPv */
u64
mdlCreateMotion__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 *puVar1;
  u64 uVar2;
  u64 uVar3;
  
  puVar1 = (u32 *)args[1];
  uVar2 = FindWorkModel__10EffectCoreFUi(ctx,*(u32 *)*args);
  uVar3 = GetDataPtr__10EffectCoreFUciUiUi(ctx,0x41,*puVar1,0x80,0x7f);
  createMotion__5ModelFPUc(uVar2,uVar3);
  (**(code **)(*(int *)((int)uVar2 + 0x10) + 0x28))(uVar2,0);
  return 0;
}

/* ---- 0x0030deb0 size 0x90  mdlSetTransCallbackMode(iiPPcPv)
 *      mangled: mdlSetTransCallbackMode__FiiPPcPv */
u64
mdlSetTransCallbackMode__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  uint *puVar1;
  int iVar2;
  
  puVar1 = (uint *)args[1];
  iVar2 = FindWorkModel__10EffectCoreFUi(ctx,*(u32 *)*args);
  *(byte *)(iVar2 + 0x5a8) = *(byte *)(iVar2 + 0x5a8) & 0xfd | (byte)((*puVar1 & 1) << 1);
  return 0;
}

/* ---- 0x0030df40 size 0xc0  mdlCreateShadow(iiPPcPv)
 *      mangled: mdlCreateShadow__FiiPPcPv */
u64
mdlCreateShadow__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 uVar1;
  u64 uVar2;
  u64 uVar3;
  
  uVar1 = *(u32 *)args[1];
  uVar2 = FindWorkModel__10EffectCoreFUi(ctx,*(u32 *)*args);
  uVar3 = GetDataPtr__10EffectCoreFUciUiUi(ctx,0x4f,uVar1,0xffffffffffffffff,0xffffffffffffffff)
  ;
  createLevelofDetale__5ModelFPUcUi(uVar2,uVar3,2);
  setDropShadow__13ShadowControlFP5Model(m_pOur__13ShadowControl,uVar2);
  return 0;
}

/* ---- 0x0030e000 size 0xe0  mdlSetDrawLayerDirect(iiPPcPv)
 *      mangled: mdlSetDrawLayerDirect__FiiPPcPv */
u64
mdlSetDrawLayerDirect__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  int layerA;
  int layerB;
  u32 uVar1;
  VIF1Prim *prim;
  
  layerA = *(int *)args[1];
  layerB = *(int *)args[2];
  uVar1 = *(u32 *)args[3];
  prim = (VIF1Prim *)FindWorkModel__10EffectCoreFUi(ctx,*(u32 *)*args);
  ReleaseOT__5WorldFP8VIF1Prim((World *)&m_World__4CApp,prim);
  AddDoubleOT__5WorldFiiP8VIF1Prim((World *)&m_World__4CApp,layerA,layerB,prim);
  setZvolume__8VIF1PrimFs(prim,(short)uVar1);
  return 0;
}

/* ---- 0x0030e0e0 size 0x74  hitCreateCylinder(iiPPcPv)
 *      mangled: hitCreateCylinder__FiiPPcPv */
u64
hitCreateCylinder__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 *puVar1;
  u32 uVar2;
  u64 uVar3;
  
  uVar2 = *args;
  puVar1 = (u32 *)args[1];
  uVar3 = GetCore__3VECFv(ctx);
  uVar2 = CreateHitCylinder__10EffectCoreFR7FVectori(uVar3,uVar2,0);
  *puVar1 = uVar2;
  return 0;
}

/* ---- 0x0030e160 size 0x7c  hitCreateCylinder2(iiPPcPv)
 *      mangled: hitCreateCylinder2__FiiPPcPv */
u64
hitCreateCylinder2__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 *puVar1;
  u32 uVar2;
  
  puVar1 = (u32 *)args[2];
  uVar2 = CreateHitCylinder__10EffectCoreFR7FVectori(ctx,*args,*(u32 *)args[1]);
  *puVar1 = uVar2;
  return 0;
}

/* ---- 0x0030e1e0 size 0x80  hitDeleteCylinder(iiPPcPv)
 *      mangled: hitDeleteCylinder__FiiPPcPv */
u64 hitDeleteCylinder__FiiPPcPv(void)

{
  int iVar1;
  int in_a3_lo;
  
  if (*(int *)(in_a3_lo + 0x36c) != 0) {
    iVar1 = *(int *)(in_a3_lo + 0x36c);
    if (iVar1 != 0) {
      (**(code **)(*(int *)(iVar1 + 0x38) + 8))(iVar1,1);
    }
    *(u32 *)(in_a3_lo + 0x36c) = 0;
  }
  return 0;
}

/* ---- 0x0030e260 size 0x88  hitIsEndCylinder(iiPPcPv)
 *      mangled: hitIsEndCylinder__FiiPPcPv */
u64
hitIsEndCylinder__FiiPPcPv(u64 id,u64 argc,int args,u32 ctx)

{
  uint *puVar1;
  int iVar2;
  
  puVar1 = *(uint **)(args + 4);
  iVar2 = GetCore__3VECFv(ctx);
  *puVar1 = (uint)(*(int *)(iVar2 + 0x36c) == 0);
  return 0;
}

/* ---- 0x0030e2f0 size 0x5c4  hitIsModelCylinderHit(iiPPcPv)
 *      mangled: hitIsModelCylinderHit__FiiPPcPv */
u64
hitIsModelCylinderHit__FiiPPcPv
          (u64 id,u64 argc,int args,u32 ctx)

{
  u32 *puVar1;
  u32 *puVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  float *pfVar6;
  u64 uVar7;
  float fVar8;
  float fVar9;
  u8 auStack_80 [16];
  u8 auStack_70 [4];
  float fStack_6c;
  float fStack_68;
  float fStack_54;
  float fStack_50;
  float fStack_4c;
  float fStack_48;
  float fStack_44;
  int iStack_20;
  u32 uStack_10;
  
  puVar1 = *(u32 **)(args + 4);
  puVar2 = *(u32 **)(args + 8);
  iStack_20 = args;
  uStack_10 = ctx;
  uVar7 = GetCore__3VECFv(ctx);
  iVar4 = GetModelSet__10EffectCoreFii(uVar7,1,*puVar1);
  if ((*(byte *)(iVar4 + 0xc) & 3) == 2) {
    *puVar2 = 2;
  }
  else {
    iVar5 = GetCore__3VECFv(ctx);
    iVar5 = *(int *)(iVar5 + 0x36c);
    GetMiddle__11HitCylinderFP20tagHitMotionCylinder(iVar5,auStack_70);
    iVar3 = *(int *)(iVar4 + 8);
    __pl__7FVectorCFRC7FVector(auStack_80,iVar3 + 0x2e0,iVar3 + 0xa0);
    pfVar6 = (float *)vx__7FVectorFv(iVar3 + 0x2b0);
    fVar8 = *pfVar6;
    pfVar6 = (float *)vz__7FVectorFv(iVar3 + 0x2b0);
    fStack_54 = (fVar8 + *pfVar6) / 2.0;
    if (fStack_54 < 0.0) {
      fStack_54 = -fStack_54;
    }
    fStack_44 = fStack_54;
    pfVar6 = (float *)vx__7FVectorFv(iVar5 + 0x20);
    fVar8 = *pfVar6;
    pfVar6 = (float *)vx__7FVectorFv(auStack_80);
    fStack_48 = fVar8 - *pfVar6;
    pfVar6 = (float *)vz__7FVectorFv(iVar5 + 0x20);
    fVar8 = *pfVar6;
    pfVar6 = (float *)vz__7FVectorFv(auStack_80);
    fStack_4c = fVar8 - *pfVar6;
    fStack_50 = SQRT(fStack_48 * fStack_48 + fStack_4c * fStack_4c);
    if (fStack_44 + fStack_6c < fStack_50) {
      *puVar2 = 0;
    }
    else if (((ulong)*(byte *)(iVar3 + 4) & 7) >> 1 == 1) {
      pfVar6 = (float *)vy__7FVectorFv(iVar3 + 0x2b0);
      fVar9 = *pfVar6;
      pfVar6 = (float *)vy__7FVectorFv(auStack_80);
      fVar8 = *pfVar6;
      pfVar6 = (float *)vy__7FVectorFv(iVar5 + 0x20);
      if (fVar8 + fVar9 <= *pfVar6) {
        pfVar6 = (float *)vy__7FVectorFv(iVar3 + 0x2b0);
        fVar9 = *pfVar6;
        pfVar6 = (float *)vy__7FVectorFv(auStack_80);
        fVar8 = *pfVar6;
        pfVar6 = (float *)vy__7FVectorFv(iVar5 + 0x20);
        if (*pfVar6 - fStack_68 <= fVar8 - fVar9) {
          if ((*(byte *)(iVar4 + 0xc) & 3) == 1) {
            *(byte *)(iVar4 + 0xc) = *(byte *)(iVar4 + 0xc) & 0xfc | 2;
            *puVar2 = 2;
            return 0;
          }
          *(byte *)(iVar4 + 0xc) = *(byte *)(iVar4 + 0xc) & 0xfc | 1;
          *puVar2 = 1;
          return 0;
        }
      }
      pfVar6 = (float *)vy__7FVectorFv(iVar3 + 0x2b0);
      fVar9 = *pfVar6;
      pfVar6 = (float *)vy__7FVectorFv(auStack_80);
      fVar8 = *pfVar6;
      pfVar6 = (float *)vy__7FVectorFv(iVar5 + 0x20);
      if (*pfVar6 - fStack_68 <= fVar8 + fVar9) {
        pfVar6 = (float *)vy__7FVectorFv(iVar3 + 0x2b0);
        fVar9 = *pfVar6;
        pfVar6 = (float *)vy__7FVectorFv(auStack_80);
        fVar8 = *pfVar6;
        pfVar6 = (float *)vy__7FVectorFv(iVar5 + 0x20);
        if (fVar8 - fVar9 <= *pfVar6 - fStack_68) {
          if ((*(byte *)(iVar4 + 0xc) & 3) == 1) {
            *(byte *)(iVar4 + 0xc) = *(byte *)(iVar4 + 0xc) & 0xfc | 2;
            *puVar2 = 2;
            *puVar2 = 2;
            return 0;
          }
          *(byte *)(iVar4 + 0xc) = *(byte *)(iVar4 + 0xc) & 0xfc | 1;
          *puVar2 = 1;
          return 0;
        }
      }
      pfVar6 = (float *)vy__7FVectorFv(iVar3 + 0x2b0);
      fVar9 = *pfVar6;
      pfVar6 = (float *)vy__7FVectorFv(auStack_80);
      fVar8 = *pfVar6;
      pfVar6 = (float *)vy__7FVectorFv(iVar5 + 0x20);
      if (*pfVar6 <= fVar8 + fVar9) {
        pfVar6 = (float *)vy__7FVectorFv(iVar3 + 0x2b0);
        fVar9 = *pfVar6;
        pfVar6 = (float *)vy__7FVectorFv(auStack_80);
        fVar8 = *pfVar6;
        pfVar6 = (float *)vy__7FVectorFv(iVar5 + 0x20);
        if (fVar8 - fVar9 <= *pfVar6) {
          if ((*(byte *)(iVar4 + 0xc) & 3) == 1) {
            *(byte *)(iVar4 + 0xc) = *(byte *)(iVar4 + 0xc) & 0xfc | 2;
            *puVar2 = 2;
            return 0;
          }
          *(byte *)(iVar4 + 0xc) = *(byte *)(iVar4 + 0xc) & 0xfc | 1;
          *puVar2 = 1;
          return 0;
        }
      }
      *puVar2 = 0;
    }
    else if ((*(byte *)(iVar4 + 0xc) & 3) == 1) {
      *(byte *)(iVar4 + 0xc) = *(byte *)(iVar4 + 0xc) & 0xfc | 2;
      *puVar2 = 2;
    }
    else {
      *(byte *)(iVar4 + 0xc) = *(byte *)(iVar4 + 0xc) & 0xfc | 1;
      *puVar2 = 1;
    }
  }
  return 0;
}

/* ---- 0x0030e8c0 size 0x98  hitCreateShot(iiPPcPv)
 *      mangled: hitCreateShot__FiiPPcPv */
u64
hitCreateShot__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 *puVar1;
  u32 uVar2;
  u32 *puVar3;
  u32 uVar4;
  u64 uVar5;
  
  puVar1 = (u32 *)*args;
  uVar4 = args[1];
  uVar2 = args[2];
  puVar3 = (u32 *)args[3];
  uVar5 = GetCore__3VECFv(ctx);
  uVar4 = CreateHitShot__10EffectCoreFiR7FVectorR7FVector(uVar5,*puVar1,uVar4,uVar2);
  *puVar3 = uVar4;
  return 0;
}

/* ---- 0x0030e960 size 0x78  hitIsEndShot(iiPPcPv)
 *      mangled: hitIsEndShot__FiiPPcPv */
u64
hitIsEndShot__FiiPPcPv(u64 id,u64 argc,int args,u32 ctx)

{
  u32 *puVar1;
  int iVar2;
  
  puVar1 = *(u32 **)(args + 4);
  *puVar1 = 0;
  iVar2 = GetCore__3VECFv(ctx);
  if (*(int *)(iVar2 + 0x370) == 0) {
    *puVar1 = 1;
  }
  return 0;
}

/* ---- 0x0030e9e0 size 0x43c  hitIsModelShotHit(iiPPcPv)
 *      mangled: hitIsModelShotHit__FiiPPcPv */
u64
hitIsModelShotHit__FiiPPcPv(u64 id,u64 argc,int args,u32 ctx)

{
  u32 *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  float *pfVar5;
  u32 *puVar6;
  u64 uVar7;
  long lVar8;
  float fVar9;
  u32 uVar10;
  u8 auStack_e0 [16];
  u8 auStack_d0 [16];
  u8 auStack_c0 [16];
  u8 auStack_b0 [16];
  u8 auStack_a0 [16];
  u8 auStack_90 [16];
  u8 auStack_80 [16];
  u8 auStack_70 [16];
  u8 auStack_60 [20];
  float fStack_4c;
  float fStack_48;
  float fStack_44;
  int iStack_20;
  u32 uStack_10;
  
  puVar6 = *(u32 **)(args + 4);
  puVar1 = *(u32 **)(args + 8);
  *puVar1 = 0;
  iStack_20 = args;
  uStack_10 = ctx;
  uVar7 = GetCore__3VECFv(ctx);
  iVar3 = GetModelSet__10EffectCoreFii(uVar7,1,*puVar6);
  if ((*(byte *)(iVar3 + 0xc) & 3) == 2) {
    *puVar1 = 2;
  }
  else {
    iVar4 = GetCore__3VECFv(ctx);
    iVar4 = *(int *)(iVar4 + 0x370);
    iVar2 = *(int *)(iVar3 + 8);
    __pl__7FVectorCFRC7FVector(auStack_60,iVar2 + 0x2e0,iVar2 + 0xa0);
    pfVar5 = (float *)vx__7FVectorFv(iVar2 + 0x2b0);
    fVar9 = *pfVar5;
    pfVar5 = (float *)vz__7FVectorFv(iVar2 + 0x2b0);
    fStack_4c = (fVar9 + *pfVar5) / 2.0;
    if (fStack_4c < 0.0) {
      fStack_4c = -fStack_4c;
    }
    fStack_44 = fStack_4c;
    __ct__7FVectorFRC7FVector(auStack_70,iVar4 + 0x10);
    __ct__7FVectorFRC7FVector(auStack_80,iVar4 + 0x30);
    __mi__7FVectorCFRC7FVector(auStack_90,auStack_80,auStack_70);
    pfVar5 = (float *)vy__7FVectorFv(iVar2 + 0x2b0);
    __ct__7FVectorFffff(0,-*pfVar5 * 2.0,0,0x3f800000,auStack_a0);
    OuterProduct__7FVectorCFRC7FVector(auStack_b0,auStack_90,auStack_a0);
    Normalize__7FVectorFv(auStack_b0);
    __ct__7FVectorFRC7FVector(auStack_c0,auStack_60);
    __ct__7FVectorFRC7FVector(auStack_d0,auStack_60);
    pfVar5 = (float *)vy__7FVectorFv(iVar2 + 0x2b0);
    fVar9 = *pfVar5;
    pfVar5 = (float *)vy__7FVectorFv(auStack_c0);
    *pfVar5 = *pfVar5 + fVar9;
    pfVar5 = (float *)vy__7FVectorFv(iVar2 + 0x2b0);
    fVar9 = *pfVar5;
    pfVar5 = (float *)vy__7FVectorFv(auStack_d0);
    *pfVar5 = *pfVar5 - fVar9;
    __mi__7FVectorCFRC7FVector(auStack_e0,auStack_80,auStack_c0);
    fVar9 = (float)InnerProduct__7FVectorCFRC7FVector(auStack_b0,auStack_e0);
    fStack_48 = fabsf(fVar9);
    if (fStack_48 <= fStack_44 + *(float *)(*(int *)(iVar4 + 4) + 0x14)) {
      if (((ulong)*(byte *)(iVar2 + 4) & 7) >> 1 == 1) {
        lVar8 = IsHit_CylinderToSphere__FR7FVectorR7FVectorfR7FVectorf
                          (*(u32 *)(*(int *)(iVar4 + 4) + 0x14),fStack_44,auStack_70,
                           auStack_80,auStack_60);
        if (lVar8 != 0) {
          if ((*(byte *)(iVar3 + 0xc) & 3) == 1) {
            *(byte *)(iVar3 + 0xc) = *(byte *)(iVar3 + 0xc) & 0xfc | 2;
            *puVar1 = 2;
          }
          else {
            *(byte *)(iVar3 + 0xc) = *(byte *)(iVar3 + 0xc) & 0xfc | 1;
            *puVar1 = 1;
          }
        }
      }
      else {
        puVar6 = (u32 *)vy__7FVectorFv(auStack_70);
        uVar10 = *puVar6;
        puVar6 = (u32 *)vy__7FVectorFv(auStack_60);
        *puVar6 = uVar10;
        lVar8 = IsHit_CylinderToSphere__FR7FVectorR7FVectorfR7FVectorf
                          (*(u32 *)(*(int *)(iVar4 + 4) + 0x14),fStack_44,auStack_70,
                           auStack_80,auStack_60);
        if (lVar8 != 0) {
          if ((*(byte *)(iVar3 + 0xc) & 3) == 1) {
            *(byte *)(iVar3 + 0xc) = *(byte *)(iVar3 + 0xc) & 0xfc | 2;
            *puVar1 = 2;
          }
          else {
            *(byte *)(iVar3 + 0xc) = *(byte *)(iVar3 + 0xc) & 0xfc | 1;
            *puVar1 = 1;
          }
        }
      }
    }
  }
  return 0;
}

/* ---- 0x0030ee20 size 0x64  hitGetShotEndPos(iiPPcPv)
 *      mangled: hitGetShotEndPos__FiiPPcPv */
u64 hitGetShotEndPos__FiiPPcPv(u64 id,u64 argc,int args,int ctx)

{
  __as__7FVectorFRC7FVector(*(u32 *)(args + 4),*(int *)(ctx + 0x370) + 0x30);
  return 0;
}

/* ---- 0x0030ee90 size 0x64  hitSetShotUpdateMode(iiPPcPv)
 *      mangled: hitSetShotUpdateMode__FiiPPcPv */
u64
hitSetShotUpdateMode__FiiPPcPv(u64 id,u64 argc,int args,int ctx)

{
  SetUpdateMode__7HitShotFi(*(u32 *)(ctx + 0x370),**(u32 **)(args + 4));
  return 0;
}

/* ---- 0x0030ef00 size 0xdc  hitAddShotKey(iiPPcPv)
 *      mangled: hitAddShotKey__FiiPPcPv */
u64 hitAddShotKey__FiiPPcPv(u64 id,u64 argc,int args,int ctx)

{
  int iVar1;
  u32 uVar2;
  long lVar3;
  u64 uVar4;
  u32 uVar5;
  
  iVar1 = **(int **)(args + 4);
  uVar5 = **(u32 **)(args + 8);
  uVar2 = *(u32 *)(ctx + 0x370);
  lVar3 = __nw__FUi(0x14);
  uVar4 = 0;
  if (lVar3 != 0) {
    uVar4 = __ct__10HitDynaKeyFff((float)iVar1 * 0.0333333,uVar5,lVar3);
  }
  AddKey__7HitShotFP10HitDynaKey(uVar2,uVar4);
  return 0;
}

/* ---- 0x0030f040 size 0x90  hitResetHitMark(iiPPcPv)
 *      mangled: hitResetHitMark__FiiPPcPv */
u64
hitResetHitMark__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  int iVar1;
  u64 uVar2;
  
  args = (u32 *)*args;
  uVar2 = GetCore__3VECFv(ctx);
  iVar1 = GetModelSet__10EffectCoreFii(uVar2,1,*args);
  *(byte *)(iVar1 + 0xc) = *(byte *)(iVar1 + 0xc) & 0xfc;
  return 0;
}

/* ---- 0x0030f0d0 size 0x70  hitSetShotEndMode(iiPPcPv)
 *      mangled: hitSetShotEndMode__FiiPPcPv */
u64
hitSetShotEndMode__FiiPPcPv(u64 id,u64 argc,int args,int ctx)

{
  *(byte *)(*(int *)(ctx + 0x370) + 0x50) =
       *(byte *)(*(int *)(ctx + 0x370) + 0x50) & 0xfb |
       (byte)((**(uint **)(args + 4) & 1) << 2);
  return 0;
}

/* ---- 0x0030f140 size 0x39c  hitGetShotHitFrame(iiPPcPv)
 *      mangled: hitGetShotHitFrame__FiiPPcPv */
u64
hitGetShotHitFrame__FiiPPcPv(u64 id,u64 argc,int args,u32 ctx)

{
  u32 *puVar1;
  uint *puVar2;
  int iVar3;
  int iVar4;
  float *pfVar5;
  u32 *puVar6;
  u64 uVar7;
  long lVar8;
  uint uVar9;
  float fVar10;
  u32 uVar11;
  u8 auStack_100 [16];
  u8 auStack_f0 [16];
  u8 auStack_e0 [16];
  u8 auStack_d0 [16];
  u8 auStack_c0 [16];
  u8 auStack_b0 [16];
  u8 auStack_a0 [16];
  u8 auStack_90 [16];
  u8 auStack_80 [16];
  u8 auStack_70 [28];
  float fStack_54;
  float fStack_48;
  float fStack_44;
  int iStack_20;
  u32 uStack_10;
  
  puVar6 = *(u32 **)(args + 4);
  puVar1 = *(u32 **)(args + 8);
  puVar2 = *(uint **)(args + 0xc);
  *puVar1 = 0;
  iStack_20 = args;
  uStack_10 = ctx;
  uVar7 = GetCore__3VECFv(ctx);
  iVar3 = GetModelSet__10EffectCoreFii(uVar7,1,*puVar6);
  iVar4 = GetCore__3VECFv(ctx);
  iVar4 = *(int *)(iVar4 + 0x370);
  iVar3 = *(int *)(iVar3 + 8);
  __pl__7FVectorCFRC7FVector(auStack_70,iVar3 + 0x2e0,iVar3 + 0xa0);
  pfVar5 = (float *)vx__7FVectorFv(iVar3 + 0x2b0);
  fVar10 = *pfVar5;
  pfVar5 = (float *)vz__7FVectorFv(iVar3 + 0x2b0);
  fStack_54 = (fVar10 + *pfVar5) / 2.0;
  if (fStack_54 < 0.0) {
    fStack_54 = -fStack_54;
  }
  fStack_44 = fStack_54;
  __ct__7FVectorFRC7FVector(auStack_80,iVar4 + 0x10);
  __ct__7FVectorFRC7FVector(auStack_90,iVar4 + 0x20);
  __mi__7FVectorCFRC7FVector(auStack_a0,auStack_90,auStack_80);
  pfVar5 = (float *)vy__7FVectorFv(iVar3 + 0x2b0);
  __ct__7FVectorFffff(0,-*pfVar5 * 2.0,0,0x3f800000,auStack_b0);
  OuterProduct__7FVectorCFRC7FVector(auStack_c0,auStack_a0,auStack_b0);
  Normalize__7FVectorFv(auStack_c0);
  __ct__7FVectorFRC7FVector(auStack_d0,auStack_70);
  __ct__7FVectorFRC7FVector(auStack_e0,auStack_70);
  pfVar5 = (float *)vy__7FVectorFv(iVar3 + 0x2b0);
  fVar10 = *pfVar5;
  pfVar5 = (float *)vy__7FVectorFv(auStack_d0);
  *pfVar5 = *pfVar5 + fVar10;
  pfVar5 = (float *)vy__7FVectorFv(iVar3 + 0x2b0);
  fVar10 = *pfVar5;
  pfVar5 = (float *)vy__7FVectorFv(auStack_e0);
  *pfVar5 = *pfVar5 - fVar10;
  __mi__7FVectorCFRC7FVector(auStack_f0,auStack_90,auStack_d0);
  fVar10 = (float)InnerProduct__7FVectorCFRC7FVector(auStack_c0,auStack_f0);
  fStack_48 = fabsf(fVar10);
  if (fStack_48 <= fStack_44 + *(float *)(*(int *)(iVar4 + 4) + 0x14)) {
    puVar6 = (u32 *)vy__7FVectorFv(auStack_80);
    uVar11 = *puVar6;
    puVar6 = (u32 *)vy__7FVectorFv(auStack_70);
    *puVar6 = uVar11;
    lVar8 = IsHit_CylinderToSphere__FR7FVectorR7FVectorfR7FVectorf
                      (*(u32 *)(*(int *)(iVar4 + 4) + 0x14),fStack_44,auStack_80,auStack_90,
                       auStack_70);
    if (lVar8 != 0) {
      *puVar1 = 1;
      __mi__7FVectorCFRC7FVector(auStack_100,auStack_70,iVar4 + 0x10);
      puVar6 = (u32 *)vy__7FVectorFv(auStack_100);
      *puVar6 = 0;
      fVar10 = (float)Length__7FVectorCFv(auStack_100);
      fVar10 = fVar10 / *(float *)(*(int *)(iVar4 + 4) + 0x18);
      if (fVar10 < 2.1474836e+09) {
        uVar9 = (uint)fVar10;
      }
      else {
        uVar9 = (int)(fVar10 - 2.1474836e+09) | 0x80000000;
      }
      *puVar2 = uVar9;
    }
  }
  return 0;
}

/* ---- 0x0030f4e0 size 0x70  camCreate(iiPPcPv)
 *      mangled: camCreate__FiiPPcPv */
u64
camCreate__FiiPPcPv(u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 *puVar1;
  u32 *puVar2;
  u32 uVar3;
  u64 uVar4;
  
  puVar1 = (u32 *)*args;
  puVar2 = (u32 *)args[1];
  uVar4 = GetCore__3VECFv(ctx);
  uVar3 = CreateCamera__10EffectCoreFi(uVar4,*puVar1);
  *puVar2 = uVar3;
  return 0;
}

/* ---- 0x0030f550 size 0xc4  camCreateVector(iiPPcPv)
 *      mangled: camCreateVector__FiiPPcPv */
u64
camCreateVector__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 *puVar1;
  u32 uVar2;
  u32 uVar3;
  u32 *puVar4;
  u64 uVar5;
  u32 uVar6;
  
  puVar1 = (u32 *)*args;
  uVar2 = args[1];
  uVar3 = args[2];
  uVar6 = *(u32 *)args[3];
  puVar4 = (u32 *)args[4];
  uVar5 = GetCore__3VECFv(ctx);
  uVar5 = CreateCamera__10EffectCoreFi(uVar5,*puVar1);
  CreateVector__12EffectCameraFP7FVectorP7FVectorf(uVar6,uVar5,uVar2,uVar3);
  *puVar4 = (int)uVar5;
  return 0;
}

/* ---- 0x0030f620 size 0x15c  camPlay(iiPPcPv)
 *      mangled: camPlay__FiiPPcPv */
u64
camPlay__FiiPPcPv(u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 *puVar1;
  int *piVar2;
  u32 *puVar3;
  u32 *puVar4;
  u64 uVar5;
  u64 uVar6;
  
  puVar1 = (u32 *)*args;
  piVar2 = (int *)args[1];
  puVar3 = (u32 *)args[2];
  puVar4 = (u32 *)args[3];
  uVar6 = 0;
  uVar5 = GetCore__3VECFv(ctx);
  uVar5 = FindCamera__10EffectCoreFUi(uVar5,*puVar1);
  if ((*(byte *)(*(int *)((int)uVar5 + 4) + 10) & 3) == 1) {
    if (*piVar2 == 2) {
      uVar6 = GetCore__3VECFv(ctx);
      uVar6 = FindWorkModel__10EffectCoreFUi(uVar6,*puVar3);
    }
    else {
      uVar6 = GetCore__3VECFv(ctx);
      uVar6 = GetModel__10EffectCoreFiiii(uVar6,*piVar2,*puVar3,0,0);
    }
  }
  SetInterFrame__12EffectCameraFP5ModelPc(uVar5,uVar6,0);
  uVar6 = GetCore__3VECFv(ctx);
  SetCurrentCamera__10EffectCoreFP12EffectCamerai(uVar6,uVar5,*puVar4);
  return 0;
}

/* ---- 0x0030f780 size 0x94  camStop(iiPPcPv)
 *      mangled: camStop__FiiPPcPv */
u64
camStop__FiiPPcPv(u64 id,u64 argc,u32 *args,u32 ctx)

{
  int iVar1;
  u64 uVar2;
  
  args = (u32 *)*args;
  uVar2 = GetCore__3VECFv(ctx);
  iVar1 = FindCamera__10EffectCoreFUi(uVar2,*args);
  uVar2 = GetCore__3VECFv(ctx);
  SetCurrentCamera__10EffectCoreFP12EffectCamerai(uVar2,0,0);
  Init__9tagEcFlagFv(iVar1 + 0xc);
  return 0;
}

/* ---- 0x0030f820 size 0x98  camSetMode(iiPPcPv)
 *      mangled: camSetMode__FiiPPcPv */
u64
camSetMode__FiiPPcPv(u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 *puVar1;
  u32 *puVar2;
  int iVar3;
  u64 uVar4;
  
  puVar1 = (u32 *)*args;
  puVar2 = (u32 *)args[1];
  uVar4 = GetCore__3VECFv(ctx);
  iVar3 = FindCamera__10EffectCoreFUi(uVar4,*puVar1);
  *(byte *)(iVar3 + 0xc) = *(byte *)(iVar3 + 0xc) & 0xfc | (byte)*puVar2 & 3;
  return 0;
}

/* ---- 0x0030f8c0 size 0x168  camPlay2(iiPPcPv)
 *      mangled: camPlay2__FiiPPcPv */
u64
camPlay2__FiiPPcPv(u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 *puVar1;
  int *piVar2;
  u32 *puVar3;
  u32 uVar4;
  u32 *puVar5;
  u64 uVar6;
  u64 uVar7;
  
  puVar1 = (u32 *)*args;
  piVar2 = (int *)args[1];
  puVar3 = (u32 *)args[2];
  uVar4 = args[3];
  puVar5 = (u32 *)args[4];
  uVar7 = 0;
  uVar6 = GetCore__3VECFv(ctx);
  uVar6 = FindCamera__10EffectCoreFUi(uVar6,*puVar1);
  if ((*(byte *)(*(int *)((int)uVar6 + 4) + 10) & 3) == 1) {
    if (*piVar2 == 2) {
      uVar7 = GetCore__3VECFv(ctx);
      uVar7 = FindWorkModel__10EffectCoreFUi(uVar7,*puVar3);
    }
    else {
      uVar7 = GetCore__3VECFv(ctx);
      uVar7 = GetModel__10EffectCoreFiiii(uVar7,*piVar2,*puVar3,0,0);
    }
  }
  SetInterFrame__12EffectCameraFP5ModelPc(uVar6,uVar7,uVar4);
  uVar7 = GetCore__3VECFv(ctx);
  SetCurrentCamera__10EffectCoreFP12EffectCamerai(uVar7,uVar6,*puVar5);
  return 0;
}

/* ---- 0x0030fa30 size 0x138  camPlay3(iiPPcPv)
 *      mangled: camPlay3__FiiPPcPv */
u64
camPlay3__FiiPPcPv(u64 id,u64 argc,u32 *args,u32 ctx)

{
  int *piVar1;
  u32 *puVar2;
  u32 uVar3;
  u64 uVar4;
  u64 uVar5;
  
  piVar1 = (int *)args[1];
  puVar2 = (u32 *)args[2];
  uVar3 = args[3];
  uVar4 = FindCamera__10EffectCoreFUi(ctx,*(u32 *)*args);
  uVar5 = GetModelSet__10EffectCoreFii(ctx,*piVar1,*puVar2);
  if ((*(byte *)(*(int *)((int)uVar4 + 4) + 10) & 3) == 1) {
    if (*piVar1 == 2) {
      return 0;
    }
    GetModel__10EffectCoreFiiii(ctx,*piVar1,*puVar2,0,0);
  }
  SetBoxCamera__12EffectCameraFPvP7FVector(uVar4,uVar5,uVar3);
  SetCurrentCamera__10EffectCoreFP12EffectCamerai(ctx,uVar4,0);
  return 0;
}

/* ---- 0x0030fb70 size 0x18c  camSetFogColor(iiPPcPv)
 *      mangled: camSetFogColor__FiiPPcPv */
u64 camSetFogColor__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  u32 uVar1;
  float *pfVar2;
  float fVar3;
  u8 uStack_44;
  u8 uStack_43;
  u8 uStack_42;
  u8 uStack_41;
  u32 *puStack_20;
  
  uVar1 = *args;
  puStack_20 = args;
  __ct__7_rgba32Fv(&uStack_44);
  pfVar2 = (float *)vx__7FVectorFv(uVar1);
  fVar3 = *pfVar2;
  if (fVar3 < 2.1474836e+09) {
    uStack_44 = (u8)(int)fVar3;
  }
  else {
    uStack_44 = (u8)(int)(fVar3 - 2.1474836e+09);
  }
  pfVar2 = (float *)vy__7FVectorFv(uVar1);
  fVar3 = *pfVar2;
  if (fVar3 < 2.1474836e+09) {
    uStack_43 = (u8)(int)fVar3;
  }
  else {
    uStack_43 = (u8)(int)(fVar3 - 2.1474836e+09);
  }
  pfVar2 = (float *)vz__7FVectorFv(uVar1);
  fVar3 = *pfVar2;
  if (fVar3 < 2.1474836e+09) {
    uStack_42 = (u8)(int)fVar3;
  }
  else {
    uStack_42 = (u8)(int)(fVar3 - 2.1474836e+09);
  }
  pfVar2 = (float *)vw__7FVectorFv(uVar1);
  fVar3 = *pfVar2;
  if (fVar3 < 2.1474836e+09) {
    uStack_41 = (u8)(int)fVar3;
  }
  else {
    uStack_41 = (u8)(int)(fVar3 - 2.1474836e+09);
  }
  SetFogColor__9GsxCameraFRC7_rgba32(camera__4CApp,&uStack_44);
  return 0;
}

/* ---- 0x0030fd70 size 0x54  camSetFogParam(iiPPcPv)
 *      mangled: camSetFogParam__FiiPPcPv */
u64 camSetFogParam__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  SetFogParam__9GsxCameraFff(*(u32 *)*args,*(u32 *)args[1],camera__4CApp);
  return 0;
}

/* ---- 0x0030fdd0 size 0x94  camGetMatrix(iiPPcPv)
 *      mangled: camGetMatrix__FiiPPcPv */
u64 camGetMatrix__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  u32 uVar1;
  u64 uVar2;
  
  uVar1 = args[1];
  if (*(int *)*args == 0) {
    uVar2 = GetMatrix__9GsxCameraFv(camera__4CApp);
    __as__6MatrixFRC6Matrix(uVar1,uVar2);
  }
  else {
    uVar2 = GetViewMatrix__9GsxCameraFv(camera__4CApp);
    __as__6MatrixFRC6Matrix(uVar1,uVar2);
  }
  return 0;
}

/* ---- 0x0030fe90 size 0x64  camSetFogOriginal(iiPPcPv)
 *      mangled: camSetFogOriginal__FiiPPcPv */
u64 camSetFogOriginal__FiiPPcPv(void)

{
  int iVar1;
  u32 in_a3_lo;
  
  iVar1 = GetCore__3VECFv(in_a3_lo);
  SetFogParam__9GsxCameraFff
            (*(u32 *)(iVar1 + 0x438),*(u32 *)(iVar1 + 0x43c),camera__4CApp);
  *(u64 *)(camera__4CApp + 0x150) = *(u64 *)(iVar1 + 0x440);
  return 0;
}

/* ---- 0x0030ff00 size 0x80  camSetVectorPos(iiPPcPv)
 *      mangled: camSetVectorPos__FiiPPcPv */
u64
camSetVectorPos__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 *puVar1;
  int iVar2;
  u64 uVar3;
  u32 uVar4;
  
  puVar1 = (u32 *)*args;
  uVar4 = *(u32 *)args[1];
  uVar3 = GetCore__3VECFv(ctx);
  iVar2 = FindCamera__10EffectCoreFUi(uVar3,*puVar1);
  *(u32 *)(iVar2 + 0xe8) = uVar4;
  return 0;
}

/* ---- 0x0030ff80 size 0x80  camSetVectorHight(iiPPcPv)
 *      mangled: camSetVectorHight__FiiPPcPv */
u64
camSetVectorHight__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 *puVar1;
  int iVar2;
  u64 uVar3;
  u32 uVar4;
  
  puVar1 = (u32 *)*args;
  uVar4 = *(u32 *)args[1];
  uVar3 = GetCore__3VECFv(ctx);
  iVar2 = FindCamera__10EffectCoreFUi(uVar3,*puVar1);
  *(u32 *)(iVar2 + 0xec) = uVar4;
  return 0;
}

/* ---- 0x00310000 size 0x108  camSetVibPower(iiPPcPv)
 *      mangled: camSetVibPower__FiiPPcPv */
u64
camSetVibPower__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 uVar1;
  u32 uVar2;
  u32 uVar3;
  u64 uVar4;
  u64 uVar5;
  u64 uVar6;
  u8 auStack_90 [16];
  u8 auStack_80 [16];
  u8 auStack_70 [16];
  u8 auStack_60 [28];
  u32 uStack_44;
  u32 *puStack_20;
  u32 uStack_10;
  
  uVar1 = *(u32 *)*args;
  uVar2 = args[1];
  puStack_20 = args;
  uStack_10 = ctx;
  __ct__7FVectorFRC7FVector(auStack_60,args[2]);
  __ct__7FVectorFRC7FVector(auStack_70,puStack_20[3]);
  uVar3 = *(u32 *)puStack_20[4];
  uStack_44 = *(u32 *)puStack_20[5];
  uVar4 = FindCamera__10EffectCoreFUi(uStack_10,uVar1);
  uVar5 = __ct__7FVectorFRC7FVector(auStack_80,auStack_60);
  uVar6 = __ct__7FVectorFRC7FVector(auStack_90,auStack_70);
  SetVibratePower__12EffectCameraFP7FVector7FVector7FVectorif
            (uStack_44,uVar4,uVar2,uVar5,uVar6,uVar3);
  return 0;
}

/* ---- 0x00310110 size 0xb8  camSetVibParam(iiPPcPv)
 *      mangled: camSetVibParam__FiiPPcPv */
u64
camSetVibParam__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)args[1];
  iVar2 = FindCamera__10EffectCoreFUi(ctx,*(u32 *)*args);
  *(byte *)(iVar2 + 0xc) = *(byte *)(iVar2 + 0xc) & 0xef | (iVar1 != 0) << 4;
  return 0;
}

/* ---- 0x003101d0 size 0x4c  vecZeroVector(iiPPcPv)
 *      mangled: vecZeroVector__FiiPPcPv */
u64 vecZeroVector__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  args = (u32 *)*args;
  args[2] = 0;
  args[1] = 0;
  *args = 0;
  args[3] = 0x3f800000;
  return 0;
}

/* ---- 0x00310220 size 0x5c  vecNormalize(iiPPcPv)
 *      mangled: vecNormalize__FiiPPcPv */
u64 vecNormalize__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  u32 uVar1;
  
  uVar1 = *args;
  __as__7FVectorFRC7FVector(uVar1,args[1]);
  Normalize__7FVectorFv(uVar1);
  return 0;
}

/* ---- 0x00310280 size 0x74  vecOuterProduct(iiPPcPv)
 *      mangled: vecOuterProduct__FiiPPcPv */
u64 vecOuterProduct__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  u32 uVar1;
  u8 auStack_50 [48];
  u32 *puStack_20;
  
  uVar1 = *args;
  puStack_20 = args;
  OuterProduct__7FVectorCFRC7FVector(auStack_50,args[1],args[2]);
  __as__7FVectorFRC7FVector(uVar1,auStack_50);
  return 0;
}

/* ---- 0x00310300 size 0x64  vecInnerProduct(iiPPcPv)
 *      mangled: vecInnerProduct__FiiPPcPv */
u64 vecInnerProduct__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  u32 *puVar1;
  u32 uVar2;
  
  puVar1 = (u32 *)*args;
  uVar2 = InnerProduct__7FVectorCFRC7FVector(args[1],args[2]);
  *puVar1 = uVar2;
  return 0;
}

/* ---- 0x00310370 size 0x50  vecLength(iiPPcPv)
 *      mangled: vecLength__FiiPPcPv */
u64 vecLength__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  u32 *puVar1;
  u32 uVar2;
  
  puVar1 = (u32 *)*args;
  uVar2 = Length__7FVectorCFv(args[1]);
  *puVar1 = uVar2;
  return 0;
}

/* ---- 0x003106b0 size 0x3c  matUnitMatrix(iiPPcPv)
 *      mangled: matUnitMatrix__FiiPPcPv */
u64 matUnitMatrix__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  UnitMatrix__6MatrixFv(*args);
  return 0;
}

/* ---- 0x003106f0 size 0x74  matApplyMatrix(iiPPcPv)
 *      mangled: matApplyMatrix__FiiPPcPv */
u64 matApplyMatrix__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  u32 uVar1;
  u8 auStack_50 [48];
  u32 *puStack_20;
  
  uVar1 = *args;
  puStack_20 = args;
  ApplyMatrix__6MatrixCFRC7FVector(auStack_50,args[1],args[2]);
  __as__7FVectorFRC7FVector(uVar1,auStack_50);
  return 0;
}

/* ---- 0x00310770 size 0x74  matMulMatrix(iiPPcPv)
 *      mangled: matMulMatrix__FiiPPcPv */
u64 matMulMatrix__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  u32 uVar1;
  u8 auStack_80 [96];
  u32 *puStack_20;
  
  uVar1 = *args;
  puStack_20 = args;
  MulMatrix__6MatrixCFRC6Matrix(auStack_80,args[1],args[2]);
  __as__6MatrixFRC6Matrix(uVar1,auStack_80);
  return 0;
}

/* ---- 0x003107f0 size 0x50  matTransMatrix(iiPPcPv)
 *      mangled: matTransMatrix__FiiPPcPv */
u64 matTransMatrix__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  TransMatrix__6MatrixFRC7FVector(*args,args[1]);
  return 0;
}

/* ---- 0x00310840 size 0x50  matRotXMatrix(iiPPcPv)
 *      mangled: matRotXMatrix__FiiPPcPv */
u64 matRotXMatrix__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  RotXMatrix__6MatrixFf(*(u32 *)args[1],*args);
  return 0;
}

/* ---- 0x00310890 size 0x50  matRotYMatrix(iiPPcPv)
 *      mangled: matRotYMatrix__FiiPPcPv */
u64 matRotYMatrix__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  RotYMatrix__6MatrixFf(*(u32 *)args[1],*args);
  return 0;
}

/* ---- 0x003108e0 size 0x50  matRotZMatrix(iiPPcPv)
 *      mangled: matRotZMatrix__FiiPPcPv */
u64 matRotZMatrix__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  RotZMatrix__6MatrixFf(*(u32 *)args[1],*args);
  return 0;
}

/* ---- 0x00310930 size 0x50  matRotMatrix(iiPPcPv)
 *      mangled: matRotMatrix__FiiPPcPv */
u64 matRotMatrix__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  RotMatrix__6MatrixFRC7FVector(*args,args[1]);
  return 0;
}

/* ---- 0x00310980 size 0x5c  matTranspose(iiPPcPv)
 *      mangled: matTranspose__FiiPPcPv */
u64 matTranspose__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  u32 uVar1;
  
  uVar1 = *args;
  __as__6MatrixFRC6Matrix(uVar1,args[1]);
  Transpose__6MatrixFv(uVar1);
  return 0;
}

/* ---- 0x00310a10 size 0x5c  matInvers(iiPPcPv)
 *      mangled: matInvers__FiiPPcPv */
u64 matInvers__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  u32 uVar1;
  
  uVar1 = *args;
  __as__6MatrixFRC6Matrix(uVar1,args[1]);
  Invers__6MatrixFv(uVar1);
  return 0;
}

/* ---- 0x00310a70 size 0x60  matGetAngle(iiPPcPv)
 *      mangled: matGetAngle__FiiPPcPv */
u64 matGetAngle__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  u32 uVar1;
  u8 auStack_50 [48];
  u32 *puStack_20;
  
  uVar1 = args[1];
  puStack_20 = args;
  GetAngle__FP6Matrix(auStack_50,*args);
  __as__7FVectorFRC7FVector(uVar1,auStack_50);
  return 0;
}

/* ---- 0x00310bd0 size 0x3c  sysWaitSystem(iiPPcPv)
 *      mangled: sysWaitSystem__FiiPPcPv */
u64 sysWaitSystem__FiiPPcPv(void)

{
  u32 in_a3_lo;
  
  SetRunState__3VECFi(in_a3_lo,2);
  return 0;
}

/* ---- 0x00310c10 size 0x3c  sysGetTime(iiPPcPv)
 *      mangled: sysGetTime__FiiPPcPv */
u64 sysGetTime__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  u32 uVar1;
  
  args = (u32 *)*args;
  uVar1 = GetTimer__7SysToolFv();
  *args = uVar1;
  return 0;
}

/* ---- 0x00310c50 size 0x38  sysSetTick(iiPPcPv)
 *      mangled: sysSetTick__FiiPPcPv */
u64 sysSetTick__FiiPPcPv(void)

{
  u32 uVar1;
  int in_a3_lo;
  
  uVar1 = GetTimer__7SysToolFv();
  *(u32 *)(in_a3_lo + 0x234) = uVar1;
  return 0;
}

/* ---- 0x00310c90 size 0x54  sysGetTick(iiPPcPv)
 *      mangled: sysGetTick__FiiPPcPv */
u64
sysGetTick__FiiPPcPv(u64 id,u64 argc,u32 *args,int ctx)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)*args;
  iVar2 = GetTimer__7SysToolFv();
  *piVar1 = iVar2 - *(int *)(ctx + 0x234);
  return 0;
}

/* ---- 0x00310cf0 size 0x70  sysSetAddTime(iiPPcPv)
 *      mangled: sysSetAddTime__FiiPPcPv */
u64
sysSetAddTime__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 *puVar1;
  u32 *puVar2;
  u64 uVar3;
  
  puVar1 = (u32 *)*args;
  puVar2 = (u32 *)args[1];
  uVar3 = GetCore__3VECFv(ctx);
  SetAddTime__10EffectCoreFif(*puVar2,uVar3,*puVar1);
  return 0;
}

/* ---- 0x00310d60 size 0x64  sysGetAddTime(iiPPcPv)
 *      mangled: sysGetAddTime__FiiPPcPv */
u64
sysGetAddTime__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 *puVar1;
  u32 uVar2;
  
  puVar1 = (u32 *)args[1];
  uVar2 = GetAddTime__10EffectCoreFi(ctx,*(u32 *)*args);
  *puVar1 = uVar2;
  return 0;
}

/* ---- 0x00310dd0 size 0x8c  sysCreateEffect(iiPPcPv)
 *      mangled: sysCreateEffect__FiiPPcPv */
u64
sysCreateEffect__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  char acStack_140 [128];
  u8 auStack_c0 [160];
  u32 *puStack_20;
  u32 uStack_10;
  
  puStack_20 = args;
  uStack_10 = ctx;
  sprintf(acStack_140,_6034,*args);
  SetPathname__7SysToolFPcPCc(auStack_c0,acStack_140);
  ReadOrder__11DvdromOrderFPCcPFiP9BufMemoryiPcPv_iiPvi
            (Dvdromour__11DvdromOrder,auStack_c0,0x310ad0,0,ctx,0);
  return 0;
}

/* ---- 0x00310e60 size 0x84  sysSetHandle(iiPPcPv)
 *      mangled: sysSetHandle__FiiPPcPv */
u64
sysSetHandle__FiiPPcPv(u64 id,u64 argc,u32 *args,int ctx)

{
  AddHandle__12EffProcParamFiUiUi
            (ctx + 0xe4,*(u32 *)*args,*(u32 *)args[1],
             *(u32 *)args[2]);
  return 0;
}

/* ---- 0x00310ef0 size 0x7c  sysGetHandle(iiPPcPv)
 *      mangled: sysGetHandle__FiiPPcPv */
u64
sysGetHandle__FiiPPcPv(u64 id,u64 argc,u32 *args,int ctx)

{
  int iVar1;
  u32 *puVar2;
  
  iVar1 = *(int *)*args;
  puVar2 = (u32 *)args[2];
  *(u32 *)args[1] = *(u32 *)(ctx + iVar1 * 4 + 0xe8);
  *puVar2 = *(u32 *)(ctx + iVar1 * 4 + 0x138);
  return 0;
}

/* ---- 0x00310f70 size 0x50  sysGetHandleCount(iiPPcPv)
 *      mangled: sysGetHandleCount__FiiPPcPv */
u64
sysGetHandleCount__FiiPPcPv(u64 id,u64 argc,u32 *args,int ctx)

{
  u32 uVar1;
  
  args = (u32 *)*args;
  uVar1 = GetCount__12EffProcParamFv(ctx + 0xe4);
  *args = uVar1;
  return 0;
}

/* ---- 0x00310fe0 size 0x40  sysWaitCreateEffect(iiPPcPv)
 *      mangled: sysWaitCreateEffect__FiiPPcPv */
u64 sysWaitCreateEffect__FiiPPcPv(void)

{
  int in_a3_lo;
  
  *(byte *)(in_a3_lo + 0x238) = *(byte *)(in_a3_lo + 0x238) & 0xfe | 1;
  return 0;
}

/* ---- 0x00311020 size 0xac  sysStartEffect(iiPPcPv)
 *      mangled: sysStartEffect__FiiPPcPv */
u64 sysStartEffect__FiiPPcPv(void)

{
  u64 uVar1;
  u32 in_a3_lo;
  int iVar2;
  
  uVar1 = GetParent__10EffectCoreFv(in_a3_lo);
  KillThreadAll__10EffectCoreFv(in_a3_lo);
  iVar2 = (int)uVar1;
  Duplicate__6EffectFP6Effect(*(u32 *)(iVar2 + 0x28),uVar1);
  SetEndCallback__6EffectFPFPvi_vPvi(uVar1,0,0,0);
  (**(code **)(iVar2 + 0x38))
            (*(u32 *)(iVar2 + 0x28),*(u32 *)(iVar2 + 0x3c),
             *(u32 *)(iVar2 + 0x40));
  Run__6EffectFv(*(u32 *)(iVar2 + 0x28));
  *(u32 *)(iVar2 + 0x28) = 0;
  PollDelete__6EffectFv(uVar1);
  return 0;
}

/* ---- 0x003110d0 size 0x64  calRand(iiPPcPv)
 *      mangled: calRand__FiiPPcPv */
u64 calRand__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  
  piVar1 = (int *)*args;
  piVar2 = (int *)args[1];
  iVar3 = rand();
  if (*piVar2 == 0) {
    trap(7);
  }
  *piVar1 = iVar3 % *piVar2;
  return 0;
}

/* ---- 0x00311140 size 0x70  calFRand(iiPPcPv)
 *      mangled: calFRand__FiiPPcPv */
u64 calFRand__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  float *pfVar1;
  float *pfVar2;
  int iVar3;
  
  pfVar1 = (float *)*args;
  pfVar2 = (float *)args[1];
  iVar3 = rand();
  *pfVar1 = *pfVar2 * ((float)iVar3 / 2.1474836e+09);
  return 0;
}

/* ---- 0x003111b0 size 0x5c  calSin(iiPPcPv)
 *      mangled: calSin__FiiPPcPv */
u64 calSin__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  float *pfVar1;
  float fVar2;
  
  pfVar1 = (float *)*args;
  fVar2 = (float)GetRad(*(u32 *)args[1]);
  fVar2 = sinf(fVar2);
  *pfVar1 = fVar2;
  return 0;
}

/* ---- 0x00311210 size 0x5c  calCos(iiPPcPv)
 *      mangled: calCos__FiiPPcPv */
u64 calCos__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  float *pfVar1;
  float fVar2;
  
  pfVar1 = (float *)*args;
  fVar2 = (float)GetRad(*(u32 *)args[1]);
  fVar2 = cosf(fVar2);
  *pfVar1 = fVar2;
  return 0;
}

/* ---- 0x00311270 size 0x5c  calTan(iiPPcPv)
 *      mangled: calTan__FiiPPcPv */
u64 calTan__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  float *pfVar1;
  float fVar2;
  
  pfVar1 = (float *)*args;
  fVar2 = (float)GetRad(*(u32 *)args[1]);
  fVar2 = tanf(fVar2);
  *pfVar1 = fVar2;
  return 0;
}

/* ---- 0x003112d0 size 0x50  calAsin(iiPPcPv)
 *      mangled: calAsin__FiiPPcPv */
u64 calAsin__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  float *pfVar1;
  float fVar2;
  
  pfVar1 = (float *)*args;
  fVar2 = asinf(*(float *)args[1]);
  *pfVar1 = fVar2;
  return 0;
}

/* ---- 0x00311320 size 0x50  calAcos(iiPPcPv)
 *      mangled: calAcos__FiiPPcPv */
u64 calAcos__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  float *pfVar1;
  float fVar2;
  
  pfVar1 = (float *)*args;
  fVar2 = acosf(*(float *)args[1]);
  *pfVar1 = fVar2;
  return 0;
}

/* ---- 0x00311370 size 0x50  calAtan(iiPPcPv)
 *      mangled: calAtan__FiiPPcPv */
u64 calAtan__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  float *pfVar1;
  float fVar2;
  
  pfVar1 = (float *)*args;
  fVar2 = atanf(*(float *)args[1]);
  *pfVar1 = fVar2;
  return 0;
}

/* ---- 0x003113c0 size 0x50  calRad(iiPPcPv)
 *      mangled: calRad__FiiPPcPv */
u64 calRad__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  u32 *puVar1;
  u32 uVar2;
  
  puVar1 = (u32 *)*args;
  uVar2 = GetRad(*(u32 *)args[1]);
  *puVar1 = uVar2;
  return 0;
}

/* ---- 0x00311410 size 0x44  calSqrt(iiPPcPv)
 *      mangled: calSqrt__FiiPPcPv */
u64 calSqrt__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  *(float *)*args = SQRT(*(float *)args[1]);
  return 0;
}

/* ---- 0x00311460 size 0xe8  cusCreate(iiPPcPv)
 *      mangled: cusCreate__FiiPPcPv */
u64
cusCreate__FiiPPcPv(u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 *puVar1;
  u32 uVar2;
  u32 *puVar3;
  u32 uVar4;
  int *piVar5;
  int *piVar6;
  int iVar7;
  u64 uVar8;
  
  puVar1 = (u32 *)*args;
  uVar2 = args[1];
  puVar3 = (u32 *)args[2];
  uVar4 = args[3];
  piVar5 = (int *)args[4];
  piVar6 = (int *)args[5];
  uVar8 = GetCore__3VECFv(ctx);
  iVar7 = CreateCustomModel__10EffectCoreFiPcUiPc(uVar8,*puVar1,uVar2,*puVar3,uVar4);
  if (*piVar5 != 0) {
    (**(code **)(*(int *)(iVar7 + 0x10) + 0x28))();
  }
  *piVar6 = iVar7;
  return 0;
}

/* ---- 0x00311550 size 0xbc  cusShow(iiPPcPv)
 *      mangled: cusShow__FiiPPcPv */
u64
cusShow__FiiPPcPv(u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 *puVar1;
  int *piVar2;
  int iVar3;
  u64 uVar4;
  
  puVar1 = (u32 *)*args;
  piVar2 = (int *)args[1];
  uVar4 = GetCore__3VECFv(ctx);
  iVar3 = FindCustomModel__10EffectCoreFUi(uVar4,*puVar1);
  if (*piVar2 == 0) {
    (**(code **)(*(int *)(iVar3 + 0x10) + 0x2c))();
  }
  else {
    (**(code **)(*(int *)(iVar3 + 0x10) + 0x28))();
  }
  return 0;
}

/* ---- 0x00311610 size 0x8c  btlStatusRecovery(iiPPcPv)
 *      mangled: btlStatusRecovery__FiiPPcPv */
u64
btlStatusRecovery__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 *puVar1;
  u32 *puVar2;
  u64 uVar3;
  
  puVar2 = (u32 *)*args;
  puVar1 = (u32 *)args[1];
  uVar3 = GetCore__3VECFv(ctx);
  puVar2 = (u32 *)GetModelSet__10EffectCoreFii(uVar3,*puVar2,*puVar1);
  StatusRecovery__Fii(*puVar2,0);
  return 0;
}

/* ---- 0x003116a0 size 0x9c  btlStatusRecovery2(iiPPcPv)
 *      mangled: btlStatusRecovery2__FiiPPcPv */
u64
btlStatusRecovery2__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 uVar1;
  u32 *puVar2;
  
  uVar1 = *(u32 *)args[2];
  puVar2 = (u32 *)
           GetModelSet__10EffectCoreFii(ctx,*(u32 *)*args,*(u32 *)args[1]);
  StatusRecovery__Fii(*puVar2,uVar1);
  return 0;
}

/* ---- 0x00311740 size 0x88  btlIdelMotionReset(iiPPcPv)
 *      mangled: btlIdelMotionReset__FiiPPcPv */
u64
btlIdelMotionReset__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 *puVar1;
  u32 *puVar2;
  u64 uVar3;
  
  puVar2 = (u32 *)*args;
  puVar1 = (u32 *)args[1];
  uVar3 = GetCore__3VECFv(ctx);
  puVar2 = (u32 *)GetModelSet__10EffectCoreFii(uVar3,*puVar2,*puVar1);
  IdelMotionReset__Fi(*puVar2);
  return 0;
}

/* ---- 0x003117d0 size 0x7c  btlCameraControlStatus(iiPPcPv)
 *      mangled: btlCameraControlStatus__FiiPPcPv */
u64
btlCameraControlStatus__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  int *piVar1;
  
  piVar1 = (int *)*args;
  CameraControlStatus__Fb(*piVar1 != 0);
  if (*piVar1 == 1) {
    SetCurrentCamera__10EffectCoreFP12EffectCamerai(ctx,0,0);
  }
  return 0;
}

/* ---- 0x00311850 size 0x9c  btlGetCharno(iiPPcPv)
 *      mangled: btlGetCharno__FiiPPcPv */
u64
btlGetCharno__FiiPPcPv(u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 *puVar1;
  u32 *puVar2;
  int *piVar3;
  int iVar4;
  u64 uVar5;
  
  puVar1 = (u32 *)*args;
  puVar2 = (u32 *)args[1];
  piVar3 = (int *)args[2];
  uVar5 = GetCore__3VECFv(ctx);
  iVar4 = GetBtlChrParam__10EffectCoreFii(uVar5,*puVar1,*puVar2);
  *piVar3 = (int)*(short *)(iVar4 + 10);
  return 0;
}

/* ---- 0x003118f0 size 0x88  btlBeginMagicEffectClear(iiPPcPv)
 *      mangled: btlBeginMagicEffectClear__FiiPPcPv */
u64
btlBeginMagicEffectClear__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 *puVar1;
  u32 *puVar2;
  u64 uVar3;
  
  puVar2 = (u32 *)*args;
  puVar1 = (u32 *)args[1];
  uVar3 = GetCore__3VECFv(ctx);
  puVar2 = (u32 *)GetModelSet__10EffectCoreFii(uVar3,*puVar2,*puVar1);
  BeginMagicEffectClear__Fi(*puVar2);
  return 0;
}

/* ---- 0x00311980 size 0x88  btlMagicMotionEndSet(iiPPcPv)
 *      mangled: btlMagicMotionEndSet__FiiPPcPv */
u64
btlMagicMotionEndSet__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 *puVar1;
  u32 *puVar2;
  u64 uVar3;
  
  puVar2 = (u32 *)*args;
  puVar1 = (u32 *)args[1];
  uVar3 = GetCore__3VECFv(ctx);
  puVar2 = (u32 *)GetModelSet__10EffectCoreFii(uVar3,*puVar2,*puVar1);
  MagicMotionEndSet__Fi(*puVar2);
  return 0;
}

/* ---- 0x00311a10 size 0x19c  btlEffectDamageSet(iiPPcPv)
 *      mangled: btlEffectDamageSet__FiiPPcPv */
u64
btlEffectDamageSet__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 *puVar1;
  int *piVar2;
  u32 *puVar3;
  u32 *puVar4;
  u32 *puVar5;
  u32 *puVar6;
  u32 uVar7;
  u64 uVar8;
  u8 auStack_70 [24];
  u32 uStack_58;
  u32 uStack_54;
  u32 *puStack_50;
  u32 *puStack_4c;
  u32 *puStack_48;
  u32 *puStack_44;
  u32 *puStack_20;
  u32 uStack_10;
  
  puStack_44 = (u32 *)*args;
  puStack_48 = (u32 *)args[1];
  puStack_4c = (u32 *)args[2];
  puStack_50 = (u32 *)args[3];
  puVar1 = (u32 *)args[4];
  uStack_54 = args[5];
  piVar2 = (int *)args[6];
  puVar3 = (u32 *)args[7];
  puVar4 = (u32 *)args[8];
  puVar5 = (u32 *)args[0xc];
  uStack_58 = ctx;
  puStack_20 = args;
  uStack_10 = ctx;
  uVar8 = GetCore__3VECFv(ctx);
  puVar6 = (u32 *)GetModelSet__10EffectCoreFii(uVar8,*puStack_44,*puStack_48);
  uVar8 = __ct__7FVectorFRC7FVector(auStack_70,uStack_54);
  uVar7 = EffectDamageSet__Fisss7FVectorbiiiii
                    (*puVar6,(short)*puStack_4c,(short)*puStack_50,(short)*puVar1,uVar8,*piVar2 != 0
                     ,*puVar3,*puVar4);
  *puVar5 = uVar7;
  return 0;
}

/* ---- 0x00311bb0 size 0x16c  btlGetCharBBoxSize(iiPPcPv)
 *      mangled: btlGetCharBBoxSize__FiiPPcPv */
u64
btlGetCharBBoxSize__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 *puVar1;
  u32 uVar2;
  float *pfVar3;
  u32 *puVar4;
  int iVar5;
  float *pfVar6;
  u32 *puVar7;
  u64 uVar8;
  float fVar9;
  u8 auStack_60 [28];
  float fStack_44;
  u32 *puStack_20;
  u32 uStack_10;
  
  puVar7 = (u32 *)*args;
  puVar1 = (u32 *)args[1];
  uVar2 = args[2];
  pfVar3 = (float *)args[3];
  puVar4 = (u32 *)args[4];
  puStack_20 = args;
  uStack_10 = ctx;
  uVar8 = GetCore__3VECFv(ctx);
  iVar5 = GetModelSet__10EffectCoreFii(uVar8,*puVar7,*puVar1);
  iVar5 = *(int *)(iVar5 + 8);
  __pl__7FVectorCFRC7FVector(auStack_60,iVar5 + 0x2a0,iVar5 + 0xa0);
  __as__7FVectorFRC7FVector(uVar2,auStack_60);
  pfVar6 = (float *)vx__7FVectorFv(iVar5 + 0x2f0);
  fVar9 = *pfVar6;
  pfVar6 = (float *)vz__7FVectorFv(iVar5 + 0x2f0);
  *pfVar3 = (fVar9 + *pfVar6) / 2.0;
  if (*pfVar3 < 0.0) {
    fStack_44 = -*pfVar3;
  }
  else {
    fStack_44 = *pfVar3;
  }
  *pfVar3 = fStack_44;
  puVar7 = (u32 *)vy__7FVectorFv(iVar5 + 0x2f0);
  *puVar4 = *puVar7;
  return 0;
}

/* ---- 0x00311d20 size 0x100  btlChangeBattleBG(iiPPcPv)
 *      mangled: btlChangeBattleBG__FiiPPcPv */
u64
btlChangeBattleBG__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  int *piVar1;
  u32 *puVar2;
  VIF1Prim *prim;
  VIF1Prim *prim_00;
  u64 uVar3;
  
  piVar1 = (int *)*args;
  puVar2 = (u32 *)args[1];
  prim = (VIF1Prim *)GetBattleBgModel__Fv();
  uVar3 = GetCore__3VECFv(ctx);
  prim_00 = (VIF1Prim *)FindWorkModel__10EffectCoreFUi(uVar3,*puVar2);
  if (*piVar1 == 0) {
    ReleaseOT__5WorldFP8VIF1Prim((World *)&m_World__4CApp,prim_00);
    AddDoubleOT__5WorldFiiP8VIF1Prim((World *)&m_World__4CApp,1,2,prim);
  }
  else {
    ReleaseOT__5WorldFP8VIF1Prim((World *)&m_World__4CApp,prim);
    AddDoubleOT__5WorldFiiP8VIF1Prim((World *)&m_World__4CApp,1,2,prim_00);
  }
  return 0;
}

/* ---- 0x00311e20 size 0x60  btlChangeFusionModel(iiPPcPv)
 *      mangled: btlChangeFusionModel__FiiPPcPv */
u64 btlChangeFusionModel__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  uint *puVar1;
  long lVar2;
  
  puVar1 = (uint *)*args;
  lVar2 = ChangeFusionModel__Fv();
  *puVar1 = (uint)(lVar2 != 0);
  return 0;
}

/* ---- 0x00311e80 size 0x98  btlComboStopOff(iiPPcPv)
 *      mangled: btlComboStopOff__FiiPPcPv */
u64
btlComboStopOff__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 *puVar1;
  u32 uVar2;
  
  if (*(int *)*args == -1) {
    uVar2 = 0xffffffff;
  }
  else {
    puVar1 = (u32 *)GetModelSet__10EffectCoreFii(ctx,1,*(int *)*args);
    uVar2 = *puVar1;
  }
  ComboStopOff__Fi(uVar2);
  return 0;
}

/* ---- 0x00311f20 size 0xf4  btlCharactorShow(iiPPcPv)
 *      mangled: btlCharactorShow__FiiPPcPv */
u64
btlCharactorShow__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  int iVar1;
  u32 *puVar2;
  
  iVar1 = *(int *)args[2];
  if (*(int *)args[1] == -1) {
    CharactorShow__Fib(0xffffffffffffffff,iVar1 != 0);
  }
  else {
    puVar2 = (u32 *)
             GetModelSet__10EffectCoreFii(ctx,*(u32 *)*args,*(int *)args[1]);
    CharactorShow__Fib(*puVar2,iVar1 != 0);
  }
  return 0;
}

/* ---- 0x00312020 size 0x50  btlGetFusionCharactor(iiPPcPv)
 *      mangled: btlGetFusionCharactor__FiiPPcPv */
u64
btlGetFusionCharactor__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  GetFusionCharactor__FPiPi(*args,args[1]);
  return 0;
}

/* ---- 0x00312070 size 0x88  btlMagicStartEffectCall(iiPPcPv)
 *      mangled: btlMagicStartEffectCall__FiiPPcPv */
u64
btlMagicStartEffectCall__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 *puVar1;
  u32 *puVar2;
  u64 uVar3;
  
  puVar2 = (u32 *)*args;
  puVar1 = (u32 *)args[1];
  uVar3 = GetCore__3VECFv(ctx);
  puVar2 = (u32 *)GetModelSet__10EffectCoreFii(uVar3,*puVar2,*puVar1);
  MagicStartEffectCall__Fi(*puVar2);
  return 0;
}

/* ---- 0x00312100 size 0x58  btlBattleBGShow(iiPPcPv)
 *      mangled: btlBattleBGShow__FiiPPcPv */
u64 btlBattleBGShow__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  int iVar1;
  
  iVar1 = *(int *)*args;
  BattleBGShow__Fb(iVar1 != 0);
  if (iVar1 != 0) {
    CameraCutChange__Fv();
  }
  return 0;
}

/* ---- 0x00312160 size 0xb0  btlHitMarkEffectCall(iiPPcPv)
 *      mangled: btlHitMarkEffectCall__FiiPPcPv */
u64 btlHitMarkEffectCall__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  u32 uVar1;
  u64 uVar2;
  u64 uVar3;
  u8 auStack_90 [16];
  u8 auStack_80 [16];
  u8 auStack_70 [16];
  u8 auStack_60 [28];
  u32 uStack_44;
  u32 *puStack_20;
  
  uVar1 = *(u32 *)*args;
  puStack_20 = args;
  __ct__7FVectorFRC7FVector(auStack_60,args[1]);
  __ct__7FVectorFRC7FVector(auStack_70,puStack_20[2]);
  uStack_44 = *(u32 *)puStack_20[3];
  uVar2 = __ct__7FVectorFRC7FVector(auStack_80,auStack_60);
  uVar3 = __ct__7FVectorFRC7FVector(auStack_90,auStack_70);
  HitMarkEffectCall__Fi7FVector7FVectorf(uStack_44,uVar1,uVar2,uVar3);
  return 0;
}

/* ---- 0x00312210 size 0x6c  btlBGShowParts(iiPPcPv)
 *      mangled: btlBGShowParts__FiiPPcPv */
u64 btlBGShowParts__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  u32 *puVar1;
  u32 uVar2;
  
  puVar1 = (u32 *)args[2];
  uVar2 = BattleBGShowParts__FUiUi(*(u32 *)*args,*(u32 *)args[1]);
  *puVar1 = uVar2;
  return 0;
}

/* ---- 0x00312280 size 0xa4  btlCharacterPushMode(iiPPcPv)
 *      mangled: btlCharacterPushMode__FiiPPcPv */
u64
btlCharacterPushMode__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  int iVar1;
  u32 *puVar2;
  
  iVar1 = *(int *)args[2];
  puVar2 = (u32 *)
           GetModelSet__10EffectCoreFii(ctx,*(u32 *)*args,*(u32 *)args[1]);
  CharacterPushMode__Fib(*puVar2,iVar1 != 0);
  return 0;
}

/* ---- 0x00312330 size 0xc8  btlGetWarpPos(iiPPcPv)
 *      mangled: btlGetWarpPos__FiiPPcPv */
u64
btlGetWarpPos__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  int iVar1;
  u32 uVar2;
  u32 *puVar3;
  u8 auStack_50 [48];
  u32 *puStack_20;
  u32 uStack_10;
  
  iVar1 = *(int *)args[2];
  uVar2 = args[3];
  puStack_20 = args;
  uStack_10 = ctx;
  puVar3 = (u32 *)
           GetModelSet__10EffectCoreFii(ctx,*(u32 *)*args,*(u32 *)args[1]);
  GetWarpPos__Fib(auStack_50,*puVar3,iVar1 != 0);
  __as__7FVectorFRC7FVector(uVar2,auStack_50);
  return 0;
}

/* ---- 0x00312400 size 0x11c  btlCharacterTargetMove(iiPPcPv)
 *      mangled: btlCharacterTargetMove__FiiPPcPv */
u64
btlCharacterTargetMove__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 uVar1;
  u32 uVar2;
  int iVar3;
  uint *puVar4;
  u32 *puVar5;
  u32 *puVar6;
  uint uVar7;
  u32 uVar8;
  
  uVar1 = *(u32 *)args[2];
  uVar2 = *(u32 *)args[3];
  uVar8 = *(u32 *)args[4];
  iVar3 = *(int *)args[5];
  puVar4 = (uint *)args[6];
  puVar5 = (u32 *)
           GetModelSet__10EffectCoreFii(ctx,*(u32 *)*args,*(u32 *)args[1]);
  puVar6 = (u32 *)GetModelSet__10EffectCoreFii(ctx,uVar1,uVar2);
  uVar7 = CharacterTargetMove__Fiifb(uVar8,*puVar5,*puVar6,iVar3 != 0);
  *puVar4 = uVar7 & 0xff;
  return 0;
}

/* ---- 0x00312520 size 0x1c4  btlGetWeponWorldPos(iiPPcPv)
 *      mangled: btlGetWeponWorldPos__FiiPPcPv */
u64
btlGetWeponWorldPos__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 uVar1;
  u32 uVar2;
  int iVar3;
  int iVar4;
  long lVar5;
  u8 auStack_60 [28];
  u32 uStack_44;
  u32 *puStack_20;
  u32 uStack_10;
  
  uStack_44 = *(u32 *)*args;
  iVar4 = *(int *)args[2];
  uVar1 = args[3];
  uVar2 = args[4];
  puStack_20 = args;
  uStack_10 = ctx;
  iVar3 = GetModelSet__10EffectCoreFii(ctx,uStack_44,*(u32 *)args[1]);
  lVar5 = 0;
  if (iVar4 == 1) {
    iVar4 = searchFrame__5FrameFPCc(*(u32 *)(*(int *)(iVar3 + 4) + 0x30),0x3fef90);
    if (*(int *)(iVar4 + 0x94) == 0) {
      return 0;
    }
    lVar5 = searchFrame__5FrameFPCc(*(u32 *)(iVar4 + 0x94),uVar1);
  }
  else if (iVar4 == 0) {
    iVar4 = searchFrame__5FrameFPCc(*(u32 *)(*(int *)(iVar3 + 4) + 0x30),0x3fef88);
    if (*(int *)(iVar4 + 0x94) == 0) {
      return 0;
    }
    lVar5 = searchFrame__5FrameFPCc(*(u32 *)(iVar4 + 0x94),uVar1);
  }
  if (lVar5 != 0) {
    getWorldPos__5FrameFi(auStack_60,lVar5,m_Env__8VIF1Prim & 1);
    __as__7FVectorFRC7FVector(uVar2,auStack_60);
  }
  return 0;
}

/* ---- 0x003126f0 size 0x1c4  btlGetWeponWorldRot(iiPPcPv)
 *      mangled: btlGetWeponWorldRot__FiiPPcPv */
u64
btlGetWeponWorldRot__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 uVar1;
  u32 uVar2;
  int iVar3;
  int iVar4;
  long lVar5;
  u8 auStack_90 [76];
  u32 uStack_44;
  u32 *puStack_20;
  u32 uStack_10;
  
  uStack_44 = *(u32 *)*args;
  iVar4 = *(int *)args[2];
  uVar1 = args[3];
  uVar2 = args[4];
  puStack_20 = args;
  uStack_10 = ctx;
  iVar3 = GetModelSet__10EffectCoreFii(ctx,uStack_44,*(u32 *)args[1]);
  lVar5 = 0;
  if (iVar4 == 1) {
    iVar4 = searchFrame__5FrameFPCc(*(u32 *)(*(int *)(iVar3 + 4) + 0x30),0x3fef90);
    if (*(int *)(iVar4 + 0x94) == 0) {
      return 0;
    }
    lVar5 = searchFrame__5FrameFPCc(*(u32 *)(iVar4 + 0x94),uVar1);
  }
  else if (iVar4 == 0) {
    iVar4 = searchFrame__5FrameFPCc(*(u32 *)(*(int *)(iVar3 + 4) + 0x30),0x3fef88);
    if (*(int *)(iVar4 + 0x94) == 0) {
      return 0;
    }
    lVar5 = searchFrame__5FrameFPCc(*(u32 *)(iVar4 + 0x94),uVar1);
  }
  if (lVar5 != 0) {
    getWorldRot__5FrameFi(auStack_90,lVar5,m_Env__8VIF1Prim & 1);
    __as__6MatrixFRC6Matrix(uVar2,auStack_90);
  }
  return 0;
}

/* ---- 0x003128c0 size 0x84  btlSetForceDeath(iiPPcPv)
 *      mangled: btlSetForceDeath__FiiPPcPv */
u64
btlSetForceDeath__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 *puVar1;
  
  puVar1 = (u32 *)
           GetModelSet__10EffectCoreFii(ctx,*(u32 *)*args,*(u32 *)args[1]);
  SetForceDeath__Fi(*puVar1);
  return 0;
}

/* ---- 0x00312950 size 0xcc  btlSetCharacterWallHitMode(iiPPcPv)
 *      mangled: btlSetCharacterWallHitMode__FiiPPcPv */
u64
btlSetCharacterWallHitMode__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  int iVar1;
  u32 *puVar2;
  
  iVar1 = *(int *)args[2];
  puVar2 = (u32 *)
           GetModelSet__10EffectCoreFii(ctx,*(u32 *)*args,*(u32 *)args[1]);
  SetCharacterWallHitMode__Fib(*puVar2,iVar1 != 0);
  return 0;
}

/* ---- 0x00312a20 size 0x94  btlMagicStartEffectCall2(iiPPcPv)
 *      mangled: btlMagicStartEffectCall2__FiiPPcPv */
u64
btlMagicStartEffectCall2__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  MagicStartEffectCall2__FiiP7FVectorff
            (*(u32 *)args[3],*(u32 *)args[4],*(u32 *)*args,
             *(u32 *)args[1],args[2]);
  return 0;
}

/* ---- 0x00312ac0 size 0x40  btlBeginMagicEffectClear2(iiPPcPv)
 *      mangled: btlBeginMagicEffectClear2__FiiPPcPv */
u64
btlBeginMagicEffectClear2__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  BeginMagicEffectClear2__Fi(*(u32 *)*args);
  return 0;
}

/* ---- 0x00312b00 size 0x3c  btlSetWait(iiPPcPv)
 *      mangled: btlSetWait__FiiPPcPv */
u64 btlSetWait__FiiPPcPv(void)

{
  int in_a3_lo;
  
  *(u8 *)(in_a3_lo + 0x24c) = 1;
  BattleNext__Fv();
  return 0;
}

/* ---- 0x00312b40 size 0x68  btlGetWait(iiPPcPv)
 *      mangled: btlGetWait__FiiPPcPv */
u64
btlGetWait__FiiPPcPv(u64 id,u64 argc,u32 *args,int ctx)

{
  *(uint *)*args = (uint)(*(char *)(ctx + 0x24c) != '\0');
  return 0;
}

/* ---- 0x00312bb0 size 0x2d0  btlSetTargetAngle(iiPPcPv)
 *      mangled: btlSetTargetAngle__FiiPPcPv */
u64
btlSetTargetAngle__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 uVar1;
  int iVar2;
  u32 uVar3;
  u32 *puVar4;
  u32 *puVar5;
  u64 uVar6;
  u64 uVar7;
  int iVar8;
  u8 auStack_d0 [64];
  u8 auStack_90 [16];
  u8 auStack_80 [96];
  u32 *puStack_20;
  u32 uStack_10;
  
  iVar8 = *(int *)*args;
  uVar1 = *(u32 *)args[1];
  iVar2 = *(int *)args[2];
  uVar3 = *(u32 *)args[3];
  puStack_20 = args;
  uStack_10 = ctx;
  if ((iVar8 == 2) || (iVar2 == 2)) {
    __ct__6MatrixFv(auStack_80);
    if (iVar8 == 2) {
      uVar6 = FindWorkModel__10EffectCoreFUi(ctx,uVar1);
      __as__6MatrixFRC6Matrix(auStack_80,(int)uVar6 + 0x560);
    }
    else {
      uVar6 = GetModel__10EffectCoreFiiii(ctx,iVar8,uVar1,0,0);
      __as__6MatrixFRC6Matrix(auStack_80,*(int *)((int)uVar6 + 0x30) + 0x160);
    }
    if (iVar2 == 2) {
      uVar7 = FindWorkModel__10EffectCoreFUi(ctx,uVar3);
    }
    else {
      uVar7 = GetModel__10EffectCoreFiiii(ctx,iVar2,uVar3,0,0);
    }
    GetTargetAngle__FP5ModelP5ModelP6Matrix(auStack_90,uVar6,uVar7,auStack_80);
    if (iVar8 == 2) {
      SetRot__11EffectModelFP7FVector(uVar6,auStack_90);
    }
    else {
      __ct__6MatrixFv(auStack_d0);
      RotMatrix__6MatrixFRC7FVector(auStack_d0,auStack_90);
      iVar8 = (int)uVar6;
      uVar6 = GetRight__6MatrixFv(*(int *)(iVar8 + 0x30) + 0x160);
      uVar7 = GetRight__6MatrixFv(auStack_d0);
      __as__7FVectorFRC7FVector(uVar6,uVar7);
      uVar6 = GetUp__6MatrixFv(*(int *)(iVar8 + 0x30) + 0x160);
      uVar7 = GetUp__6MatrixFv(auStack_d0);
      __as__7FVectorFRC7FVector(uVar6,uVar7);
      uVar6 = GetAt__6MatrixFv(*(int *)(iVar8 + 0x30) + 0x160);
      uVar7 = GetAt__6MatrixFv(auStack_d0);
      __as__7FVectorFRC7FVector(uVar6,uVar7);
      Frame::myMatrixUpdate__5FrameFv(*(Frame **)(iVar8 + 0x30));
    }
  }
  else {
    puVar4 = (u32 *)GetModelSet__10EffectCoreFii(ctx,iVar8,uVar1);
    puVar5 = (u32 *)GetModelSet__10EffectCoreFii(ctx,iVar2,uVar3);
    SetTargetAngle__7CBattleFii(Sys__7CBattle,*puVar4,*puVar5);
  }
  return 0;
}

/* ---- 0x00312e80 size 0xa4  btlGetModelNo(iiPPcPv)
 *      mangled: btlGetModelNo__FiiPPcPv */
u64
btlGetModelNo__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)args[2];
  iVar2 = GetModelSet__10EffectCoreFii(ctx,*(u32 *)*args,*(u32 *)args[1]);
  *piVar1 = (int)*(short *)(*(int *)(iVar2 + 8) + 0xdc);
  return 0;
}

/* ---- 0x00312f30 size 0x178  btlSetWeponModel(iiPPcPv)
 *      mangled: btlSetWeponModel__FiiPPcPv */
u64
btlSetWeponModel__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 uVar1;
  u32 uVar2;
  int iVar3;
  int iVar4;
  u32 *puVar5;
  u64 uVar6;
  u64 uVar7;
  u8 **ppuVar8;
  
  uVar1 = *(u32 *)*args;
  uVar2 = *(u32 *)args[1];
  iVar3 = *(int *)args[2];
  iVar4 = *(int *)args[4];
  uVar6 = FindWorkModel__10EffectCoreFUi(ctx,*(u32 *)args[3]);
  puVar5 = (u32 *)GetModelSet__10EffectCoreFii(ctx,uVar1,uVar2);
  if (iVar4 == 0) {
    unChainModel__5FrameFv(*(u32 *)(*(int *)((int)uVar6 + 0x30) + 0x1e0));
    WeaponShow__Fiib(*puVar5,iVar3,1);
  }
  else {
    WeaponShow__Fiib(*puVar5,iVar3,iVar4 == 0);
    if (iVar3 == 0) {
      ppuVar8 = &_6547;
    }
    else {
      ppuVar8 = (u8 **)&_6548;
    }
    uVar7 = searchFrame__5FrameFPCc(*(u32 *)(puVar5[1] + 0x30),ppuVar8);
    chainModel__5FrameFP5Model(uVar7,uVar6);
  }
  return 0;
}

/* ---- 0x003130b0 size 0x74  btlSetBGMParam(iiPPcPv)
 *      mangled: btlSetBGMParam__FiiPPcPv */
u64 btlSetBGMParam__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  SetBGMParam__6HNMSndFiii
            (sys__6HNMSnd,*(u32 *)*args,*(u32 *)args[1],
             *(u32 *)args[2]);
  return 0;
}

/* ---- 0x00313130 size 0x70  btlBattleCheck(iiPPcPv)
 *      mangled: btlBattleCheck__FiiPPcPv */
u64 btlBattleCheck__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  uint *puVar1;
  uint uVar2;
  
  puVar1 = (uint *)args[2];
  uVar2 = BattleCheck__Fii(*(u32 *)*args,*(u32 *)args[1]);
  *puVar1 = uVar2 & 0xff;
  return 0;
}

/* ---- 0x003131a0 size 0x134  colGetLightColor(iiPPcPv)
 *      mangled: colGetLightColor__FiiPPcPv */
u64 colGetLightColor__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = args[1];
  *(u32 *)*args = m_NumLight__12LightControl;
  iVar3 = 0;
  for (iVar2 = 0; iVar2 < 0x20; iVar2 = iVar2 + 1) {
    if ((long)((ulong)(byte)(&DAT_00413abe)[iVar2 * 0x80] << 0x3c) < 0) {
      *(int *)(iVar1 + iVar3 * 0x20) = iVar2;
      *(u32 *)(iVar1 + iVar3 * 0x20 + 4) = *(u32 *)(&DAT_00413ad0 + iVar2 * 0x80);
      *(u32 *)(iVar1 + iVar3 * 0x20 + 8) = *(u32 *)(&DAT_00413ad4 + iVar2 * 0x80);
      *(u32 *)(iVar1 + iVar3 * 0x20 + 0xc) = *(u32 *)(&DAT_00413ad8 + iVar2 * 0x80);
      *(u32 *)(iVar1 + iVar3 * 0x20 + 0x10) = *(u32 *)(&DAT_00413adc + iVar2 * 0x80);
      *(u32 *)(iVar1 + iVar3 * 0x20 + 0x14) = 0;
      iVar3 = iVar3 + 1;
    }
  }
  return 0;
}

/* ---- 0x003132e0 size 0xe0  colSetLightColor(iiPPcPv)
 *      mangled: colSetLightColor__FiiPPcPv */
u64 colSetLightColor__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  uint *puVar1;
  int iVar2;
  u64 uVar3;
  uint uVar4;
  u8 auStack_60 [16];
  u8 auStack_50 [48];
  u32 *puStack_20;
  
  puVar1 = (uint *)*args;
  iVar2 = args[1];
  puStack_20 = args;
  for (uVar4 = 0; uVar4 < *puVar1; uVar4 = uVar4 + 1) {
    __ct__7FVectorFffff(*(u32 *)(iVar2 + uVar4 * 0x20 + 4),
                        *(u32 *)(iVar2 + uVar4 * 0x20 + 8),
                        *(u32 *)(iVar2 + uVar4 * 0x20 + 0xc),
                        *(u32 *)(iVar2 + uVar4 * 0x20 + 0x10),auStack_50);
    uVar3 = __ct__7FVectorFRC7FVector(auStack_60,auStack_50);
    changeCol__9LightDataF7FVector
              (&m_Lights__12LightControl + *(int *)(iVar2 + uVar4 * 0x20) * 0x80,uVar3);
  }
  return 0;
}

/* ---- 0x00313400 size 0xa4  sprCreate(iiPPcPv)
 *      mangled: sprCreate__FiiPPcPv */
u64
sprCreate__FiiPPcPv(u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 uVar1;
  u32 uVar2;
  u32 *puVar3;
  u32 uVar4;
  u64 uVar5;
  
  uVar4 = *args;
  uVar1 = args[1];
  uVar2 = args[2];
  puVar3 = (u32 *)args[3];
  uVar5 = GetCore__3VECFv(ctx);
  uVar4 = CreateSprite__10EffectCoreFP7FVectorP7FVectorP7FVectorP7FVectorP7FVectori
                    (uVar5,uVar4,uVar1,uVar2,0,0,0);
  *puVar3 = uVar4;
  return 0;
}

/* ---- 0x003134b0 size 0xe8  sprShow(iiPPcPv)
 *      mangled: sprShow__FiiPPcPv */
u64
sprShow__FiiPPcPv(u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 *puVar1;
  int *piVar2;
  int *piVar3;
  VIF1Prim *prim;
  int iVar4;
  u64 uVar5;
  
  puVar1 = (u32 *)*args;
  piVar2 = (int *)args[1];
  piVar3 = (int *)args[2];
  uVar5 = GetCore__3VECFv(ctx);
  prim = (VIF1Prim *)FindSprite__10EffectCoreFUi(uVar5,*puVar1);
  if (*piVar2 == 0) {
    ReleaseOT__5WorldFP8VIF1Prim((World *)&m_World__4CApp,prim);
  }
  else {
    iVar4 = FindOT__5WorldFP8VIF1Prim((World *)&m_World__4CApp,prim);
    if (iVar4 == 0) {
      AddOT__5WorldFiP8VIF1Prim((World *)&m_World__4CApp,*piVar3,prim);
    }
  }
  return 0;
}

/* ---- 0x003135a0 size 0x88  sprSetColor(iiPPcPv)
 *      mangled: sprSetColor__FiiPPcPv */
u64
sprSetColor__FiiPPcPv(u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 *puVar1;
  u32 uVar2;
  int iVar3;
  u64 uVar4;
  
  puVar1 = (u32 *)*args;
  uVar2 = args[1];
  uVar4 = GetCore__3VECFv(ctx);
  iVar3 = FindSprite__10EffectCoreFUi(uVar4,*puVar1);
  __as__7FVectorFRC7FVector(iVar3 + 0x40,uVar2);
  return 0;
}

/* ---- 0x00313630 size 0x98  sprDelete(iiPPcPv)
 *      mangled: sprDelete__FiiPPcPv */
u64
sprDelete__FiiPPcPv(u64 id,u64 argc,u32 *args,u32 ctx)

{
  u64 uVar1;
  u64 uVar2;
  
  args = (u32 *)*args;
  uVar1 = GetCore__3VECFv(ctx);
  uVar1 = FindSprite__10EffectCoreFUi(uVar1,*args);
  ReleaseOT__5WorldFP8VIF1Prim((World *)&m_World__4CApp,(VIF1Prim *)uVar1);
  uVar2 = GetCore__3VECFv(ctx);
  DeleteSprite__10EffectCoreFP12EffectSprite(uVar2,uVar1);
  return 0;
}

/* ---- 0x003136d0 size 0x90  sprSetZ(iiPPcPv)
 *      mangled: sprSetZ__FiiPPcPv */
u64
sprSetZ__FiiPPcPv(u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 *puVar1;
  u32 *puVar2;
  VIF1Prim *this;
  u64 uVar3;
  
  puVar1 = (u32 *)*args;
  puVar2 = (u32 *)args[1];
  uVar3 = GetCore__3VECFv(ctx);
  this = (VIF1Prim *)FindSprite__10EffectCoreFUi(uVar3,*puVar1);
  setZvolume__8VIF1PrimFs(this,(short)*puVar2);
  return 0;
}

/* ---- 0x00313760 size 0x184  sprSetTestReg(iiPPcPv)
 *      mangled: sprSetTestReg__FiiPPcPv */
u64
sprSetTestReg__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  u64 uVar11;
  
  puVar1 = (u32 *)*args;
  iVar2 = *(int *)args[1];
  iVar3 = *(int *)args[2];
  iVar4 = *(int *)args[3];
  iVar5 = *(int *)args[4];
  iVar6 = *(int *)args[5];
  iVar7 = *(int *)args[6];
  iVar8 = *(int *)args[7];
  iVar9 = *(int *)args[8];
  uVar11 = GetCore__3VECFv(ctx);
  iVar10 = FindSprite__10EffectCoreFUi(uVar11,*puVar1);
  *(long *)(iVar10 + 0x78) =
       (long)iVar9 << 0x11 |
       (long)iVar8 << 0x10 |
       (long)iVar7 << 0xf |
       (long)iVar6 << 0xe | (long)iVar5 << 0xc | (long)iVar4 << 4 | (long)iVar2 | (long)iVar3 << 1;
  return 0;
}

/* ---- 0x003138f0 size 0x118  sprSetAlphaReg(iiPPcPv)
 *      mangled: sprSetAlphaReg__FiiPPcPv */
u64
sprSetAlphaReg__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  u64 uVar8;
  
  puVar1 = (u32 *)*args;
  iVar2 = *(int *)args[1];
  iVar3 = *(int *)args[2];
  iVar4 = *(int *)args[3];
  iVar5 = *(int *)args[4];
  iVar6 = *(int *)args[5];
  uVar8 = GetCore__3VECFv(ctx);
  iVar7 = FindSprite__10EffectCoreFUi(uVar8,*puVar1);
  *(long *)(iVar7 + 0x80) =
       (long)iVar6 << 0x20 | (long)iVar5 << 6 | (long)iVar4 << 4 | (long)iVar2 | (long)iVar3 << 2;
  return 0;
}

/* ---- 0x003149e0 size 0x138  shrGetModelColor(iiPPcPv)
 *      mangled: shrGetModelColor__FiiPPcPv */
u64
shrGetModelColor__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  int *piVar1;
  u32 *puVar2;
  u32 uVar3;
  int iVar4;
  u64 uVar5;
  u8 auStack_50 [48];
  u32 *puStack_20;
  u32 uStack_10;
  
  piVar1 = (int *)*args;
  puVar2 = (u32 *)args[1];
  uVar3 = args[2];
  uVar5 = 0;
  iVar4 = *piVar1;
  puStack_20 = args;
  uStack_10 = ctx;
  if (iVar4 == 3) {
    uVar5 = GetBattleBgModel__Fv();
  }
  else if (iVar4 == 2) {
    uVar5 = GetCore__3VECFv(ctx);
    uVar5 = FindWorkModel__10EffectCoreFUi(uVar5,*puVar2);
  }
  else if ((iVar4 == 1) || (iVar4 == 0)) {
    uVar5 = GetCore__3VECFv(ctx);
    uVar5 = GetModel__10EffectCoreFiiii(uVar5,*piVar1,*puVar2,0,0);
  }
  getModelColor__5ModelFv(auStack_50,uVar5);
  __as__7FVectorFRC7FVector(uVar3,auStack_50);
  return 0;
}

/* ---- 0x00314b20 size 0x128  shrSetModelColor(iiPPcPv)
 *      mangled: shrSetModelColor__FiiPPcPv */
u64
shrSetModelColor__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  int *piVar1;
  u32 *puVar2;
  u32 uVar3;
  int iVar4;
  u64 uVar5;
  
  piVar1 = (int *)*args;
  puVar2 = (u32 *)args[1];
  uVar3 = args[2];
  uVar5 = 0;
  iVar4 = *piVar1;
  if (iVar4 == 3) {
    uVar5 = GetBattleBgModel__Fv();
  }
  else if (iVar4 == 2) {
    uVar5 = GetCore__3VECFv(ctx);
    uVar5 = FindWorkModel__10EffectCoreFUi(uVar5,*puVar2);
  }
  else if ((iVar4 == 1) || (iVar4 == 0)) {
    uVar5 = GetCore__3VECFv(ctx);
    uVar5 = GetModel__10EffectCoreFiiii(uVar5,*piVar1,*puVar2,0,0);
  }
  setModelColor__5ModelFR7FVector(uVar5,uVar3);
  return 0;
}

/* ---- 0x00314c50 size 0x19c  shrStartModelColorFader(iiPPcPv)
 *      mangled: shrStartModelColorFader__FiiPPcPv */
u64
shrStartModelColorFader__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  int *piVar1;
  u32 *puVar2;
  u32 uVar3;
  u32 *puVar4;
  int iVar5;
  long lVar6;
  u64 uVar7;
  u64 uVar8;
  
  piVar1 = (int *)*args;
  puVar2 = (u32 *)args[1];
  uVar3 = args[2];
  puVar4 = (u32 *)args[3];
  uVar8 = 0;
  iVar5 = *piVar1;
  if (iVar5 == 3) {
    uVar8 = GetBattleBgModel__Fv();
  }
  else if (iVar5 == 2) {
    uVar8 = GetCore__3VECFv(ctx);
    uVar8 = FindWorkModel__10EffectCoreFUi(uVar8,*puVar2);
  }
  else if ((iVar5 == 1) || (iVar5 == 0)) {
    uVar8 = GetCore__3VECFv(ctx);
    uVar8 = GetModel__10EffectCoreFiiii(uVar8,*piVar1,*puVar2,0,0);
  }
  lVar6 = __nw__FUi(0x40);
  uVar7 = 0;
  if (lVar6 != 0) {
    uVar7 = __ct__10ModelFaderFP5ModelR7FVectorib(lVar6,uVar8,uVar3,*puVar4,1);
  }
  if (m_Fader__10EffectCore == 0) {
    m_Fader__10EffectCore = (int)uVar7;
  }
  else {
    Add__5CListFP5CList(m_Fader__10EffectCore,uVar7);
  }
  return 0;
}

/* ---- 0x00314df0 size 0x1a4  shrStartModelAlphaFader(iiPPcPv)
 *      mangled: shrStartModelAlphaFader__FiiPPcPv */
u64
shrStartModelAlphaFader__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 *puVar1;
  u32 *puVar2;
  int iVar3;
  long lVar4;
  u64 uVar5;
  u64 uVar6;
  u8 auStack_50 [48];
  u32 *puStack_20;
  u32 uStack_10;
  
  puVar1 = (u32 *)args[2];
  puVar2 = (u32 *)args[3];
  uVar6 = 0;
  iVar3 = *(int *)*args;
  puStack_20 = args;
  uStack_10 = ctx;
  if (iVar3 == 3) {
    uVar6 = GetBattleBgModel__Fv();
  }
  else if (iVar3 == 2) {
    uVar6 = FindWorkModel__10EffectCoreFUi(ctx,*(u32 *)args[1]);
  }
  else if ((iVar3 == 1) || (iVar3 == 0)) {
    uVar6 = GetModel__10EffectCoreFiiii(ctx,*(int *)*args,*(u32 *)args[1],0,0);
  }
  __ct__7FVectorFffff(0,0,0,*puVar1,auStack_50);
  lVar4 = __nw__FUi(0x40);
  uVar5 = 0;
  if (lVar4 != 0) {
    uVar5 = __ct__10ModelFaderFP5ModelR7FVectorib(lVar4,uVar6,auStack_50,*puVar2,0);
  }
  if (m_Fader__10EffectCore == 0) {
    m_Fader__10EffectCore = (int)uVar5;
  }
  else {
    Add__5CListFP5CList(m_Fader__10EffectCore,uVar5);
  }
  return 0;
}

/* ---- 0x00314fa0 size 0x158  shrSetModelRootMatrix(iiPPcPv)
 *      mangled: shrSetModelRootMatrix__FiiPPcPv */
u64
shrSetModelRootMatrix__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  int *piVar1;
  u32 *puVar2;
  u32 uVar3;
  int iVar4;
  int iVar5;
  u64 uVar6;
  
  piVar1 = (int *)*args;
  puVar2 = (u32 *)args[1];
  uVar3 = args[2];
  iVar5 = 0;
  iVar4 = *piVar1;
  if (iVar4 == 3) {
    iVar5 = GetBattleBgModel__Fv();
  }
  else {
    if (iVar4 == 2) {
      uVar6 = GetCore__3VECFv(ctx);
      uVar6 = FindWorkModel__10EffectCoreFUi(uVar6,*puVar2);
      SetMatrix__11EffectModelFP6Matrix(uVar6,uVar3);
      return 0;
    }
    if ((iVar4 == 1) || (iVar4 == 0)) {
      uVar6 = GetCore__3VECFv(ctx);
      iVar5 = GetModel__10EffectCoreFiiii(uVar6,*piVar1,*puVar2,0,0);
    }
  }
  __as__6MatrixFRC6Matrix(*(int *)(iVar5 + 0x30) + 0x160,uVar3);
  Frame::myMatrixUpdate__5FrameFv(*(Frame **)(iVar5 + 0x30));
  return 0;
}

/* ---- 0x00315100 size 0x12c  shrGetModelRootMatrix(iiPPcPv)
 *      mangled: shrGetModelRootMatrix__FiiPPcPv */
u64
shrGetModelRootMatrix__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  int *piVar1;
  u32 *puVar2;
  u32 uVar3;
  int iVar4;
  int iVar5;
  u64 uVar6;
  
  piVar1 = (int *)*args;
  puVar2 = (u32 *)args[1];
  uVar3 = args[2];
  iVar5 = 0;
  iVar4 = *piVar1;
  if (iVar4 == 3) {
    iVar5 = GetBattleBgModel__Fv();
  }
  else if (iVar4 == 2) {
    uVar6 = GetCore__3VECFv(ctx);
    iVar5 = FindWorkModel__10EffectCoreFUi(uVar6,*puVar2);
  }
  else if ((iVar4 == 1) || (iVar4 == 0)) {
    uVar6 = GetCore__3VECFv(ctx);
    iVar5 = GetModel__10EffectCoreFiiii(uVar6,*piVar1,*puVar2,0,0);
  }
  __as__6MatrixFRC6Matrix(uVar3,*(int *)(iVar5 + 0x30) + 0x160);
  return 0;
}

/* ---- 0x00315230 size 0x18c  shrGetWorldPos(iiPPcPv)
 *      mangled: shrGetWorldPos__FiiPPcPv */
u64
shrGetWorldPos__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  int *piVar1;
  u32 *puVar2;
  u32 uVar3;
  u32 uVar4;
  int iVar5;
  int iVar6;
  u64 uVar7;
  u8 auStack_50 [48];
  u32 *puStack_20;
  u32 uStack_10;
  
  piVar1 = (int *)*args;
  puVar2 = (u32 *)args[1];
  uVar3 = args[2];
  uVar4 = args[3];
  iVar6 = 0;
  iVar5 = *piVar1;
  puStack_20 = args;
  uStack_10 = ctx;
  if (iVar5 == 4) {
    iVar6 = CheckLsdModel__FP5Model(*puVar2);
  }
  else if (iVar5 == 3) {
    iVar6 = GetBattleBgModel__Fv();
  }
  else if (iVar5 == 2) {
    uVar7 = GetCore__3VECFv(ctx);
    iVar6 = FindWorkModel__10EffectCoreFUi(uVar7,*puVar2);
  }
  else if ((iVar5 == 1) || (iVar5 == 0)) {
    uVar7 = GetCore__3VECFv(ctx);
    iVar6 = GetModel__10EffectCoreFiiii(uVar7,*piVar1,*puVar2,0,0);
  }
  uVar7 = searchFrame__5FrameFPCc(*(u32 *)(iVar6 + 0x30),uVar3);
  getWorldPos__5FrameFi(auStack_50,uVar7,m_Env__8VIF1Prim & 1);
  __as__7FVectorFRC7FVector(uVar4,auStack_50);
  return 0;
}

/* ---- 0x003153c0 size 0x18c  shrGetWorldRot(iiPPcPv)
 *      mangled: shrGetWorldRot__FiiPPcPv */
u64
shrGetWorldRot__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  int *piVar1;
  u32 *puVar2;
  u32 uVar3;
  u32 uVar4;
  int iVar5;
  int iVar6;
  u64 uVar7;
  u8 auStack_80 [96];
  u32 *puStack_20;
  u32 uStack_10;
  
  piVar1 = (int *)*args;
  puVar2 = (u32 *)args[1];
  uVar3 = args[2];
  uVar4 = args[3];
  iVar6 = 0;
  iVar5 = *piVar1;
  puStack_20 = args;
  uStack_10 = ctx;
  if (iVar5 == 4) {
    iVar6 = CheckLsdModel__FP5Model(*puVar2);
  }
  else if (iVar5 == 3) {
    iVar6 = GetBattleBgModel__Fv();
  }
  else if (iVar5 == 2) {
    uVar7 = GetCore__3VECFv(ctx);
    iVar6 = FindWorkModel__10EffectCoreFUi(uVar7,*puVar2);
  }
  else if ((iVar5 == 1) || (iVar5 == 0)) {
    uVar7 = GetCore__3VECFv(ctx);
    iVar6 = GetModel__10EffectCoreFiiii(uVar7,*piVar1,*puVar2,0,0);
  }
  uVar7 = searchFrame__5FrameFPCc(*(u32 *)(iVar6 + 0x30),uVar3);
  getWorldRot__5FrameFi(auStack_80,uVar7,m_Env__8VIF1Prim & 1);
  __as__6MatrixFRC6Matrix(uVar4,auStack_80);
  return 0;
}

/* ---- 0x00315550 size 0x178  shrGetBackColor(iiPPcPv)
 *      mangled: shrGetBackColor__FiiPPcPv */
u64 shrGetBackColor__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  byte bVar1;
  u32 uVar2;
  float *pfVar3;
  
  uVar2 = *args;
  bVar1 = *(byte *)(camera__4CApp + 0x180);
  pfVar3 = (float *)vx__7FVectorFv(uVar2);
  *pfVar3 = (float)bVar1;
  bVar1 = *(byte *)(camera__4CApp + 0x181);
  pfVar3 = (float *)vy__7FVectorFv(uVar2);
  *pfVar3 = (float)bVar1;
  bVar1 = *(byte *)(camera__4CApp + 0x182);
  pfVar3 = (float *)vz__7FVectorFv(uVar2);
  *pfVar3 = (float)bVar1;
  bVar1 = *(byte *)(camera__4CApp + 0x183);
  pfVar3 = (float *)vw__7FVectorFv(uVar2);
  *pfVar3 = (float)bVar1;
  return 0;
}

/* ---- 0x003156d0 size 0x18c  shrSetBackColor(iiPPcPv)
 *      mangled: shrSetBackColor__FiiPPcPv */
u64 shrSetBackColor__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  u32 uVar1;
  float *pfVar2;
  float fVar3;
  u8 uStack_44;
  u8 uStack_43;
  u8 uStack_42;
  u8 uStack_41;
  u32 *puStack_20;
  
  uVar1 = *args;
  puStack_20 = args;
  __ct__7_rgba32Fv(&uStack_44);
  pfVar2 = (float *)vx__7FVectorFv(uVar1);
  fVar3 = *pfVar2;
  if (fVar3 < 2.1474836e+09) {
    uStack_44 = (u8)(int)fVar3;
  }
  else {
    uStack_44 = (u8)(int)(fVar3 - 2.1474836e+09);
  }
  pfVar2 = (float *)vy__7FVectorFv(uVar1);
  fVar3 = *pfVar2;
  if (fVar3 < 2.1474836e+09) {
    uStack_43 = (u8)(int)fVar3;
  }
  else {
    uStack_43 = (u8)(int)(fVar3 - 2.1474836e+09);
  }
  pfVar2 = (float *)vz__7FVectorFv(uVar1);
  fVar3 = *pfVar2;
  if (fVar3 < 2.1474836e+09) {
    uStack_42 = (u8)(int)fVar3;
  }
  else {
    uStack_42 = (u8)(int)(fVar3 - 2.1474836e+09);
  }
  pfVar2 = (float *)vw__7FVectorFv(uVar1);
  fVar3 = *pfVar2;
  if (fVar3 < 2.1474836e+09) {
    uStack_41 = (u8)(int)fVar3;
  }
  else {
    uStack_41 = (u8)(int)(fVar3 - 2.1474836e+09);
  }
  SetBgColor__9GsxCameraFRC7_rgba32(camera__4CApp,&uStack_44);
  return 0;
}

/* ---- 0x00315860 size 0xec  shrSetNextMotion(iiPPcPv)
 *      mangled: shrSetNextMotion__FiiPPcPv */
u64
shrSetNextMotion__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 uVar1;
  int iVar2;
  u64 uVar3;
  
  uVar1 = args[2];
  uVar3 = 0;
  iVar2 = *(int *)*args;
  if (iVar2 == 2) {
    uVar3 = FindWorkModel__10EffectCoreFUi(ctx,*(u32 *)args[1]);
  }
  else if ((iVar2 == 1) || (iVar2 == 0)) {
    uVar3 = GetModel__10EffectCoreFiiii(ctx,*(int *)*args,*(u32 *)args[1],0,0);
  }
  setNextMotion__5ModelFPCcUs(uVar3,uVar1,1);
  return 0;
}

/* ---- 0x00315950 size 0x64  quaGetQuat(iiPPcPv)
 *      mangled: quaGetQuat__FiiPPcPv */
u64 quaGetQuat__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  u32 uVar1;
  u64 uVar2;
  u8 auStack_60 [16];
  u8 auStack_50 [48];
  u32 *puStack_20;
  
  uVar1 = args[1];
  puStack_20 = args;
  uVar2 = __ct__10QuaternionFP6Matrix(auStack_60,*args);
  __as__10QuaternionFRC10Quaternion(auStack_50,uVar1,uVar2);
  return 0;
}

/* ---- 0x003159c0 size 0x78  quaSlerp(iiPPcPv)
 *      mangled: quaSlerp__FiiPPcPv */
u64 quaSlerp__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  slerp__10QuaternionFR10QuaternionRC10Quaternionf
            (*(u32 *)args[2],*args,args[3],args[1]);
  return 0;
}

/* ---- 0x00315a40 size 0x5c  quaGetMatrix(iiPPcPv)
 *      mangled: quaGetMatrix__FiiPPcPv */
u64 quaGetMatrix__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  u32 uVar1;
  u32 uVar2;
  
  uVar1 = *args;
  uVar2 = args[1];
  UnitMatrix__6MatrixFv(uVar2);
  getMatrix__10QuaternionFPf(uVar1,uVar2);
  return 0;
}

/* ---- 0x00317a50 size 0xb8  pgrCreate(iiPPcPv)
 *      mangled: pgrCreate__FiiPPcPv */
u64
pgrCreate__FiiPPcPv(u64 id,u64 argc,u32 *args,u32 ctx)

{
  int iVar1;
  long lVar2;
  u64 uVar3;
  
  args = (u32 *)*args;
  iVar1 = GetCore__3VECFv(ctx);
  lVar2 = __nw__FUi(0x110);
  uVar3 = 0;
  if (lVar2 != 0) {
    uVar3 = __ct__8PolGroupFv(lVar2);
  }
  Create__8PolGroupFv(uVar3);
  *args = (int)uVar3;
  AddGroup__9PolPacketFiP8PolGroup(*(u32 *)(iVar1 + 0x14),0,uVar3);
  return 0;
}

/* ---- 0x00317b10 size 0x94  pgrSetTrans(iiPPcPv)
 *      mangled: pgrSetTrans__FiiPPcPv */
u64 pgrSetTrans__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  u32 uVar1;
  u8 auStack_60 [20];
  u32 uStack_4c;
  u32 uStack_48;
  u32 uStack_44;
  u32 *puStack_20;
  
  uVar1 = *(u32 *)*args;
  uStack_44 = *(u32 *)args[1];
  uStack_48 = *(u32 *)args[2];
  uStack_4c = *(u32 *)args[3];
  puStack_20 = args;
  __ct__7FVectorFffff(uStack_44,uStack_48,uStack_4c,0x3f800000,auStack_60);
  SetTrans__8PolGroupFP7FVector(uVar1,auStack_60);
  return 0;
}

/* ---- 0x00317bb0 size 0x94  pgrSetRot(iiPPcPv)
 *      mangled: pgrSetRot__FiiPPcPv */
u64 pgrSetRot__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  u32 uVar1;
  u8 auStack_60 [20];
  u32 uStack_4c;
  u32 uStack_48;
  u32 uStack_44;
  u32 *puStack_20;
  
  uVar1 = *(u32 *)*args;
  uStack_44 = *(u32 *)args[1];
  uStack_48 = *(u32 *)args[2];
  uStack_4c = *(u32 *)args[3];
  puStack_20 = args;
  __ct__7FVectorFffff(uStack_44,uStack_48,uStack_4c,0x3f800000,auStack_60);
  SetRot__8PolGroupFP7FVector(uVar1,auStack_60);
  return 0;
}

/* ---- 0x00317c50 size 0x54  pgrSetMatrix(iiPPcPv)
 *      mangled: pgrSetMatrix__FiiPPcPv */
u64 pgrSetMatrix__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  SetMatrix__8PolGroupFP6Matrix(*(u32 *)*args,args[1]);
  return 0;
}

/* ---- 0x00317cb0 size 0x58  pgrSetTexture(iiPPcPv)
 *      mangled: pgrSetTexture__FiiPPcPv */
u64 pgrSetTexture__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  SetTexture__8PolGroupFi(*(u32 *)*args,*(u32 *)args[1]);
  return 0;
}

/* ---- 0x00317d10 size 0x100  pgrSetTestReg(iiPPcPv)
 *      mangled: pgrSetTestReg__FiiPPcPv */
u64 pgrSetTestReg__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  SetTestReg__8PolGroupFiiiiiiii
            (*(u32 *)*args,*(u32 *)args[1],*(u32 *)args[2],
             *(u32 *)args[3],*(u32 *)args[4],*(u32 *)args[5],
             *(u32 *)args[6],*(u32 *)args[7]);
  return 0;
}

/* ---- 0x00317e10 size 0xb8  pgrSetAlphaReg(iiPPcPv)
 *      mangled: pgrSetAlphaReg__FiiPPcPv */
u64 pgrSetAlphaReg__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  SetAlphaReg__8PolGroupFiiiii
            (*(u32 *)*args,*(u32 *)args[1],*(u32 *)args[2],
             *(u32 *)args[3],*(u32 *)args[4],*(u32 *)args[5]);
  return 0;
}

/* ---- 0x00317ed0 size 0x84  pgrShow(iiPPcPv)
 *      mangled: pgrShow__FiiPPcPv */
u64
pgrShow__FiiPPcPv(u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 uVar1;
  u32 uVar2;
  int iVar3;
  
  uVar1 = *(u32 *)*args;
  uVar2 = *(u32 *)args[1];
  iVar3 = GetCore__3VECFv(ctx);
  Show__9PolPacketFiP8PolGroup(*(u32 *)(iVar3 + 0x14),uVar2,uVar1);
  return 0;
}

/* ---- 0x00317f60 size 0x70  pgrSetLayer(iiPPcPv)
 *      mangled: pgrSetLayer__FiiPPcPv */
u64
pgrSetLayer__FiiPPcPv(u64 id,u64 argc,u32 *args,int ctx)

{
  int layer;
  
  layer = *(int *)*args;
  ReleaseOT__5WorldFP8VIF1Prim((World *)&m_World__4CApp,*(VIF1Prim **)(ctx + 0x14));
  AddOT__5WorldFiP8VIF1Prim((World *)&m_World__4CApp,layer,*(VIF1Prim **)(ctx + 0x14));
  return 0;
}

/* ---- 0x00317fd0 size 0xd0  pgrSetClampReg(iiPPcPv)
 *      mangled: pgrSetClampReg__FiiPPcPv */
u64 pgrSetClampReg__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  SetClampReg__8PolGroupFiiiiii
            (*(u32 *)*args,*(u32 *)args[1],*(u32 *)args[2],
             *(u32 *)args[3],*(u32 *)args[4],*(u32 *)args[5],
             *(u32 *)args[6]);
  return 0;
}

/* ---- 0x00318fa0 size 0x94  polCreate3D(iiPPcPv)
 *      mangled: polCreate3D__FiiPPcPv */
u64 polCreate3D__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  u32 uVar1;
  u32 *puVar2;
  long lVar3;
  u64 uVar4;
  
  uVar1 = *(u32 *)*args;
  puVar2 = (u32 *)args[1];
  lVar3 = __nw__FUi(0x290);
  uVar4 = 0;
  if (lVar3 != 0) {
    uVar4 = __ct__7PolDataFv(lVar3);
  }
  AddData__8PolGroupFP7PolData(uVar1,uVar4);
  *puVar2 = (int)uVar4;
  return 0;
}

/* ---- 0x00319040 size 0x94  polCreateBB(iiPPcPv)
 *      mangled: polCreateBB__FiiPPcPv */
u64 polCreateBB__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  u32 uVar1;
  u32 *puVar2;
  long lVar3;
  u64 uVar4;
  
  uVar1 = *(u32 *)*args;
  puVar2 = (u32 *)args[1];
  lVar3 = __nw__FUi(0x2a0);
  uVar4 = 0;
  if (lVar3 != 0) {
    uVar4 = __ct__9BbPolDataFv(lVar3);
  }
  AddData__8PolGroupFP7PolData(uVar1,uVar4);
  *puVar2 = (int)uVar4;
  return 0;
}

/* ---- 0x003190e0 size 0x94  polCreateDirect(iiPPcPv)
 *      mangled: polCreateDirect__FiiPPcPv */
u64 polCreateDirect__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  u32 uVar1;
  u32 *puVar2;
  long lVar3;
  u64 uVar4;
  
  uVar1 = *(u32 *)*args;
  puVar2 = (u32 *)args[1];
  lVar3 = __nw__FUi(0x2a0);
  uVar4 = 0;
  if (lVar3 != 0) {
    uVar4 = __ct__13DirectPolDataFv(lVar3);
  }
  AddData__8PolGroupFP7PolData(uVar1,uVar4);
  *puVar2 = (int)uVar4;
  return 0;
}

/* ---- 0x00319180 size 0x84  polSetRot(iiPPcPv)
 *      mangled: polSetRot__FiiPPcPv */
u64 polSetRot__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  (**(code **)(*(int *)(*(int *)*args + 0x280) + 0xc))
            (*(u32 *)args[1],*(u32 *)args[2],*(u32 *)args[3]);
  return 0;
}

/* ---- 0x00319210 size 0x84  polSetCenter(iiPPcPv)
 *      mangled: polSetCenter__FiiPPcPv */
u64 polSetCenter__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  (**(code **)(*(int *)(*(int *)*args + 0x280) + 0x10))
            (*(u32 *)args[1],*(u32 *)args[2],*(u32 *)args[3]);
  return 0;
}

/* ---- 0x003192a0 size 0x70  polSetVertex(iiPPcPv)
 *      mangled: polSetVertex__FiiPPcPv */
u64 polSetVertex__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  (**(code **)(*(int *)(*(int *)*args + 0x280) + 0x14))
            (*(u32 *)args[1],*(u32 *)args[2]);
  return 0;
}

/* ---- 0x00319310 size 0x88  polSetSt(iiPPcPv)
 *      mangled: polSetSt__FiiPPcPv */
u64 polSetSt__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  (**(code **)(*(int *)(*(int *)*args + 0x280) + 0x18))
            (*(u32 *)args[2],*(u32 *)args[3],*(int *)*args,
             *(u32 *)args[1]);
  return 0;
}

/* ---- 0x003193a0 size 0xb0  polSetColor(iiPPcPv)
 *      mangled: polSetColor__FiiPPcPv */
u64 polSetColor__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  (**(code **)(*(int *)(*(int *)*args + 0x280) + 0x1c))
            (*(u32 *)args[2],*(u32 *)args[3],*(u32 *)args[4],
             *(u32 *)args[5],*(int *)*args,*(u32 *)args[1]);
  return 0;
}

/* ---- 0x00319450 size 0x40  polDelete(iiPPcPv)
 *      mangled: polDelete__FiiPPcPv */
u64 polDelete__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  DelayDelete__7PolDataFv(*(u32 *)*args);
  return 0;
}

/* ---- 0x0031a040 size 0xa8  lgtCreate(iiPPcPv)
 *      mangled: lgtCreate__FiiPPcPv */
u64
lgtCreate__FiiPPcPv(u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 *puVar1;
  int *piVar2;
  u32 *puVar3;
  u64 uVar4;
  
  puVar1 = (u32 *)*args;
  piVar2 = (int *)args[1];
  puVar3 = (u32 *)args[2];
  uVar4 = GetCore__3VECFv(ctx);
  uVar4 = CreateLight__10EffectCoreFi(uVar4,*puVar1);
  LightOn__11EffectLightFb(uVar4,*piVar2 != 0);
  *puVar3 = (int)uVar4;
  return 0;
}

/* ---- 0x0031a0f0 size 0x94  lgtShow(iiPPcPv)
 *      mangled: lgtShow__FiiPPcPv */
u64
lgtShow__FiiPPcPv(u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 *puVar1;
  int *piVar2;
  u64 uVar3;
  
  puVar1 = (u32 *)*args;
  piVar2 = (int *)args[1];
  uVar3 = GetCore__3VECFv(ctx);
  uVar3 = FindLight__10EffectCoreFUi(uVar3,*puVar1);
  LightOn__11EffectLightFb(uVar3,*piVar2 != 0);
  return 0;
}

/* ---- 0x0031a190 size 0x14c  lgtAttach(iiPPcPv)
 *      mangled: lgtAttach__FiiPPcPv */
u64
lgtAttach__FiiPPcPv(u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 *puVar1;
  int *piVar2;
  u32 *puVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  u32 uVar7;
  u64 uVar8;
  
  puVar1 = (u32 *)*args;
  piVar2 = (int *)args[1];
  puVar3 = (u32 *)args[2];
  uVar7 = args[3];
  iVar6 = 0;
  uVar8 = GetCore__3VECFv(ctx);
  iVar5 = FindLight__10EffectCoreFUi(uVar8,*puVar1);
  iVar4 = *piVar2;
  if (iVar4 == 2) {
    uVar8 = GetCore__3VECFv(ctx);
    iVar6 = FindWorkModel__10EffectCoreFUi(uVar8,*puVar3);
  }
  else if ((iVar4 == 0) || (iVar4 == 1)) {
    uVar8 = GetCore__3VECFv(ctx);
    iVar6 = GetModel__10EffectCoreFiiii(uVar8,*piVar2,*puVar3,0,0);
  }
  uVar7 = searchFrame__5FrameFPCc(*(u32 *)(iVar6 + 0x30),uVar7);
  *(u32 *)(iVar5 + 0xc) = uVar7;
  return 0;
}

/* ---- 0x0031a2e0 size 0x88  lgtSetOffset(iiPPcPv)
 *      mangled: lgtSetOffset__FiiPPcPv */
u64
lgtSetOffset__FiiPPcPv(u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 *puVar1;
  u32 uVar2;
  int iVar3;
  u64 uVar4;
  
  puVar1 = (u32 *)*args;
  uVar2 = args[1];
  uVar4 = GetCore__3VECFv(ctx);
  iVar3 = FindLight__10EffectCoreFUi(uVar4,*puVar1);
  __as__7FVectorFRC7FVector(iVar3 + 0x10,uVar2);
  return 0;
}

/* ---- 0x0031a370 size 0xd0  lgtDelete(iiPPcPv)
 *      mangled: lgtDelete__FiiPPcPv */
u64
lgtDelete__FiiPPcPv(u64 id,u64 argc,u32 *args,int ctx)

{
  int iVar1;
  int iVar2;
  u64 uVar3;
  
  uVar3 = FindLight__10EffectCoreFUi(ctx,*(u32 *)*args);
  iVar2 = FindLightIndex__10EffectCoreFP11EffectLight(ctx,uVar3);
  if (*(int *)(ctx + iVar2 * 4 + 0x374) != 0) {
    iVar1 = *(int *)(ctx + iVar2 * 4 + 0x374);
    if (iVar1 != 0) {
      (**(code **)(*(int *)(iVar1 + 0x20) + 0x10))(iVar1,1);
    }
    *(u32 *)(ctx + iVar2 * 4 + 0x374) = 0;
  }
  return 0;
}

/* ---- 0x0031a440 size 0x80  sseLoadSe(iiPPcPv)
 *      mangled: sseLoadSe__FiiPPcPv */
u64
sseLoadSe__FiiPPcPv(u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 *puVar1;
  u32 uVar2;
  u64 uVar3;
  
  uVar2 = *(u32 *)*args;
  puVar1 = (u32 *)args[1];
  uVar3 = GetCore__3VECFv(ctx);
  uVar2 = LoadSe__10EffectCoreFi(uVar3,uVar2);
  *puVar1 = uVar2;
  return 0;
}

/* ---- 0x0031a4c0 size 0x6c  sseUnloadSe(iiPPcPv)
 *      mangled: sseUnloadSe__FiiPPcPv */
u64
sseUnloadSe__FiiPPcPv(u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 uVar1;
  u64 uVar2;
  
  uVar1 = *(u32 *)*args;
  uVar2 = GetCore__3VECFv(ctx);
  UnloadSe__10EffectCoreFUi(uVar2,uVar1);
  return 0;
}

/* ---- 0x0031a530 size 0xac  ssePlaySe(iiPPcPv)
 *      mangled: ssePlaySe__FiiPPcPv */
u64
ssePlaySe__FiiPPcPv(u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 uVar1;
  u32 uVar2;
  u64 uVar3;
  u64 uVar4;
  
  uVar1 = *(u32 *)*args;
  uVar2 = *(u32 *)args[1];
  uVar3 = GetCore__3VECFv(ctx);
  uVar4 = FindSe__10EffectCoreFUi(uVar3,uVar1);
  IsLoaded__12tagEffSeCtrlFv(uVar4);
  PlaySe__10EffectCoreFP12tagEffSeCtrlUi(uVar3,uVar4,uVar2);
  return 0;
}

/* ---- 0x0031a630 size 0xbc  sseGetSysSe(iiPPcPv)
 *      mangled: sseGetSysSe__FiiPPcPv */
u64
sseGetSysSe__FiiPPcPv(u64 id,u64 argc,u32 *args,u32 ctx)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  iVar1 = *(int *)*args;
  piVar2 = (int *)args[1];
  iVar3 = GetCore__3VECFv(ctx);
  if (iVar1 == 2) {
    *piVar2 = iVar3 + 0x42c;
  }
  else if (iVar1 == 1) {
    *piVar2 = iVar3 + 0x420;
  }
  else if (iVar1 == 0) {
    *piVar2 = iVar3 + 0x414;
  }
  return 0;
}

/* ---- 0x0031a6f0 size 0xec  ssePlayLoopSe(iiPPcPv)
 *      mangled: ssePlayLoopSe__FiiPPcPv */
u64
ssePlayLoopSe__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 uVar1;
  u32 uVar2;
  u64 uVar3;
  u64 uVar4;
  byte *pbVar5;
  
  uVar1 = *(u32 *)*args;
  uVar2 = *(u32 *)args[1];
  uVar3 = GetCore__3VECFv(ctx);
  uVar4 = FindSe__10EffectCoreFUi(uVar3,uVar1);
  IsLoaded__12tagEffSeCtrlFv(uVar4);
  pbVar5 = (byte *)uVar4;
  *pbVar5 = *pbVar5 & 0xfb | 4;
  *pbVar5 = *pbVar5 & 0xf7;
  pbVar5[8] = 0;
  pbVar5[9] = 0;
  pbVar5[10] = 0;
  pbVar5[0xb] = 0;
  PlaySe__10EffectCoreFP12tagEffSeCtrlUi(uVar3,uVar4,uVar2);
  return 0;
}

/* ---- 0x0031a7e0 size 0xc4  sseStopLoopSe(iiPPcPv)
 *      mangled: sseStopLoopSe__FiiPPcPv */
u64
sseStopLoopSe__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 uVar1;
  byte *pbVar2;
  u64 uVar3;
  
  uVar1 = *(u32 *)*args;
  uVar3 = GetCore__3VECFv(ctx);
  pbVar2 = (byte *)FindSe__10EffectCoreFUi(uVar3,uVar1);
  *pbVar2 = *pbVar2 & 0xfb;
  uVar3 = ReleaseSE__4SdrvFUii(sys__4Sdrv,*(u32 *)(pbVar2 + 8),0);
  CloseHandle__4SdrvFUi(sys__4Sdrv,uVar3);
  return 0;
}

/* ---- 0x0031a8b0 size 0xb8  sseWaitLoadSe(iiPPcPv)
 *      mangled: sseWaitLoadSe__FiiPPcPv */
u64
sseWaitLoadSe__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 uVar1;
  u32 *puVar2;
  byte *pbVar3;
  u64 uVar4;
  
  uVar1 = *(u32 *)*args;
  puVar2 = (u32 *)args[1];
  uVar4 = GetCore__3VECFv(ctx);
  pbVar3 = (byte *)FindSe__10EffectCoreFUi(uVar4,uVar1);
  if ((long)((ulong)*pbVar3 << 0x3e) < 0) {
    *puVar2 = 1;
  }
  else {
    *puVar2 = 0;
  }
  return 0;
}

/* ---- 0x0031b390 size 0x14  xxxCall(iiPPcPv)
 *      mangled: xxxCall__FiiPPcPv */
u64 xxxCall__FiiPPcPv(void)

{
  return 0;
}

/* ---- 0x0031b3b0 size 0xb4  chrGetTrans(iiPPcPv)
 *      mangled: chrGetTrans__FiiPPcPv */
u64
chrGetTrans__FiiPPcPv(u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 *puVar1;
  u32 *puVar2;
  u32 uVar3;
  int iVar4;
  u64 uVar5;
  
  puVar1 = (u32 *)*args;
  puVar2 = (u32 *)args[1];
  uVar3 = args[2];
  uVar5 = GetCore__3VECFv(ctx);
  iVar4 = GetModel__10EffectCoreFiiii(uVar5,*puVar1,*puVar2,0,0);
  uVar5 = GetPos__6MatrixFv(*(int *)(iVar4 + 0x30) + 0x160);
  __as__7FVectorFRC7FVector(uVar3,uVar5);
  return 0;
}

/* ---- 0x0031b470 size 0x94  chrGetGTCount(iiPPcPv)
 *      mangled: chrGetGTCount__FiiPPcPv */
u64
chrGetGTCount__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  int *piVar1;
  u32 *puVar2;
  int iVar3;
  
  piVar1 = (int *)*args;
  puVar2 = (u32 *)args[1];
  iVar3 = GetCore__3VECFv(ctx);
  if (*piVar1 == 1) {
    *puVar2 = *(u32 *)(iVar3 + 0xd8);
  }
  else {
    *puVar2 = *(u32 *)(iVar3 + 0xdc);
  }
  return 0;
}

/* ---- 0x0031b510 size 0xa8  chrGetRootMatrix(iiPPcPv)
 *      mangled: chrGetRootMatrix__FiiPPcPv */
u64
chrGetRootMatrix__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 *puVar1;
  u32 *puVar2;
  u32 uVar3;
  int iVar4;
  u64 uVar5;
  
  puVar1 = (u32 *)*args;
  puVar2 = (u32 *)args[1];
  uVar3 = args[2];
  uVar5 = GetCore__3VECFv(ctx);
  iVar4 = GetModel__10EffectCoreFiiii(uVar5,*puVar1,*puVar2,0,0);
  __as__6MatrixFRC6Matrix(uVar3,*(int *)(iVar4 + 0x30) + 0x160);
  return 0;
}

/* ---- 0x0031b5c0 size 0xf0  chrCreateMotion(iiPPcPv)
 *      mangled: chrCreateMotion__FiiPPcPv */
u64
chrCreateMotion__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 *puVar1;
  u32 *puVar2;
  u32 *puVar3;
  u32 *puVar4;
  u32 uVar5;
  u64 uVar6;
  u64 uVar7;
  
  puVar1 = (u32 *)*args;
  puVar2 = (u32 *)args[1];
  puVar3 = (u32 *)args[2];
  puVar4 = (u32 *)args[3];
  GetCore__3VECFv(ctx);
  uVar6 = GetCore__3VECFv(ctx);
  uVar6 = GetModel__10EffectCoreFiiii(uVar6,*puVar1,*puVar2,0,0);
  uVar7 = GetCore__3VECFv(ctx);
  uVar5 = CreateMotion__10EffectCoreFP5Modeliiiii(uVar7,uVar6,*puVar1,*puVar2,*puVar3,0,0);
  *puVar4 = uVar5;
  return 0;
}

/* ---- 0x0031b6b0 size 0x100  chrSetMotion(iiPPcPv)
 *      mangled: chrSetMotion__FiiPPcPv */
u64
chrSetMotion__FiiPPcPv(u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 *puVar1;
  u32 *puVar2;
  u32 uVar3;
  u64 uVar4;
  
  puVar1 = (u32 *)*args;
  puVar2 = (u32 *)args[1];
  uVar3 = args[2];
  GetCore__3VECFv(ctx);
  uVar4 = GetCore__3VECFv(ctx);
  uVar4 = GetModel__10EffectCoreFiiii(uVar4,*puVar1,*puVar2,0,0);
  SetCtrlMode__8BtlModelFbb(uVar4,1,1);
  setMotion__8BtlModelFPCc(uVar4,uVar3);
  (**(code **)(*(int *)((int)uVar4 + 0x10) + 0x2c))(0);
  (**(code **)(*(int *)((int)uVar4 + 0x10) + 0x28))(uVar4,0);
  return 0;
}

/* ---- 0x0031b7b0 size 0xa8  chrSetRootMatrix(iiPPcPv)
 *      mangled: chrSetRootMatrix__FiiPPcPv */
u64
chrSetRootMatrix__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 uVar1;
  int iVar2;
  
  uVar1 = args[2];
  iVar2 = GetModel__10EffectCoreFiiii(ctx,*(u32 *)*args,*(u32 *)args[1],0,0)
  ;
  __as__6MatrixFRC6Matrix(*(int *)(iVar2 + 0x30) + 0x160,uVar1);
  Frame::myMatrixUpdate__5FrameFv(*(Frame **)(iVar2 + 0x30));
  return 0;
}

/* ---- 0x0031b860 size 0xd0  chrCreateWeponMotion(iiPPcPv)
 *      mangled: chrCreateWeponMotion__FiiPPcPv */
u64
chrCreateWeponMotion__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 *puVar1;
  u32 *puVar2;
  u32 *puVar3;
  u32 *puVar4;
  u32 *puVar5;
  u32 uVar6;
  u64 uVar7;
  
  puVar1 = (u32 *)*args;
  puVar2 = (u32 *)args[1];
  puVar3 = (u32 *)args[2];
  puVar4 = (u32 *)args[3];
  puVar5 = (u32 *)args[4];
  uVar7 = GetModel__10EffectCoreFiiii(ctx,*puVar1,*puVar2,1,*puVar3);
  uVar6 = CreateMotion__10EffectCoreFP5Modeliiiii(ctx,uVar7,*puVar1,*puVar2,*puVar4,1,*puVar3);
  *puVar5 = uVar6;
  return 0;
}

/* ---- 0x0031b930 size 0xdc  chrSetWeponMotion(iiPPcPv)
 *      mangled: chrSetWeponMotion__FiiPPcPv */
u64
chrSetWeponMotion__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  char *name;
  u64 uVar1;
  Model *this;
  
  name = (char *)args[3];
  uVar1 = GetModel__10EffectCoreFiiii
                    (ctx,*(u32 *)*args,*(u32 *)args[1],1,
                     *(u32 *)args[2]);
  this = (Model *)uVar1;
  Model::setMotion__5ModelFPCcf(this,name,0.0);
  (**(code **)((int)this->pVtable + 0x2c))(0);
  (**(code **)((int)this->pVtable + 0x28))(uVar1,0);
  return 0;
}

/* ---- 0x0031ba10 size 0x100  chrDynaReset(iiPPcPv)
 *      mangled: chrDynaReset__FiiPPcPv */
u64
chrDynaReset__FiiPPcPv(u64 id,u64 argc,u32 *args,u32 ctx)

{
  int iVar1;
  u64 uVar2;
  
  uVar2 = 0;
  iVar1 = *(int *)*args;
  if (iVar1 == 2) {
    uVar2 = FindWorkModel__10EffectCoreFUi(ctx,*(u32 *)args[1]);
  }
  else if ((iVar1 == 1) || (iVar1 == 0)) {
    uVar2 = GetModel__10EffectCoreFiiii
                      (ctx,*(int *)*args,*(u32 *)args[1],*(u32 *)args[2],
                       *(u32 *)args[3]);
  }
  DynaReset__5ModelFv(uVar2);
  return 0;
}

/* ---- 0x0031c590 size 0x68  blrCreate(iiPPcPv)
 *      mangled: blrCreate__FiiPPcPv */
u64
blrCreate__FiiPPcPv(u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 uVar1;
  u64 uVar2;
  
  args = (u32 *)*args;
  uVar2 = GetCore__3VECFv(ctx);
  uVar1 = CreateBlur__10EffectCoreFv(uVar2);
  *args = uVar1;
  return 0;
}

/* ---- 0x0031c600 size 0xdc  blrShow(iiPPcPv)
 *      mangled: blrShow__FiiPPcPv */
u64
blrShow__FiiPPcPv(u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 *puVar1;
  VIF1Prim *prim;
  int iVar2;
  u64 uVar3;
  
  puVar1 = (u32 *)*args;
  iVar2 = *(int *)args[1];
  uVar3 = GetCore__3VECFv(ctx);
  prim = (VIF1Prim *)FindBlur__10EffectCoreFUi(uVar3,*puVar1);
  if (iVar2 == 0) {
    ReleaseOT__5WorldFP8VIF1Prim((World *)&m_World__4CApp,prim);
  }
  else {
    iVar2 = FindOT__5WorldFP8VIF1Prim((World *)&m_World__4CApp,prim);
    if (iVar2 == 0) {
      AddOT__5WorldFiP8VIF1Prim((World *)&m_World__4CApp,0xe,prim);
    }
  }
  return 0;
}

/* ---- 0x0031c6e0 size 0x8c  blrSetAlpha(iiPPcPv)
 *      mangled: blrSetAlpha__FiiPPcPv */
u64
blrSetAlpha__FiiPPcPv(u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 *puVar1;
  u32 uVar2;
  u64 uVar3;
  
  puVar1 = (u32 *)*args;
  uVar2 = *(u32 *)args[1];
  uVar3 = GetCore__3VECFv(ctx);
  uVar3 = FindBlur__10EffectCoreFUi(uVar3,*puVar1);
  SetAlpha__10EffectBlurFi(uVar3,uVar2);
  return 0;
}

/* ---- 0x0031c770 size 0x98  blrDelete(iiPPcPv)
 *      mangled: blrDelete__FiiPPcPv */
u64
blrDelete__FiiPPcPv(u64 id,u64 argc,u32 *args,u32 ctx)

{
  u64 uVar1;
  u64 uVar2;
  
  args = (u32 *)*args;
  uVar1 = GetCore__3VECFv(ctx);
  uVar1 = FindBlur__10EffectCoreFUi(uVar1,*args);
  ReleaseOT__5WorldFP8VIF1Prim((World *)&m_World__4CApp,(VIF1Prim *)uVar1);
  uVar2 = GetCore__3VECFv(ctx);
  DeleteBlur__10EffectCoreFP10EffectBlur(uVar2,uVar1);
  return 0;
}

/* ---- 0x0031c810 size 0x100  blrSetUv(iiPPcPv)
 *      mangled: blrSetUv__FiiPPcPv */
u64
blrSetUv__FiiPPcPv(u64 id,u64 argc,u32 *args,u32 ctx)

{
  int iVar1;
  u32 *puVar2;
  u64 uVar3;
  u32 uVar4;
  u32 uVar5;
  u32 uVar6;
  u32 uVar7;
  
  puVar2 = (u32 *)*args;
  uVar4 = *(u32 *)args[1];
  uVar5 = *(u32 *)args[2];
  uVar6 = *(u32 *)args[3];
  uVar7 = *(u32 *)args[4];
  uVar3 = GetCore__3VECFv(ctx);
  iVar1 = FindBlur__10EffectCoreFUi(uVar3,*puVar2);
  puVar2 = (u32 *)vx__7FVectorFv(iVar1 + 0x40);
  *puVar2 = uVar4;
  puVar2 = (u32 *)vy__7FVectorFv(iVar1 + 0x40);
  *puVar2 = uVar5;
  puVar2 = (u32 *)vx__7FVectorFv(iVar1 + 0x50);
  *puVar2 = uVar6;
  puVar2 = (u32 *)vy__7FVectorFv(iVar1 + 0x50);
  *puVar2 = uVar7;
  return 0;
}

/* ---- 0x0031c910 size 0xd8  blrSetColor(iiPPcPv)
 *      mangled: blrSetColor__FiiPPcPv */
u64
blrSetColor__FiiPPcPv(u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 *puVar1;
  u32 uVar2;
  u32 uVar3;
  u32 uVar4;
  u32 uVar5;
  int iVar6;
  u64 uVar7;
  
  puVar1 = (u32 *)*args;
  uVar2 = *(u32 *)args[1];
  uVar3 = *(u32 *)args[2];
  uVar4 = *(u32 *)args[3];
  uVar5 = *(u32 *)args[4];
  uVar7 = GetCore__3VECFv(ctx);
  iVar6 = FindBlur__10EffectCoreFUi(uVar7,*puVar1);
  *(char *)(iVar6 + 0x60) = (char)uVar2;
  *(char *)(iVar6 + 0x61) = (char)uVar3;
  *(char *)(iVar6 + 0x62) = (char)uVar4;
  *(char *)(iVar6 + 99) = (char)uVar5;
  return 0;
}

/* ---- 0x0031c9f0 size 0x114  blrCreateLine(iiPPcPv)
 *      mangled: blrCreateLine__FiiPPcPv */
u64
blrCreateLine__FiiPPcPv(u64 id,u64 argc,u32 *args,int ctx)

{
  u32 uVar1;
  u32 uVar2;
  u32 *puVar3;
  int iVar4;
  long lVar5;
  u64 uVar6;
  u32 uVar7;
  
  uVar1 = *(u32 *)*args;
  uVar2 = *(u32 *)args[1];
  uVar7 = *(u32 *)args[2];
  puVar3 = (u32 *)args[3];
  iVar4 = FindLineBlurIndex__10EffectCoreFUi(ctx,0);
  lVar5 = __nw__FUi(0x1e0e0);
  uVar6 = 0;
  if (lVar5 != 0) {
    uVar6 = __ct__8LineBlurFv(lVar5);
  }
  SetPower__8LineBlurFf(uVar7,uVar6);
  SetCenter__8LineBlurFUiUi(uVar6,uVar1,uVar2);
  *(int *)(ctx + iVar4 * 4 + 0x57c) = (int)uVar6;
  *puVar3 = *(u32 *)(ctx + iVar4 * 4 + 0x57c);
  return 0;
}

/* ---- 0x0031cbb0 size 0xe8  blrShowLine(iiPPcPv)
 *      mangled: blrShowLine__FiiPPcPv */
u64
blrShowLine__FiiPPcPv(u64 id,u64 argc,u32 *args,int ctx)

{
  VIF1Prim *prim;
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)args[1];
  iVar1 = FindLineBlurIndex__10EffectCoreFUi(ctx,*(u32 *)*args);
  prim = *(VIF1Prim **)(ctx + iVar1 * 4 + 0x57c);
  if (iVar2 == 0) {
    ReleaseOT__5WorldFP8VIF1Prim((World *)&m_World__4CApp,prim);
  }
  else {
    iVar2 = FindOT__5WorldFP8VIF1Prim((World *)&m_World__4CApp,prim);
    if (iVar2 == 0) {
      AddOT__5WorldFiP8VIF1Prim((World *)&m_World__4CApp,0xe,prim);
    }
  }
  return 0;
}

/* ---- 0x0031cca0 size 0x94  blrSetLinePower(iiPPcPv)
 *      mangled: blrSetLinePower__FiiPPcPv */
u64
blrSetLinePower__FiiPPcPv(u64 id,u64 argc,u32 *args,int ctx)

{
  int iVar1;
  u32 uVar2;
  
  uVar2 = *(u32 *)args[1];
  iVar1 = FindLineBlurIndex__10EffectCoreFUi(ctx,*(u32 *)*args);
  SetPower__8LineBlurFf(uVar2,*(u32 *)(ctx + iVar1 * 4 + 0x57c));
  return 0;
}

/* ---- 0x0031cd40 size 0xb0  blrSetLineCenter(iiPPcPv)
 *      mangled: blrSetLineCenter__FiiPPcPv */
u64
blrSetLineCenter__FiiPPcPv(u64 id,u64 argc,u32 *args,int ctx)

{
  u32 uVar1;
  u32 uVar2;
  int iVar3;
  
  uVar1 = *(u32 *)args[1];
  uVar2 = *(u32 *)args[2];
  iVar3 = FindLineBlurIndex__10EffectCoreFUi(ctx,*(u32 *)*args);
  SetCenter__8LineBlurFUiUi(*(u32 *)(ctx + iVar3 * 4 + 0x57c),uVar1,uVar2);
  return 0;
}

/* ---- 0x0031cdf0 size 0xa8  blrDeleteLine(iiPPcPv)
 *      mangled: blrDeleteLine__FiiPPcPv */
u64
blrDeleteLine__FiiPPcPv(u64 id,u64 argc,u32 *args,int ctx)

{
  VIF1Prim *prim;
  int iVar1;
  
  iVar1 = FindLineBlurIndex__10EffectCoreFUi(ctx,*(u32 *)*args);
  prim = *(VIF1Prim **)(ctx + iVar1 * 4 + 0x57c);
  ReleaseOT__5WorldFP8VIF1Prim((World *)&m_World__4CApp,prim);
  (**(code **)(prim[1].dwEnv + 0xc))();
  *(u32 *)(ctx + iVar1 * 4 + 0x57c) = 0;
  return 0;
}

/* ---- 0x0031cea0 size 0xe0  blrSetLineRect(iiPPcPv)
 *      mangled: blrSetLineRect__FiiPPcPv */
u64
blrSetLineRect__FiiPPcPv(u64 id,u64 argc,u32 *args,int ctx)

{
  u32 uVar1;
  u32 uVar2;
  u32 uVar3;
  u32 uVar4;
  int iVar5;
  
  uVar1 = *(u32 *)args[1];
  uVar2 = *(u32 *)args[2];
  uVar3 = *(u32 *)args[3];
  uVar4 = *(u32 *)args[4];
  iVar5 = FindLineBlurIndex__10EffectCoreFUi(ctx,*(u32 *)*args);
  SetBlurRect__8LineBlurFUiUiUiUi
            (*(u32 *)(ctx + iVar5 * 4 + 0x57c),uVar1,uVar2,uVar3,uVar4);
  return 0;
}

/* ---- 0x0031cf80 size 0xf4  pphCreate(iiPPcPv)
 *      mangled: pphCreate__FiiPPcPv */
u64
pphCreate__FiiPPcPv(u64 id,u64 argc,u32 *args,int ctx)

{
  u32 uVar1;
  u32 *puVar2;
  int iVar3;
  long lVar4;
  u64 uVar5;
  float fVar6;
  
  uVar1 = *(u32 *)*args;
  fVar6 = *(float *)args[1];
  puVar2 = (u32 *)args[2];
  iVar3 = FindPathIndex__10EffectCoreFPv(ctx,0);
  lVar4 = __nw__FUi(0x5b0);
  uVar5 = 0;
  if (lVar4 != 0) {
    uVar5 = __ct__12CPathControlFv(lVar4);
  }
  Create__12CPathControlFif(fVar6 * 0.0333333,uVar5,uVar1);
  *(int *)(ctx + iVar3 * 4 + 0x454) = (int)uVar5;
  *puVar2 = (int)uVar5;
  return 0;
}

/* ---- 0x0031d080 size 0x94  pphDelete(iiPPcPv)
 *      mangled: pphDelete__FiiPPcPv */
u64
pphDelete__FiiPPcPv(u64 id,u64 argc,u32 *args,int ctx)

{
  VIF1Prim *prim;
  int iVar1;
  
  prim = *(VIF1Prim **)*args;
  iVar1 = FindPathIndex__10EffectCoreFPv(ctx,prim);
  ReleaseOT__5WorldFP8VIF1Prim((World *)&m_World__4CApp,prim);
  (**(code **)(prim[1].dwEnv + 0xc))();
  *(u32 *)(ctx + iVar1 * 4 + 0x454) = 0;
  return 0;
}

/* ---- 0x0031d120 size 0x124  pphShow(iiPPcPv)
 *      mangled: pphShow__FiiPPcPv */
u64
pphShow__FiiPPcPv(u64 id,u64 argc,u32 *args,u32 ctx)

{
  VIF1Prim *prim;
  int iVar1;
  u32 uVar2;
  int iVar3;
  
  prim = *(VIF1Prim **)*args;
  iVar3 = *(int *)args[1];
  iVar1 = *(int *)args[2];
  uVar2 = *(u32 *)args[3];
  FindPathIndex__10EffectCoreFPv(ctx,prim);
  if (iVar3 == 0) {
    ReleaseOT__5WorldFP8VIF1Prim((World *)&m_World__4CApp,prim);
  }
  else {
    iVar3 = FindOT__5WorldFP8VIF1Prim((World *)&m_World__4CApp,prim);
    if (iVar3 == 0) {
      AddOT__5WorldFiP8VIF1Prim((World *)&m_World__4CApp,*(int *)(WkLayer + iVar1 * 8),prim);
    }
    else {
      setZvolume__8VIF1PrimFs(prim,(short)uVar2);
    }
  }
  return 0;
}

/* ---- 0x0031d250 size 0x94  pphAddPath(iiPPcPv)
 *      mangled: pphAddPath__FiiPPcPv */
u64
pphAddPath__FiiPPcPv(u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 uVar1;
  u32 uVar2;
  u32 uVar3;
  
  uVar1 = *(u32 *)*args;
  uVar2 = args[1];
  uVar3 = args[2];
  FindPathIndex__10EffectCoreFPv(ctx,uVar1);
  AddPath__12CPathControlFR7FVectorR7FVector(uVar1,uVar2,uVar3);
  return 0;
}

/* ---- 0x0031d2f0 size 0xac  pphAddColorKey(iiPPcPv)
 *      mangled: pphAddColorKey__FiiPPcPv */
u64
pphAddColorKey__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 uVar1;
  u32 uVar2;
  float fVar3;
  
  uVar1 = *(u32 *)*args;
  fVar3 = *(float *)args[1];
  uVar2 = args[2];
  FindPathIndex__10EffectCoreFPv(ctx,uVar1);
  AddColorKey__12CPathControlFfR9_RGBAReal(fVar3 * 0.0333333,uVar1,uVar2);
  return 0;
}

/* ---- 0x0031d3a0 size 0x120  pphSetTestReg(iiPPcPv)
 *      mangled: pphSetTestReg__FiiPPcPv */
u64
pphSetTestReg__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 uVar1;
  u32 uVar2;
  u32 uVar3;
  u32 uVar4;
  u32 uVar5;
  u32 uVar6;
  u32 uVar7;
  u32 uVar8;
  
  uVar1 = *(u32 *)*args;
  uVar2 = *(u32 *)args[1];
  uVar3 = *(u32 *)args[2];
  uVar4 = *(u32 *)args[3];
  uVar5 = *(u32 *)args[4];
  uVar6 = *(u32 *)args[5];
  uVar7 = *(u32 *)args[6];
  uVar8 = *(u32 *)args[7];
  FindPathIndex__10EffectCoreFPv(ctx,uVar1);
  changeGSTest__12CPathControlFiiiiiiii(uVar1,uVar2,uVar3,uVar4,uVar5,uVar6,uVar7,uVar8);
  return 0;
}

/* ---- 0x0031d4c0 size 0xe4  pphSetAlphaReg(iiPPcPv)
 *      mangled: pphSetAlphaReg__FiiPPcPv */
u64
pphSetAlphaReg__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 uVar1;
  u32 uVar2;
  u32 uVar3;
  u32 uVar4;
  u32 uVar5;
  u32 uVar6;
  
  uVar1 = *(u32 *)*args;
  uVar2 = *(u32 *)args[1];
  uVar3 = *(u32 *)args[2];
  uVar4 = *(u32 *)args[3];
  uVar5 = *(u32 *)args[4];
  uVar6 = *(u32 *)args[5];
  FindPathIndex__10EffectCoreFPv(ctx,uVar1);
  changeGSAlpha__12CPathControlFiiiii(uVar1,uVar2,uVar3,uVar4,uVar5,uVar6);
  return 0;
}

/* ---- 0x0031d5b0 size 0xac  pphCreateTexture(iiPPcPv)
 *      mangled: pphCreateTexture__FiiPPcPv */
u64
pphCreateTexture__FiiPPcPv
          (u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 uVar1;
  u32 uVar2;
  u64 uVar3;
  
  uVar1 = *(u32 *)*args;
  uVar2 = *(u32 *)args[1];
  FindPathIndex__10EffectCoreFPv(ctx,uVar1);
  uVar3 = GetDataPtr__10EffectCoreFUciUiUi(ctx,0x4f,uVar2,0xffffffffffffffff,0xffffffffffffffff)
  ;
  CreateTexture__12CPathControlFPc(uVar1,uVar3);
  return 0;
}

/* ---- 0x0031d660 size 0xf8  pphAddStKey(iiPPcPv)
 *      mangled: pphAddStKey__FiiPPcPv */
u64
pphAddStKey__FiiPPcPv(u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 uVar1;
  u8 auStack_70 [28];
  u32 uStack_54;
  u32 uStack_50;
  u32 uStack_4c;
  u32 uStack_48;
  float fStack_44;
  u32 *puStack_20;
  u32 uStack_10;
  
  uVar1 = *(u32 *)*args;
  fStack_44 = *(float *)args[1];
  uStack_48 = *(u32 *)args[2];
  uStack_4c = *(u32 *)args[3];
  uStack_50 = *(u32 *)args[4];
  uStack_54 = *(u32 *)args[5];
  puStack_20 = args;
  uStack_10 = ctx;
  FindPathIndex__10EffectCoreFPv(ctx,uVar1);
  fStack_44 = fStack_44 * 0.0333333;
  __ct__7FVectorFffff(uStack_48,uStack_4c,uStack_50,uStack_54,auStack_70);
  AddSTKey__12CPathControlFfR7FVector(fStack_44,uVar1,auStack_70);
  return 0;
}

/* ---- 0x0031f330 size 0xbc  fldGetPos(iiPPcPv)
 *      mangled: fldGetPos__FiiPPcPv */
u64
fldGetPos__FiiPPcPv(u64 id,u64 argc,u32 *args,int ctx)

{
  if (*(int *)*args == 0) {
    __as__7FVectorFRC7FVector(args[2],ctx + *(int *)args[1] * 0x10 + 0x30);
  }
  else if (*(int *)*args == 1) {
    __as__7FVectorFRC7FVector(args[2],ctx + *(int *)args[1] * 0x10 + 0x80);
  }
  return 0;
}

/* ---- 0x0031f3f0 size 0x84  fldGetGTCount(iiPPcPv)
 *      mangled: fldGetGTCount__FiiPPcPv */
u64
fldGetGTCount__FiiPPcPv(u64 id,u64 argc,u32 *args,int ctx)

{
  int iVar1;
  u32 *puVar2;
  
  iVar1 = *(int *)*args;
  puVar2 = (u32 *)args[1];
  *puVar2 = 0;
  if (iVar1 == 0) {
    *puVar2 = *(u32 *)(ctx + 0xdc);
  }
  else if (iVar1 == 1) {
    *puVar2 = *(u32 *)(ctx + 0xd8);
  }
  return 0;
}

/* ---- 0x0031f480 size 0xd4  fldAttachBG(iiPPcPv)
 *      mangled: fldAttachBG__FiiPPcPv */
u64
fldAttachBG__FiiPPcPv(u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 uVar1;
  u32 uVar2;
  int iVar3;
  int iVar4;
  u32 uVar5;
  
  uVar5 = *(u32 *)args[1];
  uVar1 = *(u32 *)args[2];
  uVar2 = args[3];
  iVar3 = FindWorkModel__10EffectCoreFUi(ctx,*(u32 *)*args);
  iVar4 = FindFieldModel__Fii(uVar5,uVar1);
  uVar5 = searchFrame__5FrameFPCc(*(u32 *)(iVar4 + 0x30),uVar2);
  *(u32 *)(iVar3 + 0x518) = uVar5;
  return 0;
}

/* ---- 0x0031f560 size 0xe0  fldAttachBG2(iiPPcPv)
 *      mangled: fldAttachBG2__FiiPPcPv */
u64
fldAttachBG2__FiiPPcPv(u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 uVar1;
  u32 uVar2;
  u32 uVar3;
  int iVar4;
  u64 uVar5;
  u64 uVar6;
  
  uVar1 = *(u32 *)args[1];
  uVar2 = *(u32 *)args[2];
  uVar3 = args[3];
  uVar5 = FindWorkModel__10EffectCoreFUi(ctx,*(u32 *)*args);
  iVar4 = FindFieldModel__Fii(uVar1,uVar2);
  uVar6 = searchFrame__5FrameFPCc(*(u32 *)(iVar4 + 0x30),uVar3);
  chainModel__5FrameFP5Model(uVar6,uVar5);
  return 0;
}

/* ---- 0x0031f640 size 0xa8  gnyCreate(iiPPcPv)
 *      mangled: gnyCreate__FiiPPcPv */
u64
gnyCreate__FiiPPcPv(u64 id,u64 argc,u32 *args,int ctx)

{
  int iVar1;
  u32 uVar2;
  long lVar3;
  
  args = (u32 *)*args;
  iVar1 = FindGunyaIndex__10EffectCoreFP11EffectGunya(ctx,0);
  lVar3 = __nw__FUi(0xf20);
  uVar2 = 0;
  if (lVar3 != 0) {
    uVar2 = __ct__11EffectGunyaFv(lVar3);
  }
  *(u32 *)(ctx + iVar1 * 4 + 0x56c) = uVar2;
  *args = *(u32 *)(ctx + iVar1 * 4 + 0x56c);
  return 0;
}

/* ---- 0x0031f6f0 size 0xa8  gnyDelete(iiPPcPv)
 *      mangled: gnyDelete__FiiPPcPv */
u64
gnyDelete__FiiPPcPv(u64 id,u64 argc,u32 *args,int ctx)

{
  int iVar1;
  
  iVar1 = FindGunyaIndex__10EffectCoreFP11EffectGunya(ctx,*(u32 *)*args);
  ReleaseOT__5WorldFP8VIF1Prim((World *)&m_World__4CApp,*(VIF1Prim **)(ctx + iVar1 * 4 + 0x56c))
  ;
  (**(code **)(*(int *)(*(int *)(ctx + iVar1 * 4 + 0x56c) + 0x1c) + 0xc))();
  *(u32 *)(ctx + iVar1 * 4 + 0x56c) = 0;
  return 0;
}

/* ---- 0x0031f7a0 size 0x114  gnyShow(iiPPcPv)
 *      mangled: gnyShow__FiiPPcPv */
u64
gnyShow__FiiPPcPv(u64 id,u64 argc,u32 *args,u32 ctx)

{
  int layer;
  u32 uVar1;
  VIF1Prim *prim;
  int iVar2;
  
  iVar2 = *(int *)args[1];
  layer = *(int *)args[2];
  uVar1 = *(u32 *)args[3];
  prim = (VIF1Prim *)FindGunya__10EffectCoreFUi(ctx,*(u32 *)*args);
  if (iVar2 == 0) {
    ReleaseOT__5WorldFP8VIF1Prim((World *)&m_World__4CApp,prim);
  }
  else {
    iVar2 = FindOT__5WorldFP8VIF1Prim((World *)&m_World__4CApp,prim);
    if (iVar2 == 0) {
      AddOT__5WorldFiP8VIF1Prim((World *)&m_World__4CApp,layer,prim);
    }
    setZvolume__8VIF1PrimFs(prim,(short)uVar1);
  }
  return 0;
}

/* ---- 0x0031f8c0 size 0xa4  gnyAddRotKey(iiPPcPv)
 *      mangled: gnyAddRotKey__FiiPPcPv */
u64
gnyAddRotKey__FiiPPcPv(u64 id,u64 argc,u32 *args,u32 ctx)

{
  u64 uVar1;
  float fVar2;
  u32 uVar3;
  
  fVar2 = *(float *)args[1];
  uVar3 = *(u32 *)args[2];
  uVar1 = FindGunya__10EffectCoreFUi(ctx,*(u32 *)*args);
  AddRotKey__11EffectGunyaFff(fVar2 * 0.033333,uVar3,uVar1);
  return 0;
}

/* ---- 0x003227b0 size 0x1fc  bngCreate(iiPPcPv)
 *      mangled: bngCreate__FiiPPcPv */
u64
bngCreate__FiiPPcPv(u64 id,u64 argc,u32 *args,int ctx)

{
  u32 *puVar1;
  u32 uVar2;
  long lVar3;
  u64 uVar4;
  int iVar5;
  int iVar6;
  u8 auStack_50 [48];
  u32 *puStack_20;
  int iStack_10;
  
  puVar1 = (u32 *)*args;
  puStack_20 = args;
  iStack_10 = ctx;
  lVar3 = __nw__FUi(0x5e0);
  uVar2 = 0;
  if (lVar3 != 0) {
    uVar2 = __ct__11EffectBarinFv(lVar3);
  }
  *(u32 *)(ctx + 0x578) = uVar2;
  for (iVar5 = 0; iVar5 < 0x35; iVar5 = iVar5 + 1) {
    lVar3 = __nw__FUi(0xb0);
    uVar4 = 0;
    if (lVar3 != 0) {
      uVar4 = __ct__7FreePolFi(lVar3,*(u16 *)(___bvt + iVar5 * 0x12));
    }
    lVar3 = 0;
    while (lVar3 < *(short *)(___bvt + iVar5 * 0x12)) {
      iVar6 = (int)lVar3;
      PixelTo3D__11EffectBarinFff
                ((float)(int)*(short *)(___bvt + iVar6 * 4 + iVar5 * 0x12 + 2),
                 (float)(int)*(short *)(___bvt + iVar6 * 4 + iVar5 * 0x12 + 4),auStack_50,
                 *(u32 *)(ctx + 0x578));
      __as__7FVectorFRC7FVector(*(int *)((int)uVar4 + 0x10) + iVar6 * 0x10,auStack_50);
      lVar3 = (long)(iVar6 + 1);
    }
    *(u32 *)((int)uVar4 + 0xc) = 0x3c23d70a;
    AddPolygon__11EffectBarinFP7FreePol(*(u32 *)(ctx + 0x578),uVar4);
  }
  *puVar1 = *(u32 *)(ctx + 0x578);
  return 0;
}

/* ---- 0x003229b0 size 0x7c  bngCreateUser(iiPPcPv)
 *      mangled: bngCreateUser__FiiPPcPv */
u64
bngCreateUser__FiiPPcPv(u64 id,u64 argc,u32 *args,int ctx)

{
  u32 uVar1;
  long lVar2;
  
  args = (u32 *)*args;
  lVar2 = __nw__FUi(0x5e0);
  uVar1 = 0;
  if (lVar2 != 0) {
    uVar1 = __ct__11EffectBarinFv(lVar2);
  }
  *(u32 *)(ctx + 0x578) = uVar1;
  *args = *(u32 *)(ctx + 0x578);
  return 0;
}

/* ---- 0x00322a30 size 0x74  bngDelete(iiPPcPv)
 *      mangled: bngDelete__FiiPPcPv */
u64 bngDelete__FiiPPcPv(void)

{
  int in_a3_lo;
  
  ReleaseOT__5WorldFP8VIF1Prim((World *)&m_World__4CApp,*(VIF1Prim **)(in_a3_lo + 0x578));
  (**(code **)(*(int *)(*(int *)(in_a3_lo + 0x578) + 0x1c) + 0xc))();
  *(u32 *)(in_a3_lo + 0x578) = 0;
  return 0;
}

/* ---- 0x00322ab0 size 0x110  bngShow(iiPPcPv)
 *      mangled: bngShow__FiiPPcPv */
u64 bngShow__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  VIF1Prim *prim;
  int layer;
  u32 uVar1;
  int iVar2;
  
  prim = *(VIF1Prim **)*args;
  iVar2 = *(int *)args[1];
  layer = *(int *)args[2];
  uVar1 = *(u32 *)args[3];
  *(byte *)&prim[0xe].dwEnv = (byte)prim[0xe].dwEnv & 0xfe | (byte)iVar2 & 1;
  if (iVar2 == 0) {
    ReleaseOT__5WorldFP8VIF1Prim((World *)&m_World__4CApp,prim);
  }
  else {
    iVar2 = FindOT__5WorldFP8VIF1Prim((World *)&m_World__4CApp,prim);
    if (iVar2 == 0) {
      AddOT__5WorldFiP8VIF1Prim((World *)&m_World__4CApp,layer,prim);
    }
    setZvolume__8VIF1PrimFs(prim,(short)uVar1);
  }
  return 0;
}

/* ---- 0x00322bc0 size 0x14  bngSetBackColor(iiPPcPv)
 *      mangled: bngSetBackColor__FiiPPcPv */
u64 bngSetBackColor__FiiPPcPv(void)

{
  return 0;
}

/* ---- 0x00322be0 size 0x1c8  bngAddPolygon(iiPPcPv)
 *      mangled: bngAddPolygon__FiiPPcPv */
u64 bngAddPolygon__FiiPPcPv(u64 id,u64 argc,int args,int ctx)

{
  u32 uVar1;
  u32 uVar2;
  u32 uVar3;
  int *piVar4;
  u32 *puVar5;
  u32 *puVar6;
  long lVar7;
  u64 uVar8;
  int iVar9;
  u8 auStack_70 [16];
  u8 auStack_60 [16];
  u8 auStack_50 [48];
  int iStack_20;
  int iStack_10;
  
  uVar1 = *(u32 *)(args + 4);
  uVar2 = *(u32 *)(args + 8);
  uVar3 = *(u32 *)(args + 0xc);
  piVar4 = *(int **)(args + 0x10);
  iStack_20 = args;
  iStack_10 = ctx;
  lVar7 = __nw__FUi(0xb0);
  uVar8 = 0;
  if (lVar7 != 0) {
    uVar8 = __ct__11FreePolUserFv(lVar7);
  }
  puVar5 = (u32 *)vx__7FVectorFv(uVar1);
  puVar6 = (u32 *)vy__7FVectorFv(uVar1);
  PixelTo3D__11EffectBarinFff(*puVar5,*puVar6,auStack_50,*(u32 *)(ctx + 0x578));
  iVar9 = (int)uVar8;
  __as__7FVectorFRC7FVector(*(u32 *)(iVar9 + 0x10),auStack_50);
  puVar5 = (u32 *)vx__7FVectorFv(uVar2);
  puVar6 = (u32 *)vy__7FVectorFv(uVar2);
  PixelTo3D__11EffectBarinFff(*puVar5,*puVar6,auStack_60,*(u32 *)(ctx + 0x578));
  __as__7FVectorFRC7FVector(*(int *)(iVar9 + 0x10) + 0x10,auStack_60);
  puVar5 = (u32 *)vx__7FVectorFv(uVar3);
  puVar6 = (u32 *)vy__7FVectorFv(uVar3);
  PixelTo3D__11EffectBarinFff(*puVar5,*puVar6,auStack_70,*(u32 *)(ctx + 0x578));
  __as__7FVectorFRC7FVector(*(int *)(iVar9 + 0x10) + 0x20,auStack_70);
  *(u32 *)(iVar9 + 0xc) = 0x3c23d70a;
  AddPolygon__11EffectBarinFP7FreePol(*(u32 *)(ctx + 0x578),uVar8);
  *piVar4 = iVar9;
  return 0;
}

/* ---- 0x00322db0 size 0x9c  bngSetPolTrans(iiPPcPv)
 *      mangled: bngSetPolTrans__FiiPPcPv */
u64 bngSetPolTrans__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  int iVar1;
  float *pfVar2;
  float fVar3;
  float fVar4;
  
  iVar1 = *(int *)*args;
  fVar3 = *(float *)args[1];
  fVar4 = *(float *)args[2];
  pfVar2 = (float *)vx__7FVectorFv(iVar1 + 0x60);
  *pfVar2 = *pfVar2 + fVar3;
  pfVar2 = (float *)vy__7FVectorFv(iVar1 + 0x60);
  *pfVar2 = *pfVar2 + fVar4;
  return 0;
}

/* ---- 0x00322e50 size 0x68  bngSetPolRot(iiPPcPv)
 *      mangled: bngSetPolRot__FiiPPcPv */
u64
bngSetPolRot__FiiPPcPv(u64 id,u64 argc,u32 *args,u32 ctx)

{
  int iVar1;
  u8 auStack_50 [48];
  u32 *puStack_20;
  u32 uStack_10;
  
  iVar1 = *(int *)*args;
  puStack_20 = args;
  uStack_10 = ctx;
  __ct__7FVectorFRC7FVector(auStack_50,args[1]);
  __as__7FVectorFRC7FVector(iVar1 + 0x80,auStack_50);
  return 0;
}

/* ---- 0x00322ec0 size 0x54  bngSetPolScale(iiPPcPv)
 *      mangled: bngSetPolScale__FiiPPcPv */
u64 bngSetPolScale__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  *(u32 *)(*(int *)*args + 0x78) = *(u32 *)args[1];
  return 0;
}

/* ---- 0x00323f40 size 0x50  strStrCopy(iiPPcPv)
 *      mangled: strStrCopy__FiiPPcPv */
u64 strStrCopy__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  strcpy((char *)*args,(char *)args[1]);
  return 0;
}

/* ---- 0x00323f90 size 0x70  strStrNCopy(iiPPcPv)
 *      mangled: strStrNCopy__FiiPPcPv */
u64 strStrNCopy__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  void *__dest;
  int iVar1;
  
  __dest = (void *)*args;
  iVar1 = *(int *)args[2];
  memcpy(__dest,(void *)args[1],(long)iVar1);
  *(u8 *)((int)__dest + iVar1) = 0;
  return 0;
}

/* ---- 0x00324000 size 0xf4  pthCreate(iiPPcPv)
 *      mangled: pthCreate__FiiPPcPv */
u64
pthCreate__FiiPPcPv(u64 id,u64 argc,u32 *args,int ctx)

{
  u32 uVar1;
  u32 *puVar2;
  int iVar3;
  long lVar4;
  u64 uVar5;
  float fVar6;
  
  uVar1 = *(u32 *)*args;
  fVar6 = *(float *)args[1];
  puVar2 = (u32 *)args[2];
  iVar3 = FindCalcPathIndex__10EffectCoreFPv(ctx,0);
  lVar4 = __nw__FUi(0x2b0);
  uVar5 = 0;
  if (lVar4 != 0) {
    uVar5 = __ct__5CPathFv(lVar4);
  }
  Create__5CPathFif(fVar6 * 0.0333333,uVar5,uVar1);
  *(int *)(ctx + iVar3 * 4 + 0x51c) = (int)uVar5;
  *puVar2 = (int)uVar5;
  return 0;
}

/* ---- 0x00324100 size 0x98  pthDelete(iiPPcPv)
 *      mangled: pthDelete__FiiPPcPv */
u64
pthDelete__FiiPPcPv(u64 id,u64 argc,u32 *args,int ctx)

{
  int iVar1;
  
  iVar1 = FindCalcPathIndex__10EffectCoreFPv(ctx,*(u32 *)*args);
  if (*(int *)(ctx + iVar1 * 4 + 0x51c) != 0) {
    __dt__5CPathFv(*(u32 *)(ctx + iVar1 * 4 + 0x51c),1);
    *(u32 *)(ctx + iVar1 * 4 + 0x51c) = 0;
  }
  return 0;
}

/* ---- 0x003241a0 size 0x94  pthAddPath(iiPPcPv)
 *      mangled: pthAddPath__FiiPPcPv */
u64
pthAddPath__FiiPPcPv(u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 uVar1;
  u32 uVar2;
  u32 uVar3;
  
  uVar1 = *(u32 *)*args;
  uVar2 = args[1];
  uVar3 = args[2];
  FindCalcPathIndex__10EffectCoreFPv(ctx,uVar1);
  AddPath__5CPathFR7FVectorR7FVector(uVar1,uVar2,uVar3);
  return 0;
}

/* ---- 0x00324240 size 0xd0  pthGetPath(iiPPcPv)
 *      mangled: pthGetPath__FiiPPcPv */
u64
pthGetPath__FiiPPcPv(u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 uVar1;
  u32 uVar2;
  u32 uVar3;
  u8 auStack_80 [16];
  u8 auStack_70 [44];
  u32 uStack_44;
  u32 *puStack_20;
  u32 uStack_10;
  
  uVar1 = *(u32 *)*args;
  uStack_44 = *(u32 *)args[1];
  uVar2 = args[2];
  uVar3 = args[3];
  puStack_20 = args;
  uStack_10 = ctx;
  FindCalcPathIndex__10EffectCoreFPv(ctx,uVar1);
  __ct__8PATHDATAFv(auStack_80);
  GetPath__5CPathFR8PATHDATAf(uStack_44,uVar1,auStack_80);
  __as__7FVectorFRC7FVector(uVar2,auStack_80);
  __as__7FVectorFRC7FVector(uVar3,auStack_70);
  return 0;
}

/* ---- 0x00324350 size 0x80  pthAddTime(iiPPcPv)
 *      mangled: pthAddTime__FiiPPcPv */
u64
pthAddTime__FiiPPcPv(u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 uVar1;
  u32 uVar2;
  
  uVar1 = *(u32 *)*args;
  uVar2 = *(u32 *)args[1];
  FindCalcPathIndex__10EffectCoreFPv(ctx,uVar1);
  AddTime__5CPathFf(uVar2,uVar1);
  return 0;
}

/* ---- 0x003243d0 size 0x14  padGetKeyPress(iiPPcPv)
 *      mangled: padGetKeyPress__FiiPPcPv */
u64 padGetKeyPress__FiiPPcPv(void)

{
  return 0;
}

/* ---- 0x003246d0 size 0x1bc  bfdSetMode(iiPPcPv)
 *      mangled: bfdSetMode__FiiPPcPv */
u64 bfdSetMode__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  u32 uVar1;
  float *pfVar2;
  u8 uVar3;
  float fVar4;
  u8 auStack_60 [24];
  u32 uStack_48;
  u32 uStack_44;
  u32 *puStack_20;
  
  uVar1 = *(u32 *)*args;
  uStack_44 = *(u32 *)args[1];
  puStack_20 = args;
  __ct__7FVectorFRC7FVector(auStack_60,args[2]);
  __ct__7_rgba32Fv(&uStack_48);
  pfVar2 = (float *)vx__7FVectorFv(auStack_60);
  fVar4 = *pfVar2;
  if (fVar4 < 2.1474836e+09) {
    uVar3 = (u8)(int)fVar4;
  }
  else {
    uVar3 = (u8)(int)(fVar4 - 2.1474836e+09);
  }
  uStack_48 = CONCAT31(uStack_48._1_3_,uVar3);
  pfVar2 = (float *)vy__7FVectorFv(auStack_60);
  fVar4 = *pfVar2;
  if (fVar4 < 2.1474836e+09) {
    uVar3 = (u8)(int)fVar4;
  }
  else {
    uVar3 = (u8)(int)(fVar4 - 2.1474836e+09);
  }
  uStack_48._0_2_ = CONCAT11(uVar3,(u8)uStack_48);
  pfVar2 = (float *)vz__7FVectorFv(auStack_60);
  fVar4 = *pfVar2;
  if (fVar4 < 2.1474836e+09) {
    uVar3 = (u8)(int)fVar4;
  }
  else {
    uVar3 = (u8)(int)(fVar4 - 2.1474836e+09);
  }
  uStack_48._0_3_ = CONCAT12(uVar3,(u16)uStack_48);
  pfVar2 = (float *)vw__7FVectorFv(auStack_60);
  fVar4 = *pfVar2;
  if (fVar4 < 2.1474836e+09) {
    uVar3 = (u8)(int)fVar4;
  }
  else {
    uVar3 = (u8)(int)(fVar4 - 2.1474836e+09);
  }
  uStack_48 = CONCAT13(uVar3,(undefined3)uStack_48);
  SetMode__8BtlFaderFsf7_rgba32(uStack_44,(short)uVar1,uStack_48);
  return 0;
}

/* ---- 0x00324890 size 0xd4  bfdSetAlphaMode(iiPPcPv)
 *      mangled: bfdSetAlphaMode__FiiPPcPv */
u64 bfdSetAlphaMode__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  SetAlphaMode__8BtlFaderFUl
            ((long)*(int *)args[4] << 0x20 |
             (long)*(int *)args[3] << 6 |
             (long)*(int *)args[2] << 4 | (long)*(int *)*args | (long)*(int *)args[1] << 2)
  ;
  return 0;
}

/* ---- 0x00324970 size 0x18c  bfdSetColor(iiPPcPv)
 *      mangled: bfdSetColor__FiiPPcPv */
u64 bfdSetColor__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  float *pfVar1;
  u8 uVar2;
  float fVar3;
  u8 auStack_60 [28];
  u32 uStack_44;
  u32 *puStack_20;
  
  puStack_20 = args;
  __ct__7FVectorFRC7FVector(auStack_60,*args);
  __ct__7_rgba32Fv(&uStack_44);
  pfVar1 = (float *)vx__7FVectorFv(auStack_60);
  fVar3 = *pfVar1;
  if (fVar3 < 2.1474836e+09) {
    uVar2 = (u8)(int)fVar3;
  }
  else {
    uVar2 = (u8)(int)(fVar3 - 2.1474836e+09);
  }
  uStack_44 = CONCAT31(uStack_44._1_3_,uVar2);
  pfVar1 = (float *)vy__7FVectorFv(auStack_60);
  fVar3 = *pfVar1;
  if (fVar3 < 2.1474836e+09) {
    uVar2 = (u8)(int)fVar3;
  }
  else {
    uVar2 = (u8)(int)(fVar3 - 2.1474836e+09);
  }
  uStack_44._0_2_ = CONCAT11(uVar2,(u8)uStack_44);
  pfVar1 = (float *)vz__7FVectorFv(auStack_60);
  fVar3 = *pfVar1;
  if (fVar3 < 2.1474836e+09) {
    uVar2 = (u8)(int)fVar3;
  }
  else {
    uVar2 = (u8)(int)(fVar3 - 2.1474836e+09);
  }
  uStack_44._0_3_ = CONCAT12(uVar2,(u16)uStack_44);
  pfVar1 = (float *)vw__7FVectorFv(auStack_60);
  fVar3 = *pfVar1;
  if (fVar3 < 2.1474836e+09) {
    uVar2 = (u8)(int)fVar3;
  }
  else {
    uVar2 = (u8)(int)(fVar3 - 2.1474836e+09);
  }
  uStack_44 = CONCAT13(uVar2,(undefined3)uStack_44);
  SetColor__8BtlFaderF7_rgba32(uStack_44);
  return 0;
}

/* ---- 0x003250a0 size 0x5c  lsdGetModel(iiPPcPv)
 *      mangled: lsdGetModel__FiiPPcPv */
u64 lsdGetModel__FiiPPcPv(u64 id,u64 argc,u32 *args)

{
  u32 *puVar1;
  u32 uVar2;
  
  puVar1 = (u32 *)args[1];
  uVar2 = FindLsdModel__FPc(*args);
  *puVar1 = uVar2;
  return 0;
}

/* ---- 0x00325100 size 0xc8  lsdAttach(iiPPcPv)
 *      mangled: lsdAttach__FiiPPcPv */
u64
lsdAttach__FiiPPcPv(u64 id,u64 argc,u32 *args,u32 ctx)

{
  u32 uVar1;
  u32 uVar2;
  int iVar3;
  u64 uVar4;
  u64 uVar5;
  
  uVar1 = *(u32 *)args[1];
  uVar2 = args[2];
  uVar4 = FindWorkModel__10EffectCoreFUi(ctx,*(u32 *)*args);
  iVar3 = CheckLsdModel__FP5Model(uVar1);
  uVar5 = searchFrame__5FrameFPCc(*(u32 *)(iVar3 + 0x30),uVar2);
  chainModel__5FrameFP5Model(uVar5,uVar4);
  return 0;
}

/* ---- 0x003251d0 size 0x70  lsdDetach(iiPPcPv)
 *      mangled: lsdDetach__FiiPPcPv */
u64
lsdDetach__FiiPPcPv(u64 id,u64 argc,u32 *args,u32 ctx)

{
  int iVar1;
  
  iVar1 = FindWorkModel__10EffectCoreFUi(ctx,*(u32 *)*args);
  unChainModel__5FrameFv(*(u32 *)(*(int *)(iVar1 + 0x30) + 0x1e0));
  return 0;
}

/* ---- 0x00325240 size 0x50c  fefCreateSmoke(iiPPcPv)
 *      mangled: fefCreateSmoke__FiiPPcPv */
u64
fefCreateSmoke__FiiPPcPv(u64 id,u64 argc,u32 *args,int ctx)

{
  u32 uVar1;
  u32 uVar2;
  u32 uVar3;
  u32 uVar4;
  u32 *puVar5;
  int iVar6;
  int iVar7;
  float *pfVar8;
  long lVar9;
  u64 uVar10;
  u64 uVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  u8 auStack_100 [16];
  u8 auStack_f0 [16];
  u8 auStack_e0 [16];
  u8 auStack_d0 [4];
  u8 auStack_cc [4];
  u32 uStack_c8;
  u32 uStack_c4;
  u32 uStack_c0;
  u32 uStack_bc;
  u8 uStack_b8;
  u8 uStack_b7;
  u8 uStack_b6;
  u8 auStack_b0 [16];
  u8 auStack_a0 [16];
  u8 auStack_90 [16];
  u8 auStack_80 [16];
  u8 auStack_70 [28];
  u8 auStack_54 [4];
  u8 auStack_50 [4];
  u32 uStack_4c;
  u32 uStack_48;
  u32 uStack_44;
  u32 *puStack_20;
  int iStack_10;
  
  puStack_20 = args;
  iStack_10 = ctx;
  __ct__7FVectorFRC7FVector(auStack_70,*args);
  __ct__7FVectorFRC7FVector(auStack_80,puStack_20[1]);
  __ct__7FVectorFRC7FVector(auStack_90,puStack_20[2]);
  __ct__7FVectorFRC7FVector(auStack_a0,puStack_20[3]);
  __ct__7FVectorFRC7FVector(auStack_b0,puStack_20[4]);
  iVar6 = iStack_10;
  uStack_44 = *(u32 *)puStack_20[5];
  uStack_48 = *(u32 *)puStack_20[6];
  uStack_4c = *(u32 *)puStack_20[7];
  uVar1 = *(u32 *)puStack_20[8];
  uVar2 = *(u32 *)puStack_20[9];
  uVar3 = *(u32 *)puStack_20[10];
  uVar4 = *(u32 *)puStack_20[0xb];
  puVar5 = (u32 *)puStack_20[0xc];
  __ct__12FpSmokeParamFv(auStack_100);
  Init__12FpSmokeParamFv(auStack_100);
  iVar7 = FindFParticle__10EffectCoreFPv(iVar6,0);
  lVar9 = __nw__FUi(0x100);
  uVar10 = 0;
  if (lVar9 != 0) {
    uVar10 = __ct__7FpSmokeFv(lVar9);
  }
  __as__7FVectorFRC7FVector(auStack_100,auStack_70);
  __as__7FVectorFRC7FVector(auStack_f0,auStack_80);
  __as__7FVectorFRC7FVector(auStack_e0,auStack_90);
  pfVar8 = (float *)vx__7FVectorFv(auStack_a0);
  fVar12 = *pfVar8;
  if (2.1474836e+09 <= fVar12) {
    fVar12 = fVar12 - 2.1474836e+09;
  }
  pfVar8 = (float *)vy__7FVectorFv(auStack_a0);
  fVar13 = *pfVar8;
  if (2.1474836e+09 <= fVar13) {
    fVar13 = fVar13 - 2.1474836e+09;
  }
  pfVar8 = (float *)vz__7FVectorFv(auStack_a0);
  fVar14 = *pfVar8;
  if (2.1474836e+09 <= fVar14) {
    fVar14 = fVar14 - 2.1474836e+09;
  }
  pfVar8 = (float *)vw__7FVectorFv(auStack_a0);
  fVar15 = *pfVar8;
  if (2.1474836e+09 <= fVar15) {
    fVar15 = fVar15 - 2.1474836e+09;
  }
  uVar11 = __ct__7_rgba32FUcUcUcUc
                     (auStack_50,(int)fVar12 & 0xff,(int)fVar13 & 0xff,(int)fVar14 & 0xff,
                      (int)fVar15 & 0xff);
  __as__7_rgba32FRC7_rgba32(auStack_d0,uVar11);
  pfVar8 = (float *)vx__7FVectorFv(auStack_b0);
  fVar12 = *pfVar8;
  if (2.1474836e+09 <= fVar12) {
    fVar12 = fVar12 - 2.1474836e+09;
  }
  pfVar8 = (float *)vy__7FVectorFv(auStack_b0);
  fVar13 = *pfVar8;
  if (2.1474836e+09 <= fVar13) {
    fVar13 = fVar13 - 2.1474836e+09;
  }
  pfVar8 = (float *)vz__7FVectorFv(auStack_b0);
  fVar14 = *pfVar8;
  if (2.1474836e+09 <= fVar14) {
    fVar14 = fVar14 - 2.1474836e+09;
  }
  pfVar8 = (float *)vw__7FVectorFv(auStack_b0);
  fVar15 = *pfVar8;
  if (2.1474836e+09 <= fVar15) {
    fVar15 = fVar15 - 2.1474836e+09;
  }
  uVar11 = __ct__7_rgba32FUcUcUcUc
                     (auStack_54,(int)fVar12 & 0xff,(int)fVar13 & 0xff,(int)fVar14 & 0xff,
                      (int)fVar15 & 0xff);
  __as__7_rgba32FRC7_rgba32(auStack_cc,uVar11);
  uStack_c8 = uStack_44;
  uStack_c4 = uStack_48;
  uStack_bc = uStack_4c;
  uStack_b8 = (u8)uVar2;
  uStack_b7 = (u8)uVar3;
  uStack_b6 = (u8)uVar4;
  uStack_c0 = uVar1;
  CreateEffect__7FpSmokeFP12FpSmokeParam(uVar10,auStack_100);
  *(int *)(iVar6 + iVar7 * 8 + 0x5b0) = (int)uVar10;
  *puVar5 = (int)uVar10;
  return 0;
}

/* ---- 0x00325940 size 0x3b4  fefCreateFlare(iiPPcPv)
 *      mangled: fefCreateFlare__FiiPPcPv */
u64
fefCreateFlare__FiiPPcPv(u64 id,u64 argc,u32 *args,int ctx)

{
  u32 uVar1;
  u32 uVar2;
  uint uVar3;
  u32 *puVar4;
  int iVar5;
  int iVar6;
  float *pfVar7;
  long lVar8;
  u64 uVar9;
  u64 uVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  u8 auStack_e0 [16];
  u8 auStack_d0 [4];
  u32 uStack_cc;
  u32 uStack_c8;
  u32 uStack_c4;
  u32 uStack_c0;
  u32 uStack_bc;
  u32 uStack_b8;
  u32 uStack_b4;
  byte bStack_b0;
  u8 auStack_a0 [16];
  u8 auStack_90 [16];
  u8 auStack_80 [16];
  u8 auStack_70 [20];
  u8 auStack_5c [4];
  u32 uStack_58;
  u32 uStack_54;
  u32 uStack_50;
  u32 uStack_4c;
  u32 uStack_48;
  u32 uStack_44;
  u32 *puStack_20;
  int iStack_10;
  
  puStack_20 = args;
  iStack_10 = ctx;
  __ct__7FVectorFRC7FVector(auStack_70,*args);
  __ct__7FVectorFRC7FVector(auStack_80,puStack_20[1]);
  uStack_44 = *(u32 *)puStack_20[2];
  uStack_48 = *(u32 *)puStack_20[3];
  uStack_4c = *(u32 *)puStack_20[4];
  uStack_50 = *(u32 *)puStack_20[5];
  uStack_54 = *(u32 *)puStack_20[6];
  uStack_58 = *(u32 *)puStack_20[7];
  uVar1 = *(u32 *)puStack_20[8];
  uVar2 = *(u32 *)puStack_20[9];
  uVar3 = *(uint *)puStack_20[10];
  __ct__7FVectorFRC7FVector(auStack_90,puStack_20[0xb]);
  iVar5 = iStack_10;
  puVar4 = (u32 *)puStack_20[0xc];
  __ct__12FpFlareParamFv(auStack_e0);
  Init__12FpFlareParamFv(auStack_e0);
  iVar6 = FindFParticle__10EffectCoreFPv(iVar5,0);
  lVar8 = __nw__FUi(0x70);
  uVar9 = 0;
  if (lVar8 != 0) {
    uVar9 = __ct__7FpFlareFv(lVar8);
  }
  __as__7FVectorFRC7FVector(auStack_e0,auStack_70);
  pfVar7 = (float *)vx__7FVectorFv(auStack_80);
  fVar11 = *pfVar7;
  if (2.1474836e+09 <= fVar11) {
    fVar11 = fVar11 - 2.1474836e+09;
  }
  pfVar7 = (float *)vy__7FVectorFv(auStack_80);
  fVar12 = *pfVar7;
  if (2.1474836e+09 <= fVar12) {
    fVar12 = fVar12 - 2.1474836e+09;
  }
  pfVar7 = (float *)vz__7FVectorFv(auStack_80);
  fVar13 = *pfVar7;
  if (2.1474836e+09 <= fVar13) {
    fVar13 = fVar13 - 2.1474836e+09;
  }
  pfVar7 = (float *)vw__7FVectorFv(auStack_80);
  fVar14 = *pfVar7;
  if (2.1474836e+09 <= fVar14) {
    fVar14 = fVar14 - 2.1474836e+09;
  }
  uVar10 = __ct__7_rgba32FUcUcUcUc
                     (auStack_5c,(int)fVar11 & 0xff,(int)fVar12 & 0xff,(int)fVar13 & 0xff,
                      (int)fVar14 & 0xff);
  __as__7_rgba32FRC7_rgba32(auStack_d0,uVar10);
  uStack_cc = uStack_44;
  uStack_c8 = uStack_48;
  uStack_c4 = uStack_4c;
  uStack_c0 = uStack_50;
  uStack_bc = uStack_54;
  uStack_b8 = uStack_58;
  bStack_b0 = bStack_b0 & 0xfc | (byte)uVar2 & 1 | (byte)((uVar3 & 1) << 1);
  uStack_b4 = uVar1;
  __as__7FVectorFRC7FVector(auStack_a0,auStack_90);
  CreateEffect__7FpFlareFP12FpFlareParam(uVar9,auStack_e0);
  *(int *)(iVar5 + iVar6 * 8 + 0x5b0) = (int)uVar9;
  *puVar4 = (int)uVar9;
  return 0;
}

/* ---- 0x00325ee0 size 0x488  fefCreateThunder(iiPPcPv)
 *      mangled: fefCreateThunder__FiiPPcPv */
u64
fefCreateThunder__FiiPPcPv(u64 id,u64 argc,u32 *args,int ctx)

{
  u32 uVar1;
  u32 *puVar2;
  int iVar3;
  int iVar4;
  float *pfVar5;
  long lVar6;
  u64 uVar7;
  u64 uVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  u8 auStack_e0 [16];
  u8 auStack_d0 [16];
  u8 auStack_c0 [4];
  u8 auStack_bc [4];
  u32 uStack_b8;
  u32 uStack_b4;
  u32 uStack_b0;
  u32 uStack_ac;
  u8 auStack_a0 [16];
  u8 auStack_90 [16];
  u8 auStack_80 [16];
  u8 auStack_70 [28];
  u8 auStack_54 [4];
  u8 auStack_50 [4];
  u32 uStack_4c;
  u32 uStack_48;
  u32 uStack_44;
  u32 *puStack_20;
  int iStack_10;
  
  puStack_20 = args;
  iStack_10 = ctx;
  __ct__7FVectorFRC7FVector(auStack_70,*args);
  __ct__7FVectorFRC7FVector(auStack_80,puStack_20[1]);
  __ct__7FVectorFRC7FVector(auStack_90,puStack_20[2]);
  __ct__7FVectorFRC7FVector(auStack_a0,puStack_20[3]);
  iVar3 = iStack_10;
  uStack_44 = *(u32 *)puStack_20[4];
  uStack_48 = *(u32 *)puStack_20[5];
  uStack_4c = *(u32 *)puStack_20[6];
  uVar1 = *(u32 *)puStack_20[7];
  puVar2 = (u32 *)puStack_20[8];
  __ct__14FpThunderParamFv(auStack_e0);
  Init__14FpThunderParamFv(auStack_e0);
  iVar4 = FindFParticle__10EffectCoreFPv(iVar3,0);
  lVar6 = __nw__FUi(0x70);
  uVar7 = 0;
  if (lVar6 != 0) {
    uVar7 = __ct__9FpThunderFv(lVar6);
  }
  __as__7FVectorFRC7FVector(auStack_e0,auStack_70);
  __as__7FVectorFRC7FVector(auStack_d0,auStack_80);
  pfVar5 = (float *)vx__7FVectorFv(auStack_90);
  fVar9 = *pfVar5;
  if (2.1474836e+09 <= fVar9) {
    fVar9 = fVar9 - 2.1474836e+09;
  }
  pfVar5 = (float *)vy__7FVectorFv(auStack_90);
  fVar10 = *pfVar5;
  if (2.1474836e+09 <= fVar10) {
    fVar10 = fVar10 - 2.1474836e+09;
  }
  pfVar5 = (float *)vz__7FVectorFv(auStack_90);
  fVar11 = *pfVar5;
  if (2.1474836e+09 <= fVar11) {
    fVar11 = fVar11 - 2.1474836e+09;
  }
  pfVar5 = (float *)vw__7FVectorFv(auStack_90);
  fVar12 = *pfVar5;
  if (2.1474836e+09 <= fVar12) {
    fVar12 = fVar12 - 2.1474836e+09;
  }
  uVar8 = __ct__7_rgba32FUcUcUcUc
                    (auStack_50,(int)fVar9 & 0xff,(int)fVar10 & 0xff,(int)fVar11 & 0xff,
                     (int)fVar12 & 0xff);
  __as__7_rgba32FRC7_rgba32(auStack_c0,uVar8);
  pfVar5 = (float *)vx__7FVectorFv(auStack_a0);
  fVar9 = *pfVar5;
  if (2.1474836e+09 <= fVar9) {
    fVar9 = fVar9 - 2.1474836e+09;
  }
  pfVar5 = (float *)vy__7FVectorFv(auStack_a0);
  fVar10 = *pfVar5;
  if (2.1474836e+09 <= fVar10) {
    fVar10 = fVar10 - 2.1474836e+09;
  }
  pfVar5 = (float *)vz__7FVectorFv(auStack_a0);
  fVar11 = *pfVar5;
  if (2.1474836e+09 <= fVar11) {
    fVar11 = fVar11 - 2.1474836e+09;
  }
  pfVar5 = (float *)vw__7FVectorFv(auStack_a0);
  fVar12 = *pfVar5;
  if (2.1474836e+09 <= fVar12) {
    fVar12 = fVar12 - 2.1474836e+09;
  }
  uVar8 = __ct__7_rgba32FUcUcUcUc
                    (auStack_54,(int)fVar9 & 0xff,(int)fVar10 & 0xff,(int)fVar11 & 0xff,
                     (int)fVar12 & 0xff);
  __as__7_rgba32FRC7_rgba32(auStack_bc,uVar8);
  uStack_b8 = uStack_44;
  uStack_b4 = uStack_48;
  uStack_b0 = uStack_4c;
  uStack_ac = uVar1;
  CreateEffect__9FpThunderFP14FpThunderParam(uVar7,auStack_e0);
  *(int *)(iVar3 + iVar4 * 8 + 0x5b0) = (int)uVar7;
  *puVar2 = (int)uVar7;
  return 0;
}

/* ---- 0x00326550 size 0x84  fefDelete(iiPPcPv)
 *      mangled: fefDelete__FiiPPcPv */
u64
fefDelete__FiiPPcPv(u64 id,u64 argc,u32 *args,int ctx)

{
  int iVar1;
  
  iVar1 = FindFParticle__10EffectCoreFPv(ctx,*(u32 *)*args);
  Delete__8PutiPrimFv(*(u32 *)(ctx + iVar1 * 8 + 0x5b0));
  Init__13tagFpPrimInfoFv(ctx + iVar1 * 8 + 0x5b0);
  return 0;
}

/* ---- 0x003265e0 size 0x90  fefSetLayer(iiPPcPv)
 *      mangled: fefSetLayer__FiiPPcPv */
u64
fefSetLayer__FiiPPcPv(u64 id,u64 argc,u32 *args,int ctx)

{
  u32 uVar1;
  int iVar2;
  
  uVar1 = *(u32 *)args[1];
  iVar2 = FindFParticle__10EffectCoreFPv(ctx,*(u32 *)*args);
  iVar2 = *(int *)(ctx + iVar2 * 8 + 0x5b0);
  (**(code **)(*(int *)(iVar2 + 0x10) + 0x2c))(iVar2,uVar1);
  return 0;
}

/* ---- 0x00326670 size 0x98  fefSetZTest(iiPPcPv)
 *      mangled: fefSetZTest__FiiPPcPv */
u64
fefSetZTest__FiiPPcPv(u64 id,u64 argc,u32 *args,int ctx)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)args[1];
  iVar2 = FindFParticle__10EffectCoreFPv(ctx,*(u32 *)*args);
  iVar2 = *(int *)(ctx + iVar2 * 8 + 0x5b0);
  (**(code **)(*(int *)(iVar2 + 0x10) + 0x30))(iVar2,iVar1 != 0);
  return 0;
}

/* ---- 0x00326710 size 0x90  fefSetAlphaPower(iiPPcPv)
 *      mangled: fefSetAlphaPower__FiiPPcPv */
u64
fefSetAlphaPower__FiiPPcPv(u64 id,u64 argc,u32 *args,int ctx)

{
  int iVar1;
  u32 uVar2;
  
  uVar2 = *(u32 *)args[1];
  iVar1 = FindFParticle__10EffectCoreFPv(ctx,*(u32 *)*args);
  iVar1 = *(int *)(ctx + iVar1 * 8 + 0x5b0);
  (**(code **)(*(int *)(iVar1 + 0x10) + 0x34))(uVar2,iVar1,0);
  return 0;
}

/* ---- 0x003267a0 size 0xc0  fefSetPos(iiPPcPv)
 *      mangled: fefSetPos__FiiPPcPv */
u64
fefSetPos__FiiPPcPv(u64 id,u64 argc,u32 *args,int ctx)

{
  u32 *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  u64 uVar5;
  u8 auStack_60 [16];
  u8 auStack_50 [48];
  u32 *puStack_20;
  int iStack_10;
  
  puVar1 = (u32 *)*args;
  puStack_20 = args;
  iStack_10 = ctx;
  __ct__7FVectorFRC7FVector(auStack_50,args[1]);
  iVar3 = iStack_10;
  iVar2 = *(int *)puStack_20[2];
  iVar4 = FindFParticle__10EffectCoreFPv(iStack_10,*puVar1);
  uVar5 = __ct__7FVectorFRC7FVector(auStack_60,auStack_50);
  iVar3 = *(int *)(iVar3 + iVar4 * 8 + 0x5b0);
  (**(code **)(*(int *)(iVar3 + 0x10) + 0x48))(iVar3,uVar5,iVar2 != 0);
  return 0;
}

/* ---- 0x00327700 size 0xf0  vibCreate(iiPPcPv)
 *      mangled: vibCreate__FiiPPcPv */
u64
vibCreate__FiiPPcPv(u64 id,u64 argc,u32 *args,int ctx)

{
  u32 *puVar1;
  int iVar2;
  u32 uVar3;
  u32 uVar4;
  long lVar5;
  
  uVar4 = *(u32 *)*args;
  puVar1 = (u32 *)args[1];
  iVar2 = FindVibIndex__10EffectCoreFUi(ctx,0);
  uVar3 = GetDataPtr__10EffectCoreFUciUiUi(ctx,0x4f,uVar4,0xffffffffffffffff,0xffffffffffffffff)
  ;
  lVar5 = __nw__FUi(0x44);
  uVar4 = 0;
  if (lVar5 != 0) {
    uVar4 = __ct__5CVibeFv(lVar5);
  }
  *(u32 *)(ctx + iVar2 * 8 + 0x588) = uVar4;
  *(u32 *)(ctx + iVar2 * 8 + 0x58c) = uVar3;
  *puVar1 = uVar4;
  return 0;
}

/* ---- 0x003277f0 size 0xac  vibStart(iiPPcPv)
 *      mangled: vibStart__FiiPPcPv */
u64 vibStart__FiiPPcPv(u64 id,u64 argc,u32 *args,int ctx)

{
  int iVar1;
  int iVar2;
  
  iVar2 = FindVibIndex__10EffectCoreFUi(ctx,*(u32 *)*args);
  iVar1 = *(int *)(ctx + iVar2 * 8 + 0x58c);
  Start__8CVibeManFP5CVibeP10_ActSeqHdri
            (sys__8CVibeMan,*(u32 *)(ctx + iVar2 * 8 + 0x588),
             iVar1 + (uint)*(ushort *)(iVar1 + 0xc) * 0x10,0);
  return 0;
}

/* ---- 0x003278a0 size 0xe4  vibStart2(iiPPcPv)
 *      mangled: vibStart2__FiiPPcPv */
u64
vibStart2__FiiPPcPv(u64 id,u64 argc,u32 *args,int ctx)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = *(int *)args[1];
  iVar3 = FindVibIndex__10EffectCoreFUi(ctx,*(u32 *)*args);
  iVar2 = *(int *)(ctx + iVar3 * 8 + 0x58c);
  Start__8CVibeManFP5CVibeP10_ActSeqHdri
            (sys__8CVibeMan,*(u32 *)(ctx + iVar3 * 8 + 0x588),
             iVar2 + (uint)*(ushort *)(iVar2 + 0xc) * 0x10 +
             (uint)*(ushort *)(iVar2 + 0x10 + iVar1 * 2) * 2,0);
  return 0;
}

/* ---- 0x00327990 size 0x74  vibStop(iiPPcPv)
 *      mangled: vibStop__FiiPPcPv */
u64 vibStop__FiiPPcPv(u64 id,u64 argc,u32 *args,int ctx)

{
  int iVar1;
  
  iVar1 = FindVibIndex__10EffectCoreFUi(ctx,*(u32 *)*args);
  Stop__5CVibeFv(*(u32 *)(ctx + iVar1 * 8 + 0x588));
  return 0;
}

/* ---- 0x00327a10 size 0xac  vibDelete(iiPPcPv)
 *      mangled: vibDelete__FiiPPcPv */
u64
vibDelete__FiiPPcPv(u64 id,u64 argc,u32 *args,int ctx)

{
  int iVar1;
  
  iVar1 = FindVibIndex__10EffectCoreFUi(ctx,*(u32 *)*args);
  if (*(int *)(ctx + iVar1 * 8 + 0x588) != 0) {
    __dt__5CVibeFv(*(u32 *)(ctx + iVar1 * 8 + 0x588),1);
    *(u32 *)(ctx + iVar1 * 8 + 0x588) = 0;
  }
  Init__8_VibInfoFv(ctx + iVar1 * 8 + 0x588);
  return 0;
}

/* ---- 0x00327ac0 size 0xbc  vibSetFade(iiPPcPv)
 *      mangled: vibSetFade__FiiPPcPv */
u64
vibSetFade__FiiPPcPv(u64 id,u64 argc,u32 *args,int ctx)

{
  u32 uVar1;
  u32 uVar2;
  u32 uVar3;
  int iVar4;
  
  uVar1 = *(u32 *)args[1];
  uVar2 = *(u32 *)args[2];
  uVar3 = *(u32 *)args[3];
  iVar4 = FindVibIndex__10EffectCoreFUi(ctx,*(u32 *)*args);
  SetFader__5CVibeFiii(*(u32 *)(ctx + iVar4 * 8 + 0x588),uVar1,uVar2,uVar3);
  return 0;
}

/* ---- 0x00327b80 size 0x8c  vibSetVolume(iiPPcPv)
 *      mangled: vibSetVolume__FiiPPcPv */
u64
vibSetVolume__FiiPPcPv(u64 id,u64 argc,u32 *args,int ctx)

{
  u32 uVar1;
  int iVar2;
  
  uVar1 = *(u32 *)args[1];
  iVar2 = FindVibIndex__10EffectCoreFUi(ctx,*(u32 *)*args);
  Volume__5CVibeFi(*(u32 *)(ctx + iVar2 * 8 + 0x588),uVar1);
  return 0;
}

/* ---- 0x00327c10 size 0xbc  sbgCreate(iiPPcPv)
 *      mangled: sbgCreate__FiiPPcPv */
u64
sbgCreate__FiiPPcPv(u64 id,u64 argc,u32 *args,int ctx)

{
  u32 *puVar1;
  u32 uVar2;
  long lVar3;
  u8 auStack_c0 [160];
  u32 *puStack_20;
  int iStack_10;
  
  puVar1 = (u32 *)args[1];
  puStack_20 = args;
  iStack_10 = ctx;
  SetPathname__7SysToolFPcPCc(auStack_c0,*args);
  lVar3 = __nw__FUi(0xbc);
  uVar2 = 0;
  if (lVar3 != 0) {
    uVar2 = __ct__9StreamBGMFv(lVar3);
  }
  *(u32 *)(ctx + 0x600) = uVar2;
  Create__9StreamBGMFPCc(*(u32 *)(ctx + 0x600),auStack_c0);
  Preload__9StreamBGMFv(*(u32 *)(ctx + 0x600));
  *puVar1 = *(u32 *)(ctx + 0x600);
  return 0;
}

/* ---- 0x00327cd0 size 0x50  sbgPlay(iiPPcPv)
 *      mangled: sbgPlay__FiiPPcPv */
u64 sbgPlay__FiiPPcPv(void)

{
  int in_a3_lo;
  
  Play__9StreamBGMFv(*(u32 *)(in_a3_lo + 0x600));
  return 0;
}

/* ---- 0x00327d20 size 0x6c  sbgStop(iiPPcPv)
 *      mangled: sbgStop__FiiPPcPv */
u64 sbgStop__FiiPPcPv(u64 id,u64 argc,int args,int ctx)

{
  Stop__9StreamBGMFib(*(u32 *)(ctx + 0x600),**(u32 **)(args + 4),0);
  return 0;
}

/* ---- 0x00327d90 size 0x7c  sbgDelete(iiPPcPv)
 *      mangled: sbgDelete__FiiPPcPv */
u64 sbgDelete__FiiPPcPv(void)

{
  long lVar1;
  int in_a3_lo;
  
  lVar1 = isPlay__9StreamBGMFv(*(u32 *)(in_a3_lo + 0x600));
  if (lVar1 != 0) {
    Stop__9StreamBGMFib(*(u32 *)(in_a3_lo + 0x600),0,0);
  }
  Delete__9StreamBGMFv(*(u32 *)(in_a3_lo + 0x600));
  *(u32 *)(in_a3_lo + 0x600) = 0;
  return 0;
}

/* ---- 0x00327e10 size 0x68  sbgSetVolume(iiPPcPv)
 *      mangled: sbgSetVolume__FiiPPcPv */
u64 sbgSetVolume__FiiPPcPv(u64 id,u64 argc,int args,int ctx)

{
  SetVolume__9StreamBGMFi(*(u32 *)(ctx + 0x600),**(u32 **)(args + 4));
  return 0;
}

/* ---- 0x00327e80 size 0x64  sbgGetReady(iiPPcPv)
 *      mangled: sbgGetReady__FiiPPcPv */
u64 sbgGetReady__FiiPPcPv(u64 id,u64 argc,int args,int ctx)

{
  u32 *puVar1;
  u32 uVar2;
  
  puVar1 = *(u32 **)(args + 4);
  uVar2 = isReady__9StreamBGMFv(*(u32 *)(ctx + 0x600));
  *puVar1 = uVar2;
  return 0;
}

