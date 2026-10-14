/* SECTION G  FIELD.BIN overlay (JP Furokuban, load 0x00430a00)
 * class: FVector   functions: 16
 * Source: Ghidra decompile (SH2JP_FIELD.BIN) with main-exe symbols and gp-relative globals resolved
 * (gp = 0x00412870). Types are still Ghidra-inferred unless a struct was recovered (see notes/G/_OverlayCopies_FVector.md).
 */

/* JP: 0x00430c50  FVector::FVector()   [__ct__7FVectorFv]  size=0x20 */
undefined4 * __ct__7FVectorFv(undefined4 *param_1)

{
  undefined4 in_zero_lo;
  undefined4 in_zero_hi;
  undefined4 in_zero_udw;
  undefined4 in_register_0000000c;
  
  *param_1 = in_zero_lo;
  param_1[1] = in_zero_hi;
  param_1[2] = in_zero_udw;
  param_1[3] = in_register_0000000c;
  return param_1;
}

/* JP: 0x004312f0  FVector::Origin()   [Origin__7FVectorFv]  size=0x40 */
void Origin__7FVectorFv(undefined4 *param_1)

{
  param_1[2] = 0;
  param_1[1] = 0;
  *param_1 = 0;
  param_1[3] = 0x3f800000;
  return;
}

/* JP: 0x00431330  FVector::FVector(float, float, float, float)   [__ct__7FVectorFffff]  size=0x88 */
undefined4
__ct__7FVectorFffff(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                   undefined4 param_5)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)vx__7FVectorFv(param_5);
  *puVar1 = param_1;
  puVar1 = (undefined4 *)vy__7FVectorFv(param_5);
  *puVar1 = param_2;
  puVar1 = (undefined4 *)vz__7FVectorFv(param_5);
  *puVar1 = param_3;
  puVar1 = (undefined4 *)vw__7FVectorFv(param_5);
  *puVar1 = param_4;
  return param_5;
}

/* JP: 0x004313c0  FVector::vw()   [vw__7FVectorFv]  size=0x1c */
int vw__7FVectorFv(int param_1)

{
  return param_1 + 0xc;
}

/* JP: 0x004313e0  FVector::vz()   [vz__7FVectorFv]  size=0x1c */
int vz__7FVectorFv(int param_1)

{
  return param_1 + 8;
}

/* JP: 0x00431400  FVector::vy()   [vy__7FVectorFv]  size=0x1c */
int vy__7FVectorFv(int param_1)

{
  return param_1 + 4;
}

/* JP: 0x00431420  FVector::vx()   [vx__7FVectorFv]  size=0x18 */
undefined4 vx__7FVectorFv(undefined4 param_1)

{
  return param_1;
}

/* JP: 0x00431fc0  FVector::__as(const FVector&)   [__as__7FVectorFRC7FVector]  size=0x14 */
undefined8 __as__7FVectorFRC7FVector(undefined8 param_1,undefined8 *param_2)

{
  undefined8 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  
  puVar4 = (undefined4 *)param_1;
  uVar1 = *param_2;
  uVar2 = *(undefined4 *)(param_2 + 1);
  uVar3 = *(undefined4 *)((int)param_2 + 0xc);
  *puVar4 = (int)uVar1;
  puVar4[1] = (int)((ulong)uVar1 >> 0x20);
  puVar4[2] = uVar2;
  puVar4[3] = uVar3;
  return param_1;
}

/* JP: 0x00432160  FVector::__mi   [__mi__7FVectorCFRC7FVector]  size=0x6c */
void __mi__7FVectorCFRC7FVector
               (undefined8 param_1,undefined1 (*param_2) [16],undefined1 (*param_3) [16])

{
  undefined1 auVar1 [16];
  undefined1 auVar2 [16];
  undefined1 auStack_10 [16];
  
  __ct__7FVectorFv(auStack_10);
  auVar1 = _lqc2(*param_2);
  auVar2 = _lqc2(*param_3);
  auVar1 = _vsub(auVar1,auVar2);
  auStack_10 = _sqc2(auVar1);
  __ct__7FVectorFRC7FVector(param_1,auStack_10);
  return;
}

/* JP: 0x004325b0  FVector::__pl   [__pl__7FVectorCFRC7FVector]  size=0x6c */
void __pl__7FVectorCFRC7FVector
               (undefined8 param_1,undefined1 (*param_2) [16],undefined1 (*param_3) [16])

{
  undefined1 auVar1 [16];
  undefined1 auVar2 [16];
  undefined1 auStack_10 [16];
  
  __ct__7FVectorFv(auStack_10);
  auVar1 = _lqc2(*param_2);
  auVar2 = _lqc2(*param_3);
  auVar1 = _vadd(auVar1,auVar2);
  auStack_10 = _sqc2(auVar1);
  __ct__7FVectorFRC7FVector(param_1,auStack_10);
  return;
}

/* JP: 0x00432970  FVector::__ami(const FVector&)   [__ami__7FVectorFRC7FVector]  size=0x1c */
undefined8 __ami__7FVectorFRC7FVector(undefined8 param_1,undefined1 (*param_2) [16])

{
  undefined1 auVar1 [16];
  undefined1 auVar2 [16];
  
  auVar2 = _lqc2(*param_2);
  auVar1 = _lqc2(*(undefined1 (*) [16])param_1);
  auVar1 = _vsub(auVar1,auVar2);
  auVar1 = _sqc2(auVar1);
  *(undefined1 (*) [16])param_1 = auVar1;
  return param_1;
}

/* JP: 0x00434a80  FVector::__apl(const FVector&)   [__apl__7FVectorFRC7FVector]  size=0x1c */
undefined8 __apl__7FVectorFRC7FVector(undefined8 param_1,undefined1 (*param_2) [16])

{
  undefined1 auVar1 [16];
  undefined1 auVar2 [16];
  
  auVar2 = _lqc2(*param_2);
  auVar1 = _lqc2(*(undefined1 (*) [16])param_1);
  auVar1 = _vadd(auVar1,auVar2);
  auVar1 = _sqc2(auVar1);
  *(undefined1 (*) [16])param_1 = auVar1;
  return param_1;
}

/* JP: 0x004a8160  FVector::__ml   [__ml__7FVectorCFf]  size=0x74 */
void __ml__7FVectorCFf(undefined4 param_1,undefined8 param_2,undefined1 (*param_3) [16])

{
  undefined1 auVar1 [16];
  undefined1 auVar2 [16];
  undefined1 auStack_10 [16];
  
  __ct__7FVectorFv(auStack_10);
  auVar1 = _lqc2(*param_3);
  auVar2 = _qmtc2(param_1);
  auVar1 = _vmulbc(auVar1,auVar2);
  auStack_10 = _sqc2(auVar1);
  __ct__7FVectorFRC7FVector(param_2,auStack_10);
  return;
}

/* JP: 0x004a81e0  FVector::InnerProduct   [InnerProduct__7FVectorCFRC7FVector]  size=0x24 */
undefined4 InnerProduct__7FVectorCFRC7FVector(undefined1 (*param_1) [16],undefined1 (*param_2) [16])

{
  undefined1 auVar1 [16];
  undefined1 auVar2 [16];
  
  auVar1 = _lqc2(*param_1);
  auVar2 = _lqc2(*param_2);
  auVar1 = _vmul(auVar1,auVar2);
  auVar1 = _vaddbc(auVar1,auVar1);
  auVar1 = _vaddbc(auVar1,auVar1);
  auVar1 = _qmfc2(auVar1._0_4_);
  return auVar1._0_4_;
}

/* JP: 0x004b1b50  FVector::__amu(const FVector&)   [__amu__7FVectorFRC7FVector]  size=0x1c */
undefined8 __amu__7FVectorFRC7FVector(undefined8 param_1,undefined1 (*param_2) [16])

{
  undefined1 auVar1 [16];
  undefined1 auVar2 [16];
  
  auVar2 = _lqc2(*param_2);
  auVar1 = _lqc2(*(undefined1 (*) [16])param_1);
  auVar1 = _vmul(auVar1,auVar2);
  auVar1 = _sqc2(auVar1);
  *(undefined1 (*) [16])param_1 = auVar1;
  return param_1;
}

/* JP: 0x004d0440  FVector::__as(const IVector&)   [__as__7FVectorFRC7IVector]  size=0x8c */
float * __as__7FVectorFRC7IVector(float *param_1,int *param_2)

{
  *param_1 = (float)*param_2;
  param_1[1] = (float)param_2[1];
  param_1[2] = (float)param_2[2];
  param_1[3] = (float)param_2[3];
  return param_1;
}
